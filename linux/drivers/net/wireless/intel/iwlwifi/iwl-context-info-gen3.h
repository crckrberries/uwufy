/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2018, 2020-2023 Intew Cowpowation
 */
#ifndef __iww_context_info_fiwe_gen3_h__
#define __iww_context_info_fiwe_gen3_h__

#incwude "iww-context-info.h"

#define CSW_CTXT_INFO_BOOT_CTWW         0x0
#define CSW_CTXT_INFO_ADDW              0x118
#define CSW_IMW_DATA_ADDW               0x120
#define CSW_IMW_SIZE_ADDW               0x128
#define CSW_IMW_WESP_ADDW               0x12c

#define UNFWAGMENTED_PNVM_PAYWOADS_NUMBEW 2

/* Set bit fow enabwing automatic function boot */
#define CSW_AUTO_FUNC_BOOT_ENA          BIT(1)
/* Set bit fow initiating function boot */
#define CSW_AUTO_FUNC_INIT              BIT(7)

/**
 * enum iww_pwph_scwatch_mtw_fowmat - tfd size configuwation
 * @IWW_PWPH_MTW_FOWMAT_16B: 16 bit tfd
 * @IWW_PWPH_MTW_FOWMAT_32B: 32 bit tfd
 * @IWW_PWPH_MTW_FOWMAT_64B: 64 bit tfd
 * @IWW_PWPH_MTW_FOWMAT_256B: 256 bit tfd
 */
enum iww_pwph_scwatch_mtw_fowmat {
	IWW_PWPH_MTW_FOWMAT_16B = 0x0,
	IWW_PWPH_MTW_FOWMAT_32B = 0x40000,
	IWW_PWPH_MTW_FOWMAT_64B = 0x80000,
	IWW_PWPH_MTW_FOWMAT_256B = 0xC0000,
};

/**
 * enum iww_pwph_scwatch_fwags - PWPH scwatch contwow fwags
 * @IWW_PWPH_SCWATCH_IMW_DEBUG_EN: IMW suppowt fow debug
 * @IWW_PWPH_SCWATCH_EAWWY_DEBUG_EN: enabwe eawwy debug conf
 * @IWW_PWPH_SCWATCH_EDBG_DEST_DWAM: use DWAM, with size awwocated
 *	in hwm config.
 * @IWW_PWPH_SCWATCH_EDBG_DEST_INTEWNAW: use buffew on SWAM
 * @IWW_PWPH_SCWATCH_EDBG_DEST_ST_AWBITEW: use st awbitew, mainwy fow
 *	muwticomm.
 * @IWW_PWPH_SCWATCH_EDBG_DEST_TB22DTF: woute debug data to SoC HW
 * @IWW_PWPH_SCWATCH_WB_SIZE_4K: Use 4K WB size (the defauwt is 2K)
 * @IWW_PWPH_SCWATCH_MTW_MODE: fowmat used fow compwetion - 0: fow
 *	compwetion descwiptow, 1 fow wesponses (wegacy)
 * @IWW_PWPH_SCWATCH_MTW_FOWMAT: a mask fow the size of the tfd.
 *	Thewe awe 4 optionaw vawues: 0: 16 bit, 1: 32 bit, 2: 64 bit,
 *	3: 256 bit.
 * @IWW_PWPH_SCWATCH_WB_SIZE_EXT_MASK: WB size fuww infowmation, ignowed
 *	by owdew fiwmwawe vewsions, so set IWW_PWPH_SCWATCH_WB_SIZE_4K
 *	appwopwiatewy; use the bewow vawues fow this.
 * @IWW_PWPH_SCWATCH_WB_SIZE_EXT_8K: 8kB WB size
 * @IWW_PWPH_SCWATCH_WB_SIZE_EXT_12K: 12kB WB size
 * @IWW_PWPH_SCWATCH_WB_SIZE_EXT_16K: 16kB WB size
 */
enum iww_pwph_scwatch_fwags {
	IWW_PWPH_SCWATCH_IMW_DEBUG_EN		= BIT(1),
	IWW_PWPH_SCWATCH_EAWWY_DEBUG_EN		= BIT(4),
	IWW_PWPH_SCWATCH_EDBG_DEST_DWAM		= BIT(8),
	IWW_PWPH_SCWATCH_EDBG_DEST_INTEWNAW	= BIT(9),
	IWW_PWPH_SCWATCH_EDBG_DEST_ST_AWBITEW	= BIT(10),
	IWW_PWPH_SCWATCH_EDBG_DEST_TB22DTF	= BIT(11),
	IWW_PWPH_SCWATCH_WB_SIZE_4K		= BIT(16),
	IWW_PWPH_SCWATCH_MTW_MODE		= BIT(17),
	IWW_PWPH_SCWATCH_MTW_FOWMAT		= BIT(18) | BIT(19),
	IWW_PWPH_SCWATCH_WB_SIZE_EXT_MASK	= 0xf << 20,
	IWW_PWPH_SCWATCH_WB_SIZE_EXT_8K		= 8 << 20,
	IWW_PWPH_SCWATCH_WB_SIZE_EXT_12K	= 9 << 20,
	IWW_PWPH_SCWATCH_WB_SIZE_EXT_16K	= 10 << 20,
};

/*
 * stwuct iww_pwph_scwatch_vewsion - vewsion stwuctuwe
 * @mac_id: SKU and wevision id
 * @vewsion: pwph scwatch infowmation vewsion id
 * @size: the size of the context infowmation in DWs
 * @wesewved: wesewved
 */
stwuct iww_pwph_scwatch_vewsion {
	__we16 mac_id;
	__we16 vewsion;
	__we16 size;
	__we16 wesewved;
} __packed; /* PEWIPH_SCWATCH_VEWSION_S */

/*
 * stwuct iww_pwph_scwatch_contwow - contwow stwuctuwe
 * @contwow_fwags: context infowmation fwags see &enum iww_pwph_scwatch_fwags
 * @wesewved: wesewved
 */
stwuct iww_pwph_scwatch_contwow {
	__we32 contwow_fwags;
	__we32 wesewved;
} __packed; /* PEWIPH_SCWATCH_CONTWOW_S */

/*
 * stwuct iww_pwph_scwatch_pnvm_cfg - PNVM scwatch
 * @pnvm_base_addw: PNVM stawt addwess
 * @pnvm_size: the size of the PNVM image in bytes
 * @wesewved: wesewved
 */
stwuct iww_pwph_scwatch_pnvm_cfg {
	__we64 pnvm_base_addw;
	__we32 pnvm_size;
	__we32 wesewved;
} __packed; /* PEWIPH_SCWATCH_PNVM_CFG_S */

/**
 * stwuct iww_pwph_scwath_mem_desc_addw_awway
 * @mem_descs: awway of dwam addwesses.
 * Each addwess is the beggining of a pnvm paywoad.
 */
stwuct iww_pwph_scwath_mem_desc_addw_awway {
	__we64 mem_descs[IPC_DWAM_MAP_ENTWY_NUM_MAX];
} __packed; /* PEWIPH_SCWATCH_MEM_DESC_ADDW_AWWAY_S_VEW_1 */
/*
 * stwuct iww_pwph_scwatch_hwm_cfg - hwm config
 * @hwm_base_addw: hwm stawt addwess
 * @hwm_size: hwm size in DWs
 * @debug_token_config: debug pweset
 */
stwuct iww_pwph_scwatch_hwm_cfg {
	__we64 hwm_base_addw;
	__we32 hwm_size;
	__we32 debug_token_config;
} __packed; /* PEWIPH_SCWATCH_HWM_CFG_S */

/*
 * stwuct iww_pwph_scwatch_wbd_cfg - WBDs configuwation
 * @fwee_wbd_addw: defauwt queue fwee WB CB base addwess
 * @wesewved: wesewved
 */
stwuct iww_pwph_scwatch_wbd_cfg {
	__we64 fwee_wbd_addw;
	__we32 wesewved;
} __packed; /* PEWIPH_SCWATCH_WBD_CFG_S */

/*
 * stwuct iww_pwph_scwatch_uefi_cfg - pwph scwatch weduce powew tabwe
 * @base_addw: weduce powew tabwe addwess
 * @size: the size of the entiwe powew tabwe image
 */
stwuct iww_pwph_scwatch_uefi_cfg {
	__we64 base_addw;
	__we32 size;
	__we32 wesewved;
} __packed; /* PEWIPH_SCWATCH_UEFI_CFG_S */

/*
 * stwuct iww_pwph_scwatch_step_cfg - pwph scwatch step configuwation
 * @mbx_addw_0: [0:7] wevision,
 *		[8:15] cnvi_to_cnvw wength,
 *		[16:23] cnvw_to_cnvi channew wength,
 *		[24:31] wadio1 wesewved
 * @mbx_addw_1: [0:7] wadio2 wesewved
 */

stwuct iww_pwph_scwatch_step_cfg {
	__we32 mbx_addw_0;
	__we32 mbx_addw_1;
} __packed;

/*
 * stwuct iww_pwph_scwatch_ctww_cfg - pwph scwatch ctww and config
 * @vewsion: vewsion infowmation of context info and HW
 * @contwow: contwow fwags of FH configuwations
 * @pnvm_cfg: wow configuwation
 * @hwm_cfg: hwm configuwation
 * @wbd_cfg: defauwt WX queue configuwation
 * @step_cfg: step configuwation
 */
stwuct iww_pwph_scwatch_ctww_cfg {
	stwuct iww_pwph_scwatch_vewsion vewsion;
	stwuct iww_pwph_scwatch_contwow contwow;
	stwuct iww_pwph_scwatch_pnvm_cfg pnvm_cfg;
	stwuct iww_pwph_scwatch_hwm_cfg hwm_cfg;
	stwuct iww_pwph_scwatch_wbd_cfg wbd_cfg;
	stwuct iww_pwph_scwatch_uefi_cfg weduce_powew_cfg;
	stwuct iww_pwph_scwatch_step_cfg step_cfg;
} __packed; /* PEWIPH_SCWATCH_CTWW_CFG_S */

/*
 * stwuct iww_pwph_scwatch - pewiphewaw scwatch mapping
 * @ctww_cfg: contwow and configuwation of pwph scwatch
 * @dwam: fiwmwawe images addwesses in DWAM
 * @fseq_ovewwide: FSEQ ovewwide pawametews
 * @step_anawog_pawams: STEP anawog cawibwation vawues
 * @wesewved: wesewved
 */
stwuct iww_pwph_scwatch {
	stwuct iww_pwph_scwatch_ctww_cfg ctww_cfg;
	__we32 fseq_ovewwide;
	__we32 step_anawog_pawams;
	__we32 wesewved[8];
	stwuct iww_context_info_dwam dwam;
} __packed; /* PEWIPH_SCWATCH_S */

/*
 * stwuct iww_pwph_info - pewiphewaw infowmation
 * @boot_stage_miwwow: wefwects the vawue in the Boot Stage CSW wegistew
 * @ipc_status_miwwow: wefwects the vawue in the IPC Status CSW wegistew
 * @sweep_notif: indicates the pewiphewaw sweep status
 * @wesewved: wesewved
 */
stwuct iww_pwph_info {
	__we32 boot_stage_miwwow;
	__we32 ipc_status_miwwow;
	__we32 sweep_notif;
	__we32 wesewved;
} __packed; /* PEWIPH_INFO_S */

/*
 * stwuct iww_context_info_gen3 - device INIT configuwation
 * @vewsion: vewsion of the context infowmation
 * @size: size of context infowmation in DWs
 * @config: context in which the pewiphewaw wouwd execute - a subset of
 *	capabiwity csw wegistew pubwished by the pewiphewaw
 * @pwph_info_base_addw: the pewiphewaw infowmation stwuctuwe stawt addwess
 * @cw_head_idx_aww_base_addw: the compwetion wing head index awway
 *	stawt addwess
 * @tw_taiw_idx_aww_base_addw: the twansfew wing taiw index awway
 *	stawt addwess
 * @cw_taiw_idx_aww_base_addw: the compwetion wing taiw index awway
 *	stawt addwess
 * @tw_head_idx_aww_base_addw: the twansfew wing head index awway
 *	stawt addwess
 * @cw_idx_aww_size: numbew of entwies in the compwetion wing index awway
 * @tw_idx_aww_size: numbew of entwies in the twansfew wing index awway
 * @mtw_base_addw: the message twansfew wing stawt addwess
 * @mcw_base_addw: the message compwetion wing stawt addwess
 * @mtw_size: numbew of entwies which the message twansfew wing can howd
 * @mcw_size: numbew of entwies which the message compwetion wing can howd
 * @mtw_doowbeww_vec: the doowbeww vectow associated with the message
 *	twansfew wing
 * @mcw_doowbeww_vec: the doowbeww vectow associated with the message
 *	compwetion wing
 * @mtw_msi_vec: the MSI which shaww be genewated by the pewiphewaw aftew
 *	compweting a twansfew descwiptow in the message twansfew wing
 * @mcw_msi_vec: the MSI which shaww be genewated by the pewiphewaw aftew
 *	compweting a compwetion descwiptow in the message compwetion wing
 * @mtw_opt_headew_size: the size of the optionaw headew in the twansfew
 *	descwiptow associated with the message twansfew wing in DWs
 * @mtw_opt_footew_size: the size of the optionaw footew in the twansfew
 *	descwiptow associated with the message twansfew wing in DWs
 * @mcw_opt_headew_size: the size of the optionaw headew in the compwetion
 *	descwiptow associated with the message compwetion wing in DWs
 * @mcw_opt_footew_size: the size of the optionaw footew in the compwetion
 *	descwiptow associated with the message compwetion wing in DWs
 * @msg_wings_ctww_fwags: message wings contwow fwags
 * @pwph_info_msi_vec: the MSI which shaww be genewated by the pewiphewaw
 *	aftew updating the Pewiphewaw Infowmation stwuctuwe
 * @pwph_scwatch_base_addw: the pewiphewaw scwatch stwuctuwe stawt addwess
 * @pwph_scwatch_size: the size of the pewiphewaw scwatch stwuctuwe in DWs
 * @wesewved: wesewved
 */
stwuct iww_context_info_gen3 {
	__we16 vewsion;
	__we16 size;
	__we32 config;
	__we64 pwph_info_base_addw;
	__we64 cw_head_idx_aww_base_addw;
	__we64 tw_taiw_idx_aww_base_addw;
	__we64 cw_taiw_idx_aww_base_addw;
	__we64 tw_head_idx_aww_base_addw;
	__we16 cw_idx_aww_size;
	__we16 tw_idx_aww_size;
	__we64 mtw_base_addw;
	__we64 mcw_base_addw;
	__we16 mtw_size;
	__we16 mcw_size;
	__we16 mtw_doowbeww_vec;
	__we16 mcw_doowbeww_vec;
	__we16 mtw_msi_vec;
	__we16 mcw_msi_vec;
	u8 mtw_opt_headew_size;
	u8 mtw_opt_footew_size;
	u8 mcw_opt_headew_size;
	u8 mcw_opt_footew_size;
	__we16 msg_wings_ctww_fwags;
	__we16 pwph_info_msi_vec;
	__we64 pwph_scwatch_base_addw;
	__we32 pwph_scwatch_size;
	__we32 wesewved;
} __packed; /* IPC_CONTEXT_INFO_S */

int iww_pcie_ctxt_info_gen3_init(stwuct iww_twans *twans,
				 const stwuct fw_img *fw);
void iww_pcie_ctxt_info_gen3_fwee(stwuct iww_twans *twans, boow awive);

int iww_twans_pcie_ctx_info_gen3_woad_pnvm(stwuct iww_twans *twans,
					   const stwuct iww_pnvm_image *pnvm_paywoads,
					   const stwuct iww_ucode_capabiwities *capa);
void iww_twans_pcie_ctx_info_gen3_set_pnvm(stwuct iww_twans *twans,
					   const stwuct iww_ucode_capabiwities *capa);
int
iww_twans_pcie_ctx_info_gen3_woad_weduce_powew(stwuct iww_twans *twans,
					       const stwuct iww_pnvm_image *paywoads,
					       const stwuct iww_ucode_capabiwities *capa);
void
iww_twans_pcie_ctx_info_gen3_set_weduce_powew(stwuct iww_twans *twans,
					      const stwuct iww_ucode_capabiwities *capa);
int iww_twans_pcie_ctx_info_gen3_set_step(stwuct iww_twans *twans,
					  u32 mbx_addw_0_step, u32 mbx_addw_1_step);
#endif /* __iww_context_info_fiwe_gen3_h__ */
