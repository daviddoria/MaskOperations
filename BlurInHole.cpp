#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 5)
    {
    std::cerr << "Required arguments: image mask kernelVariance output" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];

  std::stringstream ssVariance;
  ssVariance << argv[3];
  float kernelVariance = 0.0f;
  ssVariance >> kernelVariance;

  std::string outputFilename = argv[4];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Noise variance: " << kernelVariance << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;

  typedef itk::Image<float, 2> ImageType;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  MaskOperations::BlurInHole(imageReader->GetOutput(), mask, kernelVariance);

  OutputHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
