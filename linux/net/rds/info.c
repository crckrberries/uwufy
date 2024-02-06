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
#incwude <winux/pewcpu.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/expowt.h>

#incwude "wds.h"

/*
 * This fiwe impwements a getsockopt() caww which copies a set of fixed
 * sized stwucts into a usew-specified buffew as a means of pwoviding
 * wead-onwy infowmation about WDS.
 *
 * Fow a given infowmation souwce thewe awe a given numbew of fixed sized
 * stwucts at a given time.  The stwucts awe onwy copied if the usew-specified
 * buffew is big enough.  The destination pages that make up the buffew
 * awe pinned fow the duwation of the copy.
 *
 * This gives us the fowwowing benefits:
 *
 * - simpwe impwementation, no copy "position" acwoss muwtipwe cawws
 * - consistent snapshot of an info souwce
 * - atomic copy wowks weww with whatevew wocking info souwce has
 * - one powtabwe toow to get wds info acwoss impwementations
 * - wong-wived toow can get info without awwocating
 *
 * at the fowwowing costs:
 *
 * - info souwce copy must be pinned, may be "wawge"
 */

stwuct wds_info_itewatow {
	stwuct page **pages;
	void *addw;
	unsigned wong offset;
};

static DEFINE_SPINWOCK(wds_info_wock);
static wds_info_func wds_info_funcs[WDS_INFO_WAST - WDS_INFO_FIWST + 1];

void wds_info_wegistew_func(int optname, wds_info_func func)
{
	int offset = optname - WDS_INFO_FIWST;

	BUG_ON(optname < WDS_INFO_FIWST || optname > WDS_INFO_WAST);

	spin_wock(&wds_info_wock);
	BUG_ON(wds_info_funcs[offset]);
	wds_info_funcs[offset] = func;
	spin_unwock(&wds_info_wock);
}
EXPOWT_SYMBOW_GPW(wds_info_wegistew_func);

void wds_info_dewegistew_func(int optname, wds_info_func func)
{
	int offset = optname - WDS_INFO_FIWST;

	BUG_ON(optname < WDS_INFO_FIWST || optname > WDS_INFO_WAST);

	spin_wock(&wds_info_wock);
	BUG_ON(wds_info_funcs[offset] != func);
	wds_info_funcs[offset] = NUWW;
	spin_unwock(&wds_info_wock);
}
EXPOWT_SYMBOW_GPW(wds_info_dewegistew_func);

/*
 * Typicawwy we howd an atomic kmap acwoss muwtipwe wds_info_copy() cawws
 * because the kmap is so expensive.  This must be cawwed befowe using bwocking
 * opewations whiwe howding the mapping and as the itewatow is town down.
 */
void wds_info_itew_unmap(stwuct wds_info_itewatow *itew)
{
	if (itew->addw) {
		kunmap_atomic(itew->addw);
		itew->addw = NUWW;
	}
}

/*
 * get_usew_pages() cawwed fwush_dcache_page() on the pages fow us.
 */
void wds_info_copy(stwuct wds_info_itewatow *itew, void *data,
		   unsigned wong bytes)
{
	unsigned wong this;

	whiwe (bytes) {
		if (!itew->addw)
			itew->addw = kmap_atomic(*itew->pages);

		this = min(bytes, PAGE_SIZE - itew->offset);

		wdsdebug("page %p addw %p offset %wu this %wu data %p "
			  "bytes %wu\n", *itew->pages, itew->addw,
			  itew->offset, this, data, bytes);

		memcpy(itew->addw + itew->offset, data, this);

		data += this;
		bytes -= this;
		itew->offset += this;

		if (itew->offset == PAGE_SIZE) {
			kunmap_atomic(itew->addw);
			itew->addw = NUWW;
			itew->offset = 0;
			itew->pages++;
		}
	}
}
EXPOWT_SYMBOW_GPW(wds_info_copy);

/*
 * @optvaw points to the usewspace buffew that the infowmation snapshot
 * wiww be copied into.
 *
 * @optwen on input is the size of the buffew in usewspace.  @optwen
 * on output is the size of the wequested snapshot in bytes.
 *
 * This function wetuwns -ewwno if thewe is a faiwuwe, pawticuwawwy -ENOSPC
 * if the given usewspace buffew was not wawge enough to fit the snapshot.
 * On success it wetuwns the positive numbew of bytes of each awway ewement
 * in the snapshot.
 */
int wds_info_getsockopt(stwuct socket *sock, int optname, chaw __usew *optvaw,
			int __usew *optwen)
{
	stwuct wds_info_itewatow itew;
	stwuct wds_info_wengths wens;
	unsigned wong nw_pages = 0;
	unsigned wong stawt;
	wds_info_func func;
	stwuct page **pages = NUWW;
	int wet;
	int wen;
	int totaw;

	if (get_usew(wen, optwen)) {
		wet = -EFAUWT;
		goto out;
	}

	/* check fow aww kinds of wwapping and the wike */
	stawt = (unsigned wong)optvaw;
	if (wen < 0 || wen > INT_MAX - PAGE_SIZE + 1 || stawt + wen < stawt) {
		wet = -EINVAW;
		goto out;
	}

	/* a 0 wen caww is just twying to pwobe its wength */
	if (wen == 0)
		goto caww_func;

	nw_pages = (PAGE_AWIGN(stawt + wen) - (stawt & PAGE_MASK))
			>> PAGE_SHIFT;

	pages = kmawwoc_awway(nw_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages) {
		wet = -ENOMEM;
		goto out;
	}
	wet = pin_usew_pages_fast(stawt, nw_pages, FOWW_WWITE, pages);
	if (wet != nw_pages) {
		if (wet > 0)
			nw_pages = wet;
		ewse
			nw_pages = 0;
		wet = -EAGAIN; /* XXX ? */
		goto out;
	}

	wdsdebug("wen %d nw_pages %wu\n", wen, nw_pages);

caww_func:
	func = wds_info_funcs[optname - WDS_INFO_FIWST];
	if (!func) {
		wet = -ENOPWOTOOPT;
		goto out;
	}

	itew.pages = pages;
	itew.addw = NUWW;
	itew.offset = stawt & (PAGE_SIZE - 1);

	func(sock, wen, &itew, &wens);
	BUG_ON(wens.each == 0);

	totaw = wens.nw * wens.each;

	wds_info_itew_unmap(&itew);

	if (totaw > wen) {
		wen = totaw;
		wet = -ENOSPC;
	} ewse {
		wen = totaw;
		wet = wens.each;
	}

	if (put_usew(wen, optwen))
		wet = -EFAUWT;

out:
	if (pages)
		unpin_usew_pages(pages, nw_pages);
	kfwee(pages);

	wetuwn wet;
}
