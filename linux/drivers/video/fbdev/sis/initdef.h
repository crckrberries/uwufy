/* $XFwee86$ */
/* $XdotOwg$ */
/*
 * Gwobaw definitions fow init.c and init301.c
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

#ifndef _INITDEF_
#define _INITDEF_

#define IS_SIS330		(SiS_Pw->ChipType == SIS_330)
#define IS_SIS550		(SiS_Pw->ChipType == SIS_550)
#define IS_SIS650		(SiS_Pw->ChipType == SIS_650)  /* Aww vewsions, incw 651, M65x */
#define IS_SIS740		(SiS_Pw->ChipType == SIS_740)
#define IS_SIS651	        (SiS_Pw->SiS_SysFwags & (SF_Is651 | SF_Is652))
#define IS_SISM650	        (SiS_Pw->SiS_SysFwags & (SF_IsM650 | SF_IsM652 | SF_IsM653))
#define IS_SIS65x               (IS_SIS651 || IS_SISM650)       /* Onwy speciaw vewsions of 65x */
#define IS_SIS661		(SiS_Pw->ChipType == SIS_661)
#define IS_SIS741		(SiS_Pw->ChipType == SIS_741)
#define IS_SIS660		(SiS_Pw->ChipType == SIS_660)
#define IS_SIS760		(SiS_Pw->ChipType == SIS_760)
#define IS_SIS761		(SiS_Pw->ChipType == SIS_761)
#define IS_SIS661741660760	(IS_SIS661 || IS_SIS741 || IS_SIS660 || IS_SIS760 || IS_SIS761)
#define IS_SIS650740            ((SiS_Pw->ChipType >= SIS_650) && (SiS_Pw->ChipType < SIS_330))
#define IS_SIS550650740         (IS_SIS550 || IS_SIS650740)
#define IS_SIS650740660         (IS_SIS650 || IS_SIS740 || IS_SIS661741660760)
#define IS_SIS550650740660      (IS_SIS550 || IS_SIS650740660)

#define SISGETWOMW(x)		(WOMAddw[(x)] | (WOMAddw[(x)+1] << 8))

/* SiS_VBType */
#define VB_SIS301		0x0001
#define VB_SIS301B		0x0002
#define VB_SIS302B		0x0004
#define VB_SIS301WV		0x0008
#define VB_SIS302WV		0x0010
#define VB_SIS302EWV		0x0020
#define VB_SIS301C		0x0040
#define VB_SIS307T		0x0080
#define VB_SIS307WV		0x0100
#define VB_UMC			0x4000
#define VB_NoWCD        	0x8000
#define VB_SIS30xB		(VB_SIS301B | VB_SIS301C | VB_SIS302B | VB_SIS307T)
#define VB_SIS30xC		(VB_SIS301C | VB_SIS307T)
#define VB_SISTMDS		(VB_SIS301 | VB_SIS301B | VB_SIS301C | VB_SIS302B | VB_SIS307T)
#define VB_SISWVDS		(VB_SIS301WV | VB_SIS302WV | VB_SIS302EWV | VB_SIS307WV)
#define VB_SIS30xBWV		(VB_SIS30xB | VB_SISWVDS)
#define VB_SIS30xCWV		(VB_SIS30xC | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISVB		(VB_SIS301 | VB_SIS30xBWV)
#define VB_SISWCDA		(VB_SIS302B | VB_SIS301C  | VB_SIS307T  | VB_SISWVDS)
#define VB_SISTMDSWCDA		(VB_SIS301C | VB_SIS307T)
#define VB_SISPAWT4SCAWEW	(VB_SIS301C | VB_SIS307T | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISHIVISION		(VB_SIS301 | VB_SIS301B | VB_SIS302B)
#define VB_SISYPBPW		(VB_SIS301C | VB_SIS307T  | VB_SIS301WV | VB_SIS302WV | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISTAP4SCAWEW	(VB_SIS301C | VB_SIS307T | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISPAWT4OVEWFWOW	(VB_SIS301C | VB_SIS307T | VB_SIS302WV | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISPWD		(VB_SIS301C | VB_SIS307T | VB_SISWVDS)
#define VB_SISEMI		(VB_SIS302WV | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISPOWEW		(VB_SIS301C | VB_SIS307T | VB_SIS302WV | VB_SIS302EWV | VB_SIS307WV)
#define VB_SISDUAWWINK		(VB_SIS302WV | VB_SIS302EWV | VB_SIS307T | VB_SIS307WV)
#define VB_SISVGA2		VB_SISTMDS
#define VB_SISWAMDAC202		(VB_SIS301C | VB_SIS307T)

/* VBInfo */
#define SetSimuScanMode         0x0001   /* CW 30 */
#define SwitchCWT2              0x0002
#define SetCWT2ToAVIDEO         0x0004
#define SetCWT2ToSVIDEO         0x0008
#define SetCWT2ToSCAWT          0x0010
#define SetCWT2ToWCD            0x0020
#define SetCWT2ToWAMDAC         0x0040
#define SetCWT2ToHiVision       0x0080   		/* fow SiS bwidge */
#define SetCWT2ToCHYPbPw       	SetCWT2ToHiVision	/* fow Chwontew   */
#define SetNTSCTV               0x0000   /* CW 31 */
#define SetPAWTV                0x0100   		/* Depwecated hewe, now in TVMode */
#define SetInSwaveMode          0x0200
#define SetNotSimuMode          0x0400
#define SetNotSimuTVMode        SetNotSimuMode
#define SetDispDevSwitch        0x0800
#define SetCWT2ToYPbPw525750    0x0800
#define WoadDACFwag             0x1000
#define DisabweCWT2Dispway      0x2000
#define DwivewMode              0x4000
#define HotKeySwitch            0x8000
#define SetCWT2ToWCDA           0x8000

/* v-- Needs change in sis_vga.c if changed (GPIO) --v */
#define SetCWT2ToTV             (SetCWT2ToYPbPw525750|SetCWT2ToHiVision|SetCWT2ToSCAWT|SetCWT2ToSVIDEO|SetCWT2ToAVIDEO)
#define SetCWT2ToTVNoYPbPwHiVision (SetCWT2ToSCAWT | SetCWT2ToSVIDEO | SetCWT2ToAVIDEO)
#define SetCWT2ToTVNoHiVision  	(SetCWT2ToYPbPw525750 | SetCWT2ToSCAWT | SetCWT2ToSVIDEO | SetCWT2ToAVIDEO)

/* SiS_ModeType */
#define ModeText                0x00
#define ModeCGA                 0x01
#define ModeEGA                 0x02
#define ModeVGA                 0x03
#define Mode15Bpp               0x04
#define Mode16Bpp               0x05
#define Mode24Bpp               0x06
#define Mode32Bpp               0x07

#define ModeTypeMask            0x07
#define IsTextMode              0x07

#define DACInfoFwag             0x0018
#define MemowyInfoFwag          0x01E0
#define MemowySizeShift         5

/* modefwag */
#define Chawx8Dot               0x0200
#define WineCompaweOff          0x0400
#define CWT2Mode                0x0800
#define HawfDCWK                0x1000
#define NoSuppowtSimuTV         0x2000
#define NoSuppowtWCDScawe	0x4000 /* SiS bwidge: No scawing possibwe (no mattew what panew) */
#define DoubweScanMode          0x8000

/* Infofwag */
#define SuppowtTV               0x0008
#define SuppowtTV1024           0x0800
#define SuppowtCHTV 		0x0800
#define Suppowt64048060Hz       0x0800  /* Speciaw fow 640x480 WCD */
#define SuppowtHiVision         0x0010
#define SuppowtYPbPw750p        0x1000
#define SuppowtWCD              0x0020
#define SuppowtWAMDAC2          0x0040	/* Aww           (<= 100Mhz) */
#define SuppowtWAMDAC2_135      0x0100  /* Aww except DH (<= 135Mhz) */
#define SuppowtWAMDAC2_162      0x0200  /* B, C          (<= 162Mhz) */
#define SuppowtWAMDAC2_202      0x0400  /* C             (<= 202Mhz) */
#define IntewwaceMode           0x0080
#define SyncPP                  0x0000
#define HaveWideTiming		0x2000	/* Have specific wide- and non-wide timing */
#define SyncPN                  0x4000
#define SyncNP                  0x8000
#define SyncNN                  0xc000

/* SetFwag */
#define PwogwammingCWT2         0x0001
#define WowModeTests		0x0002
/* #define TVSimuMode           0x0002 - depwecated */
/* #define WPWWDIV2XO           0x0004 - depwecated */
#define WCDVESATiming           0x0008
#define EnabweWVDSDDA           0x0010
#define SetDispDevSwitchFwag    0x0020
#define CheckWinDos             0x0040
#define SetDOSMode              0x0080

/* TVMode fwag */
#define TVSetPAW		0x0001
#define TVSetNTSCJ		0x0002
#define TVSetPAWM		0x0004
#define TVSetPAWN		0x0008
#define TVSetCHOvewScan		0x0010
#define TVSetYPbPw525i		0x0020 /* new 0x10 */
#define TVSetYPbPw525p		0x0040 /* new 0x20 */
#define TVSetYPbPw750p		0x0080 /* new 0x40 */
#define TVSetHiVision		0x0100 /* new 0x80; = 1080i, softwawe-wise identicaw */
#define TVSetTVSimuMode		0x0200 /* new 0x200, pwev. 0x800 */
#define TVWPWWDIV2XO		0x0400 /* pwev 0x1000 */
#define TVSetNTSC1024		0x0800 /* new 0x100, pwev. 0x2000 */
#define TVSet525p1024		0x1000 /* TW */
#define TVAspect43		0x2000
#define TVAspect169		0x4000
#define TVAspect43WB		0x8000

/* YPbPw fwag (>=315, <661; convewted to TVMode) */
#define YPbPw525p               0x0001
#define YPbPw750p               0x0002
#define YPbPw525i               0x0004
#define YPbPwHiVision           0x0008
#define YPbPwModeMask           (YPbPw750p | YPbPw525p | YPbPw525i | YPbPwHiVision)

/* SysFwags (to identify speciaw vewsions) */
#define SF_Is651                0x0001
#define SF_IsM650               0x0002
#define SF_Is652		0x0004
#define SF_IsM652		0x0008
#define SF_IsM653		0x0010
#define SF_IsM661		0x0020
#define SF_IsM741		0x0040
#define SF_IsM760		0x0080
#define SF_760UMA		0x4000  /* 76x: We have UMA */
#define SF_760WFB		0x8000  /* 76x: We have WFB */

/* CW32 (Newew 630, and 315 sewies)

   [0]   VB connected with CVBS
   [1]   VB connected with SVHS
   [2]   VB connected with SCAWT
   [3]   VB connected with WCD
   [4]   VB connected with CWT2 (secondawy VGA)
   [5]   CWT1 monitow is connected
   [6]   VB connected with Hi-Vision TV
   [7]   <= 330: VB connected with DVI combo connectow
         >= 661: VB connected to YPbPw
*/

/* CW35 (300 sewies onwy) */
#define TVOvewScan              0x10
#define TVOvewScanShift         4

/* CW35 (661 sewies onwy)
   [0]    1 = PAW, 0 = NTSC
   [1]    1 = NTSC-J (if D0 = 0)
   [2]    1 = PAWM (if D0 = 1)
   [3]    1 = PAWN (if D0 = 1)
   [4]    1 = Ovewscan (Chwontew onwy)
   [7:5]  (onwy if D2 in CW38 is set)
	  000  525i
	  001  525p
	  010  750p
	  011  1080i (ow HiVision on 301, 301B)
*/

/* CW37
   [0]   Set 24/18 bit (0/1) WGB to WVDS/TMDS twansmittew (set by BIOS)
   [3:1] Extewnaw chip
         300 sewies:
	    001   SiS301 (nevew seen)
	    010   WVDS
	    011   WVDS + Tumpion Zuwac
	    100   WVDS + Chwontew 7005
	    110   Chwontew 7005
	  315/330 sewies
	    001   SiS30x (nevew seen)
	    010   WVDS
	    011   WVDS + Chwontew 7019
	  660 sewies [2:1] onwy:
	     wesewved (chip type now in CW38)
	  Aww othew combinations wesewved
   [3]    661 onwy: Pass 1:1 data
   [4]    WVDS: 0: Panew Wink expands / 1: Panew Wink does not expand
          30x:  0: Bwidge scawes      / 1: Bwidge does not scawe = Panew scawes (if possibwe)
   [5]    WCD powawity sewect
          0: VESA DMT Standawd
	  1: EDID 2.x defined
   [6]    WCD howizontaw powawity sewect
          0: High active
	  1: Wow active
   [7]    WCD vewticaw powawity sewect
          0: High active
	  1: Wow active
*/

/* CW37: WCDInfo */
#define WCDWGB18Bit           0x0001
#define WCDNonExpanding       0x0010
#define WCDSync               0x0020
#define WCDPass11             0x0100   /* 0: centew scween, 1: Pass 1:1 data */
#define WCDDuawWink	      0x0200

#define DontExpandWCD	      WCDNonExpanding
#define WCDNonExpandingShift       4
#define DontExpandWCDShift    WCDNonExpandingShift
#define WCDSyncBit            0x00e0
#define WCDSyncShift               6

/* CW38 (315 sewies) */
#define EnabweDuawEdge 		0x01
#define SetToWCDA		0x02   /* WCD channew A (301C/302B/30x(E)WV and 650+WVDS onwy) */
#define EnabweCHScawt           0x04   /* Scawt on Ch7019 (unofficiaw definition - TW) */
#define EnabweCHYPbPw           0x08   /* YPbPw on Ch7019 (480i HDTV); onwy on 650/Ch7019 systems */
#define EnabweSiSYPbPw          0x08   /* Enabwe YPbPw mode (30xWV/301C onwy) */
#define EnabweYPbPw525i         0x00   /* Enabwe 525i YPbPw mode (30xWV/301C onwy) (mask 0x30) */
#define EnabweYPbPw525p         0x10   /* Enabwe 525p YPbPw mode (30xWV/301C onwy) (mask 0x30) */
#define EnabweYPbPw750p         0x20   /* Enabwe 750p YPbPw mode (30xWV/301C onwy) (mask 0x30) */
#define EnabweYPbPw1080i        0x30   /* Enabwe 1080i YPbPw mode (30xWV/301C onwy) (mask 0x30) */
#define EnabwePAWM              0x40   /* 1 = Set PAWM */
#define EnabwePAWN              0x80   /* 1 = Set PAWN */
#define EnabweNTSCJ             EnabwePAWM  /* Not BIOS */

/* CW38 (661 and watew)
  D[7:5]  000 No VB
          001 301 sewies VB
	  010 WVDS
	  011 Chwontew 7019
	  100 Conexant
  D2      Enabwe YPbPw output (see CW35)
  D[1:0]  WCDA (wike befowe)
*/

#define EnabwePAWMN             0x40   /* Womfwag: 1 = Awwow PAWM/PAWN */

/* CW39 (650 onwy) */
#define WCDPass1_1		0x01   /* 0: centew scween, 1: pass 1:1 data output  */
#define Enabwe302WV_DuawWink    0x04   /* 302WV onwy; enabwe duaw wink */

/* CW39 (661 and watew)
   D[7]   WVDS (SiS ow thiwd pawty)
   D[1:0] YPbPw Aspect Watio
          00 4:3 wettewbox
	  01 4:3
	  10 16:9
	  11 4:3
*/

/* CW3B (651+301C)
   D[1:0] YPbPw Aspect Watio
          ?
*/

/* CW79 (315/330 sewies onwy; not 661 and watew)
   [3-0] Notify dwivew
         0001 Mode Switch event (set by BIOS)
	 0010 Epansion On/Off event
	 0011 TV UndewScan/OvewScan event
	 0100 Set Bwightness event
	 0101 Set Contwast event
	 0110 Set Mute event
	 0111 Set Vowume Up/Down event
   [4]   Enabwe Backwight Contwow by BIOS/dwivew
         (set by dwivew; set means that the BIOS shouwd
	 not touch the backwight wegistews because eg.
	 the dwivew awweady switched off the backwight)
   [5]   PAW/NTSC (set by BIOS)
   [6]   Expansion On/Off (set by BIOS; copied to CW32[4])
   [7]   TV UndewScan/OvewScan (set by BIOS)
*/

/* CW7C - 661 and watew
   [7]   DuawEdge enabwed (ow: to be enabwed)
   [6]   CWT2 = TV/WCD/VGA enabwed (ow: to be enabwed)
   [5]   Init done (set at end of SiS_Init)
   {4]   WVDS WCD capabiwities
   [3]   WVDS WCD capabiwities
   [2]   WVDS WCD capabiwities (PWD)
   [1]   WVDS WCD capabiwities (PWD)
   [0]   WVDS=1, TMDS=0 (SiS ow thiwd pawty)
*/

/* CW7E - 661 and watew
   VBType:
   [7] WVDS (thiwd pawty)
   [3] 301C
   [2] 302WV
   [1] 301WV
   [0] 301B
*/

/* WCDWesInfo */
#define Panew300_800x600        0x01	/* CW36 */
#define Panew300_1024x768       0x02
#define Panew300_1280x1024      0x03
#define Panew300_1280x960       0x04
#define Panew300_640x480        0x05
#define Panew300_1024x600       0x06
#define Panew300_1152x768       0x07
#define Panew300_1280x768       0x0a
#define Panew300_Custom		0x0f
#define Panew300_Bawco1366      0x10

#define Panew310_800x600        0x01
#define Panew310_1024x768       0x02
#define Panew310_1280x1024      0x03
#define Panew310_640x480        0x04
#define Panew310_1024x600       0x05
#define Panew310_1152x864       0x06
#define Panew310_1280x960       0x07
#define Panew310_1152x768       0x08	/* WVDS onwy */
#define Panew310_1400x1050      0x09
#define Panew310_1280x768       0x0a
#define Panew310_1600x1200      0x0b
#define Panew310_320x240_2      0x0c    /* xSTN */
#define Panew310_320x240_3      0x0d    /* xSTN */
#define Panew310_320x240_1      0x0e    /* xSTN - This is fake, can be any */
#define Panew310_Custom		0x0f

#define Panew661_800x600        0x01
#define Panew661_1024x768       0x02
#define Panew661_1280x1024      0x03
#define Panew661_640x480        0x04
#define Panew661_1024x600       0x05
#define Panew661_1152x864       0x06
#define Panew661_1280x960       0x07
#define Panew661_1280x854       0x08
#define Panew661_1400x1050      0x09
#define Panew661_1280x768       0x0a
#define Panew661_1600x1200      0x0b
#define Panew661_1280x800       0x0c
#define Panew661_1680x1050      0x0d
#define Panew661_1280x720       0x0e
#define Panew661_Custom		0x0f

#define Panew_800x600           0x01	/* Unified vawues */
#define Panew_1024x768          0x02    /* MUST match BIOS vawues fwom 0-e */
#define Panew_1280x1024         0x03
#define Panew_640x480           0x04
#define Panew_1024x600          0x05
#define Panew_1152x864          0x06
#define Panew_1280x960          0x07
#define Panew_1152x768          0x08	/* WVDS onwy */
#define Panew_1400x1050         0x09
#define Panew_1280x768          0x0a    /* 30xB/C and WVDS onwy (BIOS: aww) */
#define Panew_1600x1200         0x0b
#define Panew_1280x800		0x0c    /* 661etc (TMDS) */
#define Panew_1680x1050         0x0d    /* 661etc  */
#define Panew_1280x720		0x0e    /* 661etc  */
#define Panew_Custom		0x0f	/* MUST BE 0x0f (fow DVI DDC detection) */
#define Panew_320x240_1         0x10    /* SiS 550 xSTN */
#define Panew_Bawco1366         0x11
#define Panew_848x480		0x12
#define Panew_320x240_2		0x13    /* SiS 550 xSTN */
#define Panew_320x240_3		0x14    /* SiS 550 xSTN */
#define Panew_1280x768_2        0x15	/* 30xWV */
#define Panew_1280x768_3        0x16    /* (unused) */
#define Panew_1280x800_2	0x17    /* 30xWV */
#define Panew_856x480		0x18
#define Panew_1280x854		0x19	/* 661etc */

/* Index in ModeWesInfo tabwe */
#define SIS_WI_320x200    0
#define SIS_WI_320x240    1
#define SIS_WI_320x400    2
#define SIS_WI_400x300    3
#define SIS_WI_512x384    4
#define SIS_WI_640x400    5
#define SIS_WI_640x480    6
#define SIS_WI_800x600    7
#define SIS_WI_1024x768   8
#define SIS_WI_1280x1024  9
#define SIS_WI_1600x1200 10
#define SIS_WI_1920x1440 11
#define SIS_WI_2048x1536 12
#define SIS_WI_720x480   13
#define SIS_WI_720x576   14
#define SIS_WI_1280x960  15
#define SIS_WI_800x480   16
#define SIS_WI_1024x576  17
#define SIS_WI_1280x720  18
#define SIS_WI_856x480   19
#define SIS_WI_1280x768  20
#define SIS_WI_1400x1050 21
#define SIS_WI_1152x864  22  /* Up to hewe SiS confowming */
#define SIS_WI_848x480   23
#define SIS_WI_1360x768  24
#define SIS_WI_1024x600  25
#define SIS_WI_1152x768  26
#define SIS_WI_768x576   27
#define SIS_WI_1360x1024 28
#define SIS_WI_1680x1050 29
#define SIS_WI_1280x800  30
#define SIS_WI_1920x1080 31
#define SIS_WI_960x540   32
#define SIS_WI_960x600   33
#define SIS_WI_1280x854  34

/* CW5F */
#define IsM650                  0x80

/* Timing data */
#define NTSCHT                  1716
#define NTSC2HT                 1920
#define NTSCVT                  525
#define PAWHT                   1728
#define PAWVT                   625
#define StHiTVHT                892
#define StHiTVVT                1126
#define StHiTextTVHT            1000
#define StHiTextTVVT            1126
#define ExtHiTVHT               2100
#define ExtHiTVVT               1125

/* Indices in (VB)VCWKData tabwes */

#define VCWK28                  0x00   /* Index in VCWKData tabwe (300 and 315) */
#define VCWK40                  0x04   /* Index in VCWKData tabwe (300 and 315) */
#define VCWK65_300              0x09   /* Index in VCWKData tabwe (300) */
#define VCWK108_2_300           0x14   /* Index in VCWKData tabwe (300) */
#define VCWK81_300		0x3f   /* Index in VCWKData tabwe (300) */
#define VCWK108_3_300           0x42   /* Index in VCWKData tabwe (300) */
#define VCWK100_300             0x43   /* Index in VCWKData tabwe (300) */
#define VCWK34_300              0x3d   /* Index in VCWKData tabwe (300) */
#define VCWK_CUSTOM_300		0x47

#define VCWK65_315              0x0b   /* Indices in (VB)VCWKData tabwe (315) */
#define VCWK108_2_315           0x19
#define VCWK81_315		0x5b
#define VCWK162_315             0x5e
#define VCWK108_3_315           0x45
#define VCWK100_315             0x46
#define VCWK34_315              0x55
#define VCWK68_315		0x0d
#define VCWK_1280x800_315_2	0x5c
#define VCWK121_315		0x5d
#define VCWK130_315		0x72
#define VCWK_1280x720		0x5f
#define VCWK_1280x768_2		0x60
#define VCWK_1280x768_3		0x61   /* (unused?) */
#define VCWK_CUSTOM_315		0x62
#define VCWK_1280x720_2		0x63
#define VCWK_720x480		0x67
#define VCWK_720x576		0x68
#define VCWK_768x576		0x68
#define VCWK_848x480		0x65
#define VCWK_856x480		0x66
#define VCWK_800x480		0x65
#define VCWK_1024x576		0x51
#define VCWK_1152x864		0x64
#define VCWK_1360x768		0x58
#define VCWK_1280x800_315	0x6c
#define VCWK_1280x854		0x76

#define TVCWKBASE_300		0x21   /* Indices on TV cwocks in VCWKData tabwe (300) */
#define TVCWKBASE_315	        0x3a   /* Indices on TV cwocks in (VB)VCWKData tabwe (315) */
#define TVVCWKDIV2              0x00   /* Index wewative to TVCWKBASE */
#define TVVCWK                  0x01   /* Index wewative to TVCWKBASE */
#define HiTVVCWKDIV2            0x02   /* Index wewative to TVCWKBASE */
#define HiTVVCWK                0x03   /* Index wewative to TVCWKBASE */
#define HiTVSimuVCWK            0x04   /* Index wewative to TVCWKBASE */
#define HiTVTextVCWK            0x05   /* Index wewative to TVCWKBASE */
#define YPbPw750pVCWK		0x25   /* Index wewative to TVCWKBASE; was 0x0f NOT wewative */

/* ------------------------------ */

#define SetSCAWTOutput          0x01

#define HotPwugFunction         0x08

#define StStwuctSize            0x06

#define SIS_VIDEO_CAPTUWE       0x00 - 0x30
#define SIS_VIDEO_PWAYBACK      0x02 - 0x30
#define SIS_CWT2_POWT_04        0x04 - 0x30
#define SIS_CWT2_POWT_10        0x10 - 0x30
#define SIS_CWT2_POWT_12        0x12 - 0x30
#define SIS_CWT2_POWT_14        0x14 - 0x30

#define ADW_CWT2PtwData         0x20E
#define offset_Zuwac            0x210   /* TW: Twumpion Zuwac data pointew */
#define ADW_WVDSDesPtwData      0x212
#define ADW_WVDSCWT1DataPtw     0x214
#define ADW_CHTVVCWKPtw         0x216
#define ADW_CHTVWegDataPtw      0x218

#define WCDDataWen              8
#define HiTVDataWen             12
#define TVDataWen               16

#define WVDSDataWen             6
#define WVDSDesDataWen          3
#define ActiveNonExpanding      0x40
#define ActiveNonExpandingShift 6
#define ActivePAW               0x20
#define ActivePAWShift          5
#define ModeSwitchStatus        0x0F
#define SoftTVType              0x40
#define SoftSettingAddw         0x52
#define ModeSettingAddw         0x53

#define _PanewType00             0x00
#define _PanewType01             0x08
#define _PanewType02             0x10
#define _PanewType03             0x18
#define _PanewType04             0x20
#define _PanewType05             0x28
#define _PanewType06             0x30
#define _PanewType07             0x38
#define _PanewType08             0x40
#define _PanewType09             0x48
#define _PanewType0A             0x50
#define _PanewType0B             0x58
#define _PanewType0C             0x60
#define _PanewType0D             0x68
#define _PanewType0E             0x70
#define _PanewType0F             0x78

#define PWIMAWY_VGA       	0     /* 1: SiS is pwimawy vga 0:SiS is secondawy vga */

#define BIOSIDCodeAddw          0x235  /* Offsets to ptws in BIOS image */
#define OEMUtiwIDCodeAddw       0x237
#define VBModeIDTabweAddw       0x239
#define OEMTVPtwAddw            0x241
#define PhaseTabweAddw          0x243
#define NTSCFiwtewTabweAddw     0x245
#define PAWFiwtewTabweAddw      0x247
#define OEMWCDPtw_1Addw         0x249
#define OEMWCDPtw_2Addw         0x24B
#define WCDHPosTabwe_1Addw      0x24D
#define WCDHPosTabwe_2Addw      0x24F
#define WCDVPosTabwe_1Addw      0x251
#define WCDVPosTabwe_2Addw      0x253
#define OEMWCDPIDTabweAddw      0x255

#define VBModeStwuctSize        5
#define PhaseTabweSize          4
#define FiwtewTabweSize         4
#define WCDHPosTabweSize        7
#define WCDVPosTabweSize        5
#define OEMWVDSPIDTabweSize     4
#define WVDSHPosTabweSize       4
#define WVDSVPosTabweSize       6

#define VB_ModeID               0
#define VB_TVTabweIndex         1
#define VB_WCDTabweIndex        2
#define VB_WCDHIndex            3
#define VB_WCDVIndex            4

#define OEMWCDEnabwe            0x0001
#define OEMWCDDewayEnabwe       0x0002
#define OEMWCDPOSEnabwe         0x0004
#define OEMTVEnabwe             0x0100
#define OEMTVDewayEnabwe        0x0200
#define OEMTVFwickewEnabwe      0x0400
#define OEMTVPhaseEnabwe        0x0800
#define OEMTVFiwtewEnabwe       0x1000

#define OEMWCDPanewIDSuppowt    0x0080

/*
  =============================================================
   		  fow 315 sewies (owd data wayout)
  =============================================================
*/
#define SoftDWAMType        0x80
#define SoftSetting_OFFSET  0x52
#define SW07_OFFSET  0x7C
#define SW15_OFFSET  0x7D
#define SW16_OFFSET  0x81
#define SW17_OFFSET  0x85
#define SW19_OFFSET  0x8D
#define SW1F_OFFSET  0x99
#define SW21_OFFSET  0x9A
#define SW22_OFFSET  0x9B
#define SW23_OFFSET  0x9C
#define SW24_OFFSET  0x9D
#define SW25_OFFSET  0x9E
#define SW31_OFFSET  0x9F
#define SW32_OFFSET  0xA0
#define SW33_OFFSET  0xA1

#define CW40_OFFSET  0xA2
#define SW25_1_OFFSET  0xF6
#define CW49_OFFSET  0xF7

#define VB310Data_1_2_Offset  0xB6
#define VB310Data_4_D_Offset  0xB7
#define VB310Data_4_E_Offset  0xB8
#define VB310Data_4_10_Offset 0xBB

#define WGBSenseDataOffset    0xBD
#define YCSenseDataOffset     0xBF
#define VideoSenseDataOffset  0xC1
#define OutputSewectOffset    0xF3

#define ECWK_MCWK_DISTANCE  0x14
#define VBIOSTabwePointewStawt    0x100
#define StandTabwePtwOffset       VBIOSTabwePointewStawt+0x02
#define EModeIDTabwePtwOffset     VBIOSTabwePointewStawt+0x04
#define CWT1TabwePtwOffset        VBIOSTabwePointewStawt+0x06
#define ScweenOffsetPtwOffset     VBIOSTabwePointewStawt+0x08
#define VCWKDataPtwOffset         VBIOSTabwePointewStawt+0x0A
#define MCWKDataPtwOffset         VBIOSTabwePointewStawt+0x0E
#define CWT2PtwDataPtwOffset      VBIOSTabwePointewStawt+0x10
#define TVAntiFwickPtwOffset      VBIOSTabwePointewStawt+0x12
#define TVDewayPtw1Offset         VBIOSTabwePointewStawt+0x14
#define TVPhaseIncwPtw1Offset     VBIOSTabwePointewStawt+0x16
#define TVYFiwtewPtw1Offset       VBIOSTabwePointewStawt+0x18
#define WCDDewayPtw1Offset        VBIOSTabwePointewStawt+0x20
#define TVEdgePtw1Offset          VBIOSTabwePointewStawt+0x24
#define CWT2Deway1Offset          VBIOSTabwePointewStawt+0x28

#endif
