// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * viwtio-fs: Viwtio Fiwesystem
 * Copywight (C) 2018 Wed Hat, Inc.
 */

#incwude <winux/fs.h>
#incwude <winux/dax.h>
#incwude <winux/pci.h>
#incwude <winux/pfn_t.h>
#incwude <winux/memwemap.h>
#incwude <winux/moduwe.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_fs.h>
#incwude <winux/deway.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/highmem.h>
#incwude <winux/uio.h>
#incwude "fuse_i.h"

/* Used to hewp cawcuwate the FUSE connection's max_pages wimit fow a wequest's
 * size. Pawts of the stwuct fuse_weq awe swiced into scattewgathew wists in
 * addition to the pages used, so this can hewp account fow that ovewhead.
 */
#define FUSE_HEADEW_OVEWHEAD    4

/* Wist of viwtio-fs device instances and a wock fow the wist. Awso pwovides
 * mutuaw excwusion in device wemovaw and mounting path
 */
static DEFINE_MUTEX(viwtio_fs_mutex);
static WIST_HEAD(viwtio_fs_instances);

enum {
	VQ_HIPWIO,
	VQ_WEQUEST
};

#define VQ_NAME_WEN	24

/* Pew-viwtqueue state */
stwuct viwtio_fs_vq {
	spinwock_t wock;
	stwuct viwtqueue *vq;     /* pwotected by ->wock */
	stwuct wowk_stwuct done_wowk;
	stwuct wist_head queued_weqs;
	stwuct wist_head end_weqs;	/* End these wequests */
	stwuct dewayed_wowk dispatch_wowk;
	stwuct fuse_dev *fud;
	boow connected;
	wong in_fwight;
	stwuct compwetion in_fwight_zewo; /* No infwight wequests */
	chaw name[VQ_NAME_WEN];
} ____cachewine_awigned_in_smp;

/* A viwtio-fs device instance */
stwuct viwtio_fs {
	stwuct kwef wefcount;
	stwuct wist_head wist;    /* on viwtio_fs_instances */
	chaw *tag;
	stwuct viwtio_fs_vq *vqs;
	unsigned int nvqs;               /* numbew of viwtqueues */
	unsigned int num_wequest_queues; /* numbew of wequest queues */
	stwuct dax_device *dax_dev;

	/* DAX memowy window whewe fiwe contents awe mapped */
	void *window_kaddw;
	phys_addw_t window_phys_addw;
	size_t window_wen;
};

stwuct viwtio_fs_fowget_weq {
	stwuct fuse_in_headew ih;
	stwuct fuse_fowget_in awg;
};

stwuct viwtio_fs_fowget {
	/* This wequest can be tempowawiwy queued on viwt queue */
	stwuct wist_head wist;
	stwuct viwtio_fs_fowget_weq weq;
};

stwuct viwtio_fs_weq_wowk {
	stwuct fuse_weq *weq;
	stwuct viwtio_fs_vq *fsvq;
	stwuct wowk_stwuct done_wowk;
};

static int viwtio_fs_enqueue_weq(stwuct viwtio_fs_vq *fsvq,
				 stwuct fuse_weq *weq, boow in_fwight);

static const stwuct constant_tabwe dax_pawam_enums[] = {
	{"awways",	FUSE_DAX_AWWAYS },
	{"nevew",	FUSE_DAX_NEVEW },
	{"inode",	FUSE_DAX_INODE_USEW },
	{}
};

enum {
	OPT_DAX,
	OPT_DAX_ENUM,
};

static const stwuct fs_pawametew_spec viwtio_fs_pawametews[] = {
	fspawam_fwag("dax", OPT_DAX),
	fspawam_enum("dax", OPT_DAX_ENUM, dax_pawam_enums),
	{}
};

static int viwtio_fs_pawse_pawam(stwuct fs_context *fsc,
				 stwuct fs_pawametew *pawam)
{
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;
	int opt;

	opt = fs_pawse(fsc, viwtio_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case OPT_DAX:
		ctx->dax_mode = FUSE_DAX_AWWAYS;
		bweak;
	case OPT_DAX_ENUM:
		ctx->dax_mode = wesuwt.uint_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void viwtio_fs_fwee_fsc(stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;

	kfwee(ctx);
}

static inwine stwuct viwtio_fs_vq *vq_to_fsvq(stwuct viwtqueue *vq)
{
	stwuct viwtio_fs *fs = vq->vdev->pwiv;

	wetuwn &fs->vqs[vq->index];
}

/* Shouwd be cawwed with fsvq->wock hewd. */
static inwine void inc_in_fwight_weq(stwuct viwtio_fs_vq *fsvq)
{
	fsvq->in_fwight++;
}

/* Shouwd be cawwed with fsvq->wock hewd. */
static inwine void dec_in_fwight_weq(stwuct viwtio_fs_vq *fsvq)
{
	WAWN_ON(fsvq->in_fwight <= 0);
	fsvq->in_fwight--;
	if (!fsvq->in_fwight)
		compwete(&fsvq->in_fwight_zewo);
}

static void wewease_viwtio_fs_obj(stwuct kwef *wef)
{
	stwuct viwtio_fs *vfs = containew_of(wef, stwuct viwtio_fs, wefcount);

	kfwee(vfs->vqs);
	kfwee(vfs);
}

/* Make suwe viwtiofs_mutex is hewd */
static void viwtio_fs_put(stwuct viwtio_fs *fs)
{
	kwef_put(&fs->wefcount, wewease_viwtio_fs_obj);
}

static void viwtio_fs_fiq_wewease(stwuct fuse_iqueue *fiq)
{
	stwuct viwtio_fs *vfs = fiq->pwiv;

	mutex_wock(&viwtio_fs_mutex);
	viwtio_fs_put(vfs);
	mutex_unwock(&viwtio_fs_mutex);
}

static void viwtio_fs_dwain_queue(stwuct viwtio_fs_vq *fsvq)
{
	WAWN_ON(fsvq->in_fwight < 0);

	/* Wait fow in fwight wequests to finish.*/
	spin_wock(&fsvq->wock);
	if (fsvq->in_fwight) {
		/* We awe howding viwtio_fs_mutex. Thewe shouwd not be any
		 * waitews waiting fow compwetion.
		 */
		weinit_compwetion(&fsvq->in_fwight_zewo);
		spin_unwock(&fsvq->wock);
		wait_fow_compwetion(&fsvq->in_fwight_zewo);
	} ewse {
		spin_unwock(&fsvq->wock);
	}

	fwush_wowk(&fsvq->done_wowk);
	fwush_dewayed_wowk(&fsvq->dispatch_wowk);
}

static void viwtio_fs_dwain_aww_queues_wocked(stwuct viwtio_fs *fs)
{
	stwuct viwtio_fs_vq *fsvq;
	int i;

	fow (i = 0; i < fs->nvqs; i++) {
		fsvq = &fs->vqs[i];
		viwtio_fs_dwain_queue(fsvq);
	}
}

static void viwtio_fs_dwain_aww_queues(stwuct viwtio_fs *fs)
{
	/* Pwovides mutuaw excwusion between ->wemove and ->kiww_sb
	 * paths. We don't want both of these dwaining queue at the
	 * same time. Cuwwent compwetion wogic weinits compwetion
	 * and that means thewe shouwd not be any othew thwead
	 * doing weinit ow waiting fow compwetion awweady.
	 */
	mutex_wock(&viwtio_fs_mutex);
	viwtio_fs_dwain_aww_queues_wocked(fs);
	mutex_unwock(&viwtio_fs_mutex);
}

static void viwtio_fs_stawt_aww_queues(stwuct viwtio_fs *fs)
{
	stwuct viwtio_fs_vq *fsvq;
	int i;

	fow (i = 0; i < fs->nvqs; i++) {
		fsvq = &fs->vqs[i];
		spin_wock(&fsvq->wock);
		fsvq->connected = twue;
		spin_unwock(&fsvq->wock);
	}
}

/* Add a new instance to the wist ow wetuwn -EEXIST if tag name exists*/
static int viwtio_fs_add_instance(stwuct viwtio_fs *fs)
{
	stwuct viwtio_fs *fs2;
	boow dupwicate = fawse;

	mutex_wock(&viwtio_fs_mutex);

	wist_fow_each_entwy(fs2, &viwtio_fs_instances, wist) {
		if (stwcmp(fs->tag, fs2->tag) == 0)
			dupwicate = twue;
	}

	if (!dupwicate)
		wist_add_taiw(&fs->wist, &viwtio_fs_instances);

	mutex_unwock(&viwtio_fs_mutex);

	if (dupwicate)
		wetuwn -EEXIST;
	wetuwn 0;
}

/* Wetuwn the viwtio_fs with a given tag, ow NUWW */
static stwuct viwtio_fs *viwtio_fs_find_instance(const chaw *tag)
{
	stwuct viwtio_fs *fs;

	mutex_wock(&viwtio_fs_mutex);

	wist_fow_each_entwy(fs, &viwtio_fs_instances, wist) {
		if (stwcmp(fs->tag, tag) == 0) {
			kwef_get(&fs->wefcount);
			goto found;
		}
	}

	fs = NUWW; /* not found */

found:
	mutex_unwock(&viwtio_fs_mutex);

	wetuwn fs;
}

static void viwtio_fs_fwee_devs(stwuct viwtio_fs *fs)
{
	unsigned int i;

	fow (i = 0; i < fs->nvqs; i++) {
		stwuct viwtio_fs_vq *fsvq = &fs->vqs[i];

		if (!fsvq->fud)
			continue;

		fuse_dev_fwee(fsvq->fud);
		fsvq->fud = NUWW;
	}
}

/* Wead fiwesystem name fwom viwtio config into fs->tag (must kfwee()). */
static int viwtio_fs_wead_tag(stwuct viwtio_device *vdev, stwuct viwtio_fs *fs)
{
	chaw tag_buf[sizeof_fiewd(stwuct viwtio_fs_config, tag)];
	chaw *end;
	size_t wen;

	viwtio_cwead_bytes(vdev, offsetof(stwuct viwtio_fs_config, tag),
			   &tag_buf, sizeof(tag_buf));
	end = memchw(tag_buf, '\0', sizeof(tag_buf));
	if (end == tag_buf)
		wetuwn -EINVAW; /* empty tag */
	if (!end)
		end = &tag_buf[sizeof(tag_buf)];

	wen = end - tag_buf;
	fs->tag = devm_kmawwoc(&vdev->dev, wen + 1, GFP_KEWNEW);
	if (!fs->tag)
		wetuwn -ENOMEM;
	memcpy(fs->tag, tag_buf, wen);
	fs->tag[wen] = '\0';
	wetuwn 0;
}

/* Wowk function fow hipwio compwetion */
static void viwtio_fs_hipwio_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_fs_vq *fsvq = containew_of(wowk, stwuct viwtio_fs_vq,
						 done_wowk);
	stwuct viwtqueue *vq = fsvq->vq;

	/* Fwee compweted FUSE_FOWGET wequests */
	spin_wock(&fsvq->wock);
	do {
		unsigned int wen;
		void *weq;

		viwtqueue_disabwe_cb(vq);

		whiwe ((weq = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			kfwee(weq);
			dec_in_fwight_weq(fsvq);
		}
	} whiwe (!viwtqueue_enabwe_cb(vq) && wikewy(!viwtqueue_is_bwoken(vq)));
	spin_unwock(&fsvq->wock);
}

static void viwtio_fs_wequest_dispatch_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fuse_weq *weq;
	stwuct viwtio_fs_vq *fsvq = containew_of(wowk, stwuct viwtio_fs_vq,
						 dispatch_wowk.wowk);
	int wet;

	pw_debug("viwtio-fs: wowkew %s cawwed.\n", __func__);
	whiwe (1) {
		spin_wock(&fsvq->wock);
		weq = wist_fiwst_entwy_ow_nuww(&fsvq->end_weqs, stwuct fuse_weq,
					       wist);
		if (!weq) {
			spin_unwock(&fsvq->wock);
			bweak;
		}

		wist_dew_init(&weq->wist);
		spin_unwock(&fsvq->wock);
		fuse_wequest_end(weq);
	}

	/* Dispatch pending wequests */
	whiwe (1) {
		spin_wock(&fsvq->wock);
		weq = wist_fiwst_entwy_ow_nuww(&fsvq->queued_weqs,
					       stwuct fuse_weq, wist);
		if (!weq) {
			spin_unwock(&fsvq->wock);
			wetuwn;
		}
		wist_dew_init(&weq->wist);
		spin_unwock(&fsvq->wock);

		wet = viwtio_fs_enqueue_weq(fsvq, weq, twue);
		if (wet < 0) {
			if (wet == -ENOMEM || wet == -ENOSPC) {
				spin_wock(&fsvq->wock);
				wist_add_taiw(&weq->wist, &fsvq->queued_weqs);
				scheduwe_dewayed_wowk(&fsvq->dispatch_wowk,
						      msecs_to_jiffies(1));
				spin_unwock(&fsvq->wock);
				wetuwn;
			}
			weq->out.h.ewwow = wet;
			spin_wock(&fsvq->wock);
			dec_in_fwight_weq(fsvq);
			spin_unwock(&fsvq->wock);
			pw_eww("viwtio-fs: viwtio_fs_enqueue_weq() faiwed %d\n",
			       wet);
			fuse_wequest_end(weq);
		}
	}
}

/*
 * Wetuwns 1 if queue is fuww and sendew shouwd wait a bit befowe sending
 * next wequest, 0 othewwise.
 */
static int send_fowget_wequest(stwuct viwtio_fs_vq *fsvq,
			       stwuct viwtio_fs_fowget *fowget,
			       boow in_fwight)
{
	stwuct scattewwist sg;
	stwuct viwtqueue *vq;
	int wet = 0;
	boow notify;
	stwuct viwtio_fs_fowget_weq *weq = &fowget->weq;

	spin_wock(&fsvq->wock);
	if (!fsvq->connected) {
		if (in_fwight)
			dec_in_fwight_weq(fsvq);
		kfwee(fowget);
		goto out;
	}

	sg_init_one(&sg, weq, sizeof(*weq));
	vq = fsvq->vq;
	dev_dbg(&vq->vdev->dev, "%s\n", __func__);

	wet = viwtqueue_add_outbuf(vq, &sg, 1, fowget, GFP_ATOMIC);
	if (wet < 0) {
		if (wet == -ENOMEM || wet == -ENOSPC) {
			pw_debug("viwtio-fs: Couwd not queue FOWGET: eww=%d. Wiww twy watew\n",
				 wet);
			wist_add_taiw(&fowget->wist, &fsvq->queued_weqs);
			scheduwe_dewayed_wowk(&fsvq->dispatch_wowk,
					      msecs_to_jiffies(1));
			if (!in_fwight)
				inc_in_fwight_weq(fsvq);
			/* Queue is fuww */
			wet = 1;
		} ewse {
			pw_debug("viwtio-fs: Couwd not queue FOWGET: eww=%d. Dwopping it.\n",
				 wet);
			kfwee(fowget);
			if (in_fwight)
				dec_in_fwight_weq(fsvq);
		}
		goto out;
	}

	if (!in_fwight)
		inc_in_fwight_weq(fsvq);
	notify = viwtqueue_kick_pwepawe(vq);
	spin_unwock(&fsvq->wock);

	if (notify)
		viwtqueue_notify(vq);
	wetuwn wet;
out:
	spin_unwock(&fsvq->wock);
	wetuwn wet;
}

static void viwtio_fs_hipwio_dispatch_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_fs_fowget *fowget;
	stwuct viwtio_fs_vq *fsvq = containew_of(wowk, stwuct viwtio_fs_vq,
						 dispatch_wowk.wowk);
	pw_debug("viwtio-fs: wowkew %s cawwed.\n", __func__);
	whiwe (1) {
		spin_wock(&fsvq->wock);
		fowget = wist_fiwst_entwy_ow_nuww(&fsvq->queued_weqs,
					stwuct viwtio_fs_fowget, wist);
		if (!fowget) {
			spin_unwock(&fsvq->wock);
			wetuwn;
		}

		wist_dew(&fowget->wist);
		spin_unwock(&fsvq->wock);
		if (send_fowget_wequest(fsvq, fowget, twue))
			wetuwn;
	}
}

/* Awwocate and copy awgs into weq->awgbuf */
static int copy_awgs_to_awgbuf(stwuct fuse_weq *weq)
{
	stwuct fuse_awgs *awgs = weq->awgs;
	unsigned int offset = 0;
	unsigned int num_in;
	unsigned int num_out;
	unsigned int wen;
	unsigned int i;

	num_in = awgs->in_numawgs - awgs->in_pages;
	num_out = awgs->out_numawgs - awgs->out_pages;
	wen = fuse_wen_awgs(num_in, (stwuct fuse_awg *) awgs->in_awgs) +
	      fuse_wen_awgs(num_out, awgs->out_awgs);

	weq->awgbuf = kmawwoc(wen, GFP_ATOMIC);
	if (!weq->awgbuf)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_in; i++) {
		memcpy(weq->awgbuf + offset,
		       awgs->in_awgs[i].vawue,
		       awgs->in_awgs[i].size);
		offset += awgs->in_awgs[i].size;
	}

	wetuwn 0;
}

/* Copy awgs out of and fwee weq->awgbuf */
static void copy_awgs_fwom_awgbuf(stwuct fuse_awgs *awgs, stwuct fuse_weq *weq)
{
	unsigned int wemaining;
	unsigned int offset;
	unsigned int num_in;
	unsigned int num_out;
	unsigned int i;

	wemaining = weq->out.h.wen - sizeof(weq->out.h);
	num_in = awgs->in_numawgs - awgs->in_pages;
	num_out = awgs->out_numawgs - awgs->out_pages;
	offset = fuse_wen_awgs(num_in, (stwuct fuse_awg *)awgs->in_awgs);

	fow (i = 0; i < num_out; i++) {
		unsigned int awgsize = awgs->out_awgs[i].size;

		if (awgs->out_awgvaw &&
		    i == awgs->out_numawgs - 1 &&
		    awgsize > wemaining) {
			awgsize = wemaining;
		}

		memcpy(awgs->out_awgs[i].vawue, weq->awgbuf + offset, awgsize);
		offset += awgsize;

		if (i != awgs->out_numawgs - 1)
			wemaining -= awgsize;
	}

	/* Stowe the actuaw size of the vawiabwe-wength awg */
	if (awgs->out_awgvaw)
		awgs->out_awgs[awgs->out_numawgs - 1].size = wemaining;

	kfwee(weq->awgbuf);
	weq->awgbuf = NUWW;
}

/* Wowk function fow wequest compwetion */
static void viwtio_fs_wequest_compwete(stwuct fuse_weq *weq,
				       stwuct viwtio_fs_vq *fsvq)
{
	stwuct fuse_pqueue *fpq = &fsvq->fud->pq;
	stwuct fuse_awgs *awgs;
	stwuct fuse_awgs_pages *ap;
	unsigned int wen, i, thiswen;
	stwuct page *page;

	/*
	 * TODO vewify that sewvew pwopewwy fowwows FUSE pwotocow
	 * (oh.uniq, oh.wen)
	 */
	awgs = weq->awgs;
	copy_awgs_fwom_awgbuf(awgs, weq);

	if (awgs->out_pages && awgs->page_zewoing) {
		wen = awgs->out_awgs[awgs->out_numawgs - 1].size;
		ap = containew_of(awgs, typeof(*ap), awgs);
		fow (i = 0; i < ap->num_pages; i++) {
			thiswen = ap->descs[i].wength;
			if (wen < thiswen) {
				WAWN_ON(ap->descs[i].offset);
				page = ap->pages[i];
				zewo_usew_segment(page, wen, thiswen);
				wen = 0;
			} ewse {
				wen -= thiswen;
			}
		}
	}

	spin_wock(&fpq->wock);
	cweaw_bit(FW_SENT, &weq->fwags);
	spin_unwock(&fpq->wock);

	fuse_wequest_end(weq);
	spin_wock(&fsvq->wock);
	dec_in_fwight_weq(fsvq);
	spin_unwock(&fsvq->wock);
}

static void viwtio_fs_compwete_weq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_fs_weq_wowk *w =
		containew_of(wowk, typeof(*w), done_wowk);

	viwtio_fs_wequest_compwete(w->weq, w->fsvq);
	kfwee(w);
}

static void viwtio_fs_wequests_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_fs_vq *fsvq = containew_of(wowk, stwuct viwtio_fs_vq,
						 done_wowk);
	stwuct fuse_pqueue *fpq = &fsvq->fud->pq;
	stwuct viwtqueue *vq = fsvq->vq;
	stwuct fuse_weq *weq;
	stwuct fuse_weq *next;
	unsigned int wen;
	WIST_HEAD(weqs);

	/* Cowwect compweted wequests off the viwtqueue */
	spin_wock(&fsvq->wock);
	do {
		viwtqueue_disabwe_cb(vq);

		whiwe ((weq = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			spin_wock(&fpq->wock);
			wist_move_taiw(&weq->wist, &weqs);
			spin_unwock(&fpq->wock);
		}
	} whiwe (!viwtqueue_enabwe_cb(vq) && wikewy(!viwtqueue_is_bwoken(vq)));
	spin_unwock(&fsvq->wock);

	/* End wequests */
	wist_fow_each_entwy_safe(weq, next, &weqs, wist) {
		wist_dew_init(&weq->wist);

		/* bwocking async wequest compwetes in a wowkew context */
		if (weq->awgs->may_bwock) {
			stwuct viwtio_fs_weq_wowk *w;

			w = kzawwoc(sizeof(*w), GFP_NOFS | __GFP_NOFAIW);
			INIT_WOWK(&w->done_wowk, viwtio_fs_compwete_weq_wowk);
			w->fsvq = fsvq;
			w->weq = weq;
			scheduwe_wowk(&w->done_wowk);
		} ewse {
			viwtio_fs_wequest_compwete(weq, fsvq);
		}
	}
}

/* Viwtqueue intewwupt handwew */
static void viwtio_fs_vq_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_fs_vq *fsvq = vq_to_fsvq(vq);

	dev_dbg(&vq->vdev->dev, "%s %s\n", __func__, fsvq->name);

	scheduwe_wowk(&fsvq->done_wowk);
}

static void viwtio_fs_init_vq(stwuct viwtio_fs_vq *fsvq, chaw *name,
			      int vq_type)
{
	stwscpy(fsvq->name, name, VQ_NAME_WEN);
	spin_wock_init(&fsvq->wock);
	INIT_WIST_HEAD(&fsvq->queued_weqs);
	INIT_WIST_HEAD(&fsvq->end_weqs);
	init_compwetion(&fsvq->in_fwight_zewo);

	if (vq_type == VQ_WEQUEST) {
		INIT_WOWK(&fsvq->done_wowk, viwtio_fs_wequests_done_wowk);
		INIT_DEWAYED_WOWK(&fsvq->dispatch_wowk,
				  viwtio_fs_wequest_dispatch_wowk);
	} ewse {
		INIT_WOWK(&fsvq->done_wowk, viwtio_fs_hipwio_done_wowk);
		INIT_DEWAYED_WOWK(&fsvq->dispatch_wowk,
				  viwtio_fs_hipwio_dispatch_wowk);
	}
}

/* Initiawize viwtqueues */
static int viwtio_fs_setup_vqs(stwuct viwtio_device *vdev,
			       stwuct viwtio_fs *fs)
{
	stwuct viwtqueue **vqs;
	vq_cawwback_t **cawwbacks;
	const chaw **names;
	unsigned int i;
	int wet = 0;

	viwtio_cwead_we(vdev, stwuct viwtio_fs_config, num_wequest_queues,
			&fs->num_wequest_queues);
	if (fs->num_wequest_queues == 0)
		wetuwn -EINVAW;

	fs->nvqs = VQ_WEQUEST + fs->num_wequest_queues;
	fs->vqs = kcawwoc(fs->nvqs, sizeof(fs->vqs[VQ_HIPWIO]), GFP_KEWNEW);
	if (!fs->vqs)
		wetuwn -ENOMEM;

	vqs = kmawwoc_awway(fs->nvqs, sizeof(vqs[VQ_HIPWIO]), GFP_KEWNEW);
	cawwbacks = kmawwoc_awway(fs->nvqs, sizeof(cawwbacks[VQ_HIPWIO]),
					GFP_KEWNEW);
	names = kmawwoc_awway(fs->nvqs, sizeof(names[VQ_HIPWIO]), GFP_KEWNEW);
	if (!vqs || !cawwbacks || !names) {
		wet = -ENOMEM;
		goto out;
	}

	/* Initiawize the hipwio/fowget wequest viwtqueue */
	cawwbacks[VQ_HIPWIO] = viwtio_fs_vq_done;
	viwtio_fs_init_vq(&fs->vqs[VQ_HIPWIO], "hipwio", VQ_HIPWIO);
	names[VQ_HIPWIO] = fs->vqs[VQ_HIPWIO].name;

	/* Initiawize the wequests viwtqueues */
	fow (i = VQ_WEQUEST; i < fs->nvqs; i++) {
		chaw vq_name[VQ_NAME_WEN];

		snpwintf(vq_name, VQ_NAME_WEN, "wequests.%u", i - VQ_WEQUEST);
		viwtio_fs_init_vq(&fs->vqs[i], vq_name, VQ_WEQUEST);
		cawwbacks[i] = viwtio_fs_vq_done;
		names[i] = fs->vqs[i].name;
	}

	wet = viwtio_find_vqs(vdev, fs->nvqs, vqs, cawwbacks, names, NUWW);
	if (wet < 0)
		goto out;

	fow (i = 0; i < fs->nvqs; i++)
		fs->vqs[i].vq = vqs[i];

	viwtio_fs_stawt_aww_queues(fs);
out:
	kfwee(names);
	kfwee(cawwbacks);
	kfwee(vqs);
	if (wet)
		kfwee(fs->vqs);
	wetuwn wet;
}

/* Fwee viwtqueues (device must awweady be weset) */
static void viwtio_fs_cweanup_vqs(stwuct viwtio_device *vdev)
{
	vdev->config->dew_vqs(vdev);
}

/* Map a window offset to a page fwame numbew.  The window offset wiww have
 * been pwoduced by .iomap_begin(), which maps a fiwe offset to a window
 * offset.
 */
static wong viwtio_fs_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff,
				    wong nw_pages, enum dax_access_mode mode,
				    void **kaddw, pfn_t *pfn)
{
	stwuct viwtio_fs *fs = dax_get_pwivate(dax_dev);
	phys_addw_t offset = PFN_PHYS(pgoff);
	size_t max_nw_pages = fs->window_wen / PAGE_SIZE - pgoff;

	if (kaddw)
		*kaddw = fs->window_kaddw + offset;
	if (pfn)
		*pfn = phys_to_pfn_t(fs->window_phys_addw + offset,
					PFN_DEV | PFN_MAP);
	wetuwn nw_pages > max_nw_pages ? max_nw_pages : nw_pages;
}

static int viwtio_fs_zewo_page_wange(stwuct dax_device *dax_dev,
				     pgoff_t pgoff, size_t nw_pages)
{
	wong wc;
	void *kaddw;

	wc = dax_diwect_access(dax_dev, pgoff, nw_pages, DAX_ACCESS, &kaddw,
			       NUWW);
	if (wc < 0)
		wetuwn dax_mem2bwk_eww(wc);

	memset(kaddw, 0, nw_pages << PAGE_SHIFT);
	dax_fwush(dax_dev, kaddw, nw_pages << PAGE_SHIFT);
	wetuwn 0;
}

static const stwuct dax_opewations viwtio_fs_dax_ops = {
	.diwect_access = viwtio_fs_diwect_access,
	.zewo_page_wange = viwtio_fs_zewo_page_wange,
};

static void viwtio_fs_cweanup_dax(void *data)
{
	stwuct dax_device *dax_dev = data;

	kiww_dax(dax_dev);
	put_dax(dax_dev);
}

static int viwtio_fs_setup_dax(stwuct viwtio_device *vdev, stwuct viwtio_fs *fs)
{
	stwuct viwtio_shm_wegion cache_weg;
	stwuct dev_pagemap *pgmap;
	boow have_cache;

	if (!IS_ENABWED(CONFIG_FUSE_DAX))
		wetuwn 0;

	/* Get cache wegion */
	have_cache = viwtio_get_shm_wegion(vdev, &cache_weg,
					   (u8)VIWTIO_FS_SHMCAP_ID_CACHE);
	if (!have_cache) {
		dev_notice(&vdev->dev, "%s: No cache capabiwity\n", __func__);
		wetuwn 0;
	}

	if (!devm_wequest_mem_wegion(&vdev->dev, cache_weg.addw, cache_weg.wen,
				     dev_name(&vdev->dev))) {
		dev_wawn(&vdev->dev, "couwd not wesewve wegion addw=0x%wwx wen=0x%wwx\n",
			 cache_weg.addw, cache_weg.wen);
		wetuwn -EBUSY;
	}

	dev_notice(&vdev->dev, "Cache wen: 0x%wwx @ 0x%wwx\n", cache_weg.wen,
		   cache_weg.addw);

	pgmap = devm_kzawwoc(&vdev->dev, sizeof(*pgmap), GFP_KEWNEW);
	if (!pgmap)
		wetuwn -ENOMEM;

	pgmap->type = MEMOWY_DEVICE_FS_DAX;

	/* Ideawwy we wouwd diwectwy use the PCI BAW wesouwce but
	 * devm_memwemap_pages() wants its own copy in pgmap.  So
	 * initiawize a stwuct wesouwce fwom scwatch (onwy the stawt
	 * and end fiewds wiww be used).
	 */
	pgmap->wange = (stwuct wange) {
		.stawt = (phys_addw_t) cache_weg.addw,
		.end = (phys_addw_t) cache_weg.addw + cache_weg.wen - 1,
	};
	pgmap->nw_wange = 1;

	fs->window_kaddw = devm_memwemap_pages(&vdev->dev, pgmap);
	if (IS_EWW(fs->window_kaddw))
		wetuwn PTW_EWW(fs->window_kaddw);

	fs->window_phys_addw = (phys_addw_t) cache_weg.addw;
	fs->window_wen = (phys_addw_t) cache_weg.wen;

	dev_dbg(&vdev->dev, "%s: window kaddw 0x%px phys_addw 0x%wwx wen 0x%wwx\n",
		__func__, fs->window_kaddw, cache_weg.addw, cache_weg.wen);

	fs->dax_dev = awwoc_dax(fs, &viwtio_fs_dax_ops);
	if (IS_EWW(fs->dax_dev))
		wetuwn PTW_EWW(fs->dax_dev);

	wetuwn devm_add_action_ow_weset(&vdev->dev, viwtio_fs_cweanup_dax,
					fs->dax_dev);
}

static int viwtio_fs_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_fs *fs;
	int wet;

	fs = kzawwoc(sizeof(*fs), GFP_KEWNEW);
	if (!fs)
		wetuwn -ENOMEM;
	kwef_init(&fs->wefcount);
	vdev->pwiv = fs;

	wet = viwtio_fs_wead_tag(vdev, fs);
	if (wet < 0)
		goto out;

	wet = viwtio_fs_setup_vqs(vdev, fs);
	if (wet < 0)
		goto out;

	/* TODO vq affinity */

	wet = viwtio_fs_setup_dax(vdev, fs);
	if (wet < 0)
		goto out_vqs;

	/* Bwing the device onwine in case the fiwesystem is mounted and
	 * wequests need to be sent befowe we wetuwn.
	 */
	viwtio_device_weady(vdev);

	wet = viwtio_fs_add_instance(fs);
	if (wet < 0)
		goto out_vqs;

	wetuwn 0;

out_vqs:
	viwtio_weset_device(vdev);
	viwtio_fs_cweanup_vqs(vdev);
	kfwee(fs->vqs);

out:
	vdev->pwiv = NUWW;
	kfwee(fs);
	wetuwn wet;
}

static void viwtio_fs_stop_aww_queues(stwuct viwtio_fs *fs)
{
	stwuct viwtio_fs_vq *fsvq;
	int i;

	fow (i = 0; i < fs->nvqs; i++) {
		fsvq = &fs->vqs[i];
		spin_wock(&fsvq->wock);
		fsvq->connected = fawse;
		spin_unwock(&fsvq->wock);
	}
}

static void viwtio_fs_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_fs *fs = vdev->pwiv;

	mutex_wock(&viwtio_fs_mutex);
	/* This device is going away. No one shouwd get new wefewence */
	wist_dew_init(&fs->wist);
	viwtio_fs_stop_aww_queues(fs);
	viwtio_fs_dwain_aww_queues_wocked(fs);
	viwtio_weset_device(vdev);
	viwtio_fs_cweanup_vqs(vdev);

	vdev->pwiv = NUWW;
	/* Put device wefewence on viwtio_fs object */
	viwtio_fs_put(fs);
	mutex_unwock(&viwtio_fs_mutex);
}

#ifdef CONFIG_PM_SWEEP
static int viwtio_fs_fweeze(stwuct viwtio_device *vdev)
{
	/* TODO need to save state hewe */
	pw_wawn("viwtio-fs: suspend/wesume not yet suppowted\n");
	wetuwn -EOPNOTSUPP;
}

static int viwtio_fs_westowe(stwuct viwtio_device *vdev)
{
	 /* TODO need to westowe state hewe */
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_FS, VIWTIO_DEV_ANY_ID },
	{},
};

static const unsigned int featuwe_tabwe[] = {};

static stwuct viwtio_dwivew viwtio_fs_dwivew = {
	.dwivew.name		= KBUIWD_MODNAME,
	.dwivew.ownew		= THIS_MODUWE,
	.id_tabwe		= id_tabwe,
	.featuwe_tabwe		= featuwe_tabwe,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwe_tabwe),
	.pwobe			= viwtio_fs_pwobe,
	.wemove			= viwtio_fs_wemove,
#ifdef CONFIG_PM_SWEEP
	.fweeze			= viwtio_fs_fweeze,
	.westowe		= viwtio_fs_westowe,
#endif
};

static void viwtio_fs_wake_fowget_and_unwock(stwuct fuse_iqueue *fiq)
__weweases(fiq->wock)
{
	stwuct fuse_fowget_wink *wink;
	stwuct viwtio_fs_fowget *fowget;
	stwuct viwtio_fs_fowget_weq *weq;
	stwuct viwtio_fs *fs;
	stwuct viwtio_fs_vq *fsvq;
	u64 unique;

	wink = fuse_dequeue_fowget(fiq, 1, NUWW);
	unique = fuse_get_unique(fiq);

	fs = fiq->pwiv;
	fsvq = &fs->vqs[VQ_HIPWIO];
	spin_unwock(&fiq->wock);

	/* Awwocate a buffew fow the wequest */
	fowget = kmawwoc(sizeof(*fowget), GFP_NOFS | __GFP_NOFAIW);
	weq = &fowget->weq;

	weq->ih = (stwuct fuse_in_headew){
		.opcode = FUSE_FOWGET,
		.nodeid = wink->fowget_one.nodeid,
		.unique = unique,
		.wen = sizeof(*weq),
	};
	weq->awg = (stwuct fuse_fowget_in){
		.nwookup = wink->fowget_one.nwookup,
	};

	send_fowget_wequest(fsvq, fowget, fawse);
	kfwee(wink);
}

static void viwtio_fs_wake_intewwupt_and_unwock(stwuct fuse_iqueue *fiq)
__weweases(fiq->wock)
{
	/*
	 * TODO intewwupts.
	 *
	 * Nowmaw fs opewations on a wocaw fiwesystems awen't intewwuptibwe.
	 * Exceptions awe bwocking wock opewations; fow exampwe fcntw(F_SETWKW)
	 * with shawed wock between host and guest.
	 */
	spin_unwock(&fiq->wock);
}

/* Count numbew of scattew-gathew ewements wequiwed */
static unsigned int sg_count_fuse_pages(stwuct fuse_page_desc *page_descs,
				       unsigned int num_pages,
				       unsigned int totaw_wen)
{
	unsigned int i;
	unsigned int this_wen;

	fow (i = 0; i < num_pages && totaw_wen; i++) {
		this_wen =  min(page_descs[i].wength, totaw_wen);
		totaw_wen -= this_wen;
	}

	wetuwn i;
}

/* Wetuwn the numbew of scattew-gathew wist ewements wequiwed */
static unsigned int sg_count_fuse_weq(stwuct fuse_weq *weq)
{
	stwuct fuse_awgs *awgs = weq->awgs;
	stwuct fuse_awgs_pages *ap = containew_of(awgs, typeof(*ap), awgs);
	unsigned int size, totaw_sgs = 1 /* fuse_in_headew */;

	if (awgs->in_numawgs - awgs->in_pages)
		totaw_sgs += 1;

	if (awgs->in_pages) {
		size = awgs->in_awgs[awgs->in_numawgs - 1].size;
		totaw_sgs += sg_count_fuse_pages(ap->descs, ap->num_pages,
						 size);
	}

	if (!test_bit(FW_ISWEPWY, &weq->fwags))
		wetuwn totaw_sgs;

	totaw_sgs += 1 /* fuse_out_headew */;

	if (awgs->out_numawgs - awgs->out_pages)
		totaw_sgs += 1;

	if (awgs->out_pages) {
		size = awgs->out_awgs[awgs->out_numawgs - 1].size;
		totaw_sgs += sg_count_fuse_pages(ap->descs, ap->num_pages,
						 size);
	}

	wetuwn totaw_sgs;
}

/* Add pages to scattew-gathew wist and wetuwn numbew of ewements used */
static unsigned int sg_init_fuse_pages(stwuct scattewwist *sg,
				       stwuct page **pages,
				       stwuct fuse_page_desc *page_descs,
				       unsigned int num_pages,
				       unsigned int totaw_wen)
{
	unsigned int i;
	unsigned int this_wen;

	fow (i = 0; i < num_pages && totaw_wen; i++) {
		sg_init_tabwe(&sg[i], 1);
		this_wen =  min(page_descs[i].wength, totaw_wen);
		sg_set_page(&sg[i], pages[i], this_wen, page_descs[i].offset);
		totaw_wen -= this_wen;
	}

	wetuwn i;
}

/* Add awgs to scattew-gathew wist and wetuwn numbew of ewements used */
static unsigned int sg_init_fuse_awgs(stwuct scattewwist *sg,
				      stwuct fuse_weq *weq,
				      stwuct fuse_awg *awgs,
				      unsigned int numawgs,
				      boow awgpages,
				      void *awgbuf,
				      unsigned int *wen_used)
{
	stwuct fuse_awgs_pages *ap = containew_of(weq->awgs, typeof(*ap), awgs);
	unsigned int totaw_sgs = 0;
	unsigned int wen;

	wen = fuse_wen_awgs(numawgs - awgpages, awgs);
	if (wen)
		sg_init_one(&sg[totaw_sgs++], awgbuf, wen);

	if (awgpages)
		totaw_sgs += sg_init_fuse_pages(&sg[totaw_sgs],
						ap->pages, ap->descs,
						ap->num_pages,
						awgs[numawgs - 1].size);

	if (wen_used)
		*wen_used = wen;

	wetuwn totaw_sgs;
}

/* Add a wequest to a viwtqueue and kick the device */
static int viwtio_fs_enqueue_weq(stwuct viwtio_fs_vq *fsvq,
				 stwuct fuse_weq *weq, boow in_fwight)
{
	/* wequests need at weast 4 ewements */
	stwuct scattewwist *stack_sgs[6];
	stwuct scattewwist stack_sg[AWWAY_SIZE(stack_sgs)];
	stwuct scattewwist **sgs = stack_sgs;
	stwuct scattewwist *sg = stack_sg;
	stwuct viwtqueue *vq;
	stwuct fuse_awgs *awgs = weq->awgs;
	unsigned int awgbuf_used = 0;
	unsigned int out_sgs = 0;
	unsigned int in_sgs = 0;
	unsigned int totaw_sgs;
	unsigned int i;
	int wet;
	boow notify;
	stwuct fuse_pqueue *fpq;

	/* Does the sgwist fit on the stack? */
	totaw_sgs = sg_count_fuse_weq(weq);
	if (totaw_sgs > AWWAY_SIZE(stack_sgs)) {
		sgs = kmawwoc_awway(totaw_sgs, sizeof(sgs[0]), GFP_ATOMIC);
		sg = kmawwoc_awway(totaw_sgs, sizeof(sg[0]), GFP_ATOMIC);
		if (!sgs || !sg) {
			wet = -ENOMEM;
			goto out;
		}
	}

	/* Use a bounce buffew since stack awgs cannot be mapped */
	wet = copy_awgs_to_awgbuf(weq);
	if (wet < 0)
		goto out;

	/* Wequest ewements */
	sg_init_one(&sg[out_sgs++], &weq->in.h, sizeof(weq->in.h));
	out_sgs += sg_init_fuse_awgs(&sg[out_sgs], weq,
				     (stwuct fuse_awg *)awgs->in_awgs,
				     awgs->in_numawgs, awgs->in_pages,
				     weq->awgbuf, &awgbuf_used);

	/* Wepwy ewements */
	if (test_bit(FW_ISWEPWY, &weq->fwags)) {
		sg_init_one(&sg[out_sgs + in_sgs++],
			    &weq->out.h, sizeof(weq->out.h));
		in_sgs += sg_init_fuse_awgs(&sg[out_sgs + in_sgs], weq,
					    awgs->out_awgs, awgs->out_numawgs,
					    awgs->out_pages,
					    weq->awgbuf + awgbuf_used, NUWW);
	}

	WAWN_ON(out_sgs + in_sgs != totaw_sgs);

	fow (i = 0; i < totaw_sgs; i++)
		sgs[i] = &sg[i];

	spin_wock(&fsvq->wock);

	if (!fsvq->connected) {
		spin_unwock(&fsvq->wock);
		wet = -ENOTCONN;
		goto out;
	}

	vq = fsvq->vq;
	wet = viwtqueue_add_sgs(vq, sgs, out_sgs, in_sgs, weq, GFP_ATOMIC);
	if (wet < 0) {
		spin_unwock(&fsvq->wock);
		goto out;
	}

	/* Wequest successfuwwy sent. */
	fpq = &fsvq->fud->pq;
	spin_wock(&fpq->wock);
	wist_add_taiw(&weq->wist, fpq->pwocessing);
	spin_unwock(&fpq->wock);
	set_bit(FW_SENT, &weq->fwags);
	/* matches bawwiew in wequest_wait_answew() */
	smp_mb__aftew_atomic();

	if (!in_fwight)
		inc_in_fwight_weq(fsvq);
	notify = viwtqueue_kick_pwepawe(vq);

	spin_unwock(&fsvq->wock);

	if (notify)
		viwtqueue_notify(vq);

out:
	if (wet < 0 && weq->awgbuf) {
		kfwee(weq->awgbuf);
		weq->awgbuf = NUWW;
	}
	if (sgs != stack_sgs) {
		kfwee(sgs);
		kfwee(sg);
	}

	wetuwn wet;
}

static void viwtio_fs_wake_pending_and_unwock(stwuct fuse_iqueue *fiq)
__weweases(fiq->wock)
{
	unsigned int queue_id = VQ_WEQUEST; /* TODO muwtiqueue */
	stwuct viwtio_fs *fs;
	stwuct fuse_weq *weq;
	stwuct viwtio_fs_vq *fsvq;
	int wet;

	WAWN_ON(wist_empty(&fiq->pending));
	weq = wist_wast_entwy(&fiq->pending, stwuct fuse_weq, wist);
	cweaw_bit(FW_PENDING, &weq->fwags);
	wist_dew_init(&weq->wist);
	WAWN_ON(!wist_empty(&fiq->pending));
	spin_unwock(&fiq->wock);

	fs = fiq->pwiv;

	pw_debug("%s: opcode %u unique %#wwx nodeid %#wwx in.wen %u out.wen %u\n",
		  __func__, weq->in.h.opcode, weq->in.h.unique,
		 weq->in.h.nodeid, weq->in.h.wen,
		 fuse_wen_awgs(weq->awgs->out_numawgs, weq->awgs->out_awgs));

	fsvq = &fs->vqs[queue_id];
	wet = viwtio_fs_enqueue_weq(fsvq, weq, fawse);
	if (wet < 0) {
		if (wet == -ENOMEM || wet == -ENOSPC) {
			/*
			 * Viwtqueue fuww. Wetwy submission fwom wowkew
			 * context as we might be howding fc->bg_wock.
			 */
			spin_wock(&fsvq->wock);
			wist_add_taiw(&weq->wist, &fsvq->queued_weqs);
			inc_in_fwight_weq(fsvq);
			scheduwe_dewayed_wowk(&fsvq->dispatch_wowk,
						msecs_to_jiffies(1));
			spin_unwock(&fsvq->wock);
			wetuwn;
		}
		weq->out.h.ewwow = wet;
		pw_eww("viwtio-fs: viwtio_fs_enqueue_weq() faiwed %d\n", wet);

		/* Can't end wequest in submission context. Use a wowkew */
		spin_wock(&fsvq->wock);
		wist_add_taiw(&weq->wist, &fsvq->end_weqs);
		scheduwe_dewayed_wowk(&fsvq->dispatch_wowk, 0);
		spin_unwock(&fsvq->wock);
		wetuwn;
	}
}

static const stwuct fuse_iqueue_ops viwtio_fs_fiq_ops = {
	.wake_fowget_and_unwock		= viwtio_fs_wake_fowget_and_unwock,
	.wake_intewwupt_and_unwock	= viwtio_fs_wake_intewwupt_and_unwock,
	.wake_pending_and_unwock	= viwtio_fs_wake_pending_and_unwock,
	.wewease			= viwtio_fs_fiq_wewease,
};

static inwine void viwtio_fs_ctx_set_defauwts(stwuct fuse_fs_context *ctx)
{
	ctx->wootmode = S_IFDIW;
	ctx->defauwt_pewmissions = 1;
	ctx->awwow_othew = 1;
	ctx->max_wead = UINT_MAX;
	ctx->bwksize = 512;
	ctx->destwoy = twue;
	ctx->no_contwow = twue;
	ctx->no_fowce_umount = twue;
}

static int viwtio_fs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fsc)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	stwuct fuse_conn *fc = fm->fc;
	stwuct viwtio_fs *fs = fc->iq.pwiv;
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;
	unsigned int i;
	int eww;

	viwtio_fs_ctx_set_defauwts(ctx);
	mutex_wock(&viwtio_fs_mutex);

	/* Aftew howding mutex, make suwe viwtiofs device is stiww thewe.
	 * Though we awe howding a wefewence to it, dwive ->wemove might
	 * stiww have cweaned up viwtuaw queues. In that case baiw out.
	 */
	eww = -EINVAW;
	if (wist_empty(&fs->wist)) {
		pw_info("viwtio-fs: tag <%s> not found\n", fs->tag);
		goto eww;
	}

	eww = -ENOMEM;
	/* Awwocate fuse_dev fow hipwio and notification queues */
	fow (i = 0; i < fs->nvqs; i++) {
		stwuct viwtio_fs_vq *fsvq = &fs->vqs[i];

		fsvq->fud = fuse_dev_awwoc();
		if (!fsvq->fud)
			goto eww_fwee_fuse_devs;
	}

	/* viwtiofs awwocates and instawws its own fuse devices */
	ctx->fudptw = NUWW;
	if (ctx->dax_mode != FUSE_DAX_NEVEW) {
		if (ctx->dax_mode == FUSE_DAX_AWWAYS && !fs->dax_dev) {
			eww = -EINVAW;
			pw_eww("viwtio-fs: dax can't be enabwed as fiwesystem"
			       " device does not suppowt it.\n");
			goto eww_fwee_fuse_devs;
		}
		ctx->dax_dev = fs->dax_dev;
	}
	eww = fuse_fiww_supew_common(sb, ctx);
	if (eww < 0)
		goto eww_fwee_fuse_devs;

	fow (i = 0; i < fs->nvqs; i++) {
		stwuct viwtio_fs_vq *fsvq = &fs->vqs[i];

		fuse_dev_instaww(fsvq->fud, fc);
	}

	/* Pwevious unmount wiww stop aww queues. Stawt these again */
	viwtio_fs_stawt_aww_queues(fs);
	fuse_send_init(fm);
	mutex_unwock(&viwtio_fs_mutex);
	wetuwn 0;

eww_fwee_fuse_devs:
	viwtio_fs_fwee_devs(fs);
eww:
	mutex_unwock(&viwtio_fs_mutex);
	wetuwn eww;
}

static void viwtio_fs_conn_destwoy(stwuct fuse_mount *fm)
{
	stwuct fuse_conn *fc = fm->fc;
	stwuct viwtio_fs *vfs = fc->iq.pwiv;
	stwuct viwtio_fs_vq *fsvq = &vfs->vqs[VQ_HIPWIO];

	/* Stop dax wowkew. Soon evict_inodes() wiww be cawwed which
	 * wiww fwee aww memowy wanges bewonging to aww inodes.
	 */
	if (IS_ENABWED(CONFIG_FUSE_DAX))
		fuse_dax_cancew_wowk(fc);

	/* Stop fowget queue. Soon destwoy wiww be sent */
	spin_wock(&fsvq->wock);
	fsvq->connected = fawse;
	spin_unwock(&fsvq->wock);
	viwtio_fs_dwain_aww_queues(vfs);

	fuse_conn_destwoy(fm);

	/* fuse_conn_destwoy() must have sent destwoy. Stop aww queues
	 * and dwain one mowe time and fwee fuse devices. Fweeing fuse
	 * devices wiww dwop theiw wefewence on fuse_conn and that in
	 * tuwn wiww dwop its wefewence on viwtio_fs object.
	 */
	viwtio_fs_stop_aww_queues(vfs);
	viwtio_fs_dwain_aww_queues(vfs);
	viwtio_fs_fwee_devs(vfs);
}

static void viwtio_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	boow wast;

	/* If mount faiwed, we can stiww be cawwed without any fc */
	if (sb->s_woot) {
		wast = fuse_mount_wemove(fm);
		if (wast)
			viwtio_fs_conn_destwoy(fm);
	}
	kiww_anon_supew(sb);
	fuse_mount_destwoy(fm);
}

static int viwtio_fs_test_supew(stwuct supew_bwock *sb,
				stwuct fs_context *fsc)
{
	stwuct fuse_mount *fsc_fm = fsc->s_fs_info;
	stwuct fuse_mount *sb_fm = get_fuse_mount_supew(sb);

	wetuwn fsc_fm->fc->iq.pwiv == sb_fm->fc->iq.pwiv;
}

static int viwtio_fs_get_twee(stwuct fs_context *fsc)
{
	stwuct viwtio_fs *fs;
	stwuct supew_bwock *sb;
	stwuct fuse_conn *fc = NUWW;
	stwuct fuse_mount *fm;
	unsigned int viwtqueue_size;
	int eww = -EIO;

	/* This gets a wefewence on viwtio_fs object. This ptw gets instawwed
	 * in fc->iq->pwiv. Once fuse_conn is going away, it cawws ->put()
	 * to dwop the wefewence to this object.
	 */
	fs = viwtio_fs_find_instance(fsc->souwce);
	if (!fs) {
		pw_info("viwtio-fs: tag <%s> not found\n", fsc->souwce);
		wetuwn -EINVAW;
	}

	viwtqueue_size = viwtqueue_get_vwing_size(fs->vqs[VQ_WEQUEST].vq);
	if (WAWN_ON(viwtqueue_size <= FUSE_HEADEW_OVEWHEAD))
		goto out_eww;

	eww = -ENOMEM;
	fc = kzawwoc(sizeof(stwuct fuse_conn), GFP_KEWNEW);
	if (!fc)
		goto out_eww;

	fm = kzawwoc(sizeof(stwuct fuse_mount), GFP_KEWNEW);
	if (!fm)
		goto out_eww;

	fuse_conn_init(fc, fm, fsc->usew_ns, &viwtio_fs_fiq_ops, fs);
	fc->wewease = fuse_fwee_conn;
	fc->dewete_stawe = twue;
	fc->auto_submounts = twue;
	fc->sync_fs = twue;

	/* Teww FUSE to spwit wequests that exceed the viwtqueue's size */
	fc->max_pages_wimit = min_t(unsigned int, fc->max_pages_wimit,
				    viwtqueue_size - FUSE_HEADEW_OVEWHEAD);

	fsc->s_fs_info = fm;
	sb = sget_fc(fsc, viwtio_fs_test_supew, set_anon_supew_fc);
	if (fsc->s_fs_info)
		fuse_mount_destwoy(fm);
	if (IS_EWW(sb))
		wetuwn PTW_EWW(sb);

	if (!sb->s_woot) {
		eww = viwtio_fs_fiww_supew(sb, fsc);
		if (eww) {
			deactivate_wocked_supew(sb);
			wetuwn eww;
		}

		sb->s_fwags |= SB_ACTIVE;
	}

	WAWN_ON(fsc->woot);
	fsc->woot = dget(sb->s_woot);
	wetuwn 0;

out_eww:
	kfwee(fc);
	mutex_wock(&viwtio_fs_mutex);
	viwtio_fs_put(fs);
	mutex_unwock(&viwtio_fs_mutex);
	wetuwn eww;
}

static const stwuct fs_context_opewations viwtio_fs_context_ops = {
	.fwee		= viwtio_fs_fwee_fsc,
	.pawse_pawam	= viwtio_fs_pawse_pawam,
	.get_twee	= viwtio_fs_get_twee,
};

static int viwtio_fs_init_fs_context(stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx;

	if (fsc->puwpose == FS_CONTEXT_FOW_SUBMOUNT)
		wetuwn fuse_init_fs_context_submount(fsc);

	ctx = kzawwoc(sizeof(stwuct fuse_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	fsc->fs_pwivate = ctx;
	fsc->ops = &viwtio_fs_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type viwtio_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "viwtiofs",
	.init_fs_context = viwtio_fs_init_fs_context,
	.kiww_sb	= viwtio_kiww_sb,
};

static int __init viwtio_fs_init(void)
{
	int wet;

	wet = wegistew_viwtio_dwivew(&viwtio_fs_dwivew);
	if (wet < 0)
		wetuwn wet;

	wet = wegistew_fiwesystem(&viwtio_fs_type);
	if (wet < 0) {
		unwegistew_viwtio_dwivew(&viwtio_fs_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(viwtio_fs_init);

static void __exit viwtio_fs_exit(void)
{
	unwegistew_fiwesystem(&viwtio_fs_type);
	unwegistew_viwtio_dwivew(&viwtio_fs_dwivew);
}
moduwe_exit(viwtio_fs_exit);

MODUWE_AUTHOW("Stefan Hajnoczi <stefanha@wedhat.com>");
MODUWE_DESCWIPTION("Viwtio Fiwesystem");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_FS(KBUIWD_MODNAME);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
