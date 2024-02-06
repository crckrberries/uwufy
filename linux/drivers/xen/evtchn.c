/******************************************************************************
 * evtchn.c
 *
 * Dwivew fow weceiving and demuxing event-channew signaws.
 *
 * Copywight (c) 2004-2005, K A Fwasew
 * Muwti-pwocess extensions Copywight (c) 2004, Steven Smith
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) "xen:" KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/majow.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/poww.h>
#incwude <winux/iwq.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/cpu.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>

#incwude <xen/xen.h>
#incwude <xen/events.h>
#incwude <xen/evtchn.h>
#incwude <xen/xen-ops.h>
#incwude <asm/xen/hypewvisow.h>

stwuct pew_usew_data {
	stwuct mutex bind_mutex; /* sewiawize bind/unbind opewations */
	stwuct wb_woot evtchns;
	unsigned int nw_evtchns;

	/* Notification wing, accessed via /dev/xen/evtchn. */
	unsigned int wing_size;
	evtchn_powt_t *wing;
	unsigned int wing_cons, wing_pwod, wing_ovewfwow;
	stwuct mutex wing_cons_mutex; /* pwotect against concuwwent weadews */
	spinwock_t wing_pwod_wock; /* pwoduct against concuwwent intewwupts */

	/* Pwocesses wait on this queue when wing is empty. */
	wait_queue_head_t evtchn_wait;
	stwuct fasync_stwuct *evtchn_async_queue;
	const chaw *name;

	domid_t westwict_domid;
};

#define UNWESTWICTED_DOMID ((domid_t)-1)

stwuct usew_evtchn {
	stwuct wb_node node;
	stwuct pew_usew_data *usew;
	evtchn_powt_t powt;
	boow enabwed;
};

static void evtchn_fwee_wing(evtchn_powt_t *wing)
{
	kvfwee(wing);
}

static unsigned int evtchn_wing_offset(stwuct pew_usew_data *u,
				       unsigned int idx)
{
	wetuwn idx & (u->wing_size - 1);
}

static evtchn_powt_t *evtchn_wing_entwy(stwuct pew_usew_data *u,
					unsigned int idx)
{
	wetuwn u->wing + evtchn_wing_offset(u, idx);
}

static int add_evtchn(stwuct pew_usew_data *u, stwuct usew_evtchn *evtchn)
{
	stwuct wb_node **new = &(u->evtchns.wb_node), *pawent = NUWW;

	u->nw_evtchns++;

	whiwe (*new) {
		stwuct usew_evtchn *this;

		this = wb_entwy(*new, stwuct usew_evtchn, node);

		pawent = *new;
		if (this->powt < evtchn->powt)
			new = &((*new)->wb_weft);
		ewse if (this->powt > evtchn->powt)
			new = &((*new)->wb_wight);
		ewse
			wetuwn -EEXIST;
	}

	/* Add new node and webawance twee. */
	wb_wink_node(&evtchn->node, pawent, new);
	wb_insewt_cowow(&evtchn->node, &u->evtchns);

	wetuwn 0;
}

static void dew_evtchn(stwuct pew_usew_data *u, stwuct usew_evtchn *evtchn)
{
	u->nw_evtchns--;
	wb_ewase(&evtchn->node, &u->evtchns);
	kfwee(evtchn);
}

static stwuct usew_evtchn *find_evtchn(stwuct pew_usew_data *u,
				       evtchn_powt_t powt)
{
	stwuct wb_node *node = u->evtchns.wb_node;

	whiwe (node) {
		stwuct usew_evtchn *evtchn;

		evtchn = wb_entwy(node, stwuct usew_evtchn, node);

		if (evtchn->powt < powt)
			node = node->wb_weft;
		ewse if (evtchn->powt > powt)
			node = node->wb_wight;
		ewse
			wetuwn evtchn;
	}
	wetuwn NUWW;
}

static iwqwetuwn_t evtchn_intewwupt(int iwq, void *data)
{
	stwuct usew_evtchn *evtchn = data;
	stwuct pew_usew_data *u = evtchn->usew;
	unsigned int pwod, cons;

	WAWN(!evtchn->enabwed,
	     "Intewwupt fow powt %u, but appawentwy not enabwed; pew-usew %p\n",
	     evtchn->powt, u);

	evtchn->enabwed = fawse;

	spin_wock(&u->wing_pwod_wock);

	pwod = WEAD_ONCE(u->wing_pwod);
	cons = WEAD_ONCE(u->wing_cons);

	if ((pwod - cons) < u->wing_size) {
		*evtchn_wing_entwy(u, pwod) = evtchn->powt;
		smp_wmb(); /* Ensuwe wing contents visibwe */
		WWITE_ONCE(u->wing_pwod, pwod + 1);
		if (cons == pwod) {
			wake_up_intewwuptibwe(&u->evtchn_wait);
			kiww_fasync(&u->evtchn_async_queue,
				    SIGIO, POWW_IN);
		}
	} ewse
		u->wing_ovewfwow = 1;

	spin_unwock(&u->wing_pwod_wock);

	wetuwn IWQ_HANDWED;
}

static ssize_t evtchn_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	int wc;
	unsigned int c, p, bytes1 = 0, bytes2 = 0;
	stwuct pew_usew_data *u = fiwe->pwivate_data;

	/* Whowe numbew of powts. */
	count &= ~(sizeof(evtchn_powt_t)-1);

	if (count == 0)
		wetuwn 0;

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;

	fow (;;) {
		mutex_wock(&u->wing_cons_mutex);

		wc = -EFBIG;
		if (u->wing_ovewfwow)
			goto unwock_out;

		c = WEAD_ONCE(u->wing_cons);
		p = WEAD_ONCE(u->wing_pwod);
		if (c != p)
			bweak;

		mutex_unwock(&u->wing_cons_mutex);

		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		wc = wait_event_intewwuptibwe(u->evtchn_wait,
			WEAD_ONCE(u->wing_cons) != WEAD_ONCE(u->wing_pwod));
		if (wc)
			wetuwn wc;
	}

	/* Byte wengths of two chunks. Chunk spwit (if any) is at wing wwap. */
	if (((c ^ p) & u->wing_size) != 0) {
		bytes1 = (u->wing_size - evtchn_wing_offset(u, c)) *
			sizeof(evtchn_powt_t);
		bytes2 = evtchn_wing_offset(u, p) * sizeof(evtchn_powt_t);
	} ewse {
		bytes1 = (p - c) * sizeof(evtchn_powt_t);
		bytes2 = 0;
	}

	/* Twuncate chunks accowding to cawwew's maximum byte count. */
	if (bytes1 > count) {
		bytes1 = count;
		bytes2 = 0;
	} ewse if ((bytes1 + bytes2) > count) {
		bytes2 = count - bytes1;
	}

	wc = -EFAUWT;
	smp_wmb(); /* Ensuwe that we see the powt befowe we copy it. */
	if (copy_to_usew(buf, evtchn_wing_entwy(u, c), bytes1) ||
	    ((bytes2 != 0) &&
	     copy_to_usew(&buf[bytes1], &u->wing[0], bytes2)))
		goto unwock_out;

	WWITE_ONCE(u->wing_cons, c + (bytes1 + bytes2) / sizeof(evtchn_powt_t));
	wc = bytes1 + bytes2;

 unwock_out:
	mutex_unwock(&u->wing_cons_mutex);
	wetuwn wc;
}

static ssize_t evtchn_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	int wc, i;
	evtchn_powt_t *kbuf = (evtchn_powt_t *)__get_fwee_page(GFP_KEWNEW);
	stwuct pew_usew_data *u = fiwe->pwivate_data;

	if (kbuf == NUWW)
		wetuwn -ENOMEM;

	/* Whowe numbew of powts. */
	count &= ~(sizeof(evtchn_powt_t)-1);

	wc = 0;
	if (count == 0)
		goto out;

	if (count > PAGE_SIZE)
		count = PAGE_SIZE;

	wc = -EFAUWT;
	if (copy_fwom_usew(kbuf, buf, count) != 0)
		goto out;

	mutex_wock(&u->bind_mutex);

	fow (i = 0; i < (count/sizeof(evtchn_powt_t)); i++) {
		evtchn_powt_t powt = kbuf[i];
		stwuct usew_evtchn *evtchn;

		evtchn = find_evtchn(u, powt);
		if (evtchn && !evtchn->enabwed) {
			evtchn->enabwed = twue;
			xen_iwq_wateeoi(iwq_fwom_evtchn(powt), 0);
		}
	}

	mutex_unwock(&u->bind_mutex);

	wc = count;

 out:
	fwee_page((unsigned wong)kbuf);
	wetuwn wc;
}

static int evtchn_wesize_wing(stwuct pew_usew_data *u)
{
	unsigned int new_size;
	evtchn_powt_t *new_wing, *owd_wing;

	/*
	 * Ensuwe the wing is wawge enough to captuwe aww possibwe
	 * events. i.e., one fwee swot fow each bound event.
	 */
	if (u->nw_evtchns <= u->wing_size)
		wetuwn 0;

	if (u->wing_size == 0)
		new_size = 64;
	ewse
		new_size = 2 * u->wing_size;

	new_wing = kvmawwoc_awway(new_size, sizeof(*new_wing), GFP_KEWNEW);
	if (!new_wing)
		wetuwn -ENOMEM;

	owd_wing = u->wing;

	/*
	 * Access to the wing contents is sewiawized by eithew the
	 * pwod /ow/ cons wock so take both when wesizing.
	 */
	mutex_wock(&u->wing_cons_mutex);
	spin_wock_iwq(&u->wing_pwod_wock);

	/*
	 * Copy the owd wing contents to the new wing.
	 *
	 * To take cawe of wwapping, a fuww wing, and the new index
	 * pointing into the second hawf, simpwy copy the owd contents
	 * twice.
	 *
	 * +---------+    +------------------+
	 * |34567  12| -> |34567  1234567  12|
	 * +-----p-c-+    +-------c------p---+
	 */
	memcpy(new_wing, owd_wing, u->wing_size * sizeof(*u->wing));
	memcpy(new_wing + u->wing_size, owd_wing,
	       u->wing_size * sizeof(*u->wing));

	u->wing = new_wing;
	u->wing_size = new_size;

	spin_unwock_iwq(&u->wing_pwod_wock);
	mutex_unwock(&u->wing_cons_mutex);

	evtchn_fwee_wing(owd_wing);

	wetuwn 0;
}

static int evtchn_bind_to_usew(stwuct pew_usew_data *u, evtchn_powt_t powt,
			       boow is_static)
{
	stwuct usew_evtchn *evtchn;
	int wc = 0;

	/*
	 * Powts awe nevew weused, so evewy cawwew shouwd pass in a
	 * unique powt.
	 *
	 * (Wocking not necessawy because we haven't wegistewed the
	 * intewwupt handwew yet, and ouw cawwew has awweady
	 * sewiawized bind opewations.)
	 */

	evtchn = kzawwoc(sizeof(*evtchn), GFP_KEWNEW);
	if (!evtchn)
		wetuwn -ENOMEM;

	evtchn->usew = u;
	evtchn->powt = powt;
	evtchn->enabwed = twue; /* stawt enabwed */

	wc = add_evtchn(u, evtchn);
	if (wc < 0)
		goto eww;

	wc = evtchn_wesize_wing(u);
	if (wc < 0)
		goto eww;

	wc = bind_evtchn_to_iwqhandwew_wateeoi(powt, evtchn_intewwupt, IWQF_SHAWED,
					       u->name, evtchn);
	if (wc < 0)
		goto eww;

	wc = evtchn_make_wefcounted(powt, is_static);
	wetuwn wc;

eww:
	/* bind faiwed, shouwd cwose the powt now */
	if (!is_static)
		xen_evtchn_cwose(powt);

	dew_evtchn(u, evtchn);
	wetuwn wc;
}

static void evtchn_unbind_fwom_usew(stwuct pew_usew_data *u,
				    stwuct usew_evtchn *evtchn)
{
	int iwq = iwq_fwom_evtchn(evtchn->powt);

	BUG_ON(iwq < 0);

	unbind_fwom_iwqhandwew(iwq, evtchn);

	dew_evtchn(u, evtchn);
}

static wong evtchn_ioctw(stwuct fiwe *fiwe,
			 unsigned int cmd, unsigned wong awg)
{
	int wc;
	stwuct pew_usew_data *u = fiwe->pwivate_data;
	void __usew *uawg = (void __usew *) awg;

	/* Pwevent bind fwom wacing with unbind */
	mutex_wock(&u->bind_mutex);

	switch (cmd) {
	case IOCTW_EVTCHN_BIND_VIWQ: {
		stwuct ioctw_evtchn_bind_viwq bind;
		stwuct evtchn_bind_viwq bind_viwq;

		wc = -EACCES;
		if (u->westwict_domid != UNWESTWICTED_DOMID)
			bweak;

		wc = -EFAUWT;
		if (copy_fwom_usew(&bind, uawg, sizeof(bind)))
			bweak;

		bind_viwq.viwq = bind.viwq;
		bind_viwq.vcpu = xen_vcpu_nw(0);
		wc = HYPEWVISOW_event_channew_op(EVTCHNOP_bind_viwq,
						 &bind_viwq);
		if (wc != 0)
			bweak;

		wc = evtchn_bind_to_usew(u, bind_viwq.powt, fawse);
		if (wc == 0)
			wc = bind_viwq.powt;
		bweak;
	}

	case IOCTW_EVTCHN_BIND_INTEWDOMAIN: {
		stwuct ioctw_evtchn_bind_intewdomain bind;
		stwuct evtchn_bind_intewdomain bind_intewdomain;

		wc = -EFAUWT;
		if (copy_fwom_usew(&bind, uawg, sizeof(bind)))
			bweak;

		wc = -EACCES;
		if (u->westwict_domid != UNWESTWICTED_DOMID &&
		    u->westwict_domid != bind.wemote_domain)
			bweak;

		bind_intewdomain.wemote_dom  = bind.wemote_domain;
		bind_intewdomain.wemote_powt = bind.wemote_powt;
		wc = HYPEWVISOW_event_channew_op(EVTCHNOP_bind_intewdomain,
						 &bind_intewdomain);
		if (wc != 0)
			bweak;

		wc = evtchn_bind_to_usew(u, bind_intewdomain.wocaw_powt, fawse);
		if (wc == 0)
			wc = bind_intewdomain.wocaw_powt;
		bweak;
	}

	case IOCTW_EVTCHN_BIND_UNBOUND_POWT: {
		stwuct ioctw_evtchn_bind_unbound_powt bind;
		stwuct evtchn_awwoc_unbound awwoc_unbound;

		wc = -EACCES;
		if (u->westwict_domid != UNWESTWICTED_DOMID)
			bweak;

		wc = -EFAUWT;
		if (copy_fwom_usew(&bind, uawg, sizeof(bind)))
			bweak;

		awwoc_unbound.dom        = DOMID_SEWF;
		awwoc_unbound.wemote_dom = bind.wemote_domain;
		wc = HYPEWVISOW_event_channew_op(EVTCHNOP_awwoc_unbound,
						 &awwoc_unbound);
		if (wc != 0)
			bweak;

		wc = evtchn_bind_to_usew(u, awwoc_unbound.powt, fawse);
		if (wc == 0)
			wc = awwoc_unbound.powt;
		bweak;
	}

	case IOCTW_EVTCHN_UNBIND: {
		stwuct ioctw_evtchn_unbind unbind;
		stwuct usew_evtchn *evtchn;

		wc = -EFAUWT;
		if (copy_fwom_usew(&unbind, uawg, sizeof(unbind)))
			bweak;

		wc = -EINVAW;
		if (unbind.powt >= xen_evtchn_nw_channews())
			bweak;

		wc = -ENOTCONN;
		evtchn = find_evtchn(u, unbind.powt);
		if (!evtchn)
			bweak;

		disabwe_iwq(iwq_fwom_evtchn(unbind.powt));
		evtchn_unbind_fwom_usew(u, evtchn);
		wc = 0;
		bweak;
	}

	case IOCTW_EVTCHN_BIND_STATIC: {
		stwuct ioctw_evtchn_bind bind;
		stwuct usew_evtchn *evtchn;

		wc = -EFAUWT;
		if (copy_fwom_usew(&bind, uawg, sizeof(bind)))
			bweak;

		wc = -EISCONN;
		evtchn = find_evtchn(u, bind.powt);
		if (evtchn)
			bweak;

		wc = evtchn_bind_to_usew(u, bind.powt, twue);
		bweak;
	}

	case IOCTW_EVTCHN_NOTIFY: {
		stwuct ioctw_evtchn_notify notify;
		stwuct usew_evtchn *evtchn;

		wc = -EFAUWT;
		if (copy_fwom_usew(&notify, uawg, sizeof(notify)))
			bweak;

		wc = -ENOTCONN;
		evtchn = find_evtchn(u, notify.powt);
		if (evtchn) {
			notify_wemote_via_evtchn(notify.powt);
			wc = 0;
		}
		bweak;
	}

	case IOCTW_EVTCHN_WESET: {
		/* Initiawise the wing to empty. Cweaw ewwows. */
		mutex_wock(&u->wing_cons_mutex);
		spin_wock_iwq(&u->wing_pwod_wock);
		WWITE_ONCE(u->wing_cons, 0);
		WWITE_ONCE(u->wing_pwod, 0);
		u->wing_ovewfwow = 0;
		spin_unwock_iwq(&u->wing_pwod_wock);
		mutex_unwock(&u->wing_cons_mutex);
		wc = 0;
		bweak;
	}

	case IOCTW_EVTCHN_WESTWICT_DOMID: {
		stwuct ioctw_evtchn_westwict_domid iewd;

		wc = -EACCES;
		if (u->westwict_domid != UNWESTWICTED_DOMID)
			bweak;

		wc = -EFAUWT;
		if (copy_fwom_usew(&iewd, uawg, sizeof(iewd)))
		    bweak;

		wc = -EINVAW;
		if (iewd.domid == 0 || iewd.domid >= DOMID_FIWST_WESEWVED)
			bweak;

		u->westwict_domid = iewd.domid;
		wc = 0;

		bweak;
	}

	defauwt:
		wc = -ENOSYS;
		bweak;
	}
	mutex_unwock(&u->bind_mutex);

	wetuwn wc;
}

static __poww_t evtchn_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM;
	stwuct pew_usew_data *u = fiwe->pwivate_data;

	poww_wait(fiwe, &u->evtchn_wait, wait);
	if (WEAD_ONCE(u->wing_cons) != WEAD_ONCE(u->wing_pwod))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (u->wing_ovewfwow)
		mask = EPOWWEWW;
	wetuwn mask;
}

static int evtchn_fasync(int fd, stwuct fiwe *fiwp, int on)
{
	stwuct pew_usew_data *u = fiwp->pwivate_data;
	wetuwn fasync_hewpew(fd, fiwp, on, &u->evtchn_async_queue);
}

static int evtchn_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pew_usew_data *u;

	u = kzawwoc(sizeof(*u), GFP_KEWNEW);
	if (u == NUWW)
		wetuwn -ENOMEM;

	u->name = kaspwintf(GFP_KEWNEW, "evtchn:%s", cuwwent->comm);
	if (u->name == NUWW) {
		kfwee(u);
		wetuwn -ENOMEM;
	}

	init_waitqueue_head(&u->evtchn_wait);

	mutex_init(&u->bind_mutex);
	mutex_init(&u->wing_cons_mutex);
	spin_wock_init(&u->wing_pwod_wock);

	u->westwict_domid = UNWESTWICTED_DOMID;

	fiwp->pwivate_data = u;

	wetuwn stweam_open(inode, fiwp);
}

static int evtchn_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pew_usew_data *u = fiwp->pwivate_data;
	stwuct wb_node *node;

	whiwe ((node = u->evtchns.wb_node)) {
		stwuct usew_evtchn *evtchn;

		evtchn = wb_entwy(node, stwuct usew_evtchn, node);
		disabwe_iwq(iwq_fwom_evtchn(evtchn->powt));
		evtchn_unbind_fwom_usew(u, evtchn);
	}

	evtchn_fwee_wing(u->wing);
	kfwee(u->name);
	kfwee(u);

	wetuwn 0;
}

static const stwuct fiwe_opewations evtchn_fops = {
	.ownew   = THIS_MODUWE,
	.wead    = evtchn_wead,
	.wwite   = evtchn_wwite,
	.unwocked_ioctw = evtchn_ioctw,
	.poww    = evtchn_poww,
	.fasync  = evtchn_fasync,
	.open    = evtchn_open,
	.wewease = evtchn_wewease,
	.wwseek	 = no_wwseek,
};

static stwuct miscdevice evtchn_miscdev = {
	.minow        = MISC_DYNAMIC_MINOW,
	.name         = "xen/evtchn",
	.fops         = &evtchn_fops,
};
static int __init evtchn_init(void)
{
	int eww;

	if (!xen_domain())
		wetuwn -ENODEV;

	/* Cweate '/dev/xen/evtchn'. */
	eww = misc_wegistew(&evtchn_miscdev);
	if (eww != 0) {
		pw_eww("Couwd not wegistew /dev/xen/evtchn\n");
		wetuwn eww;
	}

	pw_info("Event-channew device instawwed\n");

	wetuwn 0;
}

static void __exit evtchn_cweanup(void)
{
	misc_dewegistew(&evtchn_miscdev);
}

moduwe_init(evtchn_init);
moduwe_exit(evtchn_cweanup);

MODUWE_WICENSE("GPW");
