include(ExternalProject)

ExternalProject_Add(
  tensorflow_shared
  TMP_DIR "/tmp"
  STAMP_DIR "tensorflow-stamp"
  SOURCE_DIR ${TENSORFLOW_SOURCE_DIR}
  BUILD_IN_SOURCE 1
  DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  # CONFIGURE_COMMAND bazel clean
  CONFIGURE_COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/cmake/build_tensorflow.sh" .
            COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_links.sh" .
            COMMAND ./build_tensorflow.sh
            COMMAND ./copy_links.sh .
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)