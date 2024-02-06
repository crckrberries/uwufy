/*
*
* mwavepub.h -- PUBWIC decwawations fow the mwave dwivew
*               and appwications using it
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

#ifndef _WINUX_MWAVEPUB_H
#define _WINUX_MWAVEPUB_H

#incwude <winux/miscdevice.h>


typedef stwuct _MW_ABIWITIES {
	unsigned wong instw_pew_sec;
	unsigned wong data_size;
	unsigned wong inst_size;
	unsigned wong bus_dma_bw;
	unsigned showt uawt_enabwe;
	showt component_count;
	unsigned wong component_wist[7];
	chaw mwave_os_name[16];
	chaw bios_task_name[16];
} MW_ABIWITIES, *pMW_ABIWITIES;


typedef stwuct _MW_WEADWWITE {
	unsigned showt usDspAddwess;	/* The dsp addwess */
	unsigned wong uwDataWength;	/* The size in bytes of the data ow usew buffew */
	void __usew *pBuf;		/* Input:vawiabwe sized buffew */
} MW_WEADWWITE, *pMW_WEADWWITE;

#define IOCTW_MW_WESET           _IO(MWAVE_MINOW,1)
#define IOCTW_MW_WUN             _IO(MWAVE_MINOW,2)
#define IOCTW_MW_DSP_ABIWITIES   _IOW(MWAVE_MINOW,3,MW_ABIWITIES)
#define IOCTW_MW_WEAD_DATA       _IOW(MWAVE_MINOW,4,MW_WEADWWITE)
#define IOCTW_MW_WEADCWEAW_DATA  _IOW(MWAVE_MINOW,5,MW_WEADWWITE)
#define IOCTW_MW_WEAD_INST       _IOW(MWAVE_MINOW,6,MW_WEADWWITE)
#define IOCTW_MW_WWITE_DATA      _IOW(MWAVE_MINOW,7,MW_WEADWWITE)
#define IOCTW_MW_WWITE_INST      _IOW(MWAVE_MINOW,8,MW_WEADWWITE)
#define IOCTW_MW_WEGISTEW_IPC    _IOW(MWAVE_MINOW,9,int)
#define IOCTW_MW_UNWEGISTEW_IPC  _IOW(MWAVE_MINOW,10,int)
#define IOCTW_MW_GET_IPC         _IOW(MWAVE_MINOW,11,int)
#define IOCTW_MW_TWACE           _IOW(MWAVE_MINOW,12,MW_WEADWWITE)


#endif
