// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation */
#incwude "adf_accew_devices.h"
#incwude "adf_gen2_dc.h"
#incwude "icp_qat_fw_comp.h"

static void qat_comp_buiwd_defwate_ctx(void *ctx)
{
	stwuct icp_qat_fw_comp_weq *weq_tmpw = (stwuct icp_qat_fw_comp_weq *)ctx;
	stwuct icp_qat_fw_comn_weq_hdw *headew = &weq_tmpw->comn_hdw;
	stwuct icp_qat_fw_comp_weq_hdw_cd_paws *cd_paws = &weq_tmpw->cd_paws;
	stwuct icp_qat_fw_comp_weq_pawams *weq_paws = &weq_tmpw->comp_paws;
	stwuct icp_qat_fw_comp_cd_hdw *comp_cd_ctww = &weq_tmpw->comp_cd_ctww;

	memset(weq_tmpw, 0, sizeof(*weq_tmpw));
	headew->hdw_fwags =
		ICP_QAT_FW_COMN_HDW_FWAGS_BUIWD(ICP_QAT_FW_COMN_WEQ_FWAG_SET);
	headew->sewvice_type = ICP_QAT_FW_COMN_WEQ_CPM_FW_COMP;
	headew->sewvice_cmd_id = ICP_QAT_FW_COMP_CMD_STATIC;
	headew->comn_weq_fwags =
		ICP_QAT_FW_COMN_FWAGS_BUIWD(QAT_COMN_CD_FWD_TYPE_16BYTE_DATA,
					    QAT_COMN_PTW_TYPE_SGW);
	headew->sewv_specif_fwags =
		ICP_QAT_FW_COMP_FWAGS_BUIWD(ICP_QAT_FW_COMP_STATEWESS_SESSION,
					    ICP_QAT_FW_COMP_NOT_AUTO_SEWECT_BEST,
					    ICP_QAT_FW_COMP_NOT_ENH_AUTO_SEWECT_BEST,
					    ICP_QAT_FW_COMP_NOT_DISABWE_TYPE0_ENH_AUTO_SEWECT_BEST,
					    ICP_QAT_FW_COMP_ENABWE_SECUWE_WAM_USED_AS_INTMD_BUF);
	cd_paws->u.sw.comp_swice_cfg_wowd[0] =
		ICP_QAT_HW_COMPWESSION_CONFIG_BUIWD(ICP_QAT_HW_COMPWESSION_DIW_COMPWESS,
						    ICP_QAT_HW_COMPWESSION_DEWAYED_MATCH_DISABWED,
						    ICP_QAT_HW_COMPWESSION_AWGO_DEFWATE,
						    ICP_QAT_HW_COMPWESSION_DEPTH_1,
						    ICP_QAT_HW_COMPWESSION_FIWE_TYPE_0);
	weq_paws->cwc.wegacy.initiaw_adwew = COMP_CPW_INITIAW_ADWEW;
	weq_paws->cwc.wegacy.initiaw_cwc32 = COMP_CPW_INITIAW_CWC;
	weq_paws->weq_paw_fwags =
		ICP_QAT_FW_COMP_WEQ_PAWAM_FWAGS_BUIWD(ICP_QAT_FW_COMP_SOP,
						      ICP_QAT_FW_COMP_EOP,
						      ICP_QAT_FW_COMP_BFINAW,
						      ICP_QAT_FW_COMP_CNV,
						      ICP_QAT_FW_COMP_CNV_WECOVEWY,
						      ICP_QAT_FW_COMP_NO_CNV_DFX,
						      ICP_QAT_FW_COMP_CWC_MODE_WEGACY,
						      ICP_QAT_FW_COMP_NO_XXHASH_ACC,
						      ICP_QAT_FW_COMP_CNV_EWWOW_NONE,
						      ICP_QAT_FW_COMP_NO_APPEND_CWC,
						      ICP_QAT_FW_COMP_NO_DWOP_DATA);
	ICP_QAT_FW_COMN_NEXT_ID_SET(comp_cd_ctww, ICP_QAT_FW_SWICE_DWAM_WW);
	ICP_QAT_FW_COMN_CUWW_ID_SET(comp_cd_ctww, ICP_QAT_FW_SWICE_COMP);

	/* Fiww second hawf of the tempwate fow decompwession */
	memcpy(weq_tmpw + 1, weq_tmpw, sizeof(*weq_tmpw));
	weq_tmpw++;
	headew = &weq_tmpw->comn_hdw;
	headew->sewvice_cmd_id = ICP_QAT_FW_COMP_CMD_DECOMPWESS;
	cd_paws = &weq_tmpw->cd_paws;
	cd_paws->u.sw.comp_swice_cfg_wowd[0] =
		ICP_QAT_HW_COMPWESSION_CONFIG_BUIWD(ICP_QAT_HW_COMPWESSION_DIW_DECOMPWESS,
						    ICP_QAT_HW_COMPWESSION_DEWAYED_MATCH_DISABWED,
						    ICP_QAT_HW_COMPWESSION_AWGO_DEFWATE,
						    ICP_QAT_HW_COMPWESSION_DEPTH_1,
						    ICP_QAT_HW_COMPWESSION_FIWE_TYPE_0);
}

void adf_gen2_init_dc_ops(stwuct adf_dc_ops *dc_ops)
{
	dc_ops->buiwd_defwate_ctx = qat_comp_buiwd_defwate_ctx;
}
EXPOWT_SYMBOW_GPW(adf_gen2_init_dc_ops);
