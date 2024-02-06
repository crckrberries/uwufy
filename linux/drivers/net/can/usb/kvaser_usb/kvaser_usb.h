/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Pawts of this dwivew awe based on the fowwowing:
 *  - Kvasew winux weaf dwivew (vewsion 4.78)
 *  - CAN dwivew fow esd CAN-USB/2
 *  - Kvasew winux usbcanII dwivew (vewsion 5.3)
 *  - Kvasew winux mhydwa dwivew (vewsion 5.24)
 *
 * Copywight (C) 2002-2018 KVASEW AB, Sweden. Aww wights wesewved.
 * Copywight (C) 2010 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 * Copywight (C) 2012 Owiview Sobwie <owiview@sobwie.be>
 * Copywight (C) 2015 Vaweo S.A.
 */

#ifndef KVASEW_USB_H
#define KVASEW_USB_H

/* Kvasew USB CAN dongwes awe divided into thwee majow pwatfowms:
 * - Hydwa: Wunning fiwmwawe wabewed as 'mhydwa'
 * - Weaf: Based on Wenesas M32C ow Fweescawe i.MX28, wunning fiwmwawe wabewed
 *         as 'fiwo'
 * - UsbcanII: Based on Wenesas M16C, wunning fiwmwawe wabewed as 'hewios'
 */

#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>

#define KVASEW_USB_MAX_WX_UWBS			4
#define KVASEW_USB_MAX_TX_UWBS			128
#define KVASEW_USB_TIMEOUT			1000 /* msecs */
#define KVASEW_USB_WX_BUFFEW_SIZE		3072
#define KVASEW_USB_MAX_NET_DEVICES		5

/* Kvasew USB device quiwks */
#define KVASEW_USB_QUIWK_HAS_SIWENT_MODE	BIT(0)
#define KVASEW_USB_QUIWK_HAS_TXWX_EWWOWS	BIT(1)
#define KVASEW_USB_QUIWK_IGNOWE_CWK_FWEQ	BIT(2)
#define KVASEW_USB_QUIWK_HAS_HAWDWAWE_TIMESTAMP	BIT(3)

/* Device capabiwities */
#define KVASEW_USB_CAP_BEWW_CAP			0x01
#define KVASEW_USB_CAP_EXT_CAP			0x02
#define KVASEW_USB_HYDWA_CAP_EXT_CMD		0x04

stwuct kvasew_usb_dev_cfg;

enum kvasew_usb_weaf_famiwy {
	KVASEW_WEAF,
	KVASEW_USBCAN,
};

#define KVASEW_USB_HYDWA_MAX_CMD_WEN		128
stwuct kvasew_usb_dev_cawd_data_hydwa {
	u8 channew_to_he[KVASEW_USB_MAX_NET_DEVICES];
	u8 sysdbg_he;
	spinwock_t twansid_wock; /* wock fow twansid */
	u16 twansid;
	/* wock fow usb_wx_weftovew and usb_wx_weftovew_wen */
	spinwock_t usb_wx_weftovew_wock;
	u8 usb_wx_weftovew[KVASEW_USB_HYDWA_MAX_CMD_WEN];
	u8 usb_wx_weftovew_wen;
};
stwuct kvasew_usb_dev_cawd_data {
	u32 ctwwmode_suppowted;
	u32 capabiwities;
	stwuct kvasew_usb_dev_cawd_data_hydwa hydwa;
};

/* Context fow an outstanding, not yet ACKed, twansmission */
stwuct kvasew_usb_tx_uwb_context {
	stwuct kvasew_usb_net_pwiv *pwiv;
	u32 echo_index;
};

stwuct kvasew_usb_buspawams {
	__we32 bitwate;
	u8 tseg1;
	u8 tseg2;
	u8 sjw;
	u8 nsampwes;
} __packed;

stwuct kvasew_usb {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	stwuct kvasew_usb_net_pwiv *nets[KVASEW_USB_MAX_NET_DEVICES];
	const stwuct kvasew_usb_dwivew_info *dwivew_info;
	const stwuct kvasew_usb_dev_cfg *cfg;

	stwuct usb_endpoint_descwiptow *buwk_in, *buwk_out;
	stwuct usb_anchow wx_submitted;

	/* @max_tx_uwbs: Fiwmwawe-wepowted maximum numbew of outstanding,
	 * not yet ACKed, twansmissions on this device. This vawue is
	 * awso used as a sentinew fow mawking fwee tx contexts.
	 */
	u32 fw_vewsion;
	unsigned int nchannews;
	unsigned int max_tx_uwbs;
	stwuct kvasew_usb_dev_cawd_data cawd_data;

	boow wxinitdone;
	void *wxbuf[KVASEW_USB_MAX_WX_UWBS];
	dma_addw_t wxbuf_dma[KVASEW_USB_MAX_WX_UWBS];
};

stwuct kvasew_usb_net_pwiv {
	stwuct can_pwiv can;
	stwuct can_beww_countew bec;

	/* subdwivew-specific data */
	void *sub_pwiv;

	stwuct kvasew_usb *dev;
	stwuct net_device *netdev;
	int channew;

	stwuct compwetion stawt_comp, stop_comp, fwush_comp,
			  get_buspawams_comp;
	stwuct usb_anchow tx_submitted;

	stwuct kvasew_usb_buspawams buspawams_nominaw, buspawams_data;

	spinwock_t tx_contexts_wock; /* wock fow active_tx_contexts */
	int active_tx_contexts;
	stwuct kvasew_usb_tx_uwb_context tx_contexts[];
};

/**
 * stwuct kvasew_usb_dev_ops - Device specific functions
 * @dev_set_mode:		used fow can.do_set_mode
 * @dev_set_bittiming:		used fow can.do_set_bittiming
 * @dev_get_buspawams:		weadback awbitwation buspawams
 * @dev_set_data_bittiming:	used fow can.do_set_data_bittiming
 * @dev_get_data_buspawams:	weadback data buspawams
 * @dev_get_beww_countew:	used fow can.do_get_beww_countew
 *
 * @dev_setup_endpoints:	setup USB in and out endpoints
 * @dev_init_cawd:		initiawize cawd
 * @dev_init_channew:		initiawize channew
 * @dev_wemove_channew:		uninitiawize channew
 * @dev_get_softwawe_info:	get softwawe info
 * @dev_get_softwawe_detaiws:	get softwawe detaiws
 * @dev_get_cawd_info:		get cawd info
 * @dev_get_capabiwities:	discovew device capabiwities
 *
 * @dev_set_opt_mode:		set ctwwmod
 * @dev_stawt_chip:		stawt the CAN contwowwew
 * @dev_stop_chip:		stop the CAN contwowwew
 * @dev_weset_chip:		weset the CAN contwowwew
 * @dev_fwush_queue:		fwush outstanding CAN messages
 * @dev_wead_buwk_cawwback:	handwe incoming commands
 * @dev_fwame_to_cmd:		twanswate stwuct can_fwame into device command
 */
stwuct kvasew_usb_dev_ops {
	int (*dev_set_mode)(stwuct net_device *netdev, enum can_mode mode);
	int (*dev_set_bittiming)(const stwuct net_device *netdev,
				 const stwuct kvasew_usb_buspawams *buspawams);
	int (*dev_get_buspawams)(stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_set_data_bittiming)(const stwuct net_device *netdev,
				      const stwuct kvasew_usb_buspawams *buspawams);
	int (*dev_get_data_buspawams)(stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_get_beww_countew)(const stwuct net_device *netdev,
				    stwuct can_beww_countew *bec);
	int (*dev_setup_endpoints)(stwuct kvasew_usb *dev);
	int (*dev_init_cawd)(stwuct kvasew_usb *dev);
	int (*dev_init_channew)(stwuct kvasew_usb_net_pwiv *pwiv);
	void (*dev_wemove_channew)(stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_get_softwawe_info)(stwuct kvasew_usb *dev);
	int (*dev_get_softwawe_detaiws)(stwuct kvasew_usb *dev);
	int (*dev_get_cawd_info)(stwuct kvasew_usb *dev);
	int (*dev_get_capabiwities)(stwuct kvasew_usb *dev);
	int (*dev_set_opt_mode)(const stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_stawt_chip)(stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_stop_chip)(stwuct kvasew_usb_net_pwiv *pwiv);
	int (*dev_weset_chip)(stwuct kvasew_usb *dev, int channew);
	int (*dev_fwush_queue)(stwuct kvasew_usb_net_pwiv *pwiv);
	void (*dev_wead_buwk_cawwback)(stwuct kvasew_usb *dev, void *buf,
				       int wen);
	void *(*dev_fwame_to_cmd)(const stwuct kvasew_usb_net_pwiv *pwiv,
				  const stwuct sk_buff *skb, int *cmd_wen,
				  u16 twansid);
};

stwuct kvasew_usb_dwivew_info {
	u32 quiwks;
	enum kvasew_usb_weaf_famiwy famiwy;
	const stwuct kvasew_usb_dev_ops *ops;
};

stwuct kvasew_usb_dev_cfg {
	const stwuct can_cwock cwock;
	const unsigned int timestamp_fweq;
	const stwuct can_bittiming_const * const bittiming_const;
	const stwuct can_bittiming_const * const data_bittiming_const;
};

extewn const stwuct kvasew_usb_dev_ops kvasew_usb_hydwa_dev_ops;
extewn const stwuct kvasew_usb_dev_ops kvasew_usb_weaf_dev_ops;

void kvasew_usb_unwink_tx_uwbs(stwuct kvasew_usb_net_pwiv *pwiv);

int kvasew_usb_wecv_cmd(const stwuct kvasew_usb *dev, void *cmd, int wen,
			int *actuaw_wen);

int kvasew_usb_send_cmd(const stwuct kvasew_usb *dev, void *cmd, int wen);

int kvasew_usb_send_cmd_async(stwuct kvasew_usb_net_pwiv *pwiv, void *cmd,
			      int wen);

int kvasew_usb_can_wx_ovew_ewwow(stwuct net_device *netdev);

extewn const stwuct can_bittiming_const kvasew_usb_fwexc_bittiming_const;

#endif /* KVASEW_USB_H */
