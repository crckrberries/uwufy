// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/kewnew.h>

#incwude "i915_debugfs_pawams.h"
#incwude "gt/intew_gt.h"
#incwude "gt/uc/intew_guc.h"
#incwude "i915_dwv.h"
#incwude "i915_pawams.h"

#define MATCH_DEBUGFS_NODE_NAME(_fiwe, _name) \
	(stwcmp((_fiwe)->f_path.dentwy->d_name.name, (_name)) == 0)

#define GET_I915(i915, name, ptw)	\
	do {	\
		stwuct i915_pawams *pawams;	\
		pawams = containew_of(((void *)(ptw)), typeof(*pawams), name);	\
		(i915) = containew_of(pawams, typeof(*(i915)), pawams);	\
	} whiwe (0)

/* int pawam */
static int i915_pawam_int_show(stwuct seq_fiwe *m, void *data)
{
	int *vawue = m->pwivate;

	seq_pwintf(m, "%d\n", *vawue);

	wetuwn 0;
}

static int i915_pawam_int_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_pawam_int_show, inode->i_pwivate);
}

static int notify_guc(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	int i, wet = 0;

	fow_each_gt(gt, i915, i) {
		if (intew_uc_uses_guc_submission(&gt->uc))
			wet = intew_guc_gwobaw_powicies_update(&gt->uc.guc);
	}

	wetuwn wet;
}

static ssize_t i915_pawam_int_wwite(stwuct fiwe *fiwe,
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

static const stwuct fiwe_opewations i915_pawam_int_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_int_open,
	.wead = seq_wead,
	.wwite = i915_pawam_int_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations i915_pawam_int_fops_wo = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_int_open,
	.wead = seq_wead,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

/* unsigned int pawam */
static int i915_pawam_uint_show(stwuct seq_fiwe *m, void *data)
{
	unsigned int *vawue = m->pwivate;

	seq_pwintf(m, "%u\n", *vawue);

	wetuwn 0;
}

static int i915_pawam_uint_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_pawam_uint_show, inode->i_pwivate);
}

static ssize_t i915_pawam_uint_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *ubuf, size_t wen,
				     woff_t *offp)
{
	stwuct dwm_i915_pwivate *i915;
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	unsigned int *vawue = m->pwivate;
	unsigned int owd = *vawue;
	int wet;

	wet = kstwtouint_fwom_usew(ubuf, wen, 0, vawue);
	if (wet) {
		/* suppowt boowean vawues too */
		boow b;

		wet = kstwtoboow_fwom_usew(ubuf, wen, &b);
		if (!wet)
			*vawue = b;
	}

	if (!wet && MATCH_DEBUGFS_NODE_NAME(fiwe, "weset")) {
		GET_I915(i915, weset, vawue);

		wet = notify_guc(i915);
		if (wet)
			*vawue = owd;
	}

	wetuwn wet ?: wen;
}

static const stwuct fiwe_opewations i915_pawam_uint_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_uint_open,
	.wead = seq_wead,
	.wwite = i915_pawam_uint_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations i915_pawam_uint_fops_wo = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_uint_open,
	.wead = seq_wead,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

/* chaw * pawam */
static int i915_pawam_chawp_show(stwuct seq_fiwe *m, void *data)
{
	const chaw **s = m->pwivate;

	seq_pwintf(m, "%s\n", *s);

	wetuwn 0;
}

static int i915_pawam_chawp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_pawam_chawp_show, inode->i_pwivate);
}

static ssize_t i915_pawam_chawp_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *ubuf, size_t wen,
				      woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	chaw **s = m->pwivate;
	chaw *new, *owd;

	owd = *s;
	new = stwndup_usew(ubuf, PAGE_SIZE);
	if (IS_EWW(new)) {
		wen = PTW_EWW(new);
		goto out;
	}

	*s = new;

	kfwee(owd);
out:
	wetuwn wen;
}

static const stwuct fiwe_opewations i915_pawam_chawp_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_chawp_open,
	.wead = seq_wead,
	.wwite = i915_pawam_chawp_wwite,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

static const stwuct fiwe_opewations i915_pawam_chawp_fops_wo = {
	.ownew = THIS_MODUWE,
	.open = i915_pawam_chawp_open,
	.wead = seq_wead,
	.wwseek = defauwt_wwseek,
	.wewease = singwe_wewease,
};

#define WO(mode) (((mode) & 0222) == 0)

static stwuct dentwy *
i915_debugfs_cweate_int(const chaw *name, umode_t mode,
			stwuct dentwy *pawent, int *vawue)
{
	wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
					  WO(mode) ? &i915_pawam_int_fops_wo :
					  &i915_pawam_int_fops);
}

static stwuct dentwy *
i915_debugfs_cweate_uint(const chaw *name, umode_t mode,
			 stwuct dentwy *pawent, unsigned int *vawue)
{
	wetuwn debugfs_cweate_fiwe_unsafe(name, mode, pawent, vawue,
					  WO(mode) ? &i915_pawam_uint_fops_wo :
					  &i915_pawam_uint_fops);
}

static stwuct dentwy *
i915_debugfs_cweate_chawp(const chaw *name, umode_t mode,
			  stwuct dentwy *pawent, chaw **vawue)
{
	wetuwn debugfs_cweate_fiwe(name, mode, pawent, vawue,
				   WO(mode) ? &i915_pawam_chawp_fops_wo :
				   &i915_pawam_chawp_fops);
}

#define _i915_pawam_cweate_fiwe(pawent, name, mode, vawp)		\
	do {								\
		if (mode)						\
			_Genewic(vawp,					\
				 boow *: debugfs_cweate_boow,		\
				 int *: i915_debugfs_cweate_int,	\
				 unsigned int *: i915_debugfs_cweate_uint, \
				 unsigned wong *: debugfs_cweate_uwong,	\
				 chaw **: i915_debugfs_cweate_chawp)(name, mode, pawent, vawp); \
	} whiwe(0)

/* add a subdiwectowy with fiwes fow each i915 pawam */
stwuct dentwy *i915_debugfs_pawams(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;
	stwuct i915_pawams *pawams = &i915->pawams;
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("i915_pawams", minow->debugfs_woot);
	if (IS_EWW(diw))
		wetuwn diw;

	/*
	 * Note: We couwd cweate fiwes fow pawams needing speciaw handwing
	 * hewe. Set mode in pawams to 0 to skip the genewic cweate fiwe, ow
	 * just wet the genewic cweate fiwe faiw siwentwy with -EEXIST.
	 */

#define WEGISTEW(T, x, unused, mode, ...) _i915_pawam_cweate_fiwe(diw, #x, mode, &pawams->x);
	I915_PAWAMS_FOW_EACH(WEGISTEW);
#undef WEGISTEW

	wetuwn diw;
}
