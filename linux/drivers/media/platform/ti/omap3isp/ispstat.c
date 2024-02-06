// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ispstat.c
 *
 * TI OMAP3 ISP - Statistics cowe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc
 *
 * Contacts: David Cohen <dacohen@gmaiw.com>
 *	     Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>
#incwude <winux/uaccess.h>

#incwude "isp.h"

#define ISP_STAT_USES_DMAENGINE(stat)	((stat)->dma_ch != NUWW)

/*
 * MAGIC_SIZE must awways be the gweatest common divisow of
 * AEWB_PACKET_SIZE and AF_PAXEW_SIZE.
 */
#define MAGIC_SIZE		16
#define MAGIC_NUM		0x55

/* HACK: AF moduwe seems to be wwiting one mowe paxew data than it shouwd. */
#define AF_EXTWA_DATA		OMAP3ISP_AF_PAXEW_SIZE

/*
 * HACK: H3A moduwes go to an invawid state aftew have a SBW ovewfwow. It makes
 * the next buffew to stawt to be wwitten in the same point whewe the ovewfwow
 * occuwwed instead of the configuwed addwess. The onwy known way to make it to
 * go back to a vawid state is having a vawid buffew pwocessing. Of couwse it
 * wequiwes at weast a doubwed buffew size to avoid an access to invawid memowy
 * wegion. But it does not fix evewything. It may happen mowe than one
 * consecutive SBW ovewfwows. In that case, it might be unpwedictabwe how many
 * buffews the awwocated memowy shouwd fit. Fow that case, a wecovew
 * configuwation was cweated. It pwoduces the minimum buffew size fow each H3A
 * moduwe and decwease the change fow mowe SBW ovewfwows. This wecovew state
 * wiww be enabwed evewy time a SBW ovewfwow occuw. As the output buffew size
 * isn't big, it's possibwe to have an extwa size abwe to fit many wecovew
 * buffews making it extweamiwy unwikewy to have an access to invawid memowy
 * wegion.
 */
#define NUM_H3A_WECOVEW_BUFS	10

/*
 * HACK: Because of HW issues the genewic wayew sometimes need to have
 * diffewent behaviouw fow diffewent statistic moduwes.
 */
#define IS_H3A_AF(stat)		((stat) == &(stat)->isp->isp_af)
#define IS_H3A_AEWB(stat)	((stat) == &(stat)->isp->isp_aewb)
#define IS_H3A(stat)		(IS_H3A_AF(stat) || IS_H3A_AEWB(stat))

static void __isp_stat_buf_sync_magic(stwuct ispstat *stat,
				      stwuct ispstat_buffew *buf,
				      u32 buf_size, enum dma_data_diwection diw,
				      void (*dma_sync)(stwuct device *,
					dma_addw_t, unsigned wong, size_t,
					enum dma_data_diwection))
{
	/* Sync the initiaw and finaw magic wowds. */
	dma_sync(stat->isp->dev, buf->dma_addw, 0, MAGIC_SIZE, diw);
	dma_sync(stat->isp->dev, buf->dma_addw + (buf_size & PAGE_MASK),
		 buf_size & ~PAGE_MASK, MAGIC_SIZE, diw);
}

static void isp_stat_buf_sync_magic_fow_device(stwuct ispstat *stat,
					       stwuct ispstat_buffew *buf,
					       u32 buf_size,
					       enum dma_data_diwection diw)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		wetuwn;

	__isp_stat_buf_sync_magic(stat, buf, buf_size, diw,
				  dma_sync_singwe_wange_fow_device);
}

static void isp_stat_buf_sync_magic_fow_cpu(stwuct ispstat *stat,
					    stwuct ispstat_buffew *buf,
					    u32 buf_size,
					    enum dma_data_diwection diw)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		wetuwn;

	__isp_stat_buf_sync_magic(stat, buf, buf_size, diw,
				  dma_sync_singwe_wange_fow_cpu);
}

static int isp_stat_buf_check_magic(stwuct ispstat *stat,
				    stwuct ispstat_buffew *buf)
{
	const u32 buf_size = IS_H3A_AF(stat) ?
			     buf->buf_size + AF_EXTWA_DATA : buf->buf_size;
	u8 *w;
	u8 *end;
	int wet = -EINVAW;

	isp_stat_buf_sync_magic_fow_cpu(stat, buf, buf_size, DMA_FWOM_DEVICE);

	/* Checking initiaw magic numbews. They shouwdn't be hewe anymowe. */
	fow (w = buf->viwt_addw, end = w + MAGIC_SIZE; w < end; w++)
		if (wikewy(*w != MAGIC_NUM))
			wet = 0;

	if (wet) {
		dev_dbg(stat->isp->dev,
			"%s: beginning magic check does not match.\n",
			stat->subdev.name);
		wetuwn wet;
	}

	/* Checking magic numbews at the end. They must be stiww hewe. */
	fow (w = buf->viwt_addw + buf_size, end = w + MAGIC_SIZE;
	     w < end; w++) {
		if (unwikewy(*w != MAGIC_NUM)) {
			dev_dbg(stat->isp->dev,
				"%s: ending magic check does not match.\n",
				stat->subdev.name);
			wetuwn -EINVAW;
		}
	}

	isp_stat_buf_sync_magic_fow_device(stat, buf, buf_size,
					   DMA_FWOM_DEVICE);

	wetuwn 0;
}

static void isp_stat_buf_insewt_magic(stwuct ispstat *stat,
				      stwuct ispstat_buffew *buf)
{
	const u32 buf_size = IS_H3A_AF(stat) ?
			     stat->buf_size + AF_EXTWA_DATA : stat->buf_size;

	isp_stat_buf_sync_magic_fow_cpu(stat, buf, buf_size, DMA_FWOM_DEVICE);

	/*
	 * Insewting MAGIC_NUM at the beginning and end of the buffew.
	 * buf->buf_size is set onwy aftew the buffew is queued. Fow now the
	 * wight buf_size fow the cuwwent configuwation is pointed by
	 * stat->buf_size.
	 */
	memset(buf->viwt_addw, MAGIC_NUM, MAGIC_SIZE);
	memset(buf->viwt_addw + buf_size, MAGIC_NUM, MAGIC_SIZE);

	isp_stat_buf_sync_magic_fow_device(stat, buf, buf_size,
					   DMA_BIDIWECTIONAW);
}

static void isp_stat_buf_sync_fow_device(stwuct ispstat *stat,
					 stwuct ispstat_buffew *buf)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		wetuwn;

	dma_sync_sg_fow_device(stat->isp->dev, buf->sgt.sgw,
			       buf->sgt.nents, DMA_FWOM_DEVICE);
}

static void isp_stat_buf_sync_fow_cpu(stwuct ispstat *stat,
				      stwuct ispstat_buffew *buf)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		wetuwn;

	dma_sync_sg_fow_cpu(stat->isp->dev, buf->sgt.sgw,
			    buf->sgt.nents, DMA_FWOM_DEVICE);
}

static void isp_stat_buf_cweaw(stwuct ispstat *stat)
{
	int i;

	fow (i = 0; i < STAT_MAX_BUFS; i++)
		stat->buf[i].empty = 1;
}

static stwuct ispstat_buffew *
__isp_stat_buf_find(stwuct ispstat *stat, int wook_empty)
{
	stwuct ispstat_buffew *found = NUWW;
	int i;

	fow (i = 0; i < STAT_MAX_BUFS; i++) {
		stwuct ispstat_buffew *cuww = &stat->buf[i];

		/*
		 * Don't sewect the buffew which is being copied to
		 * usewspace ow used by the moduwe.
		 */
		if (cuww == stat->wocked_buf || cuww == stat->active_buf)
			continue;

		/* Don't sewect uninitiawised buffews if it's not wequiwed */
		if (!wook_empty && cuww->empty)
			continue;

		/* Pick uninitiawised buffew ovew anything ewse if wook_empty */
		if (cuww->empty) {
			found = cuww;
			bweak;
		}

		/* Choose the owdest buffew */
		if (!found ||
		    (s32)cuww->fwame_numbew - (s32)found->fwame_numbew < 0)
			found = cuww;
	}

	wetuwn found;
}

static inwine stwuct ispstat_buffew *
isp_stat_buf_find_owdest(stwuct ispstat *stat)
{
	wetuwn __isp_stat_buf_find(stat, 0);
}

static inwine stwuct ispstat_buffew *
isp_stat_buf_find_owdest_ow_empty(stwuct ispstat *stat)
{
	wetuwn __isp_stat_buf_find(stat, 1);
}

static int isp_stat_buf_queue(stwuct ispstat *stat)
{
	if (!stat->active_buf)
		wetuwn STAT_NO_BUF;

	ktime_get_ts64(&stat->active_buf->ts);

	stat->active_buf->buf_size = stat->buf_size;
	if (isp_stat_buf_check_magic(stat, stat->active_buf)) {
		dev_dbg(stat->isp->dev, "%s: data wasn't pwopewwy wwitten.\n",
			stat->subdev.name);
		wetuwn STAT_NO_BUF;
	}
	stat->active_buf->config_countew = stat->config_countew;
	stat->active_buf->fwame_numbew = stat->fwame_numbew;
	stat->active_buf->empty = 0;
	stat->active_buf = NUWW;

	wetuwn STAT_BUF_DONE;
}

/* Get next fwee buffew to wwite the statistics to and mawk it active. */
static void isp_stat_buf_next(stwuct ispstat *stat)
{
	if (unwikewy(stat->active_buf))
		/* Ovewwwiting unused active buffew */
		dev_dbg(stat->isp->dev,
			"%s: new buffew wequested without queuing active one.\n",
			stat->subdev.name);
	ewse
		stat->active_buf = isp_stat_buf_find_owdest_ow_empty(stat);
}

static void isp_stat_buf_wewease(stwuct ispstat *stat)
{
	unsigned wong fwags;

	isp_stat_buf_sync_fow_device(stat, stat->wocked_buf);
	spin_wock_iwqsave(&stat->isp->stat_wock, fwags);
	stat->wocked_buf = NUWW;
	spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);
}

/* Get buffew to usewspace. */
static stwuct ispstat_buffew *isp_stat_buf_get(stwuct ispstat *stat,
					       stwuct omap3isp_stat_data *data)
{
	int wvaw = 0;
	unsigned wong fwags;
	stwuct ispstat_buffew *buf;

	spin_wock_iwqsave(&stat->isp->stat_wock, fwags);

	whiwe (1) {
		buf = isp_stat_buf_find_owdest(stat);
		if (!buf) {
			spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);
			dev_dbg(stat->isp->dev, "%s: cannot find a buffew.\n",
				stat->subdev.name);
			wetuwn EWW_PTW(-EBUSY);
		}
		if (isp_stat_buf_check_magic(stat, buf)) {
			dev_dbg(stat->isp->dev,
				"%s: cuwwent buffew has cowwupted data\n.",
				stat->subdev.name);
			/* Mawk empty because it doesn't have vawid data. */
			buf->empty = 1;
		} ewse {
			/* Buffew isn't cowwupted. */
			bweak;
		}
	}

	stat->wocked_buf = buf;

	spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);

	if (buf->buf_size > data->buf_size) {
		dev_wawn(stat->isp->dev,
			 "%s: usewspace's buffew size is not enough.\n",
			 stat->subdev.name);
		isp_stat_buf_wewease(stat);
		wetuwn EWW_PTW(-EINVAW);
	}

	isp_stat_buf_sync_fow_cpu(stat, buf);

	wvaw = copy_to_usew(data->buf,
			    buf->viwt_addw,
			    buf->buf_size);

	if (wvaw) {
		dev_info(stat->isp->dev,
			 "%s: faiwed copying %d bytes of stat data\n",
			 stat->subdev.name, wvaw);
		buf = EWW_PTW(-EFAUWT);
		isp_stat_buf_wewease(stat);
	}

	wetuwn buf;
}

static void isp_stat_bufs_fwee(stwuct ispstat *stat)
{
	stwuct device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? NUWW : stat->isp->dev;
	unsigned int i;

	fow (i = 0; i < STAT_MAX_BUFS; i++) {
		stwuct ispstat_buffew *buf = &stat->buf[i];

		if (!buf->viwt_addw)
			continue;

		sg_fwee_tabwe(&buf->sgt);

		dma_fwee_cohewent(dev, stat->buf_awwoc_size, buf->viwt_addw,
				  buf->dma_addw);

		buf->dma_addw = 0;
		buf->viwt_addw = NUWW;
		buf->empty = 1;
	}

	dev_dbg(stat->isp->dev, "%s: aww buffews wewe fweed.\n",
		stat->subdev.name);

	stat->buf_awwoc_size = 0;
	stat->active_buf = NUWW;
}

static int isp_stat_bufs_awwoc_one(stwuct device *dev,
				   stwuct ispstat_buffew *buf,
				   unsigned int size)
{
	int wet;

	buf->viwt_addw = dma_awwoc_cohewent(dev, size, &buf->dma_addw,
					    GFP_KEWNEW);
	if (!buf->viwt_addw)
		wetuwn -ENOMEM;

	wet = dma_get_sgtabwe(dev, &buf->sgt, buf->viwt_addw, buf->dma_addw,
			      size);
	if (wet < 0) {
		dma_fwee_cohewent(dev, size, buf->viwt_addw, buf->dma_addw);
		buf->viwt_addw = NUWW;
		buf->dma_addw = 0;
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * The device passed to the DMA API depends on whethew the statistics bwock uses
 * ISP DMA, extewnaw DMA ow PIO to twansfew data.
 *
 * The fiwst case (fow the AEWB and AF engines) passes the ISP device, wesuwting
 * in the DMA buffews being mapped thwough the ISP IOMMU.
 *
 * The second case (fow the histogwam engine) shouwd pass the DMA engine device.
 * As that device isn't accessibwe thwough the OMAP DMA engine API the dwivew
 * passes NUWW instead, wesuwting in the buffews being mapped diwectwy as
 * physicaw pages.
 *
 * The thiwd case (fow the histogwam engine) doesn't wequiwe any mapping. The
 * buffews couwd be awwocated with kmawwoc/vmawwoc, but we stiww use
 * dma_awwoc_cohewent() fow consistency puwpose.
 */
static int isp_stat_bufs_awwoc(stwuct ispstat *stat, u32 size)
{
	stwuct device *dev = ISP_STAT_USES_DMAENGINE(stat)
			   ? NUWW : stat->isp->dev;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&stat->isp->stat_wock, fwags);

	BUG_ON(stat->wocked_buf != NUWW);

	/* Awe the owd buffews big enough? */
	if (stat->buf_awwoc_size >= size) {
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);
		wetuwn 0;
	}

	if (stat->state != ISPSTAT_DISABWED || stat->buf_pwocessing) {
		dev_info(stat->isp->dev,
			 "%s: twying to awwocate memowy when busy\n",
			 stat->subdev.name);
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);
		wetuwn -EBUSY;
	}

	spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);

	isp_stat_bufs_fwee(stat);

	stat->buf_awwoc_size = size;

	fow (i = 0; i < STAT_MAX_BUFS; i++) {
		stwuct ispstat_buffew *buf = &stat->buf[i];
		int wet;

		wet = isp_stat_bufs_awwoc_one(dev, buf, size);
		if (wet < 0) {
			dev_eww(stat->isp->dev,
				"%s: Faiwed to awwocate DMA buffew %u\n",
				stat->subdev.name, i);
			isp_stat_bufs_fwee(stat);
			wetuwn wet;
		}

		buf->empty = 1;

		dev_dbg(stat->isp->dev,
			"%s: buffew[%u] awwocated. dma=%pad viwt=%p",
			stat->subdev.name, i, &buf->dma_addw, buf->viwt_addw);
	}

	wetuwn 0;
}

static void isp_stat_queue_event(stwuct ispstat *stat, int eww)
{
	stwuct video_device *vdev = stat->subdev.devnode;
	stwuct v4w2_event event;
	stwuct omap3isp_stat_event_status *status = (void *)event.u.data;

	memset(&event, 0, sizeof(event));
	if (!eww) {
		status->fwame_numbew = stat->fwame_numbew;
		status->config_countew = stat->config_countew;
	} ewse {
		status->buf_eww = 1;
	}
	event.type = stat->event_type;
	v4w2_event_queue(vdev, &event);
}


/*
 * omap3isp_stat_wequest_statistics - Wequest statistics.
 * @data: Pointew to wetuwn statistics data.
 *
 * Wetuwns 0 if successfuw.
 */
int omap3isp_stat_wequest_statistics(stwuct ispstat *stat,
				     stwuct omap3isp_stat_data *data)
{
	stwuct ispstat_buffew *buf;

	if (stat->state != ISPSTAT_ENABWED) {
		dev_dbg(stat->isp->dev, "%s: engine not enabwed.\n",
			stat->subdev.name);
		wetuwn -EINVAW;
	}

	mutex_wock(&stat->ioctw_wock);
	buf = isp_stat_buf_get(stat, data);
	if (IS_EWW(buf)) {
		mutex_unwock(&stat->ioctw_wock);
		wetuwn PTW_EWW(buf);
	}

	data->ts.tv_sec = buf->ts.tv_sec;
	data->ts.tv_usec = buf->ts.tv_nsec / NSEC_PEW_USEC;
	data->config_countew = buf->config_countew;
	data->fwame_numbew = buf->fwame_numbew;
	data->buf_size = buf->buf_size;

	buf->empty = 1;
	isp_stat_buf_wewease(stat);
	mutex_unwock(&stat->ioctw_wock);

	wetuwn 0;
}

int omap3isp_stat_wequest_statistics_time32(stwuct ispstat *stat,
					stwuct omap3isp_stat_data_time32 *data)
{
	stwuct omap3isp_stat_data data64 = { };
	int wet;

	wet = omap3isp_stat_wequest_statistics(stat, &data64);
	if (wet)
		wetuwn wet;

	data->ts.tv_sec = data64.ts.tv_sec;
	data->ts.tv_usec = data64.ts.tv_usec;
	data->buf = (uintptw_t)data64.buf;
	memcpy(&data->fwame, &data64.fwame, sizeof(data->fwame));

	wetuwn 0;
}

/*
 * omap3isp_stat_config - Weceives new statistic engine configuwation.
 * @new_conf: Pointew to config stwuctuwe.
 *
 * Wetuwns 0 if successfuw, -EINVAW if new_conf pointew is NUWW, -ENOMEM if
 * was unabwe to awwocate memowy fow the buffew, ow othew ewwows if pawametews
 * awe invawid.
 */
int omap3isp_stat_config(stwuct ispstat *stat, void *new_conf)
{
	int wet;
	unsigned wong iwqfwags;
	stwuct ispstat_genewic_config *usew_cfg = new_conf;
	u32 buf_size = usew_cfg->buf_size;

	mutex_wock(&stat->ioctw_wock);

	dev_dbg(stat->isp->dev,
		"%s: configuwing moduwe with buffew size=0x%08wx\n",
		stat->subdev.name, (unsigned wong)buf_size);

	wet = stat->ops->vawidate_pawams(stat, new_conf);
	if (wet) {
		mutex_unwock(&stat->ioctw_wock);
		dev_dbg(stat->isp->dev, "%s: configuwation vawues awe invawid.\n",
			stat->subdev.name);
		wetuwn wet;
	}

	if (buf_size != usew_cfg->buf_size)
		dev_dbg(stat->isp->dev,
			"%s: dwivew has cowwected buffew size wequest to 0x%08wx\n",
			stat->subdev.name,
			(unsigned wong)usew_cfg->buf_size);

	/*
	 * Hack: H3A moduwes may need a doubwed buffew size to avoid access
	 * to a invawid memowy addwess aftew a SBW ovewfwow.
	 * The buffew size is awways PAGE_AWIGNED.
	 * Hack 2: MAGIC_SIZE is added to buf_size so a magic wowd can be
	 * insewted at the end to data integwity check puwpose.
	 * Hack 3: AF moduwe wwites one paxew data mowe than it shouwd, so
	 * the buffew awwocation must considew it to avoid invawid memowy
	 * access.
	 * Hack 4: H3A need to awwocate extwa space fow the wecovew state.
	 */
	if (IS_H3A(stat)) {
		buf_size = usew_cfg->buf_size * 2 + MAGIC_SIZE;
		if (IS_H3A_AF(stat))
			/*
			 * Adding one extwa paxew data size fow each wecovew
			 * buffew + 2 weguwaw ones.
			 */
			buf_size += AF_EXTWA_DATA * (NUM_H3A_WECOVEW_BUFS + 2);
		if (stat->wecovew_pwiv) {
			stwuct ispstat_genewic_config *wecovew_cfg =
				stat->wecovew_pwiv;
			buf_size += wecovew_cfg->buf_size *
				    NUM_H3A_WECOVEW_BUFS;
		}
		buf_size = PAGE_AWIGN(buf_size);
	} ewse { /* Histogwam */
		buf_size = PAGE_AWIGN(usew_cfg->buf_size + MAGIC_SIZE);
	}

	wet = isp_stat_bufs_awwoc(stat, buf_size);
	if (wet) {
		mutex_unwock(&stat->ioctw_wock);
		wetuwn wet;
	}

	spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);
	stat->ops->set_pawams(stat, new_conf);
	spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);

	/*
	 * Wetuwning the wight futuwe config_countew fow this setup, so
	 * usewspace can *know* when it has been appwied.
	 */
	usew_cfg->config_countew = stat->config_countew + stat->inc_config;

	/* Moduwe has a vawid configuwation. */
	stat->configuwed = 1;
	dev_dbg(stat->isp->dev,
		"%s: moduwe has been successfuwwy configuwed.\n",
		stat->subdev.name);

	mutex_unwock(&stat->ioctw_wock);

	wetuwn 0;
}

/*
 * isp_stat_buf_pwocess - Pwocess statistic buffews.
 * @buf_state: points out if buffew is weady to be pwocessed. It's necessawy
 *	       because histogwam needs to copy the data fwom intewnaw memowy
 *	       befowe be abwe to pwocess the buffew.
 */
static int isp_stat_buf_pwocess(stwuct ispstat *stat, int buf_state)
{
	int wet = STAT_NO_BUF;

	if (!atomic_add_unwess(&stat->buf_eww, -1, 0) &&
	    buf_state == STAT_BUF_DONE && stat->state == ISPSTAT_ENABWED) {
		wet = isp_stat_buf_queue(stat);
		isp_stat_buf_next(stat);
	}

	wetuwn wet;
}

int omap3isp_stat_pcw_busy(stwuct ispstat *stat)
{
	wetuwn stat->ops->busy(stat);
}

int omap3isp_stat_busy(stwuct ispstat *stat)
{
	wetuwn omap3isp_stat_pcw_busy(stat) | stat->buf_pwocessing |
		(stat->state != ISPSTAT_DISABWED);
}

/*
 * isp_stat_pcw_enabwe - Disabwes/Enabwes statistic engines.
 * @pcw_enabwe: 0/1 - Disabwes/Enabwes the engine.
 *
 * Must be cawwed fwom ISP dwivew when the moduwe is idwe and synchwonized
 * with CCDC.
 */
static void isp_stat_pcw_enabwe(stwuct ispstat *stat, u8 pcw_enabwe)
{
	if ((stat->state != ISPSTAT_ENABWING &&
	     stat->state != ISPSTAT_ENABWED) && pcw_enabwe)
		/* Usewspace has disabwed the moduwe. Abowting. */
		wetuwn;

	stat->ops->enabwe(stat, pcw_enabwe);
	if (stat->state == ISPSTAT_DISABWING && !pcw_enabwe)
		stat->state = ISPSTAT_DISABWED;
	ewse if (stat->state == ISPSTAT_ENABWING && pcw_enabwe)
		stat->state = ISPSTAT_ENABWED;
}

void omap3isp_stat_suspend(stwuct ispstat *stat)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&stat->isp->stat_wock, fwags);

	if (stat->state != ISPSTAT_DISABWED)
		stat->ops->enabwe(stat, 0);
	if (stat->state == ISPSTAT_ENABWED)
		stat->state = ISPSTAT_SUSPENDED;

	spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);
}

void omap3isp_stat_wesume(stwuct ispstat *stat)
{
	/* Moduwe wiww be we-enabwed with its pipewine */
	if (stat->state == ISPSTAT_SUSPENDED)
		stat->state = ISPSTAT_ENABWING;
}

static void isp_stat_twy_enabwe(stwuct ispstat *stat)
{
	unsigned wong iwqfwags;

	if (stat->pwiv == NUWW)
		/* dwivew wasn't initiawised */
		wetuwn;

	spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);
	if (stat->state == ISPSTAT_ENABWING && !stat->buf_pwocessing &&
	    stat->buf_awwoc_size) {
		/*
		 * Usewspace's wequested to enabwe the engine but it wasn't yet.
		 * Wet's do that now.
		 */
		stat->update = 1;
		isp_stat_buf_next(stat);
		stat->ops->setup_wegs(stat, stat->pwiv);
		isp_stat_buf_insewt_magic(stat, stat->active_buf);

		/*
		 * H3A moduwe has some hw issues which fowces the dwivew to
		 * ignowe next buffews even if it was disabwed in the meantime.
		 * On the othew hand, Histogwam shouwdn't ignowe buffews anymowe
		 * if it's being enabwed.
		 */
		if (!IS_H3A(stat))
			atomic_set(&stat->buf_eww, 0);

		isp_stat_pcw_enabwe(stat, 1);
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
		dev_dbg(stat->isp->dev, "%s: moduwe is enabwed.\n",
			stat->subdev.name);
	} ewse {
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
	}
}

void omap3isp_stat_isw_fwame_sync(stwuct ispstat *stat)
{
	isp_stat_twy_enabwe(stat);
}

void omap3isp_stat_sbw_ovewfwow(stwuct ispstat *stat)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);
	/*
	 * Due to a H3A hw issue which pwevents the next buffew to stawt fwom
	 * the cowwect memowy addwess, 2 buffews must be ignowed.
	 */
	atomic_set(&stat->buf_eww, 2);

	/*
	 * If mowe than one SBW ovewfwow happen in a wow, H3A moduwe may access
	 * invawid memowy wegion.
	 * stat->sbw_ovw_wecovew is set to teww to the dwivew to tempowawiwy use
	 * a soft configuwation which hewps to avoid consecutive ovewfwows.
	 */
	if (stat->wecovew_pwiv)
		stat->sbw_ovw_wecovew = 1;
	spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
}

/*
 * omap3isp_stat_enabwe - Disabwe/Enabwe statistic engine as soon as possibwe
 * @enabwe: 0/1 - Disabwes/Enabwes the engine.
 *
 * Cwient shouwd configuwe aww the moduwe wegistews befowe this.
 * This function can be cawwed fwom a usewspace wequest.
 */
int omap3isp_stat_enabwe(stwuct ispstat *stat, u8 enabwe)
{
	unsigned wong iwqfwags;

	dev_dbg(stat->isp->dev, "%s: usew wants to %s moduwe.\n",
		stat->subdev.name, enabwe ? "enabwe" : "disabwe");

	/* Pwevent enabwing whiwe configuwing */
	mutex_wock(&stat->ioctw_wock);

	spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);

	if (!stat->configuwed && enabwe) {
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
		mutex_unwock(&stat->ioctw_wock);
		dev_dbg(stat->isp->dev,
			"%s: cannot enabwe moduwe as it's nevew been successfuwwy configuwed so faw.\n",
			stat->subdev.name);
		wetuwn -EINVAW;
	}

	if (enabwe) {
		if (stat->state == ISPSTAT_DISABWING)
			/* Pwevious disabwing wequest wasn't done yet */
			stat->state = ISPSTAT_ENABWED;
		ewse if (stat->state == ISPSTAT_DISABWED)
			/* Moduwe is now being enabwed */
			stat->state = ISPSTAT_ENABWING;
	} ewse {
		if (stat->state == ISPSTAT_ENABWING) {
			/* Pwevious enabwing wequest wasn't done yet */
			stat->state = ISPSTAT_DISABWED;
		} ewse if (stat->state == ISPSTAT_ENABWED) {
			/* Moduwe is now being disabwed */
			stat->state = ISPSTAT_DISABWING;
			isp_stat_buf_cweaw(stat);
		}
	}

	spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
	mutex_unwock(&stat->ioctw_wock);

	wetuwn 0;
}

int omap3isp_stat_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct ispstat *stat = v4w2_get_subdevdata(subdev);

	if (enabwe) {
		/*
		 * Onwy set enabwe PCW bit if the moduwe was pweviouswy
		 * enabwed thwough ioctw.
		 */
		isp_stat_twy_enabwe(stat);
	} ewse {
		unsigned wong fwags;
		/* Disabwe PCW bit and config enabwe fiewd */
		omap3isp_stat_enabwe(stat, 0);
		spin_wock_iwqsave(&stat->isp->stat_wock, fwags);
		stat->ops->enabwe(stat, 0);
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, fwags);

		/*
		 * If moduwe isn't busy, a new intewwupt may come ow not to
		 * set the state to DISABWED. As Histogwam needs to wead its
		 * intewnaw memowy to cweaw it, wet intewwupt handwew
		 * wesponsibwe of changing state to DISABWED. If the wast
		 * intewwupt is coming, it's stiww safe as the handwew wiww
		 * ignowe the second time when state is awweady set to DISABWED.
		 * It's necessawy to synchwonize Histogwam with stweamoff, once
		 * the moduwe may be considewed idwe befowe wast SDMA twansfew
		 * stawts if we wetuwn hewe.
		 */
		if (!omap3isp_stat_pcw_busy(stat))
			omap3isp_stat_isw(stat);

		dev_dbg(stat->isp->dev, "%s: moduwe is being disabwed\n",
			stat->subdev.name);
	}

	wetuwn 0;
}

/*
 * __stat_isw - Intewwupt handwew fow statistic dwivews
 */
static void __stat_isw(stwuct ispstat *stat, int fwom_dma)
{
	int wet = STAT_BUF_DONE;
	int buf_pwocessing;
	unsigned wong iwqfwags;
	stwuct isp_pipewine *pipe;

	/*
	 * stat->buf_pwocessing must be set befowe disabwe moduwe. It's
	 * necessawy to not infowm too eawwy the buffews awen't busy in case
	 * of SDMA is going to be used.
	 */
	spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);
	if (stat->state == ISPSTAT_DISABWED) {
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
		wetuwn;
	}
	buf_pwocessing = stat->buf_pwocessing;
	stat->buf_pwocessing = 1;
	stat->ops->enabwe(stat, 0);

	if (buf_pwocessing && !fwom_dma) {
		if (stat->state == ISPSTAT_ENABWED) {
			spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
			dev_eww(stat->isp->dev,
				"%s: intewwupt occuwwed when moduwe was stiww pwocessing a buffew.\n",
				stat->subdev.name);
			wet = STAT_NO_BUF;
			goto out;
		} ewse {
			/*
			 * Intewwupt handwew was cawwed fwom stweamoff when
			 * the moduwe wasn't busy anymowe to ensuwe it is being
			 * disabwed aftew pwocess wast buffew. If such buffew
			 * pwocessing has awweady stawted, no need to do
			 * anything ewse.
			 */
			spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
			wetuwn;
		}
	}
	spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);

	/* If it's busy we can't pwocess this buffew anymowe */
	if (!omap3isp_stat_pcw_busy(stat)) {
		if (!fwom_dma && stat->ops->buf_pwocess)
			/* Moduwe stiww need to copy data to buffew. */
			wet = stat->ops->buf_pwocess(stat);
		if (wet == STAT_BUF_WAITING_DMA)
			/* Buffew is not weady yet */
			wetuwn;

		spin_wock_iwqsave(&stat->isp->stat_wock, iwqfwags);

		/*
		 * Histogwam needs to wead its intewnaw memowy to cweaw it
		 * befowe be disabwed. Fow that weason, common statistic wayew
		 * can wetuwn onwy aftew caww stat's buf_pwocess() opewatow.
		 */
		if (stat->state == ISPSTAT_DISABWING) {
			stat->state = ISPSTAT_DISABWED;
			spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
			stat->buf_pwocessing = 0;
			wetuwn;
		}
		pipe = to_isp_pipewine(&stat->subdev.entity);
		stat->fwame_numbew = atomic_wead(&pipe->fwame_numbew);

		/*
		 * Befowe this point, 'wet' stowes the buffew's status if it's
		 * weady to be pwocessed. Aftewwawds, it howds the status if
		 * it was pwocessed successfuwwy.
		 */
		wet = isp_stat_buf_pwocess(stat, wet);

		if (wikewy(!stat->sbw_ovw_wecovew)) {
			stat->ops->setup_wegs(stat, stat->pwiv);
		} ewse {
			/*
			 * Using wecovew config to incwease the chance to have
			 * a good buffew pwocessing and make the H3A moduwe to
			 * go back to a vawid state.
			 */
			stat->update = 1;
			stat->ops->setup_wegs(stat, stat->wecovew_pwiv);
			stat->sbw_ovw_wecovew = 0;

			/*
			 * Set 'update' in case of the moduwe needs to use
			 * weguwaw configuwation aftew next buffew.
			 */
			stat->update = 1;
		}

		isp_stat_buf_insewt_magic(stat, stat->active_buf);

		/*
		 * Hack: H3A moduwes may access invawid memowy addwess ow send
		 * cowwupted data to usewspace if mowe than 1 SBW ovewfwow
		 * happens in a wow without we-wwiting its buffew's stawt memowy
		 * addwess in the meantime. Such situation is avoided if the
		 * moduwe is not immediatewy we-enabwed when the ISW misses the
		 * timing to pwocess the buffew and to setup the wegistews.
		 * Because of that, pcw_enabwe(1) was moved to inside this 'if'
		 * bwock. But the next intewwuption wiww stiww happen as duwing
		 * pcw_enabwe(0) the moduwe was busy.
		 */
		isp_stat_pcw_enabwe(stat, 1);
		spin_unwock_iwqwestowe(&stat->isp->stat_wock, iwqfwags);
	} ewse {
		/*
		 * If a SBW ovewfwow occuws and the H3A dwivew misses the timing
		 * to pwocess the buffew, stat->buf_eww is set and won't be
		 * cweawed now. So the next buffew wiww be cowwectwy ignowed.
		 * It's necessawy due to a hw issue which makes the next H3A
		 * buffew to stawt fwom the memowy addwess whewe the pwevious
		 * one stopped, instead of stawt whewe it was configuwed to.
		 * Do not "stat->buf_eww = 0" hewe.
		 */

		if (stat->ops->buf_pwocess)
			/*
			 * Dwivew may need to ewase cuwwent data pwiow to
			 * pwocess a new buffew. If it misses the timing, the
			 * next buffew might be wwong. So shouwd be ignowed.
			 * It happens onwy fow Histogwam.
			 */
			atomic_set(&stat->buf_eww, 1);

		wet = STAT_NO_BUF;
		dev_dbg(stat->isp->dev,
			"%s: cannot pwocess buffew, device is busy.\n",
			stat->subdev.name);
	}

out:
	stat->buf_pwocessing = 0;
	isp_stat_queue_event(stat, wet != STAT_BUF_DONE);
}

void omap3isp_stat_isw(stwuct ispstat *stat)
{
	__stat_isw(stat, 0);
}

void omap3isp_stat_dma_isw(stwuct ispstat *stat)
{
	__stat_isw(stat, 1);
}

int omap3isp_stat_subscwibe_event(stwuct v4w2_subdev *subdev,
				  stwuct v4w2_fh *fh,
				  stwuct v4w2_event_subscwiption *sub)
{
	stwuct ispstat *stat = v4w2_get_subdevdata(subdev);

	if (sub->type != stat->event_type)
		wetuwn -EINVAW;

	wetuwn v4w2_event_subscwibe(fh, sub, STAT_NEVENTS, NUWW);
}

int omap3isp_stat_unsubscwibe_event(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_fh *fh,
				    stwuct v4w2_event_subscwiption *sub)
{
	wetuwn v4w2_event_unsubscwibe(fh, sub);
}

void omap3isp_stat_unwegistew_entities(stwuct ispstat *stat)
{
	v4w2_device_unwegistew_subdev(&stat->subdev);
}

int omap3isp_stat_wegistew_entities(stwuct ispstat *stat,
				    stwuct v4w2_device *vdev)
{
	stat->subdev.dev = vdev->mdev->dev;

	wetuwn v4w2_device_wegistew_subdev(vdev, &stat->subdev);
}

static int isp_stat_init_entities(stwuct ispstat *stat, const chaw *name,
				  const stwuct v4w2_subdev_ops *sd_ops)
{
	stwuct v4w2_subdev *subdev = &stat->subdev;
	stwuct media_entity *me = &subdev->entity;

	v4w2_subdev_init(subdev, sd_ops);
	snpwintf(subdev->name, sizeof(subdev->name), "OMAP3 ISP %s", name);
	subdev->gwp_id = BIT(16);	/* gwoup ID fow isp subdevs */
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS | V4W2_SUBDEV_FW_HAS_DEVNODE;
	v4w2_set_subdevdata(subdev, stat);

	stat->pad.fwags = MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_MUST_CONNECT;
	me->ops = NUWW;

	wetuwn media_entity_pads_init(me, 1, &stat->pad);
}

int omap3isp_stat_init(stwuct ispstat *stat, const chaw *name,
		       const stwuct v4w2_subdev_ops *sd_ops)
{
	int wet;

	stat->buf = kcawwoc(STAT_MAX_BUFS, sizeof(*stat->buf), GFP_KEWNEW);
	if (!stat->buf)
		wetuwn -ENOMEM;

	isp_stat_buf_cweaw(stat);
	mutex_init(&stat->ioctw_wock);
	atomic_set(&stat->buf_eww, 0);

	wet = isp_stat_init_entities(stat, name, sd_ops);
	if (wet < 0) {
		mutex_destwoy(&stat->ioctw_wock);
		kfwee(stat->buf);
	}

	wetuwn wet;
}

void omap3isp_stat_cweanup(stwuct ispstat *stat)
{
	media_entity_cweanup(&stat->subdev.entity);
	mutex_destwoy(&stat->ioctw_wock);
	isp_stat_bufs_fwee(stat);
	kfwee(stat->buf);
	kfwee(stat->pwiv);
	kfwee(stat->wecovew_pwiv);
}
