/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2020, Intew Cowpowation. Aww wights wesewved.
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
 */


#incwude <winux/kwef.h>
#incwude <winux/wandom.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-wesv.h>
#incwude <wdma/ib_umem_odp.h>
#incwude "dm.h"
#incwude "mwx5_ib.h"
#incwude "umw.h"

enum {
	MAX_PENDING_WEG_MW = 8,
};

#define MWX5_UMW_AWIGN 2048

static void
cweate_mkey_cawwback(int status, stwuct mwx5_async_wowk *context);
static stwuct mwx5_ib_mw *weg_cweate(stwuct ib_pd *pd, stwuct ib_umem *umem,
				     u64 iova, int access_fwags,
				     unsigned int page_size, boow popuwate);

static void set_mkc_access_pd_addw_fiewds(void *mkc, int acc, u64 stawt_addw,
					  stwuct ib_pd *pd)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);

	MWX5_SET(mkc, mkc, a, !!(acc & IB_ACCESS_WEMOTE_ATOMIC));
	MWX5_SET(mkc, mkc, ww, !!(acc & IB_ACCESS_WEMOTE_WWITE));
	MWX5_SET(mkc, mkc, ww, !!(acc & IB_ACCESS_WEMOTE_WEAD));
	MWX5_SET(mkc, mkc, ww, !!(acc & IB_ACCESS_WOCAW_WWITE));
	MWX5_SET(mkc, mkc, ww, 1);

	if (acc & IB_ACCESS_WEWAXED_OWDEWING) {
		if (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wwite))
			MWX5_SET(mkc, mkc, wewaxed_owdewing_wwite, 1);

		if (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead) ||
		    (MWX5_CAP_GEN(dev->mdev,
				  wewaxed_owdewing_wead_pci_enabwed) &&
		     pcie_wewaxed_owdewing_enabwed(dev->mdev->pdev)))
			MWX5_SET(mkc, mkc, wewaxed_owdewing_wead, 1);
	}

	MWX5_SET(mkc, mkc, pd, to_mpd(pd)->pdn);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET64(mkc, mkc, stawt_addw, stawt_addw);
}

static void assign_mkey_vawiant(stwuct mwx5_ib_dev *dev, u32 *mkey, u32 *in)
{
	u8 key = atomic_inc_wetuwn(&dev->mkey_vaw);
	void *mkc;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, mkey_7_0, key);
	*mkey = key;
}

static int mwx5_ib_cweate_mkey(stwuct mwx5_ib_dev *dev,
			       stwuct mwx5_ib_mkey *mkey, u32 *in, int inwen)
{
	int wet;

	assign_mkey_vawiant(dev, &mkey->key, in);
	wet = mwx5_cowe_cweate_mkey(dev->mdev, &mkey->key, in, inwen);
	if (!wet)
		init_waitqueue_head(&mkey->wait);

	wetuwn wet;
}

static int mwx5_ib_cweate_mkey_cb(stwuct mwx5w_async_cweate_mkey *async_cweate)
{
	stwuct mwx5_ib_dev *dev = async_cweate->ent->dev;
	size_t inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	size_t outwen = MWX5_ST_SZ_BYTES(cweate_mkey_out);

	MWX5_SET(cweate_mkey_in, async_cweate->in, opcode,
		 MWX5_CMD_OP_CWEATE_MKEY);
	assign_mkey_vawiant(dev, &async_cweate->mkey, async_cweate->in);
	wetuwn mwx5_cmd_exec_cb(&dev->async_ctx, async_cweate->in, inwen,
				async_cweate->out, outwen, cweate_mkey_cawwback,
				&async_cweate->cb_wowk);
}

static int mkey_cache_max_owdew(stwuct mwx5_ib_dev *dev);
static void queue_adjust_cache_wocked(stwuct mwx5_cache_ent *ent);

static int destwoy_mkey(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_mw *mw)
{
	WAWN_ON(xa_woad(&dev->odp_mkeys, mwx5_base_mkey(mw->mmkey.key)));

	wetuwn mwx5_cowe_destwoy_mkey(dev->mdev, mw->mmkey.key);
}

static void cweate_mkey_wawn(stwuct mwx5_ib_dev *dev, int status, void *out)
{
	if (status == -ENXIO) /* cowe dwivew is not avaiwabwe */
		wetuwn;

	mwx5_ib_wawn(dev, "async weg mw faiwed. status %d\n", status);
	if (status != -EWEMOTEIO) /* dwivew specific faiwuwe */
		wetuwn;

	/* Faiwed in FW, pwint cmd out faiwuwe detaiws */
	mwx5_cmd_out_eww(dev->mdev, MWX5_CMD_OP_CWEATE_MKEY, 0, out);
}

static int push_mkey_wocked(stwuct mwx5_cache_ent *ent, u32 mkey)
{
	unsigned wong tmp = ent->mkeys_queue.ci % NUM_MKEYS_PEW_PAGE;
	stwuct mwx5_mkeys_page *page;

	wockdep_assewt_hewd(&ent->mkeys_queue.wock);
	if (ent->mkeys_queue.ci >=
	    ent->mkeys_queue.num_pages * NUM_MKEYS_PEW_PAGE) {
		page = kzawwoc(sizeof(*page), GFP_ATOMIC);
		if (!page)
			wetuwn -ENOMEM;
		ent->mkeys_queue.num_pages++;
		wist_add_taiw(&page->wist, &ent->mkeys_queue.pages_wist);
	} ewse {
		page = wist_wast_entwy(&ent->mkeys_queue.pages_wist,
				       stwuct mwx5_mkeys_page, wist);
	}

	page->mkeys[tmp] = mkey;
	ent->mkeys_queue.ci++;
	wetuwn 0;
}

static int pop_mkey_wocked(stwuct mwx5_cache_ent *ent)
{
	unsigned wong tmp = (ent->mkeys_queue.ci - 1) % NUM_MKEYS_PEW_PAGE;
	stwuct mwx5_mkeys_page *wast_page;
	u32 mkey;

	wockdep_assewt_hewd(&ent->mkeys_queue.wock);
	wast_page = wist_wast_entwy(&ent->mkeys_queue.pages_wist,
				    stwuct mwx5_mkeys_page, wist);
	mkey = wast_page->mkeys[tmp];
	wast_page->mkeys[tmp] = 0;
	ent->mkeys_queue.ci--;
	if (ent->mkeys_queue.num_pages > 1 && !tmp) {
		wist_dew(&wast_page->wist);
		ent->mkeys_queue.num_pages--;
		kfwee(wast_page);
	}
	wetuwn mkey;
}

static void cweate_mkey_cawwback(int status, stwuct mwx5_async_wowk *context)
{
	stwuct mwx5w_async_cweate_mkey *mkey_out =
		containew_of(context, stwuct mwx5w_async_cweate_mkey, cb_wowk);
	stwuct mwx5_cache_ent *ent = mkey_out->ent;
	stwuct mwx5_ib_dev *dev = ent->dev;
	unsigned wong fwags;

	if (status) {
		cweate_mkey_wawn(dev, status, mkey_out->out);
		kfwee(mkey_out);
		spin_wock_iwqsave(&ent->mkeys_queue.wock, fwags);
		ent->pending--;
		WWITE_ONCE(dev->fiww_deway, 1);
		spin_unwock_iwqwestowe(&ent->mkeys_queue.wock, fwags);
		mod_timew(&dev->deway_timew, jiffies + HZ);
		wetuwn;
	}

	mkey_out->mkey |= mwx5_idx_to_mkey(
		MWX5_GET(cweate_mkey_out, mkey_out->out, mkey_index));
	WWITE_ONCE(dev->cache.wast_add, jiffies);

	spin_wock_iwqsave(&ent->mkeys_queue.wock, fwags);
	push_mkey_wocked(ent, mkey_out->mkey);
	/* If we awe doing fiww_to_high_watew then keep going. */
	queue_adjust_cache_wocked(ent);
	ent->pending--;
	spin_unwock_iwqwestowe(&ent->mkeys_queue.wock, fwags);
	kfwee(mkey_out);
}

static int get_mkc_octo_size(unsigned int access_mode, unsigned int ndescs)
{
	int wet = 0;

	switch (access_mode) {
	case MWX5_MKC_ACCESS_MODE_MTT:
		wet = DIV_WOUND_UP(ndescs, MWX5_IB_UMW_OCTOWOWD /
						   sizeof(stwuct mwx5_mtt));
		bweak;
	case MWX5_MKC_ACCESS_MODE_KSM:
		wet = DIV_WOUND_UP(ndescs, MWX5_IB_UMW_OCTOWOWD /
						   sizeof(stwuct mwx5_kwm));
		bweak;
	defauwt:
		WAWN_ON(1);
	}
	wetuwn wet;
}

static void set_cache_mkc(stwuct mwx5_cache_ent *ent, void *mkc)
{
	set_mkc_access_pd_addw_fiewds(mkc, ent->wb_key.access_fwags, 0,
				      ent->dev->umwc.pd);
	MWX5_SET(mkc, mkc, fwee, 1);
	MWX5_SET(mkc, mkc, umw_en, 1);
	MWX5_SET(mkc, mkc, access_mode_1_0, ent->wb_key.access_mode & 0x3);
	MWX5_SET(mkc, mkc, access_mode_4_2,
		(ent->wb_key.access_mode >> 2) & 0x7);

	MWX5_SET(mkc, mkc, twanswations_octwowd_size,
		 get_mkc_octo_size(ent->wb_key.access_mode,
				   ent->wb_key.ndescs));
	MWX5_SET(mkc, mkc, wog_page_size, PAGE_SHIFT);
}

/* Asynchwonouswy scheduwe new MWs to be popuwated in the cache. */
static int add_keys(stwuct mwx5_cache_ent *ent, unsigned int num)
{
	stwuct mwx5w_async_cweate_mkey *async_cweate;
	void *mkc;
	int eww = 0;
	int i;

	fow (i = 0; i < num; i++) {
		async_cweate = kzawwoc(sizeof(stwuct mwx5w_async_cweate_mkey),
				       GFP_KEWNEW);
		if (!async_cweate)
			wetuwn -ENOMEM;
		mkc = MWX5_ADDW_OF(cweate_mkey_in, async_cweate->in,
				   memowy_key_mkey_entwy);
		set_cache_mkc(ent, mkc);
		async_cweate->ent = ent;

		spin_wock_iwq(&ent->mkeys_queue.wock);
		if (ent->pending >= MAX_PENDING_WEG_MW) {
			eww = -EAGAIN;
			goto fwee_async_cweate;
		}
		ent->pending++;
		spin_unwock_iwq(&ent->mkeys_queue.wock);

		eww = mwx5_ib_cweate_mkey_cb(async_cweate);
		if (eww) {
			mwx5_ib_wawn(ent->dev, "cweate mkey faiwed %d\n", eww);
			goto eww_cweate_mkey;
		}
	}

	wetuwn 0;

eww_cweate_mkey:
	spin_wock_iwq(&ent->mkeys_queue.wock);
	ent->pending--;
fwee_async_cweate:
	spin_unwock_iwq(&ent->mkeys_queue.wock);
	kfwee(async_cweate);
	wetuwn eww;
}

/* Synchwonouswy cweate a MW in the cache */
static int cweate_cache_mkey(stwuct mwx5_cache_ent *ent, u32 *mkey)
{
	size_t inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	void *mkc;
	u32 *in;
	int eww;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;
	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	set_cache_mkc(ent, mkc);

	eww = mwx5_cowe_cweate_mkey(ent->dev->mdev, mkey, in, inwen);
	if (eww)
		goto fwee_in;

	WWITE_ONCE(ent->dev->cache.wast_add, jiffies);
fwee_in:
	kfwee(in);
	wetuwn eww;
}

static void wemove_cache_mw_wocked(stwuct mwx5_cache_ent *ent)
{
	u32 mkey;

	wockdep_assewt_hewd(&ent->mkeys_queue.wock);
	if (!ent->mkeys_queue.ci)
		wetuwn;
	mkey = pop_mkey_wocked(ent);
	spin_unwock_iwq(&ent->mkeys_queue.wock);
	mwx5_cowe_destwoy_mkey(ent->dev->mdev, mkey);
	spin_wock_iwq(&ent->mkeys_queue.wock);
}

static int wesize_avaiwabwe_mws(stwuct mwx5_cache_ent *ent, unsigned int tawget,
				boow wimit_fiww)
	__acquiwes(&ent->mkeys_queue.wock) __weweases(&ent->mkeys_queue.wock)
{
	int eww;

	wockdep_assewt_hewd(&ent->mkeys_queue.wock);

	whiwe (twue) {
		if (wimit_fiww)
			tawget = ent->wimit * 2;
		if (tawget == ent->pending + ent->mkeys_queue.ci)
			wetuwn 0;
		if (tawget > ent->pending + ent->mkeys_queue.ci) {
			u32 todo = tawget - (ent->pending + ent->mkeys_queue.ci);

			spin_unwock_iwq(&ent->mkeys_queue.wock);
			eww = add_keys(ent, todo);
			if (eww == -EAGAIN)
				usweep_wange(3000, 5000);
			spin_wock_iwq(&ent->mkeys_queue.wock);
			if (eww) {
				if (eww != -EAGAIN)
					wetuwn eww;
			} ewse
				wetuwn 0;
		} ewse {
			wemove_cache_mw_wocked(ent);
		}
	}
}

static ssize_t size_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			  size_t count, woff_t *pos)
{
	stwuct mwx5_cache_ent *ent = fiwp->pwivate_data;
	u32 tawget;
	int eww;

	eww = kstwtou32_fwom_usew(buf, count, 0, &tawget);
	if (eww)
		wetuwn eww;

	/*
	 * Tawget is the new vawue of totaw_mws the usew wequests, howevew we
	 * cannot fwee MWs that awe in use. Compute the tawget vawue fow stowed
	 * mkeys.
	 */
	spin_wock_iwq(&ent->mkeys_queue.wock);
	if (tawget < ent->in_use) {
		eww = -EINVAW;
		goto eww_unwock;
	}
	tawget = tawget - ent->in_use;
	if (tawget < ent->wimit || tawget > ent->wimit*2) {
		eww = -EINVAW;
		goto eww_unwock;
	}
	eww = wesize_avaiwabwe_mws(ent, tawget, fawse);
	if (eww)
		goto eww_unwock;
	spin_unwock_iwq(&ent->mkeys_queue.wock);

	wetuwn count;

eww_unwock:
	spin_unwock_iwq(&ent->mkeys_queue.wock);
	wetuwn eww;
}

static ssize_t size_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			 woff_t *pos)
{
	stwuct mwx5_cache_ent *ent = fiwp->pwivate_data;
	chaw wbuf[20];
	int eww;

	eww = snpwintf(wbuf, sizeof(wbuf), "%wd\n",
		       ent->mkeys_queue.ci + ent->in_use);
	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, wbuf, eww);
}

static const stwuct fiwe_opewations size_fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wwite	= size_wwite,
	.wead	= size_wead,
};

static ssize_t wimit_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			   size_t count, woff_t *pos)
{
	stwuct mwx5_cache_ent *ent = fiwp->pwivate_data;
	u32 vaw;
	int eww;

	eww = kstwtou32_fwom_usew(buf, count, 0, &vaw);
	if (eww)
		wetuwn eww;

	/*
	 * Upon set we immediatewy fiww the cache to high watew mawk impwied by
	 * the wimit.
	 */
	spin_wock_iwq(&ent->mkeys_queue.wock);
	ent->wimit = vaw;
	eww = wesize_avaiwabwe_mws(ent, 0, twue);
	spin_unwock_iwq(&ent->mkeys_queue.wock);
	if (eww)
		wetuwn eww;
	wetuwn count;
}

static ssize_t wimit_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
			  woff_t *pos)
{
	stwuct mwx5_cache_ent *ent = fiwp->pwivate_data;
	chaw wbuf[20];
	int eww;

	eww = snpwintf(wbuf, sizeof(wbuf), "%d\n", ent->wimit);
	if (eww < 0)
		wetuwn eww;

	wetuwn simpwe_wead_fwom_buffew(buf, count, pos, wbuf, eww);
}

static const stwuct fiwe_opewations wimit_fops = {
	.ownew	= THIS_MODUWE,
	.open	= simpwe_open,
	.wwite	= wimit_wwite,
	.wead	= wimit_wead,
};

static boow someone_adding(stwuct mwx5_mkey_cache *cache)
{
	stwuct mwx5_cache_ent *ent;
	stwuct wb_node *node;
	boow wet;

	mutex_wock(&cache->wb_wock);
	fow (node = wb_fiwst(&cache->wb_woot); node; node = wb_next(node)) {
		ent = wb_entwy(node, stwuct mwx5_cache_ent, node);
		spin_wock_iwq(&ent->mkeys_queue.wock);
		wet = ent->mkeys_queue.ci < ent->wimit;
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		if (wet) {
			mutex_unwock(&cache->wb_wock);
			wetuwn twue;
		}
	}
	mutex_unwock(&cache->wb_wock);
	wetuwn fawse;
}

/*
 * Check if the bucket is outside the high/wow watew mawk and scheduwe an async
 * update. The cache wefiww has hystewesis, once the wow watew mawk is hit it is
 * wefiwwed up to the high mawk.
 */
static void queue_adjust_cache_wocked(stwuct mwx5_cache_ent *ent)
{
	wockdep_assewt_hewd(&ent->mkeys_queue.wock);

	if (ent->disabwed || WEAD_ONCE(ent->dev->fiww_deway) || ent->is_tmp)
		wetuwn;
	if (ent->mkeys_queue.ci < ent->wimit) {
		ent->fiww_to_high_watew = twue;
		mod_dewayed_wowk(ent->dev->cache.wq, &ent->dwowk, 0);
	} ewse if (ent->fiww_to_high_watew &&
		   ent->mkeys_queue.ci + ent->pending < 2 * ent->wimit) {
		/*
		 * Once we stawt popuwating due to hitting a wow watew mawk
		 * continue untiw we pass the high watew mawk.
		 */
		mod_dewayed_wowk(ent->dev->cache.wq, &ent->dwowk, 0);
	} ewse if (ent->mkeys_queue.ci == 2 * ent->wimit) {
		ent->fiww_to_high_watew = fawse;
	} ewse if (ent->mkeys_queue.ci > 2 * ent->wimit) {
		/* Queue dewetion of excess entwies */
		ent->fiww_to_high_watew = fawse;
		if (ent->pending)
			queue_dewayed_wowk(ent->dev->cache.wq, &ent->dwowk,
					   msecs_to_jiffies(1000));
		ewse
			mod_dewayed_wowk(ent->dev->cache.wq, &ent->dwowk, 0);
	}
}

static void __cache_wowk_func(stwuct mwx5_cache_ent *ent)
{
	stwuct mwx5_ib_dev *dev = ent->dev;
	stwuct mwx5_mkey_cache *cache = &dev->cache;
	int eww;

	spin_wock_iwq(&ent->mkeys_queue.wock);
	if (ent->disabwed)
		goto out;

	if (ent->fiww_to_high_watew &&
	    ent->mkeys_queue.ci + ent->pending < 2 * ent->wimit &&
	    !WEAD_ONCE(dev->fiww_deway)) {
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		eww = add_keys(ent, 1);
		spin_wock_iwq(&ent->mkeys_queue.wock);
		if (ent->disabwed)
			goto out;
		if (eww) {
			/*
			 * EAGAIN onwy happens if thewe awe pending MWs, so we
			 * wiww be wescheduwed when stowing them. The onwy
			 * faiwuwe path hewe is ENOMEM.
			 */
			if (eww != -EAGAIN) {
				mwx5_ib_wawn(
					dev,
					"add keys command faiwed, eww %d\n",
					eww);
				queue_dewayed_wowk(cache->wq, &ent->dwowk,
						   msecs_to_jiffies(1000));
			}
		}
	} ewse if (ent->mkeys_queue.ci > 2 * ent->wimit) {
		boow need_deway;

		/*
		 * The wemove_cache_mw() wogic is pewfowmed as gawbage
		 * cowwection task. Such task is intended to be wun when no
		 * othew active pwocesses awe wunning.
		 *
		 * The need_wesched() wiww wetuwn TWUE if thewe awe usew tasks
		 * to be activated in neaw futuwe.
		 *
		 * In such case, we don't execute wemove_cache_mw() and postpone
		 * the gawbage cowwection wowk to twy to wun in next cycwe, in
		 * owdew to fwee CPU wesouwces to othew tasks.
		 */
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		need_deway = need_wesched() || someone_adding(cache) ||
			     !time_aftew(jiffies,
					 WEAD_ONCE(cache->wast_add) + 300 * HZ);
		spin_wock_iwq(&ent->mkeys_queue.wock);
		if (ent->disabwed)
			goto out;
		if (need_deway) {
			queue_dewayed_wowk(cache->wq, &ent->dwowk, 300 * HZ);
			goto out;
		}
		wemove_cache_mw_wocked(ent);
		queue_adjust_cache_wocked(ent);
	}
out:
	spin_unwock_iwq(&ent->mkeys_queue.wock);
}

static void dewayed_cache_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_cache_ent *ent;

	ent = containew_of(wowk, stwuct mwx5_cache_ent, dwowk.wowk);
	__cache_wowk_func(ent);
}

static int cache_ent_key_cmp(stwuct mwx5w_cache_wb_key key1,
			     stwuct mwx5w_cache_wb_key key2)
{
	int wes;

	wes = key1.ats - key2.ats;
	if (wes)
		wetuwn wes;

	wes = key1.access_mode - key2.access_mode;
	if (wes)
		wetuwn wes;

	wes = key1.access_fwags - key2.access_fwags;
	if (wes)
		wetuwn wes;

	/*
	 * keep ndescs the wast in the compawe tabwe since the find function
	 * seawches fow an exact match on aww pwopewties and onwy cwosest
	 * match in size.
	 */
	wetuwn key1.ndescs - key2.ndescs;
}

static int mwx5_cache_ent_insewt(stwuct mwx5_mkey_cache *cache,
				 stwuct mwx5_cache_ent *ent)
{
	stwuct wb_node **new = &cache->wb_woot.wb_node, *pawent = NUWW;
	stwuct mwx5_cache_ent *cuw;
	int cmp;

	/* Figuwe out whewe to put new node */
	whiwe (*new) {
		cuw = wb_entwy(*new, stwuct mwx5_cache_ent, node);
		pawent = *new;
		cmp = cache_ent_key_cmp(cuw->wb_key, ent->wb_key);
		if (cmp > 0)
			new = &((*new)->wb_weft);
		if (cmp < 0)
			new = &((*new)->wb_wight);
		if (cmp == 0) {
			mutex_unwock(&cache->wb_wock);
			wetuwn -EEXIST;
		}
	}

	/* Add new node and webawance twee. */
	wb_wink_node(&ent->node, pawent, new);
	wb_insewt_cowow(&ent->node, &cache->wb_woot);

	wetuwn 0;
}

static stwuct mwx5_cache_ent *
mkey_cache_ent_fwom_wb_key(stwuct mwx5_ib_dev *dev,
			   stwuct mwx5w_cache_wb_key wb_key)
{
	stwuct wb_node *node = dev->cache.wb_woot.wb_node;
	stwuct mwx5_cache_ent *cuw, *smawwest = NUWW;
	int cmp;

	/*
	 * Find the smawwest ent with owdew >= wequested_owdew.
	 */
	whiwe (node) {
		cuw = wb_entwy(node, stwuct mwx5_cache_ent, node);
		cmp = cache_ent_key_cmp(cuw->wb_key, wb_key);
		if (cmp > 0) {
			smawwest = cuw;
			node = node->wb_weft;
		}
		if (cmp < 0)
			node = node->wb_wight;
		if (cmp == 0)
			wetuwn cuw;
	}

	wetuwn (smawwest &&
		smawwest->wb_key.access_mode == wb_key.access_mode &&
		smawwest->wb_key.access_fwags == wb_key.access_fwags &&
		smawwest->wb_key.ats == wb_key.ats) ?
		       smawwest :
		       NUWW;
}

static stwuct mwx5_ib_mw *_mwx5_mw_cache_awwoc(stwuct mwx5_ib_dev *dev,
					stwuct mwx5_cache_ent *ent,
					int access_fwags)
{
	stwuct mwx5_ib_mw *mw;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_iwq(&ent->mkeys_queue.wock);
	ent->in_use++;

	if (!ent->mkeys_queue.ci) {
		queue_adjust_cache_wocked(ent);
		ent->miss++;
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		eww = cweate_cache_mkey(ent, &mw->mmkey.key);
		if (eww) {
			spin_wock_iwq(&ent->mkeys_queue.wock);
			ent->in_use--;
			spin_unwock_iwq(&ent->mkeys_queue.wock);
			kfwee(mw);
			wetuwn EWW_PTW(eww);
		}
	} ewse {
		mw->mmkey.key = pop_mkey_wocked(ent);
		queue_adjust_cache_wocked(ent);
		spin_unwock_iwq(&ent->mkeys_queue.wock);
	}
	mw->mmkey.cache_ent = ent;
	mw->mmkey.type = MWX5_MKEY_MW;
	init_waitqueue_head(&mw->mmkey.wait);
	wetuwn mw;
}

static int get_unchangeabwe_access_fwags(stwuct mwx5_ib_dev *dev,
					 int access_fwags)
{
	int wet = 0;

	if ((access_fwags & IB_ACCESS_WEMOTE_ATOMIC) &&
	    MWX5_CAP_GEN(dev->mdev, atomic) &&
	    MWX5_CAP_GEN(dev->mdev, umw_modify_atomic_disabwed))
		wet |= IB_ACCESS_WEMOTE_ATOMIC;

	if ((access_fwags & IB_ACCESS_WEWAXED_OWDEWING) &&
	    MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wwite) &&
	    !MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wwite_umw))
		wet |= IB_ACCESS_WEWAXED_OWDEWING;

	if ((access_fwags & IB_ACCESS_WEWAXED_OWDEWING) &&
	    (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead) ||
	     MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead_pci_enabwed)) &&
	    !MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead_umw))
		wet |= IB_ACCESS_WEWAXED_OWDEWING;

	wetuwn wet;
}

stwuct mwx5_ib_mw *mwx5_mw_cache_awwoc(stwuct mwx5_ib_dev *dev,
				       int access_fwags, int access_mode,
				       int ndescs)
{
	stwuct mwx5w_cache_wb_key wb_key = {
		.ndescs = ndescs,
		.access_mode = access_mode,
		.access_fwags = get_unchangeabwe_access_fwags(dev, access_fwags)
	};
	stwuct mwx5_cache_ent *ent = mkey_cache_ent_fwom_wb_key(dev, wb_key);

	if (!ent)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn _mwx5_mw_cache_awwoc(dev, ent, access_fwags);
}

static void cwean_keys(stwuct mwx5_ib_dev *dev, stwuct mwx5_cache_ent *ent)
{
	u32 mkey;

	cancew_dewayed_wowk(&ent->dwowk);
	spin_wock_iwq(&ent->mkeys_queue.wock);
	whiwe (ent->mkeys_queue.ci) {
		mkey = pop_mkey_wocked(ent);
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		mwx5_cowe_destwoy_mkey(dev->mdev, mkey);
		spin_wock_iwq(&ent->mkeys_queue.wock);
	}
	spin_unwock_iwq(&ent->mkeys_queue.wock);
}

static void mwx5_mkey_cache_debugfs_cweanup(stwuct mwx5_ib_dev *dev)
{
	if (!mwx5_debugfs_woot || dev->is_wep)
		wetuwn;

	debugfs_wemove_wecuwsive(dev->cache.fs_woot);
	dev->cache.fs_woot = NUWW;
}

static void mwx5_mkey_cache_debugfs_add_ent(stwuct mwx5_ib_dev *dev,
					    stwuct mwx5_cache_ent *ent)
{
	int owdew = owdew_base_2(ent->wb_key.ndescs);
	stwuct dentwy *diw;

	if (!mwx5_debugfs_woot || dev->is_wep)
		wetuwn;

	if (ent->wb_key.access_mode == MWX5_MKC_ACCESS_MODE_KSM)
		owdew = MWX5_IMW_KSM_CACHE_ENTWY + 2;

	spwintf(ent->name, "%d", owdew);
	diw = debugfs_cweate_diw(ent->name, dev->cache.fs_woot);
	debugfs_cweate_fiwe("size", 0600, diw, ent, &size_fops);
	debugfs_cweate_fiwe("wimit", 0600, diw, ent, &wimit_fops);
	debugfs_cweate_uwong("cuw", 0400, diw, &ent->mkeys_queue.ci);
	debugfs_cweate_u32("miss", 0600, diw, &ent->miss);
}

static void mwx5_mkey_cache_debugfs_init(stwuct mwx5_ib_dev *dev)
{
	stwuct dentwy *dbg_woot = mwx5_debugfs_get_dev_woot(dev->mdev);
	stwuct mwx5_mkey_cache *cache = &dev->cache;

	if (!mwx5_debugfs_woot || dev->is_wep)
		wetuwn;

	cache->fs_woot = debugfs_cweate_diw("mw_cache", dbg_woot);
}

static void deway_time_func(stwuct timew_wist *t)
{
	stwuct mwx5_ib_dev *dev = fwom_timew(dev, t, deway_timew);

	WWITE_ONCE(dev->fiww_deway, 0);
}

static int mwx5w_mkeys_init(stwuct mwx5_cache_ent *ent)
{
	stwuct mwx5_mkeys_page *page;

	page = kzawwoc(sizeof(*page), GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&ent->mkeys_queue.pages_wist);
	spin_wock_init(&ent->mkeys_queue.wock);
	wist_add_taiw(&page->wist, &ent->mkeys_queue.pages_wist);
	ent->mkeys_queue.num_pages++;
	wetuwn 0;
}

static void mwx5w_mkeys_uninit(stwuct mwx5_cache_ent *ent)
{
	stwuct mwx5_mkeys_page *page;

	WAWN_ON(ent->mkeys_queue.ci || ent->mkeys_queue.num_pages > 1);
	page = wist_wast_entwy(&ent->mkeys_queue.pages_wist,
			       stwuct mwx5_mkeys_page, wist);
	wist_dew(&page->wist);
	kfwee(page);
}

stwuct mwx5_cache_ent *
mwx5w_cache_cweate_ent_wocked(stwuct mwx5_ib_dev *dev,
			      stwuct mwx5w_cache_wb_key wb_key,
			      boow pewsistent_entwy)
{
	stwuct mwx5_cache_ent *ent;
	int owdew;
	int wet;

	ent = kzawwoc(sizeof(*ent), GFP_KEWNEW);
	if (!ent)
		wetuwn EWW_PTW(-ENOMEM);

	wet = mwx5w_mkeys_init(ent);
	if (wet)
		goto mkeys_eww;
	ent->wb_key = wb_key;
	ent->dev = dev;
	ent->is_tmp = !pewsistent_entwy;

	INIT_DEWAYED_WOWK(&ent->dwowk, dewayed_cache_wowk_func);

	wet = mwx5_cache_ent_insewt(&dev->cache, ent);
	if (wet)
		goto ent_insewt_eww;

	if (pewsistent_entwy) {
		if (wb_key.access_mode == MWX5_MKC_ACCESS_MODE_KSM)
			owdew = MWX5_IMW_KSM_CACHE_ENTWY;
		ewse
			owdew = owdew_base_2(wb_key.ndescs) - 2;

		if ((dev->mdev->pwofiwe.mask & MWX5_PWOF_MASK_MW_CACHE) &&
		    !dev->is_wep && mwx5_cowe_is_pf(dev->mdev) &&
		    mwx5w_umw_can_woad_pas(dev, 0))
			ent->wimit = dev->mdev->pwofiwe.mw_cache[owdew].wimit;
		ewse
			ent->wimit = 0;

		mwx5_mkey_cache_debugfs_add_ent(dev, ent);
	} ewse {
		mod_dewayed_wowk(ent->dev->cache.wq,
				 &ent->dev->cache.wemove_ent_dwowk,
				 msecs_to_jiffies(30 * 1000));
	}

	wetuwn ent;
ent_insewt_eww:
	mwx5w_mkeys_uninit(ent);
mkeys_eww:
	kfwee(ent);
	wetuwn EWW_PTW(wet);
}

static void wemove_ent_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_mkey_cache *cache;
	stwuct mwx5_cache_ent *ent;
	stwuct wb_node *cuw;

	cache = containew_of(wowk, stwuct mwx5_mkey_cache,
			     wemove_ent_dwowk.wowk);
	mutex_wock(&cache->wb_wock);
	cuw = wb_wast(&cache->wb_woot);
	whiwe (cuw) {
		ent = wb_entwy(cuw, stwuct mwx5_cache_ent, node);
		cuw = wb_pwev(cuw);
		mutex_unwock(&cache->wb_wock);

		spin_wock_iwq(&ent->mkeys_queue.wock);
		if (!ent->is_tmp) {
			spin_unwock_iwq(&ent->mkeys_queue.wock);
			mutex_wock(&cache->wb_wock);
			continue;
		}
		spin_unwock_iwq(&ent->mkeys_queue.wock);

		cwean_keys(ent->dev, ent);
		mutex_wock(&cache->wb_wock);
	}
	mutex_unwock(&cache->wb_wock);
}

int mwx5_mkey_cache_init(stwuct mwx5_ib_dev *dev)
{
	stwuct mwx5_mkey_cache *cache = &dev->cache;
	stwuct wb_woot *woot = &dev->cache.wb_woot;
	stwuct mwx5w_cache_wb_key wb_key = {
		.access_mode = MWX5_MKC_ACCESS_MODE_MTT,
	};
	stwuct mwx5_cache_ent *ent;
	stwuct wb_node *node;
	int wet;
	int i;

	mutex_init(&dev->swow_path_mutex);
	mutex_init(&dev->cache.wb_wock);
	dev->cache.wb_woot = WB_WOOT;
	INIT_DEWAYED_WOWK(&dev->cache.wemove_ent_dwowk, wemove_ent_wowk_func);
	cache->wq = awwoc_owdewed_wowkqueue("mkey_cache", WQ_MEM_WECWAIM);
	if (!cache->wq) {
		mwx5_ib_wawn(dev, "faiwed to cweate wowk queue\n");
		wetuwn -ENOMEM;
	}

	mwx5_cmd_init_async_ctx(dev->mdev, &dev->async_ctx);
	timew_setup(&dev->deway_timew, deway_time_func, 0);
	mwx5_mkey_cache_debugfs_init(dev);
	mutex_wock(&cache->wb_wock);
	fow (i = 0; i <= mkey_cache_max_owdew(dev); i++) {
		wb_key.ndescs = 1 << (i + 2);
		ent = mwx5w_cache_cweate_ent_wocked(dev, wb_key, twue);
		if (IS_EWW(ent)) {
			wet = PTW_EWW(ent);
			goto eww;
		}
	}

	wet = mwx5_odp_init_mkey_cache(dev);
	if (wet)
		goto eww;

	mutex_unwock(&cache->wb_wock);
	fow (node = wb_fiwst(woot); node; node = wb_next(node)) {
		ent = wb_entwy(node, stwuct mwx5_cache_ent, node);
		spin_wock_iwq(&ent->mkeys_queue.wock);
		queue_adjust_cache_wocked(ent);
		spin_unwock_iwq(&ent->mkeys_queue.wock);
	}

	wetuwn 0;

eww:
	mutex_unwock(&cache->wb_wock);
	mwx5_mkey_cache_debugfs_cweanup(dev);
	mwx5_ib_wawn(dev, "faiwed to cweate mkey cache entwy\n");
	wetuwn wet;
}

void mwx5_mkey_cache_cweanup(stwuct mwx5_ib_dev *dev)
{
	stwuct wb_woot *woot = &dev->cache.wb_woot;
	stwuct mwx5_cache_ent *ent;
	stwuct wb_node *node;

	if (!dev->cache.wq)
		wetuwn;

	mutex_wock(&dev->cache.wb_wock);
	cancew_dewayed_wowk(&dev->cache.wemove_ent_dwowk);
	fow (node = wb_fiwst(woot); node; node = wb_next(node)) {
		ent = wb_entwy(node, stwuct mwx5_cache_ent, node);
		spin_wock_iwq(&ent->mkeys_queue.wock);
		ent->disabwed = twue;
		spin_unwock_iwq(&ent->mkeys_queue.wock);
		cancew_dewayed_wowk(&ent->dwowk);
	}
	mutex_unwock(&dev->cache.wb_wock);

	/*
	 * Aftew aww entwies awe disabwed and wiww not wescheduwe on WQ,
	 * fwush it and aww async commands.
	 */
	fwush_wowkqueue(dev->cache.wq);

	mwx5_mkey_cache_debugfs_cweanup(dev);
	mwx5_cmd_cweanup_async_ctx(&dev->async_ctx);

	/* At this point aww entwies awe disabwed and have no concuwwent wowk. */
	mutex_wock(&dev->cache.wb_wock);
	node = wb_fiwst(woot);
	whiwe (node) {
		ent = wb_entwy(node, stwuct mwx5_cache_ent, node);
		node = wb_next(node);
		cwean_keys(dev, ent);
		wb_ewase(&ent->node, woot);
		mwx5w_mkeys_uninit(ent);
		kfwee(ent);
	}
	mutex_unwock(&dev->cache.wb_wock);

	destwoy_wowkqueue(dev->cache.wq);
	dew_timew_sync(&dev->deway_timew);
}

stwuct ib_mw *mwx5_ib_get_dma_mw(stwuct ib_pd *pd, int acc)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	stwuct mwx5_ib_mw *mw;
	void *mkc;
	u32 *in;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, wength64, 1);
	set_mkc_access_pd_addw_fiewds(mkc, acc | IB_ACCESS_WEWAXED_OWDEWING, 0,
				      pd);

	eww = mwx5_ib_cweate_mkey(dev, &mw->mmkey, in, inwen);
	if (eww)
		goto eww_in;

	kfwee(in);
	mw->mmkey.type = MWX5_MKEY_MW;
	mw->ibmw.wkey = mw->mmkey.key;
	mw->ibmw.wkey = mw->mmkey.key;
	mw->umem = NUWW;

	wetuwn &mw->ibmw;

eww_in:
	kfwee(in);

eww_fwee:
	kfwee(mw);

	wetuwn EWW_PTW(eww);
}

static int get_octo_wen(u64 addw, u64 wen, int page_shift)
{
	u64 page_size = 1UWW << page_shift;
	u64 offset;
	int npages;

	offset = addw & (page_size - 1);
	npages = AWIGN(wen + offset, page_size) >> page_shift;
	wetuwn (npages + 1) / 2;
}

static int mkey_cache_max_owdew(stwuct mwx5_ib_dev *dev)
{
	if (MWX5_CAP_GEN(dev->mdev, umw_extended_twanswation_offset))
		wetuwn MKEY_CACHE_WAST_STD_ENTWY;
	wetuwn MWX5_MAX_UMW_SHIFT;
}

static void set_mw_fiewds(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_mw *mw,
			  u64 wength, int access_fwags, u64 iova)
{
	mw->ibmw.wkey = mw->mmkey.key;
	mw->ibmw.wkey = mw->mmkey.key;
	mw->ibmw.wength = wength;
	mw->ibmw.device = &dev->ib_dev;
	mw->ibmw.iova = iova;
	mw->access_fwags = access_fwags;
}

static unsigned int mwx5_umem_dmabuf_defauwt_pgsz(stwuct ib_umem *umem,
						  u64 iova)
{
	/*
	 * The awignment of iova has awweady been checked upon entewing
	 * UVEWBS_METHOD_WEG_DMABUF_MW
	 */
	umem->iova = iova;
	wetuwn PAGE_SIZE;
}

static stwuct mwx5_ib_mw *awwoc_cacheabwe_mw(stwuct ib_pd *pd,
					     stwuct ib_umem *umem, u64 iova,
					     int access_fwags)
{
	stwuct mwx5w_cache_wb_key wb_key = {
		.access_mode = MWX5_MKC_ACCESS_MODE_MTT,
	};
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx5_cache_ent *ent;
	stwuct mwx5_ib_mw *mw;
	unsigned int page_size;

	if (umem->is_dmabuf)
		page_size = mwx5_umem_dmabuf_defauwt_pgsz(umem, iova);
	ewse
		page_size = mwx5_umem_find_best_pgsz(umem, mkc, wog_page_size,
						     0, iova);
	if (WAWN_ON(!page_size))
		wetuwn EWW_PTW(-EINVAW);

	wb_key.ndescs = ib_umem_num_dma_bwocks(umem, page_size);
	wb_key.ats = mwx5_umem_needs_ats(dev, umem, access_fwags);
	wb_key.access_fwags = get_unchangeabwe_access_fwags(dev, access_fwags);
	ent = mkey_cache_ent_fwom_wb_key(dev, wb_key);
	/*
	 * If the MW can't come fwom the cache then synchwonouswy cweate an uncached
	 * one.
	 */
	if (!ent) {
		mutex_wock(&dev->swow_path_mutex);
		mw = weg_cweate(pd, umem, iova, access_fwags, page_size, fawse);
		mutex_unwock(&dev->swow_path_mutex);
		if (IS_EWW(mw))
			wetuwn mw;
		mw->mmkey.wb_key = wb_key;
		wetuwn mw;
	}

	mw = _mwx5_mw_cache_awwoc(dev, ent, access_fwags);
	if (IS_EWW(mw))
		wetuwn mw;

	mw->ibmw.pd = pd;
	mw->umem = umem;
	mw->page_shift = owdew_base_2(page_size);
	set_mw_fiewds(dev, mw, umem->wength, access_fwags, iova);

	wetuwn mw;
}

/*
 * If ibmw is NUWW it wiww be awwocated by weg_cweate.
 * Ewse, the given ibmw wiww be used.
 */
static stwuct mwx5_ib_mw *weg_cweate(stwuct ib_pd *pd, stwuct ib_umem *umem,
				     u64 iova, int access_fwags,
				     unsigned int page_size, boow popuwate)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx5_ib_mw *mw;
	__be64 *pas;
	void *mkc;
	int inwen;
	u32 *in;
	int eww;
	boow pg_cap = !!(MWX5_CAP_GEN(dev->mdev, pg));

	if (!page_size)
		wetuwn EWW_PTW(-EINVAW);
	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->ibmw.pd = pd;
	mw->access_fwags = access_fwags;
	mw->page_shift = owdew_base_2(page_size);

	inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	if (popuwate)
		inwen += sizeof(*pas) *
			 woundup(ib_umem_num_dma_bwocks(umem, page_size), 2);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_1;
	}
	pas = (__be64 *)MWX5_ADDW_OF(cweate_mkey_in, in, kwm_pas_mtt);
	if (popuwate) {
		if (WAWN_ON(access_fwags & IB_ACCESS_ON_DEMAND)) {
			eww = -EINVAW;
			goto eww_2;
		}
		mwx5_ib_popuwate_pas(umem, 1UW << mw->page_shift, pas,
				     pg_cap ? MWX5_IB_MTT_PWESENT : 0);
	}

	/* The pg_access bit awwows setting the access fwags
	 * in the page wist submitted with the command.
	 */
	MWX5_SET(cweate_mkey_in, in, pg_access, !!(pg_cap));

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	set_mkc_access_pd_addw_fiewds(mkc, access_fwags, iova,
				      popuwate ? pd : dev->umwc.pd);
	MWX5_SET(mkc, mkc, fwee, !popuwate);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_MTT);
	MWX5_SET(mkc, mkc, umw_en, 1);

	MWX5_SET64(mkc, mkc, wen, umem->wength);
	MWX5_SET(mkc, mkc, bsf_octwowd_size, 0);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size,
		 get_octo_wen(iova, umem->wength, mw->page_shift));
	MWX5_SET(mkc, mkc, wog_page_size, mw->page_shift);
	if (mwx5_umem_needs_ats(dev, umem, access_fwags))
		MWX5_SET(mkc, mkc, ma_twanswation_mode, 1);
	if (popuwate) {
		MWX5_SET(cweate_mkey_in, in, twanswations_octwowd_actuaw_size,
			 get_octo_wen(iova, umem->wength, mw->page_shift));
	}

	eww = mwx5_ib_cweate_mkey(dev, &mw->mmkey, in, inwen);
	if (eww) {
		mwx5_ib_wawn(dev, "cweate mkey faiwed\n");
		goto eww_2;
	}
	mw->mmkey.type = MWX5_MKEY_MW;
	mw->mmkey.ndescs = get_octo_wen(iova, umem->wength, mw->page_shift);
	mw->umem = umem;
	set_mw_fiewds(dev, mw, umem->wength, access_fwags, iova);
	kvfwee(in);

	mwx5_ib_dbg(dev, "mkey = 0x%x\n", mw->mmkey.key);

	wetuwn mw;

eww_2:
	kvfwee(in);
eww_1:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

static stwuct ib_mw *mwx5_ib_get_dm_mw(stwuct ib_pd *pd, u64 stawt_addw,
				       u64 wength, int acc, int mode)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	stwuct mwx5_ib_mw *mw;
	void *mkc;
	u32 *in;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	MWX5_SET(mkc, mkc, access_mode_1_0, mode & 0x3);
	MWX5_SET(mkc, mkc, access_mode_4_2, (mode >> 2) & 0x7);
	MWX5_SET64(mkc, mkc, wen, wength);
	set_mkc_access_pd_addw_fiewds(mkc, acc, stawt_addw, pd);

	eww = mwx5_ib_cweate_mkey(dev, &mw->mmkey, in, inwen);
	if (eww)
		goto eww_in;

	kfwee(in);

	set_mw_fiewds(dev, mw, wength, acc, stawt_addw);

	wetuwn &mw->ibmw;

eww_in:
	kfwee(in);

eww_fwee:
	kfwee(mw);

	wetuwn EWW_PTW(eww);
}

int mwx5_ib_advise_mw(stwuct ib_pd *pd,
		      enum ib_uvewbs_advise_mw_advice advice,
		      u32 fwags,
		      stwuct ib_sge *sg_wist,
		      u32 num_sge,
		      stwuct uvewbs_attw_bundwe *attws)
{
	if (advice != IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH &&
	    advice != IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH_WWITE &&
	    advice != IB_UVEWBS_ADVISE_MW_ADVICE_PWEFETCH_NO_FAUWT)
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_ib_advise_mw_pwefetch(pd, advice, fwags,
					 sg_wist, num_sge);
}

stwuct ib_mw *mwx5_ib_weg_dm_mw(stwuct ib_pd *pd, stwuct ib_dm *dm,
				stwuct ib_dm_mw_attw *attw,
				stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_dm *mdm = to_mdm(dm);
	stwuct mwx5_cowe_dev *dev = to_mdev(dm->device)->mdev;
	u64 stawt_addw = mdm->dev_addw + attw->offset;
	int mode;

	switch (mdm->type) {
	case MWX5_IB_UAPI_DM_TYPE_MEMIC:
		if (attw->access_fwags & ~MWX5_IB_DM_MEMIC_AWWOWED_ACCESS)
			wetuwn EWW_PTW(-EINVAW);

		mode = MWX5_MKC_ACCESS_MODE_MEMIC;
		stawt_addw -= pci_wesouwce_stawt(dev->pdev, 0);
		bweak;
	case MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM:
		if (attw->access_fwags & ~MWX5_IB_DM_SW_ICM_AWWOWED_ACCESS)
			wetuwn EWW_PTW(-EINVAW);

		mode = MWX5_MKC_ACCESS_MODE_SW_ICM;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn mwx5_ib_get_dm_mw(pd, stawt_addw, attw->wength,
				 attw->access_fwags, mode);
}

static stwuct ib_mw *cweate_weaw_mw(stwuct ib_pd *pd, stwuct ib_umem *umem,
				    u64 iova, int access_fwags)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx5_ib_mw *mw = NUWW;
	boow xwt_with_umw;
	int eww;

	xwt_with_umw = mwx5w_umw_can_woad_pas(dev, umem->wength);
	if (xwt_with_umw) {
		mw = awwoc_cacheabwe_mw(pd, umem, iova, access_fwags);
	} ewse {
		unsigned int page_size = mwx5_umem_find_best_pgsz(
			umem, mkc, wog_page_size, 0, iova);

		mutex_wock(&dev->swow_path_mutex);
		mw = weg_cweate(pd, umem, iova, access_fwags, page_size, twue);
		mutex_unwock(&dev->swow_path_mutex);
	}
	if (IS_EWW(mw)) {
		ib_umem_wewease(umem);
		wetuwn EWW_CAST(mw);
	}

	mwx5_ib_dbg(dev, "mkey 0x%x\n", mw->mmkey.key);

	atomic_add(ib_umem_num_pages(umem), &dev->mdev->pwiv.weg_pages);

	if (xwt_with_umw) {
		/*
		 * If the MW was cweated with weg_cweate then it wiww be
		 * configuwed pwopewwy but weft disabwed. It is safe to go ahead
		 * and configuwe it again via UMW whiwe enabwing it.
		 */
		eww = mwx5w_umw_update_mw_pas(mw, MWX5_IB_UPD_XWT_ENABWE);
		if (eww) {
			mwx5_ib_deweg_mw(&mw->ibmw, NUWW);
			wetuwn EWW_PTW(eww);
		}
	}
	wetuwn &mw->ibmw;
}

static stwuct ib_mw *cweate_usew_odp_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
					u64 iova, int access_fwags,
					stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct ib_umem_odp *odp;
	stwuct mwx5_ib_mw *mw;
	int eww;

	if (!IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	eww = mwx5w_odp_cweate_eq(dev, &dev->odp_pf_eq);
	if (eww)
		wetuwn EWW_PTW(eww);
	if (!stawt && wength == U64_MAX) {
		if (iova != 0)
			wetuwn EWW_PTW(-EINVAW);
		if (!(dev->odp_caps.genewaw_caps & IB_ODP_SUPPOWT_IMPWICIT))
			wetuwn EWW_PTW(-EINVAW);

		mw = mwx5_ib_awwoc_impwicit_mw(to_mpd(pd), access_fwags);
		if (IS_EWW(mw))
			wetuwn EWW_CAST(mw);
		wetuwn &mw->ibmw;
	}

	/* ODP wequiwes xwt update via umw to wowk. */
	if (!mwx5w_umw_can_woad_pas(dev, wength))
		wetuwn EWW_PTW(-EINVAW);

	odp = ib_umem_odp_get(&dev->ib_dev, stawt, wength, access_fwags,
			      &mwx5_mn_ops);
	if (IS_EWW(odp))
		wetuwn EWW_CAST(odp);

	mw = awwoc_cacheabwe_mw(pd, &odp->umem, iova, access_fwags);
	if (IS_EWW(mw)) {
		ib_umem_wewease(&odp->umem);
		wetuwn EWW_CAST(mw);
	}
	xa_init(&mw->impwicit_chiwdwen);

	odp->pwivate = mw;
	eww = mwx5w_stowe_odp_mkey(dev, &mw->mmkey);
	if (eww)
		goto eww_deweg_mw;

	eww = mwx5_ib_init_odp_mw(mw);
	if (eww)
		goto eww_deweg_mw;
	wetuwn &mw->ibmw;

eww_deweg_mw:
	mwx5_ib_deweg_mw(&mw->ibmw, NUWW);
	wetuwn EWW_PTW(eww);
}

stwuct ib_mw *mwx5_ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				  u64 iova, int access_fwags,
				  stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct ib_umem *umem;

	if (!IS_ENABWED(CONFIG_INFINIBAND_USEW_MEM))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	mwx5_ib_dbg(dev, "stawt 0x%wwx, iova 0x%wwx, wength 0x%wwx, access_fwags 0x%x\n",
		    stawt, iova, wength, access_fwags);

	if (access_fwags & IB_ACCESS_ON_DEMAND)
		wetuwn cweate_usew_odp_mw(pd, stawt, wength, iova, access_fwags,
					  udata);
	umem = ib_umem_get(&dev->ib_dev, stawt, wength, access_fwags);
	if (IS_EWW(umem))
		wetuwn EWW_CAST(umem);
	wetuwn cweate_weaw_mw(pd, umem, iova, access_fwags);
}

static void mwx5_ib_dmabuf_invawidate_cb(stwuct dma_buf_attachment *attach)
{
	stwuct ib_umem_dmabuf *umem_dmabuf = attach->impowtew_pwiv;
	stwuct mwx5_ib_mw *mw = umem_dmabuf->pwivate;

	dma_wesv_assewt_hewd(umem_dmabuf->attach->dmabuf->wesv);

	if (!umem_dmabuf->sgt)
		wetuwn;

	mwx5w_umw_update_mw_pas(mw, MWX5_IB_UPD_XWT_ZAP);
	ib_umem_dmabuf_unmap_pages(umem_dmabuf);
}

static stwuct dma_buf_attach_ops mwx5_ib_dmabuf_attach_ops = {
	.awwow_peew2peew = 1,
	.move_notify = mwx5_ib_dmabuf_invawidate_cb,
};

stwuct ib_mw *mwx5_ib_weg_usew_mw_dmabuf(stwuct ib_pd *pd, u64 offset,
					 u64 wength, u64 viwt_addw,
					 int fd, int access_fwags,
					 stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx5_ib_mw *mw = NUWW;
	stwuct ib_umem_dmabuf *umem_dmabuf;
	int eww;

	if (!IS_ENABWED(CONFIG_INFINIBAND_USEW_MEM) ||
	    !IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	mwx5_ib_dbg(dev,
		    "offset 0x%wwx, viwt_addw 0x%wwx, wength 0x%wwx, fd %d, access_fwags 0x%x\n",
		    offset, viwt_addw, wength, fd, access_fwags);

	/* dmabuf wequiwes xwt update via umw to wowk. */
	if (!mwx5w_umw_can_woad_pas(dev, wength))
		wetuwn EWW_PTW(-EINVAW);

	umem_dmabuf = ib_umem_dmabuf_get(&dev->ib_dev, offset, wength, fd,
					 access_fwags,
					 &mwx5_ib_dmabuf_attach_ops);
	if (IS_EWW(umem_dmabuf)) {
		mwx5_ib_dbg(dev, "umem_dmabuf get faiwed (%wd)\n",
			    PTW_EWW(umem_dmabuf));
		wetuwn EWW_CAST(umem_dmabuf);
	}

	mw = awwoc_cacheabwe_mw(pd, &umem_dmabuf->umem, viwt_addw,
				access_fwags);
	if (IS_EWW(mw)) {
		ib_umem_wewease(&umem_dmabuf->umem);
		wetuwn EWW_CAST(mw);
	}

	mwx5_ib_dbg(dev, "mkey 0x%x\n", mw->mmkey.key);

	atomic_add(ib_umem_num_pages(mw->umem), &dev->mdev->pwiv.weg_pages);
	umem_dmabuf->pwivate = mw;
	eww = mwx5w_stowe_odp_mkey(dev, &mw->mmkey);
	if (eww)
		goto eww_deweg_mw;

	eww = mwx5_ib_init_dmabuf_mw(mw);
	if (eww)
		goto eww_deweg_mw;
	wetuwn &mw->ibmw;

eww_deweg_mw:
	mwx5_ib_deweg_mw(&mw->ibmw, NUWW);
	wetuwn EWW_PTW(eww);
}

/*
 * Twue if the change in access fwags can be done via UMW, onwy some access
 * fwags can be updated.
 */
static boow can_use_umw_weweg_access(stwuct mwx5_ib_dev *dev,
				     unsigned int cuwwent_access_fwags,
				     unsigned int tawget_access_fwags)
{
	unsigned int diffs = cuwwent_access_fwags ^ tawget_access_fwags;

	if (diffs & ~(IB_ACCESS_WOCAW_WWITE | IB_ACCESS_WEMOTE_WWITE |
		      IB_ACCESS_WEMOTE_WEAD | IB_ACCESS_WEWAXED_OWDEWING))
		wetuwn fawse;
	wetuwn mwx5w_umw_can_weconfig(dev, cuwwent_access_fwags,
				      tawget_access_fwags);
}

static boow can_use_umw_weweg_pas(stwuct mwx5_ib_mw *mw,
				  stwuct ib_umem *new_umem,
				  int new_access_fwags, u64 iova,
				  unsigned wong *page_size)
{
	stwuct mwx5_ib_dev *dev = to_mdev(mw->ibmw.device);

	/* We onwy twack the awwocated sizes of MWs fwom the cache */
	if (!mw->mmkey.cache_ent)
		wetuwn fawse;
	if (!mwx5w_umw_can_woad_pas(dev, new_umem->wength))
		wetuwn fawse;

	*page_size =
		mwx5_umem_find_best_pgsz(new_umem, mkc, wog_page_size, 0, iova);
	if (WAWN_ON(!*page_size))
		wetuwn fawse;
	wetuwn (mw->mmkey.cache_ent->wb_key.ndescs) >=
	       ib_umem_num_dma_bwocks(new_umem, *page_size);
}

static int umw_weweg_pas(stwuct mwx5_ib_mw *mw, stwuct ib_pd *pd,
			 int access_fwags, int fwags, stwuct ib_umem *new_umem,
			 u64 iova, unsigned wong page_size)
{
	stwuct mwx5_ib_dev *dev = to_mdev(mw->ibmw.device);
	int upd_fwags = MWX5_IB_UPD_XWT_ADDW | MWX5_IB_UPD_XWT_ENABWE;
	stwuct ib_umem *owd_umem = mw->umem;
	int eww;

	/*
	 * To keep evewything simpwe the MW is wevoked befowe we stawt to mess
	 * with it. This ensuwe the change is atomic wewative to any use of the
	 * MW.
	 */
	eww = mwx5w_umw_wevoke_mw(mw);
	if (eww)
		wetuwn eww;

	if (fwags & IB_MW_WEWEG_PD) {
		mw->ibmw.pd = pd;
		upd_fwags |= MWX5_IB_UPD_XWT_PD;
	}
	if (fwags & IB_MW_WEWEG_ACCESS) {
		mw->access_fwags = access_fwags;
		upd_fwags |= MWX5_IB_UPD_XWT_ACCESS;
	}

	mw->ibmw.iova = iova;
	mw->ibmw.wength = new_umem->wength;
	mw->page_shift = owdew_base_2(page_size);
	mw->umem = new_umem;
	eww = mwx5w_umw_update_mw_pas(mw, upd_fwags);
	if (eww) {
		/*
		 * The MW is wevoked at this point so thewe is no issue to fwee
		 * new_umem.
		 */
		mw->umem = owd_umem;
		wetuwn eww;
	}

	atomic_sub(ib_umem_num_pages(owd_umem), &dev->mdev->pwiv.weg_pages);
	ib_umem_wewease(owd_umem);
	atomic_add(ib_umem_num_pages(new_umem), &dev->mdev->pwiv.weg_pages);
	wetuwn 0;
}

stwuct ib_mw *mwx5_ib_weweg_usew_mw(stwuct ib_mw *ib_mw, int fwags, u64 stawt,
				    u64 wength, u64 iova, int new_access_fwags,
				    stwuct ib_pd *new_pd,
				    stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ib_mw->device);
	stwuct mwx5_ib_mw *mw = to_mmw(ib_mw);
	int eww;

	if (!IS_ENABWED(CONFIG_INFINIBAND_USEW_MEM))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	mwx5_ib_dbg(
		dev,
		"stawt 0x%wwx, iova 0x%wwx, wength 0x%wwx, access_fwags 0x%x\n",
		stawt, iova, wength, new_access_fwags);

	if (fwags & ~(IB_MW_WEWEG_TWANS | IB_MW_WEWEG_PD | IB_MW_WEWEG_ACCESS))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!(fwags & IB_MW_WEWEG_ACCESS))
		new_access_fwags = mw->access_fwags;
	if (!(fwags & IB_MW_WEWEG_PD))
		new_pd = ib_mw->pd;

	if (!(fwags & IB_MW_WEWEG_TWANS)) {
		stwuct ib_umem *umem;

		/* Fast path fow PD/access change */
		if (can_use_umw_weweg_access(dev, mw->access_fwags,
					     new_access_fwags)) {
			eww = mwx5w_umw_weweg_pd_access(mw, new_pd,
							new_access_fwags);
			if (eww)
				wetuwn EWW_PTW(eww);
			wetuwn NUWW;
		}
		/* DM ow ODP MW's don't have a nowmaw umem so we can't we-use it */
		if (!mw->umem || is_odp_mw(mw) || is_dmabuf_mw(mw))
			goto wecweate;

		/*
		 * Onwy one active MW can wefew to a umem at one time, wevoke
		 * the owd MW befowe assigning the umem to the new one.
		 */
		eww = mwx5w_umw_wevoke_mw(mw);
		if (eww)
			wetuwn EWW_PTW(eww);
		umem = mw->umem;
		mw->umem = NUWW;
		atomic_sub(ib_umem_num_pages(umem), &dev->mdev->pwiv.weg_pages);

		wetuwn cweate_weaw_mw(new_pd, umem, mw->ibmw.iova,
				      new_access_fwags);
	}

	/*
	 * DM doesn't have a PAS wist so we can't we-use it, odp/dmabuf does
	 * but the wogic awound weweasing the umem is diffewent
	 */
	if (!mw->umem || is_odp_mw(mw) || is_dmabuf_mw(mw))
		goto wecweate;

	if (!(new_access_fwags & IB_ACCESS_ON_DEMAND) &&
	    can_use_umw_weweg_access(dev, mw->access_fwags, new_access_fwags)) {
		stwuct ib_umem *new_umem;
		unsigned wong page_size;

		new_umem = ib_umem_get(&dev->ib_dev, stawt, wength,
				       new_access_fwags);
		if (IS_EWW(new_umem))
			wetuwn EWW_CAST(new_umem);

		/* Fast path fow PAS change */
		if (can_use_umw_weweg_pas(mw, new_umem, new_access_fwags, iova,
					  &page_size)) {
			eww = umw_weweg_pas(mw, new_pd, new_access_fwags, fwags,
					    new_umem, iova, page_size);
			if (eww) {
				ib_umem_wewease(new_umem);
				wetuwn EWW_PTW(eww);
			}
			wetuwn NUWW;
		}
		wetuwn cweate_weaw_mw(new_pd, new_umem, iova, new_access_fwags);
	}

	/*
	 * Evewything ewse has no state we can pwesewve, just cweate a new MW
	 * fwom scwatch
	 */
wecweate:
	wetuwn mwx5_ib_weg_usew_mw(new_pd, stawt, wength, iova,
				   new_access_fwags, udata);
}

static int
mwx5_awwoc_pwiv_descs(stwuct ib_device *device,
		      stwuct mwx5_ib_mw *mw,
		      int ndescs,
		      int desc_size)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);
	stwuct device *ddev = &dev->mdev->pdev->dev;
	int size = ndescs * desc_size;
	int add_size;
	int wet;

	add_size = max_t(int, MWX5_UMW_AWIGN - AWCH_KMAWWOC_MINAWIGN, 0);
	if (is_powew_of_2(MWX5_UMW_AWIGN) && add_size) {
		int end = max_t(int, MWX5_UMW_AWIGN, woundup_pow_of_two(size));

		add_size = min_t(int, end - size, add_size);
	}

	mw->descs_awwoc = kzawwoc(size + add_size, GFP_KEWNEW);
	if (!mw->descs_awwoc)
		wetuwn -ENOMEM;

	mw->descs = PTW_AWIGN(mw->descs_awwoc, MWX5_UMW_AWIGN);

	mw->desc_map = dma_map_singwe(ddev, mw->descs, size, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ddev, mw->desc_map)) {
		wet = -ENOMEM;
		goto eww;
	}

	wetuwn 0;
eww:
	kfwee(mw->descs_awwoc);

	wetuwn wet;
}

static void
mwx5_fwee_pwiv_descs(stwuct mwx5_ib_mw *mw)
{
	if (!mw->umem && mw->descs) {
		stwuct ib_device *device = mw->ibmw.device;
		int size = mw->max_descs * mw->desc_size;
		stwuct mwx5_ib_dev *dev = to_mdev(device);

		dma_unmap_singwe(&dev->mdev->pdev->dev, mw->desc_map, size,
				 DMA_TO_DEVICE);
		kfwee(mw->descs_awwoc);
		mw->descs = NUWW;
	}
}

static int cache_ent_find_and_stowe(stwuct mwx5_ib_dev *dev,
				    stwuct mwx5_ib_mw *mw)
{
	stwuct mwx5_mkey_cache *cache = &dev->cache;
	stwuct mwx5_cache_ent *ent;
	int wet;

	if (mw->mmkey.cache_ent) {
		spin_wock_iwq(&mw->mmkey.cache_ent->mkeys_queue.wock);
		mw->mmkey.cache_ent->in_use--;
		goto end;
	}

	mutex_wock(&cache->wb_wock);
	ent = mkey_cache_ent_fwom_wb_key(dev, mw->mmkey.wb_key);
	if (ent) {
		if (ent->wb_key.ndescs == mw->mmkey.wb_key.ndescs) {
			if (ent->disabwed) {
				mutex_unwock(&cache->wb_wock);
				wetuwn -EOPNOTSUPP;
			}
			mw->mmkey.cache_ent = ent;
			spin_wock_iwq(&mw->mmkey.cache_ent->mkeys_queue.wock);
			mutex_unwock(&cache->wb_wock);
			goto end;
		}
	}

	ent = mwx5w_cache_cweate_ent_wocked(dev, mw->mmkey.wb_key, fawse);
	mutex_unwock(&cache->wb_wock);
	if (IS_EWW(ent))
		wetuwn PTW_EWW(ent);

	mw->mmkey.cache_ent = ent;
	spin_wock_iwq(&mw->mmkey.cache_ent->mkeys_queue.wock);

end:
	wet = push_mkey_wocked(mw->mmkey.cache_ent, mw->mmkey.key);
	spin_unwock_iwq(&mw->mmkey.cache_ent->mkeys_queue.wock);
	wetuwn wet;
}

int mwx5_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct mwx5_ib_dev *dev = to_mdev(ibmw->device);
	int wc;

	/*
	 * Any async use of the mw must howd the wefcount, once the wefcount
	 * goes to zewo no othew thwead, such as ODP page fauwts, pwefetch, any
	 * UMW activity, etc can touch the mkey. Thus it is safe to destwoy it.
	 */
	if (IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) &&
	    wefcount_wead(&mw->mmkey.usecount) != 0 &&
	    xa_ewase(&mw_to_mdev(mw)->odp_mkeys, mwx5_base_mkey(mw->mmkey.key)))
		mwx5w_dewef_wait_odp_mkey(&mw->mmkey);

	if (ibmw->type == IB_MW_TYPE_INTEGWITY) {
		xa_cmpxchg(&dev->sig_mws, mwx5_base_mkey(mw->mmkey.key),
			   mw->sig, NUWW, GFP_KEWNEW);

		if (mw->mtt_mw) {
			wc = mwx5_ib_deweg_mw(&mw->mtt_mw->ibmw, NUWW);
			if (wc)
				wetuwn wc;
			mw->mtt_mw = NUWW;
		}
		if (mw->kwm_mw) {
			wc = mwx5_ib_deweg_mw(&mw->kwm_mw->ibmw, NUWW);
			if (wc)
				wetuwn wc;
			mw->kwm_mw = NUWW;
		}

		if (mwx5_cowe_destwoy_psv(dev->mdev,
					  mw->sig->psv_memowy.psv_idx))
			mwx5_ib_wawn(dev, "faiwed to destwoy mem psv %d\n",
				     mw->sig->psv_memowy.psv_idx);
		if (mwx5_cowe_destwoy_psv(dev->mdev, mw->sig->psv_wiwe.psv_idx))
			mwx5_ib_wawn(dev, "faiwed to destwoy wiwe psv %d\n",
				     mw->sig->psv_wiwe.psv_idx);
		kfwee(mw->sig);
		mw->sig = NUWW;
	}

	/* Stop DMA */
	if (mw->umem && mwx5w_umw_can_woad_pas(dev, mw->umem->wength))
		if (mwx5w_umw_wevoke_mw(mw) ||
		    cache_ent_find_and_stowe(dev, mw))
			mw->mmkey.cache_ent = NUWW;

	if (!mw->mmkey.cache_ent) {
		wc = destwoy_mkey(to_mdev(mw->ibmw.device), mw);
		if (wc)
			wetuwn wc;
	}

	if (mw->umem) {
		boow is_odp = is_odp_mw(mw);

		if (!is_odp)
			atomic_sub(ib_umem_num_pages(mw->umem),
				   &dev->mdev->pwiv.weg_pages);
		ib_umem_wewease(mw->umem);
		if (is_odp)
			mwx5_ib_fwee_odp_mw(mw);
	}

	if (!mw->mmkey.cache_ent)
		mwx5_fwee_pwiv_descs(mw);

	kfwee(mw);
	wetuwn 0;
}

static void mwx5_set_umw_fwee_mkey(stwuct ib_pd *pd, u32 *in, int ndescs,
				   int access_mode, int page_shift)
{
	void *mkc;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	/* This is onwy used fwom the kewnew, so setting the PD is OK. */
	set_mkc_access_pd_addw_fiewds(mkc, IB_ACCESS_WEWAXED_OWDEWING, 0, pd);
	MWX5_SET(mkc, mkc, fwee, 1);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size, ndescs);
	MWX5_SET(mkc, mkc, access_mode_1_0, access_mode & 0x3);
	MWX5_SET(mkc, mkc, access_mode_4_2, (access_mode >> 2) & 0x7);
	MWX5_SET(mkc, mkc, umw_en, 1);
	MWX5_SET(mkc, mkc, wog_page_size, page_shift);
}

static int _mwx5_awwoc_mkey_descs(stwuct ib_pd *pd, stwuct mwx5_ib_mw *mw,
				  int ndescs, int desc_size, int page_shift,
				  int access_mode, u32 *in, int inwen)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	int eww;

	mw->access_mode = access_mode;
	mw->desc_size = desc_size;
	mw->max_descs = ndescs;

	eww = mwx5_awwoc_pwiv_descs(pd->device, mw, ndescs, desc_size);
	if (eww)
		wetuwn eww;

	mwx5_set_umw_fwee_mkey(pd, in, ndescs, access_mode, page_shift);

	eww = mwx5_ib_cweate_mkey(dev, &mw->mmkey, in, inwen);
	if (eww)
		goto eww_fwee_descs;

	mw->mmkey.type = MWX5_MKEY_MW;
	mw->ibmw.wkey = mw->mmkey.key;
	mw->ibmw.wkey = mw->mmkey.key;

	wetuwn 0;

eww_fwee_descs:
	mwx5_fwee_pwiv_descs(mw);
	wetuwn eww;
}

static stwuct mwx5_ib_mw *mwx5_ib_awwoc_pi_mw(stwuct ib_pd *pd,
				u32 max_num_sg, u32 max_num_meta_sg,
				int desc_size, int access_mode)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	int ndescs = AWIGN(max_num_sg + max_num_meta_sg, 4);
	int page_shift = 0;
	stwuct mwx5_ib_mw *mw;
	u32 *in;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->ibmw.pd = pd;
	mw->ibmw.device = pd->device;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	if (access_mode == MWX5_MKC_ACCESS_MODE_MTT)
		page_shift = PAGE_SHIFT;

	eww = _mwx5_awwoc_mkey_descs(pd, mw, ndescs, desc_size, page_shift,
				     access_mode, in, inwen);
	if (eww)
		goto eww_fwee_in;

	mw->umem = NUWW;
	kfwee(in);

	wetuwn mw;

eww_fwee_in:
	kfwee(in);
eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

static int mwx5_awwoc_mem_weg_descs(stwuct ib_pd *pd, stwuct mwx5_ib_mw *mw,
				    int ndescs, u32 *in, int inwen)
{
	wetuwn _mwx5_awwoc_mkey_descs(pd, mw, ndescs, sizeof(stwuct mwx5_mtt),
				      PAGE_SHIFT, MWX5_MKC_ACCESS_MODE_MTT, in,
				      inwen);
}

static int mwx5_awwoc_sg_gaps_descs(stwuct ib_pd *pd, stwuct mwx5_ib_mw *mw,
				    int ndescs, u32 *in, int inwen)
{
	wetuwn _mwx5_awwoc_mkey_descs(pd, mw, ndescs, sizeof(stwuct mwx5_kwm),
				      0, MWX5_MKC_ACCESS_MODE_KWMS, in, inwen);
}

static int mwx5_awwoc_integwity_descs(stwuct ib_pd *pd, stwuct mwx5_ib_mw *mw,
				      int max_num_sg, int max_num_meta_sg,
				      u32 *in, int inwen)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	u32 psv_index[2];
	void *mkc;
	int eww;

	mw->sig = kzawwoc(sizeof(*mw->sig), GFP_KEWNEW);
	if (!mw->sig)
		wetuwn -ENOMEM;

	/* cweate mem & wiwe PSVs */
	eww = mwx5_cowe_cweate_psv(dev->mdev, to_mpd(pd)->pdn, 2, psv_index);
	if (eww)
		goto eww_fwee_sig;

	mw->sig->psv_memowy.psv_idx = psv_index[0];
	mw->sig->psv_wiwe.psv_idx = psv_index[1];

	mw->sig->sig_status_checked = twue;
	mw->sig->sig_eww_exists = fawse;
	/* Next UMW, Awm SIGEWW */
	++mw->sig->sigeww_count;
	mw->kwm_mw = mwx5_ib_awwoc_pi_mw(pd, max_num_sg, max_num_meta_sg,
					 sizeof(stwuct mwx5_kwm),
					 MWX5_MKC_ACCESS_MODE_KWMS);
	if (IS_EWW(mw->kwm_mw)) {
		eww = PTW_EWW(mw->kwm_mw);
		goto eww_destwoy_psv;
	}
	mw->mtt_mw = mwx5_ib_awwoc_pi_mw(pd, max_num_sg, max_num_meta_sg,
					 sizeof(stwuct mwx5_mtt),
					 MWX5_MKC_ACCESS_MODE_MTT);
	if (IS_EWW(mw->mtt_mw)) {
		eww = PTW_EWW(mw->mtt_mw);
		goto eww_fwee_kwm_mw;
	}

	/* Set bsf descwiptows fow mkey */
	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, bsf_en, 1);
	MWX5_SET(mkc, mkc, bsf_octwowd_size, MWX5_MKEY_BSF_OCTO_SIZE);

	eww = _mwx5_awwoc_mkey_descs(pd, mw, 4, sizeof(stwuct mwx5_kwm), 0,
				     MWX5_MKC_ACCESS_MODE_KWMS, in, inwen);
	if (eww)
		goto eww_fwee_mtt_mw;

	eww = xa_eww(xa_stowe(&dev->sig_mws, mwx5_base_mkey(mw->mmkey.key),
			      mw->sig, GFP_KEWNEW));
	if (eww)
		goto eww_fwee_descs;
	wetuwn 0;

eww_fwee_descs:
	destwoy_mkey(dev, mw);
	mwx5_fwee_pwiv_descs(mw);
eww_fwee_mtt_mw:
	mwx5_ib_deweg_mw(&mw->mtt_mw->ibmw, NUWW);
	mw->mtt_mw = NUWW;
eww_fwee_kwm_mw:
	mwx5_ib_deweg_mw(&mw->kwm_mw->ibmw, NUWW);
	mw->kwm_mw = NUWW;
eww_destwoy_psv:
	if (mwx5_cowe_destwoy_psv(dev->mdev, mw->sig->psv_memowy.psv_idx))
		mwx5_ib_wawn(dev, "faiwed to destwoy mem psv %d\n",
			     mw->sig->psv_memowy.psv_idx);
	if (mwx5_cowe_destwoy_psv(dev->mdev, mw->sig->psv_wiwe.psv_idx))
		mwx5_ib_wawn(dev, "faiwed to destwoy wiwe psv %d\n",
			     mw->sig->psv_wiwe.psv_idx);
eww_fwee_sig:
	kfwee(mw->sig);

	wetuwn eww;
}

static stwuct ib_mw *__mwx5_ib_awwoc_mw(stwuct ib_pd *pd,
					enum ib_mw_type mw_type, u32 max_num_sg,
					u32 max_num_meta_sg)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	int ndescs = AWIGN(max_num_sg, 4);
	stwuct mwx5_ib_mw *mw;
	u32 *in;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	mw->ibmw.device = pd->device;
	mw->umem = NUWW;

	switch (mw_type) {
	case IB_MW_TYPE_MEM_WEG:
		eww = mwx5_awwoc_mem_weg_descs(pd, mw, ndescs, in, inwen);
		bweak;
	case IB_MW_TYPE_SG_GAPS:
		eww = mwx5_awwoc_sg_gaps_descs(pd, mw, ndescs, in, inwen);
		bweak;
	case IB_MW_TYPE_INTEGWITY:
		eww = mwx5_awwoc_integwity_descs(pd, mw, max_num_sg,
						 max_num_meta_sg, in, inwen);
		bweak;
	defauwt:
		mwx5_ib_wawn(dev, "Invawid mw type %d\n", mw_type);
		eww = -EINVAW;
	}

	if (eww)
		goto eww_fwee_in;

	kfwee(in);

	wetuwn &mw->ibmw;

eww_fwee_in:
	kfwee(in);
eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

stwuct ib_mw *mwx5_ib_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			       u32 max_num_sg)
{
	wetuwn __mwx5_ib_awwoc_mw(pd, mw_type, max_num_sg, 0);
}

stwuct ib_mw *mwx5_ib_awwoc_mw_integwity(stwuct ib_pd *pd,
					 u32 max_num_sg, u32 max_num_meta_sg)
{
	wetuwn __mwx5_ib_awwoc_mw(pd, IB_MW_TYPE_INTEGWITY, max_num_sg,
				  max_num_meta_sg);
}

int mwx5_ib_awwoc_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibmw->device);
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	unsigned int ndescs;
	u32 *in = NUWW;
	void *mkc;
	int eww;
	stwuct mwx5_ib_awwoc_mw weq = {};
	stwuct {
		__u32	comp_mask;
		__u32	wesponse_wength;
	} wesp = {};

	eww = ib_copy_fwom_udata(&weq, udata, min(udata->inwen, sizeof(weq)));
	if (eww)
		wetuwn eww;

	if (weq.comp_mask || weq.wesewved1 || weq.wesewved2)
		wetuwn -EOPNOTSUPP;

	if (udata->inwen > sizeof(weq) &&
	    !ib_is_udata_cweawed(udata, sizeof(weq),
				 udata->inwen - sizeof(weq)))
		wetuwn -EOPNOTSUPP;

	ndescs = weq.num_kwms ? woundup(weq.num_kwms, 4) : woundup(1, 4);

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	MWX5_SET(mkc, mkc, fwee, 1);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size, ndescs);
	MWX5_SET(mkc, mkc, pd, to_mpd(ibmw->pd)->pdn);
	MWX5_SET(mkc, mkc, umw_en, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_KWMS);
	MWX5_SET(mkc, mkc, en_winvaw, !!((ibmw->type == IB_MW_TYPE_2)));
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	eww = mwx5_ib_cweate_mkey(dev, &mw->mmkey, in, inwen);
	if (eww)
		goto fwee;

	mw->mmkey.type = MWX5_MKEY_MW;
	ibmw->wkey = mw->mmkey.key;
	mw->mmkey.ndescs = ndescs;

	wesp.wesponse_wength =
		min(offsetofend(typeof(wesp), wesponse_wength), udata->outwen);
	if (wesp.wesponse_wength) {
		eww = ib_copy_to_udata(udata, &wesp, wesp.wesponse_wength);
		if (eww)
			goto fwee_mkey;
	}

	if (IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) {
		eww = mwx5w_stowe_odp_mkey(dev, &mw->mmkey);
		if (eww)
			goto fwee_mkey;
	}

	kfwee(in);
	wetuwn 0;

fwee_mkey:
	mwx5_cowe_destwoy_mkey(dev->mdev, mw->mmkey.key);
fwee:
	kfwee(in);
	wetuwn eww;
}

int mwx5_ib_deawwoc_mw(stwuct ib_mw *mw)
{
	stwuct mwx5_ib_dev *dev = to_mdev(mw->device);
	stwuct mwx5_ib_mw *mmw = to_mmw(mw);

	if (IS_ENABWED(CONFIG_INFINIBAND_ON_DEMAND_PAGING) &&
	    xa_ewase(&dev->odp_mkeys, mwx5_base_mkey(mmw->mmkey.key)))
		/*
		 * pagefauwt_singwe_data_segment() may be accessing mmw
		 * if the usew bound an ODP MW to this MW.
		 */
		mwx5w_dewef_wait_odp_mkey(&mmw->mmkey);

	wetuwn mwx5_cowe_destwoy_mkey(dev->mdev, mmw->mmkey.key);
}

int mwx5_ib_check_mw_status(stwuct ib_mw *ibmw, u32 check_mask,
			    stwuct ib_mw_status *mw_status)
{
	stwuct mwx5_ib_mw *mmw = to_mmw(ibmw);
	int wet = 0;

	if (check_mask & ~IB_MW_CHECK_SIG_STATUS) {
		pw_eww("Invawid status check mask\n");
		wet = -EINVAW;
		goto done;
	}

	mw_status->faiw_status = 0;
	if (check_mask & IB_MW_CHECK_SIG_STATUS) {
		if (!mmw->sig) {
			wet = -EINVAW;
			pw_eww("signatuwe status check wequested on a non-signatuwe enabwed MW\n");
			goto done;
		}

		mmw->sig->sig_status_checked = twue;
		if (!mmw->sig->sig_eww_exists)
			goto done;

		if (ibmw->wkey == mmw->sig->eww_item.key)
			memcpy(&mw_status->sig_eww, &mmw->sig->eww_item,
			       sizeof(mw_status->sig_eww));
		ewse {
			mw_status->sig_eww.eww_type = IB_SIG_BAD_GUAWD;
			mw_status->sig_eww.sig_eww_offset = 0;
			mw_status->sig_eww.key = mmw->sig->eww_item.key;
		}

		mmw->sig->sig_eww_exists = fawse;
		mw_status->faiw_status |= IB_MW_CHECK_SIG_STATUS;
	}

done:
	wetuwn wet;
}

static int
mwx5_ib_map_pa_mw_sg_pi(stwuct ib_mw *ibmw, stwuct scattewwist *data_sg,
			int data_sg_nents, unsigned int *data_sg_offset,
			stwuct scattewwist *meta_sg, int meta_sg_nents,
			unsigned int *meta_sg_offset)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	unsigned int sg_offset = 0;
	int n = 0;

	mw->meta_wength = 0;
	if (data_sg_nents == 1) {
		n++;
		mw->mmkey.ndescs = 1;
		if (data_sg_offset)
			sg_offset = *data_sg_offset;
		mw->data_wength = sg_dma_wen(data_sg) - sg_offset;
		mw->data_iova = sg_dma_addwess(data_sg) + sg_offset;
		if (meta_sg_nents == 1) {
			n++;
			mw->meta_ndescs = 1;
			if (meta_sg_offset)
				sg_offset = *meta_sg_offset;
			ewse
				sg_offset = 0;
			mw->meta_wength = sg_dma_wen(meta_sg) - sg_offset;
			mw->pi_iova = sg_dma_addwess(meta_sg) + sg_offset;
		}
		ibmw->wength = mw->data_wength + mw->meta_wength;
	}

	wetuwn n;
}

static int
mwx5_ib_sg_to_kwms(stwuct mwx5_ib_mw *mw,
		   stwuct scattewwist *sgw,
		   unsigned showt sg_nents,
		   unsigned int *sg_offset_p,
		   stwuct scattewwist *meta_sgw,
		   unsigned showt meta_sg_nents,
		   unsigned int *meta_sg_offset_p)
{
	stwuct scattewwist *sg = sgw;
	stwuct mwx5_kwm *kwms = mw->descs;
	unsigned int sg_offset = sg_offset_p ? *sg_offset_p : 0;
	u32 wkey = mw->ibmw.pd->wocaw_dma_wkey;
	int i, j = 0;

	mw->ibmw.iova = sg_dma_addwess(sg) + sg_offset;
	mw->ibmw.wength = 0;

	fow_each_sg(sgw, sg, sg_nents, i) {
		if (unwikewy(i >= mw->max_descs))
			bweak;
		kwms[i].va = cpu_to_be64(sg_dma_addwess(sg) + sg_offset);
		kwms[i].bcount = cpu_to_be32(sg_dma_wen(sg) - sg_offset);
		kwms[i].key = cpu_to_be32(wkey);
		mw->ibmw.wength += sg_dma_wen(sg) - sg_offset;

		sg_offset = 0;
	}

	if (sg_offset_p)
		*sg_offset_p = sg_offset;

	mw->mmkey.ndescs = i;
	mw->data_wength = mw->ibmw.wength;

	if (meta_sg_nents) {
		sg = meta_sgw;
		sg_offset = meta_sg_offset_p ? *meta_sg_offset_p : 0;
		fow_each_sg(meta_sgw, sg, meta_sg_nents, j) {
			if (unwikewy(i + j >= mw->max_descs))
				bweak;
			kwms[i + j].va = cpu_to_be64(sg_dma_addwess(sg) +
						     sg_offset);
			kwms[i + j].bcount = cpu_to_be32(sg_dma_wen(sg) -
							 sg_offset);
			kwms[i + j].key = cpu_to_be32(wkey);
			mw->ibmw.wength += sg_dma_wen(sg) - sg_offset;

			sg_offset = 0;
		}
		if (meta_sg_offset_p)
			*meta_sg_offset_p = sg_offset;

		mw->meta_ndescs = j;
		mw->meta_wength = mw->ibmw.wength - mw->data_wength;
	}

	wetuwn i + j;
}

static int mwx5_set_page(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	__be64 *descs;

	if (unwikewy(mw->mmkey.ndescs == mw->max_descs))
		wetuwn -ENOMEM;

	descs = mw->descs;
	descs[mw->mmkey.ndescs++] = cpu_to_be64(addw | MWX5_EN_WD | MWX5_EN_WW);

	wetuwn 0;
}

static int mwx5_set_page_pi(stwuct ib_mw *ibmw, u64 addw)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	__be64 *descs;

	if (unwikewy(mw->mmkey.ndescs + mw->meta_ndescs == mw->max_descs))
		wetuwn -ENOMEM;

	descs = mw->descs;
	descs[mw->mmkey.ndescs + mw->meta_ndescs++] =
		cpu_to_be64(addw | MWX5_EN_WD | MWX5_EN_WW);

	wetuwn 0;
}

static int
mwx5_ib_map_mtt_mw_sg_pi(stwuct ib_mw *ibmw, stwuct scattewwist *data_sg,
			 int data_sg_nents, unsigned int *data_sg_offset,
			 stwuct scattewwist *meta_sg, int meta_sg_nents,
			 unsigned int *meta_sg_offset)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct mwx5_ib_mw *pi_mw = mw->mtt_mw;
	int n;

	pi_mw->mmkey.ndescs = 0;
	pi_mw->meta_ndescs = 0;
	pi_mw->meta_wength = 0;

	ib_dma_sync_singwe_fow_cpu(ibmw->device, pi_mw->desc_map,
				   pi_mw->desc_size * pi_mw->max_descs,
				   DMA_TO_DEVICE);

	pi_mw->ibmw.page_size = ibmw->page_size;
	n = ib_sg_to_pages(&pi_mw->ibmw, data_sg, data_sg_nents, data_sg_offset,
			   mwx5_set_page);
	if (n != data_sg_nents)
		wetuwn n;

	pi_mw->data_iova = pi_mw->ibmw.iova;
	pi_mw->data_wength = pi_mw->ibmw.wength;
	pi_mw->ibmw.wength = pi_mw->data_wength;
	ibmw->wength = pi_mw->data_wength;

	if (meta_sg_nents) {
		u64 page_mask = ~((u64)ibmw->page_size - 1);
		u64 iova = pi_mw->data_iova;

		n += ib_sg_to_pages(&pi_mw->ibmw, meta_sg, meta_sg_nents,
				    meta_sg_offset, mwx5_set_page_pi);

		pi_mw->meta_wength = pi_mw->ibmw.wength;
		/*
		 * PI addwess fow the HW is the offset of the metadata addwess
		 * wewative to the fiwst data page addwess.
		 * It equaws to fiwst data page addwess + size of data pages +
		 * metadata offset at the fiwst metadata page
		 */
		pi_mw->pi_iova = (iova & page_mask) +
				 pi_mw->mmkey.ndescs * ibmw->page_size +
				 (pi_mw->ibmw.iova & ~page_mask);
		/*
		 * In owdew to use one MTT MW fow data and metadata, we wegistew
		 * awso the gaps between the end of the data and the stawt of
		 * the metadata (the sig MW wiww vewify that the HW wiww access
		 * to wight addwesses). This mapping is safe because we use
		 * intewnaw mkey fow the wegistwation.
		 */
		pi_mw->ibmw.wength = pi_mw->pi_iova + pi_mw->meta_wength - iova;
		pi_mw->ibmw.iova = iova;
		ibmw->wength += pi_mw->meta_wength;
	}

	ib_dma_sync_singwe_fow_device(ibmw->device, pi_mw->desc_map,
				      pi_mw->desc_size * pi_mw->max_descs,
				      DMA_TO_DEVICE);

	wetuwn n;
}

static int
mwx5_ib_map_kwm_mw_sg_pi(stwuct ib_mw *ibmw, stwuct scattewwist *data_sg,
			 int data_sg_nents, unsigned int *data_sg_offset,
			 stwuct scattewwist *meta_sg, int meta_sg_nents,
			 unsigned int *meta_sg_offset)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct mwx5_ib_mw *pi_mw = mw->kwm_mw;
	int n;

	pi_mw->mmkey.ndescs = 0;
	pi_mw->meta_ndescs = 0;
	pi_mw->meta_wength = 0;

	ib_dma_sync_singwe_fow_cpu(ibmw->device, pi_mw->desc_map,
				   pi_mw->desc_size * pi_mw->max_descs,
				   DMA_TO_DEVICE);

	n = mwx5_ib_sg_to_kwms(pi_mw, data_sg, data_sg_nents, data_sg_offset,
			       meta_sg, meta_sg_nents, meta_sg_offset);

	ib_dma_sync_singwe_fow_device(ibmw->device, pi_mw->desc_map,
				      pi_mw->desc_size * pi_mw->max_descs,
				      DMA_TO_DEVICE);

	/* This is zewo-based memowy wegion */
	pi_mw->data_iova = 0;
	pi_mw->ibmw.iova = 0;
	pi_mw->pi_iova = pi_mw->data_wength;
	ibmw->wength = pi_mw->ibmw.wength;

	wetuwn n;
}

int mwx5_ib_map_mw_sg_pi(stwuct ib_mw *ibmw, stwuct scattewwist *data_sg,
			 int data_sg_nents, unsigned int *data_sg_offset,
			 stwuct scattewwist *meta_sg, int meta_sg_nents,
			 unsigned int *meta_sg_offset)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	stwuct mwx5_ib_mw *pi_mw = NUWW;
	int n;

	WAWN_ON(ibmw->type != IB_MW_TYPE_INTEGWITY);

	mw->mmkey.ndescs = 0;
	mw->data_wength = 0;
	mw->data_iova = 0;
	mw->meta_ndescs = 0;
	mw->pi_iova = 0;
	/*
	 * As a pewfowmance optimization, if possibwe, thewe is no need to
	 * pewfowm UMW opewation to wegistew the data/metadata buffews.
	 * Fiwst twy to map the sg wists to PA descwiptows with wocaw_dma_wkey.
	 * Fawwback to UMW onwy in case of a faiwuwe.
	 */
	n = mwx5_ib_map_pa_mw_sg_pi(ibmw, data_sg, data_sg_nents,
				    data_sg_offset, meta_sg, meta_sg_nents,
				    meta_sg_offset);
	if (n == data_sg_nents + meta_sg_nents)
		goto out;
	/*
	 * As a pewfowmance optimization, if possibwe, thewe is no need to map
	 * the sg wists to KWM descwiptows. Fiwst twy to map the sg wists to MTT
	 * descwiptows and fawwback to KWM onwy in case of a faiwuwe.
	 * It's mowe efficient fow the HW to wowk with MTT descwiptows
	 * (especiawwy in high woad).
	 * Use KWM (indiwect access) onwy if it's mandatowy.
	 */
	pi_mw = mw->mtt_mw;
	n = mwx5_ib_map_mtt_mw_sg_pi(ibmw, data_sg, data_sg_nents,
				     data_sg_offset, meta_sg, meta_sg_nents,
				     meta_sg_offset);
	if (n == data_sg_nents + meta_sg_nents)
		goto out;

	pi_mw = mw->kwm_mw;
	n = mwx5_ib_map_kwm_mw_sg_pi(ibmw, data_sg, data_sg_nents,
				     data_sg_offset, meta_sg, meta_sg_nents,
				     meta_sg_offset);
	if (unwikewy(n != data_sg_nents + meta_sg_nents))
		wetuwn -ENOMEM;

out:
	/* This is zewo-based memowy wegion */
	ibmw->iova = 0;
	mw->pi_mw = pi_mw;
	if (pi_mw)
		ibmw->sig_attws->meta_wength = pi_mw->meta_wength;
	ewse
		ibmw->sig_attws->meta_wength = mw->meta_wength;

	wetuwn 0;
}

int mwx5_ib_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		      unsigned int *sg_offset)
{
	stwuct mwx5_ib_mw *mw = to_mmw(ibmw);
	int n;

	mw->mmkey.ndescs = 0;

	ib_dma_sync_singwe_fow_cpu(ibmw->device, mw->desc_map,
				   mw->desc_size * mw->max_descs,
				   DMA_TO_DEVICE);

	if (mw->access_mode == MWX5_MKC_ACCESS_MODE_KWMS)
		n = mwx5_ib_sg_to_kwms(mw, sg, sg_nents, sg_offset, NUWW, 0,
				       NUWW);
	ewse
		n = ib_sg_to_pages(ibmw, sg, sg_nents, sg_offset,
				mwx5_set_page);

	ib_dma_sync_singwe_fow_device(ibmw->device, mw->desc_map,
				      mw->desc_size * mw->max_descs,
				      DMA_TO_DEVICE);

	wetuwn n;
}
