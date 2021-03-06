/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "remote_command.h"
#include <unistd.h>
#include<fcntl.h>


void
remote_command_1(char *host, char* commandName, int parametersNumber, char** parameters, char* stdinBuff)
{
	CLIENT *clnt;
	commandOutput  *result_1 = (commandOutput*)malloc(sizeof(commandOutput));
	commandData  rexec_1_arg;

	rexec_1_arg.commandName = commandName;
	rexec_1_arg.commandId = "";
	rexec_1_arg.packetNum = 0;
	rexec_1_arg.stdinBuf = stdinBuff;
	rexec_1_arg.parameters.parameters_len = parametersNumber;
	rexec_1_arg.parameters.parameters_val = (parameter*)malloc(sizeof(parameter)*parametersNumber);
	for (int i=0; i< parametersNumber; i++) {
		rexec_1_arg.parameters.parameters_val[i] = parameters[i];
	}


#ifndef	DEBUG
	clnt = clnt_create (host, REMOTE_COMMAND, Remote, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = rexec_1(&rexec_1_arg, clnt);
	if (result_1 == (commandOutput *) NULL) {
		clnt_perror (clnt, "call failed");
		exit(1);
	}

	commandOutput *results = (commandOutput*)malloc(result_1->packetCount*sizeof(commandOutput));
	results[result_1->packetNum] = *result_1;

	for (int i=0; i<result_1->packetCount-1 ; i++){
		rexec_1_arg.packetNum++;
		commandOutput  *result = rexec_1(&rexec_1_arg, clnt);
		results[result->packetNum] = *result;
	}

	for (int i=0; i<result_1->packetCount; i++){
		fprintf(stdout, "%s", results[i].stdoutBuf);
		fflush(stdout);
	}
	printf("\n");
	for (int i=0; i<result_1->packetCount; i++){
		fprintf(stderr, "%s", results[i].stderrBuf);
		fflush(stderr);
	}
	printf("\n");


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	if (result_1 != NULL)
		exit(result_1->statusCode); // Wyjście ztym samym statusem co wykonywania funkacja
	exit(1);
}

int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 3) {
		printf ("usage: %s: server_host, command_name, parameters\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	char* stdinBuf = (char*)malloc(sizeof(char)* 1024);
	int readSize = 0;
	int stdinBufSize = 0;
	while((readSize = read(STDIN_FILENO, stdinBuf+stdinBufSize, 1024)) > 0)
	{
		stdinBufSize += readSize;
		stdinBuf = (char*)realloc(stdinBuf, sizeof(char)* (stdinBufSize+1024));
	}
	stdinBuf[stdinBufSize] = 0;
	remote_command_1 (host, argv[2], argc-3, argv+3, stdinBuf);
	exit (0);
}
