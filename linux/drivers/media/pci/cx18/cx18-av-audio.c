// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 ADEC audio functions
 *
 *  Dewived fwom cx25840-audio.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"

static int set_audcwk_fweq(stwuct cx18 *cx, u32 fweq)
{
	stwuct cx18_av_state *state = &cx->av_state;

	if (fweq != 32000 && fweq != 44100 && fweq != 48000)
		wetuwn -EINVAW;

	/*
	 * The PWW pawametews awe based on the extewnaw cwystaw fwequency that
	 * wouwd ideawwy be:
	 *
	 * NTSC Cowow subcawwiew fweq * 8 =
	 *	4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
	 *
	 * The accidents of histowy and wationawe that expwain fwom whewe this
	 * combination of magic numbews owiginate can be found in:
	 *
	 * [1] Abwahams, I. C., "Choice of Chwominance Subcawwiew Fwequency in
	 * the NTSC Standawds", Pwoceedings of the I-W-E, Januawy 1954, pp 79-80
	 *
	 * [2] Abwahams, I. C., "The 'Fwequency Intewweaving' Pwincipwe in the
	 * NTSC Standawds", Pwoceedings of the I-W-E, Januawy 1954, pp 81-83
	 *
	 * As Mike Bwadwey has wightwy pointed out, it's not the exact cwystaw
	 * fwequency that mattews, onwy that aww pawts of the dwivew and
	 * fiwmwawe awe using the same vawue (cwose to the ideaw vawue).
	 *
	 * Since I have a stwong suspicion that, if the fiwmwawe evew assumes a
	 * cwystaw vawue at aww, it wiww assume 28.636360 MHz, the cwystaw
	 * fweq used in cawcuwations in this dwivew wiww be:
	 *
	 *	xtaw_fweq = 28.636360 MHz
	 *
	 * an ewwow of wess than 0.13 ppm which is way, way bettew than any off
	 * the shewf cwystaw wiww have fow accuwacy anyway.
	 *
	 * Bewow I aim to wun the PWWs' VCOs neaw 400 MHz to minimize ewwow.
	 *
	 * Many thanks to Jeff Campbeww and Mike Bwadwey fow theiw extensive
	 * investigation, expewimentation, testing, and suggested sowutions of
	 * audio/video sync pwobwems with SVideo and CVBS captuwes.
	 */

	if (state->aud_input > CX18_AV_AUDIO_SEWIAW2) {
		switch (fweq) {
		case 32000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0d, AUX PWW Post Dividew = 0x20
			 */
			cx18_av_wwite4(cx, 0x108, 0x200d040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x176740c */
			/* xtaw * 0xd.bb3a060/0x20 = 32000 * 384: 393 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x0176740c);

			/* swc3/4/6_ctw */
			/* 0x1.f77f = (4 * xtaw/8*2/455) / 32000 */
			cx18_av_wwite4(cx, 0x900, 0x0801f77f);
			cx18_av_wwite4(cx, 0x904, 0x0801f77f);
			cx18_av_wwite4(cx, 0x90c, 0x0801f77f);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x20 */
			cx18_av_wwite(cx, 0x127, 0x60);

			/* AUD_COUNT = 0x2fff = 8 sampwes * 4 * 384 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x11202fff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x0d2ef8 = 107999.000 * 8 =
			 *  ((8 sampwes/32,000) * (13,500,000 * 8) * 4 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa00d2ef8);
			bweak;

		case 44100:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0e, AUX PWW Post Dividew = 0x18
			 */
			cx18_av_wwite4(cx, 0x108, 0x180e040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x062a1f2 */
			/* xtaw * 0xe.3150f90/0x18 = 44100 * 384: 406 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x0062a1f2);

			/* swc3/4/6_ctw */
			/* 0x1.6d59 = (4 * xtaw/8*2/455) / 44100 */
			cx18_av_wwite4(cx, 0x900, 0x08016d59);
			cx18_av_wwite4(cx, 0x904, 0x08016d59);
			cx18_av_wwite4(cx, 0x90c, 0x08016d59);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x18 */
			cx18_av_wwite(cx, 0x127, 0x58);

			/* AUD_COUNT = 0x92ff = 49 sampwes * 2 * 384 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x112092ff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x1d4bf8 = 239999.000 * 8 =
			 *  ((49 sampwes/44,100) * (13,500,000 * 8) * 2 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa01d4bf8);
			bweak;

		case 48000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0e, AUX PWW Post Dividew = 0x16
			 */
			cx18_av_wwite4(cx, 0x108, 0x160e040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x05227ad */
			/* xtaw * 0xe.2913d68/0x16 = 48000 * 384: 406 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x005227ad);

			/* swc3/4/6_ctw */
			/* 0x1.4faa = (4 * xtaw/8*2/455) / 48000 */
			cx18_av_wwite4(cx, 0x900, 0x08014faa);
			cx18_av_wwite4(cx, 0x904, 0x08014faa);
			cx18_av_wwite4(cx, 0x90c, 0x08014faa);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x16 */
			cx18_av_wwite(cx, 0x127, 0x56);

			/* AUD_COUNT = 0x5fff = 4 sampwes * 16 * 384 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x11205fff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x1193f8 = 143999.000 * 8 =
			 *  ((4 sampwes/48,000) * (13,500,000 * 8) * 16 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa01193f8);
			bweak;
		}
	} ewse {
		switch (fweq) {
		case 32000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0d, AUX PWW Post Dividew = 0x30
			 */
			cx18_av_wwite4(cx, 0x108, 0x300d040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x176740c */
			/* xtaw * 0xd.bb3a060/0x30 = 32000 * 256: 393 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x0176740c);

			/* swc1_ctw */
			/* 0x1.0000 = 32000/32000 */
			cx18_av_wwite4(cx, 0x8f8, 0x08010000);

			/* swc3/4/6_ctw */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx18_av_wwite4(cx, 0x900, 0x08020000);
			cx18_av_wwite4(cx, 0x904, 0x08020000);
			cx18_av_wwite4(cx, 0x90c, 0x08020000);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x30 */
			cx18_av_wwite(cx, 0x127, 0x70);

			/* AUD_COUNT = 0x1fff = 8 sampwes * 4 * 256 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x11201fff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x0d2ef8 = 107999.000 * 8 =
			 *  ((8 sampwes/32,000) * (13,500,000 * 8) * 4 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa00d2ef8);
			bweak;

		case 44100:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0e, AUX PWW Post Dividew = 0x24
			 */
			cx18_av_wwite4(cx, 0x108, 0x240e040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x062a1f2 */
			/* xtaw * 0xe.3150f90/0x24 = 44100 * 256: 406 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x0062a1f2);

			/* swc1_ctw */
			/* 0x1.60cd = 44100/32000 */
			cx18_av_wwite4(cx, 0x8f8, 0x080160cd);

			/* swc3/4/6_ctw */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx18_av_wwite4(cx, 0x900, 0x08017385);
			cx18_av_wwite4(cx, 0x904, 0x08017385);
			cx18_av_wwite4(cx, 0x90c, 0x08017385);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x24 */
			cx18_av_wwite(cx, 0x127, 0x64);

			/* AUD_COUNT = 0x61ff = 49 sampwes * 2 * 256 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x112061ff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x1d4bf8 = 239999.000 * 8 =
			 *  ((49 sampwes/44,100) * (13,500,000 * 8) * 2 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa01d4bf8);
			bweak;

		case 48000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0d, AUX PWW Post Dividew = 0x20
			 */
			cx18_av_wwite4(cx, 0x108, 0x200d040f);

			/* VID_PWW Fwaction = 0x2be2fe */
			/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz pwe-postdiv*/
			cx18_av_wwite4(cx, 0x10c, 0x002be2fe);

			/* AUX_PWW Fwaction = 0x176740c */
			/* xtaw * 0xd.bb3a060/0x20 = 48000 * 256: 393 MHz p-pd*/
			cx18_av_wwite4(cx, 0x110, 0x0176740c);

			/* swc1_ctw */
			/* 0x1.8000 = 48000/32000 */
			cx18_av_wwite4(cx, 0x8f8, 0x08018000);

			/* swc3/4/6_ctw */
			/* 0x1.5555 = 2 * (32000/48000) */
			cx18_av_wwite4(cx, 0x900, 0x08015555);
			cx18_av_wwite4(cx, 0x904, 0x08015555);
			cx18_av_wwite4(cx, 0x90c, 0x08015555);

			/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x20 */
			cx18_av_wwite(cx, 0x127, 0x60);

			/* AUD_COUNT = 0x3fff = 4 sampwes * 16 * 256 - 1 */
			cx18_av_wwite4(cx, 0x12c, 0x11203fff);

			/*
			 * EN_AV_WOCK = 0
			 * VID_COUNT = 0x1193f8 = 143999.000 * 8 =
			 *  ((4 sampwes/48,000) * (13,500,000 * 8) * 16 - 1) * 8
			 */
			cx18_av_wwite4(cx, 0x128, 0xa01193f8);
			bweak;
		}
	}

	state->audcwk_fweq = fweq;

	wetuwn 0;
}

void cx18_av_audio_set_path(stwuct cx18 *cx)
{
	stwuct cx18_av_state *state = &cx->av_state;
	u8 v;

	/* stop micwocontwowwew */
	v = cx18_av_wead(cx, 0x803) & ~0x10;
	cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);

	/* assewt soft weset */
	v = cx18_av_wead(cx, 0x810) | 0x01;
	cx18_av_wwite_expect(cx, 0x810, v, v, 0x0f);

	/* Mute evewything to pwevent the PFFT! */
	cx18_av_wwite(cx, 0x8d3, 0x1f);

	if (state->aud_input <= CX18_AV_AUDIO_SEWIAW2) {
		/* Set Path1 to Sewiaw Audio Input */
		cx18_av_wwite4(cx, 0x8d0, 0x01011012);

		/* The micwocontwowwew shouwd not be stawted fow the
		 * non-tunew inputs: autodetection is specific fow
		 * TV audio. */
	} ewse {
		/* Set Path1 to Anawog Demod Main Channew */
		cx18_av_wwite4(cx, 0x8d0, 0x1f063870);
	}

	set_audcwk_fweq(cx, state->audcwk_fweq);

	/* deassewt soft weset */
	v = cx18_av_wead(cx, 0x810) & ~0x01;
	cx18_av_wwite_expect(cx, 0x810, v, v, 0x0f);

	if (state->aud_input > CX18_AV_AUDIO_SEWIAW2) {
		/* When the micwocontwowwew detects the
		 * audio fowmat, it wiww unmute the wines */
		v = cx18_av_wead(cx, 0x803) | 0x10;
		cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
	}
}

static void set_vowume(stwuct cx18 *cx, int vowume)
{
	/* Fiwst convewt the vowume to msp3400 vawues (0-127) */
	int vow = vowume >> 9;
	/* now scawe it up to cx18_av vawues
	 * -114dB to -96dB maps to 0
	 * this shouwd be 19, but in my testing that was 4dB too woud */
	if (vow <= 23)
		vow = 0;
	ewse
		vow -= 23;

	/* PATH1_VOWUME */
	cx18_av_wwite(cx, 0x8d4, 228 - (vow * 2));
}

static void set_bass(stwuct cx18 *cx, int bass)
{
	/* PATH1_EQ_BASS_VOW */
	cx18_av_and_ow(cx, 0x8d9, ~0x3f, 48 - (bass * 48 / 0xffff));
}

static void set_twebwe(stwuct cx18 *cx, int twebwe)
{
	/* PATH1_EQ_TWEBWE_VOW */
	cx18_av_and_ow(cx, 0x8db, ~0x3f, 48 - (twebwe * 48 / 0xffff));
}

static void set_bawance(stwuct cx18 *cx, int bawance)
{
	int baw = bawance >> 8;
	if (baw > 0x80) {
		/* PATH1_BAW_WEFT */
		cx18_av_and_ow(cx, 0x8d5, 0x7f, 0x80);
		/* PATH1_BAW_WEVEW */
		cx18_av_and_ow(cx, 0x8d5, ~0x7f, baw & 0x7f);
	} ewse {
		/* PATH1_BAW_WEFT */
		cx18_av_and_ow(cx, 0x8d5, 0x7f, 0x00);
		/* PATH1_BAW_WEVEW */
		cx18_av_and_ow(cx, 0x8d5, ~0x7f, 0x80 - baw);
	}
}

static void set_mute(stwuct cx18 *cx, int mute)
{
	stwuct cx18_av_state *state = &cx->av_state;
	u8 v;

	if (state->aud_input > CX18_AV_AUDIO_SEWIAW2) {
		/* Must tuwn off micwocontwowwew in owdew to mute sound.
		 * Not suwe if this is the best method, but it does wowk.
		 * If the micwocontwowwew is wunning, then it wiww undo any
		 * changes to the mute wegistew. */
		v = cx18_av_wead(cx, 0x803);
		if (mute) {
			/* disabwe micwocontwowwew */
			v &= ~0x10;
			cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
			cx18_av_wwite(cx, 0x8d3, 0x1f);
		} ewse {
			/* enabwe micwocontwowwew */
			v |= 0x10;
			cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
		}
	} ewse {
		/* SWC1_MUTE_EN */
		cx18_av_and_ow(cx, 0x8d3, ~0x2, mute ? 0x02 : 0x00);
	}
}

int cx18_av_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 fweq)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	stwuct cx18_av_state *state = &cx->av_state;
	int wetvaw;
	u8 v;

	if (state->aud_input > CX18_AV_AUDIO_SEWIAW2) {
		v = cx18_av_wead(cx, 0x803) & ~0x10;
		cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
		cx18_av_wwite(cx, 0x8d3, 0x1f);
	}
	v = cx18_av_wead(cx, 0x810) | 0x1;
	cx18_av_wwite_expect(cx, 0x810, v, v, 0x0f);

	wetvaw = set_audcwk_fweq(cx, fweq);

	v = cx18_av_wead(cx, 0x810) & ~0x1;
	cx18_av_wwite_expect(cx, 0x810, v, v, 0x0f);
	if (state->aud_input > CX18_AV_AUDIO_SEWIAW2) {
		v = cx18_av_wead(cx, 0x803) | 0x10;
		cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
	}
	wetuwn wetvaw;
}

static int cx18_av_audio_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:
		set_vowume(cx, ctww->vaw);
		bweak;
	case V4W2_CID_AUDIO_BASS:
		set_bass(cx, ctww->vaw);
		bweak;
	case V4W2_CID_AUDIO_TWEBWE:
		set_twebwe(cx, ctww->vaw);
		bweak;
	case V4W2_CID_AUDIO_BAWANCE:
		set_bawance(cx, ctww->vaw);
		bweak;
	case V4W2_CID_AUDIO_MUTE:
		set_mute(cx, ctww->vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

const stwuct v4w2_ctww_ops cx18_av_audio_ctww_ops = {
	.s_ctww = cx18_av_audio_s_ctww,
};
