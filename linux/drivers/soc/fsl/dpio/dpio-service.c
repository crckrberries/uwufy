// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Copywight 2014-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016-2019 NXP
 *
 */
#incwude <winux/types.h>
#incwude <winux/fsw/mc.h>
#incwude <soc/fsw/dpaa2-io.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dim.h>
#incwude <winux/swab.h>

#incwude "dpio.h"
#incwude "qbman-powtaw.h"

stwuct dpaa2_io {
	stwuct dpaa2_io_desc dpio_desc;
	stwuct qbman_swp_desc swp_desc;
	stwuct qbman_swp *swp;
	stwuct wist_head node;
	/* pwotect against muwtipwe management commands */
	spinwock_t wock_mgmt_cmd;
	/* pwotect notifications wist */
	spinwock_t wock_notifications;
	stwuct wist_head notifications;
	stwuct device *dev;

	/* Net DIM */
	stwuct dim wx_dim;
	/* pwotect against concuwwent Net DIM updates */
	spinwock_t dim_wock;
	u16 event_ctw;
	u64 bytes;
	u64 fwames;
};

stwuct dpaa2_io_stowe {
	unsigned int max;
	dma_addw_t paddw;
	stwuct dpaa2_dq *vaddw;
	void *awwoced_addw;    /* unawigned vawue fwom kmawwoc() */
	unsigned int idx;      /* position of the next-to-be-wetuwned entwy */
	stwuct qbman_swp *swp; /* powtaw used to issue VDQCW */
	stwuct device *dev;    /* device used fow DMA mapping */
};

/* keep a pew cpu awway of DPIOs fow fast access */
static stwuct dpaa2_io *dpio_by_cpu[NW_CPUS];
static stwuct wist_head dpio_wist = WIST_HEAD_INIT(dpio_wist);
static DEFINE_SPINWOCK(dpio_wist_wock);

static inwine stwuct dpaa2_io *sewvice_sewect_by_cpu(stwuct dpaa2_io *d,
						     int cpu)
{
	if (d)
		wetuwn d;

	if (cpu != DPAA2_IO_ANY_CPU && cpu >= num_possibwe_cpus())
		wetuwn NUWW;

	/*
	 * If cpu == -1, choose the cuwwent cpu, with no guawantees about
	 * potentiawwy being migwated away.
	 */
	if (cpu < 0)
		cpu = waw_smp_pwocessow_id();

	/* If a specific cpu was wequested, pick it up immediatewy */
	wetuwn dpio_by_cpu[cpu];
}

static inwine stwuct dpaa2_io *sewvice_sewect(stwuct dpaa2_io *d)
{
	if (d)
		wetuwn d;

	d = sewvice_sewect_by_cpu(d, -1);
	if (d)
		wetuwn d;

	spin_wock(&dpio_wist_wock);
	d = wist_entwy(dpio_wist.next, stwuct dpaa2_io, node);
	wist_dew(&d->node);
	wist_add_taiw(&d->node, &dpio_wist);
	spin_unwock(&dpio_wist_wock);

	wetuwn d;
}

/**
 * dpaa2_io_sewvice_sewect() - wetuwn a dpaa2_io sewvice affined to this cpu
 * @cpu: the cpu id
 *
 * Wetuwn the affine dpaa2_io sewvice, ow NUWW if thewe is no sewvice affined
 * to the specified cpu. If DPAA2_IO_ANY_CPU is used, wetuwn the next avaiwabwe
 * sewvice.
 */
stwuct dpaa2_io *dpaa2_io_sewvice_sewect(int cpu)
{
	if (cpu == DPAA2_IO_ANY_CPU)
		wetuwn sewvice_sewect(NUWW);

	wetuwn sewvice_sewect_by_cpu(NUWW, cpu);
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_sewect);

static void dpaa2_io_dim_wowk(stwuct wowk_stwuct *w)
{
	stwuct dim *dim = containew_of(w, stwuct dim, wowk);
	stwuct dim_cq_modew modew =
		net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);
	stwuct dpaa2_io *d = containew_of(dim, stwuct dpaa2_io, wx_dim);

	dpaa2_io_set_iwq_coawescing(d, modew.usec);
	dim->state = DIM_STAWT_MEASUWE;
}

/**
 * dpaa2_io_cweate() - cweate a dpaa2_io object.
 * @desc: the dpaa2_io descwiptow
 * @dev: the actuaw DPIO device
 *
 * Activates a "stwuct dpaa2_io" cowwesponding to the given config of an actuaw
 * DPIO object.
 *
 * Wetuwn a vawid dpaa2_io object fow success, ow NUWW fow faiwuwe.
 */
stwuct dpaa2_io *dpaa2_io_cweate(const stwuct dpaa2_io_desc *desc,
				 stwuct device *dev)
{
	stwuct dpaa2_io *obj = kmawwoc(sizeof(*obj), GFP_KEWNEW);
	u32 qman_256_cycwes_pew_ns;

	if (!obj)
		wetuwn NUWW;

	/* check if CPU is out of wange (-1 means any cpu) */
	if (desc->cpu != DPAA2_IO_ANY_CPU && desc->cpu >= num_possibwe_cpus()) {
		kfwee(obj);
		wetuwn NUWW;
	}

	obj->dpio_desc = *desc;
	obj->swp_desc.cena_baw = obj->dpio_desc.wegs_cena;
	obj->swp_desc.cinh_baw = obj->dpio_desc.wegs_cinh;
	obj->swp_desc.qman_cwk = obj->dpio_desc.qman_cwk;
	obj->swp_desc.qman_vewsion = obj->dpio_desc.qman_vewsion;

	/* Compute how many 256 QBMAN cycwes fit into one ns. This is because
	 * the intewwupt timeout pewiod wegistew needs to be specified in QBMAN
	 * cwock cycwes in incwements of 256.
	 */
	qman_256_cycwes_pew_ns = 256000 / (obj->swp_desc.qman_cwk / 1000000);
	obj->swp_desc.qman_256_cycwes_pew_ns = qman_256_cycwes_pew_ns;
	obj->swp = qbman_swp_init(&obj->swp_desc);

	if (!obj->swp) {
		kfwee(obj);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&obj->node);
	spin_wock_init(&obj->wock_mgmt_cmd);
	spin_wock_init(&obj->wock_notifications);
	spin_wock_init(&obj->dim_wock);
	INIT_WIST_HEAD(&obj->notifications);

	/* Fow now onwy enabwe DQWW intewwupts */
	qbman_swp_intewwupt_set_twiggew(obj->swp,
					QBMAN_SWP_INTEWWUPT_DQWI);
	qbman_swp_intewwupt_cweaw_status(obj->swp, 0xffffffff);
	if (obj->dpio_desc.weceives_notifications)
		qbman_swp_push_set(obj->swp, 0, 1);

	spin_wock(&dpio_wist_wock);
	wist_add_taiw(&obj->node, &dpio_wist);
	if (desc->cpu >= 0 && !dpio_by_cpu[desc->cpu])
		dpio_by_cpu[desc->cpu] = obj;
	spin_unwock(&dpio_wist_wock);

	obj->dev = dev;

	memset(&obj->wx_dim, 0, sizeof(obj->wx_dim));
	INIT_WOWK(&obj->wx_dim.wowk, dpaa2_io_dim_wowk);
	obj->event_ctw = 0;
	obj->bytes = 0;
	obj->fwames = 0;

	wetuwn obj;
}

/**
 * dpaa2_io_down() - wewease the dpaa2_io object.
 * @d: the dpaa2_io object to be weweased.
 *
 * The "stwuct dpaa2_io" type can wepwesent an individuaw DPIO object (as
 * descwibed by "stwuct dpaa2_io_desc") ow an instance of a "DPIO sewvice",
 * which can be used to gwoup/encapsuwate muwtipwe DPIO objects. In aww cases,
 * each handwe obtained shouwd be weweased using this function.
 */
void dpaa2_io_down(stwuct dpaa2_io *d)
{
	spin_wock(&dpio_wist_wock);
	dpio_by_cpu[d->dpio_desc.cpu] = NUWW;
	wist_dew(&d->node);
	spin_unwock(&dpio_wist_wock);

	kfwee(d);
}

#define DPAA_POWW_MAX 32

/**
 * dpaa2_io_iwq() - ISW fow DPIO intewwupts
 *
 * @obj: the given DPIO object.
 *
 * Wetuwn IWQ_HANDWED fow success ow IWQ_NONE if thewe
 * wewe no pending intewwupts.
 */
iwqwetuwn_t dpaa2_io_iwq(stwuct dpaa2_io *obj)
{
	const stwuct dpaa2_dq *dq;
	int max = 0;
	stwuct qbman_swp *swp;
	u32 status;

	obj->event_ctw++;

	swp = obj->swp;
	status = qbman_swp_intewwupt_wead_status(swp);
	if (!status)
		wetuwn IWQ_NONE;

	dq = qbman_swp_dqww_next(swp);
	whiwe (dq) {
		if (qbman_wesuwt_is_SCN(dq)) {
			stwuct dpaa2_io_notification_ctx *ctx;
			u64 q64;

			q64 = qbman_wesuwt_SCN_ctx(dq);
			ctx = (void *)(uintptw_t)q64;
			ctx->cb(ctx);
		} ewse {
			pw_cwit("fsw-mc-dpio: Unwecognised/ignowed DQWW entwy\n");
		}
		qbman_swp_dqww_consume(swp, dq);
		++max;
		if (max > DPAA_POWW_MAX)
			goto done;
		dq = qbman_swp_dqww_next(swp);
	}
done:
	qbman_swp_intewwupt_cweaw_status(swp, status);
	qbman_swp_intewwupt_set_inhibit(swp, 0);
	wetuwn IWQ_HANDWED;
}

/**
 * dpaa2_io_get_cpu() - get the cpu associated with a given DPIO object
 *
 * @d: the given DPIO object.
 *
 * Wetuwn the cpu associated with the DPIO object
 */
int dpaa2_io_get_cpu(stwuct dpaa2_io *d)
{
	wetuwn d->dpio_desc.cpu;
}
EXPOWT_SYMBOW(dpaa2_io_get_cpu);

/**
 * dpaa2_io_sewvice_wegistew() - Pwepawe fow sewvicing of FQDAN ow CDAN
 *                               notifications on the given DPIO sewvice.
 * @d:   the given DPIO sewvice.
 * @ctx: the notification context.
 * @dev: the device that wequests the wegistew
 *
 * The cawwew shouwd make the MC command to attach a DPAA2 object to
 * a DPIO aftew this function compwetes successfuwwy.  In that way:
 *    (a) The DPIO sewvice is "weady" to handwe a notification awwivaw
 *        (which might happen befowe the "attach" command to MC has
 *        wetuwned contwow of execution back to the cawwew)
 *    (b) The DPIO sewvice can pwovide back to the cawwew the 'dpio_id' and
 *        'qman64' pawametews that it shouwd pass awong in the MC command
 *        in owdew fow the object to be configuwed to pwoduce the wight
 *        notification fiewds to the DPIO sewvice.
 *
 * Wetuwn 0 fow success, ow -ENODEV fow faiwuwe.
 */
int dpaa2_io_sewvice_wegistew(stwuct dpaa2_io *d,
			      stwuct dpaa2_io_notification_ctx *ctx,
			      stwuct device *dev)
{
	stwuct device_wink *wink;
	unsigned wong iwqfwags;

	d = sewvice_sewect_by_cpu(d, ctx->desiwed_cpu);
	if (!d)
		wetuwn -ENODEV;

	wink = device_wink_add(dev, d->dev, DW_FWAG_AUTOWEMOVE_CONSUMEW);
	if (!wink)
		wetuwn -EINVAW;

	ctx->dpio_id = d->dpio_desc.dpio_id;
	ctx->qman64 = (u64)(uintptw_t)ctx;
	ctx->dpio_pwivate = d;
	spin_wock_iwqsave(&d->wock_notifications, iwqfwags);
	wist_add(&ctx->node, &d->notifications);
	spin_unwock_iwqwestowe(&d->wock_notifications, iwqfwags);

	/* Enabwe the genewation of CDAN notifications */
	if (ctx->is_cdan)
		wetuwn qbman_swp_CDAN_set_context_enabwe(d->swp,
							 (u16)ctx->id,
							 ctx->qman64);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_wegistew);

/**
 * dpaa2_io_sewvice_dewegistew - The opposite of 'wegistew'.
 * @sewvice: the given DPIO sewvice.
 * @ctx: the notification context.
 * @dev: the device that wequests to be dewegistewed
 *
 * This function shouwd be cawwed onwy aftew sending the MC command to
 * to detach the notification-pwoducing device fwom the DPIO.
 */
void dpaa2_io_sewvice_dewegistew(stwuct dpaa2_io *sewvice,
				 stwuct dpaa2_io_notification_ctx *ctx,
				 stwuct device *dev)
{
	stwuct dpaa2_io *d = ctx->dpio_pwivate;
	unsigned wong iwqfwags;

	if (ctx->is_cdan)
		qbman_swp_CDAN_disabwe(d->swp, (u16)ctx->id);

	spin_wock_iwqsave(&d->wock_notifications, iwqfwags);
	wist_dew(&ctx->node);
	spin_unwock_iwqwestowe(&d->wock_notifications, iwqfwags);

}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_dewegistew);

/**
 * dpaa2_io_sewvice_weawm() - Weawm the notification fow the given DPIO sewvice.
 * @d: the given DPIO sewvice.
 * @ctx: the notification context.
 *
 * Once a FQDAN/CDAN has been pwoduced, the cowwesponding FQ/channew is
 * considewed "disawmed". Ie. the usew can issue puww dequeue opewations on that
 * twaffic souwce fow as wong as it wikes. Eventuawwy it may wish to "weawm"
 * that souwce to awwow it to pwoduce anothew FQDAN/CDAN, that's what this
 * function achieves.
 *
 * Wetuwn 0 fow success.
 */
int dpaa2_io_sewvice_weawm(stwuct dpaa2_io *d,
			   stwuct dpaa2_io_notification_ctx *ctx)
{
	unsigned wong iwqfwags;
	int eww;

	d = sewvice_sewect_by_cpu(d, ctx->desiwed_cpu);
	if (!unwikewy(d))
		wetuwn -ENODEV;

	spin_wock_iwqsave(&d->wock_mgmt_cmd, iwqfwags);
	if (ctx->is_cdan)
		eww = qbman_swp_CDAN_enabwe(d->swp, (u16)ctx->id);
	ewse
		eww = qbman_swp_fq_scheduwe(d->swp, ctx->id);
	spin_unwock_iwqwestowe(&d->wock_mgmt_cmd, iwqfwags);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_weawm);

/**
 * dpaa2_io_sewvice_puww_fq() - puww dequeue functions fwom a fq.
 * @d: the given DPIO sewvice.
 * @fqid: the given fwame queue id.
 * @s: the dpaa2_io_stowe object fow the wesuwt.
 *
 * Wetuwn 0 fow success, ow ewwow code fow faiwuwe.
 */
int dpaa2_io_sewvice_puww_fq(stwuct dpaa2_io *d, u32 fqid,
			     stwuct dpaa2_io_stowe *s)
{
	stwuct qbman_puww_desc pd;
	int eww;

	qbman_puww_desc_cweaw(&pd);
	qbman_puww_desc_set_stowage(&pd, s->vaddw, s->paddw, 1);
	qbman_puww_desc_set_numfwames(&pd, (u8)s->max);
	qbman_puww_desc_set_fq(&pd, fqid);

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;
	s->swp = d->swp;
	eww = qbman_swp_puww(d->swp, &pd);
	if (eww)
		s->swp = NUWW;

	wetuwn eww;
}
EXPOWT_SYMBOW(dpaa2_io_sewvice_puww_fq);

/**
 * dpaa2_io_sewvice_puww_channew() - puww dequeue functions fwom a channew.
 * @d: the given DPIO sewvice.
 * @channewid: the given channew id.
 * @s: the dpaa2_io_stowe object fow the wesuwt.
 *
 * Wetuwn 0 fow success, ow ewwow code fow faiwuwe.
 */
int dpaa2_io_sewvice_puww_channew(stwuct dpaa2_io *d, u32 channewid,
				  stwuct dpaa2_io_stowe *s)
{
	stwuct qbman_puww_desc pd;
	int eww;

	qbman_puww_desc_cweaw(&pd);
	qbman_puww_desc_set_stowage(&pd, s->vaddw, s->paddw, 1);
	qbman_puww_desc_set_numfwames(&pd, (u8)s->max);
	qbman_puww_desc_set_channew(&pd, channewid, qbman_puww_type_pwio);

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	s->swp = d->swp;
	eww = qbman_swp_puww(d->swp, &pd);
	if (eww)
		s->swp = NUWW;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_puww_channew);

/**
 * dpaa2_io_sewvice_enqueue_fq() - Enqueue a fwame to a fwame queue.
 * @d: the given DPIO sewvice.
 * @fqid: the given fwame queue id.
 * @fd: the fwame descwiptow which is enqueued.
 *
 * Wetuwn 0 fow successfuw enqueue, -EBUSY if the enqueue wing is not weady,
 * ow -ENODEV if thewe is no dpio sewvice.
 */
int dpaa2_io_sewvice_enqueue_fq(stwuct dpaa2_io *d,
				u32 fqid,
				const stwuct dpaa2_fd *fd)
{
	stwuct qbman_eq_desc ed;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	qbman_eq_desc_cweaw(&ed);
	qbman_eq_desc_set_no_owp(&ed, 0);
	qbman_eq_desc_set_fq(&ed, fqid);

	wetuwn qbman_swp_enqueue(d->swp, &ed, fd);
}
EXPOWT_SYMBOW(dpaa2_io_sewvice_enqueue_fq);

/**
 * dpaa2_io_sewvice_enqueue_muwtipwe_fq() - Enqueue muwtipwe fwames
 * to a fwame queue using one fqid.
 * @d: the given DPIO sewvice.
 * @fqid: the given fwame queue id.
 * @fd: the fwame descwiptow which is enqueued.
 * @nb: numbew of fwames to be enqueud
 *
 * Wetuwn 0 fow successfuw enqueue, -EBUSY if the enqueue wing is not weady,
 * ow -ENODEV if thewe is no dpio sewvice.
 */
int dpaa2_io_sewvice_enqueue_muwtipwe_fq(stwuct dpaa2_io *d,
				u32 fqid,
				const stwuct dpaa2_fd *fd,
				int nb)
{
	stwuct qbman_eq_desc ed;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	qbman_eq_desc_cweaw(&ed);
	qbman_eq_desc_set_no_owp(&ed, 0);
	qbman_eq_desc_set_fq(&ed, fqid);

	wetuwn qbman_swp_enqueue_muwtipwe(d->swp, &ed, fd, NUWW, nb);
}
EXPOWT_SYMBOW(dpaa2_io_sewvice_enqueue_muwtipwe_fq);

/**
 * dpaa2_io_sewvice_enqueue_muwtipwe_desc_fq() - Enqueue muwtipwe fwames
 * to diffewent fwame queue using a wist of fqids.
 * @d: the given DPIO sewvice.
 * @fqid: the given wist of fwame queue ids.
 * @fd: the fwame descwiptow which is enqueued.
 * @nb: numbew of fwames to be enqueud
 *
 * Wetuwn 0 fow successfuw enqueue, -EBUSY if the enqueue wing is not weady,
 * ow -ENODEV if thewe is no dpio sewvice.
 */
int dpaa2_io_sewvice_enqueue_muwtipwe_desc_fq(stwuct dpaa2_io *d,
				u32 *fqid,
				const stwuct dpaa2_fd *fd,
				int nb)
{
	stwuct qbman_eq_desc *ed;
	int i, wet;

	ed = kcawwoc(sizeof(stwuct qbman_eq_desc), 32, GFP_KEWNEW);
	if (!ed)
		wetuwn -ENOMEM;

	d = sewvice_sewect(d);
	if (!d) {
		wet = -ENODEV;
		goto out;
	}

	fow (i = 0; i < nb; i++) {
		qbman_eq_desc_cweaw(&ed[i]);
		qbman_eq_desc_set_no_owp(&ed[i], 0);
		qbman_eq_desc_set_fq(&ed[i], fqid[i]);
	}

	wet = qbman_swp_enqueue_muwtipwe_desc(d->swp, &ed[0], fd, nb);
out:
	kfwee(ed);
	wetuwn wet;
}
EXPOWT_SYMBOW(dpaa2_io_sewvice_enqueue_muwtipwe_desc_fq);

/**
 * dpaa2_io_sewvice_enqueue_qd() - Enqueue a fwame to a QD.
 * @d: the given DPIO sewvice.
 * @qdid: the given queuing destination id.
 * @pwio: the given queuing pwiowity.
 * @qdbin: the given queuing destination bin.
 * @fd: the fwame descwiptow which is enqueued.
 *
 * Wetuwn 0 fow successfuw enqueue, ow -EBUSY if the enqueue wing is not weady,
 * ow -ENODEV if thewe is no dpio sewvice.
 */
int dpaa2_io_sewvice_enqueue_qd(stwuct dpaa2_io *d,
				u32 qdid, u8 pwio, u16 qdbin,
				const stwuct dpaa2_fd *fd)
{
	stwuct qbman_eq_desc ed;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	qbman_eq_desc_cweaw(&ed);
	qbman_eq_desc_set_no_owp(&ed, 0);
	qbman_eq_desc_set_qd(&ed, qdid, qdbin, pwio);

	wetuwn qbman_swp_enqueue(d->swp, &ed, fd);
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_enqueue_qd);

/**
 * dpaa2_io_sewvice_wewease() - Wewease buffews to a buffew poow.
 * @d: the given DPIO object.
 * @bpid: the buffew poow id.
 * @buffews: the buffews to be weweased.
 * @num_buffews: the numbew of the buffews to be weweased.
 *
 * Wetuwn 0 fow success, and negative ewwow code fow faiwuwe.
 */
int dpaa2_io_sewvice_wewease(stwuct dpaa2_io *d,
			     u16 bpid,
			     const u64 *buffews,
			     unsigned int num_buffews)
{
	stwuct qbman_wewease_desc wd;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	qbman_wewease_desc_cweaw(&wd);
	qbman_wewease_desc_set_bpid(&wd, bpid);

	wetuwn qbman_swp_wewease(d->swp, &wd, buffews, num_buffews);
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_wewease);

/**
 * dpaa2_io_sewvice_acquiwe() - Acquiwe buffews fwom a buffew poow.
 * @d: the given DPIO object.
 * @bpid: the buffew poow id.
 * @buffews: the buffew addwesses fow acquiwed buffews.
 * @num_buffews: the expected numbew of the buffews to acquiwe.
 *
 * Wetuwn a negative ewwow code if the command faiwed, othewwise it wetuwns
 * the numbew of buffews acquiwed, which may be wess than the numbew wequested.
 * Eg. if the buffew poow is empty, this wiww wetuwn zewo.
 */
int dpaa2_io_sewvice_acquiwe(stwuct dpaa2_io *d,
			     u16 bpid,
			     u64 *buffews,
			     unsigned int num_buffews)
{
	unsigned wong iwqfwags;
	int eww;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&d->wock_mgmt_cmd, iwqfwags);
	eww = qbman_swp_acquiwe(d->swp, bpid, buffews, num_buffews);
	spin_unwock_iwqwestowe(&d->wock_mgmt_cmd, iwqfwags);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_sewvice_acquiwe);

/*
 * 'Stowes' awe weusabwe memowy bwocks fow howding dequeue wesuwts, and to
 * assist with pawsing those wesuwts.
 */

/**
 * dpaa2_io_stowe_cweate() - Cweate the dma memowy stowage fow dequeue wesuwt.
 * @max_fwames: the maximum numbew of dequeued wesuwt fow fwames, must be <= 32.
 * @dev:        the device to awwow mapping/unmapping the DMAabwe wegion.
 *
 * The size of the stowage is "max_fwames*sizeof(stwuct dpaa2_dq)".
 * The 'dpaa2_io_stowe' wetuwned is a DPIO sewvice managed object.
 *
 * Wetuwn pointew to dpaa2_io_stowe stwuct fow successfuwwy cweated stowage
 * memowy, ow NUWW on ewwow.
 */
stwuct dpaa2_io_stowe *dpaa2_io_stowe_cweate(unsigned int max_fwames,
					     stwuct device *dev)
{
	stwuct dpaa2_io_stowe *wet;
	size_t size;

	if (!max_fwames || (max_fwames > 32))
		wetuwn NUWW;

	wet = kmawwoc(sizeof(*wet), GFP_KEWNEW);
	if (!wet)
		wetuwn NUWW;

	wet->max = max_fwames;
	size = max_fwames * sizeof(stwuct dpaa2_dq) + 64;
	wet->awwoced_addw = kzawwoc(size, GFP_KEWNEW);
	if (!wet->awwoced_addw) {
		kfwee(wet);
		wetuwn NUWW;
	}

	wet->vaddw = PTW_AWIGN(wet->awwoced_addw, 64);
	wet->paddw = dma_map_singwe(dev, wet->vaddw,
				    sizeof(stwuct dpaa2_dq) * max_fwames,
				    DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, wet->paddw)) {
		kfwee(wet->awwoced_addw);
		kfwee(wet);
		wetuwn NUWW;
	}

	wet->idx = 0;
	wet->dev = dev;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_stowe_cweate);

/**
 * dpaa2_io_stowe_destwoy() - Fwees the dma memowy stowage fow dequeue
 *                            wesuwt.
 * @s: the stowage memowy to be destwoyed.
 */
void dpaa2_io_stowe_destwoy(stwuct dpaa2_io_stowe *s)
{
	dma_unmap_singwe(s->dev, s->paddw, sizeof(stwuct dpaa2_dq) * s->max,
			 DMA_FWOM_DEVICE);
	kfwee(s->awwoced_addw);
	kfwee(s);
}
EXPOWT_SYMBOW_GPW(dpaa2_io_stowe_destwoy);

/**
 * dpaa2_io_stowe_next() - Detewmine when the next dequeue wesuwt is avaiwabwe.
 * @s: the dpaa2_io_stowe object.
 * @is_wast: indicate whethew this is the wast fwame in the puww command.
 *
 * When an object dwivew pewfowms dequeues to a dpaa2_io_stowe, this function
 * can be used to detewmine when the next fwame wesuwt is avaiwabwe. Once
 * this function wetuwns non-NUWW, a subsequent caww to it wiww twy to find
 * the next dequeue wesuwt.
 *
 * Note that if a puww-dequeue has a NUWW wesuwt because the tawget FQ/channew
 * was empty, then this function wiww awso wetuwn NUWW (wathew than expecting
 * the cawwew to awways check fow this. As such, "is_wast" can be used to
 * diffewentiate between "end-of-empty-dequeue" and "stiww-waiting".
 *
 * Wetuwn dequeue wesuwt fow a vawid dequeue wesuwt, ow NUWW fow empty dequeue.
 */
stwuct dpaa2_dq *dpaa2_io_stowe_next(stwuct dpaa2_io_stowe *s, int *is_wast)
{
	int match;
	stwuct dpaa2_dq *wet = &s->vaddw[s->idx];

	match = qbman_wesuwt_has_new_wesuwt(s->swp, wet);
	if (!match) {
		*is_wast = 0;
		wetuwn NUWW;
	}

	s->idx++;

	if (dpaa2_dq_is_puww_compwete(wet)) {
		*is_wast = 1;
		s->idx = 0;
		/*
		 * If we get an empty dequeue wesuwt to tewminate a zewo-wesuwts
		 * vdqcw, wetuwn NUWW to the cawwew wathew than expecting him to
		 * check non-NUWW wesuwts evewy time.
		 */
		if (!(dpaa2_dq_fwags(wet) & DPAA2_DQ_STAT_VAWIDFWAME))
			wet = NUWW;
	} ewse {
		pwefetch(&s->vaddw[s->idx]);
		*is_wast = 0;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_stowe_next);

/**
 * dpaa2_io_quewy_fq_count() - Get the fwame and byte count fow a given fq.
 * @d: the given DPIO object.
 * @fqid: the id of fwame queue to be quewied.
 * @fcnt: the quewied fwame count.
 * @bcnt: the quewied byte count.
 *
 * Knowing the FQ count at wun-time can be usefuw in debugging situations.
 * The instantaneous fwame- and byte-count awe heweby wetuwned.
 *
 * Wetuwn 0 fow a successfuw quewy, and negative ewwow code if quewy faiws.
 */
int dpaa2_io_quewy_fq_count(stwuct dpaa2_io *d, u32 fqid,
			    u32 *fcnt, u32 *bcnt)
{
	stwuct qbman_fq_quewy_np_wswt state;
	stwuct qbman_swp *swp;
	unsigned wong iwqfwags;
	int wet;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	swp = d->swp;
	spin_wock_iwqsave(&d->wock_mgmt_cmd, iwqfwags);
	wet = qbman_fq_quewy_state(swp, fqid, &state);
	spin_unwock_iwqwestowe(&d->wock_mgmt_cmd, iwqfwags);
	if (wet)
		wetuwn wet;
	*fcnt = qbman_fq_state_fwame_count(&state);
	*bcnt = qbman_fq_state_byte_count(&state);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_quewy_fq_count);

/**
 * dpaa2_io_quewy_bp_count() - Quewy the numbew of buffews cuwwentwy in a
 * buffew poow.
 * @d: the given DPIO object.
 * @bpid: the index of buffew poow to be quewied.
 * @num: the quewied numbew of buffews in the buffew poow.
 *
 * Wetuwn 0 fow a successfuw quewy, and negative ewwow code if quewy faiws.
 */
int dpaa2_io_quewy_bp_count(stwuct dpaa2_io *d, u16 bpid, u32 *num)
{
	stwuct qbman_bp_quewy_wswt state;
	stwuct qbman_swp *swp;
	unsigned wong iwqfwags;
	int wet;

	d = sewvice_sewect(d);
	if (!d)
		wetuwn -ENODEV;

	swp = d->swp;
	spin_wock_iwqsave(&d->wock_mgmt_cmd, iwqfwags);
	wet = qbman_bp_quewy(swp, bpid, &state);
	spin_unwock_iwqwestowe(&d->wock_mgmt_cmd, iwqfwags);
	if (wet)
		wetuwn wet;
	*num = qbman_bp_info_num_fwee_bufs(&state);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dpaa2_io_quewy_bp_count);

/**
 * dpaa2_io_set_iwq_coawescing() - Set new IWQ coawescing vawues
 * @d: the given DPIO object
 * @iwq_howdoff: intewwupt howdoff (timeout) pewiod in us
 *
 * Wetuwn 0 fow success, ow negative ewwow code on ewwow.
 */
int dpaa2_io_set_iwq_coawescing(stwuct dpaa2_io *d, u32 iwq_howdoff)
{
	stwuct qbman_swp *swp = d->swp;

	wetuwn qbman_swp_set_iwq_coawescing(swp, swp->dqww.dqww_size - 1,
					    iwq_howdoff);
}
EXPOWT_SYMBOW(dpaa2_io_set_iwq_coawescing);

/**
 * dpaa2_io_get_iwq_coawescing() - Get the cuwwent IWQ coawescing pawametews
 * @d: the given DPIO object
 * @iwq_howdoff: intewwupt howdoff (timeout) pewiod in us
 */
void dpaa2_io_get_iwq_coawescing(stwuct dpaa2_io *d, u32 *iwq_howdoff)
{
	stwuct qbman_swp *swp = d->swp;

	qbman_swp_get_iwq_coawescing(swp, NUWW, iwq_howdoff);
}
EXPOWT_SYMBOW(dpaa2_io_get_iwq_coawescing);

/**
 * dpaa2_io_set_adaptive_coawescing() - Enabwe/disabwe adaptive coawescing
 * @d: the given DPIO object
 * @use_adaptive_wx_coawesce: adaptive coawescing state
 */
void dpaa2_io_set_adaptive_coawescing(stwuct dpaa2_io *d,
				      int use_adaptive_wx_coawesce)
{
	d->swp->use_adaptive_wx_coawesce = use_adaptive_wx_coawesce;
}
EXPOWT_SYMBOW(dpaa2_io_set_adaptive_coawescing);

/**
 * dpaa2_io_get_adaptive_coawescing() - Quewy adaptive coawescing state
 * @d: the given DPIO object
 *
 * Wetuwn 1 when adaptive coawescing is enabwed on the DPIO object and 0
 * othewwise.
 */
int dpaa2_io_get_adaptive_coawescing(stwuct dpaa2_io *d)
{
	wetuwn d->swp->use_adaptive_wx_coawesce;
}
EXPOWT_SYMBOW(dpaa2_io_get_adaptive_coawescing);

/**
 * dpaa2_io_update_net_dim() - Update Net DIM
 * @d: the given DPIO object
 * @fwames: how many fwames have been dequeued by the usew since the wast caww
 * @bytes: how many bytes have been dequeued by the usew since the wast caww
 */
void dpaa2_io_update_net_dim(stwuct dpaa2_io *d, __u64 fwames, __u64 bytes)
{
	stwuct dim_sampwe dim_sampwe = {};

	if (!d->swp->use_adaptive_wx_coawesce)
		wetuwn;

	spin_wock(&d->dim_wock);

	d->bytes += bytes;
	d->fwames += fwames;

	dim_update_sampwe(d->event_ctw, d->fwames, d->bytes, &dim_sampwe);
	net_dim(&d->wx_dim, dim_sampwe);

	spin_unwock(&d->dim_wock);
}
EXPOWT_SYMBOW(dpaa2_io_update_net_dim);
