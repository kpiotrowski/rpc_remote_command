/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REMOTE_COMMAND_H_RPCGEN
#define _REMOTE_COMMAND_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef char *parameter;

struct commandData {
	char *commandName;
	struct {
		u_int parameters_len;
		parameter *parameters_val;
	} parameters;
	char *stdinBuf;
	char *commandId;
  	int packetNum;
};
typedef struct commandData commandData;

struct commandOutput {
	int statusCode;
	int packetCount;
	int packetNum;
	char *stdoutBuf;
	char *stderrBuf;
};
typedef struct commandOutput commandOutput;

#define REMOTE_COMMAND 0x20000000
#define Remote 1

#if defined(__STDC__) || defined(__cplusplus)
#define rexec 1
extern  commandOutput * rexec_1(commandData *, CLIENT *);
extern  commandOutput * rexec_1_svc(commandData *, struct svc_req *);
extern int remote_command_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rexec 1
extern  commandOutput * rexec_1();
extern  commandOutput * rexec_1_svc();
extern int remote_command_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_parameter (XDR *, parameter*);
extern  bool_t xdr_commandData (XDR *, commandData*);
extern  bool_t xdr_commandOutput (XDR *, commandOutput*);

#else /* K&R C */
extern bool_t xdr_parameter ();
extern bool_t xdr_commandData ();
extern bool_t xdr_commandOutput ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REMOTE_COMMAND_H_RPCGEN */
