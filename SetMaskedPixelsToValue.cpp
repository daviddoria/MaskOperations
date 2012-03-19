#include "MaskOperations.h"
#include "Mask.h"
#include "OutputHelpers.h"

// ITK
#include "itkImageFileReader.h"

// Custom
#include "Color.h"

int main(int argc, char*argv[])
{
  if(argc != 4)
    {
    std::cerr << "Required arguments: image mask output" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];
  std::string outputFilename = argv[3];

  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;

  //typedef itk::Image<float, 2> ImageType;

  //typedef itk::Image<itk::CovariantVector<unsigned char, 3>, 2> ImageType;
//   ImageType::PixelType color;
//   color[0] = 0;
//   color[1] = 255;
//   color[2] = 0;

  typedef itk::VectorImage<float, 2> ImageType;
  
//   ImageType::PixelType color;
//   color.SetRed(0);
//   color.SetGreen(255);
//   color.SetBlue(0);


  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();

  ImageType::PixelType value(imageReader->GetOutput()->GetNumberOfComponentsPerPixel());
  value.Fill(0);
  
  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  mask->ApplyToImage(imageReader->GetOutput(), value);

  OutputHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
