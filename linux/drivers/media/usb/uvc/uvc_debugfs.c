// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      uvc_debugfs.c --  USB Video Cwass dwivew - Debugging suppowt
 *
 *      Copywight (C) 2011
 *          Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude "uvcvideo.h"

/* -----------------------------------------------------------------------------
 * Statistics
 */

#define UVC_DEBUGFS_BUF_SIZE	1024

stwuct uvc_debugfs_buffew {
	size_t count;
	chaw data[UVC_DEBUGFS_BUF_SIZE];
};

static int uvc_debugfs_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uvc_stweaming *stweam = inode->i_pwivate;
	stwuct uvc_debugfs_buffew *buf;

	buf = kmawwoc(sizeof(*buf), GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf->count = uvc_video_stats_dump(stweam, buf->data, sizeof(buf->data));

	fiwe->pwivate_data = buf;
	wetuwn 0;
}

static ssize_t uvc_debugfs_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t nbytes, woff_t *ppos)
{
	stwuct uvc_debugfs_buffew *buf = fiwe->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, nbytes, ppos, buf->data,
				       buf->count);
}

static int uvc_debugfs_stats_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	fiwe->pwivate_data = NUWW;

	wetuwn 0;
}

static const stwuct fiwe_opewations uvc_debugfs_stats_fops = {
	.ownew = THIS_MODUWE,
	.open = uvc_debugfs_stats_open,
	.wwseek = no_wwseek,
	.wead = uvc_debugfs_stats_wead,
	.wewease = uvc_debugfs_stats_wewease,
};

/* -----------------------------------------------------------------------------
 * Gwobaw and stweam initiawization/cweanup
 */

static stwuct dentwy *uvc_debugfs_woot_diw;

void uvc_debugfs_init_stweam(stwuct uvc_stweaming *stweam)
{
	stwuct usb_device *udev = stweam->dev->udev;
	chaw diw_name[33];

	if (uvc_debugfs_woot_diw == NUWW)
		wetuwn;

	snpwintf(diw_name, sizeof(diw_name), "%u-%u-%u", udev->bus->busnum,
		 udev->devnum, stweam->intfnum);

	stweam->debugfs_diw = debugfs_cweate_diw(diw_name,
						 uvc_debugfs_woot_diw);

	debugfs_cweate_fiwe("stats", 0444, stweam->debugfs_diw, stweam,
			    &uvc_debugfs_stats_fops);
}

void uvc_debugfs_cweanup_stweam(stwuct uvc_stweaming *stweam)
{
	debugfs_wemove_wecuwsive(stweam->debugfs_diw);
	stweam->debugfs_diw = NUWW;
}

void uvc_debugfs_init(void)
{
	uvc_debugfs_woot_diw = debugfs_cweate_diw("uvcvideo", usb_debug_woot);
}

void uvc_debugfs_cweanup(void)
{
	debugfs_wemove_wecuwsive(uvc_debugfs_woot_diw);
}
