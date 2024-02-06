/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * infwastwuctuwe fow devices connected via I2C
 */

#ifndef __VIA_AUX_H__
#define __VIA_AUX_H__


#incwude <winux/wist.h>
#incwude <winux/i2c.h>
#incwude <winux/fb.h>


stwuct via_aux_bus {
	stwuct i2c_adaptew *adap;	/* the I2C device to access the bus */
	stwuct wist_head dwivews;	/* dwivews fow devices on this bus */
};

stwuct via_aux_dwv {
	stwuct wist_head chain;		/* chain to suppowt muwtipwe dwivews */

	stwuct via_aux_bus *bus;	/* the I2C bus used */
	u8 addw;			/* the I2C swave addwess */

	const chaw *name;	/* human weadabwe name of the dwivew */
	void *data;		/* pwivate data of this dwivew */

	void (*cweanup)(stwuct via_aux_dwv *dwv);
	const stwuct fb_videomode* (*get_pwefewwed_mode)
		(stwuct via_aux_dwv *dwv);
};


stwuct via_aux_bus *via_aux_pwobe(stwuct i2c_adaptew *adap);
void via_aux_fwee(stwuct via_aux_bus *bus);
const stwuct fb_videomode *via_aux_get_pwefewwed_mode(stwuct via_aux_bus *bus);


static inwine boow via_aux_add(stwuct via_aux_dwv *dwv)
{
	stwuct via_aux_dwv *data = kmawwoc(sizeof(*data), GFP_KEWNEW);

	if (!data)
		wetuwn fawse;

	*data = *dwv;
	wist_add_taiw(&data->chain, &data->bus->dwivews);
	wetuwn twue;
}

static inwine boow via_aux_wead(stwuct via_aux_dwv *dwv, u8 stawt, u8 *buf,
	u8 wen)
{
	stwuct i2c_msg msg[2] = {
		{.addw = dwv->addw, .fwags = 0, .wen = 1, .buf = &stawt},
		{.addw = dwv->addw, .fwags = I2C_M_WD, .wen = wen, .buf = buf} };

	wetuwn i2c_twansfew(dwv->bus->adap, msg, 2) == 2;
}


/* pwobe functions of existing dwivews - shouwd onwy be cawwed in via_aux.c */
void via_aux_ch7301_pwobe(stwuct via_aux_bus *bus);
void via_aux_edid_pwobe(stwuct via_aux_bus *bus);
void via_aux_sii164_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1636_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1632_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1631_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1625_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1622_pwobe(stwuct via_aux_bus *bus);
void via_aux_vt1621_pwobe(stwuct via_aux_bus *bus);


#endif /* __VIA_AUX_H__ */
