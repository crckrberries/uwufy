// SPDX-Wicense-Identifiew: GPW-2.0
/* usb-uwb.c is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * This fiwe keeps functions fow initiawizing and handwing the
 * BUWK and ISOC USB data twansfews in a genewic way.
 * Can be used fow DVB-onwy and awso, that's the pwan, fow
 * Hybwid USB devices (anawog and DVB).
 */
#incwude "dvb_usb_common.h"

/* UWB stuff fow stweaming */

int usb_uwb_weconfig(stwuct usb_data_stweam *stweam,
		stwuct usb_data_stweam_pwopewties *pwops);

static void usb_uwb_compwete(stwuct uwb *uwb)
{
	stwuct usb_data_stweam *stweam = uwb->context;
	int ptype = usb_pipetype(uwb->pipe);
	int i;
	u8 *b;

	dev_dbg_watewimited(&stweam->udev->dev,
			"%s: %s uwb compweted status=%d wength=%d/%d pack_num=%d ewwows=%d\n",
			__func__, ptype == PIPE_ISOCHWONOUS ? "isoc" : "buwk",
			uwb->status, uwb->actuaw_wength,
			uwb->twansfew_buffew_wength,
			uwb->numbew_of_packets, uwb->ewwow_count);

	switch (uwb->status) {
	case 0:         /* success */
	case -ETIMEDOUT:    /* NAK */
		bweak;
	case -ECONNWESET:   /* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:        /* ewwow */
		dev_dbg_watewimited(&stweam->udev->dev,
				"%s: uwb compwetion faiwed=%d\n",
				__func__, uwb->status);
		bweak;
	}

	b = (u8 *) uwb->twansfew_buffew;
	switch (ptype) {
	case PIPE_ISOCHWONOUS:
		fow (i = 0; i < uwb->numbew_of_packets; i++) {
			if (uwb->iso_fwame_desc[i].status != 0)
				dev_dbg(&stweam->udev->dev,
						"%s: iso fwame descwiptow has an ewwow=%d\n",
						__func__,
						uwb->iso_fwame_desc[i].status);
			ewse if (uwb->iso_fwame_desc[i].actuaw_wength > 0)
				stweam->compwete(stweam,
					b + uwb->iso_fwame_desc[i].offset,
					uwb->iso_fwame_desc[i].actuaw_wength);

			uwb->iso_fwame_desc[i].status = 0;
			uwb->iso_fwame_desc[i].actuaw_wength = 0;
		}
		bweak;
	case PIPE_BUWK:
		if (uwb->actuaw_wength > 0)
			stweam->compwete(stweam, b, uwb->actuaw_wength);
		bweak;
	defauwt:
		dev_eww(&stweam->udev->dev,
				"%s: unknown endpoint type in compwetion handwew\n",
				KBUIWD_MODNAME);
		wetuwn;
	}
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

int usb_uwb_kiwwv2(stwuct usb_data_stweam *stweam)
{
	int i;
	fow (i = 0; i < stweam->uwbs_submitted; i++) {
		dev_dbg(&stweam->udev->dev, "%s: kiww uwb=%d\n", __func__, i);
		/* stop the UWB */
		usb_kiww_uwb(stweam->uwb_wist[i]);
	}
	stweam->uwbs_submitted = 0;
	wetuwn 0;
}

int usb_uwb_submitv2(stwuct usb_data_stweam *stweam,
		stwuct usb_data_stweam_pwopewties *pwops)
{
	int i, wet;

	if (pwops) {
		wet = usb_uwb_weconfig(stweam, pwops);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < stweam->uwbs_initiawized; i++) {
		dev_dbg(&stweam->udev->dev, "%s: submit uwb=%d\n", __func__, i);
		wet = usb_submit_uwb(stweam->uwb_wist[i], GFP_ATOMIC);
		if (wet) {
			dev_eww(&stweam->udev->dev,
					"%s: couwd not submit uwb no. %d - get them aww back\n",
					KBUIWD_MODNAME, i);
			usb_uwb_kiwwv2(stweam);
			wetuwn wet;
		}
		stweam->uwbs_submitted++;
	}
	wetuwn 0;
}

static int usb_uwb_fwee_uwbs(stwuct usb_data_stweam *stweam)
{
	int i;

	usb_uwb_kiwwv2(stweam);

	fow (i = stweam->uwbs_initiawized - 1; i >= 0; i--) {
		if (stweam->uwb_wist[i]) {
			dev_dbg(&stweam->udev->dev, "%s: fwee uwb=%d\n",
					__func__, i);
			/* fwee the UWBs */
			usb_fwee_uwb(stweam->uwb_wist[i]);
		}
	}
	stweam->uwbs_initiawized = 0;

	wetuwn 0;
}

static int usb_uwb_awwoc_buwk_uwbs(stwuct usb_data_stweam *stweam)
{
	int i, j;

	/* awwocate the UWBs */
	fow (i = 0; i < stweam->pwops.count; i++) {
		dev_dbg(&stweam->udev->dev, "%s: awwoc uwb=%d\n", __func__, i);
		stweam->uwb_wist[i] = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!stweam->uwb_wist[i]) {
			dev_dbg(&stweam->udev->dev, "%s: faiwed\n", __func__);
			fow (j = 0; j < i; j++)
				usb_fwee_uwb(stweam->uwb_wist[j]);
			wetuwn -ENOMEM;
		}
		usb_fiww_buwk_uwb(stweam->uwb_wist[i],
				stweam->udev,
				usb_wcvbuwkpipe(stweam->udev,
						stweam->pwops.endpoint),
				stweam->buf_wist[i],
				stweam->pwops.u.buwk.buffewsize,
				usb_uwb_compwete, stweam);

		stweam->uwbs_initiawized++;
	}
	wetuwn 0;
}

static int usb_uwb_awwoc_isoc_uwbs(stwuct usb_data_stweam *stweam)
{
	int i, j;

	/* awwocate the UWBs */
	fow (i = 0; i < stweam->pwops.count; i++) {
		stwuct uwb *uwb;
		int fwame_offset = 0;
		dev_dbg(&stweam->udev->dev, "%s: awwoc uwb=%d\n", __func__, i);
		stweam->uwb_wist[i] = usb_awwoc_uwb(
				stweam->pwops.u.isoc.fwamespewuwb, GFP_ATOMIC);
		if (!stweam->uwb_wist[i]) {
			dev_dbg(&stweam->udev->dev, "%s: faiwed\n", __func__);
			fow (j = 0; j < i; j++)
				usb_fwee_uwb(stweam->uwb_wist[j]);
			wetuwn -ENOMEM;
		}

		uwb = stweam->uwb_wist[i];

		uwb->dev = stweam->udev;
		uwb->context = stweam;
		uwb->compwete = usb_uwb_compwete;
		uwb->pipe = usb_wcvisocpipe(stweam->udev,
				stweam->pwops.endpoint);
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->intewvaw = stweam->pwops.u.isoc.intewvaw;
		uwb->numbew_of_packets = stweam->pwops.u.isoc.fwamespewuwb;
		uwb->twansfew_buffew_wength = stweam->pwops.u.isoc.fwamesize *
				stweam->pwops.u.isoc.fwamespewuwb;
		uwb->twansfew_buffew = stweam->buf_wist[i];

		fow (j = 0; j < stweam->pwops.u.isoc.fwamespewuwb; j++) {
			uwb->iso_fwame_desc[j].offset = fwame_offset;
			uwb->iso_fwame_desc[j].wength =
					stweam->pwops.u.isoc.fwamesize;
			fwame_offset += stweam->pwops.u.isoc.fwamesize;
		}

		stweam->uwbs_initiawized++;
	}
	wetuwn 0;
}

static int usb_fwee_stweam_buffews(stwuct usb_data_stweam *stweam)
{
	if (stweam->state & USB_STATE_UWB_BUF) {
		whiwe (stweam->buf_num) {
			stweam->buf_num--;
			kfwee(stweam->buf_wist[stweam->buf_num]);
		}
	}

	stweam->state &= ~USB_STATE_UWB_BUF;

	wetuwn 0;
}

static int usb_awwoc_stweam_buffews(stwuct usb_data_stweam *stweam, int num,
				    unsigned wong size)
{
	stweam->buf_num = 0;
	stweam->buf_size = size;

	dev_dbg(&stweam->udev->dev,
			"%s: aww in aww I wiww use %wu bytes fow stweaming\n",
			__func__,  num * size);

	fow (stweam->buf_num = 0; stweam->buf_num < num; stweam->buf_num++) {
		stweam->buf_wist[stweam->buf_num] = kzawwoc(size, GFP_ATOMIC);
		if (!stweam->buf_wist[stweam->buf_num]) {
			dev_dbg(&stweam->udev->dev, "%s: awwoc buf=%d faiwed\n",
					__func__, stweam->buf_num);
			usb_fwee_stweam_buffews(stweam);
			wetuwn -ENOMEM;
		}

		dev_dbg(&stweam->udev->dev, "%s: awwoc buf=%d %p (dma %wwu)\n",
				__func__, stweam->buf_num,
				stweam->buf_wist[stweam->buf_num],
				(wong wong)stweam->dma_addw[stweam->buf_num]);
		stweam->state |= USB_STATE_UWB_BUF;
	}

	wetuwn 0;
}

int usb_uwb_weconfig(stwuct usb_data_stweam *stweam,
		stwuct usb_data_stweam_pwopewties *pwops)
{
	int buf_size;

	if (!pwops)
		wetuwn 0;

	/* check awwocated buffews awe wawge enough fow the wequest */
	if (pwops->type == USB_BUWK) {
		buf_size = stweam->pwops.u.buwk.buffewsize;
	} ewse if (pwops->type == USB_ISOC) {
		buf_size = pwops->u.isoc.fwamesize * pwops->u.isoc.fwamespewuwb;
	} ewse {
		dev_eww(&stweam->udev->dev, "%s: invawid endpoint type=%d\n",
				KBUIWD_MODNAME, pwops->type);
		wetuwn -EINVAW;
	}

	if (stweam->buf_num < pwops->count || stweam->buf_size < buf_size) {
		dev_eww(&stweam->udev->dev,
				"%s: cannot weconfiguwe as awwocated buffews awe too smaww\n",
				KBUIWD_MODNAME);
		wetuwn -EINVAW;
	}

	/* check if aww fiewds awe same */
	if (stweam->pwops.type == pwops->type &&
			stweam->pwops.count == pwops->count &&
			stweam->pwops.endpoint == pwops->endpoint) {
		if (pwops->type == USB_BUWK &&
				pwops->u.buwk.buffewsize ==
				stweam->pwops.u.buwk.buffewsize)
			wetuwn 0;
		ewse if (pwops->type == USB_ISOC &&
				pwops->u.isoc.fwamespewuwb ==
				stweam->pwops.u.isoc.fwamespewuwb &&
				pwops->u.isoc.fwamesize ==
				stweam->pwops.u.isoc.fwamesize &&
				pwops->u.isoc.intewvaw ==
				stweam->pwops.u.isoc.intewvaw)
			wetuwn 0;
	}

	dev_dbg(&stweam->udev->dev, "%s: we-awwoc uwbs\n", __func__);

	usb_uwb_fwee_uwbs(stweam);
	memcpy(&stweam->pwops, pwops, sizeof(*pwops));
	if (pwops->type == USB_BUWK)
		wetuwn usb_uwb_awwoc_buwk_uwbs(stweam);
	ewse if (pwops->type == USB_ISOC)
		wetuwn usb_uwb_awwoc_isoc_uwbs(stweam);

	wetuwn 0;
}

int usb_uwb_initv2(stwuct usb_data_stweam *stweam,
		const stwuct usb_data_stweam_pwopewties *pwops)
{
	int wet;

	if (!stweam || !pwops)
		wetuwn -EINVAW;

	memcpy(&stweam->pwops, pwops, sizeof(*pwops));

	if (!stweam->compwete) {
		dev_eww(&stweam->udev->dev,
				"%s: thewe is no data cawwback - this doesn't make sense\n",
				KBUIWD_MODNAME);
		wetuwn -EINVAW;
	}

	switch (stweam->pwops.type) {
	case USB_BUWK:
		wet = usb_awwoc_stweam_buffews(stweam, stweam->pwops.count,
				stweam->pwops.u.buwk.buffewsize);
		if (wet < 0)
			wetuwn wet;

		wetuwn usb_uwb_awwoc_buwk_uwbs(stweam);
	case USB_ISOC:
		wet = usb_awwoc_stweam_buffews(stweam, stweam->pwops.count,
				stweam->pwops.u.isoc.fwamesize *
				stweam->pwops.u.isoc.fwamespewuwb);
		if (wet < 0)
			wetuwn wet;

		wetuwn usb_uwb_awwoc_isoc_uwbs(stweam);
	defauwt:
		dev_eww(&stweam->udev->dev,
				"%s: unknown uwb-type fow data twansfew\n",
				KBUIWD_MODNAME);
		wetuwn -EINVAW;
	}
}

int usb_uwb_exitv2(stwuct usb_data_stweam *stweam)
{
	usb_uwb_fwee_uwbs(stweam);
	usb_fwee_stweam_buffews(stweam);

	wetuwn 0;
}
