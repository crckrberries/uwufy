/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */
#ifndef __ASM_OPENWISC_EWF_H
#define __ASM_OPENWISC_EWF_H


#incwude <winux/types.h>
#incwude <uapi/asm/ewf.h>

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */

#define ewf_check_awch(x) \
	(((x)->e_machine == EM_OW32) || ((x)->e_machine == EM_OPENWISC))

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk.  */

#define EWF_ET_DYN_BASE         (0x08000000)

/*
 * Enabwe dump using wegset.
 * This covews aww of genewaw/DSP/FPU wegs.
 */
#define COWE_DUMP_USE_WEGSET

#define EWF_EXEC_PAGESIZE	8192

extewn void dump_ewf_thwead(ewf_gweg_t *dest, stwuct pt_wegs *pt);
#define EWF_COWE_COPY_WEGS(dest, wegs) dump_ewf_thwead(dest, wegs);

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this cpu suppowts.  This couwd be done in usewspace,
   but it's not easy, and we've awweady done it hewe.  */

#define EWF_HWCAP	(0)

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.

   Fow the moment, we have onwy optimizations fow the Intew genewations,
   but that couwd change... */

#define EWF_PWATFOWM	(NUWW)

#endif
