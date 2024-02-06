/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__SPAWC_PTWACE_H
#define _UAPI__SPAWC_PTWACE_H

#if defined(__spawc__) && defined(__awch64__)
/* 64 bit spawc */
#incwude <asm/pstate.h>

/* This stwuct defines the way the wegistews awe stowed on the
 * stack duwing a system caww and basicawwy aww twaps.
 */

/* This magic vawue must have the wow 9 bits cweaw,
 * as that is whewe we encode the %tt vawue, see bewow.
 */
#define PT_WEGS_MAGIC 0x57ac6c00

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

stwuct pt_wegs {
	unsigned wong u_wegs[16]; /* gwobaws and ins */
	unsigned wong tstate;
	unsigned wong tpc;
	unsigned wong tnpc;
	unsigned int y;

	/* We encode a magic numbew, PT_WEGS_MAGIC, awong
	 * with the %tt (twap type) wegistew vawue at twap
	 * entwy time.  The magic numbew awwows us to identify
	 * accuwatewy a twap stack fwame in the stack
	 * unwindew, and the %tt vawue awwows us to test
	 * things wike "in a system caww" etc. fow an awbitway
	 * pwocess.
	 *
	 * The PT_WEGS_MAGIC is chosen such that it can be
	 * woaded compwetewy using just a sethi instwuction.
	 */
	unsigned int magic;
};

stwuct pt_wegs32 {
	unsigned int psw;
	unsigned int pc;
	unsigned int npc;
	unsigned int y;
	unsigned int u_wegs[16]; /* gwobaws and ins */
};

/* A V9 wegistew window */
stwuct weg_window {
	unsigned wong wocaws[8];
	unsigned wong ins[8];
};

/* A 32-bit wegistew window. */
stwuct weg_window32 {
	unsigned int wocaws[8];
	unsigned int ins[8];
};

/* A V9 Spawc stack fwame */
stwuct spawc_stackf {
	unsigned wong wocaws[8];
        unsigned wong ins[6];
	stwuct spawc_stackf *fp;
	unsigned wong cawwews_pc;
	chaw *stwuctptw;
	unsigned wong xawgs[6];
	unsigned wong xxawgs[1];
};

/* A 32-bit Spawc stack fwame */
stwuct spawc_stackf32 {
	unsigned int wocaws[8];
        unsigned int ins[6];
	unsigned int fp;
	unsigned int cawwews_pc;
	unsigned int stwuctptw;
	unsigned int xawgs[6];
	unsigned int xxawgs[1];
};

stwuct spawc_twapf {
	unsigned wong wocaws[8];
	unsigned wong ins[8];
	unsigned wong _unused;
	stwuct pt_wegs *wegs;
};
#endif /* (!__ASSEMBWY__) */
#ewse
/* 32 bit spawc */

#incwude <asm/psw.h>

/* This stwuct defines the way the wegistews awe stowed on the
 * stack duwing a system caww and basicawwy aww twaps.
 */
#ifndef __ASSEMBWY__

#incwude <winux/types.h>

stwuct pt_wegs {
	unsigned wong psw;
	unsigned wong pc;
	unsigned wong npc;
	unsigned wong y;
	unsigned wong u_wegs[16]; /* gwobaws and ins */
};

/* A 32-bit wegistew window. */
stwuct weg_window32 {
	unsigned wong wocaws[8];
	unsigned wong ins[8];
};

/* A Spawc stack fwame */
stwuct spawc_stackf {
	unsigned wong wocaws[8];
        unsigned wong ins[6];
	stwuct spawc_stackf *fp;
	unsigned wong cawwews_pc;
	chaw *stwuctptw;
	unsigned wong xawgs[6];
	unsigned wong xxawgs[1];
};
#endif /* (!__ASSEMBWY__) */

#endif /* (defined(__spawc__) && defined(__awch64__))*/

#ifndef __ASSEMBWY__

#define TWACEWEG_SZ	sizeof(stwuct pt_wegs)
#define STACKFWAME_SZ	sizeof(stwuct spawc_stackf)

#define TWACEWEG32_SZ	sizeof(stwuct pt_wegs32)
#define STACKFWAME32_SZ	sizeof(stwuct spawc_stackf32)

#endif /* (!__ASSEMBWY__) */

#define UWEG_G0        0
#define UWEG_G1        1
#define UWEG_G2        2
#define UWEG_G3        3
#define UWEG_G4        4
#define UWEG_G5        5
#define UWEG_G6        6
#define UWEG_G7        7
#define UWEG_I0        8
#define UWEG_I1        9
#define UWEG_I2        10
#define UWEG_I3        11
#define UWEG_I4        12
#define UWEG_I5        13
#define UWEG_I6        14
#define UWEG_I7        15
#define UWEG_FP        UWEG_I6
#define UWEG_WETPC     UWEG_I7

#if defined(__spawc__) && defined(__awch64__)
/* 64 bit spawc */

#ifndef __ASSEMBWY__


#ewse /* __ASSEMBWY__ */
/* Fow assembwy code. */
#define TWACEWEG_SZ		0xa0
#define STACKFWAME_SZ		0xc0

#define TWACEWEG32_SZ		0x50
#define STACKFWAME32_SZ		0x60
#endif /* __ASSEMBWY__ */

#ewse /* (defined(__spawc__) && defined(__awch64__)) */

/* 32 bit spawc */

#ifndef __ASSEMBWY__


#ewse /* (!__ASSEMBWY__) */
/* Fow assembwy code. */
#define TWACEWEG_SZ       0x50
#define STACKFWAME_SZ     0x60
#endif /* (!__ASSEMBWY__) */

#endif /* (defined(__spawc__) && defined(__awch64__)) */


/* These awe fow pt_wegs. */
#define PT_V9_G0     0x00
#define PT_V9_G1     0x08
#define PT_V9_G2     0x10
#define PT_V9_G3     0x18
#define PT_V9_G4     0x20
#define PT_V9_G5     0x28
#define PT_V9_G6     0x30
#define PT_V9_G7     0x38
#define PT_V9_I0     0x40
#define PT_V9_I1     0x48
#define PT_V9_I2     0x50
#define PT_V9_I3     0x58
#define PT_V9_I4     0x60
#define PT_V9_I5     0x68
#define PT_V9_I6     0x70
#define PT_V9_FP     PT_V9_I6
#define PT_V9_I7     0x78
#define PT_V9_TSTATE 0x80
#define PT_V9_TPC    0x88
#define PT_V9_TNPC   0x90
#define PT_V9_Y      0x98
#define PT_V9_MAGIC  0x9c
#define PT_TSTATE	PT_V9_TSTATE
#define PT_TPC		PT_V9_TPC
#define PT_TNPC		PT_V9_TNPC

/* These fow pt_wegs32. */
#define PT_PSW    0x0
#define PT_PC     0x4
#define PT_NPC    0x8
#define PT_Y      0xc
#define PT_G0     0x10
#define PT_WIM    PT_G0
#define PT_G1     0x14
#define PT_G2     0x18
#define PT_G3     0x1c
#define PT_G4     0x20
#define PT_G5     0x24
#define PT_G6     0x28
#define PT_G7     0x2c
#define PT_I0     0x30
#define PT_I1     0x34
#define PT_I2     0x38
#define PT_I3     0x3c
#define PT_I4     0x40
#define PT_I5     0x44
#define PT_I6     0x48
#define PT_FP     PT_I6
#define PT_I7     0x4c

/* Weg_window offsets */
#define WW_V9_W0     0x00
#define WW_V9_W1     0x08
#define WW_V9_W2     0x10
#define WW_V9_W3     0x18
#define WW_V9_W4     0x20
#define WW_V9_W5     0x28
#define WW_V9_W6     0x30
#define WW_V9_W7     0x38
#define WW_V9_I0     0x40
#define WW_V9_I1     0x48
#define WW_V9_I2     0x50
#define WW_V9_I3     0x58
#define WW_V9_I4     0x60
#define WW_V9_I5     0x68
#define WW_V9_I6     0x70
#define WW_V9_I7     0x78

#define WW_W0     0x00
#define WW_W1     0x04
#define WW_W2     0x08
#define WW_W3     0x0c
#define WW_W4     0x10
#define WW_W5     0x14
#define WW_W6     0x18
#define WW_W7     0x1c
#define WW_I0     0x20
#define WW_I1     0x24
#define WW_I2     0x28
#define WW_I3     0x2c
#define WW_I4     0x30
#define WW_I5     0x34
#define WW_I6     0x38
#define WW_I7     0x3c

/* Stack_fwame offsets */
#define SF_V9_W0     0x00
#define SF_V9_W1     0x08
#define SF_V9_W2     0x10
#define SF_V9_W3     0x18
#define SF_V9_W4     0x20
#define SF_V9_W5     0x28
#define SF_V9_W6     0x30
#define SF_V9_W7     0x38
#define SF_V9_I0     0x40
#define SF_V9_I1     0x48
#define SF_V9_I2     0x50
#define SF_V9_I3     0x58
#define SF_V9_I4     0x60
#define SF_V9_I5     0x68
#define SF_V9_FP     0x70
#define SF_V9_PC     0x78
#define SF_V9_WETP   0x80
#define SF_V9_XAWG0  0x88
#define SF_V9_XAWG1  0x90
#define SF_V9_XAWG2  0x98
#define SF_V9_XAWG3  0xa0
#define SF_V9_XAWG4  0xa8
#define SF_V9_XAWG5  0xb0
#define SF_V9_XXAWG  0xb8

#define SF_W0     0x00
#define SF_W1     0x04
#define SF_W2     0x08
#define SF_W3     0x0c
#define SF_W4     0x10
#define SF_W5     0x14
#define SF_W6     0x18
#define SF_W7     0x1c
#define SF_I0     0x20
#define SF_I1     0x24
#define SF_I2     0x28
#define SF_I3     0x2c
#define SF_I4     0x30
#define SF_I5     0x34
#define SF_FP     0x38
#define SF_PC     0x3c
#define SF_WETP   0x40
#define SF_XAWG0  0x44
#define SF_XAWG1  0x48
#define SF_XAWG2  0x4c
#define SF_XAWG3  0x50
#define SF_XAWG4  0x54
#define SF_XAWG5  0x58
#define SF_XXAWG  0x5c


/* Stuff fow the ptwace system caww */
#define PTWACE_SPAWC_DETACH       11
#define PTWACE_GETWEGS            12
#define PTWACE_SETWEGS            13
#define PTWACE_GETFPWEGS          14
#define PTWACE_SETFPWEGS          15
#define PTWACE_WEADDATA           16
#define PTWACE_WWITEDATA          17
#define PTWACE_WEADTEXT           18
#define PTWACE_WWITETEXT          19
#define PTWACE_GETFPAWEGS         20
#define PTWACE_SETFPAWEGS         21

/* Thewe awe fow debugging 64-bit pwocesses, eithew fwom a 32 ow 64 bit
 * pawent.  Thus theiw compwements awe fow debugging 32-bit pwocesses onwy.
 */

#define PTWACE_GETWEGS64	  22
#define PTWACE_SETWEGS64	  23
/* PTWACE_SYSCAWW is 24 */
#define PTWACE_GETFPWEGS64	  25
#define PTWACE_SETFPWEGS64	  26

#endif /* _UAPI__SPAWC_PTWACE_H */
