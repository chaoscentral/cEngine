# cEngine
My first attempt at an open source game engine. This is going to be a journey! I am also learning how to use git properly so bear with me. This is based off of TheCherno's wonderful video series on Game Engine creation. Check out his current repo for the Hazel engine (https://github.com/theCherno/Hazel). Right now it is mostly the same but there is a divergence planned once the skeleton is in place

# How to build
**Prerequisites**
* Git
* Visual Studio 2017

Open a command prompt window int the directory where you want to create the cEngine sub folder and enter the following commands

    git clone https://github.com/chaoscentral/cEngine.git
    cd cEngine
    git submodule init
    git submodule update
    
This will clone the cEngine repo to your local machine as well as initialize and clone any dependant submodules

# Current Issues
Depending on your system you may or may not needd to change the "OpenGL32.lib" include in the premake5.lua script. apparently it is case sensitive so it may have to change to "opengl32.lib" if you are getting linking errors.
