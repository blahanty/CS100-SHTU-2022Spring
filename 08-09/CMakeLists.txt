cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Dawnbreaker")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

#SET(FREEGLUT_REPLACE_GLUT ON CACHE BOOL "" FORCE)

IF(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/third_party/SOIL/"
  "${CMAKE_CURRENT_BINARY_DIR}/SOIL"
  EXCLUDE_FROM_ALL
)

IF (APPLE)
ELSE()
  add_subdirectory(
    "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/"
    "${CMAKE_CURRENT_BINARY_DIR}/freeglut"
    EXCLUDE_FROM_ALL
  )
  set(FREEGLUT_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/include")
ENDIF()


add_library(
  ProvidedFramework
  STATIC
  src/ProvidedFramework/ObjectBase.h
  src/ProvidedFramework/ObjectBase.cpp
  src/ProvidedFramework/WorldBase.h
  src/ProvidedFramework/WorldBase.cpp
  src/ProvidedFramework/GameManager.h
  src/ProvidedFramework/GameManager.cpp
  src/ProvidedFramework/SpriteManager.h
  src/ProvidedFramework/SpriteManager.cpp
  src/utils.h
)

IF (APPLE)
  target_link_libraries(
    ProvidedFramework
    SOIL
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework GLUT"
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC
    src/
    src/ProvidedFramework/
  )
ELSE()
  target_link_libraries(
    ProvidedFramework
    freeglut
    SOIL
  )

  target_include_directories(
    ProvidedFramework
    PUBLIC 
    ${FREEGLUT_INCLUDE_DIR}
    src/
    src/ProvidedFramework/
  )
ENDIF()

add_library(
  PartForYou
  STATIC
  src/PartForYou/GameWorld.h
  src/PartForYou/GameWorld.cpp
  src/PartForYou/GameObjects.h
  src/PartForYou/GameObjects.cpp
  src/utils.h
)

add_library(
  DB
  STATIC
  src/PartForYou/Dawnbreaker.h
  src/PartForYou/Dawnbreaker.cpp
)

add_library(
  Bullet
  STATIC
  src/PartForYou/Bullet.h
  src/PartForYou/Bullet.cpp
  src/PartForYou/RedBullet.h
  src/PartForYou/RedBullet.cpp
  src/PartForYou/BlueBullet.h
  src/PartForYou/BlueBullet.cpp
  src/PartForYou/Meteor.h
  src/PartForYou/Meteor.cpp
)

add_library(
  Decoration
  STATIC
  src/PartForYou/Decoration.h
  src/PartForYou/Decoration.cpp
  src/PartForYou/Star.h
  src/PartForYou/Star.cpp
  src/PartForYou/Explosion.h
  src/PartForYou/Explosion.cpp
)

add_library(
  Goodie
  STATIC
  src/PartForYou/Goodie.h
  src/PartForYou/Goodie.cpp
  src/PartForYou/HPRestoreGoodie.h
  src/PartForYou/HPRestoreGoodie.cpp
  src/PartForYou/PowerUpGoodie.h
  src/PartForYou/PowerUpGoodie.cpp
  src/PartForYou/MeteorGoodie.h
  src/PartForYou/MeteorGoodie.cpp
)

add_library(
  Plane
  STATIC
  src/PartForYou/Plane.h
  src/PartForYou/Plane.cpp
  src/PartForYou/Alphatron.h
  src/PartForYou/Alphatron.cpp
  src/PartForYou/Sigmatron.h
  src/PartForYou/Sigmatron.cpp
  src/PartForYou/Omegatron.h
  src/PartForYou/Omegatron.cpp
)

target_link_libraries(
  PartForYou
  ProvidedFramework
  DB
  Bullet
  Decoration
  Goodie
  Plane
)

target_link_libraries(
  DB
  PartForYou
)

target_link_libraries(
  Bullet
  PartForYou
)

target_link_libraries(
  Decoration
  PartForYou
)

target_link_libraries(
  Goodie
  PartForYou
)

target_link_libraries(
  Plane
  PartForYou
)

target_include_directories(
  PartForYou
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  PartForYou
  ProvidedFramework
  DB
  Bullet
  Decoration
  Goodie
  Plane
)

target_link_libraries(
  ${PROJECT_NAME}
  DB
  PartForYou
)

target_link_libraries(
  ${PROJECT_NAME}
  Bullet
  PartForYou
)

target_link_libraries(
  ${PROJECT_NAME}
  Decoration
  PartForYou
)

target_link_libraries(
  ${PROJECT_NAME}
  Goodie
  PartForYou
)

target_link_libraries(
  ${PROJECT_NAME}
  Plane
  PartForYou
)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/PartForYou/
)
