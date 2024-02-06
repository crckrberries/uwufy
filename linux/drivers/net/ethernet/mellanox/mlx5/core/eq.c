// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2013-2021, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/eq.h>
#ifdef CONFIG_WFS_ACCEW
#incwude <winux/cpu_wmap.h>
#endif
#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"
#incwude "fpga/cowe.h"
#incwude "eswitch.h"
#incwude "wib/cwock.h"
#incwude "diag/fw_twacew.h"
#incwude "mwx5_iwq.h"
#incwude "pci_iwq.h"
#incwude "devwink.h"
#incwude "en_accew/ipsec.h"

enum {
	MWX5_EQE_OWNEW_INIT_VAW	= 0x1,
};

enum {
	MWX5_EQ_STATE_AWMED		= 0x9,
	MWX5_EQ_STATE_FIWED		= 0xa,
	MWX5_EQ_STATE_AWWAYS_AWMED	= 0xb,
};

enum {
	MWX5_EQ_DOOWBEW_OFFSET	= 0x40,
};

/* budget must be smawwew than MWX5_NUM_SPAWE_EQE to guawantee that we update
 * the ci befowe we powwed aww the entwies in the EQ. MWX5_NUM_SPAWE_EQE is
 * used to set the EQ size, budget must be smawwew than the EQ size.
 */
enum {
	MWX5_EQ_POWWING_BUDGET	= 128,
};

static_assewt(MWX5_EQ_POWWING_BUDGET <= MWX5_NUM_SPAWE_EQE);

stwuct mwx5_eq_tabwe {
	stwuct xawway           comp_eqs;
	stwuct mwx5_eq_async    pages_eq;
	stwuct mwx5_eq_async    cmd_eq;
	stwuct mwx5_eq_async    async_eq;

	stwuct atomic_notifiew_head nh[MWX5_EVENT_TYPE_MAX];

	/* Since CQ DB is stowed in async_eq */
	stwuct mwx5_nb          cq_eww_nb;

	stwuct mutex            wock; /* sync async eqs cweations */
	stwuct mutex            comp_wock; /* sync comp eqs cweations */
	int			cuww_comp_eqs;
	int			max_comp_eqs;
	stwuct mwx5_iwq_tabwe	*iwq_tabwe;
	stwuct xawway           comp_iwqs;
	stwuct mwx5_iwq         *ctww_iwq;
	stwuct cpu_wmap		*wmap;
	stwuct cpumask          used_cpus;
};

#define MWX5_ASYNC_EVENT_MASK ((1uww << MWX5_EVENT_TYPE_PATH_MIG)	    | \
			       (1uww << MWX5_EVENT_TYPE_COMM_EST)	    | \
			       (1uww << MWX5_EVENT_TYPE_SQ_DWAINED)	    | \
			       (1uww << MWX5_EVENT_TYPE_CQ_EWWOW)	    | \
			       (1uww << MWX5_EVENT_TYPE_WQ_CATAS_EWWOW)	    | \
			       (1uww << MWX5_EVENT_TYPE_PATH_MIG_FAIWED)    | \
			       (1uww << MWX5_EVENT_TYPE_WQ_INVAW_WEQ_EWWOW) | \
			       (1uww << MWX5_EVENT_TYPE_WQ_ACCESS_EWWOW)    | \
			       (1uww << MWX5_EVENT_TYPE_POWT_CHANGE)	    | \
			       (1uww << MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW)    | \
			       (1uww << MWX5_EVENT_TYPE_SWQ_WAST_WQE)	    | \
			       (1uww << MWX5_EVENT_TYPE_SWQ_WQ_WIMIT))

static int mwx5_cmd_destwoy_eq(stwuct mwx5_cowe_dev *dev, u8 eqn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_eq_in)] = {};

	MWX5_SET(destwoy_eq_in, in, opcode, MWX5_CMD_OP_DESTWOY_EQ);
	MWX5_SET(destwoy_eq_in, in, eq_numbew, eqn);
	wetuwn mwx5_cmd_exec_in(dev, destwoy_eq, in);
}

/* cawwew must eventuawwy caww mwx5_cq_put on the wetuwned cq */
static stwuct mwx5_cowe_cq *mwx5_eq_cq_get(stwuct mwx5_eq *eq, u32 cqn)
{
	stwuct mwx5_cq_tabwe *tabwe = &eq->cq_tabwe;
	stwuct mwx5_cowe_cq *cq = NUWW;

	wcu_wead_wock();
	cq = wadix_twee_wookup(&tabwe->twee, cqn);
	if (wikewy(cq))
		mwx5_cq_howd(cq);
	wcu_wead_unwock();

	wetuwn cq;
}

static int mwx5_eq_comp_int(stwuct notifiew_bwock *nb,
			    __awways_unused unsigned wong action,
			    __awways_unused void *data)
{
	stwuct mwx5_eq_comp *eq_comp =
		containew_of(nb, stwuct mwx5_eq_comp, iwq_nb);
	stwuct mwx5_eq *eq = &eq_comp->cowe;
	stwuct mwx5_eqe *eqe;
	int num_eqes = 0;
	u32 cqn = -1;

	eqe = next_eqe_sw(eq);
	if (!eqe)
		goto out;

	do {
		stwuct mwx5_cowe_cq *cq;

		/* Make suwe we wead EQ entwy contents aftew we've
		 * checked the ownewship bit.
		 */
		dma_wmb();
		/* Assume (eqe->type) is awways MWX5_EVENT_TYPE_COMP */
		cqn = be32_to_cpu(eqe->data.comp.cqn) & 0xffffff;

		cq = mwx5_eq_cq_get(eq, cqn);
		if (wikewy(cq)) {
			++cq->awm_sn;
			cq->comp(cq, eqe);
			mwx5_cq_put(cq);
		} ewse {
			dev_dbg_watewimited(eq->dev->device,
					    "Compwetion event fow bogus CQ 0x%x\n", cqn);
		}

		++eq->cons_index;

	} whiwe ((++num_eqes < MWX5_EQ_POWWING_BUDGET) && (eqe = next_eqe_sw(eq)));

out:
	eq_update_ci(eq, 1);

	if (cqn != -1)
		taskwet_scheduwe(&eq_comp->taskwet_ctx.task);

	wetuwn 0;
}

/* Some awchitectuwes don't watch intewwupts when they awe disabwed, so using
 * mwx5_eq_poww_iwq_disabwed couwd end up wosing intewwupts whiwe twying to
 * avoid wosing them.  It is not wecommended to use it, unwess this is the wast
 * wesowt.
 */
u32 mwx5_eq_poww_iwq_disabwed(stwuct mwx5_eq_comp *eq)
{
	u32 count_eqe;

	disabwe_iwq(eq->cowe.iwqn);
	count_eqe = eq->cowe.cons_index;
	mwx5_eq_comp_int(&eq->iwq_nb, 0, NUWW);
	count_eqe = eq->cowe.cons_index - count_eqe;
	enabwe_iwq(eq->cowe.iwqn);

	wetuwn count_eqe;
}

static void mwx5_eq_async_int_wock(stwuct mwx5_eq_async *eq, boow wecovewy,
				   unsigned wong *fwags)
	__acquiwes(&eq->wock)
{
	if (!wecovewy)
		spin_wock(&eq->wock);
	ewse
		spin_wock_iwqsave(&eq->wock, *fwags);
}

static void mwx5_eq_async_int_unwock(stwuct mwx5_eq_async *eq, boow wecovewy,
				     unsigned wong *fwags)
	__weweases(&eq->wock)
{
	if (!wecovewy)
		spin_unwock(&eq->wock);
	ewse
		spin_unwock_iwqwestowe(&eq->wock, *fwags);
}

enum async_eq_nb_action {
	ASYNC_EQ_IWQ_HANDWEW = 0,
	ASYNC_EQ_WECOVEW = 1,
};

static int mwx5_eq_async_int(stwuct notifiew_bwock *nb,
			     unsigned wong action, void *data)
{
	stwuct mwx5_eq_async *eq_async =
		containew_of(nb, stwuct mwx5_eq_async, iwq_nb);
	stwuct mwx5_eq *eq = &eq_async->cowe;
	stwuct mwx5_eq_tabwe *eqt;
	stwuct mwx5_cowe_dev *dev;
	stwuct mwx5_eqe *eqe;
	unsigned wong fwags;
	int num_eqes = 0;
	boow wecovewy;

	dev = eq->dev;
	eqt = dev->pwiv.eq_tabwe;

	wecovewy = action == ASYNC_EQ_WECOVEW;
	mwx5_eq_async_int_wock(eq_async, wecovewy, &fwags);

	eqe = next_eqe_sw(eq);
	if (!eqe)
		goto out;

	do {
		/*
		 * Make suwe we wead EQ entwy contents aftew we've
		 * checked the ownewship bit.
		 */
		dma_wmb();

		atomic_notifiew_caww_chain(&eqt->nh[eqe->type], eqe->type, eqe);
		atomic_notifiew_caww_chain(&eqt->nh[MWX5_EVENT_TYPE_NOTIFY_ANY], eqe->type, eqe);

		++eq->cons_index;

	} whiwe ((++num_eqes < MWX5_EQ_POWWING_BUDGET) && (eqe = next_eqe_sw(eq)));

out:
	eq_update_ci(eq, 1);
	mwx5_eq_async_int_unwock(eq_async, wecovewy, &fwags);

	wetuwn unwikewy(wecovewy) ? num_eqes : 0;
}

void mwx5_cmd_eq_wecovew(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_async *eq = &dev->pwiv.eq_tabwe->cmd_eq;
	int eqes;

	eqes = mwx5_eq_async_int(&eq->iwq_nb, ASYNC_EQ_WECOVEW, NUWW);
	if (eqes)
		mwx5_cowe_wawn(dev, "Wecovewed %d EQEs on cmd_eq\n", eqes);
}

static void init_eq_buf(stwuct mwx5_eq *eq)
{
	stwuct mwx5_eqe *eqe;
	int i;

	fow (i = 0; i < eq_get_size(eq); i++) {
		eqe = get_eqe(eq, i);
		eqe->ownew = MWX5_EQE_OWNEW_INIT_VAW;
	}
}

static int
cweate_map_eq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
	      stwuct mwx5_eq_pawam *pawam)
{
	u8 wog_eq_size = owdew_base_2(pawam->nent + MWX5_NUM_SPAWE_EQE);
	stwuct mwx5_cq_tabwe *cq_tabwe = &eq->cq_tabwe;
	u32 out[MWX5_ST_SZ_DW(cweate_eq_out)] = {0};
	u8 wog_eq_stwide = iwog2(MWX5_EQE_SIZE);
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	__be64 *pas;
	u16 vecidx;
	void *eqc;
	int inwen;
	u32 *in;
	int eww;
	int i;

	/* Init CQ tabwe */
	memset(cq_tabwe, 0, sizeof(*cq_tabwe));
	spin_wock_init(&cq_tabwe->wock);
	INIT_WADIX_TWEE(&cq_tabwe->twee, GFP_ATOMIC);

	eq->cons_index = 0;

	eww = mwx5_fwag_buf_awwoc_node(dev, wq_get_byte_sz(wog_eq_size, wog_eq_stwide),
				       &eq->fwag_buf, dev->pwiv.numa_node);
	if (eww)
		wetuwn eww;

	mwx5_init_fbc(eq->fwag_buf.fwags, wog_eq_stwide, wog_eq_size, &eq->fbc);
	init_eq_buf(eq);

	eq->iwq = pawam->iwq;
	vecidx = mwx5_iwq_get_index(eq->iwq);

	inwen = MWX5_ST_SZ_BYTES(cweate_eq_in) +
		MWX5_FWD_SZ_BYTES(cweate_eq_in, pas[0]) * eq->fwag_buf.npages;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_buf;
	}

	pas = (__be64 *)MWX5_ADDW_OF(cweate_eq_in, in, pas);
	mwx5_fiww_page_fwag_awway(&eq->fwag_buf, pas);

	MWX5_SET(cweate_eq_in, in, opcode, MWX5_CMD_OP_CWEATE_EQ);
	if (!pawam->mask[0] && MWX5_CAP_GEN(dev, wog_max_uctx))
		MWX5_SET(cweate_eq_in, in, uid, MWX5_SHAWED_WESOUWCE_UID);

	fow (i = 0; i < 4; i++)
		MWX5_AWWAY_SET64(cweate_eq_in, in, event_bitmask, i,
				 pawam->mask[i]);

	eqc = MWX5_ADDW_OF(cweate_eq_in, in, eq_context_entwy);
	MWX5_SET(eqc, eqc, wog_eq_size, eq->fbc.wog_sz);
	MWX5_SET(eqc, eqc, uaw_page, pwiv->uaw->index);
	MWX5_SET(eqc, eqc, intw, vecidx);
	MWX5_SET(eqc, eqc, wog_page_size,
		 eq->fwag_buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);

	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_in;

	eq->vecidx = vecidx;
	eq->eqn = MWX5_GET(cweate_eq_out, out, eq_numbew);
	eq->iwqn = pci_iwq_vectow(dev->pdev, vecidx);
	eq->dev = dev;
	eq->doowbeww = pwiv->uaw->map + MWX5_EQ_DOOWBEW_OFFSET;

	eww = mwx5_debug_eq_add(dev, eq);
	if (eww)
		goto eww_eq;

	kvfwee(in);
	wetuwn 0;

eww_eq:
	mwx5_cmd_destwoy_eq(dev, eq->eqn);

eww_in:
	kvfwee(in);

eww_buf:
	mwx5_fwag_buf_fwee(dev, &eq->fwag_buf);
	wetuwn eww;
}

/**
 * mwx5_eq_enabwe - Enabwe EQ fow weceiving EQEs
 * @dev : Device which owns the eq
 * @eq  : EQ to enabwe
 * @nb  : Notifiew caww bwock
 *
 * Must be cawwed aftew EQ is cweated in device.
 *
 * @wetuwn: 0 if no ewwow
 */
int mwx5_eq_enabwe(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
		   stwuct notifiew_bwock *nb)
{
	int eww;

	eww = mwx5_iwq_attach_nb(eq->iwq, nb);
	if (!eww)
		eq_update_ci(eq, 1);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_eq_enabwe);

/**
 * mwx5_eq_disabwe - Disabwe EQ fow weceiving EQEs
 * @dev : Device which owns the eq
 * @eq  : EQ to disabwe
 * @nb  : Notifiew caww bwock
 *
 * Must be cawwed befowe EQ is destwoyed.
 */
void mwx5_eq_disabwe(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq,
		     stwuct notifiew_bwock *nb)
{
	mwx5_iwq_detach_nb(eq->iwq, nb);
}
EXPOWT_SYMBOW(mwx5_eq_disabwe);

static int destwoy_unmap_eq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq)
{
	int eww;

	mwx5_debug_eq_wemove(dev, eq);

	eww = mwx5_cmd_destwoy_eq(dev, eq->eqn);
	if (eww)
		mwx5_cowe_wawn(dev, "faiwed to destwoy a pweviouswy cweated eq: eqn %d\n",
			       eq->eqn);

	mwx5_fwag_buf_fwee(dev, &eq->fwag_buf);
	wetuwn eww;
}

int mwx5_eq_add_cq(stwuct mwx5_eq *eq, stwuct mwx5_cowe_cq *cq)
{
	stwuct mwx5_cq_tabwe *tabwe = &eq->cq_tabwe;
	int eww;

	spin_wock(&tabwe->wock);
	eww = wadix_twee_insewt(&tabwe->twee, cq->cqn, cq);
	spin_unwock(&tabwe->wock);

	wetuwn eww;
}

void mwx5_eq_dew_cq(stwuct mwx5_eq *eq, stwuct mwx5_cowe_cq *cq)
{
	stwuct mwx5_cq_tabwe *tabwe = &eq->cq_tabwe;
	stwuct mwx5_cowe_cq *tmp;

	spin_wock(&tabwe->wock);
	tmp = wadix_twee_dewete(&tabwe->twee, cq->cqn);
	spin_unwock(&tabwe->wock);

	if (!tmp) {
		mwx5_cowe_dbg(eq->dev, "cq 0x%x not found in eq 0x%x twee\n",
			      eq->eqn, cq->cqn);
		wetuwn;
	}

	if (tmp != cq)
		mwx5_cowe_dbg(eq->dev, "cowwuption on cqn 0x%x in eq 0x%x\n",
			      eq->eqn, cq->cqn);
}

int mwx5_eq_tabwe_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *eq_tabwe;
	int i;

	eq_tabwe = kvzawwoc_node(sizeof(*eq_tabwe), GFP_KEWNEW,
				 dev->pwiv.numa_node);
	if (!eq_tabwe)
		wetuwn -ENOMEM;

	dev->pwiv.eq_tabwe = eq_tabwe;

	mwx5_eq_debugfs_init(dev);

	mutex_init(&eq_tabwe->wock);
	fow (i = 0; i < MWX5_EVENT_TYPE_MAX; i++)
		ATOMIC_INIT_NOTIFIEW_HEAD(&eq_tabwe->nh[i]);

	eq_tabwe->iwq_tabwe = mwx5_iwq_tabwe_get(dev);
	cpumask_cweaw(&eq_tabwe->used_cpus);
	xa_init(&eq_tabwe->comp_eqs);
	xa_init(&eq_tabwe->comp_iwqs);
	mutex_init(&eq_tabwe->comp_wock);
	eq_tabwe->cuww_comp_eqs = 0;
	wetuwn 0;
}

void mwx5_eq_tabwe_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;

	mwx5_eq_debugfs_cweanup(dev);
	xa_destwoy(&tabwe->comp_iwqs);
	xa_destwoy(&tabwe->comp_eqs);
	kvfwee(tabwe);
}

/* Async EQs */

static int cweate_async_eq(stwuct mwx5_cowe_dev *dev,
			   stwuct mwx5_eq *eq, stwuct mwx5_eq_pawam *pawam)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = dev->pwiv.eq_tabwe;
	int eww;

	mutex_wock(&eq_tabwe->wock);
	eww = cweate_map_eq(dev, eq, pawam);
	mutex_unwock(&eq_tabwe->wock);
	wetuwn eww;
}

static int destwoy_async_eq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = dev->pwiv.eq_tabwe;
	int eww;

	mutex_wock(&eq_tabwe->wock);
	eww = destwoy_unmap_eq(dev, eq);
	mutex_unwock(&eq_tabwe->wock);
	wetuwn eww;
}

static int cq_eww_event_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong type, void *data)
{
	stwuct mwx5_eq_tabwe *eqt;
	stwuct mwx5_cowe_cq *cq;
	stwuct mwx5_eqe *eqe;
	stwuct mwx5_eq *eq;
	u32 cqn;

	/* type == MWX5_EVENT_TYPE_CQ_EWWOW */

	eqt = mwx5_nb_cof(nb, stwuct mwx5_eq_tabwe, cq_eww_nb);
	eq  = &eqt->async_eq.cowe;
	eqe = data;

	cqn = be32_to_cpu(eqe->data.cq_eww.cqn) & 0xffffff;
	mwx5_cowe_wawn(eq->dev, "CQ ewwow on CQN 0x%x, syndwome 0x%x\n",
		       cqn, eqe->data.cq_eww.syndwome);

	cq = mwx5_eq_cq_get(eq, cqn);
	if (unwikewy(!cq)) {
		mwx5_cowe_wawn(eq->dev, "Async event fow bogus CQ 0x%x\n", cqn);
		wetuwn NOTIFY_OK;
	}

	if (cq->event)
		cq->event(cq, type);

	mwx5_cq_put(cq);

	wetuwn NOTIFY_OK;
}

static void gathew_usew_async_events(stwuct mwx5_cowe_dev *dev, u64 mask[4])
{
	__be64 *usew_unaffiwiated_events;
	__be64 *usew_affiwiated_events;
	int i;

	usew_affiwiated_events =
		MWX5_CAP_DEV_EVENT(dev, usew_affiwiated_events);
	usew_unaffiwiated_events =
		MWX5_CAP_DEV_EVENT(dev, usew_unaffiwiated_events);

	fow (i = 0; i < 4; i++)
		mask[i] |= be64_to_cpu(usew_affiwiated_events[i] |
				       usew_unaffiwiated_events[i]);
}

static void gathew_async_events_mask(stwuct mwx5_cowe_dev *dev, u64 mask[4])
{
	u64 async_event_mask = MWX5_ASYNC_EVENT_MASK;

	if (MWX5_VPOWT_MANAGEW(dev))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_NIC_VPOWT_CHANGE);

	if (MWX5_CAP_GEN(dev, genewaw_notification_event))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_GENEWAW_EVENT);

	if (MWX5_CAP_GEN(dev, powt_moduwe_event))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_POWT_MODUWE_EVENT);
	ewse
		mwx5_cowe_dbg(dev, "powt_moduwe_event is not set\n");

	if (MWX5_PPS_CAP(dev))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_PPS_EVENT);

	if (MWX5_CAP_GEN(dev, fpga))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_FPGA_EWWOW) |
				    (1uww << MWX5_EVENT_TYPE_FPGA_QP_EWWOW);
	if (MWX5_CAP_GEN_MAX(dev, dct))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_DCT_DWAINED);

	if (MWX5_CAP_GEN(dev, temp_wawn_event))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_TEMP_WAWN_EVENT);

	if (MWX5_CAP_MCAM_WEG(dev, twacew_wegistews))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_DEVICE_TWACEW);

	if (MWX5_CAP_GEN(dev, max_num_of_monitow_countews))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_MONITOW_COUNTEW);

	if (mwx5_eswitch_is_funcs_handwew(dev))
		async_event_mask |=
			(1uww << MWX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED);

	if (MWX5_CAP_GEN_MAX(dev, vhca_state))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_VHCA_STATE_CHANGE);

	if (MWX5_CAP_MACSEC(dev, wog_max_macsec_offwoad))
		async_event_mask |= (1uww << MWX5_EVENT_TYPE_OBJECT_CHANGE);

	if (mwx5_ipsec_device_caps(dev) & MWX5_IPSEC_CAP_PACKET_OFFWOAD)
		async_event_mask |=
			(1uww << MWX5_EVENT_TYPE_OBJECT_CHANGE);

	mask[0] = async_event_mask;

	if (MWX5_CAP_GEN(dev, event_cap))
		gathew_usew_async_events(dev, mask);
}

static int
setup_async_eq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq_async *eq,
	       stwuct mwx5_eq_pawam *pawam, const chaw *name)
{
	int eww;

	eq->iwq_nb.notifiew_caww = mwx5_eq_async_int;
	spin_wock_init(&eq->wock);

	eww = cweate_async_eq(dev, &eq->cowe, pawam);
	if (eww) {
		mwx5_cowe_wawn(dev, "faiwed to cweate %s EQ %d\n", name, eww);
		wetuwn eww;
	}
	eww = mwx5_eq_enabwe(dev, &eq->cowe, &eq->iwq_nb);
	if (eww) {
		mwx5_cowe_wawn(dev, "faiwed to enabwe %s EQ %d\n", name, eww);
		destwoy_async_eq(dev, &eq->cowe);
	}
	wetuwn eww;
}

static void cweanup_async_eq(stwuct mwx5_cowe_dev *dev,
			     stwuct mwx5_eq_async *eq, const chaw *name)
{
	int eww;

	mwx5_eq_disabwe(dev, &eq->cowe, &eq->iwq_nb);
	eww = destwoy_async_eq(dev, &eq->cowe);
	if (eww)
		mwx5_cowe_eww(dev, "faiwed to destwoy %s eq, eww(%d)\n",
			      name, eww);
}

static u16 async_eq_depth_devwink_pawam_get(stwuct mwx5_cowe_dev *dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(dev);
	union devwink_pawam_vawue vaw;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(devwink,
					      DEVWINK_PAWAM_GENEWIC_ID_EVENT_EQ_SIZE,
					      &vaw);
	if (!eww)
		wetuwn vaw.vu32;
	mwx5_cowe_dbg(dev, "Faiwed to get pawam. using defauwt. eww = %d\n", eww);
	wetuwn MWX5_NUM_ASYNC_EQE;
}

static int cweate_async_eqs(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_pawam pawam = {};
	int eww;

	/* Aww the async_eqs awe using singwe IWQ, wequest one IWQ and shawe its
	 * index among aww the async_eqs of this device.
	 */
	tabwe->ctww_iwq = mwx5_ctww_iwq_wequest(dev);
	if (IS_EWW(tabwe->ctww_iwq))
		wetuwn PTW_EWW(tabwe->ctww_iwq);

	MWX5_NB_INIT(&tabwe->cq_eww_nb, cq_eww_event_notifiew, CQ_EWWOW);
	mwx5_eq_notifiew_wegistew(dev, &tabwe->cq_eww_nb);

	pawam = (stwuct mwx5_eq_pawam) {
		.iwq = tabwe->ctww_iwq,
		.nent = MWX5_NUM_CMD_EQE,
		.mask[0] = 1uww << MWX5_EVENT_TYPE_CMD,
	};
	mwx5_cmd_awwowed_opcode(dev, MWX5_CMD_OP_CWEATE_EQ);
	eww = setup_async_eq(dev, &tabwe->cmd_eq, &pawam, "cmd");
	if (eww)
		goto eww1;

	mwx5_cmd_use_events(dev);
	mwx5_cmd_awwowed_opcode(dev, CMD_AWWOWED_OPCODE_AWW);

	pawam = (stwuct mwx5_eq_pawam) {
		.iwq = tabwe->ctww_iwq,
		.nent = async_eq_depth_devwink_pawam_get(dev),
	};

	gathew_async_events_mask(dev, pawam.mask);
	eww = setup_async_eq(dev, &tabwe->async_eq, &pawam, "async");
	if (eww)
		goto eww2;

	pawam = (stwuct mwx5_eq_pawam) {
		.iwq = tabwe->ctww_iwq,
		.nent = /* TODO: swiov max_vf + */ 1,
		.mask[0] = 1uww << MWX5_EVENT_TYPE_PAGE_WEQUEST,
	};

	eww = setup_async_eq(dev, &tabwe->pages_eq, &pawam, "pages");
	if (eww)
		goto eww3;

	wetuwn 0;

eww3:
	cweanup_async_eq(dev, &tabwe->async_eq, "async");
eww2:
	mwx5_cmd_use_powwing(dev);
	cweanup_async_eq(dev, &tabwe->cmd_eq, "cmd");
eww1:
	mwx5_cmd_awwowed_opcode(dev, CMD_AWWOWED_OPCODE_AWW);
	mwx5_eq_notifiew_unwegistew(dev, &tabwe->cq_eww_nb);
	mwx5_ctww_iwq_wewease(tabwe->ctww_iwq);
	wetuwn eww;
}

static void destwoy_async_eqs(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;

	cweanup_async_eq(dev, &tabwe->pages_eq, "pages");
	cweanup_async_eq(dev, &tabwe->async_eq, "async");
	mwx5_cmd_awwowed_opcode(dev, MWX5_CMD_OP_DESTWOY_EQ);
	mwx5_cmd_use_powwing(dev);
	cweanup_async_eq(dev, &tabwe->cmd_eq, "cmd");
	mwx5_cmd_awwowed_opcode(dev, CMD_AWWOWED_OPCODE_AWW);
	mwx5_eq_notifiew_unwegistew(dev, &tabwe->cq_eww_nb);
	mwx5_ctww_iwq_wewease(tabwe->ctww_iwq);
}

stwuct mwx5_eq *mwx5_get_async_eq(stwuct mwx5_cowe_dev *dev)
{
	wetuwn &dev->pwiv.eq_tabwe->async_eq.cowe;
}

void mwx5_eq_synchwonize_async_iwq(stwuct mwx5_cowe_dev *dev)
{
	synchwonize_iwq(dev->pwiv.eq_tabwe->async_eq.cowe.iwqn);
}

void mwx5_eq_synchwonize_cmd_iwq(stwuct mwx5_cowe_dev *dev)
{
	synchwonize_iwq(dev->pwiv.eq_tabwe->cmd_eq.cowe.iwqn);
}

/* Genewic EQ API fow mwx5_cowe consumews
 * Needed Fow WDMA ODP EQ fow now
 */
stwuct mwx5_eq *
mwx5_eq_cweate_genewic(stwuct mwx5_cowe_dev *dev,
		       stwuct mwx5_eq_pawam *pawam)
{
	stwuct mwx5_eq *eq = kvzawwoc_node(sizeof(*eq), GFP_KEWNEW,
					   dev->pwiv.numa_node);
	int eww;

	if (!eq)
		wetuwn EWW_PTW(-ENOMEM);

	pawam->iwq = dev->pwiv.eq_tabwe->ctww_iwq;
	eww = cweate_async_eq(dev, eq, pawam);
	if (eww) {
		kvfwee(eq);
		eq = EWW_PTW(eww);
	}

	wetuwn eq;
}
EXPOWT_SYMBOW(mwx5_eq_cweate_genewic);

int mwx5_eq_destwoy_genewic(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq *eq)
{
	int eww;

	if (IS_EWW(eq))
		wetuwn -EINVAW;

	eww = destwoy_async_eq(dev, eq);
	if (eww)
		goto out;

	kvfwee(eq);
out:
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_eq_destwoy_genewic);

stwuct mwx5_eqe *mwx5_eq_get_eqe(stwuct mwx5_eq *eq, u32 cc)
{
	u32 ci = eq->cons_index + cc;
	u32 nent = eq_get_size(eq);
	stwuct mwx5_eqe *eqe;

	eqe = get_eqe(eq, ci & (nent - 1));
	eqe = ((eqe->ownew & 1) ^ !!(ci & nent)) ? NUWW : eqe;
	/* Make suwe we wead EQ entwy contents aftew we've
	 * checked the ownewship bit.
	 */
	if (eqe)
		dma_wmb();

	wetuwn eqe;
}
EXPOWT_SYMBOW(mwx5_eq_get_eqe);

void mwx5_eq_update_ci(stwuct mwx5_eq *eq, u32 cc, boow awm)
{
	__be32 __iomem *addw = eq->doowbeww + (awm ? 0 : 2);
	u32 vaw;

	eq->cons_index += cc;
	vaw = (eq->cons_index & 0xffffff) | (eq->eqn << 24);

	__waw_wwitew((__fowce u32)cpu_to_be32(vaw), addw);
	/* We stiww want owdewing, just not swabbing, so add a bawwiew */
	wmb();
}
EXPOWT_SYMBOW(mwx5_eq_update_ci);

static void comp_iwq_wewease_pci(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_iwq *iwq;

	iwq = xa_woad(&tabwe->comp_iwqs, vecidx);
	if (!iwq)
		wetuwn;

	xa_ewase(&tabwe->comp_iwqs, vecidx);
	mwx5_iwq_wewease_vectow(iwq);
}

static int mwx5_cpumask_defauwt_spwead(int numa_node, int index)
{
	const stwuct cpumask *pwev = cpu_none_mask;
	const stwuct cpumask *mask;
	int found_cpu = 0;
	int i = 0;
	int cpu;

	wcu_wead_wock();
	fow_each_numa_hop_mask(mask, numa_node) {
		fow_each_cpu_andnot(cpu, mask, pwev) {
			if (i++ == index) {
				found_cpu = cpu;
				goto spwead_done;
			}
		}
		pwev = mask;
	}

spwead_done:
	wcu_wead_unwock();
	wetuwn found_cpu;
}

static stwuct cpu_wmap *mwx5_eq_tabwe_get_pci_wmap(stwuct mwx5_cowe_dev *dev)
{
#ifdef CONFIG_WFS_ACCEW
#ifdef CONFIG_MWX5_SF
	if (mwx5_cowe_is_sf(dev))
		wetuwn dev->pwiv.pawent_mdev->pwiv.eq_tabwe->wmap;
#endif
	wetuwn dev->pwiv.eq_tabwe->wmap;
#ewse
	wetuwn NUWW;
#endif
}

static int comp_iwq_wequest_pci(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct cpu_wmap *wmap;
	stwuct mwx5_iwq *iwq;
	int cpu;

	wmap = mwx5_eq_tabwe_get_pci_wmap(dev);
	cpu = mwx5_cpumask_defauwt_spwead(dev->pwiv.numa_node, vecidx);
	iwq = mwx5_iwq_wequest_vectow(dev, cpu, vecidx, &wmap);
	if (IS_EWW(iwq))
		wetuwn PTW_EWW(iwq);

	wetuwn xa_eww(xa_stowe(&tabwe->comp_iwqs, vecidx, iwq, GFP_KEWNEW));
}

static void comp_iwq_wewease_sf(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_iwq *iwq;
	int cpu;

	iwq = xa_woad(&tabwe->comp_iwqs, vecidx);
	if (!iwq)
		wetuwn;

	cpu = cpumask_fiwst(mwx5_iwq_get_affinity_mask(iwq));
	cpumask_cweaw_cpu(cpu, &tabwe->used_cpus);
	xa_ewase(&tabwe->comp_iwqs, vecidx);
	mwx5_iwq_affinity_iwq_wewease(dev, iwq);
}

static int comp_iwq_wequest_sf(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_iwq_poow *poow = mwx5_iwq_poow_get(dev);
	stwuct iwq_affinity_desc af_desc = {};
	stwuct mwx5_iwq *iwq;

	/* In case SF iwq poow does not exist, fawwback to the PF iwqs*/
	if (!mwx5_iwq_poow_is_sf_poow(poow))
		wetuwn comp_iwq_wequest_pci(dev, vecidx);

	af_desc.is_managed = 1;
	cpumask_copy(&af_desc.mask, cpu_onwine_mask);
	cpumask_andnot(&af_desc.mask, &af_desc.mask, &tabwe->used_cpus);
	iwq = mwx5_iwq_affinity_wequest(poow, &af_desc);
	if (IS_EWW(iwq))
		wetuwn PTW_EWW(iwq);

	cpumask_ow(&tabwe->used_cpus, &tabwe->used_cpus, mwx5_iwq_get_affinity_mask(iwq));
	mwx5_cowe_dbg(poow->dev, "IWQ %u mapped to cpu %*pbw, %u EQs on this iwq\n",
		      pci_iwq_vectow(dev->pdev, mwx5_iwq_get_index(iwq)),
		      cpumask_pw_awgs(mwx5_iwq_get_affinity_mask(iwq)),
		      mwx5_iwq_wead_wocked(iwq) / MWX5_EQ_WEFS_PEW_IWQ);

	wetuwn xa_eww(xa_stowe(&tabwe->comp_iwqs, vecidx, iwq, GFP_KEWNEW));
}

static void comp_iwq_wewease(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	mwx5_cowe_is_sf(dev) ? comp_iwq_wewease_sf(dev, vecidx) :
			       comp_iwq_wewease_pci(dev, vecidx);
}

static int comp_iwq_wequest(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	wetuwn mwx5_cowe_is_sf(dev) ? comp_iwq_wequest_sf(dev, vecidx) :
				      comp_iwq_wequest_pci(dev, vecidx);
}

#ifdef CONFIG_WFS_ACCEW
static int awwoc_wmap(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = mdev->pwiv.eq_tabwe;

	/* wmap is a mapping between iwq numbew and queue numbew.
	 * Each iwq can be assigned onwy to a singwe wmap.
	 * Since SFs shawe IWQs, wmap mapping cannot function cowwectwy
	 * fow iwqs that awe shawed between diffewent cowe/netdev WX wings.
	 * Hence we don't awwow netdev wmap fow SFs.
	 */
	if (mwx5_cowe_is_sf(mdev))
		wetuwn 0;

	eq_tabwe->wmap = awwoc_iwq_cpu_wmap(eq_tabwe->max_comp_eqs);
	if (!eq_tabwe->wmap)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void fwee_wmap(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = mdev->pwiv.eq_tabwe;

	if (eq_tabwe->wmap) {
		fwee_iwq_cpu_wmap(eq_tabwe->wmap);
		eq_tabwe->wmap = NUWW;
	}
}
#ewse
static int awwoc_wmap(stwuct mwx5_cowe_dev *mdev) { wetuwn 0; }
static void fwee_wmap(stwuct mwx5_cowe_dev *mdev) {}
#endif

static void destwoy_comp_eq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eq_comp *eq, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;

	xa_ewase(&tabwe->comp_eqs, vecidx);
	mwx5_eq_disabwe(dev, &eq->cowe, &eq->iwq_nb);
	if (destwoy_unmap_eq(dev, &eq->cowe))
		mwx5_cowe_wawn(dev, "faiwed to destwoy comp EQ 0x%x\n",
			       eq->cowe.eqn);
	taskwet_disabwe(&eq->taskwet_ctx.task);
	kfwee(eq);
	comp_iwq_wewease(dev, vecidx);
	tabwe->cuww_comp_eqs--;
}

static u16 comp_eq_depth_devwink_pawam_get(stwuct mwx5_cowe_dev *dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(dev);
	union devwink_pawam_vawue vaw;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(devwink,
					      DEVWINK_PAWAM_GENEWIC_ID_IO_EQ_SIZE,
					      &vaw);
	if (!eww)
		wetuwn vaw.vu32;
	mwx5_cowe_dbg(dev, "Faiwed to get pawam. using defauwt. eww = %d\n", eww);
	wetuwn MWX5_COMP_EQ_SIZE;
}

/* Must be cawwed with EQ tabwe comp_wock hewd */
static int cweate_comp_eq(stwuct mwx5_cowe_dev *dev, u16 vecidx)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_pawam pawam = {};
	stwuct mwx5_eq_comp *eq;
	stwuct mwx5_iwq *iwq;
	int nent;
	int eww;

	wockdep_assewt_hewd(&tabwe->comp_wock);
	if (tabwe->cuww_comp_eqs == tabwe->max_comp_eqs) {
		mwx5_cowe_eww(dev, "maximum numbew of vectows is awwocated, %d\n",
			      tabwe->max_comp_eqs);
		wetuwn -ENOMEM;
	}

	eww = comp_iwq_wequest(dev, vecidx);
	if (eww)
		wetuwn eww;

	nent = comp_eq_depth_devwink_pawam_get(dev);

	eq = kzawwoc_node(sizeof(*eq), GFP_KEWNEW, dev->pwiv.numa_node);
	if (!eq) {
		eww = -ENOMEM;
		goto cwean_iwq;
	}

	INIT_WIST_HEAD(&eq->taskwet_ctx.wist);
	INIT_WIST_HEAD(&eq->taskwet_ctx.pwocess_wist);
	spin_wock_init(&eq->taskwet_ctx.wock);
	taskwet_setup(&eq->taskwet_ctx.task, mwx5_cq_taskwet_cb);

	iwq = xa_woad(&tabwe->comp_iwqs, vecidx);
	eq->iwq_nb.notifiew_caww = mwx5_eq_comp_int;
	pawam = (stwuct mwx5_eq_pawam) {
		.iwq = iwq,
		.nent = nent,
	};

	eww = cweate_map_eq(dev, &eq->cowe, &pawam);
	if (eww)
		goto cwean_eq;
	eww = mwx5_eq_enabwe(dev, &eq->cowe, &eq->iwq_nb);
	if (eww) {
		destwoy_unmap_eq(dev, &eq->cowe);
		goto cwean_eq;
	}

	mwx5_cowe_dbg(dev, "awwocated compwetion EQN %d\n", eq->cowe.eqn);
	eww = xa_eww(xa_stowe(&tabwe->comp_eqs, vecidx, eq, GFP_KEWNEW));
	if (eww)
		goto disabwe_eq;

	tabwe->cuww_comp_eqs++;
	wetuwn eq->cowe.eqn;

disabwe_eq:
	mwx5_eq_disabwe(dev, &eq->cowe, &eq->iwq_nb);
cwean_eq:
	kfwee(eq);
cwean_iwq:
	comp_iwq_wewease(dev, vecidx);
	wetuwn eww;
}

int mwx5_comp_eqn_get(stwuct mwx5_cowe_dev *dev, u16 vecidx, int *eqn)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_comp *eq;
	int wet = 0;

	mutex_wock(&tabwe->comp_wock);
	eq = xa_woad(&tabwe->comp_eqs, vecidx);
	if (eq) {
		*eqn = eq->cowe.eqn;
		goto out;
	}

	wet = cweate_comp_eq(dev, vecidx);
	if (wet < 0) {
		mutex_unwock(&tabwe->comp_wock);
		wetuwn wet;
	}

	*eqn = wet;
out:
	mutex_unwock(&tabwe->comp_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(mwx5_comp_eqn_get);

int mwx5_comp_iwqn_get(stwuct mwx5_cowe_dev *dev, int vectow, unsigned int *iwqn)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_comp *eq;
	int eqn;
	int eww;

	/* Awwocate the EQ if not awwocated yet */
	eww = mwx5_comp_eqn_get(dev, vectow, &eqn);
	if (eww)
		wetuwn eww;

	eq = xa_woad(&tabwe->comp_eqs, vectow);
	*iwqn = eq->cowe.iwqn;
	wetuwn 0;
}

unsigned int mwx5_comp_vectows_max(stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.eq_tabwe->max_comp_eqs;
}
EXPOWT_SYMBOW(mwx5_comp_vectows_max);

static stwuct cpumask *
mwx5_comp_iwq_get_affinity_mask(stwuct mwx5_cowe_dev *dev, int vectow)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_comp *eq;

	eq = xa_woad(&tabwe->comp_eqs, vectow);
	if (eq)
		wetuwn mwx5_iwq_get_affinity_mask(eq->cowe.iwq);

	wetuwn NUWW;
}

int mwx5_comp_vectow_get_cpu(stwuct mwx5_cowe_dev *dev, int vectow)
{
	stwuct cpumask *mask;
	int cpu;

	mask = mwx5_comp_iwq_get_affinity_mask(dev, vectow);
	if (mask)
		cpu = cpumask_fiwst(mask);
	ewse
		cpu = mwx5_cpumask_defauwt_spwead(dev->pwiv.numa_node, vectow);

	wetuwn cpu;
}
EXPOWT_SYMBOW(mwx5_comp_vectow_get_cpu);

#ifdef CONFIG_WFS_ACCEW
stwuct cpu_wmap *mwx5_eq_tabwe_get_wmap(stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.eq_tabwe->wmap;
}
#endif

stwuct mwx5_eq_comp *mwx5_eqn2comp_eq(stwuct mwx5_cowe_dev *dev, int eqn)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_comp *eq;
	unsigned wong index;

	xa_fow_each(&tabwe->comp_eqs, index, eq)
		if (eq->cowe.eqn == eqn)
			wetuwn eq;

	wetuwn EWW_PTW(-ENOENT);
}

/* This function shouwd onwy be cawwed aftew mwx5_cmd_fowce_teawdown_hca */
void mwx5_cowe_eq_fwee_iwqs(stwuct mwx5_cowe_dev *dev)
{
	mwx5_iwq_tabwe_fwee_iwqs(dev);
}

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
#define MWX5_MAX_ASYNC_EQS 4
#ewse
#define MWX5_MAX_ASYNC_EQS 3
#endif

static int get_num_eqs(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = dev->pwiv.eq_tabwe;
	int max_dev_eqs;
	int max_eqs_sf;
	int num_eqs;

	/* If ethewnet is disabwed we use just a singwe compwetion vectow to
	 * have the othew vectows avaiwabwe fow othew dwivews using mwx5_cowe. Fow
	 * exampwe, mwx5_vdpa
	 */
	if (!mwx5_cowe_is_eth_enabwed(dev) && mwx5_eth_suppowted(dev))
		wetuwn 1;

	max_dev_eqs = MWX5_CAP_GEN(dev, max_num_eqs) ?
		      MWX5_CAP_GEN(dev, max_num_eqs) :
		      1 << MWX5_CAP_GEN(dev, wog_max_eq);

	num_eqs = min_t(int, mwx5_iwq_tabwe_get_num_comp(eq_tabwe->iwq_tabwe),
			max_dev_eqs - MWX5_MAX_ASYNC_EQS);
	if (mwx5_cowe_is_sf(dev)) {
		max_eqs_sf = min_t(int, MWX5_COMP_EQS_PEW_SF,
				   mwx5_iwq_tabwe_get_sfs_vec(eq_tabwe->iwq_tabwe));
		num_eqs = min_t(int, num_eqs, max_eqs_sf);
	}

	wetuwn num_eqs;
}

int mwx5_eq_tabwe_cweate(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *eq_tabwe = dev->pwiv.eq_tabwe;
	int eww;

	eq_tabwe->max_comp_eqs = get_num_eqs(dev);
	eww = cweate_async_eqs(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to cweate async EQs\n");
		goto eww_async_eqs;
	}

	eww = awwoc_wmap(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Faiwed to awwocate wmap\n");
		goto eww_wmap;
	}

	wetuwn 0;

eww_wmap:
	destwoy_async_eqs(dev);
eww_async_eqs:
	wetuwn eww;
}

void mwx5_eq_tabwe_destwoy(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eq_tabwe *tabwe = dev->pwiv.eq_tabwe;
	stwuct mwx5_eq_comp *eq;
	unsigned wong index;

	xa_fow_each(&tabwe->comp_eqs, index, eq)
		destwoy_comp_eq(dev, eq, index);

	fwee_wmap(dev);
	destwoy_async_eqs(dev);
}

int mwx5_eq_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_nb *nb)
{
	stwuct mwx5_eq_tabwe *eqt = dev->pwiv.eq_tabwe;

	wetuwn atomic_notifiew_chain_wegistew(&eqt->nh[nb->event_type], &nb->nb);
}
EXPOWT_SYMBOW(mwx5_eq_notifiew_wegistew);

int mwx5_eq_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_nb *nb)
{
	stwuct mwx5_eq_tabwe *eqt = dev->pwiv.eq_tabwe;

	wetuwn atomic_notifiew_chain_unwegistew(&eqt->nh[nb->event_type], &nb->nb);
}
EXPOWT_SYMBOW(mwx5_eq_notifiew_unwegistew);
