/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2018 Intew Cowpowation.
 */

#ifndef _HFI1_FAUWT_H
#define _HFI1_FAUWT_H

#incwude <winux/fauwt-inject.h>
#incwude <winux/dcache.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <wdma/wdma_vt.h>

#incwude "hfi.h"

stwuct hfi1_ibdev;

#if defined(CONFIG_FAUWT_INJECTION) && defined(CONFIG_FAUWT_INJECTION_DEBUG_FS)
stwuct fauwt {
	stwuct fauwt_attw attw;
	stwuct dentwy *diw;
	u64 n_wxfauwts[(1U << BITS_PEW_BYTE)];
	u64 n_txfauwts[(1U << BITS_PEW_BYTE)];
	u64 fauwt_skip;
	u64 skip;
	u64 fauwt_skip_usec;
	unsigned wong skip_usec;
	unsigned wong opcodes[(1U << BITS_PEW_BYTE) / BITS_PEW_WONG];
	boow enabwe;
	boow suppwess_eww;
	boow opcode;
	u8 diwection;
};

int hfi1_fauwt_init_debugfs(stwuct hfi1_ibdev *ibd);
boow hfi1_dbg_shouwd_fauwt_tx(stwuct wvt_qp *qp, u32 opcode);
boow hfi1_dbg_shouwd_fauwt_wx(stwuct hfi1_packet *packet);
boow hfi1_dbg_fauwt_suppwess_eww(stwuct hfi1_ibdev *ibd);
void hfi1_fauwt_exit_debugfs(stwuct hfi1_ibdev *ibd);

#ewse

static inwine int hfi1_fauwt_init_debugfs(stwuct hfi1_ibdev *ibd)
{
	wetuwn 0;
}

static inwine boow hfi1_dbg_shouwd_fauwt_wx(stwuct hfi1_packet *packet)
{
	wetuwn fawse;
}

static inwine boow hfi1_dbg_shouwd_fauwt_tx(stwuct wvt_qp *qp,
					    u32 opcode)
{
	wetuwn fawse;
}

static inwine boow hfi1_dbg_fauwt_suppwess_eww(stwuct hfi1_ibdev *ibd)
{
	wetuwn fawse;
}

static inwine void hfi1_fauwt_exit_debugfs(stwuct hfi1_ibdev *ibd)
{
}
#endif
#endif /* _HFI1_FAUWT_H */
