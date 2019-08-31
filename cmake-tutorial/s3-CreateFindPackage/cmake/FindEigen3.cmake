# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindEigen3
# --------
#
# Find the Eigen3 library (libEigen3).
#
# Imported targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :prop_tgt:`IMPORTED` targets:
#
# ``Eigen3::Eigen3``
#   The Eigen3 library, if found.
#
# Result variables
# ^^^^^^^^^^^^^^^^
#
# This module will set the following variables in your project:
#
# ``Eigen3_FOUND``
#   true if the Eigen3 headers and libraries were found
# ``Eigen3_INCLUDE_DIR``
#   the directory containing the Eigen3 headers
# ``Eigen3_INCLUDE_DIRS``
#   the directory containing the Eigen3 headers
# ``Eigen3_LIBRARIES``
#   Eigen3 libraries to be linked
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# The following cache variables may also be set:
#
# ``Eigen3_INCLUDE_DIR``
#   the directory containing the Eigen3 headers
# ``Eigen3_LIBRARY``
#   the path to the Eigen3 library

find_path(Eigen3_INCLUDE_DIR signature_of_eigen3_matrix_library)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Eigen3
                                  REQUIRED_VARS Eigen3_INCLUDE_DIR
                                  VERSION_VAR Eigen3_VERSION_STRING)

if(Eigen3_FOUND)
  set(Eigen3_INCLUDE_DIRS "${Eigen3_INCLUDE_DIR}")

  if(NOT TARGET Eigen3::Eigen3)
    add_library(Eigen3::Eigen3 INTERFACE IMPORTED)
    if(Eigen3_INCLUDE_DIRS)
      set_target_properties(Eigen3::Eigen3 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Eigen3_INCLUDE_DIRS}")
    endif()
  endif()
endif()

mark_as_advanced(Eigen3_INCLUDE_DIR)
