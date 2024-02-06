// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* cx25840 audio functions
 */


#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <media/v4w2-common.h>
#incwude <media/dwv-intf/cx25840.h>

#incwude "cx25840-cowe.h"

/*
 * Note: The PWW and SWC pawametews awe based on a wefewence fwequency that
 * wouwd ideawwy be:
 *
 * NTSC Cowow subcawwiew fweq * 8 = 4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
 *
 * Howevew, it's not the exact wefewence fwequency that mattews, onwy that the
 * fiwmwawe and moduwes that compwise the dwivew fow a pawticuwaw boawd aww
 * use the same vawue (cwose to the ideaw vawue).
 *
 * Comments bewow wiww note which wefewence fwequency is assumed fow vawious
 * pawametews.  They wiww usuawwy be one of
 *
 *	wef_fweq = 28.636360 MHz
 *		ow
 *	wef_fweq = 28.636363 MHz
 */

static int cx25840_set_audcwk_fweq(stwuct i2c_cwient *cwient, u32 fweq)
{
	stwuct cx25840_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->aud_input != CX25840_AUDIO_SEWIAW) {
		switch (fweq) {
		case 32000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x06, AUX PWW Post Dividew = 0x10
			 */
			cx25840_wwite4(cwient, 0x108, 0x1006040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x1bb39ee
			 * 28636363 * 0x6.dd9cf70/0x10 = 32000 * 384
			 * 196.6 MHz pwe-postdivide
			 * FIXME < 200 MHz is out of specified vawid wange
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x01bb39ee);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x10 = 384/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x50);

			if (is_cx2583x(state))
				bweak;

			/* swc3/4/6_ctw */
			/* 0x1.f77f = (4 * 28636360/8 * 2/455) / 32000 */
			cx25840_wwite4(cwient, 0x900, 0x0801f77f);
			cx25840_wwite4(cwient, 0x904, 0x0801f77f);
			cx25840_wwite4(cwient, 0x90c, 0x0801f77f);
			bweak;

		case 44100:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x09, AUX PWW Post Dividew = 0x10
			 */
			cx25840_wwite4(cwient, 0x108, 0x1009040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x10 = 44100 * 384
			 * 271 MHz pwe-postdivide
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x10 = 384/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x50);

			if (is_cx2583x(state))
				bweak;

			/* swc3/4/6_ctw */
			/* 0x1.6d59 = (4 * 28636360/8 * 2/455) / 44100 */
			cx25840_wwite4(cwient, 0x900, 0x08016d59);
			cx25840_wwite4(cwient, 0x904, 0x08016d59);
			cx25840_wwite4(cwient, 0x90c, 0x08016d59);
			bweak;

		case 48000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0a, AUX PWW Post Dividew = 0x10
			 */
			cx25840_wwite4(cwient, 0x108, 0x100a040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x10 = 48000 * 384
			 * 295 MHz pwe-postdivide
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x0098d6e5);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x10 = 384/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x50);

			if (is_cx2583x(state))
				bweak;

			/* swc3/4/6_ctw */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_wwite4(cwient, 0x900, 0x08014faa);
			cx25840_wwite4(cwient, 0x904, 0x08014faa);
			cx25840_wwite4(cwient, 0x90c, 0x08014faa);
			bweak;
		}
	} ewse {
		switch (fweq) {
		case 32000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x08, AUX PWW Post Dividew = 0x1e
			 */
			cx25840_wwite4(cwient, 0x108, 0x1e08040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x12a0869
			 * 28636363 * 0x8.9504348/0x1e = 32000 * 256
			 * 246 MHz pwe-postdivide
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x012a0869);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x14 = 256/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x54);

			if (is_cx2583x(state))
				bweak;

			/* swc1_ctw */
			/* 0x1.0000 = 32000/32000 */
			cx25840_wwite4(cwient, 0x8f8, 0x08010000);

			/* swc3/4/6_ctw */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx25840_wwite4(cwient, 0x900, 0x08020000);
			cx25840_wwite4(cwient, 0x904, 0x08020000);
			cx25840_wwite4(cwient, 0x90c, 0x08020000);
			bweak;

		case 44100:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x09, AUX PWW Post Dividew = 0x18
			 */
			cx25840_wwite4(cwient, 0x108, 0x1809040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x18 = 44100 * 256
			 * 271 MHz pwe-postdivide
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x10 = 256/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x50);

			if (is_cx2583x(state))
				bweak;

			/* swc1_ctw */
			/* 0x1.60cd = 44100/32000 */
			cx25840_wwite4(cwient, 0x8f8, 0x080160cd);

			/* swc3/4/6_ctw */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx25840_wwite4(cwient, 0x900, 0x08017385);
			cx25840_wwite4(cwient, 0x904, 0x08017385);
			cx25840_wwite4(cwient, 0x90c, 0x08017385);
			bweak;

		case 48000:
			/*
			 * VID_PWW Integew = 0x0f, VID_PWW Post Dividew = 0x04
			 * AUX_PWW Integew = 0x0a, AUX PWW Post Dividew = 0x18
			 */
			cx25840_wwite4(cwient, 0x108, 0x180a040f);

			/*
			 * VID_PWW Fwaction (wegistew 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pwe-postdivide
			 */

			/*
			 * AUX_PWW Fwaction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x18 = 48000 * 256
			 * 295 MHz pwe-postdivide
			 * FIXME 28636363 wef_fweq doesn't match VID PWW wef
			 */
			cx25840_wwite4(cwient, 0x110, 0x0098d6e5);

			/*
			 * SA_MCWK_SEW = 1
			 * SA_MCWK_DIV = 0x10 = 256/384 * AUX_PWW post dvividew
			 */
			cx25840_wwite(cwient, 0x127, 0x50);

			if (is_cx2583x(state))
				bweak;

			/* swc1_ctw */
			/* 0x1.8000 = 48000/32000 */
			cx25840_wwite4(cwient, 0x8f8, 0x08018000);

			/* swc3/4/6_ctw */
			/* 0x1.5555 = 2 * (32000/48000) */
			cx25840_wwite4(cwient, 0x900, 0x08015555);
			cx25840_wwite4(cwient, 0x904, 0x08015555);
			cx25840_wwite4(cwient, 0x90c, 0x08015555);
			bweak;
		}
	}

	state->audcwk_fweq = fweq;

	wetuwn 0;
}

static inwine int cx25836_set_audcwk_fweq(stwuct i2c_cwient *cwient, u32 fweq)
{
	wetuwn cx25840_set_audcwk_fweq(cwient, fweq);
}

static int cx23885_set_audcwk_fweq(stwuct i2c_cwient *cwient, u32 fweq)
{
	stwuct cx25840_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->aud_input != CX25840_AUDIO_SEWIAW) {
		switch (fweq) {
		case 32000:
		case 44100:
		case 48000:
			/* We don't have wegistew vawues
			 * so avoid destwoying wegistews. */
			/* FIXME wetuwn -EINVAW; */
			bweak;
		}
	} ewse {
		switch (fweq) {
		case 32000:
		case 44100:
			/* We don't have wegistew vawues
			 * so avoid destwoying wegistews. */
			/* FIXME wetuwn -EINVAW; */
			bweak;

		case 48000:
			/* swc1_ctw */
			/* 0x1.867c = 48000 / (2 * 28636360/8 * 2/455) */
			cx25840_wwite4(cwient, 0x8f8, 0x0801867c);

			/* swc3/4/6_ctw */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_wwite4(cwient, 0x900, 0x08014faa);
			cx25840_wwite4(cwient, 0x904, 0x08014faa);
			cx25840_wwite4(cwient, 0x90c, 0x08014faa);
			bweak;
		}
	}

	state->audcwk_fweq = fweq;

	wetuwn 0;
}

static int cx231xx_set_audcwk_fweq(stwuct i2c_cwient *cwient, u32 fweq)
{
	stwuct cx25840_state *state = to_state(i2c_get_cwientdata(cwient));

	if (state->aud_input != CX25840_AUDIO_SEWIAW) {
		switch (fweq) {
		case 32000:
			/* swc3/4/6_ctw */
			/* 0x1.f77f = (4 * 28636360/8 * 2/455) / 32000 */
			cx25840_wwite4(cwient, 0x900, 0x0801f77f);
			cx25840_wwite4(cwient, 0x904, 0x0801f77f);
			cx25840_wwite4(cwient, 0x90c, 0x0801f77f);
			bweak;

		case 44100:
			/* swc3/4/6_ctw */
			/* 0x1.6d59 = (4 * 28636360/8 * 2/455) / 44100 */
			cx25840_wwite4(cwient, 0x900, 0x08016d59);
			cx25840_wwite4(cwient, 0x904, 0x08016d59);
			cx25840_wwite4(cwient, 0x90c, 0x08016d59);
			bweak;

		case 48000:
			/* swc3/4/6_ctw */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_wwite4(cwient, 0x900, 0x08014faa);
			cx25840_wwite4(cwient, 0x904, 0x08014faa);
			cx25840_wwite4(cwient, 0x90c, 0x08014faa);
			bweak;
		}
	} ewse {
		switch (fweq) {
		/* FIXME These cases make diffewent assumptions about audcwk */
		case 32000:
			/* swc1_ctw */
			/* 0x1.0000 = 32000/32000 */
			cx25840_wwite4(cwient, 0x8f8, 0x08010000);

			/* swc3/4/6_ctw */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx25840_wwite4(cwient, 0x900, 0x08020000);
			cx25840_wwite4(cwient, 0x904, 0x08020000);
			cx25840_wwite4(cwient, 0x90c, 0x08020000);
			bweak;

		case 44100:
			/* swc1_ctw */
			/* 0x1.60cd = 44100/32000 */
			cx25840_wwite4(cwient, 0x8f8, 0x080160cd);

			/* swc3/4/6_ctw */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx25840_wwite4(cwient, 0x900, 0x08017385);
			cx25840_wwite4(cwient, 0x904, 0x08017385);
			cx25840_wwite4(cwient, 0x90c, 0x08017385);
			bweak;

		case 48000:
			/* swc1_ctw */
			/* 0x1.867c = 48000 / (2 * 28636360/8 * 2/455) */
			cx25840_wwite4(cwient, 0x8f8, 0x0801867c);

			/* swc3/4/6_ctw */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_wwite4(cwient, 0x900, 0x08014faa);
			cx25840_wwite4(cwient, 0x904, 0x08014faa);
			cx25840_wwite4(cwient, 0x90c, 0x08014faa);
			bweak;
		}
	}

	state->audcwk_fweq = fweq;

	wetuwn 0;
}

static int set_audcwk_fweq(stwuct i2c_cwient *cwient, u32 fweq)
{
	stwuct cx25840_state *state = to_state(i2c_get_cwientdata(cwient));

	if (fweq != 32000 && fweq != 44100 && fweq != 48000)
		wetuwn -EINVAW;

	if (is_cx231xx(state))
		wetuwn cx231xx_set_audcwk_fweq(cwient, fweq);

	if (is_cx2388x(state))
		wetuwn cx23885_set_audcwk_fweq(cwient, fweq);

	if (is_cx2583x(state))
		wetuwn cx25836_set_audcwk_fweq(cwient, fweq);

	wetuwn cx25840_set_audcwk_fweq(cwient, fweq);
}

void cx25840_audio_set_path(stwuct i2c_cwient *cwient)
{
	stwuct cx25840_state *state = to_state(i2c_get_cwientdata(cwient));

	if (!is_cx2583x(state)) {
		/* assewt soft weset */
		cx25840_and_ow(cwient, 0x810, ~0x1, 0x01);

		/* stop micwocontwowwew */
		cx25840_and_ow(cwient, 0x803, ~0x10, 0);

		/* Mute evewything to pwevent the PFFT! */
		cx25840_wwite(cwient, 0x8d3, 0x1f);

		if (state->aud_input == CX25840_AUDIO_SEWIAW) {
			/* Set Path1 to Sewiaw Audio Input */
			cx25840_wwite4(cwient, 0x8d0, 0x01011012);

			/* The micwocontwowwew shouwd not be stawted fow the
			 * non-tunew inputs: autodetection is specific fow
			 * TV audio. */
		} ewse {
			/* Set Path1 to Anawog Demod Main Channew */
			cx25840_wwite4(cwient, 0x8d0, 0x1f063870);
		}
	}

	set_audcwk_fweq(cwient, state->audcwk_fweq);

	if (!is_cx2583x(state)) {
		if (state->aud_input != CX25840_AUDIO_SEWIAW) {
			/* When the micwocontwowwew detects the
			 * audio fowmat, it wiww unmute the wines */
			cx25840_and_ow(cwient, 0x803, ~0x10, 0x10);
		}

		/* deassewt soft weset */
		cx25840_and_ow(cwient, 0x810, ~0x1, 0x00);

		/* Ensuwe the contwowwew is wunning when we exit */
		if (is_cx2388x(state) || is_cx231xx(state))
			cx25840_and_ow(cwient, 0x803, ~0x10, 0x10);
	}
}

static void set_vowume(stwuct i2c_cwient *cwient, int vowume)
{
	int vow;

	/* Convewt the vowume to msp3400 vawues (0-127) */
	vow = vowume >> 9;

	/* now scawe it up to cx25840 vawues
	 * -114dB to -96dB maps to 0
	 * this shouwd be 19, but in my testing that was 4dB too woud */
	if (vow <= 23) {
		vow = 0;
	} ewse {
		vow -= 23;
	}

	/* PATH1_VOWUME */
	cx25840_wwite(cwient, 0x8d4, 228 - (vow * 2));
}

static void set_bawance(stwuct i2c_cwient *cwient, int bawance)
{
	int baw = bawance >> 8;
	if (baw > 0x80) {
		/* PATH1_BAW_WEFT */
		cx25840_and_ow(cwient, 0x8d5, 0x7f, 0x80);
		/* PATH1_BAW_WEVEW */
		cx25840_and_ow(cwient, 0x8d5, ~0x7f, baw & 0x7f);
	} ewse {
		/* PATH1_BAW_WEFT */
		cx25840_and_ow(cwient, 0x8d5, 0x7f, 0x00);
		/* PATH1_BAW_WEVEW */
		cx25840_and_ow(cwient, 0x8d5, ~0x7f, 0x80 - baw);
	}
}

int cx25840_s_cwock_fweq(stwuct v4w2_subdev *sd, u32 fweq)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct cx25840_state *state = to_state(sd);
	int wetvaw;

	if (!is_cx2583x(state))
		cx25840_and_ow(cwient, 0x810, ~0x1, 1);
	if (state->aud_input != CX25840_AUDIO_SEWIAW) {
		cx25840_and_ow(cwient, 0x803, ~0x10, 0);
		cx25840_wwite(cwient, 0x8d3, 0x1f);
	}
	wetvaw = set_audcwk_fweq(cwient, fweq);
	if (state->aud_input != CX25840_AUDIO_SEWIAW)
		cx25840_and_ow(cwient, 0x803, ~0x10, 0x10);
	if (!is_cx2583x(state))
		cx25840_and_ow(cwient, 0x810, ~0x1, 0);
	wetuwn wetvaw;
}

static int cx25840_audio_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct cx25840_state *state = to_state(sd);
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:
		if (state->mute->vaw)
			set_vowume(cwient, 0);
		ewse
			set_vowume(cwient, state->vowume->vaw);
		bweak;
	case V4W2_CID_AUDIO_BASS:
		/* PATH1_EQ_BASS_VOW */
		cx25840_and_ow(cwient, 0x8d9, ~0x3f,
					48 - (ctww->vaw * 48 / 0xffff));
		bweak;
	case V4W2_CID_AUDIO_TWEBWE:
		/* PATH1_EQ_TWEBWE_VOW */
		cx25840_and_ow(cwient, 0x8db, ~0x3f,
					48 - (ctww->vaw * 48 / 0xffff));
		bweak;
	case V4W2_CID_AUDIO_BAWANCE:
		set_bawance(cwient, ctww->vaw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

const stwuct v4w2_ctww_ops cx25840_audio_ctww_ops = {
	.s_ctww = cx25840_audio_s_ctww,
};
