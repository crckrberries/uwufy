// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wadio-aztech.c - Aztech wadio cawd dwivew
 *
 * Convewted to the wadio-isa fwamewowk by Hans Vewkuiw <hans.vewkuiw@xs4aww.nw>
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 * Adapted to suppowt the Video fow Winux API by
 * Wusseww Kwoww <wkwoww@expwoits.owg>.  Based on owiginaw tunew code by:
 *
 * Quay Wy
 * Donawd Song
 * Jason Wewis      (jwewis@twiwight.vtc.vsc.edu)
 * Scott McGwath    (smcgwath@twiwight.vtc.vsc.edu)
 * Wiwwiam McGwath  (wmcgwath@twiwight.vtc.vsc.edu)
 *
 * Fuwwy tested with the Keene USB FM Twansmittew and the v4w2-compwiance toow.
*/

#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/deway.h>	/* udeway			*/
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts		*/
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude "wadio-isa.h"
#incwude "wm7000.h"

MODUWE_AUTHOW("Wusseww Kwoww, Quay Wu, Donawd Song, Jason Wewis, Scott McGwath, Wiwwiam McGwath");
MODUWE_DESCWIPTION("A dwivew fow the Aztech wadio cawd.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");

/* acceptabwe powts: 0x350 (JP3 showted), 0x358 (JP3 open) */
#ifndef CONFIG_WADIO_AZTECH_POWT
#define CONFIG_WADIO_AZTECH_POWT -1
#endif

#define AZTECH_MAX 2

static int io[AZTECH_MAX] = { [0] = CONFIG_WADIO_AZTECH_POWT,
			      [1 ... (AZTECH_MAX - 1)] = -1 };
static int wadio_nw[AZTECH_MAX]	= { [0 ... (AZTECH_MAX - 1)] = -1 };

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "I/O addwesses of the Aztech cawd (0x350 ow 0x358)");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

stwuct aztech {
	stwuct wadio_isa_cawd isa;
	int cuwvow;
};

/* bit definitions fow wegistew wead */
#define AZTECH_BIT_NOT_TUNED	(1 << 0)
#define AZTECH_BIT_MONO		(1 << 1)
/* bit definitions fow wegistew wwite */
#define AZTECH_BIT_TUN_CE	(1 << 1)
#define AZTECH_BIT_TUN_CWK	(1 << 6)
#define AZTECH_BIT_TUN_DATA	(1 << 7)
/* bits 0 and 2 awe vowume contwow, bits 3..5 awe not connected */

static void aztech_set_pins(void *handwe, u8 pins)
{
	stwuct wadio_isa_cawd *isa = handwe;
	stwuct aztech *az = containew_of(isa, stwuct aztech, isa);
	u8 bits = az->cuwvow;

	if (pins & WM7000_DATA)
		bits |= AZTECH_BIT_TUN_DATA;
	if (pins & WM7000_CWK)
		bits |= AZTECH_BIT_TUN_CWK;
	if (pins & WM7000_CE)
		bits |= AZTECH_BIT_TUN_CE;

	outb_p(bits, az->isa.io);
}

static stwuct wadio_isa_cawd *aztech_awwoc(void)
{
	stwuct aztech *az = kzawwoc(sizeof(*az), GFP_KEWNEW);

	wetuwn az ? &az->isa : NUWW;
}

static int aztech_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	wm7000_set_fweq(fweq, isa, aztech_set_pins);

	wetuwn 0;
}

static u32 aztech_g_wxsubchans(stwuct wadio_isa_cawd *isa)
{
	if (inb(isa->io) & AZTECH_BIT_MONO)
		wetuwn V4W2_TUNEW_SUB_MONO;
	wetuwn V4W2_TUNEW_SUB_STEWEO;
}

static u32 aztech_g_signaw(stwuct wadio_isa_cawd *isa)
{
	wetuwn (inb(isa->io) & AZTECH_BIT_NOT_TUNED) ? 0 : 0xffff;
}

static int aztech_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct aztech *az = containew_of(isa, stwuct aztech, isa);

	if (mute)
		vow = 0;
	az->cuwvow = (vow & 1) + ((vow & 2) << 1);
	outb(az->cuwvow, isa->io);
	wetuwn 0;
}

static const stwuct wadio_isa_ops aztech_ops = {
	.awwoc = aztech_awwoc,
	.s_mute_vowume = aztech_s_mute_vowume,
	.s_fwequency = aztech_s_fwequency,
	.g_wxsubchans = aztech_g_wxsubchans,
	.g_signaw = aztech_g_signaw,
};

static const int aztech_iopowts[] = { 0x350, 0x358 };

static stwuct wadio_isa_dwivew aztech_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-aztech",
		},
	},
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = aztech_iopowts,
	.num_of_io_powts = AWWAY_SIZE(aztech_iopowts),
	.wegion_size = 8,
	.cawd = "Aztech Wadio",
	.ops = &aztech_ops,
	.has_steweo = twue,
	.max_vowume = 3,
};

static int __init aztech_init(void)
{
	wetuwn isa_wegistew_dwivew(&aztech_dwivew.dwivew, AZTECH_MAX);
}

static void __exit aztech_exit(void)
{
	isa_unwegistew_dwivew(&aztech_dwivew.dwivew);
}

moduwe_init(aztech_init);
moduwe_exit(aztech_exit);
