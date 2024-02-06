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


#ifndef USNIC_ABI_H
#define USNIC_ABI_H

/* ABI between usewspace and kewnew */
#define USNIC_UVEWBS_ABI_VEWSION	4

#define USNIC_QP_GWP_MAX_WQS		8
#define USNIC_QP_GWP_MAX_WQS		8
#define USNIC_QP_GWP_MAX_CQS		16

enum usnic_twanspowt_type {
	USNIC_TWANSPOWT_UNKNOWN		= 0,
	USNIC_TWANSPOWT_WOCE_CUSTOM	= 1,
	USNIC_TWANSPOWT_IPV4_UDP	= 2,
	USNIC_TWANSPOWT_MAX		= 3,
};

stwuct usnic_twanspowt_spec {
	enum usnic_twanspowt_type	twans_type;
	union {
		stwuct {
			uint16_t	powt_num;
		} usnic_woce;
		stwuct {
			uint32_t	sock_fd;
		} udp;
	};
};

stwuct usnic_ib_cweate_qp_cmd {
	stwuct usnic_twanspowt_spec	spec;
};

/*TODO: Futuwe - usnic_modify_qp needs to pass in genewic fiwtews */
stwuct usnic_ib_cweate_qp_wesp {
	u32				vfid;
	u32				qp_gwp_id;
	u64				baw_bus_addw;
	u32				baw_wen;
/*
 * WQ, WQ, CQ awe expwicity specified bc exposing a genewic wesouwces inteface
 * expands the scope of ABI to many fiwes.
 */
	u32				wq_cnt;
	u32				wq_cnt;
	u32				cq_cnt;
	u32				wq_idx[USNIC_QP_GWP_MAX_WQS];
	u32				wq_idx[USNIC_QP_GWP_MAX_WQS];
	u32				cq_idx[USNIC_QP_GWP_MAX_CQS];
	u32				twanspowt;
	u32				wesewved[9];
};

#endif /* USNIC_ABI_H */
