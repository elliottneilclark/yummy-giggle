package(default_visibility=["//visibility:public"])
cc_library(
    name="gtest-cxx",
    srcs=glob(
        [
            "googletest/src/*.cc", "googletest/src/*.h",
        ],
        exclude=[
            "googletest/src/gtest-all.cc", "googletest/include/gtest/gtest.h"
        ]),
    hdrs=glob(["googletest/include/**/*.h"]),
    includes=["googletest/include/", "googletest/"],
    linkopts=["-lpthread"], )
