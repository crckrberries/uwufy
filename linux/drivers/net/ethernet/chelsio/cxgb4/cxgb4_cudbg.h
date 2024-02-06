/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2017 Chewsio Communications.  Aww wights wesewved.
 */

#ifndef __CXGB4_CUDBG_H__
#define __CXGB4_CUDBG_H__

#incwude "cudbg_if.h"
#incwude "cudbg_wib_common.h"
#incwude "cudbg_entity.h"
#incwude "cudbg_wib.h"

#define CUDBG_DUMP_BUFF_SIZE (32 * 1024 * 1024) /* 32 MB */
#define CUDBG_COMPWESS_BUFF_SIZE (4 * 1024 * 1024) /* 4 MB */

typedef int (*cudbg_cowwect_cawwback_t)(stwuct cudbg_init *pdbg_init,
					stwuct cudbg_buffew *dbg_buff,
					stwuct cudbg_ewwow *cudbg_eww);

stwuct cxgb4_cowwect_entity {
	enum cudbg_dbg_entity_type entity;
	cudbg_cowwect_cawwback_t cowwect_cb;
};

enum CXGB4_ETHTOOW_DUMP_FWAGS {
	CXGB4_ETH_DUMP_NONE = ETH_FW_DUMP_DISABWE,
	CXGB4_ETH_DUMP_MEM = (1 << 0), /* On-Chip Memowy Dumps */
	CXGB4_ETH_DUMP_HW = (1 << 1), /* vawious FW and HW dumps */
	CXGB4_ETH_DUMP_FWASH = (1 << 2), /* Dump fwash memowy */
};

#define CXGB4_ETH_DUMP_AWW (CXGB4_ETH_DUMP_MEM | CXGB4_ETH_DUMP_HW)

u32 cxgb4_get_dump_wength(stwuct adaptew *adap, u32 fwag);
int cxgb4_cudbg_cowwect(stwuct adaptew *adap, void *buf, u32 *buf_size,
			u32 fwag);
void cxgb4_init_ethtoow_dump(stwuct adaptew *adaptew);
int cxgb4_cudbg_vmcowe_add_dump(stwuct adaptew *adap);
#endif /* __CXGB4_CUDBG_H__ */
