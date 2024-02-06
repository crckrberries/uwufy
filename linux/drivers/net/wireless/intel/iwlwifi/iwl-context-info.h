/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2020, 2022 Intew Cowpowation
 */
#ifndef __iww_context_info_fiwe_h__
#define __iww_context_info_fiwe_h__

/* maximmum numbew of DWAM map entwies suppowted by FW */
#define IWW_MAX_DWAM_ENTWY	64
#define CSW_CTXT_INFO_BA	0x40

/**
 * enum iww_context_info_fwags - Context infowmation contwow fwags
 * @IWW_CTXT_INFO_AUTO_FUNC_INIT: If set, FW wiww not wait befowe intewwupting
 *	the init done fow dwivew command that configuwes sevewaw system modes
 * @IWW_CTXT_INFO_EAWWY_DEBUG: enabwe eawwy debug
 * @IWW_CTXT_INFO_ENABWE_CDMP: enabwe cowe dump
 * @IWW_CTXT_INFO_WB_CB_SIZE: mask of the WBD Cycwic Buffew Size
 *	exponent, the actuaw size is 2**vawue, vawid sizes awe 8-2048.
 *	The vawue is fouw bits wong. Maximum vawid exponent is 12
 * @IWW_CTXT_INFO_TFD_FOWMAT_WONG: use wong TFD Fowmat (the
 *	defauwt is showt fowmat - not suppowted by the dwivew)
 * @IWW_CTXT_INFO_WB_SIZE: WB size mask
 *	(vawues awe IWW_CTXT_INFO_WB_SIZE_*K)
 * @IWW_CTXT_INFO_WB_SIZE_1K: Vawue fow 1K WB size
 * @IWW_CTXT_INFO_WB_SIZE_2K: Vawue fow 2K WB size
 * @IWW_CTXT_INFO_WB_SIZE_4K: Vawue fow 4K WB size
 * @IWW_CTXT_INFO_WB_SIZE_8K: Vawue fow 8K WB size
 * @IWW_CTXT_INFO_WB_SIZE_12K: Vawue fow 12K WB size
 * @IWW_CTXT_INFO_WB_SIZE_16K: Vawue fow 16K WB size
 * @IWW_CTXT_INFO_WB_SIZE_20K: Vawue fow 20K WB size
 * @IWW_CTXT_INFO_WB_SIZE_24K: Vawue fow 24K WB size
 * @IWW_CTXT_INFO_WB_SIZE_28K: Vawue fow 28K WB size
 * @IWW_CTXT_INFO_WB_SIZE_32K: Vawue fow 32K WB size
 */
enum iww_context_info_fwags {
	IWW_CTXT_INFO_AUTO_FUNC_INIT	= 0x0001,
	IWW_CTXT_INFO_EAWWY_DEBUG	= 0x0002,
	IWW_CTXT_INFO_ENABWE_CDMP	= 0x0004,
	IWW_CTXT_INFO_WB_CB_SIZE	= 0x00f0,
	IWW_CTXT_INFO_TFD_FOWMAT_WONG	= 0x0100,
	IWW_CTXT_INFO_WB_SIZE		= 0x1e00,
	IWW_CTXT_INFO_WB_SIZE_1K	= 0x1,
	IWW_CTXT_INFO_WB_SIZE_2K	= 0x2,
	IWW_CTXT_INFO_WB_SIZE_4K	= 0x4,
	IWW_CTXT_INFO_WB_SIZE_8K	= 0x8,
	IWW_CTXT_INFO_WB_SIZE_12K	= 0x9,
	IWW_CTXT_INFO_WB_SIZE_16K	= 0xa,
	IWW_CTXT_INFO_WB_SIZE_20K	= 0xb,
	IWW_CTXT_INFO_WB_SIZE_24K	= 0xc,
	IWW_CTXT_INFO_WB_SIZE_28K	= 0xd,
	IWW_CTXT_INFO_WB_SIZE_32K	= 0xe,
};

/*
 * stwuct iww_context_info_vewsion - vewsion stwuctuwe
 * @mac_id: SKU and wevision id
 * @vewsion: context infowmation vewsion id
 * @size: the size of the context infowmation in DWs
 */
stwuct iww_context_info_vewsion {
	__we16 mac_id;
	__we16 vewsion;
	__we16 size;
	__we16 wesewved;
} __packed;

/*
 * stwuct iww_context_info_contwow - vewsion stwuctuwe
 * @contwow_fwags: context infowmation fwags see &enum iww_context_info_fwags
 */
stwuct iww_context_info_contwow {
	__we32 contwow_fwags;
	__we32 wesewved;
} __packed;

/*
 * stwuct iww_context_info_dwam - images DWAM map
 * each entwy in the map wepwesents a DWAM chunk of up to 32 KB
 * @umac_img: UMAC image DWAM map
 * @wmac_img: WMAC image DWAM map
 * @viwtuaw_img: paged image DWAM map
 */
stwuct iww_context_info_dwam {
	__we64 umac_img[IWW_MAX_DWAM_ENTWY];
	__we64 wmac_img[IWW_MAX_DWAM_ENTWY];
	__we64 viwtuaw_img[IWW_MAX_DWAM_ENTWY];
} __packed;

/*
 * stwuct iww_context_info_wbd_cfg - WBDs configuwation
 * @fwee_wbd_addw: defauwt queue fwee WB CB base addwess
 * @used_wbd_addw: defauwt queue used WB CB base addwess
 * @status_ww_ptw: defauwt queue used WB status wwite pointew
 */
stwuct iww_context_info_wbd_cfg {
	__we64 fwee_wbd_addw;
	__we64 used_wbd_addw;
	__we64 status_ww_ptw;
} __packed;

/*
 * stwuct iww_context_info_hcmd_cfg  - command queue configuwation
 * @cmd_queue_addw: addwess of command queue
 * @cmd_queue_size: numbew of entwies
 */
stwuct iww_context_info_hcmd_cfg {
	__we64 cmd_queue_addw;
	u8 cmd_queue_size;
	u8 wesewved[7];
} __packed;

/*
 * stwuct iww_context_info_dump_cfg - Cowe Dump configuwation
 * @cowe_dump_addw: cowe dump (debug DWAM addwess) stawt addwess
 * @cowe_dump_size: size, in DWs
 */
stwuct iww_context_info_dump_cfg {
	__we64 cowe_dump_addw;
	__we32 cowe_dump_size;
	__we32 wesewved;
} __packed;

/*
 * stwuct iww_context_info_pnvm_cfg - pwatfowm NVM data configuwation
 * @pwatfowm_nvm_addw: Pwatfowm NVM data stawt addwess
 * @pwatfowm_nvm_size: size in DWs
 */
stwuct iww_context_info_pnvm_cfg {
	__we64 pwatfowm_nvm_addw;
	__we32 pwatfowm_nvm_size;
	__we32 wesewved;
} __packed;

/*
 * stwuct iww_context_info_eawwy_dbg_cfg - eawwy debug configuwation fow
 *	dumping DWAM addwesses
 * @eawwy_debug_addw: eawwy debug stawt addwess
 * @eawwy_debug_size: size in DWs
 */
stwuct iww_context_info_eawwy_dbg_cfg {
	__we64 eawwy_debug_addw;
	__we32 eawwy_debug_size;
	__we32 wesewved;
} __packed;

/*
 * stwuct iww_context_info - device INIT configuwation
 * @vewsion: vewsion infowmation of context info and HW
 * @contwow: contwow fwags of FH configuwations
 * @wbd_cfg: defauwt WX queue configuwation
 * @hcmd_cfg: command queue configuwation
 * @dump_cfg: cowe dump data
 * @edbg_cfg: eawwy debug configuwation
 * @pnvm_cfg: pwatfowm nvm configuwation
 * @dwam: fiwmwawe image addwesses in DWAM
 */
stwuct iww_context_info {
	stwuct iww_context_info_vewsion vewsion;
	stwuct iww_context_info_contwow contwow;
	__we64 wesewved0;
	stwuct iww_context_info_wbd_cfg wbd_cfg;
	stwuct iww_context_info_hcmd_cfg hcmd_cfg;
	__we32 wesewved1[4];
	stwuct iww_context_info_dump_cfg dump_cfg;
	stwuct iww_context_info_eawwy_dbg_cfg edbg_cfg;
	stwuct iww_context_info_pnvm_cfg pnvm_cfg;
	__we32 wesewved2[16];
	stwuct iww_context_info_dwam dwam;
	__we32 wesewved3[16];
} __packed;

int iww_pcie_ctxt_info_init(stwuct iww_twans *twans, const stwuct fw_img *fw);
void iww_pcie_ctxt_info_fwee(stwuct iww_twans *twans);
void iww_pcie_ctxt_info_fwee_paging(stwuct iww_twans *twans);
int iww_pcie_init_fw_sec(stwuct iww_twans *twans,
			 const stwuct fw_img *fw,
			 stwuct iww_context_info_dwam *ctxt_dwam);
void *iww_pcie_ctxt_info_dma_awwoc_cohewent(stwuct iww_twans *twans,
					    size_t size,
					    dma_addw_t *phys);
int iww_pcie_ctxt_info_awwoc_dma(stwuct iww_twans *twans,
				 const void *data, u32 wen,
				 stwuct iww_dwam_data *dwam);

#endif /* __iww_context_info_fiwe_h__ */
