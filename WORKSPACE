git_repository(
    name="boringssl",
    commit="2ddb72aa77c8186391e1269442ded05bdeb0328b",
    remote="https://boringssl.googlesource.com/boringssl", )
git_repository(
    name="double_conversion",
    commit="4abe3267170fa52f39460460456990dbae803f4d",
    remote="https://github.com/google/double-conversion.git")
git_repository(
    name="com_github_gflags_gflags",
    commit="9314597d4b742ed6f95665241345e590a0f5759b",
    remote="https://github.com/gflags/gflags.git",
)
git_repository(
  name = "org_pubref_rules_protobuf",
  remote = "https://github.com/pubref/rules_protobuf",
  commit="d4c4ec7ccca3647cd6ccc4f8fc4b4ca7347a0113",
)
http_file(
    name="glog_tar",
    url="https://github.com/google/glog/archive/v0.3.4.tar.gz")
http_file(
    name="libunwind_tar",
    url=
    "http://download.savannah.nongnu.org/releases/libunwind/libunwind-1.1.tar.gz"
)
http_file(
    name="boost_tar",
    url=
    "https://superb-sea2.dl.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.tar.gz"
)
new_git_repository(
    name="google_benchmark",
    commit="3336ea00d892fc312715c3a00d33a9568261e86a",
    remote="https://github.com/google/benchmark.git",
    build_file="third_party/benchmark/benchmark.BUILD", )
new_git_repository(
    name="google_gtest",
    commit="aa148eb2b7f70ede0eb10de34b6254826bfb34f4",
    remote="https://github.com/google/googletest.git",
    build_file="third_party/gtest/gtest.BUILD",
)


load("@bazel_tools//tools/cpp:cc_configure.bzl", "cc_configure")
cc_configure()

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cpp_proto_repositories")
cpp_proto_repositories()