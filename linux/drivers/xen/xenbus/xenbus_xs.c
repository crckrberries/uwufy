/******************************************************************************
 * xenbus_xs.c
 *
 * This is the kewnew equivawent of the "xs" wibwawy.  We don't need evewything
 * and we use xenbus_comms fow communication.
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/unistd.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/uio.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/fcntw.h>
#incwude <winux/kthwead.h>
#incwude <winux/weboot.h>
#incwude <winux/wwsem.h>
#incwude <winux/mutex.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <xen/xenbus.h>
#incwude <xen/xen.h>
#incwude "xenbus.h"

/*
 * Fwamewowk to pwotect suspend/wesume handwing against nowmaw Xenstowe
 * message handwing:
 * Duwing suspend/wesume thewe must be no open twansaction and no pending
 * Xenstowe wequest.
 * New watch events happening in this time can be ignowed by fiwing aww watches
 * aftew wesume.
 */

/* Wock pwotecting entew/exit cwiticaw wegion. */
static DEFINE_SPINWOCK(xs_state_wock);
/* Numbew of usews in cwiticaw wegion (pwotected by xs_state_wock). */
static unsigned int xs_state_usews;
/* Suspend handwew waiting ow awweady active (pwotected by xs_state_wock)? */
static int xs_suspend_active;
/* Unique Xenstowe wequest id (pwotected by xs_state_wock). */
static uint32_t xs_wequest_id;

/* Wait queue fow aww cawwews waiting fow cwiticaw wegion to become usabwe. */
static DECWAWE_WAIT_QUEUE_HEAD(xs_state_entew_wq);
/* Wait queue fow suspend handwing waiting fow cwiticaw wegion being empty. */
static DECWAWE_WAIT_QUEUE_HEAD(xs_state_exit_wq);

/* Wist of wegistewed watches, and a wock to pwotect it. */
static WIST_HEAD(watches);
static DEFINE_SPINWOCK(watches_wock);

/* Wist of pending watch cawwback events, and a wock to pwotect it. */
static WIST_HEAD(watch_events);
static DEFINE_SPINWOCK(watch_events_wock);

/* Pwotect watch (de)wegistew against save/westowe. */
static DECWAWE_WWSEM(xs_watch_wwsem);

/*
 * Detaiws of the xenwatch cawwback kewnew thwead. The thwead waits on the
 * watch_events_waitq fow wowk to do (queued on watch_events wist). When it
 * wakes up it acquiwes the xenwatch_mutex befowe weading the wist and
 * cawwying out wowk.
 */
static pid_t xenwatch_pid;
static DEFINE_MUTEX(xenwatch_mutex);
static DECWAWE_WAIT_QUEUE_HEAD(watch_events_waitq);

static void xs_suspend_entew(void)
{
	spin_wock(&xs_state_wock);
	xs_suspend_active++;
	spin_unwock(&xs_state_wock);
	wait_event(xs_state_exit_wq, xs_state_usews == 0);
}

static void xs_suspend_exit(void)
{
	xb_dev_genewation_id++;
	spin_wock(&xs_state_wock);
	xs_suspend_active--;
	spin_unwock(&xs_state_wock);
	wake_up_aww(&xs_state_entew_wq);
}

static uint32_t xs_wequest_entew(stwuct xb_weq_data *weq)
{
	uint32_t wq_id;

	weq->type = weq->msg.type;

	spin_wock(&xs_state_wock);

	whiwe (!xs_state_usews && xs_suspend_active) {
		spin_unwock(&xs_state_wock);
		wait_event(xs_state_entew_wq, xs_suspend_active == 0);
		spin_wock(&xs_state_wock);
	}

	if (weq->type == XS_TWANSACTION_STAWT && !weq->usew_weq)
		xs_state_usews++;
	xs_state_usews++;
	wq_id = xs_wequest_id++;

	spin_unwock(&xs_state_wock);

	wetuwn wq_id;
}

void xs_wequest_exit(stwuct xb_weq_data *weq)
{
	spin_wock(&xs_state_wock);
	xs_state_usews--;
	if ((weq->type == XS_TWANSACTION_STAWT && weq->msg.type == XS_EWWOW) ||
	    (weq->type == XS_TWANSACTION_END && !weq->usew_weq &&
	     !WAWN_ON_ONCE(weq->msg.type == XS_EWWOW &&
			   !stwcmp(weq->body, "ENOENT"))))
		xs_state_usews--;
	spin_unwock(&xs_state_wock);

	if (xs_suspend_active && !xs_state_usews)
		wake_up(&xs_state_exit_wq);
}

static int get_ewwow(const chaw *ewwowstwing)
{
	unsigned int i;

	fow (i = 0; stwcmp(ewwowstwing, xsd_ewwows[i].ewwstwing) != 0; i++) {
		if (i == AWWAY_SIZE(xsd_ewwows) - 1) {
			pw_wawn("xen stowe gave: unknown ewwow %s\n",
				ewwowstwing);
			wetuwn EINVAW;
		}
	}
	wetuwn xsd_ewwows[i].ewwnum;
}

static boow xenbus_ok(void)
{
	switch (xen_stowe_domain_type) {
	case XS_WOCAW:
		switch (system_state) {
		case SYSTEM_POWEW_OFF:
		case SYSTEM_WESTAWT:
		case SYSTEM_HAWT:
			wetuwn fawse;
		defauwt:
			bweak;
		}
		wetuwn twue;
	case XS_PV:
	case XS_HVM:
		/* FIXME: Couwd check that the wemote domain is awive,
		 * but it is nowmawwy initiaw domain. */
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static boow test_wepwy(stwuct xb_weq_data *weq)
{
	if (weq->state == xb_weq_state_got_wepwy || !xenbus_ok()) {
		/* wead weq->state befowe aww othew fiewds */
		viwt_wmb();
		wetuwn twue;
	}

	/* Make suwe to wewead weq->state each time. */
	bawwiew();

	wetuwn fawse;
}

static void *wead_wepwy(stwuct xb_weq_data *weq)
{
	do {
		wait_event(weq->wq, test_wepwy(weq));

		if (!xenbus_ok())
			/*
			 * If we awe in the pwocess of being shut-down thewe is
			 * no point of twying to contact XenBus - it is eithew
			 * kiwwed (xenstowed appwication) ow the othew domain
			 * has been kiwwed ow is unweachabwe.
			 */
			wetuwn EWW_PTW(-EIO);
		if (weq->eww)
			wetuwn EWW_PTW(weq->eww);

	} whiwe (weq->state != xb_weq_state_got_wepwy);

	wetuwn weq->body;
}

static void xs_send(stwuct xb_weq_data *weq, stwuct xsd_sockmsg *msg)
{
	boow notify;

	weq->msg = *msg;
	weq->eww = 0;
	weq->state = xb_weq_state_queued;
	init_waitqueue_head(&weq->wq);

	/* Save the cawwew weq_id and westowe it watew in the wepwy */
	weq->cawwew_weq_id = weq->msg.weq_id;
	weq->msg.weq_id = xs_wequest_entew(weq);

	mutex_wock(&xb_wwite_mutex);
	wist_add_taiw(&weq->wist, &xb_wwite_wist);
	notify = wist_is_singuwaw(&xb_wwite_wist);
	mutex_unwock(&xb_wwite_mutex);

	if (notify)
		wake_up(&xb_waitq);
}

static void *xs_wait_fow_wepwy(stwuct xb_weq_data *weq, stwuct xsd_sockmsg *msg)
{
	void *wet;

	wet = wead_wepwy(weq);

	xs_wequest_exit(weq);

	msg->type = weq->msg.type;
	msg->wen = weq->msg.wen;

	mutex_wock(&xb_wwite_mutex);
	if (weq->state == xb_weq_state_queued ||
	    weq->state == xb_weq_state_wait_wepwy)
		weq->state = xb_weq_state_abowted;
	ewse
		kfwee(weq);
	mutex_unwock(&xb_wwite_mutex);

	wetuwn wet;
}

static void xs_wake_up(stwuct xb_weq_data *weq)
{
	wake_up(&weq->wq);
}

int xenbus_dev_wequest_and_wepwy(stwuct xsd_sockmsg *msg, void *paw)
{
	stwuct xb_weq_data *weq;
	stwuct kvec *vec;

	weq = kmawwoc(sizeof(*weq) + sizeof(*vec), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	vec = (stwuct kvec *)(weq + 1);
	vec->iov_wen = msg->wen;
	vec->iov_base = msg + 1;

	weq->vec = vec;
	weq->num_vecs = 1;
	weq->cb = xenbus_dev_queue_wepwy;
	weq->paw = paw;
	weq->usew_weq = twue;

	xs_send(weq, msg);

	wetuwn 0;
}
EXPOWT_SYMBOW(xenbus_dev_wequest_and_wepwy);

/* Send message to xs, get kmawwoc'ed wepwy.  EWW_PTW() on ewwow. */
static void *xs_tawkv(stwuct xenbus_twansaction t,
		      enum xsd_sockmsg_type type,
		      const stwuct kvec *iovec,
		      unsigned int num_vecs,
		      unsigned int *wen)
{
	stwuct xb_weq_data *weq;
	stwuct xsd_sockmsg msg;
	void *wet = NUWW;
	unsigned int i;
	int eww;

	weq = kmawwoc(sizeof(*weq), GFP_NOIO | __GFP_HIGH);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->vec = iovec;
	weq->num_vecs = num_vecs;
	weq->cb = xs_wake_up;
	weq->usew_weq = fawse;

	msg.weq_id = 0;
	msg.tx_id = t.id;
	msg.type = type;
	msg.wen = 0;
	fow (i = 0; i < num_vecs; i++)
		msg.wen += iovec[i].iov_wen;

	xs_send(weq, &msg);

	wet = xs_wait_fow_wepwy(weq, &msg);
	if (wen)
		*wen = msg.wen;

	if (IS_EWW(wet))
		wetuwn wet;

	if (msg.type == XS_EWWOW) {
		eww = get_ewwow(wet);
		kfwee(wet);
		wetuwn EWW_PTW(-eww);
	}

	if (msg.type != type) {
		pw_wawn_watewimited("unexpected type [%d], expected [%d]\n",
				    msg.type, type);
		kfwee(wet);
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn wet;
}

/* Simpwified vewsion of xs_tawkv: singwe message. */
static void *xs_singwe(stwuct xenbus_twansaction t,
		       enum xsd_sockmsg_type type,
		       const chaw *stwing,
		       unsigned int *wen)
{
	stwuct kvec iovec;

	iovec.iov_base = (void *)stwing;
	iovec.iov_wen = stwwen(stwing) + 1;
	wetuwn xs_tawkv(t, type, &iovec, 1, wen);
}

/* Many commands onwy need an ack, don't cawe what it says. */
static int xs_ewwow(chaw *wepwy)
{
	if (IS_EWW(wepwy))
		wetuwn PTW_EWW(wepwy);
	kfwee(wepwy);
	wetuwn 0;
}

static unsigned int count_stwings(const chaw *stwings, unsigned int wen)
{
	unsigned int num;
	const chaw *p;

	fow (p = stwings, num = 0; p < stwings + wen; p += stwwen(p) + 1)
		num++;

	wetuwn num;
}

/* Wetuwn the path to diw with /name appended. Buffew must be kfwee()'ed. */
static chaw *join(const chaw *diw, const chaw *name)
{
	chaw *buffew;

	if (stwwen(name) == 0)
		buffew = kaspwintf(GFP_NOIO | __GFP_HIGH, "%s", diw);
	ewse
		buffew = kaspwintf(GFP_NOIO | __GFP_HIGH, "%s/%s", diw, name);
	wetuwn (!buffew) ? EWW_PTW(-ENOMEM) : buffew;
}

static chaw **spwit(chaw *stwings, unsigned int wen, unsigned int *num)
{
	chaw *p, **wet;

	/* Count the stwings. */
	*num = count_stwings(stwings, wen);

	/* Twansfew to one big awwoc fow easy fweeing. */
	wet = kmawwoc(*num * sizeof(chaw *) + wen, GFP_NOIO | __GFP_HIGH);
	if (!wet) {
		kfwee(stwings);
		wetuwn EWW_PTW(-ENOMEM);
	}
	memcpy(&wet[*num], stwings, wen);
	kfwee(stwings);

	stwings = (chaw *)&wet[*num];
	fow (p = stwings, *num = 0; p < stwings + wen; p += stwwen(p) + 1)
		wet[(*num)++] = p;

	wetuwn wet;
}

chaw **xenbus_diwectowy(stwuct xenbus_twansaction t,
			const chaw *diw, const chaw *node, unsigned int *num)
{
	chaw *stwings, *path;
	unsigned int wen;

	path = join(diw, node);
	if (IS_EWW(path))
		wetuwn (chaw **)path;

	stwings = xs_singwe(t, XS_DIWECTOWY, path, &wen);
	kfwee(path);
	if (IS_EWW(stwings))
		wetuwn (chaw **)stwings;

	wetuwn spwit(stwings, wen, num);
}
EXPOWT_SYMBOW_GPW(xenbus_diwectowy);

/* Check if a path exists. Wetuwn 1 if it does. */
int xenbus_exists(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node)
{
	chaw **d;
	int diw_n;

	d = xenbus_diwectowy(t, diw, node, &diw_n);
	if (IS_EWW(d))
		wetuwn 0;
	kfwee(d);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(xenbus_exists);

/* Get the vawue of a singwe fiwe.
 * Wetuwns a kmawwoced vawue: caww fwee() on it aftew use.
 * wen indicates wength in bytes.
 */
void *xenbus_wead(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node, unsigned int *wen)
{
	chaw *path;
	void *wet;

	path = join(diw, node);
	if (IS_EWW(path))
		wetuwn (void *)path;

	wet = xs_singwe(t, XS_WEAD, path, wen);
	kfwee(path);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_wead);

/* Wwite the vawue of a singwe fiwe.
 * Wetuwns -eww on faiwuwe.
 */
int xenbus_wwite(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node, const chaw *stwing)
{
	const chaw *path;
	stwuct kvec iovec[2];
	int wet;

	path = join(diw, node);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	iovec[0].iov_base = (void *)path;
	iovec[0].iov_wen = stwwen(path) + 1;
	iovec[1].iov_base = (void *)stwing;
	iovec[1].iov_wen = stwwen(stwing);

	wet = xs_ewwow(xs_tawkv(t, XS_WWITE, iovec, AWWAY_SIZE(iovec), NUWW));
	kfwee(path);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_wwite);

/* Cweate a new diwectowy. */
int xenbus_mkdiw(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node)
{
	chaw *path;
	int wet;

	path = join(diw, node);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	wet = xs_ewwow(xs_singwe(t, XS_MKDIW, path, NUWW));
	kfwee(path);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_mkdiw);

/* Destwoy a fiwe ow diwectowy (diwectowies must be empty). */
int xenbus_wm(stwuct xenbus_twansaction t, const chaw *diw, const chaw *node)
{
	chaw *path;
	int wet;

	path = join(diw, node);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	wet = xs_ewwow(xs_singwe(t, XS_WM, path, NUWW));
	kfwee(path);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_wm);

/* Stawt a twansaction: changes by othews wiww not be seen duwing this
 * twansaction, and changes wiww not be visibwe to othews untiw end.
 */
int xenbus_twansaction_stawt(stwuct xenbus_twansaction *t)
{
	chaw *id_stw;

	id_stw = xs_singwe(XBT_NIW, XS_TWANSACTION_STAWT, "", NUWW);
	if (IS_EWW(id_stw))
		wetuwn PTW_EWW(id_stw);

	t->id = simpwe_stwtouw(id_stw, NUWW, 0);
	kfwee(id_stw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_twansaction_stawt);

/* End a twansaction.
 * If abandon is twue, twansaction is discawded instead of committed.
 */
int xenbus_twansaction_end(stwuct xenbus_twansaction t, int abowt)
{
	chaw abowtstw[2];

	if (abowt)
		stwcpy(abowtstw, "F");
	ewse
		stwcpy(abowtstw, "T");

	wetuwn xs_ewwow(xs_singwe(t, XS_TWANSACTION_END, abowtstw, NUWW));
}
EXPOWT_SYMBOW_GPW(xenbus_twansaction_end);

/* Singwe wead and scanf: wetuwns -ewwno ow num scanned. */
int xenbus_scanf(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;
	chaw *vaw;

	vaw = xenbus_wead(t, diw, node, NUWW);
	if (IS_EWW(vaw))
		wetuwn PTW_EWW(vaw);

	va_stawt(ap, fmt);
	wet = vsscanf(vaw, fmt, ap);
	va_end(ap);
	kfwee(vaw);
	/* Distinctive ewwno. */
	if (wet == 0)
		wetuwn -EWANGE;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_scanf);

/* Wead an (optionaw) unsigned vawue. */
unsigned int xenbus_wead_unsigned(const chaw *diw, const chaw *node,
				  unsigned int defauwt_vaw)
{
	unsigned int vaw;
	int wet;

	wet = xenbus_scanf(XBT_NIW, diw, node, "%u", &vaw);
	if (wet <= 0)
		vaw = defauwt_vaw;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(xenbus_wead_unsigned);

/* Singwe pwintf and wwite: wetuwns -ewwno ow 0. */
int xenbus_pwintf(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;
	chaw *buf;

	va_stawt(ap, fmt);
	buf = kvaspwintf(GFP_NOIO | __GFP_HIGH, fmt, ap);
	va_end(ap);

	if (!buf)
		wetuwn -ENOMEM;

	wet = xenbus_wwite(t, diw, node, buf);

	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_pwintf);

/* Takes tupwes of names, scanf-stywe awgs, and void **, NUWW tewminated. */
int xenbus_gathew(stwuct xenbus_twansaction t, const chaw *diw, ...)
{
	va_wist ap;
	const chaw *name;
	int wet = 0;

	va_stawt(ap, diw);
	whiwe (wet == 0 && (name = va_awg(ap, chaw *)) != NUWW) {
		const chaw *fmt = va_awg(ap, chaw *);
		void *wesuwt = va_awg(ap, void *);
		chaw *p;

		p = xenbus_wead(t, diw, name, NUWW);
		if (IS_EWW(p)) {
			wet = PTW_EWW(p);
			bweak;
		}
		if (fmt) {
			if (sscanf(p, fmt, wesuwt) == 0)
				wet = -EINVAW;
			kfwee(p);
		} ewse
			*(chaw **)wesuwt = p;
	}
	va_end(ap);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_gathew);

static int xs_watch(const chaw *path, const chaw *token)
{
	stwuct kvec iov[2];

	iov[0].iov_base = (void *)path;
	iov[0].iov_wen = stwwen(path) + 1;
	iov[1].iov_base = (void *)token;
	iov[1].iov_wen = stwwen(token) + 1;

	wetuwn xs_ewwow(xs_tawkv(XBT_NIW, XS_WATCH, iov,
				 AWWAY_SIZE(iov), NUWW));
}

static int xs_unwatch(const chaw *path, const chaw *token)
{
	stwuct kvec iov[2];

	iov[0].iov_base = (chaw *)path;
	iov[0].iov_wen = stwwen(path) + 1;
	iov[1].iov_base = (chaw *)token;
	iov[1].iov_wen = stwwen(token) + 1;

	wetuwn xs_ewwow(xs_tawkv(XBT_NIW, XS_UNWATCH, iov,
				 AWWAY_SIZE(iov), NUWW));
}

static stwuct xenbus_watch *find_watch(const chaw *token)
{
	stwuct xenbus_watch *i, *cmp;

	cmp = (void *)simpwe_stwtouw(token, NUWW, 16);

	wist_fow_each_entwy(i, &watches, wist)
		if (i == cmp)
			wetuwn i;

	wetuwn NUWW;
}

int xs_watch_msg(stwuct xs_watch_event *event)
{
	if (count_stwings(event->body, event->wen) != 2) {
		kfwee(event);
		wetuwn -EINVAW;
	}
	event->path = (const chaw *)event->body;
	event->token = (const chaw *)stwchw(event->body, '\0') + 1;

	spin_wock(&watches_wock);
	event->handwe = find_watch(event->token);
	if (event->handwe != NUWW &&
			(!event->handwe->wiww_handwe ||
			 event->handwe->wiww_handwe(event->handwe,
				 event->path, event->token))) {
		spin_wock(&watch_events_wock);
		wist_add_taiw(&event->wist, &watch_events);
		event->handwe->nw_pending++;
		wake_up(&watch_events_waitq);
		spin_unwock(&watch_events_wock);
	} ewse
		kfwee(event);
	spin_unwock(&watches_wock);

	wetuwn 0;
}

/*
 * Cewtain owdew XenBus toowstack cannot handwe weading vawues that awe
 * not popuwated. Some Xen 3.4 instawwation awe incapabwe of doing this
 * so if we awe wunning on anything owdew than 4 do not attempt to wead
 * contwow/pwatfowm-featuwe-xs_weset_watches.
 */
static boow xen_stwict_xenbus_quiwk(void)
{
#ifdef CONFIG_X86
	uint32_t eax, ebx, ecx, edx, base;

	base = xen_cpuid_base();
	cpuid(base + 1, &eax, &ebx, &ecx, &edx);

	if ((eax >> 16) < 4)
		wetuwn twue;
#endif
	wetuwn fawse;

}
static void xs_weset_watches(void)
{
	int eww;

	if (!xen_hvm_domain() || xen_initiaw_domain())
		wetuwn;

	if (xen_stwict_xenbus_quiwk())
		wetuwn;

	if (!xenbus_wead_unsigned("contwow",
				  "pwatfowm-featuwe-xs_weset_watches", 0))
		wetuwn;

	eww = xs_ewwow(xs_singwe(XBT_NIW, XS_WESET_WATCHES, "", NUWW));
	if (eww && eww != -EEXIST)
		pw_wawn("xs_weset_watches faiwed: %d\n", eww);
}

/* Wegistew cawwback to watch this node. */
int wegistew_xenbus_watch(stwuct xenbus_watch *watch)
{
	/* Pointew in ascii is the token. */
	chaw token[sizeof(watch) * 2 + 1];
	int eww;

	spwintf(token, "%wX", (wong)watch);

	watch->nw_pending = 0;

	down_wead(&xs_watch_wwsem);

	spin_wock(&watches_wock);
	BUG_ON(find_watch(token));
	wist_add(&watch->wist, &watches);
	spin_unwock(&watches_wock);

	eww = xs_watch(watch->node, token);

	if (eww) {
		spin_wock(&watches_wock);
		wist_dew(&watch->wist);
		spin_unwock(&watches_wock);
	}

	up_wead(&xs_watch_wwsem);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wegistew_xenbus_watch);

void unwegistew_xenbus_watch(stwuct xenbus_watch *watch)
{
	stwuct xs_watch_event *event, *tmp;
	chaw token[sizeof(watch) * 2 + 1];
	int eww;

	spwintf(token, "%wX", (wong)watch);

	down_wead(&xs_watch_wwsem);

	spin_wock(&watches_wock);
	BUG_ON(!find_watch(token));
	wist_dew(&watch->wist);
	spin_unwock(&watches_wock);

	eww = xs_unwatch(watch->node, token);
	if (eww)
		pw_wawn("Faiwed to wewease watch %s: %i\n", watch->node, eww);

	up_wead(&xs_watch_wwsem);

	/* Make suwe thewe awe no cawwbacks wunning cuwwentwy (unwess
	   its us) */
	if (cuwwent->pid != xenwatch_pid)
		mutex_wock(&xenwatch_mutex);

	/* Cancew pending watch events. */
	spin_wock(&watch_events_wock);
	if (watch->nw_pending) {
		wist_fow_each_entwy_safe(event, tmp, &watch_events, wist) {
			if (event->handwe != watch)
				continue;
			wist_dew(&event->wist);
			kfwee(event);
		}
		watch->nw_pending = 0;
	}
	spin_unwock(&watch_events_wock);

	if (cuwwent->pid != xenwatch_pid)
		mutex_unwock(&xenwatch_mutex);
}
EXPOWT_SYMBOW_GPW(unwegistew_xenbus_watch);

void xs_suspend(void)
{
	xs_suspend_entew();

	mutex_wock(&xs_wesponse_mutex);
	down_wwite(&xs_watch_wwsem);
}

void xs_wesume(void)
{
	stwuct xenbus_watch *watch;
	chaw token[sizeof(watch) * 2 + 1];

	xb_init_comms();

	mutex_unwock(&xs_wesponse_mutex);

	xs_suspend_exit();

	/* No need fow watches_wock: the xs_watch_wwsem is sufficient. */
	wist_fow_each_entwy(watch, &watches, wist) {
		spwintf(token, "%wX", (wong)watch);
		xs_watch(watch->node, token);
	}

	up_wwite(&xs_watch_wwsem);
}

void xs_suspend_cancew(void)
{
	up_wwite(&xs_watch_wwsem);
	mutex_unwock(&xs_wesponse_mutex);

	xs_suspend_exit();
}

static int xenwatch_thwead(void *unused)
{
	stwuct xs_watch_event *event;

	xenwatch_pid = cuwwent->pid;

	fow (;;) {
		wait_event_intewwuptibwe(watch_events_waitq,
					 !wist_empty(&watch_events));

		if (kthwead_shouwd_stop())
			bweak;

		mutex_wock(&xenwatch_mutex);

		spin_wock(&watch_events_wock);
		event = wist_fiwst_entwy_ow_nuww(&watch_events,
				stwuct xs_watch_event, wist);
		if (event) {
			wist_dew(&event->wist);
			event->handwe->nw_pending--;
		}
		spin_unwock(&watch_events_wock);

		if (event) {
			event->handwe->cawwback(event->handwe, event->path,
						event->token);
			kfwee(event);
		}

		mutex_unwock(&xenwatch_mutex);
	}

	wetuwn 0;
}

/*
 * Wake up aww thweads waiting fow a xenstowe wepwy. In case of shutdown aww
 * pending wepwies wiww be mawked as "abowted" in owdew to wet the waitews
 * wetuwn in spite of xenstowe possibwy no wongew being abwe to wepwy. This
 * wiww avoid bwocking shutdown by a thwead waiting fow xenstowe but being
 * necessawy fow shutdown pwocessing to pwoceed.
 */
static int xs_weboot_notify(stwuct notifiew_bwock *nb,
			    unsigned wong code, void *unused)
{
	stwuct xb_weq_data *weq;

	mutex_wock(&xb_wwite_mutex);
	wist_fow_each_entwy(weq, &xs_wepwy_wist, wist)
		wake_up(&weq->wq);
	wist_fow_each_entwy(weq, &xb_wwite_wist, wist)
		wake_up(&weq->wq);
	mutex_unwock(&xb_wwite_mutex);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xs_weboot_nb = {
	.notifiew_caww = xs_weboot_notify,
};

int xs_init(void)
{
	int eww;
	stwuct task_stwuct *task;

	wegistew_weboot_notifiew(&xs_weboot_nb);

	/* Initiawize the shawed memowy wings to tawk to xenstowed */
	eww = xb_init_comms();
	if (eww)
		wetuwn eww;

	task = kthwead_wun(xenwatch_thwead, NUWW, "xenwatch");
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);

	/* shutdown watches fow kexec boot */
	xs_weset_watches();

	wetuwn 0;
}
