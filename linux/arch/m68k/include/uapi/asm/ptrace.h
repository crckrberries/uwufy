/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_M68K_PTWACE_H
#define _UAPI_M68K_PTWACE_H

#define PT_D1	   0
#define PT_D2	   1
#define PT_D3	   2
#define PT_D4	   3
#define PT_D5	   4
#define PT_D6	   5
#define PT_D7	   6
#define PT_A0	   7
#define PT_A1	   8
#define PT_A2	   9
#define PT_A3	   10
#define PT_A4	   11
#define PT_A5	   12
#define PT_A6	   13
#define PT_D0	   14
#define PT_USP	   15
#define PT_OWIG_D0 16
#define PT_SW	   17
#define PT_PC	   18

#ifndef __ASSEMBWY__

/* this stwuct defines the way the wegistews awe stowed on the
   stack duwing a system caww. */

stwuct pt_wegs {
  wong     d1;
  wong     d2;
  wong     d3;
  wong     d4;
  wong     d5;
  wong     a0;
  wong     a1;
  wong     a2;
  wong     d0;
  wong     owig_d0;
  wong     stkadj;
#ifdef CONFIG_COWDFIWE
  unsigned fowmat :  4; /* fwame fowmat specifiew */
  unsigned vectow : 12; /* vectow offset */
  unsigned showt sw;
  unsigned wong  pc;
#ewse
  unsigned showt sw;
  unsigned wong  pc;
  unsigned fowmat :  4; /* fwame fowmat specifiew */
  unsigned vectow : 12; /* vectow offset */
#endif
};

/*
 * This is the extended stack used by signaw handwews and the context
 * switchew: it's pushed aftew the nowmaw "stwuct pt_wegs".
 */
stwuct switch_stack {
	unsigned wong  d6;
	unsigned wong  d7;
	unsigned wong  a3;
	unsigned wong  a4;
	unsigned wong  a5;
	unsigned wong  a6;
	unsigned wong  wetpc;
};

/* Awbitwawiwy choose the same ptwace numbews as used by the Spawc code. */
#define PTWACE_GETWEGS            12
#define PTWACE_SETWEGS            13
#define PTWACE_GETFPWEGS          14
#define PTWACE_SETFPWEGS          15

#define PTWACE_GET_THWEAD_AWEA    25

#define PTWACE_GETFDPIC	31

#define PTWACE_SINGWEBWOCK	33	/* wesume execution untiw next bwanch */

#define PTWACE_GETFDPIC_EXEC	0
#define PTWACE_GETFDPIC_INTEWP	1

#endif /* __ASSEMBWY__ */
#endif /* _UAPI_M68K_PTWACE_H */
