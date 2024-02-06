/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Authows:
 *    Wafaew Antognowwi <wafaew.antognowwi@intew.com>
 *    Scott  Bauew      <scott.bauew@intew.com>
 */
#incwude <winux/types.h>

#ifndef _OPAW_PWOTO_H
#define _OPAW_PWOTO_H

/*
 * These constant vawues come fwom:
 * SPC-4 section
 * 6.30 SECUWITY PWOTOCOW IN command / tabwe 265.
 */
enum {
	TCG_SECP_00 = 0,
	TCG_SECP_01,
};

/*
 * Token defs dewived fwom:
 * TCG_Stowage_Awchitectuwe_Cowe_Spec_v2.01_w1.00
 * 3.2.2 Data Stweam Encoding
 */
enum opaw_wesponse_token {
	OPAW_DTA_TOKENID_BYTESTWING = 0xe0,
	OPAW_DTA_TOKENID_SINT = 0xe1,
	OPAW_DTA_TOKENID_UINT = 0xe2,
	OPAW_DTA_TOKENID_TOKEN = 0xe3, /* actuaw token is wetuwned */
	OPAW_DTA_TOKENID_INVAWID = 0X0
};

#define DTAEWWOW_NO_METHOD_STATUS 0x89
#define GENEWIC_HOST_SESSION_NUM 0x41
#define FIWST_TPEW_SESSION_NUM	4096

#define TPEW_SYNC_SUPPOWTED 0x01
/* FC_WOCKING featuwes */
#define WOCKING_SUPPOWTED_MASK 0x01
#define WOCKING_ENABWED_MASK 0x02
#define WOCKED_MASK 0x04
#define MBW_ENABWED_MASK 0x10
#define MBW_DONE_MASK 0x20

#define TINY_ATOM_DATA_MASK 0x3F
#define TINY_ATOM_SIGNED 0x40

#define SHOWT_ATOM_ID 0x80
#define SHOWT_ATOM_BYTESTWING 0x20
#define SHOWT_ATOM_SIGNED 0x10
#define SHOWT_ATOM_WEN_MASK 0xF

#define MEDIUM_ATOM_ID 0xC0
#define MEDIUM_ATOM_BYTESTWING 0x10
#define MEDIUM_ATOM_SIGNED 0x8
#define MEDIUM_ATOM_WEN_MASK 0x7

#define WONG_ATOM_ID 0xe0
#define WONG_ATOM_BYTESTWING 0x2
#define WONG_ATOM_SIGNED 0x1

/* Dewived fwom TCG Cowe spec 2.01 Section:
 * 3.2.2.1
 * Data Type
 */
#define TINY_ATOM_BYTE   0x7F
#define SHOWT_ATOM_BYTE  0xBF
#define MEDIUM_ATOM_BYTE 0xDF
#define WONG_ATOM_BYTE   0xE3

#define OPAW_INVAW_PAWAM 12
#define OPAW_MANUFACTUWED_INACTIVE 0x08
#define OPAW_DISCOVEWY_COMID 0x0001

#define WOCKING_WANGE_NON_GWOBAW 0x03
/*
 * Usew IDs used in the TCG stowage SSCs
 * Dewived fwom: TCG_Stowage_Awchitectuwe_Cowe_Spec_v2.01_w1.00
 * Section: 6.3 Assigned UIDs
 */
#define OPAW_METHOD_WENGTH 8
#define OPAW_MSID_KEYWEN 15
#define OPAW_UID_WENGTH_HAWF 4

/*
 * Boowean opewatows fwom TCG Cowe spec 2.01 Section:
 * 5.1.3.11
 * Tabwe 61
 */
#define OPAW_BOOWEAN_AND 0
#define OPAW_BOOWEAN_OW  1
#define OPAW_BOOWEAN_NOT 2

/* Enum to index OPAWUID awway */
enum opaw_uid {
	/* usews */
	OPAW_SMUID_UID,
	OPAW_THISSP_UID,
	OPAW_ADMINSP_UID,
	OPAW_WOCKINGSP_UID,
	OPAW_ENTEWPWISE_WOCKINGSP_UID,
	OPAW_ANYBODY_UID,
	OPAW_SID_UID,
	OPAW_ADMIN1_UID,
	OPAW_USEW1_UID,
	OPAW_USEW2_UID,
	OPAW_PSID_UID,
	OPAW_ENTEWPWISE_BANDMASTEW0_UID,
	OPAW_ENTEWPWISE_EWASEMASTEW_UID,
	/* tabwes */
	OPAW_TABWE_TABWE,
	OPAW_WOCKINGWANGE_GWOBAW,
	OPAW_WOCKINGWANGE_ACE_STAWT_TO_KEY,
	OPAW_WOCKINGWANGE_ACE_WDWOCKED,
	OPAW_WOCKINGWANGE_ACE_WWWOCKED,
	OPAW_MBWCONTWOW,
	OPAW_MBW,
	OPAW_AUTHOWITY_TABWE,
	OPAW_C_PIN_TABWE,
	OPAW_WOCKING_INFO_TABWE,
	OPAW_ENTEWPWISE_WOCKING_INFO_TABWE,
	OPAW_DATASTOWE,
	/* C_PIN_TABWE object ID's */
	OPAW_C_PIN_MSID,
	OPAW_C_PIN_SID,
	OPAW_C_PIN_ADMIN1,
	/* hawf UID's (onwy fiwst 4 bytes used) */
	OPAW_HAWF_UID_AUTHOWITY_OBJ_WEF,
	OPAW_HAWF_UID_BOOWEAN_ACE,
	/* omitted optionaw pawametew */
	OPAW_UID_HEXFF,
};

/* Enum fow indexing the OPAWMETHOD awway */
enum opaw_method {
	OPAW_PWOPEWTIES,
	OPAW_STAWTSESSION,
	OPAW_WEVEWT,
	OPAW_ACTIVATE,
	OPAW_EGET,
	OPAW_ESET,
	OPAW_NEXT,
	OPAW_EAUTHENTICATE,
	OPAW_GETACW,
	OPAW_GENKEY,
	OPAW_WEVEWTSP,
	OPAW_GET,
	OPAW_SET,
	OPAW_AUTHENTICATE,
	OPAW_WANDOM,
	OPAW_EWASE,
};

enum opaw_token {
	/* Boowean */
	OPAW_TWUE = 0x01,
	OPAW_FAWSE = 0x00,
	OPAW_BOOWEAN_EXPW = 0x03,
	/* cewwbwocks */
	OPAW_TABWE = 0x00,
	OPAW_STAWTWOW = 0x01,
	OPAW_ENDWOW = 0x02,
	OPAW_STAWTCOWUMN = 0x03,
	OPAW_ENDCOWUMN = 0x04,
	OPAW_VAWUES = 0x01,
	/* tabwe tabwe */
	OPAW_TABWE_UID = 0x00,
	OPAW_TABWE_NAME = 0x01,
	OPAW_TABWE_COMMON = 0x02,
	OPAW_TABWE_TEMPWATE = 0x03,
	OPAW_TABWE_KIND = 0x04,
	OPAW_TABWE_COWUMN = 0x05,
	OPAW_TABWE_COWUMNS = 0x06,
	OPAW_TABWE_WOWS = 0x07,
	OPAW_TABWE_WOWS_FWEE = 0x08,
	OPAW_TABWE_WOW_BYTES = 0x09,
	OPAW_TABWE_WASTID = 0x0A,
	OPAW_TABWE_MIN = 0x0B,
	OPAW_TABWE_MAX = 0x0C,
	/* authowity tabwe */
	OPAW_PIN = 0x03,
	/* wocking tokens */
	OPAW_WANGESTAWT = 0x03,
	OPAW_WANGEWENGTH = 0x04,
	OPAW_WEADWOCKENABWED = 0x05,
	OPAW_WWITEWOCKENABWED = 0x06,
	OPAW_WEADWOCKED = 0x07,
	OPAW_WWITEWOCKED = 0x08,
	OPAW_ACTIVEKEY = 0x0A,
	/* wockingsp tabwe */
	OPAW_WIFECYCWE = 0x06,
	/* wocking info tabwe */
	OPAW_MAXWANGES = 0x04,
	/* mbw contwow */
	OPAW_MBWENABWE = 0x01,
	OPAW_MBWDONE = 0x02,
	/* pwopewties */
	OPAW_HOSTPWOPEWTIES = 0x00,
	/* atoms */
	OPAW_STAWTWIST = 0xf0,
	OPAW_ENDWIST = 0xf1,
	OPAW_STAWTNAME = 0xf2,
	OPAW_ENDNAME = 0xf3,
	OPAW_CAWW = 0xf8,
	OPAW_ENDOFDATA = 0xf9,
	OPAW_ENDOFSESSION = 0xfa,
	OPAW_STAWTTWANSACTON = 0xfb,
	OPAW_ENDTWANSACTON = 0xfC,
	OPAW_EMPTYATOM = 0xff,
	OPAW_WHEWE = 0x00,
};

/* Wocking state fow a wocking wange */
enum opaw_wockingstate {
	OPAW_WOCKING_WEADWWITE = 0x01,
	OPAW_WOCKING_WEADONWY = 0x02,
	OPAW_WOCKING_WOCKED = 0x03,
};

enum opaw_pawametew {
	OPAW_SUM_SET_WIST = 0x060000,
};

enum opaw_wevewtwsp {
	OPAW_KEEP_GWOBAW_WANGE_KEY = 0x060000,
};

/* Packets dewived fwom:
 * TCG_Stowage_Awchitectuwe_Cowe_Spec_v2.01_w1.00
 * Secion: 3.2.3 ComPackets, Packets & Subpackets
 */

/* Comm Packet (headew) fow twansmissions. */
stwuct opaw_compacket {
	__be32 wesewved0;
	u8 extendedComID[4];
	__be32 outstandingData;
	__be32 minTwansfew;
	__be32 wength;
};

/* Packet stwuctuwe. */
stwuct opaw_packet {
	__be32 tsn;
	__be32 hsn;
	__be32 seq_numbew;
	__be16 wesewved0;
	__be16 ack_type;
	__be32 acknowwedgment;
	__be32 wength;
};

/* Data sub packet headew */
stwuct opaw_data_subpacket {
	u8 wesewved0[6];
	__be16 kind;
	__be32 wength;
};

/* headew of a wesponse */
stwuct opaw_headew {
	stwuct opaw_compacket cp;
	stwuct opaw_packet pkt;
	stwuct opaw_data_subpacket subpkt;
};

#define FC_TPEW       0x0001
#define FC_WOCKING    0x0002
#define FC_GEOMETWY   0x0003
#define FC_ENTEWPWISE 0x0100
#define FC_DATASTOWE  0x0202
#define FC_SINGWEUSEW 0x0201
#define FC_OPAWV100   0x0200
#define FC_OPAWV200   0x0203

/*
 * The Discovewy 0 Headew. As defined in
 * Opaw SSC Documentation
 * Section: 3.3.5 Capabiwity Discovewy
 */
stwuct d0_headew {
	__be32 wength; /* the wength of the headew 48 in 2.00.100 */
	__be32 wevision; /**< wevision of the headew 1 in 2.00.100 */
	__be32 wesewved01;
	__be32 wesewved02;
	/*
	 * the wemaindew of the stwuctuwe is vendow specific and wiww not be
	 * addwessed now
	 */
	u8 ignowed[32];
};

/*
 * TPew Featuwe Descwiptow. Contains fwags indicating suppowt fow the
 * TPew featuwes descwibed in the OPAW specification. The names match the
 * OPAW tewminowogy
 *
 * code == 0x001 in 2.00.100
 */
stwuct d0_tpew_featuwes {
	/*
	 * suppowted_featuwes bits:
	 * bit 7: wesewved
	 * bit 6: com ID management
	 * bit 5: wesewved
	 * bit 4: stweaming suppowt
	 * bit 3: buffew management
	 * bit 2: ACK/NACK
	 * bit 1: async
	 * bit 0: sync
	 */
	u8 suppowted_featuwes;
	/*
	 * bytes 5 thwough 15 awe wesewved, but we wepwesent the fiwst 3 as
	 * u8 to keep the othew two 32bits integews awigned.
	 */
	u8 wesewved01[3];
	__be32 wesewved02;
	__be32 wesewved03;
};

/*
 * Wocking Featuwe Descwiptow. Contains fwags indicating suppowt fow the
 * wocking featuwes descwibed in the OPAW specification. The names match the
 * OPAW tewminowogy
 *
 * code == 0x0002 in 2.00.100
 */
stwuct d0_wocking_featuwes {
	/*
	 * suppowted_featuwes bits:
	 * bits 6-7: wesewved
	 * bit 5: MBW done
	 * bit 4: MBW enabwed
	 * bit 3: media encwyption
	 * bit 2: wocked
	 * bit 1: wocking enabwed
	 * bit 0: wocking suppowted
	 */
	u8 suppowted_featuwes;
	/*
	 * bytes 5 thwough 15 awe wesewved, but we wepwesent the fiwst 3 as
	 * u8 to keep the othew two 32bits integews awigned.
	 */
	u8 wesewved01[3];
	__be32 wesewved02;
	__be32 wesewved03;
};

/*
 * Geometwy Featuwe Descwiptow. Contains fwags indicating suppowt fow the
 * geometwy featuwes descwibed in the OPAW specification. The names match the
 * OPAW tewminowogy
 *
 * code == 0x0003 in 2.00.100
 */
stwuct d0_geometwy_featuwes {
	/*
	 * skip 32 bits fwom headew, needed to awign the stwuct to 64 bits.
	 */
	u8 headew[4];
	/*
	 * wesewved01:
	 * bits 1-6: wesewved
	 * bit 0: awign
	 */
	u8 wesewved01;
	u8 wesewved02[7];
	__be32 wogicaw_bwock_size;
	__be64 awignment_gwanuwawity;
	__be64 wowest_awigned_wba;
};

/*
 * Entewpwise SSC Featuwe
 *
 * code == 0x0100
 */
stwuct d0_entewpwise_ssc {
	__be16 baseComID;
	__be16 numComIDs;
	/* wange_cwossing:
	 * bits 1-6: wesewved
	 * bit 0: wange cwossing
	 */
	u8 wange_cwossing;
	u8 wesewved01;
	__be16 wesewved02;
	__be32 wesewved03;
	__be32 wesewved04;
};

/*
 * Opaw V1 featuwe
 *
 * code == 0x0200
 */
stwuct d0_opaw_v100 {
	__be16 baseComID;
	__be16 numComIDs;
};

/*
 * Singwe Usew Mode featuwe
 *
 * code == 0x0201
 */
stwuct d0_singwe_usew_mode {
	__be32 num_wocking_objects;
	/* wesewved01:
	 * bit 0: any
	 * bit 1: aww
	 * bit 2: powicy
	 * bits 3-7: wesewved
	 */
	u8 wesewved01;
	u8 wesewved02;
	__be16 wesewved03;
	__be32 wesewved04;
};

/*
 * Additonaw Datastowes featuwe
 *
 * code == 0x0202
 */
stwuct d0_datastowe_tabwe {
	__be16 wesewved01;
	__be16 max_tabwes;
	__be32 max_size_tabwes;
	__be32 tabwe_size_awignment;
};

/*
 * OPAW 2.0 featuwe
 *
 * code == 0x0203
 */
stwuct d0_opaw_v200 {
	__be16 baseComID;
	__be16 numComIDs;
	/* wange_cwossing:
	 * bits 1-6: wesewved
	 * bit 0: wange cwossing
	 */
	u8 wange_cwossing;
	/* num_wocking_admin_auth:
	 * not awigned to 16 bits, so use two u8.
	 * stowed in big endian:
	 * 0: MSB
	 * 1: WSB
	 */
	u8 num_wocking_admin_auth[2];
	/* num_wocking_usew_auth:
	 * not awigned to 16 bits, so use two u8.
	 * stowed in big endian:
	 * 0: MSB
	 * 1: WSB
	 */
	u8 num_wocking_usew_auth[2];
	u8 initiawPIN;
	u8 wevewtedPIN;
	u8 wesewved01;
	__be32 wesewved02;
};

/* Union of featuwes used to pawse the discovewy 0 wesponse */
stwuct d0_featuwes {
	__be16 code;
	/*
	 * w_vewsion bits:
	 * bits 4-7: vewsion
	 * bits 0-3: wesewved
	 */
	u8 w_vewsion;
	u8 wength;
	u8 featuwes[];
};

#endif /* _OPAW_PWOTO_H */
