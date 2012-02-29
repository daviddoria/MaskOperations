#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  srand48((unsigned)time(0));

  typedef itk::Image<float, 2> ImageType;

  itk::Index<2> imageCorner = {{0,0}};
  itk::Size<2> imageSize = {{6, 6}};
  itk::ImageRegion<2> region(imageCorner, imageSize);

  ImageType::Pointer image = ImageType::New();
  image->SetRegions(region);
  image->Allocate();
  //image->FillBuffer(2.0f);

  itk::Index<2> leftHalfCorner = {{0,0}};
  itk::Size<2> leftHalfSize = {{imageSize[0]/2, imageSize[1]}};
  itk::ImageRegion<2> leftHalfRegion(leftHalfCorner, leftHalfSize);
  ITKHelpers::SetRegionToConstant(image.GetPointer(), leftHalfRegion, 5);

  itk::Index<2> rightHalfCorner = {{imageSize[0]/2, 0}};
  itk::Size<2> rightHalfSize = {{imageSize[0]/2, imageSize[1]}};
  itk::ImageRegion<2> rightHalfRegion(rightHalfCorner, rightHalfSize);
  ITKHelpers::SetRegionToConstant(image.GetPointer(), rightHalfRegion, 10);

  //ITKHelpers::PrintImage(image.GetPointer());

  Mask::Pointer mask = Mask::New();
  mask->SetRegions(region);
  mask->Allocate();
  ITKHelpers::SetImageToConstant(mask.GetPointer(), mask->GetValidValue());
  ITKHelpers::PrintImage(mask.GetPointer());

  itk::Index<2> holeCorner = {{2,2}};
  itk::Size<2> holeSize = {{2, 2}};
  itk::ImageRegion<2> holeRegion(holeCorner, holeSize);

  ITKHelpers::SetRegionToConstant(mask.GetPointer(), holeRegion, mask->GetHoleValue());
  ITKHelpers::SetRegionToConstant(image.GetPointer(), holeRegion, 0);

  std::cout << "image: " << std::endl;
  ITKHelpers::PrintImage(image.GetPointer());
  std::cout << "mask: " << std::endl;
  ITKHelpers::PrintImage(mask.GetPointer());

  itk::Index<2> p0 = {{0, 3}};
  itk::Index<2> p1 = {{5, 3}};
  
  MaskOperations::InteroplateThroughHole(image.GetPointer(), mask.GetPointer(), p0, p1);

  std::cout << "result: " << std::endl;
  ITKHelpers::PrintImage(image.GetPointer());

  return EXIT_SUCCESS;
}
