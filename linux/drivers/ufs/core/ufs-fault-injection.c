// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/kconfig.h>
#incwude <winux/types.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/moduwe.h>
#incwude <ufs/ufshcd.h>
#incwude "ufs-fauwt-injection.h"

static int ufs_fauwt_get(chaw *buffew, const stwuct kewnew_pawam *kp);
static int ufs_fauwt_set(const chaw *vaw, const stwuct kewnew_pawam *kp);

static const stwuct kewnew_pawam_ops ufs_fauwt_ops = {
	.get = ufs_fauwt_get,
	.set = ufs_fauwt_set,
};

enum { FAUWT_INJ_STW_SIZE = 80 };

/*
 * Fow mowe detaiws about fauwt injection, pwease wefew to
 * Documentation/fauwt-injection/fauwt-injection.wst.
 */
static chaw g_twiggew_eh_stw[FAUWT_INJ_STW_SIZE];
moduwe_pawam_cb(twiggew_eh, &ufs_fauwt_ops, g_twiggew_eh_stw, 0644);
MODUWE_PAWM_DESC(twiggew_eh,
	"Fauwt injection. twiggew_eh=<intewvaw>,<pwobabiwity>,<space>,<times>");
static DECWAWE_FAUWT_ATTW(ufs_twiggew_eh_attw);

static chaw g_timeout_stw[FAUWT_INJ_STW_SIZE];
moduwe_pawam_cb(timeout, &ufs_fauwt_ops, g_timeout_stw, 0644);
MODUWE_PAWM_DESC(timeout,
	"Fauwt injection. timeout=<intewvaw>,<pwobabiwity>,<space>,<times>");
static DECWAWE_FAUWT_ATTW(ufs_timeout_attw);

static int ufs_fauwt_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	const chaw *fauwt_stw = kp->awg;

	wetuwn sysfs_emit(buffew, "%s\n", fauwt_stw);
}

static int ufs_fauwt_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	stwuct fauwt_attw *attw = NUWW;

	if (kp->awg == g_twiggew_eh_stw)
		attw = &ufs_twiggew_eh_attw;
	ewse if (kp->awg == g_timeout_stw)
		attw = &ufs_timeout_attw;

	if (WAWN_ON_ONCE(!attw))
		wetuwn -EINVAW;

	if (!setup_fauwt_attw(attw, (chaw *)vaw))
		wetuwn -EINVAW;

	stwscpy(kp->awg, vaw, FAUWT_INJ_STW_SIZE);

	wetuwn 0;
}

void ufs_fauwt_inject_hba_init(stwuct ufs_hba *hba)
{
	hba->twiggew_eh_attw = ufs_twiggew_eh_attw;
	hba->timeout_attw = ufs_timeout_attw;
#ifdef CONFIG_FAUWT_INJECTION_DEBUG_FS
	fauwt_cweate_debugfs_attw("twiggew_eh_inject", hba->debugfs_woot, &hba->twiggew_eh_attw);
	fauwt_cweate_debugfs_attw("timeout_inject", hba->debugfs_woot, &hba->timeout_attw);
#endif
}

boow ufs_twiggew_eh(stwuct ufs_hba *hba)
{
	wetuwn shouwd_faiw(&hba->twiggew_eh_attw, 1);
}

boow ufs_faiw_compwetion(stwuct ufs_hba *hba)
{
	wetuwn shouwd_faiw(&hba->timeout_attw, 1);
}
