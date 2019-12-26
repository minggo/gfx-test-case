set(TARGET_NAME GFXTestWin)

message(STATUS "Target: ${TARGET_NAME}...")
set(CMAKE_MODULE_PATH ${COCOS_EXTERNAL_PATH}/cmake)
include(CocosBuildSet)
# ---------------------------------------------
# set cocos platform, base, math, external files
set(CC_PLATFORM_SOURCES
    ${COCOS_SRC_PATH}/platform/CCApplication.h
    ${COCOS_SRC_PATH}/platform/CCDevice.h
    ${COCOS_SRC_PATH}/platform/CCFileUtils.h
    ${COCOS_SRC_PATH}/platform/CCGL.h
    ${COCOS_SRC_PATH}/platform/CCImage.h
    ${COCOS_SRC_PATH}/platform/CCPlatformConfig.h
    ${COCOS_SRC_PATH}/platform/CCPlatformDefine.h
    ${COCOS_SRC_PATH}/platform/CCSAXParser.h
    ${COCOS_SRC_PATH}/platform/CCStdC.h

    ${COCOS_SRC_PATH}/platform/CCFileUtils.cpp
    ${COCOS_SRC_PATH}/platform/CCImage.cpp
    ${COCOS_SRC_PATH}/platform/CCSAXParser.cpp
)
if(COCOS_PLATFORM_WIN32)
    list(APPEND CC_PLATFORM_SOURCES
        ${COCOS_SRC_PATH}/platform/win32/CCFileUtils-win32.h
        ${COCOS_SRC_PATH}/platform/win32/CCPlatformDefine-win32.h
        ${COCOS_SRC_PATH}/platform/win32/CCUtils-win32.h
       
        ${COCOS_SRC_PATH}/platform/win32/CCDevice-win32.cpp
        ${COCOS_SRC_PATH}/platform/win32/CCFileUtils-win32.cpp
        ${COCOS_SRC_PATH}/platform/win32/CCUtils-win32.cpp
    )
endif()

set(CC_BASE_HEADERS 
    ${COCOS_SRC_PATH}/base/base64.h
    ${COCOS_SRC_PATH}/base/CCAutoreleasePool.h
    ${COCOS_SRC_PATH}/base/ccCArray.h
    ${COCOS_SRC_PATH}/base/ccConfig.h
    ${COCOS_SRC_PATH}/base/CCConfiguration.h
    ${COCOS_SRC_PATH}/base/CCData.h
    # ${COCOS_SRC_PATH}/base/CCGLUtils.h
    ${COCOS_SRC_PATH}/base/CCLog.h
    ${COCOS_SRC_PATH}/base/ccMacros.h
    ${COCOS_SRC_PATH}/base/CCMap.h
    ${COCOS_SRC_PATH}/base/ccRandom.h
    ${COCOS_SRC_PATH}/base/CCRef.h
    ${COCOS_SRC_PATH}/base/CCRefPtr.h
    # ${COCOS_SRC_PATH}/base/CCRenderTexture.h
    # ${COCOS_SRC_PATH}/base/CCScheduler.h
    # ${COCOS_SRC_PATH}/base/CCThreadPool.h
    ${COCOS_SRC_PATH}/base/ccTypes.h
    ${COCOS_SRC_PATH}/base/ccUTF8.h
    ${COCOS_SRC_PATH}/base/ccUtils.h
    ${COCOS_SRC_PATH}/base/CCValue.h
    ${COCOS_SRC_PATH}/base/CCVector.h
    ${COCOS_SRC_PATH}/base/etc1.h
    ${COCOS_SRC_PATH}/base/etc2.h
    ${COCOS_SRC_PATH}/base/pvr.h
    ${COCOS_SRC_PATH}/base/TGAlib.h
    ${COCOS_SRC_PATH}/base/uthash.h
    ${COCOS_SRC_PATH}/base/utlist.h
    ${COCOS_SRC_PATH}/base/ZipUtils.h
)

set(CC_BASE_SOURCES
    ${COCOS_SRC_PATH}/base/base64.cpp
    ${COCOS_SRC_PATH}/base/CCAutoreleasePool.cpp
    ${COCOS_SRC_PATH}/base/ccCArray.cpp
    ${COCOS_SRC_PATH}/base/CCConfiguration.cpp
    ${COCOS_SRC_PATH}/base/CCData.cpp
    # ${COCOS_SRC_PATH}/base/CCGLUtils.cpp
    ${COCOS_SRC_PATH}/base/CCLog.cpp
    ${COCOS_SRC_PATH}/base/ccRandom.cpp
    ${COCOS_SRC_PATH}/base/CCRef.cpp
    # ${COCOS_SRC_PATH}/base/CCRenderTexture.cpp
    # ${COCOS_SRC_PATH}/base/CCScheduler.cpp
    # ${COCOS_SRC_PATH}/base/CCThreadPool.cpp
    ${COCOS_SRC_PATH}/base/ccTypes.cpp
    ${COCOS_SRC_PATH}/base/ccUTF8.cpp
    ${COCOS_SRC_PATH}/base/ccUtils.cpp
    ${COCOS_SRC_PATH}/base/CCValue.cpp
    ${COCOS_SRC_PATH}/base/csscolorparser.cpp
    ${COCOS_SRC_PATH}/base/etc1.cpp
    ${COCOS_SRC_PATH}/base/etc2.cpp
    ${COCOS_SRC_PATH}/base/pvr.cpp
    ${COCOS_SRC_PATH}/base/TGAlib.cpp
    ${COCOS_SRC_PATH}/base/ZipUtils.cpp
)

set(CC_MATH_HEADERS
    ${COCOS_SRC_PATH}/math/CCGeometry.h
    ${COCOS_SRC_PATH}/math/CCMath.h
    ${COCOS_SRC_PATH}/math/CCMathBase.h
    ${COCOS_SRC_PATH}/math/CCVertex.h
    ${COCOS_SRC_PATH}/math/Mat4.h
    ${COCOS_SRC_PATH}/math/MathUtil.h
    ${COCOS_SRC_PATH}/math/Quaternion.h
    ${COCOS_SRC_PATH}/math/Vec2.h
    ${COCOS_SRC_PATH}/math/Vec3.h
    ${COCOS_SRC_PATH}/math/Vec4.h
)

set(CC_MATH_SOURCES
    ${COCOS_SRC_PATH}/math/CCGeometry.cpp
    ${COCOS_SRC_PATH}/math/CCVertex.cpp
    ${COCOS_SRC_PATH}/math/Mat4.cpp
    ${COCOS_SRC_PATH}/math/MathUtil.cpp
    ${COCOS_SRC_PATH}/math/Quaternion.cpp
    ${COCOS_SRC_PATH}/math/Vec2.cpp
    ${COCOS_SRC_PATH}/math/Vec3.cpp
    ${COCOS_SRC_PATH}/math/Vec4.cpp
)
add_definitions("-DCC_STATIC")
include(${COCOS_EXTERNAL_PATH}/CMakeLists.txt)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/../Resources"
    )
if(APPLE OR VS)
    cocos_mark_multi_resources(cc_common_res RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# ---------------------------------------------------------------------
# set include files

include(${PROJECT_SOURCE_DIR}/tests/CMakeLists.txt)

set(INCLUDE_FILES
  ${GFX_EXTERNAL_PATH}/khronos
  ${COCOS_SRC_PATH}/renderer/core
  ${COCOS_SRC_PATH}/renderer/gfx-gles2
  ${COCOS_SRC_PATH}/renderer/gfx-gles3
  ./GFXTest
)

# ---------------------------------------------------------------------

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp *.cc)
file(GLOB_RECURSE SOURCE_C_FILES *.c)

set(ALL_FILES 
    ${HEADER_FILES} 
    ${SOURCE_CPP_FILES} 
    ${SOURCE_C_FILES} 
    ${GFX_TESTCASE_HEADER} 
    ${GFX_TESTCASE_SOURCE}
    ${CC_PLATFORM_SOURCES}
    ${CC_EXTERNAL_SROUCES}
    ${CC_BASE_HEADERS}
    ${CC_BASE_SOURCES}
    ${CC_MATH_HEADERS}
    ${CC_MATH_SOURCES}
    ${cc_common_res}
    ${COCOS_SRC_PATH}/cocos2d.h
    ${COCOS_SRC_PATH}/cocos2d.cpp
)

if(COCOS_UNICODE)
	add_definitions("-DUNICODE -D_UNICODE")
endif()

add_executable(${TARGET_NAME} WIN32 ${ALL_FILES})

if(COCOS_CPU_X64)
  set(PVRSDK_LIB_DIR ${GFX_EXTERNAL_PATH}/pvrsdk/lib/Windows_x86_64)
else()
  set(PVRSDK_LIB_DIR ${GFX_EXTERNAL_PATH}/pvrsdk/lib/Windows_x86_32)
endif()

# Gather list of all .dll files
file(GLOB PVRDLLS ${PVRSDK_LIB_DIR}/*.dll)
if(COCOS_PLATFORM_WIN32)
  list(APPEND PVRDLLS ${COCOS_EXTERNAL_PATH}/win32/libs/zlib1.dll)
endif()

foreach(PVRDLL ${PVRDLLS})
  add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E
                         copy ${PVRDLL} $<TARGET_FILE_DIR:${TARGET_NAME}>)
endforeach()

target_include_directories(${TARGET_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/win 
    ${PROJECT_SOURCE_DIR}
    ${INCLUDE_FILES}
    ${COCOS_EXTERNAL_PATH}/sources
    ${CC_EXTERNAL_INCLUDES}
    ${COCOS_SRC_PATH}/platform
)

target_link_libraries(${TARGET_NAME} 
  Core 
  GFXGLES2 
  GFXGLES3
  ${CC_EXTERNAL_LIBS}
) 

include(CocosBuildHelpers)
if(LINUX OR WINDOWS)
    set(COCOS2DX_ROOT_PATH ${COCOS_EXTERNAL_PATH})
    cocos_def_copy_resource_target(${TARGET_NAME})
    cocos_copy_target_res(${TARGET_NAME} LINK_TO "${COCOS_BUILD_PATH}/${CMAKE_CFG_INTDIR}/Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

source_group(TREE ${COCOS_SRC_PATH}/platform PREFIX "Header Files/platform" FILES ${CC_PLATFORM_SOURCES})
source_group(TREE ${COCOS_SRC_PATH}/base PREFIX "Header Files/base" FILES ${CC_BASE_HEADERS})
source_group(TREE ${COCOS_SRC_PATH}/base PREFIX "Source Files/base" FILES ${CC_BASE_SOURCES})
source_group(TREE ${COCOS_SRC_PATH}/math PREFIX "Header Files/math" FILES ${CC_MATH_HEADERS})
source_group(TREE ${COCOS_SRC_PATH}/math PREFIX "Source Files/math" FILES ${CC_MATH_SOURCES})
source_group(TREE ${COCOS_EXTERNAL_PATH}/sources PREFIX "Header Files/external" FILES ${CC_EXTERNAL_SROUCES})

message(STATUS "${TARGET_NAME} configuration completed.") 
