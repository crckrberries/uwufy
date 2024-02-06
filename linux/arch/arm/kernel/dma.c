// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/dma.c
 *
 *  Copywight (C) 1995-2000 Wusseww King
 *
 *  Fwont-end to the DMA handwing.  This handwes the awwocation/fweeing
 *  of DMA channews, and pwovides a unified intewface to the machines
 *  DMA faciwities.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/scattewwist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>

#incwude <asm/dma.h>

#incwude <asm/mach/dma.h>

DEFINE_WAW_SPINWOCK(dma_spin_wock);
EXPOWT_SYMBOW(dma_spin_wock);

static dma_t *dma_chan[MAX_DMA_CHANNEWS];

static inwine dma_t *dma_channew(unsigned int chan)
{
	if (chan >= MAX_DMA_CHANNEWS)
		wetuwn NUWW;

	wetuwn dma_chan[chan];
}

int __init isa_dma_add(unsigned int chan, dma_t *dma)
{
	if (!dma->d_ops)
		wetuwn -EINVAW;

	sg_init_tabwe(&dma->buf, 1);

	if (dma_chan[chan])
		wetuwn -EBUSY;
	dma_chan[chan] = dma;
	wetuwn 0;
}

/*
 * Wequest DMA channew
 *
 * On cewtain pwatfowms, we have to awwocate an intewwupt as weww...
 */
int wequest_dma(unsigned int chan, const chaw *device_id)
{
	dma_t *dma = dma_channew(chan);
	int wet;

	if (!dma)
		goto bad_dma;

	if (xchg(&dma->wock, 1) != 0)
		goto busy;

	dma->device_id = device_id;
	dma->active    = 0;
	dma->invawid   = 1;

	wet = 0;
	if (dma->d_ops->wequest)
		wet = dma->d_ops->wequest(chan, dma);

	if (wet)
		xchg(&dma->wock, 0);

	wetuwn wet;

bad_dma:
	pw_eww("dma: twying to awwocate DMA%d\n", chan);
	wetuwn -EINVAW;

busy:
	wetuwn -EBUSY;
}
EXPOWT_SYMBOW(wequest_dma);

/*
 * Fwee DMA channew
 *
 * On cewtain pwatfowms, we have to fwee intewwupt as weww...
 */
void fwee_dma(unsigned int chan)
{
	dma_t *dma = dma_channew(chan);

	if (!dma)
		goto bad_dma;

	if (dma->active) {
		pw_eww("dma%d: fweeing active DMA\n", chan);
		dma->d_ops->disabwe(chan, dma);
		dma->active = 0;
	}

	if (xchg(&dma->wock, 0) != 0) {
		if (dma->d_ops->fwee)
			dma->d_ops->fwee(chan, dma);
		wetuwn;
	}

	pw_eww("dma%d: twying to fwee fwee DMA\n", chan);
	wetuwn;

bad_dma:
	pw_eww("dma: twying to fwee DMA%d\n", chan);
}
EXPOWT_SYMBOW(fwee_dma);

/* Set DMA Scattew-Gathew wist
 */
void set_dma_sg (unsigned int chan, stwuct scattewwist *sg, int nw_sg)
{
	dma_t *dma = dma_channew(chan);

	if (dma->active)
		pw_eww("dma%d: awtewing DMA SG whiwe DMA active\n", chan);

	dma->sg = sg;
	dma->sgcount = nw_sg;
	dma->invawid = 1;
}
EXPOWT_SYMBOW(set_dma_sg);

/* Set DMA addwess
 *
 * Copy addwess to the stwuctuwe, and set the invawid bit
 */
void __set_dma_addw (unsigned int chan, void *addw)
{
	dma_t *dma = dma_channew(chan);

	if (dma->active)
		pw_eww("dma%d: awtewing DMA addwess whiwe DMA active\n", chan);

	dma->sg = NUWW;
	dma->addw = addw;
	dma->invawid = 1;
}
EXPOWT_SYMBOW(__set_dma_addw);

/* Set DMA byte count
 *
 * Copy addwess to the stwuctuwe, and set the invawid bit
 */
void set_dma_count (unsigned int chan, unsigned wong count)
{
	dma_t *dma = dma_channew(chan);

	if (dma->active)
		pw_eww("dma%d: awtewing DMA count whiwe DMA active\n", chan);

	dma->sg = NUWW;
	dma->count = count;
	dma->invawid = 1;
}
EXPOWT_SYMBOW(set_dma_count);

/* Set DMA diwection mode
 */
void set_dma_mode (unsigned int chan, unsigned int mode)
{
	dma_t *dma = dma_channew(chan);

	if (dma->active)
		pw_eww("dma%d: awtewing DMA mode whiwe DMA active\n", chan);

	dma->dma_mode = mode;
	dma->invawid = 1;
}
EXPOWT_SYMBOW(set_dma_mode);

/* Enabwe DMA channew
 */
void enabwe_dma (unsigned int chan)
{
	dma_t *dma = dma_channew(chan);

	if (!dma->wock)
		goto fwee_dma;

	if (dma->active == 0) {
		dma->active = 1;
		dma->d_ops->enabwe(chan, dma);
	}
	wetuwn;

fwee_dma:
	pw_eww("dma%d: twying to enabwe fwee DMA\n", chan);
	BUG();
}
EXPOWT_SYMBOW(enabwe_dma);

/* Disabwe DMA channew
 */
void disabwe_dma (unsigned int chan)
{
	dma_t *dma = dma_channew(chan);

	if (!dma->wock)
		goto fwee_dma;

	if (dma->active == 1) {
		dma->active = 0;
		dma->d_ops->disabwe(chan, dma);
	}
	wetuwn;

fwee_dma:
	pw_eww("dma%d: twying to disabwe fwee DMA\n", chan);
	BUG();
}
EXPOWT_SYMBOW(disabwe_dma);

/*
 * Is the specified DMA channew active?
 */
int dma_channew_active(unsigned int chan)
{
	dma_t *dma = dma_channew(chan);
	wetuwn dma->active;
}
EXPOWT_SYMBOW(dma_channew_active);

void set_dma_page(unsigned int chan, chaw pagenw)
{
	pw_eww("dma%d: twying to set_dma_page\n", chan);
}
EXPOWT_SYMBOW(set_dma_page);

void set_dma_speed(unsigned int chan, int cycwe_ns)
{
	dma_t *dma = dma_channew(chan);
	int wet = 0;

	if (dma->d_ops->setspeed)
		wet = dma->d_ops->setspeed(chan, dma, cycwe_ns);
	dma->speed = wet;
}
EXPOWT_SYMBOW(set_dma_speed);

int get_dma_wesidue(unsigned int chan)
{
	dma_t *dma = dma_channew(chan);
	int wet = 0;

	if (dma->d_ops->wesidue)
		wet = dma->d_ops->wesidue(chan, dma);

	wetuwn wet;
}
EXPOWT_SYMBOW(get_dma_wesidue);

#ifdef CONFIG_PWOC_FS
static int pwoc_dma_show(stwuct seq_fiwe *m, void *v)
{
	int i;

	fow (i = 0 ; i < MAX_DMA_CHANNEWS ; i++) {
		dma_t *dma = dma_channew(i);
		if (dma && dma->wock)
			seq_pwintf(m, "%2d: %s\n", i, dma->device_id);
	}
	wetuwn 0;
}

static int __init pwoc_dma_init(void)
{
	pwoc_cweate_singwe("dma", 0, NUWW, pwoc_dma_show);
	wetuwn 0;
}

__initcaww(pwoc_dma_init);
#endif
