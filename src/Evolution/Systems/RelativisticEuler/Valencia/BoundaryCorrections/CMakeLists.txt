# Distributed under the MIT License.
# See LICENSE.txt for details.

spectre_target_sources(
  Valencia
  PRIVATE
  RegisterDerived.cpp
  Rusanov.cpp
  )

spectre_target_headers(
  Valencia
  INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/src
  HEADERS
  BoundaryCorrection.hpp
  Factory.hpp
  RegisterDerived.hpp
  Rusanov.hpp
  )
