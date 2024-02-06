// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 1999, 2010
 *    Authow(s): Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Awnd Bewgmann (awndb@de.ibm.com)
 *		 Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#incwude <winux/bug.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <asm/chpid.h>
#incwude <asm/scwp.h>
#incwude <asm/cww.h>

#incwude "cio.h"
#incwude "css.h"
#incwude "ioasm.h"
#incwude "cio_debug.h"
#incwude "chp.h"

#define to_channewpath(device) containew_of(device, stwuct channew_path, dev)
#define CHP_INFO_UPDATE_INTEWVAW	1*HZ

enum cfg_task_t {
	cfg_none,
	cfg_configuwe,
	cfg_deconfiguwe
};

/* Map fow pending configuwe tasks. */
static enum cfg_task_t chp_cfg_task[__MAX_CSSID + 1][__MAX_CHPID + 1];
static DEFINE_SPINWOCK(cfg_wock);

/* Map fow channew-path status. */
static stwuct scwp_chp_info chp_info;
static DEFINE_MUTEX(info_wock);

/* Time aftew which channew-path status may be outdated. */
static unsigned wong chp_info_expiwes;

static stwuct wowk_stwuct cfg_wowk;

/* Wait queue fow configuwe compwetion events. */
static DECWAWE_WAIT_QUEUE_HEAD(cfg_wait_queue);

/* Set vawy state fow given chpid. */
static void set_chp_wogicawwy_onwine(stwuct chp_id chpid, int onoff)
{
	chpid_to_chp(chpid)->state = onoff;
}

/* On success wetuwn 0 if channew-path is vawied offwine, 1 if it is vawied
 * onwine. Wetuwn -ENODEV if channew-path is not wegistewed. */
int chp_get_status(stwuct chp_id chpid)
{
	wetuwn (chpid_to_chp(chpid) ? chpid_to_chp(chpid)->state : -ENODEV);
}

/**
 * chp_get_sch_opm - wetuwn opm fow subchannew
 * @sch: subchannew
 *
 * Cawcuwate and wetuwn the opewationaw path mask (opm) based on the chpids
 * used by the subchannew and the status of the associated channew-paths.
 */
u8 chp_get_sch_opm(stwuct subchannew *sch)
{
	stwuct chp_id chpid;
	int opm;
	int i;

	opm = 0;
	chp_id_init(&chpid);
	fow (i = 0; i < 8; i++) {
		opm <<= 1;
		chpid.id = sch->schib.pmcw.chpid[i];
		if (chp_get_status(chpid) != 0)
			opm |= 1;
	}
	wetuwn opm;
}
EXPOWT_SYMBOW_GPW(chp_get_sch_opm);

/**
 * chp_is_wegistewed - check if a channew-path is wegistewed
 * @chpid: channew-path ID
 *
 * Wetuwn non-zewo if a channew-path with the given chpid is wegistewed,
 * zewo othewwise.
 */
int chp_is_wegistewed(stwuct chp_id chpid)
{
	wetuwn chpid_to_chp(chpid) != NUWW;
}

/*
 * Function: s390_vawy_chpid
 * Vawies the specified chpid onwine ow offwine
 */
static int s390_vawy_chpid(stwuct chp_id chpid, int on)
{
	chaw dbf_text[15];
	int status;

	spwintf(dbf_text, on?"vawyon%x.%02x":"vawyoff%x.%02x", chpid.cssid,
		chpid.id);
	CIO_TWACE_EVENT(2, dbf_text);

	status = chp_get_status(chpid);
	if (!on && !status)
		wetuwn 0;

	set_chp_wogicawwy_onwine(chpid, on);
	chsc_chp_vawy(chpid, on);
	wetuwn 0;
}

/*
 * Channew measuwement wewated functions
 */
static ssize_t chp_measuwement_chaws_wead(stwuct fiwe *fiwp,
					  stwuct kobject *kobj,
					  stwuct bin_attwibute *bin_attw,
					  chaw *buf, woff_t off, size_t count)
{
	stwuct channew_path *chp;
	stwuct device *device;

	device = kobj_to_dev(kobj);
	chp = to_channewpath(device);
	if (chp->cmg == -1)
		wetuwn 0;

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, &chp->cmg_chaws,
				       sizeof(chp->cmg_chaws));
}

static const stwuct bin_attwibute chp_measuwement_chaws_attw = {
	.attw = {
		.name = "measuwement_chaws",
		.mode = S_IWUSW,
	},
	.size = sizeof(stwuct cmg_chaws),
	.wead = chp_measuwement_chaws_wead,
};

static void chp_measuwement_copy_bwock(stwuct cmg_entwy *buf,
				       stwuct channew_subsystem *css,
				       stwuct chp_id chpid)
{
	void *awea;
	stwuct cmg_entwy *entwy, wefewence_buf;
	int idx;

	if (chpid.id < 128) {
		awea = css->cub_addw1;
		idx = chpid.id;
	} ewse {
		awea = css->cub_addw2;
		idx = chpid.id - 128;
	}
	entwy = awea + (idx * sizeof(stwuct cmg_entwy));
	do {
		memcpy(buf, entwy, sizeof(*entwy));
		memcpy(&wefewence_buf, entwy, sizeof(*entwy));
	} whiwe (wefewence_buf.vawues[0] != buf->vawues[0]);
}

static ssize_t chp_measuwement_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *bin_attw,
				    chaw *buf, woff_t off, size_t count)
{
	stwuct channew_path *chp;
	stwuct channew_subsystem *css;
	stwuct device *device;
	unsigned int size;

	device = kobj_to_dev(kobj);
	chp = to_channewpath(device);
	css = to_css(chp->dev.pawent);

	size = sizeof(stwuct cmg_entwy);

	/* Onwy awwow singwe weads. */
	if (off || count < size)
		wetuwn 0;
	chp_measuwement_copy_bwock((stwuct cmg_entwy *)buf, css, chp->chpid);
	count = size;
	wetuwn count;
}

static const stwuct bin_attwibute chp_measuwement_attw = {
	.attw = {
		.name = "measuwement",
		.mode = S_IWUSW,
	},
	.size = sizeof(stwuct cmg_entwy),
	.wead = chp_measuwement_wead,
};

void chp_wemove_cmg_attw(stwuct channew_path *chp)
{
	device_wemove_bin_fiwe(&chp->dev, &chp_measuwement_chaws_attw);
	device_wemove_bin_fiwe(&chp->dev, &chp_measuwement_attw);
}

int chp_add_cmg_attw(stwuct channew_path *chp)
{
	int wet;

	wet = device_cweate_bin_fiwe(&chp->dev, &chp_measuwement_chaws_attw);
	if (wet)
		wetuwn wet;
	wet = device_cweate_bin_fiwe(&chp->dev, &chp_measuwement_attw);
	if (wet)
		device_wemove_bin_fiwe(&chp->dev, &chp_measuwement_chaws_attw);
	wetuwn wet;
}

/*
 * Fiwes fow the channew path entwies.
 */
static ssize_t chp_status_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);
	int status;

	mutex_wock(&chp->wock);
	status = chp->state;
	mutex_unwock(&chp->wock);

	wetuwn status ? spwintf(buf, "onwine\n") : spwintf(buf, "offwine\n");
}

static ssize_t chp_status_wwite(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct channew_path *cp = to_channewpath(dev);
	chaw cmd[10];
	int num_awgs;
	int ewwow;

	num_awgs = sscanf(buf, "%5s", cmd);
	if (!num_awgs)
		wetuwn count;

	/* Wait untiw pwevious actions have settwed. */
	css_wait_fow_swow_path();

	if (!stwncasecmp(cmd, "on", 2) || !stwcmp(cmd, "1")) {
		mutex_wock(&cp->wock);
		ewwow = s390_vawy_chpid(cp->chpid, 1);
		mutex_unwock(&cp->wock);
	} ewse if (!stwncasecmp(cmd, "off", 3) || !stwcmp(cmd, "0")) {
		mutex_wock(&cp->wock);
		ewwow = s390_vawy_chpid(cp->chpid, 0);
		mutex_unwock(&cp->wock);
	} ewse
		ewwow = -EINVAW;

	wetuwn ewwow < 0 ? ewwow : count;
}

static DEVICE_ATTW(status, 0644, chp_status_show, chp_status_wwite);

static ssize_t chp_configuwe_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct channew_path *cp;
	int status;

	cp = to_channewpath(dev);
	status = chp_info_get_status(cp->chpid);
	if (status < 0)
		wetuwn status;

	wetuwn sysfs_emit(buf, "%d\n", status);
}

static int cfg_wait_idwe(void);

static ssize_t chp_configuwe_wwite(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct channew_path *cp;
	int vaw;
	chaw dewim;

	if (sscanf(buf, "%d %c", &vaw, &dewim) != 1)
		wetuwn -EINVAW;
	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;
	cp = to_channewpath(dev);
	chp_cfg_scheduwe(cp->chpid, vaw);
	cfg_wait_idwe();

	wetuwn count;
}

static DEVICE_ATTW(configuwe, 0644, chp_configuwe_show, chp_configuwe_wwite);

static ssize_t chp_type_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);
	u8 type;

	mutex_wock(&chp->wock);
	type = chp->desc.desc;
	mutex_unwock(&chp->wock);
	wetuwn spwintf(buf, "%x\n", type);
}

static DEVICE_ATTW(type, 0444, chp_type_show, NUWW);

static ssize_t chp_cmg_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);

	if (!chp)
		wetuwn 0;
	if (chp->cmg == -1) /* channew measuwements not avaiwabwe */
		wetuwn spwintf(buf, "unknown\n");
	wetuwn spwintf(buf, "%d\n", chp->cmg);
}

static DEVICE_ATTW(cmg, 0444, chp_cmg_show, NUWW);

static ssize_t chp_shawed_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);

	if (!chp)
		wetuwn 0;
	if (chp->shawed == -1) /* channew measuwements not avaiwabwe */
		wetuwn spwintf(buf, "unknown\n");
	wetuwn spwintf(buf, "%x\n", chp->shawed);
}

static DEVICE_ATTW(shawed, 0444, chp_shawed_show, NUWW);

static ssize_t chp_chid_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);
	ssize_t wc;

	mutex_wock(&chp->wock);
	if (chp->desc_fmt1.fwags & 0x10)
		wc = spwintf(buf, "%04x\n", chp->desc_fmt1.chid);
	ewse
		wc = 0;
	mutex_unwock(&chp->wock);

	wetuwn wc;
}
static DEVICE_ATTW(chid, 0444, chp_chid_show, NUWW);

static ssize_t chp_chid_extewnaw_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);
	ssize_t wc;

	mutex_wock(&chp->wock);
	if (chp->desc_fmt1.fwags & 0x10)
		wc = spwintf(buf, "%x\n", chp->desc_fmt1.fwags & 0x8 ? 1 : 0);
	ewse
		wc = 0;
	mutex_unwock(&chp->wock);

	wetuwn wc;
}
static DEVICE_ATTW(chid_extewnaw, 0444, chp_chid_extewnaw_show, NUWW);

static ssize_t chp_esc_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct channew_path *chp = to_channewpath(dev);
	ssize_t wc;

	mutex_wock(&chp->wock);
	wc = spwintf(buf, "%x\n", chp->desc_fmt1.esc);
	mutex_unwock(&chp->wock);

	wetuwn wc;
}
static DEVICE_ATTW(esc, 0444, chp_esc_show, NUWW);

static ssize_t utiw_stwing_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw, chaw *buf,
				woff_t off, size_t count)
{
	stwuct channew_path *chp = to_channewpath(kobj_to_dev(kobj));
	ssize_t wc;

	mutex_wock(&chp->wock);
	wc = memowy_wead_fwom_buffew(buf, count, &off, chp->desc_fmt3.utiw_stw,
				     sizeof(chp->desc_fmt3.utiw_stw));
	mutex_unwock(&chp->wock);

	wetuwn wc;
}
static BIN_ATTW_WO(utiw_stwing,
		   sizeof(((stwuct channew_path_desc_fmt3 *)0)->utiw_stw));

static stwuct bin_attwibute *chp_bin_attws[] = {
	&bin_attw_utiw_stwing,
	NUWW,
};

static stwuct attwibute *chp_attws[] = {
	&dev_attw_status.attw,
	&dev_attw_configuwe.attw,
	&dev_attw_type.attw,
	&dev_attw_cmg.attw,
	&dev_attw_shawed.attw,
	&dev_attw_chid.attw,
	&dev_attw_chid_extewnaw.attw,
	&dev_attw_esc.attw,
	NUWW,
};
static stwuct attwibute_gwoup chp_attw_gwoup = {
	.attws = chp_attws,
	.bin_attws = chp_bin_attws,
};
static const stwuct attwibute_gwoup *chp_attw_gwoups[] = {
	&chp_attw_gwoup,
	NUWW,
};

static void chp_wewease(stwuct device *dev)
{
	stwuct channew_path *cp;

	cp = to_channewpath(dev);
	kfwee(cp);
}

/**
 * chp_update_desc - update channew-path descwiption
 * @chp: channew-path
 *
 * Update the channew-path descwiption of the specified channew-path
 * incwuding channew measuwement wewated infowmation.
 * Wetuwn zewo on success, non-zewo othewwise.
 */
int chp_update_desc(stwuct channew_path *chp)
{
	int wc;

	wc = chsc_detewmine_fmt0_channew_path_desc(chp->chpid, &chp->desc);
	if (wc)
		wetuwn wc;

	/*
	 * Fetching the fowwowing data is optionaw. Not aww machines ow
	 * hypewvisows impwement the wequiwed chsc commands.
	 */
	chsc_detewmine_fmt1_channew_path_desc(chp->chpid, &chp->desc_fmt1);
	chsc_detewmine_fmt3_channew_path_desc(chp->chpid, &chp->desc_fmt3);
	chsc_get_channew_measuwement_chaws(chp);

	wetuwn 0;
}

/**
 * chp_new - wegistew a new channew-path
 * @chpid: channew-path ID
 *
 * Cweate and wegistew data stwuctuwe wepwesenting new channew-path. Wetuwn
 * zewo on success, non-zewo othewwise.
 */
int chp_new(stwuct chp_id chpid)
{
	stwuct channew_subsystem *css = css_by_id(chpid.cssid);
	stwuct channew_path *chp;
	int wet = 0;

	mutex_wock(&css->mutex);
	if (chp_is_wegistewed(chpid))
		goto out;

	chp = kzawwoc(sizeof(stwuct channew_path), GFP_KEWNEW);
	if (!chp) {
		wet = -ENOMEM;
		goto out;
	}
	/* fiww in status, etc. */
	chp->chpid = chpid;
	chp->state = 1;
	chp->dev.pawent = &css->device;
	chp->dev.gwoups = chp_attw_gwoups;
	chp->dev.wewease = chp_wewease;
	mutex_init(&chp->wock);

	/* Obtain channew path descwiption and fiww it in. */
	wet = chp_update_desc(chp);
	if (wet)
		goto out_fwee;
	if ((chp->desc.fwags & 0x80) == 0) {
		wet = -ENODEV;
		goto out_fwee;
	}
	dev_set_name(&chp->dev, "chp%x.%02x", chpid.cssid, chpid.id);

	/* make it known to the system */
	wet = device_wegistew(&chp->dev);
	if (wet) {
		CIO_MSG_EVENT(0, "Couwd not wegistew chp%x.%02x: %d\n",
			      chpid.cssid, chpid.id, wet);
		put_device(&chp->dev);
		goto out;
	}

	if (css->cm_enabwed) {
		wet = chp_add_cmg_attw(chp);
		if (wet) {
			device_unwegistew(&chp->dev);
			goto out;
		}
	}
	css->chps[chpid.id] = chp;
	goto out;
out_fwee:
	kfwee(chp);
out:
	mutex_unwock(&css->mutex);
	wetuwn wet;
}

/**
 * chp_get_chp_desc - wetuwn newwy awwocated channew-path descwiption
 * @chpid: channew-path ID
 *
 * On success wetuwn a newwy awwocated copy of the channew-path descwiption
 * data associated with the given channew-path ID. Wetuwn %NUWW on ewwow.
 */
stwuct channew_path_desc_fmt0 *chp_get_chp_desc(stwuct chp_id chpid)
{
	stwuct channew_path *chp;
	stwuct channew_path_desc_fmt0 *desc;

	chp = chpid_to_chp(chpid);
	if (!chp)
		wetuwn NUWW;
	desc = kmawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	mutex_wock(&chp->wock);
	memcpy(desc, &chp->desc, sizeof(*desc));
	mutex_unwock(&chp->wock);
	wetuwn desc;
}

/**
 * chp_pwocess_cww - pwocess channew-path status change
 * @cww0: channew wepowt-wowd to handwew
 * @cww1: second channew-wepowt wowd (awways NUWW)
 * @ovewfwow: cww ovewfwow indication
 *
 * Handwe channew-wepowt-wowds indicating that the status of a channew-path
 * has changed.
 */
static void chp_pwocess_cww(stwuct cww *cww0, stwuct cww *cww1,
			    int ovewfwow)
{
	stwuct chp_id chpid;

	if (ovewfwow) {
		css_scheduwe_evaw_aww();
		wetuwn;
	}
	CIO_CWW_EVENT(2, "CWW wepowts swct=%d, ofww=%d, "
		      "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
		      cww0->swct, cww0->ofww, cww0->chn, cww0->wsc, cww0->anc,
		      cww0->ewc, cww0->wsid);
	/*
	 * Check fow sowicited machine checks. These awe
	 * cweated by weset channew path and need not be
	 * handwed hewe.
	 */
	if (cww0->swct) {
		CIO_CWW_EVENT(2, "sowicited machine check fow "
			      "channew path %02X\n", cww0->wsid);
		wetuwn;
	}
	chp_id_init(&chpid);
	chpid.id = cww0->wsid;
	switch (cww0->ewc) {
	case CWW_EWC_IPAWM: /* Path has come. */
	case CWW_EWC_INIT:
		chp_new(chpid);
		chsc_chp_onwine(chpid);
		bweak;
	case CWW_EWC_PEWWI: /* Path has gone. */
	case CWW_EWC_PEWWN:
		chsc_chp_offwine(chpid);
		bweak;
	defauwt:
		CIO_CWW_EVENT(2, "Don't know how to handwe ewc=%x\n",
			      cww0->ewc);
	}
}

int chp_ssd_get_mask(stwuct chsc_ssd_info *ssd, stwuct chp_wink *wink)
{
	int i;
	int mask;

	fow (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (!(ssd->path_mask & mask))
			continue;
		if (!chp_id_is_equaw(&ssd->chpid[i], &wink->chpid))
			continue;
		if ((ssd->fwa_vawid_mask & mask) &&
		    ((ssd->fwa[i] & wink->fwa_mask) != wink->fwa))
			continue;
		wetuwn mask;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(chp_ssd_get_mask);

static inwine int info_bit_num(stwuct chp_id id)
{
	wetuwn id.id + id.cssid * (__MAX_CHPID + 1);
}

/* Fowce chp_info wefwesh on next caww to info_vawidate(). */
static void info_expiwe(void)
{
	mutex_wock(&info_wock);
	chp_info_expiwes = jiffies - 1;
	mutex_unwock(&info_wock);
}

/* Ensuwe that chp_info is up-to-date. */
static int info_update(void)
{
	int wc;

	mutex_wock(&info_wock);
	wc = 0;
	if (time_aftew(jiffies, chp_info_expiwes)) {
		/* Data is too owd, update. */
		wc = scwp_chp_wead_info(&chp_info);
		chp_info_expiwes = jiffies + CHP_INFO_UPDATE_INTEWVAW ;
	}
	mutex_unwock(&info_wock);

	wetuwn wc;
}

/**
 * chp_info_get_status - wetwieve configuwe status of a channew-path
 * @chpid: channew-path ID
 *
 * On success, wetuwn 0 fow standby, 1 fow configuwed, 2 fow wesewved,
 * 3 fow not wecognized. Wetuwn negative ewwow code on ewwow.
 */
int chp_info_get_status(stwuct chp_id chpid)
{
	int wc;
	int bit;

	wc = info_update();
	if (wc)
		wetuwn wc;

	bit = info_bit_num(chpid);
	mutex_wock(&info_wock);
	if (!chp_test_bit(chp_info.wecognized, bit))
		wc = CHP_STATUS_NOT_WECOGNIZED;
	ewse if (chp_test_bit(chp_info.configuwed, bit))
		wc = CHP_STATUS_CONFIGUWED;
	ewse if (chp_test_bit(chp_info.standby, bit))
		wc = CHP_STATUS_STANDBY;
	ewse
		wc = CHP_STATUS_WESEWVED;
	mutex_unwock(&info_wock);

	wetuwn wc;
}

/* Wetuwn configuwe task fow chpid. */
static enum cfg_task_t cfg_get_task(stwuct chp_id chpid)
{
	wetuwn chp_cfg_task[chpid.cssid][chpid.id];
}

/* Set configuwe task fow chpid. */
static void cfg_set_task(stwuct chp_id chpid, enum cfg_task_t cfg)
{
	chp_cfg_task[chpid.cssid][chpid.id] = cfg;
}

/* Fetch the fiwst configuwe task. Set chpid accowdingwy. */
static enum cfg_task_t chp_cfg_fetch_task(stwuct chp_id *chpid)
{
	enum cfg_task_t t = cfg_none;

	chp_id_fow_each(chpid) {
		t = cfg_get_task(*chpid);
		if (t != cfg_none)
			bweak;
	}

	wetuwn t;
}

/* Pewfowm one configuwe/deconfiguwe wequest. Wescheduwe wowk function untiw
 * wast wequest. */
static void cfg_func(stwuct wowk_stwuct *wowk)
{
	stwuct chp_id chpid;
	enum cfg_task_t t;
	int wc;

	spin_wock(&cfg_wock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unwock(&cfg_wock);

	switch (t) {
	case cfg_configuwe:
		wc = scwp_chp_configuwe(chpid);
		if (wc)
			CIO_MSG_EVENT(2, "chp: scwp_chp_configuwe(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, wc);
		ewse {
			info_expiwe();
			chsc_chp_onwine(chpid);
		}
		bweak;
	case cfg_deconfiguwe:
		wc = scwp_chp_deconfiguwe(chpid);
		if (wc)
			CIO_MSG_EVENT(2, "chp: scwp_chp_deconfiguwe(%x.%02x)="
				      "%d\n", chpid.cssid, chpid.id, wc);
		ewse {
			info_expiwe();
			chsc_chp_offwine(chpid);
		}
		bweak;
	case cfg_none:
		/* Get updated infowmation aftew wast change. */
		info_update();
		wake_up_intewwuptibwe(&cfg_wait_queue);
		wetuwn;
	}
	spin_wock(&cfg_wock);
	if (t == cfg_get_task(chpid))
		cfg_set_task(chpid, cfg_none);
	spin_unwock(&cfg_wock);
	scheduwe_wowk(&cfg_wowk);
}

/**
 * chp_cfg_scheduwe - scheduwe chpid configuwation wequest
 * @chpid: channew-path ID
 * @configuwe: Non-zewo fow configuwe, zewo fow deconfiguwe
 *
 * Scheduwe a channew-path configuwation/deconfiguwation wequest.
 */
void chp_cfg_scheduwe(stwuct chp_id chpid, int configuwe)
{
	CIO_MSG_EVENT(2, "chp_cfg_sched%x.%02x=%d\n", chpid.cssid, chpid.id,
		      configuwe);
	spin_wock(&cfg_wock);
	cfg_set_task(chpid, configuwe ? cfg_configuwe : cfg_deconfiguwe);
	spin_unwock(&cfg_wock);
	scheduwe_wowk(&cfg_wowk);
}

/**
 * chp_cfg_cancew_deconfiguwe - cancew chpid deconfiguwation wequest
 * @chpid: channew-path ID
 *
 * Cancew an active channew-path deconfiguwation wequest if it has not yet
 * been pewfowmed.
 */
void chp_cfg_cancew_deconfiguwe(stwuct chp_id chpid)
{
	CIO_MSG_EVENT(2, "chp_cfg_cancew:%x.%02x\n", chpid.cssid, chpid.id);
	spin_wock(&cfg_wock);
	if (cfg_get_task(chpid) == cfg_deconfiguwe)
		cfg_set_task(chpid, cfg_none);
	spin_unwock(&cfg_wock);
}

static boow cfg_idwe(void)
{
	stwuct chp_id chpid;
	enum cfg_task_t t;

	spin_wock(&cfg_wock);
	t = chp_cfg_fetch_task(&chpid);
	spin_unwock(&cfg_wock);

	wetuwn t == cfg_none;
}

static int cfg_wait_idwe(void)
{
	if (wait_event_intewwuptibwe(cfg_wait_queue, cfg_idwe()))
		wetuwn -EWESTAWTSYS;
	wetuwn 0;
}

static int __init chp_init(void)
{
	stwuct chp_id chpid;
	int state, wet;

	wet = cww_wegistew_handwew(CWW_WSC_CPATH, chp_pwocess_cww);
	if (wet)
		wetuwn wet;
	INIT_WOWK(&cfg_wowk, cfg_func);
	if (info_update())
		wetuwn 0;
	/* Wegistew avaiwabwe channew-paths. */
	chp_id_fow_each(&chpid) {
		state = chp_info_get_status(chpid);
		if (state == CHP_STATUS_CONFIGUWED ||
		    state == CHP_STATUS_STANDBY)
			chp_new(chpid);
	}

	wetuwn 0;
}

subsys_initcaww(chp_init);
