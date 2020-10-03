#pragma once

#include <stdint.h>
#include <stddef.h>

#include <kernel/cpu/idt.hpp>
#include <kernel/drivers/screen.hpp>
#include <kernel/drivers/keyboard.hpp>
#include <lib/strutils.hpp>
#include <kernel/cpu/reg.hpp>
#include <kernel/cpu/pit.hpp>

// The isr handlers we wrote in assembly

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void errorIsr8();
extern "C" void isr9();
extern "C" void errorIsr10();
extern "C" void errorIsr11();
extern "C" void errorIsr12();
extern "C" void errorIsr13();
extern "C" void errorIsr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();
extern "C" void isr48();
extern "C" void isr49();
extern "C" void isr50();
extern "C" void isr51();
extern "C" void isr52();
extern "C" void isr53();
extern "C" void isr54();
extern "C" void isr55();
extern "C" void isr56();
extern "C" void isr57();
extern "C" void isr58();
extern "C" void isr59();
extern "C" void isr60();
extern "C" void isr61();
extern "C" void isr62();
extern "C" void isr63();
extern "C" void isr64();
extern "C" void isr65();
extern "C" void isr66();
extern "C" void isr67();
extern "C" void isr68();
extern "C" void isr69();
extern "C" void isr70();
extern "C" void isr71();
extern "C" void isr72();
extern "C" void isr73();
extern "C" void isr74();
extern "C" void isr75();
extern "C" void isr76();
extern "C" void isr77();
extern "C" void isr78();
extern "C" void isr79();
extern "C" void isr80();
extern "C" void isr81();
extern "C" void isr82();
extern "C" void isr83();
extern "C" void isr84();
extern "C" void isr85();
extern "C" void isr86();
extern "C" void isr87();
extern "C" void isr88();
extern "C" void isr89();
extern "C" void isr90();
extern "C" void isr91();
extern "C" void isr92();
extern "C" void isr93();
extern "C" void isr94();
extern "C" void isr95();
extern "C" void isr96();
extern "C" void isr97();
extern "C" void isr98();
extern "C" void isr99();
extern "C" void isr100();
extern "C" void isr101();
extern "C" void isr102();
extern "C" void isr103();
extern "C" void isr104();
extern "C" void isr105();
extern "C" void isr106();
extern "C" void isr107();
extern "C" void isr108();
extern "C" void isr109();
extern "C" void isr110();
extern "C" void isr111();
extern "C" void isr112();
extern "C" void isr113();
extern "C" void isr114();
extern "C" void isr115();
extern "C" void isr116();
extern "C" void isr117();
extern "C" void isr118();
extern "C" void isr119();
extern "C" void isr120();
extern "C" void isr121();
extern "C" void isr122();
extern "C" void isr123();
extern "C" void isr124();
extern "C" void isr125();
extern "C" void isr126();
extern "C" void isr127();
extern "C" void isr128();
extern "C" void isr129();
extern "C" void isr130();
extern "C" void isr131();
extern "C" void isr132();
extern "C" void isr133();
extern "C" void isr134();
extern "C" void isr135();
extern "C" void isr136();
extern "C" void isr137();
extern "C" void isr138();
extern "C" void isr139();
extern "C" void isr140();
extern "C" void isr141();
extern "C" void isr142();
extern "C" void isr143();
extern "C" void isr144();
extern "C" void isr145();
extern "C" void isr146();
extern "C" void isr147();
extern "C" void isr148();
extern "C" void isr149();
extern "C" void isr150();
extern "C" void isr151();
extern "C" void isr152();
extern "C" void isr153();
extern "C" void isr154();
extern "C" void isr155();
extern "C" void isr156();
extern "C" void isr157();
extern "C" void isr158();
extern "C" void isr159();
extern "C" void isr160();
extern "C" void isr161();
extern "C" void isr162();
extern "C" void isr163();
extern "C" void isr164();
extern "C" void isr165();
extern "C" void isr166();
extern "C" void isr167();
extern "C" void isr168();
extern "C" void isr169();
extern "C" void isr170();
extern "C" void isr171();
extern "C" void isr172();
extern "C" void isr173();
extern "C" void isr174();
extern "C" void isr175();
extern "C" void isr176();
extern "C" void isr177();
extern "C" void isr178();
extern "C" void isr179();
extern "C" void isr180();
extern "C" void isr181();
extern "C" void isr182();
extern "C" void isr183();
extern "C" void isr184();
extern "C" void isr185();
extern "C" void isr186();
extern "C" void isr187();
extern "C" void isr188();
extern "C" void isr189();
extern "C" void isr190();
extern "C" void isr191();
extern "C" void isr192();
extern "C" void isr193();
extern "C" void isr194();
extern "C" void isr195();
extern "C" void isr196();
extern "C" void isr197();
extern "C" void isr198();
extern "C" void isr199();
extern "C" void isr200();
extern "C" void isr201();
extern "C" void isr202();
extern "C" void isr203();
extern "C" void isr204();
extern "C" void isr205();
extern "C" void isr206();
extern "C" void isr207();
extern "C" void isr208();
extern "C" void isr209();
extern "C" void isr210();
extern "C" void isr211();
extern "C" void isr212();
extern "C" void isr213();
extern "C" void isr214();
extern "C" void isr215();
extern "C" void isr216();
extern "C" void isr217();
extern "C" void isr218();
extern "C" void isr219();
extern "C" void isr220();
extern "C" void isr221();
extern "C" void isr222();
extern "C" void isr223();
extern "C" void isr224();
extern "C" void isr225();
extern "C" void isr226();
extern "C" void isr227();
extern "C" void isr228();
extern "C" void isr229();
extern "C" void isr230();
extern "C" void isr231();
extern "C" void isr232();
extern "C" void isr233();
extern "C" void isr234();
extern "C" void isr235();
extern "C" void isr236();
extern "C" void isr237();
extern "C" void isr238();
extern "C" void isr239();
extern "C" void isr240();
extern "C" void isr241();
extern "C" void isr242();
extern "C" void isr243();
extern "C" void isr244();
extern "C" void isr245();
extern "C" void isr246();
extern "C" void isr247();
extern "C" void isr248();
extern "C" void isr249();
extern "C" void isr250();
extern "C" void isr251();
extern "C" void isr252();
extern "C" void isr253();
extern "C" void isr254();
extern "C" void isr255();


typedef void (*eventHandlers_t)(registers_t*);

inline const char *exceptionMessages[] = {"Divide by zero",
                                          "Debug",
                                          "NMI",
                                          "Breakpoint",
                                          "Overflow",
                                          "Bound Range Exceeded",
                                          "Invaild Opcode",
                                          "Device Not Available",
                                          "Double fault",
                                          "Co-processor Segment Overrun",
                                          "Invaild TSS",
                                          "Segment not present",
                                          "Stack-Segment Fault",
                                          "GPF",
                                          "Page Fault",
                                          "Reserved",
                                          "x87 Floating Point Exception",
                                          "allignement check",
                                          "Machine check",
                                          "SIMD floating-point exception",
                                          "Virtualization Excpetion",
                                          "Deadlock",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Reserved",
                                          "Security Exception",
                                          "Reserved",
                                          "Triple Fault",
                                          "FPU error"};

// Functions
void isr_install();
extern "C" void isr_handler(registers_t *r);

// Map handlers
inline eventHandlers_t eventHandlers[] =   {
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        timer_handler, keyboard_handler, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                                    };
