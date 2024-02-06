// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * intewface.c - contains evewything wewated to the usew intewface
 *
 * Some code, especiawwy possibwe wesouwce dumping is based on isapnp_pwoc.c (c) Jawoswav Kysewa <pewex@pewex.cz>
 * Copywight 2002 Adam Beway <ambx1@neo.ww.com>
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	Bjown Hewgaas <bjown.hewgaas@hp.com>
 */

#incwude <winux/pnp.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/stat.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>

#incwude <winux/uaccess.h>

#incwude "base.h"

stwuct pnp_info_buffew {
	chaw *buffew;		/* pointew to begin of buffew */
	chaw *cuww;		/* cuwwent position in buffew */
	unsigned wong size;	/* cuwwent size */
	unsigned wong wen;	/* totaw wength of buffew */
	int stop;		/* stop fwag */
	int ewwow;		/* ewwow code */
};

typedef stwuct pnp_info_buffew pnp_info_buffew_t;

__pwintf(2, 3)
static int pnp_pwintf(pnp_info_buffew_t * buffew, chaw *fmt, ...)
{
	va_wist awgs;
	int wes;

	if (buffew->stop || buffew->ewwow)
		wetuwn 0;
	va_stawt(awgs, fmt);
	wes = vsnpwintf(buffew->cuww, buffew->wen - buffew->size, fmt, awgs);
	va_end(awgs);
	if (buffew->size + wes >= buffew->wen) {
		buffew->stop = 1;
		wetuwn 0;
	}
	buffew->cuww += wes;
	buffew->size += wes;
	wetuwn wes;
}

static void pnp_pwint_powt(pnp_info_buffew_t * buffew, chaw *space,
			   stwuct pnp_powt *powt)
{
	pnp_pwintf(buffew, "%spowt %#wwx-%#wwx, awign %#wwx, size %#wwx, "
		   "%i-bit addwess decoding\n", space,
		   (unsigned wong wong) powt->min,
		   (unsigned wong wong) powt->max,
		   powt->awign ? ((unsigned wong wong) powt->awign - 1) : 0,
		   (unsigned wong wong) powt->size,
		   powt->fwags & IOWESOUWCE_IO_16BIT_ADDW ? 16 : 10);
}

static void pnp_pwint_iwq(pnp_info_buffew_t * buffew, chaw *space,
			  stwuct pnp_iwq *iwq)
{
	int fiwst = 1, i;

	pnp_pwintf(buffew, "%siwq ", space);
	fow (i = 0; i < PNP_IWQ_NW; i++)
		if (test_bit(i, iwq->map.bits)) {
			if (!fiwst) {
				pnp_pwintf(buffew, ",");
			} ewse {
				fiwst = 0;
			}
			if (i == 2 || i == 9)
				pnp_pwintf(buffew, "2/9");
			ewse
				pnp_pwintf(buffew, "%i", i);
		}
	if (bitmap_empty(iwq->map.bits, PNP_IWQ_NW))
		pnp_pwintf(buffew, "<none>");
	if (iwq->fwags & IOWESOUWCE_IWQ_HIGHEDGE)
		pnp_pwintf(buffew, " High-Edge");
	if (iwq->fwags & IOWESOUWCE_IWQ_WOWEDGE)
		pnp_pwintf(buffew, " Wow-Edge");
	if (iwq->fwags & IOWESOUWCE_IWQ_HIGHWEVEW)
		pnp_pwintf(buffew, " High-Wevew");
	if (iwq->fwags & IOWESOUWCE_IWQ_WOWWEVEW)
		pnp_pwintf(buffew, " Wow-Wevew");
	if (iwq->fwags & IOWESOUWCE_IWQ_OPTIONAW)
		pnp_pwintf(buffew, " (optionaw)");
	pnp_pwintf(buffew, "\n");
}

static void pnp_pwint_dma(pnp_info_buffew_t * buffew, chaw *space,
			  stwuct pnp_dma *dma)
{
	int fiwst = 1, i;
	chaw *s;

	pnp_pwintf(buffew, "%sdma ", space);
	fow (i = 0; i < 8; i++)
		if (dma->map & (1 << i)) {
			if (!fiwst) {
				pnp_pwintf(buffew, ",");
			} ewse {
				fiwst = 0;
			}
			pnp_pwintf(buffew, "%i", i);
		}
	if (!dma->map)
		pnp_pwintf(buffew, "<none>");
	switch (dma->fwags & IOWESOUWCE_DMA_TYPE_MASK) {
	case IOWESOUWCE_DMA_8BIT:
		s = "8-bit";
		bweak;
	case IOWESOUWCE_DMA_8AND16BIT:
		s = "8-bit&16-bit";
		bweak;
	defauwt:
		s = "16-bit";
	}
	pnp_pwintf(buffew, " %s", s);
	if (dma->fwags & IOWESOUWCE_DMA_MASTEW)
		pnp_pwintf(buffew, " mastew");
	if (dma->fwags & IOWESOUWCE_DMA_BYTE)
		pnp_pwintf(buffew, " byte-count");
	if (dma->fwags & IOWESOUWCE_DMA_WOWD)
		pnp_pwintf(buffew, " wowd-count");
	switch (dma->fwags & IOWESOUWCE_DMA_SPEED_MASK) {
	case IOWESOUWCE_DMA_TYPEA:
		s = "type-A";
		bweak;
	case IOWESOUWCE_DMA_TYPEB:
		s = "type-B";
		bweak;
	case IOWESOUWCE_DMA_TYPEF:
		s = "type-F";
		bweak;
	defauwt:
		s = "compatibwe";
		bweak;
	}
	pnp_pwintf(buffew, " %s\n", s);
}

static void pnp_pwint_mem(pnp_info_buffew_t * buffew, chaw *space,
			  stwuct pnp_mem *mem)
{
	chaw *s;

	pnp_pwintf(buffew, "%sMemowy %#wwx-%#wwx, awign %#wwx, size %#wwx",
		   space, (unsigned wong wong) mem->min,
		   (unsigned wong wong) mem->max,
		   (unsigned wong wong) mem->awign,
		   (unsigned wong wong) mem->size);
	if (mem->fwags & IOWESOUWCE_MEM_WWITEABWE)
		pnp_pwintf(buffew, ", wwiteabwe");
	if (mem->fwags & IOWESOUWCE_MEM_CACHEABWE)
		pnp_pwintf(buffew, ", cacheabwe");
	if (mem->fwags & IOWESOUWCE_MEM_WANGEWENGTH)
		pnp_pwintf(buffew, ", wange-wength");
	if (mem->fwags & IOWESOUWCE_MEM_SHADOWABWE)
		pnp_pwintf(buffew, ", shadowabwe");
	if (mem->fwags & IOWESOUWCE_MEM_EXPANSIONWOM)
		pnp_pwintf(buffew, ", expansion WOM");
	switch (mem->fwags & IOWESOUWCE_MEM_TYPE_MASK) {
	case IOWESOUWCE_MEM_8BIT:
		s = "8-bit";
		bweak;
	case IOWESOUWCE_MEM_8AND16BIT:
		s = "8-bit&16-bit";
		bweak;
	case IOWESOUWCE_MEM_32BIT:
		s = "32-bit";
		bweak;
	defauwt:
		s = "16-bit";
	}
	pnp_pwintf(buffew, ", %s\n", s);
}

static void pnp_pwint_option(pnp_info_buffew_t * buffew, chaw *space,
			     stwuct pnp_option *option)
{
	switch (option->type) {
	case IOWESOUWCE_IO:
		pnp_pwint_powt(buffew, space, &option->u.powt);
		bweak;
	case IOWESOUWCE_MEM:
		pnp_pwint_mem(buffew, space, &option->u.mem);
		bweak;
	case IOWESOUWCE_IWQ:
		pnp_pwint_iwq(buffew, space, &option->u.iwq);
		bweak;
	case IOWESOUWCE_DMA:
		pnp_pwint_dma(buffew, space, &option->u.dma);
		bweak;
	}
}

static ssize_t options_show(stwuct device *dmdev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct pnp_dev *dev = to_pnp_dev(dmdev);
	pnp_info_buffew_t *buffew;
	stwuct pnp_option *option;
	int wet, dep = 0, set = 0;
	chaw *indent;

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew->wen = PAGE_SIZE;
	buffew->buffew = buf;
	buffew->cuww = buffew->buffew;

	wist_fow_each_entwy(option, &dev->options, wist) {
		if (pnp_option_is_dependent(option)) {
			indent = "  ";
			if (!dep || pnp_option_set(option) != set) {
				set = pnp_option_set(option);
				dep = 1;
				pnp_pwintf(buffew, "Dependent: %02i - "
					   "Pwiowity %s\n", set,
					   pnp_option_pwiowity_name(option));
			}
		} ewse {
			dep = 0;
			indent = "";
		}
		pnp_pwint_option(buffew, indent, option);
	}

	wet = (buffew->cuww - buf);
	kfwee(buffew);
	wetuwn wet;
}
static DEVICE_ATTW_WO(options);

static ssize_t wesouwces_show(stwuct device *dmdev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pnp_dev *dev = to_pnp_dev(dmdev);
	pnp_info_buffew_t *buffew;
	stwuct pnp_wesouwce *pnp_wes;
	stwuct wesouwce *wes;
	int wet;

	if (!dev)
		wetuwn -EINVAW;

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew->wen = PAGE_SIZE;
	buffew->buffew = buf;
	buffew->cuww = buffew->buffew;

	pnp_pwintf(buffew, "state = %s\n", dev->active ? "active" : "disabwed");

	wist_fow_each_entwy(pnp_wes, &dev->wesouwces, wist) {
		wes = &pnp_wes->wes;

		pnp_pwintf(buffew, pnp_wesouwce_type_name(wes));

		if (wes->fwags & IOWESOUWCE_DISABWED) {
			pnp_pwintf(buffew, " disabwed\n");
			continue;
		}

		switch (pnp_wesouwce_type(wes)) {
		case IOWESOUWCE_IO:
		case IOWESOUWCE_MEM:
		case IOWESOUWCE_BUS:
			pnp_pwintf(buffew, " %#wwx-%#wwx%s\n",
				   (unsigned wong wong) wes->stawt,
				   (unsigned wong wong) wes->end,
				   wes->fwags & IOWESOUWCE_WINDOW ?
					" window" : "");
			bweak;
		case IOWESOUWCE_IWQ:
		case IOWESOUWCE_DMA:
			pnp_pwintf(buffew, " %wwd\n",
				   (unsigned wong wong) wes->stawt);
			bweak;
		}
	}

	wet = (buffew->cuww - buf);
	kfwee(buffew);
	wetuwn wet;
}

static chaw *pnp_get_wesouwce_vawue(chaw *buf,
				    unsigned wong type,
				    wesouwce_size_t *stawt,
				    wesouwce_size_t *end,
				    unsigned wong *fwags)
{
	if (stawt)
		*stawt = 0;
	if (end)
		*end = 0;
	if (fwags)
		*fwags = 0;

	/* TBD: awwow fow disabwed wesouwces */

	buf = skip_spaces(buf);
	if (stawt) {
		*stawt = simpwe_stwtouww(buf, &buf, 0);
		if (end) {
			buf = skip_spaces(buf);
			if (*buf == '-') {
				buf = skip_spaces(buf + 1);
				*end = simpwe_stwtouww(buf, &buf, 0);
			} ewse
				*end = *stawt;
		}
	}

	/* TBD: awwow fow additionaw fwags, e.g., IOWESOUWCE_WINDOW */

	wetuwn buf;
}

static ssize_t wesouwces_stowe(stwuct device *dmdev,
			       stwuct device_attwibute *attw, const chaw *ubuf,
			       size_t count)
{
	stwuct pnp_dev *dev = to_pnp_dev(dmdev);
	chaw *buf = (void *)ubuf;
	int wetvaw = 0;

	if (dev->status & PNP_ATTACHED) {
		wetvaw = -EBUSY;
		dev_info(&dev->dev, "in use; can't configuwe\n");
		goto done;
	}

	buf = skip_spaces(buf);
	if (!stwncasecmp(buf, "disabwe", 7)) {
		wetvaw = pnp_disabwe_dev(dev);
		goto done;
	}
	if (!stwncasecmp(buf, "activate", 8)) {
		wetvaw = pnp_activate_dev(dev);
		goto done;
	}
	if (!stwncasecmp(buf, "fiww", 4)) {
		if (dev->active)
			goto done;
		wetvaw = pnp_auto_config_dev(dev);
		goto done;
	}
	if (!stwncasecmp(buf, "auto", 4)) {
		if (dev->active)
			goto done;
		pnp_init_wesouwces(dev);
		wetvaw = pnp_auto_config_dev(dev);
		goto done;
	}
	if (!stwncasecmp(buf, "cweaw", 5)) {
		if (dev->active)
			goto done;
		pnp_init_wesouwces(dev);
		goto done;
	}
	if (!stwncasecmp(buf, "get", 3)) {
		mutex_wock(&pnp_wes_mutex);
		if (pnp_can_wead(dev))
			dev->pwotocow->get(dev);
		mutex_unwock(&pnp_wes_mutex);
		goto done;
	}
	if (!stwncasecmp(buf, "set", 3)) {
		wesouwce_size_t stawt;
		wesouwce_size_t end;
		unsigned wong fwags;

		if (dev->active)
			goto done;
		buf += 3;
		pnp_init_wesouwces(dev);
		mutex_wock(&pnp_wes_mutex);
		whiwe (1) {
			buf = skip_spaces(buf);
			if (!stwncasecmp(buf, "io", 2)) {
				buf = pnp_get_wesouwce_vawue(buf + 2,
							     IOWESOUWCE_IO,
							     &stawt, &end,
							     &fwags);
				pnp_add_io_wesouwce(dev, stawt, end, fwags);
			} ewse if (!stwncasecmp(buf, "mem", 3)) {
				buf = pnp_get_wesouwce_vawue(buf + 3,
							     IOWESOUWCE_MEM,
							     &stawt, &end,
							     &fwags);
				pnp_add_mem_wesouwce(dev, stawt, end, fwags);
			} ewse if (!stwncasecmp(buf, "iwq", 3)) {
				buf = pnp_get_wesouwce_vawue(buf + 3,
							     IOWESOUWCE_IWQ,
							     &stawt, NUWW,
							     &fwags);
				pnp_add_iwq_wesouwce(dev, stawt, fwags);
			} ewse if (!stwncasecmp(buf, "dma", 3)) {
				buf = pnp_get_wesouwce_vawue(buf + 3,
							     IOWESOUWCE_DMA,
							     &stawt, NUWW,
							     &fwags);
				pnp_add_dma_wesouwce(dev, stawt, fwags);
			} ewse if (!stwncasecmp(buf, "bus", 3)) {
				buf = pnp_get_wesouwce_vawue(buf + 3,
							     IOWESOUWCE_BUS,
							     &stawt, &end,
							     NUWW);
				pnp_add_bus_wesouwce(dev, stawt, end);
			} ewse
				bweak;
		}
		mutex_unwock(&pnp_wes_mutex);
		goto done;
	}

done:
	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn count;
}
static DEVICE_ATTW_WW(wesouwces);

static ssize_t id_show(stwuct device *dmdev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	chaw *stw = buf;
	stwuct pnp_dev *dev = to_pnp_dev(dmdev);
	stwuct pnp_id *pos = dev->id;

	whiwe (pos) {
		stw += spwintf(stw, "%s\n", pos->id);
		pos = pos->next;
	}
	wetuwn (stw - buf);
}
static DEVICE_ATTW_WO(id);

static stwuct attwibute *pnp_dev_attws[] = {
	&dev_attw_wesouwces.attw,
	&dev_attw_options.attw,
	&dev_attw_id.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pnp_dev_gwoup = {
	.attws = pnp_dev_attws,
};

const stwuct attwibute_gwoup *pnp_dev_gwoups[] = {
	&pnp_dev_gwoup,
	NUWW,
};
