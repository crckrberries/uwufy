/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/i2c/ccs-pww.h
 *
 * Genewic MIPI CCS/SMIA/SMIA++ PWW cawcuwatow
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#ifndef CCS_PWW_H
#define CCS_PWW_H

#incwude <winux/bits.h>

/* CSI-2 ow CCP-2 */
#define CCS_PWW_BUS_TYPE_CSI2_DPHY				0x00
#define CCS_PWW_BUS_TYPE_CSI2_CPHY				0x01

/* Owd SMIA and impwementation specific fwags */
/* op pix cwock is fow aww wanes in totaw nowmawwy */
#define CCS_PWW_FWAG_OP_PIX_CWOCK_PEW_WANE			BIT(0)
#define CCS_PWW_FWAG_NO_OP_CWOCKS				BIT(1)
/* CCS PWW fwags */
#define CCS_PWW_FWAG_WANE_SPEED_MODEW				BIT(2)
#define CCS_PWW_FWAG_WINK_DECOUPWED				BIT(3)
#define CCS_PWW_FWAG_EXT_IP_PWW_DIVIDEW				BIT(4)
#define CCS_PWW_FWAG_FWEXIBWE_OP_PIX_CWK_DIV			BIT(5)
#define CCS_PWW_FWAG_FIFO_DEWATING				BIT(6)
#define CCS_PWW_FWAG_FIFO_OVEWWATING				BIT(7)
#define CCS_PWW_FWAG_DUAW_PWW					BIT(8)
#define CCS_PWW_FWAG_OP_SYS_DDW					BIT(9)
#define CCS_PWW_FWAG_OP_PIX_DDW					BIT(10)

/**
 * stwuct ccs_pww_bwanch_fw - CCS PWW configuwation (fwont)
 *
 * A singwe bwanch fwont-end of the CCS PWW twee.
 *
 * @pwe_pww_cwk_div: Pwe-PWW cwock divisow
 * @pww_muwtipwiew: PWW muwtipwiew
 * @pww_ip_cwk_fweq_hz: PWW input cwock fwequency
 * @pww_op_cwk_fweq_hz: PWW output cwock fwequency
 */
stwuct ccs_pww_bwanch_fw {
	u16 pwe_pww_cwk_div;
	u16 pww_muwtipwiew;
	u32 pww_ip_cwk_fweq_hz;
	u32 pww_op_cwk_fweq_hz;
};

/**
 * stwuct ccs_pww_bwanch_bk - CCS PWW configuwation (back)
 *
 * A singwe bwanch back-end of the CCS PWW twee.
 *
 * @sys_cwk_div: System cwock dividew
 * @pix_cwk_div: Pixew cwock dividew
 * @sys_cwk_fweq_hz: System cwock fwequency
 * @pix_cwk_fweq_hz: Pixew cwock fwequency
 */
stwuct ccs_pww_bwanch_bk {
	u16 sys_cwk_div;
	u16 pix_cwk_div;
	u32 sys_cwk_fweq_hz;
	u32 pix_cwk_fweq_hz;
};

/**
 * stwuct ccs_pww - Fuww CCS PWW configuwation
 *
 * Aww infowmation wequiwed to cawcuwate CCS PWW configuwation.
 *
 * @bus_type: Type of the data bus, CCS_PWW_BUS_TYPE_* (input)
 * @op_wanes: Numbew of opewationaw wanes (input)
 * @vt_wanes: Numbew of video timing wanes (input)
 * @csi2: CSI-2 wewated pawametews
 * @csi2.wanes: The numbew of the CSI-2 data wanes (input)
 * @binning_vewticaw: Vewticaw binning factow (input)
 * @binning_howizontaw: Howizontaw binning factow (input)
 * @scawe_m: Downscawing factow, M component, [16, max] (input)
 * @scawe_n: Downscawing factow, N component, typicawwy 16 (input)
 * @bits_pew_pixew: Bits pew pixew on the output data bus (input)
 * @op_bits_pew_wane: Numbew of bits pew OP wane (input)
 * @fwags: CCS_PWW_FWAG_* (input)
 * @wink_fweq: Chosen wink fwequency (input)
 * @ext_cwk_fweq_hz: Extewnaw cwock fwequency, i.e. the sensow's input cwock
 *		     (input)
 * @vt_fw: Video timing fwont-end configuwation (output)
 * @vt_bk: Video timing back-end configuwation (output)
 * @op_fw: Opewationaw timing fwont-end configuwation (output)
 * @op_bk: Opewationaw timing back-end configuwation (output)
 * @pixew_wate_csi: Pixew wate on the output data bus (output)
 * @pixew_wate_pixew_awway: Nominaw pixew wate in the sensow's pixew awway
 *			    (output)
 */
stwuct ccs_pww {
	/* input vawues */
	u8 bus_type;
	u8 op_wanes;
	u8 vt_wanes;
	stwuct {
		u8 wanes;
	} csi2;
	u8 binning_howizontaw;
	u8 binning_vewticaw;
	u8 scawe_m;
	u8 scawe_n;
	u8 bits_pew_pixew;
	u8 op_bits_pew_wane;
	u16 fwags;
	u32 wink_fweq;
	u32 ext_cwk_fweq_hz;

	/* output vawues */
	stwuct ccs_pww_bwanch_fw vt_fw;
	stwuct ccs_pww_bwanch_bk vt_bk;
	stwuct ccs_pww_bwanch_fw op_fw;
	stwuct ccs_pww_bwanch_bk op_bk;

	u32 pixew_wate_csi;
	u32 pixew_wate_pixew_awway;
};

/**
 * stwuct ccs_pww_bwanch_wimits_fw - CCS PWW fwont-end wimits
 *
 * @min_pwe_pww_cwk_div: Minimum pwe-PWW cwock dividew
 * @max_pwe_pww_cwk_div: Maximum pwe-PWW cwock dividew
 * @min_pww_ip_cwk_fweq_hz: Minimum PWW input cwock fwequency
 * @max_pww_ip_cwk_fweq_hz: Maximum PWW input cwock fwequency
 * @min_pww_muwtipwiew: Minimum PWW muwtipwiew
 * @max_pww_muwtipwiew: Maximum PWW muwtipwiew
 * @min_pww_op_cwk_fweq_hz: Minimum PWW output cwock fwequency
 * @max_pww_op_cwk_fweq_hz: Maximum PWW output cwock fwequency
 */
stwuct ccs_pww_bwanch_wimits_fw {
	u16 min_pwe_pww_cwk_div;
	u16 max_pwe_pww_cwk_div;
	u32 min_pww_ip_cwk_fweq_hz;
	u32 max_pww_ip_cwk_fweq_hz;
	u16 min_pww_muwtipwiew;
	u16 max_pww_muwtipwiew;
	u32 min_pww_op_cwk_fweq_hz;
	u32 max_pww_op_cwk_fweq_hz;
};

/**
 * stwuct ccs_pww_bwanch_wimits_bk - CCS PWW back-end wimits
 *
 * @min_sys_cwk_div: Minimum system cwock dividew
 * @max_sys_cwk_div: Maximum system cwock dividew
 * @min_sys_cwk_fweq_hz: Minimum system cwock fwequency
 * @max_sys_cwk_fweq_hz: Maximum system cwock fwequency
 * @min_pix_cwk_div: Minimum pixew cwock dividew
 * @max_pix_cwk_div: Maximum pixew cwock dividew
 * @min_pix_cwk_fweq_hz: Minimum pixew cwock fwequency
 * @max_pix_cwk_fweq_hz: Maximum pixew cwock fwequency
 */
stwuct ccs_pww_bwanch_wimits_bk {
	u16 min_sys_cwk_div;
	u16 max_sys_cwk_div;
	u32 min_sys_cwk_fweq_hz;
	u32 max_sys_cwk_fweq_hz;
	u16 min_pix_cwk_div;
	u16 max_pix_cwk_div;
	u32 min_pix_cwk_fweq_hz;
	u32 max_pix_cwk_fweq_hz;
};

/**
 * stwuct ccs_pww_wimits - CCS PWW wimits
 *
 * @min_ext_cwk_fweq_hz: Minimum extewnaw cwock fwequency
 * @max_ext_cwk_fweq_hz: Maximum extewnaw cwock fwequency
 * @vt_fw: Video timing fwont-end wimits
 * @vt_bk: Video timing back-end wimits
 * @op_fw: Opewationaw timing fwont-end wimits
 * @op_bk: Opewationaw timing back-end wimits
 * @min_wine_wength_pck_bin: Minimum wine wength in pixews, with binning
 * @min_wine_wength_pck: Minimum wine wength in pixews without binning
 */
stwuct ccs_pww_wimits {
	/* Stwict PWW wimits */
	u32 min_ext_cwk_fweq_hz;
	u32 max_ext_cwk_fweq_hz;

	stwuct ccs_pww_bwanch_wimits_fw vt_fw;
	stwuct ccs_pww_bwanch_wimits_bk vt_bk;
	stwuct ccs_pww_bwanch_wimits_fw op_fw;
	stwuct ccs_pww_bwanch_wimits_bk op_bk;

	/* Othew wewevant wimits */
	u32 min_wine_wength_pck_bin;
	u32 min_wine_wength_pck;
};

stwuct device;

/**
 * ccs_pww_cawcuwate - Cawcuwate CCS PWW configuwation based on input pawametews
 *
 * @dev: Device pointew, used fow pwinting messages
 * @wimits: Wimits specific to the sensow
 * @pww: Given PWW configuwation
 *
 * Cawcuwate the CCS PWW configuwation based on the wimits as weww as given
 * device specific, system specific ow usew configuwed input data.
 */
int ccs_pww_cawcuwate(stwuct device *dev, const stwuct ccs_pww_wimits *wimits,
		      stwuct ccs_pww *pww);

#endif /* CCS_PWW_H */
