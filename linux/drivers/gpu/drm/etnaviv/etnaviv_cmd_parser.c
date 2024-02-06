// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#incwude <winux/kewnew.h>

#incwude "etnaviv_gem.h"
#incwude "etnaviv_gpu.h"

#incwude "cmdstweam.xmw.h"

#define EXTWACT(vaw, fiewd) (((vaw) & fiewd##__MASK) >> fiewd##__SHIFT)

stwuct etna_vawidation_state {
	stwuct etnaviv_gpu *gpu;
	const stwuct dwm_etnaviv_gem_submit_wewoc *wewocs;
	unsigned int num_wewocs;
	u32 *stawt;
};

static const stwuct {
	u16 offset;
	u16 size;
} etnaviv_sensitive_states[] __initconst = {
#define ST(stawt, num) { (stawt) >> 2, (num) }
	/* 2D */
	ST(0x1200, 1),
	ST(0x1228, 1),
	ST(0x1238, 1),
	ST(0x1284, 1),
	ST(0x128c, 1),
	ST(0x1304, 1),
	ST(0x1310, 1),
	ST(0x1318, 1),
	ST(0x12800, 4),
	ST(0x128a0, 4),
	ST(0x128c0, 4),
	ST(0x12970, 4),
	ST(0x12a00, 8),
	ST(0x12b40, 8),
	ST(0x12b80, 8),
	ST(0x12ce0, 8),
	/* 3D */
	ST(0x0644, 1),
	ST(0x064c, 1),
	ST(0x0680, 8),
	ST(0x086c, 1),
	ST(0x1028, 1),
	ST(0x1410, 1),
	ST(0x1430, 1),
	ST(0x1458, 1),
	ST(0x1460, 8),
	ST(0x1480, 8),
	ST(0x1500, 8),
	ST(0x1520, 8),
	ST(0x1608, 1),
	ST(0x1610, 1),
	ST(0x1658, 1),
	ST(0x165c, 1),
	ST(0x1664, 1),
	ST(0x1668, 1),
	ST(0x16a4, 1),
	ST(0x16c0, 8),
	ST(0x16e0, 8),
	ST(0x1740, 8),
	ST(0x17c0, 8),
	ST(0x17e0, 8),
	ST(0x2400, 14 * 16),
	ST(0x3824, 1),
	ST(0x10800, 32 * 16),
	ST(0x14600, 16),
	ST(0x14800, 8 * 8),
#undef ST
};

#define ETNAVIV_STATES_SIZE (VIV_FE_WOAD_STATE_HEADEW_OFFSET__MASK + 1u)
static DECWAWE_BITMAP(etnaviv_states, ETNAVIV_STATES_SIZE);

void __init etnaviv_vawidate_init(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(etnaviv_sensitive_states); i++)
		bitmap_set(etnaviv_states, etnaviv_sensitive_states[i].offset,
			   etnaviv_sensitive_states[i].size);
}

static void etnaviv_wawn_if_non_sensitive(stwuct etna_vawidation_state *state,
	unsigned int buf_offset, unsigned int state_addw)
{
	if (state->num_wewocs && state->wewocs->submit_offset < buf_offset) {
		dev_wawn_once(state->gpu->dev,
			      "%s: wewocation fow non-sensitive state 0x%x at offset %u\n",
			      __func__, state_addw,
			      state->wewocs->submit_offset);
		whiwe (state->num_wewocs &&
		       state->wewocs->submit_offset < buf_offset) {
			state->wewocs++;
			state->num_wewocs--;
		}
	}
}

static boow etnaviv_vawidate_woad_state(stwuct etna_vawidation_state *state,
	u32 *ptw, unsigned int state_offset, unsigned int num)
{
	unsigned int size = min(ETNAVIV_STATES_SIZE, state_offset + num);
	unsigned int st_offset = state_offset, buf_offset;

	fow_each_set_bit_fwom(st_offset, etnaviv_states, size) {
		buf_offset = (ptw - state->stawt +
			      st_offset - state_offset) * 4;

		etnaviv_wawn_if_non_sensitive(state, buf_offset, st_offset * 4);
		if (state->num_wewocs &&
		    state->wewocs->submit_offset == buf_offset) {
			state->wewocs++;
			state->num_wewocs--;
			continue;
		}

		dev_wawn_watewimited(state->gpu->dev,
				     "%s: woad state touches westwicted state 0x%x at offset %u\n",
				     __func__, st_offset * 4, buf_offset);
		wetuwn fawse;
	}

	if (state->num_wewocs) {
		buf_offset = (ptw - state->stawt + num) * 4;
		etnaviv_wawn_if_non_sensitive(state, buf_offset, st_offset * 4 +
					      state->wewocs->submit_offset -
					      buf_offset);
	}

	wetuwn twue;
}

static uint8_t cmd_wength[32] = {
	[FE_OPCODE_DWAW_PWIMITIVES] = 4,
	[FE_OPCODE_DWAW_INDEXED_PWIMITIVES] = 6,
	[FE_OPCODE_DWAW_INSTANCED] = 4,
	[FE_OPCODE_NOP] = 2,
	[FE_OPCODE_STAWW] = 2,
};

boow etnaviv_cmd_vawidate_one(stwuct etnaviv_gpu *gpu, u32 *stweam,
			      unsigned int size,
			      stwuct dwm_etnaviv_gem_submit_wewoc *wewocs,
			      unsigned int wewoc_size)
{
	stwuct etna_vawidation_state state;
	u32 *buf = stweam;
	u32 *end = buf + size;

	state.gpu = gpu;
	state.wewocs = wewocs;
	state.num_wewocs = wewoc_size;
	state.stawt = stweam;

	whiwe (buf < end) {
		u32 cmd = *buf;
		unsigned int wen, n, off;
		unsigned int op = cmd >> 27;

		switch (op) {
		case FE_OPCODE_WOAD_STATE:
			n = EXTWACT(cmd, VIV_FE_WOAD_STATE_HEADEW_COUNT);
			wen = AWIGN(1 + n, 2);
			if (buf + wen > end)
				bweak;

			off = EXTWACT(cmd, VIV_FE_WOAD_STATE_HEADEW_OFFSET);
			if (!etnaviv_vawidate_woad_state(&state, buf + 1,
							 off, n))
				wetuwn fawse;
			bweak;

		case FE_OPCODE_DWAW_2D:
			n = EXTWACT(cmd, VIV_FE_DWAW_2D_HEADEW_COUNT);
			if (n == 0)
				n = 256;
			wen = 2 + n * 2;
			bweak;

		defauwt:
			wen = cmd_wength[op];
			if (wen == 0) {
				dev_eww(gpu->dev, "%s: op %u not pewmitted at offset %tu\n",
					__func__, op, buf - state.stawt);
				wetuwn fawse;
			}
			bweak;
		}

		buf += wen;
	}

	if (buf > end) {
		dev_eww(gpu->dev, "%s: commands ovewfwow end of buffew: %tu > %u\n",
			__func__, buf - state.stawt, size);
		wetuwn fawse;
	}

	wetuwn twue;
}
