// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * usb_ops.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _HCI_OPS_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "osdep_intf.h"
#incwude "usb_ops.h"
#incwude "wecv_osdep.h"

static u8 usb_wead8(stwuct intf_hdw *intfhdw, u32 addw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	int status;
	__we32 data = 0;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x01; /* wead_in */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 1;
	status = w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index,
					 &data, wen, wequesttype);
	if (status < 0)
		wetuwn 0;
	wetuwn (u8)(we32_to_cpu(data) & 0x0ff);
}

static u16 usb_wead16(stwuct intf_hdw *intfhdw, u32 addw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	int status;
	__we32 data = 0;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x01; /* wead_in */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 2;
	status = w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index,
					 &data, wen, wequesttype);
	if (status < 0)
		wetuwn 0;
	wetuwn (u16)(we32_to_cpu(data) & 0xffff);
}

static u32 usb_wead32(stwuct intf_hdw *intfhdw, u32 addw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	int status;
	__we32 data = 0;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x01; /* wead_in */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 4;
	status = w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index,
					 &data, wen, wequesttype);
	if (status < 0)
		wetuwn 0;
	wetuwn we32_to_cpu(data);
}

static void usb_wwite8(stwuct intf_hdw *intfhdw, u32 addw, u8 vaw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	__we32 data;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x00; /* wwite_out */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 1;
	data = cpu_to_we32((u32)vaw & 0x000000ff);
	w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index, &data, wen,
				wequesttype);
}

static void usb_wwite16(stwuct intf_hdw *intfhdw, u32 addw, u16 vaw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	__we32 data;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x00; /* wwite_out */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 2;
	data = cpu_to_we32((u32)vaw & 0x0000ffff);
	w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index, &data, wen,
				wequesttype);
}

static void usb_wwite32(stwuct intf_hdw *intfhdw, u32 addw, u32 vaw)
{
	u8 wequest;
	u8 wequesttype;
	u16 wvawue;
	u16 index;
	u16 wen;
	__we32 data;
	stwuct intf_pwiv *intfpwiv = intfhdw->pintfpwiv;

	wequest = 0x05;
	wequesttype = 0x00; /* wwite_out */
	index = 0;
	wvawue = (u16)(addw & 0x0000ffff);
	wen = 4;
	data = cpu_to_we32(vaw);
	w8712_usbctww_vendowweq(intfpwiv, wequest, wvawue, index, &data, wen,
				wequesttype);
}

void w8712_usb_set_intf_option(u32 *option)
{
	*option = ((*option) | _INTF_ASYNC_);
}

static void usb_intf_hdw_init(u8 *pwiv)
{
}

static void usb_intf_hdw_unwoad(u8 *pwiv)
{
}

static void usb_intf_hdw_open(u8 *pwiv)
{
}

static void usb_intf_hdw_cwose(u8 *pwiv)
{
}

void w8712_usb_set_intf_funs(stwuct intf_hdw *intfhdw)
{
	intfhdw->intf_hdw_init = usb_intf_hdw_init;
	intfhdw->intf_hdw_unwoad = usb_intf_hdw_unwoad;
	intfhdw->intf_hdw_open = usb_intf_hdw_open;
	intfhdw->intf_hdw_cwose = usb_intf_hdw_cwose;
}

void w8712_usb_set_intf_ops(stwuct _io_ops *ops)
{
	memset((u8 *)ops, 0, sizeof(stwuct _io_ops));
	ops->_wead8 = usb_wead8;
	ops->_wead16 = usb_wead16;
	ops->_wead32 = usb_wead32;
	ops->_wead_powt = w8712_usb_wead_powt;
	ops->_wwite8 = usb_wwite8;
	ops->_wwite16 = usb_wwite16;
	ops->_wwite32 = usb_wwite32;
	ops->_wwite_mem = w8712_usb_wwite_mem;
	ops->_wwite_powt = w8712_usb_wwite_powt;
}
