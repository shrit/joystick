cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
## Specify your project's name
project(Joystick)

# Enable strict handling of warnings

add_definitions(" -fPIC -O0 -g ")

# Set moc compilling for qt 
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Specfiy a list of source files .

set ( SOURCES  
  main.cc
  joystick.cc
  )

# Specify include directories
include_directories(

  /usr/include/

  # ... any other header files
  )


set(pthread_lib "/usr/lib/libpthread.so")


add_executable(Joystick
  
 ${SOURCES}  
  # ... any other source files
  )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


# Specify your app's executable name and a list of linked libraries
target_link_libraries(Joystick  

  ${pthread_lib}
  
  )



