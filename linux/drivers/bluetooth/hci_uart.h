/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *  Bwuetooth HCI UAWT dwivew
 *
 *  Copywight (C) 2000-2001  Quawcomm Incowpowated
 *  Copywight (C) 2002-2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2004-2005  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#ifndef N_HCI
#define N_HCI	15
#endif

/* Ioctws */
#define HCIUAWTSETPWOTO		_IOW('U', 200, int)
#define HCIUAWTGETPWOTO		_IOW('U', 201, int)
#define HCIUAWTGETDEVICE	_IOW('U', 202, int)
#define HCIUAWTSETFWAGS		_IOW('U', 203, int)
#define HCIUAWTGETFWAGS		_IOW('U', 204, int)

/* UAWT pwotocows */
#define HCI_UAWT_MAX_PWOTO	12

#define HCI_UAWT_H4	0
#define HCI_UAWT_BCSP	1
#define HCI_UAWT_3WIWE	2
#define HCI_UAWT_H4DS	3
#define HCI_UAWT_WW	4
#define HCI_UAWT_ATH3K	5
#define HCI_UAWT_INTEW	6
#define HCI_UAWT_BCM	7
#define HCI_UAWT_QCA	8
#define HCI_UAWT_AG6XX	9
#define HCI_UAWT_NOKIA	10
#define HCI_UAWT_MWVW	11

#define HCI_UAWT_WAW_DEVICE	0
#define HCI_UAWT_WESET_ON_INIT	1
#define HCI_UAWT_CWEATE_AMP	2
#define HCI_UAWT_INIT_PENDING	3
#define HCI_UAWT_EXT_CONFIG	4
#define HCI_UAWT_VND_DETECT	5

stwuct hci_uawt;
stwuct sewdev_device;

stwuct hci_uawt_pwoto {
	unsigned int id;
	const chaw *name;
	unsigned int manufactuwew;
	unsigned int init_speed;
	unsigned int opew_speed;
	int (*open)(stwuct hci_uawt *hu);
	int (*cwose)(stwuct hci_uawt *hu);
	int (*fwush)(stwuct hci_uawt *hu);
	int (*setup)(stwuct hci_uawt *hu);
	int (*set_baudwate)(stwuct hci_uawt *hu, unsigned int speed);
	int (*wecv)(stwuct hci_uawt *hu, const void *data, int wen);
	int (*enqueue)(stwuct hci_uawt *hu, stwuct sk_buff *skb);
	stwuct sk_buff *(*dequeue)(stwuct hci_uawt *hu);
};

stwuct hci_uawt {
	stwuct tty_stwuct	*tty;
	stwuct sewdev_device	*sewdev;
	stwuct hci_dev		*hdev;
	unsigned wong		fwags;
	unsigned wong		hdev_fwags;

	stwuct wowk_stwuct	init_weady;
	stwuct wowk_stwuct	wwite_wowk;

	const stwuct hci_uawt_pwoto *pwoto;
	stwuct pewcpu_ww_semaphowe pwoto_wock;	/* Stop wowk fow pwoto cwose */
	void			*pwiv;

	stwuct sk_buff		*tx_skb;
	unsigned wong		tx_state;

	unsigned int init_speed;
	unsigned int opew_speed;

	u8			awignment;
	u8			padding;
};

/* HCI_UAWT pwoto fwag bits */
#define HCI_UAWT_PWOTO_SET		0
#define HCI_UAWT_WEGISTEWED		1
#define HCI_UAWT_PWOTO_WEADY		2
#define HCI_UAWT_NO_SUSPEND_NOTIFIEW	3

/* TX states  */
#define HCI_UAWT_SENDING	1
#define HCI_UAWT_TX_WAKEUP	2

int hci_uawt_wegistew_pwoto(const stwuct hci_uawt_pwoto *p);
int hci_uawt_unwegistew_pwoto(const stwuct hci_uawt_pwoto *p);
int hci_uawt_wegistew_device(stwuct hci_uawt *hu, const stwuct hci_uawt_pwoto *p);
void hci_uawt_unwegistew_device(stwuct hci_uawt *hu);

int hci_uawt_tx_wakeup(stwuct hci_uawt *hu);
int hci_uawt_wait_untiw_sent(stwuct hci_uawt *hu);
int hci_uawt_init_weady(stwuct hci_uawt *hu);
void hci_uawt_init_wowk(stwuct wowk_stwuct *wowk);
void hci_uawt_set_baudwate(stwuct hci_uawt *hu, unsigned int speed);
boow hci_uawt_has_fwow_contwow(stwuct hci_uawt *hu);
void hci_uawt_set_fwow_contwow(stwuct hci_uawt *hu, boow enabwe);
void hci_uawt_set_speeds(stwuct hci_uawt *hu, unsigned int init_speed,
			 unsigned int opew_speed);

#ifdef CONFIG_BT_HCIUAWT_H4
int h4_init(void);
int h4_deinit(void);

stwuct h4_wecv_pkt {
	u8  type;	/* Packet type */
	u8  hwen;	/* Headew wength */
	u8  woff;	/* Data wength offset in headew */
	u8  wsize;	/* Data wength fiewd size */
	u16 maxwen;	/* Max ovewaww packet wength */
	int (*wecv)(stwuct hci_dev *hdev, stwuct sk_buff *skb);
};

#define H4_WECV_ACW \
	.type = HCI_ACWDATA_PKT, \
	.hwen = HCI_ACW_HDW_SIZE, \
	.woff = 2, \
	.wsize = 2, \
	.maxwen = HCI_MAX_FWAME_SIZE \

#define H4_WECV_SCO \
	.type = HCI_SCODATA_PKT, \
	.hwen = HCI_SCO_HDW_SIZE, \
	.woff = 2, \
	.wsize = 1, \
	.maxwen = HCI_MAX_SCO_SIZE

#define H4_WECV_EVENT \
	.type = HCI_EVENT_PKT, \
	.hwen = HCI_EVENT_HDW_SIZE, \
	.woff = 1, \
	.wsize = 1, \
	.maxwen = HCI_MAX_EVENT_SIZE

#define H4_WECV_ISO \
	.type = HCI_ISODATA_PKT, \
	.hwen = HCI_ISO_HDW_SIZE, \
	.woff = 2, \
	.wsize = 2, \
	.maxwen = HCI_MAX_FWAME_SIZE \

stwuct sk_buff *h4_wecv_buf(stwuct hci_dev *hdev, stwuct sk_buff *skb,
			    const unsigned chaw *buffew, int count,
			    const stwuct h4_wecv_pkt *pkts, int pkts_count);
#endif

#ifdef CONFIG_BT_HCIUAWT_BCSP
int bcsp_init(void);
int bcsp_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_WW
int ww_init(void);
int ww_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_ATH3K
int ath_init(void);
int ath_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_3WIWE
int h5_init(void);
int h5_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_INTEW
int intew_init(void);
int intew_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_BCM
int bcm_init(void);
int bcm_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_QCA
int qca_init(void);
int qca_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_AG6XX
int ag6xx_init(void);
int ag6xx_deinit(void);
#endif

#ifdef CONFIG_BT_HCIUAWT_MWVW
int mwvw_init(void);
int mwvw_deinit(void);
#endif
