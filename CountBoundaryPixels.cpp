#include "MaskOperations.h"
#include "Mask.h"

// ITK
#include "itkImageFileReader.h"

int main(int argc, char*argv[])
{
  if(argc != 2)
    {
    std::cerr << "Required arguments: mask" << std::endl;
    return EXIT_FAILURE;
    }

  std::string maskFilename = argv[1];

  std::cout << "Reading mask: " << maskFilename << std::endl;

  Mask::Pointer mask = Mask::New();
  mask->Read(maskFilename.c_str());

  std::cout << "There are " << mask->CountBoundaryPixels() << " boundary pixels." << std::endl;

  return EXIT_SUCCESS;
}
