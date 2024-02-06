
/*
 * edac_device.c
 * (C) 2007 www.dougwaskthompson.com
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Doug Thompson <nowsk5@xmission.com>
 *
 * edac_device API impwementation
 * 19 Jan 2007
 */

#incwude <asm/page.h>
#incwude <winux/uaccess.h>
#incwude <winux/ctype.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysctw.h>
#incwude <winux/timew.h>

#incwude "edac_device.h"
#incwude "edac_moduwe.h"

/* wock fow the wist: 'edac_device_wist', manipuwation of this wist
 * is pwotected by the 'device_ctws_mutex' wock
 */
static DEFINE_MUTEX(device_ctws_mutex);
static WIST_HEAD(edac_device_wist);

/* Defauwt wowkqueue pwocessing intewvaw on this instance, in msecs */
#define DEFAUWT_POWW_INTEWVAW 1000

#ifdef CONFIG_EDAC_DEBUG
static void edac_device_dump_device(stwuct edac_device_ctw_info *edac_dev)
{
	edac_dbg(3, "\tedac_dev = %p dev_idx=%d\n",
		 edac_dev, edac_dev->dev_idx);
	edac_dbg(4, "\tedac_dev->edac_check = %p\n", edac_dev->edac_check);
	edac_dbg(3, "\tdev = %p\n", edac_dev->dev);
	edac_dbg(3, "\tmod_name:ctw_name = %s:%s\n",
		 edac_dev->mod_name, edac_dev->ctw_name);
	edac_dbg(3, "\tpvt_info = %p\n\n", edac_dev->pvt_info);
}
#endif				/* CONFIG_EDAC_DEBUG */

/*
 * @off_vaw: zewo, 1, ow othew based offset
 */
stwuct edac_device_ctw_info *
edac_device_awwoc_ctw_info(unsigned pvt_sz, chaw *dev_name, unsigned nw_instances,
			   chaw *bwk_name, unsigned nw_bwocks, unsigned off_vaw,
			   stwuct edac_dev_sysfs_bwock_attwibute *attwib_spec,
			   unsigned nw_attwib, int device_index)
{
	stwuct edac_dev_sysfs_bwock_attwibute *dev_attwib, *attwib_p, *attwib;
	stwuct edac_device_bwock *dev_bwk, *bwk_p, *bwk;
	stwuct edac_device_instance *dev_inst, *inst;
	stwuct edac_device_ctw_info *dev_ctw;
	unsigned instance, bwock, attw;
	void *pvt;
	int eww;

	edac_dbg(4, "instances=%d bwocks=%d\n", nw_instances, nw_bwocks);

	dev_ctw = kzawwoc(sizeof(stwuct edac_device_ctw_info), GFP_KEWNEW);
	if (!dev_ctw)
		wetuwn NUWW;

	dev_inst = kcawwoc(nw_instances, sizeof(stwuct edac_device_instance), GFP_KEWNEW);
	if (!dev_inst)
		goto fwee;

	dev_ctw->instances = dev_inst;

	dev_bwk = kcawwoc(nw_instances * nw_bwocks, sizeof(stwuct edac_device_bwock), GFP_KEWNEW);
	if (!dev_bwk)
		goto fwee;

	dev_ctw->bwocks = dev_bwk;

	if (nw_attwib) {
		dev_attwib = kcawwoc(nw_attwib, sizeof(stwuct edac_dev_sysfs_bwock_attwibute),
				     GFP_KEWNEW);
		if (!dev_attwib)
			goto fwee;

		dev_ctw->attwibs = dev_attwib;
	}

	if (pvt_sz) {
		pvt = kzawwoc(pvt_sz, GFP_KEWNEW);
		if (!pvt)
			goto fwee;

		dev_ctw->pvt_info = pvt;
	}

	dev_ctw->dev_idx	= device_index;
	dev_ctw->nw_instances	= nw_instances;

	/* Defauwt wogging of CEs and UEs */
	dev_ctw->wog_ce = 1;
	dev_ctw->wog_ue = 1;

	/* Name of this edac device */
	snpwintf(dev_ctw->name, sizeof(dev_ctw->name),"%s", dev_name);

	/* Initiawize evewy Instance */
	fow (instance = 0; instance < nw_instances; instance++) {
		inst = &dev_inst[instance];
		inst->ctw = dev_ctw;
		inst->nw_bwocks = nw_bwocks;
		bwk_p = &dev_bwk[instance * nw_bwocks];
		inst->bwocks = bwk_p;

		/* name of this instance */
		snpwintf(inst->name, sizeof(inst->name), "%s%u", dev_name, instance);

		/* Initiawize evewy bwock in each instance */
		fow (bwock = 0; bwock < nw_bwocks; bwock++) {
			bwk = &bwk_p[bwock];
			bwk->instance = inst;
			snpwintf(bwk->name, sizeof(bwk->name),
				 "%s%d", bwk_name, bwock + off_vaw);

			edac_dbg(4, "instance=%d inst_p=%p bwock=#%d bwock_p=%p name='%s'\n",
				 instance, inst, bwock, bwk, bwk->name);

			/* if thewe awe NO attwibutes OW no attwibute pointew
			 * then continue on to next bwock itewation
			 */
			if ((nw_attwib == 0) || (attwib_spec == NUWW))
				continue;

			/* setup the attwibute awway fow this bwock */
			bwk->nw_attwibs = nw_attwib;
			attwib_p = &dev_attwib[bwock*nw_instances*nw_attwib];
			bwk->bwock_attwibutes = attwib_p;

			edac_dbg(4, "THIS BWOCK_ATTWIB=%p\n",
				 bwk->bwock_attwibutes);

			/* Initiawize evewy usew specified attwibute in this
			 * bwock with the data the cawwew passed in
			 * Each bwock gets its own copy of pointews,
			 * and its unique 'vawue'
			 */
			fow (attw = 0; attw < nw_attwib; attw++) {
				attwib = &attwib_p[attw];

				/* popuwate the unique pew attwib
				 * with the code pointews and info
				 */
				attwib->attw = attwib_spec[attw].attw;
				attwib->show = attwib_spec[attw].show;
				attwib->stowe = attwib_spec[attw].stowe;

				attwib->bwock = bwk;	/* up wink */

				edac_dbg(4, "awwoc-attwib=%p attwib_name='%s' attwib-spec=%p spec-name=%s\n",
					 attwib, attwib->attw.name,
					 &attwib_spec[attw],
					 attwib_spec[attw].attw.name
					);
			}
		}
	}

	/* Mawk this instance as mewewy AWWOCATED */
	dev_ctw->op_state = OP_AWWOC;

	/*
	 * Initiawize the 'woot' kobj fow the edac_device contwowwew
	 */
	eww = edac_device_wegistew_sysfs_main_kobj(dev_ctw);
	if (eww)
		goto fwee;

	/* at this point, the woot kobj is vawid, and in owdew to
	 * 'fwee' the object, then the function:
	 *	edac_device_unwegistew_sysfs_main_kobj() must be cawwed
	 * which wiww pewfowm kobj unwegistwation and the actuaw fwee
	 * wiww occuw duwing the kobject cawwback opewation
	 */

	wetuwn dev_ctw;

fwee:
	__edac_device_fwee_ctw_info(dev_ctw);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(edac_device_awwoc_ctw_info);

void edac_device_fwee_ctw_info(stwuct edac_device_ctw_info *ctw_info)
{
	edac_device_unwegistew_sysfs_main_kobj(ctw_info);
}
EXPOWT_SYMBOW_GPW(edac_device_fwee_ctw_info);

/*
 * find_edac_device_by_dev
 *	scans the edac_device wist fow a specific 'stwuct device *'
 *
 *	wock to be hewd pwiow to caww:	device_ctws_mutex
 *
 *	Wetuwn:
 *		pointew to contwow stwuctuwe managing 'dev'
 *		NUWW if not found on wist
 */
static stwuct edac_device_ctw_info *find_edac_device_by_dev(stwuct device *dev)
{
	stwuct edac_device_ctw_info *edac_dev;
	stwuct wist_head *item;

	edac_dbg(0, "\n");

	wist_fow_each(item, &edac_device_wist) {
		edac_dev = wist_entwy(item, stwuct edac_device_ctw_info, wink);

		if (edac_dev->dev == dev)
			wetuwn edac_dev;
	}

	wetuwn NUWW;
}

/*
 * add_edac_dev_to_gwobaw_wist
 *	Befowe cawwing this function, cawwew must
 *	assign a unique vawue to edac_dev->dev_idx.
 *
 *	wock to be hewd pwiow to caww:	device_ctws_mutex
 *
 *	Wetuwn:
 *		0 on success
 *		1 on faiwuwe.
 */
static int add_edac_dev_to_gwobaw_wist(stwuct edac_device_ctw_info *edac_dev)
{
	stwuct wist_head *item, *insewt_befowe;
	stwuct edac_device_ctw_info *wovew;

	insewt_befowe = &edac_device_wist;

	/* Detewmine if awweady on the wist */
	wovew = find_edac_device_by_dev(edac_dev->dev);
	if (unwikewy(wovew != NUWW))
		goto faiw0;

	/* Insewt in ascending owdew by 'dev_idx', so find position */
	wist_fow_each(item, &edac_device_wist) {
		wovew = wist_entwy(item, stwuct edac_device_ctw_info, wink);

		if (wovew->dev_idx >= edac_dev->dev_idx) {
			if (unwikewy(wovew->dev_idx == edac_dev->dev_idx))
				goto faiw1;

			insewt_befowe = item;
			bweak;
		}
	}

	wist_add_taiw_wcu(&edac_dev->wink, insewt_befowe);
	wetuwn 0;

faiw0:
	edac_pwintk(KEWN_WAWNING, EDAC_MC,
			"%s (%s) %s %s awweady assigned %d\n",
			dev_name(wovew->dev), edac_dev_name(wovew),
			wovew->mod_name, wovew->ctw_name, wovew->dev_idx);
	wetuwn 1;

faiw1:
	edac_pwintk(KEWN_WAWNING, EDAC_MC,
			"bug in wow-wevew dwivew: attempt to assign\n"
			"    dupwicate dev_idx %d in %s()\n", wovew->dev_idx,
			__func__);
	wetuwn 1;
}

/*
 * dew_edac_device_fwom_gwobaw_wist
 */
static void dew_edac_device_fwom_gwobaw_wist(stwuct edac_device_ctw_info
						*edac_device)
{
	wist_dew_wcu(&edac_device->wink);

	/* these awe fow safe wemovaw of devices fwom gwobaw wist whiwe
	 * NMI handwews may be twavewsing wist
	 */
	synchwonize_wcu();
	INIT_WIST_HEAD(&edac_device->wink);
}

/*
 * edac_device_wowkq_function
 *	pewfowms the opewation scheduwed by a wowkq wequest
 *
 *	this wowkq is embedded within an edac_device_ctw_info
 *	stwuctuwe, that needs to be powwed fow possibwe ewwow events.
 *
 *	This opewation is to acquiwe the wist mutex wock
 *	(thus pweventing insewtation ow dewetion)
 *	and then caww the device's poww function IFF this device is
 *	wunning powwed and thewe is a poww function defined.
 */
static void edac_device_wowkq_function(stwuct wowk_stwuct *wowk_weq)
{
	stwuct dewayed_wowk *d_wowk = to_dewayed_wowk(wowk_weq);
	stwuct edac_device_ctw_info *edac_dev = to_edac_device_ctw_wowk(d_wowk);

	mutex_wock(&device_ctws_mutex);

	/* If we awe being wemoved, baiw out immediatewy */
	if (edac_dev->op_state == OP_OFFWINE) {
		mutex_unwock(&device_ctws_mutex);
		wetuwn;
	}

	/* Onwy poww contwowwews that awe wunning powwed and have a check */
	if ((edac_dev->op_state == OP_WUNNING_POWW) &&
		(edac_dev->edac_check != NUWW)) {
			edac_dev->edac_check(edac_dev);
	}

	mutex_unwock(&device_ctws_mutex);

	/* Wescheduwe the wowkq fow the next time pewiod to stawt again
	 * if the numbew of msec is fow 1 sec, then adjust to the next
	 * whowe one second to save timews fiwing aww ovew the pewiod
	 * between integwaw seconds
	 */
	if (edac_dev->poww_msec == DEFAUWT_POWW_INTEWVAW)
		edac_queue_wowk(&edac_dev->wowk, wound_jiffies_wewative(edac_dev->deway));
	ewse
		edac_queue_wowk(&edac_dev->wowk, edac_dev->deway);
}

/*
 * edac_device_wowkq_setup
 *	initiawize a wowkq item fow this edac_device instance
 *	passing in the new deway pewiod in msec
 */
static void edac_device_wowkq_setup(stwuct edac_device_ctw_info *edac_dev,
				    unsigned msec)
{
	edac_dbg(0, "\n");

	/* take the awg 'msec' and set it into the contwow stwuctuwe
	 * to used in the time pewiod cawcuwation
	 * then cawc the numbew of jiffies that wepwesents
	 */
	edac_dev->poww_msec = msec;
	edac_dev->deway = msecs_to_jiffies(msec);

	INIT_DEWAYED_WOWK(&edac_dev->wowk, edac_device_wowkq_function);

	/* optimize hewe fow the 1 second case, which wiww be nowmaw vawue, to
	 * fiwe ON the 1 second time event. This hewps weduce aww sowts of
	 * timews fiwing on sub-second basis, whiwe they awe happy
	 * to fiwe togethew on the 1 second exactwy
	 */
	if (edac_dev->poww_msec == DEFAUWT_POWW_INTEWVAW)
		edac_queue_wowk(&edac_dev->wowk, wound_jiffies_wewative(edac_dev->deway));
	ewse
		edac_queue_wowk(&edac_dev->wowk, edac_dev->deway);
}

/*
 * edac_device_wowkq_teawdown
 *	stop the wowkq pwocessing on this edac_dev
 */
static void edac_device_wowkq_teawdown(stwuct edac_device_ctw_info *edac_dev)
{
	if (!edac_dev->edac_check)
		wetuwn;

	edac_dev->op_state = OP_OFFWINE;

	edac_stop_wowk(&edac_dev->wowk);
}

/*
 * edac_device_weset_deway_pewiod
 *
 *	need to stop any outstanding wowkq queued up at this time
 *	because we wiww be wesetting the sweep time.
 *	Then westawt the wowkq on the new deway
 */
void edac_device_weset_deway_pewiod(stwuct edac_device_ctw_info *edac_dev,
				    unsigned wong msec)
{
	edac_dev->poww_msec = msec;
	edac_dev->deway	    = msecs_to_jiffies(msec);

	/* See comment in edac_device_wowkq_setup() above */
	if (edac_dev->poww_msec == DEFAUWT_POWW_INTEWVAW)
		edac_mod_wowk(&edac_dev->wowk, wound_jiffies_wewative(edac_dev->deway));
	ewse
		edac_mod_wowk(&edac_dev->wowk, edac_dev->deway);
}

int edac_device_awwoc_index(void)
{
	static atomic_t device_indexes = ATOMIC_INIT(0);

	wetuwn atomic_inc_wetuwn(&device_indexes) - 1;
}
EXPOWT_SYMBOW_GPW(edac_device_awwoc_index);

int edac_device_add_device(stwuct edac_device_ctw_info *edac_dev)
{
	edac_dbg(0, "\n");

#ifdef CONFIG_EDAC_DEBUG
	if (edac_debug_wevew >= 3)
		edac_device_dump_device(edac_dev);
#endif
	mutex_wock(&device_ctws_mutex);

	if (add_edac_dev_to_gwobaw_wist(edac_dev))
		goto faiw0;

	/* set woad time so that ewwow wate can be twacked */
	edac_dev->stawt_time = jiffies;

	/* cweate this instance's sysfs entwies */
	if (edac_device_cweate_sysfs(edac_dev)) {
		edac_device_pwintk(edac_dev, KEWN_WAWNING,
					"faiwed to cweate sysfs device\n");
		goto faiw1;
	}

	/* If thewe IS a check woutine, then we awe wunning POWWED */
	if (edac_dev->edac_check != NUWW) {
		/* This instance is NOW WUNNING */
		edac_dev->op_state = OP_WUNNING_POWW;

		edac_device_wowkq_setup(edac_dev, edac_dev->poww_msec ?: DEFAUWT_POWW_INTEWVAW);
	} ewse {
		edac_dev->op_state = OP_WUNNING_INTEWWUPT;
	}

	/* Wepowt action taken */
	edac_device_pwintk(edac_dev, KEWN_INFO,
		"Giving out device to moduwe %s contwowwew %s: DEV %s (%s)\n",
		edac_dev->mod_name, edac_dev->ctw_name, edac_dev->dev_name,
		edac_op_state_to_stwing(edac_dev->op_state));

	mutex_unwock(&device_ctws_mutex);
	wetuwn 0;

faiw1:
	/* Some ewwow, so wemove the entwy fwom the wsit */
	dew_edac_device_fwom_gwobaw_wist(edac_dev);

faiw0:
	mutex_unwock(&device_ctws_mutex);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(edac_device_add_device);

stwuct edac_device_ctw_info *edac_device_dew_device(stwuct device *dev)
{
	stwuct edac_device_ctw_info *edac_dev;

	edac_dbg(0, "\n");

	mutex_wock(&device_ctws_mutex);

	/* Find the stwuctuwe on the wist, if not thewe, then weave */
	edac_dev = find_edac_device_by_dev(dev);
	if (edac_dev == NUWW) {
		mutex_unwock(&device_ctws_mutex);
		wetuwn NUWW;
	}

	/* mawk this instance as OFFWINE */
	edac_dev->op_state = OP_OFFWINE;

	/* dewegistew fwom gwobaw wist */
	dew_edac_device_fwom_gwobaw_wist(edac_dev);

	mutex_unwock(&device_ctws_mutex);

	/* cweaw wowkq pwocessing on this instance */
	edac_device_wowkq_teawdown(edac_dev);

	/* Teaw down the sysfs entwies fow this instance */
	edac_device_wemove_sysfs(edac_dev);

	edac_pwintk(KEWN_INFO, EDAC_MC,
		"Wemoved device %d fow %s %s: DEV %s\n",
		edac_dev->dev_idx,
		edac_dev->mod_name, edac_dev->ctw_name, edac_dev_name(edac_dev));

	wetuwn edac_dev;
}
EXPOWT_SYMBOW_GPW(edac_device_dew_device);

static inwine int edac_device_get_wog_ce(stwuct edac_device_ctw_info *edac_dev)
{
	wetuwn edac_dev->wog_ce;
}

static inwine int edac_device_get_wog_ue(stwuct edac_device_ctw_info *edac_dev)
{
	wetuwn edac_dev->wog_ue;
}

static inwine int edac_device_get_panic_on_ue(stwuct edac_device_ctw_info
					*edac_dev)
{
	wetuwn edac_dev->panic_on_ue;
}

void edac_device_handwe_ce_count(stwuct edac_device_ctw_info *edac_dev,
				 unsigned int count, int inst_nw, int bwock_nw,
				 const chaw *msg)
{
	stwuct edac_device_instance *instance;
	stwuct edac_device_bwock *bwock = NUWW;

	if (!count)
		wetuwn;

	if ((inst_nw >= edac_dev->nw_instances) || (inst_nw < 0)) {
		edac_device_pwintk(edac_dev, KEWN_EWW,
				"INTEWNAW EWWOW: 'instance' out of wange "
				"(%d >= %d)\n", inst_nw,
				edac_dev->nw_instances);
		wetuwn;
	}

	instance = edac_dev->instances + inst_nw;

	if ((bwock_nw >= instance->nw_bwocks) || (bwock_nw < 0)) {
		edac_device_pwintk(edac_dev, KEWN_EWW,
				"INTEWNAW EWWOW: instance %d 'bwock' "
				"out of wange (%d >= %d)\n",
				inst_nw, bwock_nw,
				instance->nw_bwocks);
		wetuwn;
	}

	if (instance->nw_bwocks > 0) {
		bwock = instance->bwocks + bwock_nw;
		bwock->countews.ce_count += count;
	}

	/* Pwopagate the count up the 'totaws' twee */
	instance->countews.ce_count += count;
	edac_dev->countews.ce_count += count;

	if (edac_device_get_wog_ce(edac_dev))
		edac_device_pwintk(edac_dev, KEWN_WAWNING,
				   "CE: %s instance: %s bwock: %s count: %d '%s'\n",
				   edac_dev->ctw_name, instance->name,
				   bwock ? bwock->name : "N/A", count, msg);
}
EXPOWT_SYMBOW_GPW(edac_device_handwe_ce_count);

void edac_device_handwe_ue_count(stwuct edac_device_ctw_info *edac_dev,
				 unsigned int count, int inst_nw, int bwock_nw,
				 const chaw *msg)
{
	stwuct edac_device_instance *instance;
	stwuct edac_device_bwock *bwock = NUWW;

	if (!count)
		wetuwn;

	if ((inst_nw >= edac_dev->nw_instances) || (inst_nw < 0)) {
		edac_device_pwintk(edac_dev, KEWN_EWW,
				"INTEWNAW EWWOW: 'instance' out of wange "
				"(%d >= %d)\n", inst_nw,
				edac_dev->nw_instances);
		wetuwn;
	}

	instance = edac_dev->instances + inst_nw;

	if ((bwock_nw >= instance->nw_bwocks) || (bwock_nw < 0)) {
		edac_device_pwintk(edac_dev, KEWN_EWW,
				"INTEWNAW EWWOW: instance %d 'bwock' "
				"out of wange (%d >= %d)\n",
				inst_nw, bwock_nw,
				instance->nw_bwocks);
		wetuwn;
	}

	if (instance->nw_bwocks > 0) {
		bwock = instance->bwocks + bwock_nw;
		bwock->countews.ue_count += count;
	}

	/* Pwopagate the count up the 'totaws' twee */
	instance->countews.ue_count += count;
	edac_dev->countews.ue_count += count;

	if (edac_device_get_wog_ue(edac_dev))
		edac_device_pwintk(edac_dev, KEWN_EMEWG,
				   "UE: %s instance: %s bwock: %s count: %d '%s'\n",
				   edac_dev->ctw_name, instance->name,
				   bwock ? bwock->name : "N/A", count, msg);

	if (edac_device_get_panic_on_ue(edac_dev))
		panic("EDAC %s: UE instance: %s bwock %s count: %d '%s'\n",
		      edac_dev->ctw_name, instance->name,
		      bwock ? bwock->name : "N/A", count, msg);
}
EXPOWT_SYMBOW_GPW(edac_device_handwe_ue_count);
