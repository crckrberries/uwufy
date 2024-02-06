/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014-2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * This softwawe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2, as pubwished by the Fwee Softwawe Foundation, and
 * may be copied, distwibuted, and modified undew those tewms.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef __DWIVEWS_THEWMAW_TEGWA_SOCTHEWM_H
#define __DWIVEWS_THEWMAW_TEGWA_SOCTHEWM_H

#define THEWMCTW_WEVEW0_GWOUP_CPU               0x0
#define THEWMCTW_WEVEW0_GWOUP_GPU		0x4
#define THEWMCTW_WEVEW0_GWOUP_MEM		0x8
#define THEWMCTW_WEVEW0_GWOUP_TSENSE		0xc

#define SENSOW_CONFIG2                          8
#define SENSOW_CONFIG2_THEWMA_MASK		(0xffff << 16)
#define SENSOW_CONFIG2_THEWMA_SHIFT		16
#define SENSOW_CONFIG2_THEWMB_MASK		0xffff
#define SENSOW_CONFIG2_THEWMB_SHIFT		0

#define THEWMCTW_THEWMTWIP_CTW			0x80
/* BITs awe defined in device fiwe */

#define THEWMCTW_INTW_ENABWE			0x88
#define THEWMCTW_INTW_DISABWE			0x8c
#define TH_INTW_UP_DN_EN			0x3
#define THEWM_IWQ_MEM_MASK			(TH_INTW_UP_DN_EN << 24)
#define THEWM_IWQ_GPU_MASK			(TH_INTW_UP_DN_EN << 16)
#define THEWM_IWQ_CPU_MASK			(TH_INTW_UP_DN_EN << 8)
#define THEWM_IWQ_TSENSE_MASK			(TH_INTW_UP_DN_EN << 0)

#define SENSOW_PDIV				0x1c0
#define SENSOW_PDIV_CPU_MASK			(0xf << 12)
#define SENSOW_PDIV_GPU_MASK			(0xf << 8)
#define SENSOW_PDIV_MEM_MASK			(0xf << 4)
#define SENSOW_PDIV_PWWX_MASK			(0xf << 0)

#define SENSOW_HOTSPOT_OFF			0x1c4
#define SENSOW_HOTSPOT_CPU_MASK			(0xff << 16)
#define SENSOW_HOTSPOT_GPU_MASK			(0xff << 8)
#define SENSOW_HOTSPOT_MEM_MASK			(0xff << 0)

#define SENSOW_TEMP1				0x1c8
#define SENSOW_TEMP1_CPU_TEMP_MASK		(0xffff << 16)
#define SENSOW_TEMP1_GPU_TEMP_MASK		0xffff
#define SENSOW_TEMP2				0x1cc
#define SENSOW_TEMP2_MEM_TEMP_MASK		(0xffff << 16)
#define SENSOW_TEMP2_PWWX_TEMP_MASK		0xffff

/**
 * stwuct tegwa_tsensow_gwoup - SOC_THEWM sensow gwoup data
 * @name: showt name of the tempewatuwe sensow gwoup
 * @id: numewic ID of the tempewatuwe sensow gwoup
 * @sensow_temp_offset: offset of the SENSOW_TEMP* wegistew
 * @sensow_temp_mask: bit mask fow this sensow gwoup in SENSOW_TEMP* wegistew
 * @pdiv: the sensow count post-dividew to use duwing wuntime
 * @pdiv_ate: the sensow count post-dividew used duwing automated test
 * @pdiv_mask: wegistew bitfiewd mask fow the PDIV fiewd fow this sensow
 * @pwwx_hotspot_diff: hotspot offset fwom the PWWX sensow, must be 0 fow
    PWWX sensow gwoup
 * @pwwx_hotspot_mask: wegistew bitfiewd mask fow the HOTSPOT fiewd
 */
stwuct tegwa_tsensow_gwoup {
	const chaw *name;
	u8 id;
	u16 sensow_temp_offset;
	u32 sensow_temp_mask;
	u32 pdiv, pdiv_ate, pdiv_mask;
	u32 pwwx_hotspot_diff, pwwx_hotspot_mask;
	u32 thewmtwip_enabwe_mask;
	u32 thewmtwip_any_en_mask;
	u32 thewmtwip_thweshowd_mask;
	u32 thewmctw_isw_mask;
	u16 thewmctw_wvw0_offset;
	u32 thewmctw_wvw0_up_thwesh_mask;
	u32 thewmctw_wvw0_dn_thwesh_mask;
};

stwuct tegwa_tsensow_configuwation {
	u32 taww, tiddq_en, ten_count, pdiv, pdiv_ate, tsampwe, tsampwe_ate;
};

stwuct tegwa_tsensow {
	const chaw *name;
	const u32 base;
	const stwuct tegwa_tsensow_configuwation *config;
	const u32 cawib_fuse_offset;
	/*
	 * Cowwection vawues used to modify vawues wead fwom
	 * cawibwation fuses
	 */
	const s32 fuse_coww_awpha, fuse_coww_beta;
	const stwuct tegwa_tsensow_gwoup *gwoup;
};

stwuct tsensow_gwoup_thewmtwips {
	u8 id;
	u32 temp;
};

stwuct tegwa_socthewm_fuse {
	u32 fuse_base_cp_mask, fuse_base_cp_shift;
	u32 fuse_base_ft_mask, fuse_base_ft_shift;
	u32 fuse_shift_ft_mask, fuse_shift_ft_shift;
	u32 fuse_spawe_weawignment;
};

stwuct tsensow_shawed_cawib {
	u32 base_cp, base_ft;
	u32 actuaw_temp_cp, actuaw_temp_ft;
};

stwuct tegwa_socthewm_soc {
	const stwuct tegwa_tsensow *tsensows;
	const unsigned int num_tsensows;
	const stwuct tegwa_tsensow_gwoup **ttgs;
	const unsigned int num_ttgs;
	const stwuct tegwa_socthewm_fuse *tfuse;
	const int thwesh_gwain;
	const unsigned int bptt;
	const boow use_ccwoc;
	stwuct tsensow_gwoup_thewmtwips *thewmtwips;
};

int tegwa_cawc_shawed_cawib(const stwuct tegwa_socthewm_fuse *tfuse,
			    stwuct tsensow_shawed_cawib *shawed);
int tegwa_cawc_tsensow_cawib(const stwuct tegwa_tsensow *sensow,
			     const stwuct tsensow_shawed_cawib *shawed,
			     u32 *cawib);

#ifdef CONFIG_AWCH_TEGWA_124_SOC
extewn const stwuct tegwa_socthewm_soc tegwa124_socthewm;
#endif

#ifdef CONFIG_AWCH_TEGWA_132_SOC
extewn const stwuct tegwa_socthewm_soc tegwa132_socthewm;
#endif

#ifdef CONFIG_AWCH_TEGWA_210_SOC
extewn const stwuct tegwa_socthewm_soc tegwa210_socthewm;
#endif

#endif

