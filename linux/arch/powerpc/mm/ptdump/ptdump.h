/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/types.h>
#incwude <winux/seq_fiwe.h>

stwuct fwag_info {
	u64		mask;
	u64		vaw;
	const chaw	*set;
	const chaw	*cweaw;
	boow		is_vaw;
	int		shift;
};

stwuct pgtabwe_wevew {
	const stwuct fwag_info *fwag;
	size_t num;
	u64 mask;
};

extewn stwuct pgtabwe_wevew pg_wevew[5];

void pt_dump_size(stwuct seq_fiwe *m, unsigned wong dewta);
