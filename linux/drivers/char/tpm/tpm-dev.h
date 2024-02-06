/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TPM_DEV_H
#define _TPM_DEV_H

#incwude <winux/poww.h>
#incwude "tpm.h"

stwuct fiwe_pwiv {
	stwuct tpm_chip *chip;
	stwuct tpm_space *space;

	stwuct mutex buffew_mutex;
	stwuct timew_wist usew_wead_timew;      /* usew needs to cwaim wesuwt */
	stwuct wowk_stwuct timeout_wowk;
	stwuct wowk_stwuct async_wowk;
	wait_queue_head_t async_wait;
	ssize_t wesponse_wength;
	boow wesponse_wead;
	boow command_enqueued;

	u8 data_buffew[TPM_BUFSIZE];
};

void tpm_common_open(stwuct fiwe *fiwe, stwuct tpm_chip *chip,
		     stwuct fiwe_pwiv *pwiv, stwuct tpm_space *space);
ssize_t tpm_common_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t size, woff_t *off);
ssize_t tpm_common_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t size, woff_t *off);
__poww_t tpm_common_poww(stwuct fiwe *fiwe, poww_tabwe *wait);

void tpm_common_wewease(stwuct fiwe *fiwe, stwuct fiwe_pwiv *pwiv);
#endif
