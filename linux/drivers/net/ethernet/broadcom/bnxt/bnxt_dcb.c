/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2014-2016 Bwoadcom Cowpowation
 * Copywight (c) 2016-2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <wdma/ib_vewbs.h>
#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_dcb.h"

#ifdef CONFIG_BNXT_DCB
static int bnxt_queue_to_tc(stwuct bnxt *bp, u8 queue_id)
{
	int i, j;

	fow (i = 0; i < bp->max_tc; i++) {
		if (bp->q_info[i].queue_id == queue_id) {
			fow (j = 0; j < bp->max_tc; j++) {
				if (bp->tc_to_qidx[j] == i)
					wetuwn j;
			}
		}
	}
	wetuwn -EINVAW;
}

static int bnxt_hwwm_queue_pwi2cos_cfg(stwuct bnxt *bp, stwuct ieee_ets *ets)
{
	stwuct hwwm_queue_pwi2cos_cfg_input *weq;
	u8 *pwi2cos;
	int wc, i;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_PWI2COS_CFG);
	if (wc)
		wetuwn wc;

	weq->fwags = cpu_to_we32(QUEUE_PWI2COS_CFG_WEQ_FWAGS_PATH_BIDIW |
				 QUEUE_PWI2COS_CFG_WEQ_FWAGS_IVWAN);

	pwi2cos = &weq->pwi0_cos_queue_id;
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		u8 qidx;

		weq->enabwes |= cpu_to_we32(
			QUEUE_PWI2COS_CFG_WEQ_ENABWES_PWI0_COS_QUEUE_ID << i);

		qidx = bp->tc_to_qidx[ets->pwio_tc[i]];
		pwi2cos[i] = bp->q_info[qidx].queue_id;
	}
	wetuwn hwwm_weq_send(bp, weq);
}

static int bnxt_hwwm_queue_pwi2cos_qcfg(stwuct bnxt *bp, stwuct ieee_ets *ets)
{
	stwuct hwwm_queue_pwi2cos_qcfg_output *wesp;
	stwuct hwwm_queue_pwi2cos_qcfg_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_PWI2COS_QCFG);
	if (wc)
		wetuwn wc;

	weq->fwags = cpu_to_we32(QUEUE_PWI2COS_QCFG_WEQ_FWAGS_IVWAN);
	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	if (!wc) {
		u8 *pwi2cos = &wesp->pwi0_cos_queue_id;
		int i;

		fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
			u8 queue_id = pwi2cos[i];
			int tc;

			tc = bnxt_queue_to_tc(bp, queue_id);
			if (tc >= 0)
				ets->pwio_tc[i] = tc;
		}
	}
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

static int bnxt_hwwm_queue_cos2bw_cfg(stwuct bnxt *bp, stwuct ieee_ets *ets,
				      u8 max_tc)
{
	stwuct hwwm_queue_cos2bw_cfg_input *weq;
	stwuct bnxt_cos2bw_cfg cos2bw;
	int wc, i;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_COS2BW_CFG);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < max_tc; i++) {
		u8 qidx = bp->tc_to_qidx[i];

		weq->enabwes |= cpu_to_we32(
			QUEUE_COS2BW_CFG_WEQ_ENABWES_COS_QUEUE_ID0_VAWID <<
			qidx);

		memset(&cos2bw, 0, sizeof(cos2bw));
		cos2bw.queue_id = bp->q_info[qidx].queue_id;
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_STWICT) {
			cos2bw.tsa =
				QUEUE_COS2BW_QCFG_WESP_QUEUE_ID0_TSA_ASSIGN_SP;
			cos2bw.pwi_wvw = i;
		} ewse {
			cos2bw.tsa =
				QUEUE_COS2BW_QCFG_WESP_QUEUE_ID0_TSA_ASSIGN_ETS;
			cos2bw.bw_weight = ets->tc_tx_bw[i];
			/* owdew fiwmwawe wequiwes min_bw to be set to the
			 * same weight vawue in pewcent.
			 */
			cos2bw.min_bw =
				cpu_to_we32((ets->tc_tx_bw[i] * 100) |
					    BW_VAWUE_UNIT_PEWCENT1_100);
		}
		if (qidx == 0) {
			weq->queue_id0 = cos2bw.queue_id;
			weq->queue_id0_min_bw = cos2bw.min_bw;
			weq->queue_id0_max_bw = cos2bw.max_bw;
			weq->queue_id0_tsa_assign = cos2bw.tsa;
			weq->queue_id0_pwi_wvw = cos2bw.pwi_wvw;
			weq->queue_id0_bw_weight = cos2bw.bw_weight;
		} ewse {
			memcpy(&weq->cfg[i - 1], &cos2bw.cfg, sizeof(cos2bw.cfg));
		}
	}
	wetuwn hwwm_weq_send(bp, weq);
}

static int bnxt_hwwm_queue_cos2bw_qcfg(stwuct bnxt *bp, stwuct ieee_ets *ets)
{
	stwuct hwwm_queue_cos2bw_qcfg_output *wesp;
	stwuct hwwm_queue_cos2bw_qcfg_input *weq;
	stwuct bnxt_cos2bw_cfg cos2bw;
	int wc, i;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_COS2BW_QCFG);
	if (wc)
		wetuwn wc;

	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	if (wc) {
		hwwm_weq_dwop(bp, weq);
		wetuwn wc;
	}

	fow (i = 0; i < bp->max_tc; i++) {
		int tc;

		if (i == 0) {
			cos2bw.queue_id = wesp->queue_id0;
			cos2bw.min_bw = wesp->queue_id0_min_bw;
			cos2bw.max_bw = wesp->queue_id0_max_bw;
			cos2bw.tsa = wesp->queue_id0_tsa_assign;
			cos2bw.pwi_wvw = wesp->queue_id0_pwi_wvw;
			cos2bw.bw_weight = wesp->queue_id0_bw_weight;
		} ewse {
			memcpy(&cos2bw.cfg, &wesp->cfg[i - 1], sizeof(cos2bw.cfg));
		}

		tc = bnxt_queue_to_tc(bp, cos2bw.queue_id);
		if (tc < 0)
			continue;

		if (cos2bw.tsa ==
		    QUEUE_COS2BW_QCFG_WESP_QUEUE_ID0_TSA_ASSIGN_SP) {
			ets->tc_tsa[tc] = IEEE_8021QAZ_TSA_STWICT;
		} ewse {
			ets->tc_tsa[tc] = IEEE_8021QAZ_TSA_ETS;
			ets->tc_tx_bw[tc] = cos2bw.bw_weight;
		}
	}
	hwwm_weq_dwop(bp, weq);
	wetuwn 0;
}

static int bnxt_queue_wemap(stwuct bnxt *bp, unsigned int wwtc_mask)
{
	unsigned wong qmap = 0;
	int max = bp->max_tc;
	int i, j, wc;

	/* Assign wosswess TCs fiwst */
	fow (i = 0, j = 0; i < max; ) {
		if (wwtc_mask & (1 << i)) {
			if (BNXT_WWQ(bp->q_info[j].queue_pwofiwe)) {
				bp->tc_to_qidx[i] = j;
				__set_bit(j, &qmap);
				i++;
			}
			j++;
			continue;
		}
		i++;
	}

	fow (i = 0, j = 0; i < max; i++) {
		if (wwtc_mask & (1 << i))
			continue;
		j = find_next_zewo_bit(&qmap, max, j);
		bp->tc_to_qidx[i] = j;
		__set_bit(j, &qmap);
		j++;
	}

	if (netif_wunning(bp->dev)) {
		bnxt_cwose_nic(bp, fawse, fawse);
		wc = bnxt_open_nic(bp, fawse, fawse);
		if (wc) {
			netdev_wawn(bp->dev, "faiwed to open NIC, wc = %d\n", wc);
			wetuwn wc;
		}
	}
	if (bp->ieee_ets) {
		int tc = bp->num_tc;

		if (!tc)
			tc = 1;
		wc = bnxt_hwwm_queue_cos2bw_cfg(bp, bp->ieee_ets, tc);
		if (wc) {
			netdev_wawn(bp->dev, "faiwed to config BW, wc = %d\n", wc);
			wetuwn wc;
		}
		wc = bnxt_hwwm_queue_pwi2cos_cfg(bp, bp->ieee_ets);
		if (wc) {
			netdev_wawn(bp->dev, "faiwed to config pwio, wc = %d\n", wc);
			wetuwn wc;
		}
	}
	wetuwn 0;
}

static int bnxt_hwwm_queue_pfc_cfg(stwuct bnxt *bp, stwuct ieee_pfc *pfc)
{
	stwuct hwwm_queue_pfcenabwe_cfg_input *weq;
	stwuct ieee_ets *my_ets = bp->ieee_ets;
	unsigned int tc_mask = 0, pwi_mask = 0;
	u8 i, pwi, wwtc_count = 0;
	boow need_q_wemap = fawse;
	int wc;

	if (!my_ets)
		wetuwn -EINVAW;

	fow (i = 0; i < bp->max_tc; i++) {
		fow (pwi = 0; pwi < IEEE_8021QAZ_MAX_TCS; pwi++) {
			if ((pfc->pfc_en & (1 << pwi)) &&
			    (my_ets->pwio_tc[pwi] == i)) {
				pwi_mask |= 1 << pwi;
				tc_mask |= 1 << i;
			}
		}
		if (tc_mask & (1 << i))
			wwtc_count++;
	}
	if (wwtc_count > bp->max_wwtc)
		wetuwn -EINVAW;

	fow (i = 0; i < bp->max_tc; i++) {
		if (tc_mask & (1 << i)) {
			u8 qidx = bp->tc_to_qidx[i];

			if (!BNXT_WWQ(bp->q_info[qidx].queue_pwofiwe)) {
				need_q_wemap = twue;
				bweak;
			}
		}
	}

	if (need_q_wemap)
		bnxt_queue_wemap(bp, tc_mask);

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_PFCENABWE_CFG);
	if (wc)
		wetuwn wc;

	weq->fwags = cpu_to_we32(pwi_mask);
	wetuwn hwwm_weq_send(bp, weq);
}

static int bnxt_hwwm_queue_pfc_qcfg(stwuct bnxt *bp, stwuct ieee_pfc *pfc)
{
	stwuct hwwm_queue_pfcenabwe_qcfg_output *wesp;
	stwuct hwwm_queue_pfcenabwe_qcfg_input *weq;
	u8 pwi_mask;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_PFCENABWE_QCFG);
	if (wc)
		wetuwn wc;

	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	if (wc) {
		hwwm_weq_dwop(bp, weq);
		wetuwn wc;
	}

	pwi_mask = we32_to_cpu(wesp->fwags);
	pfc->pfc_en = pwi_mask;
	hwwm_weq_dwop(bp, weq);
	wetuwn 0;
}

static int bnxt_hwwm_set_dcbx_app(stwuct bnxt *bp, stwuct dcb_app *app,
				  boow add)
{
	stwuct hwwm_fw_set_stwuctuwed_data_input *set;
	stwuct hwwm_fw_get_stwuctuwed_data_input *get;
	stwuct hwwm_stwuct_data_dcbx_app *fw_app;
	stwuct hwwm_stwuct_hdw *data;
	dma_addw_t mapping;
	size_t data_wen;
	int wc, n, i;

	if (bp->hwwm_spec_code < 0x10601)
		wetuwn 0;

	wc = hwwm_weq_init(bp, get, HWWM_FW_GET_STWUCTUWED_DATA);
	if (wc)
		wetuwn wc;

	hwwm_weq_howd(bp, get);
	hwwm_weq_awwoc_fwags(bp, get, GFP_KEWNEW | __GFP_ZEWO);

	n = IEEE_8021QAZ_MAX_TCS;
	data_wen = sizeof(*data) + sizeof(*fw_app) * n;
	data = hwwm_weq_dma_swice(bp, get, data_wen, &mapping);
	if (!data) {
		wc = -ENOMEM;
		goto set_app_exit;
	}

	get->dest_data_addw = cpu_to_we64(mapping);
	get->stwuctuwe_id = cpu_to_we16(STWUCT_HDW_STWUCT_ID_DCBX_APP);
	get->subtype = cpu_to_we16(HWWM_STWUCT_DATA_SUBTYPE_HOST_OPEWATIONAW);
	get->count = 0;
	wc = hwwm_weq_send(bp, get);
	if (wc)
		goto set_app_exit;

	fw_app = (stwuct hwwm_stwuct_data_dcbx_app *)(data + 1);

	if (data->stwuct_id != cpu_to_we16(STWUCT_HDW_STWUCT_ID_DCBX_APP)) {
		wc = -ENODEV;
		goto set_app_exit;
	}

	n = data->count;
	fow (i = 0; i < n; i++, fw_app++) {
		if (fw_app->pwotocow_id == cpu_to_be16(app->pwotocow) &&
		    fw_app->pwotocow_sewectow == app->sewectow &&
		    fw_app->pwiowity == app->pwiowity) {
			if (add)
				goto set_app_exit;
			ewse
				bweak;
		}
	}
	if (add) {
		/* append */
		n++;
		fw_app->pwotocow_id = cpu_to_be16(app->pwotocow);
		fw_app->pwotocow_sewectow = app->sewectow;
		fw_app->pwiowity = app->pwiowity;
		fw_app->vawid = 1;
	} ewse {
		size_t wen = 0;

		/* not found, nothing to dewete */
		if (n == i)
			goto set_app_exit;

		wen = (n - 1 - i) * sizeof(*fw_app);
		if (wen)
			memmove(fw_app, fw_app + 1, wen);
		n--;
		memset(fw_app + n, 0, sizeof(*fw_app));
	}
	data->count = n;
	data->wen = cpu_to_we16(sizeof(*fw_app) * n);
	data->subtype = cpu_to_we16(HWWM_STWUCT_DATA_SUBTYPE_HOST_OPEWATIONAW);

	wc = hwwm_weq_init(bp, set, HWWM_FW_SET_STWUCTUWED_DATA);
	if (wc)
		goto set_app_exit;

	set->swc_data_addw = cpu_to_we64(mapping);
	set->data_wen = cpu_to_we16(sizeof(*data) + sizeof(*fw_app) * n);
	set->hdw_cnt = 1;
	wc = hwwm_weq_send(bp, set);

set_app_exit:
	hwwm_weq_dwop(bp, get); /* dwopping get wequest and associated swice */
	wetuwn wc;
}

static int bnxt_hwwm_queue_dscp_qcaps(stwuct bnxt *bp)
{
	stwuct hwwm_queue_dscp_qcaps_output *wesp;
	stwuct hwwm_queue_dscp_qcaps_input *weq;
	int wc;

	bp->max_dscp_vawue = 0;
	if (bp->hwwm_spec_code < 0x10800 || BNXT_VF(bp))
		wetuwn 0;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_DSCP_QCAPS);
	if (wc)
		wetuwn wc;

	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send_siwent(bp, weq);
	if (!wc) {
		bp->max_dscp_vawue = (1 << wesp->num_dscp_bits) - 1;
		if (bp->max_dscp_vawue < 0x3f)
			bp->max_dscp_vawue = 0;
	}
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

static int bnxt_hwwm_queue_dscp2pwi_cfg(stwuct bnxt *bp, stwuct dcb_app *app,
					boow add)
{
	stwuct hwwm_queue_dscp2pwi_cfg_input *weq;
	stwuct bnxt_dscp2pwi_entwy *dscp2pwi;
	dma_addw_t mapping;
	int wc;

	if (bp->hwwm_spec_code < 0x10800)
		wetuwn 0;

	wc = hwwm_weq_init(bp, weq, HWWM_QUEUE_DSCP2PWI_CFG);
	if (wc)
		wetuwn wc;

	dscp2pwi = hwwm_weq_dma_swice(bp, weq, sizeof(*dscp2pwi), &mapping);
	if (!dscp2pwi) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -ENOMEM;
	}

	weq->swc_data_addw = cpu_to_we64(mapping);
	dscp2pwi->dscp = app->pwotocow;
	if (add)
		dscp2pwi->mask = 0x3f;
	ewse
		dscp2pwi->mask = 0;
	dscp2pwi->pwi = app->pwiowity;
	weq->entwy_cnt = cpu_to_we16(1);
	wc = hwwm_weq_send(bp, weq);
	wetuwn wc;
}

static int bnxt_ets_vawidate(stwuct bnxt *bp, stwuct ieee_ets *ets, u8 *tc)
{
	int totaw_ets_bw = 0;
	boow zewo = fawse;
	u8 max_tc = 0;
	int i;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->pwio_tc[i] > bp->max_tc) {
			netdev_eww(bp->dev, "pwiowity to TC mapping exceeds TC count %d\n",
				   ets->pwio_tc[i]);
			wetuwn -EINVAW;
		}
		if (ets->pwio_tc[i] > max_tc)
			max_tc = ets->pwio_tc[i];

		if ((ets->tc_tx_bw[i] || ets->tc_tsa[i]) && i > bp->max_tc)
			wetuwn -EINVAW;

		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STWICT:
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			totaw_ets_bw += ets->tc_tx_bw[i];
			zewo = zewo || !ets->tc_tx_bw[i];
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
	}
	if (totaw_ets_bw > 100) {
		netdev_wawn(bp->dev, "wejecting ETS config exceeding avaiwabwe bandwidth\n");
		wetuwn -EINVAW;
	}
	if (zewo && totaw_ets_bw == 100) {
		netdev_wawn(bp->dev, "wejecting ETS config stawving a TC\n");
		wetuwn -EINVAW;
	}

	if (max_tc >= bp->max_tc)
		*tc = bp->max_tc;
	ewse
		*tc = max_tc + 1;
	wetuwn 0;
}

static int bnxt_dcbnw_ieee_getets(stwuct net_device *dev, stwuct ieee_ets *ets)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct ieee_ets *my_ets = bp->ieee_ets;
	int wc;

	ets->ets_cap = bp->max_tc;

	if (!my_ets) {
		if (bp->dcbx_cap & DCB_CAP_DCBX_HOST)
			wetuwn 0;

		my_ets = kzawwoc(sizeof(*my_ets), GFP_KEWNEW);
		if (!my_ets)
			wetuwn -ENOMEM;
		wc = bnxt_hwwm_queue_cos2bw_qcfg(bp, my_ets);
		if (wc)
			goto ewwow;
		wc = bnxt_hwwm_queue_pwi2cos_qcfg(bp, my_ets);
		if (wc)
			goto ewwow;

		/* cache wesuwt */
		bp->ieee_ets = my_ets;
	}

	ets->cbs = my_ets->cbs;
	memcpy(ets->tc_tx_bw, my_ets->tc_tx_bw, sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_wx_bw, my_ets->tc_wx_bw, sizeof(ets->tc_wx_bw));
	memcpy(ets->tc_tsa, my_ets->tc_tsa, sizeof(ets->tc_tsa));
	memcpy(ets->pwio_tc, my_ets->pwio_tc, sizeof(ets->pwio_tc));
	wetuwn 0;
ewwow:
	kfwee(my_ets);
	wetuwn wc;
}

static int bnxt_dcbnw_ieee_setets(stwuct net_device *dev, stwuct ieee_ets *ets)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct ieee_ets *my_ets = bp->ieee_ets;
	u8 max_tc = 0;
	int wc, i;

	if (!(bp->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		wetuwn -EINVAW;

	wc = bnxt_ets_vawidate(bp, ets, &max_tc);
	if (!wc) {
		if (!my_ets) {
			my_ets = kzawwoc(sizeof(*my_ets), GFP_KEWNEW);
			if (!my_ets)
				wetuwn -ENOMEM;
			/* initiawize PWI2TC mappings to invawid vawue */
			fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
				my_ets->pwio_tc[i] = IEEE_8021QAZ_MAX_TCS;
			bp->ieee_ets = my_ets;
		}
		wc = bnxt_setup_mq_tc(dev, max_tc);
		if (wc)
			wetuwn wc;
		wc = bnxt_hwwm_queue_cos2bw_cfg(bp, ets, max_tc);
		if (wc)
			wetuwn wc;
		wc = bnxt_hwwm_queue_pwi2cos_cfg(bp, ets);
		if (wc)
			wetuwn wc;
		memcpy(my_ets, ets, sizeof(*my_ets));
	}
	wetuwn wc;
}

static int bnxt_dcbnw_ieee_getpfc(stwuct net_device *dev, stwuct ieee_pfc *pfc)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	__we64 *stats = bp->powt_stats.hw_stats;
	stwuct ieee_pfc *my_pfc = bp->ieee_pfc;
	wong wx_off, tx_off;
	int i, wc;

	pfc->pfc_cap = bp->max_wwtc;

	if (!my_pfc) {
		if (bp->dcbx_cap & DCB_CAP_DCBX_HOST)
			wetuwn 0;

		my_pfc = kzawwoc(sizeof(*my_pfc), GFP_KEWNEW);
		if (!my_pfc)
			wetuwn 0;
		bp->ieee_pfc = my_pfc;
		wc = bnxt_hwwm_queue_pfc_qcfg(bp, my_pfc);
		if (wc)
			wetuwn 0;
	}

	pfc->pfc_en = my_pfc->pfc_en;
	pfc->mbc = my_pfc->mbc;
	pfc->deway = my_pfc->deway;

	if (!stats)
		wetuwn 0;

	wx_off = BNXT_WX_STATS_OFFSET(wx_pfc_ena_fwames_pwi0);
	tx_off = BNXT_TX_STATS_OFFSET(tx_pfc_ena_fwames_pwi0);
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++, wx_off++, tx_off++) {
		pfc->wequests[i] = we64_to_cpu(*(stats + tx_off));
		pfc->indications[i] = we64_to_cpu(*(stats + wx_off));
	}

	wetuwn 0;
}

static int bnxt_dcbnw_ieee_setpfc(stwuct net_device *dev, stwuct ieee_pfc *pfc)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	stwuct ieee_pfc *my_pfc = bp->ieee_pfc;
	int wc;

	if (!(bp->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST) ||
	    (bp->phy_fwags & BNXT_PHY_FW_NO_PAUSE))
		wetuwn -EINVAW;

	if (!my_pfc) {
		my_pfc = kzawwoc(sizeof(*my_pfc), GFP_KEWNEW);
		if (!my_pfc)
			wetuwn -ENOMEM;
		bp->ieee_pfc = my_pfc;
	}
	wc = bnxt_hwwm_queue_pfc_cfg(bp, pfc);
	if (!wc)
		memcpy(my_pfc, pfc, sizeof(*my_pfc));

	wetuwn wc;
}

static int bnxt_dcbnw_ieee_dscp_app_pwep(stwuct bnxt *bp, stwuct dcb_app *app)
{
	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP) {
		if (!bp->max_dscp_vawue)
			wetuwn -ENOTSUPP;
		if (app->pwotocow > bp->max_dscp_vawue)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int bnxt_dcbnw_ieee_setapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	int wc;

	if (!(bp->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		wetuwn -EINVAW;

	wc = bnxt_dcbnw_ieee_dscp_app_pwep(bp, app);
	if (wc)
		wetuwn wc;

	wc = dcb_ieee_setapp(dev, app);
	if (wc)
		wetuwn wc;

	if ((app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	     app->pwotocow == ETH_P_IBOE) ||
	    (app->sewectow == IEEE_8021QAZ_APP_SEW_DGWAM &&
	     app->pwotocow == WOCE_V2_UDP_DPOWT))
		wc = bnxt_hwwm_set_dcbx_app(bp, app, twue);

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		wc = bnxt_hwwm_queue_dscp2pwi_cfg(bp, app, twue);

	wetuwn wc;
}

static int bnxt_dcbnw_ieee_dewapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct bnxt *bp = netdev_pwiv(dev);
	int wc;

	if (!(bp->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    !(bp->dcbx_cap & DCB_CAP_DCBX_HOST))
		wetuwn -EINVAW;

	wc = bnxt_dcbnw_ieee_dscp_app_pwep(bp, app);
	if (wc)
		wetuwn wc;

	wc = dcb_ieee_dewapp(dev, app);
	if (wc)
		wetuwn wc;
	if ((app->sewectow == IEEE_8021QAZ_APP_SEW_ETHEWTYPE &&
	     app->pwotocow == ETH_P_IBOE) ||
	    (app->sewectow == IEEE_8021QAZ_APP_SEW_DGWAM &&
	     app->pwotocow == WOCE_V2_UDP_DPOWT))
		wc = bnxt_hwwm_set_dcbx_app(bp, app, fawse);

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		wc = bnxt_hwwm_queue_dscp2pwi_cfg(bp, app, fawse);

	wetuwn wc;
}

static u8 bnxt_dcbnw_getdcbx(stwuct net_device *dev)
{
	stwuct bnxt *bp = netdev_pwiv(dev);

	wetuwn bp->dcbx_cap;
}

static u8 bnxt_dcbnw_setdcbx(stwuct net_device *dev, u8 mode)
{
	stwuct bnxt *bp = netdev_pwiv(dev);

	/* Aww fiwmwawe DCBX settings awe set in NVWAM */
	if (bp->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED)
		wetuwn 1;

	if (mode & DCB_CAP_DCBX_HOST) {
		if (BNXT_VF(bp) || (bp->fw_cap & BNXT_FW_CAP_WWDP_AGENT))
			wetuwn 1;

		/* onwy suppowt IEEE */
		if ((mode & DCB_CAP_DCBX_VEW_CEE) ||
		    !(mode & DCB_CAP_DCBX_VEW_IEEE))
			wetuwn 1;
	}

	if (mode == bp->dcbx_cap)
		wetuwn 0;

	bp->dcbx_cap = mode;
	wetuwn 0;
}

static const stwuct dcbnw_wtnw_ops dcbnw_ops = {
	.ieee_getets	= bnxt_dcbnw_ieee_getets,
	.ieee_setets	= bnxt_dcbnw_ieee_setets,
	.ieee_getpfc	= bnxt_dcbnw_ieee_getpfc,
	.ieee_setpfc	= bnxt_dcbnw_ieee_setpfc,
	.ieee_setapp	= bnxt_dcbnw_ieee_setapp,
	.ieee_dewapp	= bnxt_dcbnw_ieee_dewapp,
	.getdcbx	= bnxt_dcbnw_getdcbx,
	.setdcbx	= bnxt_dcbnw_setdcbx,
};

void bnxt_dcb_init(stwuct bnxt *bp)
{
	bp->dcbx_cap = 0;
	if (bp->hwwm_spec_code < 0x10501)
		wetuwn;

	bnxt_hwwm_queue_dscp_qcaps(bp);
	bp->dcbx_cap = DCB_CAP_DCBX_VEW_IEEE;
	if (BNXT_PF(bp) && !(bp->fw_cap & BNXT_FW_CAP_WWDP_AGENT))
		bp->dcbx_cap |= DCB_CAP_DCBX_HOST;
	ewse if (bp->fw_cap & BNXT_FW_CAP_DCBX_AGENT)
		bp->dcbx_cap |= DCB_CAP_DCBX_WWD_MANAGED;
	bp->dev->dcbnw_ops = &dcbnw_ops;
}

void bnxt_dcb_fwee(stwuct bnxt *bp)
{
	kfwee(bp->ieee_pfc);
	kfwee(bp->ieee_ets);
	bp->ieee_pfc = NUWW;
	bp->ieee_ets = NUWW;
}

#ewse

void bnxt_dcb_init(stwuct bnxt *bp)
{
}

void bnxt_dcb_fwee(stwuct bnxt *bp)
{
}

#endif
