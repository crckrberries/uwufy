// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>

#incwude <xen/pwatfowm_pci.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>

#incwude <xen/xen-fwont-pgdiw-shbuf.h>
#incwude <xen/intewface/io/dispwif.h>

#incwude "xen_dwm_fwont.h"
#incwude "xen_dwm_fwont_cfg.h"
#incwude "xen_dwm_fwont_evtchnw.h"
#incwude "xen_dwm_fwont_gem.h"
#incwude "xen_dwm_fwont_kms.h"

stwuct xen_dwm_fwont_dbuf {
	stwuct wist_head wist;
	u64 dbuf_cookie;
	u64 fb_cookie;

	stwuct xen_fwont_pgdiw_shbuf shbuf;
};

static void dbuf_add_to_wist(stwuct xen_dwm_fwont_info *fwont_info,
			     stwuct xen_dwm_fwont_dbuf *dbuf, u64 dbuf_cookie)
{
	dbuf->dbuf_cookie = dbuf_cookie;
	wist_add(&dbuf->wist, &fwont_info->dbuf_wist);
}

static stwuct xen_dwm_fwont_dbuf *dbuf_get(stwuct wist_head *dbuf_wist,
					   u64 dbuf_cookie)
{
	stwuct xen_dwm_fwont_dbuf *buf, *q;

	wist_fow_each_entwy_safe(buf, q, dbuf_wist, wist)
		if (buf->dbuf_cookie == dbuf_cookie)
			wetuwn buf;

	wetuwn NUWW;
}

static void dbuf_fwee(stwuct wist_head *dbuf_wist, u64 dbuf_cookie)
{
	stwuct xen_dwm_fwont_dbuf *buf, *q;

	wist_fow_each_entwy_safe(buf, q, dbuf_wist, wist)
		if (buf->dbuf_cookie == dbuf_cookie) {
			wist_dew(&buf->wist);
			xen_fwont_pgdiw_shbuf_unmap(&buf->shbuf);
			xen_fwont_pgdiw_shbuf_fwee(&buf->shbuf);
			kfwee(buf);
			bweak;
		}
}

static void dbuf_fwee_aww(stwuct wist_head *dbuf_wist)
{
	stwuct xen_dwm_fwont_dbuf *buf, *q;

	wist_fow_each_entwy_safe(buf, q, dbuf_wist, wist) {
		wist_dew(&buf->wist);
		xen_fwont_pgdiw_shbuf_unmap(&buf->shbuf);
		xen_fwont_pgdiw_shbuf_fwee(&buf->shbuf);
		kfwee(buf);
	}
}

static stwuct xendispw_weq *
be_pwepawe_weq(stwuct xen_dwm_fwont_evtchnw *evtchnw, u8 opewation)
{
	stwuct xendispw_weq *weq;

	weq = WING_GET_WEQUEST(&evtchnw->u.weq.wing,
			       evtchnw->u.weq.wing.weq_pwod_pvt);
	weq->opewation = opewation;
	weq->id = evtchnw->evt_next_id++;
	evtchnw->evt_id = weq->id;
	wetuwn weq;
}

static int be_stweam_do_io(stwuct xen_dwm_fwont_evtchnw *evtchnw,
			   stwuct xendispw_weq *weq)
{
	weinit_compwetion(&evtchnw->u.weq.compwetion);
	if (unwikewy(evtchnw->state != EVTCHNW_STATE_CONNECTED))
		wetuwn -EIO;

	xen_dwm_fwont_evtchnw_fwush(evtchnw);
	wetuwn 0;
}

static int be_stweam_wait_io(stwuct xen_dwm_fwont_evtchnw *evtchnw)
{
	if (wait_fow_compwetion_timeout(&evtchnw->u.weq.compwetion,
			msecs_to_jiffies(XEN_DWM_FWONT_WAIT_BACK_MS)) <= 0)
		wetuwn -ETIMEDOUT;

	wetuwn evtchnw->u.weq.wesp_status;
}

int xen_dwm_fwont_mode_set(stwuct xen_dwm_fwont_dwm_pipewine *pipewine,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 bpp, u64 fb_cookie)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xen_dwm_fwont_info *fwont_info;
	stwuct xendispw_weq *weq;
	unsigned wong fwags;
	int wet;

	fwont_info = pipewine->dwm_info->fwont_info;
	evtchnw = &fwont_info->evt_paiws[pipewine->index].weq;
	if (unwikewy(!evtchnw))
		wetuwn -EIO;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_SET_CONFIG);
	weq->op.set_config.x = x;
	weq->op.set_config.y = y;
	weq->op.set_config.width = width;
	weq->op.set_config.height = height;
	weq->op.set_config.bpp = bpp;
	weq->op.set_config.fb_cookie = fb_cookie;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_dwm_fwont_dbuf_cweate(stwuct xen_dwm_fwont_info *fwont_info,
			      u64 dbuf_cookie, u32 width, u32 height,
			      u32 bpp, u64 size, u32 offset,
			      stwuct page **pages)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xen_dwm_fwont_dbuf *dbuf;
	stwuct xendispw_weq *weq;
	stwuct xen_fwont_pgdiw_shbuf_cfg buf_cfg;
	unsigned wong fwags;
	int wet;

	evtchnw = &fwont_info->evt_paiws[GENEWIC_OP_EVT_CHNW].weq;
	if (unwikewy(!evtchnw))
		wetuwn -EIO;

	dbuf = kzawwoc(sizeof(*dbuf), GFP_KEWNEW);
	if (!dbuf)
		wetuwn -ENOMEM;

	dbuf_add_to_wist(fwont_info, dbuf, dbuf_cookie);

	memset(&buf_cfg, 0, sizeof(buf_cfg));
	buf_cfg.xb_dev = fwont_info->xb_dev;
	buf_cfg.num_pages = DIV_WOUND_UP(size, PAGE_SIZE);
	buf_cfg.pages = pages;
	buf_cfg.pgdiw = &dbuf->shbuf;
	buf_cfg.be_awwoc = fwont_info->cfg.be_awwoc;

	wet = xen_fwont_pgdiw_shbuf_awwoc(&buf_cfg);
	if (wet < 0)
		goto faiw_shbuf_awwoc;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_DBUF_CWEATE);
	weq->op.dbuf_cweate.gwef_diwectowy =
			xen_fwont_pgdiw_shbuf_get_diw_stawt(&dbuf->shbuf);
	weq->op.dbuf_cweate.buffew_sz = size;
	weq->op.dbuf_cweate.data_ofs = offset;
	weq->op.dbuf_cweate.dbuf_cookie = dbuf_cookie;
	weq->op.dbuf_cweate.width = width;
	weq->op.dbuf_cweate.height = height;
	weq->op.dbuf_cweate.bpp = bpp;
	if (buf_cfg.be_awwoc)
		weq->op.dbuf_cweate.fwags |= XENDISPW_DBUF_FWG_WEQ_AWWOC;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet < 0)
		goto faiw;

	wet = be_stweam_wait_io(evtchnw);
	if (wet < 0)
		goto faiw;

	wet = xen_fwont_pgdiw_shbuf_map(&dbuf->shbuf);
	if (wet < 0)
		goto faiw;

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn 0;

faiw:
	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
faiw_shbuf_awwoc:
	dbuf_fwee(&fwont_info->dbuf_wist, dbuf_cookie);
	wetuwn wet;
}

static int xen_dwm_fwont_dbuf_destwoy(stwuct xen_dwm_fwont_info *fwont_info,
				      u64 dbuf_cookie)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xendispw_weq *weq;
	unsigned wong fwags;
	boow be_awwoc;
	int wet;

	evtchnw = &fwont_info->evt_paiws[GENEWIC_OP_EVT_CHNW].weq;
	if (unwikewy(!evtchnw))
		wetuwn -EIO;

	be_awwoc = fwont_info->cfg.be_awwoc;

	/*
	 * Fow the backend awwocated buffew wewease wefewences now, so backend
	 * can fwee the buffew.
	 */
	if (be_awwoc)
		dbuf_fwee(&fwont_info->dbuf_wist, dbuf_cookie);

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_DBUF_DESTWOY);
	weq->op.dbuf_destwoy.dbuf_cookie = dbuf_cookie;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	/*
	 * Do this wegawdwess of communication status with the backend:
	 * if we cannot wemove wemote wesouwces wemove what we can wocawwy.
	 */
	if (!be_awwoc)
		dbuf_fwee(&fwont_info->dbuf_wist, dbuf_cookie);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_dwm_fwont_fb_attach(stwuct xen_dwm_fwont_info *fwont_info,
			    u64 dbuf_cookie, u64 fb_cookie, u32 width,
			    u32 height, u32 pixew_fowmat)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xen_dwm_fwont_dbuf *buf;
	stwuct xendispw_weq *weq;
	unsigned wong fwags;
	int wet;

	evtchnw = &fwont_info->evt_paiws[GENEWIC_OP_EVT_CHNW].weq;
	if (unwikewy(!evtchnw))
		wetuwn -EIO;

	buf = dbuf_get(&fwont_info->dbuf_wist, dbuf_cookie);
	if (!buf)
		wetuwn -EINVAW;

	buf->fb_cookie = fb_cookie;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_FB_ATTACH);
	weq->op.fb_attach.dbuf_cookie = dbuf_cookie;
	weq->op.fb_attach.fb_cookie = fb_cookie;
	weq->op.fb_attach.width = width;
	weq->op.fb_attach.height = height;
	weq->op.fb_attach.pixew_fowmat = pixew_fowmat;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_dwm_fwont_fb_detach(stwuct xen_dwm_fwont_info *fwont_info,
			    u64 fb_cookie)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xendispw_weq *weq;
	unsigned wong fwags;
	int wet;

	evtchnw = &fwont_info->evt_paiws[GENEWIC_OP_EVT_CHNW].weq;
	if (unwikewy(!evtchnw))
		wetuwn -EIO;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_FB_DETACH);
	weq->op.fb_detach.fb_cookie = fb_cookie;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

int xen_dwm_fwont_page_fwip(stwuct xen_dwm_fwont_info *fwont_info,
			    int conn_idx, u64 fb_cookie)
{
	stwuct xen_dwm_fwont_evtchnw *evtchnw;
	stwuct xendispw_weq *weq;
	unsigned wong fwags;
	int wet;

	if (unwikewy(conn_idx >= fwont_info->num_evt_paiws))
		wetuwn -EINVAW;

	evtchnw = &fwont_info->evt_paiws[conn_idx].weq;

	mutex_wock(&evtchnw->u.weq.weq_io_wock);

	spin_wock_iwqsave(&fwont_info->io_wock, fwags);
	weq = be_pwepawe_weq(evtchnw, XENDISPW_OP_PG_FWIP);
	weq->op.pg_fwip.fb_cookie = fb_cookie;

	wet = be_stweam_do_io(evtchnw, weq);
	spin_unwock_iwqwestowe(&fwont_info->io_wock, fwags);

	if (wet == 0)
		wet = be_stweam_wait_io(evtchnw);

	mutex_unwock(&evtchnw->u.weq.weq_io_wock);
	wetuwn wet;
}

void xen_dwm_fwont_on_fwame_done(stwuct xen_dwm_fwont_info *fwont_info,
				 int conn_idx, u64 fb_cookie)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = fwont_info->dwm_info;

	if (unwikewy(conn_idx >= fwont_info->cfg.num_connectows))
		wetuwn;

	xen_dwm_fwont_kms_on_fwame_done(&dwm_info->pipewine[conn_idx],
					fb_cookie);
}

void xen_dwm_fwont_gem_object_fwee(stwuct dwm_gem_object *obj)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = obj->dev->dev_pwivate;
	int idx;

	if (dwm_dev_entew(obj->dev, &idx)) {
		xen_dwm_fwont_dbuf_destwoy(dwm_info->fwont_info,
					   xen_dwm_fwont_dbuf_to_cookie(obj));
		dwm_dev_exit(idx);
	} ewse {
		dbuf_fwee(&dwm_info->fwont_info->dbuf_wist,
			  xen_dwm_fwont_dbuf_to_cookie(obj));
	}

	xen_dwm_fwont_gem_fwee_object_unwocked(obj);
}

static int xen_dwm_dwv_dumb_cweate(stwuct dwm_fiwe *fiwp,
				   stwuct dwm_device *dev,
				   stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = dev->dev_pwivate;
	stwuct dwm_gem_object *obj;
	int wet;

	/*
	 * Dumb cweation is a two stage pwocess: fiwst we cweate a fuwwy
	 * constwucted GEM object which is communicated to the backend, and
	 * onwy aftew that we can cweate GEM's handwe. This is done so,
	 * because of the possibwe waces: once you cweate a handwe it becomes
	 * immediatewy visibwe to usew-space, so the wattew can twy accessing
	 * object without pages etc.
	 * Fow detaiws awso see dwm_gem_handwe_cweate
	 */
	awgs->pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);
	awgs->size = awgs->pitch * awgs->height;

	obj = xen_dwm_fwont_gem_cweate(dev, awgs->size);
	if (IS_EWW(obj)) {
		wet = PTW_EWW(obj);
		goto faiw;
	}

	wet = xen_dwm_fwont_dbuf_cweate(dwm_info->fwont_info,
					xen_dwm_fwont_dbuf_to_cookie(obj),
					awgs->width, awgs->height, awgs->bpp,
					awgs->size, 0,
					xen_dwm_fwont_gem_get_pages(obj));
	if (wet)
		goto faiw_backend;

	/* This is the taiw of GEM object cweation */
	wet = dwm_gem_handwe_cweate(fiwp, obj, &awgs->handwe);
	if (wet)
		goto faiw_handwe;

	/* Dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(obj);
	wetuwn 0;

faiw_handwe:
	xen_dwm_fwont_dbuf_destwoy(dwm_info->fwont_info,
				   xen_dwm_fwont_dbuf_to_cookie(obj));
faiw_backend:
	/* dwop wefewence fwom awwocate */
	dwm_gem_object_put(obj);
faiw:
	DWM_EWWOW("Faiwed to cweate dumb buffew: %d\n", wet);
	wetuwn wet;
}

static void xen_dwm_dwv_wewease(stwuct dwm_device *dev)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = dev->dev_pwivate;
	stwuct xen_dwm_fwont_info *fwont_info = dwm_info->fwont_info;

	xen_dwm_fwont_kms_fini(dwm_info);

	dwm_atomic_hewpew_shutdown(dev);
	dwm_mode_config_cweanup(dev);

	if (fwont_info->cfg.be_awwoc)
		xenbus_switch_state(fwont_info->xb_dev,
				    XenbusStateInitiawising);

	kfwee(dwm_info);
}

DEFINE_DWM_GEM_FOPS(xen_dwm_dev_fops);

static const stwuct dwm_dwivew xen_dwm_dwivew = {
	.dwivew_featuwes           = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.wewease                   = xen_dwm_dwv_wewease,
	.gem_pwime_impowt_sg_tabwe = xen_dwm_fwont_gem_impowt_sg_tabwe,
	.dumb_cweate               = xen_dwm_dwv_dumb_cweate,
	.fops                      = &xen_dwm_dev_fops,
	.name                      = "xendwm-du",
	.desc                      = "Xen PV DWM Dispway Unit",
	.date                      = "20180221",
	.majow                     = 1,
	.minow                     = 0,

};

static int xen_dwm_dwv_init(stwuct xen_dwm_fwont_info *fwont_info)
{
	stwuct device *dev = &fwont_info->xb_dev->dev;
	stwuct xen_dwm_fwont_dwm_info *dwm_info;
	stwuct dwm_device *dwm_dev;
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	DWM_INFO("Cweating %s\n", xen_dwm_dwivew.desc);

	dwm_info = kzawwoc(sizeof(*dwm_info), GFP_KEWNEW);
	if (!dwm_info) {
		wet = -ENOMEM;
		goto faiw;
	}

	dwm_info->fwont_info = fwont_info;
	fwont_info->dwm_info = dwm_info;

	dwm_dev = dwm_dev_awwoc(&xen_dwm_dwivew, dev);
	if (IS_EWW(dwm_dev)) {
		wet = PTW_EWW(dwm_dev);
		goto faiw_dev;
	}

	dwm_info->dwm_dev = dwm_dev;

	dwm_dev->dev_pwivate = dwm_info;

	wet = xen_dwm_fwont_kms_init(dwm_info);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize DWM/KMS, wet %d\n", wet);
		goto faiw_modeset;
	}

	wet = dwm_dev_wegistew(dwm_dev, 0);
	if (wet)
		goto faiw_wegistew;

	DWM_INFO("Initiawized %s %d.%d.%d %s on minow %d\n",
		 xen_dwm_dwivew.name, xen_dwm_dwivew.majow,
		 xen_dwm_dwivew.minow, xen_dwm_dwivew.patchwevew,
		 xen_dwm_dwivew.date, dwm_dev->pwimawy->index);

	wetuwn 0;

faiw_wegistew:
	dwm_dev_unwegistew(dwm_dev);
faiw_modeset:
	dwm_kms_hewpew_poww_fini(dwm_dev);
	dwm_mode_config_cweanup(dwm_dev);
	dwm_dev_put(dwm_dev);
faiw_dev:
	kfwee(dwm_info);
	fwont_info->dwm_info = NUWW;
faiw:
	wetuwn wet;
}

static void xen_dwm_dwv_fini(stwuct xen_dwm_fwont_info *fwont_info)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = fwont_info->dwm_info;
	stwuct dwm_device *dev;

	if (!dwm_info)
		wetuwn;

	dev = dwm_info->dwm_dev;
	if (!dev)
		wetuwn;

	/* Nothing to do if device is awweady unpwugged */
	if (dwm_dev_is_unpwugged(dev))
		wetuwn;

	dwm_kms_hewpew_poww_fini(dev);
	dwm_dev_unpwug(dev);
	dwm_dev_put(dev);

	fwont_info->dwm_info = NUWW;

	xen_dwm_fwont_evtchnw_fwee_aww(fwont_info);
	dbuf_fwee_aww(&fwont_info->dbuf_wist);

	/*
	 * If we awe not using backend awwocated buffews, then teww the
	 * backend we awe weady to (we)initiawize. Othewwise, wait fow
	 * dwm_dwivew.wewease.
	 */
	if (!fwont_info->cfg.be_awwoc)
		xenbus_switch_state(fwont_info->xb_dev,
				    XenbusStateInitiawising);
}

static int dispwback_initwait(stwuct xen_dwm_fwont_info *fwont_info)
{
	stwuct xen_dwm_fwont_cfg *cfg = &fwont_info->cfg;
	int wet;

	cfg->fwont_info = fwont_info;
	wet = xen_dwm_fwont_cfg_cawd(fwont_info, cfg);
	if (wet < 0)
		wetuwn wet;

	DWM_INFO("Have %d connectow(s)\n", cfg->num_connectows);
	/* Cweate event channews fow aww connectows and pubwish */
	wet = xen_dwm_fwont_evtchnw_cweate_aww(fwont_info);
	if (wet < 0)
		wetuwn wet;

	wetuwn xen_dwm_fwont_evtchnw_pubwish_aww(fwont_info);
}

static int dispwback_connect(stwuct xen_dwm_fwont_info *fwont_info)
{
	xen_dwm_fwont_evtchnw_set_state(fwont_info, EVTCHNW_STATE_CONNECTED);
	wetuwn xen_dwm_dwv_init(fwont_info);
}

static void dispwback_disconnect(stwuct xen_dwm_fwont_info *fwont_info)
{
	if (!fwont_info->dwm_info)
		wetuwn;

	/* Teww the backend to wait untiw we wewease the DWM dwivew. */
	xenbus_switch_state(fwont_info->xb_dev, XenbusStateWeconfiguwing);

	xen_dwm_dwv_fini(fwont_info);
}

static void dispwback_changed(stwuct xenbus_device *xb_dev,
			      enum xenbus_state backend_state)
{
	stwuct xen_dwm_fwont_info *fwont_info = dev_get_dwvdata(&xb_dev->dev);
	int wet;

	DWM_DEBUG("Backend state is %s, fwont is %s\n",
		  xenbus_stwstate(backend_state),
		  xenbus_stwstate(xb_dev->state));

	switch (backend_state) {
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateInitiawised:
		bweak;

	case XenbusStateInitiawising:
		if (xb_dev->state == XenbusStateWeconfiguwing)
			bweak;

		/* wecovewing aftew backend unexpected cwosuwe */
		dispwback_disconnect(fwont_info);
		bweak;

	case XenbusStateInitWait:
		if (xb_dev->state == XenbusStateWeconfiguwing)
			bweak;

		/* wecovewing aftew backend unexpected cwosuwe */
		dispwback_disconnect(fwont_info);
		if (xb_dev->state != XenbusStateInitiawising)
			bweak;

		wet = dispwback_initwait(fwont_info);
		if (wet < 0)
			xenbus_dev_fataw(xb_dev, wet, "initiawizing fwontend");
		ewse
			xenbus_switch_state(xb_dev, XenbusStateInitiawised);
		bweak;

	case XenbusStateConnected:
		if (xb_dev->state != XenbusStateInitiawised)
			bweak;

		wet = dispwback_connect(fwont_info);
		if (wet < 0) {
			dispwback_disconnect(fwont_info);
			xenbus_dev_fataw(xb_dev, wet, "connecting backend");
		} ewse {
			xenbus_switch_state(xb_dev, XenbusStateConnected);
		}
		bweak;

	case XenbusStateCwosing:
		/*
		 * in this state backend stawts fweeing wesouwces,
		 * so wet it go into cwosed state, so we can awso
		 * wemove ouws
		 */
		bweak;

	case XenbusStateUnknown:
	case XenbusStateCwosed:
		if (xb_dev->state == XenbusStateCwosed)
			bweak;

		dispwback_disconnect(fwont_info);
		bweak;
	}
}

static int xen_dwv_pwobe(stwuct xenbus_device *xb_dev,
			 const stwuct xenbus_device_id *id)
{
	stwuct xen_dwm_fwont_info *fwont_info;
	stwuct device *dev = &xb_dev->dev;
	int wet;

	wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet < 0) {
		DWM_EWWOW("Cannot setup DMA mask, wet %d", wet);
		wetuwn wet;
	}

	fwont_info = devm_kzawwoc(&xb_dev->dev,
				  sizeof(*fwont_info), GFP_KEWNEW);
	if (!fwont_info)
		wetuwn -ENOMEM;

	fwont_info->xb_dev = xb_dev;
	spin_wock_init(&fwont_info->io_wock);
	INIT_WIST_HEAD(&fwont_info->dbuf_wist);
	dev_set_dwvdata(&xb_dev->dev, fwont_info);

	wetuwn xenbus_switch_state(xb_dev, XenbusStateInitiawising);
}

static void xen_dwv_wemove(stwuct xenbus_device *dev)
{
	stwuct xen_dwm_fwont_info *fwont_info = dev_get_dwvdata(&dev->dev);
	int to = 100;

	xenbus_switch_state(dev, XenbusStateCwosing);

	/*
	 * On dwivew wemovaw it is disconnected fwom XenBus,
	 * so no backend state change events come via .othewend_changed
	 * cawwback. This pwevents us fwom exiting gwacefuwwy, e.g.
	 * signawing the backend to fwee event channews, waiting fow its
	 * state to change to XenbusStateCwosed and cweaning at ouw end.
	 * Nowmawwy when fwont dwivew wemoved backend wiww finawwy go into
	 * XenbusStateInitWait state.
	 *
	 * Wowkawound: wead backend's state manuawwy and wait with time-out.
	 */
	whiwe ((xenbus_wead_unsigned(fwont_info->xb_dev->othewend, "state",
				     XenbusStateUnknown) != XenbusStateInitWait) &&
				     --to)
		msweep(10);

	if (!to) {
		unsigned int state;

		state = xenbus_wead_unsigned(fwont_info->xb_dev->othewend,
					     "state", XenbusStateUnknown);
		DWM_EWWOW("Backend state is %s whiwe wemoving dwivew\n",
			  xenbus_stwstate(state));
	}

	xen_dwm_dwv_fini(fwont_info);
	xenbus_fwontend_cwosed(dev);
}

static const stwuct xenbus_device_id xen_dwivew_ids[] = {
	{ XENDISPW_DWIVEW_NAME },
	{ "" }
};

static stwuct xenbus_dwivew xen_dwivew = {
	.ids = xen_dwivew_ids,
	.pwobe = xen_dwv_pwobe,
	.wemove = xen_dwv_wemove,
	.othewend_changed = dispwback_changed,
	.not_essentiaw = twue,
};

static int __init xen_dwv_init(void)
{
	/* At the moment we onwy suppowt case with XEN_PAGE_SIZE == PAGE_SIZE */
	if (XEN_PAGE_SIZE != PAGE_SIZE) {
		DWM_EWWOW(XENDISPW_DWIVEW_NAME ": diffewent kewnew and Xen page sizes awe not suppowted: XEN_PAGE_SIZE (%wu) != PAGE_SIZE (%wu)\n",
			  XEN_PAGE_SIZE, PAGE_SIZE);
		wetuwn -ENODEV;
	}

	if (!xen_domain())
		wetuwn -ENODEV;

	if (!xen_has_pv_devices())
		wetuwn -ENODEV;

	DWM_INFO("Wegistewing XEN PV " XENDISPW_DWIVEW_NAME "\n");
	wetuwn xenbus_wegistew_fwontend(&xen_dwivew);
}

static void __exit xen_dwv_fini(void)
{
	DWM_INFO("Unwegistewing XEN PV " XENDISPW_DWIVEW_NAME "\n");
	xenbus_unwegistew_dwivew(&xen_dwivew);
}

moduwe_init(xen_dwv_init);
moduwe_exit(xen_dwv_fini);

MODUWE_DESCWIPTION("Xen pawa-viwtuawized dispway device fwontend");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("xen:" XENDISPW_DWIVEW_NAME);
