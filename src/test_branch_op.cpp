#include <../include/tests.hpp>
#include <cstddef>
#include <cstdint>
#include <format>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string TEST_BRANCH_OP(vector<string> args, int index) {
  string opcode = args[0];
  int temp_op = stoi(args[1].substr(2), nullptr, 10);
  int op1 = stoi(args[2].substr(2), nullptr, 10);
  int op2 = stoi(args[3].substr(2), nullptr, 10);
  uint64_t op1val = stoull(args[4], nullptr, 16);
  uint64_t op2val = stoull(args[5], nullptr, 16);
  uint64_t immval = stoull(args[6], nullptr, 16);

  stringstream as;

  as << format("// opcode: {:}; op1: x{:}; op2: x{:}; op1val: 0x{:x}; op2val: "
               "0x{:x}; immval: 0x{:x}; temp_op: x{:}",
               opcode, op1, op2, op1val, op2val, immval, temp_op)
     << endl;

  as << format("inst_{:}:", index) << endl;
  as << format("  li gp, 0x{:x}", index) << endl;
  as << format("  la t0, pointer") << endl;
  as << format("  sh gp, 0(t0)") << endl;

  as << format("  li x{:}, 0x{:x}", op1, op1val) << endl;
  as << format("  li x{:}, 0x{:x}", op2, op2val) << endl;

  as << format("  {:} x{:}, x{:}, x{:}", opcode, op1, op2, immval) << endl;
  for (int i = 0; i < immval - 4; i += 4) {
    as << "call fail" << endl;
  }
  as << "nop" << endl;

  return as.str();
}
