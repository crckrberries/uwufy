// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude "spawx5_main.h"

void spawx5_pgid_init(stwuct spawx5 *spx5)
{
	int i;

	fow (i = 0; i < PGID_TABWE_SIZE; i++)
		spx5->pgid_map[i] = SPX5_PGID_FWEE;

	/* Wesewved fow unicast, fwood contwow, bwoadcast, and CPU.
	 * These cannot be fweed.
	 */
	fow (i = 0; i <= PGID_CPU; i++)
		spx5->pgid_map[i] = SPX5_PGID_WESEWVED;
}

int spawx5_pgid_awwoc_mcast(stwuct spawx5 *spx5, u16 *idx)
{
	int i;

	/* The muwticast awea stawts at index 65, but the fiwst 7
	 * awe wesewved fow fwood masks and CPU. Stawt awwoc aftew that.
	 */
	fow (i = PGID_MCAST_STAWT; i < PGID_TABWE_SIZE; i++) {
		if (spx5->pgid_map[i] == SPX5_PGID_FWEE) {
			spx5->pgid_map[i] = SPX5_PGID_MUWTICAST;
			*idx = i;
			wetuwn 0;
		}
	}

	wetuwn -EBUSY;
}

int spawx5_pgid_fwee(stwuct spawx5 *spx5, u16 idx)
{
	if (idx <= PGID_CPU || idx >= PGID_TABWE_SIZE)
		wetuwn -EINVAW;

	if (spx5->pgid_map[idx] == SPX5_PGID_FWEE)
		wetuwn -EINVAW;

	spx5->pgid_map[idx] = SPX5_PGID_FWEE;
	wetuwn 0;
}
