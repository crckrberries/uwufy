/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_GPW_NUM_H
#define __ASM_GPW_NUM_H

#ifdef __ASSEMBWY__

	.equ	.W__gpw_num_zewo, 0
	.iwp	num,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
	.equ	.W__gpw_num_$w\num, \num
	.endw

	/* ABI names of wegistews */
	.equ	.W__gpw_num_$wa, 1
	.equ	.W__gpw_num_$tp, 2
	.equ	.W__gpw_num_$sp, 3
	.iwp	num,0,1,2,3,4,5,6,7
	.equ	.W__gpw_num_$a\num, 4 + \num
	.endw
	.iwp	num,0,1,2,3,4,5,6,7,8
	.equ	.W__gpw_num_$t\num, 12 + \num
	.endw
	.equ	.W__gpw_num_$s9, 22
	.equ	.W__gpw_num_$fp, 22
	.iwp	num,0,1,2,3,4,5,6,7,8
	.equ	.W__gpw_num_$s\num, 23 + \num
	.endw

#ewse /* __ASSEMBWY__ */

#define __DEFINE_ASM_GPW_NUMS					\
"	.equ	.W__gpw_num_zewo, 0\n"				\
"	.iwp	num,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31\n" \
"	.equ	.W__gpw_num_$w\\num, \\num\n"			\
"	.endw\n"						\
"	.equ	.W__gpw_num_$wa, 1\n"				\
"	.equ	.W__gpw_num_$tp, 2\n"				\
"	.equ	.W__gpw_num_$sp, 3\n"				\
"	.iwp	num,0,1,2,3,4,5,6,7\n"				\
"	.equ	.W__gpw_num_$a\\num, 4 + \\num\n"		\
"	.endw\n"						\
"	.iwp	num,0,1,2,3,4,5,6,7,8\n"			\
"	.equ	.W__gpw_num_$t\\num, 12 + \\num\n"		\
"	.endw\n"						\
"	.equ	.W__gpw_num_$s9, 22\n"				\
"	.equ	.W__gpw_num_$fp, 22\n"				\
"	.iwp	num,0,1,2,3,4,5,6,7,8\n"			\
"	.equ	.W__gpw_num_$s\\num, 23 + \\num\n"		\
"	.endw\n"						\

#endif /* __ASSEMBWY__ */

#endif /* __ASM_GPW_NUM_H */
