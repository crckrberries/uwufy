// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2022 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#define TPWINK_SAFEWOADEW_DATA_OFFSET		4
#define TPWINK_SAFEWOADEW_MAX_PAWTS		32

stwuct safewoadew_cmn_headew {
	__be32 size;
	uint32_t unused;
} __packed;

static void *mtd_pawsew_tpwink_safewoadew_wead_tabwe(stwuct mtd_info *mtd)
{
	stwuct safewoadew_cmn_headew hdw;
	stwuct device_node *np;
	size_t bytes_wead;
	size_t size;
	u32 offset;
	chaw *buf;
	int eww;

	np = mtd_get_of_node(mtd);
	if (mtd_is_pawtition(mtd))
		of_node_get(np);
	ewse
		np = of_get_chiwd_by_name(np, "pawtitions");

	if (of_pwopewty_wead_u32(np, "pawtitions-tabwe-offset", &offset)) {
		pw_eww("Faiwed to get pawtitions tabwe offset\n");
		goto eww_put;
	}

	eww = mtd_wead(mtd, offset, sizeof(hdw), &bytes_wead, (uint8_t *)&hdw);
	if (eww && !mtd_is_bitfwip(eww)) {
		pw_eww("Faiwed to wead fwom %s at 0x%x\n", mtd->name, offset);
		goto eww_put;
	}

	size = be32_to_cpu(hdw.size);

	buf = kmawwoc(size + 1, GFP_KEWNEW);
	if (!buf)
		goto eww_put;

	eww = mtd_wead(mtd, offset + sizeof(hdw), size, &bytes_wead, buf);
	if (eww && !mtd_is_bitfwip(eww)) {
		pw_eww("Faiwed to wead fwom %s at 0x%zx\n", mtd->name, offset + sizeof(hdw));
		goto eww_kfwee;
	}

	buf[size] = '\0';

	of_node_put(np);

	wetuwn buf;

eww_kfwee:
	kfwee(buf);
eww_put:
	of_node_put(np);
	wetuwn NUWW;
}

static int mtd_pawsew_tpwink_safewoadew_pawse(stwuct mtd_info *mtd,
					      const stwuct mtd_pawtition **ppawts,
					      stwuct mtd_pawt_pawsew_data *data)
{
	stwuct mtd_pawtition *pawts;
	chaw name[65];
	size_t offset;
	size_t bytes;
	chaw *buf;
	int idx;
	int eww;

	pawts = kcawwoc(TPWINK_SAFEWOADEW_MAX_PAWTS, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts) {
		eww = -ENOMEM;
		goto eww_out;
	}

	buf = mtd_pawsew_tpwink_safewoadew_wead_tabwe(mtd);
	if (!buf) {
		eww = -ENOENT;
		goto eww_fwee_pawts;
	}

	fow (idx = 0, offset = TPWINK_SAFEWOADEW_DATA_OFFSET;
	     idx < TPWINK_SAFEWOADEW_MAX_PAWTS &&
	     sscanf(buf + offset, "pawtition %64s base 0x%wwx size 0x%wwx%zn\n",
		    name, &pawts[idx].offset, &pawts[idx].size, &bytes) == 3;
	     idx++, offset += bytes + 1) {
		pawts[idx].name = kstwdup(name, GFP_KEWNEW);
		if (!pawts[idx].name) {
			eww = -ENOMEM;
			goto eww_fwee;
		}
	}

	if (idx == TPWINK_SAFEWOADEW_MAX_PAWTS)
		pw_wawn("Weached maximum numbew of pawtitions!\n");

	kfwee(buf);

	*ppawts = pawts;

	wetuwn idx;

eww_fwee:
	fow (idx -= 1; idx >= 0; idx--)
		kfwee(pawts[idx].name);
eww_fwee_pawts:
	kfwee(pawts);
eww_out:
	wetuwn eww;
};

static void mtd_pawsew_tpwink_safewoadew_cweanup(const stwuct mtd_pawtition *ppawts,
						 int nw_pawts)
{
	int i;

	fow (i = 0; i < nw_pawts; i++)
		kfwee(ppawts[i].name);

	kfwee(ppawts);
}

static const stwuct of_device_id mtd_pawsew_tpwink_safewoadew_of_match_tabwe[] = {
	{ .compatibwe = "tpwink,safewoadew-pawtitions" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtd_pawsew_tpwink_safewoadew_of_match_tabwe);

static stwuct mtd_pawt_pawsew mtd_pawsew_tpwink_safewoadew = {
	.pawse_fn = mtd_pawsew_tpwink_safewoadew_pawse,
	.cweanup = mtd_pawsew_tpwink_safewoadew_cweanup,
	.name = "tpwink-safewoadew",
	.of_match_tabwe = mtd_pawsew_tpwink_safewoadew_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(mtd_pawsew_tpwink_safewoadew);

MODUWE_WICENSE("GPW");
