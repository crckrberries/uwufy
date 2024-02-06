/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "nouveau_dwv.h"
#incwude "nouveau_encodew.h"
#incwude "nouveau_cwtc.h"
#incwude "hw.h"
#incwude "tvnv17.h"

const chaw * const nv17_tv_nowm_names[NUM_TV_NOWMS] = {
	[TV_NOWM_PAW] = "PAW",
	[TV_NOWM_PAW_M] = "PAW-M",
	[TV_NOWM_PAW_N] = "PAW-N",
	[TV_NOWM_PAW_NC] = "PAW-Nc",
	[TV_NOWM_NTSC_M] = "NTSC-M",
	[TV_NOWM_NTSC_J] = "NTSC-J",
	[TV_NOWM_HD480I] = "hd480i",
	[TV_NOWM_HD480P] = "hd480p",
	[TV_NOWM_HD576I] = "hd576i",
	[TV_NOWM_HD576P] = "hd576p",
	[TV_NOWM_HD720P] = "hd720p",
	[TV_NOWM_HD1080I] = "hd1080i"
};

/* TV standawd specific pawametews */

stwuct nv17_tv_nowm_pawams nv17_tv_nowms[NUM_TV_NOWMS] = {
	[TV_NOWM_PAW] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 576, 50000, {
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				} } } },

	[TV_NOWM_PAW_M] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 480, 59940, {
					0x21, 0xe6, 0xef, 0xe3, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x32, 0x25, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x18, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x40, 0x10, 0x0, 0x9c,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_PAW_N] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 576, 50000, {
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x32, 0x25, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_PAW_NC] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 576, 50000, {
					0x21, 0xf6, 0x94, 0x46, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				} } } },

	[TV_NOWM_NTSC_M] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 480, 59940, {
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x3c, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xc5, 0x4, 0xc5, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0x9c,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_NTSC_J] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 480, 59940, {
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x32, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xcf, 0x4, 0xcf, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0xa4,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_HD480I] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 480, 59940, {
					0x21, 0xf0, 0x7c, 0x1f, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x44, 0x76, 0x48, 0x0, 0x0, 0x32, 0x0,
					0x3c, 0x0, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x83,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x1,
					0xcf, 0x4, 0xcf, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x16, 0xff, 0x3, 0x20, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x4, 0x10, 0x0, 0xa4,
					0xc8, 0x15, 0x5, 0x15, 0x3c, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_HD576I] = { TV_ENC_MODE, {
			.tv_enc_mode = { 720, 576, 50000, {
					0x2a, 0x9, 0x8a, 0xcb, 0x0, 0x0, 0xb, 0x18,
					0x7e, 0x40, 0x8a, 0x35, 0x27, 0x0, 0x34, 0x3,
					0x3e, 0x3, 0x17, 0x21, 0x1b, 0x1b, 0x24, 0x9c,
					0x1, 0x0, 0xf, 0xf, 0x60, 0x5, 0xd3, 0x3,
					0xd3, 0x4, 0xd4, 0x1, 0x2, 0x0, 0xa, 0x5,
					0x0, 0x1a, 0xff, 0x3, 0x18, 0xf, 0x78, 0x0,
					0x0, 0xb4, 0x0, 0x15, 0x49, 0x10, 0x0, 0x9b,
					0xbd, 0x15, 0x5, 0x15, 0x3e, 0x3, 0x0, 0x0
				} } } },


	[TV_NOWM_HD480P] = { CTV_ENC_MODE, {
			.ctv_enc_mode = {
				.mode = { DWM_MODE("720x480", DWM_MODE_TYPE_DWIVEW, 27000,
						   720, 735, 743, 858, 0, 480, 490, 494, 525, 0,
						   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
				.ctv_wegs = { 0x3540000, 0x0, 0x0, 0x314,
					      0x354003a, 0x40000, 0x6f0344, 0x18100000,
					      0x10160004, 0x10060005, 0x1006000c, 0x10060020,
					      0x10060021, 0x140e0022, 0x10060202, 0x1802020a,
					      0x1810020b, 0x10000fff, 0x10000fff, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x70,
					      0x3ff0000, 0x57, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x80960019, 0x12c0300,
					      0x2019, 0x600, 0x32060019, 0x0, 0x0, 0x400
				} } } },

	[TV_NOWM_HD576P] = { CTV_ENC_MODE, {
			.ctv_enc_mode = {
				.mode = { DWM_MODE("720x576", DWM_MODE_TYPE_DWIVEW, 27000,
						   720, 730, 738, 864, 0, 576, 581, 585, 625, 0,
						   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
				.ctv_wegs = { 0x3540000, 0x0, 0x0, 0x314,
					      0x354003a, 0x40000, 0x6f0344, 0x18100000,
					      0x10060001, 0x10060009, 0x10060026, 0x10060027,
					      0x140e0028, 0x10060268, 0x1810026d, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x10000fff,
					      0x10000fff, 0x10000fff, 0x10000fff, 0x69,
					      0x3ff0000, 0x57, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x80960019, 0x12c0300,
					      0x2019, 0x600, 0x32060019, 0x0, 0x0, 0x400
				} } } },

	[TV_NOWM_HD720P] = { CTV_ENC_MODE, {
			.ctv_enc_mode = {
				.mode = { DWM_MODE("1280x720", DWM_MODE_TYPE_DWIVEW, 74250,
						   1280, 1349, 1357, 1650, 0, 720, 725, 730, 750, 0,
						   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
				.ctv_wegs = { 0x1260394, 0x0, 0x0, 0x622,
					      0x66b0021, 0x6004a, 0x1210626, 0x8170000,
					      0x70004, 0x70016, 0x70017, 0x40f0018,
					      0x702e8, 0x81702ed, 0xfff, 0xfff,
					      0xfff, 0xfff, 0xfff, 0xfff,
					      0xfff, 0xfff, 0xfff, 0x0,
					      0x2e40001, 0x58, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x810c0039, 0x12c0300,
					      0xc0002039, 0x600, 0x32060039, 0x0, 0x0, 0x0
				} } } },

	[TV_NOWM_HD1080I] = { CTV_ENC_MODE, {
			.ctv_enc_mode = {
				.mode = { DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 74250,
						   1920, 1961, 2049, 2200, 0, 1080, 1084, 1088, 1125, 0,
						   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC
						   | DWM_MODE_FWAG_INTEWWACE) },
				.ctv_wegs = { 0xac0420, 0x44c0478, 0x4a4, 0x4fc0868,
					      0x8940028, 0x60054, 0xe80870, 0xbf70000,
					      0xbc70004, 0x70005, 0x70012, 0x70013,
					      0x40f0014, 0x70230, 0xbf70232, 0xbf70233,
					      0x1c70237, 0x70238, 0x70244, 0x70245,
					      0x40f0246, 0x70462, 0x1f70464, 0x0,
					      0x2e40001, 0x58, 0x2e001e, 0x258012c,
					      0xa0aa04ec, 0x30, 0x815f004c, 0x12c0300,
					      0xc000204c, 0x600, 0x3206004c, 0x0, 0x0, 0x0
				} } } }
};

/*
 * The fowwowing is some guesswowk on how the TV encodew fwickew
 * fiwtew/wescawew wowks:
 *
 * It seems to use some sowt of wesampwing fiwtew, it is contwowwed
 * thwough the wegistews at NV_PTV_HFIWTEW and NV_PTV_VFIWTEW, they
 * contwow the howizontaw and vewticaw stage wespectivewy, thewe is
 * awso NV_PTV_HFIWTEW2 the bwob fiwws identicawwy to NV_PTV_HFIWTEW,
 * but they seem to do nothing. A wough guess might be that they couwd
 * be used to independentwy contwow the fiwtewing of each intewwaced
 * fiewd, but I don't know how they awe enabwed. The whowe fiwtewing
 * pwocess seems to be disabwed with bits 26:27 of PTV_200, but we
 * awen't doing that.
 *
 * The wayout of both wegistew sets is the same:
 *
 * A: [BASE+0x18]...[BASE+0x0] [BASE+0x58]..[BASE+0x40]
 * B: [BASE+0x34]...[BASE+0x1c] [BASE+0x74]..[BASE+0x5c]
 *
 * Each coefficient is stowed in bits [31],[15:9] in two's compwement
 * fowmat. They seem to be some kind of weights used in a wow-pass
 * fiwtew. Both A and B coefficients awe appwied to the 14 neawest
 * sampwes on each side (Wisted fwom neawest to fuwthewmost.  They
 * woughwy covew 2 fwamebuffew pixews on each side).  They awe
 * pwobabwy muwtipwied with some mowe hawdwiwed weights befowe being
 * used: B-coefficients awe appwied the same on both sides,
 * A-coefficients awe invewted befowe being appwied to the opposite
 * side.
 *
 * Aftew aww the hasswe, I got the fowwowing fowmuwa by empiwicaw
 * means...
 */

#define cawc_ovewscan(o) intewpowate(0x100, 0xe1, 0xc1, o)

#define id1 (1WW << 8)
#define id2 (1WW << 16)
#define id3 (1WW << 24)
#define id4 (1WW << 32)
#define id5 (1WW << 48)

static stwuct fiwtew_pawams{
	int64_t k1;
	int64_t ki;
	int64_t ki2;
	int64_t ki3;
	int64_t kw;
	int64_t kiw;
	int64_t ki2w;
	int64_t ki3w;
	int64_t kf;
	int64_t kif;
	int64_t ki2f;
	int64_t ki3f;
	int64_t kwf;
	int64_t kiwf;
	int64_t ki2wf;
	int64_t ki3wf;
} fpawams[2][4] = {
	/* Howizontaw fiwtew pawametews */
	{
		{64.311690 * id5, -39.516924 * id5, 6.586143 * id5, 0.000002 * id5,
		 0.051285 * id4, 26.168746 * id4, -4.361449 * id4, -0.000001 * id4,
		 9.308169 * id3, 78.180965 * id3, -13.030158 * id3, -0.000001 * id3,
		 -8.801540 * id1, -46.572890 * id1, 7.762145 * id1, -0.000000 * id1},
		{-44.565569 * id5, -68.081246 * id5, 39.812074 * id5, -4.009316 * id5,
		 29.832207 * id4, 50.047322 * id4, -25.380017 * id4, 2.546422 * id4,
		 104.605622 * id3, 141.908641 * id3, -74.322319 * id3, 7.484316 * id3,
		 -37.081621 * id1, -90.397510 * id1, 42.784229 * id1, -4.289952 * id1},
		{-56.793244 * id5, 31.153584 * id5, -5.192247 * id5, -0.000003 * id5,
		 33.541131 * id4, -34.149302 * id4, 5.691537 * id4, 0.000002 * id4,
		 87.196610 * id3, -88.995169 * id3, 14.832456 * id3, 0.000012 * id3,
		 17.288138 * id1, 71.864786 * id1, -11.977408 * id1, -0.000009 * id1},
		{51.787796 * id5, 21.211771 * id5, -18.993730 * id5, 1.853310 * id5,
		 -41.470726 * id4, -17.775823 * id4, 13.057821 * id4, -1.15823 * id4,
		 -154.235673 * id3, -44.878641 * id3, 40.656077 * id3, -3.695595 * id3,
		 112.201065 * id1, 39.992155 * id1, -25.155714 * id1, 2.113984 * id1},
	},

	/* Vewticaw fiwtew pawametews */
	{
		{67.601979 * id5, 0.428319 * id5, -0.071318 * id5, -0.000012 * id5,
		 -3.402339 * id4, 0.000209 * id4, -0.000092 * id4, 0.000010 * id4,
		 -9.180996 * id3, 6.111270 * id3, -1.024457 * id3, 0.001043 * id3,
		 6.060315 * id1, -0.017425 * id1, 0.007830 * id1, -0.000869 * id1},
		{6.755647 * id5, 5.841348 * id5, 1.469734 * id5, -0.149656 * id5,
		 8.293120 * id4, -1.192888 * id4, -0.947652 * id4, 0.094507 * id4,
		 37.526655 * id3, 10.257875 * id3, -10.823275 * id3, 1.081497 * id3,
		 -2.361928 * id1, -2.059432 * id1, 1.840671 * id1, -0.168100 * id1},
		{-14.780391 * id5, -16.042148 * id5, 2.673692 * id5, -0.000000 * id5,
		 39.541978 * id4, 5.680053 * id4, -0.946676 * id4, 0.000000 * id4,
		 152.994486 * id3, 12.625439 * id3, -2.119579 * id3, 0.002708 * id3,
		 -38.125089 * id1, -0.855880 * id1, 0.155359 * id1, -0.002245 * id1},
		{-27.476193 * id5, -1.454976 * id5, 1.286557 * id5, 0.025346 * id5,
		 20.687300 * id4, 3.014003 * id4, -0.557786 * id4, -0.01311 * id4,
		 60.008737 * id3, -0.738273 * id3, 5.408217 * id3, -0.796798 * id3,
		 -17.296835 * id1, 4.438577 * id1, -2.809420 * id1, 0.385491 * id1},
	}
};

static void tv_setup_fiwtew(stwuct dwm_encodew *encodew)
{
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->mode;
	uint32_t (*fiwtews[])[4][7] = {&tv_enc->state.hfiwtew,
				       &tv_enc->state.vfiwtew};
	int i, j, k;
	int32_t ovewscan = cawc_ovewscan(tv_enc->ovewscan);
	int64_t fwickew = (tv_enc->fwickew - 50) * (id3 / 100);
	uint64_t ws[] = {mode->hdispway * id3,
			 mode->vdispway * id3};

	do_div(ws[0], ovewscan * tv_nowm->tv_enc_mode.hdispway);
	do_div(ws[1], ovewscan * tv_nowm->tv_enc_mode.vdispway);

	fow (k = 0; k < 2; k++) {
		ws[k] = max((int64_t)ws[k], id2);

		fow (j = 0; j < 4; j++) {
			stwuct fiwtew_pawams *p = &fpawams[k][j];

			fow (i = 0; i < 7; i++) {
				int64_t c = (p->k1 + p->ki*i + p->ki2*i*i +
					     p->ki3*i*i*i)
					+ (p->kw + p->kiw*i + p->ki2w*i*i +
					   p->ki3w*i*i*i) * ws[k]
					+ (p->kf + p->kif*i + p->ki2f*i*i +
					   p->ki3f*i*i*i) * fwickew
					+ (p->kwf + p->kiwf*i + p->ki2wf*i*i +
					   p->ki3wf*i*i*i) * fwickew * ws[k];

				(*fiwtews[k])[j][i] = (c + id5/2) >> 39
					& (0x1 << 31 | 0x7f << 9);
			}
		}
	}
}

/* Hawdwawe state saving/westowing */

static void tv_save_fiwtew(stwuct dwm_device *dev, uint32_t base,
			   uint32_t wegs[4][7])
{
	int i, j;
	uint32_t offsets[] = { base, base + 0x1c, base + 0x40, base + 0x5c };

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < 7; j++)
			wegs[i][j] = nv_wead_ptv(dev, offsets[i]+4*j);
	}
}

static void tv_woad_fiwtew(stwuct dwm_device *dev, uint32_t base,
			   uint32_t wegs[4][7])
{
	int i, j;
	uint32_t offsets[] = { base, base + 0x1c, base + 0x40, base + 0x5c };

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < 7; j++)
			nv_wwite_ptv(dev, offsets[i]+4*j, wegs[i][j]);
	}
}

void nv17_tv_state_save(stwuct dwm_device *dev, stwuct nv17_tv_state *state)
{
	int i;

	fow (i = 0; i < 0x40; i++)
		state->tv_enc[i] = nv_wead_tv_enc(dev, i);

	tv_save_fiwtew(dev, NV_PTV_HFIWTEW, state->hfiwtew);
	tv_save_fiwtew(dev, NV_PTV_HFIWTEW2, state->hfiwtew2);
	tv_save_fiwtew(dev, NV_PTV_VFIWTEW, state->vfiwtew);

	nv_save_ptv(dev, state, 200);
	nv_save_ptv(dev, state, 204);
	nv_save_ptv(dev, state, 208);
	nv_save_ptv(dev, state, 20c);
	nv_save_ptv(dev, state, 304);
	nv_save_ptv(dev, state, 500);
	nv_save_ptv(dev, state, 504);
	nv_save_ptv(dev, state, 508);
	nv_save_ptv(dev, state, 600);
	nv_save_ptv(dev, state, 604);
	nv_save_ptv(dev, state, 608);
	nv_save_ptv(dev, state, 60c);
	nv_save_ptv(dev, state, 610);
	nv_save_ptv(dev, state, 614);
}

void nv17_tv_state_woad(stwuct dwm_device *dev, stwuct nv17_tv_state *state)
{
	int i;

	fow (i = 0; i < 0x40; i++)
		nv_wwite_tv_enc(dev, i, state->tv_enc[i]);

	tv_woad_fiwtew(dev, NV_PTV_HFIWTEW, state->hfiwtew);
	tv_woad_fiwtew(dev, NV_PTV_HFIWTEW2, state->hfiwtew2);
	tv_woad_fiwtew(dev, NV_PTV_VFIWTEW, state->vfiwtew);

	nv_woad_ptv(dev, state, 200);
	nv_woad_ptv(dev, state, 204);
	nv_woad_ptv(dev, state, 208);
	nv_woad_ptv(dev, state, 20c);
	nv_woad_ptv(dev, state, 304);
	nv_woad_ptv(dev, state, 500);
	nv_woad_ptv(dev, state, 504);
	nv_woad_ptv(dev, state, 508);
	nv_woad_ptv(dev, state, 600);
	nv_woad_ptv(dev, state, 604);
	nv_woad_ptv(dev, state, 608);
	nv_woad_ptv(dev, state, 60c);
	nv_woad_ptv(dev, state, 610);
	nv_woad_ptv(dev, state, 614);

	/* This is wequiwed fow some settings to kick in. */
	nv_wwite_tv_enc(dev, 0x3e, 1);
	nv_wwite_tv_enc(dev, 0x3e, 0);
}

/* Timings simiwaw to the ones the bwob sets */

const stwuct dwm_dispway_mode nv17_tv_modes[] = {
	{ DWM_MODE("320x200", DWM_MODE_TYPE_DWIVEW, 0,
		   320, 344, 392, 560, 0, 200, 200, 202, 220, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC
		   | DWM_MODE_FWAG_DBWSCAN | DWM_MODE_FWAG_CWKDIV2) },
	{ DWM_MODE("320x240", DWM_MODE_TYPE_DWIVEW, 0,
		   320, 344, 392, 560, 0, 240, 240, 246, 263, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC
		   | DWM_MODE_FWAG_DBWSCAN | DWM_MODE_FWAG_CWKDIV2) },
	{ DWM_MODE("400x300", DWM_MODE_TYPE_DWIVEW, 0,
		   400, 432, 496, 640, 0, 300, 300, 303, 314, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC
		   | DWM_MODE_FWAG_DBWSCAN | DWM_MODE_FWAG_CWKDIV2) },
	{ DWM_MODE("640x480", DWM_MODE_TYPE_DWIVEW, 0,
		   640, 672, 768, 880, 0, 480, 480, 492, 525, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	{ DWM_MODE("720x480", DWM_MODE_TYPE_DWIVEW, 0,
		   720, 752, 872, 960, 0, 480, 480, 493, 525, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	{ DWM_MODE("720x576", DWM_MODE_TYPE_DWIVEW, 0,
		   720, 776, 856, 960, 0, 576, 576, 588, 597, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	{ DWM_MODE("800x600", DWM_MODE_TYPE_DWIVEW, 0,
		   800, 840, 920, 1040, 0, 600, 600, 604, 618, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	{ DWM_MODE("1024x768", DWM_MODE_TYPE_DWIVEW, 0,
		   1024, 1064, 1200, 1344, 0, 768, 768, 777, 806, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	{}
};

void nv17_tv_update_pwopewties(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct nv17_tv_state *wegs = &tv_enc->state;
	stwuct nv17_tv_nowm_pawams *tv_nowm = get_tv_nowm(encodew);
	int subconnectow = tv_enc->sewect_subconnectow ?
						tv_enc->sewect_subconnectow :
						tv_enc->subconnectow;

	switch (subconnectow) {
	case DWM_MODE_SUBCONNECTOW_Composite:
	{
		wegs->ptv_204 = 0x2;

		/* The composite connectow may be found on eithew pin. */
		if (tv_enc->pin_mask & 0x4)
			wegs->ptv_204 |= 0x010000;
		ewse if (tv_enc->pin_mask & 0x2)
			wegs->ptv_204 |= 0x100000;
		ewse
			wegs->ptv_204 |= 0x110000;

		wegs->tv_enc[0x7] = 0x10;
		bweak;
	}
	case DWM_MODE_SUBCONNECTOW_SVIDEO:
		wegs->ptv_204 = 0x11012;
		wegs->tv_enc[0x7] = 0x18;
		bweak;

	case DWM_MODE_SUBCONNECTOW_Component:
		wegs->ptv_204 = 0x111333;
		wegs->tv_enc[0x7] = 0x14;
		bweak;

	case DWM_MODE_SUBCONNECTOW_SCAWT:
		wegs->ptv_204 = 0x111012;
		wegs->tv_enc[0x7] = 0x18;
		bweak;
	}

	wegs->tv_enc[0x20] = intewpowate(0, tv_nowm->tv_enc_mode.tv_enc[0x20],
					 255, tv_enc->satuwation);
	wegs->tv_enc[0x22] = intewpowate(0, tv_nowm->tv_enc_mode.tv_enc[0x22],
					 255, tv_enc->satuwation);
	wegs->tv_enc[0x25] = tv_enc->hue * 255 / 100;

	nv_woad_ptv(dev, wegs, 204);
	nv_woad_tv_enc(dev, wegs, 7);
	nv_woad_tv_enc(dev, wegs, 20);
	nv_woad_tv_enc(dev, wegs, 22);
	nv_woad_tv_enc(dev, wegs, 25);
}

void nv17_tv_update_wescawew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	stwuct nv17_tv_state *wegs = &tv_enc->state;

	wegs->ptv_208 = 0x40 | (cawc_ovewscan(tv_enc->ovewscan) << 8);

	tv_setup_fiwtew(encodew);

	nv_woad_ptv(dev, wegs, 208);
	tv_woad_fiwtew(dev, NV_PTV_HFIWTEW, wegs->hfiwtew);
	tv_woad_fiwtew(dev, NV_PTV_HFIWTEW2, wegs->hfiwtew2);
	tv_woad_fiwtew(dev, NV_PTV_VFIWTEW, wegs->vfiwtew);
}

void nv17_ctv_update_wescawew(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct nv17_tv_encodew *tv_enc = to_tv_enc(encodew);
	int head = nouveau_cwtc(encodew->cwtc)->index;
	stwuct nv04_cwtc_weg *wegs = &nv04_dispway(dev)->mode_weg.cwtc_weg[head];
	stwuct dwm_dispway_mode *cwtc_mode = &encodew->cwtc->mode;
	stwuct dwm_dispway_mode *output_mode =
		&get_tv_nowm(encodew)->ctv_enc_mode.mode;
	int ovewscan, hmawgin, vmawgin, hwatio, vwatio;

	/* The wescawew doesn't do the wight thing fow intewwaced modes. */
	if (output_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		ovewscan = 100;
	ewse
		ovewscan = tv_enc->ovewscan;

	hmawgin = (output_mode->hdispway - cwtc_mode->hdispway) / 2;
	vmawgin = (output_mode->vdispway - cwtc_mode->vdispway) / 2;

	hmawgin = intewpowate(0, min(hmawgin, output_mode->hdispway/20),
			      hmawgin, ovewscan);
	vmawgin = intewpowate(0, min(vmawgin, output_mode->vdispway/20),
			      vmawgin, ovewscan);

	hwatio = cwtc_mode->hdispway * 0x800 /
		(output_mode->hdispway - 2*hmawgin);
	vwatio = cwtc_mode->vdispway * 0x800 /
		(output_mode->vdispway - 2*vmawgin) & ~3;

	wegs->fp_howiz_wegs[FP_VAWID_STAWT] = hmawgin;
	wegs->fp_howiz_wegs[FP_VAWID_END] = output_mode->hdispway - hmawgin - 1;
	wegs->fp_vewt_wegs[FP_VAWID_STAWT] = vmawgin;
	wegs->fp_vewt_wegs[FP_VAWID_END] = output_mode->vdispway - vmawgin - 1;

	wegs->fp_debug_1 = NV_PWAMDAC_FP_DEBUG_1_YSCAWE_TESTMODE_ENABWE |
		XWATE(vwatio, 0, NV_PWAMDAC_FP_DEBUG_1_YSCAWE_VAWUE) |
		NV_PWAMDAC_FP_DEBUG_1_XSCAWE_TESTMODE_ENABWE |
		XWATE(hwatio, 0, NV_PWAMDAC_FP_DEBUG_1_XSCAWE_VAWUE);

	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HVAWID_STAWT,
		      wegs->fp_howiz_wegs[FP_VAWID_STAWT]);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_HVAWID_END,
		      wegs->fp_howiz_wegs[FP_VAWID_END]);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_VVAWID_STAWT,
		      wegs->fp_vewt_wegs[FP_VAWID_STAWT]);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_VVAWID_END,
		      wegs->fp_vewt_wegs[FP_VAWID_END]);
	NVWwiteWAMDAC(dev, head, NV_PWAMDAC_FP_DEBUG_1, wegs->fp_debug_1);
}
