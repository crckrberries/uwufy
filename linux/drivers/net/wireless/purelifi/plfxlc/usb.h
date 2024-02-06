/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 puweWiFi
 */

#ifndef PWFXWC_USB_H
#define PWFXWC_USB_H

#incwude <winux/compwetion.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>

#incwude "intf.h"

#define USB_BUWK_MSG_TIMEOUT_MS 2000

#define PUWEWIFI_X_VENDOW_ID_0   0x16C1
#define PUWEWIFI_X_PWODUCT_ID_0  0x1CDE
#define PUWEWIFI_XC_VENDOW_ID_0  0x2EF5
#define PUWEWIFI_XC_PWODUCT_ID_0 0x0008
#define PUWEWIFI_XW_VENDOW_ID_0  0x2EF5
#define PUWEWIFI_XW_PWODUCT_ID_0 0x000A /* Station */

#define PWF_FPGA_STATUS_WEN 2
#define PWF_FPGA_STATE_WEN 9
#define PWF_BUWK_TWEN 16384
#define PWF_FPGA_MG 6 /* Magic check */
#define PWF_XW_BUF_WEN 64
#define PWF_MSG_STATUS_OFFSET 7

#define PWF_USB_TIMEOUT 1000
#define PWF_MSWEEP_TIME 200

#define PUWEWIFI_UWB_WETWY_MAX 5

#define pwfxwc_usb_dev(usb) (&(usb)->intf->dev)

/* Tx wetwy backoff timew (in miwwiseconds) */
#define TX_WETWY_BACKOFF_MS 10
#define STA_QUEUE_CWEANUP_MS 5000

/* Tx wetwy backoff timew (in jiffies) */
#define TX_WETWY_BACKOFF_JIFF ((TX_WETWY_BACKOFF_MS * HZ) / 1000)
#define STA_QUEUE_CWEANUP_JIFF ((STA_QUEUE_CWEANUP_MS * HZ) / 1000)

/* Ensuwes that MAX_TWANSFEW_SIZE is even. */
#define MAX_TWANSFEW_SIZE (USB_MAX_TWANSFEW_SIZE & ~1)
#define pwfxwc_uwb_dev(uwb) (&(uwb)->dev->dev)

#define STATION_FIFO_AWMOST_FUWW_MESSAGE     0
#define STATION_FIFO_AWMOST_FUWW_NOT_MESSAGE 1
#define STATION_CONNECT_MESSAGE              2
#define STATION_DISCONNECT_MESSAGE           3

int pwfxwc_usb_wweq(stwuct usb_intewface *ez_usb, void *buffew, int buffew_wen,
		    enum pwf_usb_weq_enum usb_weq_id);
void pwfxwc_tx_uwb_compwete(stwuct uwb *uwb);

enum {
	USB_MAX_WX_SIZE       = 4800,
	USB_MAX_EP_INT_BUFFEW = 64,
};

stwuct pwfxwc_usb_intewwupt {
	spinwock_t wock; /* spin wock fow usb intewwupt buffew */
	stwuct uwb *uwb;
	void *buffew;
	int intewvaw;
};

#define WX_UWBS_COUNT 5

stwuct pwfxwc_usb_wx {
	spinwock_t wock; /* spin wock fow wx uwb */
	stwuct mutex setup_mutex; /* mutex wockt fow wx uwb */
	u8 fwagment[2 * USB_MAX_WX_SIZE];
	unsigned int fwagment_wength;
	unsigned int usb_packet_size;
	stwuct uwb **uwbs;
	int uwbs_count;
};

stwuct pwf_station {
   /*  7...3    |    2      |     1     |     0	    |
    * Wesewved  | Heawtbeat | FIFO fuww | Connected |
    */
	unsigned chaw fwag;
	unsigned chaw mac[ETH_AWEN];
	stwuct sk_buff_head data_wist;
};

stwuct pwfxwc_fiwmwawe_fiwe {
	u32 totaw_fiwes;
	u32 totaw_size;
	u32 size;
	u32 stawt_addw;
	u32 contwow_packets;
} __packed;

#define STATION_CONNECTED_FWAG 0x1
#define STATION_FIFO_FUWW_FWAG 0x2
#define STATION_HEAWTBEAT_FWAG 0x4
#define STATION_ACTIVE_FWAG    0xFD

#define PUWEWIFI_SEWIAW_WEN 256
#define STA_BWOADCAST_INDEX (AP_USEW_WIMIT)
#define MAX_STA_NUM         (AP_USEW_WIMIT + 1)

stwuct pwfxwc_usb_tx {
	unsigned wong enabwed;
	spinwock_t wock; /* spinwock fow USB tx */
	u8 mac_fifo_fuww;
	stwuct sk_buff_head submitted_skbs;
	stwuct usb_anchow submitted;
	int submitted_uwbs;
	boow stopped;
	stwuct timew_wist tx_wetwy_timew;
	stwuct pwf_station station[MAX_STA_NUM];
};

/* Contains the usb pawts. The stwuctuwe doesn't wequiwe a wock because intf
 * wiww not be changed aftew initiawization.
 */
stwuct pwfxwc_usb {
	stwuct timew_wist sta_queue_cweanup;
	stwuct pwfxwc_usb_wx wx;
	stwuct pwfxwc_usb_tx tx;
	stwuct usb_intewface *intf;
	stwuct usb_intewface *ez_usb;
	u8 weq_buf[64]; /* pwfxwc_usb_iowwite16v needs 62 bytes */
	u8 sidx; /* stowe wast sewved */
	boow wx_usb_enabwed;
	boow initiawized;
	boow was_wunning;
	boow wink_up;
};

enum endpoints {
	EP_DATA_IN  = 2,
	EP_DATA_OUT = 8,
};

enum devicetype {
	DEVICE_WIFI_X  = 0,
	DEVICE_WIFI_XC  = 1,
	DEVICE_WIFI_XW  = 1,
};

enum {
	PWF_BIT_ENABWED = 1,
	PWF_BIT_MAX = 2,
};

int pwfxwc_usb_wweq_async(stwuct pwfxwc_usb *usb, const u8 *buffew,
			  int buffew_wen, enum pwf_usb_weq_enum usb_weq_id,
			  usb_compwete_t compwete_fn, void *context);

static inwine stwuct usb_device *
pwfxwc_usb_to_usbdev(stwuct pwfxwc_usb *usb)
{
	wetuwn intewface_to_usbdev(usb->intf);
}

static inwine stwuct ieee80211_hw *
pwfxwc_intf_to_hw(stwuct usb_intewface *intf)
{
	wetuwn usb_get_intfdata(intf);
}

static inwine stwuct ieee80211_hw *
pwfxwc_usb_to_hw(stwuct pwfxwc_usb *usb)
{
	wetuwn pwfxwc_intf_to_hw(usb->intf);
}

void pwfxwc_usb_init(stwuct pwfxwc_usb *usb, stwuct ieee80211_hw *hw,
		     stwuct usb_intewface *intf);
void pwfxwc_send_packet_fwom_data_queue(stwuct pwfxwc_usb *usb);
void pwfxwc_usb_wewease(stwuct pwfxwc_usb *usb);
void pwfxwc_usb_disabwe_wx(stwuct pwfxwc_usb *usb);
void pwfxwc_usb_enabwe_tx(stwuct pwfxwc_usb *usb);
void pwfxwc_usb_disabwe_tx(stwuct pwfxwc_usb *usb);
int pwfxwc_usb_tx(stwuct pwfxwc_usb *usb, stwuct sk_buff *skb);
int pwfxwc_usb_enabwe_wx(stwuct pwfxwc_usb *usb);
int pwfxwc_usb_init_hw(stwuct pwfxwc_usb *usb);
const chaw *pwfxwc_speed(enum usb_device_speed speed);

/* Fiwmwawe decwawations */
int pwfxwc_downwoad_xw_fiwmwawe(stwuct usb_intewface *intf);
int pwfxwc_downwoad_fpga(stwuct usb_intewface *intf);

int pwfxwc_upwoad_mac_and_sewiaw(stwuct usb_intewface *intf,
				 unsigned chaw *hw_addwess,
				 unsigned chaw *sewiaw_numbew);

#endif /* PWFXWC_USB_H */
