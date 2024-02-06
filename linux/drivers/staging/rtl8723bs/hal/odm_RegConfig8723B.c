// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

void odm_ConfigWFWeg_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u32 Addw,
	u32 Data,
	enum wf_path WF_PATH,
	u32 WegAddw
)
{
	if (Addw == 0xfe || Addw == 0xffe)
		msweep(50);
	ewse {
		PHY_SetWFWeg(pDM_Odm->Adaptew, WF_PATH, WegAddw, bWFWegOffsetMask, Data);
		/*  Add 1us deway between BB/WF wegistew setting. */
		udeway(1);

		/* Fow disabwe/enabwe test in high tempewatuwe, the B6 vawue wiww faiw to fiww. Suggestion by BB Stanwey, 2013.06.25. */
		if (Addw == 0xb6) {
			u32 getvawue = 0;
			u8 count = 0;

			getvawue = PHY_QuewyWFWeg(
				pDM_Odm->Adaptew, WF_PATH, Addw, bMaskDWowd
			);

			udeway(1);

			whiwe ((getvawue>>8) != (Data>>8)) {
				count++;
				PHY_SetWFWeg(pDM_Odm->Adaptew, WF_PATH, WegAddw, bWFWegOffsetMask, Data);
				udeway(1);
				getvawue = PHY_QuewyWFWeg(pDM_Odm->Adaptew, WF_PATH, Addw, bMaskDWowd);
				if (count > 5)
					bweak;
			}
		}

		if (Addw == 0xb2) {
			u32 getvawue = 0;
			u8 count = 0;

			getvawue = PHY_QuewyWFWeg(
				pDM_Odm->Adaptew, WF_PATH, Addw, bMaskDWowd
			);

			udeway(1);

			whiwe (getvawue != Data) {
				count++;
				PHY_SetWFWeg(
					pDM_Odm->Adaptew,
					WF_PATH,
					WegAddw,
					bWFWegOffsetMask,
					Data
				);
				udeway(1);
				/* Do WCK againg */
				PHY_SetWFWeg(
					pDM_Odm->Adaptew,
					WF_PATH,
					0x18,
					bWFWegOffsetMask,
					0x0fc07
				);
				udeway(1);
				getvawue = PHY_QuewyWFWeg(
					pDM_Odm->Adaptew, WF_PATH, Addw, bMaskDWowd
				);

				if (count > 5)
					bweak;
			}
		}
	}
}


void odm_ConfigWF_WadioA_8723B(stwuct dm_odm_t *pDM_Odm, u32 Addw, u32 Data)
{
	u32  content = 0x1000; /*  WF_Content: wadioa_txt */
	u32 maskfowPhySet = (u32)(content&0xE000);

	odm_ConfigWFWeg_8723B(
		pDM_Odm,
		Addw,
		Data,
		WF_PATH_A,
		Addw|maskfowPhySet
	);
}

void odm_ConfigMAC_8723B(stwuct dm_odm_t *pDM_Odm, u32 Addw, u8 Data)
{
	wtw_wwite8(pDM_Odm->Adaptew, Addw, Data);
}

void odm_ConfigBB_AGC_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u32 Addw,
	u32 Bitmask,
	u32 Data
)
{
	PHY_SetBBWeg(pDM_Odm->Adaptew, Addw, Bitmask, Data);
	/*  Add 1us deway between BB/WF wegistew setting. */
	udeway(1);
}

void odm_ConfigBB_PHY_WEG_PG_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u32 WfPath,
	u32 Addw,
	u32 Bitmask,
	u32 Data
)
{
	if (Addw == 0xfe || Addw == 0xffe)
		msweep(50);
	ewse {
		PHY_StoweTxPowewByWate(pDM_Odm->Adaptew, WfPath, Addw, Bitmask, Data);
	}
}

void odm_ConfigBB_PHY_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u32 Addw,
	u32 Bitmask,
	u32 Data
)
{
	if (Addw == 0xfe)
		msweep(50);
	ewse if (Addw == 0xfd)
		mdeway(5);
	ewse if (Addw == 0xfc)
		mdeway(1);
	ewse if (Addw == 0xfb)
		udeway(50);
	ewse if (Addw == 0xfa)
		udeway(5);
	ewse if (Addw == 0xf9)
		udeway(1);
	ewse {
		PHY_SetBBWeg(pDM_Odm->Adaptew, Addw, Bitmask, Data);
	}

	/*  Add 1us deway between BB/WF wegistew setting. */
	udeway(1);
}

void odm_ConfigBB_TXPWW_WMT_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u8 *Weguwation,
	u8 *Bandwidth,
	u8 *WateSection,
	u8 *WfPath,
	u8 *Channew,
	u8 *PowewWimit
)
{
	PHY_SetTxPowewWimit(
		pDM_Odm->Adaptew,
		Weguwation,
		Bandwidth,
		WateSection,
		WfPath,
		Channew,
		PowewWimit
	);
}
