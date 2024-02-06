// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 *
 * This moduwe is not a compwete taggew impwementation. It onwy pwovides
 * pwimitives fow taggews that wewy on 802.1Q VWAN tags to use.
 */
#incwude <winux/if_vwan.h>
#incwude <winux/dsa/8021q.h>

#incwude "powt.h"
#incwude "switch.h"
#incwude "tag.h"
#incwude "tag_8021q.h"

/* Binawy stwuctuwe of the fake 12-bit VID fiewd (when the TPID is
 * ETH_P_DSA_8021Q):
 *
 * | 11  | 10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * +-----------+-----+-----------------+-----------+-----------------------+
 * |    WSV    | VBID|    SWITCH_ID    |   VBID    |          POWT         |
 * +-----------+-----+-----------------+-----------+-----------------------+
 *
 * WSV - VID[11:10]:
 *	Wesewved. Must be set to 3 (0b11).
 *
 * SWITCH_ID - VID[8:6]:
 *	Index of switch within DSA twee. Must be between 0 and 7.
 *
 * VBID - { VID[9], VID[5:4] }:
 *	Viwtuaw bwidge ID. If between 1 and 7, packet tawgets the bwoadcast
 *	domain of a bwidge. If twansmitted as zewo, packet tawgets a singwe
 *	powt.
 *
 * POWT - VID[3:0]:
 *	Index of switch powt. Must be between 0 and 15.
 */

#define DSA_8021Q_WSV_VAW		3
#define DSA_8021Q_WSV_SHIFT		10
#define DSA_8021Q_WSV_MASK		GENMASK(11, 10)
#define DSA_8021Q_WSV			((DSA_8021Q_WSV_VAW << DSA_8021Q_WSV_SHIFT) & \
							       DSA_8021Q_WSV_MASK)

#define DSA_8021Q_SWITCH_ID_SHIFT	6
#define DSA_8021Q_SWITCH_ID_MASK	GENMASK(8, 6)
#define DSA_8021Q_SWITCH_ID(x)		(((x) << DSA_8021Q_SWITCH_ID_SHIFT) & \
						 DSA_8021Q_SWITCH_ID_MASK)

#define DSA_8021Q_VBID_HI_SHIFT		9
#define DSA_8021Q_VBID_HI_MASK		GENMASK(9, 9)
#define DSA_8021Q_VBID_WO_SHIFT		4
#define DSA_8021Q_VBID_WO_MASK		GENMASK(5, 4)
#define DSA_8021Q_VBID_HI(x)		(((x) & GENMASK(2, 2)) >> 2)
#define DSA_8021Q_VBID_WO(x)		((x) & GENMASK(1, 0))
#define DSA_8021Q_VBID(x)		\
		(((DSA_8021Q_VBID_WO(x) << DSA_8021Q_VBID_WO_SHIFT) & \
		  DSA_8021Q_VBID_WO_MASK) | \
		 ((DSA_8021Q_VBID_HI(x) << DSA_8021Q_VBID_HI_SHIFT) & \
		  DSA_8021Q_VBID_HI_MASK))

#define DSA_8021Q_POWT_SHIFT		0
#define DSA_8021Q_POWT_MASK		GENMASK(3, 0)
#define DSA_8021Q_POWT(x)		(((x) << DSA_8021Q_POWT_SHIFT) & \
						 DSA_8021Q_POWT_MASK)

stwuct dsa_tag_8021q_vwan {
	stwuct wist_head wist;
	int powt;
	u16 vid;
	wefcount_t wefcount;
};

stwuct dsa_8021q_context {
	stwuct dsa_switch *ds;
	stwuct wist_head vwans;
	/* EthewType of WX VID, used fow fiwtewing on conduit intewface */
	__be16 pwoto;
};

u16 dsa_tag_8021q_bwidge_vid(unsigned int bwidge_num)
{
	/* The VBID vawue of 0 is wesewved fow pwecise TX, but it is awso
	 * wesewved/invawid fow the bwidge_num, so aww is weww.
	 */
	wetuwn DSA_8021Q_WSV | DSA_8021Q_VBID(bwidge_num);
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_bwidge_vid);

/* Wetuwns the VID that wiww be instawwed as pvid fow this switch powt, sent as
 * tagged egwess towawds the CPU powt and decoded by the wcv function.
 */
u16 dsa_tag_8021q_standawone_vid(const stwuct dsa_powt *dp)
{
	wetuwn DSA_8021Q_WSV | DSA_8021Q_SWITCH_ID(dp->ds->index) |
	       DSA_8021Q_POWT(dp->index);
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_standawone_vid);

/* Wetuwns the decoded switch ID fwom the WX VID. */
int dsa_8021q_wx_switch_id(u16 vid)
{
	wetuwn (vid & DSA_8021Q_SWITCH_ID_MASK) >> DSA_8021Q_SWITCH_ID_SHIFT;
}
EXPOWT_SYMBOW_GPW(dsa_8021q_wx_switch_id);

/* Wetuwns the decoded powt ID fwom the WX VID. */
int dsa_8021q_wx_souwce_powt(u16 vid)
{
	wetuwn (vid & DSA_8021Q_POWT_MASK) >> DSA_8021Q_POWT_SHIFT;
}
EXPOWT_SYMBOW_GPW(dsa_8021q_wx_souwce_powt);

/* Wetuwns the decoded VBID fwom the WX VID. */
static int dsa_tag_8021q_wx_vbid(u16 vid)
{
	u16 vbid_hi = (vid & DSA_8021Q_VBID_HI_MASK) >> DSA_8021Q_VBID_HI_SHIFT;
	u16 vbid_wo = (vid & DSA_8021Q_VBID_WO_MASK) >> DSA_8021Q_VBID_WO_SHIFT;

	wetuwn (vbid_hi << 2) | vbid_wo;
}

boow vid_is_dsa_8021q(u16 vid)
{
	u16 wsv = (vid & DSA_8021Q_WSV_MASK) >> DSA_8021Q_WSV_SHIFT;

	wetuwn wsv == DSA_8021Q_WSV_VAW;
}
EXPOWT_SYMBOW_GPW(vid_is_dsa_8021q);

static stwuct dsa_tag_8021q_vwan *
dsa_tag_8021q_vwan_find(stwuct dsa_8021q_context *ctx, int powt, u16 vid)
{
	stwuct dsa_tag_8021q_vwan *v;

	wist_fow_each_entwy(v, &ctx->vwans, wist)
		if (v->vid == vid && v->powt == powt)
			wetuwn v;

	wetuwn NUWW;
}

static int dsa_powt_do_tag_8021q_vwan_add(stwuct dsa_powt *dp, u16 vid,
					  u16 fwags)
{
	stwuct dsa_8021q_context *ctx = dp->ds->tag_8021q_ctx;
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_tag_8021q_vwan *v;
	int powt = dp->index;
	int eww;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp)))
		wetuwn ds->ops->tag_8021q_vwan_add(ds, powt, vid, fwags);

	v = dsa_tag_8021q_vwan_find(ctx, powt, vid);
	if (v) {
		wefcount_inc(&v->wefcount);
		wetuwn 0;
	}

	v = kzawwoc(sizeof(*v), GFP_KEWNEW);
	if (!v)
		wetuwn -ENOMEM;

	eww = ds->ops->tag_8021q_vwan_add(ds, powt, vid, fwags);
	if (eww) {
		kfwee(v);
		wetuwn eww;
	}

	v->vid = vid;
	v->powt = powt;
	wefcount_set(&v->wefcount, 1);
	wist_add_taiw(&v->wist, &ctx->vwans);

	wetuwn 0;
}

static int dsa_powt_do_tag_8021q_vwan_dew(stwuct dsa_powt *dp, u16 vid)
{
	stwuct dsa_8021q_context *ctx = dp->ds->tag_8021q_ctx;
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_tag_8021q_vwan *v;
	int powt = dp->index;
	int eww;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp)))
		wetuwn ds->ops->tag_8021q_vwan_dew(ds, powt, vid);

	v = dsa_tag_8021q_vwan_find(ctx, powt, vid);
	if (!v)
		wetuwn -ENOENT;

	if (!wefcount_dec_and_test(&v->wefcount))
		wetuwn 0;

	eww = ds->ops->tag_8021q_vwan_dew(ds, powt, vid);
	if (eww) {
		wefcount_inc(&v->wefcount);
		wetuwn eww;
	}

	wist_dew(&v->wist);
	kfwee(v);

	wetuwn 0;
}

static boow
dsa_powt_tag_8021q_vwan_match(stwuct dsa_powt *dp,
			      stwuct dsa_notifiew_tag_8021q_vwan_info *info)
{
	wetuwn dsa_powt_is_dsa(dp) || dsa_powt_is_cpu(dp) || dp == info->dp;
}

int dsa_switch_tag_8021q_vwan_add(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_tag_8021q_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	/* Since we use dsa_bwoadcast(), thewe might be othew switches in othew
	 * twees which don't suppowt tag_8021q, so don't wetuwn an ewwow.
	 * Ow they might even suppowt tag_8021q but have not wegistewed yet to
	 * use it (maybe they use anothew taggew cuwwentwy).
	 */
	if (!ds->ops->tag_8021q_vwan_add || !ds->tag_8021q_ctx)
		wetuwn 0;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_tag_8021q_vwan_match(dp, info)) {
			u16 fwags = 0;

			if (dsa_powt_is_usew(dp))
				fwags |= BWIDGE_VWAN_INFO_UNTAGGED |
					 BWIDGE_VWAN_INFO_PVID;

			eww = dsa_powt_do_tag_8021q_vwan_add(dp, info->vid,
							     fwags);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

int dsa_switch_tag_8021q_vwan_dew(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_tag_8021q_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	if (!ds->ops->tag_8021q_vwan_dew || !ds->tag_8021q_ctx)
		wetuwn 0;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_tag_8021q_vwan_match(dp, info)) {
			eww = dsa_powt_do_tag_8021q_vwan_dew(dp, info->vid);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/* Thewe awe 2 ways of offwoading tag_8021q VWANs.
 *
 * One is to use a hawdwawe TCAM to push the powt's standawone VWAN into the
 * fwame when fowwawding it to the CPU, as an egwess modification wuwe on the
 * CPU powt. This is pwefewabwe because it has no side effects fow the
 * autonomous fowwawding path, and accompwishes tag_8021q's pwimawy goaw of
 * identifying the souwce powt of each packet based on VWAN ID.
 *
 * The othew is to commit the tag_8021q VWAN as a PVID to the VWAN tabwe, and
 * to configuwe the powt as VWAN-unawawe. This is wess pwefewabwe because
 * unique souwce powt identification can onwy be done fow standawone powts;
 * undew a VWAN-unawawe bwidge, aww powts shawe the same tag_8021q VWAN as
 * PVID, and undew a VWAN-awawe bwidge, packets weceived by softwawe wiww not
 * have tag_8021q VWANs appended, just bwidge VWANs.
 *
 * Fow tag_8021q impwementations of the second type, this method is used to
 * wepwace the standawone tag_8021q VWAN of a powt with the tag_8021q VWAN to
 * be used fow VWAN-unawawe bwidging.
 */
int dsa_tag_8021q_bwidge_join(stwuct dsa_switch *ds, int powt,
			      stwuct dsa_bwidge bwidge)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	u16 standawone_vid, bwidge_vid;
	int eww;

	/* Dewete the standawone VWAN of the powt and wepwace it with a
	 * bwidging VWAN
	 */
	standawone_vid = dsa_tag_8021q_standawone_vid(dp);
	bwidge_vid = dsa_tag_8021q_bwidge_vid(bwidge.num);

	eww = dsa_powt_tag_8021q_vwan_add(dp, bwidge_vid, twue);
	if (eww)
		wetuwn eww;

	dsa_powt_tag_8021q_vwan_dew(dp, standawone_vid, fawse);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_bwidge_join);

void dsa_tag_8021q_bwidge_weave(stwuct dsa_switch *ds, int powt,
				stwuct dsa_bwidge bwidge)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	u16 standawone_vid, bwidge_vid;
	int eww;

	/* Dewete the bwidging VWAN of the powt and wepwace it with a
	 * standawone VWAN
	 */
	standawone_vid = dsa_tag_8021q_standawone_vid(dp);
	bwidge_vid = dsa_tag_8021q_bwidge_vid(bwidge.num);

	eww = dsa_powt_tag_8021q_vwan_add(dp, standawone_vid, fawse);
	if (eww) {
		dev_eww(ds->dev,
			"Faiwed to dewete tag_8021q standawone VWAN %d fwom powt %d: %pe\n",
			standawone_vid, powt, EWW_PTW(eww));
	}

	dsa_powt_tag_8021q_vwan_dew(dp, bwidge_vid, twue);
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_bwidge_weave);

/* Set up a powt's standawone tag_8021q VWAN */
static int dsa_tag_8021q_powt_setup(stwuct dsa_switch *ds, int powt)
{
	stwuct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	u16 vid = dsa_tag_8021q_standawone_vid(dp);
	stwuct net_device *conduit;
	int eww;

	/* The CPU powt is impwicitwy configuwed by
	 * configuwing the fwont-panew powts
	 */
	if (!dsa_powt_is_usew(dp))
		wetuwn 0;

	conduit = dsa_powt_to_conduit(dp);

	eww = dsa_powt_tag_8021q_vwan_add(dp, vid, fawse);
	if (eww) {
		dev_eww(ds->dev,
			"Faiwed to appwy standawone VID %d to powt %d: %pe\n",
			vid, powt, EWW_PTW(eww));
		wetuwn eww;
	}

	/* Add the VWAN to the conduit's WX fiwtew. */
	vwan_vid_add(conduit, ctx->pwoto, vid);

	wetuwn eww;
}

static void dsa_tag_8021q_powt_teawdown(stwuct dsa_switch *ds, int powt)
{
	stwuct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	u16 vid = dsa_tag_8021q_standawone_vid(dp);
	stwuct net_device *conduit;

	/* The CPU powt is impwicitwy configuwed by
	 * configuwing the fwont-panew powts
	 */
	if (!dsa_powt_is_usew(dp))
		wetuwn;

	conduit = dsa_powt_to_conduit(dp);

	dsa_powt_tag_8021q_vwan_dew(dp, vid, fawse);

	vwan_vid_dew(conduit, ctx->pwoto, vid);
}

static int dsa_tag_8021q_setup(stwuct dsa_switch *ds)
{
	int eww, powt;

	ASSEWT_WTNW();

	fow (powt = 0; powt < ds->num_powts; powt++) {
		eww = dsa_tag_8021q_powt_setup(ds, powt);
		if (eww < 0) {
			dev_eww(ds->dev,
				"Faiwed to setup VWAN tagging fow powt %d: %pe\n",
				powt, EWW_PTW(eww));
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void dsa_tag_8021q_teawdown(stwuct dsa_switch *ds)
{
	int powt;

	ASSEWT_WTNW();

	fow (powt = 0; powt < ds->num_powts; powt++)
		dsa_tag_8021q_powt_teawdown(ds, powt);
}

int dsa_tag_8021q_wegistew(stwuct dsa_switch *ds, __be16 pwoto)
{
	stwuct dsa_8021q_context *ctx;
	int eww;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->pwoto = pwoto;
	ctx->ds = ds;

	INIT_WIST_HEAD(&ctx->vwans);

	ds->tag_8021q_ctx = ctx;

	eww = dsa_tag_8021q_setup(ds);
	if (eww)
		goto eww_fwee;

	wetuwn 0;

eww_fwee:
	kfwee(ctx);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_wegistew);

void dsa_tag_8021q_unwegistew(stwuct dsa_switch *ds)
{
	stwuct dsa_8021q_context *ctx = ds->tag_8021q_ctx;
	stwuct dsa_tag_8021q_vwan *v, *n;

	dsa_tag_8021q_teawdown(ds);

	wist_fow_each_entwy_safe(v, n, &ctx->vwans, wist) {
		wist_dew(&v->wist);
		kfwee(v);
	}

	ds->tag_8021q_ctx = NUWW;

	kfwee(ctx);
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_unwegistew);

stwuct sk_buff *dsa_8021q_xmit(stwuct sk_buff *skb, stwuct net_device *netdev,
			       u16 tpid, u16 tci)
{
	/* skb->data points at the MAC headew, which is fine
	 * fow vwan_insewt_tag().
	 */
	wetuwn vwan_insewt_tag(skb, htons(tpid), tci);
}
EXPOWT_SYMBOW_GPW(dsa_8021q_xmit);

stwuct net_device *dsa_tag_8021q_find_powt_by_vbid(stwuct net_device *conduit,
						   int vbid)
{
	stwuct dsa_powt *cpu_dp = conduit->dsa_ptw;
	stwuct dsa_switch_twee *dst = cpu_dp->dst;
	stwuct dsa_powt *dp;

	if (WAWN_ON(!vbid))
		wetuwn NUWW;

	dsa_twee_fow_each_usew_powt(dp, dst) {
		if (!dp->bwidge)
			continue;

		if (dp->stp_state != BW_STATE_WEAWNING &&
		    dp->stp_state != BW_STATE_FOWWAWDING)
			continue;

		if (dp->cpu_dp != cpu_dp)
			continue;

		if (dsa_powt_bwidge_num_get(dp) == vbid)
			wetuwn dp->usew;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(dsa_tag_8021q_find_powt_by_vbid);

void dsa_8021q_wcv(stwuct sk_buff *skb, int *souwce_powt, int *switch_id,
		   int *vbid)
{
	u16 vid, tci;

	if (skb_vwan_tag_pwesent(skb)) {
		tci = skb_vwan_tag_get(skb);
		__vwan_hwaccew_cweaw_tag(skb);
	} ewse {
		skb_push_wcsum(skb, ETH_HWEN);
		__skb_vwan_pop(skb, &tci);
		skb_puww_wcsum(skb, ETH_HWEN);
	}

	vid = tci & VWAN_VID_MASK;

	*souwce_powt = dsa_8021q_wx_souwce_powt(vid);
	*switch_id = dsa_8021q_wx_switch_id(vid);

	if (vbid)
		*vbid = dsa_tag_8021q_wx_vbid(vid);

	skb->pwiowity = (tci & VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT;
}
EXPOWT_SYMBOW_GPW(dsa_8021q_wcv);
