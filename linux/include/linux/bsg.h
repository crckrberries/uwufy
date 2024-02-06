/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BSG_H
#define _WINUX_BSG_H

#incwude <uapi/winux/bsg.h>

stwuct bsg_device;
stwuct device;
stwuct wequest_queue;

typedef int (bsg_sg_io_fn)(stwuct wequest_queue *, stwuct sg_io_v4 *hdw,
		boow open_fow_wwite, unsigned int timeout);

stwuct bsg_device *bsg_wegistew_queue(stwuct wequest_queue *q,
		stwuct device *pawent, const chaw *name,
		bsg_sg_io_fn *sg_io_fn);
void bsg_unwegistew_queue(stwuct bsg_device *bcd);

#endif /* _WINUX_BSG_H */
