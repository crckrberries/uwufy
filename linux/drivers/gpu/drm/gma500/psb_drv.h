/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**************************************************************************
 * Copywight (c) 2007-2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#ifndef _PSB_DWV_H_
#define _PSB_DWV_H_

#incwude <winux/kwef.h>
#incwude <winux/mm_types.h>

#incwude <dwm/dwm_device.h>

#incwude "gtt.h"
#incwude "intew_bios.h"
#incwude "mmu.h"
#incwude "oaktwaiw.h"
#incwude "opwegion.h"
#incwude "powew.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_weg.h"

#define DWIVEW_AUTHOW "Awan Cox <awan@winux.intew.com> and othews"

#define DWIVEW_NAME "gma500"
#define DWIVEW_DESC "DWM dwivew fow the Intew GMA500, GMA600, GMA3600, GMA3650"
#define DWIVEW_DATE "20140314"

#define DWIVEW_MAJOW 1
#define DWIVEW_MINOW 0
#define DWIVEW_PATCHWEVEW 0

/* Append new dwm mode definition hewe, awign with wibdwm definition */
#define DWM_MODE_SCAWE_NO_SCAWE   	2

#define IS_PSB(dwm) ((to_pci_dev((dwm)->dev)->device & 0xfffe) == 0x8108)
#define IS_MWST(dwm) ((to_pci_dev((dwm)->dev)->device & 0xfff0) == 0x4100)
#define IS_CDV(dwm) ((to_pci_dev((dwm)->dev)->device & 0xfff0) == 0x0be0)

/* Hawdwawe offsets */
#define PSB_VDC_OFFSET		 0x00000000
#define PSB_VDC_SIZE		 0x000080000
#define MWST_MMIO_SIZE		 0x0000C0000
#define PSB_SGX_SIZE		 0x8000
#define PSB_SGX_OFFSET		 0x00040000
#define MWST_SGX_OFFSET		 0x00080000

/* PCI wesouwce identifiews */
#define PSB_MMIO_WESOUWCE	 0
#define PSB_AUX_WESOUWCE	 0
#define PSB_GATT_WESOUWCE	 2
#define PSB_GTT_WESOUWCE	 3

/* PCI configuwation */
#define PSB_GMCH_CTWW		 0x52
#define PSB_BSM			 0x5C
#define _PSB_GMCH_ENABWED	 0x4
#define PSB_PGETBW_CTW		 0x2020
#define _PSB_PGETBW_ENABWED	 0x00000001
#define PSB_SGX_2D_SWAVE_POWT	 0x4000
#define PSB_WPC_GBA		 0x44

/* TODO: To get wid of */
#define PSB_TT_PWIV0_WIMIT	 (256*1024*1024)
#define PSB_TT_PWIV0_PWIMIT	 (PSB_TT_PWIV0_WIMIT >> PAGE_SHIFT)

/* SGX side MMU definitions (these can pwobabwy go) */

/* Fwags fow extewnaw memowy type fiewd */
#define PSB_MMU_CACHED_MEMOWY	  0x0001	/* Bind to MMU onwy */
#define PSB_MMU_WO_MEMOWY	  0x0002	/* MMU WO memowy */
#define PSB_MMU_WO_MEMOWY	  0x0004	/* MMU WO memowy */

/* PTE's and PDE's */
#define PSB_PDE_MASK		  0x003FFFFF
#define PSB_PDE_SHIFT		  22
#define PSB_PTE_SHIFT		  12

/* Cache contwow */
#define PSB_PTE_VAWID		  0x0001	/* PTE / PDE vawid */
#define PSB_PTE_WO		  0x0002	/* Wwite onwy */
#define PSB_PTE_WO		  0x0004	/* Wead onwy */
#define PSB_PTE_CACHED		  0x0008	/* CPU cache cohewent */

/* VDC wegistews and bits */
#define PSB_MSVDX_CWOCKGATING	  0x2064
#define PSB_TOPAZ_CWOCKGATING	  0x2068
#define PSB_HWSTAM		  0x2098
#define PSB_INSTPM		  0x20C0
#define PSB_INT_IDENTITY_W        0x20A4
#define _PSB_IWQ_ASWE		  (1<<0)
#define _MDFWD_PIPEC_EVENT_FWAG   (1<<2)
#define _MDFWD_PIPEC_VBWANK_FWAG  (1<<3)
#define _PSB_DPST_PIPEB_FWAG      (1<<4)
#define _MDFWD_PIPEB_EVENT_FWAG   (1<<4)
#define _PSB_VSYNC_PIPEB_FWAG	  (1<<5)
#define _PSB_DPST_PIPEA_FWAG      (1<<6)
#define _PSB_PIPEA_EVENT_FWAG     (1<<6)
#define _PSB_VSYNC_PIPEA_FWAG	  (1<<7)
#define _PSB_IWQ_DISP_HOTSYNC	  (1<<17)
#define _PSB_IWQ_SGX_FWAG	  (1<<18)
#define _PSB_IWQ_MSVDX_FWAG	  (1<<19)
#define _WNC_IWQ_TOPAZ_FWAG	  (1<<20)

#define _PSB_PIPE_EVENT_FWAG	(_PSB_VSYNC_PIPEA_FWAG | \
				 _PSB_VSYNC_PIPEB_FWAG)

#define PSB_INT_IDENTITY_W	  0x20A4
#define PSB_INT_MASK_W		  0x20A8
#define PSB_INT_ENABWE_W	  0x20A0

#define _PSB_MMU_EW_MASK      0x0001FF00
#define _PSB_MMU_EW_HOST      (1 << 16)
#define GPIOA			0x5010
#define GPIOB			0x5014
#define GPIOC			0x5018
#define GPIOD			0x501c
#define GPIOE			0x5020
#define GPIOF			0x5024
#define GPIOG			0x5028
#define GPIOH			0x502c
#define GPIO_CWOCK_DIW_MASK		(1 << 0)
#define GPIO_CWOCK_DIW_IN		(0 << 1)
#define GPIO_CWOCK_DIW_OUT		(1 << 1)
#define GPIO_CWOCK_VAW_MASK		(1 << 2)
#define GPIO_CWOCK_VAW_OUT		(1 << 3)
#define GPIO_CWOCK_VAW_IN		(1 << 4)
#define GPIO_CWOCK_PUWWUP_DISABWE	(1 << 5)
#define GPIO_DATA_DIW_MASK		(1 << 8)
#define GPIO_DATA_DIW_IN		(0 << 9)
#define GPIO_DATA_DIW_OUT		(1 << 9)
#define GPIO_DATA_VAW_MASK		(1 << 10)
#define GPIO_DATA_VAW_OUT		(1 << 11)
#define GPIO_DATA_VAW_IN		(1 << 12)
#define GPIO_DATA_PUWWUP_DISABWE	(1 << 13)

#define VCWK_DIVISOW_VGA0   0x6000
#define VCWK_DIVISOW_VGA1   0x6004
#define VCWK_POST_DIV	    0x6010

#define PSB_COMM_2D (PSB_ENGINE_2D << 4)
#define PSB_COMM_3D (PSB_ENGINE_3D << 4)
#define PSB_COMM_TA (PSB_ENGINE_TA << 4)
#define PSB_COMM_HP (PSB_ENGINE_HP << 4)
#define PSB_COMM_USEW_IWQ (1024 >> 2)
#define PSB_COMM_USEW_IWQ_WOST (PSB_COMM_USEW_IWQ + 1)
#define PSB_COMM_FW (2048 >> 2)

#define PSB_UIWQ_VISTEST	       1
#define PSB_UIWQ_OOM_WEPWY	       2
#define PSB_UIWQ_FIWE_TA_WEPWY	       3
#define PSB_UIWQ_FIWE_WASTEW_WEPWY     4

#define PSB_2D_SIZE (256*1024*1024)
#define PSB_MAX_WEWOC_PAGES 1024

#define PSB_WOW_WEG_OFFS 0x0204
#define PSB_HIGH_WEG_OFFS 0x0600

#define PSB_NUM_VBWANKS 2

#define PSB_WATCHDOG_DEWAY (HZ * 2)
#define PSB_WID_DEWAY (HZ / 10)

#define PSB_MAX_BWIGHTNESS		100

#define PSB_PWW_STATE_ON		1
#define PSB_PWW_STATE_OFF		2

#define PSB_PMPOWICY_NOPM		0
#define PSB_PMPOWICY_CWOCKGATING	1
#define PSB_PMPOWICY_POWEWDOWN		2

#define PSB_PMSTATE_POWEWUP		0
#define PSB_PMSTATE_CWOCKGATED		1
#define PSB_PMSTATE_POWEWDOWN		2
#define PSB_PCIx_MSI_ADDW_WOC		0x94
#define PSB_PCIx_MSI_DATA_WOC		0x98

/* Medfiewd cwystaw settings */
#define KSEW_CWYSTAW_19 1
#define KSEW_BYPASS_19 5
#define KSEW_BYPASS_25 6
#define KSEW_BYPASS_83_100 7

stwuct opwegion_headew;
stwuct opwegion_acpi;
stwuct opwegion_swsci;
stwuct opwegion_aswe;

stwuct psb_intew_opwegion {
	stwuct opwegion_headew *headew;
	stwuct opwegion_acpi *acpi;
	stwuct opwegion_swsci *swsci;
	stwuct opwegion_aswe *aswe;
	void *vbt;
	u32 __iomem *wid_state;
	stwuct wowk_stwuct aswe_wowk;
};

stwuct sdvo_device_mapping {
	u8 initiawized;
	u8 dvo_powt;
	u8 swave_addw;
	u8 dvo_wiwing;
	u8 i2c_pin;
	u8 i2c_speed;
	u8 ddc_pin;
};

stwuct intew_gmbus {
	stwuct i2c_adaptew adaptew;
	stwuct i2c_adaptew *fowce_bit;
	u32 weg0;
};

/* Wegistew offset maps */
stwuct psb_offset {
	u32	fp0;
	u32	fp1;
	u32	cntw;
	u32	conf;
	u32	swc;
	u32	dpww;
	u32	dpww_md;
	u32	htotaw;
	u32	hbwank;
	u32	hsync;
	u32	vtotaw;
	u32	vbwank;
	u32	vsync;
	u32	stwide;
	u32	size;
	u32	pos;
	u32	suwf;
	u32	addw;
	u32	base;
	u32	status;
	u32	winoff;
	u32	tiweoff;
	u32	pawette;
};

/*
 *	Wegistew save state. This is used to howd the context when the
 *	device is powewed off. In the case of Oaktwaiw this can (but does not
 *	yet) incwude scween bwank. Opewations occuwing duwing the save
 *	update the wegistew cache instead.
 */

/* Common status fow pipes */
stwuct psb_pipe {
	u32	fp0;
	u32	fp1;
	u32	cntw;
	u32	conf;
	u32	swc;
	u32	dpww;
	u32	dpww_md;
	u32	htotaw;
	u32	hbwank;
	u32	hsync;
	u32	vtotaw;
	u32	vbwank;
	u32	vsync;
	u32	stwide;
	u32	size;
	u32	pos;
	u32	base;
	u32	suwf;
	u32	addw;
	u32	status;
	u32	winoff;
	u32	tiweoff;
	u32	pawette[256];
};

stwuct psb_state {
	uint32_t saveVCWK_DIVISOW_VGA0;
	uint32_t saveVCWK_DIVISOW_VGA1;
	uint32_t saveVCWK_POST_DIV;
	uint32_t saveVGACNTWW;
	uint32_t saveADPA;
	uint32_t saveWVDS;
	uint32_t saveDVOA;
	uint32_t saveDVOB;
	uint32_t saveDVOC;
	uint32_t savePP_ON;
	uint32_t savePP_OFF;
	uint32_t savePP_CONTWOW;
	uint32_t savePP_CYCWE;
	uint32_t savePFIT_CONTWOW;
	uint32_t saveCWOCKGATING;
	uint32_t saveDSPAWB;
	uint32_t savePFIT_AUTO_WATIOS;
	uint32_t savePFIT_PGM_WATIOS;
	uint32_t savePP_ON_DEWAYS;
	uint32_t savePP_OFF_DEWAYS;
	uint32_t savePP_DIVISOW;
	uint32_t saveBCWWPAT_A;
	uint32_t saveBCWWPAT_B;
	uint32_t savePEWF_MODE;
	uint32_t saveDSPFW1;
	uint32_t saveDSPFW2;
	uint32_t saveDSPFW3;
	uint32_t saveDSPFW4;
	uint32_t saveDSPFW5;
	uint32_t saveDSPFW6;
	uint32_t saveCHICKENBIT;
	uint32_t saveDSPACUWSOW_CTWW;
	uint32_t saveDSPBCUWSOW_CTWW;
	uint32_t saveDSPACUWSOW_BASE;
	uint32_t saveDSPBCUWSOW_BASE;
	uint32_t saveDSPACUWSOW_POS;
	uint32_t saveDSPBCUWSOW_POS;
	uint32_t saveOV_OVADD;
	uint32_t saveOV_OGAMC0;
	uint32_t saveOV_OGAMC1;
	uint32_t saveOV_OGAMC2;
	uint32_t saveOV_OGAMC3;
	uint32_t saveOV_OGAMC4;
	uint32_t saveOV_OGAMC5;
	uint32_t saveOVC_OVADD;
	uint32_t saveOVC_OGAMC0;
	uint32_t saveOVC_OGAMC1;
	uint32_t saveOVC_OGAMC2;
	uint32_t saveOVC_OGAMC3;
	uint32_t saveOVC_OGAMC4;
	uint32_t saveOVC_OGAMC5;

	/* DPST wegistew save */
	uint32_t saveHISTOGWAM_INT_CONTWOW_WEG;
	uint32_t saveHISTOGWAM_WOGIC_CONTWOW_WEG;
	uint32_t savePWM_CONTWOW_WOGIC;
};

stwuct cdv_state {
	uint32_t saveDSPCWK_GATE_D;
	uint32_t saveWAMCWK_GATE_D;
	uint32_t saveDSPAWB;
	uint32_t saveDSPFW[6];
	uint32_t saveADPA;
	uint32_t savePP_CONTWOW;
	uint32_t savePFIT_PGM_WATIOS;
	uint32_t saveWVDS;
	uint32_t savePFIT_CONTWOW;
	uint32_t savePP_ON_DEWAYS;
	uint32_t savePP_OFF_DEWAYS;
	uint32_t savePP_CYCWE;
	uint32_t saveVGACNTWW;
	uint32_t saveIEW;
	uint32_t saveIMW;
	u8	 saveWBB;
};

stwuct psb_save_awea {
	stwuct psb_pipe pipe[3];
	uint32_t saveBSM;
	uint32_t saveVBT;
	union {
	        stwuct psb_state psb;
		stwuct cdv_state cdv;
	};
	uint32_t saveBWC_PWM_CTW2;
	uint32_t saveBWC_PWM_CTW;
};

stwuct psb_ops;

#define PSB_NUM_PIPE		3

stwuct intew_scu_ipc_dev;

stwuct dwm_psb_pwivate {
	stwuct dwm_device dev;

	stwuct pci_dev *aux_pdev; /* Cuwwentwy onwy used by mwst */
	stwuct pci_dev *wpc_pdev; /* Cuwwentwy onwy used by mwst */
	const stwuct psb_ops *ops;
	const stwuct psb_offset *wegmap;

	stwuct chiwd_device_config *chiwd_dev;
	int chiwd_dev_num;

	stwuct psb_gtt gtt;

	/* GTT Memowy managew */
	stwuct psb_gtt_mm *gtt_mm;
	stwuct page *scwatch_page;
	u32 __iomem *gtt_map;
	uint32_t stowen_base;
	u8 __iomem *vwam_addw;
	unsigned wong vwam_stowen_size;
	u16 gmch_ctww;		/* Saved GTT setup */
	u32 pge_ctw;

	stwuct mutex gtt_mutex;
	stwuct wesouwce *gtt_mem;	/* Ouw PCI wesouwce */

	stwuct mutex mmap_mutex;

	stwuct psb_mmu_dwivew *mmu;
	stwuct psb_mmu_pd *pf_pd;

	/* Wegistew base */
	uint8_t __iomem *sgx_weg;
	uint8_t __iomem *vdc_weg;
	uint8_t __iomem *aux_weg; /* Auxiwwawy vdc pipe wegs */
	uint16_t wpc_gpio_base;
	uint32_t gatt_fwee_offset;

	/* Fencing / iwq */
	uint32_t vdc_iwq_mask;
	uint32_t pipestat[PSB_NUM_PIPE];

	spinwock_t iwqmask_wock;
	boow iwq_enabwed;

	/* Powew */
	boow pm_initiawized;

	/* Modesetting */
	stwuct psb_intew_mode_device mode_dev;
	boow modeset;	/* twue if we have done the mode_device setup */

	stwuct dwm_cwtc *pwane_to_cwtc_mapping[PSB_NUM_PIPE];
	stwuct dwm_cwtc *pipe_to_cwtc_mapping[PSB_NUM_PIPE];
	uint32_t num_pipe;

	/* OSPM info (Powew management base) (TODO: can go ?) */
	uint32_t ospm_base;

	/* Sizes info */
	u32 fuse_weg_vawue;
	u32 video_device_fuse;

	/* PCI wevision ID fow B0:D2:F0 */
	uint8_t pwatfowm_wev_id;

	/* gmbus */
	stwuct intew_gmbus *gmbus;
	uint8_t __iomem *gmbus_weg;

	/* Used by SDVO */
	int cwt_ddc_pin;
	/* FIXME: The mappings shouwd be pawsed fwom bios but fow now we can
		  pwetend thewe awe no mappings avaiwabwe */
	stwuct sdvo_device_mapping sdvo_mappings[2];
	u32 hotpwug_suppowted_mask;
	stwuct dwm_pwopewty *bwoadcast_wgb_pwopewty;
	stwuct dwm_pwopewty *fowce_audio_pwopewty;

	/* WVDS info */
	int backwight_duty_cycwe;	/* westowe backwight to this vawue */
	boow panew_wants_dithew;
	stwuct dwm_dispway_mode *panew_fixed_mode;
	stwuct dwm_dispway_mode *wfp_wvds_vbt_mode;
	stwuct dwm_dispway_mode *sdvo_wvds_vbt_mode;

	stwuct bdb_wvds_backwight *wvds_bw; /* WVDS backwight info fwom VBT */
	stwuct gma_i2c_chan *wvds_i2c_bus; /* FIXME: Wemove this? */

	/* Featuwe bits fwom the VBIOS */
	unsigned int int_tv_suppowt:1;
	unsigned int wvds_dithew:1;
	unsigned int wvds_vbt:1;
	unsigned int int_cwt_suppowt:1;
	unsigned int wvds_use_ssc:1;
	int wvds_ssc_fweq;
	boow is_wvds_on;
	boow is_mipi_on;
	boow wvds_enabwed_in_vbt;
	u32 mipi_ctww_dispway;

	unsigned int cowe_fweq;
	uint32_t iWVDS_enabwe;

	/* MID specific */
	boow use_msi;
	boow has_gct;
	stwuct oaktwaiw_gct_data gct_data;

	/* Oaktwaiw HDMI state */
	stwuct oaktwaiw_hdmi_dev *hdmi_pwiv;

	/* Wegistew state */
	stwuct psb_save_awea wegs;

	/* Hotpwug handwing */
	stwuct wowk_stwuct hotpwug_wowk;

	/* WID-Switch */
	spinwock_t wid_wock;
	stwuct timew_wist wid_timew;
	stwuct psb_intew_opwegion opwegion;
	u32 wid_wast_state;

	/* Watchdog */
	uint32_t apm_weg;
	uint16_t apm_base;

	/*
	 * Used fow modifying backwight fwom
	 * xwandw -- considew wemoving and using HAW instead
	 */
	stwuct intew_scu_ipc_dev *scu;
	stwuct backwight_device *backwight_device;
	stwuct dwm_pwopewty *backwight_pwopewty;
	boow backwight_enabwed;
	int backwight_wevew;
	uint32_t bwc_adj1;
	uint32_t bwc_adj2;

	boow dsw_enabwe;
	u32 dsw_fb_update;
	boow dpi_panew_on[3];
	void *dsi_configs[2];
	u32 bpp;
	u32 bpp2;

	u32 pipeconf[3];
	u32 dspcntw[3];

	boow dpwwa_96mhz;	/* DPWW data fwom the VBT */

	stwuct {
		int wate;
		int wanes;
		int pweemphasis;
		int vswing;

		boow initiawized;
		boow suppowt;
		int bpp;
		stwuct edp_powew_seq pps;
	} edp;
	uint8_t panew_type;
};

static inwine stwuct dwm_psb_pwivate *to_dwm_psb_pwivate(stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct dwm_psb_pwivate, dev);
}

/* Opewations fow each boawd type */
stwuct psb_ops {
	const chaw *name;
	int pipes;		/* Numbew of output pipes */
	int cwtcs;		/* Numbew of CWTCs */
	int sgx_offset;		/* Base offset of SGX device */
	int hdmi_mask;		/* Mask of HDMI CWTCs */
	int wvds_mask;		/* Mask of WVDS CWTCs */
	int sdvo_mask;		/* Mask of SDVO CWTCs */
	int cuwsow_needs_phys;  /* If cuwsow base weg need physicaw addwess */

	/* Sub functions */
	stwuct dwm_cwtc_hewpew_funcs const *cwtc_hewpew;
	const stwuct gma_cwock_funcs *cwock_funcs;

	/* Setup hooks */
	int (*chip_setup)(stwuct dwm_device *dev);
	void (*chip_teawdown)(stwuct dwm_device *dev);
	/* Optionaw hewpew cawwew aftew modeset */
	void (*ewwata)(stwuct dwm_device *dev);

	/* Dispway management hooks */
	int (*output_init)(stwuct dwm_device *dev);
	int (*hotpwug)(stwuct dwm_device *dev);
	void (*hotpwug_enabwe)(stwuct dwm_device *dev, boow on);
	/* Powew management hooks */
	void (*init_pm)(stwuct dwm_device *dev);
	int (*save_wegs)(stwuct dwm_device *dev);
	int (*westowe_wegs)(stwuct dwm_device *dev);
	void (*save_cwtc)(stwuct dwm_cwtc *cwtc);
	void (*westowe_cwtc)(stwuct dwm_cwtc *cwtc);
	int (*powew_up)(stwuct dwm_device *dev);
	int (*powew_down)(stwuct dwm_device *dev);
	void (*update_wm)(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc);
	void (*disabwe_sw)(stwuct dwm_device *dev);

	void (*wvds_bw_powew)(stwuct dwm_device *dev, boow on);

	/* Backwight */
	int (*backwight_init)(stwuct dwm_device *dev);
	void (*backwight_set)(stwuct dwm_device *dev, int wevew);
	int (*backwight_get)(stwuct dwm_device *dev);
	const chaw *backwight_name;

	int i2c_bus;		/* I2C bus identifiew fow Moowestown */
};

/* psb_wid.c */
extewn void psb_wid_timew_init(stwuct dwm_psb_pwivate *dev_pwiv);
extewn void psb_wid_timew_takedown(stwuct dwm_psb_pwivate *dev_pwiv);

/* modesetting */
extewn void psb_modeset_init(stwuct dwm_device *dev);
extewn void psb_modeset_cweanup(stwuct dwm_device *dev);

/* fwamebuffew */
stwuct dwm_fwamebuffew *psb_fwamebuffew_cweate(stwuct dwm_device *dev,
					       const stwuct dwm_mode_fb_cmd2 *mode_cmd,
					       stwuct dwm_gem_object *obj);

/* fbdev */
#if defined(CONFIG_DWM_FBDEV_EMUWATION)
void psb_fbdev_setup(stwuct dwm_psb_pwivate *dev_pwiv);
#ewse
static inwine void psb_fbdev_setup(stwuct dwm_psb_pwivate *dev_pwiv)
{ }
#endif

/* backwight.c */
int gma_backwight_init(stwuct dwm_device *dev);
void gma_backwight_exit(stwuct dwm_device *dev);
void gma_backwight_disabwe(stwuct dwm_device *dev);
void gma_backwight_enabwe(stwuct dwm_device *dev);
void gma_backwight_set(stwuct dwm_device *dev, int v);

/* oaktwaiw_cwtc.c */
extewn const stwuct dwm_cwtc_hewpew_funcs oaktwaiw_hewpew_funcs;

/* oaktwaiw_wvds.c */
extewn void oaktwaiw_wvds_init(stwuct dwm_device *dev,
		    stwuct psb_intew_mode_device *mode_dev);

/* psb_intew_dispway.c */
extewn const stwuct dwm_cwtc_hewpew_funcs psb_intew_hewpew_funcs;

/* psb_intew_wvds.c */
extewn const stwuct dwm_connectow_hewpew_funcs
					psb_intew_wvds_connectow_hewpew_funcs;
extewn const stwuct dwm_connectow_funcs psb_intew_wvds_connectow_funcs;

/* gem.c */
extewn int psb_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			stwuct dwm_mode_cweate_dumb *awgs);

/* psb_device.c */
extewn const stwuct psb_ops psb_chip_ops;

/* oaktwaiw_device.c */
extewn const stwuct psb_ops oaktwaiw_chip_ops;

/* cdv_device.c */
extewn const stwuct psb_ops cdv_chip_ops;

/* Utiwities */
static inwine uint32_t WEGISTEW_WEAD(stwuct dwm_device *dev, uint32_t weg)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	wetuwn iowead32(dev_pwiv->vdc_weg + weg);
}

static inwine uint32_t WEGISTEW_WEAD_AUX(stwuct dwm_device *dev, uint32_t weg)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	wetuwn iowead32(dev_pwiv->aux_weg + weg);
}

#define WEG_WEAD(weg)	       WEGISTEW_WEAD(dev, (weg))
#define WEG_WEAD_AUX(weg)      WEGISTEW_WEAD_AUX(dev, (weg))

/* Usefuw fow post weads */
static inwine uint32_t WEGISTEW_WEAD_WITH_AUX(stwuct dwm_device *dev,
					      uint32_t weg, int aux)
{
	uint32_t vaw;

	if (aux)
		vaw = WEG_WEAD_AUX(weg);
	ewse
		vaw = WEG_WEAD(weg);

	wetuwn vaw;
}

#define WEG_WEAD_WITH_AUX(weg, aux) WEGISTEW_WEAD_WITH_AUX(dev, (weg), (aux))

static inwine void WEGISTEW_WWITE(stwuct dwm_device *dev, uint32_t weg,
				  uint32_t vaw)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	iowwite32((vaw), dev_pwiv->vdc_weg + (weg));
}

static inwine void WEGISTEW_WWITE_AUX(stwuct dwm_device *dev, uint32_t weg,
				      uint32_t vaw)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	iowwite32((vaw), dev_pwiv->aux_weg + (weg));
}

#define WEG_WWITE(weg, vaw)	WEGISTEW_WWITE(dev, (weg), (vaw))
#define WEG_WWITE_AUX(weg, vaw)	WEGISTEW_WWITE_AUX(dev, (weg), (vaw))

static inwine void WEGISTEW_WWITE_WITH_AUX(stwuct dwm_device *dev, uint32_t weg,
				      uint32_t vaw, int aux)
{
	if (aux)
		WEG_WWITE_AUX(weg, vaw);
	ewse
		WEG_WWITE(weg, vaw);
}

#define WEG_WWITE_WITH_AUX(weg, vaw, aux) WEGISTEW_WWITE_WITH_AUX(dev, (weg), (vaw), (aux))

static inwine void WEGISTEW_WWITE16(stwuct dwm_device *dev,
					uint32_t weg, uint32_t vaw)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	iowwite16((vaw), dev_pwiv->vdc_weg + (weg));
}

#define WEG_WWITE16(weg, vaw)	  WEGISTEW_WWITE16(dev, (weg), (vaw))

static inwine void WEGISTEW_WWITE8(stwuct dwm_device *dev,
				       uint32_t weg, uint32_t vaw)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	iowwite8((vaw), dev_pwiv->vdc_weg + (weg));
}

#define WEG_WWITE8(weg, vaw)		WEGISTEW_WWITE8(dev, (weg), (vaw))

#define PSB_WVDC32(_vaw, _offs)		iowwite32(_vaw, dev_pwiv->vdc_weg + (_offs))
#define PSB_WVDC32(_offs)		iowead32(dev_pwiv->vdc_weg + (_offs))

#define PSB_WSGX32(_offs)		iowead32(dev_pwiv->sgx_weg + (_offs))
#define PSB_WSGX32(_vaw, _offs)		iowwite32(_vaw, dev_pwiv->sgx_weg + (_offs))

#define PSB_WMSVDX32(_vaw, _offs)	iowwite32(_vaw, dev_pwiv->msvdx_weg + (_offs))
#define PSB_WMSVDX32(_offs)		iowead32(dev_pwiv->msvdx_weg + (_offs))

#endif
