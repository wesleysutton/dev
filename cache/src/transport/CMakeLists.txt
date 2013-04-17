# protoc --proto_path=src --cpp_out=cpp src/core.proto 

include_directories(
  src/transport
  ${BOOST_INC}
  ${LOG4CXX_INC}
  ${ZEROMQ_INC}
)

link_directories(
  ${BOOST_LIB}
  ${LOG4CXX_LIB}
  ${ZEROMQ_LIB}
)

add_executable(
  test_mcast
    BufferPool.cpp
    test_BufferPool.cpp 
)

add_executable(
  test_ZmqClient
    test_ZmqClient.cpp
)

add_executable(
  test_ZmqServer
    test_ZmqServer.cpp
)

#add_dependencies( 
#  test_mcast
#    b
#)

