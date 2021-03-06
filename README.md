# BruhOS

I tried making an OS in [assembly-fun](https://github.com/soumitradev/assembly-fun). I failed. The code was crusty. This is my second attempt I guess.

I'm using the [limine bootloader](https://github.com/limine-bootloader/limine) with the stivale protocol.

Since this repo uses Limine as a submodule, you will have to clone this repo recursively using:

```
git clone --recursive https://github.com/soumitradev/BruhOS.git
```

## Building

Setting up a cross compiler is **strongly recommended** if you want to compile this project. A basic `toolchain.sh` file is included in the root of this repo that installs a cross compiler for the x86_64 platform for elf files.

After installing the cross compiler, you can run `make run` to run the OS in qemu.

As of now, the following make commands are available:

- `make all`: Make the .hdd file for the OS. That's it.
- `make disk`: Make the .hdd file for the OS. That's it.
- `make run`: Make the .hdd file for the OS and run it in qemu.
- `make log`: Make the .hdd file for the OS, run it, and let qemu generate logs.
- `make logs`: Make the .hdd file for the OS, run it, and let qemu generate logs.
- `make debug`: Make the .hdd file for the OS, run it, and attach it to gdb for debugging.
- `make clean`: Clean the working directory and remove all build artefacts.

### Setup

Running the `toolchain.sh` script will install the cross compiler at `~/.local/bin/cross_compiler/x86_64/`. It includes gcc, gdb, and binutils. The cross compiler binaries have the prefix `x86-64-elf-`. So for example, to run `gcc`, you will have to run `~/.local/bin/cross_compiler/x86_64/bin/x86-64-elf-gcc`. Note how the prefix is prepended to the binary we want to run.

**NOTE:** To make this process faster, you will have to set the number of threads as a variable, which is usually 1 more than the number of threads your machine has. My machine has 8 threads, so I set the `THREADS` variable in the `toolchain.sh` script to 9. Please check the number of threads you have, and change that variable in the `toolchain.sh` script accordingly.

As of writing, the latest gcc, gdb and binutils versions are 10.2.0, 9.2 and 2.35 respectively. If you want a different version, replace the `BINUTILSVERSION`, `GCCVERSION`, and `GDBVERSION` variables in the same `toolchain.sh` script.

**Note:** Don't run this script as superuser. Running the script will require a stable internet connection and a cup of coffee because it takes a while ;)

## Acknowledgements

[Limine](https://github.com/limine-bootloader/limine) is the most epic bootloader to ever exist.

[qword](https://github.com/qword-os/qword), [rock](https://github.com/ethan4984/rock), and [DripOS](https://github.com/Menotdan/DripOS) were very helpful. This code is pretty much a clusterfuck of their code. Their code is well written, easy to understand and is overall a great place to start learning OSDev.

The [OSDev Discord server](https://discord.gg/RnCtsqD) is also a great place to learn, ask questions, and is generally a great community.

## Screenshots

Screenshots because it's just not worth the time spent getting the toolchain to test out a half-finished kernel.

### Limine boot screen:

![](./boot.png)


### Kernel:

![](./kernel.png)

## Contributions

All files use the C++ 17 standard, don't use any standard library except libgcc (obvious for OS/Kernel development). All object files and kernel build files should be cleaned before commit using `make clean` or manually deleting the files. The gitignore includes some basic filters, but always double check you aren't committing any build artefacts.

All files except the Makefile are space indented with an Indent with of 2 spaces. Yes, I like 4 spaces, but having some previous experience, this can generate huge tree like structures, and it looks cleaner with 2 space indentation. The Makefile requires tab indentation by definition. Formatting it will cause it to break.

Make sure you are using the `Google` formatting guidelines. This can be set in VS Code.

**Don't push any commits without testing and making sure they work.**

**If the basic features work as they are intended to be used, push your commits. I don't expect you to forsee every security flaw and patch it before pushing.**

I might add a pre-push check script later that makes sure that your code follows these standards.
