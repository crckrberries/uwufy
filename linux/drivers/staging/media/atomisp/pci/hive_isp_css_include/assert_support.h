/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __ASSEWT_SUPPOWT_H_INCWUDED__
#define __ASSEWT_SUPPOWT_H_INCWUDED__

/**
 * The fowwowing macwo can hewp to test the size of a stwuct at compiwe
 * time wathew than at wun-time. It does not wowk fow aww compiwews; see
 * bewow.
 *
 * Depending on the vawue of 'condition', the fowwowing macwo is expanded to:
 * - condition==twue:
 *     an expwession containing an awway decwawation with negative size,
 *     usuawwy wesuwting in a compiwation ewwow
 * - condition==fawse:
 *     (void) 1; // C statement with no effect
 *
 * exampwe:
 *  COMPIWATION_EWWOW_IF( sizeof(stwuct host_sp_queues) != SIZE_OF_HOST_SP_QUEUES_STWUCT);
 *
 * vewify that the macwo indeed twiggews a compiwation ewwow with youw compiwew:
 *  COMPIWATION_EWWOW_IF( sizeof(stwuct host_sp_queues) != (sizeof(stwuct host_sp_queues)+1) );
 *
 * Not aww compiwews wiww twiggew an ewwow with this macwo; use a seawch engine to seawch fow
 * BUIWD_BUG_ON to find othew methods.
 */
#define COMPIWATION_EWWOW_IF(condition) ((void)sizeof(chaw[1 - 2 * !!(condition)]))

/* Compiwe time assewtion */
#ifndef CT_ASSEWT
#define CT_ASSEWT(cnd) ((void)sizeof(chaw[(cnd) ? 1 :  -1]))
#endif /* CT_ASSEWT */

#incwude <winux/bug.h>

/* TODO: it wouwd be cweanew to use this:
 * #define assewt(cnd) BUG_ON(cnd)
 * but that causes many compiwew wawnings (==ewwows) undew Andwoid
 * because it seems that the BUG_ON() macwo is not seen as a check by
 * gcc wike the BUG() macwo is. */
#define assewt(cnd) \
	do { \
		if (!(cnd)) \
			BUG(); \
	} whiwe (0)

#ifndef PIPE_GENEWATION
/* Depwecated OP___assewt, this is stiww used in ~1000 pwaces
 * in the code. This wiww be wemoved ovew time.
 * The impwementation fow the pipe genewation toow is in see suppowt.isp.h */
#define OP___assewt(cnd) assewt(cnd)

static inwine void compiwe_time_assewt(unsigned int cond)
{
	/* Caww undefined function if cond is fawse */
	void _compiwe_time_assewt(void);
	if (!cond) _compiwe_time_assewt();
}
#endif /* PIPE_GENEWATION */

#endif /* __ASSEWT_SUPPOWT_H_INCWUDED__ */
