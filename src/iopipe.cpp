#include "../header/iopipe.h"
// #include <iostream>
#include "../header/base.h"
#include "../header/connector.h"


#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

// #include <stat/stat.h>

using namespace std;

class Base;
class Connector;

bool IOPipe::execute() {
    // int file_desc[2];
    // int temp;
    // pid_t pid1;
    // pid_t pid2;
    // int pipe = pipe(file_desc);
    //
    // if (pipe < 0) {
    //   perror("pipe");
    //   exit(1);
    //   return false;
    // }
    //
    // pid = fork();
    //
    // if (pid < 0) {
    //   perror("fork");
    //   exit(1);
    //   return false;
    // }
    //
    // if (pid == 0) {
    //   pid2 = fork();
    //
    //   if (pid2 < 0) {
    //     perror("fork");
    //     exit(1);
    //     return false;
    //   }
    //   else if (pid2 == 0) {
    //     if (dup2(file_desc[1], 1) < 0) {
    //       perror("dup2");
    //       exit(1);
    //       return false;
    //     }
    //     if (close(file_desc[0]) < 0) {
    //       perror("errno");
    //       exit(1);
    //       return false;
    //     }
    //     if (!left->execute()) {
    //       exit(1);
    //       return false;
    //     }
    //     exit(0);
    //   }
    //   else {
    //     if (dup2(file_desc[0], 0) < 0) {
    //       perror("dup2");
    //       exit(1);
    //       return false;
    //     }
    //     if (close(file_desc[1]) < 0) {
    //       perror("errno");
    //       exit(1);
    //       return false;
    //     }
    //     if (!right->execute()) {
    //       exit(1);
    //       return false;
    //     }
    //     exit(0);
    //   }
    // }
    //
    // if (close(file_desc[0]) < 0) {
    //   perror("errno");
    //   exit(1);
    //   return false;
    // }
    //
    // if (close(file_desc[1]) < 0) {
    //   perror("errno");
    //   exit(1);
    //   return false;
    // }
    //
    // waitpid(pid, &temp, 0);
    //
    // while (!WIFEXITED(temp)) {
    // }
    // waitpid(pid, &temp, 0);
    // if (temp > 0) {
    //   return false;
    // }
    // else if (WEXITSTATUS(temp) == 0) {
    //   return true;
    // }
    // else if (WEXITSTATUS(temp) == 1) {
    //   return false;
    // }
}

string IOPipe::getCommand() {
  return left->getCommand() + " | " + right->getCommand();
}