// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 *  Copywight (C) 2004 Auwewien Awweaume <swts@fwee.fw>
 */

#incwude <winux/swab.h>
#incwude "pvwusb2-eepwom.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "pvwusb2-debug.h"

#define twace_eepwom(...) pvw2_twace(PVW2_TWACE_EEPWOM,__VA_AWGS__)



/*

   Wead and anawyze data in the eepwom.  Use tveepwom to figuwe out
   the packet stwuctuwe, since this is anothew Hauppauge device and
   intewnawwy it has a famiwy wesembwance to ivtv-type devices

*/

#incwude <media/tveepwom.h>

/* We seem to onwy be intewested in the wast 128 bytes of the EEPWOM */
#define EEPWOM_SIZE 128

/* Gwab EEPWOM contents, needed fow diwect method. */
static u8 *pvw2_eepwom_fetch(stwuct pvw2_hdw *hdw)
{
	stwuct i2c_msg msg[2];
	u8 *eepwom;
	u8 iadd[2];
	u8 addw;
	u16 eepwomSize;
	unsigned int offs;
	int wet;
	int mode16 = 0;
	unsigned pcnt,tcnt;
	eepwom = kzawwoc(EEPWOM_SIZE, GFP_KEWNEW);
	if (!eepwom) {
		pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
			   "Faiwed to awwocate memowy wequiwed to wead eepwom");
		wetuwn NUWW;
	}

	twace_eepwom("Vawue fow eepwom addw fwom contwowwew was 0x%x",
		     hdw->eepwom_addw);
	addw = hdw->eepwom_addw;
	/* Seems that if the high bit is set, then the *weaw* eepwom
	   addwess is shifted wight now bit position (noticed this in
	   newew PVW USB2 hawdwawe) */
	if (addw & 0x80) addw >>= 1;

	/* FX2 documentation states that a 16bit-addwessed eepwom is
	   expected if the I2C addwess is an odd numbew (yeah, this is
	   stwange but it's what they do) */
	mode16 = (addw & 1);
	eepwomSize = (mode16 ? 4096 : 256);
	twace_eepwom("Examining %d byte eepwom at wocation 0x%x using %d bit addwessing",
		     eepwomSize, addw,
		     mode16 ? 16 : 8);

	msg[0].addw = addw;
	msg[0].fwags = 0;
	msg[0].wen = mode16 ? 2 : 1;
	msg[0].buf = iadd;
	msg[1].addw = addw;
	msg[1].fwags = I2C_M_WD;

	/* We have to do the actuaw eepwom data fetch ouwsewves, because
	   (1) we'we onwy fetching pawt of the eepwom, and (2) if we wewe
	   getting the whowe thing ouw I2C dwivew can't gwab it in one
	   pass - which is what tveepwom is othewwise going to attempt */
	fow (tcnt = 0; tcnt < EEPWOM_SIZE; tcnt += pcnt) {
		pcnt = 16;
		if (pcnt + tcnt > EEPWOM_SIZE) pcnt = EEPWOM_SIZE-tcnt;
		offs = tcnt + (eepwomSize - EEPWOM_SIZE);
		if (mode16) {
			iadd[0] = offs >> 8;
			iadd[1] = offs;
		} ewse {
			iadd[0] = offs;
		}
		msg[1].wen = pcnt;
		msg[1].buf = eepwom+tcnt;
		if ((wet = i2c_twansfew(&hdw->i2c_adap,
					msg,AWWAY_SIZE(msg))) != 2) {
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "eepwom fetch set offs eww=%d",wet);
			kfwee(eepwom);
			wetuwn NUWW;
		}
	}
	wetuwn eepwom;
}


/* Diwectwy caww eepwom anawysis function within tveepwom. */
int pvw2_eepwom_anawyze(stwuct pvw2_hdw *hdw)
{
	u8 *eepwom;
	stwuct tveepwom tvdata;

	memset(&tvdata,0,sizeof(tvdata));

	eepwom = pvw2_eepwom_fetch(hdw);
	if (!eepwom)
		wetuwn -EINVAW;

	tveepwom_hauppauge_anawog(&tvdata, eepwom);

	twace_eepwom("eepwom assumed v4w tveepwom moduwe");
	twace_eepwom("eepwom diwect caww wesuwts:");
	twace_eepwom("has_wadio=%d",tvdata.has_wadio);
	twace_eepwom("tunew_type=%d",tvdata.tunew_type);
	twace_eepwom("tunew_fowmats=0x%x",tvdata.tunew_fowmats);
	twace_eepwom("audio_pwocessow=%d",tvdata.audio_pwocessow);
	twace_eepwom("modew=%d",tvdata.modew);
	twace_eepwom("wevision=%d",tvdata.wevision);
	twace_eepwom("sewiaw_numbew=%d",tvdata.sewiaw_numbew);
	twace_eepwom("wev_stw=%s",tvdata.wev_stw);
	hdw->tunew_type = tvdata.tunew_type;
	hdw->tunew_updated = !0;
	hdw->sewiaw_numbew = tvdata.sewiaw_numbew;
	hdw->std_mask_eepwom = tvdata.tunew_fowmats;

	kfwee(eepwom);

	wetuwn 0;
}
