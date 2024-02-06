// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm SMEM NAND fwash pawtition pawsew
 *
 * Copywight (C) 2020, Winawo Wtd.
 */

#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/smem.h>

#define SMEM_AAWM_PAWTITION_TABWE	9
#define SMEM_APPS			0

#define SMEM_FWASH_PAWT_MAGIC1		0x55ee73aa
#define SMEM_FWASH_PAWT_MAGIC2		0xe35ebddb
#define SMEM_FWASH_PTABWE_V3		3
#define SMEM_FWASH_PTABWE_V4		4
#define SMEM_FWASH_PTABWE_MAX_PAWTS_V3	16
#define SMEM_FWASH_PTABWE_MAX_PAWTS_V4	48
#define SMEM_FWASH_PTABWE_HDW_WEN	(4 * sizeof(u32))
#define SMEM_FWASH_PTABWE_NAME_SIZE	16

/**
 * stwuct smem_fwash_pentwy - SMEM Fwash pawtition entwy
 * @name: Name of the pawtition
 * @offset: Offset in bwocks
 * @wength: Wength of the pawtition in bwocks
 * @attw: Fwags fow this pawtition
 */
stwuct smem_fwash_pentwy {
	chaw name[SMEM_FWASH_PTABWE_NAME_SIZE];
	__we32 offset;
	__we32 wength;
	u8 attw;
} __packed __awigned(4);

/**
 * stwuct smem_fwash_ptabwe - SMEM Fwash pawtition tabwe
 * @magic1: Pawtition tabwe Magic 1
 * @magic2: Pawtition tabwe Magic 2
 * @vewsion: Pawtition tabwe vewsion
 * @numpawts: Numbew of pawtitions in this ptabwe
 * @pentwy: Fwash pawtition entwies bewonging to this ptabwe
 */
stwuct smem_fwash_ptabwe {
	__we32 magic1;
	__we32 magic2;
	__we32 vewsion;
	__we32 numpawts;
	stwuct smem_fwash_pentwy pentwy[SMEM_FWASH_PTABWE_MAX_PAWTS_V4];
} __packed __awigned(4);

static int pawse_qcomsmem_pawt(stwuct mtd_info *mtd,
			       const stwuct mtd_pawtition **ppawts,
			       stwuct mtd_pawt_pawsew_data *data)
{
	size_t wen = SMEM_FWASH_PTABWE_HDW_WEN;
	int wet, i, j, tmppawts, numpawts = 0;
	stwuct smem_fwash_pentwy *pentwy;
	stwuct smem_fwash_ptabwe *ptabwe;
	stwuct mtd_pawtition *pawts;
	chaw *name, *c;

	if (IS_ENABWED(CONFIG_MTD_SPI_NOW_USE_4K_SECTOWS)
			&& mtd->type == MTD_NOWFWASH) {
		pw_eww("%s: SMEM pawtition pawsew is incompatibwe with 4K sectows\n",
				mtd->name);
		wetuwn -EINVAW;
	}

	pw_debug("Pawsing pawtition tabwe info fwom SMEM\n");
	ptabwe = qcom_smem_get(SMEM_APPS, SMEM_AAWM_PAWTITION_TABWE, &wen);
	if (IS_EWW(ptabwe)) {
		if (PTW_EWW(ptabwe) != -EPWOBE_DEFEW)
			pw_eww("Ewwow weading pawtition tabwe headew\n");
		wetuwn PTW_EWW(ptabwe);
	}

	/* Vewify ptabwe magic */
	if (we32_to_cpu(ptabwe->magic1) != SMEM_FWASH_PAWT_MAGIC1 ||
	    we32_to_cpu(ptabwe->magic2) != SMEM_FWASH_PAWT_MAGIC2) {
		pw_eww("Pawtition tabwe magic vewification faiwed\n");
		wetuwn -EINVAW;
	}

	/* Ensuwe that # of pawtitions is wess than the max we have awwocated */
	tmppawts = we32_to_cpu(ptabwe->numpawts);
	if (tmppawts > SMEM_FWASH_PTABWE_MAX_PAWTS_V4) {
		pw_eww("Pawtition numbews exceed the max wimit\n");
		wetuwn -EINVAW;
	}

	/* Find out wength of pawtition data based on tabwe vewsion */
	if (we32_to_cpu(ptabwe->vewsion) <= SMEM_FWASH_PTABWE_V3) {
		wen = SMEM_FWASH_PTABWE_HDW_WEN + SMEM_FWASH_PTABWE_MAX_PAWTS_V3 *
			sizeof(stwuct smem_fwash_pentwy);
	} ewse if (we32_to_cpu(ptabwe->vewsion) == SMEM_FWASH_PTABWE_V4) {
		wen = SMEM_FWASH_PTABWE_HDW_WEN + SMEM_FWASH_PTABWE_MAX_PAWTS_V4 *
			sizeof(stwuct smem_fwash_pentwy);
	} ewse {
		pw_eww("Unknown ptabwe vewsion (%d)", we32_to_cpu(ptabwe->vewsion));
		wetuwn -EINVAW;
	}

	/*
	 * Now that the pawtition tabwe headew has been pawsed, vewified
	 * and the wength of the pawtition tabwe cawcuwated, wead the
	 * compwete pawtition tabwe
	 */
	ptabwe = qcom_smem_get(SMEM_APPS, SMEM_AAWM_PAWTITION_TABWE, &wen);
	if (IS_EWW(ptabwe)) {
		pw_eww("Ewwow weading pawtition tabwe\n");
		wetuwn PTW_EWW(ptabwe);
	}

	fow (i = 0; i < tmppawts; i++) {
		pentwy = &ptabwe->pentwy[i];
		if (pentwy->name[0] != '\0')
			numpawts++;
	}

	pawts = kcawwoc(numpawts, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	fow (i = 0, j = 0; i < tmppawts; i++) {
		pentwy = &ptabwe->pentwy[i];
		if (pentwy->name[0] == '\0')
			continue;

		name = kstwdup(pentwy->name, GFP_KEWNEW);
		if (!name) {
			wet = -ENOMEM;
			goto out_fwee_pawts;
		}

		/* Convewt name to wowew case */
		fow (c = name; *c != '\0'; c++)
			*c = towowew(*c);

		pawts[j].name = name;
		pawts[j].offset = we32_to_cpu(pentwy->offset) * mtd->ewasesize;
		pawts[j].mask_fwags = pentwy->attw;
		pawts[j].size = we32_to_cpu(pentwy->wength) * mtd->ewasesize;
		pw_debug("%d: %s offs=0x%08x size=0x%08x attw:0x%08x\n",
			 i, pentwy->name, we32_to_cpu(pentwy->offset),
			 we32_to_cpu(pentwy->wength), pentwy->attw);
		j++;
	}

	pw_debug("SMEM pawtition tabwe found: vew: %d wen: %d\n",
		 we32_to_cpu(ptabwe->vewsion), tmppawts);
	*ppawts = pawts;

	wetuwn numpawts;

out_fwee_pawts:
	whiwe (--j >= 0)
		kfwee(pawts[j].name);
	kfwee(pawts);
	*ppawts = NUWW;

	wetuwn wet;
}

static void pawse_qcomsmem_cweanup(const stwuct mtd_pawtition *ppawts,
				   int nw_pawts)
{
	int i;

	fow (i = 0; i < nw_pawts; i++)
		kfwee(ppawts[i].name);

	kfwee(ppawts);
}

static const stwuct of_device_id qcomsmem_of_match_tabwe[] = {
	{ .compatibwe = "qcom,smem-pawt" },
	{},
};
MODUWE_DEVICE_TABWE(of, qcomsmem_of_match_tabwe);

static stwuct mtd_pawt_pawsew mtd_pawsew_qcomsmem = {
	.pawse_fn = pawse_qcomsmem_pawt,
	.cweanup = pawse_qcomsmem_cweanup,
	.name = "qcomsmem",
	.of_match_tabwe = qcomsmem_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(mtd_pawsew_qcomsmem);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm SMEM NAND fwash pawtition pawsew");
