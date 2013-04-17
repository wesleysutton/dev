#ifndef __MulticastTransport_h__
#define __MulticastTransport_h__

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <log4cxx/logger.h>
#include "TypeDefs.h"
#include "IoService.h"
#include "BufferPool.h"
#include "Message.h"

class MulticastTransport
  : boost::noncopyable
  , Message::Sender
{
public:
    class Callback
    {
        virtual ~Callback() {}
        virtual void onByteBuffer(const ByteBuffer&) = 0;
    };

    MulticastTransport(IOService& ios, * receiver)
      : _ios(ios)
      , _bufferPool()
      , _receiver(receiver)
    {
    }

    virtual ~MulticastTransport()
    {
      // TODO: clean shutdown
    }

    void start()
    {
      listen();
    }

    bool send(const ByteBuffer& buffer)
    {
        try
        {
            size_t bytesSent = m_socket.send_to(
                boost::asio::buffer(buffer.data(), buffer.size()),
                _endpoint
            );
            return (bytesSent == buffer.size());
        }
        catch (const boost::system::error_code& error)
        {
            LOG4CXX_ERR(s_plog, "send exception: " << error);
        }
        catch (...)
        {
            LOG4CXX_ERR(s_plog, "unknown send exception");
        }
        return false;
    }

    void cancelReceive();

private:
    void listen()
    {
        ByteBuffer::Ptr buffer = BufferPool::instance()->getByteBuffer();

        assert(buffer); // TODO:

        _socket.async_receive_from(
            boost::asio::buffer(buffer->data(), buffer->size()),
            _endpoint,
            boost::bind(
                &MulticastTransport::onReceive,
                shared_from_this(),
                boost::asio::placeholders::error,
                buffer,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

    void onReceive(const boost::system::error_code& error, ByteBuffer::Ptr buffer, size_t bytesRecvd)
    {
        if (error)
        {
            LOG4CXX_ERR(s_plog, _T("onReceive error: ") << error);
            if (error.value() != boost::system::errc::resource_unavailable_try_again)
            {
                return;
            }
        }
        else if (_decoder && bytesRecvd > 0)
        {
            asyncCall(boost::bind(&MulticastTransport::onDecode, this, buffer));
        }

        listen();
    }

    void onDecode(const ByteBuffer::Ptr buffer)
    {
        if(!_callback)
           return;

	BufferStream input(buffer);
        Message::Ptr msg(new Message);

        if (!msg->ParseFromIstream(&input))
        {
            LOG4CXX_ERROR(_log, "Failed to decode message");
            return;
        }

        // TODO: Measure/restrict callback time.
        _receiver->onMessage(msg);
    }


private:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _endpoint;
    Receiver _encoder;

public:
    static log4cxx::LoggerPtr _log;
/** TODO:
log4cxx::LoggerPtr MulticastTransport::_log = log4cxx::LogManager::getLogger("transport.mcast_src");
*/
};

#endif // __MulticastTransport_h__
