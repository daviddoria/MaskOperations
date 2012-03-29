#include "Mask/MaskOperations.h"
#include "Mask/Mask.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 3)
    {
    std::cerr << "Required arguments: mask output" << std::endl;
    return EXIT_FAILURE;
    }

  std::string maskFilename = argv[1];
  std::string outputFilename = argv[2];

  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  Mask::BoundaryImageType::Pointer boundaryImage = Mask::BoundaryImageType::New();
  boundaryImage->SetRegions(mask->GetLargestPossibleRegion());
  boundaryImage->Allocate();
  
  mask->FindBoundary(boundaryImage.GetPointer());
  
  ITKHelpers::WriteImage(boundaryImage.GetPointer(), outputFilename);

  return EXIT_SUCCESS;
}
