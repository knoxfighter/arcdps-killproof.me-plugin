cmake_minimum_required(VERSION 4.2)

include(FetchContent)
FetchContent_Declare(my-vcpkg-triplets
		GIT_REPOSITORY "https://github.com/Zinn-o-Matics/my-vcpkg-triplets.git"
		GIT_TAG "master"
)
FetchContent_MakeAvailable(my-vcpkg-triplets)

list(APPEND VCPKG_OVERLAY_TRIPLETS "${my-vcpkg-triplets_SOURCE_DIR}")

project(killproof_me CXX)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

find_package(ArcdpsExtension CONFIG REQUIRED)
find_package(ArcdpsUnofficialExtras CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(modernIni CONFIG REQUIRED)

set(VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/VersionInfo.rc")
string(TIMESTAMP CURRENT_YEAR "%Y" UTC)
# add custom target to regenerate version info on every build
add_custom_target(VersionInfo ALL
		COMMAND ${CMAKE_COMMAND}
		-DVERSION_MAJOR=${VERSION_MAJOR}
		-DVERSION_MINOR=${VERSION_MINOR}
		-DVERSION_PATCH=${VERSION_PATCH}
		-DVERSION_REF=${VERSION_REF}
		-DVERSION_REF_STR=${VERSION_REF_STR}
		-DINTERNAL_NAME=d3d9_arcdps_killproof_me.dll
		-DORIGINAL_FILENAME=d3d9_arcdps_killproof_me.dll
		"-DPRODUCT_NAME=Arcdps Killproof.me plugin"
		"-DDESCRIPTION=Arcdps Killproof.me plugin"
		"-DCOPYRIGHT=Copyright (C) ${CURRENT_YEAR} knoxfighter"
		-P ${ArcdpsExtension_DIR}/generate-version.cmake
		BYPRODUCTS ${VERSION_FILE}
		COMMENT "Generating VersionInfo.rc"
		VERBATIM
)

add_library(${PROJECT_NAME} SHARED)

add_dependencies(${PROJECT_NAME} VersionInfo)

# Use -MT / -MTd runtime library
set_property(TARGET ${PROJECT_NAME} PROPERTY
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# rename output to legacy name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "d3d9_arcdps_killproof_me")

# add general sources
target_sources(${PROJECT_NAME}
		PUBLIC
		FILE_SET HEADERS
		FILES
		killproof_me/global.h
		killproof_me/Icons.h
		killproof_me/Killproofs.h
		killproof_me/KillproofUI.h
		killproof_me/KillproofUIKeyBindComponent.h
		killproof_me/KillproofUIPositioningComponent.h
		killproof_me/KillproofUITable.h
		killproof_me/Lang.h
		killproof_me/Player.h
		killproof_me/resource.h
		killproof_me/Settings.h
		killproof_me/SettingsUI.h
)

target_sources(${PROJECT_NAME}
		PRIVATE
		"${VERSION_FILE}"
		killproof_me/resource.h
		killproof_me/icons.rc
		killproof_me/dllmain.cpp
		killproof_me/global.cpp
		killproof_me/Killproofs.cpp
		killproof_me/KillproofUI.cpp
		killproof_me/KillproofUIKeyBindComponent.cpp
		killproof_me/KillproofUITable.cpp
		killproof_me/Lang.cpp
		killproof_me/Player.cpp
		killproof_me/Settings.cpp
		killproof_me/SettingsUI.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_link_libraries(${PROJECT_NAME} PUBLIC ArcdpsExtension::ArcdpsExtension)
target_link_libraries(${PROJECT_NAME} PUBLIC ArcdpsUnofficialExtras)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC magic_enum::magic_enum)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC CURL::libcurl)
target_link_libraries(${PROJECT_NAME} PUBLIC modernIni::modernIni)

if (DEFINED GAME_DIR AND NOT GAME_DIR STREQUAL "")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> "${GAME_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
			COMMAND ${CMAKE_COMMAND} -E $<IF:$<CONFIG:Debug,RelWithDebInfo>,copy_if_different,true> $<TARGET_PDB_FILE:${PROJECT_NAME}> "${GAME_DIR}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
			COMMENT "Copying plugin to ${GAME_DIR}..."
	)
endif ()
