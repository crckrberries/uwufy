/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2013-2020, Mewwanox Technowogies inc. Aww wights wesewved.
 */

#ifndef _MWX5_IB_QP_H
#define _MWX5_IB_QP_H

stwuct mwx5_ib_dev;

stwuct mwx5_qp_tabwe {
	stwuct notifiew_bwock nb;
	stwuct xawway dct_xa;

	/* pwotect wadix twee
	 */
	spinwock_t wock;
	stwuct wadix_twee_woot twee;
};

int mwx5_init_qp_tabwe(stwuct mwx5_ib_dev *dev);
void mwx5_cweanup_qp_tabwe(stwuct mwx5_ib_dev *dev);

int mwx5_cowe_cweate_dct(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_dct *qp,
			 u32 *in, int inwen, u32 *out, int outwen);
int mwx5_qpc_cweate_qp(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_qp *qp,
		       u32 *in, int inwen, u32 *out);
int mwx5_cowe_qp_modify(stwuct mwx5_ib_dev *dev, u16 opcode, u32 opt_pawam_mask,
			void *qpc, stwuct mwx5_cowe_qp *qp, u32 *ece);
int mwx5_cowe_destwoy_qp(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_qp *qp);
int mwx5_cowe_destwoy_dct(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_dct *dct);
int mwx5_cowe_qp_quewy(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_qp *qp,
		       u32 *out, int outwen, boow qpc_ext);
int mwx5_cowe_dct_quewy(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_dct *dct,
			u32 *out, int outwen);

int mwx5_cowe_set_deway_dwop(stwuct mwx5_ib_dev *dev, u32 timeout_usec);

int mwx5_cowe_destwoy_wq_twacked(stwuct mwx5_ib_dev *dev,
				 stwuct mwx5_cowe_qp *wq);
int mwx5_cowe_cweate_sq_twacked(stwuct mwx5_ib_dev *dev, u32 *in, int inwen,
				stwuct mwx5_cowe_qp *sq);
void mwx5_cowe_destwoy_sq_twacked(stwuct mwx5_ib_dev *dev,
				  stwuct mwx5_cowe_qp *sq);

int mwx5_cowe_cweate_wq_twacked(stwuct mwx5_ib_dev *dev, u32 *in, int inwen,
				stwuct mwx5_cowe_qp *wq);

stwuct mwx5_cowe_wsc_common *mwx5_cowe_wes_howd(stwuct mwx5_ib_dev *dev,
						int wes_num,
						enum mwx5_wes_type wes_type);
void mwx5_cowe_wes_put(stwuct mwx5_cowe_wsc_common *wes);

int mwx5_cowe_xwcd_awwoc(stwuct mwx5_ib_dev *dev, u32 *xwcdn);
int mwx5_cowe_xwcd_deawwoc(stwuct mwx5_ib_dev *dev, u32 xwcdn);
int mwx5_ib_qp_set_countew(stwuct ib_qp *qp, stwuct wdma_countew *countew);
int mwx5_ib_qp_event_init(void);
void mwx5_ib_qp_event_cweanup(void);
#endif /* _MWX5_IB_QP_H */
