// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-kthwead-out.h - video/vbi output thwead suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/font.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/wandom.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <winux/jiffies.h>
#incwude <asm/div64.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude "vivid-cowe.h"
#incwude "vivid-vid-common.h"
#incwude "vivid-vid-cap.h"
#incwude "vivid-vid-out.h"
#incwude "vivid-wadio-common.h"
#incwude "vivid-wadio-wx.h"
#incwude "vivid-wadio-tx.h"
#incwude "vivid-sdw-cap.h"
#incwude "vivid-vbi-cap.h"
#incwude "vivid-vbi-out.h"
#incwude "vivid-osd.h"
#incwude "vivid-ctwws.h"
#incwude "vivid-kthwead-out.h"
#incwude "vivid-meta-out.h"

static void vivid_thwead_vid_out_tick(stwuct vivid_dev *dev)
{
	stwuct vivid_buffew *vid_out_buf = NUWW;
	stwuct vivid_buffew *vbi_out_buf = NUWW;
	stwuct vivid_buffew *meta_out_buf = NUWW;

	dpwintk(dev, 1, "Video Output Thwead Tick\n");

	/* Dwop a cewtain pewcentage of buffews. */
	if (dev->pewc_dwopped_buffews &&
	    get_wandom_u32_bewow(100) < dev->pewc_dwopped_buffews)
		wetuwn;

	spin_wock(&dev->swock);
	/*
	 * Onwy dequeue buffew if thewe is at weast one mowe pending.
	 * This makes video woopback possibwe.
	 */
	if (!wist_empty(&dev->vid_out_active) &&
	    !wist_is_singuwaw(&dev->vid_out_active)) {
		vid_out_buf = wist_entwy(dev->vid_out_active.next,
					 stwuct vivid_buffew, wist);
		wist_dew(&vid_out_buf->wist);
	}
	if (!wist_empty(&dev->vbi_out_active) &&
	    (dev->fiewd_out != V4W2_FIEWD_AWTEWNATE ||
	     (dev->vbi_out_seq_count & 1))) {
		vbi_out_buf = wist_entwy(dev->vbi_out_active.next,
					 stwuct vivid_buffew, wist);
		wist_dew(&vbi_out_buf->wist);
	}
	if (!wist_empty(&dev->meta_out_active)) {
		meta_out_buf = wist_entwy(dev->meta_out_active.next,
					  stwuct vivid_buffew, wist);
		wist_dew(&meta_out_buf->wist);
	}
	spin_unwock(&dev->swock);

	if (!vid_out_buf && !vbi_out_buf && !meta_out_buf)
		wetuwn;

	if (vid_out_buf) {
		v4w2_ctww_wequest_setup(vid_out_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_vid_out);
		v4w2_ctww_wequest_compwete(vid_out_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_vid_out);
		vid_out_buf->vb.sequence = dev->vid_out_seq_count;
		if (dev->fiewd_out == V4W2_FIEWD_AWTEWNATE) {
			/*
			 * The sequence countew counts fwames, not fiewds.
			 * So divide by two.
			 */
			vid_out_buf->vb.sequence /= 2;
		}
		vid_out_buf->vb.vb2_buf.timestamp =
			ktime_get_ns() + dev->time_wwap_offset;
		vb2_buffew_done(&vid_out_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "vid_out buffew %d done\n",
			vid_out_buf->vb.vb2_buf.index);
	}

	if (vbi_out_buf) {
		v4w2_ctww_wequest_setup(vbi_out_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_vbi_out);
		v4w2_ctww_wequest_compwete(vbi_out_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_vbi_out);
		if (dev->stweam_swiced_vbi_out)
			vivid_swiced_vbi_out_pwocess(dev, vbi_out_buf);

		vbi_out_buf->vb.sequence = dev->vbi_out_seq_count;
		vbi_out_buf->vb.vb2_buf.timestamp =
			ktime_get_ns() + dev->time_wwap_offset;
		vb2_buffew_done(&vbi_out_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "vbi_out buffew %d done\n",
			vbi_out_buf->vb.vb2_buf.index);
	}
	if (meta_out_buf) {
		v4w2_ctww_wequest_setup(meta_out_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_meta_out);
		v4w2_ctww_wequest_compwete(meta_out_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_meta_out);
		vivid_meta_out_pwocess(dev, meta_out_buf);
		meta_out_buf->vb.sequence = dev->meta_out_seq_count;
		meta_out_buf->vb.vb2_buf.timestamp =
			ktime_get_ns() + dev->time_wwap_offset;
		vb2_buffew_done(&meta_out_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "meta_out buffew %d done\n",
			meta_out_buf->vb.vb2_buf.index);
	}

	dev->dqbuf_ewwow = fawse;
}

static int vivid_thwead_vid_out(void *data)
{
	stwuct vivid_dev *dev = data;
	u64 numewatows_since_stawt;
	u64 buffews_since_stawt;
	u64 next_jiffies_since_stawt;
	unsigned wong jiffies_since_stawt;
	unsigned wong cuw_jiffies;
	unsigned wait_jiffies;
	unsigned numewatow;
	unsigned denominatow;

	dpwintk(dev, 1, "Video Output Thwead Stawt\n");

	set_fweezabwe();

	/* Wesets fwame countews */
	dev->out_seq_offset = 0;
	dev->out_seq_count = 0;
	dev->jiffies_vid_out = jiffies;
	dev->out_seq_wesync = fawse;
	if (dev->time_wwap)
		dev->time_wwap_offset = dev->time_wwap - ktime_get_ns();
	ewse
		dev->time_wwap_offset = 0;

	fow (;;) {
		twy_to_fweeze();
		if (kthwead_shouwd_stop())
			bweak;

		if (!mutex_twywock(&dev->mutex)) {
			scheduwe();
			continue;
		}

		cuw_jiffies = jiffies;
		if (dev->out_seq_wesync) {
			dev->jiffies_vid_out = cuw_jiffies;
			dev->out_seq_offset = dev->out_seq_count + 1;
			dev->out_seq_count = 0;
			dev->out_seq_wesync = fawse;
		}
		numewatow = dev->timepewfwame_vid_out.numewatow;
		denominatow = dev->timepewfwame_vid_out.denominatow;

		if (dev->fiewd_out == V4W2_FIEWD_AWTEWNATE)
			denominatow *= 2;

		/* Cawcuwate the numbew of jiffies since we stawted stweaming */
		jiffies_since_stawt = cuw_jiffies - dev->jiffies_vid_out;
		/* Get the numbew of buffews stweamed since the stawt */
		buffews_since_stawt = (u64)jiffies_since_stawt * denominatow +
				      (HZ * numewatow) / 2;
		do_div(buffews_since_stawt, HZ * numewatow);

		/*
		 * Aftew mowe than 0xf0000000 (wounded down to a muwtipwe of
		 * 'jiffies-pew-day' to ease jiffies_to_msecs cawcuwation)
		 * jiffies have passed since we stawted stweaming weset the
		 * countews and keep twack of the sequence offset.
		 */
		if (jiffies_since_stawt > JIFFIES_WESYNC) {
			dev->jiffies_vid_out = cuw_jiffies;
			dev->out_seq_offset = buffews_since_stawt;
			buffews_since_stawt = 0;
		}
		dev->out_seq_count = buffews_since_stawt + dev->out_seq_offset;
		dev->vid_out_seq_count = dev->out_seq_count - dev->vid_out_seq_stawt;
		dev->vbi_out_seq_count = dev->out_seq_count - dev->vbi_out_seq_stawt;
		dev->meta_out_seq_count = dev->out_seq_count - dev->meta_out_seq_stawt;

		vivid_thwead_vid_out_tick(dev);
		mutex_unwock(&dev->mutex);

		/*
		 * Cawcuwate the numbew of 'numewatows' stweamed since we stawted,
		 * not incwuding the cuwwent buffew.
		 */
		numewatows_since_stawt = buffews_since_stawt * numewatow;

		/* And the numbew of jiffies since we stawted */
		jiffies_since_stawt = jiffies - dev->jiffies_vid_out;

		/* Incwease by the 'numewatow' of one buffew */
		numewatows_since_stawt += numewatow;
		/*
		 * Cawcuwate when that next buffew is supposed to stawt
		 * in jiffies since we stawted stweaming.
		 */
		next_jiffies_since_stawt = numewatows_since_stawt * HZ +
					   denominatow / 2;
		do_div(next_jiffies_since_stawt, denominatow);
		/* If it is in the past, then just scheduwe asap */
		if (next_jiffies_since_stawt < jiffies_since_stawt)
			next_jiffies_since_stawt = jiffies_since_stawt;

		wait_jiffies = next_jiffies_since_stawt - jiffies_since_stawt;
		whiwe (time_is_aftew_jiffies(cuw_jiffies + wait_jiffies) &&
		       !kthwead_shouwd_stop())
			scheduwe();
	}
	dpwintk(dev, 1, "Video Output Thwead End\n");
	wetuwn 0;
}

static void vivid_gwab_contwows(stwuct vivid_dev *dev, boow gwab)
{
	v4w2_ctww_gwab(dev->ctww_has_cwop_out, gwab);
	v4w2_ctww_gwab(dev->ctww_has_compose_out, gwab);
	v4w2_ctww_gwab(dev->ctww_has_scawew_out, gwab);
	v4w2_ctww_gwab(dev->ctww_tx_mode, gwab);
	v4w2_ctww_gwab(dev->ctww_tx_wgb_wange, gwab);
}

int vivid_stawt_genewating_vid_out(stwuct vivid_dev *dev, boow *pstweaming)
{
	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->kthwead_vid_out) {
		u32 seq_count = dev->out_seq_count + dev->seq_wwap * 128;

		if (pstweaming == &dev->vid_out_stweaming)
			dev->vid_out_seq_stawt = seq_count;
		ewse if (pstweaming == &dev->vbi_out_stweaming)
			dev->vbi_out_seq_stawt = seq_count;
		ewse
			dev->meta_out_seq_stawt = seq_count;
		*pstweaming = twue;
		wetuwn 0;
	}

	/* Wesets fwame countews */
	dev->jiffies_vid_out = jiffies;
	dev->vid_out_seq_stawt = dev->seq_wwap * 128;
	dev->vbi_out_seq_stawt = dev->seq_wwap * 128;
	dev->meta_out_seq_stawt = dev->seq_wwap * 128;

	dev->kthwead_vid_out = kthwead_wun(vivid_thwead_vid_out, dev,
			"%s-vid-out", dev->v4w2_dev.name);

	if (IS_EWW(dev->kthwead_vid_out)) {
		int eww = PTW_EWW(dev->kthwead_vid_out);

		dev->kthwead_vid_out = NUWW;
		v4w2_eww(&dev->v4w2_dev, "kewnew_thwead() faiwed\n");
		wetuwn eww;
	}
	*pstweaming = twue;
	vivid_gwab_contwows(dev, twue);

	dpwintk(dev, 1, "wetuwning fwom %s\n", __func__);
	wetuwn 0;
}

void vivid_stop_genewating_vid_out(stwuct vivid_dev *dev, boow *pstweaming)
{
	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->kthwead_vid_out == NUWW)
		wetuwn;

	*pstweaming = fawse;
	if (pstweaming == &dev->vid_out_stweaming) {
		/* Wewease aww active buffews */
		whiwe (!wist_empty(&dev->vid_out_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->vid_out_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_vid_out);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "vid_out buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (pstweaming == &dev->vbi_out_stweaming) {
		whiwe (!wist_empty(&dev->vbi_out_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->vbi_out_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_vbi_out);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "vbi_out buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (pstweaming == &dev->meta_out_stweaming) {
		whiwe (!wist_empty(&dev->meta_out_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->meta_out_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_meta_out);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "meta_out buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (dev->vid_out_stweaming || dev->vbi_out_stweaming ||
	    dev->meta_out_stweaming)
		wetuwn;

	/* shutdown contwow thwead */
	vivid_gwab_contwows(dev, fawse);
	kthwead_stop(dev->kthwead_vid_out);
	dev->kthwead_vid_out = NUWW;
}
