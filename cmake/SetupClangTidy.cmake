# Distributed under the MIT License.
# See LICENSE.txt for details.

# Remove the checks because:
# -llvm-header-guard: We use pragma once instead of include guards
# -google-runtime-int: specifying int32_t and int64_t instead of just int
# -misc-noexcept-move-constructor: false positives
# -misc-unconventional-assign-operator: false positives
# -cppcoreguidelines-c-copy-assignment-signature: false positives
#
# Notes:
# misc-move-const-arg: we keep this check because even though this gives
#                      a lot of annoying warnings about moving trivially
#                      copyable types, it warns about moving const objects,
#                      which can have severe performance impacts.
set(CLANG_TIDY_IGNORE_CHECKS "*,-llvm-header-guard,-google-runtime-int,-misc-noexcept-move-constructor,-misc-unconventional-assign-operator,-cppcoreguidelines-c-copy-assignment-signature")

if(NOT CMAKE_CXX_CLANG_TIDY AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(
      REGEX MATCH "^[0-9]+.[0-9]+" LLVM_VERSION
      "${CMAKE_CXX_COMPILER_VERSION}"
  )
  find_program(
      CLANG_TIDY_BIN
      NAMES "clang-tidy-${LLVM_VERSION}" "clang-tidy"
      HINTS ${COMPILER_PATH}
      )
elseif(CMAKE_CXX_CLANG_TIDY)
  set(CLANG_TIDY_BIN "${CMAKE_CXX_CLANG_TIDY}")
endif()

if (CLANG_TIDY_BIN)
  configure_file(
    ${CMAKE_SOURCE_DIR}/tools/ClangTidyAll.sh
    ${CMAKE_BINARY_DIR}/ClangTidyAll.sh
    @ONLY IMMEDIATE
    )
  add_custom_target(
      clang-tidy
      COMMAND
      ${CLANG_TIDY_BIN}
      -header-filter=${CMAKE_SOURCE_DIR}
      -checks=${CLANG_TIDY_IGNORE_CHECKS}
      -p ${CMAKE_BINARY_DIR}
      \${FILE}
  )
  add_dependencies(
      clang-tidy
      module_RunTests
  )
  set_target_properties(
      clang-tidy
      PROPERTIES EXCLUDE_FROM_ALL TRUE
  )
  add_custom_target(
      clang-tidy-all
      COMMAND ${CMAKE_BINARY_DIR}/ClangTidyAll.sh
  )
  set_target_properties(
      clang-tidy-all
      PROPERTIES EXCLUDE_FROM_ALL TRUE
  )
  add_dependencies(
      clang-tidy-all
      module_RunTests
  )
endif()
