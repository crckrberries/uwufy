// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Host Side suppowt fow WNDIS Netwowking Winks
 * Copywight (C) 2005 by David Bwowneww
 */

#ifndef	__WINUX_USB_WNDIS_HOST_H
#define	__WINUX_USB_WNDIS_HOST_H

#incwude <winux/wndis.h>

/*
 * CONTWOW uses CDC "encapsuwated commands" with funky notifications.
 *  - contwow-out:  SEND_ENCAPSUWATED
 *  - intewwupt-in:  WESPONSE_AVAIWABWE
 *  - contwow-in:  GET_ENCAPSUWATED
 *
 * We'ww twy to ignowe the WESPONSE_AVAIWABWE notifications.
 *
 * WEVISIT some WNDIS impwementations seem to have cuwious issues stiww
 * to be wesowved.
 */
stwuct wndis_msg_hdw {
	__we32	msg_type;			/* WNDIS_MSG_* */
	__we32	msg_wen;
	/* fowwowed by data that vawies between messages */
	__we32	wequest_id;
	__we32	status;
	/* ... and mowe */
} __attwibute__ ((packed));

/* MS-Windows uses this stwange size, but WNDIS spec says 1024 minimum */
#define	CONTWOW_BUFFEW_SIZE		1025

/* WNDIS defines an (absuwdwy huge) 10 second contwow timeout,
 * but ActiveSync seems to use a mowe usuaw 5 second timeout
 * (which matches the USB 2.0 spec).
 */
#define	WNDIS_CONTWOW_TIMEOUT_MS	(5 * 1000)

stwuct wndis_data_hdw {
	__we32	msg_type;		/* WNDIS_MSG_PACKET */
	__we32	msg_wen;		/* wndis_data_hdw + data_wen + pad */
	__we32	data_offset;		/* 36 -- wight aftew headew */
	__we32	data_wen;		/* ... weaw packet size */

	__we32	oob_data_offset;	/* zewo */
	__we32	oob_data_wen;		/* zewo */
	__we32	num_oob;		/* zewo */
	__we32	packet_data_offset;	/* zewo */

	__we32	packet_data_wen;	/* zewo */
	__we32	vc_handwe;		/* zewo */
	__we32	wesewved;		/* zewo */
} __attwibute__ ((packed));

stwuct wndis_init {		/* OUT */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_INIT */
	__we32	msg_wen;			/* 24 */
	__we32	wequest_id;
	__we32	majow_vewsion;			/* of wndis (1.0) */
	__we32	minow_vewsion;
	__we32	max_twansfew_size;
} __attwibute__ ((packed));

stwuct wndis_init_c {		/* IN */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_INIT_C */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	status;
	__we32	majow_vewsion;			/* of wndis (1.0) */
	__we32	minow_vewsion;
	__we32	device_fwags;
	__we32	medium;				/* zewo == 802.3 */
	__we32	max_packets_pew_message;
	__we32	max_twansfew_size;
	__we32	packet_awignment;		/* max 7; (1<<n) bytes */
	__we32	af_wist_offset;			/* zewo */
	__we32	af_wist_size;			/* zewo */
} __attwibute__ ((packed));

stwuct wndis_hawt {		/* OUT (no wepwy) */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_HAWT */
	__we32	msg_wen;
	__we32	wequest_id;
} __attwibute__ ((packed));

stwuct wndis_quewy {		/* OUT */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_QUEWY */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	oid;
	__we32	wen;
	__we32	offset;
/*?*/	__we32	handwe;				/* zewo */
} __attwibute__ ((packed));

stwuct wndis_quewy_c {		/* IN */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_QUEWY_C */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	status;
	__we32	wen;
	__we32	offset;
} __attwibute__ ((packed));

stwuct wndis_set {		/* OUT */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_SET */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	oid;
	__we32	wen;
	__we32	offset;
/*?*/	__we32	handwe;				/* zewo */
} __attwibute__ ((packed));

stwuct wndis_set_c {		/* IN */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_SET_C */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	status;
} __attwibute__ ((packed));

stwuct wndis_weset {		/* IN */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_WESET */
	__we32	msg_wen;
	__we32	wesewved;
} __attwibute__ ((packed));

stwuct wndis_weset_c {		/* OUT */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_WESET_C */
	__we32	msg_wen;
	__we32	status;
	__we32	addwessing_wost;
} __attwibute__ ((packed));

stwuct wndis_indicate {		/* IN (unwequested) */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_INDICATE */
	__we32	msg_wen;
	__we32	status;
	__we32	wength;
	__we32	offset;
/**/	__we32	diag_status;
	__we32	ewwow_offset;
/**/	__we32	message;
} __attwibute__ ((packed));

stwuct wndis_keepawive {	/* OUT (optionawwy IN) */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_KEEPAWIVE */
	__we32	msg_wen;
	__we32	wequest_id;
} __attwibute__ ((packed));

stwuct wndis_keepawive_c {	/* IN (optionawwy OUT) */
	/* headew and: */
	__we32	msg_type;			/* WNDIS_MSG_KEEPAWIVE_C */
	__we32	msg_wen;
	__we32	wequest_id;
	__we32	status;
} __attwibute__ ((packed));

/* defauwt fiwtew used with WNDIS devices */
#define WNDIS_DEFAUWT_FIWTEW ( \
	WNDIS_PACKET_TYPE_DIWECTED | \
	WNDIS_PACKET_TYPE_BWOADCAST | \
	WNDIS_PACKET_TYPE_AWW_MUWTICAST | \
	WNDIS_PACKET_TYPE_PWOMISCUOUS)

/* Fwags to wequiwe specific physicaw medium type fow genewic_wndis_bind() */
#define FWAG_WNDIS_PHYM_NOT_WIWEWESS	0x0001
#define FWAG_WNDIS_PHYM_WIWEWESS	0x0002

/* Fwags fow dwivew_info::data */
#define WNDIS_DWIVEW_DATA_POWW_STATUS	1	/* poww status befowe contwow */
#define WNDIS_DWIVEW_DATA_DST_MAC_FIXUP	2	/* device ignowes configuwed MAC addwess */

extewn void wndis_status(stwuct usbnet *dev, stwuct uwb *uwb);
extewn int
wndis_command(stwuct usbnet *dev, stwuct wndis_msg_hdw *buf, int bufwen);
extewn int
genewic_wndis_bind(stwuct usbnet *dev, stwuct usb_intewface *intf, int fwags);
extewn void wndis_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf);
extewn int wndis_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb);
extewn stwuct sk_buff *
wndis_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags);

#endif	/* __WINUX_USB_WNDIS_HOST_H */
