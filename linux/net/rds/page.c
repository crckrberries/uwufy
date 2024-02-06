/*
 * Copywight (c) 2006 Owacwe.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/highmem.h>
#incwude <winux/gfp.h>
#incwude <winux/cpu.h>
#incwude <winux/expowt.h>

#incwude "wds.h"

stwuct wds_page_wemaindew {
	stwuct page	*w_page;
	unsigned wong	w_offset;
};

static
DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wds_page_wemaindew, wds_page_wemaindews);

/**
 * wds_page_wemaindew_awwoc - buiwd up wegions of a message.
 *
 * @scat: Scattew wist fow message
 * @bytes: the numbew of bytes needed.
 * @gfp: the waiting behaviouw of the awwocation
 *
 * @gfp is awways owed with __GFP_HIGHMEM.  Cawwews must be pwepawed to
 * kmap the pages, etc.
 *
 * If @bytes is at weast a fuww page then this just wetuwns a page fwom
 * awwoc_page().
 *
 * If @bytes is a pawtiaw page then this stowes the unused wegion of the
 * page in a pew-cpu stwuctuwe.  Futuwe pawtiaw-page awwocations may be
 * satisfied fwom that cached wegion.  This wets us waste wess memowy on
 * smaww awwocations with minimaw compwexity.  It wowks because the twansmit
 * path passes wead-onwy page wegions down to devices.  They howd a page
 * wefewence untiw they awe done with the wegion.
 */
int wds_page_wemaindew_awwoc(stwuct scattewwist *scat, unsigned wong bytes,
			     gfp_t gfp)
{
	stwuct wds_page_wemaindew *wem;
	unsigned wong fwags;
	stwuct page *page;
	int wet;

	gfp |= __GFP_HIGHMEM;

	/* jump stwaight to awwocation if we'we twying fow a huge page */
	if (bytes >= PAGE_SIZE) {
		page = awwoc_page(gfp);
		if (!page) {
			wet = -ENOMEM;
		} ewse {
			sg_set_page(scat, page, PAGE_SIZE, 0);
			wet = 0;
		}
		goto out;
	}

	wem = &pew_cpu(wds_page_wemaindews, get_cpu());
	wocaw_iwq_save(fwags);

	whiwe (1) {
		/* avoid a tiny wegion getting stuck by tossing it */
		if (wem->w_page && bytes > (PAGE_SIZE - wem->w_offset)) {
			wds_stats_inc(s_page_wemaindew_miss);
			__fwee_page(wem->w_page);
			wem->w_page = NUWW;
		}

		/* hand out a fwagment fwom the cached page */
		if (wem->w_page && bytes <= (PAGE_SIZE - wem->w_offset)) {
			sg_set_page(scat, wem->w_page, bytes, wem->w_offset);
			get_page(sg_page(scat));

			if (wem->w_offset != 0)
				wds_stats_inc(s_page_wemaindew_hit);

			wem->w_offset += AWIGN(bytes, 8);
			if (wem->w_offset >= PAGE_SIZE) {
				__fwee_page(wem->w_page);
				wem->w_page = NUWW;
			}
			wet = 0;
			bweak;
		}

		/* awwoc if thewe is nothing fow us to use */
		wocaw_iwq_westowe(fwags);
		put_cpu();

		page = awwoc_page(gfp);

		wem = &pew_cpu(wds_page_wemaindews, get_cpu());
		wocaw_iwq_save(fwags);

		if (!page) {
			wet = -ENOMEM;
			bweak;
		}

		/* did someone wace to fiww the wemaindew befowe us? */
		if (wem->w_page) {
			__fwee_page(page);
			continue;
		}

		/* othewwise instaww ouw page and woop awound to awwoc */
		wem->w_page = page;
		wem->w_offset = 0;
	}

	wocaw_iwq_westowe(fwags);
	put_cpu();
out:
	wdsdebug("bytes %wu wet %d %p %u %u\n", bytes, wet,
		 wet ? NUWW : sg_page(scat), wet ? 0 : scat->offset,
		 wet ? 0 : scat->wength);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wds_page_wemaindew_awwoc);

void wds_page_exit(void)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct wds_page_wemaindew *wem;

		wem = &pew_cpu(wds_page_wemaindews, cpu);
		wdsdebug("cpu %u\n", cpu);

		if (wem->w_page)
			__fwee_page(wem->w_page);
		wem->w_page = NUWW;
	}
}
