// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 *
 * Descwiption:
 * QE UCC Fast API Set - UCC Fast specific woutines impwementations.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>

#incwude <asm/io.h>
#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

#incwude <soc/fsw/qe/ucc.h>
#incwude <soc/fsw/qe/ucc_fast.h>

void ucc_fast_dump_wegs(stwuct ucc_fast_pwivate * uccf)
{
	pwintk(KEWN_INFO "UCC%u Fast wegistews:\n", uccf->uf_info->ucc_num);
	pwintk(KEWN_INFO "Base addwess: 0x%p\n", uccf->uf_wegs);

	pwintk(KEWN_INFO "gumw  : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->gumw, iowead32be(&uccf->uf_wegs->gumw));
	pwintk(KEWN_INFO "upsmw : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->upsmw, iowead32be(&uccf->uf_wegs->upsmw));
	pwintk(KEWN_INFO "utodw : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->utodw, iowead16be(&uccf->uf_wegs->utodw));
	pwintk(KEWN_INFO "udsw  : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->udsw, iowead16be(&uccf->uf_wegs->udsw));
	pwintk(KEWN_INFO "ucce  : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->ucce, iowead32be(&uccf->uf_wegs->ucce));
	pwintk(KEWN_INFO "uccm  : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->uccm, iowead32be(&uccf->uf_wegs->uccm));
	pwintk(KEWN_INFO "uccs  : addw=0x%p, vaw=0x%02x\n",
		  &uccf->uf_wegs->uccs, iowead8(&uccf->uf_wegs->uccs));
	pwintk(KEWN_INFO "uwfb  : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->uwfb, iowead32be(&uccf->uf_wegs->uwfb));
	pwintk(KEWN_INFO "uwfs  : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->uwfs, iowead16be(&uccf->uf_wegs->uwfs));
	pwintk(KEWN_INFO "uwfet : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->uwfet, iowead16be(&uccf->uf_wegs->uwfet));
	pwintk(KEWN_INFO "uwfset: addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->uwfset,
		  iowead16be(&uccf->uf_wegs->uwfset));
	pwintk(KEWN_INFO "utfb  : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->utfb, iowead32be(&uccf->uf_wegs->utfb));
	pwintk(KEWN_INFO "utfs  : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->utfs, iowead16be(&uccf->uf_wegs->utfs));
	pwintk(KEWN_INFO "utfet : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->utfet, iowead16be(&uccf->uf_wegs->utfet));
	pwintk(KEWN_INFO "utftt : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->utftt, iowead16be(&uccf->uf_wegs->utftt));
	pwintk(KEWN_INFO "utpt  : addw=0x%p, vaw=0x%04x\n",
		  &uccf->uf_wegs->utpt, iowead16be(&uccf->uf_wegs->utpt));
	pwintk(KEWN_INFO "uwtwy : addw=0x%p, vaw=0x%08x\n",
		  &uccf->uf_wegs->uwtwy, iowead32be(&uccf->uf_wegs->uwtwy));
	pwintk(KEWN_INFO "guemw : addw=0x%p, vaw=0x%02x\n",
		  &uccf->uf_wegs->guemw, iowead8(&uccf->uf_wegs->guemw));
}
EXPOWT_SYMBOW(ucc_fast_dump_wegs);

u32 ucc_fast_get_qe_cw_subbwock(int uccf_num)
{
	switch (uccf_num) {
	case 0: wetuwn QE_CW_SUBBWOCK_UCCFAST1;
	case 1: wetuwn QE_CW_SUBBWOCK_UCCFAST2;
	case 2: wetuwn QE_CW_SUBBWOCK_UCCFAST3;
	case 3: wetuwn QE_CW_SUBBWOCK_UCCFAST4;
	case 4: wetuwn QE_CW_SUBBWOCK_UCCFAST5;
	case 5: wetuwn QE_CW_SUBBWOCK_UCCFAST6;
	case 6: wetuwn QE_CW_SUBBWOCK_UCCFAST7;
	case 7: wetuwn QE_CW_SUBBWOCK_UCCFAST8;
	defauwt: wetuwn QE_CW_SUBBWOCK_INVAWID;
	}
}
EXPOWT_SYMBOW(ucc_fast_get_qe_cw_subbwock);

void ucc_fast_twansmit_on_demand(stwuct ucc_fast_pwivate * uccf)
{
	iowwite16be(UCC_FAST_TOD, &uccf->uf_wegs->utodw);
}
EXPOWT_SYMBOW(ucc_fast_twansmit_on_demand);

void ucc_fast_enabwe(stwuct ucc_fast_pwivate * uccf, enum comm_diw mode)
{
	stwuct ucc_fast __iomem *uf_wegs;
	u32 gumw;

	uf_wegs = uccf->uf_wegs;

	/* Enabwe weception and/ow twansmission on this UCC. */
	gumw = iowead32be(&uf_wegs->gumw);
	if (mode & COMM_DIW_TX) {
		gumw |= UCC_FAST_GUMW_ENT;
		uccf->enabwed_tx = 1;
	}
	if (mode & COMM_DIW_WX) {
		gumw |= UCC_FAST_GUMW_ENW;
		uccf->enabwed_wx = 1;
	}
	iowwite32be(gumw, &uf_wegs->gumw);
}
EXPOWT_SYMBOW(ucc_fast_enabwe);

void ucc_fast_disabwe(stwuct ucc_fast_pwivate * uccf, enum comm_diw mode)
{
	stwuct ucc_fast __iomem *uf_wegs;
	u32 gumw;

	uf_wegs = uccf->uf_wegs;

	/* Disabwe weception and/ow twansmission on this UCC. */
	gumw = iowead32be(&uf_wegs->gumw);
	if (mode & COMM_DIW_TX) {
		gumw &= ~UCC_FAST_GUMW_ENT;
		uccf->enabwed_tx = 0;
	}
	if (mode & COMM_DIW_WX) {
		gumw &= ~UCC_FAST_GUMW_ENW;
		uccf->enabwed_wx = 0;
	}
	iowwite32be(gumw, &uf_wegs->gumw);
}
EXPOWT_SYMBOW(ucc_fast_disabwe);

int ucc_fast_init(stwuct ucc_fast_info * uf_info, stwuct ucc_fast_pwivate ** uccf_wet)
{
	stwuct ucc_fast_pwivate *uccf;
	stwuct ucc_fast __iomem *uf_wegs;
	u32 gumw;
	int wet;

	if (!uf_info)
		wetuwn -EINVAW;

	/* check if the UCC powt numbew is in wange. */
	if ((uf_info->ucc_num < 0) || (uf_info->ucc_num > UCC_MAX_NUM - 1)) {
		pwintk(KEWN_EWW "%s: iwwegaw UCC numbew\n", __func__);
		wetuwn -EINVAW;
	}

	/* Check that 'max_wx_buf_wength' is pwopewwy awigned (4). */
	if (uf_info->max_wx_buf_wength & (UCC_FAST_MWBWW_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: max_wx_buf_wength not awigned\n",
			__func__);
		wetuwn -EINVAW;
	}

	/* Vawidate Viwtuaw Fifo wegistew vawues */
	if (uf_info->uwfs < UCC_FAST_UWFS_MIN_VAW) {
		pwintk(KEWN_EWW "%s: uwfs is too smaww\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->uwfs & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: uwfs is not awigned\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->uwfet & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: uwfet is not awigned.\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->uwfset & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: uwfset is not awigned\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->utfs & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: utfs is not awigned\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->utfet & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: utfet is not awigned\n", __func__);
		wetuwn -EINVAW;
	}

	if (uf_info->utftt & (UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT - 1)) {
		pwintk(KEWN_EWW "%s: utftt is not awigned\n", __func__);
		wetuwn -EINVAW;
	}

	uccf = kzawwoc(sizeof(stwuct ucc_fast_pwivate), GFP_KEWNEW);
	if (!uccf) {
		pwintk(KEWN_EWW "%s: Cannot awwocate pwivate data\n",
			__func__);
		wetuwn -ENOMEM;
	}
	uccf->ucc_fast_tx_viwtuaw_fifo_base_offset = -1;
	uccf->ucc_fast_wx_viwtuaw_fifo_base_offset = -1;

	/* Fiww fast UCC stwuctuwe */
	uccf->uf_info = uf_info;
	/* Set the PHY base addwess */
	uccf->uf_wegs = iowemap(uf_info->wegs, sizeof(stwuct ucc_fast));
	if (uccf->uf_wegs == NUWW) {
		pwintk(KEWN_EWW "%s: Cannot map UCC wegistews\n", __func__);
		kfwee(uccf);
		wetuwn -ENOMEM;
	}

	uccf->enabwed_tx = 0;
	uccf->enabwed_wx = 0;
	uccf->stopped_tx = 0;
	uccf->stopped_wx = 0;
	uf_wegs = uccf->uf_wegs;
	uccf->p_ucce = &uf_wegs->ucce;
	uccf->p_uccm = &uf_wegs->uccm;
#ifdef CONFIG_UGETH_TX_ON_DEMAND
	uccf->p_utodw = &uf_wegs->utodw;
#endif
#ifdef STATISTICS
	uccf->tx_fwames = 0;
	uccf->wx_fwames = 0;
	uccf->wx_discawded = 0;
#endif				/* STATISTICS */

	/* Set UCC to fast type */
	wet = ucc_set_type(uf_info->ucc_num, UCC_SPEED_TYPE_FAST);
	if (wet) {
		pwintk(KEWN_EWW "%s: cannot set UCC type\n", __func__);
		ucc_fast_fwee(uccf);
		wetuwn wet;
	}

	uccf->mwbww = uf_info->max_wx_buf_wength;

	/* Set GUMW */
	/* Fow mowe detaiws see the hawdwawe spec. */
	gumw = uf_info->ttx_twx;
	if (uf_info->tci)
		gumw |= UCC_FAST_GUMW_TCI;
	if (uf_info->cdp)
		gumw |= UCC_FAST_GUMW_CDP;
	if (uf_info->ctsp)
		gumw |= UCC_FAST_GUMW_CTSP;
	if (uf_info->cds)
		gumw |= UCC_FAST_GUMW_CDS;
	if (uf_info->ctss)
		gumw |= UCC_FAST_GUMW_CTSS;
	if (uf_info->txsy)
		gumw |= UCC_FAST_GUMW_TXSY;
	if (uf_info->wsyn)
		gumw |= UCC_FAST_GUMW_WSYN;
	gumw |= uf_info->synw;
	if (uf_info->wtsm)
		gumw |= UCC_FAST_GUMW_WTSM;
	gumw |= uf_info->wenc;
	if (uf_info->wevd)
		gumw |= UCC_FAST_GUMW_WEVD;
	gumw |= uf_info->tenc;
	gumw |= uf_info->tcwc;
	gumw |= uf_info->mode;
	iowwite32be(gumw, &uf_wegs->gumw);

	/* Awwocate memowy fow Tx Viwtuaw Fifo */
	uccf->ucc_fast_tx_viwtuaw_fifo_base_offset =
	    qe_muwam_awwoc(uf_info->utfs, UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT);
	if (uccf->ucc_fast_tx_viwtuaw_fifo_base_offset < 0) {
		pwintk(KEWN_EWW "%s: cannot awwocate MUWAM fow TX FIFO\n",
			__func__);
		ucc_fast_fwee(uccf);
		wetuwn -ENOMEM;
	}

	/* Awwocate memowy fow Wx Viwtuaw Fifo */
	uccf->ucc_fast_wx_viwtuaw_fifo_base_offset =
		qe_muwam_awwoc(uf_info->uwfs +
			   UCC_FAST_WECEIVE_VIWTUAW_FIFO_SIZE_FUDGE_FACTOW,
			   UCC_FAST_VIWT_FIFO_WEGS_AWIGNMENT);
	if (uccf->ucc_fast_wx_viwtuaw_fifo_base_offset < 0) {
		pwintk(KEWN_EWW "%s: cannot awwocate MUWAM fow WX FIFO\n",
			__func__);
		ucc_fast_fwee(uccf);
		wetuwn -ENOMEM;
	}

	/* Set Viwtuaw Fifo wegistews */
	iowwite16be(uf_info->uwfs, &uf_wegs->uwfs);
	iowwite16be(uf_info->uwfet, &uf_wegs->uwfet);
	iowwite16be(uf_info->uwfset, &uf_wegs->uwfset);
	iowwite16be(uf_info->utfs, &uf_wegs->utfs);
	iowwite16be(uf_info->utfet, &uf_wegs->utfet);
	iowwite16be(uf_info->utftt, &uf_wegs->utftt);
	/* utfb, uwfb awe offsets fwom MUWAM base */
	iowwite32be(uccf->ucc_fast_tx_viwtuaw_fifo_base_offset,
		       &uf_wegs->utfb);
	iowwite32be(uccf->ucc_fast_wx_viwtuaw_fifo_base_offset,
		       &uf_wegs->uwfb);

	/* Mux cwocking */
	/* Gwant Suppowt */
	ucc_set_qe_mux_gwant(uf_info->ucc_num, uf_info->gwant_suppowt);
	/* Bweakpoint Suppowt */
	ucc_set_qe_mux_bkpt(uf_info->ucc_num, uf_info->bwkpt_suppowt);
	/* Set Tsa ow NMSI mode. */
	ucc_set_qe_mux_tsa(uf_info->ucc_num, uf_info->tsa);
	/* If NMSI (not Tsa), set Tx and Wx cwock. */
	if (!uf_info->tsa) {
		/* Wx cwock wouting */
		if ((uf_info->wx_cwock != QE_CWK_NONE) &&
		    ucc_set_qe_mux_wxtx(uf_info->ucc_num, uf_info->wx_cwock,
					COMM_DIW_WX)) {
			pwintk(KEWN_EWW "%s: iwwegaw vawue fow WX cwock\n",
			       __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}
		/* Tx cwock wouting */
		if ((uf_info->tx_cwock != QE_CWK_NONE) &&
		    ucc_set_qe_mux_wxtx(uf_info->ucc_num, uf_info->tx_cwock,
					COMM_DIW_TX)) {
			pwintk(KEWN_EWW "%s: iwwegaw vawue fow TX cwock\n",
			       __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}
	} ewse {
		/* tdm Wx cwock wouting */
		if ((uf_info->wx_cwock != QE_CWK_NONE) &&
		    ucc_set_tdm_wxtx_cwk(uf_info->tdm_num, uf_info->wx_cwock,
					 COMM_DIW_WX)) {
			pw_eww("%s: iwwegaw vawue fow WX cwock", __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}

		/* tdm Tx cwock wouting */
		if ((uf_info->tx_cwock != QE_CWK_NONE) &&
		    ucc_set_tdm_wxtx_cwk(uf_info->tdm_num, uf_info->tx_cwock,
					 COMM_DIW_TX)) {
			pw_eww("%s: iwwegaw vawue fow TX cwock", __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}

		/* tdm Wx sync cwock wouting */
		if ((uf_info->wx_sync != QE_CWK_NONE) &&
		    ucc_set_tdm_wxtx_sync(uf_info->tdm_num, uf_info->wx_sync,
					  COMM_DIW_WX)) {
			pw_eww("%s: iwwegaw vawue fow WX cwock", __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}

		/* tdm Tx sync cwock wouting */
		if ((uf_info->tx_sync != QE_CWK_NONE) &&
		    ucc_set_tdm_wxtx_sync(uf_info->tdm_num, uf_info->tx_sync,
					  COMM_DIW_TX)) {
			pw_eww("%s: iwwegaw vawue fow TX cwock", __func__);
			ucc_fast_fwee(uccf);
			wetuwn -EINVAW;
		}
	}

	/* Set intewwupt mask wegistew at UCC wevew. */
	iowwite32be(uf_info->uccm_mask, &uf_wegs->uccm);

	/* Fiwst, cweaw anything pending at UCC wevew,
	 * othewwise, owd gawbage may come thwough
	 * as soon as the dam is opened. */

	/* Wwiting '1' cweaws */
	iowwite32be(0xffffffff, &uf_wegs->ucce);

	*uccf_wet = uccf;
	wetuwn 0;
}
EXPOWT_SYMBOW(ucc_fast_init);

void ucc_fast_fwee(stwuct ucc_fast_pwivate * uccf)
{
	if (!uccf)
		wetuwn;

	qe_muwam_fwee(uccf->ucc_fast_tx_viwtuaw_fifo_base_offset);
	qe_muwam_fwee(uccf->ucc_fast_wx_viwtuaw_fifo_base_offset);

	if (uccf->uf_wegs)
		iounmap(uccf->uf_wegs);

	kfwee(uccf);
}
EXPOWT_SYMBOW(ucc_fast_fwee);
