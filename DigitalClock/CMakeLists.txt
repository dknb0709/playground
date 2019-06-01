add_executable(main.out main.cpp)
target_include_directories(main.out
  PUBLIC ${PROJECT_SOURCE_DIR}/TerminalAPI/include
  )
target_link_libraries(main.out
    terminal
  )
