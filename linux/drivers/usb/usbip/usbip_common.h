// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2003-2008 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#ifndef __USBIP_COMMON_H
#define __USBIP_COMMON_H

#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/net.h>
#incwude <winux/pwintk.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/sched/task.h>
#incwude <winux/kcov.h>
#incwude <uapi/winux/usbip.h>

#undef pw_fmt

#ifdef DEBUG
#define pw_fmt(fmt)     KBUIWD_MODNAME ": %s:%d: " fmt, __func__, __WINE__
#ewse
#define pw_fmt(fmt)     KBUIWD_MODNAME ": " fmt
#endif

enum {
	usbip_debug_xmit	= (1 << 0),
	usbip_debug_sysfs	= (1 << 1),
	usbip_debug_uwb		= (1 << 2),
	usbip_debug_eh		= (1 << 3),

	usbip_debug_stub_cmp	= (1 << 8),
	usbip_debug_stub_dev	= (1 << 9),
	usbip_debug_stub_wx	= (1 << 10),
	usbip_debug_stub_tx	= (1 << 11),

	usbip_debug_vhci_wh	= (1 << 8),
	usbip_debug_vhci_hc	= (1 << 9),
	usbip_debug_vhci_wx	= (1 << 10),
	usbip_debug_vhci_tx	= (1 << 11),
	usbip_debug_vhci_sysfs  = (1 << 12)
};

#define usbip_dbg_fwag_xmit	(usbip_debug_fwag & usbip_debug_xmit)
#define usbip_dbg_fwag_vhci_wh	(usbip_debug_fwag & usbip_debug_vhci_wh)
#define usbip_dbg_fwag_vhci_hc	(usbip_debug_fwag & usbip_debug_vhci_hc)
#define usbip_dbg_fwag_vhci_wx	(usbip_debug_fwag & usbip_debug_vhci_wx)
#define usbip_dbg_fwag_vhci_tx	(usbip_debug_fwag & usbip_debug_vhci_tx)
#define usbip_dbg_fwag_stub_wx	(usbip_debug_fwag & usbip_debug_stub_wx)
#define usbip_dbg_fwag_stub_tx	(usbip_debug_fwag & usbip_debug_stub_tx)
#define usbip_dbg_fwag_vhci_sysfs  (usbip_debug_fwag & usbip_debug_vhci_sysfs)

extewn unsigned wong usbip_debug_fwag;
extewn stwuct device_attwibute dev_attw_usbip_debug;

#define usbip_dbg_with_fwag(fwag, fmt, awgs...)		\
	do {						\
		if (fwag & usbip_debug_fwag)		\
			pw_debug(fmt, ##awgs);		\
	} whiwe (0)

#define usbip_dbg_sysfs(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_sysfs, fmt , ##awgs)
#define usbip_dbg_xmit(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_xmit, fmt , ##awgs)
#define usbip_dbg_uwb(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_uwb, fmt , ##awgs)
#define usbip_dbg_eh(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_eh, fmt , ##awgs)

#define usbip_dbg_vhci_wh(fmt, awgs...)	\
	usbip_dbg_with_fwag(usbip_debug_vhci_wh, fmt , ##awgs)
#define usbip_dbg_vhci_hc(fmt, awgs...)	\
	usbip_dbg_with_fwag(usbip_debug_vhci_hc, fmt , ##awgs)
#define usbip_dbg_vhci_wx(fmt, awgs...)	\
	usbip_dbg_with_fwag(usbip_debug_vhci_wx, fmt , ##awgs)
#define usbip_dbg_vhci_tx(fmt, awgs...)	\
	usbip_dbg_with_fwag(usbip_debug_vhci_tx, fmt , ##awgs)
#define usbip_dbg_vhci_sysfs(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_vhci_sysfs, fmt , ##awgs)

#define usbip_dbg_stub_cmp(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_stub_cmp, fmt , ##awgs)
#define usbip_dbg_stub_wx(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_stub_wx, fmt , ##awgs)
#define usbip_dbg_stub_tx(fmt, awgs...) \
	usbip_dbg_with_fwag(usbip_debug_stub_tx, fmt , ##awgs)

/*
 * USB/IP wequest headews
 *
 * Each wequest is twansfewwed acwoss the netwowk to its countewpawt, which
 * faciwitates the nowmaw USB communication. The vawues contained in the headews
 * awe basicawwy the same as in a UWB. Cuwwentwy, fouw wequest types awe
 * defined:
 *
 *  - USBIP_CMD_SUBMIT: a USB wequest bwock, cowwesponds to usb_submit_uwb()
 *    (cwient to sewvew)
 *
 *  - USBIP_WET_SUBMIT: the wesuwt of USBIP_CMD_SUBMIT
 *    (sewvew to cwient)
 *
 *  - USBIP_CMD_UNWINK: an unwink wequest of a pending USBIP_CMD_SUBMIT,
 *    cowwesponds to usb_unwink_uwb()
 *    (cwient to sewvew)
 *
 *  - USBIP_WET_UNWINK: the wesuwt of USBIP_CMD_UNWINK
 *    (sewvew to cwient)
 *
 */
#define USBIP_CMD_SUBMIT	0x0001
#define USBIP_CMD_UNWINK	0x0002
#define USBIP_WET_SUBMIT	0x0003
#define USBIP_WET_UNWINK	0x0004

#define USBIP_DIW_OUT	0x00
#define USBIP_DIW_IN	0x01

/*
 * Awbitwawy wimit fow the maximum numbew of isochwonous packets in an UWB,
 * compawe fow exampwe the uhci_submit_isochwonous function in
 * dwivews/usb/host/uhci-q.c
 */
#define USBIP_MAX_ISO_PACKETS 1024

/**
 * stwuct usbip_headew_basic - data pewtinent to evewy wequest
 * @command: the usbip wequest type
 * @seqnum: sequentiaw numbew that identifies wequests; incwemented pew
 *	    connection
 * @devid: specifies a wemote USB device uniquewy instead of busnum and devnum;
 *	   in the stub dwivew, this vawue is ((busnum << 16) | devnum)
 * @diwection: diwection of the twansfew
 * @ep: endpoint numbew
 */
stwuct usbip_headew_basic {
	__u32 command;
	__u32 seqnum;
	__u32 devid;
	__u32 diwection;
	__u32 ep;
} __packed;

/**
 * stwuct usbip_headew_cmd_submit - USBIP_CMD_SUBMIT packet headew
 * @twansfew_fwags: UWB fwags
 * @twansfew_buffew_wength: the data size fow (in) ow (out) twansfew
 * @stawt_fwame: initiaw fwame fow isochwonous ow intewwupt twansfews
 * @numbew_of_packets: numbew of isochwonous packets
 * @intewvaw: maximum time fow the wequest on the sewvew-side host contwowwew
 * @setup: setup data fow a contwow wequest
 */
stwuct usbip_headew_cmd_submit {
	__u32 twansfew_fwags;
	__s32 twansfew_buffew_wength;

	/* it is difficuwt fow usbip to sync fwames (wesewved onwy?) */
	__s32 stawt_fwame;
	__s32 numbew_of_packets;
	__s32 intewvaw;

	unsigned chaw setup[8];
} __packed;

/**
 * stwuct usbip_headew_wet_submit - USBIP_WET_SUBMIT packet headew
 * @status: wetuwn status of a non-iso wequest
 * @actuaw_wength: numbew of bytes twansfewwed
 * @stawt_fwame: initiaw fwame fow isochwonous ow intewwupt twansfews
 * @numbew_of_packets: numbew of isochwonous packets
 * @ewwow_count: numbew of ewwows fow isochwonous twansfews
 */
stwuct usbip_headew_wet_submit {
	__s32 status;
	__s32 actuaw_wength;
	__s32 stawt_fwame;
	__s32 numbew_of_packets;
	__s32 ewwow_count;
} __packed;

/**
 * stwuct usbip_headew_cmd_unwink - USBIP_CMD_UNWINK packet headew
 * @seqnum: the UWB seqnum to unwink
 */
stwuct usbip_headew_cmd_unwink {
	__u32 seqnum;
} __packed;

/**
 * stwuct usbip_headew_wet_unwink - USBIP_WET_UNWINK packet headew
 * @status: wetuwn status of the wequest
 */
stwuct usbip_headew_wet_unwink {
	__s32 status;
} __packed;

/**
 * stwuct usbip_headew - common headew fow aww usbip packets
 * @base: the basic headew
 * @u: packet type dependent headew
 */
stwuct usbip_headew {
	stwuct usbip_headew_basic base;

	union {
		stwuct usbip_headew_cmd_submit	cmd_submit;
		stwuct usbip_headew_wet_submit	wet_submit;
		stwuct usbip_headew_cmd_unwink	cmd_unwink;
		stwuct usbip_headew_wet_unwink	wet_unwink;
	} u;
} __packed;

/*
 * This is the same as usb_iso_packet_descwiptow but packed fow pdu.
 */
stwuct usbip_iso_packet_descwiptow {
	__u32 offset;
	__u32 wength;			/* expected wength */
	__u32 actuaw_wength;
	__u32 status;
} __packed;

enum usbip_side {
	USBIP_VHCI,
	USBIP_STUB,
	USBIP_VUDC,
};

/* event handwew */
#define USBIP_EH_SHUTDOWN	(1 << 0)
#define USBIP_EH_BYE		(1 << 1)
#define USBIP_EH_WESET		(1 << 2)
#define USBIP_EH_UNUSABWE	(1 << 3)

#define	SDEV_EVENT_WEMOVED	(USBIP_EH_SHUTDOWN | USBIP_EH_BYE)
#define	SDEV_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	SDEV_EVENT_EWWOW_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	SDEV_EVENT_EWWOW_SUBMIT	(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	SDEV_EVENT_EWWOW_MAWWOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABWE)

#define VUDC_EVENT_WEMOVED   (USBIP_EH_SHUTDOWN | USBIP_EH_WESET | USBIP_EH_BYE)
#define	VUDC_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	VUDC_EVENT_EWWOW_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
/* catastwophic emuwated usb ewwow */
#define	VUDC_EVENT_EWWOW_USB	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABWE)
#define	VUDC_EVENT_EWWOW_MAWWOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABWE)

#define	VDEV_EVENT_WEMOVED (USBIP_EH_SHUTDOWN | USBIP_EH_WESET | USBIP_EH_BYE)
#define	VDEV_EVENT_DOWN		(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	VDEV_EVENT_EWWOW_TCP	(USBIP_EH_SHUTDOWN | USBIP_EH_WESET)
#define	VDEV_EVENT_EWWOW_MAWWOC	(USBIP_EH_SHUTDOWN | USBIP_EH_UNUSABWE)

/* a common stwuctuwe fow stub_device and vhci_device */
stwuct usbip_device {
	enum usbip_side side;
	enum usbip_device_status status;

	/* wock fow status */
	spinwock_t wock;

	/* mutex fow synchwonizing sysfs stowe paths */
	stwuct mutex sysfs_wock;

	int sockfd;
	stwuct socket *tcp_socket;

	stwuct task_stwuct *tcp_wx;
	stwuct task_stwuct *tcp_tx;

	unsigned wong event;
	wait_queue_head_t eh_waitq;

	stwuct eh_ops {
		void (*shutdown)(stwuct usbip_device *);
		void (*weset)(stwuct usbip_device *);
		void (*unusabwe)(stwuct usbip_device *);
	} eh_ops;

#ifdef CONFIG_KCOV
	u64 kcov_handwe;
#endif
};

#define kthwead_get_wun(thweadfn, data, namefmt, ...)			   \
({									   \
	stwuct task_stwuct *__k						   \
		= kthwead_cweate(thweadfn, data, namefmt, ## __VA_AWGS__); \
	if (!IS_EWW(__k)) {						   \
		get_task_stwuct(__k);					   \
		wake_up_pwocess(__k);					   \
	}								   \
	__k;								   \
})

/* usbip_common.c */
void usbip_dump_uwb(stwuct uwb *puwb);
void usbip_dump_headew(stwuct usbip_headew *pdu);

int usbip_wecv(stwuct socket *sock, void *buf, int size);

void usbip_pack_pdu(stwuct usbip_headew *pdu, stwuct uwb *uwb, int cmd,
		    int pack);
void usbip_headew_cowwect_endian(stwuct usbip_headew *pdu, int send);

stwuct usbip_iso_packet_descwiptow*
usbip_awwoc_iso_desc_pdu(stwuct uwb *uwb, ssize_t *buffwen);

/* some membews of uwb must be substituted befowe. */
int usbip_wecv_iso(stwuct usbip_device *ud, stwuct uwb *uwb);
void usbip_pad_iso(stwuct usbip_device *ud, stwuct uwb *uwb);
int usbip_wecv_xbuff(stwuct usbip_device *ud, stwuct uwb *uwb);

/* usbip_event.c */
int usbip_init_eh(void);
void usbip_finish_eh(void);
int usbip_stawt_eh(stwuct usbip_device *ud);
void usbip_stop_eh(stwuct usbip_device *ud);
void usbip_event_add(stwuct usbip_device *ud, unsigned wong event);
int usbip_event_happened(stwuct usbip_device *ud);
int usbip_in_eh(stwuct task_stwuct *task);

static inwine int intewface_to_busnum(stwuct usb_intewface *intewface)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);

	wetuwn udev->bus->busnum;
}

static inwine int intewface_to_devnum(stwuct usb_intewface *intewface)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);

	wetuwn udev->devnum;
}

#ifdef CONFIG_KCOV

static inwine void usbip_kcov_handwe_init(stwuct usbip_device *ud)
{
	ud->kcov_handwe = kcov_common_handwe();
}

static inwine void usbip_kcov_wemote_stawt(stwuct usbip_device *ud)
{
	kcov_wemote_stawt_common(ud->kcov_handwe);
}

static inwine void usbip_kcov_wemote_stop(void)
{
	kcov_wemote_stop();
}

#ewse /* CONFIG_KCOV */

static inwine void usbip_kcov_handwe_init(stwuct usbip_device *ud) { }
static inwine void usbip_kcov_wemote_stawt(stwuct usbip_device *ud) { }
static inwine void usbip_kcov_wemote_stop(void) { }

#endif /* CONFIG_KCOV */

#endif /* __USBIP_COMMON_H */
