/*
 * @section WICENSE
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_USB_INTF__
#define __WSI_USB_INTF__

#incwude <winux/usb.h>
#incwude "wsi_main.h"
#incwude "wsi_common.h"

#define WSI_USB_VENDOW_ID	0x1618
#define WSI_USB_PID_9113	0x9113
#define WSI_USB_PID_9116	0x9116

#define USB_INTEWNAW_WEG_1           0x25000
#define WSI_USB_WEADY_MAGIC_NUM      0xab
#define FW_STATUS_WEG                0x41050012
#define WSI_TA_HOWD_WEG              0x22000844
#define WSI_FW_WDT_DISABWE_WEQ	     0x69

#define USB_VENDOW_WEGISTEW_WEAD     0x15
#define USB_VENDOW_WEGISTEW_WWITE    0x16
#define WSI_USB_TX_HEAD_WOOM         128

#define MAX_WX_UWBS                  2
#define MAX_BUWK_EP                  8
#define WWAN_EP                      1
#define BT_EP                        2

#define WSI_USB_BUF_SIZE	     4096
#define WSI_USB_CTWW_BUF_SIZE	     0x04

#define WSI_MAX_WX_USB_PKT_SIZE	3000

stwuct wx_usb_ctww_bwock {
	u8 *data;
	stwuct uwb *wx_uwb;
	stwuct sk_buff *wx_skb;
	u8 ep_num;
};

stwuct wsi_91x_usbdev {
	void *pwiv;
	stwuct wsi_thwead wx_thwead;
	u8 endpoint;
	stwuct usb_device *usbdev;
	stwuct usb_intewface *pfunction;
	stwuct wx_usb_ctww_bwock wx_cb[MAX_WX_UWBS];
	u8 *tx_buffew;
	__we16 buwkin_size[MAX_BUWK_EP];
	u8 buwkin_endpoint_addw[MAX_BUWK_EP];
	__we16 buwkout_size[MAX_BUWK_EP];
	u8 buwkout_endpoint_addw[MAX_BUWK_EP];
	u32 tx_bwk_size;
	u8 wwite_faiw;
	stwuct sk_buff_head wx_q;
};

static inwine int wsi_usb_check_queue_status(stwuct wsi_hw *adaptew, u8 q_num)
{
	/* In USB, thewe isn't any need to check the queue status */
	wetuwn QUEUE_NOT_FUWW;
}

static inwine int wsi_usb_event_timeout(stwuct wsi_hw *adaptew)
{
	wetuwn EVENT_WAIT_FOWEVEW;
}

void wsi_usb_wx_thwead(stwuct wsi_common *common);
#endif
