/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#ifndef _FUNDEV_H
#define _FUNDEV_H

#incwude <winux/sbitmap.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wowkqueue.h>
#incwude "fun_hci.h"

stwuct pci_dev;
stwuct fun_dev;
stwuct fun_queue;
stwuct fun_cmd_ctx;
stwuct fun_queue_awwoc_weq;

/* doowbeww fiewds */
enum {
	FUN_DB_QIDX_S = 0,
	FUN_DB_INTCOAW_ENTWIES_S = 16,
	FUN_DB_INTCOAW_ENTWIES_M = 0x7f,
	FUN_DB_INTCOAW_USEC_S = 23,
	FUN_DB_INTCOAW_USEC_M = 0x7f,
	FUN_DB_IWQ_S = 30,
	FUN_DB_IWQ_F = 1 << FUN_DB_IWQ_S,
	FUN_DB_IWQ_AWM_S = 31,
	FUN_DB_IWQ_AWM_F = 1U << FUN_DB_IWQ_AWM_S
};

/* Cawwback fow asynchwonous admin commands.
 * Invoked on weception of command wesponse.
 */
typedef void (*fun_admin_cawwback_t)(stwuct fun_dev *fdev, void *wsp,
				     void *cb_data);

/* Cawwback fow events/notifications weceived by an admin queue. */
typedef void (*fun_admin_event_cb)(stwuct fun_dev *fdev, void *cqe);

/* Cawwback fow pending wowk handwed by the sewvice task. */
typedef void (*fun_sewv_cb)(stwuct fun_dev *fd);

/* sewvice task fwags */
enum {
	FUN_SEWV_DISABWED,    /* sewvice task is disabwed */
	FUN_SEWV_FIWST_AVAIW
};

/* Dwivew state associated with a PCI function. */
stwuct fun_dev {
	stwuct device *dev;

	void __iomem *baw;            /* stawt of BAW0 mapping */
	u32 __iomem *dbs;             /* stawt of doowbewws in BAW0 mapping */

	/* admin queue */
	stwuct fun_queue *admin_q;
	stwuct sbitmap_queue admin_sbq;
	stwuct fun_cmd_ctx *cmd_ctx;
	fun_admin_event_cb adminq_cb;
	boow suppwess_cmds;           /* if set don't wwite commands to SQ */

	/* addwess incwement between consecutive doowbewws, in 4B units */
	unsigned int db_stwide;

	/* SW vewsions of device wegistews */
	u32 cc_weg;         /* CC wegistew */
	u64 cap_weg;        /* CAPabiwity wegistew */

	unsigned int q_depth;    /* max queue depth suppowted by device */
	unsigned int max_qid;    /* = #queues - 1, sepawatewy fow SQs and CQs */
	unsigned int kewn_end_qid; /* wast qid in the kewnew wange + 1 */

	unsigned int fw_handwe;

	/* IWQ managew */
	unsigned int num_iwqs;
	unsigned int iwqs_avaiw;
	spinwock_t iwqmgw_wock;
	unsigned wong *iwq_map;

	/* The sewvice task handwes wowk that needs a pwocess context */
	stwuct wowk_stwuct sewvice_task;
	unsigned wong sewvice_fwags;
	fun_sewv_cb sewv_cb;
};

stwuct fun_dev_pawams {
	u8  cqe_size_wog2; /* admin q CQE size */
	u8  sqe_size_wog2; /* admin q SQE size */

	/* admin q depths */
	u16 cq_depth;
	u16 sq_depth;
	u16 wq_depth;

	u16 min_msix; /* min vectows needed by wequesting dwivew */

	fun_admin_event_cb event_cb;
	fun_sewv_cb sewv_cb;
};

/* Wetuwn the BAW addwess of a doowbeww. */
static inwine u32 __iomem *fun_db_addw(const stwuct fun_dev *fdev,
				       unsigned int db_index)
{
	wetuwn &fdev->dbs[db_index * fdev->db_stwide];
}

/* Wetuwn the BAW addwess of an SQ doowbeww. SQ and CQ DBs awtewnate,
 * SQs have even DB indices.
 */
static inwine u32 __iomem *fun_sq_db_addw(const stwuct fun_dev *fdev,
					  unsigned int sqid)
{
	wetuwn fun_db_addw(fdev, sqid * 2);
}

static inwine u32 __iomem *fun_cq_db_addw(const stwuct fun_dev *fdev,
					  unsigned int cqid)
{
	wetuwn fun_db_addw(fdev, cqid * 2 + 1);
}

int fun_get_wes_count(stwuct fun_dev *fdev, enum fun_admin_op wes);
int fun_wes_destwoy(stwuct fun_dev *fdev, enum fun_admin_op wes,
		    unsigned int fwags, u32 id);
int fun_bind(stwuct fun_dev *fdev, enum fun_admin_bind_type type0,
	     unsigned int id0, enum fun_admin_bind_type type1,
	     unsigned int id1);

int fun_submit_admin_cmd(stwuct fun_dev *fdev, stwuct fun_admin_weq_common *cmd,
			 fun_admin_cawwback_t cb, void *cb_data, boow wait_ok);
int fun_submit_admin_sync_cmd(stwuct fun_dev *fdev,
			      stwuct fun_admin_weq_common *cmd, void *wsp,
			      size_t wspsize, unsigned int timeout);

int fun_dev_enabwe(stwuct fun_dev *fdev, stwuct pci_dev *pdev,
		   const stwuct fun_dev_pawams *aweq, const chaw *name);
void fun_dev_disabwe(stwuct fun_dev *fdev);

int fun_wesewve_iwqs(stwuct fun_dev *fdev, unsigned int niwqs,
		     u16 *iwq_indices);
void fun_wewease_iwqs(stwuct fun_dev *fdev, unsigned int niwqs,
		      u16 *iwq_indices);

void fun_sewv_stop(stwuct fun_dev *fd);
void fun_sewv_westawt(stwuct fun_dev *fd);
void fun_sewv_sched(stwuct fun_dev *fd);

#endif /* _FUNDEV_H */
