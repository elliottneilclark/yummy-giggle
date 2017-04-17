licenses(["notice"])

package(default_visibility=["//visibility:public"])

package_name = "gtest"
package_version = "1.8.0"

package_file = "release-" + package_version + ".tar.gz"
package_dir = "googletest-release-" + package_version + "/googletest/"

include_files = [
    "include/gtest/gtest-death-test.h",
    "include/gtest/gtest-param-test.h.pump",
    "include/gtest/gtest-test-part.h",
    "include/gtest/gtest_pred_impl.h",
    "include/gtest/gtest-message.h",
    "include/gtest/gtest-printers.h",
    "include/gtest/gtest-typed-test.h",
    "include/gtest/gtest_prod.h",
    "include/gtest/gtest-param-test.h",
    "include/gtest/gtest-spi.h",
    "include/gtest/gtest.h",
    "include/gtest/internal/gtest-death-test-internal.h",
    "include/gtest/internal/gtest-param-util-generated.h.pump",
    "include/gtest/internal/gtest-tuple.h.pump",
    "include/gtest/internal/gtest-filepath.h",
    "include/gtest/internal/gtest-param-util.h",
    "include/gtest/internal/gtest-type-util.h",
    "include/gtest/internal/gtest-type-util.h.pump",
    "include/gtest/internal/gtest-internal.h",
    "include/gtest/internal/gtest-port.h",
    "include/gtest/internal/gtest-port-arch.h",
    "include/gtest/internal/gtest-linked_ptr.h",
    "include/gtest/internal/gtest-string.h",
    "include/gtest/internal/gtest-param-util-generated.h",
    "include/gtest/internal/gtest-tuple.h",
    "include/gtest/internal/custom/gtest-port.h",
    "include/gtest/internal/custom/gtest-printers.h",
    "include/gtest/internal/custom/gtest.h",
]

lib_files = [
    "lib/libgtest.a",
    "lib/libgtest_main.a",
]

genrule(
    name="gtest-srcs",
    srcs=[
        "@googletest_tar//file",
    ],
    outs=include_files + lib_files,
    cmd="\n".join([
        'export TMP_DIR=$$(mktemp -d -t gmock.XXXXX)',
        'export INSTALL_DIR=$$(pwd)/$(@D)',
        'export CPPFLAGS="-g -fPIC"',
        'export CXXFLAGS="-std=c++14 -g -fPIC"',
        'mkdir -p $$TMP_DIR',
        'cp -R $(SRCS) $$TMP_DIR',
        'cd $$TMP_DIR',
        'tar xfz ' + package_file,
        'cd ' + package_dir,
        'cmake -DCMAKE_INSTALL_PREFIX:PATH="$$INSTALL_DIR" .',
        'make install',
        'rm -rf $$TMP_DIR',
    ]), )

cc_library(
    name="gtest-cxx",
    srcs=[
        "empty.cc",
        "lib/libgtest.a",
    ],
    hdrs=include_files,
    includes=[
        "include",
    ],
    linkopts=["-pthread"],
    linkstatic=1, )

cc_library(
    name="gtest_main-cxx",
    srcs=[
        "empty.cc",
        "lib/libgtest_main.a",
    ],
    deps=[
        ":gtest-cxx",
    ],
    linkstatic=1,
    alwayslink=1, )

filegroup(
    name="gtest", srcs=[
        ":gtest-cxx",
        ":gtest_main-cxx",
    ])

filegroup(
    name="gtest-files",
    srcs=include_files + lib_files, )
