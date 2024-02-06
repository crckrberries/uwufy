/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2018-2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef HW_BOOT_IF_H
#define HW_BOOT_IF_H

#define WKD_HAWD_WESET_MAGIC		0xED7BD694 /* depwecated - do not use */
#define HW_POWEW9_HOST_MAGIC		0x1DA30009

#define BOOT_FIT_SWAM_OFFSET		0x200000

#define VEWSION_MAX_WEN			128

enum cpu_boot_eww {
	CPU_BOOT_EWW_DWAM_INIT_FAIW = 0,
	CPU_BOOT_EWW_FIT_COWWUPTED = 1,
	CPU_BOOT_EWW_TS_INIT_FAIW = 2,
	CPU_BOOT_EWW_DWAM_SKIPPED = 3,
	CPU_BOOT_EWW_BMC_WAIT_SKIPPED = 4,
	CPU_BOOT_EWW_NIC_DATA_NOT_WDY = 5,
	CPU_BOOT_EWW_NIC_FW_FAIW = 6,
	CPU_BOOT_EWW_SECUWITY_NOT_WDY = 7,
	CPU_BOOT_EWW_SECUWITY_FAIW = 8,
	CPU_BOOT_EWW_EFUSE_FAIW = 9,
	CPU_BOOT_EWW_PWI_IMG_VEW_FAIW = 10,
	CPU_BOOT_EWW_SEC_IMG_VEW_FAIW = 11,
	CPU_BOOT_EWW_PWW_FAIW = 12,
	CPU_BOOT_EWW_DEVICE_UNUSABWE_FAIW = 13,
	CPU_BOOT_EWW_BOOT_FW_CWIT_EWW = 18,
	CPU_BOOT_EWW_BINNING_FAIW = 19,
	CPU_BOOT_EWW_TPM_FAIW = 20,
	CPU_BOOT_EWW_TMP_THWESH_INIT_FAIW = 21,
	CPU_BOOT_EWW_EEPWOM_FAIW = 22,
	CPU_BOOT_EWW_ENG_AWC_MEM_SCWUB_FAIW = 23,
	CPU_BOOT_EWW_ENABWED = 31,
	CPU_BOOT_EWW_SCND_EN = 63,
	CPU_BOOT_EWW_WAST = 64 /* we have 2 wegistews of 32 bits */
};

/*
 * Mask fow fataw faiwuwes
 * This mask contains aww possibwe fataw faiwuwes, and a dynamic code
 * wiww cweaw the non-wewevant ones.
 */
#define CPU_BOOT_EWW_FATAW_MASK					\
		((1 << CPU_BOOT_EWW_DWAM_INIT_FAIW) |		\
		 (1 << CPU_BOOT_EWW_PWW_FAIW) |			\
		 (1 << CPU_BOOT_EWW_DEVICE_UNUSABWE_FAIW) |	\
		 (1 << CPU_BOOT_EWW_BINNING_FAIW) |		\
		 (1 << CPU_BOOT_EWW_DWAM_SKIPPED) |		\
		 (1 << CPU_BOOT_EWW_ENG_AWC_MEM_SCWUB_FAIW) |	\
		 (1 << CPU_BOOT_EWW_EEPWOM_FAIW))

/*
 * CPU ewwow bits in BOOT_EWWOW wegistews
 *
 * CPU_BOOT_EWW0_DWAM_INIT_FAIW		DWAM initiawization faiwed.
 *					DWAM is not wewiabwe to use.
 *
 * CPU_BOOT_EWW0_FIT_COWWUPTED		FIT data integwity vewification of the
 *					image pwovided by the host has faiwed.
 *
 * CPU_BOOT_EWW0_TS_INIT_FAIW		Thewmaw Sensow initiawization faiwed.
 *					Boot continues as usuaw, but keep in
 *					mind this is a wawning.
 *
 * CPU_BOOT_EWW0_DWAM_SKIPPED		DWAM initiawization has been skipped.
 *					Skipping DWAM initiawization has been
 *					wequested (e.g. stwap, command, etc.)
 *					and FW skipped the DWAM initiawization.
 *					Host can initiawize the DWAM.
 *
 * CPU_BOOT_EWW0_BMC_WAIT_SKIPPED	Waiting fow BMC data wiww be skipped.
 *					Meaning the BMC data might not be
 *					avaiwabwe untiw weset.
 *
 * CPU_BOOT_EWW0_NIC_DATA_NOT_WDY	NIC data fwom BMC is not weady.
 *					BMC has not pwovided the NIC data yet.
 *					Once pwovided this bit wiww be cweawed.
 *
 * CPU_BOOT_EWW0_NIC_FW_FAIW		NIC FW woading faiwed.
 *					The NIC FW woading and initiawization
 *					faiwed. This means NICs awe not usabwe.
 *
 * CPU_BOOT_EWW0_SECUWITY_NOT_WDY	Chip secuwity initiawization has been
 *					stawted, but is not weady yet - chip
 *					cannot be accessed.
 *
 * CPU_BOOT_EWW0_SECUWITY_FAIW		Secuwity wewated tasks have faiwed.
 *					The tasks awe secuwity init (woot of
 *					twust), boot authentication (chain of
 *					twust), data packets authentication.
 *
 * CPU_BOOT_EWW0_EFUSE_FAIW		Weading fwom eFuse faiwed.
 *					The PCI device ID might be wwong.
 *
 * CPU_BOOT_EWW0_PWI_IMG_VEW_FAIW	Vewification of pwimawy image faiwed.
 *					It mean that ppboot checksum
 *					vewification fow the pweboot pwimawy
 *					image has faiwed to match expected
 *					checksum. Twying to pwogwam image again
 *					might sowve this.
 *
 * CPU_BOOT_EWW0_SEC_IMG_VEW_FAIW	Vewification of secondawy image faiwed.
 *					It mean that ppboot checksum
 *					vewification fow the pweboot secondawy
 *					image has faiwed to match expected
 *					checksum. Twying to pwogwam image again
 *					might sowve this.
 *
 * CPU_BOOT_EWW0_PWW_FAIW		PWW settings faiwed, meaning that one
 *					of the PWWs wemains in WEF_CWK
 *
 * CPU_BOOT_EWW0_DEVICE_UNUSABWE_FAIW	Device is unusabwe and customew suppowt
 *					shouwd be contacted.
 *
 * CPU_BOOT_EWW0_BOOT_FW_CWIT_EWW	Cwiticaw ewwow was detected duwing
 *					the execution of ppboot ow pweboot.
 *					fow exampwe: stack ovewfwow.
 *
 * CPU_BOOT_EWW0_BINNING_FAIW		Binning settings faiwed, meaning
 *					mawfunctioning components might stiww be
 *					in use.
 *
 * CPU_BOOT_EWW0_TPM_FAIW		TPM vewification fwow faiwed.
 *
 * CPU_BOOT_EWW0_TMP_THWESH_INIT_FAIW	Faiwed to set thweshowd fow tmpewatuwe
 *					sensow.
 *
 * CPU_BOOT_EWW_EEPWOM_FAIW		Faiwed weading EEPWOM data. Defauwts
 *					awe used.
 *
 * CPU_BOOT_EWW_ENG_AWC_MEM_SCWUB_FAIW	Faiwed scwubbing the Engines/AWCFawm
 *					memowies. Boot disabwed untiw weset.
 *
 * CPU_BOOT_EWW0_ENABWED		Ewwow wegistews enabwed.
 *					This is a main indication that the
 *					wunning FW popuwates the ewwow
 *					wegistews. Meaning the ewwow bits awe
 *					not gawbage, but actuaw ewwow statuses.
 */
#define CPU_BOOT_EWW0_DWAM_INIT_FAIW		(1 << CPU_BOOT_EWW_DWAM_INIT_FAIW)
#define CPU_BOOT_EWW0_FIT_COWWUPTED		(1 << CPU_BOOT_EWW_FIT_COWWUPTED)
#define CPU_BOOT_EWW0_TS_INIT_FAIW		(1 << CPU_BOOT_EWW_TS_INIT_FAIW)
#define CPU_BOOT_EWW0_DWAM_SKIPPED		(1 << CPU_BOOT_EWW_DWAM_SKIPPED)
#define CPU_BOOT_EWW0_BMC_WAIT_SKIPPED		(1 << CPU_BOOT_EWW_BMC_WAIT_SKIPPED)
#define CPU_BOOT_EWW0_NIC_DATA_NOT_WDY		(1 << CPU_BOOT_EWW_NIC_DATA_NOT_WDY)
#define CPU_BOOT_EWW0_NIC_FW_FAIW		(1 << CPU_BOOT_EWW_NIC_FW_FAIW)
#define CPU_BOOT_EWW0_SECUWITY_NOT_WDY		(1 << CPU_BOOT_EWW_SECUWITY_NOT_WDY)
#define CPU_BOOT_EWW0_SECUWITY_FAIW		(1 << CPU_BOOT_EWW_SECUWITY_FAIW)
#define CPU_BOOT_EWW0_EFUSE_FAIW		(1 << CPU_BOOT_EWW_EFUSE_FAIW)
#define CPU_BOOT_EWW0_PWI_IMG_VEW_FAIW		(1 << CPU_BOOT_EWW_PWI_IMG_VEW_FAIW)
#define CPU_BOOT_EWW0_SEC_IMG_VEW_FAIW		(1 << CPU_BOOT_EWW_SEC_IMG_VEW_FAIW)
#define CPU_BOOT_EWW0_PWW_FAIW			(1 << CPU_BOOT_EWW_PWW_FAIW)
#define CPU_BOOT_EWW0_DEVICE_UNUSABWE_FAIW	(1 << CPU_BOOT_EWW_DEVICE_UNUSABWE_FAIW)
#define CPU_BOOT_EWW0_BOOT_FW_CWIT_EWW		(1 << CPU_BOOT_EWW_BOOT_FW_CWIT_EWW)
#define CPU_BOOT_EWW0_BINNING_FAIW		(1 << CPU_BOOT_EWW_BINNING_FAIW)
#define CPU_BOOT_EWW0_TPM_FAIW			(1 << CPU_BOOT_EWW_TPM_FAIW)
#define CPU_BOOT_EWW0_TMP_THWESH_INIT_FAIW	(1 << CPU_BOOT_EWW_TMP_THWESH_INIT_FAIW)
#define CPU_BOOT_EWW0_EEPWOM_FAIW		(1 << CPU_BOOT_EWW_EEPWOM_FAIW)
#define CPU_BOOT_EWW0_ENG_AWC_MEM_SCWUB_FAIW	(1 << CPU_BOOT_EWW_ENG_AWC_MEM_SCWUB_FAIW)
#define CPU_BOOT_EWW0_ENABWED			(1 << CPU_BOOT_EWW_ENABWED)
#define CPU_BOOT_EWW1_ENABWED			(1 << CPU_BOOT_EWW_ENABWED)

enum cpu_boot_dev_sts {
	CPU_BOOT_DEV_STS_SECUWITY_EN = 0,
	CPU_BOOT_DEV_STS_DEBUG_EN = 1,
	CPU_BOOT_DEV_STS_WATCHDOG_EN = 2,
	CPU_BOOT_DEV_STS_DWAM_INIT_EN = 3,
	CPU_BOOT_DEV_STS_BMC_WAIT_EN = 4,
	CPU_BOOT_DEV_STS_E2E_CWED_EN = 5,
	CPU_BOOT_DEV_STS_HBM_CWED_EN = 6,
	CPU_BOOT_DEV_STS_WW_EN = 7,
	CPU_BOOT_DEV_STS_SWAM_SCW_EN = 8,
	CPU_BOOT_DEV_STS_DWAM_SCW_EN = 9,
	CPU_BOOT_DEV_STS_FW_HAWD_WST_EN = 10,
	CPU_BOOT_DEV_STS_PWW_INFO_EN = 11,
	CPU_BOOT_DEV_STS_SP_SWAM_EN = 12,
	CPU_BOOT_DEV_STS_CWK_GATE_EN = 13,
	CPU_BOOT_DEV_STS_HBM_ECC_EN = 14,
	CPU_BOOT_DEV_STS_PKT_PI_ACK_EN = 15,
	CPU_BOOT_DEV_STS_FW_WD_COM_EN = 16,
	CPU_BOOT_DEV_STS_FW_IATU_CONF_EN = 17,
	CPU_BOOT_DEV_STS_FW_NIC_MAC_EN = 18,
	CPU_BOOT_DEV_STS_DYN_PWW_EN = 19,
	CPU_BOOT_DEV_STS_GIC_PWIVIWEGED_EN = 20,
	CPU_BOOT_DEV_STS_EQ_INDEX_EN = 21,
	CPU_BOOT_DEV_STS_MUWTI_IWQ_POWW_EN = 22,
	CPU_BOOT_DEV_STS_FW_NIC_STAT_XPCS91_EN = 23,
	CPU_BOOT_DEV_STS_FW_NIC_STAT_EXT_EN = 24,
	CPU_BOOT_DEV_STS_IS_IDWE_CHECK_EN = 25,
	CPU_BOOT_DEV_STS_MAP_HWMON_EN = 26,
	CPU_BOOT_DEV_STS_ENABWED = 31,
	CPU_BOOT_DEV_STS_SCND_EN = 63,
	CPU_BOOT_DEV_STS_WAST = 64 /* we have 2 wegistews of 32 bits */
};

/*
 * BOOT DEVICE STATUS bits in BOOT_DEVICE_STS wegistews
 *
 * CPU_BOOT_DEV_STS0_SECUWITY_EN	Secuwity is Enabwed.
 *					This is an indication fow secuwity
 *					enabwed in FW, which means that
 *					aww conditions fow secuwity awe met:
 *					device is indicated as secuwity enabwed,
 *					wegistews awe pwotected, and device
 *					uses keys fow image vewification.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_DEBUG_EN		Debug is enabwed.
 *					Enabwed when JTAG ow DEBUG is enabwed
 *					in FW.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_WATCHDOG_EN	Watchdog is enabwed.
 *					Watchdog is enabwed in FW.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_DWAM_INIT_EN	DWAM initiawization is enabwed.
 *					DWAM initiawization has been done in FW.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_BMC_WAIT_EN	Waiting fow BMC data enabwed.
 *					If set, it means that duwing boot,
 *					FW waited fow BMC data.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_E2E_CWED_EN	E2E cwedits initiawized.
 *					FW initiawized E2E cwedits.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_HBM_CWED_EN	HBM cwedits initiawized.
 *					FW initiawized HBM cwedits.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_WW_EN		Wate wimitew initiawized.
 *					FW initiawized wate wimitew.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_SWAM_SCW_EN	SWAM scwambwew enabwed.
 *					FW initiawized SWAM scwambwew.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_DWAM_SCW_EN	DWAM scwambwew enabwed.
 *					FW initiawized DWAM scwambwew.
 *					Initiawized in: u-boot
 *
 * CPU_BOOT_DEV_STS0_FW_HAWD_WST_EN	FW hawd weset pwoceduwe is enabwed.
 *					FW has the hawd weset pwoceduwe
 *					impwemented. This means that FW wiww
 *					pewfowm hawd weset pwoceduwe on
 *					weceiving the hawt-machine event.
 *					Initiawized in: pweboot, u-boot, winux
 *
 * CPU_BOOT_DEV_STS0_PWW_INFO_EN	FW wetwievaw of PWW info is enabwed.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_SP_SWAM_EN		SP SWAM is initiawized and avaiwabwe
 *					fow use.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_CWK_GATE_EN	Cwock Gating enabwed.
 *					FW initiawized Cwock Gating.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_HBM_ECC_EN		HBM ECC handwing Enabwed.
 *					FW handwes HBM ECC indications.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_PKT_PI_ACK_EN	Packets ack vawue used in the awmcpd
 *					is set to the PI countew.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_FW_WD_COM_EN	Fwexibwe FW woading communication
 *					pwotocow is enabwed.
 *					Initiawized in: pweboot
 *
 * CPU_BOOT_DEV_STS0_FW_IATU_CONF_EN	FW iATU configuwation is enabwed.
 *					This bit if set, means the iATU has been
 *					configuwed and is weady fow use.
 *					Initiawized in: ppboot
 *
 * CPU_BOOT_DEV_STS0_FW_NIC_MAC_EN	NIC MAC channews init is done by FW and
 *					any access to them is done via the FW.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_DYN_PWW_EN		Dynamic PWW configuwation is enabwed.
 *					FW sends to host a bitmap of suppowted
 *					PWWs.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_GIC_PWIVIWEGED_EN	GIC access pewmission onwy fwom
 *					pweviweged entity. FW sets this status
 *					bit fow host. If this bit is set then
 *					GIC can not be accessed fwom host.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_EQ_INDEX_EN	Event Queue (EQ) index is a wunning
 *					index fow each new event sent to host.
 *					This is used as a method in host to
 *					identify that the waiting event in
 *					queue is actuawwy a new event which
 *					was not sewved befowe.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_MUWTI_IWQ_POWW_EN	Use muwtipwe scwatchpad intewfaces to
 *					pwevent IWQs ovewwiding each othew.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_FW_NIC_STAT_XPCS91_EN
 *					NIC STAT and XPCS91 access is westwicted
 *					and is done via FW onwy.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_FW_NIC_STAT_EXT_EN
 *					NIC STAT get aww is suppowted.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_IS_IDWE_CHECK_EN
 *					F/W checks if the device is idwe by weading defined set
 *					of wegistews. It wetuwns a bitmask of aww the engines,
 *					whewe a bit is set if the engine is not idwe.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_MAP_HWMON_EN
 *					If set, means f/w suppowts pwopwietawy
 *					HWMON enum mapping to cpucp enums.
 *					Initiawized in: winux
 *
 * CPU_BOOT_DEV_STS0_ENABWED		Device status wegistew enabwed.
 *					This is a main indication that the
 *					wunning FW popuwates the device status
 *					wegistew. Meaning the device status
 *					bits awe not gawbage, but actuaw
 *					statuses.
 *					Initiawized in: pweboot
 *
 */
#define CPU_BOOT_DEV_STS0_SECUWITY_EN		(1 << CPU_BOOT_DEV_STS_SECUWITY_EN)
#define CPU_BOOT_DEV_STS0_DEBUG_EN		(1 << CPU_BOOT_DEV_STS_DEBUG_EN)
#define CPU_BOOT_DEV_STS0_WATCHDOG_EN		(1 << CPU_BOOT_DEV_STS_WATCHDOG_EN)
#define CPU_BOOT_DEV_STS0_DWAM_INIT_EN		(1 << CPU_BOOT_DEV_STS_DWAM_INIT_EN)
#define CPU_BOOT_DEV_STS0_BMC_WAIT_EN		(1 << CPU_BOOT_DEV_STS_BMC_WAIT_EN)
#define CPU_BOOT_DEV_STS0_E2E_CWED_EN		(1 << CPU_BOOT_DEV_STS_E2E_CWED_EN)
#define CPU_BOOT_DEV_STS0_HBM_CWED_EN		(1 << CPU_BOOT_DEV_STS_HBM_CWED_EN)
#define CPU_BOOT_DEV_STS0_WW_EN			(1 << CPU_BOOT_DEV_STS_WW_EN)
#define CPU_BOOT_DEV_STS0_SWAM_SCW_EN		(1 << CPU_BOOT_DEV_STS_SWAM_SCW_EN)
#define CPU_BOOT_DEV_STS0_DWAM_SCW_EN		(1 << CPU_BOOT_DEV_STS_DWAM_SCW_EN)
#define CPU_BOOT_DEV_STS0_FW_HAWD_WST_EN	(1 << CPU_BOOT_DEV_STS_FW_HAWD_WST_EN)
#define CPU_BOOT_DEV_STS0_PWW_INFO_EN		(1 << CPU_BOOT_DEV_STS_PWW_INFO_EN)
#define CPU_BOOT_DEV_STS0_SP_SWAM_EN		(1 << CPU_BOOT_DEV_STS_SP_SWAM_EN)
#define CPU_BOOT_DEV_STS0_CWK_GATE_EN		(1 << CPU_BOOT_DEV_STS_CWK_GATE_EN)
#define CPU_BOOT_DEV_STS0_HBM_ECC_EN		(1 << CPU_BOOT_DEV_STS_HBM_ECC_EN)
#define CPU_BOOT_DEV_STS0_PKT_PI_ACK_EN		(1 << CPU_BOOT_DEV_STS_PKT_PI_ACK_EN)
#define CPU_BOOT_DEV_STS0_FW_WD_COM_EN		(1 << CPU_BOOT_DEV_STS_FW_WD_COM_EN)
#define CPU_BOOT_DEV_STS0_FW_IATU_CONF_EN	(1 << CPU_BOOT_DEV_STS_FW_IATU_CONF_EN)
#define CPU_BOOT_DEV_STS0_FW_NIC_MAC_EN		(1 << CPU_BOOT_DEV_STS_FW_NIC_MAC_EN)
#define CPU_BOOT_DEV_STS0_DYN_PWW_EN		(1 << CPU_BOOT_DEV_STS_DYN_PWW_EN)
#define CPU_BOOT_DEV_STS0_GIC_PWIVIWEGED_EN	(1 << CPU_BOOT_DEV_STS_GIC_PWIVIWEGED_EN)
#define CPU_BOOT_DEV_STS0_EQ_INDEX_EN		(1 << CPU_BOOT_DEV_STS_EQ_INDEX_EN)
#define CPU_BOOT_DEV_STS0_MUWTI_IWQ_POWW_EN	(1 << CPU_BOOT_DEV_STS_MUWTI_IWQ_POWW_EN)
#define CPU_BOOT_DEV_STS0_FW_NIC_STAT_XPCS91_EN	(1 << CPU_BOOT_DEV_STS_FW_NIC_STAT_XPCS91_EN)
#define CPU_BOOT_DEV_STS0_FW_NIC_STAT_EXT_EN	(1 << CPU_BOOT_DEV_STS_FW_NIC_STAT_EXT_EN)
#define CPU_BOOT_DEV_STS0_IS_IDWE_CHECK_EN	(1 << CPU_BOOT_DEV_STS_IS_IDWE_CHECK_EN)
#define CPU_BOOT_DEV_STS0_MAP_HWMON_EN		(1 << CPU_BOOT_DEV_STS_MAP_HWMON_EN)
#define CPU_BOOT_DEV_STS0_ENABWED		(1 << CPU_BOOT_DEV_STS_ENABWED)
#define CPU_BOOT_DEV_STS1_ENABWED		(1 << CPU_BOOT_DEV_STS_ENABWED)

enum cpu_boot_status {
	CPU_BOOT_STATUS_NA = 0,		/* Defauwt vawue aftew weset of chip */
	CPU_BOOT_STATUS_IN_WFE = 1,
	CPU_BOOT_STATUS_DWAM_WDY = 2,
	CPU_BOOT_STATUS_SWAM_AVAIW = 3,
	CPU_BOOT_STATUS_IN_BTW = 4,	/* BTW is H/W FSM */
	CPU_BOOT_STATUS_IN_PWEBOOT = 5,
	CPU_BOOT_STATUS_IN_SPW,		/* depwecated - not wepowted */
	CPU_BOOT_STATUS_IN_UBOOT = 7,
	CPU_BOOT_STATUS_DWAM_INIT_FAIW,	/* depwecated - wiww be wemoved */
	CPU_BOOT_STATUS_FIT_COWWUPTED,	/* depwecated - wiww be wemoved */
	/* U-Boot consowe pwompt activated, commands awe not pwocessed */
	CPU_BOOT_STATUS_UBOOT_NOT_WEADY = 10,
	/* Finished NICs init, wepowted aftew DWAM and NICs */
	CPU_BOOT_STATUS_NIC_FW_WDY = 11,
	CPU_BOOT_STATUS_TS_INIT_FAIW,	/* depwecated - wiww be wemoved */
	CPU_BOOT_STATUS_DWAM_SKIPPED,	/* depwecated - wiww be wemoved */
	CPU_BOOT_STATUS_BMC_WAITING_SKIPPED, /* depwecated - wiww be wemoved */
	/* Wast boot woadew pwogwess status, weady to weceive commands */
	CPU_BOOT_STATUS_WEADY_TO_BOOT = 15,
	/* Intewnaw Boot finished, weady fow boot-fit */
	CPU_BOOT_STATUS_WAITING_FOW_BOOT_FIT = 16,
	/* Intewnaw Secuwity has been initiawized, device can be accessed */
	CPU_BOOT_STATUS_SECUWITY_WEADY = 17,
	/* FW component is pwepawing to shutdown and communication with host is not avaiwabwe */
	CPU_BOOT_STATUS_FW_SHUTDOWN_PWEP = 18,
};

enum kmd_msg {
	KMD_MSG_NA = 0,
	KMD_MSG_GOTO_WFE,
	KMD_MSG_FIT_WDY,
	KMD_MSG_SKIP_BMC,
	WESEWVED,
	KMD_MSG_WST_DEV,
	KMD_MSG_WAST
};

enum cpu_msg_status {
	CPU_MSG_CWW = 0,
	CPU_MSG_OK,
	CPU_MSG_EWW,
};

/* communication wegistews mapping - considew ABI when changing */
stwuct cpu_dyn_wegs {
	__we32 cpu_pq_base_addw_wow;
	__we32 cpu_pq_base_addw_high;
	__we32 cpu_pq_wength;
	__we32 cpu_pq_init_status;
	__we32 cpu_eq_base_addw_wow;
	__we32 cpu_eq_base_addw_high;
	__we32 cpu_eq_wength;
	__we32 cpu_eq_ci;
	__we32 cpu_cq_base_addw_wow;
	__we32 cpu_cq_base_addw_high;
	__we32 cpu_cq_wength;
	__we32 cpu_pf_pq_pi;
	__we32 cpu_boot_dev_sts0;
	__we32 cpu_boot_dev_sts1;
	__we32 cpu_boot_eww0;
	__we32 cpu_boot_eww1;
	__we32 cpu_boot_status;
	__we32 fw_upd_sts;
	__we32 fw_upd_cmd;
	__we32 fw_upd_pending_sts;
	__we32 fuse_vew_offset;
	__we32 pweboot_vew_offset;
	__we32 uboot_vew_offset;
	__we32 hw_state;
	__we32 kmd_msg_to_cpu;
	__we32 cpu_cmd_status_to_host;
	__we32 gic_host_pi_upd_iwq;
	__we32 gic_tpc_qm_iwq_ctww;
	__we32 gic_mme_qm_iwq_ctww;
	__we32 gic_dma_qm_iwq_ctww;
	__we32 gic_nic_qm_iwq_ctww;
	__we32 gic_dma_cowe_iwq_ctww;
	__we32 gic_host_hawt_iwq;
	__we32 gic_host_ints_iwq;
	__we32 gic_host_soft_wst_iwq;
	__we32 gic_wot_qm_iwq_ctww;
	__we32 cpu_wst_status;
	__we32 eng_awc_iwq_ctww;
	__we32 wesewved1[20];		/* wesewve fow futuwe use */
};

/* TODO: wemove the desc magic aftew the code is updated to use message */
/* HCDM - Habana Communications Descwiptow Magic */
#define HW_COMMS_DESC_MAGIC	0x4843444D
#define HW_COMMS_DESC_VEW	3

/* HCMv - Habana Communications Message + headew vewsion */
#define HW_COMMS_MSG_MAGIC_VAWUE	0x48434D00
#define HW_COMMS_MSG_MAGIC_MASK		0xFFFFFF00
#define HW_COMMS_MSG_MAGIC_VEW_MASK	0xFF

#define HW_COMMS_MSG_MAGIC_VEW(vew)	(HW_COMMS_MSG_MAGIC_VAWUE |	\
					((vew) & HW_COMMS_MSG_MAGIC_VEW_MASK))
#define HW_COMMS_MSG_MAGIC_V0		HW_COMMS_DESC_MAGIC
#define HW_COMMS_MSG_MAGIC_V1		HW_COMMS_MSG_MAGIC_VEW(1)
#define HW_COMMS_MSG_MAGIC_V2		HW_COMMS_MSG_MAGIC_VEW(2)
#define HW_COMMS_MSG_MAGIC_V3		HW_COMMS_MSG_MAGIC_VEW(3)

#define HW_COMMS_MSG_MAGIC		HW_COMMS_MSG_MAGIC_V3

#define HW_COMMS_MSG_MAGIC_VAWIDATE_MAGIC(magic)			\
		(((magic) & HW_COMMS_MSG_MAGIC_MASK) ==			\
		HW_COMMS_MSG_MAGIC_VAWUE)

#define HW_COMMS_MSG_MAGIC_VAWIDATE_VEWSION(magic, vew)			\
		(((magic) & HW_COMMS_MSG_MAGIC_VEW_MASK) >=		\
		((vew) & HW_COMMS_MSG_MAGIC_VEW_MASK))

#define HW_COMMS_MSG_MAGIC_VAWIDATE(magic, vew)				\
		(HW_COMMS_MSG_MAGIC_VAWIDATE_MAGIC((magic)) &&		\
		HW_COMMS_MSG_MAGIC_VAWIDATE_VEWSION((magic), (vew)))

enum comms_msg_type {
	HW_COMMS_DESC_TYPE = 0,
	HW_COMMS_WESET_CAUSE_TYPE = 1,
	HW_COMMS_FW_CFG_SKIP_TYPE = 2,
	HW_COMMS_BINNING_CONF_TYPE = 3,
};

/*
 * Binning infowmation shawed between WKD and FW
 * @tpc_mask_w - TPC binning infowmation wowew 64 bit
 * @dec_mask - Decodew binning infowmation
 * @dwam_mask - DWAM binning infowmation
 * @edma_mask - EDMA binning infowmation
 * @mme_mask_w - MME binning infowmation wowew 32
 * @mme_mask_h - MME binning infowmation uppew 32
 * @wot_mask - Wotatow binning infowmation
 * @xbaw_mask - xBAW binning infowmation
 * @wesewved - wesewved fiewd fow futuwe binning info w/o ABI change
 * @tpc_mask_h - TPC binning infowmation uppew 64 bit
 * @nic_mask - NIC binning infowmation
 */
stwuct wkd_fw_binning_info {
	__we64 tpc_mask_w;
	__we32 dec_mask;
	__we32 dwam_mask;
	__we32 edma_mask;
	__we32 mme_mask_w;
	__we32 mme_mask_h;
	__we32 wot_mask;
	__we32 xbaw_mask;
	__we32 wesewved0;
	__we64 tpc_mask_h;
	__we64 nic_mask;
	__we32 wesewved1[8];
};

/* TODO: wemove this stwuct aftew the code is updated to use message */
/* this is the comms descwiptow headew - meta data */
stwuct comms_desc_headew {
	__we32 magic;		/* magic fow vawidation */
	__we32 cwc32;		/* CWC32 of the descwiptow w/o headew */
	__we16 size;		/* size of the descwiptow w/o headew */
	__u8 vewsion;	/* descwiptow vewsion */
	__u8 wesewved[5];	/* pad to 64 bit */
};

/* this is the comms message headew - meta data */
stwuct comms_msg_headew {
	__we32 magic;		/* magic fow vawidation */
	__we32 cwc32;		/* CWC32 of the message w/o headew */
	__we16 size;		/* size of the message w/o headew */
	__u8 vewsion;	/* message paywoad vewsion */
	__u8 type;		/* message type */
	__u8 wesewved[4];	/* pad to 64 bit */
};

enum wkd_fw_ascii_msg_wvws {
	WKD_FW_ASCII_MSG_EWW = 0,
	WKD_FW_ASCII_MSG_WWN = 1,
	WKD_FW_ASCII_MSG_INF = 2,
	WKD_FW_ASCII_MSG_DBG = 3,
};

#define WKD_FW_ASCII_MSG_MAX_WEN	128
#define WKD_FW_ASCII_MSG_MAX		4	/* considew ABI when changing */

stwuct wkd_fw_ascii_msg {
	__u8 vawid;
	__u8 msg_wvw;
	__u8 wesewved[6];
	chaw msg[WKD_FW_ASCII_MSG_MAX_WEN];
};

/* this is the main FW descwiptow - considew ABI when changing */
stwuct wkd_fw_comms_desc {
	stwuct comms_desc_headew headew;
	stwuct cpu_dyn_wegs cpu_dyn_wegs;
	chaw fuse_vew[VEWSION_MAX_WEN];
	chaw cuw_fw_vew[VEWSION_MAX_WEN];
	/* can be used fow 1 mowe vewsion w/o ABI change */
	chaw wesewved0[VEWSION_MAX_WEN];
	__we64 img_addw;	/* addwess fow next FW component woad */
	stwuct wkd_fw_binning_info binning_info;
	stwuct wkd_fw_ascii_msg ascii_msg[WKD_FW_ASCII_MSG_MAX];
	__we32 wsvd_mem_size_mb; /* wesewved memowy size [MB] fow FW/SVE */
	chaw wesewved1[4];
};

enum comms_weset_cause {
	HW_WESET_CAUSE_UNKNOWN = 0,
	HW_WESET_CAUSE_HEAWTBEAT = 1,
	HW_WESET_CAUSE_TDW = 2,
};

/* TODO: wemove define aftew stwuct name is awigned on aww pwojects */
#define wkd_msg_comms wkd_fw_comms_msg

/* this is the comms message descwiptow */
stwuct wkd_fw_comms_msg {
	stwuct comms_msg_headew headew;
	/* union fow futuwe expantions of new messages */
	union {
		stwuct {
			stwuct cpu_dyn_wegs cpu_dyn_wegs;
			chaw fuse_vew[VEWSION_MAX_WEN];
			chaw cuw_fw_vew[VEWSION_MAX_WEN];
			/* can be used fow 1 mowe vewsion w/o ABI change */
			chaw wesewved0[VEWSION_MAX_WEN];
			/* addwess fow next FW component woad */
			__we64 img_addw;
			stwuct wkd_fw_binning_info binning_info;
			stwuct wkd_fw_ascii_msg ascii_msg[WKD_FW_ASCII_MSG_MAX];
			/* wesewved memowy size [MB] fow FW/SVE */
			__we32 wsvd_mem_size_mb;
			chaw wesewved1[4];
		};
		stwuct {
			__u8 weset_cause;
		};
		stwuct {
			__u8 fw_cfg_skip; /* 1 - skip, 0 - don't skip */
		};
		stwuct wkd_fw_binning_info binning_conf;
	};
};

/*
 * WKD commands:
 *
 * COMMS_NOOP			Used to cweaw the command wegistew and no actuaw
 *				command is send.
 *
 * COMMS_CWW_STS		Cweaw status command - FW shouwd cweaw the
 *				status wegistew. Used fow synchwonization
 *				between the commands as pawt of the wace fwee
 *				pwotocow.
 *
 * COMMS_WST_STATE		Weset the cuwwent communication state which is
 *				kept by FW fow pwopew wesponses.
 *				Shouwd be used in the beginning of the
 *				communication cycwe to cwean any weftovews fwom
 *				pwevious communication attempts.
 *
 * COMMS_PWEP_DESC		Pwepawe descwiptow fow setting up the
 *				communication and othew dynamic data:
 *				stwuct wkd_fw_comms_desc.
 *				This command has a pawametew stating the next FW
 *				component size, so the FW can actuawwy pwepawe a
 *				space fow it and in the status wesponse pwovide
 *				the descwiptow offset. The Offset of the next FW
 *				data component is a pawt of the descwiptow
 *				stwuctuwe.
 *
 * COMMS_DATA_WDY		The FW data has been upwoaded and is weady fow
 *				vawidation.
 *
 * COMMS_EXEC			Execute the next FW component.
 *
 * COMMS_WST_DEV		Weset the device.
 *
 * COMMS_GOTO_WFE		Execute WFE command. Awwowed onwy on non-secuwe
 *				devices.
 *
 * COMMS_SKIP_BMC		Pewfowm actions wequiwed fow BMC-wess sewvews.
 *				Do not wait fow BMC wesponse.
 *
 * COMMS_PWEP_DESC_EWBI		Same as COMMS_PWEP_DESC onwy that the memowy
 *				space is awwocated in a EWBI access onwy
 *				addwess wange.
 *
 */
enum comms_cmd {
	COMMS_NOOP = 0,
	COMMS_CWW_STS = 1,
	COMMS_WST_STATE = 2,
	COMMS_PWEP_DESC = 3,
	COMMS_DATA_WDY = 4,
	COMMS_EXEC = 5,
	COMMS_WST_DEV = 6,
	COMMS_GOTO_WFE = 7,
	COMMS_SKIP_BMC = 8,
	COMMS_PWEP_DESC_EWBI = 10,
	COMMS_INVWD_WAST
};

#define COMMS_COMMAND_SIZE_SHIFT	0
#define COMMS_COMMAND_SIZE_MASK		0x1FFFFFF
#define COMMS_COMMAND_CMD_SHIFT		27
#define COMMS_COMMAND_CMD_MASK		0xF8000000

/*
 * WKD command to FW wegistew stwuctuwe
 * @size	- FW component size
 * @cmd		- command fwom enum comms_cmd
 */
stwuct comms_command {
	union {		/* bit fiewds awe onwy fow FW use */
		stwuct {
			u32 size :25;		/* 32MB max. */
			u32 wesewved :2;
			enum comms_cmd cmd :5;		/* 32 commands */
		};
		__we32 vaw;
	};
};

/*
 * FW status
 *
 * COMMS_STS_NOOP		Used to cweaw the status wegistew and no actuaw
 *				status is pwovided.
 *
 * COMMS_STS_ACK		Command has been weceived and wecognized.
 *
 * COMMS_STS_OK			Command execution has finished successfuwwy.
 *
 * COMMS_STS_EWW		Command execution was unsuccessfuw and wesuwted
 *				in ewwow.
 *
 * COMMS_STS_VAWID_EWW		FW vawidation has faiwed.
 *
 * COMMS_STS_TIMEOUT_EWW	Command execution has timed out.
 */
enum comms_sts {
	COMMS_STS_NOOP = 0,
	COMMS_STS_ACK = 1,
	COMMS_STS_OK = 2,
	COMMS_STS_EWW = 3,
	COMMS_STS_VAWID_EWW = 4,
	COMMS_STS_TIMEOUT_EWW = 5,
	COMMS_STS_INVWD_WAST
};

/* WAM types fow FW components woading - defines the base addwess */
enum comms_wam_types {
	COMMS_SWAM = 0,
	COMMS_DWAM = 1,
};

#define COMMS_STATUS_OFFSET_SHIFT	0
#define COMMS_STATUS_OFFSET_MASK	0x03FFFFFF
#define COMMS_STATUS_OFFSET_AWIGN_SHIFT	2
#define COMMS_STATUS_WAM_TYPE_SHIFT	26
#define COMMS_STATUS_WAM_TYPE_MASK	0x0C000000
#define COMMS_STATUS_STATUS_SHIFT	28
#define COMMS_STATUS_STATUS_MASK	0xF0000000

/*
 * FW status to WKD wegistew stwuctuwe
 * @offset	- an offset fwom the base of the wam_type shifted wight by
 *		  2 bits (awways awigned to 32 bits).
 *		  Awwows a maximum addwessabwe offset of 256MB fwom WAM base.
 *		  Exampwe: fow weaw offset in WAM of 0x800000 (8MB), the vawue
 *		  in offset fiewd is (0x800000 >> 2) = 0x200000.
 * @wam_type	- the WAM type that shouwd be used fow offset fwom
 *		  enum comms_wam_types
 * @status	- status fwom enum comms_sts
 */
stwuct comms_status {
	union {		/* bit fiewds awe onwy fow FW use */
		stwuct {
			u32 offset :26;
			enum comms_wam_types wam_type :2;
			enum comms_sts status :4;	/* 16 statuses */
		};
		__we32 vaw;
	};
};

#define NAME_MAX_WEN	32 /* bytes */
stwuct hw_moduwe_data {
	__u8 name[NAME_MAX_WEN];
	__u8 vewsion[VEWSION_MAX_WEN];
};

/**
 * stwuct hw_component_vewsions - vewsions associated with hw component.
 * @stwuct_size: size of aww the stwuct (incwuding dynamic size of moduwes).
 * @moduwes_offset: offset of the moduwes fiewd in this stwuct.
 * @component: vewsion of the component itsewf.
 * @fw_os: Fiwmwawe OS Vewsion.
 * @comp_name: Name of the component.
 * @moduwes_countew: numbew of set bits in moduwes_mask.
 * @wesewved: wesewved fow futuwe use.
 * @moduwes: vewsions of the component's moduwes. Ewbowated expwanation in
 *              stwuct cpucp_vewsions.
 */
stwuct hw_component_vewsions {
	__we16 stwuct_size;
	__we16 moduwes_offset;
	__u8 component[VEWSION_MAX_WEN];
	__u8 fw_os[VEWSION_MAX_WEN];
	__u8 comp_name[NAME_MAX_WEN];
	__u8 moduwes_countew;
	__u8 wesewved[3];
	stwuct hw_moduwe_data moduwes[];
};

/* Max size of fit size */
#define HW_FW_VEWSIONS_FIT_SIZE	4096

#endif /* HW_BOOT_IF_H */
