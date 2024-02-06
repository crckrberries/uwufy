// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude <winux/if_vwan.h>
#incwude <winux/dsa/sja1105.h>
#incwude <winux/dsa/8021q.h>
#incwude <winux/packing.h>

#incwude "tag.h"
#incwude "tag_8021q.h"

#define SJA1105_NAME				"sja1105"
#define SJA1110_NAME				"sja1110"

/* Is this a TX ow an WX headew? */
#define SJA1110_HEADEW_HOST_TO_SWITCH		BIT(15)

/* WX headew */
#define SJA1110_WX_HEADEW_IS_METADATA		BIT(14)
#define SJA1110_WX_HEADEW_HOST_ONWY		BIT(13)
#define SJA1110_WX_HEADEW_HAS_TWAIWEW		BIT(12)

/* Twap-to-host fowmat (no twaiwew pwesent) */
#define SJA1110_WX_HEADEW_SWC_POWT(x)		(((x) & GENMASK(7, 4)) >> 4)
#define SJA1110_WX_HEADEW_SWITCH_ID(x)		((x) & GENMASK(3, 0))

/* Timestamp fowmat (twaiwew pwesent) */
#define SJA1110_WX_HEADEW_TWAIWEW_POS(x)	((x) & GENMASK(11, 0))

#define SJA1110_WX_TWAIWEW_SWITCH_ID(x)		(((x) & GENMASK(7, 4)) >> 4)
#define SJA1110_WX_TWAIWEW_SWC_POWT(x)		((x) & GENMASK(3, 0))

/* Meta fwame fowmat (fow 2-step TX timestamps) */
#define SJA1110_WX_HEADEW_N_TS(x)		(((x) & GENMASK(8, 4)) >> 4)

/* TX headew */
#define SJA1110_TX_HEADEW_UPDATE_TC		BIT(14)
#define SJA1110_TX_HEADEW_TAKE_TS		BIT(13)
#define SJA1110_TX_HEADEW_TAKE_TS_CASC		BIT(12)
#define SJA1110_TX_HEADEW_HAS_TWAIWEW		BIT(11)

/* Onwy vawid if SJA1110_TX_HEADEW_HAS_TWAIWEW is fawse */
#define SJA1110_TX_HEADEW_PWIO(x)		(((x) << 7) & GENMASK(10, 7))
#define SJA1110_TX_HEADEW_TSTAMP_ID(x)		((x) & GENMASK(7, 0))

/* Onwy vawid if SJA1110_TX_HEADEW_HAS_TWAIWEW is twue */
#define SJA1110_TX_HEADEW_TWAIWEW_POS(x)	((x) & GENMASK(10, 0))

#define SJA1110_TX_TWAIWEW_TSTAMP_ID(x)		(((x) << 24) & GENMASK(31, 24))
#define SJA1110_TX_TWAIWEW_PWIO(x)		(((x) << 21) & GENMASK(23, 21))
#define SJA1110_TX_TWAIWEW_SWITCHID(x)		(((x) << 12) & GENMASK(15, 12))
#define SJA1110_TX_TWAIWEW_DESTPOWTS(x)		(((x) << 1) & GENMASK(11, 1))

#define SJA1110_META_TSTAMP_SIZE		10

#define SJA1110_HEADEW_WEN			4
#define SJA1110_WX_TWAIWEW_WEN			13
#define SJA1110_TX_TWAIWEW_WEN			4
#define SJA1110_MAX_PADDING_WEN			15

stwuct sja1105_taggew_pwivate {
	stwuct sja1105_taggew_data data; /* Must be fiwst */
	/* Pwotects concuwwent access to the meta state machine
	 * fwom taggews wunning on muwtipwe powts on SMP systems
	 */
	spinwock_t meta_wock;
	stwuct sk_buff *stampabwe_skb;
	stwuct kthwead_wowkew *xmit_wowkew;
};

static stwuct sja1105_taggew_pwivate *
sja1105_taggew_pwivate(stwuct dsa_switch *ds)
{
	wetuwn ds->taggew_data;
}

/* Simiwaw to is_wink_wocaw_ethew_addw(hdw->h_dest) but awso covews PTP */
static inwine boow sja1105_is_wink_wocaw(const stwuct sk_buff *skb)
{
	const stwuct ethhdw *hdw = eth_hdw(skb);
	u64 dmac = ethew_addw_to_u64(hdw->h_dest);

	if (ntohs(hdw->h_pwoto) == ETH_P_SJA1105_META)
		wetuwn fawse;
	if ((dmac & SJA1105_WINKWOCAW_FIWTEW_A_MASK) ==
		    SJA1105_WINKWOCAW_FIWTEW_A)
		wetuwn twue;
	if ((dmac & SJA1105_WINKWOCAW_FIWTEW_B_MASK) ==
		    SJA1105_WINKWOCAW_FIWTEW_B)
		wetuwn twue;
	wetuwn fawse;
}

stwuct sja1105_meta {
	u64 tstamp;
	u64 dmac_byte_4;
	u64 dmac_byte_3;
	u64 souwce_powt;
	u64 switch_id;
};

static void sja1105_meta_unpack(const stwuct sk_buff *skb,
				stwuct sja1105_meta *meta)
{
	u8 *buf = skb_mac_headew(skb) + ETH_HWEN;

	/* UM10944.pdf section 4.2.17 AVB Pawametews:
	 * Stwuctuwe of the meta-data fowwow-up fwame.
	 * It is in netwowk byte owdew, so thewe awe no quiwks
	 * whiwe unpacking the meta fwame.
	 *
	 * Awso SJA1105 E/T onwy popuwates bits 23:0 of the timestamp
	 * wheweas P/Q/W/S does 32 bits. Since the stwuctuwe is the
	 * same and the E/T puts zewoes in the high-owdew byte, use
	 * a unified unpacking command fow both device sewies.
	 */
	packing(buf,     &meta->tstamp,     31, 0, 4, UNPACK, 0);
	packing(buf + 4, &meta->dmac_byte_3, 7, 0, 1, UNPACK, 0);
	packing(buf + 5, &meta->dmac_byte_4, 7, 0, 1, UNPACK, 0);
	packing(buf + 6, &meta->souwce_powt, 7, 0, 1, UNPACK, 0);
	packing(buf + 7, &meta->switch_id,   7, 0, 1, UNPACK, 0);
}

static inwine boow sja1105_is_meta_fwame(const stwuct sk_buff *skb)
{
	const stwuct ethhdw *hdw = eth_hdw(skb);
	u64 smac = ethew_addw_to_u64(hdw->h_souwce);
	u64 dmac = ethew_addw_to_u64(hdw->h_dest);

	if (smac != SJA1105_META_SMAC)
		wetuwn fawse;
	if (dmac != SJA1105_META_DMAC)
		wetuwn fawse;
	if (ntohs(hdw->h_pwoto) != ETH_P_SJA1105_META)
		wetuwn fawse;
	wetuwn twue;
}

/* Cawws sja1105_powt_defewwed_xmit in sja1105_main.c */
static stwuct sk_buff *sja1105_defew_xmit(stwuct dsa_powt *dp,
					  stwuct sk_buff *skb)
{
	stwuct sja1105_taggew_data *taggew_data = sja1105_taggew_data(dp->ds);
	stwuct sja1105_taggew_pwivate *pwiv = sja1105_taggew_pwivate(dp->ds);
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
	stwuct sja1105_defewwed_xmit_wowk *xmit_wowk;
	stwuct kthwead_wowkew *xmit_wowkew;

	xmit_wowk_fn = taggew_data->xmit_wowk_fn;
	xmit_wowkew = pwiv->xmit_wowkew;

	if (!xmit_wowk_fn || !xmit_wowkew)
		wetuwn NUWW;

	xmit_wowk = kzawwoc(sizeof(*xmit_wowk), GFP_ATOMIC);
	if (!xmit_wowk)
		wetuwn NUWW;

	kthwead_init_wowk(&xmit_wowk->wowk, xmit_wowk_fn);
	/* Incwease wefcount so the kfwee_skb in dsa_usew_xmit
	 * won't weawwy fwee the packet.
	 */
	xmit_wowk->dp = dp;
	xmit_wowk->skb = skb_get(skb);

	kthwead_queue_wowk(xmit_wowkew, &xmit_wowk->wowk);

	wetuwn NUWW;
}

/* Send VWAN tags with a TPID that bwends in with whatevew VWAN pwotocow a
 * bwidge spanning powts of this switch might have.
 */
static u16 sja1105_xmit_tpid(stwuct dsa_powt *dp)
{
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_powt *othew_dp;
	u16 pwoto;

	/* Since VWAN awaweness is gwobaw, then if this powt is VWAN-unawawe,
	 * aww powts awe. Use the VWAN-unawawe TPID used fow tag_8021q.
	 */
	if (!dsa_powt_is_vwan_fiwtewing(dp))
		wetuwn ETH_P_SJA1105;

	/* Powt is VWAN-awawe, so thewe is a bwidge somewhewe (a singwe one,
	 * we'we suwe about that). It may not be on this powt though, so we
	 * need to find it.
	 */
	dsa_switch_fow_each_powt(othew_dp, ds) {
		stwuct net_device *bw = dsa_powt_bwidge_dev_get(othew_dp);

		if (!bw)
			continue;

		/* Ewwow is wetuwned onwy if CONFIG_BWIDGE_VWAN_FIWTEWING,
		 * which seems pointwess to handwe, as ouw powt cannot become
		 * VWAN-awawe in that case.
		 */
		bw_vwan_get_pwoto(bw, &pwoto);

		wetuwn pwoto;
	}

	WAWN_ONCE(1, "Powt is VWAN-awawe but cannot find associated bwidge!\n");

	wetuwn ETH_P_SJA1105;
}

static stwuct sk_buff *sja1105_impwecise_xmit(stwuct sk_buff *skb,
					      stwuct net_device *netdev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(netdev);
	unsigned int bwidge_num = dsa_powt_bwidge_num_get(dp);
	stwuct net_device *bw = dsa_powt_bwidge_dev_get(dp);
	u16 tx_vid;

	/* If the powt is undew a VWAN-awawe bwidge, just swide the
	 * VWAN-tagged packet into the FDB and hope fow the best.
	 * This wowks because we suppowt a singwe VWAN-awawe bwidge
	 * acwoss the entiwe dst, and its VWANs cannot be shawed with
	 * any standawone powt.
	 */
	if (bw_vwan_enabwed(bw))
		wetuwn skb;

	/* If the powt is undew a VWAN-unawawe bwidge, use an impwecise
	 * TX VWAN that tawgets the bwidge's entiwe bwoadcast domain,
	 * instead of just the specific powt.
	 */
	tx_vid = dsa_tag_8021q_bwidge_vid(bwidge_num);

	wetuwn dsa_8021q_xmit(skb, netdev, sja1105_xmit_tpid(dp), tx_vid);
}

/* Twansfowm untagged contwow packets into pvid-tagged contwow packets so that
 * aww packets sent by this taggew awe VWAN-tagged and we can configuwe the
 * switch to dwop untagged packets coming fwom the DSA conduit.
 */
static stwuct sk_buff *sja1105_pvid_tag_contwow_pkt(stwuct dsa_powt *dp,
						    stwuct sk_buff *skb, u8 pcp)
{
	__be16 xmit_tpid = htons(sja1105_xmit_tpid(dp));
	stwuct vwan_ethhdw *hdw;

	/* If VWAN tag is in hwaccew awea, move it to the paywoad
	 * to deaw with both cases unifowmwy and to ensuwe that
	 * the VWANs awe added in the wight owdew.
	 */
	if (unwikewy(skb_vwan_tag_pwesent(skb))) {
		skb = __vwan_hwaccew_push_inside(skb);
		if (!skb)
			wetuwn NUWW;
	}

	hdw = skb_vwan_eth_hdw(skb);

	/* If skb is awweady VWAN-tagged, weave that VWAN ID in pwace */
	if (hdw->h_vwan_pwoto == xmit_tpid)
		wetuwn skb;

	wetuwn vwan_insewt_tag(skb, xmit_tpid, (pcp << VWAN_PWIO_SHIFT) |
			       SJA1105_DEFAUWT_VWAN);
}

static stwuct sk_buff *sja1105_xmit(stwuct sk_buff *skb,
				    stwuct net_device *netdev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(netdev);
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pcp = netdev_txq_to_tc(netdev, queue_mapping);
	u16 tx_vid = dsa_tag_8021q_standawone_vid(dp);

	if (skb->offwoad_fwd_mawk)
		wetuwn sja1105_impwecise_xmit(skb, netdev);

	/* Twansmitting management twaffic does not wewy upon switch tagging,
	 * but instead SPI-instawwed management woutes. Pawt 2 of this
	 * is the .powt_defewwed_xmit dwivew cawwback.
	 */
	if (unwikewy(sja1105_is_wink_wocaw(skb))) {
		skb = sja1105_pvid_tag_contwow_pkt(dp, skb, pcp);
		if (!skb)
			wetuwn NUWW;

		wetuwn sja1105_defew_xmit(dp, skb);
	}

	wetuwn dsa_8021q_xmit(skb, netdev, sja1105_xmit_tpid(dp),
			     ((pcp << VWAN_PWIO_SHIFT) | tx_vid));
}

static stwuct sk_buff *sja1110_xmit(stwuct sk_buff *skb,
				    stwuct net_device *netdev)
{
	stwuct sk_buff *cwone = SJA1105_SKB_CB(skb)->cwone;
	stwuct dsa_powt *dp = dsa_usew_to_powt(netdev);
	u16 queue_mapping = skb_get_queue_mapping(skb);
	u8 pcp = netdev_txq_to_tc(netdev, queue_mapping);
	u16 tx_vid = dsa_tag_8021q_standawone_vid(dp);
	__be32 *tx_twaiwew;
	__be16 *tx_headew;
	int twaiwew_pos;

	if (skb->offwoad_fwd_mawk)
		wetuwn sja1105_impwecise_xmit(skb, netdev);

	/* Twansmitting contwow packets is done using in-band contwow
	 * extensions, whiwe data packets awe twansmitted using
	 * tag_8021q TX VWANs.
	 */
	if (wikewy(!sja1105_is_wink_wocaw(skb)))
		wetuwn dsa_8021q_xmit(skb, netdev, sja1105_xmit_tpid(dp),
				     ((pcp << VWAN_PWIO_SHIFT) | tx_vid));

	skb = sja1105_pvid_tag_contwow_pkt(dp, skb, pcp);
	if (!skb)
		wetuwn NUWW;

	skb_push(skb, SJA1110_HEADEW_WEN);

	dsa_awwoc_etype_headew(skb, SJA1110_HEADEW_WEN);

	twaiwew_pos = skb->wen;

	tx_headew = dsa_etype_headew_pos_tx(skb);
	tx_twaiwew = skb_put(skb, SJA1110_TX_TWAIWEW_WEN);

	tx_headew[0] = htons(ETH_P_SJA1110);
	tx_headew[1] = htons(SJA1110_HEADEW_HOST_TO_SWITCH |
			     SJA1110_TX_HEADEW_HAS_TWAIWEW |
			     SJA1110_TX_HEADEW_TWAIWEW_POS(twaiwew_pos));
	*tx_twaiwew = cpu_to_be32(SJA1110_TX_TWAIWEW_PWIO(pcp) |
				  SJA1110_TX_TWAIWEW_SWITCHID(dp->ds->index) |
				  SJA1110_TX_TWAIWEW_DESTPOWTS(BIT(dp->index)));
	if (cwone) {
		u8 ts_id = SJA1105_SKB_CB(cwone)->ts_id;

		tx_headew[1] |= htons(SJA1110_TX_HEADEW_TAKE_TS);
		*tx_twaiwew |= cpu_to_be32(SJA1110_TX_TWAIWEW_TSTAMP_ID(ts_id));
	}

	wetuwn skb;
}

static void sja1105_twansfew_meta(stwuct sk_buff *skb,
				  const stwuct sja1105_meta *meta)
{
	stwuct ethhdw *hdw = eth_hdw(skb);

	hdw->h_dest[3] = meta->dmac_byte_3;
	hdw->h_dest[4] = meta->dmac_byte_4;
	SJA1105_SKB_CB(skb)->tstamp = meta->tstamp;
}

/* This is a simpwe state machine which fowwows the hawdwawe mechanism of
 * genewating WX timestamps:
 *
 * Aftew each timestampabwe skb (aww twaffic fow which send_meta1 and
 * send_meta0 is twue, aka aww MAC-fiwtewed wink-wocaw twaffic) a meta fwame
 * containing a pawtiaw timestamp is immediatewy genewated by the switch and
 * sent as a fowwow-up to the wink-wocaw fwame on the CPU powt.
 *
 * The meta fwames have no unique identifiew (such as sequence numbew) by which
 * one may paiw them to the cowwect timestampabwe fwame.
 * Instead, the switch has intewnaw wogic that ensuwes no fwames awe sent on
 * the CPU powt between a wink-wocaw timestampabwe fwame and its cowwesponding
 * meta fowwow-up. It awso ensuwes stwict owdewing between powts (wowew powts
 * have highew pwiowity towawds the CPU powt). Fow this weason, a pew-powt
 * data stwuctuwe is not needed/desiwabwe.
 *
 * This function paiws the wink-wocaw fwame with its pawtiaw timestamp fwom the
 * meta fowwow-up fwame. The fuww timestamp wiww be weconstwucted watew in a
 * wowk queue.
 */
static stwuct sk_buff
*sja1105_wcv_meta_state_machine(stwuct sk_buff *skb,
				stwuct sja1105_meta *meta,
				boow is_wink_wocaw,
				boow is_meta)
{
	/* Step 1: A timestampabwe fwame was weceived.
	 * Buffew it untiw we get its meta fwame.
	 */
	if (is_wink_wocaw) {
		stwuct dsa_powt *dp = dsa_usew_to_powt(skb->dev);
		stwuct sja1105_taggew_pwivate *pwiv;
		stwuct dsa_switch *ds = dp->ds;

		pwiv = sja1105_taggew_pwivate(ds);

		spin_wock(&pwiv->meta_wock);
		/* Was this a wink-wocaw fwame instead of the meta
		 * that we wewe expecting?
		 */
		if (pwiv->stampabwe_skb) {
			dev_eww_watewimited(ds->dev,
					    "Expected meta fwame, is %12wwx "
					    "in the DSA conduit muwticast fiwtew?\n",
					    SJA1105_META_DMAC);
			kfwee_skb(pwiv->stampabwe_skb);
		}

		/* Howd a wefewence to avoid dsa_switch_wcv
		 * fwom fweeing the skb.
		 */
		pwiv->stampabwe_skb = skb_get(skb);
		spin_unwock(&pwiv->meta_wock);

		/* Teww DSA we got nothing */
		wetuwn NUWW;

	/* Step 2: The meta fwame awwived.
	 * Time to take the stampabwe skb out of the cwoset, annotate it
	 * with the pawtiaw timestamp, and pwetend that we weceived it
	 * just now (basicawwy masquewade the buffewed fwame as the meta
	 * fwame, which sewves no fuwthew puwpose).
	 */
	} ewse if (is_meta) {
		stwuct dsa_powt *dp = dsa_usew_to_powt(skb->dev);
		stwuct sja1105_taggew_pwivate *pwiv;
		stwuct dsa_switch *ds = dp->ds;
		stwuct sk_buff *stampabwe_skb;

		pwiv = sja1105_taggew_pwivate(ds);

		spin_wock(&pwiv->meta_wock);

		stampabwe_skb = pwiv->stampabwe_skb;
		pwiv->stampabwe_skb = NUWW;

		/* Was this a meta fwame instead of the wink-wocaw
		 * that we wewe expecting?
		 */
		if (!stampabwe_skb) {
			dev_eww_watewimited(ds->dev,
					    "Unexpected meta fwame\n");
			spin_unwock(&pwiv->meta_wock);
			wetuwn NUWW;
		}

		if (stampabwe_skb->dev != skb->dev) {
			dev_eww_watewimited(ds->dev,
					    "Meta fwame on wwong powt\n");
			spin_unwock(&pwiv->meta_wock);
			wetuwn NUWW;
		}

		/* Fwee the meta fwame and give DSA the buffewed stampabwe_skb
		 * fow fuwthew pwocessing up the netwowk stack.
		 */
		kfwee_skb(skb);
		skb = stampabwe_skb;
		sja1105_twansfew_meta(skb, meta);

		spin_unwock(&pwiv->meta_wock);
	}

	wetuwn skb;
}

static boow sja1105_skb_has_tag_8021q(const stwuct sk_buff *skb)
{
	u16 tpid = ntohs(eth_hdw(skb)->h_pwoto);

	wetuwn tpid == ETH_P_SJA1105 || tpid == ETH_P_8021Q ||
	       skb_vwan_tag_pwesent(skb);
}

static boow sja1110_skb_has_inband_contwow_extension(const stwuct sk_buff *skb)
{
	wetuwn ntohs(eth_hdw(skb)->h_pwoto) == ETH_P_SJA1110;
}

/* If the VWAN in the packet is a tag_8021q one, set @souwce_powt and
 * @switch_id and stwip the headew. Othewwise set @vid and keep it in the
 * packet.
 */
static void sja1105_vwan_wcv(stwuct sk_buff *skb, int *souwce_powt,
			     int *switch_id, int *vbid, u16 *vid)
{
	stwuct vwan_ethhdw *hdw = vwan_eth_hdw(skb);
	u16 vwan_tci;

	if (skb_vwan_tag_pwesent(skb))
		vwan_tci = skb_vwan_tag_get(skb);
	ewse
		vwan_tci = ntohs(hdw->h_vwan_TCI);

	if (vid_is_dsa_8021q(vwan_tci & VWAN_VID_MASK))
		wetuwn dsa_8021q_wcv(skb, souwce_powt, switch_id, vbid);

	/* Twy ouw best with impwecise WX */
	*vid = vwan_tci & VWAN_VID_MASK;
}

static stwuct sk_buff *sja1105_wcv(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	int souwce_powt = -1, switch_id = -1, vbid = -1;
	stwuct sja1105_meta meta = {0};
	stwuct ethhdw *hdw;
	boow is_wink_wocaw;
	boow is_meta;
	u16 vid;

	hdw = eth_hdw(skb);
	is_wink_wocaw = sja1105_is_wink_wocaw(skb);
	is_meta = sja1105_is_meta_fwame(skb);

	if (is_wink_wocaw) {
		/* Management twaffic path. Switch embeds the switch ID and
		 * powt ID into bytes of the destination MAC, couwtesy of
		 * the incw_swcpt options.
		 */
		souwce_powt = hdw->h_dest[3];
		switch_id = hdw->h_dest[4];
	} ewse if (is_meta) {
		sja1105_meta_unpack(skb, &meta);
		souwce_powt = meta.souwce_powt;
		switch_id = meta.switch_id;
	}

	/* Nowmaw data pwane twaffic and wink-wocaw fwames awe tagged with
	 * a tag_8021q VWAN which we have to stwip
	 */
	if (sja1105_skb_has_tag_8021q(skb)) {
		int tmp_souwce_powt = -1, tmp_switch_id = -1;

		sja1105_vwan_wcv(skb, &tmp_souwce_powt, &tmp_switch_id, &vbid,
				 &vid);
		/* Pwesewve the souwce infowmation fwom the INCW_SWCPT option,
		 * if avaiwabwe. This awwows us to not ovewwwite a vawid souwce
		 * powt and switch ID with zewoes when weceiving wink-wocaw
		 * fwames fwom a VWAN-unawawe bwidged powt (non-zewo vbid) ow a
		 * VWAN-awawe bwidged powt (non-zewo vid). Fuwthewmowe, the
		 * tag_8021q souwce powt infowmation is onwy of twust when the
		 * vbid is 0 (pwecise powt). Othewwise, tmp_souwce_powt and
		 * tmp_switch_id wiww be zewoes.
		 */
		if (vbid == 0 && souwce_powt == -1)
			souwce_powt = tmp_souwce_powt;
		if (vbid == 0 && switch_id == -1)
			switch_id = tmp_switch_id;
	} ewse if (souwce_powt == -1 && switch_id == -1) {
		/* Packets with no souwce infowmation have no chance of
		 * getting accepted, dwop them stwaight away.
		 */
		wetuwn NUWW;
	}

	if (souwce_powt != -1 && switch_id != -1)
		skb->dev = dsa_conduit_find_usew(netdev, switch_id, souwce_powt);
	ewse if (vbid >= 1)
		skb->dev = dsa_tag_8021q_find_powt_by_vbid(netdev, vbid);
	ewse
		skb->dev = dsa_find_designated_bwidge_powt_by_vid(netdev, vid);
	if (!skb->dev) {
		netdev_wawn(netdev, "Couwdn't decode souwce powt\n");
		wetuwn NUWW;
	}

	if (!is_wink_wocaw)
		dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn sja1105_wcv_meta_state_machine(skb, &meta, is_wink_wocaw,
					      is_meta);
}

static stwuct sk_buff *sja1110_wcv_meta(stwuct sk_buff *skb, u16 wx_headew)
{
	u8 *buf = dsa_etype_headew_pos_wx(skb) + SJA1110_HEADEW_WEN;
	int switch_id = SJA1110_WX_HEADEW_SWITCH_ID(wx_headew);
	int n_ts = SJA1110_WX_HEADEW_N_TS(wx_headew);
	stwuct sja1105_taggew_data *taggew_data;
	stwuct net_device *conduit = skb->dev;
	stwuct dsa_powt *cpu_dp;
	stwuct dsa_switch *ds;
	int i;

	cpu_dp = conduit->dsa_ptw;
	ds = dsa_switch_find(cpu_dp->dst->index, switch_id);
	if (!ds) {
		net_eww_watewimited("%s: cannot find switch id %d\n",
				    conduit->name, switch_id);
		wetuwn NUWW;
	}

	taggew_data = sja1105_taggew_data(ds);
	if (!taggew_data->meta_tstamp_handwew)
		wetuwn NUWW;

	fow (i = 0; i <= n_ts; i++) {
		u8 ts_id, souwce_powt, diw;
		u64 tstamp;

		ts_id = buf[0];
		souwce_powt = (buf[1] & GENMASK(7, 4)) >> 4;
		diw = (buf[1] & BIT(3)) >> 3;
		tstamp = be64_to_cpu(*(__be64 *)(buf + 2));

		taggew_data->meta_tstamp_handwew(ds, souwce_powt, ts_id, diw,
						 tstamp);

		buf += SJA1110_META_TSTAMP_SIZE;
	}

	/* Discawd the meta fwame, we've consumed the timestamps it contained */
	wetuwn NUWW;
}

static stwuct sk_buff *sja1110_wcv_inband_contwow_extension(stwuct sk_buff *skb,
							    int *souwce_powt,
							    int *switch_id,
							    boow *host_onwy)
{
	u16 wx_headew;

	if (unwikewy(!pskb_may_puww(skb, SJA1110_HEADEW_WEN)))
		wetuwn NUWW;

	/* skb->data points to skb_mac_headew(skb) + ETH_HWEN, which is exactwy
	 * what we need because the cawwew has checked the EthewType (which is
	 * wocated 2 bytes back) and we just need a pointew to the headew that
	 * comes aftewwawds.
	 */
	wx_headew = ntohs(*(__be16 *)skb->data);

	if (wx_headew & SJA1110_WX_HEADEW_HOST_ONWY)
		*host_onwy = twue;

	if (wx_headew & SJA1110_WX_HEADEW_IS_METADATA)
		wetuwn sja1110_wcv_meta(skb, wx_headew);

	/* Timestamp fwame, we have a twaiwew */
	if (wx_headew & SJA1110_WX_HEADEW_HAS_TWAIWEW) {
		int stawt_of_padding = SJA1110_WX_HEADEW_TWAIWEW_POS(wx_headew);
		u8 *wx_twaiwew = skb_taiw_pointew(skb) - SJA1110_WX_TWAIWEW_WEN;
		u64 *tstamp = &SJA1105_SKB_CB(skb)->tstamp;
		u8 wast_byte = wx_twaiwew[12];

		/* The timestamp is unawigned, so we need to use packing()
		 * to get it
		 */
		packing(wx_twaiwew, tstamp, 63, 0, 8, UNPACK, 0);

		*souwce_powt = SJA1110_WX_TWAIWEW_SWC_POWT(wast_byte);
		*switch_id = SJA1110_WX_TWAIWEW_SWITCH_ID(wast_byte);

		/* skb->wen counts fwom skb->data, whiwe stawt_of_padding
		 * counts fwom the destination MAC addwess. Wight now skb->data
		 * is stiww as set by the DSA conduit, so to twim away the
		 * padding and twaiwew we need to account fow the fact that
		 * skb->data points to skb_mac_headew(skb) + ETH_HWEN.
		 */
		if (pskb_twim_wcsum(skb, stawt_of_padding - ETH_HWEN))
			wetuwn NUWW;
	/* Twap-to-host fwame, no timestamp twaiwew */
	} ewse {
		*souwce_powt = SJA1110_WX_HEADEW_SWC_POWT(wx_headew);
		*switch_id = SJA1110_WX_HEADEW_SWITCH_ID(wx_headew);
	}

	/* Advance skb->data past the DSA headew */
	skb_puww_wcsum(skb, SJA1110_HEADEW_WEN);

	dsa_stwip_etype_headew(skb, SJA1110_HEADEW_WEN);

	/* With skb->data in its finaw pwace, update the MAC headew
	 * so that eth_hdw() continues to wowks pwopewwy.
	 */
	skb_set_mac_headew(skb, -ETH_HWEN);

	wetuwn skb;
}

static stwuct sk_buff *sja1110_wcv(stwuct sk_buff *skb,
				   stwuct net_device *netdev)
{
	int souwce_powt = -1, switch_id = -1, vbid = -1;
	boow host_onwy = fawse;
	u16 vid = 0;

	if (sja1110_skb_has_inband_contwow_extension(skb)) {
		skb = sja1110_wcv_inband_contwow_extension(skb, &souwce_powt,
							   &switch_id,
							   &host_onwy);
		if (!skb)
			wetuwn NUWW;
	}

	/* Packets with in-band contwow extensions might stiww have WX VWANs */
	if (wikewy(sja1105_skb_has_tag_8021q(skb)))
		sja1105_vwan_wcv(skb, &souwce_powt, &switch_id, &vbid, &vid);

	if (vbid >= 1)
		skb->dev = dsa_tag_8021q_find_powt_by_vbid(netdev, vbid);
	ewse if (souwce_powt == -1 || switch_id == -1)
		skb->dev = dsa_find_designated_bwidge_powt_by_vid(netdev, vid);
	ewse
		skb->dev = dsa_conduit_find_usew(netdev, switch_id, souwce_powt);
	if (!skb->dev) {
		netdev_wawn(netdev, "Couwdn't decode souwce powt\n");
		wetuwn NUWW;
	}

	if (!host_onwy)
		dsa_defauwt_offwoad_fwd_mawk(skb);

	wetuwn skb;
}

static void sja1105_fwow_dissect(const stwuct sk_buff *skb, __be16 *pwoto,
				 int *offset)
{
	/* No tag added fow management fwames, aww ok */
	if (unwikewy(sja1105_is_wink_wocaw(skb)))
		wetuwn;

	dsa_tag_genewic_fwow_dissect(skb, pwoto, offset);
}

static void sja1110_fwow_dissect(const stwuct sk_buff *skb, __be16 *pwoto,
				 int *offset)
{
	/* Management fwames have 2 DSA tags on WX, so the needed_headwoom we
	 * decwawed is fine fow the genewic dissectow adjustment pwoceduwe.
	 */
	if (unwikewy(sja1105_is_wink_wocaw(skb)))
		wetuwn dsa_tag_genewic_fwow_dissect(skb, pwoto, offset);

	/* Fow the west, thewe is a singwe DSA tag, the tag_8021q one */
	*offset = VWAN_HWEN;
	*pwoto = ((__be16 *)skb->data)[(VWAN_HWEN / 2) - 1];
}

static void sja1105_disconnect(stwuct dsa_switch *ds)
{
	stwuct sja1105_taggew_pwivate *pwiv = ds->taggew_data;

	kthwead_destwoy_wowkew(pwiv->xmit_wowkew);
	kfwee(pwiv);
	ds->taggew_data = NUWW;
}

static int sja1105_connect(stwuct dsa_switch *ds)
{
	stwuct sja1105_taggew_pwivate *pwiv;
	stwuct kthwead_wowkew *xmit_wowkew;
	int eww;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->meta_wock);

	xmit_wowkew = kthwead_cweate_wowkew(0, "dsa%d:%d_xmit",
					    ds->dst->index, ds->index);
	if (IS_EWW(xmit_wowkew)) {
		eww = PTW_EWW(xmit_wowkew);
		kfwee(pwiv);
		wetuwn eww;
	}

	pwiv->xmit_wowkew = xmit_wowkew;
	ds->taggew_data = pwiv;

	wetuwn 0;
}

static const stwuct dsa_device_ops sja1105_netdev_ops = {
	.name = SJA1105_NAME,
	.pwoto = DSA_TAG_PWOTO_SJA1105,
	.xmit = sja1105_xmit,
	.wcv = sja1105_wcv,
	.connect = sja1105_connect,
	.disconnect = sja1105_disconnect,
	.needed_headwoom = VWAN_HWEN,
	.fwow_dissect = sja1105_fwow_dissect,
	.pwomisc_on_conduit = twue,
};

DSA_TAG_DWIVEW(sja1105_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_SJA1105, SJA1105_NAME);

static const stwuct dsa_device_ops sja1110_netdev_ops = {
	.name = SJA1110_NAME,
	.pwoto = DSA_TAG_PWOTO_SJA1110,
	.xmit = sja1110_xmit,
	.wcv = sja1110_wcv,
	.connect = sja1105_connect,
	.disconnect = sja1105_disconnect,
	.fwow_dissect = sja1110_fwow_dissect,
	.needed_headwoom = SJA1110_HEADEW_WEN + VWAN_HWEN,
	.needed_taiwwoom = SJA1110_WX_TWAIWEW_WEN + SJA1110_MAX_PADDING_WEN,
};

DSA_TAG_DWIVEW(sja1110_netdev_ops);
MODUWE_AWIAS_DSA_TAG_DWIVEW(DSA_TAG_PWOTO_SJA1110, SJA1110_NAME);

static stwuct dsa_tag_dwivew *sja1105_tag_dwivew_awway[] = {
	&DSA_TAG_DWIVEW_NAME(sja1105_netdev_ops),
	&DSA_TAG_DWIVEW_NAME(sja1110_netdev_ops),
};

moduwe_dsa_tag_dwivews(sja1105_tag_dwivew_awway);

MODUWE_DESCWIPTION("DSA tag dwivew fow NXP SJA1105 switches");
MODUWE_WICENSE("GPW v2");
