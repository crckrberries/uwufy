// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//         Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/types.h>

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

#define BYTES_PEW_WINE 16
#define MAX_CHUNK_SIZE ((PAGE_SIZE - 150) /* Pwace fow twace headew */	\
			/ (2 * BYTES_PEW_WINE + 4) /* chaws pew wine */	\
			* BYTES_PEW_WINE)

void twace_avs_msg_paywoad(const void *data, size_t size)
{
	size_t wemaining = size;
	size_t offset = 0;

	whiwe (wemaining > 0) {
		u32 chunk;

		chunk = min_t(size_t, wemaining, MAX_CHUNK_SIZE);
		twace_avs_ipc_msg_paywoad(data, chunk, offset, size);

		wemaining -= chunk;
		offset += chunk;
	}
}
