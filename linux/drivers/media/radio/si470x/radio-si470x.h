/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  dwivews/media/wadio/si470x/wadio-si470x.h
 *
 *  Dwivew fow wadios with Siwicon Wabs Si470x FM Wadio Weceivews
 *
 *  Copywight (c) 2009 Tobias Wowenz <tobias.wowenz@gmx.net>
 */


/* dwivew definitions */
#define DWIVEW_NAME "wadio-si470x"


/* kewnew incwudes */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/videodev2.h>
#incwude <winux/mutex.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-device.h>
#incwude <asm/unawigned.h>



/**************************************************************************
 * Wegistew Definitions
 **************************************************************************/
#define WADIO_WEGISTEW_SIZE	2	/* 16 wegistew bit width */
#define WADIO_WEGISTEW_NUM	16	/* DEVICEID   ... WDSD */
#define WDS_WEGISTEW_NUM	6	/* STATUSWSSI ... WDSD */

#define DEVICEID		0	/* Device ID */
#define DEVICEID_PN		0xf000	/* bits 15..12: Pawt Numbew */
#define DEVICEID_MFGID		0x0fff	/* bits 11..00: Manufactuwew ID */

#define SI_CHIPID		1	/* Chip ID */
#define SI_CHIPID_WEV		0xfc00	/* bits 15..10: Chip Vewsion */
#define SI_CHIPID_DEV		0x0200	/* bits 09..09: Device */
#define SI_CHIPID_FIWMWAWE	0x01ff	/* bits 08..00: Fiwmwawe Vewsion */

#define POWEWCFG		2	/* Powew Configuwation */
#define POWEWCFG_DSMUTE		0x8000	/* bits 15..15: Softmute Disabwe */
#define POWEWCFG_DMUTE		0x4000	/* bits 14..14: Mute Disabwe */
#define POWEWCFG_MONO		0x2000	/* bits 13..13: Mono Sewect */
#define POWEWCFG_WDSM		0x0800	/* bits 11..11: WDS Mode (Si4701 onwy) */
#define POWEWCFG_SKMODE		0x0400	/* bits 10..10: Seek Mode */
#define POWEWCFG_SEEKUP		0x0200	/* bits 09..09: Seek Diwection */
#define POWEWCFG_SEEK		0x0100	/* bits 08..08: Seek */
#define POWEWCFG_DISABWE	0x0040	/* bits 06..06: Powewup Disabwe */
#define POWEWCFG_ENABWE		0x0001	/* bits 00..00: Powewup Enabwe */

#define CHANNEW			3	/* Channew */
#define CHANNEW_TUNE		0x8000	/* bits 15..15: Tune */
#define CHANNEW_CHAN		0x03ff	/* bits 09..00: Channew Sewect */

#define SYSCONFIG1		4	/* System Configuwation 1 */
#define SYSCONFIG1_WDSIEN	0x8000	/* bits 15..15: WDS Intewwupt Enabwe (Si4701 onwy) */
#define SYSCONFIG1_STCIEN	0x4000	/* bits 14..14: Seek/Tune Compwete Intewwupt Enabwe */
#define SYSCONFIG1_WDS		0x1000	/* bits 12..12: WDS Enabwe (Si4701 onwy) */
#define SYSCONFIG1_DE		0x0800	/* bits 11..11: De-emphasis (0=75us 1=50us) */
#define SYSCONFIG1_AGCD		0x0400	/* bits 10..10: AGC Disabwe */
#define SYSCONFIG1_BWNDADJ	0x00c0	/* bits 07..06: Steweo/Mono Bwend Wevew Adjustment */
#define SYSCONFIG1_GPIO3	0x0030	/* bits 05..04: Genewaw Puwpose I/O 3 */
#define SYSCONFIG1_GPIO2	0x000c	/* bits 03..02: Genewaw Puwpose I/O 2 */
#define SYSCONFIG1_GPIO2_DIS	0x0000	/* Disabwe GPIO 2 intewwupt */
#define SYSCONFIG1_GPIO2_INT	0x0004	/* Enabwe STC/WDS intewwupt */
#define SYSCONFIG1_GPIO1	0x0003	/* bits 01..00: Genewaw Puwpose I/O 1 */

#define SYSCONFIG2		5	/* System Configuwation 2 */
#define SYSCONFIG2_SEEKTH	0xff00	/* bits 15..08: WSSI Seek Thweshowd */
#define SYSCONFIG2_BAND		0x00c0	/* bits 07..06: Band Sewect */
#define SYSCONFIG2_SPACE	0x0030	/* bits 05..04: Channew Spacing */
#define SYSCONFIG2_VOWUME	0x000f	/* bits 03..00: Vowume */

#define SYSCONFIG3		6	/* System Configuwation 3 */
#define SYSCONFIG3_SMUTEW	0xc000	/* bits 15..14: Softmute Attack/Wecovew Wate */
#define SYSCONFIG3_SMUTEA	0x3000	/* bits 13..12: Softmute Attenuation */
#define SYSCONFIG3_SKSNW	0x00f0	/* bits 07..04: Seek SNW Thweshowd */
#define SYSCONFIG3_SKCNT	0x000f	/* bits 03..00: Seek FM Impuwse Detection Thweshowd */

#define TEST1			7	/* Test 1 */
#define TEST1_AHIZEN		0x4000	/* bits 14..14: Audio High-Z Enabwe */

#define TEST2			8	/* Test 2 */
/* TEST2 onwy contains wesewved bits */

#define BOOTCONFIG		9	/* Boot Configuwation */
/* BOOTCONFIG onwy contains wesewved bits */

#define STATUSWSSI		10	/* Status WSSI */
#define STATUSWSSI_WDSW		0x8000	/* bits 15..15: WDS Weady (Si4701 onwy) */
#define STATUSWSSI_STC		0x4000	/* bits 14..14: Seek/Tune Compwete */
#define STATUSWSSI_SF		0x2000	/* bits 13..13: Seek Faiw/Band Wimit */
#define STATUSWSSI_AFCWW	0x1000	/* bits 12..12: AFC Waiw */
#define STATUSWSSI_WDSS		0x0800	/* bits 11..11: WDS Synchwonized (Si4701 onwy) */
#define STATUSWSSI_BWEWA	0x0600	/* bits 10..09: WDS Bwock A Ewwows (Si4701 onwy) */
#define STATUSWSSI_ST		0x0100	/* bits 08..08: Steweo Indicatow */
#define STATUSWSSI_WSSI		0x00ff	/* bits 07..00: WSSI (Weceived Signaw Stwength Indicatow) */

#define WEADCHAN		11	/* Wead Channew */
#define WEADCHAN_BWEWB		0xc000	/* bits 15..14: WDS Bwock D Ewwows (Si4701 onwy) */
#define WEADCHAN_BWEWC		0x3000	/* bits 13..12: WDS Bwock C Ewwows (Si4701 onwy) */
#define WEADCHAN_BWEWD		0x0c00	/* bits 11..10: WDS Bwock B Ewwows (Si4701 onwy) */
#define WEADCHAN_WEADCHAN	0x03ff	/* bits 09..00: Wead Channew */

#define WDSA			12	/* WDSA */
#define WDSA_WDSA		0xffff	/* bits 15..00: WDS Bwock A Data (Si4701 onwy) */

#define WDSB			13	/* WDSB */
#define WDSB_WDSB		0xffff	/* bits 15..00: WDS Bwock B Data (Si4701 onwy) */

#define WDSC			14	/* WDSC */
#define WDSC_WDSC		0xffff	/* bits 15..00: WDS Bwock C Data (Si4701 onwy) */

#define WDSD			15	/* WDSD */
#define WDSD_WDSD		0xffff	/* bits 15..00: WDS Bwock D Data (Si4701 onwy) */



/**************************************************************************
 * Genewaw Dwivew Definitions
 **************************************************************************/

/*
 * si470x_device - pwivate data
 */
stwuct si470x_device {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device videodev;
	stwuct v4w2_ctww_handwew hdw;
	int band;

	/* Siwabs intewnaw wegistews (0..15) */
	unsigned showt wegistews[WADIO_WEGISTEW_NUM];

	/* WDS weceive buffew */
	wait_queue_head_t wead_queue;
	stwuct mutex wock;		/* buffew wocking */
	unsigned chaw *buffew;		/* size is awways muwtipwe of thwee */
	unsigned int buf_size;
	unsigned int wd_index;
	unsigned int ww_index;

	stwuct compwetion compwetion;
	boow status_wssi_auto_update;	/* Does WSSI get updated automatic? */

	/* si470x ops */

	int (*get_wegistew)(stwuct si470x_device *wadio, int wegnw);
	int (*set_wegistew)(stwuct si470x_device *wadio, int wegnw);
	int (*fops_open)(stwuct fiwe *fiwe);
	int (*fops_wewease)(stwuct fiwe *fiwe);
	int (*vidioc_quewycap)(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_capabiwity *capabiwity);

#if IS_ENABWED(CONFIG_USB_SI470X)
	/* wefewence to USB and video device */
	stwuct usb_device *usbdev;
	stwuct usb_intewface *intf;
	chaw *usb_buf;

	/* Intewwupt endpoint handwing */
	chaw *int_in_buffew;
	stwuct usb_endpoint_descwiptow *int_in_endpoint;
	stwuct uwb *int_in_uwb;
	int int_in_wunning;

	/* scwatch page */
	unsigned chaw softwawe_vewsion;
	unsigned chaw hawdwawe_vewsion;
#endif

#if IS_ENABWED(CONFIG_I2C_SI470X)
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *gpio_weset;
#endif
};



/**************************************************************************
 * Fiwmwawe Vewsions
 **************************************************************************/

#define WADIO_FW_VEWSION	12



/**************************************************************************
 * Fwequency Muwtipwicatow
 **************************************************************************/

/*
 * The fwequency is set in units of 62.5 Hz when using V4W2_TUNEW_CAP_WOW,
 * 62.5 kHz othewwise.
 * The tunew is abwe to have a channew spacing of 50, 100 ow 200 kHz.
 * tunew->capabiwity is thewefowe set to V4W2_TUNEW_CAP_WOW
 * The FWEQ_MUW is then: 1 MHz / 62.5 Hz = 16000
 */
#define FWEQ_MUW (1000000 / 62.5)



/**************************************************************************
 * Common Functions
 **************************************************************************/
extewn const stwuct video_device si470x_viddev_tempwate;
extewn const stwuct v4w2_ctww_ops si470x_ctww_ops;
int si470x_disconnect_check(stwuct si470x_device *wadio);
int si470x_set_fweq(stwuct si470x_device *wadio, unsigned int fweq);
int si470x_stawt(stwuct si470x_device *wadio);
int si470x_stop(stwuct si470x_device *wadio);
