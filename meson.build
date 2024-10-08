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

if get_option('no_singleton_instance')
    cpp_args += '-DNO_DEFAULT_SINGLETON'
    add_project_arguments(cpp_args, language: 'cpp')
endif
if get_option('no_default_macros')
    cpp_args += '-DNO_DEFAULT_MACROS'
    add_project_arguments(cpp_args, language: 'cpp')
endif

fmt_proj = subproject('fmt', default_options: ['warning_level=3', 'werror=false'])
fmt_dep = fmt_proj.get_variable('fmt_dep')

convertx = subproject('convertx')
convertx_dep = convertx.get_variable('convertx_dep')

dependencies = [fmt_dep, convertx_dep]

subdir('src/cyberlogger')

cyber_logger = library(
    'cyberLogger',
    src_files,
    dependencies: dependencies,
    cpp_args : '-std=c++23'
)

cyberlogger_inc = include_directories('src', is_system: true)
cyberlogger_dep = declare_dependency(
    link_with: cyber_logger,
    include_directories: cyberlogger_inc,
    compile_args: cpp_args,
    dependencies: dependencies
)


if get_option('build_test_targets')

    catch2_proj = subproject('catch2', default_options: ['warning_level=0', 'werror=false'])
    catch2_dep = catch2_proj.get_variable('catch2_with_main_dep')

    subdir('test')

endif