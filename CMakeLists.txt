cmake_minimum_required(VERSION 3.16)

project(FSRecorder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.5.2\\msvc2019_64")

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appFSRecorder 
    main.cpp 
    images.qrc
)

qt_add_qml_module(appFSRecorder
    URI FSRecorder
    VERSION 1.0
    QML_FILES Main.qml 
    QML_FILES UI/HomeScreen.qml 
    QML_FILES UI/RecordingIcon.qml
    QML_FILES UI/StopIcon.qml
    QML_FILES UI/Components/PauseButton.qml
    QML_FILES UI/Components/PlayButton.qml
    QML_FILES UI/Components/StatusMessage.qml
    QML_FILES UI/Components/FileMenu.qml
    QML_FILES UI/Components/SimConnectStatus.qml
    SOURCES Systems/Recording/Recording.hpp Systems/Recording/Recording.cpp
)

qt_add_resources(appFSRecorder imageresources
    FILES
        Assets/Vector.png
)

add_library(FSRecorder_AudioAPI STATIC
    Audio/CaptureSession.cpp
    Audio/AudioDevice.cpp
)

add_executable(FSRecorder_AudioAPI_Testing Audio/AudioTestProgram.cpp)
target_link_libraries(FSRecorder_AudioAPI_Testing FSRecorder_AudioAPI)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFSRecorder PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFSRecorder
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFSRecorder
    PRIVATE Qt6::Quick
)

target_include_directories(appFSRecorder
    PRIVATE Systems/Recording
)

include(GNUInstallDirs)
install(TARGETS appFSRecorder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
