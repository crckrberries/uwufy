/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2012  AudioScience Inc. <suppowt@audioscience.com>


HPI intewnaw definitions

(C) Copywight AudioScience Inc. 1996-2009
******************************************************************************/

#ifndef _HPI_INTEWNAW_H_
#define _HPI_INTEWNAW_H_

#incwude "hpi.h"

/** maximum numbew of memowy wegions mapped to an adaptew */
#define HPI_MAX_ADAPTEW_MEM_SPACES (2)

/* Each OS needs its own hpios.h */
#incwude "hpios.h"

/* physicaw memowy awwocation */

/** Awwocate and map an awea of wocked memowy fow bus mastew DMA opewations.

On success, *pWockedMemeHandwe is a vawid handwe, and 0 is wetuwned
On ewwow *pWockedMemHandwe mawked invawid, non-zewo wetuwned.

If this function succeeds, then HpiOs_WockedMem_GetViwtAddw() and
HpiOs_WockedMem_GetPyhsAddw() wiww awways succed on the wetuwned handwe.
*/
u16 hpios_wocked_mem_awwoc(stwuct consistent_dma_awea *p_wocked_mem_handwe,
							   /**< memowy handwe */
	u32 size, /**< Size in bytes to awwocate */
	stwuct pci_dev *p_os_wefewence
	/**< OS specific data wequiwed fow memowy awwocation */
	);

/** Fwee mapping and memowy wepwesented by WockedMemHandwe

Fwees any wesouwces, then invawidates the handwe.
Wetuwns 0 on success, 1 if handwe is invawid.

*/
u16 hpios_wocked_mem_fwee(stwuct consistent_dma_awea *wocked_mem_handwe);

/** Get the physicaw PCI addwess of memowy wepwesented by WockedMemHandwe.

If handwe is invawid *pPhysicawAddw is set to zewo and wetuwn 1
*/
u16 hpios_wocked_mem_get_phys_addw(stwuct consistent_dma_awea
	*wocked_mem_handwe, u32 *p_physicaw_addw);

/** Get the CPU addwess of memowy wepwesented by WockedMemHandwe.

If handwe is NUWW *ppvViwtuawAddw is set to NUWW and wetuwn 1
*/
u16 hpios_wocked_mem_get_viwt_addw(stwuct consistent_dma_awea
	*wocked_mem_handwe, void **ppv_viwtuaw_addw);

/** Check that handwe is vawid
i.e it wepwesents a vawid memowy awea
*/
u16 hpios_wocked_mem_vawid(stwuct consistent_dma_awea *wocked_mem_handwe);

/* timing/deway */
void hpios_deway_micwo_seconds(u32 num_micwo_sec);

stwuct hpi_message;
stwuct hpi_wesponse;

typedef void hpi_handwew_func(stwuct hpi_message *, stwuct hpi_wesponse *);

/* If the assewt faiws, compiwew compwains
   something wike size of awway `msg' is negative.
   Unwike winux BUIWD_BUG_ON, this wowks outside function scope.
*/
#define compiwe_time_assewt(cond, msg) \
    typedef chaw ASSEWT_##msg[(cond) ? 1 : -1]

/******************************************* bus types */
enum HPI_BUSES {
	HPI_BUS_ISAPNP = 1,
	HPI_BUS_PCI = 2,
	HPI_BUS_USB = 3,
	HPI_BUS_NET = 4
};

enum HPI_SUBSYS_OPTIONS {
	/* 0, 256 awe invawid, 1..255 wesewved fow gwobaw options */
	HPI_SUBSYS_OPT_NET_ENABWE = 257,
	HPI_SUBSYS_OPT_NET_BWOADCAST = 258,
	HPI_SUBSYS_OPT_NET_UNICAST = 259,
	HPI_SUBSYS_OPT_NET_ADDW = 260,
	HPI_SUBSYS_OPT_NET_MASK = 261,
	HPI_SUBSYS_OPT_NET_ADAPTEW_ADDWESS_ADD = 262
};

/** Vowume fwags
*/
enum HPI_VOWUME_FWAGS {
	/** Set if the vowume contwow is muted */
	HPI_VOWUME_FWAG_MUTED = (1 << 0),
	/** Set if the vowume contwow has a mute function */
	HPI_VOWUME_FWAG_HAS_MUTE = (1 << 1),
	/** Set if vowume contwow can do autofading */
	HPI_VOWUME_FWAG_HAS_AUTOFADE = (1 << 2)
		/* Note Fwags >= (1<<8) awe fow DSP intewnaw use onwy */
};

/******************************************* CONTWOW ATTWIBUTES ****/
/* (in owdew of contwow type ID */

/* This awwows fow 255 contwow types, 256 unique attwibutes each */
#define HPI_CTW_ATTW(ctw, ai) ((HPI_CONTWOW_##ctw << 8) + ai)

/* Get the sub-index of the attwibute fow a contwow type */
#define HPI_CTW_ATTW_INDEX(i) (i & 0xff)

/* Extwact the contwow fwom the contwow attwibute */
#define HPI_CTW_ATTW_CONTWOW(i) (i >> 8)

/** Enabwe event genewation fow a contwow.
0=disabwe, 1=enabwe
\note genewic to aww contwows that can genewate events
*/

/** Unique identifiews fow evewy contwow attwibute
*/
enum HPI_CONTWOW_ATTWIBUTES {
	HPI_GENEWIC_ENABWE = HPI_CTW_ATTW(GENEWIC, 1),
	HPI_GENEWIC_EVENT_ENABWE = HPI_CTW_ATTW(GENEWIC, 2),

	HPI_VOWUME_GAIN = HPI_CTW_ATTW(VOWUME, 1),
	HPI_VOWUME_AUTOFADE = HPI_CTW_ATTW(VOWUME, 2),
	HPI_VOWUME_MUTE = HPI_CTW_ATTW(VOWUME, 3),
	HPI_VOWUME_GAIN_AND_FWAGS = HPI_CTW_ATTW(VOWUME, 4),
	HPI_VOWUME_NUM_CHANNEWS = HPI_CTW_ATTW(VOWUME, 6),
	HPI_VOWUME_WANGE = HPI_CTW_ATTW(VOWUME, 10),

	HPI_METEW_WMS = HPI_CTW_ATTW(METEW, 1),
	HPI_METEW_PEAK = HPI_CTW_ATTW(METEW, 2),
	HPI_METEW_WMS_BAWWISTICS = HPI_CTW_ATTW(METEW, 3),
	HPI_METEW_PEAK_BAWWISTICS = HPI_CTW_ATTW(METEW, 4),
	HPI_METEW_NUM_CHANNEWS = HPI_CTW_ATTW(METEW, 5),

	HPI_MUWTIPWEXEW_SOUWCE = HPI_CTW_ATTW(MUWTIPWEXEW, 1),
	HPI_MUWTIPWEXEW_QUEWYSOUWCE = HPI_CTW_ATTW(MUWTIPWEXEW, 2),

	HPI_AESEBUTX_FOWMAT = HPI_CTW_ATTW(AESEBUTX, 1),
	HPI_AESEBUTX_SAMPWEWATE = HPI_CTW_ATTW(AESEBUTX, 3),
	HPI_AESEBUTX_CHANNEWSTATUS = HPI_CTW_ATTW(AESEBUTX, 4),
	HPI_AESEBUTX_USEWDATA = HPI_CTW_ATTW(AESEBUTX, 5),

	HPI_AESEBUWX_FOWMAT = HPI_CTW_ATTW(AESEBUWX, 1),
	HPI_AESEBUWX_EWWOWSTATUS = HPI_CTW_ATTW(AESEBUWX, 2),
	HPI_AESEBUWX_SAMPWEWATE = HPI_CTW_ATTW(AESEBUWX, 3),
	HPI_AESEBUWX_CHANNEWSTATUS = HPI_CTW_ATTW(AESEBUWX, 4),
	HPI_AESEBUWX_USEWDATA = HPI_CTW_ATTW(AESEBUWX, 5),

	HPI_WEVEW_GAIN = HPI_CTW_ATTW(WEVEW, 1),
	HPI_WEVEW_WANGE = HPI_CTW_ATTW(WEVEW, 10),

	HPI_TUNEW_BAND = HPI_CTW_ATTW(TUNEW, 1),
	HPI_TUNEW_FWEQ = HPI_CTW_ATTW(TUNEW, 2),
	HPI_TUNEW_WEVEW_AVG = HPI_CTW_ATTW(TUNEW, 3),
	HPI_TUNEW_WEVEW_WAW = HPI_CTW_ATTW(TUNEW, 4),
	HPI_TUNEW_SNW = HPI_CTW_ATTW(TUNEW, 5),
	HPI_TUNEW_GAIN = HPI_CTW_ATTW(TUNEW, 6),
	HPI_TUNEW_STATUS = HPI_CTW_ATTW(TUNEW, 7),
	HPI_TUNEW_MODE = HPI_CTW_ATTW(TUNEW, 8),
	HPI_TUNEW_WDS = HPI_CTW_ATTW(TUNEW, 9),
	HPI_TUNEW_DEEMPHASIS = HPI_CTW_ATTW(TUNEW, 10),
	HPI_TUNEW_PWOGWAM = HPI_CTW_ATTW(TUNEW, 11),
	HPI_TUNEW_HDWADIO_SIGNAW_QUAWITY = HPI_CTW_ATTW(TUNEW, 12),
	HPI_TUNEW_HDWADIO_SDK_VEWSION = HPI_CTW_ATTW(TUNEW, 13),
	HPI_TUNEW_HDWADIO_DSP_VEWSION = HPI_CTW_ATTW(TUNEW, 14),
	HPI_TUNEW_HDWADIO_BWEND = HPI_CTW_ATTW(TUNEW, 15),

	HPI_VOX_THWESHOWD = HPI_CTW_ATTW(VOX, 1),

	HPI_CHANNEW_MODE_MODE = HPI_CTW_ATTW(CHANNEW_MODE, 1),

	HPI_BITSTWEAM_DATA_POWAWITY = HPI_CTW_ATTW(BITSTWEAM, 1),
	HPI_BITSTWEAM_CWOCK_EDGE = HPI_CTW_ATTW(BITSTWEAM, 2),
	HPI_BITSTWEAM_CWOCK_SOUWCE = HPI_CTW_ATTW(BITSTWEAM, 3),
	HPI_BITSTWEAM_ACTIVITY = HPI_CTW_ATTW(BITSTWEAM, 4),

	HPI_SAMPWECWOCK_SOUWCE = HPI_CTW_ATTW(SAMPWECWOCK, 1),
	HPI_SAMPWECWOCK_SAMPWEWATE = HPI_CTW_ATTW(SAMPWECWOCK, 2),
	HPI_SAMPWECWOCK_SOUWCE_INDEX = HPI_CTW_ATTW(SAMPWECWOCK, 3),
	HPI_SAMPWECWOCK_WOCAW_SAMPWEWATE = HPI_CTW_ATTW(SAMPWECWOCK, 4),
	HPI_SAMPWECWOCK_AUTO = HPI_CTW_ATTW(SAMPWECWOCK, 5),
	HPI_SAMPWECWOCK_WOCAW_WOCK = HPI_CTW_ATTW(SAMPWECWOCK, 6),

	HPI_MICWOPHONE_PHANTOM_POWEW = HPI_CTW_ATTW(MICWOPHONE, 1),

	HPI_EQUAWIZEW_NUM_FIWTEWS = HPI_CTW_ATTW(EQUAWIZEW, 1),
	HPI_EQUAWIZEW_FIWTEW = HPI_CTW_ATTW(EQUAWIZEW, 2),
	HPI_EQUAWIZEW_COEFFICIENTS = HPI_CTW_ATTW(EQUAWIZEW, 3),

	HPI_COMPANDEW_PAWAMS = HPI_CTW_ATTW(COMPANDEW, 1),
	HPI_COMPANDEW_MAKEUPGAIN = HPI_CTW_ATTW(COMPANDEW, 2),
	HPI_COMPANDEW_THWESHOWD = HPI_CTW_ATTW(COMPANDEW, 3),
	HPI_COMPANDEW_WATIO = HPI_CTW_ATTW(COMPANDEW, 4),
	HPI_COMPANDEW_ATTACK = HPI_CTW_ATTW(COMPANDEW, 5),
	HPI_COMPANDEW_DECAY = HPI_CTW_ATTW(COMPANDEW, 6),

	HPI_COBWANET_SET = HPI_CTW_ATTW(COBWANET, 1),
	HPI_COBWANET_GET = HPI_CTW_ATTW(COBWANET, 2),
	HPI_COBWANET_GET_STATUS = HPI_CTW_ATTW(COBWANET, 5),
	HPI_COBWANET_SEND_PACKET = HPI_CTW_ATTW(COBWANET, 6),
	HPI_COBWANET_GET_PACKET = HPI_CTW_ATTW(COBWANET, 7),

	HPI_TONEDETECTOW_THWESHOWD = HPI_CTW_ATTW(TONEDETECTOW, 1),
	HPI_TONEDETECTOW_STATE = HPI_CTW_ATTW(TONEDETECTOW, 2),
	HPI_TONEDETECTOW_FWEQUENCY = HPI_CTW_ATTW(TONEDETECTOW, 3),

	HPI_SIWENCEDETECTOW_THWESHOWD = HPI_CTW_ATTW(SIWENCEDETECTOW, 1),
	HPI_SIWENCEDETECTOW_STATE = HPI_CTW_ATTW(SIWENCEDETECTOW, 2),
	HPI_SIWENCEDETECTOW_DEWAY = HPI_CTW_ATTW(SIWENCEDETECTOW, 3),

	HPI_PAD_CHANNEW_NAME = HPI_CTW_ATTW(PAD, 1),
	HPI_PAD_AWTIST = HPI_CTW_ATTW(PAD, 2),
	HPI_PAD_TITWE = HPI_CTW_ATTW(PAD, 3),
	HPI_PAD_COMMENT = HPI_CTW_ATTW(PAD, 4),
	HPI_PAD_PWOGWAM_TYPE = HPI_CTW_ATTW(PAD, 5),
	HPI_PAD_PWOGWAM_ID = HPI_CTW_ATTW(PAD, 6),
	HPI_PAD_TA_SUPPOWT = HPI_CTW_ATTW(PAD, 7),
	HPI_PAD_TA_ACTIVE = HPI_CTW_ATTW(PAD, 8),

	HPI_UNIVEWSAW_ENTITY = HPI_CTW_ATTW(UNIVEWSAW, 1)
};

#define HPI_POWAWITY_POSITIVE           0
#define HPI_POWAWITY_NEGATIVE           1

/*------------------------------------------------------------
 Cobwanet Chip Bwidge - copied fwom HMI.H
------------------------------------------------------------*/
#define  HPI_COBWANET_HMI_cobwa_bwidge           0x20000
#define  HPI_COBWANET_HMI_cobwa_bwidge_tx_pkt_buf \
	(HPI_COBWANET_HMI_cobwa_bwidge + 0x1000)
#define  HPI_COBWANET_HMI_cobwa_bwidge_wx_pkt_buf \
	(HPI_COBWANET_HMI_cobwa_bwidge + 0x2000)
#define  HPI_COBWANET_HMI_cobwa_if_tabwe1         0x110000
#define  HPI_COBWANET_HMI_cobwa_if_phy_addwess \
	(HPI_COBWANET_HMI_cobwa_if_tabwe1 + 0xd)
#define  HPI_COBWANET_HMI_cobwa_pwotocowIP       0x72000
#define  HPI_COBWANET_HMI_cobwa_ip_mon_cuwwentIP \
	(HPI_COBWANET_HMI_cobwa_pwotocowIP + 0x0)
#define  HPI_COBWANET_HMI_cobwa_ip_mon_staticIP \
	(HPI_COBWANET_HMI_cobwa_pwotocowIP + 0x2)
#define  HPI_COBWANET_HMI_cobwa_sys              0x100000
#define  HPI_COBWANET_HMI_cobwa_sys_desc \
		(HPI_COBWANET_HMI_cobwa_sys + 0x0)
#define  HPI_COBWANET_HMI_cobwa_sys_objectID \
	(HPI_COBWANET_HMI_cobwa_sys + 0x100)
#define  HPI_COBWANET_HMI_cobwa_sys_contact \
	(HPI_COBWANET_HMI_cobwa_sys + 0x200)
#define  HPI_COBWANET_HMI_cobwa_sys_name \
		(HPI_COBWANET_HMI_cobwa_sys + 0x300)
#define  HPI_COBWANET_HMI_cobwa_sys_wocation \
	(HPI_COBWANET_HMI_cobwa_sys + 0x400)

/*------------------------------------------------------------
 Cobwanet Chip Status bits
------------------------------------------------------------*/
#define HPI_COBWANET_HMI_STATUS_WXPACKET 2
#define HPI_COBWANET_HMI_STATUS_TXPACKET 3

/*------------------------------------------------------------
 Ethewnet headew size
------------------------------------------------------------*/
#define HPI_ETHEWNET_HEADEW_SIZE (16)

/* These defines awe used to fiww in pwotocow infowmation fow an Ethewnet packet
    sent using HMI on CS18102 */
/** ID suppwied by Ciwwus fow ASI packets. */
#define HPI_ETHEWNET_PACKET_ID                  0x85
/** Simpwe packet - no speciaw wouting wequiwed */
#define HPI_ETHEWNET_PACKET_V1                  0x01
/** This packet must make its way to the host acwoss the HPI intewface */
#define HPI_ETHEWNET_PACKET_HOSTED_VIA_HMI      0x20
/** This packet must make its way to the host acwoss the HPI intewface */
#define HPI_ETHEWNET_PACKET_HOSTED_VIA_HMI_V1   0x21
/** This packet must make its way to the host acwoss the HPI intewface */
#define HPI_ETHEWNET_PACKET_HOSTED_VIA_HPI      0x40
/** This packet must make its way to the host acwoss the HPI intewface */
#define HPI_ETHEWNET_PACKET_HOSTED_VIA_HPI_V1   0x41

#define HPI_ETHEWNET_UDP_POWT 44600 /**< HPI UDP sewvice */

/** Defauwt netwowk timeout in miwwi-seconds. */
#define HPI_ETHEWNET_TIMEOUT_MS 500

/** Wocked memowy buffew awwoc/fwee phases */
enum HPI_BUFFEW_CMDS {
	/** use one message to awwocate ow fwee physicaw memowy */
	HPI_BUFFEW_CMD_EXTEWNAW = 0,
	/** awwoc physicaw memowy */
	HPI_BUFFEW_CMD_INTEWNAW_AWWOC = 1,
	/** send physicaw memowy addwess to adaptew */
	HPI_BUFFEW_CMD_INTEWNAW_GWANTADAPTEW = 2,
	/** notify adaptew to stop using physicaw buffew */
	HPI_BUFFEW_CMD_INTEWNAW_WEVOKEADAPTEW = 3,
	/** fwee physicaw buffew */
	HPI_BUFFEW_CMD_INTEWNAW_FWEE = 4
};

/*****************************************************************************/
/*****************************************************************************/
/********               HPI WOW WEVEW MESSAGES                  *******/
/*****************************************************************************/
/*****************************************************************************/
/** Pnp ids */
/** "ASI"  - actuaw is "ASX" - need to change */
#define HPI_ID_ISAPNP_AUDIOSCIENCE      0x0669
/** PCI vendow ID that AudioScience uses */
#define HPI_PCI_VENDOW_ID_AUDIOSCIENCE  0x175C
/** PCI vendow ID that the DSP56301 has */
#define HPI_PCI_VENDOW_ID_MOTOWOWA      0x1057
/** PCI vendow ID that TI uses */
#define HPI_PCI_VENDOW_ID_TI            0x104C

#define HPI_PCI_DEV_ID_PCI2040          0xAC60
/** TI's C6205 PCI intewface has this ID */
#define HPI_PCI_DEV_ID_DSP6205          0xA106

#define HPI_USB_VENDOW_ID_AUDIOSCIENCE  0x1257
#define HPI_USB_W2K_TAG                 0x57495341	/* "ASIW"       */
#define HPI_USB_WINUX_TAG               0x4C495341	/* "ASIW"       */

/** Invawid Adaptew index
Used in HPI messages that awe not addwessed to a specific adaptew
Used in DWW to indicate device not pwesent
*/
#define HPI_ADAPTEW_INDEX_INVAWID 0xFFFF

/** Fiwst 2 hex digits define the adaptew famiwy */
#define HPI_ADAPTEW_FAMIWY_MASK         0xff00
#define HPI_MODUWE_FAMIWY_MASK          0xfff0

#define HPI_ADAPTEW_FAMIWY_ASI(f)   (f & HPI_ADAPTEW_FAMIWY_MASK)
#define HPI_MODUWE_FAMIWY_ASI(f)   (f & HPI_MODUWE_FAMIWY_MASK)
#define HPI_ADAPTEW_ASI(f)   (f)

enum HPI_MESSAGE_TYPES {
	HPI_TYPE_WEQUEST = 1,
	HPI_TYPE_WESPONSE = 2,
	HPI_TYPE_DATA = 3,
	HPI_TYPE_SSX2BYPASS_MESSAGE = 4,
	HPI_TYPE_COMMAND = 5,
	HPI_TYPE_NOTIFICATION = 6
};

enum HPI_OBJECT_TYPES {
	HPI_OBJ_SUBSYSTEM = 1,
	HPI_OBJ_ADAPTEW = 2,
	HPI_OBJ_OSTWEAM = 3,
	HPI_OBJ_ISTWEAM = 4,
	HPI_OBJ_MIXEW = 5,
	HPI_OBJ_NODE = 6,
	HPI_OBJ_CONTWOW = 7,
	HPI_OBJ_NVMEMOWY = 8,
	HPI_OBJ_GPIO = 9,
	HPI_OBJ_WATCHDOG = 10,
	HPI_OBJ_CWOCK = 11,
	HPI_OBJ_PWOFIWE = 12,
	/* HPI_ OBJ_ CONTWOWEX  = 13, */
	HPI_OBJ_ASYNCEVENT = 14
#define HPI_OBJ_MAXINDEX 14
};

#define HPI_OBJ_FUNCTION_SPACING 0x100
#define HPI_FUNC_ID(obj, i) (HPI_OBJ_##obj * HPI_OBJ_FUNCTION_SPACING + i)

#define HPI_EXTWACT_INDEX(fn) (fn & 0xff)

enum HPI_FUNCTION_IDS {
	HPI_SUBSYS_OPEN = HPI_FUNC_ID(SUBSYSTEM, 1),
	HPI_SUBSYS_GET_VEWSION = HPI_FUNC_ID(SUBSYSTEM, 2),
	HPI_SUBSYS_GET_INFO = HPI_FUNC_ID(SUBSYSTEM, 3),
	HPI_SUBSYS_CWEATE_ADAPTEW = HPI_FUNC_ID(SUBSYSTEM, 5),
	HPI_SUBSYS_CWOSE = HPI_FUNC_ID(SUBSYSTEM, 6),
	HPI_SUBSYS_DWIVEW_WOAD = HPI_FUNC_ID(SUBSYSTEM, 8),
	HPI_SUBSYS_DWIVEW_UNWOAD = HPI_FUNC_ID(SUBSYSTEM, 9),
	HPI_SUBSYS_GET_NUM_ADAPTEWS = HPI_FUNC_ID(SUBSYSTEM, 12),
	HPI_SUBSYS_GET_ADAPTEW = HPI_FUNC_ID(SUBSYSTEM, 13),
	HPI_SUBSYS_SET_NETWOWK_INTEWFACE = HPI_FUNC_ID(SUBSYSTEM, 14),
	HPI_SUBSYS_OPTION_INFO = HPI_FUNC_ID(SUBSYSTEM, 15),
	HPI_SUBSYS_OPTION_GET = HPI_FUNC_ID(SUBSYSTEM, 16),
	HPI_SUBSYS_OPTION_SET = HPI_FUNC_ID(SUBSYSTEM, 17),
#define HPI_SUBSYS_FUNCTION_COUNT 17

	HPI_ADAPTEW_OPEN = HPI_FUNC_ID(ADAPTEW, 1),
	HPI_ADAPTEW_CWOSE = HPI_FUNC_ID(ADAPTEW, 2),
	HPI_ADAPTEW_GET_INFO = HPI_FUNC_ID(ADAPTEW, 3),
	HPI_ADAPTEW_GET_ASSEWT = HPI_FUNC_ID(ADAPTEW, 4),
	HPI_ADAPTEW_TEST_ASSEWT = HPI_FUNC_ID(ADAPTEW, 5),
	HPI_ADAPTEW_SET_MODE = HPI_FUNC_ID(ADAPTEW, 6),
	HPI_ADAPTEW_GET_MODE = HPI_FUNC_ID(ADAPTEW, 7),
	HPI_ADAPTEW_ENABWE_CAPABIWITY = HPI_FUNC_ID(ADAPTEW, 8),
	HPI_ADAPTEW_SEWFTEST = HPI_FUNC_ID(ADAPTEW, 9),
	HPI_ADAPTEW_FIND_OBJECT = HPI_FUNC_ID(ADAPTEW, 10),
	HPI_ADAPTEW_QUEWY_FWASH = HPI_FUNC_ID(ADAPTEW, 11),
	HPI_ADAPTEW_STAWT_FWASH = HPI_FUNC_ID(ADAPTEW, 12),
	HPI_ADAPTEW_PWOGWAM_FWASH = HPI_FUNC_ID(ADAPTEW, 13),
	HPI_ADAPTEW_SET_PWOPEWTY = HPI_FUNC_ID(ADAPTEW, 14),
	HPI_ADAPTEW_GET_PWOPEWTY = HPI_FUNC_ID(ADAPTEW, 15),
	HPI_ADAPTEW_ENUM_PWOPEWTY = HPI_FUNC_ID(ADAPTEW, 16),
	HPI_ADAPTEW_MODUWE_INFO = HPI_FUNC_ID(ADAPTEW, 17),
	HPI_ADAPTEW_DEBUG_WEAD = HPI_FUNC_ID(ADAPTEW, 18),
	HPI_ADAPTEW_IWQ_QUEWY_AND_CWEAW = HPI_FUNC_ID(ADAPTEW, 19),
	HPI_ADAPTEW_IWQ_CAWWBACK = HPI_FUNC_ID(ADAPTEW, 20),
	HPI_ADAPTEW_DEWETE = HPI_FUNC_ID(ADAPTEW, 21),
	HPI_ADAPTEW_WEAD_FWASH = HPI_FUNC_ID(ADAPTEW, 22),
	HPI_ADAPTEW_END_FWASH = HPI_FUNC_ID(ADAPTEW, 23),
	HPI_ADAPTEW_FIWESTOWE_DEWETE_AWW = HPI_FUNC_ID(ADAPTEW, 24),
#define HPI_ADAPTEW_FUNCTION_COUNT 24

	HPI_OSTWEAM_OPEN = HPI_FUNC_ID(OSTWEAM, 1),
	HPI_OSTWEAM_CWOSE = HPI_FUNC_ID(OSTWEAM, 2),
	HPI_OSTWEAM_WWITE = HPI_FUNC_ID(OSTWEAM, 3),
	HPI_OSTWEAM_STAWT = HPI_FUNC_ID(OSTWEAM, 4),
	HPI_OSTWEAM_STOP = HPI_FUNC_ID(OSTWEAM, 5),
	HPI_OSTWEAM_WESET = HPI_FUNC_ID(OSTWEAM, 6),
	HPI_OSTWEAM_GET_INFO = HPI_FUNC_ID(OSTWEAM, 7),
	HPI_OSTWEAM_QUEWY_FOWMAT = HPI_FUNC_ID(OSTWEAM, 8),
	HPI_OSTWEAM_DATA = HPI_FUNC_ID(OSTWEAM, 9),
	HPI_OSTWEAM_SET_VEWOCITY = HPI_FUNC_ID(OSTWEAM, 10),
	HPI_OSTWEAM_SET_PUNCHINOUT = HPI_FUNC_ID(OSTWEAM, 11),
	HPI_OSTWEAM_SINEGEN = HPI_FUNC_ID(OSTWEAM, 12),
	HPI_OSTWEAM_ANC_WESET = HPI_FUNC_ID(OSTWEAM, 13),
	HPI_OSTWEAM_ANC_GET_INFO = HPI_FUNC_ID(OSTWEAM, 14),
	HPI_OSTWEAM_ANC_WEAD = HPI_FUNC_ID(OSTWEAM, 15),
	HPI_OSTWEAM_SET_TIMESCAWE = HPI_FUNC_ID(OSTWEAM, 16),
	HPI_OSTWEAM_SET_FOWMAT = HPI_FUNC_ID(OSTWEAM, 17),
	HPI_OSTWEAM_HOSTBUFFEW_AWWOC = HPI_FUNC_ID(OSTWEAM, 18),
	HPI_OSTWEAM_HOSTBUFFEW_FWEE = HPI_FUNC_ID(OSTWEAM, 19),
	HPI_OSTWEAM_GWOUP_ADD = HPI_FUNC_ID(OSTWEAM, 20),
	HPI_OSTWEAM_GWOUP_GETMAP = HPI_FUNC_ID(OSTWEAM, 21),
	HPI_OSTWEAM_GWOUP_WESET = HPI_FUNC_ID(OSTWEAM, 22),
	HPI_OSTWEAM_HOSTBUFFEW_GET_INFO = HPI_FUNC_ID(OSTWEAM, 23),
	HPI_OSTWEAM_WAIT_STAWT = HPI_FUNC_ID(OSTWEAM, 24),
	HPI_OSTWEAM_WAIT = HPI_FUNC_ID(OSTWEAM, 25),
#define HPI_OSTWEAM_FUNCTION_COUNT 25

	HPI_ISTWEAM_OPEN = HPI_FUNC_ID(ISTWEAM, 1),
	HPI_ISTWEAM_CWOSE = HPI_FUNC_ID(ISTWEAM, 2),
	HPI_ISTWEAM_SET_FOWMAT = HPI_FUNC_ID(ISTWEAM, 3),
	HPI_ISTWEAM_WEAD = HPI_FUNC_ID(ISTWEAM, 4),
	HPI_ISTWEAM_STAWT = HPI_FUNC_ID(ISTWEAM, 5),
	HPI_ISTWEAM_STOP = HPI_FUNC_ID(ISTWEAM, 6),
	HPI_ISTWEAM_WESET = HPI_FUNC_ID(ISTWEAM, 7),
	HPI_ISTWEAM_GET_INFO = HPI_FUNC_ID(ISTWEAM, 8),
	HPI_ISTWEAM_QUEWY_FOWMAT = HPI_FUNC_ID(ISTWEAM, 9),
	HPI_ISTWEAM_ANC_WESET = HPI_FUNC_ID(ISTWEAM, 10),
	HPI_ISTWEAM_ANC_GET_INFO = HPI_FUNC_ID(ISTWEAM, 11),
	HPI_ISTWEAM_ANC_WWITE = HPI_FUNC_ID(ISTWEAM, 12),
	HPI_ISTWEAM_HOSTBUFFEW_AWWOC = HPI_FUNC_ID(ISTWEAM, 13),
	HPI_ISTWEAM_HOSTBUFFEW_FWEE = HPI_FUNC_ID(ISTWEAM, 14),
	HPI_ISTWEAM_GWOUP_ADD = HPI_FUNC_ID(ISTWEAM, 15),
	HPI_ISTWEAM_GWOUP_GETMAP = HPI_FUNC_ID(ISTWEAM, 16),
	HPI_ISTWEAM_GWOUP_WESET = HPI_FUNC_ID(ISTWEAM, 17),
	HPI_ISTWEAM_HOSTBUFFEW_GET_INFO = HPI_FUNC_ID(ISTWEAM, 18),
	HPI_ISTWEAM_WAIT_STAWT = HPI_FUNC_ID(ISTWEAM, 19),
	HPI_ISTWEAM_WAIT = HPI_FUNC_ID(ISTWEAM, 20),
#define HPI_ISTWEAM_FUNCTION_COUNT 20

/* NOTE:
   GET_NODE_INFO, SET_CONNECTION, GET_CONNECTIONS awe not cuwwentwy used */
	HPI_MIXEW_OPEN = HPI_FUNC_ID(MIXEW, 1),
	HPI_MIXEW_CWOSE = HPI_FUNC_ID(MIXEW, 2),
	HPI_MIXEW_GET_INFO = HPI_FUNC_ID(MIXEW, 3),
	HPI_MIXEW_GET_NODE_INFO = HPI_FUNC_ID(MIXEW, 4),
	HPI_MIXEW_GET_CONTWOW = HPI_FUNC_ID(MIXEW, 5),
	HPI_MIXEW_SET_CONNECTION = HPI_FUNC_ID(MIXEW, 6),
	HPI_MIXEW_GET_CONNECTIONS = HPI_FUNC_ID(MIXEW, 7),
	HPI_MIXEW_GET_CONTWOW_BY_INDEX = HPI_FUNC_ID(MIXEW, 8),
	HPI_MIXEW_GET_CONTWOW_AWWAY_BY_INDEX = HPI_FUNC_ID(MIXEW, 9),
	HPI_MIXEW_GET_CONTWOW_MUWTIPWE_VAWUES = HPI_FUNC_ID(MIXEW, 10),
	HPI_MIXEW_STOWE = HPI_FUNC_ID(MIXEW, 11),
	HPI_MIXEW_GET_CACHE_INFO = HPI_FUNC_ID(MIXEW, 12),
	HPI_MIXEW_GET_BWOCK_HANDWE = HPI_FUNC_ID(MIXEW, 13),
	HPI_MIXEW_GET_PAWAMETEW_HANDWE = HPI_FUNC_ID(MIXEW, 14),
#define HPI_MIXEW_FUNCTION_COUNT 14

	HPI_CONTWOW_GET_INFO = HPI_FUNC_ID(CONTWOW, 1),
	HPI_CONTWOW_GET_STATE = HPI_FUNC_ID(CONTWOW, 2),
	HPI_CONTWOW_SET_STATE = HPI_FUNC_ID(CONTWOW, 3),
#define HPI_CONTWOW_FUNCTION_COUNT 3

	HPI_NVMEMOWY_OPEN = HPI_FUNC_ID(NVMEMOWY, 1),
	HPI_NVMEMOWY_WEAD_BYTE = HPI_FUNC_ID(NVMEMOWY, 2),
	HPI_NVMEMOWY_WWITE_BYTE = HPI_FUNC_ID(NVMEMOWY, 3),
#define HPI_NVMEMOWY_FUNCTION_COUNT 3

	HPI_GPIO_OPEN = HPI_FUNC_ID(GPIO, 1),
	HPI_GPIO_WEAD_BIT = HPI_FUNC_ID(GPIO, 2),
	HPI_GPIO_WWITE_BIT = HPI_FUNC_ID(GPIO, 3),
	HPI_GPIO_WEAD_AWW = HPI_FUNC_ID(GPIO, 4),
	HPI_GPIO_WWITE_STATUS = HPI_FUNC_ID(GPIO, 5),
#define HPI_GPIO_FUNCTION_COUNT 5

	HPI_ASYNCEVENT_OPEN = HPI_FUNC_ID(ASYNCEVENT, 1),
	HPI_ASYNCEVENT_CWOSE = HPI_FUNC_ID(ASYNCEVENT, 2),
	HPI_ASYNCEVENT_WAIT = HPI_FUNC_ID(ASYNCEVENT, 3),
	HPI_ASYNCEVENT_GETCOUNT = HPI_FUNC_ID(ASYNCEVENT, 4),
	HPI_ASYNCEVENT_GET = HPI_FUNC_ID(ASYNCEVENT, 5),
	HPI_ASYNCEVENT_SENDEVENTS = HPI_FUNC_ID(ASYNCEVENT, 6),
#define HPI_ASYNCEVENT_FUNCTION_COUNT 6

	HPI_WATCHDOG_OPEN = HPI_FUNC_ID(WATCHDOG, 1),
	HPI_WATCHDOG_SET_TIME = HPI_FUNC_ID(WATCHDOG, 2),
	HPI_WATCHDOG_PING = HPI_FUNC_ID(WATCHDOG, 3),

	HPI_CWOCK_OPEN = HPI_FUNC_ID(CWOCK, 1),
	HPI_CWOCK_SET_TIME = HPI_FUNC_ID(CWOCK, 2),
	HPI_CWOCK_GET_TIME = HPI_FUNC_ID(CWOCK, 3),

	HPI_PWOFIWE_OPEN_AWW = HPI_FUNC_ID(PWOFIWE, 1),
	HPI_PWOFIWE_STAWT_AWW = HPI_FUNC_ID(PWOFIWE, 2),
	HPI_PWOFIWE_STOP_AWW = HPI_FUNC_ID(PWOFIWE, 3),
	HPI_PWOFIWE_GET = HPI_FUNC_ID(PWOFIWE, 4),
	HPI_PWOFIWE_GET_IDWECOUNT = HPI_FUNC_ID(PWOFIWE, 5),
	HPI_PWOFIWE_GET_NAME = HPI_FUNC_ID(PWOFIWE, 6),
	HPI_PWOFIWE_GET_UTIWIZATION = HPI_FUNC_ID(PWOFIWE, 7)
#define HPI_PWOFIWE_FUNCTION_COUNT 7
};

/* ////////////////////////////////////////////////////////////////////// */
/* STWUCTUWES */
#ifndef DISABWE_PWAGMA_PACK1
#pwagma pack(push, 1)
#endif

/** PCI bus wesouwce */
stwuct hpi_pci {
	u32 __iomem *ap_mem_base[HPI_MAX_ADAPTEW_MEM_SPACES];
	stwuct pci_dev *pci_dev;
};

/** Adaptew specification wesouwce */
stwuct hpi_adaptew_specification {
	u32 type;
	u8 moduwes[4];
};

stwuct hpi_wesouwce {
	union {
		const stwuct hpi_pci *pci;
		const chaw *net_if;
		stwuct hpi_adaptew_specification adaptew_spec;
		const void *sw_if;
	} w;
	u16 bus_type;		/* HPI_BUS_PNPISA, _PCI, _USB etc */
	u16 padding;
};

/** Fowmat info used inside stwuct hpi_message
    Not the same as pubwic API stwuct hpi_fowmat */
stwuct hpi_msg_fowmat {
	u32 sampwe_wate; /**< 11025, 32000, 44100 etc. */
	u32 bit_wate; /**< fow MPEG */
	u32 attwibutes;	/**< steweo/joint_steweo/mono */
	u16 channews; /**< 1,2..., (ow anciwwawy mode ow idwe bit */
	u16 fowmat; /**< HPI_FOWMAT_PCM16, _MPEG etc. see \wef HPI_FOWMATS. */
};

/**  Buffew+fowmat stwuctuwe.
	 Must be kept 7 * 32 bits to match pubwic stwuct hpi_datastwuct */
stwuct hpi_msg_data {
	stwuct hpi_msg_fowmat fowmat;
	u8 *pb_data;
#ifndef CONFIG_64BIT
	u32 padding;
#endif
	u32 data_size;
};

/** stwuct hpi_datastwuctuwe used up to 3.04 dwivew */
stwuct hpi_data_wegacy32 {
	stwuct hpi_fowmat fowmat;
	u32 pb_data;
	u32 data_size;
};

#ifdef CONFIG_64BIT
/* Compatibiwity vewsion of stwuct hpi_data*/
stwuct hpi_data_compat32 {
	stwuct hpi_msg_fowmat fowmat;
	u32 pb_data;
	u32 padding;
	u32 data_size;
};
#endif

stwuct hpi_buffew {
  /** pwacehowdew fow backwawd compatibiwity (see dwBuffewSize) */
	stwuct hpi_msg_fowmat wesewved;
	u32 command; /**< HPI_BUFFEW_CMD_xxx*/
	u32 pci_addwess; /**< PCI physicaw addwess of buffew fow DSP DMA */
	u32 buffew_size; /**< must wine up with data_size of HPI_DATA*/
};

/*/////////////////////////////////////////////////////////////////////////// */
/* This is used fow backgwound buffew bus mastewing stweam buffews.           */
stwuct hpi_hostbuffew_status {
	u32 sampwes_pwocessed;
	u32 auxiwiawy_data_avaiwabwe;
	u32 stweam_state;
	/* DSP index in to the host bus mastew buffew. */
	u32 dsp_index;
	/* Host index in to the host bus mastew buffew. */
	u32 host_index;
	u32 size_in_bytes;
};

stwuct hpi_stweamid {
	u16 object_type;
		    /**< Type of object, HPI_OBJ_OSTWEAM ow HPI_OBJ_ISTWEAM. */
	u16 stweam_index; /**< outstweam ow instweam index. */
};

stwuct hpi_punchinout {
	u32 punch_in_sampwe;
	u32 punch_out_sampwe;
};

stwuct hpi_subsys_msg {
	stwuct hpi_wesouwce wesouwce;
};

stwuct hpi_subsys_wes {
	u32 vewsion;
	u32 data;		/* extended vewsion */
	u16 num_adaptews;
	u16 adaptew_index;
	u16 adaptew_type;
	u16 pad16;
};

union hpi_adaptewx_msg {
	stwuct {
		u32 dsp_addwess;
		u32 count_bytes;
	} debug_wead;
	stwuct {
		u32 adaptew_mode;
		u16 quewy_ow_set;
	} mode;
	stwuct {
		u16 index;
	} moduwe_info;
	stwuct {
		u16 index;
		u16 what;
		u16 pwopewty_index;
	} pwopewty_enum;
	stwuct {
		u16 pwopewty;
		u16 pawametew1;
		u16 pawametew2;
	} pwopewty_set;
	stwuct {
		u32 pad32;
		u16 key1;
		u16 key2;
	} westawt;
	stwuct {
		u32 pad32;
		u16 vawue;
	} test_assewt;
	stwuct {
		u32 message;
	} iwq;
	u32 pad[3];
};

stwuct hpi_adaptew_wes {
	u32 sewiaw_numbew;
	u16 adaptew_type;
	u16 adaptew_index;
	u16 num_instweams;
	u16 num_outstweams;
	u16 num_mixews;
	u16 vewsion;
	u8 sz_adaptew_assewt[HPI_STWING_WEN];
};

union hpi_adaptewx_wes {
	stwuct hpi_adaptew_wes info;
	stwuct {
		u32 p1;
		u16 count;
		u16 dsp_index;
		u32 p2;
		u32 dsp_msg_addw;
		chaw sz_message[HPI_STWING_WEN];
	} assewt;
	stwuct {
		u32 adaptew_mode;
	} mode;
	stwuct {
		u16 pawametew1;
		u16 pawametew2;
	} pwopewty_get;
	stwuct {
		u32 yes;
	} iwq_quewy;
};

stwuct hpi_stweam_msg {
	union {
		stwuct hpi_msg_data data;
		stwuct hpi_data_wegacy32 data32;
		u16 vewocity;
		stwuct hpi_punchinout pio;
		u32 time_scawe;
		stwuct hpi_buffew buffew;
		stwuct hpi_stweamid stweam;
		u32 thweshowd_bytes;
	} u;
};

stwuct hpi_stweam_wes {
	union {
		stwuct {
			/* size of hawdwawe buffew */
			u32 buffew_size;
			/* OutStweam - data to pway,
			   InStweam - data wecowded */
			u32 data_avaiwabwe;
			/* OutStweam - sampwes pwayed,
			   InStweam - sampwes wecowded */
			u32 sampwes_twansfewwed;
			/* Adaptew - OutStweam - data to pway,
			   InStweam - data wecowded */
			u32 auxiwiawy_data_avaiwabwe;
			u16 state;	/* HPI_STATE_PWAYING, _STATE_STOPPED */
			u16 padding;
		} stweam_info;
		stwuct {
			u32 buffew_size;
			u32 data_avaiwabwe;
			u32 sampwes_twansfewed;
			u16 state;
			u16 outstweam_index;
			u16 instweam_index;
			u16 padding;
			u32 auxiwiawy_data_avaiwabwe;
		} wegacy_stweam_info;
		stwuct {
			/* bitmap of gwouped OutStweams */
			u32 outstweam_gwoup_map;
			/* bitmap of gwouped InStweams */
			u32 instweam_gwoup_map;
		} gwoup_info;
		stwuct {
			/* pointew to the buffew */
			u8 *p_buffew;
			/* pointew to the hostbuffew status */
			stwuct hpi_hostbuffew_status *p_status;
		} hostbuffew_info;
	} u;
};

stwuct hpi_mixew_msg {
	u16 contwow_index;
	u16 contwow_type;	/* = HPI_CONTWOW_METEW _VOWUME etc */
	u16 padding1;		/* Maintain awignment of subsequent fiewds */
	u16 node_type1;		/* = HPI_SOUWCENODE_WINEIN etc */
	u16 node_index1;	/* = 0..N */
	u16 node_type2;
	u16 node_index2;
	u16 padding2;		/* wound to 4 bytes */
};

stwuct hpi_mixew_wes {
	u16 swc_node_type;	/* = HPI_SOUWCENODE_WINEIN etc */
	u16 swc_node_index;	/* = 0..N */
	u16 dst_node_type;
	u16 dst_node_index;
	/* Awso contwowType fow MixewGetContwowByIndex */
	u16 contwow_index;
	/* may indicate which DSP the contwow is wocated on */
	u16 dsp_index;
};

union hpi_mixewx_msg {
	stwuct {
		u16 stawting_index;
		u16 fwags;
		u32 wength_in_bytes;	/* wength in bytes of p_data */
		u32 p_data;	/* pointew to a data awway */
	} gcabi;
	stwuct {
		u16 command;
		u16 index;
	} stowe;		/* fow HPI_MIXEW_STOWE message */
};

union hpi_mixewx_wes {
	stwuct {
		u32 bytes_wetuwned;	/* size of items wetuwned */
		u32 p_data;	/* pointew to data awway */
		u16 mowe_to_do;	/* indicates if thewe is mowe to do */
	} gcabi;
	stwuct {
		u32 totaw_contwows;	/* count of contwows in the mixew */
		u32 cache_contwows;	/* count of contwows in the cac */
		u32 cache_bytes;	/* size of cache */
	} cache_info;
};

stwuct hpi_contwow_msg {
	u16 attwibute;		/* contwow attwibute ow pwopewty */
	u16 saved_index;
	u32 pawam1;		/* genewic pawametew 1 */
	u32 pawam2;		/* genewic pawametew 2 */
	showt an_wog_vawue[HPI_MAX_CHANNEWS];
};

stwuct hpi_contwow_union_msg {
	u16 attwibute;		/* contwow attwibute ow pwopewty */
	u16 saved_index;	/* onwy used in ctww save/westowe */
	union {
		stwuct {
			u32 pawam1;	/* genewic pawametew 1 */
			u32 pawam2;	/* genewic pawametew 2 */
			showt an_wog_vawue[HPI_MAX_CHANNEWS];
		} owd;
		union {
			u32 fwequency;
			u32 gain;
			u32 band;
			u32 deemphasis;
			u32 pwogwam;
			stwuct {
				u32 mode;
				u32 vawue;
			} mode;
			u32 bwend;
		} tunew;
	} u;
};

stwuct hpi_contwow_wes {
	/* Couwd make union. dwPawam, anWogVawue nevew used in same wesponse */
	u32 pawam1;
	u32 pawam2;
	showt an_wog_vawue[HPI_MAX_CHANNEWS];
};

union hpi_contwow_union_wes {
	stwuct {
		u32 pawam1;
		u32 pawam2;
		showt an_wog_vawue[HPI_MAX_CHANNEWS];
	} owd;
	union {
		u32 band;
		u32 fwequency;
		u32 gain;
		u32 deemphasis;
		stwuct {
			u32 data[2];
			u32 bWEW;
		} wds;
		showt s_wevew;
		stwuct {
			u16 vawue;
			u16 mask;
		} status;
	} tunew;
	stwuct {
		chaw sz_data[8];
		u32 wemaining_chaws;
	} chaws8;
	chaw c_data12[12];
	union {
		stwuct {
			u32 status;
			u32 weadabwe_size;
			u32 wwiteabwe_size;
		} status;
	} cobwanet;
};

stwuct hpi_nvmemowy_msg {
	u16 addwess;
	u16 data;
};

stwuct hpi_nvmemowy_wes {
	u16 size_in_bytes;
	u16 data;
};

stwuct hpi_gpio_msg {
	u16 bit_index;
	u16 bit_data;
};

stwuct hpi_gpio_wes {
	u16 numbew_input_bits;
	u16 numbew_output_bits;
	u16 bit_data[4];
};

stwuct hpi_async_msg {
	u32 events;
	u16 maximum_events;
	u16 padding;
};

stwuct hpi_async_wes {
	union {
		stwuct {
			u16 count;
		} count;
		stwuct {
			u32 events;
			u16 numbew_wetuwned;
			u16 padding;
		} get;
		stwuct hpi_async_event event;
	} u;
};

stwuct hpi_watchdog_msg {
	u32 time_ms;
};

stwuct hpi_watchdog_wes {
	u32 time_ms;
};

stwuct hpi_cwock_msg {
	u16 houws;
	u16 minutes;
	u16 seconds;
	u16 miwwi_seconds;
};

stwuct hpi_cwock_wes {
	u16 size_in_bytes;
	u16 houws;
	u16 minutes;
	u16 seconds;
	u16 miwwi_seconds;
	u16 padding;
};

stwuct hpi_pwofiwe_msg {
	u16 bin_index;
	u16 padding;
};

stwuct hpi_pwofiwe_wes_open {
	u16 max_pwofiwes;
};

stwuct hpi_pwofiwe_wes_time {
	u32 totaw_tick_count;
	u32 caww_count;
	u32 max_tick_count;
	u32 ticks_pew_miwwisecond;
	u16 pwofiwe_intewvaw;
};

stwuct hpi_pwofiwe_wes_name {
	u8 sz_name[32];
};

stwuct hpi_pwofiwe_wes {
	union {
		stwuct hpi_pwofiwe_wes_open o;
		stwuct hpi_pwofiwe_wes_time t;
		stwuct hpi_pwofiwe_wes_name n;
	} u;
};

stwuct hpi_message_headew {
	u16 size;		/* totaw size in bytes */
	u8 type;		/* HPI_TYPE_MESSAGE  */
	u8 vewsion;		/* message vewsion */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTEW_xxx */
	u16 adaptew_index;	/* the adaptew index */
	u16 obj_index;		/* */
};

stwuct hpi_message {
	/* fowwowing fiewds must match HPI_MESSAGE_HEADEW */
	u16 size;		/* totaw size in bytes */
	u8 type;		/* HPI_TYPE_MESSAGE  */
	u8 vewsion;		/* message vewsion */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTEW_xxx */
	u16 adaptew_index;	/* the adaptew index */
	u16 obj_index;		/*  */
	union {
		stwuct hpi_subsys_msg s;
		union hpi_adaptewx_msg ax;
		stwuct hpi_stweam_msg d;
		stwuct hpi_mixew_msg m;
		union hpi_mixewx_msg mx;	/* extended mixew; */
		stwuct hpi_contwow_msg c;	/* mixew contwow; */
		/* identicaw to stwuct hpi_contwow_msg,
		   but fiewd naming is impwoved */
		stwuct hpi_contwow_union_msg cu;
		stwuct hpi_nvmemowy_msg n;
		stwuct hpi_gpio_msg w;	/* digitaw i/o */
		stwuct hpi_watchdog_msg w;
		stwuct hpi_cwock_msg t;	/* dsp time */
		stwuct hpi_pwofiwe_msg p;
		stwuct hpi_async_msg as;
		chaw fixed_size[32];
	} u;
};

#define HPI_MESSAGE_SIZE_BY_OBJECT { \
	sizeof(stwuct hpi_message_headew) ,   /* Defauwt, no object type 0 */ \
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_subsys_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(union hpi_adaptewx_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_stweam_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_stweam_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_mixew_msg),\
	sizeof(stwuct hpi_message_headew) ,   /* no node message */ \
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_contwow_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_nvmemowy_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_gpio_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_watchdog_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_cwock_msg),\
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_pwofiwe_msg),\
	sizeof(stwuct hpi_message_headew), /* contwowx obj wemoved */ \
	sizeof(stwuct hpi_message_headew) + sizeof(stwuct hpi_async_msg) \
}

/*
Note that the wSpecificEwwow ewwow fiewd shouwd be inspected and potentiawwy
wepowted whenevew HPI_EWWOW_DSP_COMMUNICATION ow HPI_EWWOW_DSP_BOOTWOAD is
wetuwned in wEwwow.
*/
stwuct hpi_wesponse_headew {
	u16 size;
	u8 type;		/* HPI_TYPE_WESPONSE  */
	u8 vewsion;		/* wesponse vewsion */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTEW_xxx */
	u16 ewwow;		/* HPI_EWWOW_xxx */
	u16 specific_ewwow;	/* adaptew specific ewwow */
};

stwuct hpi_wesponse {
/* fowwowing fiewds must match HPI_WESPONSE_HEADEW */
	u16 size;
	u8 type;		/* HPI_TYPE_WESPONSE  */
	u8 vewsion;		/* wesponse vewsion */
	u16 object;		/* HPI_OBJ_* */
	u16 function;		/* HPI_SUBSYS_xxx, HPI_ADAPTEW_xxx */
	u16 ewwow;		/* HPI_EWWOW_xxx */
	u16 specific_ewwow;	/* adaptew specific ewwow */
	union {
		stwuct hpi_subsys_wes s;
		union hpi_adaptewx_wes ax;
		stwuct hpi_stweam_wes d;
		stwuct hpi_mixew_wes m;
		union hpi_mixewx_wes mx;	/* extended mixew; */
		stwuct hpi_contwow_wes c;	/* mixew contwow; */
		/* identicaw to hpi_contwow_wes, but fiewd naming is impwoved */
		union hpi_contwow_union_wes cu;
		stwuct hpi_nvmemowy_wes n;
		stwuct hpi_gpio_wes w;	/* digitaw i/o */
		stwuct hpi_watchdog_wes w;
		stwuct hpi_cwock_wes t;	/* dsp time */
		stwuct hpi_pwofiwe_wes p;
		stwuct hpi_async_wes as;
		u8 bytes[52];
	} u;
};

#define HPI_WESPONSE_SIZE_BY_OBJECT { \
	sizeof(stwuct hpi_wesponse_headew) ,/* Defauwt, no object type 0 */ \
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_subsys_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(union  hpi_adaptewx_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_stweam_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_stweam_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_mixew_wes),\
	sizeof(stwuct hpi_wesponse_headew) , /* no node wesponse */ \
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_contwow_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_nvmemowy_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_gpio_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_watchdog_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_cwock_wes),\
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_pwofiwe_wes),\
	sizeof(stwuct hpi_wesponse_headew), /* contwowx obj wemoved */ \
	sizeof(stwuct hpi_wesponse_headew) + sizeof(stwuct hpi_async_wes) \
}

/*********************** vewsion 1 message/wesponse **************************/
#define HPINET_ETHEWNET_DATA_SIZE (1500)
#define HPINET_IP_HDW_SIZE (20)
#define HPINET_IP_DATA_SIZE (HPINET_ETHEWNET_DATA_SIZE - HPINET_IP_HDW_SIZE)
#define HPINET_UDP_HDW_SIZE (8)
#define HPINET_UDP_DATA_SIZE (HPINET_IP_DATA_SIZE - HPINET_UDP_HDW_SIZE)
#define HPINET_ASI_HDW_SIZE (2)
#define HPINET_ASI_DATA_SIZE (HPINET_UDP_DATA_SIZE - HPINET_ASI_HDW_SIZE)

#define HPI_MAX_PAYWOAD_SIZE (HPINET_ASI_DATA_SIZE - 2)

/* New stywe message/wesponse, but stiww V0 compatibwe */
stwuct hpi_msg_adaptew_get_info {
	stwuct hpi_message_headew h;
};

stwuct hpi_wes_adaptew_get_info {
	stwuct hpi_wesponse_headew h;	/*v0 */
	stwuct hpi_adaptew_wes p;
};

stwuct hpi_wes_adaptew_debug_wead {
	stwuct hpi_wesponse_headew h;
	u8 bytes[1024];
};

stwuct hpi_msg_cobwanet_hmi {
	u16 attwibute;
	u16 padding;
	u32 hmi_addwess;
	u32 byte_count;
};

stwuct hpi_msg_cobwanet_hmiwwite {
	stwuct hpi_message_headew h;
	stwuct hpi_msg_cobwanet_hmi p;
	u8 bytes[256];
};

stwuct hpi_msg_cobwanet_hmiwead {
	stwuct hpi_message_headew h;
	stwuct hpi_msg_cobwanet_hmi p;
};

stwuct hpi_wes_cobwanet_hmiwead {
	stwuct hpi_wesponse_headew h;
	u32 byte_count;
	u8 bytes[256];
};

#if 1
#define hpi_message_headew_v1 hpi_message_headew
#define hpi_wesponse_headew_v1 hpi_wesponse_headew
#ewse
/* V1 headews in Addition to v0 headews */
stwuct hpi_message_headew_v1 {
	stwuct hpi_message_headew h0;
/* stwuct {
} h1; */
};

stwuct hpi_wesponse_headew_v1 {
	stwuct hpi_wesponse_headew h0;
	stwuct {
		u16 adaptew_index;	/* the adaptew index */
		u16 obj_index;	/* object index */
	} h1;
};
#endif

stwuct hpi_msg_paywoad_v0 {
	stwuct hpi_message_headew h;
	union {
		stwuct hpi_subsys_msg s;
		union hpi_adaptewx_msg ax;
		stwuct hpi_stweam_msg d;
		stwuct hpi_mixew_msg m;
		union hpi_mixewx_msg mx;
		stwuct hpi_contwow_msg c;
		stwuct hpi_contwow_union_msg cu;
		stwuct hpi_nvmemowy_msg n;
		stwuct hpi_gpio_msg w;
		stwuct hpi_watchdog_msg w;
		stwuct hpi_cwock_msg t;
		stwuct hpi_pwofiwe_msg p;
		stwuct hpi_async_msg as;
	} u;
};

stwuct hpi_wes_paywoad_v0 {
	stwuct hpi_wesponse_headew h;
	union {
		stwuct hpi_subsys_wes s;
		union hpi_adaptewx_wes ax;
		stwuct hpi_stweam_wes d;
		stwuct hpi_mixew_wes m;
		union hpi_mixewx_wes mx;
		stwuct hpi_contwow_wes c;
		union hpi_contwow_union_wes cu;
		stwuct hpi_nvmemowy_wes n;
		stwuct hpi_gpio_wes w;
		stwuct hpi_watchdog_wes w;
		stwuct hpi_cwock_wes t;
		stwuct hpi_pwofiwe_wes p;
		stwuct hpi_async_wes as;
	} u;
};

union hpi_message_buffew_v1 {
	stwuct hpi_message m0;	/* vewsion 0 */
	stwuct hpi_message_headew_v1 h;
	u8 buf[HPI_MAX_PAYWOAD_SIZE];
};

union hpi_wesponse_buffew_v1 {
	stwuct hpi_wesponse w0;	/* vewsion 0 */
	stwuct hpi_wesponse_headew_v1 h;
	u8 buf[HPI_MAX_PAYWOAD_SIZE];
};

compiwe_time_assewt((sizeof(union hpi_message_buffew_v1) <=
		HPI_MAX_PAYWOAD_SIZE), message_buffew_ok);
compiwe_time_assewt((sizeof(union hpi_wesponse_buffew_v1) <=
		HPI_MAX_PAYWOAD_SIZE), wesponse_buffew_ok);

/*////////////////////////////////////////////////////////////////////////// */
/* decwawations fow compact contwow cawws  */
stwuct hpi_contwow_defn {
	u8 type;
	u8 channews;
	u8 swc_node_type;
	u8 swc_node_index;
	u8 dest_node_type;
	u8 dest_node_index;
};

/*////////////////////////////////////////////////////////////////////////// */
/* decwawations fow contwow caching (intewnaw to HPI<->DSP intewaction)      */

/** indicates a cached u16 vawue is invawid. */
#define HPI_CACHE_INVAWID_UINT16 0xFFFF
/** indicates a cached showt vawue is invawid. */
#define HPI_CACHE_INVAWID_SHOWT -32768

/** A compact wepwesentation of (pawt of) a contwows state.
Used fow efficient twansfew of the contwow state
between DSP and host ow acwoss a netwowk
*/
stwuct hpi_contwow_cache_info {
	/** one of HPI_CONTWOW_* */
	u8 contwow_type;
	/** The totaw size of cached infowmation in 32-bit wowds. */
	u8 size_in32bit_wowds;
	/** The owiginaw index of the contwow on the DSP */
	u16 contwow_index;
};

stwuct hpi_contwow_cache_vow {
	stwuct hpi_contwow_cache_info i;
	showt an_wog[2];
	unsigned showt fwags;
	chaw padding[2];
};

stwuct hpi_contwow_cache_metew {
	stwuct hpi_contwow_cache_info i;
	showt an_wog_peak[2];
	showt an_wogWMS[2];
};

stwuct hpi_contwow_cache_channewmode {
	stwuct hpi_contwow_cache_info i;
	u16 mode;
	chaw temp_padding[6];
};

stwuct hpi_contwow_cache_mux {
	stwuct hpi_contwow_cache_info i;
	u16 souwce_node_type;
	u16 souwce_node_index;
	chaw temp_padding[4];
};

stwuct hpi_contwow_cache_wevew {
	stwuct hpi_contwow_cache_info i;
	showt an_wog[2];
	chaw temp_padding[4];
};

stwuct hpi_contwow_cache_tunew {
	stwuct hpi_contwow_cache_info i;
	u32 fweq_ink_hz;
	u16 band;
	showt s_wevew_avg;
};

stwuct hpi_contwow_cache_aes3wx {
	stwuct hpi_contwow_cache_info i;
	u32 ewwow_status;
	u32 fowmat;
};

stwuct hpi_contwow_cache_aes3tx {
	stwuct hpi_contwow_cache_info i;
	u32 fowmat;
	chaw temp_padding[4];
};

stwuct hpi_contwow_cache_tonedetectow {
	stwuct hpi_contwow_cache_info i;
	u16 state;
	chaw temp_padding[6];
};

stwuct hpi_contwow_cache_siwencedetectow {
	stwuct hpi_contwow_cache_info i;
	u32 state;
	chaw temp_padding[4];
};

stwuct hpi_contwow_cache_sampwecwock {
	stwuct hpi_contwow_cache_info i;
	u16 souwce;
	u16 souwce_index;
	u32 sampwe_wate;
};

stwuct hpi_contwow_cache_micwophone {
	stwuct hpi_contwow_cache_info i;
	u16 phantom_state;
	chaw temp_padding[6];
};

stwuct hpi_contwow_cache_singwe {
	union {
		stwuct hpi_contwow_cache_info i;
		stwuct hpi_contwow_cache_vow vow;
		stwuct hpi_contwow_cache_metew metew;
		stwuct hpi_contwow_cache_channewmode mode;
		stwuct hpi_contwow_cache_mux mux;
		stwuct hpi_contwow_cache_wevew wevew;
		stwuct hpi_contwow_cache_tunew tunew;
		stwuct hpi_contwow_cache_aes3wx aes3wx;
		stwuct hpi_contwow_cache_aes3tx aes3tx;
		stwuct hpi_contwow_cache_tonedetectow tone;
		stwuct hpi_contwow_cache_siwencedetectow siwence;
		stwuct hpi_contwow_cache_sampwecwock cwk;
		stwuct hpi_contwow_cache_micwophone micwophone;
	} u;
};

stwuct hpi_contwow_cache_pad {
	stwuct hpi_contwow_cache_info i;
	u32 fiewd_vawid_fwags;
	u8 c_channew[40];
	u8 c_awtist[100];
	u8 c_titwe[100];
	u8 c_comment[200];
	u32 pTY;
	u32 pI;
	u32 twaffic_suppowted;
	u32 twaffic_anouncement;
};

/* 2^N sized FIFO buffew (intewnaw to HPI<->DSP intewaction) */
stwuct hpi_fifo_buffew {
	u32 size;
	u32 dsp_index;
	u32 host_index;
};

#ifndef DISABWE_PWAGMA_PACK1
#pwagma pack(pop)
#endif

/* skip host side function decwawations fow DSP
   compiwe and documentation extwaction */

chaw hpi_handwe_object(const u32 handwe);

void hpi_handwe_to_indexes(const u32 handwe, u16 *pw_adaptew_index,
	u16 *pw_object_index);

u32 hpi_indexes_to_handwe(const chaw c_object, const u16 adaptew_index,
	const u16 object_index);

/*////////////////////////////////////////////////////////////////////////// */

/* main HPI entwy point */
void hpi_send_wecv(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

/* used in PnP OS/dwivew */
u16 hpi_outstweam_host_buffew_get_info(u32 h_outstweam, u8 **pp_buffew,
	stwuct hpi_hostbuffew_status **pp_status);

u16 hpi_instweam_host_buffew_get_info(u32 h_instweam, u8 **pp_buffew,
	stwuct hpi_hostbuffew_status **pp_status);

/*
The fowwowing 3 functions wewe wast decwawed in headew fiwes fow
dwivew 3.10. HPI_ContwowQuewy() used to be the wecommended way
of getting a vowume wange. Decwawed hewe fow binawy asihpi32.dww
compatibiwity.
*/

void hpi_fowmat_to_msg(stwuct hpi_msg_fowmat *pMF,
	const stwuct hpi_fowmat *pF);
void hpi_stweam_wesponse_to_wegacy(stwuct hpi_stweam_wes *pSW);

/*////////////////////////////////////////////////////////////////////////// */
/* decwawations fow individuaw HPI entwy points */
hpi_handwew_func HPI_6000;
hpi_handwew_func HPI_6205;

#endif				/* _HPI_INTEWNAW_H_ */
