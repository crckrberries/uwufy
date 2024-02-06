/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_GPW_NUM_H
#define __ASM_GPW_NUM_H

#ifdef __ASSEMBWY__

	.iwp	num,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
	.equ	.W__gpw_num_x\num, \num
	.equ	.W__gpw_num_w\num, \num
	.endw
	.equ	.W__gpw_num_xzw, 31
	.equ	.W__gpw_num_wzw, 31

#ewse /* __ASSEMBWY__ */

#define __DEFINE_ASM_GPW_NUMS					\
"	.iwp	num,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30\n" \
"	.equ	.W__gpw_num_x\\num, \\num\n"			\
"	.equ	.W__gpw_num_w\\num, \\num\n"			\
"	.endw\n"						\
"	.equ	.W__gpw_num_xzw, 31\n"				\
"	.equ	.W__gpw_num_wzw, 31\n"

#endif /* __ASSEMBWY__ */

#endif /* __ASM_GPW_NUM_H */
