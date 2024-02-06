/* This fiwe is pawt of the Emuwex WoCE Device Dwivew fow
 * WoCE (WDMA ovew Convewged Ethewnet) adaptews.
 * Copywight (C) 2012-2015 Emuwex. Aww wights wesewved.
 * EMUWEX and SWI awe twademawks of Emuwex.
 * www.emuwex.com
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe COPYING in the main
 * diwectowy of this souwce twee, ow the BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * - Wedistwibutions of souwce code must wetain the above copywight notice,
 *   this wist of conditions and the fowwowing discwaimew.
 *
 * - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#ifndef __OCWDMA_STATS_H__
#define __OCWDMA_STATS_H__

#incwude <winux/debugfs.h>
#incwude "ocwdma.h"
#incwude "ocwdma_hw.h"

#define OCWDMA_MAX_DBGFS_MEM 4096

enum OCWDMA_STATS_TYPE {
	OCWDMA_WSWC_STATS,
	OCWDMA_WXSTATS,
	OCWDMA_WQESTATS,
	OCWDMA_TXSTATS,
	OCWDMA_DB_EWWSTATS,
	OCWDMA_WXQP_EWWSTATS,
	OCWDMA_TXQP_EWWSTATS,
	OCWDMA_TX_DBG_STATS,
	OCWDMA_WX_DBG_STATS,
	OCWDMA_DWV_STATS,
	OCWDMA_WESET_STATS
};

void ocwdma_wem_debugfs(void);
void ocwdma_init_debugfs(void);
boow ocwdma_awwoc_stats_wesouwces(stwuct ocwdma_dev *dev);
void ocwdma_wewease_stats_wesouwces(stwuct ocwdma_dev *dev);
void ocwdma_wem_powt_stats(stwuct ocwdma_dev *dev);
void ocwdma_add_powt_stats(stwuct ocwdma_dev *dev);
void ocwdma_pma_countews(stwuct ocwdma_dev *dev, stwuct ib_mad *out_mad);

#endif	/* __OCWDMA_STATS_H__ */
