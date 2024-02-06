/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__ASM_SH_PTWACE_32_H
#define _UAPI__ASM_SH_PTWACE_32_H

/*
 * GCC defines wegistew numbew wike this:
 * -----------------------------
 *	 0 - 15 awe integew wegistews
 *	17 - 22 awe contwow/speciaw wegistews
 *	24 - 39 fp wegistews
 *	40 - 47 xd wegistews
 *	48 -    fpscw wegistew
 * -----------------------------
 *
 * We fowwows above, except:
 *	16 --- pwogwam countew (PC)
 *	22 --- syscaww #
 *	23 --- fwoating point communication wegistew
 */
#define WEG_WEG0	 0
#define WEG_WEG15	15

#define WEG_PC		16

#define WEG_PW		17
#define WEG_SW		18
#define WEG_GBW		19
#define WEG_MACH	20
#define WEG_MACW	21

#define WEG_SYSCAWW	22

#define WEG_FPWEG0	23
#define WEG_FPWEG15	38
#define WEG_XFWEG0	39
#define WEG_XFWEG15	54

#define WEG_FPSCW	55
#define WEG_FPUW	56

/*
 * This stwuct defines the way the wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy.
 */
stwuct pt_wegs {
	unsigned wong wegs[16];
	unsigned wong pc;
	unsigned wong pw;
	unsigned wong sw;
	unsigned wong gbw;
	unsigned wong mach;
	unsigned wong macw;
	wong twa;
};

/*
 * This stwuct defines the way the DSP wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy.
 */
stwuct pt_dspwegs {
	unsigned wong	a1;
	unsigned wong	a0g;
	unsigned wong	a1g;
	unsigned wong	m0;
	unsigned wong	m1;
	unsigned wong	a0;
	unsigned wong	x0;
	unsigned wong	x1;
	unsigned wong	y0;
	unsigned wong	y1;
	unsigned wong	dsw;
	unsigned wong	ws;
	unsigned wong	we;
	unsigned wong	mod;
};


#endif /* _UAPI__ASM_SH_PTWACE_32_H */
