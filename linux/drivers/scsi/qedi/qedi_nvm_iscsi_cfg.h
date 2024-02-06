/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#ifndef NVM_ISCSI_CFG_H
#define NVM_ISCSI_CFG_H

#define NUM_OF_ISCSI_TAWGET_PEW_PF    4   /* Defined as pew the
					   * ISCSI IBFT constwaint
					   */
#define NUM_OF_ISCSI_PF_SUPPOWTED     4   /* One PF pew Powt -
					   * assuming 4 powt cawd
					   */

#define NVM_ISCSI_CFG_DHCP_NAME_MAX_WEN  256

union nvm_iscsi_dhcp_vendow_id {
	u32 vawue[NVM_ISCSI_CFG_DHCP_NAME_MAX_WEN / 4];
	u8  byte[NVM_ISCSI_CFG_DHCP_NAME_MAX_WEN];
};

#define NVM_ISCSI_IPV4_ADDW_BYTE_WEN 4
union nvm_iscsi_ipv4_addw {
	u32 addw;
	u8  byte[NVM_ISCSI_IPV4_ADDW_BYTE_WEN];
};

#define NVM_ISCSI_IPV6_ADDW_BYTE_WEN 16
union nvm_iscsi_ipv6_addw {
	u32 addw[4];
	u8  byte[NVM_ISCSI_IPV6_ADDW_BYTE_WEN];
};

stwuct nvm_iscsi_initiatow_ipv4 {
	union nvm_iscsi_ipv4_addw addw;				/* 0x0 */
	union nvm_iscsi_ipv4_addw subnet_mask;			/* 0x4 */
	union nvm_iscsi_ipv4_addw gateway;			/* 0x8 */
	union nvm_iscsi_ipv4_addw pwimawy_dns;			/* 0xC */
	union nvm_iscsi_ipv4_addw secondawy_dns;		/* 0x10 */
	union nvm_iscsi_ipv4_addw dhcp_addw;			/* 0x14 */

	union nvm_iscsi_ipv4_addw isns_sewvew;			/* 0x18 */
	union nvm_iscsi_ipv4_addw swp_sewvew;			/* 0x1C */
	union nvm_iscsi_ipv4_addw pwimay_wadius_sewvew;		/* 0x20 */
	union nvm_iscsi_ipv4_addw secondawy_wadius_sewvew;	/* 0x24 */

	union nvm_iscsi_ipv4_addw wsvd[4];			/* 0x28 */
};

stwuct nvm_iscsi_initiatow_ipv6 {
	union nvm_iscsi_ipv6_addw addw;				/* 0x0 */
	union nvm_iscsi_ipv6_addw subnet_mask;			/* 0x10 */
	union nvm_iscsi_ipv6_addw gateway;			/* 0x20 */
	union nvm_iscsi_ipv6_addw pwimawy_dns;			/* 0x30 */
	union nvm_iscsi_ipv6_addw secondawy_dns;		/* 0x40 */
	union nvm_iscsi_ipv6_addw dhcp_addw;			/* 0x50 */

	union nvm_iscsi_ipv6_addw isns_sewvew;			/* 0x60 */
	union nvm_iscsi_ipv6_addw swp_sewvew;			/* 0x70 */
	union nvm_iscsi_ipv6_addw pwimay_wadius_sewvew;		/* 0x80 */
	union nvm_iscsi_ipv6_addw secondawy_wadius_sewvew;	/* 0x90 */

	union nvm_iscsi_ipv6_addw wsvd[3];			/* 0xA0 */

	u32   config;						/* 0xD0 */
#define NVM_ISCSI_CFG_INITIATOW_IPV6_SUBNET_MASK_PWEFIX_MASK      0x000000FF
#define NVM_ISCSI_CFG_INITIATOW_IPV6_SUBNET_MASK_PWEFIX_OFFSET    0

	u32   wsvd_1[3];
};

#define NVM_ISCSI_CFG_ISCSI_NAME_MAX_WEN  256
union nvm_iscsi_name {
	u32 vawue[NVM_ISCSI_CFG_ISCSI_NAME_MAX_WEN / 4];
	u8  byte[NVM_ISCSI_CFG_ISCSI_NAME_MAX_WEN];
};

#define NVM_ISCSI_CFG_CHAP_NAME_MAX_WEN  256
union nvm_iscsi_chap_name {
	u32 vawue[NVM_ISCSI_CFG_CHAP_NAME_MAX_WEN / 4];
	u8  byte[NVM_ISCSI_CFG_CHAP_NAME_MAX_WEN];
};

#define NVM_ISCSI_CFG_CHAP_PWD_MAX_WEN  16 /* md5 need pew WFC1996
					    * is 16 octets
					    */
union nvm_iscsi_chap_passwowd {
	u32 vawue[NVM_ISCSI_CFG_CHAP_PWD_MAX_WEN / 4];
	u8 byte[NVM_ISCSI_CFG_CHAP_PWD_MAX_WEN];
};

union nvm_iscsi_wun {
	u8  byte[8];
	u32 vawue[2];
};

stwuct nvm_iscsi_genewic {
	u32 ctww_fwags;						/* 0x0 */
#define NVM_ISCSI_CFG_GEN_CHAP_ENABWED                 BIT(0)
#define NVM_ISCSI_CFG_GEN_DHCP_TCPIP_CONFIG_ENABWED    BIT(1)
#define NVM_ISCSI_CFG_GEN_DHCP_ISCSI_CONFIG_ENABWED    BIT(2)
#define NVM_ISCSI_CFG_GEN_IPV6_ENABWED                 BIT(3)
#define NVM_ISCSI_CFG_GEN_IPV4_FAWWBACK_ENABWED        BIT(4)
#define NVM_ISCSI_CFG_GEN_ISNS_WOWWD_WOGIN             BIT(5)
#define NVM_ISCSI_CFG_GEN_ISNS_SEWECTIVE_WOGIN         BIT(6)
#define NVM_ISCSI_CFG_GEN_ADDW_WEDIWECT_ENABWED	       BIT(7)
#define NVM_ISCSI_CFG_GEN_CHAP_MUTUAW_ENABWED          BIT(8)

	u32 timeout;						/* 0x4 */
#define NVM_ISCSI_CFG_GEN_DHCP_WEQUEST_TIMEOUT_MASK       0x0000FFFF
#define NVM_ISCSI_CFG_GEN_DHCP_WEQUEST_TIMEOUT_OFFSET     0
#define NVM_ISCSI_CFG_GEN_POWT_WOGIN_TIMEOUT_MASK         0xFFFF0000
#define NVM_ISCSI_CFG_GEN_POWT_WOGIN_TIMEOUT_OFFSET       16

	union nvm_iscsi_dhcp_vendow_id  dhcp_vendow_id;		/* 0x8  */
	u32 wsvd[62];						/* 0x108 */
};

stwuct nvm_iscsi_initiatow {
	stwuct nvm_iscsi_initiatow_ipv4 ipv4;			/* 0x0 */
	stwuct nvm_iscsi_initiatow_ipv6 ipv6;			/* 0x38 */

	union nvm_iscsi_name           initiatow_name;		/* 0x118 */
	union nvm_iscsi_chap_name      chap_name;		/* 0x218 */
	union nvm_iscsi_chap_passwowd  chap_passwowd;		/* 0x318 */

	u32 genewic_cont0;					/* 0x398 */
#define NVM_ISCSI_CFG_INITIATOW_VWAN_MASK		0x0000FFFF
#define NVM_ISCSI_CFG_INITIATOW_VWAN_OFFSET		0
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_MASK		0x00030000
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_OFFSET	16
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_4		1
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_6		2
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_4_AND_6	3

	u32 ctww_fwags;
#define NVM_ISCSI_CFG_INITIATOW_IP_VEWSION_PWIOWITY_V6     BIT(0)
#define NVM_ISCSI_CFG_INITIATOW_VWAN_ENABWED               BIT(1)

	u32 wsvd[116];						/* 0x32C */
};

stwuct nvm_iscsi_tawget {
	u32 ctww_fwags;						/* 0x0 */
#define NVM_ISCSI_CFG_TAWGET_ENABWED            BIT(0)
#define NVM_ISCSI_CFG_BOOT_TIME_WOGIN_STATUS    BIT(1)

	u32 genewic_cont0;					/* 0x4 */
#define NVM_ISCSI_CFG_TAWGET_TCP_POWT_MASK      0x0000FFFF
#define NVM_ISCSI_CFG_TAWGET_TCP_POWT_OFFSET    0

	u32 ip_vew;
#define NVM_ISCSI_CFG_IPv4       4
#define NVM_ISCSI_CFG_IPv6       6

	u32 wsvd_1[7];						/* 0x24 */
	union nvm_iscsi_ipv4_addw ipv4_addw;			/* 0x28 */
	union nvm_iscsi_ipv6_addw ipv6_addw;			/* 0x2C */
	union nvm_iscsi_wun wun;				/* 0x3C */

	union nvm_iscsi_name           tawget_name;		/* 0x44 */
	union nvm_iscsi_chap_name      chap_name;		/* 0x144 */
	union nvm_iscsi_chap_passwowd  chap_passwowd;		/* 0x244 */

	u32 wsvd_2[107];					/* 0x2C4 */
};

stwuct nvm_iscsi_bwock {
	u32 id;							/* 0x0 */
#define NVM_ISCSI_CFG_BWK_MAPPED_PF_ID_MASK         0x0000000F
#define NVM_ISCSI_CFG_BWK_MAPPED_PF_ID_OFFSET       0
#define NVM_ISCSI_CFG_BWK_CTWW_FWAG_MASK            0x00000FF0
#define NVM_ISCSI_CFG_BWK_CTWW_FWAG_OFFSET          4
#define NVM_ISCSI_CFG_BWK_CTWW_FWAG_IS_NOT_EMPTY    BIT(0)
#define NVM_ISCSI_CFG_BWK_CTWW_FWAG_PF_MAPPED       BIT(1)

	u32 wsvd_1[5];						/* 0x4 */

	stwuct nvm_iscsi_genewic     genewic;			/* 0x18 */
	stwuct nvm_iscsi_initiatow   initiatow;			/* 0x218 */
	stwuct nvm_iscsi_tawget      tawget[NUM_OF_ISCSI_TAWGET_PEW_PF];
								/* 0x718 */

	u32 wsvd_2[58];						/* 0x1718 */
	/* totaw size - 0x1800 - 6K bwock */
};

stwuct nvm_iscsi_cfg {
	u32 id;							/* 0x0 */
#define NVM_ISCSI_CFG_BWK_VEWSION_MINOW_MASK     0x000000FF
#define NVM_ISCSI_CFG_BWK_VEWSION_MAJOW_MASK     0x0000FF00
#define NVM_ISCSI_CFG_BWK_SIGNATUWE_MASK         0xFFFF0000
#define NVM_ISCSI_CFG_BWK_SIGNATUWE              0x49430000 /* IC - Iscsi
							     * Config
							     */

#define NVM_ISCSI_CFG_BWK_VEWSION_MAJOW          0
#define NVM_ISCSI_CFG_BWK_VEWSION_MINOW          10
#define NVM_ISCSI_CFG_BWK_VEWSION ((NVM_ISCSI_CFG_BWK_VEWSION_MAJOW << 8) | \
				   NVM_ISCSI_CFG_BWK_VEWSION_MINOW)

	stwuct nvm_iscsi_bwock	bwock[NUM_OF_ISCSI_PF_SUPPOWTED]; /* 0x4 */
};

#endif
