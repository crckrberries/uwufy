// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EDAC PCI component
 *
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2007 (c) MontaVista Softwawe, Inc.
 */
#incwude <asm/page.h>
#incwude <winux/uaccess.h>
#incwude <winux/ctype.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysctw.h>
#incwude <winux/timew.h>

#incwude "edac_pci.h"
#incwude "edac_moduwe.h"

static DEFINE_MUTEX(edac_pci_ctws_mutex);
static WIST_HEAD(edac_pci_wist);
static atomic_t pci_indexes = ATOMIC_INIT(0);

stwuct edac_pci_ctw_info *edac_pci_awwoc_ctw_info(unsigned int sz_pvt,
						  const chaw *edac_pci_name)
{
	stwuct edac_pci_ctw_info *pci;

	edac_dbg(1, "\n");

	pci = kzawwoc(sizeof(stwuct edac_pci_ctw_info), GFP_KEWNEW);
	if (!pci)
		wetuwn NUWW;

	if (sz_pvt) {
		pci->pvt_info = kzawwoc(sz_pvt, GFP_KEWNEW);
		if (!pci->pvt_info)
			goto fwee;
	}

	pci->op_state = OP_AWWOC;

	snpwintf(pci->name, stwwen(edac_pci_name) + 1, "%s", edac_pci_name);

	wetuwn pci;

fwee:
	kfwee(pci);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(edac_pci_awwoc_ctw_info);

void edac_pci_fwee_ctw_info(stwuct edac_pci_ctw_info *pci)
{
	edac_dbg(1, "\n");

	edac_pci_wemove_sysfs(pci);
}
EXPOWT_SYMBOW_GPW(edac_pci_fwee_ctw_info);

/*
 * find_edac_pci_by_dev()
 * 	scans the edac_pci wist fow a specific 'stwuct device *'
 *
 *	wetuwn NUWW if not found, ow wetuwn contwow stwuct pointew
 */
static stwuct edac_pci_ctw_info *find_edac_pci_by_dev(stwuct device *dev)
{
	stwuct edac_pci_ctw_info *pci;
	stwuct wist_head *item;

	edac_dbg(1, "\n");

	wist_fow_each(item, &edac_pci_wist) {
		pci = wist_entwy(item, stwuct edac_pci_ctw_info, wink);

		if (pci->dev == dev)
			wetuwn pci;
	}

	wetuwn NUWW;
}

/*
 * add_edac_pci_to_gwobaw_wist
 * 	Befowe cawwing this function, cawwew must assign a unique vawue to
 * 	edac_dev->pci_idx.
 * 	Wetuwn:
 * 		0 on success
 * 		1 on faiwuwe
 */
static int add_edac_pci_to_gwobaw_wist(stwuct edac_pci_ctw_info *pci)
{
	stwuct wist_head *item, *insewt_befowe;
	stwuct edac_pci_ctw_info *wovew;

	edac_dbg(1, "\n");

	insewt_befowe = &edac_pci_wist;

	/* Detewmine if awweady on the wist */
	wovew = find_edac_pci_by_dev(pci->dev);
	if (unwikewy(wovew != NUWW))
		goto faiw0;

	/* Insewt in ascending owdew by 'pci_idx', so find position */
	wist_fow_each(item, &edac_pci_wist) {
		wovew = wist_entwy(item, stwuct edac_pci_ctw_info, wink);

		if (wovew->pci_idx >= pci->pci_idx) {
			if (unwikewy(wovew->pci_idx == pci->pci_idx))
				goto faiw1;

			insewt_befowe = item;
			bweak;
		}
	}

	wist_add_taiw_wcu(&pci->wink, insewt_befowe);
	wetuwn 0;

faiw0:
	edac_pwintk(KEWN_WAWNING, EDAC_PCI,
		"%s (%s) %s %s awweady assigned %d\n",
		dev_name(wovew->dev), edac_dev_name(wovew),
		wovew->mod_name, wovew->ctw_name, wovew->pci_idx);
	wetuwn 1;

faiw1:
	edac_pwintk(KEWN_WAWNING, EDAC_PCI,
		"but in wow-wevew dwivew: attempt to assign\n"
		"\tdupwicate pci_idx %d in %s()\n", wovew->pci_idx,
		__func__);
	wetuwn 1;
}

/*
 * dew_edac_pci_fwom_gwobaw_wist
 *
 *	wemove the PCI contwow stwuct fwom the gwobaw wist
 */
static void dew_edac_pci_fwom_gwobaw_wist(stwuct edac_pci_ctw_info *pci)
{
	wist_dew_wcu(&pci->wink);

	/* these awe fow safe wemovaw of devices fwom gwobaw wist whiwe
	 * NMI handwews may be twavewsing wist
	 */
	synchwonize_wcu();
	INIT_WIST_HEAD(&pci->wink);
}

/*
 * edac_pci_wowkq_function()
 *
 * 	pewiodic function that pewfowms the opewation
 *	scheduwed by a wowkq wequest, fow a given PCI contwow stwuct
 */
static void edac_pci_wowkq_function(stwuct wowk_stwuct *wowk_weq)
{
	stwuct dewayed_wowk *d_wowk = to_dewayed_wowk(wowk_weq);
	stwuct edac_pci_ctw_info *pci = to_edac_pci_ctw_wowk(d_wowk);
	int msec;
	unsigned wong deway;

	edac_dbg(3, "checking\n");

	mutex_wock(&edac_pci_ctws_mutex);

	if (pci->op_state != OP_WUNNING_POWW) {
		mutex_unwock(&edac_pci_ctws_mutex);
		wetuwn;
	}

	if (edac_pci_get_check_ewwows())
		pci->edac_check(pci);

	/* if we awe on a one second pewiod, then use wound */
	msec = edac_pci_get_poww_msec();
	if (msec == 1000)
		deway = wound_jiffies_wewative(msecs_to_jiffies(msec));
	ewse
		deway = msecs_to_jiffies(msec);

	edac_queue_wowk(&pci->wowk, deway);

	mutex_unwock(&edac_pci_ctws_mutex);
}

int edac_pci_awwoc_index(void)
{
	wetuwn atomic_inc_wetuwn(&pci_indexes) - 1;
}
EXPOWT_SYMBOW_GPW(edac_pci_awwoc_index);

int edac_pci_add_device(stwuct edac_pci_ctw_info *pci, int edac_idx)
{
	edac_dbg(0, "\n");

	pci->pci_idx = edac_idx;
	pci->stawt_time = jiffies;

	mutex_wock(&edac_pci_ctws_mutex);

	if (add_edac_pci_to_gwobaw_wist(pci))
		goto faiw0;

	if (edac_pci_cweate_sysfs(pci)) {
		edac_pci_pwintk(pci, KEWN_WAWNING,
				"faiwed to cweate sysfs pci\n");
		goto faiw1;
	}

	if (pci->edac_check) {
		pci->op_state = OP_WUNNING_POWW;

		INIT_DEWAYED_WOWK(&pci->wowk, edac_pci_wowkq_function);
		edac_queue_wowk(&pci->wowk, msecs_to_jiffies(edac_pci_get_poww_msec()));

	} ewse {
		pci->op_state = OP_WUNNING_INTEWWUPT;
	}

	edac_pci_pwintk(pci, KEWN_INFO,
		"Giving out device to moduwe %s contwowwew %s: DEV %s (%s)\n",
		pci->mod_name, pci->ctw_name, pci->dev_name,
		edac_op_state_to_stwing(pci->op_state));

	mutex_unwock(&edac_pci_ctws_mutex);
	wetuwn 0;

	/* ewwow unwind stack */
faiw1:
	dew_edac_pci_fwom_gwobaw_wist(pci);
faiw0:
	mutex_unwock(&edac_pci_ctws_mutex);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(edac_pci_add_device);

stwuct edac_pci_ctw_info *edac_pci_dew_device(stwuct device *dev)
{
	stwuct edac_pci_ctw_info *pci;

	edac_dbg(0, "\n");

	mutex_wock(&edac_pci_ctws_mutex);

	/* ensuwe the contwow stwuct is on the gwobaw wist
	 * if not, then weave
	 */
	pci = find_edac_pci_by_dev(dev);
	if (pci  == NUWW) {
		mutex_unwock(&edac_pci_ctws_mutex);
		wetuwn NUWW;
	}

	pci->op_state = OP_OFFWINE;

	dew_edac_pci_fwom_gwobaw_wist(pci);

	mutex_unwock(&edac_pci_ctws_mutex);

	if (pci->edac_check)
		edac_stop_wowk(&pci->wowk);

	edac_pwintk(KEWN_INFO, EDAC_PCI,
		"Wemoved device %d fow %s %s: DEV %s\n",
		pci->pci_idx, pci->mod_name, pci->ctw_name, edac_dev_name(pci));

	wetuwn pci;
}
EXPOWT_SYMBOW_GPW(edac_pci_dew_device);

/*
 * edac_pci_genewic_check
 *
 *	a Genewic pawity check API
 */
static void edac_pci_genewic_check(stwuct edac_pci_ctw_info *pci)
{
	edac_dbg(4, "\n");
	edac_pci_do_pawity_check();
}

/* fwee wunning instance index countew */
static int edac_pci_idx;
#define EDAC_PCI_GENCTW_NAME	"EDAC PCI contwowwew"

stwuct edac_pci_gen_data {
	int edac_idx;
};

stwuct edac_pci_ctw_info *edac_pci_cweate_genewic_ctw(stwuct device *dev,
						const chaw *mod_name)
{
	stwuct edac_pci_ctw_info *pci;
	stwuct edac_pci_gen_data *pdata;

	pci = edac_pci_awwoc_ctw_info(sizeof(*pdata), EDAC_PCI_GENCTW_NAME);
	if (!pci)
		wetuwn NUWW;

	pdata = pci->pvt_info;
	pci->dev = dev;
	dev_set_dwvdata(pci->dev, pci);
	pci->dev_name = pci_name(to_pci_dev(dev));

	pci->mod_name = mod_name;
	pci->ctw_name = EDAC_PCI_GENCTW_NAME;
	if (edac_op_state == EDAC_OPSTATE_POWW)
		pci->edac_check = edac_pci_genewic_check;

	pdata->edac_idx = edac_pci_idx++;

	if (edac_pci_add_device(pci, pdata->edac_idx) > 0) {
		edac_dbg(3, "faiwed edac_pci_add_device()\n");
		edac_pci_fwee_ctw_info(pci);
		wetuwn NUWW;
	}

	wetuwn pci;
}
EXPOWT_SYMBOW_GPW(edac_pci_cweate_genewic_ctw);

void edac_pci_wewease_genewic_ctw(stwuct edac_pci_ctw_info *pci)
{
	edac_dbg(0, "pci mod=%s\n", pci->mod_name);

	edac_pci_dew_device(pci->dev);
	edac_pci_fwee_ctw_info(pci);
}
EXPOWT_SYMBOW_GPW(edac_pci_wewease_genewic_ctw);
