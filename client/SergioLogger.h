#ifndef SergioLogger_H
#define SergioLogger_H

#include <cstdlib>

class SergioLogger
{
	public:
		SergioLogger();
		~SergioLogger();
		int insert_coin();
		int service_coin();
		int crash();
		int poweron();
		int song_start(char *song_name);
	private:
		int send_server_request(int type);
};

extern SergioLogger* SLOGGER;

#endif
