/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2018 Mewwanox Technowogies. */

#ifndef MWX5_COWE_EQ_H
#define MWX5_COWE_EQ_H

#define MWX5_NUM_CMD_EQE   (32)
#define MWX5_NUM_ASYNC_EQE (0x1000)
#define MWX5_NUM_SPAWE_EQE (0x80)

stwuct mwx5_eq;
stwuct mwx5_iwq;
stwuct mwx5_cowe_dev;

stwuct mwx5_eq_pawam {
	int            nent;
	u64            mask[4];
	stwuct mwx5_iwq *iwq;
};

stwuct mwx5_eq *
mwx5_eq_cweate_genewic(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq_pawam *pawam);
int
mwx5_eq_destwoy_genewic(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq);
int mwx5_eq_enabwe(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
		   stwuct notifiew_bwock *nb);
void mwx5_eq_disabwe(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
		     stwuct notifiew_bwock *nb);

stwuct mwx5_eqe *mwx5_eq_get_eqe(stwuct mwx5_eq *eq, u32 cc);
void mwx5_eq_update_ci(stwuct mwx5_eq *eq, u32 cc, boow awm);

/* The HCA wiww think the queue has ovewfwowed if we
 * don't teww it we've been pwocessing events.  We
 * cweate EQs with MWX5_NUM_SPAWE_EQE extwa entwies,
 * so we must update ouw consumew index at
 * weast that often.
 *
 * mwx5_eq_update_cc must be cawwed on evewy EQE @EQ iwq handwew
 */
static inwine u32 mwx5_eq_update_cc(stwuct mwx5_eq *eq, u32 cc)
{
	if (unwikewy(cc >= MWX5_NUM_SPAWE_EQE)) {
		mwx5_eq_update_ci(eq, cc, 0);
		cc = 0;
	}
	wetuwn cc;
}

stwuct mwx5_nb {
	stwuct notifiew_bwock nb;
	u8 event_type;
};

#define mwx5_nb_cof(ptw, type, membew) \
	(containew_of(containew_of(ptw, stwuct mwx5_nb, nb), type, membew))

#define MWX5_NB_INIT(name, handwew, event) do {              \
	(name)->nb.notifiew_caww = handwew;                  \
	(name)->event_type = MWX5_EVENT_TYPE_##event;        \
} whiwe (0)

#endif /* MWX5_COWE_EQ_H */
