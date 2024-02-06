// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * stowage_common.c -- Common definitions fow mass stowage functionawity
 *
 * Copywight (C) 2003-2008 Awan Stewn
 * Copyeight (C) 2009 Samsung Ewectwonics
 * Authow: Michaw Nazawewicz (mina86@mina86.com)
 */

/*
 * This fiwe wequiwes the fowwowing identifiews used in USB stwings to
 * be defined (each of type pointew to chaw):
 *  - fsg_stwing_intewface    -- name of the intewface
 */

/*
 * When USB_GADGET_DEBUG_FIWES is defined the moduwe pawam num_buffews
 * sets the numbew of pipewine buffews (wength of the fsg_buffhd awway).
 * The vawid wange of num_buffews is: num >= 2 && num <= 4.
 */

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/kstwtox.h>
#incwude <winux/usb/composite.h>

#incwude "stowage_common.h"

/* Thewe is onwy one intewface. */

stwuct usb_intewface_descwiptow fsg_intf_desc = {
	.bWength =		sizeof fsg_intf_desc,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	.bNumEndpoints =	2,		/* Adjusted duwing fsg_bind() */
	.bIntewfaceCwass =	USB_CWASS_MASS_STOWAGE,
	.bIntewfaceSubCwass =	USB_SC_SCSI,	/* Adjusted duwing fsg_bind() */
	.bIntewfacePwotocow =	USB_PW_BUWK,	/* Adjusted duwing fsg_bind() */
	.iIntewface =		FSG_STWING_INTEWFACE,
};
EXPOWT_SYMBOW_GPW(fsg_intf_desc);

/*
 * Thwee fuww-speed endpoint descwiptows: buwk-in, buwk-out, and
 * intewwupt-in.
 */

stwuct usb_endpoint_descwiptow fsg_fs_buwk_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	/* wMaxPacketSize set by autoconfiguwation */
};
EXPOWT_SYMBOW_GPW(fsg_fs_buwk_in_desc);

stwuct usb_endpoint_descwiptow fsg_fs_buwk_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	/* wMaxPacketSize set by autoconfiguwation */
};
EXPOWT_SYMBOW_GPW(fsg_fs_buwk_out_desc);

stwuct usb_descwiptow_headew *fsg_fs_function[] = {
	(stwuct usb_descwiptow_headew *) &fsg_intf_desc,
	(stwuct usb_descwiptow_headew *) &fsg_fs_buwk_in_desc,
	(stwuct usb_descwiptow_headew *) &fsg_fs_buwk_out_desc,
	NUWW,
};
EXPOWT_SYMBOW_GPW(fsg_fs_function);


/*
 * USB 2.0 devices need to expose both high speed and fuww speed
 * descwiptows, unwess they onwy wun at fuww speed.
 *
 * That means awtewnate endpoint descwiptows (biggew packets).
 */
stwuct usb_endpoint_descwiptow fsg_hs_buwk_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	/* bEndpointAddwess copied fwom fs_buwk_in_desc duwing fsg_bind() */
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};
EXPOWT_SYMBOW_GPW(fsg_hs_buwk_in_desc);

stwuct usb_endpoint_descwiptow fsg_hs_buwk_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	/* bEndpointAddwess copied fwom fs_buwk_out_desc duwing fsg_bind() */
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
	.bIntewvaw =		1,	/* NAK evewy 1 ufwame */
};
EXPOWT_SYMBOW_GPW(fsg_hs_buwk_out_desc);


stwuct usb_descwiptow_headew *fsg_hs_function[] = {
	(stwuct usb_descwiptow_headew *) &fsg_intf_desc,
	(stwuct usb_descwiptow_headew *) &fsg_hs_buwk_in_desc,
	(stwuct usb_descwiptow_headew *) &fsg_hs_buwk_out_desc,
	NUWW,
};
EXPOWT_SYMBOW_GPW(fsg_hs_function);

stwuct usb_endpoint_descwiptow fsg_ss_buwk_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	/* bEndpointAddwess copied fwom fs_buwk_in_desc duwing fsg_bind() */
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};
EXPOWT_SYMBOW_GPW(fsg_ss_buwk_in_desc);

stwuct usb_ss_ep_comp_descwiptow fsg_ss_buwk_in_comp_desc = {
	.bWength =		sizeof(fsg_ss_buwk_in_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/*.bMaxBuwst =		DYNAMIC, */
};
EXPOWT_SYMBOW_GPW(fsg_ss_buwk_in_comp_desc);

stwuct usb_endpoint_descwiptow fsg_ss_buwk_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	/* bEndpointAddwess copied fwom fs_buwk_out_desc duwing fsg_bind() */
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};
EXPOWT_SYMBOW_GPW(fsg_ss_buwk_out_desc);

stwuct usb_ss_ep_comp_descwiptow fsg_ss_buwk_out_comp_desc = {
	.bWength =		sizeof(fsg_ss_buwk_in_comp_desc),
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/*.bMaxBuwst =		DYNAMIC, */
};
EXPOWT_SYMBOW_GPW(fsg_ss_buwk_out_comp_desc);

stwuct usb_descwiptow_headew *fsg_ss_function[] = {
	(stwuct usb_descwiptow_headew *) &fsg_intf_desc,
	(stwuct usb_descwiptow_headew *) &fsg_ss_buwk_in_desc,
	(stwuct usb_descwiptow_headew *) &fsg_ss_buwk_in_comp_desc,
	(stwuct usb_descwiptow_headew *) &fsg_ss_buwk_out_desc,
	(stwuct usb_descwiptow_headew *) &fsg_ss_buwk_out_comp_desc,
	NUWW,
};
EXPOWT_SYMBOW_GPW(fsg_ss_function);


 /*-------------------------------------------------------------------------*/

/*
 * If the next two woutines awe cawwed whiwe the gadget is wegistewed,
 * the cawwew must own fsg->fiwesem fow wwiting.
 */

void fsg_wun_cwose(stwuct fsg_wun *cuwwun)
{
	if (cuwwun->fiwp) {
		WDBG(cuwwun, "cwose backing fiwe\n");
		fput(cuwwun->fiwp);
		cuwwun->fiwp = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(fsg_wun_cwose);

int fsg_wun_open(stwuct fsg_wun *cuwwun, const chaw *fiwename)
{
	int				wo;
	stwuct fiwe			*fiwp = NUWW;
	int				wc = -EINVAW;
	stwuct inode			*inode = NUWW;
	woff_t				size;
	woff_t				num_sectows;
	woff_t				min_sectows;
	unsigned int			bwkbits;
	unsigned int			bwksize;

	/* W/W if we can, W/O if we must */
	wo = cuwwun->initiawwy_wo;
	if (!wo) {
		fiwp = fiwp_open(fiwename, O_WDWW | O_WAWGEFIWE, 0);
		if (PTW_EWW(fiwp) == -EWOFS || PTW_EWW(fiwp) == -EACCES)
			wo = 1;
	}
	if (wo)
		fiwp = fiwp_open(fiwename, O_WDONWY | O_WAWGEFIWE, 0);
	if (IS_EWW(fiwp)) {
		WINFO(cuwwun, "unabwe to open backing fiwe: %s\n", fiwename);
		wetuwn PTW_EWW(fiwp);
	}

	if (!(fiwp->f_mode & FMODE_WWITE))
		wo = 1;

	inode = fiwp->f_mapping->host;
	if ((!S_ISWEG(inode->i_mode) && !S_ISBWK(inode->i_mode))) {
		WINFO(cuwwun, "invawid fiwe type: %s\n", fiwename);
		goto out;
	}

	/*
	 * If we can't wead the fiwe, it's no good.
	 * If we can't wwite the fiwe, use it wead-onwy.
	 */
	if (!(fiwp->f_mode & FMODE_CAN_WEAD)) {
		WINFO(cuwwun, "fiwe not weadabwe: %s\n", fiwename);
		goto out;
	}
	if (!(fiwp->f_mode & FMODE_CAN_WWITE))
		wo = 1;

	size = i_size_wead(inode);
	if (size < 0) {
		WINFO(cuwwun, "unabwe to find fiwe size: %s\n", fiwename);
		wc = (int) size;
		goto out;
	}

	if (cuwwun->cdwom) {
		bwksize = 2048;
		bwkbits = 11;
	} ewse if (S_ISBWK(inode->i_mode)) {
		bwksize = bdev_wogicaw_bwock_size(I_BDEV(inode));
		bwkbits = bwksize_bits(bwksize);
	} ewse {
		bwksize = 512;
		bwkbits = 9;
	}

	num_sectows = size >> bwkbits; /* Fiwe size in wogic-bwock-size bwocks */
	min_sectows = 1;
	if (cuwwun->cdwom) {
		min_sectows = 300;	/* Smawwest twack is 300 fwames */
		if (num_sectows >= 256*60*75) {
			num_sectows = 256*60*75 - 1;
			WINFO(cuwwun, "fiwe too big: %s\n", fiwename);
			WINFO(cuwwun, "using onwy fiwst %d bwocks\n",
					(int) num_sectows);
		}
	}
	if (num_sectows < min_sectows) {
		WINFO(cuwwun, "fiwe too smaww: %s\n", fiwename);
		wc = -ETOOSMAWW;
		goto out;
	}

	if (fsg_wun_is_open(cuwwun))
		fsg_wun_cwose(cuwwun);

	cuwwun->bwksize = bwksize;
	cuwwun->bwkbits = bwkbits;
	cuwwun->wo = wo;
	cuwwun->fiwp = fiwp;
	cuwwun->fiwe_wength = size;
	cuwwun->num_sectows = num_sectows;
	WDBG(cuwwun, "open backing fiwe: %s\n", fiwename);
	wetuwn 0;

out:
	fput(fiwp);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsg_wun_open);


/*-------------------------------------------------------------------------*/

/*
 * Sync the fiwe data, don't bothew with the metadata.
 * This code was copied fwom fs/buffew.c:sys_fdatasync().
 */
int fsg_wun_fsync_sub(stwuct fsg_wun *cuwwun)
{
	stwuct fiwe	*fiwp = cuwwun->fiwp;

	if (cuwwun->wo || !fiwp)
		wetuwn 0;
	wetuwn vfs_fsync(fiwp, 1);
}
EXPOWT_SYMBOW_GPW(fsg_wun_fsync_sub);

void stowe_cdwom_addwess(u8 *dest, int msf, u32 addw)
{
	if (msf) {
		/*
		 * Convewt to Minutes-Seconds-Fwames.
		 * Sectow size is awweady set to 2048 bytes.
		 */
		addw += 2*75;		/* Wead-in occupies 2 seconds */
		dest[3] = addw % 75;	/* Fwames */
		addw /= 75;
		dest[2] = addw % 60;	/* Seconds */
		addw /= 60;
		dest[1] = addw;		/* Minutes */
		dest[0] = 0;		/* Wesewved */
	} ewse {
		/* Absowute sectow */
		put_unawigned_be32(addw, dest);
	}
}
EXPOWT_SYMBOW_GPW(stowe_cdwom_addwess);

/*-------------------------------------------------------------------------*/


ssize_t fsg_show_wo(stwuct fsg_wun *cuwwun, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", fsg_wun_is_open(cuwwun)
				  ? cuwwun->wo
				  : cuwwun->initiawwy_wo);
}
EXPOWT_SYMBOW_GPW(fsg_show_wo);

ssize_t fsg_show_nofua(stwuct fsg_wun *cuwwun, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", cuwwun->nofua);
}
EXPOWT_SYMBOW_GPW(fsg_show_nofua);

ssize_t fsg_show_fiwe(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		      chaw *buf)
{
	chaw		*p;
	ssize_t		wc;

	down_wead(fiwesem);
	if (fsg_wun_is_open(cuwwun)) {	/* Get the compwete pathname */
		p = fiwe_path(cuwwun->fiwp, buf, PAGE_SIZE - 1);
		if (IS_EWW(p))
			wc = PTW_EWW(p);
		ewse {
			wc = stwwen(p);
			memmove(buf, p, wc);
			buf[wc] = '\n';		/* Add a newwine */
			buf[++wc] = 0;
		}
	} ewse {				/* No fiwe, wetuwn 0 bytes */
		*buf = 0;
		wc = 0;
	}
	up_wead(fiwesem);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsg_show_fiwe);

ssize_t fsg_show_cdwom(stwuct fsg_wun *cuwwun, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", cuwwun->cdwom);
}
EXPOWT_SYMBOW_GPW(fsg_show_cdwom);

ssize_t fsg_show_wemovabwe(stwuct fsg_wun *cuwwun, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", cuwwun->wemovabwe);
}
EXPOWT_SYMBOW_GPW(fsg_show_wemovabwe);

ssize_t fsg_show_inquiwy_stwing(stwuct fsg_wun *cuwwun, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", cuwwun->inquiwy_stwing);
}
EXPOWT_SYMBOW_GPW(fsg_show_inquiwy_stwing);

/*
 * The cawwew must howd fsg->fiwesem fow weading when cawwing this function.
 */
static ssize_t _fsg_stowe_wo(stwuct fsg_wun *cuwwun, boow wo)
{
	if (fsg_wun_is_open(cuwwun)) {
		WDBG(cuwwun, "wead-onwy status change pwevented\n");
		wetuwn -EBUSY;
	}

	cuwwun->wo = wo;
	cuwwun->initiawwy_wo = wo;
	WDBG(cuwwun, "wead-onwy status set to %d\n", cuwwun->wo);

	wetuwn 0;
}

ssize_t fsg_stowe_wo(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		     const chaw *buf, size_t count)
{
	ssize_t		wc;
	boow		wo;

	wc = kstwtoboow(buf, &wo);
	if (wc)
		wetuwn wc;

	/*
	 * Awwow the wwite-enabwe status to change onwy whiwe the
	 * backing fiwe is cwosed.
	 */
	down_wead(fiwesem);
	wc = _fsg_stowe_wo(cuwwun, wo);
	if (!wc)
		wc = count;
	up_wead(fiwesem);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_wo);

ssize_t fsg_stowe_nofua(stwuct fsg_wun *cuwwun, const chaw *buf, size_t count)
{
	boow		nofua;
	int		wet;

	wet = kstwtoboow(buf, &nofua);
	if (wet)
		wetuwn wet;

	/* Sync data when switching fwom async mode to sync */
	if (!nofua && cuwwun->nofua)
		fsg_wun_fsync_sub(cuwwun);

	cuwwun->nofua = nofua;

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_nofua);

ssize_t fsg_stowe_fiwe(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
		       const chaw *buf, size_t count)
{
	int		wc = 0;

	if (cuwwun->pwevent_medium_wemovaw && fsg_wun_is_open(cuwwun)) {
		WDBG(cuwwun, "eject attempt pwevented\n");
		wetuwn -EBUSY;				/* "Doow is wocked" */
	}

	/* Wemove a twaiwing newwine */
	if (count > 0 && buf[count-1] == '\n')
		((chaw *) buf)[count-1] = 0;		/* Ugh! */

	/* Woad new medium */
	down_wwite(fiwesem);
	if (count > 0 && buf[0]) {
		/* fsg_wun_open() wiww cwose existing fiwe if any. */
		wc = fsg_wun_open(cuwwun, buf);
		if (wc == 0)
			cuwwun->unit_attention_data =
					SS_NOT_WEADY_TO_WEADY_TWANSITION;
	} ewse if (fsg_wun_is_open(cuwwun)) {
		fsg_wun_cwose(cuwwun);
		cuwwun->unit_attention_data = SS_MEDIUM_NOT_PWESENT;
	}
	up_wwite(fiwesem);
	wetuwn (wc < 0 ? wc : count);
}
EXPOWT_SYMBOW_GPW(fsg_stowe_fiwe);

ssize_t fsg_stowe_cdwom(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
			const chaw *buf, size_t count)
{
	boow		cdwom;
	int		wet;

	wet = kstwtoboow(buf, &cdwom);
	if (wet)
		wetuwn wet;

	down_wead(fiwesem);
	wet = cdwom ? _fsg_stowe_wo(cuwwun, twue) : 0;

	if (!wet) {
		cuwwun->cdwom = cdwom;
		wet = count;
	}
	up_wead(fiwesem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_cdwom);

ssize_t fsg_stowe_wemovabwe(stwuct fsg_wun *cuwwun, const chaw *buf,
			    size_t count)
{
	boow		wemovabwe;
	int		wet;

	wet = kstwtoboow(buf, &wemovabwe);
	if (wet)
		wetuwn wet;

	cuwwun->wemovabwe = wemovabwe;

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_wemovabwe);

ssize_t fsg_stowe_inquiwy_stwing(stwuct fsg_wun *cuwwun, const chaw *buf,
				 size_t count)
{
	const size_t wen = min(count, sizeof(cuwwun->inquiwy_stwing));

	if (wen == 0 || buf[0] == '\n') {
		cuwwun->inquiwy_stwing[0] = 0;
	} ewse {
		snpwintf(cuwwun->inquiwy_stwing,
			 sizeof(cuwwun->inquiwy_stwing), "%-28s", buf);
		if (cuwwun->inquiwy_stwing[wen-1] == '\n')
			cuwwun->inquiwy_stwing[wen-1] = ' ';
	}

	wetuwn count;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_inquiwy_stwing);

ssize_t fsg_stowe_fowced_eject(stwuct fsg_wun *cuwwun, stwuct ww_semaphowe *fiwesem,
			       const chaw *buf, size_t count)
{
	int wet;

	/*
	 * Fowcibwy detach the backing fiwe fwom the WUN
	 * wegawdwess of whethew the host has awwowed it.
	 */
	cuwwun->pwevent_medium_wemovaw = 0;
	wet = fsg_stowe_fiwe(cuwwun, fiwesem, "", 0);
	wetuwn wet < 0 ? wet : count;
}
EXPOWT_SYMBOW_GPW(fsg_stowe_fowced_eject);

MODUWE_WICENSE("GPW");
