# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "teleoperation: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iteleoperation:/home/bashar/catkin_test/src/teleoperation/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Inav_msgs:/opt/ros/kinetic/share/nav_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(teleoperation_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_custom_target(_teleoperation_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "teleoperation" "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(teleoperation
  "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/teleoperation
)

### Generating Services

### Generating Module File
_generate_module_cpp(teleoperation
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/teleoperation
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(teleoperation_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(teleoperation_generate_messages teleoperation_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_dependencies(teleoperation_generate_messages_cpp _teleoperation_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(teleoperation_gencpp)
add_dependencies(teleoperation_gencpp teleoperation_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS teleoperation_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(teleoperation
  "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/teleoperation
)

### Generating Services

### Generating Module File
_generate_module_eus(teleoperation
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/teleoperation
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(teleoperation_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(teleoperation_generate_messages teleoperation_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_dependencies(teleoperation_generate_messages_eus _teleoperation_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(teleoperation_geneus)
add_dependencies(teleoperation_geneus teleoperation_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS teleoperation_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(teleoperation
  "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/teleoperation
)

### Generating Services

### Generating Module File
_generate_module_lisp(teleoperation
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/teleoperation
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(teleoperation_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(teleoperation_generate_messages teleoperation_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_dependencies(teleoperation_generate_messages_lisp _teleoperation_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(teleoperation_genlisp)
add_dependencies(teleoperation_genlisp teleoperation_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS teleoperation_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(teleoperation
  "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/teleoperation
)

### Generating Services

### Generating Module File
_generate_module_nodejs(teleoperation
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/teleoperation
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(teleoperation_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(teleoperation_generate_messages teleoperation_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_dependencies(teleoperation_generate_messages_nodejs _teleoperation_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(teleoperation_gennodejs)
add_dependencies(teleoperation_gennodejs teleoperation_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS teleoperation_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(teleoperation
  "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/teleoperation
)

### Generating Services

### Generating Module File
_generate_module_py(teleoperation
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/teleoperation
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(teleoperation_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(teleoperation_generate_messages teleoperation_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bashar/catkin_test/src/teleoperation/msg/Status.msg" NAME_WE)
add_dependencies(teleoperation_generate_messages_py _teleoperation_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(teleoperation_genpy)
add_dependencies(teleoperation_genpy teleoperation_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS teleoperation_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/teleoperation)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/teleoperation
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(teleoperation_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(teleoperation_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(teleoperation_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/teleoperation)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/teleoperation
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(teleoperation_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(teleoperation_generate_messages_eus nav_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(teleoperation_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/teleoperation)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/teleoperation
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(teleoperation_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(teleoperation_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(teleoperation_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/teleoperation)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/teleoperation
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(teleoperation_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(teleoperation_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(teleoperation_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/teleoperation)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/teleoperation\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/teleoperation
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(teleoperation_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(teleoperation_generate_messages_py nav_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(teleoperation_generate_messages_py geometry_msgs_generate_messages_py)
endif()
