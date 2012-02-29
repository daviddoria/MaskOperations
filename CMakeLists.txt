cmake_minimum_required(VERSION 2.6)
PROJECT(MaskOperations)

FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

add_executable(AddNoiseInMaskedRegion AddNoiseInMaskedRegion.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(AddNoiseInMaskedRegion ${ITK_LIBRARIES})

add_executable(TestAddNoiseInHole TestAddNoiseInHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(TestAddNoiseInHole ${ITK_LIBRARIES})

add_executable(TestInterpolateThroughHole TestInterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(TestInterpolateThroughHole ${ITK_LIBRARIES})

add_executable(InterpolateThroughHole InterpolateThroughHole.cpp MaskOperations.cpp Mask.cpp OutputHelpers.cpp ITKHelpers.cpp Helpers.cpp)
target_link_libraries(InterpolateThroughHole ${ITK_LIBRARIES})
