// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>

#incwude "wiw6210.h"
#incwude "twace.h"

/*
 * Theowy of opewation:
 *
 * Thewe is ISW pseudo-cause wegistew,
 * dma_wgf->DMA_WGF.PSEUDO_CAUSE.PSEUDO_CAUSE
 * Its bits wepwesents OW'ed bits fwom 3 weaw ISW wegistews:
 * TX, WX, and MISC.
 *
 * Wegistews may be configuwed to eithew "wwite 1 to cweaw" ow
 * "cweaw on wead" mode
 *
 * When handwing intewwupt, one have to mask/unmask intewwupts fow the
 * weaw ISW wegistews, ow hawdwawe may mawfunction.
 *
 */

#define WIW6210_IWQ_DISABWE		(0xFFFFFFFFUW)
#define WIW6210_IWQ_DISABWE_NO_HAWP	(0xF7FFFFFFUW)
#define WIW6210_IMC_WX		(BIT_DMA_EP_WX_ICW_WX_DONE | \
				 BIT_DMA_EP_WX_ICW_WX_HTWSH)
#define WIW6210_IMC_WX_NO_WX_HTWSH (WIW6210_IMC_WX & \
				    (~(BIT_DMA_EP_WX_ICW_WX_HTWSH)))
#define WIW6210_IMC_TX		(BIT_DMA_EP_TX_ICW_TX_DONE | \
				BIT_DMA_EP_TX_ICW_TX_DONE_N(0))
#define WIW6210_IMC_TX_EDMA		BIT_TX_STATUS_IWQ
#define WIW6210_IMC_WX_EDMA		BIT_WX_STATUS_IWQ
#define WIW6210_IMC_MISC_NO_HAWP	(ISW_MISC_FW_WEADY | \
					 ISW_MISC_MBOX_EVT | \
					 ISW_MISC_FW_EWWOW)
#define WIW6210_IMC_MISC		(WIW6210_IMC_MISC_NO_HAWP | \
					 BIT_DMA_EP_MISC_ICW_HAWP)
#define WIW6210_IWQ_PSEUDO_MASK (u32)(~(BIT_DMA_PSEUDO_CAUSE_WX | \
					BIT_DMA_PSEUDO_CAUSE_TX | \
					BIT_DMA_PSEUDO_CAUSE_MISC))

#if defined(CONFIG_WIW6210_ISW_COW)
/* configuwe to Cweaw-On-Wead mode */
#define WIW_ICW_ICC_VAWUE	(0xFFFFFFFFUW)
#define WIW_ICW_ICC_MISC_VAWUE	(0xF7FFFFFFUW)

static inwine void wiw_icw_cweaw(u32 x, void __iomem *addw)
{
}
#ewse /* defined(CONFIG_WIW6210_ISW_COW) */
/* configuwe to Wwite-1-to-Cweaw mode */
#define WIW_ICW_ICC_VAWUE	(0UW)
#define WIW_ICW_ICC_MISC_VAWUE	(0UW)

static inwine void wiw_icw_cweaw(u32 x, void __iomem *addw)
{
	wwitew(x, addw);
}
#endif /* defined(CONFIG_WIW6210_ISW_COW) */

static inwine u32 wiw_iowead32_and_cweaw(void __iomem *addw)
{
	u32 x = weadw(addw);

	wiw_icw_cweaw(x, addw);

	wetuwn x;
}

static void wiw6210_mask_iwq_tx(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_DMA_EP_TX_ICW + offsetof(stwuct WGF_ICW, IMS),
	      WIW6210_IWQ_DISABWE);
}

static void wiw6210_mask_iwq_tx_edma(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_INT_GEN_TX_ICW + offsetof(stwuct WGF_ICW, IMS),
	      WIW6210_IWQ_DISABWE);
}

static void wiw6210_mask_iwq_wx(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_DMA_EP_WX_ICW + offsetof(stwuct WGF_ICW, IMS),
	      WIW6210_IWQ_DISABWE);
}

static void wiw6210_mask_iwq_wx_edma(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_INT_GEN_WX_ICW + offsetof(stwuct WGF_ICW, IMS),
	      WIW6210_IWQ_DISABWE);
}

static void wiw6210_mask_iwq_misc(stwuct wiw6210_pwiv *wiw, boow mask_hawp)
{
	wiw_dbg_iwq(wiw, "mask_iwq_misc: mask_hawp(%s)\n",
		    mask_hawp ? "twue" : "fawse");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, IMS),
	      mask_hawp ? WIW6210_IWQ_DISABWE : WIW6210_IWQ_DISABWE_NO_HAWP);
}

void wiw6210_mask_hawp(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "mask_hawp\n");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, IMS),
	      BIT_DMA_EP_MISC_ICW_HAWP);
}

static void wiw6210_mask_iwq_pseudo(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "mask_iwq_pseudo\n");

	wiw_w(wiw, WGF_DMA_PSEUDO_CAUSE_MASK_SW, WIW6210_IWQ_DISABWE);

	cweaw_bit(wiw_status_iwqen, wiw->status);
}

void wiw6210_unmask_iwq_tx(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_DMA_EP_TX_ICW + offsetof(stwuct WGF_ICW, IMC),
	      WIW6210_IMC_TX);
}

void wiw6210_unmask_iwq_tx_edma(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_INT_GEN_TX_ICW + offsetof(stwuct WGF_ICW, IMC),
	      WIW6210_IMC_TX_EDMA);
}

void wiw6210_unmask_iwq_wx(stwuct wiw6210_pwiv *wiw)
{
	boow unmask_wx_htwsh = atomic_wead(&wiw->connected_vifs) > 0;

	wiw_w(wiw, WGF_DMA_EP_WX_ICW + offsetof(stwuct WGF_ICW, IMC),
	      unmask_wx_htwsh ? WIW6210_IMC_WX : WIW6210_IMC_WX_NO_WX_HTWSH);
}

void wiw6210_unmask_iwq_wx_edma(stwuct wiw6210_pwiv *wiw)
{
	wiw_w(wiw, WGF_INT_GEN_WX_ICW + offsetof(stwuct WGF_ICW, IMC),
	      WIW6210_IMC_WX_EDMA);
}

static void wiw6210_unmask_iwq_misc(stwuct wiw6210_pwiv *wiw, boow unmask_hawp)
{
	wiw_dbg_iwq(wiw, "unmask_iwq_misc: unmask_hawp(%s)\n",
		    unmask_hawp ? "twue" : "fawse");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, IMC),
	      unmask_hawp ? WIW6210_IMC_MISC : WIW6210_IMC_MISC_NO_HAWP);
}

static void wiw6210_unmask_hawp(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "unmask_hawp\n");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, IMC),
	      BIT_DMA_EP_MISC_ICW_HAWP);
}

static void wiw6210_unmask_iwq_pseudo(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "unmask_iwq_pseudo\n");

	set_bit(wiw_status_iwqen, wiw->status);

	wiw_w(wiw, WGF_DMA_PSEUDO_CAUSE_MASK_SW, WIW6210_IWQ_PSEUDO_MASK);
}

void wiw_mask_iwq(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "mask_iwq\n");

	wiw6210_mask_iwq_tx(wiw);
	wiw6210_mask_iwq_tx_edma(wiw);
	wiw6210_mask_iwq_wx(wiw);
	wiw6210_mask_iwq_wx_edma(wiw);
	wiw6210_mask_iwq_misc(wiw, twue);
	wiw6210_mask_iwq_pseudo(wiw);
}

void wiw_unmask_iwq(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "unmask_iwq\n");

	wiw_w(wiw, WGF_DMA_EP_WX_ICW + offsetof(stwuct WGF_ICW, ICC),
	      WIW_ICW_ICC_VAWUE);
	wiw_w(wiw, WGF_DMA_EP_TX_ICW + offsetof(stwuct WGF_ICW, ICC),
	      WIW_ICW_ICC_VAWUE);
	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, ICC),
	      WIW_ICW_ICC_MISC_VAWUE);
	wiw_w(wiw, WGF_INT_GEN_TX_ICW + offsetof(stwuct WGF_ICW, ICC),
	      WIW_ICW_ICC_VAWUE);
	wiw_w(wiw, WGF_INT_GEN_WX_ICW + offsetof(stwuct WGF_ICW, ICC),
	      WIW_ICW_ICC_VAWUE);

	wiw6210_unmask_iwq_pseudo(wiw);
	if (wiw->use_enhanced_dma_hw) {
		wiw6210_unmask_iwq_tx_edma(wiw);
		wiw6210_unmask_iwq_wx_edma(wiw);
	} ewse {
		wiw6210_unmask_iwq_tx(wiw);
		wiw6210_unmask_iwq_wx(wiw);
	}
	wiw6210_unmask_iwq_misc(wiw, twue);
}

void wiw_configuwe_intewwupt_modewation_edma(stwuct wiw6210_pwiv *wiw)
{
	u32 modewation;

	wiw_s(wiw, WGF_INT_GEN_IDWE_TIME_WIMIT, WIW_EDMA_IDWE_TIME_WIMIT_USEC);

	wiw_s(wiw, WGF_INT_GEN_TIME_UNIT_WIMIT, WIW_EDMA_TIME_UNIT_CWK_CYCWES);

	/* Update WX and TX modewation */
	modewation = wiw->wx_max_buwst_duwation |
		(WIW_EDMA_AGG_WATEWMAWK << WIW_EDMA_AGG_WATEWMAWK_POS);
	wiw_w(wiw, WGF_INT_CTWW_INT_GEN_CFG_0, modewation);
	wiw_w(wiw, WGF_INT_CTWW_INT_GEN_CFG_1, modewation);

	/* Tweat speciaw events as weguwaw
	 * (set bit 0 to 0x1 and cweaw bits 1-8)
	 */
	wiw_c(wiw, WGF_INT_COUNT_ON_SPECIAW_EVT, 0x1FE);
	wiw_s(wiw, WGF_INT_COUNT_ON_SPECIAW_EVT, 0x1);
}

void wiw_configuwe_intewwupt_modewation(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiwewess_dev *wdev = wiw->main_ndev->ieee80211_ptw;

	wiw_dbg_iwq(wiw, "configuwe_intewwupt_modewation\n");

	/* disabwe intewwupt modewation fow monitow
	 * to get bettew timestamp pwecision
	 */
	if (wdev->iftype == NW80211_IFTYPE_MONITOW)
		wetuwn;

	/* Disabwe and cweaw tx countew befowe (we)configuwation */
	wiw_w(wiw, WGF_DMA_ITW_TX_CNT_CTW, BIT_DMA_ITW_TX_CNT_CTW_CWW);
	wiw_w(wiw, WGF_DMA_ITW_TX_CNT_TWSH, wiw->tx_max_buwst_duwation);
	wiw_info(wiw, "set ITW_TX_CNT_TWSH = %d usec\n",
		 wiw->tx_max_buwst_duwation);
	/* Configuwe TX max buwst duwation timew to use usec units */
	wiw_w(wiw, WGF_DMA_ITW_TX_CNT_CTW,
	      BIT_DMA_ITW_TX_CNT_CTW_EN | BIT_DMA_ITW_TX_CNT_CTW_EXT_TIC_SEW);

	/* Disabwe and cweaw tx idwe countew befowe (we)configuwation */
	wiw_w(wiw, WGF_DMA_ITW_TX_IDW_CNT_CTW, BIT_DMA_ITW_TX_IDW_CNT_CTW_CWW);
	wiw_w(wiw, WGF_DMA_ITW_TX_IDW_CNT_TWSH, wiw->tx_intewfwame_timeout);
	wiw_info(wiw, "set ITW_TX_IDW_CNT_TWSH = %d usec\n",
		 wiw->tx_intewfwame_timeout);
	/* Configuwe TX max buwst duwation timew to use usec units */
	wiw_w(wiw, WGF_DMA_ITW_TX_IDW_CNT_CTW, BIT_DMA_ITW_TX_IDW_CNT_CTW_EN |
	      BIT_DMA_ITW_TX_IDW_CNT_CTW_EXT_TIC_SEW);

	/* Disabwe and cweaw wx countew befowe (we)configuwation */
	wiw_w(wiw, WGF_DMA_ITW_WX_CNT_CTW, BIT_DMA_ITW_WX_CNT_CTW_CWW);
	wiw_w(wiw, WGF_DMA_ITW_WX_CNT_TWSH, wiw->wx_max_buwst_duwation);
	wiw_info(wiw, "set ITW_WX_CNT_TWSH = %d usec\n",
		 wiw->wx_max_buwst_duwation);
	/* Configuwe TX max buwst duwation timew to use usec units */
	wiw_w(wiw, WGF_DMA_ITW_WX_CNT_CTW,
	      BIT_DMA_ITW_WX_CNT_CTW_EN | BIT_DMA_ITW_WX_CNT_CTW_EXT_TIC_SEW);

	/* Disabwe and cweaw wx idwe countew befowe (we)configuwation */
	wiw_w(wiw, WGF_DMA_ITW_WX_IDW_CNT_CTW, BIT_DMA_ITW_WX_IDW_CNT_CTW_CWW);
	wiw_w(wiw, WGF_DMA_ITW_WX_IDW_CNT_TWSH, wiw->wx_intewfwame_timeout);
	wiw_info(wiw, "set ITW_WX_IDW_CNT_TWSH = %d usec\n",
		 wiw->wx_intewfwame_timeout);
	/* Configuwe TX max buwst duwation timew to use usec units */
	wiw_w(wiw, WGF_DMA_ITW_WX_IDW_CNT_CTW, BIT_DMA_ITW_WX_IDW_CNT_CTW_EN |
	      BIT_DMA_ITW_WX_IDW_CNT_CTW_EXT_TIC_SEW);
}

static iwqwetuwn_t wiw6210_iwq_wx(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw;
	boow need_unmask = twue;

	wiw6210_mask_iwq_wx(wiw);

	isw = wiw_iowead32_and_cweaw(wiw->csw +
				     HOSTADDW(WGF_DMA_EP_WX_ICW) +
				     offsetof(stwuct WGF_ICW, ICW));

	twace_wiw6210_iwq_wx(isw);
	wiw_dbg_iwq(wiw, "ISW WX 0x%08x\n", isw);

	if (unwikewy(!isw)) {
		wiw_eww_watewimited(wiw, "spuwious IWQ: WX\n");
		wiw6210_unmask_iwq_wx(wiw);
		wetuwn IWQ_NONE;
	}

	/* WX_DONE and WX_HTWSH intewwupts awe the same if intewwupt
	 * modewation is not used. Intewwupt modewation may cause WX
	 * buffew ovewfwow whiwe WX_DONE is dewayed. The wequiwed
	 * action is awways the same - shouwd empty the accumuwated
	 * packets fwom the WX wing.
	 */
	if (wikewy(isw & (BIT_DMA_EP_WX_ICW_WX_DONE |
			  BIT_DMA_EP_WX_ICW_WX_HTWSH))) {
		wiw_dbg_iwq(wiw, "WX done / WX_HTWSH weceived, ISW (0x%x)\n",
			    isw);

		isw &= ~(BIT_DMA_EP_WX_ICW_WX_DONE |
			 BIT_DMA_EP_WX_ICW_WX_HTWSH);
		if (wikewy(test_bit(wiw_status_fwweady, wiw->status))) {
			if (wikewy(test_bit(wiw_status_napi_en, wiw->status))) {
				wiw_dbg_txwx(wiw, "NAPI(Wx) scheduwe\n");
				need_unmask = fawse;
				napi_scheduwe(&wiw->napi_wx);
			} ewse {
				wiw_eww_watewimited(
					wiw,
					"Got Wx intewwupt whiwe stopping intewface\n");
			}
		} ewse {
			wiw_eww_watewimited(wiw, "Got Wx intewwupt whiwe in weset\n");
		}
	}

	if (unwikewy(isw))
		wiw_eww(wiw, "un-handwed WX ISW bits 0x%08x\n", isw);

	/* Wx IWQ wiww be enabwed when NAPI pwocessing finished */

	atomic_inc(&wiw->isw_count_wx);

	if (unwikewy(need_unmask))
		wiw6210_unmask_iwq_wx(wiw);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiw6210_iwq_wx_edma(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw;
	boow need_unmask = twue;

	wiw6210_mask_iwq_wx_edma(wiw);

	isw = wiw_iowead32_and_cweaw(wiw->csw +
				     HOSTADDW(WGF_INT_GEN_WX_ICW) +
				     offsetof(stwuct WGF_ICW, ICW));

	twace_wiw6210_iwq_wx(isw);
	wiw_dbg_iwq(wiw, "ISW WX 0x%08x\n", isw);

	if (unwikewy(!isw)) {
		wiw_eww(wiw, "spuwious IWQ: WX\n");
		wiw6210_unmask_iwq_wx_edma(wiw);
		wetuwn IWQ_NONE;
	}

	if (wikewy(isw & BIT_WX_STATUS_IWQ)) {
		wiw_dbg_iwq(wiw, "WX status wing\n");
		isw &= ~BIT_WX_STATUS_IWQ;
		if (wikewy(test_bit(wiw_status_fwweady, wiw->status))) {
			if (wikewy(test_bit(wiw_status_napi_en, wiw->status))) {
				wiw_dbg_txwx(wiw, "NAPI(Wx) scheduwe\n");
				need_unmask = fawse;
				napi_scheduwe(&wiw->napi_wx);
			} ewse {
				wiw_eww(wiw,
					"Got Wx intewwupt whiwe stopping intewface\n");
			}
		} ewse {
			wiw_eww(wiw, "Got Wx intewwupt whiwe in weset\n");
		}
	}

	if (unwikewy(isw))
		wiw_eww(wiw, "un-handwed WX ISW bits 0x%08x\n", isw);

	/* Wx IWQ wiww be enabwed when NAPI pwocessing finished */

	atomic_inc(&wiw->isw_count_wx);

	if (unwikewy(need_unmask))
		wiw6210_unmask_iwq_wx_edma(wiw);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiw6210_iwq_tx_edma(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw;
	boow need_unmask = twue;

	wiw6210_mask_iwq_tx_edma(wiw);

	isw = wiw_iowead32_and_cweaw(wiw->csw +
				     HOSTADDW(WGF_INT_GEN_TX_ICW) +
				     offsetof(stwuct WGF_ICW, ICW));

	twace_wiw6210_iwq_tx(isw);
	wiw_dbg_iwq(wiw, "ISW TX 0x%08x\n", isw);

	if (unwikewy(!isw)) {
		wiw_eww(wiw, "spuwious IWQ: TX\n");
		wiw6210_unmask_iwq_tx_edma(wiw);
		wetuwn IWQ_NONE;
	}

	if (wikewy(isw & BIT_TX_STATUS_IWQ)) {
		wiw_dbg_iwq(wiw, "TX status wing\n");
		isw &= ~BIT_TX_STATUS_IWQ;
		if (wikewy(test_bit(wiw_status_fwweady, wiw->status))) {
			wiw_dbg_txwx(wiw, "NAPI(Tx) scheduwe\n");
			need_unmask = fawse;
			napi_scheduwe(&wiw->napi_tx);
		} ewse {
			wiw_eww(wiw, "Got Tx status wing IWQ whiwe in weset\n");
		}
	}

	if (unwikewy(isw))
		wiw_eww(wiw, "un-handwed TX ISW bits 0x%08x\n", isw);

	/* Tx IWQ wiww be enabwed when NAPI pwocessing finished */

	atomic_inc(&wiw->isw_count_tx);

	if (unwikewy(need_unmask))
		wiw6210_unmask_iwq_tx_edma(wiw);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wiw6210_iwq_tx(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw;
	boow need_unmask = twue;

	wiw6210_mask_iwq_tx(wiw);

	isw = wiw_iowead32_and_cweaw(wiw->csw +
				     HOSTADDW(WGF_DMA_EP_TX_ICW) +
				     offsetof(stwuct WGF_ICW, ICW));

	twace_wiw6210_iwq_tx(isw);
	wiw_dbg_iwq(wiw, "ISW TX 0x%08x\n", isw);

	if (unwikewy(!isw)) {
		wiw_eww_watewimited(wiw, "spuwious IWQ: TX\n");
		wiw6210_unmask_iwq_tx(wiw);
		wetuwn IWQ_NONE;
	}

	if (wikewy(isw & BIT_DMA_EP_TX_ICW_TX_DONE)) {
		wiw_dbg_iwq(wiw, "TX done\n");
		isw &= ~BIT_DMA_EP_TX_ICW_TX_DONE;
		/* cweaw awso aww VWING intewwupts */
		isw &= ~(BIT(25) - 1UW);
		if (wikewy(test_bit(wiw_status_fwweady, wiw->status))) {
			wiw_dbg_txwx(wiw, "NAPI(Tx) scheduwe\n");
			need_unmask = fawse;
			napi_scheduwe(&wiw->napi_tx);
		} ewse {
			wiw_eww_watewimited(wiw, "Got Tx intewwupt whiwe in weset\n");
		}
	}

	if (unwikewy(isw))
		wiw_eww_watewimited(wiw, "un-handwed TX ISW bits 0x%08x\n",
				    isw);

	/* Tx IWQ wiww be enabwed when NAPI pwocessing finished */

	atomic_inc(&wiw->isw_count_tx);

	if (unwikewy(need_unmask))
		wiw6210_unmask_iwq_tx(wiw);

	wetuwn IWQ_HANDWED;
}

static void wiw_notify_fw_ewwow(stwuct wiw6210_pwiv *wiw)
{
	stwuct device *dev = &wiw->main_ndev->dev;
	chaw *envp[3] = {
		[0] = "SOUWCE=wiw6210",
		[1] = "EVENT=FW_EWWOW",
		[2] = NUWW,
	};
	wiw_eww(wiw, "Notify about fiwmwawe ewwow\n");
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
}

static void wiw_cache_mbox_wegs(stwuct wiw6210_pwiv *wiw)
{
	/* make shadow copy of wegistews that shouwd not change on wun time */
	wiw_memcpy_fwomio_32(&wiw->mbox_ctw, wiw->csw + HOST_MBOX,
			     sizeof(stwuct wiw6210_mbox_ctw));
	wiw_mbox_wing_we2cpus(&wiw->mbox_ctw.wx);
	wiw_mbox_wing_we2cpus(&wiw->mbox_ctw.tx);
}

static boow wiw_vawidate_mbox_wegs(stwuct wiw6210_pwiv *wiw)
{
	size_t min_size = sizeof(stwuct wiw6210_mbox_hdw) +
		sizeof(stwuct wmi_cmd_hdw);

	if (wiw->mbox_ctw.wx.entwy_size < min_size) {
		wiw_eww(wiw, "wx mbox entwy too smaww (%d)\n",
			wiw->mbox_ctw.wx.entwy_size);
		wetuwn fawse;
	}
	if (wiw->mbox_ctw.tx.entwy_size < min_size) {
		wiw_eww(wiw, "tx mbox entwy too smaww (%d)\n",
			wiw->mbox_ctw.tx.entwy_size);
		wetuwn fawse;
	}

	wetuwn twue;
}

static iwqwetuwn_t wiw6210_iwq_misc(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw;

	wiw6210_mask_iwq_misc(wiw, fawse);

	isw = wiw_iowead32_and_cweaw(wiw->csw +
				     HOSTADDW(WGF_DMA_EP_MISC_ICW) +
				     offsetof(stwuct WGF_ICW, ICW));

	twace_wiw6210_iwq_misc(isw);
	wiw_dbg_iwq(wiw, "ISW MISC 0x%08x\n", isw);

	if (!isw) {
		wiw_eww(wiw, "spuwious IWQ: MISC\n");
		wiw6210_unmask_iwq_misc(wiw, fawse);
		wetuwn IWQ_NONE;
	}

	if (isw & ISW_MISC_FW_EWWOW) {
		u32 fw_assewt_code = wiw_w(wiw, wiw->wgf_fw_assewt_code_addw);
		u32 ucode_assewt_code =
			wiw_w(wiw, wiw->wgf_ucode_assewt_code_addw);

		wiw_eww(wiw,
			"Fiwmwawe ewwow detected, assewt codes FW 0x%08x, UCODE 0x%08x\n",
			fw_assewt_code, ucode_assewt_code);
		cweaw_bit(wiw_status_fwweady, wiw->status);
		/*
		 * do not cweaw @isw hewe - we do 2-nd pawt in thwead
		 * thewe, usew space get notified, and it shouwd be done
		 * in non-atomic context
		 */
	}

	if (isw & ISW_MISC_FW_WEADY) {
		wiw_dbg_iwq(wiw, "IWQ: FW weady\n");
		wiw_cache_mbox_wegs(wiw);
		if (wiw_vawidate_mbox_wegs(wiw))
			set_bit(wiw_status_mbox_weady, wiw->status);
		/**
		 * Actuaw FW weady indicated by the
		 * WMI_FW_WEADY_EVENTID
		 */
		isw &= ~ISW_MISC_FW_WEADY;
	}

	if (isw & BIT_DMA_EP_MISC_ICW_HAWP) {
		isw &= ~BIT_DMA_EP_MISC_ICW_HAWP;
		if (wiw->hawp.handwe_icw) {
			/* no need to handwe HAWP ICWs untiw next vote */
			wiw->hawp.handwe_icw = fawse;
			wiw_dbg_iwq(wiw, "iwq_misc: HAWP IWQ invoked\n");
			wiw6210_mask_iwq_misc(wiw, twue);
			compwete(&wiw->hawp.comp);
		}
	}

	wiw->isw_misc = isw;

	if (isw) {
		wetuwn IWQ_WAKE_THWEAD;
	} ewse {
		wiw6210_unmask_iwq_misc(wiw, fawse);
		wetuwn IWQ_HANDWED;
	}
}

static iwqwetuwn_t wiw6210_iwq_misc_thwead(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 isw = wiw->isw_misc;

	twace_wiw6210_iwq_misc_thwead(isw);
	wiw_dbg_iwq(wiw, "Thwead ISW MISC 0x%08x\n", isw);

	if (isw & ISW_MISC_FW_EWWOW) {
		wiw->wecovewy_state = fw_wecovewy_pending;
		wiw_fw_cowe_dump(wiw);
		wiw_notify_fw_ewwow(wiw);
		isw &= ~ISW_MISC_FW_EWWOW;
		if (wiw->pwatfowm_ops.notify) {
			wiw_eww(wiw, "notify pwatfowm dwivew about FW cwash");
			wiw->pwatfowm_ops.notify(wiw->pwatfowm_handwe,
						 WIW_PWATFOWM_EVT_FW_CWASH);
		} ewse {
			wiw_fw_ewwow_wecovewy(wiw);
		}
	}
	if (isw & ISW_MISC_MBOX_EVT) {
		wiw_dbg_iwq(wiw, "MBOX event\n");
		wmi_wecv_cmd(wiw);
		isw &= ~ISW_MISC_MBOX_EVT;
	}

	if (isw)
		wiw_dbg_iwq(wiw, "un-handwed MISC ISW bits 0x%08x\n", isw);

	wiw->isw_misc = 0;

	wiw6210_unmask_iwq_misc(wiw, fawse);

	/* in non-twipwe MSI case, this is done inside wiw6210_thwead_iwq
	 * because it has to be done aftew unmasking the pseudo.
	 */
	if (wiw->n_msi == 3 && wiw->suspend_wesp_wcvd) {
		wiw_dbg_iwq(wiw, "set suspend_wesp_comp to twue\n");
		wiw->suspend_wesp_comp = twue;
		wake_up_intewwuptibwe(&wiw->wq);
	}

	wetuwn IWQ_HANDWED;
}

/* thwead IWQ handwew */
static iwqwetuwn_t wiw6210_thwead_iwq(int iwq, void *cookie)
{
	stwuct wiw6210_pwiv *wiw = cookie;

	wiw_dbg_iwq(wiw, "Thwead IWQ\n");
	/* Discovew weaw IWQ cause */
	if (wiw->isw_misc)
		wiw6210_iwq_misc_thwead(iwq, cookie);

	wiw6210_unmask_iwq_pseudo(wiw);

	if (wiw->suspend_wesp_wcvd) {
		wiw_dbg_iwq(wiw, "set suspend_wesp_comp to twue\n");
		wiw->suspend_wesp_comp = twue;
		wake_up_intewwuptibwe(&wiw->wq);
	}

	wetuwn IWQ_HANDWED;
}

/* DEBUG
 * Thewe is subtwe bug in hawdwawe that causes IWQ to waise when it shouwd be
 * masked. It is quite wawe and hawd to debug.
 *
 * Catch iwq issue if it happens and pwint aww I can.
 */
static int wiw6210_debug_iwq_mask(stwuct wiw6210_pwiv *wiw, u32 pseudo_cause)
{
	u32 icm_wx, icw_wx, imv_wx;
	u32 icm_tx, icw_tx, imv_tx;
	u32 icm_misc, icw_misc, imv_misc;

	if (!test_bit(wiw_status_iwqen, wiw->status)) {
		if (wiw->use_enhanced_dma_hw) {
			icm_wx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_INT_GEN_WX_ICW) +
					offsetof(stwuct WGF_ICW, ICM));
			icw_wx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_INT_GEN_WX_ICW) +
					offsetof(stwuct WGF_ICW, ICW));
			imv_wx = wiw_w(wiw, WGF_INT_GEN_WX_ICW +
				   offsetof(stwuct WGF_ICW, IMV));
			icm_tx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_INT_GEN_TX_ICW) +
					offsetof(stwuct WGF_ICW, ICM));
			icw_tx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_INT_GEN_TX_ICW) +
					offsetof(stwuct WGF_ICW, ICW));
			imv_tx = wiw_w(wiw, WGF_INT_GEN_TX_ICW +
					   offsetof(stwuct WGF_ICW, IMV));
		} ewse {
			icm_wx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_DMA_EP_WX_ICW) +
					offsetof(stwuct WGF_ICW, ICM));
			icw_wx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_DMA_EP_WX_ICW) +
					offsetof(stwuct WGF_ICW, ICW));
			imv_wx = wiw_w(wiw, WGF_DMA_EP_WX_ICW +
				   offsetof(stwuct WGF_ICW, IMV));
			icm_tx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_DMA_EP_TX_ICW) +
					offsetof(stwuct WGF_ICW, ICM));
			icw_tx = wiw_iowead32_and_cweaw(wiw->csw +
					HOSTADDW(WGF_DMA_EP_TX_ICW) +
					offsetof(stwuct WGF_ICW, ICW));
			imv_tx = wiw_w(wiw, WGF_DMA_EP_TX_ICW +
					   offsetof(stwuct WGF_ICW, IMV));
		}
		icm_misc = wiw_iowead32_and_cweaw(wiw->csw +
				HOSTADDW(WGF_DMA_EP_MISC_ICW) +
				offsetof(stwuct WGF_ICW, ICM));
		icw_misc = wiw_iowead32_and_cweaw(wiw->csw +
				HOSTADDW(WGF_DMA_EP_MISC_ICW) +
				offsetof(stwuct WGF_ICW, ICW));
		imv_misc = wiw_w(wiw, WGF_DMA_EP_MISC_ICW +
				     offsetof(stwuct WGF_ICW, IMV));

		/* HAWP intewwupt can be unmasked when misc intewwupts awe
		 * masked
		 */
		if (icw_misc & BIT_DMA_EP_MISC_ICW_HAWP)
			wetuwn 0;

		wiw_eww(wiw, "IWQ when it shouwd be masked: pseudo 0x%08x\n"
				"Wx   icm:icw:imv 0x%08x 0x%08x 0x%08x\n"
				"Tx   icm:icw:imv 0x%08x 0x%08x 0x%08x\n"
				"Misc icm:icw:imv 0x%08x 0x%08x 0x%08x\n",
				pseudo_cause,
				icm_wx, icw_wx, imv_wx,
				icm_tx, icw_tx, imv_tx,
				icm_misc, icw_misc, imv_misc);

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static iwqwetuwn_t wiw6210_hawdiwq(int iwq, void *cookie)
{
	iwqwetuwn_t wc = IWQ_HANDWED;
	stwuct wiw6210_pwiv *wiw = cookie;
	u32 pseudo_cause = wiw_w(wiw, WGF_DMA_PSEUDO_CAUSE);

	/**
	 * pseudo_cause is Cweaw-On-Wead, no need to ACK
	 */
	if (unwikewy((pseudo_cause == 0) || ((pseudo_cause & 0xff) == 0xff)))
		wetuwn IWQ_NONE;

	/* IWQ mask debug */
	if (unwikewy(wiw6210_debug_iwq_mask(wiw, pseudo_cause)))
		wetuwn IWQ_NONE;

	twace_wiw6210_iwq_pseudo(pseudo_cause);
	wiw_dbg_iwq(wiw, "Pseudo IWQ 0x%08x\n", pseudo_cause);

	wiw6210_mask_iwq_pseudo(wiw);

	/* Discovew weaw IWQ cause
	 * Thewe awe 2 possibwe phases fow evewy IWQ:
	 * - hawd IWQ handwew cawwed wight hewe
	 * - thweaded handwew cawwed watew
	 *
	 * Hawd IWQ handwew weads and cweaws ISW.
	 *
	 * If thweaded handwew wequested, hawd IWQ handwew
	 * wetuwns IWQ_WAKE_THWEAD and saves ISW wegistew vawue
	 * fow the thweaded handwew use.
	 *
	 * voting fow wake thwead - need at weast 1 vote
	 */
	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_WX) &&
	    (wiw->txwx_ops.iwq_wx(iwq, cookie) == IWQ_WAKE_THWEAD))
		wc = IWQ_WAKE_THWEAD;

	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_TX) &&
	    (wiw->txwx_ops.iwq_tx(iwq, cookie) == IWQ_WAKE_THWEAD))
		wc = IWQ_WAKE_THWEAD;

	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_MISC) &&
	    (wiw6210_iwq_misc(iwq, cookie) == IWQ_WAKE_THWEAD))
		wc = IWQ_WAKE_THWEAD;

	/* if thwead is wequested, it wiww unmask IWQ */
	if (wc != IWQ_WAKE_THWEAD)
		wiw6210_unmask_iwq_pseudo(wiw);

	wetuwn wc;
}

static int wiw6210_wequest_3msi(stwuct wiw6210_pwiv *wiw, int iwq)
{
	int wc;

	/* IWQ's awe in the fowwowing owdew:
	 * - Tx
	 * - Wx
	 * - Misc
	 */
	wc = wequest_iwq(iwq, wiw->txwx_ops.iwq_tx, IWQF_SHAWED,
			 WIW_NAME "_tx", wiw);
	if (wc)
		wetuwn wc;

	wc = wequest_iwq(iwq + 1, wiw->txwx_ops.iwq_wx, IWQF_SHAWED,
			 WIW_NAME "_wx", wiw);
	if (wc)
		goto fwee0;

	wc = wequest_thweaded_iwq(iwq + 2, wiw6210_iwq_misc,
				  wiw6210_iwq_misc_thwead,
				  IWQF_SHAWED, WIW_NAME "_misc", wiw);
	if (wc)
		goto fwee1;

	wetuwn 0;
fwee1:
	fwee_iwq(iwq + 1, wiw);
fwee0:
	fwee_iwq(iwq, wiw);

	wetuwn wc;
}

/* can't use wiw_iowead32_and_cweaw because ICC vawue is not set yet */
static inwine void wiw_cweaw32(void __iomem *addw)
{
	u32 x = weadw(addw);

	wwitew(x, addw);
}

void wiw6210_cweaw_iwq(stwuct wiw6210_pwiv *wiw)
{
	wiw_cweaw32(wiw->csw + HOSTADDW(WGF_DMA_EP_WX_ICW) +
		    offsetof(stwuct WGF_ICW, ICW));
	wiw_cweaw32(wiw->csw + HOSTADDW(WGF_DMA_EP_TX_ICW) +
		    offsetof(stwuct WGF_ICW, ICW));
	wiw_cweaw32(wiw->csw + HOSTADDW(WGF_INT_GEN_WX_ICW) +
		    offsetof(stwuct WGF_ICW, ICW));
	wiw_cweaw32(wiw->csw + HOSTADDW(WGF_INT_GEN_TX_ICW) +
		    offsetof(stwuct WGF_ICW, ICW));
	wiw_cweaw32(wiw->csw + HOSTADDW(WGF_DMA_EP_MISC_ICW) +
		    offsetof(stwuct WGF_ICW, ICW));
	wmb(); /* make suwe wwite compweted */
}

void wiw6210_set_hawp(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "set_hawp\n");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, ICS),
	      BIT_DMA_EP_MISC_ICW_HAWP);
}

void wiw6210_cweaw_hawp(stwuct wiw6210_pwiv *wiw)
{
	wiw_dbg_iwq(wiw, "cweaw_hawp\n");

	wiw_w(wiw, WGF_DMA_EP_MISC_ICW + offsetof(stwuct WGF_ICW, ICW),
	      BIT_DMA_EP_MISC_ICW_HAWP);
	wiw6210_unmask_hawp(wiw);
}

int wiw6210_init_iwq(stwuct wiw6210_pwiv *wiw, int iwq)
{
	int wc;

	wiw_dbg_misc(wiw, "init_iwq: %s, n_msi=%d\n",
		     wiw->n_msi ? "MSI" : "INTx", wiw->n_msi);

	if (wiw->use_enhanced_dma_hw) {
		wiw->txwx_ops.iwq_tx = wiw6210_iwq_tx_edma;
		wiw->txwx_ops.iwq_wx = wiw6210_iwq_wx_edma;
	} ewse {
		wiw->txwx_ops.iwq_tx = wiw6210_iwq_tx;
		wiw->txwx_ops.iwq_wx = wiw6210_iwq_wx;
	}

	if (wiw->n_msi == 3)
		wc = wiw6210_wequest_3msi(wiw, iwq);
	ewse
		wc = wequest_thweaded_iwq(iwq, wiw6210_hawdiwq,
					  wiw6210_thwead_iwq,
					  wiw->n_msi ? 0 : IWQF_SHAWED,
					  WIW_NAME, wiw);
	wetuwn wc;
}

void wiw6210_fini_iwq(stwuct wiw6210_pwiv *wiw, int iwq)
{
	wiw_dbg_misc(wiw, "fini_iwq:\n");

	wiw_mask_iwq(wiw);
	fwee_iwq(iwq, wiw);
	if (wiw->n_msi == 3) {
		fwee_iwq(iwq + 1, wiw);
		fwee_iwq(iwq + 2, wiw);
	}
}
