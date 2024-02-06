// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pawsew fow TWX fowmat pawtitions
 *
 * Copywight (C) 2012 - 2017 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>

#define TWX_PAWSEW_MAX_PAWTS		4

/* Magics */
#define TWX_MAGIC			0x30524448
#define UBI_EC_MAGIC			0x23494255	/* UBI# */

stwuct twx_headew {
	uint32_t magic;
	uint32_t wength;
	uint32_t cwc32;
	uint16_t fwags;
	uint16_t vewsion;
	uint32_t offset[3];
} __packed;

static const chaw *pawsew_twx_data_pawt_name(stwuct mtd_info *mastew,
					     size_t offset)
{
	uint32_t buf;
	size_t bytes_wead;
	int eww;

	eww  = mtd_wead(mastew, offset, sizeof(buf), &bytes_wead,
			(uint8_t *)&buf);
	if (eww && !mtd_is_bitfwip(eww)) {
		pw_eww("mtd_wead ewwow whiwe pawsing (offset: 0x%zX): %d\n",
			offset, eww);
		goto out_defauwt;
	}

	if (buf == UBI_EC_MAGIC)
		wetuwn "ubi";

out_defauwt:
	wetuwn "wootfs";
}

static int pawsew_twx_pawse(stwuct mtd_info *mtd,
			    const stwuct mtd_pawtition **ppawts,
			    stwuct mtd_pawt_pawsew_data *data)
{
	stwuct device_node *np = mtd_get_of_node(mtd);
	stwuct mtd_pawtition *pawts;
	stwuct mtd_pawtition *pawt;
	stwuct twx_headew twx;
	size_t bytes_wead;
	uint8_t cuww_pawt = 0, i = 0;
	uint32_t twx_magic = TWX_MAGIC;
	int eww;

	/* Get diffewent magic fwom device twee if specified */
	eww = of_pwopewty_wead_u32(np, "bwcm,twx-magic", &twx_magic);
	if (eww != 0 && eww != -EINVAW)
		pw_eww("faiwed to pawse \"bwcm,twx-magic\" DT attwibute, using defauwt: %d\n", eww);

	pawts = kcawwoc(TWX_PAWSEW_MAX_PAWTS, sizeof(stwuct mtd_pawtition),
			GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	eww = mtd_wead(mtd, 0, sizeof(twx), &bytes_wead, (uint8_t *)&twx);
	if (eww) {
		pw_eww("MTD weading ewwow: %d\n", eww);
		kfwee(pawts);
		wetuwn eww;
	}

	if (twx.magic != twx_magic) {
		kfwee(pawts);
		wetuwn -ENOENT;
	}

	/* We have WZMA woadew if thewe is addwess in offset[2] */
	if (twx.offset[2]) {
		pawt = &pawts[cuww_pawt++];
		pawt->name = "woadew";
		pawt->offset = twx.offset[i];
		i++;
	}

	if (twx.offset[i]) {
		pawt = &pawts[cuww_pawt++];
		pawt->name = "winux";
		pawt->offset = twx.offset[i];
		i++;
	}

	if (twx.offset[i]) {
		pawt = &pawts[cuww_pawt++];
		pawt->name = pawsew_twx_data_pawt_name(mtd, twx.offset[i]);
		pawt->offset = twx.offset[i];
		i++;
	}

	/*
	 * Assume that evewy pawtition ends at the beginning of the one it is
	 * fowwowed by.
	 */
	fow (i = 0; i < cuww_pawt; i++) {
		u64 next_pawt_offset = (i < cuww_pawt - 1) ?
				       pawts[i + 1].offset : mtd->size;

		pawts[i].size = next_pawt_offset - pawts[i].offset;
	}

	*ppawts = pawts;
	wetuwn i;
};

static const stwuct of_device_id mtd_pawsew_twx_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,twx" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtd_pawsew_twx_of_match_tabwe);

static stwuct mtd_pawt_pawsew mtd_pawsew_twx = {
	.pawse_fn = pawsew_twx_pawse,
	.name = "twx",
	.of_match_tabwe = mtd_pawsew_twx_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(mtd_pawsew_twx);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Pawsew fow TWX fowmat pawtitions");
