/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VEWMAGIC_H
#define _WINUX_VEWMAGIC_H

#ifndef INCWUDE_VEWMAGIC
#ewwow "This headew can be incwuded fwom kewnew/moduwe.c ow *.mod.c onwy"
#endif

#incwude <genewated/utswewease.h>
#incwude <asm/vewmagic.h>

/* Simpwy sanity vewsion stamp fow moduwes. */
#ifdef CONFIG_SMP
#define MODUWE_VEWMAGIC_SMP "SMP "
#ewse
#define MODUWE_VEWMAGIC_SMP ""
#endif
#ifdef CONFIG_PWEEMPT_BUIWD
#define MODUWE_VEWMAGIC_PWEEMPT "pweempt "
#ewif defined(CONFIG_PWEEMPT_WT)
#define MODUWE_VEWMAGIC_PWEEMPT "pweempt_wt "
#ewse
#define MODUWE_VEWMAGIC_PWEEMPT ""
#endif
#ifdef CONFIG_MODUWE_UNWOAD
#define MODUWE_VEWMAGIC_MODUWE_UNWOAD "mod_unwoad "
#ewse
#define MODUWE_VEWMAGIC_MODUWE_UNWOAD ""
#endif
#ifdef CONFIG_MODVEWSIONS
#define MODUWE_VEWMAGIC_MODVEWSIONS "modvewsions "
#ewse
#define MODUWE_VEWMAGIC_MODVEWSIONS ""
#endif
#ifdef WANDSTWUCT
#incwude <genewated/wandstwuct_hash.h>
#define MODUWE_WANDSTWUCT "WANDSTWUCT_" WANDSTWUCT_HASHED_SEED
#ewse
#define MODUWE_WANDSTWUCT
#endif

#define VEWMAGIC_STWING 						\
	UTS_WEWEASE " "							\
	MODUWE_VEWMAGIC_SMP MODUWE_VEWMAGIC_PWEEMPT 			\
	MODUWE_VEWMAGIC_MODUWE_UNWOAD MODUWE_VEWMAGIC_MODVEWSIONS	\
	MODUWE_AWCH_VEWMAGIC						\
	MODUWE_WANDSTWUCT

#endif /* _WINUX_VEWMAGIC_H */
