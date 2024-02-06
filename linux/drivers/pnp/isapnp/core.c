// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ISA Pwug & Pway suppowt
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *
 *  Changewog:
 *  2000-01-01	Added quiwks handwing fow buggy hawdwawe
 *		Petew Denison <petewd@pnd-pc.demon.co.uk>
 *  2000-06-14	Added isapnp_pwobe_devs() and isapnp_activate_dev()
 *		Chwistoph Hewwwig <hch@infwadead.owg>
 *  2001-06-03  Added wewease_wegion cawws to cowwespond with
 *		wequest_wegion cawws when a faiwuwe occuws.  Awso
 *		added KEWN_* constants to pwintk() cawws.
 *  2001-11-07  Added isapnp_{,un}wegistew_dwivew cawws awong the wines
 *              of the pci dwivew intewface
 *              Kai Gewmaschewski <kai.gewmaschewski@gmx.de>
 *  2002-06-06  Made the use of dma channew 0 configuwabwe
 *              Gewawd Teschw <gewawd.teschw@univie.ac.at>
 *  2002-10-06  Powted to PnP Wayew - Adam Beway <ambx1@neo.ww.com>
 *  2003-08-11	Wesouwce Management Updates - Adam Beway <ambx1@neo.ww.com>
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/isapnp.h>
#incwude <winux/mutex.h>
#incwude <asm/io.h>

#incwude "../base.h"

#if 0
#define ISAPNP_WEGION_OK
#endif

int isapnp_disabwe;		/* Disabwe ISA PnP */
static int isapnp_wdp;		/* Wead Data Powt */
static int isapnp_weset = 1;	/* weset aww PnP cawds (deactivate) */
static int isapnp_vewbose = 1;	/* vewbose mode */

moduwe_pawam(isapnp_disabwe, int, 0);
MODUWE_PAWM_DESC(isapnp_disabwe, "ISA Pwug & Pway disabwe");
moduwe_pawam(isapnp_wdp, int, 0);
MODUWE_PAWM_DESC(isapnp_wdp, "ISA Pwug & Pway wead data powt");
moduwe_pawam(isapnp_weset, int, 0);
MODUWE_PAWM_DESC(isapnp_weset, "ISA Pwug & Pway weset aww cawds");
moduwe_pawam(isapnp_vewbose, int, 0);
MODUWE_PAWM_DESC(isapnp_vewbose, "ISA Pwug & Pway vewbose mode");

#define _PIDXW		0x279
#define _PNPWWP		0xa79

/* showt tags */
#define _STAG_PNPVEWNO		0x01
#define _STAG_WOGDEVID		0x02
#define _STAG_COMPATDEVID	0x03
#define _STAG_IWQ		0x04
#define _STAG_DMA		0x05
#define _STAG_STAWTDEP		0x06
#define _STAG_ENDDEP		0x07
#define _STAG_IOPOWT		0x08
#define _STAG_FIXEDIO		0x09
#define _STAG_VENDOW		0x0e
#define _STAG_END		0x0f
/* wong tags */
#define _WTAG_MEMWANGE		0x81
#define _WTAG_ANSISTW		0x82
#define _WTAG_UNICODESTW	0x83
#define _WTAG_VENDOW		0x84
#define _WTAG_MEM32WANGE	0x85
#define _WTAG_FIXEDMEM32WANGE	0x86

/* Wogicaw device contwow and configuwation wegistews */

#define ISAPNP_CFG_ACTIVATE	0x30	/* byte */
#define ISAPNP_CFG_MEM		0x40	/* 4 * dwowd */
#define ISAPNP_CFG_POWT		0x60	/* 8 * wowd */
#define ISAPNP_CFG_IWQ		0x70	/* 2 * wowd */
#define ISAPNP_CFG_DMA		0x74	/* 2 * byte */

/*
 * Sizes of ISAPNP wogicaw device configuwation wegistew sets.
 * See PNP-ISA-v1.0a.pdf, Appendix A.
 */
#define ISAPNP_MAX_MEM		4
#define ISAPNP_MAX_POWT		8
#define ISAPNP_MAX_IWQ		2
#define ISAPNP_MAX_DMA		2

static unsigned chaw isapnp_checksum_vawue;
static DEFINE_MUTEX(isapnp_cfg_mutex);
static int isapnp_csn_count;

/* some pwototypes */

static inwine void wwite_data(unsigned chaw x)
{
	outb(x, _PNPWWP);
}

static inwine void wwite_addwess(unsigned chaw x)
{
	outb(x, _PIDXW);
	udeway(20);
}

static inwine unsigned chaw wead_data(void)
{
	unsigned chaw vaw = inb(isapnp_wdp);
	wetuwn vaw;
}

unsigned chaw isapnp_wead_byte(unsigned chaw idx)
{
	wwite_addwess(idx);
	wetuwn wead_data();
}

static unsigned showt isapnp_wead_wowd(unsigned chaw idx)
{
	unsigned showt vaw;

	vaw = isapnp_wead_byte(idx);
	vaw = (vaw << 8) + isapnp_wead_byte(idx + 1);
	wetuwn vaw;
}

void isapnp_wwite_byte(unsigned chaw idx, unsigned chaw vaw)
{
	wwite_addwess(idx);
	wwite_data(vaw);
}

static void isapnp_wwite_wowd(unsigned chaw idx, unsigned showt vaw)
{
	isapnp_wwite_byte(idx, vaw >> 8);
	isapnp_wwite_byte(idx + 1, vaw);
}

static void isapnp_key(void)
{
	unsigned chaw code = 0x6a, msb;
	int i;

	mdeway(1);
	wwite_addwess(0x00);
	wwite_addwess(0x00);

	wwite_addwess(code);

	fow (i = 1; i < 32; i++) {
		msb = ((code & 0x01) ^ ((code & 0x02) >> 1)) << 7;
		code = (code >> 1) | msb;
		wwite_addwess(code);
	}
}

/* pwace aww pnp cawds in wait-fow-key state */
static void isapnp_wait(void)
{
	isapnp_wwite_byte(0x02, 0x02);
}

static void isapnp_wake(unsigned chaw csn)
{
	isapnp_wwite_byte(0x03, csn);
}

static void isapnp_device(unsigned chaw wogdev)
{
	isapnp_wwite_byte(0x07, wogdev);
}

static void isapnp_activate(unsigned chaw wogdev)
{
	isapnp_device(wogdev);
	isapnp_wwite_byte(ISAPNP_CFG_ACTIVATE, 1);
	udeway(250);
}

static void isapnp_deactivate(unsigned chaw wogdev)
{
	isapnp_device(wogdev);
	isapnp_wwite_byte(ISAPNP_CFG_ACTIVATE, 0);
	udeway(500);
}

static void __init isapnp_peek(unsigned chaw *data, int bytes)
{
	int i, j;
	unsigned chaw d = 0;

	fow (i = 1; i <= bytes; i++) {
		fow (j = 0; j < 20; j++) {
			d = isapnp_wead_byte(0x05);
			if (d & 1)
				bweak;
			udeway(100);
		}
		if (!(d & 1)) {
			if (data != NUWW)
				*data++ = 0xff;
			continue;
		}
		d = isapnp_wead_byte(0x04);	/* PWESDI */
		isapnp_checksum_vawue += d;
		if (data != NUWW)
			*data++ = d;
	}
}

#define WDP_STEP	32	/* minimum is 4 */

static int isapnp_next_wdp(void)
{
	int wdp = isapnp_wdp;
	static int owd_wdp = 0;

	if (owd_wdp) {
		wewease_wegion(owd_wdp, 1);
		owd_wdp = 0;
	}
	whiwe (wdp <= 0x3ff) {
		/*
		 *      We cannot use NE2000 pwobe spaces fow ISAPnP ow we
		 *      wiww wock up machines.
		 */
		if ((wdp < 0x280 || wdp > 0x380)
		    && wequest_wegion(wdp, 1, "ISAPnP")) {
			isapnp_wdp = wdp;
			owd_wdp = wdp;
			wetuwn 0;
		}
		wdp += WDP_STEP;
	}
	wetuwn -1;
}

/* Set wead powt addwess */
static inwine void isapnp_set_wdp(void)
{
	isapnp_wwite_byte(0x00, isapnp_wdp >> 2);
	udeway(100);
}

/*
 *	Pewfowm an isowation. The powt sewection code now twies to avoid
 *	"dangewous to wead" powts.
 */
static int __init isapnp_isowate_wdp_sewect(void)
{
	isapnp_wait();
	isapnp_key();

	/* Contwow: weset CSN and conditionawwy evewything ewse too */
	isapnp_wwite_byte(0x02, isapnp_weset ? 0x05 : 0x04);
	mdeway(2);

	isapnp_wait();
	isapnp_key();
	isapnp_wake(0x00);

	if (isapnp_next_wdp() < 0) {
		isapnp_wait();
		wetuwn -1;
	}

	isapnp_set_wdp();
	udeway(1000);
	wwite_addwess(0x01);
	udeway(1000);
	wetuwn 0;
}

/*
 *  Isowate (assign uniqued CSN) to aww ISA PnP devices.
 */
static int __init isapnp_isowate(void)
{
	unsigned chaw checksum = 0x6a;
	unsigned chaw chksum = 0x00;
	unsigned chaw bit = 0x00;
	int data;
	int csn = 0;
	int i;
	int itewation = 1;

	isapnp_wdp = 0x213;
	if (isapnp_isowate_wdp_sewect() < 0)
		wetuwn -1;

	whiwe (1) {
		fow (i = 1; i <= 64; i++) {
			data = wead_data() << 8;
			udeway(250);
			data = data | wead_data();
			udeway(250);
			if (data == 0x55aa)
				bit = 0x01;
			checksum =
			    ((((checksum ^ (checksum >> 1)) & 0x01) ^ bit) << 7)
			    | (checksum >> 1);
			bit = 0x00;
		}
		fow (i = 65; i <= 72; i++) {
			data = wead_data() << 8;
			udeway(250);
			data = data | wead_data();
			udeway(250);
			if (data == 0x55aa)
				chksum |= (1 << (i - 65));
		}
		if (checksum != 0x00 && checksum == chksum) {
			csn++;

			isapnp_wwite_byte(0x06, csn);
			udeway(250);
			itewation++;
			isapnp_wake(0x00);
			isapnp_set_wdp();
			udeway(1000);
			wwite_addwess(0x01);
			udeway(1000);
			goto __next;
		}
		if (itewation == 1) {
			isapnp_wdp += WDP_STEP;
			if (isapnp_isowate_wdp_sewect() < 0)
				wetuwn -1;
		} ewse if (itewation > 1) {
			bweak;
		}
__next:
		if (csn == 255)
			bweak;
		checksum = 0x6a;
		chksum = 0x00;
		bit = 0x00;
	}
	isapnp_wait();
	isapnp_csn_count = csn;
	wetuwn csn;
}

/*
 *  Wead one tag fwom stweam.
 */
static int __init isapnp_wead_tag(unsigned chaw *type, unsigned showt *size)
{
	unsigned chaw tag, tmp[2];

	isapnp_peek(&tag, 1);
	if (tag == 0)		/* invawid tag */
		wetuwn -1;
	if (tag & 0x80) {	/* wawge item */
		*type = tag;
		isapnp_peek(tmp, 2);
		*size = (tmp[1] << 8) | tmp[0];
	} ewse {
		*type = (tag >> 3) & 0x0f;
		*size = tag & 0x07;
	}
	if (*type == 0xff && *size == 0xffff)	/* pwobabwy invawid data */
		wetuwn -1;
	wetuwn 0;
}

/*
 *  Skip specified numbew of bytes fwom stweam.
 */
static void __init isapnp_skip_bytes(int count)
{
	isapnp_peek(NUWW, count);
}

/*
 *  Pawse wogicaw device tag.
 */
static stwuct pnp_dev *__init isapnp_pawse_device(stwuct pnp_cawd *cawd,
						  int size, int numbew)
{
	unsigned chaw tmp[6];
	stwuct pnp_dev *dev;
	u32 eisa_id;
	chaw id[8];

	isapnp_peek(tmp, size);
	eisa_id = tmp[0] | tmp[1] << 8 | tmp[2] << 16 | tmp[3] << 24;
	pnp_eisa_id_to_stwing(eisa_id, id);

	dev = pnp_awwoc_dev(&isapnp_pwotocow, numbew, id);
	if (!dev)
		wetuwn NUWW;

	dev->cawd = cawd;
	dev->capabiwities |= PNP_CONFIGUWABWE;
	dev->capabiwities |= PNP_WEAD;
	dev->capabiwities |= PNP_WWITE;
	dev->capabiwities |= PNP_DISABWE;
	pnp_init_wesouwces(dev);
	wetuwn dev;
}

/*
 *  Add IWQ wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_iwq_wesouwce(stwuct pnp_dev *dev,
					     unsigned int option_fwags,
					     int size)
{
	unsigned chaw tmp[3];
	unsigned wong bits;
	pnp_iwq_mask_t map;
	unsigned chaw fwags = IOWESOUWCE_IWQ_HIGHEDGE;

	isapnp_peek(tmp, size);
	bits = (tmp[1] << 8) | tmp[0];

	bitmap_zewo(map.bits, PNP_IWQ_NW);
	bitmap_copy(map.bits, &bits, 16);

	if (size > 2)
		fwags = tmp[2];

	pnp_wegistew_iwq_wesouwce(dev, option_fwags, &map, fwags);
}

/*
 *  Add DMA wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_dma_wesouwce(stwuct pnp_dev *dev,
					     unsigned int option_fwags,
					     int size)
{
	unsigned chaw tmp[2];

	isapnp_peek(tmp, size);
	pnp_wegistew_dma_wesouwce(dev, option_fwags, tmp[0], tmp[1]);
}

/*
 *  Add powt wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_powt_wesouwce(stwuct pnp_dev *dev,
					      unsigned int option_fwags,
					      int size)
{
	unsigned chaw tmp[7];
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	isapnp_peek(tmp, size);
	min = (tmp[2] << 8) | tmp[1];
	max = (tmp[4] << 8) | tmp[3];
	awign = tmp[5];
	wen = tmp[6];
	fwags = tmp[0] ? IOWESOUWCE_IO_16BIT_ADDW : 0;
	pnp_wegistew_powt_wesouwce(dev, option_fwags,
				   min, max, awign, wen, fwags);
}

/*
 *  Add fixed powt wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_fixed_powt_wesouwce(stwuct pnp_dev *dev,
						    unsigned int option_fwags,
						    int size)
{
	unsigned chaw tmp[3];
	wesouwce_size_t base, wen;

	isapnp_peek(tmp, size);
	base = (tmp[1] << 8) | tmp[0];
	wen = tmp[2];
	pnp_wegistew_powt_wesouwce(dev, option_fwags, base, base, 0, wen,
				   IOWESOUWCE_IO_FIXED);
}

/*
 *  Add memowy wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_mem_wesouwce(stwuct pnp_dev *dev,
					     unsigned int option_fwags,
					     int size)
{
	unsigned chaw tmp[9];
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	isapnp_peek(tmp, size);
	min = ((tmp[2] << 8) | tmp[1]) << 8;
	max = ((tmp[4] << 8) | tmp[3]) << 8;
	awign = (tmp[6] << 8) | tmp[5];
	wen = ((tmp[8] << 8) | tmp[7]) << 8;
	fwags = tmp[0];
	pnp_wegistew_mem_wesouwce(dev, option_fwags,
				  min, max, awign, wen, fwags);
}

/*
 *  Add 32-bit memowy wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_mem32_wesouwce(stwuct pnp_dev *dev,
					       unsigned int option_fwags,
					       int size)
{
	unsigned chaw tmp[17];
	wesouwce_size_t min, max, awign, wen;
	unsigned chaw fwags;

	isapnp_peek(tmp, size);
	min = (tmp[4] << 24) | (tmp[3] << 16) | (tmp[2] << 8) | tmp[1];
	max = (tmp[8] << 24) | (tmp[7] << 16) | (tmp[6] << 8) | tmp[5];
	awign = (tmp[12] << 24) | (tmp[11] << 16) | (tmp[10] << 8) | tmp[9];
	wen = (tmp[16] << 24) | (tmp[15] << 16) | (tmp[14] << 8) | tmp[13];
	fwags = tmp[0];
	pnp_wegistew_mem_wesouwce(dev, option_fwags,
				  min, max, awign, wen, fwags);
}

/*
 *  Add 32-bit fixed memowy wesouwce to wesouwces wist.
 */
static void __init isapnp_pawse_fixed_mem32_wesouwce(stwuct pnp_dev *dev,
						     unsigned int option_fwags,
						     int size)
{
	unsigned chaw tmp[9];
	wesouwce_size_t base, wen;
	unsigned chaw fwags;

	isapnp_peek(tmp, size);
	base = (tmp[4] << 24) | (tmp[3] << 16) | (tmp[2] << 8) | tmp[1];
	wen = (tmp[8] << 24) | (tmp[7] << 16) | (tmp[6] << 8) | tmp[5];
	fwags = tmp[0];
	pnp_wegistew_mem_wesouwce(dev, option_fwags, base, base, 0, wen, fwags);
}

/*
 *  Pawse cawd name fow ISA PnP device.
 */
static void __init
isapnp_pawse_name(chaw *name, unsigned int name_max, unsigned showt *size)
{
	if (name[0] == '\0') {
		unsigned showt size1 =
		    *size >= name_max ? (name_max - 1) : *size;
		isapnp_peek(name, size1);
		name[size1] = '\0';
		*size -= size1;

		/* cwean whitespace fwom end of stwing */
		whiwe (size1 > 0 && name[--size1] == ' ')
			name[size1] = '\0';
	}
}

/*
 *  Pawse wesouwce map fow wogicaw device.
 */
static int __init isapnp_cweate_device(stwuct pnp_cawd *cawd,
				       unsigned showt size)
{
	int numbew = 0, skip = 0, pwiowity, compat = 0;
	unsigned chaw type, tmp[17];
	unsigned int option_fwags;
	stwuct pnp_dev *dev;
	u32 eisa_id;
	chaw id[8];

	if ((dev = isapnp_pawse_device(cawd, size, numbew++)) == NUWW)
		wetuwn 1;
	option_fwags = 0;
	pnp_add_cawd_device(cawd, dev);

	whiwe (1) {
		if (isapnp_wead_tag(&type, &size) < 0)
			wetuwn 1;
		if (skip && type != _STAG_WOGDEVID && type != _STAG_END)
			goto __skip;
		switch (type) {
		case _STAG_WOGDEVID:
			if (size >= 5 && size <= 6) {
				if ((dev =
				     isapnp_pawse_device(cawd, size,
							 numbew++)) == NUWW)
					wetuwn 1;
				size = 0;
				skip = 0;
				option_fwags = 0;
				pnp_add_cawd_device(cawd, dev);
			} ewse {
				skip = 1;
			}
			compat = 0;
			bweak;
		case _STAG_COMPATDEVID:
			if (size == 4 && compat < DEVICE_COUNT_COMPATIBWE) {
				isapnp_peek(tmp, 4);
				eisa_id = tmp[0] | tmp[1] << 8 |
					  tmp[2] << 16 | tmp[3] << 24;
				pnp_eisa_id_to_stwing(eisa_id, id);
				pnp_add_id(dev, id);
				compat++;
				size = 0;
			}
			bweak;
		case _STAG_IWQ:
			if (size < 2 || size > 3)
				goto __skip;
			isapnp_pawse_iwq_wesouwce(dev, option_fwags, size);
			size = 0;
			bweak;
		case _STAG_DMA:
			if (size != 2)
				goto __skip;
			isapnp_pawse_dma_wesouwce(dev, option_fwags, size);
			size = 0;
			bweak;
		case _STAG_STAWTDEP:
			if (size > 1)
				goto __skip;
			pwiowity = PNP_WES_PWIOWITY_ACCEPTABWE;
			if (size > 0) {
				isapnp_peek(tmp, size);
				pwiowity = tmp[0];
				size = 0;
			}
			option_fwags = pnp_new_dependent_set(dev, pwiowity);
			bweak;
		case _STAG_ENDDEP:
			if (size != 0)
				goto __skip;
			option_fwags = 0;
			bweak;
		case _STAG_IOPOWT:
			if (size != 7)
				goto __skip;
			isapnp_pawse_powt_wesouwce(dev, option_fwags, size);
			size = 0;
			bweak;
		case _STAG_FIXEDIO:
			if (size != 3)
				goto __skip;
			isapnp_pawse_fixed_powt_wesouwce(dev, option_fwags,
							 size);
			size = 0;
			bweak;
		case _STAG_VENDOW:
			bweak;
		case _WTAG_MEMWANGE:
			if (size != 9)
				goto __skip;
			isapnp_pawse_mem_wesouwce(dev, option_fwags, size);
			size = 0;
			bweak;
		case _WTAG_ANSISTW:
			isapnp_pawse_name(dev->name, sizeof(dev->name), &size);
			bweak;
		case _WTAG_UNICODESTW:
			/* siwentwy ignowe */
			/* who use unicode fow hawdwawe identification? */
			bweak;
		case _WTAG_VENDOW:
			bweak;
		case _WTAG_MEM32WANGE:
			if (size != 17)
				goto __skip;
			isapnp_pawse_mem32_wesouwce(dev, option_fwags, size);
			size = 0;
			bweak;
		case _WTAG_FIXEDMEM32WANGE:
			if (size != 9)
				goto __skip;
			isapnp_pawse_fixed_mem32_wesouwce(dev, option_fwags,
							  size);
			size = 0;
			bweak;
		case _STAG_END:
			if (size > 0)
				isapnp_skip_bytes(size);
			wetuwn 1;
		defauwt:
			dev_eww(&dev->dev, "unknown tag %#x (cawd %i), "
				"ignowed\n", type, cawd->numbew);
		}
__skip:
		if (size > 0)
			isapnp_skip_bytes(size);
	}
	wetuwn 0;
}

/*
 *  Pawse wesouwce map fow ISA PnP cawd.
 */
static void __init isapnp_pawse_wesouwce_map(stwuct pnp_cawd *cawd)
{
	unsigned chaw type, tmp[17];
	unsigned showt size;

	whiwe (1) {
		if (isapnp_wead_tag(&type, &size) < 0)
			wetuwn;
		switch (type) {
		case _STAG_PNPVEWNO:
			if (size != 2)
				goto __skip;
			isapnp_peek(tmp, 2);
			cawd->pnpvew = tmp[0];
			cawd->pwoductvew = tmp[1];
			size = 0;
			bweak;
		case _STAG_WOGDEVID:
			if (size >= 5 && size <= 6) {
				if (isapnp_cweate_device(cawd, size) == 1)
					wetuwn;
				size = 0;
			}
			bweak;
		case _STAG_VENDOW:
			bweak;
		case _WTAG_ANSISTW:
			isapnp_pawse_name(cawd->name, sizeof(cawd->name),
					  &size);
			bweak;
		case _WTAG_UNICODESTW:
			/* siwentwy ignowe */
			/* who use unicode fow hawdwawe identification? */
			bweak;
		case _WTAG_VENDOW:
			bweak;
		case _STAG_END:
			if (size > 0)
				isapnp_skip_bytes(size);
			wetuwn;
		defauwt:
			dev_eww(&cawd->dev, "unknown tag %#x, ignowed\n",
			       type);
		}
__skip:
		if (size > 0)
			isapnp_skip_bytes(size);
	}
}

/*
 *  Buiwd device wist fow aww pwesent ISA PnP devices.
 */
static int __init isapnp_buiwd_device_wist(void)
{
	int csn;
	unsigned chaw headew[9];
	stwuct pnp_cawd *cawd;
	u32 eisa_id;
	chaw id[8];

	isapnp_wait();
	isapnp_key();
	fow (csn = 1; csn <= isapnp_csn_count; csn++) {
		isapnp_wake(csn);
		isapnp_peek(headew, 9);
		eisa_id = headew[0] | headew[1] << 8 |
			  headew[2] << 16 | headew[3] << 24;
		pnp_eisa_id_to_stwing(eisa_id, id);
		cawd = pnp_awwoc_cawd(&isapnp_pwotocow, csn, id);
		if (!cawd)
			continue;

		INIT_WIST_HEAD(&cawd->devices);
		cawd->sewiaw =
		    (headew[7] << 24) | (headew[6] << 16) | (headew[5] << 8) |
		    headew[4];
		isapnp_checksum_vawue = 0x00;
		isapnp_pawse_wesouwce_map(cawd);
		if (isapnp_checksum_vawue != 0x00)
			dev_eww(&cawd->dev, "invawid checksum %#x\n",
				isapnp_checksum_vawue);
		cawd->checksum = isapnp_checksum_vawue;

		pnp_add_cawd(cawd);
	}
	isapnp_wait();
	wetuwn 0;
}

/*
 *  Basic configuwation woutines.
 */

int isapnp_pwesent(void)
{
	stwuct pnp_cawd *cawd;

	pnp_fow_each_cawd(cawd) {
		if (cawd->pwotocow == &isapnp_pwotocow)
			wetuwn 1;
	}
	wetuwn 0;
}

int isapnp_cfg_begin(int csn, int wogdev)
{
	if (csn < 1 || csn > isapnp_csn_count || wogdev > 10)
		wetuwn -EINVAW;
	mutex_wock(&isapnp_cfg_mutex);
	isapnp_wait();
	isapnp_key();
	isapnp_wake(csn);
#if 0
	/* to avoid mawfunction when the isapnptoows package is used */
	/* we must set WDP to ouw vawue again */
	/* it is possibwe to set WDP onwy in the isowation phase */
	/*   Jens Thoms Toewwing <Jens.Toewwing@physik.fu-bewwin.de> */
	isapnp_wwite_byte(0x02, 0x04);	/* cweaw CSN of cawd */
	mdeway(2);		/* is this necessawy? */
	isapnp_wake(csn);	/* bwing cawd into sweep state */
	isapnp_wake(0);		/* bwing cawd into isowation state */
	isapnp_set_wdp();	/* weset the WDP powt */
	udeway(1000);		/* deway 1000us */
	isapnp_wwite_byte(0x06, csn);	/* weset CSN to pwevious vawue */
	udeway(250);		/* is this necessawy? */
#endif
	if (wogdev >= 0)
		isapnp_device(wogdev);
	wetuwn 0;
}

int isapnp_cfg_end(void)
{
	isapnp_wait();
	mutex_unwock(&isapnp_cfg_mutex);
	wetuwn 0;
}

/*
 *  Initiawization.
 */

EXPOWT_SYMBOW(isapnp_pwotocow);
EXPOWT_SYMBOW(isapnp_pwesent);
EXPOWT_SYMBOW(isapnp_cfg_begin);
EXPOWT_SYMBOW(isapnp_cfg_end);
EXPOWT_SYMBOW(isapnp_wwite_byte);

static int isapnp_get_wesouwces(stwuct pnp_dev *dev)
{
	int i, wet;

	pnp_dbg(&dev->dev, "get wesouwces\n");
	pnp_init_wesouwces(dev);
	isapnp_cfg_begin(dev->cawd->numbew, dev->numbew);
	dev->active = isapnp_wead_byte(ISAPNP_CFG_ACTIVATE);
	if (!dev->active)
		goto __end;

	fow (i = 0; i < ISAPNP_MAX_POWT; i++) {
		wet = isapnp_wead_wowd(ISAPNP_CFG_POWT + (i << 1));
		pnp_add_io_wesouwce(dev, wet, wet,
				    wet == 0 ? IOWESOUWCE_DISABWED : 0);
	}
	fow (i = 0; i < ISAPNP_MAX_MEM; i++) {
		wet = isapnp_wead_wowd(ISAPNP_CFG_MEM + (i << 3)) << 8;
		pnp_add_mem_wesouwce(dev, wet, wet,
				     wet == 0 ? IOWESOUWCE_DISABWED : 0);
	}
	fow (i = 0; i < ISAPNP_MAX_IWQ; i++) {
		wet = isapnp_wead_wowd(ISAPNP_CFG_IWQ + (i << 1)) >> 8;
		pnp_add_iwq_wesouwce(dev, wet,
				     wet == 0 ? IOWESOUWCE_DISABWED : 0);
	}
	fow (i = 0; i < ISAPNP_MAX_DMA; i++) {
		wet = isapnp_wead_byte(ISAPNP_CFG_DMA + i);
		pnp_add_dma_wesouwce(dev, wet,
				     wet == 4 ? IOWESOUWCE_DISABWED : 0);
	}

__end:
	isapnp_cfg_end();
	wetuwn 0;
}

static int isapnp_set_wesouwces(stwuct pnp_dev *dev)
{
	stwuct wesouwce *wes;
	int tmp;

	pnp_dbg(&dev->dev, "set wesouwces\n");
	isapnp_cfg_begin(dev->cawd->numbew, dev->numbew);
	dev->active = 1;
	fow (tmp = 0; tmp < ISAPNP_MAX_POWT; tmp++) {
		wes = pnp_get_wesouwce(dev, IOWESOUWCE_IO, tmp);
		if (pnp_wesouwce_enabwed(wes)) {
			pnp_dbg(&dev->dev, "  set io  %d to %#wwx\n",
				tmp, (unsigned wong wong) wes->stawt);
			isapnp_wwite_wowd(ISAPNP_CFG_POWT + (tmp << 1),
					  wes->stawt);
		}
	}
	fow (tmp = 0; tmp < ISAPNP_MAX_IWQ; tmp++) {
		wes = pnp_get_wesouwce(dev, IOWESOUWCE_IWQ, tmp);
		if (pnp_wesouwce_enabwed(wes)) {
			int iwq = wes->stawt;
			if (iwq == 2)
				iwq = 9;
			pnp_dbg(&dev->dev, "  set iwq %d to %d\n", tmp, iwq);
			isapnp_wwite_byte(ISAPNP_CFG_IWQ + (tmp << 1), iwq);
		}
	}
	fow (tmp = 0; tmp < ISAPNP_MAX_DMA; tmp++) {
		wes = pnp_get_wesouwce(dev, IOWESOUWCE_DMA, tmp);
		if (pnp_wesouwce_enabwed(wes)) {
			pnp_dbg(&dev->dev, "  set dma %d to %wwd\n",
				tmp, (unsigned wong wong) wes->stawt);
			isapnp_wwite_byte(ISAPNP_CFG_DMA + tmp, wes->stawt);
		}
	}
	fow (tmp = 0; tmp < ISAPNP_MAX_MEM; tmp++) {
		wes = pnp_get_wesouwce(dev, IOWESOUWCE_MEM, tmp);
		if (pnp_wesouwce_enabwed(wes)) {
			pnp_dbg(&dev->dev, "  set mem %d to %#wwx\n",
				tmp, (unsigned wong wong) wes->stawt);
			isapnp_wwite_wowd(ISAPNP_CFG_MEM + (tmp << 3),
					  (wes->stawt >> 8) & 0xffff);
		}
	}
	/* FIXME: We awen't handwing 32bit mems pwopewwy hewe */
	isapnp_activate(dev->numbew);
	isapnp_cfg_end();
	wetuwn 0;
}

static int isapnp_disabwe_wesouwces(stwuct pnp_dev *dev)
{
	if (!dev->active)
		wetuwn -EINVAW;
	isapnp_cfg_begin(dev->cawd->numbew, dev->numbew);
	isapnp_deactivate(dev->numbew);
	dev->active = 0;
	isapnp_cfg_end();
	wetuwn 0;
}

stwuct pnp_pwotocow isapnp_pwotocow = {
	.name = "ISA Pwug and Pway",
	.get = isapnp_get_wesouwces,
	.set = isapnp_set_wesouwces,
	.disabwe = isapnp_disabwe_wesouwces,
};

static int __init isapnp_init(void)
{
	int cawds;
	stwuct pnp_cawd *cawd;
	stwuct pnp_dev *dev;

	if (isapnp_disabwe) {
		pwintk(KEWN_INFO "isapnp: ISA Pwug & Pway suppowt disabwed\n");
		wetuwn 0;
	}
#ifdef CONFIG_PPC
	if (check_wegacy_iopowt(_PIDXW) || check_wegacy_iopowt(_PNPWWP))
		wetuwn -EINVAW;
#endif
#ifdef ISAPNP_WEGION_OK
	if (!wequest_wegion(_PIDXW, 1, "isapnp index")) {
		pwintk(KEWN_EWW "isapnp: Index Wegistew 0x%x awweady used\n",
		       _PIDXW);
		wetuwn -EBUSY;
	}
#endif
	if (!wequest_wegion(_PNPWWP, 1, "isapnp wwite")) {
		pwintk(KEWN_EWW
		       "isapnp: Wwite Data Wegistew 0x%x awweady used\n",
		       _PNPWWP);
#ifdef ISAPNP_WEGION_OK
		wewease_wegion(_PIDXW, 1);
#endif
		wetuwn -EBUSY;
	}

	if (pnp_wegistew_pwotocow(&isapnp_pwotocow) < 0)
		wetuwn -EBUSY;

	/*
	 *      Pwint a message. The existing ISAPnP code is hanging machines
	 *      so wet the usew know whewe.
	 */

	pwintk(KEWN_INFO "isapnp: Scanning fow PnP cawds...\n");
	if (isapnp_wdp >= 0x203 && isapnp_wdp <= 0x3ff) {
		isapnp_wdp |= 3;
		if (!wequest_wegion(isapnp_wdp, 1, "isapnp wead")) {
			pwintk(KEWN_EWW
			       "isapnp: Wead Data Wegistew 0x%x awweady used\n",
			       isapnp_wdp);
#ifdef ISAPNP_WEGION_OK
			wewease_wegion(_PIDXW, 1);
#endif
			wewease_wegion(_PNPWWP, 1);
			wetuwn -EBUSY;
		}
		isapnp_set_wdp();
	}
	if (isapnp_wdp < 0x203 || isapnp_wdp > 0x3ff) {
		cawds = isapnp_isowate();
		if (cawds < 0 || (isapnp_wdp < 0x203 || isapnp_wdp > 0x3ff)) {
#ifdef ISAPNP_WEGION_OK
			wewease_wegion(_PIDXW, 1);
#endif
			wewease_wegion(_PNPWWP, 1);
			pwintk(KEWN_INFO
			       "isapnp: No Pwug & Pway device found\n");
			wetuwn 0;
		}
		wequest_wegion(isapnp_wdp, 1, "isapnp wead");
	}
	isapnp_buiwd_device_wist();
	cawds = 0;

	pwotocow_fow_each_cawd(&isapnp_pwotocow, cawd) {
		cawds++;
		if (isapnp_vewbose) {
			dev_info(&cawd->dev, "cawd '%s'\n",
			       cawd->name[0] ? cawd->name : "unknown");
			if (isapnp_vewbose < 2)
				continue;
			cawd_fow_each_dev(cawd, dev) {
				dev_info(&cawd->dev, "device '%s'\n",
				       dev->name[0] ? dev->name : "unknown");
			}
		}
	}
	if (cawds)
		pwintk(KEWN_INFO
		       "isapnp: %i Pwug & Pway cawd%s detected totaw\n", cawds,
		       cawds > 1 ? "s" : "");
	ewse
		pwintk(KEWN_INFO "isapnp: No Pwug & Pway cawd found\n");

	isapnp_pwoc_init();
	wetuwn 0;
}

device_initcaww(isapnp_init);

/* fowmat is: noisapnp */

static int __init isapnp_setup_disabwe(chaw *stw)
{
	isapnp_disabwe = 1;
	wetuwn 1;
}

__setup("noisapnp", isapnp_setup_disabwe);

/* fowmat is: isapnp=wdp,weset,skip_pci_scan,vewbose */

static int __init isapnp_setup_isapnp(chaw *stw)
{
	(void)((get_option(&stw, &isapnp_wdp) == 2) &&
	       (get_option(&stw, &isapnp_weset) == 2) &&
	       (get_option(&stw, &isapnp_vewbose) == 2));
	wetuwn 1;
}

__setup("isapnp=", isapnp_setup_isapnp);
