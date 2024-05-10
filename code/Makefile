GCC=g++-13
FLG=-std=c++23 -fmodules-ts -ggdb
MOD_DIR=gcm.cache/usr/include/c++/13
BLD_HDR=${GCC} ${FLG} -xc++-system-header

all: std_headers quick_test loglib_test

std_headers: iostream string_view string source_location

iostream:
ifeq (,$(wildcard ${MOD_DIR}/iostream.gcm))
	${BLD_HDR} iostream
endif

string_view:
ifeq (,$(wildcard ${MOD_DIR}/string_view.gcm))
	${BLD_HDR} string_view
endif

string:
ifeq (,$(wildcard ${MOD_DIR}/string.gcm))
	${BLD_HDR} string
endif

source_location:
ifeq (,$(wildcard ${MOD_DIR}/$@.gcm))
	${BLD_HDR} $@
endif

utility:
ifeq (,$(wildcard ${MOD_DIR}/$@.gcm))
	${BLD_HDR} $@
endif

cstdint:
ifeq (,$(wildcard ${MOD_DIR}/$@.gcm))
	${BLD_HDR} $@
endif

quick_test: quick_test.cpp iostream
	${GCC} ${FLG} $< -o $@

mathlib_arithmetics.o: mathlib_arithmetics.cpp
	${GCC} ${FLG} -c $< -o $@

mathlib.o: mathlib.cpp mathlib_arithmetics.o utility
	${GCC} ${FLG} -c $< -o $@

mathlib_test: mathlib_test.cpp mathlib.o iostream
	${GCC} ${FLG} $< -o $@

color_utils.o: color_utils.cpp cstdint
	${GCC} ${FLG} -c $< -o $@

color_utils_impl.o: color_utils_impl.cpp color_utils.o
	${GCC} ${FLG} -c $< -o $@

color_utils_test: color_utils_test.cpp color_utils.o color_utils_impl.o
	${GCC} ${FLG} $^ -o $@

stringlib.o: stringlib_module_interface.cpp string_view
	${GCC} ${FLG} -c $< -o $@

import_test: import_test.cpp stringlib.o iostream
	${GCC} ${FLG} $< stringlib.o -o $@

loglib.o: loglib.cpp iostream string_view string source_location
	${GCC} ${FLG} -c $< -o $@ -DDISABLE_LOGGING

loglib_test: loglib_test.cpp loglib.o
	${GCC} ${FLG} $^ -o $@

disable_lib.o: disable_lib.cpp
	${GCC} ${FLG} -c $^ -o $@

disable_lib_release.o: disable_lib.cpp
	${GCC} ${FLG} -DDLIB_DISABLE_LOG -c $^ -o $@

disable_test.asm: disable_test.cpp disable_lib.o
	${GCC} ${FLG} -S -lto $^ -o $@

disable_test_release.asm: disable_test.cpp disable_lib_release.o
	${GCC} ${FLG} -S -lto $^ -o $@

disable_test: disable_test.cpp disable_lib.o
	${GCC} ${FLG} $^ -o $@

disable_test_release: disable_test.cpp disable_lib_release.o
	${GCC} ${FLG} -Xlinker -flto $^ -o $@

file_and_line.o: file_and_line.cpp iostream string source_location
	${GCC} ${FLG} -c $< -o $@

file_and_line_test: file_and_line_test.cpp file_and_line.o
	${GCC} ${FLG} $^ -o $@

clean:
	rm -f quick_test import_test loglib_test disable_test disable_test_release

cleanall: clean
	rm -rf gcm.cache/
	rm -f *.o *.asm
