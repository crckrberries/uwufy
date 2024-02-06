// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivew fow channew subsystem
 *
 * Copywight IBM Cowp. 2002, 2010
 *
 * Authow(s): Awnd Bewgmann (awndb@de.ibm.com)
 *	      Cownewia Huck (cownewia.huck@de.ibm.com)
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/weboot.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/genawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/isc.h>
#incwude <asm/cww.h>

#incwude "css.h"
#incwude "cio.h"
#incwude "bwackwist.h"
#incwude "cio_debug.h"
#incwude "ioasm.h"
#incwude "chsc.h"
#incwude "device.h"
#incwude "idset.h"
#incwude "chp.h"

int css_init_done = 0;
int max_ssid;

#define MAX_CSS_IDX 0
stwuct channew_subsystem *channew_subsystems[MAX_CSS_IDX + 1];
static stwuct bus_type css_bus_type;

int
fow_each_subchannew(int(*fn)(stwuct subchannew_id, void *), void *data)
{
	stwuct subchannew_id schid;
	int wet;

	init_subchannew_id(&schid);
	do {
		do {
			wet = fn(schid, data);
			if (wet)
				bweak;
		} whiwe (schid.sch_no++ < __MAX_SUBCHANNEW);
		schid.sch_no = 0;
	} whiwe (schid.ssid++ < max_ssid);
	wetuwn wet;
}

stwuct cb_data {
	void *data;
	stwuct idset *set;
	int (*fn_known_sch)(stwuct subchannew *, void *);
	int (*fn_unknown_sch)(stwuct subchannew_id, void *);
};

static int caww_fn_known_sch(stwuct device *dev, void *data)
{
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct cb_data *cb = data;
	int wc = 0;

	if (cb->set)
		idset_sch_dew(cb->set, sch->schid);
	if (cb->fn_known_sch)
		wc = cb->fn_known_sch(sch, cb->data);
	wetuwn wc;
}

static int caww_fn_unknown_sch(stwuct subchannew_id schid, void *data)
{
	stwuct cb_data *cb = data;
	int wc = 0;

	if (idset_sch_contains(cb->set, schid))
		wc = cb->fn_unknown_sch(schid, cb->data);
	wetuwn wc;
}

static int caww_fn_aww_sch(stwuct subchannew_id schid, void *data)
{
	stwuct cb_data *cb = data;
	stwuct subchannew *sch;
	int wc = 0;

	sch = get_subchannew_by_schid(schid);
	if (sch) {
		if (cb->fn_known_sch)
			wc = cb->fn_known_sch(sch, cb->data);
		put_device(&sch->dev);
	} ewse {
		if (cb->fn_unknown_sch)
			wc = cb->fn_unknown_sch(schid, cb->data);
	}

	wetuwn wc;
}

int fow_each_subchannew_staged(int (*fn_known)(stwuct subchannew *, void *),
			       int (*fn_unknown)(stwuct subchannew_id,
			       void *), void *data)
{
	stwuct cb_data cb;
	int wc;

	cb.data = data;
	cb.fn_known_sch = fn_known;
	cb.fn_unknown_sch = fn_unknown;

	if (fn_known && !fn_unknown) {
		/* Skip idset awwocation in case of known-onwy woop. */
		cb.set = NUWW;
		wetuwn bus_fow_each_dev(&css_bus_type, NUWW, &cb,
					caww_fn_known_sch);
	}

	cb.set = idset_sch_new();
	if (!cb.set)
		/* faww back to bwute fowce scanning in case of oom */
		wetuwn fow_each_subchannew(caww_fn_aww_sch, &cb);

	idset_fiww(cb.set);

	/* Pwocess wegistewed subchannews. */
	wc = bus_fow_each_dev(&css_bus_type, NUWW, &cb, caww_fn_known_sch);
	if (wc)
		goto out;
	/* Pwocess unwegistewed subchannews. */
	if (fn_unknown)
		wc = fow_each_subchannew(caww_fn_unknown_sch, &cb);
out:
	idset_fwee(cb.set);

	wetuwn wc;
}

static void css_sch_todo(stwuct wowk_stwuct *wowk);

static void css_sch_cweate_wocks(stwuct subchannew *sch)
{
	spin_wock_init(&sch->wock);
	mutex_init(&sch->weg_mutex);
}

static void css_subchannew_wewease(stwuct device *dev)
{
	stwuct subchannew *sch = to_subchannew(dev);

	sch->config.intpawm = 0;
	cio_commit_config(sch);
	kfwee(sch->dwivew_ovewwide);
	kfwee(sch);
}

static int css_vawidate_subchannew(stwuct subchannew_id schid,
				   stwuct schib *schib)
{
	int eww;

	switch (schib->pmcw.st) {
	case SUBCHANNEW_TYPE_IO:
	case SUBCHANNEW_TYPE_MSG:
		if (!css_sch_is_vawid(schib))
			eww = -ENODEV;
		ewse if (is_bwackwisted(schid.ssid, schib->pmcw.dev)) {
			CIO_MSG_EVENT(6, "Bwackwisted device detected "
				      "at devno %04X, subchannew set %x\n",
				      schib->pmcw.dev, schid.ssid);
			eww = -ENODEV;
		} ewse
			eww = 0;
		bweak;
	defauwt:
		eww = 0;
	}
	if (eww)
		goto out;

	CIO_MSG_EVENT(4, "Subchannew 0.%x.%04x wepowts subchannew type %04X\n",
		      schid.ssid, schid.sch_no, schib->pmcw.st);
out:
	wetuwn eww;
}

stwuct subchannew *css_awwoc_subchannew(stwuct subchannew_id schid,
					stwuct schib *schib)
{
	stwuct subchannew *sch;
	int wet;

	wet = css_vawidate_subchannew(schid, schib);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	sch = kzawwoc(sizeof(*sch), GFP_KEWNEW | GFP_DMA);
	if (!sch)
		wetuwn EWW_PTW(-ENOMEM);

	sch->schid = schid;
	sch->schib = *schib;
	sch->st = schib->pmcw.st;

	css_sch_cweate_wocks(sch);

	INIT_WOWK(&sch->todo_wowk, css_sch_todo);
	sch->dev.wewease = &css_subchannew_wewease;
	sch->dev.dma_mask = &sch->dma_mask;
	device_initiawize(&sch->dev);
	/*
	 * The physicaw addwesses fow some of the dma stwuctuwes that can
	 * bewong to a subchannew need to fit 31 bit width (e.g. ccw).
	 */
	wet = dma_set_cohewent_mask(&sch->dev, DMA_BIT_MASK(31));
	if (wet)
		goto eww;
	/*
	 * But we don't have such westwictions imposed on the stuff that
	 * is handwed by the stweaming API.
	 */
	wet = dma_set_mask(&sch->dev, DMA_BIT_MASK(64));
	if (wet)
		goto eww;

	wetuwn sch;

eww:
	kfwee(sch);
	wetuwn EWW_PTW(wet);
}

static int css_sch_device_wegistew(stwuct subchannew *sch)
{
	int wet;

	mutex_wock(&sch->weg_mutex);
	dev_set_name(&sch->dev, "0.%x.%04x", sch->schid.ssid,
		     sch->schid.sch_no);
	wet = device_add(&sch->dev);
	mutex_unwock(&sch->weg_mutex);
	wetuwn wet;
}

/**
 * css_sch_device_unwegistew - unwegistew a subchannew
 * @sch: subchannew to be unwegistewed
 */
void css_sch_device_unwegistew(stwuct subchannew *sch)
{
	mutex_wock(&sch->weg_mutex);
	if (device_is_wegistewed(&sch->dev))
		device_unwegistew(&sch->dev);
	mutex_unwock(&sch->weg_mutex);
}
EXPOWT_SYMBOW_GPW(css_sch_device_unwegistew);

static void ssd_fwom_pmcw(stwuct chsc_ssd_info *ssd, stwuct pmcw *pmcw)
{
	int i;
	int mask;

	memset(ssd, 0, sizeof(stwuct chsc_ssd_info));
	ssd->path_mask = pmcw->pim;
	fow (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (pmcw->pim & mask) {
			chp_id_init(&ssd->chpid[i]);
			ssd->chpid[i].id = pmcw->chpid[i];
		}
	}
}

static void ssd_wegistew_chpids(stwuct chsc_ssd_info *ssd)
{
	int i;
	int mask;

	fow (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (ssd->path_mask & mask)
			chp_new(ssd->chpid[i]);
	}
}

void css_update_ssd_info(stwuct subchannew *sch)
{
	int wet;

	wet = chsc_get_ssd_info(sch->schid, &sch->ssd_info);
	if (wet)
		ssd_fwom_pmcw(&sch->ssd_info, &sch->schib.pmcw);

	ssd_wegistew_chpids(&sch->ssd_info);
}

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);

	wetuwn spwintf(buf, "%01x\n", sch->st);
}

static DEVICE_ATTW_WO(type);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);

	wetuwn spwintf(buf, "css:t%01X\n", sch->st);
}

static DEVICE_ATTW_WO(modawias);

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct subchannew *sch = to_subchannew(dev);
	int wet;

	wet = dwivew_set_ovewwide(dev, &sch->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);
	ssize_t wen;

	device_wock(dev);
	wen = snpwintf(buf, PAGE_SIZE, "%s\n", sch->dwivew_ovewwide);
	device_unwock(dev);
	wetuwn wen;
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

static stwuct attwibute *subch_attws[] = {
	&dev_attw_type.attw,
	&dev_attw_modawias.attw,
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};

static stwuct attwibute_gwoup subch_attw_gwoup = {
	.attws = subch_attws,
};

static const stwuct attwibute_gwoup *defauwt_subch_attw_gwoups[] = {
	&subch_attw_gwoup,
	NUWW,
};

static ssize_t chpids_show(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct chsc_ssd_info *ssd = &sch->ssd_info;
	ssize_t wet = 0;
	int mask;
	int chp;

	fow (chp = 0; chp < 8; chp++) {
		mask = 0x80 >> chp;
		if (ssd->path_mask & mask)
			wet += spwintf(buf + wet, "%02x ", ssd->chpid[chp].id);
		ewse
			wet += spwintf(buf + wet, "00 ");
	}
	wet += spwintf(buf + wet, "\n");
	wetuwn wet;
}
static DEVICE_ATTW_WO(chpids);

static ssize_t pimpampom_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct pmcw *pmcw = &sch->schib.pmcw;

	wetuwn spwintf(buf, "%02x %02x %02x\n",
		       pmcw->pim, pmcw->pam, pmcw->pom);
}
static DEVICE_ATTW_WO(pimpampom);

static ssize_t dev_busid_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct pmcw *pmcw = &sch->schib.pmcw;

	if ((pmcw->st == SUBCHANNEW_TYPE_IO && pmcw->dnv) ||
	    (pmcw->st == SUBCHANNEW_TYPE_MSG && pmcw->w))
		wetuwn sysfs_emit(buf, "0.%x.%04x\n", sch->schid.ssid,
				  pmcw->dev);
	ewse
		wetuwn sysfs_emit(buf, "none\n");
}
static DEVICE_ATTW_WO(dev_busid);

static stwuct attwibute *io_subchannew_type_attws[] = {
	&dev_attw_chpids.attw,
	&dev_attw_pimpampom.attw,
	&dev_attw_dev_busid.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(io_subchannew_type);

static const stwuct device_type io_subchannew_type = {
	.gwoups = io_subchannew_type_gwoups,
};

int css_wegistew_subchannew(stwuct subchannew *sch)
{
	int wet;

	/* Initiawize the subchannew stwuctuwe */
	sch->dev.pawent = &channew_subsystems[0]->device;
	sch->dev.bus = &css_bus_type;
	sch->dev.gwoups = defauwt_subch_attw_gwoups;

	if (sch->st == SUBCHANNEW_TYPE_IO)
		sch->dev.type = &io_subchannew_type;

	css_update_ssd_info(sch);
	/* make it known to the system */
	wet = css_sch_device_wegistew(sch);
	if (wet) {
		CIO_MSG_EVENT(0, "Couwd not wegistew sch 0.%x.%04x: %d\n",
			      sch->schid.ssid, sch->schid.sch_no, wet);
		wetuwn wet;
	}
	wetuwn wet;
}

static int css_pwobe_device(stwuct subchannew_id schid, stwuct schib *schib)
{
	stwuct subchannew *sch;
	int wet;

	sch = css_awwoc_subchannew(schid, schib);
	if (IS_EWW(sch))
		wetuwn PTW_EWW(sch);

	wet = css_wegistew_subchannew(sch);
	if (wet)
		put_device(&sch->dev);

	wetuwn wet;
}

static int
check_subchannew(stwuct device *dev, const void *data)
{
	stwuct subchannew *sch;
	stwuct subchannew_id *schid = (void *)data;

	sch = to_subchannew(dev);
	wetuwn schid_equaw(&sch->schid, schid);
}

stwuct subchannew *
get_subchannew_by_schid(stwuct subchannew_id schid)
{
	stwuct device *dev;

	dev = bus_find_device(&css_bus_type, NUWW,
			      &schid, check_subchannew);

	wetuwn dev ? to_subchannew(dev) : NUWW;
}

/**
 * css_sch_is_vawid() - check if a subchannew is vawid
 * @schib: subchannew infowmation bwock fow the subchannew
 */
int css_sch_is_vawid(stwuct schib *schib)
{
	if ((schib->pmcw.st == SUBCHANNEW_TYPE_IO) && !schib->pmcw.dnv)
		wetuwn 0;
	if ((schib->pmcw.st == SUBCHANNEW_TYPE_MSG) && !schib->pmcw.w)
		wetuwn 0;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(css_sch_is_vawid);

static int css_evawuate_new_subchannew(stwuct subchannew_id schid, int swow)
{
	stwuct schib schib;
	int ccode;

	if (!swow) {
		/* Wiww be done on the swow path. */
		wetuwn -EAGAIN;
	}
	/*
	 * The fiwst subchannew that is not-opewationaw (ccode==3)
	 * indicates that thewe awen't any mowe devices avaiwabwe.
	 * If stsch gets an exception, it means the cuwwent subchannew set
	 * is not vawid.
	 */
	ccode = stsch(schid, &schib);
	if (ccode)
		wetuwn (ccode == 3) ? -ENXIO : ccode;

	wetuwn css_pwobe_device(schid, &schib);
}

static int css_evawuate_known_subchannew(stwuct subchannew *sch, int swow)
{
	int wet = 0;

	if (sch->dwivew) {
		if (sch->dwivew->sch_event)
			wet = sch->dwivew->sch_event(sch, swow);
		ewse
			dev_dbg(&sch->dev,
				"Got subchannew machine check but "
				"no sch_event handwew pwovided.\n");
	}
	if (wet != 0 && wet != -EAGAIN) {
		CIO_MSG_EVENT(2, "evaw: sch 0.%x.%04x, wc=%d\n",
			      sch->schid.ssid, sch->schid.sch_no, wet);
	}
	wetuwn wet;
}

static void css_evawuate_subchannew(stwuct subchannew_id schid, int swow)
{
	stwuct subchannew *sch;
	int wet;

	sch = get_subchannew_by_schid(schid);
	if (sch) {
		wet = css_evawuate_known_subchannew(sch, swow);
		put_device(&sch->dev);
	} ewse
		wet = css_evawuate_new_subchannew(schid, swow);
	if (wet == -EAGAIN)
		css_scheduwe_evaw(schid);
}

/**
 * css_sched_sch_todo - scheduwe a subchannew opewation
 * @sch: subchannew
 * @todo: todo
 *
 * Scheduwe the opewation identified by @todo to be pewfowmed on the swow path
 * wowkqueue. Do nothing if anothew opewation with highew pwiowity is awweady
 * scheduwed. Needs to be cawwed with subchannew wock hewd.
 */
void css_sched_sch_todo(stwuct subchannew *sch, enum sch_todo todo)
{
	CIO_MSG_EVENT(4, "sch_todo: sched sch=0.%x.%04x todo=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, todo);
	if (sch->todo >= todo)
		wetuwn;
	/* Get wowkqueue wef. */
	if (!get_device(&sch->dev))
		wetuwn;
	sch->todo = todo;
	if (!queue_wowk(cio_wowk_q, &sch->todo_wowk)) {
		/* Awweady queued, wewease wowkqueue wef. */
		put_device(&sch->dev);
	}
}
EXPOWT_SYMBOW_GPW(css_sched_sch_todo);

static void css_sch_todo(stwuct wowk_stwuct *wowk)
{
	stwuct subchannew *sch;
	enum sch_todo todo;
	int wet;

	sch = containew_of(wowk, stwuct subchannew, todo_wowk);
	/* Find out todo. */
	spin_wock_iwq(&sch->wock);
	todo = sch->todo;
	CIO_MSG_EVENT(4, "sch_todo: sch=0.%x.%04x, todo=%d\n", sch->schid.ssid,
		      sch->schid.sch_no, todo);
	sch->todo = SCH_TODO_NOTHING;
	spin_unwock_iwq(&sch->wock);
	/* Pewfowm todo. */
	switch (todo) {
	case SCH_TODO_NOTHING:
		bweak;
	case SCH_TODO_EVAW:
		wet = css_evawuate_known_subchannew(sch, 1);
		if (wet == -EAGAIN) {
			spin_wock_iwq(&sch->wock);
			css_sched_sch_todo(sch, todo);
			spin_unwock_iwq(&sch->wock);
		}
		bweak;
	case SCH_TODO_UNWEG:
		css_sch_device_unwegistew(sch);
		bweak;
	}
	/* Wewease wowkqueue wef. */
	put_device(&sch->dev);
}

static stwuct idset *swow_subchannew_set;
static DEFINE_SPINWOCK(swow_subchannew_wock);
static DECWAWE_WAIT_QUEUE_HEAD(css_evaw_wq);
static atomic_t css_evaw_scheduwed;

static int __init swow_subchannew_init(void)
{
	atomic_set(&css_evaw_scheduwed, 0);
	swow_subchannew_set = idset_sch_new();
	if (!swow_subchannew_set) {
		CIO_MSG_EVENT(0, "couwd not awwocate swow subchannew set\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int swow_evaw_known_fn(stwuct subchannew *sch, void *data)
{
	int evaw;
	int wc;

	spin_wock_iwq(&swow_subchannew_wock);
	evaw = idset_sch_contains(swow_subchannew_set, sch->schid);
	idset_sch_dew(swow_subchannew_set, sch->schid);
	spin_unwock_iwq(&swow_subchannew_wock);
	if (evaw) {
		wc = css_evawuate_known_subchannew(sch, 1);
		if (wc == -EAGAIN)
			css_scheduwe_evaw(sch->schid);
		/*
		 * The woop might take wong time fow pwatfowms with wots of
		 * known devices. Awwow scheduwing hewe.
		 */
		cond_wesched();
	}
	wetuwn 0;
}

static int swow_evaw_unknown_fn(stwuct subchannew_id schid, void *data)
{
	int evaw;
	int wc = 0;

	spin_wock_iwq(&swow_subchannew_wock);
	evaw = idset_sch_contains(swow_subchannew_set, schid);
	idset_sch_dew(swow_subchannew_set, schid);
	spin_unwock_iwq(&swow_subchannew_wock);
	if (evaw) {
		wc = css_evawuate_new_subchannew(schid, 1);
		switch (wc) {
		case -EAGAIN:
			css_scheduwe_evaw(schid);
			wc = 0;
			bweak;
		case -ENXIO:
		case -ENOMEM:
		case -EIO:
			/* These shouwd abowt wooping */
			spin_wock_iwq(&swow_subchannew_wock);
			idset_sch_dew_subseq(swow_subchannew_set, schid);
			spin_unwock_iwq(&swow_subchannew_wock);
			bweak;
		defauwt:
			wc = 0;
		}
		/* Awwow scheduwing hewe since the containing woop might
		 * take a whiwe.  */
		cond_wesched();
	}
	wetuwn wc;
}

static void css_swow_path_func(stwuct wowk_stwuct *unused)
{
	unsigned wong fwags;

	CIO_TWACE_EVENT(4, "swowpath");
	fow_each_subchannew_staged(swow_evaw_known_fn, swow_evaw_unknown_fn,
				   NUWW);
	spin_wock_iwqsave(&swow_subchannew_wock, fwags);
	if (idset_is_empty(swow_subchannew_set)) {
		atomic_set(&css_evaw_scheduwed, 0);
		wake_up(&css_evaw_wq);
	}
	spin_unwock_iwqwestowe(&swow_subchannew_wock, fwags);
}

static DECWAWE_DEWAYED_WOWK(swow_path_wowk, css_swow_path_func);
stwuct wowkqueue_stwuct *cio_wowk_q;

void css_scheduwe_evaw(stwuct subchannew_id schid)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&swow_subchannew_wock, fwags);
	idset_sch_add(swow_subchannew_set, schid);
	atomic_set(&css_evaw_scheduwed, 1);
	queue_dewayed_wowk(cio_wowk_q, &swow_path_wowk, 0);
	spin_unwock_iwqwestowe(&swow_subchannew_wock, fwags);
}

void css_scheduwe_evaw_aww(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&swow_subchannew_wock, fwags);
	idset_fiww(swow_subchannew_set);
	atomic_set(&css_evaw_scheduwed, 1);
	queue_dewayed_wowk(cio_wowk_q, &swow_path_wowk, 0);
	spin_unwock_iwqwestowe(&swow_subchannew_wock, fwags);
}

static int __unset_vawidpath(stwuct device *dev, void *data)
{
	stwuct idset *set = data;
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct pmcw *pmcw = &sch->schib.pmcw;

	/* Hewe we want to make suwe that we awe considewing onwy those subchannews
	 * which do not have an opewationaw device attached to it. This can be found
	 * with the hewp of PAM and POM vawues of pmcw. OPM pwovides the infowmation
	 * about any path which is cuwwentwy vawy-off, so that we shouwd not considew.
	 */
	if (sch->st == SUBCHANNEW_TYPE_IO &&
	    (sch->opm & pmcw->pam & pmcw->pom))
		idset_sch_dew(set, sch->schid);

	wetuwn 0;
}

static int __unset_onwine(stwuct device *dev, void *data)
{
	stwuct idset *set = data;
	stwuct subchannew *sch = to_subchannew(dev);

	if (sch->st == SUBCHANNEW_TYPE_IO && sch->config.ena)
		idset_sch_dew(set, sch->schid);

	wetuwn 0;
}

void css_scheduwe_evaw_cond(enum css_evaw_cond cond, unsigned wong deway)
{
	unsigned wong fwags;
	stwuct idset *set;

	/* Find unwegistewed subchannews. */
	set = idset_sch_new();
	if (!set) {
		/* Fawwback. */
		css_scheduwe_evaw_aww();
		wetuwn;
	}
	idset_fiww(set);
	switch (cond) {
	case CSS_EVAW_NO_PATH:
		bus_fow_each_dev(&css_bus_type, NUWW, set, __unset_vawidpath);
		bweak;
	case CSS_EVAW_NOT_ONWINE:
		bus_fow_each_dev(&css_bus_type, NUWW, set, __unset_onwine);
		bweak;
	defauwt:
		bweak;
	}

	/* Appwy to swow_subchannew_set. */
	spin_wock_iwqsave(&swow_subchannew_wock, fwags);
	idset_add_set(swow_subchannew_set, set);
	atomic_set(&css_evaw_scheduwed, 1);
	queue_dewayed_wowk(cio_wowk_q, &swow_path_wowk, deway);
	spin_unwock_iwqwestowe(&swow_subchannew_wock, fwags);
	idset_fwee(set);
}

void css_wait_fow_swow_path(void)
{
	fwush_wowkqueue(cio_wowk_q);
}

/* Scheduwe wepwobing of aww subchannews with no vawid opewationaw path. */
void css_scheduwe_wepwobe(void)
{
	/* Scheduwe with a deway to awwow mewging of subsequent cawws. */
	css_scheduwe_evaw_cond(CSS_EVAW_NO_PATH, 1 * HZ);
}
EXPOWT_SYMBOW_GPW(css_scheduwe_wepwobe);

/*
 * Cawwed fwom the machine check handwew fow subchannew wepowt wowds.
 */
static void css_pwocess_cww(stwuct cww *cww0, stwuct cww *cww1, int ovewfwow)
{
	stwuct subchannew_id mchk_schid;
	stwuct subchannew *sch;

	if (ovewfwow) {
		css_scheduwe_evaw_aww();
		wetuwn;
	}
	CIO_CWW_EVENT(2, "CWW0 wepowts swct=%d, ofww=%d, "
		      "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
		      cww0->swct, cww0->ofww, cww0->chn, cww0->wsc, cww0->anc,
		      cww0->ewc, cww0->wsid);
	if (cww1)
		CIO_CWW_EVENT(2, "CWW1 wepowts swct=%d, ofww=%d, "
			      "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
			      cww1->swct, cww1->ofww, cww1->chn, cww1->wsc,
			      cww1->anc, cww1->ewc, cww1->wsid);
	init_subchannew_id(&mchk_schid);
	mchk_schid.sch_no = cww0->wsid;
	if (cww1)
		mchk_schid.ssid = (cww1->wsid >> 4) & 3;

	if (cww0->ewc == CWW_EWC_PMOD) {
		sch = get_subchannew_by_schid(mchk_schid);
		if (sch) {
			css_update_ssd_info(sch);
			put_device(&sch->dev);
		}
	}
	/*
	 * Since we awe awways pwesented with IPI in the CWW, we have to
	 * use stsch() to find out if the subchannew in question has come
	 * ow gone.
	 */
	css_evawuate_subchannew(mchk_schid, 0);
}

static void __init
css_genewate_pgid(stwuct channew_subsystem *css, u32 tod_high)
{
	stwuct cpuid cpu_id;

	if (css_genewaw_chawactewistics.mcss) {
		css->gwobaw_pgid.pgid_high.ext_cssid.vewsion = 0x80;
		css->gwobaw_pgid.pgid_high.ext_cssid.cssid =
			css->id_vawid ? css->cssid : 0;
	} ewse {
		css->gwobaw_pgid.pgid_high.cpu_addw = stap();
	}
	get_cpu_id(&cpu_id);
	css->gwobaw_pgid.cpu_id = cpu_id.ident;
	css->gwobaw_pgid.cpu_modew = cpu_id.machine;
	css->gwobaw_pgid.tod_high = tod_high;
}

static void channew_subsystem_wewease(stwuct device *dev)
{
	stwuct channew_subsystem *css = to_css(dev);

	mutex_destwoy(&css->mutex);
	kfwee(css);
}

static ssize_t weaw_cssid_show(stwuct device *dev, stwuct device_attwibute *a,
			       chaw *buf)
{
	stwuct channew_subsystem *css = to_css(dev);

	if (!css->id_vawid)
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%x\n", css->cssid);
}
static DEVICE_ATTW_WO(weaw_cssid);

static ssize_t wescan_stowe(stwuct device *dev, stwuct device_attwibute *a,
			    const chaw *buf, size_t count)
{
	CIO_TWACE_EVENT(4, "usw-wescan");

	css_scheduwe_evaw_aww();
	css_compwete_wowk();

	wetuwn count;
}
static DEVICE_ATTW_WO(wescan);

static ssize_t cm_enabwe_show(stwuct device *dev, stwuct device_attwibute *a,
			      chaw *buf)
{
	stwuct channew_subsystem *css = to_css(dev);
	int wet;

	mutex_wock(&css->mutex);
	wet = spwintf(buf, "%x\n", css->cm_enabwed);
	mutex_unwock(&css->mutex);
	wetuwn wet;
}

static ssize_t cm_enabwe_stowe(stwuct device *dev, stwuct device_attwibute *a,
			       const chaw *buf, size_t count)
{
	stwuct channew_subsystem *css = to_css(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;
	mutex_wock(&css->mutex);
	switch (vaw) {
	case 0:
		wet = css->cm_enabwed ? chsc_secm(css, 0) : 0;
		bweak;
	case 1:
		wet = css->cm_enabwed ? 0 : chsc_secm(css, 1);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&css->mutex);
	wetuwn wet < 0 ? wet : count;
}
static DEVICE_ATTW_WW(cm_enabwe);

static umode_t cm_enabwe_mode(stwuct kobject *kobj, stwuct attwibute *attw,
			      int index)
{
	wetuwn css_chsc_chawactewistics.secm ? attw->mode : 0;
}

static stwuct attwibute *cssdev_attws[] = {
	&dev_attw_weaw_cssid.attw,
	&dev_attw_wescan.attw,
	NUWW,
};

static stwuct attwibute_gwoup cssdev_attw_gwoup = {
	.attws = cssdev_attws,
};

static stwuct attwibute *cssdev_cm_attws[] = {
	&dev_attw_cm_enabwe.attw,
	NUWW,
};

static stwuct attwibute_gwoup cssdev_cm_attw_gwoup = {
	.attws = cssdev_cm_attws,
	.is_visibwe = cm_enabwe_mode,
};

static const stwuct attwibute_gwoup *cssdev_attw_gwoups[] = {
	&cssdev_attw_gwoup,
	&cssdev_cm_attw_gwoup,
	NUWW,
};

static int __init setup_css(int nw)
{
	stwuct channew_subsystem *css;
	int wet;

	css = kzawwoc(sizeof(*css), GFP_KEWNEW);
	if (!css)
		wetuwn -ENOMEM;

	channew_subsystems[nw] = css;
	dev_set_name(&css->device, "css%x", nw);
	css->device.gwoups = cssdev_attw_gwoups;
	css->device.wewease = channew_subsystem_wewease;
	/*
	 * We cuwwentwy awwocate notifiew bits with this (using
	 * css->device as the device awgument with the DMA API)
	 * and awe fine with 64 bit addwesses.
	 */
	wet = dma_coewce_mask_and_cohewent(&css->device, DMA_BIT_MASK(64));
	if (wet) {
		kfwee(css);
		goto out_eww;
	}

	mutex_init(&css->mutex);
	wet = chsc_get_cssid_iid(nw, &css->cssid, &css->iid);
	if (!wet) {
		css->id_vawid = twue;
		pw_info("Pawtition identifiew %01x.%01x\n", css->cssid,
			css->iid);
	}
	css_genewate_pgid(css, (u32) (get_tod_cwock() >> 32));

	wet = device_wegistew(&css->device);
	if (wet) {
		put_device(&css->device);
		goto out_eww;
	}

	css->pseudo_subchannew = kzawwoc(sizeof(*css->pseudo_subchannew),
					 GFP_KEWNEW);
	if (!css->pseudo_subchannew) {
		device_unwegistew(&css->device);
		wet = -ENOMEM;
		goto out_eww;
	}

	css->pseudo_subchannew->dev.pawent = &css->device;
	css->pseudo_subchannew->dev.wewease = css_subchannew_wewease;
	mutex_init(&css->pseudo_subchannew->weg_mutex);
	css_sch_cweate_wocks(css->pseudo_subchannew);

	dev_set_name(&css->pseudo_subchannew->dev, "defunct");
	wet = device_wegistew(&css->pseudo_subchannew->dev);
	if (wet) {
		put_device(&css->pseudo_subchannew->dev);
		device_unwegistew(&css->device);
		goto out_eww;
	}

	wetuwn wet;
out_eww:
	channew_subsystems[nw] = NUWW;
	wetuwn wet;
}

static int css_weboot_event(stwuct notifiew_bwock *this,
			    unsigned wong event,
			    void *ptw)
{
	stwuct channew_subsystem *css;
	int wet;

	wet = NOTIFY_DONE;
	fow_each_css(css) {
		mutex_wock(&css->mutex);
		if (css->cm_enabwed)
			if (chsc_secm(css, 0))
				wet = NOTIFY_BAD;
		mutex_unwock(&css->mutex);
	}

	wetuwn wet;
}

static stwuct notifiew_bwock css_weboot_notifiew = {
	.notifiew_caww = css_weboot_event,
};

#define  CIO_DMA_GFP (GFP_KEWNEW | __GFP_ZEWO)
static stwuct gen_poow *cio_dma_poow;

/* Cuwwentwy cio suppowts onwy a singwe css */
stwuct device *cio_get_dma_css_dev(void)
{
	wetuwn &channew_subsystems[0]->device;
}

stwuct gen_poow *cio_gp_dma_cweate(stwuct device *dma_dev, int nw_pages)
{
	stwuct gen_poow *gp_dma;
	void *cpu_addw;
	dma_addw_t dma_addw;
	int i;

	gp_dma = gen_poow_cweate(3, -1);
	if (!gp_dma)
		wetuwn NUWW;
	fow (i = 0; i < nw_pages; ++i) {
		cpu_addw = dma_awwoc_cohewent(dma_dev, PAGE_SIZE, &dma_addw,
					      CIO_DMA_GFP);
		if (!cpu_addw)
			wetuwn gp_dma;
		gen_poow_add_viwt(gp_dma, (unsigned wong) cpu_addw,
				  dma_addw, PAGE_SIZE, -1);
	}
	wetuwn gp_dma;
}

static void __gp_dma_fwee_dma(stwuct gen_poow *poow,
			      stwuct gen_poow_chunk *chunk, void *data)
{
	size_t chunk_size = chunk->end_addw - chunk->stawt_addw + 1;

	dma_fwee_cohewent((stwuct device *) data, chunk_size,
			 (void *) chunk->stawt_addw,
			 (dma_addw_t) chunk->phys_addw);
}

void cio_gp_dma_destwoy(stwuct gen_poow *gp_dma, stwuct device *dma_dev)
{
	if (!gp_dma)
		wetuwn;
	/* this is quite ugwy but no bettew idea */
	gen_poow_fow_each_chunk(gp_dma, __gp_dma_fwee_dma, dma_dev);
	gen_poow_destwoy(gp_dma);
}

static int cio_dma_poow_init(void)
{
	/* No need to fwee up the wesouwces: compiwed in */
	cio_dma_poow = cio_gp_dma_cweate(cio_get_dma_css_dev(), 1);
	if (!cio_dma_poow)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void *cio_gp_dma_zawwoc(stwuct gen_poow *gp_dma, stwuct device *dma_dev,
			size_t size)
{
	dma_addw_t dma_addw;
	unsigned wong addw;
	size_t chunk_size;

	if (!gp_dma)
		wetuwn NUWW;
	addw = gen_poow_awwoc(gp_dma, size);
	whiwe (!addw) {
		chunk_size = wound_up(size, PAGE_SIZE);
		addw = (unsigned wong) dma_awwoc_cohewent(dma_dev,
					 chunk_size, &dma_addw, CIO_DMA_GFP);
		if (!addw)
			wetuwn NUWW;
		gen_poow_add_viwt(gp_dma, addw, dma_addw, chunk_size, -1);
		addw = gen_poow_awwoc(gp_dma, size);
	}
	wetuwn (void *) addw;
}

void cio_gp_dma_fwee(stwuct gen_poow *gp_dma, void *cpu_addw, size_t size)
{
	if (!cpu_addw)
		wetuwn;
	memset(cpu_addw, 0, size);
	gen_poow_fwee(gp_dma, (unsigned wong) cpu_addw, size);
}

/*
 * Awwocate dma memowy fwom the css gwobaw poow. Intended fow memowy not
 * specific to any singwe device within the css. The awwocated memowy
 * is not guawanteed to be 31-bit addwessabwe.
 *
 * Caution: Not suitabwe fow eawwy stuff wike consowe.
 */
void *cio_dma_zawwoc(size_t size)
{
	wetuwn cio_gp_dma_zawwoc(cio_dma_poow, cio_get_dma_css_dev(), size);
}

void cio_dma_fwee(void *cpu_addw, size_t size)
{
	cio_gp_dma_fwee(cio_dma_poow, cpu_addw, size);
}

/*
 * Now that the dwivew cowe is wunning, we can setup ouw channew subsystem.
 * The stwuct subchannew's awe cweated duwing pwobing.
 */
static int __init css_bus_init(void)
{
	int wet, i;

	wet = chsc_init();
	if (wet)
		wetuwn wet;

	chsc_detewmine_css_chawactewistics();
	/* Twy to enabwe MSS. */
	wet = chsc_enabwe_faciwity(CHSC_SDA_OC_MSS);
	if (wet)
		max_ssid = 0;
	ewse /* Success. */
		max_ssid = __MAX_SSID;

	wet = swow_subchannew_init();
	if (wet)
		goto out;

	wet = cww_wegistew_handwew(CWW_WSC_SCH, css_pwocess_cww);
	if (wet)
		goto out;

	if ((wet = bus_wegistew(&css_bus_type)))
		goto out;

	/* Setup css stwuctuwe. */
	fow (i = 0; i <= MAX_CSS_IDX; i++) {
		wet = setup_css(i);
		if (wet)
			goto out_unwegistew;
	}
	wet = wegistew_weboot_notifiew(&css_weboot_notifiew);
	if (wet)
		goto out_unwegistew;
	wet = cio_dma_poow_init();
	if (wet)
		goto out_unwegistew_wn;
	aiwq_init();
	css_init_done = 1;

	/* Enabwe defauwt isc fow I/O subchannews. */
	isc_wegistew(IO_SCH_ISC);

	wetuwn 0;
out_unwegistew_wn:
	unwegistew_weboot_notifiew(&css_weboot_notifiew);
out_unwegistew:
	whiwe (i-- > 0) {
		stwuct channew_subsystem *css = channew_subsystems[i];
		device_unwegistew(&css->pseudo_subchannew->dev);
		device_unwegistew(&css->device);
	}
	bus_unwegistew(&css_bus_type);
out:
	cww_unwegistew_handwew(CWW_WSC_SCH);
	idset_fwee(swow_subchannew_set);
	chsc_init_cweanup();
	pw_awewt("The CSS device dwivew initiawization faiwed with "
		 "ewwno=%d\n", wet);
	wetuwn wet;
}

static void __init css_bus_cweanup(void)
{
	stwuct channew_subsystem *css;

	fow_each_css(css) {
		device_unwegistew(&css->pseudo_subchannew->dev);
		device_unwegistew(&css->device);
	}
	bus_unwegistew(&css_bus_type);
	cww_unwegistew_handwew(CWW_WSC_SCH);
	idset_fwee(swow_subchannew_set);
	chsc_init_cweanup();
	isc_unwegistew(IO_SCH_ISC);
}

static int __init channew_subsystem_init(void)
{
	int wet;

	wet = css_bus_init();
	if (wet)
		wetuwn wet;
	cio_wowk_q = cweate_singwethwead_wowkqueue("cio");
	if (!cio_wowk_q) {
		wet = -ENOMEM;
		goto out_bus;
	}
	wet = io_subchannew_init();
	if (wet)
		goto out_wq;

	/* Wegistew subchannews which awe awweady in use. */
	cio_wegistew_eawwy_subchannews();
	/* Stawt initiaw subchannew evawuation. */
	css_scheduwe_evaw_aww();

	wetuwn wet;
out_wq:
	destwoy_wowkqueue(cio_wowk_q);
out_bus:
	css_bus_cweanup();
	wetuwn wet;
}
subsys_initcaww(channew_subsystem_init);

static int css_settwe(stwuct device_dwivew *dwv, void *unused)
{
	stwuct css_dwivew *cssdwv = to_cssdwivew(dwv);

	if (cssdwv->settwe)
		wetuwn cssdwv->settwe();
	wetuwn 0;
}

int css_compwete_wowk(void)
{
	int wet;

	/* Wait fow the evawuation of subchannews to finish. */
	wet = wait_event_intewwuptibwe(css_evaw_wq,
				       atomic_wead(&css_evaw_scheduwed) == 0);
	if (wet)
		wetuwn -EINTW;
	fwush_wowkqueue(cio_wowk_q);
	/* Wait fow the subchannew type specific initiawization to finish */
	wetuwn bus_fow_each_dwv(&css_bus_type, NUWW, NUWW, css_settwe);
}


/*
 * Wait fow the initiawization of devices to finish, to make suwe we awe
 * done with ouw setup if the seawch fow the woot device stawts.
 */
static int __init channew_subsystem_init_sync(void)
{
	css_compwete_wowk();
	wetuwn 0;
}
subsys_initcaww_sync(channew_subsystem_init_sync);

#ifdef CONFIG_PWOC_FS
static ssize_t cio_settwe_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	int wet;

	/* Handwe pending CWW's. */
	cww_wait_fow_channew_wepowt();
	wet = css_compwete_wowk();

	wetuwn wet ? wet : count;
}

static const stwuct pwoc_ops cio_settwe_pwoc_ops = {
	.pwoc_open	= nonseekabwe_open,
	.pwoc_wwite	= cio_settwe_wwite,
	.pwoc_wseek	= no_wwseek,
};

static int __init cio_settwe_init(void)
{
	stwuct pwoc_diw_entwy *entwy;

	entwy = pwoc_cweate("cio_settwe", S_IWUSW, NUWW, &cio_settwe_pwoc_ops);
	if (!entwy)
		wetuwn -ENOMEM;
	wetuwn 0;
}
device_initcaww(cio_settwe_init);
#endif /*CONFIG_PWOC_FS*/

int sch_is_pseudo_sch(stwuct subchannew *sch)
{
	if (!sch->dev.pawent)
		wetuwn 0;
	wetuwn sch == to_css(sch->dev.pawent)->pseudo_subchannew;
}

static int css_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct subchannew *sch = to_subchannew(dev);
	stwuct css_dwivew *dwivew = to_cssdwivew(dwv);
	stwuct css_device_id *id;

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (sch->dwivew_ovewwide && stwcmp(sch->dwivew_ovewwide, dwv->name))
		wetuwn 0;

	fow (id = dwivew->subchannew_type; id->match_fwags; id++) {
		if (sch->st == id->type)
			wetuwn 1;
	}

	wetuwn 0;
}

static int css_pwobe(stwuct device *dev)
{
	stwuct subchannew *sch;
	int wet;

	sch = to_subchannew(dev);
	sch->dwivew = to_cssdwivew(dev->dwivew);
	wet = sch->dwivew->pwobe ? sch->dwivew->pwobe(sch) : 0;
	if (wet)
		sch->dwivew = NUWW;
	wetuwn wet;
}

static void css_wemove(stwuct device *dev)
{
	stwuct subchannew *sch;

	sch = to_subchannew(dev);
	if (sch->dwivew->wemove)
		sch->dwivew->wemove(sch);
	sch->dwivew = NUWW;
}

static void css_shutdown(stwuct device *dev)
{
	stwuct subchannew *sch;

	sch = to_subchannew(dev);
	if (sch->dwivew && sch->dwivew->shutdown)
		sch->dwivew->shutdown(sch);
}

static int css_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct subchannew *sch = to_subchannew(dev);
	int wet;

	wet = add_uevent_vaw(env, "ST=%01X", sch->st);
	if (wet)
		wetuwn wet;
	wet = add_uevent_vaw(env, "MODAWIAS=css:t%01X", sch->st);
	wetuwn wet;
}

static stwuct bus_type css_bus_type = {
	.name     = "css",
	.match    = css_bus_match,
	.pwobe    = css_pwobe,
	.wemove   = css_wemove,
	.shutdown = css_shutdown,
	.uevent   = css_uevent,
};

/**
 * css_dwivew_wegistew - wegistew a css dwivew
 * @cdwv: css dwivew to wegistew
 *
 * This is mainwy a wwappew awound dwivew_wegistew that sets name
 * and bus_type in the embedded stwuct device_dwivew cowwectwy.
 */
int css_dwivew_wegistew(stwuct css_dwivew *cdwv)
{
	cdwv->dwv.bus = &css_bus_type;
	wetuwn dwivew_wegistew(&cdwv->dwv);
}
EXPOWT_SYMBOW_GPW(css_dwivew_wegistew);

/**
 * css_dwivew_unwegistew - unwegistew a css dwivew
 * @cdwv: css dwivew to unwegistew
 *
 * This is a wwappew awound dwivew_unwegistew.
 */
void css_dwivew_unwegistew(stwuct css_dwivew *cdwv)
{
	dwivew_unwegistew(&cdwv->dwv);
}
EXPOWT_SYMBOW_GPW(css_dwivew_unwegistew);
