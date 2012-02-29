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

#ifndef MaskOperations_H
#define MaskOperations_H

// Custom
class Mask;

// ITK
#include "itkIndex.h"
#include "itkImageRegion.h"

namespace MaskOperations
{

/** Return a random region that is entirely inside the hole. */
itk::ImageRegion<2> RandomRegionInsideHole(const Mask* const mask, const unsigned int halfWidth);

/** Return a random region that is entirely valid. */
itk::ImageRegion<2> RandomValidRegion(const Mask* const mask, const unsigned int halfWidth);

template <class TImage>
void CopySelfPatchIntoHoleOfTargetRegion(TImage* const image, const Mask* const mask,
                                         const itk::ImageRegion<2>& sourceRegionInput,
                                         const itk::ImageRegion<2>& destinationRegionInput);

template <class TImage>
void CopySourcePatchIntoHoleOfTargetRegion(const TImage* const sourceImage, TImage* const targetImage, const Mask* const mask,
                                           const itk::ImageRegion<2>& sourceRegionInput,
                                           const itk::ImageRegion<2>& destinationRegionInput);

template<typename TImage>
void CreatePatchImage(const TImage* const image, const itk::ImageRegion<2>& sourceRegion,
                      const itk::ImageRegion<2>& targetRegion, const Mask* const mask, TImage* const result);


// Return the highest value of the specified image out of the pixels under a specified BoundaryImage.
template<typename TImage>
itk::Index<2> FindHighestValueInMaskedRegion(const TImage* const image, float& maxValue, const Mask* const maskImage);

template<typename TImage, typename TRegionIndicatorImage>
itk::Index<2> FindHighestValueInNonZero(const TImage* const image, float& maxValue, const TRegionIndicatorImage* const maskImage);

/** Get the average value of the non-masked neighbors of a pixel. */
template<typename TImage>
typename TImage::PixelType AverageNonMaskedNeighborValue(const TImage* const image, const Mask* const mask,
                                                         const itk::Index<2>& pixel);

/** Get the average value of the masked neighbors of a pixel. */
template<typename TImage>
typename TImage::PixelType AverageMaskedNeighborValue(const TImage* const image, const Mask* const mask,
                                                      const itk::Index<2>& pixel);

/** Get the average value of the masked neighbors of a pixel. */
template<typename TImage>
std::vector<typename TImage::PixelType> GetValidPixelsInRegion(const TImage* const image, const Mask* const mask,
                                                               const itk::ImageRegion<2>& region);

/** Get the average value of the masked neighbors of a pixel. */
template<typename TImage>
void AddNoiseInHole(TImage* const image, const Mask* const mask, const float noiseVariance);

template<typename TImage>
void InteroplateThroughHole(TImage* const image, Mask* const mask, const itk::Index<2>& p0, const itk::Index<2>& p1, const unsigned int lineThickness = 0);

template<typename TImage>
void InteroplateLineBetweenPoints(TImage* const image, const itk::Index<2>& p0, const itk::Index<2>& p1);

} // end namespace

#include "MaskOperations.hxx"

#endif
