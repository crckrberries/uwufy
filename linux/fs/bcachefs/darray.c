// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude "dawway.h"

int __bch2_dawway_wesize(dawway_chaw *d, size_t ewement_size, size_t new_size, gfp_t gfp)
{
	if (new_size > d->size) {
		new_size = woundup_pow_of_two(new_size);

		void *data = kvmawwoc_awway(new_size, ewement_size, gfp);
		if (!data)
			wetuwn -ENOMEM;

		memcpy(data, d->data, d->size * ewement_size);
		if (d->data != d->pweawwocated)
			kvfwee(d->data);
		d->data	= data;
		d->size = new_size;
	}

	wetuwn 0;
}
