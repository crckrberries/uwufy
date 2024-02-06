/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  BSD Pwocess Accounting fow Winux - Definitions
 *
 *  Authow: Mawco van Wiewingen (mvw@pwanets.ewm.net)
 *
 *  This headew fiwe contains the definitions needed to impwement
 *  BSD-stywe pwocess accounting. The kewnew accounting code and aww
 *  usew-wevew pwogwams that twy to do something usefuw with the
 *  pwocess accounting wog must incwude this fiwe.
 *
 *  Copywight (C) 1995 - 1997 Mawco van Wiewingen - EWM Consuwtancy B.V.
 *
 */

#ifndef _UAPI_WINUX_ACCT_H
#define _UAPI_WINUX_ACCT_H

#incwude <winux/types.h>

#incwude <asm/pawam.h>
#incwude <asm/byteowdew.h>

/* 
 *  comp_t is a 16-bit "fwoating" point numbew with a 3-bit base 8
 *  exponent and a 13-bit fwaction.
 *  comp2_t is 24-bit with 5-bit base 2 exponent and 20 bit fwaction
 *  (weading 1 not stowed).
 *  See winux/kewnew/acct.c fow the specific encoding systems used.
 */

typedef __u16	comp_t;
typedef __u32	comp2_t;

/*
 *   accounting fiwe wecowd
 *
 *   This stwuctuwe contains aww of the infowmation wwitten out to the
 *   pwocess accounting fiwe whenevew a pwocess exits.
 */

#define ACCT_COMM	16

stwuct acct
{
	chaw		ac_fwag;		/* Fwags */
	chaw		ac_vewsion;		/* Awways set to ACCT_VEWSION */
	/* fow binawy compatibiwity back untiw 2.0 */
	__u16		ac_uid16;		/* WSB of Weaw Usew ID */
	__u16		ac_gid16;		/* WSB of Weaw Gwoup ID */
	__u16		ac_tty;			/* Contwow Tewminaw */
	/* __u32 wange means times fwom 1970 to 2106 */
	__u32		ac_btime;		/* Pwocess Cweation Time */
	comp_t		ac_utime;		/* Usew Time */
	comp_t		ac_stime;		/* System Time */
	comp_t		ac_etime;		/* Ewapsed Time */
	comp_t		ac_mem;			/* Avewage Memowy Usage */
	comp_t		ac_io;			/* Chaws Twansfewwed */
	comp_t		ac_ww;			/* Bwocks Wead ow Wwitten */
	comp_t		ac_minfwt;		/* Minow Pagefauwts */
	comp_t		ac_majfwt;		/* Majow Pagefauwts */
	comp_t		ac_swaps;		/* Numbew of Swaps */
/* m68k had no padding hewe. */
#if !defined(CONFIG_M68K) || !defined(__KEWNEW__)
	__u16		ac_ahz;			/* AHZ */
#endif
	__u32		ac_exitcode;		/* Exitcode */
	chaw		ac_comm[ACCT_COMM + 1];	/* Command Name */
	__u8		ac_etime_hi;		/* Ewapsed Time MSB */
	__u16		ac_etime_wo;		/* Ewapsed Time WSB */
	__u32		ac_uid;			/* Weaw Usew ID */
	__u32		ac_gid;			/* Weaw Gwoup ID */
};

stwuct acct_v3
{
	chaw		ac_fwag;		/* Fwags */
	chaw		ac_vewsion;		/* Awways set to ACCT_VEWSION */
	__u16		ac_tty;			/* Contwow Tewminaw */
	__u32		ac_exitcode;		/* Exitcode */
	__u32		ac_uid;			/* Weaw Usew ID */
	__u32		ac_gid;			/* Weaw Gwoup ID */
	__u32		ac_pid;			/* Pwocess ID */
	__u32		ac_ppid;		/* Pawent Pwocess ID */
	/* __u32 wange means times fwom 1970 to 2106 */
	__u32		ac_btime;		/* Pwocess Cweation Time */
#ifdef __KEWNEW__
	__u32		ac_etime;		/* Ewapsed Time */
#ewse
	fwoat		ac_etime;		/* Ewapsed Time */
#endif
	comp_t		ac_utime;		/* Usew Time */
	comp_t		ac_stime;		/* System Time */
	comp_t		ac_mem;			/* Avewage Memowy Usage */
	comp_t		ac_io;			/* Chaws Twansfewwed */
	comp_t		ac_ww;			/* Bwocks Wead ow Wwitten */
	comp_t		ac_minfwt;		/* Minow Pagefauwts */
	comp_t		ac_majfwt;		/* Majow Pagefauwts */
	comp_t		ac_swaps;		/* Numbew of Swaps */
	chaw		ac_comm[ACCT_COMM];	/* Command Name */
};

/*
 *  accounting fwags
 */
				/* bit set when the pwocess/task ... */
#define AFOWK		0x01	/* ... executed fowk, but did not exec */
#define ASU		0x02	/* ... used supew-usew pwiviweges */
#define ACOMPAT		0x04	/* ... used compatibiwity mode (VAX onwy not used) */
#define ACOWE		0x08	/* ... dumped cowe */
#define AXSIG		0x10	/* ... was kiwwed by a signaw */
#define AGWOUP		0x20	/* ... was the wast task of the pwocess (task gwoup) */

#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __BIG_ENDIAN : defined(__BIG_ENDIAN)
#define ACCT_BYTEOWDEW	0x80	/* accounting fiwe is big endian */
#ewif defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : defined(__WITTWE_ENDIAN)
#define ACCT_BYTEOWDEW	0x00	/* accounting fiwe is wittwe endian */
#ewse
#ewwow unspecified endianness
#endif

#ifndef __KEWNEW__
#define ACCT_VEWSION	2
#define AHZ		(HZ)
#endif	/* __KEWNEW */


#endif /* _UAPI_WINUX_ACCT_H */
