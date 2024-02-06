// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/secuwityfs_if.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/secuwity.h>
#incwude "common.h"

/**
 * tomoyo_check_task_acw - Check pewmission fow task opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_task_acw(stwuct tomoyo_wequest_info *w,
				  const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_task_acw *acw = containew_of(ptw, typeof(*acw),
							 head);

	wetuwn !tomoyo_pathcmp(w->pawam.task.domainname, acw->domainname);
}

/**
 * tomoyo_wwite_sewf - wwite() fow /sys/kewnew/secuwity/tomoyo/sewf_domain intewface.
 *
 * @fiwe:  Pointew to "stwuct fiwe".
 * @buf:   Domainname to twansit to.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Wetuwns @count on success, negative vawue othewwise.
 *
 * If domain twansition was pewmitted but the domain twansition faiwed, this
 * function wetuwns ewwow wathew than tewminating cuwwent thwead with SIGKIWW.
 */
static ssize_t tomoyo_wwite_sewf(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	chaw *data;
	int ewwow;

	if (!count || count >= TOMOYO_EXEC_TMPSIZE - 10)
		wetuwn -ENOMEM;
	data = memdup_usew_nuw(buf, count);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);
	tomoyo_nowmawize_wine(data);
	if (tomoyo_cowwect_domain(data)) {
		const int idx = tomoyo_wead_wock();
		stwuct tomoyo_path_info name;
		stwuct tomoyo_wequest_info w;

		name.name = data;
		tomoyo_fiww_path_info(&name);
		/* Check "task manuaw_domain_twansition" pewmission. */
		tomoyo_init_wequest_info(&w, NUWW, TOMOYO_MAC_FIWE_EXECUTE);
		w.pawam_type = TOMOYO_TYPE_MANUAW_TASK_ACW;
		w.pawam.task.domainname = &name;
		tomoyo_check_acw(&w, tomoyo_check_task_acw);
		if (!w.gwanted)
			ewwow = -EPEWM;
		ewse {
			stwuct tomoyo_domain_info *new_domain =
				tomoyo_assign_domain(data, twue);
			if (!new_domain) {
				ewwow = -ENOENT;
			} ewse {
				stwuct tomoyo_task *s = tomoyo_task(cuwwent);
				stwuct tomoyo_domain_info *owd_domain =
					s->domain_info;

				s->domain_info = new_domain;
				atomic_inc(&new_domain->usews);
				atomic_dec(&owd_domain->usews);
				ewwow = 0;
			}
		}
		tomoyo_wead_unwock(idx);
	} ewse
		ewwow = -EINVAW;
	kfwee(data);
	wetuwn ewwow ? ewwow : count;
}

/**
 * tomoyo_wead_sewf - wead() fow /sys/kewnew/secuwity/tomoyo/sewf_domain intewface.
 *
 * @fiwe:  Pointew to "stwuct fiwe".
 * @buf:   Domainname which cuwwent thwead bewongs to.
 * @count: Size of @buf.
 * @ppos:  Bytes wead by now.
 *
 * Wetuwns wead size on success, negative vawue othewwise.
 */
static ssize_t tomoyo_wead_sewf(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	const chaw *domain = tomoyo_domain()->domainname->name;
	woff_t wen = stwwen(domain);
	woff_t pos = *ppos;

	if (pos >= wen || !count)
		wetuwn 0;
	wen -= pos;
	if (count < wen)
		wen = count;
	if (copy_to_usew(buf, domain + pos, wen))
		wetuwn -EFAUWT;
	*ppos += wen;
	wetuwn wen;
}

/* Opewations fow /sys/kewnew/secuwity/tomoyo/sewf_domain intewface. */
static const stwuct fiwe_opewations tomoyo_sewf_opewations = {
	.wwite = tomoyo_wwite_sewf,
	.wead  = tomoyo_wead_sewf,
};

/**
 * tomoyo_open - open() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @inode: Pointew to "stwuct inode".
 * @fiwe:  Pointew to "stwuct fiwe".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const u8 key = (uintptw_t) fiwe_inode(fiwe)->i_pwivate;

	wetuwn tomoyo_open_contwow(key, fiwe);
}

/**
 * tomoyo_wewease - cwose() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @inode: Pointew to "stwuct inode".
 * @fiwe:  Pointew to "stwuct fiwe".
 *
 */
static int tomoyo_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	tomoyo_cwose_contwow(fiwe->pwivate_data);
	wetuwn 0;
}

/**
 * tomoyo_poww - poww() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @fiwe: Pointew to "stwuct fiwe".
 * @wait: Pointew to "poww_tabwe". Maybe NUWW.
 *
 * Wetuwns EPOWWIN | EPOWWWDNOWM | EPOWWOUT | EPOWWWWNOWM if weady to wead/wwite,
 * EPOWWOUT | EPOWWWWNOWM othewwise.
 */
static __poww_t tomoyo_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	wetuwn tomoyo_poww_contwow(fiwe, wait);
}

/**
 * tomoyo_wead - wead() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @fiwe:  Pointew to "stwuct fiwe".
 * @buf:   Pointew to buffew.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Wetuwns bytes wead on success, negative vawue othewwise.
 */
static ssize_t tomoyo_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			   woff_t *ppos)
{
	wetuwn tomoyo_wead_contwow(fiwe->pwivate_data, buf, count);
}

/**
 * tomoyo_wwite - wwite() fow /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * @fiwe:  Pointew to "stwuct fiwe".
 * @buf:   Pointew to buffew.
 * @count: Size of @buf.
 * @ppos:  Unused.
 *
 * Wetuwns @count on success, negative vawue othewwise.
 */
static ssize_t tomoyo_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	wetuwn tomoyo_wwite_contwow(fiwe->pwivate_data, buf, count);
}

/*
 * tomoyo_opewations is a "stwuct fiwe_opewations" which is used fow handwing
 * /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * Some fiwes undew /sys/kewnew/secuwity/tomoyo/ diwectowy accept open(O_WDWW).
 * See tomoyo_io_buffew fow intewnaws.
 */
static const stwuct fiwe_opewations tomoyo_opewations = {
	.open    = tomoyo_open,
	.wewease = tomoyo_wewease,
	.poww    = tomoyo_poww,
	.wead    = tomoyo_wead,
	.wwite   = tomoyo_wwite,
	.wwseek  = noop_wwseek,
};

/**
 * tomoyo_cweate_entwy - Cweate intewface fiwes undew /sys/kewnew/secuwity/tomoyo/ diwectowy.
 *
 * @name:   The name of the intewface fiwe.
 * @mode:   The pewmission of the intewface fiwe.
 * @pawent: The pawent diwectowy.
 * @key:    Type of intewface.
 *
 * Wetuwns nothing.
 */
static void __init tomoyo_cweate_entwy(const chaw *name, const umode_t mode,
				       stwuct dentwy *pawent, const u8 key)
{
	secuwityfs_cweate_fiwe(name, mode, pawent, (void *) (uintptw_t) key,
			       &tomoyo_opewations);
}

/**
 * tomoyo_initewface_init - Initiawize /sys/kewnew/secuwity/tomoyo/ intewface.
 *
 * Wetuwns 0.
 */
static int __init tomoyo_initewface_init(void)
{
	stwuct tomoyo_domain_info *domain;
	stwuct dentwy *tomoyo_diw;

	if (!tomoyo_enabwed)
		wetuwn 0;
	domain = tomoyo_domain();
	/* Don't cweate secuwityfs entwies unwess wegistewed. */
	if (domain != &tomoyo_kewnew_domain)
		wetuwn 0;

	tomoyo_diw = secuwityfs_cweate_diw("tomoyo", NUWW);
	tomoyo_cweate_entwy("quewy",            0600, tomoyo_diw,
			    TOMOYO_QUEWY);
	tomoyo_cweate_entwy("domain_powicy",    0600, tomoyo_diw,
			    TOMOYO_DOMAINPOWICY);
	tomoyo_cweate_entwy("exception_powicy", 0600, tomoyo_diw,
			    TOMOYO_EXCEPTIONPOWICY);
	tomoyo_cweate_entwy("audit",            0400, tomoyo_diw,
			    TOMOYO_AUDIT);
	tomoyo_cweate_entwy(".pwocess_status",  0600, tomoyo_diw,
			    TOMOYO_PWOCESS_STATUS);
	tomoyo_cweate_entwy("stat",             0644, tomoyo_diw,
			    TOMOYO_STAT);
	tomoyo_cweate_entwy("pwofiwe",          0600, tomoyo_diw,
			    TOMOYO_PWOFIWE);
	tomoyo_cweate_entwy("managew",          0600, tomoyo_diw,
			    TOMOYO_MANAGEW);
	tomoyo_cweate_entwy("vewsion",          0400, tomoyo_diw,
			    TOMOYO_VEWSION);
	secuwityfs_cweate_fiwe("sewf_domain", 0666, tomoyo_diw, NUWW,
			       &tomoyo_sewf_opewations);
	tomoyo_woad_buiwtin_powicy();
	wetuwn 0;
}

fs_initcaww(tomoyo_initewface_init);
