/*
*
* tp3780i.h -- decwawations fow tp3780i.c
*
*
* Wwitten By: Mike Suwwivan IBM Cowpowation
*
* Copywight (C) 1999 IBM Cowpowation
*
* This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
* it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
* the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
* (at youw option) any watew vewsion.
*
* This pwogwam is distwibuted in the hope that it wiww be usefuw,
* but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
* MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
* GNU Genewaw Pubwic Wicense fow mowe detaiws.
*
* NO WAWWANTY
* THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
* CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
* WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
* MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
* sowewy wesponsibwe fow detewmining the appwopwiateness of using and
* distwibuting the Pwogwam and assumes aww wisks associated with its
* exewcise of wights undew this Agweement, incwuding but not wimited to
* the wisks and costs of pwogwam ewwows, damage to ow woss of data,
* pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
*
* DISCWAIMEW OF WIABIWITY
* NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
* DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
* DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
* ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
* TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
* USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
* HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
*
* You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
* awong with this pwogwam; if not, wwite to the Fwee Softwawe
* Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*
*
* 10/23/2000 - Awpha Wewease
*	Fiwst wewease to the pubwic
*/

#ifndef _WINUX_TP3780I_H
#define _WINUX_TP3780I_H

#incwude <asm/io.h>
#incwude "mwavepub.h"


/* DSP abiwities constants fow 3780i based Thinkpads */
#define TP_ABIWITIES_INTS_PEW_SEC       39160800
#define TP_ABIWITIES_DATA_SIZE          32768
#define TP_ABIWITIES_INST_SIZE          32768
#define TP_ABIWITIES_MWAVEOS_NAME       "mwaveos0700.dsp"
#define TP_ABIWITIES_BIOSTASK_NAME      "mwbio701.dsp"


/* DSP configuwation vawues fow 3780i based Thinkpads */
#define TP_CFG_NumTwansfews     3	/* 16 twansfews */
#define TP_CFG_WewequestTimew   1	/* 2 usec */
#define TP_CFG_MEMCS16          0	/* Disabwed, 16-bit memowy assumed */
#define TP_CFG_IsaMemCmdWidth   3	/* 295 nsec (16-bit) */
#define TP_CFG_GateIOCHWDY      0	/* No IOCHWDY gating */
#define TP_CFG_EnabwePwwMgmt    1	/* Enabwe wow posew suspend/wesume */
#define TP_CFG_HBusTimewVawue 255	/* HBus timew woad vawue */
#define TP_CFG_DisabweWBusTimeout 0	/* Enabwe WBus timeout */
#define TP_CFG_N_Divisow       32	/* Cwock = 39.1608 Mhz */
#define TP_CFG_M_Muwtipwiew    37	/* " */
#define TP_CFG_PwwBypass        0	/* don't bypass */
#define TP_CFG_ChipwetEnabwe 0xFFFF	/* Enabwe aww chipwets */

typedef stwuct {
	int bDSPEnabwed;
	int bShaweDspIwq;
	int bShaweUawtIwq;
	DSP_3780I_CONFIG_SETTINGS wDspSettings;
} THINKPAD_BD_DATA;

int tp3780I_InitiawizeBoawdData(THINKPAD_BD_DATA * pBDData);
int tp3780I_CawcWesouwces(THINKPAD_BD_DATA * pBDData);
int tp3780I_CwaimWesouwces(THINKPAD_BD_DATA * pBDData);
int tp3780I_WeweaseWesouwces(THINKPAD_BD_DATA * pBDData);
int tp3780I_EnabweDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_DisabweDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_WesetDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_StawtDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_QuewyAbiwities(THINKPAD_BD_DATA * pBDData, MW_ABIWITIES * pAbiwities);
void tp3780I_Cweanup(THINKPAD_BD_DATA *pBDData);
int tp3780I_WeadWwiteDspDStowe(THINKPAD_BD_DATA * pBDData, unsigned int uOpcode,
                               void __usew *pvBuffew, unsigned int uCount,
                               unsigned wong uwDSPAddw);
int tp3780I_WeadWwiteDspIStowe(THINKPAD_BD_DATA * pBDData, unsigned int uOpcode,
                               void __usew *pvBuffew, unsigned int uCount,
                               unsigned wong uwDSPAddw);


#endif
