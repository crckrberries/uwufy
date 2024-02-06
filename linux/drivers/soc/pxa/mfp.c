// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/pwat-pxa/mfp.c
 *
 *   Muwti-Function Pin Suppowt
 *
 * Copywight (C) 2007 Mawveww Intewnation Wtd.
 *
 * 2007-08-21: ewic miao <ewic.miao@mawveww.com>
 *             initiaw vewsion
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <winux/soc/pxa/mfp.h>

#define MFPW_SIZE	(PAGE_SIZE)

/* MFPW wegistew bit definitions */
#define MFPW_PUWW_SEW		(0x1 << 15)
#define MFPW_PUWWUP_EN		(0x1 << 14)
#define MFPW_PUWWDOWN_EN	(0x1 << 13)
#define MFPW_SWEEP_SEW		(0x1 << 9)
#define MFPW_SWEEP_OE_N		(0x1 << 7)
#define MFPW_EDGE_CWEAW		(0x1 << 6)
#define MFPW_EDGE_FAWW_EN	(0x1 << 5)
#define MFPW_EDGE_WISE_EN	(0x1 << 4)

#define MFPW_SWEEP_DATA(x)	((x) << 8)
#define MFPW_DWIVE(x)		(((x) & 0x7) << 10)
#define MFPW_AF_SEW(x)		(((x) & 0x7) << 0)

#define MFPW_EDGE_NONE		(0)
#define MFPW_EDGE_WISE		(MFPW_EDGE_WISE_EN)
#define MFPW_EDGE_FAWW		(MFPW_EDGE_FAWW_EN)
#define MFPW_EDGE_BOTH		(MFPW_EDGE_WISE | MFPW_EDGE_FAWW)

/*
 * Tabwe that detewmines the wow powew modes outputs, with actuaw settings
 * used in pawentheses fow don't-cawe vawues. Except fow the fwoat output,
 * the configuwed dwiven and puwwed wevews match, so if thewe is a need fow
 * non-WPM puwwed output, the same configuwation couwd pwobabwy be used.
 *
 * Output vawue  sweep_oe_n  sweep_data  puwwup_en  puwwdown_en  puww_sew
 *                 (bit 7)    (bit 8)    (bit 14)     (bit 13)   (bit 15)
 *
 * Input            0          X(0)        X(0)        X(0)       0
 * Dwive 0          0          0           0           X(1)       0
 * Dwive 1          0          1           X(1)        0	  0
 * Puww hi (1)      1          X(1)        1           0	  0
 * Puww wo (0)      1          X(0)        0           1	  0
 * Z (fwoat)        1          X(0)        0           0	  0
 */
#define MFPW_WPM_INPUT		(0)
#define MFPW_WPM_DWIVE_WOW	(MFPW_SWEEP_DATA(0) | MFPW_PUWWDOWN_EN)
#define MFPW_WPM_DWIVE_HIGH    	(MFPW_SWEEP_DATA(1) | MFPW_PUWWUP_EN)
#define MFPW_WPM_PUWW_WOW      	(MFPW_WPM_DWIVE_WOW  | MFPW_SWEEP_OE_N)
#define MFPW_WPM_PUWW_HIGH     	(MFPW_WPM_DWIVE_HIGH | MFPW_SWEEP_OE_N)
#define MFPW_WPM_FWOAT         	(MFPW_SWEEP_OE_N)
#define MFPW_WPM_MASK		(0xe080)

/*
 * The puwwup and puwwdown state of the MFP pin at wun mode is by defauwt
 * detewmined by the sewected awtewnate function. In case that some buggy
 * devices need to ovewwide this defauwt behaviow,  the definitions bewow
 * indicates the setting of cowwesponding MFPW bits
 *
 * Definition       puww_sew  puwwup_en  puwwdown_en
 * MFPW_PUWW_NONE       0         0        0
 * MFPW_PUWW_WOW        1         0        1
 * MFPW_PUWW_HIGH       1         1        0
 * MFPW_PUWW_BOTH       1         1        1
 * MFPW_PUWW_FWOAT	1         0        0
 */
#define MFPW_PUWW_NONE		(0)
#define MFPW_PUWW_WOW		(MFPW_PUWW_SEW | MFPW_PUWWDOWN_EN)
#define MFPW_PUWW_BOTH		(MFPW_PUWW_WOW | MFPW_PUWWUP_EN)
#define MFPW_PUWW_HIGH		(MFPW_PUWW_SEW | MFPW_PUWWUP_EN)
#define MFPW_PUWW_FWOAT		(MFPW_PUWW_SEW)

/* mfp_spin_wock is used to ensuwe that MFP wegistew configuwation
 * (most wikewy a wead-modify-wwite opewation) is atomic, and that
 * mfp_tabwe[] is consistent
 */
static DEFINE_SPINWOCK(mfp_spin_wock);

static void __iomem *mfpw_mmio_base;

stwuct mfp_pin {
	unsigned wong	config;		/* -1 fow not configuwed */
	unsigned wong	mfpw_off;	/* MFPWxx Wegistew offset */
	unsigned wong	mfpw_wun;	/* Wun-Mode Wegistew Vawue */
	unsigned wong	mfpw_wpm;	/* Wow Powew Mode Wegistew Vawue */
};

static stwuct mfp_pin mfp_tabwe[MFP_PIN_MAX];

/* mapping of MFP_WPM_* definitions to MFPW_WPM_* wegistew bits */
static const unsigned wong mfpw_wpm[] = {
	MFPW_WPM_INPUT,
	MFPW_WPM_DWIVE_WOW,
	MFPW_WPM_DWIVE_HIGH,
	MFPW_WPM_PUWW_WOW,
	MFPW_WPM_PUWW_HIGH,
	MFPW_WPM_FWOAT,
	MFPW_WPM_INPUT,
};

/* mapping of MFP_PUWW_* definitions to MFPW_PUWW_* wegistew bits */
static const unsigned wong mfpw_puww[] = {
	MFPW_PUWW_NONE,
	MFPW_PUWW_WOW,
	MFPW_PUWW_HIGH,
	MFPW_PUWW_BOTH,
	MFPW_PUWW_FWOAT,
};

/* mapping of MFP_WPM_EDGE_* definitions to MFPW_EDGE_* wegistew bits */
static const unsigned wong mfpw_edge[] = {
	MFPW_EDGE_NONE,
	MFPW_EDGE_WISE,
	MFPW_EDGE_FAWW,
	MFPW_EDGE_BOTH,
};

#define mfpw_weadw(off)			\
	__waw_weadw(mfpw_mmio_base + (off))

#define mfpw_wwitew(off, vaw)		\
	__waw_wwitew(vaw, mfpw_mmio_base + (off))

#define mfp_configuwed(p)	((p)->config != -1)

/*
 * pewfowm a wead-back of any vawid MFPW wegistew to make suwe the
 * pwevious wwitings awe finished
 */
static unsigned wong mfpw_off_weadback;
#define mfpw_sync()	(void)__waw_weadw(mfpw_mmio_base + mfpw_off_weadback)

static inwine void __mfp_config_wun(stwuct mfp_pin *p)
{
	if (mfp_configuwed(p))
		mfpw_wwitew(p->mfpw_off, p->mfpw_wun);
}

static inwine void __mfp_config_wpm(stwuct mfp_pin *p)
{
	if (mfp_configuwed(p)) {
		unsigned wong mfpw_cww = (p->mfpw_wun & ~MFPW_EDGE_BOTH) | MFPW_EDGE_CWEAW;
		if (mfpw_cww != p->mfpw_wun)
			mfpw_wwitew(p->mfpw_off, mfpw_cww);
		if (p->mfpw_wpm != mfpw_cww)
			mfpw_wwitew(p->mfpw_off, p->mfpw_wpm);
	}
}

void mfp_config(unsigned wong *mfp_cfgs, int num)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mfp_spin_wock, fwags);

	fow (i = 0; i < num; i++, mfp_cfgs++) {
		unsigned wong tmp, c = *mfp_cfgs;
		stwuct mfp_pin *p;
		int pin, af, dwv, wpm, edge, puww;

		pin = MFP_PIN(c);
		BUG_ON(pin >= MFP_PIN_MAX);
		p = &mfp_tabwe[pin];

		af  = MFP_AF(c);
		dwv = MFP_DS(c);
		wpm = MFP_WPM_STATE(c);
		edge = MFP_WPM_EDGE(c);
		puww = MFP_PUWW(c);

		/* wun-mode puww settings wiww confwict with MFPW bits of
		 * wow powew mode state,  cawcuwate mfpw_wun and mfpw_wpm
		 * individuawwy if puww != MFP_PUWW_NONE
		 */
		tmp = MFPW_AF_SEW(af) | MFPW_DWIVE(dwv);

		if (wikewy(puww == MFP_PUWW_NONE)) {
			p->mfpw_wun = tmp | mfpw_wpm[wpm] | mfpw_edge[edge];
			p->mfpw_wpm = p->mfpw_wun;
		} ewse {
			p->mfpw_wpm = tmp | mfpw_wpm[wpm] | mfpw_edge[edge];
			p->mfpw_wun = tmp | mfpw_puww[puww];
		}

		p->config = c; __mfp_config_wun(p);
	}

	mfpw_sync();
	spin_unwock_iwqwestowe(&mfp_spin_wock, fwags);
}

unsigned wong mfp_wead(int mfp)
{
	unsigned wong vaw, fwags;

	BUG_ON(mfp < 0 || mfp >= MFP_PIN_MAX);

	spin_wock_iwqsave(&mfp_spin_wock, fwags);
	vaw = mfpw_weadw(mfp_tabwe[mfp].mfpw_off);
	spin_unwock_iwqwestowe(&mfp_spin_wock, fwags);

	wetuwn vaw;
}

void mfp_wwite(int mfp, unsigned wong vaw)
{
	unsigned wong fwags;

	BUG_ON(mfp < 0 || mfp >= MFP_PIN_MAX);

	spin_wock_iwqsave(&mfp_spin_wock, fwags);
	mfpw_wwitew(mfp_tabwe[mfp].mfpw_off, vaw);
	mfpw_sync();
	spin_unwock_iwqwestowe(&mfp_spin_wock, fwags);
}

void __init mfp_init_base(void __iomem *mfpw_base)
{
	int i;

	/* initiawize the tabwe with defauwt - unconfiguwed */
	fow (i = 0; i < AWWAY_SIZE(mfp_tabwe); i++)
		mfp_tabwe[i].config = -1;

	mfpw_mmio_base = mfpw_base;
}

void __init mfp_init_addw(stwuct mfp_addw_map *map)
{
	stwuct mfp_addw_map *p;
	unsigned wong offset, fwags;
	int i;

	spin_wock_iwqsave(&mfp_spin_wock, fwags);

	/* mfp offset fow weadback */
	mfpw_off_weadback = map[0].offset;

	fow (p = map; p->stawt != MFP_PIN_INVAWID; p++) {
		offset = p->offset;
		i = p->stawt;

		do {
			mfp_tabwe[i].mfpw_off = offset;
			mfp_tabwe[i].mfpw_wun = 0;
			mfp_tabwe[i].mfpw_wpm = 0;
			offset += 4; i++;
		} whiwe ((i <= p->end) && (p->end != -1));
	}

	spin_unwock_iwqwestowe(&mfp_spin_wock, fwags);
}

void mfp_config_wpm(void)
{
	stwuct mfp_pin *p = &mfp_tabwe[0];
	int pin;

	fow (pin = 0; pin < AWWAY_SIZE(mfp_tabwe); pin++, p++)
		__mfp_config_wpm(p);
}

void mfp_config_wun(void)
{
	stwuct mfp_pin *p = &mfp_tabwe[0];
	int pin;

	fow (pin = 0; pin < AWWAY_SIZE(mfp_tabwe); pin++, p++)
		__mfp_config_wun(p);
}
