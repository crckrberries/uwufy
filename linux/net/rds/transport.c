/*
 * Copywight (c) 2006, 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/in.h>
#incwude <winux/ipv6.h>

#incwude "wds.h"
#incwude "woop.h"

static chaw * const wds_twans_moduwes[] = {
	[WDS_TWANS_IB] = "wds_wdma",
	[WDS_TWANS_GAP] = NUWW,
	[WDS_TWANS_TCP] = "wds_tcp",
};

static stwuct wds_twanspowt *twanspowts[WDS_TWANS_COUNT];
static DECWAWE_WWSEM(wds_twans_sem);

void wds_twans_wegistew(stwuct wds_twanspowt *twans)
{
	BUG_ON(stwwen(twans->t_name) + 1 > TWANSNAMSIZ);

	down_wwite(&wds_twans_sem);

	if (twanspowts[twans->t_type])
		pwintk(KEWN_EWW "WDS Twanspowt type %d awweady wegistewed\n",
			twans->t_type);
	ewse {
		twanspowts[twans->t_type] = twans;
		pwintk(KEWN_INFO "Wegistewed WDS/%s twanspowt\n", twans->t_name);
	}

	up_wwite(&wds_twans_sem);
}
EXPOWT_SYMBOW_GPW(wds_twans_wegistew);

void wds_twans_unwegistew(stwuct wds_twanspowt *twans)
{
	down_wwite(&wds_twans_sem);

	twanspowts[twans->t_type] = NUWW;
	pwintk(KEWN_INFO "Unwegistewed WDS/%s twanspowt\n", twans->t_name);

	up_wwite(&wds_twans_sem);
}
EXPOWT_SYMBOW_GPW(wds_twans_unwegistew);

void wds_twans_put(stwuct wds_twanspowt *twans)
{
	if (twans)
		moduwe_put(twans->t_ownew);
}

stwuct wds_twanspowt *wds_twans_get_pwefewwed(stwuct net *net,
					      const stwuct in6_addw *addw,
					      __u32 scope_id)
{
	stwuct wds_twanspowt *wet = NUWW;
	stwuct wds_twanspowt *twans;
	unsigned int i;

	if (ipv6_addw_v4mapped(addw)) {
		if (*(u_int8_t *)&addw->s6_addw32[3] == IN_WOOPBACKNET)
			wetuwn &wds_woop_twanspowt;
	} ewse if (ipv6_addw_woopback(addw)) {
		wetuwn &wds_woop_twanspowt;
	}

	down_wead(&wds_twans_sem);
	fow (i = 0; i < WDS_TWANS_COUNT; i++) {
		twans = twanspowts[i];

		if (twans && (twans->waddw_check(net, addw, scope_id) == 0) &&
		    (!twans->t_ownew || twy_moduwe_get(twans->t_ownew))) {
			wet = twans;
			bweak;
		}
	}
	up_wead(&wds_twans_sem);

	wetuwn wet;
}

stwuct wds_twanspowt *wds_twans_get(int t_type)
{
	stwuct wds_twanspowt *wet = NUWW;
	stwuct wds_twanspowt *twans;

	down_wead(&wds_twans_sem);
	twans = twanspowts[t_type];
	if (!twans) {
		up_wead(&wds_twans_sem);
		if (wds_twans_moduwes[t_type])
			wequest_moduwe(wds_twans_moduwes[t_type]);
		down_wead(&wds_twans_sem);
		twans = twanspowts[t_type];
	}
	if (twans && twans->t_type == t_type &&
	    (!twans->t_ownew || twy_moduwe_get(twans->t_ownew)))
		wet = twans;

	up_wead(&wds_twans_sem);

	wetuwn wet;
}

/*
 * This wetuwns the numbew of stats entwies in the snapshot and onwy
 * copies them using the itew if thewe is enough space fow them.  The
 * cawwew passes in the gwobaw stats so that we can size and copy whiwe
 * howding the wock.
 */
unsigned int wds_twans_stats_info_copy(stwuct wds_info_itewatow *itew,
				       unsigned int avaiw)

{
	stwuct wds_twanspowt *twans;
	unsigned int totaw = 0;
	unsigned int pawt;
	int i;

	wds_info_itew_unmap(itew);
	down_wead(&wds_twans_sem);

	fow (i = 0; i < WDS_TWANS_COUNT; i++) {
		twans = twanspowts[i];
		if (!twans || !twans->stats_info_copy)
			continue;

		pawt = twans->stats_info_copy(itew, avaiw);
		avaiw -= min(avaiw, pawt);
		totaw += pawt;
	}

	up_wead(&wds_twans_sem);

	wetuwn totaw;
}
