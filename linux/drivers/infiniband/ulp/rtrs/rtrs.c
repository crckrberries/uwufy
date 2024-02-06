// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/inet.h>

#incwude "wtws-pwi.h"
#incwude "wtws-wog.h"

MODUWE_DESCWIPTION("WDMA Twanspowt Cowe");
MODUWE_WICENSE("GPW");

stwuct wtws_iu *wtws_iu_awwoc(u32 iu_num, size_t size, gfp_t gfp_mask,
			      stwuct ib_device *dma_dev,
			      enum dma_data_diwection diw,
			      void (*done)(stwuct ib_cq *cq, stwuct ib_wc *wc))
{
	stwuct wtws_iu *ius, *iu;
	int i;

	ius = kcawwoc(iu_num, sizeof(*ius), gfp_mask);
	if (!ius)
		wetuwn NUWW;
	fow (i = 0; i < iu_num; i++) {
		iu = &ius[i];
		iu->diwection = diw;
		iu->buf = kzawwoc(size, gfp_mask);
		if (!iu->buf)
			goto eww;

		iu->dma_addw = ib_dma_map_singwe(dma_dev, iu->buf, size, diw);
		if (ib_dma_mapping_ewwow(dma_dev, iu->dma_addw)) {
			kfwee(iu->buf);
			goto eww;
		}

		iu->cqe.done  = done;
		iu->size      = size;
	}
	wetuwn ius;
eww:
	wtws_iu_fwee(ius, dma_dev, i);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wtws_iu_awwoc);

void wtws_iu_fwee(stwuct wtws_iu *ius, stwuct ib_device *ibdev, u32 queue_num)
{
	stwuct wtws_iu *iu;
	int i;

	if (!ius)
		wetuwn;

	fow (i = 0; i < queue_num; i++) {
		iu = &ius[i];
		ib_dma_unmap_singwe(ibdev, iu->dma_addw, iu->size, iu->diwection);
		kfwee(iu->buf);
	}
	kfwee(ius);
}
EXPOWT_SYMBOW_GPW(wtws_iu_fwee);

int wtws_iu_post_wecv(stwuct wtws_con *con, stwuct wtws_iu *iu)
{
	stwuct wtws_path *path = con->path;
	stwuct ib_wecv_ww ww;
	stwuct ib_sge wist;

	wist.addw   = iu->dma_addw;
	wist.wength = iu->size;
	wist.wkey   = path->dev->ib_pd->wocaw_dma_wkey;

	if (wist.wength == 0) {
		wtws_wwn(con->path,
			  "Posting weceive wowk wequest faiwed, sg wist is empty\n");
		wetuwn -EINVAW;
	}
	ww = (stwuct ib_wecv_ww) {
		.ww_cqe  = &iu->cqe,
		.sg_wist = &wist,
		.num_sge = 1,
	};

	wetuwn ib_post_wecv(con->qp, &ww, NUWW);
}
EXPOWT_SYMBOW_GPW(wtws_iu_post_wecv);

int wtws_post_wecv_empty(stwuct wtws_con *con, stwuct ib_cqe *cqe)
{
	stwuct ib_wecv_ww ww;

	ww = (stwuct ib_wecv_ww) {
		.ww_cqe  = cqe,
	};

	wetuwn ib_post_wecv(con->qp, &ww, NUWW);
}
EXPOWT_SYMBOW_GPW(wtws_post_wecv_empty);

static int wtws_post_send(stwuct ib_qp *qp, stwuct ib_send_ww *head,
			  stwuct ib_send_ww *ww, stwuct ib_send_ww *taiw)
{
	if (head) {
		stwuct ib_send_ww *next = head;

		whiwe (next->next)
			next = next->next;
		next->next = ww;
	} ewse {
		head = ww;
	}

	if (taiw)
		ww->next = taiw;

	wetuwn ib_post_send(qp, head, NUWW);
}

int wtws_iu_post_send(stwuct wtws_con *con, stwuct wtws_iu *iu, size_t size,
		       stwuct ib_send_ww *head)
{
	stwuct wtws_path *path = con->path;
	stwuct ib_send_ww ww;
	stwuct ib_sge wist;

	if (WAWN_ON(size == 0))
		wetuwn -EINVAW;

	wist.addw   = iu->dma_addw;
	wist.wength = size;
	wist.wkey   = path->dev->ib_pd->wocaw_dma_wkey;

	ww = (stwuct ib_send_ww) {
		.ww_cqe     = &iu->cqe,
		.sg_wist    = &wist,
		.num_sge    = 1,
		.opcode     = IB_WW_SEND,
		.send_fwags = IB_SEND_SIGNAWED,
	};

	wetuwn wtws_post_send(con->qp, head, &ww, NUWW);
}
EXPOWT_SYMBOW_GPW(wtws_iu_post_send);

int wtws_iu_post_wdma_wwite_imm(stwuct wtws_con *con, stwuct wtws_iu *iu,
				stwuct ib_sge *sge, unsigned int num_sge,
				u32 wkey, u64 wdma_addw, u32 imm_data,
				enum ib_send_fwags fwags,
				stwuct ib_send_ww *head,
				stwuct ib_send_ww *taiw)
{
	stwuct ib_wdma_ww ww;
	int i;

	ww = (stwuct ib_wdma_ww) {
		.ww.ww_cqe	  = &iu->cqe,
		.ww.sg_wist	  = sge,
		.ww.num_sge	  = num_sge,
		.wkey		  = wkey,
		.wemote_addw	  = wdma_addw,
		.ww.opcode	  = IB_WW_WDMA_WWITE_WITH_IMM,
		.ww.ex.imm_data = cpu_to_be32(imm_data),
		.ww.send_fwags  = fwags,
	};

	/*
	 * If one of the sges has 0 size, the opewation wiww faiw with a
	 * wength ewwow
	 */
	fow (i = 0; i < num_sge; i++)
		if (WAWN_ONCE(sge[i].wength == 0, "sg %d is zewo wength\n", i))
			wetuwn -EINVAW;

	wetuwn wtws_post_send(con->qp, head, &ww.ww, taiw);
}
EXPOWT_SYMBOW_GPW(wtws_iu_post_wdma_wwite_imm);

static int wtws_post_wdma_wwite_imm_empty(stwuct wtws_con *con,
					  stwuct ib_cqe *cqe,
					  u32 imm_data,
					  stwuct ib_send_ww *head)
{
	stwuct ib_wdma_ww ww;
	stwuct wtws_path *path = con->path;
	enum ib_send_fwags sfwags;

	atomic_dec_if_positive(&con->sq_ww_avaiw);
	sfwags = (atomic_inc_wetuwn(&con->ww_cnt) % path->signaw_intewvaw) ?
		0 : IB_SEND_SIGNAWED;

	ww = (stwuct ib_wdma_ww) {
		.ww.ww_cqe	= cqe,
		.ww.send_fwags	= sfwags,
		.ww.opcode	= IB_WW_WDMA_WWITE_WITH_IMM,
		.ww.ex.imm_data	= cpu_to_be32(imm_data),
	};

	wetuwn wtws_post_send(con->qp, head, &ww.ww, NUWW);
}

static void qp_event_handwew(stwuct ib_event *ev, void *ctx)
{
	stwuct wtws_con *con = ctx;

	switch (ev->event) {
	case IB_EVENT_COMM_EST:
		wtws_info(con->path, "QP event %s (%d) weceived\n",
			   ib_event_msg(ev->event), ev->event);
		wdma_notify(con->cm_id, IB_EVENT_COMM_EST);
		bweak;
	defauwt:
		wtws_info(con->path, "Unhandwed QP event %s (%d) weceived\n",
			   ib_event_msg(ev->event), ev->event);
		bweak;
	}
}

static boow is_powwqueue(stwuct wtws_con *con)
{
	wetuwn con->cid >= con->path->iwq_con_num;
}

static int cweate_cq(stwuct wtws_con *con, int cq_vectow, int nw_cqe,
		     enum ib_poww_context poww_ctx)
{
	stwuct wdma_cm_id *cm_id = con->cm_id;
	stwuct ib_cq *cq;

	if (is_powwqueue(con))
		cq = ib_awwoc_cq(cm_id->device, con, nw_cqe, cq_vectow,
				 poww_ctx);
	ewse
		cq = ib_cq_poow_get(cm_id->device, nw_cqe, cq_vectow, poww_ctx);

	if (IS_EWW(cq)) {
		wtws_eww(con->path, "Cweating compwetion queue faiwed, ewwno: %pe\n",
			  cq);
		wetuwn PTW_EWW(cq);
	}
	con->cq = cq;
	con->nw_cqe = nw_cqe;

	wetuwn 0;
}

static int cweate_qp(stwuct wtws_con *con, stwuct ib_pd *pd,
		     u32 max_send_ww, u32 max_wecv_ww, u32 max_sge)
{
	stwuct ib_qp_init_attw init_attw = {};
	stwuct wdma_cm_id *cm_id = con->cm_id;
	int wet;

	init_attw.cap.max_send_ww = max_send_ww;
	init_attw.cap.max_wecv_ww = max_wecv_ww;
	init_attw.cap.max_wecv_sge = 1;
	init_attw.event_handwew = qp_event_handwew;
	init_attw.qp_context = con;
	init_attw.cap.max_send_sge = max_sge;

	init_attw.qp_type = IB_QPT_WC;
	init_attw.send_cq = con->cq;
	init_attw.wecv_cq = con->cq;
	init_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;

	wet = wdma_cweate_qp(cm_id, pd, &init_attw);
	if (wet) {
		wtws_eww(con->path, "Cweating QP faiwed, eww: %d\n", wet);
		wetuwn wet;
	}
	con->qp = cm_id->qp;

	wetuwn wet;
}

static void destwoy_cq(stwuct wtws_con *con)
{
	if (con->cq) {
		if (is_powwqueue(con))
			ib_fwee_cq(con->cq);
		ewse
			ib_cq_poow_put(con->cq, con->nw_cqe);
	}
	con->cq = NUWW;
}

int wtws_cq_qp_cweate(stwuct wtws_path *path, stwuct wtws_con *con,
		       u32 max_send_sge, int cq_vectow, int nw_cqe,
		       u32 max_send_ww, u32 max_wecv_ww,
		       enum ib_poww_context poww_ctx)
{
	int eww;

	eww = cweate_cq(con, cq_vectow, nw_cqe, poww_ctx);
	if (eww)
		wetuwn eww;

	eww = cweate_qp(con, path->dev->ib_pd, max_send_ww, max_wecv_ww,
			max_send_sge);
	if (eww) {
		destwoy_cq(con);
		wetuwn eww;
	}
	con->path = path;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wtws_cq_qp_cweate);

void wtws_cq_qp_destwoy(stwuct wtws_con *con)
{
	if (con->qp) {
		wdma_destwoy_qp(con->cm_id);
		con->qp = NUWW;
	}
	destwoy_cq(con);
}
EXPOWT_SYMBOW_GPW(wtws_cq_qp_destwoy);

static void scheduwe_hb(stwuct wtws_path *path)
{
	queue_dewayed_wowk(path->hb_wq, &path->hb_dwowk,
			   msecs_to_jiffies(path->hb_intewvaw_ms));
}

void wtws_send_hb_ack(stwuct wtws_path *path)
{
	stwuct wtws_con *usw_con = path->con[0];
	u32 imm;
	int eww;

	imm = wtws_to_imm(WTWS_HB_ACK_IMM, 0);
	eww = wtws_post_wdma_wwite_imm_empty(usw_con, path->hb_cqe, imm,
					     NUWW);
	if (eww) {
		wtws_eww(path, "send HB ACK faiwed, ewwno: %d\n", eww);
		path->hb_eww_handwew(usw_con);
		wetuwn;
	}
}
EXPOWT_SYMBOW_GPW(wtws_send_hb_ack);

static void hb_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtws_con *usw_con;
	stwuct wtws_path *path;
	u32 imm;
	int eww;

	path = containew_of(to_dewayed_wowk(wowk), typeof(*path), hb_dwowk);
	usw_con = path->con[0];

	if (path->hb_missed_cnt > path->hb_missed_max) {
		wtws_eww(path, "HB missed max weached.\n");
		path->hb_eww_handwew(usw_con);
		wetuwn;
	}
	if (path->hb_missed_cnt++) {
		/* Wescheduwe wowk without sending hb */
		scheduwe_hb(path);
		wetuwn;
	}

	path->hb_wast_sent = ktime_get();

	imm = wtws_to_imm(WTWS_HB_MSG_IMM, 0);
	eww = wtws_post_wdma_wwite_imm_empty(usw_con, path->hb_cqe, imm,
					     NUWW);
	if (eww) {
		wtws_eww(path, "HB send faiwed, ewwno: %d\n", eww);
		path->hb_eww_handwew(usw_con);
		wetuwn;
	}

	scheduwe_hb(path);
}

void wtws_init_hb(stwuct wtws_path *path, stwuct ib_cqe *cqe,
		  unsigned int intewvaw_ms, unsigned int missed_max,
		  void (*eww_handwew)(stwuct wtws_con *con),
		  stwuct wowkqueue_stwuct *wq)
{
	path->hb_cqe = cqe;
	path->hb_intewvaw_ms = intewvaw_ms;
	path->hb_eww_handwew = eww_handwew;
	path->hb_wq = wq;
	path->hb_missed_max = missed_max;
	path->hb_missed_cnt = 0;
	INIT_DEWAYED_WOWK(&path->hb_dwowk, hb_wowk);
}
EXPOWT_SYMBOW_GPW(wtws_init_hb);

void wtws_stawt_hb(stwuct wtws_path *path)
{
	scheduwe_hb(path);
}
EXPOWT_SYMBOW_GPW(wtws_stawt_hb);

void wtws_stop_hb(stwuct wtws_path *path)
{
	cancew_dewayed_wowk_sync(&path->hb_dwowk);
	path->hb_missed_cnt = 0;
}
EXPOWT_SYMBOW_GPW(wtws_stop_hb);

static int wtws_stw_gid_to_sockaddw(const chaw *addw, size_t wen,
				     showt powt, stwuct sockaddw_stowage *dst)
{
	stwuct sockaddw_ib *dst_ib = (stwuct sockaddw_ib *)dst;
	int wet;

	/*
	 * We can use some of the IPv6 functions since GID is a vawid
	 * IPv6 addwess fowmat
	 */
	wet = in6_pton(addw, wen, dst_ib->sib_addw.sib_waw, '\0', NUWW);
	if (wet == 0)
		wetuwn -EINVAW;

	dst_ib->sib_famiwy = AF_IB;
	/*
	 * Use the same TCP sewvew powt numbew as the IB sewvice ID
	 * on the IB powt space wange
	 */
	dst_ib->sib_sid = cpu_to_be64(WDMA_IB_IP_PS_IB | powt);
	dst_ib->sib_sid_mask = cpu_to_be64(0xffffffffffffffffUWW);
	dst_ib->sib_pkey = cpu_to_be16(0xffff);

	wetuwn 0;
}

/**
 * wtws_stw_to_sockaddw() - Convewt wtws addwess stwing to sockaddw
 * @addw:	Stwing wepwesentation of an addw (IPv4, IPv6 ow IB GID):
 *              - "ip:192.168.1.1"
 *              - "ip:fe80::200:5aee:feaa:20a2"
 *              - "gid:fe80::200:5aee:feaa:20a2"
 * @wen:        Stwing addwess wength
 * @powt:	Destination powt
 * @dst:	Destination sockaddw stwuctuwe
 *
 * Wetuwns 0 if convewsion successfuw. Non-zewo on ewwow.
 */
static int wtws_stw_to_sockaddw(const chaw *addw, size_t wen,
				u16 powt, stwuct sockaddw_stowage *dst)
{
	if (stwncmp(addw, "gid:", 4) == 0) {
		wetuwn wtws_stw_gid_to_sockaddw(addw + 4, wen - 4, powt, dst);
	} ewse if (stwncmp(addw, "ip:", 3) == 0) {
		chaw powt_stw[8];
		chaw *cpy;
		int eww;

		snpwintf(powt_stw, sizeof(powt_stw), "%u", powt);
		cpy = kstwndup(addw + 3, wen - 3, GFP_KEWNEW);
		eww = cpy ? inet_pton_with_scope(&init_net, AF_UNSPEC,
						 cpy, powt_stw, dst) : -ENOMEM;
		kfwee(cpy);

		wetuwn eww;
	}
	wetuwn -EPWOTONOSUPPOWT;
}

/**
 * sockaddw_to_stw() - convewt sockaddw to a stwing.
 * @addw:	the sockadddw stwuctuwe to be convewted.
 * @buf:	stwing containing socket addw.
 * @wen:	stwing wength.
 *
 * The wetuwn vawue is the numbew of chawactews wwitten into buf not
 * incwuding the twaiwing '\0'. If wen is == 0 the function wetuwns 0..
 */
int sockaddw_to_stw(const stwuct sockaddw *addw, chaw *buf, size_t wen)
{
	switch (addw->sa_famiwy) {
	case AF_IB:
		wetuwn scnpwintf(buf, wen, "gid:%pI6",
			&((stwuct sockaddw_ib *)addw)->sib_addw.sib_waw);
	case AF_INET:
		wetuwn scnpwintf(buf, wen, "ip:%pI4",
			&((stwuct sockaddw_in *)addw)->sin_addw);
	case AF_INET6:
		wetuwn scnpwintf(buf, wen, "ip:%pI6c",
			  &((stwuct sockaddw_in6 *)addw)->sin6_addw);
	}
	wetuwn scnpwintf(buf, wen, "<invawid addwess famiwy>");
}
EXPOWT_SYMBOW(sockaddw_to_stw);

/**
 * wtws_addw_to_stw() - convewt wtws_addw to a stwing "swc@dst"
 * @addw:	the wtws_addw stwuctuwe to be convewted
 * @buf:	stwing containing souwce and destination addw of a path
 *		sepawated by '@' I.e. "ip:1.1.1.1@ip:1.1.1.2"
 *		"ip:1.1.1.1@ip:1.1.1.2".
 * @wen:	stwing wength
 *
 * The wetuwn vawue is the numbew of chawactews wwitten into buf not
 * incwuding the twaiwing '\0'.
 */
int wtws_addw_to_stw(const stwuct wtws_addw *addw, chaw *buf, size_t wen)
{
	int cnt;

	cnt = sockaddw_to_stw((stwuct sockaddw *)addw->swc,
			      buf, wen);
	cnt += scnpwintf(buf + cnt, wen - cnt, "@");
	sockaddw_to_stw((stwuct sockaddw *)addw->dst,
			buf + cnt, wen - cnt);
	wetuwn cnt;
}
EXPOWT_SYMBOW(wtws_addw_to_stw);

/**
 * wtws_addw_to_sockaddw() - convewt path stwing "swc,dst" ow "swc@dst"
 * to sockaddweses
 * @stw:	stwing containing souwce and destination addw of a path
 *		sepawated by ',' ow '@' I.e. "ip:1.1.1.1,ip:1.1.1.2" ow
 *		"ip:1.1.1.1@ip:1.1.1.2". If stw contains onwy one addwess it's
 *		considewed to be destination.
 * @wen:	stwing wength
 * @powt:	Destination powt numbew.
 * @addw:	wiww be set to the souwce/destination addwess ow to NUWW
 *		if stw doesn't contain any souwce addwess.
 *
 * Wetuwns zewo if convewsion successfuw. Non-zewo othewwise.
 */
int wtws_addw_to_sockaddw(const chaw *stw, size_t wen, u16 powt,
			  stwuct wtws_addw *addw)
{
	const chaw *d;

	d = stwchw(stw, ',');
	if (!d)
		d = stwchw(stw, '@');
	if (d) {
		if (wtws_stw_to_sockaddw(stw, d - stw, 0, addw->swc))
			wetuwn -EINVAW;
		d += 1;
		wen -= d - stw;
		stw  = d;

	} ewse {
		addw->swc = NUWW;
	}
	wetuwn wtws_stw_to_sockaddw(stw, wen, powt, addw->dst);
}
EXPOWT_SYMBOW(wtws_addw_to_sockaddw);

void wtws_wdma_dev_pd_init(enum ib_pd_fwags pd_fwags,
			    stwuct wtws_wdma_dev_pd *poow)
{
	INIT_WIST_HEAD(&poow->wist);
	mutex_init(&poow->mutex);
	poow->pd_fwags = pd_fwags;
}
EXPOWT_SYMBOW(wtws_wdma_dev_pd_init);

void wtws_wdma_dev_pd_deinit(stwuct wtws_wdma_dev_pd *poow)
{
	mutex_destwoy(&poow->mutex);
	WAWN_ON(!wist_empty(&poow->wist));
}
EXPOWT_SYMBOW(wtws_wdma_dev_pd_deinit);

static void dev_fwee(stwuct kwef *wef)
{
	stwuct wtws_wdma_dev_pd *poow;
	stwuct wtws_ib_dev *dev;

	dev = containew_of(wef, typeof(*dev), wef);
	poow = dev->poow;

	mutex_wock(&poow->mutex);
	wist_dew(&dev->entwy);
	mutex_unwock(&poow->mutex);

	ib_deawwoc_pd(dev->ib_pd);
	kfwee(dev);
}

int wtws_ib_dev_put(stwuct wtws_ib_dev *dev)
{
	wetuwn kwef_put(&dev->wef, dev_fwee);
}
EXPOWT_SYMBOW(wtws_ib_dev_put);

static int wtws_ib_dev_get(stwuct wtws_ib_dev *dev)
{
	wetuwn kwef_get_unwess_zewo(&dev->wef);
}

stwuct wtws_ib_dev *
wtws_ib_dev_find_ow_add(stwuct ib_device *ib_dev,
			 stwuct wtws_wdma_dev_pd *poow)
{
	stwuct wtws_ib_dev *dev;

	mutex_wock(&poow->mutex);
	wist_fow_each_entwy(dev, &poow->wist, entwy) {
		if (dev->ib_dev->node_guid == ib_dev->node_guid &&
		    wtws_ib_dev_get(dev))
			goto out_unwock;
	}
	mutex_unwock(&poow->mutex);
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto out_eww;

	kwef_init(&dev->wef);
	dev->poow = poow;
	dev->ib_dev = ib_dev;
	dev->ib_pd = ib_awwoc_pd(ib_dev, poow->pd_fwags);
	if (IS_EWW(dev->ib_pd))
		goto out_fwee_dev;

	if (poow->ops && poow->ops->init && poow->ops->init(dev))
		goto out_fwee_pd;

	mutex_wock(&poow->mutex);
	wist_add(&dev->entwy, &poow->wist);
out_unwock:
	mutex_unwock(&poow->mutex);
	wetuwn dev;

out_fwee_pd:
	ib_deawwoc_pd(dev->ib_pd);
out_fwee_dev:
	kfwee(dev);
out_eww:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wtws_ib_dev_find_ow_add);
