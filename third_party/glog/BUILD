licenses(["notice"])

package(default_visibility=["//visibility:public"])

package_name = "glog"
package_version = "0.3.4"

package_file = "v" + package_version + ".tar.gz"
package_dir = package_name + "-" + package_version

include_files = [
    "include/glog/log_severity.h",
    "include/glog/logging.h",
    "include/glog/raw_logging.h",
    "include/glog/stl_logging.h",
    "include/glog/vlog_is_on.h",
]

lib_files = [
    "lib/libglog.a",
]

common_script = [
    'export UNWIND_DIR=$$(pwd)/$(GENDIR)/third_party/libunwind',
    'export INSTALL_DIR=$$(pwd)/$(@D)',
    'export TMP_DIR=$$(mktemp -d -t glog.XXXXX)',
    'mkdir -p $$TMP_DIR',
    'cp -R $(SRCS) $$TMP_DIR',
    'cd $$TMP_DIR',
    'tar xfz ' + package_file,
    'cd ' + package_dir,
]

mac_script = "\n".join(common_script + [
    './configure --prefix=$$INSTALL_DIR --enable-shared=no',
    'make install',
    'rm -rf $$TMP_DIR',
])

linux_script = "\n".join(common_script + [
    'export VAR_LIBS="-Wl,--rpath -Wl,$$UNWIND_DIR/lib -L$$UNWIND_DIR/lib"',
    'export VAR_INCL="-I$$UNWIND_DIR/include"',
    'export VAR_LD="-L$$UNWIND_DIR/lib"',
    'export CPPFLAGS="-O2 -g $$VAR_INCL"',
    'export CXXFLAGS="-O2 -std=c++14 -g -fPIC $$VAR_INCL"',
    'export LIBS="$$VAR_LIBS"',
    'export LDFLAGS="$$VAR_LD"',
    './configure --prefix=$$INSTALL_DIR --enable-shared=no',
    'make install',
    'rm -rf $$TMP_DIR',
])

genrule(
    name="glog-srcs",
    srcs=select({
        "//tools/platform:darwin": ["@glog_tar//file"],
        "//conditions:default": [
            "@glog_tar//file",
            "//third_party/libunwind:libunwind-files",
        ]
    }),
    outs=include_files + lib_files,
    cmd=select({
        "//tools/platform:darwin": mac_script,
        "//conditions:default": linux_script,
    }), )

cc_library(
    name="glog-cxx",
    srcs=["empty.cc"] + lib_files,
    deps=[
        "@com_github_gflags_gflags//:gflags",
        "//third_party/libunwind:libunwind-cxx",
    ],
    hdrs=include_files,
    includes=[
        "include",
    ],
    linkstatic=1, )

filegroup(
    name="glog", srcs=[
        ":glog-cxx",
    ])

filegroup(name="glog-files", srcs=include_files + lib_files)
