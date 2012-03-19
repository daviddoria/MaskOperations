/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "MaskOperations.h"

#include <stdexcept>

namespace MaskOperations
{

itk::ImageRegion<2> RandomRegionInsideHole(const Mask* const mask, const unsigned int halfWidth)
{
  std::vector<itk::Index<2> > holePixels = mask->GetHolePixelsInRegion(mask->GetLargestPossibleRegion());

  itk::ImageRegion<2> randomRegion;

  do
  {
    itk::Index<2> randomPixel = holePixels[rand() % holePixels.size()];
    randomRegion = ITKHelpers::GetRegionInRadiusAroundPixel(randomPixel, halfWidth);
  } while (!mask->IsHole(randomRegion));

  return randomRegion;
}

itk::ImageRegion<2> RandomValidRegion(const Mask* const mask, const unsigned int halfWidth)
{
  // The center pixel must be valid, so we choose one from the valid pixels.
  std::vector<itk::Index<2> > validPixels = mask->GetValidPixelsInRegion(mask->GetLargestPossibleRegion());

  itk::ImageRegion<2> randomRegion;

  do
  {
    itk::Index<2> randomPixel = validPixels[rand() % validPixels.size()];
    randomRegion = ITKHelpers::GetRegionInRadiusAroundPixel(randomPixel, halfWidth);
  } while (!mask->IsValid(randomRegion));

  return randomRegion;
}

itk::ImageRegion<2> ComputeBoundingBox(const Mask* const mask)
{
  itk::ImageRegionConstIterator<Mask> imageIterator(mask, mask->GetLargestPossibleRegion());

  itk::Index<2> min = {{mask->GetLargestPossibleRegion().GetSize()[0], mask->GetLargestPossibleRegion().GetSize()[1]}};
  itk::Index<2> max = {{0, 0}};

  while(!imageIterator.IsAtEnd())
    {
    if(imageIterator.Get())
    {
      if(imageIterator.GetIndex()[0] < min[0])
      {
        min[0] = imageIterator.GetIndex()[0];
      }
      if(imageIterator.GetIndex()[1] < min[1])
      {
        min[1] = imageIterator.GetIndex()[1];
      }
      if(imageIterator.GetIndex()[0] > max[0])
      {
        max[0] = imageIterator.GetIndex()[0];
      }
      if(imageIterator.GetIndex()[1] > max[1])
      {
        max[1] = imageIterator.GetIndex()[1];
      }
    }
    ++imageIterator;
    }

  itk::Size<2> size = {{max[0] - min[0], max[1] - min[1]}};
  itk::ImageRegion<2> region(min, size);
  return region;
}

} // end namespace
