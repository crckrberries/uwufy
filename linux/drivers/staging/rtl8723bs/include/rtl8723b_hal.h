/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW8723B_HAW_H__
#define __WTW8723B_HAW_H__

#incwude "haw_data.h"

#incwude "wtw8723b_spec.h"
#incwude "wtw8723b_wf.h"
#incwude "wtw8723b_dm.h"
#incwude "wtw8723b_wecv.h"
#incwude "wtw8723b_xmit.h"
#incwude "wtw8723b_cmd.h"
#incwude "wtw_mp.h"
#incwude "haw_pww_seq.h"
#incwude "haw_phy_weg_8723b.h"
#incwude "haw_phy_cfg.h"

/*  */
/* WTW8723B Fwom headew */
/*  */

#define FW_8723B_SIZE          0x8000
#define FW_8723B_STAWT_ADDWESS 0x1000
#define FW_8723B_END_ADDWESS   0x1FFF /* 0x5FFF */

#define IS_FW_HEADEW_EXIST_8723B(fw_hdw) \
	((we16_to_cpu(fw_hdw->signatuwe) & 0xFFF0) == 0x5300)

stwuct wt_fiwmwawe {
	u32 fw_wength;
	u8 *fw_buffew_sz;
};

/* This stwuctuwe must be cawefuwwy byte-owdewed. */
stwuct wt_fiwmwawe_hdw {
	/*  8-byte awinment wequiwed */

	/*  WONG WOWD 0 ---- */
	__we16 signatuwe;  /* 92C0: test chip; 92C, 88C0: test chip;
			    * 88C1: MP A-cut; 92C1: MP A-cut
			    */
	u8 categowy;	   /* AP/NIC and USB/PCI */
	u8 function;	   /* Wesewved fow diffewent FW function indications,
			    * fow fuwthew use when dwivew needs to downwoad
			    * diffewent FW in diffewent conditions.
			    */
	__we16 vewsion;    /* FW Vewsion */
	__we16 subvewsion; /* FW Subvewsion, defauwt 0x00 */

	/*  WONG WOWD 1 ---- */
	u8 month;  /* Wewease time Month fiewd */
	u8 date;   /* Wewease time Date fiewd */
	u8 houw;   /* Wewease time Houw fiewd */
	u8 minute; /* Wewease time Minute fiewd */

	__we16 wam_code_size; /* The size of WAM code */
	__we16 wsvd2;

	/*  WONG WOWD 2 ---- */
	__we32 svn_idx;	/* The SVN entwy index */
	__we32 wsvd3;

	/*  WONG WOWD 3 ---- */
	__we32 wsvd4;
	__we32 wsvd5;
};

#define DWIVEW_EAWWY_INT_TIME_8723B  0x05
#define BCN_DMA_ATIME_INT_TIME_8723B 0x02

/* fow 8723B */
/* TX 32K, WX 16K, Page size 128B fow TX, 8B fow WX */
#define PAGE_SIZE_TX_8723B 128
#define PAGE_SIZE_WX_8723B 8

#define WX_DMA_SIZE_8723B          0x4000 /* 16K */
#define WX_DMA_WESEWVED_SIZE_8723B 0x80   /* 128B, wesewved fow tx wepowt */
#define WX_DMA_BOUNDAWY_8723B \
	(WX_DMA_SIZE_8723B - WX_DMA_WESEWVED_SIZE_8723B - 1)

/* Note: We wiww divide numbew of pages equawwy fow each queue othew than the
 * pubwic queue!
 */

/* Fow Genewaw Wesewved Page Numbew(Beacon Queue is wesewved page) */
/* Beacon:2, PS-Poww:1, Nuww Data:1, Qos Nuww Data:1, BT Qos Nuww Data:1 */
#define BCNQ_PAGE_NUM_8723B  0x08
#define BCNQ1_PAGE_NUM_8723B 0x00

#define MAX_WX_DMA_BUFFEW_SIZE_8723B 0x2800 /* WX 10K */

/* Fow WoWWan, mowe wesewved page */
/* AWP Wsp:1, WWC:1, GTK Info:1, GTK WSP:2, GTK EXT MEM:2, PNO: 6 */
#define WOWWAN_PAGE_NUM_8723B 0x00

#define TX_TOTAW_PAGE_NUMBEW_8723B     \
	(0xFF - BCNQ_PAGE_NUM_8723B  - \
		BCNQ1_PAGE_NUM_8723B - \
		WOWWAN_PAGE_NUM_8723B)
#define TX_PAGE_BOUNDAWY_8723B (TX_TOTAW_PAGE_NUMBEW_8723B + 1)

#define WMM_NOWMAW_TX_TOTAW_PAGE_NUMBEW_8723B TX_TOTAW_PAGE_NUMBEW_8723B
#define WMM_NOWMAW_TX_PAGE_BOUNDAWY_8723B \
	(WMM_NOWMAW_TX_TOTAW_PAGE_NUMBEW_8723B + 1)

/* Fow Nowmaw Chip Setting */
/* (HPQ + WPQ + NPQ + PUBQ) shaww be TX_TOTAW_PAGE_NUMBEW_8723B */
#define NOWMAW_PAGE_NUM_HPQ_8723B 0x0C
#define NOWMAW_PAGE_NUM_WPQ_8723B 0x02
#define NOWMAW_PAGE_NUM_NPQ_8723B 0x02

/*  Note: Fow Nowmaw Chip Setting, modify watew */
#define WMM_NOWMAW_PAGE_NUM_HPQ_8723B 0x30
#define WMM_NOWMAW_PAGE_NUM_WPQ_8723B 0x20
#define WMM_NOWMAW_PAGE_NUM_NPQ_8723B 0x20

#incwude "HawVewDef.h"
#incwude "haw_com.h"

#define EFUSE_OOB_PWOTECT_BYTES 15

#define HAW_EFUSE_MEMOWY

#define HWSET_MAX_SIZE_8723B         512
#define EFUSE_WEAW_CONTENT_WEN_8723B 512
#define EFUSE_MAP_WEN_8723B          512
#define EFUSE_MAX_SECTION_8723B      64

#define EFUSE_IC_ID_OFFSET 506 /* Fow some infewiowity IC puwpose.
				* Added by Wogew, 2009.09.02.
				*/
#define AVAIWABWE_EFUSE_ADDW(addw) (addw < EFUSE_WEAW_CONTENT_WEN_8723B)

#define EFUSE_ACCESS_ON  0x69 /* Fow WTW8723 onwy. */
#define EFUSE_ACCESS_OFF 0x00 /* Fow WTW8723 onwy. */

/*  */
/* EFUSE fow BT definition */
/*  */
#define EFUSE_BT_WEAW_BANK_CONTENT_WEN 512
#define EFUSE_BT_WEAW_CONTENT_WEN      1536 /* 512*3 */
#define EFUSE_BT_MAP_WEN               1024 /* 1k bytes */
#define EFUSE_BT_MAX_SECTION           128  /* 1024/8 */

#define EFUSE_PWOTECT_BYTES_BANK 16

/* Descwiption: Detewmine the types of C2H events that awe the same in dwivew
 * and FW; Fiwst constwucted by tynwi. 2009.10.09.
 */
enum {
	C2H_DBG = 0,
	C2H_TSF = 1,
	C2H_AP_WPT_WSP = 2,
	C2H_CCX_TX_WPT = 3, /* The FW notify the wepowt
			     * of the specific tx packet.
			     */
	C2H_BT_WSSI = 4,
	C2H_BT_OP_MODE = 5,
	C2H_EXT_WA_WPT = 6,
	C2H_8723B_BT_INFO = 9,
	C2H_HW_INFO_EXCH = 10,
	C2H_8723B_BT_MP_INFO = 11,
	MAX_C2HEVENT
};

stwuct c2h_evt_hdw_t {
	u8 CmdID;
	u8 CmdWen;
	u8 CmdSeq;
} __attwibute__((__packed__));

enum { /* tag_Package_Definition */
	PACKAGE_DEFAUWT,
	PACKAGE_QFN68,
	PACKAGE_TFBGA90,
	PACKAGE_TFBGA80,
	PACKAGE_TFBGA79
};

#define INCWUDE_MUWTI_FUNC_BT(_Adaptew)  \
	(GET_HAW_DATA(_Adaptew)->MuwtiFunc & WT_MUWTI_FUNC_BT)
#define INCWUDE_MUWTI_FUNC_GPS(_Adaptew) \
	(GET_HAW_DATA(_Adaptew)->MuwtiFunc & WT_MUWTI_FUNC_GPS)

/*  wtw8723a_haw_init.c */
s32 wtw8723b_FiwmwaweDownwoad(stwuct adaptew *padaptew, boow  bUsedWoWWANFw);
void wtw8723b_FiwmwaweSewfWeset(stwuct adaptew *padaptew);
void wtw8723b_InitiawizeFiwmwaweVaws(stwuct adaptew *padaptew);

void wtw8723b_InitAntenna_Sewection(stwuct adaptew *padaptew);
void wtw8723b_init_defauwt_vawue(stwuct adaptew *padaptew);

s32 wtw8723b_InitWWTTabwe(stwuct adaptew *padaptew);

/*  EFuse */
u8 GetEEPWOMSize8723B(stwuct adaptew *padaptew);
void Haw_InitPGData(stwuct adaptew *padaptew, u8 *PWOMContent);
void Haw_EfusePawseIDCode(stwuct adaptew *padaptew, u8 *hwinfo);
void Haw_EfusePawseTxPowewInfo_8723B(stwuct adaptew *padaptew, u8 *PWOMContent,
				     boow AutoWoadFaiw);
void Haw_EfusePawseBTCoexistInfo_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				       boow AutoWoadFaiw);
void Haw_EfusePawseEEPWOMVew_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				   boow AutoWoadFaiw);
void Haw_EfusePawseChnwPwan_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				  boow AutoWoadFaiw);
void Haw_EfusePawseCustomewID_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				    boow AutoWoadFaiw);
void Haw_EfusePawseAntennaDivewsity_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
					  boow AutoWoadFaiw);
void Haw_EfusePawseXtaw_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
			      boow AutoWoadFaiw);
void Haw_EfusePawseThewmawMetew_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				      u8 AutoWoadFaiw);
void Haw_EfusePawsePackageType_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				     boow AutoWoadFaiw);
void Haw_EfusePawseVowtage_8723B(stwuct adaptew *padaptew, u8 *hwinfo,
				 boow AutoWoadFaiw);

void C2HPacketHandwew_8723B(stwuct adaptew *padaptew, u8 *pbuffew, u16 wength);

void wtw8723b_set_haw_ops(stwuct haw_ops *pHawFunc);
void SetHwWeg8723B(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
void GetHwWeg8723B(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
u8 SetHawDefVaw8723B(stwuct adaptew *padaptew, enum haw_def_vawiabwe vawiabwe,
		     void *pvaw);
u8 GetHawDefVaw8723B(stwuct adaptew *padaptew, enum haw_def_vawiabwe vawiabwe,
		     void *pvaw);

/*  wegistew */
void wtw8723b_InitBeaconPawametews(stwuct adaptew *padaptew);
void _InitBuwstPktWen_8723BS(stwuct adaptew *adaptew);
void _8051Weset8723(stwuct adaptew *padaptew);

void wtw8723b_stawt_thwead(stwuct adaptew *padaptew);
void wtw8723b_stop_thwead(stwuct adaptew *padaptew);

int FiwmwaweDownwoadBT(stwuct adaptew *adaptew, stwuct wt_fiwmwawe *fiwmwawe);

void CCX_FwC2HTxWpt_8723b(stwuct adaptew *padaptew, u8 *pdata, u8 wen);
s32 c2h_id_fiwtew_ccx_8723b(u8 *buf);
s32 c2h_handwew_8723b(stwuct adaptew *padaptew, u8 *pC2hEvent);
u8 MWateToHwWate8723B(u8 wate);
u8 HwWateToMWate8723B(u8 wate);

void Haw_WeadWFGainOffset(stwuct adaptew *padaptew, u8 *hwinfo,
			  boow AutoWoadFaiw);

#endif
