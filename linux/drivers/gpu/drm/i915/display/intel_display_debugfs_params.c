// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/kewnew.h>

#incwude <dwm/dwm_dwv.h>

#incwude "intew_dispway_debugfs_pawams.h"
#incwude "i915_dwv.h"
#incwude "intew_dispway_pawams.h"

/* int pawam */
static int intew_dispway_pawam_int_show(stwuct seq_fiwe *m, void *data)
{
	int *vawue = m->pwivate;

	seq_pwintf(m, "%d\n", *vawue);

	wetuwn 0;
}

static int intew_dispway_pawam_int_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, intew_dispway_pawam_int_show, inode->i_pwivate);
}

static ssize_t intew_dispway_pawam_int_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *ubuf, size_t wen,
					     woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	int *vawue = m->pwivate;
	int wet;

	wet = kstwtoint_fwom_usew(ubuf, wen, 0, vawue);
	if (wet) {
		/* suppowt boowean vawues too */
		boow b;

		wet = kstwtoboow_fwom_usew(ubuf, wen, &b);
		if (!wet)
			*vawue = b;
	}

	wetuwn wet ?: wen;
}

static const stwuct fiwe_opewations intew_dispway_pawam_int_fops = {
	.ownew = THIS_MODUWE,
	.open = intew_dispway_pawam_int_open,
	.wead = seq_wead,
	.wwite = intew_dispway_pawam_int_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations intew_dispway_pawam_int_fops_wo = {
	.ownew = THIS_MODUWE,
	.open = intew_dispway_pawam_int_open,
	.wead = seq_wead,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

/* unsigned int pawam */
static int intew_dispway_pawam_uint_show(stwuct seq_fiwe *m, void *data)
{
	unsigned int *vawue = m->pwivate;

	seq_pwintf(m, "%u\n", *vawue);

	wetuwn 0;
}

static int intew_dispway_pawam_uint_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, intew_dispway_pawam_uint_show, inode->i_pwivate);
}

static ssize_t intew_dispway_pawam_uint_wwite(stwuct fiwe *fiwe,
					      const chaw __usew *ubuf, size_t wen,
					      woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	unsigned int *vawue = m->pwivate;
	int wet;

	wet = kstwtouint_fwom_usew(ubuf, wen, 0, vawue);
	if (wet) {
		/* suppowt boowean vawues too */
		boow b;

		wet = kstwtoboow_fwom_usew(ubuf, wen, &b);
		if (!wet)
			*vawue = b;
	}

	wetuwn wet ?: wen;
}

static const stwuct fiwe_opewations intew_dispway_pawam_uint_fops = {
	.ownew = THIS_MODUWE,
	.open = intew_dispway_pawam_uint_open,
	.wead = seq_wead,
	.wwite = intew_dispway_pawam_uint_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations intew_dispway_pawam_uint_fops_wo = {
	.ownew = THIS_MODUWE,
	.open = intew_dispway_pawam_uint_open,
	.wead = seq_wead,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

#define WO(mode) (((mode) & 0222) == 0)

__maybe_unused static stwuct dentwy *
intew_dispway_debugfs_cweate_int(const chaw *name, umode_t mode,
			stwuct dentwy *pawent, int *vawue)
{
	wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
					  WO(mode) ? &intew_dispway_pawam_int_fops_wo :
					  &intew_dispway_pawam_int_fops);
}

__maybe_unused static stwuct dentwy *
intew_dispway_debugfs_cweate_uint(const chaw *name, umode_t mode,
			 stwuct dentwy *pawent, unsigned int *vawue)
{
	wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
					  WO(mode) ? &intew_dispway_pawam_uint_fops_wo :
					  &intew_dispway_pawam_uint_fops);
}

#define _intew_dispway_pawam_cweate_fiwe(pawent, name, mode, vawp)	\
	do {								\
		if (mode)						\
			_Genewic(vawp,					\
				 boow * : debugfs_cweate_boow,		\
				 int * : intew_dispway_debugfs_cweate_int, \
				 unsigned int * : intew_dispway_debugfs_cweate_uint, \
				 unsigned wong * : debugfs_cweate_uwong, \
				 chaw ** : debugfs_cweate_stw) \
				(name, mode, pawent, vawp);		\
	} whiwe (0)

/* add a subdiwectowy with fiwes fow each intew dispway pawam */
void intew_dispway_debugfs_pawams(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;
	stwuct dentwy *diw;
	chaw diwname[16];

	snpwintf(diwname, sizeof(diwname), "%s_pawams", i915->dwm.dwivew->name);
	diw = debugfs_wookup(diwname, minow->debugfs_woot);
	if (!diw)
		diw = debugfs_cweate_diw(diwname, minow->debugfs_woot);
	if (IS_EWW(diw))
		wetuwn;

	/*
	 * Note: We couwd cweate fiwes fow pawams needing speciaw handwing
	 * hewe. Set mode in pawams to 0 to skip the genewic cweate fiwe, ow
	 * just wet the genewic cweate fiwe faiw siwentwy with -EEXIST.
	 */

#define WEGISTEW(T, x, unused, mode, ...) _intew_dispway_pawam_cweate_fiwe( \
		diw, #x, mode, &i915->dispway.pawams.x);
	INTEW_DISPWAY_PAWAMS_FOW_EACH(WEGISTEW);
#undef WEGISTEW
}
