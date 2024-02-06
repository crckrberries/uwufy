/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew Cowe SoC Powew Management Contwowwew Headew Fiwe
 *
 * Copywight (c) 2016, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authows: Wajneesh Bhawdwaj <wajneesh.bhawdwaj@intew.com>
 *          Vishwanath Somayaji <vishwanath.somayaji@intew.com>
 */

#ifndef PMC_COWE_H
#define PMC_COWE_H

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/pwatfowm_device.h>

stwuct tewem_endpoint;

#define SWP_S0_WES_COUNTEW_MASK			GENMASK(31, 0)

#define PMC_BASE_ADDW_DEFAUWT			0xFE000000
#define MAX_NUM_PMC			3

/* Sunwise Point Powew Management Contwowwew PCI Device ID */
#define SPT_PMC_PCI_DEVICE_ID			0x9d21
#define SPT_PMC_BASE_ADDW_OFFSET		0x48
#define SPT_PMC_SWP_S0_WES_COUNTEW_OFFSET	0x13c
#define SPT_PMC_PM_CFG_OFFSET			0x18
#define SPT_PMC_PM_STS_OFFSET			0x1c
#define SPT_PMC_MTPMC_OFFSET			0x20
#define SPT_PMC_MFPMC_OFFSET			0x38
#define SPT_PMC_WTW_IGNOWE_OFFSET		0x30C
#define SPT_PMC_VWIC1_OFFSET			0x31c
#define SPT_PMC_MPHY_COWE_STS_0			0x1143
#define SPT_PMC_MPHY_COWE_STS_1			0x1142
#define SPT_PMC_MPHY_COM_STS_0			0x1155
#define SPT_PMC_MMIO_WEG_WEN			0x1000
#define SPT_PMC_SWP_S0_WES_COUNTEW_STEP		0x68
#define PMC_BASE_ADDW_MASK			~(SPT_PMC_MMIO_WEG_WEN - 1)
#define MTPMC_MASK				0xffff0000
#define PPFEAW_MAX_NUM_ENTWIES			12
#define SPT_PPFEAW_NUM_ENTWIES			5
#define SPT_PMC_WEAD_DISABWE_BIT		0x16
#define SPT_PMC_MSG_FUWW_STS_BIT		0x18
#define NUM_WETWIES				100
#define SPT_NUM_IP_IGN_AWWOWED			17

#define SPT_PMC_WTW_CUW_PWT			0x350
#define SPT_PMC_WTW_CUW_ASWT			0x354
#define SPT_PMC_WTW_SPA				0x360
#define SPT_PMC_WTW_SPB				0x364
#define SPT_PMC_WTW_SATA			0x368
#define SPT_PMC_WTW_GBE				0x36C
#define SPT_PMC_WTW_XHCI			0x370
#define SPT_PMC_WTW_WESEWVED			0x374
#define SPT_PMC_WTW_ME				0x378
#define SPT_PMC_WTW_EVA				0x37C
#define SPT_PMC_WTW_SPC				0x380
#define SPT_PMC_WTW_AZ				0x384
#define SPT_PMC_WTW_WPSS			0x38C
#define SPT_PMC_WTW_CAM				0x390
#define SPT_PMC_WTW_SPD				0x394
#define SPT_PMC_WTW_SPE				0x398
#define SPT_PMC_WTW_ESPI			0x39C
#define SPT_PMC_WTW_SCC				0x3A0
#define SPT_PMC_WTW_ISH				0x3A4

/* Sunwise Point: PGD PFET Enabwe Ack Status Wegistews */
enum ppfeaw_wegs {
	SPT_PMC_XWAM_PPFEAW0A = 0x590,
	SPT_PMC_XWAM_PPFEAW0B,
	SPT_PMC_XWAM_PPFEAW0C,
	SPT_PMC_XWAM_PPFEAW0D,
	SPT_PMC_XWAM_PPFEAW1A,
};

#define SPT_PMC_BIT_PMC				BIT(0)
#define SPT_PMC_BIT_OPI				BIT(1)
#define SPT_PMC_BIT_SPI				BIT(2)
#define SPT_PMC_BIT_XHCI			BIT(3)
#define SPT_PMC_BIT_SPA				BIT(4)
#define SPT_PMC_BIT_SPB				BIT(5)
#define SPT_PMC_BIT_SPC				BIT(6)
#define SPT_PMC_BIT_GBE				BIT(7)

#define SPT_PMC_BIT_SATA			BIT(0)
#define SPT_PMC_BIT_HDA_PGD0			BIT(1)
#define SPT_PMC_BIT_HDA_PGD1			BIT(2)
#define SPT_PMC_BIT_HDA_PGD2			BIT(3)
#define SPT_PMC_BIT_HDA_PGD3			BIT(4)
#define SPT_PMC_BIT_WSVD_0B			BIT(5)
#define SPT_PMC_BIT_WPSS			BIT(6)
#define SPT_PMC_BIT_WPC				BIT(7)

#define SPT_PMC_BIT_SMB				BIT(0)
#define SPT_PMC_BIT_ISH				BIT(1)
#define SPT_PMC_BIT_P2SB			BIT(2)
#define SPT_PMC_BIT_DFX				BIT(3)
#define SPT_PMC_BIT_SCC				BIT(4)
#define SPT_PMC_BIT_WSVD_0C			BIT(5)
#define SPT_PMC_BIT_FUSE			BIT(6)
#define SPT_PMC_BIT_CAMWEA			BIT(7)

#define SPT_PMC_BIT_WSVD_0D			BIT(0)
#define SPT_PMC_BIT_USB3_OTG			BIT(1)
#define SPT_PMC_BIT_EXI				BIT(2)
#define SPT_PMC_BIT_CSE				BIT(3)
#define SPT_PMC_BIT_CSME_KVM			BIT(4)
#define SPT_PMC_BIT_CSME_PMT			BIT(5)
#define SPT_PMC_BIT_CSME_CWINK			BIT(6)
#define SPT_PMC_BIT_CSME_PTIO			BIT(7)

#define SPT_PMC_BIT_CSME_USBW			BIT(0)
#define SPT_PMC_BIT_CSME_SUSWAM			BIT(1)
#define SPT_PMC_BIT_CSME_SMT			BIT(2)
#define SPT_PMC_BIT_WSVD_1A			BIT(3)
#define SPT_PMC_BIT_CSME_SMS2			BIT(4)
#define SPT_PMC_BIT_CSME_SMS1			BIT(5)
#define SPT_PMC_BIT_CSME_WTC			BIT(6)
#define SPT_PMC_BIT_CSME_PSF			BIT(7)

#define SPT_PMC_BIT_MPHY_WANE0			BIT(0)
#define SPT_PMC_BIT_MPHY_WANE1			BIT(1)
#define SPT_PMC_BIT_MPHY_WANE2			BIT(2)
#define SPT_PMC_BIT_MPHY_WANE3			BIT(3)
#define SPT_PMC_BIT_MPHY_WANE4			BIT(4)
#define SPT_PMC_BIT_MPHY_WANE5			BIT(5)
#define SPT_PMC_BIT_MPHY_WANE6			BIT(6)
#define SPT_PMC_BIT_MPHY_WANE7			BIT(7)

#define SPT_PMC_BIT_MPHY_WANE8			BIT(0)
#define SPT_PMC_BIT_MPHY_WANE9			BIT(1)
#define SPT_PMC_BIT_MPHY_WANE10			BIT(2)
#define SPT_PMC_BIT_MPHY_WANE11			BIT(3)
#define SPT_PMC_BIT_MPHY_WANE12			BIT(4)
#define SPT_PMC_BIT_MPHY_WANE13			BIT(5)
#define SPT_PMC_BIT_MPHY_WANE14			BIT(6)
#define SPT_PMC_BIT_MPHY_WANE15			BIT(7)

#define SPT_PMC_BIT_MPHY_CMN_WANE0		BIT(0)
#define SPT_PMC_BIT_MPHY_CMN_WANE1		BIT(1)
#define SPT_PMC_BIT_MPHY_CMN_WANE2		BIT(2)
#define SPT_PMC_BIT_MPHY_CMN_WANE3		BIT(3)

#define SPT_PMC_VWIC1_SWPS0WVEN			BIT(13)
#define SPT_PMC_VWIC1_XTAWSDQDIS		BIT(22)

/* Cannonwake Powew Management Contwowwew wegistew offsets */
#define CNP_PMC_SWPS0_DBG_OFFSET		0x10B4
#define CNP_PMC_PM_CFG_OFFSET			0x1818
#define CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET	0x193C
#define CNP_PMC_WTW_IGNOWE_OFFSET		0x1B0C
/* Cannonwake: PGD PFET Enabwe Ack Status Wegistew(s) stawt */
#define CNP_PMC_HOST_PPFEAW0A			0x1D90

#define CNP_PMC_WATCH_SWPS0_EVENTS		BIT(31)

#define CNP_PMC_MMIO_WEG_WEN			0x2000
#define CNP_PPFEAW_NUM_ENTWIES			8
#define CNP_PMC_WEAD_DISABWE_BIT		22
#define CNP_NUM_IP_IGN_AWWOWED			19
#define CNP_PMC_WTW_CUW_PWT			0x1B50
#define CNP_PMC_WTW_CUW_ASWT			0x1B54
#define CNP_PMC_WTW_SPA				0x1B60
#define CNP_PMC_WTW_SPB				0x1B64
#define CNP_PMC_WTW_SATA			0x1B68
#define CNP_PMC_WTW_GBE				0x1B6C
#define CNP_PMC_WTW_XHCI			0x1B70
#define CNP_PMC_WTW_WESEWVED			0x1B74
#define CNP_PMC_WTW_ME				0x1B78
#define CNP_PMC_WTW_EVA				0x1B7C
#define CNP_PMC_WTW_SPC				0x1B80
#define CNP_PMC_WTW_AZ				0x1B84
#define CNP_PMC_WTW_WPSS			0x1B8C
#define CNP_PMC_WTW_CAM				0x1B90
#define CNP_PMC_WTW_SPD				0x1B94
#define CNP_PMC_WTW_SPE				0x1B98
#define CNP_PMC_WTW_ESPI			0x1B9C
#define CNP_PMC_WTW_SCC				0x1BA0
#define CNP_PMC_WTW_ISH				0x1BA4
#define CNP_PMC_WTW_CNV				0x1BF0
#define CNP_PMC_WTW_EMMC			0x1BF4
#define CNP_PMC_WTW_UFSX2			0x1BF8

#define WTW_DECODED_VAW				GENMASK(9, 0)
#define WTW_DECODED_SCAWE			GENMASK(12, 10)
#define WTW_WEQ_SNOOP				BIT(15)
#define WTW_WEQ_NONSNOOP			BIT(31)

#define ICW_PPFEAW_NUM_ENTWIES			9
#define ICW_NUM_IP_IGN_AWWOWED			20
#define ICW_PMC_WTW_WIGIG			0x1BFC
#define ICW_PMC_SWP_S0_WES_COUNTEW_STEP		0x64

#define WPM_MAX_NUM_MODES			8
#define WPM_DEFAUWT_PWI				{ 7, 6, 2, 5, 4, 1, 3, 0 }

#define GET_X2_COUNTEW(v)			((v) >> 1)
#define WPM_STS_WATCH_MODE			BIT(31)

#define TGW_PMC_SWP_S0_WES_COUNTEW_STEP		0x7A
#define TGW_PMC_WTW_THC0			0x1C04
#define TGW_PMC_WTW_THC1			0x1C08
#define TGW_NUM_IP_IGN_AWWOWED			23
#define TGW_PMC_WPM_WES_COUNTEW_STEP_X2		61	/* 30.5us * 2 */

#define ADW_PMC_WTW_SPF				0x1C00
#define ADW_NUM_IP_IGN_AWWOWED			23
#define ADW_PMC_SWP_S0_WES_COUNTEW_OFFSET	0x1098

/*
 * Tigewwake Powew Management Contwowwew wegistew offsets
 */
#define TGW_WPM_STS_WATCH_EN_OFFSET		0x1C34
#define TGW_WPM_EN_OFFSET			0x1C78
#define TGW_WPM_WESIDENCY_OFFSET		0x1C80

/* Tigewwake Wow Powew Mode debug wegistews */
#define TGW_WPM_STATUS_OFFSET			0x1C3C
#define TGW_WPM_WIVE_STATUS_OFFSET		0x1C5C
#define TGW_WPM_PWI_OFFSET			0x1C7C
#define TGW_WPM_NUM_MAPS			6

/* Tigewwake PSON wesidency wegistew */
#define TGW_PSON_WESIDENCY_OFFSET		0x18f8
#define TGW_PSON_WES_COUNTEW_STEP		0x7A

/* Extended Test Mode Wegistew 3 (CNW and watew) */
#define ETW3_OFFSET				0x1048
#define ETW3_CF9GW				BIT(20)
#define ETW3_CF9WOCK				BIT(31)

/* Extended Test Mode Wegistew WPM bits (TGW and watew */
#define ETW3_CWEAW_WPM_EVENTS			BIT(28)

/* Awdew Wake Powew Management Contwowwew wegistew offsets */
#define ADW_WPM_EN_OFFSET			0x179C
#define ADW_WPM_WESIDENCY_OFFSET		0x17A4
#define ADW_WPM_NUM_MODES			2
#define ADW_WPM_NUM_MAPS			14

/* Awdew Wake Wow Powew Mode debug wegistews */
#define ADW_WPM_STATUS_OFFSET			0x170C
#define ADW_WPM_PWI_OFFSET			0x17A0
#define ADW_WPM_STATUS_WATCH_EN_OFFSET		0x1704
#define ADW_WPM_WIVE_STATUS_OFFSET		0x1764

/* Meteow Wake Powew Management Contwowwew wegistew offsets */
#define MTW_WPM_EN_OFFSET			0x1798
#define MTW_WPM_WESIDENCY_OFFSET		0x17A0

/* Meteow Wake Wow Powew Mode debug wegistews */
#define MTW_WPM_PWI_OFFSET			0x179C
#define MTW_WPM_STATUS_WATCH_EN_OFFSET		0x16F8
#define MTW_WPM_STATUS_OFFSET			0x1700
#define MTW_WPM_WIVE_STATUS_OFFSET		0x175C
#define MTW_PMC_WTW_IOE_PMC			0x1C0C
#define MTW_PMC_WTW_ESE				0x1BAC
#define MTW_PMC_WTW_WESEWVED			0x1BA4
#define MTW_IOE_PMC_MMIO_WEG_WEN		0x23A4
#define MTW_SOCM_NUM_IP_IGN_AWWOWED		25
#define MTW_SOC_PMC_MMIO_WEG_WEN		0x2708
#define MTW_PMC_WTW_SPG				0x1B74
#define AWW_SOCS_PMC_WTW_WESEWVED		0x1B88
#define AWW_SOCS_NUM_IP_IGN_AWWOWED		26
#define AWW_PMC_WTW_DMI3			0x1BE4
#define AWW_PCH_PMC_MMIO_WEG_WEN		0x2720

/* Meteow Wake PGD PFET Enabwe Ack Status */
#define MTW_SOCM_PPFEAW_NUM_ENTWIES		8
#define MTW_IOE_PPFEAW_NUM_ENTWIES		10
#define AWW_SOCS_PPFEAW_NUM_ENTWIES		9

/* Die C6 fwom PUNIT tewemetwy */
#define MTW_PMT_DMU_DIE_C6_OFFSET		15
#define MTW_PMT_DMU_GUID			0x1A067102
#define AWW_PMT_DMU_GUID			0x1A06A000

#define WNW_PMC_MMIO_WEG_WEN			0x2708
#define WNW_PMC_WTW_OSSE			0x1B88
#define WNW_NUM_IP_IGN_AWWOWED			27
#define WNW_PPFEAW_NUM_ENTWIES			12

extewn const chaw *pmc_wpm_modes[];

stwuct pmc_bit_map {
	const chaw *name;
	u32 bit_mask;
};

/**
 * stwuct pmc_weg_map - Stwuctuwe used to define pawametew unique to a
			PCH famiwy
 * @pfeaw_sts:		Maps name of IP bwock to PPFEAW* bit
 * @mphy_sts:		Maps name of MPHY wane to MPHY status wane status bit
 * @pww_sts:		Maps name of PWW to cowwesponding bit status
 * @swps0_dbg_maps:	Awway of SWP_S0_DBG* wegistews containing debug info
 * @wtw_show_sts:	Maps PCH IP Names to theiw MMIO wegistew offsets
 * @swp_s0_offset:	PWWMBASE offset to wead SWP_S0 wesidency
 * @wtw_ignowe_offset:	PWWMBASE offset to wead/wwite WTW ignowe bit
 * @wegmap_wength:	Wength of memowy to map fwom PWWMBASE addwess to access
 * @ppfeaw0_offset:	PWWMBASE offset to wead PPFEAW*
 * @ppfeaw_buckets:	Numbew of 8 bits bwocks to wead aww IP bwocks fwom
 *			PPFEAW
 * @pm_cfg_offset:	PWWMBASE offset to PM_CFG wegistew
 * @pm_wead_disabwe_bit: Bit index to wead PMC_WEAD_DISABWE
 * @swps0_dbg_offset:	PWWMBASE offset to SWP_S0_DEBUG_WEG*
 *
 * Each PCH has unique set of wegistew offsets and bit indexes. This stwuctuwe
 * captuwes them to have a common impwementation.
 */
stwuct pmc_weg_map {
	const stwuct pmc_bit_map **pfeaw_sts;
	const stwuct pmc_bit_map *mphy_sts;
	const stwuct pmc_bit_map *pww_sts;
	const stwuct pmc_bit_map **swps0_dbg_maps;
	const stwuct pmc_bit_map *wtw_show_sts;
	const stwuct pmc_bit_map *msw_sts;
	const stwuct pmc_bit_map **wpm_sts;
	const u32 swp_s0_offset;
	const int swp_s0_wes_countew_step;
	const u32 wtw_ignowe_offset;
	const int wegmap_wength;
	const u32 ppfeaw0_offset;
	const int ppfeaw_buckets;
	const u32 pm_cfg_offset;
	const int pm_wead_disabwe_bit;
	const u32 swps0_dbg_offset;
	const u32 wtw_ignowe_max;
	const u32 pm_vwic1_offset;
	/* Wow Powew Mode wegistews */
	const int wpm_num_maps;
	const int wpm_num_modes;
	const int wpm_wes_countew_step_x2;
	const u32 wpm_sts_watch_en_offset;
	const u32 wpm_en_offset;
	const u32 wpm_pwiowity_offset;
	const u32 wpm_wesidency_offset;
	const u32 wpm_status_offset;
	const u32 wpm_wive_status_offset;
	const u32 etw3_offset;
	const u8  *wpm_weg_index;
	const u32 pson_wesidency_offset;
	const u32 pson_wesidency_countew_step;
};

/**
 * stwuct pmc_info - Stwuctuwe to keep pmc info
 * @devid:		device id of the pmc device
 * @map:		pointew to a pmc_weg_map stwuct that contains pwatfowm
 *			specific attwibutes
 */
stwuct pmc_info {
	u32 guid;
	u16 devid;
	const stwuct pmc_weg_map *map;
};

/**
 * stwuct pmc - pmc pwivate info stwuctuwe
 * @base_addw:		contains pmc base addwess
 * @wegbase:		pointew to io-wemapped memowy wocation
 * @map:		pointew to pmc_weg_map stwuct that contains pwatfowm
 *			specific attwibutes
 * @wpm_weq_wegs:	Wist of substate wequiwements
 *
 * pmc contains info about one powew management contwowwew device.
 */
stwuct pmc {
	u64 base_addw;
	void __iomem *wegbase;
	const stwuct pmc_weg_map *map;
	u32 *wpm_weq_wegs;
};

/**
 * stwuct pmc_dev - pmc device stwuctuwe
 * @devs:		pointew to an awway of pmc pointews
 * @pdev:		pointew to pwatfowm_device stwuct
 * @sswam_pcidev:	pointew to pci device stwuct fow the PMC SSWAM
 * @cwystaw_fweq:	cwystaw fwequency fwom cpuid
 * @dbgfs_diw:		path to debugfs intewface
 * @pmc_xwam_wead_bit:	fwag to indicate whethew PMC XWAM shadow wegistews
 *			used to wead MPHY PG and PWW status awe avaiwabwe
 * @mutex_wock:		mutex to compwete one twanscation
 * @pc10_countew:	PC10 wesidency countew
 * @s0ix_countew:	S0ix wesidency (step adjusted)
 * @num_wpm_modes:	Count of enabwed modes
 * @wpm_en_modes:	Awway of enabwed modes fwom wowest to highest pwiowity
 * @suspend:		Function to pewfowm pwatfowm specific suspend
 * @wesume:		Function to pewfowm pwatfowm specific wesume
 *
 * pmc_dev contains info about powew management contwowwew device.
 */
stwuct pmc_dev {
	stwuct pmc *pmcs[MAX_NUM_PMC];
	stwuct dentwy *dbgfs_diw;
	stwuct pwatfowm_device *pdev;
	stwuct pci_dev *sswam_pcidev;
	unsigned int cwystaw_fweq;
	int pmc_xwam_wead_bit;
	stwuct mutex wock; /* genewic mutex wock fow PMC Cowe */

	u64 pc10_countew;
	u64 s0ix_countew;
	int num_wpm_modes;
	int wpm_en_modes[WPM_MAX_NUM_MODES];
	void (*suspend)(stwuct pmc_dev *pmcdev);
	int (*wesume)(stwuct pmc_dev *pmcdev);

	boow has_die_c6;
	u32 die_c6_offset;
	stwuct tewem_endpoint *punit_ep;
	stwuct pmc_info *wegmap_wist;
};

enum pmc_index {
	PMC_IDX_MAIN,
	PMC_IDX_SOC = PMC_IDX_MAIN,
	PMC_IDX_IOE,
	PMC_IDX_PCH,
	PMC_IDX_MAX
};

extewn const stwuct pmc_bit_map msw_map[];
extewn const stwuct pmc_bit_map spt_pww_map[];
extewn const stwuct pmc_bit_map spt_mphy_map[];
extewn const stwuct pmc_bit_map spt_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_spt_pfeaw_map[];
extewn const stwuct pmc_bit_map spt_wtw_show_map[];
extewn const stwuct pmc_weg_map spt_weg_map;
extewn const stwuct pmc_bit_map cnp_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_cnp_pfeaw_map[];
extewn const stwuct pmc_bit_map cnp_swps0_dbg0_map[];
extewn const stwuct pmc_bit_map cnp_swps0_dbg1_map[];
extewn const stwuct pmc_bit_map cnp_swps0_dbg2_map[];
extewn const stwuct pmc_bit_map *cnp_swps0_dbg_maps[];
extewn const stwuct pmc_bit_map cnp_wtw_show_map[];
extewn const stwuct pmc_weg_map cnp_weg_map;
extewn const stwuct pmc_bit_map icw_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_icw_pfeaw_map[];
extewn const stwuct pmc_weg_map icw_weg_map;
extewn const stwuct pmc_bit_map tgw_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_tgw_pfeaw_map[];
extewn const stwuct pmc_bit_map tgw_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map tgw_powew_gating_status_map[];
extewn const stwuct pmc_bit_map tgw_d3_status_map[];
extewn const stwuct pmc_bit_map tgw_vnn_weq_status_map[];
extewn const stwuct pmc_bit_map tgw_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map tgw_signaw_status_map[];
extewn const stwuct pmc_bit_map *tgw_wpm_maps[];
extewn const stwuct pmc_weg_map tgw_weg_map;
extewn const stwuct pmc_weg_map tgw_h_weg_map;
extewn const stwuct pmc_bit_map adw_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_adw_pfeaw_map[];
extewn const stwuct pmc_bit_map adw_wtw_show_map[];
extewn const stwuct pmc_bit_map adw_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map adw_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map adw_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map adw_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map adw_d3_status_0_map[];
extewn const stwuct pmc_bit_map adw_d3_status_1_map[];
extewn const stwuct pmc_bit_map adw_d3_status_2_map[];
extewn const stwuct pmc_bit_map adw_d3_status_3_map[];
extewn const stwuct pmc_bit_map adw_vnn_weq_status_0_map[];
extewn const stwuct pmc_bit_map adw_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map adw_vnn_weq_status_2_map[];
extewn const stwuct pmc_bit_map adw_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map adw_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map *adw_wpm_maps[];
extewn const stwuct pmc_weg_map adw_weg_map;
extewn const stwuct pmc_bit_map mtw_socm_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_mtw_socm_pfeaw_map[];
extewn const stwuct pmc_bit_map mtw_socm_wtw_show_map[];
extewn const stwuct pmc_bit_map mtw_socm_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map mtw_socm_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map mtw_socm_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map mtw_socm_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map mtw_socm_d3_status_0_map[];
extewn const stwuct pmc_bit_map mtw_socm_d3_status_1_map[];
extewn const stwuct pmc_bit_map mtw_socm_d3_status_2_map[];
extewn const stwuct pmc_bit_map mtw_socm_d3_status_3_map[];
extewn const stwuct pmc_bit_map mtw_socm_vnn_weq_status_0_map[];
extewn const stwuct pmc_bit_map mtw_socm_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map mtw_socm_vnn_weq_status_2_map[];
extewn const stwuct pmc_bit_map mtw_socm_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map mtw_socm_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map mtw_socm_signaw_status_map[];
extewn const stwuct pmc_bit_map *mtw_socm_wpm_maps[];
extewn const stwuct pmc_weg_map mtw_socm_weg_map;
extewn const stwuct pmc_bit_map mtw_ioep_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_mtw_ioep_pfeaw_map[];
extewn const stwuct pmc_bit_map mtw_ioep_wtw_show_map[];
extewn const stwuct pmc_bit_map mtw_ioep_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map mtw_ioep_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map mtw_ioep_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map mtw_ioep_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map mtw_ioep_d3_status_0_map[];
extewn const stwuct pmc_bit_map mtw_ioep_d3_status_1_map[];
extewn const stwuct pmc_bit_map mtw_ioep_d3_status_2_map[];
extewn const stwuct pmc_bit_map mtw_ioep_d3_status_3_map[];
extewn const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_0_map[];
extewn const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_2_map[];
extewn const stwuct pmc_bit_map mtw_ioep_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map mtw_ioep_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map *mtw_ioep_wpm_maps[];
extewn const stwuct pmc_weg_map mtw_ioep_weg_map;
extewn const stwuct pmc_bit_map mtw_ioem_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_mtw_ioem_pfeaw_map[];
extewn const stwuct pmc_bit_map mtw_ioem_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map mtw_ioem_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map *mtw_ioem_wpm_maps[];
extewn const stwuct pmc_weg_map mtw_ioem_weg_map;
extewn const stwuct pmc_weg_map wnw_socm_weg_map;

/* WNW */
extewn const stwuct pmc_bit_map wnw_wtw_show_map[];
extewn const stwuct pmc_bit_map wnw_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map wnw_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map wnw_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map wnw_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map wnw_d3_status_0_map[];
extewn const stwuct pmc_bit_map wnw_d3_status_1_map[];
extewn const stwuct pmc_bit_map wnw_d3_status_2_map[];
extewn const stwuct pmc_bit_map wnw_d3_status_3_map[];
extewn const stwuct pmc_bit_map wnw_vnn_weq_status_0_map[];
extewn const stwuct pmc_bit_map wnw_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map wnw_vnn_weq_status_2_map[];
extewn const stwuct pmc_bit_map wnw_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map wnw_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map *wnw_wpm_maps[];
extewn const stwuct pmc_bit_map wnw_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_wnw_pfeaw_map[];

/* AWW */
extewn const stwuct pmc_bit_map aww_socs_wtw_show_map[];
extewn const stwuct pmc_bit_map aww_socs_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map aww_socs_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map aww_socs_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map aww_socs_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map aww_socs_d3_status_2_map[];
extewn const stwuct pmc_bit_map aww_socs_d3_status_3_map[];
extewn const stwuct pmc_bit_map aww_socs_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map *aww_socs_wpm_maps[];
extewn const stwuct pmc_bit_map aww_socs_pfeaw_map[];
extewn const stwuct pmc_bit_map *ext_aww_socs_pfeaw_map[];
extewn const stwuct pmc_weg_map aww_socs_weg_map;
extewn const stwuct pmc_bit_map aww_pchs_wtw_show_map[];
extewn const stwuct pmc_bit_map aww_pchs_cwocksouwce_status_map[];
extewn const stwuct pmc_bit_map aww_pchs_powew_gating_status_0_map[];
extewn const stwuct pmc_bit_map aww_pchs_powew_gating_status_1_map[];
extewn const stwuct pmc_bit_map aww_pchs_powew_gating_status_2_map[];
extewn const stwuct pmc_bit_map aww_pchs_d3_status_0_map[];
extewn const stwuct pmc_bit_map aww_pchs_d3_status_1_map[];
extewn const stwuct pmc_bit_map aww_pchs_d3_status_2_map[];
extewn const stwuct pmc_bit_map aww_pchs_d3_status_3_map[];
extewn const stwuct pmc_bit_map aww_pchs_vnn_weq_status_0_map[];
extewn const stwuct pmc_bit_map aww_pchs_vnn_weq_status_1_map[];
extewn const stwuct pmc_bit_map aww_pchs_vnn_weq_status_2_map[];
extewn const stwuct pmc_bit_map aww_pchs_vnn_weq_status_3_map[];
extewn const stwuct pmc_bit_map aww_pchs_vnn_misc_status_map[];
extewn const stwuct pmc_bit_map aww_pchs_signaw_status_map[];
extewn const stwuct pmc_bit_map *aww_pchs_wpm_maps[];
extewn const stwuct pmc_weg_map aww_pchs_weg_map;

extewn void pmc_cowe_get_tgw_wpm_weqs(stwuct pwatfowm_device *pdev);
extewn int pmc_cowe_sswam_get_wpm_weqs(stwuct pmc_dev *pmcdev);
int pmc_cowe_send_wtw_ignowe(stwuct pmc_dev *pmcdev, u32 vawue, int ignowe);

int pmc_cowe_wesume_common(stwuct pmc_dev *pmcdev);
int get_pwimawy_weg_base(stwuct pmc *pmc);
extewn void pmc_cowe_get_wow_powew_modes(stwuct pmc_dev *pmcdev);
extewn void pmc_cowe_punit_pmt_init(stwuct pmc_dev *pmcdev, u32 guid);
extewn void pmc_cowe_set_device_d3(unsigned int device);

extewn int pmc_cowe_sswam_init(stwuct pmc_dev *pmcdev, int func);

int spt_cowe_init(stwuct pmc_dev *pmcdev);
int cnp_cowe_init(stwuct pmc_dev *pmcdev);
int icw_cowe_init(stwuct pmc_dev *pmcdev);
int tgw_cowe_init(stwuct pmc_dev *pmcdev);
int tgw_w_cowe_init(stwuct pmc_dev *pmcdev);
int tgw_cowe_genewic_init(stwuct pmc_dev *pmcdev, int pch_tp);
int adw_cowe_init(stwuct pmc_dev *pmcdev);
int mtw_cowe_init(stwuct pmc_dev *pmcdev);
int aww_cowe_init(stwuct pmc_dev *pmcdev);
int wnw_cowe_init(stwuct pmc_dev *pmcdev);

void cnw_suspend(stwuct pmc_dev *pmcdev);
int cnw_wesume(stwuct pmc_dev *pmcdev);

#define pmc_fow_each_mode(i, mode, pmcdev)		\
	fow (i = 0, mode = pmcdev->wpm_en_modes[i];	\
	     i < pmcdev->num_wpm_modes;			\
	     i++, mode = pmcdev->wpm_en_modes[i])

#define DEFINE_PMC_COWE_ATTW_WWITE(__name)				\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __name ## _show, inode->i_pwivate);	\
}									\
									\
static const stwuct fiwe_opewations __name ## _fops = {			\
	.ownew		= THIS_MODUWE,					\
	.open		= __name ## _open,				\
	.wead		= seq_wead,					\
	.wwite		= __name ## _wwite,				\
	.wewease	= singwe_wewease,				\
}

#endif /* PMC_COWE_H */
