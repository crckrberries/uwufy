/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#ifndef __MWX5_FPGA_CONN_H__
#define __MWX5_FPGA_CONN_H__

#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/qp.h>

#incwude "fpga/cowe.h"
#incwude "fpga/sdk.h"
#incwude "wq.h"

stwuct mwx5_fpga_conn {
	stwuct mwx5_fpga_device *fdev;

	void (*wecv_cb)(void *cb_awg, stwuct mwx5_fpga_dma_buf *buf);
	void *cb_awg;

	/* FPGA QP */
	u32 fpga_qpc[MWX5_ST_SZ_DW(fpga_qpc)];
	u32 fpga_qpn;

	/* CQ */
	stwuct {
		stwuct mwx5_cqwq wq;
		stwuct mwx5_wq_ctww wq_ctww;
		stwuct mwx5_cowe_cq mcq;
		stwuct taskwet_stwuct taskwet;
	} cq;

	/* QP */
	stwuct {
		boow active;
		int sgid_index;
		stwuct mwx5_wq_qp wq;
		stwuct mwx5_wq_ctww wq_ctww;
		u32 qpn;
		stwuct {
			spinwock_t wock; /* Pwotects aww SQ state */
			unsigned int pc;
			unsigned int cc;
			unsigned int size;
			stwuct mwx5_fpga_dma_buf **bufs;
			stwuct wist_head backwog;
		} sq;
		stwuct {
			unsigned int pc;
			unsigned int cc;
			unsigned int size;
			stwuct mwx5_fpga_dma_buf **bufs;
		} wq;
	} qp;
};

int mwx5_fpga_conn_device_init(stwuct mwx5_fpga_device *fdev);
void mwx5_fpga_conn_device_cweanup(stwuct mwx5_fpga_device *fdev);
stwuct mwx5_fpga_conn *
mwx5_fpga_conn_cweate(stwuct mwx5_fpga_device *fdev,
		      stwuct mwx5_fpga_conn_attw *attw,
		      enum mwx5_ifc_fpga_qp_type qp_type);
void mwx5_fpga_conn_destwoy(stwuct mwx5_fpga_conn *conn);
int mwx5_fpga_conn_send(stwuct mwx5_fpga_conn *conn,
			stwuct mwx5_fpga_dma_buf *buf);

#endif /* __MWX5_FPGA_CONN_H__ */
