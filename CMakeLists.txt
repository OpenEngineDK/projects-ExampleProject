# Project name. Should be the same as the project directory name and
# will become the name of the binary target.
SET( PROJECT_NAME "ExampleProject")

# Project source code list
SET( PROJECT_SOURCES
  # Add all the cpp source files here
  main.cpp
)

# Include needed to use SDL under Mac OS X
IF(APPLE)
  SET(PROJECT_SOURCES ${PROJECT_SOURCES}  ${SDL_MAIN_FOR_MAC})
ENDIF(APPLE)

# Project executable
ADD_EXECUTABLE(${PROJECT_NAME}
  ${PROJECT_SOURCES}
)

# Project dependencies
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
  # Core library dependencies
  OpenEngine_Core
  OpenEngine_Logging
  OpenEngine_Display
  OpenEngine_Devices
  OpenEngine_Scene
  # Extension dependencies
  Extensions_SDL
  Extensions_SetupHelpers  
)
