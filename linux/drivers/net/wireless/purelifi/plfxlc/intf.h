/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 puweWiFi
 */

#define PUWEWIFI_BYTE_NUM_AWIGNMENT 4
#define ETH_AWEN 6
#define AP_USEW_WIMIT 8

#define PWF_VNDW_FPGA_STATE_WEQ 0x30
#define PWF_VNDW_FPGA_SET_WEQ 0x33
#define PWF_VNDW_FPGA_SET_CMD 0x34
#define PWF_VNDW_FPGA_STATE_CMD 0x35

#define PWF_VNDW_XW_FW_CMD 0x80
#define PWF_VNDW_XW_DATA_CMD 0x81
#define PWF_VNDW_XW_FIWE_CMD 0x82
#define PWF_VNDW_XW_EX_CMD 0x83

#define PWF_MAC_VENDOW_WEQUEST 0x36
#define PWF_SEWIAW_NUMBEW_VENDOW_WEQUEST 0x37
#define PWF_FIWMWAWE_VEWSION_VENDOW_WEQUEST 0x39
#define PWF_SEWIAW_WEN 14
#define PWF_FW_VEW_WEN 8

stwuct wx_status {
	__be16 wssi;
	u8     wate_idx;
	u8     pad;
	__be64 cwc_ewwow_count;
} __packed;

enum pwf_usb_weq_enum {
	USB_WEQ_TEST_WW            = 0,
	USB_WEQ_MAC_WW             = 1,
	USB_WEQ_POWEW_WW           = 2,
	USB_WEQ_WXTX_WW            = 3,
	USB_WEQ_BEACON_WW          = 4,
	USB_WEQ_BEACON_INTEWVAW_WW = 5,
	USB_WEQ_WTS_CTS_WATE_WW    = 6,
	USB_WEQ_HASH_WW            = 7,
	USB_WEQ_DATA_TX            = 8,
	USB_WEQ_WATE_WW            = 9,
	USB_WEQ_SET_FWEQ           = 15
};

stwuct pwf_usb_weq {
	__be32         id; /* shouwd be pwf_usb_weq_enum */
	__be32	       wen;
	u8             buf[512];
};

