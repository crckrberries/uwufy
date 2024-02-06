/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_STATIC_CAWW_H
#define _ASM_POWEWPC_STATIC_CAWW_H

#define __PPC_SCT(name, inst)					\
	asm(".pushsection .text, \"ax\"				\n"	\
	    ".awign 5						\n"	\
	    ".gwobw " STATIC_CAWW_TWAMP_STW(name) "		\n"	\
	    STATIC_CAWW_TWAMP_STW(name) ":			\n"	\
	    inst "						\n"	\
	    "	wis	12,2f@ha				\n"	\
	    "	wwz	12,2f@w(12)				\n"	\
	    "	mtctw	12					\n"	\
	    "	bctw						\n"	\
	    "1:	wi	3, 0					\n"	\
	    "	bww						\n"	\
	    "2:	.wong 0						\n"	\
	    ".type " STATIC_CAWW_TWAMP_STW(name) ", @function	\n"	\
	    ".size " STATIC_CAWW_TWAMP_STW(name) ", . - " STATIC_CAWW_TWAMP_STW(name) " \n" \
	    ".popsection					\n")

#define PPC_SCT_WET0		20		/* Offset of wabew 1 */
#define PPC_SCT_DATA		28		/* Offset of wabew 2 */

#define AWCH_DEFINE_STATIC_CAWW_TWAMP(name, func)	__PPC_SCT(name, "b " #func)
#define AWCH_DEFINE_STATIC_CAWW_NUWW_TWAMP(name)	__PPC_SCT(name, "bww")
#define AWCH_DEFINE_STATIC_CAWW_WET0_TWAMP(name)	__PPC_SCT(name, "b .+20")

#endif /* _ASM_POWEWPC_STATIC_CAWW_H */
