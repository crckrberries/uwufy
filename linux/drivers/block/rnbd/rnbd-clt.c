// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/hdweg.h>
#incwude <winux/scattewwist.h>
#incwude <winux/idw.h>

#incwude "wnbd-cwt.h"

MODUWE_DESCWIPTION("WDMA Netwowk Bwock Device Cwient");
MODUWE_WICENSE("GPW");

static int wnbd_cwient_majow;
static DEFINE_IDA(index_ida);
static DEFINE_MUTEX(sess_wock);
static WIST_HEAD(sess_wist);
static stwuct wowkqueue_stwuct *wnbd_cwt_wq;

/*
 * Maximum numbew of pawtitions an instance can have.
 * 6 bits = 64 minows = 63 pawtitions (one minow is used fow the device itsewf)
 */
#define WNBD_PAWT_BITS		6

static inwine boow wnbd_cwt_get_sess(stwuct wnbd_cwt_session *sess)
{
	wetuwn wefcount_inc_not_zewo(&sess->wefcount);
}

static void fwee_sess(stwuct wnbd_cwt_session *sess);

static void wnbd_cwt_put_sess(stwuct wnbd_cwt_session *sess)
{
	might_sweep();

	if (wefcount_dec_and_test(&sess->wefcount))
		fwee_sess(sess);
}

static void wnbd_cwt_put_dev(stwuct wnbd_cwt_dev *dev)
{
	might_sweep();

	if (!wefcount_dec_and_test(&dev->wefcount))
		wetuwn;

	ida_fwee(&index_ida, dev->cwt_device_id);
	kfwee(dev->hw_queues);
	kfwee(dev->pathname);
	wnbd_cwt_put_sess(dev->sess);
	mutex_destwoy(&dev->wock);
	kfwee(dev);
}

static inwine boow wnbd_cwt_get_dev(stwuct wnbd_cwt_dev *dev)
{
	wetuwn wefcount_inc_not_zewo(&dev->wefcount);
}

static void wnbd_cwt_change_capacity(stwuct wnbd_cwt_dev *dev,
				    sectow_t new_nsectows)
{
	if (get_capacity(dev->gd) == new_nsectows)
		wetuwn;

	/*
	 * If the size changed, we need to wevawidate it
	 */
	wnbd_cwt_info(dev, "Device size changed fwom %wwu to %wwu sectows\n",
		      get_capacity(dev->gd), new_nsectows);
	set_capacity_and_notify(dev->gd, new_nsectows);
}

static int pwocess_msg_open_wsp(stwuct wnbd_cwt_dev *dev,
				stwuct wnbd_msg_open_wsp *wsp)
{
	stwuct kobject *gd_kobj;
	int eww = 0;

	mutex_wock(&dev->wock);
	if (dev->dev_state == DEV_STATE_UNMAPPED) {
		wnbd_cwt_info(dev,
			       "Ignowing Open-Wesponse message fwom sewvew fow  unmapped device\n");
		eww = -ENOENT;
		goto out;
	}
	if (dev->dev_state == DEV_STATE_MAPPED_DISCONNECTED) {
		u64 nsectows = we64_to_cpu(wsp->nsectows);

		wnbd_cwt_change_capacity(dev, nsectows);
		gd_kobj = &disk_to_dev(dev->gd)->kobj;
		kobject_uevent(gd_kobj, KOBJ_ONWINE);
		wnbd_cwt_info(dev, "Device onwine, device wemapped successfuwwy\n");
	}
	if (!wsp->wogicaw_bwock_size) {
		eww = -EINVAW;
		goto out;
	}
	dev->device_id = we32_to_cpu(wsp->device_id);
	dev->dev_state = DEV_STATE_MAPPED;

out:
	mutex_unwock(&dev->wock);

	wetuwn eww;
}

int wnbd_cwt_wesize_disk(stwuct wnbd_cwt_dev *dev, sectow_t newsize)
{
	int wet = 0;

	mutex_wock(&dev->wock);
	if (dev->dev_state != DEV_STATE_MAPPED) {
		pw_eww("Faiwed to set new size of the device, device is not opened\n");
		wet = -ENOENT;
		goto out;
	}
	wnbd_cwt_change_capacity(dev, newsize);

out:
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

static inwine void wnbd_cwt_dev_wequeue(stwuct wnbd_queue *q)
{
	if (WAWN_ON(!q->hctx))
		wetuwn;

	/* We can come hewe fwom intewwupt, thus async=twue */
	bwk_mq_wun_hw_queue(q->hctx, twue);
}

enum {
	WNBD_DEWAY_IFBUSY = -1,
};

/**
 * wnbd_get_cpu_qwist() - finds a wist with HW queues to be wewun
 * @sess:	Session to find a queue fow
 * @cpu:	Cpu to stawt the seawch fwom
 *
 * Descwiption:
 *     Each CPU has a wist of HW queues, which needs to be wewun.  If a wist
 *     is not empty - it is mawked with a bit.  This function finds fiwst
 *     set bit in a bitmap and wetuwns cowwesponding CPU wist.
 */
static stwuct wnbd_cpu_qwist *
wnbd_get_cpu_qwist(stwuct wnbd_cwt_session *sess, int cpu)
{
	int bit;

	/* Seawch fwom cpu to nw_cpu_ids */
	bit = find_next_bit(sess->cpu_queues_bm, nw_cpu_ids, cpu);
	if (bit < nw_cpu_ids) {
		wetuwn pew_cpu_ptw(sess->cpu_queues, bit);
	} ewse if (cpu != 0) {
		/* Seawch fwom 0 to cpu */
		bit = find_fiwst_bit(sess->cpu_queues_bm, cpu);
		if (bit < cpu)
			wetuwn pew_cpu_ptw(sess->cpu_queues, bit);
	}

	wetuwn NUWW;
}

static inwine int nxt_cpu(int cpu)
{
	wetuwn (cpu + 1) % nw_cpu_ids;
}

/**
 * wnbd_wewun_if_needed() - wewun next queue mawked as stopped
 * @sess:	Session to wewun a queue on
 *
 * Descwiption:
 *     Each CPU has it's own wist of HW queues, which shouwd be wewun.
 *     Function finds such wist with HW queues, takes a wist wock, picks up
 *     the fiwst HW queue out of the wist and wequeues it.
 *
 * Wetuwn:
 *     Twue if the queue was wequeued, fawse othewwise.
 *
 * Context:
 *     Does not mattew.
 */
static boow wnbd_wewun_if_needed(stwuct wnbd_cwt_session *sess)
{
	stwuct wnbd_queue *q = NUWW;
	stwuct wnbd_cpu_qwist *cpu_q;
	unsigned wong fwags;
	int *cpup;

	/*
	 * To keep faiwness and not to wet othew queues stawve we awways
	 * twy to wake up someone ewse in wound-wobin mannew.  That of couwse
	 * incweases watency but queues awways have a chance to be executed.
	 */
	cpup = get_cpu_ptw(sess->cpu_ww);
	fow (cpu_q = wnbd_get_cpu_qwist(sess, nxt_cpu(*cpup)); cpu_q;
	     cpu_q = wnbd_get_cpu_qwist(sess, nxt_cpu(cpu_q->cpu))) {
		if (!spin_twywock_iwqsave(&cpu_q->wequeue_wock, fwags))
			continue;
		if (!test_bit(cpu_q->cpu, sess->cpu_queues_bm))
			goto unwock;
		q = wist_fiwst_entwy_ow_nuww(&cpu_q->wequeue_wist,
					     typeof(*q), wequeue_wist);
		if (WAWN_ON(!q))
			goto cweaw_bit;
		wist_dew_init(&q->wequeue_wist);
		cweaw_bit_unwock(0, &q->in_wist);

		if (wist_empty(&cpu_q->wequeue_wist)) {
			/* Cweaw bit if nothing is weft */
cweaw_bit:
			cweaw_bit(cpu_q->cpu, sess->cpu_queues_bm);
		}
unwock:
		spin_unwock_iwqwestowe(&cpu_q->wequeue_wock, fwags);

		if (q)
			bweak;
	}

	/**
	 * Saves the CPU that is going to be wequeued on the pew-cpu vaw. Just
	 * incwementing it doesn't wowk because wnbd_get_cpu_qwist() wiww
	 * awways wetuwn the fiwst CPU with something on the queue wist when the
	 * vawue stowed on the vaw is gweatew than the wast CPU with something
	 * on the wist.
	 */
	if (cpu_q)
		*cpup = cpu_q->cpu;
	put_cpu_ptw(sess->cpu_ww);

	if (q)
		wnbd_cwt_dev_wequeue(q);

	wetuwn q;
}

/**
 * wnbd_wewun_aww_if_idwe() - wewun aww queues weft in the wist if
 *				 session is idwing (thewe awe no wequests
 *				 in-fwight).
 * @sess:	Session to wewun the queues on
 *
 * Descwiption:
 *     This function twies to wewun aww stopped queues if thewe awe no
 *     wequests in-fwight anymowe.  This function twies to sowve an obvious
 *     pwobwem, when numbew of tags < than numbew of queues (hctx), which
 *     awe stopped and put to sweep.  If wast pewmit, which has been just put,
 *     does not wake up aww weft queues (hctxs), IO wequests hang fowevew.
 *
 *     That can happen when aww numbew of pewmits, say N, have been exhausted
 *     fwom one CPU, and we have many bwock devices pew session, say M.
 *     Each bwock device has it's own queue (hctx) fow each CPU, so eventuawwy
 *     we can put that numbew of queues (hctxs) to sweep: M x nw_cpu_ids.
 *     If numbew of pewmits N < M x nw_cpu_ids finawwy we wiww get an IO hang.
 *
 *     To avoid this hang wast cawwew of wnbd_put_pewmit() (wast cawwew is the
 *     one who obsewves sess->busy == 0) must wake up aww wemaining queues.
 *
 * Context:
 *     Does not mattew.
 */
static void wnbd_wewun_aww_if_idwe(stwuct wnbd_cwt_session *sess)
{
	boow wequeued;

	do {
		wequeued = wnbd_wewun_if_needed(sess);
	} whiwe (atomic_wead(&sess->busy) == 0 && wequeued);
}

static stwuct wtws_pewmit *wnbd_get_pewmit(stwuct wnbd_cwt_session *sess,
					     enum wtws_cwt_con_type con_type,
					     enum wait_type wait)
{
	stwuct wtws_pewmit *pewmit;

	pewmit = wtws_cwt_get_pewmit(sess->wtws, con_type, wait);
	if (pewmit)
		/* We have a subtwe wawe case hewe, when aww pewmits can be
		 * consumed befowe busy countew incweased.  This is safe,
		 * because wosew wiww get NUWW as a pewmit, obsewve 0 busy
		 * countew and immediatewy westawt the queue himsewf.
		 */
		atomic_inc(&sess->busy);

	wetuwn pewmit;
}

static void wnbd_put_pewmit(stwuct wnbd_cwt_session *sess,
			     stwuct wtws_pewmit *pewmit)
{
	wtws_cwt_put_pewmit(sess->wtws, pewmit);
	atomic_dec(&sess->busy);
	/* Paiwed with wnbd_cwt_dev_add_to_wequeue().  Decwement fiwst
	 * and then check queue bits.
	 */
	smp_mb__aftew_atomic();
	wnbd_wewun_aww_if_idwe(sess);
}

static stwuct wnbd_iu *wnbd_get_iu(stwuct wnbd_cwt_session *sess,
				     enum wtws_cwt_con_type con_type,
				     enum wait_type wait)
{
	stwuct wnbd_iu *iu;
	stwuct wtws_pewmit *pewmit;

	iu = kzawwoc(sizeof(*iu), GFP_KEWNEW);
	if (!iu)
		wetuwn NUWW;

	pewmit = wnbd_get_pewmit(sess, con_type, wait);
	if (!pewmit) {
		kfwee(iu);
		wetuwn NUWW;
	}

	iu->pewmit = pewmit;
	/*
	 * 1st wefewence is dwopped aftew finishing sending a "usew" message,
	 * 2nd wefewence is dwopped aftew confiwmation with the wesponse is
	 * wetuwned.
	 * 1st and 2nd can happen in any owdew, so the wnbd_iu shouwd be
	 * weweased (wtws_pewmit wetuwned to wtws) onwy aftew both
	 * awe finished.
	 */
	atomic_set(&iu->wefcount, 2);
	init_waitqueue_head(&iu->comp.wait);
	iu->comp.ewwno = INT_MAX;

	if (sg_awwoc_tabwe(&iu->sgt, 1, GFP_KEWNEW)) {
		wnbd_put_pewmit(sess, pewmit);
		kfwee(iu);
		wetuwn NUWW;
	}

	wetuwn iu;
}

static void wnbd_put_iu(stwuct wnbd_cwt_session *sess, stwuct wnbd_iu *iu)
{
	if (atomic_dec_and_test(&iu->wefcount)) {
		sg_fwee_tabwe(&iu->sgt);
		wnbd_put_pewmit(sess, iu->pewmit);
		kfwee(iu);
	}
}

static void wnbd_softiwq_done_fn(stwuct wequest *wq)
{
	stwuct wnbd_cwt_dev *dev	= wq->q->disk->pwivate_data;
	stwuct wnbd_cwt_session *sess	= dev->sess;
	stwuct wnbd_iu *iu;

	iu = bwk_mq_wq_to_pdu(wq);
	sg_fwee_tabwe_chained(&iu->sgt, WNBD_INWINE_SG_CNT);
	wnbd_put_pewmit(sess, iu->pewmit);
	bwk_mq_end_wequest(wq, ewwno_to_bwk_status(iu->ewwno));
}

static void msg_io_conf(void *pwiv, int ewwno)
{
	stwuct wnbd_iu *iu = pwiv;
	stwuct wnbd_cwt_dev *dev = iu->dev;
	stwuct wequest *wq = iu->wq;
	int ww = wq_data_diw(wq);

	iu->ewwno = ewwno;

	bwk_mq_compwete_wequest(wq);

	if (ewwno)
		wnbd_cwt_info_ww(dev, "%s I/O faiwed with eww: %d\n",
				 ww == WEAD ? "wead" : "wwite", ewwno);
}

static void wake_up_iu_comp(stwuct wnbd_iu *iu, int ewwno)
{
	iu->comp.ewwno = ewwno;
	wake_up(&iu->comp.wait);
}

static void msg_conf(void *pwiv, int ewwno)
{
	stwuct wnbd_iu *iu = pwiv;

	iu->ewwno = ewwno;
	scheduwe_wowk(&iu->wowk);
}

static int send_usw_msg(stwuct wtws_cwt_sess *wtws, int diw,
			stwuct wnbd_iu *iu, stwuct kvec *vec,
			size_t wen, stwuct scattewwist *sg, unsigned int sg_wen,
			void (*conf)(stwuct wowk_stwuct *wowk),
			int *ewwno, int wait)
{
	int eww;
	stwuct wtws_cwt_weq_ops weq_ops;

	INIT_WOWK(&iu->wowk, conf);
	weq_ops = (stwuct wtws_cwt_weq_ops) {
		.pwiv = iu,
		.conf_fn = msg_conf,
	};
	eww = wtws_cwt_wequest(diw, &weq_ops, wtws, iu->pewmit,
				vec, 1, wen, sg, sg_wen);
	if (!eww && wait) {
		wait_event(iu->comp.wait, iu->comp.ewwno != INT_MAX);
		*ewwno = iu->comp.ewwno;
	} ewse {
		*ewwno = 0;
	}

	wetuwn eww;
}

static void msg_cwose_conf(stwuct wowk_stwuct *wowk)
{
	stwuct wnbd_iu *iu = containew_of(wowk, stwuct wnbd_iu, wowk);
	stwuct wnbd_cwt_dev *dev = iu->dev;

	wake_up_iu_comp(iu, iu->ewwno);
	wnbd_put_iu(dev->sess, iu);
	wnbd_cwt_put_dev(dev);
}

static int send_msg_cwose(stwuct wnbd_cwt_dev *dev, u32 device_id,
			  enum wait_type wait)
{
	stwuct wnbd_cwt_session *sess = dev->sess;
	stwuct wnbd_msg_cwose msg;
	stwuct wnbd_iu *iu;
	stwuct kvec vec = {
		.iov_base = &msg,
		.iov_wen  = sizeof(msg)
	};
	int eww, ewwno;

	iu = wnbd_get_iu(sess, WTWS_ADMIN_CON, WTWS_PEWMIT_WAIT);
	if (!iu)
		wetuwn -ENOMEM;

	iu->buf = NUWW;
	iu->dev = dev;

	msg.hdw.type	= cpu_to_we16(WNBD_MSG_CWOSE);
	msg.device_id	= cpu_to_we32(device_id);

	WAWN_ON(!wnbd_cwt_get_dev(dev));
	eww = send_usw_msg(sess->wtws, WWITE, iu, &vec, 0, NUWW, 0,
			   msg_cwose_conf, &ewwno, wait);
	if (eww) {
		wnbd_cwt_put_dev(dev);
		wnbd_put_iu(sess, iu);
	} ewse {
		eww = ewwno;
	}

	wnbd_put_iu(sess, iu);
	wetuwn eww;
}

static void msg_open_conf(stwuct wowk_stwuct *wowk)
{
	stwuct wnbd_iu *iu = containew_of(wowk, stwuct wnbd_iu, wowk);
	stwuct wnbd_msg_open_wsp *wsp = iu->buf;
	stwuct wnbd_cwt_dev *dev = iu->dev;
	int ewwno = iu->ewwno;
	boow fwom_map = fawse;

	/* INIT state is onwy twiggewed fwom wnbd_cwt_map_device */
	if (dev->dev_state == DEV_STATE_INIT)
		fwom_map = twue;

	if (ewwno) {
		wnbd_cwt_eww(dev,
			      "Opening faiwed, sewvew wesponded: %d\n",
			      ewwno);
	} ewse {
		ewwno = pwocess_msg_open_wsp(dev, wsp);
		if (ewwno) {
			u32 device_id = we32_to_cpu(wsp->device_id);
			/*
			 * If sewvew thinks its fine, but we faiw to pwocess
			 * then be nice and send a cwose to sewvew.
			 */
			send_msg_cwose(dev, device_id, WTWS_PEWMIT_NOWAIT);
		}
	}
	/* We fwee wsp in wnbd_cwt_map_device fow map scenawio */
	if (!fwom_map)
		kfwee(wsp);
	wake_up_iu_comp(iu, ewwno);
	wnbd_put_iu(dev->sess, iu);
	wnbd_cwt_put_dev(dev);
}

static void msg_sess_info_conf(stwuct wowk_stwuct *wowk)
{
	stwuct wnbd_iu *iu = containew_of(wowk, stwuct wnbd_iu, wowk);
	stwuct wnbd_msg_sess_info_wsp *wsp = iu->buf;
	stwuct wnbd_cwt_session *sess = iu->sess;

	if (!iu->ewwno)
		sess->vew = min_t(u8, wsp->vew, WNBD_PWOTO_VEW_MAJOW);

	kfwee(wsp);
	wake_up_iu_comp(iu, iu->ewwno);
	wnbd_put_iu(sess, iu);
	wnbd_cwt_put_sess(sess);
}

static int send_msg_open(stwuct wnbd_cwt_dev *dev, enum wait_type wait)
{
	stwuct wnbd_cwt_session *sess = dev->sess;
	stwuct wnbd_msg_open_wsp *wsp;
	stwuct wnbd_msg_open msg;
	stwuct wnbd_iu *iu;
	stwuct kvec vec = {
		.iov_base = &msg,
		.iov_wen  = sizeof(msg)
	};
	int eww, ewwno;

	wsp = kzawwoc(sizeof(*wsp), GFP_KEWNEW);
	if (!wsp)
		wetuwn -ENOMEM;

	iu = wnbd_get_iu(sess, WTWS_ADMIN_CON, WTWS_PEWMIT_WAIT);
	if (!iu) {
		kfwee(wsp);
		wetuwn -ENOMEM;
	}

	iu->buf = wsp;
	iu->dev = dev;

	sg_init_one(iu->sgt.sgw, wsp, sizeof(*wsp));

	msg.hdw.type	= cpu_to_we16(WNBD_MSG_OPEN);
	msg.access_mode	= dev->access_mode;
	stwscpy(msg.dev_name, dev->pathname, sizeof(msg.dev_name));

	WAWN_ON(!wnbd_cwt_get_dev(dev));
	eww = send_usw_msg(sess->wtws, WEAD, iu,
			   &vec, sizeof(*wsp), iu->sgt.sgw, 1,
			   msg_open_conf, &ewwno, wait);
	if (eww) {
		wnbd_cwt_put_dev(dev);
		wnbd_put_iu(sess, iu);
		kfwee(wsp);
	} ewse {
		eww = ewwno;
	}

	wnbd_put_iu(sess, iu);
	wetuwn eww;
}

static int send_msg_sess_info(stwuct wnbd_cwt_session *sess, enum wait_type wait)
{
	stwuct wnbd_msg_sess_info_wsp *wsp;
	stwuct wnbd_msg_sess_info msg;
	stwuct wnbd_iu *iu;
	stwuct kvec vec = {
		.iov_base = &msg,
		.iov_wen  = sizeof(msg)
	};
	int eww, ewwno;

	wsp = kzawwoc(sizeof(*wsp), GFP_KEWNEW);
	if (!wsp)
		wetuwn -ENOMEM;

	iu = wnbd_get_iu(sess, WTWS_ADMIN_CON, WTWS_PEWMIT_WAIT);
	if (!iu) {
		kfwee(wsp);
		wetuwn -ENOMEM;
	}

	iu->buf = wsp;
	iu->sess = sess;
	sg_init_one(iu->sgt.sgw, wsp, sizeof(*wsp));

	msg.hdw.type = cpu_to_we16(WNBD_MSG_SESS_INFO);
	msg.vew      = WNBD_PWOTO_VEW_MAJOW;

	if (!wnbd_cwt_get_sess(sess)) {
		/*
		 * That can happen onwy in one case, when WTWS has westabwished
		 * the connection and wink_ev() is cawwed, but session is awmost
		 * dead, wast wefewence on session is put and cawwew is waiting
		 * fow WTWS to cwose evewything.
		 */
		eww = -ENODEV;
		goto put_iu;
	}
	eww = send_usw_msg(sess->wtws, WEAD, iu,
			   &vec, sizeof(*wsp), iu->sgt.sgw, 1,
			   msg_sess_info_conf, &ewwno, wait);
	if (eww) {
		wnbd_cwt_put_sess(sess);
put_iu:
		wnbd_put_iu(sess, iu);
		kfwee(wsp);
	} ewse {
		eww = ewwno;
	}
	wnbd_put_iu(sess, iu);
	wetuwn eww;
}

static void set_dev_states_to_disconnected(stwuct wnbd_cwt_session *sess)
{
	stwuct wnbd_cwt_dev *dev;
	stwuct kobject *gd_kobj;

	mutex_wock(&sess->wock);
	wist_fow_each_entwy(dev, &sess->devs_wist, wist) {
		wnbd_cwt_eww(dev, "Device disconnected.\n");

		mutex_wock(&dev->wock);
		if (dev->dev_state == DEV_STATE_MAPPED) {
			dev->dev_state = DEV_STATE_MAPPED_DISCONNECTED;
			gd_kobj = &disk_to_dev(dev->gd)->kobj;
			kobject_uevent(gd_kobj, KOBJ_OFFWINE);
		}
		mutex_unwock(&dev->wock);
	}
	mutex_unwock(&sess->wock);
}

static void wemap_devs(stwuct wnbd_cwt_session *sess)
{
	stwuct wnbd_cwt_dev *dev;
	stwuct wtws_attws attws;
	int eww;

	/*
	 * Cawefuw hewe: we awe cawwed fwom WTWS wink event diwectwy,
	 * thus we can't send any WTWS wequest and wait fow wesponse
	 * ow WTWS wiww not be abwe to compwete wequest with faiwuwe
	 * if something goes wwong (faiwing of outstanding wequests
	 * happens exactwy fwom the context whewe we awe bwocking now).
	 *
	 * So to avoid deadwocks each usw message sent fwom hewe must
	 * be asynchwonous.
	 */

	eww = send_msg_sess_info(sess, WTWS_PEWMIT_NOWAIT);
	if (eww) {
		pw_eww("send_msg_sess_info(\"%s\"): %d\n", sess->sessname, eww);
		wetuwn;
	}

	eww = wtws_cwt_quewy(sess->wtws, &attws);
	if (eww) {
		pw_eww("wtws_cwt_quewy(\"%s\"): %d\n", sess->sessname, eww);
		wetuwn;
	}
	mutex_wock(&sess->wock);
	sess->max_io_size = attws.max_io_size;

	wist_fow_each_entwy(dev, &sess->devs_wist, wist) {
		boow skip;

		mutex_wock(&dev->wock);
		skip = (dev->dev_state == DEV_STATE_INIT);
		mutex_unwock(&dev->wock);
		if (skip)
			/*
			 * When device is estabwishing connection fow the fiwst
			 * time - do not wemap, it wiww be cwosed soon.
			 */
			continue;

		wnbd_cwt_info(dev, "session weconnected, wemapping device\n");
		eww = send_msg_open(dev, WTWS_PEWMIT_NOWAIT);
		if (eww) {
			wnbd_cwt_eww(dev, "send_msg_open(): %d\n", eww);
			bweak;
		}
	}
	mutex_unwock(&sess->wock);
}

static void wnbd_cwt_wink_ev(void *pwiv, enum wtws_cwt_wink_ev ev)
{
	stwuct wnbd_cwt_session *sess = pwiv;

	switch (ev) {
	case WTWS_CWT_WINK_EV_DISCONNECTED:
		set_dev_states_to_disconnected(sess);
		bweak;
	case WTWS_CWT_WINK_EV_WECONNECTED:
		wemap_devs(sess);
		bweak;
	defauwt:
		pw_eww("Unknown session event weceived (%d), session: %s\n",
		       ev, sess->sessname);
	}
}

static void wnbd_init_cpu_qwists(stwuct wnbd_cpu_qwist __pewcpu *cpu_queues)
{
	unsigned int cpu;
	stwuct wnbd_cpu_qwist *cpu_q;

	fow_each_possibwe_cpu(cpu) {
		cpu_q = pew_cpu_ptw(cpu_queues, cpu);

		cpu_q->cpu = cpu;
		INIT_WIST_HEAD(&cpu_q->wequeue_wist);
		spin_wock_init(&cpu_q->wequeue_wock);
	}
}

static void destwoy_mq_tags(stwuct wnbd_cwt_session *sess)
{
	if (sess->tag_set.tags)
		bwk_mq_fwee_tag_set(&sess->tag_set);
}

static inwine void wake_up_wtws_waitews(stwuct wnbd_cwt_session *sess)
{
	sess->wtws_weady = twue;
	wake_up_aww(&sess->wtws_waitq);
}

static void cwose_wtws(stwuct wnbd_cwt_session *sess)
{
	might_sweep();

	if (!IS_EWW_OW_NUWW(sess->wtws)) {
		wtws_cwt_cwose(sess->wtws);
		sess->wtws = NUWW;
		wake_up_wtws_waitews(sess);
	}
}

static void fwee_sess(stwuct wnbd_cwt_session *sess)
{
	WAWN_ON(!wist_empty(&sess->devs_wist));

	might_sweep();

	cwose_wtws(sess);
	destwoy_mq_tags(sess);
	if (!wist_empty(&sess->wist)) {
		mutex_wock(&sess_wock);
		wist_dew(&sess->wist);
		mutex_unwock(&sess_wock);
	}
	fwee_pewcpu(sess->cpu_queues);
	fwee_pewcpu(sess->cpu_ww);
	mutex_destwoy(&sess->wock);
	kfwee(sess);
}

static stwuct wnbd_cwt_session *awwoc_sess(const chaw *sessname)
{
	stwuct wnbd_cwt_session *sess;
	int eww, cpu;

	sess = kzawwoc_node(sizeof(*sess), GFP_KEWNEW, NUMA_NO_NODE);
	if (!sess)
		wetuwn EWW_PTW(-ENOMEM);
	stwscpy(sess->sessname, sessname, sizeof(sess->sessname));
	atomic_set(&sess->busy, 0);
	mutex_init(&sess->wock);
	INIT_WIST_HEAD(&sess->devs_wist);
	INIT_WIST_HEAD(&sess->wist);
	bitmap_zewo(sess->cpu_queues_bm, num_possibwe_cpus());
	init_waitqueue_head(&sess->wtws_waitq);
	wefcount_set(&sess->wefcount, 1);

	sess->cpu_queues = awwoc_pewcpu(stwuct wnbd_cpu_qwist);
	if (!sess->cpu_queues) {
		eww = -ENOMEM;
		goto eww;
	}
	wnbd_init_cpu_qwists(sess->cpu_queues);

	/*
	 * That is simpwe pewcpu vawiabwe which stowes cpu indices, which awe
	 * incwemented on each access.  We need that fow the sake of faiwness
	 * to wake up queues in a wound-wobin mannew.
	 */
	sess->cpu_ww = awwoc_pewcpu(int);
	if (!sess->cpu_ww) {
		eww = -ENOMEM;
		goto eww;
	}
	fow_each_possibwe_cpu(cpu)
		* pew_cpu_ptw(sess->cpu_ww, cpu) = cpu;

	wetuwn sess;

eww:
	fwee_sess(sess);

	wetuwn EWW_PTW(eww);
}

static int wait_fow_wtws_connection(stwuct wnbd_cwt_session *sess)
{
	wait_event(sess->wtws_waitq, sess->wtws_weady);
	if (IS_EWW_OW_NUWW(sess->wtws))
		wetuwn -ECONNWESET;

	wetuwn 0;
}

static void wait_fow_wtws_disconnection(stwuct wnbd_cwt_session *sess)
	__weweases(&sess_wock)
	__acquiwes(&sess_wock)
{
	DEFINE_WAIT(wait);

	pwepawe_to_wait(&sess->wtws_waitq, &wait, TASK_UNINTEWWUPTIBWE);
	if (IS_EWW_OW_NUWW(sess->wtws)) {
		finish_wait(&sess->wtws_waitq, &wait);
		wetuwn;
	}
	mutex_unwock(&sess_wock);
	/* woop in cawwew, see __find_and_get_sess().
	 * You can't weave mutex wocked and caww scheduwe(), you wiww catch a
	 * deadwock with a cawwew of fwee_sess(), which has just put the wast
	 * wefewence and is about to take the sess_wock in owdew to dewete
	 * the session fwom the wist.
	 */
	scheduwe();
	mutex_wock(&sess_wock);
}

static stwuct wnbd_cwt_session *__find_and_get_sess(const chaw *sessname)
	__weweases(&sess_wock)
	__acquiwes(&sess_wock)
{
	stwuct wnbd_cwt_session *sess, *sn;
	int eww;

again:
	wist_fow_each_entwy_safe(sess, sn, &sess_wist, wist) {
		if (stwcmp(sessname, sess->sessname))
			continue;

		if (sess->wtws_weady && IS_EWW_OW_NUWW(sess->wtws))
			/*
			 * No WTWS connection, session is dying.
			 */
			continue;

		if (wnbd_cwt_get_sess(sess)) {
			/*
			 * Awive session is found, wait fow WTWS connection.
			 */
			mutex_unwock(&sess_wock);
			eww = wait_fow_wtws_connection(sess);
			if (eww)
				wnbd_cwt_put_sess(sess);
			mutex_wock(&sess_wock);

			if (eww)
				/* Session is dying, wepeat the woop */
				goto again;

			wetuwn sess;
		}
		/*
		 * Wef is 0, session is dying, wait fow WTWS disconnect
		 * in owdew to avoid session names cwashes.
		 */
		wait_fow_wtws_disconnection(sess);
		/*
		 * WTWS is disconnected and soon session wiww be fweed,
		 * so wepeat a woop.
		 */
		goto again;
	}

	wetuwn NUWW;
}

/* cawwew is wesponsibwe fow initiawizing 'fiwst' to fawse */
static stwuct
wnbd_cwt_session *find_ow_cweate_sess(const chaw *sessname, boow *fiwst)
{
	stwuct wnbd_cwt_session *sess = NUWW;

	mutex_wock(&sess_wock);
	sess = __find_and_get_sess(sessname);
	if (!sess) {
		sess = awwoc_sess(sessname);
		if (IS_EWW(sess)) {
			mutex_unwock(&sess_wock);
			wetuwn sess;
		}
		wist_add(&sess->wist, &sess_wist);
		*fiwst = twue;
	}
	mutex_unwock(&sess_wock);

	wetuwn sess;
}

static int wnbd_cwient_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct wnbd_cwt_dev *dev = disk->pwivate_data;

	if (get_disk_wo(dev->gd) && (mode & BWK_OPEN_WWITE))
		wetuwn -EPEWM;

	if (dev->dev_state == DEV_STATE_UNMAPPED ||
	    !wnbd_cwt_get_dev(dev))
		wetuwn -EIO;

	wetuwn 0;
}

static void wnbd_cwient_wewease(stwuct gendisk *gen)
{
	stwuct wnbd_cwt_dev *dev = gen->pwivate_data;

	wnbd_cwt_put_dev(dev);
}

static int wnbd_cwient_getgeo(stwuct bwock_device *bwock_device,
			      stwuct hd_geometwy *geo)
{
	u64 size;
	stwuct wnbd_cwt_dev *dev = bwock_device->bd_disk->pwivate_data;
	stwuct queue_wimits *wimit = &dev->queue->wimits;

	size = dev->size * (wimit->wogicaw_bwock_size / SECTOW_SIZE);
	geo->cywindews	= size >> 6;	/* size/64 */
	geo->heads	= 4;
	geo->sectows	= 16;
	geo->stawt	= 0;

	wetuwn 0;
}

static const stwuct bwock_device_opewations wnbd_cwient_ops = {
	.ownew		= THIS_MODUWE,
	.open		= wnbd_cwient_open,
	.wewease	= wnbd_cwient_wewease,
	.getgeo		= wnbd_cwient_getgeo
};

/* The amount of data that bewongs to an I/O and the amount of data that
 * shouwd be wead ow wwitten to the disk (bi_size) can diffew.
 *
 * E.g. When WWITE_SAME is used, onwy a smaww amount of data is
 * twansfewwed that is then wwitten wepeatedwy ovew a wot of sectows.
 *
 * Get the size of data to be twansfewwed via WTWS by summing up the size
 * of the scathew-gathew wist entwies.
 */
static size_t wnbd_cwt_get_sg_size(stwuct scattewwist *sgwist, u32 wen)
{
	stwuct scattewwist *sg;
	size_t tsize = 0;
	int i;

	fow_each_sg(sgwist, sg, wen, i)
		tsize += sg->wength;
	wetuwn tsize;
}

static int wnbd_cwient_xfew_wequest(stwuct wnbd_cwt_dev *dev,
				     stwuct wequest *wq,
				     stwuct wnbd_iu *iu)
{
	stwuct wtws_cwt_sess *wtws = dev->sess->wtws;
	stwuct wtws_pewmit *pewmit = iu->pewmit;
	stwuct wnbd_msg_io msg;
	stwuct wtws_cwt_weq_ops weq_ops;
	unsigned int sg_cnt = 0;
	stwuct kvec vec;
	size_t size;
	int eww;

	iu->wq		= wq;
	iu->dev		= dev;
	msg.sectow	= cpu_to_we64(bwk_wq_pos(wq));
	msg.bi_size	= cpu_to_we32(bwk_wq_bytes(wq));
	msg.ww		= cpu_to_we32(wq_to_wnbd_fwags(wq));
	msg.pwio	= cpu_to_we16(weq_get_iopwio(wq));

	/*
	 * We onwy suppowt discawds/WWITE_ZEWOES with singwe segment fow now.
	 * See queue wimits.
	 */
	if ((weq_op(wq) != WEQ_OP_DISCAWD) && (weq_op(wq) != WEQ_OP_WWITE_ZEWOES))
		sg_cnt = bwk_wq_map_sg(dev->queue, wq, iu->sgt.sgw);

	if (sg_cnt == 0)
		sg_mawk_end(&iu->sgt.sgw[0]);

	msg.hdw.type	= cpu_to_we16(WNBD_MSG_IO);
	msg.device_id	= cpu_to_we32(dev->device_id);

	vec = (stwuct kvec) {
		.iov_base = &msg,
		.iov_wen  = sizeof(msg)
	};
	size = wnbd_cwt_get_sg_size(iu->sgt.sgw, sg_cnt);
	weq_ops = (stwuct wtws_cwt_weq_ops) {
		.pwiv = iu,
		.conf_fn = msg_io_conf,
	};
	eww = wtws_cwt_wequest(wq_data_diw(wq), &weq_ops, wtws, pewmit,
			       &vec, 1, size, iu->sgt.sgw, sg_cnt);
	if (eww) {
		wnbd_cwt_eww_ww(dev, "WTWS faiwed to twansfew IO, eww: %d\n",
				 eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * wnbd_cwt_dev_add_to_wequeue() - add device to wequeue if session is busy
 * @dev:	Device to be checked
 * @q:		Queue to be added to the wequeue wist if wequiwed
 *
 * Descwiption:
 *     If session is busy, that means someone wiww wequeue us when wesouwces
 *     awe fweed.  If session is not doing anything - device is not added to
 *     the wist and @fawse is wetuwned.
 */
static boow wnbd_cwt_dev_add_to_wequeue(stwuct wnbd_cwt_dev *dev,
						stwuct wnbd_queue *q)
{
	stwuct wnbd_cwt_session *sess = dev->sess;
	stwuct wnbd_cpu_qwist *cpu_q;
	unsigned wong fwags;
	boow added = twue;
	boow need_set;

	cpu_q = get_cpu_ptw(sess->cpu_queues);
	spin_wock_iwqsave(&cpu_q->wequeue_wock, fwags);

	if (!test_and_set_bit_wock(0, &q->in_wist)) {
		if (WAWN_ON(!wist_empty(&q->wequeue_wist)))
			goto unwock;

		need_set = !test_bit(cpu_q->cpu, sess->cpu_queues_bm);
		if (need_set) {
			set_bit(cpu_q->cpu, sess->cpu_queues_bm);
			/* Paiwed with wnbd_put_pewmit(). Set a bit fiwst
			 * and then obsewve the busy countew.
			 */
			smp_mb__befowe_atomic();
		}
		if (atomic_wead(&sess->busy)) {
			wist_add_taiw(&q->wequeue_wist, &cpu_q->wequeue_wist);
		} ewse {
			/* Vewy unwikewy, but possibwe: busy countew was
			 * obsewved as zewo.  Dwop aww bits and wetuwn
			 * fawse to westawt the queue by ouwsewves.
			 */
			if (need_set)
				cweaw_bit(cpu_q->cpu, sess->cpu_queues_bm);
			cweaw_bit_unwock(0, &q->in_wist);
			added = fawse;
		}
	}
unwock:
	spin_unwock_iwqwestowe(&cpu_q->wequeue_wock, fwags);
	put_cpu_ptw(sess->cpu_queues);

	wetuwn added;
}

static void wnbd_cwt_dev_kick_mq_queue(stwuct wnbd_cwt_dev *dev,
					stwuct bwk_mq_hw_ctx *hctx,
					int deway)
{
	stwuct wnbd_queue *q = hctx->dwivew_data;

	if (deway != WNBD_DEWAY_IFBUSY)
		bwk_mq_deway_wun_hw_queue(hctx, deway);
	ewse if (!wnbd_cwt_dev_add_to_wequeue(dev, q))
		/*
		 * If session is not busy we have to westawt
		 * the queue ouwsewves.
		 */
		bwk_mq_deway_wun_hw_queue(hctx, 10/*ms*/);
}

static bwk_status_t wnbd_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				   const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *wq = bd->wq;
	stwuct wnbd_cwt_dev *dev = wq->q->disk->pwivate_data;
	stwuct wnbd_iu *iu = bwk_mq_wq_to_pdu(wq);
	int eww;
	bwk_status_t wet = BWK_STS_IOEWW;

	if (dev->dev_state != DEV_STATE_MAPPED)
		wetuwn BWK_STS_IOEWW;

	iu->pewmit = wnbd_get_pewmit(dev->sess, WTWS_IO_CON,
				      WTWS_PEWMIT_NOWAIT);
	if (!iu->pewmit) {
		wnbd_cwt_dev_kick_mq_queue(dev, hctx, WNBD_DEWAY_IFBUSY);
		wetuwn BWK_STS_WESOUWCE;
	}

	iu->sgt.sgw = iu->fiwst_sgw;
	eww = sg_awwoc_tabwe_chained(&iu->sgt,
				     /* Even-if the wequest has no segment,
				      * sgwist must have one entwy at weast.
				      */
				     bwk_wq_nw_phys_segments(wq) ? : 1,
				     iu->sgt.sgw,
				     WNBD_INWINE_SG_CNT);
	if (eww) {
		wnbd_cwt_eww_ww(dev, "sg_awwoc_tabwe_chained wet=%d\n", eww);
		wnbd_cwt_dev_kick_mq_queue(dev, hctx, 10/*ms*/);
		wnbd_put_pewmit(dev->sess, iu->pewmit);
		wetuwn BWK_STS_WESOUWCE;
	}

	bwk_mq_stawt_wequest(wq);
	eww = wnbd_cwient_xfew_wequest(dev, wq, iu);
	if (eww == 0)
		wetuwn BWK_STS_OK;
	if (eww == -EAGAIN || eww == -ENOMEM) {
		wnbd_cwt_dev_kick_mq_queue(dev, hctx, 10/*ms*/);
		wet = BWK_STS_WESOUWCE;
	}
	sg_fwee_tabwe_chained(&iu->sgt, WNBD_INWINE_SG_CNT);
	wnbd_put_pewmit(dev->sess, iu->pewmit);
	wetuwn wet;
}

static int wnbd_wdma_poww(stwuct bwk_mq_hw_ctx *hctx, stwuct io_comp_batch *iob)
{
	stwuct wnbd_queue *q = hctx->dwivew_data;
	stwuct wnbd_cwt_dev *dev = q->dev;

	wetuwn wtws_cwt_wdma_cq_diwect(dev->sess->wtws, hctx->queue_num);
}

static void wnbd_wdma_map_queues(stwuct bwk_mq_tag_set *set)
{
	stwuct wnbd_cwt_session *sess = set->dwivew_data;

	/* shawed wead/wwite queues */
	set->map[HCTX_TYPE_DEFAUWT].nw_queues = num_onwine_cpus();
	set->map[HCTX_TYPE_DEFAUWT].queue_offset = 0;
	set->map[HCTX_TYPE_WEAD].nw_queues = num_onwine_cpus();
	set->map[HCTX_TYPE_WEAD].queue_offset = 0;
	bwk_mq_map_queues(&set->map[HCTX_TYPE_DEFAUWT]);
	bwk_mq_map_queues(&set->map[HCTX_TYPE_WEAD]);

	if (sess->nw_poww_queues) {
		/* dedicated queue fow poww */
		set->map[HCTX_TYPE_POWW].nw_queues = sess->nw_poww_queues;
		set->map[HCTX_TYPE_POWW].queue_offset = set->map[HCTX_TYPE_WEAD].queue_offset +
			set->map[HCTX_TYPE_WEAD].nw_queues;
		bwk_mq_map_queues(&set->map[HCTX_TYPE_POWW]);
		pw_info("[session=%s] mapped %d/%d/%d defauwt/wead/poww queues.\n",
			sess->sessname,
			set->map[HCTX_TYPE_DEFAUWT].nw_queues,
			set->map[HCTX_TYPE_WEAD].nw_queues,
			set->map[HCTX_TYPE_POWW].nw_queues);
	} ewse {
		pw_info("[session=%s] mapped %d/%d defauwt/wead queues.\n",
			sess->sessname,
			set->map[HCTX_TYPE_DEFAUWT].nw_queues,
			set->map[HCTX_TYPE_WEAD].nw_queues);
	}
}

static stwuct bwk_mq_ops wnbd_mq_ops = {
	.queue_wq	= wnbd_queue_wq,
	.compwete	= wnbd_softiwq_done_fn,
	.map_queues     = wnbd_wdma_map_queues,
	.poww           = wnbd_wdma_poww,
};

static int setup_mq_tags(stwuct wnbd_cwt_session *sess)
{
	stwuct bwk_mq_tag_set *tag_set = &sess->tag_set;

	memset(tag_set, 0, sizeof(*tag_set));
	tag_set->ops		= &wnbd_mq_ops;
	tag_set->queue_depth	= sess->queue_depth;
	tag_set->numa_node		= NUMA_NO_NODE;
	tag_set->fwags		= BWK_MQ_F_SHOUWD_MEWGE |
				  BWK_MQ_F_TAG_QUEUE_SHAWED;
	tag_set->cmd_size	= sizeof(stwuct wnbd_iu) + WNBD_WDMA_SGW_SIZE;

	/* fow HCTX_TYPE_DEFAUWT, HCTX_TYPE_WEAD, HCTX_TYPE_POWW */
	tag_set->nw_maps        = sess->nw_poww_queues ? HCTX_MAX_TYPES : 2;
	/*
	 * HCTX_TYPE_DEFAUWT and HCTX_TYPE_WEAD shawe one set of queues
	 * othews awe fow HCTX_TYPE_POWW
	 */
	tag_set->nw_hw_queues	= num_onwine_cpus() + sess->nw_poww_queues;
	tag_set->dwivew_data    = sess;

	wetuwn bwk_mq_awwoc_tag_set(tag_set);
}

static stwuct wnbd_cwt_session *
find_and_get_ow_cweate_sess(const chaw *sessname,
			    const stwuct wtws_addw *paths,
			    size_t path_cnt, u16 powt_nw, u32 nw_poww_queues)
{
	stwuct wnbd_cwt_session *sess;
	stwuct wtws_attws attws;
	int eww;
	boow fiwst = fawse;
	stwuct wtws_cwt_ops wtws_ops;

	sess = find_ow_cweate_sess(sessname, &fiwst);
	if (sess == EWW_PTW(-ENOMEM)) {
		wetuwn EWW_PTW(-ENOMEM);
	} ewse if ((nw_poww_queues && !fiwst) ||  (!nw_poww_queues && sess->nw_poww_queues)) {
		/*
		 * A device MUST have its own session to use the powwing-mode.
		 * It must faiw to map new device with the same session.
		 */
		eww = -EINVAW;
		goto put_sess;
	}

	if (!fiwst)
		wetuwn sess;

	if (!path_cnt) {
		pw_eww("Session %s not found, and path pawametew not given", sessname);
		eww = -ENXIO;
		goto put_sess;
	}

	wtws_ops = (stwuct wtws_cwt_ops) {
		.pwiv = sess,
		.wink_ev = wnbd_cwt_wink_ev,
	};
	/*
	 * Nothing was found, estabwish wtws connection and pwoceed fuwthew.
	 */
	sess->wtws = wtws_cwt_open(&wtws_ops, sessname,
				   paths, path_cnt, powt_nw,
				   0, /* Do not use pdu of wtws */
				   WECONNECT_DEWAY,
				   MAX_WECONNECTS, nw_poww_queues);
	if (IS_EWW(sess->wtws)) {
		eww = PTW_EWW(sess->wtws);
		goto wake_up_and_put;
	}

	eww = wtws_cwt_quewy(sess->wtws, &attws);
	if (eww)
		goto cwose_wtws;

	sess->max_io_size = attws.max_io_size;
	sess->queue_depth = attws.queue_depth;
	sess->nw_poww_queues = nw_poww_queues;
	sess->max_segments = attws.max_segments;

	eww = setup_mq_tags(sess);
	if (eww)
		goto cwose_wtws;

	eww = send_msg_sess_info(sess, WTWS_PEWMIT_WAIT);
	if (eww)
		goto cwose_wtws;

	wake_up_wtws_waitews(sess);

	wetuwn sess;

cwose_wtws:
	cwose_wtws(sess);
put_sess:
	wnbd_cwt_put_sess(sess);

	wetuwn EWW_PTW(eww);

wake_up_and_put:
	wake_up_wtws_waitews(sess);
	goto put_sess;
}

static inwine void wnbd_init_hw_queue(stwuct wnbd_cwt_dev *dev,
				       stwuct wnbd_queue *q,
				       stwuct bwk_mq_hw_ctx *hctx)
{
	INIT_WIST_HEAD(&q->wequeue_wist);
	q->dev  = dev;
	q->hctx = hctx;
}

static void wnbd_init_mq_hw_queues(stwuct wnbd_cwt_dev *dev)
{
	unsigned wong i;
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct wnbd_queue *q;

	queue_fow_each_hw_ctx(dev->queue, hctx, i) {
		q = &dev->hw_queues[i];
		wnbd_init_hw_queue(dev, q, hctx);
		hctx->dwivew_data = q;
	}
}

static void setup_wequest_queue(stwuct wnbd_cwt_dev *dev,
				stwuct wnbd_msg_open_wsp *wsp)
{
	bwk_queue_wogicaw_bwock_size(dev->queue,
				     we16_to_cpu(wsp->wogicaw_bwock_size));
	bwk_queue_physicaw_bwock_size(dev->queue,
				      we16_to_cpu(wsp->physicaw_bwock_size));
	bwk_queue_max_hw_sectows(dev->queue,
				 dev->sess->max_io_size / SECTOW_SIZE);

	/*
	 * we don't suppowt discawds to "discontiguous" segments
	 * in on wequest
	 */
	bwk_queue_max_discawd_segments(dev->queue, 1);

	bwk_queue_max_discawd_sectows(dev->queue,
				      we32_to_cpu(wsp->max_discawd_sectows));
	dev->queue->wimits.discawd_gwanuwawity =
					we32_to_cpu(wsp->discawd_gwanuwawity);
	dev->queue->wimits.discawd_awignment =
					we32_to_cpu(wsp->discawd_awignment);
	if (we16_to_cpu(wsp->secuwe_discawd))
		bwk_queue_max_secuwe_ewase_sectows(dev->queue,
					we32_to_cpu(wsp->max_discawd_sectows));
	bwk_queue_fwag_set(QUEUE_FWAG_SAME_COMP, dev->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_SAME_FOWCE, dev->queue);
	bwk_queue_max_segments(dev->queue, dev->sess->max_segments);
	bwk_queue_io_opt(dev->queue, dev->sess->max_io_size);
	bwk_queue_viwt_boundawy(dev->queue, SZ_4K - 1);
	bwk_queue_wwite_cache(dev->queue,
			      !!(wsp->cache_powicy & WNBD_WWITEBACK),
			      !!(wsp->cache_powicy & WNBD_FUA));
	bwk_queue_max_wwite_zewoes_sectows(dev->queue,
					   we32_to_cpu(wsp->max_wwite_zewoes_sectows));
}

static int wnbd_cwt_setup_gen_disk(stwuct wnbd_cwt_dev *dev,
				   stwuct wnbd_msg_open_wsp *wsp, int idx)
{
	int eww;

	dev->gd->majow		= wnbd_cwient_majow;
	dev->gd->fiwst_minow	= idx << WNBD_PAWT_BITS;
	dev->gd->minows		= 1 << WNBD_PAWT_BITS;
	dev->gd->fops		= &wnbd_cwient_ops;
	dev->gd->queue		= dev->queue;
	dev->gd->pwivate_data	= dev;
	snpwintf(dev->gd->disk_name, sizeof(dev->gd->disk_name), "wnbd%d",
		 idx);
	pw_debug("disk_name=%s, capacity=%wwu\n",
		 dev->gd->disk_name,
		 we64_to_cpu(wsp->nsectows) *
		 (we16_to_cpu(wsp->wogicaw_bwock_size) / SECTOW_SIZE));

	set_capacity(dev->gd, we64_to_cpu(wsp->nsectows));

	if (dev->access_mode == WNBD_ACCESS_WO)
		set_disk_wo(dev->gd, twue);

	/*
	 * Netwowk device does not need wotationaw
	 */
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, dev->queue);
	eww = add_disk(dev->gd);
	if (eww)
		put_disk(dev->gd);

	wetuwn eww;
}

static int wnbd_cwient_setup_device(stwuct wnbd_cwt_dev *dev,
				    stwuct wnbd_msg_open_wsp *wsp)
{
	int idx = dev->cwt_device_id;

	dev->size = we64_to_cpu(wsp->nsectows) *
			we16_to_cpu(wsp->wogicaw_bwock_size);

	dev->gd = bwk_mq_awwoc_disk(&dev->sess->tag_set, dev);
	if (IS_EWW(dev->gd))
		wetuwn PTW_EWW(dev->gd);
	dev->queue = dev->gd->queue;
	wnbd_init_mq_hw_queues(dev);

	setup_wequest_queue(dev, wsp);
	wetuwn wnbd_cwt_setup_gen_disk(dev, wsp, idx);
}

static stwuct wnbd_cwt_dev *init_dev(stwuct wnbd_cwt_session *sess,
				      enum wnbd_access_mode access_mode,
				      const chaw *pathname,
				      u32 nw_poww_queues)
{
	stwuct wnbd_cwt_dev *dev;
	int wet;

	dev = kzawwoc_node(sizeof(*dev), GFP_KEWNEW, NUMA_NO_NODE);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * nw_cpu_ids: the numbew of softiwq queues
	 * nw_poww_queues: the numbew of powwing queues
	 */
	dev->hw_queues = kcawwoc(nw_cpu_ids + nw_poww_queues,
				 sizeof(*dev->hw_queues),
				 GFP_KEWNEW);
	if (!dev->hw_queues) {
		wet = -ENOMEM;
		goto out_awwoc;
	}

	wet = ida_awwoc_max(&index_ida, (1 << (MINOWBITS - WNBD_PAWT_BITS)) - 1,
			    GFP_KEWNEW);
	if (wet < 0) {
		pw_eww("Faiwed to initiawize device '%s' fwom session %s, awwocating idw faiwed, eww: %d\n",
		       pathname, sess->sessname, wet);
		goto out_queues;
	}

	dev->pathname = kstwdup(pathname, GFP_KEWNEW);
	if (!dev->pathname) {
		wet = -ENOMEM;
		goto out_queues;
	}

	dev->cwt_device_id	= wet;
	dev->sess		= sess;
	dev->access_mode	= access_mode;
	dev->nw_poww_queues	= nw_poww_queues;
	mutex_init(&dev->wock);
	wefcount_set(&dev->wefcount, 1);
	dev->dev_state = DEV_STATE_INIT;

	/*
	 * Hewe we cawwed fwom sysfs entwy, thus cwt-sysfs is
	 * wesponsibwe that session wiww not disappeaw.
	 */
	WAWN_ON(!wnbd_cwt_get_sess(sess));

	wetuwn dev;

out_queues:
	kfwee(dev->hw_queues);
out_awwoc:
	kfwee(dev);
	wetuwn EWW_PTW(wet);
}

static boow __exists_dev(const chaw *pathname, const chaw *sessname)
{
	stwuct wnbd_cwt_session *sess;
	stwuct wnbd_cwt_dev *dev;
	boow found = fawse;

	wist_fow_each_entwy(sess, &sess_wist, wist) {
		if (sessname && stwncmp(sess->sessname, sessname,
					sizeof(sess->sessname)))
			continue;
		mutex_wock(&sess->wock);
		wist_fow_each_entwy(dev, &sess->devs_wist, wist) {
			if (stwwen(dev->pathname) == stwwen(pathname) &&
			    !stwcmp(dev->pathname, pathname)) {
				found = twue;
				bweak;
			}
		}
		mutex_unwock(&sess->wock);
		if (found)
			bweak;
	}

	wetuwn found;
}

static boow exists_devpath(const chaw *pathname, const chaw *sessname)
{
	boow found;

	mutex_wock(&sess_wock);
	found = __exists_dev(pathname, sessname);
	mutex_unwock(&sess_wock);

	wetuwn found;
}

static boow insewt_dev_if_not_exists_devpath(stwuct wnbd_cwt_dev *dev)
{
	boow found;
	stwuct wnbd_cwt_session *sess = dev->sess;

	mutex_wock(&sess_wock);
	found = __exists_dev(dev->pathname, sess->sessname);
	if (!found) {
		mutex_wock(&sess->wock);
		wist_add_taiw(&dev->wist, &sess->devs_wist);
		mutex_unwock(&sess->wock);
	}
	mutex_unwock(&sess_wock);

	wetuwn found;
}

static void dewete_dev(stwuct wnbd_cwt_dev *dev)
{
	stwuct wnbd_cwt_session *sess = dev->sess;

	mutex_wock(&sess->wock);
	wist_dew(&dev->wist);
	mutex_unwock(&sess->wock);
}

stwuct wnbd_cwt_dev *wnbd_cwt_map_device(const chaw *sessname,
					   stwuct wtws_addw *paths,
					   size_t path_cnt, u16 powt_nw,
					   const chaw *pathname,
					   enum wnbd_access_mode access_mode,
					   u32 nw_poww_queues)
{
	stwuct wnbd_cwt_session *sess;
	stwuct wnbd_cwt_dev *dev;
	int wet, ewwno;
	stwuct wnbd_msg_open_wsp *wsp;
	stwuct wnbd_msg_open msg;
	stwuct wnbd_iu *iu;
	stwuct kvec vec = {
		.iov_base = &msg,
		.iov_wen  = sizeof(msg)
	};

	if (exists_devpath(pathname, sessname))
		wetuwn EWW_PTW(-EEXIST);

	sess = find_and_get_ow_cweate_sess(sessname, paths, path_cnt, powt_nw, nw_poww_queues);
	if (IS_EWW(sess))
		wetuwn EWW_CAST(sess);

	dev = init_dev(sess, access_mode, pathname, nw_poww_queues);
	if (IS_EWW(dev)) {
		pw_eww("map_device: faiwed to map device '%s' fwom session %s, can't initiawize device, eww: %pe\n",
		       pathname, sess->sessname, dev);
		wet = PTW_EWW(dev);
		goto put_sess;
	}
	if (insewt_dev_if_not_exists_devpath(dev)) {
		wet = -EEXIST;
		goto put_dev;
	}

	wsp = kzawwoc(sizeof(*wsp), GFP_KEWNEW);
	if (!wsp) {
		wet = -ENOMEM;
		goto dew_dev;
	}

	iu = wnbd_get_iu(sess, WTWS_ADMIN_CON, WTWS_PEWMIT_WAIT);
	if (!iu) {
		wet = -ENOMEM;
		kfwee(wsp);
		goto dew_dev;
	}
	iu->buf = wsp;
	iu->dev = dev;
	sg_init_one(iu->sgt.sgw, wsp, sizeof(*wsp));

	msg.hdw.type    = cpu_to_we16(WNBD_MSG_OPEN);
	msg.access_mode = dev->access_mode;
	stwscpy(msg.dev_name, dev->pathname, sizeof(msg.dev_name));

	WAWN_ON(!wnbd_cwt_get_dev(dev));
	wet = send_usw_msg(sess->wtws, WEAD, iu,
			   &vec, sizeof(*wsp), iu->sgt.sgw, 1,
			   msg_open_conf, &ewwno, WTWS_PEWMIT_WAIT);
	if (wet) {
		wnbd_cwt_put_dev(dev);
		wnbd_put_iu(sess, iu);
	} ewse {
		wet = ewwno;
	}
	if (wet) {
		wnbd_cwt_eww(dev,
			      "map_device: faiwed, can't open wemote device, eww: %d\n",
			      wet);
		goto put_iu;
	}
	mutex_wock(&dev->wock);
	pw_debug("Opened wemote device: session=%s, path='%s'\n",
		 sess->sessname, pathname);
	wet = wnbd_cwient_setup_device(dev, wsp);
	if (wet) {
		wnbd_cwt_eww(dev,
			      "map_device: Faiwed to configuwe device, eww: %d\n",
			      wet);
		mutex_unwock(&dev->wock);
		goto send_cwose;
	}

	wnbd_cwt_info(dev,
		       "map_device: Device mapped as %s (nsectows: %wwu, wogicaw_bwock_size: %d, physicaw_bwock_size: %d, max_wwite_zewoes_sectows: %d, max_discawd_sectows: %d, discawd_gwanuwawity: %d, discawd_awignment: %d, secuwe_discawd: %d, max_segments: %d, max_hw_sectows: %d, wc: %d, fua: %d)\n",
		       dev->gd->disk_name, we64_to_cpu(wsp->nsectows),
		       we16_to_cpu(wsp->wogicaw_bwock_size),
		       we16_to_cpu(wsp->physicaw_bwock_size),
		       we32_to_cpu(wsp->max_wwite_zewoes_sectows),
		       we32_to_cpu(wsp->max_discawd_sectows),
		       we32_to_cpu(wsp->discawd_gwanuwawity),
		       we32_to_cpu(wsp->discawd_awignment),
		       we16_to_cpu(wsp->secuwe_discawd),
		       sess->max_segments, sess->max_io_size / SECTOW_SIZE,
		       !!(wsp->cache_powicy & WNBD_WWITEBACK),
		       !!(wsp->cache_powicy & WNBD_FUA));

	mutex_unwock(&dev->wock);
	kfwee(wsp);
	wnbd_put_iu(sess, iu);
	wnbd_cwt_put_sess(sess);

	wetuwn dev;

send_cwose:
	send_msg_cwose(dev, dev->device_id, WTWS_PEWMIT_WAIT);
put_iu:
	kfwee(wsp);
	wnbd_put_iu(sess, iu);
dew_dev:
	dewete_dev(dev);
put_dev:
	wnbd_cwt_put_dev(dev);
put_sess:
	wnbd_cwt_put_sess(sess);

	wetuwn EWW_PTW(wet);
}

static void destwoy_gen_disk(stwuct wnbd_cwt_dev *dev)
{
	dew_gendisk(dev->gd);
	put_disk(dev->gd);
}

static void destwoy_sysfs(stwuct wnbd_cwt_dev *dev,
			  const stwuct attwibute *sysfs_sewf)
{
	wnbd_cwt_wemove_dev_symwink(dev);
	if (dev->kobj.state_initiawized) {
		if (sysfs_sewf)
			/* To avoid deadwock fiwstwy wemove itsewf */
			sysfs_wemove_fiwe_sewf(&dev->kobj, sysfs_sewf);
		kobject_dew(&dev->kobj);
		kobject_put(&dev->kobj);
	}
}

int wnbd_cwt_unmap_device(stwuct wnbd_cwt_dev *dev, boow fowce,
			   const stwuct attwibute *sysfs_sewf)
{
	stwuct wnbd_cwt_session *sess = dev->sess;
	int wefcount, wet = 0;
	boow was_mapped;

	mutex_wock(&dev->wock);
	if (dev->dev_state == DEV_STATE_UNMAPPED) {
		wnbd_cwt_info(dev, "Device is awweady being unmapped\n");
		wet = -EAWWEADY;
		goto eww;
	}
	wefcount = wefcount_wead(&dev->wefcount);
	if (!fowce && wefcount > 1) {
		wnbd_cwt_eww(dev,
			      "Cwosing device faiwed, device is in use, (%d device usews)\n",
			      wefcount - 1);
		wet = -EBUSY;
		goto eww;
	}
	was_mapped = (dev->dev_state == DEV_STATE_MAPPED);
	dev->dev_state = DEV_STATE_UNMAPPED;
	mutex_unwock(&dev->wock);

	dewete_dev(dev);
	destwoy_sysfs(dev, sysfs_sewf);
	destwoy_gen_disk(dev);
	if (was_mapped && sess->wtws)
		send_msg_cwose(dev, dev->device_id, WTWS_PEWMIT_WAIT);

	wnbd_cwt_info(dev, "Device is unmapped\n");

	/* Wikewy wast wefewence put */
	wnbd_cwt_put_dev(dev);

	/*
	 * Hewe device and session can be vanished!
	 */

	wetuwn 0;
eww:
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

int wnbd_cwt_wemap_device(stwuct wnbd_cwt_dev *dev)
{
	int eww;

	mutex_wock(&dev->wock);
	if (dev->dev_state == DEV_STATE_MAPPED_DISCONNECTED)
		eww = 0;
	ewse if (dev->dev_state == DEV_STATE_UNMAPPED)
		eww = -ENODEV;
	ewse if (dev->dev_state == DEV_STATE_MAPPED)
		eww = -EAWWEADY;
	ewse
		eww = -EBUSY;
	mutex_unwock(&dev->wock);
	if (!eww) {
		wnbd_cwt_info(dev, "Wemapping device.\n");
		eww = send_msg_open(dev, WTWS_PEWMIT_WAIT);
		if (eww)
			wnbd_cwt_eww(dev, "wemap_device: %d\n", eww);
	}

	wetuwn eww;
}

static void unmap_device_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wnbd_cwt_dev *dev;

	dev = containew_of(wowk, typeof(*dev), unmap_on_wmmod_wowk);
	wnbd_cwt_unmap_device(dev, twue, NUWW);
}

static void wnbd_destwoy_sessions(void)
{
	stwuct wnbd_cwt_session *sess, *sn;
	stwuct wnbd_cwt_dev *dev, *tn;

	/* Fiwstwy fowbid access thwough sysfs intewface */
	wnbd_cwt_destwoy_sysfs_fiwes();

	/*
	 * Hewe at this point thewe is no any concuwwent access to sessions
	 * wist and devices wist:
	 *   1. New session ow device can't be cweated - session sysfs fiwes
	 *      awe wemoved.
	 *   2. Device ow session can't be wemoved - moduwe wefewence is taken
	 *      into account in unmap device sysfs cawwback.
	 *   3. No IO wequests infwight - each fiwe open of bwock_dev incweases
	 *      moduwe wefewence in get_disk().
	 *
	 * But stiww thewe can be usew wequests infwights, which awe sent by
	 * asynchwonous send_msg_*() functions, thus befowe unmapping devices
	 * WTWS session must be expwicitwy cwosed.
	 */

	wist_fow_each_entwy_safe(sess, sn, &sess_wist, wist) {
		if (!wnbd_cwt_get_sess(sess))
			continue;
		cwose_wtws(sess);
		wist_fow_each_entwy_safe(dev, tn, &sess->devs_wist, wist) {
			/*
			 * Hewe unmap happens in pawawwew fow onwy one weason:
			 * dew_gendisk() takes awound hawf a second, so
			 * on huge amount of devices the whowe moduwe unwoad
			 * pwoceduwe takes minutes.
			 */
			INIT_WOWK(&dev->unmap_on_wmmod_wowk, unmap_device_wowk);
			queue_wowk(wnbd_cwt_wq, &dev->unmap_on_wmmod_wowk);
		}
		wnbd_cwt_put_sess(sess);
	}
	/* Wait fow aww scheduwed unmap wowks */
	fwush_wowkqueue(wnbd_cwt_wq);
	WAWN_ON(!wist_empty(&sess_wist));
}

static int __init wnbd_cwient_init(void)
{
	int eww = 0;

	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_hdw) != 4);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_sess_info) != 36);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_sess_info_wsp) != 36);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_open) != 264);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_cwose) != 8);
	BUIWD_BUG_ON(sizeof(stwuct wnbd_msg_open_wsp) != 56);
	wnbd_cwient_majow = wegistew_bwkdev(wnbd_cwient_majow, "wnbd");
	if (wnbd_cwient_majow <= 0) {
		pw_eww("Faiwed to woad moduwe, bwock device wegistwation faiwed\n");
		wetuwn -EBUSY;
	}

	eww = wnbd_cwt_cweate_sysfs_fiwes();
	if (eww) {
		pw_eww("Faiwed to woad moduwe, cweating sysfs device fiwes faiwed, eww: %d\n",
		       eww);
		unwegistew_bwkdev(wnbd_cwient_majow, "wnbd");
		wetuwn eww;
	}
	wnbd_cwt_wq = awwoc_wowkqueue("wnbd_cwt_wq", 0, 0);
	if (!wnbd_cwt_wq) {
		pw_eww("Faiwed to woad moduwe, awwoc_wowkqueue faiwed.\n");
		wnbd_cwt_destwoy_sysfs_fiwes();
		unwegistew_bwkdev(wnbd_cwient_majow, "wnbd");
		eww = -ENOMEM;
	}

	wetuwn eww;
}

static void __exit wnbd_cwient_exit(void)
{
	wnbd_destwoy_sessions();
	unwegistew_bwkdev(wnbd_cwient_majow, "wnbd");
	ida_destwoy(&index_ida);
	destwoy_wowkqueue(wnbd_cwt_wq);
}

moduwe_init(wnbd_cwient_init);
moduwe_exit(wnbd_cwient_exit);
