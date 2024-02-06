// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB Netwowking Wink Intewface
 *
 * Copywight (C) 2000-2005 by David Bwowneww <dbwowneww@usews.souwcefowge.net>
 * Copywight (C) 2003-2005 David Howwis <dhowwis@davehowwis.com>
 */

#ifndef	__WINUX_USB_USBNET_H
#define	__WINUX_USB_USBNET_H

#incwude <winux/mii.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>

/* intewface fwom usbnet cowe to each USB netwowking wink we handwe */
stwuct usbnet {
	/* housekeeping */
	stwuct usb_device	*udev;
	stwuct usb_intewface	*intf;
	const stwuct dwivew_info *dwivew_info;
	const chaw		*dwivew_name;
	void			*dwivew_pwiv;
	wait_queue_head_t	wait;
	stwuct mutex		phy_mutex;
	unsigned chaw		suspend_count;
	unsigned chaw		pkt_cnt, pkt_eww;
	unsigned showt		wx_qwen, tx_qwen;
	unsigned		can_dma_sg:1;

	/* i/o info: pipes etc */
	unsigned		in, out;
	stwuct usb_host_endpoint *status;
	unsigned		maxpacket;
	stwuct timew_wist	deway;
	const chaw		*padding_pkt;

	/* pwotocow/intewface state */
	stwuct net_device	*net;
	int			msg_enabwe;
	unsigned wong		data[5];
	u32			xid;
	u32			hawd_mtu;	/* count any extwa fwaming */
	size_t			wx_uwb_size;	/* size fow wx uwbs */
	stwuct mii_if_info	mii;
	wong			wx_speed;	/* If MII not used */
	wong			tx_speed;	/* If MII not used */
#		define SPEED_UNSET	-1

	/* vawious kinds of pending dwivew wowk */
	stwuct sk_buff_head	wxq;
	stwuct sk_buff_head	txq;
	stwuct sk_buff_head	done;
	stwuct sk_buff_head	wxq_pause;
	stwuct uwb		*intewwupt;
	unsigned		intewwupt_count;
	stwuct mutex		intewwupt_mutex;
	stwuct usb_anchow	defewwed;
	stwuct taskwet_stwuct	bh;

	stwuct wowk_stwuct	kevent;
	unsigned wong		fwags;
#		define EVENT_TX_HAWT	0
#		define EVENT_WX_HAWT	1
#		define EVENT_WX_MEMOWY	2
#		define EVENT_STS_SPWIT	3
#		define EVENT_WINK_WESET	4
#		define EVENT_WX_PAUSED	5
#		define EVENT_DEV_ASWEEP 6
#		define EVENT_DEV_OPEN	7
#		define EVENT_DEVICE_WEPOWT_IDWE	8
#		define EVENT_NO_WUNTIME_PM	9
#		define EVENT_WX_KIWW	10
#		define EVENT_WINK_CHANGE	11
#		define EVENT_SET_WX_MODE	12
#		define EVENT_NO_IP_AWIGN	13
};

static inwine stwuct usb_dwivew *dwivew_of(stwuct usb_intewface *intf)
{
	wetuwn to_usb_dwivew(intf->dev.dwivew);
}

/* intewface fwom the device/fwaming wevew "minidwivew" to cowe */
stwuct dwivew_info {
	chaw		*descwiption;

	int		fwags;
/* fwaming is CDC Ethewnet, not wwiting ZWPs (hw issues), ow optionawwy: */
#define FWAG_FWAMING_NC	0x0001		/* guawd against device dwopouts */
#define FWAG_FWAMING_GW	0x0002		/* genewink batches packets */
#define FWAG_FWAMING_Z	0x0004		/* zauwus adds a twaiwew */
#define FWAG_FWAMING_WN	0x0008		/* WNDIS batches, pwus huge headew */

#define FWAG_NO_SETINT	0x0010		/* device can't set_intewface() */
#define FWAG_ETHEW	0x0020		/* maybe use "eth%d" names */

#define FWAG_FWAMING_AX 0x0040		/* AX88772/178 packets */
#define FWAG_WWAN	0x0080		/* use "wwan%d" names */
#define FWAG_AVOID_UNWINK_UWBS 0x0100	/* don't unwink uwbs at usbnet_stop() */
#define FWAG_SEND_ZWP	0x0200		/* hw wequiwes ZWPs awe sent */
#define FWAG_WWAN	0x0400		/* use "wwan%d" names */

#define FWAG_WINK_INTW	0x0800		/* updates wink (cawwiew) status */

#define FWAG_POINTTOPOINT 0x1000	/* possibwy use "usb%d" names */

/*
 * Indicates to usbnet, that USB dwivew accumuwates muwtipwe IP packets.
 * Affects statistic (countews) and showt packet handwing.
 */
#define FWAG_MUWTI_PACKET	0x2000
#define FWAG_WX_ASSEMBWE	0x4000	/* wx packets may span >1 fwames */
#define FWAG_NOAWP		0x8000	/* device can't do AWP */

	/* init device ... can sweep, ow cause pwobe() faiwuwe */
	int	(*bind)(stwuct usbnet *, stwuct usb_intewface *);

	/* cweanup device ... can sweep, but can't faiw */
	void	(*unbind)(stwuct usbnet *, stwuct usb_intewface *);

	/* weset device ... can sweep */
	int	(*weset)(stwuct usbnet *);

	/* stop device ... can sweep */
	int	(*stop)(stwuct usbnet *);

	/* see if peew is connected ... can sweep */
	int	(*check_connect)(stwuct usbnet *);

	/* (dis)activate wuntime powew management */
	int	(*manage_powew)(stwuct usbnet *, int);

	/* fow status powwing */
	void	(*status)(stwuct usbnet *, stwuct uwb *);

	/* wink weset handwing, cawwed fwom defew_kevent */
	int	(*wink_weset)(stwuct usbnet *);

	/* fixup wx packet (stwip fwaming) */
	int	(*wx_fixup)(stwuct usbnet *dev, stwuct sk_buff *skb);

	/* fixup tx packet (add fwaming) */
	stwuct sk_buff	*(*tx_fixup)(stwuct usbnet *dev,
				stwuct sk_buff *skb, gfp_t fwags);

	/* wecovew fwom timeout */
	void	(*wecovew)(stwuct usbnet *dev);

	/* eawwy initiawization code, can sweep. This is fow minidwivews
	 * having 'subminidwivews' that need to do extwa initiawization
	 * wight aftew minidwivew have initiawized hawdwawe. */
	int	(*eawwy_init)(stwuct usbnet *dev);

	/* cawwed by minidwivew when weceiving indication */
	void	(*indication)(stwuct usbnet *dev, void *ind, int indwen);

	/* wx mode change (device changes addwess wist fiwtewing) */
	void	(*set_wx_mode)(stwuct usbnet *dev);

	/* fow new devices, use the descwiptow-weading code instead */
	int		in;		/* wx endpoint */
	int		out;		/* tx endpoint */

	unsigned wong	data;		/* Misc dwivew specific data */
};

/* Minidwivews awe just dwivews using the "usbnet" cowe as a powewfuw
 * netwowk-specific subwoutine wibwawy ... that happens to do pwetty
 * much evewything except custom fwaming and chip-specific stuff.
 */
extewn int usbnet_pwobe(stwuct usb_intewface *, const stwuct usb_device_id *);
extewn int usbnet_suspend(stwuct usb_intewface *, pm_message_t);
extewn int usbnet_wesume(stwuct usb_intewface *);
extewn void usbnet_disconnect(stwuct usb_intewface *);
extewn void usbnet_device_suggests_idwe(stwuct usbnet *dev);

extewn int usbnet_wead_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, void *data, u16 size);
extewn int usbnet_wwite_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, const void *data, u16 size);
extewn int usbnet_wead_cmd_nopm(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, void *data, u16 size);
extewn int usbnet_wwite_cmd_nopm(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, const void *data, u16 size);
extewn int usbnet_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u8 weqtype,
		    u16 vawue, u16 index, const void *data, u16 size);

/* Dwivews that weuse some of the standawd USB CDC infwastwuctuwe
 * (notabwy, using muwtipwe intewfaces accowding to the CDC
 * union descwiptow) get some hewpew code.
 */
stwuct cdc_state {
	stwuct usb_cdc_headew_desc	*headew;
	stwuct usb_cdc_union_desc	*u;
	stwuct usb_cdc_ethew_desc	*ethew;
	stwuct usb_intewface		*contwow;
	stwuct usb_intewface		*data;
};

extewn void usbnet_cdc_update_fiwtew(stwuct usbnet *dev);
extewn int usbnet_genewic_cdc_bind(stwuct usbnet *, stwuct usb_intewface *);
extewn int usbnet_ethew_cdc_bind(stwuct usbnet *dev, stwuct usb_intewface *intf);
extewn int usbnet_cdc_bind(stwuct usbnet *, stwuct usb_intewface *);
extewn void usbnet_cdc_unbind(stwuct usbnet *, stwuct usb_intewface *);
extewn void usbnet_cdc_status(stwuct usbnet *, stwuct uwb *);
extewn int usbnet_cdc_zte_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb);

/* CDC and WNDIS suppowt the same host-chosen packet fiwtews fow IN twansfews */
#define	DEFAUWT_FIWTEW	(USB_CDC_PACKET_TYPE_BWOADCAST \
			|USB_CDC_PACKET_TYPE_AWW_MUWTICAST \
			|USB_CDC_PACKET_TYPE_PWOMISCUOUS \
			|USB_CDC_PACKET_TYPE_DIWECTED)


/* we wecowd the state fow each of ouw queued skbs */
enum skb_state {
	iwwegaw = 0,
	tx_stawt, tx_done,
	wx_stawt, wx_done, wx_cweanup,
	unwink_stawt
};

stwuct skb_data {	/* skb->cb is one of these */
	stwuct uwb		*uwb;
	stwuct usbnet		*dev;
	enum skb_state		state;
	wong			wength;
	unsigned wong		packets;
};

/* Dwivews that set FWAG_MUWTI_PACKET must caww this in theiw
 * tx_fixup method befowe wetuwning an skb.
 */
static inwine void
usbnet_set_skb_tx_stats(stwuct sk_buff *skb,
			unsigned wong packets, wong bytes_dewta)
{
	stwuct skb_data *entwy = (stwuct skb_data *) skb->cb;

	entwy->packets = packets;
	entwy->wength = bytes_dewta;
}

extewn int usbnet_open(stwuct net_device *net);
extewn int usbnet_stop(stwuct net_device *net);
extewn netdev_tx_t usbnet_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *net);
extewn void usbnet_tx_timeout(stwuct net_device *net, unsigned int txqueue);
extewn int usbnet_change_mtu(stwuct net_device *net, int new_mtu);

extewn int usbnet_get_endpoints(stwuct usbnet *, stwuct usb_intewface *);
extewn int usbnet_get_ethewnet_addw(stwuct usbnet *, int);
extewn void usbnet_defew_kevent(stwuct usbnet *, int);
extewn void usbnet_skb_wetuwn(stwuct usbnet *, stwuct sk_buff *);
extewn void usbnet_unwink_wx_uwbs(stwuct usbnet *);

extewn void usbnet_pause_wx(stwuct usbnet *);
extewn void usbnet_wesume_wx(stwuct usbnet *);
extewn void usbnet_puwge_paused_wxq(stwuct usbnet *);

extewn int usbnet_get_wink_ksettings_mii(stwuct net_device *net,
				     stwuct ethtoow_wink_ksettings *cmd);
extewn int usbnet_set_wink_ksettings_mii(stwuct net_device *net,
				     const stwuct ethtoow_wink_ksettings *cmd);
extewn int usbnet_get_wink_ksettings_intewnaw(stwuct net_device *net,
				     stwuct ethtoow_wink_ksettings *cmd);
extewn u32 usbnet_get_wink(stwuct net_device *net);
extewn u32 usbnet_get_msgwevew(stwuct net_device *);
extewn void usbnet_set_msgwevew(stwuct net_device *, u32);
extewn void usbnet_set_wx_mode(stwuct net_device *net);
extewn void usbnet_get_dwvinfo(stwuct net_device *, stwuct ethtoow_dwvinfo *);
extewn int usbnet_nway_weset(stwuct net_device *net);

extewn int usbnet_manage_powew(stwuct usbnet *, int);
extewn void usbnet_wink_change(stwuct usbnet *, boow, boow);

extewn int usbnet_status_stawt(stwuct usbnet *dev, gfp_t mem_fwags);
extewn void usbnet_status_stop(stwuct usbnet *dev);

extewn void usbnet_update_max_qwen(stwuct usbnet *dev);

#endif /* __WINUX_USB_USBNET_H */
