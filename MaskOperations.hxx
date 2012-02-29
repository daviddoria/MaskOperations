// STL
#include <stdexcept>

// Custom
#include "OutputHelpers.h"
#include "Mask.h"
#include "ITKHelpers.h"

// ITK
#include "itkGaussianOperator.h"
#include "itkLaplacianOperator.h"
#include "itkImageRegionIterator.h"
#include "itkBresenhamLine.h"

namespace MaskOperations
{
  
template <class TImage>
void CopySelfPatchIntoHoleOfTargetRegion(TImage* const image, const Mask* const mask,
                                  const itk::ImageRegion<2>& sourceRegionInput,
                                  const itk::ImageRegion<2>& destinationRegionInput)
{
  CopySourcePatchIntoHoleOfTargetRegion(image, image, mask, sourceRegionInput, destinationRegionInput);
}

template <class TImage>
void CopySourcePatchIntoHoleOfTargetRegion(const TImage* const sourceImage, TImage* const targetImage, const Mask* const mask,
                             const itk::ImageRegion<2>& sourceRegionInput, const itk::ImageRegion<2>& destinationRegionInput)
{
  itk::ImageRegion<2> fullImageRegion = sourceImage->GetLargestPossibleRegion();

  // We pass the regions by const reference, so copy them here before they are mutated
  itk::ImageRegion<2> sourceRegion = sourceRegionInput;
  itk::ImageRegion<2> destinationRegion = destinationRegionInput;

  // Move the source region to the desintation region
  itk::Offset<2> offset = destinationRegion.GetIndex() - sourceRegion.GetIndex();
  sourceRegion.SetIndex(sourceRegion.GetIndex() + offset);

  // Make the destination be entirely inside the image
  destinationRegion.Crop(fullImageRegion);
  sourceRegion.Crop(fullImageRegion);

  // Move the source region back
  sourceRegion.SetIndex(sourceRegion.GetIndex() - offset);

  itk::ImageRegionConstIterator<TImage> sourceIterator(sourceImage, sourceRegion);
  itk::ImageRegionIterator<TImage> destinationIterator(targetImage, destinationRegion);
  itk::ImageRegionConstIterator<Mask> maskIterator(mask, destinationRegion);

  while(!sourceIterator.IsAtEnd())
    {
    if(mask->IsHole(maskIterator.GetIndex())) // we are in the target region
      {
      destinationIterator.Set(sourceIterator.Get());
      }
    ++sourceIterator;
    ++maskIterator;
    ++destinationIterator;
    }
}

template<typename TImage>
void CreatePatchImage(const TImage* const image, const itk::ImageRegion<2>& sourceRegion, const itk::ImageRegion<2>& targetRegion,
                      const Mask* const mask, TImage* const result)
{
  // The input 'result' is expected to already be sized and initialized.

  itk::ImageRegionConstIterator<TImage> sourceRegionIterator(image, sourceRegion);
  itk::ImageRegionConstIterator<TImage> targetRegionIterator(image, targetRegion);

  itk::ImageRegionIterator<TImage> resultIterator(result, result->GetLargestPossibleRegion());

  while(!sourceRegionIterator.IsAtEnd())
    {

    if(mask->IsHole(targetRegionIterator.GetIndex()))
      {
      resultIterator.Set(sourceRegionIterator.Get());
      }
    else
      {
      resultIterator.Set(targetRegionIterator.Get());
      }

    ++sourceRegionIterator;
    ++targetRegionIterator;
    ++resultIterator;
    }
}

template<typename TImage>
itk::Index<2> FindHighestValueInMaskedRegion(const TImage* const image, float& maxValue, const Mask* const maskImage)
{
  //EnterFunction("FindHighestValueOnBoundary()");
  // Return the location of the highest pixel in 'image' out of the non-zero pixels in 'boundaryImage'. Return the value of that pixel by reference.

  // Explicity find the maximum on the boundary
  maxValue = 0.0f; // priorities are non-negative, so anything better than 0 will win

  std::vector<itk::Index<2> > boundaryPixels = ITKHelpers::GetNonZeroPixels(maskImage);

  if(boundaryPixels.size() <= 0)
    {
    throw std::runtime_error("FindHighestValueOnBoundary(): No boundary pixels!");
    }

  itk::Index<2> locationOfMaxValue = boundaryPixels[0];

  for(unsigned int i = 0; i < boundaryPixels.size(); ++i)
    {
    if(image->GetPixel(boundaryPixels[i]) > maxValue)
      {
      maxValue = image->GetPixel(boundaryPixels[i]);
      locationOfMaxValue = boundaryPixels[i];
      }
    }
  //DebugMessage<float>("Highest value: ", maxValue);
  //LeaveFunction("FindHighestValueOnBoundary()");
  return locationOfMaxValue;
}

template<typename TImage, typename TRegionIndicatorImage>
itk::Index<2> FindHighestValueInNonZeroRegion(const TImage* const image, float& maxValue,
                                              const TRegionIndicatorImage* const indicatorImage)
{
  // Create a mask from the indicator image
  Mask::Pointer mask = Mask::New();
  mask->CreateFromImage(image, itk::NumericTraits<typename TRegionIndicatorImage::PixelType>::Zero);
  return FindHighestValueInMaskedRegion(image, maxValue, mask);
}



template<typename TImage>
std::vector<typename TImage::PixelType> GetValidPixelsInRegion(const TImage* const image, const Mask* const mask,
                                                               const itk::ImageRegion<2>& region)
{
  std::vector<typename TImage::PixelType> validPixels;
  
  itk::ImageRegionConstIteratorWithIndex<TImage> imageIterator(image, region);

  while(!imageIterator.IsAtEnd())
    {
    if(mask->IsValid(imageIterator.GetIndex()))
      {
      validPixels.push_back(imageIterator.Get());
      }
    ++imageIterator;
    }

  return validPixels;
}

template<typename TImage>
void AddNoiseInHole(TImage* const image, const Mask* const mask, const float noiseVariance)
{
  itk::ImageRegionIterator<TImage> imageIterator(image, image->GetLargestPossibleRegion());

  while(!imageIterator.IsAtEnd())
    {
    if(mask->IsHole(imageIterator.GetIndex()))
      {
      float randomNumber = drand48();
      //std::cout << "randomNumber: " << randomNumber << std::endl;
      float noise = (randomNumber - .5) * noiseVariance;
      //std::cout << "noise: " << noise << std::endl;
      imageIterator.Set(imageIterator.Get() + noise);
      }
    ++imageIterator;
    }
}

template<typename TImage>
void InteroplateThroughHole(TImage* const image, Mask* const mask, const itk::Index<2>& p0, const itk::Index<2>& p1)
{
  // This function sets the pixels on the line in the mask to valid and sets the corresponding pixels in the image to the interpolated values.
  if(mask->IsHole(p0) || mask->IsHole(p1))
  {
    throw std::runtime_error("Both p0 and p1 must be valid (not holes)!");
  }
  
  itk::BresenhamLine<2> line;

  std::vector< itk::Index<2> > pixels = line.BuildLine(p0, p1);
  std::vector< itk::Index<2> > holePixels;

  // Find the start and end of the line
  typename TImage::PixelType value0;
  unsigned int firstHolePixelIndex = 0;

  // Look for the first hole pixel, and set value0 to the one before it (the pixel on the valid side of the hole boundary)
  unsigned int pixelId = 0;
  for(; pixelId < pixels.size(); ++pixelId)
    {
    // std::cout << "pixel " << i << " " << pixels[i] << std::endl;
    if(mask->IsHole(pixels[pixelId]))
      {
      firstHolePixelIndex = pixelId;
      value0 = image->GetPixel(pixels[pixelId-1]);
      break;
      }
    else
      {
      //std::cout << "Skipping pixel " << pixels[pixelId] << " while looking for beginning of hole." << std::endl;
      }
    }

  typename TImage::PixelType value1;
  // Look for the last hole pixel, and set value1 to the one after it (the pixel on the valid side of the hole boundary)
  unsigned int lastHolePixelIndex = 0;
  for(; pixelId < pixels.size(); ++pixelId)
    {
    // std::cout << "pixel " << i << " " << pixels[i] << std::endl;
    if(mask->IsValid(pixels[pixelId])) // We found a pixel on the other side of the hole.
      {
      value1 = image->GetPixel(pixels[pixelId]);
      lastHolePixelIndex = pixelId - 1; // The previous pixel is the last one in the hole.
      break;
      }
    else
      {
      //std::cout << "Skipping pixel " << pixels[pixelId] << " while looking for end of hole." << std::endl;
      }
    }

  float difference = value1 - value0;
  float step = difference / static_cast<float>(lastHolePixelIndex - firstHolePixelIndex);
  
  for(unsigned int i = firstHolePixelIndex; i <= lastHolePixelIndex; ++i)
    {
    //std::cout << "Changing pixel " << i << " " << pixels[i] << std::endl;
    if(!mask->IsHole(pixels[i]))
      {
      throw std::runtime_error("Something went wrong, we should only have hole pixels!");
      }
    image->SetPixel(pixels[i], value0 + i * step);
    mask->SetPixel(pixels[i], mask->GetValidValue());
    }
}

template<typename TImage>
void InteroplateLineBetweenPoints(TImage* const image, const itk::Index<2>& p0, const itk::Index<2>& p1)
{
  itk::BresenhamLine<2> line;

  std::vector< itk::Index<2> > pixels = line.BuildLine(p0, p1);

  typename TImage::PixelType value0 = image->GetPixel(p0);
  typename TImage::PixelType value1 = image->GetPixel(p1);

  float difference = value1 - value0;
  float step = difference / static_cast<float>(pixels.size());

  for(unsigned int i = 0; i < pixels.size(); i++)
    {
    //std::cout << "pixel " << i << " " << pixels[i] << std::endl;
    image->SetPixel(pixels[i], value0 + i * step);
    }
}

} // end namespace
