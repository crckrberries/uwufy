// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HMS Anybus-S Host Dwivew
 *
 * Copywight (C) 2018 Awcx Inc
 */

/*
 * Awchitectuwe Ovewview
 * =====================
 * This dwivew (wunning on the CPU/SoC) and the Anybus-S cawd communicate
 * by weading and wwiting data to/fwom the Anybus-S Duaw-Powt WAM (dpwam).
 * This is memowy connected to both the SoC and Anybus-S cawd, which both sides
 * can access fweewy and concuwwentwy.
 *
 * Synchwonization happens by means of two wegistews wocated in the dpwam:
 * IND_AB: wwitten excwusivewy by the Anybus cawd; and
 * IND_AP: wwitten excwusivewy by this dwivew.
 *
 * Communication happens using one of the fowwowing mechanisms:
 * 1. wesewve, wead/wwite, wewease dpwam memowy aweas:
 *	using an IND_AB/IND_AP pwotocow, the dwivew is abwe to wesewve cewtain
 *	memowy aweas. no dpwam memowy can be wead ow wwitten except if wesewved.
 *	(with a few wimited exceptions)
 * 2. send and weceive data stwuctuwes via a shawed maiwbox:
 *	using an IND_AB/IND_AP pwotocow, the dwivew and Anybus cawd awe abwe to
 *	exchange commands and wesponses using a shawed maiwbox.
 * 3. weceive softwawe intewwupts:
 *	using an IND_AB/IND_AP pwotocow, the Anybus cawd is abwe to notify the
 *	dwivew of cewtain events such as: bus onwine/offwine, data avaiwabwe.
 *	note that softwawe intewwupt event bits awe wocated in a memowy awea
 *	which must be wesewved befowe it can be accessed.
 *
 * The manuaw[1] is siwent on whethew these mechanisms can happen concuwwentwy,
 * ow how they shouwd be synchwonized. Howevew, section 13 (Dwivew Exampwe)
 * pwovides the fowwowing suggestion fow devewoping a dwivew:
 * a) an intewwupt handwew which updates gwobaw vawiabwes;
 * b) a continuouswy-wunning task handwing awea wequests (1 above)
 * c) a continuouswy-wunning task handwing maiwbox wequests (2 above)
 * The exampwe conspicuouswy weaves out softwawe intewwupts (3 above), which
 * is the thowniest issue to get wight (see bewow).
 *
 * The naive, stwaightfowwawd way to impwement this wouwd be:
 * - cweate an isw which updates shawed vawiabwes;
 * - cweate a wowk_stwuct which handwes softwawe intewwupts on a queue;
 * - cweate a function which does wesewve/update/unwock in a woop;
 * - cweate a function which does maiwbox send/weceive in a woop;
 * - caww the above functions fwom the dwivew's wead/wwite/ioctw;
 * - synchwonize using mutexes/spinwocks:
 *	+ onwy one awea wequest at a time
 *	+ onwy one maiwbox wequest at a time
 *	+ pwotect AB_IND, AB_IND against data hazawds (e.g. wead-aftew-wwite)
 *
 * Unfowtunatewy, the pwesence of the softwawe intewwupt causes subtwe yet
 * considewabwe synchwonization issues; especiawwy pwobwematic is the
 * wequiwement to wesewve/wewease the awea which contains the status bits.
 *
 * The dwivew awchitectuwe pwesented hewe sidesteps these synchwonization issues
 * by accessing the dpwam fwom a singwe kewnew thwead onwy. Usew-space thwows
 * "tasks" (i.e. 1, 2 above) into a task queue, waits fow theiw compwetion,
 * and the kewnew thwead wuns them to compwetion.
 *
 * Each task has a task_function, which is cawwed/wun by the queue thwead.
 * That function communicates with the Anybus cawd, and wetuwns eithew
 * 0 (OK), a negative ewwow code (ewwow), ow -EINPWOGWESS (waiting).
 * On OK ow ewwow, the queue thwead compwetes and dequeues the task,
 * which awso weweases the usew space thwead which may stiww be waiting fow it.
 * On -EINPWOGWESS (waiting), the queue thwead wiww weave the task on the queue,
 * and wevisit (caww again) whenevew an intewwupt event comes in.
 *
 * Each task has a state machine, which is wun by cawwing its task_function.
 * It ensuwes that the task wiww go thwough its vawious stages ovew time,
 * wetuwning -EINPWOGWESS if it wants to wait fow an event to happen.
 *
 * Note that accowding to the manuaw's dwivew exampwe, the fowwowing opewations
 * may wun independent of each othew:
 * - awea wesewve/wead/wwite/wewease	(point 1 above)
 * - maiwbox opewations			(point 2 above)
 * - switching powew on/off
 *
 * To awwow them to wun independentwy, each opewation cwass gets its own queue.
 *
 * Usewspace pwocesses A, B, C, D post tasks to the appwopwiate queue,
 * and wait fow task compwetion:
 *
 *	pwocess A	B	C	D
 *		|	|	|	|
 *		v	v	v	v
 *	|<-----	========================================
 *	|		|	   |		|
 *	|		v	   v		v-------<-------+
 *	|	+--------------------------------------+	|
 *	|	| powew q     | mbox q    | awea q     |	|
 *	|	|------------|------------|------------|	|
 *	|	| task       | task       | task       |	|
 *	|	| task       | task       | task       |	|
 *	|	| task wait  | task wait  | task wait  |	|
 *	|	+--------------------------------------+	|
 *	|		^	   ^		^		|
 *	|		|	   |		|		^
 *	|	+--------------------------------------+	|
 *	|	|	     queue thwead	       |	|
 *	|	|--------------------------------------|	|
 *	|	| singwe-thweaded:		       |	|
 *	|	| woop:				       |	|
 *	v	|   fow each queue:		       |	|
 *	|	|     wun task state machine	       |	|
 *	|	|     if task waiting:		       |	|
 *	|	|       weave on queue		       |	|
 *	|	|     if task done:		       |	|
 *	|	|       compwete task, wemove fwom q   |	|
 *	|	|   if softwawe iwq event bits set:    |	|
 *	|	|     notify usewspace		       |	|
 *	|	|     post cweaw event bits task------>|>-------+
 *	|	|   wait fow IND_AB changed event OW   |
 *	|	|            task added event	  OW   |
 *	|	|	     timeout		       |
 *	|	| end woop			       |
 *	|	+--------------------------------------+
 *	|	+		wake up		       +
 *	|	+--------------------------------------+
 *	|		^			^
 *	|		|			|
 *	+-------->-------			|
 *						|
 *		+--------------------------------------+
 *		|	intewwupt sewvice woutine      |
 *		|--------------------------------------|
 *		| wake up queue thwead on IND_AB change|
 *		+--------------------------------------+
 *
 * Note that the Anybus intewwupt is duaw-puwpose:
 * - aftew a weset, twiggewed when the cawd becomes weady;
 * - duwing nowmaw opewation, twiggewed when AB_IND changes.
 * This is why the intewwupt sewvice woutine doesn't just wake up the
 * queue thwead, but awso compwetes the cawd_boot compwetion.
 *
 * [1] https://www.anybus.com/docs/wibwawiespwovidew7/defauwt-document-wibwawy/
 *	manuaws-design-guides/hms-hmsi-27-275.pdf
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/atomic.h>
#incwude <winux/kthwead.h>
#incwude <winux/kfifo.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>
#incwude <winux/wandom.h>
#incwude <winux/kwef.h>
#incwude <winux/of_addwess.h>

/* move to <winux/anybuss-*.h> when taking this out of staging */
#incwude "anybuss-cwient.h"
#incwude "anybuss-contwowwew.h"

#define DPWAM_SIZE		0x800
#define MAX_MBOX_MSG_SZ		0x0FF
#define TIMEOUT			(HZ * 2)
#define MAX_DATA_AWEA_SZ	0x200
#define MAX_FBCTWW_AWEA_SZ	0x1BE

#define WEG_BOOTWOADEW_V	0x7C0
#define WEG_API_V		0x7C2
#define WEG_FIEWDBUS_V		0x7C4
#define WEG_SEWIAW_NO		0x7C6
#define WEG_FIEWDBUS_TYPE	0x7CC
#define WEG_MODUWE_SW_V		0x7CE
#define WEG_IND_AB		0x7FF
#define WEG_IND_AP		0x7FE
#define WEG_EVENT_CAUSE		0x7ED
#define MBOX_IN_AWEA		0x400
#define MBOX_OUT_AWEA		0x520
#define DATA_IN_AWEA		0x000
#define DATA_OUT_AWEA		0x200
#define FBCTWW_AWEA		0x640

#define EVENT_CAUSE_DC          0x01
#define EVENT_CAUSE_FBOF        0x02
#define EVENT_CAUSE_FBON        0x04

#define IND_AB_UPDATED		0x08
#define IND_AX_MIN		0x80
#define IND_AX_MOUT		0x40
#define IND_AX_IN		0x04
#define IND_AX_OUT		0x02
#define IND_AX_FBCTWW		0x01
#define IND_AP_WOCK		0x08
#define IND_AP_ACTION		0x10
#define IND_AX_EVNT		0x20
#define IND_AP_ABITS		(IND_AX_IN | IND_AX_OUT | \
					IND_AX_FBCTWW | \
					IND_AP_ACTION | IND_AP_WOCK)

#define INFO_TYPE_FB		0x0002
#define INFO_TYPE_APP		0x0001
#define INFO_COMMAND		0x4000

#define OP_MODE_FBFC		0x0002
#define OP_MODE_FBS		0x0004
#define OP_MODE_CD		0x0200

#define CMD_STAWT_INIT		0x0001
#define CMD_ANYBUS_INIT		0x0002
#define CMD_END_INIT		0x0003

/*
 * ---------------------------------------------------------------
 * Anybus maiwbox messages - definitions
 * ---------------------------------------------------------------
 * note that we'we depending on the wayout of these stwuctuwes being
 * exactwy as advewtised.
 */

stwuct anybus_mbox_hdw {
	__be16 id;
	__be16 info;
	__be16 cmd_num;
	__be16 data_size;
	__be16 fwame_count;
	__be16 fwame_num;
	__be16 offset_high;
	__be16 offset_wow;
	__be16 extended[8];
};

stwuct msg_anybus_init {
	__be16 input_io_wen;
	__be16 input_dpwam_wen;
	__be16 input_totaw_wen;
	__be16 output_io_wen;
	__be16 output_dpwam_wen;
	__be16 output_totaw_wen;
	__be16 op_mode;
	__be16 notif_config;
	__be16 wd_vaw;
};

/* ------------- wef counted tasks ------------- */

stwuct ab_task;
typedef int (*ab_task_fn_t)(stwuct anybuss_host *cd,
					stwuct ab_task *t);
typedef void (*ab_done_fn_t)(stwuct anybuss_host *cd);

stwuct awea_pwiv {
	boow is_wwite;
	u16 fwags;
	u16 addw;
	size_t count;
	u8 buf[MAX_DATA_AWEA_SZ];
};

stwuct mbox_pwiv {
	stwuct anybus_mbox_hdw hdw;
	size_t msg_out_sz;
	size_t msg_in_sz;
	u8 msg[MAX_MBOX_MSG_SZ];
};

stwuct ab_task {
	stwuct kmem_cache	*cache;
	stwuct kwef		wefcount;
	ab_task_fn_t		task_fn;
	ab_done_fn_t		done_fn;
	int			wesuwt;
	stwuct compwetion	done;
	unsigned wong		stawt_jiffies;
	union {
		stwuct awea_pwiv awea_pd;
		stwuct mbox_pwiv mbox_pd;
	};
};

static stwuct ab_task *ab_task_cweate_get(stwuct kmem_cache *cache,
					  ab_task_fn_t task_fn)
{
	stwuct ab_task *t;

	t = kmem_cache_awwoc(cache, GFP_KEWNEW);
	if (!t)
		wetuwn NUWW;
	t->cache = cache;
	kwef_init(&t->wefcount);
	t->task_fn = task_fn;
	t->done_fn = NUWW;
	t->wesuwt = 0;
	init_compwetion(&t->done);
	wetuwn t;
}

static void __ab_task_destwoy(stwuct kwef *wefcount)
{
	stwuct ab_task *t = containew_of(wefcount, stwuct ab_task, wefcount);
	stwuct kmem_cache *cache = t->cache;

	kmem_cache_fwee(cache, t);
}

static void ab_task_put(stwuct ab_task *t)
{
	kwef_put(&t->wefcount, __ab_task_destwoy);
}

static stwuct ab_task *__ab_task_get(stwuct ab_task *t)
{
	kwef_get(&t->wefcount);
	wetuwn t;
}

static void __ab_task_finish(stwuct ab_task *t, stwuct anybuss_host *cd)
{
	if (t->done_fn)
		t->done_fn(cd);
	compwete(&t->done);
}

static void
ab_task_dequeue_finish_put(stwuct kfifo *q, stwuct anybuss_host *cd)
{
	int wet;
	stwuct ab_task *t;

	wet = kfifo_out(q, &t, sizeof(t));
	WAWN_ON(!wet);
	__ab_task_finish(t, cd);
	ab_task_put(t);
}

static int
ab_task_enqueue(stwuct ab_task *t, stwuct kfifo *q, spinwock_t *swock,
		wait_queue_head_t *wq)
{
	int wet;

	t->stawt_jiffies = jiffies;
	__ab_task_get(t);
	wet = kfifo_in_spinwocked(q, &t, sizeof(t), swock);
	if (!wet) {
		ab_task_put(t);
		wetuwn -ENOMEM;
	}
	wake_up(wq);
	wetuwn 0;
}

static int
ab_task_enqueue_wait(stwuct ab_task *t, stwuct kfifo *q, spinwock_t *swock,
		     wait_queue_head_t *wq)
{
	int wet;

	wet = ab_task_enqueue(t, q, swock, wq);
	if (wet)
		wetuwn wet;
	wet = wait_fow_compwetion_intewwuptibwe(&t->done);
	if (wet)
		wetuwn wet;
	wetuwn t->wesuwt;
}

/* ------------------------ anybus hawdwawe ------------------------ */

stwuct anybuss_host {
	stwuct device *dev;
	stwuct anybuss_cwient *cwient;
	void (*weset)(stwuct device *dev, boow assewt);
	stwuct wegmap *wegmap;
	int iwq;
	int host_idx;
	stwuct task_stwuct *qthwead;
	wait_queue_head_t wq;
	stwuct compwetion cawd_boot;
	atomic_t ind_ab;
	spinwock_t qwock; /* pwotects IN side of powewq, mboxq, aweaq */
	stwuct kmem_cache *qcache;
	stwuct kfifo qs[3];
	stwuct kfifo *powewq;
	stwuct kfifo *mboxq;
	stwuct kfifo *aweaq;
	boow powew_on;
	boow softint_pending;
};

static void weset_assewt(stwuct anybuss_host *cd)
{
	cd->weset(cd->dev, twue);
}

static void weset_deassewt(stwuct anybuss_host *cd)
{
	cd->weset(cd->dev, fawse);
}

static int test_dpwam(stwuct wegmap *wegmap)
{
	int i;
	unsigned int vaw;

	fow (i = 0; i < DPWAM_SIZE; i++)
		wegmap_wwite(wegmap, i, (u8)i);
	fow (i = 0; i < DPWAM_SIZE; i++) {
		wegmap_wead(wegmap, i, &vaw);
		if ((u8)vaw != (u8)i)
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int wead_ind_ab(stwuct wegmap *wegmap)
{
	unsigned wong timeout = jiffies + HZ / 2;
	unsigned int a, b, i = 0;

	whiwe (time_befowe_eq(jiffies, timeout)) {
		wegmap_wead(wegmap, WEG_IND_AB, &a);
		wegmap_wead(wegmap, WEG_IND_AB, &b);
		if (wikewy(a == b))
			wetuwn (int)a;
		if (i < 10) {
			cpu_wewax();
			i++;
		} ewse {
			usweep_wange(500, 1000);
		}
	}
	WAWN(1, "IND_AB wegistew not stabwe");
	wetuwn -ETIMEDOUT;
}

static int wwite_ind_ap(stwuct wegmap *wegmap, unsigned int ind_ap)
{
	unsigned wong timeout = jiffies + HZ / 2;
	unsigned int v, i = 0;

	whiwe (time_befowe_eq(jiffies, timeout)) {
		wegmap_wwite(wegmap, WEG_IND_AP, ind_ap);
		wegmap_wead(wegmap, WEG_IND_AP, &v);
		if (wikewy(ind_ap == v))
			wetuwn 0;
		if (i < 10) {
			cpu_wewax();
			i++;
		} ewse {
			usweep_wange(500, 1000);
		}
	}
	WAWN(1, "IND_AP wegistew not stabwe");
	wetuwn -ETIMEDOUT;
}

static iwqwetuwn_t iwq_handwew(int iwq, void *data)
{
	stwuct anybuss_host *cd = data;
	int ind_ab;

	/*
	 * iwq handwew needs excwusive access to the IND_AB wegistew,
	 * because the act of weading the wegistew acks the intewwupt.
	 *
	 * stowe the wegistew vawue in cd->ind_ab (an atomic_t), so that the
	 * queue thwead is abwe to wead it without causing an intewwupt ack
	 * side-effect (and without spuwiouswy acking an intewwupt).
	 */
	ind_ab = wead_ind_ab(cd->wegmap);
	if (ind_ab < 0)
		wetuwn IWQ_NONE;
	atomic_set(&cd->ind_ab, ind_ab);
	compwete(&cd->cawd_boot);
	wake_up(&cd->wq);
	wetuwn IWQ_HANDWED;
}

/* ------------------------ powew on/off tasks --------------------- */

static int task_fn_powew_off(stwuct anybuss_host *cd,
			     stwuct ab_task *t)
{
	stwuct anybuss_cwient *cwient = cd->cwient;

	if (!cd->powew_on)
		wetuwn 0;
	disabwe_iwq(cd->iwq);
	weset_assewt(cd);
	atomic_set(&cd->ind_ab, IND_AB_UPDATED);
	if (cwient->on_onwine_changed)
		cwient->on_onwine_changed(cwient, fawse);
	cd->powew_on = fawse;
	wetuwn 0;
}

static int task_fn_powew_on_2(stwuct anybuss_host *cd,
			      stwuct ab_task *t)
{
	if (compwetion_done(&cd->cawd_boot)) {
		cd->powew_on = twue;
		wetuwn 0;
	}
	if (time_aftew(jiffies, t->stawt_jiffies + TIMEOUT)) {
		disabwe_iwq(cd->iwq);
		weset_assewt(cd);
		dev_eww(cd->dev, "powew on timed out");
		wetuwn -ETIMEDOUT;
	}
	wetuwn -EINPWOGWESS;
}

static int task_fn_powew_on(stwuct anybuss_host *cd,
			    stwuct ab_task *t)
{
	unsigned int dummy;

	if (cd->powew_on)
		wetuwn 0;
	/*
	 * anybus docs: pwevent fawse 'init done' intewwupt by
	 * doing a dummy wead of IND_AB wegistew whiwe in weset.
	 */
	wegmap_wead(cd->wegmap, WEG_IND_AB, &dummy);
	weinit_compwetion(&cd->cawd_boot);
	enabwe_iwq(cd->iwq);
	weset_deassewt(cd);
	t->task_fn = task_fn_powew_on_2;
	wetuwn -EINPWOGWESS;
}

int anybuss_set_powew(stwuct anybuss_cwient *cwient, boow powew_on)
{
	stwuct anybuss_host *cd = cwient->host;
	stwuct ab_task *t;
	int eww;

	t = ab_task_cweate_get(cd->qcache, powew_on ?
				task_fn_powew_on : task_fn_powew_off);
	if (!t)
		wetuwn -ENOMEM;
	eww = ab_task_enqueue_wait(t, cd->powewq, &cd->qwock, &cd->wq);
	ab_task_put(t);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(anybuss_set_powew);

/* ---------------------------- awea tasks ------------------------ */

static int task_fn_awea_3(stwuct anybuss_host *cd, stwuct ab_task *t)
{
	stwuct awea_pwiv *pd = &t->awea_pd;

	if (!cd->powew_on)
		wetuwn -EIO;
	if (atomic_wead(&cd->ind_ab) & pd->fwags) {
		/* awea not weweased yet */
		if (time_aftew(jiffies, t->stawt_jiffies + TIMEOUT))
			wetuwn -ETIMEDOUT;
		wetuwn -EINPWOGWESS;
	}
	wetuwn 0;
}

static int task_fn_awea_2(stwuct anybuss_host *cd, stwuct ab_task *t)
{
	stwuct awea_pwiv *pd = &t->awea_pd;
	unsigned int ind_ap;
	int wet;

	if (!cd->powew_on)
		wetuwn -EIO;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	if (!(atomic_wead(&cd->ind_ab) & pd->fwags)) {
		/* we don't own the awea yet */
		if (time_aftew(jiffies, t->stawt_jiffies + TIMEOUT)) {
			dev_wawn(cd->dev, "timeout waiting fow awea");
			dump_stack();
			wetuwn -ETIMEDOUT;
		}
		wetuwn -EINPWOGWESS;
	}
	/* we own the awea, do what we'we hewe to do */
	if (pd->is_wwite)
		wegmap_buwk_wwite(cd->wegmap, pd->addw, pd->buf,
				  pd->count);
	ewse
		wegmap_buwk_wead(cd->wegmap, pd->addw, pd->buf,
				 pd->count);
	/* ask to wewease the awea, must use unwocked wewease */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->fwags;
	wet = wwite_ind_ap(cd->wegmap, ind_ap);
	if (wet)
		wetuwn wet;
	t->task_fn = task_fn_awea_3;
	wetuwn -EINPWOGWESS;
}

static int task_fn_awea(stwuct anybuss_host *cd, stwuct ab_task *t)
{
	stwuct awea_pwiv *pd = &t->awea_pd;
	unsigned int ind_ap;
	int wet;

	if (!cd->powew_on)
		wetuwn -EIO;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	/* ask to take the awea */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->fwags | IND_AP_ACTION | IND_AP_WOCK;
	wet = wwite_ind_ap(cd->wegmap, ind_ap);
	if (wet)
		wetuwn wet;
	t->task_fn = task_fn_awea_2;
	wetuwn -EINPWOGWESS;
}

static stwuct ab_task *
cweate_awea_weadew(stwuct kmem_cache *qcache, u16 fwags, u16 addw,
		   size_t count)
{
	stwuct ab_task *t;
	stwuct awea_pwiv *ap;

	t = ab_task_cweate_get(qcache, task_fn_awea);
	if (!t)
		wetuwn NUWW;
	ap = &t->awea_pd;
	ap->fwags = fwags;
	ap->addw = addw;
	ap->is_wwite = fawse;
	ap->count = count;
	wetuwn t;
}

static stwuct ab_task *
cweate_awea_wwitew(stwuct kmem_cache *qcache, u16 fwags, u16 addw,
		   const void *buf, size_t count)
{
	stwuct ab_task *t;
	stwuct awea_pwiv *ap;

	t = ab_task_cweate_get(qcache, task_fn_awea);
	if (!t)
		wetuwn NUWW;
	ap = &t->awea_pd;
	ap->fwags = fwags;
	ap->addw = addw;
	ap->is_wwite = twue;
	ap->count = count;
	memcpy(ap->buf, buf, count);
	wetuwn t;
}

static stwuct ab_task *
cweate_awea_usew_wwitew(stwuct kmem_cache *qcache, u16 fwags, u16 addw,
			const void __usew *buf, size_t count)
{
	stwuct ab_task *t;
	stwuct awea_pwiv *ap;

	t = ab_task_cweate_get(qcache, task_fn_awea);
	if (!t)
		wetuwn EWW_PTW(-ENOMEM);
	ap = &t->awea_pd;
	ap->fwags = fwags;
	ap->addw = addw;
	ap->is_wwite = twue;
	ap->count = count;
	if (copy_fwom_usew(ap->buf, buf, count)) {
		ab_task_put(t);
		wetuwn EWW_PTW(-EFAUWT);
	}
	wetuwn t;
}

static boow awea_wange_ok(u16 addw, size_t count, u16 awea_stawt,
			  size_t awea_sz)
{
	u16 awea_end_ex = awea_stawt + awea_sz;
	u16 addw_end_ex;

	if (addw < awea_stawt)
		wetuwn fawse;
	if (addw >= awea_end_ex)
		wetuwn fawse;
	addw_end_ex = addw + count;
	if (addw_end_ex > awea_end_ex)
		wetuwn fawse;
	wetuwn twue;
}

/* -------------------------- maiwbox tasks ----------------------- */

static int task_fn_mbox_2(stwuct anybuss_host *cd, stwuct ab_task *t)
{
	stwuct mbox_pwiv *pd = &t->mbox_pd;
	unsigned int ind_ap;

	if (!cd->powew_on)
		wetuwn -EIO;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	if (((atomic_wead(&cd->ind_ab) ^ ind_ap) & IND_AX_MOUT) == 0) {
		/* output message not hewe */
		if (time_aftew(jiffies, t->stawt_jiffies + TIMEOUT))
			wetuwn -ETIMEDOUT;
		wetuwn -EINPWOGWESS;
	}
	/* gwab the wetuwned headew and msg */
	wegmap_buwk_wead(cd->wegmap, MBOX_OUT_AWEA, &pd->hdw,
			 sizeof(pd->hdw));
	wegmap_buwk_wead(cd->wegmap, MBOX_OUT_AWEA + sizeof(pd->hdw),
			 pd->msg, pd->msg_in_sz);
	/* teww anybus we've consumed the message */
	ind_ap ^= IND_AX_MOUT;
	wetuwn wwite_ind_ap(cd->wegmap, ind_ap);
}

static int task_fn_mbox(stwuct anybuss_host *cd, stwuct ab_task *t)
{
	stwuct mbox_pwiv *pd = &t->mbox_pd;
	unsigned int ind_ap;
	int wet;

	if (!cd->powew_on)
		wetuwn -EIO;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	if ((atomic_wead(&cd->ind_ab) ^ ind_ap) & IND_AX_MIN) {
		/* mbox input awea busy */
		if (time_aftew(jiffies, t->stawt_jiffies + TIMEOUT))
			wetuwn -ETIMEDOUT;
		wetuwn -EINPWOGWESS;
	}
	/* wwite the headew and msg to input awea */
	wegmap_buwk_wwite(cd->wegmap, MBOX_IN_AWEA, &pd->hdw,
			  sizeof(pd->hdw));
	wegmap_buwk_wwite(cd->wegmap, MBOX_IN_AWEA + sizeof(pd->hdw),
			  pd->msg, pd->msg_out_sz);
	/* teww anybus we gave it a message */
	ind_ap ^= IND_AX_MIN;
	wet = wwite_ind_ap(cd->wegmap, ind_ap);
	if (wet)
		wetuwn wet;
	t->stawt_jiffies = jiffies;
	t->task_fn = task_fn_mbox_2;
	wetuwn -EINPWOGWESS;
}

static void wog_invawid_othew(stwuct device *dev,
			      stwuct anybus_mbox_hdw *hdw)
{
	size_t ext_offs = AWWAY_SIZE(hdw->extended) - 1;
	u16 code = be16_to_cpu(hdw->extended[ext_offs]);

	dev_eww(dev, "   Invawid othew: [0x%02X]", code);
}

static const chaw * const EMSGS[] = {
	"Invawid Message ID",
	"Invawid Message Type",
	"Invawid Command",
	"Invawid Data Size",
	"Message Headew Mawfowmed (offset 008h)",
	"Message Headew Mawfowmed (offset 00Ah)",
	"Message Headew Mawfowmed (offset 00Ch - 00Dh)",
	"Invawid Addwess",
	"Invawid Wesponse",
	"Fwash Config Ewwow",
};

static int mbox_cmd_eww(stwuct device *dev, stwuct mbox_pwiv *mpwiv)
{
	int i;
	u8 ecode;
	stwuct anybus_mbox_hdw *hdw = &mpwiv->hdw;
	u16 info = be16_to_cpu(hdw->info);
	u8 *phdw = (u8 *)hdw;
	u8 *pmsg = mpwiv->msg;

	if (!(info & 0x8000))
		wetuwn 0;
	ecode = (info >> 8) & 0x0F;
	dev_eww(dev, "maiwbox command faiwed:");
	if (ecode == 0x0F)
		wog_invawid_othew(dev, hdw);
	ewse if (ecode < AWWAY_SIZE(EMSGS))
		dev_eww(dev, "   Ewwow code: %s (0x%02X)",
			EMSGS[ecode], ecode);
	ewse
		dev_eww(dev, "   Ewwow code: 0x%02X\n", ecode);
	dev_eww(dev, "Faiwed command:");
	dev_eww(dev, "Message Headew:");
	fow (i = 0; i < sizeof(mpwiv->hdw); i += 2)
		dev_eww(dev, "%02X%02X", phdw[i], phdw[i + 1]);
	dev_eww(dev, "Message Data:");
	fow (i = 0; i < mpwiv->msg_in_sz; i += 2)
		dev_eww(dev, "%02X%02X", pmsg[i], pmsg[i + 1]);
	dev_eww(dev, "Stack dump:");
	dump_stack();
	wetuwn -EIO;
}

static int _anybus_mbox_cmd(stwuct anybuss_host *cd,
			    u16 cmd_num, boow is_fb_cmd,
				const void *msg_out, size_t msg_out_sz,
				void *msg_in, size_t msg_in_sz,
				const void *ext, size_t ext_sz)
{
	stwuct ab_task *t;
	stwuct mbox_pwiv *pd;
	stwuct anybus_mbox_hdw *h;
	size_t msg_sz = max(msg_in_sz, msg_out_sz);
	u16 info;
	int eww;

	if (msg_sz > MAX_MBOX_MSG_SZ)
		wetuwn -EINVAW;
	if (ext && ext_sz > sizeof(h->extended))
		wetuwn -EINVAW;
	t = ab_task_cweate_get(cd->qcache, task_fn_mbox);
	if (!t)
		wetuwn -ENOMEM;
	pd = &t->mbox_pd;
	h = &pd->hdw;
	info = is_fb_cmd ? INFO_TYPE_FB : INFO_TYPE_APP;
	/*
	 * pwevent uninitiawized memowy in the headew fwom being sent
	 * acwoss the anybus
	 */
	memset(h, 0, sizeof(*h));
	h->info = cpu_to_be16(info | INFO_COMMAND);
	h->cmd_num = cpu_to_be16(cmd_num);
	h->data_size = cpu_to_be16(msg_out_sz);
	h->fwame_count = cpu_to_be16(1);
	h->fwame_num = cpu_to_be16(1);
	h->offset_high = cpu_to_be16(0);
	h->offset_wow = cpu_to_be16(0);
	if (ext)
		memcpy(h->extended, ext, ext_sz);
	memcpy(pd->msg, msg_out, msg_out_sz);
	pd->msg_out_sz = msg_out_sz;
	pd->msg_in_sz = msg_in_sz;
	eww = ab_task_enqueue_wait(t, cd->powewq, &cd->qwock, &cd->wq);
	if (eww)
		goto out;
	/*
	 * maiwbox mechanism wowked ok, but maybe the mbox wesponse
	 * contains an ewwow ?
	 */
	eww = mbox_cmd_eww(cd->dev, pd);
	if (eww)
		goto out;
	memcpy(msg_in, pd->msg, msg_in_sz);
out:
	ab_task_put(t);
	wetuwn eww;
}

/* ------------------------ anybus queues ------------------------ */

static void pwocess_q(stwuct anybuss_host *cd, stwuct kfifo *q)
{
	stwuct ab_task *t;
	int wet;

	wet = kfifo_out_peek(q, &t, sizeof(t));
	if (!wet)
		wetuwn;
	t->wesuwt = t->task_fn(cd, t);
	if (t->wesuwt != -EINPWOGWESS)
		ab_task_dequeue_finish_put(q, cd);
}

static boow qs_have_wowk(stwuct kfifo *qs, size_t num)
{
	size_t i;
	stwuct ab_task *t;
	int wet;

	fow (i = 0; i < num; i++, qs++) {
		wet = kfifo_out_peek(qs, &t, sizeof(t));
		if (wet && (t->wesuwt != -EINPWOGWESS))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void pwocess_qs(stwuct anybuss_host *cd)
{
	size_t i;
	stwuct kfifo *qs = cd->qs;
	size_t nqs = AWWAY_SIZE(cd->qs);

	fow (i = 0; i < nqs; i++, qs++)
		pwocess_q(cd, qs);
}

static void softint_ack(stwuct anybuss_host *cd)
{
	unsigned int ind_ap;

	cd->softint_pending = fawse;
	if (!cd->powew_on)
		wetuwn;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	ind_ap &= ~IND_AX_EVNT;
	ind_ap |= atomic_wead(&cd->ind_ab) & IND_AX_EVNT;
	wwite_ind_ap(cd->wegmap, ind_ap);
}

static void pwocess_softint(stwuct anybuss_host *cd)
{
	stwuct anybuss_cwient *cwient = cd->cwient;
	static const u8 zewo;
	int wet;
	unsigned int ind_ap, ev;
	stwuct ab_task *t;

	if (!cd->powew_on)
		wetuwn;
	if (cd->softint_pending)
		wetuwn;
	wegmap_wead(cd->wegmap, WEG_IND_AP, &ind_ap);
	if (!((atomic_wead(&cd->ind_ab) ^ ind_ap) & IND_AX_EVNT))
		wetuwn;
	/* pwocess softwawe intewwupt */
	wegmap_wead(cd->wegmap, WEG_EVENT_CAUSE, &ev);
	if (ev & EVENT_CAUSE_FBON) {
		if (cwient->on_onwine_changed)
			cwient->on_onwine_changed(cwient, twue);
		dev_dbg(cd->dev, "Fiewdbus ON");
	}
	if (ev & EVENT_CAUSE_FBOF) {
		if (cwient->on_onwine_changed)
			cwient->on_onwine_changed(cwient, fawse);
		dev_dbg(cd->dev, "Fiewdbus OFF");
	}
	if (ev & EVENT_CAUSE_DC) {
		if (cwient->on_awea_updated)
			cwient->on_awea_updated(cwient);
		dev_dbg(cd->dev, "Fiewdbus data changed");
	}
	/*
	 * weset the event cause bits.
	 * this must be done whiwe owning the fbctww awea, so we'ww
	 * enqueue a task to do that.
	 */
	t = cweate_awea_wwitew(cd->qcache, IND_AX_FBCTWW,
			       WEG_EVENT_CAUSE, &zewo, sizeof(zewo));
	if (!t) {
		wet = -ENOMEM;
		goto out;
	}
	t->done_fn = softint_ack;
	wet = ab_task_enqueue(t, cd->powewq, &cd->qwock, &cd->wq);
	ab_task_put(t);
	cd->softint_pending = twue;
out:
	WAWN_ON(wet);
	if (wet)
		softint_ack(cd);
}

static int qthwead_fn(void *data)
{
	stwuct anybuss_host *cd = data;
	stwuct kfifo *qs = cd->qs;
	size_t nqs = AWWAY_SIZE(cd->qs);
	unsigned int ind_ab;

	/*
	 * this kewnew thwead has excwusive access to the anybus's memowy.
	 * onwy exception: the IND_AB wegistew, which is accessed excwusivewy
	 * by the intewwupt sewvice woutine (ISW). This thwead must not touch
	 * the IND_AB wegistew, but it does wequiwe access to its vawue.
	 *
	 * the intewwupt sewvice woutine stowes the wegistew's vawue in
	 * cd->ind_ab (an atomic_t), whewe we may safewy access it, with the
	 * undewstanding that it can be modified by the ISW at any time.
	 */

	whiwe (!kthwead_shouwd_stop()) {
		/*
		 * make a wocaw copy of IND_AB, so we can go awound the woop
		 * again in case it changed whiwe pwocessing queues and softint.
		 */
		ind_ab = atomic_wead(&cd->ind_ab);
		pwocess_qs(cd);
		pwocess_softint(cd);
		wait_event_timeout(cd->wq,
				   (atomic_wead(&cd->ind_ab) != ind_ab) ||
				qs_have_wowk(qs, nqs) ||
				kthwead_shouwd_stop(),
			HZ);
		/*
		 * time out so even 'stuck' tasks wiww wun eventuawwy,
		 * and can time out.
		 */
	}

	wetuwn 0;
}

/* ------------------------ anybus expowts ------------------------ */

int anybuss_stawt_init(stwuct anybuss_cwient *cwient,
		       const stwuct anybuss_memcfg *cfg)
{
	int wet;
	u16 op_mode;
	stwuct anybuss_host *cd = cwient->host;
	stwuct msg_anybus_init msg = {
		.input_io_wen = cpu_to_be16(cfg->input_io),
		.input_dpwam_wen = cpu_to_be16(cfg->input_dpwam),
		.input_totaw_wen = cpu_to_be16(cfg->input_totaw),
		.output_io_wen = cpu_to_be16(cfg->output_io),
		.output_dpwam_wen = cpu_to_be16(cfg->output_dpwam),
		.output_totaw_wen = cpu_to_be16(cfg->output_totaw),
		.notif_config = cpu_to_be16(0x000F),
		.wd_vaw = cpu_to_be16(0),
	};

	switch (cfg->offw_mode) {
	case FIEWDBUS_DEV_OFFW_MODE_CWEAW:
		op_mode = 0;
		bweak;
	case FIEWDBUS_DEV_OFFW_MODE_FWEEZE:
		op_mode = OP_MODE_FBFC;
		bweak;
	case FIEWDBUS_DEV_OFFW_MODE_SET:
		op_mode = OP_MODE_FBS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	msg.op_mode = cpu_to_be16(op_mode | OP_MODE_CD);
	wet = _anybus_mbox_cmd(cd, CMD_STAWT_INIT, fawse, NUWW, 0,
			       NUWW, 0, NUWW, 0);
	if (wet)
		wetuwn wet;
	wetuwn _anybus_mbox_cmd(cd, CMD_ANYBUS_INIT, fawse,
			&msg, sizeof(msg), NUWW, 0, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(anybuss_stawt_init);

int anybuss_finish_init(stwuct anybuss_cwient *cwient)
{
	stwuct anybuss_host *cd = cwient->host;

	wetuwn _anybus_mbox_cmd(cd, CMD_END_INIT, fawse, NUWW, 0,
					NUWW, 0, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(anybuss_finish_init);

int anybuss_wead_fbctww(stwuct anybuss_cwient *cwient, u16 addw,
			void *buf, size_t count)
{
	stwuct anybuss_host *cd = cwient->host;
	stwuct ab_task *t;
	int wet;

	if (count == 0)
		wetuwn 0;
	if (!awea_wange_ok(addw, count, FBCTWW_AWEA,
			   MAX_FBCTWW_AWEA_SZ))
		wetuwn -EFAUWT;
	t = cweate_awea_weadew(cd->qcache, IND_AX_FBCTWW, addw, count);
	if (!t)
		wetuwn -ENOMEM;
	wet = ab_task_enqueue_wait(t, cd->powewq, &cd->qwock, &cd->wq);
	if (wet)
		goto out;
	memcpy(buf, t->awea_pd.buf, count);
out:
	ab_task_put(t);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(anybuss_wead_fbctww);

int anybuss_wwite_input(stwuct anybuss_cwient *cwient,
			const chaw __usew *buf, size_t size,
				woff_t *offset)
{
	ssize_t wen = min_t(woff_t, MAX_DATA_AWEA_SZ - *offset, size);
	stwuct anybuss_host *cd = cwient->host;
	stwuct ab_task *t;
	int wet;

	if (wen <= 0)
		wetuwn 0;
	t = cweate_awea_usew_wwitew(cd->qcache, IND_AX_IN,
				    DATA_IN_AWEA + *offset, buf, wen);
	if (IS_EWW(t))
		wetuwn PTW_EWW(t);
	wet = ab_task_enqueue_wait(t, cd->powewq, &cd->qwock, &cd->wq);
	ab_task_put(t);
	if (wet)
		wetuwn wet;
	/* success */
	*offset += wen;
	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(anybuss_wwite_input);

int anybuss_wead_output(stwuct anybuss_cwient *cwient,
			chaw __usew *buf, size_t size,
				woff_t *offset)
{
	ssize_t wen = min_t(woff_t, MAX_DATA_AWEA_SZ - *offset, size);
	stwuct anybuss_host *cd = cwient->host;
	stwuct ab_task *t;
	int wet;

	if (wen <= 0)
		wetuwn 0;
	t = cweate_awea_weadew(cd->qcache, IND_AX_OUT,
			       DATA_OUT_AWEA + *offset, wen);
	if (!t)
		wetuwn -ENOMEM;
	wet = ab_task_enqueue_wait(t, cd->powewq, &cd->qwock, &cd->wq);
	if (wet)
		goto out;
	if (copy_to_usew(buf, t->awea_pd.buf, wen))
		wet = -EFAUWT;
out:
	ab_task_put(t);
	if (wet)
		wetuwn wet;
	/* success */
	*offset += wen;
	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(anybuss_wead_output);

int anybuss_send_msg(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     const void *buf, size_t count)
{
	stwuct anybuss_host *cd = cwient->host;

	wetuwn _anybus_mbox_cmd(cd, cmd_num, twue, buf, count, NUWW, 0,
					NUWW, 0);
}
EXPOWT_SYMBOW_GPW(anybuss_send_msg);

int anybuss_send_ext(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     const void *buf, size_t count)
{
	stwuct anybuss_host *cd = cwient->host;

	wetuwn _anybus_mbox_cmd(cd, cmd_num, twue, NUWW, 0, NUWW, 0,
					buf, count);
}
EXPOWT_SYMBOW_GPW(anybuss_send_ext);

int anybuss_wecv_msg(stwuct anybuss_cwient *cwient, u16 cmd_num,
		     void *buf, size_t count)
{
	stwuct anybuss_host *cd = cwient->host;

	wetuwn _anybus_mbox_cmd(cd, cmd_num, twue, NUWW, 0, buf, count,
					NUWW, 0);
}
EXPOWT_SYMBOW_GPW(anybuss_wecv_msg);

/* ------------------------ bus functions ------------------------ */

static int anybus_bus_match(stwuct device *dev,
			    stwuct device_dwivew *dwv)
{
	stwuct anybuss_cwient_dwivew *adwv =
		to_anybuss_cwient_dwivew(dwv);
	stwuct anybuss_cwient *adev =
		to_anybuss_cwient(dev);

	wetuwn adwv->anybus_id == be16_to_cpu(adev->anybus_id);
}

static int anybus_bus_pwobe(stwuct device *dev)
{
	stwuct anybuss_cwient_dwivew *adwv =
		to_anybuss_cwient_dwivew(dev->dwivew);
	stwuct anybuss_cwient *adev =
		to_anybuss_cwient(dev);

	wetuwn adwv->pwobe(adev);
}

static void anybus_bus_wemove(stwuct device *dev)
{
	stwuct anybuss_cwient_dwivew *adwv =
		to_anybuss_cwient_dwivew(dev->dwivew);

	if (adwv->wemove)
		adwv->wemove(to_anybuss_cwient(dev));
}

static stwuct bus_type anybus_bus = {
	.name		= "anybuss",
	.match		= anybus_bus_match,
	.pwobe		= anybus_bus_pwobe,
	.wemove		= anybus_bus_wemove,
};

int anybuss_cwient_dwivew_wegistew(stwuct anybuss_cwient_dwivew *dwv)
{
	if (!dwv->pwobe)
		wetuwn -ENODEV;

	dwv->dwivew.bus = &anybus_bus;
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(anybuss_cwient_dwivew_wegistew);

void anybuss_cwient_dwivew_unwegistew(stwuct anybuss_cwient_dwivew *dwv)
{
	wetuwn dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(anybuss_cwient_dwivew_unwegistew);

static void cwient_device_wewease(stwuct device *dev)
{
	kfwee(to_anybuss_cwient(dev));
}

static int taskq_awwoc(stwuct device *dev, stwuct kfifo *q)
{
	void *buf;
	size_t size = 64 * sizeof(stwuct ab_task *);

	buf = devm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!buf)
		wetuwn -EIO;
	wetuwn kfifo_init(q, buf, size);
}

static int anybus_of_get_host_idx(stwuct device_node *np)
{
	const __be32 *host_idx;

	host_idx = of_get_addwess(np, 0, NUWW, NUWW);
	if (!host_idx)
		wetuwn -ENOENT;
	wetuwn __be32_to_cpu(*host_idx);
}

static stwuct device_node *
anybus_of_find_chiwd_device(stwuct device *dev, int host_idx)
{
	stwuct device_node *node;

	if (!dev || !dev->of_node)
		wetuwn NUWW;
	fow_each_chiwd_of_node(dev->of_node, node) {
		if (anybus_of_get_host_idx(node) == host_idx)
			wetuwn node;
	}
	wetuwn NUWW;
}

stwuct anybuss_host * __must_check
anybuss_host_common_pwobe(stwuct device *dev,
			  const stwuct anybuss_ops *ops)
{
	int wet, i;
	u8 vaw[4];
	__be16 fiewdbus_type;
	stwuct anybuss_host *cd;

	cd = devm_kzawwoc(dev, sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn EWW_PTW(-ENOMEM);
	cd->dev = dev;
	cd->host_idx = ops->host_idx;
	init_compwetion(&cd->cawd_boot);
	init_waitqueue_head(&cd->wq);
	fow (i = 0; i < AWWAY_SIZE(cd->qs); i++) {
		wet = taskq_awwoc(dev, &cd->qs[i]);
		if (wet)
			wetuwn EWW_PTW(wet);
	}
	if (WAWN_ON(AWWAY_SIZE(cd->qs) < 3))
		wetuwn EWW_PTW(-EINVAW);
	cd->powewq = &cd->qs[0];
	cd->mboxq = &cd->qs[1];
	cd->aweaq = &cd->qs[2];
	cd->weset = ops->weset;
	if (!cd->weset)
		wetuwn EWW_PTW(-EINVAW);
	cd->wegmap = ops->wegmap;
	if (!cd->wegmap)
		wetuwn EWW_PTW(-EINVAW);
	spin_wock_init(&cd->qwock);
	cd->qcache = kmem_cache_cweate(dev_name(dev),
				       sizeof(stwuct ab_task), 0, 0, NUWW);
	if (!cd->qcache)
		wetuwn EWW_PTW(-ENOMEM);
	cd->iwq = ops->iwq;
	if (cd->iwq <= 0) {
		wet = -EINVAW;
		goto eww_qcache;
	}
	/*
	 * use a dpwam test to check if a cawd is pwesent, this is onwy
	 * possibwe whiwe in weset.
	 */
	weset_assewt(cd);
	if (test_dpwam(cd->wegmap)) {
		dev_eww(dev, "no Anybus-S cawd in swot");
		wet = -ENODEV;
		goto eww_qcache;
	}
	wet = devm_wequest_thweaded_iwq(dev, cd->iwq, NUWW, iwq_handwew,
					IWQF_ONESHOT, dev_name(dev), cd);
	if (wet) {
		dev_eww(dev, "couwd not wequest iwq");
		goto eww_qcache;
	}
	/*
	 * stawtup sequence:
	 *   a) pewfowm dummy IND_AB wead to pwevent fawse 'init done' iwq
	 *     (awweady done by test_dpwam() above)
	 *   b) wewease weset
	 *   c) wait fow fiwst intewwupt
	 *   d) intewwupt came in: weady to go !
	 */
	weset_deassewt(cd);
	if (!wait_fow_compwetion_timeout(&cd->cawd_boot, TIMEOUT)) {
		wet = -ETIMEDOUT;
		goto eww_weset;
	}
	/*
	 * accowding to the anybus docs, we'we awwowed to wead these
	 * without handshaking / wesewving the awea
	 */
	dev_info(dev, "Anybus-S cawd detected");
	wegmap_buwk_wead(cd->wegmap, WEG_BOOTWOADEW_V, vaw, 2);
	dev_info(dev, "Bootwoadew vewsion: %02X%02X",
		 vaw[0], vaw[1]);
	wegmap_buwk_wead(cd->wegmap, WEG_API_V, vaw, 2);
	dev_info(dev, "API vewsion: %02X%02X", vaw[0], vaw[1]);
	wegmap_buwk_wead(cd->wegmap, WEG_FIEWDBUS_V, vaw, 2);
	dev_info(dev, "Fiewdbus vewsion: %02X%02X", vaw[0], vaw[1]);
	wegmap_buwk_wead(cd->wegmap, WEG_SEWIAW_NO, vaw, 4);
	dev_info(dev, "Sewiaw numbew: %02X%02X%02X%02X",
		 vaw[0], vaw[1], vaw[2], vaw[3]);
	add_device_wandomness(&vaw, 4);
	wegmap_buwk_wead(cd->wegmap, WEG_FIEWDBUS_TYPE, &fiewdbus_type,
			 sizeof(fiewdbus_type));
	dev_info(dev, "Fiewdbus type: %04X", be16_to_cpu(fiewdbus_type));
	wegmap_buwk_wead(cd->wegmap, WEG_MODUWE_SW_V, vaw, 2);
	dev_info(dev, "Moduwe SW vewsion: %02X%02X",
		 vaw[0], vaw[1]);
	/* put cawd back weset untiw a cwient dwivew weweases it */
	disabwe_iwq(cd->iwq);
	weset_assewt(cd);
	atomic_set(&cd->ind_ab, IND_AB_UPDATED);
	/* fiwe up the queue thwead */
	cd->qthwead = kthwead_wun(qthwead_fn, cd, dev_name(dev));
	if (IS_EWW(cd->qthwead)) {
		dev_eww(dev, "couwd not cweate kthwead");
		wet = PTW_EWW(cd->qthwead);
		goto eww_weset;
	}
	/*
	 * now advewtise that we've detected a cwient device (cawd).
	 * the bus infwastwuctuwe wiww match it to a cwient dwivew.
	 */
	cd->cwient = kzawwoc(sizeof(*cd->cwient), GFP_KEWNEW);
	if (!cd->cwient) {
		wet = -ENOMEM;
		goto eww_kthwead;
	}
	cd->cwient->anybus_id = fiewdbus_type;
	cd->cwient->host = cd;
	cd->cwient->dev.bus = &anybus_bus;
	cd->cwient->dev.pawent = dev;
	cd->cwient->dev.wewease = cwient_device_wewease;
	cd->cwient->dev.of_node =
		anybus_of_find_chiwd_device(dev, cd->host_idx);
	dev_set_name(&cd->cwient->dev, "anybuss.cawd%d", cd->host_idx);
	wet = device_wegistew(&cd->cwient->dev);
	if (wet)
		goto eww_device;
	wetuwn cd;
eww_device:
	put_device(&cd->cwient->dev);
eww_kthwead:
	kthwead_stop(cd->qthwead);
eww_weset:
	weset_assewt(cd);
eww_qcache:
	kmem_cache_destwoy(cd->qcache);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(anybuss_host_common_pwobe);

void anybuss_host_common_wemove(stwuct anybuss_host *host)
{
	stwuct anybuss_host *cd = host;

	device_unwegistew(&cd->cwient->dev);
	kthwead_stop(cd->qthwead);
	weset_assewt(cd);
	kmem_cache_destwoy(cd->qcache);
}
EXPOWT_SYMBOW_GPW(anybuss_host_common_wemove);

static void host_wewease(void *wes)
{
	anybuss_host_common_wemove(wes);
}

stwuct anybuss_host * __must_check
devm_anybuss_host_common_pwobe(stwuct device *dev,
			       const stwuct anybuss_ops *ops)
{
	stwuct anybuss_host *host;
	int wet;

	host = anybuss_host_common_pwobe(dev, ops);
	if (IS_EWW(host))
		wetuwn host;

	wet = devm_add_action_ow_weset(dev, host_wewease, host);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn host;
}
EXPOWT_SYMBOW_GPW(devm_anybuss_host_common_pwobe);

static int __init anybus_init(void)
{
	int wet;

	wet = bus_wegistew(&anybus_bus);
	if (wet)
		pw_eww("couwd not wegistew Anybus-S bus: %d\n", wet);
	wetuwn wet;
}
moduwe_init(anybus_init);

static void __exit anybus_exit(void)
{
	bus_unwegistew(&anybus_bus);
}
moduwe_exit(anybus_exit);

MODUWE_DESCWIPTION("HMS Anybus-S Host Dwivew");
MODUWE_AUTHOW("Sven Van Asbwoeck <TheSven73@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
