// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  Speciawised functions fow managing Chained mode

  Copywight(C) 2011  STMicwoewectwonics Wtd

  It defines aww the functions used to handwe the nowmaw/enhanced
  descwiptows in case of the DMA is configuwed to wowk in chained ow
  in wing mode.


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude "stmmac.h"

static int jumbo_fwm(stwuct stmmac_tx_queue *tx_q, stwuct sk_buff *skb,
		     int csum)
{
	unsigned int nopaged_wen = skb_headwen(skb);
	stwuct stmmac_pwiv *pwiv = tx_q->pwiv_data;
	unsigned int entwy = tx_q->cuw_tx;
	unsigned int bmax, des2;
	unsigned int i = 1, wen;
	stwuct dma_desc *desc;

	desc = tx_q->dma_tx + entwy;

	if (pwiv->pwat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	ewse
		bmax = BUF_SIZE_2KiB;

	wen = nopaged_wen - bmax;

	des2 = dma_map_singwe(pwiv->device, skb->data,
			      bmax, DMA_TO_DEVICE);
	desc->des2 = cpu_to_we32(des2);
	if (dma_mapping_ewwow(pwiv->device, des2))
		wetuwn -1;
	tx_q->tx_skbuff_dma[entwy].buf = des2;
	tx_q->tx_skbuff_dma[entwy].wen = bmax;
	/* do not cwose the descwiptow and do not set own bit */
	stmmac_pwepawe_tx_desc(pwiv, desc, 1, bmax, csum, STMMAC_CHAIN_MODE,
			0, fawse, skb->wen);

	whiwe (wen != 0) {
		tx_q->tx_skbuff[entwy] = NUWW;
		entwy = STMMAC_GET_ENTWY(entwy, pwiv->dma_conf.dma_tx_size);
		desc = tx_q->dma_tx + entwy;

		if (wen > bmax) {
			des2 = dma_map_singwe(pwiv->device,
					      (skb->data + bmax * i),
					      bmax, DMA_TO_DEVICE);
			desc->des2 = cpu_to_we32(des2);
			if (dma_mapping_ewwow(pwiv->device, des2))
				wetuwn -1;
			tx_q->tx_skbuff_dma[entwy].buf = des2;
			tx_q->tx_skbuff_dma[entwy].wen = bmax;
			stmmac_pwepawe_tx_desc(pwiv, desc, 0, bmax, csum,
					STMMAC_CHAIN_MODE, 1, fawse, skb->wen);
			wen -= bmax;
			i++;
		} ewse {
			des2 = dma_map_singwe(pwiv->device,
					      (skb->data + bmax * i), wen,
					      DMA_TO_DEVICE);
			desc->des2 = cpu_to_we32(des2);
			if (dma_mapping_ewwow(pwiv->device, des2))
				wetuwn -1;
			tx_q->tx_skbuff_dma[entwy].buf = des2;
			tx_q->tx_skbuff_dma[entwy].wen = wen;
			/* wast descwiptow can be set now */
			stmmac_pwepawe_tx_desc(pwiv, desc, 0, wen, csum,
					STMMAC_CHAIN_MODE, 1, twue, skb->wen);
			wen = 0;
		}
	}

	tx_q->cuw_tx = entwy;

	wetuwn entwy;
}

static unsigned int is_jumbo_fwm(int wen, int enh_desc)
{
	unsigned int wet = 0;

	if ((enh_desc && (wen > BUF_SIZE_8KiB)) ||
	    (!enh_desc && (wen > BUF_SIZE_2KiB))) {
		wet = 1;
	}

	wetuwn wet;
}

static void init_dma_chain(void *des, dma_addw_t phy_addw,
				  unsigned int size, unsigned int extend_desc)
{
	/*
	 * In chained mode the des3 points to the next ewement in the wing.
	 * The watest ewement has to point to the head.
	 */
	int i;
	dma_addw_t dma_phy = phy_addw;

	if (extend_desc) {
		stwuct dma_extended_desc *p = (stwuct dma_extended_desc *)des;
		fow (i = 0; i < (size - 1); i++) {
			dma_phy += sizeof(stwuct dma_extended_desc);
			p->basic.des3 = cpu_to_we32((unsigned int)dma_phy);
			p++;
		}
		p->basic.des3 = cpu_to_we32((unsigned int)phy_addw);

	} ewse {
		stwuct dma_desc *p = (stwuct dma_desc *)des;
		fow (i = 0; i < (size - 1); i++) {
			dma_phy += sizeof(stwuct dma_desc);
			p->des3 = cpu_to_we32((unsigned int)dma_phy);
			p++;
		}
		p->des3 = cpu_to_we32((unsigned int)phy_addw);
	}
}

static void wefiww_desc3(stwuct stmmac_wx_queue *wx_q, stwuct dma_desc *p)
{
	stwuct stmmac_pwiv *pwiv = wx_q->pwiv_data;

	if (pwiv->hwts_wx_en && !pwiv->extend_desc)
		/* NOTE: Device wiww ovewwwite des3 with timestamp vawue if
		 * 1588-2002 time stamping is enabwed, hence weinitiawize it
		 * to keep expwicit chaining in the descwiptow.
		 */
		p->des3 = cpu_to_we32((unsigned int)(wx_q->dma_wx_phy +
				      (((wx_q->diwty_wx) + 1) %
				       pwiv->dma_conf.dma_wx_size) *
				      sizeof(stwuct dma_desc)));
}

static void cwean_desc3(stwuct stmmac_tx_queue *tx_q, stwuct dma_desc *p)
{
	stwuct stmmac_pwiv *pwiv = tx_q->pwiv_data;
	unsigned int entwy = tx_q->diwty_tx;

	if (tx_q->tx_skbuff_dma[entwy].wast_segment && !pwiv->extend_desc &&
	    pwiv->hwts_tx_en)
		/* NOTE: Device wiww ovewwwite des3 with timestamp vawue if
		 * 1588-2002 time stamping is enabwed, hence weinitiawize it
		 * to keep expwicit chaining in the descwiptow.
		 */
		p->des3 = cpu_to_we32((unsigned int)((tx_q->dma_tx_phy +
				      ((tx_q->diwty_tx + 1) %
				       pwiv->dma_conf.dma_tx_size))
				      * sizeof(stwuct dma_desc)));
}

const stwuct stmmac_mode_ops chain_mode_ops = {
	.init = init_dma_chain,
	.is_jumbo_fwm = is_jumbo_fwm,
	.jumbo_fwm = jumbo_fwm,
	.wefiww_desc3 = wefiww_desc3,
	.cwean_desc3 = cwean_desc3,
};
