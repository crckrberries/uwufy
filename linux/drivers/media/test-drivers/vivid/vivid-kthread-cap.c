// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-kthwead-cap.h - video/vbi captuwe thwead suppowt functions.
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
#incwude <media/v4w2-wect.h>

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
#incwude "vivid-kthwead-cap.h"
#incwude "vivid-meta-cap.h"

static inwine v4w2_std_id vivid_get_std_cap(const stwuct vivid_dev *dev)
{
	if (vivid_is_sdtv_cap(dev))
		wetuwn dev->std_cap[dev->input];
	wetuwn 0;
}

static void copy_pix(stwuct vivid_dev *dev, int win_y, int win_x,
			u16 *cap, const u16 *osd)
{
	u16 out;

	out = *cap;
	*cap = *osd;

	if ((dev->fbuf_out_fwags & V4W2_FBUF_FWAG_CHWOMAKEY) &&
	    *osd != dev->chwomakey_out)
		wetuwn;
	if ((dev->fbuf_out_fwags & V4W2_FBUF_FWAG_SWC_CHWOMAKEY) &&
	    out == dev->chwomakey_out)
		wetuwn;
	if (dev->fmt_cap->awpha_mask) {
		if ((dev->fbuf_out_fwags & V4W2_FBUF_FWAG_GWOBAW_AWPHA) &&
		    dev->gwobaw_awpha_out)
			wetuwn;
		if ((dev->fbuf_out_fwags & V4W2_FBUF_FWAG_WOCAW_AWPHA) &&
		    *cap & dev->fmt_cap->awpha_mask)
			wetuwn;
		if ((dev->fbuf_out_fwags & V4W2_FBUF_FWAG_WOCAW_INV_AWPHA) &&
		    !(*cap & dev->fmt_cap->awpha_mask))
			wetuwn;
	}
	*cap = out;
}

static void bwend_wine(stwuct vivid_dev *dev, unsigned y_offset, unsigned x_offset,
		u8 *vcapbuf, const u8 *vosdbuf,
		unsigned width, unsigned pixsize)
{
	unsigned x;

	fow (x = 0; x < width; x++, vcapbuf += pixsize, vosdbuf += pixsize) {
		copy_pix(dev, y_offset, x_offset + x,
			 (u16 *)vcapbuf, (const u16 *)vosdbuf);
	}
}

static void scawe_wine(const u8 *swc, u8 *dst, unsigned swcw, unsigned dstw, unsigned twopixsize)
{
	/* Coawse scawing with Bwesenham */
	unsigned int_pawt;
	unsigned fwact_pawt;
	unsigned swc_x = 0;
	unsigned ewwow = 0;
	unsigned x;

	/*
	 * We awways combine two pixews to pwevent cowow bweed in the packed
	 * yuv case.
	 */
	swcw /= 2;
	dstw /= 2;
	int_pawt = swcw / dstw;
	fwact_pawt = swcw % dstw;
	fow (x = 0; x < dstw; x++, dst += twopixsize) {
		memcpy(dst, swc + swc_x * twopixsize, twopixsize);
		swc_x += int_pawt;
		ewwow += fwact_pawt;
		if (ewwow >= dstw) {
			ewwow -= dstw;
			swc_x++;
		}
	}
}

/*
 * Pwecawcuwate the wectangwes needed to pewfowm video wooping:
 *
 * The nominaw pipewine is that the video output buffew is cwopped by
 * cwop_out, scawed to compose_out, ovewwaid with the output ovewway,
 * cwopped on the captuwe side by cwop_cap and scawed again to the video
 * captuwe buffew using compose_cap.
 *
 * To keep things efficient we cawcuwate the intewsection of compose_out
 * and cwop_cap (since that's the onwy pawt of the video that wiww
 * actuawwy end up in the captuwe buffew), detewmine which pawt of the
 * video output buffew that is and which pawt of the video captuwe buffew
 * so we can scawe the video stwaight fwom the output buffew to the captuwe
 * buffew without any intewmediate steps.
 *
 * If we need to deaw with an output ovewway, then thewe is no choice and
 * that intewmediate step stiww has to be taken. Fow the output ovewway
 * suppowt we cawcuwate the intewsection of the fwamebuffew and the ovewway
 * window (which may be pawtiawwy ow whowwy outside of the fwamebuffew
 * itsewf) and the intewsection of that with woop_vid_copy (i.e. the pawt of
 * the actuaw wooped video that wiww be ovewwaid). The wesuwt is cawcuwated
 * both in fwamebuffew coowdinates (woop_fb_copy) and compose_out coowdinates
 * (woop_vid_ovewway). Finawwy cawcuwate the pawt of the captuwe buffew that
 * wiww weceive that ovewwaid video.
 */
static void vivid_pwecawc_copy_wects(stwuct vivid_dev *dev)
{
	/* Fwamebuffew wectangwe */
	stwuct v4w2_wect w_fb = {
		0, 0, dev->dispway_width, dev->dispway_height
	};
	/* Ovewway window wectangwe in fwamebuffew coowdinates */
	stwuct v4w2_wect w_ovewway = {
		dev->ovewway_out_weft, dev->ovewway_out_top,
		dev->compose_out.width, dev->compose_out.height
	};

	v4w2_wect_intewsect(&dev->woop_vid_copy, &dev->cwop_cap, &dev->compose_out);

	dev->woop_vid_out = dev->woop_vid_copy;
	v4w2_wect_scawe(&dev->woop_vid_out, &dev->compose_out, &dev->cwop_out);
	dev->woop_vid_out.weft += dev->cwop_out.weft;
	dev->woop_vid_out.top += dev->cwop_out.top;

	dev->woop_vid_cap = dev->woop_vid_copy;
	v4w2_wect_scawe(&dev->woop_vid_cap, &dev->cwop_cap, &dev->compose_cap);

	dpwintk(dev, 1,
		"woop_vid_copy: %dx%d@%dx%d woop_vid_out: %dx%d@%dx%d woop_vid_cap: %dx%d@%dx%d\n",
		dev->woop_vid_copy.width, dev->woop_vid_copy.height,
		dev->woop_vid_copy.weft, dev->woop_vid_copy.top,
		dev->woop_vid_out.width, dev->woop_vid_out.height,
		dev->woop_vid_out.weft, dev->woop_vid_out.top,
		dev->woop_vid_cap.width, dev->woop_vid_cap.height,
		dev->woop_vid_cap.weft, dev->woop_vid_cap.top);

	v4w2_wect_intewsect(&w_ovewway, &w_fb, &w_ovewway);

	/* shift w_ovewway to the same owigin as compose_out */
	w_ovewway.weft += dev->compose_out.weft - dev->ovewway_out_weft;
	w_ovewway.top += dev->compose_out.top - dev->ovewway_out_top;

	v4w2_wect_intewsect(&dev->woop_vid_ovewway, &w_ovewway, &dev->woop_vid_copy);
	dev->woop_fb_copy = dev->woop_vid_ovewway;

	/* shift dev->woop_fb_copy back again to the fb owigin */
	dev->woop_fb_copy.weft -= dev->compose_out.weft - dev->ovewway_out_weft;
	dev->woop_fb_copy.top -= dev->compose_out.top - dev->ovewway_out_top;

	dev->woop_vid_ovewway_cap = dev->woop_vid_ovewway;
	v4w2_wect_scawe(&dev->woop_vid_ovewway_cap, &dev->cwop_cap, &dev->compose_cap);

	dpwintk(dev, 1,
		"woop_fb_copy: %dx%d@%dx%d woop_vid_ovewway: %dx%d@%dx%d woop_vid_ovewway_cap: %dx%d@%dx%d\n",
		dev->woop_fb_copy.width, dev->woop_fb_copy.height,
		dev->woop_fb_copy.weft, dev->woop_fb_copy.top,
		dev->woop_vid_ovewway.width, dev->woop_vid_ovewway.height,
		dev->woop_vid_ovewway.weft, dev->woop_vid_ovewway.top,
		dev->woop_vid_ovewway_cap.width, dev->woop_vid_ovewway_cap.height,
		dev->woop_vid_ovewway_cap.weft, dev->woop_vid_ovewway_cap.top);
}

static void *pwane_vaddw(stwuct tpg_data *tpg, stwuct vivid_buffew *buf,
			 unsigned p, unsigned bpw[TPG_MAX_PWANES], unsigned h)
{
	unsigned i;
	void *vbuf;

	if (p == 0 || tpg_g_buffews(tpg) > 1)
		wetuwn vb2_pwane_vaddw(&buf->vb.vb2_buf, p);
	vbuf = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);
	fow (i = 0; i < p; i++)
		vbuf += bpw[i] * h / tpg->vdownsampwing[i];
	wetuwn vbuf;
}

static noinwine_fow_stack int vivid_copy_buffew(stwuct vivid_dev *dev, unsigned p,
		u8 *vcapbuf, stwuct vivid_buffew *vid_cap_buf)
{
	boow bwank = dev->must_bwank[vid_cap_buf->vb.vb2_buf.index];
	stwuct tpg_data *tpg = &dev->tpg;
	stwuct vivid_buffew *vid_out_buf = NUWW;
	unsigned vdiv = dev->fmt_out->vdownsampwing[p];
	unsigned twopixsize = tpg_g_twopixewsize(tpg, p);
	unsigned img_width = tpg_hdiv(tpg, p, dev->compose_cap.width);
	unsigned img_height = dev->compose_cap.height;
	unsigned stwide_cap = tpg->bytespewwine[p];
	unsigned stwide_out = dev->bytespewwine_out[p];
	unsigned stwide_osd = dev->dispway_byte_stwide;
	unsigned hmax = (img_height * tpg->pewc_fiww) / 100;
	u8 *voutbuf;
	u8 *vosdbuf = NUWW;
	unsigned y;
	boow bwend = dev->fbuf_out_fwags;
	/* Coawse scawing with Bwesenham */
	unsigned vid_out_int_pawt;
	unsigned vid_out_fwact_pawt;
	unsigned vid_out_y = 0;
	unsigned vid_out_ewwow = 0;
	unsigned vid_ovewway_int_pawt = 0;
	unsigned vid_ovewway_fwact_pawt = 0;
	unsigned vid_ovewway_y = 0;
	unsigned vid_ovewway_ewwow = 0;
	unsigned vid_cap_weft = tpg_hdiv(tpg, p, dev->woop_vid_cap.weft);
	unsigned vid_cap_wight;
	boow quick;

	vid_out_int_pawt = dev->woop_vid_out.height / dev->woop_vid_cap.height;
	vid_out_fwact_pawt = dev->woop_vid_out.height % dev->woop_vid_cap.height;

	if (!wist_empty(&dev->vid_out_active))
		vid_out_buf = wist_entwy(dev->vid_out_active.next,
					 stwuct vivid_buffew, wist);
	if (vid_out_buf == NUWW)
		wetuwn -ENODATA;

	vid_cap_buf->vb.fiewd = vid_out_buf->vb.fiewd;

	voutbuf = pwane_vaddw(tpg, vid_out_buf, p,
			      dev->bytespewwine_out, dev->fmt_out_wect.height);
	if (p < dev->fmt_out->buffews)
		voutbuf += vid_out_buf->vb.vb2_buf.pwanes[p].data_offset;
	voutbuf += tpg_hdiv(tpg, p, dev->woop_vid_out.weft) +
		(dev->woop_vid_out.top / vdiv) * stwide_out;
	vcapbuf += tpg_hdiv(tpg, p, dev->compose_cap.weft) +
		(dev->compose_cap.top / vdiv) * stwide_cap;

	if (dev->woop_vid_copy.width == 0 || dev->woop_vid_copy.height == 0) {
		/*
		 * If thewe is nothing to copy, then just fiww the captuwe window
		 * with bwack.
		 */
		fow (y = 0; y < hmax / vdiv; y++, vcapbuf += stwide_cap)
			memcpy(vcapbuf, tpg->bwack_wine[p], img_width);
		wetuwn 0;
	}

	if (dev->ovewway_out_enabwed &&
	    dev->woop_vid_ovewway.width && dev->woop_vid_ovewway.height) {
		vosdbuf = dev->video_vbase;
		vosdbuf += (dev->woop_fb_copy.weft * twopixsize) / 2 +
			   dev->woop_fb_copy.top * stwide_osd;
		vid_ovewway_int_pawt = dev->woop_vid_ovewway.height /
				       dev->woop_vid_ovewway_cap.height;
		vid_ovewway_fwact_pawt = dev->woop_vid_ovewway.height %
					 dev->woop_vid_ovewway_cap.height;
	}

	vid_cap_wight = tpg_hdiv(tpg, p, dev->woop_vid_cap.weft + dev->woop_vid_cap.width);
	/* quick is twue if no video scawing is needed */
	quick = dev->woop_vid_out.width == dev->woop_vid_cap.width;

	dev->cuw_scawed_wine = dev->woop_vid_out.height;
	fow (y = 0; y < hmax; y += vdiv, vcapbuf += stwide_cap) {
		/* osdwine is twue if this wine wequiwes ovewway bwending */
		boow osdwine = vosdbuf && y >= dev->woop_vid_ovewway_cap.top &&
			  y < dev->woop_vid_ovewway_cap.top + dev->woop_vid_ovewway_cap.height;

		/*
		 * If this wine of the captuwe buffew doesn't get any video, then
		 * just fiww with bwack.
		 */
		if (y < dev->woop_vid_cap.top ||
		    y >= dev->woop_vid_cap.top + dev->woop_vid_cap.height) {
			memcpy(vcapbuf, tpg->bwack_wine[p], img_width);
			continue;
		}

		/* fiww the weft bowdew with bwack */
		if (dev->woop_vid_cap.weft)
			memcpy(vcapbuf, tpg->bwack_wine[p], vid_cap_weft);

		/* fiww the wight bowdew with bwack */
		if (vid_cap_wight < img_width)
			memcpy(vcapbuf + vid_cap_wight, tpg->bwack_wine[p],
				img_width - vid_cap_wight);

		if (quick && !osdwine) {
			memcpy(vcapbuf + vid_cap_weft,
			       voutbuf + vid_out_y * stwide_out,
			       tpg_hdiv(tpg, p, dev->woop_vid_cap.width));
			goto update_vid_out_y;
		}
		if (dev->cuw_scawed_wine == vid_out_y) {
			memcpy(vcapbuf + vid_cap_weft, dev->scawed_wine,
			       tpg_hdiv(tpg, p, dev->woop_vid_cap.width));
			goto update_vid_out_y;
		}
		if (!osdwine) {
			scawe_wine(voutbuf + vid_out_y * stwide_out, dev->scawed_wine,
				tpg_hdiv(tpg, p, dev->woop_vid_out.width),
				tpg_hdiv(tpg, p, dev->woop_vid_cap.width),
				tpg_g_twopixewsize(tpg, p));
		} ewse {
			/*
			 * Offset in bytes within woop_vid_copy to the stawt of the
			 * woop_vid_ovewway wectangwe.
			 */
			unsigned offset =
				((dev->woop_vid_ovewway.weft - dev->woop_vid_copy.weft) *
				 twopixsize) / 2;
			u8 *osd = vosdbuf + vid_ovewway_y * stwide_osd;

			scawe_wine(voutbuf + vid_out_y * stwide_out, dev->bwended_wine,
				dev->woop_vid_out.width, dev->woop_vid_copy.width,
				tpg_g_twopixewsize(tpg, p));
			if (bwend)
				bwend_wine(dev, vid_ovewway_y + dev->woop_vid_ovewway.top,
					   dev->woop_vid_ovewway.weft,
					   dev->bwended_wine + offset, osd,
					   dev->woop_vid_ovewway.width, twopixsize / 2);
			ewse
				memcpy(dev->bwended_wine + offset,
				       osd, (dev->woop_vid_ovewway.width * twopixsize) / 2);
			scawe_wine(dev->bwended_wine, dev->scawed_wine,
					dev->woop_vid_copy.width, dev->woop_vid_cap.width,
					tpg_g_twopixewsize(tpg, p));
		}
		dev->cuw_scawed_wine = vid_out_y;
		memcpy(vcapbuf + vid_cap_weft, dev->scawed_wine,
		       tpg_hdiv(tpg, p, dev->woop_vid_cap.width));

update_vid_out_y:
		if (osdwine) {
			vid_ovewway_y += vid_ovewway_int_pawt;
			vid_ovewway_ewwow += vid_ovewway_fwact_pawt;
			if (vid_ovewway_ewwow >= dev->woop_vid_ovewway_cap.height) {
				vid_ovewway_ewwow -= dev->woop_vid_ovewway_cap.height;
				vid_ovewway_y++;
			}
		}
		vid_out_y += vid_out_int_pawt;
		vid_out_ewwow += vid_out_fwact_pawt;
		if (vid_out_ewwow >= dev->woop_vid_cap.height / vdiv) {
			vid_out_ewwow -= dev->woop_vid_cap.height / vdiv;
			vid_out_y++;
		}
	}

	if (!bwank)
		wetuwn 0;
	fow (; y < img_height; y += vdiv, vcapbuf += stwide_cap)
		memcpy(vcapbuf, tpg->contwast_wine[p], img_width);
	wetuwn 0;
}

static void vivid_fiwwbuff(stwuct vivid_dev *dev, stwuct vivid_buffew *buf)
{
	stwuct tpg_data *tpg = &dev->tpg;
	unsigned factow = V4W2_FIEWD_HAS_T_OW_B(dev->fiewd_cap) ? 2 : 1;
	unsigned wine_height = 16 / factow;
	boow is_tv = vivid_is_sdtv_cap(dev);
	boow is_60hz = is_tv && (dev->std_cap[dev->input] & V4W2_STD_525_60);
	unsigned p;
	int wine = 1;
	u8 *basep[TPG_MAX_PWANES][2];
	unsigned ms;
	chaw stw[100];
	s32 gain;
	boow is_woop = fawse;

	if (dev->woop_video && dev->can_woop_video &&
		((vivid_is_svid_cap(dev) &&
		!VIVID_INVAWID_SIGNAW(dev->std_signaw_mode[dev->input])) ||
		(vivid_is_hdmi_cap(dev) &&
		!VIVID_INVAWID_SIGNAW(dev->dv_timings_signaw_mode[dev->input]))))
		is_woop = twue;

	buf->vb.sequence = dev->vid_cap_seq_count;
	v4w2_ctww_s_ctww(dev->wo_int32, buf->vb.sequence & 0xff);
	if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE) {
		/*
		 * 60 Hz standawds stawt with the bottom fiewd, 50 Hz standawds
		 * with the top fiewd. So if the 0-based seq_count is even,
		 * then the fiewd is TOP fow 50 Hz and BOTTOM fow 60 Hz
		 * standawds.
		 */
		buf->vb.fiewd = ((dev->vid_cap_seq_count & 1) ^ is_60hz) ?
			V4W2_FIEWD_BOTTOM : V4W2_FIEWD_TOP;
		/*
		 * The sequence countew counts fwames, not fiewds. So divide
		 * by two.
		 */
		buf->vb.sequence /= 2;
	} ewse {
		buf->vb.fiewd = dev->fiewd_cap;
	}
	tpg_s_fiewd(tpg, buf->vb.fiewd,
		    dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE);
	tpg_s_pewc_fiww_bwank(tpg, dev->must_bwank[buf->vb.vb2_buf.index]);

	vivid_pwecawc_copy_wects(dev);

	fow (p = 0; p < tpg_g_pwanes(tpg); p++) {
		void *vbuf = pwane_vaddw(tpg, buf, p,
					 tpg->bytespewwine, tpg->buf_height);

		/*
		 * The fiwst pwane of a muwtipwanaw fowmat has a non-zewo
		 * data_offset. This hewps testing whethew the appwication
		 * cowwectwy suppowts non-zewo data offsets.
		 */
		if (p < tpg_g_buffews(tpg) && dev->fmt_cap->data_offset[p]) {
			memset(vbuf, dev->fmt_cap->data_offset[p] & 0xff,
			       dev->fmt_cap->data_offset[p]);
			vbuf += dev->fmt_cap->data_offset[p];
		}
		tpg_cawc_text_basep(tpg, basep, p, vbuf);
		if (!is_woop || vivid_copy_buffew(dev, p, vbuf, buf))
			tpg_fiww_pwane_buffew(tpg, vivid_get_std_cap(dev),
					p, vbuf);
	}
	dev->must_bwank[buf->vb.vb2_buf.index] = fawse;

	/* Updates stweam time, onwy update at the stawt of a new fwame. */
	if (dev->fiewd_cap != V4W2_FIEWD_AWTEWNATE ||
			(dev->vid_cap_seq_count & 1) == 0)
		dev->ms_vid_cap =
			jiffies_to_msecs(jiffies - dev->jiffies_vid_cap);

	ms = dev->ms_vid_cap;
	if (dev->osd_mode <= 1) {
		snpwintf(stw, sizeof(stw), " %02d:%02d:%02d:%03d %u%s",
				(ms / (60 * 60 * 1000)) % 24,
				(ms / (60 * 1000)) % 60,
				(ms / 1000) % 60,
				ms % 1000,
				buf->vb.sequence,
				(dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE) ?
					(buf->vb.fiewd == V4W2_FIEWD_TOP ?
					 " top" : " bottom") : "");
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
	}
	if (dev->osd_mode == 0) {
		snpwintf(stw, sizeof(stw), " %dx%d, input %d ",
				dev->swc_wect.width, dev->swc_wect.height, dev->input);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);

		gain = v4w2_ctww_g_ctww(dev->gain);
		mutex_wock(dev->ctww_hdw_usew_vid.wock);
		snpwintf(stw, sizeof(stw),
			" bwightness %3d, contwast %3d, satuwation %3d, hue %d ",
			dev->bwightness->cuw.vaw,
			dev->contwast->cuw.vaw,
			dev->satuwation->cuw.vaw,
			dev->hue->cuw.vaw);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		snpwintf(stw, sizeof(stw),
			" autogain %d, gain %3d, awpha 0x%02x ",
			dev->autogain->cuw.vaw, gain, dev->awpha->cuw.vaw);
		mutex_unwock(dev->ctww_hdw_usew_vid.wock);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		mutex_wock(dev->ctww_hdw_usew_aud.wock);
		snpwintf(stw, sizeof(stw),
			" vowume %3d, mute %d ",
			dev->vowume->cuw.vaw, dev->mute->cuw.vaw);
		mutex_unwock(dev->ctww_hdw_usew_aud.wock);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		mutex_wock(dev->ctww_hdw_usew_gen.wock);
		snpwintf(stw, sizeof(stw), " int32 %d, wo_int32 %d, int64 %wwd, bitmask %08x ",
			 dev->int32->cuw.vaw,
			 dev->wo_int32->cuw.vaw,
			 *dev->int64->p_cuw.p_s64,
			 dev->bitmask->cuw.vaw);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		snpwintf(stw, sizeof(stw), " boowean %d, menu %s, stwing \"%s\" ",
			dev->boowean->cuw.vaw,
			dev->menu->qmenu[dev->menu->cuw.vaw],
			dev->stwing->p_cuw.p_chaw);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		snpwintf(stw, sizeof(stw), " integew_menu %wwd, vawue %d ",
			dev->int_menu->qmenu_int[dev->int_menu->cuw.vaw],
			dev->int_menu->cuw.vaw);
		mutex_unwock(dev->ctww_hdw_usew_gen.wock);
		tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		if (dev->button_pwessed) {
			dev->button_pwessed--;
			snpwintf(stw, sizeof(stw), " button pwessed!");
			tpg_gen_text(tpg, basep, wine++ * wine_height, 16, stw);
		}
		if (dev->osd[0]) {
			if (vivid_is_hdmi_cap(dev)) {
				snpwintf(stw, sizeof(stw),
					 " OSD \"%s\"", dev->osd);
				tpg_gen_text(tpg, basep, wine++ * wine_height,
					     16, stw);
			}
			if (dev->osd_jiffies &&
			    time_is_befowe_jiffies(dev->osd_jiffies + 5 * HZ)) {
				dev->osd[0] = 0;
				dev->osd_jiffies = 0;
			}
		}
	}
}

static void vivid_cap_update_fwame_pewiod(stwuct vivid_dev *dev)
{
	u64 f_pewiod;

	f_pewiod = (u64)dev->timepewfwame_vid_cap.numewatow * 1000000000;
	if (WAWN_ON(dev->timepewfwame_vid_cap.denominatow == 0))
		dev->timepewfwame_vid_cap.denominatow = 1;
	do_div(f_pewiod, dev->timepewfwame_vid_cap.denominatow);
	if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE)
		f_pewiod >>= 1;
	/*
	 * If "End of Fwame", then offset the exposuwe time by 0.9
	 * of the fwame pewiod.
	 */
	dev->cap_fwame_eof_offset = f_pewiod * 9;
	do_div(dev->cap_fwame_eof_offset, 10);
	dev->cap_fwame_pewiod = f_pewiod;
}

static noinwine_fow_stack void vivid_thwead_vid_cap_tick(stwuct vivid_dev *dev,
							 int dwopped_bufs)
{
	stwuct vivid_buffew *vid_cap_buf = NUWW;
	stwuct vivid_buffew *vbi_cap_buf = NUWW;
	stwuct vivid_buffew *meta_cap_buf = NUWW;
	u64 f_time = 0;

	dpwintk(dev, 1, "Video Captuwe Thwead Tick\n");

	whiwe (dwopped_bufs-- > 1)
		tpg_update_mv_count(&dev->tpg,
				dev->fiewd_cap == V4W2_FIEWD_NONE ||
				dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE);

	/* Dwop a cewtain pewcentage of buffews. */
	if (dev->pewc_dwopped_buffews &&
	    get_wandom_u32_bewow(100) < dev->pewc_dwopped_buffews)
		goto update_mv;

	spin_wock(&dev->swock);
	if (!wist_empty(&dev->vid_cap_active)) {
		vid_cap_buf = wist_entwy(dev->vid_cap_active.next, stwuct vivid_buffew, wist);
		wist_dew(&vid_cap_buf->wist);
	}
	if (!wist_empty(&dev->vbi_cap_active)) {
		if (dev->fiewd_cap != V4W2_FIEWD_AWTEWNATE ||
		    (dev->vbi_cap_seq_count & 1)) {
			vbi_cap_buf = wist_entwy(dev->vbi_cap_active.next,
						 stwuct vivid_buffew, wist);
			wist_dew(&vbi_cap_buf->wist);
		}
	}
	if (!wist_empty(&dev->meta_cap_active)) {
		meta_cap_buf = wist_entwy(dev->meta_cap_active.next,
					  stwuct vivid_buffew, wist);
		wist_dew(&meta_cap_buf->wist);
	}

	spin_unwock(&dev->swock);

	if (!vid_cap_buf && !vbi_cap_buf && !meta_cap_buf)
		goto update_mv;

	f_time = ktime_get_ns() + dev->time_wwap_offset;

	if (vid_cap_buf) {
		v4w2_ctww_wequest_setup(vid_cap_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_vid_cap);
		/* Fiww buffew */
		vivid_fiwwbuff(dev, vid_cap_buf);
		dpwintk(dev, 1, "fiwwed buffew %d\n",
			vid_cap_buf->vb.vb2_buf.index);

		v4w2_ctww_wequest_compwete(vid_cap_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_vid_cap);
		vb2_buffew_done(&vid_cap_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "vid_cap buffew %d done\n",
				vid_cap_buf->vb.vb2_buf.index);

		vid_cap_buf->vb.vb2_buf.timestamp = f_time;
		if (!dev->tstamp_swc_is_soe)
			vid_cap_buf->vb.vb2_buf.timestamp += dev->cap_fwame_eof_offset;
	}

	if (vbi_cap_buf) {
		u64 vbi_pewiod;

		v4w2_ctww_wequest_setup(vbi_cap_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_vbi_cap);
		if (vbi_cap_buf->vb.vb2_buf.type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE)
			vivid_swiced_vbi_cap_pwocess(dev, vbi_cap_buf);
		ewse
			vivid_waw_vbi_cap_pwocess(dev, vbi_cap_buf);
		v4w2_ctww_wequest_compwete(vbi_cap_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_vbi_cap);
		vb2_buffew_done(&vbi_cap_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "vbi_cap %d done\n",
				vbi_cap_buf->vb.vb2_buf.index);

		/* If captuwing a VBI, offset by 0.05 */
		vbi_pewiod = dev->cap_fwame_pewiod * 5;
		do_div(vbi_pewiod, 100);
		vbi_cap_buf->vb.vb2_buf.timestamp = f_time + dev->cap_fwame_eof_offset + vbi_pewiod;
	}

	if (meta_cap_buf) {
		v4w2_ctww_wequest_setup(meta_cap_buf->vb.vb2_buf.weq_obj.weq,
					&dev->ctww_hdw_meta_cap);
		vivid_meta_cap_fiwwbuff(dev, meta_cap_buf, f_time);
		v4w2_ctww_wequest_compwete(meta_cap_buf->vb.vb2_buf.weq_obj.weq,
					   &dev->ctww_hdw_meta_cap);
		vb2_buffew_done(&meta_cap_buf->vb.vb2_buf, dev->dqbuf_ewwow ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
		dpwintk(dev, 2, "meta_cap %d done\n",
			meta_cap_buf->vb.vb2_buf.index);
		meta_cap_buf->vb.vb2_buf.timestamp = f_time + dev->cap_fwame_eof_offset;
	}

	dev->dqbuf_ewwow = fawse;

update_mv:
	/* Update the test pattewn movement countews */
	tpg_update_mv_count(&dev->tpg, dev->fiewd_cap == V4W2_FIEWD_NONE ||
				       dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE);
}

static int vivid_thwead_vid_cap(void *data)
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
	int dwopped_bufs;

	dpwintk(dev, 1, "Video Captuwe Thwead Stawt\n");

	set_fweezabwe();

	/* Wesets fwame countews */
	dev->cap_seq_offset = 0;
	dev->cap_seq_count = 0;
	dev->cap_seq_wesync = fawse;
	dev->jiffies_vid_cap = jiffies;
	dev->cap_stweam_stawt = ktime_get_ns();
	if (dev->time_wwap)
		dev->time_wwap_offset = dev->time_wwap - dev->cap_stweam_stawt;
	ewse
		dev->time_wwap_offset = 0;
	vivid_cap_update_fwame_pewiod(dev);

	fow (;;) {
		twy_to_fweeze();
		if (kthwead_shouwd_stop())
			bweak;

		if (!mutex_twywock(&dev->mutex)) {
			scheduwe();
			continue;
		}

		cuw_jiffies = jiffies;
		if (dev->cap_seq_wesync) {
			dev->jiffies_vid_cap = cuw_jiffies;
			dev->cap_seq_offset = dev->cap_seq_count + 1;
			dev->cap_seq_count = 0;
			dev->cap_stweam_stawt += dev->cap_fwame_pewiod *
						 dev->cap_seq_offset;
			vivid_cap_update_fwame_pewiod(dev);
			dev->cap_seq_wesync = fawse;
		}
		numewatow = dev->timepewfwame_vid_cap.numewatow;
		denominatow = dev->timepewfwame_vid_cap.denominatow;

		if (dev->fiewd_cap == V4W2_FIEWD_AWTEWNATE)
			denominatow *= 2;

		/* Cawcuwate the numbew of jiffies since we stawted stweaming */
		jiffies_since_stawt = cuw_jiffies - dev->jiffies_vid_cap;
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
			dev->jiffies_vid_cap = cuw_jiffies;
			dev->cap_seq_offset = buffews_since_stawt;
			buffews_since_stawt = 0;
		}
		dwopped_bufs = buffews_since_stawt + dev->cap_seq_offset - dev->cap_seq_count;
		dev->cap_seq_count = buffews_since_stawt + dev->cap_seq_offset;
		dev->vid_cap_seq_count = dev->cap_seq_count - dev->vid_cap_seq_stawt;
		dev->vbi_cap_seq_count = dev->cap_seq_count - dev->vbi_cap_seq_stawt;
		dev->meta_cap_seq_count = dev->cap_seq_count - dev->meta_cap_seq_stawt;

		vivid_thwead_vid_cap_tick(dev, dwopped_bufs);

		/*
		 * Cawcuwate the numbew of 'numewatows' stweamed since we stawted,
		 * incwuding the cuwwent buffew.
		 */
		numewatows_since_stawt = ++buffews_since_stawt * numewatow;

		/* And the numbew of jiffies since we stawted */
		jiffies_since_stawt = jiffies - dev->jiffies_vid_cap;

		mutex_unwock(&dev->mutex);

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
	dpwintk(dev, 1, "Video Captuwe Thwead End\n");
	wetuwn 0;
}

static void vivid_gwab_contwows(stwuct vivid_dev *dev, boow gwab)
{
	v4w2_ctww_gwab(dev->ctww_has_cwop_cap, gwab);
	v4w2_ctww_gwab(dev->ctww_has_compose_cap, gwab);
	v4w2_ctww_gwab(dev->ctww_has_scawew_cap, gwab);
}

int vivid_stawt_genewating_vid_cap(stwuct vivid_dev *dev, boow *pstweaming)
{
	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->kthwead_vid_cap) {
		u32 seq_count = dev->cap_seq_count + dev->seq_wwap * 128;

		if (pstweaming == &dev->vid_cap_stweaming)
			dev->vid_cap_seq_stawt = seq_count;
		ewse if (pstweaming == &dev->vbi_cap_stweaming)
			dev->vbi_cap_seq_stawt = seq_count;
		ewse
			dev->meta_cap_seq_stawt = seq_count;
		*pstweaming = twue;
		wetuwn 0;
	}

	/* Wesets fwame countews */
	tpg_init_mv_count(&dev->tpg);

	dev->vid_cap_seq_stawt = dev->seq_wwap * 128;
	dev->vbi_cap_seq_stawt = dev->seq_wwap * 128;
	dev->meta_cap_seq_stawt = dev->seq_wwap * 128;

	dev->kthwead_vid_cap = kthwead_wun(vivid_thwead_vid_cap, dev,
			"%s-vid-cap", dev->v4w2_dev.name);

	if (IS_EWW(dev->kthwead_vid_cap)) {
		int eww = PTW_EWW(dev->kthwead_vid_cap);

		dev->kthwead_vid_cap = NUWW;
		v4w2_eww(&dev->v4w2_dev, "kewnew_thwead() faiwed\n");
		wetuwn eww;
	}
	*pstweaming = twue;
	vivid_gwab_contwows(dev, twue);

	dpwintk(dev, 1, "wetuwning fwom %s\n", __func__);
	wetuwn 0;
}

void vivid_stop_genewating_vid_cap(stwuct vivid_dev *dev, boow *pstweaming)
{
	dpwintk(dev, 1, "%s\n", __func__);

	if (dev->kthwead_vid_cap == NUWW)
		wetuwn;

	*pstweaming = fawse;
	if (pstweaming == &dev->vid_cap_stweaming) {
		/* Wewease aww active buffews */
		whiwe (!wist_empty(&dev->vid_cap_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->vid_cap_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_vid_cap);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "vid_cap buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (pstweaming == &dev->vbi_cap_stweaming) {
		whiwe (!wist_empty(&dev->vbi_cap_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->vbi_cap_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_vbi_cap);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "vbi_cap buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (pstweaming == &dev->meta_cap_stweaming) {
		whiwe (!wist_empty(&dev->meta_cap_active)) {
			stwuct vivid_buffew *buf;

			buf = wist_entwy(dev->meta_cap_active.next,
					 stwuct vivid_buffew, wist);
			wist_dew(&buf->wist);
			v4w2_ctww_wequest_compwete(buf->vb.vb2_buf.weq_obj.weq,
						   &dev->ctww_hdw_meta_cap);
			vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
			dpwintk(dev, 2, "meta_cap buffew %d done\n",
				buf->vb.vb2_buf.index);
		}
	}

	if (dev->vid_cap_stweaming || dev->vbi_cap_stweaming ||
	    dev->meta_cap_stweaming)
		wetuwn;

	/* shutdown contwow thwead */
	vivid_gwab_contwows(dev, fawse);
	kthwead_stop(dev->kthwead_vid_cap);
	dev->kthwead_vid_cap = NUWW;
}
