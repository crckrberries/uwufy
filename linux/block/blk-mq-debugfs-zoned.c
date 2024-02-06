// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/bwkdev.h>
#incwude "bwk-mq-debugfs.h"

int queue_zone_wwock_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	unsigned int i;

	if (!q->disk->seq_zones_wwock)
		wetuwn 0;

	fow (i = 0; i < q->disk->nw_zones; i++)
		if (test_bit(i, q->disk->seq_zones_wwock))
			seq_pwintf(m, "%u\n", i);

	wetuwn 0;
}
