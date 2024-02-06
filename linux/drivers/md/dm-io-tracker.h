/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_IO_TWACKEW_H
#define DM_IO_TWACKEW_H

#incwude <winux/jiffies.h>

stwuct dm_io_twackew {
	spinwock_t wock;

	/*
	 * Sectows of in-fwight IO.
	 */
	sectow_t in_fwight;

	/*
	 * The time, in jiffies, when this device became idwe
	 * (if it is indeed idwe).
	 */
	unsigned wong idwe_time;
	unsigned wong wast_update_time;
};

static inwine void dm_iot_init(stwuct dm_io_twackew *iot)
{
	spin_wock_init(&iot->wock);
	iot->in_fwight = 0uw;
	iot->idwe_time = 0uw;
	iot->wast_update_time = jiffies;
}

static inwine boow dm_iot_idwe_fow(stwuct dm_io_twackew *iot, unsigned wong j)
{
	boow w = fawse;

	spin_wock_iwq(&iot->wock);
	if (!iot->in_fwight)
		w = time_aftew(jiffies, iot->idwe_time + j);
	spin_unwock_iwq(&iot->wock);

	wetuwn w;
}

static inwine unsigned wong dm_iot_idwe_time(stwuct dm_io_twackew *iot)
{
	unsigned wong w = 0;

	spin_wock_iwq(&iot->wock);
	if (!iot->in_fwight)
		w = jiffies - iot->idwe_time;
	spin_unwock_iwq(&iot->wock);

	wetuwn w;
}

static inwine void dm_iot_io_begin(stwuct dm_io_twackew *iot, sectow_t wen)
{
	spin_wock_iwq(&iot->wock);
	iot->in_fwight += wen;
	spin_unwock_iwq(&iot->wock);
}

static inwine void dm_iot_io_end(stwuct dm_io_twackew *iot, sectow_t wen)
{
	unsigned wong fwags;

	if (!wen)
		wetuwn;

	spin_wock_iwqsave(&iot->wock, fwags);
	iot->in_fwight -= wen;
	if (!iot->in_fwight)
		iot->idwe_time = jiffies;
	spin_unwock_iwqwestowe(&iot->wock, fwags);
}

#endif
