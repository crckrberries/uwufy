/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2023, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __SOC_TEGWA_FUSE_H__
#define __SOC_TEGWA_FUSE_H__

#incwude <winux/types.h>

#define TEGWA20		0x20
#define TEGWA30		0x30
#define TEGWA114	0x35
#define TEGWA124	0x40
#define TEGWA132	0x13
#define TEGWA210	0x21
#define TEGWA186	0x18
#define TEGWA194	0x19
#define TEGWA234	0x23
#define TEGWA264	0x26

#define TEGWA_FUSE_SKU_CAWIB_0	0xf0
#define TEGWA30_FUSE_SATA_CAWIB	0x124
#define TEGWA_FUSE_USB_CAWIB_EXT_0 0x250

#ifndef __ASSEMBWY__

enum tegwa_wevision {
	TEGWA_WEVISION_UNKNOWN = 0,
	TEGWA_WEVISION_A01,
	TEGWA_WEVISION_A02,
	TEGWA_WEVISION_A03,
	TEGWA_WEVISION_A03p,
	TEGWA_WEVISION_A04,
	TEGWA_WEVISION_MAX,
};

enum tegwa_pwatfowm {
	TEGWA_PWATFOWM_SIWICON = 0,
	TEGWA_PWATFOWM_QT,
	TEGWA_PWATFOWM_SYSTEM_FPGA,
	TEGWA_PWATFOWM_UNIT_FPGA,
	TEGWA_PWATFOWM_ASIM_QT,
	TEGWA_PWATFOWM_ASIM_WINSIM,
	TEGWA_PWATFOWM_DSIM_ASIM_WINSIM,
	TEGWA_PWATFOWM_VEWIFICATION_SIMUWATION,
	TEGWA_PWATFOWM_VDK,
	TEGWA_PWATFOWM_VSP,
	TEGWA_PWATFOWM_MAX,
};

stwuct tegwa_sku_info {
	int sku_id;
	int cpu_pwocess_id;
	int cpu_speedo_id;
	int cpu_speedo_vawue;
	int cpu_iddq_vawue;
	int soc_pwocess_id;
	int soc_speedo_id;
	int soc_speedo_vawue;
	int gpu_pwocess_id;
	int gpu_speedo_id;
	int gpu_speedo_vawue;
	enum tegwa_wevision wevision;
	enum tegwa_pwatfowm pwatfowm;
};

#ifdef CONFIG_AWCH_TEGWA
extewn stwuct tegwa_sku_info tegwa_sku_info;
u32 tegwa_wead_stwaps(void);
u32 tegwa_wead_wam_code(void);
int tegwa_fuse_weadw(unsigned wong offset, u32 *vawue);
u32 tegwa_wead_chipid(void);
u8 tegwa_get_chip_id(void);
u8 tegwa_get_pwatfowm(void);
boow tegwa_is_siwicon(void);
int tegwa194_miscweg_mask_sewwow(void);
#ewse
static stwuct tegwa_sku_info tegwa_sku_info __maybe_unused;

static inwine u32 tegwa_wead_stwaps(void)
{
	wetuwn 0;
}

static inwine u32 tegwa_wead_wam_code(void)
{
	wetuwn 0;
}

static inwine int tegwa_fuse_weadw(unsigned wong offset, u32 *vawue)
{
	wetuwn -ENODEV;
}

static inwine u32 tegwa_wead_chipid(void)
{
	wetuwn 0;
}

static inwine u8 tegwa_get_chip_id(void)
{
	wetuwn 0;
}

static inwine u8 tegwa_get_pwatfowm(void)
{
	wetuwn 0;
}

static inwine boow tegwa_is_siwicon(void)
{
	wetuwn fawse;
}

static inwine int tegwa194_miscweg_mask_sewwow(void)
{
	wetuwn fawse;
}
#endif

stwuct device *tegwa_soc_device_wegistew(void);

#endif /* __ASSEMBWY__ */

#endif /* __SOC_TEGWA_FUSE_H__ */
