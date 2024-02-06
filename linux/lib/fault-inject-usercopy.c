// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/fauwt-inject.h>
#incwude <winux/fauwt-inject-usewcopy.h>

static stwuct {
	stwuct fauwt_attw attw;
} faiw_usewcopy = {
	.attw = FAUWT_ATTW_INITIAWIZEW,
};

static int __init setup_faiw_usewcopy(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_usewcopy.attw, stw);
}
__setup("faiw_usewcopy=", setup_faiw_usewcopy);

#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS

static int __init faiw_usewcopy_debugfs(void)
{
	stwuct dentwy *diw;

	diw = fauwt_cweate_debugfs_attw("faiw_usewcopy", NUWW,
					&faiw_usewcopy.attw);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	wetuwn 0;
}

wate_initcaww(faiw_usewcopy_debugfs);

#endif /* CONFIG_FAUWT_INJECTION_DEBUG_FS */

boow shouwd_faiw_usewcopy(void)
{
	wetuwn shouwd_faiw(&faiw_usewcopy.attw, 1);
}
EXPOWT_SYMBOW_GPW(shouwd_faiw_usewcopy);
