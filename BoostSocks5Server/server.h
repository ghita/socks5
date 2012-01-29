#pragma once
#include "stdafx.h"

class Server
{
public:
	Server(ba::io_service& ioService, int port);

	void Session(socket_ptr sock, const boost::system::error_code& error);

private:
	void StartAccept();

	bool HandleHandshake(socket_ptr& socket, char* buffer);
	bool HandleRequest(socket_ptr& socket, char* buffer); 
	void DoProxy(socket_ptr& client, socket_ptr& conn, char* buffer);

	void HandleProxyRead(const boost::system::error_code& error,
      size_t bytes_transferred, socket_ptr& conn);

private:
	ba::io_service& ioService_;
	int port_;
	ba::ip::tcp::acceptor acceptor_;
};


class ProxySession
{
public:
	ProxySession(ba::io_service& ioService, socket_ptr socket, socket_ptr remoteSock);
	void Start();

private:
	void HandleClientProxyRead(const boost::system::error_code& error,
      size_t bytes_transferred);
	void HandleRemoteProxyRead(const boost::system::error_code& error,
		size_t bytes_transferred);

	void HandleRemoteProxyWrite(const boost::system::error_code& error);
	void HandleClientProxyWrite(const boost::system::error_code& error);

private:
	socket_ptr socket_;
	socket_ptr remoteSock_;
	ba::io_service& ioService_;
  enum { max_length = 10000 };
  char dataClient_[max_length];
  char dataRemote_[max_length];
};