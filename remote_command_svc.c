/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "remote_command.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
remote_command_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		commandData rexec_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case rexec:
		_xdr_argument = (xdrproc_t) xdr_commandData;
		_xdr_result = (xdrproc_t) xdr_commandOutput;
		local = (char *(*)(char *, struct svc_req *)) rexec_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}

	result = (*local)((char *)&argument, rqstp);

	//UDP - wiele pakietów
	if (result != NULL) {
		commandOutput *resultData = (struct commandOutput*) result;
		int outputBufSize = strlen(resultData->stdoutBuf);
		int errorBufFize = strlen(resultData->stderrBuf)>2048;
		int packetCount = outputBufSize > errorBufFize ? outputBufSize / 2048 : errorBufFize / 2048;

		resultData->packetNum = 0;
		resultData->packetCount = packetCount+1;

		//Podział na wiele pakietów, ustawienie pola z liczbą pakietów w strukturze
		for (int i=0; i<packetCount; i++){
			char r1 = 0, r2 = 0;

			if (outputBufSize > 2048) {
				r1 = resultData->stdoutBuf[2048];
				resultData->stdoutBuf[2048] = 0;
			}
			if (errorBufFize > 2048) {
				r2 = resultData->stderrBuf[2048];
				resultData->stderrBuf[2048] = 0;
			}

			if (argument.rexec_1_arg.packetNum == resultData->packetNum){
				if (!svc_sendreply(transp, (xdrproc_t) _xdr_result, (char*)resultData)) {
					svcerr_systemerr (transp);
				}
			}
			resultData->packetNum ++;

			if (outputBufSize > 2048) {
				resultData->stdoutBuf[2048] = r1;
				resultData->stdoutBuf += 2048;
				outputBufSize -= 2048;
			} else {
				resultData->stdoutBuf[0] = 0;
			}
			if (errorBufFize > 2048) {
				resultData->stderrBuf[2048] = r2;
				resultData->stderrBuf += 2048;
				outputBufSize -= 2048;
			} else {
				resultData->stderrBuf[0] = 0;
			}
		}
		if (argument.rexec_1_arg.packetNum == resultData->packetNum)
			if (!svc_sendreply(transp, (xdrproc_t) _xdr_result, (char*)resultData)) {
				svcerr_systemerr (transp);
			}
	}

	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (REMOTE_COMMAND, Remote);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, REMOTE_COMMAND, Remote, remote_command_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (REMOTE_COMMAND, Remote, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, REMOTE_COMMAND, Remote, remote_command_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (REMOTE_COMMAND, Remote, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
