# include "../headers/libunixsocket.h"
# include "../headers/exception.hpp"
# include "../headers/unixdgram.hpp"

# include <sys/types.h>
# include <sys/socket.h>

# include <string>
/*
The committers of the libsocket project, all rights reserved
(c) 2012, dermesser <lbo@spheniscida.de>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
	disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
	disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

/*
 * DESCRIPTION FOR UNIXSERVERDGRAM.CPP
 * 	Class for UNIX domain datagram servers - or -
 * 	a not connect()-able unix_dgram_client class.
 */

# include "../headers/unixserverdgram.hpp"

namespace libsocket
{
	using std::string;

	unix_dgram_server::unix_dgram_server(void)
		: bound(false)
	{ }

	unix_dgram_server::unix_dgram_server(const char* bindpath, int socket_flags)
	{
		setup(bindpath,socket_flags);
	}

	unix_dgram_server::unix_dgram_server(const string& bindpath, int socket_flags)
	{
		setup(bindpath.c_str(),socket_flags);
	}

	void unix_dgram_server::setup(const char* bindpath, int socket_flags)
	{
		if ( sfd != -1 )
			throw socket_exception(__FILE__,__LINE__,"unix_dgram_server::setup: Already set up!\n");

		sfd = create_unix_server_socket(bindpath, DGRAM, socket_flags);

		_path.assign(bindpath);

		if ( sfd < 0 )
			throw socket_exception(__FILE__,__LINE__,"unix_dgram_server::setup: Could not create server!\n");

		bound = true;
	}

	void unix_dgram_server::setup(const string& bindpath, int socket_flags)
	{
		setup(bindpath.c_str(),socket_flags);
	}
}
