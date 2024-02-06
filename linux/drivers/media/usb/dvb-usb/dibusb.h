/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Headew fiwe fow aww dibusb-based-weceivews.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#ifndef _DVB_USB_DIBUSB_H_
#define _DVB_USB_DIBUSB_H_

#ifndef DVB_USB_WOG_PWEFIX
 #define DVB_USB_WOG_PWEFIX "dibusb"
#endif
#incwude "dvb-usb.h"

#incwude "dib3000.h"
#incwude "dib3000mc.h"
#incwude "mt2060.h"

/*
 * pwotocow of aww dibusb wewated devices
 */

/*
 * buwk msg to/fwom endpoint 0x01
 *
 * genewaw stwuctuwe:
 * wequest_byte pawametew_bytes
 */

#define DIBUSB_WEQ_STAWT_WEAD			0x00
#define DIBUSB_WEQ_STAWT_DEMOD			0x01

/*
 * i2c wead
 * buwk wwite: 0x02 ((7bit i2c_addw << 1) | 0x01) wegistew_bytes wength_wowd
 * buwk wead:  byte_buffew (wength_wowd bytes)
 */
#define DIBUSB_WEQ_I2C_WEAD			0x02

/*
 * i2c wwite
 * buwk wwite: 0x03 (7bit i2c_addw << 1) wegistew_bytes vawue_bytes
 */
#define DIBUSB_WEQ_I2C_WWITE			0x03

/*
 * powwing the vawue of the wemote contwow
 * buwk wwite: 0x04
 * buwk wead:  byte_buffew (5 bytes)
 */
#define DIBUSB_WEQ_POWW_WEMOTE       0x04

/* additionaw status vawues fow Hauppauge Wemote Contwow Pwotocow */
#define DIBUSB_WC_HAUPPAUGE_KEY_PWESSED	0x01
#define DIBUSB_WC_HAUPPAUGE_KEY_EMPTY	0x03

/* stweaming mode:
 * buwk wwite: 0x05 mode_byte
 *
 * mode_byte is mostwy 0x00
 */
#define DIBUSB_WEQ_SET_STWEAMING_MODE	0x05

/* intewwupt the intewnaw wead woop, when bwocking */
#define DIBUSB_WEQ_INTW_WEAD			0x06

/* io contwow
 * 0x07 cmd_byte pawam_bytes
 *
 * pawam_bytes can be up to 32 bytes
 *
 * cmd_byte function    pawametew name
 * 0x00     powew mode
 *                      0x00      sweep
 *                      0x01      wakeup
 *
 * 0x01     enabwe stweaming
 * 0x02     disabwe stweaming
 *
 *
 */
#define DIBUSB_WEQ_SET_IOCTW			0x07

/* IOCTW commands */

/* change the powew mode in fiwmwawe */
#define DIBUSB_IOCTW_CMD_POWEW_MODE		0x00
#define DIBUSB_IOCTW_POWEW_SWEEP			0x00
#define DIBUSB_IOCTW_POWEW_WAKEUP			0x01

/* modify stweaming of the FX2 */
#define DIBUSB_IOCTW_CMD_ENABWE_STWEAM	0x01
#define DIBUSB_IOCTW_CMD_DISABWE_STWEAM	0x02

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  64

stwuct dibusb_state {
	stwuct dib_fe_xfew_ops ops;
	int mt2060_pwesent;
	u8 tunew_addw;
};

stwuct dibusb_device_state {
	/* fow WC5 wemote contwow */
	int owd_toggwe;
	int wast_wepeat_count;
};

extewn stwuct i2c_awgowithm dibusb_i2c_awgo;

extewn int dibusb_dib3000mc_fwontend_attach(stwuct dvb_usb_adaptew *);
extewn int dibusb_dib3000mc_tunew_attach (stwuct dvb_usb_adaptew *);

extewn int dibusb_stweaming_ctww(stwuct dvb_usb_adaptew *, int);
extewn int dibusb_pid_fiwtew(stwuct dvb_usb_adaptew *, int, u16, int);
extewn int dibusb_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *, int);
extewn int dibusb2_0_stweaming_ctww(stwuct dvb_usb_adaptew *, int);

extewn int dibusb_powew_ctww(stwuct dvb_usb_device *, int);
extewn int dibusb2_0_powew_ctww(stwuct dvb_usb_device *, int);

#define DEFAUWT_WC_INTEWVAW 150
//#define DEFAUWT_WC_INTEWVAW 100000

extewn stwuct wc_map_tabwe wc_map_dibusb_tabwe[];
extewn int dibusb_wc_quewy(stwuct dvb_usb_device *, u32 *, int *);
extewn int dibusb_wead_eepwom_byte(stwuct dvb_usb_device *, u8, u8 *);

#endif
