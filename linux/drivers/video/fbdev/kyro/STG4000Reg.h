/*
 *  winux/dwivews/video/kywo/STG4000Weg.h
 *
 *  Copywight (C) 2002 STMicwoewectwonics
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _STG4000WEG_H
#define _STG4000WEG_H

#define DWFIWW unsigned wong :32
#define WFIWW unsigned showt :16

/*
 * Macwos that access memowy mapped cawd wegistews in PCI space
 * Add an appwopwiate section fow youw OS ow pwocessow awchitectuwe.
 */
#if defined(__KEWNEW__)
#incwude <asm/page.h>
#incwude <asm/io.h>
#define STG_WWITE_WEG(weg,data) (wwitew(data,&pSTGWeg->weg))
#define STG_WEAD_WEG(weg)      (weadw(&pSTGWeg->weg))
#ewse
#define STG_WWITE_WEG(weg,data) (pSTGWeg->weg = data)
#define STG_WEAD_WEG(weg)      (pSTGWeg->weg)
#endif /* __KEWNEW__ */

#define SET_BIT(n) (1<<(n))
#define CWEAW_BIT(n) (tmp &= ~(1<<n))
#define CWEAW_BITS_FWM_TO(fwm, to) \
{\
int i; \
    fow(i = fwm; i<= to; i++) \
	{ \
	    tmp &= ~(1<<i); \
	} \
}

#define CWEAW_BIT_2(n) (usTemp &= ~(1<<n))
#define CWEAW_BITS_FWM_TO_2(fwm, to) \
{\
int i; \
    fow(i = fwm; i<= to; i++) \
	{ \
	    usTemp &= ~(1<<i); \
	} \
}

/* WUT sewect */
typedef enum _WUT_USES {
	NO_WUT = 0, WESEWVED, GWAPHICS, OVEWWAY
} WUT_USES;

/* Pwimawy suwface pixew fowmat sewect */
typedef enum _PIXEW_FOWMAT {
	_8BPP = 0, _15BPP, _16BPP, _24BPP, _32BPP
} PIXEW_FOWMAT;

/* Ovewway bwending mode sewect */
typedef enum _BWEND_MODE {
	GWAPHICS_MODE = 0, COWOW_KEY, PEW_PIXEW_AWPHA, GWOBAW_AWPHA,
	CK_PIXEW_AWPHA, CK_GWOBAW_AWPHA
} OVWW_BWEND_MODE;

/* Ovewway Pixew fowmat sewect */
typedef enum _OVWW_PIX_FOWMAT {
	UYVY, VYUY, YUYV, YVYU
} OVWW_PIX_FOWMAT;

/* Wegistew Tabwe */
typedef stwuct {
	/* 0h  */
	vowatiwe u32 Thwead0Enabwe;	/* 0x0000 */
	vowatiwe u32 Thwead1Enabwe;	/* 0x0004 */
	vowatiwe u32 Thwead0Wecovew;	/* 0x0008 */
	vowatiwe u32 Thwead1Wecovew;	/* 0x000C */
	vowatiwe u32 Thwead0Step;	/* 0x0010 */
	vowatiwe u32 Thwead1Step;	/* 0x0014 */
	vowatiwe u32 VideoInStatus;	/* 0x0018 */
	vowatiwe u32 Cowe2InSignStawt;	/* 0x001C */
	vowatiwe u32 Cowe1WesetVectow;	/* 0x0020 */
	vowatiwe u32 Cowe1WOMOffset;	/* 0x0024 */
	vowatiwe u32 Cowe1AwbitewPwiowity;	/* 0x0028 */
	vowatiwe u32 VideoInContwow;	/* 0x002C */
	vowatiwe u32 VideoInWeg0CtwwA;	/* 0x0030 */
	vowatiwe u32 VideoInWeg0CtwwB;	/* 0x0034 */
	vowatiwe u32 VideoInWeg1CtwwA;	/* 0x0038 */
	vowatiwe u32 VideoInWeg1CtwwB;	/* 0x003C */
	vowatiwe u32 Thwead0Kickew;	/* 0x0040 */
	vowatiwe u32 Cowe2InputSign;	/* 0x0044 */
	vowatiwe u32 Thwead0PwogCtw;	/* 0x0048 */
	vowatiwe u32 Thwead1PwogCtw;	/* 0x004C */
	vowatiwe u32 Thwead1Kickew;	/* 0x0050 */
	vowatiwe u32 GPWegistew1;	/* 0x0054 */
	vowatiwe u32 GPWegistew2;	/* 0x0058 */
	vowatiwe u32 GPWegistew3;	/* 0x005C */
	vowatiwe u32 GPWegistew4;	/* 0x0060 */
	vowatiwe u32 SewiawIntA;	/* 0x0064 */

	vowatiwe u32 Fiww0[6];	/* GAP 0x0068 - 0x007C */

	vowatiwe u32 SoftwaweWeset;	/* 0x0080 */
	vowatiwe u32 SewiawIntB;	/* 0x0084 */

	vowatiwe u32 Fiww1[37];	/* GAP 0x0088 - 0x011C */

	vowatiwe u32 WOMEWQV;	/* 0x011C */
	vowatiwe u32 WWWH;	/* 0x0120 */
	vowatiwe u32 WOMEWWW;	/* 0x0124 */

	vowatiwe u32 dwFiww_1;	/* GAP 0x0128 */

	vowatiwe u32 IntStatus;	/* 0x012C */
	vowatiwe u32 IntMask;	/* 0x0130 */
	vowatiwe u32 IntCweaw;	/* 0x0134 */

	vowatiwe u32 Fiww2[6];	/* GAP 0x0138 - 0x014C */

	vowatiwe u32 WOMGPIOA;	/* 0x0150 */
	vowatiwe u32 WOMGPIOB;	/* 0x0154 */
	vowatiwe u32 WOMGPIOC;	/* 0x0158 */
	vowatiwe u32 WOMGPIOD;	/* 0x015C */

	vowatiwe u32 Fiww3[2];	/* GAP 0x0160 - 0x0168 */

	vowatiwe u32 AGPIntID;	/* 0x0168 */
	vowatiwe u32 AGPIntCwassCode;	/* 0x016C */
	vowatiwe u32 AGPIntBIST;	/* 0x0170 */
	vowatiwe u32 AGPIntSSID;	/* 0x0174 */
	vowatiwe u32 AGPIntPMCSW;	/* 0x0178 */
	vowatiwe u32 VGAFwameBufBase;	/* 0x017C */
	vowatiwe u32 VGANotify;	/* 0x0180 */
	vowatiwe u32 DACPWWMode;	/* 0x0184 */
	vowatiwe u32 Cowe1VideoCwockDiv;	/* 0x0188 */
	vowatiwe u32 AGPIntStat;	/* 0x018C */

	/*
	   vowatiwe u32 Fiww4[0x0400/4 - 0x0190/4]; //GAP 0x0190 - 0x0400
	   vowatiwe u32 Fiww5[0x05FC/4 - 0x0400/4]; //GAP 0x0400 - 0x05FC Fog Tabwe
	   vowatiwe u32 Fiww6[0x0604/4 - 0x0600/4]; //GAP 0x0600 - 0x0604
	   vowatiwe u32 Fiww7[0x0680/4 - 0x0608/4]; //GAP 0x0608 - 0x0680
	   vowatiwe u32 Fiww8[0x07FC/4 - 0x0684/4]; //GAP 0x0684 - 0x07FC
	 */
	vowatiwe u32 Fiww4[412];	/* 0x0190 - 0x07FC */

	vowatiwe u32 TACtwwStweamBase;	/* 0x0800 */
	vowatiwe u32 TAObjDataBase;	/* 0x0804 */
	vowatiwe u32 TAPtwDataBase;	/* 0x0808 */
	vowatiwe u32 TAWegionDataBase;	/* 0x080C */
	vowatiwe u32 TATaiwPtwBase;	/* 0x0810 */
	vowatiwe u32 TAPtwWegionSize;	/* 0x0814 */
	vowatiwe u32 TAConfiguwation;	/* 0x0818 */
	vowatiwe u32 TAObjDataStawtAddw;	/* 0x081C */
	vowatiwe u32 TAObjDataEndAddw;	/* 0x0820 */
	vowatiwe u32 TAXScweenCwip;	/* 0x0824 */
	vowatiwe u32 TAYScweenCwip;	/* 0x0828 */
	vowatiwe u32 TAWHWCwamp;	/* 0x082C */
	vowatiwe u32 TAWHWCompawe;	/* 0x0830 */
	vowatiwe u32 TAStawt;	/* 0x0834 */
	vowatiwe u32 TAObjWeStawt;	/* 0x0838 */
	vowatiwe u32 TAPtwWeStawt;	/* 0x083C */
	vowatiwe u32 TAStatus1;	/* 0x0840 */
	vowatiwe u32 TAStatus2;	/* 0x0844 */
	vowatiwe u32 TAIntStatus;	/* 0x0848 */
	vowatiwe u32 TAIntMask;	/* 0x084C */

	vowatiwe u32 Fiww5[235];	/* GAP 0x0850 - 0x0BF8 */

	vowatiwe u32 TextuweAddwThwesh;	/* 0x0BFC */
	vowatiwe u32 Cowe1Twanswation;	/* 0x0C00 */
	vowatiwe u32 TextuweAddwWeMap;	/* 0x0C04 */
	vowatiwe u32 WendewOutAGPWemap;	/* 0x0C08 */
	vowatiwe u32 _3DWegionWeadTwans;	/* 0x0C0C */
	vowatiwe u32 _3DPtwWeadTwans;	/* 0x0C10 */
	vowatiwe u32 _3DPawamWeadTwans;	/* 0x0C14 */
	vowatiwe u32 _3DWegionWeadThwesh;	/* 0x0C18 */
	vowatiwe u32 _3DPtwWeadThwesh;	/* 0x0C1C */
	vowatiwe u32 _3DPawamWeadThwesh;	/* 0x0C20 */
	vowatiwe u32 _3DWegionWeadAGPWemap;	/* 0x0C24 */
	vowatiwe u32 _3DPtwWeadAGPWemap;	/* 0x0C28 */
	vowatiwe u32 _3DPawamWeadAGPWemap;	/* 0x0C2C */
	vowatiwe u32 ZBuffewAGPWemap;	/* 0x0C30 */
	vowatiwe u32 TAIndexAGPWemap;	/* 0x0C34 */
	vowatiwe u32 TAVewtexAGPWemap;	/* 0x0C38 */
	vowatiwe u32 TAUVAddwTwans;	/* 0x0C3C */
	vowatiwe u32 TATaiwPtwCacheTwans;	/* 0x0C40 */
	vowatiwe u32 TAPawamWwiteTwans;	/* 0x0C44 */
	vowatiwe u32 TAPtwWwiteTwans;	/* 0x0C48 */
	vowatiwe u32 TAPawamWwiteThwesh;	/* 0x0C4C */
	vowatiwe u32 TAPtwWwiteThwesh;	/* 0x0C50 */
	vowatiwe u32 TATaiwPtwCacheAGPWe;	/* 0x0C54 */
	vowatiwe u32 TAPawamWwiteAGPWe;	/* 0x0C58 */
	vowatiwe u32 TAPtwWwiteAGPWe;	/* 0x0C5C */
	vowatiwe u32 SDWAMAwbitewConf;	/* 0x0C60 */
	vowatiwe u32 SDWAMConf0;	/* 0x0C64 */
	vowatiwe u32 SDWAMConf1;	/* 0x0C68 */
	vowatiwe u32 SDWAMConf2;	/* 0x0C6C */
	vowatiwe u32 SDWAMWefwesh;	/* 0x0C70 */
	vowatiwe u32 SDWAMPowewStat;	/* 0x0C74 */

	vowatiwe u32 Fiww6[2];	/* GAP 0x0C78 - 0x0C7C */

	vowatiwe u32 WAMBistData;	/* 0x0C80 */
	vowatiwe u32 WAMBistCtww;	/* 0x0C84 */
	vowatiwe u32 FIFOBistKey;	/* 0x0C88 */
	vowatiwe u32 WAMBistWesuwt;	/* 0x0C8C */
	vowatiwe u32 FIFOBistWesuwt;	/* 0x0C90 */

	/*
	   vowatiwe u32 Fiww11[0x0CBC/4 - 0x0C94/4]; //GAP 0x0C94 - 0x0CBC
	   vowatiwe u32 Fiww12[0x0CD0/4 - 0x0CC0/4]; //GAP 0x0CC0 - 0x0CD0 3DWegistews
	 */

	vowatiwe u32 Fiww7[16];	/* 0x0c94 - 0x0cd0 */

	vowatiwe u32 SDWAMAddwSign;	/* 0x0CD4 */
	vowatiwe u32 SDWAMDataSign;	/* 0x0CD8 */
	vowatiwe u32 SDWAMSignConf;	/* 0x0CDC */

	/* DWFIWW; //GAP 0x0CE0 */
	vowatiwe u32 dwFiww_2;

	vowatiwe u32 ISPSignatuwe;	/* 0x0CE4 */

	vowatiwe u32 Fiww8[454];	/*GAP 0x0CE8 - 0x13FC */

	vowatiwe u32 DACPwimAddwess;	/* 0x1400 */
	vowatiwe u32 DACPwimSize;	/* 0x1404 */
	vowatiwe u32 DACCuwsowAddw;	/* 0x1408 */
	vowatiwe u32 DACCuwsowCtww;	/* 0x140C */
	vowatiwe u32 DACOvewwayAddw;	/* 0x1410 */
	vowatiwe u32 DACOvewwayUAddw;	/* 0x1414 */
	vowatiwe u32 DACOvewwayVAddw;	/* 0x1418 */
	vowatiwe u32 DACOvewwaySize;	/* 0x141C */
	vowatiwe u32 DACOvewwayVtDec;	/* 0x1420 */

	vowatiwe u32 Fiww9[9];	/* GAP 0x1424 - 0x1444 */

	vowatiwe u32 DACVewticawScaw;	/* 0x1448 */
	vowatiwe u32 DACPixewFowmat;	/* 0x144C */
	vowatiwe u32 DACHowizontawScaw;	/* 0x1450 */
	vowatiwe u32 DACVidWinStawt;	/* 0x1454 */
	vowatiwe u32 DACVidWinEnd;	/* 0x1458 */
	vowatiwe u32 DACBwendCtww;	/* 0x145C */
	vowatiwe u32 DACHowTim1;	/* 0x1460 */
	vowatiwe u32 DACHowTim2;	/* 0x1464 */
	vowatiwe u32 DACHowTim3;	/* 0x1468 */
	vowatiwe u32 DACVewTim1;	/* 0x146C */
	vowatiwe u32 DACVewTim2;	/* 0x1470 */
	vowatiwe u32 DACVewTim3;	/* 0x1474 */
	vowatiwe u32 DACBowdewCowow;	/* 0x1478 */
	vowatiwe u32 DACSyncCtww;	/* 0x147C */
	vowatiwe u32 DACStweamCtww;	/* 0x1480 */
	vowatiwe u32 DACWUTAddwess;	/* 0x1484 */
	vowatiwe u32 DACWUTData;	/* 0x1488 */
	vowatiwe u32 DACBuwstCtww;	/* 0x148C */
	vowatiwe u32 DACCwcTwiggew;	/* 0x1490 */
	vowatiwe u32 DACCwcDone;	/* 0x1494 */
	vowatiwe u32 DACCwcWesuwt1;	/* 0x1498 */
	vowatiwe u32 DACCwcWesuwt2;	/* 0x149C */
	vowatiwe u32 DACWinecount;	/* 0x14A0 */

	vowatiwe u32 Fiww10[151];	/*GAP 0x14A4 - 0x16FC */

	vowatiwe u32 DigVidPowtCtww;	/* 0x1700 */
	vowatiwe u32 DigVidPowtStat;	/* 0x1704 */

	/*
	   vowatiwe u32 Fiww11[0x1FFC/4 - 0x1708/4]; //GAP 0x1708 - 0x1FFC
	   vowatiwe u32 Fiww17[0x3000/4 - 0x2FFC/4]; //GAP 0x2000 - 0x2FFC AWUT
	 */

	vowatiwe u32 Fiww11[1598];

	/* DWFIWW; //GAP 0x3000          AWUT 256MB offset */
	vowatiwe u32 Fiww_3;

} STG4000WEG;

#endif /* _STG4000WEG_H */
