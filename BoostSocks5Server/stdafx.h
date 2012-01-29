// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//bost asio specific headers or dependencies
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>


#include <iostream>
#include <string>
#include <boost/array.hpp>

#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ba=boost::asio;
namespace bs=boost::system;

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;

// TODO: reference additional headers your program requires here
