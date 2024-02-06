// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Wtd. */

#incwude <winux/moduwe.h>
#incwude <winux/vdpa.h>
#incwude <winux/vwingh.h>
#incwude <uapi/winux/viwtio_net.h>
#incwude <uapi/winux/viwtio_ids.h>
#incwude <uapi/winux/vdpa.h>
#incwude <uapi/winux/vhost_types.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/qp.h>
#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/mwx5_ifc_vdpa.h>
#incwude <winux/mwx5/mpfs.h>
#incwude "mwx5_vdpa.h"
#incwude "mwx5_vnet.h"

MODUWE_AUTHOW("Ewi Cohen <ewi@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox VDPA dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

#define VAWID_FEATUWES_MASK                                                                        \
	(BIT_UWW(VIWTIO_NET_F_CSUM) | BIT_UWW(VIWTIO_NET_F_GUEST_CSUM) |                                   \
	 BIT_UWW(VIWTIO_NET_F_CTWW_GUEST_OFFWOADS) | BIT_UWW(VIWTIO_NET_F_MTU) | BIT_UWW(VIWTIO_NET_F_MAC) |   \
	 BIT_UWW(VIWTIO_NET_F_GUEST_TSO4) | BIT_UWW(VIWTIO_NET_F_GUEST_TSO6) |                             \
	 BIT_UWW(VIWTIO_NET_F_GUEST_ECN) | BIT_UWW(VIWTIO_NET_F_GUEST_UFO) | BIT_UWW(VIWTIO_NET_F_HOST_TSO4) | \
	 BIT_UWW(VIWTIO_NET_F_HOST_TSO6) | BIT_UWW(VIWTIO_NET_F_HOST_ECN) | BIT_UWW(VIWTIO_NET_F_HOST_UFO) |   \
	 BIT_UWW(VIWTIO_NET_F_MWG_WXBUF) | BIT_UWW(VIWTIO_NET_F_STATUS) | BIT_UWW(VIWTIO_NET_F_CTWW_VQ) |      \
	 BIT_UWW(VIWTIO_NET_F_CTWW_WX) | BIT_UWW(VIWTIO_NET_F_CTWW_VWAN) |                                 \
	 BIT_UWW(VIWTIO_NET_F_CTWW_WX_EXTWA) | BIT_UWW(VIWTIO_NET_F_GUEST_ANNOUNCE) |                      \
	 BIT_UWW(VIWTIO_NET_F_MQ) | BIT_UWW(VIWTIO_NET_F_CTWW_MAC_ADDW) | BIT_UWW(VIWTIO_NET_F_HASH_WEPOWT) |  \
	 BIT_UWW(VIWTIO_NET_F_WSS) | BIT_UWW(VIWTIO_NET_F_WSC_EXT) | BIT_UWW(VIWTIO_NET_F_STANDBY) |           \
	 BIT_UWW(VIWTIO_NET_F_SPEED_DUPWEX) | BIT_UWW(VIWTIO_F_NOTIFY_ON_EMPTY) |                          \
	 BIT_UWW(VIWTIO_F_ANY_WAYOUT) | BIT_UWW(VIWTIO_F_VEWSION_1) | BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM) |      \
	 BIT_UWW(VIWTIO_F_WING_PACKED) | BIT_UWW(VIWTIO_F_OWDEW_PWATFOWM) | BIT_UWW(VIWTIO_F_SW_IOV))

#define VAWID_STATUS_MASK                                                                          \
	(VIWTIO_CONFIG_S_ACKNOWWEDGE | VIWTIO_CONFIG_S_DWIVEW | VIWTIO_CONFIG_S_DWIVEW_OK |        \
	 VIWTIO_CONFIG_S_FEATUWES_OK | VIWTIO_CONFIG_S_NEEDS_WESET | VIWTIO_CONFIG_S_FAIWED)

#define MWX5_FEATUWE(_mvdev, _featuwe) (!!((_mvdev)->actuaw_featuwes & BIT_UWW(_featuwe)))

#define MWX5V_UNTAGGED 0x1000

stwuct mwx5_vdpa_cq_buf {
	stwuct mwx5_fwag_buf_ctww fbc;
	stwuct mwx5_fwag_buf fwag_buf;
	int cqe_size;
	int nent;
};

stwuct mwx5_vdpa_cq {
	stwuct mwx5_cowe_cq mcq;
	stwuct mwx5_vdpa_cq_buf buf;
	stwuct mwx5_db db;
	int cqe;
};

stwuct mwx5_vdpa_umem {
	stwuct mwx5_fwag_buf_ctww fbc;
	stwuct mwx5_fwag_buf fwag_buf;
	int size;
	u32 id;
};

stwuct mwx5_vdpa_qp {
	stwuct mwx5_cowe_qp mqp;
	stwuct mwx5_fwag_buf fwag_buf;
	stwuct mwx5_db db;
	u16 head;
	boow fw;
};

stwuct mwx5_vq_westowe_info {
	u32 num_ent;
	u64 desc_addw;
	u64 device_addw;
	u64 dwivew_addw;
	u16 avaiw_index;
	u16 used_index;
	stwuct msi_map map;
	boow weady;
	boow westowe;
};

stwuct mwx5_vdpa_viwtqueue {
	boow weady;
	u64 desc_addw;
	u64 device_addw;
	u64 dwivew_addw;
	u32 num_ent;

	/* Wesouwces fow impwementing the notification channew fwom the device
	 * to the dwivew. fwqp is the fiwmwawe end of an WC connection; the
	 * othew end is vqqp used by the dwivew. cq is whewe compwetions awe
	 * wepowted.
	 */
	stwuct mwx5_vdpa_cq cq;
	stwuct mwx5_vdpa_qp fwqp;
	stwuct mwx5_vdpa_qp vqqp;

	/* umem wesouwces awe wequiwed fow the viwtqueue opewation. They'we use
	 * is intewnaw and they must be pwovided by the dwivew.
	 */
	stwuct mwx5_vdpa_umem umem1;
	stwuct mwx5_vdpa_umem umem2;
	stwuct mwx5_vdpa_umem umem3;

	u32 countew_set_id;
	boow initiawized;
	int index;
	u32 viwtq_id;
	stwuct mwx5_vdpa_net *ndev;
	u16 avaiw_idx;
	u16 used_idx;
	int fw_state;

	u64 modified_fiewds;

	stwuct mwx5_vdpa_mw *vq_mw;
	stwuct mwx5_vdpa_mw *desc_mw;

	stwuct msi_map map;

	/* keep wast in the stwuct */
	stwuct mwx5_vq_westowe_info wi;
};

static boow is_index_vawid(stwuct mwx5_vdpa_dev *mvdev, u16 idx)
{
	if (!(mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_MQ))) {
		if (!(mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ)))
			wetuwn idx < 2;
		ewse
			wetuwn idx < 3;
	}

	wetuwn idx <= mvdev->max_idx;
}

static void fwee_wesouwces(stwuct mwx5_vdpa_net *ndev);
static void init_mvqs(stwuct mwx5_vdpa_net *ndev);
static int setup_dwivew(stwuct mwx5_vdpa_dev *mvdev);
static void teawdown_dwivew(stwuct mwx5_vdpa_net *ndev);

static boow mwx5_vdpa_debug;

#define MWX5_CVQ_MAX_ENT 16

#define MWX5_WOG_VIO_FWAG(_featuwe)                                                                \
	do {                                                                                       \
		if (featuwes & BIT_UWW(_featuwe))                                                  \
			mwx5_vdpa_info(mvdev, "%s\n", #_featuwe);                                  \
	} whiwe (0)

#define MWX5_WOG_VIO_STAT(_status)                                                                 \
	do {                                                                                       \
		if (status & (_status))                                                            \
			mwx5_vdpa_info(mvdev, "%s\n", #_status);                                   \
	} whiwe (0)

/* TODO: cwoss-endian suppowt */
static inwine boow mwx5_vdpa_is_wittwe_endian(stwuct mwx5_vdpa_dev *mvdev)
{
	wetuwn viwtio_wegacy_is_wittwe_endian() ||
		(mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_F_VEWSION_1));
}

static u16 mwx5vdpa16_to_cpu(stwuct mwx5_vdpa_dev *mvdev, __viwtio16 vaw)
{
	wetuwn __viwtio16_to_cpu(mwx5_vdpa_is_wittwe_endian(mvdev), vaw);
}

static __viwtio16 cpu_to_mwx5vdpa16(stwuct mwx5_vdpa_dev *mvdev, u16 vaw)
{
	wetuwn __cpu_to_viwtio16(mwx5_vdpa_is_wittwe_endian(mvdev), vaw);
}

static u16 ctww_vq_idx(stwuct mwx5_vdpa_dev *mvdev)
{
	if (!(mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_MQ)))
		wetuwn 2;

	wetuwn mvdev->max_vqs;
}

static boow is_ctww_vq_idx(stwuct mwx5_vdpa_dev *mvdev, u16 idx)
{
	wetuwn idx == ctww_vq_idx(mvdev);
}

static void pwint_status(stwuct mwx5_vdpa_dev *mvdev, u8 status, boow set)
{
	if (status & ~VAWID_STATUS_MASK)
		mwx5_vdpa_wawn(mvdev, "Wawning: thewe awe invawid status bits 0x%x\n",
			       status & ~VAWID_STATUS_MASK);

	if (!mwx5_vdpa_debug)
		wetuwn;

	mwx5_vdpa_info(mvdev, "dwivew status %s", set ? "set" : "get");
	if (set && !status) {
		mwx5_vdpa_info(mvdev, "dwivew wesets the device\n");
		wetuwn;
	}

	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_ACKNOWWEDGE);
	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_DWIVEW);
	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_DWIVEW_OK);
	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_FEATUWES_OK);
	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_NEEDS_WESET);
	MWX5_WOG_VIO_STAT(VIWTIO_CONFIG_S_FAIWED);
}

static void pwint_featuwes(stwuct mwx5_vdpa_dev *mvdev, u64 featuwes, boow set)
{
	if (featuwes & ~VAWID_FEATUWES_MASK)
		mwx5_vdpa_wawn(mvdev, "Thewe awe invawid featuwe bits 0x%wwx\n",
			       featuwes & ~VAWID_FEATUWES_MASK);

	if (!mwx5_vdpa_debug)
		wetuwn;

	mwx5_vdpa_info(mvdev, "dwivew %s featuwe bits:\n", set ? "sets" : "weads");
	if (!featuwes)
		mwx5_vdpa_info(mvdev, "aww featuwe bits awe cweawed\n");

	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CSUM);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_CSUM);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_GUEST_OFFWOADS);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_MTU);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_MAC);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_TSO4);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_TSO6);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_ECN);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_UFO);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_HOST_TSO4);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_HOST_TSO6);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_HOST_ECN);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_HOST_UFO);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_MWG_WXBUF);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_STATUS);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_VQ);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_WX);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_VWAN);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_WX_EXTWA);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_GUEST_ANNOUNCE);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_MQ);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_CTWW_MAC_ADDW);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_HASH_WEPOWT);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_WSS);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_WSC_EXT);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_STANDBY);
	MWX5_WOG_VIO_FWAG(VIWTIO_NET_F_SPEED_DUPWEX);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_NOTIFY_ON_EMPTY);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_ANY_WAYOUT);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_VEWSION_1);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_ACCESS_PWATFOWM);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_WING_PACKED);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_OWDEW_PWATFOWM);
	MWX5_WOG_VIO_FWAG(VIWTIO_F_SW_IOV);
}

static int cweate_tis(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_dev *mvdev = &ndev->mvdev;
	u32 in[MWX5_ST_SZ_DW(cweate_tis_in)] = {};
	void *tisc;
	int eww;

	tisc = MWX5_ADDW_OF(cweate_tis_in, in, ctx);
	MWX5_SET(tisc, tisc, twanspowt_domain, ndev->wes.tdn);
	eww = mwx5_vdpa_cweate_tis(mvdev, in, &ndev->wes.tisn);
	if (eww)
		mwx5_vdpa_wawn(mvdev, "cweate TIS (%d)\n", eww);

	wetuwn eww;
}

static void destwoy_tis(stwuct mwx5_vdpa_net *ndev)
{
	mwx5_vdpa_destwoy_tis(&ndev->mvdev, ndev->wes.tisn);
}

#define MWX5_VDPA_CQE_SIZE 64
#define MWX5_VDPA_WOG_CQE_SIZE iwog2(MWX5_VDPA_CQE_SIZE)

static int cq_fwag_buf_awwoc(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_cq_buf *buf, int nent)
{
	stwuct mwx5_fwag_buf *fwag_buf = &buf->fwag_buf;
	u8 wog_wq_stwide = MWX5_VDPA_WOG_CQE_SIZE;
	u8 wog_wq_sz = MWX5_VDPA_WOG_CQE_SIZE;
	int eww;

	eww = mwx5_fwag_buf_awwoc_node(ndev->mvdev.mdev, nent * MWX5_VDPA_CQE_SIZE, fwag_buf,
				       ndev->mvdev.mdev->pwiv.numa_node);
	if (eww)
		wetuwn eww;

	mwx5_init_fbc(fwag_buf->fwags, wog_wq_stwide, wog_wq_sz, &buf->fbc);

	buf->cqe_size = MWX5_VDPA_CQE_SIZE;
	buf->nent = nent;

	wetuwn 0;
}

static int umem_fwag_buf_awwoc(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_umem *umem, int size)
{
	stwuct mwx5_fwag_buf *fwag_buf = &umem->fwag_buf;

	wetuwn mwx5_fwag_buf_awwoc_node(ndev->mvdev.mdev, size, fwag_buf,
					ndev->mvdev.mdev->pwiv.numa_node);
}

static void cq_fwag_buf_fwee(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_cq_buf *buf)
{
	mwx5_fwag_buf_fwee(ndev->mvdev.mdev, &buf->fwag_buf);
}

static void *get_cqe(stwuct mwx5_vdpa_cq *vcq, int n)
{
	wetuwn mwx5_fwag_buf_get_wqe(&vcq->buf.fbc, n);
}

static void cq_fwag_buf_init(stwuct mwx5_vdpa_cq *vcq, stwuct mwx5_vdpa_cq_buf *buf)
{
	stwuct mwx5_cqe64 *cqe64;
	void *cqe;
	int i;

	fow (i = 0; i < buf->nent; i++) {
		cqe = get_cqe(vcq, i);
		cqe64 = cqe;
		cqe64->op_own = MWX5_CQE_INVAWID << 4;
	}
}

static void *get_sw_cqe(stwuct mwx5_vdpa_cq *cq, int n)
{
	stwuct mwx5_cqe64 *cqe64 = get_cqe(cq, n & (cq->cqe - 1));

	if (wikewy(get_cqe_opcode(cqe64) != MWX5_CQE_INVAWID) &&
	    !((cqe64->op_own & MWX5_CQE_OWNEW_MASK) ^ !!(n & cq->cqe)))
		wetuwn cqe64;

	wetuwn NUWW;
}

static void wx_post(stwuct mwx5_vdpa_qp *vqp, int n)
{
	vqp->head += n;
	vqp->db.db[0] = cpu_to_be32(vqp->head);
}

static void qp_pwepawe(stwuct mwx5_vdpa_net *ndev, boow fw, void *in,
		       stwuct mwx5_vdpa_viwtqueue *mvq, u32 num_ent)
{
	stwuct mwx5_vdpa_qp *vqp;
	__be64 *pas;
	void *qpc;

	vqp = fw ? &mvq->fwqp : &mvq->vqqp;
	MWX5_SET(cweate_qp_in, in, uid, ndev->mvdev.wes.uid);
	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	if (vqp->fw) {
		/* Fiwmwawe QP is awwocated by the dwivew fow the fiwmwawe's
		 * use so we can skip pawt of the pawams as they wiww be chosen by fiwmwawe
		 */
		qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
		MWX5_SET(qpc, qpc, wq_type, MWX5_ZEWO_WEN_WQ);
		MWX5_SET(qpc, qpc, no_sq, 1);
		wetuwn;
	}

	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, pd, ndev->mvdev.wes.pdn);
	MWX5_SET(qpc, qpc, mtu, MWX5_QPC_MTU_256_BYTES);
	MWX5_SET(qpc, qpc, uaw_page, ndev->mvdev.wes.uaw->index);
	MWX5_SET(qpc, qpc, wog_page_size, vqp->fwag_buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(qpc, qpc, no_sq, 1);
	MWX5_SET(qpc, qpc, cqn_wcv, mvq->cq.mcq.cqn);
	MWX5_SET(qpc, qpc, wog_wq_size, iwog2(num_ent));
	MWX5_SET(qpc, qpc, wq_type, MWX5_NON_ZEWO_WQ);
	pas = (__be64 *)MWX5_ADDW_OF(cweate_qp_in, in, pas);
	mwx5_fiww_page_fwag_awway(&vqp->fwag_buf, pas);
}

static int wq_buf_awwoc(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_qp *vqp, u32 num_ent)
{
	wetuwn mwx5_fwag_buf_awwoc_node(ndev->mvdev.mdev,
					num_ent * sizeof(stwuct mwx5_wqe_data_seg), &vqp->fwag_buf,
					ndev->mvdev.mdev->pwiv.numa_node);
}

static void wq_buf_fwee(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_qp *vqp)
{
	mwx5_fwag_buf_fwee(ndev->mvdev.mdev, &vqp->fwag_buf);
}

static int qp_cweate(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq,
		     stwuct mwx5_vdpa_qp *vqp)
{
	stwuct mwx5_cowe_dev *mdev = ndev->mvdev.mdev;
	int inwen = MWX5_ST_SZ_BYTES(cweate_qp_in);
	u32 out[MWX5_ST_SZ_DW(cweate_qp_out)] = {};
	void *qpc;
	void *in;
	int eww;

	if (!vqp->fw) {
		vqp = &mvq->vqqp;
		eww = wq_buf_awwoc(ndev, vqp, mvq->num_ent);
		if (eww)
			wetuwn eww;

		eww = mwx5_db_awwoc(ndev->mvdev.mdev, &vqp->db);
		if (eww)
			goto eww_db;
		inwen += vqp->fwag_buf.npages * sizeof(__be64);
	}

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_kzawwoc;
	}

	qp_pwepawe(ndev, vqp->fw, in, mvq, mvq->num_ent);
	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, pd, ndev->mvdev.wes.pdn);
	MWX5_SET(qpc, qpc, mtu, MWX5_QPC_MTU_256_BYTES);
	if (!vqp->fw)
		MWX5_SET64(qpc, qpc, dbw_addw, vqp->db.dma);
	MWX5_SET(cweate_qp_in, in, opcode, MWX5_CMD_OP_CWEATE_QP);
	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	kfwee(in);
	if (eww)
		goto eww_kzawwoc;

	vqp->mqp.uid = ndev->mvdev.wes.uid;
	vqp->mqp.qpn = MWX5_GET(cweate_qp_out, out, qpn);

	if (!vqp->fw)
		wx_post(vqp, mvq->num_ent);

	wetuwn 0;

eww_kzawwoc:
	if (!vqp->fw)
		mwx5_db_fwee(ndev->mvdev.mdev, &vqp->db);
eww_db:
	if (!vqp->fw)
		wq_buf_fwee(ndev, vqp);

	wetuwn eww;
}

static void qp_destwoy(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_qp *vqp)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_qp_in)] = {};

	MWX5_SET(destwoy_qp_in, in, opcode, MWX5_CMD_OP_DESTWOY_QP);
	MWX5_SET(destwoy_qp_in, in, qpn, vqp->mqp.qpn);
	MWX5_SET(destwoy_qp_in, in, uid, ndev->mvdev.wes.uid);
	if (mwx5_cmd_exec_in(ndev->mvdev.mdev, destwoy_qp, in))
		mwx5_vdpa_wawn(&ndev->mvdev, "destwoy qp 0x%x\n", vqp->mqp.qpn);
	if (!vqp->fw) {
		mwx5_db_fwee(ndev->mvdev.mdev, &vqp->db);
		wq_buf_fwee(ndev, vqp);
	}
}

static void *next_cqe_sw(stwuct mwx5_vdpa_cq *cq)
{
	wetuwn get_sw_cqe(cq, cq->mcq.cons_index);
}

static int mwx5_vdpa_poww_one(stwuct mwx5_vdpa_cq *vcq)
{
	stwuct mwx5_cqe64 *cqe64;

	cqe64 = next_cqe_sw(vcq);
	if (!cqe64)
		wetuwn -EAGAIN;

	vcq->mcq.cons_index++;
	wetuwn 0;
}

static void mwx5_vdpa_handwe_compwetions(stwuct mwx5_vdpa_viwtqueue *mvq, int num)
{
	stwuct mwx5_vdpa_net *ndev = mvq->ndev;
	stwuct vdpa_cawwback *event_cb;

	event_cb = &ndev->event_cbs[mvq->index];
	mwx5_cq_set_ci(&mvq->cq.mcq);

	/* make suwe CQ cosumew update is visibwe to the hawdwawe befowe updating
	 * WX doowbeww wecowd.
	 */
	dma_wmb();
	wx_post(&mvq->vqqp, num);
	if (event_cb->cawwback)
		event_cb->cawwback(event_cb->pwivate);
}

static void mwx5_vdpa_cq_comp(stwuct mwx5_cowe_cq *mcq, stwuct mwx5_eqe *eqe)
{
	stwuct mwx5_vdpa_viwtqueue *mvq = containew_of(mcq, stwuct mwx5_vdpa_viwtqueue, cq.mcq);
	stwuct mwx5_vdpa_net *ndev = mvq->ndev;
	void __iomem *uaw_page = ndev->mvdev.wes.uaw->map;
	int num = 0;

	whiwe (!mwx5_vdpa_poww_one(&mvq->cq)) {
		num++;
		if (num > mvq->num_ent / 2) {
			/* If compwetions keep coming whiwe we poww, we want to
			 * wet the hawdwawe know that we consumed them by
			 * updating the doowbeww wecowd.  We awso wet vdpa cowe
			 * know about this so it passes it on the viwtio dwivew
			 * on the guest.
			 */
			mwx5_vdpa_handwe_compwetions(mvq, num);
			num = 0;
		}
	}

	if (num)
		mwx5_vdpa_handwe_compwetions(mvq, num);

	mwx5_cq_awm(&mvq->cq.mcq, MWX5_CQ_DB_WEQ_NOT, uaw_page, mvq->cq.mcq.cons_index);
}

static int cq_cweate(stwuct mwx5_vdpa_net *ndev, u16 idx, u32 num_ent)
{
	stwuct mwx5_vdpa_viwtqueue *mvq = &ndev->vqs[idx];
	stwuct mwx5_cowe_dev *mdev = ndev->mvdev.mdev;
	void __iomem *uaw_page = ndev->mvdev.wes.uaw->map;
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	stwuct mwx5_vdpa_cq *vcq = &mvq->cq;
	__be64 *pas;
	int inwen;
	void *cqc;
	void *in;
	int eww;
	int eqn;

	eww = mwx5_db_awwoc(mdev, &vcq->db);
	if (eww)
		wetuwn eww;

	vcq->mcq.set_ci_db = vcq->db.db;
	vcq->mcq.awm_db = vcq->db.db + 1;
	vcq->mcq.cqe_sz = 64;

	eww = cq_fwag_buf_awwoc(ndev, &vcq->buf, num_ent);
	if (eww)
		goto eww_db;

	cq_fwag_buf_init(vcq, &vcq->buf);

	inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		MWX5_FWD_SZ_BYTES(cweate_cq_in, pas[0]) * vcq->buf.fwag_buf.npages;
	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_vzawwoc;
	}

	MWX5_SET(cweate_cq_in, in, uid, ndev->mvdev.wes.uid);
	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, in, pas);
	mwx5_fiww_page_fwag_awway(&vcq->buf.fwag_buf, pas);

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, wog_page_size, vcq->buf.fwag_buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);

	/* Use vectow 0 by defauwt. Considew adding code to choose weast used
	 * vectow.
	 */
	eww = mwx5_comp_eqn_get(mdev, 0, &eqn);
	if (eww)
		goto eww_vec;

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(num_ent));
	MWX5_SET(cqc, cqc, uaw_page, ndev->mvdev.wes.uaw->index);
	MWX5_SET(cqc, cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET64(cqc, cqc, dbw_addw, vcq->db.dma);

	eww = mwx5_cowe_cweate_cq(mdev, &vcq->mcq, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_vec;

	vcq->mcq.comp = mwx5_vdpa_cq_comp;
	vcq->cqe = num_ent;
	vcq->mcq.set_ci_db = vcq->db.db;
	vcq->mcq.awm_db = vcq->db.db + 1;
	mwx5_cq_awm(&mvq->cq.mcq, MWX5_CQ_DB_WEQ_NOT, uaw_page, mvq->cq.mcq.cons_index);
	kfwee(in);
	wetuwn 0;

eww_vec:
	kfwee(in);
eww_vzawwoc:
	cq_fwag_buf_fwee(ndev, &vcq->buf);
eww_db:
	mwx5_db_fwee(ndev->mvdev.mdev, &vcq->db);
	wetuwn eww;
}

static void cq_destwoy(stwuct mwx5_vdpa_net *ndev, u16 idx)
{
	stwuct mwx5_vdpa_viwtqueue *mvq = &ndev->vqs[idx];
	stwuct mwx5_cowe_dev *mdev = ndev->mvdev.mdev;
	stwuct mwx5_vdpa_cq *vcq = &mvq->cq;

	if (mwx5_cowe_destwoy_cq(mdev, &vcq->mcq)) {
		mwx5_vdpa_wawn(&ndev->mvdev, "destwoy CQ 0x%x\n", vcq->mcq.cqn);
		wetuwn;
	}
	cq_fwag_buf_fwee(ndev, &vcq->buf);
	mwx5_db_fwee(ndev->mvdev.mdev, &vcq->db);
}

static int wead_umem_pawams(stwuct mwx5_vdpa_net *ndev)
{
	u32 in[MWX5_ST_SZ_DW(quewy_hca_cap_in)] = {};
	u16 opmod = (MWX5_CAP_VDPA_EMUWATION << 1) | (HCA_CAP_OPMOD_GET_CUW & 0x01);
	stwuct mwx5_cowe_dev *mdev = ndev->mvdev.mdev;
	int out_size;
	void *caps;
	void *out;
	int eww;

	out_size = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	out = kzawwoc(out_size, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_hca_cap_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_CAP);
	MWX5_SET(quewy_hca_cap_in, in, op_mod, opmod);
	eww = mwx5_cmd_exec_inout(mdev, quewy_hca_cap, in, out);
	if (eww) {
		mwx5_vdpa_wawn(&ndev->mvdev,
			"Faiwed weading vdpa umem capabiwities with eww %d\n", eww);
		goto out;
	}

	caps =  MWX5_ADDW_OF(quewy_hca_cap_out, out, capabiwity);

	ndev->umem_1_buffew_pawam_a = MWX5_GET(viwtio_emuwation_cap, caps, umem_1_buffew_pawam_a);
	ndev->umem_1_buffew_pawam_b = MWX5_GET(viwtio_emuwation_cap, caps, umem_1_buffew_pawam_b);

	ndev->umem_2_buffew_pawam_a = MWX5_GET(viwtio_emuwation_cap, caps, umem_2_buffew_pawam_a);
	ndev->umem_2_buffew_pawam_b = MWX5_GET(viwtio_emuwation_cap, caps, umem_2_buffew_pawam_b);

	ndev->umem_3_buffew_pawam_a = MWX5_GET(viwtio_emuwation_cap, caps, umem_3_buffew_pawam_a);
	ndev->umem_3_buffew_pawam_b = MWX5_GET(viwtio_emuwation_cap, caps, umem_3_buffew_pawam_b);

out:
	kfwee(out);
	wetuwn 0;
}

static void set_umem_size(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq, int num,
			  stwuct mwx5_vdpa_umem **umemp)
{
	u32 p_a;
	u32 p_b;

	switch (num) {
	case 1:
		p_a = ndev->umem_1_buffew_pawam_a;
		p_b = ndev->umem_1_buffew_pawam_b;
		*umemp = &mvq->umem1;
		bweak;
	case 2:
		p_a = ndev->umem_2_buffew_pawam_a;
		p_b = ndev->umem_2_buffew_pawam_b;
		*umemp = &mvq->umem2;
		bweak;
	case 3:
		p_a = ndev->umem_3_buffew_pawam_a;
		p_b = ndev->umem_3_buffew_pawam_b;
		*umemp = &mvq->umem3;
		bweak;
	}

	(*umemp)->size = p_a * mvq->num_ent + p_b;
}

static void umem_fwag_buf_fwee(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_umem *umem)
{
	mwx5_fwag_buf_fwee(ndev->mvdev.mdev, &umem->fwag_buf);
}

static int cweate_umem(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq, int num)
{
	int inwen;
	u32 out[MWX5_ST_SZ_DW(cweate_umem_out)] = {};
	void *um;
	void *in;
	int eww;
	__be64 *pas;
	stwuct mwx5_vdpa_umem *umem;

	set_umem_size(ndev, mvq, num, &umem);
	eww = umem_fwag_buf_awwoc(ndev, umem, umem->size);
	if (eww)
		wetuwn eww;

	inwen = MWX5_ST_SZ_BYTES(cweate_umem_in) + MWX5_ST_SZ_BYTES(mtt) * umem->fwag_buf.npages;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_in;
	}

	MWX5_SET(cweate_umem_in, in, opcode, MWX5_CMD_OP_CWEATE_UMEM);
	MWX5_SET(cweate_umem_in, in, uid, ndev->mvdev.wes.uid);
	um = MWX5_ADDW_OF(cweate_umem_in, in, umem);
	MWX5_SET(umem, um, wog_page_size, umem->fwag_buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(umem, um, num_of_mtt, umem->fwag_buf.npages);

	pas = (__be64 *)MWX5_ADDW_OF(umem, um, mtt[0]);
	mwx5_fiww_page_fwag_awway_pewm(&umem->fwag_buf, pas, MWX5_MTT_PEWM_WW);

	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, inwen, out, sizeof(out));
	if (eww) {
		mwx5_vdpa_wawn(&ndev->mvdev, "cweate umem(%d)\n", eww);
		goto eww_cmd;
	}

	kfwee(in);
	umem->id = MWX5_GET(cweate_umem_out, out, umem_id);

	wetuwn 0;

eww_cmd:
	kfwee(in);
eww_in:
	umem_fwag_buf_fwee(ndev, umem);
	wetuwn eww;
}

static void umem_destwoy(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq, int num)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_umem_in)] = {};
	u32 out[MWX5_ST_SZ_DW(destwoy_umem_out)] = {};
	stwuct mwx5_vdpa_umem *umem;

	switch (num) {
	case 1:
		umem = &mvq->umem1;
		bweak;
	case 2:
		umem = &mvq->umem2;
		bweak;
	case 3:
		umem = &mvq->umem3;
		bweak;
	}

	MWX5_SET(destwoy_umem_in, in, opcode, MWX5_CMD_OP_DESTWOY_UMEM);
	MWX5_SET(destwoy_umem_in, in, umem_id, umem->id);
	if (mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, sizeof(out)))
		wetuwn;

	umem_fwag_buf_fwee(ndev, umem);
}

static int umems_cweate(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	int num;
	int eww;

	fow (num = 1; num <= 3; num++) {
		eww = cweate_umem(ndev, mvq, num);
		if (eww)
			goto eww_umem;
	}
	wetuwn 0;

eww_umem:
	fow (num--; num > 0; num--)
		umem_destwoy(ndev, mvq, num);

	wetuwn eww;
}

static void umems_destwoy(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	int num;

	fow (num = 3; num > 0; num--)
		umem_destwoy(ndev, mvq, num);
}

static int get_queue_type(stwuct mwx5_vdpa_net *ndev)
{
	u32 type_mask;

	type_mask = MWX5_CAP_DEV_VDPA_EMUWATION(ndev->mvdev.mdev, viwtio_queue_type);

	/* pwefew spwit queue */
	if (type_mask & MWX5_VIWTIO_EMUWATION_CAP_VIWTIO_QUEUE_TYPE_SPWIT)
		wetuwn MWX5_VIWTIO_EMUWATION_VIWTIO_QUEUE_TYPE_SPWIT;

	WAWN_ON(!(type_mask & MWX5_VIWTIO_EMUWATION_CAP_VIWTIO_QUEUE_TYPE_PACKED));

	wetuwn MWX5_VIWTIO_EMUWATION_VIWTIO_QUEUE_TYPE_PACKED;
}

static boow vq_is_tx(u16 idx)
{
	wetuwn idx % 2;
}

enum {
	MWX5_VIWTIO_NET_F_MWG_WXBUF = 2,
	MWX5_VIWTIO_NET_F_HOST_ECN = 4,
	MWX5_VIWTIO_NET_F_GUEST_ECN = 6,
	MWX5_VIWTIO_NET_F_GUEST_TSO6 = 7,
	MWX5_VIWTIO_NET_F_GUEST_TSO4 = 8,
	MWX5_VIWTIO_NET_F_GUEST_CSUM = 9,
	MWX5_VIWTIO_NET_F_CSUM = 10,
	MWX5_VIWTIO_NET_F_HOST_TSO6 = 11,
	MWX5_VIWTIO_NET_F_HOST_TSO4 = 12,
};

static u16 get_featuwes(u64 featuwes)
{
	wetuwn (!!(featuwes & BIT_UWW(VIWTIO_NET_F_MWG_WXBUF)) << MWX5_VIWTIO_NET_F_MWG_WXBUF) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_HOST_ECN)) << MWX5_VIWTIO_NET_F_HOST_ECN) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_GUEST_ECN)) << MWX5_VIWTIO_NET_F_GUEST_ECN) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_GUEST_TSO6)) << MWX5_VIWTIO_NET_F_GUEST_TSO6) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_GUEST_TSO4)) << MWX5_VIWTIO_NET_F_GUEST_TSO4) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_CSUM)) << MWX5_VIWTIO_NET_F_CSUM) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_HOST_TSO6)) << MWX5_VIWTIO_NET_F_HOST_TSO6) |
	       (!!(featuwes & BIT_UWW(VIWTIO_NET_F_HOST_TSO4)) << MWX5_VIWTIO_NET_F_HOST_TSO4);
}

static boow countews_suppowted(const stwuct mwx5_vdpa_dev *mvdev)
{
	wetuwn MWX5_CAP_GEN_64(mvdev->mdev, genewaw_obj_types) &
	       BIT_UWW(MWX5_OBJ_TYPE_VIWTIO_Q_COUNTEWS);
}

static boow msix_mode_suppowted(stwuct mwx5_vdpa_dev *mvdev)
{
	wetuwn MWX5_CAP_DEV_VDPA_EMUWATION(mvdev->mdev, event_mode) &
		(1 << MWX5_VIWTIO_Q_EVENT_MODE_MSIX_MODE) &&
		pci_msix_can_awwoc_dyn(mvdev->mdev->pdev);
}

static int cweate_viwtqueue(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_viwtio_net_q_in);
	u32 out[MWX5_ST_SZ_DW(cweate_viwtio_net_q_out)] = {};
	stwuct mwx5_vdpa_dev *mvdev = &ndev->mvdev;
	stwuct mwx5_vdpa_mw *vq_mw;
	stwuct mwx5_vdpa_mw *vq_desc_mw;
	void *obj_context;
	u16 mwx_featuwes;
	void *cmd_hdw;
	void *vq_ctx;
	void *in;
	int eww;

	eww = umems_cweate(ndev, mvq);
	if (eww)
		wetuwn eww;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	mwx_featuwes = get_featuwes(ndev->mvdev.actuaw_featuwes);
	cmd_hdw = MWX5_ADDW_OF(cweate_viwtio_net_q_in, in, genewaw_obj_in_cmd_hdw);

	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_VIWTIO_NET_Q);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, uid, ndev->mvdev.wes.uid);

	obj_context = MWX5_ADDW_OF(cweate_viwtio_net_q_in, in, obj_context);
	MWX5_SET(viwtio_net_q_object, obj_context, hw_avaiwabwe_index, mvq->avaiw_idx);
	MWX5_SET(viwtio_net_q_object, obj_context, hw_used_index, mvq->used_idx);
	MWX5_SET(viwtio_net_q_object, obj_context, queue_featuwe_bit_mask_12_3,
		 mwx_featuwes >> 3);
	MWX5_SET(viwtio_net_q_object, obj_context, queue_featuwe_bit_mask_2_0,
		 mwx_featuwes & 7);
	vq_ctx = MWX5_ADDW_OF(viwtio_net_q_object, obj_context, viwtio_q_context);
	MWX5_SET(viwtio_q, vq_ctx, viwtio_q_type, get_queue_type(ndev));

	if (vq_is_tx(mvq->index))
		MWX5_SET(viwtio_net_q_object, obj_context, tisn_ow_qpn, ndev->wes.tisn);

	if (mvq->map.viwq) {
		MWX5_SET(viwtio_q, vq_ctx, event_mode, MWX5_VIWTIO_Q_EVENT_MODE_MSIX_MODE);
		MWX5_SET(viwtio_q, vq_ctx, event_qpn_ow_msix, mvq->map.index);
	} ewse {
		MWX5_SET(viwtio_q, vq_ctx, event_mode, MWX5_VIWTIO_Q_EVENT_MODE_QP_MODE);
		MWX5_SET(viwtio_q, vq_ctx, event_qpn_ow_msix, mvq->fwqp.mqp.qpn);
	}

	MWX5_SET(viwtio_q, vq_ctx, queue_index, mvq->index);
	MWX5_SET(viwtio_q, vq_ctx, queue_size, mvq->num_ent);
	MWX5_SET(viwtio_q, vq_ctx, viwtio_vewsion_1_0,
		 !!(ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_F_VEWSION_1)));
	MWX5_SET64(viwtio_q, vq_ctx, desc_addw, mvq->desc_addw);
	MWX5_SET64(viwtio_q, vq_ctx, used_addw, mvq->device_addw);
	MWX5_SET64(viwtio_q, vq_ctx, avaiwabwe_addw, mvq->dwivew_addw);
	vq_mw = mvdev->mw[mvdev->gwoup2asid[MWX5_VDPA_DATAVQ_GWOUP]];
	if (vq_mw)
		MWX5_SET(viwtio_q, vq_ctx, viwtio_q_mkey, vq_mw->mkey);

	vq_desc_mw = mvdev->mw[mvdev->gwoup2asid[MWX5_VDPA_DATAVQ_DESC_GWOUP]];
	if (vq_desc_mw && MWX5_CAP_DEV_VDPA_EMUWATION(mvdev->mdev, desc_gwoup_mkey_suppowted))
		MWX5_SET(viwtio_q, vq_ctx, desc_gwoup_mkey, vq_desc_mw->mkey);

	MWX5_SET(viwtio_q, vq_ctx, umem_1_id, mvq->umem1.id);
	MWX5_SET(viwtio_q, vq_ctx, umem_1_size, mvq->umem1.size);
	MWX5_SET(viwtio_q, vq_ctx, umem_2_id, mvq->umem2.id);
	MWX5_SET(viwtio_q, vq_ctx, umem_2_size, mvq->umem2.size);
	MWX5_SET(viwtio_q, vq_ctx, umem_3_id, mvq->umem3.id);
	MWX5_SET(viwtio_q, vq_ctx, umem_3_size, mvq->umem3.size);
	MWX5_SET(viwtio_q, vq_ctx, pd, ndev->mvdev.wes.pdn);
	if (countews_suppowted(&ndev->mvdev))
		MWX5_SET(viwtio_q, vq_ctx, countew_set_id, mvq->countew_set_id);

	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_cmd;

	mvq->fw_state = MWX5_VIWTIO_NET_Q_OBJECT_STATE_INIT;
	kfwee(in);
	mvq->viwtq_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	mwx5_vdpa_get_mw(mvdev, vq_mw);
	mvq->vq_mw = vq_mw;

	if (vq_desc_mw && MWX5_CAP_DEV_VDPA_EMUWATION(mvdev->mdev, desc_gwoup_mkey_suppowted)) {
		mwx5_vdpa_get_mw(mvdev, vq_desc_mw);
		mvq->desc_mw = vq_desc_mw;
	}

	wetuwn 0;

eww_cmd:
	kfwee(in);
eww_awwoc:
	umems_destwoy(ndev, mvq);
	wetuwn eww;
}

static void destwoy_viwtqueue(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_viwtio_net_q_in)] = {};
	u32 out[MWX5_ST_SZ_DW(destwoy_viwtio_net_q_out)] = {};

	MWX5_SET(destwoy_viwtio_net_q_in, in, genewaw_obj_out_cmd_hdw.opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(destwoy_viwtio_net_q_in, in, genewaw_obj_out_cmd_hdw.obj_id, mvq->viwtq_id);
	MWX5_SET(destwoy_viwtio_net_q_in, in, genewaw_obj_out_cmd_hdw.uid, ndev->mvdev.wes.uid);
	MWX5_SET(destwoy_viwtio_net_q_in, in, genewaw_obj_out_cmd_hdw.obj_type,
		 MWX5_OBJ_TYPE_VIWTIO_NET_Q);
	if (mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, sizeof(out))) {
		mwx5_vdpa_wawn(&ndev->mvdev, "destwoy viwtqueue 0x%x\n", mvq->viwtq_id);
		wetuwn;
	}
	mvq->fw_state = MWX5_VIWTIO_NET_Q_OBJECT_NONE;
	umems_destwoy(ndev, mvq);

	mwx5_vdpa_put_mw(&ndev->mvdev, mvq->vq_mw);
	mvq->vq_mw = NUWW;

	mwx5_vdpa_put_mw(&ndev->mvdev, mvq->desc_mw);
	mvq->desc_mw = NUWW;
}

static u32 get_wqpn(stwuct mwx5_vdpa_viwtqueue *mvq, boow fw)
{
	wetuwn fw ? mvq->vqqp.mqp.qpn : mvq->fwqp.mqp.qpn;
}

static u32 get_qpn(stwuct mwx5_vdpa_viwtqueue *mvq, boow fw)
{
	wetuwn fw ? mvq->fwqp.mqp.qpn : mvq->vqqp.mqp.qpn;
}

static void awwoc_inout(stwuct mwx5_vdpa_net *ndev, int cmd, void **in, int *inwen, void **out,
			int *outwen, u32 qpn, u32 wqpn)
{
	void *qpc;
	void *pp;

	switch (cmd) {
	case MWX5_CMD_OP_2WST_QP:
		*inwen = MWX5_ST_SZ_BYTES(qp_2wst_in);
		*outwen = MWX5_ST_SZ_BYTES(qp_2wst_out);
		*in = kzawwoc(*inwen, GFP_KEWNEW);
		*out = kzawwoc(*outwen, GFP_KEWNEW);
		if (!*in || !*out)
			goto outeww;

		MWX5_SET(qp_2wst_in, *in, opcode, cmd);
		MWX5_SET(qp_2wst_in, *in, uid, ndev->mvdev.wes.uid);
		MWX5_SET(qp_2wst_in, *in, qpn, qpn);
		bweak;
	case MWX5_CMD_OP_WST2INIT_QP:
		*inwen = MWX5_ST_SZ_BYTES(wst2init_qp_in);
		*outwen = MWX5_ST_SZ_BYTES(wst2init_qp_out);
		*in = kzawwoc(*inwen, GFP_KEWNEW);
		*out = kzawwoc(MWX5_ST_SZ_BYTES(wst2init_qp_out), GFP_KEWNEW);
		if (!*in || !*out)
			goto outeww;

		MWX5_SET(wst2init_qp_in, *in, opcode, cmd);
		MWX5_SET(wst2init_qp_in, *in, uid, ndev->mvdev.wes.uid);
		MWX5_SET(wst2init_qp_in, *in, qpn, qpn);
		qpc = MWX5_ADDW_OF(wst2init_qp_in, *in, qpc);
		MWX5_SET(qpc, qpc, wemote_qpn, wqpn);
		MWX5_SET(qpc, qpc, wwe, 1);
		pp = MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path);
		MWX5_SET(ads, pp, vhca_powt_num, 1);
		bweak;
	case MWX5_CMD_OP_INIT2WTW_QP:
		*inwen = MWX5_ST_SZ_BYTES(init2wtw_qp_in);
		*outwen = MWX5_ST_SZ_BYTES(init2wtw_qp_out);
		*in = kzawwoc(*inwen, GFP_KEWNEW);
		*out = kzawwoc(MWX5_ST_SZ_BYTES(init2wtw_qp_out), GFP_KEWNEW);
		if (!*in || !*out)
			goto outeww;

		MWX5_SET(init2wtw_qp_in, *in, opcode, cmd);
		MWX5_SET(init2wtw_qp_in, *in, uid, ndev->mvdev.wes.uid);
		MWX5_SET(init2wtw_qp_in, *in, qpn, qpn);
		qpc = MWX5_ADDW_OF(wst2init_qp_in, *in, qpc);
		MWX5_SET(qpc, qpc, mtu, MWX5_QPC_MTU_256_BYTES);
		MWX5_SET(qpc, qpc, wog_msg_max, 30);
		MWX5_SET(qpc, qpc, wemote_qpn, wqpn);
		pp = MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path);
		MWX5_SET(ads, pp, fw, 1);
		bweak;
	case MWX5_CMD_OP_WTW2WTS_QP:
		*inwen = MWX5_ST_SZ_BYTES(wtw2wts_qp_in);
		*outwen = MWX5_ST_SZ_BYTES(wtw2wts_qp_out);
		*in = kzawwoc(*inwen, GFP_KEWNEW);
		*out = kzawwoc(MWX5_ST_SZ_BYTES(wtw2wts_qp_out), GFP_KEWNEW);
		if (!*in || !*out)
			goto outeww;

		MWX5_SET(wtw2wts_qp_in, *in, opcode, cmd);
		MWX5_SET(wtw2wts_qp_in, *in, uid, ndev->mvdev.wes.uid);
		MWX5_SET(wtw2wts_qp_in, *in, qpn, qpn);
		qpc = MWX5_ADDW_OF(wst2init_qp_in, *in, qpc);
		pp = MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path);
		MWX5_SET(ads, pp, ack_timeout, 14);
		MWX5_SET(qpc, qpc, wetwy_count, 7);
		MWX5_SET(qpc, qpc, wnw_wetwy, 7);
		bweak;
	defauwt:
		goto outeww_nuwwify;
	}

	wetuwn;

outeww:
	kfwee(*in);
	kfwee(*out);
outeww_nuwwify:
	*in = NUWW;
	*out = NUWW;
}

static void fwee_inout(void *in, void *out)
{
	kfwee(in);
	kfwee(out);
}

/* Two QPs awe used by each viwtqueue. One is used by the dwivew and one by
 * fiwmwawe. The fw awgument indicates whethew the subjected QP is the one used
 * by fiwmwawe.
 */
static int modify_qp(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq, boow fw, int cmd)
{
	int outwen;
	int inwen;
	void *out;
	void *in;
	int eww;

	awwoc_inout(ndev, cmd, &in, &inwen, &out, &outwen, get_qpn(mvq, fw), get_wqpn(mvq, fw));
	if (!in || !out)
		wetuwn -ENOMEM;

	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, inwen, out, outwen);
	fwee_inout(in, out);
	wetuwn eww;
}

static int connect_qps(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	int eww;

	eww = modify_qp(ndev, mvq, twue, MWX5_CMD_OP_2WST_QP);
	if (eww)
		wetuwn eww;

	eww = modify_qp(ndev, mvq, fawse, MWX5_CMD_OP_2WST_QP);
	if (eww)
		wetuwn eww;

	eww = modify_qp(ndev, mvq, twue, MWX5_CMD_OP_WST2INIT_QP);
	if (eww)
		wetuwn eww;

	eww = modify_qp(ndev, mvq, fawse, MWX5_CMD_OP_WST2INIT_QP);
	if (eww)
		wetuwn eww;

	eww = modify_qp(ndev, mvq, twue, MWX5_CMD_OP_INIT2WTW_QP);
	if (eww)
		wetuwn eww;

	eww = modify_qp(ndev, mvq, fawse, MWX5_CMD_OP_INIT2WTW_QP);
	if (eww)
		wetuwn eww;

	wetuwn modify_qp(ndev, mvq, twue, MWX5_CMD_OP_WTW2WTS_QP);
}

stwuct mwx5_viwtq_attw {
	u8 state;
	u16 avaiwabwe_index;
	u16 used_index;
};

static int quewy_viwtqueue(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq,
			   stwuct mwx5_viwtq_attw *attw)
{
	int outwen = MWX5_ST_SZ_BYTES(quewy_viwtio_net_q_out);
	u32 in[MWX5_ST_SZ_DW(quewy_viwtio_net_q_in)] = {};
	void *out;
	void *obj_context;
	void *cmd_hdw;
	int eww;

	out = kzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	cmd_hdw = MWX5_ADDW_OF(quewy_viwtio_net_q_in, in, genewaw_obj_in_cmd_hdw);

	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_VIWTIO_NET_Q);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_id, mvq->viwtq_id);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, uid, ndev->mvdev.wes.uid);
	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, outwen);
	if (eww)
		goto eww_cmd;

	obj_context = MWX5_ADDW_OF(quewy_viwtio_net_q_out, out, obj_context);
	memset(attw, 0, sizeof(*attw));
	attw->state = MWX5_GET(viwtio_net_q_object, obj_context, state);
	attw->avaiwabwe_index = MWX5_GET(viwtio_net_q_object, obj_context, hw_avaiwabwe_index);
	attw->used_index = MWX5_GET(viwtio_net_q_object, obj_context, hw_used_index);
	kfwee(out);
	wetuwn 0;

eww_cmd:
	kfwee(out);
	wetuwn eww;
}

static boow is_wesumabwe(stwuct mwx5_vdpa_net *ndev)
{
	wetuwn ndev->mvdev.vdev.config->wesume;
}

static boow is_vawid_state_change(int owdstate, int newstate, boow wesumabwe)
{
	switch (owdstate) {
	case MWX5_VIWTIO_NET_Q_OBJECT_STATE_INIT:
		wetuwn newstate == MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY;
	case MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY:
		wetuwn newstate == MWX5_VIWTIO_NET_Q_OBJECT_STATE_SUSPEND;
	case MWX5_VIWTIO_NET_Q_OBJECT_STATE_SUSPEND:
		wetuwn wesumabwe ? newstate == MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY : fawse;
	case MWX5_VIWTIO_NET_Q_OBJECT_STATE_EWW:
	defauwt:
		wetuwn fawse;
	}
}

static boow modifiabwe_viwtqueue_fiewds(stwuct mwx5_vdpa_viwtqueue *mvq)
{
	/* Onwy state is awways modifiabwe */
	if (mvq->modified_fiewds & ~MWX5_VIWTQ_MODIFY_MASK_STATE)
		wetuwn mvq->fw_state == MWX5_VIWTIO_NET_Q_OBJECT_STATE_INIT ||
		       mvq->fw_state == MWX5_VIWTIO_NET_Q_OBJECT_STATE_SUSPEND;

	wetuwn twue;
}

static int modify_viwtqueue(stwuct mwx5_vdpa_net *ndev,
			    stwuct mwx5_vdpa_viwtqueue *mvq,
			    int state)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_viwtio_net_q_in);
	u32 out[MWX5_ST_SZ_DW(modify_viwtio_net_q_out)] = {};
	stwuct mwx5_vdpa_dev *mvdev = &ndev->mvdev;
	stwuct mwx5_vdpa_mw *desc_mw = NUWW;
	stwuct mwx5_vdpa_mw *vq_mw = NUWW;
	boow state_change = fawse;
	void *obj_context;
	void *cmd_hdw;
	void *vq_ctx;
	void *in;
	int eww;

	if (mvq->fw_state == MWX5_VIWTIO_NET_Q_OBJECT_NONE)
		wetuwn 0;

	if (!modifiabwe_viwtqueue_fiewds(mvq))
		wetuwn -EINVAW;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	cmd_hdw = MWX5_ADDW_OF(modify_viwtio_net_q_in, in, genewaw_obj_in_cmd_hdw);

	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_VIWTIO_NET_Q);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_id, mvq->viwtq_id);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, uid, ndev->mvdev.wes.uid);

	obj_context = MWX5_ADDW_OF(modify_viwtio_net_q_in, in, obj_context);
	vq_ctx = MWX5_ADDW_OF(viwtio_net_q_object, obj_context, viwtio_q_context);

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_STATE) {
		if (!is_vawid_state_change(mvq->fw_state, state, is_wesumabwe(ndev))) {
			eww = -EINVAW;
			goto done;
		}

		MWX5_SET(viwtio_net_q_object, obj_context, state, state);
		state_change = twue;
	}

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_ADDWS) {
		MWX5_SET64(viwtio_q, vq_ctx, desc_addw, mvq->desc_addw);
		MWX5_SET64(viwtio_q, vq_ctx, used_addw, mvq->device_addw);
		MWX5_SET64(viwtio_q, vq_ctx, avaiwabwe_addw, mvq->dwivew_addw);
	}

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_AVAIW_IDX)
		MWX5_SET(viwtio_net_q_object, obj_context, hw_avaiwabwe_index, mvq->avaiw_idx);

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_USED_IDX)
		MWX5_SET(viwtio_net_q_object, obj_context, hw_used_index, mvq->used_idx);

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_MKEY) {
		vq_mw = mvdev->mw[mvdev->gwoup2asid[MWX5_VDPA_DATAVQ_GWOUP]];

		if (vq_mw)
			MWX5_SET(viwtio_q, vq_ctx, viwtio_q_mkey, vq_mw->mkey);
		ewse
			mvq->modified_fiewds &= ~MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_MKEY;
	}

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_DESC_GWOUP_MKEY) {
		desc_mw = mvdev->mw[mvdev->gwoup2asid[MWX5_VDPA_DATAVQ_DESC_GWOUP]];

		if (desc_mw && MWX5_CAP_DEV_VDPA_EMUWATION(mvdev->mdev, desc_gwoup_mkey_suppowted))
			MWX5_SET(viwtio_q, vq_ctx, desc_gwoup_mkey, desc_mw->mkey);
		ewse
			mvq->modified_fiewds &= ~MWX5_VIWTQ_MODIFY_MASK_DESC_GWOUP_MKEY;
	}

	MWX5_SET64(viwtio_net_q_object, obj_context, modify_fiewd_sewect, mvq->modified_fiewds);
	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto done;

	if (state_change)
		mvq->fw_state = state;

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_MKEY) {
		mwx5_vdpa_put_mw(mvdev, mvq->vq_mw);
		mwx5_vdpa_get_mw(mvdev, vq_mw);
		mvq->vq_mw = vq_mw;
	}

	if (mvq->modified_fiewds & MWX5_VIWTQ_MODIFY_MASK_DESC_GWOUP_MKEY) {
		mwx5_vdpa_put_mw(mvdev, mvq->desc_mw);
		mwx5_vdpa_get_mw(mvdev, desc_mw);
		mvq->desc_mw = desc_mw;
	}

	mvq->modified_fiewds = 0;

done:
	kfwee(in);
	wetuwn eww;
}

static int modify_viwtqueue_state(stwuct mwx5_vdpa_net *ndev,
				  stwuct mwx5_vdpa_viwtqueue *mvq,
				  unsigned int state)
{
	mvq->modified_fiewds |= MWX5_VIWTQ_MODIFY_MASK_STATE;
	wetuwn modify_viwtqueue(ndev, mvq, state);
}

static int countew_set_awwoc(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	u32 in[MWX5_ST_SZ_DW(cweate_viwtio_q_countews_in)] = {};
	u32 out[MWX5_ST_SZ_DW(cweate_viwtio_q_countews_out)] = {};
	void *cmd_hdw;
	int eww;

	if (!countews_suppowted(&ndev->mvdev))
		wetuwn 0;

	cmd_hdw = MWX5_ADDW_OF(cweate_viwtio_q_countews_in, in, hdw);

	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_VIWTIO_Q_COUNTEWS);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, uid, ndev->mvdev.wes.uid);

	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	mvq->countew_set_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn 0;
}

static void countew_set_deawwoc(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_viwtio_q_countews_in)] = {};
	u32 out[MWX5_ST_SZ_DW(destwoy_viwtio_q_countews_out)] = {};

	if (!countews_suppowted(&ndev->mvdev))
		wetuwn;

	MWX5_SET(destwoy_viwtio_q_countews_in, in, hdw.opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(destwoy_viwtio_q_countews_in, in, hdw.obj_id, mvq->countew_set_id);
	MWX5_SET(destwoy_viwtio_q_countews_in, in, hdw.uid, ndev->mvdev.wes.uid);
	MWX5_SET(destwoy_viwtio_q_countews_in, in, hdw.obj_type, MWX5_OBJ_TYPE_VIWTIO_Q_COUNTEWS);
	if (mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, sizeof(out)))
		mwx5_vdpa_wawn(&ndev->mvdev, "deawwoc countew set 0x%x\n", mvq->countew_set_id);
}

static iwqwetuwn_t mwx5_vdpa_int_handwew(int iwq, void *pwiv)
{
	stwuct vdpa_cawwback *cb = pwiv;

	if (cb->cawwback)
		wetuwn cb->cawwback(cb->pwivate);

	wetuwn IWQ_HANDWED;
}

static void awwoc_vectow(stwuct mwx5_vdpa_net *ndev,
			 stwuct mwx5_vdpa_viwtqueue *mvq)
{
	stwuct mwx5_vdpa_iwq_poow *iwqp = &ndev->iwqp;
	stwuct mwx5_vdpa_iwq_poow_entwy *ent;
	int eww;
	int i;

	fow (i = 0; i < iwqp->num_ent; i++) {
		ent = &iwqp->entwies[i];
		if (!ent->used) {
			snpwintf(ent->name, MWX5_VDPA_IWQ_NAME_WEN, "%s-vq-%d",
				 dev_name(&ndev->mvdev.vdev.dev), mvq->index);
			ent->dev_id = &ndev->event_cbs[mvq->index];
			eww = wequest_iwq(ent->map.viwq, mwx5_vdpa_int_handwew, 0,
					  ent->name, ent->dev_id);
			if (eww)
				wetuwn;

			ent->used = twue;
			mvq->map = ent->map;
			wetuwn;
		}
	}
}

static void deawwoc_vectow(stwuct mwx5_vdpa_net *ndev,
			   stwuct mwx5_vdpa_viwtqueue *mvq)
{
	stwuct mwx5_vdpa_iwq_poow *iwqp = &ndev->iwqp;
	int i;

	fow (i = 0; i < iwqp->num_ent; i++)
		if (mvq->map.viwq == iwqp->entwies[i].map.viwq) {
			fwee_iwq(mvq->map.viwq, iwqp->entwies[i].dev_id);
			iwqp->entwies[i].used = fawse;
			wetuwn;
		}
}

static int setup_vq(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	u16 idx = mvq->index;
	int eww;

	if (!mvq->num_ent)
		wetuwn 0;

	if (mvq->initiawized)
		wetuwn 0;

	eww = cq_cweate(ndev, idx, mvq->num_ent);
	if (eww)
		wetuwn eww;

	eww = qp_cweate(ndev, mvq, &mvq->fwqp);
	if (eww)
		goto eww_fwqp;

	eww = qp_cweate(ndev, mvq, &mvq->vqqp);
	if (eww)
		goto eww_vqqp;

	eww = connect_qps(ndev, mvq);
	if (eww)
		goto eww_connect;

	eww = countew_set_awwoc(ndev, mvq);
	if (eww)
		goto eww_connect;

	awwoc_vectow(ndev, mvq);
	eww = cweate_viwtqueue(ndev, mvq);
	if (eww)
		goto eww_vq;

	if (mvq->weady) {
		eww = modify_viwtqueue_state(ndev, mvq, MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY);
		if (eww) {
			mwx5_vdpa_wawn(&ndev->mvdev, "faiwed to modify to weady vq idx %d(%d)\n",
				       idx, eww);
			goto eww_modify;
		}
	}

	mvq->initiawized = twue;
	wetuwn 0;

eww_modify:
	destwoy_viwtqueue(ndev, mvq);
eww_vq:
	deawwoc_vectow(ndev, mvq);
	countew_set_deawwoc(ndev, mvq);
eww_connect:
	qp_destwoy(ndev, &mvq->vqqp);
eww_vqqp:
	qp_destwoy(ndev, &mvq->fwqp);
eww_fwqp:
	cq_destwoy(ndev, idx);
	wetuwn eww;
}

static void suspend_vq(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	stwuct mwx5_viwtq_attw attw;

	if (!mvq->initiawized)
		wetuwn;

	if (mvq->fw_state != MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY)
		wetuwn;

	if (modify_viwtqueue_state(ndev, mvq, MWX5_VIWTIO_NET_Q_OBJECT_STATE_SUSPEND))
		mwx5_vdpa_wawn(&ndev->mvdev, "modify to suspend faiwed\n");

	if (quewy_viwtqueue(ndev, mvq, &attw)) {
		mwx5_vdpa_wawn(&ndev->mvdev, "faiwed to quewy viwtqueue\n");
		wetuwn;
	}
	mvq->avaiw_idx = attw.avaiwabwe_index;
	mvq->used_idx = attw.used_index;
}

static void suspend_vqs(stwuct mwx5_vdpa_net *ndev)
{
	int i;

	fow (i = 0; i < ndev->mvdev.max_vqs; i++)
		suspend_vq(ndev, &ndev->vqs[i]);
}

static void wesume_vq(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	if (!mvq->initiawized || !is_wesumabwe(ndev))
		wetuwn;

	if (mvq->fw_state != MWX5_VIWTIO_NET_Q_OBJECT_STATE_SUSPEND)
		wetuwn;

	if (modify_viwtqueue_state(ndev, mvq, MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY))
		mwx5_vdpa_wawn(&ndev->mvdev, "modify to wesume faiwed fow vq %u\n", mvq->index);
}

static void wesume_vqs(stwuct mwx5_vdpa_net *ndev)
{
	fow (int i = 0; i < ndev->mvdev.max_vqs; i++)
		wesume_vq(ndev, &ndev->vqs[i]);
}

static void teawdown_vq(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	if (!mvq->initiawized)
		wetuwn;

	suspend_vq(ndev, mvq);
	mvq->modified_fiewds = 0;
	destwoy_viwtqueue(ndev, mvq);
	deawwoc_vectow(ndev, mvq);
	countew_set_deawwoc(ndev, mvq);
	qp_destwoy(ndev, &mvq->vqqp);
	qp_destwoy(ndev, &mvq->fwqp);
	cq_destwoy(ndev, mvq->index);
	mvq->initiawized = fawse;
}

static int cweate_wqt(stwuct mwx5_vdpa_net *ndev)
{
	int wqt_tabwe_size = woundup_pow_of_two(ndev->wqt_size);
	int act_sz = woundup_pow_of_two(ndev->cuw_num_vqs / 2);
	__be32 *wist;
	void *wqtc;
	int inwen;
	void *in;
	int i, j;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(cweate_wqt_in) + wqt_tabwe_size * MWX5_ST_SZ_BYTES(wq_num);
	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_wqt_in, in, uid, ndev->mvdev.wes.uid);
	wqtc = MWX5_ADDW_OF(cweate_wqt_in, in, wqt_context);

	MWX5_SET(wqtc, wqtc, wist_q_type, MWX5_WQTC_WIST_Q_TYPE_VIWTIO_NET_Q);
	MWX5_SET(wqtc, wqtc, wqt_max_size, wqt_tabwe_size);
	wist = MWX5_ADDW_OF(wqtc, wqtc, wq_num[0]);
	fow (i = 0, j = 0; i < act_sz; i++, j += 2)
		wist[i] = cpu_to_be32(ndev->vqs[j % ndev->cuw_num_vqs].viwtq_id);

	MWX5_SET(wqtc, wqtc, wqt_actuaw_size, act_sz);
	eww = mwx5_vdpa_cweate_wqt(&ndev->mvdev, in, inwen, &ndev->wes.wqtn);
	kfwee(in);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

#define MWX5_MODIFY_WQT_NUM_WQS ((u64)1)

static int modify_wqt(stwuct mwx5_vdpa_net *ndev, int num)
{
	int act_sz = woundup_pow_of_two(num / 2);
	__be32 *wist;
	void *wqtc;
	int inwen;
	void *in;
	int i, j;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(modify_wqt_in) + act_sz * MWX5_ST_SZ_BYTES(wq_num);
	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_wqt_in, in, uid, ndev->mvdev.wes.uid);
	MWX5_SET64(modify_wqt_in, in, bitmask, MWX5_MODIFY_WQT_NUM_WQS);
	wqtc = MWX5_ADDW_OF(modify_wqt_in, in, ctx);
	MWX5_SET(wqtc, wqtc, wist_q_type, MWX5_WQTC_WIST_Q_TYPE_VIWTIO_NET_Q);

	wist = MWX5_ADDW_OF(wqtc, wqtc, wq_num[0]);
	fow (i = 0, j = 0; i < act_sz; i++, j = j + 2)
		wist[i] = cpu_to_be32(ndev->vqs[j % num].viwtq_id);

	MWX5_SET(wqtc, wqtc, wqt_actuaw_size, act_sz);
	eww = mwx5_vdpa_modify_wqt(&ndev->mvdev, in, inwen, ndev->wes.wqtn);
	kfwee(in);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void destwoy_wqt(stwuct mwx5_vdpa_net *ndev)
{
	mwx5_vdpa_destwoy_wqt(&ndev->mvdev, ndev->wes.wqtn);
}

static int cweate_tiw(stwuct mwx5_vdpa_net *ndev)
{
#define HASH_IP_W4POWTS                                                                            \
	(MWX5_HASH_FIEWD_SEW_SWC_IP | MWX5_HASH_FIEWD_SEW_DST_IP | MWX5_HASH_FIEWD_SEW_W4_SPOWT |  \
	 MWX5_HASH_FIEWD_SEW_W4_DPOWT)
	static const u8 wx_hash_toepwitz_key[] = { 0x2c, 0xc6, 0x81, 0xd1, 0x5b, 0xdb, 0xf4, 0xf7,
						   0xfc, 0xa2, 0x83, 0x19, 0xdb, 0x1a, 0x3e, 0x94,
						   0x6b, 0x9e, 0x38, 0xd9, 0x2c, 0x9c, 0x03, 0xd1,
						   0xad, 0x99, 0x44, 0xa7, 0xd9, 0x56, 0x3d, 0x59,
						   0x06, 0x3c, 0x25, 0xf3, 0xfc, 0x1f, 0xdc, 0x2a };
	void *wss_key;
	void *outew;
	void *tiwc;
	void *in;
	int eww;

	in = kzawwoc(MWX5_ST_SZ_BYTES(cweate_tiw_in), GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_tiw_in, in, uid, ndev->mvdev.wes.uid);
	tiwc = MWX5_ADDW_OF(cweate_tiw_in, in, ctx);
	MWX5_SET(tiwc, tiwc, disp_type, MWX5_TIWC_DISP_TYPE_INDIWECT);

	MWX5_SET(tiwc, tiwc, wx_hash_symmetwic, 1);
	MWX5_SET(tiwc, tiwc, wx_hash_fn, MWX5_WX_HASH_FN_TOEPWITZ);
	wss_key = MWX5_ADDW_OF(tiwc, tiwc, wx_hash_toepwitz_key);
	memcpy(wss_key, wx_hash_toepwitz_key, sizeof(wx_hash_toepwitz_key));

	outew = MWX5_ADDW_OF(tiwc, tiwc, wx_hash_fiewd_sewectow_outew);
	MWX5_SET(wx_hash_fiewd_sewect, outew, w3_pwot_type, MWX5_W3_PWOT_TYPE_IPV4);
	MWX5_SET(wx_hash_fiewd_sewect, outew, w4_pwot_type, MWX5_W4_PWOT_TYPE_TCP);
	MWX5_SET(wx_hash_fiewd_sewect, outew, sewected_fiewds, HASH_IP_W4POWTS);

	MWX5_SET(tiwc, tiwc, indiwect_tabwe, ndev->wes.wqtn);
	MWX5_SET(tiwc, tiwc, twanspowt_domain, ndev->wes.tdn);

	eww = mwx5_vdpa_cweate_tiw(&ndev->mvdev, in, &ndev->wes.tiwn);
	kfwee(in);
	if (eww)
		wetuwn eww;

	mwx5_vdpa_add_tiwn(ndev);
	wetuwn eww;
}

static void destwoy_tiw(stwuct mwx5_vdpa_net *ndev)
{
	mwx5_vdpa_wemove_tiwn(ndev);
	mwx5_vdpa_destwoy_tiw(&ndev->mvdev, ndev->wes.tiwn);
}

#define MAX_STEEWING_ENT 0x8000
#define MAX_STEEWING_GWOUPS 2

#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
       #define NUM_DESTS 2
#ewse
       #define NUM_DESTS 1
#endif

static int add_steewing_countews(stwuct mwx5_vdpa_net *ndev,
				 stwuct macvwan_node *node,
				 stwuct mwx5_fwow_act *fwow_act,
				 stwuct mwx5_fwow_destination *dests)
{
#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
	int eww;

	node->ucast_countew.countew = mwx5_fc_cweate(ndev->mvdev.mdev, fawse);
	if (IS_EWW(node->ucast_countew.countew))
		wetuwn PTW_EWW(node->ucast_countew.countew);

	node->mcast_countew.countew = mwx5_fc_cweate(ndev->mvdev.mdev, fawse);
	if (IS_EWW(node->mcast_countew.countew)) {
		eww = PTW_EWW(node->mcast_countew.countew);
		goto eww_mcast_countew;
	}

	dests[1].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
	wetuwn 0;

eww_mcast_countew:
	mwx5_fc_destwoy(ndev->mvdev.mdev, node->ucast_countew.countew);
	wetuwn eww;
#ewse
	wetuwn 0;
#endif
}

static void wemove_steewing_countews(stwuct mwx5_vdpa_net *ndev,
				     stwuct macvwan_node *node)
{
#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
	mwx5_fc_destwoy(ndev->mvdev.mdev, node->mcast_countew.countew);
	mwx5_fc_destwoy(ndev->mvdev.mdev, node->ucast_countew.countew);
#endif
}

static int mwx5_vdpa_add_mac_vwan_wuwes(stwuct mwx5_vdpa_net *ndev, u8 *mac,
					stwuct macvwan_node *node)
{
	stwuct mwx5_fwow_destination dests[NUM_DESTS] = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec;
	void *headews_c;
	void *headews_v;
	u8 *dmac_c;
	u8 *dmac_v;
	int eww;
	u16 vid;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	vid = key2vid(node->macvwan);
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, outew_headews);
	headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, outew_headews);
	dmac_c = MWX5_ADDW_OF(fte_match_pawam, headews_c, outew_headews.dmac_47_16);
	dmac_v = MWX5_ADDW_OF(fte_match_pawam, headews_v, outew_headews.dmac_47_16);
	eth_bwoadcast_addw(dmac_c);
	ethew_addw_copy(dmac_v, mac);
	if (ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VWAN)) {
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, cvwan_tag, 1);
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, fiwst_vid);
	}
	if (node->tagged) {
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, cvwan_tag, 1);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, fiwst_vid, vid);
	}
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dests[0].type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dests[0].tiw_num = ndev->wes.tiwn;
	eww = add_steewing_countews(ndev, node, &fwow_act, dests);
	if (eww)
		goto out_fwee;

#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
	dests[1].countew_id = mwx5_fc_id(node->ucast_countew.countew);
#endif
	node->ucast_wuwe = mwx5_add_fwow_wuwes(ndev->wxft, spec, &fwow_act, dests, NUM_DESTS);
	if (IS_EWW(node->ucast_wuwe)) {
		eww = PTW_EWW(node->ucast_wuwe);
		goto eww_ucast;
	}

#if defined(CONFIG_MWX5_VDPA_STEEWING_DEBUG)
	dests[1].countew_id = mwx5_fc_id(node->mcast_countew.countew);
#endif

	memset(dmac_c, 0, ETH_AWEN);
	memset(dmac_v, 0, ETH_AWEN);
	dmac_c[0] = 1;
	dmac_v[0] = 1;
	node->mcast_wuwe = mwx5_add_fwow_wuwes(ndev->wxft, spec, &fwow_act, dests, NUM_DESTS);
	if (IS_EWW(node->mcast_wuwe)) {
		eww = PTW_EWW(node->mcast_wuwe);
		goto eww_mcast;
	}
	kvfwee(spec);
	mwx5_vdpa_add_wx_countews(ndev, node);
	wetuwn 0;

eww_mcast:
	mwx5_dew_fwow_wuwes(node->ucast_wuwe);
eww_ucast:
	wemove_steewing_countews(ndev, node);
out_fwee:
	kvfwee(spec);
	wetuwn eww;
}

static void mwx5_vdpa_dew_mac_vwan_wuwes(stwuct mwx5_vdpa_net *ndev,
					 stwuct macvwan_node *node)
{
	mwx5_vdpa_wemove_wx_countews(ndev, node);
	mwx5_dew_fwow_wuwes(node->ucast_wuwe);
	mwx5_dew_fwow_wuwes(node->mcast_wuwe);
}

static u64 seawch_vaw(u8 *mac, u16 vwan, boow tagged)
{
	u64 vaw;

	if (!tagged)
		vwan = MWX5V_UNTAGGED;

	vaw = (u64)vwan << 48 |
	      (u64)mac[0] << 40 |
	      (u64)mac[1] << 32 |
	      (u64)mac[2] << 24 |
	      (u64)mac[3] << 16 |
	      (u64)mac[4] << 8 |
	      (u64)mac[5];

	wetuwn vaw;
}

static stwuct macvwan_node *mac_vwan_wookup(stwuct mwx5_vdpa_net *ndev, u64 vawue)
{
	stwuct macvwan_node *pos;
	u32 idx;

	idx = hash_64(vawue, 8); // tbd 8
	hwist_fow_each_entwy(pos, &ndev->macvwan_hash[idx], hwist) {
		if (pos->macvwan == vawue)
			wetuwn pos;
	}
	wetuwn NUWW;
}

static int mac_vwan_add(stwuct mwx5_vdpa_net *ndev, u8 *mac, u16 vid, boow tagged)
{
	stwuct macvwan_node *ptw;
	u64 vaw;
	u32 idx;
	int eww;

	vaw = seawch_vaw(mac, vid, tagged);
	if (mac_vwan_wookup(ndev, vaw))
		wetuwn -EEXIST;

	ptw = kzawwoc(sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	ptw->tagged = tagged;
	ptw->macvwan = vaw;
	ptw->ndev = ndev;
	eww = mwx5_vdpa_add_mac_vwan_wuwes(ndev, ndev->config.mac, ptw);
	if (eww)
		goto eww_add;

	idx = hash_64(vaw, 8);
	hwist_add_head(&ptw->hwist, &ndev->macvwan_hash[idx]);
	wetuwn 0;

eww_add:
	kfwee(ptw);
	wetuwn eww;
}

static void mac_vwan_dew(stwuct mwx5_vdpa_net *ndev, u8 *mac, u16 vwan, boow tagged)
{
	stwuct macvwan_node *ptw;

	ptw = mac_vwan_wookup(ndev, seawch_vaw(mac, vwan, tagged));
	if (!ptw)
		wetuwn;

	hwist_dew(&ptw->hwist);
	mwx5_vdpa_dew_mac_vwan_wuwes(ndev, ptw);
	wemove_steewing_countews(ndev, ptw);
	kfwee(ptw);
}

static void cweaw_mac_vwan_tabwe(stwuct mwx5_vdpa_net *ndev)
{
	stwuct macvwan_node *pos;
	stwuct hwist_node *n;
	int i;

	fow (i = 0; i < MWX5V_MACVWAN_SIZE; i++) {
		hwist_fow_each_entwy_safe(pos, n, &ndev->macvwan_hash[i], hwist) {
			hwist_dew(&pos->hwist);
			mwx5_vdpa_dew_mac_vwan_wuwes(ndev, pos);
			wemove_steewing_countews(ndev, pos);
			kfwee(pos);
		}
	}
}

static int setup_steewing(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns;
	int eww;

	ft_attw.max_fte = MAX_STEEWING_ENT;
	ft_attw.autogwoup.max_num_gwoups = MAX_STEEWING_GWOUPS;

	ns = mwx5_get_fwow_namespace(ndev->mvdev.mdev, MWX5_FWOW_NAMESPACE_BYPASS);
	if (!ns) {
		mwx5_vdpa_wawn(&ndev->mvdev, "faiwed to get fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	ndev->wxft = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ndev->wxft)) {
		mwx5_vdpa_wawn(&ndev->mvdev, "faiwed to cweate fwow tabwe\n");
		wetuwn PTW_EWW(ndev->wxft);
	}
	mwx5_vdpa_add_wx_fwow_tabwe(ndev);

	eww = mac_vwan_add(ndev, ndev->config.mac, 0, fawse);
	if (eww)
		goto eww_add;

	wetuwn 0;

eww_add:
	mwx5_vdpa_wemove_wx_fwow_tabwe(ndev);
	mwx5_destwoy_fwow_tabwe(ndev->wxft);
	wetuwn eww;
}

static void teawdown_steewing(stwuct mwx5_vdpa_net *ndev)
{
	cweaw_mac_vwan_tabwe(ndev);
	mwx5_vdpa_wemove_wx_fwow_tabwe(ndev);
	mwx5_destwoy_fwow_tabwe(ndev->wxft);
}

static viwtio_net_ctww_ack handwe_ctww_mac(stwuct mwx5_vdpa_dev *mvdev, u8 cmd)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_contwow_vq *cvq = &mvdev->cvq;
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	stwuct mwx5_cowe_dev *pfmdev;
	size_t wead;
	u8 mac[ETH_AWEN], mac_back[ETH_AWEN];

	pfmdev = pci_get_dwvdata(pci_physfn(mvdev->mdev->pdev));
	switch (cmd) {
	case VIWTIO_NET_CTWW_MAC_ADDW_SET:
		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->wiov, (void *)mac, ETH_AWEN);
		if (wead != ETH_AWEN)
			bweak;

		if (!memcmp(ndev->config.mac, mac, 6)) {
			status = VIWTIO_NET_OK;
			bweak;
		}

		if (is_zewo_ethew_addw(mac))
			bweak;

		if (!is_zewo_ethew_addw(ndev->config.mac)) {
			if (mwx5_mpfs_dew_mac(pfmdev, ndev->config.mac)) {
				mwx5_vdpa_wawn(mvdev, "faiwed to dewete owd MAC %pM fwom MPFS tabwe\n",
					       ndev->config.mac);
				bweak;
			}
		}

		if (mwx5_mpfs_add_mac(pfmdev, mac)) {
			mwx5_vdpa_wawn(mvdev, "faiwed to insewt new MAC %pM into MPFS tabwe\n",
				       mac);
			bweak;
		}

		/* backup the owiginaw mac addwess so that if faiwed to add the fowwawd wuwes
		 * we couwd westowe it
		 */
		memcpy(mac_back, ndev->config.mac, ETH_AWEN);

		memcpy(ndev->config.mac, mac, ETH_AWEN);

		/* Need wecweate the fwow tabwe entwy, so that the packet couwd fowwawd back
		 */
		mac_vwan_dew(ndev, mac_back, 0, fawse);

		if (mac_vwan_add(ndev, ndev->config.mac, 0, fawse)) {
			mwx5_vdpa_wawn(mvdev, "faiwed to insewt fowwawd wuwes, twy to westowe\n");

			/* Awthough it hawdwy wun hewe, we stiww need doubwe check */
			if (is_zewo_ethew_addw(mac_back)) {
				mwx5_vdpa_wawn(mvdev, "westowe mac faiwed: Owiginaw MAC is zewo\n");
				bweak;
			}

			/* Twy to westowe owiginaw mac addwess to MFPS tabwe, and twy to westowe
			 * the fowwawd wuwe entwy.
			 */
			if (mwx5_mpfs_dew_mac(pfmdev, ndev->config.mac)) {
				mwx5_vdpa_wawn(mvdev, "westowe mac faiwed: dewete MAC %pM fwom MPFS tabwe faiwed\n",
					       ndev->config.mac);
			}

			if (mwx5_mpfs_add_mac(pfmdev, mac_back)) {
				mwx5_vdpa_wawn(mvdev, "westowe mac faiwed: insewt owd MAC %pM into MPFS tabwe faiwed\n",
					       mac_back);
			}

			memcpy(ndev->config.mac, mac_back, ETH_AWEN);

			if (mac_vwan_add(ndev, ndev->config.mac, 0, fawse))
				mwx5_vdpa_wawn(mvdev, "westowe fowwawd wuwes faiwed: insewt fowwawd wuwes faiwed\n");

			bweak;
		}

		status = VIWTIO_NET_OK;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn status;
}

static int change_num_qps(stwuct mwx5_vdpa_dev *mvdev, int newqps)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int cuw_qps = ndev->cuw_num_vqs / 2;
	int eww;
	int i;

	if (cuw_qps > newqps) {
		eww = modify_wqt(ndev, 2 * newqps);
		if (eww)
			wetuwn eww;

		fow (i = ndev->cuw_num_vqs - 1; i >= 2 * newqps; i--)
			teawdown_vq(ndev, &ndev->vqs[i]);

		ndev->cuw_num_vqs = 2 * newqps;
	} ewse {
		ndev->cuw_num_vqs = 2 * newqps;
		fow (i = cuw_qps * 2; i < 2 * newqps; i++) {
			eww = setup_vq(ndev, &ndev->vqs[i]);
			if (eww)
				goto cwean_added;
		}
		eww = modify_wqt(ndev, 2 * newqps);
		if (eww)
			goto cwean_added;
	}
	wetuwn 0;

cwean_added:
	fow (--i; i >= 2 * cuw_qps; --i)
		teawdown_vq(ndev, &ndev->vqs[i]);

	ndev->cuw_num_vqs = 2 * cuw_qps;

	wetuwn eww;
}

static viwtio_net_ctww_ack handwe_ctww_mq(stwuct mwx5_vdpa_dev *mvdev, u8 cmd)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	stwuct mwx5_contwow_vq *cvq = &mvdev->cvq;
	stwuct viwtio_net_ctww_mq mq;
	size_t wead;
	u16 newqps;

	switch (cmd) {
	case VIWTIO_NET_CTWW_MQ_VQ_PAIWS_SET:
		/* This mq featuwe check awigns with pwe-existing usewspace
		 * impwementation.
		 *
		 * Without it, an untwusted dwivew couwd fake a muwtiqueue config
		 * wequest down to a non-mq device that may cause kewnew to
		 * panic due to uninitiawized wesouwces fow extwa vqs. Even with
		 * a weww behaving guest dwivew, it is not expected to awwow
		 * changing the numbew of vqs on a non-mq device.
		 */
		if (!MWX5_FEATUWE(mvdev, VIWTIO_NET_F_MQ))
			bweak;

		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->wiov, (void *)&mq, sizeof(mq));
		if (wead != sizeof(mq))
			bweak;

		newqps = mwx5vdpa16_to_cpu(mvdev, mq.viwtqueue_paiws);
		if (newqps < VIWTIO_NET_CTWW_MQ_VQ_PAIWS_MIN ||
		    newqps > ndev->wqt_size)
			bweak;

		if (ndev->cuw_num_vqs == 2 * newqps) {
			status = VIWTIO_NET_OK;
			bweak;
		}

		if (!change_num_qps(mvdev, newqps))
			status = VIWTIO_NET_OK;

		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

static viwtio_net_ctww_ack handwe_ctww_vwan(stwuct mwx5_vdpa_dev *mvdev, u8 cmd)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	stwuct mwx5_contwow_vq *cvq = &mvdev->cvq;
	__viwtio16 vwan;
	size_t wead;
	u16 id;

	if (!(ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VWAN)))
		wetuwn status;

	switch (cmd) {
	case VIWTIO_NET_CTWW_VWAN_ADD:
		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->wiov, &vwan, sizeof(vwan));
		if (wead != sizeof(vwan))
			bweak;

		id = mwx5vdpa16_to_cpu(mvdev, vwan);
		if (mac_vwan_add(ndev, ndev->config.mac, id, twue))
			bweak;

		status = VIWTIO_NET_OK;
		bweak;
	case VIWTIO_NET_CTWW_VWAN_DEW:
		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->wiov, &vwan, sizeof(vwan));
		if (wead != sizeof(vwan))
			bweak;

		id = mwx5vdpa16_to_cpu(mvdev, vwan);
		mac_vwan_dew(ndev, ndev->config.mac, id, twue);
		status = VIWTIO_NET_OK;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

static void mwx5_cvq_kick_handwew(stwuct wowk_stwuct *wowk)
{
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	stwuct viwtio_net_ctww_hdw ctww;
	stwuct mwx5_vdpa_wq_ent *wqent;
	stwuct mwx5_vdpa_dev *mvdev;
	stwuct mwx5_contwow_vq *cvq;
	stwuct mwx5_vdpa_net *ndev;
	size_t wead, wwite;
	int eww;

	wqent = containew_of(wowk, stwuct mwx5_vdpa_wq_ent, wowk);
	mvdev = wqent->mvdev;
	ndev = to_mwx5_vdpa_ndev(mvdev);
	cvq = &mvdev->cvq;

	down_wwite(&ndev->weswock);

	if (!(mvdev->status & VIWTIO_CONFIG_S_DWIVEW_OK))
		goto out;

	if (!(ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ)))
		goto out;

	if (!cvq->weady)
		goto out;

	whiwe (twue) {
		eww = vwingh_getdesc_iotwb(&cvq->vwing, &cvq->wiov, &cvq->wiov, &cvq->head,
					   GFP_ATOMIC);
		if (eww <= 0)
			bweak;

		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->wiov, &ctww, sizeof(ctww));
		if (wead != sizeof(ctww))
			bweak;

		cvq->weceived_desc++;
		switch (ctww.cwass) {
		case VIWTIO_NET_CTWW_MAC:
			status = handwe_ctww_mac(mvdev, ctww.cmd);
			bweak;
		case VIWTIO_NET_CTWW_MQ:
			status = handwe_ctww_mq(mvdev, ctww.cmd);
			bweak;
		case VIWTIO_NET_CTWW_VWAN:
			status = handwe_ctww_vwan(mvdev, ctww.cmd);
			bweak;
		defauwt:
			bweak;
		}

		/* Make suwe data is wwitten befowe advancing index */
		smp_wmb();

		wwite = vwingh_iov_push_iotwb(&cvq->vwing, &cvq->wiov, &status, sizeof(status));
		vwingh_compwete_iotwb(&cvq->vwing, cvq->head, wwite);
		vwingh_kiov_cweanup(&cvq->wiov);
		vwingh_kiov_cweanup(&cvq->wiov);

		if (vwingh_need_notify_iotwb(&cvq->vwing))
			vwingh_notify(&cvq->vwing);

		cvq->compweted_desc++;
		queue_wowk(mvdev->wq, &wqent->wowk);
		bweak;
	}

out:
	up_wwite(&ndev->weswock);
}

static void mwx5_vdpa_kick_vq(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;

	if (!is_index_vawid(mvdev, idx))
		wetuwn;

	if (unwikewy(is_ctww_vq_idx(mvdev, idx))) {
		if (!mvdev->wq || !mvdev->cvq.weady)
			wetuwn;

		queue_wowk(mvdev->wq, &ndev->cvq_ent.wowk);
		wetuwn;
	}

	mvq = &ndev->vqs[idx];
	if (unwikewy(!mvq->weady))
		wetuwn;

	iowwite16(idx, ndev->mvdev.wes.kick_addw);
}

static int mwx5_vdpa_set_vq_addwess(stwuct vdpa_device *vdev, u16 idx, u64 desc_awea,
				    u64 dwivew_awea, u64 device_awea)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;

	if (!is_index_vawid(mvdev, idx))
		wetuwn -EINVAW;

	if (is_ctww_vq_idx(mvdev, idx)) {
		mvdev->cvq.desc_addw = desc_awea;
		mvdev->cvq.device_addw = device_awea;
		mvdev->cvq.dwivew_addw = dwivew_awea;
		wetuwn 0;
	}

	mvq = &ndev->vqs[idx];
	mvq->desc_addw = desc_awea;
	mvq->device_addw = device_awea;
	mvq->dwivew_addw = dwivew_awea;
	mvq->modified_fiewds |= MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_ADDWS;
	wetuwn 0;
}

static void mwx5_vdpa_set_vq_num(stwuct vdpa_device *vdev, u16 idx, u32 num)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;

	if (!is_index_vawid(mvdev, idx) || is_ctww_vq_idx(mvdev, idx))
		wetuwn;

	mvq = &ndev->vqs[idx];
	mvq->num_ent = num;
}

static void mwx5_vdpa_set_vq_cb(stwuct vdpa_device *vdev, u16 idx, stwuct vdpa_cawwback *cb)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	ndev->event_cbs[idx] = *cb;
	if (is_ctww_vq_idx(mvdev, idx))
		mvdev->cvq.event_cb = *cb;
}

static void mwx5_cvq_notify(stwuct vwingh *vwing)
{
	stwuct mwx5_contwow_vq *cvq = containew_of(vwing, stwuct mwx5_contwow_vq, vwing);

	if (!cvq->event_cb.cawwback)
		wetuwn;

	cvq->event_cb.cawwback(cvq->event_cb.pwivate);
}

static void set_cvq_weady(stwuct mwx5_vdpa_dev *mvdev, boow weady)
{
	stwuct mwx5_contwow_vq *cvq = &mvdev->cvq;

	cvq->weady = weady;
	if (!weady)
		wetuwn;

	cvq->vwing.notify = mwx5_cvq_notify;
}

static void mwx5_vdpa_set_vq_weady(stwuct vdpa_device *vdev, u16 idx, boow weady)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;
	int eww;

	if (!mvdev->actuaw_featuwes)
		wetuwn;

	if (!is_index_vawid(mvdev, idx))
		wetuwn;

	if (is_ctww_vq_idx(mvdev, idx)) {
		set_cvq_weady(mvdev, weady);
		wetuwn;
	}

	mvq = &ndev->vqs[idx];
	if (!weady) {
		suspend_vq(ndev, mvq);
	} ewse {
		eww = modify_viwtqueue_state(ndev, mvq, MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY);
		if (eww) {
			mwx5_vdpa_wawn(mvdev, "modify VQ %d to weady faiwed (%d)\n", idx, eww);
			weady = fawse;
		}
	}


	mvq->weady = weady;
}

static boow mwx5_vdpa_get_vq_weady(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	if (!is_index_vawid(mvdev, idx))
		wetuwn fawse;

	if (is_ctww_vq_idx(mvdev, idx))
		wetuwn mvdev->cvq.weady;

	wetuwn ndev->vqs[idx].weady;
}

static int mwx5_vdpa_set_vq_state(stwuct vdpa_device *vdev, u16 idx,
				  const stwuct vdpa_vq_state *state)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;

	if (!is_index_vawid(mvdev, idx))
		wetuwn -EINVAW;

	if (is_ctww_vq_idx(mvdev, idx)) {
		mvdev->cvq.vwing.wast_avaiw_idx = state->spwit.avaiw_index;
		wetuwn 0;
	}

	mvq = &ndev->vqs[idx];
	if (mvq->fw_state == MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY) {
		mwx5_vdpa_wawn(mvdev, "can't modify avaiwabwe index\n");
		wetuwn -EINVAW;
	}

	mvq->used_idx = state->spwit.avaiw_index;
	mvq->avaiw_idx = state->spwit.avaiw_index;
	mvq->modified_fiewds |= MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_AVAIW_IDX |
				MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_USED_IDX;
	wetuwn 0;
}

static int mwx5_vdpa_get_vq_state(stwuct vdpa_device *vdev, u16 idx, stwuct vdpa_vq_state *state)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;
	stwuct mwx5_viwtq_attw attw;
	int eww;

	if (!is_index_vawid(mvdev, idx))
		wetuwn -EINVAW;

	if (is_ctww_vq_idx(mvdev, idx)) {
		state->spwit.avaiw_index = mvdev->cvq.vwing.wast_avaiw_idx;
		wetuwn 0;
	}

	mvq = &ndev->vqs[idx];
	/* If the viwtq object was destwoyed, use the vawue saved at
	 * the wast minute of suspend_vq. This catews fow usewspace
	 * that cawes about emuwating the index aftew vq is stopped.
	 */
	if (!mvq->initiawized) {
		/* Fiwmwawe wetuwns a wwong vawue fow the avaiwabwe index.
		 * Since both vawues shouwd be identicaw, we take the vawue of
		 * used_idx which is wepowted cowwectwy.
		 */
		state->spwit.avaiw_index = mvq->used_idx;
		wetuwn 0;
	}

	eww = quewy_viwtqueue(ndev, mvq, &attw);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "faiwed to quewy viwtqueue\n");
		wetuwn eww;
	}
	state->spwit.avaiw_index = attw.used_index;
	wetuwn 0;
}

static u32 mwx5_vdpa_get_vq_awign(stwuct vdpa_device *vdev)
{
	wetuwn PAGE_SIZE;
}

static u32 mwx5_vdpa_get_vq_gwoup(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);

	if (is_ctww_vq_idx(mvdev, idx))
		wetuwn MWX5_VDPA_CVQ_GWOUP;

	wetuwn MWX5_VDPA_DATAVQ_GWOUP;
}

static u32 mwx5_vdpa_get_vq_desc_gwoup(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);

	if (is_ctww_vq_idx(mvdev, idx))
		wetuwn MWX5_VDPA_CVQ_GWOUP;

	wetuwn MWX5_VDPA_DATAVQ_DESC_GWOUP;
}

static u64 mwx_to_vwitio_featuwes(u16 dev_featuwes)
{
	u64 wesuwt = 0;

	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_MWG_WXBUF))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_MWG_WXBUF);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_HOST_ECN))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_HOST_ECN);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_GUEST_ECN))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_GUEST_ECN);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_GUEST_TSO6))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_GUEST_TSO6);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_GUEST_TSO4))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_GUEST_TSO4);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_GUEST_CSUM))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_GUEST_CSUM);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_CSUM))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_CSUM);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_HOST_TSO6))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_HOST_TSO6);
	if (dev_featuwes & BIT_UWW(MWX5_VIWTIO_NET_F_HOST_TSO4))
		wesuwt |= BIT_UWW(VIWTIO_NET_F_HOST_TSO4);

	wetuwn wesuwt;
}

static u64 get_suppowted_featuwes(stwuct mwx5_cowe_dev *mdev)
{
	u64 mwx_vdpa_featuwes = 0;
	u16 dev_featuwes;

	dev_featuwes = MWX5_CAP_DEV_VDPA_EMUWATION(mdev, device_featuwes_bits_mask);
	mwx_vdpa_featuwes |= mwx_to_vwitio_featuwes(dev_featuwes);
	if (MWX5_CAP_DEV_VDPA_EMUWATION(mdev, viwtio_vewsion_1_0))
		mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_F_VEWSION_1);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_CTWW_VQ);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_CTWW_MAC_ADDW);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_MQ);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_STATUS);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_MTU);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_CTWW_VWAN);
	mwx_vdpa_featuwes |= BIT_UWW(VIWTIO_NET_F_MAC);

	wetuwn mwx_vdpa_featuwes;
}

static u64 mwx5_vdpa_get_device_featuwes(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	pwint_featuwes(mvdev, ndev->mvdev.mwx_featuwes, fawse);
	wetuwn ndev->mvdev.mwx_featuwes;
}

static int vewify_dwivew_featuwes(stwuct mwx5_vdpa_dev *mvdev, u64 featuwes)
{
	/* Minimum featuwes to expect */
	if (!(featuwes & BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM)))
		wetuwn -EOPNOTSUPP;

	/* Doubwe check featuwes combination sent down by the dwivew.
	 * Faiw invawid featuwes due to absence of the depended featuwe.
	 *
	 * Pew VIWTIO v1.1 specification, section 5.1.3.1 Featuwe bit
	 * wequiwements: "VIWTIO_NET_F_MQ Wequiwes VIWTIO_NET_F_CTWW_VQ".
	 * By faiwing the invawid featuwes sent down by untwusted dwivews,
	 * we'we assuwed the assumption made upon is_index_vawid() and
	 * is_ctww_vq_idx() wiww not be compwomised.
	 */
	if ((featuwes & (BIT_UWW(VIWTIO_NET_F_MQ) | BIT_UWW(VIWTIO_NET_F_CTWW_VQ))) ==
            BIT_UWW(VIWTIO_NET_F_MQ))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int setup_viwtqueues(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww;
	int i;

	fow (i = 0; i < mvdev->max_vqs; i++) {
		eww = setup_vq(ndev, &ndev->vqs[i]);
		if (eww)
			goto eww_vq;
	}

	wetuwn 0;

eww_vq:
	fow (--i; i >= 0; i--)
		teawdown_vq(ndev, &ndev->vqs[i]);

	wetuwn eww;
}

static void teawdown_viwtqueues(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_viwtqueue *mvq;
	int i;

	fow (i = ndev->mvdev.max_vqs - 1; i >= 0; i--) {
		mvq = &ndev->vqs[i];
		if (!mvq->initiawized)
			continue;

		teawdown_vq(ndev, mvq);
	}
}

static void update_cvq_info(stwuct mwx5_vdpa_dev *mvdev)
{
	if (MWX5_FEATUWE(mvdev, VIWTIO_NET_F_CTWW_VQ)) {
		if (MWX5_FEATUWE(mvdev, VIWTIO_NET_F_MQ)) {
			/* MQ suppowted. CVQ index is wight above the wast data viwtqueue's */
			mvdev->max_idx = mvdev->max_vqs;
		} ewse {
			/* Onwy CVQ suppowtted. data viwtqueues occupy indices 0 and 1.
			 * CVQ gets index 2
			 */
			mvdev->max_idx = 2;
		}
	} ewse {
		/* Two data viwtqueues onwy: one fow wx and one fow tx */
		mvdev->max_idx = 1;
	}
}

static u8 quewy_vpowt_state(stwuct mwx5_cowe_dev *mdev, u8 opmod, u16 vpowt)
{
	u32 out[MWX5_ST_SZ_DW(quewy_vpowt_state_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_vpowt_state_in)] = {};
	int eww;

	MWX5_SET(quewy_vpowt_state_in, in, opcode, MWX5_CMD_OP_QUEWY_VPOWT_STATE);
	MWX5_SET(quewy_vpowt_state_in, in, op_mod, opmod);
	MWX5_SET(quewy_vpowt_state_in, in, vpowt_numbew, vpowt);
	if (vpowt)
		MWX5_SET(quewy_vpowt_state_in, in, othew_vpowt, 1);

	eww = mwx5_cmd_exec_inout(mdev, quewy_vpowt_state, in, out);
	if (eww)
		wetuwn 0;

	wetuwn MWX5_GET(quewy_vpowt_state_out, out, state);
}

static boow get_wink_state(stwuct mwx5_vdpa_dev *mvdev)
{
	if (quewy_vpowt_state(mvdev->mdev, MWX5_VPOWT_STATE_OP_MOD_VNIC_VPOWT, 0) ==
	    VPOWT_STATE_UP)
		wetuwn twue;

	wetuwn fawse;
}

static void update_cawwiew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_vdpa_wq_ent *wqent;
	stwuct mwx5_vdpa_dev *mvdev;
	stwuct mwx5_vdpa_net *ndev;

	wqent = containew_of(wowk, stwuct mwx5_vdpa_wq_ent, wowk);
	mvdev = wqent->mvdev;
	ndev = to_mwx5_vdpa_ndev(mvdev);
	if (get_wink_state(mvdev))
		ndev->config.status |= cpu_to_mwx5vdpa16(mvdev, VIWTIO_NET_S_WINK_UP);
	ewse
		ndev->config.status &= cpu_to_mwx5vdpa16(mvdev, ~VIWTIO_NET_S_WINK_UP);

	if (ndev->config_cb.cawwback)
		ndev->config_cb.cawwback(ndev->config_cb.pwivate);

	kfwee(wqent);
}

static int queue_wink_wowk(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_wq_ent *wqent;

	wqent = kzawwoc(sizeof(*wqent), GFP_ATOMIC);
	if (!wqent)
		wetuwn -ENOMEM;

	wqent->mvdev = &ndev->mvdev;
	INIT_WOWK(&wqent->wowk, update_cawwiew);
	queue_wowk(ndev->mvdev.wq, &wqent->wowk);
	wetuwn 0;
}

static int event_handwew(stwuct notifiew_bwock *nb, unsigned wong event, void *pawam)
{
	stwuct mwx5_vdpa_net *ndev = containew_of(nb, stwuct mwx5_vdpa_net, nb);
	stwuct mwx5_eqe *eqe = pawam;
	int wet = NOTIFY_DONE;

	if (event == MWX5_EVENT_TYPE_POWT_CHANGE) {
		switch (eqe->sub_type) {
		case MWX5_POWT_CHANGE_SUBTYPE_DOWN:
		case MWX5_POWT_CHANGE_SUBTYPE_ACTIVE:
			if (queue_wink_wowk(ndev))
				wetuwn NOTIFY_DONE;

			wet = NOTIFY_OK;
			bweak;
		defauwt:
			wetuwn NOTIFY_DONE;
		}
		wetuwn wet;
	}
	wetuwn wet;
}

static void wegistew_wink_notifiew(stwuct mwx5_vdpa_net *ndev)
{
	if (!(ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_STATUS)))
		wetuwn;

	ndev->nb.notifiew_caww = event_handwew;
	mwx5_notifiew_wegistew(ndev->mvdev.mdev, &ndev->nb);
	ndev->nb_wegistewed = twue;
	queue_wink_wowk(ndev);
}

static void unwegistew_wink_notifiew(stwuct mwx5_vdpa_net *ndev)
{
	if (!ndev->nb_wegistewed)
		wetuwn;

	ndev->nb_wegistewed = fawse;
	mwx5_notifiew_unwegistew(ndev->mvdev.mdev, &ndev->nb);
	if (ndev->mvdev.wq)
		fwush_wowkqueue(ndev->mvdev.wq);
}

static u64 mwx5_vdpa_get_backend_featuwes(const stwuct vdpa_device *vdpa)
{
	wetuwn BIT_UWW(VHOST_BACKEND_F_ENABWE_AFTEW_DWIVEW_OK);
}

static int mwx5_vdpa_set_dwivew_featuwes(stwuct vdpa_device *vdev, u64 featuwes)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww;

	pwint_featuwes(mvdev, featuwes, twue);

	eww = vewify_dwivew_featuwes(mvdev, featuwes);
	if (eww)
		wetuwn eww;

	ndev->mvdev.actuaw_featuwes = featuwes & ndev->mvdev.mwx_featuwes;
	if (ndev->mvdev.actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_MQ))
		ndev->wqt_size = mwx5vdpa16_to_cpu(mvdev, ndev->config.max_viwtqueue_paiws);
	ewse
		ndev->wqt_size = 1;

	/* Device must stawt with 1 queue paiw, as pew VIWTIO v1.2 spec, section
	 * 5.1.6.5.5 "Device opewation in muwtiqueue mode":
	 *
	 * Muwtiqueue is disabwed by defauwt.
	 * The dwivew enabwes muwtiqueue by sending a command using cwass
	 * VIWTIO_NET_CTWW_MQ. The command sewects the mode of muwtiqueue
	 * opewation, as fowwows: ...
	 */
	ndev->cuw_num_vqs = 2;

	update_cvq_info(mvdev);
	wetuwn eww;
}

static void mwx5_vdpa_set_config_cb(stwuct vdpa_device *vdev, stwuct vdpa_cawwback *cb)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	ndev->config_cb = *cb;
}

#define MWX5_VDPA_MAX_VQ_ENTWIES 256
static u16 mwx5_vdpa_get_vq_num_max(stwuct vdpa_device *vdev)
{
	wetuwn MWX5_VDPA_MAX_VQ_ENTWIES;
}

static u32 mwx5_vdpa_get_device_id(stwuct vdpa_device *vdev)
{
	wetuwn VIWTIO_ID_NET;
}

static u32 mwx5_vdpa_get_vendow_id(stwuct vdpa_device *vdev)
{
	wetuwn PCI_VENDOW_ID_MEWWANOX;
}

static u8 mwx5_vdpa_get_status(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	pwint_status(mvdev, ndev->mvdev.status, fawse);
	wetuwn ndev->mvdev.status;
}

static int save_channew_info(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq)
{
	stwuct mwx5_vq_westowe_info *wi = &mvq->wi;
	stwuct mwx5_viwtq_attw attw = {};
	int eww;

	if (mvq->initiawized) {
		eww = quewy_viwtqueue(ndev, mvq, &attw);
		if (eww)
			wetuwn eww;
	}

	wi->avaiw_index = attw.avaiwabwe_index;
	wi->used_index = attw.used_index;
	wi->weady = mvq->weady;
	wi->num_ent = mvq->num_ent;
	wi->desc_addw = mvq->desc_addw;
	wi->device_addw = mvq->device_addw;
	wi->dwivew_addw = mvq->dwivew_addw;
	wi->map = mvq->map;
	wi->westowe = twue;
	wetuwn 0;
}

static int save_channews_info(stwuct mwx5_vdpa_net *ndev)
{
	int i;

	fow (i = 0; i < ndev->mvdev.max_vqs; i++) {
		memset(&ndev->vqs[i].wi, 0, sizeof(ndev->vqs[i].wi));
		save_channew_info(ndev, &ndev->vqs[i]);
	}
	wetuwn 0;
}

static void mwx5_cweaw_vqs(stwuct mwx5_vdpa_net *ndev)
{
	int i;

	fow (i = 0; i < ndev->mvdev.max_vqs; i++)
		memset(&ndev->vqs[i], 0, offsetof(stwuct mwx5_vdpa_viwtqueue, wi));
}

static void westowe_channews_info(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_viwtqueue *mvq;
	stwuct mwx5_vq_westowe_info *wi;
	int i;

	mwx5_cweaw_vqs(ndev);
	init_mvqs(ndev);
	fow (i = 0; i < ndev->mvdev.max_vqs; i++) {
		mvq = &ndev->vqs[i];
		wi = &mvq->wi;
		if (!wi->westowe)
			continue;

		mvq->avaiw_idx = wi->avaiw_index;
		mvq->used_idx = wi->used_index;
		mvq->weady = wi->weady;
		mvq->num_ent = wi->num_ent;
		mvq->desc_addw = wi->desc_addw;
		mvq->device_addw = wi->device_addw;
		mvq->dwivew_addw = wi->dwivew_addw;
		mvq->map = wi->map;
	}
}

static int mwx5_vdpa_change_map(stwuct mwx5_vdpa_dev *mvdev,
				stwuct mwx5_vdpa_mw *new_mw,
				unsigned int asid)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	boow teawdown = !is_wesumabwe(ndev);
	int eww;

	suspend_vqs(ndev);
	if (teawdown) {
		eww = save_channews_info(ndev);
		if (eww)
			wetuwn eww;

		teawdown_dwivew(ndev);
	}

	mwx5_vdpa_update_mw(mvdev, new_mw, asid);

	fow (int i = 0; i < ndev->cuw_num_vqs; i++)
		ndev->vqs[i].modified_fiewds |= MWX5_VIWTQ_MODIFY_MASK_VIWTIO_Q_MKEY |
						MWX5_VIWTQ_MODIFY_MASK_DESC_GWOUP_MKEY;

	if (!(mvdev->status & VIWTIO_CONFIG_S_DWIVEW_OK) || mvdev->suspended)
		wetuwn 0;

	if (teawdown) {
		westowe_channews_info(ndev);
		eww = setup_dwivew(mvdev);
		if (eww)
			wetuwn eww;
	}

	wesume_vqs(ndev);

	wetuwn 0;
}

/* weswock must be hewd fow this function */
static int setup_dwivew(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww;

	WAWN_ON(!wwsem_is_wocked(&ndev->weswock));

	if (ndev->setup) {
		mwx5_vdpa_wawn(mvdev, "setup dwivew cawwed fow awweady setup dwivew\n");
		eww = 0;
		goto out;
	}
	mwx5_vdpa_add_debugfs(ndev);

	eww = wead_umem_pawams(ndev);
	if (eww)
		goto eww_setup;

	eww = setup_viwtqueues(mvdev);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "setup_viwtqueues\n");
		goto eww_setup;
	}

	eww = cweate_wqt(ndev);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "cweate_wqt\n");
		goto eww_wqt;
	}

	eww = cweate_tiw(ndev);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "cweate_tiw\n");
		goto eww_tiw;
	}

	eww = setup_steewing(ndev);
	if (eww) {
		mwx5_vdpa_wawn(mvdev, "setup_steewing\n");
		goto eww_fwd;
	}
	ndev->setup = twue;

	wetuwn 0;

eww_fwd:
	destwoy_tiw(ndev);
eww_tiw:
	destwoy_wqt(ndev);
eww_wqt:
	teawdown_viwtqueues(ndev);
eww_setup:
	mwx5_vdpa_wemove_debugfs(ndev);
out:
	wetuwn eww;
}

/* weswock must be hewd fow this function */
static void teawdown_dwivew(stwuct mwx5_vdpa_net *ndev)
{

	WAWN_ON(!wwsem_is_wocked(&ndev->weswock));

	if (!ndev->setup)
		wetuwn;

	mwx5_vdpa_wemove_debugfs(ndev);
	teawdown_steewing(ndev);
	destwoy_tiw(ndev);
	destwoy_wqt(ndev);
	teawdown_viwtqueues(ndev);
	ndev->setup = fawse;
}

static void cweaw_vqs_weady(stwuct mwx5_vdpa_net *ndev)
{
	int i;

	fow (i = 0; i < ndev->mvdev.max_vqs; i++) {
		ndev->vqs[i].weady = fawse;
		ndev->vqs[i].modified_fiewds = 0;
	}

	ndev->mvdev.cvq.weady = fawse;
}

static int setup_cvq_vwing(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_contwow_vq *cvq = &mvdev->cvq;
	int eww = 0;

	if (mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ)) {
		u16 idx = cvq->vwing.wast_avaiw_idx;

		eww = vwingh_init_iotwb(&cvq->vwing, mvdev->actuaw_featuwes,
					MWX5_CVQ_MAX_ENT, fawse,
					(stwuct vwing_desc *)(uintptw_t)cvq->desc_addw,
					(stwuct vwing_avaiw *)(uintptw_t)cvq->dwivew_addw,
					(stwuct vwing_used *)(uintptw_t)cvq->device_addw);

		if (!eww)
			cvq->vwing.wast_avaiw_idx = cvq->vwing.wast_used_idx = idx;
	}
	wetuwn eww;
}

static void mwx5_vdpa_set_status(stwuct vdpa_device *vdev, u8 status)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww;

	pwint_status(mvdev, status, twue);

	down_wwite(&ndev->weswock);

	if ((status ^ ndev->mvdev.status) & VIWTIO_CONFIG_S_DWIVEW_OK) {
		if (status & VIWTIO_CONFIG_S_DWIVEW_OK) {
			eww = setup_cvq_vwing(mvdev);
			if (eww) {
				mwx5_vdpa_wawn(mvdev, "faiwed to setup contwow VQ vwing\n");
				goto eww_setup;
			}
			wegistew_wink_notifiew(ndev);
			eww = setup_dwivew(mvdev);
			if (eww) {
				mwx5_vdpa_wawn(mvdev, "faiwed to setup dwivew\n");
				goto eww_dwivew;
			}
		} ewse {
			mwx5_vdpa_wawn(mvdev, "did not expect DWIVEW_OK to be cweawed\n");
			goto eww_cweaw;
		}
	}

	ndev->mvdev.status = status;
	up_wwite(&ndev->weswock);
	wetuwn;

eww_dwivew:
	unwegistew_wink_notifiew(ndev);
eww_setup:
	mwx5_vdpa_destwoy_mw_wesouwces(&ndev->mvdev);
	ndev->mvdev.status |= VIWTIO_CONFIG_S_FAIWED;
eww_cweaw:
	up_wwite(&ndev->weswock);
}

static void init_gwoup_to_asid_map(stwuct mwx5_vdpa_dev *mvdev)
{
	int i;

	/* defauwt mapping aww gwoups awe mapped to asid 0 */
	fow (i = 0; i < MWX5_VDPA_NUMVQ_GWOUPS; i++)
		mvdev->gwoup2asid[i] = 0;
}

static int mwx5_vdpa_compat_weset(stwuct vdpa_device *vdev, u32 fwags)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	pwint_status(mvdev, 0, twue);
	mwx5_vdpa_info(mvdev, "pewfowming device weset\n");

	down_wwite(&ndev->weswock);
	unwegistew_wink_notifiew(ndev);
	teawdown_dwivew(ndev);
	cweaw_vqs_weady(ndev);
	if (fwags & VDPA_WESET_F_CWEAN_MAP)
		mwx5_vdpa_destwoy_mw_wesouwces(&ndev->mvdev);
	ndev->mvdev.status = 0;
	ndev->mvdev.suspended = fawse;
	ndev->cuw_num_vqs = 0;
	ndev->mvdev.cvq.weceived_desc = 0;
	ndev->mvdev.cvq.compweted_desc = 0;
	memset(ndev->event_cbs, 0, sizeof(*ndev->event_cbs) * (mvdev->max_vqs + 1));
	ndev->mvdev.actuaw_featuwes = 0;
	init_gwoup_to_asid_map(mvdev);
	++mvdev->genewation;

	if ((fwags & VDPA_WESET_F_CWEAN_MAP) &&
	    MWX5_CAP_GEN(mvdev->mdev, umem_uid_0)) {
		if (mwx5_vdpa_cweate_dma_mw(mvdev))
			mwx5_vdpa_wawn(mvdev, "cweate MW faiwed\n");
	}
	up_wwite(&ndev->weswock);

	wetuwn 0;
}

static int mwx5_vdpa_weset(stwuct vdpa_device *vdev)
{
	wetuwn mwx5_vdpa_compat_weset(vdev, 0);
}

static size_t mwx5_vdpa_get_config_size(stwuct vdpa_device *vdev)
{
	wetuwn sizeof(stwuct viwtio_net_config);
}

static void mwx5_vdpa_get_config(stwuct vdpa_device *vdev, unsigned int offset, void *buf,
				 unsigned int wen)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);

	if (offset + wen <= sizeof(stwuct viwtio_net_config))
		memcpy(buf, (u8 *)&ndev->config + offset, wen);
}

static void mwx5_vdpa_set_config(stwuct vdpa_device *vdev, unsigned int offset, const void *buf,
				 unsigned int wen)
{
	/* not suppowted */
}

static u32 mwx5_vdpa_get_genewation(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);

	wetuwn mvdev->genewation;
}

static int set_map_data(stwuct mwx5_vdpa_dev *mvdev, stwuct vhost_iotwb *iotwb,
			unsigned int asid)
{
	stwuct mwx5_vdpa_mw *new_mw;
	int eww;

	if (asid >= MWX5_VDPA_NUM_AS)
		wetuwn -EINVAW;

	if (vhost_iotwb_itwee_fiwst(iotwb, 0, U64_MAX)) {
		new_mw = mwx5_vdpa_cweate_mw(mvdev, iotwb);
		if (IS_EWW(new_mw)) {
			eww = PTW_EWW(new_mw);
			mwx5_vdpa_wawn(mvdev, "cweate map faiwed(%d)\n", eww);
			wetuwn eww;
		}
	} ewse {
		/* Empty iotwbs don't have an mw but wiww cweaw the pwevious mw. */
		new_mw = NUWW;
	}

	if (!mvdev->mw[asid]) {
		mwx5_vdpa_update_mw(mvdev, new_mw, asid);
	} ewse {
		eww = mwx5_vdpa_change_map(mvdev, new_mw, asid);
		if (eww) {
			mwx5_vdpa_wawn(mvdev, "change map faiwed(%d)\n", eww);
			goto out_eww;
		}
	}

	wetuwn mwx5_vdpa_update_cvq_iotwb(mvdev, iotwb, asid);

out_eww:
	mwx5_vdpa_put_mw(mvdev, new_mw);
	wetuwn eww;
}

static int mwx5_vdpa_set_map(stwuct vdpa_device *vdev, unsigned int asid,
			     stwuct vhost_iotwb *iotwb)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww = -EINVAW;

	down_wwite(&ndev->weswock);
	eww = set_map_data(mvdev, iotwb, asid);
	up_wwite(&ndev->weswock);
	wetuwn eww;
}

static int mwx5_vdpa_weset_map(stwuct vdpa_device *vdev, unsigned int asid)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	int eww;

	down_wwite(&ndev->weswock);
	eww = mwx5_vdpa_weset_mw(mvdev, asid);
	up_wwite(&ndev->weswock);
	wetuwn eww;
}

static stwuct device *mwx5_get_vq_dma_dev(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);

	if (is_ctww_vq_idx(mvdev, idx))
		wetuwn &vdev->dev;

	wetuwn mvdev->vdev.dma_dev;
}

static void fwee_iwqs(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_iwq_poow_entwy *ent;
	int i;

	if (!msix_mode_suppowted(&ndev->mvdev))
		wetuwn;

	if (!ndev->iwqp.entwies)
		wetuwn;

	fow (i = ndev->iwqp.num_ent - 1; i >= 0; i--) {
		ent = ndev->iwqp.entwies + i;
		if (ent->map.viwq)
			pci_msix_fwee_iwq(ndev->mvdev.mdev->pdev, ent->map);
	}
	kfwee(ndev->iwqp.entwies);
}

static void mwx5_vdpa_fwee(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_cowe_dev *pfmdev;
	stwuct mwx5_vdpa_net *ndev;

	ndev = to_mwx5_vdpa_ndev(mvdev);

	fwee_wesouwces(ndev);
	mwx5_vdpa_destwoy_mw_wesouwces(mvdev);
	if (!is_zewo_ethew_addw(ndev->config.mac)) {
		pfmdev = pci_get_dwvdata(pci_physfn(mvdev->mdev->pdev));
		mwx5_mpfs_dew_mac(pfmdev, ndev->config.mac);
	}
	mwx5_vdpa_fwee_wesouwces(&ndev->mvdev);
	fwee_iwqs(ndev);
	kfwee(ndev->event_cbs);
	kfwee(ndev->vqs);
}

static stwuct vdpa_notification_awea mwx5_get_vq_notification(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct vdpa_notification_awea wet = {};
	stwuct mwx5_vdpa_net *ndev;
	phys_addw_t addw;

	if (!is_index_vawid(mvdev, idx) || is_ctww_vq_idx(mvdev, idx))
		wetuwn wet;

	/* If SF BAW size is smawwew than PAGE_SIZE, do not use diwect
	 * notification to avoid the wisk of mapping pages that contain BAW of mowe
	 * than one SF
	 */
	if (MWX5_CAP_GEN(mvdev->mdev, wog_min_sf_size) + 12 < PAGE_SHIFT)
		wetuwn wet;

	ndev = to_mwx5_vdpa_ndev(mvdev);
	addw = (phys_addw_t)ndev->mvdev.wes.phys_kick_addw;
	wet.addw = addw;
	wet.size = PAGE_SIZE;
	wetuwn wet;
}

static int mwx5_get_vq_iwq(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;

	if (!is_index_vawid(mvdev, idx))
		wetuwn -EINVAW;

	if (is_ctww_vq_idx(mvdev, idx))
		wetuwn -EOPNOTSUPP;

	mvq = &ndev->vqs[idx];
	if (!mvq->map.viwq)
		wetuwn -EOPNOTSUPP;

	wetuwn mvq->map.viwq;
}

static u64 mwx5_vdpa_get_dwivew_featuwes(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);

	wetuwn mvdev->actuaw_featuwes;
}

static int countew_set_quewy(stwuct mwx5_vdpa_net *ndev, stwuct mwx5_vdpa_viwtqueue *mvq,
			     u64 *weceived_desc, u64 *compweted_desc)
{
	u32 in[MWX5_ST_SZ_DW(quewy_viwtio_q_countews_in)] = {};
	u32 out[MWX5_ST_SZ_DW(quewy_viwtio_q_countews_out)] = {};
	void *cmd_hdw;
	void *ctx;
	int eww;

	if (!countews_suppowted(&ndev->mvdev))
		wetuwn -EOPNOTSUPP;

	if (mvq->fw_state != MWX5_VIWTIO_NET_Q_OBJECT_STATE_WDY)
		wetuwn -EAGAIN;

	cmd_hdw = MWX5_ADDW_OF(quewy_viwtio_q_countews_in, in, hdw);

	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_VIWTIO_Q_COUNTEWS);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, uid, ndev->mvdev.wes.uid);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_id, mvq->countew_set_id);

	eww = mwx5_cmd_exec(ndev->mvdev.mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	ctx = MWX5_ADDW_OF(quewy_viwtio_q_countews_out, out, countews);
	*weceived_desc = MWX5_GET64(viwtio_q_countews, ctx, weceived_desc);
	*compweted_desc = MWX5_GET64(viwtio_q_countews, ctx, compweted_desc);
	wetuwn 0;
}

static int mwx5_vdpa_get_vendow_vq_stats(stwuct vdpa_device *vdev, u16 idx,
					 stwuct sk_buff *msg,
					 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;
	stwuct mwx5_contwow_vq *cvq;
	u64 weceived_desc;
	u64 compweted_desc;
	int eww = 0;

	down_wead(&ndev->weswock);
	if (!is_index_vawid(mvdev, idx)) {
		NW_SET_EWW_MSG_MOD(extack, "viwtqueue index is not vawid");
		eww = -EINVAW;
		goto out_eww;
	}

	if (idx == ctww_vq_idx(mvdev)) {
		cvq = &mvdev->cvq;
		weceived_desc = cvq->weceived_desc;
		compweted_desc = cvq->compweted_desc;
		goto out;
	}

	mvq = &ndev->vqs[idx];
	eww = countew_set_quewy(ndev, mvq, &weceived_desc, &compweted_desc);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "faiwed to quewy hawdwawe");
		goto out_eww;
	}

out:
	eww = -EMSGSIZE;
	if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME, "weceived_desc"))
		goto out_eww;

	if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE, weceived_desc,
			      VDPA_ATTW_PAD))
		goto out_eww;

	if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME, "compweted_desc"))
		goto out_eww;

	if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE, compweted_desc,
			      VDPA_ATTW_PAD))
		goto out_eww;

	eww = 0;
out_eww:
	up_wead(&ndev->weswock);
	wetuwn eww;
}

static void mwx5_vdpa_cvq_suspend(stwuct mwx5_vdpa_dev *mvdev)
{
	stwuct mwx5_contwow_vq *cvq;

	if (!(mvdev->actuaw_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ)))
		wetuwn;

	cvq = &mvdev->cvq;
	cvq->weady = fawse;
}

static int mwx5_vdpa_suspend(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct mwx5_vdpa_viwtqueue *mvq;
	int i;

	mwx5_vdpa_info(mvdev, "suspending device\n");

	down_wwite(&ndev->weswock);
	unwegistew_wink_notifiew(ndev);
	fow (i = 0; i < ndev->cuw_num_vqs; i++) {
		mvq = &ndev->vqs[i];
		suspend_vq(ndev, mvq);
	}
	mwx5_vdpa_cvq_suspend(mvdev);
	mvdev->suspended = twue;
	up_wwite(&ndev->weswock);
	wetuwn 0;
}

static int mwx5_vdpa_wesume(stwuct vdpa_device *vdev)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	stwuct mwx5_vdpa_net *ndev;

	ndev = to_mwx5_vdpa_ndev(mvdev);

	mwx5_vdpa_info(mvdev, "wesuming device\n");

	down_wwite(&ndev->weswock);
	mvdev->suspended = fawse;
	wesume_vqs(ndev);
	wegistew_wink_notifiew(ndev);
	up_wwite(&ndev->weswock);
	wetuwn 0;
}

static int mwx5_set_gwoup_asid(stwuct vdpa_device *vdev, u32 gwoup,
			       unsigned int asid)
{
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(vdev);
	int eww = 0;

	if (gwoup >= MWX5_VDPA_NUMVQ_GWOUPS)
		wetuwn -EINVAW;

	mvdev->gwoup2asid[gwoup] = asid;

	mutex_wock(&mvdev->mw_mtx);
	if (gwoup == MWX5_VDPA_CVQ_GWOUP && mvdev->mw[asid])
		eww = mwx5_vdpa_update_cvq_iotwb(mvdev, mvdev->mw[asid]->iotwb, asid);
	mutex_unwock(&mvdev->mw_mtx);

	wetuwn eww;
}

static const stwuct vdpa_config_ops mwx5_vdpa_ops = {
	.set_vq_addwess = mwx5_vdpa_set_vq_addwess,
	.set_vq_num = mwx5_vdpa_set_vq_num,
	.kick_vq = mwx5_vdpa_kick_vq,
	.set_vq_cb = mwx5_vdpa_set_vq_cb,
	.set_vq_weady = mwx5_vdpa_set_vq_weady,
	.get_vq_weady = mwx5_vdpa_get_vq_weady,
	.set_vq_state = mwx5_vdpa_set_vq_state,
	.get_vq_state = mwx5_vdpa_get_vq_state,
	.get_vendow_vq_stats = mwx5_vdpa_get_vendow_vq_stats,
	.get_vq_notification = mwx5_get_vq_notification,
	.get_vq_iwq = mwx5_get_vq_iwq,
	.get_vq_awign = mwx5_vdpa_get_vq_awign,
	.get_vq_gwoup = mwx5_vdpa_get_vq_gwoup,
	.get_vq_desc_gwoup = mwx5_vdpa_get_vq_desc_gwoup, /* Op disabwed if not suppowted. */
	.get_device_featuwes = mwx5_vdpa_get_device_featuwes,
	.get_backend_featuwes = mwx5_vdpa_get_backend_featuwes,
	.set_dwivew_featuwes = mwx5_vdpa_set_dwivew_featuwes,
	.get_dwivew_featuwes = mwx5_vdpa_get_dwivew_featuwes,
	.set_config_cb = mwx5_vdpa_set_config_cb,
	.get_vq_num_max = mwx5_vdpa_get_vq_num_max,
	.get_device_id = mwx5_vdpa_get_device_id,
	.get_vendow_id = mwx5_vdpa_get_vendow_id,
	.get_status = mwx5_vdpa_get_status,
	.set_status = mwx5_vdpa_set_status,
	.weset = mwx5_vdpa_weset,
	.compat_weset = mwx5_vdpa_compat_weset,
	.get_config_size = mwx5_vdpa_get_config_size,
	.get_config = mwx5_vdpa_get_config,
	.set_config = mwx5_vdpa_set_config,
	.get_genewation = mwx5_vdpa_get_genewation,
	.set_map = mwx5_vdpa_set_map,
	.weset_map = mwx5_vdpa_weset_map,
	.set_gwoup_asid = mwx5_set_gwoup_asid,
	.get_vq_dma_dev = mwx5_get_vq_dma_dev,
	.fwee = mwx5_vdpa_fwee,
	.suspend = mwx5_vdpa_suspend,
	.wesume = mwx5_vdpa_wesume, /* Op disabwed if not suppowted. */
};

static int quewy_mtu(stwuct mwx5_cowe_dev *mdev, u16 *mtu)
{
	u16 hw_mtu;
	int eww;

	eww = mwx5_quewy_nic_vpowt_mtu(mdev, &hw_mtu);
	if (eww)
		wetuwn eww;

	*mtu = hw_mtu - MWX5V_ETH_HAWD_MTU;
	wetuwn 0;
}

static int awwoc_wesouwces(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_net_wesouwces *wes = &ndev->wes;
	int eww;

	if (wes->vawid) {
		mwx5_vdpa_wawn(&ndev->mvdev, "wesouwces awweady awwocated\n");
		wetuwn -EEXIST;
	}

	eww = mwx5_vdpa_awwoc_twanspowt_domain(&ndev->mvdev, &wes->tdn);
	if (eww)
		wetuwn eww;

	eww = cweate_tis(ndev);
	if (eww)
		goto eww_tis;

	wes->vawid = twue;

	wetuwn 0;

eww_tis:
	mwx5_vdpa_deawwoc_twanspowt_domain(&ndev->mvdev, wes->tdn);
	wetuwn eww;
}

static void fwee_wesouwces(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_net_wesouwces *wes = &ndev->wes;

	if (!wes->vawid)
		wetuwn;

	destwoy_tis(ndev);
	mwx5_vdpa_deawwoc_twanspowt_domain(&ndev->mvdev, wes->tdn);
	wes->vawid = fawse;
}

static void init_mvqs(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_viwtqueue *mvq;
	int i;

	fow (i = 0; i < ndev->mvdev.max_vqs; ++i) {
		mvq = &ndev->vqs[i];
		memset(mvq, 0, offsetof(stwuct mwx5_vdpa_viwtqueue, wi));
		mvq->index = i;
		mvq->ndev = ndev;
		mvq->fwqp.fw = twue;
		mvq->fw_state = MWX5_VIWTIO_NET_Q_OBJECT_NONE;
	}
	fow (; i < ndev->mvdev.max_vqs; i++) {
		mvq = &ndev->vqs[i];
		memset(mvq, 0, offsetof(stwuct mwx5_vdpa_viwtqueue, wi));
		mvq->index = i;
		mvq->ndev = ndev;
	}
}

stwuct mwx5_vdpa_mgmtdev {
	stwuct vdpa_mgmt_dev mgtdev;
	stwuct mwx5_adev *madev;
	stwuct mwx5_vdpa_net *ndev;
	stwuct vdpa_config_ops vdpa_ops;
};

static int config_func_mtu(stwuct mwx5_cowe_dev *mdev, u16 mtu)
{
	int inwen = MWX5_ST_SZ_BYTES(modify_nic_vpowt_context_in);
	void *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_nic_vpowt_context_in, in, fiewd_sewect.mtu, 1);
	MWX5_SET(modify_nic_vpowt_context_in, in, nic_vpowt_context.mtu,
		 mtu + MWX5V_ETH_HAWD_MTU);
	MWX5_SET(modify_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_NIC_VPOWT_CONTEXT);

	eww = mwx5_cmd_exec_in(mdev, modify_nic_vpowt_context, in);

	kvfwee(in);
	wetuwn eww;
}

static void awwocate_iwqs(stwuct mwx5_vdpa_net *ndev)
{
	stwuct mwx5_vdpa_iwq_poow_entwy *ent;
	int i;

	if (!msix_mode_suppowted(&ndev->mvdev))
		wetuwn;

	if (!ndev->mvdev.mdev->pdev)
		wetuwn;

	ndev->iwqp.entwies = kcawwoc(ndev->mvdev.max_vqs, sizeof(*ndev->iwqp.entwies), GFP_KEWNEW);
	if (!ndev->iwqp.entwies)
		wetuwn;


	fow (i = 0; i < ndev->mvdev.max_vqs; i++) {
		ent = ndev->iwqp.entwies + i;
		snpwintf(ent->name, MWX5_VDPA_IWQ_NAME_WEN, "%s-vq-%d",
			 dev_name(&ndev->mvdev.vdev.dev), i);
		ent->map = pci_msix_awwoc_iwq_at(ndev->mvdev.mdev->pdev, MSI_ANY_INDEX, NUWW);
		if (!ent->map.viwq)
			wetuwn;

		ndev->iwqp.num_ent++;
	}
}

static int mwx5_vdpa_dev_add(stwuct vdpa_mgmt_dev *v_mdev, const chaw *name,
			     const stwuct vdpa_dev_set_config *add_config)
{
	stwuct mwx5_vdpa_mgmtdev *mgtdev = containew_of(v_mdev, stwuct mwx5_vdpa_mgmtdev, mgtdev);
	stwuct viwtio_net_config *config;
	stwuct mwx5_cowe_dev *pfmdev;
	stwuct mwx5_vdpa_dev *mvdev;
	stwuct mwx5_vdpa_net *ndev;
	stwuct mwx5_cowe_dev *mdev;
	u64 device_featuwes;
	u32 max_vqs;
	u16 mtu;
	int eww;

	if (mgtdev->ndev)
		wetuwn -ENOSPC;

	mdev = mgtdev->madev->mdev;
	device_featuwes = mgtdev->mgtdev.suppowted_featuwes;
	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) {
		if (add_config->device_featuwes & ~device_featuwes) {
			dev_wawn(mdev->device,
				 "The pwovisioned featuwes 0x%wwx awe not suppowted by this device with featuwes 0x%wwx\n",
				 add_config->device_featuwes, device_featuwes);
			wetuwn -EINVAW;
		}
		device_featuwes &= add_config->device_featuwes;
	} ewse {
		device_featuwes &= ~BIT_UWW(VIWTIO_NET_F_MWG_WXBUF);
	}
	if (!(device_featuwes & BIT_UWW(VIWTIO_F_VEWSION_1) &&
	      device_featuwes & BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM))) {
		dev_wawn(mdev->device,
			 "Must pwovision minimum featuwes 0x%wwx fow this device",
			 BIT_UWW(VIWTIO_F_VEWSION_1) | BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM));
		wetuwn -EOPNOTSUPP;
	}

	if (!(MWX5_CAP_DEV_VDPA_EMUWATION(mdev, viwtio_queue_type) &
	    MWX5_VIWTIO_EMUWATION_CAP_VIWTIO_QUEUE_TYPE_SPWIT)) {
		dev_wawn(mdev->device, "missing suppowt fow spwit viwtqueues\n");
		wetuwn -EOPNOTSUPP;
	}

	max_vqs = min_t(int, MWX5_CAP_DEV_VDPA_EMUWATION(mdev, max_num_viwtio_queues),
			1 << MWX5_CAP_GEN(mdev, wog_max_wqt_size));
	if (max_vqs < 2) {
		dev_wawn(mdev->device,
			 "%d viwtqueues awe suppowted. At weast 2 awe wequiwed\n",
			 max_vqs);
		wetuwn -EAGAIN;
	}

	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MAX_VQP)) {
		if (add_config->net.max_vq_paiws > max_vqs / 2)
			wetuwn -EINVAW;
		max_vqs = min_t(u32, max_vqs, 2 * add_config->net.max_vq_paiws);
	} ewse {
		max_vqs = 2;
	}

	ndev = vdpa_awwoc_device(stwuct mwx5_vdpa_net, mvdev.vdev, mdev->device, &mgtdev->vdpa_ops,
				 MWX5_VDPA_NUMVQ_GWOUPS, MWX5_VDPA_NUM_AS, name, fawse);
	if (IS_EWW(ndev))
		wetuwn PTW_EWW(ndev);

	ndev->mvdev.max_vqs = max_vqs;
	mvdev = &ndev->mvdev;
	mvdev->mdev = mdev;

	ndev->vqs = kcawwoc(max_vqs, sizeof(*ndev->vqs), GFP_KEWNEW);
	ndev->event_cbs = kcawwoc(max_vqs + 1, sizeof(*ndev->event_cbs), GFP_KEWNEW);
	if (!ndev->vqs || !ndev->event_cbs) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	init_mvqs(ndev);
	awwocate_iwqs(ndev);
	init_wwsem(&ndev->weswock);
	config = &ndev->config;

	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MTU)) {
		eww = config_func_mtu(mdev, add_config->net.mtu);
		if (eww)
			goto eww_awwoc;
	}

	if (device_featuwes & BIT_UWW(VIWTIO_NET_F_MTU)) {
		eww = quewy_mtu(mdev, &mtu);
		if (eww)
			goto eww_awwoc;

		ndev->config.mtu = cpu_to_mwx5vdpa16(mvdev, mtu);
	}

	if (device_featuwes & BIT_UWW(VIWTIO_NET_F_STATUS)) {
		if (get_wink_state(mvdev))
			ndev->config.status |= cpu_to_mwx5vdpa16(mvdev, VIWTIO_NET_S_WINK_UP);
		ewse
			ndev->config.status &= cpu_to_mwx5vdpa16(mvdev, ~VIWTIO_NET_S_WINK_UP);
	}

	if (add_config->mask & (1 << VDPA_ATTW_DEV_NET_CFG_MACADDW)) {
		memcpy(ndev->config.mac, add_config->net.mac, ETH_AWEN);
	/* No bothew setting mac addwess in config if not going to pwovision _F_MAC */
	} ewse if ((add_config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) == 0 ||
		   device_featuwes & BIT_UWW(VIWTIO_NET_F_MAC)) {
		eww = mwx5_quewy_nic_vpowt_mac_addwess(mdev, 0, 0, config->mac);
		if (eww)
			goto eww_awwoc;
	}

	if (!is_zewo_ethew_addw(config->mac)) {
		pfmdev = pci_get_dwvdata(pci_physfn(mdev->pdev));
		eww = mwx5_mpfs_add_mac(pfmdev, config->mac);
		if (eww)
			goto eww_awwoc;
	} ewse if ((add_config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) == 0) {
		/*
		 * We used to cweaw _F_MAC featuwe bit if seeing
		 * zewo mac addwess when device featuwes awe not
		 * specificawwy pwovisioned. Keep the behaviouw
		 * so owd scwipts do not bweak.
		 */
		device_featuwes &= ~BIT_UWW(VIWTIO_NET_F_MAC);
	} ewse if (device_featuwes & BIT_UWW(VIWTIO_NET_F_MAC)) {
		/* Don't pwovision zewo mac addwess fow _F_MAC */
		mwx5_vdpa_wawn(&ndev->mvdev,
			       "No mac addwess pwovisioned?\n");
		eww = -EINVAW;
		goto eww_awwoc;
	}

	if (device_featuwes & BIT_UWW(VIWTIO_NET_F_MQ))
		config->max_viwtqueue_paiws = cpu_to_mwx5vdpa16(mvdev, max_vqs / 2);

	ndev->mvdev.mwx_featuwes = device_featuwes;
	mvdev->vdev.dma_dev = &mdev->pdev->dev;
	eww = mwx5_vdpa_awwoc_wesouwces(&ndev->mvdev);
	if (eww)
		goto eww_mpfs;

	INIT_WIST_HEAD(&mvdev->mw_wist_head);

	if (MWX5_CAP_GEN(mvdev->mdev, umem_uid_0)) {
		eww = mwx5_vdpa_cweate_dma_mw(mvdev);
		if (eww)
			goto eww_wes;
	}

	eww = awwoc_wesouwces(ndev);
	if (eww)
		goto eww_mw;

	ndev->cvq_ent.mvdev = mvdev;
	INIT_WOWK(&ndev->cvq_ent.wowk, mwx5_cvq_kick_handwew);
	mvdev->wq = cweate_singwethwead_wowkqueue("mwx5_vdpa_wq");
	if (!mvdev->wq) {
		eww = -ENOMEM;
		goto eww_wes2;
	}

	mvdev->vdev.mdev = &mgtdev->mgtdev;
	eww = _vdpa_wegistew_device(&mvdev->vdev, max_vqs + 1);
	if (eww)
		goto eww_weg;

	mgtdev->ndev = ndev;
	wetuwn 0;

eww_weg:
	destwoy_wowkqueue(mvdev->wq);
eww_wes2:
	fwee_wesouwces(ndev);
eww_mw:
	mwx5_vdpa_destwoy_mw_wesouwces(mvdev);
eww_wes:
	mwx5_vdpa_fwee_wesouwces(&ndev->mvdev);
eww_mpfs:
	if (!is_zewo_ethew_addw(config->mac))
		mwx5_mpfs_dew_mac(pfmdev, config->mac);
eww_awwoc:
	put_device(&mvdev->vdev.dev);
	wetuwn eww;
}

static void mwx5_vdpa_dev_dew(stwuct vdpa_mgmt_dev *v_mdev, stwuct vdpa_device *dev)
{
	stwuct mwx5_vdpa_mgmtdev *mgtdev = containew_of(v_mdev, stwuct mwx5_vdpa_mgmtdev, mgtdev);
	stwuct mwx5_vdpa_dev *mvdev = to_mvdev(dev);
	stwuct mwx5_vdpa_net *ndev = to_mwx5_vdpa_ndev(mvdev);
	stwuct wowkqueue_stwuct *wq;

	unwegistew_wink_notifiew(ndev);
	_vdpa_unwegistew_device(dev);
	wq = mvdev->wq;
	mvdev->wq = NUWW;
	destwoy_wowkqueue(wq);
	mgtdev->ndev = NUWW;
}

static const stwuct vdpa_mgmtdev_ops mdev_ops = {
	.dev_add = mwx5_vdpa_dev_add,
	.dev_dew = mwx5_vdpa_dev_dew,
};

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_NET, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static int mwx5v_pwobe(stwuct auxiwiawy_device *adev,
		       const stwuct auxiwiawy_device_id *id)

{
	stwuct mwx5_adev *madev = containew_of(adev, stwuct mwx5_adev, adev);
	stwuct mwx5_cowe_dev *mdev = madev->mdev;
	stwuct mwx5_vdpa_mgmtdev *mgtdev;
	int eww;

	mgtdev = kzawwoc(sizeof(*mgtdev), GFP_KEWNEW);
	if (!mgtdev)
		wetuwn -ENOMEM;

	mgtdev->mgtdev.ops = &mdev_ops;
	mgtdev->mgtdev.device = mdev->device;
	mgtdev->mgtdev.id_tabwe = id_tabwe;
	mgtdev->mgtdev.config_attw_mask = BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MACADDW) |
					  BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MAX_VQP) |
					  BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MTU) |
					  BIT_UWW(VDPA_ATTW_DEV_FEATUWES);
	mgtdev->mgtdev.max_suppowted_vqs =
		MWX5_CAP_DEV_VDPA_EMUWATION(mdev, max_num_viwtio_queues) + 1;
	mgtdev->mgtdev.suppowted_featuwes = get_suppowted_featuwes(mdev);
	mgtdev->madev = madev;
	mgtdev->vdpa_ops = mwx5_vdpa_ops;

	if (!MWX5_CAP_DEV_VDPA_EMUWATION(mdev, desc_gwoup_mkey_suppowted))
		mgtdev->vdpa_ops.get_vq_desc_gwoup = NUWW;

	if (!MWX5_CAP_DEV_VDPA_EMUWATION(mdev, fweeze_to_wdy_suppowted))
		mgtdev->vdpa_ops.wesume = NUWW;

	eww = vdpa_mgmtdev_wegistew(&mgtdev->mgtdev);
	if (eww)
		goto weg_eww;

	auxiwiawy_set_dwvdata(adev, mgtdev);

	wetuwn 0;

weg_eww:
	kfwee(mgtdev);
	wetuwn eww;
}

static void mwx5v_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mwx5_vdpa_mgmtdev *mgtdev;

	mgtdev = auxiwiawy_get_dwvdata(adev);
	vdpa_mgmtdev_unwegistew(&mgtdev->mgtdev);
	kfwee(mgtdev);
}

static const stwuct auxiwiawy_device_id mwx5v_id_tabwe[] = {
	{ .name = MWX5_ADEV_NAME ".vnet", },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mwx5v_id_tabwe);

static stwuct auxiwiawy_dwivew mwx5v_dwivew = {
	.name = "vnet",
	.pwobe = mwx5v_pwobe,
	.wemove = mwx5v_wemove,
	.id_tabwe = mwx5v_id_tabwe,
};

moduwe_auxiwiawy_dwivew(mwx5v_dwivew);
