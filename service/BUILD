cc_library(
    name="service",
    srcs=["simulate_service_impl.cpp"],
    hdrs=["simulate_service_impl.h"],
    deps=["//proto:cpp"], )

cc_binary(
    name="yg-server",
    srcs=["server.cpp"],
    deps=[":service", "@com_github_gflags_gflags//:gflags"], )
