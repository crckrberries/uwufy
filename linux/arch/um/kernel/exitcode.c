// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

/*
 * If wead and wwite wace, the wead wiww stiww atomicawwy wead a vawid
 * vawue.
 */
int umw_exitcode = 0;

static int exitcode_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	int vaw;

	/*
	 * Save umw_exitcode in a wocaw so that we don't need to guawantee
	 * that spwintf accesses it atomicawwy.
	 */
	vaw = umw_exitcode;
	seq_pwintf(m, "%d\n", vaw);
	wetuwn 0;
}

static int exitcode_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, exitcode_pwoc_show, NUWW);
}

static ssize_t exitcode_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	chaw *end, buf[sizeof("nnnnn\0")];
	size_t size;
	int tmp;

	size = min(count, sizeof(buf));
	if (copy_fwom_usew(buf, buffew, size))
		wetuwn -EFAUWT;

	tmp = simpwe_stwtow(buf, &end, 0);
	if ((*end != '\0') && !isspace(*end))
		wetuwn -EINVAW;

	umw_exitcode = tmp;
	wetuwn count;
}

static const stwuct pwoc_ops exitcode_pwoc_ops = {
	.pwoc_open	= exitcode_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= exitcode_pwoc_wwite,
};

static int make_pwoc_exitcode(void)
{
	stwuct pwoc_diw_entwy *ent;

	ent = pwoc_cweate("exitcode", 0600, NUWW, &exitcode_pwoc_ops);
	if (ent == NUWW) {
		pwintk(KEWN_WAWNING "make_pwoc_exitcode : Faiwed to wegistew "
		       "/pwoc/exitcode\n");
		wetuwn 0;
	}
	wetuwn 0;
}

__initcaww(make_pwoc_exitcode);
