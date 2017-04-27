package(default_visibility=["//visibility:public"])
cc_library(
    name="card",
    srcs=["card.cpp"],
    hdrs=["card.h"],
    deps=[
        "//third_party/glog:glog-cxx", "//utils:bits",
        "//third_party/boost:functional-cxx"
    ], )
cc_test(
    name="card_test",
    srcs=["card_test.cpp"],
    deps=["//third_party/gtest:gtest_main-cxx", ":card"],
    linkstatic=1,
    size="small", )
cc_library(
    name="hand",
    srcs=["hand.cpp"],
    hdrs=["hand.h"],
    deps=[
        "//third_party/glog:glog-cxx", "//utils:bits", ":card",
        "//third_party/boost:optional-cxx"
    ], )
cc_library(
    name="deck",
    hdrs=[
        "deck.h",
    ],
    srcs=["deck.cpp"],
    deps=[
        ":card",
    ], )
cc_library(
    name="choose_iter",
    hdrs=[
        "choose_iter.h",
    ],
    srcs=["choose_iter.cpp"],
    deps=[":card", ":deck"], )
cc_test(
    name="hand_test",
    srcs=["hand_test.cpp"],
    deps=["//third_party/gtest:gtest_main-cxx", ":card", ":hand", ":deck"],
    size="small", )
cc_test(
    name="deck_test",
    srcs=["deck_test.cpp"],
    deps=["//third_party/gtest:gtest_main-cxx", ":card", ":hand", ":deck"],
    size="small", )
cc_test(
    name="choose_iter_test",
    srcs=["choose_iter_test.cpp"],
    deps=["//third_party/gtest:gtest_main-cxx", ":choose_iter"],
    size="small", )
