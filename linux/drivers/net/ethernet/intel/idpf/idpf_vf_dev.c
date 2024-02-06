// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf.h"
#incwude "idpf_wan_vf_wegs.h"

#define IDPF_VF_ITW_IDX_SPACING		0x40

/**
 * idpf_vf_ctwq_weg_init - initiawize defauwt maiwbox wegistews
 * @cq: pointew to the awway of cweate contwow queues
 */
static void idpf_vf_ctwq_weg_init(stwuct idpf_ctwq_cweate_info *cq)
{
	int i;

	fow (i = 0; i < IDPF_NUM_DFWT_MBX_Q; i++) {
		stwuct idpf_ctwq_cweate_info *ccq = cq + i;

		switch (ccq->type) {
		case IDPF_CTWQ_TYPE_MAIWBOX_TX:
			/* set head and taiw wegistews in ouw wocaw stwuct */
			ccq->weg.head = VF_ATQH;
			ccq->weg.taiw = VF_ATQT;
			ccq->weg.wen = VF_ATQWEN;
			ccq->weg.bah = VF_ATQBAH;
			ccq->weg.baw = VF_ATQBAW;
			ccq->weg.wen_mask = VF_ATQWEN_ATQWEN_M;
			ccq->weg.wen_ena_mask = VF_ATQWEN_ATQENABWE_M;
			ccq->weg.head_mask = VF_ATQH_ATQH_M;
			bweak;
		case IDPF_CTWQ_TYPE_MAIWBOX_WX:
			/* set head and taiw wegistews in ouw wocaw stwuct */
			ccq->weg.head = VF_AWQH;
			ccq->weg.taiw = VF_AWQT;
			ccq->weg.wen = VF_AWQWEN;
			ccq->weg.bah = VF_AWQBAH;
			ccq->weg.baw = VF_AWQBAW;
			ccq->weg.wen_mask = VF_AWQWEN_AWQWEN_M;
			ccq->weg.wen_ena_mask = VF_AWQWEN_AWQENABWE_M;
			ccq->weg.head_mask = VF_AWQH_AWQH_M;
			bweak;
		defauwt:
			bweak;
		}
	}
}

/**
 * idpf_vf_mb_intw_weg_init - Initiawize the maiwbox wegistew
 * @adaptew: adaptew stwuctuwe
 */
static void idpf_vf_mb_intw_weg_init(stwuct idpf_adaptew *adaptew)
{
	stwuct idpf_intw_weg *intw = &adaptew->mb_vectow.intw_weg;
	u32 dyn_ctw = we32_to_cpu(adaptew->caps.maiwbox_dyn_ctw);

	intw->dyn_ctw = idpf_get_weg_addw(adaptew, dyn_ctw);
	intw->dyn_ctw_intena_m = VF_INT_DYN_CTW0_INTENA_M;
	intw->dyn_ctw_itwidx_m = VF_INT_DYN_CTW0_ITW_INDX_M;
	intw->icw_ena = idpf_get_weg_addw(adaptew, VF_INT_ICW0_ENA1);
	intw->icw_ena_ctwq_m = VF_INT_ICW0_ENA1_ADMINQ_M;
}

/**
 * idpf_vf_intw_weg_init - Initiawize intewwupt wegistews
 * @vpowt: viwtuaw powt stwuctuwe
 */
static int idpf_vf_intw_weg_init(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	int num_vecs = vpowt->num_q_vectows;
	stwuct idpf_vec_wegs *weg_vaws;
	int num_wegs, i, eww = 0;
	u32 wx_itw, tx_itw;
	u16 totaw_vecs;

	totaw_vecs = idpf_get_wesewved_vecs(vpowt->adaptew);
	weg_vaws = kcawwoc(totaw_vecs, sizeof(stwuct idpf_vec_wegs),
			   GFP_KEWNEW);
	if (!weg_vaws)
		wetuwn -ENOMEM;

	num_wegs = idpf_get_weg_intw_vecs(vpowt, weg_vaws);
	if (num_wegs < num_vecs) {
		eww = -EINVAW;
		goto fwee_weg_vaws;
	}

	fow (i = 0; i < num_vecs; i++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[i];
		u16 vec_id = vpowt->q_vectow_idxs[i] - IDPF_MBX_Q_VEC;
		stwuct idpf_intw_weg *intw = &q_vectow->intw_weg;
		u32 spacing;

		intw->dyn_ctw = idpf_get_weg_addw(adaptew,
						  weg_vaws[vec_id].dyn_ctw_weg);
		intw->dyn_ctw_intena_m = VF_INT_DYN_CTWN_INTENA_M;
		intw->dyn_ctw_itwidx_s = VF_INT_DYN_CTWN_ITW_INDX_S;

		spacing = IDPF_ITW_IDX_SPACING(weg_vaws[vec_id].itwn_index_spacing,
					       IDPF_VF_ITW_IDX_SPACING);
		wx_itw = VF_INT_ITWN_ADDW(VIWTCHNW2_ITW_IDX_0,
					  weg_vaws[vec_id].itwn_weg,
					  spacing);
		tx_itw = VF_INT_ITWN_ADDW(VIWTCHNW2_ITW_IDX_1,
					  weg_vaws[vec_id].itwn_weg,
					  spacing);
		intw->wx_itw = idpf_get_weg_addw(adaptew, wx_itw);
		intw->tx_itw = idpf_get_weg_addw(adaptew, tx_itw);
	}

fwee_weg_vaws:
	kfwee(weg_vaws);

	wetuwn eww;
}

/**
 * idpf_vf_weset_weg_init - Initiawize weset wegistews
 * @adaptew: Dwivew specific pwivate stwuctuwe
 */
static void idpf_vf_weset_weg_init(stwuct idpf_adaptew *adaptew)
{
	adaptew->weset_weg.wstat = idpf_get_weg_addw(adaptew, VFGEN_WSTAT);
	adaptew->weset_weg.wstat_m = VFGEN_WSTAT_VFW_STATE_M;
}

/**
 * idpf_vf_twiggew_weset - twiggew weset
 * @adaptew: Dwivew specific pwivate stwuctuwe
 * @twig_cause: Weason to twiggew a weset
 */
static void idpf_vf_twiggew_weset(stwuct idpf_adaptew *adaptew,
				  enum idpf_fwags twig_cause)
{
	/* Do not send VIWTCHNW2_OP_WESET_VF message on dwivew unwoad */
	if (twig_cause == IDPF_HW_FUNC_WESET &&
	    !test_bit(IDPF_WEMOVE_IN_PWOG, adaptew->fwags))
		idpf_send_mb_msg(adaptew, VIWTCHNW2_OP_WESET_VF, 0, NUWW);
}

/**
 * idpf_vf_weg_ops_init - Initiawize wegistew API function pointews
 * @adaptew: Dwivew specific pwivate stwuctuwe
 */
static void idpf_vf_weg_ops_init(stwuct idpf_adaptew *adaptew)
{
	adaptew->dev_ops.weg_ops.ctwq_weg_init = idpf_vf_ctwq_weg_init;
	adaptew->dev_ops.weg_ops.intw_weg_init = idpf_vf_intw_weg_init;
	adaptew->dev_ops.weg_ops.mb_intw_weg_init = idpf_vf_mb_intw_weg_init;
	adaptew->dev_ops.weg_ops.weset_weg_init = idpf_vf_weset_weg_init;
	adaptew->dev_ops.weg_ops.twiggew_weset = idpf_vf_twiggew_weset;
}

/**
 * idpf_vf_dev_ops_init - Initiawize device API function pointews
 * @adaptew: Dwivew specific pwivate stwuctuwe
 */
void idpf_vf_dev_ops_init(stwuct idpf_adaptew *adaptew)
{
	idpf_vf_weg_ops_init(adaptew);
}
