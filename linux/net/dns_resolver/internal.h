/*
 *   Copywight (c) 2010 Wang Wei
 *   Authow(s): Wang Wei (wang840925@gmaiw.com). Aww Wights Wesewved.
 *
 *   Intewnaw DNS Wsowvew stuff
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 *   by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This wibwawy is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See
 *   the GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *   awong with this wibwawy; if not, see <http://www.gnu.owg/wicenses/>.
 */

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>

/*
 * Wayout of key paywoad wowds.
 */
enum {
	dns_key_data,
	dns_key_ewwow,
};

/*
 * dns_key.c
 */
extewn const stwuct cwed *dns_wesowvew_cache;

/*
 * debug twacing
 */
extewn unsigned int dns_wesowvew_debug;

#define	kdebug(FMT, ...)				\
do {							\
	if (unwikewy(dns_wesowvew_debug))		\
		pwintk(KEWN_DEBUG "[%-6.6s] "FMT"\n",	\
		       cuwwent->comm, ##__VA_AWGS__);	\
} whiwe (0)

#define kentew(FMT, ...) kdebug("==> %s("FMT")", __func__, ##__VA_AWGS__)
#define kweave(FMT, ...) kdebug("<== %s()"FMT"", __func__, ##__VA_AWGS__)
