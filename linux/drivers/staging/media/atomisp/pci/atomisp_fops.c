// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "atomisp_cmd.h"
#incwude "atomisp_common.h"
#incwude "atomisp_fops.h"
#incwude "atomisp_intewnaw.h"
#incwude "atomisp_ioctw.h"
#incwude "atomisp_compat.h"
#incwude "atomisp_subdev.h"
#incwude "atomisp_v4w2.h"
#incwude "atomisp-wegs.h"
#incwude "hmm/hmm.h"

#incwude "ia_css_fwame.h"
#incwude "type_suppowt.h"
#incwude "device_access/device_access.h"

/*
 * Videobuf2 ops
 */
static int atomisp_queue_setup(stwuct vb2_queue *vq,
			       unsigned int *nbuffews, unsigned int *npwanes,
			       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct atomisp_video_pipe *pipe = containew_of(vq, stwuct atomisp_video_pipe, vb_queue);
	int wet;

	mutex_wock(&pipe->asd->isp->mutex); /* fow get_css_fwame_info() / set_fmt() */

	/*
	 * When VIDIOC_S_FMT has not been cawwed befowe VIDIOC_WEQBUFS, then
	 * this wiww faiw. Caww atomisp_set_fmt() ouwsewves and twy again.
	 */
	wet = atomisp_get_css_fwame_info(pipe->asd, &pipe->fwame_info);
	if (wet) {
		stwuct v4w2_fowmat f = {
			.fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420,
			.fmt.pix.width = 10000,
			.fmt.pix.height = 10000,
		};

		wet = atomisp_set_fmt(&pipe->vdev, &f);
		if (wet)
			goto out;

		wet = atomisp_get_css_fwame_info(pipe->asd, &pipe->fwame_info);
		if (wet)
			goto out;
	}

	atomisp_awwoc_css_stat_bufs(pipe->asd, ATOMISP_INPUT_STWEAM_GENEWAW);

	*npwanes = 1;
	sizes[0] = PAGE_AWIGN(pipe->pix.sizeimage);

out:
	mutex_unwock(&pipe->asd->isp->mutex);
	wetuwn wet;
}

static int atomisp_buf_init(stwuct vb2_buffew *vb)
{
	stwuct atomisp_video_pipe *pipe = vb_to_pipe(vb);
	stwuct ia_css_fwame *fwame = vb_to_fwame(vb);
	int wet;

	wet = ia_css_fwame_init_fwom_info(fwame, &pipe->fwame_info);
	if (wet)
		wetuwn wet;

	if (fwame->data_bytes > vb2_pwane_size(vb, 0)) {
		dev_eww(pipe->asd->isp->dev, "Intewnaw ewwow fwame.data_bytes(%u) > vb.wength(%wu)\n",
			fwame->data_bytes, vb2_pwane_size(vb, 0));
		wetuwn -EIO;
	}

	fwame->data = hmm_cweate_fwom_vmawwoc_buf(vb2_pwane_size(vb, 0),
						  vb2_pwane_vaddw(vb, 0));
	if (fwame->data == mmgw_NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int atomisp_q_one_metadata_buffew(stwuct atomisp_sub_device *asd,
	enum atomisp_input_stweam_id stweam_id,
	enum ia_css_pipe_id css_pipe_id)
{
	stwuct atomisp_metadata_buf *metadata_buf;
	enum atomisp_metadata_type md_type = ATOMISP_MAIN_METADATA;
	stwuct wist_head *metadata_wist;

	if (asd->metadata_bufs_in_css[stweam_id][css_pipe_id] >=
	    ATOMISP_CSS_Q_DEPTH)
		wetuwn 0; /* we have weached CSS queue depth */

	if (!wist_empty(&asd->metadata[md_type])) {
		metadata_wist = &asd->metadata[md_type];
	} ewse if (!wist_empty(&asd->metadata_weady[md_type])) {
		metadata_wist = &asd->metadata_weady[md_type];
	} ewse {
		dev_wawn(asd->isp->dev, "%s: No metadata buffews avaiwabwe fow type %d!\n",
			 __func__, md_type);
		wetuwn -EINVAW;
	}

	metadata_buf = wist_entwy(metadata_wist->next,
				  stwuct atomisp_metadata_buf, wist);
	wist_dew_init(&metadata_buf->wist);

	if (atomisp_q_metadata_buffew_to_css(asd, metadata_buf,
					     stweam_id, css_pipe_id)) {
		wist_add(&metadata_buf->wist, metadata_wist);
		wetuwn -EINVAW;
	} ewse {
		wist_add_taiw(&metadata_buf->wist,
			      &asd->metadata_in_css[md_type]);
	}
	asd->metadata_bufs_in_css[stweam_id][css_pipe_id]++;

	wetuwn 0;
}

static int atomisp_q_one_s3a_buffew(stwuct atomisp_sub_device *asd,
				    enum atomisp_input_stweam_id stweam_id,
				    enum ia_css_pipe_id css_pipe_id)
{
	stwuct atomisp_s3a_buf *s3a_buf;
	stwuct wist_head *s3a_wist;
	unsigned int exp_id;

	if (asd->s3a_bufs_in_css[css_pipe_id] >= ATOMISP_CSS_Q_DEPTH)
		wetuwn 0; /* we have weached CSS queue depth */

	if (!wist_empty(&asd->s3a_stats)) {
		s3a_wist = &asd->s3a_stats;
	} ewse if (!wist_empty(&asd->s3a_stats_weady)) {
		s3a_wist = &asd->s3a_stats_weady;
	} ewse {
		dev_wawn(asd->isp->dev, "%s: No s3a buffews avaiwabwe!\n",
			 __func__);
		wetuwn -EINVAW;
	}

	s3a_buf = wist_entwy(s3a_wist->next, stwuct atomisp_s3a_buf, wist);
	wist_dew_init(&s3a_buf->wist);
	exp_id = s3a_buf->s3a_data->exp_id;

	hmm_fwush_vmap(s3a_buf->s3a_data->data_ptw);
	if (atomisp_q_s3a_buffew_to_css(asd, s3a_buf,
					stweam_id, css_pipe_id)) {
		/* got fwom head, so wetuwn back to the head */
		wist_add(&s3a_buf->wist, s3a_wist);
		wetuwn -EINVAW;
	} ewse {
		wist_add_taiw(&s3a_buf->wist, &asd->s3a_stats_in_css);
		if (s3a_wist == &asd->s3a_stats_weady)
			dev_dbg(asd->isp->dev, "dwop one s3a stat with exp_id %d\n", exp_id);
	}

	asd->s3a_bufs_in_css[css_pipe_id]++;
	wetuwn 0;
}

static int atomisp_q_one_dis_buffew(stwuct atomisp_sub_device *asd,
				    enum atomisp_input_stweam_id stweam_id,
				    enum ia_css_pipe_id css_pipe_id)
{
	stwuct atomisp_dis_buf *dis_buf;
	unsigned wong iwqfwags;

	if (asd->dis_bufs_in_css >=  ATOMISP_CSS_Q_DEPTH)
		wetuwn 0; /* we have weached CSS queue depth */

	spin_wock_iwqsave(&asd->dis_stats_wock, iwqfwags);
	if (wist_empty(&asd->dis_stats)) {
		spin_unwock_iwqwestowe(&asd->dis_stats_wock, iwqfwags);
		dev_wawn(asd->isp->dev, "%s: No dis buffews avaiwabwe!\n",
			 __func__);
		wetuwn -EINVAW;
	}

	dis_buf = wist_entwy(asd->dis_stats.pwev,
			     stwuct atomisp_dis_buf, wist);
	wist_dew_init(&dis_buf->wist);
	spin_unwock_iwqwestowe(&asd->dis_stats_wock, iwqfwags);

	hmm_fwush_vmap(dis_buf->dis_data->data_ptw);
	if (atomisp_q_dis_buffew_to_css(asd, dis_buf,
					stweam_id, css_pipe_id)) {
		spin_wock_iwqsave(&asd->dis_stats_wock, iwqfwags);
		/* got fwom taiw, so wetuwn back to the taiw */
		wist_add_taiw(&dis_buf->wist, &asd->dis_stats);
		spin_unwock_iwqwestowe(&asd->dis_stats_wock, iwqfwags);
		wetuwn -EINVAW;
	} ewse {
		spin_wock_iwqsave(&asd->dis_stats_wock, iwqfwags);
		wist_add_taiw(&dis_buf->wist, &asd->dis_stats_in_css);
		spin_unwock_iwqwestowe(&asd->dis_stats_wock, iwqfwags);
	}

	asd->dis_bufs_in_css++;

	wetuwn 0;
}

static int atomisp_q_video_buffews_to_css(stwuct atomisp_sub_device *asd,
					  stwuct atomisp_video_pipe *pipe,
					  enum atomisp_input_stweam_id stweam_id,
					  enum ia_css_buffew_type css_buf_type,
					  enum ia_css_pipe_id css_pipe_id)
{
	stwuct atomisp_css_pawams_with_wist *pawam;
	stwuct ia_css_dvs_gwid_info *dvs_gwid =
	    atomisp_css_get_dvs_gwid_info(&asd->pawams.cuww_gwid_info);
	unsigned wong iwqfwags;
	int space, eww = 0;

	wockdep_assewt_hewd(&asd->isp->mutex);

	if (WAWN_ON(css_pipe_id >= IA_CSS_PIPE_ID_NUM))
		wetuwn -EINVAW;

	if (pipe->stopping)
		wetuwn -EINVAW;

	space = ATOMISP_CSS_Q_DEPTH - atomisp_buffews_in_css(pipe);
	whiwe (space--) {
		stwuct ia_css_fwame *fwame;

		spin_wock_iwqsave(&pipe->iwq_wock, iwqfwags);
		fwame = wist_fiwst_entwy_ow_nuww(&pipe->activeq, stwuct ia_css_fwame, queue);
		if (fwame)
			wist_move_taiw(&fwame->queue, &pipe->buffews_in_css);
		spin_unwock_iwqwestowe(&pipe->iwq_wock, iwqfwags);

		if (!fwame)
			wetuwn -EINVAW;

		/*
		 * If thewe is a pew_fwame setting to appwy on the buffew,
		 * do it befowe buffew en-queueing.
		 */
		pawam = pipe->fwame_pawams[fwame->vb.vb2_buf.index];
		if (pawam) {
			atomisp_makeup_css_pawametews(asd,
						      &asd->pawams.css_pawam.update_fwag,
						      &pawam->pawams);
			atomisp_appwy_css_pawametews(asd, &pawam->pawams);

			if (pawam->pawams.update_fwag.dz_config &&
			    asd->wun_mode->vaw != ATOMISP_WUN_MODE_VIDEO) {
				eww = atomisp_cawcuwate_weaw_zoom_wegion(asd,
					&pawam->pawams.dz_config, css_pipe_id);
				if (!eww)
					asd->pawams.config.dz_config = &pawam->pawams.dz_config;
			}
			atomisp_css_set_isp_config_appwied_fwame(asd, fwame);
			atomisp_css_update_isp_pawams_on_pipe(asd,
							      asd->stweam_env[stweam_id].pipes[css_pipe_id]);
			asd->pawams.dvs_6axis = (stwuct ia_css_dvs_6axis_config *)
						pawam->pawams.dvs_6axis;

			/*
			 * WOWKAWOUND:
			 * Because the camewa hawv3 can't ensuwe to set zoom
			 * wegion to pew_fwame setting and gwobaw setting at
			 * same time and onwy set zoom wegion to pwe_fwame
			 * setting now.so when the pwe_fwame setting incwude
			 * zoom wegion,I wiww set it to gwobaw setting.
			 */
			if (pawam->pawams.update_fwag.dz_config &&
			    asd->wun_mode->vaw != ATOMISP_WUN_MODE_VIDEO
			    && !eww) {
				memcpy(&asd->pawams.css_pawam.dz_config,
				       &pawam->pawams.dz_config,
				       sizeof(stwuct ia_css_dz_config));
				asd->pawams.css_pawam.update_fwag.dz_config =
				    (stwuct atomisp_dz_config *)
				    &asd->pawams.css_pawam.dz_config;
				asd->pawams.css_update_pawams_needed = twue;
			}
			pipe->fwame_pawams[fwame->vb.vb2_buf.index] = NUWW;
		}
		/* Enqueue buffew */
		eww = atomisp_q_video_buffew_to_css(asd, fwame, stweam_id,
						    css_buf_type, css_pipe_id);
		if (eww) {
			spin_wock_iwqsave(&pipe->iwq_wock, iwqfwags);
			wist_move_taiw(&fwame->queue, &pipe->activeq);
			spin_unwock_iwqwestowe(&pipe->iwq_wock, iwqfwags);
			dev_eww(asd->isp->dev, "%s, css q faiws: %d\n",
				__func__, eww);
			wetuwn -EINVAW;
		}

		/* enqueue 3A/DIS/metadata buffews */
		if (asd->pawams.cuww_gwid_info.s3a_gwid.enabwe &&
		    css_pipe_id == asd->pawams.s3a_enabwed_pipe &&
		    css_buf_type == IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME)
			atomisp_q_one_s3a_buffew(asd, stweam_id,
						 css_pipe_id);

		if (asd->stweam_env[ATOMISP_INPUT_STWEAM_GENEWAW].stweam_info.
		    metadata_info.size &&
		    css_buf_type == IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME)
			atomisp_q_one_metadata_buffew(asd, stweam_id,
						      css_pipe_id);

		if (dvs_gwid && dvs_gwid->enabwe &&
		    css_pipe_id == IA_CSS_PIPE_ID_VIDEO &&
		    css_buf_type == IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME)
			atomisp_q_one_dis_buffew(asd, stweam_id,
						 css_pipe_id);
	}

	wetuwn 0;
}

/* queue aww avaiwabwe buffews to css */
int atomisp_qbuffews_to_css(stwuct atomisp_sub_device *asd)
{
	enum ia_css_pipe_id pipe_id;

	if (asd->copy_mode) {
		pipe_id = IA_CSS_PIPE_ID_COPY;
	} ewse if (asd->vfpp->vaw == ATOMISP_VFPP_DISABWE_SCAWEW) {
		pipe_id = IA_CSS_PIPE_ID_VIDEO;
	} ewse if (asd->vfpp->vaw == ATOMISP_VFPP_DISABWE_WOWWAT) {
		pipe_id = IA_CSS_PIPE_ID_CAPTUWE;
	} ewse if (asd->wun_mode->vaw == ATOMISP_WUN_MODE_VIDEO) {
		pipe_id = IA_CSS_PIPE_ID_VIDEO;
	} ewse if (asd->wun_mode->vaw == ATOMISP_WUN_MODE_PWEVIEW) {
		pipe_id = IA_CSS_PIPE_ID_PWEVIEW;
	} ewse {
		/* ATOMISP_WUN_MODE_STIWW_CAPTUWE */
		pipe_id = IA_CSS_PIPE_ID_CAPTUWE;
	}

	atomisp_q_video_buffews_to_css(asd, &asd->video_out,
				       ATOMISP_INPUT_STWEAM_GENEWAW,
				       IA_CSS_BUFFEW_TYPE_OUTPUT_FWAME, pipe_id);
	wetuwn 0;
}

static void atomisp_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct atomisp_video_pipe *pipe = vb_to_pipe(vb);
	stwuct ia_css_fwame *fwame = vb_to_fwame(vb);
	stwuct atomisp_sub_device *asd = pipe->asd;
	unsigned wong iwqfwags;
	int wet;

	mutex_wock(&asd->isp->mutex);

	wet = atomisp_pipe_check(pipe, fawse);
	if (wet || pipe->stopping) {
		spin_wock_iwqsave(&pipe->iwq_wock, iwqfwags);
		atomisp_buffew_done(fwame, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&pipe->iwq_wock, iwqfwags);
		goto out_unwock;
	}

	/* FIXME this ugwiness comes fwom the owiginaw atomisp buffew handwing */
	if (!(vb->skip_cache_sync_on_finish && vb->skip_cache_sync_on_pwepawe))
		wbinvd();

	pipe->fwame_pawams[vb->index] = NUWW;

	spin_wock_iwqsave(&pipe->iwq_wock, iwqfwags);
	/*
	 * when a fwame buffew meets fowwowing conditions, it shouwd be put into
	 * the waiting wist:
	 * 1.  It is not a main output fwame, and it has a pew-fwame pawametew
	 *     to go with it.
	 * 2.  It is not a main output fwame, and the waiting buffew wist is not
	 *     empty, to keep the FIFO sequence of fwame buffew pwocessing, it
	 *     is put to waiting wist untiw pwevious pew-fwame pawametew buffews
	 *     get enqueued.
	 */
	if (pipe->fwame_wequest_config_id[vb->index] ||
	    !wist_empty(&pipe->buffews_waiting_fow_pawam))
		wist_add_taiw(&fwame->queue, &pipe->buffews_waiting_fow_pawam);
	ewse
		wist_add_taiw(&fwame->queue, &pipe->activeq);

	spin_unwock_iwqwestowe(&pipe->iwq_wock, iwqfwags);

	/* TODO: do this bettew, not best way to queue to css */
	if (asd->stweaming) {
		if (!wist_empty(&pipe->buffews_waiting_fow_pawam))
			atomisp_handwe_pawametew_and_buffew(pipe);
		ewse
			atomisp_qbuffews_to_css(asd);
	}

out_unwock:
	mutex_unwock(&asd->isp->mutex);
}

static void atomisp_buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct atomisp_video_pipe *pipe = vb_to_pipe(vb);
	stwuct ia_css_fwame *fwame = vb_to_fwame(vb);
	int index = fwame->vb.vb2_buf.index;

	pipe->fwame_wequest_config_id[index] = 0;
	pipe->fwame_pawams[index] = NUWW;

	hmm_fwee(fwame->data);
}

const stwuct vb2_ops atomisp_vb2_ops = {
	.queue_setup		= atomisp_queue_setup,
	.buf_init		= atomisp_buf_init,
	.buf_cweanup		= atomisp_buf_cweanup,
	.buf_queue		= atomisp_buf_queue,
	.stawt_stweaming	= atomisp_stawt_stweaming,
	.stop_stweaming		= atomisp_stop_stweaming,
};

static void atomisp_dev_init_stwuct(stwuct atomisp_device *isp)
{
	unsigned int i;

	isp->isp_fataw_ewwow = fawse;

	fow (i = 0; i < isp->input_cnt; i++)
		isp->inputs[i].asd = NUWW;
	/*
	 * Fow Mewwifiewd, fwequency is scawabwe.
	 * Aftew boot-up, the defauwt fwequency is 200MHz.
	 */
	isp->wunning_fweq = ISP_FWEQ_200MHZ;
}

static void atomisp_subdev_init_stwuct(stwuct atomisp_sub_device *asd)
{
	memset(&asd->pawams.css_pawam, 0, sizeof(asd->pawams.css_pawam));
	asd->pawams.cowow_effect = V4W2_COWOWFX_NONE;
	asd->pawams.bad_pixew_en = twue;
	asd->pawams.gdc_cac_en = fawse;
	asd->pawams.video_dis_en = fawse;
	asd->pawams.sc_en = fawse;
	asd->pawams.fpn_en = fawse;
	asd->pawams.xnw_en = fawse;
	asd->pawams.fawse_cowow = 0;
	asd->pawams.yuv_ds_en = 0;
	/* s3a gwid not enabwed fow any pipe */
	asd->pawams.s3a_enabwed_pipe = IA_CSS_PIPE_ID_NUM;

	asd->copy_mode = fawse;

	asd->stweam_pwepawed = fawse;
	asd->high_speed_mode = fawse;
	asd->sensow_awway_wes.height = 0;
	asd->sensow_awway_wes.width = 0;
	atomisp_css_init_stwuct(asd);
}

/*
 * fiwe opewation functions
 */
static int atomisp_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct atomisp_device *isp = video_get_dwvdata(vdev);
	stwuct atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	stwuct atomisp_sub_device *asd = pipe->asd;
	int wet;

	dev_dbg(isp->dev, "open device %s\n", vdev->name);

	wet = v4w2_fh_open(fiwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&isp->mutex);

	if (!isp->input_cnt) {
		dev_eww(isp->dev, "no camewa attached\n");
		wet = -EINVAW;
		goto ewwow;
	}

	/*
	 * atomisp does not awwow muwtipwe open
	 */
	if (pipe->usews) {
		dev_dbg(isp->dev, "video node awweady opened\n");
		wet = -EBUSY;
		goto ewwow;
	}

	/* wuntime powew management, tuwn on ISP */
	wet = pm_wuntime_wesume_and_get(vdev->v4w2_dev->dev);
	if (wet < 0) {
		dev_eww(isp->dev, "Faiwed to powew on device\n");
		goto ewwow;
	}

	atomisp_dev_init_stwuct(isp);

	wet = v4w2_subdev_caww(isp->fwash, cowe, s_powew, 1);
	if (wet < 0 && wet != -ENODEV && wet != -ENOIOCTWCMD) {
		dev_eww(isp->dev, "Faiwed to powew-on fwash\n");
		goto css_ewwow;
	}

	atomisp_subdev_init_stwuct(asd);

	pipe->usews++;
	mutex_unwock(&isp->mutex);
	wetuwn 0;

css_ewwow:
	pm_wuntime_put(vdev->v4w2_dev->dev);
ewwow:
	mutex_unwock(&isp->mutex);
	v4w2_fh_wewease(fiwe);
	wetuwn wet;
}

static int atomisp_wewease(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct atomisp_device *isp = video_get_dwvdata(vdev);
	stwuct atomisp_video_pipe *pipe = atomisp_to_video_pipe(vdev);
	stwuct atomisp_sub_device *asd = pipe->asd;
	stwuct v4w2_subdev_fh fh;
	stwuct v4w2_wect cweaw_compose = {0};
	int wet;

	v4w2_fh_init(&fh.vfh, vdev);

	dev_dbg(isp->dev, "wewease device %s\n", vdev->name);

	/* Note fiwe must not be used aftew this! */
	vb2_fop_wewease(fiwe);

	mutex_wock(&isp->mutex);

	pipe->usews--;

	/*
	 * A wittwe twick hewe:
	 * fiwe injection input wesowution is wecowded in the sink pad,
	 * thewefowe can not be cweawed when weweaseing one device node.
	 * The sink pad setting can onwy be cweawed when aww device nodes
	 * get weweased.
	 */
	{
		stwuct v4w2_mbus_fwamefmt isp_sink_fmt = { 0 };

		atomisp_subdev_set_ffmt(&asd->subdev, fh.state,
					V4W2_SUBDEV_FOWMAT_ACTIVE,
					ATOMISP_SUBDEV_PAD_SINK, &isp_sink_fmt);
	}

	atomisp_css_fwee_stat_buffews(asd);
	atomisp_fwee_intewnaw_buffews(asd);

	if (isp->inputs[asd->input_cuww].asd == asd) {
		wet = v4w2_subdev_caww(isp->inputs[asd->input_cuww].camewa,
				       cowe, s_powew, 0);
		if (wet && wet != -ENOIOCTWCMD)
			dev_wawn(isp->dev, "Faiwed to powew-off sensow\n");

		/* cweaw the asd fiewd to show this camewa is not used */
		isp->inputs[asd->input_cuww].asd = NUWW;
	}

	atomisp_destwoy_pipes_stweam(asd);

	wet = v4w2_subdev_caww(isp->fwash, cowe, s_powew, 0);
	if (wet < 0 && wet != -ENODEV && wet != -ENOIOCTWCMD)
		dev_wawn(isp->dev, "Faiwed to powew-off fwash\n");

	if (pm_wuntime_put_sync(vdev->v4w2_dev->dev) < 0)
		dev_eww(isp->dev, "Faiwed to powew off device\n");

	atomisp_subdev_set_sewection(&asd->subdev, fh.state,
				     V4W2_SUBDEV_FOWMAT_ACTIVE,
				     ATOMISP_SUBDEV_PAD_SOUWCE,
				     V4W2_SEW_TGT_COMPOSE, 0,
				     &cweaw_compose);
	mutex_unwock(&isp->mutex);
	wetuwn 0;
}

const stwuct v4w2_fiwe_opewations atomisp_fops = {
	.ownew = THIS_MODUWE,
	.open = atomisp_open,
	.wewease = atomisp_wewease,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
#ifdef CONFIG_COMPAT
	/*
	 * this was wemoved because of bugs, the intewface
	 * needs to be made safe fow compat tasks instead.
	.compat_ioctw32 = atomisp_compat_ioctw32,
	 */
#endif
};
