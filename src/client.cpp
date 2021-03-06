#include "../header/base.h"
#include "../header/client.h"
#include "../header/command.h"
#include "../header/connector.h"
#include "../header/and.h"
#include "../header/semi.h"
#include "../header/pipe.h"
#include "../header/input.h"
#include "../header/iopipe.h"
#include "../header/output.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

class Base;

void Client::parse() {
  string c1str;
  string c2str;
  stack<Base*> tree;
  queue<string> parentheses;
  bool hasOp = false;
  if (command.find('#') != -1) { //found #
    int indexOfPound = command.find('#');
    string substringedCommand = command.substr(0, indexOfPound);
    Base* cmdPound = new Command(substringedCommand);
    tree.push(cmdPound);
  }
  else {
    if ((command.find('(') != -1) && (command.find(')') != -1)) { // if there are parentheses
      while ((command.find('(') != -1) && (command.find(')') != -1)) { //whihle there is still parentheses
        int parenCount1 = 0;
        int parenCount2 = 0;
        for (int i = 0; i < command.size(); i++) {
          if (command.at(i) == '(') {
            parenCount1++;
          }
          if (command.at(i) == ')') {
            parenCount2++;
          }
        }
        if (parenCount1 != parenCount2) {
          cout << "Error with parentheses" << endl;
          return;
        }
        if (parenCount1 == 1) {
          int a = command.find('(') + 1;
          int b = command.find(')') - 1;

          string insideP = command.substr(a, b - a + 1);

          parentheses.push(insideP);
          //cout << "lol" << endl;
          command = command.substr(0,command.find('(')) + command.substr(command.find(')'), command.size() - command.find(')') - 1);
          //cout << "command: " << command << endl;
        }
        else if (command.at(0) == '(') {
          //cout << "asdfasdf" << endl;
          int a = command.find('(') + 1;
          int b = command.find(')') - 1;

          string insideP = command.substr(a, b - a + 1);

          parentheses.push(insideP);
          //cout <<"roght here" << endl;
          command = command.substr(command.find(')') + 3, command.size() - command.find(')'));
          //cout << "new command: " << command << endl;
        }
        else {
          int a = command.find('(') + 1;
          int b = command.find(')') - 1;
          string insideP = command.substr(a, b - a + 1); //pushes first command into queue
          parentheses.push(insideP);
          //cout << "old command: " << command << endl;
          command = command.substr(0,command.find('(')) + command.substr(command.find(')'), command.size() - command.find(')') - 1);
          //command = command.substr()
          //cout << "in queue: " << parentheses.front() << endl;
          //cout << "new command: " << command << endl;
          if(command.at(command.size() - 2) == ';') {
            command = command.substr(0, command.size() - 2);
          }
          if(command.at(command.size() - 2) == '|' || command.at(command.size() - 1) == '&') {
            command = command.substr(0, command.size() - 3);
          }
          //cout << "new command: " << command << endl;
          //parentheses.push(command);
        }
      }
      while (!parentheses.empty()) { //if prantheses stack isnt empty, execute everyting in it
        //cout << "commandss: " << parentheses.front() << endl;
        Client * temp = new Client(parentheses.front());
        temp->parse();
        parentheses.pop();
      }
      if (command == "") {
        return;
      }
    }
    if (command.size() > 2) {
      if (command.at(0) == ')') { // if there is a prantheses
      //if (command.find('(') && command.find(')')) {
        if (command.at(1) == '&' || command.at(1) == '|') {
          command = command.substr(4);
        }
        else if(command.at(1) == ';') {
          command = command.substr(2);
        }
      }
    if (command.at(command.size() - 2) == ';' ) {
      command = command.substr(0, command.size() - 2);
    }
    else if (command.at(command.size() - 3) == '|' || command.at(command.size() - 3) == '&' ) {
      command = command.substr(0, command.size() - 4);
    }
  }
    if (command.find(' ') == -1) { //no spaces found
      Base* cmd0 = new Command(command);
      // cout << "oh we're here now" << endl;
      // root = cmd0;
      tree.push(cmd0);
      // cout << "no space command found" << endl;
      // cout << "no spaces, therefore command is: " << command << endl;
    }
    else if (command.find(' ') != -1){
      // cout << "now PROCESSING: " << command << endl;
      // cout << "o fuhk spaces found, here we go boys" << endl;
      bool whileCond = true;
      bool first = true;
      while (whileCond == true) { //while there are spaces...
        //cout << "lol" << endl;
        int indexOfSpace = command.find(' ');
        int numSpacesXD = 0;
        for (int i = 0; i < command.size(); i++) {
          if (command.at(i) == ' ') {
            numSpacesXD++;
          }
        }
        if (command.at(0) == '[' || command.substr(0,4) == "test") { //if its a test or a [ command
          if (command.find('&') == -1 && command.find('|') == -1 && command.find(';') == -1) {
          // cout << "executing as single command" << endl;
          Base* cmd0 = new TestCommand(command);
          // root = cmd0;
          tree.push(cmd0);
          // return;
          whileCond = false;
          break;
        }
        // else {
          // cout << "executing as found operation " << endl;
          // Base* cmd0 = new TestCommand(command);
          // // root = cmd0;
          // tree.push(cmd0);
          // // return;
          // whileCond = false;
        // }
        // cout << "command now: " << command << endl;
        }
        if (first == false) {
          if (numSpacesXD == 0) {
            // cout << "no spaces?" << endl;
            tree.push(new Command(command));
            whileCond = false;
            break;
          }
          string commandCopy = command.substr(command.find(' '), command.size() - 1);
          indexOfSpace = commandCopy.find(' ');
        }
        if (command.at(indexOfSpace + 1) != '&' ||
        command.at(indexOfSpace + 1) != '|' ||
        command.at(indexOfSpace + 1) != ';') {
          // hasOp = true;
          // hasOp = true;
          if (command.find('&') != -1) { // if found &&
            //cout << "FOUND &&" << endl;
          int indxOfAnd = command.find('&');
          Base* c1 = new Command(command.substr(0, indxOfAnd - 1));
          if (c1->getCommand().at(0) == '[' || c1->getCommand().substr(0, 4) == "test") {
            // cout << "TEST COMMAND DETECTED FIRST" << endl;
              c1 = new TestCommand(command.substr(0, indxOfAnd - 1));
            // } else
          }
          if (c1->getCommand().find('<') != -1) {
            // cout << "< found" << endl;
            // cout << "[" << c1->getCommand() << "]" << endl;
            //left
            //right
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('<')));
            // cout << left->getCommand() << endl;
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('<') + 2, c1->getCommand().size() - 1));
            // cout << right->getCommand() << endl;
            c1 = new Input(left,right);
          }
          if (c1->getCommand().find('|') != -1) {
            // cout << "< found" << endl;
            // cout << "[" << c1->getCommand() << "]" << endl;
            //left
            //right
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('|')));
            // cout << left->getCommand() << endl;
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('|') + 2, c1->getCommand().size() - 1));
            // cout << right->getCommand() << endl;
            c1 = new IOPipe(left,right);
          }
          if (c1->getCommand().find('>') != -1) {
            // cout << c1->getCommand().at(c1->getCommand().find('>') + 1) << endl;
            if (c1->getCommand().at(c1->getCommand().find('>') + 1) == '>') { //second >
                        // cout << "yuh double" << endl;
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 3, c1->getCommand().size() - 1));
            c1 = new Output(left,right, true);
          } else {
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 2, c1->getCommand().size() - 1));
            c1 = new Output(left,right, false);
          }
        }
            // }
          Base* c2 = new Command(command.substr(indxOfAnd + 3, command.size() - 1));
          Base* addCon = new And_Connector(c1, c2);
          tree.push(addCon);
          command = c2->getCommand();
          //cout << "AND OPERAND PROCESSING RN" << endl;
          first = false;
          hasOp = true;
          whileCond = false;
          }
          if (command.find('|') != -1) {
          int indxOfPipe = command.find('|');
          if (command.at(indxOfPipe + 1) == '|') {
          Base* c1 = new Command(command.substr(0, indxOfPipe -1));
          if (c1->getCommand().at(0) == '[' || c1->getCommand().substr(0, 4) == "test") {
            // cout << "TEST COMMAND DETECTED FIRST" << endl;
              c1 = new TestCommand(command.substr(0, indxOfPipe - 1));
            // } else
          }
          if (c1->getCommand().find('<') != -1) {
            // cout << "< found" << endl;
            // cout << "[" << c1->getCommand() << "]" << endl;
            //left
            //right
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('<')));
            // cout << left->getCommand() << endl;
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('<') + 2, c1->getCommand().size() - 1));
            // cout << right->getCommand() << endl;
            c1 = new Input(left,right);
          }
          if (c1->getCommand().find('>') != -1) {
            if (c1->getCommand().at(c1->getCommand().find('>') + 1) == '>') { //second >
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 3, c1->getCommand().size() - 1));
            c1 = new Output(left,right, true);
              // cout << "yuh double" << endl;
          } else {
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 2, c1->getCommand().size() - 1));
            c1 = new Output(left,right, false);
          }
        }
          Base* c2 = new Command(command.substr(indxOfPipe +3, command.size() - 1));
          Base* pipeCon = new Pipe_Connector(c1, c2);
          tree.push(pipeCon);
          command = c2->getCommand();
          first = false;
          hasOp = true;
        }
        else {
          // JASON - IMPLEMENT SINGLE PIPING HERE :)
          // cout << "lol theres a io pipe only" << endl;
          // assuming te command looks like this input1 | input2
          int indxOfIOpipe = command.find('|');

          Base * c1 = new Command(command.substr(0, indxOfIOpipe - 1));
          Base * c2 = new Command(command.substr(indxOfIOpipe + 1, command.size() - indxOfIOpipe));

          IOPipe * temp = new IOPipe(c1,c2);
          tree.push (temp);

          first = false;
          hasOp = true;
          whileCond = false; // ?
        }
          }
          if (command.find(';') != -1 ) {
          int indxOfSemi = command.find(';');
          Base* c1 = new Command(command.substr(0, indxOfSemi));
          if (c1->getCommand().at(0) == '[' || c1->getCommand().substr(0, 4) == "test") {
            // cout << "TEST COMMAND DETECTED FIRST" << endl;
              c1 = new TestCommand(command.substr(0, indxOfSemi));
            // } else
          }
          if (c1->getCommand().find('<') != -1) {
            // cout << "< found" << endl;
            // cout << "[" << c1->getCommand() << "]" << endl;
            //left
            //right
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('<')));
            // cout << left->getCommand() << endl;
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('<') + 2, c1->getCommand().size() - 1));
            // cout << right->getCommand() << endl;
            c1 = new Input(left,right);
          }
          if (c1->getCommand().find('|') != -1) {
            // cout << "< found" << endl;
            // cout << "[" << c1->getCommand() << "]" << endl;
            //left
            //right
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('|')));
            // cout << left->getCommand() << endl;
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('|') + 2, c1->getCommand().size() - 1));
            // cout << right->getCommand() << endl;
            c1 = new IOPipe(left,right);
          }
          if (c1->getCommand().find('>') != -1) {
            if (c1->getCommand().at(c1->getCommand().find('>') + 1) == '>') { //second >
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 3, c1->getCommand().size() - 1));
            c1 = new Output(left,right, true);
              // cout << "yuh double" << endl;
          } else {
            Command* left = new Command(c1->getCommand().substr(0, c1->getCommand().find('>')));
            Command* right = new Command(c1->getCommand().substr(c1->getCommand().find('>') + 2, c1->getCommand().size() - 1));
            c1 = new Output(left,right,false);
          }
        }
          Base* c2 = new Command(command.substr(indxOfSemi + 2, command.size() - 1));
          Base* semiCon = new Semi_Connector(c1, c2);
          tree.push(semiCon);
          command = c2->getCommand();
          first = false;
          hasOp = true;
          whileCond = false; // ?
        }
        if (command.at(1) == '[' || command.substr(0,4) == "test") {
          // cout << "hi there" << endl;
          // cout << "command rn: " << command << endl;
          TestCommand* cmd0 = new TestCommand(command);
          // root = cmd0;
          tree.push(cmd0);
          // return;
          whileCond = false; // ?
          // break;
        }
        else {
// =======
        // } else {
// >>>>>>> e146634f0188b74a015f5e72ad56772c44f41c18
        //if none of the connectors are found, truncate the string should be saved, removing the last space
        // Base* commandNoConnectorYet = new Command(command);
        // //cout << command << endl;
        // //parent = new Client(command);
        // cout << ""
        Base* elseC = new Command(command);
        // cout << "elseC: " << elseC->getCommand() << endl;
        /**
        BEGIN PROCESSING OPERATIONS
        **/
        /**
        IO REDIRECTION
        **/
        if (command.find('<') != -1) {
          // cout << "input redirection" << endl;
          int indxOfOpen = command.find('<');
          Command* c1 = new Command(command.substr(0, indxOfOpen - 1));
          Command* c2 = new Command(command.substr(indxOfOpen + 2, command.size() - 1));
          Input* inputCon = new Input(c1, c2);
          elseC = inputCon;
          first = false;
        }
        if (command.find('|') != -1) {
          // cout << "input redirection" << endl;
          int indxOfOpen = command.find('|');
          Command* c1 = new Command(command.substr(0, indxOfOpen - 1));
          Command* c2 = new Command(command.substr(indxOfOpen + 2, command.size() - 1));
          IOPipe* inputCon = new IOPipe(c1, c2);
          elseC = inputCon;
          first = false;
        }
        if (command.find('>') != -1) {
          // cout << "input redirection" << endl;
          // cout << command.at(command.find('>') + 1) << endl;
          if (command.at((command.find('>') + 1)) == '>') {
            int indxOfClose = command.find('>');
            Command* c1 = new Command(command.substr(0, indxOfClose - 1));
            Command* c2 = new Command(command.substr(indxOfClose + 3, command.size() - 1));
            Output* outputCon = new Output(c1, c2, true);
            // cout << "yuh double" << endl;
            elseC = outputCon;
            first = false;
          } else {
          int indxOfClose = command.find('>');
          Command* c1 = new Command(command.substr(0, indxOfClose - 1));
          Command* c2 = new Command(command.substr(indxOfClose + 2, command.size() - 1));
          Output* outputCon = new Output(c1, c2, false);
          elseC = outputCon;
          first = false;
        }
      }
        tree.push(elseC);
        whileCond = false;
      }
    }
  }
}
}
  bool firstCommand = true;
    while (!tree.empty()) {
      // cout << "HELLO:" << tree.top()->getCommand() << endl;
      root = tree.top();
      tree.pop();
      // if (root->getCommand().find('<')) {
      //   cout << root->getCommand() << endl;
      // }
      if (hasOp == false) {
        // cout << "NO OP" << endl;
        root->execute();
      }
      if (firstCommand == false && hasOp == true) {
      root->execute();
    }
    firstCommand = false;
    }
}
