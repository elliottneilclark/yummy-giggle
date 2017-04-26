licenses(["notice"])

package(default_visibility=["//visibility:public"])

package_name = "gmock"
package_version = "1.8.0"

package_file = "release-" + package_version + ".tar.gz"
package_dir = "googletest-release-" + package_version + "/googlemock/"

include_files = [
    "include/gmock/gmock-actions.h",
    "include/gmock/gmock-generated-function-mockers.h.pump",
    "include/gmock/gmock-matchers.h",
    "include/gmock/gmock-cardinalities.h",
    "include/gmock/gmock-generated-matchers.h",
    "include/gmock/gmock-more-actions.h",
    "include/gmock/gmock-generated-actions.h",
    "include/gmock/gmock-generated-matchers.h.pump",
    "include/gmock/gmock-more-matchers.h",
    "include/gmock/gmock-generated-actions.h.pump",
    "include/gmock/gmock-generated-nice-strict.h",
    "include/gmock/gmock-spec-builders.h",
    "include/gmock/gmock-generated-function-mockers.h",
    "include/gmock/gmock-generated-nice-strict.h.pump",
    "include/gmock/gmock.h",
    "include/gmock/internal/gmock-generated-internal-utils.h",
    "include/gmock/internal/gmock-internal-utils.h",
    "include/gmock/internal/gmock-generated-internal-utils.h.pump",
    "include/gmock/internal/gmock-port.h",
]

lib_files = [
    "lib/libgmock.a",
    "lib/libgmock_main.a",
]

genrule(
    name="gmock-srcs",
    srcs=["@googletest_tar//file"],
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
    name="gmock-cxx",
    srcs=[
        "empty.cc",
        "lib/libgmock.a",
    ],
    hdrs=include_files,
    includes=[
        "include",
    ],
    linkstatic=1, )

cc_library(
    name="gmock_main-cxx",
    srcs=[
        "empty.cc",
        "lib/libgmock_main.a",
    ],
    linkstatic=1, )

filegroup(
    name="gmock", srcs=[
        ":gmock-cxx",
        ":gmock_main-cxx",
    ])

filegroup(
    name="gmock-files",
    srcs=include_files + lib_files, )
