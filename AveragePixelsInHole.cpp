#include "Mask/MaskOperations.h"
#include "Mask/Mask.h"

// ITK
#include "itkImageFileReader.h"
#include "itkVectorImage.h"

int main(int argc, char*argv[])
{
  if(argc != 3)
    {
    std::cerr << "Required arguments: image mask" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;

  typedef itk::VectorImage<float, 2> ImageType;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  std::cout << MaskOperations::AverageHoleValue(imageReader->GetOutput(), mask) << std::endl;

  return EXIT_SUCCESS;
}
