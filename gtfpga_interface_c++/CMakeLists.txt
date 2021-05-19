cmake_minimum_required(VERSION 3.3)

project(main)

set(CMAKE_VERBOSE_MAKEFILE ON)
macro(SET_MY_COMPILE_LINK_FLAGS)
    # compiler options
        # macros
            add_definitions(-D_FILE_OFFSET_BITS=64)

        # code checks
            # http://voices.canonical.com/jussi.pakkanen/2013/03/26/a-list-of-common-cmake-antipatterns/
            # Alternate syntax (rather than add_definitions)?
            #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

            add_definitions(-std=c++2a)
            add_definitions(-Wall -Wextra)
            #add_definitions(-Wsign-conversion)
            add_definitions(-Wconversion)
            add_definitions(-Wshadow)
            #add_definitions(-pedantic)
            #add_definitions(-ansi)
            add_definitions(-Wno-long-long) # don't warn if long long types are used
            add_definitions(-Wunused-macros)
            # check for multiple definitions (multiple definitions in different compilation units)
            add_definitions(-fno-common)
            add_definitions(-Wstrict-aliasing=3) # only enabled if -fstrict-aliasing
			#add_definitions(-Weffc++)
			add_definitions(-Wno-effc++) # HACK?
            add_definitions(-Wunused-but-set-variable)
            add_definitions(-Wunused-but-set-parameter)

            # overflow/wrap
                add_definitions(-fstrict-overflow)
                add_definitions(-Wstrict-overflow=5)
                #add_definitions(-ftrapv) # WARNING: uses signals rather than just printing to screen
                add_definitions(-fsanitize=undefined)
                add_definitions(-fsanitize=signed-integer-overflow)
                #add_definitions(-fsanitize=null)
                #add_definitions(-fsanitize=address)
                SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined" )
                SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=signed-integer-overflow" )
                SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=null" )
                #SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address" )
                SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=vptr" )

        # optimizations
            #add_definitions(-funroll-loops) # not enabled by -O3
            add_definitions(-O2)
            #add_definitions(-fomit-frame-pointer)
            #add_definitions(-fstrict-aliasing) # [default]
            add_definitions(-g) # debug symbols
endmacro()

SET_MY_COMPILE_LINK_FLAGS()

# subdirectories
	#add_subdirectory(time_unit)

# libraries
	#add_library(time_period time_period.cpp time_unit.cpp cpu_consumer.cpp)

# executables
	# exec_time
	add_executable(main main.cpp)
        target_link_libraries(main -lpci)
