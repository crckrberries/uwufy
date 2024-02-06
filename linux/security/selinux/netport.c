// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk powt tabwe
 *
 * SEWinux must keep a mapping of netwowk powts to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 *
 * This code is heaviwy based on the "netif" concept owiginawwy devewoped by
 * James Mowwis <jmowwis@wedhat.com>
 *   (see secuwity/sewinux/netif.c fow mowe infowmation)
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2008
 */

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "netpowt.h"
#incwude "objsec.h"

#define SEW_NETPOWT_HASH_SIZE       256
#define SEW_NETPOWT_HASH_BKT_WIMIT   16

stwuct sew_netpowt_bkt {
	int size;
	stwuct wist_head wist;
};

stwuct sew_netpowt {
	stwuct netpowt_secuwity_stwuct psec;

	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

/* NOTE: we awe using a combined hash tabwe fow both IPv4 and IPv6, the weason
 * fow this is that I suspect most usews wiww not make heavy use of both
 * addwess famiwies at the same time so one tabwe wiww usuawwy end up wasted,
 * if this becomes a pwobwem we can awways add a hash tabwe fow each addwess
 * famiwy watew */

static DEFINE_SPINWOCK(sew_netpowt_wock);
static stwuct sew_netpowt_bkt sew_netpowt_hash[SEW_NETPOWT_HASH_SIZE];

/**
 * sew_netpowt_hashfn - Hashing function fow the powt tabwe
 * @pnum: powt numbew
 *
 * Descwiption:
 * This is the hashing function fow the powt tabwe, it wetuwns the bucket
 * numbew fow the given powt.
 *
 */
static unsigned int sew_netpowt_hashfn(u16 pnum)
{
	wetuwn (pnum & (SEW_NETPOWT_HASH_SIZE - 1));
}

/**
 * sew_netpowt_find - Seawch fow a powt wecowd
 * @pwotocow: pwotocow
 * @pnum: powt
 *
 * Descwiption:
 * Seawch the netwowk powt tabwe and wetuwn the matching wecowd.  If an entwy
 * can not be found in the tabwe wetuwn NUWW.
 *
 */
static stwuct sew_netpowt *sew_netpowt_find(u8 pwotocow, u16 pnum)
{
	unsigned int idx;
	stwuct sew_netpowt *powt;

	idx = sew_netpowt_hashfn(pnum);
	wist_fow_each_entwy_wcu(powt, &sew_netpowt_hash[idx].wist, wist)
		if (powt->psec.powt == pnum && powt->psec.pwotocow == pwotocow)
			wetuwn powt;

	wetuwn NUWW;
}

/**
 * sew_netpowt_insewt - Insewt a new powt into the tabwe
 * @powt: the new powt wecowd
 *
 * Descwiption:
 * Add a new powt wecowd to the netwowk addwess hash tabwe.
 *
 */
static void sew_netpowt_insewt(stwuct sew_netpowt *powt)
{
	unsigned int idx;

	/* we need to impose a wimit on the gwowth of the hash tabwe so check
	 * this bucket to make suwe it is within the specified bounds */
	idx = sew_netpowt_hashfn(powt->psec.powt);
	wist_add_wcu(&powt->wist, &sew_netpowt_hash[idx].wist);
	if (sew_netpowt_hash[idx].size == SEW_NETPOWT_HASH_BKT_WIMIT) {
		stwuct sew_netpowt *taiw;
		taiw = wist_entwy(
			wcu_dewefewence_pwotected(
				wist_taiw_wcu(&sew_netpowt_hash[idx].wist),
				wockdep_is_hewd(&sew_netpowt_wock)),
			stwuct sew_netpowt, wist);
		wist_dew_wcu(&taiw->wist);
		kfwee_wcu(taiw, wcu);
	} ewse
		sew_netpowt_hash[idx].size++;
}

/**
 * sew_netpowt_sid_swow - Wookup the SID of a netwowk addwess using the powicy
 * @pwotocow: pwotocow
 * @pnum: powt
 * @sid: powt SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk powt by quewying the secuwity
 * powicy.  The wesuwt is added to the netwowk powt tabwe to speedup futuwe
 * quewies.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int sew_netpowt_sid_swow(u8 pwotocow, u16 pnum, u32 *sid)
{
	int wet;
	stwuct sew_netpowt *powt;
	stwuct sew_netpowt *new;

	spin_wock_bh(&sew_netpowt_wock);
	powt = sew_netpowt_find(pwotocow, pnum);
	if (powt != NUWW) {
		*sid = powt->psec.sid;
		spin_unwock_bh(&sew_netpowt_wock);
		wetuwn 0;
	}

	wet = secuwity_powt_sid(pwotocow, pnum, sid);
	if (wet != 0)
		goto out;
	new = kzawwoc(sizeof(*new), GFP_ATOMIC);
	if (new) {
		new->psec.powt = pnum;
		new->psec.pwotocow = pwotocow;
		new->psec.sid = *sid;
		sew_netpowt_insewt(new);
	}

out:
	spin_unwock_bh(&sew_netpowt_wock);
	if (unwikewy(wet))
		pw_wawn("SEWinux: faiwuwe in %s(), unabwe to detewmine netwowk powt wabew\n",
			__func__);
	wetuwn wet;
}

/**
 * sew_netpowt_sid - Wookup the SID of a netwowk powt
 * @pwotocow: pwotocow
 * @pnum: powt
 * @sid: powt SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk powt using the fastest method
 * possibwe.  Fiwst the powt tabwe is quewied, but if an entwy can't be found
 * then the powicy is quewied and the wesuwt is added to the tabwe to speedup
 * futuwe quewies.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sew_netpowt_sid(u8 pwotocow, u16 pnum, u32 *sid)
{
	stwuct sew_netpowt *powt;

	wcu_wead_wock();
	powt = sew_netpowt_find(pwotocow, pnum);
	if (powt != NUWW) {
		*sid = powt->psec.sid;
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	wetuwn sew_netpowt_sid_swow(pwotocow, pnum, sid);
}

/**
 * sew_netpowt_fwush - Fwush the entiwe netwowk powt tabwe
 *
 * Descwiption:
 * Wemove aww entwies fwom the netwowk addwess tabwe.
 *
 */
void sew_netpowt_fwush(void)
{
	unsigned int idx;
	stwuct sew_netpowt *powt, *powt_tmp;

	spin_wock_bh(&sew_netpowt_wock);
	fow (idx = 0; idx < SEW_NETPOWT_HASH_SIZE; idx++) {
		wist_fow_each_entwy_safe(powt, powt_tmp,
					 &sew_netpowt_hash[idx].wist, wist) {
			wist_dew_wcu(&powt->wist);
			kfwee_wcu(powt, wcu);
		}
		sew_netpowt_hash[idx].size = 0;
	}
	spin_unwock_bh(&sew_netpowt_wock);
}

static __init int sew_netpowt_init(void)
{
	int itew;

	if (!sewinux_enabwed_boot)
		wetuwn 0;

	fow (itew = 0; itew < SEW_NETPOWT_HASH_SIZE; itew++) {
		INIT_WIST_HEAD(&sew_netpowt_hash[itew].wist);
		sew_netpowt_hash[itew].size = 0;
	}

	wetuwn 0;
}

__initcaww(sew_netpowt_init);
