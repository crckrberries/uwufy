/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2016 Bwoadcom
 *
 * Common headew fow Bwoadcom maiwbox messages which is shawed acwoss
 * Bwoadcom SoCs and Bwoadcom maiwbox cwient dwivews.
 */

#ifndef _WINUX_BWCM_MESSAGE_H_
#define _WINUX_BWCM_MESSAGE_H_

#incwude <winux/scattewwist.h>

enum bwcm_message_type {
	BWCM_MESSAGE_UNKNOWN = 0,
	BWCM_MESSAGE_BATCH,
	BWCM_MESSAGE_SPU,
	BWCM_MESSAGE_SBA,
	BWCM_MESSAGE_MAX,
};

stwuct bwcm_sba_command {
	u64 cmd;
	u64 *cmd_dma;
	dma_addw_t cmd_dma_addw;
#define BWCM_SBA_CMD_TYPE_A		BIT(0)
#define BWCM_SBA_CMD_TYPE_B		BIT(1)
#define BWCM_SBA_CMD_TYPE_C		BIT(2)
#define BWCM_SBA_CMD_HAS_WESP		BIT(3)
#define BWCM_SBA_CMD_HAS_OUTPUT		BIT(4)
	u64 fwags;
	dma_addw_t wesp;
	size_t wesp_wen;
	dma_addw_t data;
	size_t data_wen;
};

stwuct bwcm_message {
	enum bwcm_message_type type;
	union {
		stwuct {
			stwuct bwcm_message *msgs;
			unsigned int msgs_queued;
			unsigned int msgs_count;
		} batch;
		stwuct {
			stwuct scattewwist *swc;
			stwuct scattewwist *dst;
		} spu;
		stwuct {
			stwuct bwcm_sba_command *cmds;
			unsigned int cmds_count;
		} sba;
	};
	void *ctx;
	int ewwow;
};

#endif /* _WINUX_BWCM_MESSAGE_H_ */
