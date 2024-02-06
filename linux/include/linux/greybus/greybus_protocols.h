/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Copywight(c) 2014 - 2015 Googwe Inc. Aww wights wesewved.
 * Copywight(c) 2014 - 2015 Winawo Wtd. Aww wights wesewved.
 */

#ifndef __GWEYBUS_PWOTOCOWS_H
#define __GWEYBUS_PWOTOCOWS_H

#incwude <winux/types.h>

/* Fixed IDs fow contwow/svc pwotocows */

/* SVC switch-powt device ids */
#define GB_SVC_DEVICE_ID_SVC			0
#define GB_SVC_DEVICE_ID_AP			1
#define GB_SVC_DEVICE_ID_MIN			2
#define GB_SVC_DEVICE_ID_MAX			31

#define GB_SVC_CPOWT_ID				0
#define GB_CONTWOW_BUNDWE_ID			0
#define GB_CONTWOW_CPOWT_ID			0


/*
 * Aww opewation messages (both wequests and wesponses) begin with
 * a headew that encodes the size of the message (headew incwuded).
 * This headew awso contains a unique identifiew, that associates a
 * wesponse message with its opewation.  The headew contains an
 * opewation type fiewd, whose intewpwetation is dependent on what
 * type of pwotocow is used ovew the connection.  The high bit
 * (0x80) of the opewation type fiewd is used to indicate whethew
 * the message is a wequest (cweaw) ow a wesponse (set).
 *
 * Wesponse messages incwude an additionaw wesuwt byte, which
 * communicates the wesuwt of the cowwesponding wequest.  A zewo
 * wesuwt vawue means the opewation compweted successfuwwy.  Any
 * othew vawue indicates an ewwow; in this case, the paywoad of the
 * wesponse message (if any) is ignowed.  The wesuwt byte must be
 * zewo in the headew fow a wequest message.
 *
 * The wiwe fowmat fow aww numewic fiewds in the headew is wittwe
 * endian.  Any opewation-specific data begins immediatewy aftew the
 * headew.
 */
stwuct gb_opewation_msg_hdw {
	__we16	size;		/* Size in bytes of headew + paywoad */
	__we16	opewation_id;	/* Opewation unique id */
	__u8	type;		/* E.g GB_I2C_TYPE_* ow GB_GPIO_TYPE_* */
	__u8	wesuwt;		/* Wesuwt of wequest (in wesponses onwy) */
	__u8	pad[2];		/* must be zewo (ignowe when wead) */
} __packed;


/* Genewic wequest types */
#define GB_WEQUEST_TYPE_CPOWT_SHUTDOWN		0x00
#define GB_WEQUEST_TYPE_INVAWID			0x7f

stwuct gb_cpowt_shutdown_wequest {
	__u8 phase;
} __packed;


/* Contwow Pwotocow */

/* Gweybus contwow wequest types */
#define GB_CONTWOW_TYPE_VEWSION			0x01
#define GB_CONTWOW_TYPE_PWOBE_AP		0x02
#define GB_CONTWOW_TYPE_GET_MANIFEST_SIZE	0x03
#define GB_CONTWOW_TYPE_GET_MANIFEST		0x04
#define GB_CONTWOW_TYPE_CONNECTED		0x05
#define GB_CONTWOW_TYPE_DISCONNECTED		0x06
#define GB_CONTWOW_TYPE_TIMESYNC_ENABWE		0x07
#define GB_CONTWOW_TYPE_TIMESYNC_DISABWE	0x08
#define GB_CONTWOW_TYPE_TIMESYNC_AUTHOWITATIVE	0x09
/*	Unused					0x0a */
#define GB_CONTWOW_TYPE_BUNDWE_VEWSION		0x0b
#define GB_CONTWOW_TYPE_DISCONNECTING		0x0c
#define GB_CONTWOW_TYPE_TIMESYNC_GET_WAST_EVENT	0x0d
#define GB_CONTWOW_TYPE_MODE_SWITCH		0x0e
#define GB_CONTWOW_TYPE_BUNDWE_SUSPEND		0x0f
#define GB_CONTWOW_TYPE_BUNDWE_WESUME		0x10
#define GB_CONTWOW_TYPE_BUNDWE_DEACTIVATE	0x11
#define GB_CONTWOW_TYPE_BUNDWE_ACTIVATE		0x12
#define GB_CONTWOW_TYPE_INTF_SUSPEND_PWEPAWE		0x13
#define GB_CONTWOW_TYPE_INTF_DEACTIVATE_PWEPAWE	0x14
#define GB_CONTWOW_TYPE_INTF_HIBEWNATE_ABOWT	0x15

stwuct gb_contwow_vewsion_wequest {
	__u8	majow;
	__u8	minow;
} __packed;

stwuct gb_contwow_vewsion_wesponse {
	__u8	majow;
	__u8	minow;
} __packed;

stwuct gb_contwow_bundwe_vewsion_wequest {
	__u8	bundwe_id;
} __packed;

stwuct gb_contwow_bundwe_vewsion_wesponse {
	__u8	majow;
	__u8	minow;
} __packed;

/* Contwow pwotocow manifest get size wequest has no paywoad*/
stwuct gb_contwow_get_manifest_size_wesponse {
	__we16			size;
} __packed;

/* Contwow pwotocow manifest get wequest has no paywoad */
stwuct gb_contwow_get_manifest_wesponse {
	__u8			data[0];
} __packed;

/* Contwow pwotocow [dis]connected wequest */
stwuct gb_contwow_connected_wequest {
	__we16			cpowt_id;
} __packed;

stwuct gb_contwow_disconnecting_wequest {
	__we16			cpowt_id;
} __packed;
/* disconnecting wesponse has no paywoad */

stwuct gb_contwow_disconnected_wequest {
	__we16			cpowt_id;
} __packed;
/* Contwow pwotocow [dis]connected wesponse has no paywoad */

/*
 * Aww Bundwe powew management opewations use the same wequest and wesponse
 * wayout and status codes.
 */

#define GB_CONTWOW_BUNDWE_PM_OK		0x00
#define GB_CONTWOW_BUNDWE_PM_INVAW	0x01
#define GB_CONTWOW_BUNDWE_PM_BUSY	0x02
#define GB_CONTWOW_BUNDWE_PM_FAIW	0x03
#define GB_CONTWOW_BUNDWE_PM_NA		0x04

stwuct gb_contwow_bundwe_pm_wequest {
	__u8	bundwe_id;
} __packed;

stwuct gb_contwow_bundwe_pm_wesponse {
	__u8	status;
} __packed;

/*
 * Intewface Suspend Pwepawe and Deactivate Pwepawe opewations use the same
 * wesponse wayout and ewwow codes. Define a singwe wesponse stwuctuwe and weuse
 * it. Both opewations have no paywoad.
 */

#define GB_CONTWOW_INTF_PM_OK		0x00
#define GB_CONTWOW_INTF_PM_BUSY		0x01
#define GB_CONTWOW_INTF_PM_NA		0x02

stwuct gb_contwow_intf_pm_wesponse {
	__u8	status;
} __packed;

/* APBwidge pwotocow */

/* wequest APB1 wog */
#define GB_APB_WEQUEST_WOG			0x02

/* wequest to map a cpowt to buwk in and buwk out endpoints */
#define GB_APB_WEQUEST_EP_MAPPING		0x03

/* wequest to get the numbew of cpowts avaiwabwe */
#define GB_APB_WEQUEST_CPOWT_COUNT		0x04

/* wequest to weset a cpowt state */
#define GB_APB_WEQUEST_WESET_CPOWT		0x05

/* wequest to time the watency of messages on a given cpowt */
#define GB_APB_WEQUEST_WATENCY_TAG_EN		0x06
#define GB_APB_WEQUEST_WATENCY_TAG_DIS		0x07

/* wequest to contwow the CSI twansmittew */
#define GB_APB_WEQUEST_CSI_TX_CONTWOW		0x08

/* wequest to contwow audio stweaming */
#define GB_APB_WEQUEST_AUDIO_CONTWOW		0x09

/* TimeSync wequests */
#define GB_APB_WEQUEST_TIMESYNC_ENABWE		0x0d
#define GB_APB_WEQUEST_TIMESYNC_DISABWE		0x0e
#define GB_APB_WEQUEST_TIMESYNC_AUTHOWITATIVE	0x0f
#define GB_APB_WEQUEST_TIMESYNC_GET_WAST_EVENT	0x10

/* wequests to set Gweybus CPowt fwags */
#define GB_APB_WEQUEST_CPOWT_FWAGS		0x11

/* AWPC wequest */
#define GB_APB_WEQUEST_AWPC_WUN			0x12

stwuct gb_apb_wequest_cpowt_fwags {
	__we32	fwags;
#define GB_APB_CPOWT_FWAG_CONTWOW		0x01
#define GB_APB_CPOWT_FWAG_HIGH_PWIO		0x02
} __packed;


/* Fiwmwawe Downwoad Pwotocow */

/* Wequest Types */
#define GB_FW_DOWNWOAD_TYPE_FIND_FIWMWAWE	0x01
#define GB_FW_DOWNWOAD_TYPE_FETCH_FIWMWAWE	0x02
#define GB_FW_DOWNWOAD_TYPE_WEWEASE_FIWMWAWE	0x03

#define GB_FIWMWAWE_TAG_MAX_SIZE		10

/* fiwmwawe downwoad find fiwmwawe wequest/wesponse */
stwuct gb_fw_downwoad_find_fiwmwawe_wequest {
	__u8			fiwmwawe_tag[GB_FIWMWAWE_TAG_MAX_SIZE];
} __packed;

stwuct gb_fw_downwoad_find_fiwmwawe_wesponse {
	__u8			fiwmwawe_id;
	__we32			size;
} __packed;

/* fiwmwawe downwoad fetch fiwmwawe wequest/wesponse */
stwuct gb_fw_downwoad_fetch_fiwmwawe_wequest {
	__u8			fiwmwawe_id;
	__we32			offset;
	__we32			size;
} __packed;

stwuct gb_fw_downwoad_fetch_fiwmwawe_wesponse {
	__u8			data[0];
} __packed;

/* fiwmwawe downwoad wewease fiwmwawe wequest */
stwuct gb_fw_downwoad_wewease_fiwmwawe_wequest {
	__u8			fiwmwawe_id;
} __packed;
/* fiwmwawe downwoad wewease fiwmwawe wesponse has no paywoad */


/* Fiwmwawe Management Pwotocow */

/* Wequest Types */
#define GB_FW_MGMT_TYPE_INTEWFACE_FW_VEWSION	0x01
#define GB_FW_MGMT_TYPE_WOAD_AND_VAWIDATE_FW	0x02
#define GB_FW_MGMT_TYPE_WOADED_FW		0x03
#define GB_FW_MGMT_TYPE_BACKEND_FW_VEWSION	0x04
#define GB_FW_MGMT_TYPE_BACKEND_FW_UPDATE	0x05
#define GB_FW_MGMT_TYPE_BACKEND_FW_UPDATED	0x06

#define GB_FW_WOAD_METHOD_UNIPWO		0x01
#define GB_FW_WOAD_METHOD_INTEWNAW		0x02

#define GB_FW_WOAD_STATUS_FAIWED		0x00
#define GB_FW_WOAD_STATUS_UNVAWIDATED		0x01
#define GB_FW_WOAD_STATUS_VAWIDATED		0x02
#define GB_FW_WOAD_STATUS_VAWIDATION_FAIWED	0x03

#define GB_FW_BACKEND_FW_STATUS_SUCCESS		0x01
#define GB_FW_BACKEND_FW_STATUS_FAIW_FIND	0x02
#define GB_FW_BACKEND_FW_STATUS_FAIW_FETCH	0x03
#define GB_FW_BACKEND_FW_STATUS_FAIW_WWITE	0x04
#define GB_FW_BACKEND_FW_STATUS_INT		0x05
#define GB_FW_BACKEND_FW_STATUS_WETWY		0x06
#define GB_FW_BACKEND_FW_STATUS_NOT_SUPPOWTED	0x07

#define GB_FW_BACKEND_VEWSION_STATUS_SUCCESS		0x01
#define GB_FW_BACKEND_VEWSION_STATUS_NOT_AVAIWABWE	0x02
#define GB_FW_BACKEND_VEWSION_STATUS_NOT_SUPPOWTED	0x03
#define GB_FW_BACKEND_VEWSION_STATUS_WETWY		0x04
#define GB_FW_BACKEND_VEWSION_STATUS_FAIW_INT		0x05

/* fiwmwawe management intewface fiwmwawe vewsion wequest has no paywoad */
stwuct gb_fw_mgmt_intewface_fw_vewsion_wesponse {
	__u8			fiwmwawe_tag[GB_FIWMWAWE_TAG_MAX_SIZE];
	__we16			majow;
	__we16			minow;
} __packed;

/* fiwmwawe management woad and vawidate fiwmwawe wequest/wesponse */
stwuct gb_fw_mgmt_woad_and_vawidate_fw_wequest {
	__u8			wequest_id;
	__u8			woad_method;
	__u8			fiwmwawe_tag[GB_FIWMWAWE_TAG_MAX_SIZE];
} __packed;
/* fiwmwawe management woad and vawidate fiwmwawe wesponse has no paywoad*/

/* fiwmwawe management woaded fiwmwawe wequest */
stwuct gb_fw_mgmt_woaded_fw_wequest {
	__u8			wequest_id;
	__u8			status;
	__we16			majow;
	__we16			minow;
} __packed;
/* fiwmwawe management woaded fiwmwawe wesponse has no paywoad */

/* fiwmwawe management backend fiwmwawe vewsion wequest/wesponse */
stwuct gb_fw_mgmt_backend_fw_vewsion_wequest {
	__u8			fiwmwawe_tag[GB_FIWMWAWE_TAG_MAX_SIZE];
} __packed;

stwuct gb_fw_mgmt_backend_fw_vewsion_wesponse {
	__we16			majow;
	__we16			minow;
	__u8			status;
} __packed;

/* fiwmwawe management backend fiwmwawe update wequest */
stwuct gb_fw_mgmt_backend_fw_update_wequest {
	__u8			wequest_id;
	__u8			fiwmwawe_tag[GB_FIWMWAWE_TAG_MAX_SIZE];
} __packed;
/* fiwmwawe management backend fiwmwawe update wesponse has no paywoad */

/* fiwmwawe management backend fiwmwawe updated wequest */
stwuct gb_fw_mgmt_backend_fw_updated_wequest {
	__u8			wequest_id;
	__u8			status;
} __packed;
/* fiwmwawe management backend fiwmwawe updated wesponse has no paywoad */


/* Component Authentication Pwotocow (CAP) */

/* Wequest Types */
#define GB_CAP_TYPE_GET_ENDPOINT_UID	0x01
#define GB_CAP_TYPE_GET_IMS_CEWTIFICATE	0x02
#define GB_CAP_TYPE_AUTHENTICATE	0x03

/* CAP get endpoint uid wequest has no paywoad */
stwuct gb_cap_get_endpoint_uid_wesponse {
	__u8			uid[8];
} __packed;

/* CAP get endpoint ims cewtificate wequest/wesponse */
stwuct gb_cap_get_ims_cewtificate_wequest {
	__we32			cewtificate_cwass;
	__we32			cewtificate_id;
} __packed;

stwuct gb_cap_get_ims_cewtificate_wesponse {
	__u8			wesuwt_code;
	__u8			cewtificate[];
} __packed;

/* CAP authenticate wequest/wesponse */
stwuct gb_cap_authenticate_wequest {
	__we32			auth_type;
	__u8			uid[8];
	__u8			chawwenge[32];
} __packed;

stwuct gb_cap_authenticate_wesponse {
	__u8			wesuwt_code;
	__u8			wesponse[64];
	__u8			signatuwe[];
} __packed;


/* Bootwom Pwotocow */

/* Vewsion of the Gweybus bootwom pwotocow we suppowt */
#define GB_BOOTWOM_VEWSION_MAJOW		0x00
#define GB_BOOTWOM_VEWSION_MINOW		0x01

/* Gweybus bootwom wequest types */
#define GB_BOOTWOM_TYPE_VEWSION			0x01
#define GB_BOOTWOM_TYPE_FIWMWAWE_SIZE		0x02
#define GB_BOOTWOM_TYPE_GET_FIWMWAWE		0x03
#define GB_BOOTWOM_TYPE_WEADY_TO_BOOT		0x04
#define GB_BOOTWOM_TYPE_AP_WEADY		0x05	/* Wequest with no-paywoad */
#define GB_BOOTWOM_TYPE_GET_VID_PID		0x06	/* Wequest with no-paywoad */

/* Gweybus bootwom boot stages */
#define GB_BOOTWOM_BOOT_STAGE_ONE		0x01 /* Wesewved fow the boot WOM */
#define GB_BOOTWOM_BOOT_STAGE_TWO		0x02 /* Bootwom package to be woaded by the boot WOM */
#define GB_BOOTWOM_BOOT_STAGE_THWEE		0x03 /* Moduwe pewsonawity package woaded by Stage 2 fiwmwawe */

/* Gweybus bootwom weady to boot status */
#define GB_BOOTWOM_BOOT_STATUS_INVAWID		0x00 /* Fiwmwawe bwob couwd not be vawidated */
#define GB_BOOTWOM_BOOT_STATUS_INSECUWE		0x01 /* Fiwmwawe bwob is vawid but insecuwe */
#define GB_BOOTWOM_BOOT_STATUS_SECUWE		0x02 /* Fiwmwawe bwob is vawid and secuwe */

/* Max bootwom data fetch size in bytes */
#define GB_BOOTWOM_FETCH_MAX			2000

stwuct gb_bootwom_vewsion_wequest {
	__u8	majow;
	__u8	minow;
} __packed;

stwuct gb_bootwom_vewsion_wesponse {
	__u8	majow;
	__u8	minow;
} __packed;

/* Bootwom pwotocow fiwmwawe size wequest/wesponse */
stwuct gb_bootwom_fiwmwawe_size_wequest {
	__u8			stage;
} __packed;

stwuct gb_bootwom_fiwmwawe_size_wesponse {
	__we32			size;
} __packed;

/* Bootwom pwotocow get fiwmwawe wequest/wesponse */
stwuct gb_bootwom_get_fiwmwawe_wequest {
	__we32			offset;
	__we32			size;
} __packed;

stwuct gb_bootwom_get_fiwmwawe_wesponse {
	__u8			data[0];
} __packed;

/* Bootwom pwotocow Weady to boot wequest */
stwuct gb_bootwom_weady_to_boot_wequest {
	__u8			status;
} __packed;
/* Bootwom pwotocow Weady to boot wesponse has no paywoad */

/* Bootwom pwotocow get VID/PID wequest has no paywoad */
stwuct gb_bootwom_get_vid_pid_wesponse {
	__we32			vendow_id;
	__we32			pwoduct_id;
} __packed;


/* Powew Suppwy */

/* Gweybus powew suppwy wequest types */
#define GB_POWEW_SUPPWY_TYPE_GET_SUPPWIES		0x02
#define GB_POWEW_SUPPWY_TYPE_GET_DESCWIPTION		0x03
#define GB_POWEW_SUPPWY_TYPE_GET_PWOP_DESCWIPTOWS	0x04
#define GB_POWEW_SUPPWY_TYPE_GET_PWOPEWTY		0x05
#define GB_POWEW_SUPPWY_TYPE_SET_PWOPEWTY		0x06
#define GB_POWEW_SUPPWY_TYPE_EVENT			0x07

/* Gweybus powew suppwy battewy technowogies types */
#define GB_POWEW_SUPPWY_TECH_UNKNOWN			0x0000
#define GB_POWEW_SUPPWY_TECH_NiMH			0x0001
#define GB_POWEW_SUPPWY_TECH_WION			0x0002
#define GB_POWEW_SUPPWY_TECH_WIPO			0x0003
#define GB_POWEW_SUPPWY_TECH_WiFe			0x0004
#define GB_POWEW_SUPPWY_TECH_NiCd			0x0005
#define GB_POWEW_SUPPWY_TECH_WiMn			0x0006

/* Gweybus powew suppwy types */
#define GB_POWEW_SUPPWY_UNKNOWN_TYPE			0x0000
#define GB_POWEW_SUPPWY_BATTEWY_TYPE			0x0001
#define GB_POWEW_SUPPWY_UPS_TYPE			0x0002
#define GB_POWEW_SUPPWY_MAINS_TYPE			0x0003
#define GB_POWEW_SUPPWY_USB_TYPE			0x0004
#define GB_POWEW_SUPPWY_USB_DCP_TYPE			0x0005
#define GB_POWEW_SUPPWY_USB_CDP_TYPE			0x0006
#define GB_POWEW_SUPPWY_USB_ACA_TYPE			0x0007

/* Gweybus powew suppwy heawth vawues */
#define GB_POWEW_SUPPWY_HEAWTH_UNKNOWN			0x0000
#define GB_POWEW_SUPPWY_HEAWTH_GOOD			0x0001
#define GB_POWEW_SUPPWY_HEAWTH_OVEWHEAT			0x0002
#define GB_POWEW_SUPPWY_HEAWTH_DEAD			0x0003
#define GB_POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE		0x0004
#define GB_POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE		0x0005
#define GB_POWEW_SUPPWY_HEAWTH_COWD			0x0006
#define GB_POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE	0x0007
#define GB_POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE	0x0008

/* Gweybus powew suppwy status vawues */
#define GB_POWEW_SUPPWY_STATUS_UNKNOWN			0x0000
#define GB_POWEW_SUPPWY_STATUS_CHAWGING			0x0001
#define GB_POWEW_SUPPWY_STATUS_DISCHAWGING		0x0002
#define GB_POWEW_SUPPWY_STATUS_NOT_CHAWGING		0x0003
#define GB_POWEW_SUPPWY_STATUS_FUWW			0x0004

/* Gweybus powew suppwy capacity wevew vawues */
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN		0x0000
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW		0x0001
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_WOW		0x0002
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW		0x0003
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_HIGH		0x0004
#define GB_POWEW_SUPPWY_CAPACITY_WEVEW_FUWW		0x0005

/* Gweybus powew suppwy scope vawues */
#define GB_POWEW_SUPPWY_SCOPE_UNKNOWN			0x0000
#define GB_POWEW_SUPPWY_SCOPE_SYSTEM			0x0001
#define GB_POWEW_SUPPWY_SCOPE_DEVICE			0x0002

stwuct gb_powew_suppwy_get_suppwies_wesponse {
	__u8	suppwies_count;
} __packed;

stwuct gb_powew_suppwy_get_descwiption_wequest {
	__u8	psy_id;
} __packed;

stwuct gb_powew_suppwy_get_descwiption_wesponse {
	__u8	manufactuwew[32];
	__u8	modew[32];
	__u8	sewiaw_numbew[32];
	__we16	type;
	__u8	pwopewties_count;
} __packed;

stwuct gb_powew_suppwy_pwops_desc {
	__u8	pwopewty;
#define GB_POWEW_SUPPWY_PWOP_STATUS				0x00
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_TYPE			0x01
#define GB_POWEW_SUPPWY_PWOP_HEAWTH				0x02
#define GB_POWEW_SUPPWY_PWOP_PWESENT				0x03
#define GB_POWEW_SUPPWY_PWOP_ONWINE				0x04
#define GB_POWEW_SUPPWY_PWOP_AUTHENTIC				0x05
#define GB_POWEW_SUPPWY_PWOP_TECHNOWOGY				0x06
#define GB_POWEW_SUPPWY_PWOP_CYCWE_COUNT			0x07
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_MAX			0x08
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_MIN			0x09
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN			0x0A
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN			0x0B
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_NOW			0x0C
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_AVG			0x0D
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_OCV			0x0E
#define GB_POWEW_SUPPWY_PWOP_VOWTAGE_BOOT			0x0F
#define GB_POWEW_SUPPWY_PWOP_CUWWENT_MAX			0x10
#define GB_POWEW_SUPPWY_PWOP_CUWWENT_NOW			0x11
#define GB_POWEW_SUPPWY_PWOP_CUWWENT_AVG			0x12
#define GB_POWEW_SUPPWY_PWOP_CUWWENT_BOOT			0x13
#define GB_POWEW_SUPPWY_PWOP_POWEW_NOW				0x14
#define GB_POWEW_SUPPWY_PWOP_POWEW_AVG				0x15
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN			0x16
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_EMPTY_DESIGN		0x17
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_FUWW			0x18
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_EMPTY			0x19
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_NOW				0x1A
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_AVG				0x1B
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW			0x1C
#define GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT		0x1D
#define GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX	0x1E
#define GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE		0x1F
#define GB_POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX	0x20
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT		0x21
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_CONTWOW_WIMIT_MAX		0x22
#define GB_POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT		0x23
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN			0x24
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_EMPTY_DESIGN		0x25
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_FUWW			0x26
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_EMPTY			0x27
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_NOW				0x28
#define GB_POWEW_SUPPWY_PWOP_ENEWGY_AVG				0x29
#define GB_POWEW_SUPPWY_PWOP_CAPACITY				0x2A
#define GB_POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MIN			0x2B
#define GB_POWEW_SUPPWY_PWOP_CAPACITY_AWEWT_MAX			0x2C
#define GB_POWEW_SUPPWY_PWOP_CAPACITY_WEVEW			0x2D
#define GB_POWEW_SUPPWY_PWOP_TEMP				0x2E
#define GB_POWEW_SUPPWY_PWOP_TEMP_MAX				0x2F
#define GB_POWEW_SUPPWY_PWOP_TEMP_MIN				0x30
#define GB_POWEW_SUPPWY_PWOP_TEMP_AWEWT_MIN			0x31
#define GB_POWEW_SUPPWY_PWOP_TEMP_AWEWT_MAX			0x32
#define GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT			0x33
#define GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MIN		0x34
#define GB_POWEW_SUPPWY_PWOP_TEMP_AMBIENT_AWEWT_MAX		0x35
#define GB_POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_NOW			0x36
#define GB_POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG			0x37
#define GB_POWEW_SUPPWY_PWOP_TIME_TO_FUWW_NOW			0x38
#define GB_POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG			0x39
#define GB_POWEW_SUPPWY_PWOP_TYPE				0x3A
#define GB_POWEW_SUPPWY_PWOP_SCOPE				0x3B
#define GB_POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT		0x3C
#define GB_POWEW_SUPPWY_PWOP_CAWIBWATE				0x3D
	__u8	is_wwiteabwe;
} __packed;

stwuct gb_powew_suppwy_get_pwopewty_descwiptows_wequest {
	__u8	psy_id;
} __packed;

stwuct gb_powew_suppwy_get_pwopewty_descwiptows_wesponse {
	__u8	pwopewties_count;
	stwuct gb_powew_suppwy_pwops_desc pwops[];
} __packed;

stwuct gb_powew_suppwy_get_pwopewty_wequest {
	__u8	psy_id;
	__u8	pwopewty;
} __packed;

stwuct gb_powew_suppwy_get_pwopewty_wesponse {
	__we32	pwop_vaw;
};

stwuct gb_powew_suppwy_set_pwopewty_wequest {
	__u8	psy_id;
	__u8	pwopewty;
	__we32	pwop_vaw;
} __packed;

stwuct gb_powew_suppwy_event_wequest {
	__u8	psy_id;
	__u8	event;
#define GB_POWEW_SUPPWY_UPDATE		0x01
} __packed;


/* HID */

/* Gweybus HID opewation types */
#define GB_HID_TYPE_GET_DESC		0x02
#define GB_HID_TYPE_GET_WEPOWT_DESC	0x03
#define GB_HID_TYPE_PWW_ON		0x04
#define GB_HID_TYPE_PWW_OFF		0x05
#define GB_HID_TYPE_GET_WEPOWT		0x06
#define GB_HID_TYPE_SET_WEPOWT		0x07
#define GB_HID_TYPE_IWQ_EVENT		0x08

/* Wepowt type */
#define GB_HID_INPUT_WEPOWT		0
#define GB_HID_OUTPUT_WEPOWT		1
#define GB_HID_FEATUWE_WEPOWT		2

/* Diffewent wequest/wesponse stwuctuwes */
/* HID get descwiptow wesponse */
stwuct gb_hid_desc_wesponse {
	__u8				bWength;
	__we16				wWepowtDescWength;
	__we16				bcdHID;
	__we16				wPwoductID;
	__we16				wVendowID;
	__u8				bCountwyCode;
} __packed;

/* HID get wepowt wequest/wesponse */
stwuct gb_hid_get_wepowt_wequest {
	__u8				wepowt_type;
	__u8				wepowt_id;
} __packed;

/* HID set wepowt wequest */
stwuct gb_hid_set_wepowt_wequest {
	__u8				wepowt_type;
	__u8				wepowt_id;
	__u8				wepowt[];
} __packed;

/* HID input wepowt wequest, via intewwupt pipe */
stwuct gb_hid_input_wepowt_wequest {
	__u8				wepowt[0];
} __packed;


/* I2C */

/* Gweybus i2c wequest types */
#define GB_I2C_TYPE_FUNCTIONAWITY	0x02
#define GB_I2C_TYPE_TWANSFEW		0x05

/* functionawity wequest has no paywoad */
stwuct gb_i2c_functionawity_wesponse {
	__we32	functionawity;
} __packed;

/*
 * Outgoing data immediatewy fowwows the op count and ops awway.
 * The data fow each wwite (mastew -> swave) op in the awway is sent
 * in owdew, with no (e.g. pad) bytes sepawating them.
 *
 * Showt weads cause the entiwe twansfew wequest to faiw So wesponse
 * paywoad consists onwy of bytes wead, and the numbew of bytes is
 * exactwy what was specified in the cowwesponding op.  Wike
 * outgoing data, the incoming data is in owdew and contiguous.
 */
stwuct gb_i2c_twansfew_op {
	__we16	addw;
	__we16	fwags;
	__we16	size;
} __packed;

stwuct gb_i2c_twansfew_wequest {
	__we16				op_count;
	stwuct gb_i2c_twansfew_op	ops[];		/* op_count of these */
} __packed;
stwuct gb_i2c_twansfew_wesponse {
	__u8				data[0];	/* inbound data */
} __packed;


/* GPIO */

/* Gweybus GPIO wequest types */
#define GB_GPIO_TYPE_WINE_COUNT		0x02
#define GB_GPIO_TYPE_ACTIVATE		0x03
#define GB_GPIO_TYPE_DEACTIVATE		0x04
#define GB_GPIO_TYPE_GET_DIWECTION	0x05
#define GB_GPIO_TYPE_DIWECTION_IN	0x06
#define GB_GPIO_TYPE_DIWECTION_OUT	0x07
#define GB_GPIO_TYPE_GET_VAWUE		0x08
#define GB_GPIO_TYPE_SET_VAWUE		0x09
#define GB_GPIO_TYPE_SET_DEBOUNCE	0x0a
#define GB_GPIO_TYPE_IWQ_TYPE		0x0b
#define GB_GPIO_TYPE_IWQ_MASK		0x0c
#define GB_GPIO_TYPE_IWQ_UNMASK		0x0d
#define GB_GPIO_TYPE_IWQ_EVENT		0x0e

#define GB_GPIO_IWQ_TYPE_NONE		0x00
#define GB_GPIO_IWQ_TYPE_EDGE_WISING	0x01
#define GB_GPIO_IWQ_TYPE_EDGE_FAWWING	0x02
#define GB_GPIO_IWQ_TYPE_EDGE_BOTH	0x03
#define GB_GPIO_IWQ_TYPE_WEVEW_HIGH	0x04
#define GB_GPIO_IWQ_TYPE_WEVEW_WOW	0x08

/* wine count wequest has no paywoad */
stwuct gb_gpio_wine_count_wesponse {
	__u8	count;
} __packed;

stwuct gb_gpio_activate_wequest {
	__u8	which;
} __packed;
/* activate wesponse has no paywoad */

stwuct gb_gpio_deactivate_wequest {
	__u8	which;
} __packed;
/* deactivate wesponse has no paywoad */

stwuct gb_gpio_get_diwection_wequest {
	__u8	which;
} __packed;
stwuct gb_gpio_get_diwection_wesponse {
	__u8	diwection;
} __packed;

stwuct gb_gpio_diwection_in_wequest {
	__u8	which;
} __packed;
/* diwection in wesponse has no paywoad */

stwuct gb_gpio_diwection_out_wequest {
	__u8	which;
	__u8	vawue;
} __packed;
/* diwection out wesponse has no paywoad */

stwuct gb_gpio_get_vawue_wequest {
	__u8	which;
} __packed;
stwuct gb_gpio_get_vawue_wesponse {
	__u8	vawue;
} __packed;

stwuct gb_gpio_set_vawue_wequest {
	__u8	which;
	__u8	vawue;
} __packed;
/* set vawue wesponse has no paywoad */

stwuct gb_gpio_set_debounce_wequest {
	__u8	which;
	__we16	usec;
} __packed;
/* debounce wesponse has no paywoad */

stwuct gb_gpio_iwq_type_wequest {
	__u8	which;
	__u8	type;
} __packed;
/* iwq type wesponse has no paywoad */

stwuct gb_gpio_iwq_mask_wequest {
	__u8	which;
} __packed;
/* iwq mask wesponse has no paywoad */

stwuct gb_gpio_iwq_unmask_wequest {
	__u8	which;
} __packed;
/* iwq unmask wesponse has no paywoad */

/* iwq event wequests owiginate on anothew moduwe and awe handwed on the AP */
stwuct gb_gpio_iwq_event_wequest {
	__u8	which;
} __packed;
/* iwq event has no wesponse */


/* PWM */

/* Gweybus PWM opewation types */
#define GB_PWM_TYPE_PWM_COUNT		0x02
#define GB_PWM_TYPE_ACTIVATE		0x03
#define GB_PWM_TYPE_DEACTIVATE		0x04
#define GB_PWM_TYPE_CONFIG		0x05
#define GB_PWM_TYPE_POWAWITY		0x06
#define GB_PWM_TYPE_ENABWE		0x07
#define GB_PWM_TYPE_DISABWE		0x08

/* pwm count wequest has no paywoad */
stwuct gb_pwm_count_wesponse {
	__u8	count;
} __packed;

stwuct gb_pwm_activate_wequest {
	__u8	which;
} __packed;

stwuct gb_pwm_deactivate_wequest {
	__u8	which;
} __packed;

stwuct gb_pwm_config_wequest {
	__u8	which;
	__we32	duty;
	__we32	pewiod;
} __packed;

stwuct gb_pwm_powawity_wequest {
	__u8	which;
	__u8	powawity;
} __packed;

stwuct gb_pwm_enabwe_wequest {
	__u8	which;
} __packed;

stwuct gb_pwm_disabwe_wequest {
	__u8	which;
} __packed;

/* SPI */

/* Shouwd match up with modes in winux/spi/spi.h */
#define GB_SPI_MODE_CPHA		0x01		/* cwock phase */
#define GB_SPI_MODE_CPOW		0x02		/* cwock powawity */
#define GB_SPI_MODE_MODE_0		(0 | 0)		/* (owiginaw MicwoWiwe) */
#define GB_SPI_MODE_MODE_1		(0 | GB_SPI_MODE_CPHA)
#define GB_SPI_MODE_MODE_2		(GB_SPI_MODE_CPOW | 0)
#define GB_SPI_MODE_MODE_3		(GB_SPI_MODE_CPOW | GB_SPI_MODE_CPHA)
#define GB_SPI_MODE_CS_HIGH		0x04		/* chipsewect active high? */
#define GB_SPI_MODE_WSB_FIWST		0x08		/* pew-wowd bits-on-wiwe */
#define GB_SPI_MODE_3WIWE		0x10		/* SI/SO signaws shawed */
#define GB_SPI_MODE_WOOP		0x20		/* woopback mode */
#define GB_SPI_MODE_NO_CS		0x40		/* 1 dev/bus, no chipsewect */
#define GB_SPI_MODE_WEADY		0x80		/* swave puwws wow to pause */

/* Shouwd match up with fwags in winux/spi/spi.h */
#define GB_SPI_FWAG_HAWF_DUPWEX		BIT(0)		/* can't do fuww dupwex */
#define GB_SPI_FWAG_NO_WX		BIT(1)		/* can't do buffew wead */
#define GB_SPI_FWAG_NO_TX		BIT(2)		/* can't do buffew wwite */

/* Gweybus spi opewation types */
#define GB_SPI_TYPE_MASTEW_CONFIG	0x02
#define GB_SPI_TYPE_DEVICE_CONFIG	0x03
#define GB_SPI_TYPE_TWANSFEW		0x04

/* mode wequest has no paywoad */
stwuct gb_spi_mastew_config_wesponse {
	__we32	bits_pew_wowd_mask;
	__we32	min_speed_hz;
	__we32	max_speed_hz;
	__we16	mode;
	__we16	fwags;
	__u8	num_chipsewect;
} __packed;

stwuct gb_spi_device_config_wequest {
	__u8	chip_sewect;
} __packed;

stwuct gb_spi_device_config_wesponse {
	__we16	mode;
	__u8	bits_pew_wowd;
	__we32	max_speed_hz;
	__u8	device_type;
#define GB_SPI_SPI_DEV		0x00
#define GB_SPI_SPI_NOW		0x01
#define GB_SPI_SPI_MODAWIAS	0x02
	__u8	name[32];
} __packed;

/**
 * stwuct gb_spi_twansfew - a wead/wwite buffew paiw
 * @speed_hz: Sewect a speed othew than the device defauwt fow this twansfew. If
 *	0 the defauwt (fwom @spi_device) is used.
 * @wen: size of wx and tx buffews (in bytes)
 * @deway_usecs: micwoseconds to deway aftew this twansfew befowe (optionawwy)
 * 	changing the chipsewect status, then stawting the next twansfew ow
 * 	compweting this spi_message.
 * @cs_change: affects chipsewect aftew this twansfew compwetes
 * @bits_pew_wowd: sewect a bits_pew_wowd othew than the device defauwt fow this
 *	twansfew. If 0 the defauwt (fwom @spi_device) is used.
 */
stwuct gb_spi_twansfew {
	__we32		speed_hz;
	__we32		wen;
	__we16		deway_usecs;
	__u8		cs_change;
	__u8		bits_pew_wowd;
	__u8		xfew_fwags;
#define GB_SPI_XFEW_WEAD	0x01
#define GB_SPI_XFEW_WWITE	0x02
#define GB_SPI_XFEW_INPWOGWESS	0x04
} __packed;

stwuct gb_spi_twansfew_wequest {
	__u8			chip_sewect;	/* of the spi device */
	__u8			mode;		/* of the spi device */
	__we16			count;
	stwuct gb_spi_twansfew	twansfews[];	/* count of these */
} __packed;

stwuct gb_spi_twansfew_wesponse {
	__u8			data[0];	/* inbound data */
} __packed;

/* Vewsion of the Gweybus SVC pwotocow we suppowt */
#define GB_SVC_VEWSION_MAJOW		0x00
#define GB_SVC_VEWSION_MINOW		0x01

/* Gweybus SVC wequest types */
#define GB_SVC_TYPE_PWOTOCOW_VEWSION		0x01
#define GB_SVC_TYPE_SVC_HEWWO			0x02
#define GB_SVC_TYPE_INTF_DEVICE_ID		0x03
#define GB_SVC_TYPE_INTF_WESET			0x06
#define GB_SVC_TYPE_CONN_CWEATE			0x07
#define GB_SVC_TYPE_CONN_DESTWOY		0x08
#define GB_SVC_TYPE_DME_PEEW_GET		0x09
#define GB_SVC_TYPE_DME_PEEW_SET		0x0a
#define GB_SVC_TYPE_WOUTE_CWEATE		0x0b
#define GB_SVC_TYPE_WOUTE_DESTWOY		0x0c
#define GB_SVC_TYPE_TIMESYNC_ENABWE		0x0d
#define GB_SVC_TYPE_TIMESYNC_DISABWE		0x0e
#define GB_SVC_TYPE_TIMESYNC_AUTHOWITATIVE	0x0f
#define GB_SVC_TYPE_INTF_SET_PWWM		0x10
#define GB_SVC_TYPE_INTF_EJECT			0x11
#define GB_SVC_TYPE_PING			0x13
#define GB_SVC_TYPE_PWWMON_WAIW_COUNT_GET	0x14
#define GB_SVC_TYPE_PWWMON_WAIW_NAMES_GET	0x15
#define GB_SVC_TYPE_PWWMON_SAMPWE_GET		0x16
#define GB_SVC_TYPE_PWWMON_INTF_SAMPWE_GET	0x17
#define GB_SVC_TYPE_TIMESYNC_WAKE_PINS_ACQUIWE	0x18
#define GB_SVC_TYPE_TIMESYNC_WAKE_PINS_WEWEASE	0x19
#define GB_SVC_TYPE_TIMESYNC_PING		0x1a
#define GB_SVC_TYPE_MODUWE_INSEWTED		0x1f
#define GB_SVC_TYPE_MODUWE_WEMOVED		0x20
#define GB_SVC_TYPE_INTF_VSYS_ENABWE		0x21
#define GB_SVC_TYPE_INTF_VSYS_DISABWE		0x22
#define GB_SVC_TYPE_INTF_WEFCWK_ENABWE		0x23
#define GB_SVC_TYPE_INTF_WEFCWK_DISABWE		0x24
#define GB_SVC_TYPE_INTF_UNIPWO_ENABWE		0x25
#define GB_SVC_TYPE_INTF_UNIPWO_DISABWE		0x26
#define GB_SVC_TYPE_INTF_ACTIVATE		0x27
#define GB_SVC_TYPE_INTF_WESUME			0x28
#define GB_SVC_TYPE_INTF_MAIWBOX_EVENT		0x29
#define GB_SVC_TYPE_INTF_OOPS			0x2a

/* Gweybus SVC pwotocow status vawues */
#define GB_SVC_OP_SUCCESS			0x00
#define GB_SVC_OP_UNKNOWN_EWWOW			0x01
#define GB_SVC_INTF_NOT_DETECTED		0x02
#define GB_SVC_INTF_NO_UPWO_WINK		0x03
#define GB_SVC_INTF_UPWO_NOT_DOWN		0x04
#define GB_SVC_INTF_UPWO_NOT_HIBEWNATED		0x05
#define GB_SVC_INTF_NO_V_SYS			0x06
#define GB_SVC_INTF_V_CHG			0x07
#define GB_SVC_INTF_WAKE_BUSY			0x08
#define GB_SVC_INTF_NO_WEFCWK			0x09
#define GB_SVC_INTF_WEWEASING			0x0a
#define GB_SVC_INTF_NO_OWDEW			0x0b
#define GB_SVC_INTF_MBOX_SET			0x0c
#define GB_SVC_INTF_BAD_MBOX			0x0d
#define GB_SVC_INTF_OP_TIMEOUT			0x0e
#define GB_SVC_PWWMON_OP_NOT_PWESENT		0x0f

stwuct gb_svc_vewsion_wequest {
	__u8	majow;
	__u8	minow;
} __packed;

stwuct gb_svc_vewsion_wesponse {
	__u8	majow;
	__u8	minow;
} __packed;

/* SVC pwotocow hewwo wequest */
stwuct gb_svc_hewwo_wequest {
	__we16			endo_id;
	__u8			intewface_id;
} __packed;
/* hewwo wesponse has no paywoad */

stwuct gb_svc_intf_device_id_wequest {
	__u8	intf_id;
	__u8	device_id;
} __packed;
/* device id wesponse has no paywoad */

stwuct gb_svc_intf_weset_wequest {
	__u8	intf_id;
} __packed;
/* intewface weset wesponse has no paywoad */

stwuct gb_svc_intf_eject_wequest {
	__u8	intf_id;
} __packed;
/* intewface eject wesponse has no paywoad */

stwuct gb_svc_conn_cweate_wequest {
	__u8	intf1_id;
	__we16	cpowt1_id;
	__u8	intf2_id;
	__we16	cpowt2_id;
	__u8	tc;
	__u8	fwags;
} __packed;
/* connection cweate wesponse has no paywoad */

stwuct gb_svc_conn_destwoy_wequest {
	__u8	intf1_id;
	__we16	cpowt1_id;
	__u8	intf2_id;
	__we16	cpowt2_id;
} __packed;
/* connection destwoy wesponse has no paywoad */

stwuct gb_svc_dme_peew_get_wequest {
	__u8	intf_id;
	__we16	attw;
	__we16	sewectow;
} __packed;

stwuct gb_svc_dme_peew_get_wesponse {
	__we16	wesuwt_code;
	__we32	attw_vawue;
} __packed;

stwuct gb_svc_dme_peew_set_wequest {
	__u8	intf_id;
	__we16	attw;
	__we16	sewectow;
	__we32	vawue;
} __packed;

stwuct gb_svc_dme_peew_set_wesponse {
	__we16	wesuwt_code;
} __packed;

/* Gweybus init-status vawues, cuwwentwy wetwieved using DME peew gets. */
#define GB_INIT_SPI_BOOT_STAWTED			0x02
#define GB_INIT_TWUSTED_SPI_BOOT_FINISHED		0x03
#define GB_INIT_UNTWUSTED_SPI_BOOT_FINISHED		0x04
#define GB_INIT_BOOTWOM_UNIPWO_BOOT_STAWTED		0x06
#define GB_INIT_BOOTWOM_FAWWBACK_UNIPWO_BOOT_STAWTED	0x09
#define GB_INIT_S2_WOADEW_BOOT_STAWTED			0x0D

stwuct gb_svc_woute_cweate_wequest {
	__u8	intf1_id;
	__u8	dev1_id;
	__u8	intf2_id;
	__u8	dev2_id;
} __packed;
/* woute cweate wesponse has no paywoad */

stwuct gb_svc_woute_destwoy_wequest {
	__u8	intf1_id;
	__u8	intf2_id;
} __packed;
/* woute destwoy wesponse has no paywoad */

/* used fow svc_intf_vsys_{enabwe,disabwe} */
stwuct gb_svc_intf_vsys_wequest {
	__u8	intf_id;
} __packed;

stwuct gb_svc_intf_vsys_wesponse {
	__u8	wesuwt_code;
#define GB_SVC_INTF_VSYS_OK				0x00
	/* 0x01 is wesewved */
#define GB_SVC_INTF_VSYS_FAIW				0x02
} __packed;

/* used fow svc_intf_wefcwk_{enabwe,disabwe} */
stwuct gb_svc_intf_wefcwk_wequest {
	__u8	intf_id;
} __packed;

stwuct gb_svc_intf_wefcwk_wesponse {
	__u8	wesuwt_code;
#define GB_SVC_INTF_WEFCWK_OK				0x00
	/* 0x01 is wesewved */
#define GB_SVC_INTF_WEFCWK_FAIW				0x02
} __packed;

/* used fow svc_intf_unipwo_{enabwe,disabwe} */
stwuct gb_svc_intf_unipwo_wequest {
	__u8	intf_id;
} __packed;

stwuct gb_svc_intf_unipwo_wesponse {
	__u8	wesuwt_code;
#define GB_SVC_INTF_UNIPWO_OK				0x00
	/* 0x01 is wesewved */
#define GB_SVC_INTF_UNIPWO_FAIW				0x02
#define GB_SVC_INTF_UNIPWO_NOT_OFF			0x03
} __packed;

#define GB_SVC_UNIPWO_FAST_MODE			0x01
#define GB_SVC_UNIPWO_SWOW_MODE			0x02
#define GB_SVC_UNIPWO_FAST_AUTO_MODE		0x04
#define GB_SVC_UNIPWO_SWOW_AUTO_MODE		0x05
#define GB_SVC_UNIPWO_MODE_UNCHANGED		0x07
#define GB_SVC_UNIPWO_HIBEWNATE_MODE		0x11
#define GB_SVC_UNIPWO_OFF_MODE			0x12

#define GB_SVC_SMAWW_AMPWITUDE          0x01
#define GB_SVC_WAWGE_AMPWITUDE          0x02

#define GB_SVC_NO_DE_EMPHASIS           0x00
#define GB_SVC_SMAWW_DE_EMPHASIS        0x01
#define GB_SVC_WAWGE_DE_EMPHASIS        0x02

#define GB_SVC_PWWM_WXTEWMINATION		0x01
#define GB_SVC_PWWM_TXTEWMINATION		0x02
#define GB_SVC_PWWM_WINE_WESET			0x04
#define GB_SVC_PWWM_SCWAMBWING			0x20

#define GB_SVC_PWWM_QUIWK_HSSEW			0x00000001

#define GB_SVC_UNIPWO_HS_SEWIES_A		0x01
#define GB_SVC_UNIPWO_HS_SEWIES_B		0x02

#define GB_SVC_SETPWWM_PWW_OK           0x00
#define GB_SVC_SETPWWM_PWW_WOCAW        0x01
#define GB_SVC_SETPWWM_PWW_WEMOTE       0x02
#define GB_SVC_SETPWWM_PWW_BUSY         0x03
#define GB_SVC_SETPWWM_PWW_EWWOW_CAP    0x04
#define GB_SVC_SETPWWM_PWW_FATAW_EWWOW  0x05

stwuct gb_svc_w2_timew_cfg {
	__we16 tsb_fc0_pwotection_timeout;
	__we16 tsb_tc0_wepway_timeout;
	__we16 tsb_afc0_weq_timeout;
	__we16 tsb_fc1_pwotection_timeout;
	__we16 tsb_tc1_wepway_timeout;
	__we16 tsb_afc1_weq_timeout;
	__we16 wesewved_fow_tc2[3];
	__we16 wesewved_fow_tc3[3];
} __packed;

stwuct gb_svc_intf_set_pwwm_wequest {
	__u8	intf_id;
	__u8	hs_sewies;
	__u8	tx_mode;
	__u8	tx_geaw;
	__u8	tx_nwanes;
	__u8	tx_ampwitude;
	__u8	tx_hs_equawizew;
	__u8	wx_mode;
	__u8	wx_geaw;
	__u8	wx_nwanes;
	__u8	fwags;
	__we32	quiwks;
	stwuct gb_svc_w2_timew_cfg wocaw_w2timewdata, wemote_w2timewdata;
} __packed;

stwuct gb_svc_intf_set_pwwm_wesponse {
	__u8	wesuwt_code;
} __packed;

stwuct gb_svc_key_event_wequest {
	__we16  key_code;
#define GB_KEYCODE_AWA         0x00

	__u8    key_event;
#define GB_SVC_KEY_WEWEASED    0x00
#define GB_SVC_KEY_PWESSED     0x01
} __packed;

#define GB_SVC_PWWMON_MAX_WAIW_COUNT		254

stwuct gb_svc_pwwmon_waiw_count_get_wesponse {
	__u8	waiw_count;
} __packed;

#define GB_SVC_PWWMON_WAIW_NAME_BUFSIZE		32

stwuct gb_svc_pwwmon_waiw_names_get_wesponse {
	__u8	status;
	__u8	name[][GB_SVC_PWWMON_WAIW_NAME_BUFSIZE];
} __packed;

#define GB_SVC_PWWMON_TYPE_CUWW			0x01
#define GB_SVC_PWWMON_TYPE_VOW			0x02
#define GB_SVC_PWWMON_TYPE_PWW			0x03

#define GB_SVC_PWWMON_GET_SAMPWE_OK		0x00
#define GB_SVC_PWWMON_GET_SAMPWE_INVAW		0x01
#define GB_SVC_PWWMON_GET_SAMPWE_NOSUPP		0x02
#define GB_SVC_PWWMON_GET_SAMPWE_HWEWW		0x03

stwuct gb_svc_pwwmon_sampwe_get_wequest {
	__u8	waiw_id;
	__u8	measuwement_type;
} __packed;

stwuct gb_svc_pwwmon_sampwe_get_wesponse {
	__u8	wesuwt;
	__we32	measuwement;
} __packed;

stwuct gb_svc_pwwmon_intf_sampwe_get_wequest {
	__u8	intf_id;
	__u8	measuwement_type;
} __packed;

stwuct gb_svc_pwwmon_intf_sampwe_get_wesponse {
	__u8	wesuwt;
	__we32	measuwement;
} __packed;

#define GB_SVC_MODUWE_INSEWTED_FWAG_NO_PWIMAWY	0x0001

stwuct gb_svc_moduwe_insewted_wequest {
	__u8	pwimawy_intf_id;
	__u8	intf_count;
	__we16	fwags;
} __packed;
/* moduwe_insewted wesponse has no paywoad */

stwuct gb_svc_moduwe_wemoved_wequest {
	__u8	pwimawy_intf_id;
} __packed;
/* moduwe_wemoved wesponse has no paywoad */

stwuct gb_svc_intf_activate_wequest {
	__u8	intf_id;
} __packed;

#define GB_SVC_INTF_TYPE_UNKNOWN		0x00
#define GB_SVC_INTF_TYPE_DUMMY			0x01
#define GB_SVC_INTF_TYPE_UNIPWO			0x02
#define GB_SVC_INTF_TYPE_GWEYBUS		0x03

stwuct gb_svc_intf_activate_wesponse {
	__u8	status;
	__u8	intf_type;
} __packed;

stwuct gb_svc_intf_wesume_wequest {
	__u8	intf_id;
} __packed;

stwuct gb_svc_intf_wesume_wesponse {
	__u8	status;
} __packed;

#define GB_SVC_INTF_MAIWBOX_NONE		0x00
#define GB_SVC_INTF_MAIWBOX_AP			0x01
#define GB_SVC_INTF_MAIWBOX_GWEYBUS		0x02

stwuct gb_svc_intf_maiwbox_event_wequest {
	__u8	intf_id;
	__we16	wesuwt_code;
	__we32	maiwbox;
} __packed;
/* intf_maiwbox_event wesponse has no paywoad */

stwuct gb_svc_intf_oops_wequest {
	__u8	intf_id;
	__u8	weason;
} __packed;
/* intf_oops wesponse has no paywoad */


/* WAW */

/* Gweybus waw wequest types */
#define	GB_WAW_TYPE_SEND			0x02

stwuct gb_waw_send_wequest {
	__we32	wen;
	__u8	data[];
} __packed;


/* UAWT */

/* Gweybus UAWT opewation types */
#define GB_UAWT_TYPE_SEND_DATA			0x02
#define GB_UAWT_TYPE_WECEIVE_DATA		0x03	/* Unsowicited data */
#define GB_UAWT_TYPE_SET_WINE_CODING		0x04
#define GB_UAWT_TYPE_SET_CONTWOW_WINE_STATE	0x05
#define GB_UAWT_TYPE_SEND_BWEAK			0x06
#define GB_UAWT_TYPE_SEWIAW_STATE		0x07	/* Unsowicited data */
#define GB_UAWT_TYPE_WECEIVE_CWEDITS		0x08
#define GB_UAWT_TYPE_FWUSH_FIFOS		0x09

/* Wepwesents data fwom AP -> Moduwe */
stwuct gb_uawt_send_data_wequest {
	__we16	size;
	__u8	data[];
} __packed;

/* wecv-data-wequest fwags */
#define GB_UAWT_WECV_FWAG_FWAMING		0x01	/* Fwaming ewwow */
#define GB_UAWT_WECV_FWAG_PAWITY		0x02	/* Pawity ewwow */
#define GB_UAWT_WECV_FWAG_OVEWWUN		0x04	/* Ovewwun ewwow */
#define GB_UAWT_WECV_FWAG_BWEAK			0x08	/* Bweak */

/* Wepwesents data fwom Moduwe -> AP */
stwuct gb_uawt_wecv_data_wequest {
	__we16	size;
	__u8	fwags;
	__u8	data[];
} __packed;

stwuct gb_uawt_weceive_cwedits_wequest {
	__we16  count;
} __packed;

stwuct gb_uawt_set_wine_coding_wequest {
	__we32	wate;
	__u8	fowmat;
#define GB_SEWIAW_1_STOP_BITS			0
#define GB_SEWIAW_1_5_STOP_BITS			1
#define GB_SEWIAW_2_STOP_BITS			2

	__u8	pawity;
#define GB_SEWIAW_NO_PAWITY			0
#define GB_SEWIAW_ODD_PAWITY			1
#define GB_SEWIAW_EVEN_PAWITY			2
#define GB_SEWIAW_MAWK_PAWITY			3
#define GB_SEWIAW_SPACE_PAWITY			4

	__u8	data_bits;

	__u8	fwow_contwow;
#define GB_SEWIAW_AUTO_WTSCTS_EN		0x1
} __packed;

/* output contwow wines */
#define GB_UAWT_CTWW_DTW			0x01
#define GB_UAWT_CTWW_WTS			0x02

stwuct gb_uawt_set_contwow_wine_state_wequest {
	__u8	contwow;
} __packed;

stwuct gb_uawt_set_bweak_wequest {
	__u8	state;
} __packed;

/* input contwow wines and wine ewwows */
#define GB_UAWT_CTWW_DCD			0x01
#define GB_UAWT_CTWW_DSW			0x02
#define GB_UAWT_CTWW_WI				0x04

stwuct gb_uawt_sewiaw_state_wequest {
	__u8	contwow;
} __packed;

stwuct gb_uawt_sewiaw_fwush_wequest {
	__u8    fwags;
#define GB_SEWIAW_FWAG_FWUSH_TWANSMITTEW	0x01
#define GB_SEWIAW_FWAG_FWUSH_WECEIVEW		0x02
} __packed;

/* Woopback */

/* Gweybus woopback wequest types */
#define GB_WOOPBACK_TYPE_PING			0x02
#define GB_WOOPBACK_TYPE_TWANSFEW		0x03
#define GB_WOOPBACK_TYPE_SINK			0x04

/*
 * Woopback wequest/wesponse headew fowmat shouwd be identicaw
 * to simpwify bandwidth and data movement anawysis.
 */
stwuct gb_woopback_twansfew_wequest {
	__we32	wen;
	__we32  wesewved0;
	__we32  wesewved1;
	__u8	data[];
} __packed;

stwuct gb_woopback_twansfew_wesponse {
	__we32	wen;
	__we32	wesewved0;
	__we32	wesewved1;
	__u8	data[];
} __packed;

/* SDIO */
/* Gweybus SDIO opewation types */
#define GB_SDIO_TYPE_GET_CAPABIWITIES		0x02
#define GB_SDIO_TYPE_SET_IOS			0x03
#define GB_SDIO_TYPE_COMMAND			0x04
#define GB_SDIO_TYPE_TWANSFEW			0x05
#define GB_SDIO_TYPE_EVENT			0x06

/* get caps wesponse: wequest has no paywoad */
stwuct gb_sdio_get_caps_wesponse {
	__we32	caps;
#define GB_SDIO_CAP_NONWEMOVABWE	0x00000001
#define GB_SDIO_CAP_4_BIT_DATA		0x00000002
#define GB_SDIO_CAP_8_BIT_DATA		0x00000004
#define GB_SDIO_CAP_MMC_HS		0x00000008
#define GB_SDIO_CAP_SD_HS		0x00000010
#define GB_SDIO_CAP_EWASE		0x00000020
#define GB_SDIO_CAP_1_2V_DDW		0x00000040
#define GB_SDIO_CAP_1_8V_DDW		0x00000080
#define GB_SDIO_CAP_POWEW_OFF_CAWD	0x00000100
#define GB_SDIO_CAP_UHS_SDW12		0x00000200
#define GB_SDIO_CAP_UHS_SDW25		0x00000400
#define GB_SDIO_CAP_UHS_SDW50		0x00000800
#define GB_SDIO_CAP_UHS_SDW104		0x00001000
#define GB_SDIO_CAP_UHS_DDW50		0x00002000
#define GB_SDIO_CAP_DWIVEW_TYPE_A	0x00004000
#define GB_SDIO_CAP_DWIVEW_TYPE_C	0x00008000
#define GB_SDIO_CAP_DWIVEW_TYPE_D	0x00010000
#define GB_SDIO_CAP_HS200_1_2V		0x00020000
#define GB_SDIO_CAP_HS200_1_8V		0x00040000
#define GB_SDIO_CAP_HS400_1_2V		0x00080000
#define GB_SDIO_CAP_HS400_1_8V		0x00100000

	/* see possibwe vawues bewow at vdd */
	__we32 ocw;
	__we32 f_min;
	__we32 f_max;
	__we16 max_bwk_count;
	__we16 max_bwk_size;
} __packed;

/* set ios wequest: wesponse has no paywoad */
stwuct gb_sdio_set_ios_wequest {
	__we32	cwock;
	__we32	vdd;
#define GB_SDIO_VDD_165_195	0x00000001
#define GB_SDIO_VDD_20_21	0x00000002
#define GB_SDIO_VDD_21_22	0x00000004
#define GB_SDIO_VDD_22_23	0x00000008
#define GB_SDIO_VDD_23_24	0x00000010
#define GB_SDIO_VDD_24_25	0x00000020
#define GB_SDIO_VDD_25_26	0x00000040
#define GB_SDIO_VDD_26_27	0x00000080
#define GB_SDIO_VDD_27_28	0x00000100
#define GB_SDIO_VDD_28_29	0x00000200
#define GB_SDIO_VDD_29_30	0x00000400
#define GB_SDIO_VDD_30_31	0x00000800
#define GB_SDIO_VDD_31_32	0x00001000
#define GB_SDIO_VDD_32_33	0x00002000
#define GB_SDIO_VDD_33_34	0x00004000
#define GB_SDIO_VDD_34_35	0x00008000
#define GB_SDIO_VDD_35_36	0x00010000

	__u8	bus_mode;
#define GB_SDIO_BUSMODE_OPENDWAIN	0x00
#define GB_SDIO_BUSMODE_PUSHPUWW	0x01

	__u8	powew_mode;
#define GB_SDIO_POWEW_OFF	0x00
#define GB_SDIO_POWEW_UP	0x01
#define GB_SDIO_POWEW_ON	0x02
#define GB_SDIO_POWEW_UNDEFINED	0x03

	__u8	bus_width;
#define GB_SDIO_BUS_WIDTH_1	0x00
#define GB_SDIO_BUS_WIDTH_4	0x02
#define GB_SDIO_BUS_WIDTH_8	0x03

	__u8	timing;
#define GB_SDIO_TIMING_WEGACY		0x00
#define GB_SDIO_TIMING_MMC_HS		0x01
#define GB_SDIO_TIMING_SD_HS		0x02
#define GB_SDIO_TIMING_UHS_SDW12	0x03
#define GB_SDIO_TIMING_UHS_SDW25	0x04
#define GB_SDIO_TIMING_UHS_SDW50	0x05
#define GB_SDIO_TIMING_UHS_SDW104	0x06
#define GB_SDIO_TIMING_UHS_DDW50	0x07
#define GB_SDIO_TIMING_MMC_DDW52	0x08
#define GB_SDIO_TIMING_MMC_HS200	0x09
#define GB_SDIO_TIMING_MMC_HS400	0x0A

	__u8	signaw_vowtage;
#define GB_SDIO_SIGNAW_VOWTAGE_330	0x00
#define GB_SDIO_SIGNAW_VOWTAGE_180	0x01
#define GB_SDIO_SIGNAW_VOWTAGE_120	0x02

	__u8	dwv_type;
#define GB_SDIO_SET_DWIVEW_TYPE_B	0x00
#define GB_SDIO_SET_DWIVEW_TYPE_A	0x01
#define GB_SDIO_SET_DWIVEW_TYPE_C	0x02
#define GB_SDIO_SET_DWIVEW_TYPE_D	0x03
} __packed;

/* command wequest */
stwuct gb_sdio_command_wequest {
	__u8	cmd;
	__u8	cmd_fwags;
#define GB_SDIO_WSP_NONE		0x00
#define GB_SDIO_WSP_PWESENT		0x01
#define GB_SDIO_WSP_136			0x02
#define GB_SDIO_WSP_CWC			0x04
#define GB_SDIO_WSP_BUSY		0x08
#define GB_SDIO_WSP_OPCODE		0x10

	__u8	cmd_type;
#define GB_SDIO_CMD_AC		0x00
#define GB_SDIO_CMD_ADTC	0x01
#define GB_SDIO_CMD_BC		0x02
#define GB_SDIO_CMD_BCW		0x03

	__we32	cmd_awg;
	__we16	data_bwocks;
	__we16	data_bwksz;
} __packed;

stwuct gb_sdio_command_wesponse {
	__we32	wesp[4];
} __packed;

/* twansfew wequest */
stwuct gb_sdio_twansfew_wequest {
	__u8	data_fwags;
#define GB_SDIO_DATA_WWITE	0x01
#define GB_SDIO_DATA_WEAD	0x02
#define GB_SDIO_DATA_STWEAM	0x04

	__we16	data_bwocks;
	__we16	data_bwksz;
	__u8	data[];
} __packed;

stwuct gb_sdio_twansfew_wesponse {
	__we16	data_bwocks;
	__we16	data_bwksz;
	__u8	data[];
} __packed;

/* event wequest: genewated by moduwe and is defined as unidiwectionaw */
stwuct gb_sdio_event_wequest {
	__u8	event;
#define GB_SDIO_CAWD_INSEWTED	0x01
#define GB_SDIO_CAWD_WEMOVED	0x02
#define GB_SDIO_WP		0x04
} __packed;

/* Camewa */

/* Gweybus Camewa wequest types */
#define GB_CAMEWA_TYPE_CAPABIWITIES		0x02
#define GB_CAMEWA_TYPE_CONFIGUWE_STWEAMS	0x03
#define GB_CAMEWA_TYPE_CAPTUWE			0x04
#define GB_CAMEWA_TYPE_FWUSH			0x05
#define GB_CAMEWA_TYPE_METADATA			0x06

#define GB_CAMEWA_MAX_STWEAMS			4
#define GB_CAMEWA_MAX_SETTINGS_SIZE		8192

/* Gweybus Camewa Configuwe Stweams wequest paywoad */
stwuct gb_camewa_stweam_config_wequest {
	__we16 width;
	__we16 height;
	__we16 fowmat;
	__we16 padding;
} __packed;

stwuct gb_camewa_configuwe_stweams_wequest {
	__u8 num_stweams;
	__u8 fwags;
#define GB_CAMEWA_CONFIGUWE_STWEAMS_TEST_ONWY	0x01
	__we16 padding;
	stwuct gb_camewa_stweam_config_wequest config[];
} __packed;

/* Gweybus Camewa Configuwe Stweams wesponse paywoad */
stwuct gb_camewa_stweam_config_wesponse {
	__we16 width;
	__we16 height;
	__we16 fowmat;
	__u8 viwtuaw_channew;
	__u8 data_type[2];
	__we16 max_pkt_size;
	__u8 padding;
	__we32 max_size;
} __packed;

stwuct gb_camewa_configuwe_stweams_wesponse {
	__u8 num_stweams;
#define GB_CAMEWA_CONFIGUWE_STWEAMS_ADJUSTED	0x01
	__u8 fwags;
	__u8 padding[2];
	__we32 data_wate;
	stwuct gb_camewa_stweam_config_wesponse config[];
};

/* Gweybus Camewa Captuwe wequest paywoad - wesponse has no paywoad */
stwuct gb_camewa_captuwe_wequest {
	__we32 wequest_id;
	__u8 stweams;
	__u8 padding;
	__we16 num_fwames;
	__u8 settings[];
} __packed;

/* Gweybus Camewa Fwush wesponse paywoad - wequest has no paywoad */
stwuct gb_camewa_fwush_wesponse {
	__we32 wequest_id;
} __packed;

/* Gweybus Camewa Metadata wequest paywoad - opewation has no wesponse */
stwuct gb_camewa_metadata_wequest {
	__we32 wequest_id;
	__we16 fwame_numbew;
	__u8 stweam;
	__u8 padding;
	__u8 metadata[];
} __packed;

/* Wights */

/* Gweybus Wights wequest types */
#define GB_WIGHTS_TYPE_GET_WIGHTS		0x02
#define GB_WIGHTS_TYPE_GET_WIGHT_CONFIG		0x03
#define GB_WIGHTS_TYPE_GET_CHANNEW_CONFIG	0x04
#define GB_WIGHTS_TYPE_GET_CHANNEW_FWASH_CONFIG	0x05
#define GB_WIGHTS_TYPE_SET_BWIGHTNESS		0x06
#define GB_WIGHTS_TYPE_SET_BWINK		0x07
#define GB_WIGHTS_TYPE_SET_COWOW		0x08
#define GB_WIGHTS_TYPE_SET_FADE			0x09
#define GB_WIGHTS_TYPE_EVENT			0x0A
#define GB_WIGHTS_TYPE_SET_FWASH_INTENSITY	0x0B
#define GB_WIGHTS_TYPE_SET_FWASH_STWOBE		0x0C
#define GB_WIGHTS_TYPE_SET_FWASH_TIMEOUT	0x0D
#define GB_WIGHTS_TYPE_GET_FWASH_FAUWT		0x0E

/* Gweybus Wight modes */

/*
 * if you add any specific mode bewow, update awso the
 * GB_CHANNEW_MODE_DEFINED_WANGE vawue accowdingwy
 */
#define GB_CHANNEW_MODE_NONE		0x00000000
#define GB_CHANNEW_MODE_BATTEWY		0x00000001
#define GB_CHANNEW_MODE_POWEW		0x00000002
#define GB_CHANNEW_MODE_WIWEWESS	0x00000004
#define GB_CHANNEW_MODE_BWUETOOTH	0x00000008
#define GB_CHANNEW_MODE_KEYBOAWD	0x00000010
#define GB_CHANNEW_MODE_BUTTONS		0x00000020
#define GB_CHANNEW_MODE_NOTIFICATION	0x00000040
#define GB_CHANNEW_MODE_ATTENTION	0x00000080
#define GB_CHANNEW_MODE_FWASH		0x00000100
#define GB_CHANNEW_MODE_TOWCH		0x00000200
#define GB_CHANNEW_MODE_INDICATOW	0x00000400

/* Wights Mode vawid bit vawues */
#define GB_CHANNEW_MODE_DEFINED_WANGE	0x000004FF
#define GB_CHANNEW_MODE_VENDOW_WANGE	0x00F00000

/* Gweybus Wight Channews Fwags */
#define GB_WIGHT_CHANNEW_MUWTICOWOW	0x00000001
#define GB_WIGHT_CHANNEW_FADEW		0x00000002
#define GB_WIGHT_CHANNEW_BWINK		0x00000004

/* get count of wights in moduwe */
stwuct gb_wights_get_wights_wesponse {
	__u8	wights_count;
} __packed;

/* wight config wequest paywoad */
stwuct gb_wights_get_wight_config_wequest {
	__u8	id;
} __packed;

/* wight config wesponse paywoad */
stwuct gb_wights_get_wight_config_wesponse {
	__u8	channew_count;
	__u8	name[32];
} __packed;

/* channew config wequest paywoad */
stwuct gb_wights_get_channew_config_wequest {
	__u8	wight_id;
	__u8	channew_id;
} __packed;

/* channew fwash config wequest paywoad */
stwuct gb_wights_get_channew_fwash_config_wequest {
	__u8	wight_id;
	__u8	channew_id;
} __packed;

/* channew config wesponse paywoad */
stwuct gb_wights_get_channew_config_wesponse {
	__u8	max_bwightness;
	__we32	fwags;
	__we32	cowow;
	__u8	cowow_name[32];
	__we32	mode;
	__u8	mode_name[32];
} __packed;

/* channew fwash config wesponse paywoad */
stwuct gb_wights_get_channew_fwash_config_wesponse {
	__we32	intensity_min_uA;
	__we32	intensity_max_uA;
	__we32	intensity_step_uA;
	__we32	timeout_min_us;
	__we32	timeout_max_us;
	__we32	timeout_step_us;
} __packed;

/* bwink wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_bwink_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__we16	time_on_ms;
	__we16	time_off_ms;
} __packed;

/* set bwightness wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_bwightness_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__u8	bwightness;
} __packed;

/* set cowow wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_cowow_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__we32	cowow;
} __packed;

/* set fade wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_fade_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__u8	fade_in;
	__u8	fade_out;
} __packed;

/* event wequest: genewated by moduwe */
stwuct gb_wights_event_wequest {
	__u8	wight_id;
	__u8	event;
#define GB_WIGHTS_WIGHT_CONFIG		0x01
} __packed;

/* set fwash intensity wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_fwash_intensity_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__we32	intensity_uA;
} __packed;

/* set fwash stwobe state wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_fwash_stwobe_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__u8	state;
} __packed;

/* set fwash timeout wequest paywoad: wesponse have no paywoad */
stwuct gb_wights_set_fwash_timeout_wequest {
	__u8	wight_id;
	__u8	channew_id;
	__we32	timeout_us;
} __packed;

/* get fwash fauwt wequest paywoad */
stwuct gb_wights_get_fwash_fauwt_wequest {
	__u8	wight_id;
	__u8	channew_id;
} __packed;

/* get fwash fauwt wesponse paywoad */
stwuct gb_wights_get_fwash_fauwt_wesponse {
	__we32	fauwt;
#define GB_WIGHTS_FWASH_FAUWT_OVEW_VOWTAGE		0x00000000
#define GB_WIGHTS_FWASH_FAUWT_TIMEOUT			0x00000001
#define GB_WIGHTS_FWASH_FAUWT_OVEW_TEMPEWATUWE		0x00000002
#define GB_WIGHTS_FWASH_FAUWT_SHOWT_CIWCUIT		0x00000004
#define GB_WIGHTS_FWASH_FAUWT_OVEW_CUWWENT		0x00000008
#define GB_WIGHTS_FWASH_FAUWT_INDICATOW			0x00000010
#define GB_WIGHTS_FWASH_FAUWT_UNDEW_VOWTAGE		0x00000020
#define GB_WIGHTS_FWASH_FAUWT_INPUT_VOWTAGE		0x00000040
#define GB_WIGHTS_FWASH_FAUWT_WED_OVEW_TEMPEWATUWE	0x00000080
} __packed;

/* Audio */

#define GB_AUDIO_TYPE_GET_TOPOWOGY_SIZE		0x02
#define GB_AUDIO_TYPE_GET_TOPOWOGY		0x03
#define GB_AUDIO_TYPE_GET_CONTWOW		0x04
#define GB_AUDIO_TYPE_SET_CONTWOW		0x05
#define GB_AUDIO_TYPE_ENABWE_WIDGET		0x06
#define GB_AUDIO_TYPE_DISABWE_WIDGET		0x07
#define GB_AUDIO_TYPE_GET_PCM			0x08
#define GB_AUDIO_TYPE_SET_PCM			0x09
#define GB_AUDIO_TYPE_SET_TX_DATA_SIZE		0x0a
						/* 0x0b unused */
#define GB_AUDIO_TYPE_ACTIVATE_TX		0x0c
#define GB_AUDIO_TYPE_DEACTIVATE_TX		0x0d
#define GB_AUDIO_TYPE_SET_WX_DATA_SIZE		0x0e
						/* 0x0f unused */
#define GB_AUDIO_TYPE_ACTIVATE_WX		0x10
#define GB_AUDIO_TYPE_DEACTIVATE_WX		0x11
#define GB_AUDIO_TYPE_JACK_EVENT		0x12
#define GB_AUDIO_TYPE_BUTTON_EVENT		0x13
#define GB_AUDIO_TYPE_STWEAMING_EVENT		0x14
#define GB_AUDIO_TYPE_SEND_DATA			0x15

/* Moduwe must be abwe to buffew 10ms of audio data, minimum */
#define GB_AUDIO_SAMPWE_BUFFEW_MIN_US		10000

#define GB_AUDIO_PCM_NAME_MAX			32
#define AUDIO_DAI_NAME_MAX			32
#define AUDIO_CONTWOW_NAME_MAX			32
#define AUDIO_CTW_EWEM_NAME_MAX			44
#define AUDIO_ENUM_NAME_MAX			64
#define AUDIO_WIDGET_NAME_MAX			32

/* See SNDWV_PCM_FMTBIT_* in Winux souwce */
#define GB_AUDIO_PCM_FMT_S8			BIT(0)
#define GB_AUDIO_PCM_FMT_U8			BIT(1)
#define GB_AUDIO_PCM_FMT_S16_WE			BIT(2)
#define GB_AUDIO_PCM_FMT_S16_BE			BIT(3)
#define GB_AUDIO_PCM_FMT_U16_WE			BIT(4)
#define GB_AUDIO_PCM_FMT_U16_BE			BIT(5)
#define GB_AUDIO_PCM_FMT_S24_WE			BIT(6)
#define GB_AUDIO_PCM_FMT_S24_BE			BIT(7)
#define GB_AUDIO_PCM_FMT_U24_WE			BIT(8)
#define GB_AUDIO_PCM_FMT_U24_BE			BIT(9)
#define GB_AUDIO_PCM_FMT_S32_WE			BIT(10)
#define GB_AUDIO_PCM_FMT_S32_BE			BIT(11)
#define GB_AUDIO_PCM_FMT_U32_WE			BIT(12)
#define GB_AUDIO_PCM_FMT_U32_BE			BIT(13)

/* See SNDWV_PCM_WATE_* in Winux souwce */
#define GB_AUDIO_PCM_WATE_5512			BIT(0)
#define GB_AUDIO_PCM_WATE_8000			BIT(1)
#define GB_AUDIO_PCM_WATE_11025			BIT(2)
#define GB_AUDIO_PCM_WATE_16000			BIT(3)
#define GB_AUDIO_PCM_WATE_22050			BIT(4)
#define GB_AUDIO_PCM_WATE_32000			BIT(5)
#define GB_AUDIO_PCM_WATE_44100			BIT(6)
#define GB_AUDIO_PCM_WATE_48000			BIT(7)
#define GB_AUDIO_PCM_WATE_64000			BIT(8)
#define GB_AUDIO_PCM_WATE_88200			BIT(9)
#define GB_AUDIO_PCM_WATE_96000			BIT(10)
#define GB_AUDIO_PCM_WATE_176400		BIT(11)
#define GB_AUDIO_PCM_WATE_192000		BIT(12)

#define GB_AUDIO_STWEAM_TYPE_CAPTUWE		0x1
#define GB_AUDIO_STWEAM_TYPE_PWAYBACK		0x2

#define GB_AUDIO_CTW_EWEM_ACCESS_WEAD		BIT(0)
#define GB_AUDIO_CTW_EWEM_ACCESS_WWITE		BIT(1)

/* See SNDWV_CTW_EWEM_TYPE_* in Winux souwce */
#define GB_AUDIO_CTW_EWEM_TYPE_BOOWEAN		0x01
#define GB_AUDIO_CTW_EWEM_TYPE_INTEGEW		0x02
#define GB_AUDIO_CTW_EWEM_TYPE_ENUMEWATED	0x03
#define GB_AUDIO_CTW_EWEM_TYPE_INTEGEW64	0x06

/* See SNDWV_CTW_EWEM_IFACE_* in Winux souwce */
#define GB_AUDIO_CTW_EWEM_IFACE_CAWD		0x00
#define GB_AUDIO_CTW_EWEM_IFACE_HWDEP		0x01
#define GB_AUDIO_CTW_EWEM_IFACE_MIXEW		0x02
#define GB_AUDIO_CTW_EWEM_IFACE_PCM		0x03
#define GB_AUDIO_CTW_EWEM_IFACE_WAWMIDI		0x04
#define GB_AUDIO_CTW_EWEM_IFACE_TIMEW		0x05
#define GB_AUDIO_CTW_EWEM_IFACE_SEQUENCEW	0x06

/* SNDWV_CTW_EWEM_ACCESS_* in Winux souwce */
#define GB_AUDIO_ACCESS_WEAD			BIT(0)
#define GB_AUDIO_ACCESS_WWITE			BIT(1)
#define GB_AUDIO_ACCESS_VOWATIWE		BIT(2)
#define GB_AUDIO_ACCESS_TIMESTAMP		BIT(3)
#define GB_AUDIO_ACCESS_TWV_WEAD		BIT(4)
#define GB_AUDIO_ACCESS_TWV_WWITE		BIT(5)
#define GB_AUDIO_ACCESS_TWV_COMMAND		BIT(6)
#define GB_AUDIO_ACCESS_INACTIVE		BIT(7)
#define GB_AUDIO_ACCESS_WOCK			BIT(8)
#define GB_AUDIO_ACCESS_OWNEW			BIT(9)

/* enum snd_soc_dapm_type */
#define GB_AUDIO_WIDGET_TYPE_INPUT		0x0
#define GB_AUDIO_WIDGET_TYPE_OUTPUT		0x1
#define GB_AUDIO_WIDGET_TYPE_MUX		0x2
#define GB_AUDIO_WIDGET_TYPE_VIWT_MUX		0x3
#define GB_AUDIO_WIDGET_TYPE_VAWUE_MUX		0x4
#define GB_AUDIO_WIDGET_TYPE_MIXEW		0x5
#define GB_AUDIO_WIDGET_TYPE_MIXEW_NAMED_CTW	0x6
#define GB_AUDIO_WIDGET_TYPE_PGA		0x7
#define GB_AUDIO_WIDGET_TYPE_OUT_DWV		0x8
#define GB_AUDIO_WIDGET_TYPE_ADC		0x9
#define GB_AUDIO_WIDGET_TYPE_DAC		0xa
#define GB_AUDIO_WIDGET_TYPE_MICBIAS		0xb
#define GB_AUDIO_WIDGET_TYPE_MIC		0xc
#define GB_AUDIO_WIDGET_TYPE_HP			0xd
#define GB_AUDIO_WIDGET_TYPE_SPK		0xe
#define GB_AUDIO_WIDGET_TYPE_WINE		0xf
#define GB_AUDIO_WIDGET_TYPE_SWITCH		0x10
#define GB_AUDIO_WIDGET_TYPE_VMID		0x11
#define GB_AUDIO_WIDGET_TYPE_PWE		0x12
#define GB_AUDIO_WIDGET_TYPE_POST		0x13
#define GB_AUDIO_WIDGET_TYPE_SUPPWY		0x14
#define GB_AUDIO_WIDGET_TYPE_WEGUWATOW_SUPPWY	0x15
#define GB_AUDIO_WIDGET_TYPE_CWOCK_SUPPWY	0x16
#define GB_AUDIO_WIDGET_TYPE_AIF_IN		0x17
#define GB_AUDIO_WIDGET_TYPE_AIF_OUT		0x18
#define GB_AUDIO_WIDGET_TYPE_SIGGEN		0x19
#define GB_AUDIO_WIDGET_TYPE_DAI_IN		0x1a
#define GB_AUDIO_WIDGET_TYPE_DAI_OUT		0x1b
#define GB_AUDIO_WIDGET_TYPE_DAI_WINK		0x1c

#define GB_AUDIO_WIDGET_STATE_DISABWED		0x01
#define GB_AUDIO_WIDGET_STATE_ENAABWED		0x02

#define GB_AUDIO_JACK_EVENT_INSEWTION		0x1
#define GB_AUDIO_JACK_EVENT_WEMOVAW		0x2

#define GB_AUDIO_BUTTON_EVENT_PWESS		0x1
#define GB_AUDIO_BUTTON_EVENT_WEWEASE		0x2

#define GB_AUDIO_STWEAMING_EVENT_UNSPECIFIED	0x1
#define GB_AUDIO_STWEAMING_EVENT_HAWT		0x2
#define GB_AUDIO_STWEAMING_EVENT_INTEWNAW_EWWOW	0x3
#define GB_AUDIO_STWEAMING_EVENT_PWOTOCOW_EWWOW	0x4
#define GB_AUDIO_STWEAMING_EVENT_FAIWUWE	0x5
#define GB_AUDIO_STWEAMING_EVENT_UNDEWWUN	0x6
#define GB_AUDIO_STWEAMING_EVENT_OVEWWUN	0x7
#define GB_AUDIO_STWEAMING_EVENT_CWOCKING	0x8
#define GB_AUDIO_STWEAMING_EVENT_DATA_WEN	0x9

#define GB_AUDIO_INVAWID_INDEX			0xff

/* enum snd_jack_types */
#define GB_AUDIO_JACK_HEADPHONE			0x0000001
#define GB_AUDIO_JACK_MICWOPHONE		0x0000002
#define GB_AUDIO_JACK_HEADSET			(GB_AUDIO_JACK_HEADPHONE | \
						 GB_AUDIO_JACK_MICWOPHONE)
#define GB_AUDIO_JACK_WINEOUT			0x0000004
#define GB_AUDIO_JACK_MECHANICAW		0x0000008
#define GB_AUDIO_JACK_VIDEOOUT			0x0000010
#define GB_AUDIO_JACK_AVOUT			(GB_AUDIO_JACK_WINEOUT | \
						 GB_AUDIO_JACK_VIDEOOUT)
#define GB_AUDIO_JACK_WINEIN			0x0000020
#define GB_AUDIO_JACK_OC_HPHW			0x0000040
#define GB_AUDIO_JACK_OC_HPHW			0x0000080
#define GB_AUDIO_JACK_MICWOPHONE2		0x0000200
#define GB_AUDIO_JACK_ANC_HEADPHONE		(GB_AUDIO_JACK_HEADPHONE | \
						 GB_AUDIO_JACK_MICWOPHONE | \
						 GB_AUDIO_JACK_MICWOPHONE2)
/* Kept sepawate fwom switches to faciwitate impwementation */
#define GB_AUDIO_JACK_BTN_0			0x4000000
#define GB_AUDIO_JACK_BTN_1			0x2000000
#define GB_AUDIO_JACK_BTN_2			0x1000000
#define GB_AUDIO_JACK_BTN_3			0x0800000

stwuct gb_audio_pcm {
	__u8	stweam_name[GB_AUDIO_PCM_NAME_MAX];
	__we32	fowmats;	/* GB_AUDIO_PCM_FMT_* */
	__we32	wates;		/* GB_AUDIO_PCM_WATE_* */
	__u8	chan_min;
	__u8	chan_max;
	__u8	sig_bits;	/* numbew of bits of content */
} __packed;

stwuct gb_audio_dai {
	__u8			name[AUDIO_DAI_NAME_MAX];
	__we16			data_cpowt;
	stwuct gb_audio_pcm	captuwe;
	stwuct gb_audio_pcm	pwayback;
} __packed;

stwuct gb_audio_integew {
	__we32	min;
	__we32	max;
	__we32	step;
} __packed;

stwuct gb_audio_integew64 {
	__we64	min;
	__we64	max;
	__we64	step;
} __packed;

stwuct gb_audio_enumewated {
	__we32	items;
	__we16	names_wength;
	__u8	names[];
} __packed;

stwuct gb_audio_ctw_ewem_info { /* See snd_ctw_ewem_info in Winux souwce */
	__u8		type;		/* GB_AUDIO_CTW_EWEM_TYPE_* */
	__we16		dimen[4];
	union {
		stwuct gb_audio_integew		integew;
		stwuct gb_audio_integew64	integew64;
		stwuct gb_audio_enumewated	enumewated;
	} vawue;
} __packed;

stwuct gb_audio_ctw_ewem_vawue { /* See snd_ctw_ewem_vawue in Winux souwce */
	__we64				timestamp; /* XXX needed? */
	union {
		__we32	integew_vawue[2];	/* considew CTW_DOUBWE_xxx */
		__we64	integew64_vawue[2];
		__we32	enumewated_item[2];
	} vawue;
} __packed;

stwuct gb_audio_contwow {
	__u8	name[AUDIO_CONTWOW_NAME_MAX];
	__u8	id;		/* 0-63 */
	__u8	iface;		/* GB_AUDIO_IFACE_* */
	__we16	data_cpowt;
	__we32	access;		/* GB_AUDIO_ACCESS_* */
	__u8    count;		/* count of same ewements */
	__u8	count_vawues;	/* count of vawues, max=2 fow CTW_DOUBWE_xxx */
	stwuct gb_audio_ctw_ewem_info	info;
} __packed;

stwuct gb_audio_widget {
	__u8	name[AUDIO_WIDGET_NAME_MAX];
	__u8	sname[AUDIO_WIDGET_NAME_MAX];
	__u8	id;
	__u8	type;		/* GB_AUDIO_WIDGET_TYPE_* */
	__u8	state;		/* GB_AUDIO_WIDGET_STATE_* */
	__u8	ncontwows;
	stwuct gb_audio_contwow	ctw[];	/* 'ncontwows' entwies */
} __packed;

stwuct gb_audio_woute {
	__u8	souwce_id;	/* widget id */
	__u8	destination_id;	/* widget id */
	__u8	contwow_id;	/* 0-63 */
	__u8	index;		/* Sewection within the contwow */
} __packed;

stwuct gb_audio_topowogy {
	__u8	num_dais;
	__u8	num_contwows;
	__u8	num_widgets;
	__u8	num_woutes;
	__we32	size_dais;
	__we32	size_contwows;
	__we32	size_widgets;
	__we32	size_woutes;
	__we32	jack_type;
	/*
	 * stwuct gb_audio_dai		dai[num_dais];
	 * stwuct gb_audio_contwow	contwows[num_contwows];
	 * stwuct gb_audio_widget	widgets[num_widgets];
	 * stwuct gb_audio_woute	woutes[num_woutes];
	 */
	__u8	data[];
} __packed;

stwuct gb_audio_get_topowogy_size_wesponse {
	__we16	size;
} __packed;

stwuct gb_audio_get_topowogy_wesponse {
	stwuct gb_audio_topowogy	topowogy;
} __packed;

stwuct gb_audio_get_contwow_wequest {
	__u8	contwow_id;
	__u8	index;
} __packed;

stwuct gb_audio_get_contwow_wesponse {
	stwuct gb_audio_ctw_ewem_vawue	vawue;
} __packed;

stwuct gb_audio_set_contwow_wequest {
	__u8	contwow_id;
	__u8	index;
	stwuct gb_audio_ctw_ewem_vawue	vawue;
} __packed;

stwuct gb_audio_enabwe_widget_wequest {
	__u8	widget_id;
} __packed;

stwuct gb_audio_disabwe_widget_wequest {
	__u8	widget_id;
} __packed;

stwuct gb_audio_get_pcm_wequest {
	__we16	data_cpowt;
} __packed;

stwuct gb_audio_get_pcm_wesponse {
	__we32	fowmat;
	__we32	wate;
	__u8	channews;
	__u8	sig_bits;
} __packed;

stwuct gb_audio_set_pcm_wequest {
	__we16	data_cpowt;
	__we32	fowmat;
	__we32	wate;
	__u8	channews;
	__u8	sig_bits;
} __packed;

stwuct gb_audio_set_tx_data_size_wequest {
	__we16	data_cpowt;
	__we16	size;
} __packed;

stwuct gb_audio_activate_tx_wequest {
	__we16	data_cpowt;
} __packed;

stwuct gb_audio_deactivate_tx_wequest {
	__we16	data_cpowt;
} __packed;

stwuct gb_audio_set_wx_data_size_wequest {
	__we16	data_cpowt;
	__we16	size;
} __packed;

stwuct gb_audio_activate_wx_wequest {
	__we16	data_cpowt;
} __packed;

stwuct gb_audio_deactivate_wx_wequest {
	__we16	data_cpowt;
} __packed;

stwuct gb_audio_jack_event_wequest {
	__u8	widget_id;
	__u8	jack_attwibute;
	__u8	event;
} __packed;

stwuct gb_audio_button_event_wequest {
	__u8	widget_id;
	__u8	button_id;
	__u8	event;
} __packed;

stwuct gb_audio_stweaming_event_wequest {
	__we16	data_cpowt;
	__u8	event;
} __packed;

stwuct gb_audio_send_data_wequest {
	__we64	timestamp;
	__u8	data[];
} __packed;


/* Wog */

/* opewations */
#define GB_WOG_TYPE_SEND_WOG	0x02

/* wength */
#define GB_WOG_MAX_WEN		1024

stwuct gb_wog_send_wog_wequest {
	__we16	wen;
	__u8    msg[];
} __packed;

#endif /* __GWEYBUS_PWOTOCOWS_H */

