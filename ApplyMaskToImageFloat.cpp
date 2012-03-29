// Custom
#include "Mask/MaskOperations.h"
#include "Mask/Mask.h"

// ITK
#include "itkImageFileReader.h"
#include "itkVectorImage.h"

int main(int argc, char*argv[])
{
  if(argc < 5)
    {
    std::cerr << "Required arguments: image mask output <pixel value>" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];
  std::string outputFilename = argv[3];
  
  std::cout << "Reading image: " << imageFilename << std::endl;
  std::cout << "Reading mask: " << maskFilename << std::endl;
  std::cout << "Output: " << outputFilename << std::endl;

  typedef itk::VectorImage<float, 2> ImageType;

  typedef itk::ImageFileReader<ImageType> ImageReaderType;
  ImageReaderType::Pointer imageReader = ImageReaderType::New();
  imageReader->SetFileName(imageFilename.c_str());
  imageReader->Update();
  
  ImageType::PixelType pixel(imageReader->GetOutput()->GetNumberOfComponentsPerPixel());
  std::stringstream ss;
  unsigned int counter = 0;
  for(int i = 4; i < argc; ++i)
  {
    ss << argv[i] << " ";
    counter++;
  }

  if(counter != imageReader->GetOutput()->GetNumberOfComponentsPerPixel())
  {
    std::stringstream ss;
    ss << "The number of components of the pixel argument (" << counter << ") does not match the number of components of the image (" << imageReader->GetOutput()->GetNumberOfComponentsPerPixel() << ")";
    throw std::runtime_error(ss.str());
  }

  for(unsigned int i = 0; i < imageReader->GetOutput()->GetNumberOfComponentsPerPixel(); ++i)
  {
    ss >> pixel[i];
  }

  std::cout << "Pixel: " << pixel << std::endl;

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  mask->ApplyToImage(imageReader->GetOutput(), pixel);

  ITKHelpers::WriteImage(imageReader->GetOutput(), outputFilename);

  return EXIT_SUCCESS;
}
