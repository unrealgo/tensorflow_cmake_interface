cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(
	"tensorflow_cmake_interface"
	VERSION 0.2
)

option(TENSORFLOW_SHARED "Build shared library (required for GPU support)." ON)

function(GET_TENSORFLOW_VERSION)
	# get tf version from file ${TENSORFLOW_SOURCE_DIR}/tensorflow/core/public/version.h
	file(STRINGS "${TENSORFLOW_SOURCE_DIR}/tensorflow/core/public/version.h" TENSORFLOW_VERSION_HDR NEWLINE_CONSUME)
	string(REGEX MATCH "#define[ \t]+TF_MAJOR_VERSION+[ \t]+[0-9]" TF_MAJOR_DEF "${TENSORFLOW_VERSION_HDR}")
	string(REGEX MATCH "#define[ \t]+TF_MINOR_VERSION+[ \t]+[0-9]" TF_MINOR_DEF "${TENSORFLOW_VERSION_HDR}")
	string(REGEX MATCH "#define[ \t]+TF_PATCH_VERSION+[ \t]+[0-9]" TF_PATCH_DEF "${TENSORFLOW_VERSION_HDR}")
	string(REGEX REPLACE "#define[ \t]+TF_MAJOR_VERSION+[ \t]" "" TF_MAJOR ${TF_MAJOR_DEF})
	string(REGEX REPLACE "#define[ \t]+TF_MINOR_VERSION+[ \t]" "" TF_MINOR ${TF_MINOR_DEF})
	string(REGEX REPLACE "#define[ \t]+TF_PATCH_VERSION+[ \t]" "" TF_PATCH ${TF_PATCH_DEF})
	set(TF_VERSION ${TF_MAJOR}00${TF_MINOR}00 PARENT_SCOPE)
endfunction()

# -------------
# CMake Options
# -------------
add_definitions(-DSELECTIVE_REGISTRATION)
add_definitions(-DSUPPORT_SELECTIVE_REGISTRATION)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
include(CMakePackageConfigHelpers)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
set(INCLUDE_SUBDIR "include/tensorflow")
set(INSTALL_HEADER_PREFIX ${CMAKE_INSTALL_PREFIX}/${INCLUDE_SUBDIR})
set(CMAKECFG_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/TensorflowCC)

get_filename_component(TF_SOURCE_DIR_NAME ${TENSORFLOW_SOURCE_DIR} NAME [CACHE])
message(TF_SOURCE_DIR_NAME=${TF_SOURCE_DIR_NAME})
GET_TENSORFLOW_VERSION()
message(TF_VERSION=${TF_VERSION})
set(TF_CC_LIB libtensorflow_cc.so)

if (${TF_VERSION} GREATER 100300)
	set(TF_FRAMEWORK_LIB libtensorflow_framework.so)
	message("adding ${TF_FRAMEWORK_LIB}")
endif ()

message(TENSORFLOW_SOURCE_DIR=${TENSORFLOW_SOURCE_DIR})
message(CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR})
message(CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR})
message(CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR})
message(CMAKECFG_INSTALL_DIR=${CMAKECFG_INSTALL_DIR})
message(TENSORFLOW_SHARED=${TENSORFLOW_SHARED})
message(CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})


# --------------------------------------------------------
# Include External Projects for Shared
# --------------------------------------------------------
if (TENSORFLOW_SHARED)
	include(TensorflowShared)
endif ()

# ----------------------------------
# Define Shared Tensorflow Interface
# ----------------------------------
if (TENSORFLOW_SHARED)
	add_library(tensorflow_cc_shared INTERFACE)
	target_compile_options(
		tensorflow_cc_shared INTERFACE
		"-std=c++11"
	)
	add_dependencies(
		tensorflow_cc_shared
		tensorflow_shared
	)
	target_include_directories(
		tensorflow_cc_shared INTERFACE
		"${INSTALL_HEADER_PREFIX}"
		"${INSTALL_HEADER_PREFIX}/external/org_tensorflow"
		"${INSTALL_HEADER_PREFIX}/bazel-genfiles"
		"${INSTALL_HEADER_PREFIX}/external"
		"${INSTALL_HEADER_PREFIX}/external/eigen_archive"
		"${INSTALL_HEADER_PREFIX}/external/gemmlowp"
	)
	# if (${TF_VERSION} GREATER 100300 AND ${TF_VERSION} LESS 100500)
	if (${TF_VERSION} GREATER 100300)
		target_include_directories(
			tensorflow_cc_shared INTERFACE
			"${INSTALL_HEADER_PREFIX}/external/nsync/public"
			"${INSTALL_HEADER_PREFIX}/bazel-${TF_SOURCE_DIR_NAME}/external/protobuf_archive/src/"
		)
	endif ()

	target_link_libraries(
		tensorflow_cc_shared INTERFACE
		"${CMAKE_INSTALL_PREFIX}/lib/tensorflow_cc/${TF_CC_LIB}"
		dl pthread
	)

	if (${TF_VERSION} GREATER 100300)
		target_link_libraries(
			tensorflow_cc_shared INTERFACE
			"${CMAKE_INSTALL_PREFIX}/lib/tensorflow_cc/${TF_FRAMEWORK_LIB}"
		)
	endif ()
	target_link_libraries(
		tensorflow_cc_shared INTERFACE
		"${CMAKE_INSTALL_PREFIX}/lib/tensorflow_cc/libprotobuf.a"
	)
endif ()

# ----------------------------------------
# Configure CMake Config and Version Files
# ----------------------------------------
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/TensorflowCCConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/TensorflowCCConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/TensorflowCCConfig.cmake"
	INSTALL_DESTINATION "${CMAKECFG_INSTALL_DIR}"
	NO_SET_AND_CHECK_MACRO # TensorflowCC only uses interface libraries
	NO_CHECK_REQUIRED_COMPONENTS_MACRO # TensorflowCC does not have components
)

# -------
# Install
# -------
# install all header files
install(
	DIRECTORY "${TENSORFLOW_SOURCE_DIR}/"
	DESTINATION ${INCLUDE_SUBDIR}
	FILES_MATCHING PATTERN "*.h"
)

install(
	DIRECTORY "${TENSORFLOW_SOURCE_DIR}/bazel-${TF_SOURCE_DIR_NAME}/external/protobuf/src/"
	DESTINATION ${INCLUDE_SUBDIR}/external
	OPTIONAL
	FILES_MATCHING PATTERN "*.h"

)

install(
	DIRECTORY "${TENSORFLOW_SOURCE_DIR}/bazel-${TF_SOURCE_DIR_NAME}/external/"
	DESTINATION ${INCLUDE_SUBDIR}/external
	OPTIONAL
)
# install all files from third_party folder (e.g., Eigen/Tensor)
install(
	DIRECTORY "${TENSORFLOW_SOURCE_DIR}/third_party/"
	DESTINATION ${INCLUDE_SUBDIR}/third_party
)

# install static libprotobuf
install(
	FILES "${TENSORFLOW_SOURCE_DIR}/bazel-${TF_SOURCE_DIR_NAME}/bazel-out/host/bin/external/protobuf_archive/libprotobuf.a"
				"${TENSORFLOW_SOURCE_DIR}/bazel-out/host/bin/external/protobuf/libprotobuf.a"
	DESTINATION lib/tensorflow_cc
	OPTIONAL
)

install(
	PROGRAMS "${TENSORFLOW_SOURCE_DIR}/bazel-${TF_SOURCE_DIR_NAME}/bazel-out/host/bin/external/protobuf_archive/protoc"
	DESTINATION bin/
	OPTIONAL
)

# shared library specific
if (TENSORFLOW_SHARED)
	install(
		FILES "${TENSORFLOW_SOURCE_DIR}/bazel-bin/tensorflow/${TF_CC_LIB}"
		DESTINATION lib/tensorflow_cc
	)

	if (${TF_VERSION} GREATER 100300)
		install(
			FILES "${TENSORFLOW_SOURCE_DIR}/bazel-bin/tensorflow/${TF_FRAMEWORK_LIB}"
			DESTINATION lib/tensorflow_cc
		)
	endif ()
endif ()

# --------------------------
# Install CMake targets file
# --------------------------
if (TENSORFLOW_SHARED)
	set_target_properties(
		tensorflow_cc_shared PROPERTIES EXPORT_NAME Shared
	)
	install(
		TARGETS tensorflow_cc_shared
		EXPORT TensorflowCCSharedTargets
	)
	install(
		EXPORT TensorflowCCSharedTargets
		FILE TensorflowCCSharedTargets.cmake
		NAMESPACE TensorflowCC::
		DESTINATION "${CMAKECFG_INSTALL_DIR}"
	)
endif ()

# install config and version files
install(
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/TensorflowCCConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/TensorflowCCConfigVersion.cmake"
	DESTINATION "${CMAKECFG_INSTALL_DIR}"
)