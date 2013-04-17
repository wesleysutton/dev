#ifndef __IoService_h__
#define __IoService_h__

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <string>

class IoService 
  : private boost::noncopyable
{
  public:
    static const String DEFAULT_SERIALIZER;
    typedef boost::function<void ()> Handler;

    IoService(uint8_t threads = 1);
    virtual ~IoService();

    boost::asio::io_service& io_service() { return m_ioService; }

    void asyncCall(Handler cbHandler,
                   uint32_t delayInSecs = 0,
                   bool serialize = false,
                   const String& serializerName = DEFAULT_SERIALIZER);

    void setThreadCount(uint8_t nbThreads);
      
  private:
    void join();

    boost::asio::io_service m_ioService;
    boost::shared_ptr<boost::asio::io_service::work> m_work;
    boost::thread_group m_threadGroup;

    typedef std::map<String, boost::asio::strand*> StrandMap;
    StrandMap m_mapStrand;

    ACE_Recursive_Thread_Mutex  m_threadConfigMutex;
    ACE_Recursive_Thread_Mutex  m_strandMutex;

    SC_LOGGER_DECLARE (s_plog);
};

#endif // __IoService_h__

