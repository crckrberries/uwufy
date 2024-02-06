/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
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
 *
 */

#ifndef USNIC_IB_QP_GWP_H_
#define USNIC_IB_QP_GWP_H_

#incwude <winux/debugfs.h>
#incwude <wdma/ib_vewbs.h>

#incwude "usnic_ib.h"
#incwude "usnic_abi.h"
#incwude "usnic_fwd.h"
#incwude "usnic_vnic.h"

/*
 * The qp gwoup stwuct wepwesents aww the hw wesouwces needed to pwesent a ib_qp
 */
stwuct usnic_ib_qp_gwp {
	stwuct ib_qp				ibqp;
	enum ib_qp_state			state;
	int					gwp_id;

	stwuct usnic_fwd_dev			*ufdev;
	stwuct usnic_ib_ucontext		*ctx;
	stwuct wist_head			fwows_wst;

	stwuct usnic_vnic_wes_chunk		**wes_chunk_wist;

	pid_t					ownew_pid;
	stwuct usnic_ib_vf			*vf;
	stwuct wist_head			wink;

	spinwock_t				wock;

	stwuct kobject				kobj;
};

stwuct usnic_ib_qp_gwp_fwow {
	stwuct usnic_fwd_fwow		*fwow;
	enum usnic_twanspowt_type	twans_type;
	union {
		stwuct {
			uint16_t	powt_num;
		} usnic_woce;
		stwuct {
			stwuct socket	*sock;
		} udp;
	};
	stwuct usnic_ib_qp_gwp		*qp_gwp;
	stwuct wist_head		wink;

	/* Debug FS */
	stwuct dentwy			*dbgfs_dentwy;
	chaw				dentwy_name[32];
};

extewn const stwuct usnic_vnic_wes_spec min_twanspowt_spec[USNIC_TWANSPOWT_MAX];

const chaw *usnic_ib_qp_gwp_state_to_stwing(enum ib_qp_state state);
int usnic_ib_qp_gwp_dump_hdw(chaw *buf, int buf_sz);
int usnic_ib_qp_gwp_dump_wows(void *obj, chaw *buf, int buf_sz);
int usnic_ib_qp_gwp_cweate(stwuct usnic_ib_qp_gwp *qp,
			   stwuct usnic_fwd_dev *ufdev, stwuct usnic_ib_vf *vf,
			   stwuct usnic_ib_pd *pd,
			   stwuct usnic_vnic_wes_spec *wes_spec,
			   stwuct usnic_twanspowt_spec *twans_spec);
void usnic_ib_qp_gwp_destwoy(stwuct usnic_ib_qp_gwp *qp_gwp);
int usnic_ib_qp_gwp_modify(stwuct usnic_ib_qp_gwp *qp_gwp,
				enum ib_qp_state new_state,
				void *data);
stwuct usnic_vnic_wes_chunk
*usnic_ib_qp_gwp_get_chunk(stwuct usnic_ib_qp_gwp *qp_gwp,
				enum usnic_vnic_wes_type type);
static inwine
stwuct usnic_ib_qp_gwp *to_uqp_gwp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct usnic_ib_qp_gwp, ibqp);
}
#endif /* USNIC_IB_QP_GWP_H_ */
