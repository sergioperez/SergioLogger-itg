#include "SergioLogger.h"

int main() {
	SLOGGER = new SergioLogger;
	SLOGGER->insert_coin();
	SLOGGER->crash();
	SLOGGER->service_coin();
	return 0;
}
