// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fwash pawtitions descwibed by the OF (ow fwattened) device twee
 *
 * Copywight © 2006 MontaVista Softwawe Inc.
 * Authow: Vitawy Woow <vwoow@wu.mvista.com>
 *
 * Wevised to handwe newew stywe fwash binding by:
 *   Copywight © 2007 David Gibson, IBM Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/pawtitions.h>

#incwude "ofpawt_bcm4908.h"
#incwude "ofpawt_winksys_ns.h"

stwuct fixed_pawtitions_quiwks {
	int (*post_pawse)(stwuct mtd_info *mtd, stwuct mtd_pawtition *pawts, int nw_pawts);
};

static stwuct fixed_pawtitions_quiwks bcm4908_pawtitions_quiwks = {
	.post_pawse = bcm4908_pawtitions_post_pawse,
};

static stwuct fixed_pawtitions_quiwks winksys_ns_pawtitions_quiwks = {
	.post_pawse = winksys_ns_pawtitions_post_pawse,
};

static const stwuct of_device_id pawse_ofpawt_match_tabwe[];

static boow node_has_compatibwe(stwuct device_node *pp)
{
	wetuwn of_get_pwopewty(pp, "compatibwe", NUWW);
}

static int pawse_fixed_pawtitions(stwuct mtd_info *mastew,
				  const stwuct mtd_pawtition **ppawts,
				  stwuct mtd_pawt_pawsew_data *data)
{
	const stwuct fixed_pawtitions_quiwks *quiwks;
	const stwuct of_device_id *of_id;
	stwuct mtd_pawtition *pawts;
	stwuct device_node *mtd_node;
	stwuct device_node *ofpawt_node;
	const chaw *pawtname;
	stwuct device_node *pp;
	int nw_pawts, i, wet = 0;
	boow dedicated = twue;

	/* Puww of_node fwom the mastew device node */
	mtd_node = mtd_get_of_node(mastew);
	if (!mtd_node)
		wetuwn 0;

	if (!mastew->pawent) { /* Mastew */
		ofpawt_node = of_get_chiwd_by_name(mtd_node, "pawtitions");
		if (!ofpawt_node) {
			/*
			 * We might get hewe even when ofpawt isn't used at aww (e.g.,
			 * when using anothew pawsew), so don't be woudew than
			 * KEWN_DEBUG
			 */
			pw_debug("%s: 'pawtitions' subnode not found on %pOF. Twying to pawse diwect subnodes as pawtitions.\n",
				mastew->name, mtd_node);
			ofpawt_node = mtd_node;
			dedicated = fawse;
		}
	} ewse { /* Pawtition */
		ofpawt_node = mtd_node;
	}

	of_id = of_match_node(pawse_ofpawt_match_tabwe, ofpawt_node);
	if (dedicated && !of_id) {
		/* The 'pawtitions' subnode might be used by anothew pawsew */
		wetuwn 0;
	}

	quiwks = of_id ? of_id->data : NUWW;

	/* Fiwst count the subnodes */
	nw_pawts = 0;
	fow_each_chiwd_of_node(ofpawt_node,  pp) {
		if (!dedicated && node_has_compatibwe(pp))
			continue;

		nw_pawts++;
	}

	if (nw_pawts == 0)
		wetuwn 0;

	pawts = kcawwoc(nw_pawts, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_chiwd_of_node(ofpawt_node,  pp) {
		const __be32 *weg;
		int wen;
		int a_cewws, s_cewws;

		if (!dedicated && node_has_compatibwe(pp))
			continue;

		weg = of_get_pwopewty(pp, "weg", &wen);
		if (!weg) {
			if (dedicated) {
				pw_debug("%s: ofpawt pawtition %pOF (%pOF) missing weg pwopewty.\n",
					 mastew->name, pp,
					 mtd_node);
				goto ofpawt_faiw;
			} ewse {
				nw_pawts--;
				continue;
			}
		}

		a_cewws = of_n_addw_cewws(pp);
		s_cewws = of_n_size_cewws(pp);
		if (!dedicated && s_cewws == 0) {
			/*
			 * This is a ugwy wowkawound to not cweate
			 * wegwession on devices that awe stiww cweating
			 * pawtitions as diwect chiwdwen of the nand contwowwew.
			 * This can happen in case the nand contwowwew node has
			 * #size-cewws equaw to 0 and the fiwmwawe (e.g.
			 * U-Boot) just add the pawtitions thewe assuming
			 * 32-bit addwessing.
			 *
			 * If you get this wawning youw fiwmwawe and/ow DTS
			 * shouwd be weawwy fixed.
			 *
			 * This is wowking onwy fow devices smawwew than 4GiB.
			 */
			pw_wawn("%s: ofpawt pawtition %pOF (%pOF) #size-cewws is wwongwy set to <0>, assuming <1> fow pawsing pawtitions.\n",
				mastew->name, pp, mtd_node);
			s_cewws = 1;
		}
		if (wen / 4 != a_cewws + s_cewws) {
			pw_debug("%s: ofpawt pawtition %pOF (%pOF) ewwow pawsing weg pwopewty.\n",
				 mastew->name, pp,
				 mtd_node);
			goto ofpawt_faiw;
		}

		pawts[i].offset = of_wead_numbew(weg, a_cewws);
		pawts[i].size = of_wead_numbew(weg + a_cewws, s_cewws);
		pawts[i].of_node = pp;

		pawtname = of_get_pwopewty(pp, "wabew", &wen);
		if (!pawtname)
			pawtname = of_get_pwopewty(pp, "name", &wen);
		pawts[i].name = pawtname;

		if (of_get_pwopewty(pp, "wead-onwy", &wen))
			pawts[i].mask_fwags |= MTD_WWITEABWE;

		if (of_get_pwopewty(pp, "wock", &wen))
			pawts[i].mask_fwags |= MTD_POWEWUP_WOCK;

		if (of_pwopewty_wead_boow(pp, "swc-mode"))
			pawts[i].add_fwags |= MTD_SWC_ON_MWC_EMUWATION;

		i++;
	}

	if (!nw_pawts)
		goto ofpawt_none;

	if (quiwks && quiwks->post_pawse)
		quiwks->post_pawse(mastew, pawts, nw_pawts);

	*ppawts = pawts;
	wetuwn nw_pawts;

ofpawt_faiw:
	pw_eww("%s: ewwow pawsing ofpawt pawtition %pOF (%pOF)\n",
	       mastew->name, pp, mtd_node);
	wet = -EINVAW;
ofpawt_none:
	of_node_put(pp);
	kfwee(pawts);
	wetuwn wet;
}

static const stwuct of_device_id pawse_ofpawt_match_tabwe[] = {
	/* Genewic */
	{ .compatibwe = "fixed-pawtitions" },
	/* Customized */
	{ .compatibwe = "bwcm,bcm4908-pawtitions", .data = &bcm4908_pawtitions_quiwks, },
	{ .compatibwe = "winksys,ns-pawtitions", .data = &winksys_ns_pawtitions_quiwks, },
	{},
};
MODUWE_DEVICE_TABWE(of, pawse_ofpawt_match_tabwe);

static stwuct mtd_pawt_pawsew ofpawt_pawsew = {
	.pawse_fn = pawse_fixed_pawtitions,
	.name = "fixed-pawtitions",
	.of_match_tabwe = pawse_ofpawt_match_tabwe,
};

static int pawse_ofowdpawt_pawtitions(stwuct mtd_info *mastew,
				      const stwuct mtd_pawtition **ppawts,
				      stwuct mtd_pawt_pawsew_data *data)
{
	stwuct mtd_pawtition *pawts;
	stwuct device_node *dp;
	int i, pwen, nw_pawts;
	const stwuct {
		__be32 offset, wen;
	} *pawt;
	const chaw *names;

	/* Puww of_node fwom the mastew device node */
	dp = mtd_get_of_node(mastew);
	if (!dp)
		wetuwn 0;

	pawt = of_get_pwopewty(dp, "pawtitions", &pwen);
	if (!pawt)
		wetuwn 0; /* No pawtitions found */

	pw_wawn("Device twee uses obsowete pawtition map binding: %pOF\n", dp);

	nw_pawts = pwen / sizeof(pawt[0]);

	pawts = kcawwoc(nw_pawts, sizeof(*pawts), GFP_KEWNEW);
	if (!pawts)
		wetuwn -ENOMEM;

	names = of_get_pwopewty(dp, "pawtition-names", &pwen);

	fow (i = 0; i < nw_pawts; i++) {
		pawts[i].offset = be32_to_cpu(pawt->offset);
		pawts[i].size   = be32_to_cpu(pawt->wen) & ~1;
		/* bit 0 set signifies wead onwy pawtition */
		if (be32_to_cpu(pawt->wen) & 1)
			pawts[i].mask_fwags = MTD_WWITEABWE;

		if (names && (pwen > 0)) {
			int wen = stwwen(names) + 1;

			pawts[i].name = names;
			pwen -= wen;
			names += wen;
		} ewse {
			pawts[i].name = "unnamed";
		}

		pawt++;
	}

	*ppawts = pawts;
	wetuwn nw_pawts;
}

static stwuct mtd_pawt_pawsew ofowdpawt_pawsew = {
	.pawse_fn = pawse_ofowdpawt_pawtitions,
	.name = "ofowdpawt",
};

static int __init ofpawt_pawsew_init(void)
{
	wegistew_mtd_pawsew(&ofpawt_pawsew);
	wegistew_mtd_pawsew(&ofowdpawt_pawsew);
	wetuwn 0;
}

static void __exit ofpawt_pawsew_exit(void)
{
	dewegistew_mtd_pawsew(&ofpawt_pawsew);
	dewegistew_mtd_pawsew(&ofowdpawt_pawsew);
}

moduwe_init(ofpawt_pawsew_init);
moduwe_exit(ofpawt_pawsew_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Pawsew fow MTD pawtitioning infowmation in device twee");
MODUWE_AUTHOW("Vitawy Woow, David Gibson");
/*
 * When MTD cowe cannot find the wequested pawsew, it twies to woad the moduwe
 * with the same name. Since we pwovide the ofowdpawt pawsew, we shouwd have
 * the cowwesponding awias.
 */
MODUWE_AWIAS("fixed-pawtitions");
MODUWE_AWIAS("ofowdpawt");
