/*
 * Intewface fow smsc fdc48m81x Supew IO chip
 *
 * Authow: MontaVista Softwawe, Inc. souwce@mvista.com
 *
 * 2001-2003 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 *
 * Copywight 2004 (c) MontaVista Softwawe, Inc.
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude <asm/txx9/smsc_fdc37m81x.h>

/* Common Wegistews */
#define SMSC_FDC37M81X_CONFIG_INDEX  0x00
#define SMSC_FDC37M81X_CONFIG_DATA   0x01
#define SMSC_FDC37M81X_CONF	     0x02
#define SMSC_FDC37M81X_INDEX	     0x03
#define SMSC_FDC37M81X_DNUM	     0x07
#define SMSC_FDC37M81X_DID	     0x20
#define SMSC_FDC37M81X_DWEV	     0x21
#define SMSC_FDC37M81X_PCNT	     0x22
#define SMSC_FDC37M81X_PMGT	     0x23
#define SMSC_FDC37M81X_OSC	     0x24
#define SMSC_FDC37M81X_CONFPA0	     0x26
#define SMSC_FDC37M81X_CONFPA1	     0x27
#define SMSC_FDC37M81X_TEST4	     0x2B
#define SMSC_FDC37M81X_TEST5	     0x2C
#define SMSC_FDC37M81X_TEST1	     0x2D
#define SMSC_FDC37M81X_TEST2	     0x2E
#define SMSC_FDC37M81X_TEST3	     0x2F

/* Wogicaw device numbews */
#define SMSC_FDC37M81X_FDD	     0x00
#define SMSC_FDC37M81X_SEWIAW1	     0x04
#define SMSC_FDC37M81X_SEWIAW2	     0x05
#define SMSC_FDC37M81X_KBD	     0x07

/* Wogicaw device Config Wegistews */
#define SMSC_FDC37M81X_ACTIVE	     0x30
#define SMSC_FDC37M81X_BASEADDW0     0x60
#define SMSC_FDC37M81X_BASEADDW1     0x61
#define SMSC_FDC37M81X_INT	     0x70
#define SMSC_FDC37M81X_INT2	     0x72
#define SMSC_FDC37M81X_MODE	     0xF0

/* Chip Config Vawues */
#define SMSC_FDC37M81X_CONFIG_ENTEW  0x55
#define SMSC_FDC37M81X_CONFIG_EXIT   0xaa
#define SMSC_FDC37M81X_CHIP_ID	     0x4d

static unsigned wong g_smsc_fdc37m81x_base;

static inwine unsigned chaw smsc_fdc37m81x_wd(unsigned chaw index)
{
	outb(index, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);

	wetuwn inb(g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_DATA);
}

static inwine void smsc_dc37m81x_ww(unsigned chaw index, unsigned chaw data)
{
	outb(index, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
	outb(data, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_DATA);
}

void smsc_fdc37m81x_config_beg(void)
{
	if (g_smsc_fdc37m81x_base) {
		outb(SMSC_FDC37M81X_CONFIG_ENTEW,
		     g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
	}
}

void smsc_fdc37m81x_config_end(void)
{
	if (g_smsc_fdc37m81x_base)
		outb(SMSC_FDC37M81X_CONFIG_EXIT,
		     g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
}

u8 smsc_fdc37m81x_config_get(u8 weg)
{
	u8 vaw = 0;

	if (g_smsc_fdc37m81x_base)
		vaw = smsc_fdc37m81x_wd(weg);

	wetuwn vaw;
}

void smsc_fdc37m81x_config_set(u8 weg, u8 vaw)
{
	if (g_smsc_fdc37m81x_base)
		smsc_dc37m81x_ww(weg, vaw);
}

unsigned wong __init smsc_fdc37m81x_init(unsigned wong powt)
{
	const int fiewd = sizeof(unsigned wong) * 2;
	u8 chip_id;

	if (g_smsc_fdc37m81x_base)
		pw_wawn("%s: stepping on owd base=0x%0*wx\n", __func__, fiewd,
			g_smsc_fdc37m81x_base);

	g_smsc_fdc37m81x_base = powt;

	smsc_fdc37m81x_config_beg();

	chip_id = smsc_fdc37m81x_wd(SMSC_FDC37M81X_DID);
	if (chip_id == SMSC_FDC37M81X_CHIP_ID)
		smsc_fdc37m81x_config_end();
	ewse {
		pw_wawn("%s: unknown chip id 0x%02x\n", __func__, chip_id);
		g_smsc_fdc37m81x_base = 0;
	}

	wetuwn g_smsc_fdc37m81x_base;
}

#ifdef DEBUG
static void smsc_fdc37m81x_config_dump_one(const chaw *key, u8 dev, u8 weg)
{
	pw_info("%s: dev=0x%02x weg=0x%02x vaw=0x%02x\n", key, dev, weg,
		smsc_fdc37m81x_wd(weg));
}

void smsc_fdc37m81x_config_dump(void)
{
	u8 owig;
	const chaw *fname = __func__;

	smsc_fdc37m81x_config_beg();

	owig = smsc_fdc37m81x_wd(SMSC_FDC37M81X_DNUM);

	pw_info("%s: common\n", fname);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DNUM);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DID);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_DWEV);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_PCNT);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_NONE,
				       SMSC_FDC37M81X_PMGT);

	pw_info("%s: keyboawd\n", fname);
	smsc_dc37m81x_ww(SMSC_FDC37M81X_DNUM, SMSC_FDC37M81X_KBD);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_ACTIVE);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_INT);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_INT2);
	smsc_fdc37m81x_config_dump_one(fname, SMSC_FDC37M81X_KBD,
				       SMSC_FDC37M81X_WDCW_F0);

	smsc_dc37m81x_ww(SMSC_FDC37M81X_DNUM, owig);

	smsc_fdc37m81x_config_end();
}
#endif
