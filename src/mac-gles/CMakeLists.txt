macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
    set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY}
                 ${XCODE_VALUE})
endmacro (set_xcode_property)

message(STATUS "App: ${APP_NAME}...")

# ---------------------------------------------------------------------
# set include files

set(INCLUDE_FILES
  ${GFX_EXTERNAL_PATH}/khronos
  ${GFX_EXTERNAL_PATH}/boost
  ${GFX_EXTERNAL_PATH}/concurrentqueue
  ${GFX_EXTERNAL_PATH}/taskflow
  ${GFX_EXTERNAL_PATH}/acl/includes
  ${GFX_EXTERNAL_PATH}/rtm/includes
  ${COCOS_SRC_PATH}/renderer/core
  ${COCOS_SRC_PATH}/renderer/gfx-metal
  ${COCOS_SRC_PATH}/renderer/gfx-gles3
  ./GFXTest
)

include_directories( ${INCLUDE_FILES} )

# ---------------------------------------------------------------------

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp *.cc)
file(GLOB_RECURSE SOURCE_C_FILES *.c)
file(GLOB_RECURSE SOURCE_MM_FILES *.m *.mm)

set(APP_UI_RES
    ${CMAKE_CURRENT_LIST_DIR}/../Resources/uv_checker_01.jpg
    ${CMAKE_CURRENT_LIST_DIR}/../Resources/uv_checker_02.jpg
    ${CMAKE_CURRENT_LIST_DIR}/../Resources/stencil.jpg
    ${CMAKE_CURRENT_LIST_DIR}/Assets.xcassets/Contents.json
)

set(ALL_FILES
    ${HEADER_FILES}
    ${SOURCE_CPP_FILES}
    ${SOURCE_C_FILES}
    ${SOURCE_MM_FILES}
    ${GFX_TESTCASE_HEADER}
    ${GFX_TESTCASE_SOURCE}
    ${APP_UI_RES}
    ${CC_EXTERNAL_SOURCES}
    ${cc_common_res}
    ${COCOS_SRC_PATH}/platform/Image.h
    )

if(COCOS_UNICODE)
	add_definitions("-DUNICODE -D_UNICODE")
endif()
add_definitions("-DCC_USE_GLES3")
add_definitions("-DCC_USE_GLES2")

add_executable(${APP_NAME} MACOSX_BUNDLE ${ALL_FILES})

set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/Info.plist")
set_xcode_property(${APP_NAME} PRODUCT_BUNDLE_IDENTIFIER ${APP_NAME})

# Locate system libraries on macOS
find_library(APPKIT_LIBRARY AppKit)
list(APPEND PLATFORM_SPECIFIC_LIBS
     ${APPKIT_LIBRARY}
     ${GFX_EXTERNAL_PATH}/pvrsdk/lib/OSX_x86/libEGL.dylib
     ${GFX_EXTERNAL_PATH}/pvrsdk/lib/OSX_x86/libGLESv2.dylib
)

target_link_libraries(${APP_NAME}
    ${PLATFORM_SPECIFIC_LIBS}
    ${ENGINE_BASE_LIBS}
    GFXGLESCommon
    GFXGLES2
    GFXGLES3
    ${CC_EXTERNAL_LIBS}
    z
)

target_include_directories(${APP_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${COCOS_SRC_PATH}/platform
    ${COCOS_EXTERNAL_PATH}/sources
    ${CC_EXTERNAL_INCLUDES}
    ${CC_EXTERNAL_INCLUDES}/v8
)

if(MACOSX)
    target_include_directories(${APP_NAME} PRIVATE
        ##FIXME: bad dependency
        ${COCOS_SRC_PATH}/platform/ios
    )
endif()

set(PVRSDK_LIB_DIR ${GFX_EXTERNAL_PATH}/pvrsdk/lib/OSX_x86)

# Gather list of all .dylib files
file(GLOB PVRDLLS ${PVRSDK_LIB_DIR}/*.dylib)
foreach(PVRDLL ${PVRDLLS})
  add_custom_command(TARGET ${APP_NAME} PRE_BUILD
                     COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks
                     COMMAND ${CMAKE_COMMAND} -E
                         copy ${PVRDLL} $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks/)
endforeach()

source_group(TREE ${COCOS_SRC_PATH}/base PREFIX "Header Files/base" FILES ${CC_BASE_HEADERS})
source_group(TREE ${COCOS_SRC_PATH}/base PREFIX "Source Files/base" FILES ${CC_BASE_SOURCES})
source_group(TREE ${COCOS_SRC_PATH}/math PREFIX "Header Files/math" FILES ${CC_MATH_HEADERS})
source_group(TREE ${COCOS_SRC_PATH}/math PREFIX "Source Files/math" FILES ${CC_MATH_SOURCES})
source_group(TREE ${COCOS_EXTERNAL_PATH}/sources PREFIX "Header Files/external" FILES ${CC_EXTERNAL_SOURCES})

# setup default flags
target_compile_definitions(${APP_NAME} PUBLIC
    $<$<NOT:$<BOOL:${USE_VIDEO}>>:USE_VIDEO=0>
    $<$<NOT:$<BOOL:${USE_WEB_VIEW}>>:USE_WEB_VIEW=0>
    $<$<NOT:$<BOOL:${USE_AUDIO}>>:USE_AUDIO=0>
    $<$<NOT:$<BOOL:${USE_SOCKET}>>:USE_SOCKET=0>
    $<$<NOT:$<BOOL:${USE_MIDDLEWARE}>>:USE_MIDDLEWARE=0>
    $<$<NOT:$<BOOL:${USE_SPINE}>>:USE_SPINE=0>
    $<$<NOT:$<BOOL:${USE_DRAGONBONES}>>:USE_DRAGONBONES=0>
    $<$<NOT:$<BOOL:${USE_TIFF}>>:CC_USE_TIFF=0>
    $<$<BOOL:${USE_GFX_RENDERER}>:USE_GFX_RENDERER=1>
    $<$<NOT:$<BOOL:${USE_V8_DEBUGGER}>>:USE_V8_DEBUGGER=0>
)

message(STATUS "${APP_NAME} configuration completed.")
