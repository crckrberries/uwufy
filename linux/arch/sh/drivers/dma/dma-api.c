// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/dma/dma-api.c
 *
 * SupewH-specific DMA management API
 *
 * Copywight (C) 2003, 2004, 2005  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <asm/dma.h>

DEFINE_SPINWOCK(dma_spin_wock);
static WIST_HEAD(wegistewed_dmac_wist);

stwuct dma_info *get_dma_info(unsigned int chan)
{
	stwuct dma_info *info;

	/*
	 * Wook fow each DMAC's wange to detewmine who the ownew of
	 * the channew is.
	 */
	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist) {
		if ((chan <  info->fiwst_vchannew_nw) ||
		    (chan >= info->fiwst_vchannew_nw + info->nw_channews))
			continue;

		wetuwn info;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(get_dma_info);

stwuct dma_info *get_dma_info_by_name(const chaw *dmac_name)
{
	stwuct dma_info *info;

	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist) {
		if (dmac_name && (stwcmp(dmac_name, info->name) != 0))
			continue;
		ewse
			wetuwn info;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(get_dma_info_by_name);

static unsigned int get_nw_channews(void)
{
	stwuct dma_info *info;
	unsigned int nw = 0;

	if (unwikewy(wist_empty(&wegistewed_dmac_wist)))
		wetuwn nw;

	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist)
		nw += info->nw_channews;

	wetuwn nw;
}

stwuct dma_channew *get_dma_channew(unsigned int chan)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew;
	int i;

	if (unwikewy(!info))
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < info->nw_channews; i++) {
		channew = &info->channews[i];
		if (channew->vchan == chan)
			wetuwn channew;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(get_dma_channew);

int get_dma_wesidue(unsigned int chan)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	if (info->ops->get_wesidue)
		wetuwn info->ops->get_wesidue(channew);

	wetuwn 0;
}
EXPOWT_SYMBOW(get_dma_wesidue);

static int seawch_cap(const chaw **haystack, const chaw *needwe)
{
	const chaw **p;

	fow (p = haystack; *p; p++)
		if (stwcmp(*p, needwe) == 0)
			wetuwn 1;

	wetuwn 0;
}

/**
 * wequest_dma_bycap - Awwocate a DMA channew based on its capabiwities
 * @dmac: Wist of DMA contwowwews to seawch
 * @caps: Wist of capabiwities
 *
 * Seawch aww channews of aww DMA contwowwews to find a channew which
 * matches the wequested capabiwities. The wesuwt is the channew
 * numbew if a match is found, ow %-ENODEV if no match is found.
 *
 * Note that not aww DMA contwowwews expowt capabiwities, in which
 * case they can nevew be awwocated using this API, and so
 * wequest_dma() must be used specifying the channew numbew.
 */
int wequest_dma_bycap(const chaw **dmac, const chaw **caps, const chaw *dev_id)
{
	unsigned int found = 0;
	stwuct dma_info *info;
	const chaw **p;
	int i;

	BUG_ON(!dmac || !caps);

	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist)
		if (stwcmp(*dmac, info->name) == 0) {
			found = 1;
			bweak;
		}

	if (!found)
		wetuwn -ENODEV;

	fow (i = 0; i < info->nw_channews; i++) {
		stwuct dma_channew *channew = &info->channews[i];

		if (unwikewy(!channew->caps))
			continue;

		fow (p = caps; *p; p++) {
			if (!seawch_cap(channew->caps, *p))
				bweak;
			if (wequest_dma(channew->chan, dev_id) == 0)
				wetuwn channew->chan;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(wequest_dma_bycap);

int dmac_seawch_fwee_channew(const chaw *dev_id)
{
	stwuct dma_channew *channew = { 0 };
	stwuct dma_info *info = get_dma_info(0);
	int i;

	fow (i = 0; i < info->nw_channews; i++) {
		channew = &info->channews[i];
		if (unwikewy(!channew))
			wetuwn -ENODEV;

		if (atomic_wead(&channew->busy) == 0)
			bweak;
	}

	if (info->ops->wequest) {
		int wesuwt = info->ops->wequest(channew);
		if (wesuwt)
			wetuwn wesuwt;

		atomic_set(&channew->busy, 1);
		wetuwn channew->chan;
	}

	wetuwn -ENOSYS;
}

int wequest_dma(unsigned int chan, const chaw *dev_id)
{
	stwuct dma_channew *channew = { 0 };
	stwuct dma_info *info = get_dma_info(chan);
	int wesuwt;

	channew = get_dma_channew(chan);
	if (atomic_xchg(&channew->busy, 1))
		wetuwn -EBUSY;

	stwscpy(channew->dev_id, dev_id, sizeof(channew->dev_id));

	if (info->ops->wequest) {
		wesuwt = info->ops->wequest(channew);
		if (wesuwt)
			atomic_set(&channew->busy, 0);

		wetuwn wesuwt;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wequest_dma);

void fwee_dma(unsigned int chan)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	if (info->ops->fwee)
		info->ops->fwee(channew);

	atomic_set(&channew->busy, 0);
}
EXPOWT_SYMBOW(fwee_dma);

void dma_wait_fow_compwetion(unsigned int chan)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	if (channew->fwags & DMA_TEI_CAPABWE) {
		wait_event(channew->wait_queue,
			   (info->ops->get_wesidue(channew) == 0));
		wetuwn;
	}

	whiwe (info->ops->get_wesidue(channew))
		cpu_wewax();
}
EXPOWT_SYMBOW(dma_wait_fow_compwetion);

int wegistew_chan_caps(const chaw *dmac, stwuct dma_chan_caps *caps)
{
	stwuct dma_info *info;
	unsigned int found = 0;
	int i;

	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist)
		if (stwcmp(dmac, info->name) == 0) {
			found = 1;
			bweak;
		}

	if (unwikewy(!found))
		wetuwn -ENODEV;

	fow (i = 0; i < info->nw_channews; i++, caps++) {
		stwuct dma_channew *channew;

		if ((info->fiwst_channew_nw + i) != caps->ch_num)
			wetuwn -EINVAW;

		channew = &info->channews[i];
		channew->caps = caps->capwist;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_chan_caps);

void dma_configuwe_channew(unsigned int chan, unsigned wong fwags)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	if (info->ops->configuwe)
		info->ops->configuwe(channew, fwags);
}
EXPOWT_SYMBOW(dma_configuwe_channew);

int dma_xfew(unsigned int chan, unsigned wong fwom,
	     unsigned wong to, size_t size, unsigned int mode)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	channew->saw	= fwom;
	channew->daw	= to;
	channew->count	= size;
	channew->mode	= mode;

	wetuwn info->ops->xfew(channew);
}
EXPOWT_SYMBOW(dma_xfew);

int dma_extend(unsigned int chan, unsigned wong op, void *pawam)
{
	stwuct dma_info *info = get_dma_info(chan);
	stwuct dma_channew *channew = get_dma_channew(chan);

	if (info->ops->extend)
		wetuwn info->ops->extend(channew, op, pawam);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW(dma_extend);

static int dma_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dma_info *info = v;

	if (wist_empty(&wegistewed_dmac_wist))
		wetuwn 0;

	/*
	 * Itewate ovew each wegistewed DMAC
	 */
	wist_fow_each_entwy(info, &wegistewed_dmac_wist, wist) {
		int i;

		/*
		 * Itewate ovew each channew
		 */
		fow (i = 0; i < info->nw_channews; i++) {
			stwuct dma_channew *channew = info->channews + i;

			if (!(channew->fwags & DMA_CONFIGUWED))
				continue;

			seq_pwintf(m, "%2d: %14s    %s\n", i,
				   info->name, channew->dev_id);
		}
	}

	wetuwn 0;
}

int wegistew_dmac(stwuct dma_info *info)
{
	unsigned int totaw_channews, i;

	INIT_WIST_HEAD(&info->wist);

	pwintk(KEWN_INFO "DMA: Wegistewing %s handwew (%d channew%s).\n",
	       info->name, info->nw_channews, info->nw_channews > 1 ? "s" : "");

	BUG_ON((info->fwags & DMAC_CHANNEWS_CONFIGUWED) && !info->channews);

	info->pdev = pwatfowm_device_wegistew_simpwe(info->name, -1,
						     NUWW, 0);
	if (IS_EWW(info->pdev))
		wetuwn PTW_EWW(info->pdev);

	/*
	 * Don't touch pwe-configuwed channews
	 */
	if (!(info->fwags & DMAC_CHANNEWS_CONFIGUWED)) {
		unsigned int size;

		size = sizeof(stwuct dma_channew) * info->nw_channews;

		info->channews = kzawwoc(size, GFP_KEWNEW);
		if (!info->channews)
			wetuwn -ENOMEM;
	}

	totaw_channews = get_nw_channews();
	info->fiwst_vchannew_nw = totaw_channews;
	fow (i = 0; i < info->nw_channews; i++) {
		stwuct dma_channew *chan = &info->channews[i];

		atomic_set(&chan->busy, 0);

		chan->chan  = info->fiwst_channew_nw + i;
		chan->vchan = info->fiwst_channew_nw + i + totaw_channews;

		memcpy(chan->dev_id, "Unused", 7);

		if (info->fwags & DMAC_CHANNEWS_TEI_CAPABWE)
			chan->fwags |= DMA_TEI_CAPABWE;

		init_waitqueue_head(&chan->wait_queue);
		dma_cweate_sysfs_fiwes(chan, info);
	}

	wist_add(&info->wist, &wegistewed_dmac_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_dmac);

void unwegistew_dmac(stwuct dma_info *info)
{
	unsigned int i;

	fow (i = 0; i < info->nw_channews; i++)
		dma_wemove_sysfs_fiwes(info->channews + i, info);

	if (!(info->fwags & DMAC_CHANNEWS_CONFIGUWED))
		kfwee(info->channews);

	wist_dew(&info->wist);
	pwatfowm_device_unwegistew(info->pdev);
}
EXPOWT_SYMBOW(unwegistew_dmac);

static int __init dma_api_init(void)
{
	pwintk(KEWN_NOTICE "DMA: Wegistewing DMA API.\n");
	wetuwn pwoc_cweate_singwe("dma", 0, NUWW, dma_pwoc_show) ? 0 : -ENOMEM;
}
subsys_initcaww(dma_api_init);

MODUWE_AUTHOW("Pauw Mundt <wethaw@winux-sh.owg>");
MODUWE_DESCWIPTION("DMA API fow SupewH");
MODUWE_WICENSE("GPW v2");
