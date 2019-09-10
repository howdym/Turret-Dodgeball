add_library(catch
        src/catch.h
        src/catch-main.cpp ../../../src/controller.cpp ../../../src/controller.h ../../../src/player.h ../../../src/player.cpp ../../../src/view.h ../../../src/view.cpp)
set_property(TARGET catch PROPERTY CXX_STANDARD 14)
set_property(TARGET catch PROPERTY CXX_STANDARD_REQUIRED On)
target_include_directories(catch PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
