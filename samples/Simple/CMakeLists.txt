find_package(lua 5.3 REQUIRED)

set(SIMPLE_SOURCES
  main.cpp
)

add_executable(Simple ${SIMPLE_SOURCES})
add_dependencies(Simple Dotnet Resources)
target_link_libraries(Simple
  PRIVATE
    Engine
    lua::lua
)

add_custom_command(
  TARGET Simple POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Dotnet>
    $<TARGET_FILE_DIR:Simple>/dotnet
)

#this is pure hacky hotfix goodness. We need to figure out a better way to do this in the future.
if(WIN32)
  add_custom_command(
    TARGET Simple POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
      $<TARGET_FILE_DIR:Simple>/dotnet/nethost.dll
      $<TARGET_FILE_DIR:Simple>
  )
endif()

add_custom_command(
  TARGET Simple POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Resources>
    $<TARGET_FILE_DIR:Simple>/Resources
)

add_custom_command(
  TARGET Simple POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:Engine>
    $<TARGET_FILE_DIR:Simple>
)
