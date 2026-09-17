# CMakeLists.txt - Explanation Guide

**Purpose:** This file tells the CMake build system how to compile our C++ code, link the Qt libraries, and bundle our QML files into the final executable programs.

### Complete Code & Line-by-Line Explanation

```cmake
# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.16)

# Define the project name and specify we are using C++ (CXX)
project(AutomotiveCluster VERSION 1.0 LANGUAGES CXX)

# REQUIREMENT: JD asks for C++17/C++20. Here we force the compiler to use C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt specific settings to automatically handle Qt's special macros (like Q_OBJECT)
set(CMAKE_AUTOMOC ON) # Auto-generates C++ code for Signals and Slots
set(CMAKE_AUTORCC ON) # Auto-compiles Qt Resource files (.qrc)
set(CMAKE_AUTOUIC ON) # Auto-compiles Qt UI files (not used here, but standard)

# Find the Qt libraries on your computer. We need Core, Quick (for QML), Gui, and Network (for IPC sockets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Gui Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Gui Network)

# List all the C++ source files for the GUI Dashboard application
set(CLUSTER_SOURCES
    src/main.cpp
    src/viewmodels/ClusterViewModel.cpp
    src/viewmodels/ClusterViewModel.h
    src/services/CanSimulator.cpp
    src/services/CanSimulator.h
)

# List all the C++ source files for the Background IPC Server
set(SERVICE_SOURCES
    src/VehicleServiceMain.cpp
    src/services/MockCanServer.cpp
    src/services/MockCanServer.h
)

# Qt6/Qt5 specific target setup
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # 1. Create the Automotive Cluster (GUI Client) executable
    qt_add_executable(AutomotiveCluster
        MANUAL_FINALIZATION
        ${CLUSTER_SOURCES}
    )
    
    # List the QML UI files
    set(QML_FILES
        qml/main.qml
        qml/Speedometer.qml
    )
    
    # Fix Qt6 warnings about QML folder structures
    if(COMMAND qt_policy)
        qt_policy(SET QTP0001 NEW)
        qt_policy(SET QTP0004 OLD)
    endif()

    # Embed the QML files directly into the executable binary using the Qt Resource System
    qt_add_qml_module(AutomotiveCluster
        URI ClusterApp
        VERSION 1.0
        QML_FILES ${QML_FILES}
    )

    qt_import_qml_plugins(AutomotiveCluster)
    qt_finalize_executable(AutomotiveCluster)
    
    # 2. Create the Vehicle Service (Background IPC Server) executable
    qt_add_executable(VehicleService ${SERVICE_SOURCES})

else()
    # Qt5 fallback alternative (same logic as above, just older CMake syntax)
    add_executable(AutomotiveCluster ${CLUSTER_SOURCES})
    target_link_libraries(AutomotiveCluster PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Network)
    
    add_executable(VehicleService ${SERVICE_SOURCES})
    target_link_libraries(VehicleService PRIVATE Qt5::Core Qt5::Network)
endif()

# Link the actual Qt libraries to the AutomotiveCluster executable so it can use them
target_link_libraries(AutomotiveCluster PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
)

# Link the Qt libraries to the VehicleService executable
target_link_libraries(VehicleService PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)
```

