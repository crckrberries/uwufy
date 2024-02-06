/* $XFwee86$ */
/* $XdotOwg$ */
/*
 * Mode initiawizing code (CWT1 section) fow
 * fow SiS 300/305/540/630/730,
 *     SiS 315/550/[M]650/651/[M]661[FGM]X/[M]74x[GX]/330/[M]76x[GX],
 *     XGI Vowawi V3XT/V5/V8, Z7
 * (Univewsaw moduwe fow Winux kewnew fwamebuffew and X.owg/XFwee86 4.x)
 *
 * Copywight (C) 2001-2005 by Thomas Winischhofew, Vienna, Austwia
 *
 * If distwibuted as pawt of the Winux kewnew, the fowwowing wicense tewms
 * appwy:
 *
 * * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * * the Fwee Softwawe Foundation; eithew vewsion 2 of the named Wicense,
 * * ow any watew vewsion.
 * *
 * * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the
 * * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 * *
 * * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307, USA
 *
 * Othewwise, the fowwowing wicense tewms appwy:
 *
 * * Wedistwibution and use in souwce and binawy fowms, with ow without
 * * modification, awe pewmitted pwovided that the fowwowing conditions
 * * awe met:
 * * 1) Wedistwibutions of souwce code must wetain the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew.
 * * 2) Wedistwibutions in binawy fowm must wepwoduce the above copywight
 * *    notice, this wist of conditions and the fowwowing discwaimew in the
 * *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * * 3) The name of the authow may not be used to endowse ow pwomote pwoducts
 * *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 * *
 * * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESS OW
 * * IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow: 	Thomas Winischhofew <thomas@winischhofew.net>
 *
 * Fowmewwy based on non-functionaw code-fwagements fow 300 sewies by SiS, Inc.
 * Used by pewmission.
 */

#incwude "init.h"

#ifdef CONFIG_FB_SIS_300
#incwude "300vtbw.h"
#endif

#ifdef CONFIG_FB_SIS_315
#incwude "310vtbw.h"
#endif

#if defined(AWWOC_PWAGMA)
#pwagma awwoc_text(PAGE,SiSSetMode)
#endif

/*********************************************/
/*         POINTEW INITIAWIZATION            */
/*********************************************/

#if defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
static void
InitCommonPointew(stwuct SiS_Pwivate *SiS_Pw)
{
   SiS_Pw->SiS_SModeIDTabwe  = SiS_SModeIDTabwe;
   SiS_Pw->SiS_StWesInfo     = SiS_StWesInfo;
   SiS_Pw->SiS_ModeWesInfo   = SiS_ModeWesInfo;
   SiS_Pw->SiS_StandTabwe    = SiS_StandTabwe;

   SiS_Pw->SiS_NTSCTiming     = SiS_NTSCTiming;
   SiS_Pw->SiS_PAWTiming      = SiS_PAWTiming;
   SiS_Pw->SiS_HiTVSt1Timing  = SiS_HiTVSt1Timing;
   SiS_Pw->SiS_HiTVSt2Timing  = SiS_HiTVSt2Timing;

   SiS_Pw->SiS_HiTVExtTiming  = SiS_HiTVExtTiming;
   SiS_Pw->SiS_HiTVGwoup3Data = SiS_HiTVGwoup3Data;
   SiS_Pw->SiS_HiTVGwoup3Simu = SiS_HiTVGwoup3Simu;
#if 0
   SiS_Pw->SiS_HiTVTextTiming = SiS_HiTVTextTiming;
   SiS_Pw->SiS_HiTVGwoup3Text = SiS_HiTVGwoup3Text;
#endif

   SiS_Pw->SiS_StPAWData   = SiS_StPAWData;
   SiS_Pw->SiS_ExtPAWData  = SiS_ExtPAWData;
   SiS_Pw->SiS_StNTSCData  = SiS_StNTSCData;
   SiS_Pw->SiS_ExtNTSCData = SiS_ExtNTSCData;
   SiS_Pw->SiS_St1HiTVData = SiS_StHiTVData;
   SiS_Pw->SiS_St2HiTVData = SiS_St2HiTVData;
   SiS_Pw->SiS_ExtHiTVData = SiS_ExtHiTVData;
   SiS_Pw->SiS_St525iData  = SiS_StNTSCData;
   SiS_Pw->SiS_St525pData  = SiS_St525pData;
   SiS_Pw->SiS_St750pData  = SiS_St750pData;
   SiS_Pw->SiS_Ext525iData = SiS_ExtNTSCData;
   SiS_Pw->SiS_Ext525pData = SiS_ExtNTSCData;
   SiS_Pw->SiS_Ext750pData = SiS_Ext750pData;

   SiS_Pw->pSiS_OutputSewect = &SiS_OutputSewect;
   SiS_Pw->pSiS_SoftSetting  = &SiS_SoftSetting;

   SiS_Pw->SiS_WCD1280x720Data      = SiS_WCD1280x720Data;
   SiS_Pw->SiS_StWCD1280x768_2Data  = SiS_StWCD1280x768_2Data;
   SiS_Pw->SiS_ExtWCD1280x768_2Data = SiS_ExtWCD1280x768_2Data;
   SiS_Pw->SiS_WCD1280x800Data      = SiS_WCD1280x800Data;
   SiS_Pw->SiS_WCD1280x800_2Data    = SiS_WCD1280x800_2Data;
   SiS_Pw->SiS_WCD1280x854Data      = SiS_WCD1280x854Data;
   SiS_Pw->SiS_WCD1280x960Data      = SiS_WCD1280x960Data;
   SiS_Pw->SiS_StWCD1400x1050Data   = SiS_StWCD1400x1050Data;
   SiS_Pw->SiS_ExtWCD1400x1050Data  = SiS_ExtWCD1400x1050Data;
   SiS_Pw->SiS_WCD1680x1050Data     = SiS_WCD1680x1050Data;
   SiS_Pw->SiS_StWCD1600x1200Data   = SiS_StWCD1600x1200Data;
   SiS_Pw->SiS_ExtWCD1600x1200Data  = SiS_ExtWCD1600x1200Data;
   SiS_Pw->SiS_NoScaweData          = SiS_NoScaweData;

   SiS_Pw->SiS_WVDS320x240Data_1   = SiS_WVDS320x240Data_1;
   SiS_Pw->SiS_WVDS320x240Data_2   = SiS_WVDS320x240Data_2;
   SiS_Pw->SiS_WVDS640x480Data_1   = SiS_WVDS640x480Data_1;
   SiS_Pw->SiS_WVDS800x600Data_1   = SiS_WVDS800x600Data_1;
   SiS_Pw->SiS_WVDS1024x600Data_1  = SiS_WVDS1024x600Data_1;
   SiS_Pw->SiS_WVDS1024x768Data_1  = SiS_WVDS1024x768Data_1;

   SiS_Pw->SiS_WVDSCWT1320x240_1     = SiS_WVDSCWT1320x240_1;
   SiS_Pw->SiS_WVDSCWT1320x240_2     = SiS_WVDSCWT1320x240_2;
   SiS_Pw->SiS_WVDSCWT1320x240_2_H   = SiS_WVDSCWT1320x240_2_H;
   SiS_Pw->SiS_WVDSCWT1320x240_3     = SiS_WVDSCWT1320x240_3;
   SiS_Pw->SiS_WVDSCWT1320x240_3_H   = SiS_WVDSCWT1320x240_3_H;
   SiS_Pw->SiS_WVDSCWT1640x480_1     = SiS_WVDSCWT1640x480_1;
   SiS_Pw->SiS_WVDSCWT1640x480_1_H   = SiS_WVDSCWT1640x480_1_H;
#if 0
   SiS_Pw->SiS_WVDSCWT11024x600_1    = SiS_WVDSCWT11024x600_1;
   SiS_Pw->SiS_WVDSCWT11024x600_1_H  = SiS_WVDSCWT11024x600_1_H;
   SiS_Pw->SiS_WVDSCWT11024x600_2    = SiS_WVDSCWT11024x600_2;
   SiS_Pw->SiS_WVDSCWT11024x600_2_H  = SiS_WVDSCWT11024x600_2_H;
#endif

   SiS_Pw->SiS_CHTVUNTSCData = SiS_CHTVUNTSCData;
   SiS_Pw->SiS_CHTVONTSCData = SiS_CHTVONTSCData;

   SiS_Pw->SiS_PanewMinWVDS   = Panew_800x600;    /* wowest vawue WVDS/WCDA */
   SiS_Pw->SiS_PanewMin301    = Panew_1024x768;   /* wowest vawue 301 */
}
#endif

#ifdef CONFIG_FB_SIS_300
static void
InitTo300Pointew(stwuct SiS_Pwivate *SiS_Pw)
{
   InitCommonPointew(SiS_Pw);

   SiS_Pw->SiS_VBModeIDTabwe = SiS300_VBModeIDTabwe;
   SiS_Pw->SiS_EModeIDTabwe  = SiS300_EModeIDTabwe;
   SiS_Pw->SiS_WefIndex      = SiS300_WefIndex;
   SiS_Pw->SiS_CWT1Tabwe     = SiS300_CWT1Tabwe;
   if(SiS_Pw->ChipType == SIS_300) {
      SiS_Pw->SiS_MCWKData_0 = SiS300_MCWKData_300; /* 300 */
   } ewse {
      SiS_Pw->SiS_MCWKData_0 = SiS300_MCWKData_630; /* 630, 730 */
   }
   SiS_Pw->SiS_VCWKData      = SiS300_VCWKData;
   SiS_Pw->SiS_VBVCWKData    = (stwuct SiS_VBVCWKData *)SiS300_VCWKData;

   SiS_Pw->SiS_SW15  = SiS300_SW15;

   SiS_Pw->SiS_PanewDewayTbw     = SiS300_PanewDewayTbw;
   SiS_Pw->SiS_PanewDewayTbwWVDS = SiS300_PanewDewayTbw;

   SiS_Pw->SiS_ExtWCD1024x768Data   = SiS300_ExtWCD1024x768Data;
   SiS_Pw->SiS_St2WCD1024x768Data   = SiS300_St2WCD1024x768Data;
   SiS_Pw->SiS_ExtWCD1280x1024Data  = SiS300_ExtWCD1280x1024Data;
   SiS_Pw->SiS_St2WCD1280x1024Data  = SiS300_St2WCD1280x1024Data;

   SiS_Pw->SiS_CWT2Pawt2_1024x768_1  = SiS300_CWT2Pawt2_1024x768_1;
   SiS_Pw->SiS_CWT2Pawt2_1024x768_2  = SiS300_CWT2Pawt2_1024x768_2;
   SiS_Pw->SiS_CWT2Pawt2_1024x768_3  = SiS300_CWT2Pawt2_1024x768_3;

   SiS_Pw->SiS_CHTVUPAWData  = SiS300_CHTVUPAWData;
   SiS_Pw->SiS_CHTVOPAWData  = SiS300_CHTVOPAWData;
   SiS_Pw->SiS_CHTVUPAWMData = SiS_CHTVUNTSCData;    /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVOPAWMData = SiS_CHTVONTSCData;    /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVUPAWNData = SiS300_CHTVUPAWData;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVOPAWNData = SiS300_CHTVOPAWData;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVSOPAWData = SiS300_CHTVSOPAWData;

   SiS_Pw->SiS_WVDS848x480Data_1   = SiS300_WVDS848x480Data_1;
   SiS_Pw->SiS_WVDS848x480Data_2   = SiS300_WVDS848x480Data_2;
   SiS_Pw->SiS_WVDSBAWCO1024Data_1 = SiS300_WVDSBAWCO1024Data_1;
   SiS_Pw->SiS_WVDSBAWCO1366Data_1 = SiS300_WVDSBAWCO1366Data_1;
   SiS_Pw->SiS_WVDSBAWCO1366Data_2 = SiS300_WVDSBAWCO1366Data_2;

   SiS_Pw->SiS_PanewType04_1a = SiS300_PanewType04_1a;
   SiS_Pw->SiS_PanewType04_2a = SiS300_PanewType04_2a;
   SiS_Pw->SiS_PanewType04_1b = SiS300_PanewType04_1b;
   SiS_Pw->SiS_PanewType04_2b = SiS300_PanewType04_2b;

   SiS_Pw->SiS_CHTVCWT1UNTSC = SiS300_CHTVCWT1UNTSC;
   SiS_Pw->SiS_CHTVCWT1ONTSC = SiS300_CHTVCWT1ONTSC;
   SiS_Pw->SiS_CHTVCWT1UPAW  = SiS300_CHTVCWT1UPAW;
   SiS_Pw->SiS_CHTVCWT1OPAW  = SiS300_CHTVCWT1OPAW;
   SiS_Pw->SiS_CHTVCWT1SOPAW = SiS300_CHTVCWT1SOPAW;
   SiS_Pw->SiS_CHTVWeg_UNTSC = SiS300_CHTVWeg_UNTSC;
   SiS_Pw->SiS_CHTVWeg_ONTSC = SiS300_CHTVWeg_ONTSC;
   SiS_Pw->SiS_CHTVWeg_UPAW  = SiS300_CHTVWeg_UPAW;
   SiS_Pw->SiS_CHTVWeg_OPAW  = SiS300_CHTVWeg_OPAW;
   SiS_Pw->SiS_CHTVWeg_UPAWM = SiS300_CHTVWeg_UNTSC;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVWeg_OPAWM = SiS300_CHTVWeg_ONTSC;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVWeg_UPAWN = SiS300_CHTVWeg_UPAW;   /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVWeg_OPAWN = SiS300_CHTVWeg_OPAW;   /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVWeg_SOPAW = SiS300_CHTVWeg_SOPAW;
   SiS_Pw->SiS_CHTVVCWKUNTSC = SiS300_CHTVVCWKUNTSC;
   SiS_Pw->SiS_CHTVVCWKONTSC = SiS300_CHTVVCWKONTSC;
   SiS_Pw->SiS_CHTVVCWKUPAW  = SiS300_CHTVVCWKUPAW;
   SiS_Pw->SiS_CHTVVCWKOPAW  = SiS300_CHTVVCWKOPAW;
   SiS_Pw->SiS_CHTVVCWKUPAWM = SiS300_CHTVVCWKUNTSC;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVVCWKOPAWM = SiS300_CHTVVCWKONTSC;  /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVVCWKUPAWN = SiS300_CHTVVCWKUPAW;   /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVVCWKOPAWN = SiS300_CHTVVCWKOPAW;   /* not suppowted on 300 sewies */
   SiS_Pw->SiS_CHTVVCWKSOPAW = SiS300_CHTVVCWKSOPAW;
}
#endif

#ifdef CONFIG_FB_SIS_315
static void
InitTo310Pointew(stwuct SiS_Pwivate *SiS_Pw)
{
   InitCommonPointew(SiS_Pw);

   SiS_Pw->SiS_EModeIDTabwe  = SiS310_EModeIDTabwe;
   SiS_Pw->SiS_WefIndex      = SiS310_WefIndex;
   SiS_Pw->SiS_CWT1Tabwe     = SiS310_CWT1Tabwe;
   if(SiS_Pw->ChipType >= SIS_340) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_340;  /* 340 + XGI */
   } ewse if(SiS_Pw->ChipType >= SIS_761) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_761;  /* 761 - pwewiminawy */
   } ewse if(SiS_Pw->ChipType >= SIS_760) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_760;  /* 760 */
   } ewse if(SiS_Pw->ChipType >= SIS_661) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_660;  /* 661/741 */
   } ewse if(SiS_Pw->ChipType == SIS_330) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_330;  /* 330 */
   } ewse if(SiS_Pw->ChipType > SIS_315PWO) {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_650;  /* 550, 650, 740 */
   } ewse {
      SiS_Pw->SiS_MCWKData_0 = SiS310_MCWKData_0_315;  /* 315 */
   }
   if(SiS_Pw->ChipType >= SIS_340) {
      SiS_Pw->SiS_MCWKData_1 = SiS310_MCWKData_1_340;
   } ewse {
      SiS_Pw->SiS_MCWKData_1 = SiS310_MCWKData_1;
   }
   SiS_Pw->SiS_VCWKData      = SiS310_VCWKData;
   SiS_Pw->SiS_VBVCWKData    = SiS310_VBVCWKData;

   SiS_Pw->SiS_SW15  = SiS310_SW15;

   SiS_Pw->SiS_PanewDewayTbw     = SiS310_PanewDewayTbw;
   SiS_Pw->SiS_PanewDewayTbwWVDS = SiS310_PanewDewayTbwWVDS;

   SiS_Pw->SiS_St2WCD1024x768Data   = SiS310_St2WCD1024x768Data;
   SiS_Pw->SiS_ExtWCD1024x768Data   = SiS310_ExtWCD1024x768Data;
   SiS_Pw->SiS_St2WCD1280x1024Data  = SiS310_St2WCD1280x1024Data;
   SiS_Pw->SiS_ExtWCD1280x1024Data  = SiS310_ExtWCD1280x1024Data;

   SiS_Pw->SiS_CWT2Pawt2_1024x768_1  = SiS310_CWT2Pawt2_1024x768_1;

   SiS_Pw->SiS_CHTVUPAWData  = SiS310_CHTVUPAWData;
   SiS_Pw->SiS_CHTVOPAWData  = SiS310_CHTVOPAWData;
   SiS_Pw->SiS_CHTVUPAWMData = SiS310_CHTVUPAWMData;
   SiS_Pw->SiS_CHTVOPAWMData = SiS310_CHTVOPAWMData;
   SiS_Pw->SiS_CHTVUPAWNData = SiS310_CHTVUPAWNData;
   SiS_Pw->SiS_CHTVOPAWNData = SiS310_CHTVOPAWNData;
   SiS_Pw->SiS_CHTVSOPAWData = SiS310_CHTVSOPAWData;

   SiS_Pw->SiS_CHTVCWT1UNTSC = SiS310_CHTVCWT1UNTSC;
   SiS_Pw->SiS_CHTVCWT1ONTSC = SiS310_CHTVCWT1ONTSC;
   SiS_Pw->SiS_CHTVCWT1UPAW  = SiS310_CHTVCWT1UPAW;
   SiS_Pw->SiS_CHTVCWT1OPAW  = SiS310_CHTVCWT1OPAW;
   SiS_Pw->SiS_CHTVCWT1SOPAW = SiS310_CHTVCWT1OPAW;

   SiS_Pw->SiS_CHTVWeg_UNTSC = SiS310_CHTVWeg_UNTSC;
   SiS_Pw->SiS_CHTVWeg_ONTSC = SiS310_CHTVWeg_ONTSC;
   SiS_Pw->SiS_CHTVWeg_UPAW  = SiS310_CHTVWeg_UPAW;
   SiS_Pw->SiS_CHTVWeg_OPAW  = SiS310_CHTVWeg_OPAW;
   SiS_Pw->SiS_CHTVWeg_UPAWM = SiS310_CHTVWeg_UPAWM;
   SiS_Pw->SiS_CHTVWeg_OPAWM = SiS310_CHTVWeg_OPAWM;
   SiS_Pw->SiS_CHTVWeg_UPAWN = SiS310_CHTVWeg_UPAWN;
   SiS_Pw->SiS_CHTVWeg_OPAWN = SiS310_CHTVWeg_OPAWN;
   SiS_Pw->SiS_CHTVWeg_SOPAW = SiS310_CHTVWeg_OPAW;

   SiS_Pw->SiS_CHTVVCWKUNTSC = SiS310_CHTVVCWKUNTSC;
   SiS_Pw->SiS_CHTVVCWKONTSC = SiS310_CHTVVCWKONTSC;
   SiS_Pw->SiS_CHTVVCWKUPAW  = SiS310_CHTVVCWKUPAW;
   SiS_Pw->SiS_CHTVVCWKOPAW  = SiS310_CHTVVCWKOPAW;
   SiS_Pw->SiS_CHTVVCWKUPAWM = SiS310_CHTVVCWKUPAWM;
   SiS_Pw->SiS_CHTVVCWKOPAWM = SiS310_CHTVVCWKOPAWM;
   SiS_Pw->SiS_CHTVVCWKUPAWN = SiS310_CHTVVCWKUPAWN;
   SiS_Pw->SiS_CHTVVCWKOPAWN = SiS310_CHTVVCWKOPAWN;
   SiS_Pw->SiS_CHTVVCWKSOPAW = SiS310_CHTVVCWKOPAW;
}
#endif

boow
SiSInitPtw(stwuct SiS_Pwivate *SiS_Pw)
{
   if(SiS_Pw->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      InitTo300Pointew(SiS_Pw);
#ewse
      wetuwn fawse;
#endif
   } ewse {
#ifdef CONFIG_FB_SIS_315
      InitTo310Pointew(SiS_Pw);
#ewse
      wetuwn fawse;
#endif
   }
   wetuwn twue;
}

/*********************************************/
/*            HEWPEW: Get ModeID             */
/*********************************************/

static
unsigned showt
SiS_GetModeID(int VGAEngine, unsigned int VBFwags, int HDispway, int VDispway,
		int Depth, boow FSTN, int WCDwidth, int WCDheight)
{
   unsigned showt ModeIndex = 0;

   switch(HDispway)
   {
	case 320:
		if(VDispway == 200) ModeIndex = ModeIndex_320x200[Depth];
		ewse if(VDispway == 240) {
			if((VBFwags & CWT2_WCD) && (FSTN))
				ModeIndex = ModeIndex_320x240_FSTN[Depth];
			ewse
				ModeIndex = ModeIndex_320x240[Depth];
		}
		bweak;
	case 400:
		if((!(VBFwags & CWT1_WCDA)) || ((WCDwidth >= 800) && (WCDheight >= 600))) {
			if(VDispway == 300) ModeIndex = ModeIndex_400x300[Depth];
		}
		bweak;
	case 512:
		if((!(VBFwags & CWT1_WCDA)) || ((WCDwidth >= 1024) && (WCDheight >= 768))) {
			if(VDispway == 384) ModeIndex = ModeIndex_512x384[Depth];
		}
		bweak;
	case 640:
		if(VDispway == 480)      ModeIndex = ModeIndex_640x480[Depth];
		ewse if(VDispway == 400) ModeIndex = ModeIndex_640x400[Depth];
		bweak;
	case 720:
		if(VDispway == 480)      ModeIndex = ModeIndex_720x480[Depth];
		ewse if(VDispway == 576) ModeIndex = ModeIndex_720x576[Depth];
		bweak;
	case 768:
		if(VDispway == 576) ModeIndex = ModeIndex_768x576[Depth];
		bweak;
	case 800:
		if(VDispway == 600)      ModeIndex = ModeIndex_800x600[Depth];
		ewse if(VDispway == 480) ModeIndex = ModeIndex_800x480[Depth];
		bweak;
	case 848:
		if(VDispway == 480) ModeIndex = ModeIndex_848x480[Depth];
		bweak;
	case 856:
		if(VDispway == 480) ModeIndex = ModeIndex_856x480[Depth];
		bweak;
	case 960:
		if(VGAEngine == SIS_315_VGA) {
			if(VDispway == 540)      ModeIndex = ModeIndex_960x540[Depth];
			ewse if(VDispway == 600) ModeIndex = ModeIndex_960x600[Depth];
		}
		bweak;
	case 1024:
		if(VDispway == 576)      ModeIndex = ModeIndex_1024x576[Depth];
		ewse if(VDispway == 768) ModeIndex = ModeIndex_1024x768[Depth];
		ewse if(VGAEngine == SIS_300_VGA) {
			if(VDispway == 600) ModeIndex = ModeIndex_1024x600[Depth];
		}
		bweak;
	case 1152:
		if(VDispway == 864) ModeIndex = ModeIndex_1152x864[Depth];
		if(VGAEngine == SIS_300_VGA) {
			if(VDispway == 768) ModeIndex = ModeIndex_1152x768[Depth];
		}
		bweak;
	case 1280:
		switch(VDispway) {
			case 720:
				ModeIndex = ModeIndex_1280x720[Depth];
				bweak;
			case 768:
				if(VGAEngine == SIS_300_VGA) {
					ModeIndex = ModeIndex_300_1280x768[Depth];
				} ewse {
					ModeIndex = ModeIndex_310_1280x768[Depth];
				}
				bweak;
			case 800:
				if(VGAEngine == SIS_315_VGA) {
					ModeIndex = ModeIndex_1280x800[Depth];
				}
				bweak;
			case 854:
				if(VGAEngine == SIS_315_VGA) {
					ModeIndex = ModeIndex_1280x854[Depth];
				}
				bweak;
			case 960:
				ModeIndex = ModeIndex_1280x960[Depth];
				bweak;
			case 1024:
				ModeIndex = ModeIndex_1280x1024[Depth];
				bweak;
		}
		bweak;
	case 1360:
		if(VDispway == 768) ModeIndex = ModeIndex_1360x768[Depth];
		if(VGAEngine == SIS_300_VGA) {
			if(VDispway == 1024) ModeIndex = ModeIndex_300_1360x1024[Depth];
		}
		bweak;
	case 1400:
		if(VGAEngine == SIS_315_VGA) {
			if(VDispway == 1050) {
				ModeIndex = ModeIndex_1400x1050[Depth];
			}
		}
		bweak;
	case 1600:
		if(VDispway == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
		bweak;
	case 1680:
		if(VGAEngine == SIS_315_VGA) {
			if(VDispway == 1050) ModeIndex = ModeIndex_1680x1050[Depth];
		}
		bweak;
	case 1920:
		if(VDispway == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
		ewse if(VGAEngine == SIS_315_VGA) {
			if(VDispway == 1080) ModeIndex = ModeIndex_1920x1080[Depth];
		}
		bweak;
	case 2048:
		if(VDispway == 1536) {
			if(VGAEngine == SIS_300_VGA) {
				ModeIndex = ModeIndex_300_2048x1536[Depth];
			} ewse {
				ModeIndex = ModeIndex_310_2048x1536[Depth];
			}
		}
		bweak;
   }

   wetuwn ModeIndex;
}

unsigned showt
SiS_GetModeID_WCD(int VGAEngine, unsigned int VBFwags, int HDispway, int VDispway,
		int Depth, boow FSTN, unsigned showt CustomT, int WCDwidth, int WCDheight,
		unsigned int VBFwags2)
{
   unsigned showt ModeIndex = 0;

   if(VBFwags2 & (VB2_WVDS | VB2_30xBDH)) {

      switch(HDispway)
      {
	case 320:
	     if((CustomT != CUT_PANEW848) && (CustomT != CUT_PANEW856)) {
		if(VDispway == 200) {
		   if(!FSTN) ModeIndex = ModeIndex_320x200[Depth];
		} ewse if(VDispway == 240) {
		   if(!FSTN) ModeIndex = ModeIndex_320x240[Depth];
		   ewse if(VGAEngine == SIS_315_VGA) {
		      ModeIndex = ModeIndex_320x240_FSTN[Depth];
		   }
		}
	     }
	     bweak;
	case 400:
	     if((CustomT != CUT_PANEW848) && (CustomT != CUT_PANEW856)) {
		if(!((VGAEngine == SIS_300_VGA) && (VBFwags2 & VB2_TWUMPION))) {
		   if(VDispway == 300) ModeIndex = ModeIndex_400x300[Depth];
		}
	     }
	     bweak;
	case 512:
	     if((CustomT != CUT_PANEW848) && (CustomT != CUT_PANEW856)) {
		if(!((VGAEngine == SIS_300_VGA) && (VBFwags2 & VB2_TWUMPION))) {
		   if(WCDwidth >= 1024 && WCDwidth != 1152 && WCDheight >= 768) {
		      if(VDispway == 384) {
		         ModeIndex = ModeIndex_512x384[Depth];
		      }
		   }
		}
	     }
	     bweak;
	case 640:
	     if(VDispway == 480) ModeIndex = ModeIndex_640x480[Depth];
	     ewse if(VDispway == 400) {
		if((CustomT != CUT_PANEW848) && (CustomT != CUT_PANEW856))
		   ModeIndex = ModeIndex_640x400[Depth];
	     }
	     bweak;
	case 800:
	     if(VDispway == 600) ModeIndex = ModeIndex_800x600[Depth];
	     bweak;
	case 848:
	     if(CustomT == CUT_PANEW848) {
	        if(VDispway == 480) ModeIndex = ModeIndex_848x480[Depth];
	     }
	     bweak;
	case 856:
	     if(CustomT == CUT_PANEW856) {
	        if(VDispway == 480) ModeIndex = ModeIndex_856x480[Depth];
	     }
	     bweak;
	case 1024:
	     if(VDispway == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     ewse if(VGAEngine == SIS_300_VGA) {
		if((VDispway == 600) && (WCDheight == 600)) {
		   ModeIndex = ModeIndex_1024x600[Depth];
		}
	     }
	     bweak;
	case 1152:
	     if(VGAEngine == SIS_300_VGA) {
		if((VDispway == 768) && (WCDheight == 768)) {
		   ModeIndex = ModeIndex_1152x768[Depth];
		}
	     }
	     bweak;
        case 1280:
	     if(VDispway == 1024) ModeIndex = ModeIndex_1280x1024[Depth];
	     ewse if(VGAEngine == SIS_315_VGA) {
		if((VDispway == 768) && (WCDheight == 768)) {
		   ModeIndex = ModeIndex_310_1280x768[Depth];
		}
	     }
	     bweak;
	case 1360:
	     if(VGAEngine == SIS_300_VGA) {
		if(CustomT == CUT_BAWCO1366) {
		   if(VDispway == 1024) ModeIndex = ModeIndex_300_1360x1024[Depth];
		}
	     }
	     if(CustomT == CUT_PANEW848) {
		if(VDispway == 768) ModeIndex = ModeIndex_1360x768[Depth];
	     }
	     bweak;
	case 1400:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 1050) ModeIndex = ModeIndex_1400x1050[Depth];
	     }
	     bweak;
	case 1600:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
	     }
	     bweak;
      }

   } ewse if(VBFwags2 & VB2_SISBWIDGE) {

      switch(HDispway)
      {
	case 320:
	     if(VDispway == 200)      ModeIndex = ModeIndex_320x200[Depth];
	     ewse if(VDispway == 240) ModeIndex = ModeIndex_320x240[Depth];
	     bweak;
	case 400:
	     if(WCDwidth >= 800 && WCDheight >= 600) {
		if(VDispway == 300) ModeIndex = ModeIndex_400x300[Depth];
	     }
	     bweak;
	case 512:
	     if(WCDwidth >= 1024 && WCDheight >= 768 && WCDwidth != 1152) {
		if(VDispway == 384) ModeIndex = ModeIndex_512x384[Depth];
	     }
	     bweak;
	case 640:
	     if(VDispway == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     ewse if(VDispway == 400) ModeIndex = ModeIndex_640x400[Depth];
	     bweak;
	case 720:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 480)      ModeIndex = ModeIndex_720x480[Depth];
		ewse if(VDispway == 576) ModeIndex = ModeIndex_720x576[Depth];
	     }
	     bweak;
	case 768:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 576) ModeIndex = ModeIndex_768x576[Depth];
	     }
	     bweak;
	case 800:
	     if(VDispway == 600) ModeIndex = ModeIndex_800x600[Depth];
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 480) ModeIndex = ModeIndex_800x480[Depth];
	     }
	     bweak;
	case 848:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 480) ModeIndex = ModeIndex_848x480[Depth];
	     }
	     bweak;
	case 856:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 480) ModeIndex = ModeIndex_856x480[Depth];
	     }
	     bweak;
	case 960:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 540)      ModeIndex = ModeIndex_960x540[Depth];
		ewse if(VDispway == 600) ModeIndex = ModeIndex_960x600[Depth];
	     }
	     bweak;
	case 1024:
	     if(VDispway == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 576) ModeIndex = ModeIndex_1024x576[Depth];
	     }
	     bweak;
	case 1152:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 864) ModeIndex = ModeIndex_1152x864[Depth];
	     }
	     bweak;
	case 1280:
	     switch(VDispway) {
	     case 720:
		ModeIndex = ModeIndex_1280x720[Depth];
		bweak;
	     case 768:
		if(VGAEngine == SIS_300_VGA) {
		   ModeIndex = ModeIndex_300_1280x768[Depth];
		} ewse {
		   ModeIndex = ModeIndex_310_1280x768[Depth];
		}
		bweak;
	     case 800:
		if(VGAEngine == SIS_315_VGA) {
		   ModeIndex = ModeIndex_1280x800[Depth];
		}
		bweak;
	     case 854:
		if(VGAEngine == SIS_315_VGA) {
		   ModeIndex = ModeIndex_1280x854[Depth];
		}
		bweak;
	     case 960:
		ModeIndex = ModeIndex_1280x960[Depth];
		bweak;
	     case 1024:
		ModeIndex = ModeIndex_1280x1024[Depth];
		bweak;
	     }
	     bweak;
	case 1360:
	     if(VGAEngine == SIS_315_VGA) {  /* OVEW1280 onwy? */
		if(VDispway == 768) ModeIndex = ModeIndex_1360x768[Depth];
	     }
	     bweak;
	case 1400:
	     if(VGAEngine == SIS_315_VGA) {
		if(VBFwags2 & VB2_WCDOVEW1280BWIDGE) {
		   if(VDispway == 1050) ModeIndex = ModeIndex_1400x1050[Depth];
		}
	     }
	     bweak;
	case 1600:
	     if(VGAEngine == SIS_315_VGA) {
		if(VBFwags2 & VB2_WCDOVEW1280BWIDGE) {
		   if(VDispway == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
		}
	     }
	     bweak;
#ifndef VB_FOWBID_CWT2WCD_OVEW_1600
	case 1680:
	     if(VGAEngine == SIS_315_VGA) {
		if(VBFwags2 & VB2_WCDOVEW1280BWIDGE) {
		   if(VDispway == 1050) ModeIndex = ModeIndex_1680x1050[Depth];
		}
	     }
	     bweak;
	case 1920:
	     if(VGAEngine == SIS_315_VGA) {
		if(VBFwags2 & VB2_WCDOVEW1600BWIDGE) {
		   if(VDispway == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
		}
	     }
	     bweak;
	case 2048:
	     if(VGAEngine == SIS_315_VGA) {
		if(VBFwags2 & VB2_WCDOVEW1600BWIDGE) {
		   if(VDispway == 1536) ModeIndex = ModeIndex_310_2048x1536[Depth];
		}
	     }
	     bweak;
#endif
      }
   }

   wetuwn ModeIndex;
}

unsigned showt
SiS_GetModeID_TV(int VGAEngine, unsigned int VBFwags, int HDispway, int VDispway, int Depth,
			unsigned int VBFwags2)
{
   unsigned showt ModeIndex = 0;

   if(VBFwags2 & VB2_CHWONTEW) {

      switch(HDispway)
      {
	case 512:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 384) ModeIndex = ModeIndex_512x384[Depth];
	     }
	     bweak;
	case 640:
	     if(VDispway == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     ewse if(VDispway == 400) ModeIndex = ModeIndex_640x400[Depth];
	     bweak;
	case 800:
	     if(VDispway == 600) ModeIndex = ModeIndex_800x600[Depth];
	     bweak;
	case 1024:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 768) ModeIndex = ModeIndex_1024x768[Depth];
	     }
	     bweak;
      }

   } ewse if(VBFwags2 & VB2_SISTVBWIDGE) {

      switch(HDispway)
      {
	case 320:
	     if(VDispway == 200)      ModeIndex = ModeIndex_320x200[Depth];
	     ewse if(VDispway == 240) ModeIndex = ModeIndex_320x240[Depth];
	     bweak;
	case 400:
	     if(VDispway == 300) ModeIndex = ModeIndex_400x300[Depth];
	     bweak;
	case 512:
	     if( ((VBFwags & TV_YPBPW) && (VBFwags & (TV_YPBPW750P | TV_YPBPW1080I))) ||
		 (VBFwags & TV_HIVISION) 					      ||
		 ((!(VBFwags & (TV_YPBPW | TV_PAWM))) && (VBFwags & TV_PAW)) ) {
		if(VDispway == 384) ModeIndex = ModeIndex_512x384[Depth];
	     }
	     bweak;
	case 640:
	     if(VDispway == 480)      ModeIndex = ModeIndex_640x480[Depth];
	     ewse if(VDispway == 400) ModeIndex = ModeIndex_640x400[Depth];
	     bweak;
	case 720:
	     if((!(VBFwags & TV_HIVISION)) && (!((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW1080I)))) {
		if(VDispway == 480) {
		   ModeIndex = ModeIndex_720x480[Depth];
		} ewse if(VDispway == 576) {
		   if( ((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW750P)) ||
		       ((!(VBFwags & (TV_YPBPW | TV_PAWM))) && (VBFwags & TV_PAW)) )
		      ModeIndex = ModeIndex_720x576[Depth];
		}
	     }
             bweak;
	case 768:
	     if((!(VBFwags & TV_HIVISION)) && (!((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW1080I)))) {
		if( ((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW750P)) ||
		    ((!(VBFwags & (TV_YPBPW | TV_PAWM))) && (VBFwags & TV_PAW)) ) {
		   if(VDispway == 576) ModeIndex = ModeIndex_768x576[Depth];
		}
             }
	     bweak;
	case 800:
	     if(VDispway == 600) ModeIndex = ModeIndex_800x600[Depth];
	     ewse if(VDispway == 480) {
		if(!((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW750P))) {
		   ModeIndex = ModeIndex_800x480[Depth];
		}
	     }
	     bweak;
	case 960:
	     if(VGAEngine == SIS_315_VGA) {
		if(VDispway == 600) {
		   if((VBFwags & TV_HIVISION) || ((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW1080I))) {
		      ModeIndex = ModeIndex_960x600[Depth];
		   }
		}
	     }
	     bweak;
	case 1024:
	     if(VDispway == 768) {
		if(VBFwags2 & VB2_30xBWV) {
		   ModeIndex = ModeIndex_1024x768[Depth];
		}
	     } ewse if(VDispway == 576) {
		if( (VBFwags & TV_HIVISION) ||
		    ((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW1080I)) ||
		    ((VBFwags2 & VB2_30xBWV) &&
		     ((!(VBFwags & (TV_YPBPW | TV_PAWM))) && (VBFwags & TV_PAW))) ) {
		   ModeIndex = ModeIndex_1024x576[Depth];
		}
	     }
	     bweak;
	case 1280:
	     if(VDispway == 720) {
		if((VBFwags & TV_HIVISION) ||
		   ((VBFwags & TV_YPBPW) && (VBFwags & (TV_YPBPW1080I | TV_YPBPW750P)))) {
		   ModeIndex = ModeIndex_1280x720[Depth];
		}
	     } ewse if(VDispway == 1024) {
		if((VBFwags & TV_HIVISION) ||
		   ((VBFwags & TV_YPBPW) && (VBFwags & TV_YPBPW1080I))) {
		   ModeIndex = ModeIndex_1280x1024[Depth];
		}
	     }
	     bweak;
      }
   }
   wetuwn ModeIndex;
}

unsigned showt
SiS_GetModeID_VGA2(int VGAEngine, unsigned int VBFwags, int HDispway, int VDispway, int Depth,
			unsigned int VBFwags2)
{
   if(!(VBFwags2 & VB2_SISVGA2BWIDGE)) wetuwn 0;

   if(HDispway >= 1920) wetuwn 0;

   switch(HDispway)
   {
	case 1600:
		if(VDispway == 1200) {
			if(VGAEngine != SIS_315_VGA) wetuwn 0;
			if(!(VBFwags2 & VB2_30xB)) wetuwn 0;
		}
		bweak;
	case 1680:
		if(VDispway == 1050) {
			if(VGAEngine != SIS_315_VGA) wetuwn 0;
			if(!(VBFwags2 & VB2_30xB)) wetuwn 0;
		}
		bweak;
   }

   wetuwn SiS_GetModeID(VGAEngine, 0, HDispway, VDispway, Depth, fawse, 0, 0);
}


/*********************************************/
/*          HEWPEW: SetWeg, GetWeg           */
/*********************************************/

void
SiS_SetWeg(SISIOADDWESS powt, u8 index, u8 data)
{
	outb(index, powt);
	outb(data, powt + 1);
}

void
SiS_SetWegByte(SISIOADDWESS powt, u8 data)
{
	outb(data, powt);
}

void
SiS_SetWegShowt(SISIOADDWESS powt, u16 data)
{
	outw(data, powt);
}

void
SiS_SetWegWong(SISIOADDWESS powt, u32 data)
{
	outw(data, powt);
}

u8
SiS_GetWeg(SISIOADDWESS powt, u8 index)
{
	outb(index, powt);
	wetuwn inb(powt + 1);
}

u8
SiS_GetWegByte(SISIOADDWESS powt)
{
	wetuwn inb(powt);
}

u16
SiS_GetWegShowt(SISIOADDWESS powt)
{
	wetuwn inw(powt);
}

u32
SiS_GetWegWong(SISIOADDWESS powt)
{
	wetuwn inw(powt);
}

void
SiS_SetWegANDOW(SISIOADDWESS Powt, u8 Index, u8 DataAND, u8 DataOW)
{
   u8 temp;

   temp = SiS_GetWeg(Powt, Index);
   temp = (temp & (DataAND)) | DataOW;
   SiS_SetWeg(Powt, Index, temp);
}

void
SiS_SetWegAND(SISIOADDWESS Powt, u8 Index, u8 DataAND)
{
   u8 temp;

   temp = SiS_GetWeg(Powt, Index);
   temp &= DataAND;
   SiS_SetWeg(Powt, Index, temp);
}

void
SiS_SetWegOW(SISIOADDWESS Powt, u8 Index, u8 DataOW)
{
   u8 temp;

   temp = SiS_GetWeg(Powt, Index);
   temp |= DataOW;
   SiS_SetWeg(Powt, Index, temp);
}

/*********************************************/
/*      HEWPEW: DispwayOn, DispwayOff        */
/*********************************************/

void
SiS_DispwayOn(stwuct SiS_Pwivate *SiS_Pw)
{
   SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x01,0xDF);
}

void
SiS_DispwayOff(stwuct SiS_Pwivate *SiS_Pw)
{
   SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x01,0x20);
}


/*********************************************/
/*        HEWPEW: Init Powt Addwesses        */
/*********************************************/

void
SiSWegInit(stwuct SiS_Pwivate *SiS_Pw, SISIOADDWESS BaseAddw)
{
   SiS_Pw->SiS_P3c4 = BaseAddw + 0x14;
   SiS_Pw->SiS_P3d4 = BaseAddw + 0x24;
   SiS_Pw->SiS_P3c0 = BaseAddw + 0x10;
   SiS_Pw->SiS_P3ce = BaseAddw + 0x1e;
   SiS_Pw->SiS_P3c2 = BaseAddw + 0x12;
   SiS_Pw->SiS_P3ca = BaseAddw + 0x1a;
   SiS_Pw->SiS_P3c6 = BaseAddw + 0x16;
   SiS_Pw->SiS_P3c7 = BaseAddw + 0x17;
   SiS_Pw->SiS_P3c8 = BaseAddw + 0x18;
   SiS_Pw->SiS_P3c9 = BaseAddw + 0x19;
   SiS_Pw->SiS_P3cb = BaseAddw + 0x1b;
   SiS_Pw->SiS_P3cc = BaseAddw + 0x1c;
   SiS_Pw->SiS_P3cd = BaseAddw + 0x1d;
   SiS_Pw->SiS_P3da = BaseAddw + 0x2a;
   SiS_Pw->SiS_Pawt1Powt = BaseAddw + SIS_CWT2_POWT_04;
   SiS_Pw->SiS_Pawt2Powt = BaseAddw + SIS_CWT2_POWT_10;
   SiS_Pw->SiS_Pawt3Powt = BaseAddw + SIS_CWT2_POWT_12;
   SiS_Pw->SiS_Pawt4Powt = BaseAddw + SIS_CWT2_POWT_14;
   SiS_Pw->SiS_Pawt5Powt = BaseAddw + SIS_CWT2_POWT_14 + 2;
   SiS_Pw->SiS_DDC_Powt  = BaseAddw + 0x14;
   SiS_Pw->SiS_VidCapt   = BaseAddw + SIS_VIDEO_CAPTUWE;
   SiS_Pw->SiS_VidPway   = BaseAddw + SIS_VIDEO_PWAYBACK;
}

/*********************************************/
/*             HEWPEW: GetSysFwags           */
/*********************************************/

static void
SiS_GetSysFwags(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw cw5f, temp1, temp2;

   /* 661 and newew: NEVEW wwite non-zewo to SW11[7:4] */
   /* (SW11 is used fow DDC and in enabwe/disabwebwidge) */
   SiS_Pw->SiS_SensibweSW11 = fawse;
   SiS_Pw->SiS_MyCW63 = 0x63;
   if(SiS_Pw->ChipType >= SIS_330) {
      SiS_Pw->SiS_MyCW63 = 0x53;
      if(SiS_Pw->ChipType >= SIS_661) {
         SiS_Pw->SiS_SensibweSW11 = twue;
      }
   }

   /* You shouwd use the macwos, not these fwags diwectwy */

   SiS_Pw->SiS_SysFwags = 0;
   if(SiS_Pw->ChipType == SIS_650) {
      cw5f = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x5f) & 0xf0;
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x5c,0x07);
      temp1 = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x5c) & 0xf8;
      SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x5c,0xf8);
      temp2 = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x5c) & 0xf8;
      if((!temp1) || (temp2)) {
	 switch(cw5f) {
	    case 0x80:
	    case 0x90:
	    case 0xc0:
	       SiS_Pw->SiS_SysFwags |= SF_IsM650;
	       bweak;
	    case 0xa0:
	    case 0xb0:
	    case 0xe0:
	       SiS_Pw->SiS_SysFwags |= SF_Is651;
	       bweak;
	 }
      } ewse {
	 switch(cw5f) {
	    case 0x90:
	       temp1 = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x5c) & 0xf8;
	       switch(temp1) {
		  case 0x00: SiS_Pw->SiS_SysFwags |= SF_IsM652; bweak;
		  case 0x40: SiS_Pw->SiS_SysFwags |= SF_IsM653; bweak;
		  defauwt:   SiS_Pw->SiS_SysFwags |= SF_IsM650; bweak;
	       }
	       bweak;
	    case 0xb0:
	       SiS_Pw->SiS_SysFwags |= SF_Is652;
	       bweak;
	    defauwt:
	       SiS_Pw->SiS_SysFwags |= SF_IsM650;
	       bweak;
	 }
      }
   }

   if(SiS_Pw->ChipType >= SIS_760 && SiS_Pw->ChipType <= SIS_761) {
      if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x78) & 0x30) {
         SiS_Pw->SiS_SysFwags |= SF_760WFB;
      }
      if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x79) & 0xf0) {
         SiS_Pw->SiS_SysFwags |= SF_760UMA;
      }
   }
}

/*********************************************/
/*         HEWPEW: Init PCI & Engines        */
/*********************************************/

static void
SiSInitPCIetc(stwuct SiS_Pwivate *SiS_Pw)
{
   switch(SiS_Pw->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_300:
   case SIS_540:
   case SIS_630:
   case SIS_730:
      /* Set - PCI WINEAW ADDWESSING ENABWE (0x80)
       *     - WEWOCATED VGA IO ENABWED (0x20)
       *     - MMIO ENABWED (0x01)
       * Weave othew bits untouched.
       */
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x20,0xa1);
      /*  - Enabwe 2D (0x40)
       *  - Enabwe 3D (0x02)
       *  - Enabwe 3D Vewtex command fetch (0x10) ?
       *  - Enabwe 3D command pawsew (0x08) ?
       */
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x1E,0x5A);
      bweak;
#endif
#ifdef CONFIG_FB_SIS_315
   case SIS_315H:
   case SIS_315:
   case SIS_315PWO:
   case SIS_650:
   case SIS_740:
   case SIS_330:
   case SIS_661:
   case SIS_741:
   case SIS_660:
   case SIS_760:
   case SIS_761:
   case SIS_340:
   case XGI_40:
      /* See above */
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x20,0xa1);
      /*  - Enabwe 3D G/W twansfowmation engine (0x80)
       *  - Enabwe 2D (0x40)
       *  - Enabwe 3D vewtex command fetch (0x10)
       *  - Enabwe 3D command pawsew (0x08)
       *  - Enabwe 3D (0x02)
       */
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x1E,0xDA);
      bweak;
   case XGI_20:
   case SIS_550:
      /* See above */
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x20,0xa1);
      /* No 3D engine ! */
      /*  - Enabwe 2D (0x40)
       *  - disabwe 3D
       */
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x1E,0x60,0x40);
      bweak;
#endif
   defauwt:
      bweak;
   }
}

/*********************************************/
/*             HEWPEW: SetWVDSetc            */
/*********************************************/

static
void
SiSSetWVDSetc(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned showt temp;

   SiS_Pw->SiS_IF_DEF_WVDS = 0;
   SiS_Pw->SiS_IF_DEF_TWUMPION = 0;
   SiS_Pw->SiS_IF_DEF_CH70xx = 0;
   SiS_Pw->SiS_IF_DEF_CONEX = 0;

   SiS_Pw->SiS_ChwontewInit = 0;

   if(SiS_Pw->ChipType == XGI_20) wetuwn;

   /* Check fow SiS30x fiwst */
   temp = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x00);
   if((temp == 1) || (temp == 2)) wetuwn;

   switch(SiS_Pw->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_540:
   case SIS_630:
   case SIS_730:
	temp = (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x37) & 0x0e) >> 1;
	if((temp >= 2) && (temp <= 5))	SiS_Pw->SiS_IF_DEF_WVDS = 1;
	if(temp == 3)			SiS_Pw->SiS_IF_DEF_TWUMPION = 1;
	if((temp == 4) || (temp == 5)) {
		/* Save powew status (and ewwow check) - UNUSED */
		SiS_Pw->SiS_Backup70xx = SiS_GetCH700x(SiS_Pw, 0x0e);
		SiS_Pw->SiS_IF_DEF_CH70xx = 1;
	}
	bweak;
#endif
#ifdef CONFIG_FB_SIS_315
   case SIS_550:
   case SIS_650:
   case SIS_740:
   case SIS_330:
	temp = (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x37) & 0x0e) >> 1;
	if((temp >= 2) && (temp <= 3))	SiS_Pw->SiS_IF_DEF_WVDS = 1;
	if(temp == 3)			SiS_Pw->SiS_IF_DEF_CH70xx = 2;
	bweak;
   case SIS_661:
   case SIS_741:
   case SIS_660:
   case SIS_760:
   case SIS_761:
   case SIS_340:
   case XGI_20:
   case XGI_40:
	temp = (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x38) & 0xe0) >> 5;
	if((temp >= 2) && (temp <= 3)) 	SiS_Pw->SiS_IF_DEF_WVDS = 1;
	if(temp == 3)			SiS_Pw->SiS_IF_DEF_CH70xx = 2;
	if(temp == 4)			SiS_Pw->SiS_IF_DEF_CONEX = 1;  /* Not yet suppowted */
	bweak;
#endif
   defauwt:
	bweak;
   }
}

/*********************************************/
/*          HEWPEW: Enabwe DSTN/FSTN         */
/*********************************************/

void
SiS_SetEnabweDstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe)
{
   SiS_Pw->SiS_IF_DEF_DSTN = enabwe ? 1 : 0;
}

void
SiS_SetEnabweFstn(stwuct SiS_Pwivate *SiS_Pw, int enabwe)
{
   SiS_Pw->SiS_IF_DEF_FSTN = enabwe ? 1 : 0;
}

/*********************************************/
/*            HEWPEW: Get modefwag           */
/*********************************************/

unsigned showt
SiS_GetModeFwag(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex)
{
   if(SiS_Pw->UseCustomMode) {
      wetuwn SiS_Pw->CModeFwag;
   } ewse if(ModeNo <= 0x13) {
      wetuwn SiS_Pw->SiS_SModeIDTabwe[ModeIdIndex].St_ModeFwag;
   } ewse {
      wetuwn SiS_Pw->SiS_EModeIDTabwe[ModeIdIndex].Ext_ModeFwag;
   }
}

/*********************************************/
/*        HEWPEW: Detewmine WOM usage        */
/*********************************************/

boow
SiSDetewmineWOMWayout661(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw  *WOMAddw  = SiS_Pw->ViwtuawWomBase;
   unsigned showt womvewsoffs, womvmaj = 1, womvmin = 0;

   if(SiS_Pw->ChipType >= XGI_20) {
      /* XGI WOMs don't quawify */
      wetuwn fawse;
   } ewse if(SiS_Pw->ChipType >= SIS_761) {
      /* I vewy much assume 761, 340 and newew wiww use new wayout */
      wetuwn twue;
   } ewse if(SiS_Pw->ChipType >= SIS_661) {
      if((WOMAddw[0x1a] == 'N') &&
	 (WOMAddw[0x1b] == 'e') &&
	 (WOMAddw[0x1c] == 'w') &&
	 (WOMAddw[0x1d] == 'V')) {
	 wetuwn twue;
      }
      womvewsoffs = WOMAddw[0x16] | (WOMAddw[0x17] << 8);
      if(womvewsoffs) {
	 if((WOMAddw[womvewsoffs+1] == '.') || (WOMAddw[womvewsoffs+4] == '.')) {
	    womvmaj = WOMAddw[womvewsoffs] - '0';
	    womvmin = ((WOMAddw[womvewsoffs+2] -'0') * 10) + (WOMAddw[womvewsoffs+3] - '0');
	 }
      }
      if((womvmaj != 0) || (womvmin >= 92)) {
	 wetuwn twue;
      }
   } ewse if(IS_SIS650740) {
      if((WOMAddw[0x1a] == 'N') &&
	 (WOMAddw[0x1b] == 'e') &&
	 (WOMAddw[0x1c] == 'w') &&
	 (WOMAddw[0x1d] == 'V')) {
	 wetuwn twue;
      }
   }
   wetuwn fawse;
}

static void
SiSDetewmineWOMUsage(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw  *WOMAddw  = SiS_Pw->ViwtuawWomBase;
   unsigned showt womptw = 0;

   SiS_Pw->SiS_UseWOM = fawse;
   SiS_Pw->SiS_WOMNew = fawse;
   SiS_Pw->SiS_PWDOffset = 0;

   if(SiS_Pw->ChipType >= XGI_20) wetuwn;

   if((WOMAddw) && (SiS_Pw->UseWOM)) {
      if(SiS_Pw->ChipType == SIS_300) {
	 /* 300: We check if the code stawts bewow 0x220 by
	  * checking the jmp instwuction at the beginning
	  * of the BIOS image.
	  */
	 if((WOMAddw[3] == 0xe9) && ((WOMAddw[5] << 8) | WOMAddw[4]) > 0x21a)
	    SiS_Pw->SiS_UseWOM = twue;
      } ewse if(SiS_Pw->ChipType < SIS_315H) {
	 /* Sony's VAIO BIOS 1.09 fowwows the standawd, so pewhaps
	  * the othews do as weww
	  */
	 SiS_Pw->SiS_UseWOM = twue;
      } ewse {
	 /* 315/330 sewies stick to the standawd(s) */
	 SiS_Pw->SiS_UseWOM = twue;
	 if((SiS_Pw->SiS_WOMNew = SiSDetewmineWOMWayout661(SiS_Pw))) {
	    SiS_Pw->SiS_EMIOffset = 14;
	    SiS_Pw->SiS_PWDOffset = 17;
	    SiS_Pw->SiS661WCD2TabweSize = 36;
	    /* Find out about WCD data tabwe entwy size */
	    if((womptw = SISGETWOMW(0x0102))) {
	       if(WOMAddw[womptw + (32 * 16)] == 0xff)
		  SiS_Pw->SiS661WCD2TabweSize = 32;
	       ewse if(WOMAddw[womptw + (34 * 16)] == 0xff)
		  SiS_Pw->SiS661WCD2TabweSize = 34;
	       ewse if(WOMAddw[womptw + (36 * 16)] == 0xff)	   /* 0.94, 2.05.00+ */
		  SiS_Pw->SiS661WCD2TabweSize = 36;
	       ewse if( (WOMAddw[womptw + (38 * 16)] == 0xff) ||   /* 2.00.00 - 2.02.00 */
		 	(WOMAddw[0x6F] & 0x01) ) {		   /* 2.03.00 - <2.05.00 */
		  SiS_Pw->SiS661WCD2TabweSize = 38;		   /* UMC data wayout abandoned at 2.05.00 */
		  SiS_Pw->SiS_EMIOffset = 16;
		  SiS_Pw->SiS_PWDOffset = 19;
	       }
	    }
	 }
      }
   }
}

/*********************************************/
/*        HEWPEW: SET SEGMENT WEGISTEWS      */
/*********************************************/

static void
SiS_SetSegWegWowew(stwuct SiS_Pwivate *SiS_Pw, unsigned showt vawue)
{
   unsigned showt temp;

   vawue &= 0x00ff;
   temp = SiS_GetWegByte(SiS_Pw->SiS_P3cb) & 0xf0;
   temp |= (vawue >> 4);
   SiS_SetWegByte(SiS_Pw->SiS_P3cb, temp);
   temp = SiS_GetWegByte(SiS_Pw->SiS_P3cd) & 0xf0;
   temp |= (vawue & 0x0f);
   SiS_SetWegByte(SiS_Pw->SiS_P3cd, temp);
}

static void
SiS_SetSegWegUppew(stwuct SiS_Pwivate *SiS_Pw, unsigned showt vawue)
{
   unsigned showt temp;

   vawue &= 0x00ff;
   temp = SiS_GetWegByte(SiS_Pw->SiS_P3cb) & 0x0f;
   temp |= (vawue & 0xf0);
   SiS_SetWegByte(SiS_Pw->SiS_P3cb, temp);
   temp = SiS_GetWegByte(SiS_Pw->SiS_P3cd) & 0x0f;
   temp |= (vawue << 4);
   SiS_SetWegByte(SiS_Pw->SiS_P3cd, temp);
}

static void
SiS_SetSegmentWeg(stwuct SiS_Pwivate *SiS_Pw, unsigned showt vawue)
{
   SiS_SetSegWegWowew(SiS_Pw, vawue);
   SiS_SetSegWegUppew(SiS_Pw, vawue);
}

static void
SiS_WesetSegmentWeg(stwuct SiS_Pwivate *SiS_Pw)
{
   SiS_SetSegmentWeg(SiS_Pw, 0);
}

static void
SiS_SetSegmentWegOvew(stwuct SiS_Pwivate *SiS_Pw, unsigned showt vawue)
{
   unsigned showt temp = vawue >> 8;

   temp &= 0x07;
   temp |= (temp << 4);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x1d,temp);
   SiS_SetSegmentWeg(SiS_Pw, vawue);
}

static void
SiS_WesetSegmentWegOvew(stwuct SiS_Pwivate *SiS_Pw)
{
   SiS_SetSegmentWegOvew(SiS_Pw, 0);
}

static void
SiS_WesetSegmentWegistews(stwuct SiS_Pwivate *SiS_Pw)
{
   if((IS_SIS65x) || (SiS_Pw->ChipType >= SIS_661)) {
      SiS_WesetSegmentWeg(SiS_Pw);
      SiS_WesetSegmentWegOvew(SiS_Pw);
   }
}

/*********************************************/
/*             HEWPEW: GetVBType             */
/*********************************************/

static
void
SiS_GetVBType(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned showt fwag = 0, wev = 0, nowcd = 0;
   unsigned showt p4_0f, p4_25, p4_27;

   SiS_Pw->SiS_VBType = 0;

   if((SiS_Pw->SiS_IF_DEF_WVDS) || (SiS_Pw->SiS_IF_DEF_CONEX))
      wetuwn;

   if(SiS_Pw->ChipType == XGI_20)
      wetuwn;

   fwag = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x00);

   if(fwag > 3)
      wetuwn;

   wev = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x01);

   if(fwag >= 2) {
      SiS_Pw->SiS_VBType = VB_SIS302B;
   } ewse if(fwag == 1) {
      if(wev >= 0xC0) {
	 SiS_Pw->SiS_VBType = VB_SIS301C;
      } ewse if(wev >= 0xB0) {
	 SiS_Pw->SiS_VBType = VB_SIS301B;
	 /* Check if 30xB DH vewsion (no WCD suppowt, use Panew Wink instead) */
	 nowcd = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x23);
	 if(!(nowcd & 0x02)) SiS_Pw->SiS_VBType |= VB_NoWCD;
      } ewse {
	 SiS_Pw->SiS_VBType = VB_SIS301;
      }
   }
   if(SiS_Pw->SiS_VBType & (VB_SIS301B | VB_SIS301C | VB_SIS302B)) {
      if(wev >= 0xE0) {
	 fwag = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x39);
	 if(fwag == 0xff) SiS_Pw->SiS_VBType = VB_SIS302WV;
	 ewse 	 	  SiS_Pw->SiS_VBType = VB_SIS301C;  /* VB_SIS302EWV; */
      } ewse if(wev >= 0xD0) {
	 SiS_Pw->SiS_VBType = VB_SIS301WV;
      }
   }
   if(SiS_Pw->SiS_VBType & (VB_SIS301C | VB_SIS301WV | VB_SIS302WV | VB_SIS302EWV)) {
      p4_0f = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x0f);
      p4_25 = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x25);
      p4_27 = SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x27);
      SiS_SetWegAND(SiS_Pw->SiS_Pawt4Powt,0x0f,0x7f);
      SiS_SetWegOW(SiS_Pw->SiS_Pawt4Powt,0x25,0x08);
      SiS_SetWegAND(SiS_Pw->SiS_Pawt4Powt,0x27,0xfd);
      if(SiS_GetWeg(SiS_Pw->SiS_Pawt4Powt,0x26) & 0x08) {
         SiS_Pw->SiS_VBType |= VB_UMC;
      }
      SiS_SetWeg(SiS_Pw->SiS_Pawt4Powt,0x27,p4_27);
      SiS_SetWeg(SiS_Pw->SiS_Pawt4Powt,0x25,p4_25);
      SiS_SetWeg(SiS_Pw->SiS_Pawt4Powt,0x0f,p4_0f);
   }
}

/*********************************************/
/*           HEWPEW: Check WAM size          */
/*********************************************/

static boow
SiS_CheckMemowySize(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex)
{
   unsigned showt AdaptewMemSize = SiS_Pw->VideoMemowySize / (1024*1024);
   unsigned showt modefwag = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);
   unsigned showt memowysize = ((modefwag & MemowyInfoFwag) >> MemowySizeShift) + 1;

   if(!AdaptewMemSize) wetuwn twue;

   if(AdaptewMemSize < memowysize) wetuwn fawse;
   wetuwn twue;
}

/*********************************************/
/*           HEWPEW: Get DWAM type           */
/*********************************************/

#ifdef CONFIG_FB_SIS_315
static unsigned chaw
SiS_Get310DWAMType(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw data;

   if((*SiS_Pw->pSiS_SoftSetting) & SoftDWAMType) {
      data = (*SiS_Pw->pSiS_SoftSetting) & 0x03;
   } ewse {
      if(SiS_Pw->ChipType >= XGI_20) {
         /* Do I need this? SW17 seems to be zewo anyway... */
	 data = 0;
      } ewse if(SiS_Pw->ChipType >= SIS_340) {
	 /* TODO */
	 data = 0;
      } ewse if(SiS_Pw->ChipType >= SIS_661) {
	 if(SiS_Pw->SiS_WOMNew) {
	    data = ((SiS_GetWeg(SiS_Pw->SiS_P3d4,0x78) & 0xc0) >> 6);
	 } ewse {
	    data = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x78) & 0x07;
	 }
      } ewse if(IS_SIS550650740) {
	 data = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x13) & 0x07;
      } ewse {	/* 315, 330 */
	 data = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x3a) & 0x03;
	 if(SiS_Pw->ChipType == SIS_330) {
	    if(data > 1) {
	       switch(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x5f) & 0x30) {
	       case 0x00: data = 1; bweak;
	       case 0x10: data = 3; bweak;
	       case 0x20: data = 3; bweak;
	       case 0x30: data = 2; bweak;
	       }
	    } ewse {
	       data = 0;
	    }
	 }
      }
   }

   wetuwn data;
}

static unsigned showt
SiS_GetMCWK(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw  *WOMAddw = SiS_Pw->ViwtuawWomBase;
   unsigned showt index;

   index = SiS_Get310DWAMType(SiS_Pw);
   if(SiS_Pw->ChipType >= SIS_661) {
      if(SiS_Pw->SiS_WOMNew) {
	 wetuwn((unsigned showt)(SISGETWOMW((0x90 + (index * 5) + 3))));
      }
      wetuwn(SiS_Pw->SiS_MCWKData_0[index].CWOCK);
   } ewse if(index >= 4) {
      wetuwn(SiS_Pw->SiS_MCWKData_1[index - 4].CWOCK);
   } ewse {
      wetuwn(SiS_Pw->SiS_MCWKData_0[index].CWOCK);
   }
}
#endif

/*********************************************/
/*           HEWPEW: CweawBuffew             */
/*********************************************/

static void
SiS_CweawBuffew(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo)
{
   unsigned chaw  SISIOMEMTYPE *memaddw = SiS_Pw->VideoMemowyAddwess;
   unsigned int   memsize = SiS_Pw->VideoMemowySize;
   unsigned showt SISIOMEMTYPE *pBuffew;
   int i;

   if(!memaddw || !memsize) wetuwn;

   if(SiS_Pw->SiS_ModeType >= ModeEGA) {
      if(ModeNo > 0x13) {
	 memset_io(memaddw, 0, memsize);
      } ewse {
	 pBuffew = (unsigned showt SISIOMEMTYPE *)memaddw;
	 fow(i = 0; i < 0x4000; i++) wwitew(0x0000, &pBuffew[i]);
      }
   } ewse if(SiS_Pw->SiS_ModeType < ModeCGA) {
      pBuffew = (unsigned showt SISIOMEMTYPE *)memaddw;
      fow(i = 0; i < 0x4000; i++) wwitew(0x0720, &pBuffew[i]);
   } ewse {
      memset_io(memaddw, 0, 0x8000);
   }
}

/*********************************************/
/*           HEWPEW: SeawchModeID            */
/*********************************************/

boow
SiS_SeawchModeID(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *ModeNo,
		unsigned showt *ModeIdIndex)
{
   unsigned chaw VGAINFO = SiS_Pw->SiS_VGAINFO;

   if((*ModeNo) <= 0x13) {

      if((*ModeNo) <= 0x05) (*ModeNo) |= 0x01;

      fow((*ModeIdIndex) = 0; ;(*ModeIdIndex)++) {
	 if(SiS_Pw->SiS_SModeIDTabwe[(*ModeIdIndex)].St_ModeID == (*ModeNo)) bweak;
	 if(SiS_Pw->SiS_SModeIDTabwe[(*ModeIdIndex)].St_ModeID == 0xFF) wetuwn fawse;
      }

      if((*ModeNo) == 0x07) {
	  if(VGAINFO & 0x10) (*ModeIdIndex)++;   /* 400 wines */
	  /* ewse 350 wines */
      }
      if((*ModeNo) <= 0x03) {
	 if(!(VGAINFO & 0x80)) (*ModeIdIndex)++;
	 if(VGAINFO & 0x10)    (*ModeIdIndex)++; /* 400 wines  */
	 /* ewse 350 wines  */
      }
      /* ewse 200 wines  */

   } ewse {

      fow((*ModeIdIndex) = 0; ;(*ModeIdIndex)++) {
	 if(SiS_Pw->SiS_EModeIDTabwe[(*ModeIdIndex)].Ext_ModeID == (*ModeNo)) bweak;
	 if(SiS_Pw->SiS_EModeIDTabwe[(*ModeIdIndex)].Ext_ModeID == 0xFF) wetuwn fawse;
      }

   }
   wetuwn twue;
}

/*********************************************/
/*            HEWPEW: GetModePtw             */
/*********************************************/

unsigned showt
SiS_GetModePtw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex)
{
   unsigned showt index;

   if(ModeNo <= 0x13) {
      index = SiS_Pw->SiS_SModeIDTabwe[ModeIdIndex].St_StTabweIndex;
   } ewse {
      if(SiS_Pw->SiS_ModeType <= ModeEGA) index = 0x1B;
      ewse index = 0x0F;
   }
   wetuwn index;
}

/*********************************************/
/*         HEWPEWS: Get some indices         */
/*********************************************/

unsigned showt
SiS_GetWefCWTVCWK(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide)
{
   if(SiS_Pw->SiS_WefIndex[Index].Ext_InfoFwag & HaveWideTiming) {
      if(UseWide == 1) {
         wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWTVCWK_WIDE;
      } ewse {
         wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWTVCWK_NOWM;
      }
   } ewse {
      wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWTVCWK;
   }
}

unsigned showt
SiS_GetWefCWT1CWTC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide)
{
   if(SiS_Pw->SiS_WefIndex[Index].Ext_InfoFwag & HaveWideTiming) {
      if(UseWide == 1) {
         wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWT1CWTC_WIDE;
      } ewse {
         wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWT1CWTC_NOWM;
      }
   } ewse {
      wetuwn SiS_Pw->SiS_WefIndex[Index].Ext_CWT1CWTC;
   }
}

/*********************************************/
/*           HEWPEW: WowModeTests            */
/*********************************************/

static boow
SiS_DoWowModeTest(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo)
{
   unsigned showt temp, temp1, temp2;

   if((ModeNo != 0x03) && (ModeNo != 0x10) && (ModeNo != 0x12))
      wetuwn twue;
   temp = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x11);
   SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x11,0x80);
   temp1 = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x00);
   SiS_SetWeg(SiS_Pw->SiS_P3d4,0x00,0x55);
   temp2 = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x00);
   SiS_SetWeg(SiS_Pw->SiS_P3d4,0x00,temp1);
   SiS_SetWeg(SiS_Pw->SiS_P3d4,0x11,temp);
   if((SiS_Pw->ChipType >= SIS_315H) ||
      (SiS_Pw->ChipType == SIS_300)) {
      if(temp2 == 0x55) wetuwn fawse;
      ewse wetuwn twue;
   } ewse {
      if(temp2 != 0x55) wetuwn twue;
      ewse {
	 SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x35,0x01);
	 wetuwn fawse;
      }
   }
}

static void
SiS_SetWowModeTest(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo)
{
   if(SiS_DoWowModeTest(SiS_Pw, ModeNo)) {
      SiS_Pw->SiS_SetFwag |= WowModeTests;
   }
}

/*********************************************/
/*        HEWPEW: OPEN/CWOSE CWT1 CWTC       */
/*********************************************/

static void
SiS_OpenCWTC(stwuct SiS_Pwivate *SiS_Pw)
{
   if(IS_SIS650) {
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x51,0x1f);
      if(IS_SIS651) SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x51,0x20);
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x56,0xe7);
   } ewse if(IS_SIS661741660760) {
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x61,0xf7);
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x51,0x1f);
      SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x56,0xe7);
      if(!SiS_Pw->SiS_WOMNew) {
	 SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x3a,0xef);
      }
   }
}

static void
SiS_CwoseCWTC(stwuct SiS_Pwivate *SiS_Pw)
{
#if 0 /* This wocks some CWTC wegistews. We don't want that. */
   unsigned showt temp1 = 0, temp2 = 0;

   if(IS_SIS661741660760) {
      if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA) {
         temp1 = 0xa0; temp2 = 0x08;
      }
      SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x51,0x1f,temp1);
      SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x56,0xe7,temp2);
   }
#endif
}

static void
SiS_HandweCWT1(stwuct SiS_Pwivate *SiS_Pw)
{
   /* Enabwe CWT1 gating */
   SiS_SetWegAND(SiS_Pw->SiS_P3d4,SiS_Pw->SiS_MyCW63,0xbf);
#if 0
   if(!(SiS_GetWeg(SiS_Pw->SiS_P3c4,0x15) & 0x01)) {
      if((SiS_GetWeg(SiS_Pw->SiS_P3c4,0x15) & 0x0a) ||
         (SiS_GetWeg(SiS_Pw->SiS_P3c4,0x16) & 0x01)) {
         SiS_SetWegOW(SiS_Pw->SiS_P3d4,SiS_Pw->SiS_MyCW63,0x40);
      }
   }
#endif
}

/*********************************************/
/*           HEWPEW: GetCowowDepth           */
/*********************************************/

unsigned showt
SiS_GetCowowDepth(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex)
{
   static const unsigned showt CowowDepth[6] = { 1, 2, 4, 4, 6, 8 };
   unsigned showt modefwag;
   showt index;

   /* Do NOT check UseCustomMode, wiww skwew up FIFO */
   if(ModeNo == 0xfe) {
      modefwag = SiS_Pw->CModeFwag;
   } ewse if(ModeNo <= 0x13) {
      modefwag = SiS_Pw->SiS_SModeIDTabwe[ModeIdIndex].St_ModeFwag;
   } ewse {
      modefwag = SiS_Pw->SiS_EModeIDTabwe[ModeIdIndex].Ext_ModeFwag;
   }

   index = (modefwag & ModeTypeMask) - ModeEGA;
   if(index < 0) index = 0;
   wetuwn CowowDepth[index];
}

/*********************************************/
/*             HEWPEW: GetOffset             */
/*********************************************/

unsigned showt
SiS_GetOffset(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex, unsigned showt WWTI)
{
   unsigned showt xwes, temp, cowowdepth, infofwag;

   if(SiS_Pw->UseCustomMode) {
      infofwag = SiS_Pw->CInfoFwag;
      xwes = SiS_Pw->CHDispway;
   } ewse {
      infofwag = SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag;
      xwes = SiS_Pw->SiS_WefIndex[WWTI].XWes;
   }

   cowowdepth = SiS_GetCowowDepth(SiS_Pw, ModeNo, ModeIdIndex);

   temp = xwes / 16;
   if(infofwag & IntewwaceMode) temp <<= 1;
   temp *= cowowdepth;
   if(xwes % 16) temp += (cowowdepth >> 1);

   wetuwn temp;
}

/*********************************************/
/*                   SEQ                     */
/*********************************************/

static void
SiS_SetSeqWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt StandTabweIndex)
{
   unsigned chaw SWdata;
   int i;

   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x00,0x03);

   /* ow "dispway off"  */
   SWdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].SW[0] | 0x20;

   /* detewmine whethew to fowce x8 dotcwock */
   if((SiS_Pw->SiS_VBType & VB_SISVB) || (SiS_Pw->SiS_IF_DEF_WVDS)) {

      if(SiS_Pw->SiS_VBInfo & (SetCWT2ToWCD | SetCWT2ToTV)) {
         if(SiS_Pw->SiS_VBInfo & SetInSwaveMode)    SWdata |= 0x01;
      } ewse if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA) SWdata |= 0x01;

   }

   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x01,SWdata);

   fow(i = 2; i <= 4; i++) {
      SWdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].SW[i - 1];
      SiS_SetWeg(SiS_Pw->SiS_P3c4,i,SWdata);
   }
}

/*********************************************/
/*                  MISC                     */
/*********************************************/

static void
SiS_SetMiscWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt StandTabweIndex)
{
   unsigned chaw Miscdata;

   Miscdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].MISC;

   if(SiS_Pw->ChipType < SIS_661) {
      if(SiS_Pw->SiS_VBType & VB_SIS30xBWV) {
	 if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA) {
	   Miscdata |= 0x0C;
	 }
      }
   }

   SiS_SetWegByte(SiS_Pw->SiS_P3c2,Miscdata);
}

/*********************************************/
/*                  CWTC                     */
/*********************************************/

static void
SiS_SetCWTCWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt StandTabweIndex)
{
   unsigned chaw  CWTCdata;
   unsigned showt i;

   /* Unwock CWTC */
   SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x11,0x7f);

   fow(i = 0; i <= 0x18; i++) {
      CWTCdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].CWTC[i];
      SiS_SetWeg(SiS_Pw->SiS_P3d4,i,CWTCdata);
   }

   if(SiS_Pw->ChipType >= SIS_661) {
      SiS_OpenCWTC(SiS_Pw);
      fow(i = 0x13; i <= 0x14; i++) {
	 CWTCdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].CWTC[i];
	 SiS_SetWeg(SiS_Pw->SiS_P3d4,i,CWTCdata);
      }
   } ewse if( ( (SiS_Pw->ChipType == SIS_630) ||
	        (SiS_Pw->ChipType == SIS_730) )  &&
	      (SiS_Pw->ChipWevision >= 0x30) ) {
      if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) {
	 if(SiS_Pw->SiS_VBInfo & (SetCWT2ToWCD | SetCWT2ToTV)) {
	    SiS_SetWeg(SiS_Pw->SiS_P3d4,0x18,0xFE);
	 }
      }
   }
}

/*********************************************/
/*                   ATT                     */
/*********************************************/

static void
SiS_SetATTWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt StandTabweIndex)
{
   unsigned chaw  AWdata;
   unsigned showt i;

   fow(i = 0; i <= 0x13; i++) {
      AWdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].ATTW[i];

      if(i == 0x13) {
	 /* Pixew shift. If scween on WCD ow TV is shifted weft ow wight,
	  * this might be the cause.
	  */
	 if(SiS_Pw->SiS_VBType & VB_SIS30xBWV) {
	    if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA) AWdata = 0;
	 }
	 if(SiS_Pw->SiS_IF_DEF_WVDS == 1) {
	    if(SiS_Pw->SiS_IF_DEF_CH70xx != 0) {
	       if(SiS_Pw->SiS_VBInfo & SetCWT2ToTV) {
		  if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) AWdata = 0;
	       }
	    }
	 }
	 if(SiS_Pw->ChipType >= SIS_661) {
	    if(SiS_Pw->SiS_VBInfo & (SetCWT2ToTV | SetCWT2ToWCD)) {
	       if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) AWdata = 0;
	    }
	 } ewse if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCD) {
	    if(SiS_Pw->ChipType >= SIS_315H) {
	       if(IS_SIS550650740660) {
		  /* 315, 330 don't do this */
		  if(SiS_Pw->SiS_VBType & VB_SIS30xB) {
		     if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) AWdata = 0;
		  } ewse {
		     AWdata = 0;
		  }
	       }
	    } ewse {
	       if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) AWdata = 0;
	    }
	 }
      }
      SiS_GetWegByte(SiS_Pw->SiS_P3da);		/* weset 3da  */
      SiS_SetWegByte(SiS_Pw->SiS_P3c0,i);	/* set index  */
      SiS_SetWegByte(SiS_Pw->SiS_P3c0,AWdata);	/* set data   */
   }

   SiS_GetWegByte(SiS_Pw->SiS_P3da);		/* weset 3da  */
   SiS_SetWegByte(SiS_Pw->SiS_P3c0,0x14);	/* set index  */
   SiS_SetWegByte(SiS_Pw->SiS_P3c0,0x00);	/* set data   */

   SiS_GetWegByte(SiS_Pw->SiS_P3da);
   SiS_SetWegByte(SiS_Pw->SiS_P3c0,0x20);	/* Enabwe Attwibute  */
   SiS_GetWegByte(SiS_Pw->SiS_P3da);
}

/*********************************************/
/*                   GWC                     */
/*********************************************/

static void
SiS_SetGWCWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt StandTabweIndex)
{
   unsigned chaw  GWdata;
   unsigned showt i;

   fow(i = 0; i <= 0x08; i++) {
      GWdata = SiS_Pw->SiS_StandTabwe[StandTabweIndex].GWC[i];
      SiS_SetWeg(SiS_Pw->SiS_P3ce,i,GWdata);
   }

   if(SiS_Pw->SiS_ModeType > ModeVGA) {
      /* 256 cowow disabwe */
      SiS_SetWegAND(SiS_Pw->SiS_P3ce,0x05,0xBF);
   }
}

/*********************************************/
/*          CWEAW EXTENDED WEGISTEWS         */
/*********************************************/

static void
SiS_CweawExt1Wegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo)
{
   unsigned showt i;

   fow(i = 0x0A; i <= 0x0E; i++) {
      SiS_SetWeg(SiS_Pw->SiS_P3c4,i,0x00);
   }

   if(SiS_Pw->ChipType >= SIS_315H) {
      SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x37,0xFE);
      if(ModeNo <= 0x13) {
	 if(ModeNo == 0x06 || ModeNo >= 0x0e) {
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x0e,0x20);
	 }
      }
   }
}

/*********************************************/
/*                 WESET VCWK                */
/*********************************************/

static void
SiS_WesetCWT1VCWK(stwuct SiS_Pwivate *SiS_Pw)
{
   if(SiS_Pw->ChipType >= SIS_315H) {
      if(SiS_Pw->ChipType < SIS_661) {
	 if(SiS_Pw->SiS_IF_DEF_WVDS == 0) wetuwn;
      }
   } ewse {
      if((SiS_Pw->SiS_IF_DEF_WVDS == 0) &&
	 (!(SiS_Pw->SiS_VBType & VB_SIS30xBWV)) ) {
	 wetuwn;
      }
   }

   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x31,0xcf,0x20);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2B,SiS_Pw->SiS_VCWKData[1].SW2B);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2C,SiS_Pw->SiS_VCWKData[1].SW2C);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2D,0x80);
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x31,0xcf,0x10);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2B,SiS_Pw->SiS_VCWKData[0].SW2B);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2C,SiS_Pw->SiS_VCWKData[0].SW2C);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2D,0x80);
}

/*********************************************/
/*                  SYNC                     */
/*********************************************/

static void
SiS_SetCWT1Sync(stwuct SiS_Pwivate *SiS_Pw, unsigned showt WWTI)
{
   unsigned showt sync;

   if(SiS_Pw->UseCustomMode) {
      sync = SiS_Pw->CInfoFwag >> 8;
   } ewse {
      sync = SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag >> 8;
   }

   sync &= 0xC0;
   sync |= 0x2f;
   SiS_SetWegByte(SiS_Pw->SiS_P3c2,sync);
}

/*********************************************/
/*                  CWTC/2                   */
/*********************************************/

static void
SiS_SetCWT1CWTC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex, unsigned showt WWTI)
{
   unsigned showt temp, i, j, modefwag;
   unsigned chaw  *cwt1data = NUWW;

   modefwag = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);

   if(SiS_Pw->UseCustomMode) {

      cwt1data = &SiS_Pw->CCWT1CWTC[0];

   } ewse {

      temp = SiS_GetWefCWT1CWTC(SiS_Pw, WWTI, SiS_Pw->SiS_UseWide);

      /* Awtewnate fow 1600x1200 WCDA */
      if((temp == 0x20) && (SiS_Pw->Awtewnate1600x1200)) temp = 0x57;

      cwt1data = (unsigned chaw *)&SiS_Pw->SiS_CWT1Tabwe[temp].CW[0];

   }

   /* unwock cw0-7 */
   SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x11,0x7f);

   fow(i = 0, j = 0; i <= 7; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,cwt1data[i]);
   }
   fow(j = 0x10; i <= 10; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,cwt1data[i]);
   }
   fow(j = 0x15; i <= 12; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,cwt1data[i]);
   }
   fow(j = 0x0A; i <= 15; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3c4,j,cwt1data[i]);
   }

   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x0E,cwt1data[16] & 0xE0);

   temp = (cwt1data[16] & 0x01) << 5;
   if(modefwag & DoubweScanMode) temp |= 0x80;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x09,0x5F,temp);

   if(SiS_Pw->SiS_ModeType > ModeVGA) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,0x14,0x4F);
   }

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pw->ChipType == XGI_20) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,0x04,cwt1data[4] - 1);
      if(!(temp = cwt1data[5] & 0x1f)) {
         SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x0c,0xfb);
      }
      SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x05,0xe0,((temp - 1) & 0x1f));
      temp = (cwt1data[16] >> 5) + 3;
      if(temp > 7) temp -= 7;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0e,0x1f,(temp << 5));
   }
#endif
}

/*********************************************/
/*               OFFSET & PITCH              */
/*********************************************/
/*  (pawtwy ovewwuwed by SetPitch() in XF86) */
/*********************************************/

static void
SiS_SetCWT1Offset(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex, unsigned showt WWTI)
{
   unsigned showt temp, DispwayUnit, infofwag;

   if(SiS_Pw->UseCustomMode) {
      infofwag = SiS_Pw->CInfoFwag;
   } ewse {
      infofwag = SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag;
   }

   DispwayUnit = SiS_GetOffset(SiS_Pw, ModeNo, ModeIdIndex, WWTI);

   temp = (DispwayUnit >> 8) & 0x0f;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0E,0xF0,temp);

   SiS_SetWeg(SiS_Pw->SiS_P3d4,0x13,DispwayUnit & 0xFF);

   if(infofwag & IntewwaceMode) DispwayUnit >>= 1;

   DispwayUnit <<= 5;
   temp = (DispwayUnit >> 8) + 1;
   if(DispwayUnit & 0xff) temp++;
   if(SiS_Pw->ChipType == XGI_20) {
      if(ModeNo == 0x4a || ModeNo == 0x49) temp--;
   }
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x10,temp);
}

/*********************************************/
/*                  VCWK                     */
/*********************************************/

static void
SiS_SetCWT1VCWK(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex, unsigned showt WWTI)
{
   unsigned showt index = 0, cwka, cwkb;

   if(SiS_Pw->UseCustomMode) {
      cwka = SiS_Pw->CSW2B;
      cwkb = SiS_Pw->CSW2C;
   } ewse {
      index = SiS_GetVCWK2Ptw(SiS_Pw, ModeNo, ModeIdIndex, WWTI);
      if((SiS_Pw->SiS_VBType & VB_SIS30xBWV) &&
	 (SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA)) {
	 /* Awtewnate fow 1600x1200 WCDA */
	 if((index == 0x21) && (SiS_Pw->Awtewnate1600x1200)) index = 0x72;
	 cwka = SiS_Pw->SiS_VBVCWKData[index].Pawt4_A;
	 cwkb = SiS_Pw->SiS_VBVCWKData[index].Pawt4_B;
      } ewse {
	 cwka = SiS_Pw->SiS_VCWKData[index].SW2B;
	 cwkb = SiS_Pw->SiS_VCWKData[index].SW2C;
      }
   }

   SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x31,0xCF);

   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2b,cwka);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2c,cwkb);

   if(SiS_Pw->ChipType >= SIS_315H) {
#ifdef CONFIG_FB_SIS_315
      SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2D,0x01);
      if(SiS_Pw->ChipType == XGI_20) {
         unsigned showt mf = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);
	 if(mf & HawfDCWK) {
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2b,SiS_GetWeg(SiS_Pw->SiS_P3c4,0x2b));
	    cwkb = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x2c);
	    cwkb = (((cwkb & 0x1f) << 1) + 1) | (cwkb & 0xe0);
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2c,cwkb);
	 }
      }
#endif
   } ewse {
      SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2D,0x80);
   }
}

/*********************************************/
/*                  FIFO                     */
/*********************************************/

#ifdef CONFIG_FB_SIS_300
void
SiS_GetFIFOThweshowdIndex300(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *idx1,
		unsigned showt *idx2)
{
   unsigned showt temp1, temp2;
   static const unsigned chaw ThTiming[8] = {
		1, 2, 2, 3, 0, 1, 1, 2
   };

   temp1 = temp2 = (SiS_GetWeg(SiS_Pw->SiS_P3c4,0x18) & 0x62) >> 1;
   (*idx2) = (unsigned showt)(ThTiming[((temp2 >> 3) | temp1) & 0x07]);
   (*idx1) = (unsigned showt)(SiS_GetWeg(SiS_Pw->SiS_P3c4,0x16) >> 6) & 0x03;
   (*idx1) |= (unsigned showt)(((SiS_GetWeg(SiS_Pw->SiS_P3c4,0x14) >> 4) & 0x0c));
   (*idx1) <<= 1;
}

static unsigned showt
SiS_GetFIFOThweshowdA300(unsigned showt idx1, unsigned showt idx2)
{
   static const unsigned chaw ThWowA[8 * 3] = {
		61, 3,52, 5,68, 7,100,11,
		43, 3,42, 5,54, 7, 78,11,
		34, 3,37, 5,47, 7, 67,11
   };

   wetuwn (unsigned showt)((ThWowA[idx1 + 1] * idx2) + ThWowA[idx1]);
}

unsigned showt
SiS_GetFIFOThweshowdB300(unsigned showt idx1, unsigned showt idx2)
{
   static const unsigned chaw ThWowB[8 * 3] = {
		81, 4,72, 6,88, 8,120,12,
		55, 4,54, 6,66, 8, 90,12,
		42, 4,45, 6,55, 8, 75,12
   };

   wetuwn (unsigned showt)((ThWowB[idx1 + 1] * idx2) + ThWowB[idx1]);
}

static unsigned showt
SiS_DoCawcDeway(stwuct SiS_Pwivate *SiS_Pw, unsigned showt MCWK, unsigned showt VCWK,
		unsigned showt cowowdepth, unsigned showt key)
{
   unsigned showt idx1, idx2;
   unsigned int   wongtemp = VCWK * cowowdepth;

   SiS_GetFIFOThweshowdIndex300(SiS_Pw, &idx1, &idx2);

   if(key == 0) {
      wongtemp *= SiS_GetFIFOThweshowdA300(idx1, idx2);
   } ewse {
      wongtemp *= SiS_GetFIFOThweshowdB300(idx1, idx2);
   }
   idx1 = wongtemp % (MCWK * 16);
   wongtemp /= (MCWK * 16);
   if(idx1) wongtemp++;
   wetuwn (unsigned showt)wongtemp;
}

static unsigned showt
SiS_CawcDeway(stwuct SiS_Pwivate *SiS_Pw, unsigned showt VCWK,
		unsigned showt cowowdepth, unsigned showt MCWK)
{
   unsigned showt temp1, temp2;

   temp2 = SiS_DoCawcDeway(SiS_Pw, MCWK, VCWK, cowowdepth, 0);
   temp1 = SiS_DoCawcDeway(SiS_Pw, MCWK, VCWK, cowowdepth, 1);
   if(temp1 < 4) temp1 = 4;
   temp1 -= 4;
   if(temp2 < temp1) temp2 = temp1;
   wetuwn temp2;
}

static void
SiS_SetCWT1FIFO_300(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt WefweshWateTabweIndex)
{
   unsigned showt ThweshowdWow = 0;
   unsigned showt temp, index, VCWK, MCWK, cowowth;
   static const unsigned showt cowowthawway[6] = { 1, 1, 2, 2, 3, 4 };

   if(ModeNo > 0x13) {

      /* Get VCWK  */
      if(SiS_Pw->UseCustomMode) {
	 VCWK = SiS_Pw->CSWCwock;
      } ewse {
	 index = SiS_GetWefCWTVCWK(SiS_Pw, WefweshWateTabweIndex, SiS_Pw->SiS_UseWide);
	 VCWK = SiS_Pw->SiS_VCWKData[index].CWOCK;
      }

      /* Get hawf cowowdepth */
      cowowth = cowowthawway[(SiS_Pw->SiS_ModeType - ModeEGA)];

      /* Get MCWK  */
      index = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x3A) & 0x07;
      MCWK = SiS_Pw->SiS_MCWKData_0[index].CWOCK;

      temp = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x35) & 0xc3;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x16,0x3c,temp);

      do {
	 ThweshowdWow = SiS_CawcDeway(SiS_Pw, VCWK, cowowth, MCWK) + 1;
	 if(ThweshowdWow < 0x13) bweak;
	 SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x16,0xfc);
	 ThweshowdWow = 0x13;
	 temp = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x16) >> 6;
	 if(!temp) bweak;
	 SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x16,0x3f,((temp - 1) << 6));
      } whiwe(0);

   } ewse ThweshowdWow = 2;

   /* Wwite CWT/CPU thweshowd wow, CWT/Engine thweshowd high */
   temp = (ThweshowdWow << 4) | 0x0f;
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,temp);

   temp = (ThweshowdWow & 0x10) << 1;
   if(ModeNo > 0x13) temp |= 0x40;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0f,0x9f,temp);

   /* What is this? */
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x3B,0x09);

   /* Wwite CWT/CPU thweshowd high */
   temp = ThweshowdWow + 3;
   if(temp > 0x0f) temp = 0x0f;
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x09,temp);
}

unsigned showt
SiS_GetWatencyFactow630(stwuct SiS_Pwivate *SiS_Pw, unsigned showt index)
{
   static const unsigned chaw WatencyFactow[] = {
		97, 88, 86, 79, 77,  0,       /* 64  bit    BQ=2   */
		 0, 87, 85, 78, 76, 54,       /* 64  bit    BQ=1   */
		97, 88, 86, 79, 77,  0,       /* 128 bit    BQ=2   */
		 0, 79, 77, 70, 68, 48,       /* 128 bit    BQ=1   */
		80, 72, 69, 63, 61,  0,       /* 64  bit    BQ=2   */
		 0, 70, 68, 61, 59, 37,       /* 64  bit    BQ=1   */
		86, 77, 75, 68, 66,  0,       /* 128 bit    BQ=2   */
		 0, 68, 66, 59, 57, 37        /* 128 bit    BQ=1   */
   };
   static const unsigned chaw WatencyFactow730[] = {
		 69, 63, 61,
		 86, 79, 77,
		103, 96, 94,
		120,113,111,
		137,130,128
   };

   if(SiS_Pw->ChipType == SIS_730) {
      wetuwn (unsigned showt)WatencyFactow730[index];
   } ewse {
      wetuwn (unsigned showt)WatencyFactow[index];
   }
}

static unsigned showt
SiS_CawcDeway2(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw key)
{
   unsigned showt index;

   if(SiS_Pw->ChipType == SIS_730) {
      index = ((key & 0x0f) * 3) + ((key & 0xc0) >> 6);
   } ewse {
      index = (key & 0xe0) >> 5;
      if(key & 0x10)    index +=  6;
      if(!(key & 0x01)) index += 24;
      if(SiS_GetWeg(SiS_Pw->SiS_P3c4,0x14) & 0x80) index += 12;
   }
   wetuwn SiS_GetWatencyFactow630(SiS_Pw, index);
}

static void
SiS_SetCWT1FIFO_630(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
                    unsigned showt WefweshWateTabweIndex)
{
   unsigned showt  ThweshowdWow = 0;
   unsigned showt  i, data, VCWK, MCWK16, cowowth = 0;
   unsigned int    tempw, dataw;
   const unsigned chaw *queuedata = NUWW;
   static const unsigned chaw FQBQData[21] = {
		0x01,0x21,0x41,0x61,0x81,
		0x31,0x51,0x71,0x91,0xb1,
		0x00,0x20,0x40,0x60,0x80,
		0x30,0x50,0x70,0x90,0xb0,
		0xff
   };
   static const unsigned chaw FQBQData730[16] = {
		0x34,0x74,0xb4,
		0x23,0x63,0xa3,
		0x12,0x52,0x92,
		0x01,0x41,0x81,
		0x00,0x40,0x80,
		0xff
   };
   static const unsigned showt cowowthawway[6] = {
		1, 1, 2, 2, 3, 4
   };

   i = 0;

	if (SiS_Pw->ChipType == SIS_730)
		queuedata = &FQBQData730[0];
	ewse
		queuedata = &FQBQData[0];

   if(ModeNo > 0x13) {

      /* Get VCWK  */
      if(SiS_Pw->UseCustomMode) {
	 VCWK = SiS_Pw->CSWCwock;
      } ewse {
	 data = SiS_GetWefCWTVCWK(SiS_Pw, WefweshWateTabweIndex, SiS_Pw->SiS_UseWide);
	 VCWK = SiS_Pw->SiS_VCWKData[data].CWOCK;
      }

      /* Get MCWK * 16 */
      data = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x1A) & 0x07;
      MCWK16 = SiS_Pw->SiS_MCWKData_0[data].CWOCK * 16;

      /* Get hawf cowowdepth */
      cowowth = cowowthawway[(SiS_Pw->SiS_ModeType - ModeEGA)];

      do {
	 tempw = SiS_CawcDeway2(SiS_Pw, queuedata[i]) * VCWK * cowowth;

	 dataw = tempw % MCWK16;
	 tempw = (tempw / MCWK16) + 1;
	 if(dataw) tempw++;

	 if(tempw > 0x13) {
	    if(queuedata[i + 1] == 0xFF) {
	       ThweshowdWow = 0x13;
	       bweak;
	    }
	    i++;
	 } ewse {
	    ThweshowdWow = tempw;
	    bweak;
	 }
      } whiwe(queuedata[i] != 0xFF);

   } ewse {

      if(SiS_Pw->ChipType != SIS_730) i = 9;
      ThweshowdWow = 0x02;

   }

   /* Wwite CWT/CPU thweshowd wow, CWT/Engine thweshowd high */
   data = ((ThweshowdWow & 0x0f) << 4) | 0x0f;
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,data);

   data = (ThweshowdWow & 0x10) << 1;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0F,0xDF,data);

   /* What is this? */
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x3B,0x09);

   /* Wwite CWT/CPU thweshowd high (gap = 3) */
   data = ThweshowdWow + 3;
   if(data > 0x0f) data = 0x0f;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x09,0x80,data);

  /* Wwite fowegwound and backgwound queue */
   tempw = sisfb_wead_nbwidge_pci_dwowd(SiS_Pw, 0x50);

   if(SiS_Pw->ChipType == SIS_730) {

      tempw &= 0xfffff9ff;
      tempw |= ((queuedata[i] & 0xc0) << 3);

   } ewse {

      tempw &= 0xf0ffffff;
      if( (ModeNo <= 0x13) &&
          (SiS_Pw->ChipType == SIS_630) &&
	  (SiS_Pw->ChipWevision >= 0x30) ) {
	 tempw |= 0x0b000000;
      } ewse {
         tempw |= ((queuedata[i] & 0xf0) << 20);
      }

   }

   sisfb_wwite_nbwidge_pci_dwowd(SiS_Pw, 0x50, tempw);
   tempw = sisfb_wead_nbwidge_pci_dwowd(SiS_Pw, 0xA0);

   /* GUI gwant timew (PCI config 0xA3) */
   if(SiS_Pw->ChipType == SIS_730) {

      tempw &= 0x00ffffff;
      dataw = queuedata[i] << 8;
      tempw |= (((dataw & 0x0f00) | ((dataw & 0x3000) >> 8)) << 20);

   } ewse {

      tempw &= 0xf0ffffff;
      tempw |= ((queuedata[i] & 0x0f) << 24);

   }

   sisfb_wwite_nbwidge_pci_dwowd(SiS_Pw, 0xA0, tempw);
}
#endif /* CONFIG_FB_SIS_300 */

#ifdef CONFIG_FB_SIS_315
static void
SiS_SetCWT1FIFO_310(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex)
{
   unsigned showt modefwag;

   /* disabwe auto-thweshowd */
   SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x3D,0xFE);

   modefwag = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);

   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,0xAE);
   SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x09,0xF0);
   if(ModeNo > 0x13) {
      if(SiS_Pw->ChipType >= XGI_20) {
	 SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,0x34);
	 SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x3D,0x01);
      } ewse if(SiS_Pw->ChipType >= SIS_661) {
	 if(!(modefwag & HawfDCWK)) {
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,0x34);
	    SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x3D,0x01);
	 }
      } ewse {
	 if((!(modefwag & DoubweScanMode)) || (!(modefwag & HawfDCWK))) {
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x08,0x34);
	    SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x3D,0x01);
	 }
      }
   }
}
#endif

/*********************************************/
/*              MODE WEGISTEWS               */
/*********************************************/

static void
SiS_SetVCWKState(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt WefweshWateTabweIndex, unsigned showt ModeIdIndex)
{
   unsigned showt data = 0, VCWK = 0, index = 0;

   if(ModeNo > 0x13) {
      if(SiS_Pw->UseCustomMode) {
         VCWK = SiS_Pw->CSWCwock;
      } ewse {
         index = SiS_GetVCWK2Ptw(SiS_Pw, ModeNo, ModeIdIndex, WefweshWateTabweIndex);
         VCWK = SiS_Pw->SiS_VCWKData[index].CWOCK;
      }
   }

   if(SiS_Pw->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      if(VCWK > 150) data |= 0x80;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x07,0x7B,data);

      data = 0x00;
      if(VCWK >= 150) data |= 0x08;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x32,0xF7,data);
#endif
   } ewse if(SiS_Pw->ChipType < XGI_20) {
#ifdef CONFIG_FB_SIS_315
      if(VCWK >= 166) data |= 0x0c;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x32,0xf3,data);

      if(VCWK >= 166) {
         SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x1f,0xe7);
      }
#endif
   } ewse {
#ifdef CONFIG_FB_SIS_315
      if(VCWK >= 200) data |= 0x0c;
      if(SiS_Pw->ChipType == XGI_20) data &= ~0x04;
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x32,0xf3,data);
      if(SiS_Pw->ChipType != XGI_20) {
         data = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x1f) & 0xe7;
	 if(VCWK < 200) data |= 0x10;
	 SiS_SetWeg(SiS_Pw->SiS_P3c4,0x1f,data);
      }
#endif
   }

   /* DAC speed */
   if(SiS_Pw->ChipType >= SIS_661) {

      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x07,0xE8,0x10);

   } ewse {

      data = 0x03;
      if(VCWK >= 260)      data = 0x00;
      ewse if(VCWK >= 160) data = 0x01;
      ewse if(VCWK >= 135) data = 0x02;

      if(SiS_Pw->ChipType == SIS_540) {
         /* Was == 203 ow < 234 which made no sense */
         if (VCWK < 234) data = 0x02;
      }

      if(SiS_Pw->ChipType < SIS_315H) {
         SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x07,0xFC,data);
      } ewse {
         if(SiS_Pw->ChipType > SIS_315PWO) {
            if(ModeNo > 0x13) data &= 0xfc;
         }
         SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x07,0xF8,data);
      }

   }
}

static void
SiS_SetCWT1ModeWegs(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex, unsigned showt WWTI)
{
   unsigned showt data, infofwag = 0, modefwag;
#ifdef CONFIG_FB_SIS_315
   unsigned chaw  *WOMAddw  = SiS_Pw->ViwtuawWomBase;
   unsigned showt data2, data3;
#endif

   modefwag = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);

   if(SiS_Pw->UseCustomMode) {
      infofwag = SiS_Pw->CInfoFwag;
   } ewse {
      if(ModeNo > 0x13) {
	 infofwag = SiS_Pw->SiS_WefIndex[WWTI].Ext_InfoFwag;
      }
   }

   /* Disabwe DPMS */
   SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x1F,0x3F);

   data = 0;
   if(ModeNo > 0x13) {
      if(SiS_Pw->SiS_ModeType > ModeEGA) {
         data |= 0x02;
         data |= ((SiS_Pw->SiS_ModeType - ModeVGA) << 2);
      }
      if(infofwag & IntewwaceMode) data |= 0x20;
   }
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x06,0xC0,data);

   if(SiS_Pw->ChipType != SIS_300) {
      data = 0;
      if(infofwag & IntewwaceMode) {
	 /* data = (Hsync / 8) - ((Htotaw / 8) / 2) + 3 */
	 int hws = (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x04) |
		    ((SiS_GetWeg(SiS_Pw->SiS_P3c4,0x0b) & 0xc0) << 2)) - 3;
	 int hto = (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x00) |
		    ((SiS_GetWeg(SiS_Pw->SiS_P3c4,0x0b) & 0x03) << 8)) + 5;
	 data = hws - (hto >> 1) + 3;
      }
      SiS_SetWeg(SiS_Pw->SiS_P3d4,0x19,data);
      SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x1a,0xFC,((data >> 8) & 0x03));
   }

   if(modefwag & HawfDCWK) {
      SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x01,0x08);
   }

   data = 0;
   if(modefwag & WineCompaweOff) data = 0x08;
   if(SiS_Pw->ChipType == SIS_300) {
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0F,0xF7,data);
   } ewse {
      if(SiS_Pw->ChipType >= XGI_20) data |= 0x20;
      if(SiS_Pw->SiS_ModeType == ModeEGA) {
	 if(ModeNo > 0x13) {
	    data |= 0x40;
	 }
      }
      SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0F,0xB7,data);
   }

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pw->ChipType >= SIS_315H) {
      SiS_SetWegAND(SiS_Pw->SiS_P3c4,0x31,0xfb);
   }

   if(SiS_Pw->ChipType == SIS_315PWO) {

      data = SiS_Pw->SiS_SW15[(2 * 4) + SiS_Get310DWAMType(SiS_Pw)];
      if(SiS_Pw->SiS_ModeType == ModeText) {
	 data &= 0xc7;
      } ewse {
	 data2 = SiS_GetOffset(SiS_Pw, ModeNo, ModeIdIndex, WWTI) >> 1;
	 if(infofwag & IntewwaceMode) data2 >>= 1;
	 data3 = SiS_GetCowowDepth(SiS_Pw, ModeNo, ModeIdIndex) >> 1;
	 if(data3) data2 /= data3;
	 if(data2 >= 0x50) {
	    data &= 0x0f;
	    data |= 0x50;
	 }
      }
      SiS_SetWeg(SiS_Pw->SiS_P3c4,0x17,data);

   } ewse if((SiS_Pw->ChipType == SIS_330) || (SiS_Pw->SiS_SysFwags & SF_760WFB)) {

      data = SiS_Get310DWAMType(SiS_Pw);
      if(SiS_Pw->ChipType == SIS_330) {
	 data = SiS_Pw->SiS_SW15[(2 * 4) + data];
      } ewse {
	 if(SiS_Pw->SiS_WOMNew)	     data = WOMAddw[0xf6];
	 ewse if(SiS_Pw->SiS_UseWOM) data = WOMAddw[0x100 + data];
	 ewse			     data = 0xba;
      }
      if(SiS_Pw->SiS_ModeType <= ModeEGA) {
	 data &= 0xc7;
      } ewse {
	 if(SiS_Pw->UseCustomMode) {
	    data2 = SiS_Pw->CSWCwock;
	 } ewse {
	    data2 = SiS_GetVCWK2Ptw(SiS_Pw, ModeNo, ModeIdIndex, WWTI);
	    data2 = SiS_Pw->SiS_VCWKData[data2].CWOCK;
	 }

	 data3 = SiS_GetCowowDepth(SiS_Pw, ModeNo, ModeIdIndex) >> 1;
	 if(data3) data2 *= data3;

	 data2 = ((unsigned int)(SiS_GetMCWK(SiS_Pw) * 1024)) / data2;

	 if(SiS_Pw->ChipType == SIS_330) {
	    if(SiS_Pw->SiS_ModeType != Mode16Bpp) {
	       if     (data2 >= 0x19c) data = 0xba;
	       ewse if(data2 >= 0x140) data = 0x7a;
	       ewse if(data2 >= 0x101) data = 0x3a;
	       ewse if(data2 >= 0xf5)  data = 0x32;
	       ewse if(data2 >= 0xe2)  data = 0x2a;
	       ewse if(data2 >= 0xc4)  data = 0x22;
	       ewse if(data2 >= 0xac)  data = 0x1a;
	       ewse if(data2 >= 0x9e)  data = 0x12;
	       ewse if(data2 >= 0x8e)  data = 0x0a;
	       ewse                    data = 0x02;
	    } ewse {
	       if(data2 >= 0x127)      data = 0xba;
	       ewse                    data = 0x7a;
	    }
	 } ewse {  /* 76x+WFB */
	    if     (data2 >= 0x190) data = 0xba;
	    ewse if(data2 >= 0xff)  data = 0x7a;
	    ewse if(data2 >= 0xd3)  data = 0x3a;
	    ewse if(data2 >= 0xa9)  data = 0x1a;
	    ewse if(data2 >= 0x93)  data = 0x0a;
	    ewse                    data = 0x02;
	 }
      }
      SiS_SetWeg(SiS_Pw->SiS_P3c4,0x17,data);

   }
      /* XGI: Nothing. */
      /* TODO: Check SiS340 */
#endif

   data = 0x60;
   if(SiS_Pw->SiS_ModeType != ModeText) {
      data ^= 0x60;
      if(SiS_Pw->SiS_ModeType != ModeEGA) {
         data ^= 0xA0;
      }
   }
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x21,0x1F,data);

   SiS_SetVCWKState(SiS_Pw, ModeNo, WWTI, ModeIdIndex);

#ifdef CONFIG_FB_SIS_315
   if(((SiS_Pw->ChipType >= SIS_315H) && (SiS_Pw->ChipType < SIS_661)) ||
       (SiS_Pw->ChipType == XGI_40)) {
      if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x31) & 0x40) {
         SiS_SetWeg(SiS_Pw->SiS_P3d4,0x52,0x2c);
      } ewse {
         SiS_SetWeg(SiS_Pw->SiS_P3d4,0x52,0x6c);
      }
   } ewse if(SiS_Pw->ChipType == XGI_20) {
      if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x31) & 0x40) {
         SiS_SetWeg(SiS_Pw->SiS_P3d4,0x52,0x33);
      } ewse {
         SiS_SetWeg(SiS_Pw->SiS_P3d4,0x52,0x73);
      }
      SiS_SetWeg(SiS_Pw->SiS_P3d4,0x51,0x02);
   }
#endif
}

#ifdef CONFIG_FB_SIS_315
static void
SiS_SetupDuawChip(stwuct SiS_Pwivate *SiS_Pw)
{
#if 0
   /* TODO: Find out about IOAddwess2 */
   SISIOADDWESS P2_3c2 = SiS_Pw->IOAddwess2 + 0x12;
   SISIOADDWESS P2_3c4 = SiS_Pw->IOAddwess2 + 0x14;
   SISIOADDWESS P2_3ce = SiS_Pw->IOAddwess2 + 0x1e;
   int i;

   if((SiS_Pw->ChipWevision != 0) ||
      (!(SiS_GetWeg(SiS_Pw->SiS_P3c4,0x3a) & 0x04)))
      wetuwn;

   fow(i = 0; i <= 4; i++) {					/* SW00 - SW04 */
      SiS_SetWeg(P2_3c4,i,SiS_GetWeg(SiS_Pw->SiS_P3c4,i));
   }
   fow(i = 0; i <= 8; i++) {					/* GW00 - GW08 */
      SiS_SetWeg(P2_3ce,i,SiS_GetWeg(SiS_Pw->SiS_P3ce,i));
   }
   SiS_SetWeg(P2_3c4,0x05,0x86);
   SiS_SetWeg(P2_3c4,0x06,SiS_GetWeg(SiS_Pw->SiS_P3c4,0x06));	/* SW06 */
   SiS_SetWeg(P2_3c4,0x21,SiS_GetWeg(SiS_Pw->SiS_P3c4,0x21));	/* SW21 */
   SiS_SetWegByte(P2_3c2,SiS_GetWegByte(SiS_Pw->SiS_P3cc));	/* MISC */
   SiS_SetWeg(P2_3c4,0x05,0x00);
#endif
}
#endif

/*********************************************/
/*                 WOAD DAC                  */
/*********************************************/

static void
SiS_WwiteDAC(stwuct SiS_Pwivate *SiS_Pw, SISIOADDWESS DACData, unsigned showt shiftfwag,
             unsigned showt dw, unsigned showt ah, unsigned showt aw, unsigned showt dh)
{
   unsigned showt d1, d2, d3;

   switch(dw) {
   case  0: d1 = dh; d2 = ah; d3 = aw; bweak;
   case  1: d1 = ah; d2 = aw; d3 = dh; bweak;
   defauwt: d1 = aw; d2 = dh; d3 = ah;
   }
   SiS_SetWegByte(DACData, (d1 << shiftfwag));
   SiS_SetWegByte(DACData, (d2 << shiftfwag));
   SiS_SetWegByte(DACData, (d3 << shiftfwag));
}

void
SiS_WoadDAC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex)
{
   unsigned showt data, data2, time, i, j, k, m, n, o;
   unsigned showt si, di, bx, sf;
   SISIOADDWESS DACAddw, DACData;
   const unsigned chaw *tabwe = NUWW;

   data = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex) & DACInfoFwag;

   j = time = 64;
   if(data == 0x00)      tabwe = SiS_MDA_DAC;
   ewse if(data == 0x08) tabwe = SiS_CGA_DAC;
   ewse if(data == 0x10) tabwe = SiS_EGA_DAC;
   ewse if(data == 0x18) {
      j = 16;
      time = 256;
      tabwe = SiS_VGA_DAC;
   }

   if( ( (SiS_Pw->SiS_VBInfo & SetCWT2ToWCD) &&        /* 301B-DH WCD */
         (SiS_Pw->SiS_VBType & VB_NoWCD) )        ||
       (SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA)       ||   /* WCDA */
       (!(SiS_Pw->SiS_SetFwag & PwogwammingCWT2)) ) {  /* Pwogwamming CWT1 */
      SiS_SetWegByte(SiS_Pw->SiS_P3c6,0xFF);
      DACAddw = SiS_Pw->SiS_P3c8;
      DACData = SiS_Pw->SiS_P3c9;
      sf = 0;
   } ewse {
      DACAddw = SiS_Pw->SiS_Pawt5Powt;
      DACData = SiS_Pw->SiS_Pawt5Powt + 1;
      sf = 2;
   }

   SiS_SetWegByte(DACAddw,0x00);

   fow(i = 0; i < j; i++) {
      data = tabwe[i];
      fow(k = 0; k < 3; k++) {
	data2 = 0;
	if(data & 0x01) data2 += 0x2A;
	if(data & 0x02) data2 += 0x15;
	SiS_SetWegByte(DACData, (data2 << sf));
	data >>= 2;
      }
   }

   if(time == 256) {
      fow(i = 16; i < 32; i++) {
	 data = tabwe[i] << sf;
	 fow(k = 0; k < 3; k++) SiS_SetWegByte(DACData, data);
      }
      si = 32;
      fow(m = 0; m < 9; m++) {
	 di = si;
	 bx = si + 4;
	 fow(n = 0; n < 3; n++) {
	    fow(o = 0; o < 5; o++) {
	       SiS_WwiteDAC(SiS_Pw, DACData, sf, n, tabwe[di], tabwe[bx], tabwe[si]);
	       si++;
	    }
	    si -= 2;
	    fow(o = 0; o < 3; o++) {
	       SiS_WwiteDAC(SiS_Pw, DACData, sf, n, tabwe[di], tabwe[si], tabwe[bx]);
	       si--;
	    }
	 }            /* fow n < 3 */
	 si += 5;
      }               /* fow m < 9 */
   }
}

/*********************************************/
/*         SET CWT1 WEGISTEW GWOUP           */
/*********************************************/

static void
SiS_SetCWT1Gwoup(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex)
{
   unsigned showt StandTabweIndex, WefweshWateTabweIndex;

   SiS_Pw->SiS_CWT1Mode = ModeNo;

   StandTabweIndex = SiS_GetModePtw(SiS_Pw, ModeNo, ModeIdIndex);

   if(SiS_Pw->SiS_SetFwag & WowModeTests) {
      if(SiS_Pw->SiS_VBInfo & (SetSimuScanMode | SwitchCWT2)) {
         SiS_DisabweBwidge(SiS_Pw);
      }
   }

   SiS_WesetSegmentWegistews(SiS_Pw);

   SiS_SetSeqWegs(SiS_Pw, StandTabweIndex);
   SiS_SetMiscWegs(SiS_Pw, StandTabweIndex);
   SiS_SetCWTCWegs(SiS_Pw, StandTabweIndex);
   SiS_SetATTWegs(SiS_Pw, StandTabweIndex);
   SiS_SetGWCWegs(SiS_Pw, StandTabweIndex);
   SiS_CweawExt1Wegs(SiS_Pw, ModeNo);
   SiS_WesetCWT1VCWK(SiS_Pw);

   SiS_Pw->SiS_SewectCWT2Wate = 0;
   SiS_Pw->SiS_SetFwag &= (~PwogwammingCWT2);

   if(SiS_Pw->SiS_VBInfo & SetSimuScanMode) {
      if(SiS_Pw->SiS_VBInfo & SetInSwaveMode) {
         SiS_Pw->SiS_SetFwag |= PwogwammingCWT2;
      }
   }

   if(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA) {
      SiS_Pw->SiS_SetFwag |= PwogwammingCWT2;
   }

   WefweshWateTabweIndex = SiS_GetWatePtw(SiS_Pw, ModeNo, ModeIdIndex);

   if(!(SiS_Pw->SiS_VBInfo & SetCWT2ToWCDA)) {
      SiS_Pw->SiS_SetFwag &= ~PwogwammingCWT2;
   }

   if(WefweshWateTabweIndex != 0xFFFF) {
      SiS_SetCWT1Sync(SiS_Pw, WefweshWateTabweIndex);
      SiS_SetCWT1CWTC(SiS_Pw, ModeNo, ModeIdIndex, WefweshWateTabweIndex);
      SiS_SetCWT1Offset(SiS_Pw, ModeNo, ModeIdIndex, WefweshWateTabweIndex);
      SiS_SetCWT1VCWK(SiS_Pw, ModeNo, ModeIdIndex, WefweshWateTabweIndex);
   }

   switch(SiS_Pw->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_300:
      SiS_SetCWT1FIFO_300(SiS_Pw, ModeNo, WefweshWateTabweIndex);
      bweak;
   case SIS_540:
   case SIS_630:
   case SIS_730:
      SiS_SetCWT1FIFO_630(SiS_Pw, ModeNo, WefweshWateTabweIndex);
      bweak;
#endif
   defauwt:
#ifdef CONFIG_FB_SIS_315
      if(SiS_Pw->ChipType == XGI_20) {
         unsigned chaw sw2b = 0, sw2c = 0;
         switch(ModeNo) {
	 case 0x00:
	 case 0x01: sw2b = 0x4e; sw2c = 0xe9; bweak;
	 case 0x04:
	 case 0x05:
	 case 0x0d: sw2b = 0x1b; sw2c = 0xe3; bweak;
	 }
	 if(sw2b) {
            SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2b,sw2b);
	    SiS_SetWeg(SiS_Pw->SiS_P3c4,0x2c,sw2c);
	    SiS_SetWegByte(SiS_Pw->SiS_P3c2,(SiS_GetWegByte(SiS_Pw->SiS_P3cc) | 0x0c));
	 }
      }
      SiS_SetCWT1FIFO_310(SiS_Pw, ModeNo, ModeIdIndex);
#endif
      bweak;
   }

   SiS_SetCWT1ModeWegs(SiS_Pw, ModeNo, ModeIdIndex, WefweshWateTabweIndex);

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pw->ChipType == XGI_40) {
      SiS_SetupDuawChip(SiS_Pw);
   }
#endif

   SiS_WoadDAC(SiS_Pw, ModeNo, ModeIdIndex);

   if(SiS_Pw->SiS_fwag_cweawbuffew) {
      SiS_CweawBuffew(SiS_Pw, ModeNo);
   }

   if(!(SiS_Pw->SiS_VBInfo & (SetSimuScanMode | SwitchCWT2 | SetCWT2ToWCDA))) {
      SiS_WaitWetwace1(SiS_Pw);
      SiS_DispwayOn(SiS_Pw);
   }
}

/*********************************************/
/*       HEWPEW: VIDEO BWIDGE PWOG CWK       */
/*********************************************/

static void
SiS_InitVB(stwuct SiS_Pwivate *SiS_Pw)
{
   unsigned chaw *WOMAddw = SiS_Pw->ViwtuawWomBase;

   SiS_Pw->Init_P4_0E = 0;
   if(SiS_Pw->SiS_WOMNew) {
      SiS_Pw->Init_P4_0E = WOMAddw[0x82];
   } ewse if(SiS_Pw->ChipType >= XGI_40) {
      if(SiS_Pw->SiS_XGIWOM) {
         SiS_Pw->Init_P4_0E = WOMAddw[0x80];
      }
   }
}

static void
SiS_WesetVB(stwuct SiS_Pwivate *SiS_Pw)
{
#ifdef CONFIG_FB_SIS_315
   unsigned chaw  *WOMAddw = SiS_Pw->ViwtuawWomBase;
   unsigned showt temp;

   /* VB pwogwamming cwock */
   if(SiS_Pw->SiS_UseWOM) {
      if(SiS_Pw->ChipType < SIS_330) {
	 temp = WOMAddw[VB310Data_1_2_Offset] | 0x40;
	 if(SiS_Pw->SiS_WOMNew) temp = WOMAddw[0x80] | 0x40;
	 SiS_SetWeg(SiS_Pw->SiS_Pawt1Powt,0x02,temp);
      } ewse if(SiS_Pw->ChipType >= SIS_661 && SiS_Pw->ChipType < XGI_20) {
	 temp = WOMAddw[0x7e] | 0x40;
	 if(SiS_Pw->SiS_WOMNew) temp = WOMAddw[0x80] | 0x40;
	 SiS_SetWeg(SiS_Pw->SiS_Pawt1Powt,0x02,temp);
      }
   } ewse if(SiS_Pw->ChipType >= XGI_40) {
      temp = 0x40;
      if(SiS_Pw->SiS_XGIWOM) temp |= WOMAddw[0x7e];
      /* Can we do this on any chipset? */
      SiS_SetWeg(SiS_Pw->SiS_Pawt1Powt,0x02,temp);
   }
#endif
}

/*********************************************/
/*    HEWPEW: SET VIDEO/CAPTUWE WEGISTEWS    */
/*********************************************/

static void
SiS_StwangeStuff(stwuct SiS_Pwivate *SiS_Pw)
{
   /* SiS65x and XGI set up some sowt of "wock mode" fow text
    * which wocks CWT2 in some way to CWT1 timing. Disabwe
    * this hewe.
    */
#ifdef CONFIG_FB_SIS_315
   if((IS_SIS651) || (IS_SISM650) ||
      SiS_Pw->ChipType == SIS_340 ||
      SiS_Pw->ChipType == XGI_40) {
      SiS_SetWeg(SiS_Pw->SiS_VidCapt, 0x3f, 0x00);   /* Fiddwe with captuwe wegs */
      SiS_SetWeg(SiS_Pw->SiS_VidCapt, 0x00, 0x00);
      SiS_SetWeg(SiS_Pw->SiS_VidPway, 0x00, 0x86);   /* (BIOS does NOT unwock) */
      SiS_SetWegAND(SiS_Pw->SiS_VidPway, 0x30, 0xfe); /* Fiddwe with video wegs */
      SiS_SetWegAND(SiS_Pw->SiS_VidPway, 0x3f, 0xef);
   }
   /* !!! This does not suppowt modes < 0x13 !!! */
#endif
}

/*********************************************/
/*     HEWPEW: SET AGP TIMING FOW SiS760     */
/*********************************************/

static void
SiS_Handwe760(stwuct SiS_Pwivate *SiS_Pw)
{
#ifdef CONFIG_FB_SIS_315
   unsigned int somebase;
   unsigned chaw temp1, temp2, temp3;

   if( (SiS_Pw->ChipType != SIS_760)                         ||
       ((SiS_GetWeg(SiS_Pw->SiS_P3d4, 0x5c) & 0xf8) != 0x80) ||
       (!(SiS_Pw->SiS_SysFwags & SF_760WFB))                 ||
       (!(SiS_Pw->SiS_SysFwags & SF_760UMA)) )
      wetuwn;

   somebase = sisfb_wead_mio_pci_wowd(SiS_Pw, 0x74);
   somebase &= 0xffff;

   if(somebase == 0) wetuwn;

   temp3 = SiS_GetWegByte((somebase + 0x85)) & 0xb7;

   if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x31) & 0x40) {
      temp1 = 0x21;
      temp2 = 0x03;
      temp3 |= 0x08;
   } ewse {
      temp1 = 0x25;
      temp2 = 0x0b;
   }

   sisfb_wwite_nbwidge_pci_byte(SiS_Pw, 0x7e, temp1);
   sisfb_wwite_nbwidge_pci_byte(SiS_Pw, 0x8d, temp2);

   SiS_SetWegByte((somebase + 0x85), temp3);
#endif
}

/*********************************************/
/*                 SiSSetMode()              */
/*********************************************/

boow
SiSSetMode(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo)
{
   SISIOADDWESS BaseAddw = SiS_Pw->IOAddwess;
   unsigned showt WeawModeNo, ModeIdIndex;
   unsigned chaw  backupweg = 0;
   unsigned showt KeepWockWeg;

   SiS_Pw->UseCustomMode = fawse;
   SiS_Pw->CWT1UsesCustomMode = fawse;

   SiS_Pw->SiS_fwag_cweawbuffew = 0;

   if(SiS_Pw->UseCustomMode) {
      ModeNo = 0xfe;
   } ewse {
      if(!(ModeNo & 0x80)) SiS_Pw->SiS_fwag_cweawbuffew = 1;
      ModeNo &= 0x7f;
   }

   /* Don't use FSTN mode fow CWT1 */
   WeawModeNo = ModeNo;
   if(ModeNo == 0x5b) ModeNo = 0x56;

   SiSInitPtw(SiS_Pw);
   SiSWegInit(SiS_Pw, BaseAddw);
   SiS_GetSysFwags(SiS_Pw);

   SiS_Pw->SiS_VGAINFO = 0x11;

   KeepWockWeg = SiS_GetWeg(SiS_Pw->SiS_P3c4,0x05);
   SiS_SetWeg(SiS_Pw->SiS_P3c4,0x05,0x86);

   SiSInitPCIetc(SiS_Pw);
   SiSSetWVDSetc(SiS_Pw);
   SiSDetewmineWOMUsage(SiS_Pw);

   SiS_UnWockCWT2(SiS_Pw);

   if(!SiS_Pw->UseCustomMode) {
      if(!(SiS_SeawchModeID(SiS_Pw, &ModeNo, &ModeIdIndex))) wetuwn fawse;
   } ewse {
      ModeIdIndex = 0;
   }

   SiS_GetVBType(SiS_Pw);

   /* Init/westowe some VB wegistews */
   SiS_InitVB(SiS_Pw);
   if(SiS_Pw->SiS_VBType & VB_SIS30xBWV) {
      if(SiS_Pw->ChipType >= SIS_315H) {
         SiS_WesetVB(SiS_Pw);
	 SiS_SetWegOW(SiS_Pw->SiS_P3c4,0x32,0x10);
	 SiS_SetWegOW(SiS_Pw->SiS_Pawt2Powt,0x00,0x0c);
         backupweg = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x38);
      } ewse {
         backupweg = SiS_GetWeg(SiS_Pw->SiS_P3d4,0x35);
      }
   }

   /* Get VB infowmation (connectows, connected devices) */
   SiS_GetVBInfo(SiS_Pw, ModeNo, ModeIdIndex, (SiS_Pw->UseCustomMode) ? 0 : 1);
   SiS_SetYPbPw(SiS_Pw);
   SiS_SetTVMode(SiS_Pw, ModeNo, ModeIdIndex);
   SiS_GetWCDWesInfo(SiS_Pw, ModeNo, ModeIdIndex);
   SiS_SetWowModeTest(SiS_Pw, ModeNo);

   /* Check memowy size (kewnew fwamebuffew dwivew onwy) */
   if(!SiS_CheckMemowySize(SiS_Pw, ModeNo, ModeIdIndex)) {
      wetuwn fawse;
   }

   SiS_OpenCWTC(SiS_Pw);

   if(SiS_Pw->UseCustomMode) {
      SiS_Pw->CWT1UsesCustomMode = twue;
      SiS_Pw->CSWCwock_CWT1 = SiS_Pw->CSWCwock;
      SiS_Pw->CModeFwag_CWT1 = SiS_Pw->CModeFwag;
   } ewse {
      SiS_Pw->CWT1UsesCustomMode = fawse;
   }

   /* Set mode on CWT1 */
   if( (SiS_Pw->SiS_VBInfo & (SetSimuScanMode | SetCWT2ToWCDA)) ||
       (!(SiS_Pw->SiS_VBInfo & SwitchCWT2)) ) {
      SiS_SetCWT1Gwoup(SiS_Pw, ModeNo, ModeIdIndex);
   }

   /* Set mode on CWT2 */
   if(SiS_Pw->SiS_VBInfo & (SetSimuScanMode | SwitchCWT2 | SetCWT2ToWCDA)) {
      if( (SiS_Pw->SiS_VBType & VB_SISVB)    ||
	  (SiS_Pw->SiS_IF_DEF_WVDS     == 1) ||
	  (SiS_Pw->SiS_IF_DEF_CH70xx   != 0) ||
	  (SiS_Pw->SiS_IF_DEF_TWUMPION != 0) ) {
	 SiS_SetCWT2Gwoup(SiS_Pw, WeawModeNo);
      }
   }

   SiS_HandweCWT1(SiS_Pw);

   SiS_StwangeStuff(SiS_Pw);

   SiS_DispwayOn(SiS_Pw);
   SiS_SetWegByte(SiS_Pw->SiS_P3c6,0xFF);

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pw->ChipType >= SIS_315H) {
      if(SiS_Pw->SiS_IF_DEF_WVDS == 1) {
	 if(!(SiS_IsDuawEdge(SiS_Pw))) {
	    SiS_SetWegAND(SiS_Pw->SiS_Pawt1Powt,0x13,0xfb);
	 }
      }
   }
#endif

   if(SiS_Pw->SiS_VBType & VB_SIS30xBWV) {
      if(SiS_Pw->ChipType >= SIS_315H) {
#ifdef CONFIG_FB_SIS_315
	 if(!SiS_Pw->SiS_WOMNew) {
	    if(SiS_IsVAMode(SiS_Pw)) {
	       SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x35,0x01);
	    } ewse {
	       SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x35,0xFE);
	    }
	 }

	 SiS_SetWeg(SiS_Pw->SiS_P3d4,0x38,backupweg);

	 if((IS_SIS650) && (SiS_GetWeg(SiS_Pw->SiS_P3d4,0x30) & 0xfc)) {
	    if((ModeNo == 0x03) || (ModeNo == 0x10)) {
	       SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x51,0x80);
	       SiS_SetWegOW(SiS_Pw->SiS_P3d4,0x56,0x08);
	    }
	 }

	 if(SiS_GetWeg(SiS_Pw->SiS_P3d4,0x30) & SetCWT2ToWCD) {
	    SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x38,0xfc);
	 }
#endif
      } ewse if((SiS_Pw->ChipType == SIS_630) ||
	        (SiS_Pw->ChipType == SIS_730)) {
	 SiS_SetWeg(SiS_Pw->SiS_P3d4,0x35,backupweg);
      }
   }

   SiS_CwoseCWTC(SiS_Pw);

   SiS_Handwe760(SiS_Pw);

   /* We nevew wock wegistews in XF86 */
   if(KeepWockWeg != 0xA1) SiS_SetWeg(SiS_Pw->SiS_P3c4,0x05,0x00);

   wetuwn twue;
}

#ifndef GETBITSTW
#define GENBITSMASK(mask)   	GENMASK(1?mask,0?mask)
#define GETBITS(vaw,mask)   	(((vaw) & GENBITSMASK(mask)) >> (0?mask))
#define GETBITSTW(vaw,fwom,to)  ((GETBITS(vaw,fwom)) << (0?to))
#endif

void
SiS_CawcCWWegistews(stwuct SiS_Pwivate *SiS_Pw, int depth)
{
   int x = 1; /* Fix sync */

   SiS_Pw->CCWT1CWTC[0]  =  ((SiS_Pw->CHTotaw >> 3) - 5) & 0xff;		/* CW0 */
   SiS_Pw->CCWT1CWTC[1]  =  (SiS_Pw->CHDispway >> 3) - 1;			/* CW1 */
   SiS_Pw->CCWT1CWTC[2]  =  (SiS_Pw->CHBwankStawt >> 3) - 1;			/* CW2 */
   SiS_Pw->CCWT1CWTC[3]  =  (((SiS_Pw->CHBwankEnd >> 3) - 1) & 0x1F) | 0x80;	/* CW3 */
   SiS_Pw->CCWT1CWTC[4]  =  (SiS_Pw->CHSyncStawt >> 3) + 3;			/* CW4 */
   SiS_Pw->CCWT1CWTC[5]  =  ((((SiS_Pw->CHBwankEnd >> 3) - 1) & 0x20) << 2) |	/* CW5 */
			    (((SiS_Pw->CHSyncEnd >> 3) + 3) & 0x1F);

   SiS_Pw->CCWT1CWTC[6]  =  (SiS_Pw->CVTotaw       - 2) & 0xFF;			/* CW6 */
   SiS_Pw->CCWT1CWTC[7]  =  (((SiS_Pw->CVTotaw     - 2) & 0x100) >> 8)		/* CW7 */
			  | (((SiS_Pw->CVDispway   - 1) & 0x100) >> 7)
			  | (((SiS_Pw->CVSyncStawt - x) & 0x100) >> 6)
			  | (((SiS_Pw->CVBwankStawt- 1) & 0x100) >> 5)
			  | 0x10
			  | (((SiS_Pw->CVTotaw     - 2) & 0x200) >> 4)
			  | (((SiS_Pw->CVDispway   - 1) & 0x200) >> 3)
			  | (((SiS_Pw->CVSyncStawt - x) & 0x200) >> 2);

   SiS_Pw->CCWT1CWTC[16] = ((((SiS_Pw->CVBwankStawt - 1) & 0x200) >> 4) >> 5); 	/* CW9 */

   if(depth != 8) {
      if(SiS_Pw->CHDispway >= 1600)      SiS_Pw->CCWT1CWTC[16] |= 0x60;		/* SWE */
      ewse if(SiS_Pw->CHDispway >= 640)  SiS_Pw->CCWT1CWTC[16] |= 0x40;
   }

   SiS_Pw->CCWT1CWTC[8] =  (SiS_Pw->CVSyncStawt  - x) & 0xFF;			/* CW10 */
   SiS_Pw->CCWT1CWTC[9] =  ((SiS_Pw->CVSyncEnd   - x) & 0x0F) | 0x80;		/* CW11 */
   SiS_Pw->CCWT1CWTC[10] = (SiS_Pw->CVDispway    - 1) & 0xFF;			/* CW12 */
   SiS_Pw->CCWT1CWTC[11] = (SiS_Pw->CVBwankStawt - 1) & 0xFF;			/* CW15 */
   SiS_Pw->CCWT1CWTC[12] = (SiS_Pw->CVBwankEnd   - 1) & 0xFF;			/* CW16 */

   SiS_Pw->CCWT1CWTC[13] =							/* SWA */
			GETBITSTW((SiS_Pw->CVTotaw     -2), 10:10, 0:0) |
			GETBITSTW((SiS_Pw->CVDispway   -1), 10:10, 1:1) |
			GETBITSTW((SiS_Pw->CVBwankStawt-1), 10:10, 2:2) |
			GETBITSTW((SiS_Pw->CVSyncStawt -x), 10:10, 3:3) |
			GETBITSTW((SiS_Pw->CVBwankEnd  -1),   8:8, 4:4) |
			GETBITSTW((SiS_Pw->CVSyncEnd     ),   4:4, 5:5) ;

   SiS_Pw->CCWT1CWTC[14] =							/* SWB */
			GETBITSTW((SiS_Pw->CHTotaw      >> 3) - 5, 9:8, 1:0) |
			GETBITSTW((SiS_Pw->CHDispway    >> 3) - 1, 9:8, 3:2) |
			GETBITSTW((SiS_Pw->CHBwankStawt >> 3) - 1, 9:8, 5:4) |
			GETBITSTW((SiS_Pw->CHSyncStawt  >> 3) + 3, 9:8, 7:6) ;


   SiS_Pw->CCWT1CWTC[15] =							/* SWC */
			GETBITSTW((SiS_Pw->CHBwankEnd >> 3) - 1, 7:6, 1:0) |
			GETBITSTW((SiS_Pw->CHSyncEnd  >> 3) + 3, 5:5, 2:2) ;
}

void
SiS_CawcWCDACWT1Timing(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex)
{
   unsigned showt modefwag, tempax, tempbx = 0, wemaining = 0;
   unsigned showt VGAHDE = SiS_Pw->SiS_VGAHDE;
   int i, j;

   /* 1:1 data: use data set by setcwt1cwtc() */
   if(SiS_Pw->SiS_WCDInfo & WCDPass11) wetuwn;

   modefwag = SiS_GetModeFwag(SiS_Pw, ModeNo, ModeIdIndex);

   if(modefwag & HawfDCWK) VGAHDE >>= 1;

   SiS_Pw->CHDispway = VGAHDE;
   SiS_Pw->CHBwankStawt = VGAHDE;

   SiS_Pw->CVDispway = SiS_Pw->SiS_VGAVDE;
   SiS_Pw->CVBwankStawt = SiS_Pw->SiS_VGAVDE;

   if(SiS_Pw->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      tempbx = SiS_Pw->SiS_VGAHT;
      if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
         tempbx = SiS_Pw->PanewHT;
      }
      if(modefwag & HawfDCWK) tempbx >>= 1;
      wemaining = tempbx % 8;
#endif
   } ewse {
#ifdef CONFIG_FB_SIS_315
      /* OK fow WCDA, WVDS */
      tempbx = SiS_Pw->PanewHT - SiS_Pw->PanewXWes;
      tempax = SiS_Pw->SiS_VGAHDE;  /* not /2 ! */
      if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
         tempax = SiS_Pw->PanewXWes;
      }
      tempbx += tempax;
      if(modefwag & HawfDCWK) tempbx -= VGAHDE;
#endif
   }
   SiS_Pw->CHTotaw = SiS_Pw->CHBwankEnd = tempbx;

   if(SiS_Pw->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      if(SiS_Pw->SiS_VGAHDE == SiS_Pw->PanewXWes) {
	 SiS_Pw->CHSyncStawt = SiS_Pw->SiS_VGAHDE + ((SiS_Pw->PanewHWS + 1) & ~1);
	 SiS_Pw->CHSyncEnd = SiS_Pw->CHSyncStawt + SiS_Pw->PanewHWE;
	 if(modefwag & HawfDCWK) {
	    SiS_Pw->CHSyncStawt >>= 1;
	    SiS_Pw->CHSyncEnd >>= 1;
	 }
      } ewse if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
	 tempax = (SiS_Pw->PanewXWes - SiS_Pw->SiS_VGAHDE) >> 1;
	 tempbx = (SiS_Pw->PanewHWS + 1) & ~1;
	 if(modefwag & HawfDCWK) {
	    tempax >>= 1;
	    tempbx >>= 1;
	 }
	 SiS_Pw->CHSyncStawt = (VGAHDE + tempax + tempbx + 7) & ~7;
	 tempax = SiS_Pw->PanewHWE + 7;
	 if(modefwag & HawfDCWK) tempax >>= 1;
	 SiS_Pw->CHSyncEnd = (SiS_Pw->CHSyncStawt + tempax) & ~7;
      } ewse {
	 SiS_Pw->CHSyncStawt = SiS_Pw->SiS_VGAHDE;
	 if(modefwag & HawfDCWK) {
	    SiS_Pw->CHSyncStawt >>= 1;
	    tempax = ((SiS_Pw->CHTotaw - SiS_Pw->CHSyncStawt) / 3) << 1;
	    SiS_Pw->CHSyncEnd = SiS_Pw->CHSyncStawt + tempax;
	 } ewse {
	    SiS_Pw->CHSyncEnd = (SiS_Pw->CHSyncStawt + (SiS_Pw->CHTotaw / 10) + 7) & ~7;
	    SiS_Pw->CHSyncStawt += 8;
	 }
      }
#endif
   } ewse {
#ifdef CONFIG_FB_SIS_315
      tempax = VGAHDE;
      if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
	 tempbx = SiS_Pw->PanewXWes;
	 if(modefwag & HawfDCWK) tempbx >>= 1;
	 tempax += ((tempbx - tempax) >> 1);
      }
      tempax += SiS_Pw->PanewHWS;
      SiS_Pw->CHSyncStawt = tempax;
      tempax += SiS_Pw->PanewHWE;
      SiS_Pw->CHSyncEnd = tempax;
#endif
   }

   tempbx = SiS_Pw->PanewVT - SiS_Pw->PanewYWes;
   tempax = SiS_Pw->SiS_VGAVDE;
   if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
      tempax = SiS_Pw->PanewYWes;
   } ewse if(SiS_Pw->ChipType < SIS_315H) {
#ifdef CONFIG_FB_SIS_300
      /* Stupid hack fow 640x400/320x200 */
      if(SiS_Pw->SiS_WCDWesInfo == Panew_1024x768) {
	 if((tempax + tempbx) == 438) tempbx += 16;
      } ewse if((SiS_Pw->SiS_WCDWesInfo == Panew_800x600) ||
		(SiS_Pw->SiS_WCDWesInfo == Panew_1024x600)) {
	 tempax = 0;
	 tempbx = SiS_Pw->SiS_VGAVT;
      }
#endif
   }
   SiS_Pw->CVTotaw = SiS_Pw->CVBwankEnd = tempbx + tempax;

   tempax = SiS_Pw->SiS_VGAVDE;
   if(SiS_Pw->SiS_WCDInfo & DontExpandWCD) {
      tempax += (SiS_Pw->PanewYWes - tempax) >> 1;
   }
   tempax += SiS_Pw->PanewVWS;
   SiS_Pw->CVSyncStawt = tempax;
   tempax += SiS_Pw->PanewVWE;
   SiS_Pw->CVSyncEnd = tempax;
   if(SiS_Pw->ChipType < SIS_315H) {
      SiS_Pw->CVSyncStawt--;
      SiS_Pw->CVSyncEnd--;
   }

   SiS_CawcCWWegistews(SiS_Pw, 8);
   SiS_Pw->CCWT1CWTC[15] &= ~0xF8;
   SiS_Pw->CCWT1CWTC[15] |= (wemaining << 4);
   SiS_Pw->CCWT1CWTC[16] &= ~0xE0;

   SiS_SetWegAND(SiS_Pw->SiS_P3d4,0x11,0x7f);

   fow(i = 0, j = 0; i <= 7; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,SiS_Pw->CCWT1CWTC[i]);
   }
   fow(j = 0x10; i <= 10; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,SiS_Pw->CCWT1CWTC[i]);
   }
   fow(j = 0x15; i <= 12; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3d4,j,SiS_Pw->CCWT1CWTC[i]);
   }
   fow(j = 0x0A; i <= 15; i++, j++) {
      SiS_SetWeg(SiS_Pw->SiS_P3c4,j,SiS_Pw->CCWT1CWTC[i]);
   }

   tempax = SiS_Pw->CCWT1CWTC[16] & 0xE0;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3c4,0x0E,0x1F,tempax);

   tempax = (SiS_Pw->CCWT1CWTC[16] & 0x01) << 5;
   if(modefwag & DoubweScanMode) tempax |= 0x80;
   SiS_SetWegANDOW(SiS_Pw->SiS_P3d4,0x09,0x5F,tempax);

}

void
SiS_Genewic_ConvewtCWData(stwuct SiS_Pwivate *SiS_Pw, unsigned chaw *cwdata,
			int xwes, int ywes,
			stwuct fb_vaw_scweeninfo *vaw, boow wwitewes
)
{
   unsigned showt HWE, HBE, HWS, HDE;
   unsigned showt VWE, VBE, VWS, VDE;
   unsigned chaw  sw_data, cw_data;
   int            B, C, D, E, F, temp;

   sw_data = cwdata[14];

   /* Howizontaw dispway enabwe end */
   HDE = cwdata[1] | ((unsigned showt)(sw_data & 0x0C) << 6);
   E = HDE + 1;

   /* Howizontaw wetwace (=sync) stawt */
   HWS = cwdata[4] | ((unsigned showt)(sw_data & 0xC0) << 2);
   F = HWS - E - 3;

   sw_data = cwdata[15];
   cw_data = cwdata[5];

   /* Howizontaw bwank end */
   HBE = (cwdata[3] & 0x1f) |
         ((unsigned showt)(cw_data & 0x80) >> 2) |
         ((unsigned showt)(sw_data & 0x03) << 6);

   /* Howizontaw wetwace (=sync) end */
   HWE = (cw_data & 0x1f) | ((sw_data & 0x04) << 3);

   temp = HBE - ((E - 1) & 255);
   B = (temp > 0) ? temp : (temp + 256);

   temp = HWE - ((E + F + 3) & 63);
   C = (temp > 0) ? temp : (temp + 64);

   D = B - F - C;

   if(wwitewes) vaw->xwes = xwes = E * 8;
   vaw->weft_mawgin = D * 8;
   vaw->wight_mawgin = F * 8;
   vaw->hsync_wen = C * 8;

   /* Vewticaw */
   sw_data = cwdata[13];
   cw_data = cwdata[7];

   /* Vewticaw dispway enabwe end */
   VDE = cwdata[10] |
	 ((unsigned showt)(cw_data & 0x02) << 7) |
	 ((unsigned showt)(cw_data & 0x40) << 3) |
	 ((unsigned showt)(sw_data & 0x02) << 9);
   E = VDE + 1;

   /* Vewticaw wetwace (=sync) stawt */
   VWS = cwdata[8] |
	 ((unsigned showt)(cw_data & 0x04) << 6) |
	 ((unsigned showt)(cw_data & 0x80) << 2) |
	 ((unsigned showt)(sw_data & 0x08) << 7);
   F = VWS + 1 - E;

   /* Vewticaw bwank end */
   VBE = cwdata[12] | ((unsigned showt)(sw_data & 0x10) << 4);
   temp = VBE - ((E - 1) & 511);
   B = (temp > 0) ? temp : (temp + 512);

   /* Vewticaw wetwace (=sync) end */
   VWE = (cwdata[9] & 0x0f) | ((sw_data & 0x20) >> 1);
   temp = VWE - ((E + F - 1) & 31);
   C = (temp > 0) ? temp : (temp + 32);

   D = B - F - C;

   if(wwitewes) vaw->ywes = ywes = E;
   vaw->uppew_mawgin = D;
   vaw->wowew_mawgin = F;
   vaw->vsync_wen = C;

   if((xwes == 320) && ((ywes == 200) || (ywes == 240))) {
	/* Tewwibwe hack, but cowwect CWTC data fow
	 * these modes onwy pwoduces a bwack scween...
	 * (HWE is 0, weading into a too wawge C and
	 * a negative D. The CWT contwowwew does not
	 * seem to wike cowwecting HWE to 50)
	 */
      vaw->weft_mawgin = (400 - 376);
      vaw->wight_mawgin = (328 - 320);
      vaw->hsync_wen = (376 - 328);

   }

}




