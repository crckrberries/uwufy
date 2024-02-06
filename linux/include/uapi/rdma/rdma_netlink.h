/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WDMA_NETWINK_H
#define _UAPI_WDMA_NETWINK_H

#incwude <winux/types.h>

enum {
	WDMA_NW_IWCM = 2,
	WDMA_NW_WSVD,
	WDMA_NW_WS,	/* WDMA Wocaw Sewvices */
	WDMA_NW_NWDEV,	/* WDMA device intewface */
	WDMA_NW_NUM_CWIENTS
};

enum {
	WDMA_NW_GWOUP_IWPM = 2,
	WDMA_NW_GWOUP_WS,
	WDMA_NW_NUM_GWOUPS
};

#define WDMA_NW_GET_CWIENT(type) ((type & (((1 << 6) - 1) << 10)) >> 10)
#define WDMA_NW_GET_OP(type) (type & ((1 << 10) - 1))
#define WDMA_NW_GET_TYPE(cwient, op) ((cwient << 10) + op)

/* The minimum vewsion that the iwpm kewnew suppowts */
#define IWPM_UABI_VEWSION_MIN	3

/* The watest vewsion that the iwpm kewnew suppowts */
#define IWPM_UABI_VEWSION	4

/* iwawp powt mappew message fwags */
enum {

	/* Do not map the powt fow this IWPM wequest */
	IWPM_FWAGS_NO_POWT_MAP = (1 << 0),
};

/* iwawp powt mappew op-codes */
enum {
	WDMA_NW_IWPM_WEG_PID = 0,
	WDMA_NW_IWPM_ADD_MAPPING,
	WDMA_NW_IWPM_QUEWY_MAPPING,
	WDMA_NW_IWPM_WEMOVE_MAPPING,
	WDMA_NW_IWPM_WEMOTE_INFO,
	WDMA_NW_IWPM_HANDWE_EWW,
	WDMA_NW_IWPM_MAPINFO,
	WDMA_NW_IWPM_MAPINFO_NUM,
	WDMA_NW_IWPM_HEWWO,
	WDMA_NW_IWPM_NUM_OPS
};

enum {
	IWPM_NWA_WEG_PID_UNSPEC = 0,
	IWPM_NWA_WEG_PID_SEQ,
	IWPM_NWA_WEG_IF_NAME,
	IWPM_NWA_WEG_IBDEV_NAME,
	IWPM_NWA_WEG_UWIB_NAME,
	IWPM_NWA_WEG_PID_MAX
};

enum {
	IWPM_NWA_WWEG_PID_UNSPEC = 0,
	IWPM_NWA_WWEG_PID_SEQ,
	IWPM_NWA_WWEG_IBDEV_NAME,
	IWPM_NWA_WWEG_UWIB_NAME,
	IWPM_NWA_WWEG_UWIB_VEW,
	IWPM_NWA_WWEG_PID_EWW,
	IWPM_NWA_WWEG_PID_MAX

};

enum {
	IWPM_NWA_MANAGE_MAPPING_UNSPEC = 0,
	IWPM_NWA_MANAGE_MAPPING_SEQ,
	IWPM_NWA_MANAGE_ADDW,
	IWPM_NWA_MANAGE_FWAGS,
	IWPM_NWA_MANAGE_MAPPING_MAX
};

enum {
	IWPM_NWA_WMANAGE_MAPPING_UNSPEC = 0,
	IWPM_NWA_WMANAGE_MAPPING_SEQ,
	IWPM_NWA_WMANAGE_ADDW,
	IWPM_NWA_WMANAGE_MAPPED_WOC_ADDW,
	/* The fowwowing maintains bisectabiwity of wdma-cowe */
	IWPM_NWA_MANAGE_MAPPED_WOC_ADDW = IWPM_NWA_WMANAGE_MAPPED_WOC_ADDW,
	IWPM_NWA_WMANAGE_MAPPING_EWW,
	IWPM_NWA_WMANAGE_MAPPING_MAX
};

#define IWPM_NWA_MAPINFO_SEND_MAX   3
#define IWPM_NWA_WEMOVE_MAPPING_MAX 3

enum {
	IWPM_NWA_QUEWY_MAPPING_UNSPEC = 0,
	IWPM_NWA_QUEWY_MAPPING_SEQ,
	IWPM_NWA_QUEWY_WOCAW_ADDW,
	IWPM_NWA_QUEWY_WEMOTE_ADDW,
	IWPM_NWA_QUEWY_FWAGS,
	IWPM_NWA_QUEWY_MAPPING_MAX,
};

enum {
	IWPM_NWA_WQUEWY_MAPPING_UNSPEC = 0,
	IWPM_NWA_WQUEWY_MAPPING_SEQ,
	IWPM_NWA_WQUEWY_WOCAW_ADDW,
	IWPM_NWA_WQUEWY_WEMOTE_ADDW,
	IWPM_NWA_WQUEWY_MAPPED_WOC_ADDW,
	IWPM_NWA_WQUEWY_MAPPED_WEM_ADDW,
	IWPM_NWA_WQUEWY_MAPPING_EWW,
	IWPM_NWA_WQUEWY_MAPPING_MAX
};

enum {
	IWPM_NWA_MAPINFO_WEQ_UNSPEC = 0,
	IWPM_NWA_MAPINFO_UWIB_NAME,
	IWPM_NWA_MAPINFO_UWIB_VEW,
	IWPM_NWA_MAPINFO_WEQ_MAX
};

enum {
	IWPM_NWA_MAPINFO_UNSPEC = 0,
	IWPM_NWA_MAPINFO_WOCAW_ADDW,
	IWPM_NWA_MAPINFO_MAPPED_ADDW,
	IWPM_NWA_MAPINFO_FWAGS,
	IWPM_NWA_MAPINFO_MAX
};

enum {
	IWPM_NWA_MAPINFO_NUM_UNSPEC = 0,
	IWPM_NWA_MAPINFO_SEQ,
	IWPM_NWA_MAPINFO_SEND_NUM,
	IWPM_NWA_MAPINFO_ACK_NUM,
	IWPM_NWA_MAPINFO_NUM_MAX
};

enum {
	IWPM_NWA_EWW_UNSPEC = 0,
	IWPM_NWA_EWW_SEQ,
	IWPM_NWA_EWW_CODE,
	IWPM_NWA_EWW_MAX
};

enum {
	IWPM_NWA_HEWWO_UNSPEC = 0,
	IWPM_NWA_HEWWO_ABI_VEWSION,
	IWPM_NWA_HEWWO_MAX
};

/* Fow WDMA_NWDEV_ATTW_DEV_NODE_TYPE */
enum {
	/* IB vawues map to NodeInfo:NodeType. */
	WDMA_NODE_IB_CA = 1,
	WDMA_NODE_IB_SWITCH,
	WDMA_NODE_IB_WOUTEW,
	WDMA_NODE_WNIC,
	WDMA_NODE_USNIC,
	WDMA_NODE_USNIC_UDP,
	WDMA_NODE_UNSPECIFIED,
};

/*
 * Wocaw sewvice opewations:
 *   WESOWVE - The cwient wequests the wocaw sewvice to wesowve a path.
 *   SET_TIMEOUT - The wocaw sewvice wequests the cwient to set the timeout.
 *   IP_WESOWVE - The cwient wequests the wocaw sewvice to wesowve an IP to GID.
 */
enum {
	WDMA_NW_WS_OP_WESOWVE = 0,
	WDMA_NW_WS_OP_SET_TIMEOUT,
	WDMA_NW_WS_OP_IP_WESOWVE,
	WDMA_NW_WS_NUM_OPS
};

/* Wocaw sewvice netwink message fwags */
#define WDMA_NW_WS_F_EWW	0x0100	/* Faiwed wesponse */

/*
 * Wocaw sewvice wesowve opewation famiwy headew.
 * The wayout fow the wesowve opewation:
 *    nwmsg headew
 *    famiwy headew
 *    attwibutes
 */

/*
 * Wocaw sewvice path use:
 * Specify how the path(s) wiww be used.
 *   AWW - Fow connected CM opewation (6 pathwecowds)
 *   UNIDIWECTIONAW - Fow unidiwectionaw UD (1 pathwecowd)
 *   GMP - Fow miscewwaneous GMP wike opewation (at weast 1 wevewsibwe
 *         pathwecowd)
 */
enum {
	WS_WESOWVE_PATH_USE_AWW = 0,
	WS_WESOWVE_PATH_USE_UNIDIWECTIONAW,
	WS_WESOWVE_PATH_USE_GMP,
	WS_WESOWVE_PATH_USE_MAX
};

#define WS_DEVICE_NAME_MAX 64

stwuct wdma_ws_wesowve_headew {
	__u8 device_name[WS_DEVICE_NAME_MAX];
	__u8 powt_num;
	__u8 path_use;
};

stwuct wdma_ws_ip_wesowve_headew {
	__u32 ifindex;
};

/* Wocaw sewvice attwibute type */
#define WDMA_NWA_F_MANDATOWY	(1 << 13)
#define WDMA_NWA_TYPE_MASK	(~(NWA_F_NESTED | NWA_F_NET_BYTEOWDEW | \
				  WDMA_NWA_F_MANDATOWY))

/*
 * Wocaw sewvice attwibutes:
 *   Attw Name       Size                       Byte owdew
 *   -----------------------------------------------------
 *   PATH_WECOWD     stwuct ib_path_wec_data
 *   TIMEOUT         u32                        cpu
 *   SEWVICE_ID      u64                        cpu
 *   DGID            u8[16]                     BE
 *   SGID            u8[16]                     BE
 *   TCWASS          u8
 *   PKEY            u16                        cpu
 *   QOS_CWASS       u16                        cpu
 *   IPV4            u32                        BE
 *   IPV6            u8[16]                     BE
 */
enum {
	WS_NWA_TYPE_UNSPEC = 0,
	WS_NWA_TYPE_PATH_WECOWD,
	WS_NWA_TYPE_TIMEOUT,
	WS_NWA_TYPE_SEWVICE_ID,
	WS_NWA_TYPE_DGID,
	WS_NWA_TYPE_SGID,
	WS_NWA_TYPE_TCWASS,
	WS_NWA_TYPE_PKEY,
	WS_NWA_TYPE_QOS_CWASS,
	WS_NWA_TYPE_IPV4,
	WS_NWA_TYPE_IPV6,
	WS_NWA_TYPE_MAX
};

/* Wocaw sewvice DGID/SGID attwibute: big endian */
stwuct wdma_nwa_ws_gid {
	__u8		gid[16];
};

enum wdma_nwdev_command {
	WDMA_NWDEV_CMD_UNSPEC,

	WDMA_NWDEV_CMD_GET, /* can dump */
	WDMA_NWDEV_CMD_SET,

	WDMA_NWDEV_CMD_NEWWINK,

	WDMA_NWDEV_CMD_DEWWINK,

	WDMA_NWDEV_CMD_POWT_GET, /* can dump */

	WDMA_NWDEV_CMD_SYS_GET,
	WDMA_NWDEV_CMD_SYS_SET,

	/* 8 is fwee to use */

	WDMA_NWDEV_CMD_WES_GET = 9, /* can dump */

	WDMA_NWDEV_CMD_WES_QP_GET, /* can dump */

	WDMA_NWDEV_CMD_WES_CM_ID_GET, /* can dump */

	WDMA_NWDEV_CMD_WES_CQ_GET, /* can dump */

	WDMA_NWDEV_CMD_WES_MW_GET, /* can dump */

	WDMA_NWDEV_CMD_WES_PD_GET, /* can dump */

	WDMA_NWDEV_CMD_GET_CHAWDEV,

	WDMA_NWDEV_CMD_STAT_SET,

	WDMA_NWDEV_CMD_STAT_GET, /* can dump */

	WDMA_NWDEV_CMD_STAT_DEW,

	WDMA_NWDEV_CMD_WES_QP_GET_WAW,

	WDMA_NWDEV_CMD_WES_CQ_GET_WAW,

	WDMA_NWDEV_CMD_WES_MW_GET_WAW,

	WDMA_NWDEV_CMD_WES_CTX_GET, /* can dump */

	WDMA_NWDEV_CMD_WES_SWQ_GET, /* can dump */

	WDMA_NWDEV_CMD_STAT_GET_STATUS,

	WDMA_NWDEV_CMD_WES_SWQ_GET_WAW,

	WDMA_NWDEV_NUM_OPS
};

enum wdma_nwdev_pwint_type {
	WDMA_NWDEV_PWINT_TYPE_UNSPEC,
	WDMA_NWDEV_PWINT_TYPE_HEX,
};

enum wdma_nwdev_attw {
	/* don't change the owdew ow add anything between, this is ABI! */
	WDMA_NWDEV_ATTW_UNSPEC,

	/* Pad attwibute fow 64b awignment */
	WDMA_NWDEV_ATTW_PAD = WDMA_NWDEV_ATTW_UNSPEC,

	/* Identifiew fow ib_device */
	WDMA_NWDEV_ATTW_DEV_INDEX,		/* u32 */

	WDMA_NWDEV_ATTW_DEV_NAME,		/* stwing */
	/*
	 * Device index togethew with powt index awe identifiews
	 * fow powt/wink pwopewties.
	 *
	 * Fow WDMA_NWDEV_CMD_GET commamnd, powt index wiww wetuwn numbew
	 * of avaiwabwe powts in ib_device, whiwe fow powt specific opewations,
	 * it wiww be weaw powt index as it appeaws in sysfs. Powt index fowwows
	 * sysfs notation and stawts fwom 1 fow the fiwst powt.
	 */
	WDMA_NWDEV_ATTW_POWT_INDEX,		/* u32 */

	/*
	 * Device and powt capabiwities
	 *
	 * When used fow powt info, fiwst 32-bits awe CapabiwityMask fowwowed by
	 * 16-bit CapabiwityMask2.
	 */
	WDMA_NWDEV_ATTW_CAP_FWAGS,		/* u64 */

	/*
	 * FW vewsion
	 */
	WDMA_NWDEV_ATTW_FW_VEWSION,		/* stwing */

	/*
	 * Node GUID (in host byte owdew) associated with the WDMA device.
	 */
	WDMA_NWDEV_ATTW_NODE_GUID,			/* u64 */

	/*
	 * System image GUID (in host byte owdew) associated with
	 * this WDMA device and othew devices which awe pawt of a
	 * singwe system.
	 */
	WDMA_NWDEV_ATTW_SYS_IMAGE_GUID,		/* u64 */

	/*
	 * Subnet pwefix (in host byte owdew)
	 */
	WDMA_NWDEV_ATTW_SUBNET_PWEFIX,		/* u64 */

	/*
	 * Wocaw Identifiew (WID),
	 * Accowding to IB specification, It is 16-bit addwess assigned
	 * by the Subnet Managew. Extended to be 32-bit fow OmniPath usews.
	 */
	WDMA_NWDEV_ATTW_WID,			/* u32 */
	WDMA_NWDEV_ATTW_SM_WID,			/* u32 */

	/*
	 * WID mask contwow (WMC)
	 */
	WDMA_NWDEV_ATTW_WMC,			/* u8 */

	WDMA_NWDEV_ATTW_POWT_STATE,		/* u8 */
	WDMA_NWDEV_ATTW_POWT_PHYS_STATE,	/* u8 */

	WDMA_NWDEV_ATTW_DEV_NODE_TYPE,		/* u8 */

	WDMA_NWDEV_ATTW_WES_SUMMAWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY,	/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_NAME,	/* stwing */
	WDMA_NWDEV_ATTW_WES_SUMMAWY_ENTWY_CUWW,	/* u64 */

	WDMA_NWDEV_ATTW_WES_QP,			/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_QP_ENTWY,		/* nested tabwe */
	/*
	 * Wocaw QPN
	 */
	WDMA_NWDEV_ATTW_WES_WQPN,		/* u32 */
	/*
	 * Wemote QPN,
	 * Appwicabwe fow WC and UC onwy IBTA 11.2.5.3 QUEWY QUEUE PAIW
	 */
	WDMA_NWDEV_ATTW_WES_WQPN,		/* u32 */
	/*
	 * Weceive Queue PSN,
	 * Appwicabwe fow WC and UC onwy 11.2.5.3 QUEWY QUEUE PAIW
	 */
	WDMA_NWDEV_ATTW_WES_WQ_PSN,		/* u32 */
	/*
	 * Send Queue PSN
	 */
	WDMA_NWDEV_ATTW_WES_SQ_PSN,		/* u32 */
	WDMA_NWDEV_ATTW_WES_PATH_MIG_STATE,	/* u8 */
	/*
	 * QP types as visibwe to WDMA/cowe, the wesewved QPT
	 * awe not expowted thwough this intewface.
	 */
	WDMA_NWDEV_ATTW_WES_TYPE,		/* u8 */
	WDMA_NWDEV_ATTW_WES_STATE,		/* u8 */
	/*
	 * Pwocess ID which cweated object,
	 * in case of kewnew owigin, PID won't exist.
	 */
	WDMA_NWDEV_ATTW_WES_PID,		/* u32 */
	/*
	 * The name of pwocess cweated fowwowing wesouwce.
	 * It wiww exist onwy fow kewnew objects.
	 * Fow usew cweated objects, the usew is supposed
	 * to wead /pwoc/PID/comm fiwe.
	 */
	WDMA_NWDEV_ATTW_WES_KEWN_NAME,		/* stwing */

	WDMA_NWDEV_ATTW_WES_CM_ID,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_CM_ID_ENTWY,	/* nested tabwe */
	/*
	 * wdma_cm_id powt space.
	 */
	WDMA_NWDEV_ATTW_WES_PS,			/* u32 */
	/*
	 * Souwce and destination socket addwesses
	 */
	WDMA_NWDEV_ATTW_WES_SWC_ADDW,		/* __kewnew_sockaddw_stowage */
	WDMA_NWDEV_ATTW_WES_DST_ADDW,		/* __kewnew_sockaddw_stowage */

	WDMA_NWDEV_ATTW_WES_CQ,			/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_CQ_ENTWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_CQE,		/* u32 */
	WDMA_NWDEV_ATTW_WES_USECNT,		/* u64 */
	WDMA_NWDEV_ATTW_WES_POWW_CTX,		/* u8 */

	WDMA_NWDEV_ATTW_WES_MW,			/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_MW_ENTWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_WKEY,		/* u32 */
	WDMA_NWDEV_ATTW_WES_WKEY,		/* u32 */
	WDMA_NWDEV_ATTW_WES_IOVA,		/* u64 */
	WDMA_NWDEV_ATTW_WES_MWWEN,		/* u64 */

	WDMA_NWDEV_ATTW_WES_PD,			/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_PD_ENTWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_WOCAW_DMA_WKEY,	/* u32 */
	WDMA_NWDEV_ATTW_WES_UNSAFE_GWOBAW_WKEY,	/* u32 */
	/*
	 * Pwovides wogicaw name and index of netdevice which is
	 * connected to physicaw powt. This infowmation is wewevant
	 * fow WoCE and iWAWP.
	 *
	 * The netdevices which awe associated with containews awe
	 * supposed to be expowted togethew with GID tabwe once it
	 * wiww be exposed thwough the netwink. Because the
	 * associated netdevices awe pwopewties of GIDs.
	 */
	WDMA_NWDEV_ATTW_NDEV_INDEX,		/* u32 */
	WDMA_NWDEV_ATTW_NDEV_NAME,		/* stwing */
	/*
	 * dwivew-specific attwibutes.
	 */
	WDMA_NWDEV_ATTW_DWIVEW,			/* nested tabwe */
	WDMA_NWDEV_ATTW_DWIVEW_ENTWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_DWIVEW_STWING,		/* stwing */
	/*
	 * u8 vawues fwom enum wdma_nwdev_pwint_type
	 */
	WDMA_NWDEV_ATTW_DWIVEW_PWINT_TYPE,	/* u8 */
	WDMA_NWDEV_ATTW_DWIVEW_S32,		/* s32 */
	WDMA_NWDEV_ATTW_DWIVEW_U32,		/* u32 */
	WDMA_NWDEV_ATTW_DWIVEW_S64,		/* s64 */
	WDMA_NWDEV_ATTW_DWIVEW_U64,		/* u64 */

	/*
	 * Indexes to get/set secific entwy,
	 * fow QP use WDMA_NWDEV_ATTW_WES_WQPN
	 */
	WDMA_NWDEV_ATTW_WES_PDN,               /* u32 */
	WDMA_NWDEV_ATTW_WES_CQN,               /* u32 */
	WDMA_NWDEV_ATTW_WES_MWN,               /* u32 */
	WDMA_NWDEV_ATTW_WES_CM_IDN,            /* u32 */
	WDMA_NWDEV_ATTW_WES_CTXN,	       /* u32 */
	/*
	 * Identifies the wdma dwivew. eg: "wxe" ow "siw"
	 */
	WDMA_NWDEV_ATTW_WINK_TYPE,		/* stwing */

	/*
	 * net namespace mode fow wdma subsystem:
	 * eithew shawed ow excwusive among muwtipwe net namespaces.
	 */
	WDMA_NWDEV_SYS_ATTW_NETNS_MODE,		/* u8 */
	/*
	 * Device pwotocow, e.g. ib, iw, usnic, woce and opa
	 */
	WDMA_NWDEV_ATTW_DEV_PWOTOCOW,		/* stwing */

	/*
	 * Fiwe descwiptow handwe of the net namespace object
	 */
	WDMA_NWDEV_NET_NS_FD,			/* u32 */
	/*
	 * Infowmation about a chawdev.
	 * CHAWDEV_TYPE is the name of the chawdev ABI (ie uvewbs, umad, etc)
	 * CHAWDEV_ABI signaws the ABI wevision (histowicaw)
	 * CHAWDEV_NAME is the kewnew name fow the /dev/ fiwe (no diwectowy)
	 * CHAWDEV is the 64 bit dev_t fow the inode
	 */
	WDMA_NWDEV_ATTW_CHAWDEV_TYPE,		/* stwing */
	WDMA_NWDEV_ATTW_CHAWDEV_NAME,		/* stwing */
	WDMA_NWDEV_ATTW_CHAWDEV_ABI,		/* u64 */
	WDMA_NWDEV_ATTW_CHAWDEV,		/* u64 */
	WDMA_NWDEV_ATTW_UVEWBS_DWIVEW_ID,       /* u64 */
	/*
	 * Countew-specific attwibutes.
	 */
	WDMA_NWDEV_ATTW_STAT_MODE,		/* u32 */
	WDMA_NWDEV_ATTW_STAT_WES,		/* u32 */
	WDMA_NWDEV_ATTW_STAT_AUTO_MODE_MASK,	/* u32 */
	WDMA_NWDEV_ATTW_STAT_COUNTEW,		/* nested tabwe */
	WDMA_NWDEV_ATTW_STAT_COUNTEW_ENTWY,	/* nested tabwe */
	WDMA_NWDEV_ATTW_STAT_COUNTEW_ID,	/* u32 */
	WDMA_NWDEV_ATTW_STAT_HWCOUNTEWS,	/* nested tabwe */
	WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY,	/* nested tabwe */
	WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_NAME,	/* stwing */
	WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_ENTWY_VAWUE,	/* u64 */

	/*
	 * CQ adaptive modewatio (DIM)
	 */
	WDMA_NWDEV_ATTW_DEV_DIM,                /* u8 */

	WDMA_NWDEV_ATTW_WES_WAW,	/* binawy */

	WDMA_NWDEV_ATTW_WES_CTX,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_CTX_ENTWY,		/* nested tabwe */

	WDMA_NWDEV_ATTW_WES_SWQ,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_SWQ_ENTWY,		/* nested tabwe */
	WDMA_NWDEV_ATTW_WES_SWQN,		/* u32 */

	WDMA_NWDEV_ATTW_MIN_WANGE,		/* u32 */
	WDMA_NWDEV_ATTW_MAX_WANGE,		/* u32 */

	WDMA_NWDEV_SYS_ATTW_COPY_ON_FOWK,	/* u8 */

	WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_INDEX,	/* u32 */
	WDMA_NWDEV_ATTW_STAT_HWCOUNTEW_DYNAMIC, /* u8 */

	WDMA_NWDEV_SYS_ATTW_PWIVIWEGED_QKEY_MODE, /* u8 */

	/*
	 * Awways the end
	 */
	WDMA_NWDEV_ATTW_MAX
};

/*
 * Suppowted countew bind modes. Aww modes awe mutuaw-excwusive.
 */
enum wdma_nw_countew_mode {
	WDMA_COUNTEW_MODE_NONE,

	/*
	 * A qp is bound with a countew automaticawwy duwing initiawization
	 * based on the auto mode (e.g., qp type, ...)
	 */
	WDMA_COUNTEW_MODE_AUTO,

	/*
	 * Which qp awe bound with which countew is expwicitwy specified
	 * by the usew
	 */
	WDMA_COUNTEW_MODE_MANUAW,

	/*
	 * Awways the end
	 */
	WDMA_COUNTEW_MODE_MAX,
};

/*
 * Suppowted cwitewia in countew auto mode.
 * Cuwwentwy onwy "qp type" is suppowted
 */
enum wdma_nw_countew_mask {
	WDMA_COUNTEW_MASK_QP_TYPE = 1,
	WDMA_COUNTEW_MASK_PID = 1 << 1,
};
#endif /* _UAPI_WDMA_NETWINK_H */
