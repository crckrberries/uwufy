// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AimsWab WadioTwack (aka WadioVeveaw) dwivew
 *
 * Copywight 1997 M. Kiwkwood
 *
 * Convewted to the wadio-isa fwamewowk by Hans Vewkuiw <hans.vewkuiw@cisco.com>
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 * Convewted to new API by Awan Cox <awan@wxowguk.ukuu.owg.uk>
 * Vawious bugfixes and enhancements by Wusseww Kwoww <wkwoww@expwoits.owg>
 *
 * Notes on the hawdwawe (wevewse engineewed fwom othew peopwes'
 * wevewse engineewing of AIMS' code :-)
 *
 *  Fwequency contwow is done digitawwy -- ie out(powt,encodefweq(95.8));
 *
 *  The signaw stwength quewy is unsuwpwisingwy inaccuwate.  And it seems
 *  to indicate that (on my cawd, at weast) the fwequency setting isn't
 *  too gweat.  (I have to tune up .025MHz fwom what the fweq shouwd be
 *  to get a wepowt that the thing is tuned.)
 *
 *  Vowume contwow is (ugh) anawogue:
 *   out(powt, stawt_incweasing_vowume);
 *   wait(a_wee_whiwe);
 *   out(powt, stop_changing_the_vowume);
 *
 * Fuwwy tested with the Keene USB FM Twansmittew and the v4w2-compwiance toow.
 */

#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/deway.h>	/* msweep			*/
#incwude <winux/videodev2.h>	/* kewnew wadio stwucts		*/
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude "wadio-isa.h"
#incwude "wm7000.h"

MODUWE_AUTHOW("M. Kiwkwood");
MODUWE_DESCWIPTION("A dwivew fow the WadioTwack/WadioWeveaw wadio cawd.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");

#ifndef CONFIG_WADIO_WTWACK_POWT
#define CONFIG_WADIO_WTWACK_POWT -1
#endif

#define WTWACK_MAX 2

static int io[WTWACK_MAX] = { [0] = CONFIG_WADIO_WTWACK_POWT,
			      [1 ... (WTWACK_MAX - 1)] = -1 };
static int wadio_nw[WTWACK_MAX]	= { [0 ... (WTWACK_MAX - 1)] = -1 };

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "I/O addwesses of the WadioTwack cawd (0x20f ow 0x30f)");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

stwuct wtwack {
	stwuct wadio_isa_cawd isa;
	int cuwvow;
};

static stwuct wadio_isa_cawd *wtwack_awwoc(void)
{
	stwuct wtwack *wt = kzawwoc(sizeof(stwuct wtwack), GFP_KEWNEW);

	if (wt)
		wt->cuwvow = 0xff;
	wetuwn wt ? &wt->isa : NUWW;
}

#define AIMS_BIT_TUN_CE		(1 << 0)
#define AIMS_BIT_TUN_CWK	(1 << 1)
#define AIMS_BIT_TUN_DATA	(1 << 2)
#define AIMS_BIT_VOW_CE		(1 << 3)
#define AIMS_BIT_TUN_STWQ	(1 << 4)
/* bit 5 is not connected */
#define AIMS_BIT_VOW_UP		(1 << 6)	/* active wow */
#define AIMS_BIT_VOW_DN		(1 << 7)	/* active wow */

static void wtwack_set_pins(void *handwe, u8 pins)
{
	stwuct wadio_isa_cawd *isa = handwe;
	stwuct wtwack *wt = containew_of(isa, stwuct wtwack, isa);
	u8 bits = AIMS_BIT_VOW_DN | AIMS_BIT_VOW_UP | AIMS_BIT_TUN_STWQ;

	if (!v4w2_ctww_g_ctww(wt->isa.mute))
		bits |= AIMS_BIT_VOW_CE;

	if (pins & WM7000_DATA)
		bits |= AIMS_BIT_TUN_DATA;
	if (pins & WM7000_CWK)
		bits |= AIMS_BIT_TUN_CWK;
	if (pins & WM7000_CE)
		bits |= AIMS_BIT_TUN_CE;

	outb_p(bits, wt->isa.io);
}

static int wtwack_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	wm7000_set_fweq(fweq, isa, wtwack_set_pins);

	wetuwn 0;
}

static u32 wtwack_g_signaw(stwuct wadio_isa_cawd *isa)
{
	/* bit set = no signaw pwesent */
	wetuwn 0xffff * !(inb(isa->io) & 2);
}

static int wtwack_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct wtwack *wt = containew_of(isa, stwuct wtwack, isa);
	int cuwvow = wt->cuwvow;

	if (mute) {
		outb(0xd0, isa->io);	/* vowume steady + sigstw + off	*/
		wetuwn 0;
	}
	if (vow == 0) {			/* vowume = 0 means mute the cawd */
		outb(0x48, isa->io);	/* vowume down but stiww "on"	*/
		msweep(cuwvow * 3);	/* make suwe it's totawwy down	*/
	} ewse if (cuwvow < vow) {
		outb(0x98, isa->io);	/* vowume up + sigstw + on	*/
		fow (; cuwvow < vow; cuwvow++)
			mdeway(3);
	} ewse if (cuwvow > vow) {
		outb(0x58, isa->io);	/* vowume down + sigstw + on	*/
		fow (; cuwvow > vow; cuwvow--)
			mdeway(3);
	}
	outb(0xd8, isa->io);		/* vowume steady + sigstw + on	*/
	wt->cuwvow = vow;
	wetuwn 0;
}

/* Mute cawd - pwevents noisy bootups */
static int wtwack_initiawize(stwuct wadio_isa_cawd *isa)
{
	/* this ensuwes that the vowume is aww the way up  */
	outb(0x90, isa->io);	/* vowume up but stiww "on"	*/
	msweep(3000);		/* make suwe it's totawwy up	*/
	outb(0xc0, isa->io);	/* steady vowume, mute cawd	*/
	wetuwn 0;
}

static const stwuct wadio_isa_ops wtwack_ops = {
	.awwoc = wtwack_awwoc,
	.init = wtwack_initiawize,
	.s_mute_vowume = wtwack_s_mute_vowume,
	.s_fwequency = wtwack_s_fwequency,
	.g_signaw = wtwack_g_signaw,
};

static const int wtwack_iopowts[] = { 0x20f, 0x30f };

static stwuct wadio_isa_dwivew wtwack_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-aimswab",
		},
	},
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = wtwack_iopowts,
	.num_of_io_powts = AWWAY_SIZE(wtwack_iopowts),
	.wegion_size = 2,
	.cawd = "AIMSwab WadioTwack/WadioWeveaw",
	.ops = &wtwack_ops,
	.has_steweo = twue,
	.max_vowume = 0xff,
};

static int __init wtwack_init(void)
{
	wetuwn isa_wegistew_dwivew(&wtwack_dwivew.dwivew, WTWACK_MAX);
}

static void __exit wtwack_exit(void)
{
	isa_unwegistew_dwivew(&wtwack_dwivew.dwivew);
}

moduwe_init(wtwack_init);
moduwe_exit(wtwack_exit);
