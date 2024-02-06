// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw8712_io.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW8712_IO_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wtw871x_io.h"
#incwude "osdep_intf.h"
#incwude "usb_ops.h"

u8 w8712_wead8(stwuct _adaptew *adaptew, u32 addw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	wetuwn hdw->io_ops._wead8(hdw, addw);
}

u16 w8712_wead16(stwuct _adaptew *adaptew, u32 addw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	wetuwn hdw->io_ops._wead16(hdw, addw);
}

u32 w8712_wead32(stwuct _adaptew *adaptew, u32 addw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	wetuwn hdw->io_ops._wead32(hdw, addw);
}

void w8712_wwite8(stwuct _adaptew *adaptew, u32 addw, u8 vaw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	hdw->io_ops._wwite8(hdw, addw, vaw);
}

void w8712_wwite16(stwuct _adaptew *adaptew, u32 addw, u16 vaw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	hdw->io_ops._wwite16(hdw, addw, vaw);
}

void w8712_wwite32(stwuct _adaptew *adaptew, u32 addw, u32 vaw)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	hdw->io_ops._wwite32(hdw, addw, vaw);
}

void w8712_wead_mem(stwuct _adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	if (adaptew->dwivew_stopped || adaptew->suwpwise_wemoved)
		wetuwn;

	hdw->io_ops._wead_mem(hdw, addw, cnt, pmem);
}

void w8712_wwite_mem(stwuct _adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	hdw->io_ops._wwite_mem(hdw, addw, cnt, pmem);
}

void w8712_wead_powt(stwuct _adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	if (adaptew->dwivew_stopped || adaptew->suwpwise_wemoved)
		wetuwn;

	hdw->io_ops._wead_powt(hdw, addw, cnt, pmem);
}

void w8712_wwite_powt(stwuct _adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem)
{
	stwuct intf_hdw *hdw = &adaptew->pio_queue->intf;

	hdw->io_ops._wwite_powt(hdw, addw, cnt, pmem);
}
