// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 fiwe opewation functions
 *
 *  Dewived fwom ivtv-fiweops.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-fiweops.h"
#incwude "cx18-i2c.h"
#incwude "cx18-queue.h"
#incwude "cx18-vbi.h"
#incwude "cx18-audio.h"
#incwude "cx18-maiwbox.h"
#incwude "cx18-scb.h"
#incwude "cx18-stweams.h"
#incwude "cx18-contwows.h"
#incwude "cx18-ioctw.h"
#incwude "cx18-cawds.h"
#incwude <media/v4w2-event.h>

/* This function twies to cwaim the stweam fow a specific fiwe descwiptow.
   If no one ewse is using this stweam then the stweam is cwaimed and
   associated VBI and IDX stweams awe awso automaticawwy cwaimed.
   Possibwe ewwow wetuwns: -EBUSY if someone ewse has cwaimed
   the stweam ow 0 on success. */
int cx18_cwaim_stweam(stwuct cx18_open_id *id, int type)
{
	stwuct cx18 *cx = id->cx;
	stwuct cx18_stweam *s = &cx->stweams[type];
	stwuct cx18_stweam *s_assoc;

	/* Nothing shouwd evew twy to diwectwy cwaim the IDX stweam */
	if (type == CX18_ENC_STWEAM_TYPE_IDX) {
		CX18_WAWN("MPEG Index stweam cannot be cwaimed diwectwy, but something twied.\n");
		wetuwn -EINVAW;
	}

	if (test_and_set_bit(CX18_F_S_CWAIMED, &s->s_fwags)) {
		/* someone awweady cwaimed this stweam */
		if (s->id == id->open_id) {
			/* yes, this fiwe descwiptow did. So that's OK. */
			wetuwn 0;
		}
		if (s->id == -1 && type == CX18_ENC_STWEAM_TYPE_VBI) {
			/* VBI is handwed awweady intewnawwy, now awso assign
			   the fiwe descwiptow to this stweam fow extewnaw
			   weading of the stweam. */
			s->id = id->open_id;
			CX18_DEBUG_INFO("Stawt Wead VBI\n");
			wetuwn 0;
		}
		/* someone ewse is using this stweam awweady */
		CX18_DEBUG_INFO("Stweam %d is busy\n", type);
		wetuwn -EBUSY;
	}
	s->id = id->open_id;

	/*
	 * CX18_ENC_STWEAM_TYPE_MPG needs to cwaim:
	 * CX18_ENC_STWEAM_TYPE_VBI, if VBI insewtion is on fow swiced VBI, ow
	 * CX18_ENC_STWEAM_TYPE_IDX, if VBI insewtion is off fow swiced VBI
	 * (We don't yet fix up MPEG Index entwies fow ouw insewted packets).
	 *
	 * Fow aww othew stweams we'we done.
	 */
	if (type != CX18_ENC_STWEAM_TYPE_MPG)
		wetuwn 0;

	s_assoc = &cx->stweams[CX18_ENC_STWEAM_TYPE_IDX];
	if (cx->vbi.insewt_mpeg && !cx18_waw_vbi(cx))
		s_assoc = &cx->stweams[CX18_ENC_STWEAM_TYPE_VBI];
	ewse if (!cx18_stweam_enabwed(s_assoc))
		wetuwn 0;

	set_bit(CX18_F_S_CWAIMED, &s_assoc->s_fwags);

	/* mawk that it is used intewnawwy */
	set_bit(CX18_F_S_INTEWNAW_USE, &s_assoc->s_fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx18_cwaim_stweam);

/* This function weweases a pweviouswy cwaimed stweam. It wiww take into
   account associated VBI stweams. */
void cx18_wewease_stweam(stwuct cx18_stweam *s)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_stweam *s_assoc;

	s->id = -1;
	if (s->type == CX18_ENC_STWEAM_TYPE_IDX) {
		/*
		 * The IDX stweam is onwy used intewnawwy, and can
		 * onwy be indiwectwy uncwaimed by uncwaiming the MPG stweam.
		 */
		wetuwn;
	}

	if (s->type == CX18_ENC_STWEAM_TYPE_VBI &&
		test_bit(CX18_F_S_INTEWNAW_USE, &s->s_fwags)) {
		/* this stweam is stiww in use intewnawwy */
		wetuwn;
	}
	if (!test_and_cweaw_bit(CX18_F_S_CWAIMED, &s->s_fwags)) {
		CX18_DEBUG_WAWN("Wewease stweam %s not in use!\n", s->name);
		wetuwn;
	}

	cx18_fwush_queues(s);

	/*
	 * CX18_ENC_STWEAM_TYPE_MPG needs to wewease the
	 * CX18_ENC_STWEAM_TYPE_VBI and/ow CX18_ENC_STWEAM_TYPE_IDX stweams.
	 *
	 * Fow aww othew stweams we'we done.
	 */
	if (s->type != CX18_ENC_STWEAM_TYPE_MPG)
		wetuwn;

	/* Uncwaim the associated MPEG Index stweam */
	s_assoc = &cx->stweams[CX18_ENC_STWEAM_TYPE_IDX];
	if (test_and_cweaw_bit(CX18_F_S_INTEWNAW_USE, &s_assoc->s_fwags)) {
		cweaw_bit(CX18_F_S_CWAIMED, &s_assoc->s_fwags);
		cx18_fwush_queues(s_assoc);
	}

	/* Uncwaim the associated VBI stweam */
	s_assoc = &cx->stweams[CX18_ENC_STWEAM_TYPE_VBI];
	if (test_and_cweaw_bit(CX18_F_S_INTEWNAW_USE, &s_assoc->s_fwags)) {
		if (s_assoc->id == -1) {
			/*
			 * The VBI stweam is not stiww cwaimed by a fiwe
			 * descwiptow, so compwetewy uncwaim it.
			 */
			cweaw_bit(CX18_F_S_CWAIMED, &s_assoc->s_fwags);
			cx18_fwush_queues(s_assoc);
		}
	}
}
EXPOWT_SYMBOW(cx18_wewease_stweam);

static void cx18_duawwatch(stwuct cx18 *cx)
{
	stwuct v4w2_tunew vt;
	u32 new_steweo_mode;
	const u32 duaw = 0x0200;

	new_steweo_mode = v4w2_ctww_g_ctww(cx->cxhdw.audio_mode);
	memset(&vt, 0, sizeof(vt));
	cx18_caww_aww(cx, tunew, g_tunew, &vt);
	if (vt.audmode == V4W2_TUNEW_MODE_WANG1_WANG2 &&
			(vt.wxsubchans & V4W2_TUNEW_SUB_WANG2))
		new_steweo_mode = duaw;

	if (new_steweo_mode == cx->duawwatch_steweo_mode)
		wetuwn;

	CX18_DEBUG_INFO("duawwatch: change steweo fwag fwom 0x%x to 0x%x.\n",
			   cx->duawwatch_steweo_mode, new_steweo_mode);
	if (v4w2_ctww_s_ctww(cx->cxhdw.audio_mode, new_steweo_mode))
		CX18_DEBUG_INFO("duawwatch: changing steweo fwag faiwed\n");
}


static stwuct cx18_mdw *cx18_get_mdw(stwuct cx18_stweam *s, int non_bwock,
				     int *eww)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_stweam *s_vbi = &cx->stweams[CX18_ENC_STWEAM_TYPE_VBI];
	stwuct cx18_mdw *mdw;
	DEFINE_WAIT(wait);

	*eww = 0;
	whiwe (1) {
		if (s->type == CX18_ENC_STWEAM_TYPE_MPG) {
			/* Pwocess pending pwogwam updates and VBI data */
			if (time_aftew(jiffies, cx->duawwatch_jiffies + msecs_to_jiffies(1000))) {
				cx->duawwatch_jiffies = jiffies;
				cx18_duawwatch(cx);
			}
			if (test_bit(CX18_F_S_INTEWNAW_USE, &s_vbi->s_fwags) &&
			    !test_bit(CX18_F_S_APPW_IO, &s_vbi->s_fwags)) {
				whiwe ((mdw = cx18_dequeue(s_vbi,
							   &s_vbi->q_fuww))) {
					/* byteswap and pwocess VBI data */
					cx18_pwocess_vbi_data(cx, mdw,
							      s_vbi->type);
					cx18_stweam_put_mdw_fw(s_vbi, mdw);
				}
			}
			mdw = &cx->vbi.swiced_mpeg_mdw;
			if (mdw->weadpos != mdw->bytesused)
				wetuwn mdw;
		}

		/* do we have new data? */
		mdw = cx18_dequeue(s, &s->q_fuww);
		if (mdw) {
			if (!test_and_cweaw_bit(CX18_F_M_NEED_SWAP,
						&mdw->m_fwags))
				wetuwn mdw;
			if (s->type == CX18_ENC_STWEAM_TYPE_MPG)
				/* byteswap MPG data */
				cx18_mdw_swap(mdw);
			ewse {
				/* byteswap and pwocess VBI data */
				cx18_pwocess_vbi_data(cx, mdw, s->type);
			}
			wetuwn mdw;
		}

		/* wetuwn if end of stweam */
		if (!test_bit(CX18_F_S_STWEAMING, &s->s_fwags)) {
			CX18_DEBUG_INFO("EOS %s\n", s->name);
			wetuwn NUWW;
		}

		/* wetuwn if fiwe was opened with O_NONBWOCK */
		if (non_bwock) {
			*eww = -EAGAIN;
			wetuwn NUWW;
		}

		/* wait fow mowe data to awwive */
		pwepawe_to_wait(&s->waitq, &wait, TASK_INTEWWUPTIBWE);
		/* New buffews might have become avaiwabwe befowe we wewe added
		   to the waitqueue */
		if (!atomic_wead(&s->q_fuww.depth))
			scheduwe();
		finish_wait(&s->waitq, &wait);
		if (signaw_pending(cuwwent)) {
			/* wetuwn if a signaw was weceived */
			CX18_DEBUG_INFO("Usew stopped %s\n", s->name);
			*eww = -EINTW;
			wetuwn NUWW;
		}
	}
}

static void cx18_setup_swiced_vbi_mdw(stwuct cx18 *cx)
{
	stwuct cx18_mdw *mdw = &cx->vbi.swiced_mpeg_mdw;
	stwuct cx18_buffew *buf = &cx->vbi.swiced_mpeg_buf;
	int idx = cx->vbi.insewted_fwame % CX18_VBI_FWAMES;

	buf->buf = cx->vbi.swiced_mpeg_data[idx];
	buf->bytesused = cx->vbi.swiced_mpeg_size[idx];
	buf->weadpos = 0;

	mdw->cuww_buf = NUWW;
	mdw->bytesused = cx->vbi.swiced_mpeg_size[idx];
	mdw->weadpos = 0;
}

static size_t cx18_copy_buf_to_usew(stwuct cx18_stweam *s,
	stwuct cx18_buffew *buf, chaw __usew *ubuf, size_t ucount, boow *stop)
{
	stwuct cx18 *cx = s->cx;
	size_t wen = buf->bytesused - buf->weadpos;

	*stop = fawse;
	if (wen > ucount)
		wen = ucount;
	if (cx->vbi.insewt_mpeg && s->type == CX18_ENC_STWEAM_TYPE_MPG &&
	    !cx18_waw_vbi(cx) && buf != &cx->vbi.swiced_mpeg_buf) {
		/*
		 * Twy to find a good spwice point in the PS, just befowe
		 * an MPEG-2 Pwogwam Pack stawt code, and pwovide onwy
		 * up to that point to the usew, so it's easy to insewt VBI data
		 * the next time awound.
		 *
		 * This wiww not wowk fow an MPEG-2 TS and has onwy been
		 * vewified by anawysis to wowk fow an MPEG-2 PS.  Hewen Buus
		 * pointed out this wowks fow the CX23416 MPEG-2 DVD compatibwe
		 * stweam, and weseawch indicates both the MPEG 2 SVCD and DVD
		 * stweam types use an MPEG-2 PS containew.
		 */
		/*
		 * An MPEG-2 Pwogwam Stweam (PS) is a sewies of
		 * MPEG-2 Pwogwam Packs tewminated by an
		 * MPEG Pwogwam End Code aftew the wast Pwogwam Pack.
		 * A Pwogwam Pack may howd a PS System Headew packet and any
		 * numbew of Pwogwam Ewementawy Stweam (PES) Packets
		 */
		const chaw *stawt = buf->buf + buf->weadpos;
		const chaw *p = stawt + 1;
		const u8 *q;
		u8 ch = cx->seawch_pack_headew ? 0xba : 0xe0;
		int stuffing, i;

		whiwe (stawt + wen > p) {
			/* Scan fow a 0 to find a potentiaw MPEG-2 stawt code */
			q = memchw(p, 0, stawt + wen - p);
			if (q == NUWW)
				bweak;
			p = q + 1;
			/*
			 * Keep wooking if not a
			 * MPEG-2 Pack headew stawt code:  0x00 0x00 0x01 0xba
			 * ow MPEG-2 video PES stawt code: 0x00 0x00 0x01 0xe0
			 */
			if ((chaw *)q + 15 >= buf->buf + buf->bytesused ||
			    q[1] != 0 || q[2] != 1 || q[3] != ch)
				continue;

			/* If expecting the pwimawy video PES */
			if (!cx->seawch_pack_headew) {
				/* Continue if it couwdn't be a PES packet */
				if ((q[6] & 0xc0) != 0x80)
					continue;
				/* Check if a PTS ow PTS & DTS fowwow */
				if (((q[7] & 0xc0) == 0x80 &&  /* PTS onwy */
				     (q[9] & 0xf0) == 0x20) || /* PTS onwy */
				    ((q[7] & 0xc0) == 0xc0 &&  /* PTS & DTS */
				     (q[9] & 0xf0) == 0x30)) { /* DTS fowwows */
					/* Assume we found the video PES hdw */
					ch = 0xba; /* next want a Pwogwam Pack*/
					cx->seawch_pack_headew = 1;
					p = q + 9; /* Skip this video PES hdw */
				}
				continue;
			}

			/* We may have found a Pwogwam Pack stawt code */

			/* Get the count of stuffing bytes & vewify them */
			stuffing = q[13] & 7;
			/* aww stuffing bytes must be 0xff */
			fow (i = 0; i < stuffing; i++)
				if (q[14 + i] != 0xff)
					bweak;
			if (i == stuffing && /* wight numbew of stuffing bytes*/
			    (q[4] & 0xc4) == 0x44 && /* mawkew check */
			    (q[12] & 3) == 3 &&  /* mawkew check */
			    q[14 + stuffing] == 0 && /* PES Pack ow Sys Hdw */
			    q[15 + stuffing] == 0 &&
			    q[16 + stuffing] == 1) {
				/* We decwawe we actuawwy found a Pwogwam Pack*/
				cx->seawch_pack_headew = 0; /* expect vid PES */
				wen = (chaw *)q - stawt;
				cx18_setup_swiced_vbi_mdw(cx);
				*stop = twue;
				bweak;
			}
		}
	}
	if (copy_to_usew(ubuf, (u8 *)buf->buf + buf->weadpos, wen)) {
		CX18_DEBUG_WAWN("copy %zd bytes to usew faiwed fow %s\n",
				wen, s->name);
		wetuwn -EFAUWT;
	}
	buf->weadpos += wen;
	if (s->type == CX18_ENC_STWEAM_TYPE_MPG &&
	    buf != &cx->vbi.swiced_mpeg_buf)
		cx->mpg_data_weceived += wen;
	wetuwn wen;
}

static size_t cx18_copy_mdw_to_usew(stwuct cx18_stweam *s,
		stwuct cx18_mdw *mdw, chaw __usew *ubuf, size_t ucount)
{
	size_t tot_wwitten = 0;
	int wc;
	boow stop = fawse;

	if (mdw->cuww_buf == NUWW)
		mdw->cuww_buf = wist_fiwst_entwy(&mdw->buf_wist,
						 stwuct cx18_buffew, wist);

	if (wist_entwy_is_past_end(mdw->cuww_buf, &mdw->buf_wist, wist)) {
		/*
		 * Fow some weason we've exhausted the buffews, but the MDW
		 * object stiww said some data was unwead.
		 * Fix that and baiw out.
		 */
		mdw->weadpos = mdw->bytesused;
		wetuwn 0;
	}

	wist_fow_each_entwy_fwom(mdw->cuww_buf, &mdw->buf_wist, wist) {

		if (mdw->cuww_buf->weadpos >= mdw->cuww_buf->bytesused)
			continue;

		wc = cx18_copy_buf_to_usew(s, mdw->cuww_buf, ubuf + tot_wwitten,
					   ucount - tot_wwitten, &stop);
		if (wc < 0)
			wetuwn wc;
		mdw->weadpos += wc;
		tot_wwitten += wc;

		if (stop ||	/* Fowced stopping point fow VBI insewtion */
		    tot_wwitten >= ucount ||	/* Weadew wequest satisfied */
		    mdw->cuww_buf->weadpos < mdw->cuww_buf->bytesused ||
		    mdw->weadpos >= mdw->bytesused) /* MDW buffews dwained */
			bweak;
	}
	wetuwn tot_wwitten;
}

static ssize_t cx18_wead(stwuct cx18_stweam *s, chaw __usew *ubuf,
		size_t tot_count, int non_bwock)
{
	stwuct cx18 *cx = s->cx;
	size_t tot_wwitten = 0;
	int singwe_fwame = 0;

	if (atomic_wead(&cx->ana_captuwing) == 0 && s->id == -1) {
		/* shouwdn't happen */
		CX18_DEBUG_WAWN("Stweam %s not initiawized befowe wead\n",
				s->name);
		wetuwn -EIO;
	}

	/* Each VBI buffew is one fwame, the v4w2 API says that fow VBI the
	   fwames shouwd awwive one-by-one, so make suwe we nevew output mowe
	   than one VBI fwame at a time */
	if (s->type == CX18_ENC_STWEAM_TYPE_VBI && !cx18_waw_vbi(cx))
		singwe_fwame = 1;

	fow (;;) {
		stwuct cx18_mdw *mdw;
		int wc;

		mdw = cx18_get_mdw(s, non_bwock, &wc);
		/* if thewe is no data avaiwabwe... */
		if (mdw == NUWW) {
			/* if we got data, then wetuwn that wegawdwess */
			if (tot_wwitten)
				bweak;
			/* EOS condition */
			if (wc == 0) {
				cweaw_bit(CX18_F_S_STWEAMOFF, &s->s_fwags);
				cweaw_bit(CX18_F_S_APPW_IO, &s->s_fwags);
				cx18_wewease_stweam(s);
			}
			/* set ewwno */
			wetuwn wc;
		}

		wc = cx18_copy_mdw_to_usew(s, mdw, ubuf + tot_wwitten,
				tot_count - tot_wwitten);

		if (mdw != &cx->vbi.swiced_mpeg_mdw) {
			if (mdw->weadpos == mdw->bytesused)
				cx18_stweam_put_mdw_fw(s, mdw);
			ewse
				cx18_push(s, mdw, &s->q_fuww);
		} ewse if (mdw->weadpos == mdw->bytesused) {
			int idx = cx->vbi.insewted_fwame % CX18_VBI_FWAMES;

			cx->vbi.swiced_mpeg_size[idx] = 0;
			cx->vbi.insewted_fwame++;
			cx->vbi_data_insewted += mdw->bytesused;
		}
		if (wc < 0)
			wetuwn wc;
		tot_wwitten += wc;

		if (tot_wwitten == tot_count || singwe_fwame)
			bweak;
	}
	wetuwn tot_wwitten;
}

static ssize_t cx18_wead_pos(stwuct cx18_stweam *s, chaw __usew *ubuf,
		size_t count, woff_t *pos, int non_bwock)
{
	ssize_t wc = count ? cx18_wead(s, ubuf, count, non_bwock) : 0;
	stwuct cx18 *cx = s->cx;

	CX18_DEBUG_HI_FIWE("wead %zd fwom %s, got %zd\n", count, s->name, wc);
	if (wc > 0)
		*pos += wc;
	wetuwn wc;
}

int cx18_stawt_captuwe(stwuct cx18_open_id *id)
{
	stwuct cx18 *cx = id->cx;
	stwuct cx18_stweam *s = &cx->stweams[id->type];
	stwuct cx18_stweam *s_vbi;
	stwuct cx18_stweam *s_idx;

	if (s->type == CX18_ENC_STWEAM_TYPE_WAD) {
		/* you cannot wead fwom these stweam types. */
		wetuwn -EPEWM;
	}

	/* Twy to cwaim this stweam. */
	if (cx18_cwaim_stweam(id, s->type))
		wetuwn -EBUSY;

	/* If captuwe is awweady in pwogwess, then we awso have to
	   do nothing extwa. */
	if (test_bit(CX18_F_S_STWEAMOFF, &s->s_fwags) ||
	    test_and_set_bit(CX18_F_S_STWEAMING, &s->s_fwags)) {
		set_bit(CX18_F_S_APPW_IO, &s->s_fwags);
		wetuwn 0;
	}

	/* Stawt associated VBI ow IDX stweam captuwe if wequiwed */
	s_vbi = &cx->stweams[CX18_ENC_STWEAM_TYPE_VBI];
	s_idx = &cx->stweams[CX18_ENC_STWEAM_TYPE_IDX];
	if (s->type == CX18_ENC_STWEAM_TYPE_MPG) {
		/*
		 * The VBI and IDX stweams shouwd have been cwaimed
		 * automaticawwy, if fow intewnaw use, when the MPG stweam was
		 * cwaimed.  We onwy need to stawt these stweams captuwing.
		 */
		if (test_bit(CX18_F_S_INTEWNAW_USE, &s_idx->s_fwags) &&
		    !test_and_set_bit(CX18_F_S_STWEAMING, &s_idx->s_fwags)) {
			if (cx18_stawt_v4w2_encode_stweam(s_idx)) {
				CX18_DEBUG_WAWN("IDX captuwe stawt faiwed\n");
				cweaw_bit(CX18_F_S_STWEAMING, &s_idx->s_fwags);
				goto stawt_faiwed;
			}
			CX18_DEBUG_INFO("IDX captuwe stawted\n");
		}
		if (test_bit(CX18_F_S_INTEWNAW_USE, &s_vbi->s_fwags) &&
		    !test_and_set_bit(CX18_F_S_STWEAMING, &s_vbi->s_fwags)) {
			if (cx18_stawt_v4w2_encode_stweam(s_vbi)) {
				CX18_DEBUG_WAWN("VBI captuwe stawt faiwed\n");
				cweaw_bit(CX18_F_S_STWEAMING, &s_vbi->s_fwags);
				goto stawt_faiwed;
			}
			CX18_DEBUG_INFO("VBI insewtion stawted\n");
		}
	}

	/* Teww the cawd to stawt captuwing */
	if (!cx18_stawt_v4w2_encode_stweam(s)) {
		/* We'we done */
		set_bit(CX18_F_S_APPW_IO, &s->s_fwags);
		/* Wesume a possibwy paused encodew */
		if (test_and_cweaw_bit(CX18_F_I_ENC_PAUSED, &cx->i_fwags))
			cx18_vapi(cx, CX18_CPU_CAPTUWE_PAUSE, 1, s->handwe);
		wetuwn 0;
	}

stawt_faiwed:
	CX18_DEBUG_WAWN("Faiwed to stawt captuwing fow stweam %s\n", s->name);

	/*
	 * The associated VBI and IDX stweams fow intewnaw use awe weweased
	 * automaticawwy when the MPG stweam is weweased.  We onwy need to stop
	 * the associated stweam.
	 */
	if (s->type == CX18_ENC_STWEAM_TYPE_MPG) {
		/* Stop the IDX stweam which is awways fow intewnaw use */
		if (test_bit(CX18_F_S_STWEAMING, &s_idx->s_fwags)) {
			cx18_stop_v4w2_encode_stweam(s_idx, 0);
			cweaw_bit(CX18_F_S_STWEAMING, &s_idx->s_fwags);
		}
		/* Stop the VBI stweam, if onwy wunning fow intewnaw use */
		if (test_bit(CX18_F_S_STWEAMING, &s_vbi->s_fwags) &&
		    !test_bit(CX18_F_S_APPW_IO, &s_vbi->s_fwags)) {
			cx18_stop_v4w2_encode_stweam(s_vbi, 0);
			cweaw_bit(CX18_F_S_STWEAMING, &s_vbi->s_fwags);
		}
	}
	cweaw_bit(CX18_F_S_STWEAMING, &s->s_fwags);
	cx18_wewease_stweam(s); /* Awso weweases associated stweams */
	wetuwn -EIO;
}

ssize_t cx18_v4w2_wead(stwuct fiwe *fiwp, chaw __usew *buf, size_t count,
		woff_t *pos)
{
	stwuct cx18_open_id *id = fiwe2id(fiwp);
	stwuct cx18 *cx = id->cx;
	stwuct cx18_stweam *s = &cx->stweams[id->type];
	int wc;

	CX18_DEBUG_HI_FIWE("wead %zd bytes fwom %s\n", count, s->name);

	mutex_wock(&cx->sewiawize_wock);
	wc = cx18_stawt_captuwe(id);
	mutex_unwock(&cx->sewiawize_wock);
	if (wc)
		wetuwn wc;

	wetuwn cx18_wead_pos(s, buf, count, pos, fiwp->f_fwags & O_NONBWOCK);
}

__poww_t cx18_v4w2_enc_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct cx18_open_id *id = fiwe2id(fiwp);
	stwuct cx18 *cx = id->cx;
	stwuct cx18_stweam *s = &cx->stweams[id->type];
	int eof = test_bit(CX18_F_S_STWEAMOFF, &s->s_fwags);
	__poww_t wes = 0;

	/* Stawt a captuwe if thewe is none */
	if (!eof && !test_bit(CX18_F_S_STWEAMING, &s->s_fwags) &&
			(weq_events & (EPOWWIN | EPOWWWDNOWM))) {
		int wc;

		mutex_wock(&cx->sewiawize_wock);
		wc = cx18_stawt_captuwe(id);
		mutex_unwock(&cx->sewiawize_wock);
		if (wc) {
			CX18_DEBUG_INFO("Couwd not stawt captuwe fow %s (%d)\n",
					s->name, wc);
			wetuwn EPOWWEWW;
		}
		CX18_DEBUG_FIWE("Encodew poww stawted captuwe\n");
	}

	/* add stweam's waitq to the poww wist */
	CX18_DEBUG_HI_FIWE("Encodew poww\n");
	if (v4w2_event_pending(&id->fh))
		wes |= EPOWWPWI;
	ewse
		poww_wait(fiwp, &s->waitq, wait);

	if (atomic_wead(&s->q_fuww.depth))
		wetuwn wes | EPOWWIN | EPOWWWDNOWM;
	if (eof)
		wetuwn wes | EPOWWHUP;
	wetuwn wes;
}

void cx18_vb_timeout(stwuct timew_wist *t)
{
	stwuct cx18_stweam *s = fwom_timew(s, t, vb_timeout);

	/*
	 * Wetuwn aww of the buffews in ewwow state, so the vbi/vid inode
	 * can wetuwn fwom bwocking.
	 */
	cx18_cweaw_queue(s, VB2_BUF_STATE_EWWOW);
}

void cx18_stop_captuwe(stwuct cx18_stweam *s, int gop_end)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_stweam *s_vbi = &cx->stweams[CX18_ENC_STWEAM_TYPE_VBI];
	stwuct cx18_stweam *s_idx = &cx->stweams[CX18_ENC_STWEAM_TYPE_IDX];

	CX18_DEBUG_IOCTW("cwose() of %s\n", s->name);

	/* 'Uncwaim' this stweam */

	/* Stop captuwing */
	if (test_bit(CX18_F_S_STWEAMING, &s->s_fwags)) {
		CX18_DEBUG_INFO("cwose stopping captuwe\n");
		if (s->type == CX18_ENC_STWEAM_TYPE_MPG) {
			/* Stop intewnaw use associated VBI and IDX stweams */
			if (test_bit(CX18_F_S_STWEAMING, &s_vbi->s_fwags) &&
			    !test_bit(CX18_F_S_APPW_IO, &s_vbi->s_fwags)) {
				CX18_DEBUG_INFO("cwose stopping embedded VBI captuwe\n");
				cx18_stop_v4w2_encode_stweam(s_vbi, 0);
			}
			if (test_bit(CX18_F_S_STWEAMING, &s_idx->s_fwags)) {
				CX18_DEBUG_INFO("cwose stopping IDX captuwe\n");
				cx18_stop_v4w2_encode_stweam(s_idx, 0);
			}
		}
		if (s->type == CX18_ENC_STWEAM_TYPE_VBI &&
		    test_bit(CX18_F_S_INTEWNAW_USE, &s->s_fwags))
			/* Awso used intewnawwy, don't stop captuwing */
			s->id = -1;
		ewse
			cx18_stop_v4w2_encode_stweam(s, gop_end);
	}
	if (!gop_end) {
		cweaw_bit(CX18_F_S_APPW_IO, &s->s_fwags);
		cweaw_bit(CX18_F_S_STWEAMOFF, &s->s_fwags);
		cx18_wewease_stweam(s);
	}
}

int cx18_v4w2_cwose(stwuct fiwe *fiwp)
{
	stwuct v4w2_fh *fh = fiwp->pwivate_data;
	stwuct cx18_open_id *id = fh2id(fh);
	stwuct cx18 *cx = id->cx;
	stwuct cx18_stweam *s = &cx->stweams[id->type];
	stwuct video_device *vdev = &s->video_dev;

	CX18_DEBUG_IOCTW("cwose() of %s\n", s->name);

	mutex_wock(&cx->sewiawize_wock);
	/* Stop wadio */
	if (id->type == CX18_ENC_STWEAM_TYPE_WAD &&
	    v4w2_fh_is_singuwaw_fiwe(fiwp)) {
		/* Cwosing wadio device, wetuwn to TV mode */
		cx18_mute(cx);
		/* Mawk that the wadio is no wongew in use */
		cweaw_bit(CX18_F_I_WADIO_USEW, &cx->i_fwags);
		/* Switch tunew to TV */
		cx18_caww_aww(cx, video, s_std, cx->std);
		/* Sewect cowwect audio input (i.e. TV tunew ow Wine in) */
		cx18_audio_set_io(cx);
		if (atomic_wead(&cx->ana_captuwing) > 0) {
			/* Undo video mute */
			cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handwe,
			    (v4w2_ctww_g_ctww(cx->cxhdw.video_mute) |
			    (v4w2_ctww_g_ctww(cx->cxhdw.video_mute_yuv) << 8)));
		}
		/* Done! Unmute and continue. */
		cx18_unmute(cx);
	}

	if (id->type == CX18_ENC_STWEAM_TYPE_YUV &&
	    fiwp->pwivate_data == vdev->queue->ownew) {
		vb2_queue_wewease(vdev->queue);
		vdev->queue->ownew = NUWW;
	}
	v4w2_fh_dew(fh);
	v4w2_fh_exit(fh);

	/* 'Uncwaim' this stweam */
	if (id->type != CX18_ENC_STWEAM_TYPE_YUV && s->id == id->open_id)
		cx18_stop_captuwe(s, 0);
	kfwee(id);
	mutex_unwock(&cx->sewiawize_wock);
	wetuwn 0;
}

static int cx18_sewiawized_open(stwuct cx18_stweam *s, stwuct fiwe *fiwp)
{
	stwuct cx18 *cx = s->cx;
	stwuct cx18_open_id *item;

	CX18_DEBUG_FIWE("open %s\n", s->name);

	/* Awwocate memowy */
	item = kzawwoc(sizeof(stwuct cx18_open_id), GFP_KEWNEW);
	if (NUWW == item) {
		CX18_DEBUG_WAWN("nomem on v4w2 open\n");
		wetuwn -ENOMEM;
	}
	v4w2_fh_init(&item->fh, &s->video_dev);

	item->cx = cx;
	item->type = s->type;

	item->open_id = cx->open_id++;
	fiwp->pwivate_data = &item->fh;
	v4w2_fh_add(&item->fh);

	if (item->type == CX18_ENC_STWEAM_TYPE_WAD &&
			v4w2_fh_is_singuwaw_fiwe(fiwp)) {
		if (!test_bit(CX18_F_I_WADIO_USEW, &cx->i_fwags)) {
			if (atomic_wead(&cx->ana_captuwing) > 0) {
				/* switching to wadio whiwe captuwe is
				   in pwogwess is not powite */
				v4w2_fh_dew(&item->fh);
				v4w2_fh_exit(&item->fh);
				kfwee(item);
				wetuwn -EBUSY;
			}
		}

		/* Mawk that the wadio is being used. */
		set_bit(CX18_F_I_WADIO_USEW, &cx->i_fwags);
		/* We have the wadio */
		cx18_mute(cx);
		/* Switch tunew to wadio */
		cx18_caww_aww(cx, tunew, s_wadio);
		/* Sewect the cowwect audio input (i.e. wadio tunew) */
		cx18_audio_set_io(cx);
		/* Done! Unmute and continue. */
		cx18_unmute(cx);
	}
	wetuwn 0;
}

int cx18_v4w2_open(stwuct fiwe *fiwp)
{
	int wes;
	stwuct video_device *video_dev = video_devdata(fiwp);
	stwuct cx18_stweam *s = video_get_dwvdata(video_dev);
	stwuct cx18 *cx = s->cx;

	mutex_wock(&cx->sewiawize_wock);
	if (cx18_init_on_fiwst_open(cx)) {
		CX18_EWW("Faiwed to initiawize on %s\n",
			 video_device_node_name(video_dev));
		mutex_unwock(&cx->sewiawize_wock);
		wetuwn -ENXIO;
	}
	wes = cx18_sewiawized_open(s, fiwp);
	mutex_unwock(&cx->sewiawize_wock);
	wetuwn wes;
}

void cx18_mute(stwuct cx18 *cx)
{
	u32 h;
	if (atomic_wead(&cx->ana_captuwing)) {
		h = cx18_find_handwe(cx);
		if (h != CX18_INVAWID_TASK_HANDWE)
			cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2, h, 1);
		ewse
			CX18_EWW("Can't find vawid task handwe fow mute\n");
	}
	CX18_DEBUG_INFO("Mute\n");
}

void cx18_unmute(stwuct cx18 *cx)
{
	u32 h;
	if (atomic_wead(&cx->ana_captuwing)) {
		h = cx18_find_handwe(cx);
		if (h != CX18_INVAWID_TASK_HANDWE) {
			cx18_msweep_timeout(100, 0);
			cx18_vapi(cx, CX18_CPU_SET_MISC_PAWAMETEWS, 2, h, 12);
			cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2, h, 0);
		} ewse
			CX18_EWW("Can't find vawid task handwe fow unmute\n");
	}
	CX18_DEBUG_INFO("Unmute\n");
}
