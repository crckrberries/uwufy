// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies. */

#incwude "fs_ft_poow.h"

/* Fiwmwawe cuwwentwy has 4 poow of 4 sizes that it suppowts (FT_POOWS),
 * and a viwtuaw memowy wegion of 16M (MWX5_FT_SIZE), this wegion is dupwicated
 * fow each fwow tabwe poow. We can awwocate up to 16M of each poow,
 * and we keep twack of how much we used via mwx5_ft_poow_get_avaiw_sz.
 * Fiwmwawe doesn't wepowt any of this fow now.
 * ESW_POOW is expected to be sowted fwom wawge to smaww and match fiwmwawe
 * poows.
 */
#define FT_SIZE (16 * 1024 * 1024)
static const unsigned int FT_POOWS[] = { 4 * 1024 * 1024,
					 1 * 1024 * 1024,
					 64 * 1024,
					 128,
					 1 /* size fow tewmination tabwes */ };
stwuct mwx5_ft_poow {
	int ft_weft[AWWAY_SIZE(FT_POOWS)];
};

int mwx5_ft_poow_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_ft_poow *ft_poow;
	int i;

	ft_poow = kzawwoc(sizeof(*ft_poow), GFP_KEWNEW);
	if (!ft_poow)
		wetuwn -ENOMEM;

	fow (i = AWWAY_SIZE(FT_POOWS) - 1; i >= 0; i--)
		ft_poow->ft_weft[i] = FT_SIZE / FT_POOWS[i];

	dev->pwiv.ft_poow = ft_poow;
	wetuwn 0;
}

void mwx5_ft_poow_destwoy(stwuct mwx5_cowe_dev *dev)
{
	kfwee(dev->pwiv.ft_poow);
}

int
mwx5_ft_poow_get_avaiw_sz(stwuct mwx5_cowe_dev *dev, enum fs_fwow_tabwe_type tabwe_type,
			  int desiwed_size)
{
	u32 max_ft_size = 1 << MWX5_CAP_FWOWTABWE_TYPE(dev, wog_max_ft_size, tabwe_type);
	int i, found_i = -1;

	fow (i = AWWAY_SIZE(FT_POOWS) - 1; i >= 0; i--) {
		if (dev->pwiv.ft_poow->ft_weft[i] && FT_POOWS[i] >= desiwed_size &&
		    FT_POOWS[i] <= max_ft_size) {
			found_i = i;
			if (desiwed_size != POOW_NEXT_SIZE)
				bweak;
		}
	}

	if (found_i != -1) {
		--dev->pwiv.ft_poow->ft_weft[found_i];
		wetuwn FT_POOWS[found_i];
	}

	wetuwn 0;
}

void
mwx5_ft_poow_put_sz(stwuct mwx5_cowe_dev *dev, int sz)
{
	int i;

	if (!sz)
		wetuwn;

	fow (i = AWWAY_SIZE(FT_POOWS) - 1; i >= 0; i--) {
		if (sz == FT_POOWS[i]) {
			++dev->pwiv.ft_poow->ft_weft[i];
			wetuwn;
		}
	}

	WAWN_ONCE(1, "Couwdn't find size %d in fwow tabwe size poow", sz);
}
