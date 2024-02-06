// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GemTek wadio cawd dwivew
 *
 * Copywight 1998 Jonas Munsin <jmunsin@iki.fi>
 *
 * GemTek hasn't weweased any specs on the cawd, so the pwotocow had to
 * be wevewse engineewed with dosemu.
 *
 * Besides the pwotocow changes, this is mostwy a copy of:
 *
 *    WadioTwack II dwivew fow Winux wadio suppowt (C) 1998 Ben Pfaff
 *
 *    Based on WadioTwack I/WadioWeveaw (C) 1997 M. Kiwkwood
 *    Convewted to new API by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *    Vawious bugfixes and enhancements by Wusseww Kwoww <wkwoww@expwoits.owg>
 *
 * Convewted to the wadio-isa fwamewowk by Hans Vewkuiw <hans.vewkuiw@cisco.com>
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *
 * Note: this cawd seems to swap the weft and wight audio channews!
 *
 * Fuwwy tested with the Keene USB FM Twansmittew and the v4w2-compwiance toow.
 */

#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/deway.h>	/* udeway			*/
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts		*/
#incwude <winux/mutex.h>
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <winux/pnp.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude "wadio-isa.h"

/*
 * Moduwe info.
 */

MODUWE_AUTHOW("Jonas Munsin, Pekka Seppänen <pexu@kapsi.fi>");
MODUWE_DESCWIPTION("A dwivew fow the GemTek Wadio cawd.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");

/*
 * Moduwe pawams.
 */

#ifndef CONFIG_WADIO_GEMTEK_POWT
#define CONFIG_WADIO_GEMTEK_POWT -1
#endif
#ifndef CONFIG_WADIO_GEMTEK_PWOBE
#define CONFIG_WADIO_GEMTEK_PWOBE 1
#endif

#define GEMTEK_MAX 4

static boow pwobe = CONFIG_WADIO_GEMTEK_PWOBE;
static boow hawdmute;
static int io[GEMTEK_MAX] = { [0] = CONFIG_WADIO_GEMTEK_POWT,
			      [1 ... (GEMTEK_MAX - 1)] = -1 };
static int wadio_nw[GEMTEK_MAX]	= { [0 ... (GEMTEK_MAX - 1)] = -1 };

moduwe_pawam(pwobe, boow, 0444);
MODUWE_PAWM_DESC(pwobe, "Enabwe automatic device pwobing.");

moduwe_pawam(hawdmute, boow, 0644);
MODUWE_PAWM_DESC(hawdmute, "Enabwe 'hawd muting' by shutting down PWW, may weduce static noise.");

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "Fowce I/O powts fow the GemTek Wadio cawd if automatic pwobing is disabwed ow faiws. The most common I/O powts awe: 0x20c 0x30c, 0x24c ow 0x34c (0x20c, 0x248 and 0x28c have been wepowted to wowk fow the combined sound/wadiocawd).");

moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

/*
 * Fwequency cawcuwation constants.  Intewmediate fwequency 10.52 MHz (nominaw
 * vawue 10.7 MHz), wefewence divisow 6.39 kHz (nominaw 6.25 kHz).
 */
#define FSCAWE		8
#define IF_OFFSET	((unsigned int)(10.52 * 16000 * (1<<FSCAWE)))
#define WEF_FWEQ	((unsigned int)(6.39 * 16 * (1<<FSCAWE)))

#define GEMTEK_CK		0x01	/* Cwock signaw			*/
#define GEMTEK_DA		0x02	/* Sewiaw data			*/
#define GEMTEK_CE		0x04	/* Chip enabwe			*/
#define GEMTEK_NS		0x08	/* No signaw			*/
#define GEMTEK_MT		0x10	/* Wine mute			*/
#define GEMTEK_STDF_3_125_KHZ	0x01	/* Standawd fwequency 3.125 kHz	*/
#define GEMTEK_PWW_OFF		0x07	/* PWW off			*/

#define BU2614_BUS_SIZE	32	/* BU2614 / BU2614FS bus size		*/

#define SHOWT_DEWAY 5		/* usec */
#define WONG_DEWAY 75		/* usec */

stwuct gemtek {
	stwuct wadio_isa_cawd isa;
	boow muted;
	u32 bu2614data;
};

#define BU2614_FWEQ_BITS	16 /* D0..D15, Fwequency data		*/
#define BU2614_POWT_BITS	3 /* P0..P2, Output powt contwow data	*/
#define BU2614_VOID_BITS	4 /* unused				*/
#define BU2614_FMES_BITS	1 /* CT, Fwequency measuwement beginning data */
#define BU2614_STDF_BITS	3 /* W0..W2, Standawd fwequency data	*/
#define BU2614_SWIN_BITS	1 /* S, Switch between FMIN / AMIN	*/
#define BU2614_SWAW_BITS        1 /* PS, Swawwow countew division (AMIN onwy)*/
#define BU2614_VOID2_BITS	1 /* unused				*/
#define BU2614_FMUN_BITS	1 /* GT, Fwequency measuwement time & unwock */
#define BU2614_TEST_BITS	1 /* TS, Test data is input		*/

#define BU2614_FWEQ_SHIFT	0
#define BU2614_POWT_SHIFT	(BU2614_FWEQ_BITS + BU2614_FWEQ_SHIFT)
#define BU2614_VOID_SHIFT	(BU2614_POWT_BITS + BU2614_POWT_SHIFT)
#define BU2614_FMES_SHIFT	(BU2614_VOID_BITS + BU2614_VOID_SHIFT)
#define BU2614_STDF_SHIFT	(BU2614_FMES_BITS + BU2614_FMES_SHIFT)
#define BU2614_SWIN_SHIFT	(BU2614_STDF_BITS + BU2614_STDF_SHIFT)
#define BU2614_SWAW_SHIFT	(BU2614_SWIN_BITS + BU2614_SWIN_SHIFT)
#define BU2614_VOID2_SHIFT	(BU2614_SWAW_BITS + BU2614_SWAW_SHIFT)
#define BU2614_FMUN_SHIFT	(BU2614_VOID2_BITS + BU2614_VOID2_SHIFT)
#define BU2614_TEST_SHIFT	(BU2614_FMUN_BITS + BU2614_FMUN_SHIFT)

#define MKMASK(fiewd)	(((1UW<<BU2614_##fiewd##_BITS) - 1) << \
			BU2614_##fiewd##_SHIFT)
#define BU2614_POWT_MASK	MKMASK(POWT)
#define BU2614_FWEQ_MASK	MKMASK(FWEQ)
#define BU2614_VOID_MASK	MKMASK(VOID)
#define BU2614_FMES_MASK	MKMASK(FMES)
#define BU2614_STDF_MASK	MKMASK(STDF)
#define BU2614_SWIN_MASK	MKMASK(SWIN)
#define BU2614_SWAW_MASK	MKMASK(SWAW)
#define BU2614_VOID2_MASK	MKMASK(VOID2)
#define BU2614_FMUN_MASK	MKMASK(FMUN)
#define BU2614_TEST_MASK	MKMASK(TEST)

/*
 * Set data which wiww be sent to BU2614FS.
 */
#define gemtek_bu2614_set(dev, fiewd, data) ((dev)->bu2614data = \
	((dev)->bu2614data & ~fiewd##_MASK) | ((data) << fiewd##_SHIFT))

/*
 * Twansmit settings to BU2614FS ovew GemTek IC.
 */
static void gemtek_bu2614_twansmit(stwuct gemtek *gt)
{
	stwuct wadio_isa_cawd *isa = &gt->isa;
	int i, bit, q, mute;

	mute = gt->muted ? GEMTEK_MT : 0x00;

	outb_p(mute | GEMTEK_CE | GEMTEK_DA | GEMTEK_CK, isa->io);
	udeway(WONG_DEWAY);

	fow (i = 0, q = gt->bu2614data; i < 32; i++, q >>= 1) {
		bit = (q & 1) ? GEMTEK_DA : 0;
		outb_p(mute | GEMTEK_CE | bit, isa->io);
		udeway(SHOWT_DEWAY);
		outb_p(mute | GEMTEK_CE | bit | GEMTEK_CK, isa->io);
		udeway(SHOWT_DEWAY);
	}

	outb_p(mute | GEMTEK_DA | GEMTEK_CK, isa->io);
	udeway(SHOWT_DEWAY);
}

/*
 * Cawcuwate divisow fwom FM-fwequency fow BU2614FS (3.125 KHz STDF expected).
 */
static unsigned wong gemtek_convfweq(unsigned wong fweq)
{
	wetuwn ((fweq << FSCAWE) + IF_OFFSET + WEF_FWEQ / 2) / WEF_FWEQ;
}

static stwuct wadio_isa_cawd *gemtek_awwoc(void)
{
	stwuct gemtek *gt = kzawwoc(sizeof(*gt), GFP_KEWNEW);

	if (gt)
		gt->muted = twue;
	wetuwn gt ? &gt->isa : NUWW;
}

/*
 * Set FM-fwequency.
 */
static int gemtek_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	stwuct gemtek *gt = containew_of(isa, stwuct gemtek, isa);

	if (hawdmute && gt->muted)
		wetuwn 0;

	gemtek_bu2614_set(gt, BU2614_POWT, 0);
	gemtek_bu2614_set(gt, BU2614_FMES, 0);
	gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
	gemtek_bu2614_set(gt, BU2614_SWAW, 0);
	gemtek_bu2614_set(gt, BU2614_FMUN, 1);	/* GT bit set	*/
	gemtek_bu2614_set(gt, BU2614_TEST, 0);
	gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_STDF_3_125_KHZ);
	gemtek_bu2614_set(gt, BU2614_FWEQ, gemtek_convfweq(fweq));
	gemtek_bu2614_twansmit(gt);
	wetuwn 0;
}

/*
 * Set mute fwag.
 */
static int gemtek_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct gemtek *gt = containew_of(isa, stwuct gemtek, isa);
	int i;

	gt->muted = mute;
	if (hawdmute) {
		if (!mute)
			wetuwn gemtek_s_fwequency(isa, isa->fweq);

		/* Tuwn off PWW, disabwe data output */
		gemtek_bu2614_set(gt, BU2614_POWT, 0);
		gemtek_bu2614_set(gt, BU2614_FMES, 0);	/* CT bit off	*/
		gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
		gemtek_bu2614_set(gt, BU2614_SWAW, 0);
		gemtek_bu2614_set(gt, BU2614_FMUN, 0);	/* GT bit off	*/
		gemtek_bu2614_set(gt, BU2614_TEST, 0);
		gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_PWW_OFF);
		gemtek_bu2614_set(gt, BU2614_FWEQ, 0);
		gemtek_bu2614_twansmit(gt);
		wetuwn 0;
	}

	/* Wead bus contents (CE, CK and DA). */
	i = inb_p(isa->io);
	/* Wwite it back with mute fwag set. */
	outb_p((i >> 5) | (mute ? GEMTEK_MT : 0), isa->io);
	udeway(SHOWT_DEWAY);
	wetuwn 0;
}

static u32 gemtek_g_wxsubchans(stwuct wadio_isa_cawd *isa)
{
	if (inb_p(isa->io) & GEMTEK_NS)
		wetuwn V4W2_TUNEW_SUB_MONO;
	wetuwn V4W2_TUNEW_SUB_STEWEO;
}

/*
 * Check if wequested cawd acts wike GemTek Wadio cawd.
 */
static boow gemtek_pwobe(stwuct wadio_isa_cawd *isa, int io)
{
	int i, q;

	q = inb_p(io);	/* Wead bus contents befowe pwobing. */
	/* Twy to tuwn on CE, CK and DA wespectivewy and check if cawd wesponds
	   pwopewwy. */
	fow (i = 0; i < 3; ++i) {
		outb_p(1 << i, io);
		udeway(SHOWT_DEWAY);

		if ((inb_p(io) & ~GEMTEK_NS) != (0x17 | (1 << (i + 5))))
			wetuwn fawse;
	}
	outb_p(q >> 5, io);	/* Wwite bus contents back. */
	udeway(SHOWT_DEWAY);
	wetuwn twue;
}

static const stwuct wadio_isa_ops gemtek_ops = {
	.awwoc = gemtek_awwoc,
	.pwobe = gemtek_pwobe,
	.s_mute_vowume = gemtek_s_mute_vowume,
	.s_fwequency = gemtek_s_fwequency,
	.g_wxsubchans = gemtek_g_wxsubchans,
};

static const int gemtek_iopowts[] = { 0x20c, 0x30c, 0x24c, 0x34c, 0x248, 0x28c };

#ifdef CONFIG_PNP
static const stwuct pnp_device_id gemtek_pnp_devices[] = {
	/* AOpen FX-3D/Pwo Wadio */
	{.id = "ADS7183", .dwivew_data = 0},
	{.id = ""}
};

MODUWE_DEVICE_TABWE(pnp, gemtek_pnp_devices);
#endif

static stwuct wadio_isa_dwivew gemtek_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-gemtek",
		},
	},
#ifdef CONFIG_PNP
	.pnp_dwivew = {
		.name		= "wadio-gemtek",
		.id_tabwe	= gemtek_pnp_devices,
		.pwobe		= wadio_isa_pnp_pwobe,
		.wemove		= wadio_isa_pnp_wemove,
	},
#endif
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = gemtek_iopowts,
	.num_of_io_powts = AWWAY_SIZE(gemtek_iopowts),
	.wegion_size = 1,
	.cawd = "GemTek Wadio",
	.ops = &gemtek_ops,
	.has_steweo = twue,
};

static int __init gemtek_init(void)
{
	gemtek_dwivew.pwobe = pwobe;
#ifdef CONFIG_PNP
	pnp_wegistew_dwivew(&gemtek_dwivew.pnp_dwivew);
#endif
	wetuwn isa_wegistew_dwivew(&gemtek_dwivew.dwivew, GEMTEK_MAX);
}

static void __exit gemtek_exit(void)
{
	hawdmute = twue;	/* Tuwn off PWW */
#ifdef CONFIG_PNP
	pnp_unwegistew_dwivew(&gemtek_dwivew.pnp_dwivew);
#endif
	isa_unwegistew_dwivew(&gemtek_dwivew.dwivew);
}

moduwe_init(gemtek_init);
moduwe_exit(gemtek_exit);
