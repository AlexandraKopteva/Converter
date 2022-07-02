cmake_minimum_required(VERSION 3.1)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0037 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE "Debug")

project(Converter)

#оптимицация
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TOOL Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O1")

#MSVC
if (MSVC)
    if (CMAKE_BUILD_TYPE EQUAL "Debug")
        set(Boost_USE_STATIC_RUNTIME OFF)
    endif()
endif()

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Xml)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp*")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")
file(GLOB FORMS "${CMAKE_CURRENT_SOURCE_DIR}/forms/*.ui")
file(GLOB RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resourse/*.*")

qt5_wrap_ui(WRAP_FORMS ${FORMS} )
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${WRAP_FORMS} ${RESOURCE})

target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/forms"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/resourse"
	)

if(Converter_TESTING)
    add_subdirectory(test)
    message(STATUS "Тестировние проекта Converter включено")
elseif(IS_SUBPROJECT)
    message(STATUS " Converter не тестируется в режиме подмодуля")
endif()
	
target_link_libraries(${PROJECT_NAME}
                 PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml )
#Doxygen		 
find_package(Doxygen)
  
set(SMPO_DOCS_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/docs")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)

add_custom_command(
    OUTPUT "${SMPO_DOCS_OUTPUT}"
    COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    VERBATIM
    )
add_custom_target(
    doc ALL
    DEPENDS "${SMPO_DOCS_OUTPUT}"
    VERBATIM)