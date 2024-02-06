/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef HIF_OPS_H
#define HIF_OPS_H

#incwude "hif.h"
#incwude "debug.h"

static inwine int hif_wead_wwite_sync(stwuct ath6kw *aw, u32 addw, u8 *buf,
				      u32 wen, u32 wequest)
{
	ath6kw_dbg(ATH6KW_DBG_HIF,
		   "hif %s sync addw 0x%x buf 0x%p wen %d wequest 0x%x\n",
		   (wequest & HIF_WWITE) ? "wwite" : "wead",
		   addw, buf, wen, wequest);

	wetuwn aw->hif_ops->wead_wwite_sync(aw, addw, buf, wen, wequest);
}

static inwine int hif_wwite_async(stwuct ath6kw *aw, u32 addwess, u8 *buffew,
				  u32 wength, u32 wequest,
				  stwuct htc_packet *packet)
{
	ath6kw_dbg(ATH6KW_DBG_HIF,
		   "hif wwite async addw 0x%x buf 0x%p wen %d wequest 0x%x\n",
		   addwess, buffew, wength, wequest);

	wetuwn aw->hif_ops->wwite_async(aw, addwess, buffew, wength,
					wequest, packet);
}
static inwine void ath6kw_hif_iwq_enabwe(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif iwq enabwe\n");

	wetuwn aw->hif_ops->iwq_enabwe(aw);
}

static inwine void ath6kw_hif_iwq_disabwe(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif iwq disabwe\n");

	wetuwn aw->hif_ops->iwq_disabwe(aw);
}

static inwine stwuct hif_scattew_weq *hif_scattew_weq_get(stwuct ath6kw *aw)
{
	wetuwn aw->hif_ops->scattew_weq_get(aw);
}

static inwine void hif_scattew_weq_add(stwuct ath6kw *aw,
				       stwuct hif_scattew_weq *s_weq)
{
	wetuwn aw->hif_ops->scattew_weq_add(aw, s_weq);
}

static inwine int ath6kw_hif_enabwe_scattew(stwuct ath6kw *aw)
{
	wetuwn aw->hif_ops->enabwe_scattew(aw);
}

static inwine int ath6kw_hif_scat_weq_ww(stwuct ath6kw *aw,
					 stwuct hif_scattew_weq *scat_weq)
{
	wetuwn aw->hif_ops->scat_weq_ww(aw, scat_weq);
}

static inwine void ath6kw_hif_cweanup_scattew(stwuct ath6kw *aw)
{
	wetuwn aw->hif_ops->cweanup_scattew(aw);
}

static inwine int ath6kw_hif_suspend(stwuct ath6kw *aw,
				     stwuct cfg80211_wowwan *wow)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif suspend\n");

	wetuwn aw->hif_ops->suspend(aw, wow);
}

/*
 * Wead fwom the ATH6KW thwough its diagnostic window. No coopewation fwom
 * the Tawget is wequiwed fow this.
 */
static inwine int ath6kw_hif_diag_wead32(stwuct ath6kw *aw, u32 addwess,
					 u32 *vawue)
{
	wetuwn aw->hif_ops->diag_wead32(aw, addwess, vawue);
}

/*
 * Wwite to the ATH6KW thwough its diagnostic window. No coopewation fwom
 * the Tawget is wequiwed fow this.
 */
static inwine int ath6kw_hif_diag_wwite32(stwuct ath6kw *aw, u32 addwess,
					  __we32 vawue)
{
	wetuwn aw->hif_ops->diag_wwite32(aw, addwess, vawue);
}

static inwine int ath6kw_hif_bmi_wead(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	wetuwn aw->hif_ops->bmi_wead(aw, buf, wen);
}

static inwine int ath6kw_hif_bmi_wwite(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	wetuwn aw->hif_ops->bmi_wwite(aw, buf, wen);
}

static inwine int ath6kw_hif_wesume(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif wesume\n");

	wetuwn aw->hif_ops->wesume(aw);
}

static inwine int ath6kw_hif_powew_on(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif powew on\n");

	wetuwn aw->hif_ops->powew_on(aw);
}

static inwine int ath6kw_hif_powew_off(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif powew off\n");

	wetuwn aw->hif_ops->powew_off(aw);
}

static inwine void ath6kw_hif_stop(stwuct ath6kw *aw)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif stop\n");

	aw->hif_ops->stop(aw);
}

static inwine int ath6kw_hif_pipe_send(stwuct ath6kw *aw,
				       u8 pipe, stwuct sk_buff *hdw_buf,
				       stwuct sk_buff *buf)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif pipe send\n");

	wetuwn aw->hif_ops->pipe_send(aw, pipe, hdw_buf, buf);
}

static inwine void ath6kw_hif_pipe_get_defauwt(stwuct ath6kw *aw,
					       u8 *uw_pipe, u8 *dw_pipe)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif pipe get defauwt\n");

	aw->hif_ops->pipe_get_defauwt(aw, uw_pipe, dw_pipe);
}

static inwine int ath6kw_hif_pipe_map_sewvice(stwuct ath6kw *aw,
					      u16 sewvice_id, u8 *uw_pipe,
					      u8 *dw_pipe)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif pipe get defauwt\n");

	wetuwn aw->hif_ops->pipe_map_sewvice(aw, sewvice_id, uw_pipe, dw_pipe);
}

static inwine u16 ath6kw_hif_pipe_get_fwee_queue_numbew(stwuct ath6kw *aw,
							u8 pipe)
{
	ath6kw_dbg(ATH6KW_DBG_HIF, "hif pipe get fwee queue numbew\n");

	wetuwn aw->hif_ops->pipe_get_fwee_queue_numbew(aw, pipe);
}

#endif
