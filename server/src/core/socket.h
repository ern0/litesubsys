#pragma once

#include <vector>


namespace com_c
{
namespace netw
{

class BaseSocket
{
public:
    virtual ~BaseSocket();

    // Movable but not Copyable
    BaseSocket(BaseSocket&& move) noexcept; 
    BaseSocket& operator=(BaseSocket&& move) noexcept;
    void swap(BaseSocket& other) noexcept;
    BaseSocket(BaseSocket const&) = delete;
    BaseSocket& operator=(BaseSocket const&) = delete;

    // can manually call close
    void close();

private:
    int mSocketId;

protected:
    static constexpr int mInvalidSocketId = -1;

    BaseSocket(int socketId);
    int getSocketId() const { return mSocketId; }
    const char *getLocalAddress();
};

class UDPSocket : BaseSocket
{
public:
    UDPSocket(int port);
    void Listen();

    std::size_t getMessageData(char *localBuffer, std::size_t size);
    void putMessageData(char const* buffer, std::size_t size);

}; // UDPSocket
} // netw
} // com_c