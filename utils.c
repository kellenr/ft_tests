#include <unistd.h>

int open_pipe_stdout(){
  // Redirect stdout to a pipe
  int pipefd[2]; // read <- 0======1 <- write
  pipe(pipefd);
  dup2(pipefd[1], STDOUT_FILENO);
  // https://www.figma.com/file/a2GaX3wOVmEjFjit8oyAWH/Untitled?node-id=0-1&t=AXTzXqghrAzZdD69-0
  close(pipefd[1]);

  return pipefd[0];
}

void read_from_pipe_and_close(int pipe, char *buf, int n) {
  read(pipe, buf, n);
  buf[n] = '\0';
  close(pipe);
}
