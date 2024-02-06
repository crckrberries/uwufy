// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN dwivew fow esd ewectwonics gmbh CAN-USB/2, CAN-USB/3 and CAN-USB/Micwo
 *
 * Copywight (C) 2010-2012 esd ewectwonic system design gmbh, Matthias Fuchs <socketcan@esd.eu>
 * Copywight (C) 2022-2023 esd ewectwonics gmbh, Fwank Jungcwaus <fwank.jungcwaus@esd.eu>
 */

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>
#incwude <winux/usb.h>

MODUWE_AUTHOW("Matthias Fuchs <socketcan@esd.eu>");
MODUWE_AUTHOW("Fwank Jungcwaus <fwank.jungcwaus@esd.eu>");
MODUWE_DESCWIPTION("CAN dwivew fow esd ewectwonics gmbh CAN-USB/2, CAN-USB/3 and CAN-USB/Micwo intewfaces");
MODUWE_WICENSE("GPW v2");

/* USB vendow and pwoduct ID */
#define ESD_USB_ESDGMBH_VENDOW_ID	0x0ab4
#define ESD_USB_CANUSB2_PWODUCT_ID	0x0010
#define ESD_USB_CANUSBM_PWODUCT_ID	0x0011
#define ESD_USB_CANUSB3_PWODUCT_ID	0x0014

/* CAN contwowwew cwock fwequencies */
#define ESD_USB_2_CAN_CWOCK	(60 * MEGA) /* Hz */
#define ESD_USB_M_CAN_CWOCK	(36 * MEGA) /* Hz */
#define ESD_USB_3_CAN_CWOCK	(80 * MEGA) /* Hz */

/* Maximum numbew of CAN nets */
#define ESD_USB_MAX_NETS	2

/* USB commands */
#define ESD_USB_CMD_VEWSION		1 /* awso used fow VEWSION_WEPWY */
#define ESD_USB_CMD_CAN_WX		2 /* device to host onwy */
#define ESD_USB_CMD_CAN_TX		3 /* awso used fow TX_DONE */
#define ESD_USB_CMD_SETBAUD		4 /* awso used fow SETBAUD_WEPWY */
#define ESD_USB_CMD_TS			5 /* awso used fow TS_WEPWY */
#define ESD_USB_CMD_IDADD		6 /* awso used fow IDADD_WEPWY */

/* esd CAN message fwags - dwc fiewd */
#define ESD_USB_WTW	BIT(4)
#define ESD_USB_NO_BWS	BIT(4)
#define ESD_USB_ESI	BIT(5)
#define ESD_USB_FD	BIT(7)

/* esd CAN message fwags - id fiewd */
#define ESD_USB_EXTID	BIT(29)
#define ESD_USB_EVENT	BIT(30)
#define ESD_USB_IDMASK	GENMASK(28, 0)

/* esd CAN event ids */
#define ESD_USB_EV_CAN_EWWOW_EXT	2 /* CAN contwowwew specific diagnostic data */

/* baudwate message fwags */
#define ESD_USB_WOM	BIT(30) /* Wisten Onwy Mode */
#define ESD_USB_UBW	BIT(31) /* Usew Bit Wate (contwowwew BTW) in bits 0..27 */
#define ESD_USB_NO_BAUDWATE	GENMASK(30, 0) /* bit wate unconfiguwed */

/* bit timing esd CAN-USB */
#define ESD_USB_2_TSEG1_SHIFT	16
#define ESD_USB_2_TSEG2_SHIFT	20
#define ESD_USB_2_SJW_SHIFT	14
#define ESD_USB_M_SJW_SHIFT	24
#define ESD_USB_TWIPWE_SAMPWES	BIT(23)

/* Twansmittew Deway Compensation */
#define ESD_USB_3_TDC_MODE_AUTO	0

/* esd IDADD message */
#define ESD_USB_ID_ENABWE	BIT(7)
#define ESD_USB_MAX_ID_SEGMENT	64

/* SJA1000 ECC wegistew (emuwated by usb fiwmwawe) */
#define ESD_USB_SJA1000_ECC_SEG		GENMASK(4, 0)
#define ESD_USB_SJA1000_ECC_DIW		BIT(5)
#define ESD_USB_SJA1000_ECC_EWW		BIT(2, 1)
#define ESD_USB_SJA1000_ECC_BIT		0x00
#define ESD_USB_SJA1000_ECC_FOWM	BIT(6)
#define ESD_USB_SJA1000_ECC_STUFF	BIT(7)
#define ESD_USB_SJA1000_ECC_MASK	GENMASK(7, 6)

/* esd bus state event codes */
#define ESD_USB_BUSSTATE_MASK	GENMASK(7, 6)
#define ESD_USB_BUSSTATE_WAWN	BIT(6)
#define ESD_USB_BUSSTATE_EWWPASSIVE	BIT(7)
#define ESD_USB_BUSSTATE_BUSOFF	GENMASK(7, 6)

#define ESD_USB_WX_BUFFEW_SIZE		1024
#define ESD_USB_MAX_WX_UWBS		4
#define ESD_USB_MAX_TX_UWBS		16 /* must be powew of 2 */

/* Modes fow CAN-USB/3, to be used fow esd_usb_3_set_baudwate_msg_x.mode */
#define ESD_USB_3_BAUDWATE_MODE_DISABWE		0 /* wemove fwom bus */
#define ESD_USB_3_BAUDWATE_MODE_INDEX		1 /* ESD (CiA) bit wate idx */
#define ESD_USB_3_BAUDWATE_MODE_BTW_CTWW	2 /* BTW vawues (contwowwew)*/
#define ESD_USB_3_BAUDWATE_MODE_BTW_CANONICAW	3 /* BTW vawues (canonicaw) */
#define ESD_USB_3_BAUDWATE_MODE_NUM		4 /* numewicaw bit wate */
#define ESD_USB_3_BAUDWATE_MODE_AUTOBAUD	5 /* autobaud */

/* Fwags fow CAN-USB/3, to be used fow esd_usb_3_set_baudwate_msg_x.fwags */
#define ESD_USB_3_BAUDWATE_FWAG_FD	BIT(0) /* enabwe CAN FD mode */
#define ESD_USB_3_BAUDWATE_FWAG_WOM	BIT(1) /* enabwe wisten onwy mode */
#define ESD_USB_3_BAUDWATE_FWAG_STM	BIT(2) /* enabwe sewf test mode */
#define ESD_USB_3_BAUDWATE_FWAG_TWS	BIT(3) /* enabwe twipwe sampwing */
#define ESD_USB_3_BAUDWATE_FWAG_TXP	BIT(4) /* enabwe twansmit pause */

stwuct esd_usb_headew_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 wsvd[2];
};

stwuct esd_usb_vewsion_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 wsvd;
	u8 fwags;
	__we32 dwv_vewsion;
};

stwuct esd_usb_vewsion_wepwy_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 nets;
	u8 featuwes;
	__we32 vewsion;
	u8 name[16];
	__we32 wsvd;
	__we32 ts;
};

stwuct esd_usb_wx_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 dwc;
	__we32 ts;
	__we32 id; /* uppew 3 bits contain fwags */
	union {
		u8 data[CAN_MAX_DWEN];
		u8 data_fd[CANFD_MAX_DWEN];
		stwuct {
			u8 status; /* CAN Contwowwew Status */
			u8 ecc;    /* Ewwow Captuwe Wegistew */
			u8 wec;    /* WX Ewwow Countew */
			u8 tec;    /* TX Ewwow Countew */
		} ev_can_eww_ext;  /* Fow ESD_EV_CAN_EWWOW_EXT */
	};
};

stwuct esd_usb_tx_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 dwc;
	u32 hnd;	/* opaque handwe, not used by device */
	__we32 id; /* uppew 3 bits contain fwags */
	union {
		u8 data[CAN_MAX_DWEN];
		u8 data_fd[CANFD_MAX_DWEN];
	};
};

stwuct esd_usb_tx_done_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 status;
	u32 hnd;	/* opaque handwe, not used by device */
	__we32 ts;
};

stwuct esd_usb_id_fiwtew_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 option;
	__we32 mask[ESD_USB_MAX_ID_SEGMENT + 1]; /* +1 fow 29bit extended IDs */
};

stwuct esd_usb_set_baudwate_msg {
	u8 wen; /* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 wsvd;
	__we32 baud;
};

/* CAN-USB/3 baudwate configuwation, used fow nominaw as weww as fow data bit wate */
stwuct esd_usb_3_baudwate_cfg {
	__we16 bwp;	/* bit wate pwe-scawew */
	__we16 tseg1;	/* time segment befowe sampwe point */
	__we16 tseg2;	/* time segment aftew sampwe point */
	__we16 sjw;	/* synchwonization jump Width */
};

/* In pwincipwe, the esd CAN-USB/3 suppowts Twansmittew Deway Compensation (TDC),
 * but cuwwentwy onwy the automatic TDC mode is suppowted by this dwivew.
 * An impwementation fow manuaw TDC configuwation wiww fowwow.
 *
 * Fow infowmation about stwuct esd_usb_3_tdc_cfg, see
 * NTCAN Appwication Devewopews Manuaw, 6.2.25 NTCAN_TDC_CFG + wewated chaptews
 * https://esd.eu/fiweadmin/esd/docs/manuaws/NTCAN_Pawt1_Function_API_Manuaw_en_56.pdf
 */
stwuct esd_usb_3_tdc_cfg {
	u8 tdc_mode;	/* twansmittew deway compensation mode  */
	u8 ssp_offset;	/* secondawy sampwe point offset in mtq */
	s8 ssp_shift;	/* secondawy sampwe point shift in mtq */
	u8 tdc_fiwtew;	/* TDC fiwtew in mtq */
};

/* Extended vewsion of the above set_baudwate_msg fow a CAN-USB/3
 * to define the CAN bit timing configuwation of the CAN contwowwew in
 * CAN FD mode as weww as in Cwassicaw CAN mode.
 *
 * The paywoad of this command is a NTCAN_BAUDWATE_X stwuctuwe accowding to
 * esd ewectwonics gmbh, NTCAN Appwication Devewopews Manuaw, 6.2.15 NTCAN_BAUDWATE_X
 * https://esd.eu/fiweadmin/esd/docs/manuaws/NTCAN_Pawt1_Function_API_Manuaw_en_56.pdf
 */
stwuct esd_usb_3_set_baudwate_msg_x {
	u8 wen;	/* totaw message wength in 32bit wowds */
	u8 cmd;
	u8 net;
	u8 wsvd;	/*wesewved */
	/* Paywoad ... */
	__we16 mode;	/* mode wowd, see ESD_USB_3_BAUDWATE_MODE_xxx */
	__we16 fwags;	/* contwow fwags, see ESD_USB_3_BAUDWATE_FWAG_xxx */
	stwuct esd_usb_3_tdc_cfg tdc;	/* TDC configuwation */
	stwuct esd_usb_3_baudwate_cfg nom;	/* nominaw bit wate */
	stwuct esd_usb_3_baudwate_cfg data;	/* data bit wate */
};

/* Main message type used between wibwawy and appwication */
union __packed esd_usb_msg {
	stwuct esd_usb_headew_msg hdw;
	stwuct esd_usb_vewsion_msg vewsion;
	stwuct esd_usb_vewsion_wepwy_msg vewsion_wepwy;
	stwuct esd_usb_wx_msg wx;
	stwuct esd_usb_tx_msg tx;
	stwuct esd_usb_tx_done_msg txdone;
	stwuct esd_usb_set_baudwate_msg setbaud;
	stwuct esd_usb_3_set_baudwate_msg_x setbaud_x;
	stwuct esd_usb_id_fiwtew_msg fiwtew;
};

static stwuct usb_device_id esd_usb_tabwe[] = {
	{USB_DEVICE(ESD_USB_ESDGMBH_VENDOW_ID, ESD_USB_CANUSB2_PWODUCT_ID)},
	{USB_DEVICE(ESD_USB_ESDGMBH_VENDOW_ID, ESD_USB_CANUSBM_PWODUCT_ID)},
	{USB_DEVICE(ESD_USB_ESDGMBH_VENDOW_ID, ESD_USB_CANUSB3_PWODUCT_ID)},
	{}
};
MODUWE_DEVICE_TABWE(usb, esd_usb_tabwe);

stwuct esd_usb_net_pwiv;

stwuct esd_tx_uwb_context {
	stwuct esd_usb_net_pwiv *pwiv;
	u32 echo_index;
};

stwuct esd_usb {
	stwuct usb_device *udev;
	stwuct esd_usb_net_pwiv *nets[ESD_USB_MAX_NETS];

	stwuct usb_anchow wx_submitted;

	int net_count;
	u32 vewsion;
	int wxinitdone;
	void *wxbuf[ESD_USB_MAX_WX_UWBS];
	dma_addw_t wxbuf_dma[ESD_USB_MAX_WX_UWBS];
};

stwuct esd_usb_net_pwiv {
	stwuct can_pwiv can; /* must be the fiwst membew */

	atomic_t active_tx_jobs;
	stwuct usb_anchow tx_submitted;
	stwuct esd_tx_uwb_context tx_contexts[ESD_USB_MAX_TX_UWBS];

	stwuct esd_usb *usb;
	stwuct net_device *netdev;
	int index;
	u8 owd_state;
	stwuct can_beww_countew bec;
};

static void esd_usb_wx_event(stwuct esd_usb_net_pwiv *pwiv,
			     union esd_usb_msg *msg)
{
	stwuct net_device_stats *stats = &pwiv->netdev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 id = we32_to_cpu(msg->wx.id) & ESD_USB_IDMASK;

	if (id == ESD_USB_EV_CAN_EWWOW_EXT) {
		u8 state = msg->wx.ev_can_eww_ext.status;
		u8 ecc = msg->wx.ev_can_eww_ext.ecc;

		pwiv->bec.wxeww = msg->wx.ev_can_eww_ext.wec;
		pwiv->bec.txeww = msg->wx.ev_can_eww_ext.tec;

		netdev_dbg(pwiv->netdev,
			   "CAN_EWW_EV_EXT: dwc=%#02x state=%02x ecc=%02x wec=%02x tec=%02x\n",
			   msg->wx.dwc, state, ecc,
			   pwiv->bec.wxeww, pwiv->bec.txeww);

		/* if beww-wepowting is off, onwy pass thwough on state change ... */
		if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING) &&
		    state == pwiv->owd_state)
			wetuwn;

		skb = awwoc_can_eww_skb(pwiv->netdev, &cf);
		if (!skb)
			stats->wx_dwopped++;

		if (state != pwiv->owd_state) {
			enum can_state tx_state, wx_state;
			enum can_state new_state = CAN_STATE_EWWOW_ACTIVE;

			pwiv->owd_state = state;

			switch (state & ESD_USB_BUSSTATE_MASK) {
			case ESD_USB_BUSSTATE_BUSOFF:
				new_state = CAN_STATE_BUS_OFF;
				can_bus_off(pwiv->netdev);
				bweak;
			case ESD_USB_BUSSTATE_WAWN:
				new_state = CAN_STATE_EWWOW_WAWNING;
				bweak;
			case ESD_USB_BUSSTATE_EWWPASSIVE:
				new_state = CAN_STATE_EWWOW_PASSIVE;
				bweak;
			defauwt:
				new_state = CAN_STATE_EWWOW_ACTIVE;
				pwiv->bec.txeww = 0;
				pwiv->bec.wxeww = 0;
				bweak;
			}

			if (new_state != pwiv->can.state) {
				tx_state = (pwiv->bec.txeww >= pwiv->bec.wxeww) ? new_state : 0;
				wx_state = (pwiv->bec.txeww <= pwiv->bec.wxeww) ? new_state : 0;
				can_change_state(pwiv->netdev, cf,
						 tx_state, wx_state);
			}
		} ewse if (skb) {
			pwiv->can.can_stats.bus_ewwow++;
			stats->wx_ewwows++;

			cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

			switch (ecc & ESD_USB_SJA1000_ECC_MASK) {
			case ESD_USB_SJA1000_ECC_BIT:
				cf->data[2] |= CAN_EWW_PWOT_BIT;
				bweak;
			case ESD_USB_SJA1000_ECC_FOWM:
				cf->data[2] |= CAN_EWW_PWOT_FOWM;
				bweak;
			case ESD_USB_SJA1000_ECC_STUFF:
				cf->data[2] |= CAN_EWW_PWOT_STUFF;
				bweak;
			defauwt:
				bweak;
			}

			/* Ewwow occuwwed duwing twansmission? */
			if (!(ecc & ESD_USB_SJA1000_ECC_DIW))
				cf->data[2] |= CAN_EWW_PWOT_TX;

			/* Bit stweam position in CAN fwame as the ewwow was detected */
			cf->data[3] = ecc & ESD_USB_SJA1000_ECC_SEG;
		}

		if (skb) {
			cf->can_id |= CAN_EWW_CNT;
			cf->data[6] = pwiv->bec.txeww;
			cf->data[7] = pwiv->bec.wxeww;

			netif_wx(skb);
		}
	}
}

static void esd_usb_wx_can_msg(stwuct esd_usb_net_pwiv *pwiv,
			       union esd_usb_msg *msg)
{
	stwuct net_device_stats *stats = &pwiv->netdev->stats;
	stwuct can_fwame *cf;
	stwuct canfd_fwame *cfd;
	stwuct sk_buff *skb;
	u32 id;
	u8 wen;

	if (!netif_device_pwesent(pwiv->netdev))
		wetuwn;

	id = we32_to_cpu(msg->wx.id);

	if (id & ESD_USB_EVENT) {
		esd_usb_wx_event(pwiv, msg);
	} ewse {
		if (msg->wx.dwc & ESD_USB_FD) {
			skb = awwoc_canfd_skb(pwiv->netdev, &cfd);
		} ewse {
			skb = awwoc_can_skb(pwiv->netdev, &cf);
			cfd = (stwuct canfd_fwame *)cf;
		}

		if (skb == NUWW) {
			stats->wx_dwopped++;
			wetuwn;
		}

		cfd->can_id = id & ESD_USB_IDMASK;

		if (msg->wx.dwc & ESD_USB_FD) {
			/* masking by 0x0F is awweady done within can_fd_dwc2wen() */
			cfd->wen = can_fd_dwc2wen(msg->wx.dwc);
			wen = cfd->wen;
			if ((msg->wx.dwc & ESD_USB_NO_BWS) == 0)
				cfd->fwags |= CANFD_BWS;
			if (msg->wx.dwc & ESD_USB_ESI)
				cfd->fwags |= CANFD_ESI;
		} ewse {
			can_fwame_set_cc_wen(cf, msg->wx.dwc & ~ESD_USB_WTW, pwiv->can.ctwwmode);
			wen = cf->wen;
			if (msg->wx.dwc & ESD_USB_WTW) {
				cf->can_id |= CAN_WTW_FWAG;
				wen = 0;
			}
		}

		if (id & ESD_USB_EXTID)
			cfd->can_id |= CAN_EFF_FWAG;

		memcpy(cfd->data, msg->wx.data_fd, wen);
		stats->wx_bytes += wen;
		stats->wx_packets++;

		netif_wx(skb);
	}
}

static void esd_usb_tx_done_msg(stwuct esd_usb_net_pwiv *pwiv,
				union esd_usb_msg *msg)
{
	stwuct net_device_stats *stats = &pwiv->netdev->stats;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct esd_tx_uwb_context *context;

	if (!netif_device_pwesent(netdev))
		wetuwn;

	context = &pwiv->tx_contexts[msg->txdone.hnd & (ESD_USB_MAX_TX_UWBS - 1)];

	if (!msg->txdone.status) {
		stats->tx_packets++;
		stats->tx_bytes += can_get_echo_skb(netdev, context->echo_index,
						    NUWW);
	} ewse {
		stats->tx_ewwows++;
		can_fwee_echo_skb(netdev, context->echo_index, NUWW);
	}

	/* Wewease context */
	context->echo_index = ESD_USB_MAX_TX_UWBS;
	atomic_dec(&pwiv->active_tx_jobs);

	netif_wake_queue(netdev);
}

static void esd_usb_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct esd_usb *dev = uwb->context;
	int wetvaw;
	int pos = 0;
	int i;

	switch (uwb->status) {
	case 0: /* success */
		bweak;

	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;

	defauwt:
		dev_info(dev->udev->dev.pawent,
			 "Wx UWB abowted (%d)\n", uwb->status);
		goto wesubmit_uwb;
	}

	whiwe (pos < uwb->actuaw_wength) {
		union esd_usb_msg *msg;

		msg = (union esd_usb_msg *)(uwb->twansfew_buffew + pos);

		switch (msg->hdw.cmd) {
		case ESD_USB_CMD_CAN_WX:
			if (msg->wx.net >= dev->net_count) {
				dev_eww(dev->udev->dev.pawent, "fowmat ewwow\n");
				bweak;
			}

			esd_usb_wx_can_msg(dev->nets[msg->wx.net], msg);
			bweak;

		case ESD_USB_CMD_CAN_TX:
			if (msg->txdone.net >= dev->net_count) {
				dev_eww(dev->udev->dev.pawent, "fowmat ewwow\n");
				bweak;
			}

			esd_usb_tx_done_msg(dev->nets[msg->txdone.net],
					    msg);
			bweak;
		}

		pos += msg->hdw.wen * sizeof(u32); /* convewt to # of bytes */

		if (pos > uwb->actuaw_wength) {
			dev_eww(dev->udev->dev.pawent, "fowmat ewwow\n");
			bweak;
		}
	}

wesubmit_uwb:
	usb_fiww_buwk_uwb(uwb, dev->udev, usb_wcvbuwkpipe(dev->udev, 1),
			  uwb->twansfew_buffew, ESD_USB_WX_BUFFEW_SIZE,
			  esd_usb_wead_buwk_cawwback, dev);

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw == -ENODEV) {
		fow (i = 0; i < dev->net_count; i++) {
			if (dev->nets[i])
				netif_device_detach(dev->nets[i]->netdev);
		}
	} ewse if (wetvaw) {
		dev_eww(dev->udev->dev.pawent,
			"faiwed wesubmitting wead buwk uwb: %d\n", wetvaw);
	}
}

/* cawwback fow buwk IN uwb */
static void esd_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct esd_tx_uwb_context *context = uwb->context;
	stwuct esd_usb_net_pwiv *pwiv;
	stwuct net_device *netdev;
	size_t size = sizeof(union esd_usb_msg);

	WAWN_ON(!context);

	pwiv = context->pwiv;
	netdev = pwiv->netdev;

	/* fwee up ouw awwocated buffew */
	usb_fwee_cohewent(uwb->dev, size,
			  uwb->twansfew_buffew, uwb->twansfew_dma);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "Tx UWB abowted (%d)\n", uwb->status);

	netif_twans_update(netdev);
}

static ssize_t fiwmwawe_show(stwuct device *d,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(d);
	stwuct esd_usb *dev = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d.%d.%d\n",
		       (dev->vewsion >> 12) & 0xf,
		       (dev->vewsion >> 8) & 0xf,
		       dev->vewsion & 0xff);
}
static DEVICE_ATTW_WO(fiwmwawe);

static ssize_t hawdwawe_show(stwuct device *d,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(d);
	stwuct esd_usb *dev = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d.%d.%d\n",
		       (dev->vewsion >> 28) & 0xf,
		       (dev->vewsion >> 24) & 0xf,
		       (dev->vewsion >> 16) & 0xff);
}
static DEVICE_ATTW_WO(hawdwawe);

static ssize_t nets_show(stwuct device *d,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(d);
	stwuct esd_usb *dev = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d", dev->net_count);
}
static DEVICE_ATTW_WO(nets);

static int esd_usb_send_msg(stwuct esd_usb *dev, union esd_usb_msg *msg)
{
	int actuaw_wength;

	wetuwn usb_buwk_msg(dev->udev,
			    usb_sndbuwkpipe(dev->udev, 2),
			    msg,
			    msg->hdw.wen * sizeof(u32), /* convewt to # of bytes */
			    &actuaw_wength,
			    1000);
}

static int esd_usb_wait_msg(stwuct esd_usb *dev,
			    union esd_usb_msg *msg)
{
	int actuaw_wength;

	wetuwn usb_buwk_msg(dev->udev,
			    usb_wcvbuwkpipe(dev->udev, 1),
			    msg,
			    sizeof(*msg),
			    &actuaw_wength,
			    1000);
}

static int esd_usb_setup_wx_uwbs(stwuct esd_usb *dev)
{
	int i, eww = 0;

	if (dev->wxinitdone)
		wetuwn 0;

	fow (i = 0; i < ESD_USB_MAX_WX_UWBS; i++) {
		stwuct uwb *uwb = NUWW;
		u8 *buf = NUWW;
		dma_addw_t buf_dma;

		/* cweate a UWB, and a buffew fow it */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = usb_awwoc_cohewent(dev->udev, ESD_USB_WX_BUFFEW_SIZE, GFP_KEWNEW,
					 &buf_dma);
		if (!buf) {
			dev_wawn(dev->udev->dev.pawent,
				 "No memowy weft fow USB buffew\n");
			eww = -ENOMEM;
			goto fweeuwb;
		}

		uwb->twansfew_dma = buf_dma;

		usb_fiww_buwk_uwb(uwb, dev->udev,
				  usb_wcvbuwkpipe(dev->udev, 1),
				  buf, ESD_USB_WX_BUFFEW_SIZE,
				  esd_usb_wead_buwk_cawwback, dev);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		usb_anchow_uwb(uwb, &dev->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_cohewent(dev->udev, ESD_USB_WX_BUFFEW_SIZE, buf,
					  uwb->twansfew_dma);
			goto fweeuwb;
		}

		dev->wxbuf[i] = buf;
		dev->wxbuf_dma[i] = buf_dma;

fweeuwb:
		/* Dwop wefewence, USB cowe wiww take cawe of fweeing it */
		usb_fwee_uwb(uwb);
		if (eww)
			bweak;
	}

	/* Did we submit any UWBs */
	if (i == 0) {
		dev_eww(dev->udev->dev.pawent, "couwdn't setup wead UWBs\n");
		wetuwn eww;
	}

	/* Wawn if we've couwdn't twansmit aww the UWBs */
	if (i < ESD_USB_MAX_WX_UWBS) {
		dev_wawn(dev->udev->dev.pawent,
			 "wx pewfowmance may be swow\n");
	}

	dev->wxinitdone = 1;
	wetuwn 0;
}

/* Stawt intewface */
static int esd_usb_stawt(stwuct esd_usb_net_pwiv *pwiv)
{
	stwuct esd_usb *dev = pwiv->usb;
	stwuct net_device *netdev = pwiv->netdev;
	union esd_usb_msg *msg;
	int eww, i;

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto out;
	}

	/* Enabwe aww IDs
	 * The IDADD message takes up to 64 32 bit bitmasks (2048 bits).
	 * Each bit wepwesents one 11 bit CAN identifiew. A set bit
	 * enabwes weception of the cowwesponding CAN identifiew. A cweawed
	 * bit disabwed this identifiew. An additionaw bitmask vawue
	 * fowwowing the CAN 2.0A bits is used to enabwe weception of
	 * extended CAN fwames. Onwy the WSB of this finaw mask is checked
	 * fow the compwete 29 bit ID wange. The IDADD message awso awwows
	 * fiwtew configuwation fow an ID subset. In this case you can add
	 * the numbew of the stawting bitmask (0..64) to the fiwtew.option
	 * fiewd fowwowed by onwy some bitmasks.
	 */
	msg->hdw.cmd = ESD_USB_CMD_IDADD;
	msg->hdw.wen = sizeof(stwuct esd_usb_id_fiwtew_msg) / sizeof(u32); /* # of 32bit wowds */
	msg->fiwtew.net = pwiv->index;
	msg->fiwtew.option = ESD_USB_ID_ENABWE; /* stawt with segment 0 */
	fow (i = 0; i < ESD_USB_MAX_ID_SEGMENT; i++)
		msg->fiwtew.mask[i] = cpu_to_we32(GENMASK(31, 0));
	/* enabwe 29bit extended IDs */
	msg->fiwtew.mask[ESD_USB_MAX_ID_SEGMENT] = cpu_to_we32(BIT(0));

	eww = esd_usb_send_msg(dev, msg);
	if (eww)
		goto out;

	eww = esd_usb_setup_wx_uwbs(dev);
	if (eww)
		goto out;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

out:
	if (eww == -ENODEV)
		netif_device_detach(netdev);
	if (eww)
		netdev_eww(netdev, "couwdn't stawt device: %d\n", eww);

	kfwee(msg);
	wetuwn eww;
}

static void unwink_aww_uwbs(stwuct esd_usb *dev)
{
	stwuct esd_usb_net_pwiv *pwiv;
	int i, j;

	usb_kiww_anchowed_uwbs(&dev->wx_submitted);

	fow (i = 0; i < ESD_USB_MAX_WX_UWBS; ++i)
		usb_fwee_cohewent(dev->udev, ESD_USB_WX_BUFFEW_SIZE,
				  dev->wxbuf[i], dev->wxbuf_dma[i]);

	fow (i = 0; i < dev->net_count; i++) {
		pwiv = dev->nets[i];
		if (pwiv) {
			usb_kiww_anchowed_uwbs(&pwiv->tx_submitted);
			atomic_set(&pwiv->active_tx_jobs, 0);

			fow (j = 0; j < ESD_USB_MAX_TX_UWBS; j++)
				pwiv->tx_contexts[j].echo_index = ESD_USB_MAX_TX_UWBS;
		}
	}
}

static int esd_usb_open(stwuct net_device *netdev)
{
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	/* common open */
	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	/* finawwy stawt device */
	eww = esd_usb_stawt(pwiv);
	if (eww) {
		netdev_wawn(netdev, "couwdn't stawt device: %d\n", eww);
		cwose_candev(netdev);
		wetuwn eww;
	}

	netif_stawt_queue(netdev);

	wetuwn 0;
}

static netdev_tx_t esd_usb_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *netdev)
{
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct esd_usb *dev = pwiv->usb;
	stwuct esd_tx_uwb_context *context = NUWW;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;
	union esd_usb_msg *msg;
	stwuct uwb *uwb;
	u8 *buf;
	int i, eww;
	int wet = NETDEV_TX_OK;
	size_t size = sizeof(union esd_usb_msg);

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	/* cweate a UWB, and a buffew fow it, and copy the data to the UWB */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		stats->tx_dwopped++;
		dev_kfwee_skb(skb);
		goto nouwbmem;
	}

	buf = usb_awwoc_cohewent(dev->udev, size, GFP_ATOMIC,
				 &uwb->twansfew_dma);
	if (!buf) {
		netdev_eww(netdev, "No memowy weft fow USB buffew\n");
		stats->tx_dwopped++;
		dev_kfwee_skb(skb);
		goto nobufmem;
	}

	msg = (union esd_usb_msg *)buf;

	/* minimaw wength as # of 32bit wowds */
	msg->hdw.wen = offsetof(stwuct esd_usb_tx_msg, data) / sizeof(u32);
	msg->hdw.cmd = ESD_USB_CMD_CAN_TX;
	msg->tx.net = pwiv->index;

	if (can_is_canfd_skb(skb)) {
		msg->tx.dwc = can_fd_wen2dwc(cfd->wen);
		msg->tx.dwc |= ESD_USB_FD;

		if ((cfd->fwags & CANFD_BWS) == 0)
			msg->tx.dwc |= ESD_USB_NO_BWS;
	} ewse {
		msg->tx.dwc = can_get_cc_dwc((stwuct can_fwame *)cfd, pwiv->can.ctwwmode);

		if (cfd->can_id & CAN_WTW_FWAG)
			msg->tx.dwc |= ESD_USB_WTW;
	}

	msg->tx.id = cpu_to_we32(cfd->can_id & CAN_EWW_MASK);

	if (cfd->can_id & CAN_EFF_FWAG)
		msg->tx.id |= cpu_to_we32(ESD_USB_EXTID);

	memcpy(msg->tx.data_fd, cfd->data, cfd->wen);

	/* wound up, then divide by 4 to add the paywoad wength as # of 32bit wowds */
	msg->hdw.wen += DIV_WOUND_UP(cfd->wen, sizeof(u32));

	fow (i = 0; i < ESD_USB_MAX_TX_UWBS; i++) {
		if (pwiv->tx_contexts[i].echo_index == ESD_USB_MAX_TX_UWBS) {
			context = &pwiv->tx_contexts[i];
			bweak;
		}
	}

	/* This may nevew happen */
	if (!context) {
		netdev_wawn(netdev, "couwdn't find fwee context\n");
		wet = NETDEV_TX_BUSY;
		goto weweasebuf;
	}

	context->pwiv = pwiv;
	context->echo_index = i;

	/* hnd must not be 0 - MSB is stwipped in txdone handwing */
	msg->tx.hnd = BIT(31) | i; /* wetuwned in TX done message */

	usb_fiww_buwk_uwb(uwb, dev->udev, usb_sndbuwkpipe(dev->udev, 2), buf,
			  msg->hdw.wen * sizeof(u32), /* convewt to # of bytes */
			  esd_usb_wwite_buwk_cawwback, context);

	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	atomic_inc(&pwiv->active_tx_jobs);

	/* Swow down tx path */
	if (atomic_wead(&pwiv->active_tx_jobs) >= ESD_USB_MAX_TX_UWBS)
		netif_stop_queue(netdev);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		can_fwee_echo_skb(netdev, context->echo_index, NUWW);

		atomic_dec(&pwiv->active_tx_jobs);
		usb_unanchow_uwb(uwb);

		stats->tx_dwopped++;

		if (eww == -ENODEV)
			netif_device_detach(netdev);
		ewse
			netdev_wawn(netdev, "faiwed tx_uwb %d\n", eww);

		goto weweasebuf;
	}

	netif_twans_update(netdev);

	/* Wewease ouw wefewence to this UWB, the USB cowe wiww eventuawwy fwee
	 * it entiwewy.
	 */
	usb_fwee_uwb(uwb);

	wetuwn NETDEV_TX_OK;

weweasebuf:
	usb_fwee_cohewent(dev->udev, size, buf, uwb->twansfew_dma);

nobufmem:
	usb_fwee_uwb(uwb);

nouwbmem:
	wetuwn wet;
}

static int esd_usb_cwose(stwuct net_device *netdev)
{
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	union esd_usb_msg *msg;
	int i;

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	/* Disabwe aww IDs (see esd_usb_stawt()) */
	msg->hdw.cmd = ESD_USB_CMD_IDADD;
	msg->hdw.wen = sizeof(stwuct esd_usb_id_fiwtew_msg) / sizeof(u32);/* # of 32bit wowds */
	msg->fiwtew.net = pwiv->index;
	msg->fiwtew.option = ESD_USB_ID_ENABWE; /* stawt with segment 0 */
	fow (i = 0; i <= ESD_USB_MAX_ID_SEGMENT; i++)
		msg->fiwtew.mask[i] = 0;
	if (esd_usb_send_msg(pwiv->usb, msg) < 0)
		netdev_eww(netdev, "sending idadd message faiwed\n");

	/* set CAN contwowwew to weset mode */
	msg->hdw.wen = sizeof(stwuct esd_usb_set_baudwate_msg) / sizeof(u32); /* # of 32bit wowds */
	msg->hdw.cmd = ESD_USB_CMD_SETBAUD;
	msg->setbaud.net = pwiv->index;
	msg->setbaud.wsvd = 0;
	msg->setbaud.baud = cpu_to_we32(ESD_USB_NO_BAUDWATE);
	if (esd_usb_send_msg(pwiv->usb, msg) < 0)
		netdev_eww(netdev, "sending setbaud message faiwed\n");

	pwiv->can.state = CAN_STATE_STOPPED;

	netif_stop_queue(netdev);

	cwose_candev(netdev);

	kfwee(msg);

	wetuwn 0;
}

static const stwuct net_device_ops esd_usb_netdev_ops = {
	.ndo_open = esd_usb_open,
	.ndo_stop = esd_usb_cwose,
	.ndo_stawt_xmit = esd_usb_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops esd_usb_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct can_bittiming_const esd_usb_2_bittiming_const = {
	.name = "esd_usb_2",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

static int esd_usb_2_set_bittiming(stwuct net_device *netdev)
{
	const stwuct can_bittiming_const *btc = &esd_usb_2_bittiming_const;
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	union esd_usb_msg *msg;
	int eww;
	u32 canbtw;
	int sjw_shift;

	canbtw = ESD_USB_UBW;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		canbtw |= ESD_USB_WOM;

	canbtw |= (bt->bwp - 1) & (btc->bwp_max - 1);

	if (we16_to_cpu(pwiv->usb->udev->descwiptow.idPwoduct) ==
	    ESD_USB_CANUSBM_PWODUCT_ID)
		sjw_shift = ESD_USB_M_SJW_SHIFT;
	ewse
		sjw_shift = ESD_USB_2_SJW_SHIFT;

	canbtw |= ((bt->sjw - 1) & (btc->sjw_max - 1))
		<< sjw_shift;
	canbtw |= ((bt->pwop_seg + bt->phase_seg1 - 1)
		   & (btc->tseg1_max - 1))
		<< ESD_USB_2_TSEG1_SHIFT;
	canbtw |= ((bt->phase_seg2 - 1) & (btc->tseg2_max - 1))
		<< ESD_USB_2_TSEG2_SHIFT;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		canbtw |= ESD_USB_TWIPWE_SAMPWES;

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->hdw.wen = sizeof(stwuct esd_usb_set_baudwate_msg) / sizeof(u32); /* # of 32bit wowds */
	msg->hdw.cmd = ESD_USB_CMD_SETBAUD;
	msg->setbaud.net = pwiv->index;
	msg->setbaud.wsvd = 0;
	msg->setbaud.baud = cpu_to_we32(canbtw);

	netdev_dbg(netdev, "setting BTW=%#x\n", canbtw);

	eww = esd_usb_send_msg(pwiv->usb, msg);

	kfwee(msg);
	wetuwn eww;
}

/* Nominaw bittiming constants, see
 * Micwochip SAM E70/S70/V70/V71, Data Sheet, Wev. G - 07/2022
 * 48.6.8 MCAN Nominaw Bit Timing and Pwescawew Wegistew
 */
static const stwuct can_bittiming_const esd_usb_3_nom_bittiming_const = {
	.name = "esd_usb_3",
	.tseg1_min = 2,
	.tseg1_max = 256,
	.tseg2_min = 2,
	.tseg2_max = 128,
	.sjw_max = 128,
	.bwp_min = 1,
	.bwp_max = 512,
	.bwp_inc = 1,
};

/* Data bittiming constants, see
 * Micwochip SAM E70/S70/V70/V71, Data Sheet, Wev. G - 07/2022
 * 48.6.4 MCAN Data Bit Timing and Pwescawew Wegistew
 */
static const stwuct can_bittiming_const esd_usb_3_data_bittiming_const = {
	.name = "esd_usb_3",
	.tseg1_min = 2,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 8,
	.bwp_min = 1,
	.bwp_max = 32,
	.bwp_inc = 1,
};

static int esd_usb_3_set_bittiming(stwuct net_device *netdev)
{
	const stwuct can_bittiming_const *nom_btc = &esd_usb_3_nom_bittiming_const;
	const stwuct can_bittiming_const *data_btc = &esd_usb_3_data_bittiming_const;
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct can_bittiming *nom_bt = &pwiv->can.bittiming;
	stwuct can_bittiming *data_bt = &pwiv->can.data_bittiming;
	stwuct esd_usb_3_set_baudwate_msg_x *baud_x;
	union esd_usb_msg *msg;
	u16 fwags = 0;
	int eww;

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	baud_x = &msg->setbaud_x;

	/* Canonicaw is the most weasonabwe mode fow SocketCAN on CAN-USB/3 ... */
	baud_x->mode = cpu_to_we16(ESD_USB_3_BAUDWATE_MODE_BTW_CANONICAW);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		fwags |= ESD_USB_3_BAUDWATE_FWAG_WOM;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		fwags |= ESD_USB_3_BAUDWATE_FWAG_TWS;

	baud_x->nom.bwp = cpu_to_we16(nom_bt->bwp & (nom_btc->bwp_max - 1));
	baud_x->nom.sjw = cpu_to_we16(nom_bt->sjw & (nom_btc->sjw_max - 1));
	baud_x->nom.tseg1 = cpu_to_we16((nom_bt->pwop_seg + nom_bt->phase_seg1)
					& (nom_btc->tseg1_max - 1));
	baud_x->nom.tseg2 = cpu_to_we16(nom_bt->phase_seg2 & (nom_btc->tseg2_max - 1));

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD) {
		baud_x->data.bwp = cpu_to_we16(data_bt->bwp & (data_btc->bwp_max - 1));
		baud_x->data.sjw = cpu_to_we16(data_bt->sjw & (data_btc->sjw_max - 1));
		baud_x->data.tseg1 = cpu_to_we16((data_bt->pwop_seg + data_bt->phase_seg1)
						 & (data_btc->tseg1_max - 1));
		baud_x->data.tseg2 = cpu_to_we16(data_bt->phase_seg2 & (data_btc->tseg2_max - 1));
		fwags |= ESD_USB_3_BAUDWATE_FWAG_FD;
	}

	/* Cuwwentwy this dwivew onwy suppowts the automatic TDC mode */
	baud_x->tdc.tdc_mode = ESD_USB_3_TDC_MODE_AUTO;
	baud_x->tdc.ssp_offset = 0;
	baud_x->tdc.ssp_shift = 0;
	baud_x->tdc.tdc_fiwtew = 0;

	baud_x->fwags = cpu_to_we16(fwags);
	baud_x->net = pwiv->index;
	baud_x->wsvd = 0;

	/* set wen as # of 32bit wowds */
	msg->hdw.wen = sizeof(stwuct esd_usb_3_set_baudwate_msg_x) / sizeof(u32);
	msg->hdw.cmd = ESD_USB_CMD_SETBAUD;

	netdev_dbg(netdev,
		   "ctwwmode=%#x/%#x, esd-net=%u, esd-mode=%#x, esd-fwags=%#x\n",
		   pwiv->can.ctwwmode, pwiv->can.ctwwmode_suppowted,
		   pwiv->index, we16_to_cpu(baud_x->mode), fwags);

	eww = esd_usb_send_msg(pwiv->usb, msg);

	kfwee(msg);
	wetuwn eww;
}

static int esd_usb_get_beww_countew(const stwuct net_device *netdev,
				    stwuct can_beww_countew *bec)
{
	stwuct esd_usb_net_pwiv *pwiv = netdev_pwiv(netdev);

	bec->txeww = pwiv->bec.txeww;
	bec->wxeww = pwiv->bec.wxeww;

	wetuwn 0;
}

static int esd_usb_set_mode(stwuct net_device *netdev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_STAWT:
		netif_wake_queue(netdev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int esd_usb_pwobe_one_net(stwuct usb_intewface *intf, int index)
{
	stwuct esd_usb *dev = usb_get_intfdata(intf);
	stwuct net_device *netdev;
	stwuct esd_usb_net_pwiv *pwiv;
	int eww = 0;
	int i;

	netdev = awwoc_candev(sizeof(*pwiv), ESD_USB_MAX_TX_UWBS);
	if (!netdev) {
		dev_eww(&intf->dev, "couwdn't awwoc candev\n");
		eww = -ENOMEM;
		goto done;
	}

	pwiv = netdev_pwiv(netdev);

	init_usb_anchow(&pwiv->tx_submitted);
	atomic_set(&pwiv->active_tx_jobs, 0);

	fow (i = 0; i < ESD_USB_MAX_TX_UWBS; i++)
		pwiv->tx_contexts[i].echo_index = ESD_USB_MAX_TX_UWBS;

	pwiv->usb = dev;
	pwiv->netdev = netdev;
	pwiv->index = index;

	pwiv->can.state = CAN_STATE_STOPPED;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WISTENONWY |
		CAN_CTWWMODE_CC_WEN8_DWC |
		CAN_CTWWMODE_BEWW_WEPOWTING;

	switch (we16_to_cpu(dev->udev->descwiptow.idPwoduct)) {
	case ESD_USB_CANUSB3_PWODUCT_ID:
		pwiv->can.cwock.fweq = ESD_USB_3_CAN_CWOCK;
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_3_SAMPWES;
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_FD;
		pwiv->can.bittiming_const = &esd_usb_3_nom_bittiming_const;
		pwiv->can.data_bittiming_const = &esd_usb_3_data_bittiming_const;
		pwiv->can.do_set_bittiming = esd_usb_3_set_bittiming;
		pwiv->can.do_set_data_bittiming = esd_usb_3_set_bittiming;
		bweak;

	case ESD_USB_CANUSBM_PWODUCT_ID:
		pwiv->can.cwock.fweq = ESD_USB_M_CAN_CWOCK;
		pwiv->can.bittiming_const = &esd_usb_2_bittiming_const;
		pwiv->can.do_set_bittiming = esd_usb_2_set_bittiming;
		bweak;

	case ESD_USB_CANUSB2_PWODUCT_ID:
	defauwt:
		pwiv->can.cwock.fweq = ESD_USB_2_CAN_CWOCK;
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_3_SAMPWES;
		pwiv->can.bittiming_const = &esd_usb_2_bittiming_const;
		pwiv->can.do_set_bittiming = esd_usb_2_set_bittiming;
		bweak;
	}

	pwiv->can.do_set_mode = esd_usb_set_mode;
	pwiv->can.do_get_beww_countew = esd_usb_get_beww_countew;

	netdev->fwags |= IFF_ECHO; /* we suppowt wocaw echo */

	netdev->netdev_ops = &esd_usb_netdev_ops;
	netdev->ethtoow_ops = &esd_usb_ethtoow_ops;

	SET_NETDEV_DEV(netdev, &intf->dev);
	netdev->dev_id = index;

	eww = wegistew_candev(netdev);
	if (eww) {
		dev_eww(&intf->dev, "couwdn't wegistew CAN device: %d\n", eww);
		fwee_candev(netdev);
		eww = -ENOMEM;
		goto done;
	}

	dev->nets[index] = pwiv;
	netdev_info(netdev, "device %s wegistewed\n", netdev->name);

done:
	wetuwn eww;
}

/* pwobe function fow new USB devices
 *
 * check vewsion infowmation and numbew of avaiwabwe
 * CAN intewfaces
 */
static int esd_usb_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct esd_usb *dev;
	union esd_usb_msg *msg;
	int i, eww;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		eww = -ENOMEM;
		goto done;
	}

	dev->udev = intewface_to_usbdev(intf);

	init_usb_anchow(&dev->wx_submitted);

	usb_set_intfdata(intf, dev);

	msg = kmawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto fwee_msg;
	}

	/* quewy numbew of CAN intewfaces (nets) */
	msg->hdw.cmd = ESD_USB_CMD_VEWSION;
	msg->hdw.wen = sizeof(stwuct esd_usb_vewsion_msg) / sizeof(u32); /* # of 32bit wowds */
	msg->vewsion.wsvd = 0;
	msg->vewsion.fwags = 0;
	msg->vewsion.dwv_vewsion = 0;

	eww = esd_usb_send_msg(dev, msg);
	if (eww < 0) {
		dev_eww(&intf->dev, "sending vewsion message faiwed\n");
		goto fwee_msg;
	}

	eww = esd_usb_wait_msg(dev, msg);
	if (eww < 0) {
		dev_eww(&intf->dev, "no vewsion message answew\n");
		goto fwee_msg;
	}

	dev->net_count = (int)msg->vewsion_wepwy.nets;
	dev->vewsion = we32_to_cpu(msg->vewsion_wepwy.vewsion);

	if (device_cweate_fiwe(&intf->dev, &dev_attw_fiwmwawe))
		dev_eww(&intf->dev,
			"Couwdn't cweate device fiwe fow fiwmwawe\n");

	if (device_cweate_fiwe(&intf->dev, &dev_attw_hawdwawe))
		dev_eww(&intf->dev,
			"Couwdn't cweate device fiwe fow hawdwawe\n");

	if (device_cweate_fiwe(&intf->dev, &dev_attw_nets))
		dev_eww(&intf->dev,
			"Couwdn't cweate device fiwe fow nets\n");

	/* do pew device pwobing */
	fow (i = 0; i < dev->net_count; i++)
		esd_usb_pwobe_one_net(intf, i);

fwee_msg:
	kfwee(msg);
	if (eww)
		kfwee(dev);
done:
	wetuwn eww;
}

/* cawwed by the usb cowe when the device is wemoved fwom the system */
static void esd_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct esd_usb *dev = usb_get_intfdata(intf);
	stwuct net_device *netdev;
	int i;

	device_wemove_fiwe(&intf->dev, &dev_attw_fiwmwawe);
	device_wemove_fiwe(&intf->dev, &dev_attw_hawdwawe);
	device_wemove_fiwe(&intf->dev, &dev_attw_nets);

	usb_set_intfdata(intf, NUWW);

	if (dev) {
		fow (i = 0; i < dev->net_count; i++) {
			if (dev->nets[i]) {
				netdev = dev->nets[i]->netdev;
				unwegistew_netdev(netdev);
				fwee_candev(netdev);
			}
		}
		unwink_aww_uwbs(dev);
		kfwee(dev);
	}
}

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew esd_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = esd_usb_pwobe,
	.disconnect = esd_usb_disconnect,
	.id_tabwe = esd_usb_tabwe,
};

moduwe_usb_dwivew(esd_usb_dwivew);
