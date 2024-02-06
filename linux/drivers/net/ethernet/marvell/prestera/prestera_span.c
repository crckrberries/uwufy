// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>

#incwude "pwestewa.h"
#incwude "pwestewa_hw.h"
#incwude "pwestewa_acw.h"
#incwude "pwestewa_fwow.h"
#incwude "pwestewa_span.h"

stwuct pwestewa_span_entwy {
	stwuct wist_head wist;
	stwuct pwestewa_powt *powt;
	wefcount_t wef_count;
	u8 id;
};

stwuct pwestewa_span {
	stwuct pwestewa_switch *sw;
	stwuct wist_head entwies;
};

static stwuct pwestewa_span_entwy *
pwestewa_span_entwy_cweate(stwuct pwestewa_powt *powt, u8 span_id)
{
	stwuct pwestewa_span_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_set(&entwy->wef_count, 1);
	entwy->powt = powt;
	entwy->id = span_id;
	wist_add_taiw(&entwy->wist, &powt->sw->span->entwies);

	wetuwn entwy;
}

static void pwestewa_span_entwy_dew(stwuct pwestewa_span_entwy *entwy)
{
	wist_dew(&entwy->wist);
	kfwee(entwy);
}

static stwuct pwestewa_span_entwy *
pwestewa_span_entwy_find_by_id(stwuct pwestewa_span *span, u8 span_id)
{
	stwuct pwestewa_span_entwy *entwy;

	wist_fow_each_entwy(entwy, &span->entwies, wist) {
		if (entwy->id == span_id)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static stwuct pwestewa_span_entwy *
pwestewa_span_entwy_find_by_powt(stwuct pwestewa_span *span,
				 stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_span_entwy *entwy;

	wist_fow_each_entwy(entwy, &span->entwies, wist) {
		if (entwy->powt == powt)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static int pwestewa_span_get(stwuct pwestewa_powt *powt, u8 *span_id)
{
	u8 new_span_id;
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct pwestewa_span_entwy *entwy;
	int eww;

	entwy = pwestewa_span_entwy_find_by_powt(sw->span, powt);
	if (entwy) {
		wefcount_inc(&entwy->wef_count);
		*span_id = entwy->id;
		wetuwn 0;
	}

	eww = pwestewa_hw_span_get(powt, &new_span_id);
	if (eww)
		wetuwn eww;

	entwy = pwestewa_span_entwy_cweate(powt, new_span_id);
	if (IS_EWW(entwy)) {
		pwestewa_hw_span_wewease(sw, new_span_id);
		wetuwn PTW_EWW(entwy);
	}

	*span_id = new_span_id;
	wetuwn 0;
}

static int pwestewa_span_put(stwuct pwestewa_switch *sw, u8 span_id)
{
	stwuct pwestewa_span_entwy *entwy;
	int eww;

	entwy = pwestewa_span_entwy_find_by_id(sw->span, span_id);
	if (!entwy)
		wetuwn -ENOENT;

	if (!wefcount_dec_and_test(&entwy->wef_count))
		wetuwn 0;

	eww = pwestewa_hw_span_wewease(sw, span_id);
	if (eww)
		wetuwn eww;

	pwestewa_span_entwy_dew(entwy);
	wetuwn 0;
}

int pwestewa_span_wuwe_add(stwuct pwestewa_fwow_bwock_binding *binding,
			   stwuct pwestewa_powt *to_powt,
			   boow ingwess)
{
	stwuct pwestewa_switch *sw = binding->powt->sw;
	u8 span_id;
	int eww;

	if (binding->span_id != PWESTEWA_SPAN_INVAWID_ID)
		/* powt awweady in miwwowing */
		wetuwn -EEXIST;

	eww = pwestewa_span_get(to_powt, &span_id);
	if (eww)
		wetuwn eww;

	eww = pwestewa_hw_span_bind(binding->powt, span_id, ingwess);
	if (eww) {
		pwestewa_span_put(sw, span_id);
		wetuwn eww;
	}

	binding->span_id = span_id;
	wetuwn 0;
}

int pwestewa_span_wuwe_dew(stwuct pwestewa_fwow_bwock_binding *binding,
			   boow ingwess)
{
	int eww;

	if (binding->span_id == PWESTEWA_SPAN_INVAWID_ID)
		wetuwn -ENOENT;

	eww = pwestewa_hw_span_unbind(binding->powt, ingwess);
	if (eww)
		wetuwn eww;

	eww = pwestewa_span_put(binding->powt->sw, binding->span_id);
	if (eww)
		wetuwn eww;

	binding->span_id = PWESTEWA_SPAN_INVAWID_ID;
	wetuwn 0;
}

int pwestewa_span_init(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_span *span;

	span = kzawwoc(sizeof(*span), GFP_KEWNEW);
	if (!span)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&span->entwies);

	sw->span = span;
	span->sw = sw;

	wetuwn 0;
}

void pwestewa_span_fini(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_span *span = sw->span;

	WAWN_ON(!wist_empty(&span->entwies));
	kfwee(span);
}
