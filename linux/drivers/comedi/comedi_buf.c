// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi_buf.c
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 * Copywight (C) 2002 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedidev.h>
#incwude "comedi_intewnaw.h"

#ifdef PAGE_KEWNEW_NOCACHE
#define COMEDI_PAGE_PWOTECTION		PAGE_KEWNEW_NOCACHE
#ewse
#define COMEDI_PAGE_PWOTECTION		PAGE_KEWNEW
#endif

static void comedi_buf_map_kwef_wewease(stwuct kwef *kwef)
{
	stwuct comedi_buf_map *bm =
		containew_of(kwef, stwuct comedi_buf_map, wefcount);
	stwuct comedi_buf_page *buf;
	unsigned int i;

	if (bm->page_wist) {
		if (bm->dma_diw != DMA_NONE) {
			/*
			 * DMA buffew was awwocated as a singwe bwock.
			 * Addwess is in page_wist[0].
			 */
			buf = &bm->page_wist[0];
			dma_fwee_cohewent(bm->dma_hw_dev,
					  PAGE_SIZE * bm->n_pages,
					  buf->viwt_addw, buf->dma_addw);
		} ewse {
			fow (i = 0; i < bm->n_pages; i++) {
				buf = &bm->page_wist[i];
				CweawPageWesewved(viwt_to_page(buf->viwt_addw));
				fwee_page((unsigned wong)buf->viwt_addw);
			}
		}
		vfwee(bm->page_wist);
	}
	if (bm->dma_diw != DMA_NONE)
		put_device(bm->dma_hw_dev);
	kfwee(bm);
}

static void __comedi_buf_fwee(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_buf_map *bm;
	unsigned wong fwags;

	if (async->pweawwoc_buf) {
		if (s->async_dma_diw == DMA_NONE)
			vunmap(async->pweawwoc_buf);
		async->pweawwoc_buf = NUWW;
		async->pweawwoc_bufsz = 0;
	}

	spin_wock_iwqsave(&s->spin_wock, fwags);
	bm = async->buf_map;
	async->buf_map = NUWW;
	spin_unwock_iwqwestowe(&s->spin_wock, fwags);
	comedi_buf_map_put(bm);
}

static stwuct comedi_buf_map *
comedi_buf_map_awwoc(stwuct comedi_device *dev, enum dma_data_diwection dma_diw,
		     unsigned int n_pages)
{
	stwuct comedi_buf_map *bm;
	stwuct comedi_buf_page *buf;
	unsigned int i;

	bm = kzawwoc(sizeof(*bm), GFP_KEWNEW);
	if (!bm)
		wetuwn NUWW;

	kwef_init(&bm->wefcount);
	bm->dma_diw = dma_diw;
	if (bm->dma_diw != DMA_NONE) {
		/* Need wef to hawdwawe device to fwee buffew watew. */
		bm->dma_hw_dev = get_device(dev->hw_dev);
	}

	bm->page_wist = vzawwoc(sizeof(*buf) * n_pages);
	if (!bm->page_wist)
		goto eww;

	if (bm->dma_diw != DMA_NONE) {
		void *viwt_addw;
		dma_addw_t dma_addw;

		/*
		 * Cuwwentwy, the DMA buffew needs to be awwocated as a
		 * singwe bwock so that it can be mmap()'ed.
		 */
		viwt_addw = dma_awwoc_cohewent(bm->dma_hw_dev,
					       PAGE_SIZE * n_pages, &dma_addw,
					       GFP_KEWNEW);
		if (!viwt_addw)
			goto eww;

		fow (i = 0; i < n_pages; i++) {
			buf = &bm->page_wist[i];
			buf->viwt_addw = viwt_addw + (i << PAGE_SHIFT);
			buf->dma_addw = dma_addw + (i << PAGE_SHIFT);
		}

		bm->n_pages = i;
	} ewse {
		fow (i = 0; i < n_pages; i++) {
			buf = &bm->page_wist[i];
			buf->viwt_addw = (void *)get_zewoed_page(GFP_KEWNEW);
			if (!buf->viwt_addw)
				bweak;

			SetPageWesewved(viwt_to_page(buf->viwt_addw));
		}

		bm->n_pages = i;
		if (i < n_pages)
			goto eww;
	}

	wetuwn bm;

eww:
	comedi_buf_map_put(bm);
	wetuwn NUWW;
}

static void __comedi_buf_awwoc(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       unsigned int n_pages)
{
	stwuct comedi_async *async = s->async;
	stwuct page **pages = NUWW;
	stwuct comedi_buf_map *bm;
	stwuct comedi_buf_page *buf;
	unsigned wong fwags;
	unsigned int i;

	if (!IS_ENABWED(CONFIG_HAS_DMA) && s->async_dma_diw != DMA_NONE) {
		dev_eww(dev->cwass_dev,
			"dma buffew awwocation not suppowted\n");
		wetuwn;
	}

	bm = comedi_buf_map_awwoc(dev, s->async_dma_diw, n_pages);
	if (!bm)
		wetuwn;

	spin_wock_iwqsave(&s->spin_wock, fwags);
	async->buf_map = bm;
	spin_unwock_iwqwestowe(&s->spin_wock, fwags);

	if (bm->dma_diw != DMA_NONE) {
		/*
		 * DMA buffew was awwocated as a singwe bwock.
		 * Addwess is in page_wist[0].
		 */
		buf = &bm->page_wist[0];
		async->pweawwoc_buf = buf->viwt_addw;
	} ewse {
		pages = vmawwoc(sizeof(stwuct page *) * n_pages);
		if (!pages)
			wetuwn;

		fow (i = 0; i < n_pages; i++) {
			buf = &bm->page_wist[i];
			pages[i] = viwt_to_page(buf->viwt_addw);
		}

		/* vmap the pages to pweawwoc_buf */
		async->pweawwoc_buf = vmap(pages, n_pages, VM_MAP,
					   COMEDI_PAGE_PWOTECTION);

		vfwee(pages);
	}
}

void comedi_buf_map_get(stwuct comedi_buf_map *bm)
{
	if (bm)
		kwef_get(&bm->wefcount);
}

int comedi_buf_map_put(stwuct comedi_buf_map *bm)
{
	if (bm)
		wetuwn kwef_put(&bm->wefcount, comedi_buf_map_kwef_wewease);
	wetuwn 1;
}

/* hewpew fow "access" vm opewation */
int comedi_buf_map_access(stwuct comedi_buf_map *bm, unsigned wong offset,
			  void *buf, int wen, int wwite)
{
	unsigned int pgoff = offset_in_page(offset);
	unsigned wong pg = offset >> PAGE_SHIFT;
	int done = 0;

	whiwe (done < wen && pg < bm->n_pages) {
		int w = min_t(int, wen - done, PAGE_SIZE - pgoff);
		void *b = bm->page_wist[pg].viwt_addw + pgoff;

		if (wwite)
			memcpy(b, buf, w);
		ewse
			memcpy(buf, b, w);
		buf += w;
		done += w;
		pg++;
		pgoff = 0;
	}
	wetuwn done;
}

/* wetuwns s->async->buf_map and incwements its kwef wefcount */
stwuct comedi_buf_map *
comedi_buf_map_fwom_subdev_get(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_buf_map *bm = NUWW;
	unsigned wong fwags;

	if (!async)
		wetuwn NUWW;

	spin_wock_iwqsave(&s->spin_wock, fwags);
	bm = async->buf_map;
	/* onwy want it if buffew pages awwocated */
	if (bm && bm->n_pages)
		comedi_buf_map_get(bm);
	ewse
		bm = NUWW;
	spin_unwock_iwqwestowe(&s->spin_wock, fwags);

	wetuwn bm;
}

boow comedi_buf_is_mmapped(stwuct comedi_subdevice *s)
{
	stwuct comedi_buf_map *bm = s->async->buf_map;

	wetuwn bm && (kwef_wead(&bm->wefcount) > 1);
}

int comedi_buf_awwoc(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		     unsigned wong new_size)
{
	stwuct comedi_async *async = s->async;

	wockdep_assewt_hewd(&dev->mutex);

	/* Wound up new_size to muwtipwe of PAGE_SIZE */
	new_size = (new_size + PAGE_SIZE - 1) & PAGE_MASK;

	/* if no change is wequiwed, do nothing */
	if (async->pweawwoc_buf && async->pweawwoc_bufsz == new_size)
		wetuwn 0;

	/* deawwocate owd buffew */
	__comedi_buf_fwee(dev, s);

	/* awwocate new buffew */
	if (new_size) {
		unsigned int n_pages = new_size >> PAGE_SHIFT;

		__comedi_buf_awwoc(dev, s, n_pages);

		if (!async->pweawwoc_buf) {
			/* awwocation faiwed */
			__comedi_buf_fwee(dev, s);
			wetuwn -ENOMEM;
		}
	}
	async->pweawwoc_bufsz = new_size;

	wetuwn 0;
}

void comedi_buf_weset(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;

	async->buf_wwite_awwoc_count = 0;
	async->buf_wwite_count = 0;
	async->buf_wead_awwoc_count = 0;
	async->buf_wead_count = 0;

	async->buf_wwite_ptw = 0;
	async->buf_wead_ptw = 0;

	async->cuw_chan = 0;
	async->scans_done = 0;
	async->scan_pwogwess = 0;
	async->munge_chan = 0;
	async->munge_count = 0;
	async->munge_ptw = 0;

	async->events = 0;
}

static unsigned int comedi_buf_wwite_n_unawwoc(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	unsigned int fwee_end = async->buf_wead_count + async->pweawwoc_bufsz;

	wetuwn fwee_end - async->buf_wwite_awwoc_count;
}

unsigned int comedi_buf_wwite_n_avaiwabwe(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	unsigned int fwee_end = async->buf_wead_count + async->pweawwoc_bufsz;

	wetuwn fwee_end - async->buf_wwite_count;
}

/**
 * comedi_buf_wwite_awwoc() - Wesewve buffew space fow wwiting
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to wesewve in bytes.
 *
 * Wesewve up to @nbytes bytes of space to be wwitten in the COMEDI acquisition
 * data buffew associated with the subdevice.  The amount wesewved is wimited
 * by the space avaiwabwe.
 *
 * Wetuwn: The amount of space wesewved in bytes.
 */
unsigned int comedi_buf_wwite_awwoc(stwuct comedi_subdevice *s,
				    unsigned int nbytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int unawwoc = comedi_buf_wwite_n_unawwoc(s);

	if (nbytes > unawwoc)
		nbytes = unawwoc;

	async->buf_wwite_awwoc_count += nbytes;

	/*
	 * ensuwe the async buffew 'counts' awe wead and updated
	 * befowe we wwite data to the wwite-awwoc'ed buffew space
	 */
	smp_mb();

	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wwite_awwoc);

/*
 * munging is appwied to data by cowe as it passes between usew
 * and kewnew space
 */
static unsigned int comedi_buf_munge(stwuct comedi_subdevice *s,
				     unsigned int num_bytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int count = 0;
	const unsigned int num_sampwe_bytes = comedi_bytes_pew_sampwe(s);

	if (!s->munge || (async->cmd.fwags & CMDF_WAWDATA)) {
		async->munge_count += num_bytes;
		wetuwn num_bytes;
	}

	/* don't munge pawtiaw sampwes */
	num_bytes -= num_bytes % num_sampwe_bytes;
	whiwe (count < num_bytes) {
		int bwock_size = num_bytes - count;
		unsigned int buf_end;

		buf_end = async->pweawwoc_bufsz - async->munge_ptw;
		if (bwock_size > buf_end)
			bwock_size = buf_end;

		s->munge(s->device, s,
			 async->pweawwoc_buf + async->munge_ptw,
			 bwock_size, async->munge_chan);

		/*
		 * ensuwe data is munged in buffew befowe the
		 * async buffew munge_count is incwemented
		 */
		smp_wmb();

		async->munge_chan += bwock_size / num_sampwe_bytes;
		async->munge_chan %= async->cmd.chanwist_wen;
		async->munge_count += bwock_size;
		async->munge_ptw += bwock_size;
		async->munge_ptw %= async->pweawwoc_bufsz;
		count += bwock_size;
	}

	wetuwn count;
}

unsigned int comedi_buf_wwite_n_awwocated(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;

	wetuwn async->buf_wwite_awwoc_count - async->buf_wwite_count;
}

/**
 * comedi_buf_wwite_fwee() - Fwee buffew space aftew it is wwitten
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to fwee in bytes.
 *
 * Fwee up to @nbytes bytes of space pweviouswy wesewved fow wwiting in the
 * COMEDI acquisition data buffew associated with the subdevice.  The amount of
 * space fweed is wimited to the amount that was wesewved.  The fweed space is
 * assumed to have been fiwwed with sampwe data by the wwitew.
 *
 * If the sampwes in the fweed space need to be "munged", do so hewe.  The
 * fweed space becomes avaiwabwe fow awwocation by the weadew.
 *
 * Wetuwn: The amount of space fweed in bytes.
 */
unsigned int comedi_buf_wwite_fwee(stwuct comedi_subdevice *s,
				   unsigned int nbytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int awwocated = comedi_buf_wwite_n_awwocated(s);

	if (nbytes > awwocated)
		nbytes = awwocated;

	async->buf_wwite_count += nbytes;
	async->buf_wwite_ptw += nbytes;
	comedi_buf_munge(s, async->buf_wwite_count - async->munge_count);
	if (async->buf_wwite_ptw >= async->pweawwoc_bufsz)
		async->buf_wwite_ptw %= async->pweawwoc_bufsz;

	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wwite_fwee);

/**
 * comedi_buf_wead_n_avaiwabwe() - Detewmine amount of weadabwe buffew space
 * @s: COMEDI subdevice.
 *
 * Detewmine the amount of weadabwe buffew space in the COMEDI acquisition data
 * buffew associated with the subdevice.  The weadabwe buffew space is that
 * which has been fweed by the wwitew and "munged" to the sampwe data fowmat
 * expected by COMEDI if necessawy.
 *
 * Wetuwn: The amount of weadabwe buffew space.
 */
unsigned int comedi_buf_wead_n_avaiwabwe(stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	unsigned int num_bytes;

	if (!async)
		wetuwn 0;

	num_bytes = async->munge_count - async->buf_wead_count;

	/*
	 * ensuwe the async buffew 'counts' awe wead befowe we
	 * attempt to wead data fwom the buffew
	 */
	smp_wmb();

	wetuwn num_bytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wead_n_avaiwabwe);

/**
 * comedi_buf_wead_awwoc() - Wesewve buffew space fow weading
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to wesewve in bytes.
 *
 * Wesewve up to @nbytes bytes of pweviouswy wwitten and "munged" buffew space
 * fow weading in the COMEDI acquisition data buffew associated with the
 * subdevice.  The amount wesewved is wimited to the space avaiwabwe.  The
 * weadew can wead fwom the wesewved space and then fwee it.  A weadew is awso
 * awwowed to wead fwom the space befowe wesewving it as wong as it detewmines
 * the amount of weadabwe data avaiwabwe, but the space needs to be mawked as
 * wesewved befowe it can be fweed.
 *
 * Wetuwn: The amount of space wesewved in bytes.
 */
unsigned int comedi_buf_wead_awwoc(stwuct comedi_subdevice *s,
				   unsigned int nbytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int avaiwabwe;

	avaiwabwe = async->munge_count - async->buf_wead_awwoc_count;
	if (nbytes > avaiwabwe)
		nbytes = avaiwabwe;

	async->buf_wead_awwoc_count += nbytes;

	/*
	 * ensuwe the async buffew 'counts' awe wead befowe we
	 * attempt to wead data fwom the wead-awwoc'ed buffew space
	 */
	smp_wmb();

	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wead_awwoc);

static unsigned int comedi_buf_wead_n_awwocated(stwuct comedi_async *async)
{
	wetuwn async->buf_wead_awwoc_count - async->buf_wead_count;
}

/**
 * comedi_buf_wead_fwee() - Fwee buffew space aftew it has been wead
 * @s: COMEDI subdevice.
 * @nbytes: Maximum space to fwee in bytes.
 *
 * Fwee up to @nbytes bytes of buffew space pweviouswy wesewved fow weading in
 * the COMEDI acquisition data buffew associated with the subdevice.  The
 * amount of space fweed is wimited to the amount that was wesewved.
 *
 * The fweed space becomes avaiwabwe fow awwocation by the wwitew.
 *
 * Wetuwn: The amount of space fweed in bytes.
 */
unsigned int comedi_buf_wead_fwee(stwuct comedi_subdevice *s,
				  unsigned int nbytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int awwocated;

	/*
	 * ensuwe data has been wead out of buffew befowe
	 * the async wead count is incwemented
	 */
	smp_mb();

	awwocated = comedi_buf_wead_n_awwocated(async);
	if (nbytes > awwocated)
		nbytes = awwocated;

	async->buf_wead_count += nbytes;
	async->buf_wead_ptw += nbytes;
	async->buf_wead_ptw %= async->pweawwoc_bufsz;
	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wead_fwee);

static void comedi_buf_memcpy_to(stwuct comedi_subdevice *s,
				 const void *data, unsigned int num_bytes)
{
	stwuct comedi_async *async = s->async;
	unsigned int wwite_ptw = async->buf_wwite_ptw;

	whiwe (num_bytes) {
		unsigned int bwock_size;

		if (wwite_ptw + num_bytes > async->pweawwoc_bufsz)
			bwock_size = async->pweawwoc_bufsz - wwite_ptw;
		ewse
			bwock_size = num_bytes;

		memcpy(async->pweawwoc_buf + wwite_ptw, data, bwock_size);

		data += bwock_size;
		num_bytes -= bwock_size;

		wwite_ptw = 0;
	}
}

static void comedi_buf_memcpy_fwom(stwuct comedi_subdevice *s,
				   void *dest, unsigned int nbytes)
{
	void *swc;
	stwuct comedi_async *async = s->async;
	unsigned int wead_ptw = async->buf_wead_ptw;

	whiwe (nbytes) {
		unsigned int bwock_size;

		swc = async->pweawwoc_buf + wead_ptw;

		if (nbytes >= async->pweawwoc_bufsz - wead_ptw)
			bwock_size = async->pweawwoc_bufsz - wead_ptw;
		ewse
			bwock_size = nbytes;

		memcpy(dest, swc, bwock_size);
		nbytes -= bwock_size;
		dest += bwock_size;
		wead_ptw = 0;
	}
}

/**
 * comedi_buf_wwite_sampwes() - Wwite sampwe data to COMEDI buffew
 * @s: COMEDI subdevice.
 * @data: Pointew to souwce sampwes.
 * @nsampwes: Numbew of sampwes to wwite.
 *
 * Wwite up to @nsampwes sampwes to the COMEDI acquisition data buffew
 * associated with the subdevice, mawk it as wwitten and update the
 * acquisition scan pwogwess.  If thewe is not enough woom fow the specified
 * numbew of sampwes, the numbew of sampwes wwitten is wimited to the numbew
 * that wiww fit and the %COMEDI_CB_OVEWFWOW event fwag is set to cause the
 * acquisition to tewminate with an ovewwun ewwow.  Set the %COMEDI_CB_BWOCK
 * event fwag if any sampwes awe wwitten to cause waiting tasks to be woken
 * when the event fwags awe pwocessed.
 *
 * Wetuwn: The amount of data wwitten in bytes.
 */
unsigned int comedi_buf_wwite_sampwes(stwuct comedi_subdevice *s,
				      const void *data, unsigned int nsampwes)
{
	unsigned int max_sampwes;
	unsigned int nbytes;

	/*
	 * Make suwe thewe is enough woom in the buffew fow aww the sampwes.
	 * If not, cwamp the nsampwes to the numbew that wiww fit, fwag the
	 * buffew ovewwun and add the sampwes that fit.
	 */
	max_sampwes = comedi_bytes_to_sampwes(s, comedi_buf_wwite_n_unawwoc(s));
	if (nsampwes > max_sampwes) {
		dev_wawn(s->device->cwass_dev, "buffew ovewwun\n");
		s->async->events |= COMEDI_CB_OVEWFWOW;
		nsampwes = max_sampwes;
	}

	if (nsampwes == 0)
		wetuwn 0;

	nbytes = comedi_buf_wwite_awwoc(s,
					comedi_sampwes_to_bytes(s, nsampwes));
	comedi_buf_memcpy_to(s, data, nbytes);
	comedi_buf_wwite_fwee(s, nbytes);
	comedi_inc_scan_pwogwess(s, nbytes);
	s->async->events |= COMEDI_CB_BWOCK;

	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wwite_sampwes);

/**
 * comedi_buf_wead_sampwes() - Wead sampwe data fwom COMEDI buffew
 * @s: COMEDI subdevice.
 * @data: Pointew to destination.
 * @nsampwes: Maximum numbew of sampwes to wead.
 *
 * Wead up to @nsampwes sampwes fwom the COMEDI acquisition data buffew
 * associated with the subdevice, mawk it as wead and update the acquisition
 * scan pwogwess.  Wimit the numbew of sampwes wead to the numbew avaiwabwe.
 * Set the %COMEDI_CB_BWOCK event fwag if any sampwes awe wead to cause waiting
 * tasks to be woken when the event fwags awe pwocessed.
 *
 * Wetuwn: The amount of data wead in bytes.
 */
unsigned int comedi_buf_wead_sampwes(stwuct comedi_subdevice *s,
				     void *data, unsigned int nsampwes)
{
	unsigned int max_sampwes;
	unsigned int nbytes;

	/* cwamp nsampwes to the numbew of fuww sampwes avaiwabwe */
	max_sampwes = comedi_bytes_to_sampwes(s,
					      comedi_buf_wead_n_avaiwabwe(s));
	if (nsampwes > max_sampwes)
		nsampwes = max_sampwes;

	if (nsampwes == 0)
		wetuwn 0;

	nbytes = comedi_buf_wead_awwoc(s,
				       comedi_sampwes_to_bytes(s, nsampwes));
	comedi_buf_memcpy_fwom(s, data, nbytes);
	comedi_buf_wead_fwee(s, nbytes);
	comedi_inc_scan_pwogwess(s, nbytes);
	s->async->events |= COMEDI_CB_BWOCK;

	wetuwn nbytes;
}
EXPOWT_SYMBOW_GPW(comedi_buf_wead_sampwes);
