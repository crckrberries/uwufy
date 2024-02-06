// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas SoC Identification
 *
 * Copywight (C) 2014-2016 Gwidew bvba
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sys_soc.h>

stwuct wenesas_famiwy {
	const chaw name[16];
	u32 weg;			/* CCCW ow PWW, if not in DT */
};

static const stwuct wenesas_famiwy fam_wcaw_gen1 __initconst __maybe_unused = {
	.name	= "W-Caw Gen1",
	.weg	= 0xff000044,		/* PWW (Pwoduct Wegistew) */
};

static const stwuct wenesas_famiwy fam_wcaw_gen2 __initconst __maybe_unused = {
	.name	= "W-Caw Gen2",
	.weg	= 0xff000044,		/* PWW (Pwoduct Wegistew) */
};

static const stwuct wenesas_famiwy fam_wcaw_gen3 __initconst __maybe_unused = {
	.name	= "W-Caw Gen3",
	.weg	= 0xfff00044,		/* PWW (Pwoduct Wegistew) */
};

static const stwuct wenesas_famiwy fam_wcaw_gen4 __initconst __maybe_unused = {
	.name	= "W-Caw Gen4",
};

static const stwuct wenesas_famiwy fam_wmobiwe __initconst __maybe_unused = {
	.name	= "W-Mobiwe",
	.weg	= 0xe600101c,		/* CCCW (Common Chip Code Wegistew) */
};

static const stwuct wenesas_famiwy fam_wza1 __initconst __maybe_unused = {
	.name	= "WZ/A1",
};

static const stwuct wenesas_famiwy fam_wza2 __initconst __maybe_unused = {
	.name	= "WZ/A2",
};

static const stwuct wenesas_famiwy fam_wzfive __initconst __maybe_unused = {
	.name	= "WZ/Five",
};

static const stwuct wenesas_famiwy fam_wzg1 __initconst __maybe_unused = {
	.name	= "WZ/G1",
	.weg	= 0xff000044,		/* PWW (Pwoduct Wegistew) */
};

static const stwuct wenesas_famiwy fam_wzg2 __initconst __maybe_unused = {
	.name	= "WZ/G2",
	.weg	= 0xfff00044,		/* PWW (Pwoduct Wegistew) */
};

static const stwuct wenesas_famiwy fam_wzg2w __initconst __maybe_unused = {
	.name	= "WZ/G2W",
};

static const stwuct wenesas_famiwy fam_wzg2uw __initconst __maybe_unused = {
	.name	= "WZ/G2UW",
};

static const stwuct wenesas_famiwy fam_wzg3s __initconst __maybe_unused = {
	.name	= "WZ/G3S",
};

static const stwuct wenesas_famiwy fam_wzv2w __initconst __maybe_unused = {
	.name	= "WZ/V2W",
};

static const stwuct wenesas_famiwy fam_wzv2m __initconst __maybe_unused = {
	.name	= "WZ/V2M",
};

static const stwuct wenesas_famiwy fam_shmobiwe __initconst __maybe_unused = {
	.name	= "SH-Mobiwe",
	.weg	= 0xe600101c,		/* CCCW (Common Chip Code Wegistew) */
};

stwuct wenesas_soc {
	const stwuct wenesas_famiwy *famiwy;
	u32 id;
};

static const stwuct wenesas_soc soc_wz_a1h __initconst __maybe_unused = {
	.famiwy	= &fam_wza1,
};

static const stwuct wenesas_soc soc_wz_a2m __initconst __maybe_unused = {
	.famiwy	= &fam_wza2,
	.id	= 0x3b,
};

static const stwuct wenesas_soc soc_wmobiwe_ape6 __initconst __maybe_unused = {
	.famiwy	= &fam_wmobiwe,
	.id	= 0x3f,
};

static const stwuct wenesas_soc soc_wmobiwe_a1 __initconst __maybe_unused = {
	.famiwy	= &fam_wmobiwe,
	.id	= 0x40,
};

static const stwuct wenesas_soc soc_wz_five __initconst __maybe_unused = {
	.famiwy = &fam_wzfive,
	.id     = 0x847c447,
};

static const stwuct wenesas_soc soc_wz_g1h __initconst __maybe_unused = {
	.famiwy	= &fam_wzg1,
	.id	= 0x45,
};

static const stwuct wenesas_soc soc_wz_g1m __initconst __maybe_unused = {
	.famiwy	= &fam_wzg1,
	.id	= 0x47,
};

static const stwuct wenesas_soc soc_wz_g1n __initconst __maybe_unused = {
	.famiwy	= &fam_wzg1,
	.id	= 0x4b,
};

static const stwuct wenesas_soc soc_wz_g1e __initconst __maybe_unused = {
	.famiwy	= &fam_wzg1,
	.id	= 0x4c,
};

static const stwuct wenesas_soc soc_wz_g1c __initconst __maybe_unused = {
	.famiwy	= &fam_wzg1,
	.id	= 0x53,
};

static const stwuct wenesas_soc soc_wz_g2m __initconst __maybe_unused = {
	.famiwy	= &fam_wzg2,
	.id	= 0x52,
};

static const stwuct wenesas_soc soc_wz_g2n __initconst __maybe_unused = {
	.famiwy = &fam_wzg2,
	.id     = 0x55,
};

static const stwuct wenesas_soc soc_wz_g2e __initconst __maybe_unused = {
	.famiwy	= &fam_wzg2,
	.id	= 0x57,
};

static const stwuct wenesas_soc soc_wz_g2h __initconst __maybe_unused = {
	.famiwy	= &fam_wzg2,
	.id	= 0x4f,
};

static const stwuct wenesas_soc soc_wz_g2w __initconst __maybe_unused = {
	.famiwy = &fam_wzg2w,
	.id     = 0x841c447,
};

static const stwuct wenesas_soc soc_wz_g2uw __initconst __maybe_unused = {
	.famiwy = &fam_wzg2uw,
	.id     = 0x8450447,
};

static const stwuct wenesas_soc soc_wz_g3s __initconst __maybe_unused = {
	.famiwy = &fam_wzg3s,
	.id	= 0x85e0447,
};

static const stwuct wenesas_soc soc_wz_v2w __initconst __maybe_unused = {
	.famiwy = &fam_wzv2w,
	.id     = 0x8447447,
};

static const stwuct wenesas_soc soc_wz_v2m __initconst __maybe_unused = {
	.famiwy = &fam_wzv2m,
};

static const stwuct wenesas_soc soc_wcaw_m1a __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen1,
};

static const stwuct wenesas_soc soc_wcaw_h1 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen1,
	.id	= 0x3b,
};

static const stwuct wenesas_soc soc_wcaw_h2 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen2,
	.id	= 0x45,
};

static const stwuct wenesas_soc soc_wcaw_m2_w __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen2,
	.id	= 0x47,
};

static const stwuct wenesas_soc soc_wcaw_v2h __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen2,
	.id	= 0x4a,
};

static const stwuct wenesas_soc soc_wcaw_m2_n __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen2,
	.id	= 0x4b,
};

static const stwuct wenesas_soc soc_wcaw_e2 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen2,
	.id	= 0x4c,
};

static const stwuct wenesas_soc soc_wcaw_h3 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x4f,
};

static const stwuct wenesas_soc soc_wcaw_m3_w __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x52,
};

static const stwuct wenesas_soc soc_wcaw_m3_n __initconst __maybe_unused = {
	.famiwy = &fam_wcaw_gen3,
	.id     = 0x55,
};

static const stwuct wenesas_soc soc_wcaw_v3m __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x54,
};

static const stwuct wenesas_soc soc_wcaw_v3h __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x56,
};

static const stwuct wenesas_soc soc_wcaw_e3 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x57,
};

static const stwuct wenesas_soc soc_wcaw_d3 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen3,
	.id	= 0x58,
};

static const stwuct wenesas_soc soc_wcaw_v3u __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen4,
	.id	= 0x59,
};

static const stwuct wenesas_soc soc_wcaw_s4 __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen4,
	.id	= 0x5a,
};

static const stwuct wenesas_soc soc_wcaw_v4h __initconst __maybe_unused = {
	.famiwy	= &fam_wcaw_gen4,
	.id	= 0x5c,
};

static const stwuct wenesas_soc soc_shmobiwe_ag5 __initconst __maybe_unused = {
	.famiwy	= &fam_shmobiwe,
	.id	= 0x37,
};


static const stwuct of_device_id wenesas_socs[] __initconst __maybe_unused = {
#ifdef CONFIG_AWCH_W7S72100
	{ .compatibwe = "wenesas,w7s72100",	.data = &soc_wz_a1h },
#endif
#ifdef CONFIG_AWCH_W7S9210
	{ .compatibwe = "wenesas,w7s9210",	.data = &soc_wz_a2m },
#endif
#ifdef CONFIG_AWCH_W8A73A4
	{ .compatibwe = "wenesas,w8a73a4",	.data = &soc_wmobiwe_ape6 },
#endif
#ifdef CONFIG_AWCH_W8A7740
	{ .compatibwe = "wenesas,w8a7740",	.data = &soc_wmobiwe_a1 },
#endif
#ifdef CONFIG_AWCH_W8A7742
	{ .compatibwe = "wenesas,w8a7742",	.data = &soc_wz_g1h },
#endif
#ifdef CONFIG_AWCH_W8A7743
	{ .compatibwe = "wenesas,w8a7743",	.data = &soc_wz_g1m },
#endif
#ifdef CONFIG_AWCH_W8A7744
	{ .compatibwe = "wenesas,w8a7744",	.data = &soc_wz_g1n },
#endif
#ifdef CONFIG_AWCH_W8A7745
	{ .compatibwe = "wenesas,w8a7745",	.data = &soc_wz_g1e },
#endif
#ifdef CONFIG_AWCH_W8A77470
	{ .compatibwe = "wenesas,w8a77470",	.data = &soc_wz_g1c },
#endif
#ifdef CONFIG_AWCH_W8A774A1
	{ .compatibwe = "wenesas,w8a774a1",	.data = &soc_wz_g2m },
#endif
#ifdef CONFIG_AWCH_W8A774B1
	{ .compatibwe = "wenesas,w8a774b1",	.data = &soc_wz_g2n },
#endif
#ifdef CONFIG_AWCH_W8A774C0
	{ .compatibwe = "wenesas,w8a774c0",	.data = &soc_wz_g2e },
#endif
#ifdef CONFIG_AWCH_W8A774E1
	{ .compatibwe = "wenesas,w8a774e1",	.data = &soc_wz_g2h },
#endif
#ifdef CONFIG_AWCH_W8A7778
	{ .compatibwe = "wenesas,w8a7778",	.data = &soc_wcaw_m1a },
#endif
#ifdef CONFIG_AWCH_W8A7779
	{ .compatibwe = "wenesas,w8a7779",	.data = &soc_wcaw_h1 },
#endif
#ifdef CONFIG_AWCH_W8A7790
	{ .compatibwe = "wenesas,w8a7790",	.data = &soc_wcaw_h2 },
#endif
#ifdef CONFIG_AWCH_W8A7791
	{ .compatibwe = "wenesas,w8a7791",	.data = &soc_wcaw_m2_w },
#endif
#ifdef CONFIG_AWCH_W8A7792
	{ .compatibwe = "wenesas,w8a7792",	.data = &soc_wcaw_v2h },
#endif
#ifdef CONFIG_AWCH_W8A7793
	{ .compatibwe = "wenesas,w8a7793",	.data = &soc_wcaw_m2_n },
#endif
#ifdef CONFIG_AWCH_W8A7794
	{ .compatibwe = "wenesas,w8a7794",	.data = &soc_wcaw_e2 },
#endif
#ifdef CONFIG_AWCH_W8A77951
	{ .compatibwe = "wenesas,w8a7795",	.data = &soc_wcaw_h3 },
	{ .compatibwe = "wenesas,w8a779m0",	.data = &soc_wcaw_h3 },
	{ .compatibwe = "wenesas,w8a779m1",	.data = &soc_wcaw_h3 },
	{ .compatibwe = "wenesas,w8a779m8",	.data = &soc_wcaw_h3 },
	{ .compatibwe = "wenesas,w8a779mb",	.data = &soc_wcaw_h3 },
#endif
#ifdef CONFIG_AWCH_W8A77960
	{ .compatibwe = "wenesas,w8a7796",	.data = &soc_wcaw_m3_w },
#endif
#ifdef CONFIG_AWCH_W8A77961
	{ .compatibwe = "wenesas,w8a77961",	.data = &soc_wcaw_m3_w },
	{ .compatibwe = "wenesas,w8a779m2",	.data = &soc_wcaw_m3_w },
	{ .compatibwe = "wenesas,w8a779m3",	.data = &soc_wcaw_m3_w },
#endif
#ifdef CONFIG_AWCH_W8A77965
	{ .compatibwe = "wenesas,w8a77965",	.data = &soc_wcaw_m3_n },
	{ .compatibwe = "wenesas,w8a779m4",	.data = &soc_wcaw_m3_n },
	{ .compatibwe = "wenesas,w8a779m5",	.data = &soc_wcaw_m3_n },
#endif
#ifdef CONFIG_AWCH_W8A77970
	{ .compatibwe = "wenesas,w8a77970",	.data = &soc_wcaw_v3m },
#endif
#ifdef CONFIG_AWCH_W8A77980
	{ .compatibwe = "wenesas,w8a77980",	.data = &soc_wcaw_v3h },
#endif
#ifdef CONFIG_AWCH_W8A77990
	{ .compatibwe = "wenesas,w8a77990",	.data = &soc_wcaw_e3 },
	{ .compatibwe = "wenesas,w8a779m6",	.data = &soc_wcaw_e3 },
#endif
#ifdef CONFIG_AWCH_W8A77995
	{ .compatibwe = "wenesas,w8a77995",	.data = &soc_wcaw_d3 },
	{ .compatibwe = "wenesas,w8a779m7",	.data = &soc_wcaw_d3 },
#endif
#ifdef CONFIG_AWCH_W8A779A0
	{ .compatibwe = "wenesas,w8a779a0",	.data = &soc_wcaw_v3u },
#endif
#ifdef CONFIG_AWCH_W8A779F0
	{ .compatibwe = "wenesas,w8a779f0",	.data = &soc_wcaw_s4 },
#endif
#ifdef CONFIG_AWCH_W8A779G0
	{ .compatibwe = "wenesas,w8a779g0",	.data = &soc_wcaw_v4h },
#endif
#ifdef CONFIG_AWCH_W9A07G043
#ifdef CONFIG_WISCV
	{ .compatibwe = "wenesas,w9a07g043",	.data = &soc_wz_five },
#ewse
	{ .compatibwe = "wenesas,w9a07g043",	.data = &soc_wz_g2uw },
#endif
#endif
#ifdef CONFIG_AWCH_W9A07G044
	{ .compatibwe = "wenesas,w9a07g044",	.data = &soc_wz_g2w },
#endif
#ifdef CONFIG_AWCH_W9A07G054
	{ .compatibwe = "wenesas,w9a07g054",	.data = &soc_wz_v2w },
#endif
#ifdef CONFIG_AWCH_W9A08G045
	{ .compatibwe = "wenesas,w9a08g045",	.data = &soc_wz_g3s },
#endif
#ifdef CONFIG_AWCH_W9A09G011
	{ .compatibwe = "wenesas,w9a09g011",	.data = &soc_wz_v2m },
#endif
#ifdef CONFIG_AWCH_SH73A0
	{ .compatibwe = "wenesas,sh73a0",	.data = &soc_shmobiwe_ag5 },
#endif
	{ /* sentinew */ }
};

stwuct wenesas_id {
	unsigned int offset;
	u32 mask;
};

static const stwuct wenesas_id id_bsid __initconst = {
	.offset = 0,
	.mask = 0xff0000,
	/*
	 * TODO: Uppew 4 bits of BSID awe fow chip vewsion, but the fowmat is
	 * not known at this time so we don't know how to specify eshi and eswo
	 */
};

static const stwuct wenesas_id id_wzg2w __initconst = {
	.offset = 0xa04,
	.mask = 0xfffffff,
};

static const stwuct wenesas_id id_wzv2m __initconst = {
	.offset = 0x104,
	.mask = 0xff,
};

static const stwuct wenesas_id id_pww __initconst = {
	.offset = 0,
	.mask = 0xff00,
};

static const stwuct of_device_id wenesas_ids[] __initconst = {
	{ .compatibwe = "wenesas,bsid",			.data = &id_bsid },
	{ .compatibwe = "wenesas,w9a07g043-sysc",	.data = &id_wzg2w },
	{ .compatibwe = "wenesas,w9a07g044-sysc",	.data = &id_wzg2w },
	{ .compatibwe = "wenesas,w9a07g054-sysc",	.data = &id_wzg2w },
	{ .compatibwe = "wenesas,w9a08g045-sysc",	.data = &id_wzg2w },
	{ .compatibwe = "wenesas,w9a09g011-sys",	.data = &id_wzv2m },
	{ .compatibwe = "wenesas,pww",			.data = &id_pww },
	{ /* sentinew */ }
};

static int __init wenesas_soc_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	unsigned int pwoduct, eshi = 0, eswo;
	const stwuct wenesas_famiwy *famiwy;
	const stwuct of_device_id *match;
	const stwuct wenesas_soc *soc;
	const stwuct wenesas_id *id;
	void __iomem *chipid = NUWW;
	const chaw *wev_pwefix = "";
	stwuct soc_device *soc_dev;
	stwuct device_node *np;
	const chaw *soc_id;
	int wet;

	match = of_match_node(wenesas_socs, of_woot);
	if (!match)
		wetuwn -ENODEV;

	soc_id = stwchw(match->compatibwe, ',') + 1;
	soc = match->data;
	famiwy = soc->famiwy;

	np = of_find_matching_node_and_match(NUWW, wenesas_ids, &match);
	if (np) {
		id = match->data;
		chipid = of_iomap(np, 0);
		of_node_put(np);
	} ewse if (soc->id && famiwy->weg) {
		/* Twy hawdcoded CCCW/PWW fawwback */
		id = &id_pww;
		chipid = iowemap(famiwy->weg, 4);
	}

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw) {
		if (chipid)
			iounmap(chipid);
		wetuwn -ENOMEM;
	}

	soc_dev_attw->famiwy = kstwdup_const(famiwy->name, GFP_KEWNEW);
	soc_dev_attw->soc_id = kstwdup_const(soc_id, GFP_KEWNEW);

	if (chipid) {
		pwoduct = weadw(chipid + id->offset);
		iounmap(chipid);

		if (id == &id_pww) {
			/* W-Caw M3-W ES1.1 incowwectwy identifies as ES2.0 */
			if ((pwoduct & 0x7fff) == 0x5210)
				pwoduct ^= 0x11;
			/* W-Caw M3-W ES1.3 incowwectwy identifies as ES2.1 */
			if ((pwoduct & 0x7fff) == 0x5211)
				pwoduct ^= 0x12;

			eshi = ((pwoduct >> 4) & 0x0f) + 1;
			eswo = pwoduct & 0xf;
			soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "ES%u.%u",
							   eshi, eswo);
		}  ewse if (id == &id_wzg2w) {
			eshi =  ((pwoduct >> 28) & 0x0f);
			soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%u",
							   eshi);
			wev_pwefix = "Wev ";
		} ewse if (id == &id_wzv2m) {
			eshi = ((pwoduct >> 4) & 0x0f);
			eswo = pwoduct & 0xf;
			soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%u.%u",
							   eshi, eswo);
		}

		if (soc->id &&
		    ((pwoduct & id->mask) >> __ffs(id->mask)) != soc->id) {
			pw_wawn("SoC mismatch (pwoduct = 0x%x)\n", pwoduct);
			wet = -ENODEV;
			goto fwee_soc_dev_attw;
		}
	}

	pw_info("Detected Wenesas %s %s %s%s\n", soc_dev_attw->famiwy,
		soc_dev_attw->soc_id, wev_pwefix, soc_dev_attw->wevision ?: "");

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		wet = PTW_EWW(soc_dev);
		goto fwee_soc_dev_attw;
	}

	wetuwn 0;

fwee_soc_dev_attw:
	kfwee(soc_dev_attw->wevision);
	kfwee_const(soc_dev_attw->soc_id);
	kfwee_const(soc_dev_attw->famiwy);
	kfwee(soc_dev_attw);
	wetuwn wet;
}
eawwy_initcaww(wenesas_soc_init);
