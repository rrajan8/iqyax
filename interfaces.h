#ifndef SCORE_INTERFACES_H
#define SCORE_INTERFACES_H

#include <chdl/ag.h>
#include <chdl/chdl.h>

#define SIMULATE
//#define SYNTHESIZE

#define DELAYED_BRANCH

#define MUL_DIV
//#define ONE_CYC_MUL
//#define FPGA_MUL
#define BTB
#define TRAP

// #define RANDOM_STALL
// #define INST_ROM_SIMULATE_ICACHE_MISS

// #define SST_MEM
#define LLSC
#define INTERNAL_MEM
#define INFO_ROM

#define MAP_ROM_COPY
#define INST_ROM
// #define SST_IMEM

#define TRISTATE_ALU_MUX

// #define SHOW_PC

// #define SCOREBOARD // These can be enabled manually but are also enabled
// #define MSHR       // automatically as needed.

// Handle dependencies between #defines:
#ifdef MUL_DIV
#define STALL_SIGNAL
#endif

#ifdef SCOREBOARD
#define STALL_SIGNAL
#endif

#ifdef SST_MEM
#define MSHR
#endif

#ifdef MSHR
#define SCOREBOARD
#endif

namespace s_core {
  const bool SOFT_IO(true), FPGA_IO(true), DEBUG_MEM(false);
  const unsigned N(32), IROM_SZ(10), RAM_SZ(20), MSHR_SZ(8);
  const chdl::cycle_t TMAX(100000);

  #ifdef BTB
  const unsigned BTB_SZ(5), BF_SZ(7), BF_HASHES(2), BF_CLEAR_INT(7);
  #endif

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
          #ifdef STALL_SIGNAL
          ,chdl::ag<STP("stall"), chdl::node
          #endif
          #ifdef BTB
          ,chdl::ag<STP("bp_valid"), chdl::node
          ,chdl::ag<STP("bp_state"), chdl::bvec<2>
          ,chdl::ag<STP("bp_branch"), chdl::node
          ,chdl::ag<STP("bp_pc"), word_t
          ,chdl::ag<STP("bp_predict_taken"), chdl::node> > > > >
          #endif
          #ifdef STALL_SIGNAL
          >
          #endif
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
          chdl::ag<STP("j"), chdl::node,
          chdl::ag<STP("jr"), chdl::node,
          chdl::ag<STP("beq"), chdl::node,
          chdl::ag<STP("bne"), chdl::node,
          chdl::ag<STP("bgez"), chdl::node,
          chdl::ag<STP("bltz"), chdl::node,
          chdl::ag<STP("blez"), chdl::node,
          chdl::ag<STP("bgtz"), chdl::node,
          chdl::ag<STP("jal"), chdl::node,
          chdl::ag<STP("next_pc"), word_t,
          chdl::ag<STP("pc"), word_t
          #ifdef LLSC
          ,chdl::ag<STP("llsc"), chdl::node
          #endif
          #ifdef STALL_SIGNAL
          ,chdl::ag<STP("stall"), chdl::node
          #endif
          #ifdef BTB
          ,chdl::ag<STP("bp_valid"), chdl::node
          ,chdl::ag<STP("bp_state"), chdl::bvec<2>
          ,chdl::ag<STP("bp_branch"), chdl::node
          ,chdl::ag<STP("bp_pc"), word_t
          ,chdl::ag<STP("bp_predict_taken"), chdl::node> > > > >
          #endif
          #ifdef STALL_SIGNAL
          >
          #endif
          #ifdef LLSC
          >
          #endif
  > > > > > > > > > > > > > > > > > > > > > > > > > decode_reg_t;

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
          chdl::ag<STP("j"), chdl::node,
          chdl::ag<STP("jr"), chdl::node,
          chdl::ag<STP("beq"), chdl::node,
          chdl::ag<STP("bne"), chdl::node,
          chdl::ag<STP("bgez"), chdl::node,
          chdl::ag<STP("bltz"), chdl::node,
          chdl::ag<STP("blez"), chdl::node,
          chdl::ag<STP("bgtz"), chdl::node,
          chdl::ag<STP("jal"), chdl::node,
          chdl::ag<STP("next_pc"), word_t,
          chdl::ag<STP("pc"), word_t
          #ifdef LLSC
          ,chdl::ag<STP("llsc"), chdl::node
          #endif
          #ifdef STALL_SIGNAL
          ,chdl::ag<STP("stall"), chdl::node
          #endif
          #ifdef BTB
          ,chdl::ag<STP("bp_valid"), chdl::node
          ,chdl::ag<STP("bp_state"), chdl::bvec<2>
          ,chdl::ag<STP("bp_branch"), chdl::node
          ,chdl::ag<STP("bp_pc"), word_t
          ,chdl::ag<STP("bp_predict_taken"), chdl::node> > > > >
          #endif
          #ifdef STALL_SIGNAL
          >
          #endif
          #ifdef LLSC
          >
          #endif
  > > > > > > > > > > > > > > > > > > > > > > > > > > > reg_exec_t;

  // Signals from execute to fetch stage (branch mispredict)
  typedef chdl::ag<STP("ldpc"), chdl::node,
          chdl::ag<STP("val"), word_t
          #ifdef BTB
          ,chdl::ag<STP("bp_state"), chdl::bvec<2>
          ,chdl::ag<STP("bp_branch"), chdl::node
          ,chdl::ag<STP("branch"), chdl::node
          ,chdl::ag<STP("branch_pc"), word_t> > > >
          #endif
  > > exec_fetch_t;

  // Signals from execute to memory stage
  typedef chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("result"), word_t,
          chdl::ag<STP("addr"), word_t,
          chdl::ag<STP("mem_rd"), chdl::node,
          chdl::ag<STP("mem_wr"), chdl::node,
          chdl::ag<STP("mem_byte"), chdl::node,
          chdl::ag<STP("pc"), word_t
          #ifdef LLSC
          ,chdl::ag<STP("llsc"), chdl::node
          #endif
          #ifdef STALL_SIGNAL
           ,chdl::ag<STP("stall"), chdl::node>
          #endif
          #ifdef LLSC
          >
          #endif
  > > > > > > > > exec_mem_t;

  // Forwarding values and register names from last stage back to execute stage
  typedef chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("result"), word_t,
          chdl::ag<STP("mem_rd"), chdl::node
  > > > > mem_exec_t;

  // Signals from memory to registers (writeback)
  typedef chdl::ag<STP("rdest_idx"), rname_t,
          chdl::ag<STP("rdest_valid"), chdl::node,
          chdl::ag<STP("result"), word_t
  > > > mem_reg_t;
};

#endif
