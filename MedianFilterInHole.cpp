#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 5)
    {
    std::cerr << "Required arguments: image mask kernelRadius output" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];

  std::stringstream ssRadius;
  ssRadius << argv[3];
  unsigned int kernelRadius = 0;
  ssRadius >> kernelRadius;

  std::string outputFilename = argv[4];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Kernel radius: " << kernelRadius << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;

  typedef itk::Image<float, 2> ImageType;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  MaskOperations::MedianFilterInHole(imageReader->GetOutput(), mask, kernelRadius);

  OutputHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
