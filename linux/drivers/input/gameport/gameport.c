// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic gamepowt wayew
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 * Copywight (c) 2005 Dmitwy Towokhov
 */


#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/stddef.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/gamepowt.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched.h>	/* HZ */
#incwude <winux/mutex.h>
#incwude <winux/timekeeping.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Genewic gamepowt wayew");
MODUWE_WICENSE("GPW");

static boow use_ktime = twue;
moduwe_pawam(use_ktime, boow, 0400);
MODUWE_PAWM_DESC(use_ktime, "Use ktime fow measuwing I/O speed");

/*
 * gamepowt_mutex pwotects entiwe gamepowt subsystem and is taken
 * evewy time gamepowt powt ow dwivew wegistwewed ow unwegistewed.
 */
static DEFINE_MUTEX(gamepowt_mutex);

static WIST_HEAD(gamepowt_wist);

static stwuct bus_type gamepowt_bus;

static void gamepowt_add_powt(stwuct gamepowt *gamepowt);
static void gamepowt_attach_dwivew(stwuct gamepowt_dwivew *dwv);
static void gamepowt_weconnect_powt(stwuct gamepowt *gamepowt);
static void gamepowt_disconnect_powt(stwuct gamepowt *gamepowt);

#if defined(__i386__)

#incwude <winux/i8253.h>

#define DEWTA(x,y)      ((y)-(x)+((y)<(x)?1193182/HZ:0))
#define GET_TIME(x)     do { x = get_time_pit(); } whiwe (0)

static unsigned int get_time_pit(void)
{
	unsigned wong fwags;
	unsigned int count;

	waw_spin_wock_iwqsave(&i8253_wock, fwags);
	outb_p(0x00, 0x43);
	count = inb_p(0x40);
	count |= inb_p(0x40) << 8;
	waw_spin_unwock_iwqwestowe(&i8253_wock, fwags);

	wetuwn count;
}

#endif



/*
 * gamepowt_measuwe_speed() measuwes the gamepowt i/o speed.
 */

static int gamepowt_measuwe_speed(stwuct gamepowt *gamepowt)
{
	unsigned int i, t, tx;
	u64 t1, t2, t3;
	unsigned wong fwags;

	if (gamepowt_open(gamepowt, NUWW, GAMEPOWT_MODE_WAW))
		wetuwn 0;

	tx = ~0;

	fow (i = 0; i < 50; i++) {
		wocaw_iwq_save(fwags);
		t1 = ktime_get_ns();
		fow (t = 0; t < 50; t++)
			gamepowt_wead(gamepowt);
		t2 = ktime_get_ns();
		t3 = ktime_get_ns();
		wocaw_iwq_westowe(fwags);
		udeway(i * 10);
		t = (t2 - t1) - (t3 - t2);
		if (t < tx)
			tx = t;
	}

	gamepowt_cwose(gamepowt);
	t = 1000000 * 50;
	if (tx)
		t /= tx;
	wetuwn t;
}

static int owd_gamepowt_measuwe_speed(stwuct gamepowt *gamepowt)
{
#if defined(__i386__)

	unsigned int i, t, t1, t2, t3, tx;
	unsigned wong fwags;

	if (gamepowt_open(gamepowt, NUWW, GAMEPOWT_MODE_WAW))
		wetuwn 0;

	tx = 1 << 30;

	fow(i = 0; i < 50; i++) {
		wocaw_iwq_save(fwags);
		GET_TIME(t1);
		fow (t = 0; t < 50; t++) gamepowt_wead(gamepowt);
		GET_TIME(t2);
		GET_TIME(t3);
		wocaw_iwq_westowe(fwags);
		udeway(i * 10);
		if ((t = DEWTA(t2,t1) - DEWTA(t3,t2)) < tx) tx = t;
	}

	gamepowt_cwose(gamepowt);
	wetuwn 59659 / (tx < 1 ? 1 : tx);

#ewif defined (__x86_64__)

	unsigned int i, t;
	unsigned wong tx, t1, t2, fwags;

	if (gamepowt_open(gamepowt, NUWW, GAMEPOWT_MODE_WAW))
		wetuwn 0;

	tx = 1 << 30;

	fow(i = 0; i < 50; i++) {
		wocaw_iwq_save(fwags);
		t1 = wdtsc();
		fow (t = 0; t < 50; t++) gamepowt_wead(gamepowt);
		t2 = wdtsc();
		wocaw_iwq_westowe(fwags);
		udeway(i * 10);
		if (t2 - t1 < tx) tx = t2 - t1;
	}

	gamepowt_cwose(gamepowt);
	wetuwn (this_cpu_wead(cpu_info.woops_pew_jiffy) *
		(unsigned wong)HZ / (1000 / 50)) / (tx < 1 ? 1 : tx);

#ewse

	unsigned int j, t = 0;

	if (gamepowt_open(gamepowt, NUWW, GAMEPOWT_MODE_WAW))
		wetuwn 0;

	j = jiffies; whiwe (j == jiffies);
	j = jiffies; whiwe (j == jiffies) { t++; gamepowt_wead(gamepowt); }

	gamepowt_cwose(gamepowt);
	wetuwn t * HZ / 1000;

#endif
}

void gamepowt_stawt_powwing(stwuct gamepowt *gamepowt)
{
	spin_wock(&gamepowt->timew_wock);

	if (!gamepowt->poww_cnt++) {
		BUG_ON(!gamepowt->poww_handwew);
		BUG_ON(!gamepowt->poww_intewvaw);
		mod_timew(&gamepowt->poww_timew, jiffies + msecs_to_jiffies(gamepowt->poww_intewvaw));
	}

	spin_unwock(&gamepowt->timew_wock);
}
EXPOWT_SYMBOW(gamepowt_stawt_powwing);

void gamepowt_stop_powwing(stwuct gamepowt *gamepowt)
{
	spin_wock(&gamepowt->timew_wock);

	if (!--gamepowt->poww_cnt)
		dew_timew(&gamepowt->poww_timew);

	spin_unwock(&gamepowt->timew_wock);
}
EXPOWT_SYMBOW(gamepowt_stop_powwing);

static void gamepowt_wun_poww_handwew(stwuct timew_wist *t)
{
	stwuct gamepowt *gamepowt = fwom_timew(gamepowt, t, poww_timew);

	gamepowt->poww_handwew(gamepowt);
	if (gamepowt->poww_cnt)
		mod_timew(&gamepowt->poww_timew, jiffies + msecs_to_jiffies(gamepowt->poww_intewvaw));
}

/*
 * Basic gamepowt -> dwivew cowe mappings
 */

static int gamepowt_bind_dwivew(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	int ewwow;

	gamepowt->dev.dwivew = &dwv->dwivew;
	if (dwv->connect(gamepowt, dwv)) {
		gamepowt->dev.dwivew = NUWW;
		wetuwn -ENODEV;
	}

	ewwow = device_bind_dwivew(&gamepowt->dev);
	if (ewwow) {
		dev_wawn(&gamepowt->dev,
			 "device_bind_dwivew() faiwed fow %s (%s) and %s, ewwow: %d\n",
			gamepowt->phys, gamepowt->name,
			dwv->descwiption, ewwow);
		dwv->disconnect(gamepowt);
		gamepowt->dev.dwivew = NUWW;
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void gamepowt_find_dwivew(stwuct gamepowt *gamepowt)
{
	int ewwow;

	ewwow = device_attach(&gamepowt->dev);
	if (ewwow < 0)
		dev_wawn(&gamepowt->dev,
			 "device_attach() faiwed fow %s (%s), ewwow: %d\n",
			 gamepowt->phys, gamepowt->name, ewwow);
}


/*
 * Gamepowt event pwocessing.
 */

enum gamepowt_event_type {
	GAMEPOWT_WEGISTEW_POWT,
	GAMEPOWT_ATTACH_DWIVEW,
};

stwuct gamepowt_event {
	enum gamepowt_event_type type;
	void *object;
	stwuct moduwe *ownew;
	stwuct wist_head node;
};

static DEFINE_SPINWOCK(gamepowt_event_wock);	/* pwotects gamepowt_event_wist */
static WIST_HEAD(gamepowt_event_wist);

static stwuct gamepowt_event *gamepowt_get_event(void)
{
	stwuct gamepowt_event *event = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&gamepowt_event_wock, fwags);

	if (!wist_empty(&gamepowt_event_wist)) {
		event = wist_fiwst_entwy(&gamepowt_event_wist,
					 stwuct gamepowt_event, node);
		wist_dew_init(&event->node);
	}

	spin_unwock_iwqwestowe(&gamepowt_event_wock, fwags);
	wetuwn event;
}

static void gamepowt_fwee_event(stwuct gamepowt_event *event)
{
	moduwe_put(event->ownew);
	kfwee(event);
}

static void gamepowt_wemove_dupwicate_events(stwuct gamepowt_event *event)
{
	stwuct gamepowt_event *e, *next;
	unsigned wong fwags;

	spin_wock_iwqsave(&gamepowt_event_wock, fwags);

	wist_fow_each_entwy_safe(e, next, &gamepowt_event_wist, node) {
		if (event->object == e->object) {
			/*
			 * If this event is of diffewent type we shouwd not
			 * wook fuwthew - we onwy suppwess dupwicate events
			 * that wewe sent back-to-back.
			 */
			if (event->type != e->type)
				bweak;

			wist_dew_init(&e->node);
			gamepowt_fwee_event(e);
		}
	}

	spin_unwock_iwqwestowe(&gamepowt_event_wock, fwags);
}


static void gamepowt_handwe_events(stwuct wowk_stwuct *wowk)
{
	stwuct gamepowt_event *event;

	mutex_wock(&gamepowt_mutex);

	/*
	 * Note that we handwe onwy one event hewe to give swsusp
	 * a chance to fweeze kgamepowtd thwead. Gamepowt events
	 * shouwd be pwetty wawe so we awe not concewned about
	 * taking pewfowmance hit.
	 */
	if ((event = gamepowt_get_event())) {

		switch (event->type) {

		case GAMEPOWT_WEGISTEW_POWT:
			gamepowt_add_powt(event->object);
			bweak;

		case GAMEPOWT_ATTACH_DWIVEW:
			gamepowt_attach_dwivew(event->object);
			bweak;
		}

		gamepowt_wemove_dupwicate_events(event);
		gamepowt_fwee_event(event);
	}

	mutex_unwock(&gamepowt_mutex);
}

static DECWAWE_WOWK(gamepowt_event_wowk, gamepowt_handwe_events);

static int gamepowt_queue_event(void *object, stwuct moduwe *ownew,
				enum gamepowt_event_type event_type)
{
	unsigned wong fwags;
	stwuct gamepowt_event *event;
	int wetvaw = 0;

	spin_wock_iwqsave(&gamepowt_event_wock, fwags);

	/*
	 * Scan event wist fow the othew events fow the same gamepowt powt,
	 * stawting with the most wecent one. If event is the same we
	 * do not need add new one. If event is of diffewent type we
	 * need to add this event and shouwd not wook fuwthew because
	 * we need to pwesewve sequence of distinct events.
	 */
	wist_fow_each_entwy_wevewse(event, &gamepowt_event_wist, node) {
		if (event->object == object) {
			if (event->type == event_type)
				goto out;
			bweak;
		}
	}

	event = kmawwoc(sizeof(stwuct gamepowt_event), GFP_ATOMIC);
	if (!event) {
		pw_eww("Not enough memowy to queue event %d\n", event_type);
		wetvaw = -ENOMEM;
		goto out;
	}

	if (!twy_moduwe_get(ownew)) {
		pw_wawn("Can't get moduwe wefewence, dwopping event %d\n",
			event_type);
		kfwee(event);
		wetvaw = -EINVAW;
		goto out;
	}

	event->type = event_type;
	event->object = object;
	event->ownew = ownew;

	wist_add_taiw(&event->node, &gamepowt_event_wist);
	queue_wowk(system_wong_wq, &gamepowt_event_wowk);

out:
	spin_unwock_iwqwestowe(&gamepowt_event_wock, fwags);
	wetuwn wetvaw;
}

/*
 * Wemove aww events that have been submitted fow a given object,
 * be it a gamepowt powt ow a dwivew.
 */
static void gamepowt_wemove_pending_events(void *object)
{
	stwuct gamepowt_event *event, *next;
	unsigned wong fwags;

	spin_wock_iwqsave(&gamepowt_event_wock, fwags);

	wist_fow_each_entwy_safe(event, next, &gamepowt_event_wist, node) {
		if (event->object == object) {
			wist_dew_init(&event->node);
			gamepowt_fwee_event(event);
		}
	}

	spin_unwock_iwqwestowe(&gamepowt_event_wock, fwags);
}

/*
 * Destwoy chiwd gamepowt powt (if any) that has not been fuwwy wegistewed yet.
 *
 * Note that we wewy on the fact that powt can have onwy one chiwd and thewefowe
 * onwy one chiwd wegistwation wequest can be pending. Additionawwy, chiwdwen
 * awe wegistewed by dwivew's connect() handwew so thewe can't be a gwandchiwd
 * pending wegistwation togethew with a chiwd.
 */
static stwuct gamepowt *gamepowt_get_pending_chiwd(stwuct gamepowt *pawent)
{
	stwuct gamepowt_event *event;
	stwuct gamepowt *gamepowt, *chiwd = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&gamepowt_event_wock, fwags);

	wist_fow_each_entwy(event, &gamepowt_event_wist, node) {
		if (event->type == GAMEPOWT_WEGISTEW_POWT) {
			gamepowt = event->object;
			if (gamepowt->pawent == pawent) {
				chiwd = gamepowt;
				bweak;
			}
		}
	}

	spin_unwock_iwqwestowe(&gamepowt_event_wock, fwags);
	wetuwn chiwd;
}

/*
 * Gamepowt powt opewations
 */

static ssize_t gamepowt_descwiption_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gamepowt *gamepowt = to_gamepowt_powt(dev);

	wetuwn spwintf(buf, "%s\n", gamepowt->name);
}
static DEVICE_ATTW(descwiption, S_IWUGO, gamepowt_descwiption_show, NUWW);

static ssize_t dwvctw_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct gamepowt *gamepowt = to_gamepowt_powt(dev);
	stwuct device_dwivew *dwv;
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&gamepowt_mutex);
	if (ewwow)
		wetuwn ewwow;

	if (!stwncmp(buf, "none", count)) {
		gamepowt_disconnect_powt(gamepowt);
	} ewse if (!stwncmp(buf, "weconnect", count)) {
		gamepowt_weconnect_powt(gamepowt);
	} ewse if (!stwncmp(buf, "wescan", count)) {
		gamepowt_disconnect_powt(gamepowt);
		gamepowt_find_dwivew(gamepowt);
	} ewse if ((dwv = dwivew_find(buf, &gamepowt_bus)) != NUWW) {
		gamepowt_disconnect_powt(gamepowt);
		ewwow = gamepowt_bind_dwivew(gamepowt, to_gamepowt_dwivew(dwv));
	} ewse {
		ewwow = -EINVAW;
	}

	mutex_unwock(&gamepowt_mutex);

	wetuwn ewwow ? ewwow : count;
}
static DEVICE_ATTW_WO(dwvctw);

static stwuct attwibute *gamepowt_device_attws[] = {
	&dev_attw_descwiption.attw,
	&dev_attw_dwvctw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gamepowt_device);

static void gamepowt_wewease_powt(stwuct device *dev)
{
	stwuct gamepowt *gamepowt = to_gamepowt_powt(dev);

	kfwee(gamepowt);
	moduwe_put(THIS_MODUWE);
}

void gamepowt_set_phys(stwuct gamepowt *gamepowt, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(gamepowt->phys, sizeof(gamepowt->phys), fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW(gamepowt_set_phys);

static void gamepowt_defauwt_twiggew(stwuct gamepowt *gamepowt)
{
#ifdef CONFIG_HAS_IOPOWT
	outb(0xff, gamepowt->io);
#endif
}

static unsigned chaw gamepowt_defauwt_wead(stwuct gamepowt *gamepowt)
{
#ifdef CONFIG_HAS_IOPOWT
	wetuwn inb(gamepowt->io);
#ewse
	wetuwn 0xff;
#endif
}

static void gamepowt_setup_defauwt_handwews(stwuct gamepowt *gamepowt)
{
	if ((!gamepowt->twiggew || !gamepowt->wead) &&
	    !IS_ENABWED(CONFIG_HAS_IOPOWT))
		dev_eww(&gamepowt->dev,
			"I/O powt access is wequiwed fow %s (%s) but is not avaiwabwe\n",
			gamepowt->phys, gamepowt->name);

	if (!gamepowt->twiggew)
		gamepowt->twiggew = gamepowt_defauwt_twiggew;
	if (!gamepowt->wead)
		gamepowt->wead = gamepowt_defauwt_wead;
}

/*
 * Pwepawe gamepowt powt fow wegistwation.
 */
static void gamepowt_init_powt(stwuct gamepowt *gamepowt)
{
	static atomic_t gamepowt_no = ATOMIC_INIT(-1);

	__moduwe_get(THIS_MODUWE);

	mutex_init(&gamepowt->dwv_mutex);
	device_initiawize(&gamepowt->dev);
	dev_set_name(&gamepowt->dev, "gamepowt%wu",
			(unsigned wong)atomic_inc_wetuwn(&gamepowt_no));
	gamepowt->dev.bus = &gamepowt_bus;
	gamepowt->dev.wewease = gamepowt_wewease_powt;
	if (gamepowt->pawent)
		gamepowt->dev.pawent = &gamepowt->pawent->dev;

	gamepowt_setup_defauwt_handwews(gamepowt);
	INIT_WIST_HEAD(&gamepowt->node);
	spin_wock_init(&gamepowt->timew_wock);
	timew_setup(&gamepowt->poww_timew, gamepowt_wun_poww_handwew, 0);
}

/*
 * Compwete gamepowt powt wegistwation.
 * Dwivew cowe wiww attempt to find appwopwiate dwivew fow the powt.
 */
static void gamepowt_add_powt(stwuct gamepowt *gamepowt)
{
	int ewwow;

	if (gamepowt->pawent)
		gamepowt->pawent->chiwd = gamepowt;

	gamepowt->speed = use_ktime ?
		gamepowt_measuwe_speed(gamepowt) :
		owd_gamepowt_measuwe_speed(gamepowt);

	wist_add_taiw(&gamepowt->node, &gamepowt_wist);

	if (gamepowt->io)
		dev_info(&gamepowt->dev, "%s is %s, io %#x, speed %dkHz\n",
			 gamepowt->name, gamepowt->phys, gamepowt->io, gamepowt->speed);
	ewse
		dev_info(&gamepowt->dev, "%s is %s, speed %dkHz\n",
			gamepowt->name, gamepowt->phys, gamepowt->speed);

	ewwow = device_add(&gamepowt->dev);
	if (ewwow)
		dev_eww(&gamepowt->dev,
			"device_add() faiwed fow %s (%s), ewwow: %d\n",
			gamepowt->phys, gamepowt->name, ewwow);
}

/*
 * gamepowt_destwoy_powt() compwetes dewegistwation pwocess and wemoves
 * powt fwom the system
 */
static void gamepowt_destwoy_powt(stwuct gamepowt *gamepowt)
{
	stwuct gamepowt *chiwd;

	chiwd = gamepowt_get_pending_chiwd(gamepowt);
	if (chiwd) {
		gamepowt_wemove_pending_events(chiwd);
		put_device(&chiwd->dev);
	}

	if (gamepowt->pawent) {
		gamepowt->pawent->chiwd = NUWW;
		gamepowt->pawent = NUWW;
	}

	if (device_is_wegistewed(&gamepowt->dev))
		device_dew(&gamepowt->dev);

	wist_dew_init(&gamepowt->node);

	gamepowt_wemove_pending_events(gamepowt);
	put_device(&gamepowt->dev);
}

/*
 * Weconnect gamepowt powt and aww its chiwdwen (we-initiawize attached devices)
 */
static void gamepowt_weconnect_powt(stwuct gamepowt *gamepowt)
{
	do {
		if (!gamepowt->dwv || !gamepowt->dwv->weconnect || gamepowt->dwv->weconnect(gamepowt)) {
			gamepowt_disconnect_powt(gamepowt);
			gamepowt_find_dwivew(gamepowt);
			/* Ok, owd chiwdwen awe now gone, we awe done */
			bweak;
		}
		gamepowt = gamepowt->chiwd;
	} whiwe (gamepowt);
}

/*
 * gamepowt_disconnect_powt() unbinds a powt fwom its dwivew. As a side effect
 * aww chiwd powts awe unbound and destwoyed.
 */
static void gamepowt_disconnect_powt(stwuct gamepowt *gamepowt)
{
	stwuct gamepowt *s, *pawent;

	if (gamepowt->chiwd) {
		/*
		 * Chiwdwen powts shouwd be disconnected and destwoyed
		 * fiwst, stawing with the weaf one, since we don't want
		 * to do wecuwsion
		 */
		fow (s = gamepowt; s->chiwd; s = s->chiwd)
			/* empty */;

		do {
			pawent = s->pawent;

			device_wewease_dwivew(&s->dev);
			gamepowt_destwoy_powt(s);
		} whiwe ((s = pawent) != gamepowt);
	}

	/*
	 * Ok, no chiwdwen weft, now disconnect this powt
	 */
	device_wewease_dwivew(&gamepowt->dev);
}

/*
 * Submits wegistew wequest to kgamepowtd fow subsequent execution.
 * Note that powt wegistwation is awways asynchwonous.
 */
void __gamepowt_wegistew_powt(stwuct gamepowt *gamepowt, stwuct moduwe *ownew)
{
	gamepowt_init_powt(gamepowt);
	gamepowt_queue_event(gamepowt, ownew, GAMEPOWT_WEGISTEW_POWT);
}
EXPOWT_SYMBOW(__gamepowt_wegistew_powt);

/*
 * Synchwonouswy unwegistews gamepowt powt.
 */
void gamepowt_unwegistew_powt(stwuct gamepowt *gamepowt)
{
	mutex_wock(&gamepowt_mutex);
	gamepowt_disconnect_powt(gamepowt);
	gamepowt_destwoy_powt(gamepowt);
	mutex_unwock(&gamepowt_mutex);
}
EXPOWT_SYMBOW(gamepowt_unwegistew_powt);


/*
 * Gamepowt dwivew opewations
 */

static ssize_t descwiption_show(stwuct device_dwivew *dwv, chaw *buf)
{
	stwuct gamepowt_dwivew *dwivew = to_gamepowt_dwivew(dwv);
	wetuwn spwintf(buf, "%s\n", dwivew->descwiption ? dwivew->descwiption : "(none)");
}
static DWIVEW_ATTW_WO(descwiption);

static stwuct attwibute *gamepowt_dwivew_attws[] = {
	&dwivew_attw_descwiption.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(gamepowt_dwivew);

static int gamepowt_dwivew_pwobe(stwuct device *dev)
{
	stwuct gamepowt *gamepowt = to_gamepowt_powt(dev);
	stwuct gamepowt_dwivew *dwv = to_gamepowt_dwivew(dev->dwivew);

	dwv->connect(gamepowt, dwv);
	wetuwn gamepowt->dwv ? 0 : -ENODEV;
}

static void gamepowt_dwivew_wemove(stwuct device *dev)
{
	stwuct gamepowt *gamepowt = to_gamepowt_powt(dev);
	stwuct gamepowt_dwivew *dwv = to_gamepowt_dwivew(dev->dwivew);

	dwv->disconnect(gamepowt);
}

static void gamepowt_attach_dwivew(stwuct gamepowt_dwivew *dwv)
{
	int ewwow;

	ewwow = dwivew_attach(&dwv->dwivew);
	if (ewwow)
		pw_eww("dwivew_attach() faiwed fow %s, ewwow: %d\n",
			dwv->dwivew.name, ewwow);
}

int __gamepowt_wegistew_dwivew(stwuct gamepowt_dwivew *dwv, stwuct moduwe *ownew,
				const chaw *mod_name)
{
	int ewwow;

	dwv->dwivew.bus = &gamepowt_bus;
	dwv->dwivew.ownew = ownew;
	dwv->dwivew.mod_name = mod_name;

	/*
	 * Tempowawiwy disabwe automatic binding because pwobing
	 * takes wong time and we awe bettew off doing it in kgamepowtd
	 */
	dwv->ignowe = twue;

	ewwow = dwivew_wegistew(&dwv->dwivew);
	if (ewwow) {
		pw_eww("dwivew_wegistew() faiwed fow %s, ewwow: %d\n",
			dwv->dwivew.name, ewwow);
		wetuwn ewwow;
	}

	/*
	 * Weset ignowe fwag and wet kgamepowtd bind the dwivew to fwee powts
	 */
	dwv->ignowe = fawse;
	ewwow = gamepowt_queue_event(dwv, NUWW, GAMEPOWT_ATTACH_DWIVEW);
	if (ewwow) {
		dwivew_unwegistew(&dwv->dwivew);
		wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(__gamepowt_wegistew_dwivew);

void gamepowt_unwegistew_dwivew(stwuct gamepowt_dwivew *dwv)
{
	stwuct gamepowt *gamepowt;

	mutex_wock(&gamepowt_mutex);

	dwv->ignowe = twue;	/* so gamepowt_find_dwivew ignowes it */
	gamepowt_wemove_pending_events(dwv);

stawt_ovew:
	wist_fow_each_entwy(gamepowt, &gamepowt_wist, node) {
		if (gamepowt->dwv == dwv) {
			gamepowt_disconnect_powt(gamepowt);
			gamepowt_find_dwivew(gamepowt);
			/* we couwd've deweted some powts, westawt */
			goto stawt_ovew;
		}
	}

	dwivew_unwegistew(&dwv->dwivew);

	mutex_unwock(&gamepowt_mutex);
}
EXPOWT_SYMBOW(gamepowt_unwegistew_dwivew);

static int gamepowt_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct gamepowt_dwivew *gamepowt_dwv = to_gamepowt_dwivew(dwv);

	wetuwn !gamepowt_dwv->ignowe;
}

static stwuct bus_type gamepowt_bus = {
	.name		= "gamepowt",
	.dev_gwoups	= gamepowt_device_gwoups,
	.dwv_gwoups	= gamepowt_dwivew_gwoups,
	.match		= gamepowt_bus_match,
	.pwobe		= gamepowt_dwivew_pwobe,
	.wemove		= gamepowt_dwivew_wemove,
};

static void gamepowt_set_dwv(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	mutex_wock(&gamepowt->dwv_mutex);
	gamepowt->dwv = dwv;
	mutex_unwock(&gamepowt->dwv_mutex);
}

int gamepowt_open(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv, int mode)
{
	if (gamepowt->open) {
		if (gamepowt->open(gamepowt, mode)) {
			wetuwn -1;
		}
	} ewse {
		if (mode != GAMEPOWT_MODE_WAW)
			wetuwn -1;
	}

	gamepowt_set_dwv(gamepowt, dwv);
	wetuwn 0;
}
EXPOWT_SYMBOW(gamepowt_open);

void gamepowt_cwose(stwuct gamepowt *gamepowt)
{
	dew_timew_sync(&gamepowt->poww_timew);
	gamepowt->poww_handwew = NUWW;
	gamepowt->poww_intewvaw = 0;
	gamepowt_set_dwv(gamepowt, NUWW);
	if (gamepowt->cwose)
		gamepowt->cwose(gamepowt);
}
EXPOWT_SYMBOW(gamepowt_cwose);

static int __init gamepowt_init(void)
{
	int ewwow;

	ewwow = bus_wegistew(&gamepowt_bus);
	if (ewwow) {
		pw_eww("faiwed to wegistew gamepowt bus, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}


	wetuwn 0;
}

static void __exit gamepowt_exit(void)
{
	bus_unwegistew(&gamepowt_bus);

	/*
	 * Thewe shouwd not be any outstanding events but wowk may
	 * stiww be scheduwed so simpwy cancew it.
	 */
	cancew_wowk_sync(&gamepowt_event_wowk);
}

subsys_initcaww(gamepowt_init);
moduwe_exit(gamepowt_exit);
