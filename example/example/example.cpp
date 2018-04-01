#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>
#include <tensorflow/cc/framework/scope.h>
#include <tensorflow/c/c_api_internal.h>
#include <tensorflow/core/public/version.h>
#include <google/tensorflow/tensorflow/cc/ops/math_ops.h>
#include <google/tensorflow/tensorflow/cc/ops/array_ops.h>

using namespace std;
using namespace tensorflow;

static void Deallocator(void *data, size_t, void *arg) {
  tensorflow::cpu_allocator()->DeallocateRaw(data);
  *reinterpret_cast<bool *>(arg) = true;
}

TF_Tensor* Feature2TF_Tensor(float feature[], int64_t dims[], int nDims, TF_DataType type) {
  size_t len = 1;
  for (int i = 0; i < nDims; i++)
    len *= dims[i];
  len *= sizeof(float);
  bool deallocator_called = false;
  TF_Tensor *ts = TF_NewTensor(type, dims, nDims, feature, len, &Deallocator, &deallocator_called);
  return ts;
}

int main() {
  Session *session;
  Status status = NewSession(SessionOptions(), &session);
  if (!status.ok()) {
    cout << status.ToString() << "\n";
    return 1;
  }

  cout << "Session successfully created.\n";

  auto root = tensorflow::Scope::NewRootScope();
  cout << root.status() << std::endl;
  cout << GOOGLE_PROTOBUF_MIN_PROTOC_VERSION << std::endl;

  auto* feature = new float[1000];
  int64_t dims[] = {10, 10, 10};
  int nDims = 3;
  TF_DataType type = TF_FLOAT;
  TF_Tensor *tftensor = Feature2TF_Tensor(feature, dims, nDims, type);

  std::string version = std::to_string(TF_MAJOR_VERSION) + "." + std::to_string(TF_MINOR_VERSION) + "." + std::to_string(TF_PATCH_VERSION);
  std::cout << "tf version:" << version << std::endl;
  std::cout << "gcc compiler:" << tf_compiler_version() << std::endl;
  std::cout << "git:" << tf_git_version() << std::endl;




  gtl::InlinedVector<int64, 24> starts;
  std::cout << starts.capacity() << std::endl;
  starts.emplace_back(1);
  starts.emplace_back(2);
  starts.emplace_back(3);
  starts.emplace_back(4);
  starts.emplace_back(5);
  starts.emplace_back(6);
  starts.emplace_back(7);
  std::cout << starts.capacity() << std::endl;
  for (int64 val : starts)
    std::cout << val << " ";
  std::cout << std::endl;
  std::cout << "sizeof inlined vector:" << starts.size() << std::endl;

  CHECK_GE(starts.capacity(), 20);

  Microseconds microseconds;
  microseconds = 200;
  std::cout << sizeof(microseconds) << " " << microseconds << std::endl;
}