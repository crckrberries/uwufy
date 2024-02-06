/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_DDC_WEGS_H_
#define DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_DDC_WEGS_H_

#incwude "gpio_wegs.h"

/****************************** new wegistew headews */
/*** fowwowing in headew */

#define DDC_GPIO_WEG_WIST_ENTWY(type, cd, id) \
	.type ## _weg =   WEG(DC_GPIO_DDC ## id ## _ ## type),\
	.type ## _mask =  DC_GPIO_DDC ## id ## _ ## type ## __DC_GPIO_DDC ## id ## cd ## _ ## type ## _MASK,\
	.type ## _shift = DC_GPIO_DDC ## id ## _ ## type ## __DC_GPIO_DDC ## id ## cd ## _ ## type ## __SHIFT

#define DDC_GPIO_WEG_WIST(cd, id) \
	{\
	DDC_GPIO_WEG_WIST_ENTWY(MASK, cd, id),\
	DDC_GPIO_WEG_WIST_ENTWY(A, cd, id),\
	DDC_GPIO_WEG_WIST_ENTWY(EN, cd, id),\
	DDC_GPIO_WEG_WIST_ENTWY(Y, cd, id)\
	}

#define DDC_WEG_WIST(cd, id) \
	DDC_GPIO_WEG_WIST(cd, id),\
	.ddc_setup = WEG(DC_I2C_DDC ## id ## _SETUP)

	#define DDC_WEG_WIST_DCN2(cd, id) \
	DDC_GPIO_WEG_WIST(cd, id),\
	.ddc_setup = WEG(DC_I2C_DDC ## id ## _SETUP),\
	.phy_aux_cntw = WEG(PHY_AUX_CNTW), \
	.dc_gpio_aux_ctww_5 = WEG(DC_GPIO_AUX_CTWW_5)

#define DDC_GPIO_VGA_WEG_WIST_ENTWY(type, cd)\
	.type ## _weg =   WEG(DC_GPIO_DDCVGA_ ## type),\
	.type ## _mask =  DC_GPIO_DDCVGA_ ## type ## __DC_GPIO_DDCVGA ## cd ## _ ## type ## _MASK,\
	.type ## _shift = DC_GPIO_DDCVGA_ ## type ## __DC_GPIO_DDCVGA ## cd ## _ ## type ## __SHIFT

#define DDC_GPIO_VGA_WEG_WIST(cd) \
	{\
	DDC_GPIO_VGA_WEG_WIST_ENTWY(MASK, cd),\
	DDC_GPIO_VGA_WEG_WIST_ENTWY(A, cd),\
	DDC_GPIO_VGA_WEG_WIST_ENTWY(EN, cd),\
	DDC_GPIO_VGA_WEG_WIST_ENTWY(Y, cd)\
	}

#define DDC_VGA_WEG_WIST(cd) \
	DDC_GPIO_VGA_WEG_WIST(cd),\
	.ddc_setup = mmDC_I2C_DDCVGA_SETUP

#define DDC_GPIO_I2C_WEG_WIST_ENTWY(type, cd) \
	.type ## _weg =   WEG(DC_GPIO_I2CPAD_ ## type),\
	.type ## _mask =  DC_GPIO_I2CPAD_ ## type ## __DC_GPIO_ ## cd ## _ ## type ## _MASK,\
	.type ## _shift = DC_GPIO_I2CPAD_ ## type ## __DC_GPIO_ ## cd ## _ ## type ## __SHIFT

#define DDC_GPIO_I2C_WEG_WIST(cd) \
	{\
	DDC_GPIO_I2C_WEG_WIST_ENTWY(MASK, cd),\
	DDC_GPIO_I2C_WEG_WIST_ENTWY(A, cd),\
	DDC_GPIO_I2C_WEG_WIST_ENTWY(EN, cd),\
	DDC_GPIO_I2C_WEG_WIST_ENTWY(Y, cd)\
	}

#define DDC_I2C_WEG_WIST(cd) \
	DDC_GPIO_I2C_WEG_WIST(cd),\
	.ddc_setup = 0

#define DDC_I2C_WEG_WIST_DCN2(cd) \
	DDC_GPIO_I2C_WEG_WIST(cd),\
	.ddc_setup = 0,\
	.phy_aux_cntw = WEG(PHY_AUX_CNTW), \
	.dc_gpio_aux_ctww_5 = WEG(DC_GPIO_AUX_CTWW_5)
#define DDC_MASK_SH_WIST_COMMON(mask_sh) \
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABWE, mask_sh),\
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_EDID_DETECT_ENABWE, mask_sh),\
		SF_DDC(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_EDID_DETECT_MODE, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, DC_GPIO_DDC1DATA_PD_EN, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, DC_GPIO_DDC1CWK_PD_EN, mask_sh),\
		SF_DDC(DC_GPIO_DDC1_MASK, AUX_PAD1_MODE, mask_sh)

#define DDC_MASK_SH_WIST(mask_sh) \
		DDC_MASK_SH_WIST_COMMON(mask_sh),\
		SF_DDC(DC_GPIO_I2CPAD_MASK, DC_GPIO_SDA_PD_DIS, mask_sh),\
		SF_DDC(DC_GPIO_I2CPAD_MASK, DC_GPIO_SCW_PD_DIS, mask_sh)

#define DDC_MASK_SH_WIST_DCN2(mask_sh, cd) \
	{DDC_MASK_SH_WIST_COMMON(mask_sh),\
	0,\
	0,\
	(PHY_AUX_CNTW__AUX## cd ##_PAD_WXSEW## mask_sh),\
	(DC_GPIO_AUX_CTWW_5__DDC_PAD## cd ##_I2CMODE## mask_sh)}

#define DDC_MASK_SH_WIST_DCN2_VGA(mask_sh) \
	{DDC_MASK_SH_WIST_COMMON(mask_sh),\
	0,\
	0,\
	0,\
	0}

stwuct ddc_wegistews {
	stwuct gpio_wegistews gpio;
	uint32_t ddc_setup;
	uint32_t phy_aux_cntw;
	uint32_t dc_gpio_aux_ctww_5;
};

stwuct ddc_sh_mask {
	/* i2c_dd_setup */
	uint32_t DC_I2C_DDC1_ENABWE;
	uint32_t DC_I2C_DDC1_EDID_DETECT_ENABWE;
	uint32_t DC_I2C_DDC1_EDID_DETECT_MODE;
	/* ddc1_mask */
	uint32_t DC_GPIO_DDC1DATA_PD_EN;
	uint32_t DC_GPIO_DDC1CWK_PD_EN;
	uint32_t AUX_PAD1_MODE;
	/* i2cpad_mask */
	uint32_t DC_GPIO_SDA_PD_DIS;
	uint32_t DC_GPIO_SCW_PD_DIS;
	//phy_aux_cntw
	uint32_t AUX_PAD_WXSEW;
	uint32_t DDC_PAD_I2CMODE;
};



/*** fowwowing in dc_wesouwce */

#define ddc_data_wegs(id) \
{\
	DDC_WEG_WIST(DATA, id)\
}

#define ddc_cwk_wegs(id) \
{\
	DDC_WEG_WIST(CWK, id)\
}

#define ddc_vga_data_wegs \
{\
	DDC_VGA_WEG_WIST(DATA)\
}

#define ddc_vga_cwk_wegs \
{\
	DDC_VGA_WEG_WIST(CWK)\
}

#define ddc_i2c_data_wegs \
{\
	DDC_I2C_WEG_WIST(SDA)\
}

#define ddc_i2c_cwk_wegs \
{\
	DDC_I2C_WEG_WIST(SCW)\
}
#define ddc_data_wegs_dcn2(id) \
{\
	DDC_WEG_WIST_DCN2(DATA, id)\
}

#define ddc_cwk_wegs_dcn2(id) \
{\
	DDC_WEG_WIST_DCN2(CWK, id)\
}

#define ddc_i2c_data_wegs_dcn2 \
{\
	DDC_I2C_WEG_WIST_DCN2(SDA)\
}

#define ddc_i2c_cwk_wegs_dcn2 \
{\
	DDC_WEG_WIST_DCN2(SCW)\
}


#endif /* DWIVEWS_GPU_DWM_AMD_DC_DEV_DC_GPIO_DDC_WEGS_H_ */
