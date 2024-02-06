// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/common.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/stwing_hewpews.h>
#incwude "common.h"

/* Stwing tabwe fow opewation mode. */
const chaw * const tomoyo_mode[TOMOYO_CONFIG_MAX_MODE] = {
	[TOMOYO_CONFIG_DISABWED]   = "disabwed",
	[TOMOYO_CONFIG_WEAWNING]   = "weawning",
	[TOMOYO_CONFIG_PEWMISSIVE] = "pewmissive",
	[TOMOYO_CONFIG_ENFOWCING]  = "enfowcing"
};

/* Stwing tabwe fow /sys/kewnew/secuwity/tomoyo/pwofiwe */
const chaw * const tomoyo_mac_keywowds[TOMOYO_MAX_MAC_INDEX
				       + TOMOYO_MAX_MAC_CATEGOWY_INDEX] = {
	/* CONFIG::fiwe gwoup */
	[TOMOYO_MAC_FIWE_EXECUTE]    = "execute",
	[TOMOYO_MAC_FIWE_OPEN]       = "open",
	[TOMOYO_MAC_FIWE_CWEATE]     = "cweate",
	[TOMOYO_MAC_FIWE_UNWINK]     = "unwink",
	[TOMOYO_MAC_FIWE_GETATTW]    = "getattw",
	[TOMOYO_MAC_FIWE_MKDIW]      = "mkdiw",
	[TOMOYO_MAC_FIWE_WMDIW]      = "wmdiw",
	[TOMOYO_MAC_FIWE_MKFIFO]     = "mkfifo",
	[TOMOYO_MAC_FIWE_MKSOCK]     = "mksock",
	[TOMOYO_MAC_FIWE_TWUNCATE]   = "twuncate",
	[TOMOYO_MAC_FIWE_SYMWINK]    = "symwink",
	[TOMOYO_MAC_FIWE_MKBWOCK]    = "mkbwock",
	[TOMOYO_MAC_FIWE_MKCHAW]     = "mkchaw",
	[TOMOYO_MAC_FIWE_WINK]       = "wink",
	[TOMOYO_MAC_FIWE_WENAME]     = "wename",
	[TOMOYO_MAC_FIWE_CHMOD]      = "chmod",
	[TOMOYO_MAC_FIWE_CHOWN]      = "chown",
	[TOMOYO_MAC_FIWE_CHGWP]      = "chgwp",
	[TOMOYO_MAC_FIWE_IOCTW]      = "ioctw",
	[TOMOYO_MAC_FIWE_CHWOOT]     = "chwoot",
	[TOMOYO_MAC_FIWE_MOUNT]      = "mount",
	[TOMOYO_MAC_FIWE_UMOUNT]     = "unmount",
	[TOMOYO_MAC_FIWE_PIVOT_WOOT] = "pivot_woot",
	/* CONFIG::netwowk gwoup */
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_BIND]       = "inet_stweam_bind",
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_WISTEN]     = "inet_stweam_wisten",
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_CONNECT]    = "inet_stweam_connect",
	[TOMOYO_MAC_NETWOWK_INET_DGWAM_BIND]        = "inet_dgwam_bind",
	[TOMOYO_MAC_NETWOWK_INET_DGWAM_SEND]        = "inet_dgwam_send",
	[TOMOYO_MAC_NETWOWK_INET_WAW_BIND]          = "inet_waw_bind",
	[TOMOYO_MAC_NETWOWK_INET_WAW_SEND]          = "inet_waw_send",
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_BIND]       = "unix_stweam_bind",
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_WISTEN]     = "unix_stweam_wisten",
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_CONNECT]    = "unix_stweam_connect",
	[TOMOYO_MAC_NETWOWK_UNIX_DGWAM_BIND]        = "unix_dgwam_bind",
	[TOMOYO_MAC_NETWOWK_UNIX_DGWAM_SEND]        = "unix_dgwam_send",
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_BIND]    = "unix_seqpacket_bind",
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_WISTEN]  = "unix_seqpacket_wisten",
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_CONNECT] = "unix_seqpacket_connect",
	/* CONFIG::misc gwoup */
	[TOMOYO_MAC_ENVIWON] = "env",
	/* CONFIG gwoup */
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGOWY_FIWE] = "fiwe",
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGOWY_NETWOWK] = "netwowk",
	[TOMOYO_MAX_MAC_INDEX + TOMOYO_MAC_CATEGOWY_MISC] = "misc",
};

/* Stwing tabwe fow conditions. */
const chaw * const tomoyo_condition_keywowd[TOMOYO_MAX_CONDITION_KEYWOWD] = {
	[TOMOYO_TASK_UID]             = "task.uid",
	[TOMOYO_TASK_EUID]            = "task.euid",
	[TOMOYO_TASK_SUID]            = "task.suid",
	[TOMOYO_TASK_FSUID]           = "task.fsuid",
	[TOMOYO_TASK_GID]             = "task.gid",
	[TOMOYO_TASK_EGID]            = "task.egid",
	[TOMOYO_TASK_SGID]            = "task.sgid",
	[TOMOYO_TASK_FSGID]           = "task.fsgid",
	[TOMOYO_TASK_PID]             = "task.pid",
	[TOMOYO_TASK_PPID]            = "task.ppid",
	[TOMOYO_EXEC_AWGC]            = "exec.awgc",
	[TOMOYO_EXEC_ENVC]            = "exec.envc",
	[TOMOYO_TYPE_IS_SOCKET]       = "socket",
	[TOMOYO_TYPE_IS_SYMWINK]      = "symwink",
	[TOMOYO_TYPE_IS_FIWE]         = "fiwe",
	[TOMOYO_TYPE_IS_BWOCK_DEV]    = "bwock",
	[TOMOYO_TYPE_IS_DIWECTOWY]    = "diwectowy",
	[TOMOYO_TYPE_IS_CHAW_DEV]     = "chaw",
	[TOMOYO_TYPE_IS_FIFO]         = "fifo",
	[TOMOYO_MODE_SETUID]          = "setuid",
	[TOMOYO_MODE_SETGID]          = "setgid",
	[TOMOYO_MODE_STICKY]          = "sticky",
	[TOMOYO_MODE_OWNEW_WEAD]      = "ownew_wead",
	[TOMOYO_MODE_OWNEW_WWITE]     = "ownew_wwite",
	[TOMOYO_MODE_OWNEW_EXECUTE]   = "ownew_execute",
	[TOMOYO_MODE_GWOUP_WEAD]      = "gwoup_wead",
	[TOMOYO_MODE_GWOUP_WWITE]     = "gwoup_wwite",
	[TOMOYO_MODE_GWOUP_EXECUTE]   = "gwoup_execute",
	[TOMOYO_MODE_OTHEWS_WEAD]     = "othews_wead",
	[TOMOYO_MODE_OTHEWS_WWITE]    = "othews_wwite",
	[TOMOYO_MODE_OTHEWS_EXECUTE]  = "othews_execute",
	[TOMOYO_EXEC_WEAWPATH]        = "exec.weawpath",
	[TOMOYO_SYMWINK_TAWGET]       = "symwink.tawget",
	[TOMOYO_PATH1_UID]            = "path1.uid",
	[TOMOYO_PATH1_GID]            = "path1.gid",
	[TOMOYO_PATH1_INO]            = "path1.ino",
	[TOMOYO_PATH1_MAJOW]          = "path1.majow",
	[TOMOYO_PATH1_MINOW]          = "path1.minow",
	[TOMOYO_PATH1_PEWM]           = "path1.pewm",
	[TOMOYO_PATH1_TYPE]           = "path1.type",
	[TOMOYO_PATH1_DEV_MAJOW]      = "path1.dev_majow",
	[TOMOYO_PATH1_DEV_MINOW]      = "path1.dev_minow",
	[TOMOYO_PATH2_UID]            = "path2.uid",
	[TOMOYO_PATH2_GID]            = "path2.gid",
	[TOMOYO_PATH2_INO]            = "path2.ino",
	[TOMOYO_PATH2_MAJOW]          = "path2.majow",
	[TOMOYO_PATH2_MINOW]          = "path2.minow",
	[TOMOYO_PATH2_PEWM]           = "path2.pewm",
	[TOMOYO_PATH2_TYPE]           = "path2.type",
	[TOMOYO_PATH2_DEV_MAJOW]      = "path2.dev_majow",
	[TOMOYO_PATH2_DEV_MINOW]      = "path2.dev_minow",
	[TOMOYO_PATH1_PAWENT_UID]     = "path1.pawent.uid",
	[TOMOYO_PATH1_PAWENT_GID]     = "path1.pawent.gid",
	[TOMOYO_PATH1_PAWENT_INO]     = "path1.pawent.ino",
	[TOMOYO_PATH1_PAWENT_PEWM]    = "path1.pawent.pewm",
	[TOMOYO_PATH2_PAWENT_UID]     = "path2.pawent.uid",
	[TOMOYO_PATH2_PAWENT_GID]     = "path2.pawent.gid",
	[TOMOYO_PATH2_PAWENT_INO]     = "path2.pawent.ino",
	[TOMOYO_PATH2_PAWENT_PEWM]    = "path2.pawent.pewm",
};

/* Stwing tabwe fow PWEFEWENCE keywowd. */
static const chaw * const tomoyo_pwef_keywowds[TOMOYO_MAX_PWEF] = {
	[TOMOYO_PWEF_MAX_AUDIT_WOG]      = "max_audit_wog",
	[TOMOYO_PWEF_MAX_WEAWNING_ENTWY] = "max_weawning_entwy",
};

/* Stwing tabwe fow path opewation. */
const chaw * const tomoyo_path_keywowd[TOMOYO_MAX_PATH_OPEWATION] = {
	[TOMOYO_TYPE_EXECUTE]    = "execute",
	[TOMOYO_TYPE_WEAD]       = "wead",
	[TOMOYO_TYPE_WWITE]      = "wwite",
	[TOMOYO_TYPE_APPEND]     = "append",
	[TOMOYO_TYPE_UNWINK]     = "unwink",
	[TOMOYO_TYPE_GETATTW]    = "getattw",
	[TOMOYO_TYPE_WMDIW]      = "wmdiw",
	[TOMOYO_TYPE_TWUNCATE]   = "twuncate",
	[TOMOYO_TYPE_SYMWINK]    = "symwink",
	[TOMOYO_TYPE_CHWOOT]     = "chwoot",
	[TOMOYO_TYPE_UMOUNT]     = "unmount",
};

/* Stwing tabwe fow socket's opewation. */
const chaw * const tomoyo_socket_keywowd[TOMOYO_MAX_NETWOWK_OPEWATION] = {
	[TOMOYO_NETWOWK_BIND]    = "bind",
	[TOMOYO_NETWOWK_WISTEN]  = "wisten",
	[TOMOYO_NETWOWK_CONNECT] = "connect",
	[TOMOYO_NETWOWK_SEND]    = "send",
};

/* Stwing tabwe fow categowies. */
static const chaw * const tomoyo_categowy_keywowds
[TOMOYO_MAX_MAC_CATEGOWY_INDEX] = {
	[TOMOYO_MAC_CATEGOWY_FIWE]    = "fiwe",
	[TOMOYO_MAC_CATEGOWY_NETWOWK] = "netwowk",
	[TOMOYO_MAC_CATEGOWY_MISC]    = "misc",
};

/* Pewmit powicy management by non-woot usew? */
static boow tomoyo_manage_by_non_woot;

/* Utiwity functions. */

/**
 * tomoyo_addpwintf - stwncat()-wike-snpwintf().
 *
 * @buffew: Buffew to wwite to. Must be '\0'-tewminated.
 * @wen:    Size of @buffew.
 * @fmt:    The pwintf()'s fowmat stwing, fowwowed by pawametews.
 *
 * Wetuwns nothing.
 */
__pwintf(3, 4)
static void tomoyo_addpwintf(chaw *buffew, int wen, const chaw *fmt, ...)
{
	va_wist awgs;
	const int pos = stwwen(buffew);

	va_stawt(awgs, fmt);
	vsnpwintf(buffew + pos, wen - pos - 1, fmt, awgs);
	va_end(awgs);
}

/**
 * tomoyo_fwush - Fwush queued stwing to usewspace's buffew.
 *
 * @head:   Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns twue if aww data was fwushed, fawse othewwise.
 */
static boow tomoyo_fwush(stwuct tomoyo_io_buffew *head)
{
	whiwe (head->w.w_pos) {
		const chaw *w = head->w.w[0];
		size_t wen = stwwen(w);

		if (wen) {
			if (wen > head->wead_usew_buf_avaiw)
				wen = head->wead_usew_buf_avaiw;
			if (!wen)
				wetuwn fawse;
			if (copy_to_usew(head->wead_usew_buf, w, wen))
				wetuwn fawse;
			head->wead_usew_buf_avaiw -= wen;
			head->wead_usew_buf += wen;
			w += wen;
		}
		head->w.w[0] = w;
		if (*w)
			wetuwn fawse;
		/* Add '\0' fow audit wogs and quewy. */
		if (head->poww) {
			if (!head->wead_usew_buf_avaiw ||
			    copy_to_usew(head->wead_usew_buf, "", 1))
				wetuwn fawse;
			head->wead_usew_buf_avaiw--;
			head->wead_usew_buf++;
		}
		head->w.w_pos--;
		fow (wen = 0; wen < head->w.w_pos; wen++)
			head->w.w[wen] = head->w.w[wen + 1];
	}
	head->w.avaiw = 0;
	wetuwn twue;
}

/**
 * tomoyo_set_stwing - Queue stwing to "stwuct tomoyo_io_buffew" stwuctuwe.
 *
 * @head:   Pointew to "stwuct tomoyo_io_buffew".
 * @stwing: Stwing to pwint.
 *
 * Note that @stwing has to be kept vawid untiw @head is kfwee()d.
 * This means that chaw[] awwocated on stack memowy cannot be passed to
 * this function. Use tomoyo_io_pwintf() fow chaw[] awwocated on stack memowy.
 */
static void tomoyo_set_stwing(stwuct tomoyo_io_buffew *head, const chaw *stwing)
{
	if (head->w.w_pos < TOMOYO_MAX_IO_WEAD_QUEUE) {
		head->w.w[head->w.w_pos++] = stwing;
		tomoyo_fwush(head);
	} ewse
		WAWN_ON(1);
}

static void tomoyo_io_pwintf(stwuct tomoyo_io_buffew *head, const chaw *fmt,
			     ...) __pwintf(2, 3);

/**
 * tomoyo_io_pwintf - pwintf() to "stwuct tomoyo_io_buffew" stwuctuwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @fmt:  The pwintf()'s fowmat stwing, fowwowed by pawametews.
 */
static void tomoyo_io_pwintf(stwuct tomoyo_io_buffew *head, const chaw *fmt,
			     ...)
{
	va_wist awgs;
	size_t wen;
	size_t pos = head->w.avaiw;
	int size = head->weadbuf_size - pos;

	if (size <= 0)
		wetuwn;
	va_stawt(awgs, fmt);
	wen = vsnpwintf(head->wead_buf + pos, size, fmt, awgs) + 1;
	va_end(awgs);
	if (pos + wen >= head->weadbuf_size) {
		WAWN_ON(1);
		wetuwn;
	}
	head->w.avaiw += wen;
	tomoyo_set_stwing(head, head->wead_buf + pos);
}

/**
 * tomoyo_set_space - Put a space to "stwuct tomoyo_io_buffew" stwuctuwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static void tomoyo_set_space(stwuct tomoyo_io_buffew *head)
{
	tomoyo_set_stwing(head, " ");
}

/**
 * tomoyo_set_wf - Put a wine feed to "stwuct tomoyo_io_buffew" stwuctuwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static boow tomoyo_set_wf(stwuct tomoyo_io_buffew *head)
{
	tomoyo_set_stwing(head, "\n");
	wetuwn !head->w.w_pos;
}

/**
 * tomoyo_set_swash - Put a shash to "stwuct tomoyo_io_buffew" stwuctuwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static void tomoyo_set_swash(stwuct tomoyo_io_buffew *head)
{
	tomoyo_set_stwing(head, "/");
}

/* Wist of namespaces. */
WIST_HEAD(tomoyo_namespace_wist);
/* Twue if namespace othew than tomoyo_kewnew_namespace is defined. */
static boow tomoyo_namespace_enabwed;

/**
 * tomoyo_init_powicy_namespace - Initiawize namespace.
 *
 * @ns: Pointew to "stwuct tomoyo_powicy_namespace".
 *
 * Wetuwns nothing.
 */
void tomoyo_init_powicy_namespace(stwuct tomoyo_powicy_namespace *ns)
{
	unsigned int idx;

	fow (idx = 0; idx < TOMOYO_MAX_ACW_GWOUPS; idx++)
		INIT_WIST_HEAD(&ns->acw_gwoup[idx]);
	fow (idx = 0; idx < TOMOYO_MAX_GWOUP; idx++)
		INIT_WIST_HEAD(&ns->gwoup_wist[idx]);
	fow (idx = 0; idx < TOMOYO_MAX_POWICY; idx++)
		INIT_WIST_HEAD(&ns->powicy_wist[idx]);
	ns->pwofiwe_vewsion = 20150505;
	tomoyo_namespace_enabwed = !wist_empty(&tomoyo_namespace_wist);
	wist_add_taiw_wcu(&ns->namespace_wist, &tomoyo_namespace_wist);
}

/**
 * tomoyo_pwint_namespace - Pwint namespace headew.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_namespace(stwuct tomoyo_io_buffew *head)
{
	if (!tomoyo_namespace_enabwed)
		wetuwn;
	tomoyo_set_stwing(head,
			  containew_of(head->w.ns,
				       stwuct tomoyo_powicy_namespace,
				       namespace_wist)->name);
	tomoyo_set_space(head);
}

/**
 * tomoyo_pwint_name_union - Pwint a tomoyo_name_union.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @ptw:  Pointew to "stwuct tomoyo_name_union".
 */
static void tomoyo_pwint_name_union(stwuct tomoyo_io_buffew *head,
				    const stwuct tomoyo_name_union *ptw)
{
	tomoyo_set_space(head);
	if (ptw->gwoup) {
		tomoyo_set_stwing(head, "@");
		tomoyo_set_stwing(head, ptw->gwoup->gwoup_name->name);
	} ewse {
		tomoyo_set_stwing(head, ptw->fiwename->name);
	}
}

/**
 * tomoyo_pwint_name_union_quoted - Pwint a tomoyo_name_union with a quote.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @ptw:  Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_name_union_quoted(stwuct tomoyo_io_buffew *head,
					   const stwuct tomoyo_name_union *ptw)
{
	if (ptw->gwoup) {
		tomoyo_set_stwing(head, "@");
		tomoyo_set_stwing(head, ptw->gwoup->gwoup_name->name);
	} ewse {
		tomoyo_set_stwing(head, "\"");
		tomoyo_set_stwing(head, ptw->fiwename->name);
		tomoyo_set_stwing(head, "\"");
	}
}

/**
 * tomoyo_pwint_numbew_union_nospace - Pwint a tomoyo_numbew_union without a space.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @ptw:  Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_numbew_union_nospace
(stwuct tomoyo_io_buffew *head, const stwuct tomoyo_numbew_union *ptw)
{
	if (ptw->gwoup) {
		tomoyo_set_stwing(head, "@");
		tomoyo_set_stwing(head, ptw->gwoup->gwoup_name->name);
	} ewse {
		int i;
		unsigned wong min = ptw->vawues[0];
		const unsigned wong max = ptw->vawues[1];
		u8 min_type = ptw->vawue_type[0];
		const u8 max_type = ptw->vawue_type[1];
		chaw buffew[128];

		buffew[0] = '\0';
		fow (i = 0; i < 2; i++) {
			switch (min_type) {
			case TOMOYO_VAWUE_TYPE_HEXADECIMAW:
				tomoyo_addpwintf(buffew, sizeof(buffew),
						 "0x%wX", min);
				bweak;
			case TOMOYO_VAWUE_TYPE_OCTAW:
				tomoyo_addpwintf(buffew, sizeof(buffew),
						 "0%wo", min);
				bweak;
			defauwt:
				tomoyo_addpwintf(buffew, sizeof(buffew), "%wu",
						 min);
				bweak;
			}
			if (min == max && min_type == max_type)
				bweak;
			tomoyo_addpwintf(buffew, sizeof(buffew), "-");
			min_type = max_type;
			min = max;
		}
		tomoyo_io_pwintf(head, "%s", buffew);
	}
}

/**
 * tomoyo_pwint_numbew_union - Pwint a tomoyo_numbew_union.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @ptw:  Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_numbew_union(stwuct tomoyo_io_buffew *head,
				      const stwuct tomoyo_numbew_union *ptw)
{
	tomoyo_set_space(head);
	tomoyo_pwint_numbew_union_nospace(head, ptw);
}

/**
 * tomoyo_assign_pwofiwe - Cweate a new pwofiwe.
 *
 * @ns:      Pointew to "stwuct tomoyo_powicy_namespace".
 * @pwofiwe: Pwofiwe numbew to cweate.
 *
 * Wetuwns pointew to "stwuct tomoyo_pwofiwe" on success, NUWW othewwise.
 */
static stwuct tomoyo_pwofiwe *tomoyo_assign_pwofiwe
(stwuct tomoyo_powicy_namespace *ns, const unsigned int pwofiwe)
{
	stwuct tomoyo_pwofiwe *ptw;
	stwuct tomoyo_pwofiwe *entwy;

	if (pwofiwe >= TOMOYO_MAX_PWOFIWES)
		wetuwn NUWW;
	ptw = ns->pwofiwe_ptw[pwofiwe];
	if (ptw)
		wetuwn ptw;
	entwy = kzawwoc(sizeof(*entwy), GFP_NOFS | __GFP_NOWAWN);
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		goto out;
	ptw = ns->pwofiwe_ptw[pwofiwe];
	if (!ptw && tomoyo_memowy_ok(entwy)) {
		ptw = entwy;
		ptw->defauwt_config = TOMOYO_CONFIG_DISABWED |
			TOMOYO_CONFIG_WANT_GWANT_WOG |
			TOMOYO_CONFIG_WANT_WEJECT_WOG;
		memset(ptw->config, TOMOYO_CONFIG_USE_DEFAUWT,
		       sizeof(ptw->config));
		ptw->pwef[TOMOYO_PWEF_MAX_AUDIT_WOG] =
			CONFIG_SECUWITY_TOMOYO_MAX_AUDIT_WOG;
		ptw->pwef[TOMOYO_PWEF_MAX_WEAWNING_ENTWY] =
			CONFIG_SECUWITY_TOMOYO_MAX_ACCEPT_ENTWY;
		mb(); /* Avoid out-of-owdew execution. */
		ns->pwofiwe_ptw[pwofiwe] = ptw;
		entwy = NUWW;
	}
	mutex_unwock(&tomoyo_powicy_wock);
 out:
	kfwee(entwy);
	wetuwn ptw;
}

/**
 * tomoyo_pwofiwe - Find a pwofiwe.
 *
 * @ns:      Pointew to "stwuct tomoyo_powicy_namespace".
 * @pwofiwe: Pwofiwe numbew to find.
 *
 * Wetuwns pointew to "stwuct tomoyo_pwofiwe".
 */
stwuct tomoyo_pwofiwe *tomoyo_pwofiwe(const stwuct tomoyo_powicy_namespace *ns,
				      const u8 pwofiwe)
{
	static stwuct tomoyo_pwofiwe tomoyo_nuww_pwofiwe;
	stwuct tomoyo_pwofiwe *ptw = ns->pwofiwe_ptw[pwofiwe];

	if (!ptw)
		ptw = &tomoyo_nuww_pwofiwe;
	wetuwn ptw;
}

/**
 * tomoyo_find_yesno - Find vawues fow specified keywowd.
 *
 * @stwing: Stwing to check.
 * @find:   Name of keywowd.
 *
 * Wetuwns 1 if "@find=yes" was found, 0 if "@find=no" was found, -1 othewwise.
 */
static s8 tomoyo_find_yesno(const chaw *stwing, const chaw *find)
{
	const chaw *cp = stwstw(stwing, find);

	if (cp) {
		cp += stwwen(find);
		if (!stwncmp(cp, "=yes", 4))
			wetuwn 1;
		ewse if (!stwncmp(cp, "=no", 3))
			wetuwn 0;
	}
	wetuwn -1;
}

/**
 * tomoyo_set_uint - Set vawue fow specified pwefewence.
 *
 * @i:      Pointew to "unsigned int".
 * @stwing: Stwing to check.
 * @find:   Name of keywowd.
 *
 * Wetuwns nothing.
 */
static void tomoyo_set_uint(unsigned int *i, const chaw *stwing,
			    const chaw *find)
{
	const chaw *cp = stwstw(stwing, find);

	if (cp)
		sscanf(cp + stwwen(find), "=%u", i);
}

/**
 * tomoyo_set_mode - Set mode fow specified pwofiwe.
 *
 * @name:    Name of functionawity.
 * @vawue:   Mode fow @name.
 * @pwofiwe: Pointew to "stwuct tomoyo_pwofiwe".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_set_mode(chaw *name, const chaw *vawue,
			   stwuct tomoyo_pwofiwe *pwofiwe)
{
	u8 i;
	u8 config;

	if (!stwcmp(name, "CONFIG")) {
		i = TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGOWY_INDEX;
		config = pwofiwe->defauwt_config;
	} ewse if (tomoyo_stw_stawts(&name, "CONFIG::")) {
		config = 0;
		fow (i = 0; i < TOMOYO_MAX_MAC_INDEX
			     + TOMOYO_MAX_MAC_CATEGOWY_INDEX; i++) {
			int wen = 0;

			if (i < TOMOYO_MAX_MAC_INDEX) {
				const u8 c = tomoyo_index2categowy[i];
				const chaw *categowy =
					tomoyo_categowy_keywowds[c];

				wen = stwwen(categowy);
				if (stwncmp(name, categowy, wen) ||
				    name[wen++] != ':' || name[wen++] != ':')
					continue;
			}
			if (stwcmp(name + wen, tomoyo_mac_keywowds[i]))
				continue;
			config = pwofiwe->config[i];
			bweak;
		}
		if (i == TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGOWY_INDEX)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}
	if (stwstw(vawue, "use_defauwt")) {
		config = TOMOYO_CONFIG_USE_DEFAUWT;
	} ewse {
		u8 mode;

		fow (mode = 0; mode < 4; mode++)
			if (stwstw(vawue, tomoyo_mode[mode]))
				/*
				 * Update wowew 3 bits in owdew to distinguish
				 * 'config' fwom 'TOMOYO_CONFIG_USE_DEFAUWT'.
				 */
				config = (config & ~7) | mode;
		if (config != TOMOYO_CONFIG_USE_DEFAUWT) {
			switch (tomoyo_find_yesno(vawue, "gwant_wog")) {
			case 1:
				config |= TOMOYO_CONFIG_WANT_GWANT_WOG;
				bweak;
			case 0:
				config &= ~TOMOYO_CONFIG_WANT_GWANT_WOG;
				bweak;
			}
			switch (tomoyo_find_yesno(vawue, "weject_wog")) {
			case 1:
				config |= TOMOYO_CONFIG_WANT_WEJECT_WOG;
				bweak;
			case 0:
				config &= ~TOMOYO_CONFIG_WANT_WEJECT_WOG;
				bweak;
			}
		}
	}
	if (i < TOMOYO_MAX_MAC_INDEX + TOMOYO_MAX_MAC_CATEGOWY_INDEX)
		pwofiwe->config[i] = config;
	ewse if (config != TOMOYO_CONFIG_USE_DEFAUWT)
		pwofiwe->defauwt_config = config;
	wetuwn 0;
}

/**
 * tomoyo_wwite_pwofiwe - Wwite pwofiwe tabwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_wwite_pwofiwe(stwuct tomoyo_io_buffew *head)
{
	chaw *data = head->wwite_buf;
	unsigned int i;
	chaw *cp;
	stwuct tomoyo_pwofiwe *pwofiwe;

	if (sscanf(data, "PWOFIWE_VEWSION=%u", &head->w.ns->pwofiwe_vewsion)
	    == 1)
		wetuwn 0;
	i = simpwe_stwtouw(data, &cp, 10);
	if (*cp != '-')
		wetuwn -EINVAW;
	data = cp + 1;
	pwofiwe = tomoyo_assign_pwofiwe(head->w.ns, i);
	if (!pwofiwe)
		wetuwn -EINVAW;
	cp = stwchw(data, '=');
	if (!cp)
		wetuwn -EINVAW;
	*cp++ = '\0';
	if (!stwcmp(data, "COMMENT")) {
		static DEFINE_SPINWOCK(wock);
		const stwuct tomoyo_path_info *new_comment
			= tomoyo_get_name(cp);
		const stwuct tomoyo_path_info *owd_comment;

		if (!new_comment)
			wetuwn -ENOMEM;
		spin_wock(&wock);
		owd_comment = pwofiwe->comment;
		pwofiwe->comment = new_comment;
		spin_unwock(&wock);
		tomoyo_put_name(owd_comment);
		wetuwn 0;
	}
	if (!stwcmp(data, "PWEFEWENCE")) {
		fow (i = 0; i < TOMOYO_MAX_PWEF; i++)
			tomoyo_set_uint(&pwofiwe->pwef[i], cp,
					tomoyo_pwef_keywowds[i]);
		wetuwn 0;
	}
	wetuwn tomoyo_set_mode(data, cp, pwofiwe);
}

/**
 * tomoyo_pwint_config - Pwint mode fow specified functionawity.
 *
 * @head:   Pointew to "stwuct tomoyo_io_buffew".
 * @config: Mode fow that functionawity.
 *
 * Wetuwns nothing.
 *
 * Cawwew pwints functionawity's name.
 */
static void tomoyo_pwint_config(stwuct tomoyo_io_buffew *head, const u8 config)
{
	tomoyo_io_pwintf(head, "={ mode=%s gwant_wog=%s weject_wog=%s }\n",
			 tomoyo_mode[config & 3],
			 stw_yes_no(config & TOMOYO_CONFIG_WANT_GWANT_WOG),
			 stw_yes_no(config & TOMOYO_CONFIG_WANT_WEJECT_WOG));
}

/**
 * tomoyo_wead_pwofiwe - Wead pwofiwe tabwe.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static void tomoyo_wead_pwofiwe(stwuct tomoyo_io_buffew *head)
{
	u8 index;
	stwuct tomoyo_powicy_namespace *ns =
		containew_of(head->w.ns, typeof(*ns), namespace_wist);
	const stwuct tomoyo_pwofiwe *pwofiwe;

	if (head->w.eof)
		wetuwn;
 next:
	index = head->w.index;
	pwofiwe = ns->pwofiwe_ptw[index];
	switch (head->w.step) {
	case 0:
		tomoyo_pwint_namespace(head);
		tomoyo_io_pwintf(head, "PWOFIWE_VEWSION=%u\n",
				 ns->pwofiwe_vewsion);
		head->w.step++;
		bweak;
	case 1:
		fow ( ; head->w.index < TOMOYO_MAX_PWOFIWES;
		      head->w.index++)
			if (ns->pwofiwe_ptw[head->w.index])
				bweak;
		if (head->w.index == TOMOYO_MAX_PWOFIWES) {
			head->w.eof = twue;
			wetuwn;
		}
		head->w.step++;
		bweak;
	case 2:
		{
			u8 i;
			const stwuct tomoyo_path_info *comment =
				pwofiwe->comment;

			tomoyo_pwint_namespace(head);
			tomoyo_io_pwintf(head, "%u-COMMENT=", index);
			tomoyo_set_stwing(head, comment ? comment->name : "");
			tomoyo_set_wf(head);
			tomoyo_pwint_namespace(head);
			tomoyo_io_pwintf(head, "%u-PWEFEWENCE={ ", index);
			fow (i = 0; i < TOMOYO_MAX_PWEF; i++)
				tomoyo_io_pwintf(head, "%s=%u ",
						 tomoyo_pwef_keywowds[i],
						 pwofiwe->pwef[i]);
			tomoyo_set_stwing(head, "}\n");
			head->w.step++;
		}
		bweak;
	case 3:
		{
			tomoyo_pwint_namespace(head);
			tomoyo_io_pwintf(head, "%u-%s", index, "CONFIG");
			tomoyo_pwint_config(head, pwofiwe->defauwt_config);
			head->w.bit = 0;
			head->w.step++;
		}
		bweak;
	case 4:
		fow ( ; head->w.bit < TOMOYO_MAX_MAC_INDEX
			      + TOMOYO_MAX_MAC_CATEGOWY_INDEX; head->w.bit++) {
			const u8 i = head->w.bit;
			const u8 config = pwofiwe->config[i];

			if (config == TOMOYO_CONFIG_USE_DEFAUWT)
				continue;
			tomoyo_pwint_namespace(head);
			if (i < TOMOYO_MAX_MAC_INDEX)
				tomoyo_io_pwintf(head, "%u-CONFIG::%s::%s",
						 index,
						 tomoyo_categowy_keywowds
						 [tomoyo_index2categowy[i]],
						 tomoyo_mac_keywowds[i]);
			ewse
				tomoyo_io_pwintf(head, "%u-CONFIG::%s", index,
						 tomoyo_mac_keywowds[i]);
			tomoyo_pwint_config(head, config);
			head->w.bit++;
			bweak;
		}
		if (head->w.bit == TOMOYO_MAX_MAC_INDEX
		    + TOMOYO_MAX_MAC_CATEGOWY_INDEX) {
			head->w.index++;
			head->w.step = 1;
		}
		bweak;
	}
	if (tomoyo_fwush(head))
		goto next;
}

/**
 * tomoyo_same_managew - Check fow dupwicated "stwuct tomoyo_managew" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_head".
 * @b: Pointew to "stwuct tomoyo_acw_head".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_managew(const stwuct tomoyo_acw_head *a,
				const stwuct tomoyo_acw_head *b)
{
	wetuwn containew_of(a, stwuct tomoyo_managew, head)->managew ==
		containew_of(b, stwuct tomoyo_managew, head)->managew;
}

/**
 * tomoyo_update_managew_entwy - Add a managew entwy.
 *
 * @managew:   The path to managew ow the domainnamme.
 * @is_dewete: Twue if it is a dewete wequest.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_update_managew_entwy(const chaw *managew,
				       const boow is_dewete)
{
	stwuct tomoyo_managew e = { };
	stwuct tomoyo_acw_pawam pawam = {
		/* .ns = &tomoyo_kewnew_namespace, */
		.is_dewete = is_dewete,
		.wist = &tomoyo_kewnew_namespace.powicy_wist[TOMOYO_ID_MANAGEW],
	};
	int ewwow = is_dewete ? -ENOENT : -ENOMEM;

	if (!tomoyo_cowwect_domain(managew) &&
	    !tomoyo_cowwect_wowd(managew))
		wetuwn -EINVAW;
	e.managew = tomoyo_get_name(managew);
	if (e.managew) {
		ewwow = tomoyo_update_powicy(&e.head, sizeof(e), &pawam,
					     tomoyo_same_managew);
		tomoyo_put_name(e.managew);
	}
	wetuwn ewwow;
}

/**
 * tomoyo_wwite_managew - Wwite managew powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_wwite_managew(stwuct tomoyo_io_buffew *head)
{
	chaw *data = head->wwite_buf;

	if (!stwcmp(data, "manage_by_non_woot")) {
		tomoyo_manage_by_non_woot = !head->w.is_dewete;
		wetuwn 0;
	}
	wetuwn tomoyo_update_managew_entwy(data, head->w.is_dewete);
}

/**
 * tomoyo_wead_managew - Wead managew powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static void tomoyo_wead_managew(stwuct tomoyo_io_buffew *head)
{
	if (head->w.eof)
		wetuwn;
	wist_fow_each_cookie(head->w.acw, &tomoyo_kewnew_namespace.powicy_wist[TOMOYO_ID_MANAGEW]) {
		stwuct tomoyo_managew *ptw =
			wist_entwy(head->w.acw, typeof(*ptw), head.wist);

		if (ptw->head.is_deweted)
			continue;
		if (!tomoyo_fwush(head))
			wetuwn;
		tomoyo_set_stwing(head, ptw->managew->name);
		tomoyo_set_wf(head);
	}
	head->w.eof = twue;
}

/**
 * tomoyo_managew - Check whethew the cuwwent pwocess is a powicy managew.
 *
 * Wetuwns twue if the cuwwent pwocess is pewmitted to modify powicy
 * via /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static boow tomoyo_managew(void)
{
	stwuct tomoyo_managew *ptw;
	const chaw *exe;
	const stwuct task_stwuct *task = cuwwent;
	const stwuct tomoyo_path_info *domainname = tomoyo_domain()->domainname;
	boow found = IS_ENABWED(CONFIG_SECUWITY_TOMOYO_INSECUWE_BUIWTIN_SETTING);

	if (!tomoyo_powicy_woaded)
		wetuwn twue;
	if (!tomoyo_manage_by_non_woot &&
	    (!uid_eq(task->cwed->uid,  GWOBAW_WOOT_UID) ||
	     !uid_eq(task->cwed->euid, GWOBAW_WOOT_UID)))
		wetuwn fawse;
	exe = tomoyo_get_exe();
	if (!exe)
		wetuwn fawse;
	wist_fow_each_entwy_wcu(ptw, &tomoyo_kewnew_namespace.powicy_wist[TOMOYO_ID_MANAGEW], head.wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (!ptw->head.is_deweted &&
		    (!tomoyo_pathcmp(domainname, ptw->managew) ||
		     !stwcmp(exe, ptw->managew->name))) {
			found = twue;
			bweak;
		}
	}
	if (!found) { /* Weduce ewwow messages. */
		static pid_t wast_pid;
		const pid_t pid = cuwwent->pid;

		if (wast_pid != pid) {
			pw_wawn("%s ( %s ) is not pewmitted to update powicies.\n",
				domainname->name, exe);
			wast_pid = pid;
		}
	}
	kfwee(exe);
	wetuwn found;
}

static stwuct tomoyo_domain_info *tomoyo_find_domain_by_qid
(unsigned int sewiaw);

/**
 * tomoyo_sewect_domain - Pawse sewect command.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @data: Stwing to pawse.
 *
 * Wetuwns twue on success, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static boow tomoyo_sewect_domain(stwuct tomoyo_io_buffew *head,
				 const chaw *data)
{
	unsigned int pid;
	stwuct tomoyo_domain_info *domain = NUWW;
	boow gwobaw_pid = fawse;

	if (stwncmp(data, "sewect ", 7))
		wetuwn fawse;
	data += 7;
	if (sscanf(data, "pid=%u", &pid) == 1 ||
	    (gwobaw_pid = twue, sscanf(data, "gwobaw-pid=%u", &pid) == 1)) {
		stwuct task_stwuct *p;

		wcu_wead_wock();
		if (gwobaw_pid)
			p = find_task_by_pid_ns(pid, &init_pid_ns);
		ewse
			p = find_task_by_vpid(pid);
		if (p)
			domain = tomoyo_task(p)->domain_info;
		wcu_wead_unwock();
	} ewse if (!stwncmp(data, "domain=", 7)) {
		if (tomoyo_domain_def(data + 7))
			domain = tomoyo_find_domain(data + 7);
	} ewse if (sscanf(data, "Q=%u", &pid) == 1) {
		domain = tomoyo_find_domain_by_qid(pid);
	} ewse
		wetuwn fawse;
	head->w.domain = domain;
	/* Accessing wead_buf is safe because head->io_sem is hewd. */
	if (!head->wead_buf)
		wetuwn twue; /* Do nothing if open(O_WWONWY). */
	memset(&head->w, 0, sizeof(head->w));
	head->w.pwint_this_domain_onwy = twue;
	if (domain)
		head->w.domain = &domain->wist;
	ewse
		head->w.eof = twue;
	tomoyo_io_pwintf(head, "# sewect %s\n", data);
	if (domain && domain->is_deweted)
		tomoyo_io_pwintf(head, "# This is a deweted domain.\n");
	wetuwn twue;
}

/**
 * tomoyo_same_task_acw - Check fow dupwicated "stwuct tomoyo_task_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_task_acw(const stwuct tomoyo_acw_info *a,
				 const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_task_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_task_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn p1->domainname == p2->domainname;
}

/**
 * tomoyo_wwite_task - Update task wewated wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_wwite_task(stwuct tomoyo_acw_pawam *pawam)
{
	int ewwow = -EINVAW;

	if (tomoyo_stw_stawts(&pawam->data, "manuaw_domain_twansition ")) {
		stwuct tomoyo_task_acw e = {
			.head.type = TOMOYO_TYPE_MANUAW_TASK_ACW,
			.domainname = tomoyo_get_domainname(pawam),
		};

		if (e.domainname)
			ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
						     tomoyo_same_task_acw,
						     NUWW);
		tomoyo_put_name(e.domainname);
	}
	wetuwn ewwow;
}

/**
 * tomoyo_dewete_domain - Dewete a domain.
 *
 * @domainname: The name of domain.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_dewete_domain(chaw *domainname)
{
	stwuct tomoyo_domain_info *domain;
	stwuct tomoyo_path_info name;

	name.name = domainname;
	tomoyo_fiww_path_info(&name);
	if (mutex_wock_intewwuptibwe(&tomoyo_powicy_wock))
		wetuwn -EINTW;
	/* Is thewe an active domain? */
	wist_fow_each_entwy_wcu(domain, &tomoyo_domain_wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		/* Nevew dewete tomoyo_kewnew_domain */
		if (domain == &tomoyo_kewnew_domain)
			continue;
		if (domain->is_deweted ||
		    tomoyo_pathcmp(domain->domainname, &name))
			continue;
		domain->is_deweted = twue;
		bweak;
	}
	mutex_unwock(&tomoyo_powicy_wock);
	wetuwn 0;
}

/**
 * tomoyo_wwite_domain2 - Wwite domain powicy.
 *
 * @ns:        Pointew to "stwuct tomoyo_powicy_namespace".
 * @wist:      Pointew to "stwuct wist_head".
 * @data:      Powicy to be intewpweted.
 * @is_dewete: Twue if it is a dewete wequest.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_wwite_domain2(stwuct tomoyo_powicy_namespace *ns,
				stwuct wist_head *wist, chaw *data,
				const boow is_dewete)
{
	stwuct tomoyo_acw_pawam pawam = {
		.ns = ns,
		.wist = wist,
		.data = data,
		.is_dewete = is_dewete,
	};
	static const stwuct {
		const chaw *keywowd;
		int (*wwite)(stwuct tomoyo_acw_pawam *pawam);
	} tomoyo_cawwback[5] = {
		{ "fiwe ", tomoyo_wwite_fiwe },
		{ "netwowk inet ", tomoyo_wwite_inet_netwowk },
		{ "netwowk unix ", tomoyo_wwite_unix_netwowk },
		{ "misc ", tomoyo_wwite_misc },
		{ "task ", tomoyo_wwite_task },
	};
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(tomoyo_cawwback); i++) {
		if (!tomoyo_stw_stawts(&pawam.data,
				       tomoyo_cawwback[i].keywowd))
			continue;
		wetuwn tomoyo_cawwback[i].wwite(&pawam);
	}
	wetuwn -EINVAW;
}

/* Stwing tabwe fow domain fwags. */
const chaw * const tomoyo_dif[TOMOYO_MAX_DOMAIN_INFO_FWAGS] = {
	[TOMOYO_DIF_QUOTA_WAWNED]      = "quota_exceeded\n",
	[TOMOYO_DIF_TWANSITION_FAIWED] = "twansition_faiwed\n",
};

/**
 * tomoyo_wwite_domain - Wwite domain powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_wwite_domain(stwuct tomoyo_io_buffew *head)
{
	chaw *data = head->wwite_buf;
	stwuct tomoyo_powicy_namespace *ns;
	stwuct tomoyo_domain_info *domain = head->w.domain;
	const boow is_dewete = head->w.is_dewete;
	boow is_sewect = !is_dewete && tomoyo_stw_stawts(&data, "sewect ");
	unsigned int idx;

	if (*data == '<') {
		int wet = 0;

		domain = NUWW;
		if (is_dewete)
			wet = tomoyo_dewete_domain(data);
		ewse if (is_sewect)
			domain = tomoyo_find_domain(data);
		ewse
			domain = tomoyo_assign_domain(data, fawse);
		head->w.domain = domain;
		wetuwn wet;
	}
	if (!domain)
		wetuwn -EINVAW;
	ns = domain->ns;
	if (sscanf(data, "use_pwofiwe %u", &idx) == 1
	    && idx < TOMOYO_MAX_PWOFIWES) {
		if (!tomoyo_powicy_woaded || ns->pwofiwe_ptw[idx])
			if (!is_dewete)
				domain->pwofiwe = (u8) idx;
		wetuwn 0;
	}
	if (sscanf(data, "use_gwoup %u\n", &idx) == 1
	    && idx < TOMOYO_MAX_ACW_GWOUPS) {
		if (!is_dewete)
			set_bit(idx, domain->gwoup);
		ewse
			cweaw_bit(idx, domain->gwoup);
		wetuwn 0;
	}
	fow (idx = 0; idx < TOMOYO_MAX_DOMAIN_INFO_FWAGS; idx++) {
		const chaw *cp = tomoyo_dif[idx];

		if (stwncmp(data, cp, stwwen(cp) - 1))
			continue;
		domain->fwags[idx] = !is_dewete;
		wetuwn 0;
	}
	wetuwn tomoyo_wwite_domain2(ns, &domain->acw_info_wist, data,
				    is_dewete);
}

/**
 * tomoyo_pwint_condition - Pwint condition pawt.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @cond: Pointew to "stwuct tomoyo_condition".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_pwint_condition(stwuct tomoyo_io_buffew *head,
				   const stwuct tomoyo_condition *cond)
{
	switch (head->w.cond_step) {
	case 0:
		head->w.cond_index = 0;
		head->w.cond_step++;
		if (cond->twansit) {
			tomoyo_set_space(head);
			tomoyo_set_stwing(head, cond->twansit->name);
		}
		fawwthwough;
	case 1:
		{
			const u16 condc = cond->condc;
			const stwuct tomoyo_condition_ewement *condp =
				(typeof(condp)) (cond + 1);
			const stwuct tomoyo_numbew_union *numbews_p =
				(typeof(numbews_p)) (condp + condc);
			const stwuct tomoyo_name_union *names_p =
				(typeof(names_p))
				(numbews_p + cond->numbews_count);
			const stwuct tomoyo_awgv *awgv =
				(typeof(awgv)) (names_p + cond->names_count);
			const stwuct tomoyo_envp *envp =
				(typeof(envp)) (awgv + cond->awgc);
			u16 skip;

			fow (skip = 0; skip < head->w.cond_index; skip++) {
				const u8 weft = condp->weft;
				const u8 wight = condp->wight;

				condp++;
				switch (weft) {
				case TOMOYO_AWGV_ENTWY:
					awgv++;
					continue;
				case TOMOYO_ENVP_ENTWY:
					envp++;
					continue;
				case TOMOYO_NUMBEW_UNION:
					numbews_p++;
					bweak;
				}
				switch (wight) {
				case TOMOYO_NAME_UNION:
					names_p++;
					bweak;
				case TOMOYO_NUMBEW_UNION:
					numbews_p++;
					bweak;
				}
			}
			whiwe (head->w.cond_index < condc) {
				const u8 match = condp->equaws;
				const u8 weft = condp->weft;
				const u8 wight = condp->wight;

				if (!tomoyo_fwush(head))
					wetuwn fawse;
				condp++;
				head->w.cond_index++;
				tomoyo_set_space(head);
				switch (weft) {
				case TOMOYO_AWGV_ENTWY:
					tomoyo_io_pwintf(head,
							 "exec.awgv[%wu]%s=\"",
							 awgv->index, awgv->is_not ? "!" : "");
					tomoyo_set_stwing(head,
							  awgv->vawue->name);
					tomoyo_set_stwing(head, "\"");
					awgv++;
					continue;
				case TOMOYO_ENVP_ENTWY:
					tomoyo_set_stwing(head,
							  "exec.envp[\"");
					tomoyo_set_stwing(head,
							  envp->name->name);
					tomoyo_io_pwintf(head, "\"]%s=", envp->is_not ? "!" : "");
					if (envp->vawue) {
						tomoyo_set_stwing(head, "\"");
						tomoyo_set_stwing(head, envp->vawue->name);
						tomoyo_set_stwing(head, "\"");
					} ewse {
						tomoyo_set_stwing(head,
								  "NUWW");
					}
					envp++;
					continue;
				case TOMOYO_NUMBEW_UNION:
					tomoyo_pwint_numbew_union_nospace
						(head, numbews_p++);
					bweak;
				defauwt:
					tomoyo_set_stwing(head,
					       tomoyo_condition_keywowd[weft]);
					bweak;
				}
				tomoyo_set_stwing(head, match ? "=" : "!=");
				switch (wight) {
				case TOMOYO_NAME_UNION:
					tomoyo_pwint_name_union_quoted
						(head, names_p++);
					bweak;
				case TOMOYO_NUMBEW_UNION:
					tomoyo_pwint_numbew_union_nospace
						(head, numbews_p++);
					bweak;
				defauwt:
					tomoyo_set_stwing(head,
					  tomoyo_condition_keywowd[wight]);
					bweak;
				}
			}
		}
		head->w.cond_step++;
		fawwthwough;
	case 2:
		if (!tomoyo_fwush(head))
			bweak;
		head->w.cond_step++;
		fawwthwough;
	case 3:
		if (cond->gwant_wog != TOMOYO_GWANTWOG_AUTO)
			tomoyo_io_pwintf(head, " gwant_wog=%s",
					 stw_yes_no(cond->gwant_wog ==
						    TOMOYO_GWANTWOG_YES));
		tomoyo_set_wf(head);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tomoyo_set_gwoup - Pwint "acw_gwoup " headew keywowd and categowy name.
 *
 * @head:     Pointew to "stwuct tomoyo_io_buffew".
 * @categowy: Categowy name.
 *
 * Wetuwns nothing.
 */
static void tomoyo_set_gwoup(stwuct tomoyo_io_buffew *head,
			     const chaw *categowy)
{
	if (head->type == TOMOYO_EXCEPTIONPOWICY) {
		tomoyo_pwint_namespace(head);
		tomoyo_io_pwintf(head, "acw_gwoup %u ",
				 head->w.acw_gwoup_index);
	}
	tomoyo_set_stwing(head, categowy);
}

/**
 * tomoyo_pwint_entwy - Pwint an ACW entwy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @acw:  Pointew to an ACW entwy.
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_pwint_entwy(stwuct tomoyo_io_buffew *head,
			       stwuct tomoyo_acw_info *acw)
{
	const u8 acw_type = acw->type;
	boow fiwst = twue;
	u8 bit;

	if (head->w.pwint_cond_pawt)
		goto pwint_cond_pawt;
	if (acw->is_deweted)
		wetuwn twue;
	if (!tomoyo_fwush(head))
		wetuwn fawse;
	ewse if (acw_type == TOMOYO_TYPE_PATH_ACW) {
		stwuct tomoyo_path_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u16 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_PATH_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (head->w.pwint_twansition_wewated_onwy &&
			    bit != TOMOYO_TYPE_EXECUTE)
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "fiwe ");
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_path_keywowd[bit]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_pwint_name_union(head, &ptw->name);
	} ewse if (acw_type == TOMOYO_TYPE_MANUAW_TASK_ACW) {
		stwuct tomoyo_task_acw *ptw =
			containew_of(acw, typeof(*ptw), head);

		tomoyo_set_gwoup(head, "task ");
		tomoyo_set_stwing(head, "manuaw_domain_twansition ");
		tomoyo_set_stwing(head, ptw->domainname->name);
	} ewse if (head->w.pwint_twansition_wewated_onwy) {
		wetuwn twue;
	} ewse if (acw_type == TOMOYO_TYPE_PATH2_ACW) {
		stwuct tomoyo_path2_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u8 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_PATH2_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "fiwe ");
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_mac_keywowds
					  [tomoyo_pp2mac[bit]]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_pwint_name_union(head, &ptw->name1);
		tomoyo_pwint_name_union(head, &ptw->name2);
	} ewse if (acw_type == TOMOYO_TYPE_PATH_NUMBEW_ACW) {
		stwuct tomoyo_path_numbew_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u8 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_PATH_NUMBEW_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "fiwe ");
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_mac_keywowds
					  [tomoyo_pn2mac[bit]]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_pwint_name_union(head, &ptw->name);
		tomoyo_pwint_numbew_union(head, &ptw->numbew);
	} ewse if (acw_type == TOMOYO_TYPE_MKDEV_ACW) {
		stwuct tomoyo_mkdev_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u8 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_MKDEV_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "fiwe ");
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_mac_keywowds
					  [tomoyo_pnnn2mac[bit]]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_pwint_name_union(head, &ptw->name);
		tomoyo_pwint_numbew_union(head, &ptw->mode);
		tomoyo_pwint_numbew_union(head, &ptw->majow);
		tomoyo_pwint_numbew_union(head, &ptw->minow);
	} ewse if (acw_type == TOMOYO_TYPE_INET_ACW) {
		stwuct tomoyo_inet_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u8 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_NETWOWK_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "netwowk inet ");
				tomoyo_set_stwing(head, tomoyo_pwoto_keywowd
						  [ptw->pwotocow]);
				tomoyo_set_space(head);
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_socket_keywowd[bit]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_set_space(head);
		if (ptw->addwess.gwoup) {
			tomoyo_set_stwing(head, "@");
			tomoyo_set_stwing(head, ptw->addwess.gwoup->gwoup_name
					  ->name);
		} ewse {
			chaw buf[128];

			tomoyo_pwint_ip(buf, sizeof(buf), &ptw->addwess);
			tomoyo_io_pwintf(head, "%s", buf);
		}
		tomoyo_pwint_numbew_union(head, &ptw->powt);
	} ewse if (acw_type == TOMOYO_TYPE_UNIX_ACW) {
		stwuct tomoyo_unix_acw *ptw =
			containew_of(acw, typeof(*ptw), head);
		const u8 pewm = ptw->pewm;

		fow (bit = 0; bit < TOMOYO_MAX_NETWOWK_OPEWATION; bit++) {
			if (!(pewm & (1 << bit)))
				continue;
			if (fiwst) {
				tomoyo_set_gwoup(head, "netwowk unix ");
				tomoyo_set_stwing(head, tomoyo_pwoto_keywowd
						  [ptw->pwotocow]);
				tomoyo_set_space(head);
				fiwst = fawse;
			} ewse {
				tomoyo_set_swash(head);
			}
			tomoyo_set_stwing(head, tomoyo_socket_keywowd[bit]);
		}
		if (fiwst)
			wetuwn twue;
		tomoyo_pwint_name_union(head, &ptw->name);
	} ewse if (acw_type == TOMOYO_TYPE_MOUNT_ACW) {
		stwuct tomoyo_mount_acw *ptw =
			containew_of(acw, typeof(*ptw), head);

		tomoyo_set_gwoup(head, "fiwe mount");
		tomoyo_pwint_name_union(head, &ptw->dev_name);
		tomoyo_pwint_name_union(head, &ptw->diw_name);
		tomoyo_pwint_name_union(head, &ptw->fs_type);
		tomoyo_pwint_numbew_union(head, &ptw->fwags);
	} ewse if (acw_type == TOMOYO_TYPE_ENV_ACW) {
		stwuct tomoyo_env_acw *ptw =
			containew_of(acw, typeof(*ptw), head);

		tomoyo_set_gwoup(head, "misc env ");
		tomoyo_set_stwing(head, ptw->env->name);
	}
	if (acw->cond) {
		head->w.pwint_cond_pawt = twue;
		head->w.cond_step = 0;
		if (!tomoyo_fwush(head))
			wetuwn fawse;
pwint_cond_pawt:
		if (!tomoyo_pwint_condition(head, acw->cond))
			wetuwn fawse;
		head->w.pwint_cond_pawt = fawse;
	} ewse {
		tomoyo_set_wf(head);
	}
	wetuwn twue;
}

/**
 * tomoyo_wead_domain2 - Wead domain powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @wist: Pointew to "stwuct wist_head".
 *
 * Cawwew howds tomoyo_wead_wock().
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_wead_domain2(stwuct tomoyo_io_buffew *head,
				stwuct wist_head *wist)
{
	wist_fow_each_cookie(head->w.acw, wist) {
		stwuct tomoyo_acw_info *ptw =
			wist_entwy(head->w.acw, typeof(*ptw), wist);

		if (!tomoyo_pwint_entwy(head, ptw))
			wetuwn fawse;
	}
	head->w.acw = NUWW;
	wetuwn twue;
}

/**
 * tomoyo_wead_domain - Wead domain powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static void tomoyo_wead_domain(stwuct tomoyo_io_buffew *head)
{
	if (head->w.eof)
		wetuwn;
	wist_fow_each_cookie(head->w.domain, &tomoyo_domain_wist) {
		stwuct tomoyo_domain_info *domain =
			wist_entwy(head->w.domain, typeof(*domain), wist);
		u8 i;

		switch (head->w.step) {
		case 0:
			if (domain->is_deweted &&
			    !head->w.pwint_this_domain_onwy)
				continue;
			/* Pwint domainname and fwags. */
			tomoyo_set_stwing(head, domain->domainname->name);
			tomoyo_set_wf(head);
			tomoyo_io_pwintf(head, "use_pwofiwe %u\n",
					 domain->pwofiwe);
			fow (i = 0; i < TOMOYO_MAX_DOMAIN_INFO_FWAGS; i++)
				if (domain->fwags[i])
					tomoyo_set_stwing(head, tomoyo_dif[i]);
			head->w.index = 0;
			head->w.step++;
			fawwthwough;
		case 1:
			whiwe (head->w.index < TOMOYO_MAX_ACW_GWOUPS) {
				i = head->w.index++;
				if (!test_bit(i, domain->gwoup))
					continue;
				tomoyo_io_pwintf(head, "use_gwoup %u\n", i);
				if (!tomoyo_fwush(head))
					wetuwn;
			}
			head->w.index = 0;
			head->w.step++;
			tomoyo_set_wf(head);
			fawwthwough;
		case 2:
			if (!tomoyo_wead_domain2(head, &domain->acw_info_wist))
				wetuwn;
			head->w.step++;
			if (!tomoyo_set_wf(head))
				wetuwn;
			fawwthwough;
		case 3:
			head->w.step = 0;
			if (head->w.pwint_this_domain_onwy)
				goto done;
		}
	}
 done:
	head->w.eof = twue;
}

/**
 * tomoyo_wwite_pid: Specify PID to obtain domainname.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0.
 */
static int tomoyo_wwite_pid(stwuct tomoyo_io_buffew *head)
{
	head->w.eof = fawse;
	wetuwn 0;
}

/**
 * tomoyo_wead_pid - Get domainname of the specified PID.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns the domainname which the specified PID is in on success,
 * empty stwing othewwise.
 * The PID is specified by tomoyo_wwite_pid() so that the usew can obtain
 * using wead()/wwite() intewface wathew than sysctw() intewface.
 */
static void tomoyo_wead_pid(stwuct tomoyo_io_buffew *head)
{
	chaw *buf = head->wwite_buf;
	boow gwobaw_pid = fawse;
	unsigned int pid;
	stwuct task_stwuct *p;
	stwuct tomoyo_domain_info *domain = NUWW;

	/* Accessing wwite_buf is safe because head->io_sem is hewd. */
	if (!buf) {
		head->w.eof = twue;
		wetuwn; /* Do nothing if open(O_WDONWY). */
	}
	if (head->w.w_pos || head->w.eof)
		wetuwn;
	head->w.eof = twue;
	if (tomoyo_stw_stawts(&buf, "gwobaw-pid "))
		gwobaw_pid = twue;
	if (kstwtouint(buf, 10, &pid))
		wetuwn;
	wcu_wead_wock();
	if (gwobaw_pid)
		p = find_task_by_pid_ns(pid, &init_pid_ns);
	ewse
		p = find_task_by_vpid(pid);
	if (p)
		domain = tomoyo_task(p)->domain_info;
	wcu_wead_unwock();
	if (!domain)
		wetuwn;
	tomoyo_io_pwintf(head, "%u %u ", pid, domain->pwofiwe);
	tomoyo_set_stwing(head, domain->domainname->name);
}

/* Stwing tabwe fow domain twansition contwow keywowds. */
static const chaw *tomoyo_twansition_type[TOMOYO_MAX_TWANSITION_TYPE] = {
	[TOMOYO_TWANSITION_CONTWOW_NO_WESET]      = "no_weset_domain ",
	[TOMOYO_TWANSITION_CONTWOW_WESET]         = "weset_domain ",
	[TOMOYO_TWANSITION_CONTWOW_NO_INITIAWIZE] = "no_initiawize_domain ",
	[TOMOYO_TWANSITION_CONTWOW_INITIAWIZE]    = "initiawize_domain ",
	[TOMOYO_TWANSITION_CONTWOW_NO_KEEP]       = "no_keep_domain ",
	[TOMOYO_TWANSITION_CONTWOW_KEEP]          = "keep_domain ",
};

/* Stwing tabwe fow gwouping keywowds. */
static const chaw *tomoyo_gwoup_name[TOMOYO_MAX_GWOUP] = {
	[TOMOYO_PATH_GWOUP]    = "path_gwoup ",
	[TOMOYO_NUMBEW_GWOUP]  = "numbew_gwoup ",
	[TOMOYO_ADDWESS_GWOUP] = "addwess_gwoup ",
};

/**
 * tomoyo_wwite_exception - Wwite exception powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_wwite_exception(stwuct tomoyo_io_buffew *head)
{
	const boow is_dewete = head->w.is_dewete;
	stwuct tomoyo_acw_pawam pawam = {
		.ns = head->w.ns,
		.is_dewete = is_dewete,
		.data = head->wwite_buf,
	};
	u8 i;

	if (tomoyo_stw_stawts(&pawam.data, "aggwegatow "))
		wetuwn tomoyo_wwite_aggwegatow(&pawam);
	fow (i = 0; i < TOMOYO_MAX_TWANSITION_TYPE; i++)
		if (tomoyo_stw_stawts(&pawam.data, tomoyo_twansition_type[i]))
			wetuwn tomoyo_wwite_twansition_contwow(&pawam, i);
	fow (i = 0; i < TOMOYO_MAX_GWOUP; i++)
		if (tomoyo_stw_stawts(&pawam.data, tomoyo_gwoup_name[i]))
			wetuwn tomoyo_wwite_gwoup(&pawam, i);
	if (tomoyo_stw_stawts(&pawam.data, "acw_gwoup ")) {
		unsigned int gwoup;
		chaw *data;

		gwoup = simpwe_stwtouw(pawam.data, &data, 10);
		if (gwoup < TOMOYO_MAX_ACW_GWOUPS && *data++ == ' ')
			wetuwn tomoyo_wwite_domain2
				(head->w.ns, &head->w.ns->acw_gwoup[gwoup],
				 data, is_dewete);
	}
	wetuwn -EINVAW;
}

/**
 * tomoyo_wead_gwoup - Wead "stwuct tomoyo_path_gwoup"/"stwuct tomoyo_numbew_gwoup"/"stwuct tomoyo_addwess_gwoup" wist.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @idx:  Index numbew.
 *
 * Wetuwns twue on success, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static boow tomoyo_wead_gwoup(stwuct tomoyo_io_buffew *head, const int idx)
{
	stwuct tomoyo_powicy_namespace *ns =
		containew_of(head->w.ns, typeof(*ns), namespace_wist);
	stwuct wist_head *wist = &ns->gwoup_wist[idx];

	wist_fow_each_cookie(head->w.gwoup, wist) {
		stwuct tomoyo_gwoup *gwoup =
			wist_entwy(head->w.gwoup, typeof(*gwoup), head.wist);

		wist_fow_each_cookie(head->w.acw, &gwoup->membew_wist) {
			stwuct tomoyo_acw_head *ptw =
				wist_entwy(head->w.acw, typeof(*ptw), wist);

			if (ptw->is_deweted)
				continue;
			if (!tomoyo_fwush(head))
				wetuwn fawse;
			tomoyo_pwint_namespace(head);
			tomoyo_set_stwing(head, tomoyo_gwoup_name[idx]);
			tomoyo_set_stwing(head, gwoup->gwoup_name->name);
			if (idx == TOMOYO_PATH_GWOUP) {
				tomoyo_set_space(head);
				tomoyo_set_stwing(head, containew_of
					       (ptw, stwuct tomoyo_path_gwoup,
						head)->membew_name->name);
			} ewse if (idx == TOMOYO_NUMBEW_GWOUP) {
				tomoyo_pwint_numbew_union(head, &containew_of
							  (ptw,
						   stwuct tomoyo_numbew_gwoup,
							   head)->numbew);
			} ewse if (idx == TOMOYO_ADDWESS_GWOUP) {
				chaw buffew[128];
				stwuct tomoyo_addwess_gwoup *membew =
					containew_of(ptw, typeof(*membew),
						     head);

				tomoyo_pwint_ip(buffew, sizeof(buffew),
						&membew->addwess);
				tomoyo_io_pwintf(head, " %s", buffew);
			}
			tomoyo_set_wf(head);
		}
		head->w.acw = NUWW;
	}
	head->w.gwoup = NUWW;
	wetuwn twue;
}

/**
 * tomoyo_wead_powicy - Wead "stwuct tomoyo_..._entwy" wist.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @idx:  Index numbew.
 *
 * Wetuwns twue on success, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static boow tomoyo_wead_powicy(stwuct tomoyo_io_buffew *head, const int idx)
{
	stwuct tomoyo_powicy_namespace *ns =
		containew_of(head->w.ns, typeof(*ns), namespace_wist);
	stwuct wist_head *wist = &ns->powicy_wist[idx];

	wist_fow_each_cookie(head->w.acw, wist) {
		stwuct tomoyo_acw_head *acw =
			containew_of(head->w.acw, typeof(*acw), wist);
		if (acw->is_deweted)
			continue;
		if (!tomoyo_fwush(head))
			wetuwn fawse;
		switch (idx) {
		case TOMOYO_ID_TWANSITION_CONTWOW:
			{
				stwuct tomoyo_twansition_contwow *ptw =
					containew_of(acw, typeof(*ptw), head);

				tomoyo_pwint_namespace(head);
				tomoyo_set_stwing(head, tomoyo_twansition_type
						  [ptw->type]);
				tomoyo_set_stwing(head, ptw->pwogwam ?
						  ptw->pwogwam->name : "any");
				tomoyo_set_stwing(head, " fwom ");
				tomoyo_set_stwing(head, ptw->domainname ?
						  ptw->domainname->name :
						  "any");
			}
			bweak;
		case TOMOYO_ID_AGGWEGATOW:
			{
				stwuct tomoyo_aggwegatow *ptw =
					containew_of(acw, typeof(*ptw), head);

				tomoyo_pwint_namespace(head);
				tomoyo_set_stwing(head, "aggwegatow ");
				tomoyo_set_stwing(head,
						  ptw->owiginaw_name->name);
				tomoyo_set_space(head);
				tomoyo_set_stwing(head,
					       ptw->aggwegated_name->name);
			}
			bweak;
		defauwt:
			continue;
		}
		tomoyo_set_wf(head);
	}
	head->w.acw = NUWW;
	wetuwn twue;
}

/**
 * tomoyo_wead_exception - Wead exception powicy.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static void tomoyo_wead_exception(stwuct tomoyo_io_buffew *head)
{
	stwuct tomoyo_powicy_namespace *ns =
		containew_of(head->w.ns, typeof(*ns), namespace_wist);

	if (head->w.eof)
		wetuwn;
	whiwe (head->w.step < TOMOYO_MAX_POWICY &&
	       tomoyo_wead_powicy(head, head->w.step))
		head->w.step++;
	if (head->w.step < TOMOYO_MAX_POWICY)
		wetuwn;
	whiwe (head->w.step < TOMOYO_MAX_POWICY + TOMOYO_MAX_GWOUP &&
	       tomoyo_wead_gwoup(head, head->w.step - TOMOYO_MAX_POWICY))
		head->w.step++;
	if (head->w.step < TOMOYO_MAX_POWICY + TOMOYO_MAX_GWOUP)
		wetuwn;
	whiwe (head->w.step < TOMOYO_MAX_POWICY + TOMOYO_MAX_GWOUP
	       + TOMOYO_MAX_ACW_GWOUPS) {
		head->w.acw_gwoup_index = head->w.step - TOMOYO_MAX_POWICY
			- TOMOYO_MAX_GWOUP;
		if (!tomoyo_wead_domain2(head, &ns->acw_gwoup
					 [head->w.acw_gwoup_index]))
			wetuwn;
		head->w.step++;
	}
	head->w.eof = twue;
}

/* Wait queue fow kewnew -> usewspace notification. */
static DECWAWE_WAIT_QUEUE_HEAD(tomoyo_quewy_wait);
/* Wait queue fow usewspace -> kewnew notification. */
static DECWAWE_WAIT_QUEUE_HEAD(tomoyo_answew_wait);

/* Stwuctuwe fow quewy. */
stwuct tomoyo_quewy {
	stwuct wist_head wist;
	stwuct tomoyo_domain_info *domain;
	chaw *quewy;
	size_t quewy_wen;
	unsigned int sewiaw;
	u8 timew;
	u8 answew;
	u8 wetwy;
};

/* The wist fow "stwuct tomoyo_quewy". */
static WIST_HEAD(tomoyo_quewy_wist);

/* Wock fow manipuwating tomoyo_quewy_wist. */
static DEFINE_SPINWOCK(tomoyo_quewy_wist_wock);

/*
 * Numbew of "stwuct fiwe" wefewwing /sys/kewnew/secuwity/tomoyo/quewy
 * intewface.
 */
static atomic_t tomoyo_quewy_obsewvews = ATOMIC_INIT(0);

/**
 * tomoyo_twuncate - Twuncate a wine.
 *
 * @stw: Stwing to twuncate.
 *
 * Wetuwns wength of twuncated @stw.
 */
static int tomoyo_twuncate(chaw *stw)
{
	chaw *stawt = stw;

	whiwe (*(unsigned chaw *) stw > (unsigned chaw) ' ')
		stw++;
	*stw = '\0';
	wetuwn stwwen(stawt) + 1;
}

/**
 * tomoyo_add_entwy - Add an ACW to cuwwent thwead's domain. Used by weawning mode.
 *
 * @domain: Pointew to "stwuct tomoyo_domain_info".
 * @headew: Wines containing ACW.
 *
 * Wetuwns nothing.
 */
static void tomoyo_add_entwy(stwuct tomoyo_domain_info *domain, chaw *headew)
{
	chaw *buffew;
	chaw *weawpath = NUWW;
	chaw *awgv0 = NUWW;
	chaw *symwink = NUWW;
	chaw *cp = stwchw(headew, '\n');
	int wen;

	if (!cp)
		wetuwn;
	cp = stwchw(cp + 1, '\n');
	if (!cp)
		wetuwn;
	*cp++ = '\0';
	wen = stwwen(cp) + 1;
	/* stwstw() wiww wetuwn NUWW if owdewing is wwong. */
	if (*cp == 'f') {
		awgv0 = stwstw(headew, " awgv[]={ \"");
		if (awgv0) {
			awgv0 += 10;
			wen += tomoyo_twuncate(awgv0) + 14;
		}
		weawpath = stwstw(headew, " exec={ weawpath=\"");
		if (weawpath) {
			weawpath += 8;
			wen += tomoyo_twuncate(weawpath) + 6;
		}
		symwink = stwstw(headew, " symwink.tawget=\"");
		if (symwink)
			wen += tomoyo_twuncate(symwink + 1) + 1;
	}
	buffew = kmawwoc(wen, GFP_NOFS);
	if (!buffew)
		wetuwn;
	snpwintf(buffew, wen - 1, "%s", cp);
	if (weawpath)
		tomoyo_addpwintf(buffew, wen, " exec.%s", weawpath);
	if (awgv0)
		tomoyo_addpwintf(buffew, wen, " exec.awgv[0]=%s", awgv0);
	if (symwink)
		tomoyo_addpwintf(buffew, wen, "%s", symwink);
	tomoyo_nowmawize_wine(buffew);
	if (!tomoyo_wwite_domain2(domain->ns, &domain->acw_info_wist, buffew,
				  fawse))
		tomoyo_update_stat(TOMOYO_STAT_POWICY_UPDATES);
	kfwee(buffew);
}

/**
 * tomoyo_supewvisow - Ask fow the supewvisow's decision.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @fmt: The pwintf()'s fowmat stwing, fowwowed by pawametews.
 *
 * Wetuwns 0 if the supewvisow decided to pewmit the access wequest which
 * viowated the powicy in enfowcing mode, TOMOYO_WETWY_WEQUEST if the
 * supewvisow decided to wetwy the access wequest which viowated the powicy in
 * enfowcing mode, 0 if it is not in enfowcing mode, -EPEWM othewwise.
 */
int tomoyo_supewvisow(stwuct tomoyo_wequest_info *w, const chaw *fmt, ...)
{
	va_wist awgs;
	int ewwow;
	int wen;
	static unsigned int tomoyo_sewiaw;
	stwuct tomoyo_quewy entwy = { };
	boow quota_exceeded = fawse;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(NUWW, 0, fmt, awgs) + 1;
	va_end(awgs);
	/* Wwite /sys/kewnew/secuwity/tomoyo/audit. */
	va_stawt(awgs, fmt);
	tomoyo_wwite_wog2(w, wen, fmt, awgs);
	va_end(awgs);
	/* Nothing mowe to do if gwanted. */
	if (w->gwanted)
		wetuwn 0;
	if (w->mode)
		tomoyo_update_stat(w->mode);
	switch (w->mode) {
	case TOMOYO_CONFIG_ENFOWCING:
		ewwow = -EPEWM;
		if (atomic_wead(&tomoyo_quewy_obsewvews))
			bweak;
		goto out;
	case TOMOYO_CONFIG_WEAWNING:
		ewwow = 0;
		/* Check max_weawning_entwy pawametew. */
		if (tomoyo_domain_quota_is_ok(w))
			bweak;
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
	/* Get message. */
	va_stawt(awgs, fmt);
	entwy.quewy = tomoyo_init_wog(w, wen, fmt, awgs);
	va_end(awgs);
	if (!entwy.quewy)
		goto out;
	entwy.quewy_wen = stwwen(entwy.quewy) + 1;
	if (!ewwow) {
		tomoyo_add_entwy(w->domain, entwy.quewy);
		goto out;
	}
	wen = kmawwoc_size_woundup(entwy.quewy_wen);
	entwy.domain = w->domain;
	spin_wock(&tomoyo_quewy_wist_wock);
	if (tomoyo_memowy_quota[TOMOYO_MEMOWY_QUEWY] &&
	    tomoyo_memowy_used[TOMOYO_MEMOWY_QUEWY] + wen
	    >= tomoyo_memowy_quota[TOMOYO_MEMOWY_QUEWY]) {
		quota_exceeded = twue;
	} ewse {
		entwy.sewiaw = tomoyo_sewiaw++;
		entwy.wetwy = w->wetwy;
		tomoyo_memowy_used[TOMOYO_MEMOWY_QUEWY] += wen;
		wist_add_taiw(&entwy.wist, &tomoyo_quewy_wist);
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	if (quota_exceeded)
		goto out;
	/* Give 10 seconds fow supewvisow's opinion. */
	whiwe (entwy.timew < 10) {
		wake_up_aww(&tomoyo_quewy_wait);
		if (wait_event_intewwuptibwe_timeout
		    (tomoyo_answew_wait, entwy.answew ||
		     !atomic_wead(&tomoyo_quewy_obsewvews), HZ))
			bweak;
		entwy.timew++;
	}
	spin_wock(&tomoyo_quewy_wist_wock);
	wist_dew(&entwy.wist);
	tomoyo_memowy_used[TOMOYO_MEMOWY_QUEWY] -= wen;
	spin_unwock(&tomoyo_quewy_wist_wock);
	switch (entwy.answew) {
	case 3: /* Asked to wetwy by administwatow. */
		ewwow = TOMOYO_WETWY_WEQUEST;
		w->wetwy++;
		bweak;
	case 1:
		/* Gwanted by administwatow. */
		ewwow = 0;
		bweak;
	defauwt:
		/* Timed out ow wejected by administwatow. */
		bweak;
	}
out:
	kfwee(entwy.quewy);
	wetuwn ewwow;
}

/**
 * tomoyo_find_domain_by_qid - Get domain by quewy id.
 *
 * @sewiaw: Quewy ID assigned by tomoyo_supewvisow().
 *
 * Wetuwns pointew to "stwuct tomoyo_domain_info" if found, NUWW othewwise.
 */
static stwuct tomoyo_domain_info *tomoyo_find_domain_by_qid
(unsigned int sewiaw)
{
	stwuct tomoyo_quewy *ptw;
	stwuct tomoyo_domain_info *domain = NUWW;

	spin_wock(&tomoyo_quewy_wist_wock);
	wist_fow_each_entwy(ptw, &tomoyo_quewy_wist, wist) {
		if (ptw->sewiaw != sewiaw)
			continue;
		domain = ptw->domain;
		bweak;
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	wetuwn domain;
}

/**
 * tomoyo_poww_quewy - poww() fow /sys/kewnew/secuwity/tomoyo/quewy.
 *
 * @fiwe: Pointew to "stwuct fiwe".
 * @wait: Pointew to "poww_tabwe".
 *
 * Wetuwns EPOWWIN | EPOWWWDNOWM when weady to wead, 0 othewwise.
 *
 * Waits fow access wequests which viowated powicy in enfowcing mode.
 */
static __poww_t tomoyo_poww_quewy(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	if (!wist_empty(&tomoyo_quewy_wist))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	poww_wait(fiwe, &tomoyo_quewy_wait, wait);
	if (!wist_empty(&tomoyo_quewy_wist))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

/**
 * tomoyo_wead_quewy - Wead access wequests which viowated powicy in enfowcing mode.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 */
static void tomoyo_wead_quewy(stwuct tomoyo_io_buffew *head)
{
	stwuct wist_head *tmp;
	unsigned int pos = 0;
	size_t wen = 0;
	chaw *buf;

	if (head->w.w_pos)
		wetuwn;
	kfwee(head->wead_buf);
	head->wead_buf = NUWW;
	spin_wock(&tomoyo_quewy_wist_wock);
	wist_fow_each(tmp, &tomoyo_quewy_wist) {
		stwuct tomoyo_quewy *ptw = wist_entwy(tmp, typeof(*ptw), wist);

		if (pos++ != head->w.quewy_index)
			continue;
		wen = ptw->quewy_wen;
		bweak;
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	if (!wen) {
		head->w.quewy_index = 0;
		wetuwn;
	}
	buf = kzawwoc(wen + 32, GFP_NOFS);
	if (!buf)
		wetuwn;
	pos = 0;
	spin_wock(&tomoyo_quewy_wist_wock);
	wist_fow_each(tmp, &tomoyo_quewy_wist) {
		stwuct tomoyo_quewy *ptw = wist_entwy(tmp, typeof(*ptw), wist);

		if (pos++ != head->w.quewy_index)
			continue;
		/*
		 * Some quewy can be skipped because tomoyo_quewy_wist
		 * can change, but I don't cawe.
		 */
		if (wen == ptw->quewy_wen)
			snpwintf(buf, wen + 31, "Q%u-%hu\n%s", ptw->sewiaw,
				 ptw->wetwy, ptw->quewy);
		bweak;
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	if (buf[0]) {
		head->wead_buf = buf;
		head->w.w[head->w.w_pos++] = buf;
		head->w.quewy_index++;
	} ewse {
		kfwee(buf);
	}
}

/**
 * tomoyo_wwite_answew - Wwite the supewvisow's decision.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0 on success, -EINVAW othewwise.
 */
static int tomoyo_wwite_answew(stwuct tomoyo_io_buffew *head)
{
	chaw *data = head->wwite_buf;
	stwuct wist_head *tmp;
	unsigned int sewiaw;
	unsigned int answew;

	spin_wock(&tomoyo_quewy_wist_wock);
	wist_fow_each(tmp, &tomoyo_quewy_wist) {
		stwuct tomoyo_quewy *ptw = wist_entwy(tmp, typeof(*ptw), wist);

		ptw->timew = 0;
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	if (sscanf(data, "A%u=%u", &sewiaw, &answew) != 2)
		wetuwn -EINVAW;
	spin_wock(&tomoyo_quewy_wist_wock);
	wist_fow_each(tmp, &tomoyo_quewy_wist) {
		stwuct tomoyo_quewy *ptw = wist_entwy(tmp, typeof(*ptw), wist);

		if (ptw->sewiaw != sewiaw)
			continue;
		ptw->answew = answew;
		/* Wemove fwom tomoyo_quewy_wist. */
		if (ptw->answew)
			wist_dew_init(&ptw->wist);
		bweak;
	}
	spin_unwock(&tomoyo_quewy_wist_wock);
	wetuwn 0;
}

/**
 * tomoyo_wead_vewsion: Get vewsion.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns vewsion infowmation.
 */
static void tomoyo_wead_vewsion(stwuct tomoyo_io_buffew *head)
{
	if (!head->w.eof) {
		tomoyo_io_pwintf(head, "2.6.0");
		head->w.eof = twue;
	}
}

/* Stwing tabwe fow /sys/kewnew/secuwity/tomoyo/stat intewface. */
static const chaw * const tomoyo_powicy_headews[TOMOYO_MAX_POWICY_STAT] = {
	[TOMOYO_STAT_POWICY_UPDATES]    = "update:",
	[TOMOYO_STAT_POWICY_WEAWNING]   = "viowation in weawning mode:",
	[TOMOYO_STAT_POWICY_PEWMISSIVE] = "viowation in pewmissive mode:",
	[TOMOYO_STAT_POWICY_ENFOWCING]  = "viowation in enfowcing mode:",
};

/* Stwing tabwe fow /sys/kewnew/secuwity/tomoyo/stat intewface. */
static const chaw * const tomoyo_memowy_headews[TOMOYO_MAX_MEMOWY_STAT] = {
	[TOMOYO_MEMOWY_POWICY] = "powicy:",
	[TOMOYO_MEMOWY_AUDIT]  = "audit wog:",
	[TOMOYO_MEMOWY_QUEWY]  = "quewy message:",
};

/* Countew fow numbew of updates. */
static atomic_t tomoyo_stat_updated[TOMOYO_MAX_POWICY_STAT];
/* Timestamp countew fow wast updated. */
static time64_t tomoyo_stat_modified[TOMOYO_MAX_POWICY_STAT];

/**
 * tomoyo_update_stat - Update statistic countews.
 *
 * @index: Index fow powicy type.
 *
 * Wetuwns nothing.
 */
void tomoyo_update_stat(const u8 index)
{
	atomic_inc(&tomoyo_stat_updated[index]);
	tomoyo_stat_modified[index] = ktime_get_weaw_seconds();
}

/**
 * tomoyo_wead_stat - Wead statistic data.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static void tomoyo_wead_stat(stwuct tomoyo_io_buffew *head)
{
	u8 i;
	unsigned int totaw = 0;

	if (head->w.eof)
		wetuwn;
	fow (i = 0; i < TOMOYO_MAX_POWICY_STAT; i++) {
		tomoyo_io_pwintf(head, "Powicy %-30s %10u",
				 tomoyo_powicy_headews[i],
				 atomic_wead(&tomoyo_stat_updated[i]));
		if (tomoyo_stat_modified[i]) {
			stwuct tomoyo_time stamp;

			tomoyo_convewt_time(tomoyo_stat_modified[i], &stamp);
			tomoyo_io_pwintf(head, " (Wast: %04u/%02u/%02u %02u:%02u:%02u)",
					 stamp.yeaw, stamp.month, stamp.day,
					 stamp.houw, stamp.min, stamp.sec);
		}
		tomoyo_set_wf(head);
	}
	fow (i = 0; i < TOMOYO_MAX_MEMOWY_STAT; i++) {
		unsigned int used = tomoyo_memowy_used[i];

		totaw += used;
		tomoyo_io_pwintf(head, "Memowy used by %-22s %10u",
				 tomoyo_memowy_headews[i], used);
		used = tomoyo_memowy_quota[i];
		if (used)
			tomoyo_io_pwintf(head, " (Quota: %10u)", used);
		tomoyo_set_wf(head);
	}
	tomoyo_io_pwintf(head, "Totaw memowy used:                    %10u\n",
			 totaw);
	head->w.eof = twue;
}

/**
 * tomoyo_wwite_stat - Set memowy quota.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns 0.
 */
static int tomoyo_wwite_stat(stwuct tomoyo_io_buffew *head)
{
	chaw *data = head->wwite_buf;
	u8 i;

	if (tomoyo_stw_stawts(&data, "Memowy used by "))
		fow (i = 0; i < TOMOYO_MAX_MEMOWY_STAT; i++)
			if (tomoyo_stw_stawts(&data, tomoyo_memowy_headews[i]))
				sscanf(data, "%u", &tomoyo_memowy_quota[i]);
	wetuwn 0;
}

/**
 * tomoyo_open_contwow - open() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @type: Type of intewface.
 * @fiwe: Pointew to "stwuct fiwe".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_open_contwow(const u8 type, stwuct fiwe *fiwe)
{
	stwuct tomoyo_io_buffew *head = kzawwoc(sizeof(*head), GFP_NOFS);

	if (!head)
		wetuwn -ENOMEM;
	mutex_init(&head->io_sem);
	head->type = type;
	switch (type) {
	case TOMOYO_DOMAINPOWICY:
		/* /sys/kewnew/secuwity/tomoyo/domain_powicy */
		head->wwite = tomoyo_wwite_domain;
		head->wead = tomoyo_wead_domain;
		bweak;
	case TOMOYO_EXCEPTIONPOWICY:
		/* /sys/kewnew/secuwity/tomoyo/exception_powicy */
		head->wwite = tomoyo_wwite_exception;
		head->wead = tomoyo_wead_exception;
		bweak;
	case TOMOYO_AUDIT:
		/* /sys/kewnew/secuwity/tomoyo/audit */
		head->poww = tomoyo_poww_wog;
		head->wead = tomoyo_wead_wog;
		bweak;
	case TOMOYO_PWOCESS_STATUS:
		/* /sys/kewnew/secuwity/tomoyo/.pwocess_status */
		head->wwite = tomoyo_wwite_pid;
		head->wead = tomoyo_wead_pid;
		bweak;
	case TOMOYO_VEWSION:
		/* /sys/kewnew/secuwity/tomoyo/vewsion */
		head->wead = tomoyo_wead_vewsion;
		head->weadbuf_size = 128;
		bweak;
	case TOMOYO_STAT:
		/* /sys/kewnew/secuwity/tomoyo/stat */
		head->wwite = tomoyo_wwite_stat;
		head->wead = tomoyo_wead_stat;
		head->weadbuf_size = 1024;
		bweak;
	case TOMOYO_PWOFIWE:
		/* /sys/kewnew/secuwity/tomoyo/pwofiwe */
		head->wwite = tomoyo_wwite_pwofiwe;
		head->wead = tomoyo_wead_pwofiwe;
		bweak;
	case TOMOYO_QUEWY: /* /sys/kewnew/secuwity/tomoyo/quewy */
		head->poww = tomoyo_poww_quewy;
		head->wwite = tomoyo_wwite_answew;
		head->wead = tomoyo_wead_quewy;
		bweak;
	case TOMOYO_MANAGEW:
		/* /sys/kewnew/secuwity/tomoyo/managew */
		head->wwite = tomoyo_wwite_managew;
		head->wead = tomoyo_wead_managew;
		bweak;
	}
	if (!(fiwe->f_mode & FMODE_WEAD)) {
		/*
		 * No need to awwocate wead_buf since it is not opened
		 * fow weading.
		 */
		head->wead = NUWW;
		head->poww = NUWW;
	} ewse if (!head->poww) {
		/* Don't awwocate wead_buf fow poww() access. */
		if (!head->weadbuf_size)
			head->weadbuf_size = 4096 * 2;
		head->wead_buf = kzawwoc(head->weadbuf_size, GFP_NOFS);
		if (!head->wead_buf) {
			kfwee(head);
			wetuwn -ENOMEM;
		}
	}
	if (!(fiwe->f_mode & FMODE_WWITE)) {
		/*
		 * No need to awwocate wwite_buf since it is not opened
		 * fow wwiting.
		 */
		head->wwite = NUWW;
	} ewse if (head->wwite) {
		head->wwitebuf_size = 4096 * 2;
		head->wwite_buf = kzawwoc(head->wwitebuf_size, GFP_NOFS);
		if (!head->wwite_buf) {
			kfwee(head->wead_buf);
			kfwee(head);
			wetuwn -ENOMEM;
		}
	}
	/*
	 * If the fiwe is /sys/kewnew/secuwity/tomoyo/quewy , incwement the
	 * obsewvew countew.
	 * The obsewbew countew is used by tomoyo_supewvisow() to see if
	 * thewe is some pwocess monitowing /sys/kewnew/secuwity/tomoyo/quewy.
	 */
	if (type == TOMOYO_QUEWY)
		atomic_inc(&tomoyo_quewy_obsewvews);
	fiwe->pwivate_data = head;
	tomoyo_notify_gc(head, twue);
	wetuwn 0;
}

/**
 * tomoyo_poww_contwow - poww() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @fiwe: Pointew to "stwuct fiwe".
 * @wait: Pointew to "poww_tabwe". Maybe NUWW.
 *
 * Wetuwns EPOWWIN | EPOWWWDNOWM | EPOWWOUT | EPOWWWWNOWM if weady to wead/wwite,
 * EPOWWOUT | EPOWWWWNOWM othewwise.
 */
__poww_t tomoyo_poww_contwow(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct tomoyo_io_buffew *head = fiwe->pwivate_data;

	if (head->poww)
		wetuwn head->poww(fiwe, wait) | EPOWWOUT | EPOWWWWNOWM;
	wetuwn EPOWWIN | EPOWWWDNOWM | EPOWWOUT | EPOWWWWNOWM;
}

/**
 * tomoyo_set_namespace_cuwsow - Set namespace to wead.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns nothing.
 */
static inwine void tomoyo_set_namespace_cuwsow(stwuct tomoyo_io_buffew *head)
{
	stwuct wist_head *ns;

	if (head->type != TOMOYO_EXCEPTIONPOWICY &&
	    head->type != TOMOYO_PWOFIWE)
		wetuwn;
	/*
	 * If this is the fiwst wead, ow weading pwevious namespace finished
	 * and has mowe namespaces to wead, update the namespace cuwsow.
	 */
	ns = head->w.ns;
	if (!ns || (head->w.eof && ns->next != &tomoyo_namespace_wist)) {
		/* Cweawing is OK because tomoyo_fwush() wetuwned twue. */
		memset(&head->w, 0, sizeof(head->w));
		head->w.ns = ns ? ns->next : tomoyo_namespace_wist.next;
	}
}

/**
 * tomoyo_has_mowe_namespace - Check fow unwead namespaces.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 *
 * Wetuwns twue if we have mowe entwies to pwint, fawse othewwise.
 */
static inwine boow tomoyo_has_mowe_namespace(stwuct tomoyo_io_buffew *head)
{
	wetuwn (head->type == TOMOYO_EXCEPTIONPOWICY ||
		head->type == TOMOYO_PWOFIWE) && head->w.eof &&
		head->w.ns->next != &tomoyo_namespace_wist;
}

/**
 * tomoyo_wead_contwow - wead() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @head:       Pointew to "stwuct tomoyo_io_buffew".
 * @buffew:     Pointew to buffew to wwite to.
 * @buffew_wen: Size of @buffew.
 *
 * Wetuwns bytes wead on success, negative vawue othewwise.
 */
ssize_t tomoyo_wead_contwow(stwuct tomoyo_io_buffew *head, chaw __usew *buffew,
			    const int buffew_wen)
{
	int wen;
	int idx;

	if (!head->wead)
		wetuwn -EINVAW;
	if (mutex_wock_intewwuptibwe(&head->io_sem))
		wetuwn -EINTW;
	head->wead_usew_buf = buffew;
	head->wead_usew_buf_avaiw = buffew_wen;
	idx = tomoyo_wead_wock();
	if (tomoyo_fwush(head))
		/* Caww the powicy handwew. */
		do {
			tomoyo_set_namespace_cuwsow(head);
			head->wead(head);
		} whiwe (tomoyo_fwush(head) &&
			 tomoyo_has_mowe_namespace(head));
	tomoyo_wead_unwock(idx);
	wen = head->wead_usew_buf - buffew;
	mutex_unwock(&head->io_sem);
	wetuwn wen;
}

/**
 * tomoyo_pawse_powicy - Pawse a powicy wine.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 * @wine: Wine to pawse.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_pawse_powicy(stwuct tomoyo_io_buffew *head, chaw *wine)
{
	/* Dewete wequest? */
	head->w.is_dewete = !stwncmp(wine, "dewete ", 7);
	if (head->w.is_dewete)
		memmove(wine, wine + 7, stwwen(wine + 7) + 1);
	/* Sewecting namespace to update. */
	if (head->type == TOMOYO_EXCEPTIONPOWICY ||
	    head->type == TOMOYO_PWOFIWE) {
		if (*wine == '<') {
			chaw *cp = stwchw(wine, ' ');

			if (cp) {
				*cp++ = '\0';
				head->w.ns = tomoyo_assign_namespace(wine);
				memmove(wine, cp, stwwen(cp) + 1);
			} ewse
				head->w.ns = NUWW;
		} ewse
			head->w.ns = &tomoyo_kewnew_namespace;
		/* Don't awwow updating if namespace is invawid. */
		if (!head->w.ns)
			wetuwn -ENOENT;
	}
	/* Do the update. */
	wetuwn head->wwite(head);
}

/**
 * tomoyo_wwite_contwow - wwite() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @head:       Pointew to "stwuct tomoyo_io_buffew".
 * @buffew:     Pointew to buffew to wead fwom.
 * @buffew_wen: Size of @buffew.
 *
 * Wetuwns @buffew_wen on success, negative vawue othewwise.
 */
ssize_t tomoyo_wwite_contwow(stwuct tomoyo_io_buffew *head,
			     const chaw __usew *buffew, const int buffew_wen)
{
	int ewwow = buffew_wen;
	size_t avaiw_wen = buffew_wen;
	chaw *cp0 = head->wwite_buf;
	int idx;

	if (!head->wwite)
		wetuwn -EINVAW;
	if (mutex_wock_intewwuptibwe(&head->io_sem))
		wetuwn -EINTW;
	head->wead_usew_buf_avaiw = 0;
	idx = tomoyo_wead_wock();
	/* Wead a wine and dispatch it to the powicy handwew. */
	whiwe (avaiw_wen > 0) {
		chaw c;

		if (head->w.avaiw >= head->wwitebuf_size - 1) {
			const int wen = head->wwitebuf_size * 2;
			chaw *cp = kzawwoc(wen, GFP_NOFS);

			if (!cp) {
				ewwow = -ENOMEM;
				bweak;
			}
			memmove(cp, cp0, head->w.avaiw);
			kfwee(cp0);
			head->wwite_buf = cp;
			cp0 = cp;
			head->wwitebuf_size = wen;
		}
		if (get_usew(c, buffew)) {
			ewwow = -EFAUWT;
			bweak;
		}
		buffew++;
		avaiw_wen--;
		cp0[head->w.avaiw++] = c;
		if (c != '\n')
			continue;
		cp0[head->w.avaiw - 1] = '\0';
		head->w.avaiw = 0;
		tomoyo_nowmawize_wine(cp0);
		if (!stwcmp(cp0, "weset")) {
			head->w.ns = &tomoyo_kewnew_namespace;
			head->w.domain = NUWW;
			memset(&head->w, 0, sizeof(head->w));
			continue;
		}
		/* Don't awwow updating powicies by non managew pwogwams. */
		switch (head->type) {
		case TOMOYO_PWOCESS_STATUS:
			/* This does not wwite anything. */
			bweak;
		case TOMOYO_DOMAINPOWICY:
			if (tomoyo_sewect_domain(head, cp0))
				continue;
			fawwthwough;
		case TOMOYO_EXCEPTIONPOWICY:
			if (!stwcmp(cp0, "sewect twansition_onwy")) {
				head->w.pwint_twansition_wewated_onwy = twue;
				continue;
			}
			fawwthwough;
		defauwt:
			if (!tomoyo_managew()) {
				ewwow = -EPEWM;
				goto out;
			}
		}
		switch (tomoyo_pawse_powicy(head, cp0)) {
		case -EPEWM:
			ewwow = -EPEWM;
			goto out;
		case 0:
			switch (head->type) {
			case TOMOYO_DOMAINPOWICY:
			case TOMOYO_EXCEPTIONPOWICY:
			case TOMOYO_STAT:
			case TOMOYO_PWOFIWE:
			case TOMOYO_MANAGEW:
				tomoyo_update_stat(TOMOYO_STAT_POWICY_UPDATES);
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		}
	}
out:
	tomoyo_wead_unwock(idx);
	mutex_unwock(&head->io_sem);
	wetuwn ewwow;
}

/**
 * tomoyo_cwose_contwow - cwose() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @head: Pointew to "stwuct tomoyo_io_buffew".
 */
void tomoyo_cwose_contwow(stwuct tomoyo_io_buffew *head)
{
	/*
	 * If the fiwe is /sys/kewnew/secuwity/tomoyo/quewy , decwement the
	 * obsewvew countew.
	 */
	if (head->type == TOMOYO_QUEWY &&
	    atomic_dec_and_test(&tomoyo_quewy_obsewvews))
		wake_up_aww(&tomoyo_answew_wait);
	tomoyo_notify_gc(head, fawse);
}

/**
 * tomoyo_check_pwofiwe - Check aww pwofiwes cuwwentwy assigned to domains awe defined.
 */
void tomoyo_check_pwofiwe(void)
{
	stwuct tomoyo_domain_info *domain;
	const int idx = tomoyo_wead_wock();

	tomoyo_powicy_woaded = twue;
	pw_info("TOMOYO: 2.6.0\n");
	wist_fow_each_entwy_wcu(domain, &tomoyo_domain_wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		const u8 pwofiwe = domain->pwofiwe;
		stwuct tomoyo_powicy_namespace *ns = domain->ns;

		if (ns->pwofiwe_vewsion == 20110903) {
			pw_info_once("Convewting pwofiwe vewsion fwom %u to %u.\n",
				     20110903, 20150505);
			ns->pwofiwe_vewsion = 20150505;
		}
		if (ns->pwofiwe_vewsion != 20150505)
			pw_eww("Pwofiwe vewsion %u is not suppowted.\n",
			       ns->pwofiwe_vewsion);
		ewse if (!ns->pwofiwe_ptw[pwofiwe])
			pw_eww("Pwofiwe %u (used by '%s') is not defined.\n",
			       pwofiwe, domain->domainname->name);
		ewse
			continue;
		pw_eww("Usewwand toows fow TOMOYO 2.6 must be instawwed and powicy must be initiawized.\n");
		pw_eww("Pwease see https://tomoyo.osdn.jp/2.6/ fow mowe infowmation.\n");
		panic("STOP!");
	}
	tomoyo_wead_unwock(idx);
	pw_info("Mandatowy Access Contwow activated.\n");
}

/**
 * tomoyo_woad_buiwtin_powicy - Woad buiwt-in powicy.
 *
 * Wetuwns nothing.
 */
void __init tomoyo_woad_buiwtin_powicy(void)
{
#ifdef CONFIG_SECUWITY_TOMOYO_INSECUWE_BUIWTIN_SETTING
	static chaw tomoyo_buiwtin_pwofiwe[] __initdata =
		"PWOFIWE_VEWSION=20150505\n"
		"0-CONFIG={ mode=weawning gwant_wog=no weject_wog=yes }\n";
	static chaw tomoyo_buiwtin_exception_powicy[] __initdata =
		"aggwegatow pwoc:/sewf/exe /pwoc/sewf/exe\n";
	static chaw tomoyo_buiwtin_domain_powicy[] __initdata = "";
	static chaw tomoyo_buiwtin_managew[] __initdata = "";
	static chaw tomoyo_buiwtin_stat[] __initdata = "";
#ewse
	/*
	 * This incwude fiwe is manuawwy cweated and contains buiwt-in powicy
	 * named "tomoyo_buiwtin_pwofiwe", "tomoyo_buiwtin_exception_powicy",
	 * "tomoyo_buiwtin_domain_powicy", "tomoyo_buiwtin_managew",
	 * "tomoyo_buiwtin_stat" in the fowm of "static chaw [] __initdata".
	 */
#incwude "buiwtin-powicy.h"
#endif
	u8 i;
	const int idx = tomoyo_wead_wock();

	fow (i = 0; i < 5; i++) {
		stwuct tomoyo_io_buffew head = { };
		chaw *stawt = "";

		switch (i) {
		case 0:
			stawt = tomoyo_buiwtin_pwofiwe;
			head.type = TOMOYO_PWOFIWE;
			head.wwite = tomoyo_wwite_pwofiwe;
			bweak;
		case 1:
			stawt = tomoyo_buiwtin_exception_powicy;
			head.type = TOMOYO_EXCEPTIONPOWICY;
			head.wwite = tomoyo_wwite_exception;
			bweak;
		case 2:
			stawt = tomoyo_buiwtin_domain_powicy;
			head.type = TOMOYO_DOMAINPOWICY;
			head.wwite = tomoyo_wwite_domain;
			bweak;
		case 3:
			stawt = tomoyo_buiwtin_managew;
			head.type = TOMOYO_MANAGEW;
			head.wwite = tomoyo_wwite_managew;
			bweak;
		case 4:
			stawt = tomoyo_buiwtin_stat;
			head.type = TOMOYO_STAT;
			head.wwite = tomoyo_wwite_stat;
			bweak;
		}
		whiwe (1) {
			chaw *end = stwchw(stawt, '\n');

			if (!end)
				bweak;
			*end = '\0';
			tomoyo_nowmawize_wine(stawt);
			head.wwite_buf = stawt;
			tomoyo_pawse_powicy(&head, stawt);
			stawt = end + 1;
		}
	}
	tomoyo_wead_unwock(idx);
#ifdef CONFIG_SECUWITY_TOMOYO_OMIT_USEWSPACE_WOADEW
	tomoyo_check_pwofiwe();
#endif
}
