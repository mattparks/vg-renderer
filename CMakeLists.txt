cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)
project(vg-renderer VERSION 0.1.0 LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build Shared Libraries" ON)
option(VG_RENDERER_BUILD_BGFX "Should vg-renderer download and build bgfx.cmake" ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if(VG_RENDERER_BUILD_BGFX)
	include(FetchContent)
	FetchContent_Declare(
	        bgfx
	        GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
	        )

	FetchContent_GetProperties(bgfx)

	if(NOT bgfx_POPULATED)
	    FetchContent_Populate(bgfx)
        set(BGFX_BUILD_EXAMPLES OFF CACHE INTERNAL "Build bgfx examples.")
        set(BGFX_INSTALL_EXAMPLES OFF CACHE INTERNAL "Install examples and their runtimes.")
        add_subdirectory(${bgfx_SOURCE_DIR} ${bgfx_BINARY_DIR})
        add_executable(bgfx::shaderc ALIAS shaderc)
        set(BGFX_SHADER_INCLUDE_PATH ${bgfx_SOURCE_DIR}/bgfx/src)
        include(${bgfx_SOURCE_DIR}/cmake/bgfxToolUtils.cmake)
	endif()
endif()

file(GLOB_RECURSE _vg_renderer_headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/**.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/**.inl
        )
file(GLOB_RECURSE _vg_renderer_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp
        )
file(GLOB_RECURSE _vg_renderer_fs_shaders
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/fs_*.sc
        )
file(GLOB_RECURSE _vg_renderer_vs_shaders
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vs_*.sc
        )
bgfx_compile_shader_to_header(
        TYPE FRAGMENT
        SHADERS ${_vg_renderer_fs_shaders}
        VARYING_DEF ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/varying.def.sc
        OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/src
        )
bgfx_compile_shader_to_header(
        TYPE VERTEX
        SHADERS ${_vg_renderer_vs_shaders}
        VARYING_DEF ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/varying.def.sc
        OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/src
        )

add_library(vg-renderer STATIC
        ${_vg_renderer_headers}
        ${_vg_renderer_sources}
        ${_vg_renderer_fs_shaders}
        ${_vg_renderer_vs_shaders}
        )
target_include_directories(vg-renderer
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/src>
        )
target_link_libraries(vg-renderer PUBLIC
        bx bgfx
        )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "" FILES ${_vg_renderer_headers})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "" FILES ${_vg_renderer_sources})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "" FILES ${_vg_renderer_fs_shaders})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "" FILES ${_vg_renderer_vs_shaders})
