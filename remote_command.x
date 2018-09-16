typedef string parameter<>;

struct commandData{
  string commandName<>;
  string commandId<>;
  int packetNum;
  parameter parameters<>;
  string stdinBuf<>;
};

struct commandOutput{
  int statusCode;
  int packetCount;
  int packetNum;
  string stdoutBuf<>;
  string stderrBuf<>;
};

program REMOTE_COMMAND {
  version Remote{
    commandOutput rexec(commandData data)=1;
  }=1;
}=0x20000000;
