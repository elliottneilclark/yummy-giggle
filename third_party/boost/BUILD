licenses(["notice"])

package(default_visibility=["//visibility:public"])
load('//third_party/boost:boost_generated.bzl', 'all_files')
load('//third_party/boost:boost_lib.bzl', 'boost_library')

package_version = "1_63_0"
package_dir = "boost_" + package_version
package_file = package_dir + ".tar.gz"

genrule(
    name="boost-srcs",
    srcs=["@boost_tar//file"],
    outs=all_files,
    cmd="\n".join([
        'export INSTALL_DIR=$$(pwd)/$(@D)',
        'export TMP_DIR=$$(mktemp -d -t gflags.XXXXX)',
        'mkdir -p $$TMP_DIR',
        'cp -R $(SRCS) $$TMP_DIR',
        'cd $$TMP_DIR',
        'tar xfz ' + package_file,
        'cd ' + package_dir,
        './bootstrap.sh',
        './b2 -a -j2 -q cxxflags="-std=c++14 -msse -msse2 -msse3 -fPIC -g" link=static --reconfigure --without-python --without-mpi --prefix="$$INSTALL_DIR" install',
        'rm -rf $$TMP_DIR',
    ]), )

boost_library(
    name="algorithm-cxx", deps=[
        ":function-cxx",
        ":range-cxx",
    ])
boost_library(
    name="align-cxx", )

boost_library(
    name="assert-cxx", )

boost_library(
    name="atomic-cxx", )

boost_library(
    name="bind-cxx", )

boost_library(
    name="chrono-cxx",
    deps=[":ratio-cxx"], )

boost_library(
    name="concept_check-cxx", )

boost_library(
    name="config-cxx", )

boost_library(
    name="container-cxx", )

boost_library(
    name="context-cxx",
    deps=[":config-cxx"], )

boost_library(
    name="conversion-cxx", )

boost_library(name="core-cxx", deps=[":config-cxx", ":detail-cxx"])

boost_library(
    name="date_time-cxx", )

boost_library(
    name="detail-cxx", )

boost_library(
    name="exception-cxx", )

boost_library(
    name="filesystem-cxx",
    deps=[
        ":config-cxx",
        ":functional-cxx",
        ":io-cxx",
        ":iterator-cxx",
        ":range-cxx",
        ":smart_ptr-cxx",
        ":system-cxx",
        ":type_traits-cxx",
    ], )

boost_library(
    name="foreach-cxx", )

boost_library(
    name="function-cxx",
    deps=[
        ":bind-cxx",
    ], )

boost_library(
    name="function_types-cxx", )

boost_library(
    name="functional-cxx",
    deps=[
        ":detail-cxx",
    ], )

boost_library(
    name="heap-cxx",
    deps=[
        ":parameter-cxx",
    ], )

boost_library(
    name="integer-cxx",
    deps=[":static_assert-cxx"], )

boost_library(
    name="iterator-cxx",
    deps=[
        ":detail-cxx",
        ":static_assert-cxx",
    ], )

boost_library(
    name="intrusive-cxx",
    deps=[":assert-cxx", ":static_assert-cxx"], )

boost_library(
    name="io-cxx", )

boost_library(
    name="math-cxx", )

boost_library(
    name="move-cxx", )

boost_library(
    name="mpl-cxx", deps=[
        ":preprocessor-cxx",
        ":move-cxx",
    ])

boost_library(
    name="multi_index-cxx",
    deps=[
        ":foreach-cxx",
        ":serialization-cxx",
        ":static_assert-cxx",
        ":tuple-cxx",
    ], )

boost_library(
    name="optional-cxx",
    deps=[
        ":assert-cxx", "core-cxx", ":static_assert-cxx",
        ":throw_exception-cxx", ":type-cxx", ":none-cxx", ":type_traits-cxx",
        ":version-cxx"
    ])

boost_library(
    name="parameter-cxx", )

boost_library(name="none-cxx", deps=[":none_t-cxx"])
boost_library(
    name="none_t-cxx", )

boost_library(
    name="version-cxx", )

boost_library(
    name="predef-cxx", )

boost_library(
    name="preprocessor-cxx", )

boost_library(
    name="range-cxx", deps=[
        ":concept_check-cxx",
        ":optional-cxx",
    ])

boost_library(
    name="ratio-cxx", )

boost_library(
    name="regex-cxx",
    deps=[
        ":assert-cxx",
        ":config-cxx",
        ":functional-cxx",
        ":integer-cxx",
        ":mpl-cxx",
        ":smart_ptr-cxx",
        ":throw_exception-cxx",
        ":type_traits-cxx",
    ])

boost_library(
    name="serialization-cxx", )

boost_library(
    name="smart_ptr-cxx",
    deps=[
        ":align-cxx",
        ":core-cxx",
        ":predef-cxx",
        ":throw_exception-cxx",
        ":utility-cxx",
    ], )

boost_library(
    name="static_assert-cxx", )

boost_library(
    name="system-cxx",
    deps=[
        ":assert-cxx",
        ":config-cxx",
        ":core-cxx",
        ":predef-cxx",
    ], )

boost_library(
    name="thread-cxx",
    deps=[
        ":atomic-cxx",
        ":chrono-cxx",
        ":core-cxx",
        ":date_time-cxx",
        ":exception-cxx",
        ":io-cxx",
        ":system-cxx",
    ])

boost_library(
    name="throw_exception-cxx",
    deps=[":exception-cxx", ":current_function-cxx"])

boost_library(
    name="current_function-cxx", )

boost_library(
    name="type-cxx", )

boost_library(
    name="type_index-cxx", deps=[
        ":core-cxx",
    ])

boost_library(
    name="type_traits-cxx",
    deps=[
        ":core-cxx",
        ":mpl-cxx",
        ":utility-cxx",
        ":static_assert-cxx",
    ])

boost_library(
    name="tuple-cxx", )

boost_library(
    name="tr1-cxx", deps=[
        ":config-cxx",
    ])

boost_library(
    name="utility-cxx", )

boost_library(
    name="variant-cxx", deps=[
        ":math-cxx",
        ":type_index-cxx",
    ])
