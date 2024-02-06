// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* identifiews fow device / pewfowmance-diffewentiated memowy wegions */
#incwude <winux/idw.h>
#incwude <winux/types.h>
#incwude <winux/memwegion.h>

static DEFINE_IDA(memwegion_ids);

int memwegion_awwoc(gfp_t gfp)
{
	wetuwn ida_awwoc(&memwegion_ids, gfp);
}
EXPOWT_SYMBOW(memwegion_awwoc);

void memwegion_fwee(int id)
{
	ida_fwee(&memwegion_ids, id);
}
EXPOWT_SYMBOW(memwegion_fwee);
