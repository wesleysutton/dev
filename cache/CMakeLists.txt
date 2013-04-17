cmake_minimum_required (VERSION 2.6)

project(distcache)

set (THIRDPARTY_HOME "/Users/wsutton/dev/thirdparty")

#macro add_thirdparty(name version)
#endmacro

set (BOOST_HOME "${THIRDPARTY_HOME}/boost_1_53_0")
set (BOOST_INC "${BOOST_HOME}/include")
set (BOOST_LIB "${BOOST_HOME}/lib")

set (LOG4CXX_HOME "${THIRDPARTY_HOME}/log4cxx-0.10.0")
set (LOG4CXX_INC "${LOG4CXX_HOME}/include")
set (LOG4CXX_LIB "${LOG4CXX_HOME}/lib")

set (PROTOBUF_HOME "${THIRDPARTY_HOME}/protobuf-2.5.0")
set (PROTOBUF_INC "${PROTOBUF_HOME}/include")
set (PROTOBUF_LIB "${PROTOBUF_HOME}/lib")

set (ZEROMQ_HOME "${THIRDPARTY_HOME}/zeromq-3.2.2")
set (ZEROMQ_INC "${ZEROMQ_HOME}/include")
set (ZEROMQ_LIB "${ZEROMQ_HOME}/lib")

add_subdirectory(src/transport)
#add_subdirectory(test)

