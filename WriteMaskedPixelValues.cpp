// STL
#include <fstream>

// Custom
#include "MaskOperations.h"
#include "Mask.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 4)
    {
    std::cerr << "Required arguments: image mask output.txt" << std::endl;
    return EXIT_FAILURE;
    }

  std::string imageFilename = argv[1];
  std::string maskFilename = argv[2];
  std::string outputFilename = argv[3];

  std::cout << "Reading mask: " << maskFilename << std::endl;

  typedef itk::VectorImage<float, 2> ImageType;
  
  typedef itk::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(imageFilename);
  reader->Update();
  
  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  typedef std::vector<itk::Index<2> > PixelContainer;
  PixelContainer holePixels = mask->GetHolePixels();

  std::ofstream fout(outputFilename.c_str());

  for(PixelContainer::const_iterator iter = holePixels.begin(); iter != holePixels.end(); ++iter)
  {
    for(unsigned int component = 0; component < reader->GetOutput()->GetNumberOfComponentsPerPixel(); ++component)
      {
      fout << reader->GetOutput()->GetPixel(*iter)[component] << " ";
      }
    fout << std::endl;
  }

  fout.close();
  
  return EXIT_SUCCESS;
}
