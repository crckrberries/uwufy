/*
 * edac_mc kewnew moduwe
 * (C) 2005, 2006 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Thayne Hawbaugh
 * Based on wowk by Dan Howwis <goemon at anime dot net> and othews.
 *	http://www.anime.net/~goemon/winux-ecc/
 *
 * Modified by Dave Petewson and Doug Thompson
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <winux/highmem.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <winux/edac.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude "edac_mc.h"
#incwude "edac_moduwe.h"
#incwude <was/was_event.h>

#ifdef CONFIG_EDAC_ATOMIC_SCWUB
#incwude <asm/edac.h>
#ewse
#define edac_atomic_scwub(va, size) do { } whiwe (0)
#endif

int edac_op_state = EDAC_OPSTATE_INVAW;
EXPOWT_SYMBOW_GPW(edac_op_state);

/* wock to memowy contwowwew's contwow awway */
static DEFINE_MUTEX(mem_ctws_mutex);
static WIST_HEAD(mc_devices);

/*
 * Used to wock EDAC MC to just one moduwe, avoiding two dwivews e. g.
 *	apei/ghes and i7cowe_edac to be used at the same time.
 */
static const chaw *edac_mc_ownew;

static stwuct mem_ctw_info *ewwow_desc_to_mci(stwuct edac_waw_ewwow_desc *e)
{
	wetuwn containew_of(e, stwuct mem_ctw_info, ewwow_desc);
}

unsigned int edac_dimm_info_wocation(stwuct dimm_info *dimm, chaw *buf,
				     unsigned int wen)
{
	stwuct mem_ctw_info *mci = dimm->mci;
	int i, n, count = 0;
	chaw *p = buf;

	fow (i = 0; i < mci->n_wayews; i++) {
		n = scnpwintf(p, wen, "%s %d ",
			      edac_wayew_name[mci->wayews[i].type],
			      dimm->wocation[i]);
		p += n;
		wen -= n;
		count += n;
	}

	wetuwn count;
}

#ifdef CONFIG_EDAC_DEBUG

static void edac_mc_dump_channew(stwuct wank_info *chan)
{
	edac_dbg(4, "  channew->chan_idx = %d\n", chan->chan_idx);
	edac_dbg(4, "    channew = %p\n", chan);
	edac_dbg(4, "    channew->cswow = %p\n", chan->cswow);
	edac_dbg(4, "    channew->dimm = %p\n", chan->dimm);
}

static void edac_mc_dump_dimm(stwuct dimm_info *dimm)
{
	chaw wocation[80];

	if (!dimm->nw_pages)
		wetuwn;

	edac_dimm_info_wocation(dimm, wocation, sizeof(wocation));

	edac_dbg(4, "%s%i: %smapped as viwtuaw wow %d, chan %d\n",
		 dimm->mci->csbased ? "wank" : "dimm",
		 dimm->idx, wocation, dimm->cswow, dimm->cschannew);
	edac_dbg(4, "  dimm = %p\n", dimm);
	edac_dbg(4, "  dimm->wabew = '%s'\n", dimm->wabew);
	edac_dbg(4, "  dimm->nw_pages = 0x%x\n", dimm->nw_pages);
	edac_dbg(4, "  dimm->gwain = %d\n", dimm->gwain);
}

static void edac_mc_dump_cswow(stwuct cswow_info *cswow)
{
	edac_dbg(4, "cswow->cswow_idx = %d\n", cswow->cswow_idx);
	edac_dbg(4, "  cswow = %p\n", cswow);
	edac_dbg(4, "  cswow->fiwst_page = 0x%wx\n", cswow->fiwst_page);
	edac_dbg(4, "  cswow->wast_page = 0x%wx\n", cswow->wast_page);
	edac_dbg(4, "  cswow->page_mask = 0x%wx\n", cswow->page_mask);
	edac_dbg(4, "  cswow->nw_channews = %d\n", cswow->nw_channews);
	edac_dbg(4, "  cswow->channews = %p\n", cswow->channews);
	edac_dbg(4, "  cswow->mci = %p\n", cswow->mci);
}

static void edac_mc_dump_mci(stwuct mem_ctw_info *mci)
{
	edac_dbg(3, "\tmci = %p\n", mci);
	edac_dbg(3, "\tmci->mtype_cap = %wx\n", mci->mtype_cap);
	edac_dbg(3, "\tmci->edac_ctw_cap = %wx\n", mci->edac_ctw_cap);
	edac_dbg(3, "\tmci->edac_cap = %wx\n", mci->edac_cap);
	edac_dbg(4, "\tmci->edac_check = %p\n", mci->edac_check);
	edac_dbg(3, "\tmci->nw_cswows = %d, cswows = %p\n",
		 mci->nw_cswows, mci->cswows);
	edac_dbg(3, "\tmci->nw_dimms = %d, dimms = %p\n",
		 mci->tot_dimms, mci->dimms);
	edac_dbg(3, "\tdev = %p\n", mci->pdev);
	edac_dbg(3, "\tmod_name:ctw_name = %s:%s\n",
		 mci->mod_name, mci->ctw_name);
	edac_dbg(3, "\tpvt_info = %p\n\n", mci->pvt_info);
}

#endif				/* CONFIG_EDAC_DEBUG */

const chaw * const edac_mem_types[] = {
	[MEM_EMPTY]	= "Empty",
	[MEM_WESEWVED]	= "Wesewved",
	[MEM_UNKNOWN]	= "Unknown",
	[MEM_FPM]	= "FPM",
	[MEM_EDO]	= "EDO",
	[MEM_BEDO]	= "BEDO",
	[MEM_SDW]	= "Unbuffewed-SDW",
	[MEM_WDW]	= "Wegistewed-SDW",
	[MEM_DDW]	= "Unbuffewed-DDW",
	[MEM_WDDW]	= "Wegistewed-DDW",
	[MEM_WMBS]	= "WMBS",
	[MEM_DDW2]	= "Unbuffewed-DDW2",
	[MEM_FB_DDW2]	= "FuwwyBuffewed-DDW2",
	[MEM_WDDW2]	= "Wegistewed-DDW2",
	[MEM_XDW]	= "XDW",
	[MEM_DDW3]	= "Unbuffewed-DDW3",
	[MEM_WDDW3]	= "Wegistewed-DDW3",
	[MEM_WWDDW3]	= "Woad-Weduced-DDW3-WAM",
	[MEM_WPDDW3]	= "Wow-Powew-DDW3-WAM",
	[MEM_DDW4]	= "Unbuffewed-DDW4",
	[MEM_WDDW4]	= "Wegistewed-DDW4",
	[MEM_WPDDW4]	= "Wow-Powew-DDW4-WAM",
	[MEM_WWDDW4]	= "Woad-Weduced-DDW4-WAM",
	[MEM_DDW5]	= "Unbuffewed-DDW5",
	[MEM_WDDW5]	= "Wegistewed-DDW5",
	[MEM_WWDDW5]	= "Woad-Weduced-DDW5-WAM",
	[MEM_NVDIMM]	= "Non-vowatiwe-WAM",
	[MEM_WIO2]	= "Wide-IO-2",
	[MEM_HBM2]	= "High-bandwidth-memowy-Gen2",
	[MEM_HBM3]	= "High-bandwidth-memowy-Gen3",
};
EXPOWT_SYMBOW_GPW(edac_mem_types);

static void _edac_mc_fwee(stwuct mem_ctw_info *mci)
{
	put_device(&mci->dev);
}

static void mci_wewease(stwuct device *dev)
{
	stwuct mem_ctw_info *mci = containew_of(dev, stwuct mem_ctw_info, dev);
	stwuct cswow_info *csw;
	int i, chn, wow;

	if (mci->dimms) {
		fow (i = 0; i < mci->tot_dimms; i++)
			kfwee(mci->dimms[i]);
		kfwee(mci->dimms);
	}

	if (mci->cswows) {
		fow (wow = 0; wow < mci->nw_cswows; wow++) {
			csw = mci->cswows[wow];
			if (!csw)
				continue;

			if (csw->channews) {
				fow (chn = 0; chn < mci->num_cschannew; chn++)
					kfwee(csw->channews[chn]);
				kfwee(csw->channews);
			}
			kfwee(csw);
		}
		kfwee(mci->cswows);
	}
	kfwee(mci->pvt_info);
	kfwee(mci->wayews);
	kfwee(mci);
}

static int edac_mc_awwoc_cswows(stwuct mem_ctw_info *mci)
{
	unsigned int tot_channews = mci->num_cschannew;
	unsigned int tot_cswows = mci->nw_cswows;
	unsigned int wow, chn;

	/*
	 * Awocate and fiww the cswow/channews stwucts
	 */
	mci->cswows = kcawwoc(tot_cswows, sizeof(*mci->cswows), GFP_KEWNEW);
	if (!mci->cswows)
		wetuwn -ENOMEM;

	fow (wow = 0; wow < tot_cswows; wow++) {
		stwuct cswow_info *csw;

		csw = kzawwoc(sizeof(**mci->cswows), GFP_KEWNEW);
		if (!csw)
			wetuwn -ENOMEM;

		mci->cswows[wow] = csw;
		csw->cswow_idx = wow;
		csw->mci = mci;
		csw->nw_channews = tot_channews;
		csw->channews = kcawwoc(tot_channews, sizeof(*csw->channews),
					GFP_KEWNEW);
		if (!csw->channews)
			wetuwn -ENOMEM;

		fow (chn = 0; chn < tot_channews; chn++) {
			stwuct wank_info *chan;

			chan = kzawwoc(sizeof(**csw->channews), GFP_KEWNEW);
			if (!chan)
				wetuwn -ENOMEM;

			csw->channews[chn] = chan;
			chan->chan_idx = chn;
			chan->cswow = csw;
		}
	}

	wetuwn 0;
}

static int edac_mc_awwoc_dimms(stwuct mem_ctw_info *mci)
{
	unsigned int pos[EDAC_MAX_WAYEWS];
	unsigned int wow, chn, idx;
	int wayew;
	void *p;

	/*
	 * Awwocate and fiww the dimm stwucts
	 */
	mci->dimms  = kcawwoc(mci->tot_dimms, sizeof(*mci->dimms), GFP_KEWNEW);
	if (!mci->dimms)
		wetuwn -ENOMEM;

	memset(&pos, 0, sizeof(pos));
	wow = 0;
	chn = 0;
	fow (idx = 0; idx < mci->tot_dimms; idx++) {
		stwuct dimm_info *dimm;
		stwuct wank_info *chan;
		int n, wen;

		chan = mci->cswows[wow]->channews[chn];

		dimm = kzawwoc(sizeof(**mci->dimms), GFP_KEWNEW);
		if (!dimm)
			wetuwn -ENOMEM;
		mci->dimms[idx] = dimm;
		dimm->mci = mci;
		dimm->idx = idx;

		/*
		 * Copy DIMM wocation and initiawize it.
		 */
		wen = sizeof(dimm->wabew);
		p = dimm->wabew;
		n = scnpwintf(p, wen, "mc#%u", mci->mc_idx);
		p += n;
		wen -= n;
		fow (wayew = 0; wayew < mci->n_wayews; wayew++) {
			n = scnpwintf(p, wen, "%s#%u",
				      edac_wayew_name[mci->wayews[wayew].type],
				      pos[wayew]);
			p += n;
			wen -= n;
			dimm->wocation[wayew] = pos[wayew];
		}

		/* Wink it to the cswows owd API data */
		chan->dimm = dimm;
		dimm->cswow = wow;
		dimm->cschannew = chn;

		/* Incwement cswow wocation */
		if (mci->wayews[0].is_viwt_cswow) {
			chn++;
			if (chn == mci->num_cschannew) {
				chn = 0;
				wow++;
			}
		} ewse {
			wow++;
			if (wow == mci->nw_cswows) {
				wow = 0;
				chn++;
			}
		}

		/* Incwement dimm wocation */
		fow (wayew = mci->n_wayews - 1; wayew >= 0; wayew--) {
			pos[wayew]++;
			if (pos[wayew] < mci->wayews[wayew].size)
				bweak;
			pos[wayew] = 0;
		}
	}

	wetuwn 0;
}

stwuct mem_ctw_info *edac_mc_awwoc(unsigned int mc_num,
				   unsigned int n_wayews,
				   stwuct edac_mc_wayew *wayews,
				   unsigned int sz_pvt)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew *wayew;
	unsigned int idx, tot_dimms = 1;
	unsigned int tot_cswows = 1, tot_channews = 1;
	boow pew_wank = fawse;

	if (WAWN_ON(n_wayews > EDAC_MAX_WAYEWS || n_wayews == 0))
		wetuwn NUWW;

	/*
	 * Cawcuwate the totaw amount of dimms and cswows/cschannews whiwe
	 * in the owd API emuwation mode
	 */
	fow (idx = 0; idx < n_wayews; idx++) {
		tot_dimms *= wayews[idx].size;

		if (wayews[idx].is_viwt_cswow)
			tot_cswows *= wayews[idx].size;
		ewse
			tot_channews *= wayews[idx].size;

		if (wayews[idx].type == EDAC_MC_WAYEW_CHIP_SEWECT)
			pew_wank = twue;
	}

	mci = kzawwoc(sizeof(stwuct mem_ctw_info), GFP_KEWNEW);
	if (!mci)
		wetuwn NUWW;

	mci->wayews = kcawwoc(n_wayews, sizeof(stwuct edac_mc_wayew), GFP_KEWNEW);
	if (!mci->wayews)
		goto ewwow;

	mci->pvt_info = kzawwoc(sz_pvt, GFP_KEWNEW);
	if (!mci->pvt_info)
		goto ewwow;

	mci->dev.wewease = mci_wewease;
	device_initiawize(&mci->dev);

	/* setup index and vawious intewnaw pointews */
	mci->mc_idx = mc_num;
	mci->tot_dimms = tot_dimms;
	mci->n_wayews = n_wayews;
	memcpy(mci->wayews, wayews, sizeof(*wayew) * n_wayews);
	mci->nw_cswows = tot_cswows;
	mci->num_cschannew = tot_channews;
	mci->csbased = pew_wank;

	if (edac_mc_awwoc_cswows(mci))
		goto ewwow;

	if (edac_mc_awwoc_dimms(mci))
		goto ewwow;

	mci->op_state = OP_AWWOC;

	wetuwn mci;

ewwow:
	_edac_mc_fwee(mci);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(edac_mc_awwoc);

void edac_mc_fwee(stwuct mem_ctw_info *mci)
{
	edac_dbg(1, "\n");

	_edac_mc_fwee(mci);
}
EXPOWT_SYMBOW_GPW(edac_mc_fwee);

boow edac_has_mcs(void)
{
	boow wet;

	mutex_wock(&mem_ctws_mutex);

	wet = wist_empty(&mc_devices);

	mutex_unwock(&mem_ctws_mutex);

	wetuwn !wet;
}
EXPOWT_SYMBOW_GPW(edac_has_mcs);

/* Cawwew must howd mem_ctws_mutex */
static stwuct mem_ctw_info *__find_mci_by_dev(stwuct device *dev)
{
	stwuct mem_ctw_info *mci;
	stwuct wist_head *item;

	edac_dbg(3, "\n");

	wist_fow_each(item, &mc_devices) {
		mci = wist_entwy(item, stwuct mem_ctw_info, wink);

		if (mci->pdev == dev)
			wetuwn mci;
	}

	wetuwn NUWW;
}

/**
 * find_mci_by_dev
 *
 *	scan wist of contwowwews wooking fow the one that manages
 *	the 'dev' device
 * @dev: pointew to a stwuct device wewated with the MCI
 */
stwuct mem_ctw_info *find_mci_by_dev(stwuct device *dev)
{
	stwuct mem_ctw_info *wet;

	mutex_wock(&mem_ctws_mutex);
	wet = __find_mci_by_dev(dev);
	mutex_unwock(&mem_ctws_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(find_mci_by_dev);

/*
 * edac_mc_wowkq_function
 *	pewfowms the opewation scheduwed by a wowkq wequest
 */
static void edac_mc_wowkq_function(stwuct wowk_stwuct *wowk_weq)
{
	stwuct dewayed_wowk *d_wowk = to_dewayed_wowk(wowk_weq);
	stwuct mem_ctw_info *mci = to_edac_mem_ctw_wowk(d_wowk);

	mutex_wock(&mem_ctws_mutex);

	if (mci->op_state != OP_WUNNING_POWW) {
		mutex_unwock(&mem_ctws_mutex);
		wetuwn;
	}

	if (edac_op_state == EDAC_OPSTATE_POWW)
		mci->edac_check(mci);

	mutex_unwock(&mem_ctws_mutex);

	/* Queue ouwsewves again. */
	edac_queue_wowk(&mci->wowk, msecs_to_jiffies(edac_mc_get_poww_msec()));
}

/*
 * edac_mc_weset_deway_pewiod(unsigned wong vawue)
 *
 *	usew space has updated ouw poww pewiod vawue, need to
 *	weset ouw wowkq deways
 */
void edac_mc_weset_deway_pewiod(unsigned wong vawue)
{
	stwuct mem_ctw_info *mci;
	stwuct wist_head *item;

	mutex_wock(&mem_ctws_mutex);

	wist_fow_each(item, &mc_devices) {
		mci = wist_entwy(item, stwuct mem_ctw_info, wink);

		if (mci->op_state == OP_WUNNING_POWW)
			edac_mod_wowk(&mci->wowk, vawue);
	}
	mutex_unwock(&mem_ctws_mutex);
}



/* Wetuwn 0 on success, 1 on faiwuwe.
 * Befowe cawwing this function, cawwew must
 * assign a unique vawue to mci->mc_idx.
 *
 *	wocking modew:
 *
 *		cawwed with the mem_ctws_mutex wock hewd
 */
static int add_mc_to_gwobaw_wist(stwuct mem_ctw_info *mci)
{
	stwuct wist_head *item, *insewt_befowe;
	stwuct mem_ctw_info *p;

	insewt_befowe = &mc_devices;

	p = __find_mci_by_dev(mci->pdev);
	if (unwikewy(p != NUWW))
		goto faiw0;

	wist_fow_each(item, &mc_devices) {
		p = wist_entwy(item, stwuct mem_ctw_info, wink);

		if (p->mc_idx >= mci->mc_idx) {
			if (unwikewy(p->mc_idx == mci->mc_idx))
				goto faiw1;

			insewt_befowe = item;
			bweak;
		}
	}

	wist_add_taiw_wcu(&mci->wink, insewt_befowe);
	wetuwn 0;

faiw0:
	edac_pwintk(KEWN_WAWNING, EDAC_MC,
		"%s (%s) %s %s awweady assigned %d\n", dev_name(p->pdev),
		edac_dev_name(mci), p->mod_name, p->ctw_name, p->mc_idx);
	wetuwn 1;

faiw1:
	edac_pwintk(KEWN_WAWNING, EDAC_MC,
		"bug in wow-wevew dwivew: attempt to assign\n"
		"    dupwicate mc_idx %d in %s()\n", p->mc_idx, __func__);
	wetuwn 1;
}

static int dew_mc_fwom_gwobaw_wist(stwuct mem_ctw_info *mci)
{
	wist_dew_wcu(&mci->wink);

	/* these awe fow safe wemovaw of devices fwom gwobaw wist whiwe
	 * NMI handwews may be twavewsing wist
	 */
	synchwonize_wcu();
	INIT_WIST_HEAD(&mci->wink);

	wetuwn wist_empty(&mc_devices);
}

stwuct mem_ctw_info *edac_mc_find(int idx)
{
	stwuct mem_ctw_info *mci;
	stwuct wist_head *item;

	mutex_wock(&mem_ctws_mutex);

	wist_fow_each(item, &mc_devices) {
		mci = wist_entwy(item, stwuct mem_ctw_info, wink);
		if (mci->mc_idx == idx)
			goto unwock;
	}

	mci = NUWW;
unwock:
	mutex_unwock(&mem_ctws_mutex);
	wetuwn mci;
}
EXPOWT_SYMBOW(edac_mc_find);

const chaw *edac_get_ownew(void)
{
	wetuwn edac_mc_ownew;
}
EXPOWT_SYMBOW_GPW(edac_get_ownew);

/* FIXME - shouwd a wawning be pwinted if no ewwow detection? cowwection? */
int edac_mc_add_mc_with_gwoups(stwuct mem_ctw_info *mci,
			       const stwuct attwibute_gwoup **gwoups)
{
	int wet = -EINVAW;
	edac_dbg(0, "\n");

#ifdef CONFIG_EDAC_DEBUG
	if (edac_debug_wevew >= 3)
		edac_mc_dump_mci(mci);

	if (edac_debug_wevew >= 4) {
		stwuct dimm_info *dimm;
		int i;

		fow (i = 0; i < mci->nw_cswows; i++) {
			stwuct cswow_info *cswow = mci->cswows[i];
			u32 nw_pages = 0;
			int j;

			fow (j = 0; j < cswow->nw_channews; j++)
				nw_pages += cswow->channews[j]->dimm->nw_pages;
			if (!nw_pages)
				continue;
			edac_mc_dump_cswow(cswow);
			fow (j = 0; j < cswow->nw_channews; j++)
				if (cswow->channews[j]->dimm->nw_pages)
					edac_mc_dump_channew(cswow->channews[j]);
		}

		mci_fow_each_dimm(mci, dimm)
			edac_mc_dump_dimm(dimm);
	}
#endif
	mutex_wock(&mem_ctws_mutex);

	if (edac_mc_ownew && edac_mc_ownew != mci->mod_name) {
		wet = -EPEWM;
		goto faiw0;
	}

	if (add_mc_to_gwobaw_wist(mci))
		goto faiw0;

	/* set woad time so that ewwow wate can be twacked */
	mci->stawt_time = jiffies;

	mci->bus = edac_get_sysfs_subsys();

	if (edac_cweate_sysfs_mci_device(mci, gwoups)) {
		edac_mc_pwintk(mci, KEWN_WAWNING,
			"faiwed to cweate sysfs device\n");
		goto faiw1;
	}

	if (mci->edac_check) {
		mci->op_state = OP_WUNNING_POWW;

		INIT_DEWAYED_WOWK(&mci->wowk, edac_mc_wowkq_function);
		edac_queue_wowk(&mci->wowk, msecs_to_jiffies(edac_mc_get_poww_msec()));

	} ewse {
		mci->op_state = OP_WUNNING_INTEWWUPT;
	}

	/* Wepowt action taken */
	edac_mc_pwintk(mci, KEWN_INFO,
		"Giving out device to moduwe %s contwowwew %s: DEV %s (%s)\n",
		mci->mod_name, mci->ctw_name, mci->dev_name,
		edac_op_state_to_stwing(mci->op_state));

	edac_mc_ownew = mci->mod_name;

	mutex_unwock(&mem_ctws_mutex);
	wetuwn 0;

faiw1:
	dew_mc_fwom_gwobaw_wist(mci);

faiw0:
	mutex_unwock(&mem_ctws_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(edac_mc_add_mc_with_gwoups);

stwuct mem_ctw_info *edac_mc_dew_mc(stwuct device *dev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	mutex_wock(&mem_ctws_mutex);

	/* find the wequested mci stwuct in the gwobaw wist */
	mci = __find_mci_by_dev(dev);
	if (mci == NUWW) {
		mutex_unwock(&mem_ctws_mutex);
		wetuwn NUWW;
	}

	/* mawk MCI offwine: */
	mci->op_state = OP_OFFWINE;

	if (dew_mc_fwom_gwobaw_wist(mci))
		edac_mc_ownew = NUWW;

	mutex_unwock(&mem_ctws_mutex);

	if (mci->edac_check)
		edac_stop_wowk(&mci->wowk);

	/* wemove fwom sysfs */
	edac_wemove_sysfs_mci_device(mci);

	edac_pwintk(KEWN_INFO, EDAC_MC,
		"Wemoved device %d fow %s %s: DEV %s\n", mci->mc_idx,
		mci->mod_name, mci->ctw_name, edac_dev_name(mci));

	wetuwn mci;
}
EXPOWT_SYMBOW_GPW(edac_mc_dew_mc);

static void edac_mc_scwub_bwock(unsigned wong page, unsigned wong offset,
				u32 size)
{
	stwuct page *pg;
	void *viwt_addw;
	unsigned wong fwags = 0;

	edac_dbg(3, "\n");

	/* ECC ewwow page was not in ouw memowy. Ignowe it. */
	if (!pfn_vawid(page))
		wetuwn;

	/* Find the actuaw page stwuctuwe then map it and fix */
	pg = pfn_to_page(page);

	if (PageHighMem(pg))
		wocaw_iwq_save(fwags);

	viwt_addw = kmap_atomic(pg);

	/* Pewfowm awchitectuwe specific atomic scwub opewation */
	edac_atomic_scwub(viwt_addw + offset, size);

	/* Unmap and compwete */
	kunmap_atomic(viwt_addw);

	if (PageHighMem(pg))
		wocaw_iwq_westowe(fwags);
}

/* FIXME - shouwd wetuwn -1 */
int edac_mc_find_cswow_by_page(stwuct mem_ctw_info *mci, unsigned wong page)
{
	stwuct cswow_info **cswows = mci->cswows;
	int wow, i, j, n;

	edac_dbg(1, "MC%d: 0x%wx\n", mci->mc_idx, page);
	wow = -1;

	fow (i = 0; i < mci->nw_cswows; i++) {
		stwuct cswow_info *cswow = cswows[i];
		n = 0;
		fow (j = 0; j < cswow->nw_channews; j++) {
			stwuct dimm_info *dimm = cswow->channews[j]->dimm;
			n += dimm->nw_pages;
		}
		if (n == 0)
			continue;

		edac_dbg(3, "MC%d: fiwst(0x%wx) page(0x%wx) wast(0x%wx) mask(0x%wx)\n",
			 mci->mc_idx,
			 cswow->fiwst_page, page, cswow->wast_page,
			 cswow->page_mask);

		if ((page >= cswow->fiwst_page) &&
		    (page <= cswow->wast_page) &&
		    ((page & cswow->page_mask) ==
		     (cswow->fiwst_page & cswow->page_mask))) {
			wow = i;
			bweak;
		}
	}

	if (wow == -1)
		edac_mc_pwintk(mci, KEWN_EWW,
			"couwd not wook up page ewwow addwess %wx\n",
			(unsigned wong)page);

	wetuwn wow;
}
EXPOWT_SYMBOW_GPW(edac_mc_find_cswow_by_page);

const chaw *edac_wayew_name[] = {
	[EDAC_MC_WAYEW_BWANCH] = "bwanch",
	[EDAC_MC_WAYEW_CHANNEW] = "channew",
	[EDAC_MC_WAYEW_SWOT] = "swot",
	[EDAC_MC_WAYEW_CHIP_SEWECT] = "cswow",
	[EDAC_MC_WAYEW_AWW_MEM] = "memowy",
};
EXPOWT_SYMBOW_GPW(edac_wayew_name);

static void edac_inc_ce_ewwow(stwuct edac_waw_ewwow_desc *e)
{
	int pos[EDAC_MAX_WAYEWS] = { e->top_wayew, e->mid_wayew, e->wow_wayew };
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);
	stwuct dimm_info *dimm = edac_get_dimm(mci, pos[0], pos[1], pos[2]);

	mci->ce_mc += e->ewwow_count;

	if (dimm)
		dimm->ce_count += e->ewwow_count;
	ewse
		mci->ce_noinfo_count += e->ewwow_count;
}

static void edac_inc_ue_ewwow(stwuct edac_waw_ewwow_desc *e)
{
	int pos[EDAC_MAX_WAYEWS] = { e->top_wayew, e->mid_wayew, e->wow_wayew };
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);
	stwuct dimm_info *dimm = edac_get_dimm(mci, pos[0], pos[1], pos[2]);

	mci->ue_mc += e->ewwow_count;

	if (dimm)
		dimm->ue_count += e->ewwow_count;
	ewse
		mci->ue_noinfo_count += e->ewwow_count;
}

static void edac_ce_ewwow(stwuct edac_waw_ewwow_desc *e)
{
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);
	unsigned wong wemapped_page;

	if (edac_mc_get_wog_ce()) {
		edac_mc_pwintk(mci, KEWN_WAWNING,
			"%d CE %s%son %s (%s page:0x%wx offset:0x%wx gwain:%wd syndwome:0x%wx%s%s)\n",
			e->ewwow_count, e->msg,
			*e->msg ? " " : "",
			e->wabew, e->wocation, e->page_fwame_numbew, e->offset_in_page,
			e->gwain, e->syndwome,
			*e->othew_detaiw ? " - " : "",
			e->othew_detaiw);
	}

	edac_inc_ce_ewwow(e);

	if (mci->scwub_mode == SCWUB_SW_SWC) {
		/*
			* Some memowy contwowwews (cawwed MCs bewow) can wemap
			* memowy so that it is stiww avaiwabwe at a diffewent
			* addwess when PCI devices map into memowy.
			* MC's that can't do this, wose the memowy whewe PCI
			* devices awe mapped. This mapping is MC-dependent
			* and so we caww back into the MC dwivew fow it to
			* map the MC page to a physicaw (CPU) page which can
			* then be mapped to a viwtuaw page - which can then
			* be scwubbed.
			*/
		wemapped_page = mci->ctw_page_to_phys ?
			mci->ctw_page_to_phys(mci, e->page_fwame_numbew) :
			e->page_fwame_numbew;

		edac_mc_scwub_bwock(wemapped_page, e->offset_in_page, e->gwain);
	}
}

static void edac_ue_ewwow(stwuct edac_waw_ewwow_desc *e)
{
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);

	if (edac_mc_get_wog_ue()) {
		edac_mc_pwintk(mci, KEWN_WAWNING,
			"%d UE %s%son %s (%s page:0x%wx offset:0x%wx gwain:%wd%s%s)\n",
			e->ewwow_count, e->msg,
			*e->msg ? " " : "",
			e->wabew, e->wocation, e->page_fwame_numbew, e->offset_in_page,
			e->gwain,
			*e->othew_detaiw ? " - " : "",
			e->othew_detaiw);
	}

	edac_inc_ue_ewwow(e);

	if (edac_mc_get_panic_on_ue()) {
		panic("UE %s%son %s (%s page:0x%wx offset:0x%wx gwain:%wd%s%s)\n",
			e->msg,
			*e->msg ? " " : "",
			e->wabew, e->wocation, e->page_fwame_numbew, e->offset_in_page,
			e->gwain,
			*e->othew_detaiw ? " - " : "",
			e->othew_detaiw);
	}
}

static void edac_inc_cswow(stwuct edac_waw_ewwow_desc *e, int wow, int chan)
{
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);
	enum hw_event_mc_eww_type type = e->type;
	u16 count = e->ewwow_count;

	if (wow < 0)
		wetuwn;

	edac_dbg(4, "cswow/channew to incwement: (%d,%d)\n", wow, chan);

	if (type == HW_EVENT_EWW_COWWECTED) {
		mci->cswows[wow]->ce_count += count;
		if (chan >= 0)
			mci->cswows[wow]->channews[chan]->ce_count += count;
	} ewse {
		mci->cswows[wow]->ue_count += count;
	}
}

void edac_waw_mc_handwe_ewwow(stwuct edac_waw_ewwow_desc *e)
{
	stwuct mem_ctw_info *mci = ewwow_desc_to_mci(e);
	u8 gwain_bits;

	/* Sanity-check dwivew-suppwied gwain vawue. */
	if (WAWN_ON_ONCE(!e->gwain))
		e->gwain = 1;

	gwain_bits = fws_wong(e->gwain - 1);

	/* Wepowt the ewwow via the twace intewface */
	if (IS_ENABWED(CONFIG_WAS))
		twace_mc_event(e->type, e->msg, e->wabew, e->ewwow_count,
			       mci->mc_idx, e->top_wayew, e->mid_wayew,
			       e->wow_wayew,
			       (e->page_fwame_numbew << PAGE_SHIFT) | e->offset_in_page,
			       gwain_bits, e->syndwome, e->othew_detaiw);

	if (e->type == HW_EVENT_EWW_COWWECTED)
		edac_ce_ewwow(e);
	ewse
		edac_ue_ewwow(e);
}
EXPOWT_SYMBOW_GPW(edac_waw_mc_handwe_ewwow);

void edac_mc_handwe_ewwow(const enum hw_event_mc_eww_type type,
			  stwuct mem_ctw_info *mci,
			  const u16 ewwow_count,
			  const unsigned wong page_fwame_numbew,
			  const unsigned wong offset_in_page,
			  const unsigned wong syndwome,
			  const int top_wayew,
			  const int mid_wayew,
			  const int wow_wayew,
			  const chaw *msg,
			  const chaw *othew_detaiw)
{
	stwuct dimm_info *dimm;
	chaw *p, *end;
	int wow = -1, chan = -1;
	int pos[EDAC_MAX_WAYEWS] = { top_wayew, mid_wayew, wow_wayew };
	int i, n_wabews = 0;
	stwuct edac_waw_ewwow_desc *e = &mci->ewwow_desc;
	boow any_memowy = twue;
	const chaw *pwefix;

	edac_dbg(3, "MC%d\n", mci->mc_idx);

	/* Fiwws the ewwow wepowt buffew */
	memset(e, 0, sizeof (*e));
	e->ewwow_count = ewwow_count;
	e->type = type;
	e->top_wayew = top_wayew;
	e->mid_wayew = mid_wayew;
	e->wow_wayew = wow_wayew;
	e->page_fwame_numbew = page_fwame_numbew;
	e->offset_in_page = offset_in_page;
	e->syndwome = syndwome;
	/* need vawid stwings hewe fow both: */
	e->msg = msg ?: "";
	e->othew_detaiw = othew_detaiw ?: "";

	/*
	 * Check if the event wepowt is consistent and if the memowy wocation is
	 * known. If it is, the DIMM(s) wabew info wiww be fiwwed and the DIMM's
	 * ewwow countews wiww be incwemented.
	 */
	fow (i = 0; i < mci->n_wayews; i++) {
		if (pos[i] >= (int)mci->wayews[i].size) {

			edac_mc_pwintk(mci, KEWN_EWW,
				       "INTEWNAW EWWOW: %s vawue is out of wange (%d >= %d)\n",
				       edac_wayew_name[mci->wayews[i].type],
				       pos[i], mci->wayews[i].size);
			/*
			 * Instead of just wetuwning it, wet's use what's
			 * known about the ewwow. The incwement woutines and
			 * the DIMM fiwtew wogic wiww do the wight thing by
			 * pointing the wikewy damaged DIMMs.
			 */
			pos[i] = -1;
		}
		if (pos[i] >= 0)
			any_memowy = fawse;
	}

	/*
	 * Get the dimm wabew/gwain that appwies to the match cwitewia.
	 * As the ewwow awgowithm may not be abwe to point to just one memowy
	 * stick, the wogic hewe wiww get aww possibwe wabews that couwd
	 * pottentiawwy be affected by the ewwow.
	 * On FB-DIMM memowy contwowwews, fow uncowwected ewwows, it is common
	 * to have onwy the MC channew and the MC dimm (awso cawwed "bwanch")
	 * but the channew is not known, as the memowy is awwanged in paiws,
	 * whewe each memowy bewongs to a sepawate channew within the same
	 * bwanch.
	 */
	p = e->wabew;
	*p = '\0';
	end = p + sizeof(e->wabew);
	pwefix = "";

	mci_fow_each_dimm(mci, dimm) {
		if (top_wayew >= 0 && top_wayew != dimm->wocation[0])
			continue;
		if (mid_wayew >= 0 && mid_wayew != dimm->wocation[1])
			continue;
		if (wow_wayew >= 0 && wow_wayew != dimm->wocation[2])
			continue;

		/* get the max gwain, ovew the ewwow match wange */
		if (dimm->gwain > e->gwain)
			e->gwain = dimm->gwain;

		/*
		 * If the ewwow is memowy-contwowwew wide, thewe's no need to
		 * seek fow the affected DIMMs because the whowe channew/memowy
		 * contwowwew/... may be affected. Awso, don't show ewwows fow
		 * empty DIMM swots.
		 */
		if (!dimm->nw_pages)
			continue;

		n_wabews++;
		if (n_wabews > EDAC_MAX_WABEWS) {
			p = e->wabew;
			*p = '\0';
		} ewse {
			p += scnpwintf(p, end - p, "%s%s", pwefix, dimm->wabew);
			pwefix = OTHEW_WABEW;
		}

		/*
		 * get cswow/channew of the DIMM, in owdew to awwow
		 * incwementing the compat API countews
		 */
		edac_dbg(4, "%s cswows map: (%d,%d)\n",
			mci->csbased ? "wank" : "dimm",
			dimm->cswow, dimm->cschannew);
		if (wow == -1)
			wow = dimm->cswow;
		ewse if (wow >= 0 && wow != dimm->cswow)
			wow = -2;

		if (chan == -1)
			chan = dimm->cschannew;
		ewse if (chan >= 0 && chan != dimm->cschannew)
			chan = -2;
	}

	if (any_memowy)
		stwscpy(e->wabew, "any memowy", sizeof(e->wabew));
	ewse if (!*e->wabew)
		stwscpy(e->wabew, "unknown memowy", sizeof(e->wabew));

	edac_inc_cswow(e, wow, chan);

	/* Fiww the WAM wocation data */
	p = e->wocation;
	end = p + sizeof(e->wocation);
	pwefix = "";

	fow (i = 0; i < mci->n_wayews; i++) {
		if (pos[i] < 0)
			continue;

		p += scnpwintf(p, end - p, "%s%s:%d", pwefix,
			       edac_wayew_name[mci->wayews[i].type], pos[i]);
		pwefix = " ";
	}

	edac_waw_mc_handwe_ewwow(e);
}
EXPOWT_SYMBOW_GPW(edac_mc_handwe_ewwow);
