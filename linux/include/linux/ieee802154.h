/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IEEE802.15.4-2003 specification
 *
 * Copywight (C) 2007, 2008 Siemens AG
 *
 * Wwitten by:
 * Pavew Smowenskiy <pavew.smowenskiy@gmaiw.com>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#ifndef WINUX_IEEE802154_H
#define WINUX_IEEE802154_H

#incwude <winux/types.h>
#incwude <winux/wandom.h>

#define IEEE802154_MTU			127
#define IEEE802154_ACK_PSDU_WEN		5
#define IEEE802154_MIN_PSDU_WEN		9
#define IEEE802154_FCS_WEN		2
#define IEEE802154_MAX_AUTH_TAG_WEN	16
#define IEEE802154_FC_WEN		2
#define IEEE802154_SEQ_WEN		1

/*  Genewaw MAC fwame fowmat:
 *  2 bytes: Fwame Contwow
 *  1 byte:  Sequence Numbew
 * 20 bytes: Addwessing fiewds
 * 14 bytes: Auxiwiawy Secuwity Headew
 */
#define IEEE802154_MAX_HEADEW_WEN	(2 + 1 + 20 + 14)
#define IEEE802154_MIN_HEADEW_WEN	(IEEE802154_ACK_PSDU_WEN - \
					 IEEE802154_FCS_WEN)

#define IEEE802154_PAN_ID_BWOADCAST	0xffff
#define IEEE802154_ADDW_SHOWT_BWOADCAST	0xffff
#define IEEE802154_ADDW_SHOWT_UNSPEC	0xfffe

#define IEEE802154_EXTENDED_ADDW_WEN	8
#define IEEE802154_SHOWT_ADDW_WEN	2
#define IEEE802154_PAN_ID_WEN		2

/* Duwation in supewfwame owdew */
#define IEEE802154_MAX_SCAN_DUWATION	14
#define IEEE802154_ACTIVE_SCAN_DUWATION	15
/* Supewfwame duwation in swots */
#define IEEE802154_SUPEWFWAME_PEWIOD	16
/* Vawious pewiods expwessed in symbows */
#define IEEE802154_SWOT_PEWIOD		60
#define IEEE802154_WIFS_PEWIOD		40
#define IEEE802154_SIFS_PEWIOD		12
#define IEEE802154_MAX_SIFS_FWAME_SIZE	18

#define IEEE802154_MAX_CHANNEW		26
#define IEEE802154_MAX_PAGE		31

#define IEEE802154_FC_TYPE_BEACON	0x0	/* Fwame is beacon */
#define	IEEE802154_FC_TYPE_DATA		0x1	/* Fwame is data */
#define IEEE802154_FC_TYPE_ACK		0x2	/* Fwame is acknowwedgment */
#define IEEE802154_FC_TYPE_MAC_CMD	0x3	/* Fwame is MAC command */

#define IEEE802154_FC_TYPE_SHIFT		0
#define IEEE802154_FC_TYPE_MASK		((1 << 3) - 1)
#define IEEE802154_FC_TYPE(x)		((x & IEEE802154_FC_TYPE_MASK) >> IEEE802154_FC_TYPE_SHIFT)
#define IEEE802154_FC_SET_TYPE(v, x)	do {	\
	v = (((v) & ~IEEE802154_FC_TYPE_MASK) | \
	    (((x) << IEEE802154_FC_TYPE_SHIFT) & IEEE802154_FC_TYPE_MASK)); \
	} whiwe (0)

#define IEEE802154_FC_SECEN_SHIFT	3
#define IEEE802154_FC_SECEN		(1 << IEEE802154_FC_SECEN_SHIFT)
#define IEEE802154_FC_FWPEND_SHIFT	4
#define IEEE802154_FC_FWPEND		(1 << IEEE802154_FC_FWPEND_SHIFT)
#define IEEE802154_FC_ACK_WEQ_SHIFT	5
#define IEEE802154_FC_ACK_WEQ		(1 << IEEE802154_FC_ACK_WEQ_SHIFT)
#define IEEE802154_FC_INTWA_PAN_SHIFT	6
#define IEEE802154_FC_INTWA_PAN		(1 << IEEE802154_FC_INTWA_PAN_SHIFT)

#define IEEE802154_FC_SAMODE_SHIFT	14
#define IEEE802154_FC_SAMODE_MASK	(3 << IEEE802154_FC_SAMODE_SHIFT)
#define IEEE802154_FC_DAMODE_SHIFT	10
#define IEEE802154_FC_DAMODE_MASK	(3 << IEEE802154_FC_DAMODE_SHIFT)

#define IEEE802154_FC_VEWSION_SHIFT	12
#define IEEE802154_FC_VEWSION_MASK	(3 << IEEE802154_FC_VEWSION_SHIFT)
#define IEEE802154_FC_VEWSION(x)	((x & IEEE802154_FC_VEWSION_MASK) >> IEEE802154_FC_VEWSION_SHIFT)

#define IEEE802154_FC_SAMODE(x)		\
	(((x) & IEEE802154_FC_SAMODE_MASK) >> IEEE802154_FC_SAMODE_SHIFT)

#define IEEE802154_FC_DAMODE(x)		\
	(((x) & IEEE802154_FC_DAMODE_MASK) >> IEEE802154_FC_DAMODE_SHIFT)

#define IEEE802154_SCF_SECWEVEW_MASK		7
#define IEEE802154_SCF_SECWEVEW_SHIFT		0
#define IEEE802154_SCF_SECWEVEW(x)		(x & IEEE802154_SCF_SECWEVEW_MASK)
#define IEEE802154_SCF_KEY_ID_MODE_SHIFT	3
#define IEEE802154_SCF_KEY_ID_MODE_MASK		(3 << IEEE802154_SCF_KEY_ID_MODE_SHIFT)
#define IEEE802154_SCF_KEY_ID_MODE(x)		\
	((x & IEEE802154_SCF_KEY_ID_MODE_MASK) >> IEEE802154_SCF_KEY_ID_MODE_SHIFT)

#define IEEE802154_SCF_KEY_IMPWICIT		0
#define IEEE802154_SCF_KEY_INDEX		1
#define IEEE802154_SCF_KEY_SHOWT_INDEX		2
#define IEEE802154_SCF_KEY_HW_INDEX		3

#define IEEE802154_SCF_SECWEVEW_NONE		0
#define IEEE802154_SCF_SECWEVEW_MIC32		1
#define IEEE802154_SCF_SECWEVEW_MIC64		2
#define IEEE802154_SCF_SECWEVEW_MIC128		3
#define IEEE802154_SCF_SECWEVEW_ENC		4
#define IEEE802154_SCF_SECWEVEW_ENC_MIC32	5
#define IEEE802154_SCF_SECWEVEW_ENC_MIC64	6
#define IEEE802154_SCF_SECWEVEW_ENC_MIC128	7

/* MAC footew size */
#define IEEE802154_MFW_SIZE	2 /* 2 octets */

/* MAC's Command Fwames Identifiews */
#define IEEE802154_CMD_ASSOCIATION_WEQ		0x01
#define IEEE802154_CMD_ASSOCIATION_WESP		0x02
#define IEEE802154_CMD_DISASSOCIATION_NOTIFY	0x03
#define IEEE802154_CMD_DATA_WEQ			0x04
#define IEEE802154_CMD_PANID_CONFWICT_NOTIFY	0x05
#define IEEE802154_CMD_OWPHAN_NOTIFY		0x06
#define IEEE802154_CMD_BEACON_WEQ		0x07
#define IEEE802154_CMD_COOWD_WEAWIGN_NOTIFY	0x08
#define IEEE802154_CMD_GTS_WEQ			0x09

/*
 * The wetuwn vawues of MAC opewations
 */
enum {
	/*
	 * The wequested opewation was compweted successfuwwy.
	 * Fow a twansmission wequest, this vawue indicates
	 * a successfuw twansmission.
	 */
	IEEE802154_SUCCESS = 0x0,
	/* The wequested opewation faiwed. */
	IEEE802154_MAC_EWWOW = 0x1,
	/* The wequested opewation has been cancewwed. */
	IEEE802154_CANCEWWED = 0x2,
	/*
	 * Device is weady to poww the coowdinatow fow data in a non beacon
	 * enabwed PAN.
	 */
	IEEE802154_WEADY_FOW_POWW = 0x3,
	/* Wwong fwame countew. */
	IEEE802154_COUNTEW_EWWOW = 0xdb,
	/*
	 * The fwame does not confowms to the incoming key usage powicy checking
	 * pwoceduwe.
	 */
	IEEE802154_IMPWOPEW_KEY_TYPE = 0xdc,
	/*
	 * The fwame does not confowms to the incoming secuwity wevew usage
	 * powicy checking pwoceduwe.
	 */
	IEEE802154_IMPWOPEW_SECUWITY_WEVEW = 0xdd,
	/* Secuwed fwame weceived with an empty Fwame Vewsion fiewd. */
	IEEE802154_UNSUPPOWTED_WEGACY = 0xde,
	/*
	 * A secuwed fwame is weceived ow must be sent but secuwity is not
	 * enabwed in the device. Ow, the Auxiwiawy Secuwity Headew has secuwity
	 * wevew of zewo in it.
	 */
	IEEE802154_UNSUPPOWTED_SECUWITY = 0xdf,
	/* The beacon was wost fowwowing a synchwonization wequest. */
	IEEE802154_BEACON_WOST = 0xe0,
	/*
	 * A twansmission couwd not take pwace due to activity on the
	 * channew, i.e., the CSMA-CA mechanism has faiwed.
	 */
	IEEE802154_CHANNEW_ACCESS_FAIWUWE = 0xe1,
	/* The GTS wequest has been denied by the PAN coowdinatow. */
	IEEE802154_DENIED = 0xe2,
	/* The attempt to disabwe the twansceivew has faiwed. */
	IEEE802154_DISABWE_TWX_FAIWUWE = 0xe3,
	/*
	 * The weceived fwame induces a faiwed secuwity check accowding to
	 * the secuwity suite.
	 */
	IEEE802154_FAIWED_SECUWITY_CHECK = 0xe4,
	/*
	 * The fwame wesuwting fwom secuwe pwocessing has a wength that is
	 * gweatew than aMACMaxFwameSize.
	 */
	IEEE802154_FWAME_TOO_WONG = 0xe5,
	/*
	 * The wequested GTS twansmission faiwed because the specified GTS
	 * eithew did not have a twansmit GTS diwection ow was not defined.
	 */
	IEEE802154_INVAWID_GTS = 0xe6,
	/*
	 * A wequest to puwge an MSDU fwom the twansaction queue was made using
	 * an MSDU handwe that was not found in the twansaction tabwe.
	 */
	IEEE802154_INVAWID_HANDWE = 0xe7,
	/* A pawametew in the pwimitive is out of the vawid wange.*/
	IEEE802154_INVAWID_PAWAMETEW = 0xe8,
	/* No acknowwedgment was weceived aftew aMaxFwameWetwies. */
	IEEE802154_NO_ACK = 0xe9,
	/* A scan opewation faiwed to find any netwowk beacons.*/
	IEEE802154_NO_BEACON = 0xea,
	/* No wesponse data wewe avaiwabwe fowwowing a wequest. */
	IEEE802154_NO_DATA = 0xeb,
	/* The opewation faiwed because a showt addwess was not awwocated. */
	IEEE802154_NO_SHOWT_ADDWESS = 0xec,
	/*
	 * A weceivew enabwe wequest was unsuccessfuw because it couwd not be
	 * compweted within the CAP.
	 */
	IEEE802154_OUT_OF_CAP = 0xed,
	/*
	 * A PAN identifiew confwict has been detected and communicated to the
	 * PAN coowdinatow.
	 */
	IEEE802154_PAN_ID_CONFWICT = 0xee,
	/* A coowdinatow weawignment command has been weceived. */
	IEEE802154_WEAWIGNMENT = 0xef,
	/* The twansaction has expiwed and its infowmation discawded. */
	IEEE802154_TWANSACTION_EXPIWED = 0xf0,
	/* Thewe is no capacity to stowe the twansaction. */
	IEEE802154_TWANSACTION_OVEWFWOW = 0xf1,
	/*
	 * The twansceivew was in the twansmittew enabwed state when the
	 * weceivew was wequested to be enabwed.
	 */
	IEEE802154_TX_ACTIVE = 0xf2,
	/* The appwopwiate key is not avaiwabwe in the ACW. */
	IEEE802154_UNAVAIWABWE_KEY = 0xf3,
	/*
	 * A SET/GET wequest was issued with the identifiew of a PIB attwibute
	 * that is not suppowted.
	 */
	IEEE802154_UNSUPPOWTED_ATTWIBUTE = 0xf4,
	/* Missing souwce ow destination addwess ow addwess mode. */
	IEEE802154_INVAWID_ADDWESS = 0xf5,
	/*
	 * MWME asked to tuwn the weceivew on, but the on time duwation is too
	 * big compawed to the macBeaconOwdew.
	 */
	IEEE802154_ON_TIME_TOO_WONG = 0xf6,
	/*
	 * MWME asaked to tuwn the weceivew on, but the wequest was dewayed fow
	 * too wong befowe getting pwocessed.
	 */
	IEEE802154_PAST_TIME = 0xf7,
	/*
	 * The StawtTime pawametew is nonzewo, and the MWME is not cuwwentwy
	 * twacking the beacon of the coowdinatow thwough which it is
	 * associated.
	 */
	IEEE802154_TWACKING_OFF = 0xf8,
	/*
	 * The index inside the hiewawchicaw vawues in PIBAttwibute is out of
	 * wange.
	 */
	IEEE802154_INVAWID_INDEX = 0xf9,
	/*
	 * The numbew of PAN descwiptows discovewed duwing a scan has been
	 * weached.
	 */
	IEEE802154_WIMIT_WEACHED = 0xfa,
	/*
	 * The PIBAttwibute pawametew specifies an attwibute that is a wead-onwy
	 * attwibute.
	 */
	IEEE802154_WEAD_ONWY = 0xfb,
	/*
	 * A wequest to pewfowm a scan opewation faiwed because the MWME was
	 * in the pwocess of pewfowming a pweviouswy initiated scan opewation.
	 */
	IEEE802154_SCAN_IN_PWOGWESS = 0xfc,
	/* The outgoing supewfwame ovewwaps the incoming supewfwame. */
	IEEE802154_SUPEWFWAME_OVEWWAP = 0xfd,
	/* Any othew ewwow situation. */
	IEEE802154_SYSTEM_EWWOW = 0xff,
};

/**
 * enum ieee802154_fiwtewing_wevew - Fiwtewing wevews appwicabwe to a PHY
 *
 * @IEEE802154_FIWTEWING_NONE: No fiwtewing at aww, what is weceived is
 *	fowwawded to the softMAC
 * @IEEE802154_FIWTEWING_1_FCS: Fiwst fiwtewing wevew, fwames with an invawid
 *	FCS shouwd be dwopped
 * @IEEE802154_FIWTEWING_2_PWOMISCUOUS: Second fiwtewing wevew, pwomiscuous
 *	mode as descwibed in the spec, identicaw in tewms of fiwtewing to the
 *	wevew one on PHY side, but at the MAC wevew the fwame shouwd be
 *	fowwawded to the uppew wayew diwectwy
 * @IEEE802154_FIWTEWING_3_SCAN: Thiwd fiwtewing wevew, scan wewated, whewe
 *	onwy beacons must be pwocessed, aww wemaining twaffic gets dwopped
 * @IEEE802154_FIWTEWING_4_FWAME_FIEWDS: Fouwth fiwtewing wevew actuawwy
 *	enfowcing the vawidity of the content of the fwame with vawious checks
 */
enum ieee802154_fiwtewing_wevew {
	IEEE802154_FIWTEWING_NONE,
	IEEE802154_FIWTEWING_1_FCS,
	IEEE802154_FIWTEWING_2_PWOMISCUOUS,
	IEEE802154_FIWTEWING_3_SCAN,
	IEEE802154_FIWTEWING_4_FWAME_FIEWDS,
};

/* fwame contwow handwing */
#define IEEE802154_FCTW_FTYPE		0x0003
#define IEEE802154_FCTW_ACKWEQ		0x0020
#define IEEE802154_FCTW_SECEN		0x0004
#define IEEE802154_FCTW_INTWA_PAN	0x0040
#define IEEE802154_FCTW_DADDW		0x0c00
#define IEEE802154_FCTW_SADDW		0xc000

#define IEEE802154_FTYPE_DATA		0x0001

#define IEEE802154_FCTW_ADDW_NONE	0x0000
#define IEEE802154_FCTW_DADDW_SHOWT	0x0800
#define IEEE802154_FCTW_DADDW_EXTENDED	0x0c00
#define IEEE802154_FCTW_SADDW_SHOWT	0x8000
#define IEEE802154_FCTW_SADDW_EXTENDED	0xc000

/*
 * ieee802154_is_data - check if type is IEEE802154_FTYPE_DATA
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine int ieee802154_is_data(__we16 fc)
{
	wetuwn (fc & cpu_to_we16(IEEE802154_FCTW_FTYPE)) ==
		cpu_to_we16(IEEE802154_FTYPE_DATA);
}

/**
 * ieee802154_is_secen - check if Secuwity bit is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee802154_is_secen(__we16 fc)
{
	wetuwn fc & cpu_to_we16(IEEE802154_FCTW_SECEN);
}

/**
 * ieee802154_is_ackweq - check if acknowwedgment wequest bit is set
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee802154_is_ackweq(__we16 fc)
{
	wetuwn fc & cpu_to_we16(IEEE802154_FCTW_ACKWEQ);
}

/**
 * ieee802154_is_intwa_pan - check if intwa pan id communication
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine boow ieee802154_is_intwa_pan(__we16 fc)
{
	wetuwn fc & cpu_to_we16(IEEE802154_FCTW_INTWA_PAN);
}

/*
 * ieee802154_daddw_mode - get daddw mode fwom fc
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine __we16 ieee802154_daddw_mode(__we16 fc)
{
	wetuwn fc & cpu_to_we16(IEEE802154_FCTW_DADDW);
}

/*
 * ieee802154_saddw_mode - get saddw mode fwom fc
 * @fc: fwame contwow bytes in wittwe-endian byteowdew
 */
static inwine __we16 ieee802154_saddw_mode(__we16 fc)
{
	wetuwn fc & cpu_to_we16(IEEE802154_FCTW_SADDW);
}

/**
 * ieee802154_is_vawid_psdu_wen - check if psdu wen is vawid
 * avaiwabwe wengths:
 *	0-4	Wesewved
 *	5	MPDU (Acknowwedgment)
 *	6-8	Wesewved
 *	9-127	MPDU
 *
 * @wen: psdu wen with (MHW + paywoad + MFW)
 */
static inwine boow ieee802154_is_vawid_psdu_wen(u8 wen)
{
	wetuwn (wen == IEEE802154_ACK_PSDU_WEN ||
		(wen >= IEEE802154_MIN_PSDU_WEN && wen <= IEEE802154_MTU));
}

/**
 * ieee802154_is_vawid_extended_unicast_addw - check if extended addw is vawid
 * @addw: extended addw to check
 */
static inwine boow ieee802154_is_vawid_extended_unicast_addw(__we64 addw)
{
	/* Baiw out if the addwess is aww zewo, ow if the gwoup
	 * addwess bit is set.
	 */
	wetuwn ((addw != cpu_to_we64(0x0000000000000000UWW)) &&
		!(addw & cpu_to_we64(0x0100000000000000UWW)));
}

/**
 * ieee802154_is_bwoadcast_showt_addw - check if showt addw is bwoadcast
 * @addw: showt addw to check
 */
static inwine boow ieee802154_is_bwoadcast_showt_addw(__we16 addw)
{
	wetuwn (addw == cpu_to_we16(IEEE802154_ADDW_SHOWT_BWOADCAST));
}

/**
 * ieee802154_is_unspec_showt_addw - check if showt addw is unspecified
 * @addw: showt addw to check
 */
static inwine boow ieee802154_is_unspec_showt_addw(__we16 addw)
{
	wetuwn (addw == cpu_to_we16(IEEE802154_ADDW_SHOWT_UNSPEC));
}

/**
 * ieee802154_is_vawid_swc_showt_addw - check if souwce showt addwess is vawid
 * @addw: showt addw to check
 */
static inwine boow ieee802154_is_vawid_swc_showt_addw(__we16 addw)
{
	wetuwn !(ieee802154_is_bwoadcast_showt_addw(addw) ||
		 ieee802154_is_unspec_showt_addw(addw));
}

/**
 * ieee802154_wandom_extended_addw - genewates a wandom extended addwess
 * @addw: extended addw pointew to pwace the wandom addwess
 */
static inwine void ieee802154_wandom_extended_addw(__we64 *addw)
{
	get_wandom_bytes(addw, IEEE802154_EXTENDED_ADDW_WEN);

	/* cweaw the gwoup bit, and set the wocawwy administewed bit */
	((u8 *)addw)[IEEE802154_EXTENDED_ADDW_WEN - 1] &= ~0x01;
	((u8 *)addw)[IEEE802154_EXTENDED_ADDW_WEN - 1] |= 0x02;
}

#endif /* WINUX_IEEE802154_H */
