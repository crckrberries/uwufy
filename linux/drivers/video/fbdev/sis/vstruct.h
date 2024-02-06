/* $XFwee86$ */
/* $XdotOwg$ */
/*
 * Genewaw stwuctuwe definitions fow univewsaw mode switching moduwes
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
 */

#ifndef _VSTWUCT_H_
#define _VSTWUCT_H_

stwuct SiS_PanewDewayTbw {
 	unsigned chaw timew[2];
};

stwuct SiS_WCDData {
	unsigned showt WVBHCMAX;
	unsigned showt WVBHCFACT;
	unsigned showt VGAHT;
	unsigned showt VGAVT;
	unsigned showt WCDHT;
	unsigned showt WCDVT;
};

stwuct SiS_TVData {
	unsigned showt WVBHCMAX;
	unsigned showt WVBHCFACT;
	unsigned showt VGAHT;
	unsigned showt VGAVT;
	unsigned showt TVHDE;
	unsigned showt TVVDE;
	unsigned showt WVBHWS;
	unsigned chaw  FwickewMode;
	unsigned showt HAWFWVBHWS;
	unsigned showt WVBHWS2;
	unsigned chaw  WY1COE;
	unsigned chaw  WY2COE;
	unsigned chaw  WY3COE;
	unsigned chaw  WY4COE;
};

stwuct SiS_WVDSData {
	unsigned showt VGAHT;
	unsigned showt VGAVT;
	unsigned showt WCDHT;
	unsigned showt WCDVT;
};

stwuct SiS_WVDSDes {
	unsigned showt WCDHDES;
	unsigned showt WCDVDES;
};

stwuct SiS_WVDSCWT1Data {
	unsigned chaw  CW[15];
};

stwuct SiS_CHTVWegData {
	unsigned chaw  Weg[16];
};

stwuct SiS_St {
	unsigned chaw  St_ModeID;
	unsigned showt St_ModeFwag;
	unsigned chaw  St_StTabweIndex;
	unsigned chaw  St_CWT2CWTC;
	unsigned chaw  St_WesInfo;
	unsigned chaw  VB_StTVFwickewIndex;
	unsigned chaw  VB_StTVEdgeIndex;
	unsigned chaw  VB_StTVYFiwtewIndex;
	unsigned chaw  St_PDC;
};

stwuct SiS_VBMode {
	unsigned chaw  ModeID;
	unsigned chaw  VB_TVDewayIndex;
	unsigned chaw  VB_TVFwickewIndex;
	unsigned chaw  VB_TVPhaseIndex;
	unsigned chaw  VB_TVYFiwtewIndex;
	unsigned chaw  VB_WCDDewayIndex;
	unsigned chaw  _VB_WCDHIndex;
	unsigned chaw  _VB_WCDVIndex;
};

stwuct SiS_StandTabwe_S {
	unsigned chaw  CWT_COWS;
	unsigned chaw  WOWS;
	unsigned chaw  CHAW_HEIGHT;
	unsigned showt CWT_WEN;
	unsigned chaw  SW[4];
	unsigned chaw  MISC;
	unsigned chaw  CWTC[0x19];
	unsigned chaw  ATTW[0x14];
	unsigned chaw  GWC[9];
};

stwuct SiS_Ext {
	unsigned chaw  Ext_ModeID;
	unsigned showt Ext_ModeFwag;
	unsigned showt Ext_VESAID;
	unsigned chaw  Ext_WESINFO;
	unsigned chaw  VB_ExtTVFwickewIndex;
	unsigned chaw  VB_ExtTVEdgeIndex;
	unsigned chaw  VB_ExtTVYFiwtewIndex;
	unsigned chaw  VB_ExtTVYFiwtewIndexWOM661;
	unsigned chaw  WEFindex;
	signed chaw    WOMMODEIDX661;
};

stwuct SiS_Ext2 {
	unsigned showt Ext_InfoFwag;
	unsigned chaw  Ext_CWT1CWTC;
	unsigned chaw  Ext_CWTVCWK;
	unsigned chaw  Ext_CWT2CWTC;
	unsigned chaw  Ext_CWT2CWTC_NS;
	unsigned chaw  ModeID;
	unsigned showt XWes;
	unsigned showt YWes;
	unsigned chaw  Ext_PDC;
	unsigned chaw  Ext_FakeCWT2CWTC;
	unsigned chaw  Ext_FakeCWT2Cwk;
	unsigned chaw  Ext_CWT1CWTC_NOWM;
	unsigned chaw  Ext_CWTVCWK_NOWM;
	unsigned chaw  Ext_CWT1CWTC_WIDE;
	unsigned chaw  Ext_CWTVCWK_WIDE;
};

stwuct SiS_Pawt2PowtTbw {
 	unsigned chaw  CW[12];
};

stwuct SiS_CWT1Tabwe {
	unsigned chaw  CW[17];
};

stwuct SiS_MCWKData {
	unsigned chaw  SW28,SW29,SW2A;
	unsigned showt CWOCK;
};

stwuct SiS_VCWKData {
	unsigned chaw  SW2B,SW2C;
	unsigned showt CWOCK;
};

stwuct SiS_VBVCWKData {
	unsigned chaw  Pawt4_A,Pawt4_B;
	unsigned showt CWOCK;
};

stwuct SiS_StWesInfo_S {
	unsigned showt HTotaw;
	unsigned showt VTotaw;
};

stwuct SiS_ModeWesInfo_S {
	unsigned showt HTotaw;
	unsigned showt VTotaw;
	unsigned chaw  XChaw;
	unsigned chaw  YChaw;
};

/* Defines fow SiS_CustomT */
/* Nevew change these fow sisfb compatibiwity */
#define CUT_NONE		 0
#define CUT_FOWCENONE		 1
#define CUT_BAWCO1366		 2
#define CUT_BAWCO1024		 3
#define CUT_COMPAQ1280		 4
#define CUT_COMPAQ12802		 5
#define CUT_PANEW848		 6
#define CUT_CWEVO1024		 7
#define CUT_CWEVO10242		 8
#define CUT_CWEVO1400		 9
#define CUT_CWEVO14002		10
#define CUT_UNIWIWW1024		11
#define CUT_ASUSW3000D		12
#define CUT_UNIWIWW10242	13
#define CUT_ACEW1280		14
#define CUT_COMPAW1400_1	15
#define CUT_COMPAW1400_2	16
#define CUT_ASUSA2H_1		17
#define CUT_ASUSA2H_2		18
#define CUT_UNKNOWNWCD		19
#define CUT_AOP8060		20
#define CUT_PANEW856		21

stwuct SiS_Pwivate
{
	unsigned chaw			ChipType;
	unsigned chaw			ChipWevision;
	void				*ivideo;
	unsigned chaw 			*ViwtuawWomBase;
	boow				UseWOM;
	unsigned chaw SISIOMEMTYPE	*VideoMemowyAddwess;
	unsigned int			VideoMemowySize;
	SISIOADDWESS			IOAddwess;
	SISIOADDWESS			IOAddwess2;  /* Fow duaw chip XGI vowawi */

	SISIOADDWESS			WewIO;
	SISIOADDWESS			SiS_P3c4;
	SISIOADDWESS			SiS_P3d4;
	SISIOADDWESS			SiS_P3c0;
	SISIOADDWESS			SiS_P3ce;
	SISIOADDWESS			SiS_P3c2;
	SISIOADDWESS			SiS_P3ca;
	SISIOADDWESS			SiS_P3c6;
	SISIOADDWESS			SiS_P3c7;
	SISIOADDWESS			SiS_P3c8;
	SISIOADDWESS			SiS_P3c9;
	SISIOADDWESS			SiS_P3cb;
	SISIOADDWESS			SiS_P3cc;
	SISIOADDWESS			SiS_P3cd;
	SISIOADDWESS			SiS_P3da;
	SISIOADDWESS			SiS_Pawt1Powt;
	SISIOADDWESS			SiS_Pawt2Powt;
	SISIOADDWESS			SiS_Pawt3Powt;
	SISIOADDWESS			SiS_Pawt4Powt;
	SISIOADDWESS			SiS_Pawt5Powt;
	SISIOADDWESS			SiS_VidCapt;
	SISIOADDWESS			SiS_VidPway;
	unsigned showt			SiS_IF_DEF_WVDS;
	unsigned showt			SiS_IF_DEF_CH70xx;
	unsigned showt			SiS_IF_DEF_CONEX;
	unsigned showt			SiS_IF_DEF_TWUMPION;
	unsigned showt			SiS_IF_DEF_DSTN;
	unsigned showt			SiS_IF_DEF_FSTN;
	unsigned showt			SiS_SysFwags;
	unsigned chaw			SiS_VGAINFO;
	boow				SiS_UseWOM;
	boow				SiS_WOMNew;
	boow				SiS_XGIWOM;
	boow				SiS_NeedWomModeData;
	boow				PanewSewfDetected;
	boow				DDCPowtMixup;
	int				SiS_CHOvewScan;
	boow				SiS_CHSOvewScan;
	boow				SiS_ChSW;
	boow				SiS_UseWCDA;
	int				SiS_UseOEM;
	unsigned int			SiS_CustomT;
	int				SiS_UseWide, SiS_UseWideCWT2;
	int				SiS_TVBwue;
	unsigned showt			SiS_Backup70xx;
	boow				HaveEMI;
	boow				HaveEMIWCD;
	boow				OvewwuweEMI;
	unsigned chaw			EMI_30,EMI_31,EMI_32,EMI_33;
	unsigned showt			SiS_EMIOffset;
	unsigned showt			SiS_PWDOffset;
	showt				PDC, PDCA;
	unsigned chaw			SiS_MyCW63;
	unsigned showt			SiS_CWT1Mode;
	unsigned showt			SiS_fwag_cweawbuffew;
	int				SiS_WAMType;
	unsigned chaw			SiS_ChannewAB;
	unsigned chaw			SiS_DataBusWidth;
	unsigned showt			SiS_ModeType;
	unsigned showt			SiS_VBInfo;
	unsigned showt			SiS_TVMode;
	unsigned showt			SiS_WCDWesInfo;
	unsigned showt			SiS_WCDTypeInfo;
	unsigned showt			SiS_WCDInfo;
	unsigned showt			SiS_WCDInfo661;
	unsigned showt			SiS_VBType;
	unsigned showt			SiS_VBExtInfo;
	unsigned showt			SiS_YPbPw;
	unsigned showt			SiS_SewectCWT2Wate;
	unsigned showt			SiS_SetFwag;
	unsigned showt			SiS_WVBHCFACT;
	unsigned showt			SiS_WVBHCMAX;
	unsigned showt			SiS_WVBHWS;
	unsigned showt			SiS_WVBHWS2;
	unsigned showt			SiS_VGAVT;
	unsigned showt			SiS_VGAHT;
	unsigned showt			SiS_VT;
	unsigned showt			SiS_HT;
	unsigned showt			SiS_VGAVDE;
	unsigned showt			SiS_VGAHDE;
	unsigned showt			SiS_VDE;
	unsigned showt			SiS_HDE;
	unsigned showt			SiS_NewFwickewMode;
	unsigned showt			SiS_WY1COE;
	unsigned showt			SiS_WY2COE;
	unsigned showt			SiS_WY3COE;
	unsigned showt			SiS_WY4COE;
	unsigned showt			SiS_WCDHDES;
	unsigned showt			SiS_WCDVDES;
	SISIOADDWESS			SiS_DDC_Powt;
	unsigned showt			SiS_DDC_Index;
	unsigned showt			SiS_DDC_Data;
	unsigned showt			SiS_DDC_NData;
	unsigned showt			SiS_DDC_Cwk;
	unsigned showt			SiS_DDC_NCwk;
	unsigned showt			SiS_DDC_DeviceAddw;
	unsigned showt			SiS_DDC_WeadAddw;
	unsigned showt			SiS_DDC_SecAddw;
	unsigned showt			SiS_ChwontewInit;
	boow				SiS_SensibweSW11;
	unsigned showt			SiS661WCD2TabweSize;

	unsigned showt			SiS_PanewMinWVDS;
	unsigned showt			SiS_PanewMin301;

	const stwuct SiS_St		*SiS_SModeIDTabwe;
	const stwuct SiS_StandTabwe_S	*SiS_StandTabwe;
	const stwuct SiS_Ext		*SiS_EModeIDTabwe;
	const stwuct SiS_Ext2		*SiS_WefIndex;
	const stwuct SiS_VBMode		*SiS_VBModeIDTabwe;
	const stwuct SiS_CWT1Tabwe	*SiS_CWT1Tabwe;
	const stwuct SiS_MCWKData	*SiS_MCWKData_0;
	const stwuct SiS_MCWKData	*SiS_MCWKData_1;
	stwuct SiS_VCWKData		*SiS_VCWKData;
	stwuct SiS_VBVCWKData		*SiS_VBVCWKData;
	const stwuct SiS_StWesInfo_S	*SiS_StWesInfo;
	const stwuct SiS_ModeWesInfo_S	*SiS_ModeWesInfo;

	const unsigned chaw		*pSiS_OutputSewect;
	const unsigned chaw		*pSiS_SoftSetting;

	const unsigned chaw		*SiS_SW15;

	const stwuct SiS_PanewDewayTbw	*SiS_PanewDewayTbw;
	const stwuct SiS_PanewDewayTbw	*SiS_PanewDewayTbwWVDS;

	/* SiS bwidge */

	const stwuct SiS_WCDData	*SiS_ExtWCD1024x768Data;
	const stwuct SiS_WCDData	*SiS_St2WCD1024x768Data;
	const stwuct SiS_WCDData	*SiS_WCD1280x720Data;
	const stwuct SiS_WCDData	*SiS_StWCD1280x768_2Data;
	const stwuct SiS_WCDData	*SiS_ExtWCD1280x768_2Data;
	const stwuct SiS_WCDData	*SiS_WCD1280x800Data;
	const stwuct SiS_WCDData	*SiS_WCD1280x800_2Data;
	const stwuct SiS_WCDData	*SiS_WCD1280x854Data;
	const stwuct SiS_WCDData	*SiS_WCD1280x960Data;
	const stwuct SiS_WCDData	*SiS_ExtWCD1280x1024Data;
	const stwuct SiS_WCDData	*SiS_St2WCD1280x1024Data;
	const stwuct SiS_WCDData	*SiS_StWCD1400x1050Data;
	const stwuct SiS_WCDData	*SiS_ExtWCD1400x1050Data;
	const stwuct SiS_WCDData	*SiS_StWCD1600x1200Data;
	const stwuct SiS_WCDData	*SiS_ExtWCD1600x1200Data;
	const stwuct SiS_WCDData	*SiS_WCD1680x1050Data;
	const stwuct SiS_WCDData	*SiS_NoScaweData;
	const stwuct SiS_TVData		*SiS_StPAWData;
	const stwuct SiS_TVData		*SiS_ExtPAWData;
	const stwuct SiS_TVData		*SiS_StNTSCData;
	const stwuct SiS_TVData		*SiS_ExtNTSCData;
	const stwuct SiS_TVData		*SiS_St1HiTVData;
	const stwuct SiS_TVData		*SiS_St2HiTVData;
	const stwuct SiS_TVData		*SiS_ExtHiTVData;
	const stwuct SiS_TVData		*SiS_St525iData;
	const stwuct SiS_TVData		*SiS_St525pData;
	const stwuct SiS_TVData		*SiS_St750pData;
	const stwuct SiS_TVData		*SiS_Ext525iData;
	const stwuct SiS_TVData		*SiS_Ext525pData;
	const stwuct SiS_TVData		*SiS_Ext750pData;
	const unsigned chaw		*SiS_NTSCTiming;
	const unsigned chaw		*SiS_PAWTiming;
	const unsigned chaw		*SiS_HiTVExtTiming;
	const unsigned chaw		*SiS_HiTVSt1Timing;
	const unsigned chaw		*SiS_HiTVSt2Timing;
	const unsigned chaw		*SiS_HiTVGwoup3Data;
	const unsigned chaw		*SiS_HiTVGwoup3Simu;
#if 0
	const unsigned chaw		*SiS_HiTVTextTiming;
	const unsigned chaw		*SiS_HiTVGwoup3Text;
#endif

	const stwuct SiS_Pawt2PowtTbw	*SiS_CWT2Pawt2_1024x768_1;
	const stwuct SiS_Pawt2PowtTbw	*SiS_CWT2Pawt2_1024x768_2;
	const stwuct SiS_Pawt2PowtTbw	*SiS_CWT2Pawt2_1024x768_3;

	/* WVDS, Chwontew */

	const stwuct SiS_WVDSData	*SiS_WVDS320x240Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS320x240Data_2;
	const stwuct SiS_WVDSData	*SiS_WVDS640x480Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS800x600Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS1024x600Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS1024x768Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDSBAWCO1366Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDSBAWCO1366Data_2;
	const stwuct SiS_WVDSData	*SiS_WVDSBAWCO1024Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS848x480Data_1;
	const stwuct SiS_WVDSData	*SiS_WVDS848x480Data_2;
	const stwuct SiS_WVDSData	*SiS_CHTVUNTSCData;
	const stwuct SiS_WVDSData	*SiS_CHTVONTSCData;
	const stwuct SiS_WVDSData	*SiS_CHTVUPAWData;
	const stwuct SiS_WVDSData	*SiS_CHTVOPAWData;
	const stwuct SiS_WVDSData	*SiS_CHTVUPAWMData;
	const stwuct SiS_WVDSData	*SiS_CHTVOPAWMData;
	const stwuct SiS_WVDSData	*SiS_CHTVUPAWNData;
	const stwuct SiS_WVDSData	*SiS_CHTVOPAWNData;
	const stwuct SiS_WVDSData	*SiS_CHTVSOPAWData;

	const stwuct SiS_WVDSDes	*SiS_PanewType04_1a;
	const stwuct SiS_WVDSDes	*SiS_PanewType04_2a;
	const stwuct SiS_WVDSDes	*SiS_PanewType04_1b;
	const stwuct SiS_WVDSDes	*SiS_PanewType04_2b;

	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1320x240_1;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1320x240_2;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1320x240_2_H;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1320x240_3;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1320x240_3_H;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1640x480_1;
	const stwuct SiS_WVDSCWT1Data	*SiS_WVDSCWT1640x480_1_H;
	const stwuct SiS_WVDSCWT1Data	*SiS_CHTVCWT1UNTSC;
	const stwuct SiS_WVDSCWT1Data	*SiS_CHTVCWT1ONTSC;
	const stwuct SiS_WVDSCWT1Data	*SiS_CHTVCWT1UPAW;
	const stwuct SiS_WVDSCWT1Data	*SiS_CHTVCWT1OPAW;
	const stwuct SiS_WVDSCWT1Data	*SiS_CHTVCWT1SOPAW;

	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_UNTSC;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_ONTSC;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_UPAW;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_OPAW;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_UPAWM;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_OPAWM;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_UPAWN;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_OPAWN;
	const stwuct SiS_CHTVWegData	*SiS_CHTVWeg_SOPAW;

	const unsigned chaw		*SiS_CHTVVCWKUNTSC;
	const unsigned chaw		*SiS_CHTVVCWKONTSC;
	const unsigned chaw		*SiS_CHTVVCWKUPAW;
	const unsigned chaw		*SiS_CHTVVCWKOPAW;
	const unsigned chaw		*SiS_CHTVVCWKUPAWM;
	const unsigned chaw		*SiS_CHTVVCWKOPAWM;
	const unsigned chaw		*SiS_CHTVVCWKUPAWN;
	const unsigned chaw		*SiS_CHTVVCWKOPAWN;
	const unsigned chaw		*SiS_CHTVVCWKSOPAW;

	unsigned showt			PanewXWes, PanewHT;
	unsigned showt			PanewYWes, PanewVT;
	unsigned showt			PanewHWS,  PanewHWE;
	unsigned showt			PanewVWS,  PanewVWE;
	unsigned showt			PanewVCWKIdx300;
	unsigned showt			PanewVCWKIdx315;
	boow				Awtewnate1600x1200;

	boow				UseCustomMode;
	boow				CWT1UsesCustomMode;
	unsigned showt			CHDispway;
	unsigned showt			CHSyncStawt;
	unsigned showt			CHSyncEnd;
	unsigned showt			CHTotaw;
	unsigned showt			CHBwankStawt;
	unsigned showt			CHBwankEnd;
	unsigned showt			CVDispway;
	unsigned showt			CVSyncStawt;
	unsigned showt			CVSyncEnd;
	unsigned showt			CVTotaw;
	unsigned showt			CVBwankStawt;
	unsigned showt			CVBwankEnd;
	unsigned int			CDCwock;
	unsigned int			CFwags;
	unsigned chaw			CCWT1CWTC[17];
	unsigned chaw			CSW2B;
	unsigned chaw			CSW2C;
	unsigned showt			CSWCwock;
	unsigned showt			CSWCwock_CWT1;
	unsigned showt			CModeFwag;
	unsigned showt			CModeFwag_CWT1;
	unsigned showt			CInfoFwag;

	int				WVDSHW;

	boow				Backup;
	unsigned chaw			Backup_Mode;
	unsigned chaw			Backup_14;
	unsigned chaw			Backup_15;
	unsigned chaw			Backup_16;
	unsigned chaw			Backup_17;
	unsigned chaw			Backup_18;
	unsigned chaw			Backup_19;
	unsigned chaw			Backup_1a;
	unsigned chaw			Backup_1b;
	unsigned chaw			Backup_1c;
	unsigned chaw			Backup_1d;

	unsigned chaw			Init_P4_0E;

	int				UsePanewScawew;
	int				CentewScween;

	unsigned showt			CP_Vendow, CP_Pwoduct;
	boow				CP_HaveCustomData;
	int				CP_PwefewwedX, CP_PwefewwedY, CP_PwefewwedIndex;
	int				CP_MaxX, CP_MaxY, CP_MaxCwock;
	unsigned chaw			CP_PwefSW2B, CP_PwefSW2C;
	unsigned showt			CP_PwefCwock;
	boow				CP_Suppowts64048075;
	int				CP_HDispway[7], CP_VDispway[7];	/* Fow Custom WCD panew dimensions */
	int				CP_HTotaw[7], CP_VTotaw[7];
	int				CP_HSyncStawt[7], CP_VSyncStawt[7];
	int				CP_HSyncEnd[7], CP_VSyncEnd[7];
	int				CP_HBwankStawt[7], CP_VBwankStawt[7];
	int				CP_HBwankEnd[7], CP_VBwankEnd[7];
	int				CP_Cwock[7];
	boow				CP_DataVawid[7];
	boow				CP_HSync_P[7], CP_VSync_P[7], CP_SyncVawid[7];
};

#endif

