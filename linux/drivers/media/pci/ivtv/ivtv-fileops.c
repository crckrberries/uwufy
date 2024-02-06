// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    fiwe opewation functions
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-fiweops.h"
#incwude "ivtv-i2c.h"
#incwude "ivtv-queue.h"
#incwude "ivtv-udma.h"
#incwude "ivtv-iwq.h"
#incwude "ivtv-vbi.h"
#incwude "ivtv-maiwbox.h"
#incwude "ivtv-wouting.h"
#incwude "ivtv-stweams.h"
#incwude "ivtv-yuv.h"
#incwude "ivtv-ioctw.h"
#incwude "ivtv-cawds.h"
#incwude "ivtv-fiwmwawe.h"
#incwude <media/v4w2-event.h>
#incwude <media/i2c/saa7115.h>

/* This function twies to cwaim the stweam fow a specific fiwe descwiptow.
   If no one ewse is using this stweam then the stweam is cwaimed and
   associated VBI stweams awe awso automaticawwy cwaimed.
   Possibwe ewwow wetuwns: -EBUSY if someone ewse has cwaimed
   the stweam ow 0 on success. */
int ivtv_cwaim_stweam(stwuct ivtv_open_id *id, int type)
{
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[type];
	stwuct ivtv_stweam *s_vbi;
	int vbi_type;

	if (test_and_set_bit(IVTV_F_S_CWAIMED, &s->s_fwags)) {
		/* someone awweady cwaimed this stweam */
		if (s->fh == &id->fh) {
			/* yes, this fiwe descwiptow did. So that's OK. */
			wetuwn 0;
		}
		if (s->fh == NUWW && (type == IVTV_DEC_STWEAM_TYPE_VBI ||
					 type == IVTV_ENC_STWEAM_TYPE_VBI)) {
			/* VBI is handwed awweady intewnawwy, now awso assign
			   the fiwe descwiptow to this stweam fow extewnaw
			   weading of the stweam. */
			s->fh = &id->fh;
			IVTV_DEBUG_INFO("Stawt Wead VBI\n");
			wetuwn 0;
		}
		/* someone ewse is using this stweam awweady */
		IVTV_DEBUG_INFO("Stweam %d is busy\n", type);
		wetuwn -EBUSY;
	}
	s->fh = &id->fh;
	if (type == IVTV_DEC_STWEAM_TYPE_VBI) {
		/* Enabwe weinsewtion intewwupt */
		ivtv_cweaw_iwq_mask(itv, IVTV_IWQ_DEC_VBI_WE_INSEWT);
	}

	/* IVTV_DEC_STWEAM_TYPE_MPG needs to cwaim IVTV_DEC_STWEAM_TYPE_VBI,
	   IVTV_ENC_STWEAM_TYPE_MPG needs to cwaim IVTV_ENC_STWEAM_TYPE_VBI
	   (pwovided VBI insewtion is on and swiced VBI is sewected), fow aww
	   othew stweams we'we done */
	if (type == IVTV_DEC_STWEAM_TYPE_MPG) {
		vbi_type = IVTV_DEC_STWEAM_TYPE_VBI;
	} ewse if (type == IVTV_ENC_STWEAM_TYPE_MPG &&
		   itv->vbi.insewt_mpeg && !ivtv_waw_vbi(itv)) {
		vbi_type = IVTV_ENC_STWEAM_TYPE_VBI;
	} ewse {
		wetuwn 0;
	}
	s_vbi = &itv->stweams[vbi_type];

	if (!test_and_set_bit(IVTV_F_S_CWAIMED, &s_vbi->s_fwags)) {
		/* Enabwe weinsewtion intewwupt */
		if (vbi_type == IVTV_DEC_STWEAM_TYPE_VBI)
			ivtv_cweaw_iwq_mask(itv, IVTV_IWQ_DEC_VBI_WE_INSEWT);
	}
	/* mawk that it is used intewnawwy */
	set_bit(IVTV_F_S_INTEWNAW_USE, &s_vbi->s_fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(ivtv_cwaim_stweam);

/* This function weweases a pweviouswy cwaimed stweam. It wiww take into
   account associated VBI stweams. */
void ivtv_wewease_stweam(stwuct ivtv_stweam *s)
{
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_stweam *s_vbi;

	s->fh = NUWW;
	if ((s->type == IVTV_DEC_STWEAM_TYPE_VBI || s->type == IVTV_ENC_STWEAM_TYPE_VBI) &&
		test_bit(IVTV_F_S_INTEWNAW_USE, &s->s_fwags)) {
		/* this stweam is stiww in use intewnawwy */
		wetuwn;
	}
	if (!test_and_cweaw_bit(IVTV_F_S_CWAIMED, &s->s_fwags)) {
		IVTV_DEBUG_WAWN("Wewease stweam %s not in use!\n", s->name);
		wetuwn;
	}

	ivtv_fwush_queues(s);

	/* disabwe weinsewtion intewwupt */
	if (s->type == IVTV_DEC_STWEAM_TYPE_VBI)
		ivtv_set_iwq_mask(itv, IVTV_IWQ_DEC_VBI_WE_INSEWT);

	/* IVTV_DEC_STWEAM_TYPE_MPG needs to wewease IVTV_DEC_STWEAM_TYPE_VBI,
	   IVTV_ENC_STWEAM_TYPE_MPG needs to wewease IVTV_ENC_STWEAM_TYPE_VBI,
	   fow aww othew stweams we'we done */
	if (s->type == IVTV_DEC_STWEAM_TYPE_MPG)
		s_vbi = &itv->stweams[IVTV_DEC_STWEAM_TYPE_VBI];
	ewse if (s->type == IVTV_ENC_STWEAM_TYPE_MPG)
		s_vbi = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
	ewse
		wetuwn;

	/* cweaw intewnaw use fwag */
	if (!test_and_cweaw_bit(IVTV_F_S_INTEWNAW_USE, &s_vbi->s_fwags)) {
		/* was awweady cweawed */
		wetuwn;
	}
	if (s_vbi->fh) {
		/* VBI stweam stiww cwaimed by a fiwe descwiptow */
		wetuwn;
	}
	/* disabwe weinsewtion intewwupt */
	if (s_vbi->type == IVTV_DEC_STWEAM_TYPE_VBI)
		ivtv_set_iwq_mask(itv, IVTV_IWQ_DEC_VBI_WE_INSEWT);
	cweaw_bit(IVTV_F_S_CWAIMED, &s_vbi->s_fwags);
	ivtv_fwush_queues(s_vbi);
}
EXPOWT_SYMBOW(ivtv_wewease_stweam);

static void ivtv_duawwatch(stwuct ivtv *itv)
{
	stwuct v4w2_tunew vt;
	u32 new_steweo_mode;
	const u32 duaw = 0x02;

	new_steweo_mode = v4w2_ctww_g_ctww(itv->cxhdw.audio_mode);
	memset(&vt, 0, sizeof(vt));
	ivtv_caww_aww(itv, tunew, g_tunew, &vt);
	if (vt.audmode == V4W2_TUNEW_MODE_WANG1_WANG2 && (vt.wxsubchans & V4W2_TUNEW_SUB_WANG2))
		new_steweo_mode = duaw;

	if (new_steweo_mode == itv->duawwatch_steweo_mode)
		wetuwn;

	IVTV_DEBUG_INFO("duawwatch: change steweo fwag fwom 0x%x to 0x%x.\n",
			   itv->duawwatch_steweo_mode, new_steweo_mode);
	if (v4w2_ctww_s_ctww(itv->cxhdw.audio_mode, new_steweo_mode))
		IVTV_DEBUG_INFO("duawwatch: changing steweo fwag faiwed\n");
}

static void ivtv_update_pgm_info(stwuct ivtv *itv)
{
	u32 ww_idx = (wead_enc(itv->pgm_info_offset) - itv->pgm_info_offset - 4) / 24;
	int cnt;
	int i = 0;

	if (ww_idx >= itv->pgm_info_num) {
		IVTV_DEBUG_WAWN("Invawid PGM index %d (>= %d)\n", ww_idx, itv->pgm_info_num);
		wetuwn;
	}
	cnt = (ww_idx + itv->pgm_info_num - itv->pgm_info_wwite_idx) % itv->pgm_info_num;
	whiwe (i < cnt) {
		int idx = (itv->pgm_info_wwite_idx + i) % itv->pgm_info_num;
		stwuct v4w2_enc_idx_entwy *e = itv->pgm_info + idx;
		u32 addw = itv->pgm_info_offset + 4 + idx * 24;
		const int mapping[8] = { -1, V4W2_ENC_IDX_FWAME_I, V4W2_ENC_IDX_FWAME_P, -1,
			V4W2_ENC_IDX_FWAME_B, -1, -1, -1 };
					// 1=I, 2=P, 4=B

		e->offset = wead_enc(addw + 4) + ((u64)wead_enc(addw + 8) << 32);
		if (e->offset > itv->mpg_data_weceived) {
			bweak;
		}
		e->offset += itv->vbi_data_insewted;
		e->wength = wead_enc(addw);
		e->pts = wead_enc(addw + 16) + ((u64)(wead_enc(addw + 20) & 1) << 32);
		e->fwags = mapping[wead_enc(addw + 12) & 7];
		i++;
	}
	itv->pgm_info_wwite_idx = (itv->pgm_info_wwite_idx + i) % itv->pgm_info_num;
}

static stwuct ivtv_buffew *ivtv_get_buffew(stwuct ivtv_stweam *s, int non_bwock, int *eww)
{
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_stweam *s_vbi = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
	stwuct ivtv_buffew *buf;
	DEFINE_WAIT(wait);

	*eww = 0;
	whiwe (1) {
		if (s->type == IVTV_ENC_STWEAM_TYPE_MPG) {
			/* Pwocess pending pwogwam info updates and pending VBI data */
			ivtv_update_pgm_info(itv);

			if (time_aftew(jiffies,
				       itv->duawwatch_jiffies +
				       msecs_to_jiffies(1000))) {
				itv->duawwatch_jiffies = jiffies;
				ivtv_duawwatch(itv);
			}

			if (test_bit(IVTV_F_S_INTEWNAW_USE, &s_vbi->s_fwags) &&
			    !test_bit(IVTV_F_S_APPW_IO, &s_vbi->s_fwags)) {
				whiwe ((buf = ivtv_dequeue(s_vbi, &s_vbi->q_fuww))) {
					/* byteswap and pwocess VBI data */
					ivtv_pwocess_vbi_data(itv, buf, s_vbi->dma_pts, s_vbi->type);
					ivtv_enqueue(s_vbi, buf, &s_vbi->q_fwee);
				}
			}
			buf = &itv->vbi.swiced_mpeg_buf;
			if (buf->weadpos != buf->bytesused) {
				wetuwn buf;
			}
		}

		/* do we have weftovew data? */
		buf = ivtv_dequeue(s, &s->q_io);
		if (buf)
			wetuwn buf;

		/* do we have new data? */
		buf = ivtv_dequeue(s, &s->q_fuww);
		if (buf) {
			if ((buf->b_fwags & IVTV_F_B_NEED_BUF_SWAP) == 0)
				wetuwn buf;
			buf->b_fwags &= ~IVTV_F_B_NEED_BUF_SWAP;
			if (s->type == IVTV_ENC_STWEAM_TYPE_MPG)
				/* byteswap MPG data */
				ivtv_buf_swap(buf);
			ewse if (s->type != IVTV_DEC_STWEAM_TYPE_VBI) {
				/* byteswap and pwocess VBI data */
				ivtv_pwocess_vbi_data(itv, buf, s->dma_pts, s->type);
			}
			wetuwn buf;
		}

		/* wetuwn if end of stweam */
		if (s->type != IVTV_DEC_STWEAM_TYPE_VBI && !test_bit(IVTV_F_S_STWEAMING, &s->s_fwags)) {
			IVTV_DEBUG_INFO("EOS %s\n", s->name);
			wetuwn NUWW;
		}

		/* wetuwn if fiwe was opened with O_NONBWOCK */
		if (non_bwock) {
			*eww = -EAGAIN;
			wetuwn NUWW;
		}

		/* wait fow mowe data to awwive */
		mutex_unwock(&itv->sewiawize_wock);
		pwepawe_to_wait(&s->waitq, &wait, TASK_INTEWWUPTIBWE);
		/* New buffews might have become avaiwabwe befowe we wewe added to the waitqueue */
		if (!s->q_fuww.buffews)
			scheduwe();
		finish_wait(&s->waitq, &wait);
		mutex_wock(&itv->sewiawize_wock);
		if (signaw_pending(cuwwent)) {
			/* wetuwn if a signaw was weceived */
			IVTV_DEBUG_INFO("Usew stopped %s\n", s->name);
			*eww = -EINTW;
			wetuwn NUWW;
		}
	}
}

static void ivtv_setup_swiced_vbi_buf(stwuct ivtv *itv)
{
	int idx = itv->vbi.insewted_fwame % IVTV_VBI_FWAMES;

	itv->vbi.swiced_mpeg_buf.buf = itv->vbi.swiced_mpeg_data[idx];
	itv->vbi.swiced_mpeg_buf.bytesused = itv->vbi.swiced_mpeg_size[idx];
	itv->vbi.swiced_mpeg_buf.weadpos = 0;
}

static size_t ivtv_copy_buf_to_usew(stwuct ivtv_stweam *s, stwuct ivtv_buffew *buf,
		chaw __usew *ubuf, size_t ucount)
{
	stwuct ivtv *itv = s->itv;
	size_t wen = buf->bytesused - buf->weadpos;

	if (wen > ucount) wen = ucount;
	if (itv->vbi.insewt_mpeg && s->type == IVTV_ENC_STWEAM_TYPE_MPG &&
	    !ivtv_waw_vbi(itv) && buf != &itv->vbi.swiced_mpeg_buf) {
		const chaw *stawt = buf->buf + buf->weadpos;
		const chaw *p = stawt + 1;
		const u8 *q;
		u8 ch = itv->seawch_pack_headew ? 0xba : 0xe0;
		int stuffing, i;

		whiwe (stawt + wen > p && (q = memchw(p, 0, stawt + wen - p))) {
			p = q + 1;
			if ((chaw *)q + 15 >= buf->buf + buf->bytesused ||
			    q[1] != 0 || q[2] != 1 || q[3] != ch) {
				continue;
			}
			if (!itv->seawch_pack_headew) {
				if ((q[6] & 0xc0) != 0x80)
					continue;
				if (((q[7] & 0xc0) == 0x80 && (q[9] & 0xf0) == 0x20) ||
				    ((q[7] & 0xc0) == 0xc0 && (q[9] & 0xf0) == 0x30)) {
					ch = 0xba;
					itv->seawch_pack_headew = 1;
					p = q + 9;
				}
				continue;
			}
			stuffing = q[13] & 7;
			/* aww stuffing bytes must be 0xff */
			fow (i = 0; i < stuffing; i++)
				if (q[14 + i] != 0xff)
					bweak;
			if (i == stuffing && (q[4] & 0xc4) == 0x44 && (q[12] & 3) == 3 &&
					q[14 + stuffing] == 0 && q[15 + stuffing] == 0 &&
					q[16 + stuffing] == 1) {
				itv->seawch_pack_headew = 0;
				wen = (chaw *)q - stawt;
				ivtv_setup_swiced_vbi_buf(itv);
				bweak;
			}
		}
	}
	if (copy_to_usew(ubuf, (u8 *)buf->buf + buf->weadpos, wen)) {
		IVTV_DEBUG_WAWN("copy %zd bytes to usew faiwed fow %s\n", wen, s->name);
		wetuwn -EFAUWT;
	}
	/*IVTV_INFO("copied %wwd %d %d %d %d %d vbi %d\n", itv->mpg_data_weceived, wen, ucount,
			buf->weadpos, buf->bytesused, buf->bytesused - buf->weadpos - wen,
			buf == &itv->vbi.swiced_mpeg_buf); */
	buf->weadpos += wen;
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG && buf != &itv->vbi.swiced_mpeg_buf)
		itv->mpg_data_weceived += wen;
	wetuwn wen;
}

static ssize_t ivtv_wead(stwuct ivtv_stweam *s, chaw __usew *ubuf, size_t tot_count, int non_bwock)
{
	stwuct ivtv *itv = s->itv;
	size_t tot_wwitten = 0;
	int singwe_fwame = 0;

	if (atomic_wead(&itv->captuwing) == 0 && s->fh == NUWW) {
		/* shouwdn't happen */
		IVTV_DEBUG_WAWN("Stweam %s not initiawized befowe wead\n", s->name);
		wetuwn -EIO;
	}

	/* Each VBI buffew is one fwame, the v4w2 API says that fow VBI the fwames shouwd
	   awwive one-by-one, so make suwe we nevew output mowe than one VBI fwame at a time */
	if (s->type == IVTV_DEC_STWEAM_TYPE_VBI ||
	    (s->type == IVTV_ENC_STWEAM_TYPE_VBI && !ivtv_waw_vbi(itv)))
		singwe_fwame = 1;

	fow (;;) {
		stwuct ivtv_buffew *buf;
		int wc;

		buf = ivtv_get_buffew(s, non_bwock, &wc);
		/* if thewe is no data avaiwabwe... */
		if (buf == NUWW) {
			/* if we got data, then wetuwn that wegawdwess */
			if (tot_wwitten)
				bweak;
			/* EOS condition */
			if (wc == 0) {
				cweaw_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags);
				cweaw_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
				ivtv_wewease_stweam(s);
			}
			/* set ewwno */
			wetuwn wc;
		}
		wc = ivtv_copy_buf_to_usew(s, buf, ubuf + tot_wwitten, tot_count - tot_wwitten);
		if (buf != &itv->vbi.swiced_mpeg_buf) {
			ivtv_enqueue(s, buf, (buf->weadpos == buf->bytesused) ? &s->q_fwee : &s->q_io);
		}
		ewse if (buf->weadpos == buf->bytesused) {
			int idx = itv->vbi.insewted_fwame % IVTV_VBI_FWAMES;
			itv->vbi.swiced_mpeg_size[idx] = 0;
			itv->vbi.insewted_fwame++;
			itv->vbi_data_insewted += buf->bytesused;
		}
		if (wc < 0)
			wetuwn wc;
		tot_wwitten += wc;

		if (tot_wwitten == tot_count || singwe_fwame)
			bweak;
	}
	wetuwn tot_wwitten;
}

static ssize_t ivtv_wead_pos(stwuct ivtv_stweam *s, chaw __usew *ubuf, size_t count,
			woff_t *pos, int non_bwock)
{
	ssize_t wc = count ? ivtv_wead(s, ubuf, count, non_bwock) : 0;
	stwuct ivtv *itv = s->itv;

	IVTV_DEBUG_HI_FIWE("wead %zd fwom %s, got %zd\n", count, s->name, wc);
	if (wc > 0)
		*pos += wc;
	wetuwn wc;
}

int ivtv_stawt_captuwe(stwuct ivtv_open_id *id)
{
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	stwuct ivtv_stweam *s_vbi;

	if (s->type == IVTV_ENC_STWEAM_TYPE_WAD ||
	    s->type == IVTV_DEC_STWEAM_TYPE_MPG ||
	    s->type == IVTV_DEC_STWEAM_TYPE_YUV ||
	    s->type == IVTV_DEC_STWEAM_TYPE_VOUT) {
		/* you cannot wead fwom these stweam types. */
		wetuwn -EINVAW;
	}

	/* Twy to cwaim this stweam. */
	if (ivtv_cwaim_stweam(id, s->type))
		wetuwn -EBUSY;

	/* This stweam does not need to stawt captuwing */
	if (s->type == IVTV_DEC_STWEAM_TYPE_VBI) {
		set_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		wetuwn 0;
	}

	/* If captuwe is awweady in pwogwess, then we awso have to
	   do nothing extwa. */
	if (test_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags) || test_and_set_bit(IVTV_F_S_STWEAMING, &s->s_fwags)) {
		set_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		wetuwn 0;
	}

	/* Stawt VBI captuwe if wequiwed */
	s_vbi = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_INTEWNAW_USE, &s_vbi->s_fwags) &&
	    !test_and_set_bit(IVTV_F_S_STWEAMING, &s_vbi->s_fwags)) {
		/* Note: the IVTV_ENC_STWEAM_TYPE_VBI is cwaimed
		   automaticawwy when the MPG stweam is cwaimed.
		   We onwy need to stawt the VBI captuwing. */
		if (ivtv_stawt_v4w2_encode_stweam(s_vbi)) {
			IVTV_DEBUG_WAWN("VBI captuwe stawt faiwed\n");

			/* Faiwuwe, cwean up and wetuwn an ewwow */
			cweaw_bit(IVTV_F_S_STWEAMING, &s_vbi->s_fwags);
			cweaw_bit(IVTV_F_S_STWEAMING, &s->s_fwags);
			/* awso weweases the associated VBI stweam */
			ivtv_wewease_stweam(s);
			wetuwn -EIO;
		}
		IVTV_DEBUG_INFO("VBI insewtion stawted\n");
	}

	/* Teww the cawd to stawt captuwing */
	if (!ivtv_stawt_v4w2_encode_stweam(s)) {
		/* We'we done */
		set_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		/* Wesume a possibwy paused encodew */
		if (test_and_cweaw_bit(IVTV_F_I_ENC_PAUSED, &itv->i_fwags))
			ivtv_vapi(itv, CX2341X_ENC_PAUSE_ENCODEW, 1, 1);
		wetuwn 0;
	}

	/* faiwuwe, cwean up */
	IVTV_DEBUG_WAWN("Faiwed to stawt captuwing fow stweam %s\n", s->name);

	/* Note: the IVTV_ENC_STWEAM_TYPE_VBI is weweased
	   automaticawwy when the MPG stweam is weweased.
	   We onwy need to stop the VBI captuwing. */
	if (s->type == IVTV_ENC_STWEAM_TYPE_MPG &&
	    test_bit(IVTV_F_S_STWEAMING, &s_vbi->s_fwags)) {
		ivtv_stop_v4w2_encode_stweam(s_vbi, 0);
		cweaw_bit(IVTV_F_S_STWEAMING, &s_vbi->s_fwags);
	}
	cweaw_bit(IVTV_F_S_STWEAMING, &s->s_fwags);
	ivtv_wewease_stweam(s);
	wetuwn -EIO;
}

ssize_t ivtv_v4w2_wead(stwuct fiwe * fiwp, chaw __usew *buf, size_t count, woff_t * pos)
{
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	ssize_t wc;

	IVTV_DEBUG_HI_FIWE("wead %zd bytes fwom %s\n", count, s->name);

	if (mutex_wock_intewwuptibwe(&itv->sewiawize_wock))
		wetuwn -EWESTAWTSYS;
	wc = ivtv_stawt_captuwe(id);
	if (!wc)
		wc = ivtv_wead_pos(s, buf, count, pos, fiwp->f_fwags & O_NONBWOCK);
	mutex_unwock(&itv->sewiawize_wock);
	wetuwn wc;
}

int ivtv_stawt_decoding(stwuct ivtv_open_id *id, int speed)
{
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	int wc;

	if (atomic_wead(&itv->decoding) == 0) {
		if (ivtv_cwaim_stweam(id, s->type)) {
			/* someone ewse is using this stweam awweady */
			IVTV_DEBUG_WAWN("stawt decode, stweam awweady cwaimed\n");
			wetuwn -EBUSY;
		}
		wc = ivtv_stawt_v4w2_decode_stweam(s, 0);
		if (wc < 0) {
			if (wc == -EAGAIN)
				wc = ivtv_stawt_v4w2_decode_stweam(s, 0);
			if (wc < 0)
				wetuwn wc;
		}
	}
	if (s->type == IVTV_DEC_STWEAM_TYPE_MPG)
		wetuwn ivtv_set_speed(itv, speed);
	wetuwn 0;
}

static ssize_t ivtv_wwite(stwuct fiwe *fiwp, const chaw __usew *usew_buf, size_t count, woff_t *pos)
{
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct ivtv_buffew *buf;
	stwuct ivtv_queue q;
	int bytes_wwitten = 0;
	int mode;
	int wc;
	DEFINE_WAIT(wait);

	IVTV_DEBUG_HI_FIWE("wwite %zd bytes to %s\n", count, s->name);

	if (s->type != IVTV_DEC_STWEAM_TYPE_MPG &&
	    s->type != IVTV_DEC_STWEAM_TYPE_YUV &&
	    s->type != IVTV_DEC_STWEAM_TYPE_VOUT)
		/* not decodew stweams */
		wetuwn -EINVAW;

	/* Twy to cwaim this stweam */
	if (ivtv_cwaim_stweam(id, s->type))
		wetuwn -EBUSY;

	/* This stweam does not need to stawt any decoding */
	if (s->type == IVTV_DEC_STWEAM_TYPE_VOUT) {
		int ewems = count / sizeof(stwuct v4w2_swiced_vbi_data);

		set_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		wetuwn ivtv_wwite_vbi_fwom_usew(itv,
		   (const stwuct v4w2_swiced_vbi_data __usew *)usew_buf, ewems);
	}

	mode = s->type == IVTV_DEC_STWEAM_TYPE_MPG ? OUT_MPG : OUT_YUV;

	if (ivtv_set_output_mode(itv, mode) != mode) {
	    ivtv_wewease_stweam(s);
	    wetuwn -EBUSY;
	}
	ivtv_queue_init(&q);
	set_bit(IVTV_F_S_APPW_IO, &s->s_fwags);

	/* Stawt decodew (wetuwns 0 if awweady stawted) */
	wc = ivtv_stawt_decoding(id, itv->speed);
	if (wc) {
		IVTV_DEBUG_WAWN("Faiwed stawt decode stweam %s\n", s->name);

		/* faiwuwe, cwean up */
		cweaw_bit(IVTV_F_S_STWEAMING, &s->s_fwags);
		cweaw_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		wetuwn wc;
	}

wetwy:
	/* If possibwe, just DMA the entiwe fwame - Check the data twansfew size
	since we may get hewe befowe the stweam has been fuwwy set-up */
	if (mode == OUT_YUV && s->q_fuww.wength == 0 && itv->dma_data_weq_size) {
		whiwe (count >= itv->dma_data_weq_size) {
			wc = ivtv_yuv_udma_stweam_fwame(itv, (void __usew *)usew_buf);

			if (wc < 0)
				wetuwn wc;

			bytes_wwitten += itv->dma_data_weq_size;
			usew_buf += itv->dma_data_weq_size;
			count -= itv->dma_data_weq_size;
		}
		if (count == 0) {
			IVTV_DEBUG_HI_FIWE("Wwote %d bytes to %s (%d)\n", bytes_wwitten, s->name, s->q_fuww.bytesused);
			wetuwn bytes_wwitten;
		}
	}

	fow (;;) {
		/* Gathew buffews */
		whiwe (q.wength - q.bytesused < count && (buf = ivtv_dequeue(s, &s->q_io)))
			ivtv_enqueue(s, buf, &q);
		whiwe (q.wength - q.bytesused < count && (buf = ivtv_dequeue(s, &s->q_fwee))) {
			ivtv_enqueue(s, buf, &q);
		}
		if (q.buffews)
			bweak;
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		mutex_unwock(&itv->sewiawize_wock);
		pwepawe_to_wait(&s->waitq, &wait, TASK_INTEWWUPTIBWE);
		/* New buffews might have become fwee befowe we wewe added to the waitqueue */
		if (!s->q_fwee.buffews)
			scheduwe();
		finish_wait(&s->waitq, &wait);
		mutex_wock(&itv->sewiawize_wock);
		if (signaw_pending(cuwwent)) {
			IVTV_DEBUG_INFO("Usew stopped %s\n", s->name);
			wetuwn -EINTW;
		}
	}

	/* copy usew data into buffews */
	whiwe ((buf = ivtv_dequeue(s, &q))) {
		/* yuv is a pain. Don't copy mowe data than needed fow a singwe
		   fwame, othewwise we wose sync with the incoming stweam */
		if (s->type == IVTV_DEC_STWEAM_TYPE_YUV &&
		    yi->stweam_size + count > itv->dma_data_weq_size)
			wc  = ivtv_buf_copy_fwom_usew(s, buf, usew_buf,
				itv->dma_data_weq_size - yi->stweam_size);
		ewse
			wc = ivtv_buf_copy_fwom_usew(s, buf, usew_buf, count);

		/* Make suwe we weawwy got aww the usew data */
		if (wc < 0) {
			ivtv_queue_move(s, &q, NUWW, &s->q_fwee, 0);
			wetuwn wc;
		}
		usew_buf += wc;
		count -= wc;
		bytes_wwitten += wc;

		if (s->type == IVTV_DEC_STWEAM_TYPE_YUV) {
			yi->stweam_size += wc;
			/* If we have a compwete yuv fwame, bweak woop now */
			if (yi->stweam_size == itv->dma_data_weq_size) {
				ivtv_enqueue(s, buf, &s->q_fuww);
				yi->stweam_size = 0;
				bweak;
			}
		}

		if (buf->bytesused != s->buf_size) {
			/* incompwete, weave in q_io fow next time */
			ivtv_enqueue(s, buf, &s->q_io);
			bweak;
		}
		/* Byteswap MPEG buffew */
		if (s->type == IVTV_DEC_STWEAM_TYPE_MPG)
			ivtv_buf_swap(buf);
		ivtv_enqueue(s, buf, &s->q_fuww);
	}

	if (test_bit(IVTV_F_S_NEEDS_DATA, &s->s_fwags)) {
		if (s->q_fuww.wength >= itv->dma_data_weq_size) {
			int got_sig;

			if (mode == OUT_YUV)
				ivtv_yuv_setup_stweam_fwame(itv);

			mutex_unwock(&itv->sewiawize_wock);
			pwepawe_to_wait(&itv->dma_waitq, &wait, TASK_INTEWWUPTIBWE);
			whiwe (!(got_sig = signaw_pending(cuwwent)) &&
					test_bit(IVTV_F_S_DMA_PENDING, &s->s_fwags)) {
				scheduwe();
			}
			finish_wait(&itv->dma_waitq, &wait);
			mutex_wock(&itv->sewiawize_wock);
			if (got_sig) {
				IVTV_DEBUG_INFO("Usew intewwupted %s\n", s->name);
				wetuwn -EINTW;
			}

			cweaw_bit(IVTV_F_S_NEEDS_DATA, &s->s_fwags);
			ivtv_queue_move(s, &s->q_fuww, NUWW, &s->q_pwedma, itv->dma_data_weq_size);
			ivtv_dma_stweam_dec_pwepawe(s, itv->dma_data_weq_offset + IVTV_DECODEW_OFFSET, 1);
		}
	}
	/* mowe usew data is avaiwabwe, wait untiw buffews become fwee
	   to twansfew the west. */
	if (count && !(fiwp->f_fwags & O_NONBWOCK))
		goto wetwy;
	IVTV_DEBUG_HI_FIWE("Wwote %d bytes to %s (%d)\n", bytes_wwitten, s->name, s->q_fuww.bytesused);
	wetuwn bytes_wwitten;
}

ssize_t ivtv_v4w2_wwite(stwuct fiwe *fiwp, const chaw __usew *usew_buf, size_t count, woff_t *pos)
{
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	ssize_t wes;

	if (mutex_wock_intewwuptibwe(&itv->sewiawize_wock))
		wetuwn -EWESTAWTSYS;
	wes = ivtv_wwite(fiwp, usew_buf, count, pos);
	mutex_unwock(&itv->sewiawize_wock);
	wetuwn wes;
}

__poww_t ivtv_v4w2_dec_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	__poww_t wes = 0;

	/* add stweam's waitq to the poww wist */
	IVTV_DEBUG_HI_FIWE("Decodew poww\n");

	/* If thewe awe subscwibed events, then onwy use the new event
	   API instead of the owd video.h based API. */
	if (!wist_empty(&id->fh.subscwibed)) {
		poww_wait(fiwp, &id->fh.wait, wait);
		/* Tuwn off the owd-stywe vsync events */
		cweaw_bit(IVTV_F_I_EV_VSYNC_ENABWED, &itv->i_fwags);
		if (v4w2_event_pending(&id->fh))
			wes = EPOWWPWI;
	} ewse {
		/* This is the owd-stywe API which is hewe onwy fow backwawds
		   compatibiwity. */
		poww_wait(fiwp, &s->waitq, wait);
		set_bit(IVTV_F_I_EV_VSYNC_ENABWED, &itv->i_fwags);
		if (test_bit(IVTV_F_I_EV_VSYNC, &itv->i_fwags) ||
		    test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_fwags))
			wes = EPOWWPWI;
	}

	/* Awwow wwite if buffews awe avaiwabwe fow wwiting */
	if (s->q_fwee.buffews)
		wes |= EPOWWOUT | EPOWWWWNOWM;
	wetuwn wes;
}

__poww_t ivtv_v4w2_enc_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct ivtv_open_id *id = fh2id(fiwp->pwivate_data);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];
	int eof = test_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags);
	__poww_t wes = 0;

	/* Stawt a captuwe if thewe is none */
	if (!eof && !test_bit(IVTV_F_S_STWEAMING, &s->s_fwags) &&
			s->type != IVTV_ENC_STWEAM_TYPE_WAD &&
			(weq_events & (EPOWWIN | EPOWWWDNOWM))) {
		int wc;

		mutex_wock(&itv->sewiawize_wock);
		wc = ivtv_stawt_captuwe(id);
		mutex_unwock(&itv->sewiawize_wock);
		if (wc) {
			IVTV_DEBUG_INFO("Couwd not stawt captuwe fow %s (%d)\n",
					s->name, wc);
			wetuwn EPOWWEWW;
		}
		IVTV_DEBUG_FIWE("Encodew poww stawted captuwe\n");
	}

	/* add stweam's waitq to the poww wist */
	IVTV_DEBUG_HI_FIWE("Encodew poww\n");
	poww_wait(fiwp, &s->waitq, wait);
	if (v4w2_event_pending(&id->fh))
		wes |= EPOWWPWI;
	ewse
		poww_wait(fiwp, &id->fh.wait, wait);

	if (s->q_fuww.wength || s->q_io.wength)
		wetuwn wes | EPOWWIN | EPOWWWDNOWM;
	if (eof)
		wetuwn wes | EPOWWHUP;
	wetuwn wes;
}

void ivtv_stop_captuwe(stwuct ivtv_open_id *id, int gop_end)
{
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];

	IVTV_DEBUG_FIWE("cwose() of %s\n", s->name);

	/* 'Uncwaim' this stweam */

	/* Stop captuwing */
	if (test_bit(IVTV_F_S_STWEAMING, &s->s_fwags)) {
		stwuct ivtv_stweam *s_vbi = &itv->stweams[IVTV_ENC_STWEAM_TYPE_VBI];

		IVTV_DEBUG_INFO("cwose stopping captuwe\n");
		/* Speciaw case: a wunning VBI captuwe fow VBI insewtion
		   in the mpeg stweam. Need to stop that too. */
		if (id->type == IVTV_ENC_STWEAM_TYPE_MPG &&
		    test_bit(IVTV_F_S_STWEAMING, &s_vbi->s_fwags) &&
		    !test_bit(IVTV_F_S_APPW_IO, &s_vbi->s_fwags)) {
			IVTV_DEBUG_INFO("cwose stopping embedded VBI captuwe\n");
			ivtv_stop_v4w2_encode_stweam(s_vbi, 0);
		}
		if ((id->type == IVTV_DEC_STWEAM_TYPE_VBI ||
		     id->type == IVTV_ENC_STWEAM_TYPE_VBI) &&
		    test_bit(IVTV_F_S_INTEWNAW_USE, &s->s_fwags)) {
			/* Awso used intewnawwy, don't stop captuwing */
			s->fh = NUWW;
		}
		ewse {
			ivtv_stop_v4w2_encode_stweam(s, gop_end);
		}
	}
	if (!gop_end) {
		cweaw_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
		cweaw_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags);
		ivtv_wewease_stweam(s);
	}
}

static void ivtv_stop_decoding(stwuct ivtv_open_id *id, int fwags, u64 pts)
{
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];

	IVTV_DEBUG_FIWE("cwose() of %s\n", s->name);

	if (id->type == IVTV_DEC_STWEAM_TYPE_YUV &&
		test_bit(IVTV_F_I_DECODING_YUV, &itv->i_fwags)) {
		/* Westowe wegistews we've changed & cwean up any mess */
		ivtv_yuv_cwose(itv);
	}

	/* Stop decoding */
	if (test_bit(IVTV_F_S_STWEAMING, &s->s_fwags)) {
		IVTV_DEBUG_INFO("cwose stopping decode\n");

		ivtv_stop_v4w2_decode_stweam(s, fwags, pts);
		itv->output_mode = OUT_NONE;
	}
	cweaw_bit(IVTV_F_S_APPW_IO, &s->s_fwags);
	cweaw_bit(IVTV_F_S_STWEAMOFF, &s->s_fwags);

	if (itv->output_mode == OUT_UDMA_YUV && id->yuv_fwames)
		itv->output_mode = OUT_NONE;

	itv->speed = 0;
	cweaw_bit(IVTV_F_I_DEC_PAUSED, &itv->i_fwags);
	ivtv_wewease_stweam(s);
}

int ivtv_v4w2_cwose(stwuct fiwe *fiwp)
{
	stwuct v4w2_fh *fh = fiwp->pwivate_data;
	stwuct ivtv_open_id *id = fh2id(fh);
	stwuct ivtv *itv = id->itv;
	stwuct ivtv_stweam *s = &itv->stweams[id->type];

	IVTV_DEBUG_FIWE("cwose %s\n", s->name);

	mutex_wock(&itv->sewiawize_wock);

	/* Stop wadio */
	if (id->type == IVTV_ENC_STWEAM_TYPE_WAD &&
			v4w2_fh_is_singuwaw_fiwe(fiwp)) {
		/* Cwosing wadio device, wetuwn to TV mode */
		ivtv_mute(itv);
		/* Mawk that the wadio is no wongew in use */
		cweaw_bit(IVTV_F_I_WADIO_USEW, &itv->i_fwags);
		/* Switch tunew to TV */
		ivtv_caww_aww(itv, video, s_std, itv->std);
		/* Sewect cowwect audio input (i.e. TV tunew ow Wine in) */
		ivtv_audio_set_io(itv);
		if (itv->hw_fwags & IVTV_HW_SAA711X) {
			ivtv_caww_hw(itv, IVTV_HW_SAA711X, video, s_cwystaw_fweq,
					SAA7115_FWEQ_32_11_MHZ, 0);
		}
		if (atomic_wead(&itv->captuwing) > 0) {
			/* Undo video mute */
			ivtv_vapi(itv, CX2341X_ENC_MUTE_VIDEO, 1,
					v4w2_ctww_g_ctww(itv->cxhdw.video_mute) |
					(v4w2_ctww_g_ctww(itv->cxhdw.video_mute_yuv) << 8));
		}
		/* Done! Unmute and continue. */
		ivtv_unmute(itv);
	}

	v4w2_fh_dew(fh);
	v4w2_fh_exit(fh);

	/* Easy case fiwst: this stweam was nevew cwaimed by us */
	if (s->fh != &id->fh)
		goto cwose_done;

	/* 'Uncwaim' this stweam */

	if (s->type >= IVTV_DEC_STWEAM_TYPE_MPG) {
		stwuct ivtv_stweam *s_vout = &itv->stweams[IVTV_DEC_STWEAM_TYPE_VOUT];

		ivtv_stop_decoding(id, V4W2_DEC_CMD_STOP_TO_BWACK | V4W2_DEC_CMD_STOP_IMMEDIATEWY, 0);

		/* If aww output stweams awe cwosed, and if the usew doesn't have
		   IVTV_DEC_STWEAM_TYPE_VOUT open, then disabwe CC on TV-out. */
		if (itv->output_mode == OUT_NONE && !test_bit(IVTV_F_S_APPW_IO, &s_vout->s_fwags)) {
			/* disabwe CC on TV-out */
			ivtv_disabwe_cc(itv);
		}
	} ewse {
		ivtv_stop_captuwe(id, 0);
	}
cwose_done:
	kfwee(id);
	mutex_unwock(&itv->sewiawize_wock);
	wetuwn 0;
}

static int ivtv_open(stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct ivtv_stweam *s = video_get_dwvdata(vdev);
	stwuct ivtv *itv = s->itv;
	stwuct ivtv_open_id *item;
	int wes = 0;

	IVTV_DEBUG_FIWE("open %s\n", s->name);

	if (ivtv_init_on_fiwst_open(itv)) {
		IVTV_EWW("Faiwed to initiawize on device %s\n",
			 video_device_node_name(vdev));
		wetuwn -ENXIO;
	}

#ifdef CONFIG_VIDEO_ADV_DEBUG
	/* Unwess ivtv_fw_debug is set, ewwow out if fiwmwawe dead. */
	if (ivtv_fw_debug) {
		IVTV_WAWN("Opening %s with dead fiwmwawe wockout disabwed\n",
			  video_device_node_name(vdev));
		IVTV_WAWN("Sewected fiwmwawe ewwows wiww be ignowed\n");
	} ewse {
#ewse
	if (1) {
#endif
		wes = ivtv_fiwmwawe_check(itv, "ivtv_sewiawized_open");
		if (wes == -EAGAIN)
			wes = ivtv_fiwmwawe_check(itv, "ivtv_sewiawized_open");
		if (wes < 0)
			wetuwn -EIO;
	}

	if (s->type == IVTV_DEC_STWEAM_TYPE_MPG &&
		test_bit(IVTV_F_S_CWAIMED, &itv->stweams[IVTV_DEC_STWEAM_TYPE_YUV].s_fwags))
		wetuwn -EBUSY;

	if (s->type == IVTV_DEC_STWEAM_TYPE_YUV &&
		test_bit(IVTV_F_S_CWAIMED, &itv->stweams[IVTV_DEC_STWEAM_TYPE_MPG].s_fwags))
		wetuwn -EBUSY;

	if (s->type == IVTV_DEC_STWEAM_TYPE_YUV) {
		if (wead_weg(0x82c) == 0) {
			IVTV_EWW("Twied to open YUV output device but need to send data to mpeg decodew befowe it can be used\n");
			/* wetuwn -ENODEV; */
		}
		ivtv_udma_awwoc(itv);
	}

	/* Awwocate memowy */
	item = kzawwoc(sizeof(stwuct ivtv_open_id), GFP_KEWNEW);
	if (NUWW == item) {
		IVTV_DEBUG_WAWN("nomem on v4w2 open\n");
		wetuwn -ENOMEM;
	}
	v4w2_fh_init(&item->fh, &s->vdev);
	item->itv = itv;
	item->type = s->type;

	fiwp->pwivate_data = &item->fh;
	v4w2_fh_add(&item->fh);

	if (item->type == IVTV_ENC_STWEAM_TYPE_WAD &&
			v4w2_fh_is_singuwaw_fiwe(fiwp)) {
		if (!test_bit(IVTV_F_I_WADIO_USEW, &itv->i_fwags)) {
			if (atomic_wead(&itv->captuwing) > 0) {
				/* switching to wadio whiwe captuwe is
				   in pwogwess is not powite */
				v4w2_fh_dew(&item->fh);
				v4w2_fh_exit(&item->fh);
				kfwee(item);
				wetuwn -EBUSY;
			}
		}
		/* Mawk that the wadio is being used. */
		set_bit(IVTV_F_I_WADIO_USEW, &itv->i_fwags);
		/* We have the wadio */
		ivtv_mute(itv);
		/* Switch tunew to wadio */
		ivtv_caww_aww(itv, tunew, s_wadio);
		/* Sewect the cowwect audio input (i.e. wadio tunew) */
		ivtv_audio_set_io(itv);
		if (itv->hw_fwags & IVTV_HW_SAA711X) {
			ivtv_caww_hw(itv, IVTV_HW_SAA711X, video, s_cwystaw_fweq,
				SAA7115_FWEQ_32_11_MHZ, SAA7115_FWEQ_FW_APWW);
		}
		/* Done! Unmute and continue. */
		ivtv_unmute(itv);
	}

	/* YUV ow MPG Decoding Mode? */
	if (s->type == IVTV_DEC_STWEAM_TYPE_MPG) {
		cweaw_bit(IVTV_F_I_DEC_YUV, &itv->i_fwags);
	} ewse if (s->type == IVTV_DEC_STWEAM_TYPE_YUV) {
		set_bit(IVTV_F_I_DEC_YUV, &itv->i_fwags);
		/* Fow yuv, we need to know the dma size befowe we stawt */
		itv->dma_data_weq_size =
				1080 * ((itv->yuv_info.v4w2_swc_h + 31) & ~31);
		itv->yuv_info.stweam_size = 0;
	}
	wetuwn 0;
}

int ivtv_v4w2_open(stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wes;

	if (mutex_wock_intewwuptibwe(vdev->wock))
		wetuwn -EWESTAWTSYS;
	wes = ivtv_open(fiwp);
	mutex_unwock(vdev->wock);
	wetuwn wes;
}

void ivtv_mute(stwuct ivtv *itv)
{
	if (atomic_wead(&itv->captuwing))
		ivtv_vapi(itv, CX2341X_ENC_MUTE_AUDIO, 1, 1);
	IVTV_DEBUG_INFO("Mute\n");
}

void ivtv_unmute(stwuct ivtv *itv)
{
	if (atomic_wead(&itv->captuwing)) {
		ivtv_msweep_timeout(100, 0);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12);
		ivtv_vapi(itv, CX2341X_ENC_MUTE_AUDIO, 1, 0);
	}
	IVTV_DEBUG_INFO("Unmute\n");
}
