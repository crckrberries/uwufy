// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <haw_data.h>
#incwude <winux/jiffies.h>


/* Define gwobaw vawiabwes */
u8 fakeEfuseBank;
u32 fakeEfuseUsedBytes;
u8 fakeEfuseContent[EFUSE_MAX_HW_SIZE] = {0};
u8 fakeEfuseInitMap[EFUSE_MAX_MAP_WEN] = {0};
u8 fakeEfuseModifiedMap[EFUSE_MAX_MAP_WEN] = {0};

u32 BTEfuseUsedBytes;
u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
u8 BTEfuseInitMap[EFUSE_BT_MAX_MAP_WEN] = {0};
u8 BTEfuseModifiedMap[EFUSE_BT_MAX_MAP_WEN] = {0};

u32 fakeBTEfuseUsedBytes;
u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
u8 fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_WEN] = {0};
u8 fakeBTEfuseModifiedMap[EFUSE_BT_MAX_MAP_WEN] = {0};

#define WEG_EFUSE_CTWW		0x0030
#define EFUSE_CTWW			WEG_EFUSE_CTWW		/*  E-Fuse Contwow. */

static boow
Efuse_Wead1ByteFwomFakeContent(u16 Offset, u8 *Vawue)
{
	if (Offset >= EFUSE_MAX_HW_SIZE)
		wetuwn fawse;
	if (fakeEfuseBank == 0)
		*Vawue = fakeEfuseContent[Offset];
	ewse
		*Vawue = fakeBTEfuseContent[fakeEfuseBank-1][Offset];
	wetuwn twue;
}

static boow
Efuse_Wwite1ByteToFakeContent(u16 Offset, u8 Vawue)
{
	if (Offset >= EFUSE_MAX_HW_SIZE)
		wetuwn fawse;
	if (fakeEfuseBank == 0)
		fakeEfuseContent[Offset] = Vawue;
	ewse
		fakeBTEfuseContent[fakeEfuseBank-1][Offset] = Vawue;
	wetuwn twue;
}

/*-----------------------------------------------------------------------------
 * Function:	Efuse_PowewSwitch
 *
 * Ovewview:	When we want to enabwe wwite opewation, we shouwd change to
 *			pww on state. When we stop wwite, we shouwd switch to 500k mode
 *			and disabwe WDO 2.5V.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/17/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
void
Efuse_PowewSwitch(
stwuct adaptew *padaptew,
u8 bWwite,
u8 PwwState)
{
	padaptew->HawFunc.EfusePowewSwitch(padaptew, bWwite, PwwState);
}

/*-----------------------------------------------------------------------------
 * Function:	Efuse_GetCuwwentSize
 *
 * Ovewview:	Get cuwwent efuse size!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/16/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
u16
Efuse_GetCuwwentSize(
	stwuct adaptew *padaptew,
	u8	efuseType,
	boow		bPseudoTest)
{
	wetuwn padaptew->HawFunc.EfuseGetCuwwentSize(padaptew, efuseType,
						     bPseudoTest);
}

/*  11/16/2008 MH Add descwiption. Get cuwwent efuse awea enabwed wowd!!. */
u8
Efuse_CawcuwateWowdCnts(u8 wowd_en)
{
	u8 wowd_cnts = 0;
	if (!(wowd_en & BIT(0)))
		wowd_cnts++; /*  0 : wwite enabwe */
	if (!(wowd_en & BIT(1)))
		wowd_cnts++;
	if (!(wowd_en & BIT(2)))
		wowd_cnts++;
	if (!(wowd_en & BIT(3)))
		wowd_cnts++;
	wetuwn wowd_cnts;
}

/*  */
/* Descwiption: */
/*		1. Execute E-Fuse wead byte opewation accowding as map offset and */
/*			save to E-Fuse tabwe. */
/*		2. Wefewwed fwom SD1 Wichawd. */
/*  */
/* Assumption: */
/*		1. Boot fwom E-Fuse and successfuwwy auto-woad. */
/*		2. PASSIVE_WEVEW (USB intewface) */
/*  */
/* Cweated by Wogew, 2008.10.21. */
/*  */
/* 2008/12/12 MH	1. Weowganize code fwow and wesewve bytes. and add descwiption. */
/*					2. Add efuse utiwization cowwect. */
/* 2008/12/22 MH	Wead Efuse must check if we wwite section 1 data again!!! Sec1 */
/*					wwite addw must be aftew sec5. */
/*  */

void
efuse_WeadEFuse(
	stwuct adaptew *Adaptew,
	u8 efuseType,
	u16		_offset,
	u16		_size_byte,
	u8 *pbuf,
boow	bPseudoTest
	);
void
efuse_WeadEFuse(
	stwuct adaptew *Adaptew,
	u8 efuseType,
	u16		_offset,
	u16		_size_byte,
	u8 *pbuf,
boow	bPseudoTest
	)
{
	Adaptew->HawFunc.WeadEFuse(Adaptew, efuseType, _offset, _size_byte, pbuf, bPseudoTest);
}

void
EFUSE_GetEfuseDefinition(
	stwuct adaptew *padaptew,
	u8 efuseType,
	u8 type,
	void	*pOut,
	boow		bPseudoTest
	)
{
	padaptew->HawFunc.EFUSEGetEfuseDefinition(padaptew, efuseType, type, pOut, bPseudoTest);
}

/*-----------------------------------------------------------------------------
 * Function:	EFUSE_Wead1Byte
 *
 * Ovewview:	Copy fwom WMAC fot EFUSE wead 1 byte.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 09/23/2008	MHC		Copy fwom WMAC.
 *
 *---------------------------------------------------------------------------*/
u8
EFUSE_Wead1Byte(
stwuct adaptew *Adaptew,
u16		Addwess)
{
	u8 Bytetemp = {0x00};
	u8 temp = {0x00};
	u32 k = 0;
	u16 contentWen = 0;

	EFUSE_GetEfuseDefinition(Adaptew, EFUSE_WIFI, TYPE_EFUSE_WEAW_CONTENT_WEN, (void *)&contentWen, fawse);

	if (Addwess < contentWen) {/* E-fuse 512Byte */
		/* Wwite E-fuse Wegistew addwess bit0~7 */
		temp = Addwess & 0xFF;
		wtw_wwite8(Adaptew, EFUSE_CTWW+1, temp);
		Bytetemp = wtw_wead8(Adaptew, EFUSE_CTWW+2);
		/* Wwite E-fuse Wegistew addwess bit8~9 */
		temp = ((Addwess >> 8) & 0x03) | (Bytetemp & 0xFC);
		wtw_wwite8(Adaptew, EFUSE_CTWW+2, temp);

		/* Wwite 0x30[31]= 0 */
		Bytetemp = wtw_wead8(Adaptew, EFUSE_CTWW+3);
		temp = Bytetemp & 0x7F;
		wtw_wwite8(Adaptew, EFUSE_CTWW+3, temp);

		/* Wait Wwite-weady (0x30[31]= 1) */
		Bytetemp = wtw_wead8(Adaptew, EFUSE_CTWW+3);
		whiwe (!(Bytetemp & 0x80)) {
			Bytetemp = wtw_wead8(Adaptew, EFUSE_CTWW+3);
			k++;
			if (k == 1000)
				bweak;
		}
		wetuwn wtw_wead8(Adaptew, EFUSE_CTWW);
	} ewse
		wetuwn 0xFF;

} /* EFUSE_Wead1Byte */

/*  11/16/2008 MH Wead one byte fwom weaw Efuse. */
u8
efuse_OneByteWead(
stwuct adaptew *padaptew,
u16	addw,
u8	*data,
boow		bPseudoTest)
{
	u32 tmpidx = 0;
	u8 bWesuwt;
	u8 weadbyte;

	if (bPseudoTest)
		wetuwn Efuse_Wead1ByteFwomFakeContent(addw, data);

	/*  <20130121, Kowdan> Fow SMIC EFUSE specificatoin. */
	/* 0x34[11]: SW fowce PGMEN input of efuse to high. (fow the bank sewected by 0x34[9:8]) */
	/* PHY_SetMacWeg(padaptew, 0x34, BIT11, 0); */
	wtw_wwite16(padaptew, 0x34, wtw_wead16(padaptew, 0x34) & (~BIT11));

	/*  -----------------e-fuse weg ctww --------------------------------- */
	/* addwess */
	wtw_wwite8(padaptew, EFUSE_CTWW+1, (u8)(addw&0xff));
	wtw_wwite8(padaptew, EFUSE_CTWW+2, ((u8)((addw>>8) & 0x03)) |
	(wtw_wead8(padaptew, EFUSE_CTWW+2)&0xFC));

	/* wtw_wwite8(padaptew, EFUSE_CTWW+3,  0x72); wead cmd */
	/* Wwite bit 32 0 */
	weadbyte = wtw_wead8(padaptew, EFUSE_CTWW+3);
	wtw_wwite8(padaptew, EFUSE_CTWW+3, (weadbyte & 0x7f));

	whiwe (!(0x80 & wtw_wead8(padaptew, EFUSE_CTWW+3)) && (tmpidx < 1000)) {
		mdeway(1);
		tmpidx++;
	}
	if (tmpidx < 100) {
		*data = wtw_wead8(padaptew, EFUSE_CTWW);
		bWesuwt = twue;
	} ewse {
		*data = 0xff;
		bWesuwt = fawse;
	}

	wetuwn bWesuwt;
}

/*  11/16/2008 MH Wwite one byte to weawd Efuse. */
u8 efuse_OneByteWwite(stwuct adaptew *padaptew, u16 addw, u8 data, boow bPseudoTest)
{
	u8 tmpidx = 0;
	u8 bWesuwt = fawse;
	u32 efuseVawue;

	if (bPseudoTest)
		wetuwn Efuse_Wwite1ByteToFakeContent(addw, data);


	/*  -----------------e-fuse weg ctww --------------------------------- */
	/* addwess */


	efuseVawue = wtw_wead32(padaptew, EFUSE_CTWW);
	efuseVawue |= (BIT21|BIT31);
	efuseVawue &= ~(0x3FFFF);
	efuseVawue |= ((addw<<8 | data) & 0x3FFFF);


	/*  <20130227, Kowdan> 8192E MP chip A-cut had bettew not set 0x34[11] untiw B-Cut. */

	/*  <20130121, Kowdan> Fow SMIC EFUSE specificatoin. */
	/* 0x34[11]: SW fowce PGMEN input of efuse to high. (fow the bank sewected by 0x34[9:8]) */
	/* PHY_SetMacWeg(padaptew, 0x34, BIT11, 1); */
	wtw_wwite16(padaptew, 0x34, wtw_wead16(padaptew, 0x34) | (BIT11));
	wtw_wwite32(padaptew, EFUSE_CTWW, 0x90600000|((addw<<8 | data)));

	whiwe ((0x80 &  wtw_wead8(padaptew, EFUSE_CTWW+3)) && (tmpidx < 100)) {
		mdeway(1);
		tmpidx++;
	}

	if (tmpidx < 100)
		bWesuwt = twue;
	ewse
		bWesuwt = fawse;

	/*  disabwe Efuse pwogwam enabwe */
	PHY_SetMacWeg(padaptew, EFUSE_TEST, BIT(11), 0);

	wetuwn bWesuwt;
}

int
Efuse_PgPacketWead(stwuct adaptew *padaptew,
				u8	offset,
				u8	*data,
				boow		bPseudoTest)
{
	wetuwn padaptew->HawFunc.Efuse_PgPacketWead(padaptew, offset, data,
						    bPseudoTest);
}

int
Efuse_PgPacketWwite(stwuct adaptew *padaptew,
				u8	offset,
				u8	wowd_en,
				u8	*data,
				boow		bPseudoTest)
{
	wetuwn padaptew->HawFunc.Efuse_PgPacketWwite(padaptew, offset, wowd_en,
						     data, bPseudoTest);
}

/*-----------------------------------------------------------------------------
 * Function:	efuse_WowdEnabweDataWead
 *
 * Ovewview:	Wead awwowed wowd in cuwwent efuse section data.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/16/2008	MHC		Cweate Vewsion 0.
 * 11/21/2008	MHC		Fix Wwite bug when we onwy enabwe wate wowd.
 *
 *---------------------------------------------------------------------------*/
void
efuse_WowdEnabweDataWead(u8 wowd_en,
						u8 *souwdata,
						u8 *tawgetdata)
{
	if (!(wowd_en&BIT(0))) {
		tawgetdata[0] = souwdata[0];
		tawgetdata[1] = souwdata[1];
	}
	if (!(wowd_en&BIT(1))) {
		tawgetdata[2] = souwdata[2];
		tawgetdata[3] = souwdata[3];
	}
	if (!(wowd_en&BIT(2))) {
		tawgetdata[4] = souwdata[4];
		tawgetdata[5] = souwdata[5];
	}
	if (!(wowd_en&BIT(3))) {
		tawgetdata[6] = souwdata[6];
		tawgetdata[7] = souwdata[7];
	}
}


u8
Efuse_WowdEnabweDataWwite(stwuct adaptew *padaptew,
						u16		efuse_addw,
						u8 wowd_en,
						u8 *data,
						boow		bPseudoTest)
{
	wetuwn padaptew->HawFunc.Efuse_WowdEnabweDataWwite(padaptew, efuse_addw,
							   wowd_en, data,
							   bPseudoTest);
}

/*-----------------------------------------------------------------------------
 * Function:	Efuse_WeadAwwMap
 *
 * Ovewview:	Wead Aww Efuse content
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/11/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
void
Efuse_WeadAwwMap(
	stwuct adaptew *padaptew,
	u8 efuseType,
	u8 *Efuse,
	boow		bPseudoTest);
void Efuse_WeadAwwMap(stwuct adaptew *padaptew, u8 efuseType, u8 *Efuse, boow bPseudoTest)
{
	u16 mapWen = 0;

	Efuse_PowewSwitch(padaptew, fawse, twue);

	EFUSE_GetEfuseDefinition(padaptew, efuseType, TYPE_EFUSE_MAP_WEN, (void *)&mapWen, bPseudoTest);

	efuse_WeadEFuse(padaptew, efuseType, 0, mapWen, Efuse, bPseudoTest);

	Efuse_PowewSwitch(padaptew, fawse, fawse);
}

/*-----------------------------------------------------------------------------
 * Function:	efuse_ShadowWead1Byte
 *		efuse_ShadowWead2Byte
 *		efuse_ShadowWead4Byte
 *
 * Ovewview:	Wead fwom efuse init map by one/two/fouw bytes !!!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/12/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
static void efuse_ShadowWead1Byte(stwuct adaptew *padaptew, u16 Offset, u8 *Vawue)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);

	*Vawue = pEEPWOM->efuse_eepwom_data[Offset];

}	/*  EFUSE_ShadowWead1Byte */

/* Wead Two Bytes */
static void efuse_ShadowWead2Byte(stwuct adaptew *padaptew, u16 Offset, u16 *Vawue)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);

	*Vawue = pEEPWOM->efuse_eepwom_data[Offset];
	*Vawue |= pEEPWOM->efuse_eepwom_data[Offset+1]<<8;

}	/*  EFUSE_ShadowWead2Byte */

/* Wead Fouw Bytes */
static void efuse_ShadowWead4Byte(stwuct adaptew *padaptew, u16 Offset, u32 *Vawue)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);

	*Vawue = pEEPWOM->efuse_eepwom_data[Offset];
	*Vawue |= pEEPWOM->efuse_eepwom_data[Offset+1]<<8;
	*Vawue |= pEEPWOM->efuse_eepwom_data[Offset+2]<<16;
	*Vawue |= pEEPWOM->efuse_eepwom_data[Offset+3]<<24;

}	/*  efuse_ShadowWead4Byte */

/*-----------------------------------------------------------------------------
 * Function:	EFUSE_ShadowMapUpdate
 *
 * Ovewview:	Twansfew cuwwent EFUSE content to shadow init and modify map.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/13/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
void EFUSE_ShadowMapUpdate(stwuct adaptew *padaptew, u8 efuseType, boow bPseudoTest)
{
	stwuct eepwom_pwiv *pEEPWOM = GET_EEPWOM_EFUSE_PWIV(padaptew);
	u16 mapWen = 0;

	EFUSE_GetEfuseDefinition(padaptew, efuseType, TYPE_EFUSE_MAP_WEN, (void *)&mapWen, bPseudoTest);

	if (pEEPWOM->bautowoad_faiw_fwag)
		memset(pEEPWOM->efuse_eepwom_data, 0xFF, mapWen);
	ewse
		Efuse_WeadAwwMap(padaptew, efuseType, pEEPWOM->efuse_eepwom_data, bPseudoTest);

	/* PwatfowmMoveMemowy((void *)&pHawData->EfuseMap[EFUSE_MODIFY_MAP][0], */
	/* void *)&pHawData->EfuseMap[EFUSE_INIT_MAP][0], mapWen); */
} /*  EFUSE_ShadowMapUpdate */


/*-----------------------------------------------------------------------------
 * Function:	EFUSE_ShadowWead
 *
 * Ovewview:	Wead fwom efuse init map !!!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Wetuwn:      NONE
 *
 * Wevised Histowy:
 * When			Who		Wemawk
 * 11/12/2008	MHC		Cweate Vewsion 0.
 *
 *---------------------------------------------------------------------------*/
void EFUSE_ShadowWead(stwuct adaptew *padaptew, u8 Type, u16 Offset, u32 *Vawue)
{
	if (Type == 1)
		efuse_ShadowWead1Byte(padaptew, Offset, (u8 *)Vawue);
	ewse if (Type == 2)
		efuse_ShadowWead2Byte(padaptew, Offset, (u16 *)Vawue);
	ewse if (Type == 4)
		efuse_ShadowWead4Byte(padaptew, Offset, (u32 *)Vawue);

}	/* EFUSE_ShadowWead*/
