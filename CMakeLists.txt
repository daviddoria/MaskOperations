cmake_minimum_required(VERSION 2.6)
PROJECT(MaskOperations)

# This is needed for shared_ptr and the trick using enable_if and if_fundamental to allow scalars
# to be treated as the 0th component of a vector.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

SET( INSTALL_DIR ${CMAKE_INSTALL_PREFIX} )

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

add_subdirectory(Mask)

# add_executable(AddNoiseInMaskedRegion AddNoiseInMaskedRegion.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(AddNoiseInMaskedRegion ${ITK_LIBRARIES})
# 
# add_executable(InterpolateThroughHole InterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(InterpolateThroughHole ${ITK_LIBRARIES})

add_library(MaskedOperations Mask/Mask.cpp Mask/ITKHelpers/ITKHelpers.cpp Mask/Helpers/Helpers.cpp Mask/MaskOperations.cpp)

SET(MO_SetMaskedPixelsToValue CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_SetMaskedPixelsToValue)
  ADD_EXECUTABLE(SetMaskedPixelsToValue SetMaskedPixelsToValue.cpp)
  TARGET_LINK_LIBRARIES(SetMaskedPixelsToValue ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS SetMaskedPixelsToValue RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_AveragePixelsInHole CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_AveragePixelsInHole)
  add_executable(AveragePixelsInHole AveragePixelsInHole.cpp)
  target_link_libraries(AveragePixelsInHole ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS AveragePixelsInHole RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_WriteMaskedPixelValues CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_WriteMaskedPixelValues)
  add_executable(WriteMaskedPixelValues WriteMaskedPixelValues.cpp)
  target_link_libraries(WriteMaskedPixelValues ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS WriteMaskedPixelValues RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_CreateMaskFromImage CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_CreateMaskFromImage)
  add_executable(CreateMaskFromImage CreateMaskFromImage.cpp)
  target_link_libraries(CreateMaskFromImage ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS CreateMaskFromImage RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_ApplyMaskToImageRGB CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_ApplyMaskToImageRGB)
  add_executable(ApplyMaskToImageRGB ApplyMaskToImageRGB.cpp)
  target_link_libraries(ApplyMaskToImageRGB ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS ApplyMaskToImageRGB RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_ApplyMaskToImageFloat CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_ApplyMaskToImageFloat)
  add_executable(ApplyMaskToImageFloat ApplyMaskToImageFloat.cpp)
  target_link_libraries(ApplyMaskToImageFloat ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS ApplyMaskToImageFloat RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_AddConstantInHole CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_AddConstantInHole)
  add_executable(AddConstantInHole AddConstantInHole.cpp)
  target_link_libraries(AddConstantInHole ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS AddConstantInHole RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_BlurInHole CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_BlurInHole)
  add_executable(BlurInHole BlurInHole.cpp)
  target_link_libraries(BlurInHole ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS BlurInHole RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_MedianFilterInHole CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_MedianFilterInHole)
  add_executable(MedianFilterInHole MedianFilterInHole.cpp)
  target_link_libraries(MedianFilterInHole ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS MedianFilterInHole RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_CountBoundaryPixels CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_CountBoundaryPixels)
  add_executable(CountBoundaryPixels CountBoundaryPixels.cpp)
  target_link_libraries(CountBoundaryPixels ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS CountBoundaryPixels RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_ExtractBoundary CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_ExtractBoundary)
  add_executable(ExtractBoundary ExtractBoundary.cpp)
  target_link_libraries(ExtractBoundary ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS ExtractBoundary RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

SET(MO_HoleInformation CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
if(MO_HoleInformation)
  add_executable(HoleInformation HoleInformation.cpp)
  target_link_libraries(HoleInformation ${ITK_LIBRARIES} MaskedOperations)
  INSTALL( TARGETS HoleInformation RUNTIME DESTINATION ${INSTALL_DIR} )
endif()

############## Tests ##############
#
# add_executable(TestAddNoiseInHole TestAddNoiseInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(TestAddNoiseInHole ${ITK_LIBRARIES})
#
# add_executable(TestInterpolateThroughHole TestInterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(TestInterpolateThroughHole ${ITK_LIBRARIES})
