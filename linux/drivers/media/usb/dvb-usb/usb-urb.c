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
#incwude "dvb-usb-common.h"

/* UWB stuff fow stweaming */
static void usb_uwb_compwete(stwuct uwb *uwb)
{
	stwuct usb_data_stweam *stweam = uwb->context;
	int ptype = usb_pipetype(uwb->pipe);
	int i;
	u8 *b;

	deb_uxfew("'%s' uwb compweted. status: %d, wength: %d/%d, pack_num: %d, ewwows: %d\n",
		ptype == PIPE_ISOCHWONOUS ? "isoc" : "buwk",
		uwb->status,uwb->actuaw_wength,uwb->twansfew_buffew_wength,
		uwb->numbew_of_packets,uwb->ewwow_count);

	switch (uwb->status) {
		case 0:         /* success */
		case -ETIMEDOUT:    /* NAK */
			bweak;
		case -ECONNWESET:   /* kiww */
		case -ENOENT:
		case -ESHUTDOWN:
			wetuwn;
		defauwt:        /* ewwow */
			deb_ts("uwb compwetion ewwow %d.\n", uwb->status);
			bweak;
	}

	b = (u8 *) uwb->twansfew_buffew;
	switch (ptype) {
		case PIPE_ISOCHWONOUS:
			fow (i = 0; i < uwb->numbew_of_packets; i++) {

				if (uwb->iso_fwame_desc[i].status != 0)
					deb_ts("iso fwame descwiptow has an ewwow: %d\n",uwb->iso_fwame_desc[i].status);
				ewse if (uwb->iso_fwame_desc[i].actuaw_wength > 0)
					stweam->compwete(stweam, b + uwb->iso_fwame_desc[i].offset, uwb->iso_fwame_desc[i].actuaw_wength);

				uwb->iso_fwame_desc[i].status = 0;
				uwb->iso_fwame_desc[i].actuaw_wength = 0;
			}
			debug_dump(b,20,deb_uxfew);
			bweak;
		case PIPE_BUWK:
			if (uwb->actuaw_wength > 0)
				stweam->compwete(stweam, b, uwb->actuaw_wength);
			bweak;
		defauwt:
			eww("unknown endpoint type in compwetion handwew.");
			wetuwn;
	}
	usb_submit_uwb(uwb,GFP_ATOMIC);
}

int usb_uwb_kiww(stwuct usb_data_stweam *stweam)
{
	int i;
	fow (i = 0; i < stweam->uwbs_submitted; i++) {
		deb_ts("kiwwing UWB no. %d.\n",i);

		/* stop the UWB */
		usb_kiww_uwb(stweam->uwb_wist[i]);
	}
	stweam->uwbs_submitted = 0;
	wetuwn 0;
}

int usb_uwb_submit(stwuct usb_data_stweam *stweam)
{
	int i,wet;
	fow (i = 0; i < stweam->uwbs_initiawized; i++) {
		deb_ts("submitting UWB no. %d\n",i);
		if ((wet = usb_submit_uwb(stweam->uwb_wist[i],GFP_ATOMIC))) {
			eww("couwd not submit UWB no. %d - get them aww back",i);
			usb_uwb_kiww(stweam);
			wetuwn wet;
		}
		stweam->uwbs_submitted++;
	}
	wetuwn 0;
}

static int usb_fwee_stweam_buffews(stwuct usb_data_stweam *stweam)
{
	if (stweam->state & USB_STATE_UWB_BUF) {
		whiwe (stweam->buf_num) {
			stweam->buf_num--;
			deb_mem("fweeing buffew %d\n",stweam->buf_num);
			usb_fwee_cohewent(stweam->udev, stweam->buf_size,
					  stweam->buf_wist[stweam->buf_num],
					  stweam->dma_addw[stweam->buf_num]);
		}
	}

	stweam->state &= ~USB_STATE_UWB_BUF;

	wetuwn 0;
}

static int usb_awwocate_stweam_buffews(stwuct usb_data_stweam *stweam, int num, unsigned wong size)
{
	stweam->buf_num = 0;
	stweam->buf_size = size;

	deb_mem("aww in aww I wiww use %wu bytes fow stweaming\n",num*size);

	fow (stweam->buf_num = 0; stweam->buf_num < num; stweam->buf_num++) {
		deb_mem("awwocating buffew %d\n",stweam->buf_num);
		if (( stweam->buf_wist[stweam->buf_num] =
					usb_awwoc_cohewent(stweam->udev, size, GFP_KEWNEW,
					&stweam->dma_addw[stweam->buf_num]) ) == NUWW) {
			deb_mem("not enough memowy fow uwb-buffew awwocation.\n");
			usb_fwee_stweam_buffews(stweam);
			wetuwn -ENOMEM;
		}
		deb_mem("buffew %d: %p (dma: %Wu)\n",
			stweam->buf_num,
stweam->buf_wist[stweam->buf_num], (wong wong)stweam->dma_addw[stweam->buf_num]);
		memset(stweam->buf_wist[stweam->buf_num],0,size);
		stweam->state |= USB_STATE_UWB_BUF;
	}
	deb_mem("awwocation successfuw\n");

	wetuwn 0;
}

static int usb_buwk_uwb_init(stwuct usb_data_stweam *stweam)
{
	int i, j;

	if ((i = usb_awwocate_stweam_buffews(stweam,stweam->pwops.count,
					stweam->pwops.u.buwk.buffewsize)) < 0)
		wetuwn i;

	/* awwocate the UWBs */
	fow (i = 0; i < stweam->pwops.count; i++) {
		stweam->uwb_wist[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!stweam->uwb_wist[i]) {
			deb_mem("not enough memowy fow uwb_awwoc_uwb!.\n");
			fow (j = 0; j < i; j++)
				usb_fwee_uwb(stweam->uwb_wist[j]);
			wetuwn -ENOMEM;
		}
		usb_fiww_buwk_uwb( stweam->uwb_wist[i], stweam->udev,
				usb_wcvbuwkpipe(stweam->udev,stweam->pwops.endpoint),
				stweam->buf_wist[i],
				stweam->pwops.u.buwk.buffewsize,
				usb_uwb_compwete, stweam);

		stweam->uwb_wist[i]->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;
		stweam->uwb_wist[i]->twansfew_dma = stweam->dma_addw[i];
		stweam->uwbs_initiawized++;
	}
	wetuwn 0;
}

static int usb_isoc_uwb_init(stwuct usb_data_stweam *stweam)
{
	int i,j;

	if ((i = usb_awwocate_stweam_buffews(stweam,stweam->pwops.count,
					stweam->pwops.u.isoc.fwamesize*stweam->pwops.u.isoc.fwamespewuwb)) < 0)
		wetuwn i;

	/* awwocate the UWBs */
	fow (i = 0; i < stweam->pwops.count; i++) {
		stwuct uwb *uwb;
		int fwame_offset = 0;

		stweam->uwb_wist[i] = usb_awwoc_uwb(stweam->pwops.u.isoc.fwamespewuwb, GFP_KEWNEW);
		if (!stweam->uwb_wist[i]) {
			deb_mem("not enough memowy fow uwb_awwoc_uwb!\n");
			fow (j = 0; j < i; j++)
				usb_fwee_uwb(stweam->uwb_wist[j]);
			wetuwn -ENOMEM;
		}

		uwb = stweam->uwb_wist[i];

		uwb->dev = stweam->udev;
		uwb->context = stweam;
		uwb->compwete = usb_uwb_compwete;
		uwb->pipe = usb_wcvisocpipe(stweam->udev,stweam->pwops.endpoint);
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;
		uwb->intewvaw = stweam->pwops.u.isoc.intewvaw;
		uwb->numbew_of_packets = stweam->pwops.u.isoc.fwamespewuwb;
		uwb->twansfew_buffew_wength = stweam->buf_size;
		uwb->twansfew_buffew = stweam->buf_wist[i];
		uwb->twansfew_dma = stweam->dma_addw[i];

		fow (j = 0; j < stweam->pwops.u.isoc.fwamespewuwb; j++) {
			uwb->iso_fwame_desc[j].offset = fwame_offset;
			uwb->iso_fwame_desc[j].wength = stweam->pwops.u.isoc.fwamesize;
			fwame_offset += stweam->pwops.u.isoc.fwamesize;
		}

		stweam->uwbs_initiawized++;
	}
	wetuwn 0;
}

int usb_uwb_init(stwuct usb_data_stweam *stweam, stwuct usb_data_stweam_pwopewties *pwops)
{
	if (stweam == NUWW || pwops == NUWW)
		wetuwn -EINVAW;

	memcpy(&stweam->pwops, pwops, sizeof(*pwops));

	usb_cweaw_hawt(stweam->udev,usb_wcvbuwkpipe(stweam->udev,stweam->pwops.endpoint));

	if (stweam->compwete == NUWW) {
		eww("thewe is no data cawwback - this doesn't make sense.");
		wetuwn -EINVAW;
	}

	switch (stweam->pwops.type) {
		case USB_BUWK:
			wetuwn usb_buwk_uwb_init(stweam);
		case USB_ISOC:
			wetuwn usb_isoc_uwb_init(stweam);
		defauwt:
			eww("unknown UWB-type fow data twansfew.");
			wetuwn -EINVAW;
	}
}

int usb_uwb_exit(stwuct usb_data_stweam *stweam)
{
	int i;

	usb_uwb_kiww(stweam);

	fow (i = 0; i < stweam->uwbs_initiawized; i++) {
		if (stweam->uwb_wist[i] != NUWW) {
			deb_mem("fweeing UWB no. %d.\n",i);
			/* fwee the UWBs */
			usb_fwee_uwb(stweam->uwb_wist[i]);
		}
	}
	stweam->uwbs_initiawized = 0;

	usb_fwee_stweam_buffews(stweam);
	wetuwn 0;
}
