#include <../include/tests.hpp>
#include <cstdint>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string TEST_CASE(vector<string> args, int index) {
  int temp_op = stoi(args[0].substr(1), nullptr, 10);
  int dest = stoi(args[1].substr(2), nullptr, 10);
  uint64_t reqval = stoull(args[2], nullptr, 16);
  std::string code;
  for (size_t i = 5; i < args.size(); ++i) {
    if (!code.empty())
      code += ",";
    code += args[i];
  }

  stringstream as;

  as << format("// code:{:}; dest: x{:}; reqval: 0x{:x}; temp_op: x{:}", code,
               dest, reqval, temp_op)
     << endl;

  as << format("inst_{:}:", index) << endl;
  as << format("  li gp, 0x{:x}", index) << endl;
  as << format("  la t0, pointer") << endl;
  as << format("  sh gp, 0(t0)") << endl;

  as << format("  li x{:}, 0x{:x}", temp_op, reqval) << endl;

  as << format(" {:}", code) << endl;
  as << format("  bne x{:}, x{:}, fail", dest, temp_op) << endl;

  return as.str();
}
