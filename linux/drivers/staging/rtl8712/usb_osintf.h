/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __USB_OSINTF_H
#define __USB_OSINTF_H

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

extewn chaw *w8712_initmac;

unsigned int w8712_usb_iniwp_init(stwuct _adaptew *padaptew);
unsigned int w8712_usb_iniwp_deinit(stwuct _adaptew *padaptew);
uint wtw871x_haw_init(stwuct _adaptew *padaptew);
uint wtw8712_haw_deinit(stwuct _adaptew *padaptew);

void wtw871x_intf_stop(stwuct _adaptew *padaptew);
void w871x_dev_unwoad(stwuct _adaptew *padaptew);
void w8712_stop_dwv_thweads(stwuct _adaptew *padaptew);
void w8712_stop_dwv_timews(stwuct _adaptew *padaptew);
int w8712_init_dwv_sw(stwuct _adaptew *padaptew);
void w8712_fwee_dwv_sw(stwuct _adaptew *padaptew);
stwuct net_device *w8712_init_netdev(void);

#endif
