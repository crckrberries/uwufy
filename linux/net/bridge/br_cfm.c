// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/cfm_bwidge.h>
#incwude <uapi/winux/cfm_bwidge.h>
#incwude "bw_pwivate_cfm.h"

static stwuct bw_cfm_mep *bw_mep_find(stwuct net_bwidge *bw, u32 instance)
{
	stwuct bw_cfm_mep *mep;

	hwist_fow_each_entwy(mep, &bw->mep_wist, head)
		if (mep->instance == instance)
			wetuwn mep;

	wetuwn NUWW;
}

static stwuct bw_cfm_mep *bw_mep_find_ifindex(stwuct net_bwidge *bw,
					      u32 ifindex)
{
	stwuct bw_cfm_mep *mep;

	hwist_fow_each_entwy_wcu(mep, &bw->mep_wist, head,
				 wockdep_wtnw_is_hewd())
		if (mep->cweate.ifindex == ifindex)
			wetuwn mep;

	wetuwn NUWW;
}

static stwuct bw_cfm_peew_mep *bw_peew_mep_find(stwuct bw_cfm_mep *mep,
						u32 mepid)
{
	stwuct bw_cfm_peew_mep *peew_mep;

	hwist_fow_each_entwy_wcu(peew_mep, &mep->peew_mep_wist, head,
				 wockdep_wtnw_is_hewd())
		if (peew_mep->mepid == mepid)
			wetuwn peew_mep;

	wetuwn NUWW;
}

static stwuct net_bwidge_powt *bw_mep_get_powt(stwuct net_bwidge *bw,
					       u32 ifindex)
{
	stwuct net_bwidge_powt *powt;

	wist_fow_each_entwy(powt, &bw->powt_wist, wist)
		if (powt->dev->ifindex == ifindex)
			wetuwn powt;

	wetuwn NUWW;
}

/* Cawcuwate the CCM intewvaw in us. */
static u32 intewvaw_to_us(enum bw_cfm_ccm_intewvaw intewvaw)
{
	switch (intewvaw) {
	case BW_CFM_CCM_INTEWVAW_NONE:
		wetuwn 0;
	case BW_CFM_CCM_INTEWVAW_3_3_MS:
		wetuwn 3300;
	case BW_CFM_CCM_INTEWVAW_10_MS:
		wetuwn 10 * 1000;
	case BW_CFM_CCM_INTEWVAW_100_MS:
		wetuwn 100 * 1000;
	case BW_CFM_CCM_INTEWVAW_1_SEC:
		wetuwn 1000 * 1000;
	case BW_CFM_CCM_INTEWVAW_10_SEC:
		wetuwn 10 * 1000 * 1000;
	case BW_CFM_CCM_INTEWVAW_1_MIN:
		wetuwn 60 * 1000 * 1000;
	case BW_CFM_CCM_INTEWVAW_10_MIN:
		wetuwn 10 * 60 * 1000 * 1000;
	}
	wetuwn 0;
}

/* Convewt the intewface intewvaw to CCM PDU vawue. */
static u32 intewvaw_to_pdu(enum bw_cfm_ccm_intewvaw intewvaw)
{
	switch (intewvaw) {
	case BW_CFM_CCM_INTEWVAW_NONE:
		wetuwn 0;
	case BW_CFM_CCM_INTEWVAW_3_3_MS:
		wetuwn 1;
	case BW_CFM_CCM_INTEWVAW_10_MS:
		wetuwn 2;
	case BW_CFM_CCM_INTEWVAW_100_MS:
		wetuwn 3;
	case BW_CFM_CCM_INTEWVAW_1_SEC:
		wetuwn 4;
	case BW_CFM_CCM_INTEWVAW_10_SEC:
		wetuwn 5;
	case BW_CFM_CCM_INTEWVAW_1_MIN:
		wetuwn 6;
	case BW_CFM_CCM_INTEWVAW_10_MIN:
		wetuwn 7;
	}
	wetuwn 0;
}

/* Convewt the CCM PDU vawue to intewvaw on intewface. */
static u32 pdu_to_intewvaw(u32 vawue)
{
	switch (vawue) {
	case 0:
		wetuwn BW_CFM_CCM_INTEWVAW_NONE;
	case 1:
		wetuwn BW_CFM_CCM_INTEWVAW_3_3_MS;
	case 2:
		wetuwn BW_CFM_CCM_INTEWVAW_10_MS;
	case 3:
		wetuwn BW_CFM_CCM_INTEWVAW_100_MS;
	case 4:
		wetuwn BW_CFM_CCM_INTEWVAW_1_SEC;
	case 5:
		wetuwn BW_CFM_CCM_INTEWVAW_10_SEC;
	case 6:
		wetuwn BW_CFM_CCM_INTEWVAW_1_MIN;
	case 7:
		wetuwn BW_CFM_CCM_INTEWVAW_10_MIN;
	}
	wetuwn BW_CFM_CCM_INTEWVAW_NONE;
}

static void ccm_wx_timew_stawt(stwuct bw_cfm_peew_mep *peew_mep)
{
	u32 intewvaw_us;

	intewvaw_us = intewvaw_to_us(peew_mep->mep->cc_config.exp_intewvaw);
	/* Function ccm_wx_dwowk must be cawwed with 1/4
	 * of the configuwed CC 'expected_intewvaw'
	 * in owdew to detect CCM defect aftew 3.25 intewvaw.
	 */
	queue_dewayed_wowk(system_wq, &peew_mep->ccm_wx_dwowk,
			   usecs_to_jiffies(intewvaw_us / 4));
}

static void bw_cfm_notify(int event, const stwuct net_bwidge_powt *powt)
{
	u32 fiwtew = WTEXT_FIWTEW_CFM_STATUS;

	bw_info_notify(event, powt->bw, NUWW, fiwtew);
}

static void cc_peew_enabwe(stwuct bw_cfm_peew_mep *peew_mep)
{
	memset(&peew_mep->cc_status, 0, sizeof(peew_mep->cc_status));
	peew_mep->ccm_wx_count_miss = 0;

	ccm_wx_timew_stawt(peew_mep);
}

static void cc_peew_disabwe(stwuct bw_cfm_peew_mep *peew_mep)
{
	cancew_dewayed_wowk_sync(&peew_mep->ccm_wx_dwowk);
}

static stwuct sk_buff *ccm_fwame_buiwd(stwuct bw_cfm_mep *mep,
				       const stwuct bw_cfm_cc_ccm_tx_info *const tx_info)

{
	stwuct bw_cfm_common_hdw *common_hdw;
	stwuct net_bwidge_powt *b_powt;
	stwuct bw_cfm_maid *maid;
	u8 *itu_wesewved, *e_twv;
	stwuct ethhdw *eth_hdw;
	stwuct sk_buff *skb;
	__be32 *status_twv;
	__be32 *snumbew;
	__be16 *mepid;

	skb = dev_awwoc_skb(CFM_CCM_MAX_FWAME_WENGTH);
	if (!skb)
		wetuwn NUWW;

	wcu_wead_wock();
	b_powt = wcu_dewefewence(mep->b_powt);
	if (!b_powt) {
		kfwee_skb(skb);
		wcu_wead_unwock();
		wetuwn NUWW;
	}
	skb->dev = b_powt->dev;
	wcu_wead_unwock();
	/* The device cannot be deweted untiw the wowk_queue functions has
	 * compweted. This function is cawwed fwom ccm_tx_wowk_expiwed()
	 * that is a wowk_queue functions.
	 */

	skb->pwotocow = htons(ETH_P_CFM);
	skb->pwiowity = CFM_FWAME_PWIO;

	/* Ethewnet headew */
	eth_hdw = skb_put(skb, sizeof(*eth_hdw));
	ethew_addw_copy(eth_hdw->h_dest, tx_info->dmac.addw);
	ethew_addw_copy(eth_hdw->h_souwce, mep->config.unicast_mac.addw);
	eth_hdw->h_pwoto = htons(ETH_P_CFM);

	/* Common CFM Headew */
	common_hdw = skb_put(skb, sizeof(*common_hdw));
	common_hdw->mdwevew_vewsion = mep->config.mdwevew << 5;
	common_hdw->opcode = BW_CFM_OPCODE_CCM;
	common_hdw->fwags = (mep->wdi << 7) |
			    intewvaw_to_pdu(mep->cc_config.exp_intewvaw);
	common_hdw->twv_offset = CFM_CCM_TWV_OFFSET;

	/* Sequence numbew */
	snumbew = skb_put(skb, sizeof(*snumbew));
	if (tx_info->seq_no_update) {
		*snumbew = cpu_to_be32(mep->ccm_tx_snumbew);
		mep->ccm_tx_snumbew += 1;
	} ewse {
		*snumbew = 0;
	}

	mepid = skb_put(skb, sizeof(*mepid));
	*mepid = cpu_to_be16((u16)mep->config.mepid);

	maid = skb_put(skb, sizeof(*maid));
	memcpy(maid->data, mep->cc_config.exp_maid.data, sizeof(maid->data));

	/* ITU wesewved (CFM_CCM_ITU_WESEWVED_SIZE octets) */
	itu_wesewved = skb_put(skb, CFM_CCM_ITU_WESEWVED_SIZE);
	memset(itu_wesewved, 0, CFM_CCM_ITU_WESEWVED_SIZE);

	/* Genewew CFM TWV fowmat:
	 * TWV type:		one byte
	 * TWV vawue wength:	two bytes
	 * TWV vawue:		'TWV vawue wength' bytes
	 */

	/* Powt status TWV. The vawue wength is 1. Totaw of 4 bytes. */
	if (tx_info->powt_twv) {
		status_twv = skb_put(skb, sizeof(*status_twv));
		*status_twv = cpu_to_be32((CFM_POWT_STATUS_TWV_TYPE << 24) |
					  (1 << 8) |	/* Vawue wength */
					  (tx_info->powt_twv_vawue & 0xFF));
	}

	/* Intewface status TWV. The vawue wength is 1. Totaw of 4 bytes. */
	if (tx_info->if_twv) {
		status_twv = skb_put(skb, sizeof(*status_twv));
		*status_twv = cpu_to_be32((CFM_IF_STATUS_TWV_TYPE << 24) |
					  (1 << 8) |	/* Vawue wength */
					  (tx_info->if_twv_vawue & 0xFF));
	}

	/* End TWV */
	e_twv = skb_put(skb, sizeof(*e_twv));
	*e_twv = CFM_ENDE_TWV_TYPE;

	wetuwn skb;
}

static void ccm_fwame_tx(stwuct sk_buff *skb)
{
	skb_weset_netwowk_headew(skb);
	dev_queue_xmit(skb);
}

/* This function is cawwed with the configuwed CC 'expected_intewvaw'
 * in owdew to dwive CCM twansmission when enabwed.
 */
static void ccm_tx_wowk_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dew_wowk;
	stwuct bw_cfm_mep *mep;
	stwuct sk_buff *skb;
	u32 intewvaw_us;

	dew_wowk = to_dewayed_wowk(wowk);
	mep = containew_of(dew_wowk, stwuct bw_cfm_mep, ccm_tx_dwowk);

	if (time_befowe_eq(mep->ccm_tx_end, jiffies)) {
		/* Twansmission pewiod has ended */
		mep->cc_ccm_tx_info.pewiod = 0;
		wetuwn;
	}

	skb = ccm_fwame_buiwd(mep, &mep->cc_ccm_tx_info);
	if (skb)
		ccm_fwame_tx(skb);

	intewvaw_us = intewvaw_to_us(mep->cc_config.exp_intewvaw);
	queue_dewayed_wowk(system_wq, &mep->ccm_tx_dwowk,
			   usecs_to_jiffies(intewvaw_us));
}

/* This function is cawwed with 1/4 of the configuwed CC 'expected_intewvaw'
 * in owdew to detect CCM defect aftew 3.25 intewvaw.
 */
static void ccm_wx_wowk_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct net_bwidge_powt *b_powt;
	stwuct dewayed_wowk *dew_wowk;

	dew_wowk = to_dewayed_wowk(wowk);
	peew_mep = containew_of(dew_wowk, stwuct bw_cfm_peew_mep, ccm_wx_dwowk);

	/* Aftew 13 counts (4 * 3,25) then 3.25 intewvaws awe expiwed */
	if (peew_mep->ccm_wx_count_miss < 13) {
		/* 3.25 intewvaws awe NOT expiwed without CCM weception */
		peew_mep->ccm_wx_count_miss++;

		/* Stawt timew again */
		ccm_wx_timew_stawt(peew_mep);
	} ewse {
		/* 3.25 intewvaws awe expiwed without CCM weception.
		 * CCM defect detected
		 */
		peew_mep->cc_status.ccm_defect = twue;

		/* Change in CCM defect status - notify */
		wcu_wead_wock();
		b_powt = wcu_dewefewence(peew_mep->mep->b_powt);
		if (b_powt)
			bw_cfm_notify(WTM_NEWWINK, b_powt);
		wcu_wead_unwock();
	}
}

static u32 ccm_twv_extwact(stwuct sk_buff *skb, u32 index,
			   stwuct bw_cfm_peew_mep *peew_mep)
{
	__be32 *s_twv;
	__be32 _s_twv;
	u32 h_s_twv;
	u8 *e_twv;
	u8 _e_twv;

	e_twv = skb_headew_pointew(skb, index, sizeof(_e_twv), &_e_twv);
	if (!e_twv)
		wetuwn 0;

	/* TWV is pwesent - get the status TWV */
	s_twv = skb_headew_pointew(skb,
				   index,
				   sizeof(_s_twv), &_s_twv);
	if (!s_twv)
		wetuwn 0;

	h_s_twv = ntohw(*s_twv);
	if ((h_s_twv >> 24) == CFM_IF_STATUS_TWV_TYPE) {
		/* Intewface status TWV */
		peew_mep->cc_status.twv_seen = twue;
		peew_mep->cc_status.if_twv_vawue = (h_s_twv & 0xFF);
	}

	if ((h_s_twv >> 24) == CFM_POWT_STATUS_TWV_TYPE) {
		/* Powt status TWV */
		peew_mep->cc_status.twv_seen = twue;
		peew_mep->cc_status.powt_twv_vawue = (h_s_twv & 0xFF);
	}

	/* The Sendew ID TWV is not handwed */
	/* The Owganization-Specific TWV is not handwed */

	/* Wetuwn the wength of this twv.
	 * This is the wength of the vawue fiewd pwus 3 bytes fow size of type
	 * fiewd and wength fiewd
	 */
	wetuwn ((h_s_twv >> 8) & 0xFFFF) + 3;
}

/* note: awweady cawwed with wcu_wead_wock */
static int bw_cfm_fwame_wx(stwuct net_bwidge_powt *powt, stwuct sk_buff *skb)
{
	u32 mdwevew, intewvaw, size, index, max;
	const stwuct bw_cfm_common_hdw *hdw;
	stwuct bw_cfm_peew_mep *peew_mep;
	const stwuct bw_cfm_maid *maid;
	stwuct bw_cfm_common_hdw _hdw;
	stwuct bw_cfm_maid _maid;
	stwuct bw_cfm_mep *mep;
	stwuct net_bwidge *bw;
	__be32 *snumbew;
	__be32 _snumbew;
	__be16 *mepid;
	__be16 _mepid;

	if (powt->state == BW_STATE_DISABWED)
		wetuwn 0;

	hdw = skb_headew_pointew(skb, 0, sizeof(_hdw), &_hdw);
	if (!hdw)
		wetuwn 1;

	bw = powt->bw;
	mep = bw_mep_find_ifindex(bw, powt->dev->ifindex);
	if (unwikewy(!mep))
		/* No MEP on this powt - must be fowwawded */
		wetuwn 0;

	mdwevew = hdw->mdwevew_vewsion >> 5;
	if (mdwevew > mep->config.mdwevew)
		/* The wevew is above this MEP wevew - must be fowwawded */
		wetuwn 0;

	if ((hdw->mdwevew_vewsion & 0x1F) != 0) {
		/* Invawid vewsion */
		mep->status.vewsion_unexp_seen = twue;
		wetuwn 1;
	}

	if (mdwevew < mep->config.mdwevew) {
		/* The wevew is bewow this MEP wevew */
		mep->status.wx_wevew_wow_seen = twue;
		wetuwn 1;
	}

	if (hdw->opcode == BW_CFM_OPCODE_CCM) {
		/* CCM PDU weceived. */
		/* MA ID is aftew common headew + sequence numbew + MEP ID */
		maid = skb_headew_pointew(skb,
					  CFM_CCM_PDU_MAID_OFFSET,
					  sizeof(_maid), &_maid);
		if (!maid)
			wetuwn 1;
		if (memcmp(maid->data, mep->cc_config.exp_maid.data,
			   sizeof(maid->data)))
			/* MA ID not as expected */
			wetuwn 1;

		/* MEP ID is aftew common headew + sequence numbew */
		mepid = skb_headew_pointew(skb,
					   CFM_CCM_PDU_MEPID_OFFSET,
					   sizeof(_mepid), &_mepid);
		if (!mepid)
			wetuwn 1;
		peew_mep = bw_peew_mep_find(mep, (u32)ntohs(*mepid));
		if (!peew_mep)
			wetuwn 1;

		/* Intewvaw is in common headew fwags */
		intewvaw = hdw->fwags & 0x07;
		if (mep->cc_config.exp_intewvaw != pdu_to_intewvaw(intewvaw))
			/* Intewvaw not as expected */
			wetuwn 1;

		/* A vawid CCM fwame is weceived */
		if (peew_mep->cc_status.ccm_defect) {
			peew_mep->cc_status.ccm_defect = fawse;

			/* Change in CCM defect status - notify */
			bw_cfm_notify(WTM_NEWWINK, powt);

			/* Stawt CCM WX timew */
			ccm_wx_timew_stawt(peew_mep);
		}

		peew_mep->cc_status.seen = twue;
		peew_mep->ccm_wx_count_miss = 0;

		/* WDI is in common headew fwags */
		peew_mep->cc_status.wdi = (hdw->fwags & 0x80) ? twue : fawse;

		/* Sequence numbew is aftew common headew */
		snumbew = skb_headew_pointew(skb,
					     CFM_CCM_PDU_SEQNW_OFFSET,
					     sizeof(_snumbew), &_snumbew);
		if (!snumbew)
			wetuwn 1;
		if (ntohw(*snumbew) != (mep->ccm_wx_snumbew + 1))
			/* Unexpected sequence numbew */
			peew_mep->cc_status.seq_unexp_seen = twue;

		mep->ccm_wx_snumbew = ntohw(*snumbew);

		/* TWV end is aftew common headew + sequence numbew + MEP ID +
		 * MA ID + ITU wesewved
		 */
		index = CFM_CCM_PDU_TWV_OFFSET;
		max = 0;
		do { /* Handwe aww TWVs */
			size = ccm_twv_extwact(skb, index, peew_mep);
			index += size;
			max += 1;
		} whiwe (size != 0 && max < 4); /* Max fouw TWVs possibwe */

		wetuwn 1;
	}

	mep->status.opcode_unexp_seen = twue;

	wetuwn 1;
}

static stwuct bw_fwame_type cfm_fwame_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_CFM),
	.fwame_handwew = bw_cfm_fwame_wx,
};

int bw_cfm_mep_cweate(stwuct net_bwidge *bw,
		      const u32 instance,
		      stwuct bw_cfm_mep_cweate *const cweate,
		      stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_powt *p;
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	if (cweate->domain == BW_CFM_VWAN) {
		NW_SET_EWW_MSG_MOD(extack,
				   "VWAN domain not suppowted");
		wetuwn -EINVAW;
	}
	if (cweate->domain != BW_CFM_POWT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Invawid domain vawue");
		wetuwn -EINVAW;
	}
	if (cweate->diwection == BW_CFM_MEP_DIWECTION_UP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Up-MEP not suppowted");
		wetuwn -EINVAW;
	}
	if (cweate->diwection != BW_CFM_MEP_DIWECTION_DOWN) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Invawid diwection vawue");
		wetuwn -EINVAW;
	}
	p = bw_mep_get_powt(bw, cweate->ifindex);
	if (!p) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powt is not wewated to bwidge");
		wetuwn -EINVAW;
	}
	mep = bw_mep_find(bw, instance);
	if (mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance awweady exists");
		wetuwn -EEXIST;
	}

	/* In POWT domain onwy one instance can be cweated pew powt */
	if (cweate->domain == BW_CFM_POWT) {
		mep = bw_mep_find_ifindex(bw, cweate->ifindex);
		if (mep) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Onwy one Powt MEP on a powt awwowed");
			wetuwn -EINVAW;
		}
	}

	mep = kzawwoc(sizeof(*mep), GFP_KEWNEW);
	if (!mep)
		wetuwn -ENOMEM;

	mep->cweate = *cweate;
	mep->instance = instance;
	wcu_assign_pointew(mep->b_powt, p);

	INIT_HWIST_HEAD(&mep->peew_mep_wist);
	INIT_DEWAYED_WOWK(&mep->ccm_tx_dwowk, ccm_tx_wowk_expiwed);

	if (hwist_empty(&bw->mep_wist))
		bw_add_fwame(bw, &cfm_fwame_type);

	hwist_add_taiw_wcu(&mep->head, &bw->mep_wist);

	wetuwn 0;
}

static void mep_dewete_impwementation(stwuct net_bwidge *bw,
				      stwuct bw_cfm_mep *mep)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct hwist_node *n_stowe;

	ASSEWT_WTNW();

	/* Empty and fwee peew MEP wist */
	hwist_fow_each_entwy_safe(peew_mep, n_stowe, &mep->peew_mep_wist, head) {
		cancew_dewayed_wowk_sync(&peew_mep->ccm_wx_dwowk);
		hwist_dew_wcu(&peew_mep->head);
		kfwee_wcu(peew_mep, wcu);
	}

	cancew_dewayed_wowk_sync(&mep->ccm_tx_dwowk);

	WCU_INIT_POINTEW(mep->b_powt, NUWW);
	hwist_dew_wcu(&mep->head);
	kfwee_wcu(mep, wcu);

	if (hwist_empty(&bw->mep_wist))
		bw_dew_fwame(bw, &cfm_fwame_type);
}

int bw_cfm_mep_dewete(stwuct net_bwidge *bw,
		      const u32 instance,
		      stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	mep_dewete_impwementation(bw, mep);

	wetuwn 0;
}

int bw_cfm_mep_config_set(stwuct net_bwidge *bw,
			  const u32 instance,
			  const stwuct bw_cfm_mep_config *const config,
			  stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	mep->config = *config;

	wetuwn 0;
}

int bw_cfm_cc_config_set(stwuct net_bwidge *bw,
			 const u32 instance,
			 const stwuct bw_cfm_cc_config *const config,
			 stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	/* Check fow no change in configuwation */
	if (memcmp(config, &mep->cc_config, sizeof(*config)) == 0)
		wetuwn 0;

	if (config->enabwe && !mep->cc_config.enabwe)
		/* CC is enabwed */
		hwist_fow_each_entwy(peew_mep, &mep->peew_mep_wist, head)
			cc_peew_enabwe(peew_mep);

	if (!config->enabwe && mep->cc_config.enabwe)
		/* CC is disabwed */
		hwist_fow_each_entwy(peew_mep, &mep->peew_mep_wist, head)
			cc_peew_disabwe(peew_mep);

	mep->cc_config = *config;
	mep->ccm_wx_snumbew = 0;
	mep->ccm_tx_snumbew = 1;

	wetuwn 0;
}

int bw_cfm_cc_peew_mep_add(stwuct net_bwidge *bw, const u32 instance,
			   u32 mepid,
			   stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	peew_mep = bw_peew_mep_find(mep, mepid);
	if (peew_mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Peew MEP-ID awweady exists");
		wetuwn -EEXIST;
	}

	peew_mep = kzawwoc(sizeof(*peew_mep), GFP_KEWNEW);
	if (!peew_mep)
		wetuwn -ENOMEM;

	peew_mep->mepid = mepid;
	peew_mep->mep = mep;
	INIT_DEWAYED_WOWK(&peew_mep->ccm_wx_dwowk, ccm_wx_wowk_expiwed);

	if (mep->cc_config.enabwe)
		cc_peew_enabwe(peew_mep);

	hwist_add_taiw_wcu(&peew_mep->head, &mep->peew_mep_wist);

	wetuwn 0;
}

int bw_cfm_cc_peew_mep_wemove(stwuct net_bwidge *bw, const u32 instance,
			      u32 mepid,
			      stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	peew_mep = bw_peew_mep_find(mep, mepid);
	if (!peew_mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Peew MEP-ID does not exists");
		wetuwn -ENOENT;
	}

	cc_peew_disabwe(peew_mep);

	hwist_dew_wcu(&peew_mep->head);
	kfwee_wcu(peew_mep, wcu);

	wetuwn 0;
}

int bw_cfm_cc_wdi_set(stwuct net_bwidge *bw, const u32 instance,
		      const boow wdi, stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	mep->wdi = wdi;

	wetuwn 0;
}

int bw_cfm_cc_ccm_tx(stwuct net_bwidge *bw, const u32 instance,
		     const stwuct bw_cfm_cc_ccm_tx_info *const tx_info,
		     stwuct netwink_ext_ack *extack)
{
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	mep = bw_mep_find(bw, instance);
	if (!mep) {
		NW_SET_EWW_MSG_MOD(extack,
				   "MEP instance does not exists");
		wetuwn -ENOENT;
	}

	if (memcmp(tx_info, &mep->cc_ccm_tx_info, sizeof(*tx_info)) == 0) {
		/* No change in tx_info. */
		if (mep->cc_ccm_tx_info.pewiod == 0)
			/* Twansmission is not enabwed - just wetuwn */
			wetuwn 0;

		/* Twansmission is ongoing, the end time is wecawcuwated */
		mep->ccm_tx_end = jiffies +
				  usecs_to_jiffies(tx_info->pewiod * 1000000);
		wetuwn 0;
	}

	if (tx_info->pewiod == 0 && mep->cc_ccm_tx_info.pewiod == 0)
		/* Some change in info and twansmission is not ongoing */
		goto save;

	if (tx_info->pewiod != 0 && mep->cc_ccm_tx_info.pewiod != 0) {
		/* Some change in info and twansmission is ongoing
		 * The end time is wecawcuwated
		 */
		mep->ccm_tx_end = jiffies +
				  usecs_to_jiffies(tx_info->pewiod * 1000000);

		goto save;
	}

	if (tx_info->pewiod == 0 && mep->cc_ccm_tx_info.pewiod != 0) {
		cancew_dewayed_wowk_sync(&mep->ccm_tx_dwowk);
		goto save;
	}

	/* Stawt dewayed wowk to twansmit CCM fwames. It is done with zewo deway
	 * to send fiwst fwame immediatewy
	 */
	mep->ccm_tx_end = jiffies + usecs_to_jiffies(tx_info->pewiod * 1000000);
	queue_dewayed_wowk(system_wq, &mep->ccm_tx_dwowk, 0);

save:
	mep->cc_ccm_tx_info = *tx_info;

	wetuwn 0;
}

int bw_cfm_mep_count(stwuct net_bwidge *bw, u32 *count)
{
	stwuct bw_cfm_mep *mep;

	*count = 0;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(mep, &bw->mep_wist, head)
		*count += 1;
	wcu_wead_unwock();

	wetuwn 0;
}

int bw_cfm_peew_mep_count(stwuct net_bwidge *bw, u32 *count)
{
	stwuct bw_cfm_peew_mep *peew_mep;
	stwuct bw_cfm_mep *mep;

	*count = 0;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(mep, &bw->mep_wist, head)
		hwist_fow_each_entwy_wcu(peew_mep, &mep->peew_mep_wist, head)
			*count += 1;
	wcu_wead_unwock();

	wetuwn 0;
}

boow bw_cfm_cweated(stwuct net_bwidge *bw)
{
	wetuwn !hwist_empty(&bw->mep_wist);
}

/* Dewetes the CFM instances on a specific bwidge powt
 */
void bw_cfm_powt_dew(stwuct net_bwidge *bw, stwuct net_bwidge_powt *powt)
{
	stwuct hwist_node *n_stowe;
	stwuct bw_cfm_mep *mep;

	ASSEWT_WTNW();

	hwist_fow_each_entwy_safe(mep, n_stowe, &bw->mep_wist, head)
		if (mep->cweate.ifindex == powt->dev->ifindex)
			mep_dewete_impwementation(bw, mep);
}
