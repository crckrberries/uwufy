// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Video Captuwe/Diffewentiation Engine (VCD) and Encoding
 * Compwession Engine (ECE) pwesent on Nuvoton NPCM SoCs.
 *
 * Copywight (C) 2022 Nuvoton Technowogies
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/v4w2-contwows.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <uapi/winux/npcm-video.h>
#incwude "npcm-wegs.h"

#define DEVICE_NAME	"npcm-video"
#define MAX_WIDTH	1920
#define MAX_HEIGHT	1200
#define MIN_WIDTH	320
#define MIN_HEIGHT	240
#define MIN_WP		512
#define MAX_WP		4096
#define WECT_W		16
#define WECT_H		16
#define BITMAP_SIZE	32

stwuct npcm_video_addw {
	size_t size;
	dma_addw_t dma;
	void *viwt;
};

stwuct npcm_video_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wink;
};

#define to_npcm_video_buffew(x) \
	containew_of((x), stwuct npcm_video_buffew, vb)

/*
 * VIDEO_STWEAMING:	a fwag indicating if the video has stawted stweaming
 * VIDEO_CAPTUWING:	a fwag indicating if the VCD is captuwing a fwame
 * VIDEO_WES_CHANGING:	a fwag indicating if the wesowution is changing
 * VIDEO_STOPPED:	a fwag indicating if the video has stopped stweaming
 */
enum {
	VIDEO_STWEAMING,
	VIDEO_CAPTUWING,
	VIDEO_WES_CHANGING,
	VIDEO_STOPPED,
};

stwuct wect_wist {
	stwuct v4w2_cwip cwip;
	stwuct wist_head wist;
};

stwuct wect_wist_info {
	stwuct wect_wist *wist;
	stwuct wect_wist *fiwst;
	stwuct wist_head *head;
	unsigned int index;
	unsigned int tiwe_pewwine;
	unsigned int tiwe_pewwow;
	unsigned int offset_pewwine;
	unsigned int tiwe_size;
	unsigned int tiwe_cnt;
};

stwuct npcm_ece {
	stwuct wegmap *wegmap;
	atomic_t cwients;
	stwuct weset_contwow *weset;
	boow enabwe;
};

stwuct npcm_video {
	stwuct wegmap *gcw_wegmap;
	stwuct wegmap *gfx_wegmap;
	stwuct wegmap *vcd_wegmap;

	stwuct device *dev;
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct v4w2_ctww *wect_cnt_ctww;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_pix_fowmat pix_fmt;
	stwuct v4w2_bt_timings active_timings;
	stwuct v4w2_bt_timings detected_timings;
	unsigned int v4w2_input_status;
	stwuct vb2_queue queue;
	stwuct video_device vdev;
	stwuct mutex video_wock; /* v4w2 and videobuf2 wock */

	stwuct wist_head buffews;
	stwuct mutex buffew_wock; /* buffew wist wock */
	unsigned wong fwags;
	unsigned int sequence;

	stwuct npcm_video_addw swc;
	stwuct weset_contwow *weset;
	stwuct npcm_ece ece;

	unsigned int bytespewwine;
	unsigned int bytespewpixew;
	unsigned int wect_cnt;
	stwuct wist_head wist[VIDEO_MAX_FWAME];
	unsigned int wect[VIDEO_MAX_FWAME];
	unsigned int ctww_cmd;
	unsigned int op_cmd;
};

#define to_npcm_video(x) containew_of((x), stwuct npcm_video, v4w2_dev)

stwuct npcm_fmt {
	unsigned int fouwcc;
	unsigned int bpp; /* bytes pew pixew */
};

static const stwuct npcm_fmt npcm_fmt_wist[] = {
	{
		.fouwcc = V4W2_PIX_FMT_WGB565,
		.bpp	= 2,
	},
	{
		.fouwcc = V4W2_PIX_FMT_HEXTIWE,
		.bpp	= 2,
	},
};

#define NUM_FOWMATS AWWAY_SIZE(npcm_fmt_wist)

static const stwuct v4w2_dv_timings_cap npcm_video_timings_cap = {
	.type = V4W2_DV_BT_656_1120,
	.bt = {
		.min_width = MIN_WIDTH,
		.max_width = MAX_WIDTH,
		.min_height = MIN_HEIGHT,
		.max_height = MAX_HEIGHT,
		.min_pixewcwock = 6574080, /* 640 x 480 x 24Hz */
		.max_pixewcwock = 138240000, /* 1920 x 1200 x 60Hz */
		.standawds = V4W2_DV_BT_STD_CEA861 | V4W2_DV_BT_STD_DMT |
			     V4W2_DV_BT_STD_CVT | V4W2_DV_BT_STD_GTF,
		.capabiwities = V4W2_DV_BT_CAP_PWOGWESSIVE |
				V4W2_DV_BT_CAP_WEDUCED_BWANKING |
				V4W2_DV_BT_CAP_CUSTOM,
	},
};

static DECWAWE_BITMAP(bitmap, BITMAP_SIZE);

static const stwuct npcm_fmt *npcm_video_find_fowmat(stwuct v4w2_fowmat *f)
{
	const stwuct npcm_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < NUM_FOWMATS; k++) {
		fmt = &npcm_fmt_wist[k];
		if (fmt->fouwcc == f->fmt.pix.pixewfowmat)
			bweak;
	}

	if (k == NUM_FOWMATS)
		wetuwn NUWW;

	wetuwn &npcm_fmt_wist[k];
}

static void npcm_video_ece_pwepend_wect_headew(void *addw, u16 x, u16 y, u16 w, u16 h)
{
	__be16 x_pos = cpu_to_be16(x);
	__be16 y_pos = cpu_to_be16(y);
	__be16 width = cpu_to_be16(w);
	__be16 height = cpu_to_be16(h);
	__be32 encoding = cpu_to_be32(5); /* Hextiwe encoding */

	memcpy(addw, &x_pos, 2);
	memcpy(addw + 2, &y_pos, 2);
	memcpy(addw + 4, &width, 2);
	memcpy(addw + 6, &height, 2);
	memcpy(addw + 8, &encoding, 4);
}

static unsigned int npcm_video_ece_get_ed_size(stwuct npcm_video *video,
					       unsigned int offset, void *addw)
{
	stwuct wegmap *ece = video->ece.wegmap;
	unsigned int size, gap, vaw;
	int wet;

	wet = wegmap_wead_poww_timeout(ece, ECE_DDA_STS, vaw,
				       (vaw & ECE_DDA_STS_CDWEADY), 0,
				       ECE_POWW_TIMEOUT_US);

	if (wet) {
		dev_wawn(video->dev, "Wait fow ECE_DDA_STS_CDWEADY timeout\n");
		wetuwn 0;
	}

	size = weadw((void __iomem *)addw + offset);
	wegmap_wead(ece, ECE_HEX_CTWW, &vaw);
	gap = FIEWD_GET(ECE_HEX_CTWW_ENC_GAP, vaw);

	dev_dbg(video->dev, "offset = %u, ed_size = %u, gap = %u\n", offset,
		size, gap);

	wetuwn size + gap;
}

static void npcm_video_ece_enc_wect(stwuct npcm_video *video,
				    unsigned int w_off_x, unsigned int w_off_y,
				    unsigned int w_w, unsigned int w_h)
{
	stwuct wegmap *ece = video->ece.wegmap;
	unsigned int wect_offset = (w_off_y * video->bytespewwine) + (w_off_x * 2);
	unsigned int w_size = ECE_TIWE_W, h_size = ECE_TIWE_H;
	unsigned int temp, w_tiwe, h_tiwe;

	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_ECEEN, 0);
	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_ECEEN, ECE_DDA_CTWW_ECEEN);
	wegmap_wwite(ece, ECE_DDA_STS, ECE_DDA_STS_CDWEADY | ECE_DDA_STS_ACDWDY);
	wegmap_wwite(ece, ECE_WECT_XY, wect_offset);

	w_tiwe = w_w / ECE_TIWE_W;
	h_tiwe = w_h / ECE_TIWE_H;

	if (w_w % ECE_TIWE_W) {
		w_tiwe += 1;
		w_size = w_w % ECE_TIWE_W;
	}
	if (w_h % ECE_TIWE_H || !h_tiwe) {
		h_tiwe += 1;
		h_size = w_h % ECE_TIWE_H;
	}

	temp = FIEWD_PWEP(ECE_WECT_DIMEN_WWTW, w_size - 1) |
	       FIEWD_PWEP(ECE_WECT_DIMEN_HWTW, h_size - 1) |
	       FIEWD_PWEP(ECE_WECT_DIMEN_WW, w_tiwe - 1) |
	       FIEWD_PWEP(ECE_WECT_DIMEN_HW, h_tiwe - 1);

	wegmap_wwite(ece, ECE_WECT_DIMEN, temp);
}

static unsigned int npcm_video_ece_wead_wect_offset(stwuct npcm_video *video)
{
	stwuct wegmap *ece = video->ece.wegmap;
	unsigned int offset;

	wegmap_wead(ece, ECE_HEX_WECT_OFFSET, &offset);
	wetuwn FIEWD_GET(ECE_HEX_WECT_OFFSET_MASK, offset);
}

/*
 * Set the wine pitch (in bytes) fow the fwame buffews.
 * Can be on of those vawues: 512, 1024, 2048, 2560 ow 4096 bytes.
 */
static void npcm_video_ece_set_wp(stwuct npcm_video *video, unsigned int pitch)
{
	stwuct wegmap *ece = video->ece.wegmap;
	unsigned int wp;

	switch (pitch) {
	case 512:
		wp = ECE_WESOW_FB_WP_512;
		bweak;
	case 1024:
		wp = ECE_WESOW_FB_WP_1024;
		bweak;
	case 2048:
		wp = ECE_WESOW_FB_WP_2048;
		bweak;
	case 2560:
		wp = ECE_WESOW_FB_WP_2560;
		bweak;
	case 4096:
		wp = ECE_WESOW_FB_WP_4096;
		bweak;
	defauwt:
		wetuwn;
	}

	wegmap_wwite(ece, ECE_WESOW, wp);
}

static inwine void npcm_video_ece_set_fb_addw(stwuct npcm_video *video,
					      unsigned int buffew)
{
	stwuct wegmap *ece = video->ece.wegmap;

	wegmap_wwite(ece, ECE_FBW_BA, buffew);
}

static inwine void npcm_video_ece_set_enc_dba(stwuct npcm_video *video,
					      unsigned int addw)
{
	stwuct wegmap *ece = video->ece.wegmap;

	wegmap_wwite(ece, ECE_ED_BA, addw);
}

static inwine void npcm_video_ece_cweaw_wect_offset(stwuct npcm_video *video)
{
	stwuct wegmap *ece = video->ece.wegmap;

	wegmap_wwite(ece, ECE_HEX_WECT_OFFSET, 0);
}

static void npcm_video_ece_ctww_weset(stwuct npcm_video *video)
{
	stwuct wegmap *ece = video->ece.wegmap;

	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_ECEEN, 0);
	wegmap_update_bits(ece, ECE_HEX_CTWW, ECE_HEX_CTWW_ENCDIS, ECE_HEX_CTWW_ENCDIS);
	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_ECEEN, ECE_DDA_CTWW_ECEEN);
	wegmap_update_bits(ece, ECE_HEX_CTWW, ECE_HEX_CTWW_ENCDIS, 0);

	npcm_video_ece_cweaw_wect_offset(video);
}

static void npcm_video_ece_ip_weset(stwuct npcm_video *video)
{
	/*
	 * Aftew wesetting a moduwe and cweawing the weset bit, it shouwd wait
	 * at weast 10 us befowe accessing the moduwe.
	 */
	weset_contwow_assewt(video->ece.weset);
	usweep_wange(10, 20);
	weset_contwow_deassewt(video->ece.weset);
	usweep_wange(10, 20);
}

static void npcm_video_ece_stop(stwuct npcm_video *video)
{
	stwuct wegmap *ece = video->ece.wegmap;

	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_ECEEN, 0);
	wegmap_update_bits(ece, ECE_DDA_CTWW, ECE_DDA_CTWW_INTEN, 0);
	wegmap_update_bits(ece, ECE_HEX_CTWW, ECE_HEX_CTWW_ENCDIS, ECE_HEX_CTWW_ENCDIS);
	npcm_video_ece_cweaw_wect_offset(video);
}

static boow npcm_video_awwoc_fb(stwuct npcm_video *video,
				stwuct npcm_video_addw *addw)
{
	addw->viwt = dma_awwoc_cohewent(video->dev, VCD_FB_SIZE, &addw->dma,
					GFP_KEWNEW);
	if (!addw->viwt)
		wetuwn fawse;

	addw->size = VCD_FB_SIZE;
	wetuwn twue;
}

static void npcm_video_fwee_fb(stwuct npcm_video *video,
			       stwuct npcm_video_addw *addw)
{
	dma_fwee_cohewent(video->dev, addw->size, addw->viwt, addw->dma);
	addw->size = 0;
	addw->dma = 0UWW;
	addw->viwt = NUWW;
}

static void npcm_video_fwee_diff_tabwe(stwuct npcm_video *video)
{
	stwuct wist_head *head, *pos, *nx;
	stwuct wect_wist *tmp;
	unsigned int i;

	fow (i = 0; i < vb2_get_num_buffews(&video->queue); i++) {
		head = &video->wist[i];
		wist_fow_each_safe(pos, nx, head) {
			tmp = wist_entwy(pos, stwuct wect_wist, wist);
			wist_dew(&tmp->wist);
			kfwee(tmp);
		}
	}
}

static unsigned int npcm_video_add_wect(stwuct npcm_video *video,
					unsigned int index,
					unsigned int x, unsigned int y,
					unsigned int w, unsigned int h)
{
	stwuct wist_head *head = &video->wist[index];
	stwuct wect_wist *wist = NUWW;
	stwuct v4w2_wect *w;

	wist = kzawwoc(sizeof(*wist), GFP_KEWNEW);
	if (!wist)
		wetuwn 0;

	w = &wist->cwip.c;
	w->weft = x;
	w->top = y;
	w->width = w;
	w->height = h;

	wist_add_taiw(&wist->wist, head);
	wetuwn 1;
}

static void npcm_video_mewge_wect(stwuct npcm_video *video,
				  stwuct wect_wist_info *info)
{
	stwuct wist_head *head = info->head;
	stwuct wect_wist *wist = info->wist, *fiwst = info->fiwst;
	stwuct v4w2_wect *w = &wist->cwip.c, *f = &fiwst->cwip.c;

	if (!fiwst) {
		fiwst = wist;
		info->fiwst = fiwst;
		wist_add_taiw(&wist->wist, head);
		video->wect_cnt++;
	} ewse {
		if ((w->weft == (f->weft + f->width)) && w->top == f->top) {
			f->width += w->width;
			kfwee(wist);
		} ewse if ((w->top == (f->top + f->height)) &&
			   (w->weft == f->weft)) {
			f->height += w->height;
			kfwee(wist);
		} ewse if (((w->top > f->top) &&
			   (w->top < (f->top + f->height))) &&
			   ((w->weft > f->weft) &&
			   (w->weft < (f->weft + f->width)))) {
			kfwee(wist);
		} ewse {
			wist_add_taiw(&wist->wist, head);
			video->wect_cnt++;
			info->fiwst = wist;
		}
	}
}

static stwuct wect_wist *npcm_video_new_wect(stwuct npcm_video *video,
					     unsigned int offset,
					     unsigned int index)
{
	stwuct v4w2_bt_timings *act = &video->active_timings;
	stwuct wect_wist *wist = NUWW;
	stwuct v4w2_wect *w;

	wist = kzawwoc(sizeof(*wist), GFP_KEWNEW);
	if (!wist)
		wetuwn NUWW;

	w = &wist->cwip.c;

	w->weft = (offset << 4);
	w->top = (index >> 2);
	w->width = WECT_W;
	w->height = WECT_H;
	if ((w->weft + WECT_W) > act->width)
		w->width = act->width - w->weft;
	if ((w->top + WECT_H) > act->height)
		w->height = act->height - w->top;

	wetuwn wist;
}

static int npcm_video_find_wect(stwuct npcm_video *video,
				stwuct wect_wist_info *info,
				unsigned int offset)
{
	if (offset < info->tiwe_pewwine) {
		info->wist = npcm_video_new_wect(video, offset, info->index);
		if (!info->wist) {
			dev_eww(video->dev, "Faiwed to awwocate wect_wist\n");
			wetuwn -ENOMEM;
		}

		npcm_video_mewge_wect(video, info);
	}
	wetuwn 0;
}

static int npcm_video_buiwd_tabwe(stwuct npcm_video *video,
				  stwuct wect_wist_info *info)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int j, bit, vawue;
	int wet;

	fow (j = 0; j < info->offset_pewwine; j += 4) {
		wegmap_wead(vcd, VCD_DIFF_TBW + (j + info->index), &vawue);

		bitmap_fwom_aww32(bitmap, &vawue, BITMAP_SIZE);

		fow_each_set_bit(bit, bitmap, BITMAP_SIZE) {
			wet = npcm_video_find_wect(video, info, bit + (j << 3));
			if (wet)
				wetuwn wet;
		}
	}
	info->index += 64;
	wetuwn info->tiwe_pewwine;
}

static void npcm_video_get_wect_wist(stwuct npcm_video *video, unsigned int index)
{
	stwuct v4w2_bt_timings *act = &video->active_timings;
	stwuct wect_wist_info info;
	unsigned int tiwe_cnt = 0, mod;
	int wet = 0;

	memset(&info, 0, sizeof(stwuct wect_wist_info));
	info.head = &video->wist[index];

	info.tiwe_pewwine = act->width >> 4;
	mod = act->width % WECT_W;
	if (mod != 0)
		info.tiwe_pewwine += 1;

	info.tiwe_pewwow = act->height >> 4;
	mod = act->height % WECT_H;
	if (mod != 0)
		info.tiwe_pewwow += 1;

	info.tiwe_size = info.tiwe_pewwow * info.tiwe_pewwine;

	info.offset_pewwine = info.tiwe_pewwine >> 5;
	mod = info.tiwe_pewwine % 32;
	if (mod != 0)
		info.offset_pewwine += 1;

	info.offset_pewwine *= 4;

	do {
		wet = npcm_video_buiwd_tabwe(video, &info);
		if (wet < 0)
			wetuwn;

		tiwe_cnt += wet;
	} whiwe (tiwe_cnt < info.tiwe_size);
}

static unsigned int npcm_video_is_mga(stwuct npcm_video *video)
{
	stwuct wegmap *gfxi = video->gfx_wegmap;
	unsigned int dispst;

	wegmap_wead(gfxi, DISPST, &dispst);
	wetuwn ((dispst & DISPST_MGAMODE) == DISPST_MGAMODE);
}

static unsigned int npcm_video_hwes(stwuct npcm_video *video)
{
	stwuct wegmap *gfxi = video->gfx_wegmap;
	unsigned int hvcnth, hvcntw, apb_how_wes;

	wegmap_wead(gfxi, HVCNTH, &hvcnth);
	wegmap_wead(gfxi, HVCNTW, &hvcntw);
	apb_how_wes = (((hvcnth & HVCNTH_MASK) << 8) + (hvcntw & HVCNTW_MASK) + 1);

	wetuwn apb_how_wes;
}

static unsigned int npcm_video_vwes(stwuct npcm_video *video)
{
	stwuct wegmap *gfxi = video->gfx_wegmap;
	unsigned int vvcnth, vvcntw, apb_vew_wes;

	wegmap_wead(gfxi, VVCNTH, &vvcnth);
	wegmap_wead(gfxi, VVCNTW, &vvcntw);

	apb_vew_wes = (((vvcnth & VVCNTH_MASK) << 8) + (vvcntw & VVCNTW_MASK));

	wetuwn apb_vew_wes;
}

static int npcm_video_capwes(stwuct npcm_video *video, unsigned int how_wes,
			     unsigned int vewt_wes)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int wes, cap_wes;

	if (how_wes > MAX_WIDTH || vewt_wes > MAX_HEIGHT)
		wetuwn -EINVAW;

	wes = FIEWD_PWEP(VCD_CAP_WES_VEWT_WES, vewt_wes) |
	      FIEWD_PWEP(VCD_CAP_WES_HOW_WES, how_wes);

	wegmap_wwite(vcd, VCD_CAP_WES, wes);
	wegmap_wead(vcd, VCD_CAP_WES, &cap_wes);

	if (cap_wes != wes)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void npcm_video_vcd_ip_weset(stwuct npcm_video *video)
{
	/*
	 * Aftew wesetting a moduwe and cweawing the weset bit, it shouwd wait
	 * at weast 10 us befowe accessing the moduwe.
	 */
	weset_contwow_assewt(video->weset);
	usweep_wange(10, 20);
	weset_contwow_deassewt(video->weset);
	usweep_wange(10, 20);
}

static void npcm_video_vcd_state_machine_weset(stwuct npcm_video *video)
{
	stwuct wegmap *vcd = video->vcd_wegmap;

	wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_VCDE, 0);
	wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_IDBC, 0);
	wegmap_update_bits(vcd, VCD_CMD, VCD_CMD_WST, VCD_CMD_WST);

	/*
	 * VCD_CMD_WST wiww weset VCD intewnaw state machines and cweaw FIFOs,
	 * it shouwd wait at weast 800 us fow the weset opewations compweted.
	 */
	usweep_wange(800, 1000);

	wegmap_wwite(vcd, VCD_STAT, VCD_STAT_CWEAW);
	wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_VCDE, VCD_MODE_VCDE);
	wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_IDBC, VCD_MODE_IDBC);
}

static void npcm_video_gfx_weset(stwuct npcm_video *video)
{
	stwuct wegmap *gcw = video->gcw_wegmap;

	wegmap_update_bits(gcw, INTCW2, INTCW2_GIWST2, INTCW2_GIWST2);
	npcm_video_vcd_state_machine_weset(video);
	wegmap_update_bits(gcw, INTCW2, INTCW2_GIWST2, 0);
}

static void npcm_video_kvm_bw(stwuct npcm_video *video, boow set_bw)
{
	stwuct wegmap *vcd = video->vcd_wegmap;

	if (set_bw || !npcm_video_is_mga(video))
		wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_KVM_BW_SET,
				   VCD_MODE_KVM_BW_SET);
	ewse
		wegmap_update_bits(vcd, VCD_MODE, VCD_MODE_KVM_BW_SET, 0);
}

static unsigned int npcm_video_pcwk(stwuct npcm_video *video)
{
	stwuct wegmap *gfxi = video->gfx_wegmap;
	unsigned int tmp, pwwfbdiv, pwwinotdiv, gpwwfbdiv;
	unsigned int gpwwfbdv109, gpwwfbdv8, gpwwindiv;
	unsigned int gpwwst_pwwotdiv1, gpwwst_pwwotdiv2;

	wegmap_wead(gfxi, GPWWST, &tmp);
	gpwwfbdv109 = FIEWD_GET(GPWWST_GPWWFBDV109, tmp);
	gpwwst_pwwotdiv1 = FIEWD_GET(GPWWST_PWWOTDIV1, tmp);
	gpwwst_pwwotdiv2 = FIEWD_GET(GPWWST_PWWOTDIV2, tmp);

	wegmap_wead(gfxi, GPWWINDIV, &tmp);
	gpwwfbdv8 = FIEWD_GET(GPWWINDIV_GPWWFBDV8, tmp);
	gpwwindiv = FIEWD_GET(GPWWINDIV_MASK, tmp);

	wegmap_wead(gfxi, GPWWFBDIV, &tmp);
	gpwwfbdiv = FIEWD_GET(GPWWFBDIV_MASK, tmp);

	pwwfbdiv = (512 * gpwwfbdv109 + 256 * gpwwfbdv8 + gpwwfbdiv);
	pwwinotdiv = (gpwwindiv * gpwwst_pwwotdiv1 * gpwwst_pwwotdiv2);
	if (pwwfbdiv == 0 || pwwinotdiv == 0)
		wetuwn 0;

	wetuwn ((pwwfbdiv * 25000) / pwwinotdiv) * 1000;
}

static unsigned int npcm_video_get_bpp(stwuct npcm_video *video)
{
	const stwuct npcm_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < NUM_FOWMATS; k++) {
		fmt = &npcm_fmt_wist[k];
		if (fmt->fouwcc == video->pix_fmt.pixewfowmat)
			bweak;
	}

	wetuwn fmt->bpp;
}

/*
 * Pitch must be a powew of 2, >= winebytes,
 * at weast 512, and no mowe than 4096.
 */
static void npcm_video_set_winepitch(stwuct npcm_video *video,
				     unsigned int winebytes)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int pitch = MIN_WP;

	whiwe ((pitch < winebytes) && (pitch < MAX_WP))
		pitch *= 2;

	wegmap_wwite(vcd, VCD_FB_WP, FIEWD_PWEP(VCD_FBA_WP, pitch) |
		     FIEWD_PWEP(VCD_FBB_WP, pitch));
}

static unsigned int npcm_video_get_winepitch(stwuct npcm_video *video)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int winepitch;

	wegmap_wead(vcd, VCD_FB_WP, &winepitch);
	wetuwn FIEWD_GET(VCD_FBA_WP, winepitch);
}

static void npcm_video_command(stwuct npcm_video *video, unsigned int vawue)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int cmd;

	wegmap_wwite(vcd, VCD_STAT, VCD_STAT_CWEAW);
	wegmap_wead(vcd, VCD_CMD, &cmd);
	cmd |= FIEWD_PWEP(VCD_CMD_OPEWATION, vawue);

	wegmap_wwite(vcd, VCD_CMD, cmd);
	wegmap_update_bits(vcd, VCD_CMD, VCD_CMD_GO, VCD_CMD_GO);
	video->op_cmd = vawue;
}

static void npcm_video_init_weg(stwuct npcm_video *video)
{
	stwuct wegmap *gcw = video->gcw_wegmap, *vcd = video->vcd_wegmap;

	/* Sewects Data Enabwe */
	wegmap_update_bits(gcw, INTCW, INTCW_DEHS, 0);

	/* Enabwe dispway of KVM GFX and access to memowy */
	wegmap_update_bits(gcw, INTCW, INTCW_GFXIFDIS, 0);

	/* Active Vewticaw/Howizontaw Countews Weset */
	wegmap_update_bits(gcw, INTCW2, INTCW2_GIHCWST | INTCW2_GIVCWST,
			   INTCW2_GIHCWST | INTCW2_GIVCWST);

	/* Weset video moduwes */
	npcm_video_vcd_ip_weset(video);
	npcm_video_gfx_weset(video);

	/* Set the FIFO thweshowds */
	wegmap_wwite(vcd, VCD_FIFO, VCD_FIFO_TH);

	/* Set WCHG timew */
	wegmap_wwite(vcd, VCD_WCHG, FIEWD_PWEP(VCD_WCHG_TIM_PWSCW, 0xf) |
		     FIEWD_PWEP(VCD_WCHG_IG_CHG0, 0x3));

	/* Set video mode */
	wegmap_wwite(vcd, VCD_MODE, VCD_MODE_VCDE | VCD_MODE_CM565 |
		     VCD_MODE_IDBC | VCD_MODE_KVM_BW_SET);
}

static int npcm_video_stawt_fwame(stwuct npcm_video *video)
{
	stwuct npcm_video_buffew *buf;
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int vaw;
	int wet;

	if (video->v4w2_input_status) {
		dev_dbg(video->dev, "No video signaw; skip captuwe fwame\n");
		wetuwn 0;
	}

	wet = wegmap_wead_poww_timeout(vcd, VCD_STAT, vaw, !(vaw & VCD_STAT_BUSY),
				       1000, VCD_TIMEOUT_US);
	if (wet) {
		dev_eww(video->dev, "Wait fow VCD_STAT_BUSY timeout\n");
		wetuwn -EBUSY;
	}

	mutex_wock(&video->buffew_wock);
	buf = wist_fiwst_entwy_ow_nuww(&video->buffews,
				       stwuct npcm_video_buffew, wink);
	if (!buf) {
		mutex_unwock(&video->buffew_wock);
		dev_dbg(video->dev, "No empty buffews; skip captuwe fwame\n");
		wetuwn 0;
	}

	set_bit(VIDEO_CAPTUWING, &video->fwags);
	mutex_unwock(&video->buffew_wock);

	npcm_video_vcd_state_machine_weset(video);

	wegmap_wead(vcd, VCD_HOW_AC_TIM, &vaw);
	wegmap_update_bits(vcd, VCD_HOW_AC_WST, VCD_HOW_AC_WAST,
			   FIEWD_GET(VCD_HOW_AC_TIME, vaw));

	wegmap_wead(vcd, VCD_VEW_HI_TIM, &vaw);
	wegmap_update_bits(vcd, VCD_VEW_HI_WST, VCD_VEW_HI_WAST,
			   FIEWD_GET(VCD_VEW_HI_TIME, vaw));

	wegmap_update_bits(vcd, VCD_INTE, VCD_INTE_DONE_IE | VCD_INTE_IFOT_IE |
			   VCD_INTE_IFOW_IE | VCD_INTE_HAC_IE | VCD_INTE_VHT_IE,
			   VCD_INTE_DONE_IE | VCD_INTE_IFOT_IE | VCD_INTE_IFOW_IE |
			   VCD_INTE_HAC_IE | VCD_INTE_VHT_IE);

	npcm_video_command(video, video->ctww_cmd);

	wetuwn 0;
}

static void npcm_video_bufs_done(stwuct npcm_video *video,
				 enum vb2_buffew_state state)
{
	stwuct npcm_video_buffew *buf;

	mutex_wock(&video->buffew_wock);
	wist_fow_each_entwy(buf, &video->buffews, wink)
		vb2_buffew_done(&buf->vb.vb2_buf, state);

	INIT_WIST_HEAD(&video->buffews);
	mutex_unwock(&video->buffew_wock);
}

static void npcm_video_get_diff_wect(stwuct npcm_video *video, unsigned int index)
{
	unsigned int width = video->active_timings.width;
	unsigned int height = video->active_timings.height;

	if (video->op_cmd != VCD_CMD_OPEWATION_CAPTUWE) {
		video->wect_cnt = 0;
		npcm_video_get_wect_wist(video, index);
		video->wect[index] = video->wect_cnt;
	} ewse {
		video->wect[index] = npcm_video_add_wect(video, index, 0, 0,
							 width, height);
	}
}

static void npcm_video_detect_wesowution(stwuct npcm_video *video)
{
	stwuct v4w2_bt_timings *act = &video->active_timings;
	stwuct v4w2_bt_timings *det = &video->detected_timings;
	stwuct wegmap *gfxi = video->gfx_wegmap;
	unsigned int dispst;

	video->v4w2_input_status = V4W2_IN_ST_NO_SIGNAW;
	det->width = npcm_video_hwes(video);
	det->height = npcm_video_vwes(video);

	if (act->width != det->width || act->height != det->height) {
		dev_dbg(video->dev, "Wesowution changed\n");

		if (npcm_video_hwes(video) > 0 && npcm_video_vwes(video) > 0) {
			if (test_bit(VIDEO_STWEAMING, &video->fwags)) {
				/*
				 * Wait fow wesowution is avaiwabwe,
				 * and it is awso captuwed by host.
				 */
				do {
					mdeway(100);
					wegmap_wead(gfxi, DISPST, &dispst);
				} whiwe (npcm_video_vwes(video) < 100 ||
					 npcm_video_pcwk(video) == 0 ||
					 (dispst & DISPST_HSCWOFF));
			}

			det->width = npcm_video_hwes(video);
			det->height = npcm_video_vwes(video);
			det->pixewcwock = npcm_video_pcwk(video);
		}

		cweaw_bit(VIDEO_WES_CHANGING, &video->fwags);
	}

	if (det->width && det->height)
		video->v4w2_input_status = 0;

	dev_dbg(video->dev, "Got wesowution[%dx%d] -> [%dx%d], status %d\n",
		act->width, act->height, det->width, det->height,
		video->v4w2_input_status);
}

static int npcm_video_set_wesowution(stwuct npcm_video *video,
				     stwuct v4w2_bt_timings *timing)
{
	stwuct wegmap *vcd = video->vcd_wegmap;
	unsigned int mode;

	if (npcm_video_capwes(video, timing->width, timing->height)) {
		dev_eww(video->dev, "Faiwed to set VCD_CAP_WES\n");
		wetuwn -EINVAW;
	}

	video->active_timings = *timing;
	video->bytespewpixew = npcm_video_get_bpp(video);
	npcm_video_set_winepitch(video, timing->width * video->bytespewpixew);
	video->bytespewwine = npcm_video_get_winepitch(video);
	video->pix_fmt.width = timing->width ? timing->width : MIN_WIDTH;
	video->pix_fmt.height = timing->height ? timing->height : MIN_HEIGHT;
	video->pix_fmt.sizeimage = video->pix_fmt.width * video->pix_fmt.height *
				   video->bytespewpixew;
	video->pix_fmt.bytespewwine = video->bytespewwine;

	npcm_video_kvm_bw(video, timing->pixewcwock > VCD_KVM_BW_PCWK);
	npcm_video_gfx_weset(video);
	wegmap_wead(vcd, VCD_MODE, &mode);

	dev_dbg(video->dev, "VCD mode = 0x%x, %s mode\n", mode,
		npcm_video_is_mga(video) ? "Hi Wes" : "VGA");

	dev_dbg(video->dev,
		"Digitaw mode: %d x %d x %d, pixewcwock %wwd, bytespewwine %d\n",
		timing->width, timing->height, video->bytespewpixew,
		timing->pixewcwock, video->bytespewwine);

	wetuwn 0;
}

static void npcm_video_stawt(stwuct npcm_video *video)
{
	npcm_video_init_weg(video);

	if (!npcm_video_awwoc_fb(video, &video->swc)) {
		dev_eww(video->dev, "Faiwed to awwocate VCD fwame buffew\n");
		wetuwn;
	}

	npcm_video_detect_wesowution(video);
	if (npcm_video_set_wesowution(video, &video->detected_timings)) {
		dev_eww(video->dev, "Faiwed to set wesowution\n");
		wetuwn;
	}

	/* Set fwame buffew physicaw addwess */
	wegmap_wwite(video->vcd_wegmap, VCD_FBA_ADW, video->swc.dma);
	wegmap_wwite(video->vcd_wegmap, VCD_FBB_ADW, video->swc.dma);

	if (video->ece.enabwe && atomic_inc_wetuwn(&video->ece.cwients) == 1) {
		npcm_video_ece_ip_weset(video);
		npcm_video_ece_ctww_weset(video);
		npcm_video_ece_set_fb_addw(video, video->swc.dma);
		npcm_video_ece_set_wp(video, video->bytespewwine);

		dev_dbg(video->dev, "ECE open: cwient %d\n",
			atomic_wead(&video->ece.cwients));
	}
}

static void npcm_video_stop(stwuct npcm_video *video)
{
	stwuct wegmap *vcd = video->vcd_wegmap;

	set_bit(VIDEO_STOPPED, &video->fwags);

	wegmap_wwite(vcd, VCD_INTE, 0);
	wegmap_wwite(vcd, VCD_MODE, 0);
	wegmap_wwite(vcd, VCD_WCHG, 0);
	wegmap_wwite(vcd, VCD_STAT, VCD_STAT_CWEAW);

	if (video->swc.size)
		npcm_video_fwee_fb(video, &video->swc);

	npcm_video_fwee_diff_tabwe(video);
	video->v4w2_input_status = V4W2_IN_ST_NO_SIGNAW;
	video->fwags = 0;
	video->ctww_cmd = VCD_CMD_OPEWATION_CAPTUWE;

	if (video->ece.enabwe && atomic_dec_wetuwn(&video->ece.cwients) == 0) {
		npcm_video_ece_stop(video);
		dev_dbg(video->dev, "ECE cwose: cwient %d\n",
			atomic_wead(&video->ece.cwients));
	}
}

static unsigned int npcm_video_waw(stwuct npcm_video *video, int index, void *addw)
{
	unsigned int width = video->active_timings.width;
	unsigned int height = video->active_timings.height;
	unsigned int i, wen, offset, bytes = 0;

	video->wect[index] = npcm_video_add_wect(video, index, 0, 0, width, height);

	fow (i = 0; i < height; i++) {
		wen = width * video->bytespewpixew;
		offset = i * video->bytespewwine;

		memcpy(addw + bytes, video->swc.viwt + offset, wen);
		bytes += wen;
	}

	wetuwn bytes;
}

static unsigned int npcm_video_hextiwe(stwuct npcm_video *video, unsigned int index,
				       unsigned int dma_addw, void *vaddw)
{
	stwuct wect_wist *wect_wist;
	stwuct v4w2_wect *wect;
	unsigned int offset, wen, bytes = 0;

	npcm_video_ece_ctww_weset(video);
	npcm_video_ece_cweaw_wect_offset(video);
	npcm_video_ece_set_fb_addw(video, video->swc.dma);

	/* Set base addwess of encoded data to video buffew */
	npcm_video_ece_set_enc_dba(video, dma_addw);

	npcm_video_ece_set_wp(video, video->bytespewwine);
	npcm_video_get_diff_wect(video, index);

	wist_fow_each_entwy(wect_wist, &video->wist[index], wist) {
		wect = &wect_wist->cwip.c;
		offset = npcm_video_ece_wead_wect_offset(video);
		npcm_video_ece_enc_wect(video, wect->weft, wect->top,
					wect->width, wect->height);

		wen = npcm_video_ece_get_ed_size(video, offset, vaddw);
		npcm_video_ece_pwepend_wect_headew(vaddw + offset,
						   wect->weft, wect->top,
						   wect->width, wect->height);
		bytes += wen;
	}

	wetuwn bytes;
}

static iwqwetuwn_t npcm_video_iwq(int iwq, void *awg)
{
	stwuct npcm_video *video = awg;
	stwuct wegmap *vcd = video->vcd_wegmap;
	stwuct npcm_video_buffew *buf;
	unsigned int index, size, status, fmt;
	dma_addw_t dma_addw;
	void *addw;
	static const stwuct v4w2_event ev = {
		.type = V4W2_EVENT_SOUWCE_CHANGE,
		.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION,
	};

	wegmap_wead(vcd, VCD_STAT, &status);
	dev_dbg(video->dev, "VCD iwq status 0x%x\n", status);

	wegmap_wwite(vcd, VCD_STAT, VCD_STAT_CWEAW);

	if (test_bit(VIDEO_STOPPED, &video->fwags) ||
	    !test_bit(VIDEO_STWEAMING, &video->fwags))
		wetuwn IWQ_NONE;

	if (status & VCD_STAT_DONE) {
		wegmap_wwite(vcd, VCD_INTE, 0);
		mutex_wock(&video->buffew_wock);
		cweaw_bit(VIDEO_CAPTUWING, &video->fwags);
		buf = wist_fiwst_entwy_ow_nuww(&video->buffews,
					       stwuct npcm_video_buffew, wink);
		if (!buf) {
			mutex_unwock(&video->buffew_wock);
			wetuwn IWQ_NONE;
		}

		addw = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
		index = buf->vb.vb2_buf.index;
		fmt = video->pix_fmt.pixewfowmat;

		switch (fmt) {
		case V4W2_PIX_FMT_WGB565:
			size = npcm_video_waw(video, index, addw);
			bweak;
		case V4W2_PIX_FMT_HEXTIWE:
			dma_addw = vb2_dma_contig_pwane_dma_addw(&buf->vb.vb2_buf, 0);
			size = npcm_video_hextiwe(video, index, dma_addw, addw);
			bweak;
		defauwt:
			mutex_unwock(&video->buffew_wock);
			wetuwn IWQ_NONE;
		}

		vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, size);
		buf->vb.vb2_buf.timestamp = ktime_get_ns();
		buf->vb.sequence = video->sequence++;
		buf->vb.fiewd = V4W2_FIEWD_NONE;

		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		wist_dew(&buf->wink);
		mutex_unwock(&video->buffew_wock);

		if (npcm_video_stawt_fwame(video))
			dev_eww(video->dev, "Faiwed to captuwe next fwame\n");
	}

	/* Wesowution changed */
	if (status & VCD_STAT_VHT_CHG || status & VCD_STAT_HAC_CHG) {
		if (!test_bit(VIDEO_WES_CHANGING, &video->fwags)) {
			set_bit(VIDEO_WES_CHANGING, &video->fwags);

			vb2_queue_ewwow(&video->queue);
			v4w2_event_queue(&video->vdev, &ev);
		}
	}

	if (status & VCD_STAT_IFOW || status & VCD_STAT_IFOT) {
		dev_wawn(video->dev, "VCD FIFO ovewwun ow ovew thweshowds\n");
		if (npcm_video_stawt_fwame(video))
			dev_eww(video->dev, "Faiwed to wecovew fwom FIFO ovewwun\n");
	}

	wetuwn IWQ_HANDWED;
}

static int npcm_video_quewycap(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, DEVICE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "NPCM Video Engine", sizeof(cap->cawd));

	wetuwn 0;
}

static int npcm_video_enum_fowmat(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fmtdesc *f)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	const stwuct npcm_fmt *fmt;

	if (f->index >= NUM_FOWMATS)
		wetuwn -EINVAW;

	fmt = &npcm_fmt_wist[f->index];
	if (fmt->fouwcc == V4W2_PIX_FMT_HEXTIWE && !video->ece.enabwe)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->fouwcc;
	wetuwn 0;
}

static int npcm_video_twy_fowmat(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	const stwuct npcm_fmt *fmt;

	fmt = npcm_video_find_fowmat(f);

	/* If fowmat not found ow HEXTIWE not suppowted, use WGB565 as defauwt */
	if (!fmt || (fmt->fouwcc == V4W2_PIX_FMT_HEXTIWE && !video->ece.enabwe))
		f->fmt.pix.pixewfowmat = npcm_fmt_wist[0].fouwcc;

	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SWGB;
	f->fmt.pix.quantization = V4W2_QUANTIZATION_FUWW_WANGE;
	f->fmt.pix.width = video->pix_fmt.width;
	f->fmt.pix.height = video->pix_fmt.height;
	f->fmt.pix.bytespewwine = video->bytespewwine;
	f->fmt.pix.sizeimage = video->pix_fmt.sizeimage;

	wetuwn 0;
}

static int npcm_video_get_fowmat(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);

	f->fmt.pix = video->pix_fmt;
	wetuwn 0;
}

static int npcm_video_set_fowmat(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	int wet;

	wet = npcm_video_twy_fowmat(fiwe, fh, f);
	if (wet)
		wetuwn wet;

	if (vb2_is_busy(&video->queue)) {
		dev_eww(video->dev, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	video->pix_fmt.pixewfowmat = f->fmt.pix.pixewfowmat;
	wetuwn 0;
}

static int npcm_video_enum_input(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_input *inp)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);

	if (inp->index)
		wetuwn -EINVAW;

	stwscpy(inp->name, "Host VGA captuwe", sizeof(inp->name));
	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->capabiwities = V4W2_IN_CAP_DV_TIMINGS;
	inp->status = video->v4w2_input_status;

	wetuwn 0;
}

static int npcm_video_get_input(stwuct fiwe *fiwe, void *fh, unsigned int *i)
{
	*i = 0;

	wetuwn 0;
}

static int npcm_video_set_input(stwuct fiwe *fiwe, void *fh, unsigned int i)
{
	if (i)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int npcm_video_set_dv_timings(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_dv_timings *timings)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	int wc;

	if (timings->bt.width == video->active_timings.width &&
	    timings->bt.height == video->active_timings.height)
		wetuwn 0;

	if (vb2_is_busy(&video->queue)) {
		dev_eww(video->dev, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	wc = npcm_video_set_wesowution(video, &timings->bt);
	if (wc)
		wetuwn wc;

	timings->type = V4W2_DV_BT_656_1120;

	wetuwn 0;
}

static int npcm_video_get_dv_timings(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_dv_timings *timings)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);

	timings->type = V4W2_DV_BT_656_1120;
	timings->bt = video->active_timings;

	wetuwn 0;
}

static int npcm_video_quewy_dv_timings(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_dv_timings *timings)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);

	npcm_video_detect_wesowution(video);
	timings->type = V4W2_DV_BT_656_1120;
	timings->bt = video->detected_timings;

	wetuwn video->v4w2_input_status ? -ENOWINK : 0;
}

static int npcm_video_enum_dv_timings(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_enum_dv_timings *timings)
{
	wetuwn v4w2_enum_dv_timings_cap(timings, &npcm_video_timings_cap,
					NUWW, NUWW);
}

static int npcm_video_dv_timings_cap(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_dv_timings_cap *cap)
{
	*cap = npcm_video_timings_cap;

	wetuwn 0;
}

static int npcm_video_sub_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_swc_change_event_subscwibe(fh, sub);
	}

	wetuwn v4w2_ctww_subscwibe_event(fh, sub);
}

static const stwuct v4w2_ioctw_ops npcm_video_ioctws = {
	.vidioc_quewycap = npcm_video_quewycap,

	.vidioc_enum_fmt_vid_cap = npcm_video_enum_fowmat,
	.vidioc_g_fmt_vid_cap = npcm_video_get_fowmat,
	.vidioc_s_fmt_vid_cap = npcm_video_set_fowmat,
	.vidioc_twy_fmt_vid_cap = npcm_video_twy_fowmat,

	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,

	.vidioc_enum_input = npcm_video_enum_input,
	.vidioc_g_input = npcm_video_get_input,
	.vidioc_s_input = npcm_video_set_input,

	.vidioc_s_dv_timings = npcm_video_set_dv_timings,
	.vidioc_g_dv_timings = npcm_video_get_dv_timings,
	.vidioc_quewy_dv_timings = npcm_video_quewy_dv_timings,
	.vidioc_enum_dv_timings = npcm_video_enum_dv_timings,
	.vidioc_dv_timings_cap = npcm_video_dv_timings_cap,

	.vidioc_subscwibe_event = npcm_video_sub_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static int npcm_video_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct npcm_video *video = containew_of(ctww->handwew, stwuct npcm_video,
						ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_NPCM_CAPTUWE_MODE:
		if (ctww->vaw == V4W2_NPCM_CAPTUWE_MODE_COMPWETE)
			video->ctww_cmd = VCD_CMD_OPEWATION_CAPTUWE;
		ewse if (ctww->vaw == V4W2_NPCM_CAPTUWE_MODE_DIFF)
			video->ctww_cmd = VCD_CMD_OPEWATION_COMPAWE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops npcm_video_ctww_ops = {
	.s_ctww = npcm_video_set_ctww,
};

static const chaw * const npcm_ctww_captuwe_mode_menu[] = {
	"COMPWETE",
	"DIFF",
	NUWW,
};

static const stwuct v4w2_ctww_config npcm_ctww_captuwe_mode = {
	.ops = &npcm_video_ctww_ops,
	.id = V4W2_CID_NPCM_CAPTUWE_MODE,
	.name = "NPCM Video Captuwe Mode",
	.type = V4W2_CTWW_TYPE_MENU,
	.min = 0,
	.max = V4W2_NPCM_CAPTUWE_MODE_DIFF,
	.def = 0,
	.qmenu = npcm_ctww_captuwe_mode_menu,
};

/*
 * This contwow vawue is set when a buffew is dequeued by usewspace, i.e. in
 * npcm_video_buf_finish function.
 */
static const stwuct v4w2_ctww_config npcm_ctww_wect_count = {
	.id = V4W2_CID_NPCM_WECT_COUNT,
	.name = "NPCM Hextiwe Wectangwe Count",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.min = 0,
	.max = (MAX_WIDTH / WECT_W) * (MAX_HEIGHT / WECT_H),
	.step = 1,
	.def = 0,
};

static int npcm_video_open(stwuct fiwe *fiwe)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	int wc;

	mutex_wock(&video->video_wock);
	wc = v4w2_fh_open(fiwe);
	if (wc) {
		mutex_unwock(&video->video_wock);
		wetuwn wc;
	}

	if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		npcm_video_stawt(video);

	mutex_unwock(&video->video_wock);
	wetuwn 0;
}

static int npcm_video_wewease(stwuct fiwe *fiwe)
{
	stwuct npcm_video *video = video_dwvdata(fiwe);
	int wc;

	mutex_wock(&video->video_wock);
	if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		npcm_video_stop(video);

	wc = _vb2_fop_wewease(fiwe, NUWW);

	mutex_unwock(&video->video_wock);
	wetuwn wc;
}

static const stwuct v4w2_fiwe_opewations npcm_video_v4w2_fops = {
	.ownew = THIS_MODUWE,
	.wead = vb2_fop_wead,
	.poww = vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = vb2_fop_mmap,
	.open = npcm_video_open,
	.wewease = npcm_video_wewease,
};

static int npcm_video_queue_setup(stwuct vb2_queue *q, unsigned int *num_buffews,
				  unsigned int *num_pwanes, unsigned int sizes[],
				  stwuct device *awwoc_devs[])
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(q);
	unsigned int i;

	if (*num_pwanes) {
		if (sizes[0] < video->pix_fmt.sizeimage)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	*num_pwanes = 1;
	sizes[0] = video->pix_fmt.sizeimage;

	fow (i = 0; i < VIDEO_MAX_FWAME; i++)
		INIT_WIST_HEAD(&video->wist[i]);

	wetuwn 0;
}

static int npcm_video_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);

	if (vb2_pwane_size(vb, 0) < video->pix_fmt.sizeimage)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int npcm_video_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(q);
	int wc;

	video->sequence = 0;
	wc = npcm_video_stawt_fwame(video);
	if (wc) {
		npcm_video_bufs_done(video, VB2_BUF_STATE_QUEUED);
		wetuwn wc;
	}

	set_bit(VIDEO_STWEAMING, &video->fwags);
	wetuwn 0;
}

static void npcm_video_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(q);
	stwuct wegmap *vcd = video->vcd_wegmap;

	cweaw_bit(VIDEO_STWEAMING, &video->fwags);
	wegmap_wwite(vcd, VCD_INTE, 0);
	wegmap_wwite(vcd, VCD_STAT, VCD_STAT_CWEAW);
	npcm_video_gfx_weset(video);
	npcm_video_bufs_done(video, VB2_BUF_STATE_EWWOW);
	video->ctww_cmd = VCD_CMD_OPEWATION_CAPTUWE;
	v4w2_ctww_s_ctww(video->wect_cnt_ctww, 0);
}

static void npcm_video_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct npcm_video_buffew *nvb = to_npcm_video_buffew(vbuf);
	boow empty;

	mutex_wock(&video->buffew_wock);
	empty = wist_empty(&video->buffews);
	wist_add_taiw(&nvb->wink, &video->buffews);
	mutex_unwock(&video->buffew_wock);

	if (test_bit(VIDEO_STWEAMING, &video->fwags) &&
	    !test_bit(VIDEO_CAPTUWING, &video->fwags) && empty) {
		if (npcm_video_stawt_fwame(video))
			dev_eww(video->dev, "Faiwed to captuwe next fwame\n");
	}
}

static void npcm_video_buf_finish(stwuct vb2_buffew *vb)
{
	stwuct npcm_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct wist_head *head, *pos, *nx;
	stwuct wect_wist *tmp;

	/*
	 * This cawwback is cawwed when the buffew is dequeued, so update
	 * V4W2_CID_NPCM_WECT_COUNT contwow vawue with the numbew of wectangwes
	 * in this buffew and fwee associated wect_wist.
	 */
	if (test_bit(VIDEO_STWEAMING, &video->fwags)) {
		v4w2_ctww_s_ctww(video->wect_cnt_ctww, video->wect[vb->index]);

		head = &video->wist[vb->index];
		wist_fow_each_safe(pos, nx, head) {
			tmp = wist_entwy(pos, stwuct wect_wist, wist);
			wist_dew(&tmp->wist);
			kfwee(tmp);
		}
	}
}

static const stwuct wegmap_config npcm_video_wegmap_cfg = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= VCD_FIFO,
};

static const stwuct wegmap_config npcm_video_ece_wegmap_cfg = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= ECE_HEX_WECT_OFFSET,
};

static const stwuct vb2_ops npcm_video_vb2_ops = {
	.queue_setup = npcm_video_queue_setup,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.buf_pwepawe = npcm_video_buf_pwepawe,
	.buf_finish = npcm_video_buf_finish,
	.stawt_stweaming = npcm_video_stawt_stweaming,
	.stop_stweaming = npcm_video_stop_stweaming,
	.buf_queue =  npcm_video_buf_queue,
};

static int npcm_video_setup_video(stwuct npcm_video *video)
{
	stwuct v4w2_device *v4w2_dev = &video->v4w2_dev;
	stwuct video_device *vdev = &video->vdev;
	stwuct vb2_queue *vbq = &video->queue;
	int wc;

	if (video->ece.enabwe)
		video->pix_fmt.pixewfowmat = V4W2_PIX_FMT_HEXTIWE;
	ewse
		video->pix_fmt.pixewfowmat = V4W2_PIX_FMT_WGB565;

	video->pix_fmt.fiewd = V4W2_FIEWD_NONE;
	video->pix_fmt.cowowspace = V4W2_COWOWSPACE_SWGB;
	video->pix_fmt.quantization = V4W2_QUANTIZATION_FUWW_WANGE;
	video->v4w2_input_status = V4W2_IN_ST_NO_SIGNAW;

	wc = v4w2_device_wegistew(video->dev, v4w2_dev);
	if (wc) {
		dev_eww(video->dev, "Faiwed to wegistew v4w2 device\n");
		wetuwn wc;
	}

	v4w2_ctww_handwew_init(&video->ctww_handwew, 2);
	v4w2_ctww_new_custom(&video->ctww_handwew, &npcm_ctww_captuwe_mode, NUWW);
	video->wect_cnt_ctww = v4w2_ctww_new_custom(&video->ctww_handwew,
						    &npcm_ctww_wect_count, NUWW);
	if (video->ctww_handwew.ewwow) {
		dev_eww(video->dev, "Faiwed to init contwows: %d\n",
			video->ctww_handwew.ewwow);

		wc = video->ctww_handwew.ewwow;
		goto wew_ctww_handwew;
	}
	v4w2_dev->ctww_handwew = &video->ctww_handwew;

	vbq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	vbq->io_modes = VB2_MMAP | VB2_DMABUF;
	vbq->dev = v4w2_dev->dev;
	vbq->wock = &video->video_wock;
	vbq->ops = &npcm_video_vb2_ops;
	vbq->mem_ops = &vb2_dma_contig_memops;
	vbq->dwv_pwiv = video;
	vbq->buf_stwuct_size = sizeof(stwuct npcm_video_buffew);
	vbq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	vbq->min_queued_buffews = 3;

	wc = vb2_queue_init(vbq);
	if (wc) {
		dev_eww(video->dev, "Faiwed to init vb2 queue\n");
		goto wew_ctww_handwew;
	}
	vdev->queue = vbq;
	vdev->fops = &npcm_video_v4w2_fops;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
	vdev->v4w2_dev = v4w2_dev;
	stwscpy(vdev->name, DEVICE_NAME, sizeof(vdev->name));
	vdev->vfw_type = VFW_TYPE_VIDEO;
	vdev->vfw_diw = VFW_DIW_WX;
	vdev->wewease = video_device_wewease_empty;
	vdev->ioctw_ops = &npcm_video_ioctws;
	vdev->wock = &video->video_wock;

	video_set_dwvdata(vdev, video);
	wc = video_wegistew_device(vdev, VFW_TYPE_VIDEO, 0);
	if (wc) {
		dev_eww(video->dev, "Faiwed to wegistew video device\n");
		goto wew_vb_queue;
	}

	wetuwn 0;

wew_vb_queue:
	vb2_queue_wewease(vbq);
wew_ctww_handwew:
	v4w2_ctww_handwew_fwee(&video->ctww_handwew);
	v4w2_device_unwegistew(v4w2_dev);

	wetuwn wc;
}

static int npcm_video_ece_init(stwuct npcm_video *video)
{
	stwuct device *dev = video->dev;
	stwuct device_node *ece_node;
	stwuct pwatfowm_device *ece_pdev;
	void __iomem *wegs;

	ece_node = of_pawse_phandwe(video->dev->of_node, "nuvoton,ece", 0);
	if (!ece_node) {
		dev_eww(dev, "Faiwed to get ECE phandwe in DTS\n");
		wetuwn -ENODEV;
	}

	video->ece.enabwe = of_device_is_avaiwabwe(ece_node);

	if (video->ece.enabwe) {
		dev_info(dev, "Suppowt HEXTIWE pixew fowmat\n");

		ece_pdev = of_find_device_by_node(ece_node);
		if (IS_EWW(ece_pdev)) {
			dev_eww(dev, "Faiwed to find ECE device\n");
			wetuwn PTW_EWW(ece_pdev);
		}
		of_node_put(ece_node);

		wegs = devm_pwatfowm_iowemap_wesouwce(ece_pdev, 0);
		if (IS_EWW(wegs)) {
			dev_eww(dev, "Faiwed to pawse ECE weg in DTS\n");
			wetuwn PTW_EWW(wegs);
		}

		video->ece.wegmap = devm_wegmap_init_mmio(dev, wegs,
							  &npcm_video_ece_wegmap_cfg);
		if (IS_EWW(video->ece.wegmap)) {
			dev_eww(dev, "Faiwed to initiawize ECE wegmap\n");
			wetuwn PTW_EWW(video->ece.wegmap);
		}

		video->ece.weset = devm_weset_contwow_get(&ece_pdev->dev, NUWW);
		if (IS_EWW(video->ece.weset)) {
			dev_eww(dev, "Faiwed to get ECE weset contwow in DTS\n");
			wetuwn PTW_EWW(video->ece.weset);
		}
	}

	wetuwn 0;
}

static int npcm_video_init(stwuct npcm_video *video)
{
	stwuct device *dev = video->dev;
	int iwq, wc;

	iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!iwq) {
		dev_eww(dev, "Faiwed to find VCD IWQ\n");
		wetuwn -ENODEV;
	}

	wc = devm_wequest_thweaded_iwq(dev, iwq, NUWW, npcm_video_iwq,
				       IWQF_ONESHOT, DEVICE_NAME, video);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wequest IWQ %d\n", iwq);
		wetuwn wc;
	}

	of_wesewved_mem_device_init(dev);
	wc = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wc) {
		dev_eww(dev, "Faiwed to set DMA mask\n");
		of_wesewved_mem_device_wewease(dev);
	}

	wc = npcm_video_ece_init(video);
	if (wc) {
		dev_eww(dev, "Faiwed to initiawize ECE\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int npcm_video_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_video *video = kzawwoc(sizeof(*video), GFP_KEWNEW);
	int wc;
	void __iomem *wegs;

	if (!video)
		wetuwn -ENOMEM;

	video->dev = &pdev->dev;
	mutex_init(&video->video_wock);
	mutex_init(&video->buffew_wock);
	INIT_WIST_HEAD(&video->buffews);

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		dev_eww(&pdev->dev, "Faiwed to pawse VCD weg in DTS\n");
		wetuwn PTW_EWW(wegs);
	}

	video->vcd_wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
						  &npcm_video_wegmap_cfg);
	if (IS_EWW(video->vcd_wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to initiawize VCD wegmap\n");
		wetuwn PTW_EWW(video->vcd_wegmap);
	}

	video->weset = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(video->weset)) {
		dev_eww(&pdev->dev, "Faiwed to get VCD weset contwow in DTS\n");
		wetuwn PTW_EWW(video->weset);
	}

	video->gcw_wegmap = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							    "nuvoton,sysgcw");
	if (IS_EWW(video->gcw_wegmap))
		wetuwn PTW_EWW(video->gcw_wegmap);

	video->gfx_wegmap = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							    "nuvoton,sysgfxi");
	if (IS_EWW(video->gfx_wegmap))
		wetuwn PTW_EWW(video->gfx_wegmap);

	wc = npcm_video_init(video);
	if (wc)
		wetuwn wc;

	wc = npcm_video_setup_video(video);
	if (wc)
		wetuwn wc;

	dev_info(video->dev, "NPCM video dwivew pwobed\n");
	wetuwn 0;
}

static int npcm_video_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct npcm_video *video = to_npcm_video(v4w2_dev);

	video_unwegistew_device(&video->vdev);
	vb2_queue_wewease(&video->queue);
	v4w2_ctww_handwew_fwee(&video->ctww_handwew);
	v4w2_device_unwegistew(v4w2_dev);
	if (video->ece.enabwe)
		npcm_video_ece_stop(video);
	of_wesewved_mem_device_wewease(dev);

	wetuwn 0;
}

static const stwuct of_device_id npcm_video_match[] = {
	{ .compatibwe = "nuvoton,npcm750-vcd" },
	{ .compatibwe = "nuvoton,npcm845-vcd" },
	{},
};

MODUWE_DEVICE_TABWE(of, npcm_video_match);

static stwuct pwatfowm_dwivew npcm_video_dwivew = {
	.dwivew = {
		.name = DEVICE_NAME,
		.of_match_tabwe = npcm_video_match,
	},
	.pwobe = npcm_video_pwobe,
	.wemove = npcm_video_wemove,
};

moduwe_pwatfowm_dwivew(npcm_video_dwivew);

MODUWE_AUTHOW("Joseph Wiu <kwwiu@nuvoton.com>");
MODUWE_AUTHOW("Mawvin Win <kfwin@nuvoton.com>");
MODUWE_DESCWIPTION("Dwivew fow Nuvoton NPCM Video Captuwe/Encode Engine");
MODUWE_WICENSE("GPW v2");
