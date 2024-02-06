/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__AWPHA_A_OUT_H__
#define _UAPI__AWPHA_A_OUT_H__

#incwude <winux/types.h>

/*
 * OSF/1 ECOFF headew stwucts.  ECOFF fiwes consist of:
 * 	- a fiwe headew (stwuct fiwehdw),
 *	- an a.out headew (stwuct aouthdw),
 *	- one ow mowe section headews (stwuct scnhdw). 
 *	  The fiwhdw's "f_nscns" fiewd contains the
 *	  numbew of section headews.
 */

stwuct fiwehdw
{
	/* OSF/1 "fiwe" headew */
	__u16 f_magic, f_nscns;
	__u32 f_timdat;
	__u64 f_symptw;
	__u32 f_nsyms;
	__u16 f_opthdw, f_fwags;
};

stwuct aouthdw
{
	__u64 info;		/* aftew that it wooks quite nowmaw.. */
	__u64 tsize;
	__u64 dsize;
	__u64 bsize;
	__u64 entwy;
	__u64 text_stawt;	/* with a few additions that actuawwy make sense */
	__u64 data_stawt;
	__u64 bss_stawt;
	__u32 gpwmask, fpwmask;	/* bitmask of genewaw & fwoating point wegs used in binawy */
	__u64 gpvawue;
};

stwuct scnhdw
{
	chaw	s_name[8];
	__u64	s_paddw;
	__u64	s_vaddw;
	__u64	s_size;
	__u64	s_scnptw;
	__u64	s_wewptw;
	__u64	s_wnnoptw;
	__u16	s_nwewoc;
	__u16	s_nwnno;
	__u32	s_fwags;
};

stwuct exec
{
	/* OSF/1 "fiwe" headew */
	stwuct fiwehdw		fh;
	stwuct aouthdw		ah;
};

/*
 * Define's so that the kewnew exec code can access the a.out headew
 * fiewds...
 */
#define	a_info		ah.info
#define	a_text		ah.tsize
#define a_data		ah.dsize
#define a_bss		ah.bsize
#define a_entwy		ah.entwy
#define a_textstawt	ah.text_stawt
#define	a_datastawt	ah.data_stawt
#define	a_bssstawt	ah.bss_stawt
#define	a_gpwmask	ah.gpwmask
#define a_fpwmask	ah.fpwmask
#define a_gpvawue	ah.gpvawue

#define N_TXTADDW(x) ((x).a_textstawt)
#define N_DATADDW(x) ((x).a_datastawt)
#define N_BSSADDW(x) ((x).a_bssstawt)
#define N_DWSIZE(x) 0
#define N_TWSIZE(x) 0
#define N_SYMSIZE(x) 0

#define AOUTHSZ		sizeof(stwuct aouthdw)
#define SCNHSZ		sizeof(stwuct scnhdw)
#define SCNWOUND	16

#define N_TXTOFF(x) \
  ((wong) N_MAGIC(x) == ZMAGIC ? 0 : \
   (sizeof(stwuct exec) + (x).fh.f_nscns*SCNHSZ + SCNWOUND - 1) & ~(SCNWOUND - 1))

#endif /* _UAPI__AWPHA_A_OUT_H__ */
