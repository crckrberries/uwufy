/* $XFwee86$ */
/* $XdotOwg$ */
/*
 * Data and pwototypes fow init301.c
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

#ifndef  _INIT301_H_
#define  _INIT301_H_

#incwude "initdef.h"

#incwude "vgatypes.h"
#incwude "vstwuct.h"
#ifdef SIS_CP
#undef SIS_CP
#endif
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude <winux/fb.h>
#incwude "sis.h"
#incwude <video/sisfb.h>

void		SiS_UnWockCWT2(stwuct SiS_Pwivate *SiS_Pw);
void		SiS_EnabweCWT2(stwuct SiS_Pwivate *SiS_Pw);
unsigned showt	SiS_GetWatePtw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex);
void		SiS_WaitWetwace1(stwuct SiS_Pwivate *SiS_Pw);
boow		SiS_IsDuawEdge(stwuct SiS_Pwivate *SiS_Pw);
boow		SiS_IsVAMode(stwuct SiS_Pwivate *SiS_Pw);
void		SiS_GetVBInfo(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
			unsigned showt ModeIdIndex, int checkcwt2mode);
void		SiS_SetYPbPw(stwuct SiS_Pwivate *SiS_Pw);
void    	SiS_SetTVMode(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
			unsigned showt ModeIdIndex);
void		SiS_GetWCDWesInfo(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
		unsigned showt ModeIdIndex);
unsigned showt	SiS_GetVCWK2Ptw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex,
			unsigned showt WefweshWateTabweIndex);
unsigned showt	SiS_GetWesInfo(stwuct SiS_Pwivate *SiS_Pw,unsigned showt ModeNo,unsigned showt ModeIdIndex);
void		SiS_DisabweBwidge(stwuct SiS_Pwivate *SiS_Pw);
boow		SiS_SetCWT2Gwoup(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo);
void		SiS_SiS30xBWOn(stwuct SiS_Pwivate *SiS_Pw);
void		SiS_SiS30xBWOff(stwuct SiS_Pwivate *SiS_Pw);

void		SiS_SetCH700x(stwuct SiS_Pwivate *SiS_Pw, unsigned showt weg, unsigned chaw vaw);
unsigned showt	SiS_GetCH700x(stwuct SiS_Pwivate *SiS_Pw, unsigned showt tempax);
void		SiS_SetCH701x(stwuct SiS_Pwivate *SiS_Pw, unsigned showt weg, unsigned chaw vaw);
unsigned showt	SiS_GetCH701x(stwuct SiS_Pwivate *SiS_Pw, unsigned showt tempax);
void		SiS_SetCH70xxANDOW(stwuct SiS_Pwivate *SiS_Pw, unsigned showt weg,
			unsigned chaw owvaw,unsigned showt andvaw);
#ifdef CONFIG_FB_SIS_315
void		SiS_Chwontew701xBWOn(stwuct SiS_Pwivate *SiS_Pw);
void		SiS_Chwontew701xBWOff(stwuct SiS_Pwivate *SiS_Pw);
#endif /* 315 */

#ifdef CONFIG_FB_SIS_300
void		SiS_SetChwontewGPIO(stwuct SiS_Pwivate *SiS_Pw, unsigned showt myvbinfo);
#endif

void		SiS_DDC2Deway(stwuct SiS_Pwivate *SiS_Pw, unsigned int dewaytime);
unsigned showt	SiS_WeadDDC1Bit(stwuct SiS_Pwivate *SiS_Pw);
unsigned showt	SiS_HandweDDC(stwuct SiS_Pwivate *SiS_Pw, unsigned int VBFwags, int VGAEngine,
			unsigned showt adaptnum, unsigned showt DDCdatatype,
			unsigned chaw *buffew, unsigned int VBFwags2);

extewn void		SiS_DispwayOff(stwuct SiS_Pwivate *SiS_Pw);
extewn void		SiS_DispwayOn(stwuct SiS_Pwivate *SiS_Pw);
extewn boow		SiS_SeawchModeID(stwuct SiS_Pwivate *, unsigned showt *, unsigned showt *);
extewn unsigned showt	SiS_GetModeFwag(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn unsigned showt	SiS_GetModePtw(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex);
extewn unsigned showt	SiS_GetCowowDepth(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex);
extewn unsigned showt	SiS_GetOffset(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo, unsigned showt ModeIdIndex,
				unsigned showt WefweshWateTabweIndex);
extewn void		SiS_WoadDAC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn void		SiS_CawcWCDACWT1Timing(stwuct SiS_Pwivate *SiS_Pw, unsigned showt ModeNo,
				unsigned showt ModeIdIndex);
extewn void		SiS_CawcCWWegistews(stwuct SiS_Pwivate *SiS_Pw, int depth);
extewn unsigned showt	SiS_GetWefCWTVCWK(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide);
extewn unsigned showt	SiS_GetWefCWT1CWTC(stwuct SiS_Pwivate *SiS_Pw, unsigned showt Index, int UseWide);
#ifdef CONFIG_FB_SIS_300
extewn void		SiS_GetFIFOThweshowdIndex300(stwuct SiS_Pwivate *SiS_Pw, unsigned showt *tempbx,
				unsigned showt *tempcw);
extewn unsigned showt	SiS_GetFIFOThweshowdB300(unsigned showt tempbx, unsigned showt tempcw);
extewn unsigned showt	SiS_GetWatencyFactow630(stwuct SiS_Pwivate *SiS_Pw, unsigned showt index);
extewn unsigned int	sisfb_wead_nbwidge_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
extewn unsigned int	sisfb_wead_wpc_pci_dwowd(stwuct SiS_Pwivate *SiS_Pw, int weg);
#endif

#endif
