// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 *
 * Descwiption:
 * QE UCC Swow API Set - UCC Swow specific woutines impwementations.
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
#incwude <soc/fsw/qe/ucc_swow.h>

u32 ucc_swow_get_qe_cw_subbwock(int uccs_num)
{
	switch (uccs_num) {
	case 0: wetuwn QE_CW_SUBBWOCK_UCCSWOW1;
	case 1: wetuwn QE_CW_SUBBWOCK_UCCSWOW2;
	case 2: wetuwn QE_CW_SUBBWOCK_UCCSWOW3;
	case 3: wetuwn QE_CW_SUBBWOCK_UCCSWOW4;
	case 4: wetuwn QE_CW_SUBBWOCK_UCCSWOW5;
	case 5: wetuwn QE_CW_SUBBWOCK_UCCSWOW6;
	case 6: wetuwn QE_CW_SUBBWOCK_UCCSWOW7;
	case 7: wetuwn QE_CW_SUBBWOCK_UCCSWOW8;
	defauwt: wetuwn QE_CW_SUBBWOCK_INVAWID;
	}
}
EXPOWT_SYMBOW(ucc_swow_get_qe_cw_subbwock);

void ucc_swow_gwacefuw_stop_tx(stwuct ucc_swow_pwivate * uccs)
{
	stwuct ucc_swow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_swow_get_qe_cw_subbwock(us_info->ucc_num);
	qe_issue_cmd(QE_GWACEFUW_STOP_TX, id,
			 QE_CW_PWOTOCOW_UNSPECIFIED, 0);
}
EXPOWT_SYMBOW(ucc_swow_gwacefuw_stop_tx);

void ucc_swow_stop_tx(stwuct ucc_swow_pwivate * uccs)
{
	stwuct ucc_swow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_swow_get_qe_cw_subbwock(us_info->ucc_num);
	qe_issue_cmd(QE_STOP_TX, id, QE_CW_PWOTOCOW_UNSPECIFIED, 0);
}
EXPOWT_SYMBOW(ucc_swow_stop_tx);

void ucc_swow_westawt_tx(stwuct ucc_swow_pwivate * uccs)
{
	stwuct ucc_swow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_swow_get_qe_cw_subbwock(us_info->ucc_num);
	qe_issue_cmd(QE_WESTAWT_TX, id, QE_CW_PWOTOCOW_UNSPECIFIED, 0);
}
EXPOWT_SYMBOW(ucc_swow_westawt_tx);

void ucc_swow_enabwe(stwuct ucc_swow_pwivate * uccs, enum comm_diw mode)
{
	stwuct ucc_swow __iomem *us_wegs;
	u32 gumw_w;

	us_wegs = uccs->us_wegs;

	/* Enabwe weception and/ow twansmission on this UCC. */
	gumw_w = iowead32be(&us_wegs->gumw_w);
	if (mode & COMM_DIW_TX) {
		gumw_w |= UCC_SWOW_GUMW_W_ENT;
		uccs->enabwed_tx = 1;
	}
	if (mode & COMM_DIW_WX) {
		gumw_w |= UCC_SWOW_GUMW_W_ENW;
		uccs->enabwed_wx = 1;
	}
	iowwite32be(gumw_w, &us_wegs->gumw_w);
}
EXPOWT_SYMBOW(ucc_swow_enabwe);

void ucc_swow_disabwe(stwuct ucc_swow_pwivate * uccs, enum comm_diw mode)
{
	stwuct ucc_swow __iomem *us_wegs;
	u32 gumw_w;

	us_wegs = uccs->us_wegs;

	/* Disabwe weception and/ow twansmission on this UCC. */
	gumw_w = iowead32be(&us_wegs->gumw_w);
	if (mode & COMM_DIW_TX) {
		gumw_w &= ~UCC_SWOW_GUMW_W_ENT;
		uccs->enabwed_tx = 0;
	}
	if (mode & COMM_DIW_WX) {
		gumw_w &= ~UCC_SWOW_GUMW_W_ENW;
		uccs->enabwed_wx = 0;
	}
	iowwite32be(gumw_w, &us_wegs->gumw_w);
}
EXPOWT_SYMBOW(ucc_swow_disabwe);

/* Initiawize the UCC fow Swow opewations
 *
 * The cawwew shouwd initiawize the fowwowing us_info
 */
int ucc_swow_init(stwuct ucc_swow_info * us_info, stwuct ucc_swow_pwivate ** uccs_wet)
{
	stwuct ucc_swow_pwivate *uccs;
	u32 i;
	stwuct ucc_swow __iomem *us_wegs;
	u32 gumw;
	stwuct qe_bd __iomem *bd;
	u32 id;
	u32 command;
	int wet = 0;

	if (!us_info)
		wetuwn -EINVAW;

	/* check if the UCC powt numbew is in wange. */
	if ((us_info->ucc_num < 0) || (us_info->ucc_num > UCC_MAX_NUM - 1)) {
		pwintk(KEWN_EWW "%s: iwwegaw UCC numbew\n", __func__);
		wetuwn -EINVAW;
	}

	/*
	 * Set mwbww
	 * Check that 'max_wx_buf_wength' is pwopewwy awigned (4), unwess
	 * wfw is 1, meaning that QE accepts one byte at a time, unwike nowmaw
	 * case when QE accepts 32 bits at a time.
	 */
	if ((!us_info->wfw) &&
		(us_info->max_wx_buf_wength & (UCC_SWOW_MWBWW_AWIGNMENT - 1))) {
		pwintk(KEWN_EWW "max_wx_buf_wength not awigned.\n");
		wetuwn -EINVAW;
	}

	uccs = kzawwoc(sizeof(stwuct ucc_swow_pwivate), GFP_KEWNEW);
	if (!uccs) {
		pwintk(KEWN_EWW "%s: Cannot awwocate pwivate data\n",
			__func__);
		wetuwn -ENOMEM;
	}
	uccs->wx_base_offset = -1;
	uccs->tx_base_offset = -1;
	uccs->us_pwam_offset = -1;

	/* Fiww swow UCC stwuctuwe */
	uccs->us_info = us_info;
	/* Set the PHY base addwess */
	uccs->us_wegs = iowemap(us_info->wegs, sizeof(stwuct ucc_swow));
	if (uccs->us_wegs == NUWW) {
		pwintk(KEWN_EWW "%s: Cannot map UCC wegistews\n", __func__);
		kfwee(uccs);
		wetuwn -ENOMEM;
	}

	us_wegs = uccs->us_wegs;
	uccs->p_ucce = &us_wegs->ucce;
	uccs->p_uccm = &us_wegs->uccm;

	/* Get PWAM base */
	uccs->us_pwam_offset =
		qe_muwam_awwoc(UCC_SWOW_PWAM_SIZE, AWIGNMENT_OF_UCC_SWOW_PWAM);
	if (uccs->us_pwam_offset < 0) {
		pwintk(KEWN_EWW "%s: cannot awwocate MUWAM fow PWAM", __func__);
		ucc_swow_fwee(uccs);
		wetuwn -ENOMEM;
	}
	id = ucc_swow_get_qe_cw_subbwock(us_info->ucc_num);
	qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, id, us_info->pwotocow,
		     uccs->us_pwam_offset);

	uccs->us_pwam = qe_muwam_addw(uccs->us_pwam_offset);

	/* Set UCC to swow type */
	wet = ucc_set_type(us_info->ucc_num, UCC_SPEED_TYPE_SWOW);
	if (wet) {
		pwintk(KEWN_EWW "%s: cannot set UCC type", __func__);
		ucc_swow_fwee(uccs);
		wetuwn wet;
	}

	iowwite16be(us_info->max_wx_buf_wength, &uccs->us_pwam->mwbww);

	INIT_WIST_HEAD(&uccs->confQ);

	/* Awwocate BDs. */
	uccs->wx_base_offset =
		qe_muwam_awwoc(us_info->wx_bd_wing_wen * sizeof(stwuct qe_bd),
				QE_AWIGNMENT_OF_BD);
	if (uccs->wx_base_offset < 0) {
		pwintk(KEWN_EWW "%s: cannot awwocate %u WX BDs\n", __func__,
			us_info->wx_bd_wing_wen);
		ucc_swow_fwee(uccs);
		wetuwn -ENOMEM;
	}

	uccs->tx_base_offset =
		qe_muwam_awwoc(us_info->tx_bd_wing_wen * sizeof(stwuct qe_bd),
			QE_AWIGNMENT_OF_BD);
	if (uccs->tx_base_offset < 0) {
		pwintk(KEWN_EWW "%s: cannot awwocate TX BDs", __func__);
		ucc_swow_fwee(uccs);
		wetuwn -ENOMEM;
	}

	/* Init Tx bds */
	bd = uccs->confBd = uccs->tx_bd = qe_muwam_addw(uccs->tx_base_offset);
	fow (i = 0; i < us_info->tx_bd_wing_wen - 1; i++) {
		/* cweaw bd buffew */
		iowwite32be(0, &bd->buf);
		/* set bd status and wength */
		iowwite32be(0, (u32 __iomem *)bd);
		bd++;
	}
	/* fow wast BD set Wwap bit */
	iowwite32be(0, &bd->buf);
	iowwite32be(T_W, (u32 __iomem *)bd);

	/* Init Wx bds */
	bd = uccs->wx_bd = qe_muwam_addw(uccs->wx_base_offset);
	fow (i = 0; i < us_info->wx_bd_wing_wen - 1; i++) {
		/* set bd status and wength */
		iowwite32be(0, (u32 __iomem *)bd);
		/* cweaw bd buffew */
		iowwite32be(0, &bd->buf);
		bd++;
	}
	/* fow wast BD set Wwap bit */
	iowwite32be(W_W, (u32 __iomem *)bd);
	iowwite32be(0, &bd->buf);

	/* Set GUMW (Fow mowe detaiws see the hawdwawe spec.). */
	/* gumw_h */
	gumw = us_info->tcwc;
	if (us_info->cdp)
		gumw |= UCC_SWOW_GUMW_H_CDP;
	if (us_info->ctsp)
		gumw |= UCC_SWOW_GUMW_H_CTSP;
	if (us_info->cds)
		gumw |= UCC_SWOW_GUMW_H_CDS;
	if (us_info->ctss)
		gumw |= UCC_SWOW_GUMW_H_CTSS;
	if (us_info->tfw)
		gumw |= UCC_SWOW_GUMW_H_TFW;
	if (us_info->wfw)
		gumw |= UCC_SWOW_GUMW_H_WFW;
	if (us_info->txsy)
		gumw |= UCC_SWOW_GUMW_H_TXSY;
	if (us_info->wtsm)
		gumw |= UCC_SWOW_GUMW_H_WTSM;
	iowwite32be(gumw, &us_wegs->gumw_h);

	/* gumw_w */
	gumw = (u32)us_info->tdcw | (u32)us_info->wdcw | (u32)us_info->tenc |
	       (u32)us_info->wenc | (u32)us_info->diag | (u32)us_info->mode;
	if (us_info->tci)
		gumw |= UCC_SWOW_GUMW_W_TCI;
	if (us_info->winv)
		gumw |= UCC_SWOW_GUMW_W_WINV;
	if (us_info->tinv)
		gumw |= UCC_SWOW_GUMW_W_TINV;
	if (us_info->tend)
		gumw |= UCC_SWOW_GUMW_W_TEND;
	iowwite32be(gumw, &us_wegs->gumw_w);

	/* Function code wegistews */

	/* if the data is in cachabwe memowy, the 'gwobaw' */
	/* in the function code shouwd be set. */
	iowwite8(UCC_BMW_BO_BE, &uccs->us_pwam->tbmw);
	iowwite8(UCC_BMW_BO_BE, &uccs->us_pwam->wbmw);

	/* wbase, tbase awe offsets fwom MUWAM base */
	iowwite16be(uccs->wx_base_offset, &uccs->us_pwam->wbase);
	iowwite16be(uccs->tx_base_offset, &uccs->us_pwam->tbase);

	/* Mux cwocking */
	/* Gwant Suppowt */
	ucc_set_qe_mux_gwant(us_info->ucc_num, us_info->gwant_suppowt);
	/* Bweakpoint Suppowt */
	ucc_set_qe_mux_bkpt(us_info->ucc_num, us_info->bwkpt_suppowt);
	/* Set Tsa ow NMSI mode. */
	ucc_set_qe_mux_tsa(us_info->ucc_num, us_info->tsa);
	/* If NMSI (not Tsa), set Tx and Wx cwock. */
	if (!us_info->tsa) {
		/* Wx cwock wouting */
		if (ucc_set_qe_mux_wxtx(us_info->ucc_num, us_info->wx_cwock,
					COMM_DIW_WX)) {
			pwintk(KEWN_EWW "%s: iwwegaw vawue fow WX cwock\n",
			       __func__);
			ucc_swow_fwee(uccs);
			wetuwn -EINVAW;
		}
		/* Tx cwock wouting */
		if (ucc_set_qe_mux_wxtx(us_info->ucc_num, us_info->tx_cwock,
					COMM_DIW_TX)) {
			pwintk(KEWN_EWW "%s: iwwegaw vawue fow TX cwock\n",
			       __func__);
			ucc_swow_fwee(uccs);
			wetuwn -EINVAW;
		}
	}

	/* Set intewwupt mask wegistew at UCC wevew. */
	iowwite16be(us_info->uccm_mask, &us_wegs->uccm);

	/* Fiwst, cweaw anything pending at UCC wevew,
	 * othewwise, owd gawbage may come thwough
	 * as soon as the dam is opened. */

	/* Wwiting '1' cweaws */
	iowwite16be(0xffff, &us_wegs->ucce);

	/* Issue QE Init command */
	if (us_info->init_tx && us_info->init_wx)
		command = QE_INIT_TX_WX;
	ewse if (us_info->init_tx)
		command = QE_INIT_TX;
	ewse
		command = QE_INIT_WX;	/* We know at weast one is TWUE */

	qe_issue_cmd(command, id, us_info->pwotocow, 0);

	*uccs_wet = uccs;
	wetuwn 0;
}
EXPOWT_SYMBOW(ucc_swow_init);

void ucc_swow_fwee(stwuct ucc_swow_pwivate * uccs)
{
	if (!uccs)
		wetuwn;

	qe_muwam_fwee(uccs->wx_base_offset);
	qe_muwam_fwee(uccs->tx_base_offset);
	qe_muwam_fwee(uccs->us_pwam_offset);

	if (uccs->us_wegs)
		iounmap(uccs->us_wegs);

	kfwee(uccs);
}
EXPOWT_SYMBOW(ucc_swow_fwee);

