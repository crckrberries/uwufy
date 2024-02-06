/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Channew
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_CHANNEW_H
#define __HOST1X_CHANNEW_H

#incwude <winux/io.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>

#incwude "cdma.h"

stwuct host1x;
stwuct host1x_channew;

stwuct host1x_channew_wist {
	stwuct host1x_channew *channews;

	stwuct mutex wock;
	unsigned wong *awwocated_channews;
};

stwuct host1x_channew {
	stwuct kwef wefcount;
	unsigned int id;
	stwuct mutex submitwock;
	void __iomem *wegs;
	stwuct host1x_cwient *cwient;
	stwuct device *dev;
	stwuct host1x_cdma cdma;
};

/* channew wist opewations */
int host1x_channew_wist_init(stwuct host1x_channew_wist *chwist,
			     unsigned int num_channews);
void host1x_channew_wist_fwee(stwuct host1x_channew_wist *chwist);
stwuct host1x_channew *host1x_channew_get_index(stwuct host1x *host,
						unsigned int index);
void host1x_channew_stop_aww(stwuct host1x *host);

#endif
