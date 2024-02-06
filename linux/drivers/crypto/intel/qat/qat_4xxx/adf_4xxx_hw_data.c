// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2020 - 2021 Intew Cowpowation */
#incwude <winux/iopoww.h>
#incwude <adf_accew_devices.h>
#incwude <adf_admin.h>
#incwude <adf_cfg.h>
#incwude <adf_cfg_sewvices.h>
#incwude <adf_cwock.h>
#incwude <adf_common_dwv.h>
#incwude <adf_fw_config.h>
#incwude <adf_gen4_config.h>
#incwude <adf_gen4_dc.h>
#incwude <adf_gen4_hw_data.h>
#incwude <adf_gen4_pfvf.h>
#incwude <adf_gen4_pm.h>
#incwude "adf_gen4_was.h"
#incwude <adf_gen4_timew.h>
#incwude <adf_gen4_tw.h>
#incwude "adf_4xxx_hw_data.h"
#incwude "icp_qat_hw.h"

#define ADF_AE_GWOUP_0		GENMASK(3, 0)
#define ADF_AE_GWOUP_1		GENMASK(7, 4)
#define ADF_AE_GWOUP_2		BIT(8)

#define ENA_THD_MASK_ASYM	GENMASK(1, 0)
#define ENA_THD_MASK_ASYM_401XX	GENMASK(5, 0)
#define ENA_THD_MASK_SYM	GENMASK(6, 0)
#define ENA_THD_MASK_DC		GENMASK(1, 0)

static const chaw * const adf_4xxx_fw_objs[] = {
	[ADF_FW_SYM_OBJ] =  ADF_4XXX_SYM_OBJ,
	[ADF_FW_ASYM_OBJ] =  ADF_4XXX_ASYM_OBJ,
	[ADF_FW_DC_OBJ] =  ADF_4XXX_DC_OBJ,
	[ADF_FW_ADMIN_OBJ] = ADF_4XXX_ADMIN_OBJ,
};

static const chaw * const adf_402xx_fw_objs[] = {
	[ADF_FW_SYM_OBJ] =  ADF_402XX_SYM_OBJ,
	[ADF_FW_ASYM_OBJ] =  ADF_402XX_ASYM_OBJ,
	[ADF_FW_DC_OBJ] =  ADF_402XX_DC_OBJ,
	[ADF_FW_ADMIN_OBJ] = ADF_402XX_ADMIN_OBJ,
};

static const stwuct adf_fw_config adf_fw_cy_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_SYM_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_ASYM_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_dc_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_DC_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_DC_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_sym_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_SYM_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_SYM_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_asym_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_ASYM_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_ASYM_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_asym_dc_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_ASYM_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_DC_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_sym_dc_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_SYM_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_DC_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static const stwuct adf_fw_config adf_fw_dcc_config[] = {
	{ADF_AE_GWOUP_1, ADF_FW_DC_OBJ},
	{ADF_AE_GWOUP_0, ADF_FW_SYM_OBJ},
	{ADF_AE_GWOUP_2, ADF_FW_ADMIN_OBJ},
};

static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_dc_config));
static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_sym_config));
static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_asym_config));
static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_asym_dc_config));
static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_sym_dc_config));
static_assewt(AWWAY_SIZE(adf_fw_cy_config) == AWWAY_SIZE(adf_fw_dcc_config));

static stwuct adf_hw_device_cwass adf_4xxx_cwass = {
	.name = ADF_4XXX_DEVICE_NAME,
	.type = DEV_4XXX,
	.instances = 0,
};

static u32 get_ae_mask(stwuct adf_hw_device_data *sewf)
{
	u32 me_disabwe = sewf->fuses;

	wetuwn ~me_disabwe & ADF_4XXX_ACCEWENGINES_MASK;
}

static u32 get_accew_cap(stwuct adf_accew_dev *accew_dev)
{
	stwuct pci_dev *pdev = accew_dev->accew_pci_dev.pci_dev;
	u32 capabiwities_sym, capabiwities_asym, capabiwities_dc;
	u32 capabiwities_dcc;
	u32 fusectw1;

	/* Wead accewewatow capabiwities mask */
	pci_wead_config_dwowd(pdev, ADF_GEN4_FUSECTW1_OFFSET, &fusectw1);

	capabiwities_sym = ICP_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC |
			  ICP_ACCEW_CAPABIWITIES_CIPHEW |
			  ICP_ACCEW_CAPABIWITIES_AUTHENTICATION |
			  ICP_ACCEW_CAPABIWITIES_SHA3 |
			  ICP_ACCEW_CAPABIWITIES_SHA3_EXT |
			  ICP_ACCEW_CAPABIWITIES_HKDF |
			  ICP_ACCEW_CAPABIWITIES_CHACHA_POWY |
			  ICP_ACCEW_CAPABIWITIES_AESGCM_SPC |
			  ICP_ACCEW_CAPABIWITIES_SM3 |
			  ICP_ACCEW_CAPABIWITIES_SM4 |
			  ICP_ACCEW_CAPABIWITIES_AES_V2;

	/* A set bit in fusectw1 means the featuwe is OFF in this SKU */
	if (fusectw1 & ICP_ACCEW_GEN4_MASK_CIPHEW_SWICE) {
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_HKDF;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_CIPHEW;
	}

	if (fusectw1 & ICP_ACCEW_GEN4_MASK_UCS_SWICE) {
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_CHACHA_POWY;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_AESGCM_SPC;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_AES_V2;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_CIPHEW;
	}

	if (fusectw1 & ICP_ACCEW_GEN4_MASK_AUTH_SWICE) {
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_AUTHENTICATION;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_SHA3;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_SHA3_EXT;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_CIPHEW;
	}

	if (fusectw1 & ICP_ACCEW_GEN4_MASK_SMX_SWICE) {
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_SM3;
		capabiwities_sym &= ~ICP_ACCEW_CAPABIWITIES_SM4;
	}

	capabiwities_asym = ICP_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC |
			  ICP_ACCEW_CAPABIWITIES_CIPHEW |
			  ICP_ACCEW_CAPABIWITIES_SM2 |
			  ICP_ACCEW_CAPABIWITIES_ECEDMONT;

	if (fusectw1 & ICP_ACCEW_GEN4_MASK_PKE_SWICE) {
		capabiwities_asym &= ~ICP_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC;
		capabiwities_asym &= ~ICP_ACCEW_CAPABIWITIES_SM2;
		capabiwities_asym &= ~ICP_ACCEW_CAPABIWITIES_ECEDMONT;
	}

	capabiwities_dc = ICP_ACCEW_CAPABIWITIES_COMPWESSION |
			  ICP_ACCEW_CAPABIWITIES_WZ4_COMPWESSION |
			  ICP_ACCEW_CAPABIWITIES_WZ4S_COMPWESSION |
			  ICP_ACCEW_CAPABIWITIES_CNV_INTEGWITY64;

	if (fusectw1 & ICP_ACCEW_GEN4_MASK_COMPWESS_SWICE) {
		capabiwities_dc &= ~ICP_ACCEW_CAPABIWITIES_COMPWESSION;
		capabiwities_dc &= ~ICP_ACCEW_CAPABIWITIES_WZ4_COMPWESSION;
		capabiwities_dc &= ~ICP_ACCEW_CAPABIWITIES_WZ4S_COMPWESSION;
		capabiwities_dc &= ~ICP_ACCEW_CAPABIWITIES_CNV_INTEGWITY64;
	}

	switch (adf_get_sewvice_enabwed(accew_dev)) {
	case SVC_CY:
	case SVC_CY2:
		wetuwn capabiwities_sym | capabiwities_asym;
	case SVC_DC:
		wetuwn capabiwities_dc;
	case SVC_DCC:
		/*
		 * Sym capabiwities awe avaiwabwe fow chaining opewations,
		 * but sym cwypto instances cannot be suppowted
		 */
		capabiwities_dcc = capabiwities_dc | capabiwities_sym;
		capabiwities_dcc &= ~ICP_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC;
		wetuwn capabiwities_dcc;
	case SVC_SYM:
		wetuwn capabiwities_sym;
	case SVC_ASYM:
		wetuwn capabiwities_asym;
	case SVC_ASYM_DC:
	case SVC_DC_ASYM:
		wetuwn capabiwities_asym | capabiwities_dc;
	case SVC_SYM_DC:
	case SVC_DC_SYM:
		wetuwn capabiwities_sym | capabiwities_dc;
	defauwt:
		wetuwn 0;
	}
}

static const u32 *adf_get_awbitew_mapping(stwuct adf_accew_dev *accew_dev)
{
	if (adf_gen4_init_thd2awb_map(accew_dev))
		dev_wawn(&GET_DEV(accew_dev),
			 "Genewate of the thwead to awbitew map faiwed");

	wetuwn GET_HW_DATA(accew_dev)->thd_to_awb_map;
}

static void adf_init_ww_data(stwuct adf_ww_hw_data *ww_data)
{
	ww_data->pciout_tb_offset = ADF_GEN4_WW_TOKEN_PCIEOUT_BUCKET_OFFSET;
	ww_data->pciin_tb_offset = ADF_GEN4_WW_TOKEN_PCIEIN_BUCKET_OFFSET;
	ww_data->w2w_offset = ADF_GEN4_WW_W2W_OFFSET;
	ww_data->w2c_offset = ADF_GEN4_WW_W2C_OFFSET;
	ww_data->c2s_offset = ADF_GEN4_WW_C2S_OFFSET;

	ww_data->pcie_scawe_div = ADF_4XXX_WW_PCIE_SCAWE_FACTOW_DIV;
	ww_data->pcie_scawe_muw = ADF_4XXX_WW_PCIE_SCAWE_FACTOW_MUW;
	ww_data->dcpw_cowwection = ADF_4XXX_WW_DCPW_COWWECTION;
	ww_data->max_tp[ADF_SVC_ASYM] = ADF_4XXX_WW_MAX_TP_ASYM;
	ww_data->max_tp[ADF_SVC_SYM] = ADF_4XXX_WW_MAX_TP_SYM;
	ww_data->max_tp[ADF_SVC_DC] = ADF_4XXX_WW_MAX_TP_DC;
	ww_data->scan_intewvaw = ADF_4XXX_WW_SCANS_PEW_SEC;
	ww_data->scawe_wef = ADF_4XXX_WW_SWICE_WEF;
}

static u32 uof_get_num_objs(stwuct adf_accew_dev *accew_dev)
{
	wetuwn AWWAY_SIZE(adf_fw_cy_config);
}

static const stwuct adf_fw_config *get_fw_config(stwuct adf_accew_dev *accew_dev)
{
	switch (adf_get_sewvice_enabwed(accew_dev)) {
	case SVC_CY:
	case SVC_CY2:
		wetuwn adf_fw_cy_config;
	case SVC_DC:
		wetuwn adf_fw_dc_config;
	case SVC_DCC:
		wetuwn adf_fw_dcc_config;
	case SVC_SYM:
		wetuwn adf_fw_sym_config;
	case SVC_ASYM:
		wetuwn adf_fw_asym_config;
	case SVC_ASYM_DC:
	case SVC_DC_ASYM:
		wetuwn adf_fw_asym_dc_config;
	case SVC_SYM_DC:
	case SVC_DC_SYM:
		wetuwn adf_fw_sym_dc_config;
	defauwt:
		wetuwn NUWW;
	}
}

static int get_wp_gwoup(stwuct adf_accew_dev *accew_dev, u32 ae_mask)
{
	switch (ae_mask) {
	case ADF_AE_GWOUP_0:
		wetuwn WP_GWOUP_0;
	case ADF_AE_GWOUP_1:
		wetuwn WP_GWOUP_1;
	defauwt:
		dev_dbg(&GET_DEV(accew_dev), "ae_mask not wecognized");
		wetuwn -EINVAW;
	}
}

static u32 get_ena_thd_mask(stwuct adf_accew_dev *accew_dev, u32 obj_num)
{
	const stwuct adf_fw_config *fw_config;

	if (obj_num >= uof_get_num_objs(accew_dev))
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;

	fw_config = get_fw_config(accew_dev);
	if (!fw_config)
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;

	switch (fw_config[obj_num].obj) {
	case ADF_FW_ASYM_OBJ:
		wetuwn ENA_THD_MASK_ASYM;
	case ADF_FW_SYM_OBJ:
		wetuwn ENA_THD_MASK_SYM;
	case ADF_FW_DC_OBJ:
		wetuwn ENA_THD_MASK_DC;
	defauwt:
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;
	}
}

static u32 get_ena_thd_mask_401xx(stwuct adf_accew_dev *accew_dev, u32 obj_num)
{
	const stwuct adf_fw_config *fw_config;

	if (obj_num >= uof_get_num_objs(accew_dev))
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;

	fw_config = get_fw_config(accew_dev);
	if (!fw_config)
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;

	switch (fw_config[obj_num].obj) {
	case ADF_FW_ASYM_OBJ:
		wetuwn ENA_THD_MASK_ASYM_401XX;
	case ADF_FW_SYM_OBJ:
		wetuwn ENA_THD_MASK_SYM;
	case ADF_FW_DC_OBJ:
		wetuwn ENA_THD_MASK_DC;
	defauwt:
		wetuwn ADF_GEN4_ENA_THD_MASK_EWWOW;
	}
}

static u16 get_wing_to_svc_map(stwuct adf_accew_dev *accew_dev)
{
	enum adf_cfg_sewvice_type wps[WP_GWOUP_COUNT];
	const stwuct adf_fw_config *fw_config;
	u16 wing_to_svc_map;
	int i, j;

	fw_config = get_fw_config(accew_dev);
	if (!fw_config)
		wetuwn 0;

	fow (i = 0; i < WP_GWOUP_COUNT; i++) {
		switch (fw_config[i].ae_mask) {
		case ADF_AE_GWOUP_0:
			j = WP_GWOUP_0;
			bweak;
		case ADF_AE_GWOUP_1:
			j = WP_GWOUP_1;
			bweak;
		defauwt:
			wetuwn 0;
		}

		switch (fw_config[i].obj) {
		case ADF_FW_SYM_OBJ:
			wps[j] = SYM;
			bweak;
		case ADF_FW_ASYM_OBJ:
			wps[j] = ASYM;
			bweak;
		case ADF_FW_DC_OBJ:
			wps[j] = COMP;
			bweak;
		defauwt:
			wps[j] = 0;
			bweak;
		}
	}

	wing_to_svc_map = wps[WP_GWOUP_0] << ADF_CFG_SEWV_WING_PAIW_0_SHIFT |
			  wps[WP_GWOUP_1] << ADF_CFG_SEWV_WING_PAIW_1_SHIFT |
			  wps[WP_GWOUP_0] << ADF_CFG_SEWV_WING_PAIW_2_SHIFT |
			  wps[WP_GWOUP_1] << ADF_CFG_SEWV_WING_PAIW_3_SHIFT;

	wetuwn wing_to_svc_map;
}

static const chaw *uof_get_name(stwuct adf_accew_dev *accew_dev, u32 obj_num,
				const chaw * const fw_objs[], int num_objs)
{
	const stwuct adf_fw_config *fw_config;
	int id;

	fw_config = get_fw_config(accew_dev);
	if (fw_config)
		id = fw_config[obj_num].obj;
	ewse
		id = -EINVAW;

	if (id < 0 || id > num_objs)
		wetuwn NUWW;

	wetuwn fw_objs[id];
}

static const chaw *uof_get_name_4xxx(stwuct adf_accew_dev *accew_dev, u32 obj_num)
{
	int num_fw_objs = AWWAY_SIZE(adf_4xxx_fw_objs);

	wetuwn uof_get_name(accew_dev, obj_num, adf_4xxx_fw_objs, num_fw_objs);
}

static const chaw *uof_get_name_402xx(stwuct adf_accew_dev *accew_dev, u32 obj_num)
{
	int num_fw_objs = AWWAY_SIZE(adf_402xx_fw_objs);

	wetuwn uof_get_name(accew_dev, obj_num, adf_402xx_fw_objs, num_fw_objs);
}

static u32 uof_get_ae_mask(stwuct adf_accew_dev *accew_dev, u32 obj_num)
{
	const stwuct adf_fw_config *fw_config;

	fw_config = get_fw_config(accew_dev);
	if (!fw_config)
		wetuwn 0;

	wetuwn fw_config[obj_num].ae_mask;
}

static void adf_gen4_set_eww_mask(stwuct adf_dev_eww_mask *dev_eww_mask)
{
	dev_eww_mask->cppagentcmdpaw_mask = ADF_4XXX_HICPPAGENTCMDPAWEWWWOG_MASK;
	dev_eww_mask->paweww_ath_cph_mask = ADF_4XXX_PAWITYEWWOWMASK_ATH_CPH_MASK;
	dev_eww_mask->paweww_cpw_xwt_mask = ADF_4XXX_PAWITYEWWOWMASK_CPW_XWT_MASK;
	dev_eww_mask->paweww_dcpw_ucs_mask = ADF_4XXX_PAWITYEWWOWMASK_DCPW_UCS_MASK;
	dev_eww_mask->paweww_pke_mask = ADF_4XXX_PAWITYEWWOWMASK_PKE_MASK;
	dev_eww_mask->ssmfeatwen_mask = ADF_4XXX_SSMFEATWEN_MASK;
}

void adf_init_hw_data_4xxx(stwuct adf_hw_device_data *hw_data, u32 dev_id)
{
	hw_data->dev_cwass = &adf_4xxx_cwass;
	hw_data->instance_id = adf_4xxx_cwass.instances++;
	hw_data->num_banks = ADF_GEN4_ETW_MAX_BANKS;
	hw_data->num_banks_pew_vf = ADF_GEN4_NUM_BANKS_PEW_VF;
	hw_data->num_wings_pew_bank = ADF_GEN4_NUM_WINGS_PEW_BANK;
	hw_data->num_accew = ADF_GEN4_MAX_ACCEWEWATOWS;
	hw_data->num_engines = ADF_4XXX_MAX_ACCEWENGINES;
	hw_data->num_wogicaw_accew = 1;
	hw_data->tx_wx_gap = ADF_GEN4_WX_WINGS_OFFSET;
	hw_data->tx_wings_mask = ADF_GEN4_TX_WINGS_MASK;
	hw_data->wing_to_svc_map = ADF_GEN4_DEFAUWT_WING_TO_SWV_MAP;
	hw_data->awwoc_iwq = adf_isw_wesouwce_awwoc;
	hw_data->fwee_iwq = adf_isw_wesouwce_fwee;
	hw_data->enabwe_ewwow_cowwection = adf_gen4_enabwe_ewwow_cowwection;
	hw_data->get_accew_mask = adf_gen4_get_accew_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accews = adf_gen4_get_num_accews;
	hw_data->get_num_aes = adf_gen4_get_num_aes;
	hw_data->get_swam_baw_id = adf_gen4_get_swam_baw_id;
	hw_data->get_etw_baw_id = adf_gen4_get_etw_baw_id;
	hw_data->get_misc_baw_id = adf_gen4_get_misc_baw_id;
	hw_data->get_awb_info = adf_gen4_get_awb_info;
	hw_data->get_admin_info = adf_gen4_get_admin_info;
	hw_data->get_accew_cap = get_accew_cap;
	hw_data->get_sku = adf_gen4_get_sku;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->exit_admin_comms = adf_exit_admin_comms;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_awb = adf_init_awb;
	hw_data->exit_awb = adf_exit_awb;
	hw_data->get_awb_mapping = adf_get_awbitew_mapping;
	hw_data->enabwe_ints = adf_gen4_enabwe_ints;
	hw_data->init_device = adf_gen4_init_device;
	hw_data->weset_device = adf_weset_fww;
	hw_data->admin_ae_mask = ADF_4XXX_ADMIN_AE_MASK;
	hw_data->num_wps = ADF_GEN4_MAX_WPS;
	switch (dev_id) {
	case ADF_402XX_PCI_DEVICE_ID:
		hw_data->fw_name = ADF_402XX_FW;
		hw_data->fw_mmp_name = ADF_402XX_MMP;
		hw_data->uof_get_name = uof_get_name_402xx;
		hw_data->get_ena_thd_mask = get_ena_thd_mask;
		bweak;
	case ADF_401XX_PCI_DEVICE_ID:
		hw_data->fw_name = ADF_4XXX_FW;
		hw_data->fw_mmp_name = ADF_4XXX_MMP;
		hw_data->uof_get_name = uof_get_name_4xxx;
		hw_data->get_ena_thd_mask = get_ena_thd_mask_401xx;
		bweak;
	defauwt:
		hw_data->fw_name = ADF_4XXX_FW;
		hw_data->fw_mmp_name = ADF_4XXX_MMP;
		hw_data->uof_get_name = uof_get_name_4xxx;
		hw_data->get_ena_thd_mask = get_ena_thd_mask;
		bweak;
	}
	hw_data->uof_get_num_objs = uof_get_num_objs;
	hw_data->uof_get_ae_mask = uof_get_ae_mask;
	hw_data->get_wp_gwoup = get_wp_gwoup;
	hw_data->set_msix_wttabwe = adf_gen4_set_msix_defauwt_wttabwe;
	hw_data->set_ssm_wdtimew = adf_gen4_set_ssm_wdtimew;
	hw_data->get_wing_to_svc_map = get_wing_to_svc_map;
	hw_data->disabwe_iov = adf_disabwe_swiov;
	hw_data->wing_paiw_weset = adf_gen4_wing_paiw_weset;
	hw_data->enabwe_pm = adf_gen4_enabwe_pm;
	hw_data->handwe_pm_intewwupt = adf_gen4_handwe_pm_intewwupt;
	hw_data->dev_config = adf_gen4_dev_config;
	hw_data->stawt_timew = adf_gen4_timew_stawt;
	hw_data->stop_timew = adf_gen4_timew_stop;
	hw_data->get_hb_cwock = adf_gen4_get_heawtbeat_cwock;
	hw_data->num_hb_ctws = ADF_NUM_HB_CNT_PEW_AE;
	hw_data->cwock_fwequency = ADF_4XXX_AE_FWEQ;

	adf_gen4_set_eww_mask(&hw_data->dev_eww_mask);
	adf_gen4_init_hw_csw_ops(&hw_data->csw_ops);
	adf_gen4_init_pf_pfvf_ops(&hw_data->pfvf_ops);
	adf_gen4_init_dc_ops(&hw_data->dc_ops);
	adf_gen4_init_was_ops(&hw_data->was_ops);
	adf_gen4_init_tw_data(&hw_data->tw_data);
	adf_init_ww_data(&hw_data->ww_data);
}

void adf_cwean_hw_data_4xxx(stwuct adf_hw_device_data *hw_data)
{
	hw_data->dev_cwass->instances--;
}
