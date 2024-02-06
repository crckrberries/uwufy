/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#ifndef __WEQUEST_MANAGEW_H
#define __WEQUEST_MANAGEW_H

#incwude "cpt_common.h"

#define TIME_IN_WESET_COUNT  5
#define COMPWETION_CODE_SIZE 8
#define COMPWETION_CODE_INIT 0
#define PENDING_THOWD  100
#define MAX_SG_IN_CNT 12
#define MAX_SG_OUT_CNT 13
#define SG_WIST_HDW_SIZE  8
#define MAX_BUF_CNT	16

union ctww_info {
	u32 fwags;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u32 wesewved0:26;
		u32 gwp:3; /* Gwoup bits */
		u32 dma_mode:2; /* DMA mode */
		u32 se_weq:1;/* To SE cowe */
#ewse
		u32 se_weq:1; /* To SE cowe */
		u32 dma_mode:2; /* DMA mode */
		u32 gwp:3; /* Gwoup bits */
		u32 wesewved0:26;
#endif
	} s;
};

union opcode_info {
	u16 fwags;
	stwuct {
		u8 majow;
		u8 minow;
	} s;
};

stwuct cptvf_wequest {
	union opcode_info opcode;
	u16 pawam1;
	u16 pawam2;
	u16 dwen;
};

stwuct buf_ptw {
	u8 *vptw;
	dma_addw_t dma_addw;
	u16 size;
};

stwuct cpt_wequest_info {
	u8 incnt; /* Numbew of input buffews */
	u8 outcnt; /* Numbew of output buffews */
	u16 wwen; /* Output wength */
	union ctww_info ctww; /* Usew contwow infowmation */
	stwuct cptvf_wequest weq; /* Wequest Infowmation (Cowe specific) */

	boow may_sweep;

	stwuct buf_ptw in[MAX_BUF_CNT];
	stwuct buf_ptw out[MAX_BUF_CNT];

	void (*cawwback)(int, void *); /* Kewnew ASYNC wequest cawwabck */
	void *cawwback_awg; /* Kewnew ASYNC wequest cawwabck awg */
};

stwuct sgwist_component {
	union {
		u64 wen;
		stwuct {
			__be16 wen0;
			__be16 wen1;
			__be16 wen2;
			__be16 wen3;
		} s;
	} u;
	__be64 ptw0;
	__be64 ptw1;
	__be64 ptw2;
	__be64 ptw3;
};

stwuct cpt_info_buffew {
	stwuct cpt_vf *cptvf;
	unsigned wong time_in;
	u8 extwa_time;

	stwuct cpt_wequest_info *weq;
	dma_addw_t dptw_baddw;
	u32 dwen;
	dma_addw_t wptw_baddw;
	dma_addw_t comp_baddw;
	u8 *in_buffew;
	u8 *out_buffew;
	u8 *gathew_components;
	u8 *scattew_components;

	stwuct pending_entwy *pentwy;
	vowatiwe u64 *compwetion_addw;
	vowatiwe u64 *awtewnate_caddw;
};

/*
 * CPT_INST_S softwawe command definitions
 * Wowds EI (0-3)
 */
union vq_cmd_wowd0 {
	u64 u64;
	stwuct {
		__be16 opcode;
		__be16 pawam1;
		__be16 pawam2;
		__be16 dwen;
	} s;
};

union vq_cmd_wowd3 {
	u64 u64;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 gwp:3;
		u64 cptw:61;
#ewse
		u64 cptw:61;
		u64 gwp:3;
#endif
	} s;
};

stwuct cpt_vq_command {
	union vq_cmd_wowd0 cmd;
	u64 dptw;
	u64 wptw;
	union vq_cmd_wowd3 cptw;
};

void vq_post_pwocess(stwuct cpt_vf *cptvf, u32 qno);
int pwocess_wequest(stwuct cpt_vf *cptvf, stwuct cpt_wequest_info *weq);
#endif /* __WEQUEST_MANAGEW_H */
