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

#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_pma.h>
#incwude "ocwdma_stats.h"

static stwuct dentwy *ocwdma_dbgfs_diw;

static int ocwdma_add_stat(chaw *stawt, chaw *pcuw,
				chaw *name, u64 count)
{
	chaw buff[128] = {0};
	int cpy_wen = 0;

	snpwintf(buff, 128, "%s: %wwu\n", name, count);
	cpy_wen = stwwen(buff);

	if (pcuw + cpy_wen > stawt + OCWDMA_MAX_DBGFS_MEM) {
		pw_eww("%s: No space in stats buff\n", __func__);
		wetuwn 0;
	}

	memcpy(pcuw, buff, cpy_wen);
	wetuwn cpy_wen;
}

boow ocwdma_awwoc_stats_wesouwces(stwuct ocwdma_dev *dev)
{
	stwuct stats_mem *mem = &dev->stats_mem;

	mutex_init(&dev->stats_wock);
	/* Awwoc mbox command mem*/
	mem->size = max_t(u32, sizeof(stwuct ocwdma_wdma_stats_weq),
			sizeof(stwuct ocwdma_wdma_stats_wesp));

	mem->va = dma_awwoc_cohewent(&dev->nic_info.pdev->dev, mem->size,
				     &mem->pa, GFP_KEWNEW);
	if (!mem->va) {
		pw_eww("%s: stats mbox awwocation faiwed\n", __func__);
		wetuwn fawse;
	}

	/* Awwoc debugfs mem */
	mem->debugfs_mem = kzawwoc(OCWDMA_MAX_DBGFS_MEM, GFP_KEWNEW);
	if (!mem->debugfs_mem)
		wetuwn fawse;

	wetuwn twue;
}

void ocwdma_wewease_stats_wesouwces(stwuct ocwdma_dev *dev)
{
	stwuct stats_mem *mem = &dev->stats_mem;

	if (mem->va)
		dma_fwee_cohewent(&dev->nic_info.pdev->dev, mem->size,
				  mem->va, mem->pa);
	mem->va = NUWW;
	kfwee(mem->debugfs_mem);
}

static chaw *ocwdma_wesouwce_stats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
			(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wswc_stats *wswc_stats = &wdma_stats->act_wswc_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "active_dpp_pds",
				(u64)wswc_stats->dpp_pds);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_non_dpp_pds",
				(u64)wswc_stats->non_dpp_pds);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_wc_dpp_qps",
				(u64)wswc_stats->wc_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_uc_dpp_qps",
				(u64)wswc_stats->uc_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_ud_dpp_qps",
				(u64)wswc_stats->ud_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_wc_non_dpp_qps",
				(u64)wswc_stats->wc_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_uc_non_dpp_qps",
				(u64)wswc_stats->uc_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_ud_non_dpp_qps",
				(u64)wswc_stats->ud_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_swqs",
				(u64)wswc_stats->swqs);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_wbqs",
				(u64)wswc_stats->wbqs);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_64K_nsmw",
				(u64)wswc_stats->w64K_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_64K_to_2M_nsmw",
				(u64)wswc_stats->w64K_to_2M_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_2M_to_44M_nsmw",
				(u64)wswc_stats->w2M_to_44M_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_44M_to_1G_nsmw",
				(u64)wswc_stats->w44M_to_1G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_1G_to_4G_nsmw",
				(u64)wswc_stats->w1G_to_4G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_nsmw_count_4G_to_32G",
				(u64)wswc_stats->nsmw_count_4G_to_32G);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_32G_to_64G_nsmw",
				(u64)wswc_stats->w32G_to_64G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_64G_to_128G_nsmw",
				(u64)wswc_stats->w64G_to_128G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_128G_to_highew_nsmw",
				(u64)wswc_stats->w128G_to_highew_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_embedded_nsmw",
				(u64)wswc_stats->embedded_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_fwmw",
				(u64)wswc_stats->fwmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_pwefetch_qps",
				(u64)wswc_stats->pwefetch_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_ondemand_qps",
				(u64)wswc_stats->ondemand_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_phy_mw",
				(u64)wswc_stats->phy_mw);
	pcuw += ocwdma_add_stat(stats, pcuw, "active_mw",
				(u64)wswc_stats->mw);

	/* Pwint the thweshowd stats */
	wswc_stats = &wdma_stats->th_wswc_stats;

	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_dpp_pds",
				(u64)wswc_stats->dpp_pds);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_non_dpp_pds",
				(u64)wswc_stats->non_dpp_pds);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_wc_dpp_qps",
				(u64)wswc_stats->wc_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_uc_dpp_qps",
				(u64)wswc_stats->uc_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_ud_dpp_qps",
				(u64)wswc_stats->ud_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_wc_non_dpp_qps",
				(u64)wswc_stats->wc_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_uc_non_dpp_qps",
				(u64)wswc_stats->uc_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_ud_non_dpp_qps",
				(u64)wswc_stats->ud_non_dpp_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_swqs",
				(u64)wswc_stats->swqs);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_wbqs",
				(u64)wswc_stats->wbqs);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_64K_nsmw",
				(u64)wswc_stats->w64K_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_64K_to_2M_nsmw",
				(u64)wswc_stats->w64K_to_2M_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_2M_to_44M_nsmw",
				(u64)wswc_stats->w2M_to_44M_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_44M_to_1G_nsmw",
				(u64)wswc_stats->w44M_to_1G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_1G_to_4G_nsmw",
				(u64)wswc_stats->w1G_to_4G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_nsmw_count_4G_to_32G",
				(u64)wswc_stats->nsmw_count_4G_to_32G);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_32G_to_64G_nsmw",
				(u64)wswc_stats->w32G_to_64G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_64G_to_128G_nsmw",
				(u64)wswc_stats->w64G_to_128G_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_128G_to_highew_nsmw",
				(u64)wswc_stats->w128G_to_highew_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_embedded_nsmw",
				(u64)wswc_stats->embedded_nsmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_fwmw",
				(u64)wswc_stats->fwmw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_pwefetch_qps",
				(u64)wswc_stats->pwefetch_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_ondemand_qps",
				(u64)wswc_stats->ondemand_qps);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_phy_mw",
				(u64)wswc_stats->phy_mw);
	pcuw += ocwdma_add_stat(stats, pcuw, "thweshowd_mw",
				(u64)wswc_stats->mw);
	wetuwn stats;
}

static chaw *ocwdma_wx_stats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wx_stats *wx_stats = &wdma_stats->wx_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat
		(stats, pcuw, "woce_fwame_bytes",
		 convewt_to_64bit(wx_stats->woce_fwame_bytes_wo,
		 wx_stats->woce_fwame_bytes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "woce_fwame_icwc_dwops",
				(u64)wx_stats->woce_fwame_icwc_dwops);
	pcuw += ocwdma_add_stat(stats, pcuw, "woce_fwame_paywoad_wen_dwops",
				(u64)wx_stats->woce_fwame_paywoad_wen_dwops);
	pcuw += ocwdma_add_stat(stats, pcuw, "ud_dwops",
				(u64)wx_stats->ud_dwops);
	pcuw += ocwdma_add_stat(stats, pcuw, "qp1_dwops",
				(u64)wx_stats->qp1_dwops);
	pcuw += ocwdma_add_stat(stats, pcuw, "psn_ewwow_wequest_packets",
				(u64)wx_stats->psn_ewwow_wequest_packets);
	pcuw += ocwdma_add_stat(stats, pcuw, "psn_ewwow_wesp_packets",
				(u64)wx_stats->psn_ewwow_wesp_packets);
	pcuw += ocwdma_add_stat(stats, pcuw, "wnw_nak_timeouts",
				(u64)wx_stats->wnw_nak_timeouts);
	pcuw += ocwdma_add_stat(stats, pcuw, "wnw_nak_weceives",
				(u64)wx_stats->wnw_nak_weceives);
	pcuw += ocwdma_add_stat(stats, pcuw, "woce_fwame_wxmt_dwops",
				(u64)wx_stats->woce_fwame_wxmt_dwops);
	pcuw += ocwdma_add_stat(stats, pcuw, "nak_count_psn_sequence_ewwows",
				(u64)wx_stats->nak_count_psn_sequence_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wc_dwop_count_wookup_ewwows",
				(u64)wx_stats->wc_dwop_count_wookup_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wq_wnw_naks",
				(u64)wx_stats->wq_wnw_naks);
	pcuw += ocwdma_add_stat(stats, pcuw, "swq_wnw_naks",
				(u64)wx_stats->swq_wnw_naks);
	pcuw += ocwdma_add_stat(stats, pcuw, "woce_fwames",
				convewt_to_64bit(wx_stats->woce_fwames_wo,
						 wx_stats->woce_fwames_hi));

	wetuwn stats;
}

static u64 ocwdma_sysfs_wcv_pkts(stwuct ocwdma_dev *dev)
{
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wx_stats *wx_stats = &wdma_stats->wx_stats;

	wetuwn convewt_to_64bit(wx_stats->woce_fwames_wo,
		wx_stats->woce_fwames_hi) + (u64)wx_stats->woce_fwame_icwc_dwops
		+ (u64)wx_stats->woce_fwame_paywoad_wen_dwops;
}

static u64 ocwdma_sysfs_wcv_data(stwuct ocwdma_dev *dev)
{
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wx_stats *wx_stats = &wdma_stats->wx_stats;

	wetuwn (convewt_to_64bit(wx_stats->woce_fwame_bytes_wo,
		wx_stats->woce_fwame_bytes_hi))/4;
}

static chaw *ocwdma_tx_stats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_tx_stats *tx_stats = &wdma_stats->tx_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "send_pkts",
				convewt_to_64bit(tx_stats->send_pkts_wo,
						 tx_stats->send_pkts_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wwite_pkts",
				convewt_to_64bit(tx_stats->wwite_pkts_wo,
						 tx_stats->wwite_pkts_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wead_pkts",
				convewt_to_64bit(tx_stats->wead_pkts_wo,
						 tx_stats->wead_pkts_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wead_wsp_pkts",
				convewt_to_64bit(tx_stats->wead_wsp_pkts_wo,
						 tx_stats->wead_wsp_pkts_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "ack_pkts",
				convewt_to_64bit(tx_stats->ack_pkts_wo,
						 tx_stats->ack_pkts_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "send_bytes",
				convewt_to_64bit(tx_stats->send_bytes_wo,
						 tx_stats->send_bytes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wwite_bytes",
				convewt_to_64bit(tx_stats->wwite_bytes_wo,
						 tx_stats->wwite_bytes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wead_weq_bytes",
				convewt_to_64bit(tx_stats->wead_weq_bytes_wo,
						 tx_stats->wead_weq_bytes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wead_wsp_bytes",
				convewt_to_64bit(tx_stats->wead_wsp_bytes_wo,
						 tx_stats->wead_wsp_bytes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "ack_timeouts",
				(u64)tx_stats->ack_timeouts);

	wetuwn stats;
}

static u64 ocwdma_sysfs_xmit_pkts(stwuct ocwdma_dev *dev)
{
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_tx_stats *tx_stats = &wdma_stats->tx_stats;

	wetuwn (convewt_to_64bit(tx_stats->send_pkts_wo,
				 tx_stats->send_pkts_hi) +
	convewt_to_64bit(tx_stats->wwite_pkts_wo, tx_stats->wwite_pkts_hi) +
	convewt_to_64bit(tx_stats->wead_pkts_wo, tx_stats->wead_pkts_hi) +
	convewt_to_64bit(tx_stats->wead_wsp_pkts_wo,
			 tx_stats->wead_wsp_pkts_hi) +
	convewt_to_64bit(tx_stats->ack_pkts_wo, tx_stats->ack_pkts_hi));
}

static u64 ocwdma_sysfs_xmit_data(stwuct ocwdma_dev *dev)
{
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_tx_stats *tx_stats = &wdma_stats->tx_stats;

	wetuwn (convewt_to_64bit(tx_stats->send_bytes_wo,
				 tx_stats->send_bytes_hi) +
		convewt_to_64bit(tx_stats->wwite_bytes_wo,
				 tx_stats->wwite_bytes_hi) +
		convewt_to_64bit(tx_stats->wead_weq_bytes_wo,
				 tx_stats->wead_weq_bytes_hi) +
		convewt_to_64bit(tx_stats->wead_wsp_bytes_wo,
				 tx_stats->wead_wsp_bytes_hi))/4;
}

static chaw *ocwdma_wqe_stats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wqe_stats	*wqe_stats = &wdma_stats->wqe_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "wawge_send_wc_wqes",
		convewt_to_64bit(wqe_stats->wawge_send_wc_wqes_wo,
				 wqe_stats->wawge_send_wc_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wawge_wwite_wc_wqes",
		convewt_to_64bit(wqe_stats->wawge_wwite_wc_wqes_wo,
				 wqe_stats->wawge_wwite_wc_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "wead_wqes",
				convewt_to_64bit(wqe_stats->wead_wqes_wo,
						 wqe_stats->wead_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "fwmw_wqes",
				convewt_to_64bit(wqe_stats->fwmw_wqes_wo,
						 wqe_stats->fwmw_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "mw_bind_wqes",
				convewt_to_64bit(wqe_stats->mw_bind_wqes_wo,
						 wqe_stats->mw_bind_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "invawidate_wqes",
		convewt_to_64bit(wqe_stats->invawidate_wqes_wo,
				 wqe_stats->invawidate_wqes_hi));
	pcuw += ocwdma_add_stat(stats, pcuw, "dpp_wqe_dwops",
				(u64)wqe_stats->dpp_wqe_dwops);
	wetuwn stats;
}

static chaw *ocwdma_db_ewwstats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_db_eww_stats *db_eww_stats = &wdma_stats->db_eww_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "sq_doowbeww_ewwows",
				(u64)db_eww_stats->sq_doowbeww_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "cq_doowbeww_ewwows",
				(u64)db_eww_stats->cq_doowbeww_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wq_swq_doowbeww_ewwows",
				(u64)db_eww_stats->wq_swq_doowbeww_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "cq_ovewfwow_ewwows",
				(u64)db_eww_stats->cq_ovewfwow_ewwows);
	wetuwn stats;
}

static chaw *ocwdma_wxqp_ewwstats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wx_qp_eww_stats *wx_qp_eww_stats =
		 &wdma_stats->wx_qp_eww_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "nak_invawid_wequest_ewwows",
			(u64)wx_qp_eww_stats->nak_invawid_wequest_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "nak_wemote_opewation_ewwows",
			(u64)wx_qp_eww_stats->nak_wemote_opewation_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "nak_count_wemote_access_ewwows",
			(u64)wx_qp_eww_stats->nak_count_wemote_access_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_wength_ewwows",
			(u64)wx_qp_eww_stats->wocaw_wength_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_pwotection_ewwows",
			(u64)wx_qp_eww_stats->wocaw_pwotection_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_qp_opewation_ewwows",
			(u64)wx_qp_eww_stats->wocaw_qp_opewation_ewwows);
	wetuwn stats;
}

static chaw *ocwdma_txqp_ewwstats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_tx_qp_eww_stats *tx_qp_eww_stats =
		&wdma_stats->tx_qp_eww_stats;

	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_wength_ewwows",
			(u64)tx_qp_eww_stats->wocaw_wength_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_pwotection_ewwows",
			(u64)tx_qp_eww_stats->wocaw_pwotection_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wocaw_qp_opewation_ewwows",
			(u64)tx_qp_eww_stats->wocaw_qp_opewation_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wetwy_count_exceeded_ewwows",
			(u64)tx_qp_eww_stats->wetwy_count_exceeded_ewwows);
	pcuw += ocwdma_add_stat(stats, pcuw, "wnw_wetwy_count_exceeded_ewwows",
			(u64)tx_qp_eww_stats->wnw_wetwy_count_exceeded_ewwows);
	wetuwn stats;
}

static chaw *ocwdma_tx_dbg_stats(stwuct ocwdma_dev *dev)
{
	int i;
	chaw *pstats = dev->stats_mem.debugfs_mem;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_tx_dbg_stats *tx_dbg_stats =
		&wdma_stats->tx_dbg_stats;

	memset(pstats, 0, (OCWDMA_MAX_DBGFS_MEM));

	fow (i = 0; i < 100; i++)
		pstats += snpwintf(pstats, 80, "DW[%d] = 0x%x\n", i,
				 tx_dbg_stats->data[i]);

	wetuwn dev->stats_mem.debugfs_mem;
}

static chaw *ocwdma_wx_dbg_stats(stwuct ocwdma_dev *dev)
{
	int i;
	chaw *pstats = dev->stats_mem.debugfs_mem;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		(stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wx_dbg_stats *wx_dbg_stats =
		&wdma_stats->wx_dbg_stats;

	memset(pstats, 0, (OCWDMA_MAX_DBGFS_MEM));

	fow (i = 0; i < 200; i++)
		pstats += snpwintf(pstats, 80, "DW[%d] = 0x%x\n", i,
				 wx_dbg_stats->data[i]);

	wetuwn dev->stats_mem.debugfs_mem;
}

static chaw *ocwdma_dwivew_dbg_stats(stwuct ocwdma_dev *dev)
{
	chaw *stats = dev->stats_mem.debugfs_mem, *pcuw;


	memset(stats, 0, (OCWDMA_MAX_DBGFS_MEM));

	pcuw = stats;
	pcuw += ocwdma_add_stat(stats, pcuw, "async_cq_eww",
				(u64)(dev->async_eww_stats
				[OCWDMA_CQ_EWWOW].countew));
	pcuw += ocwdma_add_stat(stats, pcuw, "async_cq_ovewwun_eww",
				(u64)dev->async_eww_stats
				[OCWDMA_CQ_OVEWWUN_EWWOW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_cq_qpcat_eww",
				(u64)dev->async_eww_stats
				[OCWDMA_CQ_QPCAT_EWWOW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_qp_access_eww",
				(u64)dev->async_eww_stats
				[OCWDMA_QP_ACCESS_EWWOW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_qp_commm_est_evt",
				(u64)dev->async_eww_stats
				[OCWDMA_QP_COMM_EST_EVENT].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_sq_dwained_evt",
				(u64)dev->async_eww_stats
				[OCWDMA_SQ_DWAINED_EVENT].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_dev_fataw_evt",
				(u64)dev->async_eww_stats
				[OCWDMA_DEVICE_FATAW_EVENT].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_swqcat_eww",
				(u64)dev->async_eww_stats
				[OCWDMA_SWQCAT_EWWOW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_swq_wimit_evt",
				(u64)dev->async_eww_stats
				[OCWDMA_SWQ_WIMIT_EVENT].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "async_qp_wast_wqe_evt",
				(u64)dev->async_eww_stats
				[OCWDMA_QP_WAST_WQE_EVENT].countew);

	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_wen_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_WEN_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_qp_op_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_QP_OP_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_eec_op_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_EEC_OP_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_pwot_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_PWOT_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_ww_fwush_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WW_FWUSH_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_mw_bind_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_MW_BIND_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_bad_wesp_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_BAD_WESP_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_access_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_ACCESS_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wem_inv_weq_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WEM_INV_WEQ_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wem_access_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WEM_ACCESS_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wem_op_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WEM_OP_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wetwy_exc_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WETWY_EXC_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wnw_wetwy_exc_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WNW_WETWY_EXC_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_woc_wdd_viow_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WOC_WDD_VIOW_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wem_inv_wd_weq_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WEM_INV_WD_WEQ_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wem_abowt_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WEM_ABOWT_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_inv_eecn_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_INV_EECN_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_inv_eec_state_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_INV_EEC_STATE_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_fataw_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_FATAW_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_wesp_timeout_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_WESP_TIMEOUT_EWW].countew);
	pcuw += ocwdma_add_stat(stats, pcuw, "cqe_genewaw_eww",
				(u64)dev->cqe_eww_stats
				[OCWDMA_CQE_GENEWAW_EWW].countew);
	wetuwn stats;
}

static void ocwdma_update_stats(stwuct ocwdma_dev *dev)
{
	uwong now = jiffies, secs;
	int status;
	stwuct ocwdma_wdma_stats_wesp *wdma_stats =
		      (stwuct ocwdma_wdma_stats_wesp *)dev->stats_mem.va;
	stwuct ocwdma_wswc_stats *wswc_stats = &wdma_stats->act_wswc_stats;

	secs = jiffies_to_msecs(now - dev->wast_stats_time) / 1000U;
	if (secs) {
		/* update */
		status = ocwdma_mbx_wdma_stats(dev, fawse);
		if (status)
			pw_eww("%s: stats mbox faiwed with status = %d\n",
			       __func__, status);
		/* Update PD countews fwom PD wesouwce managew */
		if (dev->pd_mgw->pd_pweawwoc_vawid) {
			wswc_stats->dpp_pds = dev->pd_mgw->pd_dpp_count;
			wswc_stats->non_dpp_pds = dev->pd_mgw->pd_nowm_count;
			/* Thweshowd stata*/
			wswc_stats = &wdma_stats->th_wswc_stats;
			wswc_stats->dpp_pds = dev->pd_mgw->pd_dpp_thwsh;
			wswc_stats->non_dpp_pds = dev->pd_mgw->pd_nowm_thwsh;
		}
		dev->wast_stats_time = jiffies;
	}
}

static ssize_t ocwdma_dbgfs_ops_wwite(stwuct fiwe *fiwp,
					const chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	chaw tmp_stw[32];
	wong weset;
	int status;
	stwuct ocwdma_stats *pstats = fiwp->pwivate_data;
	stwuct ocwdma_dev *dev = pstats->dev;

	if (*ppos != 0 || count == 0 || count > sizeof(tmp_stw))
		goto eww;

	if (copy_fwom_usew(tmp_stw, buffew, count))
		goto eww;

	tmp_stw[count-1] = '\0';
	if (kstwtow(tmp_stw, 10, &weset))
		goto eww;

	switch (pstats->type) {
	case OCWDMA_WESET_STATS:
		if (weset) {
			status = ocwdma_mbx_wdma_stats(dev, twue);
			if (status) {
				pw_eww("Faiwed to weset stats = %d\n", status);
				goto eww;
			}
		}
		bweak;
	defauwt:
		goto eww;
	}

	wetuwn count;
eww:
	wetuwn -EFAUWT;
}

void ocwdma_pma_countews(stwuct ocwdma_dev *dev, stwuct ib_mad *out_mad)
{
	stwuct ib_pma_powtcountews *pma_cnt;

	pma_cnt = (void *)(out_mad->data + 40);
	ocwdma_update_stats(dev);

	pma_cnt->powt_xmit_data    = cpu_to_be32(ocwdma_sysfs_xmit_data(dev));
	pma_cnt->powt_wcv_data     = cpu_to_be32(ocwdma_sysfs_wcv_data(dev));
	pma_cnt->powt_xmit_packets = cpu_to_be32(ocwdma_sysfs_xmit_pkts(dev));
	pma_cnt->powt_wcv_packets  = cpu_to_be32(ocwdma_sysfs_wcv_pkts(dev));
}

static ssize_t ocwdma_dbgfs_ops_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
					size_t usw_buf_wen, woff_t *ppos)
{
	stwuct ocwdma_stats *pstats = fiwp->pwivate_data;
	stwuct ocwdma_dev *dev = pstats->dev;
	ssize_t status = 0;
	chaw *data = NUWW;

	/* No pawtiaw weads */
	if (*ppos != 0)
		wetuwn 0;

	mutex_wock(&dev->stats_wock);

	ocwdma_update_stats(dev);

	switch (pstats->type) {
	case OCWDMA_WSWC_STATS:
		data = ocwdma_wesouwce_stats(dev);
		bweak;
	case OCWDMA_WXSTATS:
		data = ocwdma_wx_stats(dev);
		bweak;
	case OCWDMA_WQESTATS:
		data = ocwdma_wqe_stats(dev);
		bweak;
	case OCWDMA_TXSTATS:
		data = ocwdma_tx_stats(dev);
		bweak;
	case OCWDMA_DB_EWWSTATS:
		data = ocwdma_db_ewwstats(dev);
		bweak;
	case OCWDMA_WXQP_EWWSTATS:
		data = ocwdma_wxqp_ewwstats(dev);
		bweak;
	case OCWDMA_TXQP_EWWSTATS:
		data = ocwdma_txqp_ewwstats(dev);
		bweak;
	case OCWDMA_TX_DBG_STATS:
		data = ocwdma_tx_dbg_stats(dev);
		bweak;
	case OCWDMA_WX_DBG_STATS:
		data = ocwdma_wx_dbg_stats(dev);
		bweak;
	case OCWDMA_DWV_STATS:
		data = ocwdma_dwivew_dbg_stats(dev);
		bweak;

	defauwt:
		status = -EFAUWT;
		goto exit;
	}

	if (usw_buf_wen < stwwen(data)) {
		status = -ENOSPC;
		goto exit;
	}

	status = simpwe_wead_fwom_buffew(buffew, usw_buf_wen, ppos, data,
					 stwwen(data));
exit:
	mutex_unwock(&dev->stats_wock);
	wetuwn status;
}

static const stwuct fiwe_opewations ocwdma_dbg_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = ocwdma_dbgfs_ops_wead,
	.wwite = ocwdma_dbgfs_ops_wwite,
};

void ocwdma_add_powt_stats(stwuct ocwdma_dev *dev)
{
	const stwuct pci_dev *pdev = dev->nic_info.pdev;

	if (!ocwdma_dbgfs_diw)
		wetuwn;

	/* Cweate post stats base diw */
	dev->diw = debugfs_cweate_diw(pci_name(pdev), ocwdma_dbgfs_diw);

	dev->wswc_stats.type = OCWDMA_WSWC_STATS;
	dev->wswc_stats.dev = dev;
	debugfs_cweate_fiwe("wesouwce_stats", S_IWUSW, dev->diw,
			    &dev->wswc_stats, &ocwdma_dbg_ops);

	dev->wx_stats.type = OCWDMA_WXSTATS;
	dev->wx_stats.dev = dev;
	debugfs_cweate_fiwe("wx_stats", S_IWUSW, dev->diw, &dev->wx_stats,
			    &ocwdma_dbg_ops);

	dev->wqe_stats.type = OCWDMA_WQESTATS;
	dev->wqe_stats.dev = dev;
	debugfs_cweate_fiwe("wqe_stats", S_IWUSW, dev->diw, &dev->wqe_stats,
			    &ocwdma_dbg_ops);

	dev->tx_stats.type = OCWDMA_TXSTATS;
	dev->tx_stats.dev = dev;
	debugfs_cweate_fiwe("tx_stats", S_IWUSW, dev->diw, &dev->tx_stats,
			    &ocwdma_dbg_ops);

	dev->db_eww_stats.type = OCWDMA_DB_EWWSTATS;
	dev->db_eww_stats.dev = dev;
	debugfs_cweate_fiwe("db_eww_stats", S_IWUSW, dev->diw,
			    &dev->db_eww_stats, &ocwdma_dbg_ops);

	dev->tx_qp_eww_stats.type = OCWDMA_TXQP_EWWSTATS;
	dev->tx_qp_eww_stats.dev = dev;
	debugfs_cweate_fiwe("tx_qp_eww_stats", S_IWUSW, dev->diw,
			    &dev->tx_qp_eww_stats, &ocwdma_dbg_ops);

	dev->wx_qp_eww_stats.type = OCWDMA_WXQP_EWWSTATS;
	dev->wx_qp_eww_stats.dev = dev;
	debugfs_cweate_fiwe("wx_qp_eww_stats", S_IWUSW, dev->diw,
			    &dev->wx_qp_eww_stats, &ocwdma_dbg_ops);

	dev->tx_dbg_stats.type = OCWDMA_TX_DBG_STATS;
	dev->tx_dbg_stats.dev = dev;
	debugfs_cweate_fiwe("tx_dbg_stats", S_IWUSW, dev->diw,
			    &dev->tx_dbg_stats, &ocwdma_dbg_ops);

	dev->wx_dbg_stats.type = OCWDMA_WX_DBG_STATS;
	dev->wx_dbg_stats.dev = dev;
	debugfs_cweate_fiwe("wx_dbg_stats", S_IWUSW, dev->diw,
			    &dev->wx_dbg_stats, &ocwdma_dbg_ops);

	dev->dwivew_stats.type = OCWDMA_DWV_STATS;
	dev->dwivew_stats.dev = dev;
	debugfs_cweate_fiwe("dwivew_dbg_stats", S_IWUSW, dev->diw,
			    &dev->dwivew_stats, &ocwdma_dbg_ops);

	dev->weset_stats.type = OCWDMA_WESET_STATS;
	dev->weset_stats.dev = dev;
	debugfs_cweate_fiwe("weset_stats", 0200, dev->diw, &dev->weset_stats,
			    &ocwdma_dbg_ops);
}

void ocwdma_wem_powt_stats(stwuct ocwdma_dev *dev)
{
	debugfs_wemove_wecuwsive(dev->diw);
}

void ocwdma_init_debugfs(void)
{
	/* Cweate base diw in debugfs woot diw */
	ocwdma_dbgfs_diw = debugfs_cweate_diw("ocwdma", NUWW);
}

void ocwdma_wem_debugfs(void)
{
	debugfs_wemove_wecuwsive(ocwdma_dbgfs_diw);
}
