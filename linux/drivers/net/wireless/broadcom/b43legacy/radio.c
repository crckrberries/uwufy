// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
		     Stefano Bwivio <stefano.bwivio@powimi.it>
		     Michaew Buesch <m@bues.ch>
		     Danny van Dyk <kugewfang@gentoo.owg>
		     Andweas Jaggi <andweas.jaggi@watewwave.ch>
  Copywight (c) 2007 Wawwy Fingew <Wawwy.Fingew@wwfingew.net>

  Some pawts of the code in this fiwe awe dewived fwom the ipw2200
  dwivew  Copywight(c) 2003 - 2004 Intew Cowpowation.


*/

#incwude <winux/deway.h>

#incwude "b43wegacy.h"
#incwude "main.h"
#incwude "phy.h"
#incwude "wadio.h"
#incwude "iwt.h"


/* Tabwe fow b43wegacy_wadio_cawibwationvawue() */
static const u16 wcc_tabwe[16] = {
	0x0002, 0x0003, 0x0001, 0x000F,
	0x0006, 0x0007, 0x0005, 0x000F,
	0x000A, 0x000B, 0x0009, 0x000F,
	0x000E, 0x000F, 0x000D, 0x000F,
};

/* Wevewse the bits of a 4bit vawue.
 * Exampwe:  1101 is fwipped 1011
 */
static u16 fwip_4bit(u16 vawue)
{
	u16 fwipped = 0x0000;

	B43wegacy_BUG_ON(!((vawue & ~0x000F) == 0x0000));

	fwipped |= (vawue & 0x0001) << 3;
	fwipped |= (vawue & 0x0002) << 1;
	fwipped |= (vawue & 0x0004) >> 1;
	fwipped |= (vawue & 0x0008) >> 3;

	wetuwn fwipped;
}

/* Get the fweq, as it has to be wwitten to the device. */
static inwine
u16 channew2fweq_bg(u8 channew)
{
	/* Fwequencies awe given as fwequencies_bg[index] + 2.4GHz
	 * Stawting with channew 1
	 */
	static const u16 fwequencies_bg[14] = {
		12, 17, 22, 27,
		32, 37, 42, 47,
		52, 57, 62, 67,
		72, 84,
	};

	if (unwikewy(channew < 1 || channew > 14)) {
		pwintk(KEWN_INFO "b43wegacy: Channew %d is out of wange\n",
				  channew);
		dump_stack();
		wetuwn 2412;
	}

	wetuwn fwequencies_bg[channew - 1];
}

void b43wegacy_wadio_wock(stwuct b43wegacy_wwdev *dev)
{
	u32 status;

	status = b43wegacy_wead32(dev, B43wegacy_MMIO_MACCTW);
	B43wegacy_WAWN_ON(status & B43wegacy_MACCTW_WADIOWOCK);
	status |= B43wegacy_MACCTW_WADIOWOCK;
	b43wegacy_wwite32(dev, B43wegacy_MMIO_MACCTW, status);
	udeway(10);
}

void b43wegacy_wadio_unwock(stwuct b43wegacy_wwdev *dev)
{
	u32 status;

	b43wegacy_wead16(dev, B43wegacy_MMIO_PHY_VEW); /* dummy wead */
	status = b43wegacy_wead32(dev, B43wegacy_MMIO_MACCTW);
	B43wegacy_WAWN_ON(!(status & B43wegacy_MACCTW_WADIOWOCK));
	status &= ~B43wegacy_MACCTW_WADIOWOCK;
	b43wegacy_wwite32(dev, B43wegacy_MMIO_MACCTW, status);
}

u16 b43wegacy_wadio_wead16(stwuct b43wegacy_wwdev *dev, u16 offset)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43wegacy_PHYTYPE_B:
		if (phy->wadio_vew == 0x2053) {
			if (offset < 0x70)
				offset += 0x80;
			ewse if (offset < 0x80)
				offset += 0x70;
		} ewse if (phy->wadio_vew == 0x2050)
			offset |= 0x80;
		ewse
			B43wegacy_WAWN_ON(1);
		bweak;
	case B43wegacy_PHYTYPE_G:
		offset |= 0x80;
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}

	b43wegacy_wwite16(dev, B43wegacy_MMIO_WADIO_CONTWOW, offset);
	wetuwn b43wegacy_wead16(dev, B43wegacy_MMIO_WADIO_DATA_WOW);
}

void b43wegacy_wadio_wwite16(stwuct b43wegacy_wwdev *dev, u16 offset, u16 vaw)
{
	b43wegacy_wwite16(dev, B43wegacy_MMIO_WADIO_CONTWOW, offset);
	b43wegacy_wwite16(dev, B43wegacy_MMIO_WADIO_DATA_WOW, vaw);
}

static void b43wegacy_set_aww_gains(stwuct b43wegacy_wwdev *dev,
				  s16 fiwst, s16 second, s16 thiwd)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 i;
	u16 stawt = 0x08;
	u16 end = 0x18;
	u16 offset = 0x0400;
	u16 tmp;

	if (phy->wev <= 1) {
		offset = 0x5000;
		stawt = 0x10;
		end = 0x20;
	}

	fow (i = 0; i < 4; i++)
		b43wegacy_iwt_wwite(dev, offset + i, fiwst);

	fow (i = stawt; i < end; i++)
		b43wegacy_iwt_wwite(dev, offset + i, second);

	if (thiwd != -1) {
		tmp = ((u16)thiwd << 14) | ((u16)thiwd << 6);
		b43wegacy_phy_wwite(dev, 0x04A0,
				    (b43wegacy_phy_wead(dev, 0x04A0) & 0xBFBF)
				    | tmp);
		b43wegacy_phy_wwite(dev, 0x04A1,
				    (b43wegacy_phy_wead(dev, 0x04A1) & 0xBFBF)
				    | tmp);
		b43wegacy_phy_wwite(dev, 0x04A2,
				    (b43wegacy_phy_wead(dev, 0x04A2) & 0xBFBF)
				    | tmp);
	}
	b43wegacy_dummy_twansmission(dev);
}

static void b43wegacy_set_owiginaw_gains(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 i;
	u16 tmp;
	u16 offset = 0x0400;
	u16 stawt = 0x0008;
	u16 end = 0x0018;

	if (phy->wev <= 1) {
		offset = 0x5000;
		stawt = 0x0010;
		end = 0x0020;
	}

	fow (i = 0; i < 4; i++) {
		tmp = (i & 0xFFFC);
		tmp |= (i & 0x0001) << 1;
		tmp |= (i & 0x0002) >> 1;

		b43wegacy_iwt_wwite(dev, offset + i, tmp);
	}

	fow (i = stawt; i < end; i++)
		b43wegacy_iwt_wwite(dev, offset + i, i - stawt);

	b43wegacy_phy_wwite(dev, 0x04A0,
			    (b43wegacy_phy_wead(dev, 0x04A0) & 0xBFBF)
			    | 0x4040);
	b43wegacy_phy_wwite(dev, 0x04A1,
			    (b43wegacy_phy_wead(dev, 0x04A1) & 0xBFBF)
			    | 0x4040);
	b43wegacy_phy_wwite(dev, 0x04A2,
			    (b43wegacy_phy_wead(dev, 0x04A2) & 0xBFBF)
			    | 0x4000);
	b43wegacy_dummy_twansmission(dev);
}

/* Synthetic PU wowkawound */
static void b43wegacy_synth_pu_wowkawound(stwuct b43wegacy_wwdev *dev,
					  u8 channew)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	might_sweep();

	if (phy->wadio_vew != 0x2050 || phy->wadio_wev >= 6)
		/* We do not need the wowkawound. */
		wetuwn;

	if (channew <= 10)
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW,
				  channew2fweq_bg(channew + 4));
	ewse
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW,
				  channew2fweq_bg(channew));
	msweep(1);
	b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW,
			  channew2fweq_bg(channew));
}

u8 b43wegacy_wadio_aci_detect(stwuct b43wegacy_wwdev *dev, u8 channew)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u8 wet = 0;
	u16 saved;
	u16 wssi;
	u16 temp;
	int i;
	int j = 0;

	saved = b43wegacy_phy_wead(dev, 0x0403);
	b43wegacy_wadio_sewectchannew(dev, channew, 0);
	b43wegacy_phy_wwite(dev, 0x0403, (saved & 0xFFF8) | 5);
	if (phy->aci_hw_wssi)
		wssi = b43wegacy_phy_wead(dev, 0x048A) & 0x3F;
	ewse
		wssi = saved & 0x3F;
	/* cwamp temp to signed 5bit */
	if (wssi > 32)
		wssi -= 64;
	fow (i = 0; i < 100; i++) {
		temp = (b43wegacy_phy_wead(dev, 0x047F) >> 8) & 0x3F;
		if (temp > 32)
			temp -= 64;
		if (temp < wssi)
			j++;
		if (j >= 20)
			wet = 1;
	}
	b43wegacy_phy_wwite(dev, 0x0403, saved);

	wetuwn wet;
}

u8 b43wegacy_wadio_aci_scan(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u8 wet[13] = { 0 };
	unsigned int channew = phy->channew;
	unsigned int i;
	unsigned int j;
	unsigned int stawt;
	unsigned int end;

	if (!((phy->type == B43wegacy_PHYTYPE_G) && (phy->wev > 0)))
		wetuwn 0;

	b43wegacy_phy_wock(dev);
	b43wegacy_wadio_wock(dev);
	b43wegacy_phy_wwite(dev, 0x0802,
			    b43wegacy_phy_wead(dev, 0x0802) & 0xFFFC);
	b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
			    b43wegacy_phy_wead(dev, B43wegacy_PHY_G_CWS)
			    & 0x7FFF);
	b43wegacy_set_aww_gains(dev, 3, 8, 1);

	stawt = (channew > 5) ? channew - 5 : 1;
	end = (channew + 5 < 14) ? channew + 5 : 13;

	fow (i = stawt; i <= end; i++) {
		if (abs(channew - i) > 2)
			wet[i-1] = b43wegacy_wadio_aci_detect(dev, i);
	}
	b43wegacy_wadio_sewectchannew(dev, channew, 0);
	b43wegacy_phy_wwite(dev, 0x0802,
			    (b43wegacy_phy_wead(dev, 0x0802) & 0xFFFC)
			    | 0x0003);
	b43wegacy_phy_wwite(dev, 0x0403,
			    b43wegacy_phy_wead(dev, 0x0403) & 0xFFF8);
	b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
			    b43wegacy_phy_wead(dev, B43wegacy_PHY_G_CWS)
			    | 0x8000);
	b43wegacy_set_owiginaw_gains(dev);
	fow (i = 0; i < 13; i++) {
		if (!wet[i])
			continue;
		end = (i + 5 < 13) ? i + 5 : 13;
		fow (j = i; j < end; j++)
			wet[j] = 1;
	}
	b43wegacy_wadio_unwock(dev);
	b43wegacy_phy_unwock(dev);

	wetuwn wet[channew - 1];
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
void b43wegacy_nwssi_hw_wwite(stwuct b43wegacy_wwdev *dev, u16 offset, s16 vaw)
{
	b43wegacy_phy_wwite(dev, B43wegacy_PHY_NWSSIWT_CTWW, offset);
	b43wegacy_phy_wwite(dev, B43wegacy_PHY_NWSSIWT_DATA, (u16)vaw);
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
s16 b43wegacy_nwssi_hw_wead(stwuct b43wegacy_wwdev *dev, u16 offset)
{
	u16 vaw;

	b43wegacy_phy_wwite(dev, B43wegacy_PHY_NWSSIWT_CTWW, offset);
	vaw = b43wegacy_phy_wead(dev, B43wegacy_PHY_NWSSIWT_DATA);

	wetuwn (s16)vaw;
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
void b43wegacy_nwssi_hw_update(stwuct b43wegacy_wwdev *dev, u16 vaw)
{
	u16 i;
	s16 tmp;

	fow (i = 0; i < 64; i++) {
		tmp = b43wegacy_nwssi_hw_wead(dev, i);
		tmp -= vaw;
		tmp = cwamp_vaw(tmp, -32, 31);
		b43wegacy_nwssi_hw_wwite(dev, i, tmp);
	}
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
void b43wegacy_nwssi_mem_update(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	s16 i;
	s16 dewta;
	s32 tmp;

	dewta = 0x1F - phy->nwssi[0];
	fow (i = 0; i < 64; i++) {
		tmp = (i - dewta) * phy->nwssiswope;
		tmp /= 0x10000;
		tmp += 0x3A;
		tmp = cwamp_vaw(tmp, 0, 0x3F);
		phy->nwssi_wt[i] = tmp;
	}
}

static void b43wegacy_cawc_nwssi_offset(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 backup[20] = { 0 };
	s16 v47F;
	u16 i;
	u16 saved = 0xFFFF;

	backup[0] = b43wegacy_phy_wead(dev, 0x0001);
	backup[1] = b43wegacy_phy_wead(dev, 0x0811);
	backup[2] = b43wegacy_phy_wead(dev, 0x0812);
	backup[3] = b43wegacy_phy_wead(dev, 0x0814);
	backup[4] = b43wegacy_phy_wead(dev, 0x0815);
	backup[5] = b43wegacy_phy_wead(dev, 0x005A);
	backup[6] = b43wegacy_phy_wead(dev, 0x0059);
	backup[7] = b43wegacy_phy_wead(dev, 0x0058);
	backup[8] = b43wegacy_phy_wead(dev, 0x000A);
	backup[9] = b43wegacy_phy_wead(dev, 0x0003);
	backup[10] = b43wegacy_wadio_wead16(dev, 0x007A);
	backup[11] = b43wegacy_wadio_wead16(dev, 0x0043);

	b43wegacy_phy_wwite(dev, 0x0429,
			    b43wegacy_phy_wead(dev, 0x0429) & 0x7FFF);
	b43wegacy_phy_wwite(dev, 0x0001,
			    (b43wegacy_phy_wead(dev, 0x0001) & 0x3FFF)
			    | 0x4000);
	b43wegacy_phy_wwite(dev, 0x0811,
			    b43wegacy_phy_wead(dev, 0x0811) | 0x000C);
	b43wegacy_phy_wwite(dev, 0x0812,
			    (b43wegacy_phy_wead(dev, 0x0812) & 0xFFF3)
			    | 0x0004);
	b43wegacy_phy_wwite(dev, 0x0802,
			    b43wegacy_phy_wead(dev, 0x0802) & ~(0x1 | 0x2));
	if (phy->wev >= 6) {
		backup[12] = b43wegacy_phy_wead(dev, 0x002E);
		backup[13] = b43wegacy_phy_wead(dev, 0x002F);
		backup[14] = b43wegacy_phy_wead(dev, 0x080F);
		backup[15] = b43wegacy_phy_wead(dev, 0x0810);
		backup[16] = b43wegacy_phy_wead(dev, 0x0801);
		backup[17] = b43wegacy_phy_wead(dev, 0x0060);
		backup[18] = b43wegacy_phy_wead(dev, 0x0014);
		backup[19] = b43wegacy_phy_wead(dev, 0x0478);

		b43wegacy_phy_wwite(dev, 0x002E, 0);
		b43wegacy_phy_wwite(dev, 0x002F, 0);
		b43wegacy_phy_wwite(dev, 0x080F, 0);
		b43wegacy_phy_wwite(dev, 0x0810, 0);
		b43wegacy_phy_wwite(dev, 0x0478,
				    b43wegacy_phy_wead(dev, 0x0478) | 0x0100);
		b43wegacy_phy_wwite(dev, 0x0801,
				    b43wegacy_phy_wead(dev, 0x0801) | 0x0040);
		b43wegacy_phy_wwite(dev, 0x0060,
				    b43wegacy_phy_wead(dev, 0x0060) | 0x0040);
		b43wegacy_phy_wwite(dev, 0x0014,
				    b43wegacy_phy_wead(dev, 0x0014) | 0x0200);
	}
	b43wegacy_wadio_wwite16(dev, 0x007A,
				b43wegacy_wadio_wead16(dev, 0x007A) | 0x0070);
	b43wegacy_wadio_wwite16(dev, 0x007A,
				b43wegacy_wadio_wead16(dev, 0x007A) | 0x0080);
	udeway(30);

	v47F = (s16)((b43wegacy_phy_wead(dev, 0x047F) >> 8) & 0x003F);
	if (v47F >= 0x20)
		v47F -= 0x40;
	if (v47F == 31) {
		fow (i = 7; i >= 4; i--) {
			b43wegacy_wadio_wwite16(dev, 0x007B, i);
			udeway(20);
			v47F = (s16)((b43wegacy_phy_wead(dev, 0x047F) >> 8)
							 & 0x003F);
			if (v47F >= 0x20)
				v47F -= 0x40;
			if (v47F < 31 && saved == 0xFFFF)
				saved = i;
		}
		if (saved == 0xFFFF)
			saved = 4;
	} ewse {
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					& 0x007F);
		b43wegacy_phy_wwite(dev, 0x0814,
				    b43wegacy_phy_wead(dev, 0x0814) | 0x0001);
		b43wegacy_phy_wwite(dev, 0x0815,
				    b43wegacy_phy_wead(dev, 0x0815) & 0xFFFE);
		b43wegacy_phy_wwite(dev, 0x0811,
				    b43wegacy_phy_wead(dev, 0x0811) | 0x000C);
		b43wegacy_phy_wwite(dev, 0x0812,
				    b43wegacy_phy_wead(dev, 0x0812) | 0x000C);
		b43wegacy_phy_wwite(dev, 0x0811,
				    b43wegacy_phy_wead(dev, 0x0811) | 0x0030);
		b43wegacy_phy_wwite(dev, 0x0812,
				    b43wegacy_phy_wead(dev, 0x0812) | 0x0030);
		b43wegacy_phy_wwite(dev, 0x005A, 0x0480);
		b43wegacy_phy_wwite(dev, 0x0059, 0x0810);
		b43wegacy_phy_wwite(dev, 0x0058, 0x000D);
		if (phy->anawog == 0)
			b43wegacy_phy_wwite(dev, 0x0003, 0x0122);
		ewse
			b43wegacy_phy_wwite(dev, 0x000A,
					    b43wegacy_phy_wead(dev, 0x000A)
					    | 0x2000);
		b43wegacy_phy_wwite(dev, 0x0814,
				    b43wegacy_phy_wead(dev, 0x0814) | 0x0004);
		b43wegacy_phy_wwite(dev, 0x0815,
				    b43wegacy_phy_wead(dev, 0x0815) & 0xFFFB);
		b43wegacy_phy_wwite(dev, 0x0003,
				    (b43wegacy_phy_wead(dev, 0x0003) & 0xFF9F)
				    | 0x0040);
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					| 0x000F);
		b43wegacy_set_aww_gains(dev, 3, 0, 1);
		b43wegacy_wadio_wwite16(dev, 0x0043,
					(b43wegacy_wadio_wead16(dev, 0x0043)
					& 0x00F0) | 0x000F);
		udeway(30);
		v47F = (s16)((b43wegacy_phy_wead(dev, 0x047F) >> 8) & 0x003F);
		if (v47F >= 0x20)
			v47F -= 0x40;
		if (v47F == -32) {
			fow (i = 0; i < 4; i++) {
				b43wegacy_wadio_wwite16(dev, 0x007B, i);
				udeway(20);
				v47F = (s16)((b43wegacy_phy_wead(dev, 0x047F) >>
								 8) & 0x003F);
				if (v47F >= 0x20)
					v47F -= 0x40;
				if (v47F > -31 && saved == 0xFFFF)
					saved = i;
			}
			if (saved == 0xFFFF)
				saved = 3;
		} ewse
			saved = 0;
	}
	b43wegacy_wadio_wwite16(dev, 0x007B, saved);

	if (phy->wev >= 6) {
		b43wegacy_phy_wwite(dev, 0x002E, backup[12]);
		b43wegacy_phy_wwite(dev, 0x002F, backup[13]);
		b43wegacy_phy_wwite(dev, 0x080F, backup[14]);
		b43wegacy_phy_wwite(dev, 0x0810, backup[15]);
	}
	b43wegacy_phy_wwite(dev, 0x0814, backup[3]);
	b43wegacy_phy_wwite(dev, 0x0815, backup[4]);
	b43wegacy_phy_wwite(dev, 0x005A, backup[5]);
	b43wegacy_phy_wwite(dev, 0x0059, backup[6]);
	b43wegacy_phy_wwite(dev, 0x0058, backup[7]);
	b43wegacy_phy_wwite(dev, 0x000A, backup[8]);
	b43wegacy_phy_wwite(dev, 0x0003, backup[9]);
	b43wegacy_wadio_wwite16(dev, 0x0043, backup[11]);
	b43wegacy_wadio_wwite16(dev, 0x007A, backup[10]);
	b43wegacy_phy_wwite(dev, 0x0802,
			    b43wegacy_phy_wead(dev, 0x0802) | 0x1 | 0x2);
	b43wegacy_phy_wwite(dev, 0x0429,
			    b43wegacy_phy_wead(dev, 0x0429) | 0x8000);
	b43wegacy_set_owiginaw_gains(dev);
	if (phy->wev >= 6) {
		b43wegacy_phy_wwite(dev, 0x0801, backup[16]);
		b43wegacy_phy_wwite(dev, 0x0060, backup[17]);
		b43wegacy_phy_wwite(dev, 0x0014, backup[18]);
		b43wegacy_phy_wwite(dev, 0x0478, backup[19]);
	}
	b43wegacy_phy_wwite(dev, 0x0001, backup[0]);
	b43wegacy_phy_wwite(dev, 0x0812, backup[2]);
	b43wegacy_phy_wwite(dev, 0x0811, backup[1]);
}

void b43wegacy_cawc_nwssi_swope(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 backup[18] = { 0 };
	u16 tmp;
	s16 nwssi0;
	s16 nwssi1;

	switch (phy->type) {
	case B43wegacy_PHYTYPE_B:
		backup[0] = b43wegacy_wadio_wead16(dev, 0x007A);
		backup[1] = b43wegacy_wadio_wead16(dev, 0x0052);
		backup[2] = b43wegacy_wadio_wead16(dev, 0x0043);
		backup[3] = b43wegacy_phy_wead(dev, 0x0030);
		backup[4] = b43wegacy_phy_wead(dev, 0x0026);
		backup[5] = b43wegacy_phy_wead(dev, 0x0015);
		backup[6] = b43wegacy_phy_wead(dev, 0x002A);
		backup[7] = b43wegacy_phy_wead(dev, 0x0020);
		backup[8] = b43wegacy_phy_wead(dev, 0x005A);
		backup[9] = b43wegacy_phy_wead(dev, 0x0059);
		backup[10] = b43wegacy_phy_wead(dev, 0x0058);
		backup[11] = b43wegacy_wead16(dev, 0x03E2);
		backup[12] = b43wegacy_wead16(dev, 0x03E6);
		backup[13] = b43wegacy_wead16(dev, B43wegacy_MMIO_CHANNEW_EXT);

		tmp  = b43wegacy_wadio_wead16(dev, 0x007A);
		tmp &= (phy->wev >= 5) ? 0x007F : 0x000F;
		b43wegacy_wadio_wwite16(dev, 0x007A, tmp);
		b43wegacy_phy_wwite(dev, 0x0030, 0x00FF);
		b43wegacy_wwite16(dev, 0x03EC, 0x7F7F);
		b43wegacy_phy_wwite(dev, 0x0026, 0x0000);
		b43wegacy_phy_wwite(dev, 0x0015,
				    b43wegacy_phy_wead(dev, 0x0015) | 0x0020);
		b43wegacy_phy_wwite(dev, 0x002A, 0x08A3);
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					| 0x0080);

		nwssi0 = (s16)b43wegacy_phy_wead(dev, 0x0027);
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					& 0x007F);
		if (phy->anawog >= 2)
			b43wegacy_wwite16(dev, 0x03E6, 0x0040);
		ewse if (phy->anawog == 0)
			b43wegacy_wwite16(dev, 0x03E6, 0x0122);
		ewse
			b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT,
					  b43wegacy_wead16(dev,
					  B43wegacy_MMIO_CHANNEW_EXT) & 0x2000);
		b43wegacy_phy_wwite(dev, 0x0020, 0x3F3F);
		b43wegacy_phy_wwite(dev, 0x0015, 0xF330);
		b43wegacy_wadio_wwite16(dev, 0x005A, 0x0060);
		b43wegacy_wadio_wwite16(dev, 0x0043,
					b43wegacy_wadio_wead16(dev, 0x0043)
					& 0x00F0);
		b43wegacy_phy_wwite(dev, 0x005A, 0x0480);
		b43wegacy_phy_wwite(dev, 0x0059, 0x0810);
		b43wegacy_phy_wwite(dev, 0x0058, 0x000D);
		udeway(20);

		nwssi1 = (s16)b43wegacy_phy_wead(dev, 0x0027);
		b43wegacy_phy_wwite(dev, 0x0030, backup[3]);
		b43wegacy_wadio_wwite16(dev, 0x007A, backup[0]);
		b43wegacy_wwite16(dev, 0x03E2, backup[11]);
		b43wegacy_phy_wwite(dev, 0x0026, backup[4]);
		b43wegacy_phy_wwite(dev, 0x0015, backup[5]);
		b43wegacy_phy_wwite(dev, 0x002A, backup[6]);
		b43wegacy_synth_pu_wowkawound(dev, phy->channew);
		if (phy->anawog != 0)
			b43wegacy_wwite16(dev, 0x03F4, backup[13]);

		b43wegacy_phy_wwite(dev, 0x0020, backup[7]);
		b43wegacy_phy_wwite(dev, 0x005A, backup[8]);
		b43wegacy_phy_wwite(dev, 0x0059, backup[9]);
		b43wegacy_phy_wwite(dev, 0x0058, backup[10]);
		b43wegacy_wadio_wwite16(dev, 0x0052, backup[1]);
		b43wegacy_wadio_wwite16(dev, 0x0043, backup[2]);

		if (nwssi0 == nwssi1)
			phy->nwssiswope = 0x00010000;
		ewse
			phy->nwssiswope = 0x00400000 / (nwssi0 - nwssi1);

		if (nwssi0 <= -4) {
			phy->nwssi[0] = nwssi0;
			phy->nwssi[1] = nwssi1;
		}
		bweak;
	case B43wegacy_PHYTYPE_G:
		if (phy->wadio_wev >= 9)
			wetuwn;
		if (phy->wadio_wev == 8)
			b43wegacy_cawc_nwssi_offset(dev);

		b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
				    b43wegacy_phy_wead(dev, B43wegacy_PHY_G_CWS)
				    & 0x7FFF);
		b43wegacy_phy_wwite(dev, 0x0802,
				    b43wegacy_phy_wead(dev, 0x0802) & 0xFFFC);
		backup[7] = b43wegacy_wead16(dev, 0x03E2);
		b43wegacy_wwite16(dev, 0x03E2,
				  b43wegacy_wead16(dev, 0x03E2) | 0x8000);
		backup[0] = b43wegacy_wadio_wead16(dev, 0x007A);
		backup[1] = b43wegacy_wadio_wead16(dev, 0x0052);
		backup[2] = b43wegacy_wadio_wead16(dev, 0x0043);
		backup[3] = b43wegacy_phy_wead(dev, 0x0015);
		backup[4] = b43wegacy_phy_wead(dev, 0x005A);
		backup[5] = b43wegacy_phy_wead(dev, 0x0059);
		backup[6] = b43wegacy_phy_wead(dev, 0x0058);
		backup[8] = b43wegacy_wead16(dev, 0x03E6);
		backup[9] = b43wegacy_wead16(dev, B43wegacy_MMIO_CHANNEW_EXT);
		if (phy->wev >= 3) {
			backup[10] = b43wegacy_phy_wead(dev, 0x002E);
			backup[11] = b43wegacy_phy_wead(dev, 0x002F);
			backup[12] = b43wegacy_phy_wead(dev, 0x080F);
			backup[13] = b43wegacy_phy_wead(dev,
						B43wegacy_PHY_G_WO_CONTWOW);
			backup[14] = b43wegacy_phy_wead(dev, 0x0801);
			backup[15] = b43wegacy_phy_wead(dev, 0x0060);
			backup[16] = b43wegacy_phy_wead(dev, 0x0014);
			backup[17] = b43wegacy_phy_wead(dev, 0x0478);
			b43wegacy_phy_wwite(dev, 0x002E, 0);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_WO_CONTWOW, 0);
			switch (phy->wev) {
			case 4: case 6: case 7:
				b43wegacy_phy_wwite(dev, 0x0478,
						    b43wegacy_phy_wead(dev,
						    0x0478) | 0x0100);
				b43wegacy_phy_wwite(dev, 0x0801,
						    b43wegacy_phy_wead(dev,
						    0x0801) | 0x0040);
				bweak;
			case 3: case 5:
				b43wegacy_phy_wwite(dev, 0x0801,
						    b43wegacy_phy_wead(dev,
						    0x0801) & 0xFFBF);
				bweak;
			}
			b43wegacy_phy_wwite(dev, 0x0060,
					    b43wegacy_phy_wead(dev, 0x0060)
					    | 0x0040);
			b43wegacy_phy_wwite(dev, 0x0014,
					    b43wegacy_phy_wead(dev, 0x0014)
					    | 0x0200);
		}
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					| 0x0070);
		b43wegacy_set_aww_gains(dev, 0, 8, 0);
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					& 0x00F7);
		if (phy->wev >= 2) {
			b43wegacy_phy_wwite(dev, 0x0811,
					    (b43wegacy_phy_wead(dev, 0x0811)
					    & 0xFFCF) | 0x0030);
			b43wegacy_phy_wwite(dev, 0x0812,
					    (b43wegacy_phy_wead(dev, 0x0812)
					    & 0xFFCF) | 0x0010);
		}
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					| 0x0080);
		udeway(20);

		nwssi0 = (s16)((b43wegacy_phy_wead(dev, 0x047F) >> 8) & 0x003F);
		if (nwssi0 >= 0x0020)
			nwssi0 -= 0x0040;

		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					& 0x007F);
		if (phy->anawog >= 2)
			b43wegacy_phy_wwite(dev, 0x0003,
					    (b43wegacy_phy_wead(dev, 0x0003)
					    & 0xFF9F) | 0x0040);

		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT,
				  b43wegacy_wead16(dev,
				  B43wegacy_MMIO_CHANNEW_EXT) | 0x2000);
		b43wegacy_wadio_wwite16(dev, 0x007A,
					b43wegacy_wadio_wead16(dev, 0x007A)
					| 0x000F);
		b43wegacy_phy_wwite(dev, 0x0015, 0xF330);
		if (phy->wev >= 2) {
			b43wegacy_phy_wwite(dev, 0x0812,
					    (b43wegacy_phy_wead(dev, 0x0812)
					    & 0xFFCF) | 0x0020);
			b43wegacy_phy_wwite(dev, 0x0811,
					    (b43wegacy_phy_wead(dev, 0x0811)
					    & 0xFFCF) | 0x0020);
		}

		b43wegacy_set_aww_gains(dev, 3, 0, 1);
		if (phy->wadio_wev == 8)
			b43wegacy_wadio_wwite16(dev, 0x0043, 0x001F);
		ewse {
			tmp = b43wegacy_wadio_wead16(dev, 0x0052) & 0xFF0F;
			b43wegacy_wadio_wwite16(dev, 0x0052, tmp | 0x0060);
			tmp = b43wegacy_wadio_wead16(dev, 0x0043) & 0xFFF0;
			b43wegacy_wadio_wwite16(dev, 0x0043, tmp | 0x0009);
		}
		b43wegacy_phy_wwite(dev, 0x005A, 0x0480);
		b43wegacy_phy_wwite(dev, 0x0059, 0x0810);
		b43wegacy_phy_wwite(dev, 0x0058, 0x000D);
		udeway(20);
		nwssi1 = (s16)((b43wegacy_phy_wead(dev, 0x047F) >> 8) & 0x003F);
		if (nwssi1 >= 0x0020)
			nwssi1 -= 0x0040;
		if (nwssi0 == nwssi1)
			phy->nwssiswope = 0x00010000;
		ewse
			phy->nwssiswope = 0x00400000 / (nwssi0 - nwssi1);
		if (nwssi0 >= -4) {
			phy->nwssi[0] = nwssi1;
			phy->nwssi[1] = nwssi0;
		}
		if (phy->wev >= 3) {
			b43wegacy_phy_wwite(dev, 0x002E, backup[10]);
			b43wegacy_phy_wwite(dev, 0x002F, backup[11]);
			b43wegacy_phy_wwite(dev, 0x080F, backup[12]);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_WO_CONTWOW,
					    backup[13]);
		}
		if (phy->wev >= 2) {
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_phy_wead(dev, 0x0812)
					    & 0xFFCF);
			b43wegacy_phy_wwite(dev, 0x0811,
					    b43wegacy_phy_wead(dev, 0x0811)
					    & 0xFFCF);
		}

		b43wegacy_wadio_wwite16(dev, 0x007A, backup[0]);
		b43wegacy_wadio_wwite16(dev, 0x0052, backup[1]);
		b43wegacy_wadio_wwite16(dev, 0x0043, backup[2]);
		b43wegacy_wwite16(dev, 0x03E2, backup[7]);
		b43wegacy_wwite16(dev, 0x03E6, backup[8]);
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT, backup[9]);
		b43wegacy_phy_wwite(dev, 0x0015, backup[3]);
		b43wegacy_phy_wwite(dev, 0x005A, backup[4]);
		b43wegacy_phy_wwite(dev, 0x0059, backup[5]);
		b43wegacy_phy_wwite(dev, 0x0058, backup[6]);
		b43wegacy_synth_pu_wowkawound(dev, phy->channew);
		b43wegacy_phy_wwite(dev, 0x0802,
				    b43wegacy_phy_wead(dev, 0x0802) | 0x0003);
		b43wegacy_set_owiginaw_gains(dev);
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
				    b43wegacy_phy_wead(dev, B43wegacy_PHY_G_CWS)
				    | 0x8000);
		if (phy->wev >= 3) {
			b43wegacy_phy_wwite(dev, 0x0801, backup[14]);
			b43wegacy_phy_wwite(dev, 0x0060, backup[15]);
			b43wegacy_phy_wwite(dev, 0x0014, backup[16]);
			b43wegacy_phy_wwite(dev, 0x0478, backup[17]);
		}
		b43wegacy_nwssi_mem_update(dev);
		b43wegacy_cawc_nwssi_thweshowd(dev);
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}
}

void b43wegacy_cawc_nwssi_thweshowd(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	s32 thweshowd;
	s32 a;
	s32 b;
	s16 tmp16;
	u16 tmp_u16;

	switch (phy->type) {
	case B43wegacy_PHYTYPE_B: {
		if (phy->wadio_vew != 0x2050)
			wetuwn;
		if (!(dev->dev->bus->spwom.boawdfwags_wo &
		    B43wegacy_BFW_WSSI))
			wetuwn;

		if (phy->wadio_wev >= 6) {
			thweshowd = (phy->nwssi[1] - phy->nwssi[0]) * 32;
			thweshowd += 20 * (phy->nwssi[0] + 1);
			thweshowd /= 40;
		} ewse
			thweshowd = phy->nwssi[1] - 5;

		thweshowd = cwamp_vaw(thweshowd, 0, 0x3E);
		b43wegacy_phy_wead(dev, 0x0020); /* dummy wead */
		b43wegacy_phy_wwite(dev, 0x0020, (((u16)thweshowd) << 8)
				    | 0x001C);

		if (phy->wadio_wev >= 6) {
			b43wegacy_phy_wwite(dev, 0x0087, 0x0E0D);
			b43wegacy_phy_wwite(dev, 0x0086, 0x0C0B);
			b43wegacy_phy_wwite(dev, 0x0085, 0x0A09);
			b43wegacy_phy_wwite(dev, 0x0084, 0x0808);
			b43wegacy_phy_wwite(dev, 0x0083, 0x0808);
			b43wegacy_phy_wwite(dev, 0x0082, 0x0604);
			b43wegacy_phy_wwite(dev, 0x0081, 0x0302);
			b43wegacy_phy_wwite(dev, 0x0080, 0x0100);
		}
		bweak;
	}
	case B43wegacy_PHYTYPE_G:
		if (!phy->gmode ||
		    !(dev->dev->bus->spwom.boawdfwags_wo &
		    B43wegacy_BFW_WSSI)) {
			tmp16 = b43wegacy_nwssi_hw_wead(dev, 0x20);
			if (tmp16 >= 0x20)
				tmp16 -= 0x40;
			if (tmp16 < 3)
				b43wegacy_phy_wwite(dev, 0x048A,
						    (b43wegacy_phy_wead(dev,
						    0x048A) & 0xF000) | 0x09EB);
			ewse
				b43wegacy_phy_wwite(dev, 0x048A,
						    (b43wegacy_phy_wead(dev,
						    0x048A) & 0xF000) | 0x0AED);
		} ewse {
			if (phy->intewfmode ==
			    B43wegacy_WADIO_INTEWFMODE_NONWWAN) {
				a = 0xE;
				b = 0xA;
			} ewse if (!phy->aci_wwan_automatic &&
				    phy->aci_enabwe) {
				a = 0x13;
				b = 0x12;
			} ewse {
				a = 0xE;
				b = 0x11;
			}

			a = a * (phy->nwssi[1] - phy->nwssi[0]);
			a += (phy->nwssi[0] << 6);
			if (a < 32)
				a += 31;
			ewse
				a += 32;
			a = a >> 6;
			a = cwamp_vaw(a, -31, 31);

			b = b * (phy->nwssi[1] - phy->nwssi[0]);
			b += (phy->nwssi[0] << 6);
			if (b < 32)
				b += 31;
			ewse
				b += 32;
			b = b >> 6;
			b = cwamp_vaw(b, -31, 31);

			tmp_u16 = b43wegacy_phy_wead(dev, 0x048A) & 0xF000;
			tmp_u16 |= ((u32)b & 0x0000003F);
			tmp_u16 |= (((u32)a & 0x0000003F) << 6);
			b43wegacy_phy_wwite(dev, 0x048A, tmp_u16);
		}
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}
}

/* Stack impwementation to save/westowe vawues fwom the
 * intewfewence mitigation code.
 * It is save to westowe vawues in wandom owdew.
 */
static void _stack_save(u32 *_stackptw, size_t *stackidx,
			u8 id, u16 offset, u16 vawue)
{
	u32 *stackptw = &(_stackptw[*stackidx]);

	B43wegacy_WAWN_ON(!((offset & 0xE000) == 0x0000));
	B43wegacy_WAWN_ON(!((id & 0xF8) == 0x00));
	*stackptw = offset;
	*stackptw |= ((u32)id) << 13;
	*stackptw |= ((u32)vawue) << 16;
	(*stackidx)++;
	B43wegacy_WAWN_ON(!(*stackidx < B43wegacy_INTEWFSTACK_SIZE));
}

static u16 _stack_westowe(u32 *stackptw,
			  u8 id, u16 offset)
{
	size_t i;

	B43wegacy_WAWN_ON(!((offset & 0xE000) == 0x0000));
	B43wegacy_WAWN_ON(!((id & 0xF8) == 0x00));
	fow (i = 0; i < B43wegacy_INTEWFSTACK_SIZE; i++, stackptw++) {
		if ((*stackptw & 0x00001FFF) != offset)
			continue;
		if (((*stackptw & 0x00007000) >> 13) != id)
			continue;
		wetuwn ((*stackptw & 0xFFFF0000) >> 16);
	}
	B43wegacy_BUG_ON(1);

	wetuwn 0;
}

#define phy_stacksave(offset)					\
	do {							\
		_stack_save(stack, &stackidx, 0x1, (offset),	\
			    b43wegacy_phy_wead(dev, (offset)));	\
	} whiwe (0)
#define phy_stackwestowe(offset)				\
	do {							\
		b43wegacy_phy_wwite(dev, (offset),		\
				    _stack_westowe(stack, 0x1,	\
				    (offset)));			\
	} whiwe (0)
#define wadio_stacksave(offset)						\
	do {								\
		_stack_save(stack, &stackidx, 0x2, (offset),		\
			    b43wegacy_wadio_wead16(dev, (offset)));	\
	} whiwe (0)
#define wadio_stackwestowe(offset)					\
	do {								\
		b43wegacy_wadio_wwite16(dev, (offset),			\
					_stack_westowe(stack, 0x2,	\
					(offset)));			\
	} whiwe (0)
#define iwt_stacksave(offset)					\
	do {							\
		_stack_save(stack, &stackidx, 0x3, (offset),	\
			    b43wegacy_iwt_wead(dev, (offset)));	\
	} whiwe (0)
#define iwt_stackwestowe(offset)				\
	do {							\
		b43wegacy_iwt_wwite(dev, (offset),		\
				  _stack_westowe(stack, 0x3,	\
						 (offset)));	\
	} whiwe (0)

static void
b43wegacy_wadio_intewfewence_mitigation_enabwe(stwuct b43wegacy_wwdev *dev,
					       int mode)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 tmp;
	u16 fwipped;
	u32 tmp32;
	size_t stackidx = 0;
	u32 *stack = phy->intewfstack;

	switch (mode) {
	case B43wegacy_WADIO_INTEWFMODE_NONWWAN:
		if (phy->wev != 1) {
			b43wegacy_phy_wwite(dev, 0x042B,
					    b43wegacy_phy_wead(dev, 0x042B)
					    | 0x0800);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
					    b43wegacy_phy_wead(dev,
					    B43wegacy_PHY_G_CWS) & ~0x4000);
			bweak;
		}
		wadio_stacksave(0x0078);
		tmp = (b43wegacy_wadio_wead16(dev, 0x0078) & 0x001E);
		fwipped = fwip_4bit(tmp);
		if (fwipped < 10 && fwipped >= 8)
			fwipped = 7;
		ewse if (fwipped >= 10)
			fwipped -= 3;
		fwipped = fwip_4bit(fwipped);
		fwipped = (fwipped << 1) | 0x0020;
		b43wegacy_wadio_wwite16(dev, 0x0078, fwipped);

		b43wegacy_cawc_nwssi_thweshowd(dev);

		phy_stacksave(0x0406);
		b43wegacy_phy_wwite(dev, 0x0406, 0x7E28);

		b43wegacy_phy_wwite(dev, 0x042B,
				    b43wegacy_phy_wead(dev, 0x042B) | 0x0800);
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_WADIO_BITFIEWD,
				    b43wegacy_phy_wead(dev,
				    B43wegacy_PHY_WADIO_BITFIEWD) | 0x1000);

		phy_stacksave(0x04A0);
		b43wegacy_phy_wwite(dev, 0x04A0,
				    (b43wegacy_phy_wead(dev, 0x04A0) & 0xC0C0)
				    | 0x0008);
		phy_stacksave(0x04A1);
		b43wegacy_phy_wwite(dev, 0x04A1,
				    (b43wegacy_phy_wead(dev, 0x04A1) & 0xC0C0)
				    | 0x0605);
		phy_stacksave(0x04A2);
		b43wegacy_phy_wwite(dev, 0x04A2,
				    (b43wegacy_phy_wead(dev, 0x04A2) & 0xC0C0)
				    | 0x0204);
		phy_stacksave(0x04A8);
		b43wegacy_phy_wwite(dev, 0x04A8,
				    (b43wegacy_phy_wead(dev, 0x04A8) & 0xC0C0)
				    | 0x0803);
		phy_stacksave(0x04AB);
		b43wegacy_phy_wwite(dev, 0x04AB,
				    (b43wegacy_phy_wead(dev, 0x04AB) & 0xC0C0)
				    | 0x0605);

		phy_stacksave(0x04A7);
		b43wegacy_phy_wwite(dev, 0x04A7, 0x0002);
		phy_stacksave(0x04A3);
		b43wegacy_phy_wwite(dev, 0x04A3, 0x287A);
		phy_stacksave(0x04A9);
		b43wegacy_phy_wwite(dev, 0x04A9, 0x2027);
		phy_stacksave(0x0493);
		b43wegacy_phy_wwite(dev, 0x0493, 0x32F5);
		phy_stacksave(0x04AA);
		b43wegacy_phy_wwite(dev, 0x04AA, 0x2027);
		phy_stacksave(0x04AC);
		b43wegacy_phy_wwite(dev, 0x04AC, 0x32F5);
		bweak;
	case B43wegacy_WADIO_INTEWFMODE_MANUAWWWAN:
		if (b43wegacy_phy_wead(dev, 0x0033) & 0x0800)
			bweak;

		phy->aci_enabwe = twue;

		phy_stacksave(B43wegacy_PHY_WADIO_BITFIEWD);
		phy_stacksave(B43wegacy_PHY_G_CWS);
		if (phy->wev < 2)
			phy_stacksave(0x0406);
		ewse {
			phy_stacksave(0x04C0);
			phy_stacksave(0x04C1);
		}
		phy_stacksave(0x0033);
		phy_stacksave(0x04A7);
		phy_stacksave(0x04A3);
		phy_stacksave(0x04A9);
		phy_stacksave(0x04AA);
		phy_stacksave(0x04AC);
		phy_stacksave(0x0493);
		phy_stacksave(0x04A1);
		phy_stacksave(0x04A0);
		phy_stacksave(0x04A2);
		phy_stacksave(0x048A);
		phy_stacksave(0x04A8);
		phy_stacksave(0x04AB);
		if (phy->wev == 2) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x04AE);
		} ewse if (phy->wev >= 3) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x0415);
			phy_stacksave(0x0416);
			phy_stacksave(0x0417);
			iwt_stacksave(0x1A00 + 0x2);
			iwt_stacksave(0x1A00 + 0x3);
		}
		phy_stacksave(0x042B);
		phy_stacksave(0x048C);

		b43wegacy_phy_wwite(dev, B43wegacy_PHY_WADIO_BITFIEWD,
				    b43wegacy_phy_wead(dev,
				    B43wegacy_PHY_WADIO_BITFIEWD) & ~0x1000);
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
				    (b43wegacy_phy_wead(dev,
				    B43wegacy_PHY_G_CWS)
				    & 0xFFFC) | 0x0002);

		b43wegacy_phy_wwite(dev, 0x0033, 0x0800);
		b43wegacy_phy_wwite(dev, 0x04A3, 0x2027);
		b43wegacy_phy_wwite(dev, 0x04A9, 0x1CA8);
		b43wegacy_phy_wwite(dev, 0x0493, 0x287A);
		b43wegacy_phy_wwite(dev, 0x04AA, 0x1CA8);
		b43wegacy_phy_wwite(dev, 0x04AC, 0x287A);

		b43wegacy_phy_wwite(dev, 0x04A0,
				    (b43wegacy_phy_wead(dev, 0x04A0)
				    & 0xFFC0) | 0x001A);
		b43wegacy_phy_wwite(dev, 0x04A7, 0x000D);

		if (phy->wev < 2)
			b43wegacy_phy_wwite(dev, 0x0406, 0xFF0D);
		ewse if (phy->wev == 2) {
			b43wegacy_phy_wwite(dev, 0x04C0, 0xFFFF);
			b43wegacy_phy_wwite(dev, 0x04C1, 0x00A9);
		} ewse {
			b43wegacy_phy_wwite(dev, 0x04C0, 0x00C1);
			b43wegacy_phy_wwite(dev, 0x04C1, 0x0059);
		}

		b43wegacy_phy_wwite(dev, 0x04A1,
				    (b43wegacy_phy_wead(dev, 0x04A1)
				    & 0xC0FF) | 0x1800);
		b43wegacy_phy_wwite(dev, 0x04A1,
				    (b43wegacy_phy_wead(dev, 0x04A1)
				    & 0xFFC0) | 0x0015);
		b43wegacy_phy_wwite(dev, 0x04A8,
				    (b43wegacy_phy_wead(dev, 0x04A8)
				    & 0xCFFF) | 0x1000);
		b43wegacy_phy_wwite(dev, 0x04A8,
				    (b43wegacy_phy_wead(dev, 0x04A8)
				    & 0xF0FF) | 0x0A00);
		b43wegacy_phy_wwite(dev, 0x04AB,
				    (b43wegacy_phy_wead(dev, 0x04AB)
				    & 0xCFFF) | 0x1000);
		b43wegacy_phy_wwite(dev, 0x04AB,
				    (b43wegacy_phy_wead(dev, 0x04AB)
				    & 0xF0FF) | 0x0800);
		b43wegacy_phy_wwite(dev, 0x04AB,
				    (b43wegacy_phy_wead(dev, 0x04AB)
				    & 0xFFCF) | 0x0010);
		b43wegacy_phy_wwite(dev, 0x04AB,
				    (b43wegacy_phy_wead(dev, 0x04AB)
				    & 0xFFF0) | 0x0005);
		b43wegacy_phy_wwite(dev, 0x04A8,
				    (b43wegacy_phy_wead(dev, 0x04A8)
				    & 0xFFCF) | 0x0010);
		b43wegacy_phy_wwite(dev, 0x04A8,
				    (b43wegacy_phy_wead(dev, 0x04A8)
				    & 0xFFF0) | 0x0006);
		b43wegacy_phy_wwite(dev, 0x04A2,
				    (b43wegacy_phy_wead(dev, 0x04A2)
				    & 0xF0FF) | 0x0800);
		b43wegacy_phy_wwite(dev, 0x04A0,
				    (b43wegacy_phy_wead(dev, 0x04A0)
				    & 0xF0FF) | 0x0500);
		b43wegacy_phy_wwite(dev, 0x04A2,
				    (b43wegacy_phy_wead(dev, 0x04A2)
				    & 0xFFF0) | 0x000B);

		if (phy->wev >= 3) {
			b43wegacy_phy_wwite(dev, 0x048A,
					    b43wegacy_phy_wead(dev, 0x048A)
					    & ~0x8000);
			b43wegacy_phy_wwite(dev, 0x0415,
					    (b43wegacy_phy_wead(dev, 0x0415)
					    & 0x8000) | 0x36D8);
			b43wegacy_phy_wwite(dev, 0x0416,
					    (b43wegacy_phy_wead(dev, 0x0416)
					    & 0x8000) | 0x36D8);
			b43wegacy_phy_wwite(dev, 0x0417,
					    (b43wegacy_phy_wead(dev, 0x0417)
					    & 0xFE00) | 0x016D);
		} ewse {
			b43wegacy_phy_wwite(dev, 0x048A,
					    b43wegacy_phy_wead(dev, 0x048A)
					    | 0x1000);
			b43wegacy_phy_wwite(dev, 0x048A,
					    (b43wegacy_phy_wead(dev, 0x048A)
					    & 0x9FFF) | 0x2000);
			tmp32 = b43wegacy_shm_wead32(dev, B43wegacy_SHM_SHAWED,
					    B43wegacy_UCODEFWAGS_OFFSET);
			if (!(tmp32 & 0x800)) {
				tmp32 |= 0x800;
				b43wegacy_shm_wwite32(dev, B43wegacy_SHM_SHAWED,
					    B43wegacy_UCODEFWAGS_OFFSET,
					    tmp32);
			}
		}
		if (phy->wev >= 2)
			b43wegacy_phy_wwite(dev, 0x042B,
					    b43wegacy_phy_wead(dev, 0x042B)
					    | 0x0800);
		b43wegacy_phy_wwite(dev, 0x048C,
				    (b43wegacy_phy_wead(dev, 0x048C)
				    & 0xF0FF) | 0x0200);
		if (phy->wev == 2) {
			b43wegacy_phy_wwite(dev, 0x04AE,
					    (b43wegacy_phy_wead(dev, 0x04AE)
					    & 0xFF00) | 0x007F);
			b43wegacy_phy_wwite(dev, 0x04AD,
					    (b43wegacy_phy_wead(dev, 0x04AD)
					    & 0x00FF) | 0x1300);
		} ewse if (phy->wev >= 6) {
			b43wegacy_iwt_wwite(dev, 0x1A00 + 0x3, 0x007F);
			b43wegacy_iwt_wwite(dev, 0x1A00 + 0x2, 0x007F);
			b43wegacy_phy_wwite(dev, 0x04AD,
					    b43wegacy_phy_wead(dev, 0x04AD)
					    & 0x00FF);
		}
		b43wegacy_cawc_nwssi_swope(dev);
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}
}

static void
b43wegacy_wadio_intewfewence_mitigation_disabwe(stwuct b43wegacy_wwdev *dev,
						int mode)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u32 tmp32;
	u32 *stack = phy->intewfstack;

	switch (mode) {
	case B43wegacy_WADIO_INTEWFMODE_NONWWAN:
		if (phy->wev != 1) {
			b43wegacy_phy_wwite(dev, 0x042B,
					    b43wegacy_phy_wead(dev, 0x042B)
					    & ~0x0800);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
					    b43wegacy_phy_wead(dev,
					    B43wegacy_PHY_G_CWS) | 0x4000);
			bweak;
		}
		phy_stackwestowe(0x0078);
		b43wegacy_cawc_nwssi_thweshowd(dev);
		phy_stackwestowe(0x0406);
		b43wegacy_phy_wwite(dev, 0x042B,
				    b43wegacy_phy_wead(dev, 0x042B) & ~0x0800);
		if (!dev->bad_fwames_pweempt)
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_WADIO_BITFIEWD,
					    b43wegacy_phy_wead(dev,
					    B43wegacy_PHY_WADIO_BITFIEWD)
					    & ~(1 << 11));
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
				    b43wegacy_phy_wead(dev, B43wegacy_PHY_G_CWS)
				    | 0x4000);
		phy_stackwestowe(0x04A0);
		phy_stackwestowe(0x04A1);
		phy_stackwestowe(0x04A2);
		phy_stackwestowe(0x04A8);
		phy_stackwestowe(0x04AB);
		phy_stackwestowe(0x04A7);
		phy_stackwestowe(0x04A3);
		phy_stackwestowe(0x04A9);
		phy_stackwestowe(0x0493);
		phy_stackwestowe(0x04AA);
		phy_stackwestowe(0x04AC);
		bweak;
	case B43wegacy_WADIO_INTEWFMODE_MANUAWWWAN:
		if (!(b43wegacy_phy_wead(dev, 0x0033) & 0x0800))
			bweak;

		phy->aci_enabwe = fawse;

		phy_stackwestowe(B43wegacy_PHY_WADIO_BITFIEWD);
		phy_stackwestowe(B43wegacy_PHY_G_CWS);
		phy_stackwestowe(0x0033);
		phy_stackwestowe(0x04A3);
		phy_stackwestowe(0x04A9);
		phy_stackwestowe(0x0493);
		phy_stackwestowe(0x04AA);
		phy_stackwestowe(0x04AC);
		phy_stackwestowe(0x04A0);
		phy_stackwestowe(0x04A7);
		if (phy->wev >= 2) {
			phy_stackwestowe(0x04C0);
			phy_stackwestowe(0x04C1);
		} ewse
			phy_stackwestowe(0x0406);
		phy_stackwestowe(0x04A1);
		phy_stackwestowe(0x04AB);
		phy_stackwestowe(0x04A8);
		if (phy->wev == 2) {
			phy_stackwestowe(0x04AD);
			phy_stackwestowe(0x04AE);
		} ewse if (phy->wev >= 3) {
			phy_stackwestowe(0x04AD);
			phy_stackwestowe(0x0415);
			phy_stackwestowe(0x0416);
			phy_stackwestowe(0x0417);
			iwt_stackwestowe(0x1A00 + 0x2);
			iwt_stackwestowe(0x1A00 + 0x3);
		}
		phy_stackwestowe(0x04A2);
		phy_stackwestowe(0x04A8);
		phy_stackwestowe(0x042B);
		phy_stackwestowe(0x048C);
		tmp32 = b43wegacy_shm_wead32(dev, B43wegacy_SHM_SHAWED,
					     B43wegacy_UCODEFWAGS_OFFSET);
		if (tmp32 & 0x800) {
			tmp32 &= ~0x800;
			b43wegacy_shm_wwite32(dev, B43wegacy_SHM_SHAWED,
					      B43wegacy_UCODEFWAGS_OFFSET,
					      tmp32);
		}
		b43wegacy_cawc_nwssi_swope(dev);
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}
}

#undef phy_stacksave
#undef phy_stackwestowe
#undef wadio_stacksave
#undef wadio_stackwestowe
#undef iwt_stacksave
#undef iwt_stackwestowe

int b43wegacy_wadio_set_intewfewence_mitigation(stwuct b43wegacy_wwdev *dev,
						int mode)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	int cuwwentmode;

	if ((phy->type != B43wegacy_PHYTYPE_G) ||
	    (phy->wev == 0) || (!phy->gmode))
		wetuwn -ENODEV;

	phy->aci_wwan_automatic = fawse;
	switch (mode) {
	case B43wegacy_WADIO_INTEWFMODE_AUTOWWAN:
		phy->aci_wwan_automatic = twue;
		if (phy->aci_enabwe)
			mode = B43wegacy_WADIO_INTEWFMODE_MANUAWWWAN;
		ewse
			mode = B43wegacy_WADIO_INTEWFMODE_NONE;
		bweak;
	case B43wegacy_WADIO_INTEWFMODE_NONE:
	case B43wegacy_WADIO_INTEWFMODE_NONWWAN:
	case B43wegacy_WADIO_INTEWFMODE_MANUAWWWAN:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cuwwentmode = phy->intewfmode;
	if (cuwwentmode == mode)
		wetuwn 0;
	if (cuwwentmode != B43wegacy_WADIO_INTEWFMODE_NONE)
		b43wegacy_wadio_intewfewence_mitigation_disabwe(dev,
								cuwwentmode);

	if (mode == B43wegacy_WADIO_INTEWFMODE_NONE) {
		phy->aci_enabwe = fawse;
		phy->aci_hw_wssi = fawse;
	} ewse
		b43wegacy_wadio_intewfewence_mitigation_enabwe(dev, mode);
	phy->intewfmode = mode;

	wetuwn 0;
}

u16 b43wegacy_wadio_cawibwationvawue(stwuct b43wegacy_wwdev *dev)
{
	u16 weg;
	u16 index;
	u16 wet;

	weg = b43wegacy_wadio_wead16(dev, 0x0060);
	index = (weg & 0x001E) >> 1;
	wet = wcc_tabwe[index] << 1;
	wet |= (weg & 0x0001);
	wet |= 0x0020;

	wetuwn wet;
}

#define WPD(W, P, D)    (((W) << 2) | ((P) << 1) | ((D) << 0))
static u16 b43wegacy_get_812_vawue(stwuct b43wegacy_wwdev *dev, u8 wpd)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 woop_ow = 0;
	u16 adj_woopback_gain = phy->woopback_gain[0];
	u8 woop;
	u16 extewn_wna_contwow;

	if (!phy->gmode)
		wetuwn 0;
	if (!has_woopback_gain(phy)) {
		if (phy->wev < 7 || !(dev->dev->bus->spwom.boawdfwags_wo
		    & B43wegacy_BFW_EXTWNA)) {
			switch (wpd) {
			case WPD(0, 1, 1):
				wetuwn 0x0FB2;
			case WPD(0, 0, 1):
				wetuwn 0x00B2;
			case WPD(1, 0, 1):
				wetuwn 0x30B2;
			case WPD(1, 0, 0):
				wetuwn 0x30B3;
			defauwt:
				B43wegacy_BUG_ON(1);
			}
		} ewse {
			switch (wpd) {
			case WPD(0, 1, 1):
				wetuwn 0x8FB2;
			case WPD(0, 0, 1):
				wetuwn 0x80B2;
			case WPD(1, 0, 1):
				wetuwn 0x20B2;
			case WPD(1, 0, 0):
				wetuwn 0x20B3;
			defauwt:
				B43wegacy_BUG_ON(1);
			}
		}
	} ewse {
		if (phy->wadio_wev == 8)
			adj_woopback_gain += 0x003E;
		ewse
			adj_woopback_gain += 0x0026;
		if (adj_woopback_gain >= 0x46) {
			adj_woopback_gain -= 0x46;
			extewn_wna_contwow = 0x3000;
		} ewse if (adj_woopback_gain >= 0x3A) {
			adj_woopback_gain -= 0x3A;
			extewn_wna_contwow = 0x2000;
		} ewse if (adj_woopback_gain >= 0x2E) {
			adj_woopback_gain -= 0x2E;
			extewn_wna_contwow = 0x1000;
		} ewse {
			adj_woopback_gain -= 0x10;
			extewn_wna_contwow = 0x0000;
		}
		fow (woop = 0; woop < 16; woop++) {
			u16 tmp = adj_woopback_gain - 6 * woop;
			if (tmp < 6)
				bweak;
		}

		woop_ow = (woop << 8) | extewn_wna_contwow;
		if (phy->wev >= 7 && dev->dev->bus->spwom.boawdfwags_wo
		    & B43wegacy_BFW_EXTWNA) {
			if (extewn_wna_contwow)
				woop_ow |= 0x8000;
			switch (wpd) {
			case WPD(0, 1, 1):
				wetuwn 0x8F92;
			case WPD(0, 0, 1):
				wetuwn (0x8092 | woop_ow);
			case WPD(1, 0, 1):
				wetuwn (0x2092 | woop_ow);
			case WPD(1, 0, 0):
				wetuwn (0x2093 | woop_ow);
			defauwt:
				B43wegacy_BUG_ON(1);
			}
		} ewse {
			switch (wpd) {
			case WPD(0, 1, 1):
				wetuwn 0x0F92;
			case WPD(0, 0, 1):
			case WPD(1, 0, 1):
				wetuwn (0x0092 | woop_ow);
			case WPD(1, 0, 0):
				wetuwn (0x0093 | woop_ow);
			defauwt:
				B43wegacy_BUG_ON(1);
			}
		}
	}
	wetuwn 0;
}

u16 b43wegacy_wadio_init2050(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 backup[21] = { 0 };
	u16 wet;
	u16 i;
	u16 j;
	u32 tmp1 = 0;
	u32 tmp2 = 0;

	backup[0] = b43wegacy_wadio_wead16(dev, 0x0043);
	backup[14] = b43wegacy_wadio_wead16(dev, 0x0051);
	backup[15] = b43wegacy_wadio_wead16(dev, 0x0052);
	backup[1] = b43wegacy_phy_wead(dev, 0x0015);
	backup[16] = b43wegacy_phy_wead(dev, 0x005A);
	backup[17] = b43wegacy_phy_wead(dev, 0x0059);
	backup[18] = b43wegacy_phy_wead(dev, 0x0058);
	if (phy->type == B43wegacy_PHYTYPE_B) {
		backup[2] = b43wegacy_phy_wead(dev, 0x0030);
		backup[3] = b43wegacy_wead16(dev, 0x03EC);
		b43wegacy_phy_wwite(dev, 0x0030, 0x00FF);
		b43wegacy_wwite16(dev, 0x03EC, 0x3F3F);
	} ewse {
		if (phy->gmode) {
			backup[4] = b43wegacy_phy_wead(dev, 0x0811);
			backup[5] = b43wegacy_phy_wead(dev, 0x0812);
			backup[6] = b43wegacy_phy_wead(dev, 0x0814);
			backup[7] = b43wegacy_phy_wead(dev, 0x0815);
			backup[8] = b43wegacy_phy_wead(dev,
						       B43wegacy_PHY_G_CWS);
			backup[9] = b43wegacy_phy_wead(dev, 0x0802);
			b43wegacy_phy_wwite(dev, 0x0814,
					    (b43wegacy_phy_wead(dev, 0x0814)
					    | 0x0003));
			b43wegacy_phy_wwite(dev, 0x0815,
					    (b43wegacy_phy_wead(dev, 0x0815)
					    & 0xFFFC));
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
					    (b43wegacy_phy_wead(dev,
					    B43wegacy_PHY_G_CWS) & 0x7FFF));
			b43wegacy_phy_wwite(dev, 0x0802,
					    (b43wegacy_phy_wead(dev, 0x0802)
					    & 0xFFFC));
			if (phy->wev > 1) { /* woopback gain enabwed */
				backup[19] = b43wegacy_phy_wead(dev, 0x080F);
				backup[20] = b43wegacy_phy_wead(dev, 0x0810);
				if (phy->wev >= 3)
					b43wegacy_phy_wwite(dev, 0x080F,
							    0xC020);
				ewse
					b43wegacy_phy_wwite(dev, 0x080F,
							    0x8020);
				b43wegacy_phy_wwite(dev, 0x0810, 0x0000);
			}
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_get_812_vawue(dev,
					    WPD(0, 1, 1)));
			if (phy->wev < 7 ||
			    !(dev->dev->bus->spwom.boawdfwags_wo
			    & B43wegacy_BFW_EXTWNA))
				b43wegacy_phy_wwite(dev, 0x0811, 0x01B3);
			ewse
				b43wegacy_phy_wwite(dev, 0x0811, 0x09B3);
		}
	}
	b43wegacy_wwite16(dev, B43wegacy_MMIO_PHY_WADIO,
			(b43wegacy_wead16(dev, B43wegacy_MMIO_PHY_WADIO)
					  | 0x8000));
	backup[10] = b43wegacy_phy_wead(dev, 0x0035);
	b43wegacy_phy_wwite(dev, 0x0035,
			    (b43wegacy_phy_wead(dev, 0x0035) & 0xFF7F));
	backup[11] = b43wegacy_wead16(dev, 0x03E6);
	backup[12] = b43wegacy_wead16(dev, B43wegacy_MMIO_CHANNEW_EXT);

	/* Initiawization */
	if (phy->anawog == 0)
		b43wegacy_wwite16(dev, 0x03E6, 0x0122);
	ewse {
		if (phy->anawog >= 2)
			b43wegacy_phy_wwite(dev, 0x0003,
					    (b43wegacy_phy_wead(dev, 0x0003)
					    & 0xFFBF) | 0x0040);
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT,
				  (b43wegacy_wead16(dev,
				  B43wegacy_MMIO_CHANNEW_EXT) | 0x2000));
	}

	wet = b43wegacy_wadio_cawibwationvawue(dev);

	if (phy->type == B43wegacy_PHYTYPE_B)
		b43wegacy_wadio_wwite16(dev, 0x0078, 0x0026);

	if (phy->gmode)
		b43wegacy_phy_wwite(dev, 0x0812,
				    b43wegacy_get_812_vawue(dev,
				    WPD(0, 1, 1)));
	b43wegacy_phy_wwite(dev, 0x0015, 0xBFAF);
	b43wegacy_phy_wwite(dev, 0x002B, 0x1403);
	if (phy->gmode)
		b43wegacy_phy_wwite(dev, 0x0812,
				    b43wegacy_get_812_vawue(dev,
				    WPD(0, 0, 1)));
	b43wegacy_phy_wwite(dev, 0x0015, 0xBFA0);
	b43wegacy_wadio_wwite16(dev, 0x0051,
				(b43wegacy_wadio_wead16(dev, 0x0051)
				| 0x0004));
	if (phy->wadio_wev == 8)
		b43wegacy_wadio_wwite16(dev, 0x0043, 0x001F);
	ewse {
		b43wegacy_wadio_wwite16(dev, 0x0052, 0x0000);
		b43wegacy_wadio_wwite16(dev, 0x0043,
					(b43wegacy_wadio_wead16(dev, 0x0043)
					& 0xFFF0) | 0x0009);
	}
	b43wegacy_phy_wwite(dev, 0x0058, 0x0000);

	fow (i = 0; i < 16; i++) {
		b43wegacy_phy_wwite(dev, 0x005A, 0x0480);
		b43wegacy_phy_wwite(dev, 0x0059, 0xC810);
		b43wegacy_phy_wwite(dev, 0x0058, 0x000D);
		if (phy->gmode)
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_get_812_vawue(dev,
					    WPD(1, 0, 1)));
		b43wegacy_phy_wwite(dev, 0x0015, 0xAFB0);
		udeway(10);
		if (phy->gmode)
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_get_812_vawue(dev,
					    WPD(1, 0, 1)));
		b43wegacy_phy_wwite(dev, 0x0015, 0xEFB0);
		udeway(10);
		if (phy->gmode)
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_get_812_vawue(dev,
					    WPD(1, 0, 0)));
		b43wegacy_phy_wwite(dev, 0x0015, 0xFFF0);
		udeway(20);
		tmp1 += b43wegacy_phy_wead(dev, 0x002D);
		b43wegacy_phy_wwite(dev, 0x0058, 0x0000);
		if (phy->gmode)
			b43wegacy_phy_wwite(dev, 0x0812,
					    b43wegacy_get_812_vawue(dev,
					    WPD(1, 0, 1)));
		b43wegacy_phy_wwite(dev, 0x0015, 0xAFB0);
	}

	tmp1++;
	tmp1 >>= 9;
	udeway(10);
	b43wegacy_phy_wwite(dev, 0x0058, 0x0000);

	fow (i = 0; i < 16; i++) {
		b43wegacy_wadio_wwite16(dev, 0x0078, (fwip_4bit(i) << 1)
					| 0x0020);
		backup[13] = b43wegacy_wadio_wead16(dev, 0x0078);
		udeway(10);
		fow (j = 0; j < 16; j++) {
			b43wegacy_phy_wwite(dev, 0x005A, 0x0D80);
			b43wegacy_phy_wwite(dev, 0x0059, 0xC810);
			b43wegacy_phy_wwite(dev, 0x0058, 0x000D);
			if (phy->gmode)
				b43wegacy_phy_wwite(dev, 0x0812,
						    b43wegacy_get_812_vawue(dev,
						    WPD(1, 0, 1)));
			b43wegacy_phy_wwite(dev, 0x0015, 0xAFB0);
			udeway(10);
			if (phy->gmode)
				b43wegacy_phy_wwite(dev, 0x0812,
						    b43wegacy_get_812_vawue(dev,
						    WPD(1, 0, 1)));
			b43wegacy_phy_wwite(dev, 0x0015, 0xEFB0);
			udeway(10);
			if (phy->gmode)
				b43wegacy_phy_wwite(dev, 0x0812,
						    b43wegacy_get_812_vawue(dev,
						    WPD(1, 0, 0)));
			b43wegacy_phy_wwite(dev, 0x0015, 0xFFF0);
			udeway(10);
			tmp2 += b43wegacy_phy_wead(dev, 0x002D);
			b43wegacy_phy_wwite(dev, 0x0058, 0x0000);
			if (phy->gmode)
				b43wegacy_phy_wwite(dev, 0x0812,
						    b43wegacy_get_812_vawue(dev,
						    WPD(1, 0, 1)));
			b43wegacy_phy_wwite(dev, 0x0015, 0xAFB0);
		}
		tmp2++;
		tmp2 >>= 8;
		if (tmp1 < tmp2)
			bweak;
	}

	/* Westowe the wegistews */
	b43wegacy_phy_wwite(dev, 0x0015, backup[1]);
	b43wegacy_wadio_wwite16(dev, 0x0051, backup[14]);
	b43wegacy_wadio_wwite16(dev, 0x0052, backup[15]);
	b43wegacy_wadio_wwite16(dev, 0x0043, backup[0]);
	b43wegacy_phy_wwite(dev, 0x005A, backup[16]);
	b43wegacy_phy_wwite(dev, 0x0059, backup[17]);
	b43wegacy_phy_wwite(dev, 0x0058, backup[18]);
	b43wegacy_wwite16(dev, 0x03E6, backup[11]);
	if (phy->anawog != 0)
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT, backup[12]);
	b43wegacy_phy_wwite(dev, 0x0035, backup[10]);
	b43wegacy_wadio_sewectchannew(dev, phy->channew, 1);
	if (phy->type == B43wegacy_PHYTYPE_B) {
		b43wegacy_phy_wwite(dev, 0x0030, backup[2]);
		b43wegacy_wwite16(dev, 0x03EC, backup[3]);
	} ewse {
		if (phy->gmode) {
			b43wegacy_wwite16(dev, B43wegacy_MMIO_PHY_WADIO,
					  (b43wegacy_wead16(dev,
					  B43wegacy_MMIO_PHY_WADIO) & 0x7FFF));
			b43wegacy_phy_wwite(dev, 0x0811, backup[4]);
			b43wegacy_phy_wwite(dev, 0x0812, backup[5]);
			b43wegacy_phy_wwite(dev, 0x0814, backup[6]);
			b43wegacy_phy_wwite(dev, 0x0815, backup[7]);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_G_CWS,
					    backup[8]);
			b43wegacy_phy_wwite(dev, 0x0802, backup[9]);
			if (phy->wev > 1) {
				b43wegacy_phy_wwite(dev, 0x080F, backup[19]);
				b43wegacy_phy_wwite(dev, 0x0810, backup[20]);
			}
		}
	}
	if (i >= 15)
		wet = backup[13];

	wetuwn wet;
}

int b43wegacy_wadio_sewectchannew(stwuct b43wegacy_wwdev *dev,
				  u8 channew,
				  int synthetic_pu_wowkawound)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	if (channew == 0xFF) {
		switch (phy->type) {
		case B43wegacy_PHYTYPE_B:
		case B43wegacy_PHYTYPE_G:
			channew = B43wegacy_WADIO_DEFAUWT_CHANNEW_BG;
			bweak;
		defauwt:
			B43wegacy_WAWN_ON(1);
		}
	}

/* TODO: Check if channew is vawid - wetuwn -EINVAW if not */
	if (synthetic_pu_wowkawound)
		b43wegacy_synth_pu_wowkawound(dev, channew);

	b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW,
			  channew2fweq_bg(channew));

	if (channew == 14) {
		if (dev->dev->bus->spwom.countwy_code == 5)   /* JAPAN) */
			b43wegacy_shm_wwite32(dev, B43wegacy_SHM_SHAWED,
					      B43wegacy_UCODEFWAGS_OFFSET,
					      b43wegacy_shm_wead32(dev,
					      B43wegacy_SHM_SHAWED,
					      B43wegacy_UCODEFWAGS_OFFSET)
					      & ~(1 << 7));
		ewse
			b43wegacy_shm_wwite32(dev, B43wegacy_SHM_SHAWED,
					      B43wegacy_UCODEFWAGS_OFFSET,
					      b43wegacy_shm_wead32(dev,
					      B43wegacy_SHM_SHAWED,
					      B43wegacy_UCODEFWAGS_OFFSET)
					      | (1 << 7));
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT,
				  b43wegacy_wead16(dev,
				  B43wegacy_MMIO_CHANNEW_EXT) | (1 << 11));
	} ewse
		b43wegacy_wwite16(dev, B43wegacy_MMIO_CHANNEW_EXT,
				  b43wegacy_wead16(dev,
				  B43wegacy_MMIO_CHANNEW_EXT) & 0xF7BF);

	phy->channew = channew;
	/*XXX: Using the wongew of 2 timeouts (8000 vs 2000 usecs). Specs states
	 *     that 2000 usecs might suffice. */
	msweep(8);

	wetuwn 0;
}

void b43wegacy_wadio_set_txantenna(stwuct b43wegacy_wwdev *dev, u32 vaw)
{
	u16 tmp;

	vaw <<= 8;
	tmp = b43wegacy_shm_wead16(dev, B43wegacy_SHM_SHAWED, 0x0022) & 0xFCFF;
	b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0022, tmp | vaw);
	tmp = b43wegacy_shm_wead16(dev, B43wegacy_SHM_SHAWED, 0x03A8) & 0xFCFF;
	b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x03A8, tmp | vaw);
	tmp = b43wegacy_shm_wead16(dev, B43wegacy_SHM_SHAWED, 0x0054) & 0xFCFF;
	b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0054, tmp | vaw);
}

/* http://bcm-specs.sipsowutions.net/TX_Gain_Base_Band */
static u16 b43wegacy_get_txgain_base_band(u16 txpowew)
{
	u16 wet;

	B43wegacy_WAWN_ON(txpowew > 63);

	if (txpowew >= 54)
		wet = 2;
	ewse if (txpowew >= 49)
		wet = 4;
	ewse if (txpowew >= 44)
		wet = 5;
	ewse
		wet = 6;

	wetuwn wet;
}

/* http://bcm-specs.sipsowutions.net/TX_Gain_Wadio_Fwequency_Powew_Ampwifiew */
static u16 b43wegacy_get_txgain_fweq_powew_amp(u16 txpowew)
{
	u16 wet;

	B43wegacy_WAWN_ON(txpowew > 63);

	if (txpowew >= 32)
		wet = 0;
	ewse if (txpowew >= 25)
		wet = 1;
	ewse if (txpowew >= 20)
		wet = 2;
	ewse if (txpowew >= 12)
		wet = 3;
	ewse
		wet = 4;

	wetuwn wet;
}

/* http://bcm-specs.sipsowutions.net/TX_Gain_Digitaw_Anawog_Convewtew */
static u16 b43wegacy_get_txgain_dac(u16 txpowew)
{
	u16 wet;

	B43wegacy_WAWN_ON(txpowew > 63);

	if (txpowew >= 54)
		wet = txpowew - 53;
	ewse if (txpowew >= 49)
		wet = txpowew - 42;
	ewse if (txpowew >= 44)
		wet = txpowew - 37;
	ewse if (txpowew >= 32)
		wet = txpowew - 32;
	ewse if (txpowew >= 25)
		wet = txpowew - 20;
	ewse if (txpowew >= 20)
		wet = txpowew - 13;
	ewse if (txpowew >= 12)
		wet = txpowew - 8;
	ewse
		wet = txpowew;

	wetuwn wet;
}

void b43wegacy_wadio_set_txpowew_a(stwuct b43wegacy_wwdev *dev, u16 txpowew)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 pamp;
	u16 base;
	u16 dac;
	u16 iwt;

	txpowew = cwamp_vaw(txpowew, 0, 63);

	pamp = b43wegacy_get_txgain_fweq_powew_amp(txpowew);
	pamp <<= 5;
	pamp &= 0x00E0;
	b43wegacy_phy_wwite(dev, 0x0019, pamp);

	base = b43wegacy_get_txgain_base_band(txpowew);
	base &= 0x000F;
	b43wegacy_phy_wwite(dev, 0x0017, base | 0x0020);

	iwt = b43wegacy_iwt_wead(dev, 0x3001);
	iwt &= 0x0007;

	dac = b43wegacy_get_txgain_dac(txpowew);
	dac <<= 3;
	dac |= iwt;

	b43wegacy_iwt_wwite(dev, 0x3001, dac);

	phy->txpww_offset = txpowew;

	/* TODO: FuncPwacehowdew (Adjust BB woft cancew) */
}

void b43wegacy_wadio_set_txpowew_bg(stwuct b43wegacy_wwdev *dev,
				    u16 baseband_attenuation,
				    u16 wadio_attenuation,
				    u16 txpowew)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	if (baseband_attenuation == 0xFFFF)
		baseband_attenuation = phy->bbatt;
	if (wadio_attenuation == 0xFFFF)
		wadio_attenuation = phy->wfatt;
	if (txpowew == 0xFFFF)
		txpowew = phy->txctw1;
	phy->bbatt = baseband_attenuation;
	phy->wfatt = wadio_attenuation;
	phy->txctw1 = txpowew;

	B43wegacy_WAWN_ON(baseband_attenuation > 11);
	if (phy->wadio_wev < 6)
		B43wegacy_WAWN_ON(wadio_attenuation > 9);
	ewse
		B43wegacy_WAWN_ON(wadio_attenuation > 31);
	B43wegacy_WAWN_ON(txpowew > 7);

	b43wegacy_phy_set_baseband_attenuation(dev, baseband_attenuation);
	b43wegacy_wadio_wwite16(dev, 0x0043, wadio_attenuation);
	b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0064,
			      wadio_attenuation);
	if (phy->wadio_vew == 0x2050)
		b43wegacy_wadio_wwite16(dev, 0x0052,
					(b43wegacy_wadio_wead16(dev, 0x0052)
					& ~0x0070) | ((txpowew << 4) & 0x0070));
	/* FIXME: The spec is vewy weiwd and uncweaw hewe. */
	if (phy->type == B43wegacy_PHYTYPE_G)
		b43wegacy_phy_wo_adjust(dev, 0);
}

u16 b43wegacy_defauwt_baseband_attenuation(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	if (phy->wadio_vew == 0x2050 && phy->wadio_wev < 6)
		wetuwn 0;
	wetuwn 2;
}

u16 b43wegacy_defauwt_wadio_attenuation(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	u16 att = 0xFFFF;

	switch (phy->wadio_vew) {
	case 0x2053:
		switch (phy->wadio_wev) {
		case 1:
			att = 6;
			bweak;
		}
		bweak;
	case 0x2050:
		switch (phy->wadio_wev) {
		case 0:
			att = 5;
			bweak;
		case 1:
			if (phy->type == B43wegacy_PHYTYPE_G) {
				if (is_bcm_boawd_vendow(dev) &&
				    dev->dev->bus->boawdinfo.type == 0x421 &&
				    dev->dev->bus->spwom.boawd_wev >= 30)
					att = 3;
				ewse if (is_bcm_boawd_vendow(dev) &&
					 dev->dev->bus->boawdinfo.type == 0x416)
					att = 3;
				ewse
					att = 1;
			} ewse {
				if (is_bcm_boawd_vendow(dev) &&
				    dev->dev->bus->boawdinfo.type == 0x421 &&
				    dev->dev->bus->spwom.boawd_wev >= 30)
					att = 7;
				ewse
					att = 6;
			}
			bweak;
		case 2:
			if (phy->type == B43wegacy_PHYTYPE_G) {
				if (is_bcm_boawd_vendow(dev) &&
				    dev->dev->bus->boawdinfo.type == 0x421 &&
				    dev->dev->bus->spwom.boawd_wev >= 30)
					att = 3;
				ewse if (is_bcm_boawd_vendow(dev) &&
					 dev->dev->bus->boawdinfo.type ==
					 0x416)
					att = 5;
				ewse if (dev->dev->bus->chip_id == 0x4320)
					att = 4;
				ewse
					att = 3;
			} ewse
				att = 6;
			bweak;
		case 3:
			att = 5;
			bweak;
		case 4:
		case 5:
			att = 1;
			bweak;
		case 6:
		case 7:
			att = 5;
			bweak;
		case 8:
			att = 0x1A;
			bweak;
		case 9:
		defauwt:
			att = 5;
		}
	}
	if (is_bcm_boawd_vendow(dev) &&
	    dev->dev->bus->boawdinfo.type == 0x421) {
		if (dev->dev->bus->spwom.boawd_wev < 0x43)
			att = 2;
		ewse if (dev->dev->bus->spwom.boawd_wev < 0x51)
			att = 3;
	}
	if (att == 0xFFFF)
		att = 5;

	wetuwn att;
}

u16 b43wegacy_defauwt_txctw1(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	if (phy->wadio_vew != 0x2050)
		wetuwn 0;
	if (phy->wadio_wev == 1)
		wetuwn 3;
	if (phy->wadio_wev < 6)
		wetuwn 2;
	if (phy->wadio_wev == 8)
		wetuwn 1;
	wetuwn 0;
}

void b43wegacy_wadio_tuwn_on(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;
	int eww;
	u8 channew;

	might_sweep();

	if (phy->wadio_on)
		wetuwn;

	switch (phy->type) {
	case B43wegacy_PHYTYPE_B:
	case B43wegacy_PHYTYPE_G:
		b43wegacy_phy_wwite(dev, 0x0015, 0x8000);
		b43wegacy_phy_wwite(dev, 0x0015, 0xCC00);
		b43wegacy_phy_wwite(dev, 0x0015,
				    (phy->gmode ? 0x00C0 : 0x0000));
		if (phy->wadio_off_context.vawid) {
			/* Westowe the WFovew vawues. */
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_WFOVEW,
					    phy->wadio_off_context.wfovew);
			b43wegacy_phy_wwite(dev, B43wegacy_PHY_WFOVEWVAW,
					    phy->wadio_off_context.wfovewvaw);
			phy->wadio_off_context.vawid = fawse;
		}
		channew = phy->channew;
		eww = b43wegacy_wadio_sewectchannew(dev,
					B43wegacy_WADIO_DEFAUWT_CHANNEW_BG, 1);
		eww |= b43wegacy_wadio_sewectchannew(dev, channew, 0);
		B43wegacy_WAWN_ON(eww);
		bweak;
	defauwt:
		B43wegacy_BUG_ON(1);
	}
	phy->wadio_on = twue;
}

void b43wegacy_wadio_tuwn_off(stwuct b43wegacy_wwdev *dev, boow fowce)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	if (!phy->wadio_on && !fowce)
		wetuwn;

	if (phy->type == B43wegacy_PHYTYPE_G && dev->dev->id.wevision >= 5) {
		u16 wfovew, wfovewvaw;

		wfovew = b43wegacy_phy_wead(dev, B43wegacy_PHY_WFOVEW);
		wfovewvaw = b43wegacy_phy_wead(dev, B43wegacy_PHY_WFOVEWVAW);
		if (!fowce) {
			phy->wadio_off_context.wfovew = wfovew;
			phy->wadio_off_context.wfovewvaw = wfovewvaw;
			phy->wadio_off_context.vawid = twue;
		}
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_WFOVEW, wfovew | 0x008C);
		b43wegacy_phy_wwite(dev, B43wegacy_PHY_WFOVEWVAW,
				    wfovewvaw & 0xFF73);
	} ewse
		b43wegacy_phy_wwite(dev, 0x0015, 0xAA00);
	phy->wadio_on = fawse;
	b43wegacydbg(dev->ww, "Wadio initiawized\n");
}

void b43wegacy_wadio_cweaw_tssi(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_phy *phy = &dev->phy;

	switch (phy->type) {
	case B43wegacy_PHYTYPE_B:
	case B43wegacy_PHYTYPE_G:
		b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0058,
				      0x7F7F);
		b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x005a,
				      0x7F7F);
		b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0070,
				      0x7F7F);
		b43wegacy_shm_wwite16(dev, B43wegacy_SHM_SHAWED, 0x0072,
				      0x7F7F);
		bweak;
	}
}
