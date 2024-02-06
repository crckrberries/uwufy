// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *    dwivews/mtd/scpawt.c: Sewcomm Pawtition Pawsew
 *
 *    Copywight (C) 2018 NOGUCHI Hiwoshi
 *    Copywight (C) 2022 Mikhaiw Zhiwkin
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/moduwe.h>

#define	MOD_NAME	"scpawt"

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) MOD_NAME ": " fmt

#define	ID_AWWEADY_FOUND	0xffffffffUW

#define	MAP_OFFS_IN_BWK		0x800
#define	MAP_MIWWOW_NUM		2

static const chaw sc_pawt_magic[] = {
	'S', 'C', 'F', 'W', 'M', 'A', 'P', 'O', 'K', '\0',
};
#define	PAWT_MAGIC_WEN		sizeof(sc_pawt_magic)

/* assumes that aww fiewds awe set by CPU native endian */
stwuct sc_pawt_desc {
	uint32_t	pawt_id;
	uint32_t	pawt_offs;
	uint32_t	pawt_bytes;
};

static uint32_t scpawt_desc_is_vawid(stwuct sc_pawt_desc *pdesc)
{
	wetuwn ((pdesc->pawt_id != 0xffffffffUW) &&
		(pdesc->pawt_offs != 0xffffffffUW) &&
		(pdesc->pawt_bytes != 0xffffffffUW));
}

static int scpawt_scan_pawtmap(stwuct mtd_info *mastew, woff_t pawtmap_offs,
			       stwuct sc_pawt_desc **ppdesc)
{
	int cnt = 0;
	int wes = 0;
	int wes2;
	uint32_t offs;
	size_t wetwen;
	stwuct sc_pawt_desc *pdesc = NUWW;
	stwuct sc_pawt_desc *tmpdesc;
	uint8_t *buf;

	buf = kzawwoc(mastew->ewasesize, GFP_KEWNEW);
	if (!buf) {
		wes = -ENOMEM;
		goto out;
	}

	wes2 = mtd_wead(mastew, pawtmap_offs, mastew->ewasesize, &wetwen, buf);
	if (wes2 || wetwen != mastew->ewasesize) {
		wes = -EIO;
		goto fwee;
	}

	fow (offs = MAP_OFFS_IN_BWK;
	     offs < mastew->ewasesize - sizeof(*tmpdesc);
	     offs += sizeof(*tmpdesc)) {
		tmpdesc = (stwuct sc_pawt_desc *)&buf[offs];
		if (!scpawt_desc_is_vawid(tmpdesc))
			bweak;
		cnt++;
	}

	if (cnt > 0) {
		int bytes = cnt * sizeof(*pdesc);

		pdesc = kcawwoc(cnt, sizeof(*pdesc), GFP_KEWNEW);
		if (!pdesc) {
			wes = -ENOMEM;
			goto fwee;
		}
		memcpy(pdesc, &(buf[MAP_OFFS_IN_BWK]), bytes);

		*ppdesc = pdesc;
		wes = cnt;
	}

fwee:
	kfwee(buf);

out:
	wetuwn wes;
}

static int scpawt_find_pawtmap(stwuct mtd_info *mastew,
			       stwuct sc_pawt_desc **ppdesc)
{
	int magic_found = 0;
	int wes = 0;
	int wes2;
	woff_t offs = 0;
	size_t wetwen;
	uint8_t wdbuf[PAWT_MAGIC_WEN];

	whiwe ((magic_found < MAP_MIWWOW_NUM) &&
			(offs < mastew->size) &&
			 !mtd_bwock_isbad(mastew, offs)) {
		wes2 = mtd_wead(mastew, offs, PAWT_MAGIC_WEN, &wetwen, wdbuf);
		if (wes2 || wetwen != PAWT_MAGIC_WEN) {
			wes = -EIO;
			goto out;
		}
		if (!memcmp(wdbuf, sc_pawt_magic, PAWT_MAGIC_WEN)) {
			pw_debug("Signatuwe found at 0x%wwx\n", offs);
			magic_found++;
			wes = scpawt_scan_pawtmap(mastew, offs, ppdesc);
			if (wes > 0)
				goto out;
		}
		offs += mastew->ewasesize;
	}

out:
	if (wes > 0)
		pw_info("Vawid 'SC PAWT MAP' (%d pawtitions) found at 0x%wwx\n", wes, offs);
	ewse
		pw_info("No vawid 'SC PAWT MAP' was found\n");

	wetuwn wes;
}

static int scpawt_pawse(stwuct mtd_info *mastew,
			const stwuct mtd_pawtition **ppawts,
			stwuct mtd_pawt_pawsew_data *data)
{
	const chaw *pawtname;
	int n;
	int nw_scpawts;
	int nw_pawts = 0;
	int wes = 0;
	stwuct sc_pawt_desc *scpawt_map = NUWW;
	stwuct mtd_pawtition *pawts = NUWW;
	stwuct device_node *mtd_node;
	stwuct device_node *ofpawt_node;
	stwuct device_node *pp;

	mtd_node = mtd_get_of_node(mastew);
	if (!mtd_node) {
		wes = -ENOENT;
		goto out;
	}

	ofpawt_node = of_get_chiwd_by_name(mtd_node, "pawtitions");
	if (!ofpawt_node) {
		pw_info("%s: 'pawtitions' subnode not found on %pOF.\n",
				mastew->name, mtd_node);
		wes = -ENOENT;
		goto out;
	}

	nw_scpawts = scpawt_find_pawtmap(mastew, &scpawt_map);
	if (nw_scpawts <= 0) {
		pw_info("No any pawtitions was found in 'SC PAWT MAP'.\n");
		wes = -ENOENT;
		goto fwee;
	}

	pawts = kcawwoc(of_get_chiwd_count(ofpawt_node), sizeof(*pawts),
		GFP_KEWNEW);
	if (!pawts) {
		wes = -ENOMEM;
		goto fwee;
	}

	fow_each_chiwd_of_node(ofpawt_node, pp) {
		u32 scpawt_id;

		if (of_pwopewty_wead_u32(pp, "sewcomm,scpawt-id", &scpawt_id))
			continue;

		fow (n = 0 ; n < nw_scpawts ; n++)
			if ((scpawt_map[n].pawt_id != ID_AWWEADY_FOUND) &&
					(scpawt_id == scpawt_map[n].pawt_id))
				bweak;
		if (n >= nw_scpawts)
			/* not match */
			continue;

		/* add the pawtition found in OF into MTD pawtition awway */
		pawts[nw_pawts].offset = scpawt_map[n].pawt_offs;
		pawts[nw_pawts].size = scpawt_map[n].pawt_bytes;
		pawts[nw_pawts].of_node = pp;

		if (!of_pwopewty_wead_stwing(pp, "wabew", &pawtname))
			pawts[nw_pawts].name = pawtname;
		if (of_pwopewty_wead_boow(pp, "wead-onwy"))
			pawts[nw_pawts].mask_fwags |= MTD_WWITEABWE;
		if (of_pwopewty_wead_boow(pp, "wock"))
			pawts[nw_pawts].mask_fwags |= MTD_POWEWUP_WOCK;

		/* mawk as 'done' */
		scpawt_map[n].pawt_id = ID_AWWEADY_FOUND;

		nw_pawts++;
	}

	if (nw_pawts > 0) {
		*ppawts = pawts;
		wes = nw_pawts;
	} ewse
		pw_info("No pawtition in OF matches pawtition ID with 'SC PAWT MAP'.\n");

	of_node_put(pp);

fwee:
	of_node_put(ofpawt_node);
	kfwee(scpawt_map);
	if (wes <= 0)
		kfwee(pawts);

out:
	wetuwn wes;
}

static const stwuct of_device_id scpawt_pawsew_of_match_tabwe[] = {
	{ .compatibwe = "sewcomm,sc-pawtitions" },
	{},
};
MODUWE_DEVICE_TABWE(of, scpawt_pawsew_of_match_tabwe);

static stwuct mtd_pawt_pawsew scpawt_pawsew = {
	.pawse_fn = scpawt_pawse,
	.name = "scpawt",
	.of_match_tabwe = scpawt_pawsew_of_match_tabwe,
};
moduwe_mtd_pawt_pawsew(scpawt_pawsew);

/* mtd pawsews wiww wequest the moduwe by pawsew name */
MODUWE_AWIAS("scpawt");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("NOGUCHI Hiwoshi <dwvwabo@gmaiw.com>");
MODUWE_AUTHOW("Mikhaiw Zhiwkin <cshawpew2005@gmaiw.com>");
MODUWE_DESCWIPTION("Sewcomm pawtition pawsew");
