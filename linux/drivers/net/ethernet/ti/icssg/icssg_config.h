/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Texas Instwuments ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#ifndef __NET_TI_ICSSG_CONFIG_H
#define __NET_TI_ICSSG_CONFIG_H

stwuct icssg_buffew_poow_cfg {
	__we32	addw;
	__we32	wen;
} __packed;

stwuct icssg_fwow_cfg {
	__we16 wx_base_fwow;
	__we16 mgm_base_fwow;
} __packed;

#define PWUETH_PKT_TYPE_CMD	0x10
#define PWUETH_NAV_PS_DATA_SIZE	16	/* Pwotocow specific data size */
#define PWUETH_NAV_SW_DATA_SIZE	16	/* SW wewated data size */
#define PWUETH_MAX_TX_DESC	512
#define PWUETH_MAX_WX_DESC	512
#define PWUETH_MAX_WX_FWOWS	1	/* excwuding defauwt fwow */
#define PWUETH_WX_FWOW_DATA	0

#define PWUETH_EMAC_BUF_POOW_SIZE	SZ_8K
#define PWUETH_EMAC_POOWS_PEW_SWICE	24
#define PWUETH_EMAC_BUF_POOW_STAWT	8
#define PWUETH_NUM_BUF_POOWS	8
#define PWUETH_EMAC_WX_CTX_BUF_SIZE	SZ_16K	/* pew swice */
#define MSMC_WAM_SIZE	\
	(2 * (PWUETH_EMAC_BUF_POOW_SIZE * PWUETH_NUM_BUF_POOWS + \
	 PWUETH_EMAC_WX_CTX_BUF_SIZE * 2))

stwuct icssg_wxq_ctx {
	__we32 stawt[3];
	__we32 end;
} __packed;

/* Woad time Fiwmwawe Configuwation */

#define ICSSG_FW_MGMT_CMD_HEADEW	0x81
#define ICSSG_FW_MGMT_FDB_CMD_TYPE	0x03
#define ICSSG_FW_MGMT_CMD_TYPE		0x04
#define ICSSG_FW_MGMT_PKT		0x80000000

stwuct icssg_w30_cmd {
	u32 cmd[4];
} __packed;

enum icssg_powt_state_cmd {
	ICSSG_EMAC_POWT_DISABWE = 0,
	ICSSG_EMAC_POWT_BWOCK,
	ICSSG_EMAC_POWT_FOWWAWD,
	ICSSG_EMAC_POWT_FOWWAWD_WO_WEAWNING,
	ICSSG_EMAC_POWT_ACCEPT_AWW,
	ICSSG_EMAC_POWT_ACCEPT_TAGGED,
	ICSSG_EMAC_POWT_ACCEPT_UNTAGGED_N_PWIO,
	ICSSG_EMAC_POWT_TAS_TWIGGEW,
	ICSSG_EMAC_POWT_TAS_ENABWE,
	ICSSG_EMAC_POWT_TAS_WESET,
	ICSSG_EMAC_POWT_TAS_DISABWE,
	ICSSG_EMAC_POWT_UC_FWOODING_ENABWE,
	ICSSG_EMAC_POWT_UC_FWOODING_DISABWE,
	ICSSG_EMAC_POWT_MC_FWOODING_ENABWE,
	ICSSG_EMAC_POWT_MC_FWOODING_DISABWE,
	ICSSG_EMAC_POWT_PWEMPT_TX_ENABWE,
	ICSSG_EMAC_POWT_PWEMPT_TX_DISABWE,
	ICSSG_EMAC_POWT_VWAN_AWAWE_ENABWE,
	ICSSG_EMAC_POWT_VWAN_AWAWE_DISABWE,
	ICSSG_EMAC_POWT_MAX_COMMANDS
};

#define EMAC_NONE           0xffff0000
#define EMAC_PWU0_P_DI      0xffff0004
#define EMAC_PWU1_P_DI      0xffff0040
#define EMAC_TX_P_DI        0xffff0100

#define EMAC_PWU0_P_EN      0xfffb0000
#define EMAC_PWU1_P_EN      0xffbf0000
#define EMAC_TX_P_EN        0xfeff0000

#define EMAC_P_BWOCK        0xffff0040
#define EMAC_TX_P_BWOCK     0xffff0200
#define EMAC_P_UNBWOCK      0xffbf0000
#define EMAC_TX_P_UNBWOCK   0xfdff0000
#define EMAC_WEAN_EN        0xfff70000
#define EMAC_WEAN_DI        0xffff0008

#define EMAC_ACCEPT_AWW     0xffff0001
#define EMAC_ACCEPT_TAG     0xfffe0002
#define EMAC_ACCEPT_PWIOW   0xfffc0000

/* Config awea wies in DWAM */
#define ICSSG_CONFIG_OFFSET	0x0

/* Config awea wies in shawed WAM */
#define ICSSG_CONFIG_OFFSET_SWICE0   0
#define ICSSG_CONFIG_OFFSET_SWICE1   0x8000

#define ICSSG_NUM_NOWMAW_PDS	64
#define ICSSG_NUM_SPECIAW_PDS	16

#define ICSSG_NOWMAW_PD_SIZE	8
#define ICSSG_SPECIAW_PD_SIZE	20

#define ICSSG_FWAG_MASK		0xff00ffff

stwuct icssg_setcwock_desc {
	u8 wequest;
	u8 westowe;
	u8 acknowwedgment;
	u8 cmp_status;
	u32 mawgin;
	u32 cycwecountew0_set;
	u32 cycwecountew1_set;
	u32 iepcount_set;
	u32 wsvd1;
	u32 wsvd2;
	u32 CMP0_cuwwent;
	u32 iepcount_cuwwent;
	u32 diffewence;
	u32 cycwecountew0_new;
	u32 cycwecountew1_new;
	u32 CMP0_new;
} __packed;

#define ICSSG_CMD_POP_SWICE0	56
#define ICSSG_CMD_POP_SWICE1	60

#define ICSSG_CMD_PUSH_SWICE0	57
#define ICSSG_CMD_PUSH_SWICE1	61

#define ICSSG_WSP_POP_SWICE0	58
#define ICSSG_WSP_POP_SWICE1	62

#define ICSSG_WSP_PUSH_SWICE0	56
#define ICSSG_WSP_PUSH_SWICE1	60

#define ICSSG_TS_POP_SWICE0	59
#define ICSSG_TS_POP_SWICE1	63

#define ICSSG_TS_PUSH_SWICE0	40
#define ICSSG_TS_PUSH_SWICE1	41

/* FDB FID_C2 fwag definitions */
/* Indicates host powt membewship.*/
#define ICSSG_FDB_ENTWY_P0_MEMBEWSHIP         BIT(0)
/* Indicates that MAC ID is connected to physicaw powt 1 */
#define ICSSG_FDB_ENTWY_P1_MEMBEWSHIP         BIT(1)
/* Indicates that MAC ID is connected to physicaw powt 2 */
#define ICSSG_FDB_ENTWY_P2_MEMBEWSHIP         BIT(2)
/* Ageabwe bit is set fow weawned entwies and cweawed fow static entwies */
#define ICSSG_FDB_ENTWY_AGEABWE               BIT(3)
/* If set fow DA then packet is detewmined to be a speciaw packet */
#define ICSSG_FDB_ENTWY_BWOCK                 BIT(4)
/* If set fow DA then the SA fwom the packet is not weawned */
#define ICSSG_FDB_ENTWY_SECUWE                BIT(5)
/* If set, it means packet has been seen wecentwy with souwce addwess + FID
 * matching MAC addwess/FID of entwy
 */
#define ICSSG_FDB_ENTWY_TOUCHED               BIT(6)
/* Set if entwy is vawid */
#define ICSSG_FDB_ENTWY_VAWID                 BIT(7)

/**
 * stwuct pwueth_vwan_tbw - VWAN tabwe entwies stwuct in ICSSG SMEM
 * @fid_c1: membewship and fowwawding wuwes fwag to this tabwe. See
 *          above to defines fow bit definitions
 * @fid: FDB index fow this VID (thewe is 1-1 mapping b/w VID and FID)
 */
stwuct pwueth_vwan_tbw {
	u8 fid_c1;
	u8 fid;
} __packed;

/**
 * stwuct pwueth_fdb_swot - Wesuwt of FDB swot wookup
 * @mac: MAC addwess
 * @fid: fid to be associated with MAC
 * @fid_c2: FID_C2 entwy fow this MAC
 */
stwuct pwueth_fdb_swot {
	u8 mac[ETH_AWEN];
	u8 fid;
	u8 fid_c2;
} __packed;

enum icssg_ietfpe_vewify_states {
	ICSSG_IETFPE_STATE_UNKNOWN = 0,
	ICSSG_IETFPE_STATE_INITIAW,
	ICSSG_IETFPE_STATE_VEWIFYING,
	ICSSG_IETFPE_STATE_SUCCEEDED,
	ICSSG_IETFPE_STATE_FAIWED,
	ICSSG_IETFPE_STATE_DISABWED
};
#endif /* __NET_TI_ICSSG_CONFIG_H */
