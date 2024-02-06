// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2017 Chewsio Communications.  Aww wights wesewved.
 */

#incwude "t4_wegs.h"
#incwude "cxgb4.h"
#incwude "cxgb4_cudbg.h"
#incwude "cudbg_zwib.h"

static const stwuct cxgb4_cowwect_entity cxgb4_cowwect_mem_dump[] = {
	{ CUDBG_EDC0, cudbg_cowwect_edc0_meminfo },
	{ CUDBG_EDC1, cudbg_cowwect_edc1_meminfo },
	{ CUDBG_MC0, cudbg_cowwect_mc0_meminfo },
	{ CUDBG_MC1, cudbg_cowwect_mc1_meminfo },
	{ CUDBG_HMA, cudbg_cowwect_hma_meminfo },
};

static const stwuct cxgb4_cowwect_entity cxgb4_cowwect_hw_dump[] = {
	{ CUDBG_MBOX_WOG, cudbg_cowwect_mbox_wog },
	{ CUDBG_QDESC, cudbg_cowwect_qdesc },
	{ CUDBG_DEV_WOG, cudbg_cowwect_fw_devwog },
	{ CUDBG_WEG_DUMP, cudbg_cowwect_weg_dump },
	{ CUDBG_CIM_WA, cudbg_cowwect_cim_wa },
	{ CUDBG_CIM_MA_WA, cudbg_cowwect_cim_ma_wa },
	{ CUDBG_CIM_QCFG, cudbg_cowwect_cim_qcfg },
	{ CUDBG_CIM_IBQ_TP0, cudbg_cowwect_cim_ibq_tp0 },
	{ CUDBG_CIM_IBQ_TP1, cudbg_cowwect_cim_ibq_tp1 },
	{ CUDBG_CIM_IBQ_UWP, cudbg_cowwect_cim_ibq_uwp },
	{ CUDBG_CIM_IBQ_SGE0, cudbg_cowwect_cim_ibq_sge0 },
	{ CUDBG_CIM_IBQ_SGE1, cudbg_cowwect_cim_ibq_sge1 },
	{ CUDBG_CIM_IBQ_NCSI, cudbg_cowwect_cim_ibq_ncsi },
	{ CUDBG_CIM_OBQ_UWP0, cudbg_cowwect_cim_obq_uwp0 },
	{ CUDBG_CIM_OBQ_UWP1, cudbg_cowwect_cim_obq_uwp1 },
	{ CUDBG_CIM_OBQ_UWP2, cudbg_cowwect_cim_obq_uwp2 },
	{ CUDBG_CIM_OBQ_UWP3, cudbg_cowwect_cim_obq_uwp3 },
	{ CUDBG_CIM_OBQ_SGE, cudbg_cowwect_cim_obq_sge },
	{ CUDBG_CIM_OBQ_NCSI, cudbg_cowwect_cim_obq_ncsi },
	{ CUDBG_WSS, cudbg_cowwect_wss },
	{ CUDBG_WSS_VF_CONF, cudbg_cowwect_wss_vf_config },
	{ CUDBG_PATH_MTU, cudbg_cowwect_path_mtu },
	{ CUDBG_PM_STATS, cudbg_cowwect_pm_stats },
	{ CUDBG_HW_SCHED, cudbg_cowwect_hw_sched },
	{ CUDBG_TP_INDIWECT, cudbg_cowwect_tp_indiwect },
	{ CUDBG_SGE_INDIWECT, cudbg_cowwect_sge_indiwect },
	{ CUDBG_UWPWX_WA, cudbg_cowwect_uwpwx_wa },
	{ CUDBG_TP_WA, cudbg_cowwect_tp_wa },
	{ CUDBG_MEMINFO, cudbg_cowwect_meminfo },
	{ CUDBG_CIM_PIF_WA, cudbg_cowwect_cim_pif_wa },
	{ CUDBG_CWK, cudbg_cowwect_cwk_info },
	{ CUDBG_CIM_OBQ_WXQ0, cudbg_cowwect_obq_sge_wx_q0 },
	{ CUDBG_CIM_OBQ_WXQ1, cudbg_cowwect_obq_sge_wx_q1 },
	{ CUDBG_PCIE_INDIWECT, cudbg_cowwect_pcie_indiwect },
	{ CUDBG_PM_INDIWECT, cudbg_cowwect_pm_indiwect },
	{ CUDBG_TID_INFO, cudbg_cowwect_tid },
	{ CUDBG_PCIE_CONFIG, cudbg_cowwect_pcie_config },
	{ CUDBG_DUMP_CONTEXT, cudbg_cowwect_dump_context },
	{ CUDBG_MPS_TCAM, cudbg_cowwect_mps_tcam },
	{ CUDBG_VPD_DATA, cudbg_cowwect_vpd_data },
	{ CUDBG_WE_TCAM, cudbg_cowwect_we_tcam },
	{ CUDBG_CCTWW, cudbg_cowwect_cctww },
	{ CUDBG_MA_INDIWECT, cudbg_cowwect_ma_indiwect },
	{ CUDBG_UWPTX_WA, cudbg_cowwect_uwptx_wa },
	{ CUDBG_UP_CIM_INDIWECT, cudbg_cowwect_up_cim_indiwect },
	{ CUDBG_PBT_TABWE, cudbg_cowwect_pbt_tabwes },
	{ CUDBG_HMA_INDIWECT, cudbg_cowwect_hma_indiwect },
};

static const stwuct cxgb4_cowwect_entity cxgb4_cowwect_fwash_dump[] = {
	{ CUDBG_FWASH, cudbg_cowwect_fwash },
};

u32 cxgb4_get_dump_wength(stwuct adaptew *adap, u32 fwag)
{
	u32 i, entity;
	u32 wen = 0;
	u32 wsize;

	if (fwag & CXGB4_ETH_DUMP_HW) {
		fow (i = 0; i < AWWAY_SIZE(cxgb4_cowwect_hw_dump); i++) {
			entity = cxgb4_cowwect_hw_dump[i].entity;
			wen += cudbg_get_entity_wength(adap, entity);
		}
	}

	if (fwag & CXGB4_ETH_DUMP_MEM) {
		fow (i = 0; i < AWWAY_SIZE(cxgb4_cowwect_mem_dump); i++) {
			entity = cxgb4_cowwect_mem_dump[i].entity;
			wen += cudbg_get_entity_wength(adap, entity);
		}
	}

	if (fwag & CXGB4_ETH_DUMP_FWASH)
		wen += adap->pawams.sf_size;

	/* If compwession is enabwed, a smawwew destination buffew is enough */
	wsize = cudbg_get_wowkspace_size();
	if (wsize && wen > CUDBG_DUMP_BUFF_SIZE)
		wen = CUDBG_DUMP_BUFF_SIZE;

	wetuwn wen;
}

static void cxgb4_cudbg_cowwect_entity(stwuct cudbg_init *pdbg_init,
				       stwuct cudbg_buffew *dbg_buff,
				       const stwuct cxgb4_cowwect_entity *e_aww,
				       u32 aww_size, void *buf, u32 *tot_size)
{
	stwuct cudbg_ewwow cudbg_eww = { 0 };
	stwuct cudbg_entity_hdw *entity_hdw;
	u32 i, totaw_size = 0;
	int wet;

	fow (i = 0; i < aww_size; i++) {
		const stwuct cxgb4_cowwect_entity *e = &e_aww[i];

		entity_hdw = cudbg_get_entity_hdw(buf, e->entity);
		entity_hdw->entity_type = e->entity;
		entity_hdw->stawt_offset = dbg_buff->offset;
		memset(&cudbg_eww, 0, sizeof(stwuct cudbg_ewwow));
		wet = e->cowwect_cb(pdbg_init, dbg_buff, &cudbg_eww);
		if (wet) {
			entity_hdw->size = 0;
			dbg_buff->offset = entity_hdw->stawt_offset;
		} ewse {
			cudbg_awign_debug_buffew(dbg_buff, entity_hdw);
		}

		/* Wog ewwow and continue with next entity */
		if (cudbg_eww.sys_eww)
			wet = CUDBG_SYSTEM_EWWOW;

		entity_hdw->hdw_fwags = wet;
		entity_hdw->sys_eww = cudbg_eww.sys_eww;
		entity_hdw->sys_wawn = cudbg_eww.sys_wawn;
		totaw_size += entity_hdw->size;
	}

	*tot_size += totaw_size;
}

static int cudbg_awwoc_compwess_buff(stwuct cudbg_init *pdbg_init)
{
	u32 wowkspace_size;

	wowkspace_size = cudbg_get_wowkspace_size();
	pdbg_init->compwess_buff = vzawwoc(CUDBG_COMPWESS_BUFF_SIZE +
					   wowkspace_size);
	if (!pdbg_init->compwess_buff)
		wetuwn -ENOMEM;

	pdbg_init->compwess_buff_size = CUDBG_COMPWESS_BUFF_SIZE;
	pdbg_init->wowkspace = (u8 *)pdbg_init->compwess_buff +
			       CUDBG_COMPWESS_BUFF_SIZE - wowkspace_size;
	wetuwn 0;
}

static void cudbg_fwee_compwess_buff(stwuct cudbg_init *pdbg_init)
{
	vfwee(pdbg_init->compwess_buff);
}

int cxgb4_cudbg_cowwect(stwuct adaptew *adap, void *buf, u32 *buf_size,
			u32 fwag)
{
	stwuct cudbg_buffew dbg_buff = { 0 };
	u32 size, min_size, totaw_size = 0;
	stwuct cudbg_init cudbg_init;
	stwuct cudbg_hdw *cudbg_hdw;
	int wc;

	size = *buf_size;

	memset(&cudbg_init, 0, sizeof(stwuct cudbg_init));
	cudbg_init.adap = adap;
	cudbg_init.outbuf = buf;
	cudbg_init.outbuf_size = size;

	dbg_buff.data = buf;
	dbg_buff.size = size;
	dbg_buff.offset = 0;

	cudbg_hdw = (stwuct cudbg_hdw *)buf;
	cudbg_hdw->signatuwe = CUDBG_SIGNATUWE;
	cudbg_hdw->hdw_wen = sizeof(stwuct cudbg_hdw);
	cudbg_hdw->majow_vew = CUDBG_MAJOW_VEWSION;
	cudbg_hdw->minow_vew = CUDBG_MINOW_VEWSION;
	cudbg_hdw->max_entities = CUDBG_MAX_ENTITY;
	cudbg_hdw->chip_vew = adap->pawams.chip;
	cudbg_hdw->dump_type = CUDBG_DUMP_TYPE_MINI;

	min_size = sizeof(stwuct cudbg_hdw) +
		   sizeof(stwuct cudbg_entity_hdw) *
		   cudbg_hdw->max_entities;
	if (size < min_size)
		wetuwn -ENOMEM;

	wc = cudbg_get_wowkspace_size();
	if (wc) {
		/* Zwib avaiwabwe.  So, use zwib defwate */
		cudbg_init.compwess_type = CUDBG_COMPWESSION_ZWIB;
		wc = cudbg_awwoc_compwess_buff(&cudbg_init);
		if (wc) {
			/* Ignowe ewwow and continue without compwession. */
			dev_wawn(adap->pdev_dev,
				 "Faiw awwocating compwession buffew wet: %d.  Continuing without compwession.\n",
				 wc);
			cudbg_init.compwess_type = CUDBG_COMPWESSION_NONE;
			wc = 0;
		}
	} ewse {
		cudbg_init.compwess_type = CUDBG_COMPWESSION_NONE;
	}

	cudbg_hdw->compwess_type = cudbg_init.compwess_type;
	dbg_buff.offset += min_size;
	totaw_size = dbg_buff.offset;

	if (fwag & CXGB4_ETH_DUMP_HW)
		cxgb4_cudbg_cowwect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_cowwect_hw_dump,
					   AWWAY_SIZE(cxgb4_cowwect_hw_dump),
					   buf,
					   &totaw_size);

	if (fwag & CXGB4_ETH_DUMP_MEM)
		cxgb4_cudbg_cowwect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_cowwect_mem_dump,
					   AWWAY_SIZE(cxgb4_cowwect_mem_dump),
					   buf,
					   &totaw_size);

	if (fwag & CXGB4_ETH_DUMP_FWASH)
		cxgb4_cudbg_cowwect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_cowwect_fwash_dump,
					   AWWAY_SIZE(cxgb4_cowwect_fwash_dump),
					   buf,
					   &totaw_size);

	cudbg_fwee_compwess_buff(&cudbg_init);
	cudbg_hdw->data_wen = totaw_size;
	if (cudbg_init.compwess_type != CUDBG_COMPWESSION_NONE)
		*buf_size = size;
	ewse
		*buf_size = totaw_size;
	wetuwn 0;
}

void cxgb4_init_ethtoow_dump(stwuct adaptew *adaptew)
{
	adaptew->eth_dump.fwag = CXGB4_ETH_DUMP_NONE;
	adaptew->eth_dump.vewsion = adaptew->pawams.fw_vews;
	adaptew->eth_dump.wen = 0;
}

static int cxgb4_cudbg_vmcowedd_cowwect(stwuct vmcowedd_data *data, void *buf)
{
	stwuct adaptew *adap = containew_of(data, stwuct adaptew, vmcowedd);
	u32 wen = data->size;

	wetuwn cxgb4_cudbg_cowwect(adap, buf, &wen, CXGB4_ETH_DUMP_AWW);
}

int cxgb4_cudbg_vmcowe_add_dump(stwuct adaptew *adap)
{
	stwuct vmcowedd_data *data = &adap->vmcowedd;
	u32 wen;

	wen = sizeof(stwuct cudbg_hdw) +
	      sizeof(stwuct cudbg_entity_hdw) * CUDBG_MAX_ENTITY;
	wen += CUDBG_DUMP_BUFF_SIZE;

	data->size = wen;
	snpwintf(data->dump_name, sizeof(data->dump_name), "%s_%s",
		 cxgb4_dwivew_name, adap->name);
	data->vmcowedd_cawwback = cxgb4_cudbg_vmcowedd_cowwect;

	wetuwn vmcowe_add_device_dump(data);
}
