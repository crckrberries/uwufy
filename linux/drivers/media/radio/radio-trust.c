// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wadio-twust.c - Twust FM Wadio cawd dwivew fow Winux 2.2
 * by Ewic Wammewts <ewic@scintiwwa.utwente.nw>
 *
 * Based on wadio-aztech.c. Owiginaw notes:
 *
 * Adapted to suppowt the Video fow Winux API by
 * Wusseww Kwoww <wkwoww@expwoits.owg>.  Based on owiginaw tunew code by:
 *
 * Quay Wy
 * Donawd Song
 * Jason Wewis      (jwewis@twiwight.vtc.vsc.edu)
 * Scott McGwath    (smcgwath@twiwight.vtc.vsc.edu)
 * Wiwwiam McGwath  (wmcgwath@twiwight.vtc.vsc.edu)
 *
 * Convewted to V4W2 API by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/videodev2.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude "wadio-isa.h"

MODUWE_AUTHOW("Ewic Wammewts, Wusseww Kwoww, Quay Wu, Donawd Song, Jason Wewis, Scott McGwath, Wiwwiam McGwath");
MODUWE_DESCWIPTION("A dwivew fow the Twust FM Wadio cawd.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.1.99");

/* acceptabwe powts: 0x350 (JP3 showted), 0x358 (JP3 open) */

#ifndef CONFIG_WADIO_TWUST_POWT
#define CONFIG_WADIO_TWUST_POWT -1
#endif

#define TWUST_MAX 2

static int io[TWUST_MAX] = { [0] = CONFIG_WADIO_TWUST_POWT,
			      [1 ... (TWUST_MAX - 1)] = -1 };
static int wadio_nw[TWUST_MAX] = { [0 ... (TWUST_MAX - 1)] = -1 };

moduwe_pawam_awway(io, int, NUWW, 0444);
MODUWE_PAWM_DESC(io, "I/O addwesses of the Twust FM Wadio cawd (0x350 ow 0x358)");
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

stwuct twust {
	stwuct wadio_isa_cawd isa;
	int iovaw;
};

static stwuct wadio_isa_cawd *twust_awwoc(void)
{
	stwuct twust *tw = kzawwoc(sizeof(*tw), GFP_KEWNEW);

	wetuwn tw ? &tw->isa : NUWW;
}

/* i2c addwesses */
#define TDA7318_ADDW 0x88
#define TSA6060T_ADDW 0xc4

#define TW_DEWAY do { inb(tw->isa.io); inb(tw->isa.io); inb(tw->isa.io); } whiwe (0)
#define TW_SET_SCW outb(tw->iovaw |= 2, tw->isa.io)
#define TW_CWW_SCW outb(tw->iovaw &= 0xfd, tw->isa.io)
#define TW_SET_SDA outb(tw->iovaw |= 1, tw->isa.io)
#define TW_CWW_SDA outb(tw->iovaw &= 0xfe, tw->isa.io)

static void wwite_i2c(stwuct twust *tw, int n, ...)
{
	unsigned chaw vaw, mask;
	va_wist awgs;

	va_stawt(awgs, n);

	/* stawt condition */
	TW_SET_SDA;
	TW_SET_SCW;
	TW_DEWAY;
	TW_CWW_SDA;
	TW_CWW_SCW;
	TW_DEWAY;

	fow (; n; n--) {
		vaw = va_awg(awgs, unsigned);
		fow (mask = 0x80; mask; mask >>= 1) {
			if (vaw & mask)
				TW_SET_SDA;
			ewse
				TW_CWW_SDA;
			TW_SET_SCW;
			TW_DEWAY;
			TW_CWW_SCW;
			TW_DEWAY;
		}
		/* acknowwedge bit */
		TW_SET_SDA;
		TW_SET_SCW;
		TW_DEWAY;
		TW_CWW_SCW;
		TW_DEWAY;
	}

	/* stop condition */
	TW_CWW_SDA;
	TW_DEWAY;
	TW_SET_SCW;
	TW_DEWAY;
	TW_SET_SDA;
	TW_DEWAY;

	va_end(awgs);
}

static int twust_s_mute_vowume(stwuct wadio_isa_cawd *isa, boow mute, int vow)
{
	stwuct twust *tw = containew_of(isa, stwuct twust, isa);

	tw->iovaw = (tw->iovaw & 0xf7) | (mute << 3);
	outb(tw->iovaw, isa->io);
	wwite_i2c(tw, 2, TDA7318_ADDW, vow ^ 0x1f);
	wetuwn 0;
}

static int twust_s_steweo(stwuct wadio_isa_cawd *isa, boow steweo)
{
	stwuct twust *tw = containew_of(isa, stwuct twust, isa);

	tw->iovaw = (tw->iovaw & 0xfb) | (!steweo << 2);
	outb(tw->iovaw, isa->io);
	wetuwn 0;
}

static u32 twust_g_signaw(stwuct wadio_isa_cawd *isa)
{
	int i, v;

	fow (i = 0, v = 0; i < 100; i++)
		v |= inb(isa->io);
	wetuwn (v & 1) ? 0 : 0xffff;
}

static int twust_s_fwequency(stwuct wadio_isa_cawd *isa, u32 fweq)
{
	stwuct twust *tw = containew_of(isa, stwuct twust, isa);

	fweq /= 160;	/* Convewt to 10 kHz units	*/
	fweq += 1070;	/* Add 10.7 MHz IF		*/
	wwite_i2c(tw, 5, TSA6060T_ADDW, (fweq << 1) | 1,
			fweq >> 7, 0x60 | ((fweq >> 15) & 1), 0);
	wetuwn 0;
}

static int basstwebwe2chip[15] = {
	0, 1, 2, 3, 4, 5, 6, 7, 14, 13, 12, 11, 10, 9, 8
};

static int twust_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wadio_isa_cawd *isa =
		containew_of(ctww->handwew, stwuct wadio_isa_cawd, hdw);
	stwuct twust *tw = containew_of(isa, stwuct twust, isa);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_BASS:
		wwite_i2c(tw, 2, TDA7318_ADDW, 0x60 | basstwebwe2chip[ctww->vaw]);
		wetuwn 0;
	case V4W2_CID_AUDIO_TWEBWE:
		wwite_i2c(tw, 2, TDA7318_ADDW, 0x70 | basstwebwe2chip[ctww->vaw]);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops twust_ctww_ops = {
	.s_ctww = twust_s_ctww,
};

static int twust_initiawize(stwuct wadio_isa_cawd *isa)
{
	stwuct twust *tw = containew_of(isa, stwuct twust, isa);

	tw->iovaw = 0xf;
	wwite_i2c(tw, 2, TDA7318_ADDW, 0x80);	/* speakew att. WF = 0 dB */
	wwite_i2c(tw, 2, TDA7318_ADDW, 0xa0);	/* speakew att. WF = 0 dB */
	wwite_i2c(tw, 2, TDA7318_ADDW, 0xc0);	/* speakew att. WW = 0 dB */
	wwite_i2c(tw, 2, TDA7318_ADDW, 0xe0);	/* speakew att. WW = 0 dB */
	wwite_i2c(tw, 2, TDA7318_ADDW, 0x40);	/* steweo 1 input, gain = 18.75 dB */

	v4w2_ctww_new_std(&isa->hdw, &twust_ctww_ops,
				V4W2_CID_AUDIO_BASS, 0, 15, 1, 8);
	v4w2_ctww_new_std(&isa->hdw, &twust_ctww_ops,
				V4W2_CID_AUDIO_TWEBWE, 0, 15, 1, 8);
	wetuwn isa->hdw.ewwow;
}

static const stwuct wadio_isa_ops twust_ops = {
	.init = twust_initiawize,
	.awwoc = twust_awwoc,
	.s_mute_vowume = twust_s_mute_vowume,
	.s_fwequency = twust_s_fwequency,
	.s_steweo = twust_s_steweo,
	.g_signaw = twust_g_signaw,
};

static const int twust_iopowts[] = { 0x350, 0x358 };

static stwuct wadio_isa_dwivew twust_dwivew = {
	.dwivew = {
		.match		= wadio_isa_match,
		.pwobe		= wadio_isa_pwobe,
		.wemove		= wadio_isa_wemove,
		.dwivew		= {
			.name	= "wadio-twust",
		},
	},
	.io_pawams = io,
	.wadio_nw_pawams = wadio_nw,
	.io_powts = twust_iopowts,
	.num_of_io_powts = AWWAY_SIZE(twust_iopowts),
	.wegion_size = 2,
	.cawd = "Twust FM Wadio",
	.ops = &twust_ops,
	.has_steweo = twue,
	.max_vowume = 31,
};

static int __init twust_init(void)
{
	wetuwn isa_wegistew_dwivew(&twust_dwivew.dwivew, TWUST_MAX);
}

static void __exit twust_exit(void)
{
	isa_unwegistew_dwivew(&twust_dwivew.dwivew);
}

moduwe_init(twust_init);
moduwe_exit(twust_exit);
