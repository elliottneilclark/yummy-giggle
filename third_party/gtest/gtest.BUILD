package(default_visibility=["//visibility:public"])
cc_library(
    name="gtest-cxx",
    srcs=glob(
        [
            "googletest/src/*.cc",
            "googletest/src/*.h",
        ],
        exclude=[
            "googletest/src/gtest-all.cc", "googletest/include/gtest/gtest.h"
        ]),
    hdrs=glob(["googletest/include/**/*.h"]),
    includes=["googletest/include/", "googletest/"],
    linkopts=["-lpthread"], )

cc_library(
    name="gmock-cxx",
    testonly=1,
    srcs=glob([
        "googlemock/include/gmock/internal/**/*.h",
    ]) + [
        "googlemock/src/gmock-cardinalities.cc",
        "googlemock/src/gmock.cc",
        "googlemock/src/gmock-internal-utils.cc",
        "googlemock/src/gmock-matchers.cc",
        "googlemock/src/gmock-spec-builders.cc",
        "googlemock/src/gmock_main.cc",
    ],
    hdrs=glob(["googlemock/include/gmock/*.h"]),
    includes=["googlemock/include", "googlemock/"],
    visibility=["//visibility:public"],
    deps=[
        ":gtest-cxx",
    ], )
