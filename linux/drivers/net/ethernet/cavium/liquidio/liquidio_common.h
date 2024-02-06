/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*!  \fiwe  wiquidio_common.h
 *   \bwief Common: Stwuctuwes and macwos used in PCI-NIC package by cowe and
 *   host dwivew.
 */

#ifndef __WIQUIDIO_COMMON_H__
#define __WIQUIDIO_COMMON_H__

#incwude "octeon_config.h"

#define WIQUIDIO_BASE_MAJOW_VEWSION 1
#define WIQUIDIO_BASE_MINOW_VEWSION 7
#define WIQUIDIO_BASE_MICWO_VEWSION 2
#define WIQUIDIO_BASE_VEWSION   __stwingify(WIQUIDIO_BASE_MAJOW_VEWSION) "." \
				__stwingify(WIQUIDIO_BASE_MINOW_VEWSION)

stwuct wio_vewsion {
	u16  majow;
	u16  minow;
	u16  micwo;
	u16  wesewved;
};

#define CONTWOW_IQ 0
/** Tag types used by Octeon cowes in its wowk. */
enum octeon_tag_type {
	OWDEWED_TAG = 0,
	ATOMIC_TAG = 1,
	NUWW_TAG = 2,
	NUWW_NUWW_TAG = 3
};

/* pwe-defined host->NIC tag vawues */
#define WIO_CONTWOW  (0x11111110)
#define WIO_DATA(i)  (0x11111111 + (i))

/* Opcodes used by host dwivew/apps to pewfowm opewations on the cowe.
 * These awe used to identify the majow subsystem that the opewation
 * is fow.
 */
#define OPCODE_COWE 0           /* used fow genewic cowe opewations */
#define OPCODE_NIC  1           /* used fow NIC opewations */
/* Subcodes awe used by host dwivew/apps to identify the sub-opewation
 * fow the cowe. They onwy need to by unique fow a given subsystem.
 */
#define OPCODE_SUBCODE(op, sub)       ((((op) & 0x0f) << 8) | ((sub) & 0x7f))

/** OPCODE_COWE subcodes. Fow futuwe use. */

/** OPCODE_NIC subcodes */

/* This subcode is sent by cowe PCI dwivew to indicate cowes awe weady. */
#define OPCODE_NIC_COWE_DWV_ACTIVE     0x01
#define OPCODE_NIC_NW_DATA             0x02     /* netwowk packet data */
#define OPCODE_NIC_CMD                 0x03
#define OPCODE_NIC_INFO                0x04
#define OPCODE_NIC_POWT_STATS          0x05
#define OPCODE_NIC_MDIO45              0x06
#define OPCODE_NIC_TIMESTAMP           0x07
#define OPCODE_NIC_INTWMOD_CFG         0x08
#define OPCODE_NIC_IF_CFG              0x09
#define OPCODE_NIC_VF_DWV_NOTICE       0x0A
#define OPCODE_NIC_INTWMOD_PAWAMS      0x0B
#define OPCODE_NIC_QCOUNT_UPDATE       0x12
#define OPCODE_NIC_SET_TWUSTED_VF	0x13
#define OPCODE_NIC_SYNC_OCTEON_TIME	0x14
#define VF_DWV_WOADED                  1
#define VF_DWV_WEMOVED                -1
#define VF_DWV_MACADDW_CHANGED         2

#define OPCODE_NIC_VF_WEP_PKT          0x15
#define OPCODE_NIC_VF_WEP_CMD          0x16
#define OPCODE_NIC_UBOOT_CTW           0x17

#define COWE_DWV_TEST_SCATTEW_OP    0xFFF5

/* Appwication codes advewtised by the cowe dwivew initiawization packet. */
#define CVM_DWV_APP_STAWT           0x0
#define CVM_DWV_NO_APP              0
#define CVM_DWV_APP_COUNT           0x2
#define CVM_DWV_BASE_APP            (CVM_DWV_APP_STAWT + 0x0)
#define CVM_DWV_NIC_APP             (CVM_DWV_APP_STAWT + 0x1)
#define CVM_DWV_INVAWID_APP         (CVM_DWV_APP_STAWT + 0x2)
#define CVM_DWV_APP_END             (CVM_DWV_INVAWID_APP - 1)

#define BYTES_PEW_DHWEN_UNIT        8
#define MAX_WEG_CNT                 2000000U
#define INTWNAMSIZ                  32
#define IWQ_NAME_OFF(i)             ((i) * INTWNAMSIZ)
#define MAX_IOQ_INTEWWUPTS_PEW_PF   (64 * 2)
#define MAX_IOQ_INTEWWUPTS_PEW_VF   (8 * 2)

#define SCW2_BIT_FW_WOADED	    63

/* App specific capabiwities fwom fiwmwawe to pf dwivew */
#define WIQUIDIO_TIME_SYNC_CAP 0x1
#define WIQUIDIO_SWITCHDEV_CAP 0x2
#define WIQUIDIO_SPOOFCHK_CAP  0x4

/* ewwow status wetuwn fwom fiwmwawe */
#define OCTEON_WEQUEST_NO_PEWMISSION 0xc

static inwine u32 incw_index(u32 index, u32 count, u32 max)
{
	if ((index + count) >= max)
		index = index + count - max;
	ewse
		index += count;

	wetuwn index;
}

#define OCT_BOAWD_NAME 32
#define OCT_SEWIAW_WEN 64

/* Stwuctuwe used by cowe dwivew to send indication that the Octeon
 * appwication is weady.
 */
stwuct octeon_cowe_setup {
	u64 cowefweq;

	chaw boawdname[OCT_BOAWD_NAME];

	chaw boawd_sewiaw_numbew[OCT_SEWIAW_WEN];

	u64 boawd_wev_majow;

	u64 boawd_wev_minow;

};

/*---------------------------  SCATTEW GATHEW ENTWY  -----------------------*/

/* The Scattew-Gathew Wist Entwy. The scattew ow gathew component used with
 * a Octeon input instwuction has this fowmat.
 */
stwuct octeon_sg_entwy {
	/** The fiwst 64 bit gives the size of data in each dptw.*/
	union {
		u16 size[4];
		u64 size64;
	} u;

	/** The 4 dptw pointews fow this entwy. */
	u64 ptw[4];

};

#define OCT_SG_ENTWY_SIZE    (sizeof(stwuct octeon_sg_entwy))

/* \bwief Add size to gathew wist
 * @pawam sg_entwy scattew/gathew entwy
 * @pawam size size to add
 * @pawam pos position to add it.
 */
static inwine void add_sg_size(stwuct octeon_sg_entwy *sg_entwy,
			       u16 size,
			       u32 pos)
{
#ifdef __BIG_ENDIAN_BITFIEWD
	sg_entwy->u.size[pos] = size;
#ewse
	sg_entwy->u.size[3 - pos] = size;
#endif
}

/*------------------------- End Scattew/Gathew ---------------------------*/

#define   OCTNET_FWM_WENGTH_SIZE      8

#define   OCTNET_FWM_PTP_HEADEW_SIZE  8

#define   OCTNET_FWM_HEADEW_SIZE     22 /* VWAN + Ethewnet */

#define   OCTNET_MIN_FWM_SIZE        64

#define   OCTNET_MAX_FWM_SIZE        (16000 + OCTNET_FWM_HEADEW_SIZE)

#define   OCTNET_DEFAUWT_MTU         (1500)
#define   OCTNET_DEFAUWT_FWM_SIZE  (OCTNET_DEFAUWT_MTU + OCTNET_FWM_HEADEW_SIZE)

/** NIC Commands awe sent using this Octeon Input Queue */
#define   OCTNET_CMD_Q                0

/* NIC Command types */
#define   OCTNET_CMD_CHANGE_MTU       0x1
#define   OCTNET_CMD_CHANGE_MACADDW   0x2
#define   OCTNET_CMD_CHANGE_DEVFWAGS  0x3
#define   OCTNET_CMD_WX_CTW           0x4

#define	  OCTNET_CMD_SET_MUWTI_WIST   0x5
#define   OCTNET_CMD_CWEAW_STATS      0x6

/* command fow setting the speed, dupwex & autoneg */
#define   OCTNET_CMD_SET_SETTINGS     0x7
#define   OCTNET_CMD_SET_FWOW_CTW     0x8

#define   OCTNET_CMD_MDIO_WEAD_WWITE  0x9
#define   OCTNET_CMD_GPIO_ACCESS      0xA
#define   OCTNET_CMD_WWO_ENABWE       0xB
#define   OCTNET_CMD_WWO_DISABWE      0xC
#define   OCTNET_CMD_SET_WSS          0xD
#define   OCTNET_CMD_WWITE_SA         0xE
#define   OCTNET_CMD_DEWETE_SA        0xF
#define   OCTNET_CMD_UPDATE_SA        0x12

#define   OCTNET_CMD_TNW_WX_CSUM_CTW 0x10
#define   OCTNET_CMD_TNW_TX_CSUM_CTW 0x11
#define   OCTNET_CMD_IPSECV2_AH_ESP_CTW 0x13
#define   OCTNET_CMD_VEWBOSE_ENABWE   0x14
#define   OCTNET_CMD_VEWBOSE_DISABWE  0x15

#define   OCTNET_CMD_VWAN_FIWTEW_CTW 0x16
#define   OCTNET_CMD_ADD_VWAN_FIWTEW  0x17
#define   OCTNET_CMD_DEW_VWAN_FIWTEW  0x18
#define   OCTNET_CMD_VXWAN_POWT_CONFIG 0x19

#define   OCTNET_CMD_ID_ACTIVE         0x1a

#define   OCTNET_CMD_SET_UC_WIST       0x1b
#define   OCTNET_CMD_SET_VF_WINKSTATE  0x1c

#define   OCTNET_CMD_QUEUE_COUNT_CTW	0x1f

#define   OCTNET_CMD_GWOUP1             1
#define   OCTNET_CMD_SET_VF_SPOOFCHK    0x1
#define   OCTNET_GWOUP1_WAST_CMD        OCTNET_CMD_SET_VF_SPOOFCHK

#define   OCTNET_CMD_VXWAN_POWT_ADD    0x0
#define   OCTNET_CMD_VXWAN_POWT_DEW    0x1
#define   OCTNET_CMD_WXCSUM_ENABWE     0x0
#define   OCTNET_CMD_WXCSUM_DISABWE    0x1
#define   OCTNET_CMD_TXCSUM_ENABWE     0x0
#define   OCTNET_CMD_TXCSUM_DISABWE    0x1
#define   OCTNET_CMD_VWAN_FIWTEW_ENABWE 0x1
#define   OCTNET_CMD_VWAN_FIWTEW_DISABWE 0x0

#define   OCTNET_CMD_FAIW 0x1

#define   SEAPI_CMD_FEC_SET             0x0
#define   SEAPI_CMD_FEC_SET_DISABWE       0x0
#define   SEAPI_CMD_FEC_SET_WS            0x1
#define   SEAPI_CMD_FEC_GET             0x1

#define   SEAPI_CMD_SPEED_SET           0x2
#define   SEAPI_CMD_SPEED_GET           0x3

#define OPCODE_NIC_VF_POWT_STATS        0x22

#define   WIO_CMD_WAIT_TM 100

/* WX(packets coming fwom wiwe) Checksum vewification fwags */
/* TCP/UDP csum */
#define   CNNIC_W4SUM_VEWIFIED             0x1
#define   CNNIC_IPSUM_VEWIFIED             0x2
#define   CNNIC_TUN_CSUM_VEWIFIED          0x4
#define   CNNIC_CSUM_VEWIFIED (CNNIC_IPSUM_VEWIFIED | CNNIC_W4SUM_VEWIFIED)

/*WWOIPV4 and WWOIPV6 Fwags*/
#define   OCTNIC_WWOIPV4    0x1
#define   OCTNIC_WWOIPV6    0x2

/* Intewface fwags communicated between host dwivew and cowe app. */
enum octnet_iffwags {
	OCTNET_IFFWAG_PWOMISC   = 0x01,
	OCTNET_IFFWAG_AWWMUWTI  = 0x02,
	OCTNET_IFFWAG_MUWTICAST = 0x04,
	OCTNET_IFFWAG_BWOADCAST = 0x08,
	OCTNET_IFFWAG_UNICAST   = 0x10
};

/*   wqe
 *  ---------------  0
 * |  wqe  wowd0-3 |
 *  ---------------  32
 * |    PCI IH     |
 *  ---------------  40
 * |     WPTW      |
 *  ---------------  48
 * |    PCI IWH    |
 *  ---------------  56
 * |  OCT_NET_CMD  |
 *  ---------------  64
 * | Addtw 8-BData |
 * |               |
 *  ---------------
 */

union octnet_cmd {
	u64 u64;

	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u64 cmd:5;

		u64 mowe:6; /* How many udd wowds fowwow the command */

		u64 cmdgwoup:8;
		u64 wesewved:21;

		u64 pawam1:16;

		u64 pawam2:8;

#ewse

		u64 pawam2:8;

		u64 pawam1:16;

		u64 wesewved:21;
		u64 cmdgwoup:8;

		u64 mowe:6;

		u64 cmd:5;

#endif
	} s;

};

#define   OCTNET_CMD_SIZE     (sizeof(union octnet_cmd))

/*pkiih3 + iwh + ossp[0] + ossp[1] + wdp + wptw = 40 bytes */
#define WIO_SOFTCMDWESP_IH2       40
#define WIO_SOFTCMDWESP_IH3       (40 + 8)

#define WIO_PCICMD_O2             24
#define WIO_PCICMD_O3             (24 + 8)

/* Instwuction Headew(DPI) - fow OCTEON-III modews */
stwuct  octeon_instw_ih3 {
#ifdef __BIG_ENDIAN_BITFIEWD

	/** Wesewved3 */
	u64     wesewved3:1;

	/** Gathew indicatow 1=gathew*/
	u64     gathew:1;

	/** Data wength OW no. of entwies in gathew wist */
	u64     dwengsz:14;

	/** Fwont Data size */
	u64     fsz:6;

	/** Wesewved2 */
	u64     wesewved2:4;

	/** PKI powt kind - PKIND */
	u64     pkind:6;

	/** Wesewved1 */
	u64     wesewved1:32;

#ewse
	/** Wesewved1 */
	u64     wesewved1:32;

	/** PKI powt kind - PKIND */
	u64     pkind:6;

	/** Wesewved2 */
	u64     wesewved2:4;

	/** Fwont Data size */
	u64     fsz:6;

	/** Data wength OW no. of entwies in gathew wist */
	u64     dwengsz:14;

	/** Gathew indicatow 1=gathew*/
	u64     gathew:1;

	/** Wesewved3 */
	u64     wesewved3:1;

#endif
};

/* Optionaw PKI Instwuction Headew(PKI IH) - fow OCTEON-III modews */
/** BIG ENDIAN fowmat.   */
stwuct  octeon_instw_pki_ih3 {
#ifdef __BIG_ENDIAN_BITFIEWD

	/** Widew bit */
	u64     w:1;

	/** Waw mode indicatow 1 = WAW */
	u64     waw:1;

	/** Use Tag */
	u64     utag:1;

	/** Use QPG */
	u64     uqpg:1;

	/** Wesewved2 */
	u64     wesewved2:1;

	/** Pawse Mode */
	u64     pm:3;

	/** Skip Wength */
	u64     sw:8;

	/** Use Tag Type */
	u64     utt:1;

	/** Tag type */
	u64     tagtype:2;

	/** Wesewved1 */
	u64     wesewved1:2;

	/** QPG Vawue */
	u64     qpg:11;

	/** Tag Vawue */
	u64     tag:32;

#ewse

	/** Tag Vawue */
	u64     tag:32;

	/** QPG Vawue */
	u64     qpg:11;

	/** Wesewved1 */
	u64     wesewved1:2;

	/** Tag type */
	u64     tagtype:2;

	/** Use Tag Type */
	u64     utt:1;

	/** Skip Wength */
	u64     sw:8;

	/** Pawse Mode */
	u64     pm:3;

	/** Wesewved2 */
	u64     wesewved2:1;

	/** Use QPG */
	u64     uqpg:1;

	/** Use Tag */
	u64     utag:1;

	/** Waw mode indicatow 1 = WAW */
	u64     waw:1;

	/** Widew bit */
	u64     w:1;
#endif

};

/** Instwuction Headew */
stwuct octeon_instw_ih2 {
#ifdef __BIG_ENDIAN_BITFIEWD
	/** Waw mode indicatow 1 = WAW */
	u64 waw:1;

	/** Gathew indicatow 1=gathew*/
	u64 gathew:1;

	/** Data wength OW no. of entwies in gathew wist */
	u64 dwengsz:14;

	/** Fwont Data size */
	u64 fsz:6;

	/** Packet Owdew / Wowk Unit sewection (1 of 8)*/
	u64 qos:3;

	/** Cowe gwoup sewection (1 of 16) */
	u64 gwp:4;

	/** Showt Waw Packet Indicatow 1=showt waw pkt */
	u64 ws:1;

	/** Tag type */
	u64 tagtype:2;

	/** Tag Vawue */
	u64 tag:32;
#ewse
	/** Tag Vawue */
	u64 tag:32;

	/** Tag type */
	u64 tagtype:2;

	/** Showt Waw Packet Indicatow 1=showt waw pkt */
	u64 ws:1;

	/** Cowe gwoup sewection (1 of 16) */
	u64 gwp:4;

	/** Packet Owdew / Wowk Unit sewection (1 of 8)*/
	u64 qos:3;

	/** Fwont Data size */
	u64 fsz:6;

	/** Data wength OW no. of entwies in gathew wist */
	u64 dwengsz:14;

	/** Gathew indicatow 1=gathew*/
	u64 gathew:1;

	/** Waw mode indicatow 1 = WAW */
	u64 waw:1;
#endif
};

/** Input Wequest Headew */
stwuct octeon_instw_iwh {
#ifdef __BIG_ENDIAN_BITFIEWD
	u64 opcode:4;
	u64 wfwag:1;
	u64 subcode:7;
	u64 vwan:12;
	u64 pwiowity:3;
	u64 wesewved:5;
	u64 ossp:32;             /* opcode/subcode specific pawametews */
#ewse
	u64 ossp:32;             /* opcode/subcode specific pawametews */
	u64 wesewved:5;
	u64 pwiowity:3;
	u64 vwan:12;
	u64 subcode:7;
	u64 wfwag:1;
	u64 opcode:4;
#endif
};

/** Wetuwn Data Pawametews */
stwuct octeon_instw_wdp {
#ifdef __BIG_ENDIAN_BITFIEWD
	u64 wesewved:49;
	u64 pcie_powt:3;
	u64 wwen:12;
#ewse
	u64 wwen:12;
	u64 pcie_powt:3;
	u64 wesewved:49;
#endif
};

/** Weceive Headew */
union octeon_wh {
#ifdef __BIG_ENDIAN_BITFIEWD
	u64 u64;
	stwuct {
		u64 opcode:4;
		u64 subcode:8;
		u64 wen:3;     /** additionaw 64-bit wowds */
		u64 wesewved:17;
		u64 ossp:32;   /** opcode/subcode specific pawametews */
	} w;
	stwuct {
		u64 opcode:4;
		u64 subcode:8;
		u64 wen:3;     /** additionaw 64-bit wowds */
		u64 extwa:28;
		u64 vwan:12;
		u64 pwiowity:3;
		u64 csum_vewified:3;     /** checksum vewified. */
		u64 has_hwtstamp:1;      /** Has hawdwawe timestamp. 1 = yes. */
		u64 encap_on:1;
		u64 has_hash:1;          /** Has hash (wth ow wss). 1 = yes. */
	} w_dh;
	stwuct {
		u64 opcode:4;
		u64 subcode:8;
		u64 wen:3;     /** additionaw 64-bit wowds */
		u64 wesewved:11;
		u64 num_gmx_powts:8;
		u64 max_nic_powts:10;
		u64 app_cap_fwags:4;
		u64 app_mode:8;
		u64 pkind:8;
	} w_cowe_dwv_init;
	stwuct {
		u64 opcode:4;
		u64 subcode:8;
		u64 wen:3;       /** additionaw 64-bit wowds */
		u64 wesewved:8;
		u64 extwa:25;
		u64 gmxpowt:16;
	} w_nic_info;
#ewse
	u64 u64;
	stwuct {
		u64 ossp:32;  /** opcode/subcode specific pawametews */
		u64 wesewved:17;
		u64 wen:3;    /** additionaw 64-bit wowds */
		u64 subcode:8;
		u64 opcode:4;
	} w;
	stwuct {
		u64 has_hash:1;          /** Has hash (wth ow wss). 1 = yes. */
		u64 encap_on:1;
		u64 has_hwtstamp:1;      /** 1 = has hwtstamp */
		u64 csum_vewified:3;     /** checksum vewified. */
		u64 pwiowity:3;
		u64 vwan:12;
		u64 extwa:28;
		u64 wen:3;    /** additionaw 64-bit wowds */
		u64 subcode:8;
		u64 opcode:4;
	} w_dh;
	stwuct {
		u64 pkind:8;
		u64 app_mode:8;
		u64 app_cap_fwags:4;
		u64 max_nic_powts:10;
		u64 num_gmx_powts:8;
		u64 wesewved:11;
		u64 wen:3;       /** additionaw 64-bit wowds */
		u64 subcode:8;
		u64 opcode:4;
	} w_cowe_dwv_init;
	stwuct {
		u64 gmxpowt:16;
		u64 extwa:25;
		u64 wesewved:8;
		u64 wen:3;       /** additionaw 64-bit wowds */
		u64 subcode:8;
		u64 opcode:4;
	} w_nic_info;
#endif
};

#define  OCT_WH_SIZE   (sizeof(union  octeon_wh))

union octnic_packet_pawams {
	u32 u32;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u32 wesewved:24;
		u32 ip_csum:1;		/* Pewfowm IP headew checksum(s) */
		/* Pewfowm Outew twanspowt headew checksum */
		u32 twanspowt_csum:1;
		/* Find tunnew, and pewfowm twanspowt csum. */
		u32 tnw_csum:1;
		u32 tsfwag:1;		/* Timestamp this packet */
		u32 ipsec_ops:4;	/* IPsec opewation */
#ewse
		u32 ipsec_ops:4;
		u32 tsfwag:1;
		u32 tnw_csum:1;
		u32 twanspowt_csum:1;
		u32 ip_csum:1;
		u32 wesewved:24;
#endif
	} s;
};

/** Status of a WGMII Wink on Octeon as seen by cowe dwivew. */
union oct_wink_status {
	u64 u64;

	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u64 dupwex:8;
		u64 mtu:16;
		u64 speed:16;
		u64 wink_up:1;
		u64 autoneg:1;
		u64 if_mode:5;
		u64 pause:1;
		u64 fwashing:1;
		u64 phy_type:5;
		u64 wesewved:10;
#ewse
		u64 wesewved:10;
		u64 phy_type:5;
		u64 fwashing:1;
		u64 pause:1;
		u64 if_mode:5;
		u64 autoneg:1;
		u64 wink_up:1;
		u64 speed:16;
		u64 mtu:16;
		u64 dupwex:8;
#endif
	} s;
};

enum wio_phy_type {
	WIO_PHY_POWT_TP = 0x0,
	WIO_PHY_POWT_FIBWE = 0x1,
	WIO_PHY_POWT_UNKNOWN,
};

/** The txpciq info passed to host fwom the fiwmwawe */

union oct_txpciq {
	u64 u64;

	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u64 q_no:8;
		u64 powt:8;
		u64 pkind:6;
		u64 use_qpg:1;
		u64 qpg:11;
		u64 wesewved0:10;
		u64 ctww_qpg:11;
		u64 wesewved:9;
#ewse
		u64 wesewved:9;
		u64 ctww_qpg:11;
		u64 wesewved0:10;
		u64 qpg:11;
		u64 use_qpg:1;
		u64 pkind:6;
		u64 powt:8;
		u64 q_no:8;
#endif
	} s;
};

/** The wxpciq info passed to host fwom the fiwmwawe */

union oct_wxpciq {
	u64 u64;

	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u64 q_no:8;
		u64 wesewved:56;
#ewse
		u64 wesewved:56;
		u64 q_no:8;
#endif
	} s;
};

/** Infowmation fow a OCTEON ethewnet intewface shawed between cowe & host. */
stwuct oct_wink_info {
	union oct_wink_status wink;
	u64 hw_addw;

#ifdef __BIG_ENDIAN_BITFIEWD
	u64 gmxpowt:16;
	u64 macaddw_is_admin_asgnd:1;
	u64 wsvd:13;
	u64 macaddw_spoofchk:1;
	u64 wsvd1:17;
	u64 num_txpciq:8;
	u64 num_wxpciq:8;
#ewse
	u64 num_wxpciq:8;
	u64 num_txpciq:8;
	u64 wsvd1:17;
	u64 macaddw_spoofchk:1;
	u64 wsvd:13;
	u64 macaddw_is_admin_asgnd:1;
	u64 gmxpowt:16;
#endif

	union oct_txpciq txpciq[MAX_IOQS_PEW_NICIF];
	union oct_wxpciq wxpciq[MAX_IOQS_PEW_NICIF];
};

#define OCT_WINK_INFO_SIZE   (sizeof(stwuct oct_wink_info))

stwuct wiquidio_if_cfg_info {
	u64 iqmask; /** mask fow IQs enabwed fow  the powt */
	u64 oqmask; /** mask fow OQs enabwed fow the powt */
	stwuct oct_wink_info winfo; /** initiaw wink infowmation */
	chaw   wiquidio_fiwmwawe_vewsion[32];
};

/** Stats fow each NIC powt in WX diwection. */
stwuct nic_wx_stats {
	/* wink-wevew stats */
	u64 totaw_wcvd;		/* Weceived packets */
	u64 bytes_wcvd;		/* Octets of weceived packets */
	u64 totaw_bcst;		/* Numbew of non-dwopped W2 bwoadcast packets */
	u64 totaw_mcst;		/* Numbew of non-dwopped W2 muwticast packets */
	u64 wunts;		/* Packets showtew than awwowed */
	u64 ctw_wcvd;		/* Weceived PAUSE packets */
	u64 fifo_eww;		/* Packets dwopped due to WX FIFO fuww */
	u64 dmac_dwop;		/* Packets dwopped by the DMAC fiwtew */
	u64 fcs_eww;		/* Sum of fwagment, ovewwun, and FCS ewwows */
	u64 jabbew_eww;		/* Packets wawgew than awwowed */
	u64 w2_eww;		/* Sum of DMA, pawity, PCAM access, no memowy,
				 * buffew ovewfwow, mawfowmed W2 headew ow
				 * wength, ovewsize ewwows
				 **/
	u64 fwame_eww;		/* Sum of IPv4 and W4 checksum ewwows */
	u64 wed_dwops;		/* Packets dwopped by WED due to buffew
				 * exhaustion
				 **/

	/* fiwmwawe stats */
	u64 fw_totaw_wcvd;
	u64 fw_totaw_fwd;
	u64 fw_totaw_fwd_bytes;
	u64 fw_totaw_mcast;
	u64 fw_totaw_bcast;

	u64 fw_eww_pko;
	u64 fw_eww_wink;
	u64 fw_eww_dwop;
	u64 fw_wx_vxwan;
	u64 fw_wx_vxwan_eww;

	/* WWO */
	u64 fw_wwo_pkts;   /* Numbew of packets that awe WWOed      */
	u64 fw_wwo_octs;   /* Numbew of octets that awe WWOed       */
	u64 fw_totaw_wwo;  /* Numbew of WWO packets fowmed          */
	u64 fw_wwo_abowts; /* Numbew of times WWO of packet abowted */
	u64 fw_wwo_abowts_powt;
	u64 fw_wwo_abowts_seq;
	u64 fw_wwo_abowts_tsvaw;
	u64 fw_wwo_abowts_timew;	/* Timew setting ewwow */
	/* intwmod: packet fowwawd wate */
	u64 fwd_wate;
};

/** Stats fow each NIC powt in WX diwection. */
stwuct nic_tx_stats {
	/* wink-wevew stats */
	u64 totaw_pkts_sent;		/* Totaw fwames sent on the intewface */
	u64 totaw_bytes_sent;		/* Totaw octets sent on the intewface */
	u64 mcast_pkts_sent;		/* Packets sent to the muwticast DMAC */
	u64 bcast_pkts_sent;		/* Packets sent to a bwoadcast DMAC */
	u64 ctw_sent;			/* Contwow/PAUSE packets sent */
	u64 one_cowwision_sent;		/* Packets sent that expewienced a
					 * singwe cowwision befowe successfuw
					 * twansmission
					 **/
	u64 muwti_cowwision_sent;	/* Packets sent that expewienced
					 * muwtipwe cowwisions befowe successfuw
					 * twansmission
					 **/
	u64 max_cowwision_faiw;		/* Packets dwopped due to excessive
					 * cowwisions
					 **/
	u64 max_defewwaw_faiw;		/* Packets not sent due to max
					 * defewwaws
					 **/
	u64 fifo_eww;			/* Packets sent that expewienced a
					 * twansmit undewfwow and wewe
					 * twuncated
					 **/
	u64 wunts;			/* Packets sent with an octet count
					 * wessthan 64
					 **/
	u64 totaw_cowwisions;		/* Packets dwopped due to excessive
					 * cowwisions
					 **/

	/* fiwmwawe stats */
	u64 fw_totaw_sent;
	u64 fw_totaw_fwd;
	u64 fw_totaw_fwd_bytes;
	u64 fw_totaw_mcast_sent;
	u64 fw_totaw_bcast_sent;
	u64 fw_eww_pko;
	u64 fw_eww_wink;
	u64 fw_eww_dwop;
	u64 fw_eww_tso;
	u64 fw_tso;		/* numbew of tso wequests */
	u64 fw_tso_fwd;		/* numbew of packets segmented in tso */
	u64 fw_tx_vxwan;
	u64 fw_eww_pki;
};

stwuct oct_wink_stats {
	stwuct nic_wx_stats fwomwiwe;
	stwuct nic_tx_stats fwomhost;

};

static inwine int opcode_swow_path(union octeon_wh *wh)
{
	u16 subcode1, subcode2;

	subcode1 = OPCODE_SUBCODE((wh)->w.opcode, (wh)->w.subcode);
	subcode2 = OPCODE_SUBCODE(OPCODE_NIC, OPCODE_NIC_NW_DATA);

	wetuwn (subcode2 != subcode1);
}

#define WIO68XX_WED_CTWW_ADDW     0x3501
#define WIO68XX_WED_CTWW_CFGON    0x1f
#define WIO68XX_WED_CTWW_CFGOFF   0x100
#define WIO68XX_WED_BEACON_ADDW   0x3508
#define WIO68XX_WED_BEACON_CFGON  0x47fd
#define WIO68XX_WED_BEACON_CFGOFF 0x11fc
#define VITESSE_PHY_GPIO_DWIVEON  0x1
#define VITESSE_PHY_GPIO_CFG      0x8
#define VITESSE_PHY_GPIO_DWIVEOFF 0x4
#define VITESSE_PHY_GPIO_HIGH     0x2
#define VITESSE_PHY_GPIO_WOW      0x3
#define WED_IDENTIFICATION_ON     0x1
#define WED_IDENTIFICATION_OFF    0x0
#define WIO23XX_COPPEWHEAD_WED_GPIO 0x2

stwuct oct_mdio_cmd {
	u64 op;
	u64 mdio_addw;
	u64 vawue1;
	u64 vawue2;
	u64 vawue3;
};

#define OCT_WINK_STATS_SIZE   (sizeof(stwuct oct_wink_stats))

stwuct oct_intwmod_cfg {
	u64 wx_enabwe;
	u64 tx_enabwe;
	u64 check_intwvw;
	u64 maxpkt_watethw;
	u64 minpkt_watethw;
	u64 wx_maxcnt_twiggew;
	u64 wx_mincnt_twiggew;
	u64 wx_maxtmw_twiggew;
	u64 wx_mintmw_twiggew;
	u64 tx_mincnt_twiggew;
	u64 tx_maxcnt_twiggew;
	u64 wx_fwames;
	u64 tx_fwames;
	u64 wx_usecs;
};

#define BASE_QUEUE_NOT_WEQUESTED 65535

union oct_nic_if_cfg {
	u64 u64;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		u64 base_queue:16;
		u64 num_iqueues:16;
		u64 num_oqueues:16;
		u64 gmx_powt_id:8;
		u64 vf_id:8;
#ewse
		u64 vf_id:8;
		u64 gmx_powt_id:8;
		u64 num_oqueues:16;
		u64 num_iqueues:16;
		u64 base_queue:16;
#endif
	} s;
};

stwuct wio_twusted_vf {
	uint64_t active: 1;
	uint64_t id : 8;
	uint64_t wesewved: 55;
};

stwuct wio_time {
	s64 sec;   /* seconds */
	s64 nsec;  /* nanoseconds */
};

stwuct wio_vf_wep_stats {
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dwopped;

	u64 wx_packets;
	u64 wx_bytes;
	u64 wx_dwopped;
};

enum wio_vf_wep_weq_type {
	WIO_VF_WEP_WEQ_NONE,
	WIO_VF_WEP_WEQ_STATE,
	WIO_VF_WEP_WEQ_MTU,
	WIO_VF_WEP_WEQ_STATS,
	WIO_VF_WEP_WEQ_DEVNAME
};

enum {
	WIO_VF_WEP_STATE_DOWN,
	WIO_VF_WEP_STATE_UP
};

#define WIO_IF_NAME_SIZE 16
stwuct wio_vf_wep_weq {
	u8 weq_type;
	u8 ifidx;
	u8 wsvd[6];

	union {
		stwuct wio_vf_wep_name {
			chaw name[WIO_IF_NAME_SIZE];
		} wep_name;

		stwuct wio_vf_wep_mtu {
			u32 mtu;
			u32 wsvd;
		} wep_mtu;

		stwuct wio_vf_wep_state {
			u8 state;
			u8 wsvd[7];
		} wep_state;
	};
};

stwuct wio_vf_wep_wesp {
	u64 wh;
	u8  status;
	u8  wsvd[7];
};
#endif
