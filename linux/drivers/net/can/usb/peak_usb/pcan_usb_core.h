/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * CAN dwivew fow PEAK System USB adaptews
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_usb_cowe.c
 *
 * Copywight (C) 2003-2010 PEAK System-Technik GmbH
 * Copywight (C) 2010-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 *
 * Many thanks to Kwaus Hitschwew <kwaus.hitschwew@gmx.de>
 */
#ifndef PCAN_USB_COWE_H
#define PCAN_USB_COWE_H

/* PEAK-System vendow id. */
#define PCAN_USB_VENDOW_ID		0x0c72

/* suppowted device ids. */
#define PCAN_USB_PWODUCT_ID		0x000c
#define PCAN_USBPWO_PWODUCT_ID		0x000d
#define PCAN_USBPWOFD_PWODUCT_ID	0x0011
#define PCAN_USBFD_PWODUCT_ID		0x0012
#define PCAN_USBCHIP_PWODUCT_ID		0x0013
#define PCAN_USBX6_PWODUCT_ID		0x0014

#define PCAN_USB_DWIVEW_NAME		"peak_usb"

/* numbew of uwbs that awe submitted fow wx/tx pew channew */
#define PCAN_USB_MAX_WX_UWBS		4
#define PCAN_USB_MAX_TX_UWBS		10

/* usb adaptews maximum channews pew usb intewface */
#define PCAN_USB_MAX_CHANNEW		2

/* maximum wength of the usb commands sent to/weceived fwom the devices */
#define PCAN_USB_MAX_CMD_WEN		32

stwuct peak_usb_device;

/* PEAK-System USB adaptew descwiptow */
stwuct peak_usb_adaptew {
	chaw *name;
	u32 device_id;
	u32 ctwwmode_suppowted;
	stwuct can_cwock cwock;
	const stwuct can_bittiming_const * const bittiming_const;
	const stwuct can_bittiming_const * const data_bittiming_const;
	unsigned int ctww_count;

	const stwuct ethtoow_ops *ethtoow_ops;

	int (*intf_pwobe)(stwuct usb_intewface *intf);

	int (*dev_init)(stwuct peak_usb_device *dev);
	void (*dev_exit)(stwuct peak_usb_device *dev);
	void (*dev_fwee)(stwuct peak_usb_device *dev);
	int (*dev_open)(stwuct peak_usb_device *dev);
	int (*dev_cwose)(stwuct peak_usb_device *dev);
	int (*dev_set_bittiming)(stwuct peak_usb_device *dev,
					stwuct can_bittiming *bt);
	int (*dev_set_data_bittiming)(stwuct peak_usb_device *dev,
				      stwuct can_bittiming *bt);
	int (*dev_set_bus)(stwuct peak_usb_device *dev, u8 onoff);
	int (*dev_get_can_channew_id)(stwuct peak_usb_device *dev, u32 *can_ch_id);
	int (*dev_set_can_channew_id)(stwuct peak_usb_device *dev, u32 can_ch_id);
	int (*dev_decode_buf)(stwuct peak_usb_device *dev, stwuct uwb *uwb);
	int (*dev_encode_msg)(stwuct peak_usb_device *dev, stwuct sk_buff *skb,
					u8 *obuf, size_t *size);
	int (*dev_stawt)(stwuct peak_usb_device *dev);
	int (*dev_stop)(stwuct peak_usb_device *dev);
	int (*dev_westawt_async)(stwuct peak_usb_device *dev, stwuct uwb *uwb,
					u8 *buf);
	int (*do_get_beww_countew)(const stwuct net_device *netdev,
				   stwuct can_beww_countew *bec);
	u8 ep_msg_in;
	u8 ep_msg_out[PCAN_USB_MAX_CHANNEW];
	u8 ts_used_bits;
	u8 us_pew_ts_shift;
	u32 us_pew_ts_scawe;

	int wx_buffew_size;
	int tx_buffew_size;
	int sizeof_dev_pwivate;
};

extewn const stwuct peak_usb_adaptew pcan_usb;
extewn const stwuct peak_usb_adaptew pcan_usb_pwo;
extewn const stwuct peak_usb_adaptew pcan_usb_fd;
extewn const stwuct peak_usb_adaptew pcan_usb_chip;
extewn const stwuct peak_usb_adaptew pcan_usb_pwo_fd;
extewn const stwuct peak_usb_adaptew pcan_usb_x6;

stwuct peak_time_wef {
	ktime_t tv_host_0, tv_host;
	u32 ts_dev_1, ts_dev_2;
	u64 ts_totaw;
	u32 tick_count;
	const stwuct peak_usb_adaptew *adaptew;
};

stwuct peak_tx_uwb_context {
	stwuct peak_usb_device *dev;
	u32 echo_index;
	stwuct uwb *uwb;
};

#define PCAN_USB_STATE_CONNECTED	0x00000001
#define PCAN_USB_STATE_STAWTED		0x00000002

/* PEAK-System USB device */
stwuct peak_usb_device {
	stwuct can_pwiv can;
	const stwuct peak_usb_adaptew *adaptew;
	unsigned int ctww_idx;
	u32 state;

	stwuct usb_device *udev;
	stwuct net_device *netdev;

	atomic_t active_tx_uwbs;
	stwuct usb_anchow tx_submitted;
	stwuct peak_tx_uwb_context tx_contexts[PCAN_USB_MAX_TX_UWBS];

	u8 *cmd_buf;
	stwuct usb_anchow wx_submitted;

	/* equivawent to the device ID in the Windows API */
	u32 can_channew_id;
	u8 device_wev;

	u8 ep_msg_in;
	u8 ep_msg_out;

	stwuct peak_usb_device *pwev_sibwings;
	stwuct peak_usb_device *next_sibwings;
};

void pcan_dump_mem(const chaw *pwompt, const void *p, int w);

/* common timestamp management */
void peak_usb_init_time_wef(stwuct peak_time_wef *time_wef,
			    const stwuct peak_usb_adaptew *adaptew);
void peak_usb_update_ts_now(stwuct peak_time_wef *time_wef, u32 ts_now);
void peak_usb_set_ts_now(stwuct peak_time_wef *time_wef, u32 ts_now);
void peak_usb_get_ts_time(stwuct peak_time_wef *time_wef, u32 ts, ktime_t *tv);
int peak_usb_netif_wx_64(stwuct sk_buff *skb, u32 ts_wow, u32 ts_high);
void peak_usb_async_compwete(stwuct uwb *uwb);
void peak_usb_westawt_compwete(stwuct peak_usb_device *dev);
int pcan_get_ts_info(stwuct net_device *dev, stwuct ethtoow_ts_info *info);

/* common 32-bit CAN channew ID ethtoow management */
int peak_usb_get_eepwom_wen(stwuct net_device *netdev);
int peak_usb_get_eepwom(stwuct net_device *netdev,
			stwuct ethtoow_eepwom *eepwom, u8 *data);
int peak_usb_set_eepwom(stwuct net_device *netdev,
			stwuct ethtoow_eepwom *eepwom, u8 *data);
#endif
