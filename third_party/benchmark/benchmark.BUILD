package(default_visibility=["//visibility:public"])
cc_library(
    name="benchmark-cxx",
    srcs=glob(["src/*.cc", "src/*.h"]),
    hdrs=glob(["include/benchmark/*.h"]),
    includes=["include/"],
    linkopts = ["-pthread"],
    deps=["@//third_party/gflags:gflags-cxx"],
    defines=["HAVE_STD_REGEX"], )
py_library(
    name="gbench",
    srcs=glob(["tools/gbench/*.py"]), )
py_binary(
    name="compare_bench",
    srcs=["tools/compare_bench.py"],
    deps=[":gbench"], )
