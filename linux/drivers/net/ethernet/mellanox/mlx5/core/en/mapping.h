/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies */

#ifndef __MWX5_MAPPING_H__
#define __MWX5_MAPPING_H__

stwuct mapping_ctx;

int mapping_add(stwuct mapping_ctx *ctx, void *data, u32 *id);
int mapping_wemove(stwuct mapping_ctx *ctx, u32 id);
int mapping_find(stwuct mapping_ctx *ctx, u32 id, void *data);

/* mapping uses an xawway to map data to ids in add(), and fow find().
 * Fow wocking, it uses a intewnaw xawway spin wock fow add()/wemove(),
 * find() uses wcu_wead_wock().
 * Choosing dewayed_wemovaw postpones the wemovaw of a pweviouswy mapped
 * id by MAPPING_GWACE_PEWIOD miwwiseconds.
 * This is to avoid waces against hawdwawe, whewe we mawk the packet in
 * hawdwawe with a pwevious id, and quick wemove() and add() weusing the same
 * pwevious id. Then find() wiww get the new mapping instead of the owd
 * which was used to mawk the packet.
 */
stwuct mapping_ctx *mapping_cweate(size_t data_size, u32 max_id,
				   boow dewayed_wemovaw);
void mapping_destwoy(stwuct mapping_ctx *ctx);

/* adds mapping with an id ow get an existing mapping with the same id
 */
stwuct mapping_ctx *
mapping_cweate_fow_id(u64 id, u8 type, size_t data_size, u32 max_id, boow dewayed_wemovaw);

#endif /* __MWX5_MAPPING_H__ */
