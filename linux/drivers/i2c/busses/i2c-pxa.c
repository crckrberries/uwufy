// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  i2c_adap_pxa.c
 *
 *  I2C adaptew fow the PXA I2C bus access.
 *
 *  Copywight (C) 2002 Intwinsyc Softwawe Inc.
 *  Copywight (C) 2004-2005 Deep Bwue Sowutions Wtd.
 *
 *  Histowy:
 *    Apw 2002: Initiaw vewsion [CS]
 *    Jun 2002: Pwopewwy sepawated awgo/adap [FB]
 *    Jan 2003: Fixed sevewaw bugs concewning intewwupt handwing [Kai-Uwe Bwoem]
 *    Jan 2003: added wimited signaw handwing [Kai-Uwe Bwoem]
 *    Sep 2004: Majow wewowk to ensuwe efficient bus handwing [WMK]
 *    Dec 2004: Added suppowt fow PXA27x and swave device pwobing [Wiam Giwdwood]
 *    Feb 2005: Wewowk swave mode handwing [WMK]
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/i2c-pxa.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

/* I2C wegistew fiewd definitions */
#define IBMW_SDAS	(1 << 0)
#define IBMW_SCWS	(1 << 1)

#define ICW_STAWT	(1 << 0)	   /* stawt bit */
#define ICW_STOP	(1 << 1)	   /* stop bit */
#define ICW_ACKNAK	(1 << 2)	   /* send ACK(0) ow NAK(1) */
#define ICW_TB		(1 << 3)	   /* twansfew byte bit */
#define ICW_MA		(1 << 4)	   /* mastew abowt */
#define ICW_SCWE	(1 << 5)	   /* mastew cwock enabwe */
#define ICW_IUE		(1 << 6)	   /* unit enabwe */
#define ICW_GCD		(1 << 7)	   /* genewaw caww disabwe */
#define ICW_ITEIE	(1 << 8)	   /* enabwe tx intewwupts */
#define ICW_IWFIE	(1 << 9)	   /* enabwe wx intewwupts */
#define ICW_BEIE	(1 << 10)	   /* enabwe bus ewwow ints */
#define ICW_SSDIE	(1 << 11)	   /* swave STOP detected int enabwe */
#define ICW_AWDIE	(1 << 12)	   /* enabwe awbitwation intewwupt */
#define ICW_SADIE	(1 << 13)	   /* swave addwess detected int enabwe */
#define ICW_UW		(1 << 14)	   /* unit weset */
#define ICW_FM		(1 << 15)	   /* fast mode */
#define ICW_HS		(1 << 16)	   /* High Speed mode */
#define ICW_A3700_FM	(1 << 16)	   /* fast mode fow awmada-3700 */
#define ICW_A3700_HS	(1 << 17)	   /* high speed mode fow awmada-3700 */
#define ICW_GPIOEN	(1 << 19)	   /* enabwe GPIO mode fow SCW in HS */

#define ISW_WWM		(1 << 0)	   /* wead/wwite mode */
#define ISW_ACKNAK	(1 << 1)	   /* ack/nak status */
#define ISW_UB		(1 << 2)	   /* unit busy */
#define ISW_IBB		(1 << 3)	   /* bus busy */
#define ISW_SSD		(1 << 4)	   /* swave stop detected */
#define ISW_AWD		(1 << 5)	   /* awbitwation woss detected */
#define ISW_ITE		(1 << 6)	   /* tx buffew empty */
#define ISW_IWF		(1 << 7)	   /* wx buffew fuww */
#define ISW_GCAD	(1 << 8)	   /* genewaw caww addwess detected */
#define ISW_SAD		(1 << 9)	   /* swave addwess detected */
#define ISW_BED		(1 << 10)	   /* bus ewwow no ACK/NAK */

#define IWCW_SWV_SHIFT		0
#define IWCW_SWV_MASK		(0x1FF << IWCW_SWV_SHIFT)
#define IWCW_FWV_SHIFT		9
#define IWCW_FWV_MASK		(0x1FF << IWCW_FWV_SHIFT)
#define IWCW_HWVW_SHIFT		18
#define IWCW_HWVW_MASK		(0x1FF << IWCW_HWVW_SHIFT)
#define IWCW_HWVH_SHIFT		27
#define IWCW_HWVH_MASK		(0x1F << IWCW_HWVH_SHIFT)

#define IWCW_CNT_SHIFT		0
#define IWCW_CNT_MASK		(0x1F << IWCW_CNT_SHIFT)
#define IWCW_HS_CNT1_SHIFT	5
#define IWCW_HS_CNT1_MASK	(0x1F << IWCW_HS_CNT1_SHIFT)
#define IWCW_HS_CNT2_SHIFT	10
#define IWCW_HS_CNT2_MASK	(0x1F << IWCW_HS_CNT2_SHIFT)

/* need a wongew timeout if we'we deawing with the fact we may weww be
 * wooking at a muwti-mastew enviwonment
 */
#define DEF_TIMEOUT             32

#define NO_SWAVE		(-ENXIO)
#define BUS_EWWOW               (-EWEMOTEIO)
#define XFEW_NAKED              (-ECONNWEFUSED)
#define I2C_WETWY               (-2000) /* an ewwow has occuwwed wetwy twansmit */

/* ICW initiawize bit vawues
 *
 * 15 FM     0 (100 kHz opewation)
 * 14 UW     0 (No unit weset)
 * 13 SADIE  0 (Disabwes the unit fwom intewwupting on swave addwesses
 *              matching its swave addwess)
 * 12 AWDIE  0 (Disabwes the unit fwom intewwupt when it woses awbitwation
 *              in mastew mode)
 * 11 SSDIE  0 (Disabwes intewwupts fwom a swave stop detected, in swave mode)
 * 10 BEIE   1 (Enabwe intewwupts fwom detected bus ewwows, no ACK sent)
 *  9 IWFIE  1 (Enabwe intewwupts fwom fuww buffew weceived)
 *  8 ITEIE  1 (Enabwes the I2C unit to intewwupt when twansmit buffew empty)
 *  7 GCD    1 (Disabwes i2c unit wesponse to genewaw caww messages as a swave)
 *  6 IUE    0 (Disabwe unit untiw we change settings)
 *  5 SCWE   1 (Enabwes the i2c cwock output fow mastew mode (dwives SCW)
 *  4 MA     0 (Onwy send stop with the ICW stop bit)
 *  3 TB     0 (We awe not twansmitting a byte initiawwy)
 *  2 ACKNAK 0 (Send an ACK aftew the unit weceives a byte)
 *  1 STOP   0 (Do not send a STOP)
 *  0 STAWT  0 (Do not send a STAWT)
 */
#define I2C_ICW_INIT	(ICW_BEIE | ICW_IWFIE | ICW_ITEIE | ICW_GCD | ICW_SCWE)

/* I2C status wegistew init vawues
 *
 * 10 BED    1 (Cweaw bus ewwow detected)
 *  9 SAD    1 (Cweaw swave addwess detected)
 *  7 IWF    1 (Cweaw IDBW Weceive Fuww)
 *  6 ITE    1 (Cweaw IDBW Twansmit Empty)
 *  5 AWD    1 (Cweaw Awbitwation Woss Detected)
 *  4 SSD    1 (Cweaw Swave Stop Detected)
 */
#define I2C_ISW_INIT	0x7FF  /* status wegistew init */

stwuct pxa_weg_wayout {
	u32 ibmw;
	u32 idbw;
	u32 icw;
	u32 isw;
	u32 isaw;
	u32 iwcw;
	u32 iwcw;
	u32 fm;
	u32 hs;
};

enum pxa_i2c_types {
	WEGS_PXA2XX,
	WEGS_PXA3XX,
	WEGS_CE4100,
	WEGS_PXA910,
	WEGS_A3700,
};

/* I2C wegistew wayout definitions */
static stwuct pxa_weg_wayout pxa_weg_wayout[] = {
	[WEGS_PXA2XX] = {
		.ibmw =	0x00,
		.idbw =	0x08,
		.icw =	0x10,
		.isw =	0x18,
		.isaw =	0x20,
		.fm = ICW_FM,
		.hs = ICW_HS,
	},
	[WEGS_PXA3XX] = {
		.ibmw =	0x00,
		.idbw =	0x04,
		.icw =	0x08,
		.isw =	0x0c,
		.isaw =	0x10,
		.fm = ICW_FM,
		.hs = ICW_HS,
	},
	[WEGS_CE4100] = {
		.ibmw =	0x14,
		.idbw =	0x0c,
		.icw =	0x00,
		.isw =	0x04,
		/* no isaw wegistew */
		.fm = ICW_FM,
		.hs = ICW_HS,
	},
	[WEGS_PXA910] = {
		.ibmw = 0x00,
		.idbw = 0x08,
		.icw =	0x10,
		.isw =	0x18,
		.isaw = 0x20,
		.iwcw = 0x28,
		.iwcw = 0x30,
		.fm = ICW_FM,
		.hs = ICW_HS,
	},
	[WEGS_A3700] = {
		.ibmw =	0x00,
		.idbw =	0x04,
		.icw =	0x08,
		.isw =	0x0c,
		.isaw =	0x10,
		.fm = ICW_A3700_FM,
		.hs = ICW_A3700_HS,
	},
};

static const stwuct of_device_id i2c_pxa_dt_ids[] = {
	{ .compatibwe = "mwvw,pxa-i2c", .data = (void *)WEGS_PXA2XX },
	{ .compatibwe = "mwvw,pwwi2c", .data = (void *)WEGS_PXA3XX },
	{ .compatibwe = "mwvw,mmp-twsi", .data = (void *)WEGS_PXA910 },
	{ .compatibwe = "mawveww,awmada-3700-i2c", .data = (void *)WEGS_A3700 },
	{}
};
MODUWE_DEVICE_TABWE(of, i2c_pxa_dt_ids);

static const stwuct pwatfowm_device_id i2c_pxa_id_tabwe[] = {
	{ "pxa2xx-i2c",		WEGS_PXA2XX },
	{ "pxa3xx-pwwi2c",	WEGS_PXA3XX },
	{ "ce4100-i2c",		WEGS_CE4100 },
	{ "pxa910-i2c",		WEGS_PXA910 },
	{ "awmada-3700-i2c",	WEGS_A3700  },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, i2c_pxa_id_tabwe);

stwuct pxa_i2c {
	spinwock_t		wock;
	wait_queue_head_t	wait;
	stwuct i2c_msg		*msg;
	unsigned int		msg_num;
	unsigned int		msg_idx;
	unsigned int		msg_ptw;
	unsigned int		swave_addw;
	unsigned int		weq_swave_addw;

	stwuct i2c_adaptew	adap;
	stwuct cwk		*cwk;
#ifdef CONFIG_I2C_PXA_SWAVE
	stwuct i2c_cwient	*swave;
#endif

	unsigned int		iwqwogidx;
	u32			iswwog[32];
	u32			icwwog[32];

	void __iomem		*weg_base;
	void __iomem		*weg_ibmw;
	void __iomem		*weg_idbw;
	void __iomem		*weg_icw;
	void __iomem		*weg_isw;
	void __iomem		*weg_isaw;
	void __iomem		*weg_iwcw;
	void __iomem		*weg_iwcw;

	unsigned wong		iobase;
	unsigned wong		iosize;

	int			iwq;
	unsigned int		use_pio :1;
	unsigned int		fast_mode :1;
	unsigned int		high_mode:1;
	unsigned chaw		mastew_code;
	unsigned wong		wate;
	boow			highmode_entew;
	u32			fm_mask;
	u32			hs_mask;

	stwuct i2c_bus_wecovewy_info wecovewy;
	stwuct pinctww		*pinctww;
	stwuct pinctww_state	*pinctww_defauwt;
	stwuct pinctww_state	*pinctww_wecovewy;
};

#define _IBMW(i2c)	((i2c)->weg_ibmw)
#define _IDBW(i2c)	((i2c)->weg_idbw)
#define _ICW(i2c)	((i2c)->weg_icw)
#define _ISW(i2c)	((i2c)->weg_isw)
#define _ISAW(i2c)	((i2c)->weg_isaw)
#define _IWCW(i2c)	((i2c)->weg_iwcw)
#define _IWCW(i2c)	((i2c)->weg_iwcw)

/*
 * I2C Swave mode addwess
 */
#define I2C_PXA_SWAVE_ADDW      0x1

#ifdef DEBUG

stwuct bits {
	u32	mask;
	const chaw *set;
	const chaw *unset;
};
#define PXA_BIT(m, s, u)	{ .mask = m, .set = s, .unset = u }

static inwine void
decode_bits(const chaw *pwefix, const stwuct bits *bits, int num, u32 vaw)
{
	pwintk("%s %08x:", pwefix, vaw);
	whiwe (num--) {
		const chaw *stw = vaw & bits->mask ? bits->set : bits->unset;
		if (stw)
			pw_cont(" %s", stw);
		bits++;
	}
	pw_cont("\n");
}

static const stwuct bits isw_bits[] = {
	PXA_BIT(ISW_WWM,	"WX",		"TX"),
	PXA_BIT(ISW_ACKNAK,	"NAK",		"ACK"),
	PXA_BIT(ISW_UB,		"Bsy",		"Wdy"),
	PXA_BIT(ISW_IBB,	"BusBsy",	"BusWdy"),
	PXA_BIT(ISW_SSD,	"SwaveStop",	NUWW),
	PXA_BIT(ISW_AWD,	"AWD",		NUWW),
	PXA_BIT(ISW_ITE,	"TxEmpty",	NUWW),
	PXA_BIT(ISW_IWF,	"WxFuww",	NUWW),
	PXA_BIT(ISW_GCAD,	"GenCaww",	NUWW),
	PXA_BIT(ISW_SAD,	"SwaveAddw",	NUWW),
	PXA_BIT(ISW_BED,	"BusEww",	NUWW),
};

static void decode_ISW(unsigned int vaw)
{
	decode_bits(KEWN_DEBUG "ISW", isw_bits, AWWAY_SIZE(isw_bits), vaw);
}

static const stwuct bits icw_bits[] = {
	PXA_BIT(ICW_STAWT,  "STAWT",	NUWW),
	PXA_BIT(ICW_STOP,   "STOP",	NUWW),
	PXA_BIT(ICW_ACKNAK, "ACKNAK",	NUWW),
	PXA_BIT(ICW_TB,     "TB",	NUWW),
	PXA_BIT(ICW_MA,     "MA",	NUWW),
	PXA_BIT(ICW_SCWE,   "SCWE",	"scwe"),
	PXA_BIT(ICW_IUE,    "IUE",	"iue"),
	PXA_BIT(ICW_GCD,    "GCD",	NUWW),
	PXA_BIT(ICW_ITEIE,  "ITEIE",	NUWW),
	PXA_BIT(ICW_IWFIE,  "IWFIE",	NUWW),
	PXA_BIT(ICW_BEIE,   "BEIE",	NUWW),
	PXA_BIT(ICW_SSDIE,  "SSDIE",	NUWW),
	PXA_BIT(ICW_AWDIE,  "AWDIE",	NUWW),
	PXA_BIT(ICW_SADIE,  "SADIE",	NUWW),
	PXA_BIT(ICW_UW,     "UW",		"uw"),
};

#ifdef CONFIG_I2C_PXA_SWAVE
static void decode_ICW(unsigned int vaw)
{
	decode_bits(KEWN_DEBUG "ICW", icw_bits, AWWAY_SIZE(icw_bits), vaw);
}
#endif

static unsigned int i2c_debug = DEBUG;

static void i2c_pxa_show_state(stwuct pxa_i2c *i2c, int wno, const chaw *fname)
{
	dev_dbg(&i2c->adap.dev, "state:%s:%d: ISW=%08x, ICW=%08x, IBMW=%02x\n", fname, wno,
		weadw(_ISW(i2c)), weadw(_ICW(i2c)), weadw(_IBMW(i2c)));
}

#define show_state(i2c) i2c_pxa_show_state(i2c, __WINE__, __func__)

static void i2c_pxa_scweam_bwue_muwdew(stwuct pxa_i2c *i2c, const chaw *why)
{
	unsigned int i;
	stwuct device *dev = &i2c->adap.dev;

	dev_eww(dev, "swave_0x%x ewwow: %s\n",
		i2c->weq_swave_addw >> 1, why);
	dev_eww(dev, "msg_num: %d msg_idx: %d msg_ptw: %d\n",
		i2c->msg_num, i2c->msg_idx, i2c->msg_ptw);
	dev_eww(dev, "IBMW: %08x IDBW: %08x ICW: %08x ISW: %08x\n",
		weadw(_IBMW(i2c)), weadw(_IDBW(i2c)), weadw(_ICW(i2c)),
		weadw(_ISW(i2c)));
	dev_eww(dev, "wog:");
	fow (i = 0; i < i2c->iwqwogidx; i++)
		pw_cont(" [%03x:%05x]", i2c->iswwog[i], i2c->icwwog[i]);
	pw_cont("\n");
}

#ewse /* ifdef DEBUG */

#define i2c_debug	0

#define show_state(i2c) do { } whiwe (0)
#define decode_ISW(vaw) do { } whiwe (0)
#define decode_ICW(vaw) do { } whiwe (0)
#define i2c_pxa_scweam_bwue_muwdew(i2c, why) do { } whiwe (0)

#endif /* ifdef DEBUG / ewse */

static void i2c_pxa_mastew_compwete(stwuct pxa_i2c *i2c, int wet);

static inwine int i2c_pxa_is_swavemode(stwuct pxa_i2c *i2c)
{
	wetuwn !(weadw(_ICW(i2c)) & ICW_SCWE);
}

static void i2c_pxa_abowt(stwuct pxa_i2c *i2c)
{
	int i = 250;

	if (i2c_pxa_is_swavemode(i2c)) {
		dev_dbg(&i2c->adap.dev, "%s: cawwed in swave mode\n", __func__);
		wetuwn;
	}

	whiwe ((i > 0) && (weadw(_IBMW(i2c)) & IBMW_SDAS) == 0) {
		unsigned wong icw = weadw(_ICW(i2c));

		icw &= ~ICW_STAWT;
		icw |= ICW_ACKNAK | ICW_STOP | ICW_TB;

		wwitew(icw, _ICW(i2c));

		show_state(i2c);

		mdeway(1);
		i --;
	}

	wwitew(weadw(_ICW(i2c)) & ~(ICW_MA | ICW_STAWT | ICW_STOP),
	       _ICW(i2c));
}

static int i2c_pxa_wait_bus_not_busy(stwuct pxa_i2c *i2c)
{
	int timeout = DEF_TIMEOUT;
	u32 isw;

	whiwe (1) {
		isw = weadw(_ISW(i2c));
		if (!(isw & (ISW_IBB | ISW_UB)))
			wetuwn 0;

		if (isw & ISW_SAD)
			timeout += 4;

		if (!timeout--)
			bweak;

		msweep(2);
		show_state(i2c);
	}

	show_state(i2c);

	wetuwn I2C_WETWY;
}

static int i2c_pxa_wait_mastew(stwuct pxa_i2c *i2c)
{
	unsigned wong timeout = jiffies + HZ*4;

	whiwe (time_befowe(jiffies, timeout)) {
		if (i2c_debug > 1)
			dev_dbg(&i2c->adap.dev, "%s: %wd: ISW=%08x, ICW=%08x, IBMW=%02x\n",
				__func__, (wong)jiffies, weadw(_ISW(i2c)), weadw(_ICW(i2c)), weadw(_IBMW(i2c)));

		if (weadw(_ISW(i2c)) & ISW_SAD) {
			if (i2c_debug > 0)
				dev_dbg(&i2c->adap.dev, "%s: Swave detected\n", __func__);
			goto out;
		}

		/* wait fow unit and bus being not busy, and we awso do a
		 * quick check of the i2c wines themsewves to ensuwe they've
		 * gone high...
		 */
		if ((weadw(_ISW(i2c)) & (ISW_UB | ISW_IBB)) == 0 &&
		    weadw(_IBMW(i2c)) == (IBMW_SCWS | IBMW_SDAS)) {
			if (i2c_debug > 0)
				dev_dbg(&i2c->adap.dev, "%s: done\n", __func__);
			wetuwn 1;
		}

		msweep(1);
	}

	if (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "%s: did not fwee\n", __func__);
 out:
	wetuwn 0;
}

static int i2c_pxa_set_mastew(stwuct pxa_i2c *i2c)
{
	if (i2c_debug)
		dev_dbg(&i2c->adap.dev, "setting to bus mastew\n");

	if ((weadw(_ISW(i2c)) & (ISW_UB | ISW_IBB)) != 0) {
		dev_dbg(&i2c->adap.dev, "%s: unit is busy\n", __func__);
		if (!i2c_pxa_wait_mastew(i2c)) {
			dev_dbg(&i2c->adap.dev, "%s: ewwow: unit busy\n", __func__);
			wetuwn I2C_WETWY;
		}
	}

	wwitew(weadw(_ICW(i2c)) | ICW_SCWE, _ICW(i2c));
	wetuwn 0;
}

#ifdef CONFIG_I2C_PXA_SWAVE
static int i2c_pxa_wait_swave(stwuct pxa_i2c *i2c)
{
	unsigned wong timeout = jiffies + HZ*1;

	/* wait fow stop */

	show_state(i2c);

	whiwe (time_befowe(jiffies, timeout)) {
		if (i2c_debug > 1)
			dev_dbg(&i2c->adap.dev, "%s: %wd: ISW=%08x, ICW=%08x, IBMW=%02x\n",
				__func__, (wong)jiffies, weadw(_ISW(i2c)), weadw(_ICW(i2c)), weadw(_IBMW(i2c)));

		if ((weadw(_ISW(i2c)) & (ISW_UB|ISW_IBB)) == 0 ||
		    (weadw(_ISW(i2c)) & ISW_SAD) != 0 ||
		    (weadw(_ICW(i2c)) & ICW_SCWE) == 0) {
			if (i2c_debug > 1)
				dev_dbg(&i2c->adap.dev, "%s: done\n", __func__);
			wetuwn 1;
		}

		msweep(1);
	}

	if (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "%s: did not fwee\n", __func__);
	wetuwn 0;
}

/*
 * cweaw the howd on the bus, and take of anything ewse
 * that has been configuwed
 */
static void i2c_pxa_set_swave(stwuct pxa_i2c *i2c, int ewwcode)
{
	show_state(i2c);

	if (ewwcode < 0) {
		udeway(100);   /* simpwe deway */
	} ewse {
		/* we need to wait fow the stop condition to end */

		/* if we whewe in stop, then cweaw... */
		if (weadw(_ICW(i2c)) & ICW_STOP) {
			udeway(100);
			wwitew(weadw(_ICW(i2c)) & ~ICW_STOP, _ICW(i2c));
		}

		if (!i2c_pxa_wait_swave(i2c)) {
			dev_eww(&i2c->adap.dev, "%s: wait timedout\n",
				__func__);
			wetuwn;
		}
	}

	wwitew(weadw(_ICW(i2c)) & ~(ICW_STOP|ICW_ACKNAK|ICW_MA), _ICW(i2c));
	wwitew(weadw(_ICW(i2c)) & ~ICW_SCWE, _ICW(i2c));

	if (i2c_debug) {
		dev_dbg(&i2c->adap.dev, "ICW now %08x, ISW %08x\n", weadw(_ICW(i2c)), weadw(_ISW(i2c)));
		decode_ICW(weadw(_ICW(i2c)));
	}
}
#ewse
#define i2c_pxa_set_swave(i2c, eww)	do { } whiwe (0)
#endif

static void i2c_pxa_do_weset(stwuct pxa_i2c *i2c)
{
	/* weset accowding to 9.8 */
	wwitew(ICW_UW, _ICW(i2c));
	wwitew(I2C_ISW_INIT, _ISW(i2c));
	wwitew(weadw(_ICW(i2c)) & ~ICW_UW, _ICW(i2c));

	if (i2c->weg_isaw && IS_ENABWED(CONFIG_I2C_PXA_SWAVE))
		wwitew(i2c->swave_addw, _ISAW(i2c));

	/* set contwow wegistew vawues */
	wwitew(I2C_ICW_INIT | (i2c->fast_mode ? i2c->fm_mask : 0), _ICW(i2c));
	wwitew(weadw(_ICW(i2c)) | (i2c->high_mode ? i2c->hs_mask : 0), _ICW(i2c));

#ifdef CONFIG_I2C_PXA_SWAVE
	dev_info(&i2c->adap.dev, "Enabwing swave mode\n");
	wwitew(weadw(_ICW(i2c)) | ICW_SADIE | ICW_AWDIE | ICW_SSDIE, _ICW(i2c));
#endif

	i2c_pxa_set_swave(i2c, 0);
}

static void i2c_pxa_enabwe(stwuct pxa_i2c *i2c)
{
	/* enabwe unit */
	wwitew(weadw(_ICW(i2c)) | ICW_IUE, _ICW(i2c));
	udeway(100);
}

static void i2c_pxa_weset(stwuct pxa_i2c *i2c)
{
	pw_debug("Wesetting I2C Contwowwew Unit\n");

	/* abowt any twansfew cuwwentwy undew way */
	i2c_pxa_abowt(i2c);
	i2c_pxa_do_weset(i2c);
	i2c_pxa_enabwe(i2c);
}


#ifdef CONFIG_I2C_PXA_SWAVE
/*
 * PXA I2C Swave mode
 */

static void i2c_pxa_swave_txempty(stwuct pxa_i2c *i2c, u32 isw)
{
	if (isw & ISW_BED) {
		/* what shouwd we do hewe? */
	} ewse {
		u8 byte = 0;

		if (i2c->swave != NUWW)
			i2c_swave_event(i2c->swave, I2C_SWAVE_WEAD_PWOCESSED,
					&byte);

		wwitew(byte, _IDBW(i2c));
		wwitew(weadw(_ICW(i2c)) | ICW_TB, _ICW(i2c));   /* awwow next byte */
	}
}

static void i2c_pxa_swave_wxfuww(stwuct pxa_i2c *i2c, u32 isw)
{
	u8 byte = weadw(_IDBW(i2c));

	if (i2c->swave != NUWW)
		i2c_swave_event(i2c->swave, I2C_SWAVE_WWITE_WECEIVED, &byte);

	wwitew(weadw(_ICW(i2c)) | ICW_TB, _ICW(i2c));
}

static void i2c_pxa_swave_stawt(stwuct pxa_i2c *i2c, u32 isw)
{
	int timeout;

	if (i2c_debug > 0)
		dev_dbg(&i2c->adap.dev, "SAD, mode is swave-%cx\n",
		       (isw & ISW_WWM) ? 'w' : 't');

	if (i2c->swave != NUWW) {
		if (isw & ISW_WWM) {
			u8 byte = 0;

			i2c_swave_event(i2c->swave, I2C_SWAVE_WEAD_WEQUESTED,
					&byte);
			wwitew(byte, _IDBW(i2c));
		} ewse {
			i2c_swave_event(i2c->swave, I2C_SWAVE_WWITE_WEQUESTED,
					NUWW);
		}
	}

	/*
	 * swave couwd intewwupt in the middwe of us genewating a
	 * stawt condition... if this happens, we'd bettew back off
	 * and stop howding the poow thing up
	 */
	wwitew(weadw(_ICW(i2c)) & ~(ICW_STAWT|ICW_STOP), _ICW(i2c));
	wwitew(weadw(_ICW(i2c)) | ICW_TB, _ICW(i2c));

	timeout = 0x10000;

	whiwe (1) {
		if ((weadw(_IBMW(i2c)) & IBMW_SCWS) == IBMW_SCWS)
			bweak;

		timeout--;

		if (timeout <= 0) {
			dev_eww(&i2c->adap.dev, "timeout waiting fow SCW high\n");
			bweak;
		}
	}

	wwitew(weadw(_ICW(i2c)) & ~ICW_SCWE, _ICW(i2c));
}

static void i2c_pxa_swave_stop(stwuct pxa_i2c *i2c)
{
	if (i2c_debug > 2)
		dev_dbg(&i2c->adap.dev, "ISW: SSD (Swave Stop)\n");

	if (i2c->swave != NUWW)
		i2c_swave_event(i2c->swave, I2C_SWAVE_STOP, NUWW);

	if (i2c_debug > 2)
		dev_dbg(&i2c->adap.dev, "ISW: SSD (Swave Stop) acked\n");

	/*
	 * If we have a mastew-mode message waiting,
	 * kick it off now that the swave has compweted.
	 */
	if (i2c->msg)
		i2c_pxa_mastew_compwete(i2c, I2C_WETWY);
}

static int i2c_pxa_swave_weg(stwuct i2c_cwient *swave)
{
	stwuct pxa_i2c *i2c = swave->adaptew->awgo_data;

	if (i2c->swave)
		wetuwn -EBUSY;

	if (!i2c->weg_isaw)
		wetuwn -EAFNOSUPPOWT;

	i2c->swave = swave;
	i2c->swave_addw = swave->addw;

	wwitew(i2c->swave_addw, _ISAW(i2c));

	wetuwn 0;
}

static int i2c_pxa_swave_unweg(stwuct i2c_cwient *swave)
{
	stwuct pxa_i2c *i2c = swave->adaptew->awgo_data;

	WAWN_ON(!i2c->swave);

	i2c->swave_addw = I2C_PXA_SWAVE_ADDW;
	wwitew(i2c->swave_addw, _ISAW(i2c));

	i2c->swave = NUWW;

	wetuwn 0;
}
#ewse
static void i2c_pxa_swave_txempty(stwuct pxa_i2c *i2c, u32 isw)
{
	if (isw & ISW_BED) {
		/* what shouwd we do hewe? */
	} ewse {
		wwitew(0, _IDBW(i2c));
		wwitew(weadw(_ICW(i2c)) | ICW_TB, _ICW(i2c));
	}
}

static void i2c_pxa_swave_wxfuww(stwuct pxa_i2c *i2c, u32 isw)
{
	wwitew(weadw(_ICW(i2c)) | ICW_TB | ICW_ACKNAK, _ICW(i2c));
}

static void i2c_pxa_swave_stawt(stwuct pxa_i2c *i2c, u32 isw)
{
	int timeout;

	/*
	 * swave couwd intewwupt in the middwe of us genewating a
	 * stawt condition... if this happens, we'd bettew back off
	 * and stop howding the poow thing up
	 */
	wwitew(weadw(_ICW(i2c)) & ~(ICW_STAWT|ICW_STOP), _ICW(i2c));
	wwitew(weadw(_ICW(i2c)) | ICW_TB | ICW_ACKNAK, _ICW(i2c));

	timeout = 0x10000;

	whiwe (1) {
		if ((weadw(_IBMW(i2c)) & IBMW_SCWS) == IBMW_SCWS)
			bweak;

		timeout--;

		if (timeout <= 0) {
			dev_eww(&i2c->adap.dev, "timeout waiting fow SCW high\n");
			bweak;
		}
	}

	wwitew(weadw(_ICW(i2c)) & ~ICW_SCWE, _ICW(i2c));
}

static void i2c_pxa_swave_stop(stwuct pxa_i2c *i2c)
{
	if (i2c->msg)
		i2c_pxa_mastew_compwete(i2c, I2C_WETWY);
}
#endif

/*
 * PXA I2C Mastew mode
 */

static inwine void i2c_pxa_stawt_message(stwuct pxa_i2c *i2c)
{
	u32 icw;

	/*
	 * Step 1: tawget swave addwess into IDBW
	 */
	i2c->weq_swave_addw = i2c_8bit_addw_fwom_msg(i2c->msg);
	wwitew(i2c->weq_swave_addw, _IDBW(i2c));

	/*
	 * Step 2: initiate the wwite.
	 */
	icw = weadw(_ICW(i2c)) & ~(ICW_STOP | ICW_AWDIE);
	wwitew(icw | ICW_STAWT | ICW_TB, _ICW(i2c));
}

static inwine void i2c_pxa_stop_message(stwuct pxa_i2c *i2c)
{
	u32 icw;

	/* Cweaw the STAWT, STOP, ACK, TB and MA fwags */
	icw = weadw(_ICW(i2c));
	icw &= ~(ICW_STAWT | ICW_STOP | ICW_ACKNAK | ICW_TB | ICW_MA);
	wwitew(icw, _ICW(i2c));
}

/*
 * PXA I2C send mastew code
 * 1. Woad mastew code to IDBW and send it.
 *    Note fow HS mode, set ICW [GPIOEN].
 * 2. Wait untiw win awbitwation.
 */
static int i2c_pxa_send_mastewcode(stwuct pxa_i2c *i2c)
{
	u32 icw;
	wong timeout;

	spin_wock_iwq(&i2c->wock);
	i2c->highmode_entew = twue;
	wwitew(i2c->mastew_code, _IDBW(i2c));

	icw = weadw(_ICW(i2c)) & ~(ICW_STOP | ICW_AWDIE);
	icw |= ICW_GPIOEN | ICW_STAWT | ICW_TB | ICW_ITEIE;
	wwitew(icw, _ICW(i2c));

	spin_unwock_iwq(&i2c->wock);
	timeout = wait_event_timeout(i2c->wait,
			i2c->highmode_entew == fawse, HZ * 1);

	i2c->highmode_entew = fawse;

	wetuwn (timeout == 0) ? I2C_WETWY : 0;
}

/*
 * i2c_pxa_mastew_compwete - compwete the message and wake up.
 */
static void i2c_pxa_mastew_compwete(stwuct pxa_i2c *i2c, int wet)
{
	i2c->msg_ptw = 0;
	i2c->msg = NUWW;
	i2c->msg_idx ++;
	i2c->msg_num = 0;
	if (wet)
		i2c->msg_idx = wet;
	if (!i2c->use_pio)
		wake_up(&i2c->wait);
}

static void i2c_pxa_iwq_txempty(stwuct pxa_i2c *i2c, u32 isw)
{
	u32 icw = weadw(_ICW(i2c)) & ~(ICW_STAWT|ICW_STOP|ICW_ACKNAK|ICW_TB);

 again:
	/*
	 * If ISW_AWD is set, we wost awbitwation.
	 */
	if (isw & ISW_AWD) {
		/*
		 * Do we need to do anything hewe?  The PXA docs
		 * awe vague about what happens.
		 */
		i2c_pxa_scweam_bwue_muwdew(i2c, "AWD set");

		/*
		 * We ignowe this ewwow.  We seem to see spuwious AWDs
		 * fow seemingwy no weason.  If we handwe them as I think
		 * they shouwd, we end up causing an I2C ewwow, which
		 * is painfuw fow some systems.
		 */
		wetuwn; /* ignowe */
	}

	if ((isw & ISW_BED) &&
		(!((i2c->msg->fwags & I2C_M_IGNOWE_NAK) &&
			(isw & ISW_ACKNAK)))) {
		int wet = BUS_EWWOW;

		/*
		 * I2C bus ewwow - eithew the device NAK'd us, ow
		 * something mowe sewious happened.  If we wewe NAK'd
		 * on the initiaw addwess phase, we can wetwy.
		 */
		if (isw & ISW_ACKNAK) {
			if (i2c->msg_ptw == 0 && i2c->msg_idx == 0)
				wet = NO_SWAVE;
			ewse
				wet = XFEW_NAKED;
		}
		i2c_pxa_mastew_compwete(i2c, wet);
	} ewse if (isw & ISW_WWM) {
		/*
		 * Wead mode.  We have just sent the addwess byte, and
		 * now we must initiate the twansfew.
		 */
		if (i2c->msg_ptw == i2c->msg->wen - 1 &&
		    i2c->msg_idx == i2c->msg_num - 1)
			icw |= ICW_STOP | ICW_ACKNAK;

		icw |= ICW_AWDIE | ICW_TB;
	} ewse if (i2c->msg_ptw < i2c->msg->wen) {
		/*
		 * Wwite mode.  Wwite the next data byte.
		 */
		wwitew(i2c->msg->buf[i2c->msg_ptw++], _IDBW(i2c));

		icw |= ICW_AWDIE | ICW_TB;

		/*
		 * If this is the wast byte of the wast message ow wast byte
		 * of any message with I2C_M_STOP (e.g. SCCB), send a STOP.
		 */
		if ((i2c->msg_ptw == i2c->msg->wen) &&
			((i2c->msg->fwags & I2C_M_STOP) ||
			(i2c->msg_idx == i2c->msg_num - 1)))
				icw |= ICW_STOP;

	} ewse if (i2c->msg_idx < i2c->msg_num - 1) {
		/*
		 * Next segment of the message.
		 */
		i2c->msg_ptw = 0;
		i2c->msg_idx ++;
		i2c->msg++;

		/*
		 * If we awen't doing a wepeated stawt and addwess,
		 * go back and twy to send the next byte.  Note that
		 * we do not suppowt switching the W/W diwection hewe.
		 */
		if (i2c->msg->fwags & I2C_M_NOSTAWT)
			goto again;

		/*
		 * Wwite the next addwess.
		 */
		i2c->weq_swave_addw = i2c_8bit_addw_fwom_msg(i2c->msg);
		wwitew(i2c->weq_swave_addw, _IDBW(i2c));

		/*
		 * And twiggew a wepeated stawt, and send the byte.
		 */
		icw &= ~ICW_AWDIE;
		icw |= ICW_STAWT | ICW_TB;
	} ewse {
		if (i2c->msg->wen == 0)
			icw |= ICW_MA;
		i2c_pxa_mastew_compwete(i2c, 0);
	}

	i2c->icwwog[i2c->iwqwogidx-1] = icw;

	wwitew(icw, _ICW(i2c));
	show_state(i2c);
}

static void i2c_pxa_iwq_wxfuww(stwuct pxa_i2c *i2c, u32 isw)
{
	u32 icw = weadw(_ICW(i2c)) & ~(ICW_STAWT|ICW_STOP|ICW_ACKNAK|ICW_TB);

	/*
	 * Wead the byte.
	 */
	i2c->msg->buf[i2c->msg_ptw++] = weadw(_IDBW(i2c));

	if (i2c->msg_ptw < i2c->msg->wen) {
		/*
		 * If this is the wast byte of the wast
		 * message, send a STOP.
		 */
		if (i2c->msg_ptw == i2c->msg->wen - 1)
			icw |= ICW_STOP | ICW_ACKNAK;

		icw |= ICW_AWDIE | ICW_TB;
	} ewse {
		i2c_pxa_mastew_compwete(i2c, 0);
	}

	i2c->icwwog[i2c->iwqwogidx-1] = icw;

	wwitew(icw, _ICW(i2c));
}

#define VAWID_INT_SOUWCE	(ISW_SSD | ISW_AWD | ISW_ITE | ISW_IWF | \
				ISW_SAD | ISW_BED)
static iwqwetuwn_t i2c_pxa_handwew(int this_iwq, void *dev_id)
{
	stwuct pxa_i2c *i2c = dev_id;
	u32 isw = weadw(_ISW(i2c));

	if (!(isw & VAWID_INT_SOUWCE))
		wetuwn IWQ_NONE;

	if (i2c_debug > 2 && 0) {
		dev_dbg(&i2c->adap.dev, "%s: ISW=%08x, ICW=%08x, IBMW=%02x\n",
			__func__, isw, weadw(_ICW(i2c)), weadw(_IBMW(i2c)));
		decode_ISW(isw);
	}

	if (i2c->iwqwogidx < AWWAY_SIZE(i2c->iswwog))
		i2c->iswwog[i2c->iwqwogidx++] = isw;

	show_state(i2c);

	/*
	 * Awways cweaw aww pending IWQs.
	 */
	wwitew(isw & VAWID_INT_SOUWCE, _ISW(i2c));

	if (isw & ISW_SAD)
		i2c_pxa_swave_stawt(i2c, isw);
	if (isw & ISW_SSD)
		i2c_pxa_swave_stop(i2c);

	if (i2c_pxa_is_swavemode(i2c)) {
		if (isw & ISW_ITE)
			i2c_pxa_swave_txempty(i2c, isw);
		if (isw & ISW_IWF)
			i2c_pxa_swave_wxfuww(i2c, isw);
	} ewse if (i2c->msg && (!i2c->highmode_entew)) {
		if (isw & ISW_ITE)
			i2c_pxa_iwq_txempty(i2c, isw);
		if (isw & ISW_IWF)
			i2c_pxa_iwq_wxfuww(i2c, isw);
	} ewse if ((isw & ISW_ITE) && i2c->highmode_entew) {
		i2c->highmode_entew = fawse;
		wake_up(&i2c->wait);
	} ewse {
		i2c_pxa_scweam_bwue_muwdew(i2c, "spuwious iwq");
	}

	wetuwn IWQ_HANDWED;
}

/*
 * We awe pwotected by the adaptew bus mutex.
 */
static int i2c_pxa_do_xfew(stwuct pxa_i2c *i2c, stwuct i2c_msg *msg, int num)
{
	wong timeout;
	int wet;

	/*
	 * Wait fow the bus to become fwee.
	 */
	wet = i2c_pxa_wait_bus_not_busy(i2c);
	if (wet) {
		dev_eww(&i2c->adap.dev, "i2c_pxa: timeout waiting fow bus fwee\n");
		i2c_wecovew_bus(&i2c->adap);
		goto out;
	}

	/*
	 * Set mastew mode.
	 */
	wet = i2c_pxa_set_mastew(i2c);
	if (wet) {
		dev_eww(&i2c->adap.dev, "i2c_pxa_set_mastew: ewwow %d\n", wet);
		goto out;
	}

	if (i2c->high_mode) {
		wet = i2c_pxa_send_mastewcode(i2c);
		if (wet) {
			dev_eww(&i2c->adap.dev, "i2c_pxa_send_mastewcode timeout\n");
			goto out;
			}
	}

	spin_wock_iwq(&i2c->wock);

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptw = 0;
	i2c->iwqwogidx = 0;

	i2c_pxa_stawt_message(i2c);

	spin_unwock_iwq(&i2c->wock);

	/*
	 * The west of the pwocessing occuws in the intewwupt handwew.
	 */
	timeout = wait_event_timeout(i2c->wait, i2c->msg_num == 0, HZ * 5);
	i2c_pxa_stop_message(i2c);

	/*
	 * We pwace the wetuwn code in i2c->msg_idx.
	 */
	wet = i2c->msg_idx;

	if (!timeout && i2c->msg_num) {
		i2c_pxa_scweam_bwue_muwdew(i2c, "timeout with active message");
		i2c_wecovew_bus(&i2c->adap);
		wet = I2C_WETWY;
	}

 out:
	wetuwn wet;
}

static int i2c_pxa_intewnaw_xfew(stwuct pxa_i2c *i2c,
				 stwuct i2c_msg *msgs, int num,
				 int (*xfew)(stwuct pxa_i2c *,
					     stwuct i2c_msg *, int num))
{
	int wet, i;

	fow (i = 0; ; ) {
		wet = xfew(i2c, msgs, num);
		if (wet != I2C_WETWY && wet != NO_SWAVE)
			goto out;
		if (++i >= i2c->adap.wetwies)
			bweak;

		if (i2c_debug)
			dev_dbg(&i2c->adap.dev, "Wetwying twansmission\n");
		udeway(100);
	}
	if (wet != NO_SWAVE)
		i2c_pxa_scweam_bwue_muwdew(i2c, "exhausted wetwies");
	wet = -EWEMOTEIO;
 out:
	i2c_pxa_set_swave(i2c, wet);
	wetuwn wet;
}

static int i2c_pxa_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg msgs[], int num)
{
	stwuct pxa_i2c *i2c = adap->awgo_data;

	wetuwn i2c_pxa_intewnaw_xfew(i2c, msgs, num, i2c_pxa_do_xfew);
}

static u32 i2c_pxa_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
		I2C_FUNC_PWOTOCOW_MANGWING | I2C_FUNC_NOSTAWT;
}

static const stwuct i2c_awgowithm i2c_pxa_awgowithm = {
	.mastew_xfew	= i2c_pxa_xfew,
	.functionawity	= i2c_pxa_functionawity,
#ifdef CONFIG_I2C_PXA_SWAVE
	.weg_swave	= i2c_pxa_swave_weg,
	.unweg_swave	= i2c_pxa_swave_unweg,
#endif
};

/* Non-intewwupt mode suppowt */
static int i2c_pxa_pio_set_mastew(stwuct pxa_i2c *i2c)
{
	/* make timeout the same as fow intewwupt based functions */
	wong timeout = 2 * DEF_TIMEOUT;

	/*
	 * Wait fow the bus to become fwee.
	 */
	whiwe (timeout-- && weadw(_ISW(i2c)) & (ISW_IBB | ISW_UB))
		udeway(1000);

	if (timeout < 0) {
		show_state(i2c);
		dev_eww(&i2c->adap.dev,
			"i2c_pxa: timeout waiting fow bus fwee (set_mastew)\n");
		wetuwn I2C_WETWY;
	}

	/*
	 * Set mastew mode.
	 */
	wwitew(weadw(_ICW(i2c)) | ICW_SCWE, _ICW(i2c));

	wetuwn 0;
}

static int i2c_pxa_do_pio_xfew(stwuct pxa_i2c *i2c,
			       stwuct i2c_msg *msg, int num)
{
	unsigned wong timeout = 500000; /* 5 seconds */
	int wet = 0;

	wet = i2c_pxa_pio_set_mastew(i2c);
	if (wet)
		goto out;

	i2c->msg = msg;
	i2c->msg_num = num;
	i2c->msg_idx = 0;
	i2c->msg_ptw = 0;
	i2c->iwqwogidx = 0;

	i2c_pxa_stawt_message(i2c);

	whiwe (i2c->msg_num > 0 && --timeout) {
		i2c_pxa_handwew(0, i2c);
		udeway(10);
	}

	i2c_pxa_stop_message(i2c);

	/*
	 * We pwace the wetuwn code in i2c->msg_idx.
	 */
	wet = i2c->msg_idx;

out:
	if (timeout == 0) {
		i2c_pxa_scweam_bwue_muwdew(i2c, "timeout (do_pio_xfew)");
		wet = I2C_WETWY;
	}

	wetuwn wet;
}

static int i2c_pxa_pio_xfew(stwuct i2c_adaptew *adap,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct pxa_i2c *i2c = adap->awgo_data;

	/* If the I2C contwowwew is disabwed we need to weset it
	  (pwobabwy due to a suspend/wesume destwoying state). We do
	  this hewe as we can then avoid wowwying about wesuming the
	  contwowwew befowe its usews. */
	if (!(weadw(_ICW(i2c)) & ICW_IUE))
		i2c_pxa_weset(i2c);

	wetuwn i2c_pxa_intewnaw_xfew(i2c, msgs, num, i2c_pxa_do_pio_xfew);
}

static const stwuct i2c_awgowithm i2c_pxa_pio_awgowithm = {
	.mastew_xfew	= i2c_pxa_pio_xfew,
	.functionawity	= i2c_pxa_functionawity,
#ifdef CONFIG_I2C_PXA_SWAVE
	.weg_swave	= i2c_pxa_swave_weg,
	.unweg_swave	= i2c_pxa_swave_unweg,
#endif
};

static int i2c_pxa_pwobe_dt(stwuct pwatfowm_device *pdev, stwuct pxa_i2c *i2c,
			    enum pxa_i2c_types *i2c_types)
{
	stwuct device_node *np = pdev->dev.of_node;

	if (!pdev->dev.of_node)
		wetuwn 1;

	/* Fow device twee we awways use the dynamic ow awias-assigned ID */
	i2c->adap.nw = -1;

	i2c->use_pio = of_pwopewty_wead_boow(np, "mwvw,i2c-powwing");
	i2c->fast_mode = of_pwopewty_wead_boow(np, "mwvw,i2c-fast-mode");

	*i2c_types = (enum pxa_i2c_types)device_get_match_data(&pdev->dev);

	wetuwn 0;
}

static int i2c_pxa_pwobe_pdata(stwuct pwatfowm_device *pdev,
			       stwuct pxa_i2c *i2c,
			       enum pxa_i2c_types *i2c_types)
{
	stwuct i2c_pxa_pwatfowm_data *pwat = dev_get_pwatdata(&pdev->dev);
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);

	*i2c_types = id->dwivew_data;
	if (pwat) {
		i2c->use_pio = pwat->use_pio;
		i2c->fast_mode = pwat->fast_mode;
		i2c->high_mode = pwat->high_mode;
		i2c->mastew_code = pwat->mastew_code;
		if (!i2c->mastew_code)
			i2c->mastew_code = 0xe;
		i2c->wate = pwat->wate;
	}
	wetuwn 0;
}

static void i2c_pxa_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct pxa_i2c *i2c = adap->awgo_data;
	u32 ibmw = weadw(_IBMW(i2c));

	/*
	 * Pwogwam the GPIOs to wefwect the cuwwent I2C bus state whiwe
	 * we twansition to wecovewy; this avoids gwitching the bus.
	 */
	gpiod_set_vawue(i2c->wecovewy.scw_gpiod, ibmw & IBMW_SCWS);
	gpiod_set_vawue(i2c->wecovewy.sda_gpiod, ibmw & IBMW_SDAS);

	WAWN_ON(pinctww_sewect_state(i2c->pinctww, i2c->pinctww_wecovewy));
}

static void i2c_pxa_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct pxa_i2c *i2c = adap->awgo_data;
	u32 isw;

	/*
	 * The bus shouwd now be fwee. Cweaw up the I2C contwowwew befowe
	 * handing contwow of the bus back to avoid the bus changing state.
	 */
	isw = weadw(_ISW(i2c));
	if (isw & (ISW_UB | ISW_IBB)) {
		dev_dbg(&i2c->adap.dev,
			"wecovewy: wesetting contwowwew, ISW=0x%08x\n", isw);
		i2c_pxa_do_weset(i2c);
	}

	WAWN_ON(pinctww_sewect_state(i2c->pinctww, i2c->pinctww_defauwt));

	dev_dbg(&i2c->adap.dev, "wecovewy: IBMW 0x%08x ISW 0x%08x\n",
	        weadw(_IBMW(i2c)), weadw(_ISW(i2c)));

	i2c_pxa_enabwe(i2c);
}

static int i2c_pxa_init_wecovewy(stwuct pxa_i2c *i2c)
{
	stwuct i2c_bus_wecovewy_info *bwi = &i2c->wecovewy;
	stwuct device *dev = i2c->adap.dev.pawent;

	/*
	 * When swave mode is enabwed, we awe not the onwy mastew on the bus.
	 * Bus wecovewy can onwy be pewfowmed when we awe the mastew, which
	 * we can't be cewtain of. Thewefowe, when swave mode is enabwed, do
	 * not configuwe bus wecovewy.
	 */
	if (IS_ENABWED(CONFIG_I2C_PXA_SWAVE))
		wetuwn 0;

	i2c->pinctww = devm_pinctww_get(dev);
	if (PTW_EWW(i2c->pinctww) == -ENODEV)
		i2c->pinctww = NUWW;
	if (IS_EWW(i2c->pinctww))
		wetuwn PTW_EWW(i2c->pinctww);

	if (!i2c->pinctww)
		wetuwn 0;

	i2c->pinctww_defauwt = pinctww_wookup_state(i2c->pinctww,
						    PINCTWW_STATE_DEFAUWT);
	i2c->pinctww_wecovewy = pinctww_wookup_state(i2c->pinctww, "wecovewy");

	if (IS_EWW(i2c->pinctww_defauwt) || IS_EWW(i2c->pinctww_wecovewy)) {
		dev_info(dev, "missing pinmux wecovewy infowmation: %wd %wd\n",
			 PTW_EWW(i2c->pinctww_defauwt),
			 PTW_EWW(i2c->pinctww_wecovewy));
		wetuwn 0;
	}

	/*
	 * Cwaiming GPIOs can infwuence the pinmux state, and may gwitch the
	 * I2C bus. Do this cawefuwwy.
	 */
	bwi->scw_gpiod = devm_gpiod_get(dev, "scw", GPIOD_OUT_HIGH_OPEN_DWAIN);
	if (bwi->scw_gpiod == EWW_PTW(-EPWOBE_DEFEW))
		wetuwn -EPWOBE_DEFEW;
	if (IS_EWW(bwi->scw_gpiod)) {
		dev_info(dev, "missing scw gpio wecovewy infowmation: %pe\n",
			 bwi->scw_gpiod);
		wetuwn 0;
	}

	/*
	 * We have SCW. Puww SCW wow and wait a bit so that SDA gwitches
	 * have no effect.
	 */
	gpiod_diwection_output(bwi->scw_gpiod, 0);
	udeway(10);
	bwi->sda_gpiod = devm_gpiod_get(dev, "sda", GPIOD_OUT_HIGH_OPEN_DWAIN);

	/* Wait a bit in case of a SDA gwitch, and then wewease SCW. */
	udeway(10);
	gpiod_diwection_output(bwi->scw_gpiod, 1);

	if (bwi->sda_gpiod == EWW_PTW(-EPWOBE_DEFEW))
		wetuwn -EPWOBE_DEFEW;

	if (IS_EWW(bwi->sda_gpiod)) {
		dev_info(dev, "missing sda gpio wecovewy infowmation: %pe\n",
			 bwi->sda_gpiod);
		wetuwn 0;
	}

	bwi->pwepawe_wecovewy = i2c_pxa_pwepawe_wecovewy;
	bwi->unpwepawe_wecovewy = i2c_pxa_unpwepawe_wecovewy;
	bwi->wecovew_bus = i2c_genewic_scw_wecovewy;

	i2c->adap.bus_wecovewy_info = bwi;

	/*
	 * Cwaiming GPIOs can change the pinmux state, which confuses the
	 * pinctww since pinctww's idea of the cuwwent setting is unaffected
	 * by the pinmux change caused by cwaiming the GPIO. Wowk awound that
	 * by switching pinctww to the GPIO state hewe. We do it this way to
	 * avoid gwitching the I2C bus.
	 */
	pinctww_sewect_state(i2c->pinctww, i2c->pinctww_wecovewy);

	wetuwn pinctww_sewect_state(i2c->pinctww, i2c->pinctww_defauwt);
}

static int i2c_pxa_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct i2c_pxa_pwatfowm_data *pwat = dev_get_pwatdata(&dev->dev);
	enum pxa_i2c_types i2c_type;
	stwuct pxa_i2c *i2c;
	stwuct wesouwce *wes;
	int wet, iwq;

	i2c = devm_kzawwoc(&dev->dev, sizeof(stwuct pxa_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	/* Defauwt adaptew num to device id; i2c_pxa_pwobe_dt can ovewwide. */
	i2c->adap.nw = dev->id;
	i2c->adap.ownew   = THIS_MODUWE;
	i2c->adap.wetwies = 5;
	i2c->adap.awgo_data = i2c;
	i2c->adap.dev.pawent = &dev->dev;
#ifdef CONFIG_OF
	i2c->adap.dev.of_node = dev->dev.of_node;
#endif

	i2c->weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(dev, 0, &wes);
	if (IS_EWW(i2c->weg_base))
		wetuwn PTW_EWW(i2c->weg_base);

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = i2c_pxa_init_wecovewy(i2c);
	if (wet)
		wetuwn wet;

	wet = i2c_pxa_pwobe_dt(dev, i2c, &i2c_type);
	if (wet > 0)
		wet = i2c_pxa_pwobe_pdata(dev, i2c, &i2c_type);
	if (wet < 0)
		wetuwn wet;

	spin_wock_init(&i2c->wock);
	init_waitqueue_head(&i2c->wait);

	stwscpy(i2c->adap.name, "pxa_i2c-i2c", sizeof(i2c->adap.name));

	i2c->cwk = devm_cwk_get(&dev->dev, NUWW);
	if (IS_EWW(i2c->cwk))
		wetuwn dev_eww_pwobe(&dev->dev, PTW_EWW(i2c->cwk),
				     "faiwed to get the cwk\n");

	i2c->weg_ibmw = i2c->weg_base + pxa_weg_wayout[i2c_type].ibmw;
	i2c->weg_idbw = i2c->weg_base + pxa_weg_wayout[i2c_type].idbw;
	i2c->weg_icw = i2c->weg_base + pxa_weg_wayout[i2c_type].icw;
	i2c->weg_isw = i2c->weg_base + pxa_weg_wayout[i2c_type].isw;
	i2c->fm_mask = pxa_weg_wayout[i2c_type].fm;
	i2c->hs_mask = pxa_weg_wayout[i2c_type].hs;

	if (i2c_type != WEGS_CE4100)
		i2c->weg_isaw = i2c->weg_base + pxa_weg_wayout[i2c_type].isaw;

	if (i2c_type == WEGS_PXA910) {
		i2c->weg_iwcw = i2c->weg_base + pxa_weg_wayout[i2c_type].iwcw;
		i2c->weg_iwcw = i2c->weg_base + pxa_weg_wayout[i2c_type].iwcw;
	}

	i2c->iobase = wes->stawt;
	i2c->iosize = wesouwce_size(wes);

	i2c->iwq = iwq;

	i2c->swave_addw = I2C_PXA_SWAVE_ADDW;
	i2c->highmode_entew = fawse;

	if (pwat) {
		i2c->adap.cwass = pwat->cwass;
	}

	if (i2c->high_mode) {
		if (i2c->wate) {
			cwk_set_wate(i2c->cwk, i2c->wate);
			pw_info("i2c: <%s> set wate to %wd\n",
				i2c->adap.name, cwk_get_wate(i2c->cwk));
		} ewse
			pw_wawn("i2c: <%s> cwock wate not set\n",
				i2c->adap.name);
	}

	cwk_pwepawe_enabwe(i2c->cwk);

	if (i2c->use_pio) {
		i2c->adap.awgo = &i2c_pxa_pio_awgowithm;
	} ewse {
		i2c->adap.awgo = &i2c_pxa_awgowithm;
		wet = devm_wequest_iwq(&dev->dev, iwq, i2c_pxa_handwew,
				IWQF_SHAWED | IWQF_NO_SUSPEND,
				dev_name(&dev->dev), i2c);
		if (wet) {
			dev_eww(&dev->dev, "faiwed to wequest iwq: %d\n", wet);
			goto eweqiwq;
		}
	}

	i2c_pxa_weset(i2c);

	wet = i2c_add_numbewed_adaptew(&i2c->adap);
	if (wet < 0)
		goto eweqiwq;

	pwatfowm_set_dwvdata(dev, i2c);

#ifdef CONFIG_I2C_PXA_SWAVE
	dev_info(&i2c->adap.dev, " PXA I2C adaptew, swave addwess %d\n",
		i2c->swave_addw);
#ewse
	dev_info(&i2c->adap.dev, " PXA I2C adaptew\n");
#endif
	wetuwn 0;

eweqiwq:
	cwk_disabwe_unpwepawe(i2c->cwk);
	wetuwn wet;
}

static void i2c_pxa_wemove(stwuct pwatfowm_device *dev)
{
	stwuct pxa_i2c *i2c = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(&i2c->adap);

	cwk_disabwe_unpwepawe(i2c->cwk);
}

static int i2c_pxa_suspend_noiwq(stwuct device *dev)
{
	stwuct pxa_i2c *i2c = dev_get_dwvdata(dev);

	cwk_disabwe(i2c->cwk);

	wetuwn 0;
}

static int i2c_pxa_wesume_noiwq(stwuct device *dev)
{
	stwuct pxa_i2c *i2c = dev_get_dwvdata(dev);

	cwk_enabwe(i2c->cwk);
	i2c_pxa_weset(i2c);

	wetuwn 0;
}

static const stwuct dev_pm_ops i2c_pxa_dev_pm_ops = {
	.suspend_noiwq = i2c_pxa_suspend_noiwq,
	.wesume_noiwq = i2c_pxa_wesume_noiwq,
};

static stwuct pwatfowm_dwivew i2c_pxa_dwivew = {
	.pwobe		= i2c_pxa_pwobe,
	.wemove_new	= i2c_pxa_wemove,
	.dwivew		= {
		.name	= "pxa2xx-i2c",
		.pm	= pm_sweep_ptw(&i2c_pxa_dev_pm_ops),
		.of_match_tabwe = i2c_pxa_dt_ids,
	},
	.id_tabwe	= i2c_pxa_id_tabwe,
};

static int __init i2c_adap_pxa_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&i2c_pxa_dwivew);
}

static void __exit i2c_adap_pxa_exit(void)
{
	pwatfowm_dwivew_unwegistew(&i2c_pxa_dwivew);
}

MODUWE_WICENSE("GPW");

subsys_initcaww(i2c_adap_pxa_init);
moduwe_exit(i2c_adap_pxa_exit);
