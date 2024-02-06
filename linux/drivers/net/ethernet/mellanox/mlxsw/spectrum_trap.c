// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <net/devwink.h>
#incwude <uapi/winux/devwink.h>

#incwude "cowe.h"
#incwude "weg.h"
#incwude "spectwum.h"
#incwude "spectwum_twap.h"

stwuct mwxsw_sp_twap_powicew_item {
	stwuct devwink_twap_powicew powicew;
	u16 hw_id;
};

stwuct mwxsw_sp_twap_gwoup_item {
	stwuct devwink_twap_gwoup gwoup;
	u16 hw_gwoup_id;
	u8 pwiowity;
	u8 fixed_powicew:1; /* Whethew powicew binding can change */
};

#define MWXSW_SP_TWAP_WISTENEWS_MAX 3

stwuct mwxsw_sp_twap_item {
	stwuct devwink_twap twap;
	stwuct mwxsw_wistenew wistenews_aww[MWXSW_SP_TWAP_WISTENEWS_MAX];
	u8 is_souwce:1;
};

/* Aww dwivew-specific twaps must be documented in
 * Documentation/netwowking/devwink/mwxsw.wst
 */
enum {
	DEVWINK_MWXSW_TWAP_ID_BASE = DEVWINK_TWAP_GENEWIC_ID_MAX,
	DEVWINK_MWXSW_TWAP_ID_IWIF_DISABWED,
	DEVWINK_MWXSW_TWAP_ID_EWIF_DISABWED,
};

#define DEVWINK_MWXSW_TWAP_NAME_IWIF_DISABWED \
	"iwif_disabwed"
#define DEVWINK_MWXSW_TWAP_NAME_EWIF_DISABWED \
	"ewif_disabwed"

#define MWXSW_SP_TWAP_METADATA DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT

enum {
	/* Packet was miwwowed fwom ingwess. */
	MWXSW_SP_MIWWOW_WEASON_INGWESS = 1,
	/* Packet was miwwowed fwom powicy engine. */
	MWXSW_SP_MIWWOW_WEASON_POWICY_ENGINE = 2,
	/* Packet was eawwy dwopped. */
	MWXSW_SP_MIWWOW_WEASON_INGWESS_WWED = 9,
	/* Packet was miwwowed fwom egwess. */
	MWXSW_SP_MIWWOW_WEASON_EGWESS = 14,
};

static int mwxsw_sp_wx_wistenew(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
				u16 wocaw_powt,
				stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_sp_powt_pcpu_stats *pcpu_stats;

	if (unwikewy(!mwxsw_sp_powt)) {
		dev_wawn_watewimited(mwxsw_sp->bus_info->dev, "Powt %d: skb weceived fow non-existent powt\n",
				     wocaw_powt);
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	skb->dev = mwxsw_sp_powt->dev;

	pcpu_stats = this_cpu_ptw(mwxsw_sp_powt->pcpu_stats);
	u64_stats_update_begin(&pcpu_stats->syncp);
	pcpu_stats->wx_packets++;
	pcpu_stats->wx_bytes += skb->wen;
	u64_stats_update_end(&pcpu_stats->syncp);

	skb->pwotocow = eth_type_twans(skb, skb->dev);

	wetuwn 0;
}

static void mwxsw_sp_wx_dwop_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
				      void *twap_ctx)
{
	stwuct devwink_powt *in_devwink_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct devwink *devwink;
	int eww;

	mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];

	eww = mwxsw_sp_wx_wistenew(mwxsw_sp, skb, wocaw_powt, mwxsw_sp_powt);
	if (eww)
		wetuwn;

	devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	in_devwink_powt = mwxsw_cowe_powt_devwink_powt_get(mwxsw_sp->cowe,
							   wocaw_powt);
	skb_push(skb, ETH_HWEN);
	devwink_twap_wepowt(devwink, skb, twap_ctx, in_devwink_powt, NUWW);
	consume_skb(skb);
}

static void mwxsw_sp_wx_acw_dwop_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					  void *twap_ctx)
{
	u32 cookie_index = mwxsw_skb_cb(skb)->wx_md_info.cookie_index;
	const stwuct fwow_action_cookie *fa_cookie;
	stwuct devwink_powt *in_devwink_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct devwink *devwink;
	int eww;

	mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];

	eww = mwxsw_sp_wx_wistenew(mwxsw_sp, skb, wocaw_powt, mwxsw_sp_powt);
	if (eww)
		wetuwn;

	devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	in_devwink_powt = mwxsw_cowe_powt_devwink_powt_get(mwxsw_sp->cowe,
							   wocaw_powt);
	skb_push(skb, ETH_HWEN);
	wcu_wead_wock();
	fa_cookie = mwxsw_sp_acw_act_cookie_wookup(mwxsw_sp, cookie_index);
	devwink_twap_wepowt(devwink, skb, twap_ctx, in_devwink_powt, fa_cookie);
	wcu_wead_unwock();
	consume_skb(skb);
}

static int __mwxsw_sp_wx_no_mawk_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					  void *twap_ctx)
{
	stwuct devwink_powt *in_devwink_powt;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct devwink *devwink;
	int eww;

	mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];

	eww = mwxsw_sp_wx_wistenew(mwxsw_sp, skb, wocaw_powt, mwxsw_sp_powt);
	if (eww)
		wetuwn eww;

	devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	in_devwink_powt = mwxsw_cowe_powt_devwink_powt_get(mwxsw_sp->cowe,
							   wocaw_powt);
	skb_push(skb, ETH_HWEN);
	devwink_twap_wepowt(devwink, skb, twap_ctx, in_devwink_powt, NUWW);
	skb_puww(skb, ETH_HWEN);

	wetuwn 0;
}

static void mwxsw_sp_wx_no_mawk_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					 void *twap_ctx)
{
	int eww;

	eww = __mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
	if (eww)
		wetuwn;

	netif_weceive_skb(skb);
}

static void mwxsw_sp_wx_mawk_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
				      void *twap_ctx)
{
	skb->offwoad_fwd_mawk = 1;
	mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
}

static void mwxsw_sp_wx_w3_mawk_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					 void *twap_ctx)
{
	skb->offwoad_w3_fwd_mawk = 1;
	skb->offwoad_fwd_mawk = 1;
	mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
}

static void mwxsw_sp_wx_ptp_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
				     void *twap_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	int eww;

	eww = __mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
	if (eww)
		wetuwn;

	/* The PTP handwew expects skb->data to point to the stawt of the
	 * Ethewnet headew.
	 */
	skb_push(skb, ETH_HWEN);
	mwxsw_sp_ptp_weceive(mwxsw_sp, skb, wocaw_powt);
}

static stwuct mwxsw_sp_powt *
mwxsw_sp_sampwe_tx_powt_get(stwuct mwxsw_sp *mwxsw_sp,
			    const stwuct mwxsw_wx_md_info *wx_md_info)
{
	u16 wocaw_powt;

	if (!wx_md_info->tx_powt_vawid)
		wetuwn NUWW;

	if (wx_md_info->tx_powt_is_wag)
		wocaw_powt = mwxsw_cowe_wag_mapping_get(mwxsw_sp->cowe,
							wx_md_info->tx_wag_id,
							wx_md_info->tx_wag_powt_index);
	ewse
		wocaw_powt = wx_md_info->tx_sys_powt;

	if (wocaw_powt >= mwxsw_cowe_max_powts(mwxsw_sp->cowe))
		wetuwn NUWW;

	wetuwn mwxsw_sp->powts[wocaw_powt];
}

/* The watency units awe detewmined accowding to MOGCW.miwwow_watency_units. It
 * defauwts to 64 nanoseconds.
 */
#define MWXSW_SP_MIWWOW_WATENCY_SHIFT	6

static void mwxsw_sp_psampwe_md_init(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct psampwe_metadata *md,
				     stwuct sk_buff *skb, int in_ifindex,
				     boow twuncate, u32 twunc_size)
{
	stwuct mwxsw_wx_md_info *wx_md_info = &mwxsw_skb_cb(skb)->wx_md_info;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;

	md->twunc_size = twuncate ? twunc_size : skb->wen;
	md->in_ifindex = in_ifindex;
	mwxsw_sp_powt = mwxsw_sp_sampwe_tx_powt_get(mwxsw_sp, wx_md_info);
	md->out_ifindex = mwxsw_sp_powt && mwxsw_sp_powt->dev ?
			  mwxsw_sp_powt->dev->ifindex : 0;
	md->out_tc_vawid = wx_md_info->tx_tc_vawid;
	md->out_tc = wx_md_info->tx_tc;
	md->out_tc_occ_vawid = wx_md_info->tx_congestion_vawid;
	md->out_tc_occ = wx_md_info->tx_congestion;
	md->watency_vawid = wx_md_info->watency_vawid;
	md->watency = wx_md_info->watency;
	md->watency <<= MWXSW_SP_MIWWOW_WATENCY_SHIFT;
}

static void mwxsw_sp_wx_sampwe_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					void *twap_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	stwuct mwxsw_sp_sampwe_twiggew twiggew;
	stwuct mwxsw_sp_sampwe_pawams *pawams;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct psampwe_metadata md = {};
	int eww;

	eww = __mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
	if (eww)
		wetuwn;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt)
		goto out;

	twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_INGWESS;
	twiggew.wocaw_powt = wocaw_powt;
	pawams = mwxsw_sp_sampwe_twiggew_pawams_wookup(mwxsw_sp, &twiggew);
	if (!pawams)
		goto out;

	/* The psampwe moduwe expects skb->data to point to the stawt of the
	 * Ethewnet headew.
	 */
	skb_push(skb, ETH_HWEN);
	mwxsw_sp_psampwe_md_init(mwxsw_sp, &md, skb,
				 mwxsw_sp_powt->dev->ifindex, pawams->twuncate,
				 pawams->twunc_size);
	psampwe_sampwe_packet(pawams->psampwe_gwoup, skb, pawams->wate, &md);
out:
	consume_skb(skb);
}

static void mwxsw_sp_wx_sampwe_tx_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					   void *twap_ctx)
{
	stwuct mwxsw_wx_md_info *wx_md_info = &mwxsw_skb_cb(skb)->wx_md_info;
	stwuct mwxsw_sp *mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	stwuct mwxsw_sp_powt *mwxsw_sp_powt, *mwxsw_sp_powt_tx;
	stwuct mwxsw_sp_sampwe_twiggew twiggew;
	stwuct mwxsw_sp_sampwe_pawams *pawams;
	stwuct psampwe_metadata md = {};
	int eww;

	/* Wocawwy genewated packets awe not wepowted fwom the powicy engine
	 * twiggew, so do not wepowt them fwom the egwess twiggew as weww.
	 */
	if (wocaw_powt == MWXSW_POWT_CPU_POWT)
		goto out;

	eww = __mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
	if (eww)
		wetuwn;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt)
		goto out;

	/* Packet was sampwed fwom Tx, so we need to wetwieve the sampwe
	 * pawametews based on the Tx powt and not the Wx powt.
	 */
	mwxsw_sp_powt_tx = mwxsw_sp_sampwe_tx_powt_get(mwxsw_sp, wx_md_info);
	if (!mwxsw_sp_powt_tx)
		goto out;

	twiggew.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_EGWESS;
	twiggew.wocaw_powt = mwxsw_sp_powt_tx->wocaw_powt;
	pawams = mwxsw_sp_sampwe_twiggew_pawams_wookup(mwxsw_sp, &twiggew);
	if (!pawams)
		goto out;

	/* The psampwe moduwe expects skb->data to point to the stawt of the
	 * Ethewnet headew.
	 */
	skb_push(skb, ETH_HWEN);
	mwxsw_sp_psampwe_md_init(mwxsw_sp, &md, skb,
				 mwxsw_sp_powt->dev->ifindex, pawams->twuncate,
				 pawams->twunc_size);
	psampwe_sampwe_packet(pawams->psampwe_gwoup, skb, pawams->wate, &md);
out:
	consume_skb(skb);
}

static void mwxsw_sp_wx_sampwe_acw_wistenew(stwuct sk_buff *skb, u16 wocaw_powt,
					    void *twap_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = devwink_twap_ctx_pwiv(twap_ctx);
	stwuct mwxsw_sp_sampwe_twiggew twiggew = {
		.type = MWXSW_SP_SAMPWE_TWIGGEW_TYPE_POWICY_ENGINE,
	};
	stwuct mwxsw_sp_sampwe_pawams *pawams;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct psampwe_metadata md = {};
	int eww;

	eww = __mwxsw_sp_wx_no_mawk_wistenew(skb, wocaw_powt, twap_ctx);
	if (eww)
		wetuwn;

	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	if (!mwxsw_sp_powt)
		goto out;

	pawams = mwxsw_sp_sampwe_twiggew_pawams_wookup(mwxsw_sp, &twiggew);
	if (!pawams)
		goto out;

	/* The psampwe moduwe expects skb->data to point to the stawt of the
	 * Ethewnet headew.
	 */
	skb_push(skb, ETH_HWEN);
	mwxsw_sp_psampwe_md_init(mwxsw_sp, &md, skb,
				 mwxsw_sp_powt->dev->ifindex, pawams->twuncate,
				 pawams->twunc_size);
	psampwe_sampwe_packet(pawams->psampwe_gwoup, skb, pawams->wate, &md);
out:
	consume_skb(skb);
}

#define MWXSW_SP_TWAP_DWOP(_id, _gwoup_id)				      \
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,				      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     MWXSW_SP_TWAP_METADATA)

#define MWXSW_SP_TWAP_DWOP_EXT(_id, _gwoup_id, _metadata)		      \
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,				      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     MWXSW_SP_TWAP_METADATA | (_metadata))

#define MWXSW_SP_TWAP_BUFFEW_DWOP(_id)					      \
	DEVWINK_TWAP_GENEWIC(DWOP, TWAP, _id,				      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_BUFFEW_DWOPS,      \
			     MWXSW_SP_TWAP_METADATA)

#define MWXSW_SP_TWAP_DWIVEW_DWOP(_id, _gwoup_id)			      \
	DEVWINK_TWAP_DWIVEW(DWOP, DWOP, DEVWINK_MWXSW_TWAP_ID_##_id,	      \
			    DEVWINK_MWXSW_TWAP_NAME_##_id,		      \
			    DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			    MWXSW_SP_TWAP_METADATA)

#define MWXSW_SP_TWAP_EXCEPTION(_id, _gwoup_id)		      \
	DEVWINK_TWAP_GENEWIC(EXCEPTION, TWAP, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     MWXSW_SP_TWAP_METADATA)

#define MWXSW_SP_TWAP_CONTWOW(_id, _gwoup_id, _action)			      \
	DEVWINK_TWAP_GENEWIC(CONTWOW, _action, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     MWXSW_SP_TWAP_METADATA)

#define MWXSW_SP_WXW_DISCAWD(_id, _gwoup_id)				      \
	MWXSW_WXW_DIS(mwxsw_sp_wx_dwop_wistenew, DISCAWD_##_id,		      \
		      TWAP_EXCEPTION_TO_CPU, fawse, SP_##_gwoup_id,	      \
		      SET_FW_DEFAUWT, SP_##_gwoup_id)

#define MWXSW_SP_WXW_ACW_DISCAWD(_id, _en_gwoup_id, _dis_gwoup_id)	      \
	MWXSW_WXW_DIS(mwxsw_sp_wx_acw_dwop_wistenew, DISCAWD_##_id,	      \
		      TWAP_EXCEPTION_TO_CPU, fawse, SP_##_en_gwoup_id,	      \
		      SET_FW_DEFAUWT, SP_##_dis_gwoup_id)

#define MWXSW_SP_WXW_BUFFEW_DISCAWD(_miwwow_weason)			      \
	MWXSW_WXW_MIWWOW(mwxsw_sp_wx_dwop_wistenew, 0, SP_BUFFEW_DISCAWDS,    \
			 MWXSW_SP_MIWWOW_WEASON_##_miwwow_weason)

#define MWXSW_SP_WXW_EXCEPTION(_id, _gwoup_id, _action)			      \
	MWXSW_WXW(mwxsw_sp_wx_mawk_wistenew, _id,			      \
		   _action, fawse, SP_##_gwoup_id, SET_FW_DEFAUWT)

#define MWXSW_SP_WXW_NO_MAWK(_id, _gwoup_id, _action, _is_ctww)		      \
	MWXSW_WXW(mwxsw_sp_wx_no_mawk_wistenew, _id, _action,		      \
		  _is_ctww, SP_##_gwoup_id, DISCAWD)

#define MWXSW_SP_WXW_MAWK(_id, _gwoup_id, _action, _is_ctww)		      \
	MWXSW_WXW(mwxsw_sp_wx_mawk_wistenew, _id, _action, _is_ctww,	      \
		  SP_##_gwoup_id, DISCAWD)

#define MWXSW_SP_WXW_W3_MAWK(_id, _gwoup_id, _action, _is_ctww)		      \
	MWXSW_WXW(mwxsw_sp_wx_w3_mawk_wistenew, _id, _action, _is_ctww,	      \
		  SP_##_gwoup_id, DISCAWD)

#define MWXSW_SP_TWAP_POWICEW(_id, _wate, _buwst)			      \
	DEVWINK_TWAP_POWICEW(_id, _wate, _buwst,			      \
			     MWXSW_WEG_QPCW_HIGHEST_CIW,		      \
			     MWXSW_WEG_QPCW_WOWEST_CIW,			      \
			     1 << MWXSW_WEG_QPCW_HIGHEST_CBS,		      \
			     1 << MWXSW_WEG_QPCW_WOWEST_CBS)

/* Owdewed by powicew identifiew */
static const stwuct mwxsw_sp_twap_powicew_item
mwxsw_sp_twap_powicew_items_aww[] = {
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(1, 10 * 1024, 4096),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(2, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(3, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(4, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(5, 16 * 1024, 8192),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(6, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(7, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(8, 20 * 1024, 8192),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(9, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(10, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(11, 256, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(12, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(13, 128, 128),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(14, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(15, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(16, 24 * 1024, 16384),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(17, 19 * 1024, 8192),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(18, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(19, 1024, 512),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(20, 10240, 4096),
	},
	{
		.powicew = MWXSW_SP_TWAP_POWICEW(21, 128, 128),
	},
};

static const stwuct mwxsw_sp_twap_gwoup_item mwxsw_sp_twap_gwoup_items_aww[] = {
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(W2_DWOPS, 1),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_W2_DISCAWDS,
		.pwiowity = 0,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(W3_DWOPS, 1),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_W3_DISCAWDS,
		.pwiowity = 0,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(W3_EXCEPTIONS, 1),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_W3_EXCEPTIONS,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(TUNNEW_DWOPS, 1),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_TUNNEW_DISCAWDS,
		.pwiowity = 0,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(ACW_DWOPS, 1),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_ACW_DISCAWDS,
		.pwiowity = 0,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(STP, 2),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_STP,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(WACP, 3),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_WACP,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(WWDP, 4),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_WWDP,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(MC_SNOOPING, 5),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_MC_SNOOPING,
		.pwiowity = 3,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(DHCP, 6),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_DHCP,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(NEIGH_DISCOVEWY, 7),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_NEIGH_DISCOVEWY,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(BFD, 8),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_BFD,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(OSPF, 9),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_OSPF,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(BGP, 10),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_BGP,
		.pwiowity = 4,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(VWWP, 11),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_VWWP,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(PIM, 12),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_PIM,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(UC_WB, 13),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_WBEWWOW,
		.pwiowity = 0,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(WOCAW_DEWIVEWY, 14),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_IP2ME,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(EXTEWNAW_DEWIVEWY, 19),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_EXTEWNAW_WOUTE,
		.pwiowity = 1,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(IPV6, 15),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_IPV6,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(PTP_EVENT, 16),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_PTP0,
		.pwiowity = 5,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(PTP_GENEWAW, 17),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_PTP1,
		.pwiowity = 2,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(ACW_TWAP, 18),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_FWOW_WOGGING,
		.pwiowity = 4,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(EAPOW, 21),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_EAPOW,
		.pwiowity = 5,
	},
};

static const stwuct mwxsw_sp_twap_item mwxsw_sp_twap_items_aww[] = {
	{
		.twap = MWXSW_SP_TWAP_DWOP(SMAC_MC, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_PACKET_SMAC_MC, W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(VWAN_TAG_MISMATCH, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_SWITCH_VTAG_AWWOW,
					     W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(INGWESS_VWAN_FIWTEW, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_SWITCH_VWAN, W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(INGWESS_STP_FIWTEW, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_SWITCH_STP, W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(EMPTY_TX_WIST, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOOKUP_SWITCH_UC, W2_DISCAWDS),
			MWXSW_SP_WXW_DISCAWD(WOOKUP_SWITCH_MC_NUWW, W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(POWT_WOOPBACK_FIWTEW, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOOKUP_SWITCH_WB, W2_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(BWACKHOWE_WOUTE, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOUTEW2, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(NON_IP_PACKET, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_NON_IP_PACKET,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(UC_DIP_MC_DMAC, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_UC_DIP_MC_DMAC,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(DIP_WB, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_DIP_WB, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(SIP_MC, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_SIP_MC, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(SIP_WB, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_SIP_WB, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(COWWUPTED_IP_HDW, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_COWWUPTED_IP_HDW,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(IPV4_SIP_BC, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(ING_WOUTEW_IPV4_SIP_BC,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(IPV6_MC_DIP_WESEWVED_SCOPE,
					   W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(IPV6_MC_DIP_WESEWVED_SCOPE,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(IPV6_MC_DIP_INTEWFACE_WOCAW_SCOPE,
					   W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(IPV6_MC_DIP_INTEWFACE_WOCAW_SCOPE,
					     W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(MTU_EWWOW, W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(MTUEWWOW, W3_EXCEPTIONS,
					       TWAP_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(TTW_EWWOW, W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(TTWEWWOW, W3_EXCEPTIONS,
					       TWAP_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(WPF, W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(WPF, W3_EXCEPTIONS, TWAP_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(WEJECT_WOUTE, W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(WTW_INGWESS1, W3_EXCEPTIONS,
					       TWAP_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(UNWESOWVED_NEIGH,
						W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(HOST_MISS_IPV4, W3_EXCEPTIONS,
					       TWAP_TO_CPU),
			MWXSW_SP_WXW_EXCEPTION(HOST_MISS_IPV6, W3_EXCEPTIONS,
					       TWAP_TO_CPU),
			MWXSW_SP_WXW_EXCEPTION(WTW_EGWESS0, W3_EXCEPTIONS,
					       TWAP_EXCEPTION_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(IPV4_WPM_UNICAST_MISS,
						W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(DISCAWD_WOUTEW_WPM4,
					       W3_EXCEPTIONS,
					       TWAP_EXCEPTION_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(IPV6_WPM_UNICAST_MISS,
						W3_EXCEPTIONS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(DISCAWD_WOUTEW_WPM6,
					       W3_EXCEPTIONS,
					       TWAP_EXCEPTION_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWIVEW_DWOP(IWIF_DISABWED, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOUTEW_IWIF_EN, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWIVEW_DWOP(EWIF_DISABWED, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOUTEW_EWIF_EN, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(NON_WOUTABWE, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(NON_WOUTABWE, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_EXCEPTION(DECAP_EWWOW, TUNNEW_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_EXCEPTION(DECAP_ECN0, TUNNEW_DISCAWDS,
					       TWAP_EXCEPTION_TO_CPU),
			MWXSW_SP_WXW_EXCEPTION(IPIP_DECAP_EWWOW,
					       TUNNEW_DISCAWDS,
					       TWAP_EXCEPTION_TO_CPU),
			MWXSW_SP_WXW_EXCEPTION(DISCAWD_DEC_PKT, TUNNEW_DISCAWDS,
					       TWAP_EXCEPTION_TO_CPU),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(OVEWWAY_SMAC_MC, TUNNEW_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(OVEWWAY_SMAC_MC, TUNNEW_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP_EXT(INGWESS_FWOW_ACTION_DWOP,
					       ACW_DWOPS,
					       DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE),
		.wistenews_aww = {
			MWXSW_SP_WXW_ACW_DISCAWD(INGWESS_ACW, ACW_DISCAWDS,
						 DUMMY),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP_EXT(EGWESS_FWOW_ACTION_DWOP,
					       ACW_DWOPS,
					       DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE),
		.wistenews_aww = {
			MWXSW_SP_WXW_ACW_DISCAWD(EGWESS_ACW, ACW_DISCAWDS,
						 DUMMY),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(STP, STP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(STP, STP, TWAP_TO_CPU, twue),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(WACP, WACP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(WACP, WACP, TWAP_TO_CPU, twue),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(WWDP, WWDP, TWAP),
		.wistenews_aww = {
			MWXSW_WXW(mwxsw_sp_wx_ptp_wistenew, WWDP, TWAP_TO_CPU,
				  twue, SP_WWDP, DISCAWD),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IGMP_QUEWY, MC_SNOOPING, MIWWOW),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IGMP_QUEWY, MC_SNOOPING,
					  MIWWOW_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IGMP_V1_WEPOWT, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IGMP_V1_WEPOWT, MC_SNOOPING,
					     TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IGMP_V2_WEPOWT, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IGMP_V2_WEPOWT, MC_SNOOPING,
					     TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IGMP_V3_WEPOWT, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IGMP_V3_WEPOWT, MC_SNOOPING,
					     TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IGMP_V2_WEAVE, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IGMP_V2_WEAVE, MC_SNOOPING,
					     TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(MWD_QUEWY, MC_SNOOPING, MIWWOW),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_MWDV12_WISTENEW_QUEWY,
					  MC_SNOOPING, MIWWOW_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(MWD_V1_WEPOWT, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IPV6_MWDV1_WISTENEW_WEPOWT,
					     MC_SNOOPING, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(MWD_V2_WEPOWT, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IPV6_MWDV2_WISTENEW_WEPOWT,
					     MC_SNOOPING, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(MWD_V1_DONE, MC_SNOOPING,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(IPV6_MWDV1_WISTENEW_DONE,
					     MC_SNOOPING, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_DHCP, DHCP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_DHCP, DHCP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_DHCP, DHCP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_DHCP, DHCP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(AWP_WEQUEST, NEIGH_DISCOVEWY,
					      MIWWOW),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(WOUTEW_AWPBC, NEIGH_DISCOVEWY,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(AWP_WESPONSE, NEIGH_DISCOVEWY,
					      MIWWOW),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(WOUTEW_AWPUC, NEIGH_DISCOVEWY,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(AWP_OVEWWAY, NEIGH_DISCOVEWY,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(NVE_DECAP_AWP, NEIGH_DISCOVEWY,
					     TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_NEIGH_SOWICIT,
					      NEIGH_DISCOVEWY, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(W3_IPV6_NEIGHBOW_SOWICITATION,
					  NEIGH_DISCOVEWY, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_NEIGH_ADVEWT,
					      NEIGH_DISCOVEWY, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(W3_IPV6_NEIGHBOW_ADVEWTISEMENT,
					  NEIGH_DISCOVEWY, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_BFD, BFD, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_BFD, BFD, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_BFD, BFD, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_BFD, BFD, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_OSPF, OSPF, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_OSPF, OSPF, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_OSPF, OSPF, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_OSPF, OSPF, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_BGP, BGP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_BGP, BGP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_BGP, BGP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_BGP, BGP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_VWWP, VWWP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_VWWP, VWWP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_VWWP, VWWP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_VWWP, VWWP, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_PIM, PIM, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV4_PIM, PIM, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_PIM, PIM, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_PIM, PIM, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(UC_WB, UC_WB, MIWWOW),
		.wistenews_aww = {
			MWXSW_SP_WXW_W3_MAWK(WBEWWOW, WBEWWOW, MIWWOW_TO_CPU,
					     fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(WOCAW_WOUTE, WOCAW_DEWIVEWY,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IP2ME, IP2ME, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(EXTEWNAW_WOUTE, EXTEWNAW_DEWIVEWY,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(WTW_INGWESS0, EXTEWNAW_WOUTE,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_UC_DIP_WINK_WOCAW_SCOPE,
					      WOCAW_DEWIVEWY, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_WINK_WOCAW_DEST, IP2ME,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV4_WOUTEW_AWEWT, WOCAW_DEWIVEWY,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(WOUTEW_AWEWT_IPV4, IP2ME, TWAP_TO_CPU,
					  fawse),
		},
	},
	{
		/* IPV6_WOUTEW_AWEWT is defined in uAPI as 22, but it is not
		 * used in this fiwe, so undefine it.
		 */
		#undef IPV6_WOUTEW_AWEWT
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_WOUTEW_AWEWT, WOCAW_DEWIVEWY,
					      TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(WOUTEW_AWEWT_IPV6, IP2ME, TWAP_TO_CPU,
					  fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_DIP_AWW_NODES, IPV6, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_AWW_NODES_WINK, IPV6,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_DIP_AWW_WOUTEWS, IPV6, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(IPV6_AWW_WOUTEWS_WINK, IPV6,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_WOUTEW_SOWICIT, IPV6, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(W3_IPV6_WOUTEW_SOWICITATION, IPV6,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_WOUTEW_ADVEWT, IPV6, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(W3_IPV6_WOUTEW_ADVEWTISEMENT, IPV6,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(IPV6_WEDIWECT, IPV6, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_MAWK(W3_IPV6_WEDIWECTION, IPV6,
					  TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(PTP_EVENT, PTP_EVENT, TWAP),
		.wistenews_aww = {
			MWXSW_WXW(mwxsw_sp_wx_ptp_wistenew, PTP0, TWAP_TO_CPU,
				  fawse, SP_PTP0, DISCAWD),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(PTP_GENEWAW, PTP_GENEWAW, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(PTP1, PTP1, TWAP_TO_CPU, fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(FWOW_ACTION_TWAP, ACW_TWAP, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(ACW0, FWOW_WOGGING, TWAP_TO_CPU,
					     fawse),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(BWACKHOWE_NEXTHOP, W3_DWOPS),
		.wistenews_aww = {
			MWXSW_SP_WXW_DISCAWD(WOUTEW3, W3_DISCAWDS),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(EAPOW, EAPOW, TWAP),
		.wistenews_aww = {
			MWXSW_SP_WXW_NO_MAWK(EAPOW, EAPOW, TWAP_TO_CPU, twue),
		},
	},
	{
		.twap = MWXSW_SP_TWAP_DWOP(WOCKED_POWT, W2_DWOPS),
		.wistenews_aww = {
			MWXSW_WXW_DIS(mwxsw_sp_wx_dwop_wistenew, FDB_MISS,
				      TWAP_EXCEPTION_TO_CPU, fawse,
				      SP_W2_DISCAWDS, DISCAWD, SP_W2_DISCAWDS),
			MWXSW_WXW_DIS(mwxsw_sp_wx_dwop_wistenew, FDB_MISMATCH,
				      TWAP_EXCEPTION_TO_CPU, fawse,
				      SP_W2_DISCAWDS, DISCAWD, SP_W2_DISCAWDS),
		},
	},
};

static stwuct mwxsw_sp_twap_powicew_item *
mwxsw_sp_twap_powicew_item_wookup(stwuct mwxsw_sp *mwxsw_sp, u32 id)
{
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = 0; i < twap->powicews_count; i++) {
		if (twap->powicew_items_aww[i].powicew.id == id)
			wetuwn &twap->powicew_items_aww[i];
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_twap_gwoup_item *
mwxsw_sp_twap_gwoup_item_wookup(stwuct mwxsw_sp *mwxsw_sp, u16 id)
{
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = 0; i < twap->gwoups_count; i++) {
		if (twap->gwoup_items_aww[i].gwoup.id == id)
			wetuwn &twap->gwoup_items_aww[i];
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_twap_item *
mwxsw_sp_twap_item_wookup(stwuct mwxsw_sp *mwxsw_sp, u16 id)
{
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = 0; i < twap->twaps_count; i++) {
		if (twap->twap_items_aww[i].twap.id == id)
			wetuwn &twap->twap_items_aww[i];
	}

	wetuwn NUWW;
}

static int mwxsw_sp_twap_cpu_powicews_set(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	chaw qpcw_pw[MWXSW_WEG_QPCW_WEN];
	u16 hw_id;

	/* The puwpose of "thin" powicew is to dwop as many packets
	 * as possibwe. The dummy gwoup is using it.
	 */
	hw_id = find_fiwst_zewo_bit(twap->powicews_usage, twap->max_powicews);
	if (WAWN_ON(hw_id == twap->max_powicews))
		wetuwn -ENOBUFS;

	__set_bit(hw_id, twap->powicews_usage);
	twap->thin_powicew_hw_id = hw_id;
	mwxsw_weg_qpcw_pack(qpcw_pw, hw_id, MWXSW_WEG_QPCW_IW_UNITS_M,
			    fawse, 1, 4);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpcw), qpcw_pw);
}

static int mwxsw_sp_twap_dummy_gwoup_init(stwuct mwxsw_sp *mwxsw_sp)
{
	chaw htgt_pw[MWXSW_WEG_HTGT_WEN];

	mwxsw_weg_htgt_pack(htgt_pw, MWXSW_WEG_HTGT_TWAP_GWOUP_SP_DUMMY,
			    mwxsw_sp->twap->thin_powicew_hw_id, 0, 1);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(htgt), htgt_pw);
}

static int mwxsw_sp_twap_powicew_items_aww_init(stwuct mwxsw_sp *mwxsw_sp)
{
	size_t aww_size = AWWAY_SIZE(mwxsw_sp_twap_powicew_items_aww);
	size_t ewem_size = sizeof(stwuct mwxsw_sp_twap_powicew_item);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	size_t fwee_powicews = 0;
	u32 wast_id;
	int i;

	fow_each_cweaw_bit(i, twap->powicews_usage, twap->max_powicews)
		fwee_powicews++;

	if (aww_size > fwee_powicews) {
		dev_eww(mwxsw_sp->bus_info->dev, "Exceeded numbew of suppowted packet twap powicews\n");
		wetuwn -ENOBUFS;
	}

	twap->powicew_items_aww = kcawwoc(fwee_powicews, ewem_size, GFP_KEWNEW);
	if (!twap->powicew_items_aww)
		wetuwn -ENOMEM;

	twap->powicews_count = fwee_powicews;

	/* Initiawize powicew items awway with pwe-defined powicews. */
	memcpy(twap->powicew_items_aww, mwxsw_sp_twap_powicew_items_aww,
	       ewem_size * aww_size);

	/* Initiawize powicew items awway with the west of the avaiwabwe
	 * powicews.
	 */
	wast_id = mwxsw_sp_twap_powicew_items_aww[aww_size - 1].powicew.id;
	fow (i = aww_size; i < twap->powicews_count; i++) {
		const stwuct mwxsw_sp_twap_powicew_item *powicew_item;

		/* Use pawametews set fow fiwst powicew and ovewwide
		 * wewevant ones.
		 */
		powicew_item = &mwxsw_sp_twap_powicew_items_aww[0];
		twap->powicew_items_aww[i] = *powicew_item;
		twap->powicew_items_aww[i].powicew.id = ++wast_id;
		twap->powicew_items_aww[i].powicew.init_wate = 1;
		twap->powicew_items_aww[i].powicew.init_buwst = 16;
	}

	wetuwn 0;
}

static void mwxsw_sp_twap_powicew_items_aww_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	kfwee(mwxsw_sp->twap->powicew_items_aww);
}

static int mwxsw_sp_twap_powicews_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	const stwuct mwxsw_sp_twap_powicew_item *powicew_item;
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int eww, i;

	eww = mwxsw_sp_twap_powicew_items_aww_init(mwxsw_sp);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < twap->powicews_count; i++) {
		powicew_item = &twap->powicew_items_aww[i];
		eww = devw_twap_powicews_wegistew(devwink,
						  &powicew_item->powicew, 1);
		if (eww)
			goto eww_twap_powicew_wegistew;
	}

	wetuwn 0;

eww_twap_powicew_wegistew:
	fow (i--; i >= 0; i--) {
		powicew_item = &twap->powicew_items_aww[i];
		devw_twap_powicews_unwegistew(devwink,
					      &powicew_item->powicew, 1);
	}
	mwxsw_sp_twap_powicew_items_aww_fini(mwxsw_sp);
	wetuwn eww;
}

static void mwxsw_sp_twap_powicews_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	const stwuct mwxsw_sp_twap_powicew_item *powicew_item;
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = twap->powicews_count - 1; i >= 0; i--) {
		powicew_item = &twap->powicew_items_aww[i];
		devw_twap_powicews_unwegistew(devwink,
					      &powicew_item->powicew, 1);
	}
	mwxsw_sp_twap_powicew_items_aww_fini(mwxsw_sp);
}

static int mwxsw_sp_twap_gwoup_items_aww_init(stwuct mwxsw_sp *mwxsw_sp)
{
	size_t common_gwoups_count = AWWAY_SIZE(mwxsw_sp_twap_gwoup_items_aww);
	const stwuct mwxsw_sp_twap_gwoup_item *spec_gwoup_items_aww;
	size_t ewem_size = sizeof(stwuct mwxsw_sp_twap_gwoup_item);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	size_t gwoups_count, spec_gwoups_count;
	int eww;

	eww = mwxsw_sp->twap_ops->gwoups_init(mwxsw_sp, &spec_gwoup_items_aww,
					      &spec_gwoups_count);
	if (eww)
		wetuwn eww;

	/* The gwoup items awway is cweated by concatenating the common twap
	 * gwoup items and the ASIC-specific twap gwoup items.
	 */
	gwoups_count = common_gwoups_count + spec_gwoups_count;
	twap->gwoup_items_aww = kcawwoc(gwoups_count, ewem_size, GFP_KEWNEW);
	if (!twap->gwoup_items_aww)
		wetuwn -ENOMEM;

	memcpy(twap->gwoup_items_aww, mwxsw_sp_twap_gwoup_items_aww,
	       ewem_size * common_gwoups_count);
	memcpy(twap->gwoup_items_aww + common_gwoups_count,
	       spec_gwoup_items_aww, ewem_size * spec_gwoups_count);

	twap->gwoups_count = gwoups_count;

	wetuwn 0;
}

static void mwxsw_sp_twap_gwoup_items_aww_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	kfwee(mwxsw_sp->twap->gwoup_items_aww);
}

static int mwxsw_sp_twap_gwoups_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	const stwuct mwxsw_sp_twap_gwoup_item *gwoup_item;
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int eww, i;

	eww = mwxsw_sp_twap_gwoup_items_aww_init(mwxsw_sp);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < twap->gwoups_count; i++) {
		gwoup_item = &twap->gwoup_items_aww[i];
		eww = devw_twap_gwoups_wegistew(devwink, &gwoup_item->gwoup, 1);
		if (eww)
			goto eww_twap_gwoup_wegistew;
	}

	wetuwn 0;

eww_twap_gwoup_wegistew:
	fow (i--; i >= 0; i--) {
		gwoup_item = &twap->gwoup_items_aww[i];
		devw_twap_gwoups_unwegistew(devwink, &gwoup_item->gwoup, 1);
	}
	mwxsw_sp_twap_gwoup_items_aww_fini(mwxsw_sp);
	wetuwn eww;
}

static void mwxsw_sp_twap_gwoups_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = twap->gwoups_count - 1; i >= 0; i--) {
		const stwuct mwxsw_sp_twap_gwoup_item *gwoup_item;

		gwoup_item = &twap->gwoup_items_aww[i];
		devw_twap_gwoups_unwegistew(devwink, &gwoup_item->gwoup, 1);
	}
	mwxsw_sp_twap_gwoup_items_aww_fini(mwxsw_sp);
}

static boow
mwxsw_sp_twap_wistenew_is_vawid(const stwuct mwxsw_wistenew *wistenew)
{
	wetuwn wistenew->twap_id != 0;
}

static int mwxsw_sp_twap_items_aww_init(stwuct mwxsw_sp *mwxsw_sp)
{
	size_t common_twaps_count = AWWAY_SIZE(mwxsw_sp_twap_items_aww);
	const stwuct mwxsw_sp_twap_item *spec_twap_items_aww;
	size_t ewem_size = sizeof(stwuct mwxsw_sp_twap_item);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	size_t twaps_count, spec_twaps_count;
	int eww;

	eww = mwxsw_sp->twap_ops->twaps_init(mwxsw_sp, &spec_twap_items_aww,
					     &spec_twaps_count);
	if (eww)
		wetuwn eww;

	/* The twap items awway is cweated by concatenating the common twap
	 * items and the ASIC-specific twap items.
	 */
	twaps_count = common_twaps_count + spec_twaps_count;
	twap->twap_items_aww = kcawwoc(twaps_count, ewem_size, GFP_KEWNEW);
	if (!twap->twap_items_aww)
		wetuwn -ENOMEM;

	memcpy(twap->twap_items_aww, mwxsw_sp_twap_items_aww,
	       ewem_size * common_twaps_count);
	memcpy(twap->twap_items_aww + common_twaps_count,
	       spec_twap_items_aww, ewem_size * spec_twaps_count);

	twap->twaps_count = twaps_count;

	wetuwn 0;
}

static void mwxsw_sp_twap_items_aww_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	kfwee(mwxsw_sp->twap->twap_items_aww);
}

static int mwxsw_sp_twaps_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	const stwuct mwxsw_sp_twap_item *twap_item;
	int eww, i;

	eww = mwxsw_sp_twap_items_aww_init(mwxsw_sp);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < twap->twaps_count; i++) {
		twap_item = &twap->twap_items_aww[i];
		eww = devw_twaps_wegistew(devwink, &twap_item->twap, 1,
					  mwxsw_sp);
		if (eww)
			goto eww_twap_wegistew;
	}

	wetuwn 0;

eww_twap_wegistew:
	fow (i--; i >= 0; i--) {
		twap_item = &twap->twap_items_aww[i];
		devw_twaps_unwegistew(devwink, &twap_item->twap, 1);
	}
	mwxsw_sp_twap_items_aww_fini(mwxsw_sp);
	wetuwn eww;
}

static void mwxsw_sp_twaps_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	int i;

	fow (i = twap->twaps_count - 1; i >= 0; i--) {
		const stwuct mwxsw_sp_twap_item *twap_item;

		twap_item = &twap->twap_items_aww[i];
		devw_twaps_unwegistew(devwink, &twap_item->twap, 1);
	}
	mwxsw_sp_twap_items_aww_fini(mwxsw_sp);
}

int mwxsw_sp_devwink_twaps_init(stwuct mwxsw_sp *mwxsw_sp)
{
	int eww;

	eww = mwxsw_sp_twap_cpu_powicews_set(mwxsw_sp);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_twap_dummy_gwoup_init(mwxsw_sp);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_twap_powicews_init(mwxsw_sp);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_twap_gwoups_init(mwxsw_sp);
	if (eww)
		goto eww_twap_gwoups_init;

	eww = mwxsw_sp_twaps_init(mwxsw_sp);
	if (eww)
		goto eww_twaps_init;

	wetuwn 0;

eww_twaps_init:
	mwxsw_sp_twap_gwoups_fini(mwxsw_sp);
eww_twap_gwoups_init:
	mwxsw_sp_twap_powicews_fini(mwxsw_sp);
	wetuwn eww;
}

void mwxsw_sp_devwink_twaps_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	mwxsw_sp_twaps_fini(mwxsw_sp);
	mwxsw_sp_twap_gwoups_fini(mwxsw_sp);
	mwxsw_sp_twap_powicews_fini(mwxsw_sp);
}

int mwxsw_sp_twap_init(stwuct mwxsw_cowe *mwxsw_cowe,
		       const stwuct devwink_twap *twap, void *twap_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	const stwuct mwxsw_sp_twap_item *twap_item;
	int i;

	twap_item = mwxsw_sp_twap_item_wookup(mwxsw_sp, twap->id);
	if (WAWN_ON(!twap_item))
		wetuwn -EINVAW;

	fow (i = 0; i < MWXSW_SP_TWAP_WISTENEWS_MAX; i++) {
		const stwuct mwxsw_wistenew *wistenew;
		int eww;

		wistenew = &twap_item->wistenews_aww[i];
		if (!mwxsw_sp_twap_wistenew_is_vawid(wistenew))
			continue;
		eww = mwxsw_cowe_twap_wegistew(mwxsw_cowe, wistenew, twap_ctx);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void mwxsw_sp_twap_fini(stwuct mwxsw_cowe *mwxsw_cowe,
			const stwuct devwink_twap *twap, void *twap_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	const stwuct mwxsw_sp_twap_item *twap_item;
	int i;

	twap_item = mwxsw_sp_twap_item_wookup(mwxsw_sp, twap->id);
	if (WAWN_ON(!twap_item))
		wetuwn;

	fow (i = MWXSW_SP_TWAP_WISTENEWS_MAX - 1; i >= 0; i--) {
		const stwuct mwxsw_wistenew *wistenew;

		wistenew = &twap_item->wistenews_aww[i];
		if (!mwxsw_sp_twap_wistenew_is_vawid(wistenew))
			continue;
		mwxsw_cowe_twap_unwegistew(mwxsw_cowe, wistenew, twap_ctx);
	}
}

int mwxsw_sp_twap_action_set(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct devwink_twap *twap,
			     enum devwink_twap_action action,
			     stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	const stwuct mwxsw_sp_twap_item *twap_item;
	int i;

	twap_item = mwxsw_sp_twap_item_wookup(mwxsw_sp, twap->id);
	if (WAWN_ON(!twap_item))
		wetuwn -EINVAW;

	if (twap_item->is_souwce) {
		NW_SET_EWW_MSG_MOD(extack, "Changing the action of souwce twaps is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	fow (i = 0; i < MWXSW_SP_TWAP_WISTENEWS_MAX; i++) {
		const stwuct mwxsw_wistenew *wistenew;
		boow enabwed;
		int eww;

		wistenew = &twap_item->wistenews_aww[i];
		if (!mwxsw_sp_twap_wistenew_is_vawid(wistenew))
			continue;

		switch (action) {
		case DEVWINK_TWAP_ACTION_DWOP:
			enabwed = fawse;
			bweak;
		case DEVWINK_TWAP_ACTION_TWAP:
			enabwed = twue;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		eww = mwxsw_cowe_twap_state_set(mwxsw_cowe, wistenew, enabwed);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
__mwxsw_sp_twap_gwoup_init(stwuct mwxsw_cowe *mwxsw_cowe,
			   const stwuct devwink_twap_gwoup *gwoup,
			   u32 powicew_id, stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	u16 hw_powicew_id = MWXSW_WEG_HTGT_INVAWID_POWICEW;
	const stwuct mwxsw_sp_twap_gwoup_item *gwoup_item;
	chaw htgt_pw[MWXSW_WEG_HTGT_WEN];

	gwoup_item = mwxsw_sp_twap_gwoup_item_wookup(mwxsw_sp, gwoup->id);
	if (WAWN_ON(!gwoup_item))
		wetuwn -EINVAW;

	if (gwoup_item->fixed_powicew && powicew_id != gwoup->init_powicew_id) {
		NW_SET_EWW_MSG_MOD(extack, "Changing the powicew binding of this gwoup is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (powicew_id) {
		stwuct mwxsw_sp_twap_powicew_item *powicew_item;

		powicew_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp,
								 powicew_id);
		if (WAWN_ON(!powicew_item))
			wetuwn -EINVAW;
		hw_powicew_id = powicew_item->hw_id;
	}

	mwxsw_weg_htgt_pack(htgt_pw, gwoup_item->hw_gwoup_id, hw_powicew_id,
			    gwoup_item->pwiowity, gwoup_item->pwiowity);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(htgt), htgt_pw);
}

int mwxsw_sp_twap_gwoup_init(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct devwink_twap_gwoup *gwoup)
{
	wetuwn __mwxsw_sp_twap_gwoup_init(mwxsw_cowe, gwoup,
					  gwoup->init_powicew_id, NUWW);
}

int mwxsw_sp_twap_gwoup_set(stwuct mwxsw_cowe *mwxsw_cowe,
			    const stwuct devwink_twap_gwoup *gwoup,
			    const stwuct devwink_twap_powicew *powicew,
			    stwuct netwink_ext_ack *extack)
{
	u32 powicew_id = powicew ? powicew->id : 0;

	wetuwn __mwxsw_sp_twap_gwoup_init(mwxsw_cowe, gwoup, powicew_id,
					  extack);
}

static int
mwxsw_sp_twap_powicew_item_init(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_twap_powicew_item *powicew_item)
{
	stwuct mwxsw_sp_twap *twap = mwxsw_sp->twap;
	u16 hw_id;

	/* We shouwd be abwe to awwocate a powicew because the numbew of
	 * powicews we wegistewed with devwink is in accowding with the numbew
	 * of avaiwabwe powicews.
	 */
	hw_id = find_fiwst_zewo_bit(twap->powicews_usage, twap->max_powicews);
	if (WAWN_ON(hw_id == twap->max_powicews))
		wetuwn -ENOBUFS;

	__set_bit(hw_id, twap->powicews_usage);
	powicew_item->hw_id = hw_id;

	wetuwn 0;
}

static void
mwxsw_sp_twap_powicew_item_fini(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_twap_powicew_item *powicew_item)
{
	__cweaw_bit(powicew_item->hw_id, mwxsw_sp->twap->powicews_usage);
}

static int mwxsw_sp_twap_powicew_bs(u64 buwst, u8 *p_buwst_size,
				    stwuct netwink_ext_ack *extack)
{
	int bs = fws64(buwst) - 1;

	if (buwst != (BIT_UWW(bs))) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew buwst size is not powew of two");
		wetuwn -EINVAW;
	}

	*p_buwst_size = bs;

	wetuwn 0;
}

static int __mwxsw_sp_twap_powicew_set(stwuct mwxsw_sp *mwxsw_sp, u16 hw_id,
				       u64 wate, u64 buwst, boow cweaw_countew,
				       stwuct netwink_ext_ack *extack)
{
	chaw qpcw_pw[MWXSW_WEG_QPCW_WEN];
	u8 buwst_size;
	int eww;

	eww = mwxsw_sp_twap_powicew_bs(buwst, &buwst_size, extack);
	if (eww)
		wetuwn eww;

	mwxsw_weg_qpcw_pack(qpcw_pw, hw_id, MWXSW_WEG_QPCW_IW_UNITS_M, fawse,
			    wate, buwst_size);
	mwxsw_weg_qpcw_cweaw_countew_set(qpcw_pw, cweaw_countew);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpcw), qpcw_pw);
}

int mwxsw_sp_twap_powicew_init(stwuct mwxsw_cowe *mwxsw_cowe,
			       const stwuct devwink_twap_powicew *powicew)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	stwuct mwxsw_sp_twap_powicew_item *powicew_item;
	int eww;

	powicew_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp, powicew->id);
	if (WAWN_ON(!powicew_item))
		wetuwn -EINVAW;

	eww = mwxsw_sp_twap_powicew_item_init(mwxsw_sp, powicew_item);
	if (eww)
		wetuwn eww;

	eww = __mwxsw_sp_twap_powicew_set(mwxsw_sp, powicew_item->hw_id,
					  powicew->init_wate,
					  powicew->init_buwst, twue, NUWW);
	if (eww)
		goto eww_twap_powicew_set;

	wetuwn 0;

eww_twap_powicew_set:
	mwxsw_sp_twap_powicew_item_fini(mwxsw_sp, powicew_item);
	wetuwn eww;
}

void mwxsw_sp_twap_powicew_fini(stwuct mwxsw_cowe *mwxsw_cowe,
				const stwuct devwink_twap_powicew *powicew)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	stwuct mwxsw_sp_twap_powicew_item *powicew_item;

	powicew_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp, powicew->id);
	if (WAWN_ON(!powicew_item))
		wetuwn;

	mwxsw_sp_twap_powicew_item_fini(mwxsw_sp, powicew_item);
}

int mwxsw_sp_twap_powicew_set(stwuct mwxsw_cowe *mwxsw_cowe,
			      const stwuct devwink_twap_powicew *powicew,
			      u64 wate, u64 buwst,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	stwuct mwxsw_sp_twap_powicew_item *powicew_item;

	powicew_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp, powicew->id);
	if (WAWN_ON(!powicew_item))
		wetuwn -EINVAW;

	wetuwn __mwxsw_sp_twap_powicew_set(mwxsw_sp, powicew_item->hw_id,
					   wate, buwst, fawse, extack);
}

int
mwxsw_sp_twap_powicew_countew_get(stwuct mwxsw_cowe *mwxsw_cowe,
				  const stwuct devwink_twap_powicew *powicew,
				  u64 *p_dwops)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	stwuct mwxsw_sp_twap_powicew_item *powicew_item;
	chaw qpcw_pw[MWXSW_WEG_QPCW_WEN];
	int eww;

	powicew_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp, powicew->id);
	if (WAWN_ON(!powicew_item))
		wetuwn -EINVAW;

	mwxsw_weg_qpcw_pack(qpcw_pw, powicew_item->hw_id,
			    MWXSW_WEG_QPCW_IW_UNITS_M, fawse, 0, 0);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(qpcw), qpcw_pw);
	if (eww)
		wetuwn eww;

	*p_dwops = mwxsw_weg_qpcw_viowate_count_get(qpcw_pw);

	wetuwn 0;
}

int mwxsw_sp_twap_gwoup_powicew_hw_id_get(stwuct mwxsw_sp *mwxsw_sp, u16 id,
					  boow *p_enabwed, u16 *p_hw_id)
{
	stwuct mwxsw_sp_twap_powicew_item *pow_item;
	stwuct mwxsw_sp_twap_gwoup_item *gw_item;
	u32 pow_id;

	gw_item = mwxsw_sp_twap_gwoup_item_wookup(mwxsw_sp, id);
	if (!gw_item)
		wetuwn -ENOENT;

	pow_id = gw_item->gwoup.init_powicew_id;
	if (!pow_id) {
		*p_enabwed = fawse;
		wetuwn 0;
	}

	pow_item = mwxsw_sp_twap_powicew_item_wookup(mwxsw_sp, pow_id);
	if (WAWN_ON(!pow_item))
		wetuwn -ENOENT;

	*p_enabwed = twue;
	*p_hw_id = pow_item->hw_id;
	wetuwn 0;
}

static const stwuct mwxsw_sp_twap_gwoup_item
mwxsw_sp1_twap_gwoup_items_aww[] = {
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(ACW_SAMPWE, 0),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_PKT_SAMPWE,
		.pwiowity = 0,
	},
};

static const stwuct mwxsw_sp_twap_item
mwxsw_sp1_twap_items_aww[] = {
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(FWOW_ACTION_SAMPWE, ACW_SAMPWE,
					      MIWWOW),
		.wistenews_aww = {
			MWXSW_WXW(mwxsw_sp_wx_sampwe_wistenew, PKT_SAMPWE,
				  MIWWOW_TO_CPU, fawse, SP_PKT_SAMPWE, DISCAWD),
		},
	},
};

static int
mwxsw_sp1_twap_gwoups_init(stwuct mwxsw_sp *mwxsw_sp,
			   const stwuct mwxsw_sp_twap_gwoup_item **aww,
			   size_t *p_gwoups_count)
{
	*aww = mwxsw_sp1_twap_gwoup_items_aww;
	*p_gwoups_count = AWWAY_SIZE(mwxsw_sp1_twap_gwoup_items_aww);

	wetuwn 0;
}

static int mwxsw_sp1_twaps_init(stwuct mwxsw_sp *mwxsw_sp,
				const stwuct mwxsw_sp_twap_item **aww,
				size_t *p_twaps_count)
{
	*aww = mwxsw_sp1_twap_items_aww;
	*p_twaps_count = AWWAY_SIZE(mwxsw_sp1_twap_items_aww);

	wetuwn 0;
}

const stwuct mwxsw_sp_twap_ops mwxsw_sp1_twap_ops = {
	.gwoups_init = mwxsw_sp1_twap_gwoups_init,
	.twaps_init = mwxsw_sp1_twaps_init,
};

static const stwuct mwxsw_sp_twap_gwoup_item
mwxsw_sp2_twap_gwoup_items_aww[] = {
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(BUFFEW_DWOPS, 20),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_BUFFEW_DISCAWDS,
		.pwiowity = 0,
		.fixed_powicew = twue,
	},
	{
		.gwoup = DEVWINK_TWAP_GWOUP_GENEWIC(ACW_SAMPWE, 0),
		.hw_gwoup_id = MWXSW_WEG_HTGT_TWAP_GWOUP_SP_PKT_SAMPWE,
		.pwiowity = 0,
		.fixed_powicew = twue,
	},
};

static const stwuct mwxsw_sp_twap_item
mwxsw_sp2_twap_items_aww[] = {
	{
		.twap = MWXSW_SP_TWAP_BUFFEW_DWOP(EAWWY_DWOP),
		.wistenews_aww = {
			MWXSW_SP_WXW_BUFFEW_DISCAWD(INGWESS_WWED),
		},
		.is_souwce = twue,
	},
	{
		.twap = MWXSW_SP_TWAP_CONTWOW(FWOW_ACTION_SAMPWE, ACW_SAMPWE,
					      MIWWOW),
		.wistenews_aww = {
			MWXSW_WXW_MIWWOW(mwxsw_sp_wx_sampwe_wistenew, 1,
					 SP_PKT_SAMPWE,
					 MWXSW_SP_MIWWOW_WEASON_INGWESS),
			MWXSW_WXW_MIWWOW(mwxsw_sp_wx_sampwe_tx_wistenew, 1,
					 SP_PKT_SAMPWE,
					 MWXSW_SP_MIWWOW_WEASON_EGWESS),
			MWXSW_WXW_MIWWOW(mwxsw_sp_wx_sampwe_acw_wistenew, 1,
					 SP_PKT_SAMPWE,
					 MWXSW_SP_MIWWOW_WEASON_POWICY_ENGINE),
		},
	},
};

static int
mwxsw_sp2_twap_gwoups_init(stwuct mwxsw_sp *mwxsw_sp,
			   const stwuct mwxsw_sp_twap_gwoup_item **aww,
			   size_t *p_gwoups_count)
{
	*aww = mwxsw_sp2_twap_gwoup_items_aww;
	*p_gwoups_count = AWWAY_SIZE(mwxsw_sp2_twap_gwoup_items_aww);

	wetuwn 0;
}

static int mwxsw_sp2_twaps_init(stwuct mwxsw_sp *mwxsw_sp,
				const stwuct mwxsw_sp_twap_item **aww,
				size_t *p_twaps_count)
{
	*aww = mwxsw_sp2_twap_items_aww;
	*p_twaps_count = AWWAY_SIZE(mwxsw_sp2_twap_items_aww);

	wetuwn 0;
}

const stwuct mwxsw_sp_twap_ops mwxsw_sp2_twap_ops = {
	.gwoups_init = mwxsw_sp2_twap_gwoups_init,
	.twaps_init = mwxsw_sp2_twaps_init,
};
