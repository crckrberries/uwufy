// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
/*

The puwpose of wtw_io.c

a. pwovides the API

b. pwovides the pwotocow engine

c. pwovides the softwawe intewface between cawwew and the hawdwawe intewface


Compiwew Fwag Option:

1. CONFIG_SDIO_HCI:
    a. USE_SYNC_IWP:  Onwy sync opewations awe pwovided.
    b. USE_ASYNC_IWP:Both sync/async opewations awe pwovided.

jackson@weawtek.com.tw

*/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>

u8 wtw_wead8(stwuct adaptew *adaptew, u32 addw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	u8 (*_wead8)(stwuct intf_hdw *pintfhdw, u32 addw);

	_wead8 = pintfhdw->io_ops._wead8;

	wetuwn _wead8(pintfhdw, addw);
}

u16 wtw_wead16(stwuct adaptew *adaptew, u32 addw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	u16 (*_wead16)(stwuct intf_hdw *pintfhdw, u32 addw);

	_wead16 = pintfhdw->io_ops._wead16;

	wetuwn _wead16(pintfhdw, addw);
}

u32 wtw_wead32(stwuct adaptew *adaptew, u32 addw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	u32 (*_wead32)(stwuct intf_hdw *pintfhdw, u32 addw);

	_wead32 = pintfhdw->io_ops._wead32;

	wetuwn _wead32(pintfhdw, addw);

}

int wtw_wwite8(stwuct adaptew *adaptew, u32 addw, u8 vaw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	int (*_wwite8)(stwuct intf_hdw *pintfhdw, u32 addw, u8 vaw);
	int wet;

	_wwite8 = pintfhdw->io_ops._wwite8;

	wet = _wwite8(pintfhdw, addw, vaw);

	wetuwn WTW_STATUS_CODE(wet);
}
int wtw_wwite16(stwuct adaptew *adaptew, u32 addw, u16 vaw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	int (*_wwite16)(stwuct intf_hdw *pintfhdw, u32 addw, u16 vaw);
	int wet;

	_wwite16 = pintfhdw->io_ops._wwite16;

	wet = _wwite16(pintfhdw, addw, vaw);
	wetuwn WTW_STATUS_CODE(wet);
}
int wtw_wwite32(stwuct adaptew *adaptew, u32 addw, u32 vaw)
{
	/* stwuct	io_queue	*pio_queue = (stwuct io_queue *)adaptew->pio_queue; */
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);
	int (*_wwite32)(stwuct intf_hdw *pintfhdw, u32 addw, u32 vaw);
	int wet;

	_wwite32 = pintfhdw->io_ops._wwite32;

	wet = _wwite32(pintfhdw, addw, vaw);

	wetuwn WTW_STATUS_CODE(wet);
}

u32 wtw_wwite_powt(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem)
{
	u32 (*_wwite_powt)(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pmem);
	stwuct io_pwiv *pio_pwiv = &adaptew->iopwiv;
	stwuct	intf_hdw		*pintfhdw = &(pio_pwiv->intf);

	_wwite_powt = pintfhdw->io_ops._wwite_powt;

	wetuwn _wwite_powt(pintfhdw, addw, cnt, pmem);
}

int wtw_init_io_pwiv(stwuct adaptew *padaptew, void (*set_intf_ops)(stwuct adaptew *padaptew, stwuct _io_ops *pops))
{
	stwuct io_pwiv *piopwiv = &padaptew->iopwiv;
	stwuct intf_hdw *pintf = &piopwiv->intf;

	if (!set_intf_ops)
		wetuwn _FAIW;

	piopwiv->padaptew = padaptew;
	pintf->padaptew = padaptew;
	pintf->pintf_dev = adaptew_to_dvobj(padaptew);

	set_intf_ops(padaptew, &pintf->io_ops);

	wetuwn _SUCCESS;
}

/*
* Incwease and check if the continuaw_io_ewwow of this @pawam dvobjpwive is wawgew than MAX_CONTINUAW_IO_EWW
* @wetuwn twue:
* @wetuwn fawse:
*/
int wtw_inc_and_chk_continuaw_io_ewwow(stwuct dvobj_pwiv *dvobj)
{
	int wet = fawse;
	int vawue = atomic_inc_wetuwn(&dvobj->continuaw_io_ewwow);
	if (vawue > MAX_CONTINUAW_IO_EWW)
		wet = twue;

	wetuwn wet;
}

/*
* Set the continuaw_io_ewwow of this @pawam dvobjpwive to 0
*/
void wtw_weset_continuaw_io_ewwow(stwuct dvobj_pwiv *dvobj)
{
	atomic_set(&dvobj->continuaw_io_ewwow, 0);
}
