itk_module_test()

set(ITKDeprecatedTests
itk2DDeformableTest.cxx
itkDeformableTest.cxx
itkNonThreadedShrinkImageTest.cxx
itkNonUniformBSplineTest.cxx
itkReflectImageFilterTest.cxx
itkShiftScaleInPlaceImageFilterTest.cxx
itkTwoOutputExampleImageFilterTest.cxx
)

# For itkTestDriverIncludeDeprecatedIOFactories.h.
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

CreateTestDriver_SupportBuildInIOFactories(ITKDeprecated  "${ITKDeprecated-Test_LIBRARIES}" "${ITKDeprecatedTests}")

itk_add_test(NAME itk2DDeformableTest
      COMMAND ITKDeprecatedTestDriver itk2DDeformableTest)
itk_add_test(NAME itkDeformableTest
      COMMAND ITKDeprecatedTestDriver itkDeformableTest)
itk_add_test(NAME itkNonThreadedShrinkImageTest
      COMMAND ITKDeprecatedTestDriver itkNonThreadedShrinkImageTest)
itk_add_test(NAME itkNonUniformBSplineTest
      COMMAND ITKDeprecatedTestDriver itkNonUniformBSplineTest)
itk_add_test(NAME itkReflectImageFilterTest
      COMMAND ITKDeprecatedTestDriver itkReflectImageFilterTest)
itk_add_test(NAME itkShiftScaleInPlaceImageFilterTest
      COMMAND ITKDeprecatedTestDriver itkShiftScaleInPlaceImageFilterTest)
itk_add_test(NAME itkTwoOutputExampleImageFilterTest
      COMMAND ITKDeprecatedTestDriver itkTwoOutputExampleImageFilterTest)


create_test_sourcelist(DeprecatedIOTests  DeprecatedIOTestDriver.cxx
        itkDICOMImageIO2Test.cxx
        itkDicomImageIOTest.cxx
        itkDicomImageIODirection2DTest.cxx
        itkDICOMImageSeriesTest.cxx
        itkDICOMImageSeriesTest2.cxx
        itkDICOMSeriesFileNamesTest.cxx
        itkImageReadDICOMSeriesWriteTest.cxx
        itkAnalyzeImageIODirectionsTest.cxx
        itkAnalyzeImageIOTest.cxx
        itkAnalyzeImageIOTest2
        itkAnalyzeImageIOBadHeader
        itkAnalyzeImageIORGBImageTest

        itkAnalyzeImageIODirectionsTest

        EXTRA_INCLUDE itkTestDriverIncludeDeprecatedIOFactories.h
        FUNCTION  ProcessArgumentsAndRegisterDeprecatedIOFactories
)
add_library(ITKAnalyzeIO-TestHelper itkAnalyzeImageIOTestHelper.cxx)
itk_module_target_label(ITKAnalyzeIO-TestHelper)
target_link_libraries(ITKAnalyzeIO-TestHelper  ${ITKDeprecated_LIBRARIES})

list(APPEND ITKDeprecated-Test_LIBRARIES ITKAnalyzeIO-TestHelper)
add_executable(DeprecatedIOTestDriver DeprecatedIOTestDriver.cxx  ${DeprecatedIOTests})
itk_module_target_label(DeprecatedIOTestDriver)
target_link_libraries(DeprecatedIOTestDriver ${ITKDeprecated-Test_LIBRARIES})


##Analyze Test Suite
itk_add_test(NAME itkAnalyzeIOBigEndianCompressed.hdr
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
         DATA{${ITK_DATA_ROOT}/Input/BigEndianCompressed.hdr})
itk_add_test(NAME itkAnalyzeIOBigEndianCompressed.img
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
         DATA{${ITK_DATA_ROOT}/Input/BigEndianCompressed.img})
itk_add_test(NAME itkAnalyzeIOBigEndianCompressed.img.gz
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
         DATA{${ITK_DATA_ROOT}/Input/BigEndianCompressed.img.gz})
itk_add_test(NAME itkAnalyzeIOBigEndian
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
              DATA{${ITK_DATA_ROOT}/Input/BigEndian.hdr,BigEndian.mhd,BigEndian.img})
itk_add_test(NAME itkAnalyzeIOLittleEndianCompressed
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
              DATA{${ITK_DATA_ROOT}/Input/LittleEndianCompressed.hdr,LittleEndianCompressed.img.gz})
itk_add_test(NAME itkAnalyzeIOLittleEndian
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR}
              DATA{${ITK_DATA_ROOT}/Input/LittleEndian.hdr,LittleEndian.mhd,LittleEndian.img})
itk_add_test(NAME itkAnalyzeIOInternalTests
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest ${ITK_TEST_OUTPUT_DIR} )
itk_add_test(NAME itkAnalyzeIOShouldFail
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest2 ${ITK_TEST_OUTPUT_DIR}
                                false DATA{${ITK_DATA_ROOT}/Input/ramp.gipl})
itk_add_test(NAME itkAnalyzeIOShouldSucceed
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest2 ${ITK_TEST_OUTPUT_DIR}
                                true DATA{${ITK_DATA_ROOT}/Input/LittleEndian.hdr,LittleEndian.mhd,LittleEndian.img})
itk_add_test(NAME itkAnalyzeIOShouldSucceedZ
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOTest2 ${ITK_TEST_OUTPUT_DIR}
                                true DATA{${ITK_DATA_ROOT}/Input/LittleEndianZ.hdr,LittleEndianZ.img.gz})
itk_add_test(NAME itkAnalyzeImageIODirectionsTest
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIODirectionsTest
                                ${ITK_TEST_OUTPUT_DIR})
itk_add_test(NAME itkAnalyzeImageIOBadHeader
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIOBadHeader
                                ${ITK_TEST_OUTPUT_DIR})
itk_add_test(NAME itkAnalyzeImageIORGBImageTest
      COMMAND DeprecatedIOTestDriver itkAnalyzeImageIORGBImageTest
                                       ${ITK_TEST_OUTPUT_DIR})

itk_add_test(NAME itkDICOMImageSeriesTest
     COMMAND DeprecatedIOTestDriver itkDICOMImageSeriesTest
             DATA{${ITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm} 0)
itk_add_test(NAME itkDICOMImageSeriesTest2
     COMMAND DeprecatedIOTestDriver  itkDICOMImageSeriesTest2
             DATA{${ITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm})
itk_add_test(NAME itkDICOMSeriesFileNamesTest
     COMMAND DeprecatedIOTestDriver itkDICOMSeriesFileNamesTest
             DATA{${ITK_DATA_ROOT}/Input/DicomSeries/,REGEX:Image[0-9]+.dcm})
itk_add_test(NAME itkDicomDifficultFile
     COMMAND DeprecatedIOTestDriver
         itkDicomImageIOTest DATA{${ITK_DATA_ROOT}/Input/012345.002.050}
         ${ITK_TEST_OUTPUT_DIR}/itkDicomDifficultFile.png)
itk_add_test(NAME itkDicomImageIODirection2DTest
      COMMAND DeprecatedIOTestDriver itkDicomImageIODirection2DTest
              ${ITK_TEST_OUTPUT_DIR}/itkDicomImage3DIODirection2DTest.dcm ${ITK_TEST_OUTPUT_DIR}/itkDicomImage3DIODirection2DTest.mhd ${ITK_TEST_OUTPUT_DIR}/itkDicomImage2DIODirection2DTest.mhd)
itk_add_test(NAME itkImageReadDICOMSeriesWriteTest
     COMMAND DeprecatedIOTestDriver
      itkImageReadDICOMSeriesWriteTest DATA{${ITK_DATA_ROOT}/Input/HeadMRVolumeCompressed.mha}
  ${ITK_TEST_OUTPUT_DIR}/DICOMSeriesOutputHeadMRVolume)
itk_add_test(NAME itkImageReadDICOMSeriesWriteWithDirection002Test
       COMMAND DeprecatedIOTestDriver
      itkImageReadDICOMSeriesWriteTest DATA{${ITK_DATA_ROOT}/Input/HeadMRVolumeWithDirection002.mhd}
  ${ITK_TEST_OUTPUT_DIR}/DICOMSeriesOutputHeadMRVolumeWithDirection002)
itk_add_test(NAME itkImageReadDICOMSeriesWriteWithDirection003Test
       COMMAND DeprecatedIOTestDriver
      itkImageReadDICOMSeriesWriteTest DATA{${ITK_DATA_ROOT}/Input/HeadMRVolumeWithDirection003.mhd}
  ${ITK_TEST_OUTPUT_DIR}/DICOMSeriesOutputHeadMRVolumeWithDirection003)

## The following an expample of how to write a program that uses the deprecated AnalyzeIO class.
add_executable(ConvertAnalyzeFile ConvertAnalyzeFile.cxx)
target_link_libraries(ConvertAnalyzeFile ${ITKDeprecated-Test_LIBRARIES})

## The following example showed how to deform a MeshModel
add_executable(DeformableModel1 DeformableModel1.cxx )
target_link_libraries(DeformableModel1 ${ITKDeprecated-Test_LIBRARIES})

add_executable(DeformableModel2 DeformableModel2.cxx )
target_link_libraries(DeformableModel2 ${ITKDeprecated-Test_LIBRARIES})

# temporary solution for all print tests. Each module should have its own print test later.
add_executable(itkDeprecatedPrintTest  itkDeprecatedPrintTest.cxx)
itk_module_target_label(itkDeprecatedPrintTest)
target_link_libraries(itkDeprecatedPrintTest ${ITKDeprecated-Test_LIBRARIES})
itk_add_test(NAME itkDeprecatedPrintTest COMMAND itkDeprecatedPrintTest)
