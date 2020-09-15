# BruhOS

I tried making an OS in [assembly-fun](https://github.com/soumitradev/assembly-fun). I failed. The code was crusty. This is my second attempt I guess.

I'm using the [limine bootloader](https://github.com/limine-bootloader/limine) with the stivale protocol.

Since this repo uses an older version of Limine as a submodule, you will have to clone this repo recursively using:
```
git clone --recursive https://github.com/soumitradev/BruhOS.git
```

## Building

Setting up a cross compiler is **strongly recommended** if you want to compile this project. A basic `install.sh` file is included in the root of this repo that installs a cross compiler for the x86_64 platform for elf files.

After installing the cross compiler, you can run `make run`

### Setup

Running the `install.sh` script will install the cross compiler at `~/.local/bin/cross_compiler/x86_64/`. The cross compiler binaries have the prefix `x86-64-elf-`. So, to run gcc, you will have to run `~/.local/bin/cross_compiler/x86_64/bin/x86-64-elf-gcc`.

As of writing, the latest gcc and binutils versions are 10.2.0 and 2.35 respectively. If you want a different version, replace the `BINUTILSVERSION` and `GCCVERSION` variables in the same `install.sh` script.

**Note:** Don't run this script as superuser. Running the script will require a stable internet connection and a cup of coffee because it takes a while ;)
