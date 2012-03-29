#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

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

//   itk::RGBPixel<unsigned char> color;
//   color.SetRed(values[0]);
//   color.SetGreen(values[1]);
//   color.SetBlue(values[2]);
  Color color;
  color.r = values[0];
  color.g = values[1];
  color.b = values[2];

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];
  std::string outputFilename = argv[3];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;
  std::cout << "Color: " << static_cast<int>(values[0]) << " " << static_cast<int>(values[1]) << " " << static_cast<int>(values[2]) << std::endl;

  //typedef itk::Image<float, 2> ImageType;

  //typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
//   ImageType::PixelType color;
//   color[0] = 0;
//   color[1] = 255;
//   color[2] = 0;

  typedef itk::Image<itk::RGBPixel<unsigned char>, 2> ImageType;


//   Color color;
//   color.r = 0;
//   color.g = 255;
//   color.b = 0;
  
  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());


  mask->ApplyColorToImage(imageReader->GetOutput(), color);

  OutputHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
