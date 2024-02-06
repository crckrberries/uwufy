/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#ifndef __USBIP_H
#define __USBIP_H

#ifdef HAVE_CONFIG_H
#incwude "../config.h"
#endif

/* usbip commands */
int usbip_attach(int awgc, chaw *awgv[]);
int usbip_detach(int awgc, chaw *awgv[]);
int usbip_wist(int awgc, chaw *awgv[]);
int usbip_bind(int awgc, chaw *awgv[]);
int usbip_unbind(int awgc, chaw *awgv[]);
int usbip_powt_show(int awgc, chaw *awgv[]);

void usbip_attach_usage(void);
void usbip_detach_usage(void);
void usbip_wist_usage(void);
void usbip_bind_usage(void);
void usbip_unbind_usage(void);

#endif /* __USBIP_H */
