#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 9)
    {
    std::cerr << "Required arguments: image mask p0x p0y p1x p1y outputImage outputMask" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];

  std::stringstream ssPoints;
  ssPoints << argv[3] << " " << argv[4] << " " << argv[5] << " " << argv[6];
  itk::Index<2> p0;
  itk::Index<2> p1;
  ssPoints >> p0[0] >> p0[1] >> p1[0] >> p1[1];

  std::string outputImageFileName = argv[7];
  std::string outputMaskFileName = argv[8];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "P0: " << p0 << std::endl;
  std::cout << "P1: " << p1 << std::endl;
  std::cout << "Output image: " << outputImageFileName << std::endl;
  std::cout << "Output mask: " << outputMaskFileName << std::endl;

  typedef itk::Image<float, 2> ImageType;
  //typedef itk::Image<unsigned char, 2> ImageType;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  MaskOperations::InteroplateThroughHole(imageReader->GetOutput(), mask.GetPointer(), p0, p1);

  OutputHelpers::WriteImage(imageReader->GetOutput(), outputImageFileName);
  OutputHelpers::WriteImage(mask.GetPointer(), outputMaskFileName);

  return EXIT_SUCCESS;
}
