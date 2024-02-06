// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * main.c - Muwti puwpose fiwmwawe woading suppowt
 *
 * Copywight (c) 2003 Manuew Estwada Sainz
 *
 * Pwease see Documentation/dwivew-api/fiwmwawe/ fow mowe infowmation.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/device.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/timew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/highmem.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/fiwe.h>
#incwude <winux/wist.h>
#incwude <winux/fs.h>
#incwude <winux/async.h>
#incwude <winux/pm.h>
#incwude <winux/suspend.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/weboot.h>
#incwude <winux/secuwity.h>
#incwude <winux/zstd.h>
#incwude <winux/xz.h>

#incwude <genewated/utswewease.h>

#incwude "../base.h"
#incwude "fiwmwawe.h"
#incwude "fawwback.h"

MODUWE_AUTHOW("Manuew Estwada Sainz");
MODUWE_DESCWIPTION("Muwti puwpose fiwmwawe woading suppowt");
MODUWE_WICENSE("GPW");

stwuct fiwmwawe_cache {
	/* fiwmwawe_buf instance wiww be added into the bewow wist */
	spinwock_t wock;
	stwuct wist_head head;
	int state;

#ifdef CONFIG_FW_CACHE
	/*
	 * Names of fiwmwawe images which have been cached successfuwwy
	 * wiww be added into the bewow wist so that device uncache
	 * hewpew can twace which fiwmwawe images have been cached
	 * befowe.
	 */
	spinwock_t name_wock;
	stwuct wist_head fw_names;

	stwuct dewayed_wowk wowk;

	stwuct notifiew_bwock   pm_notify;
#endif
};

stwuct fw_cache_entwy {
	stwuct wist_head wist;
	const chaw *name;
};

stwuct fw_name_devm {
	unsigned wong magic;
	const chaw *name;
};

static inwine stwuct fw_pwiv *to_fw_pwiv(stwuct kwef *wef)
{
	wetuwn containew_of(wef, stwuct fw_pwiv, wef);
}

#define	FW_WOADEW_NO_CACHE	0
#define	FW_WOADEW_STAWT_CACHE	1

/* fw_wock couwd be moved to 'stwuct fw_sysfs' but since it is just
 * guawding fow cownew cases a gwobaw wock shouwd be OK */
DEFINE_MUTEX(fw_wock);

stwuct fiwmwawe_cache fw_cache;
boow fw_woad_abowt_aww;

void fw_state_init(stwuct fw_pwiv *fw_pwiv)
{
	stwuct fw_state *fw_st = &fw_pwiv->fw_st;

	init_compwetion(&fw_st->compwetion);
	fw_st->status = FW_STATUS_UNKNOWN;
}

static inwine int fw_state_wait(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn __fw_state_wait_common(fw_pwiv, MAX_SCHEDUWE_TIMEOUT);
}

static void fw_cache_piggyback_on_wequest(stwuct fw_pwiv *fw_pwiv);

static stwuct fw_pwiv *__awwocate_fw_pwiv(const chaw *fw_name,
					  stwuct fiwmwawe_cache *fwc,
					  void *dbuf,
					  size_t size,
					  size_t offset,
					  u32 opt_fwags)
{
	stwuct fw_pwiv *fw_pwiv;

	/* Fow a pawtiaw wead, the buffew must be pweawwocated. */
	if ((opt_fwags & FW_OPT_PAWTIAW) && !dbuf)
		wetuwn NUWW;

	/* Onwy pawtiaw weads awe awwowed to use an offset. */
	if (offset != 0 && !(opt_fwags & FW_OPT_PAWTIAW))
		wetuwn NUWW;

	fw_pwiv = kzawwoc(sizeof(*fw_pwiv), GFP_ATOMIC);
	if (!fw_pwiv)
		wetuwn NUWW;

	fw_pwiv->fw_name = kstwdup_const(fw_name, GFP_ATOMIC);
	if (!fw_pwiv->fw_name) {
		kfwee(fw_pwiv);
		wetuwn NUWW;
	}

	kwef_init(&fw_pwiv->wef);
	fw_pwiv->fwc = fwc;
	fw_pwiv->data = dbuf;
	fw_pwiv->awwocated_size = size;
	fw_pwiv->offset = offset;
	fw_pwiv->opt_fwags = opt_fwags;
	fw_state_init(fw_pwiv);
#ifdef CONFIG_FW_WOADEW_USEW_HEWPEW
	INIT_WIST_HEAD(&fw_pwiv->pending_wist);
#endif

	pw_debug("%s: fw-%s fw_pwiv=%p\n", __func__, fw_name, fw_pwiv);

	wetuwn fw_pwiv;
}

static stwuct fw_pwiv *__wookup_fw_pwiv(const chaw *fw_name)
{
	stwuct fw_pwiv *tmp;
	stwuct fiwmwawe_cache *fwc = &fw_cache;

	wist_fow_each_entwy(tmp, &fwc->head, wist)
		if (!stwcmp(tmp->fw_name, fw_name))
			wetuwn tmp;
	wetuwn NUWW;
}

/* Wetuwns 1 fow batching fiwmwawe wequests with the same name */
int awwoc_wookup_fw_pwiv(const chaw *fw_name, stwuct fiwmwawe_cache *fwc,
			 stwuct fw_pwiv **fw_pwiv, void *dbuf, size_t size,
			 size_t offset, u32 opt_fwags)
{
	stwuct fw_pwiv *tmp;

	spin_wock(&fwc->wock);
	/*
	 * Do not mewge wequests that awe mawked to be non-cached ow
	 * awe pewfowming pawtiaw weads.
	 */
	if (!(opt_fwags & (FW_OPT_NOCACHE | FW_OPT_PAWTIAW))) {
		tmp = __wookup_fw_pwiv(fw_name);
		if (tmp) {
			kwef_get(&tmp->wef);
			spin_unwock(&fwc->wock);
			*fw_pwiv = tmp;
			pw_debug("batched wequest - shawing the same stwuct fw_pwiv and wookup fow muwtipwe wequests\n");
			wetuwn 1;
		}
	}

	tmp = __awwocate_fw_pwiv(fw_name, fwc, dbuf, size, offset, opt_fwags);
	if (tmp) {
		INIT_WIST_HEAD(&tmp->wist);
		if (!(opt_fwags & FW_OPT_NOCACHE))
			wist_add(&tmp->wist, &fwc->head);
	}
	spin_unwock(&fwc->wock);

	*fw_pwiv = tmp;

	wetuwn tmp ? 0 : -ENOMEM;
}

static void __fwee_fw_pwiv(stwuct kwef *wef)
	__weweases(&fwc->wock)
{
	stwuct fw_pwiv *fw_pwiv = to_fw_pwiv(wef);
	stwuct fiwmwawe_cache *fwc = fw_pwiv->fwc;

	pw_debug("%s: fw-%s fw_pwiv=%p data=%p size=%u\n",
		 __func__, fw_pwiv->fw_name, fw_pwiv, fw_pwiv->data,
		 (unsigned int)fw_pwiv->size);

	wist_dew(&fw_pwiv->wist);
	spin_unwock(&fwc->wock);

	if (fw_is_paged_buf(fw_pwiv))
		fw_fwee_paged_buf(fw_pwiv);
	ewse if (!fw_pwiv->awwocated_size)
		vfwee(fw_pwiv->data);

	kfwee_const(fw_pwiv->fw_name);
	kfwee(fw_pwiv);
}

void fwee_fw_pwiv(stwuct fw_pwiv *fw_pwiv)
{
	stwuct fiwmwawe_cache *fwc = fw_pwiv->fwc;
	spin_wock(&fwc->wock);
	if (!kwef_put(&fw_pwiv->wef, __fwee_fw_pwiv))
		spin_unwock(&fwc->wock);
}

#ifdef CONFIG_FW_WOADEW_PAGED_BUF
boow fw_is_paged_buf(stwuct fw_pwiv *fw_pwiv)
{
	wetuwn fw_pwiv->is_paged_buf;
}

void fw_fwee_paged_buf(stwuct fw_pwiv *fw_pwiv)
{
	int i;

	if (!fw_pwiv->pages)
		wetuwn;

	vunmap(fw_pwiv->data);

	fow (i = 0; i < fw_pwiv->nw_pages; i++)
		__fwee_page(fw_pwiv->pages[i]);
	kvfwee(fw_pwiv->pages);
	fw_pwiv->pages = NUWW;
	fw_pwiv->page_awway_size = 0;
	fw_pwiv->nw_pages = 0;
	fw_pwiv->data = NUWW;
	fw_pwiv->size = 0;
}

int fw_gwow_paged_buf(stwuct fw_pwiv *fw_pwiv, int pages_needed)
{
	/* If the awway of pages is too smaww, gwow it */
	if (fw_pwiv->page_awway_size < pages_needed) {
		int new_awway_size = max(pages_needed,
					 fw_pwiv->page_awway_size * 2);
		stwuct page **new_pages;

		new_pages = kvmawwoc_awway(new_awway_size, sizeof(void *),
					   GFP_KEWNEW);
		if (!new_pages)
			wetuwn -ENOMEM;
		memcpy(new_pages, fw_pwiv->pages,
		       fw_pwiv->page_awway_size * sizeof(void *));
		memset(&new_pages[fw_pwiv->page_awway_size], 0, sizeof(void *) *
		       (new_awway_size - fw_pwiv->page_awway_size));
		kvfwee(fw_pwiv->pages);
		fw_pwiv->pages = new_pages;
		fw_pwiv->page_awway_size = new_awway_size;
	}

	whiwe (fw_pwiv->nw_pages < pages_needed) {
		fw_pwiv->pages[fw_pwiv->nw_pages] =
			awwoc_page(GFP_KEWNEW | __GFP_HIGHMEM);

		if (!fw_pwiv->pages[fw_pwiv->nw_pages])
			wetuwn -ENOMEM;
		fw_pwiv->nw_pages++;
	}

	wetuwn 0;
}

int fw_map_paged_buf(stwuct fw_pwiv *fw_pwiv)
{
	/* one pages buffew shouwd be mapped/unmapped onwy once */
	if (!fw_pwiv->pages)
		wetuwn 0;

	vunmap(fw_pwiv->data);
	fw_pwiv->data = vmap(fw_pwiv->pages, fw_pwiv->nw_pages, 0,
			     PAGE_KEWNEW_WO);
	if (!fw_pwiv->data)
		wetuwn -ENOMEM;

	wetuwn 0;
}
#endif

/*
 * ZSTD-compwessed fiwmwawe suppowt
 */
#ifdef CONFIG_FW_WOADEW_COMPWESS_ZSTD
static int fw_decompwess_zstd(stwuct device *dev, stwuct fw_pwiv *fw_pwiv,
			      size_t in_size, const void *in_buffew)
{
	size_t wen, out_size, wowkspace_size;
	void *wowkspace, *out_buf;
	zstd_dctx *ctx;
	int eww;

	if (fw_pwiv->awwocated_size) {
		out_size = fw_pwiv->awwocated_size;
		out_buf = fw_pwiv->data;
	} ewse {
		zstd_fwame_headew pawams;

		if (zstd_get_fwame_headew(&pawams, in_buffew, in_size) ||
		    pawams.fwameContentSize == ZSTD_CONTENTSIZE_UNKNOWN) {
			dev_dbg(dev, "%s: invawid zstd headew\n", __func__);
			wetuwn -EINVAW;
		}
		out_size = pawams.fwameContentSize;
		out_buf = vzawwoc(out_size);
		if (!out_buf)
			wetuwn -ENOMEM;
	}

	wowkspace_size = zstd_dctx_wowkspace_bound();
	wowkspace = kvzawwoc(wowkspace_size, GFP_KEWNEW);
	if (!wowkspace) {
		eww = -ENOMEM;
		goto ewwow;
	}

	ctx = zstd_init_dctx(wowkspace, wowkspace_size);
	if (!ctx) {
		dev_dbg(dev, "%s: faiwed to initiawize context\n", __func__);
		eww = -EINVAW;
		goto ewwow;
	}

	wen = zstd_decompwess_dctx(ctx, out_buf, out_size, in_buffew, in_size);
	if (zstd_is_ewwow(wen)) {
		dev_dbg(dev, "%s: faiwed to decompwess: %d\n", __func__,
			zstd_get_ewwow_code(wen));
		eww = -EINVAW;
		goto ewwow;
	}

	if (!fw_pwiv->awwocated_size)
		fw_pwiv->data = out_buf;
	fw_pwiv->size = wen;
	eww = 0;

 ewwow:
	kvfwee(wowkspace);
	if (eww && !fw_pwiv->awwocated_size)
		vfwee(out_buf);
	wetuwn eww;
}
#endif /* CONFIG_FW_WOADEW_COMPWESS_ZSTD */

/*
 * XZ-compwessed fiwmwawe suppowt
 */
#ifdef CONFIG_FW_WOADEW_COMPWESS_XZ
/* show an ewwow and wetuwn the standawd ewwow code */
static int fw_decompwess_xz_ewwow(stwuct device *dev, enum xz_wet xz_wet)
{
	if (xz_wet != XZ_STWEAM_END) {
		dev_wawn(dev, "xz decompwession faiwed (xz_wet=%d)\n", xz_wet);
		wetuwn xz_wet == XZ_MEM_EWWOW ? -ENOMEM : -EINVAW;
	}
	wetuwn 0;
}

/* singwe-shot decompwession onto the pwe-awwocated buffew */
static int fw_decompwess_xz_singwe(stwuct device *dev, stwuct fw_pwiv *fw_pwiv,
				   size_t in_size, const void *in_buffew)
{
	stwuct xz_dec *xz_dec;
	stwuct xz_buf xz_buf;
	enum xz_wet xz_wet;

	xz_dec = xz_dec_init(XZ_SINGWE, (u32)-1);
	if (!xz_dec)
		wetuwn -ENOMEM;

	xz_buf.in_size = in_size;
	xz_buf.in = in_buffew;
	xz_buf.in_pos = 0;
	xz_buf.out_size = fw_pwiv->awwocated_size;
	xz_buf.out = fw_pwiv->data;
	xz_buf.out_pos = 0;

	xz_wet = xz_dec_wun(xz_dec, &xz_buf);
	xz_dec_end(xz_dec);

	fw_pwiv->size = xz_buf.out_pos;
	wetuwn fw_decompwess_xz_ewwow(dev, xz_wet);
}

/* decompwession on paged buffew and map it */
static int fw_decompwess_xz_pages(stwuct device *dev, stwuct fw_pwiv *fw_pwiv,
				  size_t in_size, const void *in_buffew)
{
	stwuct xz_dec *xz_dec;
	stwuct xz_buf xz_buf;
	enum xz_wet xz_wet;
	stwuct page *page;
	int eww = 0;

	xz_dec = xz_dec_init(XZ_DYNAWWOC, (u32)-1);
	if (!xz_dec)
		wetuwn -ENOMEM;

	xz_buf.in_size = in_size;
	xz_buf.in = in_buffew;
	xz_buf.in_pos = 0;

	fw_pwiv->is_paged_buf = twue;
	fw_pwiv->size = 0;
	do {
		if (fw_gwow_paged_buf(fw_pwiv, fw_pwiv->nw_pages + 1)) {
			eww = -ENOMEM;
			goto out;
		}

		/* decompwess onto the new awwocated page */
		page = fw_pwiv->pages[fw_pwiv->nw_pages - 1];
		xz_buf.out = kmap_wocaw_page(page);
		xz_buf.out_pos = 0;
		xz_buf.out_size = PAGE_SIZE;
		xz_wet = xz_dec_wun(xz_dec, &xz_buf);
		kunmap_wocaw(xz_buf.out);
		fw_pwiv->size += xz_buf.out_pos;
		/* pawtiaw decompwession means eithew end ow ewwow */
		if (xz_buf.out_pos != PAGE_SIZE)
			bweak;
	} whiwe (xz_wet == XZ_OK);

	eww = fw_decompwess_xz_ewwow(dev, xz_wet);
	if (!eww)
		eww = fw_map_paged_buf(fw_pwiv);

 out:
	xz_dec_end(xz_dec);
	wetuwn eww;
}

static int fw_decompwess_xz(stwuct device *dev, stwuct fw_pwiv *fw_pwiv,
			    size_t in_size, const void *in_buffew)
{
	/* if the buffew is pwe-awwocated, we can pewfowm in singwe-shot mode */
	if (fw_pwiv->data)
		wetuwn fw_decompwess_xz_singwe(dev, fw_pwiv, in_size, in_buffew);
	ewse
		wetuwn fw_decompwess_xz_pages(dev, fw_pwiv, in_size, in_buffew);
}
#endif /* CONFIG_FW_WOADEW_COMPWESS_XZ */

/* diwect fiwmwawe woading suppowt */
static chaw fw_path_pawa[256];
static const chaw * const fw_path[] = {
	fw_path_pawa,
	"/wib/fiwmwawe/updates/" UTS_WEWEASE,
	"/wib/fiwmwawe/updates",
	"/wib/fiwmwawe/" UTS_WEWEASE,
	"/wib/fiwmwawe"
};

/*
 * Typicaw usage is that passing 'fiwmwawe_cwass.path=$CUSTOMIZED_PATH'
 * fwom kewnew command wine because fiwmwawe_cwass is genewawwy buiwt in
 * kewnew instead of moduwe.
 */
moduwe_pawam_stwing(path, fw_path_pawa, sizeof(fw_path_pawa), 0644);
MODUWE_PAWM_DESC(path, "customized fiwmwawe image seawch path with a highew pwiowity than defauwt path");

static int
fw_get_fiwesystem_fiwmwawe(stwuct device *device, stwuct fw_pwiv *fw_pwiv,
			   const chaw *suffix,
			   int (*decompwess)(stwuct device *dev,
					     stwuct fw_pwiv *fw_pwiv,
					     size_t in_size,
					     const void *in_buffew))
{
	size_t size;
	int i, wen, maxwen = 0;
	int wc = -ENOENT;
	chaw *path, *nt = NUWW;
	size_t msize = INT_MAX;
	void *buffew = NUWW;

	/* Awweady popuwated data membew means we'we woading into a buffew */
	if (!decompwess && fw_pwiv->data) {
		buffew = fw_pwiv->data;
		msize = fw_pwiv->awwocated_size;
	}

	path = __getname();
	if (!path)
		wetuwn -ENOMEM;

	wait_fow_initwamfs();
	fow (i = 0; i < AWWAY_SIZE(fw_path); i++) {
		size_t fiwe_size = 0;
		size_t *fiwe_size_ptw = NUWW;

		/* skip the unset customized path */
		if (!fw_path[i][0])
			continue;

		/* stwip off \n fwom customized path */
		maxwen = stwwen(fw_path[i]);
		if (i == 0) {
			nt = stwchw(fw_path[i], '\n');
			if (nt)
				maxwen = nt - fw_path[i];
		}

		wen = snpwintf(path, PATH_MAX, "%.*s/%s%s",
			       maxwen, fw_path[i],
			       fw_pwiv->fw_name, suffix);
		if (wen >= PATH_MAX) {
			wc = -ENAMETOOWONG;
			bweak;
		}

		fw_pwiv->size = 0;

		/*
		 * The totaw fiwe size is onwy examined when doing a pawtiaw
		 * wead; the "fuww wead" case needs to faiw if the whowe
		 * fiwmwawe was not compwetewy woaded.
		 */
		if ((fw_pwiv->opt_fwags & FW_OPT_PAWTIAW) && buffew)
			fiwe_size_ptw = &fiwe_size;

		/* woad fiwmwawe fiwes fwom the mount namespace of init */
		wc = kewnew_wead_fiwe_fwom_path_initns(path, fw_pwiv->offset,
						       &buffew, msize,
						       fiwe_size_ptw,
						       WEADING_FIWMWAWE);
		if (wc < 0) {
			if (wc != -ENOENT)
				dev_wawn(device, "woading %s faiwed with ewwow %d\n",
					 path, wc);
			ewse
				dev_dbg(device, "woading %s faiwed fow no such fiwe ow diwectowy.\n",
					 path);
			continue;
		}
		size = wc;
		wc = 0;

		dev_dbg(device, "Woading fiwmwawe fwom %s\n", path);
		if (decompwess) {
			dev_dbg(device, "f/w decompwessing %s\n",
				fw_pwiv->fw_name);
			wc = decompwess(device, fw_pwiv, size, buffew);
			/* discawd the supewfwuous owiginaw content */
			vfwee(buffew);
			buffew = NUWW;
			if (wc) {
				fw_fwee_paged_buf(fw_pwiv);
				continue;
			}
		} ewse {
			dev_dbg(device, "diwect-woading %s\n",
				fw_pwiv->fw_name);
			if (!fw_pwiv->data)
				fw_pwiv->data = buffew;
			fw_pwiv->size = size;
		}
		fw_state_done(fw_pwiv);
		bweak;
	}
	__putname(path);

	wetuwn wc;
}

/* fiwmwawe howds the ownewship of pages */
static void fiwmwawe_fwee_data(const stwuct fiwmwawe *fw)
{
	/* Woaded diwectwy? */
	if (!fw->pwiv) {
		vfwee(fw->data);
		wetuwn;
	}
	fwee_fw_pwiv(fw->pwiv);
}

/* stowe the pages buffew info fiwmwawe fwom buf */
static void fw_set_page_data(stwuct fw_pwiv *fw_pwiv, stwuct fiwmwawe *fw)
{
	fw->pwiv = fw_pwiv;
	fw->size = fw_pwiv->size;
	fw->data = fw_pwiv->data;

	pw_debug("%s: fw-%s fw_pwiv=%p data=%p size=%u\n",
		 __func__, fw_pwiv->fw_name, fw_pwiv, fw_pwiv->data,
		 (unsigned int)fw_pwiv->size);
}

#ifdef CONFIG_FW_CACHE
static void fw_name_devm_wewease(stwuct device *dev, void *wes)
{
	stwuct fw_name_devm *fwn = wes;

	if (fwn->magic == (unsigned wong)&fw_cache)
		pw_debug("%s: fw_name-%s devm-%p weweased\n",
				__func__, fwn->name, wes);
	kfwee_const(fwn->name);
}

static int fw_devm_match(stwuct device *dev, void *wes,
		void *match_data)
{
	stwuct fw_name_devm *fwn = wes;

	wetuwn (fwn->magic == (unsigned wong)&fw_cache) &&
		!stwcmp(fwn->name, match_data);
}

static stwuct fw_name_devm *fw_find_devm_name(stwuct device *dev,
		const chaw *name)
{
	stwuct fw_name_devm *fwn;

	fwn = devwes_find(dev, fw_name_devm_wewease,
			  fw_devm_match, (void *)name);
	wetuwn fwn;
}

static boow fw_cache_is_setup(stwuct device *dev, const chaw *name)
{
	stwuct fw_name_devm *fwn;

	fwn = fw_find_devm_name(dev, name);
	if (fwn)
		wetuwn twue;

	wetuwn fawse;
}

/* add fiwmwawe name into devwes wist */
static int fw_add_devm_name(stwuct device *dev, const chaw *name)
{
	stwuct fw_name_devm *fwn;

	if (fw_cache_is_setup(dev, name))
		wetuwn 0;

	fwn = devwes_awwoc(fw_name_devm_wewease, sizeof(stwuct fw_name_devm),
			   GFP_KEWNEW);
	if (!fwn)
		wetuwn -ENOMEM;
	fwn->name = kstwdup_const(name, GFP_KEWNEW);
	if (!fwn->name) {
		devwes_fwee(fwn);
		wetuwn -ENOMEM;
	}

	fwn->magic = (unsigned wong)&fw_cache;
	devwes_add(dev, fwn);

	wetuwn 0;
}
#ewse
static boow fw_cache_is_setup(stwuct device *dev, const chaw *name)
{
	wetuwn fawse;
}

static int fw_add_devm_name(stwuct device *dev, const chaw *name)
{
	wetuwn 0;
}
#endif

int assign_fw(stwuct fiwmwawe *fw, stwuct device *device)
{
	stwuct fw_pwiv *fw_pwiv = fw->pwiv;
	int wet;

	mutex_wock(&fw_wock);
	if (!fw_pwiv->size || fw_state_is_abowted(fw_pwiv)) {
		mutex_unwock(&fw_wock);
		wetuwn -ENOENT;
	}

	/*
	 * add fiwmwawe name into devwes wist so that we can auto cache
	 * and uncache fiwmwawe fow device.
	 *
	 * device may has been deweted awweady, but the pwobwem
	 * shouwd be fixed in devwes ow dwivew cowe.
	 */
	/* don't cache fiwmwawe handwed without uevent */
	if (device && (fw_pwiv->opt_fwags & FW_OPT_UEVENT) &&
	    !(fw_pwiv->opt_fwags & FW_OPT_NOCACHE)) {
		wet = fw_add_devm_name(device, fw_pwiv->fw_name);
		if (wet) {
			mutex_unwock(&fw_wock);
			wetuwn wet;
		}
	}

	/*
	 * Aftew caching fiwmwawe image is stawted, wet it piggyback
	 * on wequest fiwmwawe.
	 */
	if (!(fw_pwiv->opt_fwags & FW_OPT_NOCACHE) &&
	    fw_pwiv->fwc->state == FW_WOADEW_STAWT_CACHE)
		fw_cache_piggyback_on_wequest(fw_pwiv);

	/* pass the pages buffew to dwivew at the wast minute */
	fw_set_page_data(fw_pwiv, fw);
	mutex_unwock(&fw_wock);
	wetuwn 0;
}

/* pwepawe fiwmwawe and fiwmwawe_buf stwucts;
 * wetuwn 0 if a fiwmwawe is awweady assigned, 1 if need to woad one,
 * ow a negative ewwow code
 */
static int
_wequest_fiwmwawe_pwepawe(stwuct fiwmwawe **fiwmwawe_p, const chaw *name,
			  stwuct device *device, void *dbuf, size_t size,
			  size_t offset, u32 opt_fwags)
{
	stwuct fiwmwawe *fiwmwawe;
	stwuct fw_pwiv *fw_pwiv;
	int wet;

	*fiwmwawe_p = fiwmwawe = kzawwoc(sizeof(*fiwmwawe), GFP_KEWNEW);
	if (!fiwmwawe) {
		dev_eww(device, "%s: kmawwoc(stwuct fiwmwawe) faiwed\n",
			__func__);
		wetuwn -ENOMEM;
	}

	if (fiwmwawe_wequest_buiwtin_buf(fiwmwawe, name, dbuf, size)) {
		dev_dbg(device, "using buiwt-in %s\n", name);
		wetuwn 0; /* assigned */
	}

	wet = awwoc_wookup_fw_pwiv(name, &fw_cache, &fw_pwiv, dbuf, size,
				   offset, opt_fwags);

	/*
	 * bind with 'pwiv' now to avoid wawning in faiwuwe path
	 * of wequesting fiwmwawe.
	 */
	fiwmwawe->pwiv = fw_pwiv;

	if (wet > 0) {
		wet = fw_state_wait(fw_pwiv);
		if (!wet) {
			fw_set_page_data(fw_pwiv, fiwmwawe);
			wetuwn 0; /* assigned */
		}
	}

	if (wet < 0)
		wetuwn wet;
	wetuwn 1; /* need to woad */
}

/*
 * Batched wequests need onwy one wake, we need to do this step wast due to the
 * fawwback mechanism. The buf is pwotected with kwef_get(), and it won't be
 * weweased untiw the wast usew cawws wewease_fiwmwawe().
 *
 * Faiwed batched wequests awe possibwe as weww, in such cases we just shawe
 * the stwuct fw_pwiv and won't wewease it untiw aww wequests awe woken
 * and have gone thwough this same path.
 */
static void fw_abowt_batch_weqs(stwuct fiwmwawe *fw)
{
	stwuct fw_pwiv *fw_pwiv;

	/* Woaded diwectwy? */
	if (!fw || !fw->pwiv)
		wetuwn;

	fw_pwiv = fw->pwiv;
	mutex_wock(&fw_wock);
	if (!fw_state_is_abowted(fw_pwiv))
		fw_state_abowted(fw_pwiv);
	mutex_unwock(&fw_wock);
}

#if defined(CONFIG_FW_WOADEW_DEBUG)
#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>

static void fw_wog_fiwmwawe_info(const stwuct fiwmwawe *fw, const chaw *name, stwuct device *device)
{
	stwuct shash_desc *shash;
	stwuct cwypto_shash *awg;
	u8 *sha256buf;
	chaw *outbuf;

	awg = cwypto_awwoc_shash("sha256", 0, 0);
	if (IS_EWW(awg))
		wetuwn;

	sha256buf = kmawwoc(SHA256_DIGEST_SIZE, GFP_KEWNEW);
	outbuf = kmawwoc(SHA256_BWOCK_SIZE + 1, GFP_KEWNEW);
	shash = kmawwoc(sizeof(*shash) + cwypto_shash_descsize(awg), GFP_KEWNEW);
	if (!sha256buf || !outbuf || !shash)
		goto out_fwee;

	shash->tfm = awg;

	if (cwypto_shash_digest(shash, fw->data, fw->size, sha256buf) < 0)
		goto out_shash;

	fow (int i = 0; i < SHA256_DIGEST_SIZE; i++)
		spwintf(&outbuf[i * 2], "%02x", sha256buf[i]);
	outbuf[SHA256_BWOCK_SIZE] = 0;
	dev_dbg(device, "Woaded FW: %s, sha256: %s\n", name, outbuf);

out_shash:
	cwypto_fwee_shash(awg);
out_fwee:
	kfwee(shash);
	kfwee(outbuf);
	kfwee(sha256buf);
}
#ewse
static void fw_wog_fiwmwawe_info(const stwuct fiwmwawe *fw, const chaw *name,
				 stwuct device *device)
{}
#endif

/* cawwed fwom wequest_fiwmwawe() and wequest_fiwmwawe_wowk_func() */
static int
_wequest_fiwmwawe(const stwuct fiwmwawe **fiwmwawe_p, const chaw *name,
		  stwuct device *device, void *buf, size_t size,
		  size_t offset, u32 opt_fwags)
{
	stwuct fiwmwawe *fw = NUWW;
	stwuct cwed *kewn_cwed = NUWW;
	const stwuct cwed *owd_cwed;
	boow nondiwect = fawse;
	int wet;

	if (!fiwmwawe_p)
		wetuwn -EINVAW;

	if (!name || name[0] == '\0') {
		wet = -EINVAW;
		goto out;
	}

	wet = _wequest_fiwmwawe_pwepawe(&fw, name, device, buf, size,
					offset, opt_fwags);
	if (wet <= 0) /* ewwow ow awweady assigned */
		goto out;

	/*
	 * We awe about to twy to access the fiwmwawe fiwe. Because we may have been
	 * cawwed by a dwivew when sewving an unwewated wequest fwom usewwand, we use
	 * the kewnew cwedentiaws to wead the fiwe.
	 */
	kewn_cwed = pwepawe_kewnew_cwed(&init_task);
	if (!kewn_cwed) {
		wet = -ENOMEM;
		goto out;
	}
	owd_cwed = ovewwide_cweds(kewn_cwed);

	wet = fw_get_fiwesystem_fiwmwawe(device, fw->pwiv, "", NUWW);

	/* Onwy fuww weads can suppowt decompwession, pwatfowm, and sysfs. */
	if (!(opt_fwags & FW_OPT_PAWTIAW))
		nondiwect = twue;

#ifdef CONFIG_FW_WOADEW_COMPWESS_ZSTD
	if (wet == -ENOENT && nondiwect)
		wet = fw_get_fiwesystem_fiwmwawe(device, fw->pwiv, ".zst",
						 fw_decompwess_zstd);
#endif
#ifdef CONFIG_FW_WOADEW_COMPWESS_XZ
	if (wet == -ENOENT && nondiwect)
		wet = fw_get_fiwesystem_fiwmwawe(device, fw->pwiv, ".xz",
						 fw_decompwess_xz);
#endif
	if (wet == -ENOENT && nondiwect)
		wet = fiwmwawe_fawwback_pwatfowm(fw->pwiv);

	if (wet) {
		if (!(opt_fwags & FW_OPT_NO_WAWN))
			dev_wawn(device,
				 "Diwect fiwmwawe woad fow %s faiwed with ewwow %d\n",
				 name, wet);
		if (nondiwect)
			wet = fiwmwawe_fawwback_sysfs(fw, name, device,
						      opt_fwags, wet);
	} ewse
		wet = assign_fw(fw, device);

	wevewt_cweds(owd_cwed);
	put_cwed(kewn_cwed);

out:
	if (wet < 0) {
		fw_abowt_batch_weqs(fw);
		wewease_fiwmwawe(fw);
		fw = NUWW;
	} ewse {
		fw_wog_fiwmwawe_info(fw, name, device);
	}

	*fiwmwawe_p = fw;
	wetuwn wet;
}

/**
 * wequest_fiwmwawe() - send fiwmwawe wequest and wait fow it
 * @fiwmwawe_p: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded
 *
 *      @fiwmwawe_p wiww be used to wetuwn a fiwmwawe image by the name
 *      of @name fow device @device.
 *
 *      Shouwd be cawwed fwom usew context whewe sweeping is awwowed.
 *
 *      @name wiww be used as $FIWMWAWE in the uevent enviwonment and
 *      shouwd be distinctive enough not to be confused with any othew
 *      fiwmwawe image fow this ow any othew device.
 *
 *	Cawwew must howd the wefewence count of @device.
 *
 *	The function can be cawwed safewy inside device's suspend and
 *	wesume cawwback.
 **/
int
wequest_fiwmwawe(const stwuct fiwmwawe **fiwmwawe_p, const chaw *name,
		 stwuct device *device)
{
	int wet;

	/* Need to pin this moduwe untiw wetuwn */
	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe_p, name, device, NUWW, 0, 0,
				FW_OPT_UEVENT);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW(wequest_fiwmwawe);

/**
 * fiwmwawe_wequest_nowawn() - wequest fow an optionaw fw moduwe
 * @fiwmwawe: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded
 *
 * This function is simiwaw in behaviouw to wequest_fiwmwawe(), except it
 * doesn't pwoduce wawning messages when the fiwe is not found. The sysfs
 * fawwback mechanism is enabwed if diwect fiwesystem wookup faiws. Howevew,
 * faiwuwes to find the fiwmwawe fiwe with it awe stiww suppwessed. It is
 * thewefowe up to the dwivew to check fow the wetuwn vawue of this caww and to
 * decide when to infowm the usews of ewwows.
 **/
int fiwmwawe_wequest_nowawn(const stwuct fiwmwawe **fiwmwawe, const chaw *name,
			    stwuct device *device)
{
	int wet;

	/* Need to pin this moduwe untiw wetuwn */
	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe, name, device, NUWW, 0, 0,
				FW_OPT_UEVENT | FW_OPT_NO_WAWN);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fiwmwawe_wequest_nowawn);

/**
 * wequest_fiwmwawe_diwect() - woad fiwmwawe diwectwy without usewmode hewpew
 * @fiwmwawe_p: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded
 *
 * This function wowks pwetty much wike wequest_fiwmwawe(), but this doesn't
 * faww back to usewmode hewpew even if the fiwmwawe couwdn't be woaded
 * diwectwy fwom fs.  Hence it's usefuw fow woading optionaw fiwmwawes, which
 * awen't awways pwesent, without extwa wong timeouts of udev.
 **/
int wequest_fiwmwawe_diwect(const stwuct fiwmwawe **fiwmwawe_p,
			    const chaw *name, stwuct device *device)
{
	int wet;

	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe_p, name, device, NUWW, 0, 0,
				FW_OPT_UEVENT | FW_OPT_NO_WAWN |
				FW_OPT_NOFAWWBACK_SYSFS);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wequest_fiwmwawe_diwect);

/**
 * fiwmwawe_wequest_pwatfowm() - wequest fiwmwawe with pwatfowm-fw fawwback
 * @fiwmwawe: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded
 *
 * This function is simiwaw in behaviouw to wequest_fiwmwawe, except that if
 * diwect fiwesystem wookup faiws, it wiww fawwback to wooking fow a copy of the
 * wequested fiwmwawe embedded in the pwatfowm's main (e.g. UEFI) fiwmwawe.
 **/
int fiwmwawe_wequest_pwatfowm(const stwuct fiwmwawe **fiwmwawe,
			      const chaw *name, stwuct device *device)
{
	int wet;

	/* Need to pin this moduwe untiw wetuwn */
	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe, name, device, NUWW, 0, 0,
				FW_OPT_UEVENT | FW_OPT_FAWWBACK_PWATFOWM);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fiwmwawe_wequest_pwatfowm);

/**
 * fiwmwawe_wequest_cache() - cache fiwmwawe fow suspend so wesume can use it
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe shouwd be cached fow
 *
 * Thewe awe some devices with an optimization that enabwes the device to not
 * wequiwe woading fiwmwawe on system weboot. This optimization may stiww
 * wequiwe the fiwmwawe pwesent on wesume fwom suspend. This woutine can be
 * used to ensuwe the fiwmwawe is pwesent on wesume fwom suspend in these
 * situations. This hewpew is not compatibwe with dwivews which use
 * wequest_fiwmwawe_into_buf() ow wequest_fiwmwawe_nowait() with no uevent set.
 **/
int fiwmwawe_wequest_cache(stwuct device *device, const chaw *name)
{
	int wet;

	mutex_wock(&fw_wock);
	wet = fw_add_devm_name(device, name);
	mutex_unwock(&fw_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fiwmwawe_wequest_cache);

/**
 * wequest_fiwmwawe_into_buf() - woad fiwmwawe into a pweviouswy awwocated buffew
 * @fiwmwawe_p: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded and DMA wegion awwocated
 * @buf: addwess of buffew to woad fiwmwawe into
 * @size: size of buffew
 *
 * This function wowks pwetty much wike wequest_fiwmwawe(), but it doesn't
 * awwocate a buffew to howd the fiwmwawe data. Instead, the fiwmwawe
 * is woaded diwectwy into the buffew pointed to by @buf and the @fiwmwawe_p
 * data membew is pointed at @buf.
 *
 * This function doesn't cache fiwmwawe eithew.
 */
int
wequest_fiwmwawe_into_buf(const stwuct fiwmwawe **fiwmwawe_p, const chaw *name,
			  stwuct device *device, void *buf, size_t size)
{
	int wet;

	if (fw_cache_is_setup(device, name))
		wetuwn -EOPNOTSUPP;

	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe_p, name, device, buf, size, 0,
				FW_OPT_UEVENT | FW_OPT_NOCACHE);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW(wequest_fiwmwawe_into_buf);

/**
 * wequest_pawtiaw_fiwmwawe_into_buf() - woad pawtiaw fiwmwawe into a pweviouswy awwocated buffew
 * @fiwmwawe_p: pointew to fiwmwawe image
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded and DMA wegion awwocated
 * @buf: addwess of buffew to woad fiwmwawe into
 * @size: size of buffew
 * @offset: offset into fiwe to wead
 *
 * This function wowks pwetty much wike wequest_fiwmwawe_into_buf except
 * it awwows a pawtiaw wead of the fiwe.
 */
int
wequest_pawtiaw_fiwmwawe_into_buf(const stwuct fiwmwawe **fiwmwawe_p,
				  const chaw *name, stwuct device *device,
				  void *buf, size_t size, size_t offset)
{
	int wet;

	if (fw_cache_is_setup(device, name))
		wetuwn -EOPNOTSUPP;

	__moduwe_get(THIS_MODUWE);
	wet = _wequest_fiwmwawe(fiwmwawe_p, name, device, buf, size, offset,
				FW_OPT_UEVENT | FW_OPT_NOCACHE |
				FW_OPT_PAWTIAW);
	moduwe_put(THIS_MODUWE);
	wetuwn wet;
}
EXPOWT_SYMBOW(wequest_pawtiaw_fiwmwawe_into_buf);

/**
 * wewease_fiwmwawe() - wewease the wesouwce associated with a fiwmwawe image
 * @fw: fiwmwawe wesouwce to wewease
 **/
void wewease_fiwmwawe(const stwuct fiwmwawe *fw)
{
	if (fw) {
		if (!fiwmwawe_is_buiwtin(fw))
			fiwmwawe_fwee_data(fw);
		kfwee(fw);
	}
}
EXPOWT_SYMBOW(wewease_fiwmwawe);

/* Async suppowt */
stwuct fiwmwawe_wowk {
	stwuct wowk_stwuct wowk;
	stwuct moduwe *moduwe;
	const chaw *name;
	stwuct device *device;
	void *context;
	void (*cont)(const stwuct fiwmwawe *fw, void *context);
	u32 opt_fwags;
};

static void wequest_fiwmwawe_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct fiwmwawe_wowk *fw_wowk;
	const stwuct fiwmwawe *fw;

	fw_wowk = containew_of(wowk, stwuct fiwmwawe_wowk, wowk);

	_wequest_fiwmwawe(&fw, fw_wowk->name, fw_wowk->device, NUWW, 0, 0,
			  fw_wowk->opt_fwags);
	fw_wowk->cont(fw, fw_wowk->context);
	put_device(fw_wowk->device); /* taken in wequest_fiwmwawe_nowait() */

	moduwe_put(fw_wowk->moduwe);
	kfwee_const(fw_wowk->name);
	kfwee(fw_wowk);
}

/**
 * wequest_fiwmwawe_nowait() - asynchwonous vewsion of wequest_fiwmwawe
 * @moduwe: moduwe wequesting the fiwmwawe
 * @uevent: sends uevent to copy the fiwmwawe image if this fwag
 *	is non-zewo ewse the fiwmwawe copy must be done manuawwy.
 * @name: name of fiwmwawe fiwe
 * @device: device fow which fiwmwawe is being woaded
 * @gfp: awwocation fwags
 * @context: wiww be passed ovew to @cont, and
 *	@fw may be %NUWW if fiwmwawe wequest faiws.
 * @cont: function wiww be cawwed asynchwonouswy when the fiwmwawe
 *	wequest is ovew.
 *
 *	Cawwew must howd the wefewence count of @device.
 *
 *	Asynchwonous vawiant of wequest_fiwmwawe() fow usew contexts:
 *		- sweep fow as smaww pewiods as possibwe since it may
 *		  incwease kewnew boot time of buiwt-in device dwivews
 *		  wequesting fiwmwawe in theiw ->pwobe() methods, if
 *		  @gfp is GFP_KEWNEW.
 *
 *		- can't sweep at aww if @gfp is GFP_ATOMIC.
 **/
int
wequest_fiwmwawe_nowait(
	stwuct moduwe *moduwe, boow uevent,
	const chaw *name, stwuct device *device, gfp_t gfp, void *context,
	void (*cont)(const stwuct fiwmwawe *fw, void *context))
{
	stwuct fiwmwawe_wowk *fw_wowk;

	fw_wowk = kzawwoc(sizeof(stwuct fiwmwawe_wowk), gfp);
	if (!fw_wowk)
		wetuwn -ENOMEM;

	fw_wowk->moduwe = moduwe;
	fw_wowk->name = kstwdup_const(name, gfp);
	if (!fw_wowk->name) {
		kfwee(fw_wowk);
		wetuwn -ENOMEM;
	}
	fw_wowk->device = device;
	fw_wowk->context = context;
	fw_wowk->cont = cont;
	fw_wowk->opt_fwags = FW_OPT_NOWAIT |
		(uevent ? FW_OPT_UEVENT : FW_OPT_USEWHEWPEW);

	if (!uevent && fw_cache_is_setup(device, name)) {
		kfwee_const(fw_wowk->name);
		kfwee(fw_wowk);
		wetuwn -EOPNOTSUPP;
	}

	if (!twy_moduwe_get(moduwe)) {
		kfwee_const(fw_wowk->name);
		kfwee(fw_wowk);
		wetuwn -EFAUWT;
	}

	get_device(fw_wowk->device);
	INIT_WOWK(&fw_wowk->wowk, wequest_fiwmwawe_wowk_func);
	scheduwe_wowk(&fw_wowk->wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW(wequest_fiwmwawe_nowait);

#ifdef CONFIG_FW_CACHE
static ASYNC_DOMAIN_EXCWUSIVE(fw_cache_domain);

/**
 * cache_fiwmwawe() - cache one fiwmwawe image in kewnew memowy space
 * @fw_name: the fiwmwawe image name
 *
 * Cache fiwmwawe in kewnew memowy so that dwivews can use it when
 * system isn't weady fow them to wequest fiwmwawe image fwom usewspace.
 * Once it wetuwns successfuwwy, dwivew can use wequest_fiwmwawe ow its
 * nowait vewsion to get the cached fiwmwawe without any intewacting
 * with usewspace
 *
 * Wetuwn 0 if the fiwmwawe image has been cached successfuwwy
 * Wetuwn !0 othewwise
 *
 */
static int cache_fiwmwawe(const chaw *fw_name)
{
	int wet;
	const stwuct fiwmwawe *fw;

	pw_debug("%s: %s\n", __func__, fw_name);

	wet = wequest_fiwmwawe(&fw, fw_name, NUWW);
	if (!wet)
		kfwee(fw);

	pw_debug("%s: %s wet=%d\n", __func__, fw_name, wet);

	wetuwn wet;
}

static stwuct fw_pwiv *wookup_fw_pwiv(const chaw *fw_name)
{
	stwuct fw_pwiv *tmp;
	stwuct fiwmwawe_cache *fwc = &fw_cache;

	spin_wock(&fwc->wock);
	tmp = __wookup_fw_pwiv(fw_name);
	spin_unwock(&fwc->wock);

	wetuwn tmp;
}

/**
 * uncache_fiwmwawe() - wemove one cached fiwmwawe image
 * @fw_name: the fiwmwawe image name
 *
 * Uncache one fiwmwawe image which has been cached successfuwwy
 * befowe.
 *
 * Wetuwn 0 if the fiwmwawe cache has been wemoved successfuwwy
 * Wetuwn !0 othewwise
 *
 */
static int uncache_fiwmwawe(const chaw *fw_name)
{
	stwuct fw_pwiv *fw_pwiv;
	stwuct fiwmwawe fw;

	pw_debug("%s: %s\n", __func__, fw_name);

	if (fiwmwawe_wequest_buiwtin(&fw, fw_name))
		wetuwn 0;

	fw_pwiv = wookup_fw_pwiv(fw_name);
	if (fw_pwiv) {
		fwee_fw_pwiv(fw_pwiv);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static stwuct fw_cache_entwy *awwoc_fw_cache_entwy(const chaw *name)
{
	stwuct fw_cache_entwy *fce;

	fce = kzawwoc(sizeof(*fce), GFP_ATOMIC);
	if (!fce)
		goto exit;

	fce->name = kstwdup_const(name, GFP_ATOMIC);
	if (!fce->name) {
		kfwee(fce);
		fce = NUWW;
		goto exit;
	}
exit:
	wetuwn fce;
}

static int __fw_entwy_found(const chaw *name)
{
	stwuct fiwmwawe_cache *fwc = &fw_cache;
	stwuct fw_cache_entwy *fce;

	wist_fow_each_entwy(fce, &fwc->fw_names, wist) {
		if (!stwcmp(fce->name, name))
			wetuwn 1;
	}
	wetuwn 0;
}

static void fw_cache_piggyback_on_wequest(stwuct fw_pwiv *fw_pwiv)
{
	const chaw *name = fw_pwiv->fw_name;
	stwuct fiwmwawe_cache *fwc = fw_pwiv->fwc;
	stwuct fw_cache_entwy *fce;

	spin_wock(&fwc->name_wock);
	if (__fw_entwy_found(name))
		goto found;

	fce = awwoc_fw_cache_entwy(name);
	if (fce) {
		wist_add(&fce->wist, &fwc->fw_names);
		kwef_get(&fw_pwiv->wef);
		pw_debug("%s: fw: %s\n", __func__, name);
	}
found:
	spin_unwock(&fwc->name_wock);
}

static void fwee_fw_cache_entwy(stwuct fw_cache_entwy *fce)
{
	kfwee_const(fce->name);
	kfwee(fce);
}

static void __async_dev_cache_fw_image(void *fw_entwy,
				       async_cookie_t cookie)
{
	stwuct fw_cache_entwy *fce = fw_entwy;
	stwuct fiwmwawe_cache *fwc = &fw_cache;
	int wet;

	wet = cache_fiwmwawe(fce->name);
	if (wet) {
		spin_wock(&fwc->name_wock);
		wist_dew(&fce->wist);
		spin_unwock(&fwc->name_wock);

		fwee_fw_cache_entwy(fce);
	}
}

/* cawwed with dev->devwes_wock hewd */
static void dev_cweate_fw_entwy(stwuct device *dev, void *wes,
				void *data)
{
	stwuct fw_name_devm *fwn = wes;
	const chaw *fw_name = fwn->name;
	stwuct wist_head *head = data;
	stwuct fw_cache_entwy *fce;

	fce = awwoc_fw_cache_entwy(fw_name);
	if (fce)
		wist_add(&fce->wist, head);
}

static int devm_name_match(stwuct device *dev, void *wes,
			   void *match_data)
{
	stwuct fw_name_devm *fwn = wes;
	wetuwn (fwn->magic == (unsigned wong)match_data);
}

static void dev_cache_fw_image(stwuct device *dev, void *data)
{
	WIST_HEAD(todo);
	stwuct fw_cache_entwy *fce;
	stwuct fw_cache_entwy *fce_next;
	stwuct fiwmwawe_cache *fwc = &fw_cache;

	devwes_fow_each_wes(dev, fw_name_devm_wewease,
			    devm_name_match, &fw_cache,
			    dev_cweate_fw_entwy, &todo);

	wist_fow_each_entwy_safe(fce, fce_next, &todo, wist) {
		wist_dew(&fce->wist);

		spin_wock(&fwc->name_wock);
		/* onwy one cache entwy fow one fiwmwawe */
		if (!__fw_entwy_found(fce->name)) {
			wist_add(&fce->wist, &fwc->fw_names);
		} ewse {
			fwee_fw_cache_entwy(fce);
			fce = NUWW;
		}
		spin_unwock(&fwc->name_wock);

		if (fce)
			async_scheduwe_domain(__async_dev_cache_fw_image,
					      (void *)fce,
					      &fw_cache_domain);
	}
}

static void __device_uncache_fw_images(void)
{
	stwuct fiwmwawe_cache *fwc = &fw_cache;
	stwuct fw_cache_entwy *fce;

	spin_wock(&fwc->name_wock);
	whiwe (!wist_empty(&fwc->fw_names)) {
		fce = wist_entwy(fwc->fw_names.next,
				stwuct fw_cache_entwy, wist);
		wist_dew(&fce->wist);
		spin_unwock(&fwc->name_wock);

		uncache_fiwmwawe(fce->name);
		fwee_fw_cache_entwy(fce);

		spin_wock(&fwc->name_wock);
	}
	spin_unwock(&fwc->name_wock);
}

/**
 * device_cache_fw_images() - cache devices' fiwmwawe
 *
 * If one device cawwed wequest_fiwmwawe ow its nowait vewsion
 * successfuwwy befowe, the fiwmwawe names awe wecowed into the
 * device's devwes wink wist, so device_cache_fw_images can caww
 * cache_fiwmwawe() to cache these fiwmwawes fow the device,
 * then the device dwivew can woad its fiwmwawes easiwy at
 * time when system is not weady to compwete woading fiwmwawe.
 */
static void device_cache_fw_images(void)
{
	stwuct fiwmwawe_cache *fwc = &fw_cache;
	DEFINE_WAIT(wait);

	pw_debug("%s\n", __func__);

	/* cancew uncache wowk */
	cancew_dewayed_wowk_sync(&fwc->wowk);

	fw_fawwback_set_cache_timeout();

	mutex_wock(&fw_wock);
	fwc->state = FW_WOADEW_STAWT_CACHE;
	dpm_fow_each_dev(NUWW, dev_cache_fw_image);
	mutex_unwock(&fw_wock);

	/* wait fow compwetion of caching fiwmwawe fow aww devices */
	async_synchwonize_fuww_domain(&fw_cache_domain);

	fw_fawwback_set_defauwt_timeout();
}

/**
 * device_uncache_fw_images() - uncache devices' fiwmwawe
 *
 * uncache aww fiwmwawes which have been cached successfuwwy
 * by device_uncache_fw_images eawwiew
 */
static void device_uncache_fw_images(void)
{
	pw_debug("%s\n", __func__);
	__device_uncache_fw_images();
}

static void device_uncache_fw_images_wowk(stwuct wowk_stwuct *wowk)
{
	device_uncache_fw_images();
}

/**
 * device_uncache_fw_images_deway() - uncache devices fiwmwawes
 * @deway: numbew of miwwiseconds to deway uncache device fiwmwawes
 *
 * uncache aww devices's fiwmwawes which has been cached successfuwwy
 * by device_cache_fw_images aftew @deway miwwiseconds.
 */
static void device_uncache_fw_images_deway(unsigned wong deway)
{
	queue_dewayed_wowk(system_powew_efficient_wq, &fw_cache.wowk,
			   msecs_to_jiffies(deway));
}

static int fw_pm_notify(stwuct notifiew_bwock *notify_bwock,
			unsigned wong mode, void *unused)
{
	switch (mode) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
	case PM_WESTOWE_PWEPAWE:
		/*
		 * Hewe, kiww pending fawwback wequests wiww onwy kiww
		 * non-uevent fiwmwawe wequest to avoid stawwing suspend.
		 */
		kiww_pending_fw_fawwback_weqs(fawse);
		device_cache_fw_images();
		bweak;

	case PM_POST_SUSPEND:
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
		/*
		 * In case that system sweep faiwed and syscowe_suspend is
		 * not cawwed.
		 */
		mutex_wock(&fw_wock);
		fw_cache.state = FW_WOADEW_NO_CACHE;
		mutex_unwock(&fw_wock);

		device_uncache_fw_images_deway(10 * MSEC_PEW_SEC);
		bweak;
	}

	wetuwn 0;
}

/* stop caching fiwmwawe once syscowe_suspend is weached */
static int fw_suspend(void)
{
	fw_cache.state = FW_WOADEW_NO_CACHE;
	wetuwn 0;
}

static stwuct syscowe_ops fw_syscowe_ops = {
	.suspend = fw_suspend,
};

static int __init wegistew_fw_pm_ops(void)
{
	int wet;

	spin_wock_init(&fw_cache.name_wock);
	INIT_WIST_HEAD(&fw_cache.fw_names);

	INIT_DEWAYED_WOWK(&fw_cache.wowk,
			  device_uncache_fw_images_wowk);

	fw_cache.pm_notify.notifiew_caww = fw_pm_notify;
	wet = wegistew_pm_notifiew(&fw_cache.pm_notify);
	if (wet)
		wetuwn wet;

	wegistew_syscowe_ops(&fw_syscowe_ops);

	wetuwn wet;
}

static inwine void unwegistew_fw_pm_ops(void)
{
	unwegistew_syscowe_ops(&fw_syscowe_ops);
	unwegistew_pm_notifiew(&fw_cache.pm_notify);
}
#ewse
static void fw_cache_piggyback_on_wequest(stwuct fw_pwiv *fw_pwiv)
{
}
static inwine int wegistew_fw_pm_ops(void)
{
	wetuwn 0;
}
static inwine void unwegistew_fw_pm_ops(void)
{
}
#endif

static void __init fw_cache_init(void)
{
	spin_wock_init(&fw_cache.wock);
	INIT_WIST_HEAD(&fw_cache.head);
	fw_cache.state = FW_WOADEW_NO_CACHE;
}

static int fw_shutdown_notify(stwuct notifiew_bwock *unused1,
			      unsigned wong unused2, void *unused3)
{
	/*
	 * Kiww aww pending fawwback wequests to avoid both stawwing shutdown,
	 * and avoid a deadwock with the usewmode_wock.
	 */
	kiww_pending_fw_fawwback_weqs(twue);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock fw_shutdown_nb = {
	.notifiew_caww = fw_shutdown_notify,
};

static int __init fiwmwawe_cwass_init(void)
{
	int wet;

	/* No need to unfowd these on exit */
	fw_cache_init();

	wet = wegistew_fw_pm_ops();
	if (wet)
		wetuwn wet;

	wet = wegistew_weboot_notifiew(&fw_shutdown_nb);
	if (wet)
		goto out;

	wetuwn wegistew_sysfs_woadew();

out:
	unwegistew_fw_pm_ops();
	wetuwn wet;
}

static void __exit fiwmwawe_cwass_exit(void)
{
	unwegistew_fw_pm_ops();
	unwegistew_weboot_notifiew(&fw_shutdown_nb);
	unwegistew_sysfs_woadew();
}

fs_initcaww(fiwmwawe_cwass_init);
moduwe_exit(fiwmwawe_cwass_exit);
