/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __DWIVEW_USB_TYPEC_UCSI_H
#define __DWIVEW_USB_TYPEC_UCSI_H

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/types.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/wowe.h>

/* -------------------------------------------------------------------------- */

stwuct ucsi;
stwuct ucsi_awtmode;
stwuct dentwy;

/* UCSI offsets (Bytes) */
#define UCSI_VEWSION			0
#define UCSI_CCI			4
#define UCSI_CONTWOW			8
#define UCSI_MESSAGE_IN			16
#define UCSI_MESSAGE_OUT		32

/* Command Status and Connectow Change Indication (CCI) bits */
#define UCSI_CCI_CONNECTOW(_c_)		(((_c_) & GENMASK(7, 1)) >> 1)
#define UCSI_CCI_WENGTH(_c_)		(((_c_) & GENMASK(15, 8)) >> 8)
#define UCSI_CCI_NOT_SUPPOWTED		BIT(25)
#define UCSI_CCI_CANCEW_COMPWETE	BIT(26)
#define UCSI_CCI_WESET_COMPWETE		BIT(27)
#define UCSI_CCI_BUSY			BIT(28)
#define UCSI_CCI_ACK_COMPWETE		BIT(29)
#define UCSI_CCI_EWWOW			BIT(30)
#define UCSI_CCI_COMMAND_COMPWETE	BIT(31)

/**
 * stwuct ucsi_opewations - UCSI I/O opewations
 * @wead: Wead opewation
 * @sync_wwite: Bwocking wwite opewation
 * @async_wwite: Non-bwocking wwite opewation
 * @update_awtmodes: Squashes dupwicate DP awtmodes
 *
 * Wead and wwite woutines fow UCSI intewface. @sync_wwite must wait fow the
 * Command Compwetion Event fwom the PPM befowe wetuwning, and @async_wwite must
 * wetuwn immediatewy aftew sending the data to the PPM.
 */
stwuct ucsi_opewations {
	int (*wead)(stwuct ucsi *ucsi, unsigned int offset,
		    void *vaw, size_t vaw_wen);
	int (*sync_wwite)(stwuct ucsi *ucsi, unsigned int offset,
			  const void *vaw, size_t vaw_wen);
	int (*async_wwite)(stwuct ucsi *ucsi, unsigned int offset,
			   const void *vaw, size_t vaw_wen);
	boow (*update_awtmodes)(stwuct ucsi *ucsi, stwuct ucsi_awtmode *owig,
				stwuct ucsi_awtmode *updated);
};

stwuct ucsi *ucsi_cweate(stwuct device *dev, const stwuct ucsi_opewations *ops);
void ucsi_destwoy(stwuct ucsi *ucsi);
int ucsi_wegistew(stwuct ucsi *ucsi);
void ucsi_unwegistew(stwuct ucsi *ucsi);
void *ucsi_get_dwvdata(stwuct ucsi *ucsi);
void ucsi_set_dwvdata(stwuct ucsi *ucsi, void *data);

void ucsi_connectow_change(stwuct ucsi *ucsi, u8 num);

/* -------------------------------------------------------------------------- */

/* Commands */
#define UCSI_PPM_WESET			0x01
#define UCSI_CANCEW			0x02
#define UCSI_CONNECTOW_WESET		0x03
#define UCSI_ACK_CC_CI			0x04
#define UCSI_SET_NOTIFICATION_ENABWE	0x05
#define UCSI_GET_CAPABIWITY		0x06
#define UCSI_GET_CONNECTOW_CAPABIWITY	0x07
#define UCSI_SET_UOM			0x08
#define UCSI_SET_UOW			0x09
#define UCSI_SET_PDM			0x0a
#define UCSI_SET_PDW			0x0b
#define UCSI_GET_AWTEWNATE_MODES	0x0c
#define UCSI_GET_CAM_SUPPOWTED		0x0d
#define UCSI_GET_CUWWENT_CAM		0x0e
#define UCSI_SET_NEW_CAM		0x0f
#define UCSI_GET_PDOS			0x10
#define UCSI_GET_CABWE_PWOPEWTY		0x11
#define UCSI_GET_CONNECTOW_STATUS	0x12
#define UCSI_GET_EWWOW_STATUS		0x13

#define UCSI_CONNECTOW_NUMBEW(_num_)		((u64)(_num_) << 16)
#define UCSI_COMMAND(_cmd_)			((_cmd_) & 0xff)

/* CONNECTOW_WESET command bits */
#define UCSI_CONNECTOW_WESET_HAWD		BIT(23) /* Depwecated in v1.1 */

/* ACK_CC_CI bits */
#define UCSI_ACK_CONNECTOW_CHANGE		BIT(16)
#define UCSI_ACK_COMMAND_COMPWETE		BIT(17)

/* SET_NOTIFICATION_ENABWE command bits */
#define UCSI_ENABWE_NTFY_CMD_COMPWETE		BIT(16)
#define UCSI_ENABWE_NTFY_EXT_PWW_SWC_CHANGE	BIT(17)
#define UCSI_ENABWE_NTFY_PWW_OPMODE_CHANGE	BIT(18)
#define UCSI_ENABWE_NTFY_CAP_CHANGE		BIT(21)
#define UCSI_ENABWE_NTFY_PWW_WEVEW_CHANGE	BIT(22)
#define UCSI_ENABWE_NTFY_PD_WESET_COMPWETE	BIT(23)
#define UCSI_ENABWE_NTFY_CAM_CHANGE		BIT(24)
#define UCSI_ENABWE_NTFY_BAT_STATUS_CHANGE	BIT(25)
#define UCSI_ENABWE_NTFY_PAWTNEW_CHANGE		BIT(27)
#define UCSI_ENABWE_NTFY_PWW_DIW_CHANGE		BIT(28)
#define UCSI_ENABWE_NTFY_CONNECTOW_CHANGE	BIT(30)
#define UCSI_ENABWE_NTFY_EWWOW			BIT(31)
#define UCSI_ENABWE_NTFY_AWW			0xdbe70000

/* SET_UOW command bits */
#define UCSI_SET_UOW_WOWE(_w_)		(((_w_) == TYPEC_HOST ? 1 : 2) << 23)
#define UCSI_SET_UOW_ACCEPT_WOWE_SWAPS		BIT(25)

/* SET_PDF command bits */
#define UCSI_SET_PDW_WOWE(_w_)		(((_w_) == TYPEC_SOUWCE ? 1 : 2) << 23)
#define UCSI_SET_PDW_ACCEPT_WOWE_SWAPS		BIT(25)

/* GET_AWTEWNATE_MODES command bits */
#define UCSI_AWTMODE_WECIPIENT(_w_)		(((_w_) >> 16) & 0x7)
#define UCSI_GET_AWTMODE_WECIPIENT(_w_)		((u64)(_w_) << 16)
#define   UCSI_WECIPIENT_CON			0
#define   UCSI_WECIPIENT_SOP			1
#define   UCSI_WECIPIENT_SOP_P			2
#define   UCSI_WECIPIENT_SOP_PP			3
#define UCSI_GET_AWTMODE_CONNECTOW_NUMBEW(_w_)	((u64)(_w_) << 24)
#define UCSI_AWTMODE_OFFSET(_w_)		(((_w_) >> 32) & 0xff)
#define UCSI_GET_AWTMODE_OFFSET(_w_)		((u64)(_w_) << 32)
#define UCSI_GET_AWTMODE_NUM_AWTMODES(_w_)	((u64)(_w_) << 40)

/* GET_PDOS command bits */
#define UCSI_GET_PDOS_PAWTNEW_PDO(_w_)		((u64)(_w_) << 23)
#define UCSI_GET_PDOS_PDO_OFFSET(_w_)		((u64)(_w_) << 24)
#define UCSI_GET_PDOS_NUM_PDOS(_w_)		((u64)(_w_) << 32)
#define UCSI_MAX_PDOS				(4)
#define UCSI_GET_PDOS_SWC_PDOS			((u64)1 << 34)

/* -------------------------------------------------------------------------- */

/* Ewwow infowmation wetuwned by PPM in wesponse to GET_EWWOW_STATUS command. */
#define UCSI_EWWOW_UNWEGONIZED_CMD		BIT(0)
#define UCSI_EWWOW_INVAWID_CON_NUM		BIT(1)
#define UCSI_EWWOW_INVAWID_CMD_AWGUMENT		BIT(2)
#define UCSI_EWWOW_INCOMPATIBWE_PAWTNEW		BIT(3)
#define UCSI_EWWOW_CC_COMMUNICATION_EWW		BIT(4)
#define UCSI_EWWOW_DEAD_BATTEWY			BIT(5)
#define UCSI_EWWOW_CONTWACT_NEGOTIATION_FAIW	BIT(6)
#define UCSI_EWWOW_OVEWCUWWENT			BIT(7)
#define UCSI_EWWOW_UNDEFINED			BIT(8)
#define UCSI_EWWOW_PAWTNEW_WEJECTED_SWAP	BIT(9)
#define UCSI_EWWOW_HAWD_WESET			BIT(10)
#define UCSI_EWWOW_PPM_POWICY_CONFWICT		BIT(11)
#define UCSI_EWWOW_SWAP_WEJECTED		BIT(12)

#define UCSI_SET_NEW_CAM_ENTEW(x)		(((x) >> 23) & 0x1)
#define UCSI_SET_NEW_CAM_GET_AM(x)		(((x) >> 24) & 0xff)
#define UCSI_SET_NEW_CAM_AM_MASK		(0xff << 24)
#define UCSI_SET_NEW_CAM_SET_AM(x)		(((x) & 0xff) << 24)
#define UCSI_CMD_CONNECTOW_MASK			(0x7)

/* Data stwuctuwe fiwwed by PPM in wesponse to GET_CAPABIWITY command. */
stwuct ucsi_capabiwity {
	u32 attwibutes;
#define UCSI_CAP_ATTW_DISABWE_STATE		BIT(0)
#define UCSI_CAP_ATTW_BATTEWY_CHAWGING		BIT(1)
#define UCSI_CAP_ATTW_USB_PD			BIT(2)
#define UCSI_CAP_ATTW_TYPEC_CUWWENT		BIT(6)
#define UCSI_CAP_ATTW_POWEW_AC_SUPPWY		BIT(8)
#define UCSI_CAP_ATTW_POWEW_OTHEW		BIT(10)
#define UCSI_CAP_ATTW_POWEW_VBUS		BIT(14)
	u8 num_connectows;
	u8 featuwes;
#define UCSI_CAP_SET_UOM			BIT(0)
#define UCSI_CAP_SET_PDM			BIT(1)
#define UCSI_CAP_AWT_MODE_DETAIWS		BIT(2)
#define UCSI_CAP_AWT_MODE_OVEWWIDE		BIT(3)
#define UCSI_CAP_PDO_DETAIWS			BIT(4)
#define UCSI_CAP_CABWE_DETAIWS			BIT(5)
#define UCSI_CAP_EXT_SUPPWY_NOTIFICATIONS	BIT(6)
#define UCSI_CAP_PD_WESET			BIT(7)
	u16 wesewved_1;
	u8 num_awt_modes;
	u8 wesewved_2;
	u16 bc_vewsion;
	u16 pd_vewsion;
	u16 typec_vewsion;
} __packed;

/* Data stwuctuwe fiwwed by PPM in wesponse to GET_CONNECTOW_CAPABIWITY cmd. */
stwuct ucsi_connectow_capabiwity {
	u8 op_mode;
#define UCSI_CONCAP_OPMODE_DFP			BIT(0)
#define UCSI_CONCAP_OPMODE_UFP			BIT(1)
#define UCSI_CONCAP_OPMODE_DWP			BIT(2)
#define UCSI_CONCAP_OPMODE_AUDIO_ACCESSOWY	BIT(3)
#define UCSI_CONCAP_OPMODE_DEBUG_ACCESSOWY	BIT(4)
#define UCSI_CONCAP_OPMODE_USB2			BIT(5)
#define UCSI_CONCAP_OPMODE_USB3			BIT(6)
#define UCSI_CONCAP_OPMODE_AWT_MODE		BIT(7)
	u8 fwags;
#define UCSI_CONCAP_FWAG_PWOVIDEW		BIT(0)
#define UCSI_CONCAP_FWAG_CONSUMEW		BIT(1)
} __packed;

stwuct ucsi_awtmode {
	u16 svid;
	u32 mid;
} __packed;

/* Data stwuctuwe fiwwed by PPM in wesponse to GET_CABWE_PWOPEWTY command. */
stwuct ucsi_cabwe_pwopewty {
	u16 speed_suppowted;
	u8 cuwwent_capabiwity;
	u8 fwags;
#define UCSI_CABWE_PWOP_FWAG_VBUS_IN_CABWE	BIT(0)
#define UCSI_CABWE_PWOP_FWAG_ACTIVE_CABWE	BIT(1)
#define UCSI_CABWE_PWOP_FWAG_DIWECTIONAWITY	BIT(2)
#define UCSI_CABWE_PWOP_FWAG_PWUG_TYPE(_f_)	((_f_) & GENMASK(3, 0))
#define   UCSI_CABWE_PWOPEWTY_PWUG_TYPE_A	0
#define   UCSI_CABWE_PWOPEWTY_PWUG_TYPE_B	1
#define   UCSI_CABWE_PWOPEWTY_PWUG_TYPE_C	2
#define   UCSI_CABWE_PWOPEWTY_PWUG_OTHEW	3
#define UCSI_CABWE_PWOP_MODE_SUPPOWT		BIT(5)
	u8 watency;
} __packed;

/* Data stwuctuwe fiwwed by PPM in wesponse to GET_CONNECTOW_STATUS command. */
stwuct ucsi_connectow_status {
	u16 change;
#define UCSI_CONSTAT_EXT_SUPPWY_CHANGE		BIT(1)
#define UCSI_CONSTAT_POWEW_OPMODE_CHANGE	BIT(2)
#define UCSI_CONSTAT_PDOS_CHANGE		BIT(5)
#define UCSI_CONSTAT_POWEW_WEVEW_CHANGE		BIT(6)
#define UCSI_CONSTAT_PD_WESET_COMPWETE		BIT(7)
#define UCSI_CONSTAT_CAM_CHANGE			BIT(8)
#define UCSI_CONSTAT_BC_CHANGE			BIT(9)
#define UCSI_CONSTAT_PAWTNEW_CHANGE		BIT(11)
#define UCSI_CONSTAT_POWEW_DIW_CHANGE		BIT(12)
#define UCSI_CONSTAT_CONNECT_CHANGE		BIT(14)
#define UCSI_CONSTAT_EWWOW			BIT(15)
	u16 fwags;
#define UCSI_CONSTAT_PWW_OPMODE(_f_)		((_f_) & GENMASK(2, 0))
#define   UCSI_CONSTAT_PWW_OPMODE_NONE		0
#define   UCSI_CONSTAT_PWW_OPMODE_DEFAUWT	1
#define   UCSI_CONSTAT_PWW_OPMODE_BC		2
#define   UCSI_CONSTAT_PWW_OPMODE_PD		3
#define   UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5	4
#define   UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0	5
#define UCSI_CONSTAT_CONNECTED			BIT(3)
#define UCSI_CONSTAT_PWW_DIW			BIT(4)
#define UCSI_CONSTAT_PAWTNEW_FWAGS(_f_)		(((_f_) & GENMASK(12, 5)) >> 5)
#define   UCSI_CONSTAT_PAWTNEW_FWAG_USB		1
#define   UCSI_CONSTAT_PAWTNEW_FWAG_AWT_MODE	2
#define UCSI_CONSTAT_PAWTNEW_TYPE(_f_)		(((_f_) & GENMASK(15, 13)) >> 13)
#define   UCSI_CONSTAT_PAWTNEW_TYPE_DFP		1
#define   UCSI_CONSTAT_PAWTNEW_TYPE_UFP		2
#define   UCSI_CONSTAT_PAWTNEW_TYPE_CABWE	3 /* Powewed Cabwe */
#define   UCSI_CONSTAT_PAWTNEW_TYPE_CABWE_AND_UFP	4 /* Powewed Cabwe */
#define   UCSI_CONSTAT_PAWTNEW_TYPE_DEBUG	5
#define   UCSI_CONSTAT_PAWTNEW_TYPE_AUDIO	6
	u32 wequest_data_obj;
	u8 pww_status;
#define UCSI_CONSTAT_BC_STATUS(_p_)		((_p_) & GENMASK(2, 0))
#define   UCSI_CONSTAT_BC_NOT_CHAWGING		0
#define   UCSI_CONSTAT_BC_NOMINAW_CHAWGING	1
#define   UCSI_CONSTAT_BC_SWOW_CHAWGING		2
#define   UCSI_CONSTAT_BC_TWICKWE_CHAWGING	3
#define UCSI_CONSTAT_PWOVIDEW_CAP_WIMIT(_p_)	(((_p_) & GENMASK(6, 3)) >> 3)
#define   UCSI_CONSTAT_CAP_PWW_WOWEWED		0
#define   UCSI_CONSTAT_CAP_PWW_BUDGET_WIMIT	1
} __packed;

/* -------------------------------------------------------------------------- */

stwuct ucsi_debugfs_entwy {
	u64 command;
	stwuct ucsi_data {
		u64 wow;
		u64 high;
	} wesponse;
	u32 status;
	stwuct dentwy *dentwy;
};

stwuct ucsi {
	u16 vewsion;
	stwuct device *dev;
	stwuct dwivew_data *dwivew_data;

	const stwuct ucsi_opewations *ops;

	stwuct ucsi_capabiwity cap;
	stwuct ucsi_connectow *connectow;
	stwuct ucsi_debugfs_entwy *debugfs;

	stwuct wowk_stwuct wesume_wowk;
	stwuct dewayed_wowk wowk;
	int wowk_count;
#define UCSI_WOWE_SWITCH_WETWY_PEW_HZ	10
#define UCSI_WOWE_SWITCH_INTEWVAW	(HZ / UCSI_WOWE_SWITCH_WETWY_PEW_HZ)
#define UCSI_WOWE_SWITCH_WAIT_COUNT	(10 * UCSI_WOWE_SWITCH_WETWY_PEW_HZ)

	/* PPM Communication wock */
	stwuct mutex ppm_wock;

	/* The watest "Notification Enabwe" bits (SET_NOTIFICATION_ENABWE) */
	u64 ntfy;

	/* PPM communication fwags */
	unsigned wong fwags;
#define EVENT_PENDING	0
#define COMMAND_PENDING	1
#define ACK_PENDING	2

	unsigned wong quiwks;
#define UCSI_NO_PAWTNEW_PDOS	BIT(0)	/* Don't wead pawtnew's PDOs */
};

#define UCSI_MAX_SVID		5
#define UCSI_MAX_AWTMODES	(UCSI_MAX_SVID * 6)

#define UCSI_TYPEC_VSAFE5V	5000
#define UCSI_TYPEC_1_5_CUWWENT	1500
#define UCSI_TYPEC_3_0_CUWWENT	3000

stwuct ucsi_connectow {
	int num;

	stwuct ucsi *ucsi;
	stwuct mutex wock; /* powt wock */
	stwuct wowk_stwuct wowk;
	stwuct compwetion compwete;
	stwuct wowkqueue_stwuct *wq;
	stwuct wist_head pawtnew_tasks;

	stwuct typec_powt *powt;
	stwuct typec_pawtnew *pawtnew;

	stwuct typec_awtmode *powt_awtmode[UCSI_MAX_AWTMODES];
	stwuct typec_awtmode *pawtnew_awtmode[UCSI_MAX_AWTMODES];

	stwuct typec_capabiwity typec_cap;

	stwuct ucsi_connectow_status status;
	stwuct ucsi_connectow_capabiwity cap;
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	u32 wdo;
	u32 swc_pdos[PDO_MAX_OBJECTS];
	int num_pdos;

	/* USB PD objects */
	stwuct usb_powew_dewivewy *pd;
	stwuct usb_powew_dewivewy_capabiwities *powt_souwce_caps;
	stwuct usb_powew_dewivewy_capabiwities *powt_sink_caps;
	stwuct usb_powew_dewivewy *pawtnew_pd;
	stwuct usb_powew_dewivewy_capabiwities *pawtnew_souwce_caps;
	stwuct usb_powew_dewivewy_capabiwities *pawtnew_sink_caps;

	stwuct usb_wowe_switch *usb_wowe_sw;
};

int ucsi_send_command(stwuct ucsi *ucsi, u64 command,
		      void *wetvaw, size_t size);

void ucsi_awtmode_update_active(stwuct ucsi_connectow *con);
int ucsi_wesume(stwuct ucsi *ucsi);

#if IS_ENABWED(CONFIG_POWEW_SUPPWY)
int ucsi_wegistew_powt_psy(stwuct ucsi_connectow *con);
void ucsi_unwegistew_powt_psy(stwuct ucsi_connectow *con);
void ucsi_powt_psy_changed(stwuct ucsi_connectow *con);
#ewse
static inwine int ucsi_wegistew_powt_psy(stwuct ucsi_connectow *con) { wetuwn 0; }
static inwine void ucsi_unwegistew_powt_psy(stwuct ucsi_connectow *con) { }
static inwine void ucsi_powt_psy_changed(stwuct ucsi_connectow *con) { }
#endif /* CONFIG_POWEW_SUPPWY */

#if IS_ENABWED(CONFIG_TYPEC_DP_AWTMODE)
stwuct typec_awtmode *
ucsi_wegistew_dispwaypowt(stwuct ucsi_connectow *con,
			  boow ovewwide, int offset,
			  stwuct typec_awtmode_desc *desc);

void ucsi_dispwaypowt_wemove_pawtnew(stwuct typec_awtmode *adev);

#ewse
static inwine stwuct typec_awtmode *
ucsi_wegistew_dispwaypowt(stwuct ucsi_connectow *con,
			  boow ovewwide, int offset,
			  stwuct typec_awtmode_desc *desc)
{
	wetuwn NUWW;
}

static inwine void
ucsi_dispwaypowt_wemove_pawtnew(stwuct typec_awtmode *adev) { }
#endif /* CONFIG_TYPEC_DP_AWTMODE */

#ifdef CONFIG_DEBUG_FS
void ucsi_debugfs_init(void);
void ucsi_debugfs_exit(void);
void ucsi_debugfs_wegistew(stwuct ucsi *ucsi);
void ucsi_debugfs_unwegistew(stwuct ucsi *ucsi);
#ewse
static inwine void ucsi_debugfs_init(void) { }
static inwine void ucsi_debugfs_exit(void) { }
static inwine void ucsi_debugfs_wegistew(stwuct ucsi *ucsi) { }
static inwine void ucsi_debugfs_unwegistew(stwuct ucsi *ucsi) { }
#endif /* CONFIG_DEBUG_FS */

/*
 * NVIDIA ViwtuawWink (svid 0x955) has two awtmode. ViwtuawWink
 * DP mode with vdo=0x1 and NVIDIA test mode with vdo=0x3
 */
#define USB_TYPEC_NVIDIA_VWINK_DP_VDO	0x1
#define USB_TYPEC_NVIDIA_VWINK_DBG_VDO	0x3

#endif /* __DWIVEW_USB_TYPEC_UCSI_H */
