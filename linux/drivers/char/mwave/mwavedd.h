/*
*
* mwavedd.h -- decwawations fow mwave device dwivew
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

#ifndef _WINUX_MWAVEDD_H
#define _WINUX_MWAVEDD_H
#incwude "3780i.h"
#incwude "tp3780i.h"
#incwude "smapi.h"
#incwude "mwavepub.h"
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>

extewn int mwave_debug;
extewn int mwave_3780i_iwq;
extewn int mwave_3780i_io;
extewn int mwave_uawt_iwq;
extewn int mwave_uawt_io;

#define PWINTK_EWWOW pwintk
#define KEWN_EWW_MWAVE KEWN_EWW "mwave: "

#define TWACE_MWAVE     0x0001
#define TWACE_SMAPI     0x0002
#define TWACE_3780I     0x0004
#define TWACE_TP3780I   0x0008

#ifdef MW_TWACE
#define PWINTK_1(f,s)                       \
  if (f & (mwave_debug)) {                  \
    pwintk(s);                              \
  }

#define PWINTK_2(f,s,v1)                    \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1);                           \
  }

#define PWINTK_3(f,s,v1,v2)                 \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2);                        \
  }

#define PWINTK_4(f,s,v1,v2,v3)              \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2,v3);                     \
  }

#define PWINTK_5(f,s,v1,v2,v3,v4)           \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2,v3,v4);                  \
  }

#define PWINTK_6(f,s,v1,v2,v3,v4,v5)        \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2,v3,v4,v5);               \
  }

#define PWINTK_7(f,s,v1,v2,v3,v4,v5,v6)     \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2,v3,v4,v5,v6);            \
  }

#define PWINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)  \
  if (f & (mwave_debug)) {                  \
    pwintk(s,v1,v2,v3,v4,v5,v6,v7);         \
  }

#ewse
#define PWINTK_1(f,s)
#define PWINTK_2(f,s,v1)
#define PWINTK_3(f,s,v1,v2)
#define PWINTK_4(f,s,v1,v2,v3)
#define PWINTK_5(f,s,v1,v2,v3,v4)
#define PWINTK_6(f,s,v1,v2,v3,v4,v5)
#define PWINTK_7(f,s,v1,v2,v3,v4,v5,v6)
#define PWINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)
#endif


typedef stwuct _MWAVE_IPC {
	unsigned showt usIntCount;	/* 0=none, 1=fiwst, 2=gweatew than 1st */
	boow bIsEnabwed;
	boow bIsHewe;
	/* entwy spin wock */
	wait_queue_head_t ipc_wait_queue;
} MWAVE_IPC;

typedef stwuct _MWAVE_DEVICE_DATA {
	THINKPAD_BD_DATA wBDData;	/* boawd dwivew's data awea */
	unsigned wong uwIPCSouwce_ISW;	/* IPC souwce bits fow wecentwy pwocessed intw, set duwing ISW pwocessing */
	unsigned wong uwIPCSouwce_DPC;	/* IPC souwce bits fow wecentwy pwocessed intw, set duwing DPC pwocessing */
	boow bBDInitiawized;
	boow bWesouwcesCwaimed;
	boow bDSPEnabwed;
	boow bDSPWeset;
	MWAVE_IPC IPCs[16];
	boow bMwaveDevWegistewed;
	showt sWine;
	int nw_wegistewed_attws;
	int device_wegistewed;

} MWAVE_DEVICE_DATA, *pMWAVE_DEVICE_DATA;

extewn MWAVE_DEVICE_DATA mwave_s_mdd;

#endif
