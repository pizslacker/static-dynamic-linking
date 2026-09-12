# C Linking Demystified: Static vs. Dynamic
This project serves as a hands-on playground to understand how C compilers stitch code together. It builds the exact same source code into two different executables—one statically linked and one dynamically linked—so you can inspect, break, and compare how they operate at the operating system level.

#### What It Does
The program calculates the sum of a 5-million-element array. The logic for this calculation is separated into a discrete library (math_lib).

Instead of compiling everything into one big block immediately, the included Makefile splits the build path in two:

**app_static**: Embeds the math library directly inside the final executable.

**app_dynamic**: Keeps the math library as a separate file on your hard drive and loads it into memory only when the program actually runs.

How It Works
Here is the compilation architecture. The source files are identical, but the compiler and linker toolchains handle the object files (.o) completely differently.

code
```
flowchart TD
    classDef source fill:#2d3436,stroke:#74b9ff,stroke-width:2px,color:#fff;
    classDef object fill:#2d3436,stroke:#fdcb6e,stroke-width:2px,color:#fff;
    classDef lib fill:#0984e3,stroke:#74b9ff,stroke-width:2px,color:#fff;
    classDef exec fill:#00b894,stroke:#55efc4,stroke-width:2px,color:#fff;

    A[math_lib.c]:::source
    B[main.c]:::source

    subgraph Static Pipeline [Static Linking Pipeline]
        A -->|gcc -c| C(math_lib_static.o):::object
        C -->|ar rcs| D{libmath.a}:::lib
        B -->|gcc| E[app_static]:::exec
        D -->|Hard-copied into| E
    end

    subgraph Dynamic Pipeline [Dynamic Linking Pipeline]
        A -->|gcc -fPIC -c| F(math_lib_dyn.o):::object
        F -->|gcc -shared| G{libmath.so}:::lib
        B -->|gcc -L. -lmath| H[app_dynamic]:::exec
        G -.->|Loaded by OS at runtime| H
    end
```

**1. The Static Path (libmath.a)**
Compilation: We compile the C file into a standard object file (.o).

Archiving: We use the ar (archiver) tool to bundle the object file into a Static Library (.a).

Linking: When GCC builds app_static, it physically extracts the machine code from libmath.a and copies it into the final executable file.

**2. The Dynamic Path (libmath.so)**
Compilation: We compile the C file using the -fPIC (Position Independent Code) flag. This ensures the machine code uses relative memory addresses, allowing the OS to load it anywhere in RAM.

Archiving: We compile the object file into a Shared Object / Dynamic Library (.so).

Linking: When GCC builds app_dynamic, it does not copy the library's code. Instead, it embeds a "pointer" (an rpath or run-path) telling the executable: "When you start up, go find libmath.so and load it."

### Getting Started

#### 1. Build the project
Run the following command in the directory containing your files. The Makefile will handle the heavy lifting.

```bash
make
```

#### 2. Run the executables
Both will output the exact same result:

```bash
./app_static
./app_dynamic
```

**The "Break It" Tests**
To truly see the difference between the two architectures, try these three experiments in your terminal:

**Test 1: The Deletion Test**
Delete the libraries, then try to run the apps.

```bash
rm libmath.so libmath.a
```

`./app_static`   # Will run perfectly fine.
`./app_dynamic`  # Will crash: "cannot open shared object file"

Why? `app_static` carries its dependencies inside itself. `app_dynamic` relied on the external file you just deleted.

**Test 2: The Size Test**
Rebuild the project (make clean && make), then check file sizes:

```bash
ls -lh app_static app_dynamic
```

Notice: `app_static` is a larger file because the library's machine code is baked directly into the binary footprint.

**Test 3: The Dependency Tree**
Use the ldd command (List Dynamic Dependencies) on Linux to see what the OS loads when you run a program.

```bash
ldd app_static
ldd app_dynamic
```

Notice: app_dynamic will explicitly list libmath.so => ./libmath.so as a requirement to run. app_static only requires core system libraries like libc.
