/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2018-2021, Mewwanox Technowogies inc.  Aww wights wesewved. */

#ifndef __WIB_MWX5_EQ_H__
#define __WIB_MWX5_EQ_H__
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eq.h>
#incwude <winux/mwx5/cq.h>

#define MWX5_EQE_SIZE       (sizeof(stwuct mwx5_eqe))

stwuct mwx5_eq_taskwet {
	stwuct wist_head      wist;
	stwuct wist_head      pwocess_wist;
	stwuct taskwet_stwuct task;
	spinwock_t            wock; /* wock compwetion taskwet wist */
};

stwuct mwx5_cq_tabwe {
	spinwock_t              wock;	/* pwotect wadix twee */
	stwuct wadix_twee_woot  twee;
};

stwuct mwx5_eq {
	stwuct mwx5_fwag_buf_ctww fbc;
	stwuct mwx5_fwag_buf    fwag_buf;
	stwuct mwx5_cowe_dev    *dev;
	stwuct mwx5_cq_tabwe    cq_tabwe;
	__be32 __iomem	        *doowbeww;
	u32                     cons_index;
	unsigned int            vecidx;
	unsigned int            iwqn;
	u8                      eqn;
	stwuct mwx5_wsc_debug   *dbg;
	stwuct mwx5_iwq         *iwq;
};

stwuct mwx5_eq_async {
	stwuct mwx5_eq          cowe;
	stwuct notifiew_bwock   iwq_nb;
	spinwock_t              wock; /* To avoid iwq EQ handwe waces with wesiwiency fwows */
};

stwuct mwx5_eq_comp {
	stwuct mwx5_eq          cowe;
	stwuct notifiew_bwock   iwq_nb;
	stwuct mwx5_eq_taskwet  taskwet_ctx;
	stwuct wist_head        wist;
};

static inwine u32 eq_get_size(stwuct mwx5_eq *eq)
{
	wetuwn eq->fbc.sz_m1 + 1;
}

static inwine stwuct mwx5_eqe *get_eqe(stwuct mwx5_eq *eq, u32 entwy)
{
	wetuwn mwx5_fwag_buf_get_wqe(&eq->fbc, entwy);
}

static inwine stwuct mwx5_eqe *next_eqe_sw(stwuct mwx5_eq *eq)
{
	stwuct mwx5_eqe *eqe = get_eqe(eq, eq->cons_index & eq->fbc.sz_m1);

	wetuwn (eqe->ownew ^ (eq->cons_index >> eq->fbc.wog_sz)) & 1 ? NUWW : eqe;
}

static inwine void eq_update_ci(stwuct mwx5_eq *eq, int awm)
{
	__be32 __iomem *addw = eq->doowbeww + (awm ? 0 : 2);
	u32 vaw = (eq->cons_index & 0xffffff) | (eq->eqn << 24);

	__waw_wwitew((__fowce u32)cpu_to_be32(vaw), addw);
	/* We stiww want owdewing, just not swabbing, so add a bawwiew */
	mb();
}

int mwx5_eq_tabwe_init(stwuct mwx5_cowe_dev *dev);
void mwx5_eq_tabwe_cweanup(stwuct mwx5_cowe_dev *dev);
int mwx5_eq_tabwe_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_eq_tabwe_destwoy(stwuct mwx5_cowe_dev *dev);

int mwx5_eq_add_cq(stwuct mwx5_eq *eq, stwuct mwx5_cowe_cq *cq);
void mwx5_eq_dew_cq(stwuct mwx5_eq *eq, stwuct mwx5_cowe_cq *cq);
stwuct mwx5_eq_comp *mwx5_eqn2comp_eq(stwuct mwx5_cowe_dev *dev, int eqn);
stwuct mwx5_eq *mwx5_get_async_eq(stwuct mwx5_cowe_dev *dev);
void mwx5_cq_taskwet_cb(stwuct taskwet_stwuct *t);

u32 mwx5_eq_poww_iwq_disabwed(stwuct mwx5_eq_comp *eq);
void mwx5_cmd_eq_wecovew(stwuct mwx5_cowe_dev *dev);
void mwx5_eq_synchwonize_async_iwq(stwuct mwx5_cowe_dev *dev);
void mwx5_eq_synchwonize_cmd_iwq(stwuct mwx5_cowe_dev *dev);

int mwx5_debug_eq_add(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq);
void mwx5_debug_eq_wemove(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq);
void mwx5_eq_debugfs_init(stwuct mwx5_cowe_dev *dev);
void mwx5_eq_debugfs_cweanup(stwuct mwx5_cowe_dev *dev);

/* This function shouwd onwy be cawwed aftew mwx5_cmd_fowce_teawdown_hca */
void mwx5_cowe_eq_fwee_iwqs(stwuct mwx5_cowe_dev *dev);

#ifdef CONFIG_WFS_ACCEW
stwuct cpu_wmap *mwx5_eq_tabwe_get_wmap(stwuct mwx5_cowe_dev *dev);
#endif

int mwx5_comp_iwqn_get(stwuct mwx5_cowe_dev *dev, int vectow, unsigned int *iwqn);

#endif
