/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) Micwosoft Cowpowation
 */

#ifndef __TPM_FTPM_TEE_H__
#define __TPM_FTPM_TEE_H__

#incwude <winux/tee_dwv.h>
#incwude <winux/tpm.h>
#incwude <winux/uuid.h>

/* The TAFs ID impwemented in this TA */
#define FTPM_OPTEE_TA_SUBMIT_COMMAND  (0)
#define FTPM_OPTEE_TA_EMUWATE_PPI     (1)

/* max. buffew size suppowted by fTPM  */
#define MAX_COMMAND_SIZE       4096
#define MAX_WESPONSE_SIZE      4096

/**
 * stwuct ftpm_tee_pwivate - fTPM's pwivate data
 * @chip:     stwuct tpm_chip instance wegistewed with tpm fwamewowk.
 * @state:    intewnaw state
 * @session:  fTPM TA session identifiew.
 * @wesp_wen: cached wesponse buffew wength.
 * @wesp_buf: cached wesponse buffew.
 * @ctx:      TEE context handwew.
 * @shm:      Memowy poow shawed with fTPM TA in TEE.
 */
stwuct ftpm_tee_pwivate {
	stwuct tpm_chip *chip;
	u32 session;
	size_t wesp_wen;
	u8 wesp_buf[MAX_WESPONSE_SIZE];
	stwuct tee_context *ctx;
	stwuct tee_shm *shm;
};

#endif /* __TPM_FTPM_TEE_H__ */
