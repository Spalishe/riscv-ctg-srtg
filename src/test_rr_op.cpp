#include <../include/tests.hpp>
#include <cstdint>
#include <format>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string TEST_RR_OP(vector<string> args, int index) {
  string opcode = args[0];
  int dest = stoi(args[1].substr(2), nullptr, 10);
  int op1 = stoi(args[2].substr(2), nullptr, 10);
  int op2 = stoi(args[3].substr(2), nullptr, 10);
  uint64_t reqval = stoull(args[4], nullptr, 16);
  uint64_t op1val = stoull(args[5], nullptr, 16);
  uint64_t op2val = stoull(args[6], nullptr, 16);
  int temp_op = stoi(args[7].substr(2), nullptr, 10);

  stringstream as;

  as << format("// opcode: {:}; op1: x{:}; op2: x{:}; dest: x{:}; reqval: "
               "0x{:x}; op1val: 0x{:x}; op2val: 0x{:x}; temp_op: x{:}",
               opcode, op1, op2, dest, reqval, op1val, op2val, temp_op)
     << endl;

  as << format("inst_{:}:", index) << endl;
  as << format("  li gp, 0x{:x}", index) << endl;
  as << format("  la t0, pointer") << endl;
  as << format("  sh gp, 0(t0)") << endl;

  as << format("  li x{:}, 0x{:x}", op1, op1val) << endl;
  as << format("  li x{:}, 0x{:x}", op2, op2val) << endl;
  as << format("  li x{:}, 0x{:x}", temp_op, reqval) << endl;

  as << format("  {:} x{:}, x{:}, x{:}", opcode, dest, op1, op2) << endl;
  as << format("  bne x{:}, x{:}, fail", dest, temp_op) << endl;

  return as.str();
}
