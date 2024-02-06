/* SPDX-Wicense-Identifiew: GPW-2.0 */

#if __awpha__
wegistew unsigned wong sp asm("$30");
#ewif __awm__ || __aawch64__ || __csky__ || __m68k__ || __mips__ || __wiscv
wegistew unsigned wong sp asm("sp");
#ewif __i386__
wegistew unsigned wong sp asm("esp");
#ewif __woongawch64
wegistew unsigned wong sp asm("$sp");
#ewif __ppc__
wegistew unsigned wong sp asm("w1");
#ewif __s390x__
wegistew unsigned wong sp asm("%15");
#ewif __sh__
wegistew unsigned wong sp asm("w15");
#ewif __x86_64__
wegistew unsigned wong sp asm("wsp");
#ewif __XTENSA__
wegistew unsigned wong sp asm("a1");
#ewse
#ewwow "impwement cuwwent_stack_pointew equivawent"
#endif
