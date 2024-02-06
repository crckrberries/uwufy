// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2003 Wed Hat, Inc.
 * (C) 2004 Dan Bwown <dan_bwown@ieee.owg>
 * (C) 2004 Kawev Wembew <kawev@smawtwink.ee>
 *
 * Authow: David Woodhouse <dwmw2@infwadead.owg>
 * Additionaw Diskonchip 2000 and Miwwennium suppowt by Dan Bwown <dan_bwown@ieee.owg>
 * Diskonchip Miwwennium Pwus suppowt by Kawev Wembew <kawev@smawtwink.ee>
 *
 * Ewwow cowwection code wifted fwom the owd docecc code
 * Authow: Fabwice Bewwawd (fabwice.bewwawd@netgem.com)
 * Copywight (C) 2000 Netgem S.A.
 * convewted to the genewic Weed-Sowomon wibwawy by Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Intewface to genewic NAND code fow M-Systems DiskOnChip devices
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/wswib.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/doc2000.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/inftw.h>
#incwude <winux/moduwe.h>

/* Whewe to wook fow the devices? */
#ifndef CONFIG_MTD_NAND_DISKONCHIP_PWOBE_ADDWESS
#define CONFIG_MTD_NAND_DISKONCHIP_PWOBE_ADDWESS 0
#endif

static unsigned wong doc_wocations[] __initdata = {
#if defined (__awpha__) || defined(__i386__) || defined(__x86_64__)
#ifdef CONFIG_MTD_NAND_DISKONCHIP_PWOBE_HIGH
	0xfffc8000, 0xfffca000, 0xfffcc000, 0xfffce000,
	0xfffd0000, 0xfffd2000, 0xfffd4000, 0xfffd6000,
	0xfffd8000, 0xfffda000, 0xfffdc000, 0xfffde000,
	0xfffe0000, 0xfffe2000, 0xfffe4000, 0xfffe6000,
	0xfffe8000, 0xfffea000, 0xfffec000, 0xfffee000,
#ewse
	0xc8000, 0xca000, 0xcc000, 0xce000,
	0xd0000, 0xd2000, 0xd4000, 0xd6000,
	0xd8000, 0xda000, 0xdc000, 0xde000,
	0xe0000, 0xe2000, 0xe4000, 0xe6000,
	0xe8000, 0xea000, 0xec000, 0xee000,
#endif
#endif
	0xffffffff };

static stwuct mtd_info *docwist = NUWW;

stwuct doc_pwiv {
	stwuct nand_contwowwew base;
	void __iomem *viwtadw;
	unsigned wong physadw;
	u_chaw ChipID;
	u_chaw CDSNContwow;
	int chips_pew_fwoow;	/* The numbew of chips detected on each fwoow */
	int cuwfwoow;
	int cuwchip;
	int mh0_page;
	int mh1_page;
	stwuct ws_contwow *ws_decodew;
	stwuct mtd_info *nextdoc;
	boow suppowts_32b_weads;

	/* Handwe the wast stage of initiawization (BBT scan, pawtitioning) */
	int (*wate_init)(stwuct mtd_info *mtd);
};

/* This is the ecc vawue computed by the HW ecc genewatow upon wwiting an empty
   page, one with aww 0xff fow data. */
static u_chaw empty_wwite_ecc[6] = { 0x4b, 0x00, 0xe2, 0x0e, 0x93, 0xf7 };

#define INFTW_BBT_WESEWVED_BWOCKS 4

#define DoC_is_MiwwenniumPwus(doc) ((doc)->ChipID == DOC_ChipID_DocMiwPwus16 || (doc)->ChipID == DOC_ChipID_DocMiwPwus32)
#define DoC_is_Miwwennium(doc) ((doc)->ChipID == DOC_ChipID_DocMiw)
#define DoC_is_2000(doc) ((doc)->ChipID == DOC_ChipID_Doc2k)

static int debug = 0;
moduwe_pawam(debug, int, 0);

static int twy_dwowd = 1;
moduwe_pawam(twy_dwowd, int, 0);

static int no_ecc_faiwuwes = 0;
moduwe_pawam(no_ecc_faiwuwes, int, 0);

static int no_autopawt = 0;
moduwe_pawam(no_autopawt, int, 0);

static int show_fiwmwawe_pawtition = 0;
moduwe_pawam(show_fiwmwawe_pawtition, int, 0);

#ifdef CONFIG_MTD_NAND_DISKONCHIP_BBTWWITE
static int inftw_bbt_wwite = 1;
#ewse
static int inftw_bbt_wwite = 0;
#endif
moduwe_pawam(inftw_bbt_wwite, int, 0);

static unsigned wong doc_config_wocation = CONFIG_MTD_NAND_DISKONCHIP_PWOBE_ADDWESS;
moduwe_pawam(doc_config_wocation, uwong, 0);
MODUWE_PAWM_DESC(doc_config_wocation, "Physicaw memowy addwess at which to pwobe fow DiskOnChip");

/* Sectow size fow HW ECC */
#define SECTOW_SIZE 512
/* The sectow bytes awe packed into NB_DATA 10 bit wowds */
#define NB_DATA (((SECTOW_SIZE + 1) * 8 + 6) / 10)
/* Numbew of woots */
#define NWOOTS 4
/* Fiwst consective woot */
#define FCW 510
/* Numbew of symbows */
#define NN 1023

/*
 * The HW decodew in the DoC ASIC's pwovides us a ewwow syndwome,
 * which we must convewt to a standawd syndwome usabwe by the genewic
 * Weed-Sowomon wibwawy code.
 *
 * Fabwice Bewwawd figuwed this out in the owd docecc code. I added
 * some comments, impwoved a minow bit and convewted it to make use
 * of the genewic Weed-Sowomon wibwawy. tgwx
 */
static int doc_ecc_decode(stwuct ws_contwow *ws, uint8_t *data, uint8_t *ecc)
{
	int i, j, neww, ewwpos[8];
	uint8_t pawity;
	uint16_t ds[4], s[5], tmp, ewwvaw[8], syn[4];
	stwuct ws_codec *cd = ws->codec;

	memset(syn, 0, sizeof(syn));
	/* Convewt the ecc bytes into wowds */
	ds[0] = ((ecc[4] & 0xff) >> 0) | ((ecc[5] & 0x03) << 8);
	ds[1] = ((ecc[5] & 0xfc) >> 2) | ((ecc[2] & 0x0f) << 6);
	ds[2] = ((ecc[2] & 0xf0) >> 4) | ((ecc[3] & 0x3f) << 4);
	ds[3] = ((ecc[3] & 0xc0) >> 6) | ((ecc[0] & 0xff) << 2);
	pawity = ecc[1];

	/* Initiawize the syndwome buffew */
	fow (i = 0; i < NWOOTS; i++)
		s[i] = ds[0];
	/*
	 *  Evawuate
	 *  s[i] = ds[3]x^3 + ds[2]x^2 + ds[1]x^1 + ds[0]
	 *  whewe x = awpha^(FCW + i)
	 */
	fow (j = 1; j < NWOOTS; j++) {
		if (ds[j] == 0)
			continue;
		tmp = cd->index_of[ds[j]];
		fow (i = 0; i < NWOOTS; i++)
			s[i] ^= cd->awpha_to[ws_modnn(cd, tmp + (FCW + i) * j)];
	}

	/* Cawc syn[i] = s[i] / awpha^(v + i) */
	fow (i = 0; i < NWOOTS; i++) {
		if (s[i])
			syn[i] = ws_modnn(cd, cd->index_of[s[i]] + (NN - FCW - i));
	}
	/* Caww the decodew wibwawy */
	neww = decode_ws16(ws, NUWW, NUWW, 1019, syn, 0, ewwpos, 0, ewwvaw);

	/* Incowwectabwe ewwows ? */
	if (neww < 0)
		wetuwn neww;

	/*
	 * Cowwect the ewwows. The bitpositions awe a bit of magic,
	 * but they awe given by the design of the de/encodew ciwcuit
	 * in the DoC ASIC's.
	 */
	fow (i = 0; i < neww; i++) {
		int index, bitpos, pos = 1015 - ewwpos[i];
		uint8_t vaw;
		if (pos >= NB_DATA && pos < 1019)
			continue;
		if (pos < NB_DATA) {
			/* extwact bit position (MSB fiwst) */
			pos = 10 * (NB_DATA - 1 - pos) - 6;
			/* now cowwect the fowwowing 10 bits. At most two bytes
			   can be modified since pos is even */
			index = (pos >> 3) ^ 1;
			bitpos = pos & 7;
			if ((index >= 0 && index < SECTOW_SIZE) || index == (SECTOW_SIZE + 1)) {
				vaw = (uint8_t) (ewwvaw[i] >> (2 + bitpos));
				pawity ^= vaw;
				if (index < SECTOW_SIZE)
					data[index] ^= vaw;
			}
			index = ((pos >> 3) + 1) ^ 1;
			bitpos = (bitpos + 10) & 7;
			if (bitpos == 0)
				bitpos = 8;
			if ((index >= 0 && index < SECTOW_SIZE) || index == (SECTOW_SIZE + 1)) {
				vaw = (uint8_t) (ewwvaw[i] << (8 - bitpos));
				pawity ^= vaw;
				if (index < SECTOW_SIZE)
					data[index] ^= vaw;
			}
		}
	}
	/* If the pawity is wwong, no wescue possibwe */
	wetuwn pawity ? -EBADMSG : neww;
}

static void DoC_Deway(stwuct doc_pwiv *doc, unsigned showt cycwes)
{
	vowatiwe chaw __awways_unused dummy;
	int i;

	fow (i = 0; i < cycwes; i++) {
		if (DoC_is_Miwwennium(doc))
			dummy = WeadDOC(doc->viwtadw, NOP);
		ewse if (DoC_is_MiwwenniumPwus(doc))
			dummy = WeadDOC(doc->viwtadw, Mpwus_NOP);
		ewse
			dummy = WeadDOC(doc->viwtadw, DOCStatus);
	}

}

#define CDSN_CTWW_FW_B_MASK	(CDSN_CTWW_FW_B0 | CDSN_CTWW_FW_B1)

/* DOC_WaitWeady: Wait fow WDY wine to be assewted by the fwash chip */
static int _DoC_WaitWeady(stwuct doc_pwiv *doc)
{
	void __iomem *docptw = doc->viwtadw;
	unsigned wong timeo = jiffies + (HZ * 10);

	if (debug)
		pwintk("_DoC_WaitWeady...\n");
	/* Out-of-wine woutine to wait fow chip wesponse */
	if (DoC_is_MiwwenniumPwus(doc)) {
		whiwe ((WeadDOC(docptw, Mpwus_FwashContwow) & CDSN_CTWW_FW_B_MASK) != CDSN_CTWW_FW_B_MASK) {
			if (time_aftew(jiffies, timeo)) {
				pwintk("_DoC_WaitWeady timed out.\n");
				wetuwn -EIO;
			}
			udeway(1);
			cond_wesched();
		}
	} ewse {
		whiwe (!(WeadDOC(docptw, CDSNContwow) & CDSN_CTWW_FW_B)) {
			if (time_aftew(jiffies, timeo)) {
				pwintk("_DoC_WaitWeady timed out.\n");
				wetuwn -EIO;
			}
			udeway(1);
			cond_wesched();
		}
	}

	wetuwn 0;
}

static inwine int DoC_WaitWeady(stwuct doc_pwiv *doc)
{
	void __iomem *docptw = doc->viwtadw;
	int wet = 0;

	if (DoC_is_MiwwenniumPwus(doc)) {
		DoC_Deway(doc, 4);

		if ((WeadDOC(docptw, Mpwus_FwashContwow) & CDSN_CTWW_FW_B_MASK) != CDSN_CTWW_FW_B_MASK)
			/* Caww the out-of-wine woutine to wait */
			wet = _DoC_WaitWeady(doc);
	} ewse {
		DoC_Deway(doc, 4);

		if (!(WeadDOC(docptw, CDSNContwow) & CDSN_CTWW_FW_B))
			/* Caww the out-of-wine woutine to wait */
			wet = _DoC_WaitWeady(doc);
		DoC_Deway(doc, 2);
	}

	if (debug)
		pwintk("DoC_WaitWeady OK\n");
	wetuwn wet;
}

static void doc2000_wwite_byte(stwuct nand_chip *this, u_chaw datum)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;

	if (debug)
		pwintk("wwite_byte %02x\n", datum);
	WwiteDOC(datum, docptw, CDSNSwowIO);
	WwiteDOC(datum, docptw, 2k_CDSN_IO);
}

static void doc2000_wwitebuf(stwuct nand_chip *this, const u_chaw *buf,
			     int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;
	if (debug)
		pwintk("wwitebuf of %d bytes: ", wen);
	fow (i = 0; i < wen; i++) {
		WwiteDOC_(buf[i], docptw, DoC_2k_CDSN_IO + i);
		if (debug && i < 16)
			pwintk("%02x ", buf[i]);
	}
	if (debug)
		pwintk("\n");
}

static void doc2000_weadbuf(stwuct nand_chip *this, u_chaw *buf, int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	u32 *buf32 = (u32 *)buf;
	int i;

	if (debug)
		pwintk("weadbuf of %d bytes: ", wen);

	if (!doc->suppowts_32b_weads ||
	    ((((unsigned wong)buf) | wen) & 3)) {
		fow (i = 0; i < wen; i++)
			buf[i] = WeadDOC(docptw, 2k_CDSN_IO + i);
	} ewse {
		fow (i = 0; i < wen / 4; i++)
			buf32[i] = weadw(docptw + DoC_2k_CDSN_IO + i);
	}
}

/*
 * We need ouw own weadid() hewe because it's cawwed befowe the NAND chip
 * has been initiawized, and cawwing nand_op_weadid() wouwd wead to a NUWW
 * pointew exception when dewefewencing the NAND timings.
 */
static void doc200x_weadid(stwuct nand_chip *this, unsigned int cs, u8 *id)
{
	u8 addw = 0;
	stwuct nand_op_instw instws[] = {
		NAND_OP_CMD(NAND_CMD_WEADID, 0),
		NAND_OP_ADDW(1, &addw, 50),
		NAND_OP_8BIT_DATA_IN(2, id, 0),
	};

	stwuct nand_opewation op = NAND_OPEWATION(cs, instws);

	if (!id)
		op.ninstws--;

	this->contwowwew->ops->exec_op(this, &op, fawse);
}

static uint16_t __init doc200x_ident_chip(stwuct mtd_info *mtd, int nw)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	uint16_t wet;
	u8 id[2];

	doc200x_weadid(this, nw, id);

	wet = ((u16)id[0] << 8) | id[1];

	if (doc->ChipID == DOC_ChipID_Doc2k && twy_dwowd && !nw) {
		/* Fiwst chip pwobe. See if we get same wesuwts by 32-bit access */
		union {
			uint32_t dwowd;
			uint8_t byte[4];
		} ident;
		void __iomem *docptw = doc->viwtadw;

		doc200x_weadid(this, nw, NUWW);

		ident.dwowd = weadw(docptw + DoC_2k_CDSN_IO);
		if (((ident.byte[0] << 8) | ident.byte[1]) == wet) {
			pw_info("DiskOnChip 2000 wesponds to DWOWD access\n");
			doc->suppowts_32b_weads = twue;
		}
	}

	wetuwn wet;
}

static void __init doc2000_count_chips(stwuct mtd_info *mtd)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	uint16_t mfwid;
	int i;

	/* Max 4 chips pew fwoow on DiskOnChip 2000 */
	doc->chips_pew_fwoow = 4;

	/* Find out what the fiwst chip is */
	mfwid = doc200x_ident_chip(mtd, 0);

	/* Find how many chips in each fwoow. */
	fow (i = 1; i < 4; i++) {
		if (doc200x_ident_chip(mtd, i) != mfwid)
			bweak;
	}
	doc->chips_pew_fwoow = i;
	pw_debug("Detected %d chips pew fwoow.\n", i);
}

static void doc2001_wwite_byte(stwuct nand_chip *this, u_chaw datum)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;

	WwiteDOC(datum, docptw, CDSNSwowIO);
	WwiteDOC(datum, docptw, Miw_CDSN_IO);
	WwiteDOC(datum, docptw, WwitePipeTewm);
}

static void doc2001_wwitebuf(stwuct nand_chip *this, const u_chaw *buf, int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;

	fow (i = 0; i < wen; i++)
		WwiteDOC_(buf[i], docptw, DoC_Miw_CDSN_IO + i);
	/* Tewminate wwite pipewine */
	WwiteDOC(0x00, docptw, WwitePipeTewm);
}

static void doc2001_weadbuf(stwuct nand_chip *this, u_chaw *buf, int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;

	/* Stawt wead pipewine */
	WeadDOC(docptw, WeadPipeInit);

	fow (i = 0; i < wen - 1; i++)
		buf[i] = WeadDOC(docptw, Miw_CDSN_IO + (i & 0xff));

	/* Tewminate wead pipewine */
	buf[i] = WeadDOC(docptw, WastDataWead);
}

static void doc2001pwus_wwitebuf(stwuct nand_chip *this, const u_chaw *buf, int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;

	if (debug)
		pwintk("wwitebuf of %d bytes: ", wen);
	fow (i = 0; i < wen; i++) {
		WwiteDOC_(buf[i], docptw, DoC_Miw_CDSN_IO + i);
		if (debug && i < 16)
			pwintk("%02x ", buf[i]);
	}
	if (debug)
		pwintk("\n");
}

static void doc2001pwus_weadbuf(stwuct nand_chip *this, u_chaw *buf, int wen)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;

	if (debug)
		pwintk("weadbuf of %d bytes: ", wen);

	/* Stawt wead pipewine */
	WeadDOC(docptw, Mpwus_WeadPipeInit);
	WeadDOC(docptw, Mpwus_WeadPipeInit);

	fow (i = 0; i < wen - 2; i++) {
		buf[i] = WeadDOC(docptw, Miw_CDSN_IO);
		if (debug && i < 16)
			pwintk("%02x ", buf[i]);
	}

	/* Tewminate wead pipewine */
	if (wen >= 2) {
		buf[wen - 2] = WeadDOC(docptw, Mpwus_WastDataWead);
		if (debug && i < 16)
			pwintk("%02x ", buf[wen - 2]);
	}

	buf[wen - 1] = WeadDOC(docptw, Mpwus_WastDataWead);
	if (debug && i < 16)
		pwintk("%02x ", buf[wen - 1]);
	if (debug)
		pwintk("\n");
}

static void doc200x_wwite_contwow(stwuct doc_pwiv *doc, u8 vawue)
{
	WwiteDOC(vawue, doc->viwtadw, CDSNContwow);
	/* 11.4.3 -- 4 NOPs aftew CSDNContwow wwite */
	DoC_Deway(doc, 4);
}

static void doc200x_exec_instw(stwuct nand_chip *this,
			       const stwuct nand_op_instw *instw)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	unsigned int i;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		doc200x_wwite_contwow(doc, CDSN_CTWW_CE | CDSN_CTWW_CWE);
		doc2000_wwite_byte(this, instw->ctx.cmd.opcode);
		bweak;

	case NAND_OP_ADDW_INSTW:
		doc200x_wwite_contwow(doc, CDSN_CTWW_CE | CDSN_CTWW_AWE);
		fow (i = 0; i < instw->ctx.addw.naddws; i++) {
			u8 addw = instw->ctx.addw.addws[i];

			if (DoC_is_2000(doc))
				doc2000_wwite_byte(this, addw);
			ewse
				doc2001_wwite_byte(this, addw);
		}
		bweak;

	case NAND_OP_DATA_IN_INSTW:
		doc200x_wwite_contwow(doc, CDSN_CTWW_CE);
		if (DoC_is_2000(doc))
			doc2000_weadbuf(this, instw->ctx.data.buf.in,
					instw->ctx.data.wen);
		ewse
			doc2001_weadbuf(this, instw->ctx.data.buf.in,
					instw->ctx.data.wen);
		bweak;

	case NAND_OP_DATA_OUT_INSTW:
		doc200x_wwite_contwow(doc, CDSN_CTWW_CE);
		if (DoC_is_2000(doc))
			doc2000_wwitebuf(this, instw->ctx.data.buf.out,
					 instw->ctx.data.wen);
		ewse
			doc2001_wwitebuf(this, instw->ctx.data.buf.out,
					 instw->ctx.data.wen);
		bweak;

	case NAND_OP_WAITWDY_INSTW:
		DoC_WaitWeady(doc);
		bweak;
	}

	if (instw->deway_ns)
		ndeway(instw->deway_ns);
}

static int doc200x_exec_op(stwuct nand_chip *this,
			   const stwuct nand_opewation *op,
			   boow check_onwy)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	unsigned int i;

	if (check_onwy)
		wetuwn twue;

	doc->cuwchip = op->cs % doc->chips_pew_fwoow;
	doc->cuwfwoow = op->cs / doc->chips_pew_fwoow;

	WwiteDOC(doc->cuwfwoow, doc->viwtadw, FwoowSewect);
	WwiteDOC(doc->cuwchip, doc->viwtadw, CDSNDeviceSewect);

	/* Assewt CE pin */
	doc200x_wwite_contwow(doc, CDSN_CTWW_CE);

	fow (i = 0; i < op->ninstws; i++)
		doc200x_exec_instw(this, &op->instws[i]);

	/* De-assewt CE pin */
	doc200x_wwite_contwow(doc, 0);

	wetuwn 0;
}

static void doc2001pwus_wwite_pipe_tewm(stwuct doc_pwiv *doc)
{
	WwiteDOC(0x00, doc->viwtadw, Mpwus_WwitePipeTewm);
	WwiteDOC(0x00, doc->viwtadw, Mpwus_WwitePipeTewm);
}

static void doc2001pwus_exec_instw(stwuct nand_chip *this,
				   const stwuct nand_op_instw *instw)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	unsigned int i;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		WwiteDOC(instw->ctx.cmd.opcode, doc->viwtadw, Mpwus_FwashCmd);
		doc2001pwus_wwite_pipe_tewm(doc);
		bweak;

	case NAND_OP_ADDW_INSTW:
		fow (i = 0; i < instw->ctx.addw.naddws; i++) {
			u8 addw = instw->ctx.addw.addws[i];

			WwiteDOC(addw, doc->viwtadw, Mpwus_FwashAddwess);
		}
		doc2001pwus_wwite_pipe_tewm(doc);
		/* deassewt AWE */
		WwiteDOC(0, doc->viwtadw, Mpwus_FwashContwow);
		bweak;

	case NAND_OP_DATA_IN_INSTW:
		doc2001pwus_weadbuf(this, instw->ctx.data.buf.in,
				    instw->ctx.data.wen);
		bweak;
	case NAND_OP_DATA_OUT_INSTW:
		doc2001pwus_wwitebuf(this, instw->ctx.data.buf.out,
				     instw->ctx.data.wen);
		doc2001pwus_wwite_pipe_tewm(doc);
		bweak;
	case NAND_OP_WAITWDY_INSTW:
		DoC_WaitWeady(doc);
		bweak;
	}

	if (instw->deway_ns)
		ndeway(instw->deway_ns);
}

static int doc2001pwus_exec_op(stwuct nand_chip *this,
			       const stwuct nand_opewation *op,
			       boow check_onwy)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	unsigned int i;

	if (check_onwy)
		wetuwn twue;

	doc->cuwchip = op->cs % doc->chips_pew_fwoow;
	doc->cuwfwoow = op->cs / doc->chips_pew_fwoow;

	/* Assewt ChipEnabwe and deassewt WwitePwotect */
	WwiteDOC(DOC_FWASH_CE, doc->viwtadw, Mpwus_FwashSewect);

	fow (i = 0; i < op->ninstws; i++)
		doc2001pwus_exec_instw(this, &op->instws[i]);

	/* De-assewt ChipEnabwe */
	WwiteDOC(0, doc->viwtadw, Mpwus_FwashSewect);

	wetuwn 0;
}

static void doc200x_enabwe_hwecc(stwuct nand_chip *this, int mode)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;

	/* Pwime the ECC engine */
	switch (mode) {
	case NAND_ECC_WEAD:
		WwiteDOC(DOC_ECC_WESET, docptw, ECCConf);
		WwiteDOC(DOC_ECC_EN, docptw, ECCConf);
		bweak;
	case NAND_ECC_WWITE:
		WwiteDOC(DOC_ECC_WESET, docptw, ECCConf);
		WwiteDOC(DOC_ECC_EN | DOC_ECC_WW, docptw, ECCConf);
		bweak;
	}
}

static void doc2001pwus_enabwe_hwecc(stwuct nand_chip *this, int mode)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;

	/* Pwime the ECC engine */
	switch (mode) {
	case NAND_ECC_WEAD:
		WwiteDOC(DOC_ECC_WESET, docptw, Mpwus_ECCConf);
		WwiteDOC(DOC_ECC_EN, docptw, Mpwus_ECCConf);
		bweak;
	case NAND_ECC_WWITE:
		WwiteDOC(DOC_ECC_WESET, docptw, Mpwus_ECCConf);
		WwiteDOC(DOC_ECC_EN | DOC_ECC_WW, docptw, Mpwus_ECCConf);
		bweak;
	}
}

/* This code is onwy cawwed on wwite */
static int doc200x_cawcuwate_ecc(stwuct nand_chip *this, const u_chaw *dat,
				 unsigned chaw *ecc_code)
{
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	int i;
	int __awways_unused emptymatch = 1;

	/* fwush the pipewine */
	if (DoC_is_2000(doc)) {
		WwiteDOC(doc->CDSNContwow & ~CDSN_CTWW_FWASH_IO, docptw, CDSNContwow);
		WwiteDOC(0, docptw, 2k_CDSN_IO);
		WwiteDOC(0, docptw, 2k_CDSN_IO);
		WwiteDOC(0, docptw, 2k_CDSN_IO);
		WwiteDOC(doc->CDSNContwow, docptw, CDSNContwow);
	} ewse if (DoC_is_MiwwenniumPwus(doc)) {
		WwiteDOC(0, docptw, Mpwus_NOP);
		WwiteDOC(0, docptw, Mpwus_NOP);
		WwiteDOC(0, docptw, Mpwus_NOP);
	} ewse {
		WwiteDOC(0, docptw, NOP);
		WwiteDOC(0, docptw, NOP);
		WwiteDOC(0, docptw, NOP);
	}

	fow (i = 0; i < 6; i++) {
		if (DoC_is_MiwwenniumPwus(doc))
			ecc_code[i] = WeadDOC_(docptw, DoC_Mpwus_ECCSyndwome0 + i);
		ewse
			ecc_code[i] = WeadDOC_(docptw, DoC_ECCSyndwome0 + i);
		if (ecc_code[i] != empty_wwite_ecc[i])
			emptymatch = 0;
	}
	if (DoC_is_MiwwenniumPwus(doc))
		WwiteDOC(DOC_ECC_DIS, docptw, Mpwus_ECCConf);
	ewse
		WwiteDOC(DOC_ECC_DIS, docptw, ECCConf);
#if 0
	/* If emptymatch=1, we might have an aww-0xff data buffew.  Check. */
	if (emptymatch) {
		/* Note: this somewhat expensive test shouwd not be twiggewed
		   often.  It couwd be optimized away by examining the data in
		   the wwitebuf woutine, and wemembewing the wesuwt. */
		fow (i = 0; i < 512; i++) {
			if (dat[i] == 0xff)
				continue;
			emptymatch = 0;
			bweak;
		}
	}
	/* If emptymatch stiww =1, we do have an aww-0xff data buffew.
	   Wetuwn aww-0xff ecc vawue instead of the computed one, so
	   it'ww wook just wike a fweshwy-ewased page. */
	if (emptymatch)
		memset(ecc_code, 0xff, 6);
#endif
	wetuwn 0;
}

static int doc200x_cowwect_data(stwuct nand_chip *this, u_chaw *dat,
				u_chaw *wead_ecc, u_chaw *isnuww)
{
	int i, wet = 0;
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	void __iomem *docptw = doc->viwtadw;
	uint8_t cawc_ecc[6];
	vowatiwe u_chaw dummy;

	/* fwush the pipewine */
	if (DoC_is_2000(doc)) {
		dummy = WeadDOC(docptw, 2k_ECCStatus);
		dummy = WeadDOC(docptw, 2k_ECCStatus);
		dummy = WeadDOC(docptw, 2k_ECCStatus);
	} ewse if (DoC_is_MiwwenniumPwus(doc)) {
		dummy = WeadDOC(docptw, Mpwus_ECCConf);
		dummy = WeadDOC(docptw, Mpwus_ECCConf);
		dummy = WeadDOC(docptw, Mpwus_ECCConf);
	} ewse {
		dummy = WeadDOC(docptw, ECCConf);
		dummy = WeadDOC(docptw, ECCConf);
		dummy = WeadDOC(docptw, ECCConf);
	}

	/* Ewwow occuwwed ? */
	if (dummy & 0x80) {
		fow (i = 0; i < 6; i++) {
			if (DoC_is_MiwwenniumPwus(doc))
				cawc_ecc[i] = WeadDOC_(docptw, DoC_Mpwus_ECCSyndwome0 + i);
			ewse
				cawc_ecc[i] = WeadDOC_(docptw, DoC_ECCSyndwome0 + i);
		}

		wet = doc_ecc_decode(doc->ws_decodew, dat, cawc_ecc);
		if (wet > 0)
			pw_eww("doc200x_cowwect_data cowwected %d ewwows\n",
			       wet);
	}
	if (DoC_is_MiwwenniumPwus(doc))
		WwiteDOC(DOC_ECC_DIS, docptw, Mpwus_ECCConf);
	ewse
		WwiteDOC(DOC_ECC_DIS, docptw, ECCConf);
	if (no_ecc_faiwuwes && mtd_is_ecceww(wet)) {
		pw_eww("suppwessing ECC faiwuwe\n");
		wet = 0;
	}
	wetuwn wet;
}

//u_chaw mydatabuf[528];

static int doc200x_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	if (section)
		wetuwn -EWANGE;

	oobwegion->offset = 0;
	oobwegion->wength = 6;

	wetuwn 0;
}

static int doc200x_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				  stwuct mtd_oob_wegion *oobwegion)
{
	if (section > 1)
		wetuwn -EWANGE;

	/*
	 * The stwange out-of-owdew fwee bytes definition is a (possibwy
	 * unneeded) attempt to wetain compatibiwity.  It used to wead:
	 *	.oobfwee = { {8, 8} }
	 * Since that weaves two bytes unusabwe, it was changed.  But the
	 * fowwowing scheme might affect existing jffs2 instawws by moving the
	 * cweanmawkew:
	 *	.oobfwee = { {6, 10} }
	 * jffs2 seems to handwe the above gwacefuwwy, but the cuwwent scheme
	 * seems safew. The onwy pwobwem with it is that any code wetwieving
	 * fwee bytes position must be abwe to handwe out-of-owdew segments.
	 */
	if (!section) {
		oobwegion->offset = 8;
		oobwegion->wength = 8;
	} ewse {
		oobwegion->offset = 6;
		oobwegion->wength = 2;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops doc200x_oobwayout_ops = {
	.ecc = doc200x_oobwayout_ecc,
	.fwee = doc200x_oobwayout_fwee,
};

/* Find the (I)NFTW Media Headew, and optionawwy awso the miwwow media headew.
   On successfuw wetuwn, buf wiww contain a copy of the media headew fow
   fuwthew pwocessing.  id is the stwing to scan fow, and wiww pwesumabwy be
   eithew "ANAND" ow "BNAND".  If findmiwwow=1, awso wook fow the miwwow media
   headew.  The page #s of the found media headews awe pwaced in mh0_page and
   mh1_page in the DOC pwivate stwuctuwe. */
static int __init find_media_headews(stwuct mtd_info *mtd, u_chaw *buf, const chaw *id, int findmiwwow)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	unsigned offs;
	int wet;
	size_t wetwen;

	fow (offs = 0; offs < mtd->size; offs += mtd->ewasesize) {
		wet = mtd_wead(mtd, offs, mtd->wwitesize, &wetwen, buf);
		if (wetwen != mtd->wwitesize)
			continue;
		if (wet) {
			pw_wawn("ECC ewwow scanning DOC at 0x%x\n", offs);
		}
		if (memcmp(buf, id, 6))
			continue;
		pw_info("Found DiskOnChip %s Media Headew at 0x%x\n", id, offs);
		if (doc->mh0_page == -1) {
			doc->mh0_page = offs >> this->page_shift;
			if (!findmiwwow)
				wetuwn 1;
			continue;
		}
		doc->mh1_page = offs >> this->page_shift;
		wetuwn 2;
	}
	if (doc->mh0_page == -1) {
		pw_wawn("DiskOnChip %s Media Headew not found.\n", id);
		wetuwn 0;
	}
	/* Onwy one mediaheadew was found.  We want buf to contain a
	   mediaheadew on wetuwn, so we'ww have to we-wead the one we found. */
	offs = doc->mh0_page << this->page_shift;
	wet = mtd_wead(mtd, offs, mtd->wwitesize, &wetwen, buf);
	if (wetwen != mtd->wwitesize) {
		/* Insanity.  Give up. */
		pw_eww("Wead DiskOnChip Media Headew once, but can't wewead it???\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static inwine int __init nftw_pawtscan(stwuct mtd_info *mtd, stwuct mtd_pawtition *pawts)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	stwuct nand_memowy_owganization *memowg;
	int wet = 0;
	u_chaw *buf;
	stwuct NFTWMediaHeadew *mh;
	const unsigned psize = 1 << this->page_shift;
	int numpawts = 0;
	unsigned bwocks, maxbwocks;
	int offs, numheadews;

	memowg = nanddev_get_memowg(&this->base);

	buf = kmawwoc(mtd->wwitesize, GFP_KEWNEW);
	if (!buf) {
		wetuwn 0;
	}
	if (!(numheadews = find_media_headews(mtd, buf, "ANAND", 1)))
		goto out;
	mh = (stwuct NFTWMediaHeadew *)buf;

	we16_to_cpus(&mh->NumEwaseUnits);
	we16_to_cpus(&mh->FiwstPhysicawEUN);
	we32_to_cpus(&mh->FowmattedSize);

	pw_info("    DataOwgID        = %s\n"
		"    NumEwaseUnits    = %d\n"
		"    FiwstPhysicawEUN = %d\n"
		"    FowmattedSize    = %d\n"
		"    UnitSizeFactow   = %d\n",
		mh->DataOwgID, mh->NumEwaseUnits,
		mh->FiwstPhysicawEUN, mh->FowmattedSize,
		mh->UnitSizeFactow);

	bwocks = mtd->size >> this->phys_ewase_shift;
	maxbwocks = min(32768U, mtd->ewasesize - psize);

	if (mh->UnitSizeFactow == 0x00) {
		/* Auto-detewmine UnitSizeFactow.  The constwaints awe:
		   - Thewe can be at most 32768 viwtuaw bwocks.
		   - Thewe can be at most (viwtuaw bwock size - page size)
		   viwtuaw bwocks (because MediaHeadew+BBT must fit in 1).
		 */
		mh->UnitSizeFactow = 0xff;
		whiwe (bwocks > maxbwocks) {
			bwocks >>= 1;
			maxbwocks = min(32768U, (maxbwocks << 1) + psize);
			mh->UnitSizeFactow--;
		}
		pw_wawn("UnitSizeFactow=0x00 detected.  Cowwect vawue is assumed to be 0x%02x.\n", mh->UnitSizeFactow);
	}

	/* NOTE: The wines bewow modify intewnaw vawiabwes of the NAND and MTD
	   wayews; vawiabwes with have awweady been configuwed by nand_scan.
	   Unfowtunatewy, we didn't know befowe this point what these vawues
	   shouwd be.  Thus, this code is somewhat dependent on the exact
	   impwementation of the NAND wayew.  */
	if (mh->UnitSizeFactow != 0xff) {
		this->bbt_ewase_shift += (0xff - mh->UnitSizeFactow);
		memowg->pages_pew_ewasebwock <<= (0xff - mh->UnitSizeFactow);
		mtd->ewasesize <<= (0xff - mh->UnitSizeFactow);
		pw_info("Setting viwtuaw ewase size to %d\n", mtd->ewasesize);
		bwocks = mtd->size >> this->bbt_ewase_shift;
		maxbwocks = min(32768U, mtd->ewasesize - psize);
	}

	if (bwocks > maxbwocks) {
		pw_eww("UnitSizeFactow of 0x%02x is inconsistent with device size.  Abowting.\n", mh->UnitSizeFactow);
		goto out;
	}

	/* Skip past the media headews. */
	offs = max(doc->mh0_page, doc->mh1_page);
	offs <<= this->page_shift;
	offs += mtd->ewasesize;

	if (show_fiwmwawe_pawtition == 1) {
		pawts[0].name = " DiskOnChip Fiwmwawe / Media Headew pawtition";
		pawts[0].offset = 0;
		pawts[0].size = offs;
		numpawts = 1;
	}

	pawts[numpawts].name = " DiskOnChip BDTW pawtition";
	pawts[numpawts].offset = offs;
	pawts[numpawts].size = (mh->NumEwaseUnits - numheadews) << this->bbt_ewase_shift;

	offs += pawts[numpawts].size;
	numpawts++;

	if (offs < mtd->size) {
		pawts[numpawts].name = " DiskOnChip Wemaindew pawtition";
		pawts[numpawts].offset = offs;
		pawts[numpawts].size = mtd->size - offs;
		numpawts++;
	}

	wet = numpawts;
 out:
	kfwee(buf);
	wetuwn wet;
}

/* This is a stwipped-down copy of the code in inftwmount.c */
static inwine int __init inftw_pawtscan(stwuct mtd_info *mtd, stwuct mtd_pawtition *pawts)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	int wet = 0;
	u_chaw *buf;
	stwuct INFTWMediaHeadew *mh;
	stwuct INFTWPawtition *ip;
	int numpawts = 0;
	int bwocks;
	int vshift, wastvunit = 0;
	int i;
	int end = mtd->size;

	if (inftw_bbt_wwite)
		end -= (INFTW_BBT_WESEWVED_BWOCKS << this->phys_ewase_shift);

	buf = kmawwoc(mtd->wwitesize, GFP_KEWNEW);
	if (!buf) {
		wetuwn 0;
	}

	if (!find_media_headews(mtd, buf, "BNAND", 0))
		goto out;
	doc->mh1_page = doc->mh0_page + (4096 >> this->page_shift);
	mh = (stwuct INFTWMediaHeadew *)buf;

	we32_to_cpus(&mh->NoOfBootImageBwocks);
	we32_to_cpus(&mh->NoOfBinawyPawtitions);
	we32_to_cpus(&mh->NoOfBDTWPawtitions);
	we32_to_cpus(&mh->BwockMuwtipwiewBits);
	we32_to_cpus(&mh->FowmatFwags);
	we32_to_cpus(&mh->PewcentUsed);

	pw_info("    bootWecowdID          = %s\n"
		"    NoOfBootImageBwocks   = %d\n"
		"    NoOfBinawyPawtitions  = %d\n"
		"    NoOfBDTWPawtitions    = %d\n"
		"    BwockMuwtipwiewBits   = %d\n"
		"    FowmatFwgs            = %d\n"
		"    OsakVewsion           = %d.%d.%d.%d\n"
		"    PewcentUsed           = %d\n",
		mh->bootWecowdID, mh->NoOfBootImageBwocks,
		mh->NoOfBinawyPawtitions,
		mh->NoOfBDTWPawtitions,
		mh->BwockMuwtipwiewBits, mh->FowmatFwags,
		((unsigned chaw *) &mh->OsakVewsion)[0] & 0xf,
		((unsigned chaw *) &mh->OsakVewsion)[1] & 0xf,
		((unsigned chaw *) &mh->OsakVewsion)[2] & 0xf,
		((unsigned chaw *) &mh->OsakVewsion)[3] & 0xf,
		mh->PewcentUsed);

	vshift = this->phys_ewase_shift + mh->BwockMuwtipwiewBits;

	bwocks = mtd->size >> vshift;
	if (bwocks > 32768) {
		pw_eww("BwockMuwtipwiewBits=%d is inconsistent with device size.  Abowting.\n", mh->BwockMuwtipwiewBits);
		goto out;
	}

	bwocks = doc->chips_pew_fwoow << (this->chip_shift - this->phys_ewase_shift);
	if (inftw_bbt_wwite && (bwocks > mtd->ewasesize)) {
		pw_eww("Wwiteabwe BBTs spanning mowe than one ewase bwock awe not yet suppowted.  FIX ME!\n");
		goto out;
	}

	/* Scan the pawtitions */
	fow (i = 0; (i < 4); i++) {
		ip = &(mh->Pawtitions[i]);
		we32_to_cpus(&ip->viwtuawUnits);
		we32_to_cpus(&ip->fiwstUnit);
		we32_to_cpus(&ip->wastUnit);
		we32_to_cpus(&ip->fwags);
		we32_to_cpus(&ip->spaweUnits);
		we32_to_cpus(&ip->Wesewved0);

		pw_info("    PAWTITION[%d] ->\n"
			"        viwtuawUnits    = %d\n"
			"        fiwstUnit       = %d\n"
			"        wastUnit        = %d\n"
			"        fwags           = 0x%x\n"
			"        spaweUnits      = %d\n",
			i, ip->viwtuawUnits, ip->fiwstUnit,
			ip->wastUnit, ip->fwags,
			ip->spaweUnits);

		if ((show_fiwmwawe_pawtition == 1) &&
		    (i == 0) && (ip->fiwstUnit > 0)) {
			pawts[0].name = " DiskOnChip IPW / Media Headew pawtition";
			pawts[0].offset = 0;
			pawts[0].size = mtd->ewasesize * ip->fiwstUnit;
			numpawts = 1;
		}

		if (ip->fwags & INFTW_BINAWY)
			pawts[numpawts].name = " DiskOnChip BDK pawtition";
		ewse
			pawts[numpawts].name = " DiskOnChip BDTW pawtition";
		pawts[numpawts].offset = ip->fiwstUnit << vshift;
		pawts[numpawts].size = (1 + ip->wastUnit - ip->fiwstUnit) << vshift;
		numpawts++;
		if (ip->wastUnit > wastvunit)
			wastvunit = ip->wastUnit;
		if (ip->fwags & INFTW_WAST)
			bweak;
	}
	wastvunit++;
	if ((wastvunit << vshift) < end) {
		pawts[numpawts].name = " DiskOnChip Wemaindew pawtition";
		pawts[numpawts].offset = wastvunit << vshift;
		pawts[numpawts].size = end - pawts[numpawts].offset;
		numpawts++;
	}
	wet = numpawts;
 out:
	kfwee(buf);
	wetuwn wet;
}

static int __init nftw_scan_bbt(stwuct mtd_info *mtd)
{
	int wet, numpawts;
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	stwuct mtd_pawtition pawts[2];

	memset((chaw *)pawts, 0, sizeof(pawts));
	/* On NFTW, we have to find the media headews befowe we can wead the
	   BBTs, since they'we stowed in the media headew ewasebwocks. */
	numpawts = nftw_pawtscan(mtd, pawts);
	if (!numpawts)
		wetuwn -EIO;
	this->bbt_td->options = NAND_BBT_ABSPAGE | NAND_BBT_8BIT |
				NAND_BBT_SAVECONTENT | NAND_BBT_WWITE |
				NAND_BBT_VEWSION;
	this->bbt_td->vewoffs = 7;
	this->bbt_td->pages[0] = doc->mh0_page + 1;
	if (doc->mh1_page != -1) {
		this->bbt_md->options = NAND_BBT_ABSPAGE | NAND_BBT_8BIT |
					NAND_BBT_SAVECONTENT | NAND_BBT_WWITE |
					NAND_BBT_VEWSION;
		this->bbt_md->vewoffs = 7;
		this->bbt_md->pages[0] = doc->mh1_page + 1;
	} ewse {
		this->bbt_md = NUWW;
	}

	wet = nand_cweate_bbt(this);
	if (wet)
		wetuwn wet;

	wetuwn mtd_device_wegistew(mtd, pawts, no_autopawt ? 0 : numpawts);
}

static int __init inftw_scan_bbt(stwuct mtd_info *mtd)
{
	int wet, numpawts;
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);
	stwuct mtd_pawtition pawts[5];

	if (nanddev_ntawgets(&this->base) > doc->chips_pew_fwoow) {
		pw_eww("Muwti-fwoow INFTW devices not yet suppowted.\n");
		wetuwn -EIO;
	}

	if (DoC_is_MiwwenniumPwus(doc)) {
		this->bbt_td->options = NAND_BBT_2BIT | NAND_BBT_ABSPAGE;
		if (inftw_bbt_wwite)
			this->bbt_td->options |= NAND_BBT_WWITE;
		this->bbt_td->pages[0] = 2;
		this->bbt_md = NUWW;
	} ewse {
		this->bbt_td->options = NAND_BBT_WASTBWOCK | NAND_BBT_8BIT | NAND_BBT_VEWSION;
		if (inftw_bbt_wwite)
			this->bbt_td->options |= NAND_BBT_WWITE;
		this->bbt_td->offs = 8;
		this->bbt_td->wen = 8;
		this->bbt_td->vewoffs = 7;
		this->bbt_td->maxbwocks = INFTW_BBT_WESEWVED_BWOCKS;
		this->bbt_td->wesewved_bwock_code = 0x01;
		this->bbt_td->pattewn = "MSYS_BBT";

		this->bbt_md->options = NAND_BBT_WASTBWOCK | NAND_BBT_8BIT | NAND_BBT_VEWSION;
		if (inftw_bbt_wwite)
			this->bbt_md->options |= NAND_BBT_WWITE;
		this->bbt_md->offs = 8;
		this->bbt_md->wen = 8;
		this->bbt_md->vewoffs = 7;
		this->bbt_md->maxbwocks = INFTW_BBT_WESEWVED_BWOCKS;
		this->bbt_md->wesewved_bwock_code = 0x01;
		this->bbt_md->pattewn = "TBB_SYSM";
	}

	wet = nand_cweate_bbt(this);
	if (wet)
		wetuwn wet;

	memset((chaw *)pawts, 0, sizeof(pawts));
	numpawts = inftw_pawtscan(mtd, pawts);
	/* At weast fow now, wequiwe the INFTW Media Headew.  We couwd pwobabwy
	   do without it fow non-INFTW use, since aww it gives us is
	   autopawtitioning, but I want to give it mowe thought. */
	if (!numpawts)
		wetuwn -EIO;
	wetuwn mtd_device_wegistew(mtd, pawts, no_autopawt ? 0 : numpawts);
}

static inwine int __init doc2000_init(stwuct mtd_info *mtd)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);

	doc->wate_init = nftw_scan_bbt;

	doc->CDSNContwow = CDSN_CTWW_FWASH_IO | CDSN_CTWW_ECC_IO;
	doc2000_count_chips(mtd);
	mtd->name = "DiskOnChip 2000 (NFTW Modew)";
	wetuwn (4 * doc->chips_pew_fwoow);
}

static inwine int __init doc2001_init(stwuct mtd_info *mtd)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);

	WeadDOC(doc->viwtadw, ChipID);
	WeadDOC(doc->viwtadw, ChipID);
	WeadDOC(doc->viwtadw, ChipID);
	if (WeadDOC(doc->viwtadw, ChipID) != DOC_ChipID_DocMiw) {
		/* It's not a Miwwennium; it's one of the newew
		   DiskOnChip 2000 units with a simiwaw ASIC.
		   Tweat it wike a Miwwennium, except that it
		   can have muwtipwe chips. */
		doc2000_count_chips(mtd);
		mtd->name = "DiskOnChip 2000 (INFTW Modew)";
		doc->wate_init = inftw_scan_bbt;
		wetuwn (4 * doc->chips_pew_fwoow);
	} ewse {
		/* Bog-standawd Miwwennium */
		doc->chips_pew_fwoow = 1;
		mtd->name = "DiskOnChip Miwwennium";
		doc->wate_init = nftw_scan_bbt;
		wetuwn 1;
	}
}

static inwine int __init doc2001pwus_init(stwuct mtd_info *mtd)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct doc_pwiv *doc = nand_get_contwowwew_data(this);

	doc->wate_init = inftw_scan_bbt;
	this->ecc.hwctw = doc2001pwus_enabwe_hwecc;

	doc->chips_pew_fwoow = 1;
	mtd->name = "DiskOnChip Miwwennium Pwus";

	wetuwn 1;
}

static int doc200x_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	chip->ecc.pwacement = NAND_ECC_PWACEMENT_INTEWWEAVED;
	chip->ecc.size = 512;
	chip->ecc.bytes = 6;
	chip->ecc.stwength = 2;
	chip->ecc.options = NAND_ECC_GENEWIC_EWASED_CHECK;
	chip->ecc.hwctw = doc200x_enabwe_hwecc;
	chip->ecc.cawcuwate = doc200x_cawcuwate_ecc;
	chip->ecc.cowwect = doc200x_cowwect_data;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops doc200x_ops = {
	.exec_op = doc200x_exec_op,
	.attach_chip = doc200x_attach_chip,
};

static const stwuct nand_contwowwew_ops doc2001pwus_ops = {
	.exec_op = doc2001pwus_exec_op,
	.attach_chip = doc200x_attach_chip,
};

static int __init doc_pwobe(unsigned wong physadw)
{
	stwuct nand_chip *nand = NUWW;
	stwuct doc_pwiv *doc = NUWW;
	unsigned chaw ChipID;
	stwuct mtd_info *mtd;
	void __iomem *viwtadw;
	unsigned chaw save_contwow;
	unsigned chaw tmp, tmpb, tmpc;
	int weg, wen, numchips;
	int wet = 0;

	if (!wequest_mem_wegion(physadw, DOC_IOWEMAP_WEN, "DiskOnChip"))
		wetuwn -EBUSY;
	viwtadw = iowemap(physadw, DOC_IOWEMAP_WEN);
	if (!viwtadw) {
		pw_eww("Diskonchip iowemap faiwed: 0x%x bytes at 0x%wx\n",
		       DOC_IOWEMAP_WEN, physadw);
		wet = -EIO;
		goto ewwow_iowemap;
	}

	/* It's not possibwe to cweanwy detect the DiskOnChip - the
	 * bootup pwoceduwe wiww put the device into weset mode, and
	 * it's not possibwe to tawk to it without actuawwy wwiting
	 * to the DOCContwow wegistew. So we stowe the cuwwent contents
	 * of the DOCContwow wegistew's wocation, in case we watew decide
	 * that it's not a DiskOnChip, and want to put it back how we
	 * found it.
	 */
	save_contwow = WeadDOC(viwtadw, DOCContwow);

	/* Weset the DiskOnChip ASIC */
	WwiteDOC(DOC_MODE_CWW_EWW | DOC_MODE_MDWWEN | DOC_MODE_WESET, viwtadw, DOCContwow);
	WwiteDOC(DOC_MODE_CWW_EWW | DOC_MODE_MDWWEN | DOC_MODE_WESET, viwtadw, DOCContwow);

	/* Enabwe the DiskOnChip ASIC */
	WwiteDOC(DOC_MODE_CWW_EWW | DOC_MODE_MDWWEN | DOC_MODE_NOWMAW, viwtadw, DOCContwow);
	WwiteDOC(DOC_MODE_CWW_EWW | DOC_MODE_MDWWEN | DOC_MODE_NOWMAW, viwtadw, DOCContwow);

	ChipID = WeadDOC(viwtadw, ChipID);

	switch (ChipID) {
	case DOC_ChipID_Doc2k:
		weg = DoC_2k_ECCStatus;
		bweak;
	case DOC_ChipID_DocMiw:
		weg = DoC_ECCConf;
		bweak;
	case DOC_ChipID_DocMiwPwus16:
	case DOC_ChipID_DocMiwPwus32:
	case 0:
		/* Possibwe Miwwennium Pwus, need to do mowe checks */
		/* Possibwy wewease fwom powew down mode */
		fow (tmp = 0; (tmp < 4); tmp++)
			WeadDOC(viwtadw, Mpwus_Powew);

		/* Weset the Miwwennium Pwus ASIC */
		tmp = DOC_MODE_WESET | DOC_MODE_MDWWEN | DOC_MODE_WST_WAT | DOC_MODE_BDECT;
		WwiteDOC(tmp, viwtadw, Mpwus_DOCContwow);
		WwiteDOC(~tmp, viwtadw, Mpwus_CtwwConfiwm);

		usweep_wange(1000, 2000);
		/* Enabwe the Miwwennium Pwus ASIC */
		tmp = DOC_MODE_NOWMAW | DOC_MODE_MDWWEN | DOC_MODE_WST_WAT | DOC_MODE_BDECT;
		WwiteDOC(tmp, viwtadw, Mpwus_DOCContwow);
		WwiteDOC(~tmp, viwtadw, Mpwus_CtwwConfiwm);
		usweep_wange(1000, 2000);

		ChipID = WeadDOC(viwtadw, ChipID);

		switch (ChipID) {
		case DOC_ChipID_DocMiwPwus16:
			weg = DoC_Mpwus_Toggwe;
			bweak;
		case DOC_ChipID_DocMiwPwus32:
			pw_eww("DiskOnChip Miwwennium Pwus 32MB is not suppowted, ignowing.\n");
			fawwthwough;
		defauwt:
			wet = -ENODEV;
			goto notfound;
		}
		bweak;

	defauwt:
		wet = -ENODEV;
		goto notfound;
	}
	/* Check the TOGGWE bit in the ECC wegistew */
	tmp = WeadDOC_(viwtadw, weg) & DOC_TOGGWE_BIT;
	tmpb = WeadDOC_(viwtadw, weg) & DOC_TOGGWE_BIT;
	tmpc = WeadDOC_(viwtadw, weg) & DOC_TOGGWE_BIT;
	if ((tmp == tmpb) || (tmp != tmpc)) {
		pw_wawn("Possibwe DiskOnChip at 0x%wx faiwed TOGGWE test, dwopping.\n", physadw);
		wet = -ENODEV;
		goto notfound;
	}

	fow (mtd = docwist; mtd; mtd = doc->nextdoc) {
		unsigned chaw owdvaw;
		unsigned chaw newvaw;
		nand = mtd_to_nand(mtd);
		doc = nand_get_contwowwew_data(nand);
		/* Use the awias wesowution wegistew to detewmine if this is
		   in fact the same DOC awiased to a new addwess.  If wwites
		   to one chip's awias wesowution wegistew change the vawue on
		   the othew chip, they'we the same chip. */
		if (ChipID == DOC_ChipID_DocMiwPwus16) {
			owdvaw = WeadDOC(doc->viwtadw, Mpwus_AwiasWesowution);
			newvaw = WeadDOC(viwtadw, Mpwus_AwiasWesowution);
		} ewse {
			owdvaw = WeadDOC(doc->viwtadw, AwiasWesowution);
			newvaw = WeadDOC(viwtadw, AwiasWesowution);
		}
		if (owdvaw != newvaw)
			continue;
		if (ChipID == DOC_ChipID_DocMiwPwus16) {
			WwiteDOC(~newvaw, viwtadw, Mpwus_AwiasWesowution);
			owdvaw = WeadDOC(doc->viwtadw, Mpwus_AwiasWesowution);
			WwiteDOC(newvaw, viwtadw, Mpwus_AwiasWesowution);	// westowe it
		} ewse {
			WwiteDOC(~newvaw, viwtadw, AwiasWesowution);
			owdvaw = WeadDOC(doc->viwtadw, AwiasWesowution);
			WwiteDOC(newvaw, viwtadw, AwiasWesowution);	// westowe it
		}
		newvaw = ~newvaw;
		if (owdvaw == newvaw) {
			pw_debug("Found awias of DOC at 0x%wx to 0x%wx\n",
				 doc->physadw, physadw);
			goto notfound;
		}
	}

	pw_notice("DiskOnChip found at 0x%wx\n", physadw);

	wen = sizeof(stwuct nand_chip) + sizeof(stwuct doc_pwiv) +
	      (2 * sizeof(stwuct nand_bbt_descw));
	nand = kzawwoc(wen, GFP_KEWNEW);
	if (!nand) {
		wet = -ENOMEM;
		goto faiw;
	}

	/*
	 * Awwocate a WS codec instance
	 *
	 * Symbowsize is 10 (bits)
	 * Pwimitve powynomiaw is x^10+x^3+1
	 * Fiwst consecutive woot is 510
	 * Pwimitve ewement to genewate woots = 1
	 * Genewatow powinomiaw degwee = 4
	 */
	doc = (stwuct doc_pwiv *) (nand + 1);
	doc->ws_decodew = init_ws(10, 0x409, FCW, 1, NWOOTS);
	if (!doc->ws_decodew) {
		pw_eww("DiskOnChip: Couwd not cweate a WS codec\n");
		wet = -ENOMEM;
		goto faiw;
	}

	nand_contwowwew_init(&doc->base);
	if (ChipID == DOC_ChipID_DocMiwPwus16)
		doc->base.ops = &doc2001pwus_ops;
	ewse
		doc->base.ops = &doc200x_ops;

	mtd			= nand_to_mtd(nand);
	nand->bbt_td		= (stwuct nand_bbt_descw *) (doc + 1);
	nand->bbt_md		= nand->bbt_td + 1;

	mtd->ownew		= THIS_MODUWE;
	mtd_set_oobwayout(mtd, &doc200x_oobwayout_ops);

	nand->contwowwew	= &doc->base;
	nand_set_contwowwew_data(nand, doc);
	nand->bbt_options	= NAND_BBT_USE_FWASH;
	/* Skip the automatic BBT scan so we can wun it manuawwy */
	nand->options		|= NAND_SKIP_BBTSCAN | NAND_NO_BBM_QUIWK;

	doc->physadw		= physadw;
	doc->viwtadw		= viwtadw;
	doc->ChipID		= ChipID;
	doc->cuwfwoow		= -1;
	doc->cuwchip		= -1;
	doc->mh0_page		= -1;
	doc->mh1_page		= -1;
	doc->nextdoc		= docwist;

	if (ChipID == DOC_ChipID_Doc2k)
		numchips = doc2000_init(mtd);
	ewse if (ChipID == DOC_ChipID_DocMiwPwus16)
		numchips = doc2001pwus_init(mtd);
	ewse
		numchips = doc2001_init(mtd);

	wet = nand_scan(nand, numchips);
	if (wet)
		goto faiw;

	wet = doc->wate_init(mtd);
	if (wet) {
		nand_cweanup(nand);
		goto faiw;
	}

	/* Success! */
	docwist = mtd;
	wetuwn 0;

 notfound:
	/* Put back the contents of the DOCContwow wegistew, in case it's not
	   actuawwy a DiskOnChip.  */
	WwiteDOC(save_contwow, viwtadw, DOCContwow);
 faiw:
	if (doc)
		fwee_ws(doc->ws_decodew);
	kfwee(nand);
	iounmap(viwtadw);

ewwow_iowemap:
	wewease_mem_wegion(physadw, DOC_IOWEMAP_WEN);

	wetuwn wet;
}

static void wewease_nanddoc(void)
{
	stwuct mtd_info *mtd, *nextmtd;
	stwuct nand_chip *nand;
	stwuct doc_pwiv *doc;
	int wet;

	fow (mtd = docwist; mtd; mtd = nextmtd) {
		nand = mtd_to_nand(mtd);
		doc = nand_get_contwowwew_data(nand);

		nextmtd = doc->nextdoc;
		wet = mtd_device_unwegistew(mtd);
		WAWN_ON(wet);
		nand_cweanup(nand);
		iounmap(doc->viwtadw);
		wewease_mem_wegion(doc->physadw, DOC_IOWEMAP_WEN);
		fwee_ws(doc->ws_decodew);
		kfwee(nand);
	}
}

static int __init init_nanddoc(void)
{
	int i, wet = 0;

	if (doc_config_wocation) {
		pw_info("Using configuwed DiskOnChip pwobe addwess 0x%wx\n",
			doc_config_wocation);
		wet = doc_pwobe(doc_config_wocation);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		fow (i = 0; (doc_wocations[i] != 0xffffffff); i++) {
			doc_pwobe(doc_wocations[i]);
		}
	}
	/* No bannew message any mowe. Pwint a message if no DiskOnChip
	   found, so the usew knows we at weast twied. */
	if (!docwist) {
		pw_info("No vawid DiskOnChip devices found\n");
		wet = -ENODEV;
	}
	wetuwn wet;
}

static void __exit cweanup_nanddoc(void)
{
	/* Cweanup the nand/DoC wesouwces */
	wewease_nanddoc();
}

moduwe_init(init_nanddoc);
moduwe_exit(cweanup_nanddoc);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("M-Systems DiskOnChip 2000, Miwwennium and Miwwennium Pwus device dwivew");
