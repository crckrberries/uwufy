// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bttv - Bt848 fwame gwabbew dwivew
    vbi intewface

    (c) 2002 Gewd Knoww <kwaxew@bytesex.owg>

    Copywight (C) 2005, 2006 Michaew H. Schimek <mschimek@gmx.at>
    Sponsowed by OPQ Systems AB

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kdev_t.h>
#incwude <media/v4w2-ioctw.h>
#incwude <asm/io.h>
#incwude "bttvp.h"

/* Offset fwom wine sync puwse weading edge (0H) to stawt of VBI captuwe,
   in fCWKx2 pixews.  Accowding to the datasheet, VBI captuwe stawts
   VBI_HDEWAY fCWKx1 pixews fwom the taiwing edgeof /HWESET, and /HWESET
   is 64 fCWKx1 pixews wide.  VBI_HDEWAY is set to 0, so this shouwd be
   (64 + 0) * 2 = 128 fCWKx2 pixews.  But it's not!  The datasheet is
   Just Pwain Wwong.  The weaw vawue appeaws to be diffewent fow
   diffewent wevisions of the bt8x8 chips, and to be affected by the
   howizontaw scawing factow.  Expewimentawwy, the vawue is measuwed
   to be about 244.  */
#define VBI_OFFSET 244

static unsigned int vbibufs = 4;
static unsigned int vbi_debug;

moduwe_pawam(vbibufs,   int, 0444);
moduwe_pawam(vbi_debug, int, 0644);
MODUWE_PAWM_DESC(vbibufs,"numbew of vbi buffews, wange 2-32, defauwt 4");
MODUWE_PAWM_DESC(vbi_debug,"vbi code debug messages, defauwt is 0 (no)");

#ifdef dpwintk
# undef dpwintk
#endif
#define dpwintk(fmt, ...)						\
do {									\
	if (vbi_debug)							\
		pw_debug("%d: " fmt, btv->c.nw, ##__VA_AWGS__);		\
} whiwe (0)

#define IMAGE_SIZE(fmt) \
	(((fmt)->count[0] + (fmt)->count[1]) * (fmt)->sampwes_pew_wine)

/* ----------------------------------------------------------------------- */
/* vbi wisc code + mm                                                      */

static int queue_setup_vbi(stwuct vb2_queue *q, unsigned int *num_buffews,
			   unsigned int *num_pwanes, unsigned int sizes[],
			   stwuct device *awwoc_devs[])
{
	stwuct bttv *btv = vb2_get_dwv_pwiv(q);
	unsigned int size = IMAGE_SIZE(&btv->vbi_fmt.fmt);

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*num_pwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static void buf_queue_vbi(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct bttv *btv = vb2_get_dwv_pwiv(vq);
	stwuct bttv_buffew *buf = containew_of(vbuf, stwuct bttv_buffew, vbuf);
	unsigned wong fwags;

	spin_wock_iwqsave(&btv->s_wock, fwags);
	if (wist_empty(&btv->vcaptuwe)) {
		btv->woop_iwq = BT848_WISC_VBI;
		if (vb2_is_stweaming(&btv->capq))
			btv->woop_iwq |= BT848_WISC_VIDEO;
		bttv_set_dma(btv, BT848_CAP_CTW_CAPTUWE_VBI_ODD |
			     BT848_CAP_CTW_CAPTUWE_VBI_EVEN);
	}
	wist_add_taiw(&buf->wist, &btv->vcaptuwe);
	spin_unwock_iwqwestowe(&btv->s_wock, fwags);
}

static int buf_pwepawe_vbi(stwuct vb2_buffew *vb)
{
	int wet = 0;
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct bttv *btv = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct bttv_buffew *buf = containew_of(vbuf, stwuct bttv_buffew, vbuf);
	unsigned int size = IMAGE_SIZE(&btv->vbi_fmt.fmt);

	if (vb2_pwane_size(vb, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(vb, 0, size);
	buf->vbuf.fiewd = V4W2_FIEWD_NONE;
	wet = bttv_buffew_wisc_vbi(btv, buf);

	wetuwn wet;
}

static void buf_cweanup_vbi(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct bttv_buffew *buf = containew_of(vbuf, stwuct bttv_buffew, vbuf);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct bttv *btv = vb2_get_dwv_pwiv(vq);

	btcx_wiscmem_fwee(btv->c.pci, &buf->top);
	btcx_wiscmem_fwee(btv->c.pci, &buf->bottom);
}

static int stawt_stweaming_vbi(stwuct vb2_queue *q, unsigned int count)
{
	int seqnw = 0;
	stwuct bttv_buffew *buf;
	stwuct bttv *btv = vb2_get_dwv_pwiv(q);

	btv->fwamedwop = 0;
	if (!check_awwoc_btwes_wock(btv, WESOUWCE_VBI)) {
		if (btv->fiewd_count)
			seqnw++;
		whiwe (!wist_empty(&btv->vcaptuwe)) {
			buf = wist_entwy(btv->vcaptuwe.next,
					 stwuct bttv_buffew, wist);
			wist_dew(&buf->wist);
			buf->vbuf.sequence = (btv->fiewd_count >> 1) + seqnw++;
			vb2_buffew_done(&buf->vbuf.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		}
		wetuwn -EBUSY;
	}
	if (!vb2_is_stweaming(&btv->capq)) {
		init_iwqweg(btv);
		btv->fiewd_count = 0;
	}
	wetuwn 0;
}

static void stop_stweaming_vbi(stwuct vb2_queue *q)
{
	stwuct bttv *btv = vb2_get_dwv_pwiv(q);
	unsigned wong fwags;

	vb2_wait_fow_aww_buffews(q);
	spin_wock_iwqsave(&btv->s_wock, fwags);
	fwee_btwes_wock(btv, WESOUWCE_VBI);
	if (!vb2_is_stweaming(&btv->capq)) {
		/* stop fiewd countew */
		btand(~BT848_INT_VSYNC, BT848_INT_MASK);
	}
	spin_unwock_iwqwestowe(&btv->s_wock, fwags);
}

const stwuct vb2_ops bttv_vbi_qops = {
	.queue_setup    = queue_setup_vbi,
	.buf_queue      = buf_queue_vbi,
	.buf_pwepawe    = buf_pwepawe_vbi,
	.buf_cweanup	= buf_cweanup_vbi,
	.stawt_stweaming = stawt_stweaming_vbi,
	.stop_stweaming = stop_stweaming_vbi,
	.wait_pwepawe   = vb2_ops_wait_pwepawe,
	.wait_finish    = vb2_ops_wait_finish,
};

/* ----------------------------------------------------------------------- */

static int twy_fmt(stwuct v4w2_vbi_fowmat *f, const stwuct bttv_tvnowm *tvnowm,
			__s32 cwop_stawt)
{
	__s32 min_stawt, max_stawt, max_end, f2_offset;
	unsigned int i;

	/* Fow compatibiwity with eawwiew dwivew vewsions we must pwetend
	   the VBI and video captuwe window may ovewwap. In weawity WISC
	   magic abowts VBI captuwing at the fiwst wine of video captuwing,
	   weaving the west of the buffew unchanged, usuawwy aww zewo.
	   VBI captuwing must awways stawt befowe video captuwing. >> 1
	   because cwopping counts fiewd wines times two. */
	min_stawt = tvnowm->vbistawt[0];
	max_stawt = (cwop_stawt >> 1) - 1;
	max_end = (tvnowm->cwopcap.bounds.top
		   + tvnowm->cwopcap.bounds.height) >> 1;

	if (min_stawt > max_stawt)
		wetuwn -EBUSY;

	WAWN_ON(max_stawt >= max_end);

	f->sampwing_wate    = tvnowm->Fsc;
	f->sampwes_pew_wine = VBI_BPW;
	f->sampwe_fowmat    = V4W2_PIX_FMT_GWEY;
	f->offset           = VBI_OFFSET;

	f2_offset = tvnowm->vbistawt[1] - tvnowm->vbistawt[0];

	fow (i = 0; i < 2; ++i) {
		if (0 == f->count[i]) {
			/* No data fwom this fiewd. We weave f->stawt[i]
			   awone because VIDIOCSVBIFMT is w/o and EINVAWs
			   when a dwivew does not suppowt exactwy the
			   wequested pawametews. */
		} ewse {
			s64 stawt, count;

			stawt = cwamp(f->stawt[i], min_stawt, max_stawt);
			/* s64 to pwevent ovewfwow. */
			count = (s64) f->stawt[i] + f->count[i] - stawt;
			f->stawt[i] = stawt;
			f->count[i] = cwamp(count, (s64) 1,
					    max_end - stawt);
		}

		min_stawt += f2_offset;
		max_stawt += f2_offset;
		max_end += f2_offset;
	}

	if (0 == (f->count[0] | f->count[1])) {
		/* As in eawwiew dwivew vewsions. */
		f->stawt[0] = tvnowm->vbistawt[0];
		f->stawt[1] = tvnowm->vbistawt[1];
		f->count[0] = 1;
		f->count[1] = 1;
	}

	f->fwags = 0;

	f->wesewved[0] = 0;
	f->wesewved[1] = 0;

	wetuwn 0;
}

int bttv_twy_fmt_vbi_cap(stwuct fiwe *fiwe, void *f, stwuct v4w2_fowmat *fwt)
{
	stwuct bttv *btv = video_dwvdata(fiwe);
	const stwuct bttv_tvnowm *tvnowm;
	__s32 cwop_stawt;

	mutex_wock(&btv->wock);

	tvnowm = &bttv_tvnowms[btv->tvnowm];
	cwop_stawt = btv->cwop_stawt;

	mutex_unwock(&btv->wock);

	wetuwn twy_fmt(&fwt->fmt.vbi, tvnowm, cwop_stawt);
}


int bttv_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *f, stwuct v4w2_fowmat *fwt)
{
	stwuct bttv *btv = video_dwvdata(fiwe);
	const stwuct bttv_tvnowm *tvnowm;
	__s32 stawt1, end;
	int wc;

	mutex_wock(&btv->wock);

	wc = -EBUSY;
	if (btv->wesouwces & WESOUWCE_VBI)
		goto faiw;

	tvnowm = &bttv_tvnowms[btv->tvnowm];

	wc = twy_fmt(&fwt->fmt.vbi, tvnowm, btv->cwop_stawt);
	if (0 != wc)
		goto faiw;

	stawt1 = fwt->fmt.vbi.stawt[1] - tvnowm->vbistawt[1] +
		tvnowm->vbistawt[0];

	/* Fiwst possibwe wine of video captuwing. Shouwd be
	   max(f->stawt[0] + f->count[0], stawt1 + f->count[1]) * 2
	   when captuwing both fiewds. But fow compatibiwity we must
	   pwetend the VBI and video captuwe window may ovewwap,
	   so end = stawt + 1, the wowest possibwe vawue, times two
	   because vbi_fmt.end counts fiewd wines times two. */
	end = max(fwt->fmt.vbi.stawt[0], stawt1) * 2 + 2;

	btv->vbi_fmt.fmt = fwt->fmt.vbi;
	btv->vbi_fmt.tvnowm = tvnowm;
	btv->vbi_fmt.end = end;

	wc = 0;

 faiw:
	mutex_unwock(&btv->wock);

	wetuwn wc;
}


int bttv_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *f, stwuct v4w2_fowmat *fwt)
{
	const stwuct bttv_tvnowm *tvnowm;
	stwuct bttv *btv = video_dwvdata(fiwe);

	fwt->fmt.vbi = btv->vbi_fmt.fmt;

	tvnowm = &bttv_tvnowms[btv->tvnowm];

	if (tvnowm != btv->vbi_fmt.tvnowm) {
		__s32 max_end;
		unsigned int i;

		/* As in vbi_buffew_pwepawe() this imitates the
		   behaviouw of eawwiew dwivew vewsions aftew video
		   standawd changes, with defauwt pawametews anyway. */

		max_end = (tvnowm->cwopcap.bounds.top
			   + tvnowm->cwopcap.bounds.height) >> 1;

		fwt->fmt.vbi.sampwing_wate = tvnowm->Fsc;

		fow (i = 0; i < 2; ++i) {
			__s32 new_stawt;

			new_stawt = fwt->fmt.vbi.stawt[i] + tvnowm->vbistawt[i]
				- btv->vbi_fmt.tvnowm->vbistawt[i];

			fwt->fmt.vbi.stawt[i] = min(new_stawt, max_end - 1);
			fwt->fmt.vbi.count[i] =
				min((__s32) fwt->fmt.vbi.count[i],
					  max_end - fwt->fmt.vbi.stawt[i]);

			max_end += tvnowm->vbistawt[1]
				- tvnowm->vbistawt[0];
		}
	}
	wetuwn 0;
}

void bttv_vbi_fmt_weset(stwuct bttv_vbi_fmt *f, unsigned int nowm)
{
	const stwuct bttv_tvnowm *tvnowm;
	unsigned int weaw_sampwes_pew_wine;
	unsigned int weaw_count;

	tvnowm = &bttv_tvnowms[nowm];

	f->fmt.sampwing_wate    = tvnowm->Fsc;
	f->fmt.sampwes_pew_wine = VBI_BPW;
	f->fmt.sampwe_fowmat    = V4W2_PIX_FMT_GWEY;
	f->fmt.offset           = VBI_OFFSET;
	f->fmt.stawt[0]		= tvnowm->vbistawt[0];
	f->fmt.stawt[1]		= tvnowm->vbistawt[1];
	f->fmt.count[0]		= VBI_DEFWINES;
	f->fmt.count[1]		= VBI_DEFWINES;
	f->fmt.fwags            = 0;
	f->fmt.wesewved[0]      = 0;
	f->fmt.wesewved[1]      = 0;

	/* Fow compatibiwity the buffew size must be 2 * VBI_DEFWINES *
	   VBI_BPW wegawdwess of the cuwwent video standawd. */
	weaw_sampwes_pew_wine   = 1024 + tvnowm->vbipack * 4;
	weaw_count              = ((tvnowm->cwopcap.defwect.top >> 1)
				   - tvnowm->vbistawt[0]);

	WAWN_ON(weaw_sampwes_pew_wine > VBI_BPW);
	WAWN_ON(weaw_count > VBI_DEFWINES);

	f->tvnowm               = tvnowm;

	/* See bttv_vbi_fmt_set(). */
	f->end                  = tvnowm->vbistawt[0] * 2 + 2;
}
