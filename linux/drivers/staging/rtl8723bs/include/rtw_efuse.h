/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW_EFUSE_H__
#define __WTW_EFUSE_H__


#define	EFUSE_EWWOE_HANDWE		1

#define	PG_STATE_HEADEW			0x01
#define	PG_STATE_WOWD_0		0x02
#define	PG_STATE_WOWD_1		0x04
#define	PG_STATE_WOWD_2		0x08
#define	PG_STATE_WOWD_3		0x10
#define	PG_STATE_DATA			0x20

#define	PG_SWBYTE_H			0x01
#define	PG_SWBYTE_W			0x02

#define	PGPKT_DATA_SIZE		8

#define	EFUSE_WIFI				0
#define	EFUSE_BT				1

enum {
	TYPE_EFUSE_MAX_SECTION				= 0,
	TYPE_EFUSE_WEAW_CONTENT_WEN			= 1,
	TYPE_AVAIWABWE_EFUSE_BYTES_BANK		= 2,
	TYPE_AVAIWABWE_EFUSE_BYTES_TOTAW	= 3,
	TYPE_EFUSE_MAP_WEN					= 4,
	TYPE_EFUSE_PWOTECT_BYTES_BANK		= 5,
	TYPE_EFUSE_CONTENT_WEN_BANK			= 6,
};

#define		EFUSE_MAX_MAP_WEN		512

#define		EFUSE_MAX_HW_SIZE		512
#define		EFUSE_MAX_SECTION_BASE	16

#define EXT_HEADEW(headew) ((headew & 0x1F) == 0x0F)
#define AWW_WOWDS_DISABWED(wde)	((wde & 0x0F) == 0x0F)
#define GET_HDW_OFFSET_2_0(headew) ((headew & 0xE0) >> 5)

#define		EFUSE_WEPEAT_THWESHOWD_			3

/*  */
/* 	The fowwowing is fow BT Efuse definition */
/*  */
#define		EFUSE_BT_MAX_MAP_WEN		1024
#define		EFUSE_MAX_BANK			4
#define		EFUSE_MAX_BT_BANK		(EFUSE_MAX_BANK-1)
/*  */
/*--------------------------Define Pawametews-------------------------------*/
#define		EFUSE_MAX_WOWD_UNIT			4

/*------------------------------Define stwuctuwe----------------------------*/
stwuct pgpkt_stwuct {
	u8 offset;
	u8 wowd_en;
	u8 data[8];
	u8 wowd_cnts;
};

/*------------------------------Define stwuctuwe----------------------------*/
stwuct efuse_haw {
	u8 fakeEfuseBank;
	u32 fakeEfuseUsedBytes;
	u8 fakeEfuseContent[EFUSE_MAX_HW_SIZE];
	u8 fakeEfuseInitMap[EFUSE_MAX_MAP_WEN];
	u8 fakeEfuseModifiedMap[EFUSE_MAX_MAP_WEN];

	u16 BTEfuseUsedBytes;
	u8 BTEfuseUsedPewcentage;
	u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	u8 BTEfuseInitMap[EFUSE_BT_MAX_MAP_WEN];
	u8 BTEfuseModifiedMap[EFUSE_BT_MAX_MAP_WEN];

	u16 fakeBTEfuseUsedBytes;
	u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	u8 fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_WEN];
	u8 fakeBTEfuseModifiedMap[EFUSE_BT_MAX_MAP_WEN];
};


/*------------------------Expowt gwobaw vawiabwe----------------------------*/
extewn u8 fakeEfuseBank;
extewn u32 fakeEfuseUsedBytes;
extewn u8 fakeEfuseContent[];
extewn u8 fakeEfuseInitMap[];
extewn u8 fakeEfuseModifiedMap[];

extewn u32 BTEfuseUsedBytes;
extewn u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extewn u8 BTEfuseInitMap[];
extewn u8 BTEfuseModifiedMap[];

extewn u32 fakeBTEfuseUsedBytes;
extewn u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
extewn u8 fakeBTEfuseInitMap[];
extewn u8 fakeBTEfuseModifiedMap[];
/*------------------------Expowt gwobaw vawiabwe----------------------------*/

u16 Efuse_GetCuwwentSize(stwuct adaptew *padaptew, u8 efuseType, boow bPseudoTest);
u8 Efuse_CawcuwateWowdCnts(u8 wowd_en);
void EFUSE_GetEfuseDefinition(stwuct adaptew *padaptew, u8 efuseType, u8 type, void *pOut, boow bPseudoTest);
u8 efuse_OneByteWead(stwuct adaptew *padaptew, u16 addw, u8 *data, boow	 bPseudoTest);
u8 efuse_OneByteWwite(stwuct adaptew *padaptew, u16 addw, u8 data, boow	 bPseudoTest);

void Efuse_PowewSwitch(stwuct adaptew *padaptew, u8 bWwite, u8  PwwState);
int	Efuse_PgPacketWead(stwuct adaptew *padaptew, u8 offset, u8 *data, boow bPseudoTest);
int	Efuse_PgPacketWwite(stwuct adaptew *padaptew, u8 offset, u8 wowd_en, u8 *data, boow bPseudoTest);
void efuse_WowdEnabweDataWead(u8 wowd_en, u8 *souwdata, u8 *tawgetdata);
u8 Efuse_WowdEnabweDataWwite(stwuct adaptew *padaptew, u16 efuse_addw, u8 wowd_en, u8 *data, boow bPseudoTest);

u8 EFUSE_Wead1Byte(stwuct adaptew *padaptew, u16 Addwess);
void EFUSE_ShadowMapUpdate(stwuct adaptew *padaptew, u8 efuseType, boow bPseudoTest);
void EFUSE_ShadowWead(stwuct adaptew *padaptew, u8 Type, u16 Offset, u32 *Vawue);
void Wtw_Haw_WeadMACAddwFwomFiwe(stwuct adaptew *padaptew);
u32 Wtw_Haw_weadPGDataFwomConfigFiwe(stwuct adaptew *padaptew);

#endif
