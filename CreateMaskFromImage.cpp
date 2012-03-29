#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

// Custom
#include "Color.h"

int main(int argc, char*argv[])
{
  if(argc != 6)
    {
    std::cerr << "Required arguments: image output R G B" << std::endl;
    return EXIT_FAILURE;
    }

  std::vector<int> values(3,0);
  std::stringstream ss;
  unsigned int counter = 0;
  for(int i = 3; i < argc; ++i)
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
  std::string outputMaskFilename = argv[2];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "outputMaskFilename: " << outputMaskFilename << std::endl;

  std::cout << "Color: " << static_cast<int>(values[0]) << " " << static_cast<int>(values[1]) << " " << static_cast<int>(values[2]) << std::endl;

  //typedef itk::Image<float, 2> ImageType;

  typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
  ImageType::PixelType pixelColor;
  pixelColor[0] = color.r;
  pixelColor[1] = color.g;
  pixelColor[2] = color.b;


  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  Mask::Pointer mask = Mask::New();
  mask->SetRegions(imageReader->GetOutput()->GetLargestPossibleRegion());
  mask->Allocate();
  mask->CreateFromImage(imageReader->GetOutput(), pixelColor);

  OutputHelpers::WriteImage(mask.GetPointer(), outputMaskFilename);

  return EXIT_SUCCESS;
}
