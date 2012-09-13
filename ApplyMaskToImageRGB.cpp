#include <Mask/MaskOperations.h>
#include <Mask/Mask.h>

// ITK
#include "itkImageFileReader.h"

// Custom
#include "Color.h"

int main(int argc, char*argv[])
{
  if(argc != 7)
    {
    std::cerr << "Required arguments: image mask output R G B" << std::endl;
    return EXIT_FAILURE;
    }

  std::vector<int> values(3,0);
  std::stringstream ss;
  unsigned int counter = 0;
  for(int i = 4; i < argc; ++i)
  {
    ss << argv[i] << " ";
    counter++;
  }

  for(int i = 0; i < 3; ++i)
  {
    ss >> values[i];
  }

  typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
  ImageType::PixelType color;
  color[0] = values[0];
  color[1] = values[1];
  color[2] = values[2];

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];
  std::string outputFilename = argv[3];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;
  std::cout << "Color: " << static_cast<int>(values[0]) << " " << static_cast<int>(values[1]) << " " << static_cast<int>(values[2]) << std::endl;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  mask->ApplyToImage(imageReader->GetOutput(), color);

  ITKHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
