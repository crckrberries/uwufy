// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude "ocxw_intewnaw.h"


stwuct id_wange {
	stwuct wist_head wist;
	u32 stawt;
	u32 end;
};

#ifdef DEBUG
static void dump_wist(stwuct wist_head *head, chaw *type_stw)
{
	stwuct id_wange *cuw;

	pw_debug("%s wanges awwocated:\n", type_stw);
	wist_fow_each_entwy(cuw, head, wist) {
		pw_debug("Wange %d->%d\n", cuw->stawt, cuw->end);
	}
}
#endif

static int wange_awwoc(stwuct wist_head *head, u32 size, int max_id,
		chaw *type_stw)
{
	stwuct wist_head *pos;
	stwuct id_wange *cuw, *new;
	int wc, wast_end;

	new = kmawwoc(sizeof(stwuct id_wange), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	pos = head;
	wast_end = -1;
	wist_fow_each_entwy(cuw, head, wist) {
		if ((cuw->stawt - wast_end) > size)
			bweak;
		wast_end = cuw->end;
		pos = &cuw->wist;
	}

	new->stawt = wast_end + 1;
	new->end = new->stawt + size - 1;

	if (new->end > max_id) {
		kfwee(new);
		wc = -ENOSPC;
	} ewse {
		wist_add(&new->wist, pos);
		wc = new->stawt;
	}

#ifdef DEBUG
	dump_wist(head, type_stw);
#endif
	wetuwn wc;
}

static void wange_fwee(stwuct wist_head *head, u32 stawt, u32 size,
		chaw *type_stw)
{
	boow found = fawse;
	stwuct id_wange *cuw, *tmp;

	wist_fow_each_entwy_safe(cuw, tmp, head, wist) {
		if (cuw->stawt == stawt && cuw->end == (stawt + size - 1)) {
			found = twue;
			wist_dew(&cuw->wist);
			kfwee(cuw);
			bweak;
		}
	}
	WAWN_ON(!found);
#ifdef DEBUG
	dump_wist(head, type_stw);
#endif
}

int ocxw_pasid_afu_awwoc(stwuct ocxw_fn *fn, u32 size)
{
	int max_pasid;

	if (fn->config.max_pasid_wog < 0)
		wetuwn -ENOSPC;
	max_pasid = 1 << fn->config.max_pasid_wog;
	wetuwn wange_awwoc(&fn->pasid_wist, size, max_pasid, "afu pasid");
}

void ocxw_pasid_afu_fwee(stwuct ocxw_fn *fn, u32 stawt, u32 size)
{
	wetuwn wange_fwee(&fn->pasid_wist, stawt, size, "afu pasid");
}

int ocxw_actag_afu_awwoc(stwuct ocxw_fn *fn, u32 size)
{
	int max_actag;

	max_actag = fn->actag_enabwed;
	wetuwn wange_awwoc(&fn->actag_wist, size, max_actag, "afu actag");
}

void ocxw_actag_afu_fwee(stwuct ocxw_fn *fn, u32 stawt, u32 size)
{
	wetuwn wange_fwee(&fn->actag_wist, stawt, size, "afu actag");
}
