#include <iostream>
#include <vector>
#include <string>
#include <sstream>
std::string IntToString(int num) {
  if (num == 0) return "0";
  std::string result;
  while (num > 0) {
    char digit =  '0' + (num % 10);
    result = digit + result;  // // 插入到字串前面
    num /= 10;
  }

  return result;


}
class Buffer {
 private:
  std::string name;
  int current_line;
  std::vector<std::string> contents;
 public:
  explicit Buffer(std::string new_name) {
    current_line = 0;
    name = new_name;
  }
  std::string Getname() {
    return name;
  }
  void SetName(std::string new_name) {
    name = new_name;
  }
  int Getsize() {
    return contents.size();
  }
  int Getcurrent_line() {
    return current_line;
  }
  void Setcurrent_line(int num) {
    current_line = current_line + num;
  }
  bool Setcurrent_line_to(int num) {
    if (num > contents.size() || num == 0) {
      std::cout << "Error : Line number out of range! Please try again."
                << std::endl;
      return false;
    }

    current_line = num;
    return true;
  }
  void Change() {
    std::string input;
    if (Getsize() > 0) {
      if (current_line == Getsize()) {
        contents.erase(current_line + contents.begin() - 1);
        if (contents.empty()) {
          current_line = 0;
        }
        if (current_line > contents.size()) {
          current_line = contents.size();
        }
      } else if (current_line != Getsize()) {
        contents.erase(current_line + contents.begin() - 1);
        if (contents.empty()) {
          current_line = 0;
        }
        if (current_line > contents.size()) {
          current_line = contents.size();
        }
        if (current_line != 0)  {
          current_line -= 1;
        }
      }
      while (std::getline(std::cin, input)) {
        if (input == ".") {
          break;
        }
        contents.insert(current_line + contents.begin(), input);
        current_line = current_line + 1;
      }
    } else {
      std::cout << "Error : There is no data! Please try again." << std::endl;
    }


  }
  void Insert() {
    std::string input;
    if (current_line != 0)  {
      current_line -= 1;
    }
    while (std::getline(std::cin, input)) {
      if (input == ".") {
        break;
      }
      contents.insert(current_line + contents.begin(), input);
      current_line = current_line + 1;
    }

  }
  void Append() {
    std::string input;
    while (std::getline(std::cin, input)) {
      if (input == ".") {
        break;
      }
      contents.insert(current_line + contents.begin(), input);
      current_line = current_line + 1;
    }

  }
  bool Delete() {
    if (contents.empty()) {
      return false;
    }
    contents.erase(current_line + contents.begin() - 1);
    if (contents.empty()) {
      current_line = 0;
    }
    if (current_line > contents.size()) {
      current_line = contents.size();
    }
    return true;
  }
  bool Print(bool print_all) {
    if (contents.empty()) {
      return false;
    }
    if (print_all) {
      for (int i = 0; i < contents.size(); i++) {
        std::cout <<  i+1 << ": " << contents[i] << std::endl;
      }
    } else if (!print_all) {
      std::cout << contents[current_line - 1] << std::endl;
    }
    return true;
  }
  void Printlast() {
    if (contents.empty()) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
      return;
    }
    std::cout << contents.size() << ": " << contents[contents.size() - 1]
              << std::endl;
  }
  void Print_line_set_line(int print_line) {
    if (print_line > contents.size() || print_line == 0) {
      std::cout << "Error : Line number out of range! Please try again."
                << std::endl;
      return;
    } else {
      std::cout <<  print_line << ": " << contents[print_line - 1] << std::endl;
    }
    current_line = print_line;
  }
  void Printlast_Setlast() {
    if (contents.empty()) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
      return;
    }

    current_line = contents.size();
    std::cout << current_line << ": " << contents[current_line - 1];
    std::cout << std::endl;
  }
};
class BufferPro {
 private:
  int order_buffer = 1;
  int current_buffer;
  int total_buffers;
  std::vector<Buffer> buffs;
 public:
  BufferPro() {
    total_buffers = 1;
    current_buffer = 0;  // 第0個開始
    buffs.insert(buffs.begin(), Buffer("Buffer-0"));
  }
  Buffer& GetCurrentBuffer() {
    return buffs[current_buffer];
  }
  void PrintCurrentBuffer() {  // b
    std::cout << buffs[current_buffer].Getname() << " "
              << buffs[current_buffer].Getsize() << std::endl;
  }
  void RenameBuffer(std::string new_name) {  // rb
    if (new_name.empty()) {
      std::cout << "Error : buffer name cannot be empty! Please try again."
                << std::endl;
      return;
    }
    buffs[current_buffer].SetName(new_name);
  }
  void ListBuffers() {  // lb
    for (int i = 0; i < total_buffers; i++) {
      std::cout << buffs[i].Getname() << " " << buffs[i].Getsize() << std::endl;
    }
  }
  void ChangeBuffer(std::string name) {
    for (int i = 0; i < total_buffers; i++) {
      if (buffs[i].Getname() == name) {
        current_buffer = i;
        return;
      }
    }
    std::cout << "Error : There is no such buffer! Please try again."
              << std::endl;
  }
  void DeleteBuffer(std::string name) {
    if (total_buffers == 1) {
      std::cout << "Error : Illegal command! Please try again." << std::endl;
      return;
    } else if (name.empty()) {
      buffs.erase(current_buffer + buffs.begin());
      total_buffers--;
      if (total_buffers == current_buffer) {
        current_buffer--;
      }
      return;
    }

    for (int i = 0; i < total_buffers; i++) {
      if (buffs[i].Getname() == name) {
        current_buffer = i;
        buffs.erase(i + buffs.begin());
        total_buffers -= 1;
        if (current_buffer == total_buffers) {
          current_buffer -= 1;
        }
        return;
      }
    }
    std::cout << "Error : There is no such buffer! Please try again."
              << std::endl;

  }
  void NewBuffer(std::string new_name) {
    if (new_name.empty()) {
      std::string default_name = "Buffer-" + IntToString(order_buffer);
      buffs.insert(total_buffers + buffs.begin(), Buffer(default_name));
      order_buffer++;
      total_buffers++;
      current_buffer = total_buffers - 1;
      return;
    }
    for (int i = 0; i < total_buffers; i++) {
      if (new_name == buffs[i].Getname()) {
        std::cout << "Error : Illegal command! Please try again." << std::endl;
        return;
      }
    }
    buffs.insert(total_buffers + buffs.begin(), Buffer(new_name));
    order_buffer++;
    total_buffers++;
    current_buffer = total_buffers - 1;
  }

};

int StringToInt(std::string str) {
  int i = 0;
  int result = str[i] - '0';
  while (str[i+1] <= '9' && str[i+1] >= '0') {
    result *= 10;
    result += str[i+1] - '0';
    i++;
  }
  return result;
}

std::string Line_command(std::string command) {
  std::string cmd;
  int i = 0;
  while (command[i] >= '0' && command[i] <= '9') {
    i++;
  }
  if (command.length() == i) {
    return cmd;
  } else if (command.length() == i+1) {
    cmd += command[i];
    return cmd;
  } else {
    cmd += "InVaLiD";
  }

  return cmd;
}
bool Operation(Buffer& b, std::string command) {
  if (command == "a" || command == ".a" || command == "A" || command == ".A") {
    b.Append();
    return true;
  } else if (command == "i" || command == ".i" || command == "I" ||
             command == ".I") {
    b.Insert();
    return true;
  } else if (command == "c" || command == ".c" || command == "C" ||
             command == ".C") {
    b.Change();
    return true;
  } else if (command == "d" || command == ".d" || command == "D" ||
             command == ".D") {
    if (!b.Delete()) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
      return true;
    }
  } else if (command == "p" || command == "P") {
    if (!b.Print(0)) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
      return true;
    }
  } else if (command == "%p" || command == "%P") {
    if (!b.Print(1)) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
      return true;
    }
  } else if (command == "$p" || command == "$P") {
    b.Printlast();
    return true;
  } else if (command == "$") {
    b.Printlast_Setlast();
    return true;
  } else if (command == "q" || command == "Q") {
    std::cout << "Thank you for using CYCUICE editor!" << std::endl;
    exit(0);
  } else if (command == ".") {
    if (b.Getcurrent_line() == 0) {
      std::cout << "Error : There is no data! Please try again." << std::endl;
    } else
      std::cout << "You're on line " << b.Getcurrent_line() << "." << std::endl;
    return true;
  } else if (command[0] >= '0' && command[0] <= '9') {
    int designate_line = StringToInt(command);
    std::string cmd = Line_command(command);

    if (cmd.empty()) {
      b.Print_line_set_line(designate_line);
    } else if (cmd == "a" || cmd =="A") {
      if (b.Setcurrent_line_to(designate_line)) {
        b.Append();
      }
    } else if (cmd == "i" || cmd == "I") {
      if (b.Setcurrent_line_to(designate_line)) {
        b.Insert();
      }
    } else if (cmd == "d" || cmd == "D") {
      if (b.Setcurrent_line_to(designate_line)) b.Delete();
    } else if (cmd == "c" || cmd == "C") {
      if (b.Setcurrent_line_to(designate_line)) b.Change();
    } else if (cmd == "p" || cmd == "P") {
      int temp = b.Getcurrent_line();
      if (b.Setcurrent_line_to(designate_line)) {
        b.Print(0);
        b.Setcurrent_line_to(temp);
      }

    } else return false;
    return true;
  } else if (command == "$i" || command == "$I") {
    b.Setcurrent_line_to(b.Getsize());
    b.Insert();
    return true;
  } else if (command == "$a" || command == "$A") {
    b.Setcurrent_line_to(b.Getsize());
    b.Append();
    return true;
  } else if (command == "$c" || command == "$C") {
    b.Setcurrent_line_to(b.Getsize());
    b.Change();
    return true;
  } else if (command == "$d" || command == "$D") {
    b.Setcurrent_line_to(b.Getsize());
    b.Delete();
    return true;
  } else return false;
  return true;
}

bool OperationPro(BufferPro& buffs, std::string command_input) {
  std::istringstream iss(command_input);
  std::string command;
  std::string new_name = "";
  std::string name = "";
  while (iss >> command) {
    if (command == "b") {
      buffs.PrintCurrentBuffer();
      return true;
    } else if (command == "rb") {
      iss >> new_name;
      buffs.RenameBuffer(new_name);
      return true;
    } else if (command == "lb") {
      buffs.ListBuffers();
      return true;
    } else if (command == "cb") {
      iss >> name;
      buffs.ChangeBuffer(name);
      return true;
    } else if (command == "db") {
      iss >> name;
      buffs.DeleteBuffer(name);
      return true;
    } else if (command == "nb") {
      iss >> new_name;
      buffs.NewBuffer(new_name);
      return true;
    } else if (Operation(buffs.GetCurrentBuffer(), command)) {
      return true;
    } else if (iss.eof()) {
      std::cout << "Error : Illegal command! Please try again." << std::endl;
      return true;
    } else continue;
  }
  return true;

}


int main() {
  std::cout << "Welcome to use CYCUICE editor..." << std::endl;
  char ch;
  BufferPro b;
  std::string command, command_input, trash;
  while (std::getline(std::cin, command_input)) {
    if (OperationPro(b, command_input)) {
      continue;
    } else {
      break;
    }
  }
  return 0;
}
