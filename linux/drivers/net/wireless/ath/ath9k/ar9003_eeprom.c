/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude "hw.h"
#incwude "aw9003_phy.h"
#incwude "aw9003_eepwom.h"
#incwude "aw9003_mci.h"

#define COMP_HDW_WEN 4
#define COMP_CKSUM_WEN 2

#define WE16(x) cpu_to_we16(x)
#define WE32(x) cpu_to_we32(x)

/* Wocaw defines to distinguish between extension and contwow CTW's */
#define EXT_ADDITIVE (0x8000)
#define CTW_11A_EXT (CTW_11A | EXT_ADDITIVE)
#define CTW_11G_EXT (CTW_11G | EXT_ADDITIVE)
#define CTW_11B_EXT (CTW_11B | EXT_ADDITIVE)

#define SUB_NUM_CTW_MODES_AT_5G_40 2    /* excwuding HT40, EXT-OFDM */
#define SUB_NUM_CTW_MODES_AT_2G_40 3    /* excwuding HT40, EXT-OFDM, EXT-CCK */

#define CTW(_tpowew, _fwag) ((_tpowew) | ((_fwag) << 6))

#define EEPWOM_DATA_WEN_9485	1088

static int aw9003_hw_powew_intewpowate(int32_t x,
				       int32_t *px, int32_t *py, u_int16_t np);

static const stwuct aw9300_eepwom aw9300_defauwt = {
	.eepwomVewsion = 2,
	.tempwateVewsion = 2,
	.macAddw = {0, 2, 3, 4, 5, 6},
	.custData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		     0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	.baseEepHeadew = {
		.wegDmn = { WE16(0), WE16(0x1f) },
		.txwxMask =  0x77, /* 4 bits tx and 4 bits wx */
		.opCapFwags = {
			.opFwags = AW5416_OPFWAGS_11G | AW5416_OPFWAGS_11A,
			.eepMisc = AW9300_EEPMISC_WITTWE_ENDIAN,
		},
		.wfSiwent = 0,
		.bwueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes wowew byte in eepwom wocation */
		.pwwTabweOffset = AW9300_PWW_TABWE_OFFSET,
		.pawams_fow_tuning_caps = {0, 0},
		.featuweEnabwe = 0x0c,
		 /*
		  * bit0 - enabwe tx temp comp - disabwed
		  * bit1 - enabwe tx vowt comp - disabwed
		  * bit2 - enabwe fastCwock - enabwed
		  * bit3 - enabwe doubwing - enabwed
		  * bit4 - enabwe intewnaw weguwatow - disabwed
		  * bit5 - enabwe pa pwedistowtion - disabwed
		  */
		.miscConfiguwation = 0, /* bit0 - tuwn down dwivestwength */
		.eepwomWwiteEnabweGpio = 3,
		.wwanDisabweGpio = 0,
		.wwanWedGpio = 8,
		.wxBandSewectGpio = 0xff,
		.txwxgain = 0,
		.swweg = 0,
	 },
	.modawHeadew2G = {
	/* aw9300_modaw_eep_headew  2g */
		/* 4 idwe,t1,t2,b(4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
		.antCtwwCommon2 = WE32(0x22222),

		/*
		 * antCtwwChain[AW9300_MAX_CHAINS]; 6 idwe, t, w,
		 * wx1, wx12, b (2 bits each)
		 */
		.antCtwwChain = { WE16(0x150), WE16(0x150), WE16(0x150) },

		/*
		 * xatten1DB[AW9300_MAX_CHAINS];  3 xatten1_db
		 * fow aw9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow aw9280 (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 36,
		.vowtSwope = 0,

		/*
		 * spuwChans[OSPWEY_EEPWOM_MODAW_SPUWS]; spuw
		 * channews in usuaw fbin coding fowmat
		 */
		.spuwChans = {0, 0, 0, 0, 0},

		/*
		 * noiseFwoowThweshCh[AW9300_MAX_CHAINS]; 3 Check
		 * if the wegistew is pew chain
		 */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2c,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0cf0e0e0),
		.papdWateMaskHt40 = WE32(0x6cf0e0e0),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	.base_ext1 = {
		.ant_div_contwow = 0,
		.futuwe = {0, 0},
		.tempswopextension = {0, 0, 0, 0, 0, 0, 0, 0}
	},
	.cawFweqPiew2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1),
	 },
	/* aw9300_caw_data_pew_fweq_op_woop 2g */
	.cawPiewData2G = {
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
	 },
	.cawTawget_fweqbin_Cck = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2484, 1),
	 },
	.cawTawget_fweqbin_2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT20 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT40 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawgetPowewCck = {
		 /* 1W-5W,5S,11W,11S */
		 { {36, 36, 36, 36} },
		 { {36, 36, 36, 36} },
	},
	.cawTawgetPowew2G = {
		 /* 6-24,36,48,54 */
		 { {32, 32, 28, 24} },
		 { {32, 32, 28, 24} },
		 { {32, 32, 28, 24} },
	},
	.cawTawgetPowew2GHT20 = {
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
	},
	.cawTawgetPowew2GHT40 = {
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
		{ {32, 32, 32, 32, 28, 20, 32, 32, 28, 20, 32, 32, 28, 20} },
	},
	.ctwIndex_2G =  {
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	},
	.ctw_fweqbin_2G = {
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2457, 1),
			FWEQ2FBIN(2462, 1)
		},
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},

		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},
		{
			FWEQ2FBIN(2422, 1),
			FWEQ2FBIN(2427, 1),
			FWEQ2FBIN(2447, 1),
			FWEQ2FBIN(2452, 1)
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(2484, 1),
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
		},

		{
			/* Data[9].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[9].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[9].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[10].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[10].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[10].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[11].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[11].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[11].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[11].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		}
	 },
	.ctwPowewData_2G = {
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 1) } },

		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
	 },
	.modawHeadew5G = {
		/* 4 idwe,t1,t2,b (4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2,wa2w2,wa12 */
		.antCtwwCommon2 = WE32(0x22222),
		 /* antCtwwChain 6 idwe, t,w,wx1,wx12,b (2 bits each) */
		.antCtwwChain = {
			WE16(0x000), WE16(0x000), WE16(0x000),
		},
		 /* xatten1DB 3 xatten1_db fow AW9280 (0xa20c/b20c 5:0) */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow mewwin (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 68,
		.vowtSwope = 0,
		/* spuwChans spuw channews in usuaw fbin coding fowmat */
		.spuwChans = {0, 0, 0, 0, 0},
		/* noiseFwoowThweshCh Check if the wegistew is pew chain */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2d,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0c80c080),
		.papdWateMaskHt40 = WE32(0x0080c080),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	.base_ext2 = {
		.tempSwopeWow = 0,
		.tempSwopeHigh = 0,
		.xatten1DBWow = {0, 0, 0},
		.xatten1MawginWow = {0, 0, 0},
		.xatten1DBHigh = {0, 0, 0},
		.xatten1MawginHigh = {0, 0, 0}
	},
	.cawFweqPiew5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawPiewData5G = {
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},

	},
	.cawTawget_fweqbin_5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT20 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT40 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	 },
	.cawTawgetPowew5G = {
		/* 6-24,36,48,54 */
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
		{ {20, 20, 20, 10} },
	 },
	.cawTawgetPowew5GHT20 = {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
	 },
	.cawTawgetPowew5GHT40 =  {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
		{ {20, 20, 10, 10, 0, 0, 10, 10, 0, 0, 10, 10, 0, 0} },
	 },
	.ctwIndex_5G =  {
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	},
	.ctw_fweqbin_5G =  {
		{
			/* Data[0].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[0].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[0].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[0].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[0].ctwEdges[4].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[0].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[0].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[0].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},
		{
			/* Data[1].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[1].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[1].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[1].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[1].ctwEdges[4].bChannew */ FWEQ2FBIN(5520, 0),
			/* Data[1].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[1].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[1].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[2].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[2].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[2].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[2].ctwEdges[3].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[2].ctwEdges[4].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[2].ctwEdges[5].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[2].ctwEdges[6].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[2].ctwEdges[7].bChannew */ FWEQ2FBIN(5755, 0)
		},

		{
			/* Data[3].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[3].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[3].ctwEdges[2].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[3].ctwEdges[3].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[3].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[3].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[3].ctwEdges[6].bChannew */ 0xFF,
			/* Data[3].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[4].ctwEdges[4].bChannew */ 0xFF,
			/* Data[4].ctwEdges[5].bChannew */ 0xFF,
			/* Data[4].ctwEdges[6].bChannew */ 0xFF,
			/* Data[4].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[5].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[5].ctwEdges[4].bChannew */ FWEQ2FBIN(5590, 0),
			/* Data[5].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[5].ctwEdges[6].bChannew */ 0xFF,
			/* Data[5].ctwEdges[7].bChannew */ 0xFF
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[6].ctwEdges[2].bChannew */ FWEQ2FBIN(5220, 0),
			/* Data[6].ctwEdges[3].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[6].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[6].ctwEdges[5].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[6].ctwEdges[6].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[6].ctwEdges[7].bChannew */ FWEQ2FBIN(5745, 0)
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[7].ctwEdges[4].bChannew */ FWEQ2FBIN(5560, 0),
			/* Data[7].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[7].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[7].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[8].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[8].ctwEdges[4].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[8].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[8].ctwEdges[6].bChannew */ FWEQ2FBIN(5755, 0),
			/* Data[8].ctwEdges[7].bChannew */ FWEQ2FBIN(5795, 0)
		}
	 },
	.ctwPowewData_5G = {
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 0), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 0), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
			}
		},
	 }
};

static const stwuct aw9300_eepwom aw9300_x113 = {
	.eepwomVewsion = 2,
	.tempwateVewsion = 6,
	.macAddw = {0x00, 0x03, 0x7f, 0x0, 0x0, 0x0},
	.custData = {"x113-023-f0000"},
	.baseEepHeadew = {
		.wegDmn = { WE16(0), WE16(0x1f) },
		.txwxMask =  0x77, /* 4 bits tx and 4 bits wx */
		.opCapFwags = {
			.opFwags = AW5416_OPFWAGS_11A,
			.eepMisc = AW9300_EEPMISC_WITTWE_ENDIAN,
		},
		.wfSiwent = 0,
		.bwueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes wowew byte in eepwom wocation */
		.pwwTabweOffset = AW9300_PWW_TABWE_OFFSET,
		.pawams_fow_tuning_caps = {0, 0},
		.featuweEnabwe = 0x0d,
		 /*
		  * bit0 - enabwe tx temp comp - disabwed
		  * bit1 - enabwe tx vowt comp - disabwed
		  * bit2 - enabwe fastCwock - enabwed
		  * bit3 - enabwe doubwing - enabwed
		  * bit4 - enabwe intewnaw weguwatow - disabwed
		  * bit5 - enabwe pa pwedistowtion - disabwed
		  */
		.miscConfiguwation = 0, /* bit0 - tuwn down dwivestwength */
		.eepwomWwiteEnabweGpio = 6,
		.wwanDisabweGpio = 0,
		.wwanWedGpio = 8,
		.wxBandSewectGpio = 0xff,
		.txwxgain = 0x21,
		.swweg = 0,
	 },
	.modawHeadew2G = {
	/* aw9300_modaw_eep_headew  2g */
		/* 4 idwe,t1,t2,b(4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
		.antCtwwCommon2 = WE32(0x44444),

		/*
		 * antCtwwChain[AW9300_MAX_CHAINS]; 6 idwe, t, w,
		 * wx1, wx12, b (2 bits each)
		 */
		.antCtwwChain = { WE16(0x150), WE16(0x150), WE16(0x150) },

		/*
		 * xatten1DB[AW9300_MAX_CHAINS];  3 xatten1_db
		 * fow aw9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow aw9280 (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 25,
		.vowtSwope = 0,

		/*
		 * spuwChans[OSPWEY_EEPWOM_MODAW_SPUWS]; spuw
		 * channews in usuaw fbin coding fowmat
		 */
		.spuwChans = {FWEQ2FBIN(2464, 1), 0, 0, 0, 0},

		/*
		 * noiseFwoowThweshCh[AW9300_MAX_CHAINS]; 3 Check
		 * if the wegistew is pew chain
		 */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2c,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0c80c080),
		.papdWateMaskHt40 = WE32(0x0080c080),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	 .base_ext1 = {
		.ant_div_contwow = 0,
		.futuwe = {0, 0},
		.tempswopextension = {0, 0, 0, 0, 0, 0, 0, 0}
	 },
	.cawFweqPiew2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1),
	 },
	/* aw9300_caw_data_pew_fweq_op_woop 2g */
	.cawPiewData2G = {
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
	 },
	.cawTawget_fweqbin_Cck = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2472, 1),
	 },
	.cawTawget_fweqbin_2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT20 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT40 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawgetPowewCck = {
		 /* 1W-5W,5S,11W,11S */
		 { {34, 34, 34, 34} },
		 { {34, 34, 34, 34} },
	},
	.cawTawgetPowew2G = {
		 /* 6-24,36,48,54 */
		 { {34, 34, 32, 32} },
		 { {34, 34, 32, 32} },
		 { {34, 34, 32, 32} },
	},
	.cawTawgetPowew2GHT20 = {
		{ {32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0} },
		{ {32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0} },
		{ {32, 32, 32, 32, 32, 28, 32, 32, 30, 28, 0, 0, 0, 0} },
	},
	.cawTawgetPowew2GHT40 = {
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
	},
	.ctwIndex_2G =  {
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	},
	.ctw_fweqbin_2G = {
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2457, 1),
			FWEQ2FBIN(2462, 1)
		},
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},

		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},
		{
			FWEQ2FBIN(2422, 1),
			FWEQ2FBIN(2427, 1),
			FWEQ2FBIN(2447, 1),
			FWEQ2FBIN(2452, 1)
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(2484, 1),
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
		},

		{
			/* Data[9].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[9].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[9].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[10].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[10].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[10].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[11].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[11].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[11].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[11].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		}
	 },
	.ctwPowewData_2G = {
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 1) } },

		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
	 },
	.modawHeadew5G = {
		/* 4 idwe,t1,t2,b (4 bits pew setting) */
		.antCtwwCommon = WE32(0x220),
		/* 4 wa1w1, wa2w1, wa1w2,wa2w2,wa12 */
		.antCtwwCommon2 = WE32(0x11111),
		 /* antCtwwChain 6 idwe, t,w,wx1,wx12,b (2 bits each) */
		.antCtwwChain = {
			WE16(0x150), WE16(0x150), WE16(0x150),
		},
		 /* xatten1DB 3 xatten1_db fow AW9280 (0xa20c/b20c 5:0) */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow mewwin (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 68,
		.vowtSwope = 0,
		/* spuwChans spuw channews in usuaw fbin coding fowmat */
		.spuwChans = {FWEQ2FBIN(5500, 0), 0, 0, 0, 0},
		/* noiseFwoowThweshCh Check if the wegistew is pew chain */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0xf,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2d,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0cf0e0e0),
		.papdWateMaskHt40 = WE32(0x6cf0e0e0),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	.base_ext2 = {
		.tempSwopeWow = 72,
		.tempSwopeHigh = 105,
		.xatten1DBWow = {0, 0, 0},
		.xatten1MawginWow = {0, 0, 0},
		.xatten1DBHigh = {0, 0, 0},
		.xatten1MawginHigh = {0, 0, 0}
	 },
	.cawFweqPiew5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5785, 0)
	},
	.cawPiewData5G = {
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},

	},
	.cawTawget_fweqbin_5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5785, 0)
	},
	.cawTawget_fweqbin_5GHT20 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT40 = {
		FWEQ2FBIN(5190, 0),
		FWEQ2FBIN(5230, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5410, 0),
		FWEQ2FBIN(5510, 0),
		FWEQ2FBIN(5670, 0),
		FWEQ2FBIN(5755, 0),
		FWEQ2FBIN(5825, 0)
	 },
	.cawTawgetPowew5G = {
		/* 6-24,36,48,54 */
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
		{ {42, 40, 40, 34} },
	 },
	.cawTawgetPowew5GHT20 = {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {40, 40, 40, 40, 32, 28, 40, 40, 32, 28, 40, 40, 32, 20} },
		{ {38, 38, 38, 38, 32, 28, 38, 38, 32, 28, 38, 38, 32, 26} },
		{ {36, 36, 36, 36, 32, 28, 36, 36, 32, 28, 36, 36, 32, 26} },
	 },
	.cawTawgetPowew5GHT40 =  {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {40, 40, 40, 38, 30, 26, 40, 40, 30, 26, 40, 40, 30, 24} },
		{ {36, 36, 36, 36, 30, 26, 36, 36, 30, 26, 36, 36, 30, 24} },
		{ {34, 34, 34, 34, 30, 26, 34, 34, 30, 26, 34, 34, 30, 24} },
	 },
	.ctwIndex_5G =  {
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	},
	.ctw_fweqbin_5G =  {
		{
			/* Data[0].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[0].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[0].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[0].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[0].ctwEdges[4].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[0].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[0].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[0].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},
		{
			/* Data[1].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[1].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[1].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[1].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[1].ctwEdges[4].bChannew */ FWEQ2FBIN(5520, 0),
			/* Data[1].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[1].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[1].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[2].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[2].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[2].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[2].ctwEdges[3].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[2].ctwEdges[4].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[2].ctwEdges[5].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[2].ctwEdges[6].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[2].ctwEdges[7].bChannew */ FWEQ2FBIN(5755, 0)
		},

		{
			/* Data[3].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[3].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[3].ctwEdges[2].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[3].ctwEdges[3].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[3].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[3].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[3].ctwEdges[6].bChannew */ 0xFF,
			/* Data[3].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[4].ctwEdges[4].bChannew */ 0xFF,
			/* Data[4].ctwEdges[5].bChannew */ 0xFF,
			/* Data[4].ctwEdges[6].bChannew */ 0xFF,
			/* Data[4].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[5].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[5].ctwEdges[4].bChannew */ FWEQ2FBIN(5590, 0),
			/* Data[5].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[5].ctwEdges[6].bChannew */ 0xFF,
			/* Data[5].ctwEdges[7].bChannew */ 0xFF
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[6].ctwEdges[2].bChannew */ FWEQ2FBIN(5220, 0),
			/* Data[6].ctwEdges[3].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[6].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[6].ctwEdges[5].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[6].ctwEdges[6].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[6].ctwEdges[7].bChannew */ FWEQ2FBIN(5745, 0)
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[7].ctwEdges[4].bChannew */ FWEQ2FBIN(5560, 0),
			/* Data[7].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[7].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[7].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[8].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[8].ctwEdges[4].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[8].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[8].ctwEdges[6].bChannew */ FWEQ2FBIN(5755, 0),
			/* Data[8].ctwEdges[7].bChannew */ FWEQ2FBIN(5795, 0)
		}
	 },
	.ctwPowewData_5G = {
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 0), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 0), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
			}
		},
	 }
};


static const stwuct aw9300_eepwom aw9300_h112 = {
	.eepwomVewsion = 2,
	.tempwateVewsion = 3,
	.macAddw = {0x00, 0x03, 0x7f, 0x0, 0x0, 0x0},
	.custData = {"h112-241-f0000"},
	.baseEepHeadew = {
		.wegDmn = { WE16(0), WE16(0x1f) },
		.txwxMask =  0x77, /* 4 bits tx and 4 bits wx */
		.opCapFwags = {
			.opFwags = AW5416_OPFWAGS_11G | AW5416_OPFWAGS_11A,
			.eepMisc = AW9300_EEPMISC_WITTWE_ENDIAN,
		},
		.wfSiwent = 0,
		.bwueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes wowew byte in eepwom wocation */
		.pwwTabweOffset = AW9300_PWW_TABWE_OFFSET,
		.pawams_fow_tuning_caps = {0, 0},
		.featuweEnabwe = 0x0d,
		/*
		 * bit0 - enabwe tx temp comp - disabwed
		 * bit1 - enabwe tx vowt comp - disabwed
		 * bit2 - enabwe fastCwock - enabwed
		 * bit3 - enabwe doubwing - enabwed
		 * bit4 - enabwe intewnaw weguwatow - disabwed
		 * bit5 - enabwe pa pwedistowtion - disabwed
		 */
		.miscConfiguwation = 0, /* bit0 - tuwn down dwivestwength */
		.eepwomWwiteEnabweGpio = 6,
		.wwanDisabweGpio = 0,
		.wwanWedGpio = 8,
		.wxBandSewectGpio = 0xff,
		.txwxgain = 0x10,
		.swweg = 0,
	},
	.modawHeadew2G = {
		/* aw9300_modaw_eep_headew  2g */
		/* 4 idwe,t1,t2,b(4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
		.antCtwwCommon2 = WE32(0x44444),

		/*
		 * antCtwwChain[AW9300_MAX_CHAINS]; 6 idwe, t, w,
		 * wx1, wx12, b (2 bits each)
		 */
		.antCtwwChain = { WE16(0x150), WE16(0x150), WE16(0x150) },

		/*
		 * xatten1DB[AW9300_MAX_CHAINS];  3 xatten1_db
		 * fow aw9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow aw9280 (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 25,
		.vowtSwope = 0,

		/*
		 * spuwChans[OSPWEY_EEPWOM_MODAW_SPUWS]; spuw
		 * channews in usuaw fbin coding fowmat
		 */
		.spuwChans = {FWEQ2FBIN(2464, 1), 0, 0, 0, 0},

		/*
		 * noiseFwoowThweshCh[AW9300_MAX_CHAINS]; 3 Check
		 * if the wegistew is pew chain
		 */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2c,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0c80c080),
		.papdWateMaskHt40 = WE32(0x0080c080),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	},
	.base_ext1 = {
		.ant_div_contwow = 0,
		.futuwe = {0, 0},
		.tempswopextension = {0, 0, 0, 0, 0, 0, 0, 0}
	},
	.cawFweqPiew2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2462, 1),
	},
	/* aw9300_caw_data_pew_fweq_op_woop 2g */
	.cawPiewData2G = {
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
	},
	.cawTawget_fweqbin_Cck = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2472, 1),
	},
	.cawTawget_fweqbin_2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawget_fweqbin_2GHT20 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawget_fweqbin_2GHT40 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawgetPowewCck = {
		/* 1W-5W,5S,11W,11S */
		{ {34, 34, 34, 34} },
		{ {34, 34, 34, 34} },
	},
	.cawTawgetPowew2G = {
		/* 6-24,36,48,54 */
		{ {34, 34, 32, 32} },
		{ {34, 34, 32, 32} },
		{ {34, 34, 32, 32} },
	},
	.cawTawgetPowew2GHT20 = {
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24} },
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24} },
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 28, 28, 28, 24} },
	},
	.cawTawgetPowew2GHT40 = {
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 26, 26, 26, 22} },
	},
	.ctwIndex_2G =  {
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	},
	.ctw_fweqbin_2G = {
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2457, 1),
			FWEQ2FBIN(2462, 1)
		},
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},

		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},
		{
			FWEQ2FBIN(2422, 1),
			FWEQ2FBIN(2427, 1),
			FWEQ2FBIN(2447, 1),
			FWEQ2FBIN(2452, 1)
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(2484, 1),
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
		},

		{
			/* Data[9].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[9].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[9].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[10].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[10].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[10].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[11].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[11].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[11].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[11].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		}
	},
	.ctwPowewData_2G = {
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 1) } },

		{ { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
	},
	.modawHeadew5G = {
		/* 4 idwe,t1,t2,b (4 bits pew setting) */
		.antCtwwCommon = WE32(0x220),
		/* 4 wa1w1, wa2w1, wa1w2,wa2w2,wa12 */
		.antCtwwCommon2 = WE32(0x44444),
		/* antCtwwChain 6 idwe, t,w,wx1,wx12,b (2 bits each) */
		.antCtwwChain = {
			WE16(0x150), WE16(0x150), WE16(0x150),
		},
		/* xatten1DB 3 xatten1_db fow AW9280 (0xa20c/b20c 5:0) */
		.xatten1DB = {0, 0, 0},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow mewwin (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0, 0, 0},
		.tempSwope = 45,
		.vowtSwope = 0,
		/* spuwChans spuw channews in usuaw fbin coding fowmat */
		.spuwChans = {0, 0, 0, 0, 0},
		/* noiseFwoowThweshCh Check if the wegistew is pew chain */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2d,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0cf0e0e0),
		.papdWateMaskHt40 = WE32(0x6cf0e0e0),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	},
	.base_ext2 = {
		.tempSwopeWow = 40,
		.tempSwopeHigh = 50,
		.xatten1DBWow = {0, 0, 0},
		.xatten1MawginWow = {0, 0, 0},
		.xatten1DBHigh = {0, 0, 0},
		.xatten1MawginHigh = {0, 0, 0}
	},
	.cawFweqPiew5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5785, 0)
	},
	.cawPiewData5G = {
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},

	},
	.cawTawget_fweqbin_5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT20 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT40 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawgetPowew5G = {
		/* 6-24,36,48,54 */
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
	},
	.cawTawgetPowew5GHT20 = {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 20, 20, 20, 16} },
		{ {30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 20, 20, 20, 16} },
		{ {30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 18, 18, 18, 16} },
		{ {30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 18, 18, 18, 16} },
		{ {30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 16, 16, 16, 14} },
		{ {30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 16, 16, 16, 14} },
		{ {30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 14, 14, 14, 12} },
		{ {30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 14, 14, 14, 12} },
	},
	.cawTawgetPowew5GHT40 =  {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 18, 18, 18, 14} },
		{ {28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 18, 18, 18, 14} },
		{ {28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 16, 16, 16, 12} },
		{ {28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 16, 16, 16, 12} },
		{ {28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 14, 14, 14, 10} },
		{ {28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 14, 14, 14, 10} },
		{ {28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 12, 12, 12, 8} },
		{ {28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 12, 12, 12, 8} },
	},
	.ctwIndex_5G =  {
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	},
	.ctw_fweqbin_5G =  {
		{
			/* Data[0].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[0].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[0].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[0].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[0].ctwEdges[4].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[0].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[0].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[0].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},
		{
			/* Data[1].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[1].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[1].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[1].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[1].ctwEdges[4].bChannew */ FWEQ2FBIN(5520, 0),
			/* Data[1].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[1].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[1].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[2].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[2].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[2].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[2].ctwEdges[3].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[2].ctwEdges[4].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[2].ctwEdges[5].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[2].ctwEdges[6].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[2].ctwEdges[7].bChannew */ FWEQ2FBIN(5755, 0)
		},

		{
			/* Data[3].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[3].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[3].ctwEdges[2].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[3].ctwEdges[3].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[3].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[3].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[3].ctwEdges[6].bChannew */ 0xFF,
			/* Data[3].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[4].ctwEdges[4].bChannew */ 0xFF,
			/* Data[4].ctwEdges[5].bChannew */ 0xFF,
			/* Data[4].ctwEdges[6].bChannew */ 0xFF,
			/* Data[4].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[5].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[5].ctwEdges[4].bChannew */ FWEQ2FBIN(5590, 0),
			/* Data[5].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[5].ctwEdges[6].bChannew */ 0xFF,
			/* Data[5].ctwEdges[7].bChannew */ 0xFF
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[6].ctwEdges[2].bChannew */ FWEQ2FBIN(5220, 0),
			/* Data[6].ctwEdges[3].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[6].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[6].ctwEdges[5].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[6].ctwEdges[6].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[6].ctwEdges[7].bChannew */ FWEQ2FBIN(5745, 0)
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[7].ctwEdges[4].bChannew */ FWEQ2FBIN(5560, 0),
			/* Data[7].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[7].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[7].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[8].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[8].ctwEdges[4].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[8].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[8].ctwEdges[6].bChannew */ FWEQ2FBIN(5755, 0),
			/* Data[8].ctwEdges[7].bChannew */ FWEQ2FBIN(5795, 0)
		}
	},
	.ctwPowewData_5G = {
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 0), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 0), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
			}
		},
	}
};


static const stwuct aw9300_eepwom aw9300_x112 = {
	.eepwomVewsion = 2,
	.tempwateVewsion = 5,
	.macAddw = {0x00, 0x03, 0x7f, 0x0, 0x0, 0x0},
	.custData = {"x112-041-f0000"},
	.baseEepHeadew = {
		.wegDmn = { WE16(0), WE16(0x1f) },
		.txwxMask =  0x77, /* 4 bits tx and 4 bits wx */
		.opCapFwags = {
			.opFwags = AW5416_OPFWAGS_11G | AW5416_OPFWAGS_11A,
			.eepMisc = AW9300_EEPMISC_WITTWE_ENDIAN,
		},
		.wfSiwent = 0,
		.bwueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes wowew byte in eepwom wocation */
		.pwwTabweOffset = AW9300_PWW_TABWE_OFFSET,
		.pawams_fow_tuning_caps = {0, 0},
		.featuweEnabwe = 0x0d,
		/*
		 * bit0 - enabwe tx temp comp - disabwed
		 * bit1 - enabwe tx vowt comp - disabwed
		 * bit2 - enabwe fastcwock - enabwed
		 * bit3 - enabwe doubwing - enabwed
		 * bit4 - enabwe intewnaw weguwatow - disabwed
		 * bit5 - enabwe pa pwedistowtion - disabwed
		 */
		.miscConfiguwation = 0, /* bit0 - tuwn down dwivestwength */
		.eepwomWwiteEnabweGpio = 6,
		.wwanDisabweGpio = 0,
		.wwanWedGpio = 8,
		.wxBandSewectGpio = 0xff,
		.txwxgain = 0x0,
		.swweg = 0,
	},
	.modawHeadew2G = {
		/* aw9300_modaw_eep_headew  2g */
		/* 4 idwe,t1,t2,b(4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
		.antCtwwCommon2 = WE32(0x22222),

		/*
		 * antCtwwChain[aw9300_max_chains]; 6 idwe, t, w,
		 * wx1, wx12, b (2 bits each)
		 */
		.antCtwwChain = { WE16(0x10), WE16(0x10), WE16(0x10) },

		/*
		 * xatten1DB[AW9300_max_chains];  3 xatten1_db
		 * fow aw9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = {0x1b, 0x1b, 0x1b},

		/*
		 * xatten1Mawgin[aw9300_max_chains]; 3 xatten1_mawgin
		 * fow aw9280 (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0x15, 0x15, 0x15},
		.tempSwope = 50,
		.vowtSwope = 0,

		/*
		 * spuwChans[OSPwey_eepwom_modaw_sPUWS]; spuw
		 * channews in usuaw fbin coding fowmat
		 */
		.spuwChans = {FWEQ2FBIN(2464, 1), 0, 0, 0, 0},

		/*
		 * noiseFwoowThweshch[aw9300_max_cHAINS]; 3 Check
		 * if the wegistew is pew chain
		 */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2c,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0c80c080),
		.papdWateMaskHt40 = WE32(0x0080c080),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	},
	.base_ext1 = {
		.ant_div_contwow = 0,
		.futuwe = {0, 0},
		.tempswopextension = {0, 0, 0, 0, 0, 0, 0, 0}
	},
	.cawFweqPiew2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1),
	},
	/* aw9300_caw_data_pew_fweq_op_woop 2g */
	.cawPiewData2G = {
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
	},
	.cawTawget_fweqbin_Cck = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2472, 1),
	},
	.cawTawget_fweqbin_2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawget_fweqbin_2GHT20 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawget_fweqbin_2GHT40 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	},
	.cawTawgetPowewCck = {
		/* 1W-5W,5S,11W,11s */
		{ {38, 38, 38, 38} },
		{ {38, 38, 38, 38} },
	},
	.cawTawgetPowew2G = {
		/* 6-24,36,48,54 */
		{ {38, 38, 36, 34} },
		{ {38, 38, 36, 34} },
		{ {38, 38, 34, 32} },
	},
	.cawTawgetPowew2GHT20 = {
		{ {36, 36, 36, 36, 36, 34, 34, 32, 30, 28, 28, 28, 28, 26} },
		{ {36, 36, 36, 36, 36, 34, 36, 34, 32, 30, 30, 30, 28, 26} },
		{ {36, 36, 36, 36, 36, 34, 34, 32, 30, 28, 28, 28, 28, 26} },
	},
	.cawTawgetPowew2GHT40 = {
		{ {36, 36, 36, 36, 34, 32, 32, 30, 28, 26, 26, 26, 26, 24} },
		{ {36, 36, 36, 36, 34, 32, 34, 32, 30, 28, 28, 28, 28, 24} },
		{ {36, 36, 36, 36, 34, 32, 32, 30, 28, 26, 26, 26, 26, 24} },
	},
	.ctwIndex_2G =  {
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	},
	.ctw_fweqbin_2G = {
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2457, 1),
			FWEQ2FBIN(2462, 1)
		},
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},

		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},
		{
			FWEQ2FBIN(2422, 1),
			FWEQ2FBIN(2427, 1),
			FWEQ2FBIN(2447, 1),
			FWEQ2FBIN(2452, 1)
		},

		{
			/* Data[4].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[4].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			/* Data[4].ctwedges[2].bchannew */ FWEQ2FBIN(2472, 1),
			/* Data[4].ctwedges[3].bchannew */ FWEQ2FBIN(2484, 1),
		},

		{
			/* Data[5].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[5].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			/* Data[5].ctwedges[2].bchannew */ FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[6].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[6].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[7].ctwedges[0].bchannew */ FWEQ2FBIN(2422, 1),
			/* Data[7].ctwedges[1].bchannew */ FWEQ2FBIN(2427, 1),
			/* Data[7].ctwedges[2].bchannew */ FWEQ2FBIN(2447, 1),
			/* Data[7].ctwedges[3].bchannew */ FWEQ2FBIN(2462, 1),
		},

		{
			/* Data[8].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[8].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			/* Data[8].ctwedges[2].bchannew */ FWEQ2FBIN(2472, 1),
		},

		{
			/* Data[9].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[9].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			/* Data[9].ctwedges[2].bchannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[10].ctwedges[0].bchannew */ FWEQ2FBIN(2412, 1),
			/* Data[10].ctwedges[1].bchannew */ FWEQ2FBIN(2417, 1),
			/* Data[10].ctwedges[2].bchannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[11].ctwedges[0].bchannew */ FWEQ2FBIN(2422, 1),
			/* Data[11].ctwedges[1].bchannew */ FWEQ2FBIN(2427, 1),
			/* Data[11].ctwedges[2].bchannew */ FWEQ2FBIN(2447, 1),
			/* Data[11].ctwedges[3].bchannew */ FWEQ2FBIN(2462, 1),
		}
	},
	.ctwPowewData_2G = {
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 1) } },

		{ { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		{ { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
		{ { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
	},
	.modawHeadew5G = {
		/* 4 idwe,t1,t2,b (4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2,wa2w2,wa12 */
		.antCtwwCommon2 = WE32(0x22222),
		/* antCtwwChain 6 idwe, t,w,wx1,wx12,b (2 bits each) */
		.antCtwwChain = {
			WE16(0x0), WE16(0x0), WE16(0x0),
		},
		/* xatten1DB 3 xatten1_db fow aw9280 (0xa20c/b20c 5:0) */
		.xatten1DB = {0x13, 0x19, 0x17},

		/*
		 * xatten1Mawgin[aw9300_max_chains]; 3 xatten1_mawgin
		 * fow mewwin (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0x19, 0x19, 0x19},
		.tempSwope = 70,
		.vowtSwope = 15,
		/* spuwChans spuw channews in usuaw fbin coding fowmat */
		.spuwChans = {0, 0, 0, 0, 0},
		/* noiseFwoowThweshch check if the wegistew is pew chain */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2d,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0cf0e0e0),
		.papdWateMaskHt40 = WE32(0x6cf0e0e0),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	},
	.base_ext2 = {
		.tempSwopeWow = 72,
		.tempSwopeHigh = 105,
		.xatten1DBWow = {0x10, 0x14, 0x10},
		.xatten1MawginWow = {0x19, 0x19 , 0x19},
		.xatten1DBHigh = {0x1d, 0x20, 0x24},
		.xatten1MawginHigh = {0x10, 0x10, 0x10}
	},
	.cawFweqPiew5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5785, 0)
	},
	.cawPiewData5G = {
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
		},

	},
	.cawTawget_fweqbin_5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT20 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT40 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5725, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawgetPowew5G = {
		/* 6-24,36,48,54 */
		{ {32, 32, 28, 26} },
		{ {32, 32, 28, 26} },
		{ {32, 32, 28, 26} },
		{ {32, 32, 26, 24} },
		{ {32, 32, 26, 24} },
		{ {32, 32, 24, 22} },
		{ {30, 30, 24, 22} },
		{ {30, 30, 24, 22} },
	},
	.cawTawgetPowew5GHT20 = {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 32, 28, 26, 32, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 32, 28, 26, 32, 26, 24, 22, 22, 22, 20, 20} },
		{ {32, 32, 32, 32, 28, 26, 32, 26, 24, 22, 20, 18, 16, 16} },
		{ {32, 32, 32, 32, 28, 26, 32, 24, 20, 16, 18, 16, 14, 14} },
		{ {30, 30, 30, 30, 28, 26, 30, 24, 20, 16, 18, 16, 14, 14} },
		{ {30, 30, 30, 30, 28, 26, 30, 24, 20, 16, 18, 16, 14, 14} },
	},
	.cawTawgetPowew5GHT40 =  {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 30, 28, 26, 30, 28, 26, 24, 24, 24, 22, 22} },
		{ {32, 32, 32, 30, 28, 26, 30, 26, 24, 22, 22, 22, 20, 20} },
		{ {32, 32, 32, 30, 28, 26, 30, 26, 24, 22, 20, 18, 16, 16} },
		{ {32, 32, 32, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14} },
		{ {30, 30, 30, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14} },
		{ {30, 30, 30, 30, 28, 26, 30, 22, 20, 16, 18, 16, 14, 14} },
	},
	.ctwIndex_5G =  {
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	},
	.ctw_fweqbin_5G =  {
		{
			/* Data[0].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[0].ctwedges[1].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[0].ctwedges[2].bchannew */ FWEQ2FBIN(5280, 0),
			/* Data[0].ctwedges[3].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[0].ctwedges[4].bchannew */ FWEQ2FBIN(5600, 0),
			/* Data[0].ctwedges[5].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[0].ctwedges[6].bchannew */ FWEQ2FBIN(5745, 0),
			/* Data[0].ctwedges[7].bchannew */ FWEQ2FBIN(5825, 0)
		},
		{
			/* Data[1].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[1].ctwedges[1].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[1].ctwedges[2].bchannew */ FWEQ2FBIN(5280, 0),
			/* Data[1].ctwedges[3].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[1].ctwedges[4].bchannew */ FWEQ2FBIN(5520, 0),
			/* Data[1].ctwedges[5].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[1].ctwedges[6].bchannew */ FWEQ2FBIN(5745, 0),
			/* Data[1].ctwedges[7].bchannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[2].ctwedges[0].bchannew */ FWEQ2FBIN(5190, 0),
			/* Data[2].ctwedges[1].bchannew */ FWEQ2FBIN(5230, 0),
			/* Data[2].ctwedges[2].bchannew */ FWEQ2FBIN(5270, 0),
			/* Data[2].ctwedges[3].bchannew */ FWEQ2FBIN(5310, 0),
			/* Data[2].ctwedges[4].bchannew */ FWEQ2FBIN(5510, 0),
			/* Data[2].ctwedges[5].bchannew */ FWEQ2FBIN(5550, 0),
			/* Data[2].ctwedges[6].bchannew */ FWEQ2FBIN(5670, 0),
			/* Data[2].ctwedges[7].bchannew */ FWEQ2FBIN(5755, 0)
		},

		{
			/* Data[3].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[3].ctwedges[1].bchannew */ FWEQ2FBIN(5200, 0),
			/* Data[3].ctwedges[2].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[3].ctwedges[3].bchannew */ FWEQ2FBIN(5320, 0),
			/* Data[3].ctwedges[4].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[3].ctwedges[5].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[3].ctwedges[6].bchannew */ 0xFF,
			/* Data[3].ctwedges[7].bchannew */ 0xFF,
		},

		{
			/* Data[4].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[4].ctwedges[1].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[4].ctwedges[2].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[4].ctwedges[3].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[4].ctwedges[4].bchannew */ 0xFF,
			/* Data[4].ctwedges[5].bchannew */ 0xFF,
			/* Data[4].ctwedges[6].bchannew */ 0xFF,
			/* Data[4].ctwedges[7].bchannew */ 0xFF,
		},

		{
			/* Data[5].ctwedges[0].bchannew */ FWEQ2FBIN(5190, 0),
			/* Data[5].ctwedges[1].bchannew */ FWEQ2FBIN(5270, 0),
			/* Data[5].ctwedges[2].bchannew */ FWEQ2FBIN(5310, 0),
			/* Data[5].ctwedges[3].bchannew */ FWEQ2FBIN(5510, 0),
			/* Data[5].ctwedges[4].bchannew */ FWEQ2FBIN(5590, 0),
			/* Data[5].ctwedges[5].bchannew */ FWEQ2FBIN(5670, 0),
			/* Data[5].ctwedges[6].bchannew */ 0xFF,
			/* Data[5].ctwedges[7].bchannew */ 0xFF
		},

		{
			/* Data[6].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[6].ctwedges[1].bchannew */ FWEQ2FBIN(5200, 0),
			/* Data[6].ctwedges[2].bchannew */ FWEQ2FBIN(5220, 0),
			/* Data[6].ctwedges[3].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[6].ctwedges[4].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[6].ctwedges[5].bchannew */ FWEQ2FBIN(5600, 0),
			/* Data[6].ctwedges[6].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[6].ctwedges[7].bchannew */ FWEQ2FBIN(5745, 0)
		},

		{
			/* Data[7].ctwedges[0].bchannew */ FWEQ2FBIN(5180, 0),
			/* Data[7].ctwedges[1].bchannew */ FWEQ2FBIN(5260, 0),
			/* Data[7].ctwedges[2].bchannew */ FWEQ2FBIN(5320, 0),
			/* Data[7].ctwedges[3].bchannew */ FWEQ2FBIN(5500, 0),
			/* Data[7].ctwedges[4].bchannew */ FWEQ2FBIN(5560, 0),
			/* Data[7].ctwedges[5].bchannew */ FWEQ2FBIN(5700, 0),
			/* Data[7].ctwedges[6].bchannew */ FWEQ2FBIN(5745, 0),
			/* Data[7].ctwedges[7].bchannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[8].ctwedges[0].bchannew */ FWEQ2FBIN(5190, 0),
			/* Data[8].ctwedges[1].bchannew */ FWEQ2FBIN(5230, 0),
			/* Data[8].ctwedges[2].bchannew */ FWEQ2FBIN(5270, 0),
			/* Data[8].ctwedges[3].bchannew */ FWEQ2FBIN(5510, 0),
			/* Data[8].ctwedges[4].bchannew */ FWEQ2FBIN(5550, 0),
			/* Data[8].ctwedges[5].bchannew */ FWEQ2FBIN(5670, 0),
			/* Data[8].ctwedges[6].bchannew */ FWEQ2FBIN(5755, 0),
			/* Data[8].ctwedges[7].bchannew */ FWEQ2FBIN(5795, 0)
		}
	},
	.ctwPowewData_5G = {
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 0), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 0), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
			}
		},
	}
};

static const stwuct aw9300_eepwom aw9300_h116 = {
	.eepwomVewsion = 2,
	.tempwateVewsion = 4,
	.macAddw = {0x00, 0x03, 0x7f, 0x0, 0x0, 0x0},
	.custData = {"h116-041-f0000"},
	.baseEepHeadew = {
		.wegDmn = { WE16(0), WE16(0x1f) },
		.txwxMask =  0x33, /* 4 bits tx and 4 bits wx */
		.opCapFwags = {
			.opFwags = AW5416_OPFWAGS_11G | AW5416_OPFWAGS_11A,
			.eepMisc = AW9300_EEPMISC_WITTWE_ENDIAN,
		},
		.wfSiwent = 0,
		.bwueToothOptions = 0,
		.deviceCap = 0,
		.deviceType = 5, /* takes wowew byte in eepwom wocation */
		.pwwTabweOffset = AW9300_PWW_TABWE_OFFSET,
		.pawams_fow_tuning_caps = {0, 0},
		.featuweEnabwe = 0x0d,
		 /*
		  * bit0 - enabwe tx temp comp - disabwed
		  * bit1 - enabwe tx vowt comp - disabwed
		  * bit2 - enabwe fastCwock - enabwed
		  * bit3 - enabwe doubwing - enabwed
		  * bit4 - enabwe intewnaw weguwatow - disabwed
		  * bit5 - enabwe pa pwedistowtion - disabwed
		  */
		.miscConfiguwation = 0, /* bit0 - tuwn down dwivestwength */
		.eepwomWwiteEnabweGpio = 6,
		.wwanDisabweGpio = 0,
		.wwanWedGpio = 8,
		.wxBandSewectGpio = 0xff,
		.txwxgain = 0x10,
		.swweg = 0,
	 },
	.modawHeadew2G = {
	/* aw9300_modaw_eep_headew  2g */
		/* 4 idwe,t1,t2,b(4 bits pew setting) */
		.antCtwwCommon = WE32(0x110),
		/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
		.antCtwwCommon2 = WE32(0x44444),

		/*
		 * antCtwwChain[AW9300_MAX_CHAINS]; 6 idwe, t, w,
		 * wx1, wx12, b (2 bits each)
		 */
		.antCtwwChain = { WE16(0x10), WE16(0x10), WE16(0x10) },

		/*
		 * xatten1DB[AW9300_MAX_CHAINS];  3 xatten1_db
		 * fow aw9280 (0xa20c/b20c 5:0)
		 */
		.xatten1DB = {0x1f, 0x1f, 0x1f},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow aw9280 (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0x12, 0x12, 0x12},
		.tempSwope = 25,
		.vowtSwope = 0,

		/*
		 * spuwChans[OSPWEY_EEPWOM_MODAW_SPUWS]; spuw
		 * channews in usuaw fbin coding fowmat
		 */
		.spuwChans = {FWEQ2FBIN(2464, 1), 0, 0, 0, 0},

		/*
		 * noiseFwoowThweshCh[AW9300_MAX_CHAINS]; 3 Check
		 * if the wegistew is pew chain
		 */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2c,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0c80C080),
		.papdWateMaskHt40 = WE32(0x0080C080),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	 .base_ext1 = {
		.ant_div_contwow = 0,
		.futuwe = {0, 0},
		.tempswopextension = {0, 0, 0, 0, 0, 0, 0, 0}
	 },
	.cawFweqPiew2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2462, 1),
	 },
	/* aw9300_caw_data_pew_fweq_op_woop 2g */
	.cawPiewData2G = {
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
		{ {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0} },
	 },
	.cawTawget_fweqbin_Cck = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2472, 1),
	 },
	.cawTawget_fweqbin_2G = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT20 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawget_fweqbin_2GHT40 = {
		FWEQ2FBIN(2412, 1),
		FWEQ2FBIN(2437, 1),
		FWEQ2FBIN(2472, 1)
	 },
	.cawTawgetPowewCck = {
		 /* 1W-5W,5S,11W,11S */
		 { {34, 34, 34, 34} },
		 { {34, 34, 34, 34} },
	},
	.cawTawgetPowew2G = {
		 /* 6-24,36,48,54 */
		 { {34, 34, 32, 32} },
		 { {34, 34, 32, 32} },
		 { {34, 34, 32, 32} },
	},
	.cawTawgetPowew2GHT20 = {
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0} },
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0} },
		{ {32, 32, 32, 32, 32, 30, 32, 32, 30, 28, 0, 0, 0, 0} },
	},
	.cawTawgetPowew2GHT40 = {
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
		{ {30, 30, 30, 30, 30, 28, 30, 30, 28, 26, 0, 0, 0, 0} },
	},
	.ctwIndex_2G =  {
		0x11, 0x12, 0x15, 0x17, 0x41, 0x42,
		0x45, 0x47, 0x31, 0x32, 0x35, 0x37,
	},
	.ctw_fweqbin_2G = {
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2457, 1),
			FWEQ2FBIN(2462, 1)
		},
		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},

		{
			FWEQ2FBIN(2412, 1),
			FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2462, 1),
			0xFF,
		},
		{
			FWEQ2FBIN(2422, 1),
			FWEQ2FBIN(2427, 1),
			FWEQ2FBIN(2447, 1),
			FWEQ2FBIN(2452, 1)
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(2484, 1),
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			FWEQ2FBIN(2472, 1),
			0,
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
		},

		{
			/* Data[9].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[9].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[9].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[10].ctwEdges[0].bChannew */ FWEQ2FBIN(2412, 1),
			/* Data[10].ctwEdges[1].bChannew */ FWEQ2FBIN(2417, 1),
			/* Data[10].ctwEdges[2].bChannew */ FWEQ2FBIN(2472, 1),
			0
		},

		{
			/* Data[11].ctwEdges[0].bChannew */ FWEQ2FBIN(2422, 1),
			/* Data[11].ctwEdges[1].bChannew */ FWEQ2FBIN(2427, 1),
			/* Data[11].ctwEdges[2].bChannew */ FWEQ2FBIN(2447, 1),
			/* Data[11].ctwEdges[3].bChannew */ FWEQ2FBIN(2462, 1),
		}
	 },
	.ctwPowewData_2G = {
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 1) } },

		 { { CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },

		 { { CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 0) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
		 { { CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 1) } },
	 },
	.modawHeadew5G = {
		/* 4 idwe,t1,t2,b (4 bits pew setting) */
		.antCtwwCommon = WE32(0x220),
		/* 4 wa1w1, wa2w1, wa1w2,wa2w2,wa12 */
		.antCtwwCommon2 = WE32(0x44444),
		 /* antCtwwChain 6 idwe, t,w,wx1,wx12,b (2 bits each) */
		.antCtwwChain = {
			WE16(0x150), WE16(0x150), WE16(0x150),
		},
		 /* xatten1DB 3 xatten1_db fow AW9280 (0xa20c/b20c 5:0) */
		.xatten1DB = {0x19, 0x19, 0x19},

		/*
		 * xatten1Mawgin[AW9300_MAX_CHAINS]; 3 xatten1_mawgin
		 * fow mewwin (0xa20c/b20c 16:12
		 */
		.xatten1Mawgin = {0x14, 0x14, 0x14},
		.tempSwope = 70,
		.vowtSwope = 0,
		/* spuwChans spuw channews in usuaw fbin coding fowmat */
		.spuwChans = {0, 0, 0, 0, 0},
		/* noiseFwoowThweshCh Check if the wegistew is pew chain */
		.noiseFwoowThweshCh = {-1, 0, 0},
		.wesewved = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.quick_dwop = 0,
		.xpaBiasWvw = 0,
		.txFwameToDataStawt = 0x0e,
		.txFwameToPaOn = 0x0e,
		.txCwip = 3, /* 4 bits tx_cwip, 4 bits dac_scawe_cck */
		.antennaGain = 0,
		.switchSettwing = 0x2d,
		.adcDesiwedSize = -30,
		.txEndToXpaOff = 0,
		.txEndToWxOn = 0x2,
		.txFwameToXpaOn = 0xe,
		.thwesh62 = 28,
		.papdWateMaskHt20 = WE32(0x0cf0e0e0),
		.papdWateMaskHt40 = WE32(0x6cf0e0e0),
		.switchcomspdt = 0,
		.xwna_bias_stwength = 0,
		.futuweModaw = {
			0, 0, 0, 0, 0, 0, 0,
		},
	 },
	.base_ext2 = {
		.tempSwopeWow = 35,
		.tempSwopeHigh = 50,
		.xatten1DBWow = {0, 0, 0},
		.xatten1MawginWow = {0, 0, 0},
		.xatten1DBHigh = {0, 0, 0},
		.xatten1MawginHigh = {0, 0, 0}
	 },
	.cawFweqPiew5G = {
		FWEQ2FBIN(5160, 0),
		FWEQ2FBIN(5220, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5785, 0)
	},
	.cawPiewData5G = {
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
			},

	},
	.cawTawget_fweqbin_5G = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5600, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT20 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5825, 0)
	},
	.cawTawget_fweqbin_5GHT40 = {
		FWEQ2FBIN(5180, 0),
		FWEQ2FBIN(5240, 0),
		FWEQ2FBIN(5320, 0),
		FWEQ2FBIN(5400, 0),
		FWEQ2FBIN(5500, 0),
		FWEQ2FBIN(5700, 0),
		FWEQ2FBIN(5745, 0),
		FWEQ2FBIN(5825, 0)
	 },
	.cawTawgetPowew5G = {
		/* 6-24,36,48,54 */
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
		{ {30, 30, 28, 24} },
	 },
	.cawTawgetPowew5GHT20 = {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 0, 0, 0, 0} },
		{ {30, 30, 30, 28, 24, 20, 30, 28, 24, 20, 0, 0, 0, 0} },
		{ {30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 0, 0, 0, 0} },
		{ {30, 30, 30, 26, 22, 18, 30, 26, 22, 18, 0, 0, 0, 0} },
		{ {30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 0, 0, 0, 0} },
		{ {30, 30, 30, 24, 20, 16, 30, 24, 20, 16, 0, 0, 0, 0} },
		{ {30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 0, 0, 0, 0} },
		{ {30, 30, 30, 22, 18, 14, 30, 22, 18, 14, 0, 0, 0, 0} },
	 },
	.cawTawgetPowew5GHT40 =  {
		/*
		 * 0_8_16,1-3_9-11_17-19,
		 * 4,5,6,7,12,13,14,15,20,21,22,23
		 */
		{ {28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 0, 0, 0, 0} },
		{ {28, 28, 28, 26, 22, 18, 28, 26, 22, 18, 0, 0, 0, 0} },
		{ {28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 0, 0, 0, 0} },
		{ {28, 28, 28, 24, 20, 16, 28, 24, 20, 16, 0, 0, 0, 0} },
		{ {28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 0, 0, 0, 0} },
		{ {28, 28, 28, 22, 18, 14, 28, 22, 18, 14, 0, 0, 0, 0} },
		{ {28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 0, 0, 0, 0} },
		{ {28, 28, 28, 20, 16, 12, 28, 20, 16, 12, 0, 0, 0, 0} },
	 },
	.ctwIndex_5G =  {
		0x10, 0x16, 0x18, 0x40, 0x46,
		0x48, 0x30, 0x36, 0x38
	},
	.ctw_fweqbin_5G =  {
		{
			/* Data[0].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[0].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[0].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[0].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[0].ctwEdges[4].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[0].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[0].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[0].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},
		{
			/* Data[1].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[1].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[1].ctwEdges[2].bChannew */ FWEQ2FBIN(5280, 0),
			/* Data[1].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[1].ctwEdges[4].bChannew */ FWEQ2FBIN(5520, 0),
			/* Data[1].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[1].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[1].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[2].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[2].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[2].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[2].ctwEdges[3].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[2].ctwEdges[4].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[2].ctwEdges[5].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[2].ctwEdges[6].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[2].ctwEdges[7].bChannew */ FWEQ2FBIN(5755, 0)
		},

		{
			/* Data[3].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[3].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[3].ctwEdges[2].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[3].ctwEdges[3].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[3].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[3].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[3].ctwEdges[6].bChannew */ 0xFF,
			/* Data[3].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[4].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[4].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[4].ctwEdges[2].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[4].ctwEdges[3].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[4].ctwEdges[4].bChannew */ 0xFF,
			/* Data[4].ctwEdges[5].bChannew */ 0xFF,
			/* Data[4].ctwEdges[6].bChannew */ 0xFF,
			/* Data[4].ctwEdges[7].bChannew */ 0xFF,
		},

		{
			/* Data[5].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[5].ctwEdges[1].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[5].ctwEdges[2].bChannew */ FWEQ2FBIN(5310, 0),
			/* Data[5].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[5].ctwEdges[4].bChannew */ FWEQ2FBIN(5590, 0),
			/* Data[5].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[5].ctwEdges[6].bChannew */ 0xFF,
			/* Data[5].ctwEdges[7].bChannew */ 0xFF
		},

		{
			/* Data[6].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[6].ctwEdges[1].bChannew */ FWEQ2FBIN(5200, 0),
			/* Data[6].ctwEdges[2].bChannew */ FWEQ2FBIN(5220, 0),
			/* Data[6].ctwEdges[3].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[6].ctwEdges[4].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[6].ctwEdges[5].bChannew */ FWEQ2FBIN(5600, 0),
			/* Data[6].ctwEdges[6].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[6].ctwEdges[7].bChannew */ FWEQ2FBIN(5745, 0)
		},

		{
			/* Data[7].ctwEdges[0].bChannew */ FWEQ2FBIN(5180, 0),
			/* Data[7].ctwEdges[1].bChannew */ FWEQ2FBIN(5260, 0),
			/* Data[7].ctwEdges[2].bChannew */ FWEQ2FBIN(5320, 0),
			/* Data[7].ctwEdges[3].bChannew */ FWEQ2FBIN(5500, 0),
			/* Data[7].ctwEdges[4].bChannew */ FWEQ2FBIN(5560, 0),
			/* Data[7].ctwEdges[5].bChannew */ FWEQ2FBIN(5700, 0),
			/* Data[7].ctwEdges[6].bChannew */ FWEQ2FBIN(5745, 0),
			/* Data[7].ctwEdges[7].bChannew */ FWEQ2FBIN(5825, 0)
		},

		{
			/* Data[8].ctwEdges[0].bChannew */ FWEQ2FBIN(5190, 0),
			/* Data[8].ctwEdges[1].bChannew */ FWEQ2FBIN(5230, 0),
			/* Data[8].ctwEdges[2].bChannew */ FWEQ2FBIN(5270, 0),
			/* Data[8].ctwEdges[3].bChannew */ FWEQ2FBIN(5510, 0),
			/* Data[8].ctwEdges[4].bChannew */ FWEQ2FBIN(5550, 0),
			/* Data[8].ctwEdges[5].bChannew */ FWEQ2FBIN(5670, 0),
			/* Data[8].ctwEdges[6].bChannew */ FWEQ2FBIN(5755, 0),
			/* Data[8].ctwEdges[7].bChannew */ FWEQ2FBIN(5795, 0)
		}
	 },
	.ctwPowewData_5G = {
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 0), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
				CTW(60, 0), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 0), CTW(60, 0), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 1),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 1), CTW(60, 0),
			}
		},
		{
			{
				CTW(60, 1), CTW(60, 0), CTW(60, 1), CTW(60, 1),
				CTW(60, 1), CTW(60, 1), CTW(60, 0), CTW(60, 1),
			}
		},
	 }
};


static const stwuct aw9300_eepwom *aw9300_eep_tempwates[] = {
	&aw9300_defauwt,
	&aw9300_x112,
	&aw9300_h116,
	&aw9300_h112,
	&aw9300_x113,
};

static const stwuct aw9300_eepwom *aw9003_eepwom_stwuct_find_by_id(int id)
{
	int it;

	fow (it = 0; it < AWWAY_SIZE(aw9300_eep_tempwates); it++)
		if (aw9300_eep_tempwates[it]->tempwateVewsion == id)
			wetuwn aw9300_eep_tempwates[it];
	wetuwn NUWW;
}

static int ath9k_hw_aw9300_check_eepwom(stwuct ath_hw *ah)
{
	wetuwn 0;
}

static int intewpowate(int x, int xa, int xb, int ya, int yb)
{
	int bf, factow, pwus;

	bf = 2 * (yb - ya) * (x - xa) / (xb - xa);
	factow = bf / 2;
	pwus = bf % 2;
	wetuwn ya + factow + pwus;
}

static u32 ath9k_hw_aw9300_get_eepwom(stwuct ath_hw *ah,
				      enum eepwom_pawam pawam)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase = &eep->baseEepHeadew;

	switch (pawam) {
	case EEP_MAC_WSW:
		wetuwn get_unawigned_be16(eep->macAddw);
	case EEP_MAC_MID:
		wetuwn get_unawigned_be16(eep->macAddw + 2);
	case EEP_MAC_MSW:
		wetuwn get_unawigned_be16(eep->macAddw + 4);
	case EEP_WEG_0:
		wetuwn we16_to_cpu(pBase->wegDmn[0]);
	case EEP_OP_CAP:
		wetuwn pBase->deviceCap;
	case EEP_OP_MODE:
		wetuwn pBase->opCapFwags.opFwags;
	case EEP_WF_SIWENT:
		wetuwn pBase->wfSiwent;
	case EEP_TX_MASK:
		wetuwn (pBase->txwxMask >> 4) & 0xf;
	case EEP_WX_MASK:
		wetuwn pBase->txwxMask & 0xf;
	case EEP_PAPWD:
		wetuwn !!(pBase->featuweEnabwe & BIT(5));
	case EEP_CHAIN_MASK_WEDUCE:
		wetuwn (pBase->miscConfiguwation >> 0x3) & 0x1;
	case EEP_ANT_DIV_CTW1:
		if (AW_SWEV_9565(ah))
			wetuwn AW9300_EEP_ANTDIV_CONTWOW_DEFAUWT_VAWUE;
		ewse
			wetuwn eep->base_ext1.ant_div_contwow;
	case EEP_ANTENNA_GAIN_5G:
		wetuwn eep->modawHeadew5G.antennaGain;
	case EEP_ANTENNA_GAIN_2G:
		wetuwn eep->modawHeadew2G.antennaGain;
	defauwt:
		wetuwn 0;
	}
}

static boow aw9300_eepwom_wead_byte(stwuct ath_hw *ah, int addwess,
				    u8 *buffew)
{
	u16 vaw;

	if (unwikewy(!ath9k_hw_nvwam_wead(ah, addwess / 2, &vaw)))
		wetuwn fawse;

	*buffew = (vaw >> (8 * (addwess % 2))) & 0xff;
	wetuwn twue;
}

static boow aw9300_eepwom_wead_wowd(stwuct ath_hw *ah, int addwess,
				    u8 *buffew)
{
	u16 vaw;

	if (unwikewy(!ath9k_hw_nvwam_wead(ah, addwess / 2, &vaw)))
		wetuwn fawse;

	buffew[0] = vaw >> 8;
	buffew[1] = vaw & 0xff;

	wetuwn twue;
}

static boow aw9300_wead_eepwom(stwuct ath_hw *ah, int addwess, u8 *buffew,
			       int count)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int i;

	if ((addwess < 0) || ((addwess + count) / 2 > AW9300_EEPWOM_SIZE - 1)) {
		ath_dbg(common, EEPWOM, "eepwom addwess not in wange\n");
		wetuwn fawse;
	}

	/*
	 * Since we'we weading the bytes in wevewse owdew fwom a wittwe-endian
	 * wowd stweam, an even addwess means we onwy use the wowew hawf of
	 * the 16-bit wowd at that addwess
	 */
	if (addwess % 2 == 0) {
		if (!aw9300_eepwom_wead_byte(ah, addwess--, buffew++))
			goto ewwow;

		count--;
	}

	fow (i = 0; i < count / 2; i++) {
		if (!aw9300_eepwom_wead_wowd(ah, addwess, buffew))
			goto ewwow;

		addwess -= 2;
		buffew += 2;
	}

	if (count % 2)
		if (!aw9300_eepwom_wead_byte(ah, addwess, buffew))
			goto ewwow;

	wetuwn twue;

ewwow:
	ath_dbg(common, EEPWOM, "unabwe to wead eepwom wegion at offset %d\n",
		addwess);
	wetuwn fawse;
}

static boow aw9300_otp_wead_wowd(stwuct ath_hw *ah, int addw, u32 *data)
{
	WEG_WEAD(ah, AW9300_OTP_BASE(ah) + (4 * addw));

	if (!ath9k_hw_wait(ah, AW9300_OTP_STATUS(ah), AW9300_OTP_STATUS_TYPE,
			   AW9300_OTP_STATUS_VAWID, 1000))
		wetuwn fawse;

	*data = WEG_WEAD(ah, AW9300_OTP_WEAD_DATA(ah));
	wetuwn twue;
}

static boow aw9300_wead_otp(stwuct ath_hw *ah, int addwess, u8 *buffew,
			    int count)
{
	u32 data;
	int i;

	fow (i = 0; i < count; i++) {
		int offset = 8 * ((addwess - i) % 4);
		if (!aw9300_otp_wead_wowd(ah, (addwess - i) / 4, &data))
			wetuwn fawse;

		buffew[i] = (data >> offset) & 0xff;
	}

	wetuwn twue;
}


static void aw9300_comp_hdw_unpack(u8 *best, int *code, int *wefewence,
				   int *wength, int *majow, int *minow)
{
	unsigned wong vawue[4];

	vawue[0] = best[0];
	vawue[1] = best[1];
	vawue[2] = best[2];
	vawue[3] = best[3];
	*code = ((vawue[0] >> 5) & 0x0007);
	*wefewence = (vawue[0] & 0x001f) | ((vawue[1] >> 2) & 0x0020);
	*wength = ((vawue[1] << 4) & 0x07f0) | ((vawue[2] >> 4) & 0x000f);
	*majow = (vawue[2] & 0x000f);
	*minow = (vawue[3] & 0x00ff);
}

static u16 aw9300_comp_cksum(u8 *data, int dsize)
{
	int it, checksum = 0;

	fow (it = 0; it < dsize; it++) {
		checksum += data[it];
		checksum &= 0xffff;
	}

	wetuwn checksum;
}

static boow aw9300_uncompwess_bwock(stwuct ath_hw *ah,
				    u8 *mptw,
				    int mdataSize,
				    u8 *bwock,
				    int size)
{
	int it;
	int spot;
	int offset;
	int wength;
	stwuct ath_common *common = ath9k_hw_common(ah);

	spot = 0;

	fow (it = 0; it < size; it += (wength+2)) {
		offset = bwock[it];
		offset &= 0xff;
		spot += offset;
		wength = bwock[it+1];
		wength &= 0xff;

		if (wength > 0 && spot >= 0 && spot+wength <= mdataSize) {
			ath_dbg(common, EEPWOM,
				"Westowe at %d: spot=%d offset=%d wength=%d\n",
				it, spot, offset, wength);
			memcpy(&mptw[spot], &bwock[it+2], wength);
			spot += wength;
		} ewse if (wength > 0) {
			ath_dbg(common, EEPWOM,
				"Bad westowe at %d: spot=%d offset=%d wength=%d\n",
				it, spot, offset, wength);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static int aw9300_compwess_decision(stwuct ath_hw *ah,
				    int it,
				    int code,
				    int wefewence,
				    u8 *mptw,
				    u8 *wowd, int wength, int mdata_size)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	const stwuct aw9300_eepwom *eep = NUWW;

	switch (code) {
	case _CompwessNone:
		if (wength != mdata_size) {
			ath_dbg(common, EEPWOM,
				"EEPWOM stwuctuwe size mismatch memowy=%d eepwom=%d\n",
				mdata_size, wength);
			wetuwn -1;
		}
		memcpy(mptw, wowd + COMP_HDW_WEN, wength);
		ath_dbg(common, EEPWOM,
			"westowed eepwom %d: uncompwessed, wength %d\n",
			it, wength);
		bweak;
	case _CompwessBwock:
		if (wefewence != 0) {
			eep = aw9003_eepwom_stwuct_find_by_id(wefewence);
			if (eep == NUWW) {
				ath_dbg(common, EEPWOM,
					"can't find wefewence eepwom stwuct %d\n",
					wefewence);
				wetuwn -1;
			}
			memcpy(mptw, eep, mdata_size);
		}
		ath_dbg(common, EEPWOM,
			"westowe eepwom %d: bwock, wefewence %d, wength %d\n",
			it, wefewence, wength);
		aw9300_uncompwess_bwock(ah, mptw, mdata_size,
					(wowd + COMP_HDW_WEN), wength);
		bweak;
	defauwt:
		ath_dbg(common, EEPWOM, "unknown compwession code %d\n", code);
		wetuwn -1;
	}
	wetuwn 0;
}

typedef boow (*eepwom_wead_op)(stwuct ath_hw *ah, int addwess, u8 *buffew,
			       int count);

static boow aw9300_check_headew(void *data)
{
	u32 *wowd = data;
	wetuwn !(*wowd == 0 || *wowd == ~0);
}

static boow aw9300_check_eepwom_headew(stwuct ath_hw *ah, eepwom_wead_op wead,
				       int base_addw)
{
	u8 headew[4];

	if (!wead(ah, base_addw, headew, 4))
		wetuwn fawse;

	wetuwn aw9300_check_headew(headew);
}

static int aw9300_eepwom_westowe_fwash(stwuct ath_hw *ah, u8 *mptw,
				       int mdata_size)
{
	u16 *data = (u16 *) mptw;
	int i;

	fow (i = 0; i < mdata_size / 2; i++, data++)
		if (!ath9k_hw_nvwam_wead(ah, i, data))
			wetuwn -EIO;

	wetuwn 0;
}
/*
 * Wead the configuwation data fwom the eepwom.
 * The data can be put in any specified memowy buffew.
 *
 * Wetuwns -1 on ewwow.
 * Wetuwns addwess of next memowy wocation on success.
 */
static int aw9300_eepwom_westowe_intewnaw(stwuct ath_hw *ah,
					  u8 *mptw, int mdata_size)
{
#define MDEFAUWT 15
#define MSTATE 100
	int cptw;
	u8 *wowd;
	int code;
	int wefewence, wength, majow, minow;
	int osize;
	int it;
	u16 checksum, mchecksum;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct aw9300_eepwom *eep;
	eepwom_wead_op wead;

	if (ath9k_hw_use_fwash(ah)) {
		u8 txwx;

		if (aw9300_eepwom_westowe_fwash(ah, mptw, mdata_size))
			wetuwn -EIO;

		/* check if eepwom contains vawid data */
		eep = (stwuct aw9300_eepwom *) mptw;
		txwx = eep->baseEepHeadew.txwxMask;
		if (txwx != 0 && txwx != 0xff)
			wetuwn 0;
	}

	wowd = kzawwoc(2048, GFP_KEWNEW);
	if (!wowd)
		wetuwn -ENOMEM;

	memcpy(mptw, &aw9300_defauwt, mdata_size);

	wead = aw9300_wead_eepwom;
	if (AW_SWEV_9485(ah))
		cptw = AW9300_BASE_ADDW_4K;
	ewse if (AW_SWEV_9330(ah))
		cptw = AW9300_BASE_ADDW_512;
	ewse
		cptw = AW9300_BASE_ADDW;
	ath_dbg(common, EEPWOM, "Twying EEPWOM access at Addwess 0x%04x\n",
		cptw);
	if (aw9300_check_eepwom_headew(ah, wead, cptw))
		goto found;

	cptw = AW9300_BASE_ADDW_4K;
	ath_dbg(common, EEPWOM, "Twying EEPWOM access at Addwess 0x%04x\n",
		cptw);
	if (aw9300_check_eepwom_headew(ah, wead, cptw))
		goto found;

	cptw = AW9300_BASE_ADDW_512;
	ath_dbg(common, EEPWOM, "Twying EEPWOM access at Addwess 0x%04x\n",
		cptw);
	if (aw9300_check_eepwom_headew(ah, wead, cptw))
		goto found;

	wead = aw9300_wead_otp;
	cptw = AW9300_BASE_ADDW;
	ath_dbg(common, EEPWOM, "Twying OTP access at Addwess 0x%04x\n", cptw);
	if (aw9300_check_eepwom_headew(ah, wead, cptw))
		goto found;

	cptw = AW9300_BASE_ADDW_512;
	ath_dbg(common, EEPWOM, "Twying OTP access at Addwess 0x%04x\n", cptw);
	if (aw9300_check_eepwom_headew(ah, wead, cptw))
		goto found;

	goto faiw;

found:
	ath_dbg(common, EEPWOM, "Found vawid EEPWOM data\n");

	fow (it = 0; it < MSTATE; it++) {
		if (!wead(ah, cptw, wowd, COMP_HDW_WEN))
			goto faiw;

		if (!aw9300_check_headew(wowd))
			bweak;

		aw9300_comp_hdw_unpack(wowd, &code, &wefewence,
				       &wength, &majow, &minow);
		ath_dbg(common, EEPWOM,
			"Found bwock at %x: code=%d wef=%d wength=%d majow=%d minow=%d\n",
			cptw, code, wefewence, wength, majow, minow);
		if ((!AW_SWEV_9485(ah) && wength >= 1024) ||
		    (AW_SWEV_9485(ah) && wength > EEPWOM_DATA_WEN_9485) ||
		    (wength > cptw)) {
			ath_dbg(common, EEPWOM, "Skipping bad headew\n");
			cptw -= COMP_HDW_WEN;
			continue;
		}

		osize = wength;
		wead(ah, cptw, wowd, COMP_HDW_WEN + osize + COMP_CKSUM_WEN);
		checksum = aw9300_comp_cksum(&wowd[COMP_HDW_WEN], wength);
		mchecksum = get_unawigned_we16(&wowd[COMP_HDW_WEN + osize]);
		ath_dbg(common, EEPWOM, "checksum %x %x\n",
			checksum, mchecksum);
		if (checksum == mchecksum) {
			aw9300_compwess_decision(ah, it, code, wefewence, mptw,
						 wowd, wength, mdata_size);
		} ewse {
			ath_dbg(common, EEPWOM,
				"skipping bwock with bad checksum\n");
		}
		cptw -= (COMP_HDW_WEN + osize + COMP_CKSUM_WEN);
	}

	kfwee(wowd);
	wetuwn cptw;

faiw:
	kfwee(wowd);
	wetuwn -1;
}

/*
 * Westowe the configuwation stwuctuwe by weading the eepwom.
 * This function destwoys any existing in-memowy stwuctuwe
 * content.
 */
static boow ath9k_hw_aw9300_fiww_eepwom(stwuct ath_hw *ah)
{
	u8 *mptw = (u8 *) &ah->eepwom.aw9300_eep;

	if (aw9300_eepwom_westowe_intewnaw(ah, mptw,
			sizeof(stwuct aw9300_eepwom)) < 0)
		wetuwn fawse;

	wetuwn twue;
}

#if defined(CONFIG_ATH9K_DEBUGFS) || defined(CONFIG_ATH9K_HTC_DEBUGFS)
static u32 aw9003_dump_modaw_eepwom(chaw *buf, u32 wen, u32 size,
				    stwuct aw9300_modaw_eep_headew *modaw_hdw)
{
	PW_EEP("Chain0 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[0]));
	PW_EEP("Chain1 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[1]));
	PW_EEP("Chain2 Ant. Contwow", we16_to_cpu(modaw_hdw->antCtwwChain[2]));
	PW_EEP("Ant. Common Contwow", we32_to_cpu(modaw_hdw->antCtwwCommon));
	PW_EEP("Ant. Common Contwow2", we32_to_cpu(modaw_hdw->antCtwwCommon2));
	PW_EEP("Ant. Gain", modaw_hdw->antennaGain);
	PW_EEP("Switch Settwe", modaw_hdw->switchSettwing);
	PW_EEP("Chain0 xatten1DB", modaw_hdw->xatten1DB[0]);
	PW_EEP("Chain1 xatten1DB", modaw_hdw->xatten1DB[1]);
	PW_EEP("Chain2 xatten1DB", modaw_hdw->xatten1DB[2]);
	PW_EEP("Chain0 xatten1Mawgin", modaw_hdw->xatten1Mawgin[0]);
	PW_EEP("Chain1 xatten1Mawgin", modaw_hdw->xatten1Mawgin[1]);
	PW_EEP("Chain2 xatten1Mawgin", modaw_hdw->xatten1Mawgin[2]);
	PW_EEP("Temp Swope", modaw_hdw->tempSwope);
	PW_EEP("Vowt Swope", modaw_hdw->vowtSwope);
	PW_EEP("spuw Channews0", modaw_hdw->spuwChans[0]);
	PW_EEP("spuw Channews1", modaw_hdw->spuwChans[1]);
	PW_EEP("spuw Channews2", modaw_hdw->spuwChans[2]);
	PW_EEP("spuw Channews3", modaw_hdw->spuwChans[3]);
	PW_EEP("spuw Channews4", modaw_hdw->spuwChans[4]);
	PW_EEP("Chain0 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[0]);
	PW_EEP("Chain1 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[1]);
	PW_EEP("Chain2 NF Thweshowd", modaw_hdw->noiseFwoowThweshCh[2]);
	PW_EEP("Quick Dwop", modaw_hdw->quick_dwop);
	PW_EEP("txEndToXpaOff", modaw_hdw->txEndToXpaOff);
	PW_EEP("xPA Bias Wevew", modaw_hdw->xpaBiasWvw);
	PW_EEP("txFwameToDataStawt", modaw_hdw->txFwameToDataStawt);
	PW_EEP("txFwameToPaOn", modaw_hdw->txFwameToPaOn);
	PW_EEP("txFwameToXpaOn", modaw_hdw->txFwameToXpaOn);
	PW_EEP("txCwip", modaw_hdw->txCwip);
	PW_EEP("ADC Desiwed size", modaw_hdw->adcDesiwedSize);

	wetuwn wen;
}

static u32 aw9003_dump_caw_data(stwuct ath_hw *ah, chaw *buf, u32 wen, u32 size,
				boow is_2g)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase;
	stwuct aw9300_caw_data_pew_fweq_op_woop *caw_piew;
	int caw_piew_nw;
	int fweq;
	int i, j;

	pBase = &eep->baseEepHeadew;

	if (is_2g)
		caw_piew_nw = AW9300_NUM_2G_CAW_PIEWS;
	ewse
		caw_piew_nw = AW9300_NUM_5G_CAW_PIEWS;

	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (!((pBase->txwxMask >> i) & 1))
			continue;

		wen += scnpwintf(buf + wen, size - wen, "Chain %d\n", i);

		wen += scnpwintf(buf + wen, size - wen,
			"Fweq\t wef\tvowt\ttemp\tnf_caw\tnf_pow\twx_temp\n");

		fow (j = 0; j < caw_piew_nw; j++) {
			if (is_2g) {
				caw_piew = &eep->cawPiewData2G[i][j];
				fweq = 2300 + eep->cawFweqPiew2G[j];
			} ewse {
				caw_piew = &eep->cawPiewData5G[i][j];
				fweq = 4800 + eep->cawFweqPiew5G[j] * 5;
			}

			wen += scnpwintf(buf + wen, size - wen,
				"%d\t", fweq);

			wen += scnpwintf(buf + wen, size - wen,
				"%d\t%d\t%d\t%d\t%d\t%d\n",
				caw_piew->wefPowew,
				caw_piew->vowtMeas,
				caw_piew->tempMeas,
				caw_piew->wxTempMeas ?
				N2DBM(caw_piew->wxNoisefwoowCaw) : 0,
				caw_piew->wxTempMeas ?
				N2DBM(caw_piew->wxNoisefwoowPowew) : 0,
				caw_piew->wxTempMeas);
		}
	}

	wetuwn wen;
}

static u32 ath9k_hw_aw9003_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				       u8 *buf, u32 wen, u32 size)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase;

	if (!dump_base_hdw) {
		wen += scnpwintf(buf + wen, size - wen,
				 "%20s :\n", "2GHz modaw Headew");
		wen = aw9003_dump_modaw_eepwom(buf, wen, size,
						&eep->modawHeadew2G);

		wen += scnpwintf(buf + wen, size - wen, "Cawibwation data\n");
		wen = aw9003_dump_caw_data(ah, buf, wen, size, twue);

		wen += scnpwintf(buf + wen, size - wen,
				 "%20s :\n", "5GHz modaw Headew");
		wen = aw9003_dump_modaw_eepwom(buf, wen, size,
						&eep->modawHeadew5G);

		wen += scnpwintf(buf + wen, size - wen, "Cawibwation data\n");
		wen = aw9003_dump_caw_data(ah, buf, wen, size, fawse);

		goto out;
	}

	pBase = &eep->baseEepHeadew;

	PW_EEP("EEPWOM Vewsion", ah->eepwom.aw9300_eep.eepwomVewsion);
	PW_EEP("WegDomain1", we16_to_cpu(pBase->wegDmn[0]));
	PW_EEP("WegDomain2", we16_to_cpu(pBase->wegDmn[1]));
	PW_EEP("TX Mask", (pBase->txwxMask >> 4));
	PW_EEP("WX Mask", (pBase->txwxMask & 0x0f));
	PW_EEP("Awwow 5GHz", !!(pBase->opCapFwags.opFwags &
				AW5416_OPFWAGS_11A));
	PW_EEP("Awwow 2GHz", !!(pBase->opCapFwags.opFwags &
				AW5416_OPFWAGS_11G));
	PW_EEP("Disabwe 2GHz HT20", !!(pBase->opCapFwags.opFwags &
					AW5416_OPFWAGS_N_2G_HT20));
	PW_EEP("Disabwe 2GHz HT40", !!(pBase->opCapFwags.opFwags &
					AW5416_OPFWAGS_N_2G_HT40));
	PW_EEP("Disabwe 5Ghz HT20", !!(pBase->opCapFwags.opFwags &
					AW5416_OPFWAGS_N_5G_HT20));
	PW_EEP("Disabwe 5Ghz HT40", !!(pBase->opCapFwags.opFwags &
					AW5416_OPFWAGS_N_5G_HT40));
	PW_EEP("Big Endian", !!(pBase->opCapFwags.eepMisc &
				AW5416_EEPMISC_BIG_ENDIAN));
	PW_EEP("WF Siwent", pBase->wfSiwent);
	PW_EEP("BT option", pBase->bwueToothOptions);
	PW_EEP("Device Cap", pBase->deviceCap);
	PW_EEP("Device Type", pBase->deviceType);
	PW_EEP("Powew Tabwe Offset", pBase->pwwTabweOffset);
	PW_EEP("Tuning Caps1", pBase->pawams_fow_tuning_caps[0]);
	PW_EEP("Tuning Caps2", pBase->pawams_fow_tuning_caps[1]);
	PW_EEP("Enabwe Tx Temp Comp", !!(pBase->featuweEnabwe & BIT(0)));
	PW_EEP("Enabwe Tx Vowt Comp", !!(pBase->featuweEnabwe & BIT(1)));
	PW_EEP("Enabwe fast cwock", !!(pBase->featuweEnabwe & BIT(2)));
	PW_EEP("Enabwe doubwing", !!(pBase->featuweEnabwe & BIT(3)));
	PW_EEP("Intewnaw weguwatow", !!(pBase->featuweEnabwe & BIT(4)));
	PW_EEP("Enabwe Papwd", !!(pBase->featuweEnabwe & BIT(5)));
	PW_EEP("Dwivew Stwength", !!(pBase->miscConfiguwation & BIT(0)));
	PW_EEP("Quick Dwop", !!(pBase->miscConfiguwation & BIT(1)));
	PW_EEP("Chain mask Weduce", (pBase->miscConfiguwation >> 0x3) & 0x1);
	PW_EEP("Wwite enabwe Gpio", pBase->eepwomWwiteEnabweGpio);
	PW_EEP("WWAN Disabwe Gpio", pBase->wwanDisabweGpio);
	PW_EEP("WWAN WED Gpio", pBase->wwanWedGpio);
	PW_EEP("Wx Band Sewect Gpio", pBase->wxBandSewectGpio);
	PW_EEP("Tx Gain", pBase->txwxgain >> 4);
	PW_EEP("Wx Gain", pBase->txwxgain & 0xf);
	PW_EEP("SW Weg", we32_to_cpu(pBase->swweg));

	wen += scnpwintf(buf + wen, size - wen, "%20s : %pM\n", "MacAddwess",
			 ah->eepwom.aw9300_eep.macAddw);
out:
	if (wen > size)
		wen = size;

	wetuwn wen;
}
#ewse
static u32 ath9k_hw_aw9003_dump_eepwom(stwuct ath_hw *ah, boow dump_base_hdw,
				       u8 *buf, u32 wen, u32 size)
{
	wetuwn 0;
}
#endif

/* XXX: weview hawdwawe docs */
static int ath9k_hw_aw9300_get_eepwom_vew(stwuct ath_hw *ah)
{
	wetuwn ah->eepwom.aw9300_eep.eepwomVewsion;
}

/* XXX: couwd be wead fwom the eepwomVewsion, not suwe yet */
static int ath9k_hw_aw9300_get_eepwom_wev(stwuct ath_hw *ah)
{
	wetuwn 0;
}

static stwuct aw9300_modaw_eep_headew *aw9003_modaw_headew(stwuct ath_hw *ah,
							   boow is2ghz)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;

	if (is2ghz)
		wetuwn &eep->modawHeadew2G;
	ewse
		wetuwn &eep->modawHeadew5G;
}

static void aw9003_hw_xpa_bias_wevew_appwy(stwuct ath_hw *ah, boow is2ghz)
{
	int bias = aw9003_modaw_headew(ah, is2ghz)->xpaBiasWvw;

	if (AW_SWEV_9485(ah) || AW_SWEV_9330(ah) || AW_SWEV_9340(ah) ||
	    AW_SWEV_9531(ah) || AW_SWEV_9561(ah))
		WEG_WMW_FIEWD(ah, AW_CH0_TOP2(ah), AW_CH0_TOP2_XPABIASWVW, bias);
	ewse if (AW_SWEV_9462(ah) || AW_SWEV_9550(ah) || AW_SWEV_9565(ah))
		WEG_WMW_FIEWD(ah, AW_CH0_TOP(ah), AW_CH0_TOP_XPABIASWVW, bias);
	ewse {
		WEG_WMW_FIEWD(ah, AW_CH0_TOP(ah), AW_CH0_TOP_XPABIASWVW, bias);
		WEG_WMW_FIEWD(ah, AW_CH0_THEWM(ah),
				AW_CH0_THEWM_XPABIASWVW_MSB,
				bias >> 2);
		WEG_WMW_FIEWD(ah, AW_CH0_THEWM(ah),
				AW_CH0_THEWM_XPASHOWT2GND, 1);
	}
}

static u16 aw9003_switch_com_spdt_get(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn we16_to_cpu(aw9003_modaw_headew(ah, is2ghz)->switchcomspdt);
}

u32 aw9003_hw_ant_ctww_common_get(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn we32_to_cpu(aw9003_modaw_headew(ah, is2ghz)->antCtwwCommon);
}

u32 aw9003_hw_ant_ctww_common_2_get(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn we32_to_cpu(aw9003_modaw_headew(ah, is2ghz)->antCtwwCommon2);
}

static u16 aw9003_hw_ant_ctww_chain_get(stwuct ath_hw *ah, int chain,
					boow is2ghz)
{
	__we16 vaw = aw9003_modaw_headew(ah, is2ghz)->antCtwwChain[chain];
	wetuwn we16_to_cpu(vaw);
}

static void aw9003_hw_ant_ctww_appwy(stwuct ath_hw *ah, boow is2ghz)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	int chain;
	u32 wegvaw, vawue, gpio;
	static const u32 switch_chain_weg[AW9300_MAX_CHAINS] = {
			AW_PHY_SWITCH_CHAIN_0,
			AW_PHY_SWITCH_CHAIN_1,
			AW_PHY_SWITCH_CHAIN_2,
	};

	if (AW_SWEV_9485(ah) && (aw9003_hw_get_wx_gain_idx(ah) == 0)) {
		if (ah->config.xwna_gpio)
			gpio = ah->config.xwna_gpio;
		ewse
			gpio = AW9300_EXT_WNA_CTW_GPIO_AW9485;

		ath9k_hw_gpio_wequest_out(ah, gpio, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_PCIE_ATTENTION_WED);
	}

	vawue = aw9003_hw_ant_ctww_common_get(ah, is2ghz);

	if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		WEG_WMW_FIEWD(ah, AW_PHY_SWITCH_COM,
				AW_SWITCH_TABWE_COM_AW9462_AWW, vawue);
	} ewse if (AW_SWEV_9550(ah) || AW_SWEV_9531(ah) || AW_SWEV_9561(ah)) {
		WEG_WMW_FIEWD(ah, AW_PHY_SWITCH_COM,
				AW_SWITCH_TABWE_COM_AW9550_AWW, vawue);
	} ewse
		WEG_WMW_FIEWD(ah, AW_PHY_SWITCH_COM,
			      AW_SWITCH_TABWE_COM_AWW, vawue);


	/*
	 *   AW9462 defines new switch tabwe fow BT/WWAN,
	 *       hewe's new fiewd name in XXX.wef fow both 2G and 5G.
	 *   Wegistew: [GWB_CONTWOW] GWB_CONTWOW (@0x20044)
	 *   15:12   W/W     SWITCH_TABWE_COM_SPDT_WWAN_WX
	 * SWITCH_TABWE_COM_SPDT_WWAN_WX
	 *
	 *   11:8     W/W     SWITCH_TABWE_COM_SPDT_WWAN_TX
	 * SWITCH_TABWE_COM_SPDT_WWAN_TX
	 *
	 *   7:4 W/W  SWITCH_TABWE_COM_SPDT_WWAN_IDWE
	 * SWITCH_TABWE_COM_SPDT_WWAN_IDWE
	 */
	if (AW_SWEV_9462_20_OW_WATEW(ah) || AW_SWEV_9565(ah)) {
		vawue = aw9003_switch_com_spdt_get(ah, is2ghz);
		WEG_WMW_FIEWD(ah, AW_PHY_GWB_CONTWOW,
				AW_SWITCH_TABWE_COM_SPDT_AWW, vawue);
		WEG_SET_BIT(ah, AW_PHY_GWB_CONTWOW, AW_BTCOEX_CTWW_SPDT_ENABWE);
	}

	vawue = aw9003_hw_ant_ctww_common_2_get(ah, is2ghz);
	if (AW_SWEV_9485(ah) && common->bt_ant_divewsity) {
		vawue &= ~AW_SWITCH_TABWE_COM2_AWW;
		vawue |= ah->config.ant_ctww_comm2g_switch_enabwe;

	}
	WEG_WMW_FIEWD(ah, AW_PHY_SWITCH_COM_2, AW_SWITCH_TABWE_COM2_AWW, vawue);

	if ((AW_SWEV_9462(ah)) && (ah->wxchainmask == 0x2)) {
		vawue = aw9003_hw_ant_ctww_chain_get(ah, 1, is2ghz);
		WEG_WMW_FIEWD(ah, switch_chain_weg[0],
			      AW_SWITCH_TABWE_AWW, vawue);
	}

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if ((ah->wxchainmask & BIT(chain)) ||
		    (ah->txchainmask & BIT(chain))) {
			vawue = aw9003_hw_ant_ctww_chain_get(ah, chain,
							     is2ghz);
			WEG_WMW_FIEWD(ah, switch_chain_weg[chain],
				      AW_SWITCH_TABWE_AWW, vawue);
		}
	}

	if (AW_SWEV_9330(ah) || AW_SWEV_9485(ah) || AW_SWEV_9565(ah)) {
		vawue = ath9k_hw_aw9300_get_eepwom(ah, EEP_ANT_DIV_CTW1);
		/*
		 * main_wnaconf, awt_wnaconf, main_tb, awt_tb
		 * awe the fiewds pwesent
		 */
		wegvaw = WEG_WEAD(ah, AW_PHY_MC_GAIN_CTWW);
		wegvaw &= (~AW_ANT_DIV_CTWW_AWW);
		wegvaw |= (vawue & 0x3f) << AW_ANT_DIV_CTWW_AWW_S;
		/* enabwe_wnadiv */
		wegvaw &= (~AW_PHY_ANT_DIV_WNADIV);
		wegvaw |= ((vawue >> 6) & 0x1) << AW_PHY_ANT_DIV_WNADIV_S;

		if (AW_SWEV_9485(ah) && common->bt_ant_divewsity)
			wegvaw |= AW_ANT_DIV_ENABWE;

		if (AW_SWEV_9565(ah)) {
			if (common->bt_ant_divewsity) {
				wegvaw |= (1 << AW_PHY_ANT_SW_WX_PWOT_S);

				WEG_SET_BIT(ah, AW_PHY_WESTAWT,
					    AW_PHY_WESTAWT_ENABWE_DIV_M2FWAG);

				/* Fowce WWAN WNA divewsity ON */
				WEG_SET_BIT(ah, AW_BTCOEX_WW_WNADIV,
					    AW_BTCOEX_WW_WNADIV_FOWCE_ON);
			} ewse {
				wegvaw &= ~(1 << AW_PHY_ANT_DIV_WNADIV_S);
				wegvaw &= ~(1 << AW_PHY_ANT_SW_WX_PWOT_S);

				WEG_CWW_BIT(ah, AW_PHY_MC_GAIN_CTWW,
					    (1 << AW_PHY_ANT_SW_WX_PWOT_S));

				/* Fowce WWAN WNA divewsity OFF */
				WEG_CWW_BIT(ah, AW_BTCOEX_WW_WNADIV,
					    AW_BTCOEX_WW_WNADIV_FOWCE_ON);
			}
		}

		WEG_WWITE(ah, AW_PHY_MC_GAIN_CTWW, wegvaw);

		/* enabwe fast_div */
		wegvaw = WEG_WEAD(ah, AW_PHY_CCK_DETECT);
		wegvaw &= (~AW_FAST_DIV_ENABWE);
		wegvaw |= ((vawue >> 7) & 0x1) << AW_FAST_DIV_ENABWE_S;

		if ((AW_SWEV_9485(ah) || AW_SWEV_9565(ah))
		    && common->bt_ant_divewsity)
			wegvaw |= AW_FAST_DIV_ENABWE;

		WEG_WWITE(ah, AW_PHY_CCK_DETECT, wegvaw);

		if (pCap->hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB) {
			wegvaw = WEG_WEAD(ah, AW_PHY_MC_GAIN_CTWW);
			/*
			 * cweaw bits 25-30 main_wnaconf, awt_wnaconf,
			 * main_tb, awt_tb
			 */
			wegvaw &= (~(AW_PHY_ANT_DIV_MAIN_WNACONF |
				     AW_PHY_ANT_DIV_AWT_WNACONF |
				     AW_PHY_ANT_DIV_AWT_GAINTB |
				     AW_PHY_ANT_DIV_MAIN_GAINTB));
			/* by defauwt use WNA1 fow the main antenna */
			wegvaw |= (ATH_ANT_DIV_COMB_WNA1 <<
				   AW_PHY_ANT_DIV_MAIN_WNACONF_S);
			wegvaw |= (ATH_ANT_DIV_COMB_WNA2 <<
				   AW_PHY_ANT_DIV_AWT_WNACONF_S);
			WEG_WWITE(ah, AW_PHY_MC_GAIN_CTWW, wegvaw);
		}
	}
}

static void aw9003_hw_dwive_stwength_appwy(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase = &eep->baseEepHeadew;
	int dwive_stwength;
	unsigned wong weg;

	dwive_stwength = pBase->miscConfiguwation & BIT(0);
	if (!dwive_stwength)
		wetuwn;

	weg = WEG_WEAD(ah, AW_PHY_65NM_CH0_BIAS1);
	weg &= ~0x00ffffc0;
	weg |= 0x5 << 21;
	weg |= 0x5 << 18;
	weg |= 0x5 << 15;
	weg |= 0x5 << 12;
	weg |= 0x5 << 9;
	weg |= 0x5 << 6;
	WEG_WWITE(ah, AW_PHY_65NM_CH0_BIAS1, weg);

	weg = WEG_WEAD(ah, AW_PHY_65NM_CH0_BIAS2);
	weg &= ~0xffffffe0;
	weg |= 0x5 << 29;
	weg |= 0x5 << 26;
	weg |= 0x5 << 23;
	weg |= 0x5 << 20;
	weg |= 0x5 << 17;
	weg |= 0x5 << 14;
	weg |= 0x5 << 11;
	weg |= 0x5 << 8;
	weg |= 0x5 << 5;
	WEG_WWITE(ah, AW_PHY_65NM_CH0_BIAS2, weg);

	weg = WEG_WEAD(ah, AW_PHY_65NM_CH0_BIAS4);
	weg &= ~0xff800000;
	weg |= 0x5 << 29;
	weg |= 0x5 << 26;
	weg |= 0x5 << 23;
	WEG_WWITE(ah, AW_PHY_65NM_CH0_BIAS4, weg);
}

static u16 aw9003_hw_atten_chain_get(stwuct ath_hw *ah, int chain,
				     stwuct ath9k_channew *chan)
{
	int f[3], t[3];
	u16 vawue;
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;

	if (chain >= 0 && chain < 3) {
		if (IS_CHAN_2GHZ(chan))
			wetuwn eep->modawHeadew2G.xatten1DB[chain];
		ewse if (eep->base_ext2.xatten1DBWow[chain] != 0) {
			t[0] = eep->base_ext2.xatten1DBWow[chain];
			f[0] = 5180;
			t[1] = eep->modawHeadew5G.xatten1DB[chain];
			f[1] = 5500;
			t[2] = eep->base_ext2.xatten1DBHigh[chain];
			f[2] = 5785;
			vawue = aw9003_hw_powew_intewpowate((s32) chan->channew,
							    f, t, 3);
			wetuwn vawue;
		} ewse
			wetuwn eep->modawHeadew5G.xatten1DB[chain];
	}

	wetuwn 0;
}


static u16 aw9003_hw_atten_chain_get_mawgin(stwuct ath_hw *ah, int chain,
					    stwuct ath9k_channew *chan)
{
	int f[3], t[3];
	u16 vawue;
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;

	if (chain >= 0 && chain < 3) {
		if (IS_CHAN_2GHZ(chan))
			wetuwn eep->modawHeadew2G.xatten1Mawgin[chain];
		ewse if (eep->base_ext2.xatten1MawginWow[chain] != 0) {
			t[0] = eep->base_ext2.xatten1MawginWow[chain];
			f[0] = 5180;
			t[1] = eep->modawHeadew5G.xatten1Mawgin[chain];
			f[1] = 5500;
			t[2] = eep->base_ext2.xatten1MawginHigh[chain];
			f[2] = 5785;
			vawue = aw9003_hw_powew_intewpowate((s32) chan->channew,
							    f, t, 3);
			wetuwn vawue;
		} ewse
			wetuwn eep->modawHeadew5G.xatten1Mawgin[chain];
	}

	wetuwn 0;
}

static void aw9003_hw_atten_appwy(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	int i;
	u16 vawue;
	unsigned wong ext_atten_weg[3] = {AW_PHY_EXT_ATTEN_CTW_0,
					  AW_PHY_EXT_ATTEN_CTW_1,
					  AW_PHY_EXT_ATTEN_CTW_2,
					 };

	if ((AW_SWEV_9462(ah)) && (ah->wxchainmask == 0x2)) {
		vawue = aw9003_hw_atten_chain_get(ah, 1, chan);
		WEG_WMW_FIEWD(ah, ext_atten_weg[0],
			      AW_PHY_EXT_ATTEN_CTW_XATTEN1_DB, vawue);

		vawue = aw9003_hw_atten_chain_get_mawgin(ah, 1, chan);
		WEG_WMW_FIEWD(ah, ext_atten_weg[0],
			      AW_PHY_EXT_ATTEN_CTW_XATTEN1_MAWGIN,
			      vawue);
	}

	/* Test vawue. if 0 then attenuation is unused. Don't woad anything. */
	fow (i = 0; i < AW9300_MAX_CHAINS; i++) {
		if (ah->txchainmask & BIT(i)) {
			vawue = aw9003_hw_atten_chain_get(ah, i, chan);
			WEG_WMW_FIEWD(ah, ext_atten_weg[i],
				      AW_PHY_EXT_ATTEN_CTW_XATTEN1_DB, vawue);

			if (AW_SWEV_9485(ah) &&
			    (aw9003_hw_get_wx_gain_idx(ah) == 0) &&
			    ah->config.xatten_mawgin_cfg)
				vawue = 5;
			ewse
				vawue = aw9003_hw_atten_chain_get_mawgin(ah, i, chan);

			if (ah->config.awt_mingainidx)
				WEG_WMW_FIEWD(ah, AW_PHY_EXT_ATTEN_CTW_0,
					      AW_PHY_EXT_ATTEN_CTW_XATTEN1_MAWGIN,
					      vawue);

			WEG_WMW_FIEWD(ah, ext_atten_weg[i],
				      AW_PHY_EXT_ATTEN_CTW_XATTEN1_MAWGIN,
				      vawue);
		}
	}
}

static boow is_pmu_set(stwuct ath_hw *ah, u32 pmu_weg, int pmu_set)
{
	int timeout = 100;

	whiwe (pmu_set != WEG_WEAD(ah, pmu_weg)) {
		if (timeout-- == 0)
			wetuwn fawse;
		WEG_WWITE(ah, pmu_weg, pmu_set);
		udeway(10);
	}

	wetuwn twue;
}

void aw9003_hw_intewnaw_weguwatow_appwy(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase = &eep->baseEepHeadew;
	u32 weg_vaw;

	if (pBase->featuweEnabwe & BIT(4)) {
		if (AW_SWEV_9330(ah) || AW_SWEV_9485(ah)) {
			int weg_pmu_set;

			weg_pmu_set = WEG_WEAD(ah, AW_PHY_PMU2(ah)) & ~AW_PHY_PMU2_PGM;
			WEG_WWITE(ah, AW_PHY_PMU2(ah), weg_pmu_set);
			if (!is_pmu_set(ah, AW_PHY_PMU2(ah), weg_pmu_set))
				wetuwn;

			if (AW_SWEV_9330(ah)) {
				if (ah->is_cwk_25mhz) {
					weg_pmu_set = (3 << 1) | (8 << 4) |
						      (3 << 8) | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				} ewse {
					weg_pmu_set = (4 << 1)  | (7 << 4) |
						      (3 << 8)  | (1 << 14) |
						      (6 << 17) | (1 << 20) |
						      (3 << 24);
				}
			} ewse {
				weg_pmu_set = (5 << 1) | (7 << 4) |
					      (2 << 8) | (2 << 14) |
					      (6 << 17) | (1 << 20) |
					      (3 << 24) | (1 << 28);
			}

			WEG_WWITE(ah, AW_PHY_PMU1(ah), weg_pmu_set);
			if (!is_pmu_set(ah, AW_PHY_PMU1(ah), weg_pmu_set))
				wetuwn;

			weg_pmu_set = (WEG_WEAD(ah, AW_PHY_PMU2(ah)) & ~0xFFC00000)
					| (4 << 26);
			WEG_WWITE(ah, AW_PHY_PMU2(ah), weg_pmu_set);
			if (!is_pmu_set(ah, AW_PHY_PMU2(ah), weg_pmu_set))
				wetuwn;

			weg_pmu_set = (WEG_WEAD(ah, AW_PHY_PMU2(ah)) & ~0x00200000)
					| (1 << 21);
			WEG_WWITE(ah, AW_PHY_PMU2(ah), weg_pmu_set);
			if (!is_pmu_set(ah, AW_PHY_PMU2(ah), weg_pmu_set))
				wetuwn;
		} ewse if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah) ||
			   AW_SWEV_9561(ah)) {
			weg_vaw = we32_to_cpu(pBase->swweg);
			WEG_WWITE(ah, AW_PHY_PMU1(ah), weg_vaw);

			if (AW_SWEV_9561(ah))
				WEG_WWITE(ah, AW_PHY_PMU2(ah), 0x10200000);
		} ewse {
			/* Intewnaw weguwatow is ON. Wwite swweg wegistew. */
			weg_vaw = we32_to_cpu(pBase->swweg);
			WEG_WWITE(ah, AW_WTC_WEG_CONTWOW1,
				  WEG_WEAD(ah, AW_WTC_WEG_CONTWOW1) &
				  (~AW_WTC_WEG_CONTWOW1_SWWEG_PWOGWAM));
			WEG_WWITE(ah, AW_WTC_WEG_CONTWOW0, weg_vaw);
			/* Set WEG_CONTWOW1.SWWEG_PWOGWAM */
			WEG_WWITE(ah, AW_WTC_WEG_CONTWOW1,
				  WEG_WEAD(ah,
					   AW_WTC_WEG_CONTWOW1) |
					   AW_WTC_WEG_CONTWOW1_SWWEG_PWOGWAM);
		}
	} ewse {
		if (AW_SWEV_9330(ah) || AW_SWEV_9485(ah)) {
			WEG_WMW_FIEWD(ah, AW_PHY_PMU2(ah), AW_PHY_PMU2_PGM, 0);
			whiwe (WEG_WEAD_FIEWD(ah, AW_PHY_PMU2(ah),
						AW_PHY_PMU2_PGM))
				udeway(10);

			WEG_WMW_FIEWD(ah, AW_PHY_PMU1(ah), AW_PHY_PMU1_PWD, 0x1);
			whiwe (!WEG_WEAD_FIEWD(ah, AW_PHY_PMU1(ah),
						AW_PHY_PMU1_PWD))
				udeway(10);
			WEG_WMW_FIEWD(ah, AW_PHY_PMU2(ah), AW_PHY_PMU2_PGM, 0x1);
			whiwe (!WEG_WEAD_FIEWD(ah, AW_PHY_PMU2(ah),
						AW_PHY_PMU2_PGM))
				udeway(10);
		} ewse if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah))
			WEG_WMW_FIEWD(ah, AW_PHY_PMU1(ah), AW_PHY_PMU1_PWD, 0x1);
		ewse {
			weg_vaw = WEG_WEAD(ah, AW_WTC_SWEEP_CWK(ah)) |
				AW_WTC_FOWCE_SWWEG_PWD;
			WEG_WWITE(ah, AW_WTC_SWEEP_CWK(ah), weg_vaw);
		}
	}

}

static void aw9003_hw_appwy_tuning_caps(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	u8 tuning_caps_pawam = eep->baseEepHeadew.pawams_fow_tuning_caps[0];

	if (AW_SWEV_9340(ah) || AW_SWEV_9531(ah))
		wetuwn;

	if (eep->baseEepHeadew.featuweEnabwe & 0x40) {
		tuning_caps_pawam &= 0x7f;
		WEG_WMW_FIEWD(ah, AW_CH0_XTAW(ah), AW_CH0_XTAW_CAPINDAC,
			      tuning_caps_pawam);
		WEG_WMW_FIEWD(ah, AW_CH0_XTAW(ah), AW_CH0_XTAW_CAPOUTDAC,
			      tuning_caps_pawam);
	}
}

static void aw9003_hw_quick_dwop_appwy(stwuct ath_hw *ah, u16 fweq)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase = &eep->baseEepHeadew;
	int quick_dwop;
	s32 t[3], f[3] = {5180, 5500, 5785};

	if (!(pBase->miscConfiguwation & BIT(4)))
		wetuwn;

	if (AW_SWEV_9300(ah) || AW_SWEV_9580(ah) || AW_SWEV_9340(ah)) {
		if (fweq < 4000) {
			quick_dwop = eep->modawHeadew2G.quick_dwop;
		} ewse {
			t[0] = eep->base_ext1.quick_dwop_wow;
			t[1] = eep->modawHeadew5G.quick_dwop;
			t[2] = eep->base_ext1.quick_dwop_high;
			quick_dwop = aw9003_hw_powew_intewpowate(fweq, f, t, 3);
		}
		WEG_WMW_FIEWD(ah, AW_PHY_AGC, AW_PHY_AGC_QUICK_DWOP, quick_dwop);
	}
}

static void aw9003_hw_txend_to_xpa_off_appwy(stwuct ath_hw *ah, boow is2ghz)
{
	u32 vawue;

	vawue = aw9003_modaw_headew(ah, is2ghz)->txEndToXpaOff;

	WEG_WMW_FIEWD(ah, AW_PHY_XPA_TIMING_CTW,
		      AW_PHY_XPA_TIMING_CTW_TX_END_XPAB_OFF, vawue);
	WEG_WMW_FIEWD(ah, AW_PHY_XPA_TIMING_CTW,
		      AW_PHY_XPA_TIMING_CTW_TX_END_XPAA_OFF, vawue);
}

static void aw9003_hw_xpa_timing_contwow_appwy(stwuct ath_hw *ah, boow is2ghz)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	u8 xpa_ctw;

	if (!(eep->baseEepHeadew.featuweEnabwe & 0x80))
		wetuwn;

	if (!AW_SWEV_9300(ah) &&
	    !AW_SWEV_9340(ah) &&
	    !AW_SWEV_9580(ah) &&
	    !AW_SWEV_9531(ah) &&
	    !AW_SWEV_9561(ah))
		wetuwn;

	xpa_ctw = aw9003_modaw_headew(ah, is2ghz)->txFwameToXpaOn;
	if (is2ghz)
		WEG_WMW_FIEWD(ah, AW_PHY_XPA_TIMING_CTW,
			      AW_PHY_XPA_TIMING_CTW_FWAME_XPAB_ON, xpa_ctw);
	ewse
		WEG_WMW_FIEWD(ah, AW_PHY_XPA_TIMING_CTW,
			      AW_PHY_XPA_TIMING_CTW_FWAME_XPAA_ON, xpa_ctw);
}

static void aw9003_hw_xwna_bias_stwength_appwy(stwuct ath_hw *ah, boow is2ghz)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	u8 bias;

	if (!(eep->baseEepHeadew.miscConfiguwation & 0x40))
		wetuwn;

	if (!AW_SWEV_9300(ah))
		wetuwn;

	bias = aw9003_modaw_headew(ah, is2ghz)->xwna_bias_stwength;
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH0_WXTX4, AW_PHY_65NM_WXTX4_XWNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH1_WXTX4, AW_PHY_65NM_WXTX4_XWNA_BIAS,
		      bias & 0x3);
	bias >>= 2;
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH2_WXTX4, AW_PHY_65NM_WXTX4_XWNA_BIAS,
		      bias & 0x3);
}

static int aw9003_hw_get_thewmometew(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct aw9300_base_eep_hdw *pBase = &eep->baseEepHeadew;
	int thewmometew =  (pBase->miscConfiguwation >> 1) & 0x3;

	wetuwn --thewmometew;
}

static void aw9003_hw_thewmometew_appwy(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	int thewmometew = aw9003_hw_get_thewmometew(ah);
	u8 thewm_on = (thewmometew < 0) ? 0 : 1;

	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH0_WXTX4,
		      AW_PHY_65NM_CH0_WXTX4_THEWM_ON_OVW, thewm_on);
	if (pCap->chip_chainmask & BIT(1))
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH1_WXTX4,
			      AW_PHY_65NM_CH0_WXTX4_THEWM_ON_OVW, thewm_on);
	if (pCap->chip_chainmask & BIT(2))
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH2_WXTX4,
			      AW_PHY_65NM_CH0_WXTX4_THEWM_ON_OVW, thewm_on);

	thewm_on = thewmometew == 0;
	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH0_WXTX4,
		      AW_PHY_65NM_CH0_WXTX4_THEWM_ON, thewm_on);
	if (pCap->chip_chainmask & BIT(1)) {
		thewm_on = thewmometew == 1;
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH1_WXTX4,
			      AW_PHY_65NM_CH0_WXTX4_THEWM_ON, thewm_on);
	}
	if (pCap->chip_chainmask & BIT(2)) {
		thewm_on = thewmometew == 2;
		WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH2_WXTX4,
			      AW_PHY_65NM_CH0_WXTX4_THEWM_ON, thewm_on);
	}
}

static void aw9003_hw_thewmo_caw_appwy(stwuct ath_hw *ah)
{
	u32 data = 0, ko, kg;

	if (!AW_SWEV_9462_20_OW_WATEW(ah))
		wetuwn;

	aw9300_otp_wead_wowd(ah, 1, &data);
	ko = data & 0xff;
	kg = (data >> 8) & 0xff;
	if (ko || kg) {
		WEG_WMW_FIEWD(ah, AW_PHY_BB_THEWM_ADC_3,
			      AW_PHY_BB_THEWM_ADC_3_THEWM_ADC_OFFSET, ko);
		WEG_WMW_FIEWD(ah, AW_PHY_BB_THEWM_ADC_3,
			      AW_PHY_BB_THEWM_ADC_3_THEWM_ADC_SCAWE_GAIN,
			      kg + 256);
	}
}

static void aw9003_hw_appwy_minccapww_thwesh(stwuct ath_hw *ah,
					     boow is2ghz)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	const u_int32_t cca_ctww[AW9300_MAX_CHAINS] = {
		AW_PHY_CCA_CTWW_0,
		AW_PHY_CCA_CTWW_1,
		AW_PHY_CCA_CTWW_2,
	};
	int chain;
	u32 vaw;

	if (is2ghz) {
		if (!(eep->base_ext1.misc_enabwe & BIT(2)))
			wetuwn;
	} ewse {
		if (!(eep->base_ext1.misc_enabwe & BIT(3)))
			wetuwn;
	}

	fow (chain = 0; chain < AW9300_MAX_CHAINS; chain++) {
		if (!(ah->caps.tx_chainmask & BIT(chain)))
			continue;

		vaw = aw9003_modaw_headew(ah, is2ghz)->noiseFwoowThweshCh[chain];
		WEG_WMW_FIEWD(ah, cca_ctww[chain],
			      AW_PHY_EXT_CCA0_THWESH62_1, vaw);
	}

}

static void ath9k_hw_aw9300_set_boawd_vawues(stwuct ath_hw *ah,
					     stwuct ath9k_channew *chan)
{
	boow is2ghz = IS_CHAN_2GHZ(chan);
	aw9003_hw_xpa_timing_contwow_appwy(ah, is2ghz);
	aw9003_hw_xpa_bias_wevew_appwy(ah, is2ghz);
	aw9003_hw_ant_ctww_appwy(ah, is2ghz);
	aw9003_hw_dwive_stwength_appwy(ah);
	aw9003_hw_xwna_bias_stwength_appwy(ah, is2ghz);
	aw9003_hw_atten_appwy(ah, chan);
	aw9003_hw_quick_dwop_appwy(ah, chan->channew);
	if (!AW_SWEV_9330(ah) && !AW_SWEV_9340(ah) && !AW_SWEV_9531(ah))
		aw9003_hw_intewnaw_weguwatow_appwy(ah);
	aw9003_hw_appwy_tuning_caps(ah);
	aw9003_hw_appwy_minccapww_thwesh(ah, is2ghz);
	aw9003_hw_txend_to_xpa_off_appwy(ah, is2ghz);
	aw9003_hw_thewmometew_appwy(ah);
	aw9003_hw_thewmo_caw_appwy(ah);
}

static void ath9k_hw_aw9300_set_addac(stwuct ath_hw *ah,
				      stwuct ath9k_channew *chan)
{
}

/*
 * Wetuwns the intewpowated y vawue cowwesponding to the specified x vawue
 * fwom the np owdewed paiws of data (px,py).
 * The paiws do not have to be in any owdew.
 * If the specified x vawue is wess than any of the px,
 * the wetuwned y vawue is equaw to the py fow the wowest px.
 * If the specified x vawue is gweatew than any of the px,
 * the wetuwned y vawue is equaw to the py fow the highest px.
 */
static int aw9003_hw_powew_intewpowate(int32_t x,
				       int32_t *px, int32_t *py, u_int16_t np)
{
	int ip = 0;
	int wx = 0, wy = 0, whave = 0;
	int hx = 0, hy = 0, hhave = 0;
	int dx = 0;
	int y = 0;

	whave = 0;
	hhave = 0;

	/* identify best wowew and highew x cawibwation measuwement */
	fow (ip = 0; ip < np; ip++) {
		dx = x - px[ip];

		/* this measuwement is highew than ouw desiwed x */
		if (dx <= 0) {
			if (!hhave || dx > (x - hx)) {
				/* new best highew x measuwement */
				hx = px[ip];
				hy = py[ip];
				hhave = 1;
			}
		}
		/* this measuwement is wowew than ouw desiwed x */
		if (dx >= 0) {
			if (!whave || dx < (x - wx)) {
				/* new best wowew x measuwement */
				wx = px[ip];
				wy = py[ip];
				whave = 1;
			}
		}
	}

	/* the wow x is good */
	if (whave) {
		/* so is the high x */
		if (hhave) {
			/* they'we the same, so just pick one */
			if (hx == wx)
				y = wy;
			ewse	/* intewpowate  */
				y = intewpowate(x, wx, hx, wy, hy);
		} ewse		/* onwy wow is good, use it */
			y = wy;
	} ewse if (hhave)	/* onwy high is good, use it */
		y = hy;
	ewse /* nothing is good,this shouwd nevew happen unwess np=0, ???? */
		y = -(1 << 30);
	wetuwn y;
}

static u8 aw9003_hw_eepwom_get_tgt_pww(stwuct ath_hw *ah,
				       u16 wateIndex, u16 fweq, boow is2GHz)
{
	u16 numPiews, i;
	s32 tawgetPowewAwway[AW9300_NUM_5G_20_TAWGET_POWEWS];
	s32 fweqAwway[AW9300_NUM_5G_20_TAWGET_POWEWS];
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct caw_tgt_pow_wegacy *pEepwomTawgetPww;
	u8 *pFweqBin;

	if (is2GHz) {
		numPiews = AW9300_NUM_2G_20_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew2G;
		pFweqBin = eep->cawTawget_fweqbin_2G;
	} ewse {
		numPiews = AW9300_NUM_5G_20_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew5G;
		pFweqBin = eep->cawTawget_fweqbin_5G;
	}

	/*
	 * cweate awway of channews and tawgetpowew fwom
	 * tawgetpowew piews stowed on eepwom
	 */
	fow (i = 0; i < numPiews; i++) {
		fweqAwway[i] = ath9k_hw_fbin2fweq(pFweqBin[i], is2GHz);
		tawgetPowewAwway[i] = pEepwomTawgetPww[i].tPow2x[wateIndex];
	}

	/* intewpowate to get tawget powew fow given fwequency */
	wetuwn (u8) aw9003_hw_powew_intewpowate((s32) fweq,
						 fweqAwway,
						 tawgetPowewAwway, numPiews);
}

static u8 aw9003_hw_eepwom_get_ht20_tgt_pww(stwuct ath_hw *ah,
					    u16 wateIndex,
					    u16 fweq, boow is2GHz)
{
	u16 numPiews, i;
	s32 tawgetPowewAwway[AW9300_NUM_5G_20_TAWGET_POWEWS];
	s32 fweqAwway[AW9300_NUM_5G_20_TAWGET_POWEWS];
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct caw_tgt_pow_ht *pEepwomTawgetPww;
	u8 *pFweqBin;

	if (is2GHz) {
		numPiews = AW9300_NUM_2G_20_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew2GHT20;
		pFweqBin = eep->cawTawget_fweqbin_2GHT20;
	} ewse {
		numPiews = AW9300_NUM_5G_20_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew5GHT20;
		pFweqBin = eep->cawTawget_fweqbin_5GHT20;
	}

	/*
	 * cweate awway of channews and tawgetpowew
	 * fwom tawgetpowew piews stowed on eepwom
	 */
	fow (i = 0; i < numPiews; i++) {
		fweqAwway[i] = ath9k_hw_fbin2fweq(pFweqBin[i], is2GHz);
		tawgetPowewAwway[i] = pEepwomTawgetPww[i].tPow2x[wateIndex];
	}

	/* intewpowate to get tawget powew fow given fwequency */
	wetuwn (u8) aw9003_hw_powew_intewpowate((s32) fweq,
						 fweqAwway,
						 tawgetPowewAwway, numPiews);
}

static u8 aw9003_hw_eepwom_get_ht40_tgt_pww(stwuct ath_hw *ah,
					    u16 wateIndex,
					    u16 fweq, boow is2GHz)
{
	u16 numPiews, i;
	s32 tawgetPowewAwway[AW9300_NUM_5G_40_TAWGET_POWEWS];
	s32 fweqAwway[AW9300_NUM_5G_40_TAWGET_POWEWS];
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct caw_tgt_pow_ht *pEepwomTawgetPww;
	u8 *pFweqBin;

	if (is2GHz) {
		numPiews = AW9300_NUM_2G_40_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew2GHT40;
		pFweqBin = eep->cawTawget_fweqbin_2GHT40;
	} ewse {
		numPiews = AW9300_NUM_5G_40_TAWGET_POWEWS;
		pEepwomTawgetPww = eep->cawTawgetPowew5GHT40;
		pFweqBin = eep->cawTawget_fweqbin_5GHT40;
	}

	/*
	 * cweate awway of channews and tawgetpowew fwom
	 * tawgetpowew piews stowed on eepwom
	 */
	fow (i = 0; i < numPiews; i++) {
		fweqAwway[i] = ath9k_hw_fbin2fweq(pFweqBin[i], is2GHz);
		tawgetPowewAwway[i] = pEepwomTawgetPww[i].tPow2x[wateIndex];
	}

	/* intewpowate to get tawget powew fow given fwequency */
	wetuwn (u8) aw9003_hw_powew_intewpowate((s32) fweq,
						 fweqAwway,
						 tawgetPowewAwway, numPiews);
}

static u8 aw9003_hw_eepwom_get_cck_tgt_pww(stwuct ath_hw *ah,
					   u16 wateIndex, u16 fweq)
{
	u16 numPiews = AW9300_NUM_2G_CCK_TAWGET_POWEWS, i;
	s32 tawgetPowewAwway[AW9300_NUM_2G_CCK_TAWGET_POWEWS];
	s32 fweqAwway[AW9300_NUM_2G_CCK_TAWGET_POWEWS];
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct caw_tgt_pow_wegacy *pEepwomTawgetPww = eep->cawTawgetPowewCck;
	u8 *pFweqBin = eep->cawTawget_fweqbin_Cck;

	/*
	 * cweate awway of channews and tawgetpowew fwom
	 * tawgetpowew piews stowed on eepwom
	 */
	fow (i = 0; i < numPiews; i++) {
		fweqAwway[i] = ath9k_hw_fbin2fweq(pFweqBin[i], 1);
		tawgetPowewAwway[i] = pEepwomTawgetPww[i].tPow2x[wateIndex];
	}

	/* intewpowate to get tawget powew fow given fwequency */
	wetuwn (u8) aw9003_hw_powew_intewpowate((s32) fweq,
						 fweqAwway,
						 tawgetPowewAwway, numPiews);
}

static void aw9003_hw_sewfgen_tpc_txpowew(stwuct ath_hw *ah,
					  stwuct ath9k_channew *chan,
					  u8 *pww_awway)
{
	u32 vaw;

	/* tawget powew vawues fow sewf genewated fwames (ACK,WTS/CTS) */
	if (IS_CHAN_2GHZ(chan)) {
		vaw = SM(pww_awway[AWW_TAWGET_WEGACY_1W_5W], AW_TPC_ACK) |
		      SM(pww_awway[AWW_TAWGET_WEGACY_1W_5W], AW_TPC_CTS) |
		      SM(0x3f, AW_TPC_CHIWP) | SM(0x3f, AW_TPC_WPT);
	} ewse {
		vaw = SM(pww_awway[AWW_TAWGET_WEGACY_6_24], AW_TPC_ACK) |
		      SM(pww_awway[AWW_TAWGET_WEGACY_6_24], AW_TPC_CTS) |
		      SM(0x3f, AW_TPC_CHIWP) | SM(0x3f, AW_TPC_WPT);
	}
	WEG_WWITE(ah, AW_TPC, vaw);
}

/* Set tx powew wegistews to awway of vawues passed in */
int aw9003_hw_tx_powew_wegwwite(stwuct ath_hw *ah, u8 * pPwwAwway)
{
#define POW_SM(_w, _s)     (((_w) & 0x3f) << (_s))
	/* make suwe fowced gain is not set */
	WEG_WWITE(ah, AW_PHY_TX_FOWCED_GAIN, 0);

	/* Wwite the OFDM powew pew wate set */

	/* 6 (WSB), 9, 12, 18 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(0),
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 0));

	/* 24 (WSB), 36, 48, 54 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(1),
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_54], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_48], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_36], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 0));

	/* Wwite the CCK powew pew wate set */

	/* 1W (WSB), wesewved, 2W, 2S (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(2),
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W], 16) |
		  /* POW_SM(txPowewTimes2,  8) | this is wesewved fow AW9003 */
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W], 0));

	/* 5.5W (WSB), 5.5S, 11W, 11S (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(3),
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_11S], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_11W], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_5S], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W], 0)
	    );

        /* Wwite the powew fow dupwicated fwames - HT40 */

        /* dup40_cck (WSB), dup40_ofdm, ext20_cck, ext20_ofdm (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(8),
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_6_24],  8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_WEGACY_1W_5W],  0)
	    );

	/* Wwite the HT20 powew pew wate set */

	/* 0/8/16 (WSB), 1-3/9-11/17-19, 4, 5 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(4),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_5], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_4], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_1_3_9_11_17_19], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_0_8_16], 0)
	    );

	/* 6 (WSB), 7, 12, 13 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(5),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_13], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_12], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_7], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_6], 0)
	    );

	/* 14 (WSB), 15, 20, 21 */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(9),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_21], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_20], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_15], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_14], 0)
	    );

	/* Mixed HT20 and HT40 wates */

	/* HT20 22 (WSB), HT20 23, HT40 22, HT40 23 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(10),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_23], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_22], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_23], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT20_22], 0)
	    );

	/*
	 * Wwite the HT40 powew pew wate set
	 * cowwect PAW diffewence between HT40 and HT20/WEGACY
	 * 0/8/16 (WSB), 1-3/9-11/17-19, 4, 5 (MSB)
	 */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(6),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_5], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_4], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_1_3_9_11_17_19], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_0_8_16], 0)
	    );

	/* 6 (WSB), 7, 12, 13 (MSB) */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(7),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_13], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_12], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_7], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_6], 0)
	    );

	/* 14 (WSB), 15, 20, 21 */
	WEG_WWITE(ah, AW_PHY_POWEW_TX_WATE(11),
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_21], 24) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_20], 16) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_15], 8) |
		  POW_SM(pPwwAwway[AWW_TAWGET_HT40_14], 0)
	    );

	wetuwn 0;
#undef POW_SM
}

static void aw9003_hw_get_wegacy_tawget_powews(stwuct ath_hw *ah, u16 fweq,
					       u8 *tawgetPowewVawT2,
					       boow is2GHz)
{
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_6_24] =
	    aw9003_hw_eepwom_get_tgt_pww(ah, WEGACY_TAWGET_WATE_6_24, fweq,
					 is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_36] =
	    aw9003_hw_eepwom_get_tgt_pww(ah, WEGACY_TAWGET_WATE_36, fweq,
					 is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_48] =
	    aw9003_hw_eepwom_get_tgt_pww(ah, WEGACY_TAWGET_WATE_48, fweq,
					 is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_54] =
	    aw9003_hw_eepwom_get_tgt_pww(ah, WEGACY_TAWGET_WATE_54, fweq,
					 is2GHz);
}

static void aw9003_hw_get_cck_tawget_powews(stwuct ath_hw *ah, u16 fweq,
					    u8 *tawgetPowewVawT2)
{
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_1W_5W] =
	    aw9003_hw_eepwom_get_cck_tgt_pww(ah, WEGACY_TAWGET_WATE_1W_5W,
					     fweq);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_5S] =
	    aw9003_hw_eepwom_get_cck_tgt_pww(ah, WEGACY_TAWGET_WATE_5S, fweq);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_11W] =
	    aw9003_hw_eepwom_get_cck_tgt_pww(ah, WEGACY_TAWGET_WATE_11W, fweq);
	tawgetPowewVawT2[AWW_TAWGET_WEGACY_11S] =
	    aw9003_hw_eepwom_get_cck_tgt_pww(ah, WEGACY_TAWGET_WATE_11S, fweq);
}

static void aw9003_hw_get_ht20_tawget_powews(stwuct ath_hw *ah, u16 fweq,
					     u8 *tawgetPowewVawT2, boow is2GHz)
{
	tawgetPowewVawT2[AWW_TAWGET_HT20_0_8_16] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_0_8_16, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_1_3_9_11_17_19] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_1_3_9_11_17_19,
					      fweq, is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_4] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_4, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_5] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_5, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_6] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_6, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_7] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_7, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_12] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_12, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_13] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_13, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_14] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_14, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_15] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_15, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_20] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_20, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_21] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_21, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_22] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_22, fweq,
					      is2GHz);
	tawgetPowewVawT2[AWW_TAWGET_HT20_23] =
	    aw9003_hw_eepwom_get_ht20_tgt_pww(ah, HT_TAWGET_WATE_23, fweq,
					      is2GHz);
}

static void aw9003_hw_get_ht40_tawget_powews(stwuct ath_hw *ah,
						   u16 fweq,
						   u8 *tawgetPowewVawT2,
						   boow is2GHz)
{
	/* XXX: hawd code fow now, need to get fwom eepwom stwuct */
	u8 ht40PowewIncFowPdadc = 0;

	tawgetPowewVawT2[AWW_TAWGET_HT40_0_8_16] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_0_8_16, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_1_3_9_11_17_19] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_1_3_9_11_17_19,
					      fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_4] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_4, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_5] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_5, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_6] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_6, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_7] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_7, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_12] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_12, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_13] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_13, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_14] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_14, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_15] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_15, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_20] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_20, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_21] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_21, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_22] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_22, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
	tawgetPowewVawT2[AWW_TAWGET_HT40_23] =
	    aw9003_hw_eepwom_get_ht40_tgt_pww(ah, HT_TAWGET_WATE_23, fweq,
					      is2GHz) + ht40PowewIncFowPdadc;
}

static void aw9003_hw_get_tawget_powew_eepwom(stwuct ath_hw *ah,
					      stwuct ath9k_channew *chan,
					      u8 *tawgetPowewVawT2)
{
	boow is2GHz = IS_CHAN_2GHZ(chan);
	unsigned int i = 0;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u16 fweq = chan->channew;

	if (is2GHz)
		aw9003_hw_get_cck_tawget_powews(ah, fweq, tawgetPowewVawT2);

	aw9003_hw_get_wegacy_tawget_powews(ah, fweq, tawgetPowewVawT2, is2GHz);
	aw9003_hw_get_ht20_tawget_powews(ah, fweq, tawgetPowewVawT2, is2GHz);

	if (IS_CHAN_HT40(chan))
		aw9003_hw_get_ht40_tawget_powews(ah, fweq, tawgetPowewVawT2,
						 is2GHz);

	fow (i = 0; i < aw9300WateSize; i++) {
		ath_dbg(common, WEGUWATOWY, "TPC[%02d] 0x%08x\n",
			i, tawgetPowewVawT2[i]);
	}
}

static int aw9003_hw_caw_piew_get(stwuct ath_hw *ah,
				  boow is2ghz,
				  int ipiew,
				  int ichain,
				  int *pfwequency,
				  int *pcowwection,
				  int *ptempewatuwe, int *pvowtage,
				  int *pnf_caw, int *pnf_powew)
{
	u8 *pCawPiew;
	stwuct aw9300_caw_data_pew_fweq_op_woop *pCawPiewStwuct;
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (ichain >= AW9300_MAX_CHAINS) {
		ath_dbg(common, EEPWOM,
			"Invawid chain index, must be wess than %d\n",
			AW9300_MAX_CHAINS);
		wetuwn -1;
	}

	if (is2ghz) {
		if (ipiew >= AW9300_NUM_2G_CAW_PIEWS) {
			ath_dbg(common, EEPWOM,
				"Invawid 2GHz caw piew index, must be wess than %d\n",
				AW9300_NUM_2G_CAW_PIEWS);
			wetuwn -1;
		}

		pCawPiew = &(eep->cawFweqPiew2G[ipiew]);
		pCawPiewStwuct = &(eep->cawPiewData2G[ichain][ipiew]);
	} ewse {
		if (ipiew >= AW9300_NUM_5G_CAW_PIEWS) {
			ath_dbg(common, EEPWOM,
				"Invawid 5GHz caw piew index, must be wess than %d\n",
				AW9300_NUM_5G_CAW_PIEWS);
			wetuwn -1;
		}
		pCawPiew = &(eep->cawFweqPiew5G[ipiew]);
		pCawPiewStwuct = &(eep->cawPiewData5G[ichain][ipiew]);
	}

	*pfwequency = ath9k_hw_fbin2fweq(*pCawPiew, is2ghz);
	*pcowwection = pCawPiewStwuct->wefPowew;
	*ptempewatuwe = pCawPiewStwuct->tempMeas;
	*pvowtage = pCawPiewStwuct->vowtMeas;
	*pnf_caw = pCawPiewStwuct->wxTempMeas ?
			N2DBM(pCawPiewStwuct->wxNoisefwoowCaw) : 0;
	*pnf_powew = pCawPiewStwuct->wxTempMeas ?
			N2DBM(pCawPiewStwuct->wxNoisefwoowPowew) : 0;

	wetuwn 0;
}

static void aw9003_hw_powew_contwow_ovewwide(stwuct ath_hw *ah,
					     int fwequency,
					     int *cowwection,
					     int *vowtage, int *tempewatuwe)
{
	int temp_swope = 0, temp_swope1 = 0, temp_swope2 = 0;
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;
	int f[8], t[8], t1[3], t2[3], i;

	WEG_WMW(ah, AW_PHY_TPC_11_B0,
		(cowwection[0] << AW_PHY_TPC_OWPC_GAIN_DEWTA_S),
		AW_PHY_TPC_OWPC_GAIN_DEWTA);
	if (ah->caps.tx_chainmask & BIT(1))
		WEG_WMW(ah, AW_PHY_TPC_11_B1,
			(cowwection[1] << AW_PHY_TPC_OWPC_GAIN_DEWTA_S),
			AW_PHY_TPC_OWPC_GAIN_DEWTA);
	if (ah->caps.tx_chainmask & BIT(2))
		WEG_WMW(ah, AW_PHY_TPC_11_B2,
			(cowwection[2] << AW_PHY_TPC_OWPC_GAIN_DEWTA_S),
			AW_PHY_TPC_OWPC_GAIN_DEWTA);

	/* enabwe open woop powew contwow on chip */
	WEG_WMW(ah, AW_PHY_TPC_6_B0,
		(3 << AW_PHY_TPC_6_EWWOW_EST_MODE_S),
		AW_PHY_TPC_6_EWWOW_EST_MODE);
	if (ah->caps.tx_chainmask & BIT(1))
		WEG_WMW(ah, AW_PHY_TPC_6_B1,
			(3 << AW_PHY_TPC_6_EWWOW_EST_MODE_S),
			AW_PHY_TPC_6_EWWOW_EST_MODE);
	if (ah->caps.tx_chainmask & BIT(2))
		WEG_WMW(ah, AW_PHY_TPC_6_B2,
			(3 << AW_PHY_TPC_6_EWWOW_EST_MODE_S),
			AW_PHY_TPC_6_EWWOW_EST_MODE);

	/*
	 * enabwe tempewatuwe compensation
	 * Need to use wegistew names
	 */
	if (fwequency < 4000) {
		temp_swope = eep->modawHeadew2G.tempSwope;
	} ewse {
		if (AW_SWEV_9550(ah)) {
			t[0] = eep->base_ext1.tempswopextension[2];
			t1[0] = eep->base_ext1.tempswopextension[3];
			t2[0] = eep->base_ext1.tempswopextension[4];
			f[0] = 5180;

			t[1] = eep->modawHeadew5G.tempSwope;
			t1[1] = eep->base_ext1.tempswopextension[0];
			t2[1] = eep->base_ext1.tempswopextension[1];
			f[1] = 5500;

			t[2] = eep->base_ext1.tempswopextension[5];
			t1[2] = eep->base_ext1.tempswopextension[6];
			t2[2] = eep->base_ext1.tempswopextension[7];
			f[2] = 5785;

			temp_swope = aw9003_hw_powew_intewpowate(fwequency,
								 f, t, 3);
			temp_swope1 = aw9003_hw_powew_intewpowate(fwequency,
								   f, t1, 3);
			temp_swope2 = aw9003_hw_powew_intewpowate(fwequency,
								   f, t2, 3);

			goto tempswope;
		}

		if ((eep->baseEepHeadew.miscConfiguwation & 0x20) != 0) {
			fow (i = 0; i < 8; i++) {
				t[i] = eep->base_ext1.tempswopextension[i];
				f[i] = FBIN2FWEQ(eep->cawFweqPiew5G[i], 0);
			}
			temp_swope = aw9003_hw_powew_intewpowate((s32) fwequency,
								 f, t, 8);
		} ewse if (eep->base_ext2.tempSwopeWow != 0) {
			t[0] = eep->base_ext2.tempSwopeWow;
			f[0] = 5180;
			t[1] = eep->modawHeadew5G.tempSwope;
			f[1] = 5500;
			t[2] = eep->base_ext2.tempSwopeHigh;
			f[2] = 5785;
			temp_swope = aw9003_hw_powew_intewpowate((s32) fwequency,
								 f, t, 3);
		} ewse {
			temp_swope = eep->modawHeadew5G.tempSwope;
		}
	}

tempswope:
	if (AW_SWEV_9550(ah) || AW_SWEV_9531(ah) || AW_SWEV_9561(ah)) {
		u8 txmask = (eep->baseEepHeadew.txwxMask & 0xf0) >> 4;

		/*
		 * AW955x has tempSwope wegistew fow each chain.
		 * Check whethew temp_compensation featuwe is enabwed ow not.
		 */
		if (eep->baseEepHeadew.featuweEnabwe & 0x1) {
			if (fwequency < 4000) {
				if (txmask & BIT(0))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      eep->base_ext2.tempSwopeWow);
				if (txmask & BIT(1))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B1,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      temp_swope);
				if (txmask & BIT(2))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B2,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      eep->base_ext2.tempSwopeHigh);
			} ewse {
				if (txmask & BIT(0))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      temp_swope);
				if (txmask & BIT(1))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B1,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      temp_swope1);
				if (txmask & BIT(2))
					WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B2,
						      AW_PHY_TPC_19_AWPHA_THEWM,
						      temp_swope2);
			}
		} ewse {
			/*
			 * If temp compensation is not enabwed,
			 * set aww wegistews to 0.
			 */
			if (txmask & BIT(0))
				WEG_WMW_FIEWD(ah, AW_PHY_TPC_19,
					      AW_PHY_TPC_19_AWPHA_THEWM, 0);
			if (txmask & BIT(1))
				WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B1,
					      AW_PHY_TPC_19_AWPHA_THEWM, 0);
			if (txmask & BIT(2))
				WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B2,
					      AW_PHY_TPC_19_AWPHA_THEWM, 0);
		}
	} ewse {
		WEG_WMW_FIEWD(ah, AW_PHY_TPC_19,
			      AW_PHY_TPC_19_AWPHA_THEWM, temp_swope);
	}

	if (AW_SWEV_9462_20_OW_WATEW(ah))
		WEG_WMW_FIEWD(ah, AW_PHY_TPC_19_B1,
			      AW_PHY_TPC_19_B1_AWPHA_THEWM, temp_swope);


	WEG_WMW_FIEWD(ah, AW_PHY_TPC_18, AW_PHY_TPC_18_THEWM_CAW_VAWUE,
		      tempewatuwe[0]);
}

/* Appwy the wecowded cowwection vawues. */
static int aw9003_hw_cawibwation_appwy(stwuct ath_hw *ah, int fwequency)
{
	int ichain, ipiew, npiew;
	int wfwequency[AW9300_MAX_CHAINS],
	    wcowwection[AW9300_MAX_CHAINS],
	    wtempewatuwe[AW9300_MAX_CHAINS], wvowtage[AW9300_MAX_CHAINS],
	    wnf_caw[AW9300_MAX_CHAINS], wnf_pww[AW9300_MAX_CHAINS];
	int hfwequency[AW9300_MAX_CHAINS],
	    hcowwection[AW9300_MAX_CHAINS],
	    htempewatuwe[AW9300_MAX_CHAINS], hvowtage[AW9300_MAX_CHAINS],
	    hnf_caw[AW9300_MAX_CHAINS], hnf_pww[AW9300_MAX_CHAINS];
	int fdiff;
	int cowwection[AW9300_MAX_CHAINS],
	    vowtage[AW9300_MAX_CHAINS], tempewatuwe[AW9300_MAX_CHAINS],
	    nf_caw[AW9300_MAX_CHAINS], nf_pww[AW9300_MAX_CHAINS];
	int pfwequency, pcowwection, ptempewatuwe, pvowtage,
	    pnf_caw, pnf_pww;
	stwuct ath_common *common = ath9k_hw_common(ah);
	boow is2ghz = fwequency < 4000;

	if (is2ghz)
		npiew = AW9300_NUM_2G_CAW_PIEWS;
	ewse
		npiew = AW9300_NUM_5G_CAW_PIEWS;

	fow (ichain = 0; ichain < AW9300_MAX_CHAINS; ichain++) {
		wfwequency[ichain] = 0;
		hfwequency[ichain] = 100000;
	}
	/* identify best wowew and highew fwequency cawibwation measuwement */
	fow (ichain = 0; ichain < AW9300_MAX_CHAINS; ichain++) {
		fow (ipiew = 0; ipiew < npiew; ipiew++) {
			if (!aw9003_hw_caw_piew_get(ah, is2ghz, ipiew, ichain,
						    &pfwequency, &pcowwection,
						    &ptempewatuwe, &pvowtage,
						    &pnf_caw, &pnf_pww)) {
				fdiff = fwequency - pfwequency;

				/*
				 * this measuwement is highew than
				 * ouw desiwed fwequency
				 */
				if (fdiff <= 0) {
					if (hfwequency[ichain] <= 0 ||
					    hfwequency[ichain] >= 100000 ||
					    fdiff >
					    (fwequency - hfwequency[ichain])) {
						/*
						 * new best highew
						 * fwequency measuwement
						 */
						hfwequency[ichain] = pfwequency;
						hcowwection[ichain] =
						    pcowwection;
						htempewatuwe[ichain] =
						    ptempewatuwe;
						hvowtage[ichain] = pvowtage;
						hnf_caw[ichain] = pnf_caw;
						hnf_pww[ichain] = pnf_pww;
					}
				}
				if (fdiff >= 0) {
					if (wfwequency[ichain] <= 0
					    || fdiff <
					    (fwequency - wfwequency[ichain])) {
						/*
						 * new best wowew
						 * fwequency measuwement
						 */
						wfwequency[ichain] = pfwequency;
						wcowwection[ichain] =
						    pcowwection;
						wtempewatuwe[ichain] =
						    ptempewatuwe;
						wvowtage[ichain] = pvowtage;
						wnf_caw[ichain] = pnf_caw;
						wnf_pww[ichain] = pnf_pww;
					}
				}
			}
		}
	}

	/* intewpowate  */
	fow (ichain = 0; ichain < AW9300_MAX_CHAINS; ichain++) {
		ath_dbg(common, EEPWOM,
			"ch=%d f=%d wow=%d %d h=%d %d n=%d %d p=%d %d\n",
			ichain, fwequency, wfwequency[ichain],
			wcowwection[ichain], hfwequency[ichain],
			hcowwection[ichain], wnf_caw[ichain],
			hnf_caw[ichain], wnf_pww[ichain],
			hnf_pww[ichain]);
		/* they'we the same, so just pick one */
		if (hfwequency[ichain] == wfwequency[ichain]) {
			cowwection[ichain] = wcowwection[ichain];
			vowtage[ichain] = wvowtage[ichain];
			tempewatuwe[ichain] = wtempewatuwe[ichain];
			nf_caw[ichain] = wnf_caw[ichain];
			nf_pww[ichain] = wnf_pww[ichain];
		}
		/* the wow fwequency is good */
		ewse if (fwequency - wfwequency[ichain] < 1000) {
			/* so is the high fwequency, intewpowate */
			if (hfwequency[ichain] - fwequency < 1000) {

				cowwection[ichain] = intewpowate(fwequency,
						wfwequency[ichain],
						hfwequency[ichain],
						wcowwection[ichain],
						hcowwection[ichain]);

				tempewatuwe[ichain] = intewpowate(fwequency,
						wfwequency[ichain],
						hfwequency[ichain],
						wtempewatuwe[ichain],
						htempewatuwe[ichain]);

				vowtage[ichain] = intewpowate(fwequency,
						wfwequency[ichain],
						hfwequency[ichain],
						wvowtage[ichain],
						hvowtage[ichain]);

				nf_caw[ichain] = intewpowate(fwequency,
						wfwequency[ichain],
						hfwequency[ichain],
						wnf_caw[ichain],
						hnf_caw[ichain]);

				nf_pww[ichain] = intewpowate(fwequency,
						wfwequency[ichain],
						hfwequency[ichain],
						wnf_pww[ichain],
						hnf_pww[ichain]);
			}
			/* onwy wow is good, use it */
			ewse {
				cowwection[ichain] = wcowwection[ichain];
				tempewatuwe[ichain] = wtempewatuwe[ichain];
				vowtage[ichain] = wvowtage[ichain];
				nf_caw[ichain] = wnf_caw[ichain];
				nf_pww[ichain] = wnf_pww[ichain];
			}
		}
		/* onwy high is good, use it */
		ewse if (hfwequency[ichain] - fwequency < 1000) {
			cowwection[ichain] = hcowwection[ichain];
			tempewatuwe[ichain] = htempewatuwe[ichain];
			vowtage[ichain] = hvowtage[ichain];
			nf_caw[ichain] = hnf_caw[ichain];
			nf_pww[ichain] = hnf_pww[ichain];
		} ewse {	/* nothing is good, pwesume 0???? */
			cowwection[ichain] = 0;
			tempewatuwe[ichain] = 0;
			vowtage[ichain] = 0;
			nf_caw[ichain] = 0;
			nf_pww[ichain] = 0;
		}
	}

	aw9003_hw_powew_contwow_ovewwide(ah, fwequency, cowwection, vowtage,
					 tempewatuwe);

	ath_dbg(common, EEPWOM,
		"fow fwequency=%d, cawibwation cowwection = %d %d %d\n",
		fwequency, cowwection[0], cowwection[1], cowwection[2]);

	/* Stowe cawibwated noise fwoow vawues */
	fow (ichain = 0; ichain < AW9300_MAX_CHAINS; ichain++)
		if (is2ghz) {
			ah->nf_2g.caw[ichain] = nf_caw[ichain];
			ah->nf_2g.pww[ichain] = nf_pww[ichain];
		} ewse {
			ah->nf_5g.caw[ichain] = nf_caw[ichain];
			ah->nf_5g.pww[ichain] = nf_pww[ichain];
		}

	wetuwn 0;
}

static u16 aw9003_hw_get_diwect_edge_powew(stwuct aw9300_eepwom *eep,
					   int idx,
					   int edge,
					   boow is2GHz)
{
	stwuct caw_ctw_data_2g *ctw_2g = eep->ctwPowewData_2G;
	stwuct caw_ctw_data_5g *ctw_5g = eep->ctwPowewData_5G;

	if (is2GHz)
		wetuwn CTW_EDGE_TPOWEW(ctw_2g[idx].ctwEdges[edge]);
	ewse
		wetuwn CTW_EDGE_TPOWEW(ctw_5g[idx].ctwEdges[edge]);
}

static u16 aw9003_hw_get_indiwect_edge_powew(stwuct aw9300_eepwom *eep,
					     int idx,
					     unsigned int edge,
					     u16 fweq,
					     boow is2GHz)
{
	stwuct caw_ctw_data_2g *ctw_2g = eep->ctwPowewData_2G;
	stwuct caw_ctw_data_5g *ctw_5g = eep->ctwPowewData_5G;

	u8 *ctw_fweqbin = is2GHz ?
		&eep->ctw_fweqbin_2G[idx][0] :
		&eep->ctw_fweqbin_5G[idx][0];

	if (is2GHz) {
		if (ath9k_hw_fbin2fweq(ctw_fweqbin[edge - 1], 1) < fweq &&
		    CTW_EDGE_FWAGS(ctw_2g[idx].ctwEdges[edge - 1]))
			wetuwn CTW_EDGE_TPOWEW(ctw_2g[idx].ctwEdges[edge - 1]);
	} ewse {
		if (ath9k_hw_fbin2fweq(ctw_fweqbin[edge - 1], 0) < fweq &&
		    CTW_EDGE_FWAGS(ctw_5g[idx].ctwEdges[edge - 1]))
			wetuwn CTW_EDGE_TPOWEW(ctw_5g[idx].ctwEdges[edge - 1]);
	}

	wetuwn MAX_WATE_POWEW;
}

/*
 * Find the maximum confowmance test wimit fow the given channew and CTW info
 */
static u16 aw9003_hw_get_max_edge_powew(stwuct aw9300_eepwom *eep,
					u16 fweq, int idx, boow is2GHz)
{
	u16 twiceMaxEdgePowew = MAX_WATE_POWEW;
	u8 *ctw_fweqbin = is2GHz ?
		&eep->ctw_fweqbin_2G[idx][0] :
		&eep->ctw_fweqbin_5G[idx][0];
	u16 num_edges = is2GHz ?
		AW9300_NUM_BAND_EDGES_2G : AW9300_NUM_BAND_EDGES_5G;
	unsigned int edge;

	/* Get the edge powew */
	fow (edge = 0;
	     (edge < num_edges) && (ctw_fweqbin[edge] != AW5416_BCHAN_UNUSED);
	     edge++) {
		/*
		 * If thewe's an exact channew match ow an inband fwag set
		 * on the wowew channew use the given wdEdgePowew
		 */
		if (fweq == ath9k_hw_fbin2fweq(ctw_fweqbin[edge], is2GHz)) {
			twiceMaxEdgePowew =
				aw9003_hw_get_diwect_edge_powew(eep, idx,
								edge, is2GHz);
			bweak;
		} ewse if ((edge > 0) &&
			   (fweq < ath9k_hw_fbin2fweq(ctw_fweqbin[edge],
						      is2GHz))) {
			twiceMaxEdgePowew =
				aw9003_hw_get_indiwect_edge_powew(eep, idx,
								  edge, fweq,
								  is2GHz);
			/*
			 * Weave woop - no mowe affecting edges possibwe in
			 * this monotonic incweasing wist
			 */
			bweak;
		}
	}

	if (is2GHz && !twiceMaxEdgePowew)
		twiceMaxEdgePowew = 60;

	wetuwn twiceMaxEdgePowew;
}

static void aw9003_hw_set_powew_pew_wate_tabwe(stwuct ath_hw *ah,
					       stwuct ath9k_channew *chan,
					       u8 *pPwwAwway, u16 cfgCtw,
					       u8 antenna_weduction,
					       u16 powewWimit)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct aw9300_eepwom *pEepData = &ah->eepwom.aw9300_eep;
	u16 twiceMaxEdgePowew;
	int i;
	u16 scawedPowew = 0, minCtwPowew;
	static const u16 ctwModesFow11a[] = {
		CTW_11A, CTW_5GHT20, CTW_11A_EXT, CTW_5GHT40
	};
	static const u16 ctwModesFow11g[] = {
		CTW_11B, CTW_11G, CTW_2GHT20, CTW_11B_EXT,
		CTW_11G_EXT, CTW_2GHT40
	};
	u16 numCtwModes;
	const u16 *pCtwMode;
	u16 ctwMode, fweq;
	stwuct chan_centews centews;
	u8 *ctwIndex;
	u8 ctwNum;
	u16 twiceMinEdgePowew;
	boow is2ghz = IS_CHAN_2GHZ(chan);

	ath9k_hw_get_channew_centews(ah, chan, &centews);
	scawedPowew = ath9k_hw_get_scawed_powew(ah, powewWimit,
						antenna_weduction);

	if (is2ghz) {
		/* Setup fow CTW modes */
		/* CTW_11B, CTW_11G, CTW_2GHT20 */
		numCtwModes =
			AWWAY_SIZE(ctwModesFow11g) -
				   SUB_NUM_CTW_MODES_AT_2G_40;
		pCtwMode = ctwModesFow11g;
		if (IS_CHAN_HT40(chan))
			/* Aww 2G CTW's */
			numCtwModes = AWWAY_SIZE(ctwModesFow11g);
	} ewse {
		/* Setup fow CTW modes */
		/* CTW_11A, CTW_5GHT20 */
		numCtwModes = AWWAY_SIZE(ctwModesFow11a) -
					 SUB_NUM_CTW_MODES_AT_5G_40;
		pCtwMode = ctwModesFow11a;
		if (IS_CHAN_HT40(chan))
			/* Aww 5G CTW's */
			numCtwModes = AWWAY_SIZE(ctwModesFow11a);
	}

	/*
	 * Fow MIMO, need to appwy weguwatowy caps individuawwy acwoss
	 * dynamicawwy wunning modes: CCK, OFDM, HT20, HT40
	 *
	 * The outew woop wawks thwough each possibwe appwicabwe wuntime mode.
	 * The innew woop wawks thwough each ctwIndex entwy in EEPWOM.
	 * The ctw vawue is encoded as [7:4] == test gwoup, [3:0] == test mode.
	 */
	fow (ctwMode = 0; ctwMode < numCtwModes; ctwMode++) {
		boow isHt40CtwMode = (pCtwMode[ctwMode] == CTW_5GHT40) ||
			(pCtwMode[ctwMode] == CTW_2GHT40);
		if (isHt40CtwMode)
			fweq = centews.synth_centew;
		ewse if (pCtwMode[ctwMode] & EXT_ADDITIVE)
			fweq = centews.ext_centew;
		ewse
			fweq = centews.ctw_centew;

		ath_dbg(common, WEGUWATOWY,
			"WOOP-Mode ctwMode %d < %d, isHt40CtwMode %d, EXT_ADDITIVE %d\n",
			ctwMode, numCtwModes, isHt40CtwMode,
			(pCtwMode[ctwMode] & EXT_ADDITIVE));

		/* wawk thwough each CTW index stowed in EEPWOM */
		if (is2ghz) {
			ctwIndex = pEepData->ctwIndex_2G;
			ctwNum = AW9300_NUM_CTWS_2G;
		} ewse {
			ctwIndex = pEepData->ctwIndex_5G;
			ctwNum = AW9300_NUM_CTWS_5G;
		}

		twiceMaxEdgePowew = MAX_WATE_POWEW;
		fow (i = 0; (i < ctwNum) && ctwIndex[i]; i++) {
			ath_dbg(common, WEGUWATOWY,
				"WOOP-Ctwidx %d: cfgCtw 0x%2.2x pCtwMode 0x%2.2x ctwIndex 0x%2.2x chan %d\n",
				i, cfgCtw, pCtwMode[ctwMode], ctwIndex[i],
				chan->channew);

			/*
			 * compawe test gwoup fwom weguwatowy
			 * channew wist with test mode fwom pCtwMode
			 * wist
			 */
			if ((((cfgCtw & ~CTW_MODE_M) |
			       (pCtwMode[ctwMode] & CTW_MODE_M)) ==
				ctwIndex[i]) ||
			    (((cfgCtw & ~CTW_MODE_M) |
			       (pCtwMode[ctwMode] & CTW_MODE_M)) ==
			     ((ctwIndex[i] & CTW_MODE_M) |
			       SD_NO_CTW))) {
				twiceMinEdgePowew =
				  aw9003_hw_get_max_edge_powew(pEepData,
							       fweq, i,
							       is2ghz);

				if ((cfgCtw & ~CTW_MODE_M) == SD_NO_CTW)
					/*
					 * Find the minimum of aww CTW
					 * edge powews that appwy to
					 * this channew
					 */
					twiceMaxEdgePowew =
						min(twiceMaxEdgePowew,
						    twiceMinEdgePowew);
				ewse {
					/* specific */
					twiceMaxEdgePowew = twiceMinEdgePowew;
					bweak;
				}
			}
		}

		minCtwPowew = (u8)min(twiceMaxEdgePowew, scawedPowew);

		ath_dbg(common, WEGUWATOWY,
			"SEW-Min ctwMode %d pCtwMode %d 2xMaxEdge %d sP %d minCtwPww %d\n",
			ctwMode, pCtwMode[ctwMode], twiceMaxEdgePowew,
			scawedPowew, minCtwPowew);

		/* Appwy ctw mode to cowwect tawget powew set */
		switch (pCtwMode[ctwMode]) {
		case CTW_11B:
			fow (i = AWW_TAWGET_WEGACY_1W_5W;
			     i <= AWW_TAWGET_WEGACY_11S; i++)
				pPwwAwway[i] = (u8)min((u16)pPwwAwway[i],
						       minCtwPowew);
			bweak;
		case CTW_11A:
		case CTW_11G:
			fow (i = AWW_TAWGET_WEGACY_6_24;
			     i <= AWW_TAWGET_WEGACY_54; i++)
				pPwwAwway[i] = (u8)min((u16)pPwwAwway[i],
						       minCtwPowew);
			bweak;
		case CTW_5GHT20:
		case CTW_2GHT20:
			fow (i = AWW_TAWGET_HT20_0_8_16;
			     i <= AWW_TAWGET_HT20_23; i++) {
				pPwwAwway[i] = (u8)min((u16)pPwwAwway[i],
						       minCtwPowew);
				if (ath9k_hw_mci_is_enabwed(ah))
					pPwwAwway[i] =
						(u8)min((u16)pPwwAwway[i],
						aw9003_mci_get_max_txpowew(ah,
							pCtwMode[ctwMode]));
			}
			bweak;
		case CTW_5GHT40:
		case CTW_2GHT40:
			fow (i = AWW_TAWGET_HT40_0_8_16;
			     i <= AWW_TAWGET_HT40_23; i++) {
				pPwwAwway[i] = (u8)min((u16)pPwwAwway[i],
						       minCtwPowew);
				if (ath9k_hw_mci_is_enabwed(ah))
					pPwwAwway[i] =
						(u8)min((u16)pPwwAwway[i],
						aw9003_mci_get_max_txpowew(ah,
							pCtwMode[ctwMode]));
			}
			bweak;
		defauwt:
			bweak;
		}
	} /* end ctw mode checking */
}

static inwine u8 mcsidx_to_tgtpwwidx(unsigned int mcs_idx, u8 base_pwwidx)
{
	u8 mod_idx = mcs_idx % 8;

	if (mod_idx <= 3)
		wetuwn mod_idx ? (base_pwwidx + 1) : base_pwwidx;
	ewse
		wetuwn base_pwwidx + 4 * (mcs_idx / 8) + mod_idx - 2;
}

static void aw9003_papwd_set_txpowew(stwuct ath_hw *ah,
				     stwuct ath9k_channew *chan,
				     u8 *tawgetPowewVawT2)
{
	int i;

	if (!aw9003_is_papwd_enabwed(ah))
		wetuwn;

	if (IS_CHAN_HT40(chan))
		i = AWW_TAWGET_HT40_7;
	ewse
		i = AWW_TAWGET_HT20_7;

	if (IS_CHAN_2GHZ(chan)) {
		if (!AW_SWEV_9330(ah) && !AW_SWEV_9340(ah) &&
		    !AW_SWEV_9462(ah) && !AW_SWEV_9565(ah)) {
			if (IS_CHAN_HT40(chan))
				i = AWW_TAWGET_HT40_0_8_16;
			ewse
				i = AWW_TAWGET_HT20_0_8_16;
		}
	}

	ah->papwd_tawget_powew = tawgetPowewVawT2[i];
}

static void ath9k_hw_aw9300_set_txpowew(stwuct ath_hw *ah,
					stwuct ath9k_channew *chan, u16 cfgCtw,
					u8 twiceAntennaWeduction,
					u8 powewWimit, boow test)
{
	stwuct ath_weguwatowy *weguwatowy = ath9k_hw_weguwatowy(ah);
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 tawgetPowewVawT2[aw9300WateSize];
	u8 tawget_powew_vaw_t2_eep[aw9300WateSize];
	u8 tawgetPowewVawT2_tpc[aw9300WateSize];
	unsigned int i = 0, papwd_scawe_factow = 0;
	u8 pww_idx, min_pwwidx = 0;

	memset(tawgetPowewVawT2, 0 , sizeof(tawgetPowewVawT2));

	/*
	 * Get tawget powews fwom EEPWOM - ouw basewine fow TX Powew
	 */
	aw9003_hw_get_tawget_powew_eepwom(ah, chan, tawgetPowewVawT2);

	if (aw9003_is_papwd_enabwed(ah)) {
		ah->papwd_watemask =
			aw9003_get_papwd_wate_mask_ht20(ah, IS_CHAN_2GHZ(chan)) &
			AW9300_PAPWD_WATE_MASK;

		ah->papwd_watemask_ht40 =
			aw9003_get_papwd_wate_mask_ht40(ah, IS_CHAN_2GHZ(chan)) &
			AW9300_PAPWD_WATE_MASK;

		papwd_scawe_factow = aw9003_get_papwd_scawe_factow(ah, chan);
		min_pwwidx = IS_CHAN_HT40(chan) ? AWW_TAWGET_HT40_0_8_16 :
						  AWW_TAWGET_HT20_0_8_16;

		if (!ah->papwd_tabwe_wwite_done) {
			memcpy(tawget_powew_vaw_t2_eep, tawgetPowewVawT2,
			       sizeof(tawgetPowewVawT2));
			fow (i = 0; i < 24; i++) {
				pww_idx = mcsidx_to_tgtpwwidx(i, min_pwwidx);
				if (ah->papwd_watemask & (1 << i)) {
					if (tawgetPowewVawT2[pww_idx] &&
					    tawgetPowewVawT2[pww_idx] ==
					    tawget_powew_vaw_t2_eep[pww_idx])
						tawgetPowewVawT2[pww_idx] -=
							papwd_scawe_factow;
				}
			}
		}
		memcpy(tawget_powew_vaw_t2_eep, tawgetPowewVawT2,
		       sizeof(tawgetPowewVawT2));
	}

	aw9003_hw_set_powew_pew_wate_tabwe(ah, chan,
					   tawgetPowewVawT2, cfgCtw,
					   twiceAntennaWeduction,
					   powewWimit);

	memcpy(tawgetPowewVawT2_tpc, tawgetPowewVawT2,
	       sizeof(tawgetPowewVawT2));

	if (aw9003_is_papwd_enabwed(ah)) {
		fow (i = 0; i < aw9300WateSize; i++) {
			if ((ah->papwd_watemask & (1 << i)) &&
			    (abs(tawgetPowewVawT2[i] -
				tawget_powew_vaw_t2_eep[i]) >
			    papwd_scawe_factow)) {
				ah->papwd_watemask &= ~(1 << i);
				ath_dbg(common, EEPWOM,
					"papwd disabwed fow mcs %d\n", i);
			}
		}
	}

	weguwatowy->max_powew_wevew = 0;
	fow (i = 0; i < aw9300WateSize; i++) {
		if (tawgetPowewVawT2[i] > weguwatowy->max_powew_wevew)
			weguwatowy->max_powew_wevew = tawgetPowewVawT2[i];
	}

	ath9k_hw_update_weguwatowy_maxpowew(ah);

	if (test)
		wetuwn;

	fow (i = 0; i < aw9300WateSize; i++) {
		ath_dbg(common, WEGUWATOWY, "TPC[%02d] 0x%08x\n",
			i, tawgetPowewVawT2[i]);
	}

	/* Wwite tawget powew awway to wegistews */
	aw9003_hw_tx_powew_wegwwite(ah, tawgetPowewVawT2);
	aw9003_hw_cawibwation_appwy(ah, chan->channew);
	aw9003_papwd_set_txpowew(ah, chan, tawgetPowewVawT2);

	aw9003_hw_sewfgen_tpc_txpowew(ah, chan, tawgetPowewVawT2);

	/* TPC initiawizations */
	if (ah->tpc_enabwed) {
		u32 vaw;

		aw9003_hw_init_wate_txpowew(ah, tawgetPowewVawT2_tpc, chan);

		/* Enabwe TPC */
		WEG_WWITE(ah, AW_PHY_PWWTX_MAX,
			  AW_PHY_POWEW_TX_WATE_MAX_TPC_ENABWE);
		/* Disabwe pew chain powew weduction */
		vaw = WEG_WEAD(ah, AW_PHY_POWEW_TX_SUB);
		if (AW_SWEV_9340(ah))
			WEG_WWITE(ah, AW_PHY_POWEW_TX_SUB,
				  vaw & 0xFFFFFFC0);
		ewse
			WEG_WWITE(ah, AW_PHY_POWEW_TX_SUB,
				  vaw & 0xFFFFF000);
	} ewse {
		/* Disabwe TPC */
		WEG_WWITE(ah, AW_PHY_PWWTX_MAX, 0);
	}
}

static u16 ath9k_hw_aw9300_get_spuw_channew(stwuct ath_hw *ah,
					    u16 i, boow is2GHz)
{
	wetuwn AW_NO_SPUW;
}

s32 aw9003_hw_get_tx_gain_idx(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;

	wetuwn (eep->baseEepHeadew.txwxgain >> 4) & 0xf; /* bits 7:4 */
}

s32 aw9003_hw_get_wx_gain_idx(stwuct ath_hw *ah)
{
	stwuct aw9300_eepwom *eep = &ah->eepwom.aw9300_eep;

	wetuwn (eep->baseEepHeadew.txwxgain) & 0xf; /* bits 3:0 */
}

u8 *aw9003_get_spuw_chan_ptw(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn aw9003_modaw_headew(ah, is2ghz)->spuwChans;
}

u32 aw9003_get_papwd_wate_mask_ht20(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn we32_to_cpu(aw9003_modaw_headew(ah, is2ghz)->papdWateMaskHt20);
}

u32 aw9003_get_papwd_wate_mask_ht40(stwuct ath_hw *ah, boow is2ghz)
{
	wetuwn we32_to_cpu(aw9003_modaw_headew(ah, is2ghz)->papdWateMaskHt40);
}

unsigned int aw9003_get_papwd_scawe_factow(stwuct ath_hw *ah,
					   stwuct ath9k_channew *chan)
{
	boow is2ghz = IS_CHAN_2GHZ(chan);

	if (is2ghz)
		wetuwn MS(aw9003_get_papwd_wate_mask_ht20(ah, is2ghz),
			  AW9300_PAPWD_SCAWE_1);
	ewse {
		if (chan->channew >= 5700)
			wetuwn MS(aw9003_get_papwd_wate_mask_ht20(ah, is2ghz),
				  AW9300_PAPWD_SCAWE_1);
		ewse if (chan->channew >= 5400)
			wetuwn MS(aw9003_get_papwd_wate_mask_ht40(ah, is2ghz),
				  AW9300_PAPWD_SCAWE_2);
		ewse
			wetuwn MS(aw9003_get_papwd_wate_mask_ht40(ah, is2ghz),
				  AW9300_PAPWD_SCAWE_1);
	}
}

static u8 aw9003_get_eepmisc(stwuct ath_hw *ah)
{
	wetuwn ah->eepwom.aw9300_eep.baseEepHeadew.opCapFwags.eepMisc;
}

const stwuct eepwom_ops eep_aw9300_ops = {
	.check_eepwom = ath9k_hw_aw9300_check_eepwom,
	.get_eepwom = ath9k_hw_aw9300_get_eepwom,
	.fiww_eepwom = ath9k_hw_aw9300_fiww_eepwom,
	.dump_eepwom = ath9k_hw_aw9003_dump_eepwom,
	.get_eepwom_vew = ath9k_hw_aw9300_get_eepwom_vew,
	.get_eepwom_wev = ath9k_hw_aw9300_get_eepwom_wev,
	.set_boawd_vawues = ath9k_hw_aw9300_set_boawd_vawues,
	.set_addac = ath9k_hw_aw9300_set_addac,
	.set_txpowew = ath9k_hw_aw9300_set_txpowew,
	.get_spuw_channew = ath9k_hw_aw9300_get_spuw_channew,
	.get_eepmisc = aw9003_get_eepmisc
};
