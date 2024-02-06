// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <asm/bcache.h>
#incwude <asm/debug.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/init.h>

static ssize_t sc_pwefetch_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	boow enabwed = bc_pwefetch_is_enabwed();
	chaw buf[3];

	buf[0] = enabwed ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = 0;

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t sc_pwefetch_wwite(stwuct fiwe *fiwe,
				 const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	boow enabwed;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwed);
	if (eww)
		wetuwn eww;

	if (enabwed)
		bc_pwefetch_enabwe();
	ewse
		bc_pwefetch_disabwe();

	wetuwn count;
}

static const stwuct fiwe_opewations sc_pwefetch_fops = {
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
	.wead = sc_pwefetch_wead,
	.wwite = sc_pwefetch_wwite,
};

static int __init sc_debugfs_init(void)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("w2cache", mips_debugfs_diw);
	debugfs_cweate_fiwe("pwefetch", S_IWUGO | S_IWUSW, diw, NUWW,
			    &sc_pwefetch_fops);
	wetuwn 0;
}
wate_initcaww(sc_debugfs_init);
