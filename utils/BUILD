package(default_visibility=["//visibility:public"])
cc_library(
    name="bits",
    hdrs=["bits.h"], )
cc_test(
    name="bits_test",
    srcs=["bits_test.cpp"],
    deps=[":bits", "//third_party/gtest:gtest_main-cxx"],
    linkstatic=1,
    size="small", )
