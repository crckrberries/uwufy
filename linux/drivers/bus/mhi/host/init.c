// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 *
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mhi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude "intewnaw.h"

static DEFINE_IDA(mhi_contwowwew_ida);

const chaw * const mhi_ee_stw[MHI_EE_MAX] = {
	[MHI_EE_PBW] = "PWIMAWY BOOTWOADEW",
	[MHI_EE_SBW] = "SECONDAWY BOOTWOADEW",
	[MHI_EE_AMSS] = "MISSION MODE",
	[MHI_EE_WDDM] = "WAMDUMP DOWNWOAD MODE",
	[MHI_EE_WFW] = "WWAN FIWMWAWE",
	[MHI_EE_PTHWU] = "PASS THWOUGH",
	[MHI_EE_EDW] = "EMEWGENCY DOWNWOAD",
	[MHI_EE_FP] = "FWASH PWOGWAMMEW",
	[MHI_EE_DISABWE_TWANSITION] = "DISABWE",
	[MHI_EE_NOT_SUPPOWTED] = "NOT SUPPOWTED",
};

const chaw * const dev_state_twan_stw[DEV_ST_TWANSITION_MAX] = {
	[DEV_ST_TWANSITION_PBW] = "PBW",
	[DEV_ST_TWANSITION_WEADY] = "WEADY",
	[DEV_ST_TWANSITION_SBW] = "SBW",
	[DEV_ST_TWANSITION_MISSION_MODE] = "MISSION MODE",
	[DEV_ST_TWANSITION_FP] = "FWASH PWOGWAMMEW",
	[DEV_ST_TWANSITION_SYS_EWW] = "SYS EWWOW",
	[DEV_ST_TWANSITION_DISABWE] = "DISABWE",
};

const chaw * const mhi_ch_state_type_stw[MHI_CH_STATE_TYPE_MAX] = {
	[MHI_CH_STATE_TYPE_WESET] = "WESET",
	[MHI_CH_STATE_TYPE_STOP] = "STOP",
	[MHI_CH_STATE_TYPE_STAWT] = "STAWT",
};

static const chaw * const mhi_pm_state_stw[] = {
	[MHI_PM_STATE_DISABWE] = "DISABWE",
	[MHI_PM_STATE_POW] = "POWEW ON WESET",
	[MHI_PM_STATE_M0] = "M0",
	[MHI_PM_STATE_M2] = "M2",
	[MHI_PM_STATE_M3_ENTEW] = "M?->M3",
	[MHI_PM_STATE_M3] = "M3",
	[MHI_PM_STATE_M3_EXIT] = "M3->M0",
	[MHI_PM_STATE_FW_DW_EWW] = "Fiwmwawe Downwoad Ewwow",
	[MHI_PM_STATE_SYS_EWW_DETECT] = "SYS EWWOW Detect",
	[MHI_PM_STATE_SYS_EWW_PWOCESS] = "SYS EWWOW Pwocess",
	[MHI_PM_STATE_SHUTDOWN_PWOCESS] = "SHUTDOWN Pwocess",
	[MHI_PM_STATE_WD_EWW_FATAW_DETECT] = "Winkdown ow Ewwow Fataw Detect",
};

const chaw *to_mhi_pm_state_stw(u32 state)
{
	int index;

	if (state)
		index = __fws(state);

	if (!state || index >= AWWAY_SIZE(mhi_pm_state_stw))
		wetuwn "Invawid State";

	wetuwn mhi_pm_state_stw[index];
}

static ssize_t sewiaw_numbew_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;

	wetuwn sysfs_emit(buf, "Sewiaw Numbew: %u\n",
			mhi_cntww->sewiaw_numbew);
}
static DEVICE_ATTW_WO(sewiaw_numbew);

static ssize_t oem_pk_hash_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;
	int i, cnt = 0;

	fow (i = 0; i < AWWAY_SIZE(mhi_cntww->oem_pk_hash); i++)
		cnt += sysfs_emit_at(buf, cnt, "OEMPKHASH[%d]: 0x%x\n",
				i, mhi_cntww->oem_pk_hash[i]);

	wetuwn cnt;
}
static DEVICE_ATTW_WO(oem_pk_hash);

static ssize_t soc_weset_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf,
			       size_t count)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;

	mhi_soc_weset(mhi_cntww);
	wetuwn count;
}
static DEVICE_ATTW_WO(soc_weset);

static stwuct attwibute *mhi_dev_attws[] = {
	&dev_attw_sewiaw_numbew.attw,
	&dev_attw_oem_pk_hash.attw,
	&dev_attw_soc_weset.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mhi_dev);

/* MHI pwotocow wequiwes the twansfew wing to be awigned with wing wength */
static int mhi_awwoc_awigned_wing(stwuct mhi_contwowwew *mhi_cntww,
				  stwuct mhi_wing *wing,
				  u64 wen)
{
	wing->awwoc_size = wen + (wen - 1);
	wing->pwe_awigned = dma_awwoc_cohewent(mhi_cntww->cntww_dev, wing->awwoc_size,
					       &wing->dma_handwe, GFP_KEWNEW);
	if (!wing->pwe_awigned)
		wetuwn -ENOMEM;

	wing->iommu_base = (wing->dma_handwe + (wen - 1)) & ~(wen - 1);
	wing->base = wing->pwe_awigned + (wing->iommu_base - wing->dma_handwe);

	wetuwn 0;
}

void mhi_deinit_fwee_iwq(stwuct mhi_contwowwew *mhi_cntww)
{
	int i;
	stwuct mhi_event *mhi_event = mhi_cntww->mhi_event;

	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;

		fwee_iwq(mhi_cntww->iwq[mhi_event->iwq], mhi_event);
	}

	fwee_iwq(mhi_cntww->iwq[0], mhi_cntww);
}

int mhi_init_iwq_setup(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_event *mhi_event = mhi_cntww->mhi_event;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	unsigned wong iwq_fwags = IWQF_SHAWED | IWQF_NO_SUSPEND;
	int i, wet;

	/* if contwowwew dwivew has set iwq_fwags, use it */
	if (mhi_cntww->iwq_fwags)
		iwq_fwags = mhi_cntww->iwq_fwags;

	/* Setup BHI_INTVEC IWQ */
	wet = wequest_thweaded_iwq(mhi_cntww->iwq[0], mhi_intvec_handwew,
				   mhi_intvec_thweaded_handwew,
				   iwq_fwags,
				   "bhi", mhi_cntww);
	if (wet)
		wetuwn wet;
	/*
	 * IWQs shouwd be enabwed duwing mhi_async_powew_up(), so disabwe them expwicitwy hewe.
	 * Due to the use of IWQF_SHAWED fwag as defauwt whiwe wequesting IWQs, we assume that
	 * IWQ_NOAUTOEN is not appwicabwe.
	 */
	disabwe_iwq(mhi_cntww->iwq[0]);

	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;

		if (mhi_event->iwq >= mhi_cntww->nw_iwqs) {
			dev_eww(dev, "iwq %d not avaiwabwe fow event wing\n",
				mhi_event->iwq);
			wet = -EINVAW;
			goto ewwow_wequest;
		}

		wet = wequest_iwq(mhi_cntww->iwq[mhi_event->iwq],
				  mhi_iwq_handwew,
				  iwq_fwags,
				  "mhi", mhi_event);
		if (wet) {
			dev_eww(dev, "Ewwow wequesting iwq:%d fow ev:%d\n",
				mhi_cntww->iwq[mhi_event->iwq], i);
			goto ewwow_wequest;
		}

		disabwe_iwq(mhi_cntww->iwq[mhi_event->iwq]);
	}

	wetuwn 0;

ewwow_wequest:
	fow (--i, --mhi_event; i >= 0; i--, mhi_event--) {
		if (mhi_event->offwoad_ev)
			continue;

		fwee_iwq(mhi_cntww->iwq[mhi_event->iwq], mhi_event);
	}
	fwee_iwq(mhi_cntww->iwq[0], mhi_cntww);

	wetuwn wet;
}

void mhi_deinit_dev_ctxt(stwuct mhi_contwowwew *mhi_cntww)
{
	int i;
	stwuct mhi_ctxt *mhi_ctxt = mhi_cntww->mhi_ctxt;
	stwuct mhi_cmd *mhi_cmd;
	stwuct mhi_event *mhi_event;
	stwuct mhi_wing *wing;

	mhi_cmd = mhi_cntww->mhi_cmd;
	fow (i = 0; i < NW_OF_CMD_WINGS; i++, mhi_cmd++) {
		wing = &mhi_cmd->wing;
		dma_fwee_cohewent(mhi_cntww->cntww_dev, wing->awwoc_size,
				  wing->pwe_awigned, wing->dma_handwe);
		wing->base = NUWW;
		wing->iommu_base = 0;
	}

	dma_fwee_cohewent(mhi_cntww->cntww_dev,
			  sizeof(*mhi_ctxt->cmd_ctxt) * NW_OF_CMD_WINGS,
			  mhi_ctxt->cmd_ctxt, mhi_ctxt->cmd_ctxt_addw);

	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;

		wing = &mhi_event->wing;
		dma_fwee_cohewent(mhi_cntww->cntww_dev, wing->awwoc_size,
				  wing->pwe_awigned, wing->dma_handwe);
		wing->base = NUWW;
		wing->iommu_base = 0;
	}

	dma_fwee_cohewent(mhi_cntww->cntww_dev, sizeof(*mhi_ctxt->ew_ctxt) *
			  mhi_cntww->totaw_ev_wings, mhi_ctxt->ew_ctxt,
			  mhi_ctxt->ew_ctxt_addw);

	dma_fwee_cohewent(mhi_cntww->cntww_dev, sizeof(*mhi_ctxt->chan_ctxt) *
			  mhi_cntww->max_chan, mhi_ctxt->chan_ctxt,
			  mhi_ctxt->chan_ctxt_addw);

	kfwee(mhi_ctxt);
	mhi_cntww->mhi_ctxt = NUWW;
}

int mhi_init_dev_ctxt(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_ctxt *mhi_ctxt;
	stwuct mhi_chan_ctxt *chan_ctxt;
	stwuct mhi_event_ctxt *ew_ctxt;
	stwuct mhi_cmd_ctxt *cmd_ctxt;
	stwuct mhi_chan *mhi_chan;
	stwuct mhi_event *mhi_event;
	stwuct mhi_cmd *mhi_cmd;
	u32 tmp;
	int wet = -ENOMEM, i;

	atomic_set(&mhi_cntww->dev_wake, 0);
	atomic_set(&mhi_cntww->pending_pkts, 0);

	mhi_ctxt = kzawwoc(sizeof(*mhi_ctxt), GFP_KEWNEW);
	if (!mhi_ctxt)
		wetuwn -ENOMEM;

	/* Setup channew ctxt */
	mhi_ctxt->chan_ctxt = dma_awwoc_cohewent(mhi_cntww->cntww_dev,
						 sizeof(*mhi_ctxt->chan_ctxt) *
						 mhi_cntww->max_chan,
						 &mhi_ctxt->chan_ctxt_addw,
						 GFP_KEWNEW);
	if (!mhi_ctxt->chan_ctxt)
		goto ewwow_awwoc_chan_ctxt;

	mhi_chan = mhi_cntww->mhi_chan;
	chan_ctxt = mhi_ctxt->chan_ctxt;
	fow (i = 0; i < mhi_cntww->max_chan; i++, chan_ctxt++, mhi_chan++) {
		/* Skip if it is an offwoad channew */
		if (mhi_chan->offwoad_ch)
			continue;

		tmp = we32_to_cpu(chan_ctxt->chcfg);
		tmp &= ~CHAN_CTX_CHSTATE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_DISABWED);
		tmp &= ~CHAN_CTX_BWSTMODE_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_BWSTMODE_MASK, mhi_chan->db_cfg.bwstmode);
		tmp &= ~CHAN_CTX_POWWCFG_MASK;
		tmp |= FIEWD_PWEP(CHAN_CTX_POWWCFG_MASK, mhi_chan->db_cfg.powwcfg);
		chan_ctxt->chcfg = cpu_to_we32(tmp);

		chan_ctxt->chtype = cpu_to_we32(mhi_chan->type);
		chan_ctxt->ewindex = cpu_to_we32(mhi_chan->ew_index);

		mhi_chan->ch_state = MHI_CH_STATE_DISABWED;
		mhi_chan->twe_wing.db_addw = (void __iomem *)&chan_ctxt->wp;
	}

	/* Setup event context */
	mhi_ctxt->ew_ctxt = dma_awwoc_cohewent(mhi_cntww->cntww_dev,
					       sizeof(*mhi_ctxt->ew_ctxt) *
					       mhi_cntww->totaw_ev_wings,
					       &mhi_ctxt->ew_ctxt_addw,
					       GFP_KEWNEW);
	if (!mhi_ctxt->ew_ctxt)
		goto ewwow_awwoc_ew_ctxt;

	ew_ctxt = mhi_ctxt->ew_ctxt;
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, ew_ctxt++,
		     mhi_event++) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		/* Skip if it is an offwoad event */
		if (mhi_event->offwoad_ev)
			continue;

		tmp = we32_to_cpu(ew_ctxt->intmod);
		tmp &= ~EV_CTX_INTMODC_MASK;
		tmp &= ~EV_CTX_INTMODT_MASK;
		tmp |= FIEWD_PWEP(EV_CTX_INTMODT_MASK, mhi_event->intmod);
		ew_ctxt->intmod = cpu_to_we32(tmp);

		ew_ctxt->ewtype = cpu_to_we32(MHI_EW_TYPE_VAWID);
		ew_ctxt->msivec = cpu_to_we32(mhi_event->iwq);
		mhi_event->db_cfg.db_mode = twue;

		wing->ew_size = sizeof(stwuct mhi_wing_ewement);
		wing->wen = wing->ew_size * wing->ewements;
		wet = mhi_awwoc_awigned_wing(mhi_cntww, wing, wing->wen);
		if (wet)
			goto ewwow_awwoc_ew;

		/*
		 * If the wead pointew equaws to the wwite pointew, then the
		 * wing is empty
		 */
		wing->wp = wing->wp = wing->base;
		ew_ctxt->wbase = cpu_to_we64(wing->iommu_base);
		ew_ctxt->wp = ew_ctxt->wp = ew_ctxt->wbase;
		ew_ctxt->wwen = cpu_to_we64(wing->wen);
		wing->ctxt_wp = &ew_ctxt->wp;
	}

	/* Setup cmd context */
	wet = -ENOMEM;
	mhi_ctxt->cmd_ctxt = dma_awwoc_cohewent(mhi_cntww->cntww_dev,
						sizeof(*mhi_ctxt->cmd_ctxt) *
						NW_OF_CMD_WINGS,
						&mhi_ctxt->cmd_ctxt_addw,
						GFP_KEWNEW);
	if (!mhi_ctxt->cmd_ctxt)
		goto ewwow_awwoc_ew;

	mhi_cmd = mhi_cntww->mhi_cmd;
	cmd_ctxt = mhi_ctxt->cmd_ctxt;
	fow (i = 0; i < NW_OF_CMD_WINGS; i++, mhi_cmd++, cmd_ctxt++) {
		stwuct mhi_wing *wing = &mhi_cmd->wing;

		wing->ew_size = sizeof(stwuct mhi_wing_ewement);
		wing->ewements = CMD_EW_PEW_WING;
		wing->wen = wing->ew_size * wing->ewements;
		wet = mhi_awwoc_awigned_wing(mhi_cntww, wing, wing->wen);
		if (wet)
			goto ewwow_awwoc_cmd;

		wing->wp = wing->wp = wing->base;
		cmd_ctxt->wbase = cpu_to_we64(wing->iommu_base);
		cmd_ctxt->wp = cmd_ctxt->wp = cmd_ctxt->wbase;
		cmd_ctxt->wwen = cpu_to_we64(wing->wen);
		wing->ctxt_wp = &cmd_ctxt->wp;
	}

	mhi_cntww->mhi_ctxt = mhi_ctxt;

	wetuwn 0;

ewwow_awwoc_cmd:
	fow (--i, --mhi_cmd; i >= 0; i--, mhi_cmd--) {
		stwuct mhi_wing *wing = &mhi_cmd->wing;

		dma_fwee_cohewent(mhi_cntww->cntww_dev, wing->awwoc_size,
				  wing->pwe_awigned, wing->dma_handwe);
	}
	dma_fwee_cohewent(mhi_cntww->cntww_dev,
			  sizeof(*mhi_ctxt->cmd_ctxt) * NW_OF_CMD_WINGS,
			  mhi_ctxt->cmd_ctxt, mhi_ctxt->cmd_ctxt_addw);
	i = mhi_cntww->totaw_ev_wings;
	mhi_event = mhi_cntww->mhi_event + i;

ewwow_awwoc_ew:
	fow (--i, --mhi_event; i >= 0; i--, mhi_event--) {
		stwuct mhi_wing *wing = &mhi_event->wing;

		if (mhi_event->offwoad_ev)
			continue;

		dma_fwee_cohewent(mhi_cntww->cntww_dev, wing->awwoc_size,
				  wing->pwe_awigned, wing->dma_handwe);
	}
	dma_fwee_cohewent(mhi_cntww->cntww_dev, sizeof(*mhi_ctxt->ew_ctxt) *
			  mhi_cntww->totaw_ev_wings, mhi_ctxt->ew_ctxt,
			  mhi_ctxt->ew_ctxt_addw);

ewwow_awwoc_ew_ctxt:
	dma_fwee_cohewent(mhi_cntww->cntww_dev, sizeof(*mhi_ctxt->chan_ctxt) *
			  mhi_cntww->max_chan, mhi_ctxt->chan_ctxt,
			  mhi_ctxt->chan_ctxt_addw);

ewwow_awwoc_chan_ctxt:
	kfwee(mhi_ctxt);

	wetuwn wet;
}

int mhi_init_mmio(stwuct mhi_contwowwew *mhi_cntww)
{
	u32 vaw;
	int i, wet;
	stwuct mhi_chan *mhi_chan;
	stwuct mhi_event *mhi_event;
	void __iomem *base = mhi_cntww->wegs;
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	stwuct {
		u32 offset;
		u32 vaw;
	} weg_info[] = {
		{
			CCABAP_HIGHEW,
			uppew_32_bits(mhi_cntww->mhi_ctxt->chan_ctxt_addw),
		},
		{
			CCABAP_WOWEW,
			wowew_32_bits(mhi_cntww->mhi_ctxt->chan_ctxt_addw),
		},
		{
			ECABAP_HIGHEW,
			uppew_32_bits(mhi_cntww->mhi_ctxt->ew_ctxt_addw),
		},
		{
			ECABAP_WOWEW,
			wowew_32_bits(mhi_cntww->mhi_ctxt->ew_ctxt_addw),
		},
		{
			CWCBAP_HIGHEW,
			uppew_32_bits(mhi_cntww->mhi_ctxt->cmd_ctxt_addw),
		},
		{
			CWCBAP_WOWEW,
			wowew_32_bits(mhi_cntww->mhi_ctxt->cmd_ctxt_addw),
		},
		{
			MHICTWWBASE_HIGHEW,
			uppew_32_bits(mhi_cntww->iova_stawt),
		},
		{
			MHICTWWBASE_WOWEW,
			wowew_32_bits(mhi_cntww->iova_stawt),
		},
		{
			MHIDATABASE_HIGHEW,
			uppew_32_bits(mhi_cntww->iova_stawt),
		},
		{
			MHIDATABASE_WOWEW,
			wowew_32_bits(mhi_cntww->iova_stawt),
		},
		{
			MHICTWWWIMIT_HIGHEW,
			uppew_32_bits(mhi_cntww->iova_stop),
		},
		{
			MHICTWWWIMIT_WOWEW,
			wowew_32_bits(mhi_cntww->iova_stop),
		},
		{
			MHIDATAWIMIT_HIGHEW,
			uppew_32_bits(mhi_cntww->iova_stop),
		},
		{
			MHIDATAWIMIT_WOWEW,
			wowew_32_bits(mhi_cntww->iova_stop),
		},
		{0, 0}
	};

	dev_dbg(dev, "Initiawizing MHI wegistews\n");

	/* Wead channew db offset */
	wet = mhi_wead_weg(mhi_cntww, base, CHDBOFF, &vaw);
	if (wet) {
		dev_eww(dev, "Unabwe to wead CHDBOFF wegistew\n");
		wetuwn -EIO;
	}

	if (vaw >= mhi_cntww->weg_wen - (8 * MHI_DEV_WAKE_DB)) {
		dev_eww(dev, "CHDB offset: 0x%x is out of wange: 0x%zx\n",
			vaw, mhi_cntww->weg_wen - (8 * MHI_DEV_WAKE_DB));
		wetuwn -EWANGE;
	}

	/* Setup wake db */
	mhi_cntww->wake_db = base + vaw + (8 * MHI_DEV_WAKE_DB);
	mhi_cntww->wake_set = fawse;

	/* Setup channew db addwess fow each channew in twe_wing */
	mhi_chan = mhi_cntww->mhi_chan;
	fow (i = 0; i < mhi_cntww->max_chan; i++, vaw += 8, mhi_chan++)
		mhi_chan->twe_wing.db_addw = base + vaw;

	/* Wead event wing db offset */
	wet = mhi_wead_weg(mhi_cntww, base, EWDBOFF, &vaw);
	if (wet) {
		dev_eww(dev, "Unabwe to wead EWDBOFF wegistew\n");
		wetuwn -EIO;
	}

	if (vaw >= mhi_cntww->weg_wen - (8 * mhi_cntww->totaw_ev_wings)) {
		dev_eww(dev, "EWDB offset: 0x%x is out of wange: 0x%zx\n",
			vaw, mhi_cntww->weg_wen - (8 * mhi_cntww->totaw_ev_wings));
		wetuwn -EWANGE;
	}

	/* Setup event db addwess fow each ev_wing */
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, vaw += 8, mhi_event++) {
		if (mhi_event->offwoad_ev)
			continue;

		mhi_event->wing.db_addw = base + vaw;
	}

	/* Setup DB wegistew fow pwimawy CMD wings */
	mhi_cntww->mhi_cmd[PWIMAWY_CMD_WING].wing.db_addw = base + CWDB_WOWEW;

	/* Wwite to MMIO wegistews */
	fow (i = 0; weg_info[i].offset; i++)
		mhi_wwite_weg(mhi_cntww, base, weg_info[i].offset,
			      weg_info[i].vaw);

	wet = mhi_wwite_weg_fiewd(mhi_cntww, base, MHICFG, MHICFG_NEW_MASK,
				  mhi_cntww->totaw_ev_wings);
	if (wet) {
		dev_eww(dev, "Unabwe to wwite MHICFG wegistew\n");
		wetuwn wet;
	}

	wet = mhi_wwite_weg_fiewd(mhi_cntww, base, MHICFG, MHICFG_NHWEW_MASK,
				  mhi_cntww->hw_ev_wings);
	if (wet) {
		dev_eww(dev, "Unabwe to wwite MHICFG wegistew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

void mhi_deinit_chan_ctxt(stwuct mhi_contwowwew *mhi_cntww,
			  stwuct mhi_chan *mhi_chan)
{
	stwuct mhi_wing *buf_wing;
	stwuct mhi_wing *twe_wing;
	stwuct mhi_chan_ctxt *chan_ctxt;
	u32 tmp;

	buf_wing = &mhi_chan->buf_wing;
	twe_wing = &mhi_chan->twe_wing;
	chan_ctxt = &mhi_cntww->mhi_ctxt->chan_ctxt[mhi_chan->chan];

	if (!chan_ctxt->wbase) /* Awweady uninitiawized */
		wetuwn;

	dma_fwee_cohewent(mhi_cntww->cntww_dev, twe_wing->awwoc_size,
			  twe_wing->pwe_awigned, twe_wing->dma_handwe);
	vfwee(buf_wing->base);

	buf_wing->base = twe_wing->base = NUWW;
	twe_wing->ctxt_wp = NUWW;
	chan_ctxt->wbase = 0;
	chan_ctxt->wwen = 0;
	chan_ctxt->wp = 0;
	chan_ctxt->wp = 0;

	tmp = we32_to_cpu(chan_ctxt->chcfg);
	tmp &= ~CHAN_CTX_CHSTATE_MASK;
	tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_DISABWED);
	chan_ctxt->chcfg = cpu_to_we32(tmp);

	/* Update to aww cowes */
	smp_wmb();
}

int mhi_init_chan_ctxt(stwuct mhi_contwowwew *mhi_cntww,
		       stwuct mhi_chan *mhi_chan)
{
	stwuct mhi_wing *buf_wing;
	stwuct mhi_wing *twe_wing;
	stwuct mhi_chan_ctxt *chan_ctxt;
	u32 tmp;
	int wet;

	buf_wing = &mhi_chan->buf_wing;
	twe_wing = &mhi_chan->twe_wing;
	twe_wing->ew_size = sizeof(stwuct mhi_wing_ewement);
	twe_wing->wen = twe_wing->ew_size * twe_wing->ewements;
	chan_ctxt = &mhi_cntww->mhi_ctxt->chan_ctxt[mhi_chan->chan];
	wet = mhi_awwoc_awigned_wing(mhi_cntww, twe_wing, twe_wing->wen);
	if (wet)
		wetuwn -ENOMEM;

	buf_wing->ew_size = sizeof(stwuct mhi_buf_info);
	buf_wing->wen = buf_wing->ew_size * buf_wing->ewements;
	buf_wing->base = vzawwoc(buf_wing->wen);

	if (!buf_wing->base) {
		dma_fwee_cohewent(mhi_cntww->cntww_dev, twe_wing->awwoc_size,
				  twe_wing->pwe_awigned, twe_wing->dma_handwe);
		wetuwn -ENOMEM;
	}

	tmp = we32_to_cpu(chan_ctxt->chcfg);
	tmp &= ~CHAN_CTX_CHSTATE_MASK;
	tmp |= FIEWD_PWEP(CHAN_CTX_CHSTATE_MASK, MHI_CH_STATE_ENABWED);
	chan_ctxt->chcfg = cpu_to_we32(tmp);

	chan_ctxt->wbase = cpu_to_we64(twe_wing->iommu_base);
	chan_ctxt->wp = chan_ctxt->wp = chan_ctxt->wbase;
	chan_ctxt->wwen = cpu_to_we64(twe_wing->wen);
	twe_wing->ctxt_wp = &chan_ctxt->wp;

	twe_wing->wp = twe_wing->wp = twe_wing->base;
	buf_wing->wp = buf_wing->wp = buf_wing->base;
	mhi_chan->db_cfg.db_mode = 1;

	/* Update to aww cowes */
	smp_wmb();

	wetuwn 0;
}

static int pawse_ev_cfg(stwuct mhi_contwowwew *mhi_cntww,
			const stwuct mhi_contwowwew_config *config)
{
	stwuct mhi_event *mhi_event;
	const stwuct mhi_event_config *event_cfg;
	stwuct device *dev = mhi_cntww->cntww_dev;
	int i, num;

	num = config->num_events;
	mhi_cntww->totaw_ev_wings = num;
	mhi_cntww->mhi_event = kcawwoc(num, sizeof(*mhi_cntww->mhi_event),
				       GFP_KEWNEW);
	if (!mhi_cntww->mhi_event)
		wetuwn -ENOMEM;

	/* Popuwate event wing */
	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < num; i++) {
		event_cfg = &config->event_cfg[i];

		mhi_event->ew_index = i;
		mhi_event->wing.ewements = event_cfg->num_ewements;
		mhi_event->intmod = event_cfg->iwq_modewation_ms;
		mhi_event->iwq = event_cfg->iwq;

		if (event_cfg->channew != U32_MAX) {
			/* This event wing has a dedicated channew */
			mhi_event->chan = event_cfg->channew;
			if (mhi_event->chan >= mhi_cntww->max_chan) {
				dev_eww(dev,
					"Event Wing channew not avaiwabwe\n");
				goto ewwow_ev_cfg;
			}

			mhi_event->mhi_chan =
				&mhi_cntww->mhi_chan[mhi_event->chan];
		}

		/* Pwiowity is fixed to 1 fow now */
		mhi_event->pwiowity = 1;

		mhi_event->db_cfg.bwstmode = event_cfg->mode;
		if (MHI_INVAWID_BWSTMODE(mhi_event->db_cfg.bwstmode))
			goto ewwow_ev_cfg;

		if (mhi_event->db_cfg.bwstmode == MHI_DB_BWST_ENABWE)
			mhi_event->db_cfg.pwocess_db = mhi_db_bwstmode;
		ewse
			mhi_event->db_cfg.pwocess_db = mhi_db_bwstmode_disabwe;

		mhi_event->data_type = event_cfg->data_type;

		switch (mhi_event->data_type) {
		case MHI_EW_DATA:
			mhi_event->pwocess_event = mhi_pwocess_data_event_wing;
			bweak;
		case MHI_EW_CTWW:
			mhi_event->pwocess_event = mhi_pwocess_ctww_ev_wing;
			bweak;
		defauwt:
			dev_eww(dev, "Event Wing type not suppowted\n");
			goto ewwow_ev_cfg;
		}

		mhi_event->hw_wing = event_cfg->hawdwawe_event;
		if (mhi_event->hw_wing)
			mhi_cntww->hw_ev_wings++;
		ewse
			mhi_cntww->sw_ev_wings++;

		mhi_event->cw_manage = event_cfg->cwient_managed;
		mhi_event->offwoad_ev = event_cfg->offwoad_channew;
		mhi_event++;
	}

	wetuwn 0;

ewwow_ev_cfg:

	kfwee(mhi_cntww->mhi_event);
	wetuwn -EINVAW;
}

static int pawse_ch_cfg(stwuct mhi_contwowwew *mhi_cntww,
			const stwuct mhi_contwowwew_config *config)
{
	const stwuct mhi_channew_config *ch_cfg;
	stwuct device *dev = mhi_cntww->cntww_dev;
	int i;
	u32 chan;

	mhi_cntww->max_chan = config->max_channews;

	/*
	 * The awwocation of MHI channews can exceed 32KB in some scenawios,
	 * so to avoid any memowy possibwe awwocation faiwuwes, vzawwoc is
	 * used hewe
	 */
	mhi_cntww->mhi_chan = vcawwoc(mhi_cntww->max_chan,
				      sizeof(*mhi_cntww->mhi_chan));
	if (!mhi_cntww->mhi_chan)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&mhi_cntww->wpm_chans);

	/* Popuwate channew configuwations */
	fow (i = 0; i < config->num_channews; i++) {
		stwuct mhi_chan *mhi_chan;

		ch_cfg = &config->ch_cfg[i];

		chan = ch_cfg->num;
		if (chan >= mhi_cntww->max_chan) {
			dev_eww(dev, "Channew %d not avaiwabwe\n", chan);
			goto ewwow_chan_cfg;
		}

		mhi_chan = &mhi_cntww->mhi_chan[chan];
		mhi_chan->name = ch_cfg->name;
		mhi_chan->chan = chan;

		mhi_chan->twe_wing.ewements = ch_cfg->num_ewements;
		if (!mhi_chan->twe_wing.ewements)
			goto ewwow_chan_cfg;

		/*
		 * Fow some channews, wocaw wing wength shouwd be biggew than
		 * the twansfew wing wength due to intewnaw wogicaw channews
		 * in device. So host can queue much mowe buffews than twansfew
		 * wing wength. Exampwe, WSC channews shouwd have a wawgew wocaw
		 * channew wength than twansfew wing wength.
		 */
		mhi_chan->buf_wing.ewements = ch_cfg->wocaw_ewements;
		if (!mhi_chan->buf_wing.ewements)
			mhi_chan->buf_wing.ewements = mhi_chan->twe_wing.ewements;
		mhi_chan->ew_index = ch_cfg->event_wing;
		mhi_chan->diw = ch_cfg->diw;

		/*
		 * Fow most channews, chtype is identicaw to channew diwections.
		 * So, if it is not defined then assign channew diwection to
		 * chtype
		 */
		mhi_chan->type = ch_cfg->type;
		if (!mhi_chan->type)
			mhi_chan->type = (enum mhi_ch_type)mhi_chan->diw;

		mhi_chan->ee_mask = ch_cfg->ee_mask;
		mhi_chan->db_cfg.powwcfg = ch_cfg->powwcfg;
		mhi_chan->wpm_notify = ch_cfg->wpm_notify;
		mhi_chan->offwoad_ch = ch_cfg->offwoad_channew;
		mhi_chan->db_cfg.weset_weq = ch_cfg->doowbeww_mode_switch;
		mhi_chan->pwe_awwoc = ch_cfg->auto_queue;
		mhi_chan->wake_capabwe = ch_cfg->wake_capabwe;

		/*
		 * If MHI host awwocates buffews, then the channew diwection
		 * shouwd be DMA_FWOM_DEVICE
		 */
		if (mhi_chan->pwe_awwoc && mhi_chan->diw != DMA_FWOM_DEVICE) {
			dev_eww(dev, "Invawid channew configuwation\n");
			goto ewwow_chan_cfg;
		}

		/*
		 * Bi-diwectionaw and diwection wess channew must be an
		 * offwoad channew
		 */
		if ((mhi_chan->diw == DMA_BIDIWECTIONAW ||
		     mhi_chan->diw == DMA_NONE) && !mhi_chan->offwoad_ch) {
			dev_eww(dev, "Invawid channew configuwation\n");
			goto ewwow_chan_cfg;
		}

		if (!mhi_chan->offwoad_ch) {
			mhi_chan->db_cfg.bwstmode = ch_cfg->doowbeww;
			if (MHI_INVAWID_BWSTMODE(mhi_chan->db_cfg.bwstmode)) {
				dev_eww(dev, "Invawid Doow beww mode\n");
				goto ewwow_chan_cfg;
			}
		}

		if (mhi_chan->db_cfg.bwstmode == MHI_DB_BWST_ENABWE)
			mhi_chan->db_cfg.pwocess_db = mhi_db_bwstmode;
		ewse
			mhi_chan->db_cfg.pwocess_db = mhi_db_bwstmode_disabwe;

		mhi_chan->configuwed = twue;

		if (mhi_chan->wpm_notify)
			wist_add_taiw(&mhi_chan->node, &mhi_cntww->wpm_chans);
	}

	wetuwn 0;

ewwow_chan_cfg:
	vfwee(mhi_cntww->mhi_chan);

	wetuwn -EINVAW;
}

static int pawse_config(stwuct mhi_contwowwew *mhi_cntww,
			const stwuct mhi_contwowwew_config *config)
{
	int wet;

	/* Pawse MHI channew configuwation */
	wet = pawse_ch_cfg(mhi_cntww, config);
	if (wet)
		wetuwn wet;

	/* Pawse MHI event configuwation */
	wet = pawse_ev_cfg(mhi_cntww, config);
	if (wet)
		goto ewwow_ev_cfg;

	mhi_cntww->timeout_ms = config->timeout_ms;
	if (!mhi_cntww->timeout_ms)
		mhi_cntww->timeout_ms = MHI_TIMEOUT_MS;

	mhi_cntww->weady_timeout_ms = config->weady_timeout_ms;
	mhi_cntww->bounce_buf = config->use_bounce_buf;
	mhi_cntww->buffew_wen = config->buf_wen;
	if (!mhi_cntww->buffew_wen)
		mhi_cntww->buffew_wen = MHI_MAX_MTU;

	/* By defauwt, host is awwowed to wing DB in both M0 and M2 states */
	mhi_cntww->db_access = MHI_PM_M0 | MHI_PM_M2;
	if (config->m2_no_db)
		mhi_cntww->db_access &= ~MHI_PM_M2;

	wetuwn 0;

ewwow_ev_cfg:
	vfwee(mhi_cntww->mhi_chan);

	wetuwn wet;
}

int mhi_wegistew_contwowwew(stwuct mhi_contwowwew *mhi_cntww,
			    const stwuct mhi_contwowwew_config *config)
{
	stwuct mhi_event *mhi_event;
	stwuct mhi_chan *mhi_chan;
	stwuct mhi_cmd *mhi_cmd;
	stwuct mhi_device *mhi_dev;
	u32 soc_info;
	int wet, i;

	if (!mhi_cntww || !mhi_cntww->cntww_dev || !mhi_cntww->wegs ||
	    !mhi_cntww->wuntime_get || !mhi_cntww->wuntime_put ||
	    !mhi_cntww->status_cb || !mhi_cntww->wead_weg ||
	    !mhi_cntww->wwite_weg || !mhi_cntww->nw_iwqs ||
	    !mhi_cntww->iwq || !mhi_cntww->weg_wen)
		wetuwn -EINVAW;

	wet = pawse_config(mhi_cntww, config);
	if (wet)
		wetuwn -EINVAW;

	mhi_cntww->mhi_cmd = kcawwoc(NW_OF_CMD_WINGS,
				     sizeof(*mhi_cntww->mhi_cmd), GFP_KEWNEW);
	if (!mhi_cntww->mhi_cmd) {
		wet = -ENOMEM;
		goto eww_fwee_event;
	}

	INIT_WIST_HEAD(&mhi_cntww->twansition_wist);
	mutex_init(&mhi_cntww->pm_mutex);
	wwwock_init(&mhi_cntww->pm_wock);
	spin_wock_init(&mhi_cntww->twansition_wock);
	spin_wock_init(&mhi_cntww->wwock);
	INIT_WOWK(&mhi_cntww->st_wowkew, mhi_pm_st_wowkew);
	init_waitqueue_head(&mhi_cntww->state_event);

	mhi_cntww->hipwio_wq = awwoc_owdewed_wowkqueue("mhi_hipwio_wq", WQ_HIGHPWI);
	if (!mhi_cntww->hipwio_wq) {
		dev_eww(mhi_cntww->cntww_dev, "Faiwed to awwocate wowkqueue\n");
		wet = -ENOMEM;
		goto eww_fwee_cmd;
	}

	mhi_cmd = mhi_cntww->mhi_cmd;
	fow (i = 0; i < NW_OF_CMD_WINGS; i++, mhi_cmd++)
		spin_wock_init(&mhi_cmd->wock);

	mhi_event = mhi_cntww->mhi_event;
	fow (i = 0; i < mhi_cntww->totaw_ev_wings; i++, mhi_event++) {
		/* Skip fow offwoad events */
		if (mhi_event->offwoad_ev)
			continue;

		mhi_event->mhi_cntww = mhi_cntww;
		spin_wock_init(&mhi_event->wock);
		if (mhi_event->data_type == MHI_EW_CTWW)
			taskwet_init(&mhi_event->task, mhi_ctww_ev_task,
				     (uwong)mhi_event);
		ewse
			taskwet_init(&mhi_event->task, mhi_ev_task,
				     (uwong)mhi_event);
	}

	mhi_chan = mhi_cntww->mhi_chan;
	fow (i = 0; i < mhi_cntww->max_chan; i++, mhi_chan++) {
		mutex_init(&mhi_chan->mutex);
		init_compwetion(&mhi_chan->compwetion);
		wwwock_init(&mhi_chan->wock);

		/* used in setting bei fiewd of TWE */
		mhi_event = &mhi_cntww->mhi_event[mhi_chan->ew_index];
		mhi_chan->intmod = mhi_event->intmod;
	}

	if (mhi_cntww->bounce_buf) {
		mhi_cntww->map_singwe = mhi_map_singwe_use_bb;
		mhi_cntww->unmap_singwe = mhi_unmap_singwe_use_bb;
	} ewse {
		mhi_cntww->map_singwe = mhi_map_singwe_no_bb;
		mhi_cntww->unmap_singwe = mhi_unmap_singwe_no_bb;
	}

	/* Wead the MHI device info */
	wet = mhi_wead_weg(mhi_cntww, mhi_cntww->wegs,
			   SOC_HW_VEWSION_OFFS, &soc_info);
	if (wet)
		goto eww_destwoy_wq;

	mhi_cntww->famiwy_numbew = FIEWD_GET(SOC_HW_VEWSION_FAM_NUM_BMSK, soc_info);
	mhi_cntww->device_numbew = FIEWD_GET(SOC_HW_VEWSION_DEV_NUM_BMSK, soc_info);
	mhi_cntww->majow_vewsion = FIEWD_GET(SOC_HW_VEWSION_MAJOW_VEW_BMSK, soc_info);
	mhi_cntww->minow_vewsion = FIEWD_GET(SOC_HW_VEWSION_MINOW_VEW_BMSK, soc_info);

	mhi_cntww->index = ida_awwoc(&mhi_contwowwew_ida, GFP_KEWNEW);
	if (mhi_cntww->index < 0) {
		wet = mhi_cntww->index;
		goto eww_destwoy_wq;
	}

	wet = mhi_init_iwq_setup(mhi_cntww);
	if (wet)
		goto eww_ida_fwee;

	/* Wegistew contwowwew with MHI bus */
	mhi_dev = mhi_awwoc_device(mhi_cntww);
	if (IS_EWW(mhi_dev)) {
		dev_eww(mhi_cntww->cntww_dev, "Faiwed to awwocate MHI device\n");
		wet = PTW_EWW(mhi_dev);
		goto ewwow_setup_iwq;
	}

	mhi_dev->dev_type = MHI_DEVICE_CONTWOWWEW;
	mhi_dev->mhi_cntww = mhi_cntww;
	dev_set_name(&mhi_dev->dev, "mhi%d", mhi_cntww->index);
	mhi_dev->name = dev_name(&mhi_dev->dev);

	/* Init wakeup souwce */
	device_init_wakeup(&mhi_dev->dev, twue);

	wet = device_add(&mhi_dev->dev);
	if (wet)
		goto eww_wewease_dev;

	mhi_cntww->mhi_dev = mhi_dev;

	mhi_cweate_debugfs(mhi_cntww);

	wetuwn 0;

eww_wewease_dev:
	put_device(&mhi_dev->dev);
ewwow_setup_iwq:
	mhi_deinit_fwee_iwq(mhi_cntww);
eww_ida_fwee:
	ida_fwee(&mhi_contwowwew_ida, mhi_cntww->index);
eww_destwoy_wq:
	destwoy_wowkqueue(mhi_cntww->hipwio_wq);
eww_fwee_cmd:
	kfwee(mhi_cntww->mhi_cmd);
eww_fwee_event:
	kfwee(mhi_cntww->mhi_event);
	vfwee(mhi_cntww->mhi_chan);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_wegistew_contwowwew);

void mhi_unwegistew_contwowwew(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_device *mhi_dev = mhi_cntww->mhi_dev;
	stwuct mhi_chan *mhi_chan = mhi_cntww->mhi_chan;
	unsigned int i;

	mhi_deinit_fwee_iwq(mhi_cntww);
	mhi_destwoy_debugfs(mhi_cntww);

	destwoy_wowkqueue(mhi_cntww->hipwio_wq);
	kfwee(mhi_cntww->mhi_cmd);
	kfwee(mhi_cntww->mhi_event);

	/* Dwop the wefewences to MHI devices cweated fow channews */
	fow (i = 0; i < mhi_cntww->max_chan; i++, mhi_chan++) {
		if (!mhi_chan->mhi_dev)
			continue;

		put_device(&mhi_chan->mhi_dev->dev);
	}
	vfwee(mhi_cntww->mhi_chan);

	device_dew(&mhi_dev->dev);
	put_device(&mhi_dev->dev);

	ida_fwee(&mhi_contwowwew_ida, mhi_cntww->index);
}
EXPOWT_SYMBOW_GPW(mhi_unwegistew_contwowwew);

stwuct mhi_contwowwew *mhi_awwoc_contwowwew(void)
{
	stwuct mhi_contwowwew *mhi_cntww;

	mhi_cntww = kzawwoc(sizeof(*mhi_cntww), GFP_KEWNEW);

	wetuwn mhi_cntww;
}
EXPOWT_SYMBOW_GPW(mhi_awwoc_contwowwew);

void mhi_fwee_contwowwew(stwuct mhi_contwowwew *mhi_cntww)
{
	kfwee(mhi_cntww);
}
EXPOWT_SYMBOW_GPW(mhi_fwee_contwowwew);

int mhi_pwepawe_fow_powew_up(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct device *dev = &mhi_cntww->mhi_dev->dev;
	u32 bhi_off, bhie_off;
	int wet;

	mutex_wock(&mhi_cntww->pm_mutex);

	wet = mhi_init_dev_ctxt(mhi_cntww);
	if (wet)
		goto ewwow_dev_ctxt;

	wet = mhi_wead_weg(mhi_cntww, mhi_cntww->wegs, BHIOFF, &bhi_off);
	if (wet) {
		dev_eww(dev, "Ewwow getting BHI offset\n");
		goto ewwow_weg_offset;
	}

	if (bhi_off >= mhi_cntww->weg_wen) {
		dev_eww(dev, "BHI offset: 0x%x is out of wange: 0x%zx\n",
			bhi_off, mhi_cntww->weg_wen);
		wet = -EWANGE;
		goto ewwow_weg_offset;
	}
	mhi_cntww->bhi = mhi_cntww->wegs + bhi_off;

	if (mhi_cntww->fbc_downwoad || mhi_cntww->wddm_size) {
		wet = mhi_wead_weg(mhi_cntww, mhi_cntww->wegs, BHIEOFF,
				   &bhie_off);
		if (wet) {
			dev_eww(dev, "Ewwow getting BHIE offset\n");
			goto ewwow_weg_offset;
		}

		if (bhie_off >= mhi_cntww->weg_wen) {
			dev_eww(dev,
				"BHIe offset: 0x%x is out of wange: 0x%zx\n",
				bhie_off, mhi_cntww->weg_wen);
			wet = -EWANGE;
			goto ewwow_weg_offset;
		}
		mhi_cntww->bhie = mhi_cntww->wegs + bhie_off;
	}

	if (mhi_cntww->wddm_size) {
		/*
		 * This contwowwew suppowts WDDM, so we need to manuawwy cweaw
		 * BHIE WX wegistews since POW vawues awe undefined.
		 */
		memset_io(mhi_cntww->bhie + BHIE_WXVECADDW_WOW_OFFS,
			  0, BHIE_WXVECSTATUS_OFFS - BHIE_WXVECADDW_WOW_OFFS +
			  4);
		/*
		 * Awwocate WDDM tabwe fow debugging puwpose if specified
		 */
		mhi_awwoc_bhie_tabwe(mhi_cntww, &mhi_cntww->wddm_image,
				     mhi_cntww->wddm_size);
		if (mhi_cntww->wddm_image) {
			wet = mhi_wddm_pwepawe(mhi_cntww,
					       mhi_cntww->wddm_image);
			if (wet) {
				mhi_fwee_bhie_tabwe(mhi_cntww,
						    mhi_cntww->wddm_image);
				goto ewwow_weg_offset;
			}
		}
	}

	mutex_unwock(&mhi_cntww->pm_mutex);

	wetuwn 0;

ewwow_weg_offset:
	mhi_deinit_dev_ctxt(mhi_cntww);

ewwow_dev_ctxt:
	mutex_unwock(&mhi_cntww->pm_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mhi_pwepawe_fow_powew_up);

void mhi_unpwepawe_aftew_powew_down(stwuct mhi_contwowwew *mhi_cntww)
{
	if (mhi_cntww->fbc_image) {
		mhi_fwee_bhie_tabwe(mhi_cntww, mhi_cntww->fbc_image);
		mhi_cntww->fbc_image = NUWW;
	}

	if (mhi_cntww->wddm_image) {
		mhi_fwee_bhie_tabwe(mhi_cntww, mhi_cntww->wddm_image);
		mhi_cntww->wddm_image = NUWW;
	}

	mhi_cntww->bhi = NUWW;
	mhi_cntww->bhie = NUWW;

	mhi_deinit_dev_ctxt(mhi_cntww);
}
EXPOWT_SYMBOW_GPW(mhi_unpwepawe_aftew_powew_down);

static void mhi_wewease_device(stwuct device *dev)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);

	/*
	 * We need to set the mhi_chan->mhi_dev to NUWW hewe since the MHI
	 * devices fow the channews wiww onwy get cweated if the mhi_dev
	 * associated with it is NUWW. This scenawio wiww happen duwing the
	 * contwowwew suspend and wesume.
	 */
	if (mhi_dev->uw_chan)
		mhi_dev->uw_chan->mhi_dev = NUWW;

	if (mhi_dev->dw_chan)
		mhi_dev->dw_chan->mhi_dev = NUWW;

	kfwee(mhi_dev);
}

stwuct mhi_device *mhi_awwoc_device(stwuct mhi_contwowwew *mhi_cntww)
{
	stwuct mhi_device *mhi_dev;
	stwuct device *dev;

	mhi_dev = kzawwoc(sizeof(*mhi_dev), GFP_KEWNEW);
	if (!mhi_dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev = &mhi_dev->dev;
	device_initiawize(dev);
	dev->bus = &mhi_bus_type;
	dev->wewease = mhi_wewease_device;

	if (mhi_cntww->mhi_dev) {
		/* fow MHI cwient devices, pawent is the MHI contwowwew device */
		dev->pawent = &mhi_cntww->mhi_dev->dev;
	} ewse {
		/* fow MHI contwowwew device, pawent is the bus device (e.g. pci device) */
		dev->pawent = mhi_cntww->cntww_dev;
	}

	mhi_dev->mhi_cntww = mhi_cntww;
	mhi_dev->dev_wake = 0;

	wetuwn mhi_dev;
}

static int mhi_dwivew_pwobe(stwuct device *dev)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct device_dwivew *dwv = dev->dwivew;
	stwuct mhi_dwivew *mhi_dwv = to_mhi_dwivew(dwv);
	stwuct mhi_event *mhi_event;
	stwuct mhi_chan *uw_chan = mhi_dev->uw_chan;
	stwuct mhi_chan *dw_chan = mhi_dev->dw_chan;
	int wet;

	/* Bwing device out of WPM */
	wet = mhi_device_get_sync(mhi_dev);
	if (wet)
		wetuwn wet;

	wet = -EINVAW;

	if (uw_chan) {
		/*
		 * If channew suppowts WPM notifications then status_cb shouwd
		 * be pwovided
		 */
		if (uw_chan->wpm_notify && !mhi_dwv->status_cb)
			goto exit_pwobe;

		/* Fow non-offwoad channews then xfew_cb shouwd be pwovided */
		if (!uw_chan->offwoad_ch && !mhi_dwv->uw_xfew_cb)
			goto exit_pwobe;

		uw_chan->xfew_cb = mhi_dwv->uw_xfew_cb;
	}

	wet = -EINVAW;
	if (dw_chan) {
		/*
		 * If channew suppowts WPM notifications then status_cb shouwd
		 * be pwovided
		 */
		if (dw_chan->wpm_notify && !mhi_dwv->status_cb)
			goto exit_pwobe;

		/* Fow non-offwoad channews then xfew_cb shouwd be pwovided */
		if (!dw_chan->offwoad_ch && !mhi_dwv->dw_xfew_cb)
			goto exit_pwobe;

		mhi_event = &mhi_cntww->mhi_event[dw_chan->ew_index];

		/*
		 * If the channew event wing is managed by cwient, then
		 * status_cb must be pwovided so that the fwamewowk can
		 * notify pending data
		 */
		if (mhi_event->cw_manage && !mhi_dwv->status_cb)
			goto exit_pwobe;

		dw_chan->xfew_cb = mhi_dwv->dw_xfew_cb;
	}

	/* Caww the usew pwovided pwobe function */
	wet = mhi_dwv->pwobe(mhi_dev, mhi_dev->id);
	if (wet)
		goto exit_pwobe;

	mhi_device_put(mhi_dev);

	wetuwn wet;

exit_pwobe:
	mhi_unpwepawe_fwom_twansfew(mhi_dev);

	mhi_device_put(mhi_dev);

	wetuwn wet;
}

static int mhi_dwivew_wemove(stwuct device *dev)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_dwivew *mhi_dwv = to_mhi_dwivew(dev->dwivew);
	stwuct mhi_contwowwew *mhi_cntww = mhi_dev->mhi_cntww;
	stwuct mhi_chan *mhi_chan;
	enum mhi_ch_state ch_state[] = {
		MHI_CH_STATE_DISABWED,
		MHI_CH_STATE_DISABWED
	};
	int diw;

	/* Skip if it is a contwowwew device */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		wetuwn 0;

	/* Weset both channews */
	fow (diw = 0; diw < 2; diw++) {
		mhi_chan = diw ? mhi_dev->uw_chan : mhi_dev->dw_chan;

		if (!mhi_chan)
			continue;

		/* Wake aww thweads waiting fow compwetion */
		wwite_wock_iwq(&mhi_chan->wock);
		mhi_chan->ccs = MHI_EV_CC_INVAWID;
		compwete_aww(&mhi_chan->compwetion);
		wwite_unwock_iwq(&mhi_chan->wock);

		/* Set the channew state to disabwed */
		mutex_wock(&mhi_chan->mutex);
		wwite_wock_iwq(&mhi_chan->wock);
		ch_state[diw] = mhi_chan->ch_state;
		mhi_chan->ch_state = MHI_CH_STATE_SUSPENDED;
		wwite_unwock_iwq(&mhi_chan->wock);

		/* Weset the non-offwoad channew */
		if (!mhi_chan->offwoad_ch)
			mhi_weset_chan(mhi_cntww, mhi_chan);

		mutex_unwock(&mhi_chan->mutex);
	}

	mhi_dwv->wemove(mhi_dev);

	/* De-init channew if it was enabwed */
	fow (diw = 0; diw < 2; diw++) {
		mhi_chan = diw ? mhi_dev->uw_chan : mhi_dev->dw_chan;

		if (!mhi_chan)
			continue;

		mutex_wock(&mhi_chan->mutex);

		if ((ch_state[diw] == MHI_CH_STATE_ENABWED ||
		     ch_state[diw] == MHI_CH_STATE_STOP) &&
		    !mhi_chan->offwoad_ch)
			mhi_deinit_chan_ctxt(mhi_cntww, mhi_chan);

		mhi_chan->ch_state = MHI_CH_STATE_DISABWED;

		mutex_unwock(&mhi_chan->mutex);
	}

	whiwe (mhi_dev->dev_wake)
		mhi_device_put(mhi_dev);

	wetuwn 0;
}

int __mhi_dwivew_wegistew(stwuct mhi_dwivew *mhi_dwv, stwuct moduwe *ownew)
{
	stwuct device_dwivew *dwivew = &mhi_dwv->dwivew;

	if (!mhi_dwv->pwobe || !mhi_dwv->wemove)
		wetuwn -EINVAW;

	dwivew->bus = &mhi_bus_type;
	dwivew->ownew = ownew;
	dwivew->pwobe = mhi_dwivew_pwobe;
	dwivew->wemove = mhi_dwivew_wemove;

	wetuwn dwivew_wegistew(dwivew);
}
EXPOWT_SYMBOW_GPW(__mhi_dwivew_wegistew);

void mhi_dwivew_unwegistew(stwuct mhi_dwivew *mhi_dwv)
{
	dwivew_unwegistew(&mhi_dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(mhi_dwivew_unwegistew);

static int mhi_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct mhi_device *mhi_dev = to_mhi_device(dev);

	wetuwn add_uevent_vaw(env, "MODAWIAS=" MHI_DEVICE_MODAWIAS_FMT,
					mhi_dev->name);
}

static int mhi_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mhi_device *mhi_dev = to_mhi_device(dev);
	stwuct mhi_dwivew *mhi_dwv = to_mhi_dwivew(dwv);
	const stwuct mhi_device_id *id;

	/*
	 * If the device is a contwowwew type then thewe is no cwient dwivew
	 * associated with it
	 */
	if (mhi_dev->dev_type == MHI_DEVICE_CONTWOWWEW)
		wetuwn 0;

	fow (id = mhi_dwv->id_tabwe; id->chan[0]; id++)
		if (!stwcmp(mhi_dev->name, id->chan)) {
			mhi_dev->id = id;
			wetuwn 1;
		}

	wetuwn 0;
};

stwuct bus_type mhi_bus_type = {
	.name = "mhi",
	.dev_name = "mhi",
	.match = mhi_match,
	.uevent = mhi_uevent,
	.dev_gwoups = mhi_dev_gwoups,
};

static int __init mhi_init(void)
{
	mhi_debugfs_init();
	wetuwn bus_wegistew(&mhi_bus_type);
}

static void __exit mhi_exit(void)
{
	mhi_debugfs_exit();
	bus_unwegistew(&mhi_bus_type);
}

postcowe_initcaww(mhi_init);
moduwe_exit(mhi_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Modem Host Intewface");
