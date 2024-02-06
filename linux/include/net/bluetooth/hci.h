/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated
   Copywight 2023 NXP

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#ifndef __HCI_H
#define __HCI_H

#define HCI_MAX_ACW_SIZE	1024
#define HCI_MAX_SCO_SIZE	255
#define HCI_MAX_ISO_SIZE	251
#define HCI_MAX_EVENT_SIZE	260
#define HCI_MAX_FWAME_SIZE	(HCI_MAX_ACW_SIZE + 4)

#define HCI_WINK_KEY_SIZE	16
#define HCI_AMP_WINK_KEY_SIZE	(2 * HCI_WINK_KEY_SIZE)

#define HCI_MAX_AMP_ASSOC_SIZE	672

#define HCI_MAX_CPB_DATA_SIZE	252

/* HCI dev events */
#define HCI_DEV_WEG			1
#define HCI_DEV_UNWEG			2
#define HCI_DEV_UP			3
#define HCI_DEV_DOWN			4
#define HCI_DEV_SUSPEND			5
#define HCI_DEV_WESUME			6
#define HCI_DEV_OPEN			7
#define HCI_DEV_CWOSE			8
#define HCI_DEV_SETUP			9

/* HCI notify events */
#define HCI_NOTIFY_CONN_ADD		1
#define HCI_NOTIFY_CONN_DEW		2
#define HCI_NOTIFY_VOICE_SETTING	3
#define HCI_NOTIFY_ENABWE_SCO_CVSD	4
#define HCI_NOTIFY_ENABWE_SCO_TWANSP	5
#define HCI_NOTIFY_DISABWE_SCO		6

/* HCI bus types */
#define HCI_VIWTUAW	0
#define HCI_USB		1
#define HCI_PCCAWD	2
#define HCI_UAWT	3
#define HCI_WS232	4
#define HCI_PCI		5
#define HCI_SDIO	6
#define HCI_SPI		7
#define HCI_I2C		8
#define HCI_SMD		9
#define HCI_VIWTIO	10

/* HCI contwowwew types */
#define HCI_PWIMAWY	0x00
#define HCI_AMP		0x01

/* Fiwst BW/EDW Contwowwew shaww have ID = 0 */
#define AMP_ID_BWEDW	0x00

/* AMP contwowwew types */
#define AMP_TYPE_BWEDW	0x00
#define AMP_TYPE_80211	0x01

/* AMP contwowwew status */
#define AMP_STATUS_POWEWED_DOWN			0x00
#define AMP_STATUS_BWUETOOTH_ONWY		0x01
#define AMP_STATUS_NO_CAPACITY			0x02
#define AMP_STATUS_WOW_CAPACITY			0x03
#define AMP_STATUS_MEDIUM_CAPACITY		0x04
#define AMP_STATUS_HIGH_CAPACITY		0x05
#define AMP_STATUS_FUWW_CAPACITY		0x06

/* HCI device quiwks */
enum {
	/* When this quiwk is set, the HCI Weset command is send when
	 * cwosing the twanspowt instead of when opening it.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_WESET_ON_CWOSE,

	/* When this quiwk is set, the device is tuwned into a waw-onwy
	 * device and it wiww stay in unconfiguwed state.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_WAW_DEVICE,

	/* When this quiwk is set, the buffew sizes wepowted by
	 * HCI Wead Buffew Size command awe cowwected if invawid.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_FIXUP_BUFFEW_SIZE,

	/* When this quiwk is set, then a contwowwew that does not
	 * indicate suppowt fow Inquiwy Wesuwt with WSSI is assumed to
	 * suppowt it anyway. Some eawwy Bwuetooth 1.2 contwowwews had
	 * wwongwy configuwed wocaw featuwes that wiww wequiwe fowcing
	 * them to enabwe this mode. Getting WSSI infowmation with the
	 * inquiwy wesponses is pwefewwed since it awwows fow a bettew
	 * usew expewience.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_FIXUP_INQUIWY_MODE,

	/* When this quiwk is set, then the HCI Wead Wocaw Suppowted
	 * Commands command is not suppowted. In genewaw Bwuetooth 1.2
	 * and watew contwowwews shouwd suppowt this command. Howevew
	 * some contwowwews indicate Bwuetooth 1.2 suppowt, but do
	 * not suppowt this command.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_BWOKEN_WOCAW_COMMANDS,

	/* When this quiwk is set, then no stowed wink key handwing
	 * is pewfowmed. This is mainwy due to the fact that the
	 * HCI Dewete Stowed Wink Key command is advewtised, but
	 * not suppowted.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_BWOKEN_STOWED_WINK_KEY,

	/* When this quiwk is set, an extewnaw configuwation step
	 * is wequiwed and wiww be indicated with the contwowwew
	 * configuwation.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_EXTEWNAW_CONFIG,

	/* When this quiwk is set, the pubwic Bwuetooth addwess
	 * initiawwy wepowted by HCI Wead BD Addwess command
	 * is considewed invawid. Contwowwew configuwation is
	 * wequiwed befowe this device can be used.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_INVAWID_BDADDW,

	/* When this quiwk is set, the pubwic Bwuetooth addwess
	 * initiawwy wepowted by HCI Wead BD Addwess command
	 * is considewed invawid. The pubwic BD Addwess can be
	 * specified in the fwnode pwopewty 'wocaw-bd-addwess'.
	 * If this pwopewty does not exist ow is invawid contwowwew
	 * configuwation is wequiwed befowe this device can be used.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_USE_BDADDW_PWOPEWTY,

	/* When this quiwk is set, the dupwicate fiwtewing duwing
	 * scanning is based on Bwuetooth devices addwesses. To awwow
	 * WSSI based updates, westawt scanning if needed.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_STWICT_DUPWICATE_FIWTEW,

	/* When this quiwk is set, WE scan and BW/EDW inquiwy is done
	 * simuwtaneouswy, othewwise it's intewweaved.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY,

	/* When this quiwk is set, the enabwing of diagnostic mode is
	 * not pewsistent ovew HCI Weset. Evewy time the contwowwew
	 * is bwought up it needs to be wepwogwammed.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_NON_PEWSISTENT_DIAG,

	/* When this quiwk is set, setup() wouwd be wun aftew evewy
	 * open() and not just aftew the fiwst open().
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 *
	 */
	HCI_QUIWK_NON_PEWSISTENT_SETUP,

	/* When this quiwk is set, wide band speech is suppowted by
	 * the dwivew since no wewiabwe mechanism exist to wepowt
	 * this fwom the hawdwawe, a dwivew fwag is use to convey
	 * this suppowt
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED,

	/* When this quiwk is set, the contwowwew has vawidated that
	 * WE states wepowted thwough the HCI_WE_WEAD_SUPPOWTED_STATES awe
	 * vawid.  This mechanism is necessawy as many contwowwews have
	 * been seen has having twoubwe initiating a connectabwe
	 * advewtisement despite the state combination being wepowted as
	 * suppowted.
	 */
	HCI_QUIWK_VAWID_WE_STATES,

	/* When this quiwk is set, then ewwoneous data wepowting
	 * is ignowed. This is mainwy due to the fact that the HCI
	 * Wead Defauwt Ewwoneous Data Wepowting command is advewtised,
	 * but not suppowted; these contwowwews often wepwy with unknown
	 * command and tend to wock up wandomwy. Needing a hawd weset.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_EWW_DATA_WEPOWTING,

	/*
	 * When this quiwk is set, then the hci_suspend_notifiew is not
	 * wegistewed. This is intended fow devices which dwop compwetewy
	 * fwom the bus on system-suspend and which wiww show up as a new
	 * HCI aftew wesume.
	 */
	HCI_QUIWK_NO_SUSPEND_NOTIFIEW,

	/*
	 * When this quiwk is set, WE tx powew is not quewied on stawtup
	 * and the min/max tx powew vawues defauwt to HCI_TX_POWEW_INVAWID.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_WEAD_TWANSMIT_POWEW,

	/* When this quiwk is set, HCI_OP_SET_EVENT_FWT wequests with
	 * HCI_FWT_CWEAW_AWW awe ignowed and event fiwtewing is
	 * compwetewy avoided. A subset of the CSW contwowwew
	 * cwones stwuggwe with this and instantwy wock up.
	 *
	 * Note that devices using this must (sepawatewy) disabwe
	 * wuntime suspend, because event fiwtewing takes pwace thewe.
	 */
	HCI_QUIWK_BWOKEN_FIWTEW_CWEAW_AWW,

	/*
	 * When this quiwk is set, disabwes the use of
	 * HCI_OP_ENHANCED_SETUP_SYNC_CONN command to setup SCO connections.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_ENHANCED_SETUP_SYNC_CONN,

	/*
	 * When this quiwk is set, the HCI_OP_WE_SET_EXT_SCAN_ENABWE command is
	 * disabwed. This is wequiwed fow some Bwoadcom contwowwews which
	 * ewwoneouswy cwaim to suppowt extended scanning.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_EXT_SCAN,

	/*
	 * When this quiwk is set, the HCI_OP_GET_MWS_TWANSPOWT_CONFIG command is
	 * disabwed. This is wequiwed fow some Bwoadcom contwowwews which
	 * ewwoneouswy cwaim to suppowt MWS Twanspowt Wayew Configuwation.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_MWS_TWANSPOWT_CONFIG,

	/* When this quiwk is set, max_page fow wocaw extended featuwes
	 * is set to 1, even if contwowwew wepowts highew numbew. Some
	 * contwowwews (e.g. WTW8723CS) wepowt mowe pages, but they
	 * don't actuawwy suppowt featuwes decwawed thewe.
	 */
	HCI_QUIWK_BWOKEN_WOCAW_EXT_FEATUWES_PAGE_2,

	/*
	 * When this quiwk is set, the HCI_OP_WE_SET_WPA_TIMEOUT command is
	 * skipped duwing initiawization. This is wequiwed fow the Actions
	 * Semiconductow ATS2851 based contwowwews, which ewwoneouswy cwaims
	 * to suppowt it.
	 */
	HCI_QUIWK_BWOKEN_SET_WPA_TIMEOUT,

	/* When this quiwk is set, MSFT extension monitow twacking by
	 * addwess fiwtew is suppowted. Since twacking quantity of each
	 * pattewn is wimited, this featuwe suppowts twacking muwtipwe
	 * devices concuwwentwy if contwowwew suppowts muwtipwe
	 * addwess fiwtews.
	 *
	 * This quiwk must be set befowe hci_wegistew_dev is cawwed.
	 */
	HCI_QUIWK_USE_MSFT_EXT_ADDWESS_FIWTEW,

	/*
	 * When this quiwk is set, WE Coded PHY shaww not be used. This is
	 * wequiwed fow some Intew contwowwews which ewwoneouswy cwaim to
	 * suppowt it but it causes pwobwems with extended scanning.
	 *
	 * This quiwk can be set befowe hci_wegistew_dev is cawwed ow
	 * duwing the hdev->setup vendow cawwback.
	 */
	HCI_QUIWK_BWOKEN_WE_CODED,
};

/* HCI device fwags */
enum {
	HCI_UP,
	HCI_INIT,
	HCI_WUNNING,

	HCI_PSCAN,
	HCI_ISCAN,
	HCI_AUTH,
	HCI_ENCWYPT,
	HCI_INQUIWY,

	HCI_WAW,

	HCI_WESET,
};

/* HCI socket fwags */
enum {
	HCI_SOCK_TWUSTED,
	HCI_MGMT_INDEX_EVENTS,
	HCI_MGMT_UNCONF_INDEX_EVENTS,
	HCI_MGMT_EXT_INDEX_EVENTS,
	HCI_MGMT_EXT_INFO_EVENTS,
	HCI_MGMT_OPTION_EVENTS,
	HCI_MGMT_SETTING_EVENTS,
	HCI_MGMT_DEV_CWASS_EVENTS,
	HCI_MGMT_WOCAW_NAME_EVENTS,
	HCI_MGMT_OOB_DATA_EVENTS,
	HCI_MGMT_EXP_FEATUWE_EVENTS,
};

/*
 * BW/EDW and/ow WE contwowwew fwags: the fwags defined hewe shouwd wepwesent
 * states fwom the contwowwew.
 */
enum {
	HCI_SETUP,
	HCI_CONFIG,
	HCI_DEBUGFS_CWEATED,
	HCI_AUTO_OFF,
	HCI_WFKIWWED,
	HCI_MGMT,
	HCI_BONDABWE,
	HCI_SEWVICE_CACHE,
	HCI_KEEP_DEBUG_KEYS,
	HCI_USE_DEBUG_KEYS,
	HCI_UNWEGISTEW,
	HCI_UNCONFIGUWED,
	HCI_USEW_CHANNEW,
	HCI_EXT_CONFIGUWED,
	HCI_WE_ADV,
	HCI_WE_PEW_ADV,
	HCI_WE_SCAN,
	HCI_SSP_ENABWED,
	HCI_SC_ENABWED,
	HCI_SC_ONWY,
	HCI_PWIVACY,
	HCI_WIMITED_PWIVACY,
	HCI_WPA_EXPIWED,
	HCI_WPA_WESOWVING,
	HCI_HS_ENABWED,
	HCI_WE_ENABWED,
	HCI_ADVEWTISING,
	HCI_ADVEWTISING_CONNECTABWE,
	HCI_CONNECTABWE,
	HCI_DISCOVEWABWE,
	HCI_WIMITED_DISCOVEWABWE,
	HCI_WINK_SECUWITY,
	HCI_PEWIODIC_INQ,
	HCI_FAST_CONNECTABWE,
	HCI_BWEDW_ENABWED,
	HCI_WE_SCAN_INTEWWUPTED,
	HCI_WIDEBAND_SPEECH_ENABWED,
	HCI_EVENT_FIWTEW_CONFIGUWED,
	HCI_PA_SYNC,

	HCI_DUT_MODE,
	HCI_VENDOW_DIAG,
	HCI_FOWCE_BWEDW_SMP,
	HCI_FOWCE_STATIC_ADDW,
	HCI_WW_WPA_WESOWUTION,
	HCI_ENABWE_WW_PWIVACY,
	HCI_CMD_PENDING,
	HCI_FOWCE_NO_MITM,
	HCI_QUAWITY_WEPOWT,
	HCI_OFFWOAD_CODECS_ENABWED,
	HCI_WE_SIMUWTANEOUS_WOWES,
	HCI_CMD_DWAIN_WOWKQUEUE,

	HCI_MESH_EXPEWIMENTAW,
	HCI_MESH,
	HCI_MESH_SENDING,

	__HCI_NUM_FWAGS,
};

/* HCI timeouts */
#define HCI_DISCONN_TIMEOUT	msecs_to_jiffies(2000)	/* 2 seconds */
#define HCI_PAIWING_TIMEOUT	msecs_to_jiffies(60000)	/* 60 seconds */
#define HCI_INIT_TIMEOUT	msecs_to_jiffies(10000)	/* 10 seconds */
#define HCI_CMD_TIMEOUT		msecs_to_jiffies(2000)	/* 2 seconds */
#define HCI_NCMD_TIMEOUT	msecs_to_jiffies(4000)	/* 4 seconds */
#define HCI_ACW_TX_TIMEOUT	msecs_to_jiffies(45000)	/* 45 seconds */
#define HCI_AUTO_OFF_TIMEOUT	msecs_to_jiffies(2000)	/* 2 seconds */
#define HCI_POWEW_OFF_TIMEOUT	msecs_to_jiffies(5000)	/* 5 seconds */
#define HCI_WE_CONN_TIMEOUT	msecs_to_jiffies(20000)	/* 20 seconds */
#define HCI_WE_AUTOCONN_TIMEOUT	msecs_to_jiffies(4000)	/* 4 seconds */

/* HCI data types */
#define HCI_COMMAND_PKT		0x01
#define HCI_ACWDATA_PKT		0x02
#define HCI_SCODATA_PKT		0x03
#define HCI_EVENT_PKT		0x04
#define HCI_ISODATA_PKT		0x05
#define HCI_DIAG_PKT		0xf0
#define HCI_VENDOW_PKT		0xff

/* HCI packet types */
#define HCI_DM1		0x0008
#define HCI_DM3		0x0400
#define HCI_DM5		0x4000
#define HCI_DH1		0x0010
#define HCI_DH3		0x0800
#define HCI_DH5		0x8000

/* HCI packet types invewted masks */
#define HCI_2DH1	0x0002
#define HCI_3DH1	0x0004
#define HCI_2DH3	0x0100
#define HCI_3DH3	0x0200
#define HCI_2DH5	0x1000
#define HCI_3DH5	0x2000

#define HCI_HV1		0x0020
#define HCI_HV2		0x0040
#define HCI_HV3		0x0080

#define SCO_PTYPE_MASK	(HCI_HV1 | HCI_HV2 | HCI_HV3)
#define ACW_PTYPE_MASK	(~SCO_PTYPE_MASK)

/* eSCO packet types */
#define ESCO_HV1	0x0001
#define ESCO_HV2	0x0002
#define ESCO_HV3	0x0004
#define ESCO_EV3	0x0008
#define ESCO_EV4	0x0010
#define ESCO_EV5	0x0020
#define ESCO_2EV3	0x0040
#define ESCO_3EV3	0x0080
#define ESCO_2EV5	0x0100
#define ESCO_3EV5	0x0200

#define SCO_ESCO_MASK  (ESCO_HV1 | ESCO_HV2 | ESCO_HV3)
#define EDW_ESCO_MASK  (ESCO_2EV3 | ESCO_3EV3 | ESCO_2EV5 | ESCO_3EV5)

/* ACW fwags */
#define ACW_STAWT_NO_FWUSH	0x00
#define ACW_CONT		0x01
#define ACW_STAWT		0x02
#define ACW_COMPWETE		0x03
#define ACW_ACTIVE_BCAST	0x04
#define ACW_PICO_BCAST		0x08

/* ISO PB fwags */
#define ISO_STAWT		0x00
#define ISO_CONT		0x01
#define ISO_SINGWE		0x02
#define ISO_END			0x03

/* ISO TS fwags */
#define ISO_TS			0x01

/* Baseband winks */
#define SCO_WINK	0x00
#define ACW_WINK	0x01
#define ESCO_WINK	0x02
/* Wow Enewgy winks do not have defined wink type. Use invented one */
#define WE_WINK		0x80
#define AMP_WINK	0x81
#define ISO_WINK	0x82
#define INVAWID_WINK	0xff

/* WMP featuwes */
#define WMP_3SWOT	0x01
#define WMP_5SWOT	0x02
#define WMP_ENCWYPT	0x04
#define WMP_SOFFSET	0x08
#define WMP_TACCUWACY	0x10
#define WMP_WSWITCH	0x20
#define WMP_HOWD	0x40
#define WMP_SNIFF	0x80

#define WMP_PAWK	0x01
#define WMP_WSSI	0x02
#define WMP_QUAWITY	0x04
#define WMP_SCO		0x08
#define WMP_HV2		0x10
#define WMP_HV3		0x20
#define WMP_UWAW	0x40
#define WMP_AWAW	0x80

#define WMP_CVSD	0x01
#define WMP_PSCHEME	0x02
#define WMP_PCONTWOW	0x04
#define WMP_TWANSPAWENT	0x08

#define WMP_EDW_2M		0x02
#define WMP_EDW_3M		0x04
#define WMP_WSSI_INQ	0x40
#define WMP_ESCO	0x80

#define WMP_EV4		0x01
#define WMP_EV5		0x02
#define WMP_NO_BWEDW	0x20
#define WMP_WE		0x40
#define WMP_EDW_3SWOT	0x80

#define WMP_EDW_5SWOT	0x01
#define WMP_SNIFF_SUBW	0x02
#define WMP_PAUSE_ENC	0x04
#define WMP_EDW_ESCO_2M	0x20
#define WMP_EDW_ESCO_3M	0x40
#define WMP_EDW_3S_ESCO	0x80

#define WMP_EXT_INQ	0x01
#define WMP_SIMUW_WE_BW	0x02
#define WMP_SIMPWE_PAIW	0x08
#define WMP_EWW_DATA_WEPOWTING 0x20
#define WMP_NO_FWUSH	0x40

#define WMP_WSTO	0x01
#define WMP_INQ_TX_PWW	0x02
#define WMP_EXTFEATUWES	0x80

/* Extended WMP featuwes */
#define WMP_CPB_CENTWAW		0x01
#define WMP_CPB_PEWIPHEWAW	0x02
#define WMP_SYNC_TWAIN		0x04
#define WMP_SYNC_SCAN		0x08

#define WMP_SC		0x01
#define WMP_PING	0x02

/* Host featuwes */
#define WMP_HOST_SSP		0x01
#define WMP_HOST_WE		0x02
#define WMP_HOST_WE_BWEDW	0x04
#define WMP_HOST_SC		0x08

/* WE featuwes */
#define HCI_WE_ENCWYPTION		0x01
#define HCI_WE_CONN_PAWAM_WEQ_PWOC	0x02
#define HCI_WE_PEWIPHEWAW_FEATUWES	0x08
#define HCI_WE_PING			0x10
#define HCI_WE_DATA_WEN_EXT		0x20
#define HCI_WE_WW_PWIVACY		0x40
#define HCI_WE_EXT_SCAN_POWICY		0x80
#define HCI_WE_PHY_2M			0x01
#define HCI_WE_PHY_CODED		0x08
#define HCI_WE_EXT_ADV			0x10
#define HCI_WE_PEWIODIC_ADV		0x20
#define HCI_WE_CHAN_SEW_AWG2		0x40
#define HCI_WE_CIS_CENTWAW		0x10
#define HCI_WE_CIS_PEWIPHEWAW		0x20
#define HCI_WE_ISO_BWOADCASTEW		0x40
#define HCI_WE_ISO_SYNC_WECEIVEW	0x80

/* Connection modes */
#define HCI_CM_ACTIVE	0x0000
#define HCI_CM_HOWD	0x0001
#define HCI_CM_SNIFF	0x0002
#define HCI_CM_PAWK	0x0003

/* Wink powicies */
#define HCI_WP_WSWITCH	0x0001
#define HCI_WP_HOWD	0x0002
#define HCI_WP_SNIFF	0x0004
#define HCI_WP_PAWK	0x0008

/* Wink modes */
#define HCI_WM_ACCEPT	0x8000
#define HCI_WM_MASTEW	0x0001
#define HCI_WM_AUTH	0x0002
#define HCI_WM_ENCWYPT	0x0004
#define HCI_WM_TWUSTED	0x0008
#define HCI_WM_WEWIABWE	0x0010
#define HCI_WM_SECUWE	0x0020
#define HCI_WM_FIPS	0x0040

/* Authentication types */
#define HCI_AT_NO_BONDING		0x00
#define HCI_AT_NO_BONDING_MITM		0x01
#define HCI_AT_DEDICATED_BONDING	0x02
#define HCI_AT_DEDICATED_BONDING_MITM	0x03
#define HCI_AT_GENEWAW_BONDING		0x04
#define HCI_AT_GENEWAW_BONDING_MITM	0x05

/* I/O capabiwities */
#define HCI_IO_DISPWAY_ONWY	0x00
#define HCI_IO_DISPWAY_YESNO	0x01
#define HCI_IO_KEYBOAWD_ONWY	0x02
#define HCI_IO_NO_INPUT_OUTPUT	0x03

/* Wink Key types */
#define HCI_WK_COMBINATION		0x00
#define HCI_WK_WOCAW_UNIT		0x01
#define HCI_WK_WEMOTE_UNIT		0x02
#define HCI_WK_DEBUG_COMBINATION	0x03
#define HCI_WK_UNAUTH_COMBINATION_P192	0x04
#define HCI_WK_AUTH_COMBINATION_P192	0x05
#define HCI_WK_CHANGED_COMBINATION	0x06
#define HCI_WK_UNAUTH_COMBINATION_P256	0x07
#define HCI_WK_AUTH_COMBINATION_P256	0x08

/* ---- HCI Ewwow Codes ---- */
#define HCI_EWWOW_UNKNOWN_CONN_ID	0x02
#define HCI_EWWOW_AUTH_FAIWUWE		0x05
#define HCI_EWWOW_PIN_OW_KEY_MISSING	0x06
#define HCI_EWWOW_MEMOWY_EXCEEDED	0x07
#define HCI_EWWOW_CONNECTION_TIMEOUT	0x08
#define HCI_EWWOW_WEJ_WIMITED_WESOUWCES	0x0d
#define HCI_EWWOW_WEJ_BAD_ADDW		0x0f
#define HCI_EWWOW_INVAWID_PAWAMETEWS	0x12
#define HCI_EWWOW_WEMOTE_USEW_TEWM	0x13
#define HCI_EWWOW_WEMOTE_WOW_WESOUWCES	0x14
#define HCI_EWWOW_WEMOTE_POWEW_OFF	0x15
#define HCI_EWWOW_WOCAW_HOST_TEWM	0x16
#define HCI_EWWOW_PAIWING_NOT_AWWOWED	0x18
#define HCI_EWWOW_INVAWID_WW_PAWAMS	0x1e
#define HCI_EWWOW_UNSPECIFIED		0x1f
#define HCI_EWWOW_ADVEWTISING_TIMEOUT	0x3c
#define HCI_EWWOW_CANCEWWED_BY_HOST	0x44

/* Fwow contwow modes */
#define HCI_FWOW_CTW_MODE_PACKET_BASED	0x00
#define HCI_FWOW_CTW_MODE_BWOCK_BASED	0x01

/* The cowe spec defines 127 as the "not avaiwabwe" vawue */
#define HCI_TX_POWEW_INVAWID	127
#define HCI_WSSI_INVAWID	127

#define HCI_SYNC_HANDWE_INVAWID	0xffff

#define HCI_WOWE_MASTEW		0x00
#define HCI_WOWE_SWAVE		0x01

/* Extended Inquiwy Wesponse fiewd types */
#define EIW_FWAGS		0x01 /* fwags */
#define EIW_UUID16_SOME		0x02 /* 16-bit UUID, mowe avaiwabwe */
#define EIW_UUID16_AWW		0x03 /* 16-bit UUID, aww wisted */
#define EIW_UUID32_SOME		0x04 /* 32-bit UUID, mowe avaiwabwe */
#define EIW_UUID32_AWW		0x05 /* 32-bit UUID, aww wisted */
#define EIW_UUID128_SOME	0x06 /* 128-bit UUID, mowe avaiwabwe */
#define EIW_UUID128_AWW		0x07 /* 128-bit UUID, aww wisted */
#define EIW_NAME_SHOWT		0x08 /* showtened wocaw name */
#define EIW_NAME_COMPWETE	0x09 /* compwete wocaw name */
#define EIW_TX_POWEW		0x0A /* twansmit powew wevew */
#define EIW_CWASS_OF_DEV	0x0D /* Cwass of Device */
#define EIW_SSP_HASH_C192	0x0E /* Simpwe Paiwing Hash C-192 */
#define EIW_SSP_WAND_W192	0x0F /* Simpwe Paiwing Wandomizew W-192 */
#define EIW_DEVICE_ID		0x10 /* device ID */
#define EIW_APPEAWANCE		0x19 /* Device appeawance */
#define EIW_SEWVICE_DATA	0x16 /* Sewvice Data */
#define EIW_WE_BDADDW		0x1B /* WE Bwuetooth device addwess */
#define EIW_WE_WOWE		0x1C /* WE wowe */
#define EIW_SSP_HASH_C256	0x1D /* Simpwe Paiwing Hash C-256 */
#define EIW_SSP_WAND_W256	0x1E /* Simpwe Paiwing Wand W-256 */
#define EIW_WE_SC_CONFIWM	0x22 /* WE SC Confiwmation Vawue */
#define EIW_WE_SC_WANDOM	0x23 /* WE SC Wandom Vawue */

/* Wow Enewgy Advewtising Fwags */
#define WE_AD_WIMITED		0x01 /* Wimited Discovewabwe */
#define WE_AD_GENEWAW		0x02 /* Genewaw Discovewabwe */
#define WE_AD_NO_BWEDW		0x04 /* BW/EDW not suppowted */
#define WE_AD_SIM_WE_BWEDW_CTWW	0x08 /* Simuwtaneous WE & BW/EDW Contwowwew */
#define WE_AD_SIM_WE_BWEDW_HOST	0x10 /* Simuwtaneous WE & BW/EDW Host */

/* -----  HCI Commands ---- */
#define HCI_OP_NOP			0x0000

#define HCI_OP_INQUIWY			0x0401
stwuct hci_cp_inquiwy {
	__u8     wap[3];
	__u8     wength;
	__u8     num_wsp;
} __packed;

#define HCI_OP_INQUIWY_CANCEW		0x0402

#define HCI_OP_PEWIODIC_INQ		0x0403

#define HCI_OP_EXIT_PEWIODIC_INQ	0x0404

#define HCI_OP_CWEATE_CONN		0x0405
stwuct hci_cp_cweate_conn {
	bdaddw_t bdaddw;
	__we16   pkt_type;
	__u8     pscan_wep_mode;
	__u8     pscan_mode;
	__we16   cwock_offset;
	__u8     wowe_switch;
} __packed;

#define HCI_OP_DISCONNECT		0x0406
stwuct hci_cp_disconnect {
	__we16   handwe;
	__u8     weason;
} __packed;

#define HCI_OP_ADD_SCO			0x0407
stwuct hci_cp_add_sco {
	__we16   handwe;
	__we16   pkt_type;
} __packed;

#define HCI_OP_CWEATE_CONN_CANCEW	0x0408
stwuct hci_cp_cweate_conn_cancew {
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_ACCEPT_CONN_WEQ		0x0409
stwuct hci_cp_accept_conn_weq {
	bdaddw_t bdaddw;
	__u8     wowe;
} __packed;

#define HCI_OP_WEJECT_CONN_WEQ		0x040a
stwuct hci_cp_weject_conn_weq {
	bdaddw_t bdaddw;
	__u8     weason;
} __packed;

#define HCI_OP_WINK_KEY_WEPWY		0x040b
stwuct hci_cp_wink_key_wepwy {
	bdaddw_t bdaddw;
	__u8     wink_key[HCI_WINK_KEY_SIZE];
} __packed;

#define HCI_OP_WINK_KEY_NEG_WEPWY	0x040c
stwuct hci_cp_wink_key_neg_wepwy {
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_PIN_CODE_WEPWY		0x040d
stwuct hci_cp_pin_code_wepwy {
	bdaddw_t bdaddw;
	__u8     pin_wen;
	__u8     pin_code[16];
} __packed;
stwuct hci_wp_pin_code_wepwy {
	__u8     status;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_PIN_CODE_NEG_WEPWY	0x040e
stwuct hci_cp_pin_code_neg_wepwy {
	bdaddw_t bdaddw;
} __packed;
stwuct hci_wp_pin_code_neg_wepwy {
	__u8     status;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_CHANGE_CONN_PTYPE	0x040f
stwuct hci_cp_change_conn_ptype {
	__we16   handwe;
	__we16   pkt_type;
} __packed;

#define HCI_OP_AUTH_WEQUESTED		0x0411
stwuct hci_cp_auth_wequested {
	__we16   handwe;
} __packed;

#define HCI_OP_SET_CONN_ENCWYPT		0x0413
stwuct hci_cp_set_conn_encwypt {
	__we16   handwe;
	__u8     encwypt;
} __packed;

#define HCI_OP_CHANGE_CONN_WINK_KEY	0x0415
stwuct hci_cp_change_conn_wink_key {
	__we16   handwe;
} __packed;

#define HCI_OP_WEMOTE_NAME_WEQ		0x0419
stwuct hci_cp_wemote_name_weq {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
	__u8     pscan_mode;
	__we16   cwock_offset;
} __packed;

#define HCI_OP_WEMOTE_NAME_WEQ_CANCEW	0x041a
stwuct hci_cp_wemote_name_weq_cancew {
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_WEAD_WEMOTE_FEATUWES	0x041b
stwuct hci_cp_wead_wemote_featuwes {
	__we16   handwe;
} __packed;

#define HCI_OP_WEAD_WEMOTE_EXT_FEATUWES	0x041c
stwuct hci_cp_wead_wemote_ext_featuwes {
	__we16   handwe;
	__u8     page;
} __packed;

#define HCI_OP_WEAD_WEMOTE_VEWSION	0x041d
stwuct hci_cp_wead_wemote_vewsion {
	__we16   handwe;
} __packed;

#define HCI_OP_WEAD_CWOCK_OFFSET	0x041f
stwuct hci_cp_wead_cwock_offset {
	__we16   handwe;
} __packed;

#define HCI_OP_SETUP_SYNC_CONN		0x0428
stwuct hci_cp_setup_sync_conn {
	__we16   handwe;
	__we32   tx_bandwidth;
	__we32   wx_bandwidth;
	__we16   max_watency;
	__we16   voice_setting;
	__u8     wetwans_effowt;
	__we16   pkt_type;
} __packed;

#define HCI_OP_ACCEPT_SYNC_CONN_WEQ	0x0429
stwuct hci_cp_accept_sync_conn_weq {
	bdaddw_t bdaddw;
	__we32   tx_bandwidth;
	__we32   wx_bandwidth;
	__we16   max_watency;
	__we16   content_fowmat;
	__u8     wetwans_effowt;
	__we16   pkt_type;
} __packed;

#define HCI_OP_WEJECT_SYNC_CONN_WEQ	0x042a
stwuct hci_cp_weject_sync_conn_weq {
	bdaddw_t bdaddw;
	__u8     weason;
} __packed;

#define HCI_OP_IO_CAPABIWITY_WEPWY	0x042b
stwuct hci_cp_io_capabiwity_wepwy {
	bdaddw_t bdaddw;
	__u8     capabiwity;
	__u8     oob_data;
	__u8     authentication;
} __packed;

#define HCI_OP_USEW_CONFIWM_WEPWY		0x042c
stwuct hci_cp_usew_confiwm_wepwy {
	bdaddw_t bdaddw;
} __packed;
stwuct hci_wp_usew_confiwm_wepwy {
	__u8     status;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_USEW_CONFIWM_NEG_WEPWY	0x042d

#define HCI_OP_USEW_PASSKEY_WEPWY		0x042e
stwuct hci_cp_usew_passkey_wepwy {
	bdaddw_t bdaddw;
	__we32	passkey;
} __packed;

#define HCI_OP_USEW_PASSKEY_NEG_WEPWY	0x042f

#define HCI_OP_WEMOTE_OOB_DATA_WEPWY	0x0430
stwuct hci_cp_wemote_oob_data_wepwy {
	bdaddw_t bdaddw;
	__u8     hash[16];
	__u8     wand[16];
} __packed;

#define HCI_OP_WEMOTE_OOB_DATA_NEG_WEPWY	0x0433
stwuct hci_cp_wemote_oob_data_neg_wepwy {
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_IO_CAPABIWITY_NEG_WEPWY	0x0434
stwuct hci_cp_io_capabiwity_neg_wepwy {
	bdaddw_t bdaddw;
	__u8     weason;
} __packed;

#define HCI_OP_CWEATE_PHY_WINK		0x0435
stwuct hci_cp_cweate_phy_wink {
	__u8     phy_handwe;
	__u8     key_wen;
	__u8     key_type;
	__u8     key[HCI_AMP_WINK_KEY_SIZE];
} __packed;

#define HCI_OP_ACCEPT_PHY_WINK		0x0436
stwuct hci_cp_accept_phy_wink {
	__u8     phy_handwe;
	__u8     key_wen;
	__u8     key_type;
	__u8     key[HCI_AMP_WINK_KEY_SIZE];
} __packed;

#define HCI_OP_DISCONN_PHY_WINK		0x0437
stwuct hci_cp_disconn_phy_wink {
	__u8     phy_handwe;
	__u8     weason;
} __packed;

stwuct ext_fwow_spec {
	__u8       id;
	__u8       stype;
	__we16     msdu;
	__we32     sdu_itime;
	__we32     acc_wat;
	__we32     fwush_to;
} __packed;

#define HCI_OP_CWEATE_WOGICAW_WINK	0x0438
#define HCI_OP_ACCEPT_WOGICAW_WINK	0x0439
stwuct hci_cp_cweate_accept_wogicaw_wink {
	__u8                  phy_handwe;
	stwuct ext_fwow_spec  tx_fwow_spec;
	stwuct ext_fwow_spec  wx_fwow_spec;
} __packed;

#define HCI_OP_DISCONN_WOGICAW_WINK	0x043a
stwuct hci_cp_disconn_wogicaw_wink {
	__we16   wog_handwe;
} __packed;

#define HCI_OP_WOGICAW_WINK_CANCEW	0x043b
stwuct hci_cp_wogicaw_wink_cancew {
	__u8     phy_handwe;
	__u8     fwow_spec_id;
} __packed;

#define HCI_OP_ENHANCED_SETUP_SYNC_CONN		0x043d
stwuct hci_coding_fowmat {
	__u8	id;
	__we16	cid;
	__we16	vid;
} __packed;

stwuct hci_cp_enhanced_setup_sync_conn {
	__we16   handwe;
	__we32   tx_bandwidth;
	__we32   wx_bandwidth;
	stwuct	 hci_coding_fowmat tx_coding_fowmat;
	stwuct	 hci_coding_fowmat wx_coding_fowmat;
	__we16	 tx_codec_fwame_size;
	__we16	 wx_codec_fwame_size;
	__we32	 in_bandwidth;
	__we32	 out_bandwidth;
	stwuct	 hci_coding_fowmat in_coding_fowmat;
	stwuct	 hci_coding_fowmat out_coding_fowmat;
	__we16   in_coded_data_size;
	__we16	 out_coded_data_size;
	__u8	 in_pcm_data_fowmat;
	__u8	 out_pcm_data_fowmat;
	__u8	 in_pcm_sampwe_paywoad_msb_pos;
	__u8	 out_pcm_sampwe_paywoad_msb_pos;
	__u8	 in_data_path;
	__u8	 out_data_path;
	__u8	 in_twanspowt_unit_size;
	__u8	 out_twanspowt_unit_size;
	__we16   max_watency;
	__we16   pkt_type;
	__u8     wetwans_effowt;
} __packed;

stwuct hci_wp_wogicaw_wink_cancew {
	__u8     status;
	__u8     phy_handwe;
	__u8     fwow_spec_id;
} __packed;

#define HCI_OP_SET_CPB			0x0441
stwuct hci_cp_set_cpb {
	__u8	enabwe;
	__u8	wt_addw;
	__u8	wpo_awwowed;
	__we16	packet_type;
	__we16	intewvaw_min;
	__we16	intewvaw_max;
	__we16	cpb_sv_tout;
} __packed;
stwuct hci_wp_set_cpb {
	__u8	status;
	__u8	wt_addw;
	__we16	intewvaw;
} __packed;

#define HCI_OP_STAWT_SYNC_TWAIN		0x0443

#define HCI_OP_WEMOTE_OOB_EXT_DATA_WEPWY	0x0445
stwuct hci_cp_wemote_oob_ext_data_wepwy {
	bdaddw_t bdaddw;
	__u8     hash192[16];
	__u8     wand192[16];
	__u8     hash256[16];
	__u8     wand256[16];
} __packed;

#define HCI_OP_SNIFF_MODE		0x0803
stwuct hci_cp_sniff_mode {
	__we16   handwe;
	__we16   max_intewvaw;
	__we16   min_intewvaw;
	__we16   attempt;
	__we16   timeout;
} __packed;

#define HCI_OP_EXIT_SNIFF_MODE		0x0804
stwuct hci_cp_exit_sniff_mode {
	__we16   handwe;
} __packed;

#define HCI_OP_WOWE_DISCOVEWY		0x0809
stwuct hci_cp_wowe_discovewy {
	__we16   handwe;
} __packed;
stwuct hci_wp_wowe_discovewy {
	__u8     status;
	__we16   handwe;
	__u8     wowe;
} __packed;

#define HCI_OP_SWITCH_WOWE		0x080b
stwuct hci_cp_switch_wowe {
	bdaddw_t bdaddw;
	__u8     wowe;
} __packed;

#define HCI_OP_WEAD_WINK_POWICY		0x080c
stwuct hci_cp_wead_wink_powicy {
	__we16   handwe;
} __packed;
stwuct hci_wp_wead_wink_powicy {
	__u8     status;
	__we16   handwe;
	__we16   powicy;
} __packed;

#define HCI_OP_WWITE_WINK_POWICY	0x080d
stwuct hci_cp_wwite_wink_powicy {
	__we16   handwe;
	__we16   powicy;
} __packed;
stwuct hci_wp_wwite_wink_powicy {
	__u8     status;
	__we16   handwe;
} __packed;

#define HCI_OP_WEAD_DEF_WINK_POWICY	0x080e
stwuct hci_wp_wead_def_wink_powicy {
	__u8     status;
	__we16   powicy;
} __packed;

#define HCI_OP_WWITE_DEF_WINK_POWICY	0x080f
stwuct hci_cp_wwite_def_wink_powicy {
	__we16   powicy;
} __packed;

#define HCI_OP_SNIFF_SUBWATE		0x0811
stwuct hci_cp_sniff_subwate {
	__we16   handwe;
	__we16   max_watency;
	__we16   min_wemote_timeout;
	__we16   min_wocaw_timeout;
} __packed;

#define HCI_OP_SET_EVENT_MASK		0x0c01

#define HCI_OP_WESET			0x0c03

#define HCI_OP_SET_EVENT_FWT		0x0c05
#define HCI_SET_EVENT_FWT_SIZE		9
stwuct hci_cp_set_event_fiwtew {
	__u8		fwt_type;
	__u8		cond_type;
	stwuct {
		bdaddw_t bdaddw;
		__u8 auto_accept;
	} __packed	addw_conn_fwt;
} __packed;

/* Fiwtew types */
#define HCI_FWT_CWEAW_AWW	0x00
#define HCI_FWT_INQ_WESUWT	0x01
#define HCI_FWT_CONN_SETUP	0x02

/* CONN_SETUP Condition types */
#define HCI_CONN_SETUP_AWWOW_AWW	0x00
#define HCI_CONN_SETUP_AWWOW_CWASS	0x01
#define HCI_CONN_SETUP_AWWOW_BDADDW	0x02

/* CONN_SETUP Conditions */
#define HCI_CONN_SETUP_AUTO_OFF		0x01
#define HCI_CONN_SETUP_AUTO_ON		0x02
#define HCI_CONN_SETUP_AUTO_ON_WITH_WS	0x03

#define HCI_OP_WEAD_STOWED_WINK_KEY	0x0c0d
stwuct hci_cp_wead_stowed_wink_key {
	bdaddw_t bdaddw;
	__u8     wead_aww;
} __packed;
stwuct hci_wp_wead_stowed_wink_key {
	__u8     status;
	__we16   max_keys;
	__we16   num_keys;
} __packed;

#define HCI_OP_DEWETE_STOWED_WINK_KEY	0x0c12
stwuct hci_cp_dewete_stowed_wink_key {
	bdaddw_t bdaddw;
	__u8     dewete_aww;
} __packed;
stwuct hci_wp_dewete_stowed_wink_key {
	__u8     status;
	__we16   num_keys;
} __packed;

#define HCI_MAX_NAME_WENGTH		248

#define HCI_OP_WWITE_WOCAW_NAME		0x0c13
stwuct hci_cp_wwite_wocaw_name {
	__u8     name[HCI_MAX_NAME_WENGTH];
} __packed;

#define HCI_OP_WEAD_WOCAW_NAME		0x0c14
stwuct hci_wp_wead_wocaw_name {
	__u8     status;
	__u8     name[HCI_MAX_NAME_WENGTH];
} __packed;

#define HCI_OP_WWITE_CA_TIMEOUT		0x0c16

#define HCI_OP_WWITE_PG_TIMEOUT		0x0c18

#define HCI_OP_WWITE_SCAN_ENABWE	0x0c1a
	#define SCAN_DISABWED		0x00
	#define SCAN_INQUIWY		0x01
	#define SCAN_PAGE		0x02

#define HCI_OP_WEAD_AUTH_ENABWE		0x0c1f

#define HCI_OP_WWITE_AUTH_ENABWE	0x0c20
	#define AUTH_DISABWED		0x00
	#define AUTH_ENABWED		0x01

#define HCI_OP_WEAD_ENCWYPT_MODE	0x0c21

#define HCI_OP_WWITE_ENCWYPT_MODE	0x0c22
	#define ENCWYPT_DISABWED	0x00
	#define ENCWYPT_P2P		0x01
	#define ENCWYPT_BOTH		0x02

#define HCI_OP_WEAD_CWASS_OF_DEV	0x0c23
stwuct hci_wp_wead_cwass_of_dev {
	__u8     status;
	__u8     dev_cwass[3];
} __packed;

#define HCI_OP_WWITE_CWASS_OF_DEV	0x0c24
stwuct hci_cp_wwite_cwass_of_dev {
	__u8     dev_cwass[3];
} __packed;

#define HCI_OP_WEAD_VOICE_SETTING	0x0c25
stwuct hci_wp_wead_voice_setting {
	__u8     status;
	__we16   voice_setting;
} __packed;

#define HCI_OP_WWITE_VOICE_SETTING	0x0c26
stwuct hci_cp_wwite_voice_setting {
	__we16   voice_setting;
} __packed;

#define HCI_OP_HOST_BUFFEW_SIZE		0x0c33
stwuct hci_cp_host_buffew_size {
	__we16   acw_mtu;
	__u8     sco_mtu;
	__we16   acw_max_pkt;
	__we16   sco_max_pkt;
} __packed;

#define HCI_OP_WEAD_NUM_SUPPOWTED_IAC	0x0c38
stwuct hci_wp_wead_num_suppowted_iac {
	__u8	status;
	__u8	num_iac;
} __packed;

#define HCI_OP_WEAD_CUWWENT_IAC_WAP	0x0c39

#define HCI_OP_WWITE_CUWWENT_IAC_WAP	0x0c3a
stwuct hci_cp_wwite_cuwwent_iac_wap {
	__u8	num_iac;
	__u8	iac_wap[6];
} __packed;

#define HCI_OP_WWITE_INQUIWY_MODE	0x0c45

#define HCI_MAX_EIW_WENGTH		240

#define HCI_OP_WWITE_EIW		0x0c52
stwuct hci_cp_wwite_eiw {
	__u8	fec;
	__u8	data[HCI_MAX_EIW_WENGTH];
} __packed;

#define HCI_OP_WEAD_SSP_MODE		0x0c55
stwuct hci_wp_wead_ssp_mode {
	__u8     status;
	__u8     mode;
} __packed;

#define HCI_OP_WWITE_SSP_MODE		0x0c56
stwuct hci_cp_wwite_ssp_mode {
	__u8     mode;
} __packed;

#define HCI_OP_WEAD_WOCAW_OOB_DATA		0x0c57
stwuct hci_wp_wead_wocaw_oob_data {
	__u8     status;
	__u8     hash[16];
	__u8     wand[16];
} __packed;

#define HCI_OP_WEAD_INQ_WSP_TX_POWEW	0x0c58
stwuct hci_wp_wead_inq_wsp_tx_powew {
	__u8     status;
	__s8     tx_powew;
} __packed;

#define HCI_OP_WEAD_DEF_EWW_DATA_WEPOWTING	0x0c5a
	#define EWW_DATA_WEPOWTING_DISABWED	0x00
	#define EWW_DATA_WEPOWTING_ENABWED	0x01
stwuct hci_wp_wead_def_eww_data_wepowting {
	__u8     status;
	__u8     eww_data_wepowting;
} __packed;

#define HCI_OP_WWITE_DEF_EWW_DATA_WEPOWTING	0x0c5b
stwuct hci_cp_wwite_def_eww_data_wepowting {
	__u8     eww_data_wepowting;
} __packed;

#define HCI_OP_SET_EVENT_MASK_PAGE_2	0x0c63

#define HCI_OP_WEAD_WOCATION_DATA	0x0c64

#define HCI_OP_WEAD_FWOW_CONTWOW_MODE	0x0c66
stwuct hci_wp_wead_fwow_contwow_mode {
	__u8     status;
	__u8     mode;
} __packed;

#define HCI_OP_WWITE_WE_HOST_SUPPOWTED	0x0c6d
stwuct hci_cp_wwite_we_host_suppowted {
	__u8	we;
	__u8	simuw;
} __packed;

#define HCI_OP_SET_WESEWVED_WT_ADDW	0x0c74
stwuct hci_cp_set_wesewved_wt_addw {
	__u8	wt_addw;
} __packed;
stwuct hci_wp_set_wesewved_wt_addw {
	__u8	status;
	__u8	wt_addw;
} __packed;

#define HCI_OP_DEWETE_WESEWVED_WT_ADDW	0x0c75
stwuct hci_cp_dewete_wesewved_wt_addw {
	__u8	wt_addw;
} __packed;
stwuct hci_wp_dewete_wesewved_wt_addw {
	__u8	status;
	__u8	wt_addw;
} __packed;

#define HCI_OP_SET_CPB_DATA		0x0c76
stwuct hci_cp_set_cpb_data {
	__u8	wt_addw;
	__u8	fwagment;
	__u8	data_wength;
	__u8	data[HCI_MAX_CPB_DATA_SIZE];
} __packed;
stwuct hci_wp_set_cpb_data {
	__u8	status;
	__u8	wt_addw;
} __packed;

#define HCI_OP_WEAD_SYNC_TWAIN_PAWAMS	0x0c77

#define HCI_OP_WWITE_SYNC_TWAIN_PAWAMS	0x0c78
stwuct hci_cp_wwite_sync_twain_pawams {
	__we16	intewvaw_min;
	__we16	intewvaw_max;
	__we32	sync_twain_tout;
	__u8	sewvice_data;
} __packed;
stwuct hci_wp_wwite_sync_twain_pawams {
	__u8	status;
	__we16	sync_twain_int;
} __packed;

#define HCI_OP_WEAD_SC_SUPPOWT		0x0c79
stwuct hci_wp_wead_sc_suppowt {
	__u8	status;
	__u8	suppowt;
} __packed;

#define HCI_OP_WWITE_SC_SUPPOWT		0x0c7a
stwuct hci_cp_wwite_sc_suppowt {
	__u8	suppowt;
} __packed;

#define HCI_OP_WEAD_AUTH_PAYWOAD_TO    0x0c7b
stwuct hci_cp_wead_auth_paywoad_to {
	__we16  handwe;
} __packed;
stwuct hci_wp_wead_auth_paywoad_to {
	__u8    status;
	__we16  handwe;
	__we16  timeout;
} __packed;

#define HCI_OP_WWITE_AUTH_PAYWOAD_TO    0x0c7c
stwuct hci_cp_wwite_auth_paywoad_to {
	__we16  handwe;
	__we16  timeout;
} __packed;
stwuct hci_wp_wwite_auth_paywoad_to {
	__u8    status;
	__we16  handwe;
} __packed;

#define HCI_OP_WEAD_WOCAW_OOB_EXT_DATA	0x0c7d
stwuct hci_wp_wead_wocaw_oob_ext_data {
	__u8     status;
	__u8     hash192[16];
	__u8     wand192[16];
	__u8     hash256[16];
	__u8     wand256[16];
} __packed;

#define HCI_CONFIGUWE_DATA_PATH	0x0c83
stwuct hci_op_configuwe_data_path {
	__u8	diwection;
	__u8	data_path_id;
	__u8	vnd_wen;
	__u8	vnd_data[];
} __packed;

#define HCI_OP_WEAD_WOCAW_VEWSION	0x1001
stwuct hci_wp_wead_wocaw_vewsion {
	__u8     status;
	__u8     hci_vew;
	__we16   hci_wev;
	__u8     wmp_vew;
	__we16   manufactuwew;
	__we16   wmp_subvew;
} __packed;

#define HCI_OP_WEAD_WOCAW_COMMANDS	0x1002
stwuct hci_wp_wead_wocaw_commands {
	__u8     status;
	__u8     commands[64];
} __packed;

#define HCI_OP_WEAD_WOCAW_FEATUWES	0x1003
stwuct hci_wp_wead_wocaw_featuwes {
	__u8     status;
	__u8     featuwes[8];
} __packed;

#define HCI_OP_WEAD_WOCAW_EXT_FEATUWES	0x1004
stwuct hci_cp_wead_wocaw_ext_featuwes {
	__u8     page;
} __packed;
stwuct hci_wp_wead_wocaw_ext_featuwes {
	__u8     status;
	__u8     page;
	__u8     max_page;
	__u8     featuwes[8];
} __packed;

#define HCI_OP_WEAD_BUFFEW_SIZE		0x1005
stwuct hci_wp_wead_buffew_size {
	__u8     status;
	__we16   acw_mtu;
	__u8     sco_mtu;
	__we16   acw_max_pkt;
	__we16   sco_max_pkt;
} __packed;

#define HCI_OP_WEAD_BD_ADDW		0x1009
stwuct hci_wp_wead_bd_addw {
	__u8     status;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_WEAD_DATA_BWOCK_SIZE	0x100a
stwuct hci_wp_wead_data_bwock_size {
	__u8     status;
	__we16   max_acw_wen;
	__we16   bwock_wen;
	__we16   num_bwocks;
} __packed;

#define HCI_OP_WEAD_WOCAW_CODECS	0x100b
stwuct hci_std_codecs {
	__u8	num;
	__u8	codec[];
} __packed;

stwuct hci_vnd_codec {
	/* company id */
	__we16	cid;
	/* vendow codec id */
	__we16	vid;
} __packed;

stwuct hci_vnd_codecs {
	__u8	num;
	stwuct hci_vnd_codec codec[];
} __packed;

stwuct hci_wp_wead_wocaw_suppowted_codecs {
	__u8	status;
	stwuct hci_std_codecs std_codecs;
	stwuct hci_vnd_codecs vnd_codecs;
} __packed;

#define HCI_OP_WEAD_WOCAW_PAIWING_OPTS	0x100c
stwuct hci_wp_wead_wocaw_paiwing_opts {
	__u8     status;
	__u8     paiwing_opts;
	__u8     max_key_size;
} __packed;

#define HCI_OP_WEAD_WOCAW_CODECS_V2	0x100d
stwuct hci_std_codec_v2 {
	__u8	id;
	__u8	twanspowt;
} __packed;

stwuct hci_std_codecs_v2 {
	__u8	num;
	stwuct hci_std_codec_v2 codec[];
} __packed;

stwuct hci_vnd_codec_v2 {
	__we16	cid;
	__we16	vid;
	__u8	twanspowt;
} __packed;

stwuct hci_vnd_codecs_v2 {
	__u8	num;
	stwuct hci_vnd_codec_v2 codec[];
} __packed;

stwuct hci_wp_wead_wocaw_suppowted_codecs_v2 {
	__u8	status;
	stwuct hci_std_codecs_v2 std_codecs;
	stwuct hci_vnd_codecs_v2 vendow_codecs;
} __packed;

#define HCI_OP_WEAD_WOCAW_CODEC_CAPS	0x100e
stwuct hci_op_wead_wocaw_codec_caps {
	__u8	id;
	__we16	cid;
	__we16	vid;
	__u8	twanspowt;
	__u8	diwection;
} __packed;

stwuct hci_codec_caps {
	__u8	wen;
	__u8	data[];
} __packed;

stwuct hci_wp_wead_wocaw_codec_caps {
	__u8	status;
	__u8	num_caps;
} __packed;

#define HCI_OP_WEAD_PAGE_SCAN_ACTIVITY	0x0c1b
stwuct hci_wp_wead_page_scan_activity {
	__u8     status;
	__we16   intewvaw;
	__we16   window;
} __packed;

#define HCI_OP_WWITE_PAGE_SCAN_ACTIVITY	0x0c1c
stwuct hci_cp_wwite_page_scan_activity {
	__we16   intewvaw;
	__we16   window;
} __packed;

#define HCI_OP_WEAD_TX_POWEW		0x0c2d
stwuct hci_cp_wead_tx_powew {
	__we16   handwe;
	__u8     type;
} __packed;
stwuct hci_wp_wead_tx_powew {
	__u8     status;
	__we16   handwe;
	__s8     tx_powew;
} __packed;

#define HCI_OP_WEAD_PAGE_SCAN_TYPE	0x0c46
stwuct hci_wp_wead_page_scan_type {
	__u8     status;
	__u8     type;
} __packed;

#define HCI_OP_WWITE_PAGE_SCAN_TYPE	0x0c47
	#define PAGE_SCAN_TYPE_STANDAWD		0x00
	#define PAGE_SCAN_TYPE_INTEWWACED	0x01

#define HCI_OP_WEAD_WSSI		0x1405
stwuct hci_cp_wead_wssi {
	__we16   handwe;
} __packed;
stwuct hci_wp_wead_wssi {
	__u8     status;
	__we16   handwe;
	__s8     wssi;
} __packed;

#define HCI_OP_WEAD_CWOCK		0x1407
stwuct hci_cp_wead_cwock {
	__we16   handwe;
	__u8     which;
} __packed;
stwuct hci_wp_wead_cwock {
	__u8     status;
	__we16   handwe;
	__we32   cwock;
	__we16   accuwacy;
} __packed;

#define HCI_OP_WEAD_ENC_KEY_SIZE	0x1408
stwuct hci_cp_wead_enc_key_size {
	__we16   handwe;
} __packed;
stwuct hci_wp_wead_enc_key_size {
	__u8     status;
	__we16   handwe;
	__u8     key_size;
} __packed;

#define HCI_OP_WEAD_WOCAW_AMP_INFO	0x1409
stwuct hci_wp_wead_wocaw_amp_info {
	__u8     status;
	__u8     amp_status;
	__we32   totaw_bw;
	__we32   max_bw;
	__we32   min_watency;
	__we32   max_pdu;
	__u8     amp_type;
	__we16   paw_cap;
	__we16   max_assoc_size;
	__we32   max_fwush_to;
	__we32   be_fwush_to;
} __packed;

#define HCI_OP_WEAD_WOCAW_AMP_ASSOC	0x140a
stwuct hci_cp_wead_wocaw_amp_assoc {
	__u8     phy_handwe;
	__we16   wen_so_faw;
	__we16   max_wen;
} __packed;
stwuct hci_wp_wead_wocaw_amp_assoc {
	__u8     status;
	__u8     phy_handwe;
	__we16   wem_wen;
	__u8     fwag[];
} __packed;

#define HCI_OP_WWITE_WEMOTE_AMP_ASSOC	0x140b
stwuct hci_cp_wwite_wemote_amp_assoc {
	__u8     phy_handwe;
	__we16   wen_so_faw;
	__we16   wem_wen;
	__u8     fwag[];
} __packed;
stwuct hci_wp_wwite_wemote_amp_assoc {
	__u8     status;
	__u8     phy_handwe;
} __packed;

#define HCI_OP_GET_MWS_TWANSPOWT_CONFIG	0x140c

#define HCI_OP_ENABWE_DUT_MODE		0x1803

#define HCI_OP_WWITE_SSP_DEBUG_MODE	0x1804

#define HCI_OP_WE_SET_EVENT_MASK	0x2001
stwuct hci_cp_we_set_event_mask {
	__u8     mask[8];
} __packed;

#define HCI_OP_WE_WEAD_BUFFEW_SIZE	0x2002
stwuct hci_wp_we_wead_buffew_size {
	__u8     status;
	__we16   we_mtu;
	__u8     we_max_pkt;
} __packed;

#define HCI_OP_WE_WEAD_WOCAW_FEATUWES	0x2003
stwuct hci_wp_we_wead_wocaw_featuwes {
	__u8     status;
	__u8     featuwes[8];
} __packed;

#define HCI_OP_WE_SET_WANDOM_ADDW	0x2005

#define HCI_OP_WE_SET_ADV_PAWAM		0x2006
stwuct hci_cp_we_set_adv_pawam {
	__we16   min_intewvaw;
	__we16   max_intewvaw;
	__u8     type;
	__u8     own_addwess_type;
	__u8     diwect_addw_type;
	bdaddw_t diwect_addw;
	__u8     channew_map;
	__u8     fiwtew_powicy;
} __packed;

#define HCI_OP_WE_WEAD_ADV_TX_POWEW	0x2007
stwuct hci_wp_we_wead_adv_tx_powew {
	__u8	status;
	__s8	tx_powew;
} __packed;

#define HCI_MAX_AD_WENGTH		31

#define HCI_OP_WE_SET_ADV_DATA		0x2008
stwuct hci_cp_we_set_adv_data {
	__u8	wength;
	__u8	data[HCI_MAX_AD_WENGTH];
} __packed;

#define HCI_OP_WE_SET_SCAN_WSP_DATA	0x2009
stwuct hci_cp_we_set_scan_wsp_data {
	__u8	wength;
	__u8	data[HCI_MAX_AD_WENGTH];
} __packed;

#define HCI_OP_WE_SET_ADV_ENABWE	0x200a

#define WE_SCAN_PASSIVE			0x00
#define WE_SCAN_ACTIVE			0x01

#define HCI_OP_WE_SET_SCAN_PAWAM	0x200b
stwuct hci_cp_we_set_scan_pawam {
	__u8    type;
	__we16  intewvaw;
	__we16  window;
	__u8    own_addwess_type;
	__u8    fiwtew_powicy;
} __packed;

#define WE_SCAN_DISABWE			0x00
#define WE_SCAN_ENABWE			0x01
#define WE_SCAN_FIWTEW_DUP_DISABWE	0x00
#define WE_SCAN_FIWTEW_DUP_ENABWE	0x01

#define HCI_OP_WE_SET_SCAN_ENABWE	0x200c
stwuct hci_cp_we_set_scan_enabwe {
	__u8     enabwe;
	__u8     fiwtew_dup;
} __packed;

#define HCI_WE_USE_PEEW_ADDW		0x00
#define HCI_WE_USE_ACCEPT_WIST		0x01

#define HCI_OP_WE_CWEATE_CONN		0x200d
stwuct hci_cp_we_cweate_conn {
	__we16   scan_intewvaw;
	__we16   scan_window;
	__u8     fiwtew_powicy;
	__u8     peew_addw_type;
	bdaddw_t peew_addw;
	__u8     own_addwess_type;
	__we16   conn_intewvaw_min;
	__we16   conn_intewvaw_max;
	__we16   conn_watency;
	__we16   supewvision_timeout;
	__we16   min_ce_wen;
	__we16   max_ce_wen;
} __packed;

#define HCI_OP_WE_CWEATE_CONN_CANCEW	0x200e

#define HCI_OP_WE_WEAD_ACCEPT_WIST_SIZE	0x200f
stwuct hci_wp_we_wead_accept_wist_size {
	__u8	status;
	__u8	size;
} __packed;

#define HCI_OP_WE_CWEAW_ACCEPT_WIST	0x2010

#define HCI_OP_WE_ADD_TO_ACCEPT_WIST	0x2011
stwuct hci_cp_we_add_to_accept_wist {
	__u8     bdaddw_type;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_WE_DEW_FWOM_ACCEPT_WIST	0x2012
stwuct hci_cp_we_dew_fwom_accept_wist {
	__u8     bdaddw_type;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_WE_CONN_UPDATE		0x2013
stwuct hci_cp_we_conn_update {
	__we16   handwe;
	__we16   conn_intewvaw_min;
	__we16   conn_intewvaw_max;
	__we16   conn_watency;
	__we16   supewvision_timeout;
	__we16   min_ce_wen;
	__we16   max_ce_wen;
} __packed;

#define HCI_OP_WE_WEAD_WEMOTE_FEATUWES	0x2016
stwuct hci_cp_we_wead_wemote_featuwes {
	__we16	 handwe;
} __packed;

#define HCI_OP_WE_STAWT_ENC		0x2019
stwuct hci_cp_we_stawt_enc {
	__we16	handwe;
	__we64	wand;
	__we16	ediv;
	__u8	wtk[16];
} __packed;

#define HCI_OP_WE_WTK_WEPWY		0x201a
stwuct hci_cp_we_wtk_wepwy {
	__we16	handwe;
	__u8	wtk[16];
} __packed;
stwuct hci_wp_we_wtk_wepwy {
	__u8	status;
	__we16	handwe;
} __packed;

#define HCI_OP_WE_WTK_NEG_WEPWY		0x201b
stwuct hci_cp_we_wtk_neg_wepwy {
	__we16	handwe;
} __packed;
stwuct hci_wp_we_wtk_neg_wepwy {
	__u8	status;
	__we16	handwe;
} __packed;

#define HCI_OP_WE_WEAD_SUPPOWTED_STATES	0x201c
stwuct hci_wp_we_wead_suppowted_states {
	__u8	status;
	__u8	we_states[8];
} __packed;

#define HCI_OP_WE_CONN_PAWAM_WEQ_WEPWY	0x2020
stwuct hci_cp_we_conn_pawam_weq_wepwy {
	__we16	handwe;
	__we16	intewvaw_min;
	__we16	intewvaw_max;
	__we16	watency;
	__we16	timeout;
	__we16	min_ce_wen;
	__we16	max_ce_wen;
} __packed;

#define HCI_OP_WE_CONN_PAWAM_WEQ_NEG_WEPWY	0x2021
stwuct hci_cp_we_conn_pawam_weq_neg_wepwy {
	__we16	handwe;
	__u8	weason;
} __packed;

#define HCI_OP_WE_SET_DATA_WEN		0x2022
stwuct hci_cp_we_set_data_wen {
	__we16	handwe;
	__we16	tx_wen;
	__we16	tx_time;
} __packed;
stwuct hci_wp_we_set_data_wen {
	__u8	status;
	__we16	handwe;
} __packed;

#define HCI_OP_WE_WEAD_DEF_DATA_WEN	0x2023
stwuct hci_wp_we_wead_def_data_wen {
	__u8	status;
	__we16	tx_wen;
	__we16	tx_time;
} __packed;

#define HCI_OP_WE_WWITE_DEF_DATA_WEN	0x2024
stwuct hci_cp_we_wwite_def_data_wen {
	__we16	tx_wen;
	__we16	tx_time;
} __packed;

#define HCI_OP_WE_ADD_TO_WESOWV_WIST	0x2027
stwuct hci_cp_we_add_to_wesowv_wist {
	__u8	 bdaddw_type;
	bdaddw_t bdaddw;
	__u8	 peew_iwk[16];
	__u8	 wocaw_iwk[16];
} __packed;

#define HCI_OP_WE_DEW_FWOM_WESOWV_WIST	0x2028
stwuct hci_cp_we_dew_fwom_wesowv_wist {
	__u8	 bdaddw_type;
	bdaddw_t bdaddw;
} __packed;

#define HCI_OP_WE_CWEAW_WESOWV_WIST	0x2029

#define HCI_OP_WE_WEAD_WESOWV_WIST_SIZE	0x202a
stwuct hci_wp_we_wead_wesowv_wist_size {
	__u8	status;
	__u8	size;
} __packed;

#define HCI_OP_WE_SET_ADDW_WESOWV_ENABWE 0x202d

#define HCI_OP_WE_SET_WPA_TIMEOUT	0x202e

#define HCI_OP_WE_WEAD_MAX_DATA_WEN	0x202f
stwuct hci_wp_we_wead_max_data_wen {
	__u8	status;
	__we16	tx_wen;
	__we16	tx_time;
	__we16	wx_wen;
	__we16	wx_time;
} __packed;

#define HCI_OP_WE_SET_DEFAUWT_PHY	0x2031
stwuct hci_cp_we_set_defauwt_phy {
	__u8    aww_phys;
	__u8    tx_phys;
	__u8    wx_phys;
} __packed;

#define HCI_WE_SET_PHY_1M		0x01
#define HCI_WE_SET_PHY_2M		0x02
#define HCI_WE_SET_PHY_CODED		0x04

#define HCI_OP_WE_SET_EXT_SCAN_PAWAMS   0x2041
stwuct hci_cp_we_set_ext_scan_pawams {
	__u8    own_addw_type;
	__u8    fiwtew_powicy;
	__u8    scanning_phys;
	__u8    data[];
} __packed;

#define WE_SCAN_PHY_1M		0x01
#define WE_SCAN_PHY_2M		0x02
#define WE_SCAN_PHY_CODED	0x04

stwuct hci_cp_we_scan_phy_pawams {
	__u8    type;
	__we16  intewvaw;
	__we16  window;
} __packed;

#define HCI_OP_WE_SET_EXT_SCAN_ENABWE   0x2042
stwuct hci_cp_we_set_ext_scan_enabwe {
	__u8    enabwe;
	__u8    fiwtew_dup;
	__we16  duwation;
	__we16  pewiod;
} __packed;

#define HCI_OP_WE_EXT_CWEATE_CONN    0x2043
stwuct hci_cp_we_ext_cweate_conn {
	__u8      fiwtew_powicy;
	__u8      own_addw_type;
	__u8      peew_addw_type;
	bdaddw_t  peew_addw;
	__u8      phys;
	__u8      data[];
} __packed;

stwuct hci_cp_we_ext_conn_pawam {
	__we16 scan_intewvaw;
	__we16 scan_window;
	__we16 conn_intewvaw_min;
	__we16 conn_intewvaw_max;
	__we16 conn_watency;
	__we16 supewvision_timeout;
	__we16 min_ce_wen;
	__we16 max_ce_wen;
} __packed;

#define HCI_OP_WE_PA_CWEATE_SYNC	0x2044
stwuct hci_cp_we_pa_cweate_sync {
	__u8      options;
	__u8      sid;
	__u8      addw_type;
	bdaddw_t  addw;
	__we16    skip;
	__we16    sync_timeout;
	__u8      sync_cte_type;
} __packed;

#define HCI_OP_WE_PA_TEWM_SYNC		0x2046
stwuct hci_cp_we_pa_tewm_sync {
	__we16    handwe;
} __packed;

#define HCI_OP_WE_WEAD_NUM_SUPPOWTED_ADV_SETS	0x203b
stwuct hci_wp_we_wead_num_suppowted_adv_sets {
	__u8  status;
	__u8  num_of_sets;
} __packed;

#define HCI_OP_WE_SET_EXT_ADV_PAWAMS		0x2036
stwuct hci_cp_we_set_ext_adv_pawams {
	__u8      handwe;
	__we16    evt_pwopewties;
	__u8      min_intewvaw[3];
	__u8      max_intewvaw[3];
	__u8      channew_map;
	__u8      own_addw_type;
	__u8      peew_addw_type;
	bdaddw_t  peew_addw;
	__u8      fiwtew_powicy;
	__u8      tx_powew;
	__u8      pwimawy_phy;
	__u8      secondawy_max_skip;
	__u8      secondawy_phy;
	__u8      sid;
	__u8      notif_enabwe;
} __packed;

#define HCI_ADV_PHY_1M		0X01
#define HCI_ADV_PHY_2M		0x02
#define HCI_ADV_PHY_CODED	0x03

stwuct hci_wp_we_set_ext_adv_pawams {
	__u8  status;
	__u8  tx_powew;
} __packed;

stwuct hci_cp_ext_adv_set {
	__u8  handwe;
	__we16 duwation;
	__u8  max_events;
} __packed;

#define HCI_MAX_EXT_AD_WENGTH	251

#define HCI_OP_WE_SET_EXT_ADV_DATA		0x2037
stwuct hci_cp_we_set_ext_adv_data {
	__u8  handwe;
	__u8  opewation;
	__u8  fwag_pwef;
	__u8  wength;
	__u8  data[];
} __packed;

#define HCI_OP_WE_SET_EXT_SCAN_WSP_DATA		0x2038
stwuct hci_cp_we_set_ext_scan_wsp_data {
	__u8  handwe;
	__u8  opewation;
	__u8  fwag_pwef;
	__u8  wength;
	__u8  data[];
} __packed;

#define HCI_OP_WE_SET_EXT_ADV_ENABWE		0x2039
stwuct hci_cp_we_set_ext_adv_enabwe {
	__u8  enabwe;
	__u8  num_of_sets;
	__u8  data[];
} __packed;

#define HCI_OP_WE_SET_PEW_ADV_PAWAMS		0x203e
stwuct hci_cp_we_set_pew_adv_pawams {
	__u8      handwe;
	__we16    min_intewvaw;
	__we16    max_intewvaw;
	__we16    pewiodic_pwopewties;
} __packed;

#define HCI_MAX_PEW_AD_WENGTH	252

#define HCI_OP_WE_SET_PEW_ADV_DATA		0x203f
stwuct hci_cp_we_set_pew_adv_data {
	__u8  handwe;
	__u8  opewation;
	__u8  wength;
	__u8  data[];
} __packed;

#define HCI_OP_WE_SET_PEW_ADV_ENABWE		0x2040
stwuct hci_cp_we_set_pew_adv_enabwe {
	__u8  enabwe;
	__u8  handwe;
} __packed;

#define WE_SET_ADV_DATA_OP_COMPWETE	0x03

#define WE_SET_ADV_DATA_NO_FWAG		0x01

#define HCI_OP_WE_WEMOVE_ADV_SET	0x203c

#define HCI_OP_WE_CWEAW_ADV_SETS	0x203d

#define HCI_OP_WE_SET_ADV_SET_WAND_ADDW	0x2035
stwuct hci_cp_we_set_adv_set_wand_addw {
	__u8  handwe;
	bdaddw_t  bdaddw;
} __packed;

#define HCI_OP_WE_WEAD_TWANSMIT_POWEW	0x204b
stwuct hci_wp_we_wead_twansmit_powew {
	__u8  status;
	__s8  min_we_tx_powew;
	__s8  max_we_tx_powew;
} __packed;

#define HCI_NETWOWK_PWIVACY		0x00
#define HCI_DEVICE_PWIVACY		0x01

#define HCI_OP_WE_SET_PWIVACY_MODE	0x204e
stwuct hci_cp_we_set_pwivacy_mode {
	__u8  bdaddw_type;
	bdaddw_t  bdaddw;
	__u8  mode;
} __packed;

#define HCI_OP_WE_WEAD_BUFFEW_SIZE_V2	0x2060
stwuct hci_wp_we_wead_buffew_size_v2 {
	__u8    status;
	__we16  acw_mtu;
	__u8    acw_max_pkt;
	__we16  iso_mtu;
	__u8    iso_max_pkt;
} __packed;

#define HCI_OP_WE_WEAD_ISO_TX_SYNC		0x2061
stwuct hci_cp_we_wead_iso_tx_sync {
	__we16  handwe;
} __packed;

stwuct hci_wp_we_wead_iso_tx_sync {
	__u8    status;
	__we16  handwe;
	__we16  seq;
	__we32  imestamp;
	__u8    offset[3];
} __packed;

#define HCI_OP_WE_SET_CIG_PAWAMS		0x2062
stwuct hci_cis_pawams {
	__u8    cis_id;
	__we16  c_sdu;
	__we16  p_sdu;
	__u8    c_phy;
	__u8    p_phy;
	__u8    c_wtn;
	__u8    p_wtn;
} __packed;

stwuct hci_cp_we_set_cig_pawams {
	__u8    cig_id;
	__u8    c_intewvaw[3];
	__u8    p_intewvaw[3];
	__u8    sca;
	__u8    packing;
	__u8    fwaming;
	__we16  c_watency;
	__we16  p_watency;
	__u8    num_cis;
	stwuct hci_cis_pawams cis[];
} __packed;

stwuct hci_wp_we_set_cig_pawams {
	__u8    status;
	__u8    cig_id;
	__u8    num_handwes;
	__we16  handwe[];
} __packed;

#define HCI_OP_WE_CWEATE_CIS			0x2064
stwuct hci_cis {
	__we16  cis_handwe;
	__we16  acw_handwe;
} __packed;

stwuct hci_cp_we_cweate_cis {
	__u8    num_cis;
	stwuct hci_cis cis[];
} __packed;

#define HCI_OP_WE_WEMOVE_CIG			0x2065
stwuct hci_cp_we_wemove_cig {
	__u8    cig_id;
} __packed;

#define HCI_OP_WE_ACCEPT_CIS			0x2066
stwuct hci_cp_we_accept_cis {
	__we16  handwe;
} __packed;

#define HCI_OP_WE_WEJECT_CIS			0x2067
stwuct hci_cp_we_weject_cis {
	__we16  handwe;
	__u8    weason;
} __packed;

#define HCI_OP_WE_CWEATE_BIG			0x2068
stwuct hci_bis {
	__u8    sdu_intewvaw[3];
	__we16  sdu;
	__we16  watency;
	__u8    wtn;
	__u8    phy;
	__u8    packing;
	__u8    fwaming;
	__u8    encwyption;
	__u8    bcode[16];
} __packed;

stwuct hci_cp_we_cweate_big {
	__u8    handwe;
	__u8    adv_handwe;
	__u8    num_bis;
	stwuct hci_bis bis;
} __packed;

#define HCI_OP_WE_TEWM_BIG			0x206a
stwuct hci_cp_we_tewm_big {
	__u8    handwe;
	__u8    weason;
} __packed;

#define HCI_OP_WE_BIG_CWEATE_SYNC		0x206b
stwuct hci_cp_we_big_cweate_sync {
	__u8    handwe;
	__we16  sync_handwe;
	__u8    encwyption;
	__u8    bcode[16];
	__u8    mse;
	__we16  timeout;
	__u8    num_bis;
	__u8    bis[];
} __packed;

#define HCI_OP_WE_BIG_TEWM_SYNC			0x206c
stwuct hci_cp_we_big_tewm_sync {
	__u8    handwe;
} __packed;

#define HCI_OP_WE_SETUP_ISO_PATH		0x206e
stwuct hci_cp_we_setup_iso_path {
	__we16  handwe;
	__u8    diwection;
	__u8    path;
	__u8    codec;
	__we16  codec_cid;
	__we16  codec_vid;
	__u8    deway[3];
	__u8    codec_cfg_wen;
	__u8    codec_cfg[];
} __packed;

stwuct hci_wp_we_setup_iso_path {
	__u8    status;
	__we16  handwe;
} __packed;

#define HCI_OP_WE_SET_HOST_FEATUWE		0x2074
stwuct hci_cp_we_set_host_featuwe {
	__u8     bit_numbew;
	__u8     bit_vawue;
} __packed;

/* ---- HCI Events ---- */
stwuct hci_ev_status {
	__u8    status;
} __packed;

#define HCI_EV_INQUIWY_COMPWETE		0x01

#define HCI_EV_INQUIWY_WESUWT		0x02
stwuct inquiwy_info {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
	__u8     pscan_pewiod_mode;
	__u8     pscan_mode;
	__u8     dev_cwass[3];
	__we16   cwock_offset;
} __packed;

stwuct hci_ev_inquiwy_wesuwt {
	__u8    num;
	stwuct inquiwy_info info[];
};

#define HCI_EV_CONN_COMPWETE		0x03
stwuct hci_ev_conn_compwete {
	__u8     status;
	__we16   handwe;
	bdaddw_t bdaddw;
	__u8     wink_type;
	__u8     encw_mode;
} __packed;

#define HCI_EV_CONN_WEQUEST		0x04
stwuct hci_ev_conn_wequest {
	bdaddw_t bdaddw;
	__u8     dev_cwass[3];
	__u8     wink_type;
} __packed;

#define HCI_EV_DISCONN_COMPWETE		0x05
stwuct hci_ev_disconn_compwete {
	__u8     status;
	__we16   handwe;
	__u8     weason;
} __packed;

#define HCI_EV_AUTH_COMPWETE		0x06
stwuct hci_ev_auth_compwete {
	__u8     status;
	__we16   handwe;
} __packed;

#define HCI_EV_WEMOTE_NAME		0x07
stwuct hci_ev_wemote_name {
	__u8     status;
	bdaddw_t bdaddw;
	__u8     name[HCI_MAX_NAME_WENGTH];
} __packed;

#define HCI_EV_ENCWYPT_CHANGE		0x08
stwuct hci_ev_encwypt_change {
	__u8     status;
	__we16   handwe;
	__u8     encwypt;
} __packed;

#define HCI_EV_CHANGE_WINK_KEY_COMPWETE	0x09
stwuct hci_ev_change_wink_key_compwete {
	__u8     status;
	__we16   handwe;
} __packed;

#define HCI_EV_WEMOTE_FEATUWES		0x0b
stwuct hci_ev_wemote_featuwes {
	__u8     status;
	__we16   handwe;
	__u8     featuwes[8];
} __packed;

#define HCI_EV_WEMOTE_VEWSION		0x0c
stwuct hci_ev_wemote_vewsion {
	__u8     status;
	__we16   handwe;
	__u8     wmp_vew;
	__we16   manufactuwew;
	__we16   wmp_subvew;
} __packed;

#define HCI_EV_QOS_SETUP_COMPWETE	0x0d
stwuct hci_qos {
	__u8     sewvice_type;
	__u32    token_wate;
	__u32    peak_bandwidth;
	__u32    watency;
	__u32    deway_vawiation;
} __packed;
stwuct hci_ev_qos_setup_compwete {
	__u8     status;
	__we16   handwe;
	stwuct   hci_qos qos;
} __packed;

#define HCI_EV_CMD_COMPWETE		0x0e
stwuct hci_ev_cmd_compwete {
	__u8     ncmd;
	__we16   opcode;
} __packed;

#define HCI_EV_CMD_STATUS		0x0f
stwuct hci_ev_cmd_status {
	__u8     status;
	__u8     ncmd;
	__we16   opcode;
} __packed;

#define HCI_EV_HAWDWAWE_EWWOW		0x10
stwuct hci_ev_hawdwawe_ewwow {
	__u8     code;
} __packed;

#define HCI_EV_WOWE_CHANGE		0x12
stwuct hci_ev_wowe_change {
	__u8     status;
	bdaddw_t bdaddw;
	__u8     wowe;
} __packed;

#define HCI_EV_NUM_COMP_PKTS		0x13
stwuct hci_comp_pkts_info {
	__we16   handwe;
	__we16   count;
} __packed;

stwuct hci_ev_num_comp_pkts {
	__u8     num;
	stwuct hci_comp_pkts_info handwes[];
} __packed;

#define HCI_EV_MODE_CHANGE		0x14
stwuct hci_ev_mode_change {
	__u8     status;
	__we16   handwe;
	__u8     mode;
	__we16   intewvaw;
} __packed;

#define HCI_EV_PIN_CODE_WEQ		0x16
stwuct hci_ev_pin_code_weq {
	bdaddw_t bdaddw;
} __packed;

#define HCI_EV_WINK_KEY_WEQ		0x17
stwuct hci_ev_wink_key_weq {
	bdaddw_t bdaddw;
} __packed;

#define HCI_EV_WINK_KEY_NOTIFY		0x18
stwuct hci_ev_wink_key_notify {
	bdaddw_t bdaddw;
	__u8     wink_key[HCI_WINK_KEY_SIZE];
	__u8     key_type;
} __packed;

#define HCI_EV_CWOCK_OFFSET		0x1c
stwuct hci_ev_cwock_offset {
	__u8     status;
	__we16   handwe;
	__we16   cwock_offset;
} __packed;

#define HCI_EV_PKT_TYPE_CHANGE		0x1d
stwuct hci_ev_pkt_type_change {
	__u8     status;
	__we16   handwe;
	__we16   pkt_type;
} __packed;

#define HCI_EV_PSCAN_WEP_MODE		0x20
stwuct hci_ev_pscan_wep_mode {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
} __packed;

#define HCI_EV_INQUIWY_WESUWT_WITH_WSSI	0x22
stwuct inquiwy_info_wssi {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
	__u8     pscan_pewiod_mode;
	__u8     dev_cwass[3];
	__we16   cwock_offset;
	__s8     wssi;
} __packed;
stwuct inquiwy_info_wssi_pscan {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
	__u8     pscan_pewiod_mode;
	__u8     pscan_mode;
	__u8     dev_cwass[3];
	__we16   cwock_offset;
	__s8     wssi;
} __packed;
stwuct hci_ev_inquiwy_wesuwt_wssi {
	__u8     num;
	__u8     data[];
} __packed;

#define HCI_EV_WEMOTE_EXT_FEATUWES	0x23
stwuct hci_ev_wemote_ext_featuwes {
	__u8     status;
	__we16   handwe;
	__u8     page;
	__u8     max_page;
	__u8     featuwes[8];
} __packed;

#define HCI_EV_SYNC_CONN_COMPWETE	0x2c
stwuct hci_ev_sync_conn_compwete {
	__u8     status;
	__we16   handwe;
	bdaddw_t bdaddw;
	__u8     wink_type;
	__u8     tx_intewvaw;
	__u8     wetwans_window;
	__we16   wx_pkt_wen;
	__we16   tx_pkt_wen;
	__u8     aiw_mode;
} __packed;

#define HCI_EV_SYNC_CONN_CHANGED	0x2d
stwuct hci_ev_sync_conn_changed {
	__u8     status;
	__we16   handwe;
	__u8     tx_intewvaw;
	__u8     wetwans_window;
	__we16   wx_pkt_wen;
	__we16   tx_pkt_wen;
} __packed;

#define HCI_EV_SNIFF_SUBWATE		0x2e
stwuct hci_ev_sniff_subwate {
	__u8     status;
	__we16   handwe;
	__we16   max_tx_watency;
	__we16   max_wx_watency;
	__we16   max_wemote_timeout;
	__we16   max_wocaw_timeout;
} __packed;

#define HCI_EV_EXTENDED_INQUIWY_WESUWT	0x2f
stwuct extended_inquiwy_info {
	bdaddw_t bdaddw;
	__u8     pscan_wep_mode;
	__u8     pscan_pewiod_mode;
	__u8     dev_cwass[3];
	__we16   cwock_offset;
	__s8     wssi;
	__u8     data[240];
} __packed;

stwuct hci_ev_ext_inquiwy_wesuwt {
	__u8     num;
	stwuct extended_inquiwy_info info[];
} __packed;

#define HCI_EV_KEY_WEFWESH_COMPWETE	0x30
stwuct hci_ev_key_wefwesh_compwete {
	__u8	status;
	__we16	handwe;
} __packed;

#define HCI_EV_IO_CAPA_WEQUEST		0x31
stwuct hci_ev_io_capa_wequest {
	bdaddw_t bdaddw;
} __packed;

#define HCI_EV_IO_CAPA_WEPWY		0x32
stwuct hci_ev_io_capa_wepwy {
	bdaddw_t bdaddw;
	__u8     capabiwity;
	__u8     oob_data;
	__u8     authentication;
} __packed;

#define HCI_EV_USEW_CONFIWM_WEQUEST	0x33
stwuct hci_ev_usew_confiwm_weq {
	bdaddw_t	bdaddw;
	__we32		passkey;
} __packed;

#define HCI_EV_USEW_PASSKEY_WEQUEST	0x34
stwuct hci_ev_usew_passkey_weq {
	bdaddw_t	bdaddw;
} __packed;

#define HCI_EV_WEMOTE_OOB_DATA_WEQUEST	0x35
stwuct hci_ev_wemote_oob_data_wequest {
	bdaddw_t bdaddw;
} __packed;

#define HCI_EV_SIMPWE_PAIW_COMPWETE	0x36
stwuct hci_ev_simpwe_paiw_compwete {
	__u8     status;
	bdaddw_t bdaddw;
} __packed;

#define HCI_EV_USEW_PASSKEY_NOTIFY	0x3b
stwuct hci_ev_usew_passkey_notify {
	bdaddw_t	bdaddw;
	__we32		passkey;
} __packed;

#define HCI_KEYPWESS_STAWTED		0
#define HCI_KEYPWESS_ENTEWED		1
#define HCI_KEYPWESS_EWASED		2
#define HCI_KEYPWESS_CWEAWED		3
#define HCI_KEYPWESS_COMPWETED		4

#define HCI_EV_KEYPWESS_NOTIFY		0x3c
stwuct hci_ev_keypwess_notify {
	bdaddw_t	bdaddw;
	__u8		type;
} __packed;

#define HCI_EV_WEMOTE_HOST_FEATUWES	0x3d
stwuct hci_ev_wemote_host_featuwes {
	bdaddw_t bdaddw;
	__u8     featuwes[8];
} __packed;

#define HCI_EV_WE_META			0x3e
stwuct hci_ev_we_meta {
	__u8     subevent;
} __packed;

#define HCI_EV_PHY_WINK_COMPWETE	0x40
stwuct hci_ev_phy_wink_compwete {
	__u8     status;
	__u8     phy_handwe;
} __packed;

#define HCI_EV_CHANNEW_SEWECTED		0x41
stwuct hci_ev_channew_sewected {
	__u8     phy_handwe;
} __packed;

#define HCI_EV_DISCONN_PHY_WINK_COMPWETE	0x42
stwuct hci_ev_disconn_phy_wink_compwete {
	__u8     status;
	__u8     phy_handwe;
	__u8     weason;
} __packed;

#define HCI_EV_WOGICAW_WINK_COMPWETE		0x45
stwuct hci_ev_wogicaw_wink_compwete {
	__u8     status;
	__we16   handwe;
	__u8     phy_handwe;
	__u8     fwow_spec_id;
} __packed;

#define HCI_EV_DISCONN_WOGICAW_WINK_COMPWETE	0x46
stwuct hci_ev_disconn_wogicaw_wink_compwete {
	__u8     status;
	__we16   handwe;
	__u8     weason;
} __packed;

#define HCI_EV_NUM_COMP_BWOCKS		0x48
stwuct hci_comp_bwocks_info {
	__we16   handwe;
	__we16   pkts;
	__we16   bwocks;
} __packed;

stwuct hci_ev_num_comp_bwocks {
	__we16   num_bwocks;
	__u8     num_hndw;
	stwuct hci_comp_bwocks_info handwes[];
} __packed;

#define HCI_EV_SYNC_TWAIN_COMPWETE	0x4F
stwuct hci_ev_sync_twain_compwete {
	__u8	status;
} __packed;

#define HCI_EV_PEWIPHEWAW_PAGE_WESP_TIMEOUT	0x54

#define HCI_EV_WE_CONN_COMPWETE		0x01
stwuct hci_ev_we_conn_compwete {
	__u8     status;
	__we16   handwe;
	__u8     wowe;
	__u8     bdaddw_type;
	bdaddw_t bdaddw;
	__we16   intewvaw;
	__we16   watency;
	__we16   supewvision_timeout;
	__u8     cwk_accuwancy;
} __packed;

/* Advewtising wepowt event types */
#define WE_ADV_IND		0x00
#define WE_ADV_DIWECT_IND	0x01
#define WE_ADV_SCAN_IND		0x02
#define WE_ADV_NONCONN_IND	0x03
#define WE_ADV_SCAN_WSP		0x04
#define WE_ADV_INVAWID		0x05

/* Wegacy event types in extended adv wepowt */
#define WE_WEGACY_ADV_IND		0x0013
#define WE_WEGACY_ADV_DIWECT_IND 	0x0015
#define WE_WEGACY_ADV_SCAN_IND		0x0012
#define WE_WEGACY_NONCONN_IND		0x0010
#define WE_WEGACY_SCAN_WSP_ADV		0x001b
#define WE_WEGACY_SCAN_WSP_ADV_SCAN	0x001a

/* Extended Advewtising event types */
#define WE_EXT_ADV_NON_CONN_IND		0x0000
#define WE_EXT_ADV_CONN_IND		0x0001
#define WE_EXT_ADV_SCAN_IND		0x0002
#define WE_EXT_ADV_DIWECT_IND		0x0004
#define WE_EXT_ADV_SCAN_WSP		0x0008
#define WE_EXT_ADV_WEGACY_PDU		0x0010
#define WE_EXT_ADV_EVT_TYPE_MASK	0x007f

#define ADDW_WE_DEV_PUBWIC		0x00
#define ADDW_WE_DEV_WANDOM		0x01
#define ADDW_WE_DEV_PUBWIC_WESOWVED	0x02
#define ADDW_WE_DEV_WANDOM_WESOWVED	0x03

#define HCI_EV_WE_ADVEWTISING_WEPOWT	0x02
stwuct hci_ev_we_advewtising_info {
	__u8	 type;
	__u8	 bdaddw_type;
	bdaddw_t bdaddw;
	__u8	 wength;
	__u8	 data[];
} __packed;

stwuct hci_ev_we_advewtising_wepowt {
	__u8    num;
	stwuct hci_ev_we_advewtising_info info[];
} __packed;

#define HCI_EV_WE_CONN_UPDATE_COMPWETE	0x03
stwuct hci_ev_we_conn_update_compwete {
	__u8     status;
	__we16   handwe;
	__we16   intewvaw;
	__we16   watency;
	__we16   supewvision_timeout;
} __packed;

#define HCI_EV_WE_WEMOTE_FEAT_COMPWETE	0x04
stwuct hci_ev_we_wemote_feat_compwete {
	__u8     status;
	__we16   handwe;
	__u8     featuwes[8];
} __packed;

#define HCI_EV_WE_WTK_WEQ		0x05
stwuct hci_ev_we_wtk_weq {
	__we16	handwe;
	__we64	wand;
	__we16	ediv;
} __packed;

#define HCI_EV_WE_WEMOTE_CONN_PAWAM_WEQ	0x06
stwuct hci_ev_we_wemote_conn_pawam_weq {
	__we16 handwe;
	__we16 intewvaw_min;
	__we16 intewvaw_max;
	__we16 watency;
	__we16 timeout;
} __packed;

#define HCI_EV_WE_DATA_WEN_CHANGE	0x07
stwuct hci_ev_we_data_wen_change {
	__we16	handwe;
	__we16	tx_wen;
	__we16	tx_time;
	__we16	wx_wen;
	__we16	wx_time;
} __packed;

#define HCI_EV_WE_DIWECT_ADV_WEPOWT	0x0B
stwuct hci_ev_we_diwect_adv_info {
	__u8	 type;
	__u8	 bdaddw_type;
	bdaddw_t bdaddw;
	__u8	 diwect_addw_type;
	bdaddw_t diwect_addw;
	__s8	 wssi;
} __packed;

stwuct hci_ev_we_diwect_adv_wepowt {
	__u8	 num;
	stwuct hci_ev_we_diwect_adv_info info[];
} __packed;

#define HCI_EV_WE_PHY_UPDATE_COMPWETE	0x0c
stwuct hci_ev_we_phy_update_compwete {
	__u8  status;
	__we16 handwe;
	__u8  tx_phy;
	__u8  wx_phy;
} __packed;

#define HCI_EV_WE_EXT_ADV_WEPOWT    0x0d
stwuct hci_ev_we_ext_adv_info {
	__we16   type;
	__u8	 bdaddw_type;
	bdaddw_t bdaddw;
	__u8	 pwimawy_phy;
	__u8	 secondawy_phy;
	__u8	 sid;
	__u8	 tx_powew;
	__s8	 wssi;
	__we16   intewvaw;
	__u8     diwect_addw_type;
	bdaddw_t diwect_addw;
	__u8     wength;
	__u8     data[];
} __packed;

stwuct hci_ev_we_ext_adv_wepowt {
	__u8     num;
	stwuct hci_ev_we_ext_adv_info info[];
} __packed;

#define HCI_EV_WE_PA_SYNC_ESTABWISHED	0x0e
stwuct hci_ev_we_pa_sync_estabwished {
	__u8      status;
	__we16    handwe;
	__u8      sid;
	__u8      bdaddw_type;
	bdaddw_t  bdaddw;
	__u8      phy;
	__we16    intewvaw;
	__u8      cwock_accuwacy;
} __packed;

#define HCI_EV_WE_ENHANCED_CONN_COMPWETE    0x0a
stwuct hci_ev_we_enh_conn_compwete {
	__u8      status;
	__we16    handwe;
	__u8      wowe;
	__u8      bdaddw_type;
	bdaddw_t  bdaddw;
	bdaddw_t  wocaw_wpa;
	bdaddw_t  peew_wpa;
	__we16    intewvaw;
	__we16    watency;
	__we16    supewvision_timeout;
	__u8      cwk_accuwancy;
} __packed;

#define HCI_EV_WE_PEW_ADV_WEPOWT    0x0f
stwuct hci_ev_we_pew_adv_wepowt {
	__we16	 sync_handwe;
	__u8	 tx_powew;
	__u8	 wssi;
	__u8	 cte_type;
	__u8	 data_status;
	__u8     wength;
	__u8     data[];
} __packed;

#define HCI_EV_WE_EXT_ADV_SET_TEWM	0x12
stwuct hci_evt_we_ext_adv_set_tewm {
	__u8	status;
	__u8	handwe;
	__we16	conn_handwe;
	__u8	num_evts;
} __packed;

#define HCI_EVT_WE_CIS_ESTABWISHED	0x19
stwuct hci_evt_we_cis_estabwished {
	__u8  status;
	__we16 handwe;
	__u8  cig_sync_deway[3];
	__u8  cis_sync_deway[3];
	__u8  c_watency[3];
	__u8  p_watency[3];
	__u8  c_phy;
	__u8  p_phy;
	__u8  nse;
	__u8  c_bn;
	__u8  p_bn;
	__u8  c_ft;
	__u8  p_ft;
	__we16 c_mtu;
	__we16 p_mtu;
	__we16 intewvaw;
} __packed;

#define HCI_EVT_WE_CIS_WEQ		0x1a
stwuct hci_evt_we_cis_weq {
	__we16 acw_handwe;
	__we16 cis_handwe;
	__u8  cig_id;
	__u8  cis_id;
} __packed;

#define HCI_EVT_WE_CWEATE_BIG_COMPWETE	0x1b
stwuct hci_evt_we_cweate_big_compwete {
	__u8    status;
	__u8    handwe;
	__u8    sync_deway[3];
	__u8    twanspowt_deway[3];
	__u8    phy;
	__u8    nse;
	__u8    bn;
	__u8    pto;
	__u8    iwc;
	__we16  max_pdu;
	__we16  intewvaw;
	__u8    num_bis;
	__we16  bis_handwe[];
} __packed;

#define HCI_EVT_WE_BIG_SYNC_ESTABIWISHED 0x1d
stwuct hci_evt_we_big_sync_estabiwished {
	__u8    status;
	__u8    handwe;
	__u8    watency[3];
	__u8    nse;
	__u8    bn;
	__u8    pto;
	__u8    iwc;
	__we16  max_pdu;
	__we16  intewvaw;
	__u8    num_bis;
	__we16  bis[];
} __packed;

#define HCI_EVT_WE_BIG_INFO_ADV_WEPOWT	0x22
stwuct hci_evt_we_big_info_adv_wepowt {
	__we16  sync_handwe;
	__u8    num_bis;
	__u8    nse;
	__we16  iso_intewvaw;
	__u8    bn;
	__u8    pto;
	__u8    iwc;
	__we16  max_pdu;
	__u8    sdu_intewvaw[3];
	__we16  max_sdu;
	__u8    phy;
	__u8    fwaming;
	__u8    encwyption;
} __packed;

#define HCI_EV_VENDOW			0xff

/* Intewnaw events genewated by Bwuetooth stack */
#define HCI_EV_STACK_INTEWNAW	0xfd
stwuct hci_ev_stack_intewnaw {
	__u16    type;
	__u8     data[];
} __packed;

#define HCI_EV_SI_DEVICE	0x01
stwuct hci_ev_si_device {
	__u16    event;
	__u16    dev_id;
} __packed;

#define HCI_EV_SI_SECUWITY	0x02
stwuct hci_ev_si_secuwity {
	__u16    event;
	__u16    pwoto;
	__u16    subpwoto;
	__u8     incoming;
} __packed;

/* ---- HCI Packet stwuctuwes ---- */
#define HCI_COMMAND_HDW_SIZE 3
#define HCI_EVENT_HDW_SIZE   2
#define HCI_ACW_HDW_SIZE     4
#define HCI_SCO_HDW_SIZE     3
#define HCI_ISO_HDW_SIZE     4

stwuct hci_command_hdw {
	__we16	opcode;		/* OCF & OGF */
	__u8	pwen;
} __packed;

stwuct hci_event_hdw {
	__u8	evt;
	__u8	pwen;
} __packed;

stwuct hci_acw_hdw {
	__we16	handwe;		/* Handwe & Fwags(PB, BC) */
	__we16	dwen;
} __packed;

stwuct hci_sco_hdw {
	__we16	handwe;
	__u8	dwen;
} __packed;

stwuct hci_iso_hdw {
	__we16	handwe;
	__we16	dwen;
	__u8	data[];
} __packed;

/* ISO data packet status fwags */
#define HCI_ISO_STATUS_VAWID	0x00
#define HCI_ISO_STATUS_INVAWID	0x01
#define HCI_ISO_STATUS_NOP	0x02

#define HCI_ISO_DATA_HDW_SIZE	4
stwuct hci_iso_data_hdw {
	__we16	sn;
	__we16	swen;
};

#define HCI_ISO_TS_DATA_HDW_SIZE 8
stwuct hci_iso_ts_data_hdw {
	__we32	ts;
	__we16	sn;
	__we16	swen;
};

static inwine stwuct hci_event_hdw *hci_event_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct hci_event_hdw *) skb->data;
}

static inwine stwuct hci_acw_hdw *hci_acw_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct hci_acw_hdw *) skb->data;
}

static inwine stwuct hci_sco_hdw *hci_sco_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct hci_sco_hdw *) skb->data;
}

/* Command opcode pack/unpack */
#define hci_opcode_pack(ogf, ocf)	((__u16) ((ocf & 0x03ff)|(ogf << 10)))
#define hci_opcode_ogf(op)		(op >> 10)
#define hci_opcode_ocf(op)		(op & 0x03ff)

/* ACW handwe and fwags pack/unpack */
#define hci_handwe_pack(h, f)	((__u16) ((h & 0x0fff)|(f << 12)))
#define hci_handwe(h)		(h & 0x0fff)
#define hci_fwags(h)		(h >> 12)

/* ISO handwe and fwags pack/unpack */
#define hci_iso_fwags_pb(f)		(f & 0x0003)
#define hci_iso_fwags_ts(f)		((f >> 2) & 0x0001)
#define hci_iso_fwags_pack(pb, ts)	((pb & 0x03) | ((ts & 0x01) << 2))

/* ISO data wength and fwags pack/unpack */
#define hci_iso_data_wen_pack(h, f)	((__u16) ((h) | ((f) << 14)))
#define hci_iso_data_wen(h)		((h) & 0x3fff)
#define hci_iso_data_fwags(h)		((h) >> 14)

/* codec twanspowt types */
#define HCI_TWANSPOWT_SCO_ESCO	0x01

/* we24 suppowt */
static inwine void hci_cpu_to_we24(__u32 vaw, __u8 dst[3])
{
	dst[0] = vaw & 0xff;
	dst[1] = (vaw & 0xff00) >> 8;
	dst[2] = (vaw & 0xff0000) >> 16;
}

#endif /* __HCI_H */
