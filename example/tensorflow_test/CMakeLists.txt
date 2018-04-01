set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(TF_SRC_DIR "${YOUR_TENSORFLOW_SOURCE_DIR")

function(addTest)
	cmake_parse_arguments(_AT "" "TARGET" "SOURCES;LIBS;DEPENDS" ${ARGN})
	add_executable(${_AT_TARGET} ${_AT_SOURCES})

	if (_AT_DEPENDS)
		add_dependencies(${_AT_TARGET} ${_AT_DEPENDS} googletest)
	endif()

	target_link_libraries(${_AT_TARGET} ${_AT_LIBS})
endfunction()


set(tf_test_libs
	gtest_main
	gtest.a
	TensorflowCC::Shared)


set(SRC_FILES quantize_training_test.cc quantize_training.cc testlib.cc)
addTest(
	TARGET quantize_training_test
	SOURCES ${SRC_FILES}
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

set(SRC_FILES
	gtest_0.cc
	graph_runner_test.cc
	function_testlib.cc
	tensor_testutil.cc
	array_grad_test.cc
	)
addTest(
	TARGET unittestmain
	SOURCES ${SRC_FILES}
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

set(SRC_FILES
	algorithm_test.cc
	)
addTest(
	TARGET algorithm_test
	SOURCES ${SRC_FILES}
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


set(SRC_FILES
	kernel_def_builder_test.cc
	)
addTest(
	TARGET kernel_def_builder_test
	SOURCES ${SRC_FILES}
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


set(SRC_FILES
	optimizer_cse_test.cc
	testlib.cc
	test_benchmark.cc
	${TF_SRC_DIR}/tensorflow/core/util/reporter.cc
	)
addTest(
	TARGET optimizer_cse_test
	SOURCES ${SRC_FILES}
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


addTest(
	TARGET allocator_test
	SOURCES ${TF_SRC_DIR}/tensorflow/core/framework/allocator_test.cc
					${TF_SRC_DIR}/tensorflow/core/util/reporter.cc
					${TF_SRC_DIR}/tensorflow/core/platform/default/test_benchmark.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET graph_runner_test
	SOURCES graph_runner_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET bfloat16_test
	SOURCES ${TF_SRC_DIR}/tensorflow/core/framework/bfloat16_test.cc
					${TF_SRC_DIR}/tensorflow/core/platform/default/test_benchmark.cc
					${TF_SRC_DIR}/tensorflow/core/util/reporter.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


addTest(
	TARGET cancellation_test-local
	SOURCES cancellation_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


addTest(
	TARGET closure_test
	SOURCES closure_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET math_test
	SOURCES math_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET general_tf_test
	SOURCES general_tf_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET inlinedVector
	SOURCES inlinedVector.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET session_test
	SOURCES ${TF_SRC_DIR}/tensorflow/core/common_runtime/session_test.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)

addTest(
	TARGET typesTest
	SOURCES typesTest.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


addTest(
	TARGET tftypesTest
	SOURCES tftypesTest.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)


addTest(
	TARGET adjust_contrast_op_test
	SOURCES ${TF_SRC_DIR}/tensorflow/core/kernels/adjust_contrast_op_test.cc
					${TF_SRC_DIR}/tensorflow/core/framework/fake_input.cc
					${TF_SRC_DIR}/tensorflow/core/kernels/ops_testutil.cc
	LIBS ${tf_test_libs}
	DEPENDS googletest
)