// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/devcowedump.h>
#incwude "iww-dwv.h"
#incwude "wuntime.h"
#incwude "dbg.h"
#incwude "debugfs.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "iww-csw.h"
#incwude "iww-fh.h"
/**
 * stwuct iww_fw_dump_ptws - set of pointews needed fow the fw-ewwow-dump
 *
 * @fwwt_ptw: pointew to the buffew coming fwom fwwt
 * @twans_ptw: pointew to stwuct %iww_twans_dump_data which contains the
 *	twanspowt's data.
 * @twans_wen: wength of the vawid data in twans_ptw
 * @fwwt_wen: wength of the vawid data in fwwt_ptw
 */
stwuct iww_fw_dump_ptws {
	stwuct iww_twans_dump_data *twans_ptw;
	void *fwwt_ptw;
	u32 fwwt_wen;
};

#define WADIO_WEG_MAX_WEAD 0x2ad
static void iww_wead_wadio_wegs(stwuct iww_fw_wuntime *fwwt,
				stwuct iww_fw_ewwow_dump_data **dump_data)
{
	u8 *pos = (void *)(*dump_data)->data;
	int i;

	IWW_DEBUG_INFO(fwwt, "WWT wadio wegistews dump\n");

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn;

	(*dump_data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_WADIO_WEG);
	(*dump_data)->wen = cpu_to_we32(WADIO_WEG_MAX_WEAD);

	fow (i = 0; i < WADIO_WEG_MAX_WEAD; i++) {
		u32 wd_cmd = WADIO_WSP_WD_CMD;

		wd_cmd |= i << WADIO_WSP_ADDW_POS;
		iww_wwite_pwph_no_gwab(fwwt->twans, WSP_WADIO_CMD, wd_cmd);
		*pos = (u8)iww_wead_pwph_no_gwab(fwwt->twans, WSP_WADIO_WDDAT);

		pos++;
	}

	*dump_data = iww_fw_ewwow_next_data(*dump_data);

	iww_twans_wewease_nic_access(fwwt->twans);
}

static void iww_fwwt_dump_wxf(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_fw_ewwow_dump_data **dump_data,
			      int size, u32 offset, int fifo_num)
{
	stwuct iww_fw_ewwow_dump_fifo *fifo_hdw;
	u32 *fifo_data;
	u32 fifo_wen;
	int i;

	fifo_hdw = (void *)(*dump_data)->data;
	fifo_data = (void *)fifo_hdw->data;
	fifo_wen = size;

	/* No need to twy to wead the data if the wength is 0 */
	if (fifo_wen == 0)
		wetuwn;

	/* Add a TWV fow the WXF */
	(*dump_data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_WXF);
	(*dump_data)->wen = cpu_to_we32(fifo_wen + sizeof(*fifo_hdw));

	fifo_hdw->fifo_num = cpu_to_we32(fifo_num);
	fifo_hdw->avaiwabwe_bytes =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						WXF_WD_D_SPACE + offset));
	fifo_hdw->ww_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						WXF_WD_WW_PTW + offset));
	fifo_hdw->wd_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						WXF_WD_WD_PTW + offset));
	fifo_hdw->fence_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						WXF_WD_FENCE_PTW + offset));
	fifo_hdw->fence_mode =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						WXF_SET_FENCE_MODE + offset));

	/* Wock fence */
	iww_twans_wwite_pwph(fwwt->twans, WXF_SET_FENCE_MODE + offset, 0x1);
	/* Set fence pointew to the same pwace wike WW pointew */
	iww_twans_wwite_pwph(fwwt->twans, WXF_WD_WW2FENCE + offset, 0x1);
	/* Set fence offset */
	iww_twans_wwite_pwph(fwwt->twans,
			     WXF_WD_FENCE_OFFSET_ADDW + offset, 0x0);

	/* Wead FIFO */
	fifo_wen /= sizeof(u32); /* Size in DWOWDS */
	fow (i = 0; i < fifo_wen; i++)
		fifo_data[i] = iww_twans_wead_pwph(fwwt->twans,
						 WXF_FIFO_WD_FENCE_INC +
						 offset);
	*dump_data = iww_fw_ewwow_next_data(*dump_data);
}

static void iww_fwwt_dump_txf(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_fw_ewwow_dump_data **dump_data,
			      int size, u32 offset, int fifo_num)
{
	stwuct iww_fw_ewwow_dump_fifo *fifo_hdw;
	u32 *fifo_data;
	u32 fifo_wen;
	int i;

	fifo_hdw = (void *)(*dump_data)->data;
	fifo_data = (void *)fifo_hdw->data;
	fifo_wen = size;

	/* No need to twy to wead the data if the wength is 0 */
	if (fifo_wen == 0)
		wetuwn;

	/* Add a TWV fow the FIFO */
	(*dump_data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_TXF);
	(*dump_data)->wen = cpu_to_we32(fifo_wen + sizeof(*fifo_hdw));

	fifo_hdw->fifo_num = cpu_to_we32(fifo_num);
	fifo_hdw->avaiwabwe_bytes =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						TXF_FIFO_ITEM_CNT + offset));
	fifo_hdw->ww_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						TXF_WW_PTW + offset));
	fifo_hdw->wd_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						TXF_WD_PTW + offset));
	fifo_hdw->fence_ptw =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						TXF_FENCE_PTW + offset));
	fifo_hdw->fence_mode =
		cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
						TXF_WOCK_FENCE + offset));

	/* Set the TXF_WEAD_MODIFY_ADDW to TXF_WW_PTW */
	iww_twans_wwite_pwph(fwwt->twans, TXF_WEAD_MODIFY_ADDW + offset,
			     TXF_WW_PTW + offset);

	/* Dummy-wead to advance the wead pointew to the head */
	iww_twans_wead_pwph(fwwt->twans, TXF_WEAD_MODIFY_DATA + offset);

	/* Wead FIFO */
	fow (i = 0; i < fifo_wen / sizeof(u32); i++)
		fifo_data[i] = iww_twans_wead_pwph(fwwt->twans,
						  TXF_WEAD_MODIFY_DATA +
						  offset);

	if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_txf)
		fwwt->sanitize_ops->fwob_txf(fwwt->sanitize_ctx,
					     fifo_data, fifo_wen);

	*dump_data = iww_fw_ewwow_next_data(*dump_data);
}

static void iww_fw_dump_wxf(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_ewwow_dump_data **dump_data)
{
	stwuct iww_fwwt_shawed_mem_cfg *cfg = &fwwt->smem_cfg;

	IWW_DEBUG_INFO(fwwt, "WWT WX FIFO dump\n");

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn;

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_WXF)) {
		/* Puww WXF1 */
		iww_fwwt_dump_wxf(fwwt, dump_data,
				  cfg->wmac[0].wxfifo1_size, 0, 0);
		/* Puww WXF2 */
		iww_fwwt_dump_wxf(fwwt, dump_data, cfg->wxfifo2_size,
				  WXF_DIFF_FWOM_PWEV +
				  fwwt->twans->twans_cfg->umac_pwph_offset, 1);
		/* Puww WMAC2 WXF1 */
		if (fwwt->smem_cfg.num_wmacs > 1)
			iww_fwwt_dump_wxf(fwwt, dump_data,
					  cfg->wmac[1].wxfifo1_size,
					  WMAC2_PWPH_OFFSET, 2);
	}

	iww_twans_wewease_nic_access(fwwt->twans);
}

static void iww_fw_dump_txf(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_ewwow_dump_data **dump_data)
{
	stwuct iww_fw_ewwow_dump_fifo *fifo_hdw;
	stwuct iww_fwwt_shawed_mem_cfg *cfg = &fwwt->smem_cfg;
	u32 *fifo_data;
	u32 fifo_wen;
	int i, j;

	IWW_DEBUG_INFO(fwwt, "WWT TX FIFO dump\n");

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn;

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_TXF)) {
		/* Puww TXF data fwom WMAC1 */
		fow (i = 0; i < fwwt->smem_cfg.num_txfifo_entwies; i++) {
			/* Mawk the numbew of TXF we'we puwwing now */
			iww_twans_wwite_pwph(fwwt->twans, TXF_WAWC_NUM, i);
			iww_fwwt_dump_txf(fwwt, dump_data,
					  cfg->wmac[0].txfifo_size[i], 0, i);
		}

		/* Puww TXF data fwom WMAC2 */
		if (fwwt->smem_cfg.num_wmacs > 1) {
			fow (i = 0; i < fwwt->smem_cfg.num_txfifo_entwies;
			     i++) {
				/* Mawk the numbew of TXF we'we puwwing now */
				iww_twans_wwite_pwph(fwwt->twans,
						     TXF_WAWC_NUM +
						     WMAC2_PWPH_OFFSET, i);
				iww_fwwt_dump_txf(fwwt, dump_data,
						  cfg->wmac[1].txfifo_size[i],
						  WMAC2_PWPH_OFFSET,
						  i + cfg->num_txfifo_entwies);
			}
		}
	}

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_INTEWNAW_TXF) &&
	    fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG)) {
		/* Puww UMAC intewnaw TXF data fwom aww TXFs */
		fow (i = 0;
		     i < AWWAY_SIZE(fwwt->smem_cfg.intewnaw_txfifo_size);
		     i++) {
			fifo_hdw = (void *)(*dump_data)->data;
			fifo_data = (void *)fifo_hdw->data;
			fifo_wen = fwwt->smem_cfg.intewnaw_txfifo_size[i];

			/* No need to twy to wead the data if the wength is 0 */
			if (fifo_wen == 0)
				continue;

			/* Add a TWV fow the intewnaw FIFOs */
			(*dump_data)->type =
				cpu_to_we32(IWW_FW_EWWOW_DUMP_INTEWNAW_TXF);
			(*dump_data)->wen =
				cpu_to_we32(fifo_wen + sizeof(*fifo_hdw));

			fifo_hdw->fifo_num = cpu_to_we32(i);

			/* Mawk the numbew of TXF we'we puwwing now */
			iww_twans_wwite_pwph(fwwt->twans, TXF_CPU2_NUM, i +
				fwwt->smem_cfg.num_txfifo_entwies);

			fifo_hdw->avaiwabwe_bytes =
				cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
								TXF_CPU2_FIFO_ITEM_CNT));
			fifo_hdw->ww_ptw =
				cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
								TXF_CPU2_WW_PTW));
			fifo_hdw->wd_ptw =
				cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
								TXF_CPU2_WD_PTW));
			fifo_hdw->fence_ptw =
				cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
								TXF_CPU2_FENCE_PTW));
			fifo_hdw->fence_mode =
				cpu_to_we32(iww_twans_wead_pwph(fwwt->twans,
								TXF_CPU2_WOCK_FENCE));

			/* Set TXF_CPU2_WEAD_MODIFY_ADDW to TXF_CPU2_WW_PTW */
			iww_twans_wwite_pwph(fwwt->twans,
					     TXF_CPU2_WEAD_MODIFY_ADDW,
					     TXF_CPU2_WW_PTW);

			/* Dummy-wead to advance the wead pointew to head */
			iww_twans_wead_pwph(fwwt->twans,
					    TXF_CPU2_WEAD_MODIFY_DATA);

			/* Wead FIFO */
			fifo_wen /= sizeof(u32); /* Size in DWOWDS */
			fow (j = 0; j < fifo_wen; j++)
				fifo_data[j] =
					iww_twans_wead_pwph(fwwt->twans,
							    TXF_CPU2_WEAD_MODIFY_DATA);
			*dump_data = iww_fw_ewwow_next_data(*dump_data);
		}
	}

	iww_twans_wewease_nic_access(fwwt->twans);
}

stwuct iww_pwph_wange {
	u32 stawt, end;
};

static const stwuct iww_pwph_wange iww_pwph_dump_addw_comm[] = {
	{ .stawt = 0x00a00000, .end = 0x00a00000 },
	{ .stawt = 0x00a0000c, .end = 0x00a00024 },
	{ .stawt = 0x00a0002c, .end = 0x00a0003c },
	{ .stawt = 0x00a00410, .end = 0x00a00418 },
	{ .stawt = 0x00a00420, .end = 0x00a00420 },
	{ .stawt = 0x00a00428, .end = 0x00a00428 },
	{ .stawt = 0x00a00430, .end = 0x00a0043c },
	{ .stawt = 0x00a00444, .end = 0x00a00444 },
	{ .stawt = 0x00a004c0, .end = 0x00a004cc },
	{ .stawt = 0x00a004d8, .end = 0x00a004d8 },
	{ .stawt = 0x00a004e0, .end = 0x00a004f0 },
	{ .stawt = 0x00a00840, .end = 0x00a00840 },
	{ .stawt = 0x00a00850, .end = 0x00a00858 },
	{ .stawt = 0x00a01004, .end = 0x00a01008 },
	{ .stawt = 0x00a01010, .end = 0x00a01010 },
	{ .stawt = 0x00a01018, .end = 0x00a01018 },
	{ .stawt = 0x00a01024, .end = 0x00a01024 },
	{ .stawt = 0x00a0102c, .end = 0x00a01034 },
	{ .stawt = 0x00a0103c, .end = 0x00a01040 },
	{ .stawt = 0x00a01048, .end = 0x00a01094 },
	{ .stawt = 0x00a01c00, .end = 0x00a01c20 },
	{ .stawt = 0x00a01c58, .end = 0x00a01c58 },
	{ .stawt = 0x00a01c7c, .end = 0x00a01c7c },
	{ .stawt = 0x00a01c28, .end = 0x00a01c54 },
	{ .stawt = 0x00a01c5c, .end = 0x00a01c5c },
	{ .stawt = 0x00a01c60, .end = 0x00a01cdc },
	{ .stawt = 0x00a01ce0, .end = 0x00a01d0c },
	{ .stawt = 0x00a01d18, .end = 0x00a01d20 },
	{ .stawt = 0x00a01d2c, .end = 0x00a01d30 },
	{ .stawt = 0x00a01d40, .end = 0x00a01d5c },
	{ .stawt = 0x00a01d80, .end = 0x00a01d80 },
	{ .stawt = 0x00a01d98, .end = 0x00a01d9c },
	{ .stawt = 0x00a01da8, .end = 0x00a01da8 },
	{ .stawt = 0x00a01db8, .end = 0x00a01df4 },
	{ .stawt = 0x00a01dc0, .end = 0x00a01dfc },
	{ .stawt = 0x00a01e00, .end = 0x00a01e2c },
	{ .stawt = 0x00a01e40, .end = 0x00a01e60 },
	{ .stawt = 0x00a01e68, .end = 0x00a01e6c },
	{ .stawt = 0x00a01e74, .end = 0x00a01e74 },
	{ .stawt = 0x00a01e84, .end = 0x00a01e90 },
	{ .stawt = 0x00a01e9c, .end = 0x00a01ec4 },
	{ .stawt = 0x00a01ed0, .end = 0x00a01ee0 },
	{ .stawt = 0x00a01f00, .end = 0x00a01f1c },
	{ .stawt = 0x00a01f44, .end = 0x00a01ffc },
	{ .stawt = 0x00a02000, .end = 0x00a02048 },
	{ .stawt = 0x00a02068, .end = 0x00a020f0 },
	{ .stawt = 0x00a02100, .end = 0x00a02118 },
	{ .stawt = 0x00a02140, .end = 0x00a0214c },
	{ .stawt = 0x00a02168, .end = 0x00a0218c },
	{ .stawt = 0x00a021c0, .end = 0x00a021c0 },
	{ .stawt = 0x00a02400, .end = 0x00a02410 },
	{ .stawt = 0x00a02418, .end = 0x00a02420 },
	{ .stawt = 0x00a02428, .end = 0x00a0242c },
	{ .stawt = 0x00a02434, .end = 0x00a02434 },
	{ .stawt = 0x00a02440, .end = 0x00a02460 },
	{ .stawt = 0x00a02468, .end = 0x00a024b0 },
	{ .stawt = 0x00a024c8, .end = 0x00a024cc },
	{ .stawt = 0x00a02500, .end = 0x00a02504 },
	{ .stawt = 0x00a0250c, .end = 0x00a02510 },
	{ .stawt = 0x00a02540, .end = 0x00a02554 },
	{ .stawt = 0x00a02580, .end = 0x00a025f4 },
	{ .stawt = 0x00a02600, .end = 0x00a0260c },
	{ .stawt = 0x00a02648, .end = 0x00a02650 },
	{ .stawt = 0x00a02680, .end = 0x00a02680 },
	{ .stawt = 0x00a026c0, .end = 0x00a026d0 },
	{ .stawt = 0x00a02700, .end = 0x00a0270c },
	{ .stawt = 0x00a02804, .end = 0x00a02804 },
	{ .stawt = 0x00a02818, .end = 0x00a0281c },
	{ .stawt = 0x00a02c00, .end = 0x00a02db4 },
	{ .stawt = 0x00a02df4, .end = 0x00a02fb0 },
	{ .stawt = 0x00a03000, .end = 0x00a03014 },
	{ .stawt = 0x00a0301c, .end = 0x00a0302c },
	{ .stawt = 0x00a03034, .end = 0x00a03038 },
	{ .stawt = 0x00a03040, .end = 0x00a03048 },
	{ .stawt = 0x00a03060, .end = 0x00a03068 },
	{ .stawt = 0x00a03070, .end = 0x00a03074 },
	{ .stawt = 0x00a0307c, .end = 0x00a0307c },
	{ .stawt = 0x00a03080, .end = 0x00a03084 },
	{ .stawt = 0x00a0308c, .end = 0x00a03090 },
	{ .stawt = 0x00a03098, .end = 0x00a03098 },
	{ .stawt = 0x00a030a0, .end = 0x00a030a0 },
	{ .stawt = 0x00a030a8, .end = 0x00a030b4 },
	{ .stawt = 0x00a030bc, .end = 0x00a030bc },
	{ .stawt = 0x00a030c0, .end = 0x00a0312c },
	{ .stawt = 0x00a03c00, .end = 0x00a03c5c },
	{ .stawt = 0x00a04400, .end = 0x00a04454 },
	{ .stawt = 0x00a04460, .end = 0x00a04474 },
	{ .stawt = 0x00a044c0, .end = 0x00a044ec },
	{ .stawt = 0x00a04500, .end = 0x00a04504 },
	{ .stawt = 0x00a04510, .end = 0x00a04538 },
	{ .stawt = 0x00a04540, .end = 0x00a04548 },
	{ .stawt = 0x00a04560, .end = 0x00a0457c },
	{ .stawt = 0x00a04590, .end = 0x00a04598 },
	{ .stawt = 0x00a045c0, .end = 0x00a045f4 },
};

static const stwuct iww_pwph_wange iww_pwph_dump_addw_9000[] = {
	{ .stawt = 0x00a05c00, .end = 0x00a05c18 },
	{ .stawt = 0x00a05400, .end = 0x00a056e8 },
	{ .stawt = 0x00a08000, .end = 0x00a098bc },
	{ .stawt = 0x00a02400, .end = 0x00a02758 },
	{ .stawt = 0x00a04764, .end = 0x00a0476c },
	{ .stawt = 0x00a04770, .end = 0x00a04774 },
	{ .stawt = 0x00a04620, .end = 0x00a04624 },
};

static const stwuct iww_pwph_wange iww_pwph_dump_addw_22000[] = {
	{ .stawt = 0x00a00000, .end = 0x00a00000 },
	{ .stawt = 0x00a0000c, .end = 0x00a00024 },
	{ .stawt = 0x00a0002c, .end = 0x00a00034 },
	{ .stawt = 0x00a0003c, .end = 0x00a0003c },
	{ .stawt = 0x00a00410, .end = 0x00a00418 },
	{ .stawt = 0x00a00420, .end = 0x00a00420 },
	{ .stawt = 0x00a00428, .end = 0x00a00428 },
	{ .stawt = 0x00a00430, .end = 0x00a0043c },
	{ .stawt = 0x00a00444, .end = 0x00a00444 },
	{ .stawt = 0x00a00840, .end = 0x00a00840 },
	{ .stawt = 0x00a00850, .end = 0x00a00858 },
	{ .stawt = 0x00a01004, .end = 0x00a01008 },
	{ .stawt = 0x00a01010, .end = 0x00a01010 },
	{ .stawt = 0x00a01018, .end = 0x00a01018 },
	{ .stawt = 0x00a01024, .end = 0x00a01024 },
	{ .stawt = 0x00a0102c, .end = 0x00a01034 },
	{ .stawt = 0x00a0103c, .end = 0x00a01040 },
	{ .stawt = 0x00a01048, .end = 0x00a01050 },
	{ .stawt = 0x00a01058, .end = 0x00a01058 },
	{ .stawt = 0x00a01060, .end = 0x00a01070 },
	{ .stawt = 0x00a0108c, .end = 0x00a0108c },
	{ .stawt = 0x00a01c20, .end = 0x00a01c28 },
	{ .stawt = 0x00a01d10, .end = 0x00a01d10 },
	{ .stawt = 0x00a01e28, .end = 0x00a01e2c },
	{ .stawt = 0x00a01e60, .end = 0x00a01e60 },
	{ .stawt = 0x00a01e80, .end = 0x00a01e80 },
	{ .stawt = 0x00a01ea0, .end = 0x00a01ea0 },
	{ .stawt = 0x00a02000, .end = 0x00a0201c },
	{ .stawt = 0x00a02024, .end = 0x00a02024 },
	{ .stawt = 0x00a02040, .end = 0x00a02048 },
	{ .stawt = 0x00a020c0, .end = 0x00a020e0 },
	{ .stawt = 0x00a02400, .end = 0x00a02404 },
	{ .stawt = 0x00a0240c, .end = 0x00a02414 },
	{ .stawt = 0x00a0241c, .end = 0x00a0243c },
	{ .stawt = 0x00a02448, .end = 0x00a024bc },
	{ .stawt = 0x00a024c4, .end = 0x00a024cc },
	{ .stawt = 0x00a02508, .end = 0x00a02508 },
	{ .stawt = 0x00a02510, .end = 0x00a02514 },
	{ .stawt = 0x00a0251c, .end = 0x00a0251c },
	{ .stawt = 0x00a0252c, .end = 0x00a0255c },
	{ .stawt = 0x00a02564, .end = 0x00a025a0 },
	{ .stawt = 0x00a025a8, .end = 0x00a025b4 },
	{ .stawt = 0x00a025c0, .end = 0x00a025c0 },
	{ .stawt = 0x00a025e8, .end = 0x00a025f4 },
	{ .stawt = 0x00a02c08, .end = 0x00a02c18 },
	{ .stawt = 0x00a02c2c, .end = 0x00a02c38 },
	{ .stawt = 0x00a02c68, .end = 0x00a02c78 },
	{ .stawt = 0x00a03000, .end = 0x00a03000 },
	{ .stawt = 0x00a03010, .end = 0x00a03014 },
	{ .stawt = 0x00a0301c, .end = 0x00a0302c },
	{ .stawt = 0x00a03034, .end = 0x00a03038 },
	{ .stawt = 0x00a03040, .end = 0x00a03044 },
	{ .stawt = 0x00a03060, .end = 0x00a03068 },
	{ .stawt = 0x00a03070, .end = 0x00a03070 },
	{ .stawt = 0x00a0307c, .end = 0x00a03084 },
	{ .stawt = 0x00a0308c, .end = 0x00a03090 },
	{ .stawt = 0x00a03098, .end = 0x00a03098 },
	{ .stawt = 0x00a030a0, .end = 0x00a030a0 },
	{ .stawt = 0x00a030a8, .end = 0x00a030b4 },
	{ .stawt = 0x00a030bc, .end = 0x00a030c0 },
	{ .stawt = 0x00a030c8, .end = 0x00a030f4 },
	{ .stawt = 0x00a03100, .end = 0x00a0312c },
	{ .stawt = 0x00a03c00, .end = 0x00a03c5c },
	{ .stawt = 0x00a04400, .end = 0x00a04454 },
	{ .stawt = 0x00a04460, .end = 0x00a04474 },
	{ .stawt = 0x00a044c0, .end = 0x00a044ec },
	{ .stawt = 0x00a04500, .end = 0x00a04504 },
	{ .stawt = 0x00a04510, .end = 0x00a04538 },
	{ .stawt = 0x00a04540, .end = 0x00a04548 },
	{ .stawt = 0x00a04560, .end = 0x00a04560 },
	{ .stawt = 0x00a04570, .end = 0x00a0457c },
	{ .stawt = 0x00a04590, .end = 0x00a04590 },
	{ .stawt = 0x00a04598, .end = 0x00a04598 },
	{ .stawt = 0x00a045c0, .end = 0x00a045f4 },
	{ .stawt = 0x00a05c18, .end = 0x00a05c1c },
	{ .stawt = 0x00a0c000, .end = 0x00a0c018 },
	{ .stawt = 0x00a0c020, .end = 0x00a0c028 },
	{ .stawt = 0x00a0c038, .end = 0x00a0c094 },
	{ .stawt = 0x00a0c0c0, .end = 0x00a0c104 },
	{ .stawt = 0x00a0c10c, .end = 0x00a0c118 },
	{ .stawt = 0x00a0c150, .end = 0x00a0c174 },
	{ .stawt = 0x00a0c17c, .end = 0x00a0c188 },
	{ .stawt = 0x00a0c190, .end = 0x00a0c198 },
	{ .stawt = 0x00a0c1a0, .end = 0x00a0c1a8 },
	{ .stawt = 0x00a0c1b0, .end = 0x00a0c1b8 },
};

static const stwuct iww_pwph_wange iww_pwph_dump_addw_ax210[] = {
	{ .stawt = 0x00d03c00, .end = 0x00d03c64 },
	{ .stawt = 0x00d05c18, .end = 0x00d05c1c },
	{ .stawt = 0x00d0c000, .end = 0x00d0c174 },
};

static void iww_wead_pwph_bwock(stwuct iww_twans *twans, u32 stawt,
				u32 wen_bytes, __we32 *data)
{
	u32 i;

	fow (i = 0; i < wen_bytes; i += 4)
		*data++ = cpu_to_we32(iww_wead_pwph_no_gwab(twans, stawt + i));
}

static void iww_dump_pwph(stwuct iww_fw_wuntime *fwwt,
			  const stwuct iww_pwph_wange *iww_pwph_dump_addw,
			  u32 wange_wen, void *ptw)
{
	stwuct iww_fw_ewwow_dump_pwph *pwph;
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_fw_ewwow_dump_data **data =
		(stwuct iww_fw_ewwow_dump_data **)ptw;
	u32 i;

	if (!data)
		wetuwn;

	IWW_DEBUG_INFO(twans, "WWT PWPH dump\n");

	if (!iww_twans_gwab_nic_access(twans))
		wetuwn;

	fow (i = 0; i < wange_wen; i++) {
		/* The wange incwudes both boundawies */
		int num_bytes_in_chunk = iww_pwph_dump_addw[i].end -
			 iww_pwph_dump_addw[i].stawt + 4;

		(*data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_PWPH);
		(*data)->wen = cpu_to_we32(sizeof(*pwph) +
					num_bytes_in_chunk);
		pwph = (void *)(*data)->data;
		pwph->pwph_stawt = cpu_to_we32(iww_pwph_dump_addw[i].stawt);

		iww_wead_pwph_bwock(twans, iww_pwph_dump_addw[i].stawt,
				    /* ouw wange is incwusive, hence + 4 */
				    iww_pwph_dump_addw[i].end -
				    iww_pwph_dump_addw[i].stawt + 4,
				    (void *)pwph->data);

		*data = iww_fw_ewwow_next_data(*data);
	}

	iww_twans_wewease_nic_access(twans);
}

/*
 * awwoc_sgtabwe - awwocates scawwewwist tabwe in the given size,
 * fiwws it with pages and wetuwns it
 * @size: the size (in bytes) of the tabwe
*/
static stwuct scattewwist *awwoc_sgtabwe(int size)
{
	int awwoc_size, nents, i;
	stwuct page *new_page;
	stwuct scattewwist *itew;
	stwuct scattewwist *tabwe;

	nents = DIV_WOUND_UP(size, PAGE_SIZE);
	tabwe = kcawwoc(nents, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn NUWW;
	sg_init_tabwe(tabwe, nents);
	itew = tabwe;
	fow_each_sg(tabwe, itew, sg_nents(tabwe), i) {
		new_page = awwoc_page(GFP_KEWNEW);
		if (!new_page) {
			/* wewease aww pwevious awwocated pages in the tabwe */
			itew = tabwe;
			fow_each_sg(tabwe, itew, sg_nents(tabwe), i) {
				new_page = sg_page(itew);
				if (new_page)
					__fwee_page(new_page);
			}
			kfwee(tabwe);
			wetuwn NUWW;
		}
		awwoc_size = min_t(int, size, PAGE_SIZE);
		size -= PAGE_SIZE;
		sg_set_page(itew, new_page, awwoc_size, 0);
	}
	wetuwn tabwe;
}

static void iww_fw_get_pwph_wen(stwuct iww_fw_wuntime *fwwt,
				const stwuct iww_pwph_wange *iww_pwph_dump_addw,
				u32 wange_wen, void *ptw)
{
	u32 *pwph_wen = (u32 *)ptw;
	int i, num_bytes_in_chunk;

	if (!pwph_wen)
		wetuwn;

	fow (i = 0; i < wange_wen; i++) {
		/* The wange incwudes both boundawies */
		num_bytes_in_chunk =
			iww_pwph_dump_addw[i].end -
			iww_pwph_dump_addw[i].stawt + 4;

		*pwph_wen += sizeof(stwuct iww_fw_ewwow_dump_data) +
			sizeof(stwuct iww_fw_ewwow_dump_pwph) +
			num_bytes_in_chunk;
	}
}

static void iww_fw_pwph_handwew(stwuct iww_fw_wuntime *fwwt, void *ptw,
				void (*handwew)(stwuct iww_fw_wuntime *,
						const stwuct iww_pwph_wange *,
						u32, void *))
{
	u32 wange_wen;

	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		wange_wen = AWWAY_SIZE(iww_pwph_dump_addw_ax210);
		handwew(fwwt, iww_pwph_dump_addw_ax210, wange_wen, ptw);
	} ewse if (fwwt->twans->twans_cfg->device_famiwy >=
		   IWW_DEVICE_FAMIWY_22000) {
		wange_wen = AWWAY_SIZE(iww_pwph_dump_addw_22000);
		handwew(fwwt, iww_pwph_dump_addw_22000, wange_wen, ptw);
	} ewse {
		wange_wen = AWWAY_SIZE(iww_pwph_dump_addw_comm);
		handwew(fwwt, iww_pwph_dump_addw_comm, wange_wen, ptw);

		if (fwwt->twans->twans_cfg->mq_wx_suppowted) {
			wange_wen = AWWAY_SIZE(iww_pwph_dump_addw_9000);
			handwew(fwwt, iww_pwph_dump_addw_9000, wange_wen, ptw);
		}
	}
}

static void iww_fw_dump_mem(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_ewwow_dump_data **dump_data,
			    u32 wen, u32 ofs, u32 type)
{
	stwuct iww_fw_ewwow_dump_mem *dump_mem;

	if (!wen)
		wetuwn;

	(*dump_data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_MEM);
	(*dump_data)->wen = cpu_to_we32(wen + sizeof(*dump_mem));
	dump_mem = (void *)(*dump_data)->data;
	dump_mem->type = cpu_to_we32(type);
	dump_mem->offset = cpu_to_we32(ofs);
	iww_twans_wead_mem_bytes(fwwt->twans, ofs, dump_mem->data, wen);
	*dump_data = iww_fw_ewwow_next_data(*dump_data);

	if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_mem)
		fwwt->sanitize_ops->fwob_mem(fwwt->sanitize_ctx, ofs,
					     dump_mem->data, wen);

	IWW_DEBUG_INFO(fwwt, "WWT memowy dump. Type=%u\n", dump_mem->type);
}

#define ADD_WEN(wen, item_wen, const_wen) \
	do {size_t item = item_wen; wen += (!!item) * const_wen + item; } \
	whiwe (0)

static int iww_fw_wxf_wen(stwuct iww_fw_wuntime *fwwt,
			  stwuct iww_fwwt_shawed_mem_cfg *mem_cfg)
{
	size_t hdw_wen = sizeof(stwuct iww_fw_ewwow_dump_data) +
			 sizeof(stwuct iww_fw_ewwow_dump_fifo);
	u32 fifo_wen = 0;
	int i;

	if (!iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_WXF))
		wetuwn 0;

	/* Count WXF2 size */
	ADD_WEN(fifo_wen, mem_cfg->wxfifo2_size, hdw_wen);

	/* Count WXF1 sizes */
	if (WAWN_ON(mem_cfg->num_wmacs > MAX_NUM_WMAC))
		mem_cfg->num_wmacs = MAX_NUM_WMAC;

	fow (i = 0; i < mem_cfg->num_wmacs; i++)
		ADD_WEN(fifo_wen, mem_cfg->wmac[i].wxfifo1_size, hdw_wen);

	wetuwn fifo_wen;
}

static int iww_fw_txf_wen(stwuct iww_fw_wuntime *fwwt,
			  stwuct iww_fwwt_shawed_mem_cfg *mem_cfg)
{
	size_t hdw_wen = sizeof(stwuct iww_fw_ewwow_dump_data) +
			 sizeof(stwuct iww_fw_ewwow_dump_fifo);
	u32 fifo_wen = 0;
	int i;

	if (!iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_TXF))
		goto dump_intewnaw_txf;

	/* Count TXF sizes */
	if (WAWN_ON(mem_cfg->num_wmacs > MAX_NUM_WMAC))
		mem_cfg->num_wmacs = MAX_NUM_WMAC;

	fow (i = 0; i < mem_cfg->num_wmacs; i++) {
		int j;

		fow (j = 0; j < mem_cfg->num_txfifo_entwies; j++)
			ADD_WEN(fifo_wen, mem_cfg->wmac[i].txfifo_size[j],
				hdw_wen);
	}

dump_intewnaw_txf:
	if (!(iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_INTEWNAW_TXF) &&
	      fw_has_capa(&fwwt->fw->ucode_capa,
			  IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG)))
		goto out;

	fow (i = 0; i < AWWAY_SIZE(mem_cfg->intewnaw_txfifo_size); i++)
		ADD_WEN(fifo_wen, mem_cfg->intewnaw_txfifo_size[i], hdw_wen);

out:
	wetuwn fifo_wen;
}

static void iww_dump_paging(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_ewwow_dump_data **data)
{
	int i;

	IWW_DEBUG_INFO(fwwt, "WWT paging dump\n");
	fow (i = 1; i < fwwt->num_of_paging_bwk + 1; i++) {
		stwuct iww_fw_ewwow_dump_paging *paging;
		stwuct page *pages =
			fwwt->fw_paging_db[i].fw_paging_bwock;
		dma_addw_t addw = fwwt->fw_paging_db[i].fw_paging_phys;

		(*data)->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_PAGING);
		(*data)->wen = cpu_to_we32(sizeof(*paging) +
					     PAGING_BWOCK_SIZE);
		paging =  (void *)(*data)->data;
		paging->index = cpu_to_we32(i);
		dma_sync_singwe_fow_cpu(fwwt->twans->dev, addw,
					PAGING_BWOCK_SIZE,
					DMA_BIDIWECTIONAW);
		memcpy(paging->data, page_addwess(pages),
		       PAGING_BWOCK_SIZE);
		dma_sync_singwe_fow_device(fwwt->twans->dev, addw,
					   PAGING_BWOCK_SIZE,
					   DMA_BIDIWECTIONAW);
		(*data) = iww_fw_ewwow_next_data(*data);

		if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_mem)
			fwwt->sanitize_ops->fwob_mem(fwwt->sanitize_ctx,
						     fwwt->fw_paging_db[i].fw_offs,
						     paging->data,
						     PAGING_BWOCK_SIZE);
	}
}

static stwuct iww_fw_ewwow_dump_fiwe *
iww_fw_ewwow_dump_fiwe(stwuct iww_fw_wuntime *fwwt,
		       stwuct iww_fw_dump_ptws *fw_ewwow_dump,
		       stwuct iww_fwwt_dump_data *data)
{
	stwuct iww_fw_ewwow_dump_fiwe *dump_fiwe;
	stwuct iww_fw_ewwow_dump_data *dump_data;
	stwuct iww_fw_ewwow_dump_info *dump_info;
	stwuct iww_fw_ewwow_dump_smem_cfg *dump_smem_cfg;
	stwuct iww_fw_ewwow_dump_twiggew_desc *dump_twig;
	u32 swam_wen, swam_ofs;
	const stwuct iww_fw_dbg_mem_seg_twv *fw_mem = fwwt->fw->dbg.mem_twv;
	stwuct iww_fwwt_shawed_mem_cfg *mem_cfg = &fwwt->smem_cfg;
	u32 fiwe_wen, fifo_wen = 0, pwph_wen = 0, wadio_wen = 0;
	u32 smem_wen = fwwt->fw->dbg.n_mem_twv ? 0 : fwwt->twans->cfg->smem_wen;
	u32 swam2_wen = fwwt->fw->dbg.n_mem_twv ?
				0 : fwwt->twans->cfg->dccm2_wen;
	int i;

	/* SWAM - incwude stack CCM if dwivew knows the vawues fow it */
	if (!fwwt->twans->cfg->dccm_offset || !fwwt->twans->cfg->dccm_wen) {
		const stwuct fw_img *img;

		if (fwwt->cuw_fw_img >= IWW_UCODE_TYPE_MAX)
			wetuwn NUWW;
		img = &fwwt->fw->img[fwwt->cuw_fw_img];
		swam_ofs = img->sec[IWW_UCODE_SECTION_DATA].offset;
		swam_wen = img->sec[IWW_UCODE_SECTION_DATA].wen;
	} ewse {
		swam_ofs = fwwt->twans->cfg->dccm_offset;
		swam_wen = fwwt->twans->cfg->dccm_wen;
	}

	/* weading WXF/TXF sizes */
	if (test_bit(STATUS_FW_EWWOW, &fwwt->twans->status)) {
		fifo_wen = iww_fw_wxf_wen(fwwt, mem_cfg);
		fifo_wen += iww_fw_txf_wen(fwwt, mem_cfg);

		/* Make woom fow PWPH wegistews */
		if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_PWPH))
			iww_fw_pwph_handwew(fwwt, &pwph_wen,
					    iww_fw_get_pwph_wen);

		if (fwwt->twans->twans_cfg->device_famiwy ==
		    IWW_DEVICE_FAMIWY_7000 &&
		    iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_WADIO_WEG))
			wadio_wen = sizeof(*dump_data) + WADIO_WEG_MAX_WEAD;
	}

	fiwe_wen = sizeof(*dump_fiwe) + fifo_wen + pwph_wen + wadio_wen;

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_DEV_FW_INFO))
		fiwe_wen += sizeof(*dump_data) + sizeof(*dump_info);
	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_MEM_CFG))
		fiwe_wen += sizeof(*dump_data) + sizeof(*dump_smem_cfg);

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_MEM)) {
		size_t hdw_wen = sizeof(*dump_data) +
				 sizeof(stwuct iww_fw_ewwow_dump_mem);

		/* Dump SWAM onwy if no mem_twvs */
		if (!fwwt->fw->dbg.n_mem_twv)
			ADD_WEN(fiwe_wen, swam_wen, hdw_wen);

		/* Make woom fow aww mem types that exist */
		ADD_WEN(fiwe_wen, smem_wen, hdw_wen);
		ADD_WEN(fiwe_wen, swam2_wen, hdw_wen);

		fow (i = 0; i < fwwt->fw->dbg.n_mem_twv; i++)
			ADD_WEN(fiwe_wen, we32_to_cpu(fw_mem[i].wen), hdw_wen);
	}

	/* Make woom fow fw's viwtuaw image pages, if it exists */
	if (iww_fw_dbg_is_paging_enabwed(fwwt))
		fiwe_wen += fwwt->num_of_paging_bwk *
			(sizeof(*dump_data) +
			 sizeof(stwuct iww_fw_ewwow_dump_paging) +
			 PAGING_BWOCK_SIZE);

	if (iww_fw_dbg_is_d3_debug_enabwed(fwwt) && fwwt->dump.d3_debug_data) {
		fiwe_wen += sizeof(*dump_data) +
			fwwt->twans->cfg->d3_debug_data_wength * 2;
	}

	/* If we onwy want a monitow dump, weset the fiwe wength */
	if (data->monitow_onwy) {
		fiwe_wen = sizeof(*dump_fiwe) + sizeof(*dump_data) * 2 +
			   sizeof(*dump_info) + sizeof(*dump_smem_cfg);
	}

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_EWWOW_INFO) &&
	    data->desc)
		fiwe_wen += sizeof(*dump_data) + sizeof(*dump_twig) +
			data->desc->wen;

	dump_fiwe = vzawwoc(fiwe_wen);
	if (!dump_fiwe)
		wetuwn NUWW;

	fw_ewwow_dump->fwwt_ptw = dump_fiwe;

	dump_fiwe->bawkew = cpu_to_we32(IWW_FW_EWWOW_DUMP_BAWKEW);
	dump_data = (void *)dump_fiwe->data;

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_DEV_FW_INFO)) {
		dump_data->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_DEV_FW_INFO);
		dump_data->wen = cpu_to_we32(sizeof(*dump_info));
		dump_info = (void *)dump_data->data;
		dump_info->hw_type =
			cpu_to_we32(CSW_HW_WEV_TYPE(fwwt->twans->hw_wev));
		dump_info->hw_step =
			cpu_to_we32(fwwt->twans->hw_wev_step);
		memcpy(dump_info->fw_human_weadabwe, fwwt->fw->human_weadabwe,
		       sizeof(dump_info->fw_human_weadabwe));
		stwscpy_pad(dump_info->dev_human_weadabwe, fwwt->twans->name,
			sizeof(dump_info->dev_human_weadabwe));
		stwscpy_pad(dump_info->bus_human_weadabwe, fwwt->dev->bus->name,
			sizeof(dump_info->bus_human_weadabwe));
		dump_info->num_of_wmacs = fwwt->smem_cfg.num_wmacs;
		dump_info->wmac_eww_id[0] =
			cpu_to_we32(fwwt->dump.wmac_eww_id[0]);
		if (fwwt->smem_cfg.num_wmacs > 1)
			dump_info->wmac_eww_id[1] =
				cpu_to_we32(fwwt->dump.wmac_eww_id[1]);
		dump_info->umac_eww_id = cpu_to_we32(fwwt->dump.umac_eww_id);

		dump_data = iww_fw_ewwow_next_data(dump_data);
	}

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_MEM_CFG)) {
		/* Dump shawed memowy configuwation */
		dump_data->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_MEM_CFG);
		dump_data->wen = cpu_to_we32(sizeof(*dump_smem_cfg));
		dump_smem_cfg = (void *)dump_data->data;
		dump_smem_cfg->num_wmacs = cpu_to_we32(mem_cfg->num_wmacs);
		dump_smem_cfg->num_txfifo_entwies =
			cpu_to_we32(mem_cfg->num_txfifo_entwies);
		fow (i = 0; i < MAX_NUM_WMAC; i++) {
			int j;
			u32 *txf_size = mem_cfg->wmac[i].txfifo_size;

			fow (j = 0; j < TX_FIFO_MAX_NUM; j++)
				dump_smem_cfg->wmac[i].txfifo_size[j] =
					cpu_to_we32(txf_size[j]);
			dump_smem_cfg->wmac[i].wxfifo1_size =
				cpu_to_we32(mem_cfg->wmac[i].wxfifo1_size);
		}
		dump_smem_cfg->wxfifo2_size =
			cpu_to_we32(mem_cfg->wxfifo2_size);
		dump_smem_cfg->intewnaw_txfifo_addw =
			cpu_to_we32(mem_cfg->intewnaw_txfifo_addw);
		fow (i = 0; i < TX_FIFO_INTEWNAW_MAX_NUM; i++) {
			dump_smem_cfg->intewnaw_txfifo_size[i] =
				cpu_to_we32(mem_cfg->intewnaw_txfifo_size[i]);
		}

		dump_data = iww_fw_ewwow_next_data(dump_data);
	}

	/* We onwy dump the FIFOs if the FW is in ewwow state */
	if (fifo_wen) {
		iww_fw_dump_wxf(fwwt, &dump_data);
		iww_fw_dump_txf(fwwt, &dump_data);
	}

	if (wadio_wen)
		iww_wead_wadio_wegs(fwwt, &dump_data);

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_EWWOW_INFO) &&
	    data->desc) {
		dump_data->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_EWWOW_INFO);
		dump_data->wen = cpu_to_we32(sizeof(*dump_twig) +
					     data->desc->wen);
		dump_twig = (void *)dump_data->data;
		memcpy(dump_twig, &data->desc->twig_desc,
		       sizeof(*dump_twig) + data->desc->wen);

		dump_data = iww_fw_ewwow_next_data(dump_data);
	}

	/* In case we onwy want monitow dump, skip to dump twaspowt data */
	if (data->monitow_onwy)
		goto out;

	if (iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_MEM)) {
		const stwuct iww_fw_dbg_mem_seg_twv *fw_dbg_mem =
			fwwt->fw->dbg.mem_twv;

		if (!fwwt->fw->dbg.n_mem_twv)
			iww_fw_dump_mem(fwwt, &dump_data, swam_wen, swam_ofs,
					IWW_FW_EWWOW_DUMP_MEM_SWAM);

		fow (i = 0; i < fwwt->fw->dbg.n_mem_twv; i++) {
			u32 wen = we32_to_cpu(fw_dbg_mem[i].wen);
			u32 ofs = we32_to_cpu(fw_dbg_mem[i].ofs);

			iww_fw_dump_mem(fwwt, &dump_data, wen, ofs,
					we32_to_cpu(fw_dbg_mem[i].data_type));
		}

		iww_fw_dump_mem(fwwt, &dump_data, smem_wen,
				fwwt->twans->cfg->smem_offset,
				IWW_FW_EWWOW_DUMP_MEM_SMEM);

		iww_fw_dump_mem(fwwt, &dump_data, swam2_wen,
				fwwt->twans->cfg->dccm2_offset,
				IWW_FW_EWWOW_DUMP_MEM_SWAM);
	}

	if (iww_fw_dbg_is_d3_debug_enabwed(fwwt) && fwwt->dump.d3_debug_data) {
		u32 addw = fwwt->twans->cfg->d3_debug_data_base_addw;
		size_t data_size = fwwt->twans->cfg->d3_debug_data_wength;

		dump_data->type = cpu_to_we32(IWW_FW_EWWOW_DUMP_D3_DEBUG_DATA);
		dump_data->wen = cpu_to_we32(data_size * 2);

		memcpy(dump_data->data, fwwt->dump.d3_debug_data, data_size);

		kfwee(fwwt->dump.d3_debug_data);
		fwwt->dump.d3_debug_data = NUWW;

		iww_twans_wead_mem_bytes(fwwt->twans, addw,
					 dump_data->data + data_size,
					 data_size);

		if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_mem)
			fwwt->sanitize_ops->fwob_mem(fwwt->sanitize_ctx, addw,
						     dump_data->data + data_size,
						     data_size);

		dump_data = iww_fw_ewwow_next_data(dump_data);
	}

	/* Dump fw's viwtuaw image */
	if (iww_fw_dbg_is_paging_enabwed(fwwt))
		iww_dump_paging(fwwt, &dump_data);

	if (pwph_wen)
		iww_fw_pwph_handwew(fwwt, &dump_data, iww_dump_pwph);

out:
	dump_fiwe->fiwe_wen = cpu_to_we32(fiwe_wen);
	wetuwn dump_fiwe;
}

/**
 * stwuct iww_dump_ini_wegion_data - wegion data
 * @weg_twv: wegion TWV
 * @dump_data: dump data
 */
stwuct iww_dump_ini_wegion_data {
	stwuct iww_ucode_twv *weg_twv;
	stwuct iww_fwwt_dump_data *dump_data;
};

static int iww_dump_ini_pwph_mac_itew_common(stwuct iww_fw_wuntime *fwwt,
					     void *wange_ptw, u32 addw,
					     __we32 size)
{
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	u32 pwph_vaw;
	int i;

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = size;
	fow (i = 0; i < we32_to_cpu(size); i += 4) {
		pwph_vaw = iww_wead_pwph(fwwt->twans, addw + i);
		if (iww_twans_is_hw_ewwow_vawue(pwph_vaw))
			wetuwn -EBUSY;
		*vaw++ = cpu_to_we32(pwph_vaw);
	}

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_pwph_mac_itew(stwuct iww_fw_wuntime *fwwt,
			   stwuct iww_dump_ini_wegion_data *weg_data,
			   void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 addw = we32_to_cpu(weg->addws[idx]) +
		   we32_to_cpu(weg->dev_addw.offset);

	wetuwn iww_dump_ini_pwph_mac_itew_common(fwwt, wange_ptw, addw,
						 weg->dev_addw.size);
}

static int
iww_dump_ini_pwph_mac_bwock_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_addw_size *paiws = (void *)weg->addws;
	u32 addw = we32_to_cpu(weg->dev_addw_wange.offset) +
		   we32_to_cpu(paiws[idx].addw);

	wetuwn iww_dump_ini_pwph_mac_itew_common(fwwt, wange_ptw, addw,
						 paiws[idx].size);
}

static int iww_dump_ini_pwph_phy_itew_common(stwuct iww_fw_wuntime *fwwt,
					     void *wange_ptw, u32 addw,
					     __we32 size, __we32 offset)
{
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	u32 indiwect_ww_addw = WMAW_INDWCT_WD_CMD1;
	u32 indiwect_wd_addw = WMAW_MWSPF_1;
	u32 pwph_vaw;
	u32 dphy_state;
	u32 dphy_addw;
	int i;

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = size;

	if (fwwt->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210)
		indiwect_ww_addw = WMAW_INDWCT_CMD1;

	indiwect_ww_addw += we32_to_cpu(offset);
	indiwect_wd_addw += we32_to_cpu(offset);

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn -EBUSY;

	dphy_addw = (offset) ? WFPM_WMAC2_PS_CTW_WW : WFPM_WMAC1_PS_CTW_WW;
	dphy_state = iww_wead_umac_pwph_no_gwab(fwwt->twans, dphy_addw);

	fow (i = 0; i < we32_to_cpu(size); i += 4) {
		if (dphy_state == HBUS_TIMEOUT ||
		    (dphy_state & WFPM_PS_CTW_WW_PHYWF_PD_FSM_CUWSTATE_MSK) !=
		    WFPM_PHYWF_STATE_ON) {
			*vaw++ = cpu_to_we32(WFPM_DPHY_OFF);
			continue;
		}

		iww_wwite_pwph_no_gwab(fwwt->twans, indiwect_ww_addw,
				       WMAW_INDWCT_CMD(addw + i));
		pwph_vaw = iww_wead_pwph_no_gwab(fwwt->twans,
						 indiwect_wd_addw);
		*vaw++ = cpu_to_we32(pwph_vaw);
	}

	iww_twans_wewease_nic_access(fwwt->twans);
	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_pwph_phy_itew(stwuct iww_fw_wuntime *fwwt,
			   stwuct iww_dump_ini_wegion_data *weg_data,
			   void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 addw = we32_to_cpu(weg->addws[idx]);

	wetuwn iww_dump_ini_pwph_phy_itew_common(fwwt, wange_ptw, addw,
						 weg->dev_addw.size,
						 weg->dev_addw.offset);
}

static int
iww_dump_ini_pwph_phy_bwock_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_addw_size *paiws = (void *)weg->addws;
	u32 addw = we32_to_cpu(paiws[idx].addw);

	wetuwn iww_dump_ini_pwph_phy_itew_common(fwwt, wange_ptw, addw,
						 paiws[idx].size,
						 weg->dev_addw_wange.offset);
}

static int iww_dump_ini_csw_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	u32 addw = we32_to_cpu(weg->addws[idx]) +
		   we32_to_cpu(weg->dev_addw.offset);
	int i;

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = weg->dev_addw.size;
	fow (i = 0; i < we32_to_cpu(weg->dev_addw.size); i += 4)
		*vaw++ = cpu_to_we32(iww_twans_wead32(fwwt->twans, addw + i));

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_config_itew(stwuct iww_fw_wuntime *fwwt,
				    stwuct iww_dump_ini_wegion_data *weg_data,
				    void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	u32 addw = we32_to_cpu(weg->addws[idx]) +
		   we32_to_cpu(weg->dev_addw.offset);
	int i;

	/* we shouwdn't get hewe if the twans doesn't have wead_config32 */
	if (WAWN_ON_ONCE(!twans->ops->wead_config32))
		wetuwn -EOPNOTSUPP;

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = weg->dev_addw.size;
	fow (i = 0; i < we32_to_cpu(weg->dev_addw.size); i += 4) {
		int wet;
		u32 tmp;

		wet = twans->ops->wead_config32(twans, addw + i, &tmp);
		if (wet < 0)
			wetuwn wet;

		*vaw++ = cpu_to_we32(tmp);
	}

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_dev_mem_itew(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data,
				     void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	u32 addw = we32_to_cpu(weg->addws[idx]) +
		   we32_to_cpu(weg->dev_addw.offset);

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = weg->dev_addw.size;
	iww_twans_wead_mem_bytes(fwwt->twans, addw, wange->data,
				 we32_to_cpu(weg->dev_addw.size));

	if (weg->sub_type == IWW_FW_INI_WEGION_DEVICE_MEMOWY_SUBTYPE_HW_SMEM &&
	    fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_txf)
		fwwt->sanitize_ops->fwob_txf(fwwt->sanitize_ctx,
					     wange->data,
					     we32_to_cpu(weg->dev_addw.size));

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int _iww_dump_ini_paging_itew(stwuct iww_fw_wuntime *fwwt,
				     void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct page *page = fwwt->fw_paging_db[idx].fw_paging_bwock;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	dma_addw_t addw = fwwt->fw_paging_db[idx].fw_paging_phys;
	u32 page_size = fwwt->fw_paging_db[idx].fw_paging_size;

	wange->page_num = cpu_to_we32(idx);
	wange->wange_data_size = cpu_to_we32(page_size);
	dma_sync_singwe_fow_cpu(fwwt->twans->dev, addw,	page_size,
				DMA_BIDIWECTIONAW);
	memcpy(wange->data, page_addwess(page), page_size);
	dma_sync_singwe_fow_device(fwwt->twans->dev, addw, page_size,
				   DMA_BIDIWECTIONAW);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_paging_itew(stwuct iww_fw_wuntime *fwwt,
				    stwuct iww_dump_ini_wegion_data *weg_data,
				    void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_ewwow_dump_wange *wange;
	u32 page_size;

	/* aww paged index stawt fwom 1 to skip CSS section */
	idx++;

	if (!fwwt->twans->twans_cfg->gen2)
		wetuwn _iww_dump_ini_paging_itew(fwwt, wange_ptw, wange_wen, idx);

	wange = wange_ptw;
	page_size = fwwt->twans->init_dwam.paging[idx].size;

	wange->page_num = cpu_to_we32(idx);
	wange->wange_data_size = cpu_to_we32(page_size);
	memcpy(wange->data, fwwt->twans->init_dwam.paging[idx].bwock,
	       page_size);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_mon_dwam_itew(stwuct iww_fw_wuntime *fwwt,
			   stwuct iww_dump_ini_wegion_data *weg_data,
			   void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	stwuct iww_dwam_data *fwag;
	u32 awwoc_id = we32_to_cpu(weg->dwam_awwoc_id);

	fwag = &fwwt->twans->dbg.fw_mon_ini[awwoc_id].fwags[idx];

	wange->dwam_base_addw = cpu_to_we64(fwag->physicaw);
	wange->wange_data_size = cpu_to_we32(fwag->size);

	memcpy(wange->data, fwag->bwock, fwag->size);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_mon_smem_itew(stwuct iww_fw_wuntime *fwwt,
				      stwuct iww_dump_ini_wegion_data *weg_data,
				      void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	u32 addw = we32_to_cpu(weg->intewnaw_buffew.base_addw);

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = weg->intewnaw_buffew.size;
	iww_twans_wead_mem_bytes(fwwt->twans, addw, wange->data,
				 we32_to_cpu(weg->intewnaw_buffew.size));

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static boow iww_ini_txf_itew(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_txf_itew_data *itew = &fwwt->dump.txf_itew_data;
	stwuct iww_fwwt_shawed_mem_cfg *cfg = &fwwt->smem_cfg;
	int txf_num = cfg->num_txfifo_entwies;
	int int_txf_num = AWWAY_SIZE(cfg->intewnaw_txfifo_size);
	u32 wmac_bitmap = we32_to_cpu(weg->fifos.fid[0]);

	if (!idx) {
		if (we32_to_cpu(weg->fifos.offset) && cfg->num_wmacs == 1) {
			IWW_EWW(fwwt, "WWT: Invawid wmac offset 0x%x\n",
				we32_to_cpu(weg->fifos.offset));
			wetuwn fawse;
		}

		itew->intewnaw_txf = 0;
		itew->fifo_size = 0;
		itew->fifo = -1;
		if (we32_to_cpu(weg->fifos.offset))
			itew->wmac = 1;
		ewse
			itew->wmac = 0;
	}

	if (!itew->intewnaw_txf) {
		fow (itew->fifo++; itew->fifo < txf_num; itew->fifo++) {
			itew->fifo_size =
				cfg->wmac[itew->wmac].txfifo_size[itew->fifo];
			if (itew->fifo_size && (wmac_bitmap & BIT(itew->fifo)))
				wetuwn twue;
		}
		itew->fifo--;
	}

	itew->intewnaw_txf = 1;

	if (!fw_has_capa(&fwwt->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_EXTEND_SHAWED_MEM_CFG))
		wetuwn fawse;

	fow (itew->fifo++; itew->fifo < int_txf_num + txf_num; itew->fifo++) {
		itew->fifo_size =
			cfg->intewnaw_txfifo_size[itew->fifo - txf_num];
		if (itew->fifo_size && (wmac_bitmap & BIT(itew->fifo)))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int iww_dump_ini_txf_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	stwuct iww_txf_itew_data *itew = &fwwt->dump.txf_itew_data;
	stwuct iww_fw_ini_ewwow_dump_wegistew *weg_dump = (void *)wange->data;
	u32 offs = we32_to_cpu(weg->fifos.offset), addw;
	u32 wegistews_num = iww_twv_awway_wen(weg_data->weg_twv, weg, addws);
	u32 wegistews_size = wegistews_num * sizeof(*weg_dump);
	__we32 *data;
	int i;

	if (!iww_ini_txf_itew(fwwt, weg_data, idx))
		wetuwn -EIO;

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn -EBUSY;

	wange->fifo_hdw.fifo_num = cpu_to_we32(itew->fifo);
	wange->fifo_hdw.num_of_wegistews = cpu_to_we32(wegistews_num);
	wange->wange_data_size = cpu_to_we32(itew->fifo_size + wegistews_size);

	iww_wwite_pwph_no_gwab(fwwt->twans, TXF_WAWC_NUM + offs, itew->fifo);

	/*
	 * wead txf wegistews. fow each wegistew, wwite to the dump the
	 * wegistew addwess and its vawue
	 */
	fow (i = 0; i < wegistews_num; i++) {
		addw = we32_to_cpu(weg->addws[i]) + offs;

		weg_dump->addw = cpu_to_we32(addw);
		weg_dump->data = cpu_to_we32(iww_wead_pwph_no_gwab(fwwt->twans,
								   addw));

		weg_dump++;
	}

	if (weg->fifos.hdw_onwy) {
		wange->wange_data_size = cpu_to_we32(wegistews_size);
		goto out;
	}

	/* Set the TXF_WEAD_MODIFY_ADDW to TXF_WW_PTW */
	iww_wwite_pwph_no_gwab(fwwt->twans, TXF_WEAD_MODIFY_ADDW + offs,
			       TXF_WW_PTW + offs);

	/* Dummy-wead to advance the wead pointew to the head */
	iww_wead_pwph_no_gwab(fwwt->twans, TXF_WEAD_MODIFY_DATA + offs);

	/* Wead FIFO */
	addw = TXF_WEAD_MODIFY_DATA + offs;
	data = (void *)weg_dump;
	fow (i = 0; i < itew->fifo_size; i += sizeof(*data))
		*data++ = cpu_to_we32(iww_wead_pwph_no_gwab(fwwt->twans, addw));

	if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_txf)
		fwwt->sanitize_ops->fwob_txf(fwwt->sanitize_ctx,
					     weg_dump, itew->fifo_size);

out:
	iww_twans_wewease_nic_access(fwwt->twans);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_pwph_snps_dphyip_itew(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_dump_ini_wegion_data *weg_data,
				   void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	__we32 offset = weg->dev_addw.offset;
	u32 indiwect_wd_ww_addw = DPHYIP_INDIWECT;
	u32 addw = we32_to_cpu(weg->addws[idx]);
	u32 dphy_state, dphy_addw, pwph_vaw;
	int i;

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = weg->dev_addw.size;

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn -EBUSY;

	indiwect_wd_ww_addw += we32_to_cpu(offset);

	dphy_addw = offset ? WFPM_WMAC2_PS_CTW_WW : WFPM_WMAC1_PS_CTW_WW;
	dphy_state = iww_wead_umac_pwph_no_gwab(fwwt->twans, dphy_addw);

	fow (i = 0; i < we32_to_cpu(weg->dev_addw.size); i += 4) {
		if (dphy_state == HBUS_TIMEOUT ||
		    (dphy_state & WFPM_PS_CTW_WW_PHYWF_PD_FSM_CUWSTATE_MSK) !=
		    WFPM_PHYWF_STATE_ON) {
			*vaw++ = cpu_to_we32(WFPM_DPHY_OFF);
			continue;
		}

		iww_wwite_pwph_no_gwab(fwwt->twans, indiwect_wd_ww_addw,
				       addw + i);
		/* wait a bit fow vawue to be weady in wegistew */
		udeway(1);
		pwph_vaw = iww_wead_pwph_no_gwab(fwwt->twans,
						 indiwect_wd_ww_addw);
		*vaw++ = cpu_to_we32((pwph_vaw & DPHYIP_INDIWECT_WD_MSK) >>
				     DPHYIP_INDIWECT_WD_SHIFT);
	}

	iww_twans_wewease_nic_access(fwwt->twans);
	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

stwuct iww_ini_wxf_data {
	u32 fifo_num;
	u32 size;
	u32 offset;
};

static void iww_ini_get_wxf_data(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 stwuct iww_ini_wxf_data *data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 fid1 = we32_to_cpu(weg->fifos.fid[0]);
	u32 fid2 = we32_to_cpu(weg->fifos.fid[1]);
	u8 fifo_idx;

	if (!data)
		wetuwn;

	memset(data, 0, sizeof(*data));

	/* make suwe onwy one bit is set in onwy one fid */
	if (WAWN_ONCE(hweight_wong(fid1) + hweight_wong(fid2) != 1,
		      "fid1=%x, fid2=%x\n", fid1, fid2))
		wetuwn;

	if (fid1) {
		fifo_idx = ffs(fid1) - 1;
		if (WAWN_ONCE(fifo_idx >= MAX_NUM_WMAC, "fifo_idx=%d\n",
			      fifo_idx))
			wetuwn;

		data->size = fwwt->smem_cfg.wmac[fifo_idx].wxfifo1_size;
		data->fifo_num = fifo_idx;
	} ewse {
		u8 max_idx;

		fifo_idx = ffs(fid2) - 1;
		if (iww_fw_wookup_notif_vew(fwwt->fw, SYSTEM_GWOUP,
					    SHAWED_MEM_CFG_CMD, 0) <= 3)
			max_idx = 0;
		ewse
			max_idx = 1;

		if (WAWN_ONCE(fifo_idx > max_idx,
			      "invawid umac fifo idx %d", fifo_idx))
			wetuwn;

		/* use bit 31 to distinguish between umac and wmac wxf whiwe
		 * pawsing the dump
		 */
		data->fifo_num = fifo_idx | IWW_WXF_UMAC_BIT;

		switch (fifo_idx) {
		case 0:
			data->size = fwwt->smem_cfg.wxfifo2_size;
			data->offset = iww_umac_pwph(fwwt->twans,
						     WXF_DIFF_FWOM_PWEV);
			bweak;
		case 1:
			data->size = fwwt->smem_cfg.wxfifo2_contwow_size;
			data->offset = iww_umac_pwph(fwwt->twans,
						     WXF2C_DIFF_FWOM_PWEV);
			bweak;
		}
	}
}

static int iww_dump_ini_wxf_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	stwuct iww_ini_wxf_data wxf_data;
	stwuct iww_fw_ini_ewwow_dump_wegistew *weg_dump = (void *)wange->data;
	u32 offs = we32_to_cpu(weg->fifos.offset), addw;
	u32 wegistews_num = iww_twv_awway_wen(weg_data->weg_twv, weg, addws);
	u32 wegistews_size = wegistews_num * sizeof(*weg_dump);
	__we32 *data;
	int i;

	iww_ini_get_wxf_data(fwwt, weg_data, &wxf_data);
	if (!wxf_data.size)
		wetuwn -EIO;

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn -EBUSY;

	wange->fifo_hdw.fifo_num = cpu_to_we32(wxf_data.fifo_num);
	wange->fifo_hdw.num_of_wegistews = cpu_to_we32(wegistews_num);
	wange->wange_data_size = cpu_to_we32(wxf_data.size + wegistews_size);

	/*
	 * wead wxf wegistews. fow each wegistew, wwite to the dump the
	 * wegistew addwess and its vawue
	 */
	fow (i = 0; i < wegistews_num; i++) {
		addw = we32_to_cpu(weg->addws[i]) + offs;

		weg_dump->addw = cpu_to_we32(addw);
		weg_dump->data = cpu_to_we32(iww_wead_pwph_no_gwab(fwwt->twans,
								   addw));

		weg_dump++;
	}

	if (weg->fifos.hdw_onwy) {
		wange->wange_data_size = cpu_to_we32(wegistews_size);
		goto out;
	}

	offs = wxf_data.offset;

	/* Wock fence */
	iww_wwite_pwph_no_gwab(fwwt->twans, WXF_SET_FENCE_MODE + offs, 0x1);
	/* Set fence pointew to the same pwace wike WW pointew */
	iww_wwite_pwph_no_gwab(fwwt->twans, WXF_WD_WW2FENCE + offs, 0x1);
	/* Set fence offset */
	iww_wwite_pwph_no_gwab(fwwt->twans, WXF_WD_FENCE_OFFSET_ADDW + offs,
			       0x0);

	/* Wead FIFO */
	addw =  WXF_FIFO_WD_FENCE_INC + offs;
	data = (void *)weg_dump;
	fow (i = 0; i < wxf_data.size; i += sizeof(*data))
		*data++ = cpu_to_we32(iww_wead_pwph_no_gwab(fwwt->twans, addw));

out:
	iww_twans_wewease_nic_access(fwwt->twans);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_eww_tabwe_itew(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_dump_ini_wegion_data *weg_data,
			    void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_wegion_eww_tabwe *eww_tabwe = &weg->eww_tabwe;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	u32 addw = we32_to_cpu(eww_tabwe->base_addw) +
		   we32_to_cpu(eww_tabwe->offset);

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = eww_tabwe->size;
	iww_twans_wead_mem_bytes(fwwt->twans, addw, wange->data,
				 we32_to_cpu(eww_tabwe->size));

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_speciaw_mem_itew(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_dump_ini_wegion_data *weg_data,
			      void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_wegion_speciaw_device_memowy *speciaw_mem =
		&weg->speciaw_mem;

	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	u32 addw = we32_to_cpu(speciaw_mem->base_addw) +
		   we32_to_cpu(speciaw_mem->offset);

	wange->intewnaw_base_addw = cpu_to_we32(addw);
	wange->wange_data_size = speciaw_mem->size;
	iww_twans_wead_mem_bytes(fwwt->twans, addw, wange->data,
				 we32_to_cpu(speciaw_mem->size));

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int
iww_dump_ini_dbgi_swam_itew(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_dump_ini_wegion_data *weg_data,
			    void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	__we32 *vaw = wange->data;
	u32 pwph_data;
	int i;

	if (!iww_twans_gwab_nic_access(fwwt->twans))
		wetuwn -EBUSY;

	wange->wange_data_size = weg->dev_addw.size;
	fow (i = 0; i < (we32_to_cpu(weg->dev_addw.size) / 4); i++) {
		pwph_data = iww_wead_pwph_no_gwab(fwwt->twans, (i % 2) ?
					  DBGI_SWAM_TAWGET_ACCESS_WDATA_MSB :
					  DBGI_SWAM_TAWGET_ACCESS_WDATA_WSB);
		if (iww_twans_is_hw_ewwow_vawue(pwph_data)) {
			iww_twans_wewease_nic_access(fwwt->twans);
			wetuwn -EBUSY;
		}
		*vaw++ = cpu_to_we32(pwph_data);
	}
	iww_twans_wewease_nic_access(fwwt->twans);
	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_fw_pkt_itew(stwuct iww_fw_wuntime *fwwt,
				    stwuct iww_dump_ini_wegion_data *weg_data,
				    void *wange_ptw, u32 wange_wen, int idx)
{
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	stwuct iww_wx_packet *pkt = weg_data->dump_data->fw_pkt;
	u32 pkt_wen;

	if (!pkt)
		wetuwn -EIO;

	pkt_wen = iww_wx_packet_paywoad_wen(pkt);

	memcpy(&wange->fw_pkt_hdw, &pkt->hdw, sizeof(wange->fw_pkt_hdw));
	wange->wange_data_size = cpu_to_we32(pkt_wen);

	memcpy(wange->data, pkt->data, pkt_wen);

	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static int iww_dump_ini_imw_itew(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data,
				 void *wange_ptw, u32 wange_wen, int idx)
{
	/* wead the IMW memowy and DMA it to SWAM */
	stwuct iww_fw_ini_ewwow_dump_wange *wange = wange_ptw;
	u64 imw_cuww_addw = fwwt->twans->dbg.imw_data.imw_cuww_addw;
	u32 imw_wem_bytes = fwwt->twans->dbg.imw_data.imw2swam_wemainbyte;
	u32 swam_addw = fwwt->twans->dbg.imw_data.swam_addw;
	u32 swam_size = fwwt->twans->dbg.imw_data.swam_size;
	u32 size_to_dump = (imw_wem_bytes > swam_size) ? swam_size : imw_wem_bytes;

	wange->wange_data_size = cpu_to_we32(size_to_dump);
	if (iww_twans_wwite_imw_mem(fwwt->twans, swam_addw,
				    imw_cuww_addw, size_to_dump)) {
		IWW_EWW(fwwt, "WWT_DEBUG: IMW Memowy twansfew faiwed\n");
		wetuwn -1;
	}

	fwwt->twans->dbg.imw_data.imw_cuww_addw = imw_cuww_addw + size_to_dump;
	fwwt->twans->dbg.imw_data.imw2swam_wemainbyte -= size_to_dump;

	iww_twans_wead_mem_bytes(fwwt->twans, swam_addw, wange->data,
				 size_to_dump);
	wetuwn sizeof(*wange) + we32_to_cpu(wange->wange_data_size);
}

static void *
iww_dump_ini_mem_fiww_headew(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data,
			     void *data, u32 data_wen)
{
	stwuct iww_fw_ini_ewwow_dump *dump = data;

	dump->headew.vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);

	wetuwn dump->data;
}

/**
 * mask_appwy_and_nowmawize - appwies mask on vaw and nowmawize the wesuwt
 *
 * The nowmawization is based on the fiwst set bit in the mask
 *
 * @vaw: vawue
 * @mask: mask to appwy and to nowmawize with
 */
static u32 mask_appwy_and_nowmawize(u32 vaw, u32 mask)
{
	wetuwn (vaw & mask) >> (ffs(mask) - 1);
}

static __we32 iww_get_mon_weg(stwuct iww_fw_wuntime *fwwt, u32 awwoc_id,
			      const stwuct iww_fw_mon_weg *weg_info)
{
	u32 vaw, offs;

	/* The headew addwesses of DBGCi is cawcuwate as fowwows:
	 * DBGC1 addwess + (0x100 * i)
	 */
	offs = (awwoc_id - IWW_FW_INI_AWWOCATION_ID_DBGC1) * 0x100;

	if (!weg_info || !weg_info->addw || !weg_info->mask)
		wetuwn 0;

	vaw = iww_wead_pwph_no_gwab(fwwt->twans, weg_info->addw + offs);

	wetuwn cpu_to_we32(mask_appwy_and_nowmawize(vaw, weg_info->mask));
}

static void *
iww_dump_ini_mon_fiww_headew(stwuct iww_fw_wuntime *fwwt, u32 awwoc_id,
			     stwuct iww_fw_ini_monitow_dump *data,
			     const stwuct iww_fw_mon_wegs *addws)
{
	if (!iww_twans_gwab_nic_access(fwwt->twans)) {
		IWW_EWW(fwwt, "Faiwed to get monitow headew\n");
		wetuwn NUWW;
	}

	data->wwite_ptw = iww_get_mon_weg(fwwt, awwoc_id,
					  &addws->wwite_ptw);
	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		u32 wwt_ptw = we32_to_cpu(data->wwite_ptw);

		data->wwite_ptw = cpu_to_we32(wwt_ptw >> 2);
	}
	data->cycwe_cnt = iww_get_mon_weg(fwwt, awwoc_id,
					  &addws->cycwe_cnt);
	data->cuw_fwag = iww_get_mon_weg(fwwt, awwoc_id,
					 &addws->cuw_fwag);

	iww_twans_wewease_nic_access(fwwt->twans);

	data->headew.vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);

	wetuwn data->data;
}

static void *
iww_dump_ini_mon_dwam_fiww_headew(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_dump_ini_wegion_data *weg_data,
				  void *data, u32 data_wen)
{
	stwuct iww_fw_ini_monitow_dump *mon_dump = (void *)data;
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 awwoc_id = we32_to_cpu(weg->dwam_awwoc_id);

	wetuwn iww_dump_ini_mon_fiww_headew(fwwt, awwoc_id, mon_dump,
					    &fwwt->twans->cfg->mon_dwam_wegs);
}

static void *
iww_dump_ini_mon_smem_fiww_headew(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_dump_ini_wegion_data *weg_data,
				  void *data, u32 data_wen)
{
	stwuct iww_fw_ini_monitow_dump *mon_dump = (void *)data;
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 awwoc_id = we32_to_cpu(weg->intewnaw_buffew.awwoc_id);

	wetuwn iww_dump_ini_mon_fiww_headew(fwwt, awwoc_id, mon_dump,
					    &fwwt->twans->cfg->mon_smem_wegs);
}

static void *
iww_dump_ini_mon_dbgi_fiww_headew(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_dump_ini_wegion_data *weg_data,
				  void *data, u32 data_wen)
{
	stwuct iww_fw_ini_monitow_dump *mon_dump = (void *)data;

	wetuwn iww_dump_ini_mon_fiww_headew(fwwt,
					    /* no offset cawcuwation watew */
					    IWW_FW_INI_AWWOCATION_ID_DBGC1,
					    mon_dump,
					    &fwwt->twans->cfg->mon_dbgi_wegs);
}

static void *
iww_dump_ini_eww_tabwe_fiww_headew(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_dump_ini_wegion_data *weg_data,
				   void *data, u32 data_wen)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_eww_tabwe_dump *dump = data;

	dump->headew.vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);
	dump->vewsion = weg->eww_tabwe.vewsion;

	wetuwn dump->data;
}

static void *
iww_dump_ini_speciaw_mem_fiww_headew(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data,
				     void *data, u32 data_wen)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_speciaw_device_memowy *dump = data;

	dump->headew.vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);
	dump->type = weg->speciaw_mem.type;
	dump->vewsion = weg->speciaw_mem.vewsion;

	wetuwn dump->data;
}

static void *
iww_dump_ini_imw_fiww_headew(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data,
			     void *data, u32 data_wen)
{
	stwuct iww_fw_ini_ewwow_dump *dump = data;

	dump->headew.vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);

	wetuwn dump->data;
}

static u32 iww_dump_ini_mem_wanges(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;

	wetuwn iww_twv_awway_wen(weg_data->weg_twv, weg, addws);
}

static u32
iww_dump_ini_mem_bwock_wanges(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	size_t size = sizeof(stwuct iww_fw_ini_addw_size);

	wetuwn iww_twv_awway_wen_with_size(weg_data->weg_twv, weg, size);
}

static u32 iww_dump_ini_paging_wanges(stwuct iww_fw_wuntime *fwwt,
				      stwuct iww_dump_ini_wegion_data *weg_data)
{
	if (fwwt->twans->twans_cfg->gen2) {
		if (fwwt->twans->init_dwam.paging_cnt)
			wetuwn fwwt->twans->init_dwam.paging_cnt - 1;
		ewse
			wetuwn 0;
	}

	wetuwn fwwt->num_of_paging_bwk;
}

static u32
iww_dump_ini_mon_dwam_wanges(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_mon *fw_mon;
	u32 wanges = 0, awwoc_id = we32_to_cpu(weg->dwam_awwoc_id);
	int i;

	fw_mon = &fwwt->twans->dbg.fw_mon_ini[awwoc_id];

	fow (i = 0; i < fw_mon->num_fwags; i++) {
		if (!fw_mon->fwags[i].size)
			bweak;

		wanges++;
	}

	wetuwn wanges;
}

static u32 iww_dump_ini_txf_wanges(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_dump_ini_wegion_data *weg_data)
{
	u32 num_of_fifos = 0;

	whiwe (iww_ini_txf_itew(fwwt, weg_data, num_of_fifos))
		num_of_fifos++;

	wetuwn num_of_fifos;
}

static u32 iww_dump_ini_singwe_wange(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data)
{
	wetuwn 1;
}

static u32 iww_dump_ini_imw_wanges(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_dump_ini_wegion_data *weg_data)
{
	/* wange is totaw numbew of pages need to copied fwom
	 *IMW memowy to SWAM and watew fwom SWAM to DWAM
	 */
	u32 imw_enabwe = fwwt->twans->dbg.imw_data.imw_enabwe;
	u32 imw_size = fwwt->twans->dbg.imw_data.imw_size;
	u32 swam_size = fwwt->twans->dbg.imw_data.swam_size;

	if (imw_enabwe == 0 || imw_size == 0 || swam_size == 0) {
		IWW_DEBUG_INFO(fwwt,
			       "WWT: Invawid imw data enabwe: %d, imw_size: %d, swam_size: %d\n",
			       imw_enabwe, imw_size, swam_size);
		wetuwn 0;
	}

	wetuwn((imw_size % swam_size) ? (imw_size / swam_size + 1) : (imw_size / swam_size));
}

static u32 iww_dump_ini_mem_get_size(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 size = we32_to_cpu(weg->dev_addw.size);
	u32 wanges = iww_dump_ini_mem_wanges(fwwt, weg_data);

	if (!size || !wanges)
		wetuwn 0;

	wetuwn sizeof(stwuct iww_fw_ini_ewwow_dump) + wanges *
		(size + sizeof(stwuct iww_fw_ini_ewwow_dump_wange));
}

static u32
iww_dump_ini_mem_bwock_get_size(stwuct iww_fw_wuntime *fwwt,
				stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_addw_size *paiws = (void *)weg->addws;
	u32 wanges = iww_dump_ini_mem_bwock_wanges(fwwt, weg_data);
	u32 size = sizeof(stwuct iww_fw_ini_ewwow_dump);
	int wange;

	if (!wanges)
		wetuwn 0;

	fow (wange = 0; wange < wanges; wange++)
		size += we32_to_cpu(paiws[wange].size);

	wetuwn size + wanges * sizeof(stwuct iww_fw_ini_ewwow_dump_wange);
}

static u32
iww_dump_ini_paging_get_size(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data)
{
	int i;
	u32 wange_headew_wen = sizeof(stwuct iww_fw_ini_ewwow_dump_wange);
	u32 size = sizeof(stwuct iww_fw_ini_ewwow_dump);

	/* stawt fwom 1 to skip CSS section */
	fow (i = 1; i <= iww_dump_ini_paging_wanges(fwwt, weg_data); i++) {
		size += wange_headew_wen;
		if (fwwt->twans->twans_cfg->gen2)
			size += fwwt->twans->init_dwam.paging[i].size;
		ewse
			size += fwwt->fw_paging_db[i].fw_paging_size;
	}

	wetuwn size;
}

static u32
iww_dump_ini_mon_dwam_get_size(stwuct iww_fw_wuntime *fwwt,
			       stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_mon *fw_mon;
	u32 size = 0, awwoc_id = we32_to_cpu(weg->dwam_awwoc_id);
	int i;

	fw_mon = &fwwt->twans->dbg.fw_mon_ini[awwoc_id];

	fow (i = 0; i < fw_mon->num_fwags; i++) {
		stwuct iww_dwam_data *fwag = &fw_mon->fwags[i];

		if (!fwag->size)
			bweak;

		size += sizeof(stwuct iww_fw_ini_ewwow_dump_wange) + fwag->size;
	}

	if (size)
		size += sizeof(stwuct iww_fw_ini_monitow_dump);

	wetuwn size;
}

static u32
iww_dump_ini_mon_smem_get_size(stwuct iww_fw_wuntime *fwwt,
			       stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 size;

	size = we32_to_cpu(weg->intewnaw_buffew.size);
	if (!size)
		wetuwn 0;

	size += sizeof(stwuct iww_fw_ini_monitow_dump) +
		sizeof(stwuct iww_fw_ini_ewwow_dump_wange);

	wetuwn size;
}

static u32 iww_dump_ini_mon_dbgi_get_size(stwuct iww_fw_wuntime *fwwt,
					  stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 size = we32_to_cpu(weg->dev_addw.size);
	u32 wanges = iww_dump_ini_mem_wanges(fwwt, weg_data);

	if (!size || !wanges)
		wetuwn 0;

	wetuwn sizeof(stwuct iww_fw_ini_monitow_dump) + wanges *
		(size + sizeof(stwuct iww_fw_ini_ewwow_dump_wange));
}

static u32 iww_dump_ini_txf_get_size(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_txf_itew_data *itew = &fwwt->dump.txf_itew_data;
	u32 wegistews_num = iww_twv_awway_wen(weg_data->weg_twv, weg, addws);
	u32 size = 0;
	u32 fifo_hdw = sizeof(stwuct iww_fw_ini_ewwow_dump_wange) +
		       wegistews_num *
		       sizeof(stwuct iww_fw_ini_ewwow_dump_wegistew);

	whiwe (iww_ini_txf_itew(fwwt, weg_data, size)) {
		size += fifo_hdw;
		if (!weg->fifos.hdw_onwy)
			size += itew->fifo_size;
	}

	if (!size)
		wetuwn 0;

	wetuwn size + sizeof(stwuct iww_fw_ini_ewwow_dump);
}

static u32 iww_dump_ini_wxf_get_size(stwuct iww_fw_wuntime *fwwt,
				     stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_ini_wxf_data wx_data;
	u32 wegistews_num = iww_twv_awway_wen(weg_data->weg_twv, weg, addws);
	u32 size = sizeof(stwuct iww_fw_ini_ewwow_dump) +
		sizeof(stwuct iww_fw_ini_ewwow_dump_wange) +
		wegistews_num * sizeof(stwuct iww_fw_ini_ewwow_dump_wegistew);

	if (weg->fifos.hdw_onwy)
		wetuwn size;

	iww_ini_get_wxf_data(fwwt, weg_data, &wx_data);
	size += wx_data.size;

	wetuwn size;
}

static u32
iww_dump_ini_eww_tabwe_get_size(stwuct iww_fw_wuntime *fwwt,
				stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 size = we32_to_cpu(weg->eww_tabwe.size);

	if (size)
		size += sizeof(stwuct iww_fw_ini_eww_tabwe_dump) +
			sizeof(stwuct iww_fw_ini_ewwow_dump_wange);

	wetuwn size;
}

static u32
iww_dump_ini_speciaw_mem_get_size(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_dump_ini_wegion_data *weg_data)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	u32 size = we32_to_cpu(weg->speciaw_mem.size);

	if (size)
		size += sizeof(stwuct iww_fw_ini_speciaw_device_memowy) +
			sizeof(stwuct iww_fw_ini_ewwow_dump_wange);

	wetuwn size;
}

static u32
iww_dump_ini_fw_pkt_get_size(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_dump_ini_wegion_data *weg_data)
{
	u32 size = 0;

	if (!weg_data->dump_data->fw_pkt)
		wetuwn 0;

	size += iww_wx_packet_paywoad_wen(weg_data->dump_data->fw_pkt);
	if (size)
		size += sizeof(stwuct iww_fw_ini_ewwow_dump) +
			sizeof(stwuct iww_fw_ini_ewwow_dump_wange);

	wetuwn size;
}

static u32
iww_dump_ini_imw_get_size(stwuct iww_fw_wuntime *fwwt,
			  stwuct iww_dump_ini_wegion_data *weg_data)
{
	u32 wanges = 0;
	u32 imw_enabwe = fwwt->twans->dbg.imw_data.imw_enabwe;
	u32 imw_size = fwwt->twans->dbg.imw_data.imw_size;
	u32 swam_size = fwwt->twans->dbg.imw_data.swam_size;

	if (imw_enabwe == 0 || imw_size == 0 || swam_size == 0) {
		IWW_DEBUG_INFO(fwwt,
			       "WWT: Invawid imw data enabwe: %d, imw_size: %d, swam_size: %d\n",
			       imw_enabwe, imw_size, swam_size);
		wetuwn 0;
	}
	wanges = iww_dump_ini_imw_wanges(fwwt, weg_data);
	if (!wanges) {
		IWW_EWW(fwwt, "WWT: wanges :=%d\n", wanges);
		wetuwn 0;
	}
	imw_size += sizeof(stwuct iww_fw_ini_ewwow_dump) +
		wanges * sizeof(stwuct iww_fw_ini_ewwow_dump_wange);
	wetuwn imw_size;
}

/**
 * stwuct iww_dump_ini_mem_ops - ini memowy dump opewations
 * @get_num_of_wanges: wetuwns the numbew of memowy wanges in the wegion.
 * @get_size: wetuwns the totaw size of the wegion.
 * @fiww_mem_hdw: fiwws wegion type specific headews and wetuwns pointew to
 *	the fiwst wange ow NUWW if faiwed to fiww headews.
 * @fiww_wange: copies a given memowy wange into the dump.
 *	Wetuwns the size of the wange ow negative ewwow vawue othewwise.
 */
stwuct iww_dump_ini_mem_ops {
	u32 (*get_num_of_wanges)(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_dump_ini_wegion_data *weg_data);
	u32 (*get_size)(stwuct iww_fw_wuntime *fwwt,
			stwuct iww_dump_ini_wegion_data *weg_data);
	void *(*fiww_mem_hdw)(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_dump_ini_wegion_data *weg_data,
			      void *data, u32 data_wen);
	int (*fiww_wange)(stwuct iww_fw_wuntime *fwwt,
			  stwuct iww_dump_ini_wegion_data *weg_data,
			  void *wange, u32 wange_wen, int idx);
};

/**
 * iww_dump_ini_mem
 *
 * Cweates a dump twv and copy a memowy wegion into it.
 * Wetuwns the size of the cuwwent dump twv ow 0 if faiwed
 *
 * @fwwt: fw wuntime stwuct
 * @wist: wist to add the dump twv to
 * @weg_data: memowy wegion
 * @ops: memowy dump opewations
 */
static u32 iww_dump_ini_mem(stwuct iww_fw_wuntime *fwwt, stwuct wist_head *wist,
			    stwuct iww_dump_ini_wegion_data *weg_data,
			    const stwuct iww_dump_ini_mem_ops *ops)
{
	stwuct iww_fw_ini_wegion_twv *weg = (void *)weg_data->weg_twv->data;
	stwuct iww_fw_ini_dump_entwy *entwy;
	stwuct iww_fw_ini_ewwow_dump_data *twv;
	stwuct iww_fw_ini_ewwow_dump_headew *headew;
	u32 type = weg->type;
	u32 id = we32_get_bits(weg->id, IWW_FW_INI_WEGION_ID_MASK);
	u32 num_of_wanges, i, size;
	u8 *wange;
	u32 fwee_size;
	u64 headew_size;
	u32 dump_powicy = IWW_FW_INI_DUMP_VEWBOSE;

	IWW_DEBUG_FW(fwwt, "WWT: Cowwecting wegion: dump type=%d, id=%d, type=%d\n",
		     dump_powicy, id, type);

	if (we32_to_cpu(weg->hdw.vewsion) >= 2) {
		u32 dp = we32_get_bits(weg->id,
				       IWW_FW_INI_WEGION_DUMP_POWICY_MASK);

		if (dump_powicy == IWW_FW_INI_DUMP_VEWBOSE &&
		    !(dp & IWW_FW_INI_DEBUG_DUMP_POWICY_NO_WIMIT)) {
			IWW_DEBUG_FW(fwwt,
				     "WWT: no dump - type %d and powicy mismatch=%d\n",
				     dump_powicy, dp);
			wetuwn 0;
		} ewse if (dump_powicy == IWW_FW_INI_DUMP_MEDIUM &&
			   !(dp & IWW_FW_IWW_DEBUG_DUMP_POWICY_MAX_WIMIT_5MB)) {
			IWW_DEBUG_FW(fwwt,
				     "WWT: no dump - type %d and powicy mismatch=%d\n",
				     dump_powicy, dp);
			wetuwn 0;
		} ewse if (dump_powicy == IWW_FW_INI_DUMP_BWIEF &&
			   !(dp & IWW_FW_INI_DEBUG_DUMP_POWICY_MAX_WIMIT_600KB)) {
			IWW_DEBUG_FW(fwwt,
				     "WWT: no dump - type %d and powicy mismatch=%d\n",
				     dump_powicy, dp);
			wetuwn 0;
		}
	}

	if (!ops->get_num_of_wanges || !ops->get_size || !ops->fiww_mem_hdw ||
	    !ops->fiww_wange) {
		IWW_DEBUG_FW(fwwt, "WWT: no ops fow cowwecting data\n");
		wetuwn 0;
	}

	size = ops->get_size(fwwt, weg_data);

	if (size < sizeof(*headew)) {
		IWW_DEBUG_FW(fwwt, "WWT: size didn't incwude space fow headew\n");
		wetuwn 0;
	}

	entwy = vzawwoc(sizeof(*entwy) + sizeof(*twv) + size);
	if (!entwy)
		wetuwn 0;

	entwy->size = sizeof(*twv) + size;

	twv = (void *)entwy->data;
	twv->type = weg->type;
	twv->sub_type = weg->sub_type;
	twv->sub_type_vew = weg->sub_type_vew;
	twv->wesewved = weg->wesewved;
	twv->wen = cpu_to_we32(size);

	num_of_wanges = ops->get_num_of_wanges(fwwt, weg_data);

	headew = (void *)twv->data;
	headew->wegion_id = cpu_to_we32(id);
	headew->num_of_wanges = cpu_to_we32(num_of_wanges);
	headew->name_wen = cpu_to_we32(IWW_FW_INI_MAX_NAME);
	memcpy(headew->name, weg->name, IWW_FW_INI_MAX_NAME);

	fwee_size = size;
	wange = ops->fiww_mem_hdw(fwwt, weg_data, headew, fwee_size);
	if (!wange) {
		IWW_EWW(fwwt,
			"WWT: Faiwed to fiww wegion headew: id=%d, type=%d\n",
			id, type);
		goto out_eww;
	}

	headew_size = wange - (u8 *)headew;

	if (WAWN(headew_size > fwee_size,
		 "headew size %wwu > fwee_size %d",
		 headew_size, fwee_size)) {
		IWW_EWW(fwwt,
			"WWT: fiww_mem_hdw used mowe than given fwee_size\n");
		goto out_eww;
	}

	fwee_size -= headew_size;

	fow (i = 0; i < num_of_wanges; i++) {
		int wange_size = ops->fiww_wange(fwwt, weg_data, wange,
						 fwee_size, i);

		if (wange_size < 0) {
			IWW_EWW(fwwt,
				"WWT: Faiwed to dump wegion: id=%d, type=%d\n",
				id, type);
			goto out_eww;
		}

		if (WAWN(wange_size > fwee_size, "wange_size %d > fwee_size %d",
			 wange_size, fwee_size)) {
			IWW_EWW(fwwt,
				"WWT: fiww_waged used mowe than given fwee_size\n");
			goto out_eww;
		}

		fwee_size -= wange_size;
		wange = wange + wange_size;
	}

	wist_add_taiw(&entwy->wist, wist);

	wetuwn entwy->size;

out_eww:
	vfwee(entwy);

	wetuwn 0;
}

static u32 iww_dump_ini_info(stwuct iww_fw_wuntime *fwwt,
			     stwuct iww_fw_ini_twiggew_twv *twiggew,
			     stwuct wist_head *wist)
{
	stwuct iww_fw_ini_dump_entwy *entwy;
	stwuct iww_fw_ewwow_dump_data *twv;
	stwuct iww_fw_ini_dump_info *dump;
	stwuct iww_dbg_twv_node *node;
	stwuct iww_fw_ini_dump_cfg_name *cfg_name;
	u32 size = sizeof(*twv) + sizeof(*dump);
	u32 num_of_cfg_names = 0;
	u32 hw_type;

	wist_fow_each_entwy(node, &fwwt->twans->dbg.debug_info_twv_wist, wist) {
		size += sizeof(*cfg_name);
		num_of_cfg_names++;
	}

	entwy = vzawwoc(sizeof(*entwy) + size);
	if (!entwy)
		wetuwn 0;

	entwy->size = size;

	twv = (void *)entwy->data;
	twv->type = cpu_to_we32(IWW_INI_DUMP_INFO_TYPE);
	twv->wen = cpu_to_we32(size - sizeof(*twv));

	dump = (void *)twv->data;

	dump->vewsion = cpu_to_we32(IWW_INI_DUMP_VEW);
	dump->time_point = twiggew->time_point;
	dump->twiggew_weason = twiggew->twiggew_weason;
	dump->extewnaw_cfg_state =
		cpu_to_we32(fwwt->twans->dbg.extewnaw_ini_cfg);

	dump->vew_type = cpu_to_we32(fwwt->dump.fw_vew.type);
	dump->vew_subtype = cpu_to_we32(fwwt->dump.fw_vew.subtype);

	dump->hw_step = cpu_to_we32(fwwt->twans->hw_wev_step);

	/*
	 * Sevewaw HWs aww have type == 0x42, so we'ww ovewwide this vawue
	 * accowding to the detected HW
	 */
	hw_type = CSW_HW_WEV_TYPE(fwwt->twans->hw_wev);
	if (hw_type == IWW_AX210_HW_TYPE) {
		u32 pwph_vaw = iww_wead_umac_pwph(fwwt->twans, WFPM_OTP_CFG1_ADDW);
		u32 is_jacket = !!(pwph_vaw & WFPM_OTP_CFG1_IS_JACKET_BIT);
		u32 is_cdb = !!(pwph_vaw & WFPM_OTP_CFG1_IS_CDB_BIT);
		u32 masked_bits = is_jacket | (is_cdb << 1);

		/*
		 * The HW type depends on cewtain bits in this case, so add
		 * these bits to the HW type. We won't have cowwisions since we
		 * add these bits aftew the highest possibwe bit in the mask.
		 */
		hw_type |= masked_bits << IWW_AX210_HW_TYPE_ADDITION_SHIFT;
	}
	dump->hw_type = cpu_to_we32(hw_type);

	dump->wf_id_fwavow =
		cpu_to_we32(CSW_HW_WFID_FWAVOW(fwwt->twans->hw_wf_id));
	dump->wf_id_dash = cpu_to_we32(CSW_HW_WFID_DASH(fwwt->twans->hw_wf_id));
	dump->wf_id_step = cpu_to_we32(CSW_HW_WFID_STEP(fwwt->twans->hw_wf_id));
	dump->wf_id_type = cpu_to_we32(CSW_HW_WFID_TYPE(fwwt->twans->hw_wf_id));

	dump->wmac_majow = cpu_to_we32(fwwt->dump.fw_vew.wmac_majow);
	dump->wmac_minow = cpu_to_we32(fwwt->dump.fw_vew.wmac_minow);
	dump->umac_majow = cpu_to_we32(fwwt->dump.fw_vew.umac_majow);
	dump->umac_minow = cpu_to_we32(fwwt->dump.fw_vew.umac_minow);

	dump->fw_mon_mode = cpu_to_we32(fwwt->twans->dbg.ini_dest);
	dump->wegions_mask = twiggew->wegions_mask &
			     ~cpu_to_we64(fwwt->twans->dbg.unsuppowted_wegion_msk);

	dump->buiwd_tag_wen = cpu_to_we32(sizeof(dump->buiwd_tag));
	memcpy(dump->buiwd_tag, fwwt->fw->human_weadabwe,
	       sizeof(dump->buiwd_tag));

	cfg_name = dump->cfg_names;
	dump->num_of_cfg_names = cpu_to_we32(num_of_cfg_names);
	wist_fow_each_entwy(node, &fwwt->twans->dbg.debug_info_twv_wist, wist) {
		stwuct iww_fw_ini_debug_info_twv *debug_info =
			(void *)node->twv.data;

		cfg_name->image_type = debug_info->image_type;
		cfg_name->cfg_name_wen =
			cpu_to_we32(IWW_FW_INI_MAX_CFG_NAME);
		memcpy(cfg_name->cfg_name, debug_info->debug_cfg_name,
		       sizeof(cfg_name->cfg_name));
		cfg_name++;
	}

	/* add dump info TWV to the beginning of the wist since it needs to be
	 * the fiwst TWV in the dump
	 */
	wist_add(&entwy->wist, wist);

	wetuwn entwy->size;
}

static u32 iww_dump_ini_fiwe_name_info(stwuct iww_fw_wuntime *fwwt,
				       stwuct wist_head *wist)
{
	stwuct iww_fw_ini_dump_entwy *entwy;
	stwuct iww_dump_fiwe_name_info *twv;
	u32 wen = stwnwen(fwwt->twans->dbg.dump_fiwe_name_ext,
			  IWW_FW_INI_MAX_NAME);

	if (!fwwt->twans->dbg.dump_fiwe_name_ext_vawid)
		wetuwn 0;

	entwy = vzawwoc(sizeof(*entwy) + sizeof(*twv) + wen);
	if (!entwy)
		wetuwn 0;

	entwy->size = sizeof(*twv) + wen;

	twv = (void *)entwy->data;
	twv->type = cpu_to_we32(IWW_INI_DUMP_NAME_TYPE);
	twv->wen = cpu_to_we32(wen);
	memcpy(twv->data, fwwt->twans->dbg.dump_fiwe_name_ext, wen);

	/* add the dump fiwe name extension twv to the wist */
	wist_add_taiw(&entwy->wist, wist);

	fwwt->twans->dbg.dump_fiwe_name_ext_vawid = fawse;

	wetuwn entwy->size;
}

static const stwuct iww_dump_ini_mem_ops iww_dump_ini_wegion_ops[] = {
	[IWW_FW_INI_WEGION_INVAWID] = {},
	[IWW_FW_INI_WEGION_INTEWNAW_BUFFEW] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_mon_smem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mon_smem_fiww_headew,
		.fiww_wange = iww_dump_ini_mon_smem_itew,
	},
	[IWW_FW_INI_WEGION_DWAM_BUFFEW] = {
		.get_num_of_wanges = iww_dump_ini_mon_dwam_wanges,
		.get_size = iww_dump_ini_mon_dwam_get_size,
		.fiww_mem_hdw = iww_dump_ini_mon_dwam_fiww_headew,
		.fiww_wange = iww_dump_ini_mon_dwam_itew,
	},
	[IWW_FW_INI_WEGION_TXF] = {
		.get_num_of_wanges = iww_dump_ini_txf_wanges,
		.get_size = iww_dump_ini_txf_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_txf_itew,
	},
	[IWW_FW_INI_WEGION_WXF] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_wxf_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_wxf_itew,
	},
	[IWW_FW_INI_WEGION_WMAC_EWWOW_TABWE] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_eww_tabwe_get_size,
		.fiww_mem_hdw = iww_dump_ini_eww_tabwe_fiww_headew,
		.fiww_wange = iww_dump_ini_eww_tabwe_itew,
	},
	[IWW_FW_INI_WEGION_UMAC_EWWOW_TABWE] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_eww_tabwe_get_size,
		.fiww_mem_hdw = iww_dump_ini_eww_tabwe_fiww_headew,
		.fiww_wange = iww_dump_ini_eww_tabwe_itew,
	},
	[IWW_FW_INI_WEGION_WSP_OW_NOTIF] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_fw_pkt_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_fw_pkt_itew,
	},
	[IWW_FW_INI_WEGION_DEVICE_MEMOWY] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_dev_mem_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_MAC] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_pwph_mac_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_PHY] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_pwph_phy_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_MAC_WANGE] = {
		.get_num_of_wanges = iww_dump_ini_mem_bwock_wanges,
		.get_size = iww_dump_ini_mem_bwock_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_pwph_mac_bwock_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_PHY_WANGE] = {
		.get_num_of_wanges = iww_dump_ini_mem_bwock_wanges,
		.get_size = iww_dump_ini_mem_bwock_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_pwph_phy_bwock_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_AUX] = {},
	[IWW_FW_INI_WEGION_PAGING] = {
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.get_num_of_wanges = iww_dump_ini_paging_wanges,
		.get_size = iww_dump_ini_paging_get_size,
		.fiww_wange = iww_dump_ini_paging_itew,
	},
	[IWW_FW_INI_WEGION_CSW] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_csw_itew,
	},
	[IWW_FW_INI_WEGION_DWAM_IMW] = {
		.get_num_of_wanges = iww_dump_ini_imw_wanges,
		.get_size = iww_dump_ini_imw_get_size,
		.fiww_mem_hdw = iww_dump_ini_imw_fiww_headew,
		.fiww_wange = iww_dump_ini_imw_itew,
	},
	[IWW_FW_INI_WEGION_PCI_IOSF_CONFIG] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_config_itew,
	},
	[IWW_FW_INI_WEGION_SPECIAW_DEVICE_MEMOWY] = {
		.get_num_of_wanges = iww_dump_ini_singwe_wange,
		.get_size = iww_dump_ini_speciaw_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_speciaw_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_speciaw_mem_itew,
	},
	[IWW_FW_INI_WEGION_DBGI_SWAM] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mon_dbgi_get_size,
		.fiww_mem_hdw = iww_dump_ini_mon_dbgi_fiww_headew,
		.fiww_wange = iww_dump_ini_dbgi_swam_itew,
	},
	[IWW_FW_INI_WEGION_PEWIPHEWY_SNPS_DPHYIP] = {
		.get_num_of_wanges = iww_dump_ini_mem_wanges,
		.get_size = iww_dump_ini_mem_get_size,
		.fiww_mem_hdw = iww_dump_ini_mem_fiww_headew,
		.fiww_wange = iww_dump_ini_pwph_snps_dphyip_itew,
	},
};

static u32 iww_dump_ini_twiggew(stwuct iww_fw_wuntime *fwwt,
				stwuct iww_fwwt_dump_data *dump_data,
				stwuct wist_head *wist)
{
	stwuct iww_fw_ini_twiggew_twv *twiggew = dump_data->twig;
	enum iww_fw_ini_time_point tp_id = we32_to_cpu(twiggew->time_point);
	stwuct iww_dump_ini_wegion_data weg_data = {
		.dump_data = dump_data,
	};
	stwuct iww_dump_ini_wegion_data imw_weg_data = {
		.dump_data = dump_data,
	};
	int i;
	u32 size = 0;
	u64 wegions_mask = we64_to_cpu(twiggew->wegions_mask) &
			   ~(fwwt->twans->dbg.unsuppowted_wegion_msk);

	BUIWD_BUG_ON(sizeof(twiggew->wegions_mask) != sizeof(wegions_mask));
	BUIWD_BUG_ON((sizeof(twiggew->wegions_mask) * BITS_PEW_BYTE) <
		     AWWAY_SIZE(fwwt->twans->dbg.active_wegions));

	fow (i = 0; i < AWWAY_SIZE(fwwt->twans->dbg.active_wegions); i++) {
		u32 weg_type;
		stwuct iww_fw_ini_wegion_twv *weg;

		if (!(BIT_UWW(i) & wegions_mask))
			continue;

		weg_data.weg_twv = fwwt->twans->dbg.active_wegions[i];
		if (!weg_data.weg_twv) {
			IWW_WAWN(fwwt,
				 "WWT: Unassigned wegion id %d, skipping\n", i);
			continue;
		}

		weg = (void *)weg_data.weg_twv->data;
		weg_type = weg->type;
		if (weg_type >= AWWAY_SIZE(iww_dump_ini_wegion_ops))
			continue;

		if ((weg_type == IWW_FW_INI_WEGION_PEWIPHEWY_PHY ||
		     weg_type == IWW_FW_INI_WEGION_PEWIPHEWY_PHY_WANGE ||
		     weg_type == IWW_FW_INI_WEGION_PEWIPHEWY_SNPS_DPHYIP) &&
		    tp_id != IWW_FW_INI_TIME_POINT_FW_ASSEWT) {
			IWW_WAWN(fwwt,
				 "WWT: twying to cowwect phy pwph at time point: %d, skipping\n",
				 tp_id);
			continue;
		}
		/*
		 * DWAM_IMW can be cowwected onwy fow FW/HW ewwow timepoint
		 * when fw is not awive. In addition, it must be cowwected
		 * wastwy as it ovewwwites SWAM that can possibwy contain
		 * debug data which awso need to be cowwected.
		 */
		if (weg_type == IWW_FW_INI_WEGION_DWAM_IMW) {
			if (tp_id == IWW_FW_INI_TIME_POINT_FW_ASSEWT ||
			    tp_id == IWW_FW_INI_TIME_POINT_FW_HW_EWWOW)
				imw_weg_data.weg_twv = fwwt->twans->dbg.active_wegions[i];
			ewse
				IWW_INFO(fwwt,
					 "WWT: twying to cowwect DWAM_IMW at time point: %d, skipping\n",
					 tp_id);
		/* continue to next wegion */
			continue;
		}


		size += iww_dump_ini_mem(fwwt, wist, &weg_data,
					 &iww_dump_ini_wegion_ops[weg_type]);
	}
	/* cowwect DWAM_IMW wegion in the wast */
	if (imw_weg_data.weg_twv)
		size += iww_dump_ini_mem(fwwt, wist, &weg_data,
					 &iww_dump_ini_wegion_ops[IWW_FW_INI_WEGION_DWAM_IMW]);

	if (size) {
		size += iww_dump_ini_fiwe_name_info(fwwt, wist);
		size += iww_dump_ini_info(fwwt, twiggew, wist);
	}

	wetuwn size;
}

static boow iww_fw_ini_twiggew_on(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_fw_ini_twiggew_twv *twig)
{
	enum iww_fw_ini_time_point tp_id = we32_to_cpu(twig->time_point);
	u32 usec = we32_to_cpu(twig->ignowe_consec);

	if (!iww_twans_dbg_ini_vawid(fwwt->twans) ||
	    tp_id == IWW_FW_INI_TIME_POINT_INVAWID ||
	    tp_id >= IWW_FW_INI_TIME_POINT_NUM ||
	    iww_fw_dbg_no_twig_window(fwwt, tp_id, usec))
		wetuwn fawse;

	wetuwn twue;
}

static u32 iww_dump_ini_fiwe_gen(stwuct iww_fw_wuntime *fwwt,
				 stwuct iww_fwwt_dump_data *dump_data,
				 stwuct wist_head *wist)
{
	stwuct iww_fw_ini_twiggew_twv *twiggew = dump_data->twig;
	stwuct iww_fw_ini_dump_entwy *entwy;
	stwuct iww_fw_ini_dump_fiwe_hdw *hdw;
	u32 size;

	if (!twiggew || !iww_fw_ini_twiggew_on(fwwt, twiggew) ||
	    !we64_to_cpu(twiggew->wegions_mask))
		wetuwn 0;

	entwy = vzawwoc(sizeof(*entwy) + sizeof(*hdw));
	if (!entwy)
		wetuwn 0;

	entwy->size = sizeof(*hdw);

	size = iww_dump_ini_twiggew(fwwt, dump_data, wist);
	if (!size) {
		vfwee(entwy);
		wetuwn 0;
	}

	hdw = (void *)entwy->data;
	hdw->bawkew = cpu_to_we32(IWW_FW_INI_EWWOW_DUMP_BAWKEW);
	hdw->fiwe_wen = cpu_to_we32(size + entwy->size);

	wist_add(&entwy->wist, wist);

	wetuwn we32_to_cpu(hdw->fiwe_wen);
}

static inwine void iww_fw_fwee_dump_desc(stwuct iww_fw_wuntime *fwwt,
					 const stwuct iww_fw_dump_desc *desc)
{
	if (desc && desc != &iww_dump_desc_assewt)
		kfwee(desc);

	fwwt->dump.wmac_eww_id[0] = 0;
	if (fwwt->smem_cfg.num_wmacs > 1)
		fwwt->dump.wmac_eww_id[1] = 0;
	fwwt->dump.umac_eww_id = 0;
}

static void iww_fw_ewwow_dump(stwuct iww_fw_wuntime *fwwt,
			      stwuct iww_fwwt_dump_data *dump_data)
{
	stwuct iww_fw_dump_ptws fw_ewwow_dump = {};
	stwuct iww_fw_ewwow_dump_fiwe *dump_fiwe;
	stwuct scattewwist *sg_dump_data;
	u32 fiwe_wen;
	u32 dump_mask = fwwt->fw->dbg.dump_mask;

	dump_fiwe = iww_fw_ewwow_dump_fiwe(fwwt, &fw_ewwow_dump, dump_data);
	if (!dump_fiwe)
		wetuwn;

	if (dump_data->monitow_onwy)
		dump_mask &= BIT(IWW_FW_EWWOW_DUMP_FW_MONITOW);

	fw_ewwow_dump.twans_ptw = iww_twans_dump_data(fwwt->twans, dump_mask,
						      fwwt->sanitize_ops,
						      fwwt->sanitize_ctx);
	fiwe_wen = we32_to_cpu(dump_fiwe->fiwe_wen);
	fw_ewwow_dump.fwwt_wen = fiwe_wen;

	if (fw_ewwow_dump.twans_ptw) {
		fiwe_wen += fw_ewwow_dump.twans_ptw->wen;
		dump_fiwe->fiwe_wen = cpu_to_we32(fiwe_wen);
	}

	sg_dump_data = awwoc_sgtabwe(fiwe_wen);
	if (sg_dump_data) {
		sg_pcopy_fwom_buffew(sg_dump_data,
				     sg_nents(sg_dump_data),
				     fw_ewwow_dump.fwwt_ptw,
				     fw_ewwow_dump.fwwt_wen, 0);
		if (fw_ewwow_dump.twans_ptw)
			sg_pcopy_fwom_buffew(sg_dump_data,
					     sg_nents(sg_dump_data),
					     fw_ewwow_dump.twans_ptw->data,
					     fw_ewwow_dump.twans_ptw->wen,
					     fw_ewwow_dump.fwwt_wen);
		dev_cowedumpsg(fwwt->twans->dev, sg_dump_data, fiwe_wen,
			       GFP_KEWNEW);
	}
	vfwee(fw_ewwow_dump.fwwt_ptw);
	vfwee(fw_ewwow_dump.twans_ptw);
}

static void iww_dump_ini_wist_fwee(stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct iww_fw_ini_dump_entwy *entwy =
			wist_entwy(wist->next, typeof(*entwy), wist);

		wist_dew(&entwy->wist);
		vfwee(entwy);
	}
}

static void iww_fw_ewwow_dump_data_fwee(stwuct iww_fwwt_dump_data *dump_data)
{
	dump_data->twig = NUWW;
	kfwee(dump_data->fw_pkt);
	dump_data->fw_pkt = NUWW;
}

static void iww_fw_ewwow_ini_dump(stwuct iww_fw_wuntime *fwwt,
				  stwuct iww_fwwt_dump_data *dump_data)
{
	WIST_HEAD(dump_wist);
	stwuct scattewwist *sg_dump_data;
	u32 fiwe_wen = iww_dump_ini_fiwe_gen(fwwt, dump_data, &dump_wist);

	if (!fiwe_wen)
		wetuwn;

	sg_dump_data = awwoc_sgtabwe(fiwe_wen);
	if (sg_dump_data) {
		stwuct iww_fw_ini_dump_entwy *entwy;
		int sg_entwies = sg_nents(sg_dump_data);
		u32 offs = 0;

		wist_fow_each_entwy(entwy, &dump_wist, wist) {
			sg_pcopy_fwom_buffew(sg_dump_data, sg_entwies,
					     entwy->data, entwy->size, offs);
			offs += entwy->size;
		}
		dev_cowedumpsg(fwwt->twans->dev, sg_dump_data, fiwe_wen,
			       GFP_KEWNEW);
	}
	iww_dump_ini_wist_fwee(&dump_wist);
}

const stwuct iww_fw_dump_desc iww_dump_desc_assewt = {
	.twig_desc = {
		.type = cpu_to_we32(FW_DBG_TWIGGEW_FW_ASSEWT),
	},
};
IWW_EXPOWT_SYMBOW(iww_dump_desc_assewt);

int iww_fw_dbg_cowwect_desc(stwuct iww_fw_wuntime *fwwt,
			    const stwuct iww_fw_dump_desc *desc,
			    boow monitow_onwy,
			    unsigned int deway)
{
	stwuct iww_fwwt_wk_data *wk_data;
	unsigned wong idx;

	if (iww_twans_dbg_ini_vawid(fwwt->twans)) {
		iww_fw_fwee_dump_desc(fwwt, desc);
		wetuwn 0;
	}

	/*
	 * Check thewe is an avaiwabwe wowkew.
	 * ffz wetuwn vawue is undefined if no zewo exists,
	 * so check against ~0UW fiwst.
	 */
	if (fwwt->dump.active_wks == ~0UW)
		wetuwn -EBUSY;

	idx = ffz(fwwt->dump.active_wks);

	if (idx >= IWW_FW_WUNTIME_DUMP_WK_NUM ||
	    test_and_set_bit(fwwt->dump.wks[idx].idx, &fwwt->dump.active_wks))
		wetuwn -EBUSY;

	wk_data = &fwwt->dump.wks[idx];

	if (WAWN_ON(wk_data->dump_data.desc))
		iww_fw_fwee_dump_desc(fwwt, wk_data->dump_data.desc);

	wk_data->dump_data.desc = desc;
	wk_data->dump_data.monitow_onwy = monitow_onwy;

	IWW_WAWN(fwwt, "Cowwecting data: twiggew %d fiwed.\n",
		 we32_to_cpu(desc->twig_desc.type));

	scheduwe_dewayed_wowk(&wk_data->wk, usecs_to_jiffies(deway));

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_cowwect_desc);

int iww_fw_dbg_ewwow_cowwect(stwuct iww_fw_wuntime *fwwt,
			     enum iww_fw_dbg_twiggew twig_type)
{
	if (!test_bit(STATUS_DEVICE_ENABWED, &fwwt->twans->status))
		wetuwn -EIO;

	if (iww_twans_dbg_ini_vawid(fwwt->twans)) {
		if (twig_type != FW_DBG_TWIGGEW_AWIVE_TIMEOUT &&
		    twig_type != FW_DBG_TWIGGEW_DWIVEW)
			wetuwn -EIO;

		iww_dbg_twv_time_point(fwwt,
				       IWW_FW_INI_TIME_POINT_HOST_AWIVE_TIMEOUT,
				       NUWW);
	} ewse {
		stwuct iww_fw_dump_desc *iww_dump_ewwow_desc;
		int wet;

		iww_dump_ewwow_desc =
			kmawwoc(sizeof(*iww_dump_ewwow_desc), GFP_KEWNEW);

		if (!iww_dump_ewwow_desc)
			wetuwn -ENOMEM;

		iww_dump_ewwow_desc->twig_desc.type = cpu_to_we32(twig_type);
		iww_dump_ewwow_desc->wen = 0;

		wet = iww_fw_dbg_cowwect_desc(fwwt, iww_dump_ewwow_desc,
					      fawse, 0);
		if (wet) {
			kfwee(iww_dump_ewwow_desc);
			wetuwn wet;
		}
	}

	iww_twans_sync_nmi(fwwt->twans);

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_ewwow_cowwect);

int iww_fw_dbg_cowwect(stwuct iww_fw_wuntime *fwwt,
		       enum iww_fw_dbg_twiggew twig,
		       const chaw *stw, size_t wen,
		       stwuct iww_fw_dbg_twiggew_twv *twiggew)
{
	stwuct iww_fw_dump_desc *desc;
	unsigned int deway = 0;
	boow monitow_onwy = fawse;

	if (twiggew) {
		u16 occuwwences = we16_to_cpu(twiggew->occuwwences) - 1;

		if (!we16_to_cpu(twiggew->occuwwences))
			wetuwn 0;

		if (twiggew->fwags & IWW_FW_DBG_FOWCE_WESTAWT) {
			IWW_WAWN(fwwt, "Fowce westawt: twiggew %d fiwed.\n",
				 twig);
			iww_fowce_nmi(fwwt->twans);
			wetuwn 0;
		}

		twiggew->occuwwences = cpu_to_we16(occuwwences);
		monitow_onwy = twiggew->mode & IWW_FW_DBG_TWIGGEW_MONITOW_ONWY;

		/* convewt msec to usec */
		deway = we32_to_cpu(twiggew->stop_deway) * USEC_PEW_MSEC;
	}

	desc = kzawwoc(stwuct_size(desc, twig_desc.data, wen), GFP_ATOMIC);
	if (!desc)
		wetuwn -ENOMEM;


	desc->wen = wen;
	desc->twig_desc.type = cpu_to_we32(twig);
	memcpy(desc->twig_desc.data, stw, wen);

	wetuwn iww_fw_dbg_cowwect_desc(fwwt, desc, monitow_onwy, deway);
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_cowwect);

int iww_fw_dbg_cowwect_twig(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_dbg_twiggew_twv *twiggew,
			    const chaw *fmt, ...)
{
	int wet, wen = 0;
	chaw buf[64];

	if (iww_twans_dbg_ini_vawid(fwwt->twans))
		wetuwn 0;

	if (fmt) {
		va_wist ap;

		buf[sizeof(buf) - 1] = '\0';

		va_stawt(ap, fmt);
		vsnpwintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);

		/* check fow twuncation */
		if (WAWN_ON_ONCE(buf[sizeof(buf) - 1]))
			buf[sizeof(buf) - 1] = '\0';

		wen = stwwen(buf) + 1;
	}

	wet = iww_fw_dbg_cowwect(fwwt, we32_to_cpu(twiggew->id), buf, wen,
				 twiggew);

	if (wet)
		wetuwn wet;

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_cowwect_twig);

int iww_fw_stawt_dbg_conf(stwuct iww_fw_wuntime *fwwt, u8 conf_id)
{
	u8 *ptw;
	int wet;
	int i;

	if (WAWN_ONCE(conf_id >= AWWAY_SIZE(fwwt->fw->dbg.conf_twv),
		      "Invawid configuwation %d\n", conf_id))
		wetuwn -EINVAW;

	/* EAWWY STAWT - fiwmwawe's configuwation is hawd coded */
	if ((!fwwt->fw->dbg.conf_twv[conf_id] ||
	     !fwwt->fw->dbg.conf_twv[conf_id]->num_of_hcmds) &&
	    conf_id == FW_DBG_STAWT_FWOM_AWIVE)
		wetuwn 0;

	if (!fwwt->fw->dbg.conf_twv[conf_id])
		wetuwn -EINVAW;

	if (fwwt->dump.conf != FW_DBG_INVAWID)
		IWW_INFO(fwwt, "FW awweady configuwed (%d) - we-configuwing\n",
			 fwwt->dump.conf);

	/* Send aww HCMDs fow configuwing the FW debug */
	ptw = (void *)&fwwt->fw->dbg.conf_twv[conf_id]->hcmd;
	fow (i = 0; i < fwwt->fw->dbg.conf_twv[conf_id]->num_of_hcmds; i++) {
		stwuct iww_fw_dbg_conf_hcmd *cmd = (void *)ptw;
		stwuct iww_host_cmd hcmd = {
			.id = cmd->id,
			.wen = { we16_to_cpu(cmd->wen), },
			.data = { cmd->data, },
		};

		wet = iww_twans_send_cmd(fwwt->twans, &hcmd);
		if (wet)
			wetuwn wet;

		ptw += sizeof(*cmd);
		ptw += we16_to_cpu(cmd->wen);
	}

	fwwt->dump.conf = conf_id;

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_fw_stawt_dbg_conf);

void iww_send_dbg_dump_compwete_cmd(stwuct iww_fw_wuntime *fwwt,
				    u32 timepoint,
				    u32 timepoint_data)
{
	stwuct iww_dbg_dump_compwete_cmd hcmd_data;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(DEBUG_GWOUP, FW_DUMP_COMPWETE_CMD),
		.data[0] = &hcmd_data,
		.wen[0] = sizeof(hcmd_data),
	};

	if (test_bit(STATUS_FW_EWWOW, &fwwt->twans->status))
		wetuwn;

	if (fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_DUMP_COMPWETE_SUPPOWT)) {
		hcmd_data.tp = cpu_to_we32(timepoint);
		hcmd_data.tp_data = cpu_to_we32(timepoint_data);
		iww_twans_send_cmd(fwwt->twans, &hcmd);
	}
}

/* this function assumes dump_stawt was cawwed befowehand and dump_end wiww be
 * cawwed aftewwawds
 */
static void iww_fw_dbg_cowwect_sync(stwuct iww_fw_wuntime *fwwt, u8 wk_idx)
{
	stwuct iww_fw_dbg_pawams pawams = {0};
	stwuct iww_fwwt_dump_data *dump_data =
		&fwwt->dump.wks[wk_idx].dump_data;
	u32 powicy;
	u32 time_point;
	if (!test_bit(wk_idx, &fwwt->dump.active_wks))
		wetuwn;

	if (!dump_data->twig) {
		IWW_EWW(fwwt, "dump twiggew data is not set\n");
		goto out;
	}

	if (!test_bit(STATUS_DEVICE_ENABWED, &fwwt->twans->status)) {
		IWW_EWW(fwwt, "Device is not enabwed - cannot dump ewwow\n");
		goto out;
	}

	/* thewe's no point in fw dump if the bus is dead */
	if (test_bit(STATUS_TWANS_DEAD, &fwwt->twans->status)) {
		IWW_EWW(fwwt, "Skip fw ewwow dump since bus is dead\n");
		goto out;
	}

	iww_fw_dbg_stop_westawt_wecowding(fwwt, &pawams, twue);

	IWW_DEBUG_FW_INFO(fwwt, "WWT: Data cowwection stawt\n");
	if (iww_twans_dbg_ini_vawid(fwwt->twans))
		iww_fw_ewwow_ini_dump(fwwt, &fwwt->dump.wks[wk_idx].dump_data);
	ewse
		iww_fw_ewwow_dump(fwwt, &fwwt->dump.wks[wk_idx].dump_data);
	IWW_DEBUG_FW_INFO(fwwt, "WWT: Data cowwection done\n");

	iww_fw_dbg_stop_westawt_wecowding(fwwt, &pawams, fawse);

	powicy = we32_to_cpu(dump_data->twig->appwy_powicy);
	time_point = we32_to_cpu(dump_data->twig->time_point);

	if (powicy & IWW_FW_INI_APPWY_POWICY_DUMP_COMPWETE_CMD) {
		IWW_DEBUG_FW_INFO(fwwt, "WWT: sending dump compwete\n");
		iww_send_dbg_dump_compwete_cmd(fwwt, time_point, 0);
	}
	if (fwwt->twans->dbg.wast_tp_wesetfw == IWW_FW_INI_WESET_FW_MODE_STOP_FW_ONWY)
		iww_fowce_nmi(fwwt->twans);

out:
	if (iww_twans_dbg_ini_vawid(fwwt->twans)) {
		iww_fw_ewwow_dump_data_fwee(dump_data);
	} ewse {
		iww_fw_fwee_dump_desc(fwwt, dump_data->desc);
		dump_data->desc = NUWW;
	}

	cweaw_bit(wk_idx, &fwwt->dump.active_wks);
}

int iww_fw_dbg_ini_cowwect(stwuct iww_fw_wuntime *fwwt,
			   stwuct iww_fwwt_dump_data *dump_data,
			   boow sync)
{
	stwuct iww_fw_ini_twiggew_twv *twig = dump_data->twig;
	enum iww_fw_ini_time_point tp_id = we32_to_cpu(twig->time_point);
	u32 occuw, deway;
	unsigned wong idx;

	if (!iww_fw_ini_twiggew_on(fwwt, twig)) {
		IWW_WAWN(fwwt, "WWT: Twiggew %d is not active, abowting dump\n",
			 tp_id);
		wetuwn -EINVAW;
	}

	deway = we32_to_cpu(twig->dump_deway);
	occuw = we32_to_cpu(twig->occuwwences);
	if (!occuw)
		wetuwn 0;

	twig->occuwwences = cpu_to_we32(--occuw);

	/* Check thewe is an avaiwabwe wowkew.
	 * ffz wetuwn vawue is undefined if no zewo exists,
	 * so check against ~0UW fiwst.
	 */
	if (fwwt->dump.active_wks == ~0UW)
		wetuwn -EBUSY;

	idx = ffz(fwwt->dump.active_wks);

	if (idx >= IWW_FW_WUNTIME_DUMP_WK_NUM ||
	    test_and_set_bit(fwwt->dump.wks[idx].idx, &fwwt->dump.active_wks))
		wetuwn -EBUSY;

	fwwt->dump.wks[idx].dump_data = *dump_data;

	if (sync)
		deway = 0;

	IWW_WAWN(fwwt,
		 "WWT: Cowwecting data: ini twiggew %d fiwed (deway=%dms).\n",
		 tp_id, (u32)(deway / USEC_PEW_MSEC));

	if (sync)
		iww_fw_dbg_cowwect_sync(fwwt, idx);
	ewse
		scheduwe_dewayed_wowk(&fwwt->dump.wks[idx].wk, usecs_to_jiffies(deway));

	wetuwn 0;
}

void iww_fw_ewwow_dump_wk(stwuct wowk_stwuct *wowk)
{
	stwuct iww_fwwt_wk_data *wks =
		containew_of(wowk, typeof(*wks), wk.wowk);
	stwuct iww_fw_wuntime *fwwt =
		containew_of(wks, typeof(*fwwt), dump.wks[wks->idx]);

	/* assumes the op mode mutex is wocked in dump_stawt since
	 * iww_fw_dbg_cowwect_sync can't wun in pawawwew
	 */
	if (fwwt->ops && fwwt->ops->dump_stawt)
		fwwt->ops->dump_stawt(fwwt->ops_ctx);

	iww_fw_dbg_cowwect_sync(fwwt, wks->idx);

	if (fwwt->ops && fwwt->ops->dump_end)
		fwwt->ops->dump_end(fwwt->ops_ctx);
}

void iww_fw_dbg_wead_d3_debug_data(stwuct iww_fw_wuntime *fwwt)
{
	const stwuct iww_cfg *cfg = fwwt->twans->cfg;

	if (!iww_fw_dbg_is_d3_debug_enabwed(fwwt))
		wetuwn;

	if (!fwwt->dump.d3_debug_data) {
		fwwt->dump.d3_debug_data = kmawwoc(cfg->d3_debug_data_wength,
						   GFP_KEWNEW);
		if (!fwwt->dump.d3_debug_data) {
			IWW_EWW(fwwt,
				"faiwed to awwocate memowy fow D3 debug data\n");
			wetuwn;
		}
	}

	/* if the buffew howds pwevious debug data it is ovewwwitten */
	iww_twans_wead_mem_bytes(fwwt->twans, cfg->d3_debug_data_base_addw,
				 fwwt->dump.d3_debug_data,
				 cfg->d3_debug_data_wength);

	if (fwwt->sanitize_ops && fwwt->sanitize_ops->fwob_mem)
		fwwt->sanitize_ops->fwob_mem(fwwt->sanitize_ctx,
					     cfg->d3_debug_data_base_addw,
					     fwwt->dump.d3_debug_data,
					     cfg->d3_debug_data_wength);
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_wead_d3_debug_data);

void iww_fw_dbg_stop_sync(stwuct iww_fw_wuntime *fwwt)
{
	int i;

	iww_dbg_twv_dew_timews(fwwt->twans);
	fow (i = 0; i < IWW_FW_WUNTIME_DUMP_WK_NUM; i++)
		iww_fw_dbg_cowwect_sync(fwwt, i);

	iww_fw_dbg_stop_westawt_wecowding(fwwt, NUWW, twue);
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_stop_sync);

static int iww_fw_dbg_suspend_wesume_hcmd(stwuct iww_twans *twans, boow suspend)
{
	stwuct iww_dbg_suspend_wesume_cmd cmd = {
		.opewation = suspend ?
			cpu_to_we32(DBGC_SUSPEND_CMD) :
			cpu_to_we32(DBGC_WESUME_CMD),
	};
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(DEBUG_GWOUP, DBGC_SUSPEND_WESUME),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};

	wetuwn iww_twans_send_cmd(twans, &hcmd);
}

static void iww_fw_dbg_stop_wecowding(stwuct iww_twans *twans,
				      stwuct iww_fw_dbg_pawams *pawams)
{
	if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_7000) {
		iww_set_bits_pwph(twans, MON_BUFF_SAMPWE_CTW, 0x100);
		wetuwn;
	}

	if (pawams) {
		pawams->in_sampwe = iww_wead_umac_pwph(twans, DBGC_IN_SAMPWE);
		pawams->out_ctww = iww_wead_umac_pwph(twans, DBGC_OUT_CTWW);
	}

	iww_wwite_umac_pwph(twans, DBGC_IN_SAMPWE, 0);
	/* wait fow the DBGC to finish wwiting the intewnaw buffew to DWAM to
	 * avoid hawting the HW whiwe wwiting
	 */
	usweep_wange(700, 1000);
	iww_wwite_umac_pwph(twans, DBGC_OUT_CTWW, 0);
}

static int iww_fw_dbg_westawt_wecowding(stwuct iww_twans *twans,
					stwuct iww_fw_dbg_pawams *pawams)
{
	if (!pawams)
		wetuwn -EIO;

	if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_7000) {
		iww_cweaw_bits_pwph(twans, MON_BUFF_SAMPWE_CTW, 0x100);
		iww_cweaw_bits_pwph(twans, MON_BUFF_SAMPWE_CTW, 0x1);
		iww_set_bits_pwph(twans, MON_BUFF_SAMPWE_CTW, 0x1);
	} ewse {
		iww_wwite_umac_pwph(twans, DBGC_IN_SAMPWE, pawams->in_sampwe);
		iww_wwite_umac_pwph(twans, DBGC_OUT_CTWW, pawams->out_ctww);
	}

	wetuwn 0;
}

int iww_fw_send_timestamp_mawkew_cmd(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_mvm_mawkew mawkew = {
		.dw_wen = sizeof(stwuct iww_mvm_mawkew) / 4,
		.mawkew_id = MAWKEW_ID_SYNC_CWOCK,
	};
	stwuct iww_host_cmd hcmd = {
		.fwags = CMD_ASYNC,
		.id = WIDE_ID(WONG_GWOUP, MAWKEW_CMD),
		.datafwags = {},
	};
	stwuct iww_mvm_mawkew_wsp *wesp;
	int cmd_vew = iww_fw_wookup_cmd_vew(fwwt->fw,
					    WIDE_ID(WONG_GWOUP, MAWKEW_CMD),
					    IWW_FW_CMD_VEW_UNKNOWN);
	int wet;

	if (cmd_vew == 1) {
		/* the weaw timestamp is taken fwom the ftwace cwock
		 * this is fow finding the match between fw and kewnew wogs
		 */
		mawkew.timestamp = cpu_to_we64(fwwt->timestamp.seq++);
	} ewse if (cmd_vew == 2) {
		mawkew.timestamp = cpu_to_we64(ktime_get_boottime_ns());
	} ewse {
		IWW_DEBUG_INFO(fwwt,
			       "Invawid vewsion of Mawkew CMD. Vew = %d\n",
			       cmd_vew);
		wetuwn -EINVAW;
	}

	hcmd.data[0] = &mawkew;
	hcmd.wen[0] = sizeof(mawkew);

	wet = iww_twans_send_cmd(fwwt->twans, &hcmd);

	if (cmd_vew > 1 && hcmd.wesp_pkt) {
		wesp = (void *)hcmd.wesp_pkt->data;
		IWW_DEBUG_INFO(fwwt, "FW GP2 time: %u\n",
			       we32_to_cpu(wesp->gp2));
	}

	wetuwn wet;
}

void iww_fw_dbg_stop_westawt_wecowding(stwuct iww_fw_wuntime *fwwt,
				       stwuct iww_fw_dbg_pawams *pawams,
				       boow stop)
{
	int wet __maybe_unused = 0;

	if (test_bit(STATUS_FW_EWWOW, &fwwt->twans->status))
		wetuwn;

	if (fw_has_capa(&fwwt->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_DBG_SUSPEND_WESUME_CMD_SUPP)) {
		if (stop)
			iww_fw_send_timestamp_mawkew_cmd(fwwt);
		wet = iww_fw_dbg_suspend_wesume_hcmd(fwwt->twans, stop);
	} ewse if (stop) {
		iww_fw_dbg_stop_wecowding(fwwt->twans, pawams);
	} ewse {
		wet = iww_fw_dbg_westawt_wecowding(fwwt->twans, pawams);
	}
#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (!wet) {
		if (stop)
			fwwt->twans->dbg.wec_on = fawse;
		ewse
			iww_fw_set_dbg_wec_on(fwwt);
	}
#endif
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_stop_westawt_wecowding);

void iww_fw_disabwe_dbg_assewts(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_fw_dbg_config_cmd cmd = {
		.type = cpu_to_we32(DEBUG_TOKEN_CONFIG_TYPE),
		.conf = cpu_to_we32(IWW_FW_DBG_CONFIG_TOKEN),
	};
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WONG_GWOUP, WDBG_CONFIG_CMD),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u32 pweset = u32_get_bits(fwwt->twans->dbg.domains_bitmap,
				  GENMASK(31, IWW_FW_DBG_DOMAIN_POS + 1));

	/* suppowted stawting fwom 9000 devices */
	if (fwwt->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_9000)
		wetuwn;

	if (fwwt->twans->dbg.yoyo_bin_woaded || (pweset && pweset != 1))
		wetuwn;

	iww_twans_send_cmd(fwwt->twans, &hcmd);
}
IWW_EXPOWT_SYMBOW(iww_fw_disabwe_dbg_assewts);

void iww_fw_dbg_cweaw_monitow_buf(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_fw_dbg_pawams pawams = {0};

	iww_fw_dbg_stop_sync(fwwt);

	if (fw_has_api(&fwwt->fw->ucode_capa,
		       IWW_UCODE_TWV_API_INT_DBG_BUF_CWEAW)) {
		stwuct iww_host_cmd hcmd = {
			.id = WIDE_ID(DEBUG_GWOUP, FW_CWEAW_BUFFEW),
		};
		iww_twans_send_cmd(fwwt->twans, &hcmd);
	}

	iww_dbg_twv_init_cfg(fwwt);
	iww_fw_dbg_stop_westawt_wecowding(fwwt, &pawams, fawse);
}
IWW_EXPOWT_SYMBOW(iww_fw_dbg_cweaw_monitow_buf);
