// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
*
* Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
*
******************************************************************************/

#incwude <winux/kewnew.h>
#incwude "odm_pwecomp.h"

static boow CheckPositive(
	stwuct dm_odm_t *pDM_Odm, const u32 Condition1, const u32 Condition2
)
{
	u8 _BoawdType =
			((pDM_Odm->BoawdType & BIT4) >> 4) << 0 | /*  _GWNA */
			((pDM_Odm->BoawdType & BIT3) >> 3) << 1 | /*  _GPA */
			((pDM_Odm->BoawdType & BIT7) >> 7) << 2 | /*  _AWNA */
			((pDM_Odm->BoawdType & BIT6) >> 6) << 3 | /*  _APA */
			((pDM_Odm->BoawdType & BIT2) >> 2) << 4;  /*  _BT */

	u32 cond1 = Condition1, cond2 = Condition2;
	u32 dwivew1 =
		pDM_Odm->CutVewsion << 24 |
		pDM_Odm->SuppowtPwatfowm << 16 |
		pDM_Odm->PackageType << 12 |
		pDM_Odm->SuppowtIntewface << 8 |
		_BoawdType;

	u32 dwivew2 =
		pDM_Odm->TypeGWNA <<  0 |
		pDM_Odm->TypeGPA  <<  8 |
		pDM_Odm->TypeAWNA << 16 |
		pDM_Odm->TypeAPA  << 24;

	/*  Vawue Defined Check =============== */
	/* QFN Type [15:12] and Cut Vewsion [27:24] need to do vawue check */

	if (
		((cond1 & 0x0000F000) != 0) &&
		((cond1 & 0x0000F000) != (dwivew1 & 0x0000F000))
	)
		wetuwn fawse;

	if (
		((cond1 & 0x0F000000) != 0) &&
		((cond1 & 0x0F000000) != (dwivew1 & 0x0F000000))
	)
		wetuwn fawse;

	/*  Bit Defined Check ================ */
	/*  We don't cawe [31:28] and [23:20] */
	cond1   &= 0x000F0FFF;
	dwivew1 &= 0x000F0FFF;

	if ((cond1 & dwivew1) == cond1) {
		u32 bitMask = 0;

		if ((cond1 & 0x0F) == 0) /*  BoawdType is DONTCAWE */
			wetuwn twue;

		if ((cond1 & BIT0) != 0) /* GWNA */
			bitMask |= 0x000000FF;
		if ((cond1 & BIT1) != 0) /* GPA */
			bitMask |= 0x0000FF00;
		if ((cond1 & BIT2) != 0) /* AWNA */
			bitMask |= 0x00FF0000;
		if ((cond1 & BIT3) != 0) /* APA */
			bitMask |= 0xFF000000;

		/*  BoawdType of each WF path is matched */
		if ((cond2 & bitMask) == (dwivew2 & bitMask))
			wetuwn twue;

		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow CheckNegative(
	stwuct dm_odm_t *pDM_Odm, const u32  Condition1, const u32 Condition2
)
{
	wetuwn twue;
}

/******************************************************************************
*                           WadioA.TXT
******************************************************************************/

static u32 Awway_MP_8723B_WadioA[] = {
		0x000, 0x00010000,
		0x0B0, 0x000DFFE0,
		0x0FE, 0x00000000,
		0x0FE, 0x00000000,
		0x0FE, 0x00000000,
		0x0B1, 0x00000018,
		0x0FE, 0x00000000,
		0x0FE, 0x00000000,
		0x0FE, 0x00000000,
		0x0B2, 0x00084C00,
		0x0B5, 0x0000D2CC,
		0x0B6, 0x000925AA,
		0x0B7, 0x00000010,
		0x0B8, 0x0000907F,
		0x05C, 0x00000002,
		0x07C, 0x00000002,
		0x07E, 0x00000005,
		0x08B, 0x0006FC00,
		0x0B0, 0x000FF9F0,
		0x01C, 0x000739D2,
		0x01E, 0x00000000,
		0x0DF, 0x00000780,
		0x050, 0x00067435,
	0x80002000, 0x00000000, 0x40000000, 0x00000000,
		0x051, 0x0006B10E,
	0x90003000, 0x00000000, 0x40000000, 0x00000000,
		0x051, 0x0006B10E,
	0x90004000, 0x00000000, 0x40000000, 0x00000000,
		0x051, 0x0006B10E,
	0xA0000000, 0x00000000,
		0x051, 0x0006B04E,
	0xB0000000, 0x00000000,
		0x052, 0x000007D2,
		0x053, 0x00000000,
		0x054, 0x00050400,
		0x055, 0x0004026E,
		0x0DD, 0x0000004C,
		0x070, 0x00067435,
	0x80002000, 0x00000000, 0x40000000, 0x00000000,
		0x071, 0x0006B10E,
	0x90003000, 0x00000000, 0x40000000, 0x00000000,
		0x071, 0x0006B10E,
	0x90004000, 0x00000000, 0x40000000, 0x00000000,
		0x071, 0x0006B10E,
	0xA0000000, 0x00000000,
		0x071, 0x0006B04E,
	0xB0000000, 0x00000000,
		0x072, 0x000007D2,
		0x073, 0x00000000,
		0x074, 0x00050400,
		0x075, 0x0004026E,
		0x0EF, 0x00000100,
		0x034, 0x0000ADD7,
		0x035, 0x00005C00,
		0x034, 0x00009DD4,
		0x035, 0x00005000,
		0x034, 0x00008DD1,
		0x035, 0x00004400,
		0x034, 0x00007DCE,
		0x035, 0x00003800,
		0x034, 0x00006CD1,
		0x035, 0x00004400,
		0x034, 0x00005CCE,
		0x035, 0x00003800,
		0x034, 0x000048CE,
		0x035, 0x00004400,
		0x034, 0x000034CE,
		0x035, 0x00003800,
		0x034, 0x00002451,
		0x035, 0x00004400,
		0x034, 0x0000144E,
		0x035, 0x00003800,
		0x034, 0x00000051,
		0x035, 0x00004400,
		0x0EF, 0x00000000,
		0x0EF, 0x00000100,
		0x0ED, 0x00000010,
		0x044, 0x0000ADD7,
		0x044, 0x00009DD4,
		0x044, 0x00008DD1,
		0x044, 0x00007DCE,
		0x044, 0x00006CC1,
		0x044, 0x00005CCE,
		0x044, 0x000044D1,
		0x044, 0x000034CE,
		0x044, 0x00002451,
		0x044, 0x0000144E,
		0x044, 0x00000051,
		0x0EF, 0x00000000,
		0x0ED, 0x00000000,
		0x07F, 0x00020080,
		0x0EF, 0x00002000,
		0x03B, 0x000380EF,
		0x03B, 0x000302FE,
		0x03B, 0x00028CE6,
		0x03B, 0x000200BC,
		0x03B, 0x000188A5,
		0x03B, 0x00010FBC,
		0x03B, 0x00008F71,
		0x03B, 0x00000900,
		0x0EF, 0x00000000,
		0x0ED, 0x00000001,
		0x040, 0x000380EF,
		0x040, 0x000302FE,
		0x040, 0x00028CE6,
		0x040, 0x000200BC,
		0x040, 0x000188A5,
		0x040, 0x00010FBC,
		0x040, 0x00008F71,
		0x040, 0x00000900,
		0x0ED, 0x00000000,
		0x082, 0x00080000,
		0x083, 0x00008000,
		0x084, 0x00048D80,
		0x085, 0x00068000,
		0x0A2, 0x00080000,
		0x0A3, 0x00008000,
		0x0A4, 0x00048D80,
		0x0A5, 0x00068000,
		0x0ED, 0x00000002,
		0x0EF, 0x00000002,
		0x056, 0x00000032,
		0x076, 0x00000032,
		0x001, 0x00000780,

};

void ODM_WeadAndConfig_MP_8723B_WadioA(stwuct dm_odm_t *pDM_Odm)
{
	u32 i = 0;
	u32 AwwayWen = AWWAY_SIZE(Awway_MP_8723B_WadioA);
	u32 *Awway = Awway_MP_8723B_WadioA;

	fow (i = 0; i < AwwayWen; i += 2) {
		u32 v1 = Awway[i];
		u32 v2 = Awway[i+1];

		/*  This (offset, data) paiw doesn't cawe the condition. */
		if (v1 < 0x40000000) {
			odm_ConfigWF_WadioA_8723B(pDM_Odm, v1, v2);
			continue;
		} ewse {
			/*  This wine is the beginning of bwanch. */
			boow bMatched = twue;
			u8  cCond  = (u8)((v1 & (BIT29|BIT28)) >> 28);

			if (cCond == COND_EWSE) { /*  EWSE, ENDIF */
				bMatched = twue;
				WEAD_NEXT_PAIW(v1, v2, i);
			} ewse if (!CheckPositive(pDM_Odm, v1, v2)) {
				bMatched = fawse;
				WEAD_NEXT_PAIW(v1, v2, i);
				WEAD_NEXT_PAIW(v1, v2, i);
			} ewse {
				WEAD_NEXT_PAIW(v1, v2, i);
				if (!CheckNegative(pDM_Odm, v1, v2))
					bMatched = fawse;
				ewse
					bMatched = twue;
				WEAD_NEXT_PAIW(v1, v2, i);
			}

			if (!bMatched) {
				/*  Condition isn't matched.
				*   Discawd the fowwowing (offset, data) paiws.
				*/
				whiwe (v1 < 0x40000000 && i < AwwayWen-2)
					WEAD_NEXT_PAIW(v1, v2, i);

				i -= 2; /*  pwevent fwom fow-woop += 2 */
			} ewse {
				/*  Configuwe matched paiws and skip to end of if-ewse. */
				whiwe (v1 < 0x40000000 && i < AwwayWen-2) {
					odm_ConfigWF_WadioA_8723B(pDM_Odm, v1, v2);
					WEAD_NEXT_PAIW(v1, v2, i);
				}

				/*  Keeps weading untiw ENDIF. */
				cCond = (u8)((v1 & (BIT29|BIT28)) >> 28);
				whiwe (cCond != COND_ENDIF && i < AwwayWen-2) {
					WEAD_NEXT_PAIW(v1, v2, i);
					cCond = (u8)((v1 & (BIT29|BIT28)) >> 28);
				}
			}
		}
	}
}

/******************************************************************************
*                           TxPowewTwack_SDIO.TXT
******************************************************************************/

static u8 gDewtaSwingTabweIdx_MP_2GB_N_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,  5,  6,  6, 6,  6,
	7,  7,  7, 8,  8,  9,  9, 10, 10, 11, 12, 13, 14, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GB_P_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 3, 3, 4, 5, 5,  6,  6,  7,  7,  8,  8,
	9,  9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GA_N_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,  5,  6,  6,  6,  6,
	7,  7,  7,  8,  8,  9,  9, 10, 10, 11, 12, 13, 14, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GA_P_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 3, 3, 4, 5, 5,  6,  6,  7,  7,  8,  8,
	9,  9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GCCKB_N_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 3, 3, 4, 4, 5,  6,  6,  7,  7,  7,  8,
	8,  8,  9,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GCCKB_P_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,  5,  6,  6,  7,  7,
	8,  8,  9,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GCCKA_N_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 3, 3, 4, 4, 5,  6,  6,  7,  7,  7,  8,
	8,  8,  9,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15
};
static u8 gDewtaSwingTabweIdx_MP_2GCCKA_P_TxPowewTwack_SDIO_8723B[] = {
	0, 0, 1, 2, 2, 2, 3, 3, 3, 4,  5,  5,  6,  6,  7,  7,
	8,  8,  9,  9,  9, 10, 10, 11, 11, 12, 12, 13, 14, 15
};

void ODM_WeadAndConfig_MP_8723B_TxPowewTwack_SDIO(stwuct dm_odm_t *pDM_Odm)
{
	stwuct odm_wf_caw_t *pWFCawibwateInfo = &pDM_Odm->WFCawibwateInfo;


	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GA_P,
		gDewtaSwingTabweIdx_MP_2GA_P_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GA_N,
		gDewtaSwingTabweIdx_MP_2GA_N_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GB_P,
		gDewtaSwingTabweIdx_MP_2GB_P_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GB_N,
		gDewtaSwingTabweIdx_MP_2GB_N_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);

	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GCCKA_P,
		gDewtaSwingTabweIdx_MP_2GCCKA_P_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GCCKA_N,
		gDewtaSwingTabweIdx_MP_2GCCKA_N_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GCCKB_P,
		gDewtaSwingTabweIdx_MP_2GCCKB_P_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
	memcpy(
		pWFCawibwateInfo->DewtaSwingTabweIdx_2GCCKB_N,
		gDewtaSwingTabweIdx_MP_2GCCKB_N_TxPowewTwack_SDIO_8723B,
		DEWTA_SWINGIDX_SIZE
	);
}

/******************************************************************************
*                           TXPWW_WMT.TXT
******************************************************************************/

static u8 *Awway_MP_8723B_TXPWW_WMT[] = {
	"FCC", "20M", "CCK", "1T", "01", "32",
	"ETSI", "20M", "CCK", "1T", "01", "32",
	"MKK", "20M", "CCK", "1T", "01", "32",
	"FCC", "20M", "CCK", "1T", "02", "32",
	"ETSI", "20M", "CCK", "1T", "02", "32",
	"MKK", "20M", "CCK", "1T", "02", "32",
	"FCC", "20M", "CCK", "1T", "03", "32",
	"ETSI", "20M", "CCK", "1T", "03", "32",
	"MKK", "20M", "CCK", "1T", "03", "32",
	"FCC", "20M", "CCK", "1T", "04", "32",
	"ETSI", "20M", "CCK", "1T", "04", "32",
	"MKK", "20M", "CCK", "1T", "04", "32",
	"FCC", "20M", "CCK", "1T", "05", "32",
	"ETSI", "20M", "CCK", "1T", "05", "32",
	"MKK", "20M", "CCK", "1T", "05", "32",
	"FCC", "20M", "CCK", "1T", "06", "32",
	"ETSI", "20M", "CCK", "1T", "06", "32",
	"MKK", "20M", "CCK", "1T", "06", "32",
	"FCC", "20M", "CCK", "1T", "07", "32",
	"ETSI", "20M", "CCK", "1T", "07", "32",
	"MKK", "20M", "CCK", "1T", "07", "32",
	"FCC", "20M", "CCK", "1T", "08", "32",
	"ETSI", "20M", "CCK", "1T", "08", "32",
	"MKK", "20M", "CCK", "1T", "08", "32",
	"FCC", "20M", "CCK", "1T", "09", "32",
	"ETSI", "20M", "CCK", "1T", "09", "32",
	"MKK", "20M", "CCK", "1T", "09", "32",
	"FCC", "20M", "CCK", "1T", "10", "32",
	"ETSI", "20M", "CCK", "1T", "10", "32",
	"MKK", "20M", "CCK", "1T", "10", "32",
	"FCC", "20M", "CCK", "1T", "11", "32",
	"ETSI", "20M", "CCK", "1T", "11", "32",
	"MKK", "20M", "CCK", "1T", "11", "32",
	"FCC", "20M", "CCK", "1T", "12", "63",
	"ETSI", "20M", "CCK", "1T", "12", "32",
	"MKK", "20M", "CCK", "1T", "12", "32",
	"FCC", "20M", "CCK", "1T", "13", "63",
	"ETSI", "20M", "CCK", "1T", "13", "32",
	"MKK", "20M", "CCK", "1T", "13", "32",
	"FCC", "20M", "CCK", "1T", "14", "63",
	"ETSI", "20M", "CCK", "1T", "14", "63",
	"MKK", "20M", "CCK", "1T", "14", "32",
	"FCC", "20M", "OFDM", "1T", "01", "28",
	"ETSI", "20M", "OFDM", "1T", "01", "32",
	"MKK", "20M", "OFDM", "1T", "01", "32",
	"FCC", "20M", "OFDM", "1T", "02", "28",
	"ETSI", "20M", "OFDM", "1T", "02", "32",
	"MKK", "20M", "OFDM", "1T", "02", "32",
	"FCC", "20M", "OFDM", "1T", "03", "32",
	"ETSI", "20M", "OFDM", "1T", "03", "32",
	"MKK", "20M", "OFDM", "1T", "03", "32",
	"FCC", "20M", "OFDM", "1T", "04", "32",
	"ETSI", "20M", "OFDM", "1T", "04", "32",
	"MKK", "20M", "OFDM", "1T", "04", "32",
	"FCC", "20M", "OFDM", "1T", "05", "32",
	"ETSI", "20M", "OFDM", "1T", "05", "32",
	"MKK", "20M", "OFDM", "1T", "05", "32",
	"FCC", "20M", "OFDM", "1T", "06", "32",
	"ETSI", "20M", "OFDM", "1T", "06", "32",
	"MKK", "20M", "OFDM", "1T", "06", "32",
	"FCC", "20M", "OFDM", "1T", "07", "32",
	"ETSI", "20M", "OFDM", "1T", "07", "32",
	"MKK", "20M", "OFDM", "1T", "07", "32",
	"FCC", "20M", "OFDM", "1T", "08", "32",
	"ETSI", "20M", "OFDM", "1T", "08", "32",
	"MKK", "20M", "OFDM", "1T", "08", "32",
	"FCC", "20M", "OFDM", "1T", "09", "32",
	"ETSI", "20M", "OFDM", "1T", "09", "32",
	"MKK", "20M", "OFDM", "1T", "09", "32",
	"FCC", "20M", "OFDM", "1T", "10", "28",
	"ETSI", "20M", "OFDM", "1T", "10", "32",
	"MKK", "20M", "OFDM", "1T", "10", "32",
	"FCC", "20M", "OFDM", "1T", "11", "28",
	"ETSI", "20M", "OFDM", "1T", "11", "32",
	"MKK", "20M", "OFDM", "1T", "11", "32",
	"FCC", "20M", "OFDM", "1T", "12", "63",
	"ETSI", "20M", "OFDM", "1T", "12", "32",
	"MKK", "20M", "OFDM", "1T", "12", "32",
	"FCC", "20M", "OFDM", "1T", "13", "63",
	"ETSI", "20M", "OFDM", "1T", "13", "32",
	"MKK", "20M", "OFDM", "1T", "13", "32",
	"FCC", "20M", "OFDM", "1T", "14", "63",
	"ETSI", "20M", "OFDM", "1T", "14", "63",
	"MKK", "20M", "OFDM", "1T", "14", "63",
	"FCC", "20M", "HT", "1T", "01", "26",
	"ETSI", "20M", "HT", "1T", "01", "32",
	"MKK", "20M", "HT", "1T", "01", "32",
	"FCC", "20M", "HT", "1T", "02", "26",
	"ETSI", "20M", "HT", "1T", "02", "32",
	"MKK", "20M", "HT", "1T", "02", "32",
	"FCC", "20M", "HT", "1T", "03", "32",
	"ETSI", "20M", "HT", "1T", "03", "32",
	"MKK", "20M", "HT", "1T", "03", "32",
	"FCC", "20M", "HT", "1T", "04", "32",
	"ETSI", "20M", "HT", "1T", "04", "32",
	"MKK", "20M", "HT", "1T", "04", "32",
	"FCC", "20M", "HT", "1T", "05", "32",
	"ETSI", "20M", "HT", "1T", "05", "32",
	"MKK", "20M", "HT", "1T", "05", "32",
	"FCC", "20M", "HT", "1T", "06", "32",
	"ETSI", "20M", "HT", "1T", "06", "32",
	"MKK", "20M", "HT", "1T", "06", "32",
	"FCC", "20M", "HT", "1T", "07", "32",
	"ETSI", "20M", "HT", "1T", "07", "32",
	"MKK", "20M", "HT", "1T", "07", "32",
	"FCC", "20M", "HT", "1T", "08", "32",
	"ETSI", "20M", "HT", "1T", "08", "32",
	"MKK", "20M", "HT", "1T", "08", "32",
	"FCC", "20M", "HT", "1T", "09", "32",
	"ETSI", "20M", "HT", "1T", "09", "32",
	"MKK", "20M", "HT", "1T", "09", "32",
	"FCC", "20M", "HT", "1T", "10", "26",
	"ETSI", "20M", "HT", "1T", "10", "32",
	"MKK", "20M", "HT", "1T", "10", "32",
	"FCC", "20M", "HT", "1T", "11", "26",
	"ETSI", "20M", "HT", "1T", "11", "32",
	"MKK", "20M", "HT", "1T", "11", "32",
	"FCC", "20M", "HT", "1T", "12", "63",
	"ETSI", "20M", "HT", "1T", "12", "32",
	"MKK", "20M", "HT", "1T", "12", "32",
	"FCC", "20M", "HT", "1T", "13", "63",
	"ETSI", "20M", "HT", "1T", "13", "32",
	"MKK", "20M", "HT", "1T", "13", "32",
	"FCC", "20M", "HT", "1T", "14", "63",
	"ETSI", "20M", "HT", "1T", "14", "63",
	"MKK", "20M", "HT", "1T", "14", "63",
	"FCC", "40M", "HT", "1T", "01", "63",
	"ETSI", "40M", "HT", "1T", "01", "63",
	"MKK", "40M", "HT", "1T", "01", "63",
	"FCC", "40M", "HT", "1T", "02", "63",
	"ETSI", "40M", "HT", "1T", "02", "63",
	"MKK", "40M", "HT", "1T", "02", "63",
	"FCC", "40M", "HT", "1T", "03", "26",
	"ETSI", "40M", "HT", "1T", "03", "32",
	"MKK", "40M", "HT", "1T", "03", "32",
	"FCC", "40M", "HT", "1T", "04", "26",
	"ETSI", "40M", "HT", "1T", "04", "32",
	"MKK", "40M", "HT", "1T", "04", "32",
	"FCC", "40M", "HT", "1T", "05", "32",
	"ETSI", "40M", "HT", "1T", "05", "32",
	"MKK", "40M", "HT", "1T", "05", "32",
	"FCC", "40M", "HT", "1T", "06", "32",
	"ETSI", "40M", "HT", "1T", "06", "32",
	"MKK", "40M", "HT", "1T", "06", "32",
	"FCC", "40M", "HT", "1T", "07", "32",
	"ETSI", "40M", "HT", "1T", "07", "32",
	"MKK", "40M", "HT", "1T", "07", "32",
	"FCC", "40M", "HT", "1T", "08", "26",
	"ETSI", "40M", "HT", "1T", "08", "32",
	"MKK", "40M", "HT", "1T", "08", "32",
	"FCC", "40M", "HT", "1T", "09", "26",
	"ETSI", "40M", "HT", "1T", "09", "32",
	"MKK", "40M", "HT", "1T", "09", "32",
	"FCC", "40M", "HT", "1T", "10", "26",
	"ETSI", "40M", "HT", "1T", "10", "32",
	"MKK", "40M", "HT", "1T", "10", "32",
	"FCC", "40M", "HT", "1T", "11", "26",
	"ETSI", "40M", "HT", "1T", "11", "32",
	"MKK", "40M", "HT", "1T", "11", "32",
	"FCC", "40M", "HT", "1T", "12", "63",
	"ETSI", "40M", "HT", "1T", "12", "32",
	"MKK", "40M", "HT", "1T", "12", "32",
	"FCC", "40M", "HT", "1T", "13", "63",
	"ETSI", "40M", "HT", "1T", "13", "32",
	"MKK", "40M", "HT", "1T", "13", "32",
	"FCC", "40M", "HT", "1T", "14", "63",
	"ETSI", "40M", "HT", "1T", "14", "63",
	"MKK", "40M", "HT", "1T", "14", "63"
};

void ODM_WeadAndConfig_MP_8723B_TXPWW_WMT(stwuct dm_odm_t *pDM_Odm)
{
	u32 i = 0;
	u8 **Awway = Awway_MP_8723B_TXPWW_WMT;

	fow (i = 0; i < AWWAY_SIZE(Awway_MP_8723B_TXPWW_WMT); i += 6) {
		u8 *weguwation = Awway[i];
		u8 *bandwidth = Awway[i+1];
		u8 *wate = Awway[i+2];
		u8 *wfPath = Awway[i+3];
		u8 *chnw = Awway[i+4];
		u8 *vaw = Awway[i+5];

		odm_ConfigBB_TXPWW_WMT_8723B(
			pDM_Odm,
			weguwation,
			bandwidth,
			wate,
			wfPath,
			chnw,
			vaw
		);
	}
}
