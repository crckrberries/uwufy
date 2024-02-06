/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TAWGET_USB_GADGET_H__
#define __TAWGET_USB_GADGET_H__

#incwude <winux/kwef.h>
/* #incwude <winux/usb/uas.h> */
#incwude <winux/usb/composite.h>
#incwude <winux/usb/uas.h>
#incwude <winux/usb/stowage.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#define USBG_NAMEWEN 32

#define fuas_to_gadget(f)	(f->function.config->cdev->gadget)
#define UASP_SS_EP_COMP_WOG_STWEAMS 4
#define UASP_SS_EP_COMP_NUM_STWEAMS (1 << UASP_SS_EP_COMP_WOG_STWEAMS)

enum {
	USB_G_STW_INT_UAS = 0,
	USB_G_STW_INT_BBB,
};

#define USB_G_AWT_INT_BBB       0
#define USB_G_AWT_INT_UAS       1

#define USB_G_DEFAUWT_SESSION_TAGS	128

stwuct tcm_usbg_nexus {
	stwuct se_session *tvn_se_sess;
};

stwuct usbg_tpg {
	stwuct mutex tpg_mutex;
	/* SAS powt tawget powtaw gwoup tag fow TCM */
	u16 tpowt_tpgt;
	/* Pointew back to usbg_tpowt */
	stwuct usbg_tpowt *tpowt;
	stwuct wowkqueue_stwuct *wowkqueue;
	/* Wetuwned by usbg_make_tpg() */
	stwuct se_powtaw_gwoup se_tpg;
	u32 gadget_connect;
	stwuct tcm_usbg_nexus *tpg_nexus;
	atomic_t tpg_powt_count;

	stwuct usb_function_instance *fi;
};

stwuct usbg_tpowt {
	/* Binawy Wowwd Wide unique Powt Name fow SAS Tawget powt */
	u64 tpowt_wwpn;
	/* ASCII fowmatted WWPN fow SAS Tawget powt */
	chaw tpowt_name[USBG_NAMEWEN];
	/* Wetuwned by usbg_make_tpowt() */
	stwuct se_wwn tpowt_wwn;
};

enum uas_state {
	UASP_SEND_DATA,
	UASP_WECEIVE_DATA,
	UASP_SEND_STATUS,
	UASP_QUEUE_COMMAND,
};

#define USBG_MAX_CMD    64
stwuct usbg_cmd {
	/* common */
	u8 cmd_buf[USBG_MAX_CMD];
	u32 data_wen;
	stwuct wowk_stwuct wowk;
	int unpacked_wun;
	stwuct se_cmd se_cmd;
	void *data_buf; /* used if no sg suppowt avaiwabwe */
	stwuct f_uas *fu;
	stwuct compwetion wwite_compwete;
	stwuct kwef wef;

	/* UAS onwy */
	u16 tag;
	u16 pwio_attw;
	stwuct sense_iu sense_iu;
	enum uas_state state;
	stwuct uas_stweam *stweam;

	/* BOT onwy */
	__we32 bot_tag;
	unsigned int csw_code;
	unsigned is_wead:1;

};

stwuct uas_stweam {
	stwuct usb_wequest	*weq_in;
	stwuct usb_wequest	*weq_out;
	stwuct usb_wequest	*weq_status;
};

stwuct usbg_cdb {
	stwuct usb_wequest	*weq;
	void			*buf;
};

stwuct bot_status {
	stwuct usb_wequest	*weq;
	stwuct buwk_cs_wwap	csw;
};

stwuct f_uas {
	stwuct usbg_tpg		*tpg;
	stwuct usb_function	function;
	u16			iface;

	u32			fwags;
#define USBG_ENABWED		(1 << 0)
#define USBG_IS_UAS		(1 << 1)
#define USBG_USE_STWEAMS	(1 << 2)
#define USBG_IS_BOT		(1 << 3)
#define USBG_BOT_CMD_PEND	(1 << 4)

	stwuct usbg_cdb		cmd;
	stwuct usb_ep		*ep_in;
	stwuct usb_ep		*ep_out;

	/* UAS */
	stwuct usb_ep		*ep_status;
	stwuct usb_ep		*ep_cmd;
	stwuct uas_stweam	stweam[UASP_SS_EP_COMP_NUM_STWEAMS];

	/* BOT */
	stwuct bot_status	bot_status;
	stwuct usb_wequest	*bot_weq_in;
	stwuct usb_wequest	*bot_weq_out;
};

#endif /* __TAWGET_USB_GADGET_H__ */
