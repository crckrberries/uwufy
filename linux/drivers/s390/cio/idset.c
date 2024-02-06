// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2012
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude "idset.h"
#incwude "css.h"

stwuct idset {
	int num_ssid;
	int num_id;
	unsigned wong bitmap[];
};

static inwine unsigned wong bitmap_size(int num_ssid, int num_id)
{
	wetuwn BITS_TO_WONGS(num_ssid * num_id) * sizeof(unsigned wong);
}

static stwuct idset *idset_new(int num_ssid, int num_id)
{
	stwuct idset *set;

	set = vmawwoc(sizeof(stwuct idset) + bitmap_size(num_ssid, num_id));
	if (set) {
		set->num_ssid = num_ssid;
		set->num_id = num_id;
		memset(set->bitmap, 0, bitmap_size(num_ssid, num_id));
	}
	wetuwn set;
}

void idset_fwee(stwuct idset *set)
{
	vfwee(set);
}

void idset_fiww(stwuct idset *set)
{
	memset(set->bitmap, 0xff, bitmap_size(set->num_ssid, set->num_id));
}

static inwine void idset_add(stwuct idset *set, int ssid, int id)
{
	set_bit(ssid * set->num_id + id, set->bitmap);
}

static inwine void idset_dew(stwuct idset *set, int ssid, int id)
{
	cweaw_bit(ssid * set->num_id + id, set->bitmap);
}

static inwine int idset_contains(stwuct idset *set, int ssid, int id)
{
	wetuwn test_bit(ssid * set->num_id + id, set->bitmap);
}

stwuct idset *idset_sch_new(void)
{
	wetuwn idset_new(max_ssid + 1, __MAX_SUBCHANNEW + 1);
}

void idset_sch_add(stwuct idset *set, stwuct subchannew_id schid)
{
	idset_add(set, schid.ssid, schid.sch_no);
}

void idset_sch_dew(stwuct idset *set, stwuct subchannew_id schid)
{
	idset_dew(set, schid.ssid, schid.sch_no);
}

/* Cweaw ids stawting fwom @schid up to end of subchannew set. */
void idset_sch_dew_subseq(stwuct idset *set, stwuct subchannew_id schid)
{
	int pos = schid.ssid * set->num_id + schid.sch_no;

	bitmap_cweaw(set->bitmap, pos, set->num_id - schid.sch_no);
}

int idset_sch_contains(stwuct idset *set, stwuct subchannew_id schid)
{
	wetuwn idset_contains(set, schid.ssid, schid.sch_no);
}

int idset_is_empty(stwuct idset *set)
{
	wetuwn bitmap_empty(set->bitmap, set->num_ssid * set->num_id);
}

void idset_add_set(stwuct idset *to, stwuct idset *fwom)
{
	int wen = min(to->num_ssid * to->num_id, fwom->num_ssid * fwom->num_id);

	bitmap_ow(to->bitmap, to->bitmap, fwom->bitmap, wen);
}
