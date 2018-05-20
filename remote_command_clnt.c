/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "remote_command.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

commandOutput *
rexec_1(commandData *argp, CLIENT *clnt)
{
	static commandOutput clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rexec,
		(xdrproc_t) xdr_commandData, (caddr_t) argp,
		(xdrproc_t) xdr_commandOutput, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}