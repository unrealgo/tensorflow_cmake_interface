//
// Created by levin on 18-3-8.
//

#ifndef TENSORFLOWCC_EXAMPLE_TYPES_H
#define TENSORFLOWCC_EXAMPLE_TYPES_H

#include "tensorflow/core/framework/numeric_types.h"
#include "tensorflow/core/framework/types.pb.h"
#include "tensorflow/core/platform/logging.h"

using namespace tensorflow;


enum { kDataTypeRefOffset = 100 };
inline bool IsRefType(DataType dtype) {
  return dtype > static_cast<DataType>(kDataTypeRefOffset);
}
inline DataType MakeRefType(DataType dtype) {
  DCHECK(!IsRefType(dtype));
  return static_cast<DataType>(dtype + kDataTypeRefOffset);
}
inline DataType RemoveRefType(DataType dtype) {
  DCHECK(IsRefType(dtype));
  return static_cast<DataType>(dtype - kDataTypeRefOffset);
}
inline DataType BaseType(DataType dtype) {
  return IsRefType(dtype) ? RemoveRefType(dtype) : dtype;
}

// Returns true if the actual type is the same as or ref of the expected type.
inline bool TypesCompatible(DataType expected, DataType actual) {
  return expected == actual || expected == BaseType(actual);
}

template <class T>
struct IsValidDataType;

// DataTypeToEnum<T>::v() and DataTypeToEnum<T>::value are the DataType
// constants for T, e.g. DataTypeToEnum<float>::v() is DT_FLOAT.
template <class T>
struct DataTypeToEnum {
  static_assert(IsValidDataType<T>::value, "Specified Data Type not supported");
};  // Specializations below

// EnumToDataType<VALUE>::Type is the type for DataType constant VALUE, e.g.
// EnumToDataType<DT_FLOAT>::Type is float.
template <DataType VALUE>
struct EnumToDataType {};  // Specializations below

// Template specialization for both DataTypeToEnum and EnumToDataType.
#define MATCH_TYPE_AND_ENUM(TYPE, ENUM)                 \
  template <>                                           \
  struct DataTypeToEnum<TYPE> {                         \
    static DataType v() { return ENUM; }                \
    static DataType ref() { return MakeRefType(ENUM); } \
    static constexpr DataType value = ENUM;             \
  };                                                    \
  template <>                                           \
  struct IsValidDataType<TYPE> {                        \
    static constexpr bool value = true;                 \
  };                                                    \
  template <>                                           \
  struct EnumToDataType<ENUM> {                         \
    typedef TYPE Type;                                  \
  }

MATCH_TYPE_AND_ENUM(float, DT_FLOAT);
MATCH_TYPE_AND_ENUM(double, DT_DOUBLE);
MATCH_TYPE_AND_ENUM(int32, DT_INT32);
MATCH_TYPE_AND_ENUM(uint16, DT_UINT16);
MATCH_TYPE_AND_ENUM(uint8, DT_UINT8);
MATCH_TYPE_AND_ENUM(int16, DT_INT16);
MATCH_TYPE_AND_ENUM(int8, DT_INT8);
MATCH_TYPE_AND_ENUM(string, DT_STRING);
MATCH_TYPE_AND_ENUM(complex64, DT_COMPLEX64);
MATCH_TYPE_AND_ENUM(complex128, DT_COMPLEX128);
MATCH_TYPE_AND_ENUM(int64, DT_INT64);
MATCH_TYPE_AND_ENUM(bool, DT_BOOL);
MATCH_TYPE_AND_ENUM(qint8, DT_QINT8);
MATCH_TYPE_AND_ENUM(quint8, DT_QUINT8);
MATCH_TYPE_AND_ENUM(qint16, DT_QINT16);
MATCH_TYPE_AND_ENUM(quint16, DT_QUINT16);
MATCH_TYPE_AND_ENUM(qint32, DT_QINT32);
MATCH_TYPE_AND_ENUM(bfloat16, DT_BFLOAT16);
MATCH_TYPE_AND_ENUM(Eigen::half, DT_HALF);

#undef MATCH_TYPE_AND_ENUM

// All types not specialized are marked invalid.
template <class T>
struct IsValidDataType {
  static constexpr bool value = false;
};

#endif //TENSORFLOWCC_EXAMPLE_TYPES_H
