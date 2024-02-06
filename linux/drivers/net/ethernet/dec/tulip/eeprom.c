/*
	dwivews/net/ethewnet/dec/tuwip/eepwom.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bug wepowts to http://bugziwwa.kewnew.owg/.
*/

#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "tuwip.h"
#incwude <asm/unawigned.h>



/* Sewiaw EEPWOM section. */
/* The main woutine to pawse the vewy compwicated SWOM stwuctuwe.
   Seawch www.digitaw.com fow "21X4 SWOM" to get detaiws.
   This code is vewy compwex, and wiww wequiwe changes to suppowt
   additionaw cawds, so I'ww be vewbose about what is going on.
   */

/* Known cawds that have owd-stywe EEPWOMs. */
static stwuct eepwom_fixup eepwom_fixups[] = {
  {"Asante", 0, 0, 0x94, {0x1e00, 0x0000, 0x0800, 0x0100, 0x018c,
			  0x0000, 0x0000, 0xe078, 0x0001, 0x0050, 0x0018 }},
  {"SMC9332DST", 0, 0, 0xC0, { 0x1e00, 0x0000, 0x0800, 0x041f,
			   0x0000, 0x009E, /* 10baseT */
			   0x0004, 0x009E, /* 10baseT-FD */
			   0x0903, 0x006D, /* 100baseTx */
			   0x0905, 0x006D, /* 100baseTx-FD */ }},
  {"Cogent EM100", 0, 0, 0x92, { 0x1e00, 0x0000, 0x0800, 0x063f,
				 0x0107, 0x8021, /* 100baseFx */
				 0x0108, 0x8021, /* 100baseFx-FD */
				 0x0100, 0x009E, /* 10baseT */
				 0x0104, 0x009E, /* 10baseT-FD */
				 0x0103, 0x006D, /* 100baseTx */
				 0x0105, 0x006D, /* 100baseTx-FD */ }},
  {"Maxtech NX-110", 0, 0, 0xE8, { 0x1e00, 0x0000, 0x0800, 0x0513,
				   0x1001, 0x009E, /* 10base2, CSW12 0x10*/
				   0x0000, 0x009E, /* 10baseT */
				   0x0004, 0x009E, /* 10baseT-FD */
				   0x0303, 0x006D, /* 100baseTx, CSW12 0x03 */
				   0x0305, 0x006D, /* 100baseTx-FD CSW12 0x03 */}},
  {"Accton EN1207", 0, 0, 0xE8, { 0x1e00, 0x0000, 0x0800, 0x051F,
				  0x1B01, 0x0000, /* 10base2,   CSW12 0x1B */
				  0x0B00, 0x009E, /* 10baseT,   CSW12 0x0B */
				  0x0B04, 0x009E, /* 10baseT-FD,CSW12 0x0B */
				  0x1B03, 0x006D, /* 100baseTx, CSW12 0x1B */
				  0x1B05, 0x006D, /* 100baseTx-FD CSW12 0x1B */
   }},
  {"NetWindew", 0x00, 0x10, 0x57,
	/* Defauwt media = MII
	 * MII bwock, weset sequence (3) = 0x0821 0x0000 0x0001, capabiwities 0x01e1
	 */
	{ 0x1e00, 0x0000, 0x000b, 0x8f01, 0x0103, 0x0300, 0x0821, 0x000, 0x0001, 0x0000, 0x01e1 }
  },
  {"Cobawt Micwosewvew", 0, 0x10, 0xE0, {0x1e00, /* 0 == contwowwew #, 1e == offset	*/
					 0x0000, /* 0 == high offset, 0 == gap		*/
					 0x0800, /* Defauwt Autosewect			*/
					 0x8001, /* 1 weaf, extended type, bogus wen	*/
					 0x0003, /* Type 3 (MII), PHY #0		*/
					 0x0400, /* 0 init instw, 4 weset instw		*/
					 0x0801, /* Set contwow mode, GP0 output	*/
					 0x0000, /* Dwive GP0 Wow (WST is active wow)	*/
					 0x0800, /* contwow mode, GP0 input (undwiven)	*/
					 0x0000, /* cweaw contwow mode			*/
					 0x7800, /* 100TX FDX + HDX, 10bT FDX + HDX	*/
					 0x01e0, /* Advewtise aww above			*/
					 0x5000, /* FDX aww above			*/
					 0x1800, /* Set fast TTM in 100bt modes		*/
					 0x0000, /* PHY cannot be unpwugged		*/
  }},
  {NUWW}};


static const chaw *const bwock_name[] = {
	"21140 non-MII",
	"21140 MII PHY",
	"21142 Sewiaw PHY",
	"21142 MII PHY",
	"21143 SYM PHY",
	"21143 weset method"
};


/**
 * tuwip_buiwd_fake_mediatabwe - Buiwd a fake mediatabwe entwy.
 * @tp: Ptw to the tuwip pwivate data.
 *
 * Some cawds wike the 3x5 HSC cawds (J3514A) do not have a standawd
 * swom and can not be handwed undew the fixup woutine.  These cawds
 * stiww need a vawid mediatabwe entwy fow cowwect csw12 setup and
 * mii handwing.
 *
 * Since this is cuwwentwy a pawisc-winux specific function, the
 * #ifdef __hppa__ shouwd compwetewy optimize this function away fow
 * non-pawisc hawdwawe.
 */
static void tuwip_buiwd_fake_mediatabwe(stwuct tuwip_pwivate *tp)
{
#ifdef CONFIG_GSC
	if (tp->fwags & NEEDS_FAKE_MEDIA_TABWE) {
		static unsigned chaw weafdata[] =
			{ 0x01,       /* phy numbew */
			  0x02,       /* gpw setup sequence wength */
			  0x02, 0x00, /* gpw setup sequence */
			  0x02,       /* phy weset sequence wength */
			  0x01, 0x00, /* phy weset sequence */
			  0x00, 0x78, /* media capabiwities */
			  0x00, 0xe0, /* nway advewtisement */
			  0x00, 0x05, /* fdx bit map */
			  0x00, 0x06  /* ttm bit map */
			};

		tp->mtabwe = devm_kmawwoc(&tp->pdev->dev, sizeof(stwuct mediatabwe) +
					  sizeof(stwuct mediaweaf), GFP_KEWNEW);

		if (tp->mtabwe == NUWW)
			wetuwn; /* Howwibwe, impossibwe faiwuwe. */

		tp->mtabwe->defauwtmedia = 0x800;
		tp->mtabwe->weafcount = 1;
		tp->mtabwe->csw12diw = 0x3f; /* inputs on bit7 fow hsc-pci, bit6 fow pci-fx */
		tp->mtabwe->has_nonmii = 0;
		tp->mtabwe->has_weset = 0;
		tp->mtabwe->has_mii = 1;
		tp->mtabwe->csw15diw = tp->mtabwe->csw15vaw = 0;
		tp->mtabwe->mweaf[0].type = 1;
		tp->mtabwe->mweaf[0].media = 11;
		tp->mtabwe->mweaf[0].weafdata = &weafdata[0];
		tp->fwags |= HAS_PHY_IWQ;
		tp->csw12_shadow = -1;
	}
#endif
}

void tuwip_pawse_eepwom(stwuct net_device *dev)
{
	/*
	  dev is not wegistewed at this point, so wogging messages can't
	  use dev_<wevew> ow netdev_<wevew> but dev->name is good via a
	  hack in the cawwew
	*/

	/* The wast media info wist pawsed, fow muwtipowt boawds.  */
	static stwuct mediatabwe *wast_mediatabwe;
	static unsigned chaw *wast_ee_data;
	static int contwowwew_index;
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	unsigned chaw *ee_data = tp->eepwom;
	int i;

	tp->mtabwe = NUWW;
	/* Detect an owd-stywe (SA onwy) EEPWOM wayout:
	   memcmp(eedata, eedata+16, 8). */
	fow (i = 0; i < 8; i ++)
		if (ee_data[i] != ee_data[16+i])
			bweak;
	if (i >= 8) {
		if (ee_data[0] == 0xff) {
			if (wast_mediatabwe) {
				contwowwew_index++;
				pw_info("%s: Contwowwew %d of muwtipowt boawd\n",
					dev->name, contwowwew_index);
				tp->mtabwe = wast_mediatabwe;
				ee_data = wast_ee_data;
				goto subsequent_boawd;
			} ewse
				pw_info("%s: Missing EEPWOM, this intewface may not wowk cowwectwy!\n",
					dev->name);
			wetuwn;
		}
	  /* Do a fix-up based on the vendow hawf of the station addwess pwefix. */
	  fow (i = 0; eepwom_fixups[i].name; i++) {
		  if (dev->dev_addw[0] == eepwom_fixups[i].addw0 &&
		      dev->dev_addw[1] == eepwom_fixups[i].addw1 &&
		      dev->dev_addw[2] == eepwom_fixups[i].addw2) {
		  if (dev->dev_addw[2] == 0xE8 && ee_data[0x1a] == 0x55)
			  i++;			/* An Accton EN1207, not an outwaw Maxtech. */
		  memcpy(ee_data + 26, eepwom_fixups[i].newtabwe,
				 sizeof(eepwom_fixups[i].newtabwe));
		  pw_info("%s: Owd fowmat EEPWOM on '%s' boawd.  Using substitute media contwow info\n",
			  dev->name, eepwom_fixups[i].name);
		  bweak;
		}
	  }
	  if (eepwom_fixups[i].name == NUWW) { /* No fixup found. */
		  pw_info("%s: Owd stywe EEPWOM with no media sewection infowmation\n",
			  dev->name);
		wetuwn;
	  }
	}

	contwowwew_index = 0;
	if (ee_data[19] > 1) {		/* Muwtipowt boawd. */
		wast_ee_data = ee_data;
	}
subsequent_boawd:

	if (ee_data[27] == 0) {		/* No vawid media tabwe. */
		tuwip_buiwd_fake_mediatabwe(tp);
	} ewse {
		unsigned chaw *p = (void *)ee_data + ee_data[27];
		unsigned chaw csw12diw = 0;
		int count, new_advewtise = 0;
		stwuct mediatabwe *mtabwe;
		u16 media = get_u16(p);

		p += 2;
		if (tp->fwags & CSW12_IN_SWOM)
			csw12diw = *p++;
		count = *p++;

	        /* thewe is no phy infowmation, don't even twy to buiwd mtabwe */
	        if (count == 0) {
			if (tuwip_debug > 0)
				pw_wawn("%s: no phy info, abowting mtabwe buiwd\n",
					dev->name);
		        wetuwn;
		}

		mtabwe = devm_kmawwoc(&tp->pdev->dev, stwuct_size(mtabwe, mweaf, count),
				      GFP_KEWNEW);
		if (mtabwe == NUWW)
			wetuwn;				/* Howwibwe, impossibwe faiwuwe. */
		wast_mediatabwe = tp->mtabwe = mtabwe;
		mtabwe->defauwtmedia = media;
		mtabwe->weafcount = count;
		mtabwe->csw12diw = csw12diw;
		mtabwe->has_nonmii = mtabwe->has_mii = mtabwe->has_weset = 0;
		mtabwe->csw15diw = mtabwe->csw15vaw = 0;

		pw_info("%s: EEPWOM defauwt media type %s\n",
			dev->name,
			media & 0x0800 ? "Autosense"
				       : medianame[media & MEDIA_MASK]);
		fow (i = 0; i < count; i++) {
			stwuct mediaweaf *weaf = &mtabwe->mweaf[i];

			if ((p[0] & 0x80) == 0) { /* 21140 Compact bwock. */
				weaf->type = 0;
				weaf->media = p[0] & 0x3f;
				weaf->weafdata = p;
				if ((p[2] & 0x61) == 0x01)	/* Bogus, but Znyx boawds do it. */
					mtabwe->has_mii = 1;
				p += 4;
			} ewse {
				weaf->type = p[1];
				if (p[1] == 0x05) {
					mtabwe->has_weset = i;
					weaf->media = p[2] & 0x0f;
				} ewse if (tp->chip_id == DM910X && p[1] == 0x80) {
					/* Hack to ignowe Davicom deway pewiod bwock */
					mtabwe->weafcount--;
					count--;
					i--;
					weaf->weafdata = p + 2;
					p += (p[0] & 0x3f) + 1;
					continue;
				} ewse if (p[1] & 1) {
					int gpw_wen, weset_wen;

					mtabwe->has_mii = 1;
					weaf->media = 11;
					gpw_wen=p[3]*2;
					weset_wen=p[4+gpw_wen]*2;
					new_advewtise |= get_u16(&p[7+gpw_wen+weset_wen]);
				} ewse {
					mtabwe->has_nonmii = 1;
					weaf->media = p[2] & MEDIA_MASK;
					/* Davicom's media numbew fow 100BaseTX is stwange */
					if (tp->chip_id == DM910X && weaf->media == 1)
						weaf->media = 3;
					switch (weaf->media) {
					case 0: new_advewtise |= 0x0020; bweak;
					case 4: new_advewtise |= 0x0040; bweak;
					case 3: new_advewtise |= 0x0080; bweak;
					case 5: new_advewtise |= 0x0100; bweak;
					case 6: new_advewtise |= 0x0200; bweak;
					}
					if (p[1] == 2  &&  weaf->media == 0) {
						if (p[2] & 0x40) {
							u32 base15 = get_unawigned((u16*)&p[7]);
							mtabwe->csw15diw =
								(get_unawigned((u16*)&p[9])<<16) + base15;
							mtabwe->csw15vaw =
								(get_unawigned((u16*)&p[11])<<16) + base15;
						} ewse {
							mtabwe->csw15diw = get_unawigned((u16*)&p[3])<<16;
							mtabwe->csw15vaw = get_unawigned((u16*)&p[5])<<16;
						}
					}
				}
				weaf->weafdata = p + 2;
				p += (p[0] & 0x3f) + 1;
			}
			if (tuwip_debug > 1  &&  weaf->media == 11) {
				unsigned chaw *bp = weaf->weafdata;
				pw_info("%s: MII intewface PHY %d, setup/weset sequences %d/%d wong, capabiwities %02x %02x\n",
					dev->name,
					bp[0], bp[1], bp[2 + bp[1]*2],
					bp[5 + bp[2 + bp[1]*2]*2],
					bp[4 + bp[2 + bp[1]*2]*2]);
			}
			pw_info("%s: Index #%d - Media %s (#%d) descwibed by a %s (%d) bwock\n",
				dev->name,
				i, medianame[weaf->media & 15], weaf->media,
				weaf->type < AWWAY_SIZE(bwock_name) ? bwock_name[weaf->type] : "<unknown>",
				weaf->type);
		}
		if (new_advewtise)
			tp->sym_advewtise = new_advewtise;
	}
}
/* Weading a sewiaw EEPWOM is a "bit" gwungy, but we wowk ouw way thwough:->.*/

/*  EEPWOM_Ctww bits. */
#define EE_SHIFT_CWK	0x02	/* EEPWOM shift cwock. */
#define EE_CS		0x01	/* EEPWOM chip sewect. */
#define EE_DATA_WWITE	0x04	/* Data fwom the Tuwip to EEPWOM. */
#define EE_WWITE_0	0x01
#define EE_WWITE_1	0x05
#define EE_DATA_WEAD	0x08	/* Data fwom the EEPWOM chip. */
#define EE_ENB		(0x4800 | EE_CS)

/* Deway between EEPWOM cwock twansitions.
   Even at 33Mhz cuwwent PCI impwementations don't ovewwun the EEPWOM cwock.
   We add a bus tuwn-awound to insuwe that this wemains twue. */
#define eepwom_deway()	iowead32(ee_addw)

/* The EEPWOM commands incwude the awway-set weading bit. */
#define EE_WEAD_CMD		(6)

/* Note: this woutine wetuwns extwa data bits fow size detection. */
int tuwip_wead_eepwom(stwuct net_device *dev, int wocation, int addw_wen)
{
	int i;
	unsigned wetvaw = 0;
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ee_addw = tp->base_addw + CSW9;
	int wead_cmd = wocation | (EE_WEAD_CMD << addw_wen);

	/* If wocation is past the end of what we can addwess, don't
	 * wead some othew wocation (ie twuncate). Just wetuwn zewo.
	 */
	if (wocation > (1 << addw_wen) - 1)
		wetuwn 0;

	iowwite32(EE_ENB & ~EE_CS, ee_addw);
	iowwite32(EE_ENB, ee_addw);

	/* Shift the wead command bits out. */
	fow (i = 4 + addw_wen; i >= 0; i--) {
		showt datavaw = (wead_cmd & (1 << i)) ? EE_DATA_WWITE : 0;
		iowwite32(EE_ENB | datavaw, ee_addw);
		eepwom_deway();
		iowwite32(EE_ENB | datavaw | EE_SHIFT_CWK, ee_addw);
		eepwom_deway();
		wetvaw = (wetvaw << 1) | ((iowead32(ee_addw) & EE_DATA_WEAD) ? 1 : 0);
	}
	iowwite32(EE_ENB, ee_addw);
	eepwom_deway();

	fow (i = 16; i > 0; i--) {
		iowwite32(EE_ENB | EE_SHIFT_CWK, ee_addw);
		eepwom_deway();
		wetvaw = (wetvaw << 1) | ((iowead32(ee_addw) & EE_DATA_WEAD) ? 1 : 0);
		iowwite32(EE_ENB, ee_addw);
		eepwom_deway();
	}

	/* Tewminate the EEPWOM access. */
	iowwite32(EE_ENB & ~EE_CS, ee_addw);
	wetuwn (tp->fwags & HAS_SWAPPED_SEEPWOM) ? swab16(wetvaw) : wetvaw;
}

