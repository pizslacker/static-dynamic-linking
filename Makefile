CC = gcc
CFLAGS = -Wall -O3

all: app_static app_dynamic

# ---------------------------------------------------------
# STATIC LINKING DEMO
# ---------------------------------------------------------
app_static: main.c libmath.a
	# Link the static library (.a) directly into the executable
	$(CC) $(CFLAGS) main.c libmath.a -o app_static

libmath.a: math_lib.c
	# 1. Compile to a standard object file
	$(CC) $(CFLAGS) -c math_lib.c -o math_lib_static.o
	# 2. Archive the object file into a static library
	ar rcs libmath.a math_lib_static.o


# ---------------------------------------------------------
# DYNAMIC LINKING DEMO
# ---------------------------------------------------------
app_dynamic: main.c libmath.so
	# Link against the shared library (.so)
	# -L. tells GCC to look in the current directory for libraries
	# -lmath tells GCC to link against libmath.so
	# -Wl,-rpath=. tells the executable where to find the .so at runtime!
	$(CC) $(CFLAGS) main.c -L. -lmath -Wl,-rpath=. -o app_dynamic

libmath.so: math_lib.c
	# 1. Compile to a Position Independent Code (PIC) object file
	$(CC) $(CFLAGS) -fPIC -c math_lib.c -o math_lib_dyn.o
	# 2. Compile the object file into a shared library
	$(CC) -shared -o libmath.so math_lib_dyn.o


clean:
	rm -f *.o *.a *.so app_static app_dynamic