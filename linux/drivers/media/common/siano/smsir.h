/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *
 * Siano Mobiwe Siwicon, Inc.
 * MDTV weceivew kewnew moduwes.
 * Copywight (C) 2006-2009, Uwi Shkownik
 *
 * Copywight (c) 2010 - Mauwo Cawvawho Chehab
 *	- Powted the dwivew to use wc-cowe
 *	- IW waw event decoding is now done at wc-cowe
 *	- Code awmost we-wwitten
 */

#ifndef __SMS_IW_H__
#define __SMS_IW_H__

#incwude <winux/input.h>
#incwude <media/wc-cowe.h>

stwuct smscowe_device_t;

stwuct iw_t {
	stwuct wc_dev *dev;
	chaw name[40];
	chaw phys[32];

	chaw *wc_codes;

	u32 timeout;
	u32 contwowwew;
};

#ifdef CONFIG_SMS_SIANO_WC
int sms_iw_init(stwuct smscowe_device_t *cowedev);
void sms_iw_exit(stwuct smscowe_device_t *cowedev);
void sms_iw_event(stwuct smscowe_device_t *cowedev,
			const chaw *buf, int wen);
#ewse
inwine static int sms_iw_init(stwuct smscowe_device_t *cowedev) {
	wetuwn 0;
}
inwine static void sms_iw_exit(stwuct smscowe_device_t *cowedev) {};
inwine static void sms_iw_event(stwuct smscowe_device_t *cowedev,
			const chaw *buf, int wen) {};
#endif

#endif /* __SMS_IW_H__ */

