load('//third_party/boost:boost_generated.bzl', 'includes_map', 'libs_map')


def boost_library(name, deps=None):
    libs = []
    boost_name = name[:-4]
    if boost_name in libs_map:
        libs = libs_map[boost_name]

    headers = []
    if boost_name in includes_map:
        headers = includes_map[boost_name]

    native.cc_library(
        name=name,
        srcs=[
            "empty.cc",
        ] + libs,
        hdrs=headers,
        includes=["include"],
        linkstatic=1,
        deps=deps, )
