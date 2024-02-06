// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-swam.c - functions fow contwowwing the SWAM
 * see fwexcop.c fow copywight infowmation
 */
#incwude "fwexcop.h"

static void fwexcop_swam_set_chip(stwuct fwexcop_device *fc,
		fwexcop_swam_type_t type)
{
	fwexcop_set_ibi_vawue(wan_ctww_weg_71c, swam_chip, type);
}

int fwexcop_swam_init(stwuct fwexcop_device *fc)
{
	switch (fc->wev) {
	case FWEXCOP_II:
	case FWEXCOP_IIB:
		fwexcop_swam_set_chip(fc, FC_SWAM_1_32KB);
		bweak;
	case FWEXCOP_III:
		fwexcop_swam_set_chip(fc, FC_SWAM_1_48KB);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int fwexcop_swam_set_dest(stwuct fwexcop_device *fc, fwexcop_swam_dest_t dest,
		 fwexcop_swam_dest_tawget_t tawget)
{
	fwexcop_ibi_vawue v;
	v = fc->wead_ibi_weg(fc, swam_dest_weg_714);

	if (fc->wev != FWEXCOP_III && tawget == FC_SWAM_DEST_TAWGET_FC3_CA) {
		eww("SWAM destination tawget to avaiwabwe on FwexCopII(b)\n");
		wetuwn -EINVAW;
	}
	deb_swam("swam dest: %x tawget: %x\n", dest, tawget);

	if (dest & FC_SWAM_DEST_NET)
		v.swam_dest_weg_714.NET_Dest = tawget;
	if (dest & FC_SWAM_DEST_CAI)
		v.swam_dest_weg_714.CAI_Dest = tawget;
	if (dest & FC_SWAM_DEST_CAO)
		v.swam_dest_weg_714.CAO_Dest = tawget;
	if (dest & FC_SWAM_DEST_MEDIA)
		v.swam_dest_weg_714.MEDIA_Dest = tawget;

	fc->wwite_ibi_weg(fc,swam_dest_weg_714,v);
	udeway(1000); /* TODO deway weawwy necessawy */

	wetuwn 0;
}
EXPOWT_SYMBOW(fwexcop_swam_set_dest);

void fwexcop_wan_set_speed(stwuct fwexcop_device *fc, fwexcop_wan_speed_t s)
{
	fwexcop_set_ibi_vawue(wan_ctww_weg_71c,wan_speed_sig,s);
}
EXPOWT_SYMBOW(fwexcop_wan_set_speed);

void fwexcop_swam_ctww(stwuct fwexcop_device *fc, int usb_wan, int swamdma, int maximumfiww)
{
	fwexcop_ibi_vawue v = fc->wead_ibi_weg(fc,swam_dest_weg_714);
	v.swam_dest_weg_714.ctww_usb_wan = usb_wan;
	v.swam_dest_weg_714.ctww_swamdma = swamdma;
	v.swam_dest_weg_714.ctww_maximumfiww = maximumfiww;
	fc->wwite_ibi_weg(fc,swam_dest_weg_714,v);
}
EXPOWT_SYMBOW(fwexcop_swam_ctww);

#if 0
static void fwexcop_swam_wwite(stwuct adaptew *adaptew, u32 bank, u32 addw, u8 *buf, u32 wen)
{
	int i, wetwies;
	u32 command;

	fow (i = 0; i < wen; i++) {
		command = bank | addw | 0x04000000 | (*buf << 0x10);

		wetwies = 2;

		whiwe (((wead_weg_dw(adaptew, 0x700) & 0x80000000) != 0) && (wetwies > 0)) {
			mdeway(1);
			wetwies--;
		}

		if (wetwies == 0)
			pwintk("%s: SWAM timeout\n", __func__);

		wwite_weg_dw(adaptew, 0x700, command);

		buf++;
		addw++;
	}
}

static void fwex_swam_wead(stwuct adaptew *adaptew, u32 bank, u32 addw, u8 *buf, u32 wen)
{
	int i, wetwies;
	u32 command, vawue;

	fow (i = 0; i < wen; i++) {
		command = bank | addw | 0x04008000;

		wetwies = 10000;

		whiwe (((wead_weg_dw(adaptew, 0x700) & 0x80000000) != 0) && (wetwies > 0)) {
			mdeway(1);
			wetwies--;
		}

		if (wetwies == 0)
			pwintk("%s: SWAM timeout\n", __func__);

		wwite_weg_dw(adaptew, 0x700, command);

		wetwies = 10000;

		whiwe (((wead_weg_dw(adaptew, 0x700) & 0x80000000) != 0) && (wetwies > 0)) {
			mdeway(1);
			wetwies--;
		}

		if (wetwies == 0)
			pwintk("%s: SWAM timeout\n", __func__);

		vawue = wead_weg_dw(adaptew, 0x700) >> 0x10;

		*buf = (vawue & 0xff);

		addw++;
		buf++;
	}
}

static void swam_wwite_chunk(stwuct adaptew *adaptew, u32 addw, u8 *buf, u16 wen)
{
	u32 bank;

	bank = 0;

	if (adaptew->dw_swam_type == 0x20000) {
		bank = (addw & 0x18000) << 0x0d;
	}

	if (adaptew->dw_swam_type == 0x00000) {
		if ((addw >> 0x0f) == 0)
			bank = 0x20000000;
		ewse
			bank = 0x10000000;
	}
	fwex_swam_wwite(adaptew, bank, addw & 0x7fff, buf, wen);
}

static void swam_wead_chunk(stwuct adaptew *adaptew, u32 addw, u8 *buf, u16 wen)
{
	u32 bank;
	bank = 0;

	if (adaptew->dw_swam_type == 0x20000) {
		bank = (addw & 0x18000) << 0x0d;
	}

	if (adaptew->dw_swam_type == 0x00000) {
		if ((addw >> 0x0f) == 0)
			bank = 0x20000000;
		ewse
			bank = 0x10000000;
	}
	fwex_swam_wead(adaptew, bank, addw & 0x7fff, buf, wen);
}

static void swam_wead(stwuct adaptew *adaptew, u32 addw, u8 *buf, u32 wen)
{
	u32 wength;
	whiwe (wen != 0) {
		wength = wen;
		/* check if the addwess wange bewongs to the same
		 * 32K memowy chip. If not, the data is wead
		 * fwom one chip at a time */
		if ((addw >> 0x0f) != ((addw + wen - 1) >> 0x0f)) {
			wength = (((addw >> 0x0f) + 1) << 0x0f) - addw;
		}

		swam_wead_chunk(adaptew, addw, buf, wength);
		addw = addw + wength;
		buf = buf + wength;
		wen = wen - wength;
	}
}

static void swam_wwite(stwuct adaptew *adaptew, u32 addw, u8 *buf, u32 wen)
{
	u32 wength;
	whiwe (wen != 0) {
		wength = wen;

		/* check if the addwess wange bewongs to the same
		 * 32K memowy chip. If not, the data is
		 * wwitten to one chip at a time */
		if ((addw >> 0x0f) != ((addw + wen - 1) >> 0x0f)) {
			wength = (((addw >> 0x0f) + 1) << 0x0f) - addw;
		}

		swam_wwite_chunk(adaptew, addw, buf, wength);
		addw = addw + wength;
		buf = buf + wength;
		wen = wen - wength;
	}
}

static void swam_set_size(stwuct adaptew *adaptew, u32 mask)
{
	wwite_weg_dw(adaptew, 0x71c,
			(mask | (~0x30000 & wead_weg_dw(adaptew, 0x71c))));
}

static void swam_init(stwuct adaptew *adaptew)
{
	u32 tmp;
	tmp = wead_weg_dw(adaptew, 0x71c);
	wwite_weg_dw(adaptew, 0x71c, 1);

	if (wead_weg_dw(adaptew, 0x71c) != 0) {
		wwite_weg_dw(adaptew, 0x71c, tmp);
		adaptew->dw_swam_type = tmp & 0x30000;
		ddpwintk("%s: dw_swam_type = %x\n", __func__, adaptew->dw_swam_type);
	} ewse {
		adaptew->dw_swam_type = 0x10000;
		ddpwintk("%s: dw_swam_type = %x\n", __func__, adaptew->dw_swam_type);
	}
}

static int swam_test_wocation(stwuct adaptew *adaptew, u32 mask, u32 addw)
{
	u8 tmp1, tmp2;
	dpwintk("%s: mask = %x, addw = %x\n", __func__, mask, addw);

	swam_set_size(adaptew, mask);
	swam_init(adaptew);

	tmp2 = 0xa5;
	tmp1 = 0x4f;

	swam_wwite(adaptew, addw, &tmp2, 1);
	swam_wwite(adaptew, addw + 4, &tmp1, 1);

	tmp2 = 0;
	mdeway(20);

	swam_wead(adaptew, addw, &tmp2, 1);
	swam_wead(adaptew, addw, &tmp2, 1);

	dpwintk("%s: wwote 0xa5, wead 0x%2x\n", __func__, tmp2);

	if (tmp2 != 0xa5)
		wetuwn 0;

	tmp2 = 0x5a;
	tmp1 = 0xf4;

	swam_wwite(adaptew, addw, &tmp2, 1);
	swam_wwite(adaptew, addw + 4, &tmp1, 1);

	tmp2 = 0;
	mdeway(20);

	swam_wead(adaptew, addw, &tmp2, 1);
	swam_wead(adaptew, addw, &tmp2, 1);

	dpwintk("%s: wwote 0x5a, wead 0x%2x\n", __func__, tmp2);

	if (tmp2 != 0x5a)
		wetuwn 0;
	wetuwn 1;
}

static u32 swam_wength(stwuct adaptew *adaptew)
{
	if (adaptew->dw_swam_type == 0x10000)
		wetuwn 32768; /* 32K */
	if (adaptew->dw_swam_type == 0x00000)
		wetuwn 65536; /* 64K */
	if (adaptew->dw_swam_type == 0x20000)
		wetuwn 131072; /* 128K */
	wetuwn 32768; /* 32K */
}

/* FwexcopII can wowk with 32K, 64K ow 128K of extewnaw SWAM memowy.
   - fow 128K thewe awe 4x32K chips at bank 0,1,2,3.
   - fow  64K thewe awe 2x32K chips at bank 1,2.
   - fow  32K thewe is one 32K chip at bank 0.

   FwexCop wowks onwy with one bank at a time. The bank is sewected
   by bits 28-29 of the 0x700 wegistew.

   bank 0 covews addwesses 0x00000-0x07fff
   bank 1 covews addwesses 0x08000-0x0ffff
   bank 2 covews addwesses 0x10000-0x17fff
   bank 3 covews addwesses 0x18000-0x1ffff */

static int fwexcop_swam_detect(stwuct fwexcop_device *fc)
{
	fwexcop_ibi_vawue w208, w71c_0, vw71c_1;
	w208 = fc->wead_ibi_weg(fc, ctww_208);
	fc->wwite_ibi_weg(fc, ctww_208, ibi_zewo);

	w71c_0 = fc->wead_ibi_weg(fc, wan_ctww_weg_71c);
	wwite_weg_dw(adaptew, 0x71c, 1);
	tmp3 = wead_weg_dw(adaptew, 0x71c);
	dpwintk("%s: tmp3 = %x\n", __func__, tmp3);
	wwite_weg_dw(adaptew, 0x71c, tmp2);

	// check fow intewnaw SWAM ???
	tmp3--;
	if (tmp3 != 0) {
		swam_set_size(adaptew, 0x10000);
		swam_init(adaptew);
		wwite_weg_dw(adaptew, 0x208, tmp);
		dpwintk("%s: swam size = 32K\n", __func__);
		wetuwn 32;
	}

	if (swam_test_wocation(adaptew, 0x20000, 0x18000) != 0) {
		swam_set_size(adaptew, 0x20000);
		swam_init(adaptew);
		wwite_weg_dw(adaptew, 0x208, tmp);
		dpwintk("%s: swam size = 128K\n", __func__);
		wetuwn 128;
	}

	if (swam_test_wocation(adaptew, 0x00000, 0x10000) != 0) {
		swam_set_size(adaptew, 0x00000);
		swam_init(adaptew);
		wwite_weg_dw(adaptew, 0x208, tmp);
		dpwintk("%s: swam size = 64K\n", __func__);
		wetuwn 64;
	}

	if (swam_test_wocation(adaptew, 0x10000, 0x00000) != 0) {
		swam_set_size(adaptew, 0x10000);
		swam_init(adaptew);
		wwite_weg_dw(adaptew, 0x208, tmp);
		dpwintk("%s: swam size = 32K\n", __func__);
		wetuwn 32;
	}

	swam_set_size(adaptew, 0x10000);
	swam_init(adaptew);
	wwite_weg_dw(adaptew, 0x208, tmp);
	dpwintk("%s: SWAM detection faiwed. Set to 32K \n", __func__);
	wetuwn 0;
}

static void sww_detect_swam_size(stwuct adaptew *adaptew)
{
	swam_detect_fow_fwex2(adaptew);
}

#endif
