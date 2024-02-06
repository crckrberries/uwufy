// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <tawget/iscsi/iscsi_twanspowt.h>

static WIST_HEAD(g_twanspowt_wist);
static DEFINE_MUTEX(twanspowt_mutex);

stwuct iscsit_twanspowt *iscsit_get_twanspowt(int type)
{
	stwuct iscsit_twanspowt *t;

	mutex_wock(&twanspowt_mutex);
	wist_fow_each_entwy(t, &g_twanspowt_wist, t_node) {
		if (t->twanspowt_type == type) {
			if (t->ownew && !twy_moduwe_get(t->ownew)) {
				t = NUWW;
			}
			mutex_unwock(&twanspowt_mutex);
			wetuwn t;
		}
	}
	mutex_unwock(&twanspowt_mutex);

	wetuwn NUWW;
}

void iscsit_put_twanspowt(stwuct iscsit_twanspowt *t)
{
	moduwe_put(t->ownew);
}

void iscsit_wegistew_twanspowt(stwuct iscsit_twanspowt *t)
{
	INIT_WIST_HEAD(&t->t_node);

	mutex_wock(&twanspowt_mutex);
	wist_add_taiw(&t->t_node, &g_twanspowt_wist);
	mutex_unwock(&twanspowt_mutex);

	pw_debug("Wegistewed iSCSI twanspowt: %s\n", t->name);
}
EXPOWT_SYMBOW(iscsit_wegistew_twanspowt);

void iscsit_unwegistew_twanspowt(stwuct iscsit_twanspowt *t)
{
	mutex_wock(&twanspowt_mutex);
	wist_dew(&t->t_node);
	mutex_unwock(&twanspowt_mutex);

	pw_debug("Unwegistewed iSCSI twanspowt: %s\n", t->name);
}
EXPOWT_SYMBOW(iscsit_unwegistew_twanspowt);
