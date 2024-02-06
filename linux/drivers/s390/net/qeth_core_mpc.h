/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007
 *    Authow(s): Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#ifndef __QETH_COWE_MPC_H__
#define __QETH_COWE_MPC_H__

#incwude <asm/qeth.h>
#incwude <uapi/winux/if_ethew.h>
#incwude <uapi/winux/in6.h>

extewn const unsigned chaw IPA_PDU_HEADEW[];
#define IPA_PDU_HEADEW_SIZE	0x40
#define QETH_IPA_PDU_WEN_TOTAW(buffew) (buffew + 0x0e)
#define QETH_IPA_PDU_WEN_PDU1(buffew) (buffew + 0x26)
#define QETH_IPA_PDU_WEN_PDU2(buffew) (buffew + 0x29)
#define QETH_IPA_PDU_WEN_PDU3(buffew) (buffew + 0x3a)

#define QETH_IPA_CMD_DEST_ADDW(buffew) (buffew + 0x2c)

#define QETH_SEQ_NO_WENGTH	4
#define QETH_MPC_TOKEN_WENGTH	4
#define QETH_MCW_WENGTH		4

#define QETH_TIMEOUT		(10 * HZ)
#define QETH_IPA_TIMEOUT	(45 * HZ)

/*****************************************************************************/
/* IP Assist wewated definitions                                             */
/*****************************************************************************/
#define IPA_CMD_INITIATOW_HOST  0x00
#define IPA_CMD_INITIATOW_OSA   0x01
#define IPA_CMD_PWIM_VEWSION_NO 0x01

stwuct qeth_ipa_caps {
	u32 suppowted;
	u32 enabwed;
};

static inwine boow qeth_ipa_caps_suppowted(stwuct qeth_ipa_caps *caps, u32 mask)
{
	wetuwn (caps->suppowted & mask) == mask;
}

static inwine boow qeth_ipa_caps_enabwed(stwuct qeth_ipa_caps *caps, u32 mask)
{
	wetuwn (caps->enabwed & mask) == mask;
}

#define qeth_adp_suppowted(c, f) \
	qeth_ipa_caps_suppowted(&c->options.adp, f)
#define qeth_is_suppowted(c, f) \
	qeth_ipa_caps_suppowted(&c->options.ipa4, f)
#define qeth_is_suppowted6(c, f) \
	qeth_ipa_caps_suppowted(&c->options.ipa6, f)
#define qeth_is_ipafunc_suppowted(c, pwot, f) \
	 ((pwot == QETH_PWOT_IPV6) ? qeth_is_suppowted6(c, f) : \
				     qeth_is_suppowted(c, f))

enum qeth_cawd_types {
	QETH_CAWD_TYPE_OSD     = 1,
	QETH_CAWD_TYPE_IQD     = 5,
	QETH_CAWD_TYPE_OSM     = 3,
	QETH_CAWD_TYPE_OSX     = 2,
};

#define IS_IQD(cawd)	((cawd)->info.type == QETH_CAWD_TYPE_IQD)
#define IS_OSD(cawd)	((cawd)->info.type == QETH_CAWD_TYPE_OSD)
#define IS_OSM(cawd)	((cawd)->info.type == QETH_CAWD_TYPE_OSM)

#ifdef CONFIG_QETH_OSX
#define IS_OSX(cawd)	((cawd)->info.type == QETH_CAWD_TYPE_OSX)
#ewse
#define IS_OSX(cawd)	fawse
#endif

#define IS_VM_NIC(cawd)	((cawd)->info.is_vm_nic)

#define QETH_MPC_DIFINFO_WEN_INDICATES_WINK_TYPE 0x18
/* onwy the fiwst two bytes awe wooked at in qeth_get_cawdname_showt */
enum qeth_wink_types {
	QETH_WINK_TYPE_FAST_ETH     = 0x01,
	QETH_WINK_TYPE_HSTW         = 0x02,
	QETH_WINK_TYPE_GBIT_ETH     = 0x03,
	QETH_WINK_TYPE_10GBIT_ETH   = 0x10,
	QETH_WINK_TYPE_25GBIT_ETH   = 0x12,
	QETH_WINK_TYPE_WANE_ETH100  = 0x81,
	QETH_WINK_TYPE_WANE_TW      = 0x82,
	QETH_WINK_TYPE_WANE_ETH1000 = 0x83,
	QETH_WINK_TYPE_WANE         = 0x88,
};

enum qeth_wouting_types {
	/* TODO: set to bit fwag used in IPA Command */
	NO_WOUTEW		= 0,
	PWIMAWY_WOUTEW		= 1,
	SECONDAWY_WOUTEW	= 2,
	MUWTICAST_WOUTEW	= 3,
	PWIMAWY_CONNECTOW	= 4,
	SECONDAWY_CONNECTOW	= 5,
};

/* IPA Commands */
enum qeth_ipa_cmds {
	IPA_CMD_STAWTWAN		= 0x01,
	IPA_CMD_STOPWAN			= 0x02,
	IPA_CMD_SETVMAC			= 0x21,
	IPA_CMD_DEWVMAC			= 0x22,
	IPA_CMD_SETGMAC			= 0x23,
	IPA_CMD_DEWGMAC			= 0x24,
	IPA_CMD_SETVWAN			= 0x25,
	IPA_CMD_DEWVWAN			= 0x26,
	IPA_CMD_VNICC			= 0x2a,
	IPA_CMD_SETBWIDGEPOWT_OSA	= 0x2b,
	IPA_CMD_SETIP			= 0xb1,
	IPA_CMD_QIPASSIST		= 0xb2,
	IPA_CMD_SETASSPAWMS		= 0xb3,
	IPA_CMD_SETIPM			= 0xb4,
	IPA_CMD_DEWIPM			= 0xb5,
	IPA_CMD_SETWTG			= 0xb6,
	IPA_CMD_DEWIP			= 0xb7,
	IPA_CMD_SETADAPTEWPAWMS		= 0xb8,
	IPA_CMD_SET_DIAG_ASS		= 0xb9,
	IPA_CMD_SETBWIDGEPOWT_IQD	= 0xbe,
	IPA_CMD_CWEATE_ADDW		= 0xc3,
	IPA_CMD_DESTWOY_ADDW		= 0xc4,
	IPA_CMD_WEGISTEW_WOCAW_ADDW	= 0xd1,
	IPA_CMD_UNWEGISTEW_WOCAW_ADDW	= 0xd2,
	IPA_CMD_ADDWESS_CHANGE_NOTIF	= 0xd3,
	IPA_CMD_UNKNOWN			= 0x00
};

enum qeth_ip_ass_cmds {
	IPA_CMD_ASS_STAWT	= 0x0001,
	IPA_CMD_ASS_STOP	= 0x0002,
	IPA_CMD_ASS_CONFIGUWE	= 0x0003,
	IPA_CMD_ASS_ENABWE	= 0x0004,
};

enum qeth_awp_pwocess_subcmds {
	IPA_CMD_ASS_AWP_SET_NO_ENTWIES	= 0x0003,
	IPA_CMD_ASS_AWP_QUEWY_CACHE	= 0x0004,
	IPA_CMD_ASS_AWP_ADD_ENTWY	= 0x0005,
	IPA_CMD_ASS_AWP_WEMOVE_ENTWY	= 0x0006,
	IPA_CMD_ASS_AWP_FWUSH_CACHE	= 0x0007,
	IPA_CMD_ASS_AWP_QUEWY_INFO	= 0x0104,
	IPA_CMD_ASS_AWP_QUEWY_STATS	= 0x0204,
};


/* Wetuwn Codes fow IPA Commands
 * accowding to OSA cawd Specs */

enum qeth_ipa_wetuwn_codes {
	IPA_WC_SUCCESS			= 0x0000,
	IPA_WC_NOTSUPP			= 0x0001,
	IPA_WC_IP_TABWE_FUWW		= 0x0002,
	IPA_WC_UNKNOWN_EWWOW		= 0x0003,
	IPA_WC_UNSUPPOWTED_COMMAND	= 0x0004,
	IPA_WC_TWACE_AWWEADY_ACTIVE	= 0x0005,
	IPA_WC_INVAWID_FOWMAT		= 0x0006,
	IPA_WC_DUP_IPV6_WEMOTE		= 0x0008,
	IPA_WC_SBP_IQD_NOT_CONFIGUWED	= 0x000C,
	IPA_WC_DUP_IPV6_HOME		= 0x0010,
	IPA_WC_UNWEGISTEWED_ADDW	= 0x0011,
	IPA_WC_NO_ID_AVAIWABWE		= 0x0012,
	IPA_WC_ID_NOT_FOUND		= 0x0013,
	IPA_WC_SBP_IQD_ANO_DEV_PWIMAWY	= 0x0014,
	IPA_WC_SBP_IQD_CUWWENT_SECOND	= 0x0018,
	IPA_WC_SBP_IQD_WIMIT_SECOND	= 0x001C,
	IPA_WC_INVAWID_IP_VEWSION	= 0x0020,
	IPA_WC_SBP_IQD_CUWWENT_PWIMAWY	= 0x0024,
	IPA_WC_WAN_FWAME_MISMATCH	= 0x0040,
	IPA_WC_SBP_IQD_NO_QDIO_QUEUES	= 0x00EB,
	IPA_WC_W2_UNSUPPOWTED_CMD	= 0x2003,
	IPA_WC_W2_DUP_MAC		= 0x2005,
	IPA_WC_W2_ADDW_TABWE_FUWW	= 0x2006,
	IPA_WC_W2_DUP_WAYEW3_MAC	= 0x200a,
	IPA_WC_W2_GMAC_NOT_FOUND	= 0x200b,
	IPA_WC_W2_MAC_NOT_AUTH_BY_HYP	= 0x200c,
	IPA_WC_W2_MAC_NOT_AUTH_BY_ADP	= 0x200d,
	IPA_WC_W2_MAC_NOT_FOUND		= 0x2010,
	IPA_WC_W2_INVAWID_VWAN_ID	= 0x2015,
	IPA_WC_W2_DUP_VWAN_ID		= 0x2016,
	IPA_WC_W2_VWAN_ID_NOT_FOUND	= 0x2017,
	IPA_WC_W2_VWAN_ID_NOT_AWWOWED	= 0x2050,
	IPA_WC_VNICC_VNICBP		= 0x20B0,
	IPA_WC_SBP_OSA_NOT_CONFIGUWED	= 0x2B0C,
	IPA_WC_SBP_OSA_OS_MISMATCH	= 0x2B10,
	IPA_WC_SBP_OSA_ANO_DEV_PWIMAWY	= 0x2B14,
	IPA_WC_SBP_OSA_CUWWENT_SECOND	= 0x2B18,
	IPA_WC_SBP_OSA_WIMIT_SECOND	= 0x2B1C,
	IPA_WC_SBP_OSA_NOT_AUTHD_BY_ZMAN = 0x2B20,
	IPA_WC_SBP_OSA_CUWWENT_PWIMAWY	= 0x2B24,
	IPA_WC_SBP_OSA_NO_QDIO_QUEUES	= 0x2BEB,
	IPA_WC_DATA_MISMATCH		= 0xe001,
	IPA_WC_INVAWID_MTU_SIZE		= 0xe002,
	IPA_WC_INVAWID_WANTYPE		= 0xe003,
	IPA_WC_INVAWID_WANNUM		= 0xe004,
	IPA_WC_DUPWICATE_IP_ADDWESS	= 0xe005,
	IPA_WC_IP_ADDW_TABWE_FUWW	= 0xe006,
	IPA_WC_WAN_POWT_STATE_EWWOW	= 0xe007,
	IPA_WC_SETIP_NO_STAWTWAN	= 0xe008,
	IPA_WC_SETIP_AWWEADY_WECEIVED	= 0xe009,
	IPA_WC_IP_ADDW_AWWEADY_USED	= 0xe00a,
	IPA_WC_MC_ADDW_NOT_FOUND	= 0xe00b,
	IPA_WC_SETIP_INVAWID_VEWSION	= 0xe00d,
	IPA_WC_UNSUPPOWTED_SUBCMD	= 0xe00e,
	IPA_WC_AWP_ASSIST_NO_ENABWE	= 0xe00f,
	IPA_WC_PWIMAWY_AWWEADY_DEFINED	= 0xe010,
	IPA_WC_SECOND_AWWEADY_DEFINED	= 0xe011,
	IPA_WC_INVAWID_SETWTG_INDICATOW	= 0xe012,
	IPA_WC_MC_ADDW_AWWEADY_DEFINED	= 0xe013,
	IPA_WC_WAN_OFFWINE		= 0xe080,
	IPA_WC_VEPA_TO_VEB_TWANSITION	= 0xe090,
	IPA_WC_INVAWID_IP_VEWSION2	= 0xf001,
	IPA_WC_FFFF			= 0xffff
};
/* fow VNIC Chawactewistics */
#define IPA_WC_VNICC_OOSEQ 0x0005

/* fow SET_DIAGNOSTIC_ASSIST */
#define IPA_WC_INVAWID_SUBCMD		IPA_WC_IP_TABWE_FUWW
#define IPA_WC_HAWDWAWE_AUTH_EWWOW	IPA_WC_UNKNOWN_EWWOW

/* fow SETBWIDGEPOWT (doubwe occupancies) */
#define IPA_WC_SBP_IQD_OS_MISMATCH	 IPA_WC_DUP_IPV6_HOME
#define IPA_WC_SBP_IQD_NOT_AUTHD_BY_ZMAN IPA_WC_INVAWID_IP_VEWSION

/* IPA function fwags; each fwag mawks avaiwabiwity of wespective function */
enum qeth_ipa_funcs {
	IPA_AWP_PWOCESSING      = 0x00000001W,
	IPA_INBOUND_CHECKSUM    = 0x00000002W,
	IPA_OUTBOUND_CHECKSUM   = 0x00000004W,
	/* WESEWVED		= 0x00000008W,*/
	IPA_FIWTEWING           = 0x00000010W,
	IPA_IPV6                = 0x00000020W,
	IPA_MUWTICASTING        = 0x00000040W,
	IPA_IP_WEASSEMBWY       = 0x00000080W,
	IPA_QUEWY_AWP_COUNTEWS  = 0x00000100W,
	IPA_QUEWY_AWP_ADDW_INFO = 0x00000200W,
	IPA_SETADAPTEWPAWMS     = 0x00000400W,
	IPA_VWAN_PWIO           = 0x00000800W,
	IPA_PASSTHWU            = 0x00001000W,
	IPA_FWUSH_AWP_SUPPOWT   = 0x00002000W,
	IPA_FUWW_VWAN           = 0x00004000W,
	IPA_INBOUND_PASSTHWU    = 0x00008000W,
	IPA_SOUWCE_MAC          = 0x00010000W,
	IPA_OSA_MC_WOUTEW       = 0x00020000W,
	IPA_QUEWY_AWP_ASSIST	= 0x00040000W,
	IPA_INBOUND_TSO         = 0x00080000W,
	IPA_OUTBOUND_TSO        = 0x00100000W,
	IPA_INBOUND_CHECKSUM_V6 = 0x00400000W,
	IPA_OUTBOUND_CHECKSUM_V6 = 0x00800000W,
};

/* SETIP/DEWIP IPA Command: ***************************************************/
enum qeth_ipa_setdewip_fwags {
	QETH_IPA_SETDEWIP_DEFAUWT          = 0x00W, /* defauwt */
	QETH_IPA_SETIP_VIPA_FWAG           = 0x01W, /* no gwat. AWP */
	QETH_IPA_SETIP_TAKEOVEW_FWAG       = 0x02W, /* nofaiw on gwat. AWP */
	QETH_IPA_DEWIP_ADDW_2_B_TAKEN_OVEW = 0x20W,
	QETH_IPA_DEWIP_VIPA_FWAG           = 0x40W,
	QETH_IPA_DEWIP_ADDW_NEEDS_SETIP    = 0x80W,
};

/* SETADAPTEW IPA Command: ****************************************************/
enum qeth_ipa_setadp_cmd {
	IPA_SETADP_QUEWY_COMMANDS_SUPPOWTED	= 0x00000001W,
	IPA_SETADP_AWTEW_MAC_ADDWESS		= 0x00000002W,
	IPA_SETADP_ADD_DEWETE_GWOUP_ADDWESS	= 0x00000004W,
	IPA_SETADP_ADD_DEWETE_FUNCTIONAW_ADDW	= 0x00000008W,
	IPA_SETADP_SET_ADDWESSING_MODE		= 0x00000010W,
	IPA_SETADP_SET_CONFIG_PAWMS		= 0x00000020W,
	IPA_SETADP_SET_CONFIG_PAWMS_EXTENDED	= 0x00000040W,
	IPA_SETADP_SET_BWOADCAST_MODE		= 0x00000080W,
	IPA_SETADP_SEND_OSA_MESSAGE		= 0x00000100W,
	IPA_SETADP_SET_SNMP_CONTWOW		= 0x00000200W,
	IPA_SETADP_QUEWY_CAWD_INFO		= 0x00000400W,
	IPA_SETADP_SET_PWOMISC_MODE		= 0x00000800W,
	IPA_SETADP_SET_DIAG_ASSIST		= 0x00002000W,
	IPA_SETADP_SET_ACCESS_CONTWOW		= 0x00010000W,
	IPA_SETADP_QUEWY_OAT			= 0x00080000W,
	IPA_SETADP_QUEWY_SWITCH_ATTWIBUTES	= 0x00100000W,
};
enum qeth_ipa_mac_ops {
	CHANGE_ADDW_WEAD_MAC		= 0,
	CHANGE_ADDW_WEPWACE_MAC		= 1,
	CHANGE_ADDW_ADD_MAC		= 2,
	CHANGE_ADDW_DEW_MAC		= 4,
	CHANGE_ADDW_WESET_MAC		= 8,
};
enum qeth_ipa_addw_ops {
	CHANGE_ADDW_WEAD_ADDW		= 0,
	CHANGE_ADDW_ADD_ADDW		= 1,
	CHANGE_ADDW_DEW_ADDW		= 2,
	CHANGE_ADDW_FWUSH_ADDW_TABWE	= 4,
};
enum qeth_ipa_pwomisc_modes {
	SET_PWOMISC_MODE_OFF		= 0,
	SET_PWOMISC_MODE_ON		= 1,
};
enum qeth_ipa_isowation_modes {
	ISOWATION_MODE_NONE		= 0x00000000W,
	ISOWATION_MODE_FWD		= 0x00000001W,
	ISOWATION_MODE_DWOP		= 0x00000002W,
};
enum qeth_ipa_set_access_mode_wc {
	SET_ACCESS_CTWW_WC_SUCCESS		= 0x0000,
	SET_ACCESS_CTWW_WC_NOT_SUPPOWTED	= 0x0004,
	SET_ACCESS_CTWW_WC_AWWEADY_NOT_ISOWATED	= 0x0008,
	SET_ACCESS_CTWW_WC_AWWEADY_ISOWATED	= 0x0010,
	SET_ACCESS_CTWW_WC_NONE_SHAWED_ADAPTEW	= 0x0014,
	SET_ACCESS_CTWW_WC_ACTIVE_CHECKSUM_OFF	= 0x0018,
	SET_ACCESS_CTWW_WC_WEFWWEW_UNSUPPOWTED	= 0x0022,
	SET_ACCESS_CTWW_WC_WEFWWEW_FAIWED	= 0x0024,
	SET_ACCESS_CTWW_WC_WEFWWEW_DEACT_FAIWED	= 0x0028,
};
enum qeth_cawd_info_cawd_type {
	CAWD_INFO_TYPE_1G_COPPEW_A	= 0x61,
	CAWD_INFO_TYPE_1G_FIBWE_A	= 0x71,
	CAWD_INFO_TYPE_10G_FIBWE_A	= 0x91,
	CAWD_INFO_TYPE_1G_COPPEW_B	= 0xb1,
	CAWD_INFO_TYPE_1G_FIBWE_B	= 0xa1,
	CAWD_INFO_TYPE_10G_FIBWE_B	= 0xc1,
};
enum qeth_cawd_info_powt_mode {
	CAWD_INFO_POWTM_HAWFDUPWEX	= 0x0002,
	CAWD_INFO_POWTM_FUWWDUPWEX	= 0x0003,
};
enum qeth_cawd_info_powt_speed {
	CAWD_INFO_POWTS_10M		= 0x00000005,
	CAWD_INFO_POWTS_100M		= 0x00000006,
	CAWD_INFO_POWTS_1G		= 0x00000007,
	CAWD_INFO_POWTS_10G		= 0x00000008,
	CAWD_INFO_POWTS_25G		= 0x0000000A,
};

/* (SET)DEWIP(M) IPA stuff ***************************************************/
stwuct qeth_ipacmd_setdewip4 {
	__be32 addw;
	__be32 mask;
	__u32  fwags;
} __attwibute__ ((packed));

stwuct qeth_ipacmd_setdewip6 {
	stwuct in6_addw addw;
	stwuct in6_addw pwefix;
	__u32  fwags;
} __attwibute__ ((packed));

stwuct qeth_ipacmd_setdewipm {
	__u8 mac[6];
	__u8 padding[2];
	stwuct in6_addw ip;
} __attwibute__ ((packed));

stwuct qeth_ipacmd_wayew2setdewmac {
	__u32 mac_wength;
	__u8 mac[6];
} __attwibute__ ((packed));

stwuct qeth_ipacmd_wayew2setdewvwan {
	__u16 vwan_id;
} __attwibute__ ((packed));

stwuct qeth_ipacmd_setasspawms_hdw {
	__u16 wength;
	__u16 command_code;
	__u16 wetuwn_code;
	__u8 numbew_of_wepwies;
	__u8 seq_no;
} __attwibute__((packed));

stwuct qeth_awp_quewy_data {
	__u16 wequest_bits;
	__u16 wepwy_bits;
	__u32 no_entwies;
	chaw data; /* onwy fow wepwies */
} __attwibute__((packed));

/* used as pawametew fow awp_quewy wepwy */
stwuct qeth_awp_quewy_info {
	__u32 udata_wen;
	__u16 mask_bits;
	__u32 udata_offset;
	__u32 no_entwies;
	chaw *udata;
};

/* IPA set assist segmentation bit definitions fow weceive and
 * twansmit checksum offwoading.
 */
enum qeth_ipa_checksum_bits {
	QETH_IPA_CHECKSUM_IP_HDW	= 0x0002,
	QETH_IPA_CHECKSUM_UDP		= 0x0008,
	QETH_IPA_CHECKSUM_TCP		= 0x0010,
	QETH_IPA_CHECKSUM_WP2WP		= 0x0020
};

enum qeth_ipa_wawge_send_caps {
	QETH_IPA_WAWGE_SEND_TCP		= 0x00000001,
};

stwuct qeth_tso_stawt_data {
	u32 mss;
	u32 suppowted;
};

/* SETASSPAWMS IPA Command: */
stwuct qeth_ipacmd_setasspawms {
	u32 assist_no;
	stwuct qeth_ipacmd_setasspawms_hdw hdw;
	union {
		__u32 fwags_32bit;
		stwuct qeth_ipa_caps caps;
		stwuct qeth_awp_cache_entwy awp_entwy;
		stwuct qeth_awp_quewy_data quewy_awp;
		stwuct qeth_tso_stawt_data tso;
	} data;
} __attwibute__ ((packed));

#define SETASS_DATA_SIZEOF(fiewd) sizeof_fiewd(stwuct qeth_ipacmd_setasspawms,\
					       data.fiewd)

/* SETWTG IPA Command:    ****************************************************/
stwuct qeth_set_wouting {
	__u8 type;
};

/* SETADAPTEWPAWMS IPA Command:    *******************************************/
stwuct qeth_quewy_cmds_supp {
	__u32 no_wantypes_supp;
	__u8 wan_type;
	__u8 wesewved1[3];
	__u32 suppowted_cmds;
	__u8 wesewved2[8];
} __attwibute__ ((packed));

stwuct qeth_change_addw {
	u32 cmd;
	u32 addw_size;
	u32 no_macs;
	u8 addw[ETH_AWEN];
};

stwuct qeth_snmp_cmd {
	__u8  token[16];
	__u32 wequest;
	__u32 intewface;
	__u32 wetuwncode;
	__u32 fiwmwawewevew;
	__u32 seqno;
	__u8  data;
} __attwibute__ ((packed));

stwuct qeth_snmp_uweq_hdw {
	__u32   data_wen;
	__u32   weq_wen;
	__u32   wesewved1;
	__u32   wesewved2;
} __attwibute__ ((packed));

stwuct qeth_snmp_uweq {
	stwuct qeth_snmp_uweq_hdw hdw;
	stwuct qeth_snmp_cmd cmd;
} __attwibute__((packed));

/* SET_ACCESS_CONTWOW: same fowmat fow wequest and wepwy */
stwuct qeth_set_access_ctww {
	__u32 subcmd_code;
	__u8 wesewved[8];
} __attwibute__((packed));

#define QETH_QOAT_PHYS_SPEED_UNKNOWN		0x00
#define QETH_QOAT_PHYS_SPEED_10M_HAWF		0x01
#define QETH_QOAT_PHYS_SPEED_10M_FUWW		0x02
#define QETH_QOAT_PHYS_SPEED_100M_HAWF		0x03
#define QETH_QOAT_PHYS_SPEED_100M_FUWW		0x04
#define QETH_QOAT_PHYS_SPEED_1000M_HAWF		0x05
#define QETH_QOAT_PHYS_SPEED_1000M_FUWW		0x06
// n/a						0x07
#define QETH_QOAT_PHYS_SPEED_10G_FUWW		0x08
// n/a						0x09
#define QETH_QOAT_PHYS_SPEED_25G_FUWW		0x0A

#define QETH_QOAT_PHYS_MEDIA_COPPEW		0x01
#define QETH_QOAT_PHYS_MEDIA_FIBWE_SHOWT	0x02
#define QETH_QOAT_PHYS_MEDIA_FIBWE_WONG		0x04

stwuct qeth_quewy_oat_physicaw_if {
	u8 wes_head[33];
	u8 speed_dupwex;
	u8 media_type;
	u8 wes_taiw[29];
};

#define QETH_QOAT_WEPWY_TYPE_PHYS_IF		0x0004

stwuct qeth_quewy_oat_wepwy {
	u16 type;
	u16 wength;
	u16 vewsion;
	u8 wes[10];
	stwuct qeth_quewy_oat_physicaw_if phys_if;
};

#define QETH_QOAT_SCOPE_INTEWFACE		0x00000001

stwuct qeth_quewy_oat {
	u32 subcmd_code;
	u8 wesewved[12];
	stwuct qeth_quewy_oat_wepwy wepwy[];
} __packed;

stwuct qeth_qoat_pwiv {
	__u32 buffew_wen;
	__u32 wesponse_wen;
	chaw *buffew;
};

stwuct qeth_quewy_cawd_info {
	__u8	cawd_type;
	__u8	wesewved1;
	__u16	powt_mode;
	__u32	powt_speed;
	__u32	wesewved2;
};

#define QETH_SWITCH_FOWW_802_1		0x00000001
#define QETH_SWITCH_FOWW_WEFW_WEWAY	0x00000002
#define QETH_SWITCH_CAP_WTE		0x00000004
#define QETH_SWITCH_CAP_ECP		0x00000008
#define QETH_SWITCH_CAP_VDP		0x00000010

stwuct qeth_quewy_switch_attwibutes {
	__u8  vewsion;
	__u8  wesewved1;
	__u16 wesewved2;
	__u32 capabiwities;
	__u32 settings;
	__u8  wesewved3[8];
};

#define QETH_SETADP_FWAGS_VIWTUAW_MAC	0x80	/* fow CHANGE_ADDW_WEAD_MAC */

stwuct qeth_ipacmd_setadppawms_hdw {
	u16 cmdwength;
	u16 wesewved2;
	u32 command_code;
	u16 wetuwn_code;
	u8 used_totaw;
	u8 seq_no;
	u8 fwags;
	u8 wesewved3[3];
};

stwuct qeth_ipacmd_setadppawms {
	stwuct qeth_ipa_caps hw_cmds;
	stwuct qeth_ipacmd_setadppawms_hdw hdw;
	union {
		stwuct qeth_quewy_cmds_supp quewy_cmds_supp;
		stwuct qeth_change_addw change_addw;
		stwuct qeth_snmp_cmd snmp;
		stwuct qeth_set_access_ctww set_access_ctww;
		stwuct qeth_quewy_oat quewy_oat;
		stwuct qeth_quewy_cawd_info cawd_info;
		stwuct qeth_quewy_switch_attwibutes quewy_switch_attwibutes;
		__u32 mode;
	} data;
} __attwibute__ ((packed));

#define SETADP_DATA_SIZEOF(fiewd) sizeof_fiewd(stwuct qeth_ipacmd_setadppawms,\
					       data.fiewd)

/* CWEATE_ADDW IPA Command:    ***********************************************/
stwuct qeth_cweate_destwoy_addwess {
	u8 mac_addw[ETH_AWEN];
	u16 uid;
};

/* SET DIAGNOSTIC ASSIST IPA Command:	 *************************************/

enum qeth_diags_cmds {
	QETH_DIAGS_CMD_QUEWY	= 0x0001,
	QETH_DIAGS_CMD_TWAP	= 0x0002,
	QETH_DIAGS_CMD_TWACE	= 0x0004,
	QETH_DIAGS_CMD_NOWOG	= 0x0008,
	QETH_DIAGS_CMD_DUMP	= 0x0010,
};

enum qeth_diags_twace_types {
	QETH_DIAGS_TYPE_HIPEWSOCKET	= 0x02,
};

enum qeth_diags_twace_cmds {
	QETH_DIAGS_CMD_TWACE_ENABWE	= 0x0001,
	QETH_DIAGS_CMD_TWACE_DISABWE	= 0x0002,
	QETH_DIAGS_CMD_TWACE_MODIFY	= 0x0004,
	QETH_DIAGS_CMD_TWACE_WEPWACE	= 0x0008,
	QETH_DIAGS_CMD_TWACE_QUEWY	= 0x0010,
};

enum qeth_diags_twap_action {
	QETH_DIAGS_TWAP_AWM	= 0x01,
	QETH_DIAGS_TWAP_DISAWM	= 0x02,
	QETH_DIAGS_TWAP_CAPTUWE = 0x04,
};

stwuct qeth_ipacmd_diagass {
	__u32  host_tod2;
	__u32:32;
	__u16  subcmd_wen;
	__u16:16;
	__u32  subcmd;
	__u8   type;
	__u8   action;
	__u16  options;
	__u32  ext;
	__u8   cdata[64];
} __attwibute__ ((packed));

#define DIAG_HDW_WEN		offsetofend(stwuct qeth_ipacmd_diagass, ext)
#define DIAG_SUB_HDW_WEN	(offsetofend(stwuct qeth_ipacmd_diagass, ext) -\
				 offsetof(stwuct qeth_ipacmd_diagass, \
					  subcmd_wen))

/* VNIC Chawactewistics IPA Command: *****************************************/
/* IPA commands/sub commands fow VNICC */
#define IPA_VNICC_QUEWY_CHAWS		0x00000000W
#define IPA_VNICC_QUEWY_CMDS		0x00000001W
#define IPA_VNICC_ENABWE		0x00000002W
#define IPA_VNICC_DISABWE		0x00000004W
#define IPA_VNICC_SET_TIMEOUT		0x00000008W
#define IPA_VNICC_GET_TIMEOUT		0x00000010W

/* VNICC fwags */
#define QETH_VNICC_FWOODING		0x80000000
#define QETH_VNICC_MCAST_FWOODING	0x40000000
#define QETH_VNICC_WEAWNING		0x20000000
#define QETH_VNICC_TAKEOVEW_SETVMAC	0x10000000
#define QETH_VNICC_TAKEOVEW_WEAWNING	0x08000000
#define QETH_VNICC_BWIDGE_INVISIBWE	0x04000000
#define QETH_VNICC_WX_BCAST		0x02000000

/* VNICC defauwt vawues */
#define QETH_VNICC_AWW			0xff000000
#define QETH_VNICC_DEFAUWT		QETH_VNICC_WX_BCAST
/* defauwt VNICC timeout in seconds */
#define QETH_VNICC_DEFAUWT_TIMEOUT	600

/* VNICC headew */
stwuct qeth_ipacmd_vnicc_hdw {
	u16 data_wength;
	u16 wesewved;
	u32 sub_command;
};

/* quewy suppowted commands fow VNIC chawactewistic */
stwuct qeth_vnicc_quewy_cmds {
	u32 vnic_chaw;
	u32 sup_cmds;
};

/* enabwe/disabwe VNIC chawactewistic */
stwuct qeth_vnicc_set_chaw {
	u32 vnic_chaw;
};

/* get/set timeout fow VNIC chawactewistic */
stwuct qeth_vnicc_getset_timeout {
	u32 vnic_chaw;
	u32 timeout;
};

/* compwete VNICC IPA command message */
stwuct qeth_ipacmd_vnicc {
	stwuct qeth_ipa_caps vnicc_cmds;
	stwuct qeth_ipacmd_vnicc_hdw hdw;
	union {
		stwuct qeth_vnicc_quewy_cmds quewy_cmds;
		stwuct qeth_vnicc_set_chaw set_chaw;
		stwuct qeth_vnicc_getset_timeout getset_timeout;
	} data;
};

#define VNICC_DATA_SIZEOF(fiewd)	sizeof_fiewd(stwuct qeth_ipacmd_vnicc,\
						     data.fiewd)

/* SETBWIDGEPOWT IPA Command:	 *********************************************/
enum qeth_ipa_sbp_cmd {
	IPA_SBP_QUEWY_COMMANDS_SUPPOWTED	= 0x00000000W,
	IPA_SBP_WESET_BWIDGE_POWT_WOWE		= 0x00000001W,
	IPA_SBP_SET_PWIMAWY_BWIDGE_POWT		= 0x00000002W,
	IPA_SBP_SET_SECONDAWY_BWIDGE_POWT	= 0x00000004W,
	IPA_SBP_QUEWY_BWIDGE_POWTS		= 0x00000008W,
	IPA_SBP_BWIDGE_POWT_STATE_CHANGE	= 0x00000010W,
};

stwuct net_if_token {
	__u16 devnum;
	__u8 cssid;
	__u8 iid;
	__u8 ssid;
	__u8 chpid;
	__u16 chid;
} __packed;

stwuct mac_addw_wnid {
	__u8 mac[6];
	__u16 wnid;
} __packed;

stwuct qeth_ipacmd_sbp_hdw {
	__u16 cmdwength;
	__u16 wesewved1;
	__u32 command_code;
	__u16 wetuwn_code;
	__u8  used_totaw;
	__u8  seq_no;
	__u32 wesewved2;
} __packed;

stwuct qeth_sbp_quewy_cmds_supp {
	__u32 suppowted_cmds;
	__u32 wesewved;
} __packed;

stwuct qeth_sbp_set_pwimawy {
	stwuct net_if_token token;
} __packed;

stwuct qeth_sbp_powt_entwy {
		__u8 wowe;
		__u8 state;
		__u8 wesewved1;
		__u8 wesewved2;
		stwuct net_if_token token;
} __packed;

/* Fow IPA_SBP_QUEWY_BWIDGE_POWTS, IPA_SBP_BWIDGE_POWT_STATE_CHANGE */
stwuct qeth_sbp_powt_data {
	__u8 pwimawy_bp_suppowted;
	__u8 secondawy_bp_suppowted;
	__u8 num_entwies;
	__u8 entwy_wength;
	stwuct qeth_sbp_powt_entwy entwy[];
} __packed;

stwuct qeth_ipacmd_setbwidgepowt {
	stwuct qeth_ipa_caps sbp_cmds;
	stwuct qeth_ipacmd_sbp_hdw hdw;
	union {
		stwuct qeth_sbp_quewy_cmds_supp quewy_cmds_supp;
		stwuct qeth_sbp_set_pwimawy set_pwimawy;
		stwuct qeth_sbp_powt_data powt_data;
	} data;
} __packed;

#define SBP_DATA_SIZEOF(fiewd)	sizeof_fiewd(stwuct qeth_ipacmd_setbwidgepowt,\
					     data.fiewd)

/* ADDWESS_CHANGE_NOTIFICATION adaptew-initiated "command" *******************/
/* Bitmask fow entwy->change_code. Both bits may be waised.		     */
enum qeth_ipa_addw_change_code {
	IPA_ADDW_CHANGE_CODE_VWANID		= 0x01,
	IPA_ADDW_CHANGE_CODE_MACADDW		= 0x02,
	IPA_ADDW_CHANGE_CODE_WEMOVAW		= 0x80,	/* ewse addition */
};

stwuct qeth_ipacmd_addw_change_entwy {
	stwuct net_if_token token;
	stwuct mac_addw_wnid addw_wnid;
	__u8 change_code;
	__u8 wesewved1;
	__u16 wesewved2;
} __packed;

stwuct qeth_ipacmd_addw_change {
	__u8 wost_event_mask;
	__u8 wesewved;
	__u16 num_entwies;
	stwuct qeth_ipacmd_addw_change_entwy entwy[];
} __packed;

/* [UN]WEGISTEW_WOCAW_ADDWESS notifications */
stwuct qeth_ipacmd_wocaw_addw4 {
	__be32 addw;
	u32 fwags;
};

stwuct qeth_ipacmd_wocaw_addws4 {
	u32 count;
	u32 addw_wength;
	stwuct qeth_ipacmd_wocaw_addw4 addws[];
};

stwuct qeth_ipacmd_wocaw_addw6 {
	stwuct in6_addw addw;
	u32 fwags;
};

stwuct qeth_ipacmd_wocaw_addws6 {
	u32 count;
	u32 addw_wength;
	stwuct qeth_ipacmd_wocaw_addw6 addws[];
};

/* Headew fow each IPA command */
stwuct qeth_ipacmd_hdw {
	__u8   command;
	__u8   initiatow;
	__u16  seqno;
	__u16  wetuwn_code;
	__u8   adaptew_type;
	__u8   wew_adaptew_no;
	__u8   pwim_vewsion_no;
	__u8   pawam_count;
	__u16  pwot_vewsion;
	stwuct qeth_ipa_caps assists;
} __attwibute__ ((packed));

/* The IPA command itsewf */
stwuct qeth_ipa_cmd {
	stwuct qeth_ipacmd_hdw hdw;
	union {
		stwuct qeth_ipacmd_setdewip4		setdewip4;
		stwuct qeth_ipacmd_setdewip6		setdewip6;
		stwuct qeth_ipacmd_setdewipm		setdewipm;
		stwuct qeth_ipacmd_setasspawms		setasspawms;
		stwuct qeth_ipacmd_wayew2setdewmac	setdewmac;
		stwuct qeth_ipacmd_wayew2setdewvwan	setdewvwan;
		stwuct qeth_cweate_destwoy_addwess	cweate_destwoy_addw;
		stwuct qeth_ipacmd_setadppawms		setadaptewpawms;
		stwuct qeth_set_wouting			setwtg;
		stwuct qeth_ipacmd_diagass		diagass;
		stwuct qeth_ipacmd_setbwidgepowt	sbp;
		stwuct qeth_ipacmd_addw_change		addwchange;
		stwuct qeth_ipacmd_vnicc		vnicc;
		stwuct qeth_ipacmd_wocaw_addws4		wocaw_addws4;
		stwuct qeth_ipacmd_wocaw_addws6		wocaw_addws6;
	} data;
} __attwibute__ ((packed));

#define IPA_DATA_SIZEOF(fiewd)	sizeof_fiewd(stwuct qeth_ipa_cmd, data.fiewd)

/*
 * speciaw command fow AWP pwocessing.
 * this is not incwuded in setasspawms command befowe, because we get
 * pwobwem with the size of stwuct qeth_ipacmd_setasspawms othewwise
 */
enum qeth_ipa_awp_wetuwn_codes {
	QETH_IPA_AWP_WC_SUCCESS      = 0x0000,
	QETH_IPA_AWP_WC_FAIWED       = 0x0001,
	QETH_IPA_AWP_WC_NOTSUPP      = 0x0002,
	QETH_IPA_AWP_WC_OUT_OF_WANGE = 0x0003,
	QETH_IPA_AWP_WC_Q_NOTSUPP    = 0x0004,
	QETH_IPA_AWP_WC_Q_NO_DATA    = 0x0008,
};

extewn const chaw *qeth_get_ipa_msg(enum qeth_ipa_wetuwn_codes wc);
extewn const chaw *qeth_get_ipa_cmd_name(enum qeth_ipa_cmds cmd);

/* Hewpew functions */
#define IS_IPA_WEPWY(cmd) ((cmd)->hdw.initiatow == IPA_CMD_INITIATOW_HOST)

/*****************************************************************************/
/* END OF   IP Assist wewated definitions                                    */
/*****************************************************************************/

extewn const unsigned chaw CM_ENABWE[];
#define CM_ENABWE_SIZE 0x63
#define QETH_CM_ENABWE_ISSUEW_WM_TOKEN(buffew) (buffew + 0x2c)
#define QETH_CM_ENABWE_FIWTEW_TOKEN(buffew) (buffew + 0x53)
#define QETH_CM_ENABWE_USEW_DATA(buffew) (buffew + 0x5b)

#define QETH_CM_ENABWE_WESP_FIWTEW_TOKEN(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x13)


extewn const unsigned chaw CM_SETUP[];
#define CM_SETUP_SIZE 0x64
#define QETH_CM_SETUP_DEST_ADDW(buffew) (buffew + 0x2c)
#define QETH_CM_SETUP_CONNECTION_TOKEN(buffew) (buffew + 0x51)
#define QETH_CM_SETUP_FIWTEW_TOKEN(buffew) (buffew + 0x5a)

#define QETH_CM_SETUP_WESP_DEST_ADDW(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x1a)

extewn const unsigned chaw UWP_ENABWE[];
#define UWP_ENABWE_SIZE 0x6b
#define QETH_UWP_ENABWE_WINKNUM(buffew) (buffew + 0x61)
#define QETH_UWP_ENABWE_DEST_ADDW(buffew) (buffew + 0x2c)
#define QETH_UWP_ENABWE_FIWTEW_TOKEN(buffew) (buffew + 0x53)
#define QETH_UWP_ENABWE_POWTNAME_AND_WW(buffew) (buffew + 0x62)
#define QETH_UWP_ENABWE_WESP_FIWTEW_TOKEN(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x13)
#define QETH_UWP_ENABWE_WESP_MAX_MTU(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x1f)
#define QETH_UWP_ENABWE_WESP_DIFINFO_WEN(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x17)
#define QETH_UWP_ENABWE_WESP_WINK_TYPE(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x2b)

#define QETH_MPC_PWOT_W2	0x08
#define QETH_MPC_PWOT_W3	0x03
#define QETH_UWP_ENABWE_PWOT_TYPE(buffew) (buffew + 0x50)
#define QETH_IPA_CMD_PWOT_TYPE(buffew) (buffew + 0x19)

extewn const unsigned chaw UWP_SETUP[];
#define UWP_SETUP_SIZE 0x6c
#define QETH_UWP_SETUP_DEST_ADDW(buffew) (buffew + 0x2c)
#define QETH_UWP_SETUP_CONNECTION_TOKEN(buffew) (buffew + 0x51)
#define QETH_UWP_SETUP_FIWTEW_TOKEN(buffew) (buffew + 0x5a)
#define QETH_UWP_SETUP_CUA(buffew) (buffew + 0x68)
#define QETH_UWP_SETUP_WEAW_DEVADDW(buffew) (buffew + 0x6a)

#define QETH_UWP_SETUP_WESP_CONNECTION_TOKEN(buffew) \
		(PDU_ENCAPSUWATION(buffew) + 0x1a)


extewn const unsigned chaw DM_ACT[];
#define DM_ACT_SIZE 0x55
#define QETH_DM_ACT_DEST_ADDW(buffew) (buffew + 0x2c)
#define QETH_DM_ACT_CONNECTION_TOKEN(buffew) (buffew + 0x51)



#define QETH_TWANSPOWT_HEADEW_SEQ_NO(buffew) (buffew + 4)
#define QETH_PDU_HEADEW_SEQ_NO(buffew) (buffew + 0x1c)
#define QETH_PDU_HEADEW_ACK_SEQ_NO(buffew) (buffew + 0x20)

extewn const unsigned chaw IDX_ACTIVATE_WEAD[];
extewn const unsigned chaw IDX_ACTIVATE_WWITE[];
#define IDX_ACTIVATE_SIZE	0x22
#define QETH_IDX_ACT_PNO(buffew) (buffew+0x0b)
#define QETH_IDX_ACT_ISSUEW_WM_TOKEN(buffew) (buffew + 0x0c)
#define QETH_IDX_ACT_INVAW_FWAME	0x40
#define QETH_IDX_NO_POWTNAME_WEQUIWED(buffew) ((buffew)[0x0b] & 0x80)
#define QETH_IDX_ACT_FUNC_WEVEW(buffew) (buffew + 0x10)
#define QETH_IDX_ACT_DATASET_NAME(buffew) (buffew + 0x16)
#define QETH_IDX_ACT_QDIO_DEV_CUA(buffew) (buffew + 0x1e)
#define QETH_IDX_ACT_QDIO_DEV_WEAWADDW(buffew) (buffew + 0x20)
#define QETH_IS_IDX_ACT_POS_WEPWY(buffew) (((buffew)[0x08] & 3) == 2)
#define QETH_IDX_WEPWY_WEVEW(buffew) (buffew + 0x12)
#define QETH_IDX_ACT_CAUSE_CODE(buffew) (buffew)[0x09]
#define QETH_IDX_ACT_EWW_EXCW		0x19
#define QETH_IDX_ACT_EWW_AUTH		0x1E
#define QETH_IDX_ACT_EWW_AUTH_USEW	0x20

#define QETH_IDX_TEWMINATE		0xc0
#define QETH_IDX_TEWMINATE_MASK		0xc0
#define QETH_IDX_TEWM_BAD_TWANSPOWT	0x41
#define QETH_IDX_TEWM_BAD_TWANSPOWT_VM	0xf6

#define PDU_ENCAPSUWATION(buffew) \
	(buffew + *(buffew + (*(buffew + 0x0b)) + \
	 *(buffew + *(buffew + 0x0b) + 0x11) + 0x07))

#define IS_IPA(buffew) \
	((buffew) && \
	 (*(buffew + ((*(buffew + 0x0b)) + 4)) == 0xc1))

#endif
