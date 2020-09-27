#pragma once
#include <stdint.h>

// Structure of all registers
struct registers_t {
  // uint64_t ds;
  // uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
  // uint64_t int_no, err_code;
  // uint64_t eip, cs, eflags, useresp, ss;

  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rsi;
  uint64_t rdi;
  uint64_t rbp;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;
  uint64_t core;
  uint64_t isrNumber;
  uint64_t errorCode;
  uint64_t rip;
  uint64_t cs;
  uint64_t rflags;
  uint64_t rsp;
  uint64_t ss;
} __attribute__((packed));
