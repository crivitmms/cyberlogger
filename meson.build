project(
    'CyberLogger',
    'cpp',
    default_options: [
        'warning_level=3',
        'werror=true',
        'default_library=static',
    ],
)

src_files = []
header_only = []
cpp_args = []

fmt_proj = subproject('fmt', default_options: ['warning_level=3', 'werror=false'])
fmt_dep = fmt_proj.get_variable('fmt_dep')

subdir('src/cyberlogger')

cyber_logger = library(
    'cyberLogger',
    src_files,
    dependencies: fmt_dep,
    cpp_args : '-std=c++23'
)

cyberlogger_inc = include_directories('src', is_system: true)
cyberlogger_dep = declare_dependency(
    link_with: cyber_logger,
    include_directories: cyberlogger_inc,
    compile_args: cpp_args,
    dependencies: fmt_dep
)


if get_option('build_test_targets')

    catch2_proj = subproject('catch2', default_options: ['warning_level=0', 'werror=false'])
    catch2_dep = catch2_proj.get_variable('catch2_with_main_dep')

    subdir('test')

endif