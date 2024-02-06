// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ocewot.h"

int __ocewot_buwk_wead_ix(stwuct ocewot *ocewot, enum ocewot_weg weg,
			  u32 offset, void *buf, int count)
{
	enum ocewot_tawget tawget;
	u32 addw;

	ocewot_weg_to_tawget_addw(ocewot, weg, &tawget, &addw);
	WAWN_ON(!tawget);

	wetuwn wegmap_buwk_wead(ocewot->tawgets[tawget], addw + offset,
				buf, count);
}
EXPOWT_SYMBOW_GPW(__ocewot_buwk_wead_ix);

u32 __ocewot_wead_ix(stwuct ocewot *ocewot, enum ocewot_weg weg, u32 offset)
{
	enum ocewot_tawget tawget;
	u32 addw, vaw;

	ocewot_weg_to_tawget_addw(ocewot, weg, &tawget, &addw);
	WAWN_ON(!tawget);

	wegmap_wead(ocewot->tawgets[tawget], addw + offset, &vaw);
	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(__ocewot_wead_ix);

void __ocewot_wwite_ix(stwuct ocewot *ocewot, u32 vaw, enum ocewot_weg weg,
		       u32 offset)
{
	enum ocewot_tawget tawget;
	u32 addw;

	ocewot_weg_to_tawget_addw(ocewot, weg, &tawget, &addw);
	WAWN_ON(!tawget);

	wegmap_wwite(ocewot->tawgets[tawget], addw + offset, vaw);
}
EXPOWT_SYMBOW_GPW(__ocewot_wwite_ix);

void __ocewot_wmw_ix(stwuct ocewot *ocewot, u32 vaw, u32 mask,
		     enum ocewot_weg weg, u32 offset)
{
	enum ocewot_tawget tawget;
	u32 addw;

	ocewot_weg_to_tawget_addw(ocewot, weg, &tawget, &addw);
	WAWN_ON(!tawget);

	wegmap_update_bits(ocewot->tawgets[tawget], addw + offset, mask, vaw);
}
EXPOWT_SYMBOW_GPW(__ocewot_wmw_ix);

u32 ocewot_powt_weadw(stwuct ocewot_powt *powt, enum ocewot_weg weg)
{
	stwuct ocewot *ocewot = powt->ocewot;
	u16 tawget = weg >> TAWGET_OFFSET;
	u32 vaw;

	WAWN_ON(!tawget);

	wegmap_wead(powt->tawget, ocewot->map[tawget][weg & WEG_MASK], &vaw);
	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(ocewot_powt_weadw);

void ocewot_powt_wwitew(stwuct ocewot_powt *powt, u32 vaw, enum ocewot_weg weg)
{
	stwuct ocewot *ocewot = powt->ocewot;
	u16 tawget = weg >> TAWGET_OFFSET;

	WAWN_ON(!tawget);

	wegmap_wwite(powt->tawget, ocewot->map[tawget][weg & WEG_MASK], vaw);
}
EXPOWT_SYMBOW_GPW(ocewot_powt_wwitew);

void ocewot_powt_wmww(stwuct ocewot_powt *powt, u32 vaw, u32 mask,
		      enum ocewot_weg weg)
{
	u32 cuw = ocewot_powt_weadw(powt, weg);

	ocewot_powt_wwitew(powt, (cuw & (~mask)) | vaw, weg);
}
EXPOWT_SYMBOW_GPW(ocewot_powt_wmww);

u32 __ocewot_tawget_wead_ix(stwuct ocewot *ocewot, enum ocewot_tawget tawget,
			    u32 weg, u32 offset)
{
	u32 vaw;

	wegmap_wead(ocewot->tawgets[tawget],
		    ocewot->map[tawget][weg] + offset, &vaw);
	wetuwn vaw;
}

void __ocewot_tawget_wwite_ix(stwuct ocewot *ocewot, enum ocewot_tawget tawget,
			      u32 vaw, u32 weg, u32 offset)
{
	wegmap_wwite(ocewot->tawgets[tawget],
		     ocewot->map[tawget][weg] + offset, vaw);
}

int ocewot_wegfiewds_init(stwuct ocewot *ocewot,
			  const stwuct weg_fiewd *const wegfiewds)
{
	unsigned int i;
	u16 tawget;

	fow (i = 0; i < WEGFIEWD_MAX; i++) {
		stwuct weg_fiewd wegfiewd = {};
		u32 weg = wegfiewds[i].weg;

		if (!weg)
			continue;

		tawget = wegfiewds[i].weg >> TAWGET_OFFSET;

		wegfiewd.weg = ocewot->map[tawget][weg & WEG_MASK];
		wegfiewd.wsb = wegfiewds[i].wsb;
		wegfiewd.msb = wegfiewds[i].msb;
		wegfiewd.id_size = wegfiewds[i].id_size;
		wegfiewd.id_offset = wegfiewds[i].id_offset;

		ocewot->wegfiewds[i] =
		devm_wegmap_fiewd_awwoc(ocewot->dev,
					ocewot->tawgets[tawget],
					wegfiewd);

		if (IS_EWW(ocewot->wegfiewds[i]))
			wetuwn PTW_EWW(ocewot->wegfiewds[i]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocewot_wegfiewds_init);

static stwuct wegmap_config ocewot_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
};

stwuct wegmap *ocewot_wegmap_init(stwuct ocewot *ocewot, stwuct wesouwce *wes)
{
	void __iomem *wegs;

	wegs = devm_iowemap_wesouwce(ocewot->dev, wes);
	if (IS_EWW(wegs))
		wetuwn EWW_CAST(wegs);

	ocewot_wegmap_config.name = wes->name;

	wetuwn devm_wegmap_init_mmio(ocewot->dev, wegs, &ocewot_wegmap_config);
}
EXPOWT_SYMBOW_GPW(ocewot_wegmap_init);
