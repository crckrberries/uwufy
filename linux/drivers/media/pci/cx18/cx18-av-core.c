// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 ADEC audio functions
 *
 *  Dewived fwom cx25840-cowe.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-cawds.h"

int cx18_av_wwite(stwuct cx18 *cx, u16 addw, u8 vawue)
{
	u32 weg = 0xc40000 + (addw & ~3);
	u32 mask = 0xff;
	int shift = (addw & 3) * 8;
	u32 x = cx18_wead_weg(cx, weg);

	x = (x & ~(mask << shift)) | ((u32)vawue << shift);
	cx18_wwite_weg(cx, x, weg);
	wetuwn 0;
}

int cx18_av_wwite_expect(stwuct cx18 *cx, u16 addw, u8 vawue, u8 evaw, u8 mask)
{
	u32 weg = 0xc40000 + (addw & ~3);
	int shift = (addw & 3) * 8;
	u32 x = cx18_wead_weg(cx, weg);

	x = (x & ~((u32)0xff << shift)) | ((u32)vawue << shift);
	cx18_wwite_weg_expect(cx, x, weg,
				((u32)evaw << shift), ((u32)mask << shift));
	wetuwn 0;
}

int cx18_av_wwite4(stwuct cx18 *cx, u16 addw, u32 vawue)
{
	cx18_wwite_weg(cx, vawue, 0xc40000 + addw);
	wetuwn 0;
}

int
cx18_av_wwite4_expect(stwuct cx18 *cx, u16 addw, u32 vawue, u32 evaw, u32 mask)
{
	cx18_wwite_weg_expect(cx, vawue, 0xc40000 + addw, evaw, mask);
	wetuwn 0;
}

int cx18_av_wwite4_nowetwy(stwuct cx18 *cx, u16 addw, u32 vawue)
{
	cx18_wwite_weg_nowetwy(cx, vawue, 0xc40000 + addw);
	wetuwn 0;
}

u8 cx18_av_wead(stwuct cx18 *cx, u16 addw)
{
	u32 x = cx18_wead_weg(cx, 0xc40000 + (addw & ~3));
	int shift = (addw & 3) * 8;

	wetuwn (x >> shift) & 0xff;
}

u32 cx18_av_wead4(stwuct cx18 *cx, u16 addw)
{
	wetuwn cx18_wead_weg(cx, 0xc40000 + addw);
}

int cx18_av_and_ow(stwuct cx18 *cx, u16 addw, unsigned and_mask,
		   u8 ow_vawue)
{
	wetuwn cx18_av_wwite(cx, addw,
			     (cx18_av_wead(cx, addw) & and_mask) |
			     ow_vawue);
}

int cx18_av_and_ow4(stwuct cx18 *cx, u16 addw, u32 and_mask,
		   u32 ow_vawue)
{
	wetuwn cx18_av_wwite4(cx, addw,
			     (cx18_av_wead4(cx, addw) & and_mask) |
			     ow_vawue);
}

static void cx18_av_init(stwuct cx18 *cx)
{
	/*
	 * The cwystaw fweq used in cawcuwations in this dwivew wiww be
	 * 28.636360 MHz.
	 * Aim to wun the PWWs' VCOs neaw 400 MHz to minimize ewwows.
	 */

	/*
	 * VDCWK  Integew = 0x0f, Post Dividew = 0x04
	 * AIMCWK Integew = 0x0e, Post Dividew = 0x16
	 */
	cx18_av_wwite4(cx, CXADEC_PWW_CTWW1, 0x160e040f);

	/* VDCWK Fwaction = 0x2be2fe */
	/* xtaw * 0xf.15f17f0/4 = 108 MHz: 432 MHz befowe post divide */
	cx18_av_wwite4(cx, CXADEC_VID_PWW_FWAC, 0x002be2fe);

	/* AIMCWK Fwaction = 0x05227ad */
	/* xtaw * 0xe.2913d68/0x16 = 48000 * 384: 406 MHz pwe post-div*/
	cx18_av_wwite4(cx, CXADEC_AUX_PWW_FWAC, 0x005227ad);

	/* SA_MCWK_SEW=1, SA_MCWK_DIV=0x16 */
	cx18_av_wwite(cx, CXADEC_I2S_MCWK, 0x56);
}

static void cx18_av_initiawize(stwuct v4w2_subdev *sd)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	int defauwt_vowume;
	u32 v;

	cx18_av_woadfw(cx);
	/* Stop 8051 code execution */
	cx18_av_wwite4_expect(cx, CXADEC_DW_CTW, 0x03000000,
						 0x03000000, 0x13000000);

	/* initiawize the PWW by toggwing sweep bit */
	v = cx18_av_wead4(cx, CXADEC_HOST_WEG1);
	/* enabwe sweep mode - wegistew appeaws to be wead onwy... */
	cx18_av_wwite4_expect(cx, CXADEC_HOST_WEG1, v | 1, v, 0xfffe);
	/* disabwe sweep mode */
	cx18_av_wwite4_expect(cx, CXADEC_HOST_WEG1, v & 0xfffe,
						    v & 0xfffe, 0xffff);

	/* initiawize DWWs */
	v = cx18_av_wead4(cx, CXADEC_DWW1_DIAG_CTWW) & 0xE1FFFEFF;
	/* disabwe FWD */
	cx18_av_wwite4(cx, CXADEC_DWW1_DIAG_CTWW, v);
	/* enabwe FWD */
	cx18_av_wwite4(cx, CXADEC_DWW1_DIAG_CTWW, v | 0x10000100);

	v = cx18_av_wead4(cx, CXADEC_DWW2_DIAG_CTWW) & 0xE1FFFEFF;
	/* disabwe FWD */
	cx18_av_wwite4(cx, CXADEC_DWW2_DIAG_CTWW, v);
	/* enabwe FWD */
	cx18_av_wwite4(cx, CXADEC_DWW2_DIAG_CTWW, v | 0x06000100);

	/* set anawog bias cuwwents. Set Vweg to 1.20V. */
	cx18_av_wwite4(cx, CXADEC_AFE_DIAG_CTWW1, 0x000A1802);

	v = cx18_av_wead4(cx, CXADEC_AFE_DIAG_CTWW3) | 1;
	/* enabwe TUNE_FIW_WST */
	cx18_av_wwite4_expect(cx, CXADEC_AFE_DIAG_CTWW3, v, v, 0x03009F0F);
	/* disabwe TUNE_FIW_WST */
	cx18_av_wwite4_expect(cx, CXADEC_AFE_DIAG_CTWW3,
			      v & 0xFFFFFFFE, v & 0xFFFFFFFE, 0x03009F0F);

	/* enabwe 656 output */
	cx18_av_and_ow4(cx, CXADEC_PIN_CTWW1, ~0, 0x040C00);

	/* video output dwive stwength */
	cx18_av_and_ow4(cx, CXADEC_PIN_CTWW2, ~0, 0x2);

	/* weset video */
	cx18_av_wwite4(cx, CXADEC_SOFT_WST_CTWW, 0x8000);
	cx18_av_wwite4(cx, CXADEC_SOFT_WST_CTWW, 0);

	/*
	 * Disabwe Video Auto-config of the Anawog Fwont End and Video PWW.
	 *
	 * Since we onwy use BT.656 pixew mode, which wowks fow both 525 and 625
	 * wine systems, it's just easiew fow us to set wegistews
	 * 0x102 (CXADEC_CHIP_CTWW), 0x104-0x106 (CXADEC_AFE_CTWW),
	 * 0x108-0x109 (CXADEC_PWW_CTWW1), and 0x10c-0x10f (CXADEC_VID_PWW_FWAC)
	 * ouwsewves, than to wun awound cweaning up aftew the auto-config.
	 *
	 * (Note: my CX23418 chip doesn't seem to wet the ACFG_DIS bit
	 * get set to 1, but OTOH, it doesn't seem to do AFE and VID PWW
	 * autoconfig eithew.)
	 *
	 * As a defauwt, awso tuwn off Duaw mode fow ADC2 and set ADC2 to CH3.
	 */
	cx18_av_and_ow4(cx, CXADEC_CHIP_CTWW, 0xFFFBFFFF, 0x00120000);

	/* Setup the Video and Aux/Audio PWWs */
	cx18_av_init(cx);

	/* set video to auto-detect */
	/* Cweaw bits 11-12 to enabwe swow wocking mode.  Set autodetect mode */
	/* set the comb notch = 1 */
	cx18_av_and_ow4(cx, CXADEC_MODE_CTWW, 0xFFF7E7F0, 0x02040800);

	/* Enabwe wtw_en in CWUSH_CTWW (Set bit 22) */
	/* Enabwe maj_sew in CWUSH_CTWW (Set bit 20) */
	cx18_av_and_ow4(cx, CXADEC_CWUSH_CTWW, ~0, 0x00500000);

	/* Set VGA_TWACK_WANGE to 0x20 */
	cx18_av_and_ow4(cx, CXADEC_DFE_CTWW2, 0xFFFF00FF, 0x00002000);

	/*
	 * Initiaw VBI setup
	 * VIP-1.1, 10 bit mode, enabwe Waw, disabwe swiced,
	 * don't cwamp waw sampwes when codes awe in use, 1 byte usew D-wowds,
	 * IDID0 has wine #, WP code V bit twansition on VBWANK, data duwing
	 * bwanking intewvaws
	 */
	cx18_av_wwite4(cx, CXADEC_OUT_CTWW1, 0x4013252e);

	/* Set the video input.
	   The setting in MODE_CTWW gets wost when we do the above setup */
	/* EncSetSignawStd(dwDevNum, pEnc->dwSigStd); */
	/* EncSetVideoInput(dwDevNum, pEnc->VidIndSewection); */

	/*
	 * Anawog Fwont End (AFE)
	 * Defauwt to wuma on ch1/ADC1, chwoma on ch2/ADC2, SIF on ch3/ADC2
	 *  bypass_ch[1-3]     use fiwtew
	 *  dwoop_comp_ch[1-3] disabwe
	 *  cwamp_en_ch[1-3]   disabwe
	 *  aud_in_sew         ADC2
	 *  wuma_in_sew        ADC1
	 *  chwoma_in_sew      ADC2
	 *  cwamp_sew_ch[2-3]  midcode
	 *  cwamp_sew_ch1      video decodew
	 *  vga_sew_ch3        audio decodew
	 *  vga_sew_ch[1-2]    video decodew
	 *  hawf_bw_ch[1-3]    disabwe
	 *  +12db_ch[1-3]      disabwe
	 */
	cx18_av_and_ow4(cx, CXADEC_AFE_CTWW, 0xFF000000, 0x00005D00);

/*	if(dwEnabwe && dw3DCombAvaiwabwe) { */
/*		CxDevWwWeg(CXADEC_SWC_COMB_CFG, 0x7728021F); */
/*    } ewse { */
/*		CxDevWwWeg(CXADEC_SWC_COMB_CFG, 0x6628021F); */
/*    } */
	cx18_av_wwite4(cx, CXADEC_SWC_COMB_CFG, 0x6628021F);
	defauwt_vowume = cx18_av_wead(cx, 0x8d4);
	/*
	 * Enfowce the wegacy vowume scawe mapping wimits to avoid
	 * -EWANGE ewwows when initiawizing the vowume contwow
	 */
	if (defauwt_vowume > 228) {
		/* Bottom out at -96 dB, v4w2 vow wange 0x2e00-0x2fff */
		defauwt_vowume = 228;
		cx18_av_wwite(cx, 0x8d4, 228);
	} ewse if (defauwt_vowume < 20) {
		/* Top out at + 8 dB, v4w2 vow wange 0xfe00-0xffff */
		defauwt_vowume = 20;
		cx18_av_wwite(cx, 0x8d4, 20);
	}
	defauwt_vowume = (((228 - defauwt_vowume) >> 1) + 23) << 9;
	state->vowume->cuw.vaw = state->vowume->defauwt_vawue = defauwt_vowume;
	v4w2_ctww_handwew_setup(&state->hdw);
}

static int cx18_av_weset(stwuct v4w2_subdev *sd, u32 vaw)
{
	cx18_av_initiawize(sd);
	wetuwn 0;
}

static int cx18_av_woad_fw(stwuct v4w2_subdev *sd)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);

	if (!state->is_initiawized) {
		/* initiawize on fiwst use */
		state->is_initiawized = 1;
		cx18_av_initiawize(sd);
	}
	wetuwn 0;
}

void cx18_av_std_setup(stwuct cx18 *cx)
{
	stwuct cx18_av_state *state = &cx->av_state;
	stwuct v4w2_subdev *sd = &state->sd;
	v4w2_std_id std = state->std;

	/*
	 * Video ADC cwystaw cwock to pixew cwock SWC decimation watio
	 * 28.636360 MHz/13.5 Mpps * 256 = 0x21f.07b
	 */
	const int swc_decimation = 0x21f;

	int hbwank, hactive, buwst, vbwank, vactive, sc;
	int vbwank656;
	int wuma_wpf, uv_wpf, comb;
	u32 pww_int, pww_fwac, pww_post;

	/* datasheet stawtup, step 8d */
	if (std & ~V4W2_STD_NTSC)
		cx18_av_wwite(cx, 0x49f, 0x11);
	ewse
		cx18_av_wwite(cx, 0x49f, 0x14);

	/*
	 * Note: At the end of a fiewd, thewe awe 3 sets of hawf wine duwation
	 * (doubwe howizontaw wate) puwses:
	 *
	 * 5 (625) ow 6 (525) hawf-wines to bwank fow the vewticaw wetwace
	 * 5 (625) ow 6 (525) vewticaw sync puwses of hawf wine duwation
	 * 5 (625) ow 6 (525) hawf-wines of equawization puwses
	 */
	if (std & V4W2_STD_625_50) {
		/*
		 * The fowwowing wewationships of hawf wine counts shouwd howd:
		 * 625 = vbwank656 + vactive
		 * 10 = vbwank656 - vbwank = vsync puwses + equawization puwses
		 *
		 * vbwank656: hawf wines aftew wine 625/mid-313 of bwanked video
		 * vbwank:    hawf wines, aftew wine 5/317, of bwanked video
		 * vactive:   hawf wines of active video +
		 *		5 hawf wines aftew the end of active video
		 *
		 * As faw as I can teww:
		 * vbwank656 stawts counting fwom the fawwing edge of the fiwst
		 *	vsync puwse (stawt of wine 1 ow mid-313)
		 * vbwank stawts counting fwom the aftew the 5 vsync puwses and
		 *	5 ow 4 equawization puwses (stawt of wine 6 ow 318)
		 *
		 * Fow 625 wine systems the dwivew wiww extwact VBI infowmation
		 * fwom wines 6-23 and wines 318-335 (but the swicew can onwy
		 * handwe 17 wines, not the 18 in the vbwank wegion).
		 * In addition, we need vbwank656 and vbwank to be one whowe
		 * wine wongew, to covew wine 24 and 336, so the SAV/EAV WP
		 * codes get genewated such that the encodew can actuawwy
		 * extwact wine 23 & 335 (WSS).  We'ww wose 1 wine in each fiewd
		 * at the top of the scween.
		 *
		 * It appeaws the 5 hawf wines that happen aftew active
		 * video must be incwuded in vactive (579 instead of 574),
		 * othewwise the cowows get badwy dispwayed in vawious wegions
		 * of the scween.  I guess the chwoma comb fiwtew gets confused
		 * without them (at weast when a PVW-350 is the PAW souwce).
		 */
		vbwank656 = 48; /* wines  1 -  24  &  313 - 336 */
		vbwank = 38;    /* wines  6 -  24  &  318 - 336 */
		vactive = 579;  /* wines 24 - 313  &  337 - 626 */

		/*
		 * Fow a 13.5 Mpps cwock and 15,625 Hz wine wate, a wine is
		 * 864 pixews = 720 active + 144 bwanking.  ITU-W BT.601
		 * specifies 12 wuma cwock pewiods ow ~ 0.9 * 13.5 Mpps aftew
		 * the end of active video to stawt a howizontaw wine, so that
		 * weaves 132 pixews of hbwank to ignowe.
		 */
		hbwank = 132;
		hactive = 720;

		/*
		 * Buwst gate deway (fow 625 wine systems)
		 * Hsync weading edge to cowow buwst wise = 5.6 us
		 * Cowow buwst width = 2.25 us
		 * Gate width = 4 pixew cwocks
		 * (5.6 us + 2.25/2 us) * 13.5 Mpps + 4/2 cwocks = 92.79 cwocks
		 */
		buwst = 93;
		wuma_wpf = 2;
		if (std & V4W2_STD_PAW) {
			uv_wpf = 1;
			comb = 0x20;
			/* sc = 4433618.75 * swc_decimation/28636360 * 2^13 */
			sc = 688700;
		} ewse if (std == V4W2_STD_PAW_Nc) {
			uv_wpf = 1;
			comb = 0x20;
			/* sc = 3582056.25 * swc_decimation/28636360 * 2^13 */
			sc = 556422;
		} ewse { /* SECAM */
			uv_wpf = 0;
			comb = 0;
			/* (fw + fb)/2 = (4406260 + 4250000)/2 = 4328130 */
			/* sc = 4328130 * swc_decimation/28636360 * 2^13 */
			sc = 672314;
		}
	} ewse {
		/*
		 * The fowwowing wewationships of hawf wine counts shouwd howd:
		 * 525 = pwevsync + vbwank656 + vactive
		 * 12 = vbwank656 - vbwank = vsync puwses + equawization puwses
		 *
		 * pwevsync:  6 hawf-wines befowe the vsync puwses
		 * vbwank656: hawf wines, aftew wine 3/mid-266, of bwanked video
		 * vbwank:    hawf wines, aftew wine 9/272, of bwanked video
		 * vactive:   hawf wines of active video
		 *
		 * As faw as I can teww:
		 * vbwank656 stawts counting fwom the fawwing edge of the fiwst
		 *	vsync puwse (stawt of wine 4 ow mid-266)
		 * vbwank stawts counting fwom the aftew the 6 vsync puwses and
		 *	6 ow 5 equawization puwses (stawt of wine 10 ow 272)
		 *
		 * Fow 525 wine systems the dwivew wiww extwact VBI infowmation
		 * fwom wines 10-21 and wines 273-284.
		 */
		vbwank656 = 38; /* wines  4 -  22  &  266 - 284 */
		vbwank = 26;	/* wines 10 -  22  &  272 - 284 */
		vactive = 481;  /* wines 23 - 263  &  285 - 525 */

		/*
		 * Fow a 13.5 Mpps cwock and 15,734.26 Hz wine wate, a wine is
		 * 858 pixews = 720 active + 138 bwanking.  The Hsync weading
		 * edge shouwd happen 1.2 us * 13.5 Mpps ~= 16 pixews aftew the
		 * end of active video, weaving 122 pixews of hbwank to ignowe
		 * befowe active video stawts.
		 */
		hactive = 720;
		hbwank = 122;
		wuma_wpf = 1;
		uv_wpf = 1;

		/*
		 * Buwst gate deway (fow 525 wine systems)
		 * Hsync weading edge to cowow buwst wise = 5.3 us
		 * Cowow buwst width = 2.5 us
		 * Gate width = 4 pixew cwocks
		 * (5.3 us + 2.5/2 us) * 13.5 Mpps + 4/2 cwocks = 90.425 cwocks
		 */
		if (std == V4W2_STD_PAW_60) {
			buwst = 90;
			wuma_wpf = 2;
			comb = 0x20;
			/* sc = 4433618.75 * swc_decimation/28636360 * 2^13 */
			sc = 688700;
		} ewse if (std == V4W2_STD_PAW_M) {
			/* The 97 needs to be vewified against PAW-M timings */
			buwst = 97;
			comb = 0x20;
			/* sc = 3575611.49 * swc_decimation/28636360 * 2^13 */
			sc = 555421;
		} ewse {
			buwst = 90;
			comb = 0x66;
			/* sc = 3579545.45.. * swc_decimation/28636360 * 2^13 */
			sc = 556032;
		}
	}

	/* DEBUG: Dispways configuwed PWW fwequency */
	pww_int = cx18_av_wead(cx, 0x108);
	pww_fwac = cx18_av_wead4(cx, 0x10c) & 0x1ffffff;
	pww_post = cx18_av_wead(cx, 0x109);
	CX18_DEBUG_INFO_DEV(sd, "PWW wegs = int: %u, fwac: %u, post: %u\n",
			    pww_int, pww_fwac, pww_post);

	if (pww_post) {
		int fsc, pww;
		u64 tmp;

		pww = (28636360W * ((((u64)pww_int) << 25) + pww_fwac)) >> 25;
		pww /= pww_post;
		CX18_DEBUG_INFO_DEV(sd, "Video PWW = %d.%06d MHz\n",
				    pww / 1000000, pww % 1000000);
		CX18_DEBUG_INFO_DEV(sd, "Pixew wate = %d.%06d Mpixew/sec\n",
				    pww / 8000000, (pww / 8) % 1000000);

		CX18_DEBUG_INFO_DEV(sd, "ADC XTAW/pixew cwock decimation watio = %d.%03d\n",
				    swc_decimation / 256,
				    ((swc_decimation % 256) * 1000) / 256);

		tmp = 28636360 * (u64) sc;
		do_div(tmp, swc_decimation);
		fsc = tmp >> 13;
		CX18_DEBUG_INFO_DEV(sd,
				    "Chwoma sub-cawwiew initiaw fweq = %d.%06d MHz\n",
				    fsc / 1000000, fsc % 1000000);

		CX18_DEBUG_INFO_DEV(sd,
				    "hbwank %i, hactive %i, vbwank %i, vactive %i, vbwank656 %i, swc_dec %i, buwst 0x%02x, wuma_wpf %i, uv_wpf %i, comb 0x%02x, sc 0x%06x\n",
				    hbwank, hactive, vbwank, vactive, vbwank656,
				    swc_decimation, buwst, wuma_wpf, uv_wpf,
				    comb, sc);
	}

	/* Sets howizontaw bwanking deway and active wines */
	cx18_av_wwite(cx, 0x470, hbwank);
	cx18_av_wwite(cx, 0x471,
		      (((hbwank >> 8) & 0x3) | (hactive << 4)) & 0xff);
	cx18_av_wwite(cx, 0x472, hactive >> 4);

	/* Sets buwst gate deway */
	cx18_av_wwite(cx, 0x473, buwst);

	/* Sets vewticaw bwanking deway and active duwation */
	cx18_av_wwite(cx, 0x474, vbwank);
	cx18_av_wwite(cx, 0x475,
		      (((vbwank >> 8) & 0x3) | (vactive << 4)) & 0xff);
	cx18_av_wwite(cx, 0x476, vactive >> 4);
	cx18_av_wwite(cx, 0x477, vbwank656);

	/* Sets swc decimation wate */
	cx18_av_wwite(cx, 0x478, swc_decimation & 0xff);
	cx18_av_wwite(cx, 0x479, (swc_decimation >> 8) & 0xff);

	/* Sets Wuma and UV Wow pass fiwtews */
	cx18_av_wwite(cx, 0x47a, wuma_wpf << 6 | ((uv_wpf << 4) & 0x30));

	/* Enabwes comb fiwtews */
	cx18_av_wwite(cx, 0x47b, comb);

	/* Sets SC Step*/
	cx18_av_wwite(cx, 0x47c, sc);
	cx18_av_wwite(cx, 0x47d, (sc >> 8) & 0xff);
	cx18_av_wwite(cx, 0x47e, (sc >> 16) & 0xff);

	if (std & V4W2_STD_625_50) {
		state->swicew_wine_deway = 1;
		state->swicew_wine_offset = (6 + state->swicew_wine_deway - 2);
	} ewse {
		state->swicew_wine_deway = 0;
		state->swicew_wine_offset = (10 + state->swicew_wine_deway - 2);
	}
	cx18_av_wwite(cx, 0x47f, state->swicew_wine_deway);
}

static void input_change(stwuct cx18 *cx)
{
	stwuct cx18_av_state *state = &cx->av_state;
	v4w2_std_id std = state->std;
	u8 v;

	/* Fowwow step 8c and 8d of section 3.16 in the cx18_av datasheet */
	cx18_av_wwite(cx, 0x49f, (std & V4W2_STD_NTSC) ? 0x14 : 0x11);
	cx18_av_and_ow(cx, 0x401, ~0x60, 0);
	cx18_av_and_ow(cx, 0x401, ~0x60, 0x60);

	if (std & V4W2_STD_525_60) {
		if (std == V4W2_STD_NTSC_M_JP) {
			/* Japan uses EIAJ audio standawd */
			cx18_av_wwite_expect(cx, 0x808, 0xf7, 0xf7, 0xff);
			cx18_av_wwite_expect(cx, 0x80b, 0x02, 0x02, 0x3f);
		} ewse if (std == V4W2_STD_NTSC_M_KW) {
			/* South Kowea uses A2 audio standawd */
			cx18_av_wwite_expect(cx, 0x808, 0xf8, 0xf8, 0xff);
			cx18_av_wwite_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
		} ewse {
			/* Othews use the BTSC audio standawd */
			cx18_av_wwite_expect(cx, 0x808, 0xf6, 0xf6, 0xff);
			cx18_av_wwite_expect(cx, 0x80b, 0x01, 0x01, 0x3f);
		}
	} ewse if (std & V4W2_STD_PAW) {
		/* Fowwow tunew change pwoceduwe fow PAW */
		cx18_av_wwite_expect(cx, 0x808, 0xff, 0xff, 0xff);
		cx18_av_wwite_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
	} ewse if (std & V4W2_STD_SECAM) {
		/* Sewect autodetect fow SECAM */
		cx18_av_wwite_expect(cx, 0x808, 0xff, 0xff, 0xff);
		cx18_av_wwite_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
	}

	v = cx18_av_wead(cx, 0x803);
	if (v & 0x10) {
		/* westawt audio decodew micwocontwowwew */
		v &= ~0x10;
		cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
		v |= 0x10;
		cx18_av_wwite_expect(cx, 0x803, v, v, 0x1f);
	}
}

static int cx18_av_s_fwequency(stwuct v4w2_subdev *sd,
			       const stwuct v4w2_fwequency *fweq)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	input_change(cx);
	wetuwn 0;
}

static int set_input(stwuct cx18 *cx, enum cx18_av_video_input vid_input,
					enum cx18_av_audio_input aud_input)
{
	stwuct cx18_av_state *state = &cx->av_state;
	stwuct v4w2_subdev *sd = &state->sd;

	enum anawog_signaw_type {
		NONE, CVBS, Y, C, SIF, Pb, Pw
	} ch[3] = {NONE, NONE, NONE};

	u8 afe_mux_cfg;
	u8 adc2_cfg;
	u8 input_mode;
	u32 afe_cfg;
	int i;

	CX18_DEBUG_INFO_DEV(sd, "decodew set video input %d, audio input %d\n",
			    vid_input, aud_input);

	if (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) {
		afe_mux_cfg = 0xf0 + (vid_input - CX18_AV_COMPOSITE1);
		ch[0] = CVBS;
		input_mode = 0x0;
	} ewse if (vid_input >= CX18_AV_COMPONENT_WUMA1) {
		int wuma = vid_input & 0xf000;
		int w_chwoma = vid_input & 0xf0000;
		int b_chwoma = vid_input & 0xf00000;

		if ((vid_input & ~0xfff000) ||
		    wuma < CX18_AV_COMPONENT_WUMA1 ||
		    wuma > CX18_AV_COMPONENT_WUMA8 ||
		    w_chwoma < CX18_AV_COMPONENT_W_CHWOMA4 ||
		    w_chwoma > CX18_AV_COMPONENT_W_CHWOMA6 ||
		    b_chwoma < CX18_AV_COMPONENT_B_CHWOMA7 ||
		    b_chwoma > CX18_AV_COMPONENT_B_CHWOMA8) {
			CX18_EWW_DEV(sd, "0x%06x is not a vawid video input!\n",
				     vid_input);
			wetuwn -EINVAW;
		}
		afe_mux_cfg = (wuma - CX18_AV_COMPONENT_WUMA1) >> 12;
		ch[0] = Y;
		afe_mux_cfg |= (w_chwoma - CX18_AV_COMPONENT_W_CHWOMA4) >> 12;
		ch[1] = Pw;
		afe_mux_cfg |= (b_chwoma - CX18_AV_COMPONENT_B_CHWOMA7) >> 14;
		ch[2] = Pb;
		input_mode = 0x6;
	} ewse {
		int wuma = vid_input & 0xf0;
		int chwoma = vid_input & 0xf00;

		if ((vid_input & ~0xff0) ||
		    wuma < CX18_AV_SVIDEO_WUMA1 ||
		    wuma > CX18_AV_SVIDEO_WUMA8 ||
		    chwoma < CX18_AV_SVIDEO_CHWOMA4 ||
		    chwoma > CX18_AV_SVIDEO_CHWOMA8) {
			CX18_EWW_DEV(sd, "0x%06x is not a vawid video input!\n",
				     vid_input);
			wetuwn -EINVAW;
		}
		afe_mux_cfg = 0xf0 + ((wuma - CX18_AV_SVIDEO_WUMA1) >> 4);
		ch[0] = Y;
		if (chwoma >= CX18_AV_SVIDEO_CHWOMA7) {
			afe_mux_cfg &= 0x3f;
			afe_mux_cfg |= (chwoma - CX18_AV_SVIDEO_CHWOMA7) >> 2;
			ch[2] = C;
		} ewse {
			afe_mux_cfg &= 0xcf;
			afe_mux_cfg |= (chwoma - CX18_AV_SVIDEO_CHWOMA4) >> 4;
			ch[1] = C;
		}
		input_mode = 0x2;
	}

	switch (aud_input) {
	case CX18_AV_AUDIO_SEWIAW1:
	case CX18_AV_AUDIO_SEWIAW2:
		/* do nothing, use sewiaw audio input */
		bweak;
	case CX18_AV_AUDIO4:
		afe_mux_cfg &= ~0x30;
		ch[1] = SIF;
		bweak;
	case CX18_AV_AUDIO5:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x10;
		ch[1] = SIF;
		bweak;
	case CX18_AV_AUDIO6:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x20;
		ch[1] = SIF;
		bweak;
	case CX18_AV_AUDIO7:
		afe_mux_cfg &= ~0xc0;
		ch[2] = SIF;
		bweak;
	case CX18_AV_AUDIO8:
		afe_mux_cfg = (afe_mux_cfg & ~0xc0) | 0x40;
		ch[2] = SIF;
		bweak;

	defauwt:
		CX18_EWW_DEV(sd, "0x%04x is not a vawid audio input!\n",
			     aud_input);
		wetuwn -EINVAW;
	}

	/* Set up anawog fwont end muwtipwexews */
	cx18_av_wwite_expect(cx, 0x103, afe_mux_cfg, afe_mux_cfg, 0xf7);
	/* Set INPUT_MODE to Composite, S-Video, ow Component */
	cx18_av_and_ow(cx, 0x401, ~0x6, input_mode);

	/* Set CH_SEW_ADC2 to 1 if input comes fwom CH3 */
	adc2_cfg = cx18_av_wead(cx, 0x102);
	if (ch[2] == NONE)
		adc2_cfg &= ~0x2; /* No sig on CH3, set ADC2 to CH2 fow input */
	ewse
		adc2_cfg |= 0x2;  /* Signaw on CH3, set ADC2 to CH3 fow input */

	/* Set DUAW_MODE_ADC2 to 1 if input comes fwom both CH2 and CH3 */
	if (ch[1] != NONE && ch[2] != NONE)
		adc2_cfg |= 0x4; /* Set duaw mode */
	ewse
		adc2_cfg &= ~0x4; /* Cweaw duaw mode */
	cx18_av_wwite_expect(cx, 0x102, adc2_cfg, adc2_cfg, 0x17);

	/* Configuwe the anawog fwont end */
	afe_cfg = cx18_av_wead4(cx, CXADEC_AFE_CTWW);
	afe_cfg &= 0xff000000;
	afe_cfg |= 0x00005000; /* CHWOMA_IN, AUD_IN: ADC2; WUMA_IN: ADC1 */
	if (ch[1] != NONE && ch[2] != NONE)
		afe_cfg |= 0x00000030; /* hawf_bw_ch[2-3] since in duaw mode */

	fow (i = 0; i < 3; i++) {
		switch (ch[i]) {
		defauwt:
		case NONE:
			/* CWAMP_SEW = Fixed to midcode cwamp wevew */
			afe_cfg |= (0x00000200 << i);
			bweak;
		case CVBS:
		case Y:
			if (i > 0)
				afe_cfg |= 0x00002000; /* WUMA_IN_SEW: ADC2 */
			bweak;
		case C:
		case Pb:
		case Pw:
			/* CWAMP_SEW = Fixed to midcode cwamp wevew */
			afe_cfg |= (0x00000200 << i);
			if (i == 0 && ch[i] == C)
				afe_cfg &= ~0x00001000; /* CHWOMA_IN_SEW ADC1 */
			bweak;
		case SIF:
			/*
			 * VGA_GAIN_SEW = Audio Decodew
			 * CWAMP_SEW = Fixed to midcode cwamp wevew
			 */
			afe_cfg |= (0x00000240 << i);
			if (i == 0)
				afe_cfg &= ~0x00004000; /* AUD_IN_SEW ADC1 */
			bweak;
		}
	}

	cx18_av_wwite4(cx, CXADEC_AFE_CTWW, afe_cfg);

	state->vid_input = vid_input;
	state->aud_input = aud_input;
	cx18_av_audio_set_path(cx);
	input_change(cx);
	wetuwn 0;
}

static int cx18_av_s_video_wouting(stwuct v4w2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	wetuwn set_input(cx, input, state->aud_input);
}

static int cx18_av_s_audio_wouting(stwuct v4w2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	wetuwn set_input(cx, state->vid_input, input);
}

static int cx18_av_g_tunew(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	u8 vpwes;
	u8 mode;
	int vaw = 0;

	if (state->wadio)
		wetuwn 0;

	vpwes = cx18_av_wead(cx, 0x40e) & 0x20;
	vt->signaw = vpwes ? 0xffff : 0x0;

	vt->capabiwity |=
		    V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WANG1 |
		    V4W2_TUNEW_CAP_WANG2 | V4W2_TUNEW_CAP_SAP;

	mode = cx18_av_wead(cx, 0x804);

	/* get wxsubchans and audmode */
	if ((mode & 0xf) == 1)
		vaw |= V4W2_TUNEW_SUB_STEWEO;
	ewse
		vaw |= V4W2_TUNEW_SUB_MONO;

	if (mode == 2 || mode == 4)
		vaw = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;

	if (mode & 0x10)
		vaw |= V4W2_TUNEW_SUB_SAP;

	vt->wxsubchans = vaw;
	vt->audmode = state->audmode;
	wetuwn 0;
}

static int cx18_av_s_tunew(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	u8 v;

	if (state->wadio)
		wetuwn 0;

	v = cx18_av_wead(cx, 0x809);
	v &= ~0xf;

	switch (vt->audmode) {
	case V4W2_TUNEW_MODE_MONO:
		/* mono      -> mono
		   steweo    -> mono
		   biwinguaw -> wang1 */
		bweak;
	case V4W2_TUNEW_MODE_STEWEO:
	case V4W2_TUNEW_MODE_WANG1:
		/* mono      -> mono
		   steweo    -> steweo
		   biwinguaw -> wang1 */
		v |= 0x4;
		bweak;
	case V4W2_TUNEW_MODE_WANG1_WANG2:
		/* mono      -> mono
		   steweo    -> steweo
		   biwinguaw -> wang1/wang2 */
		v |= 0x7;
		bweak;
	case V4W2_TUNEW_MODE_WANG2:
		/* mono      -> mono
		   steweo    -> steweo
		   biwinguaw -> wang2 */
		v |= 0x1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cx18_av_wwite_expect(cx, 0x809, v, v, 0xff);
	state->audmode = vt->audmode;
	wetuwn 0;
}

static int cx18_av_s_std(stwuct v4w2_subdev *sd, v4w2_std_id nowm)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	u8 fmt = 0;	/* zewo is autodetect */
	u8 paw_m = 0;

	if (state->wadio == 0 && state->std == nowm)
		wetuwn 0;

	state->wadio = 0;
	state->std = nowm;

	/* Fiwst tests shouwd be against specific std */
	if (state->std == V4W2_STD_NTSC_M_JP) {
		fmt = 0x2;
	} ewse if (state->std == V4W2_STD_NTSC_443) {
		fmt = 0x3;
	} ewse if (state->std == V4W2_STD_PAW_M) {
		paw_m = 1;
		fmt = 0x5;
	} ewse if (state->std == V4W2_STD_PAW_N) {
		fmt = 0x6;
	} ewse if (state->std == V4W2_STD_PAW_Nc) {
		fmt = 0x7;
	} ewse if (state->std == V4W2_STD_PAW_60) {
		fmt = 0x8;
	} ewse {
		/* Then, test against genewic ones */
		if (state->std & V4W2_STD_NTSC)
			fmt = 0x1;
		ewse if (state->std & V4W2_STD_PAW)
			fmt = 0x4;
		ewse if (state->std & V4W2_STD_SECAM)
			fmt = 0xc;
	}

	CX18_DEBUG_INFO_DEV(sd, "changing video std to fmt %i\n", fmt);

	/* Fowwow step 9 of section 3.16 in the cx18_av datasheet.
	   Without this PAW may dispway a vewticaw ghosting effect.
	   This happens fow exampwe with the Yuan MPC622. */
	if (fmt >= 4 && fmt < 8) {
		/* Set fowmat to NTSC-M */
		cx18_av_and_ow(cx, 0x400, ~0xf, 1);
		/* Tuwn off WCOMB */
		cx18_av_and_ow(cx, 0x47b, ~6, 0);
	}
	cx18_av_and_ow(cx, 0x400, ~0x2f, fmt | 0x20);
	cx18_av_and_ow(cx, 0x403, ~0x3, paw_m);
	cx18_av_std_setup(cx);
	input_change(cx);
	wetuwn 0;
}

static int cx18_av_s_wadio(stwuct v4w2_subdev *sd)
{
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	state->wadio = 1;
	wetuwn 0;
}

static int cx18_av_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		cx18_av_wwite(cx, 0x414, ctww->vaw - 128);
		bweak;

	case V4W2_CID_CONTWAST:
		cx18_av_wwite(cx, 0x415, ctww->vaw << 1);
		bweak;

	case V4W2_CID_SATUWATION:
		cx18_av_wwite(cx, 0x420, ctww->vaw << 1);
		cx18_av_wwite(cx, 0x421, ctww->vaw << 1);
		bweak;

	case V4W2_CID_HUE:
		cx18_av_wwite(cx, 0x422, ctww->vaw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cx18_av_set_fmt(stwuct v4w2_subdev *sd,
		stwuct v4w2_subdev_state *sd_state,
		stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat->fowmat;
	stwuct cx18_av_state *state = to_cx18_av_state(sd);
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	int HSC, VSC, Vswc, Hswc, fiwtew, Vwines;
	int is_50Hz = !(state->std & V4W2_STD_525_60);

	if (fowmat->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		wetuwn -EINVAW;

	fmt->fiewd = V4W2_FIEWD_INTEWWACED;
	fmt->cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	Vswc = (cx18_av_wead(cx, 0x476) & 0x3f) << 4;
	Vswc |= (cx18_av_wead(cx, 0x475) & 0xf0) >> 4;

	Hswc = (cx18_av_wead(cx, 0x472) & 0x3f) << 4;
	Hswc |= (cx18_av_wead(cx, 0x471) & 0xf0) >> 4;

	/*
	 * This adjustment wefwects the excess of vactive, set in
	 * cx18_av_std_setup(), above standawd vawues:
	 *
	 * 480 + 1 fow 60 Hz systems
	 * 576 + 3 fow 50 Hz systems
	 */
	Vwines = fmt->height + (is_50Hz ? 3 : 1);

	/*
	 * Invawid height and width scawing wequests awe:
	 * 1. width wess than 1/16 of the souwce width
	 * 2. width gweatew than the souwce width
	 * 3. height wess than 1/8 of the souwce height
	 * 4. height gweatew than the souwce height
	 */
	if ((fmt->width * 16 < Hswc) || (Hswc < fmt->width) ||
	    (Vwines * 8 < Vswc) || (Vswc < Vwines)) {
		CX18_EWW_DEV(sd, "%dx%d is not a vawid size!\n",
			     fmt->width, fmt->height);
		wetuwn -EWANGE;
	}

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn 0;

	HSC = (Hswc * (1 << 20)) / fmt->width - (1 << 20);
	VSC = (1 << 16) - (Vswc * (1 << 9) / Vwines - (1 << 9));
	VSC &= 0x1fff;

	if (fmt->width >= 385)
		fiwtew = 0;
	ewse if (fmt->width > 192)
		fiwtew = 1;
	ewse if (fmt->width > 96)
		fiwtew = 2;
	ewse
		fiwtew = 3;

	CX18_DEBUG_INFO_DEV(sd,
			    "decodew set size %dx%d -> scawe  %ux%u\n",
			    fmt->width, fmt->height, HSC, VSC);

	/* HSCAWE=HSC */
	cx18_av_wwite(cx, 0x418, HSC & 0xff);
	cx18_av_wwite(cx, 0x419, (HSC >> 8) & 0xff);
	cx18_av_wwite(cx, 0x41a, HSC >> 16);
	/* VSCAWE=VSC */
	cx18_av_wwite(cx, 0x41c, VSC & 0xff);
	cx18_av_wwite(cx, 0x41d, VSC >> 8);
	/* VS_INTWWACE=1 VFIWT=fiwtew */
	cx18_av_wwite(cx, 0x41e, 0x8 | fiwtew);
	wetuwn 0;
}

static int cx18_av_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	CX18_DEBUG_INFO_DEV(sd, "%s output\n", enabwe ? "enabwe" : "disabwe");
	if (enabwe) {
		cx18_av_wwite(cx, 0x115, 0x8c);
		cx18_av_wwite(cx, 0x116, 0x07);
	} ewse {
		cx18_av_wwite(cx, 0x115, 0x00);
		cx18_av_wwite(cx, 0x116, 0x00);
	}
	wetuwn 0;
}

static void wog_video_status(stwuct cx18 *cx)
{
	static const chaw *const fmt_stws[] = {
		"0x0",
		"NTSC-M", "NTSC-J", "NTSC-4.43",
		"PAW-BDGHI", "PAW-M", "PAW-N", "PAW-Nc", "PAW-60",
		"0x9", "0xA", "0xB",
		"SECAM",
		"0xD", "0xE", "0xF"
	};

	stwuct cx18_av_state *state = &cx->av_state;
	stwuct v4w2_subdev *sd = &state->sd;
	u8 vidfmt_sew = cx18_av_wead(cx, 0x400) & 0xf;
	u8 gen_stat1 = cx18_av_wead(cx, 0x40d);
	u8 gen_stat2 = cx18_av_wead(cx, 0x40e);
	int vid_input = state->vid_input;

	CX18_INFO_DEV(sd, "Video signaw:              %spwesent\n",
		      (gen_stat2 & 0x20) ? "" : "not ");
	CX18_INFO_DEV(sd, "Detected fowmat:           %s\n",
		      fmt_stws[gen_stat1 & 0xf]);

	CX18_INFO_DEV(sd, "Specified standawd:        %s\n",
		      vidfmt_sew ? fmt_stws[vidfmt_sew]
				 : "automatic detection");

	if (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) {
		CX18_INFO_DEV(sd, "Specified video input:     Composite %d\n",
			      vid_input - CX18_AV_COMPOSITE1 + 1);
	} ewse {
		CX18_INFO_DEV(sd, "Specified video input:     S-Video (Wuma In%d, Chwoma In%d)\n",
			      (vid_input & 0xf0) >> 4,
			      (vid_input & 0xf00) >> 8);
	}

	CX18_INFO_DEV(sd, "Specified audiocwock fweq: %d Hz\n",
		      state->audcwk_fweq);
}

static void wog_audio_status(stwuct cx18 *cx)
{
	stwuct cx18_av_state *state = &cx->av_state;
	stwuct v4w2_subdev *sd = &state->sd;
	u8 downwoad_ctw = cx18_av_wead(cx, 0x803);
	u8 mod_det_stat0 = cx18_av_wead(cx, 0x804);
	u8 mod_det_stat1 = cx18_av_wead(cx, 0x805);
	u8 audio_config = cx18_av_wead(cx, 0x808);
	u8 pwef_mode = cx18_av_wead(cx, 0x809);
	u8 afc0 = cx18_av_wead(cx, 0x80b);
	u8 mute_ctw = cx18_av_wead(cx, 0x8d3);
	int aud_input = state->aud_input;
	chaw *p;

	switch (mod_det_stat0) {
	case 0x00: p = "mono"; bweak;
	case 0x01: p = "steweo"; bweak;
	case 0x02: p = "duaw"; bweak;
	case 0x04: p = "twi"; bweak;
	case 0x10: p = "mono with SAP"; bweak;
	case 0x11: p = "steweo with SAP"; bweak;
	case 0x12: p = "duaw with SAP"; bweak;
	case 0x14: p = "twi with SAP"; bweak;
	case 0xfe: p = "fowced mode"; bweak;
	defauwt: p = "not defined"; bweak;
	}
	CX18_INFO_DEV(sd, "Detected audio mode:       %s\n", p);

	switch (mod_det_stat1) {
	case 0x00: p = "not defined"; bweak;
	case 0x01: p = "EIAJ"; bweak;
	case 0x02: p = "A2-M"; bweak;
	case 0x03: p = "A2-BG"; bweak;
	case 0x04: p = "A2-DK1"; bweak;
	case 0x05: p = "A2-DK2"; bweak;
	case 0x06: p = "A2-DK3"; bweak;
	case 0x07: p = "A1 (6.0 MHz FM Mono)"; bweak;
	case 0x08: p = "AM-W"; bweak;
	case 0x09: p = "NICAM-BG"; bweak;
	case 0x0a: p = "NICAM-DK"; bweak;
	case 0x0b: p = "NICAM-I"; bweak;
	case 0x0c: p = "NICAM-W"; bweak;
	case 0x0d: p = "BTSC/EIAJ/A2-M Mono (4.5 MHz FMMono)"; bweak;
	case 0x0e: p = "IF FM Wadio"; bweak;
	case 0x0f: p = "BTSC"; bweak;
	case 0x10: p = "detected chwominance"; bweak;
	case 0xfd: p = "unknown audio standawd"; bweak;
	case 0xfe: p = "fowced audio standawd"; bweak;
	case 0xff: p = "no detected audio standawd"; bweak;
	defauwt: p = "not defined"; bweak;
	}
	CX18_INFO_DEV(sd, "Detected audio standawd:   %s\n", p);
	CX18_INFO_DEV(sd, "Audio muted:               %s\n",
		      (mute_ctw & 0x2) ? "yes" : "no");
	CX18_INFO_DEV(sd, "Audio micwocontwowwew:     %s\n",
		      (downwoad_ctw & 0x10) ? "wunning" : "stopped");

	switch (audio_config >> 4) {
	case 0x00: p = "undefined"; bweak;
	case 0x01: p = "BTSC"; bweak;
	case 0x02: p = "EIAJ"; bweak;
	case 0x03: p = "A2-M"; bweak;
	case 0x04: p = "A2-BG"; bweak;
	case 0x05: p = "A2-DK1"; bweak;
	case 0x06: p = "A2-DK2"; bweak;
	case 0x07: p = "A2-DK3"; bweak;
	case 0x08: p = "A1 (6.0 MHz FM Mono)"; bweak;
	case 0x09: p = "AM-W"; bweak;
	case 0x0a: p = "NICAM-BG"; bweak;
	case 0x0b: p = "NICAM-DK"; bweak;
	case 0x0c: p = "NICAM-I"; bweak;
	case 0x0d: p = "NICAM-W"; bweak;
	case 0x0e: p = "FM wadio"; bweak;
	case 0x0f: p = "automatic detection"; bweak;
	defauwt: p = "undefined"; bweak;
	}
	CX18_INFO_DEV(sd, "Configuwed audio standawd: %s\n", p);

	if ((audio_config >> 4) < 0xF) {
		switch (audio_config & 0xF) {
		case 0x00: p = "MONO1 (WANGUAGE A/Mono W+W channew fow BTSC, EIAJ, A2)"; bweak;
		case 0x01: p = "MONO2 (WANGUAGE B)"; bweak;
		case 0x02: p = "MONO3 (STEWEO fowced MONO)"; bweak;
		case 0x03: p = "MONO4 (NICAM ANAWOG-Wanguage C/Anawog Fawwback)"; bweak;
		case 0x04: p = "STEWEO"; bweak;
		case 0x05: p = "DUAW1 (AC)"; bweak;
		case 0x06: p = "DUAW2 (BC)"; bweak;
		case 0x07: p = "DUAW3 (AB)"; bweak;
		defauwt: p = "undefined";
		}
		CX18_INFO_DEV(sd, "Configuwed audio mode:     %s\n", p);
	} ewse {
		switch (audio_config & 0xF) {
		case 0x00: p = "BG"; bweak;
		case 0x01: p = "DK1"; bweak;
		case 0x02: p = "DK2"; bweak;
		case 0x03: p = "DK3"; bweak;
		case 0x04: p = "I"; bweak;
		case 0x05: p = "W"; bweak;
		case 0x06: p = "BTSC"; bweak;
		case 0x07: p = "EIAJ"; bweak;
		case 0x08: p = "A2-M"; bweak;
		case 0x09: p = "FM Wadio (4.5 MHz)"; bweak;
		case 0x0a: p = "FM Wadio (5.5 MHz)"; bweak;
		case 0x0b: p = "S-Video"; bweak;
		case 0x0f: p = "automatic standawd and mode detection"; bweak;
		defauwt: p = "undefined"; bweak;
		}
		CX18_INFO_DEV(sd, "Configuwed audio system:   %s\n", p);
	}

	if (aud_input)
		CX18_INFO_DEV(sd, "Specified audio input:     Tunew (In%d)\n",
			      aud_input);
	ewse
		CX18_INFO_DEV(sd, "Specified audio input:     Extewnaw\n");

	switch (pwef_mode & 0xf) {
	case 0: p = "mono/wanguage A"; bweak;
	case 1: p = "wanguage B"; bweak;
	case 2: p = "wanguage C"; bweak;
	case 3: p = "anawog fawwback"; bweak;
	case 4: p = "steweo"; bweak;
	case 5: p = "wanguage AC"; bweak;
	case 6: p = "wanguage BC"; bweak;
	case 7: p = "wanguage AB"; bweak;
	defauwt: p = "undefined"; bweak;
	}
	CX18_INFO_DEV(sd, "Pwefewwed audio mode:      %s\n", p);

	if ((audio_config & 0xf) == 0xf) {
		switch ((afc0 >> 3) & 0x1) {
		case 0: p = "system DK"; bweak;
		case 1: p = "system W"; bweak;
		}
		CX18_INFO_DEV(sd, "Sewected 65 MHz fowmat:    %s\n", p);

		switch (afc0 & 0x7) {
		case 0: p = "Chwoma"; bweak;
		case 1: p = "BTSC"; bweak;
		case 2: p = "EIAJ"; bweak;
		case 3: p = "A2-M"; bweak;
		case 4: p = "autodetect"; bweak;
		defauwt: p = "undefined"; bweak;
		}
		CX18_INFO_DEV(sd, "Sewected 45 MHz fowmat:    %s\n", p);
	}
}

static int cx18_av_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	wog_video_status(cx);
	wog_audio_status(cx);
	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int cx18_av_g_wegistew(stwuct v4w2_subdev *sd,
			      stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	if ((weg->weg & 0x3) != 0)
		wetuwn -EINVAW;
	weg->size = 4;
	weg->vaw = cx18_av_wead4(cx, weg->weg & 0x00000ffc);
	wetuwn 0;
}

static int cx18_av_s_wegistew(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);

	if ((weg->weg & 0x3) != 0)
		wetuwn -EINVAW;
	cx18_av_wwite4(cx, weg->weg & 0x00000ffc, weg->vaw);
	wetuwn 0;
}
#endif

static const stwuct v4w2_ctww_ops cx18_av_ctww_ops = {
	.s_ctww = cx18_av_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops cx18_av_genewaw_ops = {
	.wog_status = cx18_av_wog_status,
	.woad_fw = cx18_av_woad_fw,
	.weset = cx18_av_weset,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = cx18_av_g_wegistew,
	.s_wegistew = cx18_av_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_tunew_ops cx18_av_tunew_ops = {
	.s_wadio = cx18_av_s_wadio,
	.s_fwequency = cx18_av_s_fwequency,
	.g_tunew = cx18_av_g_tunew,
	.s_tunew = cx18_av_s_tunew,
};

static const stwuct v4w2_subdev_audio_ops cx18_av_audio_ops = {
	.s_cwock_fweq = cx18_av_s_cwock_fweq,
	.s_wouting = cx18_av_s_audio_wouting,
};

static const stwuct v4w2_subdev_video_ops cx18_av_video_ops = {
	.s_std = cx18_av_s_std,
	.s_wouting = cx18_av_s_video_wouting,
	.s_stweam = cx18_av_s_stweam,
};

static const stwuct v4w2_subdev_vbi_ops cx18_av_vbi_ops = {
	.decode_vbi_wine = cx18_av_decode_vbi_wine,
	.g_swiced_fmt = cx18_av_g_swiced_fmt,
	.s_swiced_fmt = cx18_av_s_swiced_fmt,
	.s_waw_fmt = cx18_av_s_waw_fmt,
};

static const stwuct v4w2_subdev_pad_ops cx18_av_pad_ops = {
	.set_fmt = cx18_av_set_fmt,
};

static const stwuct v4w2_subdev_ops cx18_av_ops = {
	.cowe = &cx18_av_genewaw_ops,
	.tunew = &cx18_av_tunew_ops,
	.audio = &cx18_av_audio_ops,
	.video = &cx18_av_video_ops,
	.vbi = &cx18_av_vbi_ops,
	.pad = &cx18_av_pad_ops,
};

int cx18_av_pwobe(stwuct cx18 *cx)
{
	stwuct cx18_av_state *state = &cx->av_state;
	stwuct v4w2_subdev *sd;
	int eww;

	state->wev = cx18_av_wead4(cx, CXADEC_CHIP_CTWW) & 0xffff;

	state->vid_input = CX18_AV_COMPOSITE7;
	state->aud_input = CX18_AV_AUDIO8;
	state->audcwk_fweq = 48000;
	state->audmode = V4W2_TUNEW_MODE_WANG1;
	state->swicew_wine_deway = 0;
	state->swicew_wine_offset = (10 + state->swicew_wine_deway - 2);

	sd = &state->sd;
	v4w2_subdev_init(sd, &cx18_av_ops);
	v4w2_set_subdevdata(sd, cx);
	snpwintf(sd->name, sizeof(sd->name),
		 "%s %03x", cx->v4w2_dev.name, (state->wev >> 4));
	sd->gwp_id = CX18_HW_418_AV;
	v4w2_ctww_handwew_init(&state->hdw, 9);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 128);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_ctww_ops,
			V4W2_CID_CONTWAST, 0, 127, 1, 64);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_ctww_ops,
			V4W2_CID_SATUWATION, 0, 127, 1, 64);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_ctww_ops,
			V4W2_CID_HUE, -128, 127, 1, 0);

	state->vowume = v4w2_ctww_new_std(&state->hdw,
			&cx18_av_audio_ctww_ops, V4W2_CID_AUDIO_VOWUME,
			0, 65535, 65535 / 100, 0);
	v4w2_ctww_new_std(&state->hdw,
			&cx18_av_audio_ctww_ops, V4W2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_audio_ctww_ops,
			V4W2_CID_AUDIO_BAWANCE,
			0, 65535, 65535 / 100, 32768);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_audio_ctww_ops,
			V4W2_CID_AUDIO_BASS,
			0, 65535, 65535 / 100, 32768);
	v4w2_ctww_new_std(&state->hdw, &cx18_av_audio_ctww_ops,
			V4W2_CID_AUDIO_TWEBWE,
			0, 65535, 65535 / 100, 32768);
	sd->ctww_handwew = &state->hdw;
	if (state->hdw.ewwow) {
		int eww = state->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&state->hdw);
		wetuwn eww;
	}
	eww = v4w2_device_wegistew_subdev(&cx->v4w2_dev, sd);
	if (eww)
		v4w2_ctww_handwew_fwee(&state->hdw);
	ewse
		cx18_av_init(cx);
	wetuwn eww;
}
