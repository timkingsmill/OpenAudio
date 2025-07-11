# CMake

## The JUCE Library

### Using `find_package`

To install JUCE globally on your system, you'll need to tell CMake where to
place the installed files.

    # Go to JUCE directory
    cd /path/to/clone/JUCE
    # Configure build with library components only
    cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX=/path/to/JUCE/install
    # Run the installation
    cmake --build cmake-build-install --target install

In your project which consumes JUCE, make sure the project CMakeLists.txt contains the line
`find_package(JUCE CONFIG REQUIRED)`. This will make the JUCE modules and CMake helper functions
available for use in the rest of your build. Then, run the build like so:

    # Go to project directory
    cd /path/to/my/project
    # Configure build, passing the JUCE install path you used earlier
    cmake -B cmake-build -DCMAKE_PREFIX_PATH=/path/to/JUCE/install
    # Build the project
    cmake --build cmake-build
