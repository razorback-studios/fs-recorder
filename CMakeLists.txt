cmake_minimum_required(VERSION 3.16)

set(SIMCONNECT_PATH "" CACHE STRING "Location of the SimConnect API root folder")

project(FSRecorder VERSION 0.1 LANGUAGES CXX)

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
    SOURCES Systems/SimConnectClient/SimConnectWorker.hpp Systems/SimConnectClient/SimConnectWorker.cpp
    SOURCES Systems/SimConnectClient/SimConnectManager.hpp Systems/SimConnectClient/SimConnectManager.cpp
)

qt_add_resources(appFSRecorder imageresources
    FILES
        Assets/Vector.png
)

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

target_link_directories(appFSRecorder
    PRIVATE ${SIMCONNECT_PATH}\\lib
)

target_link_libraries(appFSRecorder
    PRIVATE Qt6::Quick SimConnect
)

target_include_directories(appFSRecorder
    PRIVATE Systems/Recording ${SIMCONNECT_PATH}\\include Systems/SimConnectClient
)

target_compile_definitions(appFSRecorder
    PRIVATE WIN32_LEAN_AND_MEAN
)

include(GNUInstallDirs)
install(TARGETS appFSRecorder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
