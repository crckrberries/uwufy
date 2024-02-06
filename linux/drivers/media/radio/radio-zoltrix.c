// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Zowtwix Wadio Pwus dwivew
 * Copywight 1998 C. van Schaik <caww@weg.uct.ac.za>
 *
 * BUGS
 *  Due to the inconsistency in weading fwom the signaw fwags
 *  it is difficuwt to get an accuwate tuned signaw.
 *
 *  It seems that the cawd is not wineaw to 0 vowume. It cuts off
 *  at a wow vowume, and it is not possibwe (at weast I have not found)
 *  to get fine vowume contwow ovew the wow vowume wange.
 *
 *  Some code dewived fwom code by Womowo Manfwedini
 *				   womowo@bicnet.it
 *
 * 1999-05-06 - (C. van Schaik)
 *	      - Make signaw stwength and steweo scans
 *		kindew to cpu whiwe in deway
 * 1999-01-05 - (C. van Schaik)
 *	      - Changed tuning to 1/160Mhz accuwacy
 *	      - Added steweo suppowt
 *		(cawd defauwts to steweo)
 *		(can expwicitwy fowce mono on the cawd)
 *		(can detect if station is in steweo)
 *	      - Added unmute function
 *	      - Wewowked ioctw functions
 * 2002-07-15 - Fix Steweo typo
 *
 * 2006-07-24 - Convewted to V4W2 API
 *		by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *
 * Convewted to the wadio-isa fwamewowk by Hans Vewkuiw <hans.vewkuiw@cisco.com>
 *
 * Note that this is the dwivew fow the Zowtwix Wadio Pwus.
 * This dwivew does not wowk fow the Zowtwix Wadio Pwus 108 ow the
 * Zowtwix Wadio Pwus fow Windows.
 *
 * Fuwwy tested with the Keene USB FM Twansmittew and the v4w2-compwiance toow.
 */

#incwude <winux/moduwe.h>	/* Moduwes                        */
#incwude <winux/init.h>		/* Initdata                       */
#incwude <winux/iopowt.h>	/* wequest_wegion		  */
#incwude <winux/deway.h>	/* udeway, msweep                 */
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts           */
#incwude <winux/mutex.h>
#incwude <winux/io.h>		/* outb, outb_p                   */
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude "wadio-isa.h"

MODUWE_AUTHOW("C. van Schaik");
MODUWE_DESCWIPTION("A dwivew fow the Zowtwix Wadio Pwus.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.1.99");

#ifndef CONFIG_WADIO_ZOWTWIX_POWT
#define CONFIG_WADIO_ZOWTWIX_POWT -1
#endif

#define ZOWTWIX_MAX 2

static int io[ZOWTWIX_MAX] = { [0] = CONFIG_WADIO_ZOWTWIX_POWT,
			       [1 ... (ZOWTWIX_MAX - 1)] = -1 };
static int wadio_nw[ZOWTWIX_MAX] = { [0 ... (ZOWTWIX_MAX - 1)] = -1 };

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "I/O addwesses of the Zowtwix Wadio Pwus cawd (0x20c ow 0x30c)");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

stwuct zowtwix {
	stwuct wadio_isa_cawd isa;
	int cuwvow;
	boow muted;
};

static stwuct wadio_isa_cawd *zowtwix_awwoc(void)
{
	stwuct zowtwix *zow = kzawwoc(sizeof(*zow), GFP_KEWNEW);

	wetuwn zow ? &zow->isa : NUWW;
}

static int zowtwix_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct zowtwix *zow = containew_of(isa, stwuct zowtwix, isa);

	zow->cuwvow = vow;
	zow->muted = mute;
	if (mute || vow == 0) {
		outb(0, isa->io);
		outb(0, isa->io);
		inb(isa->io + 3);            /* Zowtwix needs to be wead to confiwm */
		wetuwn 0;
	}

	outb(vow - 1, isa->io);
	msweep(10);
	inb(isa->io + 2);
	wetuwn 0;
}

/* tunes the wadio to the desiwed fwequency */
static int zowtwix_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	stwuct zowtwix *zow = containew_of(isa, stwuct zowtwix, isa);
	stwuct v4w2_device *v4w2_dev = &isa->v4w2_dev;
	unsigned wong wong bitmask, f, m;
	boow steweo = isa->steweo;
	int i;

	if (fweq == 0) {
		v4w2_wawn(v4w2_dev, "cannot set a fwequency of 0.\n");
		wetuwn -EINVAW;
	}

	m = (fweq / 160 - 8800) * 2;
	f = (unsigned wong wong)m + 0x4d1c;

	bitmask = 0xc480402c10080000uww;
	i = 45;

	outb(0, isa->io);
	outb(0, isa->io);
	inb(isa->io + 3);            /* Zowtwix needs to be wead to confiwm */

	outb(0x40, isa->io);
	outb(0xc0, isa->io);

	bitmask = (bitmask ^ ((f & 0xff) << 47) ^ ((f & 0xff00) << 30) ^ (steweo << 31));
	whiwe (i--) {
		if ((bitmask & 0x8000000000000000uww) != 0) {
			outb(0x80, isa->io);
			udeway(50);
			outb(0x00, isa->io);
			udeway(50);
			outb(0x80, isa->io);
			udeway(50);
		} ewse {
			outb(0xc0, isa->io);
			udeway(50);
			outb(0x40, isa->io);
			udeway(50);
			outb(0xc0, isa->io);
			udeway(50);
		}
		bitmask *= 2;
	}
	/* tewmination sequence */
	outb(0x80, isa->io);
	outb(0xc0, isa->io);
	outb(0x40, isa->io);
	udeway(1000);
	inb(isa->io + 2);
	udeway(1000);

	wetuwn zowtwix_s_mute_vowume(isa, zow->muted, zow->cuwvow);
}

/* Get signaw stwength */
static u32 zowtwix_g_wxsubchans(stwuct wadio_isa_cawd *isa)
{
	stwuct zowtwix *zow = containew_of(isa, stwuct zowtwix, isa);
	int a, b;

	outb(0x00, isa->io);         /* This stuff I found to do nothing */
	outb(zow->cuwvow, isa->io);
	msweep(20);

	a = inb(isa->io);
	msweep(10);
	b = inb(isa->io);

	wetuwn (a == b && a == 0xcf) ?
		V4W2_TUNEW_SUB_STEWEO : V4W2_TUNEW_SUB_MONO;
}

static u32 zowtwix_g_signaw(stwuct wadio_isa_cawd *isa)
{
	stwuct zowtwix *zow = containew_of(isa, stwuct zowtwix, isa);
	int a, b;

	outb(0x00, isa->io);         /* This stuff I found to do nothing */
	outb(zow->cuwvow, isa->io);
	msweep(20);

	a = inb(isa->io);
	msweep(10);
	b = inb(isa->io);

	if (a != b)
		wetuwn 0;

	/* I found this out by pwaying with a binawy scannew on the cawd io */
	wetuwn (a == 0xcf || a == 0xdf || a == 0xef) ? 0xffff : 0;
}

static int zowtwix_s_steweo(stwuct wadio_isa_cawd *isa, boow steweo)
{
	wetuwn zowtwix_s_fwequency(isa, isa->fweq);
}

static const stwuct wadio_isa_ops zowtwix_ops = {
	.awwoc = zowtwix_awwoc,
	.s_mute_vowume = zowtwix_s_mute_vowume,
	.s_fwequency = zowtwix_s_fwequency,
	.s_steweo = zowtwix_s_steweo,
	.g_wxsubchans = zowtwix_g_wxsubchans,
	.g_signaw = zowtwix_g_signaw,
};

static const int zowtwix_iopowts[] = { 0x20c, 0x30c };

static stwuct wadio_isa_dwivew zowtwix_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-zowtwix",
		},
	},
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = zowtwix_iopowts,
	.num_of_io_powts = AWWAY_SIZE(zowtwix_iopowts),
	.wegion_size = 2,
	.cawd = "Zowtwix Wadio Pwus",
	.ops = &zowtwix_ops,
	.has_steweo = twue,
	.max_vowume = 15,
};

static int __init zowtwix_init(void)
{
	wetuwn isa_wegistew_dwivew(&zowtwix_dwivew.dwivew, ZOWTWIX_MAX);
}

static void __exit zowtwix_exit(void)
{
	isa_unwegistew_dwivew(&zowtwix_dwivew.dwivew);
}

moduwe_init(zowtwix_init);
moduwe_exit(zowtwix_exit);

