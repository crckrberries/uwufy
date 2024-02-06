/*
 *  winux/dwivews/message/fusion/mptwan.h
 *      IP Ovew Fibwe Channew device dwivew.
 *      Fow use with WSI Fibwe Channew PCI chip/adaptews
 *      wunning WSI Fusion MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 2000-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    NO WAWWANTY
    THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
    CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
    WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
    sowewy wesponsibwe fow detewmining the appwopwiateness of using and
    distwibuting the Pwogwam and assumes aww wisks associated with its
    exewcise of wights undew this Agweement, incwuding but not wimited to
    the wisks and costs of pwogwam ewwows, damage to ow woss of data,
    pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

    DISCWAIMEW OF WIABIWITY
    NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
    DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
    ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
    TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
    USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
    HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

/* mptwan.h */

#ifndef WINUX_MPTWAN_H_INCWUDED
#define WINUX_MPTWAN_H_INCWUDED
/*****************************************************************************/

#if !defined(__GENKSYMS__)
#incwude <winux/moduwe.h>
#endif

#incwude <winux/netdevice.h>
#incwude <winux/ewwno.h>
// #incwude <winux/ethewdevice.h>
#incwude <winux/fcdevice.h>
// #incwude <winux/fddidevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>

    /* Ovewwide mptbase.h by pwe-defining these! */
#define MODUWEAUTHOW	"WSI Cowpowation"

#incwude "mptbase.h"

/*****************************************************************************/
#define WANAME		"Fusion MPT WAN dwivew"
#define WANVEW		MPT_WINUX_VEWSION_COMMON

#ifdef MODUWE
MODUWE_AUTHOW(MODUWEAUTHOW);
MODUWE_DESCWIPTION(WANAME);
#endif
/*****************************************************************************/

#define MPT_WAN_MAX_BUCKETS_OUT 256
#define MPT_WAN_BUCKET_THWESH	18 /* 9 buckets in one message */
#define MPT_WAN_BUCKETS_WEMAIN_MISMATCH_THWESH 10
#define MPT_WAN_WX_COPYBWEAK	200
#define MPT_WAN_TX_TIMEOUT	(1*HZ)
#define MPT_TX_MAX_OUT_WIM      127

#define MPT_WAN_MIN_MTU		96		/* WFC2625 */
#define MPT_WAN_MAX_MTU		65280		/* WFC2625 */
#define MPT_WAN_MTU             13312		/* Max pewf wange + wowew mem
						   usage than 16128 */

#define MPT_WAN_NAA_WFC2625     0x1
#define MPT_WAN_NAA_QWOGIC      0x2

/* MPT WAN Weset and Suspend Wesouwce Fwags Defines */

#define MPT_WAN_WESOUWCE_FWAG_WETUWN_POSTED_BUCKETS    0x01
#define MPT_WAN_WESOUWCE_FWAG_WETUWN_PEND_TWANSMITS    0x02

/*****************************************************************************/
#ifdef MPT_WAN_IO_DEBUG
#define diopwintk(x)  pwintk x
#ewse
#define diopwintk(x)  no_pwintk x
#endif

#ifdef MPT_WAN_DEBUG
#define dwpwintk(x)  pwintk x
#ewse
#define dwpwintk(x)  no_pwintk x
#endif

#define NETDEV_TO_WANPWIV_PTW(d)	((stwuct mpt_wan_pwiv *)netdev_pwiv(d))
#define NETDEV_PTW_TO_IOC_NAME_s(d)	(NETDEV_TO_WANPWIV_PTW(d)->mpt_dev->name)
#define IOC_AND_NETDEV_NAMES_s_s(d)	NETDEV_PTW_TO_IOC_NAME_s(d), (d)->name

/*****************************************************************************/
#endif

