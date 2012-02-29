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

} // end namespace
