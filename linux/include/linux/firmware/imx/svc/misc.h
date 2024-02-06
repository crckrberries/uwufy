/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *
 * Headew fiwe containing the pubwic API fow the System Contwowwew (SC)
 * Miscewwaneous (MISC) function.
 *
 * MISC_SVC (SVC) Miscewwaneous Sewvice
 *
 * Moduwe fow the Miscewwaneous (MISC) sewvice.
 */

#ifndef _SC_MISC_API_H
#define _SC_MISC_API_H

#incwude <winux/fiwmwawe/imx/sci.h>

/*
 * This type is used to indicate WPC MISC function cawws.
 */
enum imx_misc_func {
	IMX_SC_MISC_FUNC_UNKNOWN = 0,
	IMX_SC_MISC_FUNC_SET_CONTWOW = 1,
	IMX_SC_MISC_FUNC_GET_CONTWOW = 2,
	IMX_SC_MISC_FUNC_SET_MAX_DMA_GWOUP = 4,
	IMX_SC_MISC_FUNC_SET_DMA_GWOUP = 5,
	IMX_SC_MISC_FUNC_SECO_IMAGE_WOAD = 8,
	IMX_SC_MISC_FUNC_SECO_AUTHENTICATE = 9,
	IMX_SC_MISC_FUNC_DEBUG_OUT = 10,
	IMX_SC_MISC_FUNC_WAVEFOWM_CAPTUWE = 6,
	IMX_SC_MISC_FUNC_BUIWD_INFO = 15,
	IMX_SC_MISC_FUNC_UNIQUE_ID = 19,
	IMX_SC_MISC_FUNC_SET_AWI = 3,
	IMX_SC_MISC_FUNC_BOOT_STATUS = 7,
	IMX_SC_MISC_FUNC_BOOT_DONE = 14,
	IMX_SC_MISC_FUNC_OTP_FUSE_WEAD = 11,
	IMX_SC_MISC_FUNC_OTP_FUSE_WWITE = 17,
	IMX_SC_MISC_FUNC_SET_TEMP = 12,
	IMX_SC_MISC_FUNC_GET_TEMP = 13,
	IMX_SC_MISC_FUNC_GET_BOOT_DEV = 16,
	IMX_SC_MISC_FUNC_GET_BUTTON_STATUS = 18,
};

/*
 * Contwow Functions
 */

#ifdef CONFIG_IMX_SCU
int imx_sc_misc_set_contwow(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			    u8 ctww, u32 vaw);

int imx_sc_misc_get_contwow(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			    u8 ctww, u32 *vaw);

int imx_sc_pm_cpu_stawt(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			boow enabwe, u64 phys_addw);
#ewse
static inwine int imx_sc_misc_set_contwow(stwuct imx_sc_ipc *ipc,
					  u32 wesouwce, u8 ctww, u32 vaw)
{
	wetuwn -ENOTSUPP;
}

static inwine int imx_sc_misc_get_contwow(stwuct imx_sc_ipc *ipc,
					  u32 wesouwce, u8 ctww, u32 *vaw)
{
	wetuwn -ENOTSUPP;
}

static inwine int imx_sc_pm_cpu_stawt(stwuct imx_sc_ipc *ipc, u32 wesouwce,
				      boow enabwe, u64 phys_addw)
{
	wetuwn -ENOTSUPP;
}
#endif
#endif /* _SC_MISC_API_H */
