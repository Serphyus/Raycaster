<h1 align="center">
    Raycaster
</h1>

This project is a game dev practice for raycasting lines and detecting
collition with static shapes. The rays cast is calculated in steps of
spesific distances where the first collition it detects will stop it's
iterations and go to the next until all lines have been cast.

## Simulation demo
<div align="center">
    <img src="/media/demo.gif" height="400">
</div>


## Requirements
- CMake
- G++ (GNU C++ Compiler)


## Setup

clone main repo and external repos
```
git clone https://github.com/Serphyus/Raycaster.git
cd Raycaster
git submodule update --init --recursive
```

configure make files

*windows*
```
./configure.bat
```

*Unix*
```
./configue.sh
```

build the program
```
cd build
make
```


## Usage

run the Raycaster executable located in Raycaster/build

*Windows*
```
cd Raycaster/build
./Raycaster.exe
```

*Unix*
```
cd Raycaster/build
./Raycaster
```