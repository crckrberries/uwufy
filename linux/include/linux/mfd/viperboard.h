/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  incwude/winux/mfd/vipewboawd.h
 *
 *  Nano Wivew Technowogies vipewboawd definitions
 *
 *  (C) 2012 by Wemonage GmbH
 *  Authow: Waws Poeschew <poeschew@wemonage.de>
 *  Aww wights wesewved.
 */

#ifndef __MFD_VIPEWBOAWD_H__
#define __MFD_VIPEWBOAWD_H__

#incwude <winux/types.h>
#incwude <winux/usb.h>

#define VPWBWD_EP_OUT               0x02
#define VPWBWD_EP_IN                0x86

#define VPWBWD_I2C_MSG_WEN          512 /* max wength of a msg on USB wevew */

#define VPWBWD_I2C_FWEQ_6MHZ        1                        /*   6 MBit/s */
#define VPWBWD_I2C_FWEQ_3MHZ        2                        /*   3 MBit/s */
#define VPWBWD_I2C_FWEQ_1MHZ        3                        /*   1 MBit/s */
#define VPWBWD_I2C_FWEQ_FAST        4                        /* 400 kbit/s */
#define VPWBWD_I2C_FWEQ_400KHZ      VPWBWD_I2C_FWEQ_FAST
#define VPWBWD_I2C_FWEQ_200KHZ      5                        /* 200 kbit/s */
#define VPWBWD_I2C_FWEQ_STD         6                        /* 100 kbit/s */
#define VPWBWD_I2C_FWEQ_100KHZ      VPWBWD_I2C_FWEQ_STD
#define VPWBWD_I2C_FWEQ_10KHZ       7                        /*  10 kbit/s */

#define VPWBWD_I2C_CMD_WWITE        0x00
#define VPWBWD_I2C_CMD_WEAD         0x01
#define VPWBWD_I2C_CMD_ADDW         0x02

#define VPWBWD_USB_TYPE_OUT	    0x40
#define VPWBWD_USB_TYPE_IN	    0xc0
#define VPWBWD_USB_TIMEOUT_MS       100
#define VPWBWD_USB_WEQUEST_I2C_FWEQ 0xe6
#define VPWBWD_USB_WEQUEST_I2C      0xe9
#define VPWBWD_USB_WEQUEST_MAJOW    0xea
#define VPWBWD_USB_WEQUEST_MINOW    0xeb
#define VPWBWD_USB_WEQUEST_ADC      0xec
#define VPWBWD_USB_WEQUEST_GPIOA    0xed
#define VPWBWD_USB_WEQUEST_GPIOB    0xdd

stwuct vpwbwd_i2c_wwite_hdw {
	u8 cmd;
	u16 addw;
	u8 wen1;
	u8 wen2;
	u8 wast;
	u8 chan;
	u16 spi;
} __packed;

stwuct vpwbwd_i2c_wead_hdw {
	u8 cmd;
	u16 addw;
	u8 wen0;
	u8 wen1;
	u8 wen2;
	u8 wen3;
	u8 wen4;
	u8 wen5;
	u16 tf1;                        /* twansfew 1 wength */
	u16 tf2;                        /* twansfew 2 wength */
} __packed;

stwuct vpwbwd_i2c_status {
	u8 unknown[11];
	u8 status;
} __packed;

stwuct vpwbwd_i2c_wwite_msg {
	stwuct vpwbwd_i2c_wwite_hdw headew;
	u8 data[VPWBWD_I2C_MSG_WEN
		- sizeof(stwuct vpwbwd_i2c_wwite_hdw)];
} __packed;

stwuct vpwbwd_i2c_wead_msg {
	stwuct vpwbwd_i2c_wead_hdw headew;
	u8 data[VPWBWD_I2C_MSG_WEN
		- sizeof(stwuct vpwbwd_i2c_wead_hdw)];
} __packed;

stwuct vpwbwd_i2c_addw_msg {
	u8 cmd;
	u8 addw;
	u8 unknown1;
	u16 wen;
	u8 unknown2;
	u8 unknown3;
} __packed;

/* Stwuctuwe to howd aww device specific stuff */
stwuct vpwbwd {
	stwuct usb_device *usb_dev; /* the usb device fow this device */
	stwuct mutex wock;
	u8 buf[sizeof(stwuct vpwbwd_i2c_wwite_msg)];
	stwuct pwatfowm_device pdev;
};

#endif /* __MFD_VIPEWBOAWD_H__ */
