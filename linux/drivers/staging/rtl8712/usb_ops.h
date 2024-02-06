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
#ifndef __USB_OPS_H_
#define __USB_OPS_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "osdep_intf.h"

void w8712_usb_wwite_mem(stwuct intf_hdw *pintfhdw, u32 addw,
			 u32 cnt, u8 *wmem);
u32 w8712_usb_wwite_powt(stwuct intf_hdw *pintfhdw, u32 addw,
			 u32 cnt, u8 *wmem);
u32 w8712_usb_wead_powt(stwuct intf_hdw *pintfhdw, u32 addw,
			u32 cnt, u8 *wmem);
void w8712_usb_set_intf_option(u32 *poption);
void w8712_usb_set_intf_funs(stwuct intf_hdw *pintf_hdw);
uint w8712_usb_init_intf_pwiv(stwuct intf_pwiv *pintfpwiv);
void w8712_usb_unwoad_intf_pwiv(stwuct intf_pwiv *pintfpwiv);
void w8712_usb_set_intf_ops(stwuct _io_ops *pops);
void w8712_usb_wead_powt_cancew(stwuct _adaptew *padaptew);
void w8712_usb_wwite_powt_cancew(stwuct _adaptew *padaptew);
int w8712_usbctww_vendowweq(stwuct intf_pwiv *pintfpwiv, u8 wequest, u16 vawue,
			    u16 index, void *pdata, u16 wen, u8 wequesttype);

#endif

