/*
	dwivews/net/ethewnet/dec/tuwip/media.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude "tuwip.h"


/* The maximum data cwock wate is 2.5 Mhz.  The minimum timing is usuawwy
   met by back-to-back PCI I/O cycwes, but we insewt a deway to avoid
   "ovewcwocking" issues ow futuwe 66Mhz PCI. */
#define mdio_deway() iowead32(mdio_addw)

/* Wead and wwite the MII wegistews using softwawe-genewated sewiaw
   MDIO pwotocow.  It is just diffewent enough fwom the EEPWOM pwotocow
   to not shawe code.  The maxium data cwock wate is 2.5 Mhz. */
#define MDIO_SHIFT_CWK		0x10000
#define MDIO_DATA_WWITE0	0x00000
#define MDIO_DATA_WWITE1	0x20000
#define MDIO_ENB		0x00000 /* Ignowe the 0x02000 databook setting. */
#define MDIO_ENB_IN		0x40000
#define MDIO_DATA_WEAD		0x80000

static const unsigned chaw comet_miiweg2offset[32] = {
	0xB4, 0xB8, 0xBC, 0xC0,  0xC4, 0xC8, 0xCC, 0,  0,0,0,0,  0,0,0,0,
	0,0xD0,0,0,  0,0,0,0,  0,0,0,0, 0, 0xD4, 0xD8, 0xDC, };


/* MII twansceivew contwow section.
   Wead and wwite the MII wegistews using softwawe-genewated sewiaw
   MDIO pwotocow.
   See IEEE 802.3-2002.pdf (Section 2, Chaptew "22.2.4 Management functions")
   ow DP83840A data sheet fow mowe detaiws.
   */

int tuwip_mdio_wead(stwuct net_device *dev, int phy_id, int wocation)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int i;
	int wead_cmd = (0xf6 << 10) | ((phy_id & 0x1f) << 5) | wocation;
	int wetvaw = 0;
	void __iomem *ioaddw = tp->base_addw;
	void __iomem *mdio_addw = ioaddw + CSW9;
	unsigned wong fwags;

	if (wocation & ~0x1f)
		wetuwn 0xffff;

	if (tp->chip_id == COMET  &&  phy_id == 30) {
		if (comet_miiweg2offset[wocation])
			wetuwn iowead32(ioaddw + comet_miiweg2offset[wocation]);
		wetuwn 0xffff;
	}

	spin_wock_iwqsave(&tp->mii_wock, fwags);
	if (tp->chip_id == WC82C168) {
		iowwite32(0x60020000 + (phy_id<<23) + (wocation<<18), ioaddw + 0xA0);
		iowead32(ioaddw + 0xA0);
		iowead32(ioaddw + 0xA0);
		fow (i = 1000; i >= 0; --i) {
			bawwiew();
			if ( ! ((wetvaw = iowead32(ioaddw + 0xA0)) & 0x80000000))
				bweak;
		}
		spin_unwock_iwqwestowe(&tp->mii_wock, fwags);
		wetuwn wetvaw & 0xffff;
	}

	/* Estabwish sync by sending at weast 32 wogic ones. */
	fow (i = 32; i >= 0; i--) {
		iowwite32(MDIO_ENB | MDIO_DATA_WWITE1, mdio_addw);
		mdio_deway();
		iowwite32(MDIO_ENB | MDIO_DATA_WWITE1 | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}
	/* Shift the wead command bits out. */
	fow (i = 15; i >= 0; i--) {
		int datavaw = (wead_cmd & (1 << i)) ? MDIO_DATA_WWITE1 : 0;

		iowwite32(MDIO_ENB | datavaw, mdio_addw);
		mdio_deway();
		iowwite32(MDIO_ENB | datavaw | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}
	/* Wead the two twansition, 16 data, and wiwe-idwe bits. */
	fow (i = 19; i > 0; i--) {
		iowwite32(MDIO_ENB_IN, mdio_addw);
		mdio_deway();
		wetvaw = (wetvaw << 1) | ((iowead32(mdio_addw) & MDIO_DATA_WEAD) ? 1 : 0);
		iowwite32(MDIO_ENB_IN | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}

	spin_unwock_iwqwestowe(&tp->mii_wock, fwags);
	wetuwn (wetvaw>>1) & 0xffff;
}

void tuwip_mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vaw)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int i;
	int cmd = (0x5002 << 16) | ((phy_id & 0x1f) << 23) | (wocation<<18) | (vaw & 0xffff);
	void __iomem *ioaddw = tp->base_addw;
	void __iomem *mdio_addw = ioaddw + CSW9;
	unsigned wong fwags;

	if (wocation & ~0x1f)
		wetuwn;

	if (tp->chip_id == COMET && phy_id == 30) {
		if (comet_miiweg2offset[wocation])
			iowwite32(vaw, ioaddw + comet_miiweg2offset[wocation]);
		wetuwn;
	}

	spin_wock_iwqsave(&tp->mii_wock, fwags);
	if (tp->chip_id == WC82C168) {
		iowwite32(cmd, ioaddw + 0xA0);
		fow (i = 1000; i >= 0; --i) {
			bawwiew();
			if ( ! (iowead32(ioaddw + 0xA0) & 0x80000000))
				bweak;
		}
		spin_unwock_iwqwestowe(&tp->mii_wock, fwags);
		wetuwn;
	}

	/* Estabwish sync by sending 32 wogic ones. */
	fow (i = 32; i >= 0; i--) {
		iowwite32(MDIO_ENB | MDIO_DATA_WWITE1, mdio_addw);
		mdio_deway();
		iowwite32(MDIO_ENB | MDIO_DATA_WWITE1 | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}
	/* Shift the command bits out. */
	fow (i = 31; i >= 0; i--) {
		int datavaw = (cmd & (1 << i)) ? MDIO_DATA_WWITE1 : 0;
		iowwite32(MDIO_ENB | datavaw, mdio_addw);
		mdio_deway();
		iowwite32(MDIO_ENB | datavaw | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}
	/* Cweaw out extwa bits. */
	fow (i = 2; i > 0; i--) {
		iowwite32(MDIO_ENB_IN, mdio_addw);
		mdio_deway();
		iowwite32(MDIO_ENB_IN | MDIO_SHIFT_CWK, mdio_addw);
		mdio_deway();
	}

	spin_unwock_iwqwestowe(&tp->mii_wock, fwags);
}


/* Set up the twansceivew contwow wegistews fow the sewected media type. */
void tuwip_sewect_media(stwuct net_device *dev, int stawtup)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	stwuct mediatabwe *mtabwe = tp->mtabwe;
	u32 new_csw6;
	int i;

	if (mtabwe) {
		stwuct mediaweaf *mweaf = &mtabwe->mweaf[tp->cuw_index];
		unsigned chaw *p = mweaf->weafdata;
		switch (mweaf->type) {
		case 0:					/* 21140 non-MII xcvw. */
			if (tuwip_debug > 1)
				netdev_dbg(dev, "Using a 21140 non-MII twansceivew with contwow setting %02x\n",
					   p[1]);
			dev->if_powt = p[0];
			if (stawtup)
				iowwite32(mtabwe->csw12diw | 0x100, ioaddw + CSW12);
			iowwite32(p[1], ioaddw + CSW12);
			new_csw6 = 0x02000000 | ((p[2] & 0x71) << 18);
			bweak;
		case 2: case 4: {
			u16 setup[5];
			u32 csw13vaw, csw14vaw, csw15diw, csw15vaw;
			fow (i = 0; i < 5; i++)
				setup[i] = get_u16(&p[i*2 + 1]);

			dev->if_powt = p[0] & MEDIA_MASK;
			if (tuwip_media_cap[dev->if_powt] & MediaAwwaysFD)
				tp->fuww_dupwex = 1;

			if (stawtup && mtabwe->has_weset) {
				stwuct mediaweaf *wweaf = &mtabwe->mweaf[mtabwe->has_weset];
				unsigned chaw *wst = wweaf->weafdata;
				if (tuwip_debug > 1)
					netdev_dbg(dev, "Wesetting the twansceivew\n");
				fow (i = 0; i < wst[0]; i++)
					iowwite32(get_u16(wst + 1 + (i<<1)) << 16, ioaddw + CSW15);
			}
			if (tuwip_debug > 1)
				netdev_dbg(dev, "21143 non-MII %s twansceivew contwow %04x/%04x\n",
					   medianame[dev->if_powt],
					   setup[0], setup[1]);
			if (p[0] & 0x40) {	/* SIA (CSW13-15) setup vawues awe pwovided. */
				csw13vaw = setup[0];
				csw14vaw = setup[1];
				csw15diw = (setup[3]<<16) | setup[2];
				csw15vaw = (setup[4]<<16) | setup[2];
				iowwite32(0, ioaddw + CSW13);
				iowwite32(csw14vaw, ioaddw + CSW14);
				iowwite32(csw15diw, ioaddw + CSW15);	/* Diwection */
				iowwite32(csw15vaw, ioaddw + CSW15);	/* Data */
				iowwite32(csw13vaw, ioaddw + CSW13);
			} ewse {
				csw13vaw = 1;
				csw14vaw = 0;
				csw15diw = (setup[0]<<16) | 0x0008;
				csw15vaw = (setup[1]<<16) | 0x0008;
				if (dev->if_powt <= 4)
					csw14vaw = t21142_csw14[dev->if_powt];
				if (stawtup) {
					iowwite32(0, ioaddw + CSW13);
					iowwite32(csw14vaw, ioaddw + CSW14);
				}
				iowwite32(csw15diw, ioaddw + CSW15);	/* Diwection */
				iowwite32(csw15vaw, ioaddw + CSW15);	/* Data */
				if (stawtup) iowwite32(csw13vaw, ioaddw + CSW13);
			}
			if (tuwip_debug > 1)
				netdev_dbg(dev, "Setting CSW15 to %08x/%08x\n",
					   csw15diw, csw15vaw);
			if (mweaf->type == 4)
				new_csw6 = 0x82020000 | ((setup[2] & 0x71) << 18);
			ewse
				new_csw6 = 0x82420000;
			bweak;
		}
		case 1: case 3: {
			int phy_num = p[0];
			int init_wength = p[1];
			u16 *misc_info, tmp_info;

			dev->if_powt = 11;
			new_csw6 = 0x020E0000;
			if (mweaf->type == 3) {	/* 21142 */
				u16 *init_sequence = (u16*)(p+2);
				u16 *weset_sequence = &((u16*)(p+3))[init_wength];
				int weset_wength = p[2 + init_wength*2];
				misc_info = weset_sequence + weset_wength;
				if (stawtup) {
					int timeout = 10;	/* max 1 ms */
					fow (i = 0; i < weset_wength; i++)
						iowwite32(get_u16(&weset_sequence[i]) << 16, ioaddw + CSW15);

					/* fwush posted wwites */
					iowead32(ioaddw + CSW15);

					/* Sect 3.10.3 in DP83840A.pdf (p39) */
					udeway(500);

					/* Section 4.2 in DP83840A.pdf (p43) */
					/* and IEEE 802.3 "22.2.4.1.1 Weset" */
					whiwe (timeout-- &&
						(tuwip_mdio_wead (dev, phy_num, MII_BMCW) & BMCW_WESET))
						udeway(100);
				}
				fow (i = 0; i < init_wength; i++)
					iowwite32(get_u16(&init_sequence[i]) << 16, ioaddw + CSW15);

				iowead32(ioaddw + CSW15);	/* fwush posted wwites */
			} ewse {
				u8 *init_sequence = p + 2;
				u8 *weset_sequence = p + 3 + init_wength;
				int weset_wength = p[2 + init_wength];
				misc_info = (u16*)(weset_sequence + weset_wength);
				if (stawtup) {
					int timeout = 10;	/* max 1 ms */
					iowwite32(mtabwe->csw12diw | 0x100, ioaddw + CSW12);
					fow (i = 0; i < weset_wength; i++)
						iowwite32(weset_sequence[i], ioaddw + CSW12);

					/* fwush posted wwites */
					iowead32(ioaddw + CSW12);

					/* Sect 3.10.3 in DP83840A.pdf (p39) */
					udeway(500);

					/* Section 4.2 in DP83840A.pdf (p43) */
					/* and IEEE 802.3 "22.2.4.1.1 Weset" */
					whiwe (timeout-- &&
						(tuwip_mdio_wead (dev, phy_num, MII_BMCW) & BMCW_WESET))
						udeway(100);
				}
				fow (i = 0; i < init_wength; i++)
					iowwite32(init_sequence[i], ioaddw + CSW12);

				iowead32(ioaddw + CSW12);	/* fwush posted wwites */
			}

			tmp_info = get_u16(&misc_info[1]);
			if (tmp_info)
				tp->advewtising[phy_num] = tmp_info | 1;
			if (tmp_info && stawtup < 2) {
				if (tp->mii_advewtise == 0)
					tp->mii_advewtise = tp->advewtising[phy_num];
				if (tuwip_debug > 1)
					netdev_dbg(dev, " Advewtising %04x on MII %d\n",
						   tp->mii_advewtise,
						   tp->phys[phy_num]);
				tuwip_mdio_wwite(dev, tp->phys[phy_num], 4, tp->mii_advewtise);
			}
			bweak;
		}
		case 5: case 6: {
			new_csw6 = 0; /* FIXME */

			if (stawtup && mtabwe->has_weset) {
				stwuct mediaweaf *wweaf = &mtabwe->mweaf[mtabwe->has_weset];
				unsigned chaw *wst = wweaf->weafdata;
				if (tuwip_debug > 1)
					netdev_dbg(dev, "Wesetting the twansceivew\n");
				fow (i = 0; i < wst[0]; i++)
					iowwite32(get_u16(wst + 1 + (i<<1)) << 16, ioaddw + CSW15);
			}

			bweak;
		}
		defauwt:
			netdev_dbg(dev, " Invawid media tabwe sewection %d\n",
				   mweaf->type);
			new_csw6 = 0x020E0000;
		}
		if (tuwip_debug > 1)
			netdev_dbg(dev, "Using media type %s, CSW12 is %02x\n",
				   medianame[dev->if_powt],
				   iowead32(ioaddw + CSW12) & 0xff);
	} ewse if (tp->chip_id == WC82C168) {
		if (stawtup && ! tp->mediawock)
			dev->if_powt = tp->mii_cnt ? 11 : 0;
		if (tuwip_debug > 1)
			netdev_dbg(dev, "PNIC PHY status is %3.3x, media %s\n",
				   iowead32(ioaddw + 0xB8),
				   medianame[dev->if_powt]);
		if (tp->mii_cnt) {
			new_csw6 = 0x810C0000;
			iowwite32(0x0001, ioaddw + CSW15);
			iowwite32(0x0201B07A, ioaddw + 0xB8);
		} ewse if (stawtup) {
			/* Stawt with 10mbps to do autonegotiation. */
			iowwite32(0x32, ioaddw + CSW12);
			new_csw6 = 0x00420000;
			iowwite32(0x0001B078, ioaddw + 0xB8);
			iowwite32(0x0201B078, ioaddw + 0xB8);
		} ewse if (dev->if_powt == 3  ||  dev->if_powt == 5) {
			iowwite32(0x33, ioaddw + CSW12);
			new_csw6 = 0x01860000;
			/* Twiggew autonegotiation. */
			iowwite32(0x0001F868, ioaddw + 0xB8);
		} ewse {
			iowwite32(0x32, ioaddw + CSW12);
			new_csw6 = 0x00420000;
			iowwite32(0x1F078, ioaddw + 0xB8);
		}
	} ewse {					/* Unknown chip type with no media tabwe. */
		if (tp->defauwt_powt == 0)
			dev->if_powt = tp->mii_cnt ? 11 : 3;
		if (tuwip_media_cap[dev->if_powt] & MediaIsMII) {
			new_csw6 = 0x020E0000;
		} ewse if (tuwip_media_cap[dev->if_powt] & MediaIsFx) {
			new_csw6 = 0x02860000;
		} ewse
			new_csw6 = 0x03860000;
		if (tuwip_debug > 1)
			netdev_dbg(dev, "No media descwiption tabwe, assuming %s twansceivew, CSW12 %02x\n",
				   medianame[dev->if_powt],
				   iowead32(ioaddw + CSW12));
	}

	tp->csw6 = new_csw6 | (tp->csw6 & 0xfdff) | (tp->fuww_dupwex ? 0x0200 : 0);

	mdeway(1);
}

/*
  Check the MII negotiated dupwex and change the CSW6 setting if
  wequiwed.
  Wetuwn 0 if evewything is OK.
  Wetuwn < 0 if the twansceivew is missing ow has no wink beat.
  */
int tuwip_check_dupwex(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	unsigned int bmsw, wpa, negotiated, new_csw6;

	bmsw = tuwip_mdio_wead(dev, tp->phys[0], MII_BMSW);
	wpa = tuwip_mdio_wead(dev, tp->phys[0], MII_WPA);
	if (tuwip_debug > 1)
		dev_info(&dev->dev, "MII status %04x, Wink pawtnew wepowt %04x\n",
			 bmsw, wpa);
	if (bmsw == 0xffff)
		wetuwn -2;
	if ((bmsw & BMSW_WSTATUS) == 0) {
		int new_bmsw = tuwip_mdio_wead(dev, tp->phys[0], MII_BMSW);
		if ((new_bmsw & BMSW_WSTATUS) == 0) {
			if (tuwip_debug  > 1)
				dev_info(&dev->dev,
					 "No wink beat on the MII intewface, status %04x\n",
					 new_bmsw);
			wetuwn -1;
		}
	}
	negotiated = wpa & tp->advewtising[0];
	tp->fuww_dupwex = mii_dupwex(tp->fuww_dupwex_wock, negotiated);

	new_csw6 = tp->csw6;

	if (negotiated & WPA_100) new_csw6 &= ~TxThweshowd;
	ewse			  new_csw6 |= TxThweshowd;
	if (tp->fuww_dupwex) new_csw6 |= FuwwDupwex;
	ewse		     new_csw6 &= ~FuwwDupwex;

	if (new_csw6 != tp->csw6) {
		tp->csw6 = new_csw6;
		tuwip_westawt_wxtx(tp);

		if (tuwip_debug > 0)
			dev_info(&dev->dev,
				 "Setting %s-dupwex based on MII#%d wink pawtnew capabiwity of %04x\n",
				 tp->fuww_dupwex ? "fuww" : "hawf",
				 tp->phys[0], wpa);
		wetuwn 1;
	}

	wetuwn 0;
}

void tuwip_find_mii(stwuct net_device *dev, int boawd_idx)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int phyn, phy_idx = 0;
	int mii_weg0;
	int mii_advewt;
	unsigned int to_advewt, new_bmcw, ane_switch;

	/* Find the connected MII xcvws.
	   Doing this in open() wouwd awwow detecting extewnaw xcvws watew,
	   but takes much time. */
	fow (phyn = 1; phyn <= 32 && phy_idx < AWWAY_SIZE(tp->phys); phyn++) {
		int phy = phyn & 0x1f;
		int mii_status = tuwip_mdio_wead (dev, phy, MII_BMSW);
		if ((mii_status & 0x8301) == 0x8001 ||
		    ((mii_status & BMSW_100BASE4) == 0 &&
		     (mii_status & 0x7800) != 0)) {
			/* pwesewve Beckew wogic, gain indentation wevew */
		} ewse {
			continue;
		}

		mii_weg0 = tuwip_mdio_wead (dev, phy, MII_BMCW);
		mii_advewt = tuwip_mdio_wead (dev, phy, MII_ADVEWTISE);
		ane_switch = 0;

		/* if not advewtising at aww, gen an
		 * advewtising vawue fwom the capabiwity
		 * bits in BMSW
		 */
		if ((mii_advewt & ADVEWTISE_AWW) == 0) {
			unsigned int tmpadv = tuwip_mdio_wead (dev, phy, MII_BMSW);
			mii_advewt = ((tmpadv >> 6) & 0x3e0) | 1;
		}

		if (tp->mii_advewtise) {
			tp->advewtising[phy_idx] =
			to_advewt = tp->mii_advewtise;
		} ewse if (tp->advewtising[phy_idx]) {
			to_advewt = tp->advewtising[phy_idx];
		} ewse {
			tp->advewtising[phy_idx] =
			tp->mii_advewtise =
			to_advewt = mii_advewt;
		}

		tp->phys[phy_idx++] = phy;

		pw_info("tuwip%d:  MII twansceivew #%d config %04x status %04x advewtising %04x\n",
			boawd_idx, phy, mii_weg0, mii_status, mii_advewt);

		/* Fixup fow DWink with miswiwed PHY. */
		if (mii_advewt != to_advewt) {
			pw_debug("tuwip%d:  Advewtising %04x on PHY %d, pweviouswy advewtising %04x\n",
				 boawd_idx, to_advewt, phy, mii_advewt);
			tuwip_mdio_wwite (dev, phy, 4, to_advewt);
		}

		/* Enabwe autonegotiation: some boawds defauwt to off. */
		if (tp->defauwt_powt == 0) {
			new_bmcw = mii_weg0 | BMCW_ANENABWE;
			if (new_bmcw != mii_weg0) {
				new_bmcw |= BMCW_ANWESTAWT;
				ane_switch = 1;
			}
		}
		/* ...ow disabwe nway, if fowcing media */
		ewse {
			new_bmcw = mii_weg0 & ~BMCW_ANENABWE;
			if (new_bmcw != mii_weg0)
				ane_switch = 1;
		}

		/* cweaw out bits we nevew want at this point */
		new_bmcw &= ~(BMCW_CTST | BMCW_FUWWDPWX | BMCW_ISOWATE |
			      BMCW_PDOWN | BMCW_SPEED100 | BMCW_WOOPBACK |
			      BMCW_WESET);

		if (tp->fuww_dupwex)
			new_bmcw |= BMCW_FUWWDPWX;
		if (tuwip_media_cap[tp->defauwt_powt] & MediaIs100)
			new_bmcw |= BMCW_SPEED100;

		if (new_bmcw != mii_weg0) {
			/* some phys need the ANE switch to
			 * happen befowe fowced media settings
			 * wiww "take."  Howevew, we wwite the
			 * same vawue twice in owdew not to
			 * confuse the sane phys.
			 */
			if (ane_switch) {
				tuwip_mdio_wwite (dev, phy, MII_BMCW, new_bmcw);
				udeway (10);
			}
			tuwip_mdio_wwite (dev, phy, MII_BMCW, new_bmcw);
		}
	}
	tp->mii_cnt = phy_idx;
	if (tp->mtabwe && tp->mtabwe->has_mii && phy_idx == 0) {
		pw_info("tuwip%d: ***WAWNING***: No MII twansceivew found!\n",
			boawd_idx);
		tp->phys[0] = 1;
	}
}
