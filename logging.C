#include <logging.h>
#include <fstream>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


//FILE * Logger::logger = fopen("file.txt", "w");

FILE* Logger::logger = NULL;

void Logger::LogEvent(const char *event){
	
	//printf("i got here");


	//ofstream logger;

	//ofstream logger("logfile.txt", ios_base::app | ios_base::out);
	//*logger("logfile.txt", ios_base::app | ios_base::out);
	if (logger == NULL){
		logger = fopen("logger.txt", "w");}
	
	//outputFile.open("output", ios::binary);


	//logger << event << endl;
	//logger.fwrite("file.txt", event);
	
	fprintf(logger, "%s\n", event);
	

	


}


void Logger::Finalize(){

	fclose(logger);
	//*logger->close(); //both dont work

}


DataFlowException::DataFlowException(const char *type, const char *error){


		char msg[1024];
		sprintf(msg, "Throwing exception (%s): %s", type, error);
		Logger::LogEvent(msg);
		

}
