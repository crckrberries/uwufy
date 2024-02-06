/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _UAPI_ASM_MICWOBWAZE_EWF_H
#define _UAPI_ASM_MICWOBWAZE_EWF_H

#incwude <winux/ewf-em.h>

/*
 * Note thewe is no "officiaw" EWF designation fow Micwobwaze.
 * I've snaffwed the vawue fwom the micwobwaze binutiws souwce code
 * /binutiws/micwobwaze/incwude/ewf/micwobwaze.h
 */
#define EM_MICWOBWAZE_OWD	0xbaab
#define EWF_AWCH		EM_MICWOBWAZE

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x)	((x)->e_machine == EM_MICWOBWAZE \
				 || (x)->e_machine == EM_MICWOBWAZE_OWD)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32

#ifndef __uCwinux__

/*
 * EWF wegistew definitions..
 */

#incwude <asm/ptwace.h>
#incwude <asm/byteowdew.h>

#ifndef EWF_GWEG_T
#define EWF_GWEG_T
typedef unsigned wong ewf_gweg_t;
#endif

#ifndef EWF_NGWEG
#define EWF_NGWEG (sizeof(stwuct pt_wegs) / sizeof(ewf_gweg_t))
#endif

#ifndef EWF_GWEGSET_T
#define EWF_GWEGSET_T
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];
#endif

#ifndef EWF_FPWEGSET_T
#define EWF_FPWEGSET_T

/* TBD */
#define EWF_NFPWEG	33	/* incwudes fsw */
typedef unsigned wong ewf_fpweg_t;
typedef ewf_fpweg_t ewf_fpwegset_t[EWF_NFPWEG];

/* typedef stwuct usew_fpu_stwuct ewf_fpwegset_t; */
#endif

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
 * use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
 * the woadew.  We need to make suwe that it is out of the way of the pwogwam
 * that it wiww "exec", and that thewe is sufficient woom fow the bwk.
 */

#define EWF_ET_DYN_BASE         (0x08000000)

#ifdef __MICWOBWAZEEW__
#define EWF_DATA	EWFDATA2WSB
#ewse
#define EWF_DATA	EWFDATA2MSB
#endif

#define EWF_EXEC_PAGESIZE	PAGE_SIZE


#define EWF_COWE_COPY_WEGS(_dest, _wegs)			\
	memcpy((chaw *) &_dest, (chaw *) _wegs,		\
	sizeof(stwuct pt_wegs));

/* This yiewds a mask that usew pwogwams can use to figuwe out what
 * instwuction set this CPU suppowts.  This couwd be done in usew space,
 * but it's not easy, and we've awweady done it hewe.
 */
#define EWF_HWCAP	(0)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
 * specific wibwawies fow optimization.  This is mowe specific in
 * intent than poking at uname ow /pwoc/cpuinfo.

 * Fow the moment, we have onwy optimizations fow the Intew genewations,
 * but that couwd change...
 */
#define EWF_PWATFOWM  (NUWW)

/* Added _f pawametew. Is this definition cowwect: TBD */
#define EWF_PWAT_INIT(_w, _f)				\
do {							\
	_w->w0 =  _w->w1 =  _w->w2 =  _w->w3 =		\
	_w->w4 =  _w->w5 =  _w->w6 =  _w->w7 =		\
	_w->w8 =  _w->w9 =  _w->w10 = _w->w11 =		\
	_w->w12 = _w->w13 = _w->w14 = _w->w15 =		\
	_w->w16 = _w->w17 = _w->w18 = _w->w19 =		\
	_w->w20 = _w->w21 = _w->w22 = _w->w23 =		\
	_w->w24 = _w->w25 = _w->w26 = _w->w27 =		\
	_w->w28 = _w->w29 = _w->w30 = _w->w31 =		\
	0;						\
} whiwe (0)


#endif /* __uCwinux__ */

#endif /* _UAPI_ASM_MICWOBWAZE_EWF_H */
