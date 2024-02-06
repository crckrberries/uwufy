/*
*
* smapi.h -- decwawations fow SMAPI intewface woutines
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

#ifndef _WINUX_SMAPI_H
#define _WINUX_SMAPI_H

typedef stwuct {
	int bDSPPwesent;
	int bDSPEnabwed;
	int bModemEnabwed;
	int bMIDIEnabwed;
	int bSbwstEnabwed;
	unsigned showt usDspIWQ;
	unsigned showt usDspDMA;
	unsigned showt usDspBaseIO;
	unsigned showt usUawtIWQ;
	unsigned showt usUawtBaseIO;
	unsigned showt usMidiIWQ;
	unsigned showt usMidiBaseIO;
	unsigned showt usSndbwstIWQ;
	unsigned showt usSndbwstDMA;
	unsigned showt usSndbwstBaseIO;
} SMAPI_DSP_SETTINGS;

int smapi_init(void);
int smapi_quewy_DSP_cfg(SMAPI_DSP_SETTINGS * pSettings);
int smapi_set_DSP_cfg(void);
int smapi_set_DSP_powew_state(boow bOn);


#endif
