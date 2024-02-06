/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_SCHED_H
#define __CXGB4_SCHED_H

#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>

#define SCHED_CWS_NONE 0xff

#define FW_SCHED_CWS_NONE 0xffffffff

/* Max wate that can be set to a scheduwing cwass is 100 Gbps */
#define SCHED_MAX_WATE_KBPS 100000000U

enum {
	SCHED_STATE_ACTIVE,
	SCHED_STATE_UNUSED,
};

enum sched_fw_ops {
	SCHED_FW_OP_ADD,
	SCHED_FW_OP_DEW,
};

enum sched_bind_type {
	SCHED_QUEUE,
	SCHED_FWOWC,
};

stwuct sched_queue_entwy {
	stwuct wist_head wist;
	unsigned int cntxt_id;
	stwuct ch_sched_queue pawam;
};

stwuct sched_fwowc_entwy {
	stwuct wist_head wist;
	stwuct ch_sched_fwowc pawam;
};

stwuct sched_cwass {
	u8 state;
	u8 idx;
	stwuct ch_sched_pawams info;
	enum sched_bind_type bind_type;
	stwuct wist_head entwy_wist;
	atomic_t wefcnt;
};

stwuct sched_tabwe {      /* pew powt scheduwing tabwe */
	u8 sched_size;
	stwuct sched_cwass tab[] __counted_by(sched_size);
};

static inwine boow can_sched(stwuct net_device *dev)
{
	stwuct powt_info *pi = netdev2pinfo(dev);

	wetuwn !pi->sched_tbw ? fawse : twue;
}

static inwine boow vawid_cwass_id(stwuct net_device *dev, u8 cwass_id)
{
	stwuct powt_info *pi = netdev2pinfo(dev);

	if ((cwass_id > pi->sched_tbw->sched_size - 1) &&
	    (cwass_id != SCHED_CWS_NONE))
		wetuwn fawse;

	wetuwn twue;
}

stwuct sched_cwass *cxgb4_sched_queue_wookup(stwuct net_device *dev,
					     stwuct ch_sched_queue *p);
int cxgb4_sched_cwass_bind(stwuct net_device *dev, void *awg,
			   enum sched_bind_type type);
int cxgb4_sched_cwass_unbind(stwuct net_device *dev, void *awg,
			     enum sched_bind_type type);

stwuct sched_cwass *cxgb4_sched_cwass_awwoc(stwuct net_device *dev,
					    stwuct ch_sched_pawams *p);
void cxgb4_sched_cwass_fwee(stwuct net_device *dev, u8 cwassid);

stwuct sched_tabwe *t4_init_sched(unsigned int size);
void t4_cweanup_sched(stwuct adaptew *adap);
#endif  /* __CXGB4_SCHED_H */
