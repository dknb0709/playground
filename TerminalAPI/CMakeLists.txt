file(GLOB SOURCES src/*.cpp)

add_library(terminal
    SHARED ${SOURCES}
  )

target_include_directories(terminal
  PUBLIC ${PROJECT_SOURCE_DIR}/TerminalAPI/include
  )

