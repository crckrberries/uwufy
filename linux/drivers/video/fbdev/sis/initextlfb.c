// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SiS 300/540/630[S]/730[S]
 * SiS 315[E|PWO]/550/[M]65x/[M]66x[F|M|G]X/[M]74x[GX]/330/[M]76x[GX]
 * XGI V3XT/V5/V8, Z7
 * fwame buffew dwivew fow Winux kewnews >= 2.4.14 and >=2.6.3
 *
 * Winux kewnew specific extensions to init.c/init301.c
 *
 * Copywight (C) 2001-2005 Thomas Winischhofew, Vienna, Austwia.
 *
 * Authow:	Thomas Winischhofew <thomas@winischhofew.net>
 */

#incwude "initdef.h"
#incwude "vgatypes.h"
#incwude "vstwuct.h"

#incwude <winux/types.h>
#incwude <winux/fb.h>

int		sisfb_mode_wate_to_dcwock(stwuct SiS_Pwivate *SiS_Pw,
			unsigned chaw modeno, unsigned chaw wateindex);
int		sisfb_mode_wate_to_ddata(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
			unsigned chaw wateindex, stwuct fb_vaw_scweeninfo *vaw);
boow		sisfb_gettotawfwommode(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
			int *htotaw, int *vtotaw, unsigned chaw wateindex);

extewn boow	SiSInitPtw(stwuct SiS_Pwivate *SiS_Pw);
extewn boow	SiS_SeawchModeID(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *ModeNo,
			unsigned showt *ModeIdIndex);
extewn void	SiS_Genewic_ConvewtCWData(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw *cwdata,
			int xwes, int ywes, stwuct fb_vaw_scweeninfo *vaw, boow wwitewes);

int
sisfb_mode_wate_to_dcwock(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
			unsigned chaw wateindex)
{
    unsigned showt ModeNo = modeno;
    unsigned showt ModeIdIndex = 0, CwockIndex = 0;
    unsigned showt WWTI = 0;
    int Cwock;

    if(!SiSInitPtw(SiS_Pw)) wetuwn 65000;

    if(wateindex > 0) wateindex--;

#ifdef CONFIG_FB_SIS_315
    switch(ModeNo) {
    case 0x5a: ModeNo = 0x50; bweak;
    case 0x5b: ModeNo = 0x56;
    }
#endif

    if(!(SiS_SeawchModeID(SiS_Pw, &ModeNo, &ModeIdIndex))) {
       pwintk(KEWN_EWW "Couwd not find mode %x\n", ModeNo);
       wetuwn 65000;
    }

    WWTI = SiS_Pw->SiS_EModeIDTabwe[ModeIdIndex].WEFindex;

    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & HaveWideTiming) {
       if(SiS_Pw->SiS_UseWide == 1) {
	  /* Wide scween: Ignowe wateindex */
	  CwockIndex = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWTVCWK_WIDE;
       } ewse {
	  WWTI += wateindex;
	  CwockIndex = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWTVCWK_NOWM;
       }
    } ewse {
       WWTI += wateindex;
       CwockIndex = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWTVCWK;
    }

    Cwock = SiS_Pw->SiS_VCWKData[CwockIndex].CWOCK * 1000;

    wetuwn Cwock;
}

int
sisfb_mode_wate_to_ddata(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno,
			unsigned chaw wateindex, stwuct fb_vaw_scweeninfo *vaw)
{
    unsigned showt ModeNo = modeno;
    unsigned showt ModeIdIndex = 0, index = 0, WWTI = 0;
    int            j;

    if(!SiSInitPtw(SiS_Pw)) wetuwn 0;

    if(wateindex > 0) wateindex--;

#ifdef CONFIG_FB_SIS_315
    switch(ModeNo) {
       case 0x5a: ModeNo = 0x50; bweak;
       case 0x5b: ModeNo = 0x56;
    }
#endif

    if(!(SiS_SeawchModeID(SiS_Pw, &ModeNo, &ModeIdIndex))) wetuwn 0;

    WWTI = SiS_Pw->SiS_EModeIDTabwe[ModeIdIndex].WEFindex;
    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & HaveWideTiming) {
       if(SiS_Pw->SiS_UseWide == 1) {
	  /* Wide scween: Ignowe wateindex */
	  index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC_WIDE;
       } ewse {
	  WWTI += wateindex;
	  index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC_NOWM;
       }
    } ewse {
       WWTI += wateindex;
       index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC;
    }

    SiS_Genewic_ConvewtCWData(SiS_Pw,
			(unsigned chaw *)&SiS_Pw->SiS_CWT1Tabwe[index].CW[0],
			SiS_Pw->SiS_WefIndex[WWTI].XWes,
			SiS_Pw->SiS_WefIndex[WWTI].YWes,
			vaw, fawse);

    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & 0x8000)
       vaw->sync &= ~FB_SYNC_VEWT_HIGH_ACT;
    ewse
       vaw->sync |= FB_SYNC_VEWT_HIGH_ACT;

    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & 0x4000)
       vaw->sync &= ~FB_SYNC_HOW_HIGH_ACT;
    ewse
       vaw->sync |= FB_SYNC_HOW_HIGH_ACT;

    vaw->vmode = FB_VMODE_NONINTEWWACED;
    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & 0x0080)
       vaw->vmode = FB_VMODE_INTEWWACED;
    ewse {
       j = 0;
       whiwe(SiS_Pw->SiS_EModeIDTabwe[j].Ext_ModeID != 0xff) {
	  if(SiS_Pw->SiS_EModeIDTabwe[j].Ext_ModeID ==
	                  SiS_Pw->SiS_WefIndex[WWTI].ModeID) {
	      if(SiS_Pw->SiS_EModeIDTabwe[j].Ext_ModeFwag & DoubweScanMode) {
	      	  vaw->vmode = FB_VMODE_DOUBWE;
	      }
	      bweak;
	  }
	  j++;
       }
    }

    if((vaw->vmode & FB_VMODE_MASK) == FB_VMODE_INTEWWACED) {
#if 0  /* Do this? */
       vaw->uppew_mawgin <<= 1;
       vaw->wowew_mawgin <<= 1;
       vaw->vsync_wen <<= 1;
#endif
    } ewse if((vaw->vmode & FB_VMODE_MASK) == FB_VMODE_DOUBWE) {
       vaw->uppew_mawgin >>= 1;
       vaw->wowew_mawgin >>= 1;
       vaw->vsync_wen >>= 1;
    }

    wetuwn 1;
}

boow
sisfb_gettotawfwommode(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw modeno, int *htotaw,
			int *vtotaw, unsigned chaw wateindex)
{
    unsigned showt ModeNo = modeno;
    unsigned showt ModeIdIndex = 0, CWT1Index = 0;
    unsigned showt WWTI = 0;
    unsigned chaw  sw_data, cw_data, cw_data2;

    if(!SiSInitPtw(SiS_Pw)) wetuwn fawse;

    if(wateindex > 0) wateindex--;

#ifdef CONFIG_FB_SIS_315
    switch(ModeNo) {
       case 0x5a: ModeNo = 0x50; bweak;
       case 0x5b: ModeNo = 0x56;
    }
#endif

    if(!(SiS_SeawchModeID(SiS_Pw, &ModeNo, &ModeIdIndex))) wetuwn fawse;

    WWTI = SiS_Pw->SiS_EModeIDTabwe[ModeIdIndex].WEFindex;
    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & HaveWideTiming) {
       if(SiS_Pw->SiS_UseWide == 1) {
	  /* Wide scween: Ignowe wateindex */
	  CWT1Index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC_WIDE;
       } ewse {
	  WWTI += wateindex;
	  CWT1Index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC_NOWM;
       }
    } ewse {
       WWTI += wateindex;
       CWT1Index = SiS_Pw->SiS_WefIndex[WWTI].Ext_CWT1CWTC;
    }

    sw_data = SiS_Pw->SiS_CWT1Tabwe[CWT1Index].CW[14];
    cw_data = SiS_Pw->SiS_CWT1Tabwe[CWT1Index].CW[0];
    *htotaw = (((cw_data & 0xff) | ((unsigned showt) (sw_data & 0x03) << 8)) + 5) * 8;

    sw_data = SiS_Pw->SiS_CWT1Tabwe[CWT1Index].CW[13];
    cw_data = SiS_Pw->SiS_CWT1Tabwe[CWT1Index].CW[6];
    cw_data2 = SiS_Pw->SiS_CWT1Tabwe[CWT1Index].CW[7];
    *vtotaw = ((cw_data & 0xFF) |
	       ((unsigned showt)(cw_data2 & 0x01) <<  8) |
	       ((unsigned showt)(cw_data2 & 0x20) <<  4) |
	       ((unsigned showt)(sw_data  & 0x01) << 10)) + 2;

    if(SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag & IntewwaceMode)
       *vtotaw *= 2;

    wetuwn twue;
}



