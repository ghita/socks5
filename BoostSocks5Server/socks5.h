#pragma once
#include "stdafx.h"


//data structures as defined by socks 5 protocol RFC 1928
class MethodIdentification
{
public:
    MethodIdentification(): version_(), nmethods_() {};

    boost::array<boost::asio::mutable_buffer, 2> buffers()
    {
        boost::array<boost::asio::mutable_buffer, 2> bufs =
        {
            {
                boost::asio::buffer(&version_, 1),
                boost::asio::buffer(&nmethods_, 1)
            }
        };

        return bufs;
    }

    bool Success() const
    {
        return (version_ == 5);
    }

    unsigned char Nmethods() { return nmethods_; }

private:
    unsigned char version_;
    unsigned char nmethods_;
};

class MethodSelectionPacket
{
public:
    MethodSelectionPacket(unsigned char met): version(5), method(met) {}

    boost::array<boost::asio::mutable_buffer, 2> buffers()
    {
        boost::array<boost::asio::mutable_buffer, 2> bufs =
        {
            {
                boost::asio::buffer(&version, 1),
                boost::asio::buffer(&method, 1)
            }
        };

        return bufs;
    }

public:
    unsigned char version;
    unsigned char method;
};

class SOCKS5RequestHeader
{
public:
    enum commandType
    {
        connect = 0x1,
        bind    = 0x2,
        udp_associative = 0x3
    };

    enum addressingType
    {
        atyp_ipv4 = 0x1,
        atyp_dname = 0x3,
        atyp_ipv6 = 0x4
    };

    SOCKS5RequestHeader(): version_(), cmd_(), rsv_(), atyp_()  {}

    boost::array<boost::asio::mutable_buffer, 4> buffers()
    {
        boost::array<boost::asio::mutable_buffer, 4> bufs =
        {
            {
                boost::asio::buffer(&version_, 1),
                boost::asio::buffer(&cmd_, 1),
                boost::asio::buffer(&rsv_,1),
                boost::asio::buffer(&atyp_,1)
            }
        };

        return bufs;
    }

    bool Success() const
    {
        return (version_ == 5) && (cmd_ == connect) && ( rsv_ == 0);
    }

    unsigned char Atyp() { return atyp_; }

public:
    unsigned char version_;
    unsigned char cmd_;
    unsigned char rsv_;
    unsigned char atyp_;
};

class SOCK5IP4RequestBody
{
public:
    SOCK5IP4RequestBody(): ipDst_(), port_() {}

    boost::array<boost::asio::mutable_buffer, 2> buffers()
    {
        boost::array<boost::asio::mutable_buffer, 2> bufs =
        {
            {
                boost::asio::buffer(&ipDst_, 4),
                boost::asio::buffer(&port_, 2),
            }
        };

        return bufs;
    }

    unsigned int IpDst() { return ipDst_; };
    unsigned short Port() { return port_; }

private:
    unsigned int ipDst_;
    unsigned short port_;
};


/* Responses */
#define RESP_SUCCEDED       0
#define RESP_GEN_ERROR      1

class SOCK5Response
{
public:
	SOCK5Response(bool succeded = true) : version(5), cmd(succeded ? RESP_SUCCEDED : RESP_GEN_ERROR),
		rsv(0), atyp(SOCKS5RequestHeader::addressingType::atyp_ipv4) {}

    boost::array<boost::asio::mutable_buffer, 6> buffers()
    {
        boost::array<boost::asio::mutable_buffer, 6> bufs =
        {
            {
                boost::asio::buffer(&version, 1),
                boost::asio::buffer(&cmd, 1),
				boost::asio::buffer(&rsv, 1),
				boost::asio::buffer(&atyp, 1),
				boost::asio::buffer(&ipSrc, 4),
                boost::asio::buffer(&portSrc, 2),

            }
        };

        return bufs;
    }

public:
    unsigned char version;
    unsigned char cmd;
	unsigned char rsv;
	unsigned char atyp;
	unsigned int ipSrc;
	unsigned short portSrc;
};