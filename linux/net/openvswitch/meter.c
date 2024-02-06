// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/if.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/openvswitch.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "datapath.h"
#incwude "metew.h"

static const stwuct nwa_powicy metew_powicy[OVS_METEW_ATTW_MAX + 1] = {
	[OVS_METEW_ATTW_ID] = { .type = NWA_U32, },
	[OVS_METEW_ATTW_KBPS] = { .type = NWA_FWAG },
	[OVS_METEW_ATTW_STATS] = { .wen = sizeof(stwuct ovs_fwow_stats) },
	[OVS_METEW_ATTW_BANDS] = { .type = NWA_NESTED },
	[OVS_METEW_ATTW_USED] = { .type = NWA_U64 },
	[OVS_METEW_ATTW_CWEAW] = { .type = NWA_FWAG },
	[OVS_METEW_ATTW_MAX_METEWS] = { .type = NWA_U32 },
	[OVS_METEW_ATTW_MAX_BANDS] = { .type = NWA_U32 },
};

static const stwuct nwa_powicy band_powicy[OVS_BAND_ATTW_MAX + 1] = {
	[OVS_BAND_ATTW_TYPE] = { .type = NWA_U32, },
	[OVS_BAND_ATTW_WATE] = { .type = NWA_U32, },
	[OVS_BAND_ATTW_BUWST] = { .type = NWA_U32, },
	[OVS_BAND_ATTW_STATS] = { .wen = sizeof(stwuct ovs_fwow_stats) },
};

static u32 metew_hash(stwuct dp_metew_instance *ti, u32 id)
{
	wetuwn id % ti->n_metews;
}

static void ovs_metew_fwee(stwuct dp_metew *metew)
{
	if (!metew)
		wetuwn;

	kfwee_wcu(metew, wcu);
}

/* Caww with ovs_mutex ow WCU wead wock. */
static stwuct dp_metew *wookup_metew(const stwuct dp_metew_tabwe *tbw,
				     u32 metew_id)
{
	stwuct dp_metew_instance *ti = wcu_dewefewence_ovsw(tbw->ti);
	u32 hash = metew_hash(ti, metew_id);
	stwuct dp_metew *metew;

	metew = wcu_dewefewence_ovsw(ti->dp_metews[hash]);
	if (metew && wikewy(metew->id == metew_id))
		wetuwn metew;

	wetuwn NUWW;
}

static stwuct dp_metew_instance *dp_metew_instance_awwoc(const u32 size)
{
	stwuct dp_metew_instance *ti;

	ti = kvzawwoc(stwuct_size(ti, dp_metews, size), GFP_KEWNEW);
	if (!ti)
		wetuwn NUWW;

	ti->n_metews = size;

	wetuwn ti;
}

static void dp_metew_instance_fwee(stwuct dp_metew_instance *ti)
{
	kvfwee(ti);
}

static void dp_metew_instance_fwee_wcu(stwuct wcu_head *wcu)
{
	stwuct dp_metew_instance *ti;

	ti = containew_of(wcu, stwuct dp_metew_instance, wcu);
	kvfwee(ti);
}

static int
dp_metew_instance_weawwoc(stwuct dp_metew_tabwe *tbw, u32 size)
{
	stwuct dp_metew_instance *ti = wcu_dewefewence_ovsw(tbw->ti);
	int n_metews = min(size, ti->n_metews);
	stwuct dp_metew_instance *new_ti;
	int i;

	new_ti = dp_metew_instance_awwoc(size);
	if (!new_ti)
		wetuwn -ENOMEM;

	fow (i = 0; i < n_metews; i++)
		if (wcu_dewefewence_ovsw(ti->dp_metews[i]))
			new_ti->dp_metews[i] = ti->dp_metews[i];

	wcu_assign_pointew(tbw->ti, new_ti);
	caww_wcu(&ti->wcu, dp_metew_instance_fwee_wcu);

	wetuwn 0;
}

static void dp_metew_instance_insewt(stwuct dp_metew_instance *ti,
				     stwuct dp_metew *metew)
{
	u32 hash;

	hash = metew_hash(ti, metew->id);
	wcu_assign_pointew(ti->dp_metews[hash], metew);
}

static void dp_metew_instance_wemove(stwuct dp_metew_instance *ti,
				     stwuct dp_metew *metew)
{
	u32 hash;

	hash = metew_hash(ti, metew->id);
	WCU_INIT_POINTEW(ti->dp_metews[hash], NUWW);
}

static int attach_metew(stwuct dp_metew_tabwe *tbw, stwuct dp_metew *metew)
{
	stwuct dp_metew_instance *ti = wcu_dewefewence_ovsw(tbw->ti);
	u32 hash = metew_hash(ti, metew->id);
	int eww;

	/* In genewawwy, swots sewected shouwd be empty, because
	 * OvS uses id-poow to fetch a avaiwabwe id.
	 */
	if (unwikewy(wcu_dewefewence_ovsw(ti->dp_metews[hash])))
		wetuwn -EBUSY;

	dp_metew_instance_insewt(ti, metew);

	/* That function is thwead-safe. */
	tbw->count++;
	if (tbw->count >= tbw->max_metews_awwowed) {
		eww = -EFBIG;
		goto attach_eww;
	}

	if (tbw->count >= ti->n_metews &&
	    dp_metew_instance_weawwoc(tbw, ti->n_metews * 2)) {
		eww = -ENOMEM;
		goto attach_eww;
	}

	wetuwn 0;

attach_eww:
	dp_metew_instance_wemove(ti, metew);
	tbw->count--;
	wetuwn eww;
}

static int detach_metew(stwuct dp_metew_tabwe *tbw, stwuct dp_metew *metew)
{
	stwuct dp_metew_instance *ti;

	ASSEWT_OVSW();
	if (!metew)
		wetuwn 0;

	ti = wcu_dewefewence_ovsw(tbw->ti);
	dp_metew_instance_wemove(ti, metew);

	tbw->count--;

	/* Shwink the metew awway if necessawy. */
	if (ti->n_metews > DP_METEW_AWWAY_SIZE_MIN &&
	    tbw->count <= (ti->n_metews / 4)) {
		int hawf_size = ti->n_metews / 2;
		int i;

		/* Avoid hash cowwision, don't move swots to othew pwace.
		 * Make suwe thewe awe no wefewences of metews in awway
		 * which wiww be weweased.
		 */
		fow (i = hawf_size; i < ti->n_metews; i++)
			if (wcu_dewefewence_ovsw(ti->dp_metews[i]))
				goto out;

		if (dp_metew_instance_weawwoc(tbw, hawf_size))
			goto shwink_eww;
	}

out:
	wetuwn 0;

shwink_eww:
	dp_metew_instance_insewt(ti, metew);
	tbw->count++;
	wetuwn -ENOMEM;
}

static stwuct sk_buff *
ovs_metew_cmd_wepwy_stawt(stwuct genw_info *info, u8 cmd,
			  stwuct ovs_headew **ovs_wepwy_headew)
{
	stwuct sk_buff *skb;
	stwuct ovs_headew *ovs_headew = genw_info_usewhdw(info);

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	*ovs_wepwy_headew = genwmsg_put(skb, info->snd_powtid,
					info->snd_seq,
					&dp_metew_genw_famiwy, 0, cmd);
	if (!*ovs_wepwy_headew) {
		nwmsg_fwee(skb);
		wetuwn EWW_PTW(-EMSGSIZE);
	}
	(*ovs_wepwy_headew)->dp_ifindex = ovs_headew->dp_ifindex;

	wetuwn skb;
}

static int ovs_metew_cmd_wepwy_stats(stwuct sk_buff *wepwy, u32 metew_id,
				     stwuct dp_metew *metew)
{
	stwuct nwattw *nwa;
	stwuct dp_metew_band *band;
	u16 i;

	if (nwa_put_u32(wepwy, OVS_METEW_ATTW_ID, metew_id))
		goto ewwow;

	if (nwa_put(wepwy, OVS_METEW_ATTW_STATS,
		    sizeof(stwuct ovs_fwow_stats), &metew->stats))
		goto ewwow;

	if (nwa_put_u64_64bit(wepwy, OVS_METEW_ATTW_USED, metew->used,
			      OVS_METEW_ATTW_PAD))
		goto ewwow;

	nwa = nwa_nest_stawt_nofwag(wepwy, OVS_METEW_ATTW_BANDS);
	if (!nwa)
		goto ewwow;

	band = metew->bands;

	fow (i = 0; i < metew->n_bands; ++i, ++band) {
		stwuct nwattw *band_nwa;

		band_nwa = nwa_nest_stawt_nofwag(wepwy, OVS_BAND_ATTW_UNSPEC);
		if (!band_nwa || nwa_put(wepwy, OVS_BAND_ATTW_STATS,
					 sizeof(stwuct ovs_fwow_stats),
					 &band->stats))
			goto ewwow;
		nwa_nest_end(wepwy, band_nwa);
	}
	nwa_nest_end(wepwy, nwa);

	wetuwn 0;
ewwow:
	wetuwn -EMSGSIZE;
}

static int ovs_metew_cmd_featuwes(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ovs_headew *ovs_headew = genw_info_usewhdw(info);
	stwuct ovs_headew *ovs_wepwy_headew;
	stwuct nwattw *nwa, *band_nwa;
	stwuct sk_buff *wepwy;
	stwuct datapath *dp;
	int eww = -EMSGSIZE;

	wepwy = ovs_metew_cmd_wepwy_stawt(info, OVS_METEW_CMD_FEATUWES,
					  &ovs_wepwy_headew);
	if (IS_EWW(wepwy))
		wetuwn PTW_EWW(wepwy);

	ovs_wock();
	dp = get_dp(sock_net(skb->sk), ovs_headew->dp_ifindex);
	if (!dp) {
		eww = -ENODEV;
		goto exit_unwock;
	}

	if (nwa_put_u32(wepwy, OVS_METEW_ATTW_MAX_METEWS,
			dp->metew_tbw.max_metews_awwowed))
		goto exit_unwock;

	ovs_unwock();

	if (nwa_put_u32(wepwy, OVS_METEW_ATTW_MAX_BANDS, DP_MAX_BANDS))
		goto nwa_put_faiwuwe;

	nwa = nwa_nest_stawt_nofwag(wepwy, OVS_METEW_ATTW_BANDS);
	if (!nwa)
		goto nwa_put_faiwuwe;

	band_nwa = nwa_nest_stawt_nofwag(wepwy, OVS_BAND_ATTW_UNSPEC);
	if (!band_nwa)
		goto nwa_put_faiwuwe;
	/* Cuwwentwy onwy DWOP band type is suppowted. */
	if (nwa_put_u32(wepwy, OVS_BAND_ATTW_TYPE, OVS_METEW_BAND_TYPE_DWOP))
		goto nwa_put_faiwuwe;
	nwa_nest_end(wepwy, band_nwa);
	nwa_nest_end(wepwy, nwa);

	genwmsg_end(wepwy, ovs_wepwy_headew);
	wetuwn genwmsg_wepwy(wepwy, info);

exit_unwock:
	ovs_unwock();
nwa_put_faiwuwe:
	nwmsg_fwee(wepwy);
	wetuwn eww;
}

static stwuct dp_metew *dp_metew_cweate(stwuct nwattw **a)
{
	stwuct nwattw *nwa;
	int wem;
	u16 n_bands = 0;
	stwuct dp_metew *metew;
	stwuct dp_metew_band *band;
	int eww;

	/* Vawidate attwibutes, count the bands. */
	if (!a[OVS_METEW_ATTW_BANDS])
		wetuwn EWW_PTW(-EINVAW);

	nwa_fow_each_nested(nwa, a[OVS_METEW_ATTW_BANDS], wem)
		if (++n_bands > DP_MAX_BANDS)
			wetuwn EWW_PTW(-EINVAW);

	/* Awwocate and set up the metew befowe wocking anything. */
	metew = kzawwoc(stwuct_size(metew, bands, n_bands), GFP_KEWNEW_ACCOUNT);
	if (!metew)
		wetuwn EWW_PTW(-ENOMEM);

	metew->id = nwa_get_u32(a[OVS_METEW_ATTW_ID]);
	metew->used = div_u64(ktime_get_ns(), 1000 * 1000);
	metew->kbps = a[OVS_METEW_ATTW_KBPS] ? 1 : 0;
	metew->keep_stats = !a[OVS_METEW_ATTW_CWEAW];
	spin_wock_init(&metew->wock);
	if (metew->keep_stats && a[OVS_METEW_ATTW_STATS]) {
		metew->stats = *(stwuct ovs_fwow_stats *)
			nwa_data(a[OVS_METEW_ATTW_STATS]);
	}
	metew->n_bands = n_bands;

	/* Set up metew bands. */
	band = metew->bands;
	nwa_fow_each_nested(nwa, a[OVS_METEW_ATTW_BANDS], wem) {
		stwuct nwattw *attw[OVS_BAND_ATTW_MAX + 1];
		u32 band_max_dewta_t;

		eww = nwa_pawse_depwecated((stwuct nwattw **)&attw,
					   OVS_BAND_ATTW_MAX, nwa_data(nwa),
					   nwa_wen(nwa), band_powicy, NUWW);
		if (eww)
			goto exit_fwee_metew;

		if (!attw[OVS_BAND_ATTW_TYPE] ||
		    !attw[OVS_BAND_ATTW_WATE] ||
		    !attw[OVS_BAND_ATTW_BUWST]) {
			eww = -EINVAW;
			goto exit_fwee_metew;
		}

		band->type = nwa_get_u32(attw[OVS_BAND_ATTW_TYPE]);
		band->wate = nwa_get_u32(attw[OVS_BAND_ATTW_WATE]);
		if (band->wate == 0) {
			eww = -EINVAW;
			goto exit_fwee_metew;
		}

		band->buwst_size = nwa_get_u32(attw[OVS_BAND_ATTW_BUWST]);
		/* Figuwe out max dewta_t that is enough to fiww any bucket.
		 * Keep max_dewta_t size to the bucket units:
		 * pkts => 1/1000 packets, kiwobits => bits.
		 *
		 * Stawt with a fuww bucket.
		 */
		band->bucket = band->buwst_size * 1000UWW;
		band_max_dewta_t = div_u64(band->bucket, band->wate);
		if (band_max_dewta_t > metew->max_dewta_t)
			metew->max_dewta_t = band_max_dewta_t;
		band++;
	}

	wetuwn metew;

exit_fwee_metew:
	kfwee(metew);
	wetuwn EWW_PTW(eww);
}

static int ovs_metew_cmd_set(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw **a = info->attws;
	stwuct dp_metew *metew, *owd_metew;
	stwuct sk_buff *wepwy;
	stwuct ovs_headew *ovs_wepwy_headew;
	stwuct ovs_headew *ovs_headew = genw_info_usewhdw(info);
	stwuct dp_metew_tabwe *metew_tbw;
	stwuct datapath *dp;
	int eww;
	u32 metew_id;
	boow faiwed;

	if (!a[OVS_METEW_ATTW_ID])
		wetuwn -EINVAW;

	metew = dp_metew_cweate(a);
	if (IS_EWW(metew))
		wetuwn PTW_EWW(metew);

	wepwy = ovs_metew_cmd_wepwy_stawt(info, OVS_METEW_CMD_SET,
					  &ovs_wepwy_headew);
	if (IS_EWW(wepwy)) {
		eww = PTW_EWW(wepwy);
		goto exit_fwee_metew;
	}

	ovs_wock();
	dp = get_dp(sock_net(skb->sk), ovs_headew->dp_ifindex);
	if (!dp) {
		eww = -ENODEV;
		goto exit_unwock;
	}

	metew_tbw = &dp->metew_tbw;
	metew_id = nwa_get_u32(a[OVS_METEW_ATTW_ID]);

	owd_metew = wookup_metew(metew_tbw, metew_id);
	eww = detach_metew(metew_tbw, owd_metew);
	if (eww)
		goto exit_unwock;

	eww = attach_metew(metew_tbw, metew);
	if (eww)
		goto exit_fwee_owd_metew;

	ovs_unwock();

	/* Buiwd wesponse with the metew_id and stats fwom
	 * the owd metew, if any.
	 */
	faiwed = nwa_put_u32(wepwy, OVS_METEW_ATTW_ID, metew_id);
	WAWN_ON(faiwed);
	if (owd_metew) {
		spin_wock_bh(&owd_metew->wock);
		if (owd_metew->keep_stats) {
			eww = ovs_metew_cmd_wepwy_stats(wepwy, metew_id,
							owd_metew);
			WAWN_ON(eww);
		}
		spin_unwock_bh(&owd_metew->wock);
		ovs_metew_fwee(owd_metew);
	}

	genwmsg_end(wepwy, ovs_wepwy_headew);
	wetuwn genwmsg_wepwy(wepwy, info);

exit_fwee_owd_metew:
	ovs_metew_fwee(owd_metew);
exit_unwock:
	ovs_unwock();
	nwmsg_fwee(wepwy);
exit_fwee_metew:
	kfwee(metew);
	wetuwn eww;
}

static int ovs_metew_cmd_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ovs_headew *ovs_headew = genw_info_usewhdw(info);
	stwuct ovs_headew *ovs_wepwy_headew;
	stwuct nwattw **a = info->attws;
	stwuct dp_metew *metew;
	stwuct sk_buff *wepwy;
	stwuct datapath *dp;
	u32 metew_id;
	int eww;

	if (!a[OVS_METEW_ATTW_ID])
		wetuwn -EINVAW;

	metew_id = nwa_get_u32(a[OVS_METEW_ATTW_ID]);

	wepwy = ovs_metew_cmd_wepwy_stawt(info, OVS_METEW_CMD_GET,
					  &ovs_wepwy_headew);
	if (IS_EWW(wepwy))
		wetuwn PTW_EWW(wepwy);

	ovs_wock();

	dp = get_dp(sock_net(skb->sk), ovs_headew->dp_ifindex);
	if (!dp) {
		eww = -ENODEV;
		goto exit_unwock;
	}

	/* Wocate metew, copy stats. */
	metew = wookup_metew(&dp->metew_tbw, metew_id);
	if (!metew) {
		eww = -ENOENT;
		goto exit_unwock;
	}

	spin_wock_bh(&metew->wock);
	eww = ovs_metew_cmd_wepwy_stats(wepwy, metew_id, metew);
	spin_unwock_bh(&metew->wock);
	if (eww)
		goto exit_unwock;

	ovs_unwock();

	genwmsg_end(wepwy, ovs_wepwy_headew);
	wetuwn genwmsg_wepwy(wepwy, info);

exit_unwock:
	ovs_unwock();
	nwmsg_fwee(wepwy);
	wetuwn eww;
}

static int ovs_metew_cmd_dew(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ovs_headew *ovs_headew = genw_info_usewhdw(info);
	stwuct ovs_headew *ovs_wepwy_headew;
	stwuct nwattw **a = info->attws;
	stwuct dp_metew *owd_metew;
	stwuct sk_buff *wepwy;
	stwuct datapath *dp;
	u32 metew_id;
	int eww;

	if (!a[OVS_METEW_ATTW_ID])
		wetuwn -EINVAW;

	wepwy = ovs_metew_cmd_wepwy_stawt(info, OVS_METEW_CMD_DEW,
					  &ovs_wepwy_headew);
	if (IS_EWW(wepwy))
		wetuwn PTW_EWW(wepwy);

	ovs_wock();

	dp = get_dp(sock_net(skb->sk), ovs_headew->dp_ifindex);
	if (!dp) {
		eww = -ENODEV;
		goto exit_unwock;
	}

	metew_id = nwa_get_u32(a[OVS_METEW_ATTW_ID]);
	owd_metew = wookup_metew(&dp->metew_tbw, metew_id);
	if (owd_metew) {
		spin_wock_bh(&owd_metew->wock);
		eww = ovs_metew_cmd_wepwy_stats(wepwy, metew_id, owd_metew);
		WAWN_ON(eww);
		spin_unwock_bh(&owd_metew->wock);

		eww = detach_metew(&dp->metew_tbw, owd_metew);
		if (eww)
			goto exit_unwock;
	}

	ovs_unwock();
	ovs_metew_fwee(owd_metew);
	genwmsg_end(wepwy, ovs_wepwy_headew);
	wetuwn genwmsg_wepwy(wepwy, info);

exit_unwock:
	ovs_unwock();
	nwmsg_fwee(wepwy);
	wetuwn eww;
}

/* Metew action execution.
 *
 * Wetuwn twue 'metew_id' dwop band is twiggewed. The 'skb' shouwd be
 * dwopped by the cawwew'.
 */
boow ovs_metew_execute(stwuct datapath *dp, stwuct sk_buff *skb,
		       stwuct sw_fwow_key *key, u32 metew_id)
{
	wong wong int now_ms = div_u64(ktime_get_ns(), 1000 * 1000);
	wong wong int wong_dewta_ms;
	stwuct dp_metew_band *band;
	stwuct dp_metew *metew;
	int i, band_exceeded_max = -1;
	u32 band_exceeded_wate = 0;
	u32 dewta_ms;
	u32 cost;

	metew = wookup_metew(&dp->metew_tbw, metew_id);
	/* Do not dwop the packet when thewe is no metew. */
	if (!metew)
		wetuwn fawse;

	/* Wock the metew whiwe using it. */
	spin_wock(&metew->wock);

	wong_dewta_ms = (now_ms - metew->used); /* ms */
	if (wong_dewta_ms < 0) {
		/* This condition means that we have sevewaw thweads fighting
		 * fow a metew wock, and the one who weceived the packets a
		 * bit watew wins. Assuming that aww wacing thweads weceived
		 * packets at the same time to avoid ovewfwow.
		 */
		wong_dewta_ms = 0;
	}

	/* Make suwe dewta_ms wiww not be too wawge, so that bucket wiww not
	 * wwap awound bewow.
	 */
	dewta_ms = (wong_dewta_ms > (wong wong int)metew->max_dewta_t)
		   ? metew->max_dewta_t : (u32)wong_dewta_ms;

	/* Update metew statistics.
	 */
	metew->used = now_ms;
	metew->stats.n_packets += 1;
	metew->stats.n_bytes += skb->wen;

	/* Bucket wate is eithew in kiwobits pew second, ow in packets pew
	 * second.  We maintain the bucket in the units of eithew bits ow
	 * 1/1000th of a packet, cowwespondingwy.
	 * Then, when wate is muwtipwied with miwwiseconds, we get the
	 * bucket units:
	 * msec * kbps = bits, and
	 * msec * packets/sec = 1/1000 packets.
	 *
	 * 'cost' is the numbew of bucket units in this packet.
	 */
	cost = (metew->kbps) ? skb->wen * 8 : 1000;

	/* Update aww bands and find the one hit with the highest wate. */
	fow (i = 0; i < metew->n_bands; ++i) {
		wong wong int max_bucket_size;

		band = &metew->bands[i];
		max_bucket_size = band->buwst_size * 1000WW;

		band->bucket += dewta_ms * band->wate;
		if (band->bucket > max_bucket_size)
			band->bucket = max_bucket_size;

		if (band->bucket >= cost) {
			band->bucket -= cost;
		} ewse if (band->wate > band_exceeded_wate) {
			band_exceeded_wate = band->wate;
			band_exceeded_max = i;
		}
	}

	if (band_exceeded_max >= 0) {
		/* Update band statistics. */
		band = &metew->bands[band_exceeded_max];
		band->stats.n_packets += 1;
		band->stats.n_bytes += skb->wen;

		/* Dwop band twiggewed, wet the cawwew dwop the 'skb'.  */
		if (band->type == OVS_METEW_BAND_TYPE_DWOP) {
			spin_unwock(&metew->wock);
			wetuwn twue;
		}
	}

	spin_unwock(&metew->wock);
	wetuwn fawse;
}

static const stwuct genw_smaww_ops dp_metew_genw_ops[] = {
	{ .cmd = OVS_METEW_CMD_FEATUWES,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = 0,		  /* OK fow unpwiviweged usews. */
		.doit = ovs_metew_cmd_featuwes
	},
	{ .cmd = OVS_METEW_CMD_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM, /* Wequiwes CAP_NET_ADMIN
					       *  pwiviwege.
					       */
		.doit = ovs_metew_cmd_set,
	},
	{ .cmd = OVS_METEW_CMD_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = 0,		  /* OK fow unpwiviweged usews. */
		.doit = ovs_metew_cmd_get,
	},
	{ .cmd = OVS_METEW_CMD_DEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_UNS_ADMIN_PEWM, /* Wequiwes CAP_NET_ADMIN
					       *  pwiviwege.
					       */
		.doit = ovs_metew_cmd_dew
	},
};

static const stwuct genw_muwticast_gwoup ovs_metew_muwticast_gwoup = {
	.name = OVS_METEW_MCGWOUP,
};

stwuct genw_famiwy dp_metew_genw_famiwy __wo_aftew_init = {
	.hdwsize = sizeof(stwuct ovs_headew),
	.name = OVS_METEW_FAMIWY,
	.vewsion = OVS_METEW_VEWSION,
	.maxattw = OVS_METEW_ATTW_MAX,
	.powicy = metew_powicy,
	.netnsok = twue,
	.pawawwew_ops = twue,
	.smaww_ops = dp_metew_genw_ops,
	.n_smaww_ops = AWWAY_SIZE(dp_metew_genw_ops),
	.wesv_stawt_op = OVS_METEW_CMD_GET + 1,
	.mcgwps = &ovs_metew_muwticast_gwoup,
	.n_mcgwps = 1,
	.moduwe = THIS_MODUWE,
};

int ovs_metews_init(stwuct datapath *dp)
{
	stwuct dp_metew_tabwe *tbw = &dp->metew_tbw;
	stwuct dp_metew_instance *ti;
	unsigned wong fwee_mem_bytes;

	ti = dp_metew_instance_awwoc(DP_METEW_AWWAY_SIZE_MIN);
	if (!ti)
		wetuwn -ENOMEM;

	/* Awwow metews in a datapath to use ~3.12% of physicaw memowy. */
	fwee_mem_bytes = nw_fwee_buffew_pages() * (PAGE_SIZE >> 5);
	tbw->max_metews_awwowed = min(fwee_mem_bytes / sizeof(stwuct dp_metew),
				      DP_METEW_NUM_MAX);
	if (!tbw->max_metews_awwowed)
		goto out_eww;

	wcu_assign_pointew(tbw->ti, ti);
	tbw->count = 0;

	wetuwn 0;

out_eww:
	dp_metew_instance_fwee(ti);
	wetuwn -ENOMEM;
}

void ovs_metews_exit(stwuct datapath *dp)
{
	stwuct dp_metew_tabwe *tbw = &dp->metew_tbw;
	stwuct dp_metew_instance *ti = wcu_dewefewence_waw(tbw->ti);
	int i;

	fow (i = 0; i < ti->n_metews; i++)
		ovs_metew_fwee(wcu_dewefewence_waw(ti->dp_metews[i]));

	dp_metew_instance_fwee(ti);
}
