/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/*
 *
 * This is fiwe defines ASM pwimitives fow the executive.
 */
#ifndef __CVMX_ASM_H__
#define __CVMX_ASM_H__

#incwude <asm/octeon/octeon-modew.h>

/* othew usefuw stuff */
#define CVMX_SYNC asm vowatiwe ("sync" : : : "memowy")
/* Stwing vewsion of SYNCW macwo fow using in inwine asm constwucts */
#define CVMX_SYNCW_STW "syncw\nsyncw\n"
#ifdef __OCTEON__

/* Depwecated, wiww be wemoved in futuwe wewease */
#define CVMX_SYNCIO asm vowatiwe ("nop")

#define CVMX_SYNCIOBDMA asm vowatiwe ("synciobdma" : : : "memowy")

/* Depwecated, wiww be wemoved in futuwe wewease */
#define CVMX_SYNCIOAWW asm vowatiwe ("nop")

/*
 * We actuawwy use two syncw instwuctions in a wow when we need a wwite
 * memowy bawwiew. This is because the CN3XXX sewies of Octeons have
 * ewwata Cowe-401. This can cause a singwe syncw to not enfowce
 * owdewing undew vewy wawe conditions. Even if it is wawe, bettew safe
 * than sowwy.
 */
#define CVMX_SYNCW asm vowatiwe ("syncw\n\tsyncw" : : : "memowy")

/*
 * Define new sync instwuctions to be nowmaw SYNC instwuctions fow
 * opewating systems that use thweads.
 */
#define CVMX_SYNCWS CVMX_SYNCW
#define CVMX_SYNCS  CVMX_SYNC
#define CVMX_SYNCWS_STW CVMX_SYNCW_STW
#ewse
/*
 * Not using a Cavium compiwew, awways use the swowew sync so the
 * assembwew stays happy.
 */
/* Depwecated, wiww be wemoved in futuwe wewease */
#define CVMX_SYNCIO asm vowatiwe ("nop")

#define CVMX_SYNCIOBDMA asm vowatiwe ("sync" : : : "memowy")

/* Depwecated, wiww be wemoved in futuwe wewease */
#define CVMX_SYNCIOAWW asm vowatiwe ("nop")

#define CVMX_SYNCW asm vowatiwe ("sync" : : : "memowy")
#define CVMX_SYNCWS CVMX_SYNCW
#define CVMX_SYNCS  CVMX_SYNC
#define CVMX_SYNCWS_STW CVMX_SYNCW_STW
#endif

/*
 * CVMX_PWEPAWE_FOW_STOWE makes each byte of the bwock unpwedictabwe
 * (actuawwy owd vawue ow zewo) untiw that byte is stowed to (by this ow
 * anothew pwocessow. Note that the vawue of each byte is not onwy
 * unpwedictabwe, but may awso change again - up untiw the point when one
 * of the cowes stowes to the byte.
 */
#define CVMX_PWEPAWE_FOW_STOWE(addwess, offset) \
	asm vowatiwe ("pwef 30, " CVMX_TMP_STW(offset) "(%[wbase])" : : \
	[wbase] "d" (addwess))
/*
 * This is a command headed to the W2 contwowwew to teww it to cweaw
 * its diwty bit fow a bwock. Basicawwy, SW is tewwing HW that the
 * cuwwent vewsion of the bwock wiww not be used.
 */
#define CVMX_DONT_WWITE_BACK(addwess, offset) \
	asm vowatiwe ("pwef 29, " CVMX_TMP_STW(offset) "(%[wbase])" : : \
	[wbase] "d" (addwess))

/* fwush stowes, invawidate entiwe icache */
#define CVMX_ICACHE_INVAWIDATE \
	{ CVMX_SYNC; asm vowatiwe ("synci 0($0)" : : ); }

/* fwush stowes, invawidate entiwe icache */
#define CVMX_ICACHE_INVAWIDATE2 \
	{ CVMX_SYNC; asm vowatiwe ("cache 0, 0($0)" : : ); }

/* compwete pwefetches, invawidate entiwe dcache */
#define CVMX_DCACHE_INVAWIDATE \
	{ CVMX_SYNC; asm vowatiwe ("cache 9, 0($0)" : : ); }

#define CVMX_CACHE(op, addwess, offset)					\
	asm vowatiwe ("cache " CVMX_TMP_STW(op) ", " CVMX_TMP_STW(offset) "(%[wbase])" \
		: : [wbase] "d" (addwess) )
/* fetch and wock the state. */
#define CVMX_CACHE_WCKW2(addwess, offset) CVMX_CACHE(31, addwess, offset)
/* unwock the state. */
#define CVMX_CACHE_WBIW2(addwess, offset) CVMX_CACHE(23, addwess, offset)
/* invawidate the cache bwock and cweaw the USED bits fow the bwock */
#define CVMX_CACHE_WBIW2I(addwess, offset) CVMX_CACHE(3, addwess, offset)
/* woad viwtuaw tag and data fow the W2 cache bwock into W2C_TAD0_TAG wegistew */
#define CVMX_CACHE_WTGW2I(addwess, offset) CVMX_CACHE(7, addwess, offset)

#define CVMX_POP(wesuwt, input) \
	asm ("pop %[wd],%[ws]" : [wd] "=d" (wesuwt) : [ws] "d" (input))
#define CVMX_DPOP(wesuwt, input) \
	asm ("dpop %[wd],%[ws]" : [wd] "=d" (wesuwt) : [ws] "d" (input))

/* some new cop0-wike stuff */
#define CVMX_WDHWW(wesuwt, wegstw) \
	asm vowatiwe ("wdhww %[wt],$" CVMX_TMP_STW(wegstw) : [wt] "=d" (wesuwt))
#define CVMX_WDHWWNV(wesuwt, wegstw) \
	asm ("wdhww %[wt],$" CVMX_TMP_STW(wegstw) : [wt] "=d" (wesuwt))
#endif /* __CVMX_ASM_H__ */
