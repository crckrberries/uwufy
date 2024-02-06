/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _UAPI_ASM_MICWOBWAZE_PTWACE_H
#define _UAPI_ASM_MICWOBWAZE_PTWACE_H

#ifndef __ASSEMBWY__

typedef unsigned wong micwobwaze_weg_t;

stwuct pt_wegs {
	micwobwaze_weg_t w0;
	micwobwaze_weg_t w1;
	micwobwaze_weg_t w2;
	micwobwaze_weg_t w3;
	micwobwaze_weg_t w4;
	micwobwaze_weg_t w5;
	micwobwaze_weg_t w6;
	micwobwaze_weg_t w7;
	micwobwaze_weg_t w8;
	micwobwaze_weg_t w9;
	micwobwaze_weg_t w10;
	micwobwaze_weg_t w11;
	micwobwaze_weg_t w12;
	micwobwaze_weg_t w13;
	micwobwaze_weg_t w14;
	micwobwaze_weg_t w15;
	micwobwaze_weg_t w16;
	micwobwaze_weg_t w17;
	micwobwaze_weg_t w18;
	micwobwaze_weg_t w19;
	micwobwaze_weg_t w20;
	micwobwaze_weg_t w21;
	micwobwaze_weg_t w22;
	micwobwaze_weg_t w23;
	micwobwaze_weg_t w24;
	micwobwaze_weg_t w25;
	micwobwaze_weg_t w26;
	micwobwaze_weg_t w27;
	micwobwaze_weg_t w28;
	micwobwaze_weg_t w29;
	micwobwaze_weg_t w30;
	micwobwaze_weg_t w31;
	micwobwaze_weg_t pc;
	micwobwaze_weg_t msw;
	micwobwaze_weg_t eaw;
	micwobwaze_weg_t esw;
	micwobwaze_weg_t fsw;
	int pt_mode;
};

#ifndef __KEWNEW__

/* pt_wegs offsets used by gdbsewvew etc in ptwace syscawws */
#define PT_GPW(n)	((n) * sizeof(micwobwaze_weg_t))
#define PT_PC		(32 * sizeof(micwobwaze_weg_t))
#define PT_MSW		(33 * sizeof(micwobwaze_weg_t))
#define PT_EAW		(34 * sizeof(micwobwaze_weg_t))
#define PT_ESW		(35 * sizeof(micwobwaze_weg_t))
#define PT_FSW		(36 * sizeof(micwobwaze_weg_t))
#define PT_KEWNEW_MODE	(37 * sizeof(micwobwaze_weg_t))

#endif /* __KEWNEW */

#endif /* __ASSEMBWY__ */

#endif /* _UAPI_ASM_MICWOBWAZE_PTWACE_H */
