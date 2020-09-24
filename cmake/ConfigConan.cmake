find_program(conan conan)
if(NOT conan)
    message(FATAL_ERROR "Cannot find `conan` executable")
endif()

set(conan_file ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

option(conan_source_build "Perform full source build for dependencies " True)
set(source_build_flag "")
if(conan_source_build)
    set(source_build_flag "-b")
    message("YES source build")
else()
    message("NOT source build")
endif()

if(NOT EXISTS ${conan_file})
    set(build_type ${CMAKE_BUILD_TYPE})
    if(NOT DEFINED ${CMAKE_BUILD_TYPE})
        set(build_type Debug)
    endif()
    string(REGEX MATCH [0-9]+.[0-9]+ # Get major.minor only
        conan_compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    set(conan_compiler "Visual Studio")
    set(conan_cxx_lib libstdc++11)
    string(TOLOWER ${CMAKE_CXX_COMPILER_ID} compiler_id)
    if(${compiler_id} MATCHES clang)
        if(APPLE)
            set(conan_compiler apple-clang)
            set(conan_cxx_lib libc++) #libstdc++) #libc++
        else()
            set(conan_compiler clang)
        endif()
    elseif(${compiler_id} MATCHES gnu)
        set(conan_compiler gcc)
    endif()

    file(RELATIVE_PATH REL_PATH ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR})
    set(args install
        ${source_build_flag}
        -e CXX=${CMAKE_CXX_COMPILER}
        -e CC=${CMAKE_C_COMPILER}
        -s build_type=${build_type}
        -s compiler=${conan_compiler}
        -s compiler.version=${conan_compiler_version}
        -s compiler.libcxx=${conan_cxx_lib}
        ${REL_PATH})
    LIST(JOIN args " " joined_args)
    message("Conan install has not been run, running `${conan} ${joined_args}`")
    execute_process(COMMAND ${conan} ${args}
        RESULT_VARIABLE return_code
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    if(NOT 0 EQUAL ${return_code})
        message(FATAL_ERROR "Failed Conan run with code ${return_code}")
    endif()
endif()

include(${conan_file})
conan_basic_setup(TARGETS)
