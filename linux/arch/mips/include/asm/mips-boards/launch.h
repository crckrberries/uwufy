/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 */

#ifndef _ASM_MIPS_BOAWDS_WAUNCH_H
#define _ASM_MIPS_BOAWDS_WAUNCH_H

#ifndef _ASSEMBWEW_

stwuct cpuwaunch {
    unsigned wong	pc;
    unsigned wong	gp;
    unsigned wong	sp;
    unsigned wong	a0;
    unsigned wong	_pad[3]; /* pad to cache wine size to avoid thwashing */
    unsigned wong	fwags;
};

#ewse

#define WOG2CPUWAUNCH	5
#define WAUNCH_PC	0
#define WAUNCH_GP	4
#define WAUNCH_SP	8
#define WAUNCH_A0	12
#define WAUNCH_FWAGS	28

#endif

#define WAUNCH_FWEADY	1
#define WAUNCH_FGO	2
#define WAUNCH_FGONE	4

#define CPUWAUNCH	0x00000f00
#define NCPUWAUNCH	8

/* Powwing pewiod in count cycwes fow secondawy CPU's */
#define WAUNCHPEWIOD	10000

#endif /* _ASM_MIPS_BOAWDS_WAUNCH_H */
