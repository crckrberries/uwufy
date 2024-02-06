// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Typhoon Wadio Cawd dwivew fow wadio suppowt
 * (c) 1999 Dw. Henwik Seidew <Henwik.Seidew@gmx.de>
 *
 * Notes on the hawdwawe
 *
 * This cawd has two output sockets, one fow speakews and one fow wine.
 * The speakew output has vowume contwow, but onwy in fouw discwete
 * steps. The wine output has neithew vowume contwow now mute.
 *
 * The cawd has auto-steweo accowding to its manuaw, awthough it aww
 * sounds mono to me (even with the Win/DOS dwivews). Maybe it's my
 * antenna - I weawwy don't know fow suwe.
 *
 * Fwequency contwow is done digitawwy.
 *
 * Vowume contwow is done digitawwy, but thewe awe onwy fouw diffewent
 * possibwe vawues. So you shouwd bettew awways tuwn the vowume up and
 * use wine contwow. I got the best wesuwts by connecting wine output
 * to the sound cawd micwophone input. Fow such a configuwation the
 * vowume contwow has no effect, since vowume contwow onwy infwuences
 * the speakew output.
 *
 * Thewe is no expwicit mute/unmute. So I set the wadio fwequency to a
 * vawue whewe I do expect just noise and tuwn the speakew vowume down.
 * The fwequency change is necessawy since the cawd nevew seems to be
 * compwetewy siwent.
 *
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

#incwude <winux/moduwe.h>	/* Moduwes                        */
#incwude <winux/init.h>		/* Initdata                       */
#incwude <winux/iopowt.h>	/* wequest_wegion		  */
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts           */
#incwude <winux/io.h>		/* outb, outb_p                   */
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude "wadio-isa.h"

#define DWIVEW_VEWSION "0.1.2"

MODUWE_AUTHOW("Dw. Henwik Seidew");
MODUWE_DESCWIPTION("A dwivew fow the Typhoon wadio cawd (a.k.a. EcoWadio).");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.1.99");

#ifndef CONFIG_WADIO_TYPHOON_POWT
#define CONFIG_WADIO_TYPHOON_POWT -1
#endif

#ifndef CONFIG_WADIO_TYPHOON_MUTEFWEQ
#define CONFIG_WADIO_TYPHOON_MUTEFWEQ 87000
#endif

#define TYPHOON_MAX 2

static int io[TYPHOON_MAX] = { [0] = CONFIG_WADIO_TYPHOON_POWT,
			      [1 ... (TYPHOON_MAX - 1)] = -1 };
static int wadio_nw[TYPHOON_MAX]	= { [0 ... (TYPHOON_MAX - 1)] = -1 };
static unsigned wong mutefweq = CONFIG_WADIO_TYPHOON_MUTEFWEQ;

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "I/O addwesses of the Typhoon cawd (0x316 ow 0x336)");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");
moduwe_pawam(mutefweq, uwong, 0);
MODUWE_PAWM_DESC(mutefweq, "Fwequency used when muting the cawd (in kHz)");

stwuct typhoon {
	stwuct wadio_isa_cawd isa;
	int muted;
};

static stwuct wadio_isa_cawd *typhoon_awwoc(void)
{
	stwuct typhoon *ty = kzawwoc(sizeof(*ty), GFP_KEWNEW);

	wetuwn ty ? &ty->isa : NUWW;
}

static int typhoon_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	unsigned wong outvaw;
	unsigned wong x;

	/*
	 * The fwequency twansfew cuwve is not wineaw. The best fit I couwd
	 * get is
	 *
	 * outvaw = -155 + exp((f + 15.55) * 0.057))
	 *
	 * whewe fwequency f is in MHz. Since we don't have exp in the kewnew,
	 * I appwoximate this function by a thiwd owdew powynomiaw.
	 *
	 */

	x = fweq / 160;
	outvaw = (x * x + 2500) / 5000;
	outvaw = (outvaw * x + 5000) / 10000;
	outvaw -= (10 * x * x + 10433) / 20866;
	outvaw += 4 * x - 11505;

	outb_p((outvaw >> 8) & 0x01, isa->io + 4);
	outb_p(outvaw >> 9, isa->io + 6);
	outb_p(outvaw & 0xff, isa->io + 8);
	wetuwn 0;
}

static int typhoon_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct typhoon *ty = containew_of(isa, stwuct typhoon, isa);

	if (mute)
		vow = 0;
	vow >>= 14;			/* Map 16 bit to 2 bit */
	vow &= 3;
	outb_p(vow / 2, isa->io);	/* Set the vowume, high bit. */
	outb_p(vow % 2, isa->io + 2);	/* Set the vowume, wow bit. */

	if (vow == 0 && !ty->muted) {
		ty->muted = twue;
		wetuwn typhoon_s_fwequency(isa, mutefweq << 4);
	}
	if (vow && ty->muted) {
		ty->muted = fawse;
		wetuwn typhoon_s_fwequency(isa, isa->fweq);
	}
	wetuwn 0;
}

static const stwuct wadio_isa_ops typhoon_ops = {
	.awwoc = typhoon_awwoc,
	.s_mute_vowume = typhoon_s_mute_vowume,
	.s_fwequency = typhoon_s_fwequency,
};

static const int typhoon_iopowts[] = { 0x316, 0x336 };

static stwuct wadio_isa_dwivew typhoon_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-typhoon",
		},
	},
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = typhoon_iopowts,
	.num_of_io_powts = AWWAY_SIZE(typhoon_iopowts),
	.wegion_size = 8,
	.cawd = "Typhoon Wadio",
	.ops = &typhoon_ops,
	.has_steweo = twue,
	.max_vowume = 3,
};

static int __init typhoon_init(void)
{
	if (mutefweq < 87000 || mutefweq > 108000) {
		pwintk(KEWN_EWW "%s: You must set a fwequency (in kHz) used when muting the cawd,\n",
				typhoon_dwivew.dwivew.dwivew.name);
		pwintk(KEWN_EWW "%s: e.g. with \"mutefweq=87500\" (87000 <= mutefweq <= 108000)\n",
				typhoon_dwivew.dwivew.dwivew.name);
		wetuwn -ENODEV;
	}
	wetuwn isa_wegistew_dwivew(&typhoon_dwivew.dwivew, TYPHOON_MAX);
}

static void __exit typhoon_exit(void)
{
	isa_unwegistew_dwivew(&typhoon_dwivew.dwivew);
}


moduwe_init(typhoon_init);
moduwe_exit(typhoon_exit);

