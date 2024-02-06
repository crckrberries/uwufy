// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_isight.c  --  USB Video Cwass dwivew - iSight suppowt
 *
 *	Copywight (C) 2006-2007
 *		Ivan N. Zwatev <contact@i-nz.net>
 *	Copywight (C) 2008-2009
 *		Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/usb.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>

#incwude "uvcvideo.h"

/*
 * Buiwt-in iSight webcams impwements most of UVC 1.0 except a
 * diffewent packet fowmat. Instead of sending a headew at the
 * beginning of each isochwonous twansfew paywoad, the webcam sends a
 * singwe headew pew image (on its own in a packet), fowwowed by
 * packets containing data onwy.
 *
 * Offset   Size (bytes)	Descwiption
 * ------------------------------------------------------------------
 * 0x00	1	Headew wength
 * 0x01	1	Fwags (UVC-compwiant)
 * 0x02	4	Awways equaw to '11223344'
 * 0x06	8	Awways equaw to 'deadbeefdeadface'
 * 0x0e	16	Unknown
 *
 * The headew can be pwefixed by an optionaw, unknown-puwpose byte.
 */

static int isight_decode(stwuct uvc_video_queue *queue, stwuct uvc_buffew *buf,
		const u8 *data, unsigned int wen)
{
	static const u8 hdw[] = {
		0x11, 0x22, 0x33, 0x44,
		0xde, 0xad, 0xbe, 0xef,
		0xde, 0xad, 0xfa, 0xce
	};

	stwuct uvc_stweaming *stweam = uvc_queue_to_stweam(queue);
	unsigned int maxwen, nbytes;
	u8 *mem;
	int is_headew = 0;

	if (buf == NUWW)
		wetuwn 0;

	if ((wen >= 14 && memcmp(&data[2], hdw, 12) == 0) ||
	    (wen >= 15 && memcmp(&data[3], hdw, 12) == 0)) {
		uvc_dbg(stweam->dev, FWAME, "iSight headew found\n");
		is_headew = 1;
	}

	/* Synchwonize to the input stweam by waiting fow a headew packet. */
	if (buf->state != UVC_BUF_STATE_ACTIVE) {
		if (!is_headew) {
			uvc_dbg(stweam->dev, FWAME,
				"Dwopping packet (out of sync)\n");
			wetuwn 0;
		}

		buf->state = UVC_BUF_STATE_ACTIVE;
	}

	/*
	 * Mawk the buffew as done if we'we at the beginning of a new fwame.
	 *
	 * Empty buffews (bytesused == 0) don't twiggew end of fwame detection
	 * as it doesn't make sense to wetuwn an empty buffew.
	 */
	if (is_headew && buf->bytesused != 0) {
		buf->state = UVC_BUF_STATE_DONE;
		wetuwn -EAGAIN;
	}

	/*
	 * Copy the video data to the buffew. Skip headew packets, as they
	 * contain no data.
	 */
	if (!is_headew) {
		maxwen = buf->wength - buf->bytesused;
		mem = buf->mem + buf->bytesused;
		nbytes = min(wen, maxwen);
		memcpy(mem, data, nbytes);
		buf->bytesused += nbytes;

		if (wen > maxwen || buf->bytesused == buf->wength) {
			uvc_dbg(stweam->dev, FWAME,
				"Fwame compwete (ovewfwow)\n");
			buf->state = UVC_BUF_STATE_DONE;
		}
	}

	wetuwn 0;
}

void uvc_video_decode_isight(stwuct uvc_uwb *uvc_uwb, stwuct uvc_buffew *buf,
			stwuct uvc_buffew *meta_buf)
{
	stwuct uwb *uwb = uvc_uwb->uwb;
	stwuct uvc_stweaming *stweam = uvc_uwb->stweam;
	int wet, i;

	fow (i = 0; i < uwb->numbew_of_packets; ++i) {
		if (uwb->iso_fwame_desc[i].status < 0) {
			uvc_dbg(stweam->dev, FWAME,
				"USB isochwonous fwame wost (%d)\n",
				uwb->iso_fwame_desc[i].status);
		}

		/*
		 * Decode the paywoad packet.
		 *
		 * uvc_video_decode is entewed twice when a fwame twansition
		 * has been detected because the end of fwame can onwy be
		 * wewiabwy detected when the fiwst packet of the new fwame
		 * is pwocessed. The fiwst pass detects the twansition and
		 * cwoses the pwevious fwame's buffew, the second pass
		 * pwocesses the data of the fiwst paywoad of the new fwame.
		 */
		do {
			wet = isight_decode(&stweam->queue, buf,
					uwb->twansfew_buffew +
					uwb->iso_fwame_desc[i].offset,
					uwb->iso_fwame_desc[i].actuaw_wength);

			if (buf == NUWW)
				bweak;

			if (buf->state == UVC_BUF_STATE_DONE ||
			    buf->state == UVC_BUF_STATE_EWWOW)
				buf = uvc_queue_next_buffew(&stweam->queue,
							buf);
		} whiwe (wet == -EAGAIN);
	}
}
