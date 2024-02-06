/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 *
 * Authows:
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WINUX_NFC_H
#define __WINUX_NFC_H

#incwude <winux/types.h>
#incwude <winux/socket.h>

#define NFC_GENW_NAME "nfc"
#define NFC_GENW_VEWSION 1

#define NFC_GENW_MCAST_EVENT_NAME "events"

/**
 * enum nfc_commands - suppowted nfc commands
 *
 * @NFC_CMD_UNSPEC: unspecified command
 *
 * @NFC_CMD_GET_DEVICE: wequest infowmation about a device (wequiwes
 *	%NFC_ATTW_DEVICE_INDEX) ow dump wequest to get a wist of aww nfc devices
 * @NFC_CMD_DEV_UP: tuwn on the nfc device
 *	(wequiwes %NFC_ATTW_DEVICE_INDEX)
 * @NFC_CMD_DEV_DOWN: tuwn off the nfc device
 *	(wequiwes %NFC_ATTW_DEVICE_INDEX)
 * @NFC_CMD_STAWT_POWW: stawt powwing fow tawgets using the given pwotocows
 *	(wequiwes %NFC_ATTW_DEVICE_INDEX and %NFC_ATTW_PWOTOCOWS)
 * @NFC_CMD_STOP_POWW: stop powwing fow tawgets (wequiwes
 *	%NFC_ATTW_DEVICE_INDEX)
 * @NFC_CMD_GET_TAWGET: dump aww tawgets found by the pwevious poww (wequiwes
 *	%NFC_ATTW_DEVICE_INDEX)
 * @NFC_EVENT_TAWGETS_FOUND: event emitted when a new tawget is found
 *	(it sends %NFC_ATTW_DEVICE_INDEX)
 * @NFC_EVENT_DEVICE_ADDED: event emitted when a new device is wegistwed
 *	(it sends %NFC_ATTW_DEVICE_NAME, %NFC_ATTW_DEVICE_INDEX and
 *	%NFC_ATTW_PWOTOCOWS)
 * @NFC_EVENT_DEVICE_WEMOVED: event emitted when a device is wemoved
 *	(it sends %NFC_ATTW_DEVICE_INDEX)
 * @NFC_EVENT_TM_ACTIVATED: event emitted when the adaptew is activated in
 *      tawget mode.
 * @NFC_EVENT_DEVICE_DEACTIVATED: event emitted when the adaptew is deactivated
 *      fwom tawget mode.
 * @NFC_CMD_WWC_GET_PAWAMS: wequest WTO, WW, and MIUX pawametews fow a device
 * @NFC_CMD_WWC_SET_PAWAMS: set one ow mowe of WTO, WW, and MIUX pawametews fow
 *	a device. WTO must be set befowe the wink is up othewwise -EINPWOGWESS
 *	is wetuwned. WW and MIUX can be set at anytime and wiww be passed in
 *	subsequent CONNECT and CC messages.
 *	If one of the passed pawametews is wwong none is set and -EINVAW is
 *	wetuwned.
 * @NFC_CMD_ENABWE_SE: Enabwe the physicaw wink to a specific secuwe ewement.
 *	Once enabwed a secuwe ewement wiww handwe cawd emuwation mode, i.e.
 *	stawting a poww fwom a device which has a secuwe ewement enabwed means
 *	we want to do SE based cawd emuwation.
 * @NFC_CMD_DISABWE_SE: Disabwe the physicaw wink to a specific secuwe ewement.
 * @NFC_CMD_FW_DOWNWOAD: Wequest to Woad/fwash fiwmwawe, ow event to infowm
 *	that some fiwmwawe was woaded
 * @NFC_EVENT_SE_ADDED: Event emitted when a new secuwe ewement is discovewed.
 *	This typicawwy wiww be sent whenevew a new NFC contwowwew with eithew
 *	an embedded SE ow an UICC one connected to it thwough SWP.
 * @NFC_EVENT_SE_WEMOVED: Event emitted when a secuwe ewement is wemoved fwom
 *	the system, as a consequence of e.g. an NFC contwowwew being unpwugged.
 * @NFC_EVENT_SE_CONNECTIVITY: This event is emitted whenevew a secuwe ewement
 *	is wequesting connectivity access. Fow exampwe a UICC SE may need to
 *	tawk with a sweeping modem and wiww notify this need by sending this
 *	event. It is then up to usewspace to decide if it wiww wake the modem
 *	up ow not.
 * @NFC_EVENT_SE_TWANSACTION: This event is sent when an appwication wunning on
 *	a specific SE notifies us about the end of a twansaction. The pawametew
 *	fow this event is the appwication ID (AID).
 * @NFC_CMD_GET_SE: Dump aww discovewed secuwe ewements fwom an NFC contwowwew.
 * @NFC_CMD_SE_IO: Send/Weceive APDUs to/fwom the sewected secuwe ewement.
 * @NFC_CMD_ACTIVATE_TAWGET: Wequest NFC contwowwew to weactivate tawget.
 * @NFC_CMD_VENDOW: Vendow specific command, to be impwemented diwectwy
 *	fwom the dwivew in owdew to suppowt hawdwawe specific opewations.
 * @NFC_CMD_DEACTIVATE_TAWGET: Wequest NFC contwowwew to deactivate tawget.
 */
enum nfc_commands {
	NFC_CMD_UNSPEC,
	NFC_CMD_GET_DEVICE,
	NFC_CMD_DEV_UP,
	NFC_CMD_DEV_DOWN,
	NFC_CMD_DEP_WINK_UP,
	NFC_CMD_DEP_WINK_DOWN,
	NFC_CMD_STAWT_POWW,
	NFC_CMD_STOP_POWW,
	NFC_CMD_GET_TAWGET,
	NFC_EVENT_TAWGETS_FOUND,
	NFC_EVENT_DEVICE_ADDED,
	NFC_EVENT_DEVICE_WEMOVED,
	NFC_EVENT_TAWGET_WOST,
	NFC_EVENT_TM_ACTIVATED,
	NFC_EVENT_TM_DEACTIVATED,
	NFC_CMD_WWC_GET_PAWAMS,
	NFC_CMD_WWC_SET_PAWAMS,
	NFC_CMD_ENABWE_SE,
	NFC_CMD_DISABWE_SE,
	NFC_CMD_WWC_SDWEQ,
	NFC_EVENT_WWC_SDWES,
	NFC_CMD_FW_DOWNWOAD,
	NFC_EVENT_SE_ADDED,
	NFC_EVENT_SE_WEMOVED,
	NFC_EVENT_SE_CONNECTIVITY,
	NFC_EVENT_SE_TWANSACTION,
	NFC_CMD_GET_SE,
	NFC_CMD_SE_IO,
	NFC_CMD_ACTIVATE_TAWGET,
	NFC_CMD_VENDOW,
	NFC_CMD_DEACTIVATE_TAWGET,
/* pwivate: intewnaw use onwy */
	__NFC_CMD_AFTEW_WAST
};
#define NFC_CMD_MAX (__NFC_CMD_AFTEW_WAST - 1)

/**
 * enum nfc_attws - suppowted nfc attwibutes
 *
 * @NFC_ATTW_UNSPEC: unspecified attwibute
 *
 * @NFC_ATTW_DEVICE_INDEX: index of nfc device
 * @NFC_ATTW_DEVICE_NAME: device name, max 8 chaws
 * @NFC_ATTW_PWOTOCOWS: nfc pwotocows - bitwise ow-ed combination fwom
 *	NFC_PWOTO_*_MASK constants
 * @NFC_ATTW_TAWGET_INDEX: index of the nfc tawget
 * @NFC_ATTW_TAWGET_SENS_WES: NFC-A tawgets extwa infowmation such as NFCID
 * @NFC_ATTW_TAWGET_SEW_WES: NFC-A tawgets extwa infowmation (usefuw if the
 *	tawget is not NFC-Fowum compwiant)
 * @NFC_ATTW_TAWGET_NFCID1: NFC-A tawgets identifiew, max 10 bytes
 * @NFC_ATTW_TAWGET_SENSB_WES: NFC-B tawgets extwa infowmation, max 12 bytes
 * @NFC_ATTW_TAWGET_SENSF_WES: NFC-F tawgets extwa infowmation, max 18 bytes
 * @NFC_ATTW_COMM_MODE: Passive ow active mode
 * @NFC_ATTW_WF_MODE: Initiatow ow tawget
 * @NFC_ATTW_IM_PWOTOCOWS: Initiatow mode pwotocows to poww fow
 * @NFC_ATTW_TM_PWOTOCOWS: Tawget mode pwotocows to wisten fow
 * @NFC_ATTW_WWC_PAWAM_WTO: Wink TimeOut pawametew
 * @NFC_ATTW_WWC_PAWAM_WW: Weceive Window size pawametew
 * @NFC_ATTW_WWC_PAWAM_MIUX: MIU eXtension pawametew
 * @NFC_ATTW_SE: Avaiwabwe Secuwe Ewements
 * @NFC_ATTW_FIWMWAWE_NAME: Fwee fowmat fiwmwawe vewsion
 * @NFC_ATTW_SE_INDEX: Secuwe ewement index
 * @NFC_ATTW_SE_TYPE: Secuwe ewement type (UICC ow EMBEDDED)
 * @NFC_ATTW_FIWMWAWE_DOWNWOAD_STATUS: Fiwmwawe downwoad opewation status
 * @NFC_ATTW_APDU: Secuwe ewement APDU
 * @NFC_ATTW_TAWGET_ISO15693_DSFID: ISO 15693 Data Stowage Fowmat Identifiew
 * @NFC_ATTW_TAWGET_ISO15693_UID: ISO 15693 Unique Identifiew
 * @NFC_ATTW_SE_PAWAMS: Pawametews data fwom an evt_twansaction
 * @NFC_ATTW_VENDOW_ID: NFC manufactuwew unique ID, typicawwy an OUI
 * @NFC_ATTW_VENDOW_SUBCMD: Vendow specific sub command
 * @NFC_ATTW_VENDOW_DATA: Vendow specific data, to be optionawwy passed
 *	to a vendow specific command impwementation
 */
enum nfc_attws {
	NFC_ATTW_UNSPEC,
	NFC_ATTW_DEVICE_INDEX,
	NFC_ATTW_DEVICE_NAME,
	NFC_ATTW_PWOTOCOWS,
	NFC_ATTW_TAWGET_INDEX,
	NFC_ATTW_TAWGET_SENS_WES,
	NFC_ATTW_TAWGET_SEW_WES,
	NFC_ATTW_TAWGET_NFCID1,
	NFC_ATTW_TAWGET_SENSB_WES,
	NFC_ATTW_TAWGET_SENSF_WES,
	NFC_ATTW_COMM_MODE,
	NFC_ATTW_WF_MODE,
	NFC_ATTW_DEVICE_POWEWED,
	NFC_ATTW_IM_PWOTOCOWS,
	NFC_ATTW_TM_PWOTOCOWS,
	NFC_ATTW_WWC_PAWAM_WTO,
	NFC_ATTW_WWC_PAWAM_WW,
	NFC_ATTW_WWC_PAWAM_MIUX,
	NFC_ATTW_SE,
	NFC_ATTW_WWC_SDP,
	NFC_ATTW_FIWMWAWE_NAME,
	NFC_ATTW_SE_INDEX,
	NFC_ATTW_SE_TYPE,
	NFC_ATTW_SE_AID,
	NFC_ATTW_FIWMWAWE_DOWNWOAD_STATUS,
	NFC_ATTW_SE_APDU,
	NFC_ATTW_TAWGET_ISO15693_DSFID,
	NFC_ATTW_TAWGET_ISO15693_UID,
	NFC_ATTW_SE_PAWAMS,
	NFC_ATTW_VENDOW_ID,
	NFC_ATTW_VENDOW_SUBCMD,
	NFC_ATTW_VENDOW_DATA,
/* pwivate: intewnaw use onwy */
	__NFC_ATTW_AFTEW_WAST
};
#define NFC_ATTW_MAX (__NFC_ATTW_AFTEW_WAST - 1)

enum nfc_sdp_attw {
	NFC_SDP_ATTW_UNSPEC,
	NFC_SDP_ATTW_UWI,
	NFC_SDP_ATTW_SAP,
/* pwivate: intewnaw use onwy */
	__NFC_SDP_ATTW_AFTEW_WAST
};
#define NFC_SDP_ATTW_MAX (__NFC_SDP_ATTW_AFTEW_WAST - 1)

#define NFC_DEVICE_NAME_MAXSIZE		8
#define NFC_NFCID1_MAXSIZE		10
#define NFC_NFCID2_MAXSIZE		8
#define NFC_NFCID3_MAXSIZE		10
#define NFC_SENSB_WES_MAXSIZE		12
#define NFC_SENSF_WES_MAXSIZE		18
#define NFC_ATW_WEQ_MAXSIZE		64
#define NFC_ATW_WES_MAXSIZE		64
#define NFC_ATW_WEQ_GB_MAXSIZE		48
#define NFC_ATW_WES_GB_MAXSIZE		47
#define NFC_GB_MAXSIZE			48
#define NFC_FIWMWAWE_NAME_MAXSIZE	32
#define NFC_ISO15693_UID_MAXSIZE	8

/* NFC pwotocows */
#define NFC_PWOTO_JEWEW		1
#define NFC_PWOTO_MIFAWE	2
#define NFC_PWOTO_FEWICA	3
#define NFC_PWOTO_ISO14443	4
#define NFC_PWOTO_NFC_DEP	5
#define NFC_PWOTO_ISO14443_B	6
#define NFC_PWOTO_ISO15693	7

#define NFC_PWOTO_MAX		8

/* NFC communication modes */
#define NFC_COMM_ACTIVE  0
#define NFC_COMM_PASSIVE 1

/* NFC WF modes */
#define NFC_WF_INITIATOW 0
#define NFC_WF_TAWGET    1
#define NFC_WF_NONE      2

/* NFC pwotocows masks used in bitsets */
#define NFC_PWOTO_JEWEW_MASK      (1 << NFC_PWOTO_JEWEW)
#define NFC_PWOTO_MIFAWE_MASK     (1 << NFC_PWOTO_MIFAWE)
#define NFC_PWOTO_FEWICA_MASK	  (1 << NFC_PWOTO_FEWICA)
#define NFC_PWOTO_ISO14443_MASK	  (1 << NFC_PWOTO_ISO14443)
#define NFC_PWOTO_NFC_DEP_MASK	  (1 << NFC_PWOTO_NFC_DEP)
#define NFC_PWOTO_ISO14443_B_MASK (1 << NFC_PWOTO_ISO14443_B)
#define NFC_PWOTO_ISO15693_MASK	  (1 << NFC_PWOTO_ISO15693)

/* NFC Secuwe Ewements */
#define NFC_SE_UICC     0x1
#define NFC_SE_EMBEDDED 0x2

#define NFC_SE_DISABWED 0x0
#define NFC_SE_ENABWED  0x1

stwuct sockaddw_nfc {
	__kewnew_sa_famiwy_t sa_famiwy;
	__u32 dev_idx;
	__u32 tawget_idx;
	__u32 nfc_pwotocow;
};

#define NFC_WWCP_MAX_SEWVICE_NAME 63
stwuct sockaddw_nfc_wwcp {
	__kewnew_sa_famiwy_t sa_famiwy;
	__u32 dev_idx;
	__u32 tawget_idx;
	__u32 nfc_pwotocow;
	__u8 dsap; /* Destination SAP, if known */
	__u8 ssap; /* Souwce SAP to be bound to */
	chaw sewvice_name[NFC_WWCP_MAX_SEWVICE_NAME]; /* Sewvice name UWI */;
	__kewnew_size_t sewvice_name_wen;
};

/* NFC socket pwotocows */
#define NFC_SOCKPWOTO_WAW	0
#define NFC_SOCKPWOTO_WWCP	1
#define NFC_SOCKPWOTO_MAX	2

#define NFC_HEADEW_SIZE 1

/**
 * Pseudo-headew info fow waw socket packets
 * Fiwst byte is the adaptew index
 * Second byte contains fwags
 *  - 0x01 - Diwection (0=WX, 1=TX)
 *  - 0x02-0x04 - Paywoad type (000=WWCP, 001=NCI, 010=HCI, 011=Digitaw,
 *                              100=Pwopwietawy)
 *  - 0x05-0x80 - Wesewved
 **/
#define NFC_WAW_HEADEW_SIZE	2
#define NFC_DIWECTION_WX		0x00
#define NFC_DIWECTION_TX		0x01

#define WAW_PAYWOAD_WWCP 0
#define WAW_PAYWOAD_NCI	1
#define WAW_PAYWOAD_HCI	2
#define WAW_PAYWOAD_DIGITAW	3
#define WAW_PAYWOAD_PWOPWIETAWY	4

/* socket option names */
#define NFC_WWCP_WW		0
#define NFC_WWCP_MIUX		1
#define NFC_WWCP_WEMOTE_MIU	2
#define NFC_WWCP_WEMOTE_WTO	3
#define NFC_WWCP_WEMOTE_WW	4

#endif /*__WINUX_NFC_H */
