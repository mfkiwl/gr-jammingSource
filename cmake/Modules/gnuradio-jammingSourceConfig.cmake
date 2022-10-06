find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_JAMMINGSOURCE gnuradio-jammingSource)

FIND_PATH(
    GR_JAMMINGSOURCE_INCLUDE_DIRS
    NAMES gnuradio/jammingSource/api.h
    HINTS $ENV{JAMMINGSOURCE_DIR}/include
        ${PC_JAMMINGSOURCE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_JAMMINGSOURCE_LIBRARIES
    NAMES gnuradio-jammingSource
    HINTS $ENV{JAMMINGSOURCE_DIR}/lib
        ${PC_JAMMINGSOURCE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-jammingSourceTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_JAMMINGSOURCE DEFAULT_MSG GR_JAMMINGSOURCE_LIBRARIES GR_JAMMINGSOURCE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_JAMMINGSOURCE_LIBRARIES GR_JAMMINGSOURCE_INCLUDE_DIRS)
