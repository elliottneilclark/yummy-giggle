package(default_visibility=["//visibility:public"])
cc_library(
    name="glog-cxx",
    srcs=glob([
        "src/**/*.cc",
        "src/**/*.h",
    ], exclude=["src/windows**/*"]),
    hdrs=glob(["googletest/include/**/*.h"]),
    includes=["googletest/include/", "googletest/"],
    defines=["HAVE_LIB_GFLAGS"],
    linkopts=["-lpthread"], )
