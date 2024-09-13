test_files = files('test.cpp')

# CyberLogger_test_17 = executable(
#     'CyberLogger_test_17',
#     test_files,
#     dependencies: [catch2_dep, cyberlogger_dep],
#     cpp_args : '-std=c++17'
# )
CyberLogger_test_20 = executable(
    'CyberLogger_test_20',
    test_files,
    dependencies: [catch2_dep, cyberlogger_dep],
    cpp_args : '-std=c++20'
)
CyberLogger_test_23 = executable(
    'CyberLogger_test_23',
    test_files,
    dependencies: [catch2_dep, cyberlogger_dep],
    cpp_args : '-std=c++23'
)

# test('CyberLogger tests c++17', CyberLogger_test_17)
test('CyberLogger tests c++20', CyberLogger_test_20)
test('CyberLogger tests c++23', CyberLogger_test_23)