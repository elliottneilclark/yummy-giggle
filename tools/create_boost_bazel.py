#!/usr/bin/python3

from os import listdir, walk
from os.path import isfile, join
import sys
import collections
import pprint

base_libs = [
    "numeric",
    "qvm",
    "iterator",
    "scope_exit",
    "vmd",
    "move",
    "tti",
    "atomic",
    "static_assert",
    "ratio",
    "predef",
    "property_map",
    "graph",
    "signals",
    "smart_ptr",
    "circular_buffer",
    "tr1",
    "random",
    "format",
    "python",
    "mpl",
    "lockfree",
    "interprocess",
    "fusion",
    "bimap",
    "integer",
    "signals2",
    "statechart",
    "parameter",
    "crc",
    "ptr_container",
    "lexical_cast",
    "property_tree",
    "locale",
    "accumulators",
    "concept_check",
    "asio",
    "container",
    "icl",
    "dll",
    "type_traits",
    "rational",
    "math",
    "core",
    "fiber",
    "winapi",
    "preprocessor",
    "serialization",
    "optional",
    "uuid",
    "function_types",
    "convert",
    "thread",
    "geometry",
    "timer",
    "range",
    "context",
    "logic",
    "assign",
    "lambda",
    "disjoint_sets",
    "tokenizer",
    "wave",
    "functional",
    "throw_exception",
    "flyweight",
    "array",
    "iostreams",
    "utility",
    "regex",
    "multiprecision",
    "log",
    "type_erasure",
    "system",
    "msm",
    "intrusive",
    "gil",
    "function",
    "coroutine",
    "assert",
    "coroutine2",
    "graph_parallel",
    "heap",
    "spirit",
    "xpressive",
    "exception",
    "compute",
    "multi_array",
    "align",
    "typeof",
    "endian",
    "unordered",
    "sort",
    "units",
    "multi_index",
    "type_index",
    "io",
    "any",
    "conversion",
    "polygon",
    "proto",
    "tuple",
    "detail",
    "dynamic_bitset",
    "local_function",
    "program_options",
    "foreach",
    "test",
    "config",
    "phoenix",
    "hana",
    "variant",
    "mpi",
    "compatibility",
    "pool",
    "date_time",
    "algorithm",
    "chrono",
    "bind",
    "metaparse",
    "filesystem",
]

added = ["current_function", "type", "version", "none", "none_t"]

base_dir = sys.argv[1]
lib_dir = join(base_dir, 'lib')
include_dir = join(base_dir, 'include/boost')

onlyfiles = [f for f in listdir(lib_dir) if isfile(join(lib_dir, f))]
a_files = set([f for f in onlyfiles if f.endswith('.a')])
top_files = set(
    [f for f in listdir(include_dir) if isfile(join(include_dir, f))])
top_dirs = [
    d for d in listdir(include_dir) if not isfile(join(include_dir, d))
]

name_to_includes = {}
name_to_libs = {}


def normailze_aname(name):
    lib_name = name[9:][:-2]
    if lib_name.startswith('math'):
        lib_name = 'math'
    if lib_name.startswith('wserialization'):
        lib_name = 'serialization'
    if lib_name.startswith('unit_test_framework'):
        lib_name = 'test'
    return lib_name


def normailze_includename(name):
    lib_name = name
    return lib_name


def walk_includes(name):
    result = []
    for root, dirs, files in walk(join(include_dir, name)):
        include_file_paths = [join(root, f)[len(base_dir):] for f in files]
        result += include_file_paths
    return list(set(result))


def add_include(lib_name):
    if lib_name not in name_to_includes:
        name_to_includes[lib_name] = []
    name_to_includes[lib_name] += walk_includes(lib_name)

    if '{}.hpp'.format(lib_name) in top_files:
        name_to_includes[lib_name] += ['include/boost/{}.hpp'.format(lib_name)]

    if lib_name in name_to_includes:
        name_to_includes[lib_name] = list(set(name_to_includes[lib_name]))


for a_file in a_files:
    lib_name = normailze_aname(a_file)
    if lib_name not in name_to_libs:
        name_to_libs[lib_name] = []
    name_to_libs[lib_name] += ['lib/{}'.format(a_file)]
    name_to_libs[lib_name] = list(set(name_to_libs[lib_name]))
    add_include(lib_name)

for lib in base_libs + added:
    lib_name = normailze_includename(lib)
    add_include(lib_name)

pp = pprint.PrettyPrinter(indent=4)
includes_string = pp.pformat(name_to_includes)
libs_string = pp.pformat(name_to_libs)

print("includes_map = {}".format(includes_string))
print("libs_map = {}".format(libs_string))
print(
    "all_files = [item for sublist in libs_map.values() + includes_map.values() for item in sublist]"
)
