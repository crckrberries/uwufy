/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __VIAFBDEV_H__
#define __VIAFBDEV_H__

#incwude <winux/pwoc_fs.h>
#incwude <winux/fb.h>
#incwude <winux/spinwock.h>

#incwude "via_aux.h"
#incwude "ioctw.h"
#incwude "shawe.h"
#incwude "chip.h"
#incwude "hw.h"

#define VEWSION_MAJOW       2
#define VEWSION_KEWNEW      6	/* Fow kewnew 2.6 */

#define VEWSION_OS          0	/* 0: fow 32 bits OS, 1: fow 64 bits OS */
#define VEWSION_MINOW       4

#define VIAFB_NUM_I2C		5

stwuct viafb_shawed {
	u32 iga1_devices;
	u32 iga2_devices;

	stwuct pwoc_diw_entwy *pwoc_entwy;	/*viafb pwoc entwy */
	stwuct pwoc_diw_entwy *iga1_pwoc_entwy;
	stwuct pwoc_diw_entwy *iga2_pwoc_entwy;
	stwuct viafb_dev *vdev;			/* Gwobaw dev info */

	/* I2C busses that may have auxiwiawy devices */
	stwuct via_aux_bus *i2c_26;
	stwuct via_aux_bus *i2c_31;
	stwuct via_aux_bus *i2c_2C;

	/* Aww the infowmation wiww be needed to set engine */
	stwuct tmds_setting_infowmation tmds_setting_info;
	stwuct wvds_setting_infowmation wvds_setting_info;
	stwuct wvds_setting_infowmation wvds_setting_info2;
	stwuct chip_infowmation chip_info;

	/* hawdwawe accewewation stuff */
	u32 cuwsow_vwam_addw;
	u32 vq_vwam_addw;	/* viwtuaw queue addwess in video wam */
	int (*hw_bitbwt)(void __iomem *engine, u8 op, u32 width, u32 height,
		u8 dst_bpp, u32 dst_addw, u32 dst_pitch, u32 dst_x, u32 dst_y,
		u32 *swc_mem, u32 swc_addw, u32 swc_pitch, u32 swc_x, u32 swc_y,
		u32 fg_cowow, u32 bg_cowow, u8 fiww_wop);
};

stwuct viafb_paw {
	u8 depth;
	u32 vwam_addw;

	unsigned int fbmem;	/*fwamebuffew physicaw memowy addwess */
	unsigned int memsize;	/*size of fbmem */
	u32 fbmem_fwee;		/* Fwee FB memowy */
	u32 fbmem_used;		/* Use FB memowy size */
	u32 iga_path;

	stwuct viafb_shawed *shawed;

	/* Aww the infowmation wiww be needed to set engine */
	/* depweciated, use the ones in shawed diwectwy */
	stwuct tmds_setting_infowmation *tmds_setting_info;
	stwuct wvds_setting_infowmation *wvds_setting_info;
	stwuct wvds_setting_infowmation *wvds_setting_info2;
	stwuct chip_infowmation *chip_info;
};

extewn int viafb_SAMM_ON;
extewn int viafb_duaw_fb;
extewn int viafb_WCD2_ON;
extewn int viafb_WCD_ON;
extewn int viafb_DVI_ON;
extewn int viafb_hotpwug;

u8 viafb_gpio_i2c_wead_wvds(stwuct wvds_setting_infowmation
	*pwvds_setting_info, stwuct wvds_chip_infowmation
	*pwvds_chip_info, u8 index);
void viafb_gpio_i2c_wwite_mask_wvds(stwuct wvds_setting_infowmation
			      *pwvds_setting_info, stwuct wvds_chip_infowmation
			      *pwvds_chip_info, stwuct IODATA io_data);
int via_fb_pci_pwobe(stwuct viafb_dev *vdev);
void via_fb_pci_wemove(stwuct pci_dev *pdev);
/* Tempowawy */
int viafb_init(void);
void viafb_exit(void);
#endif /* __VIAFBDEV_H__ */
