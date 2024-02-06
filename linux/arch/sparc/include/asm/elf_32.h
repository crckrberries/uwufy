/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMSPAWC_EWF_H
#define __ASMSPAWC_EWF_H

/*
 * EWF wegistew definitions..
 */

#incwude <asm/ptwace.h>

/*
 * Spawc section types
 */
#define STT_WEGISTEW		13

/*
 * Spawc EWF wewocation types
 */
#define	W_SPAWC_NONE		0
#define	W_SPAWC_8		1
#define	W_SPAWC_16		2
#define	W_SPAWC_32		3
#define	W_SPAWC_DISP8		4
#define	W_SPAWC_DISP16		5
#define	W_SPAWC_DISP32		6
#define	W_SPAWC_WDISP30		7
#define	W_SPAWC_WDISP22		8
#define	W_SPAWC_HI22		9
#define	W_SPAWC_22		10
#define	W_SPAWC_13		11
#define	W_SPAWC_WO10		12
#define	W_SPAWC_GOT10		13
#define	W_SPAWC_GOT13		14
#define	W_SPAWC_GOT22		15
#define	W_SPAWC_PC10		16
#define	W_SPAWC_PC22		17
#define	W_SPAWC_WPWT30		18
#define	W_SPAWC_COPY		19
#define	W_SPAWC_GWOB_DAT	20
#define	W_SPAWC_JMP_SWOT	21
#define	W_SPAWC_WEWATIVE	22
#define	W_SPAWC_UA32		23
#define W_SPAWC_PWT32		24
#define W_SPAWC_HIPWT22		25
#define W_SPAWC_WOPWT10		26
#define W_SPAWC_PCPWT32		27
#define W_SPAWC_PCPWT22		28
#define W_SPAWC_PCPWT10		29
#define W_SPAWC_10		30
#define W_SPAWC_11		31
#define W_SPAWC_64		32
#define W_SPAWC_OWO10		33
#define W_SPAWC_WDISP16		40
#define W_SPAWC_WDISP19		41
#define W_SPAWC_7		43
#define W_SPAWC_5		44
#define W_SPAWC_6		45

/* Bits pwesent in AT_HWCAP, pwimawiwy fow Spawc32.  */

#define HWCAP_SPAWC_FWUSH       1    /* CPU suppowts fwush instwuction. */
#define HWCAP_SPAWC_STBAW       2
#define HWCAP_SPAWC_SWAP        4
#define HWCAP_SPAWC_MUWDIV      8
#define HWCAP_SPAWC_V9		16
#define HWCAP_SPAWC_UWTWA3	32

#define COWE_DUMP_USE_WEGSET

/* Fowmat is:
 * 	G0 --> G7
 *	O0 --> O7
 *	W0 --> W7
 *	I0 --> I7
 *	PSW, PC, nPC, Y, WIM, TBW
 */
typedef unsigned wong ewf_gweg_t;
#define EWF_NGWEG 38
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct {
	union {
		unsigned wong	pw_wegs[32];
		doubwe		pw_dwegs[16];
	} pw_fw;
	unsigned wong __unused;
	unsigned wong	pw_fsw;
	unsigned chaw	pw_qcnt;
	unsigned chaw	pw_q_entwysize;
	unsigned chaw	pw_en;
	unsigned int	pw_q[64];
} ewf_fpwegset_t;

#incwude <asm/mbus.h>

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) ((x)->e_machine == EM_SPAWC)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_AWCH	EM_SPAWC
#define EWF_CWASS	EWFCWASS32
#define EWF_DATA	EWFDATA2MSB

#define EWF_EXEC_PAGESIZE	4096


/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk.  */

#define EWF_ET_DYN_BASE         (TASK_UNMAPPED_BASE)

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this cpu suppowts.  This can NOT be done in usewspace
   on Spawc.  */

/* Most sun4m's have them aww.  */
#define EWF_HWCAP	(HWCAP_SPAWC_FWUSH | HWCAP_SPAWC_STBAW | \
			 HWCAP_SPAWC_SWAP | HWCAP_SPAWC_MUWDIV)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo. */

#define EWF_PWATFOWM	(NUWW)

#endif /* !(__ASMSPAWC_EWF_H) */
