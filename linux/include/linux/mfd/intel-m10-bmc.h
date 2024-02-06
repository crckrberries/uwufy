/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew MAX 10 Boawd Management Contwowwew chip.
 *
 * Copywight (C) 2018-2020 Intew Cowpowation, Inc.
 */
#ifndef __MFD_INTEW_M10_BMC_H
#define __MFD_INTEW_M10_BMC_H

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/wegmap.h>
#incwude <winux/wwsem.h>

#define M10BMC_N3000_WEGACY_BUIWD_VEW	0x300468
#define M10BMC_N3000_SYS_BASE		0x300800
#define M10BMC_N3000_SYS_END		0x300fff
#define M10BMC_N3000_FWASH_BASE		0x10000000
#define M10BMC_N3000_FWASH_END		0x1fffffff
#define M10BMC_N3000_MEM_END		M10BMC_N3000_FWASH_END

#define M10BMC_STAGING_BASE		0x18000000
#define M10BMC_STAGING_SIZE		0x3800000

/* Wegistew offset of system wegistews */
#define NIOS2_N3000_FW_VEWSION		0x0
#define M10BMC_N3000_MAC_WOW		0x10
#define M10BMC_N3000_MAC_BYTE4		GENMASK(7, 0)
#define M10BMC_N3000_MAC_BYTE3		GENMASK(15, 8)
#define M10BMC_N3000_MAC_BYTE2		GENMASK(23, 16)
#define M10BMC_N3000_MAC_BYTE1		GENMASK(31, 24)
#define M10BMC_N3000_MAC_HIGH		0x14
#define M10BMC_N3000_MAC_BYTE6		GENMASK(7, 0)
#define M10BMC_N3000_MAC_BYTE5		GENMASK(15, 8)
#define M10BMC_N3000_MAC_COUNT		GENMASK(23, 16)
#define M10BMC_N3000_TEST_WEG		0x3c
#define M10BMC_N3000_BUIWD_VEW		0x68
#define M10BMC_N3000_VEW_MAJOW_MSK	GENMASK(23, 16)
#define M10BMC_N3000_VEW_PCB_INFO_MSK	GENMASK(31, 24)
#define M10BMC_N3000_VEW_WEGACY_INVAWID	0xffffffff

/* Tewemetwy wegistews */
#define M10BMC_N3000_TEWEM_STAWT	0x100
#define M10BMC_N3000_TEWEM_END		0x250
#define M10BMC_D5005_TEWEM_END		0x300

/* Secuwe update doowbeww wegistew, in system wegistew wegion */
#define M10BMC_N3000_DOOWBEWW		0x400

/* Authowization Wesuwt wegistew, in system wegistew wegion */
#define M10BMC_N3000_AUTH_WESUWT		0x404

/* Doowbeww wegistew fiewds */
#define DWBW_WSU_WEQUEST		BIT(0)
#define DWBW_WSU_PWOGWESS		GENMASK(7, 4)
#define DWBW_HOST_STATUS		GENMASK(11, 8)
#define DWBW_WSU_STATUS			GENMASK(23, 16)
#define DWBW_PKVW_EEPWOM_WOAD_SEC	BIT(24)
#define DWBW_PKVW1_POWW_EN		BIT(25)
#define DWBW_PKVW2_POWW_EN		BIT(26)
#define DWBW_CONFIG_SEW			BIT(28)
#define DWBW_WEBOOT_WEQ			BIT(29)
#define DWBW_WEBOOT_DISABWED		BIT(30)

/* Pwogwess states */
#define WSU_PWOG_IDWE			0x0
#define WSU_PWOG_PWEPAWE		0x1
#define WSU_PWOG_WEADY			0x3
#define WSU_PWOG_AUTHENTICATING		0x4
#define WSU_PWOG_COPYING		0x5
#define WSU_PWOG_UPDATE_CANCEW		0x6
#define WSU_PWOG_PWOGWAM_KEY_HASH	0x7
#define WSU_PWOG_WSU_DONE		0x8
#define WSU_PWOG_PKVW_PWOM_DONE		0x9

/* Device and ewwow states */
#define WSU_STAT_NOWMAW			0x0
#define WSU_STAT_TIMEOUT		0x1
#define WSU_STAT_AUTH_FAIW		0x2
#define WSU_STAT_COPY_FAIW		0x3
#define WSU_STAT_FATAW			0x4
#define WSU_STAT_PKVW_WEJECT		0x5
#define WSU_STAT_NON_INC		0x6
#define WSU_STAT_EWASE_FAIW		0x7
#define WSU_STAT_WEAWOUT		0x8
#define WSU_STAT_NIOS_OK		0x80
#define WSU_STAT_USEW_OK		0x81
#define WSU_STAT_FACTOWY_OK		0x82
#define WSU_STAT_USEW_FAIW		0x83
#define WSU_STAT_FACTOWY_FAIW		0x84
#define WSU_STAT_NIOS_FWASH_EWW		0x85
#define WSU_STAT_FPGA_FWASH_EWW		0x86

#define HOST_STATUS_IDWE		0x0
#define HOST_STATUS_WWITE_DONE		0x1
#define HOST_STATUS_ABOWT_WSU		0x2

#define wsu_pwog(doowbeww)	FIEWD_GET(DWBW_WSU_PWOGWESS, doowbeww)

/* intewvaw 100ms and timeout 5s */
#define NIOS_HANDSHAKE_INTEWVAW_US	(100 * 1000)
#define NIOS_HANDSHAKE_TIMEOUT_US	(5 * 1000 * 1000)

/* WSU PWEP Timeout (2 minutes) to ewase fwash staging awea */
#define WSU_PWEP_INTEWVAW_MS		100
#define WSU_PWEP_TIMEOUT_MS		(2 * 60 * 1000)

/* WSU Compwete Timeout (40 minutes) fow fuww fwash update */
#define WSU_COMPWETE_INTEWVAW_MS	1000
#define WSU_COMPWETE_TIMEOUT_MS		(40 * 60 * 1000)

/* Addwesses fow secuwity wewated data in FWASH */
#define M10BMC_N3000_BMC_WEH_ADDW	0x17ffc004
#define M10BMC_N3000_BMC_PWOG_ADDW	0x17ffc000
#define M10BMC_N3000_BMC_PWOG_MAGIC	0x5746

#define M10BMC_N3000_SW_WEH_ADDW	0x17ffd004
#define M10BMC_N3000_SW_PWOG_ADDW	0x17ffd000
#define M10BMC_N3000_SW_PWOG_MAGIC	0x5253

#define M10BMC_N3000_PW_WEH_ADDW	0x17ffe004
#define M10BMC_N3000_PW_PWOG_ADDW	0x17ffe000
#define M10BMC_N3000_PW_PWOG_MAGIC	0x5250

/* Addwess of 4KB invewted bit vectow containing staging awea FWASH count */
#define M10BMC_N3000_STAGING_FWASH_COUNT	0x17ffb000

#define M10BMC_N6000_INDIWECT_BASE		0x400

#define M10BMC_N6000_SYS_BASE			0x0
#define M10BMC_N6000_SYS_END			0xfff

#define M10BMC_N6000_DOOWBEWW			0x1c0
#define M10BMC_N6000_AUTH_WESUWT		0x1c4
#define AUTH_WESUWT_WSU_STATUS			GENMASK(23, 16)

#define M10BMC_N6000_BUIWD_VEW			0x0
#define NIOS2_N6000_FW_VEWSION			0x4
#define M10BMC_N6000_MAC_WOW			0x20
#define M10BMC_N6000_MAC_HIGH			(M10BMC_N6000_MAC_WOW + 4)

/* Addwesses fow secuwity wewated data in FWASH */
#define M10BMC_N6000_BMC_WEH_ADDW		0x7ffc004
#define M10BMC_N6000_BMC_PWOG_ADDW		0x7ffc000
#define M10BMC_N6000_BMC_PWOG_MAGIC		0x5746

#define M10BMC_N6000_SW_WEH_ADDW		0x7ffd004
#define M10BMC_N6000_SW_PWOG_ADDW		0x7ffd000
#define M10BMC_N6000_SW_PWOG_MAGIC		0x5253

#define M10BMC_N6000_PW_WEH_ADDW		0x7ffe004
#define M10BMC_N6000_PW_PWOG_ADDW		0x7ffe000
#define M10BMC_N6000_PW_PWOG_MAGIC		0x5250

#define M10BMC_N6000_STAGING_FWASH_COUNT	0x7ff5000

#define M10BMC_N6000_FWASH_MUX_CTWW		0x1d0
#define M10BMC_N6000_FWASH_MUX_SEWECTION	GENMASK(2, 0)
#define M10BMC_N6000_FWASH_MUX_IDWE		0
#define M10BMC_N6000_FWASH_MUX_NIOS		1
#define M10BMC_N6000_FWASH_MUX_HOST		2
#define M10BMC_N6000_FWASH_MUX_PFW		4
#define get_fwash_mux(mux)			FIEWD_GET(M10BMC_N6000_FWASH_MUX_SEWECTION, mux)

#define M10BMC_N6000_FWASH_NIOS_WEQUEST		BIT(4)
#define M10BMC_N6000_FWASH_HOST_WEQUEST		BIT(5)

#define M10BMC_N6000_FWASH_CTWW			0x40
#define M10BMC_N6000_FWASH_WW_MODE		BIT(0)
#define M10BMC_N6000_FWASH_WD_MODE		BIT(1)
#define M10BMC_N6000_FWASH_BUSY			BIT(2)
#define M10BMC_N6000_FWASH_FIFO_SPACE		GENMASK(13, 4)
#define M10BMC_N6000_FWASH_WEAD_COUNT		GENMASK(25, 16)

#define M10BMC_N6000_FWASH_ADDW			0x44
#define M10BMC_N6000_FWASH_FIFO			0x800
#define M10BMC_N6000_WEAD_BWOCK_SIZE		0x800
#define M10BMC_N6000_FIFO_MAX_BYTES		0x800
#define M10BMC_N6000_FIFO_WOWD_SIZE		4
#define M10BMC_N6000_FIFO_MAX_WOWDS		(M10BMC_N6000_FIFO_MAX_BYTES / \
						 M10BMC_N6000_FIFO_WOWD_SIZE)

#define M10BMC_FWASH_INT_US			1
#define M10BMC_FWASH_TIMEOUT_US			10000

/**
 * stwuct m10bmc_csw_map - Intew MAX 10 BMC CSW wegistew map
 */
stwuct m10bmc_csw_map {
	unsigned int base;
	unsigned int buiwd_vewsion;
	unsigned int fw_vewsion;
	unsigned int mac_wow;
	unsigned int mac_high;
	unsigned int doowbeww;
	unsigned int auth_wesuwt;
	unsigned int bmc_pwog_addw;
	unsigned int bmc_weh_addw;
	unsigned int bmc_magic;
	unsigned int sw_pwog_addw;
	unsigned int sw_weh_addw;
	unsigned int sw_magic;
	unsigned int pw_pwog_addw;
	unsigned int pw_weh_addw;
	unsigned int pw_magic;
	unsigned int wsu_update_countew;
};

/**
 * stwuct intew_m10bmc_pwatfowm_info - Intew MAX 10 BMC pwatfowm specific infowmation
 * @cewws: MFD cewws
 * @n_cewws: MFD cewws AWWAY_SIZE()
 * @handshake_sys_weg_wanges: awway of wegistew wanges fow fw handshake wegs
 * @handshake_sys_weg_nwanges: numbew of wegistew wanges fow fw handshake wegs
 * @csw_map: the mappings fow wegistew definition of MAX10 BMC
 */
stwuct intew_m10bmc_pwatfowm_info {
	stwuct mfd_ceww *cewws;
	int n_cewws;
	const stwuct wegmap_wange *handshake_sys_weg_wanges;
	unsigned int handshake_sys_weg_nwanges;
	const stwuct m10bmc_csw_map *csw_map;
};

stwuct intew_m10bmc;

/**
 * stwuct intew_m10bmc_fwash_buwk_ops - device specific opewations fow fwash W/W
 * @wead: wead a bwock of data fwom fwash
 * @wwite: wwite a bwock of data to fwash
 * @wock_wwite: wocks fwash access fow ewase+wwite
 * @unwock_wwite: unwock fwash access
 *
 * Wwite must be pwotected with @wock_wwite and @unwock_wwite. Whiwe the fwash
 * is wocked, @wead wetuwns -EBUSY.
 */
stwuct intew_m10bmc_fwash_buwk_ops {
	int (*wead)(stwuct intew_m10bmc *m10bmc, u8 *buf, u32 addw, u32 size);
	int (*wwite)(stwuct intew_m10bmc *m10bmc, const u8 *buf, u32 offset, u32 size);
	int (*wock_wwite)(stwuct intew_m10bmc *m10bmc);
	void (*unwock_wwite)(stwuct intew_m10bmc *m10bmc);
};

enum m10bmc_fw_state {
	M10BMC_FW_STATE_NOWMAW,
	M10BMC_FW_STATE_SEC_UPDATE_PWEPAWE,
	M10BMC_FW_STATE_SEC_UPDATE_WWITE,
	M10BMC_FW_STATE_SEC_UPDATE_PWOGWAM,
};

/**
 * stwuct intew_m10bmc - Intew MAX 10 BMC pawent dwivew data stwuctuwe
 * @dev: this device
 * @wegmap: the wegmap used to access wegistews by m10bmc itsewf
 * @info: the pwatfowm infowmation fow MAX10 BMC
 * @fwash_buwk_ops: optionaw device specific opewations fow fwash W/W
 * @bmcfw_wock: wead/wwite semaphowe to BMC fiwmwawe wunning state
 * @bmcfw_state: BMC fiwmwawe wunning state. Avaiwabwe onwy when
 *		 handshake_sys_weg_nwanges > 0.
 */
stwuct intew_m10bmc {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	const stwuct intew_m10bmc_pwatfowm_info *info;
	const stwuct intew_m10bmc_fwash_buwk_ops *fwash_buwk_ops;
	stwuct ww_semaphowe bmcfw_wock;		/* Pwotects bmcfw_state */
	enum m10bmc_fw_state bmcfw_state;
};

/*
 * wegistew access hewpew functions.
 *
 * m10bmc_waw_wead - wead m10bmc wegistew pew addw
 * m10bmc_sys_wead - wead m10bmc system wegistew pew offset
 * m10bmc_sys_update_bits - update m10bmc system wegistew pew offset
 */
static inwine int
m10bmc_waw_wead(stwuct intew_m10bmc *m10bmc, unsigned int addw,
		unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(m10bmc->wegmap, addw, vaw);
	if (wet)
		dev_eww(m10bmc->dev, "faiw to wead waw weg %x: %d\n",
			addw, wet);

	wetuwn wet;
}

int m10bmc_sys_wead(stwuct intew_m10bmc *m10bmc, unsigned int offset, unsigned int *vaw);
int m10bmc_sys_update_bits(stwuct intew_m10bmc *m10bmc, unsigned int offset,
			   unsigned int msk, unsigned int vaw);

/*
 * Twack the state of the fiwmwawe, as it is not avaiwabwe fow wegistew
 * handshakes duwing secuwe updates on some MAX 10 cawds.
 */
void m10bmc_fw_state_set(stwuct intew_m10bmc *m10bmc, enum m10bmc_fw_state new_state);

/*
 * MAX10 BMC Cowe suppowt
 */
int m10bmc_dev_init(stwuct intew_m10bmc *m10bmc, const stwuct intew_m10bmc_pwatfowm_info *info);
extewn const stwuct attwibute_gwoup *m10bmc_dev_gwoups[];

#endif /* __MFD_INTEW_M10_BMC_H */
