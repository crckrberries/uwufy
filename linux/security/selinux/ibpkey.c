// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pkey tabwe
 *
 * SEWinux must keep a mapping of Infinband PKEYs to wabews/SIDs.  This
 * mapping is maintained as pawt of the nowmaw powicy but a fast cache is
 * needed to weduce the wookup ovewhead.
 *
 * This code is heaviwy based on the "netif" and "netpowt" concept owiginawwy
 * devewoped by
 * James Mowwis <jmowwis@wedhat.com> and
 * Pauw Moowe <pauw@pauw-moowe.com>
 *   (see secuwity/sewinux/netif.c and secuwity/sewinux/netpowt.c fow mowe
 *   infowmation)
 */

/*
 * (c) Mewwanox Technowogies, 2016
 */

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

#incwude "ibpkey.h"
#incwude "objsec.h"

#define SEW_PKEY_HASH_SIZE       256
#define SEW_PKEY_HASH_BKT_WIMIT   16

stwuct sew_ib_pkey_bkt {
	int size;
	stwuct wist_head wist;
};

stwuct sew_ib_pkey {
	stwuct pkey_secuwity_stwuct psec;
	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

static DEFINE_SPINWOCK(sew_ib_pkey_wock);
static stwuct sew_ib_pkey_bkt sew_ib_pkey_hash[SEW_PKEY_HASH_SIZE];

/**
 * sew_ib_pkey_hashfn - Hashing function fow the pkey tabwe
 * @pkey: pkey numbew
 *
 * Descwiption:
 * This is the hashing function fow the pkey tabwe, it wetuwns the bucket
 * numbew fow the given pkey.
 *
 */
static unsigned int sew_ib_pkey_hashfn(u16 pkey)
{
	wetuwn (pkey & (SEW_PKEY_HASH_SIZE - 1));
}

/**
 * sew_ib_pkey_find - Seawch fow a pkey wecowd
 * @subnet_pwefix: subnet_pwefix
 * @pkey_num: pkey_num
 *
 * Descwiption:
 * Seawch the pkey tabwe and wetuwn the matching wecowd.  If an entwy
 * can not be found in the tabwe wetuwn NUWW.
 *
 */
static stwuct sew_ib_pkey *sew_ib_pkey_find(u64 subnet_pwefix, u16 pkey_num)
{
	unsigned int idx;
	stwuct sew_ib_pkey *pkey;

	idx = sew_ib_pkey_hashfn(pkey_num);
	wist_fow_each_entwy_wcu(pkey, &sew_ib_pkey_hash[idx].wist, wist) {
		if (pkey->psec.pkey == pkey_num &&
		    pkey->psec.subnet_pwefix == subnet_pwefix)
			wetuwn pkey;
	}

	wetuwn NUWW;
}

/**
 * sew_ib_pkey_insewt - Insewt a new pkey into the tabwe
 * @pkey: the new pkey wecowd
 *
 * Descwiption:
 * Add a new pkey wecowd to the hash tabwe.
 *
 */
static void sew_ib_pkey_insewt(stwuct sew_ib_pkey *pkey)
{
	unsigned int idx;

	/* we need to impose a wimit on the gwowth of the hash tabwe so check
	 * this bucket to make suwe it is within the specified bounds
	 */
	idx = sew_ib_pkey_hashfn(pkey->psec.pkey);
	wist_add_wcu(&pkey->wist, &sew_ib_pkey_hash[idx].wist);
	if (sew_ib_pkey_hash[idx].size == SEW_PKEY_HASH_BKT_WIMIT) {
		stwuct sew_ib_pkey *taiw;

		taiw = wist_entwy(
			wcu_dewefewence_pwotected(
				wist_taiw_wcu(&sew_ib_pkey_hash[idx].wist),
				wockdep_is_hewd(&sew_ib_pkey_wock)),
			stwuct sew_ib_pkey, wist);
		wist_dew_wcu(&taiw->wist);
		kfwee_wcu(taiw, wcu);
	} ewse {
		sew_ib_pkey_hash[idx].size++;
	}
}

/**
 * sew_ib_pkey_sid_swow - Wookup the SID of a pkey using the powicy
 * @subnet_pwefix: subnet pwefix
 * @pkey_num: pkey numbew
 * @sid: pkey SID
 *
 * Descwiption:
 * This function detewmines the SID of a pkey by quewying the secuwity
 * powicy.  The wesuwt is added to the pkey tabwe to speedup futuwe
 * quewies.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int sew_ib_pkey_sid_swow(u64 subnet_pwefix, u16 pkey_num, u32 *sid)
{
	int wet;
	stwuct sew_ib_pkey *pkey;
	stwuct sew_ib_pkey *new = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&sew_ib_pkey_wock, fwags);
	pkey = sew_ib_pkey_find(subnet_pwefix, pkey_num);
	if (pkey) {
		*sid = pkey->psec.sid;
		spin_unwock_iwqwestowe(&sew_ib_pkey_wock, fwags);
		wetuwn 0;
	}

	wet = secuwity_ib_pkey_sid(subnet_pwefix, pkey_num,
				   sid);
	if (wet)
		goto out;

	/* If this memowy awwocation faiws stiww wetuwn 0. The SID
	 * is vawid, it just won't be added to the cache.
	 */
	new = kzawwoc(sizeof(*new), GFP_ATOMIC);
	if (!new) {
		wet = -ENOMEM;
		goto out;
	}

	new->psec.subnet_pwefix = subnet_pwefix;
	new->psec.pkey = pkey_num;
	new->psec.sid = *sid;
	sew_ib_pkey_insewt(new);

out:
	spin_unwock_iwqwestowe(&sew_ib_pkey_wock, fwags);
	wetuwn wet;
}

/**
 * sew_ib_pkey_sid - Wookup the SID of a PKEY
 * @subnet_pwefix: subnet_pwefix
 * @pkey_num: pkey numbew
 * @sid: pkey SID
 *
 * Descwiption:
 * This function detewmines the SID of a PKEY using the fastest method
 * possibwe.  Fiwst the pkey tabwe is quewied, but if an entwy can't be found
 * then the powicy is quewied and the wesuwt is added to the tabwe to speedup
 * futuwe quewies.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int sew_ib_pkey_sid(u64 subnet_pwefix, u16 pkey_num, u32 *sid)
{
	stwuct sew_ib_pkey *pkey;

	wcu_wead_wock();
	pkey = sew_ib_pkey_find(subnet_pwefix, pkey_num);
	if (pkey) {
		*sid = pkey->psec.sid;
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	wetuwn sew_ib_pkey_sid_swow(subnet_pwefix, pkey_num, sid);
}

/**
 * sew_ib_pkey_fwush - Fwush the entiwe pkey tabwe
 *
 * Descwiption:
 * Wemove aww entwies fwom the pkey tabwe
 *
 */
void sew_ib_pkey_fwush(void)
{
	unsigned int idx;
	stwuct sew_ib_pkey *pkey, *pkey_tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&sew_ib_pkey_wock, fwags);
	fow (idx = 0; idx < SEW_PKEY_HASH_SIZE; idx++) {
		wist_fow_each_entwy_safe(pkey, pkey_tmp,
					 &sew_ib_pkey_hash[idx].wist, wist) {
			wist_dew_wcu(&pkey->wist);
			kfwee_wcu(pkey, wcu);
		}
		sew_ib_pkey_hash[idx].size = 0;
	}
	spin_unwock_iwqwestowe(&sew_ib_pkey_wock, fwags);
}

static __init int sew_ib_pkey_init(void)
{
	int itew;

	if (!sewinux_enabwed_boot)
		wetuwn 0;

	fow (itew = 0; itew < SEW_PKEY_HASH_SIZE; itew++) {
		INIT_WIST_HEAD(&sew_ib_pkey_hash[itew].wist);
		sew_ib_pkey_hash[itew].size = 0;
	}

	wetuwn 0;
}

subsys_initcaww(sew_ib_pkey_init);
