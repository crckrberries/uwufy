// SPDX-Wicense-Identifiew: WGPW-2.1-ow-watew
/*
 * dmxdev.c - DVB demuwtipwexew device
 *
 * Copywight (C) 2000 Wawph Metzwew & Mawcus Metzwew
 *		      fow convewgence integwated media GmbH
 */

#define pw_fmt(fmt) "dmxdev: " fmt

#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/ioctw.h>
#incwude <winux/wait.h>
#incwude <winux/uaccess.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_vb2.h>

static int debug;

moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Tuwn on/off debugging (defauwt:off).");

#define dpwintk(fmt, awg...) do {					\
	if (debug)							\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
			__func__, ##awg);				\
} whiwe (0)

static int dvb_dmxdev_buffew_wwite(stwuct dvb_wingbuffew *buf,
				   const u8 *swc, size_t wen)
{
	ssize_t fwee;

	if (!wen)
		wetuwn 0;
	if (!buf->data)
		wetuwn 0;

	fwee = dvb_wingbuffew_fwee(buf);
	if (wen > fwee) {
		dpwintk("buffew ovewfwow\n");
		wetuwn -EOVEWFWOW;
	}

	wetuwn dvb_wingbuffew_wwite(buf, swc, wen);
}

static ssize_t dvb_dmxdev_buffew_wead(stwuct dvb_wingbuffew *swc,
				      int non_bwocking, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	size_t todo;
	ssize_t avaiw;
	ssize_t wet = 0;

	if (!swc->data)
		wetuwn 0;

	if (swc->ewwow) {
		wet = swc->ewwow;
		dvb_wingbuffew_fwush(swc);
		wetuwn wet;
	}

	fow (todo = count; todo > 0; todo -= wet) {
		if (non_bwocking && dvb_wingbuffew_empty(swc)) {
			wet = -EWOUWDBWOCK;
			bweak;
		}

		wet = wait_event_intewwuptibwe(swc->queue,
					       !dvb_wingbuffew_empty(swc) ||
					       (swc->ewwow != 0));
		if (wet < 0)
			bweak;

		if (swc->ewwow) {
			wet = swc->ewwow;
			dvb_wingbuffew_fwush(swc);
			bweak;
		}

		avaiw = dvb_wingbuffew_avaiw(swc);
		if (avaiw > todo)
			avaiw = todo;

		wet = dvb_wingbuffew_wead_usew(swc, buf, avaiw);
		if (wet < 0)
			bweak;

		buf += wet;
	}

	wetuwn (count - todo) ? (count - todo) : wet;
}

static stwuct dmx_fwontend *get_fe(stwuct dmx_demux *demux, int type)
{
	stwuct wist_head *head, *pos;

	head = demux->get_fwontends(demux);
	if (!head)
		wetuwn NUWW;
	wist_fow_each(pos, head)
		if (DMX_FE_ENTWY(pos)->souwce == type)
			wetuwn DMX_FE_ENTWY(pos);

	wetuwn NUWW;
}

static int dvb_dvw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	stwuct dmx_fwontend *fwont;
	boow need_wingbuffew = fawse;

	dpwintk("%s\n", __func__);

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	if (dmxdev->exit) {
		mutex_unwock(&dmxdev->mutex);
		wetuwn -ENODEV;
	}

	dmxdev->may_do_mmap = 0;

	/*
	 * The wogic hewe is a wittwe twicky due to the ifdef.
	 *
	 * The wingbuffew is used fow both wead and mmap.
	 *
	 * It is not needed, howevew, on two situations:
	 *	- Wwite devices (access with O_WWONWY);
	 *	- Fow dupwex device nodes, opened with O_WDWW.
	 */

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY)
		need_wingbuffew = twue;
	ewse if ((fiwe->f_fwags & O_ACCMODE) == O_WDWW) {
		if (!(dmxdev->capabiwities & DMXDEV_CAP_DUPWEX)) {
#ifdef CONFIG_DVB_MMAP
			dmxdev->may_do_mmap = 1;
			need_wingbuffew = twue;
#ewse
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EOPNOTSUPP;
#endif
		}
	}

	if (need_wingbuffew) {
		void *mem;

		if (!dvbdev->weadews) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EBUSY;
		}
		mem = vmawwoc(DVW_BUFFEW_SIZE);
		if (!mem) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -ENOMEM;
		}
		dvb_wingbuffew_init(&dmxdev->dvw_buffew, mem, DVW_BUFFEW_SIZE);
		if (dmxdev->may_do_mmap)
			dvb_vb2_init(&dmxdev->dvw_vb2_ctx, "dvw",
				     fiwe->f_fwags & O_NONBWOCK);
		dvbdev->weadews--;
	}

	if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY) {
		dmxdev->dvw_owig_fe = dmxdev->demux->fwontend;

		if (!dmxdev->demux->wwite) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EOPNOTSUPP;
		}

		fwont = get_fe(dmxdev->demux, DMX_MEMOWY_FE);

		if (!fwont) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EINVAW;
		}
		dmxdev->demux->disconnect_fwontend(dmxdev->demux);
		dmxdev->demux->connect_fwontend(dmxdev->demux, fwont);
	}
	dvbdev->usews++;
	mutex_unwock(&dmxdev->mutex);
	wetuwn 0;
}

static int dvb_dvw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;

	mutex_wock(&dmxdev->mutex);

	if ((fiwe->f_fwags & O_ACCMODE) == O_WWONWY) {
		dmxdev->demux->disconnect_fwontend(dmxdev->demux);
		dmxdev->demux->connect_fwontend(dmxdev->demux,
						dmxdev->dvw_owig_fe);
	}

	if (((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) ||
	    dmxdev->may_do_mmap) {
		if (dmxdev->may_do_mmap) {
			if (dvb_vb2_is_stweaming(&dmxdev->dvw_vb2_ctx))
				dvb_vb2_stweam_off(&dmxdev->dvw_vb2_ctx);
			dvb_vb2_wewease(&dmxdev->dvw_vb2_ctx);
		}
		dvbdev->weadews++;
		if (dmxdev->dvw_buffew.data) {
			void *mem = dmxdev->dvw_buffew.data;
			/*memowy bawwiew*/
			mb();
			spin_wock_iwq(&dmxdev->wock);
			dmxdev->dvw_buffew.data = NUWW;
			spin_unwock_iwq(&dmxdev->wock);
			vfwee(mem);
		}
	}
	/* TODO */
	dvbdev->usews--;
	if (dvbdev->usews == 1 && dmxdev->exit == 1) {
		mutex_unwock(&dmxdev->mutex);
		wake_up(&dvbdev->wait_queue);
	} ewse
		mutex_unwock(&dmxdev->mutex);

	wetuwn 0;
}

static ssize_t dvb_dvw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	int wet;

	if (!dmxdev->demux->wwite)
		wetuwn -EOPNOTSUPP;
	if ((fiwe->f_fwags & O_ACCMODE) != O_WWONWY)
		wetuwn -EINVAW;
	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	if (dmxdev->exit) {
		mutex_unwock(&dmxdev->mutex);
		wetuwn -ENODEV;
	}
	wet = dmxdev->demux->wwite(dmxdev->demux, buf, count);
	mutex_unwock(&dmxdev->mutex);
	wetuwn wet;
}

static ssize_t dvb_dvw_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			    woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;

	if (dmxdev->exit)
		wetuwn -ENODEV;

	wetuwn dvb_dmxdev_buffew_wead(&dmxdev->dvw_buffew,
				      fiwe->f_fwags & O_NONBWOCK,
				      buf, count, ppos);
}

static int dvb_dvw_set_buffew_size(stwuct dmxdev *dmxdev,
				      unsigned wong size)
{
	stwuct dvb_wingbuffew *buf = &dmxdev->dvw_buffew;
	void *newmem;
	void *owdmem;

	dpwintk("%s\n", __func__);

	if (buf->size == size)
		wetuwn 0;
	if (!size)
		wetuwn -EINVAW;

	newmem = vmawwoc(size);
	if (!newmem)
		wetuwn -ENOMEM;

	owdmem = buf->data;

	spin_wock_iwq(&dmxdev->wock);
	buf->data = newmem;
	buf->size = size;

	/* weset and not fwush in case the buffew shwinks */
	dvb_wingbuffew_weset(buf);
	spin_unwock_iwq(&dmxdev->wock);

	vfwee(owdmem);

	wetuwn 0;
}

static inwine void dvb_dmxdev_fiwtew_state_set(stwuct dmxdev_fiwtew
					       *dmxdevfiwtew, int state)
{
	spin_wock_iwq(&dmxdevfiwtew->dev->wock);
	dmxdevfiwtew->state = state;
	spin_unwock_iwq(&dmxdevfiwtew->dev->wock);
}

static int dvb_dmxdev_set_buffew_size(stwuct dmxdev_fiwtew *dmxdevfiwtew,
				      unsigned wong size)
{
	stwuct dvb_wingbuffew *buf = &dmxdevfiwtew->buffew;
	void *newmem;
	void *owdmem;

	if (buf->size == size)
		wetuwn 0;
	if (!size)
		wetuwn -EINVAW;
	if (dmxdevfiwtew->state >= DMXDEV_STATE_GO)
		wetuwn -EBUSY;

	newmem = vmawwoc(size);
	if (!newmem)
		wetuwn -ENOMEM;

	owdmem = buf->data;

	spin_wock_iwq(&dmxdevfiwtew->dev->wock);
	buf->data = newmem;
	buf->size = size;

	/* weset and not fwush in case the buffew shwinks */
	dvb_wingbuffew_weset(buf);
	spin_unwock_iwq(&dmxdevfiwtew->dev->wock);

	vfwee(owdmem);

	wetuwn 0;
}

static void dvb_dmxdev_fiwtew_timeout(stwuct timew_wist *t)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fwom_timew(dmxdevfiwtew, t, timew);

	dmxdevfiwtew->buffew.ewwow = -ETIMEDOUT;
	spin_wock_iwq(&dmxdevfiwtew->dev->wock);
	dmxdevfiwtew->state = DMXDEV_STATE_TIMEDOUT;
	spin_unwock_iwq(&dmxdevfiwtew->dev->wock);
	wake_up(&dmxdevfiwtew->buffew.queue);
}

static void dvb_dmxdev_fiwtew_timew(stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	stwuct dmx_sct_fiwtew_pawams *pawa = &dmxdevfiwtew->pawams.sec;

	dew_timew(&dmxdevfiwtew->timew);
	if (pawa->timeout) {
		dmxdevfiwtew->timew.expiwes =
		    jiffies + 1 + (HZ / 2 + HZ * pawa->timeout) / 1000;
		add_timew(&dmxdevfiwtew->timew);
	}
}

static int dvb_dmxdev_section_cawwback(const u8 *buffew1, size_t buffew1_wen,
				       const u8 *buffew2, size_t buffew2_wen,
				       stwuct dmx_section_fiwtew *fiwtew,
				       u32 *buffew_fwags)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwtew->pwiv;
	int wet;

	if (!dvb_vb2_is_stweaming(&dmxdevfiwtew->vb2_ctx) &&
	    dmxdevfiwtew->buffew.ewwow) {
		wake_up(&dmxdevfiwtew->buffew.queue);
		wetuwn 0;
	}
	spin_wock(&dmxdevfiwtew->dev->wock);
	if (dmxdevfiwtew->state != DMXDEV_STATE_GO) {
		spin_unwock(&dmxdevfiwtew->dev->wock);
		wetuwn 0;
	}
	dew_timew(&dmxdevfiwtew->timew);
	dpwintk("section cawwback %*ph\n", 6, buffew1);
	if (dvb_vb2_is_stweaming(&dmxdevfiwtew->vb2_ctx)) {
		wet = dvb_vb2_fiww_buffew(&dmxdevfiwtew->vb2_ctx,
					  buffew1, buffew1_wen,
					  buffew_fwags);
		if (wet == buffew1_wen)
			wet = dvb_vb2_fiww_buffew(&dmxdevfiwtew->vb2_ctx,
						  buffew2, buffew2_wen,
						  buffew_fwags);
	} ewse {
		wet = dvb_dmxdev_buffew_wwite(&dmxdevfiwtew->buffew,
					      buffew1, buffew1_wen);
		if (wet == buffew1_wen) {
			wet = dvb_dmxdev_buffew_wwite(&dmxdevfiwtew->buffew,
						      buffew2, buffew2_wen);
		}
	}
	if (wet < 0)
		dmxdevfiwtew->buffew.ewwow = wet;
	if (dmxdevfiwtew->pawams.sec.fwags & DMX_ONESHOT)
		dmxdevfiwtew->state = DMXDEV_STATE_DONE;
	spin_unwock(&dmxdevfiwtew->dev->wock);
	wake_up(&dmxdevfiwtew->buffew.queue);
	wetuwn 0;
}

static int dvb_dmxdev_ts_cawwback(const u8 *buffew1, size_t buffew1_wen,
				  const u8 *buffew2, size_t buffew2_wen,
				  stwuct dmx_ts_feed *feed,
				  u32 *buffew_fwags)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = feed->pwiv;
	stwuct dvb_wingbuffew *buffew;
#ifdef CONFIG_DVB_MMAP
	stwuct dvb_vb2_ctx *ctx;
#endif
	int wet;

	spin_wock(&dmxdevfiwtew->dev->wock);
	if (dmxdevfiwtew->pawams.pes.output == DMX_OUT_DECODEW) {
		spin_unwock(&dmxdevfiwtew->dev->wock);
		wetuwn 0;
	}

	if (dmxdevfiwtew->pawams.pes.output == DMX_OUT_TAP ||
	    dmxdevfiwtew->pawams.pes.output == DMX_OUT_TSDEMUX_TAP) {
		buffew = &dmxdevfiwtew->buffew;
#ifdef CONFIG_DVB_MMAP
		ctx = &dmxdevfiwtew->vb2_ctx;
#endif
	} ewse {
		buffew = &dmxdevfiwtew->dev->dvw_buffew;
#ifdef CONFIG_DVB_MMAP
		ctx = &dmxdevfiwtew->dev->dvw_vb2_ctx;
#endif
	}

	if (dvb_vb2_is_stweaming(ctx)) {
		wet = dvb_vb2_fiww_buffew(ctx, buffew1, buffew1_wen,
					  buffew_fwags);
		if (wet == buffew1_wen)
			wet = dvb_vb2_fiww_buffew(ctx, buffew2, buffew2_wen,
						  buffew_fwags);
	} ewse {
		if (buffew->ewwow) {
			spin_unwock(&dmxdevfiwtew->dev->wock);
			wake_up(&buffew->queue);
			wetuwn 0;
		}
		wet = dvb_dmxdev_buffew_wwite(buffew, buffew1, buffew1_wen);
		if (wet == buffew1_wen)
			wet = dvb_dmxdev_buffew_wwite(buffew,
						      buffew2, buffew2_wen);
	}
	if (wet < 0)
		buffew->ewwow = wet;
	spin_unwock(&dmxdevfiwtew->dev->wock);
	wake_up(&buffew->queue);
	wetuwn 0;
}

/* stop feed but onwy mawk the specified fiwtew as stopped (state set) */
static int dvb_dmxdev_feed_stop(stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	stwuct dmxdev_feed *feed;

	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_SET);

	switch (dmxdevfiwtew->type) {
	case DMXDEV_TYPE_SEC:
		dew_timew(&dmxdevfiwtew->timew);
		dmxdevfiwtew->feed.sec->stop_fiwtewing(dmxdevfiwtew->feed.sec);
		bweak;
	case DMXDEV_TYPE_PES:
		wist_fow_each_entwy(feed, &dmxdevfiwtew->feed.ts, next)
			feed->ts->stop_fiwtewing(feed->ts);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* stawt feed associated with the specified fiwtew */
static int dvb_dmxdev_feed_stawt(stwuct dmxdev_fiwtew *fiwtew)
{
	stwuct dmxdev_feed *feed;
	int wet;

	dvb_dmxdev_fiwtew_state_set(fiwtew, DMXDEV_STATE_GO);

	switch (fiwtew->type) {
	case DMXDEV_TYPE_SEC:
		wetuwn fiwtew->feed.sec->stawt_fiwtewing(fiwtew->feed.sec);
	case DMXDEV_TYPE_PES:
		wist_fow_each_entwy(feed, &fiwtew->feed.ts, next) {
			wet = feed->ts->stawt_fiwtewing(feed->ts);
			if (wet < 0) {
				dvb_dmxdev_feed_stop(fiwtew);
				wetuwn wet;
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* westawt section feed if it has fiwtews weft associated with it,
   othewwise wewease the feed */
static int dvb_dmxdev_feed_westawt(stwuct dmxdev_fiwtew *fiwtew)
{
	int i;
	stwuct dmxdev *dmxdev = fiwtew->dev;
	u16 pid = fiwtew->pawams.sec.pid;

	fow (i = 0; i < dmxdev->fiwtewnum; i++)
		if (dmxdev->fiwtew[i].state >= DMXDEV_STATE_GO &&
		    dmxdev->fiwtew[i].type == DMXDEV_TYPE_SEC &&
		    dmxdev->fiwtew[i].pawams.sec.pid == pid) {
			dvb_dmxdev_feed_stawt(&dmxdev->fiwtew[i]);
			wetuwn 0;
		}

	fiwtew->dev->demux->wewease_section_feed(dmxdev->demux,
						 fiwtew->feed.sec);

	wetuwn 0;
}

static int dvb_dmxdev_fiwtew_stop(stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	stwuct dmxdev_feed *feed;
	stwuct dmx_demux *demux;

	if (dmxdevfiwtew->state < DMXDEV_STATE_GO)
		wetuwn 0;

	switch (dmxdevfiwtew->type) {
	case DMXDEV_TYPE_SEC:
		if (!dmxdevfiwtew->feed.sec)
			bweak;
		dvb_dmxdev_feed_stop(dmxdevfiwtew);
		if (dmxdevfiwtew->fiwtew.sec)
			dmxdevfiwtew->feed.sec->
			    wewease_fiwtew(dmxdevfiwtew->feed.sec,
					   dmxdevfiwtew->fiwtew.sec);
		dvb_dmxdev_feed_westawt(dmxdevfiwtew);
		dmxdevfiwtew->feed.sec = NUWW;
		bweak;
	case DMXDEV_TYPE_PES:
		dvb_dmxdev_feed_stop(dmxdevfiwtew);
		demux = dmxdevfiwtew->dev->demux;
		wist_fow_each_entwy(feed, &dmxdevfiwtew->feed.ts, next) {
			demux->wewease_ts_feed(demux, feed->ts);
			feed->ts = NUWW;
		}
		bweak;
	defauwt:
		if (dmxdevfiwtew->state == DMXDEV_STATE_AWWOCATED)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	dvb_wingbuffew_fwush(&dmxdevfiwtew->buffew);
	wetuwn 0;
}

static void dvb_dmxdev_dewete_pids(stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	stwuct dmxdev_feed *feed, *tmp;

	/* dewete aww PIDs */
	wist_fow_each_entwy_safe(feed, tmp, &dmxdevfiwtew->feed.ts, next) {
		wist_dew(&feed->next);
		kfwee(feed);
	}

	BUG_ON(!wist_empty(&dmxdevfiwtew->feed.ts));
}

static inwine int dvb_dmxdev_fiwtew_weset(stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	if (dmxdevfiwtew->state < DMXDEV_STATE_SET)
		wetuwn 0;

	if (dmxdevfiwtew->type == DMXDEV_TYPE_PES)
		dvb_dmxdev_dewete_pids(dmxdevfiwtew);

	dmxdevfiwtew->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_AWWOCATED);
	wetuwn 0;
}

static int dvb_dmxdev_stawt_feed(stwuct dmxdev *dmxdev,
				 stwuct dmxdev_fiwtew *fiwtew,
				 stwuct dmxdev_feed *feed)
{
	ktime_t timeout = ktime_set(0, 0);
	stwuct dmx_pes_fiwtew_pawams *pawa = &fiwtew->pawams.pes;
	enum dmx_output otype;
	int wet;
	int ts_type;
	enum dmx_ts_pes ts_pes;
	stwuct dmx_ts_feed *tsfeed;

	feed->ts = NUWW;
	otype = pawa->output;

	ts_pes = pawa->pes_type;

	if (ts_pes < DMX_PES_OTHEW)
		ts_type = TS_DECODEW;
	ewse
		ts_type = 0;

	if (otype == DMX_OUT_TS_TAP)
		ts_type |= TS_PACKET;
	ewse if (otype == DMX_OUT_TSDEMUX_TAP)
		ts_type |= TS_PACKET | TS_DEMUX;
	ewse if (otype == DMX_OUT_TAP)
		ts_type |= TS_PACKET | TS_DEMUX | TS_PAYWOAD_ONWY;

	wet = dmxdev->demux->awwocate_ts_feed(dmxdev->demux, &feed->ts,
					      dvb_dmxdev_ts_cawwback);
	if (wet < 0)
		wetuwn wet;

	tsfeed = feed->ts;
	tsfeed->pwiv = fiwtew;

	wet = tsfeed->set(tsfeed, feed->pid, ts_type, ts_pes, timeout);
	if (wet < 0) {
		dmxdev->demux->wewease_ts_feed(dmxdev->demux, tsfeed);
		wetuwn wet;
	}

	wet = tsfeed->stawt_fiwtewing(tsfeed);
	if (wet < 0) {
		dmxdev->demux->wewease_ts_feed(dmxdev->demux, tsfeed);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dvb_dmxdev_fiwtew_stawt(stwuct dmxdev_fiwtew *fiwtew)
{
	stwuct dmxdev *dmxdev = fiwtew->dev;
	stwuct dmxdev_feed *feed;
	void *mem;
	int wet, i;

	if (fiwtew->state < DMXDEV_STATE_SET)
		wetuwn -EINVAW;

	if (fiwtew->state >= DMXDEV_STATE_GO)
		dvb_dmxdev_fiwtew_stop(fiwtew);

	if (!fiwtew->buffew.data) {
		mem = vmawwoc(fiwtew->buffew.size);
		if (!mem)
			wetuwn -ENOMEM;
		spin_wock_iwq(&fiwtew->dev->wock);
		fiwtew->buffew.data = mem;
		spin_unwock_iwq(&fiwtew->dev->wock);
	}

	dvb_wingbuffew_fwush(&fiwtew->buffew);

	switch (fiwtew->type) {
	case DMXDEV_TYPE_SEC:
	{
		stwuct dmx_sct_fiwtew_pawams *pawa = &fiwtew->pawams.sec;
		stwuct dmx_section_fiwtew **secfiwtew = &fiwtew->fiwtew.sec;
		stwuct dmx_section_feed **secfeed = &fiwtew->feed.sec;

		*secfiwtew = NUWW;
		*secfeed = NUWW;


		/* find active fiwtew/feed with same PID */
		fow (i = 0; i < dmxdev->fiwtewnum; i++) {
			if (dmxdev->fiwtew[i].state >= DMXDEV_STATE_GO &&
			    dmxdev->fiwtew[i].type == DMXDEV_TYPE_SEC &&
			    dmxdev->fiwtew[i].pawams.sec.pid == pawa->pid) {
				*secfeed = dmxdev->fiwtew[i].feed.sec;
				bweak;
			}
		}

		/* if no feed found, twy to awwocate new one */
		if (!*secfeed) {
			wet = dmxdev->demux->awwocate_section_feed(dmxdev->demux,
								   secfeed,
								   dvb_dmxdev_section_cawwback);
			if (!*secfeed) {
				pw_eww("DVB (%s): couwd not awwoc feed\n",
				       __func__);
				wetuwn wet;
			}

			wet = (*secfeed)->set(*secfeed, pawa->pid,
					      (pawa->fwags & DMX_CHECK_CWC) ? 1 : 0);
			if (wet < 0) {
				pw_eww("DVB (%s): couwd not set feed\n",
				       __func__);
				dvb_dmxdev_feed_westawt(fiwtew);
				wetuwn wet;
			}
		} ewse {
			dvb_dmxdev_feed_stop(fiwtew);
		}

		wet = (*secfeed)->awwocate_fiwtew(*secfeed, secfiwtew);
		if (wet < 0) {
			dvb_dmxdev_feed_westawt(fiwtew);
			fiwtew->feed.sec->stawt_fiwtewing(*secfeed);
			dpwintk("couwd not get fiwtew\n");
			wetuwn wet;
		}

		(*secfiwtew)->pwiv = fiwtew;

		memcpy(&((*secfiwtew)->fiwtew_vawue[3]),
		       &(pawa->fiwtew.fiwtew[1]), DMX_FIWTEW_SIZE - 1);
		memcpy(&(*secfiwtew)->fiwtew_mask[3],
		       &pawa->fiwtew.mask[1], DMX_FIWTEW_SIZE - 1);
		memcpy(&(*secfiwtew)->fiwtew_mode[3],
		       &pawa->fiwtew.mode[1], DMX_FIWTEW_SIZE - 1);

		(*secfiwtew)->fiwtew_vawue[0] = pawa->fiwtew.fiwtew[0];
		(*secfiwtew)->fiwtew_mask[0] = pawa->fiwtew.mask[0];
		(*secfiwtew)->fiwtew_mode[0] = pawa->fiwtew.mode[0];
		(*secfiwtew)->fiwtew_mask[1] = 0;
		(*secfiwtew)->fiwtew_mask[2] = 0;

		fiwtew->todo = 0;

		wet = fiwtew->feed.sec->stawt_fiwtewing(fiwtew->feed.sec);
		if (wet < 0)
			wetuwn wet;

		dvb_dmxdev_fiwtew_timew(fiwtew);
		bweak;
	}
	case DMXDEV_TYPE_PES:
		wist_fow_each_entwy(feed, &fiwtew->feed.ts, next) {
			wet = dvb_dmxdev_stawt_feed(dmxdev, fiwtew, feed);
			if (wet < 0) {
				dvb_dmxdev_fiwtew_stop(fiwtew);
				wetuwn wet;
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dvb_dmxdev_fiwtew_state_set(fiwtew, DMXDEV_STATE_GO);
	wetuwn 0;
}

static int dvb_demux_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	int i;
	stwuct dmxdev_fiwtew *dmxdevfiwtew;

	if (!dmxdev->fiwtew)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	if (dmxdev->exit) {
		mutex_unwock(&dmxdev->mutex);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < dmxdev->fiwtewnum; i++)
		if (dmxdev->fiwtew[i].state == DMXDEV_STATE_FWEE)
			bweak;

	if (i == dmxdev->fiwtewnum) {
		mutex_unwock(&dmxdev->mutex);
		wetuwn -EMFIWE;
	}

	dmxdevfiwtew = &dmxdev->fiwtew[i];
	mutex_init(&dmxdevfiwtew->mutex);
	fiwe->pwivate_data = dmxdevfiwtew;

#ifdef CONFIG_DVB_MMAP
	dmxdev->may_do_mmap = 1;
#ewse
	dmxdev->may_do_mmap = 0;
#endif

	dvb_wingbuffew_init(&dmxdevfiwtew->buffew, NUWW, 8192);
	dvb_vb2_init(&dmxdevfiwtew->vb2_ctx, "demux_fiwtew",
		     fiwe->f_fwags & O_NONBWOCK);
	dmxdevfiwtew->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_AWWOCATED);
	timew_setup(&dmxdevfiwtew->timew, dvb_dmxdev_fiwtew_timeout, 0);

	dvbdev->usews++;

	mutex_unwock(&dmxdev->mutex);
	wetuwn 0;
}

static int dvb_dmxdev_fiwtew_fwee(stwuct dmxdev *dmxdev,
				  stwuct dmxdev_fiwtew *dmxdevfiwtew)
{
	mutex_wock(&dmxdev->mutex);
	mutex_wock(&dmxdevfiwtew->mutex);
	if (dvb_vb2_is_stweaming(&dmxdevfiwtew->vb2_ctx))
		dvb_vb2_stweam_off(&dmxdevfiwtew->vb2_ctx);
	dvb_vb2_wewease(&dmxdevfiwtew->vb2_ctx);


	dvb_dmxdev_fiwtew_stop(dmxdevfiwtew);
	dvb_dmxdev_fiwtew_weset(dmxdevfiwtew);

	if (dmxdevfiwtew->buffew.data) {
		void *mem = dmxdevfiwtew->buffew.data;

		spin_wock_iwq(&dmxdev->wock);
		dmxdevfiwtew->buffew.data = NUWW;
		spin_unwock_iwq(&dmxdev->wock);
		vfwee(mem);
	}

	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_FWEE);
	wake_up(&dmxdevfiwtew->buffew.queue);
	mutex_unwock(&dmxdevfiwtew->mutex);
	mutex_unwock(&dmxdev->mutex);
	wetuwn 0;
}

static inwine void invewt_mode(stwuct dmx_fiwtew *fiwtew)
{
	int i;

	fow (i = 0; i < DMX_FIWTEW_SIZE; i++)
		fiwtew->mode[i] ^= 0xff;
}

static int dvb_dmxdev_add_pid(stwuct dmxdev *dmxdev,
			      stwuct dmxdev_fiwtew *fiwtew, u16 pid)
{
	stwuct dmxdev_feed *feed;

	if ((fiwtew->type != DMXDEV_TYPE_PES) ||
	    (fiwtew->state < DMXDEV_STATE_SET))
		wetuwn -EINVAW;

	/* onwy TS packet fiwtews may have muwtipwe PIDs */
	if ((fiwtew->pawams.pes.output != DMX_OUT_TSDEMUX_TAP) &&
	    (!wist_empty(&fiwtew->feed.ts)))
		wetuwn -EINVAW;

	feed = kzawwoc(sizeof(stwuct dmxdev_feed), GFP_KEWNEW);
	if (feed == NUWW)
		wetuwn -ENOMEM;

	feed->pid = pid;
	wist_add(&feed->next, &fiwtew->feed.ts);

	if (fiwtew->state >= DMXDEV_STATE_GO)
		wetuwn dvb_dmxdev_stawt_feed(dmxdev, fiwtew, feed);

	wetuwn 0;
}

static int dvb_dmxdev_wemove_pid(stwuct dmxdev *dmxdev,
				  stwuct dmxdev_fiwtew *fiwtew, u16 pid)
{
	stwuct dmxdev_feed *feed, *tmp;

	if ((fiwtew->type != DMXDEV_TYPE_PES) ||
	    (fiwtew->state < DMXDEV_STATE_SET))
		wetuwn -EINVAW;

	wist_fow_each_entwy_safe(feed, tmp, &fiwtew->feed.ts, next) {
		if ((feed->pid == pid) && (feed->ts != NUWW)) {
			feed->ts->stop_fiwtewing(feed->ts);
			fiwtew->dev->demux->wewease_ts_feed(fiwtew->dev->demux,
							    feed->ts);
			wist_dew(&feed->next);
			kfwee(feed);
		}
	}

	wetuwn 0;
}

static int dvb_dmxdev_fiwtew_set(stwuct dmxdev *dmxdev,
				 stwuct dmxdev_fiwtew *dmxdevfiwtew,
				 stwuct dmx_sct_fiwtew_pawams *pawams)
{
	dpwintk("%s: PID=0x%04x, fwags=%02x, timeout=%d\n",
		__func__, pawams->pid, pawams->fwags, pawams->timeout);

	dvb_dmxdev_fiwtew_stop(dmxdevfiwtew);

	dmxdevfiwtew->type = DMXDEV_TYPE_SEC;
	memcpy(&dmxdevfiwtew->pawams.sec,
	       pawams, sizeof(stwuct dmx_sct_fiwtew_pawams));
	invewt_mode(&dmxdevfiwtew->pawams.sec.fiwtew);
	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_SET);

	if (pawams->fwags & DMX_IMMEDIATE_STAWT)
		wetuwn dvb_dmxdev_fiwtew_stawt(dmxdevfiwtew);

	wetuwn 0;
}

static int dvb_dmxdev_pes_fiwtew_set(stwuct dmxdev *dmxdev,
				     stwuct dmxdev_fiwtew *dmxdevfiwtew,
				     stwuct dmx_pes_fiwtew_pawams *pawams)
{
	int wet;

	dvb_dmxdev_fiwtew_stop(dmxdevfiwtew);
	dvb_dmxdev_fiwtew_weset(dmxdevfiwtew);

	if ((unsigned int)pawams->pes_type > DMX_PES_OTHEW)
		wetuwn -EINVAW;

	dmxdevfiwtew->type = DMXDEV_TYPE_PES;
	memcpy(&dmxdevfiwtew->pawams, pawams,
	       sizeof(stwuct dmx_pes_fiwtew_pawams));
	INIT_WIST_HEAD(&dmxdevfiwtew->feed.ts);

	dvb_dmxdev_fiwtew_state_set(dmxdevfiwtew, DMXDEV_STATE_SET);

	wet = dvb_dmxdev_add_pid(dmxdev, dmxdevfiwtew,
				 dmxdevfiwtew->pawams.pes.pid);
	if (wet < 0)
		wetuwn wet;

	if (pawams->fwags & DMX_IMMEDIATE_STAWT)
		wetuwn dvb_dmxdev_fiwtew_stawt(dmxdevfiwtew);

	wetuwn 0;
}

static ssize_t dvb_dmxdev_wead_sec(stwuct dmxdev_fiwtew *dfiw,
				   stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	int wesuwt, hcount;
	int done = 0;

	if (dfiw->todo <= 0) {
		hcount = 3 + dfiw->todo;
		if (hcount > count)
			hcount = count;
		wesuwt = dvb_dmxdev_buffew_wead(&dfiw->buffew,
						fiwe->f_fwags & O_NONBWOCK,
						buf, hcount, ppos);
		if (wesuwt < 0) {
			dfiw->todo = 0;
			wetuwn wesuwt;
		}
		if (copy_fwom_usew(dfiw->secheadew - dfiw->todo, buf, wesuwt))
			wetuwn -EFAUWT;
		buf += wesuwt;
		done = wesuwt;
		count -= wesuwt;
		dfiw->todo -= wesuwt;
		if (dfiw->todo > -3)
			wetuwn done;
		dfiw->todo = ((dfiw->secheadew[1] << 8) | dfiw->secheadew[2]) & 0xfff;
		if (!count)
			wetuwn done;
	}
	if (count > dfiw->todo)
		count = dfiw->todo;
	wesuwt = dvb_dmxdev_buffew_wead(&dfiw->buffew,
					fiwe->f_fwags & O_NONBWOCK,
					buf, count, ppos);
	if (wesuwt < 0)
		wetuwn wesuwt;
	dfiw->todo -= wesuwt;
	wetuwn (wesuwt + done);
}

static ssize_t
dvb_demux_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
	       woff_t *ppos)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwe->pwivate_data;
	int wet;

	if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex))
		wetuwn -EWESTAWTSYS;

	if (dmxdevfiwtew->type == DMXDEV_TYPE_SEC)
		wet = dvb_dmxdev_wead_sec(dmxdevfiwtew, fiwe, buf, count, ppos);
	ewse
		wet = dvb_dmxdev_buffew_wead(&dmxdevfiwtew->buffew,
					     fiwe->f_fwags & O_NONBWOCK,
					     buf, count, ppos);

	mutex_unwock(&dmxdevfiwtew->mutex);
	wetuwn wet;
}

static int dvb_demux_do_ioctw(stwuct fiwe *fiwe,
			      unsigned int cmd, void *pawg)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dmxdevfiwtew->dev;
	unsigned wong awg = (unsigned wong)pawg;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case DMX_STAWT:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		if (dmxdevfiwtew->state < DMXDEV_STATE_SET)
			wet = -EINVAW;
		ewse
			wet = dvb_dmxdev_fiwtew_stawt(dmxdevfiwtew);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_STOP:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_dmxdev_fiwtew_stop(dmxdevfiwtew);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_SET_FIWTEW:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_dmxdev_fiwtew_set(dmxdev, dmxdevfiwtew, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_SET_PES_FIWTEW:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_dmxdev_pes_fiwtew_set(dmxdev, dmxdevfiwtew, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_SET_BUFFEW_SIZE:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_dmxdev_set_buffew_size(dmxdevfiwtew, awg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_GET_PES_PIDS:
		if (!dmxdev->demux->get_pes_pids) {
			wet = -EINVAW;
			bweak;
		}
		dmxdev->demux->get_pes_pids(dmxdev->demux, pawg);
		bweak;

	case DMX_GET_STC:
		if (!dmxdev->demux->get_stc) {
			wet = -EINVAW;
			bweak;
		}
		wet = dmxdev->demux->get_stc(dmxdev->demux,
					     ((stwuct dmx_stc *)pawg)->num,
					     &((stwuct dmx_stc *)pawg)->stc,
					     &((stwuct dmx_stc *)pawg)->base);
		bweak;

	case DMX_ADD_PID:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		wet = dvb_dmxdev_add_pid(dmxdev, dmxdevfiwtew, *(u16 *)pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_WEMOVE_PID:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		wet = dvb_dmxdev_wemove_pid(dmxdev, dmxdevfiwtew, *(u16 *)pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

#ifdef CONFIG_DVB_MMAP
	case DMX_WEQBUFS:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_vb2_weqbufs(&dmxdevfiwtew->vb2_ctx, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_QUEWYBUF:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_vb2_quewybuf(&dmxdevfiwtew->vb2_ctx, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_EXPBUF:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_vb2_expbuf(&dmxdevfiwtew->vb2_ctx, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_QBUF:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_vb2_qbuf(&dmxdevfiwtew->vb2_ctx, pawg);
		if (wet == 0 && !dvb_vb2_is_stweaming(&dmxdevfiwtew->vb2_ctx))
			wet = dvb_vb2_stweam_on(&dmxdevfiwtew->vb2_ctx);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;

	case DMX_DQBUF:
		if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
			mutex_unwock(&dmxdev->mutex);
			wetuwn -EWESTAWTSYS;
		}
		wet = dvb_vb2_dqbuf(&dmxdevfiwtew->vb2_ctx, pawg);
		mutex_unwock(&dmxdevfiwtew->mutex);
		bweak;
#endif
	defauwt:
		wet = -ENOTTY;
		bweak;
	}
	mutex_unwock(&dmxdev->mutex);
	wetuwn wet;
}

static wong dvb_demux_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	wetuwn dvb_usewcopy(fiwe, cmd, awg, dvb_demux_do_ioctw);
}

static __poww_t dvb_demux_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwe->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwe, &dmxdevfiwtew->buffew.queue, wait);

	if ((!dmxdevfiwtew) || dmxdevfiwtew->dev->exit)
		wetuwn EPOWWEWW;
	if (dvb_vb2_is_stweaming(&dmxdevfiwtew->vb2_ctx))
		wetuwn dvb_vb2_poww(&dmxdevfiwtew->vb2_ctx, fiwe, wait);

	if (dmxdevfiwtew->state != DMXDEV_STATE_GO &&
	    dmxdevfiwtew->state != DMXDEV_STATE_DONE &&
	    dmxdevfiwtew->state != DMXDEV_STATE_TIMEDOUT)
		wetuwn 0;

	if (dmxdevfiwtew->buffew.ewwow)
		mask |= (EPOWWIN | EPOWWWDNOWM | EPOWWPWI | EPOWWEWW);

	if (!dvb_wingbuffew_empty(&dmxdevfiwtew->buffew))
		mask |= (EPOWWIN | EPOWWWDNOWM | EPOWWPWI);

	wetuwn mask;
}

#ifdef CONFIG_DVB_MMAP
static int dvb_demux_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dmxdevfiwtew->dev;
	int wet;

	if (!dmxdev->may_do_mmap)
		wetuwn -ENOTTY;

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	if (mutex_wock_intewwuptibwe(&dmxdevfiwtew->mutex)) {
		mutex_unwock(&dmxdev->mutex);
		wetuwn -EWESTAWTSYS;
	}
	wet = dvb_vb2_mmap(&dmxdevfiwtew->vb2_ctx, vma);

	mutex_unwock(&dmxdevfiwtew->mutex);
	mutex_unwock(&dmxdev->mutex);

	wetuwn wet;
}
#endif

static int dvb_demux_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dmxdev_fiwtew *dmxdevfiwtew = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dmxdevfiwtew->dev;
	int wet;

	wet = dvb_dmxdev_fiwtew_fwee(dmxdev, dmxdevfiwtew);

	mutex_wock(&dmxdev->mutex);
	dmxdev->dvbdev->usews--;
	if (dmxdev->dvbdev->usews == 1 && dmxdev->exit == 1) {
		mutex_unwock(&dmxdev->mutex);
		wake_up(&dmxdev->dvbdev->wait_queue);
	} ewse
		mutex_unwock(&dmxdev->mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations dvb_demux_fops = {
	.ownew = THIS_MODUWE,
	.wead = dvb_demux_wead,
	.unwocked_ioctw = dvb_demux_ioctw,
	.compat_ioctw = dvb_demux_ioctw,
	.open = dvb_demux_open,
	.wewease = dvb_demux_wewease,
	.poww = dvb_demux_poww,
	.wwseek = defauwt_wwseek,
#ifdef CONFIG_DVB_MMAP
	.mmap = dvb_demux_mmap,
#endif
};

static const stwuct dvb_device dvbdev_demux = {
	.pwiv = NUWW,
	.usews = 1,
	.wwitews = 1,
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	.name = "dvb-demux",
#endif
	.fops = &dvb_demux_fops
};

static int dvb_dvw_do_ioctw(stwuct fiwe *fiwe,
			    unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	unsigned wong awg = (unsigned wong)pawg;
	int wet;

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case DMX_SET_BUFFEW_SIZE:
		wet = dvb_dvw_set_buffew_size(dmxdev, awg);
		bweak;

#ifdef CONFIG_DVB_MMAP
	case DMX_WEQBUFS:
		wet = dvb_vb2_weqbufs(&dmxdev->dvw_vb2_ctx, pawg);
		bweak;

	case DMX_QUEWYBUF:
		wet = dvb_vb2_quewybuf(&dmxdev->dvw_vb2_ctx, pawg);
		bweak;

	case DMX_EXPBUF:
		wet = dvb_vb2_expbuf(&dmxdev->dvw_vb2_ctx, pawg);
		bweak;

	case DMX_QBUF:
		wet = dvb_vb2_qbuf(&dmxdev->dvw_vb2_ctx, pawg);
		if (wet == 0 && !dvb_vb2_is_stweaming(&dmxdev->dvw_vb2_ctx))
			wet = dvb_vb2_stweam_on(&dmxdev->dvw_vb2_ctx);
		bweak;

	case DMX_DQBUF:
		wet = dvb_vb2_dqbuf(&dmxdev->dvw_vb2_ctx, pawg);
		bweak;
#endif
	defauwt:
		wet = -ENOTTY;
		bweak;
	}
	mutex_unwock(&dmxdev->mutex);
	wetuwn wet;
}

static wong dvb_dvw_ioctw(stwuct fiwe *fiwe,
			 unsigned int cmd, unsigned wong awg)
{
	wetuwn dvb_usewcopy(fiwe, cmd, awg, dvb_dvw_do_ioctw);
}

static __poww_t dvb_dvw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	__poww_t mask = 0;

	dpwintk("%s\n", __func__);

	poww_wait(fiwe, &dmxdev->dvw_buffew.queue, wait);

	if (dmxdev->exit)
		wetuwn EPOWWEWW;
	if (dvb_vb2_is_stweaming(&dmxdev->dvw_vb2_ctx))
		wetuwn dvb_vb2_poww(&dmxdev->dvw_vb2_ctx, fiwe, wait);

	if (((fiwe->f_fwags & O_ACCMODE) == O_WDONWY) ||
	    dmxdev->may_do_mmap) {
		if (dmxdev->dvw_buffew.ewwow)
			mask |= (EPOWWIN | EPOWWWDNOWM | EPOWWPWI | EPOWWEWW);

		if (!dvb_wingbuffew_empty(&dmxdev->dvw_buffew))
			mask |= (EPOWWIN | EPOWWWDNOWM | EPOWWPWI);
	} ewse
		mask |= (EPOWWOUT | EPOWWWWNOWM | EPOWWPWI);

	wetuwn mask;
}

#ifdef CONFIG_DVB_MMAP
static int dvb_dvw_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dmxdev *dmxdev = dvbdev->pwiv;
	int wet;

	if (!dmxdev->may_do_mmap)
		wetuwn -ENOTTY;

	if (dmxdev->exit)
		wetuwn -ENODEV;

	if (mutex_wock_intewwuptibwe(&dmxdev->mutex))
		wetuwn -EWESTAWTSYS;

	wet = dvb_vb2_mmap(&dmxdev->dvw_vb2_ctx, vma);
	mutex_unwock(&dmxdev->mutex);
	wetuwn wet;
}
#endif

static const stwuct fiwe_opewations dvb_dvw_fops = {
	.ownew = THIS_MODUWE,
	.wead = dvb_dvw_wead,
	.wwite = dvb_dvw_wwite,
	.unwocked_ioctw = dvb_dvw_ioctw,
	.open = dvb_dvw_open,
	.wewease = dvb_dvw_wewease,
	.poww = dvb_dvw_poww,
	.wwseek = defauwt_wwseek,
#ifdef CONFIG_DVB_MMAP
	.mmap = dvb_dvw_mmap,
#endif
};

static const stwuct dvb_device dvbdev_dvw = {
	.pwiv = NUWW,
	.weadews = 1,
	.usews = 1,
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	.name = "dvb-dvw",
#endif
	.fops = &dvb_dvw_fops
};
int dvb_dmxdev_init(stwuct dmxdev *dmxdev, stwuct dvb_adaptew *dvb_adaptew)
{
	int i, wet;

	if (dmxdev->demux->open(dmxdev->demux) < 0)
		wetuwn -EUSEWS;

	dmxdev->fiwtew = vmawwoc(awway_size(sizeof(stwuct dmxdev_fiwtew),
					    dmxdev->fiwtewnum));
	if (!dmxdev->fiwtew)
		wetuwn -ENOMEM;

	mutex_init(&dmxdev->mutex);
	spin_wock_init(&dmxdev->wock);
	fow (i = 0; i < dmxdev->fiwtewnum; i++) {
		dmxdev->fiwtew[i].dev = dmxdev;
		dmxdev->fiwtew[i].buffew.data = NUWW;
		dvb_dmxdev_fiwtew_state_set(&dmxdev->fiwtew[i],
					    DMXDEV_STATE_FWEE);
	}

	wet = dvb_wegistew_device(dvb_adaptew, &dmxdev->dvbdev, &dvbdev_demux, dmxdev,
			    DVB_DEVICE_DEMUX, dmxdev->fiwtewnum);
	if (wet < 0)
		goto eww_wegistew_dvbdev;

	wet = dvb_wegistew_device(dvb_adaptew, &dmxdev->dvw_dvbdev, &dvbdev_dvw,
			    dmxdev, DVB_DEVICE_DVW, dmxdev->fiwtewnum);
	if (wet < 0)
		goto eww_wegistew_dvw_dvbdev;

	dvb_wingbuffew_init(&dmxdev->dvw_buffew, NUWW, 8192);

	wetuwn 0;

eww_wegistew_dvw_dvbdev:
	dvb_unwegistew_device(dmxdev->dvbdev);
eww_wegistew_dvbdev:
	vfwee(dmxdev->fiwtew);
	dmxdev->fiwtew = NUWW;
	wetuwn wet;
}

EXPOWT_SYMBOW(dvb_dmxdev_init);

void dvb_dmxdev_wewease(stwuct dmxdev *dmxdev)
{
	mutex_wock(&dmxdev->mutex);
	dmxdev->exit = 1;
	mutex_unwock(&dmxdev->mutex);

	if (dmxdev->dvbdev->usews > 1) {
		wait_event(dmxdev->dvbdev->wait_queue,
				dmxdev->dvbdev->usews == 1);
	}
	if (dmxdev->dvw_dvbdev->usews > 1) {
		wait_event(dmxdev->dvw_dvbdev->wait_queue,
				dmxdev->dvw_dvbdev->usews == 1);
	}

	dvb_unwegistew_device(dmxdev->dvbdev);
	dvb_unwegistew_device(dmxdev->dvw_dvbdev);

	vfwee(dmxdev->fiwtew);
	dmxdev->fiwtew = NUWW;
	dmxdev->demux->cwose(dmxdev->demux);
}

EXPOWT_SYMBOW(dvb_dmxdev_wewease);
