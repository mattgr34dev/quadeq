cmake_minimum_required(VERSION 3.14)
project(quadeq
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# QUADEQ_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(QUADEQ_BUILD_TESTS "Build quadeq tests" OFF)
option(QUADEQ_BUILD_EXAMPLES "Build quadeq examples" OFF)
option(QUADEQ_BUILD_DOCS "Build quadeq documentation" OFF)
option(QUADEQ_INSTALL "Generate target for installing quadeq" ${is_top_level})
set_if_undefined(QUADEQ_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/quadeq" CACHE STRING
    "Install path for quadeq package-related CMake files")

if(DEFINED QUADEQ_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${QUADEQ_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(quadeq) # initialized below
add_library(quadeq::quadeq ALIAS quadeq)

#----------------------------------------------------------------------------------------------------------------------
# quadeq dependencies
#----------------------------------------------------------------------------------------------------------------------

# Search for your dependencies here

#----------------------------------------------------------------------------------------------------------------------
# quadeq sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(quadeq EXPORT_FILE_NAME include/quadeq/${export_file_name})

set(sources
    include/quadeq/export.h
    include/quadeq/quadeq.h
    src/quadeq.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# quadeq target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(quadeq PRIVATE ${sources})
target_compile_definitions(quadeq PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:QUADEQ_STATIC_DEFINE>")

target_include_directories(quadeq
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(quadeq PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(QUADEQ_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/quadeq-config.cmake.in quadeq-config.cmake
        INSTALL_DESTINATION "${QUADEQ_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(quadeq-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS quadeq EXPORT quadeq_export
        RUNTIME COMPONENT quadeq
        LIBRARY COMPONENT quadeq NAMELINK_COMPONENT quadeq-dev
        ARCHIVE COMPONENT quadeq-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT quadeq-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/quadeq/${export_file_name}"
        COMPONENT quadeq-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/quadeq")

    set(targets_file "quadeq-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "quadeq-static-targets.cmake")
    endif()

    install(EXPORT quadeq_export
        COMPONENT quadeq-dev
        FILE "${targets_file}"
        DESTINATION "${QUADEQ_INSTALL_CMAKEDIR}"
        NAMESPACE quadeq::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/quadeq-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/quadeq-config-version.cmake"
        COMPONENT quadeq-dev
        DESTINATION "${QUADEQ_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:quadeq>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:quadeq>/$<TARGET_FILE_PREFIX:quadeq>$<TARGET_FILE_BASE_NAME:quadeq>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT quadeq-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(QUADEQ_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(QUADEQ_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(QUADEQ_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
