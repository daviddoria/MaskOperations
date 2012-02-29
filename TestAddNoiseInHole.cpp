#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  srand48((unsigned)time(0));
  
  typedef itk::Image<float, 2> ImageType;

  itk::Index<2> corner = {{0,0}};
  itk::Size<2> size = {{6, 6}};
  itk::ImageRegion<2> region(corner, size);
  
  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(2.0f);

  ITKHelpers::PrintImage(image.GetPointer());
  
  Mask::Pointer mask = Mask::New();
  mask->SetRegions(region);
  mask->Allocate();
  ITKHelpers::SetImageToConstant(mask.GetPointer(), mask->GetValidValue());
  ITKHelpers::PrintImage(mask.GetPointer());
  
  itk::Index<2> holeCorner = {{2,2}};
  itk::Size<2> holeSize = {{2, 2}};
  itk::ImageRegion<2> holeRegion(holeCorner, holeSize);
  
  ITKHelpers::SetRegionToConstant(mask.GetPointer(), holeRegion, mask->GetHoleValue());
  
  ITKHelpers::PrintImage(mask.GetPointer());

  float noiseVariance = 1.0f;
  MaskOperations::AddNoiseInHole(image.GetPointer(), mask.GetPointer(), noiseVariance);

  ITKHelpers::PrintImage(image.GetPointer());

  return EXIT_SUCCESS;
}
