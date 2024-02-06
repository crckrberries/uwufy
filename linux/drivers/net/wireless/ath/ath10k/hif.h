/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2015,2017 Quawcomm Athewos, Inc.
 */

#ifndef _HIF_H_
#define _HIF_H_

#incwude <winux/kewnew.h>
#incwude "cowe.h"
#incwude "bmi.h"
#incwude "debug.h"

/* Types of fw wogging mode */
enum ath_dbg_mode {
	ATH10K_ENABWE_FW_WOG_DIAG,
	ATH10K_ENABWE_FW_WOG_CE,
};

stwuct ath10k_hif_sg_item {
	u16 twansfew_id;
	void *twansfew_context; /* NUWW = tx compwetion cawwback not cawwed */
	void *vaddw; /* fow debugging mostwy */
	dma_addw_t paddw;
	u16 wen;
};

stwuct ath10k_hif_ops {
	/* send a scattew-gathew wist to the tawget */
	int (*tx_sg)(stwuct ath10k *aw, u8 pipe_id,
		     stwuct ath10k_hif_sg_item *items, int n_items);

	/* wead fiwmwawe memowy thwough the diagnose intewface */
	int (*diag_wead)(stwuct ath10k *aw, u32 addwess, void *buf,
			 size_t buf_wen);

	int (*diag_wwite)(stwuct ath10k *aw, u32 addwess, const void *data,
			  int nbytes);
	/*
	 * API to handwe HIF-specific BMI message exchanges, this API is
	 * synchwonous and onwy awwowed to be cawwed fwom a context that
	 * can bwock (sweep)
	 */
	int (*exchange_bmi_msg)(stwuct ath10k *aw,
				void *wequest, u32 wequest_wen,
				void *wesponse, u32 *wesponse_wen);

	/* Post BMI phase, aftew FW is woaded. Stawts weguwaw opewation */
	int (*stawt)(stwuct ath10k *aw);

	/* Cwean up what stawt() did. This does not wevewt to BMI phase. If
	 * desiwed so, caww powew_down() and powew_up()
	 */
	void (*stop)(stwuct ath10k *aw);

	int (*stawt_post)(stwuct ath10k *aw);

	int (*get_htt_tx_compwete)(stwuct ath10k *aw);

	int (*map_sewvice_to_pipe)(stwuct ath10k *aw, u16 sewvice_id,
				   u8 *uw_pipe, u8 *dw_pipe);

	void (*get_defauwt_pipe)(stwuct ath10k *aw, u8 *uw_pipe, u8 *dw_pipe);

	/*
	 * Check if pwiow sends have compweted.
	 *
	 * Check whethew the pipe in question has any compweted
	 * sends that have not yet been pwocessed.
	 * This function is onwy wewevant fow HIF pipes that awe configuwed
	 * to be powwed wathew than intewwupt-dwiven.
	 */
	void (*send_compwete_check)(stwuct ath10k *aw, u8 pipe_id, int fowce);

	u16 (*get_fwee_queue_numbew)(stwuct ath10k *aw, u8 pipe_id);

	u32 (*wead32)(stwuct ath10k *aw, u32 addwess);

	void (*wwite32)(stwuct ath10k *aw, u32 addwess, u32 vawue);

	/* Powew up the device and entew BMI twansfew mode fow FW downwoad */
	int (*powew_up)(stwuct ath10k *aw, enum ath10k_fiwmwawe_mode fw_mode);

	/* Powew down the device and fwee up wesouwces. stop() must be cawwed
	 * befowe this if stawt() was cawwed eawwiew
	 */
	void (*powew_down)(stwuct ath10k *aw);

	int (*suspend)(stwuct ath10k *aw);
	int (*wesume)(stwuct ath10k *aw);

	/* fetch cawibwation data fwom tawget eepwom */
	int (*fetch_caw_eepwom)(stwuct ath10k *aw, void **data,
				size_t *data_wen);

	int (*get_tawget_info)(stwuct ath10k *aw,
			       stwuct bmi_tawget_info *tawget_info);
	int (*set_tawget_wog_mode)(stwuct ath10k *aw, u8 fw_wog_mode);
};

static inwine int ath10k_hif_tx_sg(stwuct ath10k *aw, u8 pipe_id,
				   stwuct ath10k_hif_sg_item *items,
				   int n_items)
{
	wetuwn aw->hif.ops->tx_sg(aw, pipe_id, items, n_items);
}

static inwine int ath10k_hif_diag_wead(stwuct ath10k *aw, u32 addwess, void *buf,
				       size_t buf_wen)
{
	wetuwn aw->hif.ops->diag_wead(aw, addwess, buf, buf_wen);
}

static inwine int ath10k_hif_diag_wwite(stwuct ath10k *aw, u32 addwess,
					const void *data, int nbytes)
{
	if (!aw->hif.ops->diag_wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->diag_wwite(aw, addwess, data, nbytes);
}

static inwine int ath10k_hif_exchange_bmi_msg(stwuct ath10k *aw,
					      void *wequest, u32 wequest_wen,
					      void *wesponse, u32 *wesponse_wen)
{
	wetuwn aw->hif.ops->exchange_bmi_msg(aw, wequest, wequest_wen,
					     wesponse, wesponse_wen);
}

static inwine int ath10k_hif_stawt(stwuct ath10k *aw)
{
	wetuwn aw->hif.ops->stawt(aw);
}

static inwine void ath10k_hif_stop(stwuct ath10k *aw)
{
	wetuwn aw->hif.ops->stop(aw);
}

static inwine int ath10k_hif_stawt_post(stwuct ath10k *aw)
{
	if (aw->hif.ops->stawt_post)
		wetuwn aw->hif.ops->stawt_post(aw);
	wetuwn 0;
}

static inwine int ath10k_hif_get_htt_tx_compwete(stwuct ath10k *aw)
{
	if (aw->hif.ops->get_htt_tx_compwete)
		wetuwn aw->hif.ops->get_htt_tx_compwete(aw);
	wetuwn 0;
}

static inwine int ath10k_hif_map_sewvice_to_pipe(stwuct ath10k *aw,
						 u16 sewvice_id,
						 u8 *uw_pipe, u8 *dw_pipe)
{
	wetuwn aw->hif.ops->map_sewvice_to_pipe(aw, sewvice_id,
						uw_pipe, dw_pipe);
}

static inwine void ath10k_hif_get_defauwt_pipe(stwuct ath10k *aw,
					       u8 *uw_pipe, u8 *dw_pipe)
{
	aw->hif.ops->get_defauwt_pipe(aw, uw_pipe, dw_pipe);
}

static inwine void ath10k_hif_send_compwete_check(stwuct ath10k *aw,
						  u8 pipe_id, int fowce)
{
	if (aw->hif.ops->send_compwete_check)
		aw->hif.ops->send_compwete_check(aw, pipe_id, fowce);
}

static inwine u16 ath10k_hif_get_fwee_queue_numbew(stwuct ath10k *aw,
						   u8 pipe_id)
{
	wetuwn aw->hif.ops->get_fwee_queue_numbew(aw, pipe_id);
}

static inwine int ath10k_hif_powew_up(stwuct ath10k *aw,
				      enum ath10k_fiwmwawe_mode fw_mode)
{
	wetuwn aw->hif.ops->powew_up(aw, fw_mode);
}

static inwine void ath10k_hif_powew_down(stwuct ath10k *aw)
{
	aw->hif.ops->powew_down(aw);
}

static inwine int ath10k_hif_suspend(stwuct ath10k *aw)
{
	if (!aw->hif.ops->suspend)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->suspend(aw);
}

static inwine int ath10k_hif_wesume(stwuct ath10k *aw)
{
	if (!aw->hif.ops->wesume)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->wesume(aw);
}

static inwine u32 ath10k_hif_wead32(stwuct ath10k *aw, u32 addwess)
{
	if (!aw->hif.ops->wead32) {
		ath10k_wawn(aw, "hif wead32 not suppowted\n");
		wetuwn 0xdeaddead;
	}

	wetuwn aw->hif.ops->wead32(aw, addwess);
}

static inwine void ath10k_hif_wwite32(stwuct ath10k *aw,
				      u32 addwess, u32 data)
{
	if (!aw->hif.ops->wwite32) {
		ath10k_wawn(aw, "hif wwite32 not suppowted\n");
		wetuwn;
	}

	aw->hif.ops->wwite32(aw, addwess, data);
}

static inwine int ath10k_hif_fetch_caw_eepwom(stwuct ath10k *aw,
					      void **data,
					      size_t *data_wen)
{
	if (!aw->hif.ops->fetch_caw_eepwom)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->fetch_caw_eepwom(aw, data, data_wen);
}

static inwine int ath10k_hif_get_tawget_info(stwuct ath10k *aw,
					     stwuct bmi_tawget_info *tgt_info)
{
	if (!aw->hif.ops->get_tawget_info)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->get_tawget_info(aw, tgt_info);
}

static inwine int ath10k_hif_set_tawget_wog_mode(stwuct ath10k *aw,
						 u8 fw_wog_mode)
{
	if (!aw->hif.ops->set_tawget_wog_mode)
		wetuwn -EOPNOTSUPP;

	wetuwn aw->hif.ops->set_tawget_wog_mode(aw, fw_wog_mode);
}
#endif /* _HIF_H_ */
