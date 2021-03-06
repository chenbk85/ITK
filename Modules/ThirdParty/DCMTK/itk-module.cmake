set(DOCUMENTATION "This module builds the DCMTK library <a
href=\"http://dicom.offis.de/dcmtk.php.en\">DCMTK</a> DICOM
library suite.")

if(ITK_USE_SYSTEM_DCMTK)
  itk_module(ITKDCMTK
    DESCRIPTION
    "${DOCUMENTATION}"
    EXCLUDE_FROM_ALL
    )

else()
  itk_module(ITKDCMTK
    DEPENDS
    ITKZLIB
    ITKJPEG
    ITKTIFF
    DESCRIPTION
    "${DOCUMENTATION}"
    EXCLUDE_FROM_ALL
    )
endif()
