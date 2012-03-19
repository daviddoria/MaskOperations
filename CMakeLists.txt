cmake_minimum_required(VERSION 2.6)
PROJECT(MaskOperations)
SET( INSTALL_DIR ${CMAKE_INSTALL_PREFIX} )

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

# add_executable(AddNoiseInMaskedRegion AddNoiseInMaskedRegion.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(AddNoiseInMaskedRegion ${ITK_LIBRARIES})
# 
# add_executable(InterpolateThroughHole InterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(InterpolateThroughHole ${ITK_LIBRARIES})


#SET(OS_SetMaskedPixelsToValue CACHE BOOL "Compute the absolute value (pixel-wise) of an image")
#if(OS_SetMaskedPixelsToValue)
  ADD_EXECUTABLE(SetMaskedPixelsToValue SetMaskedPixelsToValue.cpp  Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
  TARGET_LINK_LIBRARIES(SetMaskedPixelsToValue ${ITK_LIBRARIES})
  INSTALL( TARGETS SetMaskedPixelsToValue RUNTIME DESTINATION ${INSTALL_DIR} )
#endif()

add_executable(WriteMaskedPixelValues WriteMaskedPixelValues.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(WriteMaskedPixelValues ${ITK_LIBRARIES})
INSTALL( TARGETS WriteMaskedPixelValues RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(ApplyMaskToImage ApplyMaskToImage.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(ApplyMaskToImage ${ITK_LIBRARIES})
INSTALL( TARGETS ApplyMaskToImage RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(AddConstantInHole AddConstantInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(AddConstantInHole ${ITK_LIBRARIES})
INSTALL( TARGETS AddConstantInHole RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(BlurInHole BlurInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(BlurInHole ${ITK_LIBRARIES})
INSTALL( TARGETS BlurInHole RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(MedianFilterInHole MedianFilterInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(MedianFilterInHole ${ITK_LIBRARIES})
INSTALL( TARGETS MedianFilterInHole RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(CountBoundaryPixels CountBoundaryPixels.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(CountBoundaryPixels ${ITK_LIBRARIES})
INSTALL( TARGETS CountBoundaryPixels RUNTIME DESTINATION ${INSTALL_DIR} )

add_executable(HoleInformation HoleInformation.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(HoleInformation ${ITK_LIBRARIES})
INSTALL( TARGETS HoleInformation RUNTIME DESTINATION ${INSTALL_DIR} )

############## Tests ##############
#
# add_executable(TestAddNoiseInHole TestAddNoiseInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(TestAddNoiseInHole ${ITK_LIBRARIES})
#
# add_executable(TestInterpolateThroughHole TestInterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
# target_link_libraries(TestInterpolateThroughHole ${ITK_LIBRARIES})
