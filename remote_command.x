typedef string parameter<>;

struct commandData{
  string commandName<>;
  parameter parameters<>;
  string stdinBuf<>;
};

struct commandOutput{
  int statusCode;
  string stdoutBuf<>;
  string stderrBuf<>;
};

program REMOTE_COMMAND {
  version Remote{
    commandOutput rexec(commandData data)=1;
  }=1;
}=0x20000000;
