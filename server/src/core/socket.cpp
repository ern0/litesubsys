#include "socket.h"
#include "logger.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sstream>

static const int PACKAGE_SIZE = 80;

namespace com_c
{
namespace netw
{

BaseSocket::BaseSocket(int socketId)
    : mSocketId(socketId)
{
    DEBUGLOGGING << __INFO__;
    if(mSocketId == -1)
    {   
        std::ostringstream wErrStream;
        wErrStream 
        << __INFO__ << std::endl
        << "BaseSocket socket = -1 " << std::endl
        << "Erno: " << errno << std::endl;
        ERRORLOGGING << wErrStream.str();
        throw std::runtime_error("bad socket: " + std::to_string(errno));
    }
}


BaseSocket::~BaseSocket()
{
    DEBUGLOGGING << __INFO__;
    if(mSocketId == mInvalidSocketId)
    {
        // this object has been closed or moved
        return;
    }

    try
    {
        close();
    }
    catch(...)
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "Close error";
        // TODO: error
    }
}

void BaseSocket::close()
{
    DEBUGLOGGING << __INFO__;
    if(mSocketId == mInvalidSocketId)
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "socket id is invalid, already closed? " + std::to_string(errno);
    }

    if(mSocketId >=0)
    {
        while(true)
        {
            int state = ::close(mSocketId);
            if(state == mInvalidSocketId)
            {
                break;
            }
            switch(errno)
            {
                case EBADF:
                {
                    ERRORLOGGING << __INFO__;
                    ERRORLOGGING << "close: " + std::to_string(errno);
                }
                case EIO:
                {
                    ERRORLOGGING << __INFO__;
                    ERRORLOGGING << "close: EIO " + std::to_string(errno);
                    throw std::runtime_error("close: EIO:  " + std::to_string(errno));
                }
                case EINTR:
                {
                        // TODO: Check for user interrupt flags.
                        //       Beyond the scope of this project
                        //       so continue normal operations.
                break;
                }
                default:
                {
                    INFOLOGGING << __INFO__;
                    INFOLOGGING << errno;
                    throw std::runtime_error("close: ???:  " + std::to_string(errno));
                }
            }
        }
    }
    mSocketId = mInvalidSocketId;
}

void BaseSocket::swap(BaseSocket& other) noexcept
{
    DEBUGLOGGING << __INFO__;
    std::swap(mSocketId,   other.mSocketId);
}

BaseSocket::BaseSocket(BaseSocket&& move) noexcept
    : mSocketId(mInvalidSocketId)
{
    DEBUGLOGGING << __INFO__;
    move.swap(*this);
}

BaseSocket& BaseSocket::operator=(BaseSocket&& move) noexcept
{
    DEBUGLOGGING << __INFO__;
    move.swap(*this);
    return *this;
}

const char* BaseSocket::getLocalAddress()// throw()
{
    DEBUGLOGGING << __INFO__;
    struct sockaddr_in addr;
    // Address to accept any incoming messages.
    //serverAddr.sin_addr.s_addr  = htons(INADDR_ANY);fe
    addr.sin_addr.s_addr = INADDR_ANY;
    unsigned int addr_len = sizeof(addr);

    if(getsockname(mSocketId, (sockaddr *) &addr, (socklen_t *) &addr_len))
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "Fetch of local address failed getsockname";
        //throw
        //return inet_ntoa(((in_addr_t)INADDR_ANY));
    }
    return inet_ntoa(addr.sin_addr);
}

UDPSocket::UDPSocket(int port)
    : BaseSocket(::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))
{
    DEBUGLOGGING << __INFO__;
    INFOLOGGING << "Server socket port: " + std::to_string(port) + " address:" + getLocalAddress();
    struct sockaddr_in serverAddr;
    //bzero((char*)&serverAddr, sizeof(serverAddr));
    memset((char*)&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family       = AF_INET;
    serverAddr.sin_port         = htons(port);
    serverAddr.sin_addr.s_addr  = INADDR_ANY;
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //serverAddr.sin_addr.s_addr = inet_addr(getLocalAddress());

    struct timeval tv;
    tv.tv_sec = 100;
    tv.tv_usec = 100000;

    int on = 1;

    //if(setsockopt(getSocketId(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    // allow socket descript to be reusable
    if(setsockopt(getSocketId(), SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0)
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "Error when set time out setsickopt.";
        close();
        exit(-1);
    }

    /// Set socket to be nonblocking. All the sockets for the incoming connections
    /// will also be nonblocking since hey will inherit that state from the listening socket
    /*
    if(ioctl(getSocketId(), FIONBIO, (char *) &on) < 0)
    {
        ERRORLOGGING << fmt::format("{} {}", __INFO__,"Error when set ioctl.");
        close();
        exit(-1);
    }*/

    if (::bind(getSocketId(), (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "Bind: " + std::to_string(errno);
        throw std::runtime_error("Bind: " + std::to_string(errno));
        close();
        exit(-1);
    }

}

std::size_t UDPSocket::getMessageData(char* buffer, std::size_t size)
{
    //DEBUGLOGGING << __INFO__;
    if (getSocketId() == 0)
    {
        ERRORLOGGING << __INFO__;
        ERRORLOGGING << "accept called on a bad socket object (this object was moved)";
        return -1;
    }

    std::size_t get = recv(getSocketId(), buffer, size, MSG_DONTWAIT);

    if (get == static_cast<std::size_t>(-1))
    {
        switch(errno)
        {
            // async like work, MSG_DONTWAIT, no we didn't recieve anything
            case EAGAIN:
                //INFOLOGGING << "EGAIN";
                get = 0;
                return 0;//break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENXIO:
            {
                // Fatal error. Programming bug
                ERRORLOGGING << __INFO__;
                ERRORLOGGING << "read: critical error: " + std::to_string(errno);
                throw std::runtime_error("read: critical error: " + std::to_string(errno));
                return 0; //break;
            }
            case EIO:
            case ENOBUFS:
            case ENOMEM:
            {
                // Resource acquisition failure or device error
                ERRORLOGGING << __INFO__;
                ERRORLOGGING << "read: resource failure: " + std::to_string(errno);
                throw std::runtime_error("read: resource failure: " + std::to_string(errno));                    
                return 0; //break;
            }
            case EINTR:
                // TODO: Check for user interrupt flags.
                //       Beyond the scope of this project
                //       so continue normal operations.
            case ETIMEDOUT:
            //  case EAGAIN:
            {
                // Temporary error.
                // Simply retry the read.
                ERRORLOGGING << __INFO__;
                ERRORLOGGING << "EINTR, ETIMEDOUT, EAGAIN: " + std::to_string(errno);
                return 0; //continue;
            }
            case ECONNRESET:
            case ENOTCONN:
            {
                // Connection broken.
                // Return the data we have available and exit
                // as if the connection was closed correctly.
                ERRORLOGGING << __INFO__;
                DEBUGLOGGING << "Connection broken" + std::to_string(errno);
                get = 0;
                return 0; //break;
            }
            default:
            {
                ERRORLOGGING << __INFO__;
                ERRORLOGGING << "read: returned -1"  + std::to_string(errno);
                get = 0;
            }
        }
    }

    return get;
}


void UDPSocket::Listen()
{
    DEBUGLOGGING << __INFO__;
    INFOLOGGING << "Listening.";
   
    while(true)
    {
        // This outer loop handles resizing of the message when we run of space in the string.
        char buffer[PACKAGE_SIZE];
        memset(buffer, 0, sizeof(buffer));

        std::size_t got = getMessageData(buffer, PACKAGE_SIZE);//, [](std::size_t){return false;});

        if(0 < got)
        {

            INFOLOGGING << "Datarecieved: ";
            INFOLOGGING << buffer;

            //Packet packet(buffer);
            for(int i=0; i<got; ++i)
            {
                if(i != 0 && i%8 == 0)
                {
                    std::cout << std::endl;
                }
                std::cout << "%02x " << static_cast<unsigned char>(buffer[i]);
            }
            std::cout << std::endl;
        }
    }
}

} // netw
} // com_c