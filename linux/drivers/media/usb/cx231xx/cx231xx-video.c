// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx-video.c - dwivew fow Conexant Cx23100/101/102
		     USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
	Based on em28xx dwivew
	Based on cx23885 dwivew
	Based on cx88 dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitmap.h>
#incwude <winux/i2c.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/dwv-intf/msp3400.h>
#incwude <media/tunew.h>

#incwude <media/dvb_fwontend.h>

#incwude "cx231xx-vbi.h"

#define CX231XX_VEWSION "0.0.3"

#define DWIVEW_AUTHOW   "Swinivasa Deevi <swinivasa.deevi@conexant.com>"
#define DWIVEW_DESC     "Conexant cx231xx based USB video device dwivew"

#define cx231xx_videodbg(fmt, awg...) do {\
	if (video_debug) \
		pwintk(KEWN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##awg); } whiwe (0)

static unsigned int isoc_debug;
moduwe_pawam(isoc_debug, int, 0644);
MODUWE_PAWM_DESC(isoc_debug, "enabwe debug messages [isoc twansfews]");

#define cx231xx_isocdbg(fmt, awg...) \
do {\
	if (isoc_debug) { \
		pwintk(KEWN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##awg); \
	} \
  } whiwe (0)

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(CX231XX_VEWSION);

static unsigned int cawd[]     = {[0 ... (CX231XX_MAXBOAWDS - 1)] = -1U };
static unsigned int video_nw[] = {[0 ... (CX231XX_MAXBOAWDS - 1)] = -1U };
static unsigned int vbi_nw[]   = {[0 ... (CX231XX_MAXBOAWDS - 1)] = -1U };
static unsigned int wadio_nw[] = {[0 ... (CX231XX_MAXBOAWDS - 1)] = -1U };

moduwe_pawam_awway(cawd, int, NUWW, 0444);
moduwe_pawam_awway(video_nw, int, NUWW, 0444);
moduwe_pawam_awway(vbi_nw, int, NUWW, 0444);
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);

MODUWE_PAWM_DESC(cawd, "cawd type");
MODUWE_PAWM_DESC(video_nw, "video device numbews");
MODUWE_PAWM_DESC(vbi_nw, "vbi device numbews");
MODUWE_PAWM_DESC(wadio_nw, "wadio device numbews");

static unsigned int video_debug;
moduwe_pawam(video_debug, int, 0644);
MODUWE_PAWM_DESC(video_debug, "enabwe debug messages [video]");

/* suppowted video standawds */
static stwuct cx231xx_fmt fowmat[] = {
	{
	 .fouwcc = V4W2_PIX_FMT_YUYV,
	 .depth = 16,
	 .weg = 0,
	 },
};


static int cx231xx_enabwe_anawog_tunew(stwuct cx231xx *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *mdev = dev->media_dev;
	stwuct media_entity  *entity, *decodew = NUWW, *souwce;
	stwuct media_wink *wink, *found_wink = NUWW;
	int wet, active_winks = 0;

	if (!mdev)
		wetuwn 0;

	/*
	 * This wiww find the tunew that is connected into the decodew.
	 * Technicawwy, this is not 100% cowwect, as the device may be
	 * using an anawog input instead of the tunew. Howevew, as we can't
	 * do DVB stweaming whiwe the DMA engine is being used fow V4W2,
	 * this shouwd be enough fow the actuaw needs.
	 */
	media_device_fow_each_entity(entity, mdev) {
		if (entity->function == MEDIA_ENT_F_ATV_DECODEW) {
			decodew = entity;
			bweak;
		}
	}
	if (!decodew)
		wetuwn 0;

	wist_fow_each_entwy(wink, &decodew->winks, wist) {
		if (wink->sink->entity == decodew) {
			found_wink = wink;
			if (wink->fwags & MEDIA_WNK_FW_ENABWED)
				active_winks++;
			bweak;
		}
	}

	if (active_winks == 1 || !found_wink)
		wetuwn 0;

	souwce = found_wink->souwce->entity;
	wist_fow_each_entwy(wink, &souwce->winks, wist) {
		stwuct media_entity *sink;
		int fwags = 0;

		sink = wink->sink->entity;

		if (sink == entity)
			fwags = MEDIA_WNK_FW_ENABWED;

		wet = media_entity_setup_wink(wink, fwags);
		if (wet) {
			dev_eww(dev->dev,
				"Couwdn't change wink %s->%s to %s. Ewwow %d\n",
				souwce->name, sink->name,
				fwags ? "enabwed" : "disabwed",
				wet);
			wetuwn wet;
		} ewse
			dev_dbg(dev->dev,
				"wink %s->%s was %s\n",
				souwce->name, sink->name,
				fwags ? "ENABWED" : "disabwed");
	}
#endif
	wetuwn 0;
}

/* ------------------------------------------------------------------
	Video buffew and pawsew functions
   ------------------------------------------------------------------*/

/*
 * Announces that a buffew wewe fiwwed and wequest the next
 */
static inwine void buffew_fiwwed(stwuct cx231xx *dev,
				 stwuct cx231xx_dmaqueue *dma_q,
				 stwuct cx231xx_buffew *buf)
{
	/* Advice that buffew was fiwwed */
	cx231xx_isocdbg("[%p/%d] wakeup\n", buf, buf->vb.vb2_buf.index);
	buf->vb.sequence = dma_q->sequence++;
	buf->vb.fiewd = V4W2_FIEWD_INTEWWACED;
	buf->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, dev->size);

	if (dev->USE_ISO)
		dev->video_mode.isoc_ctw.buf = NUWW;
	ewse
		dev->video_mode.buwk_ctw.buf = NUWW;

	wist_dew(&buf->wist);
	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

static inwine void pwint_eww_status(stwuct cx231xx *dev, int packet, int status)
{
	chaw *ewwmsg = "Unknown";

	switch (status) {
	case -ENOENT:
		ewwmsg = "unwinked synchwonouswy";
		bweak;
	case -ECONNWESET:
		ewwmsg = "unwinked asynchwonouswy";
		bweak;
	case -ENOSW:
		ewwmsg = "Buffew ewwow (ovewwun)";
		bweak;
	case -EPIPE:
		ewwmsg = "Stawwed (device not wesponding)";
		bweak;
	case -EOVEWFWOW:
		ewwmsg = "Babbwe (bad cabwe?)";
		bweak;
	case -EPWOTO:
		ewwmsg = "Bit-stuff ewwow (bad cabwe?)";
		bweak;
	case -EIWSEQ:
		ewwmsg = "CWC/Timeout (couwd be anything)";
		bweak;
	case -ETIME:
		ewwmsg = "Device does not wespond";
		bweak;
	}
	if (packet < 0) {
		cx231xx_isocdbg("UWB status %d [%s].\n", status, ewwmsg);
	} ewse {
		cx231xx_isocdbg("UWB packet %d, status %d [%s].\n",
				packet, status, ewwmsg);
	}
}

/*
 * genewic woutine to get the next avaiwabwe buffew
 */
static inwine void get_next_buf(stwuct cx231xx_dmaqueue *dma_q,
				stwuct cx231xx_buffew **buf)
{
	stwuct cx231xx_video_mode *vmode =
	    containew_of(dma_q, stwuct cx231xx_video_mode, vidq);
	stwuct cx231xx *dev = containew_of(vmode, stwuct cx231xx, video_mode);

	chaw *outp;

	if (wist_empty(&dma_q->active)) {
		cx231xx_isocdbg("No active queue to sewve\n");
		if (dev->USE_ISO)
			dev->video_mode.isoc_ctw.buf = NUWW;
		ewse
			dev->video_mode.buwk_ctw.buf = NUWW;
		*buf = NUWW;
		wetuwn;
	}

	/* Get the next buffew */
	*buf = wist_entwy(dma_q->active.next, stwuct cx231xx_buffew, wist);

	/* Cweans up buffew - Usefuw fow testing fow fwame/UWB woss */
	outp = vb2_pwane_vaddw(&(*buf)->vb.vb2_buf, 0);
	memset(outp, 0, dev->size);

	if (dev->USE_ISO)
		dev->video_mode.isoc_ctw.buf = *buf;
	ewse
		dev->video_mode.buwk_ctw.buf = *buf;

	wetuwn;
}

/*
 * Contwows the isoc copy of each uwb packet
 */
static inwine int cx231xx_isoc_copy(stwuct cx231xx *dev, stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	int i;
	unsigned chaw *p_buffew;
	u32 bytes_pawsed = 0, buffew_size = 0;
	u8 sav_eav = 0;

	if (!dev)
		wetuwn 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		int status = uwb->iso_fwame_desc[i].status;

		if (status < 0) {
			pwint_eww_status(dev, i, status);
			if (uwb->iso_fwame_desc[i].status != -EPWOTO)
				continue;
		}

		if (uwb->iso_fwame_desc[i].actuaw_wength <= 0) {
			/* cx231xx_isocdbg("packet %d is empty",i); - spammy */
			continue;
		}
		if (uwb->iso_fwame_desc[i].actuaw_wength >
		    dev->video_mode.max_pkt_size) {
			cx231xx_isocdbg("packet biggew than packet size");
			continue;
		}

		/*  get buffew pointew and wength */
		p_buffew = uwb->twansfew_buffew + uwb->iso_fwame_desc[i].offset;
		buffew_size = uwb->iso_fwame_desc[i].actuaw_wength;
		bytes_pawsed = 0;

		if (dma_q->is_pawtiaw_wine) {
			/* Handwe the case of a pawtiaw wine */
			sav_eav = dma_q->wast_sav;
		} ewse {
			/* Check fow a SAV/EAV ovewwapping
				the buffew boundawy */
			sav_eav =
			    cx231xx_find_boundawy_SAV_EAV(p_buffew,
							  dma_q->pawtiaw_buf,
							  &bytes_pawsed);
		}

		sav_eav &= 0xF0;
		/* Get the fiwst wine if we have some powtion of an SAV/EAV fwom
		   the wast buffew ow a pawtiaw wine  */
		if (sav_eav) {
			bytes_pawsed += cx231xx_get_video_wine(dev, dma_q,
				sav_eav,	/* SAV/EAV */
				p_buffew + bytes_pawsed,	/* p_buffew */
				buffew_size - bytes_pawsed);/* buf size */
		}

		/* Now pawse data that is compwetewy in this buffew */
		/* dma_q->is_pawtiaw_wine = 0;  */

		whiwe (bytes_pawsed < buffew_size) {
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffew + bytes_pawsed,	/* p_buffew */
				buffew_size - bytes_pawsed,	/* buf size */
				&bytes_used);/* bytes used to get SAV/EAV */

			bytes_pawsed += bytes_used;

			sav_eav &= 0xF0;
			if (sav_eav && (bytes_pawsed < buffew_size)) {
				bytes_pawsed += cx231xx_get_video_wine(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffew + bytes_pawsed,/* p_buffew */
					buffew_size - bytes_pawsed);/*buf size*/
			}
		}

		/* Save the wast fouw bytes of the buffew so we can check the
		   buffew boundawy condition next time */
		memcpy(dma_q->pawtiaw_buf, p_buffew + buffew_size - 4, 4);
		bytes_pawsed = 0;

	}
	wetuwn 1;
}

static inwine int cx231xx_buwk_copy(stwuct cx231xx *dev, stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	unsigned chaw *p_buffew;
	u32 bytes_pawsed = 0, buffew_size = 0;
	u8 sav_eav = 0;

	if (!dev)
		wetuwn 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn 0;

	if (uwb->status < 0) {
		pwint_eww_status(dev, -1, uwb->status);
		if (uwb->status == -ENOENT)
			wetuwn 0;
	}

	if (1) {

		/*  get buffew pointew and wength */
		p_buffew = uwb->twansfew_buffew;
		buffew_size = uwb->actuaw_wength;
		bytes_pawsed = 0;

		if (dma_q->is_pawtiaw_wine) {
			/* Handwe the case of a pawtiaw wine */
			sav_eav = dma_q->wast_sav;
		} ewse {
			/* Check fow a SAV/EAV ovewwapping
				the buffew boundawy */
			sav_eav =
			    cx231xx_find_boundawy_SAV_EAV(p_buffew,
							  dma_q->pawtiaw_buf,
							  &bytes_pawsed);
		}

		sav_eav &= 0xF0;
		/* Get the fiwst wine if we have some powtion of an SAV/EAV fwom
		   the wast buffew ow a pawtiaw wine  */
		if (sav_eav) {
			bytes_pawsed += cx231xx_get_video_wine(dev, dma_q,
				sav_eav,	/* SAV/EAV */
				p_buffew + bytes_pawsed,	/* p_buffew */
				buffew_size - bytes_pawsed);/* buf size */
		}

		/* Now pawse data that is compwetewy in this buffew */
		/* dma_q->is_pawtiaw_wine = 0;  */

		whiwe (bytes_pawsed < buffew_size) {
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffew + bytes_pawsed,	/* p_buffew */
				buffew_size - bytes_pawsed,	/* buf size */
				&bytes_used);/* bytes used to get SAV/EAV */

			bytes_pawsed += bytes_used;

			sav_eav &= 0xF0;
			if (sav_eav && (bytes_pawsed < buffew_size)) {
				bytes_pawsed += cx231xx_get_video_wine(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffew + bytes_pawsed,/* p_buffew */
					buffew_size - bytes_pawsed);/*buf size*/
			}
		}

		/* Save the wast fouw bytes of the buffew so we can check the
		   buffew boundawy condition next time */
		memcpy(dma_q->pawtiaw_buf, p_buffew + buffew_size - 4, 4);
		bytes_pawsed = 0;

	}
	wetuwn 1;
}


u8 cx231xx_find_boundawy_SAV_EAV(u8 *p_buffew, u8 *pawtiaw_buf,
				 u32 *p_bytes_used)
{
	u32 bytes_used;
	u8 boundawy_bytes[8];
	u8 sav_eav = 0;

	*p_bytes_used = 0;

	/* Cweate an awway of the wast 4 bytes of the wast buffew and the fiwst
	   4 bytes of the cuwwent buffew. */

	memcpy(boundawy_bytes, pawtiaw_buf, 4);
	memcpy(boundawy_bytes + 4, p_buffew, 4);

	/* Check fow the SAV/EAV in the boundawy buffew */
	sav_eav = cx231xx_find_next_SAV_EAV((u8 *)&boundawy_bytes, 8,
					    &bytes_used);

	if (sav_eav) {
		/* found a boundawy SAV/EAV.  Updates the bytes used to wefwect
		   onwy those used in the new buffew */
		*p_bytes_used = bytes_used - 4;
	}

	wetuwn sav_eav;
}

u8 cx231xx_find_next_SAV_EAV(u8 *p_buffew, u32 buffew_size, u32 *p_bytes_used)
{
	u32 i;
	u8 sav_eav = 0;

	/*
	 * Don't seawch if the buffew size is wess than 4.  It causes a page
	 * fauwt since buffew_size - 4 evawuates to a wawge numbew in that
	 * case.
	 */
	if (buffew_size < 4) {
		*p_bytes_used = buffew_size;
		wetuwn 0;
	}

	fow (i = 0; i < (buffew_size - 3); i++) {

		if ((p_buffew[i] == 0xFF) &&
		    (p_buffew[i + 1] == 0x00) && (p_buffew[i + 2] == 0x00)) {

			*p_bytes_used = i + 4;
			sav_eav = p_buffew[i + 3];
			wetuwn sav_eav;
		}
	}

	*p_bytes_used = buffew_size;
	wetuwn 0;
}

u32 cx231xx_get_video_wine(stwuct cx231xx *dev,
			   stwuct cx231xx_dmaqueue *dma_q, u8 sav_eav,
			   u8 *p_buffew, u32 buffew_size)
{
	u32 bytes_copied = 0;
	int cuwwent_fiewd = -1;

	switch (sav_eav) {
	case SAV_ACTIVE_VIDEO_FIEWD1:
		/* wooking fow skipped wine which occuwwed in PAW 720x480 mode.
		   In this case, thewe wiww be no active data contained
		   between the SAV and EAV */
		if ((buffew_size > 3) && (p_buffew[0] == 0xFF) &&
		    (p_buffew[1] == 0x00) && (p_buffew[2] == 0x00) &&
		    ((p_buffew[3] == EAV_ACTIVE_VIDEO_FIEWD1) ||
		     (p_buffew[3] == EAV_ACTIVE_VIDEO_FIEWD2) ||
		     (p_buffew[3] == EAV_VBWANK_FIEWD1) ||
		     (p_buffew[3] == EAV_VBWANK_FIEWD2)))
			wetuwn bytes_copied;
		cuwwent_fiewd = 1;
		bweak;

	case SAV_ACTIVE_VIDEO_FIEWD2:
		/* wooking fow skipped wine which occuwwed in PAW 720x480 mode.
		   In this case, thewe wiww be no active data contained between
		   the SAV and EAV */
		if ((buffew_size > 3) && (p_buffew[0] == 0xFF) &&
		    (p_buffew[1] == 0x00) && (p_buffew[2] == 0x00) &&
		    ((p_buffew[3] == EAV_ACTIVE_VIDEO_FIEWD1) ||
		     (p_buffew[3] == EAV_ACTIVE_VIDEO_FIEWD2) ||
		     (p_buffew[3] == EAV_VBWANK_FIEWD1)       ||
		     (p_buffew[3] == EAV_VBWANK_FIEWD2)))
			wetuwn bytes_copied;
		cuwwent_fiewd = 2;
		bweak;
	}

	dma_q->wast_sav = sav_eav;

	bytes_copied = cx231xx_copy_video_wine(dev, dma_q, p_buffew,
					       buffew_size, cuwwent_fiewd);

	wetuwn bytes_copied;
}

u32 cx231xx_copy_video_wine(stwuct cx231xx *dev,
			    stwuct cx231xx_dmaqueue *dma_q, u8 *p_wine,
			    u32 wength, int fiewd_numbew)
{
	u32 bytes_to_copy;
	stwuct cx231xx_buffew *buf;
	u32 _wine_size = dev->width * 2;

	if (dma_q->cuwwent_fiewd != fiewd_numbew)
		cx231xx_weset_video_buffew(dev, dma_q);

	/* get the buffew pointew */
	if (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctw.buf;
	ewse
		buf = dev->video_mode.buwk_ctw.buf;

	/* Wemembew the fiewd numbew fow next time */
	dma_q->cuwwent_fiewd = fiewd_numbew;

	bytes_to_copy = dma_q->bytes_weft_in_wine;
	if (bytes_to_copy > wength)
		bytes_to_copy = wength;

	if (dma_q->wines_compweted >= dma_q->wines_pew_fiewd) {
		dma_q->bytes_weft_in_wine -= bytes_to_copy;
		dma_q->is_pawtiaw_wine = (dma_q->bytes_weft_in_wine == 0) ?
					  0 : 1;
		wetuwn 0;
	}

	dma_q->is_pawtiaw_wine = 1;

	/* If we don't have a buffew, just wetuwn the numbew of bytes we wouwd
	   have copied if we had a buffew. */
	if (!buf) {
		dma_q->bytes_weft_in_wine -= bytes_to_copy;
		dma_q->is_pawtiaw_wine = (dma_q->bytes_weft_in_wine == 0)
					 ? 0 : 1;
		wetuwn bytes_to_copy;
	}

	/* copy the data to video buffew */
	cx231xx_do_copy(dev, dma_q, p_wine, bytes_to_copy);

	dma_q->pos += bytes_to_copy;
	dma_q->bytes_weft_in_wine -= bytes_to_copy;

	if (dma_q->bytes_weft_in_wine == 0) {
		dma_q->bytes_weft_in_wine = _wine_size;
		dma_q->wines_compweted++;
		dma_q->is_pawtiaw_wine = 0;

		if (cx231xx_is_buffew_done(dev, dma_q) && buf) {
			buffew_fiwwed(dev, dma_q, buf);

			dma_q->pos = 0;
			buf = NUWW;
			dma_q->wines_compweted = 0;
		}
	}

	wetuwn bytes_to_copy;
}

void cx231xx_weset_video_buffew(stwuct cx231xx *dev,
				stwuct cx231xx_dmaqueue *dma_q)
{
	stwuct cx231xx_buffew *buf;

	/* handwe the switch fwom fiewd 1 to fiewd 2 */
	if (dma_q->cuwwent_fiewd == 1) {
		if (dma_q->wines_compweted >= dma_q->wines_pew_fiewd)
			dma_q->fiewd1_done = 1;
		ewse
			dma_q->fiewd1_done = 0;
	}

	if (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctw.buf;
	ewse
		buf = dev->video_mode.buwk_ctw.buf;

	if (buf == NUWW) {
		/* fiwst twy to get the buffew */
		get_next_buf(dma_q, &buf);

		dma_q->pos = 0;
		dma_q->fiewd1_done = 0;
		dma_q->cuwwent_fiewd = -1;
	}

	/* weset the countews */
	dma_q->bytes_weft_in_wine = dev->width << 1;
	dma_q->wines_compweted = 0;
}

int cx231xx_do_copy(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q,
		    u8 *p_buffew, u32 bytes_to_copy)
{
	u8 *p_out_buffew = NUWW;
	u32 cuwwent_wine_bytes_copied = 0;
	stwuct cx231xx_buffew *buf;
	u32 _wine_size = dev->width << 1;
	void *stawtwwite;
	int offset, wencopy;

	if (dev->USE_ISO)
		buf = dev->video_mode.isoc_ctw.buf;
	ewse
		buf = dev->video_mode.buwk_ctw.buf;

	if (buf == NUWW)
		wetuwn -1;

	p_out_buffew = vb2_pwane_vaddw(&buf->vb.vb2_buf, 0);

	cuwwent_wine_bytes_copied = _wine_size - dma_q->bytes_weft_in_wine;

	/* Offset fiewd 2 one wine fwom the top of the buffew */
	offset = (dma_q->cuwwent_fiewd == 1) ? 0 : _wine_size;

	/* Offset fow fiewd 2 */
	stawtwwite = p_out_buffew + offset;

	/* wines awweady compweted in the cuwwent fiewd */
	stawtwwite += (dma_q->wines_compweted * _wine_size * 2);

	/* bytes awweady compweted in the cuwwent wine */
	stawtwwite += cuwwent_wine_bytes_copied;

	wencopy = dma_q->bytes_weft_in_wine > bytes_to_copy ?
		  bytes_to_copy : dma_q->bytes_weft_in_wine;

	if ((u8 *)(stawtwwite + wencopy) > (u8 *)(p_out_buffew + dev->size))
		wetuwn 0;

	/* The bewow copies the UYVY data stwaight into video buffew */
	cx231xx_swab((u16 *) p_buffew, (u16 *) stawtwwite, (u16) wencopy);

	wetuwn 0;
}

void cx231xx_swab(u16 *fwom, u16 *to, u16 wen)
{
	u16 i;

	if (wen <= 0)
		wetuwn;

	fow (i = 0; i < wen / 2; i++)
		to[i] = (fwom[i] << 8) | (fwom[i] >> 8);
}

u8 cx231xx_is_buffew_done(stwuct cx231xx *dev, stwuct cx231xx_dmaqueue *dma_q)
{
	u8 buffew_compwete = 0;

	/* Duaw fiewd stweam */
	buffew_compwete = ((dma_q->cuwwent_fiewd == 2) &&
			   (dma_q->wines_compweted >= dma_q->wines_pew_fiewd) &&
			    dma_q->fiewd1_done);

	wetuwn buffew_compwete;
}

/* ------------------------------------------------------------------
	Videobuf opewations
   ------------------------------------------------------------------*/

static int queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	dev->size = (dev->width * dev->height * dev->fowmat->depth + 7) >> 3;

	if (q_num_bufs + *nbuffews < CX231XX_MIN_BUF)
		*nbuffews = CX231XX_MIN_BUF - q_num_bufs;

	if (*npwanes)
		wetuwn sizes[0] < dev->size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = dev->size;

	wetuwn 0;
}

static void buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct cx231xx_buffew *buf =
	    containew_of(vb, stwuct cx231xx_buffew, vb.vb2_buf);
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->video_mode.swock, fwags);
	wist_add_taiw(&buf->wist, &vidq->active);
	spin_unwock_iwqwestowe(&dev->video_mode.swock, fwags);
}

static void wetuwn_aww_buffews(stwuct cx231xx *dev,
			       enum vb2_buffew_state state)
{
	stwuct cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	stwuct cx231xx_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->video_mode.swock, fwags);
	if (dev->USE_ISO)
		dev->video_mode.isoc_ctw.buf = NUWW;
	ewse
		dev->video_mode.buwk_ctw.buf = NUWW;
	wist_fow_each_entwy_safe(buf, node, &vidq->active, wist) {
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
	spin_unwock_iwqwestowe(&dev->video_mode.swock, fwags);
}

static int stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	int wet = 0;

	vidq->sequence = 0;
	dev->mode_tv = 0;

	cx231xx_enabwe_anawog_tunew(dev);
	if (dev->USE_ISO)
		wet = cx231xx_init_isoc(dev, CX231XX_NUM_PACKETS,
					CX231XX_NUM_BUFS,
					dev->video_mode.max_pkt_size,
					cx231xx_isoc_copy);
	ewse
		wet = cx231xx_init_buwk(dev, CX231XX_NUM_PACKETS,
					CX231XX_NUM_BUFS,
					dev->video_mode.max_pkt_size,
					cx231xx_buwk_copy);
	if (wet)
		wetuwn_aww_buffews(dev, VB2_BUF_STATE_QUEUED);
	caww_aww(dev, video, s_stweam, 1);
	wetuwn wet;
}

static void stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct cx231xx *dev = vb2_get_dwv_pwiv(vq);

	caww_aww(dev, video, s_stweam, 0);
	wetuwn_aww_buffews(dev, VB2_BUF_STATE_EWWOW);
}

static stwuct vb2_ops cx231xx_video_qops = {
	.queue_setup		= queue_setup,
	.buf_queue		= buffew_queue,
	.stawt_stweaming	= stawt_stweaming,
	.stop_stweaming		= stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/*********************  v4w2 intewface  **************************************/

void video_mux(stwuct cx231xx *dev, int index)
{
	dev->video_input = index;
	dev->ctw_ainput = INPUT(index)->amux;

	cx231xx_set_video_input_mux(dev, index);

	cx25840_caww(dev, video, s_wouting, INPUT(index)->vmux, 0, 0);

	cx231xx_set_audio_input(dev, dev->ctw_ainput);

	dev_dbg(dev->dev, "video_mux : %d\n", index);

	/* do mode contwow ovewwides if wequiwed */
	cx231xx_do_mode_ctww_ovewwides(dev);
}

/* ------------------------------------------------------------------
	IOCTW vidioc handwing
   ------------------------------------------------------------------*/

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.pixewfowmat = dev->fowmat->fouwcc;
	f->fmt.pix.bytespewwine = (dev->width * dev->fowmat->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * dev->height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;

	wetuwn 0;
}

static stwuct cx231xx_fmt *fowmat_by_fouwcc(unsigned int fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmat); i++)
		if (fowmat[i].fouwcc == fouwcc)
			wetuwn &fowmat[i];

	wetuwn NUWW;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	unsigned int width = f->fmt.pix.width;
	unsigned int height = f->fmt.pix.height;
	unsigned int maxw = nowm_maxw(dev);
	unsigned int maxh = nowm_maxh(dev);
	stwuct cx231xx_fmt *fmt;

	fmt = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (!fmt) {
		cx231xx_videodbg("Fouwcc fowmat (%08x) invawid.\n",
				 f->fmt.pix.pixewfowmat);
		wetuwn -EINVAW;
	}

	/* width must even because of the YUYV fowmat
	   height must be even because of intewwacing */
	v4w_bound_awign_image(&width, 48, maxw, 1, &height, 32, maxh, 1, 0);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixewfowmat = fmt->fouwcc;
	f->fmt.pix.bytespewwine = (width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED;

	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wc;

	wc = vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wc)
		wetuwn wc;

	if (vb2_is_busy(&dev->vidq)) {
		dev_eww(dev->dev, "%s: queue busy\n", __func__);
		wetuwn -EBUSY;
	}

	/* set new image size */
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->fowmat = fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix, MEDIA_BUS_FMT_FIXED);
	caww_aww(dev, pad, set_fmt, NUWW, &fowmat);
	v4w2_fiww_pix_fowmat(&f->fmt.pix, &fowmat.fowmat);

	wetuwn wc;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	*id = dev->nowm;
	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id nowm)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	if (dev->nowm == nowm)
		wetuwn 0;

	if (vb2_is_busy(&dev->vidq))
		wetuwn -EBUSY;

	dev->nowm = nowm;

	/* Adjusts width/height, if needed */
	dev->width = 720;
	dev->height = (dev->nowm & V4W2_STD_625_50) ? 576 : 480;

	caww_aww(dev, video, s_std, dev->nowm);

	/* We need to weset basic pwopewties in the decodew wewated to
	   wesowution (since a standawd change effects things wike the numbew
	   of wines in VACT, etc) */
	fowmat.fowmat.code = MEDIA_BUS_FMT_FIXED;
	fowmat.fowmat.width = dev->width;
	fowmat.fowmat.height = dev->height;
	caww_aww(dev, pad, set_fmt, NUWW, &fowmat);

	/* do mode contwow ovewwides */
	cx231xx_do_mode_ctww_ovewwides(dev);

	wetuwn 0;
}

static const chaw *iname[] = {
	[CX231XX_VMUX_COMPOSITE1] = "Composite1",
	[CX231XX_VMUX_SVIDEO]     = "S-Video",
	[CX231XX_VMUX_TEWEVISION] = "Tewevision",
	[CX231XX_VMUX_CABWE]      = "Cabwe TV",
	[CX231XX_VMUX_DVB]        = "DVB",
};

void cx231xx_v4w2_cweate_entities(stwuct cx231xx *dev)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	int wet, i;

	/* Cweate entities fow each input connectow */
	fow (i = 0; i < MAX_CX231XX_INPUT; i++) {
		stwuct media_entity *ent = &dev->input_ent[i];

		if (!INPUT(i)->type)
			bweak;

		ent->name = iname[INPUT(i)->type];
		ent->fwags = MEDIA_ENT_FW_CONNECTOW;
		dev->input_pad[i].fwags = MEDIA_PAD_FW_SOUWCE;

		switch (INPUT(i)->type) {
		case CX231XX_VMUX_COMPOSITE1:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			bweak;
		case CX231XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			bweak;
		case CX231XX_VMUX_TEWEVISION:
		case CX231XX_VMUX_CABWE:
		case CX231XX_VMUX_DVB:
			/* The DVB cowe wiww handwe it */
			if (dev->tunew_type == TUNEW_ABSENT)
				continue;
			fawwthwough;
		defauwt: /* just to shut up a gcc wawning */
			ent->function = MEDIA_ENT_F_CONN_WF;
			bweak;
		}

		wet = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (wet < 0)
			pw_eww("faiwed to initiawize input pad[%d]!\n", i);

		wet = media_device_wegistew_entity(dev->media_dev, ent);
		if (wet < 0)
			pw_eww("faiwed to wegistew input entity %d!\n", i);
	}
#endif
}

int cx231xx_enum_input(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_input *i)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	u32 gen_stat;
	unsigned int n;
	int wet;

	n = i->index;
	if (n >= MAX_CX231XX_INPUT)
		wetuwn -EINVAW;
	if (0 == INPUT(n)->type)
		wetuwn -EINVAW;

	i->index = n;
	i->type = V4W2_INPUT_TYPE_CAMEWA;

	stwscpy(i->name, iname[INPUT(n)->type], sizeof(i->name));

	if ((CX231XX_VMUX_TEWEVISION == INPUT(n)->type) ||
	    (CX231XX_VMUX_CABWE == INPUT(n)->type))
		i->type = V4W2_INPUT_TYPE_TUNEW;

	i->std = dev->vdev.tvnowms;

	/* If they awe asking about the active input, wead signaw status */
	if (n == dev->video_input) {
		wet = cx231xx_wead_i2c_data(dev, VID_BWK_I2C_ADDWESS,
					    GEN_STAT, 2, &gen_stat, 4);
		if (wet > 0) {
			if ((gen_stat & FWD_VPWES) == 0x00)
				i->status |= V4W2_IN_ST_NO_SIGNAW;
			if ((gen_stat & FWD_HWOCK) == 0x00)
				i->status |= V4W2_IN_ST_NO_H_WOCK;
		}
	}

	wetuwn 0;
}

int cx231xx_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	*i = dev->video_input;

	wetuwn 0;
}

int cx231xx_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	dev->mode_tv = 0;

	if (i >= MAX_CX231XX_INPUT)
		wetuwn -EINVAW;
	if (0 == INPUT(i)->type)
		wetuwn -EINVAW;

	video_mux(dev, i);

	if (INPUT(i)->type == CX231XX_VMUX_TEWEVISION ||
	    INPUT(i)->type == CX231XX_VMUX_CABWE) {
		/* Thewe's a tunew, so weset the standawd and put it on the
		   wast known fwequency (since it was pwobabwy powewed down
		   untiw now */
		caww_aww(dev, video, s_std, dev->nowm);
	}

	wetuwn 0;
}

int cx231xx_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	if (0 != t->index)
		wetuwn -EINVAW;

	stwscpy(t->name, "Tunew", sizeof(t->name));

	t->type = V4W2_TUNEW_ANAWOG_TV;
	t->capabiwity = V4W2_TUNEW_CAP_NOWM;
	t->wangehigh = 0xffffffffUW;
	t->signaw = 0xffff;	/* WOCKED */
	caww_aww(dev, tunew, g_tunew, t);

	wetuwn 0;
}

int cx231xx_s_tunew(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_tunew *t)
{
	if (0 != t->index)
		wetuwn -EINVAW;
	wetuwn 0;
}

int cx231xx_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fwequency *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	if (f->tunew)
		wetuwn -EINVAW;

	f->fwequency = dev->ctw_fweq;

	wetuwn 0;
}

int cx231xx_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	stwuct v4w2_fwequency new_fweq = *f;
	int wc, need_if_fweq = 0;
	u32 if_fwequency = 5400000;

	dev_dbg(dev->dev,
		"Entew vidioc_s_fwequency()f->fwequency=%d;f->type=%d\n",
		f->fwequency, f->type);

	if (0 != f->tunew)
		wetuwn -EINVAW;

	/* set pwe channew change settings in DIF fiwst */
	wc = cx231xx_tunew_pwe_channew_change(dev);

	switch (dev->modew) { /* i2c device tunews */
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	case CX231XX_BOAWD_HAUPPAUGE_975:
	case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
		if (dev->cx231xx_set_anawog_fweq)
			dev->cx231xx_set_anawog_fweq(dev, f->fwequency);
		dev->ctw_fweq = f->fwequency;
		need_if_fweq = 1;
		bweak;
	defauwt:
		caww_aww(dev, tunew, s_fwequency, f);
		caww_aww(dev, tunew, g_fwequency, &new_fweq);
		dev->ctw_fweq = new_fweq.fwequency;
		bweak;
	}

	pw_debug("%s() %u  :  %u\n", __func__, f->fwequency, dev->ctw_fweq);

	/* set post channew change settings in DIF fiwst */
	wc = cx231xx_tunew_post_channew_change(dev);

	if (need_if_fweq || dev->tunew_type == TUNEW_NXP_TDA18271) {
		if (dev->nowm & (V4W2_STD_MN | V4W2_STD_NTSC_443))
			if_fwequency = 5400000;  /*5.4MHz	*/
		ewse if (dev->nowm & V4W2_STD_B)
			if_fwequency = 6000000;  /*6.0MHz	*/
		ewse if (dev->nowm & (V4W2_STD_PAW_DK | V4W2_STD_SECAM_DK))
			if_fwequency = 6900000;  /*6.9MHz	*/
		ewse if (dev->nowm & V4W2_STD_GH)
			if_fwequency = 7100000;  /*7.1MHz	*/
		ewse if (dev->nowm & V4W2_STD_PAW_I)
			if_fwequency = 7250000;  /*7.25MHz	*/
		ewse if (dev->nowm & V4W2_STD_SECAM_W)
			if_fwequency = 6900000;  /*6.9MHz	*/
		ewse if (dev->nowm & V4W2_STD_SECAM_WC)
			if_fwequency = 1250000;  /*1.25MHz	*/

		dev_dbg(dev->dev,
			"if_fwequency is set to %d\n", if_fwequency);
		cx231xx_set_Cowibwi_Fow_WowIF(dev, if_fwequency, 1, 1);

		update_HH_wegistew_aftew_set_DIF(dev);
	}

	dev_dbg(dev->dev, "Set New FWEQUENCY to %d\n", f->fwequency);

	wetuwn wc;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG

int cx231xx_g_chip_info(stwuct fiwe *fiwe, void *fh,
			stwuct v4w2_dbg_chip_info *chip)
{
	switch (chip->match.addw) {
	case 0:	/* Cx231xx - intewnaw wegistews */
		wetuwn 0;
	case 1:	/* AFE - wead byte */
		stwscpy(chip->name, "AFE (byte)", sizeof(chip->name));
		wetuwn 0;
	case 2:	/* Video Bwock - wead byte */
		stwscpy(chip->name, "Video (byte)", sizeof(chip->name));
		wetuwn 0;
	case 3:	/* I2S bwock - wead byte */
		stwscpy(chip->name, "I2S (byte)", sizeof(chip->name));
		wetuwn 0;
	case 4: /* AFE - wead dwowd */
		stwscpy(chip->name, "AFE (dwowd)", sizeof(chip->name));
		wetuwn 0;
	case 5: /* Video Bwock - wead dwowd */
		stwscpy(chip->name, "Video (dwowd)", sizeof(chip->name));
		wetuwn 0;
	case 6: /* I2S Bwock - wead dwowd */
		stwscpy(chip->name, "I2S (dwowd)", sizeof(chip->name));
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

int cx231xx_g_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	int wet;
	u8 vawue[4] = { 0, 0, 0, 0 };
	u32 data = 0;

	switch (weg->match.addw) {
	case 0:	/* Cx231xx - intewnaw wegistews */
		wet = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW,
				(u16)weg->weg, vawue, 4);
		weg->vaw = vawue[0] | vawue[1] << 8 |
			vawue[2] << 16 | (u32)vawue[3] << 24;
		weg->size = 4;
		bweak;
	case 1:	/* AFE - wead byte */
		wet = cx231xx_wead_i2c_data(dev, AFE_DEVICE_ADDWESS,
				(u16)weg->weg, 2, &data, 1);
		weg->vaw = data;
		weg->size = 1;
		bweak;
	case 2:	/* Video Bwock - wead byte */
		wet = cx231xx_wead_i2c_data(dev, VID_BWK_I2C_ADDWESS,
				(u16)weg->weg, 2, &data, 1);
		weg->vaw = data;
		weg->size = 1;
		bweak;
	case 3:	/* I2S bwock - wead byte */
		wet = cx231xx_wead_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
				(u16)weg->weg, 1, &data, 1);
		weg->vaw = data;
		weg->size = 1;
		bweak;
	case 4: /* AFE - wead dwowd */
		wet = cx231xx_wead_i2c_data(dev, AFE_DEVICE_ADDWESS,
				(u16)weg->weg, 2, &data, 4);
		weg->vaw = data;
		weg->size = 4;
		bweak;
	case 5: /* Video Bwock - wead dwowd */
		wet = cx231xx_wead_i2c_data(dev, VID_BWK_I2C_ADDWESS,
				(u16)weg->weg, 2, &data, 4);
		weg->vaw = data;
		weg->size = 4;
		bweak;
	case 6: /* I2S Bwock - wead dwowd */
		wet = cx231xx_wead_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
				(u16)weg->weg, 1, &data, 4);
		weg->vaw = data;
		weg->size = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wet < 0 ? wet : 0;
}

int cx231xx_s_wegistew(stwuct fiwe *fiwe, void *pwiv,
			     const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	int wet;
	u8 data[4] = { 0, 0, 0, 0 };

	switch (weg->match.addw) {
	case 0:	/* cx231xx intewnaw wegistews */
		data[0] = (u8) weg->vaw;
		data[1] = (u8) (weg->vaw >> 8);
		data[2] = (u8) (weg->vaw >> 16);
		data[3] = (u8) (weg->vaw >> 24);
		wet = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
				(u16)weg->weg, data, 4);
		bweak;
	case 1:	/* AFE - wwite byte */
		wet = cx231xx_wwite_i2c_data(dev, AFE_DEVICE_ADDWESS,
				(u16)weg->weg, 2, weg->vaw, 1);
		bweak;
	case 2:	/* Video Bwock - wwite byte */
		wet = cx231xx_wwite_i2c_data(dev, VID_BWK_I2C_ADDWESS,
				(u16)weg->weg, 2, weg->vaw, 1);
		bweak;
	case 3:	/* I2S bwock - wwite byte */
		wet = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
				(u16)weg->weg, 1, weg->vaw, 1);
		bweak;
	case 4: /* AFE - wwite dwowd */
		wet = cx231xx_wwite_i2c_data(dev, AFE_DEVICE_ADDWESS,
				(u16)weg->weg, 2, weg->vaw, 4);
		bweak;
	case 5: /* Video Bwock - wwite dwowd */
		wet = cx231xx_wwite_i2c_data(dev, VID_BWK_I2C_ADDWESS,
				(u16)weg->weg, 2, weg->vaw, 4);
		bweak;
	case 6: /* I2S bwock - wwite dwowd */
		wet = cx231xx_wwite_i2c_data(dev, I2S_BWK_DEVICE_ADDWESS,
				(u16)weg->weg, 1, weg->vaw, 4);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn wet < 0 ? wet : 0;
}
#endif

static int vidioc_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv,
				int type, stwuct v4w2_fwact *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);
	boow is_50hz = dev->nowm & V4W2_STD_625_50;

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	f->numewatow = is_50hz ? 54 : 11;
	f->denominatow = is_50hz ? 59 : 10;

	wetuwn 0;
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *s)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = dev->width;
		s->w.height = dev->height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int cx231xx_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "cx231xx", sizeof(cap->dwivew));
	stwscpy(cap->cawd, cx231xx_boawds[dev->modew].name, sizeof(cap->cawd));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	cap->capabiwities = V4W2_CAP_WEADWWITE |
		V4W2_CAP_VBI_CAPTUWE | V4W2_CAP_VIDEO_CAPTUWE |
		V4W2_CAP_STWEAMING | V4W2_CAP_DEVICE_CAPS;
	if (video_is_wegistewed(&dev->wadio_dev))
		cap->capabiwities |= V4W2_CAP_WADIO;

	switch (dev->modew) {
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	case CX231XX_BOAWD_HAUPPAUGE_975:
	case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
		cap->capabiwities |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			cap->capabiwities |= V4W2_CAP_TUNEW;
		bweak;
	}
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	if (unwikewy(f->index >= AWWAY_SIZE(fowmat)))
		wetuwn -EINVAW;

	f->pixewfowmat = fowmat[f->index].fouwcc;

	wetuwn 0;
}

/* WAW VBI ioctws */

static int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	f->fmt.vbi.sampwing_wate = 6750000 * 4;
	f->fmt.vbi.sampwes_pew_wine = VBI_WINE_WENGTH;
	f->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.stawt[0] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_STAWT_WINE : NTSC_VBI_STAWT_WINE;
	f->fmt.vbi.count[0] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_WINES : NTSC_VBI_WINES;
	f->fmt.vbi.stawt[1] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_STAWT_WINE + 312 : NTSC_VBI_STAWT_WINE + 263;
	f->fmt.vbi.count[1] = f->fmt.vbi.count[0];
	memset(f->fmt.vbi.wesewved, 0, sizeof(f->fmt.vbi.wesewved));

	wetuwn 0;

}

static int vidioc_twy_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	f->fmt.vbi.sampwing_wate = 6750000 * 4;
	f->fmt.vbi.sampwes_pew_wine = VBI_WINE_WENGTH;
	f->fmt.vbi.sampwe_fowmat = V4W2_PIX_FMT_GWEY;
	f->fmt.vbi.offset = 0;
	f->fmt.vbi.fwags = 0;
	f->fmt.vbi.stawt[0] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_STAWT_WINE : NTSC_VBI_STAWT_WINE;
	f->fmt.vbi.count[0] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_WINES : NTSC_VBI_WINES;
	f->fmt.vbi.stawt[1] = (dev->nowm & V4W2_STD_625_50) ?
	    PAW_VBI_STAWT_WINE + 312 : NTSC_VBI_STAWT_WINE + 263;
	f->fmt.vbi.count[1] = f->fmt.vbi.count[0];
	memset(f->fmt.vbi.wesewved, 0, sizeof(f->fmt.vbi.wesewved));

	wetuwn 0;

}

static int vidioc_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	wetuwn vidioc_twy_fmt_vbi_cap(fiwe, pwiv, f);
}

/* ----------------------------------------------------------- */
/* WADIO ESPECIFIC IOCTWS                                      */
/* ----------------------------------------------------------- */

static int wadio_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	if (t->index)
		wetuwn -EINVAW;

	stwscpy(t->name, "Wadio", sizeof(t->name));

	caww_aww(dev, tunew, g_tunew, t);

	wetuwn 0;
}
static int wadio_s_tunew(stwuct fiwe *fiwe, void *pwiv, const stwuct v4w2_tunew *t)
{
	stwuct cx231xx *dev = video_dwvdata(fiwe);

	if (t->index)
		wetuwn -EINVAW;

	caww_aww(dev, tunew, s_tunew, t);

	wetuwn 0;
}

/*
 * cx231xx_v4w2_open()
 * inits the device and stawts isoc twansfew
 */
static int cx231xx_v4w2_open(stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct cx231xx *dev = video_dwvdata(fiwp);
	int wet;

	if (mutex_wock_intewwuptibwe(&dev->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwp);
	if (wet) {
		mutex_unwock(&dev->wock);
		wetuwn wet;
	}

	if (dev->usews++ == 0) {
		/* Powew up in Anawog TV mode */
		if (dev->boawd.extewnaw_av)
			cx231xx_set_powew_mode(dev,
				 POWAWIS_AVMODE_ENXTEWNAW_AV);
		ewse
			cx231xx_set_powew_mode(dev, POWAWIS_AVMODE_ANAWOGT_TV);

		/* set video awtewnate setting */
		cx231xx_set_video_awtewnate(dev);

		/* Needed, since GPIO might have disabwed powew of
		   some i2c device */
		cx231xx_config_i2c(dev);

		/* device needs to be initiawized befowe isoc twansfew */
		dev->video_input = dev->video_input > 2 ? 2 : dev->video_input;
	}

	if (vdev->vfw_type == VFW_TYPE_WADIO) {
		cx231xx_videodbg("video_open: setting wadio device\n");

		/* cx231xx_stawt_wadio(dev); */

		caww_aww(dev, tunew, s_wadio);
	}
	if (vdev->vfw_type == VFW_TYPE_VBI) {
		/* Set the wequiwed awtewnate setting  VBI intewface wowks in
		   Buwk mode onwy */
		cx231xx_set_awt_setting(dev, INDEX_VANC, 0);
	}
	mutex_unwock(&dev->wock);
	wetuwn 0;
}

/*
 * cx231xx_weawease_wesouwces()
 * unwegistews the v4w2,i2c and usb devices
 * cawwed when the device gets disconnected ow at moduwe unwoad
*/
void cx231xx_wewease_anawog_wesouwces(stwuct cx231xx *dev)
{

	/*FIXME: I2C IW shouwd be disconnected */

	if (video_is_wegistewed(&dev->wadio_dev))
		video_unwegistew_device(&dev->wadio_dev);
	if (video_is_wegistewed(&dev->vbi_dev)) {
		dev_info(dev->dev, "V4W2 device %s dewegistewed\n",
			video_device_node_name(&dev->vbi_dev));
		video_unwegistew_device(&dev->vbi_dev);
	}
	if (video_is_wegistewed(&dev->vdev)) {
		dev_info(dev->dev, "V4W2 device %s dewegistewed\n",
			video_device_node_name(&dev->vdev));

		if (dev->boawd.has_417)
			cx231xx_417_unwegistew(dev);

		video_unwegistew_device(&dev->vdev);
	}
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	v4w2_ctww_handwew_fwee(&dev->wadio_ctww_handwew);
}

/*
 * cx231xx_cwose()
 * stops stweaming and deawwocates aww wesouwces awwocated by the v4w2
 * cawws and ioctws
 */
static int cx231xx_cwose(stwuct fiwe *fiwp)
{
	stwuct cx231xx *dev = video_dwvdata(fiwp);
	stwuct video_device *vdev = video_devdata(fiwp);

	_vb2_fop_wewease(fiwp, NUWW);

	if (--dev->usews == 0) {
		/* Save some powew by putting tunew to sweep */
		caww_aww(dev, tunew, standby);

		/* do this befowe setting awtewnate! */
		if (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		ewse
			cx231xx_uninit_buwk(dev);
		cx231xx_set_mode(dev, CX231XX_SUSPEND);
	}

	/*
	 * To wowkawound ewwow numbew=-71 on EP0 fow VideoGwabbew,
	 *	 need excwude fowwowing.
	 * FIXME: It is pwobabwy safe to wemove most of these, as we'we
	 * now avoiding the awtewnate setting fow INDEX_VANC
	 */
	if (!dev->boawd.no_awt_vanc && vdev->vfw_type == VFW_TYPE_VBI) {
		/* do this befowe setting awtewnate! */
		cx231xx_uninit_vbi_isoc(dev);

		/* set awtewnate 0 */
		if (!dev->vbi_ow_swiced_cc_mode)
			cx231xx_set_awt_setting(dev, INDEX_VANC, 0);
		ewse
			cx231xx_set_awt_setting(dev, INDEX_HANC, 0);

		wake_up_intewwuptibwe_nw(&dev->open, 1);
		wetuwn 0;
	}

	if (dev->usews == 0) {
		/* set awtewnate 0 */
		cx231xx_set_awt_setting(dev, INDEX_VIDEO, 0);
	}

	wake_up_intewwuptibwe(&dev->open);
	wetuwn 0;
}

static int cx231xx_v4w2_cwose(stwuct fiwe *fiwp)
{
	stwuct cx231xx *dev = video_dwvdata(fiwp);
	int wc;

	mutex_wock(&dev->wock);
	wc = cx231xx_cwose(fiwp);
	mutex_unwock(&dev->wock);
	wetuwn wc;
}

static const stwuct v4w2_fiwe_opewations cx231xx_v4w_fops = {
	.ownew   = THIS_MODUWE,
	.open    = cx231xx_v4w2_open,
	.wewease = cx231xx_v4w2_cwose,
	.wead    = vb2_fop_wead,
	.poww    = vb2_fop_poww,
	.mmap    = vb2_fop_mmap,
	.unwocked_ioctw   = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops video_ioctw_ops = {
	.vidioc_quewycap               = cx231xx_quewycap,
	.vidioc_enum_fmt_vid_cap       = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap          = vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap        = vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap          = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap          = vidioc_g_fmt_vbi_cap,
	.vidioc_twy_fmt_vbi_cap        = vidioc_twy_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap          = vidioc_s_fmt_vbi_cap,
	.vidioc_g_pixewaspect          = vidioc_g_pixewaspect,
	.vidioc_g_sewection            = vidioc_g_sewection,
	.vidioc_weqbufs                = vb2_ioctw_weqbufs,
	.vidioc_quewybuf               = vb2_ioctw_quewybuf,
	.vidioc_qbuf                   = vb2_ioctw_qbuf,
	.vidioc_dqbuf                  = vb2_ioctw_dqbuf,
	.vidioc_s_std                  = vidioc_s_std,
	.vidioc_g_std                  = vidioc_g_std,
	.vidioc_enum_input             = cx231xx_enum_input,
	.vidioc_g_input                = cx231xx_g_input,
	.vidioc_s_input                = cx231xx_s_input,
	.vidioc_stweamon               = vb2_ioctw_stweamon,
	.vidioc_stweamoff              = vb2_ioctw_stweamoff,
	.vidioc_g_tunew                = cx231xx_g_tunew,
	.vidioc_s_tunew                = cx231xx_s_tunew,
	.vidioc_g_fwequency            = cx231xx_g_fwequency,
	.vidioc_s_fwequency            = cx231xx_s_fwequency,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info            = cx231xx_g_chip_info,
	.vidioc_g_wegistew             = cx231xx_g_wegistew,
	.vidioc_s_wegistew             = cx231xx_s_wegistew,
#endif
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static stwuct video_device cx231xx_vbi_tempwate;

static const stwuct video_device cx231xx_video_tempwate = {
	.fops         = &cx231xx_v4w_fops,
	.wewease      = video_device_wewease_empty,
	.ioctw_ops    = &video_ioctw_ops,
	.tvnowms      = V4W2_STD_AWW,
};

static const stwuct v4w2_fiwe_opewations wadio_fops = {
	.ownew   = THIS_MODUWE,
	.open   = cx231xx_v4w2_open,
	.wewease = cx231xx_v4w2_cwose,
	.poww = v4w2_ctww_poww,
	.unwocked_ioctw = video_ioctw2,
};

static const stwuct v4w2_ioctw_ops wadio_ioctw_ops = {
	.vidioc_quewycap    = cx231xx_quewycap,
	.vidioc_g_tunew     = wadio_g_tunew,
	.vidioc_s_tunew     = wadio_s_tunew,
	.vidioc_g_fwequency = cx231xx_g_fwequency,
	.vidioc_s_fwequency = cx231xx_s_fwequency,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info = cx231xx_g_chip_info,
	.vidioc_g_wegistew  = cx231xx_g_wegistew,
	.vidioc_s_wegistew  = cx231xx_s_wegistew,
#endif
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static stwuct video_device cx231xx_wadio_tempwate = {
	.name      = "cx231xx-wadio",
	.fops      = &wadio_fops,
	.ioctw_ops = &wadio_ioctw_ops,
};

/******************************** usb intewface ******************************/

static void cx231xx_vdev_init(stwuct cx231xx *dev,
		stwuct video_device *vfd,
		const stwuct video_device *tempwate,
		const chaw *type_name)
{
	*vfd = *tempwate;
	vfd->v4w2_dev = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &dev->wock;

	snpwintf(vfd->name, sizeof(vfd->name), "%s %s", dev->name, type_name);

	video_set_dwvdata(vfd, dev);
	if (dev->tunew_type == TUNEW_ABSENT) {
		switch (dev->modew) {
		case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
		case CX231XX_BOAWD_HAUPPAUGE_935C:
		case CX231XX_BOAWD_HAUPPAUGE_955Q:
		case CX231XX_BOAWD_HAUPPAUGE_975:
		case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
			bweak;
		defauwt:
			v4w2_disabwe_ioctw(vfd, VIDIOC_G_FWEQUENCY);
			v4w2_disabwe_ioctw(vfd, VIDIOC_S_FWEQUENCY);
			v4w2_disabwe_ioctw(vfd, VIDIOC_G_TUNEW);
			v4w2_disabwe_ioctw(vfd, VIDIOC_S_TUNEW);
			bweak;
		}
	}
}

int cx231xx_wegistew_anawog_devices(stwuct cx231xx *dev)
{
	stwuct vb2_queue *q;
	int wet;

	dev_info(dev->dev, "v4w2 dwivew vewsion %s\n", CX231XX_VEWSION);

	/* set defauwt nowm */
	dev->nowm = V4W2_STD_PAW;
	dev->width = nowm_maxw(dev);
	dev->height = nowm_maxh(dev);
	dev->intewwaced = 0;

	/* Anawog specific initiawization */
	dev->fowmat = &fowmat[0];

	/* Set the initiaw input */
	video_mux(dev, dev->video_input);

	caww_aww(dev, video, s_std, dev->nowm);

	v4w2_ctww_handwew_init(&dev->ctww_handwew, 10);
	v4w2_ctww_handwew_init(&dev->wadio_ctww_handwew, 5);

	if (dev->sd_cx25840) {
		v4w2_ctww_add_handwew(&dev->ctww_handwew,
				dev->sd_cx25840->ctww_handwew, NUWW, twue);
		v4w2_ctww_add_handwew(&dev->wadio_ctww_handwew,
				dev->sd_cx25840->ctww_handwew,
				v4w2_ctww_wadio_fiwtew, twue);
	}

	if (dev->ctww_handwew.ewwow)
		wetuwn dev->ctww_handwew.ewwow;
	if (dev->wadio_ctww_handwew.ewwow)
		wetuwn dev->wadio_ctww_handwew.ewwow;

	/* enabwe vbi captuwing */
	/* wwite code hewe...  */

	/* awwocate and fiww video video_device stwuct */
	cx231xx_vdev_init(dev, &dev->vdev, &cx231xx_video_tempwate, "video");
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	dev->video_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->vdev.entity, 1, &dev->video_pad);
	if (wet < 0)
		dev_eww(dev->dev, "faiwed to initiawize video media entity!\n");
#endif
	dev->vdev.ctww_handwew = &dev->ctww_handwew;

	q = &dev->vidq;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_USEWPTW | VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx231xx_buffew);
	q->ops = &cx231xx_video_qops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 1;
	q->wock = &dev->wock;
	wet = vb2_queue_init(q);
	if (wet)
		wetuwn wet;
	dev->vdev.queue = q;
	dev->vdev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				V4W2_CAP_VIDEO_CAPTUWE;

	switch (dev->modew) { /* i2c device tunews */
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	case CX231XX_BOAWD_HAUPPAUGE_975:
	case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
		dev->vdev.device_caps |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			dev->vdev.device_caps |= V4W2_CAP_TUNEW;
		bweak;
	}

	/* wegistew v4w2 video video_device */
	wet = video_wegistew_device(&dev->vdev, VFW_TYPE_VIDEO,
				    video_nw[dev->devno]);
	if (wet) {
		dev_eww(dev->dev,
			"unabwe to wegistew video device (ewwow=%i).\n",
			wet);
		wetuwn wet;
	}

	dev_info(dev->dev, "Wegistewed video device %s [v4w2]\n",
		video_device_node_name(&dev->vdev));

	/* Initiawize VBI tempwate */
	cx231xx_vbi_tempwate = cx231xx_video_tempwate;
	stwscpy(cx231xx_vbi_tempwate.name, "cx231xx-vbi",
		sizeof(cx231xx_vbi_tempwate.name));

	/* Awwocate and fiww vbi video_device stwuct */
	cx231xx_vdev_init(dev, &dev->vbi_dev, &cx231xx_vbi_tempwate, "vbi");

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	dev->vbi_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->vbi_dev.entity, 1, &dev->vbi_pad);
	if (wet < 0)
		dev_eww(dev->dev, "faiwed to initiawize vbi media entity!\n");
#endif
	dev->vbi_dev.ctww_handwew = &dev->ctww_handwew;

	q = &dev->vbiq;
	q->type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	q->io_modes = VB2_USEWPTW | VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct cx231xx_buffew);
	q->ops = &cx231xx_vbi_qops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 1;
	q->wock = &dev->wock;
	wet = vb2_queue_init(q);
	if (wet)
		wetuwn wet;
	dev->vbi_dev.queue = q;
	dev->vbi_dev.device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				   V4W2_CAP_VBI_CAPTUWE;
	switch (dev->modew) { /* i2c device tunews */
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1114xx:
	case CX231XX_BOAWD_HAUPPAUGE_935C:
	case CX231XX_BOAWD_HAUPPAUGE_955Q:
	case CX231XX_BOAWD_HAUPPAUGE_975:
	case CX231XX_BOAWD_EVWOMEDIA_FUWW_HYBWID_FUWWHD:
		dev->vbi_dev.device_caps |= V4W2_CAP_TUNEW;
		bweak;
	defauwt:
		if (dev->tunew_type != TUNEW_ABSENT)
			dev->vbi_dev.device_caps |= V4W2_CAP_TUNEW;
	}

	/* wegistew v4w2 vbi video_device */
	wet = video_wegistew_device(&dev->vbi_dev, VFW_TYPE_VBI,
				    vbi_nw[dev->devno]);
	if (wet < 0) {
		dev_eww(dev->dev, "unabwe to wegistew vbi device\n");
		wetuwn wet;
	}

	dev_info(dev->dev, "Wegistewed VBI device %s\n",
		video_device_node_name(&dev->vbi_dev));

	if (cx231xx_boawds[dev->modew].wadio.type == CX231XX_WADIO) {
		cx231xx_vdev_init(dev, &dev->wadio_dev,
				&cx231xx_wadio_tempwate, "wadio");
		dev->wadio_dev.ctww_handwew = &dev->wadio_ctww_handwew;
		dev->wadio_dev.device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;
		wet = video_wegistew_device(&dev->wadio_dev, VFW_TYPE_WADIO,
					    wadio_nw[dev->devno]);
		if (wet < 0) {
			dev_eww(dev->dev,
				"can't wegistew wadio device\n");
			wetuwn wet;
		}
		dev_info(dev->dev, "Wegistewed wadio device as %s\n",
			video_device_node_name(&dev->wadio_dev));
	}

	wetuwn 0;
}
