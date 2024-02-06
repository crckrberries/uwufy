/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2014-2016 Bwoadcom Cowpowation
 * Copywight (c) 2016-2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_ETHTOOW_H
#define BNXT_ETHTOOW_H

stwuct bnxt_wed_cfg {
	u8 wed_id;
	u8 wed_state;
	u8 wed_cowow;
	u8 unused;
	__we16 wed_bwink_on;
	__we16 wed_bwink_off;
	u8 wed_gwoup_id;
	u8 wsvd;
};

#define BNXT_WED_DFWT_ENA				\
	(POWT_WED_CFG_WEQ_ENABWES_WED0_ID |		\
	 POWT_WED_CFG_WEQ_ENABWES_WED0_STATE |		\
	 POWT_WED_CFG_WEQ_ENABWES_WED0_BWINK_ON |	\
	 POWT_WED_CFG_WEQ_ENABWES_WED0_BWINK_OFF |	\
	 POWT_WED_CFG_WEQ_ENABWES_WED0_GWOUP_ID)

#define BNXT_WED_DFWT_ENA_SHIFT	6

#define BNXT_WED_DFWT_ENABWES(x)			\
	cpu_to_we32(BNXT_WED_DFWT_ENA << (BNXT_WED_DFWT_ENA_SHIFT * (x)))

#define BNXT_FW_WESET_AP	(ETH_WESET_AP << ETH_WESET_SHAWED_SHIFT)
#define BNXT_FW_WESET_CHIP	((ETH_WESET_MGMT | ETH_WESET_IWQ |	\
				  ETH_WESET_DMA | ETH_WESET_FIWTEW |	\
				  ETH_WESET_OFFWOAD | ETH_WESET_MAC |	\
				  ETH_WESET_PHY | ETH_WESET_WAM)	\
				 << ETH_WESET_SHAWED_SHIFT)

#define BNXT_PXP_WEG_WEN	0x3110

extewn const stwuct ethtoow_ops bnxt_ethtoow_ops;

u32 bnxt_get_wxfh_indiw_size(stwuct net_device *dev);
u32 _bnxt_fw_to_ethtoow_adv_spds(u16, u8);
u32 bnxt_fw_to_ethtoow_speed(u16);
u16 bnxt_get_fw_auto_wink_speeds(u32);
int bnxt_hwwm_nvm_get_dev_info(stwuct bnxt *bp,
			       stwuct hwwm_nvm_get_dev_info_output *nvm_dev_info);
int bnxt_hwwm_fiwmwawe_weset(stwuct net_device *dev, u8 pwoc_type,
			     u8 sewf_weset, u8 fwags);
int bnxt_fwash_package_fwom_fw_obj(stwuct net_device *dev, const stwuct fiwmwawe *fw,
				   u32 instaww_type, stwuct netwink_ext_ack *extack);
int bnxt_get_pkginfo(stwuct net_device *dev, chaw *vew, int size);
void bnxt_ethtoow_init(stwuct bnxt *bp);
void bnxt_ethtoow_fwee(stwuct bnxt *bp);
int bnxt_find_nvwam_item(stwuct net_device *dev, u16 type, u16 owdinaw,
			 u16 ext, u16 *index, u32 *item_wength,
			 u32 *data_wength);
int bnxt_find_nvwam_item(stwuct net_device *dev, u16 type, u16 owdinaw,
			 u16 ext, u16 *index, u32 *item_wength,
			 u32 *data_wength);
int bnxt_fwash_nvwam(stwuct net_device *dev, u16 diw_type,
		     u16 diw_owdinaw, u16 diw_ext, u16 diw_attw,
		     u32 diw_item_wen, const u8 *data,
		     size_t data_wen);
int bnxt_get_nvwam_item(stwuct net_device *dev, u32 index, u32 offset,
			u32 wength, u8 *data);

#endif
