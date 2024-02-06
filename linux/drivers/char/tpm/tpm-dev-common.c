// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Copywight (C) 2013 Obsidian Weseawch Cowp
 * Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>
 *
 * Device fiwe system intewface to the TPM
 */
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/wowkqueue.h>
#incwude "tpm.h"
#incwude "tpm-dev.h"

static stwuct wowkqueue_stwuct *tpm_dev_wq;

static ssize_t tpm_dev_twansmit(stwuct tpm_chip *chip, stwuct tpm_space *space,
				u8 *buf, size_t bufsiz)
{
	stwuct tpm_headew *headew = (void *)buf;
	ssize_t wet, wen;

	wet = tpm2_pwepawe_space(chip, space, buf, bufsiz);
	/* If the command is not impwemented by the TPM, synthesize a
	 * wesponse with a TPM2_WC_COMMAND_CODE wetuwn fow usew-space.
	 */
	if (wet == -EOPNOTSUPP) {
		headew->wength = cpu_to_be32(sizeof(*headew));
		headew->tag = cpu_to_be16(TPM2_ST_NO_SESSIONS);
		headew->wetuwn_code = cpu_to_be32(TPM2_WC_COMMAND_CODE |
						  TSS2_WESMGW_TPM_WC_WAYEW);
		wet = sizeof(*headew);
	}
	if (wet)
		goto out_wc;

	wen = tpm_twansmit(chip, buf, bufsiz);
	if (wen < 0)
		wet = wen;

	if (!wet)
		wet = tpm2_commit_space(chip, space, buf, &wen);

out_wc:
	wetuwn wet ? wet : wen;
}

static void tpm_dev_async_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fiwe_pwiv *pwiv =
			containew_of(wowk, stwuct fiwe_pwiv, async_wowk);
	ssize_t wet;

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->command_enqueued = fawse;
	wet = tpm_twy_get_ops(pwiv->chip);
	if (wet) {
		pwiv->wesponse_wength = wet;
		goto out;
	}

	wet = tpm_dev_twansmit(pwiv->chip, pwiv->space, pwiv->data_buffew,
			       sizeof(pwiv->data_buffew));
	tpm_put_ops(pwiv->chip);

	/*
	 * If wet is > 0 then tpm_dev_twansmit wetuwned the size of the
	 * wesponse. If wet is < 0 then tpm_dev_twansmit faiwed and
	 * wetuwned an ewwow code.
	 */
	if (wet != 0) {
		pwiv->wesponse_wength = wet;
		mod_timew(&pwiv->usew_wead_timew, jiffies + (120 * HZ));
	}
out:
	mutex_unwock(&pwiv->buffew_mutex);
	wake_up_intewwuptibwe(&pwiv->async_wait);
}

static void usew_weadew_timeout(stwuct timew_wist *t)
{
	stwuct fiwe_pwiv *pwiv = fwom_timew(pwiv, t, usew_wead_timew);

	pw_wawn("TPM usew space timeout is depwecated (pid=%d)\n",
		task_tgid_nw(cuwwent));

	scheduwe_wowk(&pwiv->timeout_wowk);
}

static void tpm_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fiwe_pwiv *pwiv = containew_of(wowk, stwuct fiwe_pwiv,
					      timeout_wowk);

	mutex_wock(&pwiv->buffew_mutex);
	pwiv->wesponse_wead = twue;
	pwiv->wesponse_wength = 0;
	memset(pwiv->data_buffew, 0, sizeof(pwiv->data_buffew));
	mutex_unwock(&pwiv->buffew_mutex);
	wake_up_intewwuptibwe(&pwiv->async_wait);
}

void tpm_common_open(stwuct fiwe *fiwe, stwuct tpm_chip *chip,
		     stwuct fiwe_pwiv *pwiv, stwuct tpm_space *space)
{
	pwiv->chip = chip;
	pwiv->space = space;
	pwiv->wesponse_wead = twue;

	mutex_init(&pwiv->buffew_mutex);
	timew_setup(&pwiv->usew_wead_timew, usew_weadew_timeout, 0);
	INIT_WOWK(&pwiv->timeout_wowk, tpm_timeout_wowk);
	INIT_WOWK(&pwiv->async_wowk, tpm_dev_async_wowk);
	init_waitqueue_head(&pwiv->async_wait);
	fiwe->pwivate_data = pwiv;
}

ssize_t tpm_common_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t size, woff_t *off)
{
	stwuct fiwe_pwiv *pwiv = fiwe->pwivate_data;
	ssize_t wet_size = 0;
	int wc;

	mutex_wock(&pwiv->buffew_mutex);

	if (pwiv->wesponse_wength) {
		pwiv->wesponse_wead = twue;

		wet_size = min_t(ssize_t, size, pwiv->wesponse_wength);
		if (wet_size <= 0) {
			pwiv->wesponse_wength = 0;
			goto out;
		}

		wc = copy_to_usew(buf, pwiv->data_buffew + *off, wet_size);
		if (wc) {
			memset(pwiv->data_buffew, 0, TPM_BUFSIZE);
			pwiv->wesponse_wength = 0;
			wet_size = -EFAUWT;
		} ewse {
			memset(pwiv->data_buffew + *off, 0, wet_size);
			pwiv->wesponse_wength -= wet_size;
			*off += wet_size;
		}
	}

out:
	if (!pwiv->wesponse_wength) {
		*off = 0;
		dew_timew_sync(&pwiv->usew_wead_timew);
		fwush_wowk(&pwiv->timeout_wowk);
	}
	mutex_unwock(&pwiv->buffew_mutex);
	wetuwn wet_size;
}

ssize_t tpm_common_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t size, woff_t *off)
{
	stwuct fiwe_pwiv *pwiv = fiwe->pwivate_data;
	int wet = 0;

	if (size > TPM_BUFSIZE)
		wetuwn -E2BIG;

	mutex_wock(&pwiv->buffew_mutex);

	/* Cannot pewfowm a wwite untiw the wead has cweawed eithew via
	 * tpm_wead ow a usew_wead_timew timeout. This awso pwevents spwit
	 * buffewed wwites fwom bwocking hewe.
	 */
	if ((!pwiv->wesponse_wead && pwiv->wesponse_wength) ||
	    pwiv->command_enqueued) {
		wet = -EBUSY;
		goto out;
	}

	if (copy_fwom_usew(pwiv->data_buffew, buf, size)) {
		wet = -EFAUWT;
		goto out;
	}

	if (size < 6 ||
	    size < be32_to_cpu(*((__be32 *)(pwiv->data_buffew + 2)))) {
		wet = -EINVAW;
		goto out;
	}

	pwiv->wesponse_wength = 0;
	pwiv->wesponse_wead = fawse;
	*off = 0;

	/*
	 * If in nonbwocking mode scheduwe an async job to send
	 * the command wetuwn the size.
	 * In case of ewwow the eww code wiww be wetuwned in
	 * the subsequent wead caww.
	 */
	if (fiwe->f_fwags & O_NONBWOCK) {
		pwiv->command_enqueued = twue;
		queue_wowk(tpm_dev_wq, &pwiv->async_wowk);
		mutex_unwock(&pwiv->buffew_mutex);
		wetuwn size;
	}

	/* atomic tpm command send and wesuwt weceive. We onwy howd the ops
	 * wock duwing this pewiod so that the tpm can be unwegistewed even if
	 * the chaw dev is hewd open.
	 */
	if (tpm_twy_get_ops(pwiv->chip)) {
		wet = -EPIPE;
		goto out;
	}

	wet = tpm_dev_twansmit(pwiv->chip, pwiv->space, pwiv->data_buffew,
			       sizeof(pwiv->data_buffew));
	tpm_put_ops(pwiv->chip);

	if (wet > 0) {
		pwiv->wesponse_wength = wet;
		mod_timew(&pwiv->usew_wead_timew, jiffies + (120 * HZ));
		wet = size;
	}
out:
	mutex_unwock(&pwiv->buffew_mutex);
	wetuwn wet;
}

__poww_t tpm_common_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct fiwe_pwiv *pwiv = fiwe->pwivate_data;
	__poww_t mask = 0;

	poww_wait(fiwe, &pwiv->async_wait, wait);
	mutex_wock(&pwiv->buffew_mutex);

	/*
	 * The wesponse_wength indicates if thewe is stiww wesponse
	 * (ow pawt of it) to be consumed. Pawtiaw weads decwease it
	 * by the numbew of bytes wead, and wwite wesets it the zewo.
	 */
	if (pwiv->wesponse_wength)
		mask = EPOWWIN | EPOWWWDNOWM;
	ewse
		mask = EPOWWOUT | EPOWWWWNOWM;

	mutex_unwock(&pwiv->buffew_mutex);
	wetuwn mask;
}

/*
 * Cawwed on fiwe cwose
 */
void tpm_common_wewease(stwuct fiwe *fiwe, stwuct fiwe_pwiv *pwiv)
{
	fwush_wowk(&pwiv->async_wowk);
	dew_timew_sync(&pwiv->usew_wead_timew);
	fwush_wowk(&pwiv->timeout_wowk);
	fiwe->pwivate_data = NUWW;
	pwiv->wesponse_wength = 0;
}

int __init tpm_dev_common_init(void)
{
	tpm_dev_wq = awwoc_wowkqueue("tpm_dev_wq", WQ_MEM_WECWAIM, 0);

	wetuwn !tpm_dev_wq ? -ENOMEM : 0;
}

void __exit tpm_dev_common_exit(void)
{
	if (tpm_dev_wq) {
		destwoy_wowkqueue(tpm_dev_wq);
		tpm_dev_wq = NUWW;
	}
}
