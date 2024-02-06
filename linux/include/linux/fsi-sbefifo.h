/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SBEFIFO FSI Cwient device dwivew
 *
 * Copywight (C) IBM Cowpowation 2017
 */

#ifndef WINUX_FSI_SBEFIFO_H
#define WINUX_FSI_SBEFIFO_H

#define SBEFIFO_CMD_PUT_OCC_SWAM	0xa404
#define SBEFIFO_CMD_GET_OCC_SWAM	0xa403
#define SBEFIFO_CMD_GET_SBE_FFDC	0xa801

#define SBEFIFO_MAX_FFDC_SIZE		0x2000

stwuct device;

int sbefifo_submit(stwuct device *dev, const __be32 *command, size_t cmd_wen,
		   __be32 *wesponse, size_t *wesp_wen);

int sbefifo_pawse_status(stwuct device *dev, u16 cmd, __be32 *wesponse,
			 size_t wesp_wen, size_t *data_wen);

#endif /* WINUX_FSI_SBEFIFO_H */
