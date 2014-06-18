#include <chdl/ag.h>
#include <chdl/chdl.h>

namespace s_core {
  const bool SOFT_IO(true);
  const unsigned N(32), IROM_SZ(10), RAM_SZ(20);
  const chdl::cycle_t TMAX(100000);

  typedef chdl::bvec<5> rname_t;
  typedef chdl::bvec<6> opcode_t;
  typedef chdl::bvec<6> func_t;
  typedef chdl::bvec<N> word_t;
  typedef chdl::bvec<N> inst_t;

  static word_t LitW(unsigned long x) { return chdl::Lit<N>(x); }

  // Signals from instruction fetch to decoder
  typedef chdl::ag<STP("valid"), chdl::node,
          chdl::ag<STP("inst"), inst_t,
          chdl::ag<STP("next_pc"), word_t,
          chdl::ag<STP("pc"), word_t
  > > > > fetch_decode_t;

  // Signals from decoder to regsiter file
  typedef chdl::ag<STP("valid"), chdl::node,
          chdl::ag<STP("rsrc0_idx"), rname_t,
          chdl::ag<STP("rsrc0_valid"), chdl::node,
          chdl::ag<STP("rsrc1_idx"), rname_t,
          chdl::ag<STP("rsrc1_valid"), chdl::node,
          chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("imm"), word_t,
          chdl::ag<STP("imm_valid"), chdl::node,
          chdl::ag<STP("op"), opcode_t,
          chdl::ag<STP("func"), func_t,
          chdl::ag<STP("mem_rd"), chdl::node,
          chdl::ag<STP("mem_wr"), chdl::node,
          chdl::ag<STP("mem_byte"), chdl::node,
          chdl::ag<STP("jal"), chdl::node,
          chdl::ag<STP("next_pc"), word_t,
          chdl::ag<STP("pc"), word_t
  > > > > > > > > > > > > > > > > > decode_reg_t;

  // Signals from register stage to execute stage
  typedef chdl::ag<STP("valid"), chdl::node,
          chdl::ag<STP("rsrc0_idx"), rname_t,
          chdl::ag<STP("rsrc0_valid"), chdl::node,
          chdl::ag<STP("rsrc1_idx"), rname_t,
          chdl::ag<STP("rsrc1_valid"), chdl::node,
          chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("val0"), word_t,
          chdl::ag<STP("val1"), word_t,
          chdl::ag<STP("imm"), word_t,
          chdl::ag<STP("imm_valid"), chdl::node,
          chdl::ag<STP("op"), opcode_t,
          chdl::ag<STP("func"), func_t,
          chdl::ag<STP("mem_rd"), chdl::node,
          chdl::ag<STP("mem_wr"), chdl::node,
          chdl::ag<STP("mem_byte"), chdl::node,
          chdl::ag<STP("jal"), chdl::node,
          chdl::ag<STP("next_pc"), word_t,
          chdl::ag<STP("pc"), word_t
  > > > > > > > > > > > > > > > > > > > reg_exec_t;

  // Signals from execute to fetch stage (branch mispredict)
  typedef chdl::ag<STP("ldpc"), chdl::node,
          chdl::ag<STP("val"), word_t
  > > exec_fetch_t;

  // Signals from execute to memory stage
  typedef chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("result"), word_t,
          chdl::ag<STP("addr"), word_t,
          chdl::ag<STP("mem_rd"), chdl::node,
          chdl::ag<STP("mem_wr"), chdl::node,
          chdl::ag<STP("mem_byte"), chdl::node
  > > > > > > > exec_mem_t;

  // Signals from memory to registers (writeback)
  typedef chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("result"), word_t
  > > > mem_reg_t;
};