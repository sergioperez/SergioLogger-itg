#include <iostream>
#include <curl/curl.h>
#include <cstdlib>
#include <cstdio>
#include "SergioLogger.h"

/*
 * Server Request types:
 *	0 - Insert Coin
 *	1 - Game crash
 *	2 - Service coin
 *	3 - Poweron
 */


SergioLogger* SLOGGER = NULL;

char *logger_ip;
int logger_port;
char *logger_url;
/*char *buffer;
char *buffer2;
*/

SergioLogger::SergioLogger()
{
	//TODO: Use OpenITG log system
	std::cout << "SergioLogger up" << std::endl;
	if(logger_ip = std::getenv("ITG_LOGGER_IP"))
	{
		std::cout << "\tGot logger at:" << logger_ip << std::endl;
	}
	else
	{
		std::cout << "ITG logger fail" << std::endl;
	}

	//TODO: Possible memory leak?
	char *buffer;
	if(buffer = std::getenv("ITG_LOGGER_PORT"))
	{
		logger_port = std::atoi(buffer);
		std::cout << "\tGot logger port: " << logger_port << std::endl;
	}
	else
	{
		std::cout << "ITG logger port failed" << std::endl;
	}

	//buffer = new char[80];
	//buffer2 = new char[80];
	//buffer2[0] = 0;

	logger_url = (char*)calloc(45, sizeof(char));
	sprintf(logger_url, "http://%s/action", logger_ip);
}

SergioLogger::~SergioLogger()
{
	delete logger_ip;
	delete logger_url;
	//delete buffer;
	//delete buffer2;
	//TODO: Use OpenITG log system
	std::cout << "Closing SergioLogger" << std::endl;
}


int SergioLogger::send_server_request(int type)
{
	CURL *curl;
	CURLcode res;
	// CURL initialization 
	//TODO: Probably better at the constructor
	curl_global_init(CURL_GLOBAL_ALL);
	// Get curl handler 
	curl = curl_easy_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, logger_url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_PORT, logger_port);
		
		switch(type)
		{
			case 0:
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=coin");
				break;
			case 1:
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=crash");
				break;
			case 2:
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=service_coin");
				break;
			case 3:
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=poweron");
				break;
			case 4:
				/*int i = 0;
				while() {
					if(buffer[i] == 0) break;
					else if(buffer[i] == ' ') 
					{
						buffer[i] = '_';
						i++;
					}
					else
					{
						i++;
					} 
				}
				std::sprintf(buffer2, "action=song&song=%s", buffer);
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer2);*/
				
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=song");
				break;
			default:
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "action=unknown");
				break;
		}
	}

	// Perform the request 
	res = curl_easy_perform(curl);

	if(res != CURLE_OK)
	{
		//TODO: Use OpenITG logging system
		// Check for errors 
		fprintf(stderr, "curl_easy_perform() failed:%s\n", curl_easy_strerror(res));

		// Always cleanup 
		curl_easy_cleanup(curl);
	}
	//TODO:Probably better at the destructor
	curl_global_cleanup();
	return 0;
}


int SergioLogger::insert_coin()
{
	send_server_request(0);
	return 0;
}

int SergioLogger::crash()
{
	send_server_request(1);
	return 0;
}

int SergioLogger::service_coin()
{
	send_server_request(2);
	return 0;
}

int SergioLogger::poweron()
{
	send_server_request(3);
	return 0;
}

int SergioLogger::song_start(char *song_name)
{
	//TODO: Send info about the song being played
	send_server_request(4);
	//std::strcpy(buffer, song_name);
	//buffer[25] = 0;
	return 0;
}
