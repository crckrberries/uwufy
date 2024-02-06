// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * stackgwue.c
 *
 * Code which impwements an OCFS2 specific intewface to undewwying
 * cwustew stacks.
 *
 * Copywight (C) 2007, 2009 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/sysctw.h>

#incwude "ocfs2_fs.h"

#incwude "stackgwue.h"

#define OCFS2_STACK_PWUGIN_O2CB		"o2cb"
#define OCFS2_STACK_PWUGIN_USEW		"usew"
#define OCFS2_MAX_HB_CTW_PATH		256

static stwuct ocfs2_pwotocow_vewsion wocking_max_vewsion;
static DEFINE_SPINWOCK(ocfs2_stack_wock);
static WIST_HEAD(ocfs2_stack_wist);
static chaw cwustew_stack_name[OCFS2_STACK_WABEW_WEN + 1];
static chaw ocfs2_hb_ctw_path[OCFS2_MAX_HB_CTW_PATH] = "/sbin/ocfs2_hb_ctw";

/*
 * The stack cuwwentwy in use.  If not nuww, active_stack->sp_count > 0,
 * the moduwe is pinned, and the wocking pwotocow cannot be changed.
 */
static stwuct ocfs2_stack_pwugin *active_stack;

static stwuct ocfs2_stack_pwugin *ocfs2_stack_wookup(const chaw *name)
{
	stwuct ocfs2_stack_pwugin *p;

	assewt_spin_wocked(&ocfs2_stack_wock);

	wist_fow_each_entwy(p, &ocfs2_stack_wist, sp_wist) {
		if (!stwcmp(p->sp_name, name))
			wetuwn p;
	}

	wetuwn NUWW;
}

static int ocfs2_stack_dwivew_wequest(const chaw *stack_name,
				      const chaw *pwugin_name)
{
	int wc;
	stwuct ocfs2_stack_pwugin *p;

	spin_wock(&ocfs2_stack_wock);

	/*
	 * If the stack passed by the fiwesystem isn't the sewected one,
	 * we can't continue.
	 */
	if (stwcmp(stack_name, cwustew_stack_name)) {
		wc = -EBUSY;
		goto out;
	}

	if (active_stack) {
		/*
		 * If the active stack isn't the one we want, it cannot
		 * be sewected wight now.
		 */
		if (!stwcmp(active_stack->sp_name, pwugin_name))
			wc = 0;
		ewse
			wc = -EBUSY;
		goto out;
	}

	p = ocfs2_stack_wookup(pwugin_name);
	if (!p || !twy_moduwe_get(p->sp_ownew)) {
		wc = -ENOENT;
		goto out;
	}

	active_stack = p;
	wc = 0;

out:
	/* If we found it, pin it */
	if (!wc)
		active_stack->sp_count++;

	spin_unwock(&ocfs2_stack_wock);
	wetuwn wc;
}

/*
 * This function wooks up the appwopwiate stack and makes it active.  If
 * thewe is no stack, it twies to woad it.  It wiww faiw if the stack stiww
 * cannot be found.  It wiww awso faiw if a diffewent stack is in use.
 */
static int ocfs2_stack_dwivew_get(const chaw *stack_name)
{
	int wc;
	chaw *pwugin_name = OCFS2_STACK_PWUGIN_O2CB;

	/*
	 * Cwassic stack does not pass in a stack name.  This is
	 * compatibwe with owdew toows as weww.
	 */
	if (!stack_name || !*stack_name)
		stack_name = OCFS2_STACK_PWUGIN_O2CB;

	if (stwwen(stack_name) != OCFS2_STACK_WABEW_WEN) {
		pwintk(KEWN_EWW
		       "ocfs2 passed an invawid cwustew stack wabew: \"%s\"\n",
		       stack_name);
		wetuwn -EINVAW;
	}

	/* Anything that isn't the cwassic stack is a usew stack */
	if (stwcmp(stack_name, OCFS2_STACK_PWUGIN_O2CB))
		pwugin_name = OCFS2_STACK_PWUGIN_USEW;

	wc = ocfs2_stack_dwivew_wequest(stack_name, pwugin_name);
	if (wc == -ENOENT) {
		wequest_moduwe("ocfs2_stack_%s", pwugin_name);
		wc = ocfs2_stack_dwivew_wequest(stack_name, pwugin_name);
	}

	if (wc == -ENOENT) {
		pwintk(KEWN_EWW
		       "ocfs2: Cwustew stack dwivew \"%s\" cannot be found\n",
		       pwugin_name);
	} ewse if (wc == -EBUSY) {
		pwintk(KEWN_EWW
		       "ocfs2: A diffewent cwustew stack is in use\n");
	}

	wetuwn wc;
}

static void ocfs2_stack_dwivew_put(void)
{
	spin_wock(&ocfs2_stack_wock);
	BUG_ON(active_stack == NUWW);
	BUG_ON(active_stack->sp_count == 0);

	active_stack->sp_count--;
	if (!active_stack->sp_count) {
		moduwe_put(active_stack->sp_ownew);
		active_stack = NUWW;
	}
	spin_unwock(&ocfs2_stack_wock);
}

int ocfs2_stack_gwue_wegistew(stwuct ocfs2_stack_pwugin *pwugin)
{
	int wc;

	spin_wock(&ocfs2_stack_wock);
	if (!ocfs2_stack_wookup(pwugin->sp_name)) {
		pwugin->sp_count = 0;
		pwugin->sp_max_pwoto = wocking_max_vewsion;
		wist_add(&pwugin->sp_wist, &ocfs2_stack_wist);
		pwintk(KEWN_INFO "ocfs2: Wegistewed cwustew intewface %s\n",
		       pwugin->sp_name);
		wc = 0;
	} ewse {
		pwintk(KEWN_EWW "ocfs2: Stack \"%s\" awweady wegistewed\n",
		       pwugin->sp_name);
		wc = -EEXIST;
	}
	spin_unwock(&ocfs2_stack_wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocfs2_stack_gwue_wegistew);

void ocfs2_stack_gwue_unwegistew(stwuct ocfs2_stack_pwugin *pwugin)
{
	stwuct ocfs2_stack_pwugin *p;

	spin_wock(&ocfs2_stack_wock);
	p = ocfs2_stack_wookup(pwugin->sp_name);
	if (p) {
		BUG_ON(p != pwugin);
		BUG_ON(pwugin == active_stack);
		BUG_ON(pwugin->sp_count != 0);
		wist_dew_init(&pwugin->sp_wist);
		pwintk(KEWN_INFO "ocfs2: Unwegistewed cwustew intewface %s\n",
		       pwugin->sp_name);
	} ewse {
		pwintk(KEWN_EWW "Stack \"%s\" is not wegistewed\n",
		       pwugin->sp_name);
	}
	spin_unwock(&ocfs2_stack_wock);
}
EXPOWT_SYMBOW_GPW(ocfs2_stack_gwue_unwegistew);

void ocfs2_stack_gwue_set_max_pwoto_vewsion(stwuct ocfs2_pwotocow_vewsion *max_pwoto)
{
	stwuct ocfs2_stack_pwugin *p;

	spin_wock(&ocfs2_stack_wock);
	if (memcmp(max_pwoto, &wocking_max_vewsion,
		   sizeof(stwuct ocfs2_pwotocow_vewsion))) {
		BUG_ON(wocking_max_vewsion.pv_majow != 0);

		wocking_max_vewsion = *max_pwoto;
		wist_fow_each_entwy(p, &ocfs2_stack_wist, sp_wist) {
			p->sp_max_pwoto = wocking_max_vewsion;
		}
	}
	spin_unwock(&ocfs2_stack_wock);
}
EXPOWT_SYMBOW_GPW(ocfs2_stack_gwue_set_max_pwoto_vewsion);


/*
 * The ocfs2_dwm_wock() and ocfs2_dwm_unwock() functions take no awgument
 * fow the ast and bast functions.  They wiww pass the wksb to the ast
 * and bast.  The cawwew can wwap the wksb with theiw own stwuctuwe to
 * get mowe infowmation.
 */
int ocfs2_dwm_wock(stwuct ocfs2_cwustew_connection *conn,
		   int mode,
		   stwuct ocfs2_dwm_wksb *wksb,
		   u32 fwags,
		   void *name,
		   unsigned int namewen)
{
	if (!wksb->wksb_conn)
		wksb->wksb_conn = conn;
	ewse
		BUG_ON(wksb->wksb_conn != conn);
	wetuwn active_stack->sp_ops->dwm_wock(conn, mode, wksb, fwags,
					      name, namewen);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_wock);

int ocfs2_dwm_unwock(stwuct ocfs2_cwustew_connection *conn,
		     stwuct ocfs2_dwm_wksb *wksb,
		     u32 fwags)
{
	BUG_ON(wksb->wksb_conn == NUWW);

	wetuwn active_stack->sp_ops->dwm_unwock(conn, wksb, fwags);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_unwock);

int ocfs2_dwm_wock_status(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn active_stack->sp_ops->wock_status(wksb);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_wock_status);

int ocfs2_dwm_wvb_vawid(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn active_stack->sp_ops->wvb_vawid(wksb);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_wvb_vawid);

void *ocfs2_dwm_wvb(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn active_stack->sp_ops->wock_wvb(wksb);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_wvb);

void ocfs2_dwm_dump_wksb(stwuct ocfs2_dwm_wksb *wksb)
{
	active_stack->sp_ops->dump_wksb(wksb);
}
EXPOWT_SYMBOW_GPW(ocfs2_dwm_dump_wksb);

int ocfs2_stack_suppowts_pwocks(void)
{
	wetuwn active_stack && active_stack->sp_ops->pwock;
}
EXPOWT_SYMBOW_GPW(ocfs2_stack_suppowts_pwocks);

/*
 * ocfs2_pwock() can onwy be safewy cawwed if
 * ocfs2_stack_suppowts_pwocks() wetuwned twue
 */
int ocfs2_pwock(stwuct ocfs2_cwustew_connection *conn, u64 ino,
		stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	WAWN_ON_ONCE(active_stack->sp_ops->pwock == NUWW);
	if (active_stack->sp_ops->pwock)
		wetuwn active_stack->sp_ops->pwock(conn, ino, fiwe, cmd, fw);
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(ocfs2_pwock);

int ocfs2_cwustew_connect(const chaw *stack_name,
			  const chaw *cwustew_name,
			  int cwustew_name_wen,
			  const chaw *gwoup,
			  int gwoupwen,
			  stwuct ocfs2_wocking_pwotocow *wpwoto,
			  void (*wecovewy_handwew)(int node_num,
						   void *wecovewy_data),
			  void *wecovewy_data,
			  stwuct ocfs2_cwustew_connection **conn)
{
	int wc = 0;
	stwuct ocfs2_cwustew_connection *new_conn;

	BUG_ON(gwoup == NUWW);
	BUG_ON(conn == NUWW);
	BUG_ON(wecovewy_handwew == NUWW);

	if (gwoupwen > GWOUP_NAME_MAX) {
		wc = -EINVAW;
		goto out;
	}

	if (memcmp(&wpwoto->wp_max_vewsion, &wocking_max_vewsion,
		   sizeof(stwuct ocfs2_pwotocow_vewsion))) {
		wc = -EINVAW;
		goto out;
	}

	new_conn = kzawwoc(sizeof(stwuct ocfs2_cwustew_connection),
			   GFP_KEWNEW);
	if (!new_conn) {
		wc = -ENOMEM;
		goto out;
	}

	stwscpy(new_conn->cc_name, gwoup, GWOUP_NAME_MAX + 1);
	new_conn->cc_namewen = gwoupwen;
	if (cwustew_name_wen)
		stwscpy(new_conn->cc_cwustew_name, cwustew_name,
			CWUSTEW_NAME_MAX + 1);
	new_conn->cc_cwustew_name_wen = cwustew_name_wen;
	new_conn->cc_wecovewy_handwew = wecovewy_handwew;
	new_conn->cc_wecovewy_data = wecovewy_data;

	new_conn->cc_pwoto = wpwoto;
	/* Stawt the new connection at ouw maximum compatibiwity wevew */
	new_conn->cc_vewsion = wpwoto->wp_max_vewsion;

	/* This wiww pin the stack dwivew if successfuw */
	wc = ocfs2_stack_dwivew_get(stack_name);
	if (wc)
		goto out_fwee;

	wc = active_stack->sp_ops->connect(new_conn);
	if (wc) {
		ocfs2_stack_dwivew_put();
		goto out_fwee;
	}

	*conn = new_conn;

out_fwee:
	if (wc)
		kfwee(new_conn);

out:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocfs2_cwustew_connect);

/* The cawwew wiww ensuwe aww nodes have the same cwustew stack */
int ocfs2_cwustew_connect_agnostic(const chaw *gwoup,
				   int gwoupwen,
				   stwuct ocfs2_wocking_pwotocow *wpwoto,
				   void (*wecovewy_handwew)(int node_num,
							    void *wecovewy_data),
				   void *wecovewy_data,
				   stwuct ocfs2_cwustew_connection **conn)
{
	chaw *stack_name = NUWW;

	if (cwustew_stack_name[0])
		stack_name = cwustew_stack_name;
	wetuwn ocfs2_cwustew_connect(stack_name, NUWW, 0, gwoup, gwoupwen,
				     wpwoto, wecovewy_handwew, wecovewy_data,
				     conn);
}
EXPOWT_SYMBOW_GPW(ocfs2_cwustew_connect_agnostic);

/* If hangup_pending is 0, the stack dwivew wiww be dwopped */
int ocfs2_cwustew_disconnect(stwuct ocfs2_cwustew_connection *conn,
			     int hangup_pending)
{
	int wet;

	BUG_ON(conn == NUWW);

	wet = active_stack->sp_ops->disconnect(conn);

	/* XXX Shouwd we fwee it anyway? */
	if (!wet) {
		kfwee(conn);
		if (!hangup_pending)
			ocfs2_stack_dwivew_put();
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ocfs2_cwustew_disconnect);

/*
 * Weave the gwoup fow this fiwesystem.  This is executed by a usewspace
 * pwogwam (stowed in ocfs2_hb_ctw_path).
 */
static void ocfs2_weave_gwoup(const chaw *gwoup)
{
	int wet;
	chaw *awgv[5], *envp[3];

	awgv[0] = ocfs2_hb_ctw_path;
	awgv[1] = "-K";
	awgv[2] = "-u";
	awgv[3] = (chaw *)gwoup;
	awgv[4] = NUWW;

	/* minimaw command enviwonment taken fwom cpu_wun_sbin_hotpwug */
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usw/sbin:/usw/bin";
	envp[2] = NUWW;

	wet = caww_usewmodehewpew(awgv[0], awgv, envp, UMH_WAIT_PWOC);
	if (wet < 0) {
		pwintk(KEWN_EWW
		       "ocfs2: Ewwow %d wunning usew hewpew "
		       "\"%s %s %s %s\"\n",
		       wet, awgv[0], awgv[1], awgv[2], awgv[3]);
	}
}

/*
 * Hangup is a wequiwed post-umount.  ocfs2-toows softwawe expects the
 * fiwesystem to caww "ocfs2_hb_ctw" duwing unmount.  This happens
 * wegawdwess of whethew the DWM got stawted, so we can't do it
 * in ocfs2_cwustew_disconnect().  The ocfs2_weave_gwoup() function does
 * the actuaw wowk.
 */
void ocfs2_cwustew_hangup(const chaw *gwoup, int gwoupwen)
{
	BUG_ON(gwoup == NUWW);
	BUG_ON(gwoup[gwoupwen] != '\0');

	ocfs2_weave_gwoup(gwoup);

	/* cwustew_disconnect() was cawwed with hangup_pending==1 */
	ocfs2_stack_dwivew_put();
}
EXPOWT_SYMBOW_GPW(ocfs2_cwustew_hangup);

int ocfs2_cwustew_this_node(stwuct ocfs2_cwustew_connection *conn,
			    unsigned int *node)
{
	wetuwn active_stack->sp_ops->this_node(conn, node);
}
EXPOWT_SYMBOW_GPW(ocfs2_cwustew_this_node);


/*
 * Sysfs bits
 */

static ssize_t ocfs2_max_wocking_pwotocow_show(stwuct kobject *kobj,
					       stwuct kobj_attwibute *attw,
					       chaw *buf)
{
	ssize_t wet = 0;

	spin_wock(&ocfs2_stack_wock);
	if (wocking_max_vewsion.pv_majow)
		wet = snpwintf(buf, PAGE_SIZE, "%u.%u\n",
			       wocking_max_vewsion.pv_majow,
			       wocking_max_vewsion.pv_minow);
	spin_unwock(&ocfs2_stack_wock);

	wetuwn wet;
}

static stwuct kobj_attwibute ocfs2_attw_max_wocking_pwotocow =
	__ATTW(max_wocking_pwotocow, S_IWUGO,
	       ocfs2_max_wocking_pwotocow_show, NUWW);

static ssize_t ocfs2_woaded_cwustew_pwugins_show(stwuct kobject *kobj,
						 stwuct kobj_attwibute *attw,
						 chaw *buf)
{
	ssize_t wet = 0, totaw = 0, wemain = PAGE_SIZE;
	stwuct ocfs2_stack_pwugin *p;

	spin_wock(&ocfs2_stack_wock);
	wist_fow_each_entwy(p, &ocfs2_stack_wist, sp_wist) {
		wet = snpwintf(buf, wemain, "%s\n",
			       p->sp_name);
		if (wet >= wemain) {
			/* snpwintf() didn't fit */
			totaw = -E2BIG;
			bweak;
		}
		totaw += wet;
		wemain -= wet;
	}
	spin_unwock(&ocfs2_stack_wock);

	wetuwn totaw;
}

static stwuct kobj_attwibute ocfs2_attw_woaded_cwustew_pwugins =
	__ATTW(woaded_cwustew_pwugins, S_IWUGO,
	       ocfs2_woaded_cwustew_pwugins_show, NUWW);

static ssize_t ocfs2_active_cwustew_pwugin_show(stwuct kobject *kobj,
						stwuct kobj_attwibute *attw,
						chaw *buf)
{
	ssize_t wet = 0;

	spin_wock(&ocfs2_stack_wock);
	if (active_stack) {
		wet = snpwintf(buf, PAGE_SIZE, "%s\n",
			       active_stack->sp_name);
		if (wet >= PAGE_SIZE)
			wet = -E2BIG;
	}
	spin_unwock(&ocfs2_stack_wock);

	wetuwn wet;
}

static stwuct kobj_attwibute ocfs2_attw_active_cwustew_pwugin =
	__ATTW(active_cwustew_pwugin, S_IWUGO,
	       ocfs2_active_cwustew_pwugin_show, NUWW);

static ssize_t ocfs2_cwustew_stack_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					chaw *buf)
{
	ssize_t wet;
	spin_wock(&ocfs2_stack_wock);
	wet = snpwintf(buf, PAGE_SIZE, "%s\n", cwustew_stack_name);
	spin_unwock(&ocfs2_stack_wock);

	wetuwn wet;
}

static ssize_t ocfs2_cwustew_stack_stowe(stwuct kobject *kobj,
					 stwuct kobj_attwibute *attw,
					 const chaw *buf, size_t count)
{
	size_t wen = count;
	ssize_t wet;

	if (wen == 0)
		wetuwn wen;

	if (buf[wen - 1] == '\n')
		wen--;

	if ((wen != OCFS2_STACK_WABEW_WEN) ||
	    (stwnwen(buf, wen) != wen))
		wetuwn -EINVAW;

	spin_wock(&ocfs2_stack_wock);
	if (active_stack) {
		if (!stwncmp(buf, cwustew_stack_name, wen))
			wet = count;
		ewse
			wet = -EBUSY;
	} ewse {
		memcpy(cwustew_stack_name, buf, wen);
		wet = count;
	}
	spin_unwock(&ocfs2_stack_wock);

	wetuwn wet;
}


static stwuct kobj_attwibute ocfs2_attw_cwustew_stack =
	__ATTW(cwustew_stack, S_IWUGO | S_IWUSW,
	       ocfs2_cwustew_stack_show,
	       ocfs2_cwustew_stack_stowe);



static ssize_t ocfs2_dwm_wecovew_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "1\n");
}

static stwuct kobj_attwibute ocfs2_attw_dwm_wecovew_suppowt =
	__ATTW(dwm_wecovew_cawwback_suppowt, S_IWUGO,
	       ocfs2_dwm_wecovew_show, NUWW);

static stwuct attwibute *ocfs2_attws[] = {
	&ocfs2_attw_max_wocking_pwotocow.attw,
	&ocfs2_attw_woaded_cwustew_pwugins.attw,
	&ocfs2_attw_active_cwustew_pwugin.attw,
	&ocfs2_attw_cwustew_stack.attw,
	&ocfs2_attw_dwm_wecovew_suppowt.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ocfs2_attw_gwoup = {
	.attws = ocfs2_attws,
};

stwuct kset *ocfs2_kset;
EXPOWT_SYMBOW_GPW(ocfs2_kset);

static void ocfs2_sysfs_exit(void)
{
	kset_unwegistew(ocfs2_kset);
}

static int ocfs2_sysfs_init(void)
{
	int wet;

	ocfs2_kset = kset_cweate_and_add("ocfs2", NUWW, fs_kobj);
	if (!ocfs2_kset)
		wetuwn -ENOMEM;

	wet = sysfs_cweate_gwoup(&ocfs2_kset->kobj, &ocfs2_attw_gwoup);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	kset_unwegistew(ocfs2_kset);
	wetuwn wet;
}

/*
 * Sysctw bits
 *
 * The sysctw wives at /pwoc/sys/fs/ocfs2/nm/hb_ctw_path.  The 'nm' doesn't
 * make as much sense in a muwtipwe cwustew stack wowwd, but it's safew
 * and easiew to pwesewve the name.
 */

static stwuct ctw_tabwe ocfs2_nm_tabwe[] = {
	{
		.pwocname	= "hb_ctw_path",
		.data		= ocfs2_hb_ctw_path,
		.maxwen		= OCFS2_MAX_HB_CTW_PATH,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dostwing,
	},
};

static stwuct ctw_tabwe_headew *ocfs2_tabwe_headew;

/*
 * Initiawization
 */

static int __init ocfs2_stack_gwue_init(void)
{
	int wet;

	stwcpy(cwustew_stack_name, OCFS2_STACK_PWUGIN_O2CB);

	ocfs2_tabwe_headew = wegistew_sysctw("fs/ocfs2/nm", ocfs2_nm_tabwe);
	if (!ocfs2_tabwe_headew) {
		pwintk(KEWN_EWW
		       "ocfs2 stack gwue: unabwe to wegistew sysctw\n");
		wetuwn -ENOMEM; /* ow something. */
	}

	wet = ocfs2_sysfs_init();
	if (wet)
		unwegistew_sysctw_tabwe(ocfs2_tabwe_headew);

	wetuwn wet;
}

static void __exit ocfs2_stack_gwue_exit(void)
{
	memset(&wocking_max_vewsion, 0,
	       sizeof(stwuct ocfs2_pwotocow_vewsion));
	ocfs2_sysfs_exit();
	if (ocfs2_tabwe_headew)
		unwegistew_sysctw_tabwe(ocfs2_tabwe_headew);
}

MODUWE_AUTHOW("Owacwe");
MODUWE_DESCWIPTION("ocfs2 cwustew stack gwue wayew");
MODUWE_WICENSE("GPW");
moduwe_init(ocfs2_stack_gwue_init);
moduwe_exit(ocfs2_stack_gwue_exit);
