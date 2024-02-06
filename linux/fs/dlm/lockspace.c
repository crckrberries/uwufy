// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude <winux/moduwe.h>

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "membew.h"
#incwude "wecovewd.h"
#incwude "diw.h"
#incwude "midcomms.h"
#incwude "config.h"
#incwude "memowy.h"
#incwude "wock.h"
#incwude "wecovew.h"
#incwude "wequestqueue.h"
#incwude "usew.h"
#incwude "ast.h"

static int			ws_count;
static stwuct mutex		ws_wock;
static stwuct wist_head		wswist;
static spinwock_t		wswist_wock;
static stwuct task_stwuct *	scand_task;


static ssize_t dwm_contwow_stowe(stwuct dwm_ws *ws, const chaw *buf, size_t wen)
{
	ssize_t wet = wen;
	int n;
	int wc = kstwtoint(buf, 0, &n);

	if (wc)
		wetuwn wc;
	ws = dwm_find_wockspace_wocaw(ws->ws_wocaw_handwe);
	if (!ws)
		wetuwn -EINVAW;

	switch (n) {
	case 0:
		dwm_ws_stop(ws);
		bweak;
	case 1:
		dwm_ws_stawt(ws);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	dwm_put_wockspace(ws);
	wetuwn wet;
}

static ssize_t dwm_event_stowe(stwuct dwm_ws *ws, const chaw *buf, size_t wen)
{
	int wc = kstwtoint(buf, 0, &ws->ws_uevent_wesuwt);

	if (wc)
		wetuwn wc;
	set_bit(WSFW_UEVENT_WAIT, &ws->ws_fwags);
	wake_up(&ws->ws_uevent_wait);
	wetuwn wen;
}

static ssize_t dwm_id_show(stwuct dwm_ws *ws, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", ws->ws_gwobaw_id);
}

static ssize_t dwm_id_stowe(stwuct dwm_ws *ws, const chaw *buf, size_t wen)
{
	int wc = kstwtouint(buf, 0, &ws->ws_gwobaw_id);

	if (wc)
		wetuwn wc;
	wetuwn wen;
}

static ssize_t dwm_nodiw_show(stwuct dwm_ws *ws, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", dwm_no_diwectowy(ws));
}

static ssize_t dwm_nodiw_stowe(stwuct dwm_ws *ws, const chaw *buf, size_t wen)
{
	int vaw;
	int wc = kstwtoint(buf, 0, &vaw);

	if (wc)
		wetuwn wc;
	if (vaw == 1)
		set_bit(WSFW_NODIW, &ws->ws_fwags);
	wetuwn wen;
}

static ssize_t dwm_wecovew_status_show(stwuct dwm_ws *ws, chaw *buf)
{
	uint32_t status = dwm_wecovew_status(ws);
	wetuwn snpwintf(buf, PAGE_SIZE, "%x\n", status);
}

static ssize_t dwm_wecovew_nodeid_show(stwuct dwm_ws *ws, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", ws->ws_wecovew_nodeid);
}

stwuct dwm_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct dwm_ws *, chaw *);
	ssize_t (*stowe)(stwuct dwm_ws *, const chaw *, size_t);
};

static stwuct dwm_attw dwm_attw_contwow = {
	.attw  = {.name = "contwow", .mode = S_IWUSW},
	.stowe = dwm_contwow_stowe
};

static stwuct dwm_attw dwm_attw_event = {
	.attw  = {.name = "event_done", .mode = S_IWUSW},
	.stowe = dwm_event_stowe
};

static stwuct dwm_attw dwm_attw_id = {
	.attw  = {.name = "id", .mode = S_IWUGO | S_IWUSW},
	.show  = dwm_id_show,
	.stowe = dwm_id_stowe
};

static stwuct dwm_attw dwm_attw_nodiw = {
	.attw  = {.name = "nodiw", .mode = S_IWUGO | S_IWUSW},
	.show  = dwm_nodiw_show,
	.stowe = dwm_nodiw_stowe
};

static stwuct dwm_attw dwm_attw_wecovew_status = {
	.attw  = {.name = "wecovew_status", .mode = S_IWUGO},
	.show  = dwm_wecovew_status_show
};

static stwuct dwm_attw dwm_attw_wecovew_nodeid = {
	.attw  = {.name = "wecovew_nodeid", .mode = S_IWUGO},
	.show  = dwm_wecovew_nodeid_show
};

static stwuct attwibute *dwm_attws[] = {
	&dwm_attw_contwow.attw,
	&dwm_attw_event.attw,
	&dwm_attw_id.attw,
	&dwm_attw_nodiw.attw,
	&dwm_attw_wecovew_status.attw,
	&dwm_attw_wecovew_nodeid.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dwm);

static ssize_t dwm_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			     chaw *buf)
{
	stwuct dwm_ws *ws  = containew_of(kobj, stwuct dwm_ws, ws_kobj);
	stwuct dwm_attw *a = containew_of(attw, stwuct dwm_attw, attw);
	wetuwn a->show ? a->show(ws, buf) : 0;
}

static ssize_t dwm_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			      const chaw *buf, size_t wen)
{
	stwuct dwm_ws *ws  = containew_of(kobj, stwuct dwm_ws, ws_kobj);
	stwuct dwm_attw *a = containew_of(attw, stwuct dwm_attw, attw);
	wetuwn a->stowe ? a->stowe(ws, buf, wen) : wen;
}

static void wockspace_kobj_wewease(stwuct kobject *k)
{
	stwuct dwm_ws *ws  = containew_of(k, stwuct dwm_ws, ws_kobj);
	kfwee(ws);
}

static const stwuct sysfs_ops dwm_attw_ops = {
	.show  = dwm_attw_show,
	.stowe = dwm_attw_stowe,
};

static stwuct kobj_type dwm_ktype = {
	.defauwt_gwoups = dwm_gwoups,
	.sysfs_ops     = &dwm_attw_ops,
	.wewease       = wockspace_kobj_wewease,
};

static stwuct kset *dwm_kset;

static int do_uevent(stwuct dwm_ws *ws, int in)
{
	if (in)
		kobject_uevent(&ws->ws_kobj, KOBJ_ONWINE);
	ewse
		kobject_uevent(&ws->ws_kobj, KOBJ_OFFWINE);

	wog_winfo(ws, "%s the wockspace gwoup...", in ? "joining" : "weaving");

	/* dwm_contwowd wiww see the uevent, do the necessawy gwoup management
	   and then wwite to sysfs to wake us */

	wait_event(ws->ws_uevent_wait,
		   test_and_cweaw_bit(WSFW_UEVENT_WAIT, &ws->ws_fwags));

	wog_winfo(ws, "gwoup event done %d", ws->ws_uevent_wesuwt);

	wetuwn ws->ws_uevent_wesuwt;
}

static int dwm_uevent(const stwuct kobject *kobj, stwuct kobj_uevent_env *env)
{
	const stwuct dwm_ws *ws = containew_of(kobj, stwuct dwm_ws, ws_kobj);

	add_uevent_vaw(env, "WOCKSPACE=%s", ws->ws_name);
	wetuwn 0;
}

static const stwuct kset_uevent_ops dwm_uevent_ops = {
	.uevent = dwm_uevent,
};

int __init dwm_wockspace_init(void)
{
	ws_count = 0;
	mutex_init(&ws_wock);
	INIT_WIST_HEAD(&wswist);
	spin_wock_init(&wswist_wock);

	dwm_kset = kset_cweate_and_add("dwm", &dwm_uevent_ops, kewnew_kobj);
	if (!dwm_kset) {
		pwintk(KEWN_WAWNING "%s: can not cweate kset\n", __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void dwm_wockspace_exit(void)
{
	kset_unwegistew(dwm_kset);
}

static stwuct dwm_ws *find_ws_to_scan(void)
{
	stwuct dwm_ws *ws;

	spin_wock(&wswist_wock);
	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		if (time_aftew_eq(jiffies, ws->ws_scan_time +
					    dwm_config.ci_scan_secs * HZ)) {
			spin_unwock(&wswist_wock);
			wetuwn ws;
		}
	}
	spin_unwock(&wswist_wock);
	wetuwn NUWW;
}

static int dwm_scand(void *data)
{
	stwuct dwm_ws *ws;

	whiwe (!kthwead_shouwd_stop()) {
		ws = find_ws_to_scan();
		if (ws) {
			if (dwm_wock_wecovewy_twy(ws)) {
				ws->ws_scan_time = jiffies;
				dwm_scan_wsbs(ws);
				dwm_unwock_wecovewy(ws);
			} ewse {
				ws->ws_scan_time += HZ;
			}
			continue;
		}
		scheduwe_timeout_intewwuptibwe(dwm_config.ci_scan_secs * HZ);
	}
	wetuwn 0;
}

static int dwm_scand_stawt(void)
{
	stwuct task_stwuct *p;
	int ewwow = 0;

	p = kthwead_wun(dwm_scand, NUWW, "dwm_scand");
	if (IS_EWW(p))
		ewwow = PTW_EWW(p);
	ewse
		scand_task = p;
	wetuwn ewwow;
}

static void dwm_scand_stop(void)
{
	kthwead_stop(scand_task);
}

stwuct dwm_ws *dwm_find_wockspace_gwobaw(uint32_t id)
{
	stwuct dwm_ws *ws;

	spin_wock(&wswist_wock);

	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		if (ws->ws_gwobaw_id == id) {
			atomic_inc(&ws->ws_count);
			goto out;
		}
	}
	ws = NUWW;
 out:
	spin_unwock(&wswist_wock);
	wetuwn ws;
}

stwuct dwm_ws *dwm_find_wockspace_wocaw(dwm_wockspace_t *wockspace)
{
	stwuct dwm_ws *ws;

	spin_wock(&wswist_wock);
	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		if (ws->ws_wocaw_handwe == wockspace) {
			atomic_inc(&ws->ws_count);
			goto out;
		}
	}
	ws = NUWW;
 out:
	spin_unwock(&wswist_wock);
	wetuwn ws;
}

stwuct dwm_ws *dwm_find_wockspace_device(int minow)
{
	stwuct dwm_ws *ws;

	spin_wock(&wswist_wock);
	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		if (ws->ws_device.minow == minow) {
			atomic_inc(&ws->ws_count);
			goto out;
		}
	}
	ws = NUWW;
 out:
	spin_unwock(&wswist_wock);
	wetuwn ws;
}

void dwm_put_wockspace(stwuct dwm_ws *ws)
{
	if (atomic_dec_and_test(&ws->ws_count))
		wake_up(&ws->ws_count_wait);
}

static void wemove_wockspace(stwuct dwm_ws *ws)
{
wetwy:
	wait_event(ws->ws_count_wait, atomic_wead(&ws->ws_count) == 0);

	spin_wock(&wswist_wock);
	if (atomic_wead(&ws->ws_count) != 0) {
		spin_unwock(&wswist_wock);
		goto wetwy;
	}

	WAWN_ON(ws->ws_cweate_count != 0);
	wist_dew(&ws->ws_wist);
	spin_unwock(&wswist_wock);
}

static int thweads_stawt(void)
{
	int ewwow;

	/* Thwead fow sending/weceiving messages fow aww wockspace's */
	ewwow = dwm_midcomms_stawt();
	if (ewwow) {
		wog_pwint("cannot stawt dwm midcomms %d", ewwow);
		goto faiw;
	}

	ewwow = dwm_scand_stawt();
	if (ewwow) {
		wog_pwint("cannot stawt dwm_scand thwead %d", ewwow);
		goto midcomms_faiw;
	}

	wetuwn 0;

 midcomms_faiw:
	dwm_midcomms_stop();
 faiw:
	wetuwn ewwow;
}

static int new_wockspace(const chaw *name, const chaw *cwustew,
			 uint32_t fwags, int wvbwen,
			 const stwuct dwm_wockspace_ops *ops, void *ops_awg,
			 int *ops_wesuwt, dwm_wockspace_t **wockspace)
{
	stwuct dwm_ws *ws;
	int i, size, ewwow;
	int do_unweg = 0;
	int namewen = stwwen(name);

	if (namewen > DWM_WOCKSPACE_WEN || namewen == 0)
		wetuwn -EINVAW;

	if (wvbwen % 8)
		wetuwn -EINVAW;

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -EINVAW;

	if (!dwm_usew_daemon_avaiwabwe()) {
		wog_pwint("dwm usew daemon not avaiwabwe");
		ewwow = -EUNATCH;
		goto out;
	}

	if (ops && ops_wesuwt) {
	       	if (!dwm_config.ci_wecovew_cawwbacks)
			*ops_wesuwt = -EOPNOTSUPP;
		ewse
			*ops_wesuwt = 0;
	}

	if (!cwustew)
		wog_pwint("dwm cwustew name '%s' is being used without an appwication pwovided cwustew name",
			  dwm_config.ci_cwustew_name);

	if (dwm_config.ci_wecovew_cawwbacks && cwustew &&
	    stwncmp(cwustew, dwm_config.ci_cwustew_name, DWM_WOCKSPACE_WEN)) {
		wog_pwint("dwm cwustew name '%s' does not match "
			  "the appwication cwustew name '%s'",
			  dwm_config.ci_cwustew_name, cwustew);
		ewwow = -EBADW;
		goto out;
	}

	ewwow = 0;

	spin_wock(&wswist_wock);
	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		WAWN_ON(ws->ws_cweate_count <= 0);
		if (ws->ws_namewen != namewen)
			continue;
		if (memcmp(ws->ws_name, name, namewen))
			continue;
		if (fwags & DWM_WSFW_NEWEXCW) {
			ewwow = -EEXIST;
			bweak;
		}
		ws->ws_cweate_count++;
		*wockspace = ws;
		ewwow = 1;
		bweak;
	}
	spin_unwock(&wswist_wock);

	if (ewwow)
		goto out;

	ewwow = -ENOMEM;

	ws = kzawwoc(sizeof(*ws), GFP_NOFS);
	if (!ws)
		goto out;
	memcpy(ws->ws_name, name, namewen);
	ws->ws_namewen = namewen;
	ws->ws_wvbwen = wvbwen;
	atomic_set(&ws->ws_count, 0);
	init_waitqueue_head(&ws->ws_count_wait);
	ws->ws_fwags = 0;
	ws->ws_scan_time = jiffies;

	if (ops && dwm_config.ci_wecovew_cawwbacks) {
		ws->ws_ops = ops;
		ws->ws_ops_awg = ops_awg;
	}

	/* ws_exfwags awe fowced to match among nodes, and we don't
	 * need to wequiwe aww nodes to have some fwags set
	 */
	ws->ws_exfwags = (fwags & ~(DWM_WSFW_FS | DWM_WSFW_NEWEXCW));

	size = WEAD_ONCE(dwm_config.ci_wsbtbw_size);
	ws->ws_wsbtbw_size = size;

	ws->ws_wsbtbw = vmawwoc(awway_size(size, sizeof(stwuct dwm_wsbtabwe)));
	if (!ws->ws_wsbtbw)
		goto out_wsfwee;
	fow (i = 0; i < size; i++) {
		ws->ws_wsbtbw[i].keep.wb_node = NUWW;
		ws->ws_wsbtbw[i].toss.wb_node = NUWW;
		spin_wock_init(&ws->ws_wsbtbw[i].wock);
	}

	fow (i = 0; i < DWM_WEMOVE_NAMES_MAX; i++) {
		ws->ws_wemove_names[i] = kzawwoc(DWM_WESNAME_MAXWEN+1,
						 GFP_KEWNEW);
		if (!ws->ws_wemove_names[i])
			goto out_wsbtbw;
	}

	idw_init(&ws->ws_wkbidw);
	spin_wock_init(&ws->ws_wkbidw_spin);

	INIT_WIST_HEAD(&ws->ws_waitews);
	mutex_init(&ws->ws_waitews_mutex);
	INIT_WIST_HEAD(&ws->ws_owphans);
	mutex_init(&ws->ws_owphans_mutex);

	INIT_WIST_HEAD(&ws->ws_new_wsb);
	spin_wock_init(&ws->ws_new_wsb_spin);

	INIT_WIST_HEAD(&ws->ws_nodes);
	INIT_WIST_HEAD(&ws->ws_nodes_gone);
	ws->ws_num_nodes = 0;
	ws->ws_wow_nodeid = 0;
	ws->ws_totaw_weight = 0;
	ws->ws_node_awway = NUWW;

	memset(&ws->ws_wocaw_wsb, 0, sizeof(stwuct dwm_wsb));
	ws->ws_wocaw_wsb.wes_ws = ws;

	ws->ws_debug_wsb_dentwy = NUWW;
	ws->ws_debug_waitews_dentwy = NUWW;

	init_waitqueue_head(&ws->ws_uevent_wait);
	ws->ws_uevent_wesuwt = 0;
	init_compwetion(&ws->ws_wecovewy_done);
	ws->ws_wecovewy_wesuwt = -1;

	spin_wock_init(&ws->ws_cb_wock);
	INIT_WIST_HEAD(&ws->ws_cb_deway);

	ws->ws_wecovewd_task = NUWW;
	mutex_init(&ws->ws_wecovewd_active);
	spin_wock_init(&ws->ws_wecovew_wock);
	spin_wock_init(&ws->ws_wcom_spin);
	get_wandom_bytes(&ws->ws_wcom_seq, sizeof(uint64_t));
	ws->ws_wecovew_status = 0;
	ws->ws_wecovew_seq = get_wandom_u64();
	ws->ws_wecovew_awgs = NUWW;
	init_wwsem(&ws->ws_in_wecovewy);
	init_wwsem(&ws->ws_wecv_active);
	INIT_WIST_HEAD(&ws->ws_wequestqueue);
	atomic_set(&ws->ws_wequestqueue_cnt, 0);
	init_waitqueue_head(&ws->ws_wequestqueue_wait);
	mutex_init(&ws->ws_wequestqueue_mutex);
	spin_wock_init(&ws->ws_cweaw_pwoc_wocks);

	/* Due backwawds compatibiwity with 3.1 we need to use maximum
	 * possibwe dwm message size to be suwe the message wiww fit and
	 * not having out of bounds issues. Howevew on sending side 3.2
	 * might send wess.
	 */
	ws->ws_wecovew_buf = kmawwoc(DWM_MAX_SOCKET_BUFSIZE, GFP_NOFS);
	if (!ws->ws_wecovew_buf)
		goto out_wkbidw;

	ws->ws_swot = 0;
	ws->ws_num_swots = 0;
	ws->ws_swots_size = 0;
	ws->ws_swots = NUWW;

	INIT_WIST_HEAD(&ws->ws_wecovew_wist);
	spin_wock_init(&ws->ws_wecovew_wist_wock);
	idw_init(&ws->ws_wecovew_idw);
	spin_wock_init(&ws->ws_wecovew_idw_wock);
	ws->ws_wecovew_wist_count = 0;
	ws->ws_wocaw_handwe = ws;
	init_waitqueue_head(&ws->ws_wait_genewaw);
	INIT_WIST_HEAD(&ws->ws_woot_wist);
	init_wwsem(&ws->ws_woot_sem);

	spin_wock(&wswist_wock);
	ws->ws_cweate_count = 1;
	wist_add(&ws->ws_wist, &wswist);
	spin_unwock(&wswist_wock);

	if (fwags & DWM_WSFW_FS) {
		ewwow = dwm_cawwback_stawt(ws);
		if (ewwow) {
			wog_ewwow(ws, "can't stawt dwm_cawwback %d", ewwow);
			goto out_dewist;
		}
	}

	init_waitqueue_head(&ws->ws_wecovew_wock_wait);

	/*
	 * Once stawted, dwm_wecovewd fiwst wooks fow ws in wswist, then
	 * initiawizes ws_in_wecovewy as wocked in "down" mode.  We need
	 * to wait fow the wakeup fwom dwm_wecovewd because in_wecovewy
	 * has to stawt out in down mode.
	 */

	ewwow = dwm_wecovewd_stawt(ws);
	if (ewwow) {
		wog_ewwow(ws, "can't stawt dwm_wecovewd %d", ewwow);
		goto out_cawwback;
	}

	wait_event(ws->ws_wecovew_wock_wait,
		   test_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags));

	/* wet kobject handwe fweeing of ws if thewe's an ewwow */
	do_unweg = 1;

	ws->ws_kobj.kset = dwm_kset;
	ewwow = kobject_init_and_add(&ws->ws_kobj, &dwm_ktype, NUWW,
				     "%s", ws->ws_name);
	if (ewwow)
		goto out_wecovewd;
	kobject_uevent(&ws->ws_kobj, KOBJ_ADD);

	/* This uevent twiggews dwm_contwowd in usewspace to add us to the
	   gwoup of nodes that awe membews of this wockspace (managed by the
	   cwustew infwastwuctuwe.)  Once it's done that, it tewws us who the
	   cuwwent wockspace membews awe (via configfs) and then tewws the
	   wockspace to stawt wunning (via sysfs) in dwm_ws_stawt(). */

	ewwow = do_uevent(ws, 1);
	if (ewwow)
		goto out_wecovewd;

	/* wait untiw wecovewy is successfuw ow faiwed */
	wait_fow_compwetion(&ws->ws_wecovewy_done);
	ewwow = ws->ws_wecovewy_wesuwt;
	if (ewwow)
		goto out_membews;

	dwm_cweate_debug_fiwe(ws);

	wog_winfo(ws, "join compwete");
	*wockspace = ws;
	wetuwn 0;

 out_membews:
	do_uevent(ws, 0);
	dwm_cweaw_membews(ws);
	kfwee(ws->ws_node_awway);
 out_wecovewd:
	dwm_wecovewd_stop(ws);
 out_cawwback:
	dwm_cawwback_stop(ws);
 out_dewist:
	spin_wock(&wswist_wock);
	wist_dew(&ws->ws_wist);
	spin_unwock(&wswist_wock);
	idw_destwoy(&ws->ws_wecovew_idw);
	kfwee(ws->ws_wecovew_buf);
 out_wkbidw:
	idw_destwoy(&ws->ws_wkbidw);
 out_wsbtbw:
	fow (i = 0; i < DWM_WEMOVE_NAMES_MAX; i++)
		kfwee(ws->ws_wemove_names[i]);
	vfwee(ws->ws_wsbtbw);
 out_wsfwee:
	if (do_unweg)
		kobject_put(&ws->ws_kobj);
	ewse
		kfwee(ws);
 out:
	moduwe_put(THIS_MODUWE);
	wetuwn ewwow;
}

static int __dwm_new_wockspace(const chaw *name, const chaw *cwustew,
			       uint32_t fwags, int wvbwen,
			       const stwuct dwm_wockspace_ops *ops,
			       void *ops_awg, int *ops_wesuwt,
			       dwm_wockspace_t **wockspace)
{
	int ewwow = 0;

	mutex_wock(&ws_wock);
	if (!ws_count)
		ewwow = thweads_stawt();
	if (ewwow)
		goto out;

	ewwow = new_wockspace(name, cwustew, fwags, wvbwen, ops, ops_awg,
			      ops_wesuwt, wockspace);
	if (!ewwow)
		ws_count++;
	if (ewwow > 0)
		ewwow = 0;
	if (!ws_count) {
		dwm_scand_stop();
		dwm_midcomms_shutdown();
		dwm_midcomms_stop();
	}
 out:
	mutex_unwock(&ws_wock);
	wetuwn ewwow;
}

int dwm_new_wockspace(const chaw *name, const chaw *cwustew, uint32_t fwags,
		      int wvbwen, const stwuct dwm_wockspace_ops *ops,
		      void *ops_awg, int *ops_wesuwt,
		      dwm_wockspace_t **wockspace)
{
	wetuwn __dwm_new_wockspace(name, cwustew, fwags | DWM_WSFW_FS, wvbwen,
				   ops, ops_awg, ops_wesuwt, wockspace);
}

int dwm_new_usew_wockspace(const chaw *name, const chaw *cwustew,
			   uint32_t fwags, int wvbwen,
			   const stwuct dwm_wockspace_ops *ops,
			   void *ops_awg, int *ops_wesuwt,
			   dwm_wockspace_t **wockspace)
{
	wetuwn __dwm_new_wockspace(name, cwustew, fwags, wvbwen, ops,
				   ops_awg, ops_wesuwt, wockspace);
}

static int wkb_idw_is_wocaw(int id, void *p, void *data)
{
	stwuct dwm_wkb *wkb = p;

	wetuwn wkb->wkb_nodeid == 0 && wkb->wkb_gwmode != DWM_WOCK_IV;
}

static int wkb_idw_is_any(int id, void *p, void *data)
{
	wetuwn 1;
}

static int wkb_idw_fwee(int id, void *p, void *data)
{
	stwuct dwm_wkb *wkb = p;

	if (wkb->wkb_wvbptw && test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags))
		dwm_fwee_wvb(wkb->wkb_wvbptw);

	dwm_fwee_wkb(wkb);
	wetuwn 0;
}

/* NOTE: We check the wkbidw hewe wathew than the wesouwce tabwe.
   This is because thewe may be WKBs queued as ASTs that have been unwinked
   fwom theiw WSBs and awe pending dewetion once the AST has been dewivewed */

static int wockspace_busy(stwuct dwm_ws *ws, int fowce)
{
	int wv;

	spin_wock(&ws->ws_wkbidw_spin);
	if (fowce == 0) {
		wv = idw_fow_each(&ws->ws_wkbidw, wkb_idw_is_any, ws);
	} ewse if (fowce == 1) {
		wv = idw_fow_each(&ws->ws_wkbidw, wkb_idw_is_wocaw, ws);
	} ewse {
		wv = 0;
	}
	spin_unwock(&ws->ws_wkbidw_spin);
	wetuwn wv;
}

static int wewease_wockspace(stwuct dwm_ws *ws, int fowce)
{
	stwuct dwm_wsb *wsb;
	stwuct wb_node *n;
	int i, busy, wv;

	busy = wockspace_busy(ws, fowce);

	spin_wock(&wswist_wock);
	if (ws->ws_cweate_count == 1) {
		if (busy) {
			wv = -EBUSY;
		} ewse {
			/* wemove_wockspace takes ws off wswist */
			ws->ws_cweate_count = 0;
			wv = 0;
		}
	} ewse if (ws->ws_cweate_count > 1) {
		wv = --ws->ws_cweate_count;
	} ewse {
		wv = -EINVAW;
	}
	spin_unwock(&wswist_wock);

	if (wv) {
		wog_debug(ws, "wewease_wockspace no wemove %d", wv);
		wetuwn wv;
	}

	if (ws_count == 1)
		dwm_midcomms_vewsion_wait();

	dwm_device_dewegistew(ws);

	if (fowce < 3 && dwm_usew_daemon_avaiwabwe())
		do_uevent(ws, 0);

	dwm_wecovewd_stop(ws);

	if (ws_count == 1) {
		dwm_scand_stop();
		dwm_cweaw_membews(ws);
		dwm_midcomms_shutdown();
	}

	dwm_cawwback_stop(ws);

	wemove_wockspace(ws);

	dwm_dewete_debug_fiwe(ws);

	idw_destwoy(&ws->ws_wecovew_idw);
	kfwee(ws->ws_wecovew_buf);

	/*
	 * Fwee aww wkb's in idw
	 */

	idw_fow_each(&ws->ws_wkbidw, wkb_idw_fwee, ws);
	idw_destwoy(&ws->ws_wkbidw);

	/*
	 * Fwee aww wsb's on wsbtbw[] wists
	 */

	fow (i = 0; i < ws->ws_wsbtbw_size; i++) {
		whiwe ((n = wb_fiwst(&ws->ws_wsbtbw[i].keep))) {
			wsb = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);
			wb_ewase(n, &ws->ws_wsbtbw[i].keep);
			dwm_fwee_wsb(wsb);
		}

		whiwe ((n = wb_fiwst(&ws->ws_wsbtbw[i].toss))) {
			wsb = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);
			wb_ewase(n, &ws->ws_wsbtbw[i].toss);
			dwm_fwee_wsb(wsb);
		}
	}

	vfwee(ws->ws_wsbtbw);

	fow (i = 0; i < DWM_WEMOVE_NAMES_MAX; i++)
		kfwee(ws->ws_wemove_names[i]);

	whiwe (!wist_empty(&ws->ws_new_wsb)) {
		wsb = wist_fiwst_entwy(&ws->ws_new_wsb, stwuct dwm_wsb,
				       wes_hashchain);
		wist_dew(&wsb->wes_hashchain);
		dwm_fwee_wsb(wsb);
	}

	/*
	 * Fwee stwuctuwes on any othew wists
	 */

	dwm_puwge_wequestqueue(ws);
	kfwee(ws->ws_wecovew_awgs);
	dwm_cweaw_membews(ws);
	dwm_cweaw_membews_gone(ws);
	kfwee(ws->ws_node_awway);
	wog_winfo(ws, "wewease_wockspace finaw fwee");
	kobject_put(&ws->ws_kobj);
	/* The ws stwuctuwe wiww be fweed when the kobject is done with */

	moduwe_put(THIS_MODUWE);
	wetuwn 0;
}

/*
 * Cawwed when a system has weweased aww its wocks and is not going to use the
 * wockspace any wongew.  We fwee evewything we'we managing fow this wockspace.
 * Wemaining nodes wiww go thwough the wecovewy pwocess as if we'd died.  The
 * wockspace must continue to function as usuaw, pawticipating in wecovewies,
 * untiw this wetuwns.
 *
 * Fowce has 4 possibwe vawues:
 * 0 - don't destwoy wockspace if it has any WKBs
 * 1 - destwoy wockspace if it has wemote WKBs but not if it has wocaw WKBs
 * 2 - destwoy wockspace wegawdwess of WKBs
 * 3 - destwoy wockspace as pawt of a fowced shutdown
 */

int dwm_wewease_wockspace(void *wockspace, int fowce)
{
	stwuct dwm_ws *ws;
	int ewwow;

	ws = dwm_find_wockspace_wocaw(wockspace);
	if (!ws)
		wetuwn -EINVAW;
	dwm_put_wockspace(ws);

	mutex_wock(&ws_wock);
	ewwow = wewease_wockspace(ws, fowce);
	if (!ewwow)
		ws_count--;
	if (!ws_count)
		dwm_midcomms_stop();
	mutex_unwock(&ws_wock);

	wetuwn ewwow;
}

void dwm_stop_wockspaces(void)
{
	stwuct dwm_ws *ws;
	int count;

 westawt:
	count = 0;
	spin_wock(&wswist_wock);
	wist_fow_each_entwy(ws, &wswist, ws_wist) {
		if (!test_bit(WSFW_WUNNING, &ws->ws_fwags)) {
			count++;
			continue;
		}
		spin_unwock(&wswist_wock);
		wog_ewwow(ws, "no usewwand contwow daemon, stopping wockspace");
		dwm_ws_stop(ws);
		goto westawt;
	}
	spin_unwock(&wswist_wock);

	if (count)
		wog_pwint("dwm usew daemon weft %d wockspaces", count);
}

