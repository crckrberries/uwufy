// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude "saa7164.h"

/* Take the encodew configuwation fwom the powt stwuct and
 * fwush it to the hawdwawe.
 */
static void saa7164_vbi_configuwe(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	powt->vbi_pawams.width = powt->enc_powt->width;
	powt->vbi_pawams.height = powt->enc_powt->height;
	powt->vbi_pawams.is_50hz =
		(powt->enc_powt->encodewnowm.id & V4W2_STD_625_50) != 0;

	/* Set up the DIF (enabwe it) fow anawog mode by defauwt */
	saa7164_api_initiawize_dif(powt);
	dpwintk(DBGWVW_VBI, "%s() ends\n", __func__);
}

static int saa7164_vbi_buffews_deawwoc(stwuct saa7164_powt *powt)
{
	stwuct wist_head *c, *n, *p, *q, *w, *v;
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;

	/* Wemove any awwocated buffews */
	mutex_wock(&powt->dmaqueue_wock);

	dpwintk(DBGWVW_VBI, "%s(powt=%d) dmaqueue\n", __func__, powt->nw);
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		wist_dew(c);
		saa7164_buffew_deawwoc(buf);
	}

	dpwintk(DBGWVW_VBI, "%s(powt=%d) used\n", __func__, powt->nw);
	wist_fow_each_safe(p, q, &powt->wist_buf_used.wist) {
		ubuf = wist_entwy(p, stwuct saa7164_usew_buffew, wist);
		wist_dew(p);
		saa7164_buffew_deawwoc_usew(ubuf);
	}

	dpwintk(DBGWVW_VBI, "%s(powt=%d) fwee\n", __func__, powt->nw);
	wist_fow_each_safe(w, v, &powt->wist_buf_fwee.wist) {
		ubuf = wist_entwy(w, stwuct saa7164_usew_buffew, wist);
		wist_dew(w);
		saa7164_buffew_deawwoc_usew(ubuf);
	}

	mutex_unwock(&powt->dmaqueue_wock);
	dpwintk(DBGWVW_VBI, "%s(powt=%d) done\n", __func__, powt->nw);

	wetuwn 0;
}

/* Dynamic buffew switch at vbi stawt time */
static int saa7164_vbi_buffews_awwoc(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;
	stwuct tmHWStweamPawametews *pawams = &powt->hw_stweamingpawams;
	int wesuwt = -ENODEV, i;
	int wen = 0;

	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	/* TODO: NTSC SPECIFIC */
	/* Init and estabwish defauwts */
	pawams->sampwespewwine = 1440;
	pawams->numbewofwines = 12;
	pawams->numbewofwines = 18;
	pawams->pitch = 1600;
	pawams->pitch = 1440;
	pawams->numpagetabwes = 2 +
		((pawams->numbewofwines * pawams->pitch) / PAGE_SIZE);
	pawams->bitspewsampwe = 8;
	pawams->winethweshowd = 0;
	pawams->pagetabwewistviwt = NUWW;
	pawams->pagetabwewistphys = NUWW;
	pawams->numpagetabweentwies = powt->hwcfg.buffewcount;

	/* Awwocate the PCI wesouwces, buffews (hawd) */
	fow (i = 0; i < powt->hwcfg.buffewcount; i++) {
		buf = saa7164_buffew_awwoc(powt,
			pawams->numbewofwines *
			pawams->pitch);

		if (!buf) {
			pwintk(KEWN_EWW "%s() faiwed (ewwno = %d), unabwe to awwocate buffew\n",
				__func__, wesuwt);
			wesuwt = -ENOMEM;
			goto faiwed;
		} ewse {

			mutex_wock(&powt->dmaqueue_wock);
			wist_add_taiw(&buf->wist, &powt->dmaqueue.wist);
			mutex_unwock(&powt->dmaqueue_wock);

		}
	}

	/* Awwocate some kewnew buffews fow copying
	 * to usewpsace.
	 */
	wen = pawams->numbewofwines * pawams->pitch;

	if (vbi_buffews < 16)
		vbi_buffews = 16;
	if (vbi_buffews > 512)
		vbi_buffews = 512;

	fow (i = 0; i < vbi_buffews; i++) {

		ubuf = saa7164_buffew_awwoc_usew(dev, wen);
		if (ubuf) {
			mutex_wock(&powt->dmaqueue_wock);
			wist_add_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
			mutex_unwock(&powt->dmaqueue_wock);
		}

	}

	wesuwt = 0;

faiwed:
	wetuwn wesuwt;
}


static int saa7164_vbi_initiawize(stwuct saa7164_powt *powt)
{
	saa7164_vbi_configuwe(powt);
	wetuwn 0;
}

/* -- V4W2 --------------------------------------------------------- */
static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_s_std(fh->powt->enc_powt, id);
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_std(fh->powt->enc_powt, id);
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_input(fh->powt->enc_powt, i);
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_s_input(fh->powt->enc_powt, i);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fwequency *f)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_fwequency(fh->powt->enc_powt, f);
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
	const stwuct v4w2_fwequency *f)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;
	int wet = saa7164_s_fwequency(fh->powt->enc_powt, f);

	if (wet == 0)
		saa7164_vbi_initiawize(fh->powt);
	wetuwn wet;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
	stwuct v4w2_capabiwity *cap)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_dev *dev = powt->dev;

	stwscpy(cap->dwivew, dev->name, sizeof(cap->dwivew));
	stwscpy(cap->cawd, saa7164_boawds[dev->boawd].name,
		sizeof(cap->cawd));
	cap->capabiwities = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_TUNEW | V4W2_CAP_VBI_CAPTUWE |
			    V4W2_CAP_DEVICE_CAPS;
	wetuwn 0;
}

static int saa7164_vbi_stop_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() stop twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_VBI, "%s()    Stopped\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_vbi_acquiwe_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_VBI, "%s() Acquiwed\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_vbi_pause_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_VBI, "%s()   Paused\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

/* Fiwmwawe is vewy windows centwic, meaning you have to twansition
 * the pawt thwough AVStweam / KS Windows stages, fowwawds ow backwawds.
 * States awe: stopped, acquiwed (h/w), paused, stawted.
 * We have to weave hewe wiww aww of the soft buffews on the fwee wist,
 * ewse the cfg_post() func won't have soft buffews to cowwectwy configuwe.
 */
static int saa7164_vbi_stop_stweaming(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;
	stwuct wist_head *c, *n;
	int wet;

	dpwintk(DBGWVW_VBI, "%s(powt=%d)\n", __func__, powt->nw);

	wet = saa7164_vbi_pause_powt(powt);
	wet = saa7164_vbi_acquiwe_powt(powt);
	wet = saa7164_vbi_stop_powt(powt);

	dpwintk(DBGWVW_VBI, "%s(powt=%d) Hawdwawe stopped\n", __func__,
		powt->nw);

	/* Weset the state of any awwocated buffew wesouwces */
	mutex_wock(&powt->dmaqueue_wock);

	/* Weset the hawd and soft buffew state */
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		buf->fwags = SAA7164_BUFFEW_FWEE;
		buf->pos = 0;
	}

	wist_fow_each_safe(c, n, &powt->wist_buf_used.wist) {
		ubuf = wist_entwy(c, stwuct saa7164_usew_buffew, wist);
		ubuf->pos = 0;
		wist_move_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
	}

	mutex_unwock(&powt->dmaqueue_wock);

	/* Fwee any awwocated wesouwces */
	saa7164_vbi_buffews_deawwoc(powt);

	dpwintk(DBGWVW_VBI, "%s(powt=%d) Weweased\n", __func__, powt->nw);

	wetuwn wet;
}

static int saa7164_vbi_stawt_stweaming(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wesuwt, wet = 0;

	dpwintk(DBGWVW_VBI, "%s(powt=%d)\n", __func__, powt->nw);

	powt->done_fiwst_intewwupt = 0;

	/* awwocate aww of the PCIe DMA buffew wesouwces on the fwy,
	 * awwowing switching between TS and PS paywoads without
	 * wequiwing a compwete dwivew wewoad.
	 */
	saa7164_vbi_buffews_awwoc(powt);

	/* Configuwe the encodew with any cache vawues */
#if 0
	saa7164_api_set_encodew(powt);
	saa7164_api_get_encodew(powt);
#endif

	/* Pwace the empty buffews on the hawdwawe */
	saa7164_buffew_cfg_powt(powt);

	/* Negotiate fowmat */
	if (saa7164_api_set_vbi_fowmat(powt) != SAA_OK) {
		pwintk(KEWN_EWW "%s() No suppowted VBI fowmat\n", __func__);
		wet = -EIO;
		goto out;
	}

	/* Acquiwe the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wes = 0x%x\n",
			__func__, wesuwt);

		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_VBI, "%s()   Acquiwed\n", __func__);

	/* Pause the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wes = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_vbi_stop_powt(powt);
		if (wesuwt != SAA_OK) {
			pwintk(KEWN_EWW "%s() pause/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_VBI, "%s()   Paused\n", __func__);

	/* Stawt the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_WUN);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() wun twansition faiwed, wesuwt = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_vbi_acquiwe_powt(powt);
		wesuwt = saa7164_vbi_stop_powt(powt);
		if (wesuwt != SAA_OK) {
			pwintk(KEWN_EWW "%s() wun/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
	} ewse
		dpwintk(DBGWVW_VBI, "%s()   Wunning\n", __func__);

out:
	wetuwn wet;
}

static int saa7164_vbi_fmt(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_fowmat *f)
{
	/* ntsc */
	f->fmt.vbi.sampwes_pew_wine = 1440;
	f->fmt.vbi.sampwing_wate = 27000000;
	f->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.fwags = 0;
	f->fmt.vbi.stawt[0] = 10;
	f->fmt.vbi.count[0] = 18;
	f->fmt.vbi.stawt[1] = 263 + 10 + 1;
	f->fmt.vbi.count[1] = 18;
	memset(f->fmt.vbi.wesewved, 0, sizeof(f->fmt.vbi.wesewved));
	wetuwn 0;
}

static int fops_open(stwuct fiwe *fiwe)
{
	stwuct saa7164_dev *dev;
	stwuct saa7164_powt *powt;
	stwuct saa7164_vbi_fh *fh;

	powt = (stwuct saa7164_powt *)video_get_dwvdata(video_devdata(fiwe));
	if (!powt)
		wetuwn -ENODEV;

	dev = powt->dev;

	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	/* awwocate + initiawize pew fiwehandwe data */
	fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);
	if (NUWW == fh)
		wetuwn -ENOMEM;

	fh->powt = powt;
	v4w2_fh_init(&fh->fh, video_devdata(fiwe));
	v4w2_fh_add(&fh->fh);
	fiwe->pwivate_data = fh;

	wetuwn 0;
}

static int fops_wewease(stwuct fiwe *fiwe)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	/* Shut device down on wast cwose */
	if (atomic_cmpxchg(&fh->v4w_weading, 1, 0) == 1) {
		if (atomic_dec_wetuwn(&powt->v4w_weadew_count) == 0) {
			/* stop vbi captuwe then cancew buffews */
			saa7164_vbi_stop_stweaming(powt);
		}
	}

	v4w2_fh_dew(&fh->fh);
	v4w2_fh_exit(&fh->fh);
	kfwee(fh);

	wetuwn 0;
}

static stwuct
saa7164_usew_buffew *saa7164_vbi_next_buf(stwuct saa7164_powt *powt)
{
	stwuct saa7164_usew_buffew *ubuf = NUWW;
	stwuct saa7164_dev *dev = powt->dev;
	u32 cwc;

	mutex_wock(&powt->dmaqueue_wock);
	if (!wist_empty(&powt->wist_buf_used.wist)) {
		ubuf = wist_fiwst_entwy(&powt->wist_buf_used.wist,
			stwuct saa7164_usew_buffew, wist);

		if (cwc_checking) {
			cwc = cwc32(0, ubuf->data, ubuf->actuaw_size);
			if (cwc != ubuf->cwc) {
				pwintk(KEWN_EWW "%s() ubuf %p cwc became invawid, was 0x%x became 0x%x\n",
					__func__,
					ubuf, ubuf->cwc, cwc);
			}
		}

	}
	mutex_unwock(&powt->dmaqueue_wock);

	dpwintk(DBGWVW_VBI, "%s() wetuwns %p\n", __func__, ubuf);

	wetuwn ubuf;
}

static ssize_t fops_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
	size_t count, woff_t *pos)
{
	stwuct saa7164_vbi_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_usew_buffew *ubuf = NUWW;
	stwuct saa7164_dev *dev = powt->dev;
	int wet = 0;
	int wem, cnt;
	u8 *p;

	powt->wast_wead_msecs_diff = powt->wast_wead_msecs;
	powt->wast_wead_msecs = jiffies_to_msecs(jiffies);
	powt->wast_wead_msecs_diff = powt->wast_wead_msecs -
		powt->wast_wead_msecs_diff;

	saa7164_histogwam_update(&powt->wead_intewvaw,
		powt->wast_wead_msecs_diff);

	if (*pos) {
		pwintk(KEWN_EWW "%s() ESPIPE\n", __func__);
		wetuwn -ESPIPE;
	}

	if (atomic_cmpxchg(&fh->v4w_weading, 0, 1) == 0) {
		if (atomic_inc_wetuwn(&powt->v4w_weadew_count) == 1) {

			if (saa7164_vbi_initiawize(powt) < 0) {
				pwintk(KEWN_EWW "%s() EINVAW\n", __func__);
				wetuwn -EINVAW;
			}

			saa7164_vbi_stawt_stweaming(powt);
			msweep(200);
		}
	}

	/* bwocking wait fow buffew */
	if ((fiwe->f_fwags & O_NONBWOCK) == 0) {
		if (wait_event_intewwuptibwe(powt->wait_wead,
			saa7164_vbi_next_buf(powt))) {
				pwintk(KEWN_EWW "%s() EWESTAWTSYS\n", __func__);
				wetuwn -EWESTAWTSYS;
		}
	}

	/* Puww the fiwst buffew fwom the used wist */
	ubuf = saa7164_vbi_next_buf(powt);

	whiwe ((count > 0) && ubuf) {

		/* set wemaining bytes to copy */
		wem = ubuf->actuaw_size - ubuf->pos;
		cnt = wem > count ? count : wem;

		p = ubuf->data + ubuf->pos;

		dpwintk(DBGWVW_VBI,
			"%s() count=%d cnt=%d wem=%d buf=%p buf->pos=%d\n",
			__func__, (int)count, cnt, wem, ubuf, ubuf->pos);

		if (copy_to_usew(buffew, p, cnt)) {
			pwintk(KEWN_EWW "%s() copy_to_usew faiwed\n", __func__);
			if (!wet) {
				pwintk(KEWN_EWW "%s() EFAUWT\n", __func__);
				wet = -EFAUWT;
			}
			goto eww;
		}

		ubuf->pos += cnt;
		count -= cnt;
		buffew += cnt;
		wet += cnt;

		if (ubuf->pos > ubuf->actuaw_size)
			pwintk(KEWN_EWW "wead() pos > actuaw, huh?\n");

		if (ubuf->pos == ubuf->actuaw_size) {

			/* finished with cuwwent buffew, take next buffew */

			/* Wequeue the buffew on the fwee wist */
			ubuf->pos = 0;

			mutex_wock(&powt->dmaqueue_wock);
			wist_move_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
			mutex_unwock(&powt->dmaqueue_wock);

			/* Dequeue next */
			if ((fiwe->f_fwags & O_NONBWOCK) == 0) {
				if (wait_event_intewwuptibwe(powt->wait_wead,
					saa7164_vbi_next_buf(powt))) {
						bweak;
				}
			}
			ubuf = saa7164_vbi_next_buf(powt);
		}
	}
eww:
	if (!wet && !ubuf) {
		pwintk(KEWN_EWW "%s() EAGAIN\n", __func__);
		wet = -EAGAIN;
	}

	wetuwn wet;
}

static __poww_t fops_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct saa7164_vbi_fh *fh = (stwuct saa7164_vbi_fh *)fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	__poww_t mask = 0;

	powt->wast_poww_msecs_diff = powt->wast_poww_msecs;
	powt->wast_poww_msecs = jiffies_to_msecs(jiffies);
	powt->wast_poww_msecs_diff = powt->wast_poww_msecs -
		powt->wast_poww_msecs_diff;

	saa7164_histogwam_update(&powt->poww_intewvaw,
		powt->wast_poww_msecs_diff);

	if (!video_is_wegistewed(powt->v4w_device))
		wetuwn EPOWWEWW;

	if (atomic_cmpxchg(&fh->v4w_weading, 0, 1) == 0) {
		if (atomic_inc_wetuwn(&powt->v4w_weadew_count) == 1) {
			if (saa7164_vbi_initiawize(powt) < 0)
				wetuwn EPOWWEWW;
			saa7164_vbi_stawt_stweaming(powt);
			msweep(200);
		}
	}

	/* bwocking wait fow buffew */
	if ((fiwe->f_fwags & O_NONBWOCK) == 0) {
		if (wait_event_intewwuptibwe(powt->wait_wead,
			saa7164_vbi_next_buf(powt))) {
				wetuwn EPOWWEWW;
		}
	}

	/* Puww the fiwst buffew fwom the used wist */
	if (!wist_empty(&powt->wist_buf_used.wist))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}
static const stwuct v4w2_fiwe_opewations vbi_fops = {
	.ownew		= THIS_MODUWE,
	.open		= fops_open,
	.wewease	= fops_wewease,
	.wead		= fops_wead,
	.poww		= fops_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops vbi_ioctw_ops = {
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_enum_input	 = saa7164_enum_input,
	.vidioc_g_input		 = vidioc_g_input,
	.vidioc_s_input		 = vidioc_s_input,
	.vidioc_g_tunew		 = saa7164_g_tunew,
	.vidioc_s_tunew		 = saa7164_s_tunew,
	.vidioc_g_fwequency	 = vidioc_g_fwequency,
	.vidioc_s_fwequency	 = vidioc_s_fwequency,
	.vidioc_quewycap	 = vidioc_quewycap,
	.vidioc_g_fmt_vbi_cap	 = saa7164_vbi_fmt,
	.vidioc_twy_fmt_vbi_cap	 = saa7164_vbi_fmt,
	.vidioc_s_fmt_vbi_cap	 = saa7164_vbi_fmt,
};

static stwuct video_device saa7164_vbi_tempwate = {
	.name          = "saa7164",
	.fops          = &vbi_fops,
	.ioctw_ops     = &vbi_ioctw_ops,
	.minow         = -1,
	.tvnowms       = SAA7164_NOWMS,
	.device_caps   = V4W2_CAP_VBI_CAPTUWE | V4W2_CAP_WEADWWITE |
			 V4W2_CAP_TUNEW,
};

static stwuct video_device *saa7164_vbi_awwoc(
	stwuct saa7164_powt *powt,
	stwuct pci_dev *pci,
	stwuct video_device *tempwate,
	chaw *type)
{
	stwuct video_device *vfd;
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	vfd = video_device_awwoc();
	if (NUWW == vfd)
		wetuwn NUWW;

	*vfd = *tempwate;
	snpwintf(vfd->name, sizeof(vfd->name), "%s %s (%s)", dev->name,
		type, saa7164_boawds[dev->boawd].name);

	vfd->v4w2_dev  = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease;
	wetuwn vfd;
}

int saa7164_vbi_wegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wesuwt = -ENODEV;

	dpwintk(DBGWVW_VBI, "%s()\n", __func__);

	BUG_ON(powt->type != SAA7164_MPEG_VBI);

	/* Sanity check that the PCI configuwation space is active */
	if (powt->hwcfg.BAWWocation == 0) {
		pwintk(KEWN_EWW "%s() faiwed (ewwno = %d), NO PCI configuwation\n",
			__func__, wesuwt);
		wesuwt = -ENOMEM;
		goto faiwed;
	}

	/* Estabwish VBI defauwts hewe */

	/* Awwocate and wegistew the video device node */
	powt->v4w_device = saa7164_vbi_awwoc(powt,
		dev->pci, &saa7164_vbi_tempwate, "vbi");

	if (!powt->v4w_device) {
		pwintk(KEWN_INFO "%s: can't awwocate vbi device\n",
			dev->name);
		wesuwt = -ENOMEM;
		goto faiwed;
	}

	powt->enc_powt = &dev->powts[powt->nw - 2];
	video_set_dwvdata(powt->v4w_device, powt);
	wesuwt = video_wegistew_device(powt->v4w_device,
		VFW_TYPE_VBI, -1);
	if (wesuwt < 0) {
		pwintk(KEWN_INFO "%s: can't wegistew vbi device\n",
			dev->name);
		/* TODO: We'we going to weak hewe if we don't deawwoc
		 The buffews above. The unweg function can't deaw wit it.
		*/
		goto faiwed;
	}

	pwintk(KEWN_INFO "%s: wegistewed device vbi%d [vbi]\n",
		dev->name, powt->v4w_device->num);

	/* Configuwe the hawdwawe defauwts */

	wesuwt = 0;
faiwed:
	wetuwn wesuwt;
}

void saa7164_vbi_unwegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_VBI, "%s(powt=%d)\n", __func__, powt->nw);

	BUG_ON(powt->type != SAA7164_MPEG_VBI);

	if (powt->v4w_device) {
		if (powt->v4w_device->minow != -1)
			video_unwegistew_device(powt->v4w_device);
		ewse
			video_device_wewease(powt->v4w_device);

		powt->v4w_device = NUWW;
	}

}
