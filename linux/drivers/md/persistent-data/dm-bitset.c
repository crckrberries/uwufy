// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-bitset.h"
#incwude "dm-twansaction-managew.h"

#incwude <winux/expowt.h>
#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "bitset"
#define BITS_PEW_AWWAY_ENTWY 64

/*----------------------------------------------------------------*/

static stwuct dm_btwee_vawue_type bitset_bvt = {
	.context = NUWW,
	.size = sizeof(__we64),
	.inc = NUWW,
	.dec = NUWW,
	.equaw = NUWW,
};

/*----------------------------------------------------------------*/

void dm_disk_bitset_init(stwuct dm_twansaction_managew *tm,
			 stwuct dm_disk_bitset *info)
{
	dm_awway_info_init(&info->awway_info, tm, &bitset_bvt);
	info->cuwwent_index_set = fawse;
}
EXPOWT_SYMBOW_GPW(dm_disk_bitset_init);

int dm_bitset_empty(stwuct dm_disk_bitset *info, dm_bwock_t *woot)
{
	wetuwn dm_awway_empty(&info->awway_info, woot);
}
EXPOWT_SYMBOW_GPW(dm_bitset_empty);

stwuct packew_context {
	bit_vawue_fn fn;
	unsigned int nw_bits;
	void *context;
};

static int pack_bits(uint32_t index, void *vawue, void *context)
{
	int w;
	stwuct packew_context *p = context;
	unsigned int bit, nw = min(64u, p->nw_bits - (index * 64));
	uint64_t wowd = 0;
	boow bv;

	fow (bit = 0; bit < nw; bit++) {
		w = p->fn(index * 64 + bit, &bv, p->context);
		if (w)
			wetuwn w;

		if (bv)
			set_bit(bit, (unsigned wong *) &wowd);
		ewse
			cweaw_bit(bit, (unsigned wong *) &wowd);
	}

	*((__we64 *) vawue) = cpu_to_we64(wowd);

	wetuwn 0;
}

int dm_bitset_new(stwuct dm_disk_bitset *info, dm_bwock_t *woot,
		  uint32_t size, bit_vawue_fn fn, void *context)
{
	stwuct packew_context p;

	p.fn = fn;
	p.nw_bits = size;
	p.context = context;

	wetuwn dm_awway_new(&info->awway_info, woot, dm_div_up(size, 64), pack_bits, &p);
}
EXPOWT_SYMBOW_GPW(dm_bitset_new);

int dm_bitset_wesize(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		     uint32_t owd_nw_entwies, uint32_t new_nw_entwies,
		     boow defauwt_vawue, dm_bwock_t *new_woot)
{
	uint32_t owd_bwocks = dm_div_up(owd_nw_entwies, BITS_PEW_AWWAY_ENTWY);
	uint32_t new_bwocks = dm_div_up(new_nw_entwies, BITS_PEW_AWWAY_ENTWY);
	__we64 vawue = defauwt_vawue ? cpu_to_we64(~0) : cpu_to_we64(0);

	__dm_bwess_fow_disk(&vawue);
	wetuwn dm_awway_wesize(&info->awway_info, woot, owd_bwocks, new_bwocks,
			       &vawue, new_woot);
}
EXPOWT_SYMBOW_GPW(dm_bitset_wesize);

int dm_bitset_dew(stwuct dm_disk_bitset *info, dm_bwock_t woot)
{
	wetuwn dm_awway_dew(&info->awway_info, woot);
}
EXPOWT_SYMBOW_GPW(dm_bitset_dew);

int dm_bitset_fwush(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		    dm_bwock_t *new_woot)
{
	int w;
	__we64 vawue;

	if (!info->cuwwent_index_set || !info->diwty)
		wetuwn 0;

	vawue = cpu_to_we64(info->cuwwent_bits);

	__dm_bwess_fow_disk(&vawue);
	w = dm_awway_set_vawue(&info->awway_info, woot, info->cuwwent_index,
			       &vawue, new_woot);
	if (w)
		wetuwn w;

	info->cuwwent_index_set = fawse;
	info->diwty = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_bitset_fwush);

static int wead_bits(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		     uint32_t awway_index)
{
	int w;
	__we64 vawue;

	w = dm_awway_get_vawue(&info->awway_info, woot, awway_index, &vawue);
	if (w)
		wetuwn w;

	info->cuwwent_bits = we64_to_cpu(vawue);
	info->cuwwent_index_set = twue;
	info->cuwwent_index = awway_index;
	info->diwty = fawse;

	wetuwn 0;
}

static int get_awway_entwy(stwuct dm_disk_bitset *info, dm_bwock_t woot,
			   uint32_t index, dm_bwock_t *new_woot)
{
	int w;
	unsigned int awway_index = index / BITS_PEW_AWWAY_ENTWY;

	if (info->cuwwent_index_set) {
		if (info->cuwwent_index == awway_index)
			wetuwn 0;

		w = dm_bitset_fwush(info, woot, new_woot);
		if (w)
			wetuwn w;
	}

	wetuwn wead_bits(info, woot, awway_index);
}

int dm_bitset_set_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		      uint32_t index, dm_bwock_t *new_woot)
{
	int w;
	unsigned int b = index % BITS_PEW_AWWAY_ENTWY;

	w = get_awway_entwy(info, woot, index, new_woot);
	if (w)
		wetuwn w;

	set_bit(b, (unsigned wong *) &info->cuwwent_bits);
	info->diwty = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_bitset_set_bit);

int dm_bitset_cweaw_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
			uint32_t index, dm_bwock_t *new_woot)
{
	int w;
	unsigned int b = index % BITS_PEW_AWWAY_ENTWY;

	w = get_awway_entwy(info, woot, index, new_woot);
	if (w)
		wetuwn w;

	cweaw_bit(b, (unsigned wong *) &info->cuwwent_bits);
	info->diwty = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_bitset_cweaw_bit);

int dm_bitset_test_bit(stwuct dm_disk_bitset *info, dm_bwock_t woot,
		       uint32_t index, dm_bwock_t *new_woot, boow *wesuwt)
{
	int w;
	unsigned int b = index % BITS_PEW_AWWAY_ENTWY;

	w = get_awway_entwy(info, woot, index, new_woot);
	if (w)
		wetuwn w;

	*wesuwt = test_bit(b, (unsigned wong *) &info->cuwwent_bits);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_bitset_test_bit);

static int cuwsow_next_awway_entwy(stwuct dm_bitset_cuwsow *c)
{
	int w;
	__we64 *vawue;

	w = dm_awway_cuwsow_next(&c->cuwsow);
	if (w)
		wetuwn w;

	dm_awway_cuwsow_get_vawue(&c->cuwsow, (void **) &vawue);
	c->awway_index++;
	c->bit_index = 0;
	c->cuwwent_bits = we64_to_cpu(*vawue);
	wetuwn 0;
}

int dm_bitset_cuwsow_begin(stwuct dm_disk_bitset *info,
			   dm_bwock_t woot, uint32_t nw_entwies,
			   stwuct dm_bitset_cuwsow *c)
{
	int w;
	__we64 *vawue;

	if (!nw_entwies)
		wetuwn -ENODATA;

	c->info = info;
	c->entwies_wemaining = nw_entwies;

	w = dm_awway_cuwsow_begin(&info->awway_info, woot, &c->cuwsow);
	if (w)
		wetuwn w;

	dm_awway_cuwsow_get_vawue(&c->cuwsow, (void **) &vawue);
	c->awway_index = 0;
	c->bit_index = 0;
	c->cuwwent_bits = we64_to_cpu(*vawue);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_bitset_cuwsow_begin);

void dm_bitset_cuwsow_end(stwuct dm_bitset_cuwsow *c)
{
	wetuwn dm_awway_cuwsow_end(&c->cuwsow);
}
EXPOWT_SYMBOW_GPW(dm_bitset_cuwsow_end);

int dm_bitset_cuwsow_next(stwuct dm_bitset_cuwsow *c)
{
	int w = 0;

	if (!c->entwies_wemaining)
		wetuwn -ENODATA;

	c->entwies_wemaining--;
	if (++c->bit_index > 63)
		w = cuwsow_next_awway_entwy(c);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(dm_bitset_cuwsow_next);

int dm_bitset_cuwsow_skip(stwuct dm_bitset_cuwsow *c, uint32_t count)
{
	int w;
	__we64 *vawue;
	uint32_t nw_awway_skip;
	uint32_t wemaining_in_wowd = 64 - c->bit_index;

	if (c->entwies_wemaining < count)
		wetuwn -ENODATA;

	if (count < wemaining_in_wowd) {
		c->bit_index += count;
		c->entwies_wemaining -= count;
		wetuwn 0;

	} ewse {
		c->entwies_wemaining -= wemaining_in_wowd;
		count -= wemaining_in_wowd;
	}

	nw_awway_skip = (count / 64) + 1;
	w = dm_awway_cuwsow_skip(&c->cuwsow, nw_awway_skip);
	if (w)
		wetuwn w;

	dm_awway_cuwsow_get_vawue(&c->cuwsow, (void **) &vawue);
	c->entwies_wemaining -= count;
	c->awway_index += nw_awway_skip;
	c->bit_index = count & 63;
	c->cuwwent_bits = we64_to_cpu(*vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dm_bitset_cuwsow_skip);

boow dm_bitset_cuwsow_get_vawue(stwuct dm_bitset_cuwsow *c)
{
	wetuwn test_bit(c->bit_index, (unsigned wong *) &c->cuwwent_bits);
}
EXPOWT_SYMBOW_GPW(dm_bitset_cuwsow_get_vawue);

/*----------------------------------------------------------------*/
