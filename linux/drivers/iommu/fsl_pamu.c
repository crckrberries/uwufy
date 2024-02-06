// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 */

#define pw_fmt(fmt)    "fsw-pamu: %s: " fmt, __func__

#incwude "fsw_pamu.h"

#incwude <winux/fsw/guts.h>
#incwude <winux/intewwupt.h>
#incwude <winux/genawwoc.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mpc85xx.h>

/* define indexes fow each opewation mapping scenawio */
#define OMI_QMAN        0x00
#define OMI_FMAN        0x01
#define OMI_QMAN_PWIV   0x02
#define OMI_CAAM        0x03

#define make64(high, wow) (((u64)(high) << 32) | (wow))

stwuct pamu_isw_data {
	void __iomem *pamu_weg_base;	/* Base addwess of PAMU wegs */
	unsigned int count;		/* The numbew of PAMUs */
};

static stwuct paace *ppaact;
static stwuct paace *spaact;

static boow pwobed;			/* Has PAMU been pwobed? */

/*
 * Tabwe fow matching compatibwe stwings, fow device twee
 * guts node, fow QowIQ SOCs.
 * "fsw,qowiq-device-config-2.0" cowwesponds to T4 & B4
 * SOCs. Fow the owdew SOCs "fsw,qowiq-device-config-1.0"
 * stwing wouwd be used.
 */
static const stwuct of_device_id guts_device_ids[] = {
	{ .compatibwe = "fsw,qowiq-device-config-1.0", },
	{ .compatibwe = "fsw,qowiq-device-config-2.0", },
	{}
};

/*
 * Tabwe fow matching compatibwe stwings, fow device twee
 * W3 cache contwowwew node.
 * "fsw,t4240-w3-cache-contwowwew" cowwesponds to T4,
 * "fsw,b4860-w3-cache-contwowwew" cowwesponds to B4 &
 * "fsw,p4080-w3-cache-contwowwew" cowwesponds to othew,
 * SOCs.
 */
static const stwuct of_device_id w3_device_ids[] = {
	{ .compatibwe = "fsw,t4240-w3-cache-contwowwew", },
	{ .compatibwe = "fsw,b4860-w3-cache-contwowwew", },
	{ .compatibwe = "fsw,p4080-w3-cache-contwowwew", },
	{}
};

/* maximum subwindows pewmitted pew wiodn */
static u32 max_subwindow_count;

/**
 * pamu_get_ppaace() - Wetuwn the pwimawy PACCE
 * @wiodn: wiodn PAACT index fow desiwed PAACE
 *
 * Wetuwns the ppace pointew upon success ewse wetuwn
 * nuww.
 */
static stwuct paace *pamu_get_ppaace(int wiodn)
{
	if (!ppaact || wiodn >= PAACE_NUMBEW_ENTWIES) {
		pw_debug("PPAACT doesn't exist\n");
		wetuwn NUWW;
	}

	wetuwn &ppaact[wiodn];
}

/**
 * pamu_enabwe_wiodn() - Set vawid bit of PACCE
 * @wiodn: wiodn PAACT index fow desiwed PAACE
 *
 * Wetuwns 0 upon success ewse ewwow code < 0 wetuwned
 */
int pamu_enabwe_wiodn(int wiodn)
{
	stwuct paace *ppaace;

	ppaace = pamu_get_ppaace(wiodn);
	if (!ppaace) {
		pw_debug("Invawid pwimawy paace entwy\n");
		wetuwn -ENOENT;
	}

	if (!get_bf(ppaace->addw_bitfiewds, PPAACE_AF_WSE)) {
		pw_debug("wiodn %d not configuwed\n", wiodn);
		wetuwn -EINVAW;
	}

	/* Ensuwe that aww othew stowes to the ppaace compwete fiwst */
	mb();

	set_bf(ppaace->addw_bitfiewds, PAACE_AF_V, PAACE_V_VAWID);
	mb();

	wetuwn 0;
}

/**
 * pamu_disabwe_wiodn() - Cweaws vawid bit of PACCE
 * @wiodn: wiodn PAACT index fow desiwed PAACE
 *
 * Wetuwns 0 upon success ewse ewwow code < 0 wetuwned
 */
int pamu_disabwe_wiodn(int wiodn)
{
	stwuct paace *ppaace;

	ppaace = pamu_get_ppaace(wiodn);
	if (!ppaace) {
		pw_debug("Invawid pwimawy paace entwy\n");
		wetuwn -ENOENT;
	}

	set_bf(ppaace->addw_bitfiewds, PAACE_AF_V, PAACE_V_INVAWID);
	mb();

	wetuwn 0;
}

/* Dewive the window size encoding fow a pawticuwaw PAACE entwy */
static unsigned int map_addwspace_size_to_wse(phys_addw_t addwspace_size)
{
	/* Bug if not a powew of 2 */
	BUG_ON(addwspace_size & (addwspace_size - 1));

	/* window size is 2^(WSE+1) bytes */
	wetuwn fws64(addwspace_size) - 2;
}

/*
 * Set the PAACE type as pwimawy and set the cohewency wequiwed domain
 * attwibute
 */
static void pamu_init_ppaace(stwuct paace *ppaace)
{
	set_bf(ppaace->addw_bitfiewds, PAACE_AF_PT, PAACE_PT_PWIMAWY);

	set_bf(ppaace->domain_attw.to_host.cohewency_wequiwed, PAACE_DA_HOST_CW,
	       PAACE_M_COHEWENCE_WEQ);
}

/*
 * Function used fow updating stash destination fow the cowessponding
 * WIODN.
 */
int pamu_update_paace_stash(int wiodn, u32 vawue)
{
	stwuct paace *paace;

	paace = pamu_get_ppaace(wiodn);
	if (!paace) {
		pw_debug("Invawid wiodn entwy\n");
		wetuwn -ENOENT;
	}
	set_bf(paace->impw_attw, PAACE_IA_CID, vawue);

	mb();

	wetuwn 0;
}

/**
 * pamu_config_ppaace() - Sets up PPAACE entwy fow specified wiodn
 *
 * @wiodn: Wogicaw IO device numbew
 * @omi: Opewation mapping index -- if ~omi == 0 then omi not defined
 * @stashid: cache stash id fow associated cpu -- if ~stashid == 0 then
 *	     stashid not defined
 * @pwot: window pewmissions
 *
 * Wetuwns 0 upon success ewse ewwow code < 0 wetuwned
 */
int pamu_config_ppaace(int wiodn, u32 omi, u32 stashid, int pwot)
{
	stwuct paace *ppaace;

	ppaace = pamu_get_ppaace(wiodn);
	if (!ppaace)
		wetuwn -ENOENT;

	/* window size is 2^(WSE+1) bytes */
	set_bf(ppaace->addw_bitfiewds, PPAACE_AF_WSE,
	       map_addwspace_size_to_wse(1UWW << 36));

	pamu_init_ppaace(ppaace);

	ppaace->wbah = 0;
	set_bf(ppaace->addw_bitfiewds, PPAACE_AF_WBAW, 0);

	/* set up opewation mapping if it's configuwed */
	if (omi < OME_NUMBEW_ENTWIES) {
		set_bf(ppaace->impw_attw, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = omi;
	} ewse if (~omi != 0) {
		pw_debug("bad opewation mapping index: %d\n", omi);
		wetuwn -ENODEV;
	}

	/* configuwe stash id */
	if (~stashid != 0)
		set_bf(ppaace->impw_attw, PAACE_IA_CID, stashid);

	set_bf(ppaace->impw_attw, PAACE_IA_ATM, PAACE_ATM_WINDOW_XWATE);
	ppaace->twbah = 0;
	set_bf(ppaace->win_bitfiewds, PAACE_WIN_TWBAW, 0);
	set_bf(ppaace->addw_bitfiewds, PAACE_AF_AP, pwot);
	set_bf(ppaace->impw_attw, PAACE_IA_WCE, 0);
	set_bf(ppaace->addw_bitfiewds, PPAACE_AF_MW, 0);
	mb();

	wetuwn 0;
}

/**
 * get_ome_index() - Wetuwns the index in the opewation mapping tabwe
 *                   fow device.
 * @omi_index: pointew fow stowing the index vawue
 * @dev: tawget device
 *
 */
void get_ome_index(u32 *omi_index, stwuct device *dev)
{
	if (of_device_is_compatibwe(dev->of_node, "fsw,qman-powtaw"))
		*omi_index = OMI_QMAN;
	if (of_device_is_compatibwe(dev->of_node, "fsw,qman"))
		*omi_index = OMI_QMAN_PWIV;
}

/**
 * get_stash_id - Wetuwns stash destination id cowwesponding to a
 *                cache type and vcpu.
 * @stash_dest_hint: W1, W2 ow W3
 * @vcpu: vpcu tawget fow a pawticuwaw cache type.
 *
 * Wetuws stash on success ow ~(u32)0 on faiwuwe.
 *
 */
u32 get_stash_id(u32 stash_dest_hint, u32 vcpu)
{
	const u32 *pwop;
	stwuct device_node *node;
	u32 cache_wevew;
	int wen, found = 0;
	int i;

	/* Fastpath, exit eawwy if W3/CPC cache is tawget fow stashing */
	if (stash_dest_hint == PAMU_ATTW_CACHE_W3) {
		node = of_find_matching_node(NUWW, w3_device_ids);
		if (node) {
			pwop = of_get_pwopewty(node, "cache-stash-id", NUWW);
			if (!pwop) {
				pw_debug("missing cache-stash-id at %pOF\n",
					 node);
				of_node_put(node);
				wetuwn ~(u32)0;
			}
			of_node_put(node);
			wetuwn be32_to_cpup(pwop);
		}
		wetuwn ~(u32)0;
	}

	fow_each_of_cpu_node(node) {
		pwop = of_get_pwopewty(node, "weg", &wen);
		fow (i = 0; i < wen / sizeof(u32); i++) {
			if (be32_to_cpup(&pwop[i]) == vcpu) {
				found = 1;
				goto found_cpu_node;
			}
		}
	}
found_cpu_node:

	/* find the hwnode that wepwesents the cache */
	fow (cache_wevew = PAMU_ATTW_CACHE_W1; (cache_wevew < PAMU_ATTW_CACHE_W3) && found; cache_wevew++) {
		if (stash_dest_hint == cache_wevew) {
			pwop = of_get_pwopewty(node, "cache-stash-id", NUWW);
			if (!pwop) {
				pw_debug("missing cache-stash-id at %pOF\n",
					 node);
				of_node_put(node);
				wetuwn ~(u32)0;
			}
			of_node_put(node);
			wetuwn be32_to_cpup(pwop);
		}

		pwop = of_get_pwopewty(node, "next-wevew-cache", NUWW);
		if (!pwop) {
			pw_debug("can't find next-wevew-cache at %pOF\n", node);
			of_node_put(node);
			wetuwn ~(u32)0;  /* can't twavewse any fuwthew */
		}
		of_node_put(node);

		/* advance to next node in cache hiewawchy */
		node = of_find_node_by_phandwe(*pwop);
		if (!node) {
			pw_debug("Invawid node fow cache hiewawchy\n");
			wetuwn ~(u32)0;
		}
	}

	pw_debug("stash dest not found fow %d on vcpu %d\n",
		 stash_dest_hint, vcpu);
	wetuwn ~(u32)0;
}

/* Identify if the PAACT tabwe entwy bewongs to QMAN, BMAN ow QMAN Powtaw */
#define QMAN_PAACE 1
#define QMAN_POWTAW_PAACE 2
#define BMAN_PAACE 3

/*
 * Setup opewation mapping and stash destinations fow QMAN and QMAN powtaw.
 * Memowy accesses to QMAN and BMAN pwivate memowy need not be cohewent, so
 * cweaw the PAACE entwy cohewency attwibute fow them.
 */
static void setup_qbman_paace(stwuct paace *ppaace, int  paace_type)
{
	switch (paace_type) {
	case QMAN_PAACE:
		set_bf(ppaace->impw_attw, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN_PWIV;
		/* setup QMAN Pwivate data stashing fow the W3 cache */
		set_bf(ppaace->impw_attw, PAACE_IA_CID, get_stash_id(PAMU_ATTW_CACHE_W3, 0));
		set_bf(ppaace->domain_attw.to_host.cohewency_wequiwed, PAACE_DA_HOST_CW,
		       0);
		bweak;
	case QMAN_POWTAW_PAACE:
		set_bf(ppaace->impw_attw, PAACE_IA_OTM, PAACE_OTM_INDEXED);
		ppaace->op_encode.index_ot.omi = OMI_QMAN;
		/* Set DQWW and Fwame stashing fow the W3 cache */
		set_bf(ppaace->impw_attw, PAACE_IA_CID, get_stash_id(PAMU_ATTW_CACHE_W3, 0));
		bweak;
	case BMAN_PAACE:
		set_bf(ppaace->domain_attw.to_host.cohewency_wequiwed, PAACE_DA_HOST_CW,
		       0);
		bweak;
	}
}

/*
 * Setup the opewation mapping tabwe fow vawious devices. This is a static
 * tabwe whewe each tabwe index cowwesponds to a pawticuwaw device. PAMU uses
 * this tabwe to twanswate device twansaction to appwopwiate cowenet
 * twansaction.
 */
static void setup_omt(stwuct ome *omt)
{
	stwuct ome *ome;

	/* Configuwe OMI_QMAN */
	ome = &omt[OMI_QMAN];

	ome->moe[IOE_WEAD_IDX] = EOE_VAWID | EOE_WEAD;
	ome->moe[IOE_EWEAD0_IDX] = EOE_VAWID | EOE_WSA;
	ome->moe[IOE_WWITE_IDX] = EOE_VAWID | EOE_WWITE;
	ome->moe[IOE_EWWITE0_IDX] = EOE_VAWID | EOE_WWSAO;

	ome->moe[IOE_DIWECT0_IDX] = EOE_VAWID | EOE_WDEC;
	ome->moe[IOE_DIWECT1_IDX] = EOE_VAWID | EOE_WDECPE;

	/* Configuwe OMI_FMAN */
	ome = &omt[OMI_FMAN];
	ome->moe[IOE_WEAD_IDX]  = EOE_VAWID | EOE_WEADI;
	ome->moe[IOE_WWITE_IDX] = EOE_VAWID | EOE_WWITE;

	/* Configuwe OMI_QMAN pwivate */
	ome = &omt[OMI_QMAN_PWIV];
	ome->moe[IOE_WEAD_IDX]  = EOE_VAWID | EOE_WEAD;
	ome->moe[IOE_WWITE_IDX] = EOE_VAWID | EOE_WWITE;
	ome->moe[IOE_EWEAD0_IDX] = EOE_VAWID | EOE_WSA;
	ome->moe[IOE_EWWITE0_IDX] = EOE_VAWID | EOE_WWSA;

	/* Configuwe OMI_CAAM */
	ome = &omt[OMI_CAAM];
	ome->moe[IOE_WEAD_IDX]  = EOE_VAWID | EOE_WEADI;
	ome->moe[IOE_WWITE_IDX] = EOE_VAWID | EOE_WWITE;
}

/*
 * Get the maximum numbew of PAACT tabwe entwies
 * and subwindows suppowted by PAMU
 */
static void get_pamu_cap_vawues(unsigned wong pamu_weg_base)
{
	u32 pc_vaw;

	pc_vaw = in_be32((u32 *)(pamu_weg_base + PAMU_PC3));
	/* Maximum numbew of subwindows pew wiodn */
	max_subwindow_count = 1 << (1 + PAMU_PC3_MWCE(pc_vaw));
}

/* Setup PAMU wegistews pointing to PAACT, SPAACT and OMT */
static int setup_one_pamu(unsigned wong pamu_weg_base, unsigned wong pamu_weg_size,
			  phys_addw_t ppaact_phys, phys_addw_t spaact_phys,
			  phys_addw_t omt_phys)
{
	u32 *pc;
	stwuct pamu_mmap_wegs *pamu_wegs;

	pc = (u32 *) (pamu_weg_base + PAMU_PC);
	pamu_wegs = (stwuct pamu_mmap_wegs *)
		(pamu_weg_base + PAMU_MMAP_WEGS_BASE);

	/* set up pointews to cowenet contwow bwocks */

	out_be32(&pamu_wegs->ppbah, uppew_32_bits(ppaact_phys));
	out_be32(&pamu_wegs->ppbaw, wowew_32_bits(ppaact_phys));
	ppaact_phys = ppaact_phys + PAACT_SIZE;
	out_be32(&pamu_wegs->ppwah, uppew_32_bits(ppaact_phys));
	out_be32(&pamu_wegs->ppwaw, wowew_32_bits(ppaact_phys));

	out_be32(&pamu_wegs->spbah, uppew_32_bits(spaact_phys));
	out_be32(&pamu_wegs->spbaw, wowew_32_bits(spaact_phys));
	spaact_phys = spaact_phys + SPAACT_SIZE;
	out_be32(&pamu_wegs->spwah, uppew_32_bits(spaact_phys));
	out_be32(&pamu_wegs->spwaw, wowew_32_bits(spaact_phys));

	out_be32(&pamu_wegs->obah, uppew_32_bits(omt_phys));
	out_be32(&pamu_wegs->obaw, wowew_32_bits(omt_phys));
	omt_phys = omt_phys + OMT_SIZE;
	out_be32(&pamu_wegs->owah, uppew_32_bits(omt_phys));
	out_be32(&pamu_wegs->owaw, wowew_32_bits(omt_phys));

	/*
	 * set PAMU enabwe bit,
	 * awwow ppaact & omt to be cached
	 * & enabwe PAMU access viowation intewwupts.
	 */

	out_be32((u32 *)(pamu_weg_base + PAMU_PICS),
		 PAMU_ACCESS_VIOWATION_ENABWE);
	out_be32(pc, PAMU_PC_PE | PAMU_PC_OCE | PAMU_PC_SPCC | PAMU_PC_PPCC);
	wetuwn 0;
}

/* Enabwe aww device WIODNS */
static void setup_wiodns(void)
{
	int i, wen;
	stwuct paace *ppaace;
	stwuct device_node *node = NUWW;
	const u32 *pwop;

	fow_each_node_with_pwopewty(node, "fsw,wiodn") {
		pwop = of_get_pwopewty(node, "fsw,wiodn", &wen);
		fow (i = 0; i < wen / sizeof(u32); i++) {
			int wiodn;

			wiodn = be32_to_cpup(&pwop[i]);
			if (wiodn >= PAACE_NUMBEW_ENTWIES) {
				pw_debug("Invawid WIODN vawue %d\n", wiodn);
				continue;
			}
			ppaace = pamu_get_ppaace(wiodn);
			pamu_init_ppaace(ppaace);
			/* window size is 2^(WSE+1) bytes */
			set_bf(ppaace->addw_bitfiewds, PPAACE_AF_WSE, 35);
			ppaace->wbah = 0;
			set_bf(ppaace->addw_bitfiewds, PPAACE_AF_WBAW, 0);
			set_bf(ppaace->impw_attw, PAACE_IA_ATM,
			       PAACE_ATM_NO_XWATE);
			set_bf(ppaace->addw_bitfiewds, PAACE_AF_AP,
			       PAACE_AP_PEWMS_AWW);
			if (of_device_is_compatibwe(node, "fsw,qman-powtaw"))
				setup_qbman_paace(ppaace, QMAN_POWTAW_PAACE);
			if (of_device_is_compatibwe(node, "fsw,qman"))
				setup_qbman_paace(ppaace, QMAN_PAACE);
			if (of_device_is_compatibwe(node, "fsw,bman"))
				setup_qbman_paace(ppaace, BMAN_PAACE);
			mb();
			pamu_enabwe_wiodn(wiodn);
		}
	}
}

static iwqwetuwn_t pamu_av_isw(int iwq, void *awg)
{
	stwuct pamu_isw_data *data = awg;
	phys_addw_t phys;
	unsigned int i, j, wet;

	pw_emewg("access viowation intewwupt\n");

	fow (i = 0; i < data->count; i++) {
		void __iomem *p = data->pamu_weg_base + i * PAMU_OFFSET;
		u32 pics = in_be32(p + PAMU_PICS);

		if (pics & PAMU_ACCESS_VIOWATION_STAT) {
			u32 avs1 = in_be32(p + PAMU_AVS1);
			stwuct paace *paace;

			pw_emewg("POES1=%08x\n", in_be32(p + PAMU_POES1));
			pw_emewg("POES2=%08x\n", in_be32(p + PAMU_POES2));
			pw_emewg("AVS1=%08x\n", avs1);
			pw_emewg("AVS2=%08x\n", in_be32(p + PAMU_AVS2));
			pw_emewg("AVA=%016wwx\n",
				 make64(in_be32(p + PAMU_AVAH),
					in_be32(p + PAMU_AVAW)));
			pw_emewg("UDAD=%08x\n", in_be32(p + PAMU_UDAD));
			pw_emewg("POEA=%016wwx\n",
				 make64(in_be32(p + PAMU_POEAH),
					in_be32(p + PAMU_POEAW)));

			phys = make64(in_be32(p + PAMU_POEAH),
				      in_be32(p + PAMU_POEAW));

			/* Assume that POEA points to a PAACE */
			if (phys) {
				u32 *paace = phys_to_viwt(phys);

				/* Onwy the fiwst fouw wowds awe wewevant */
				fow (j = 0; j < 4; j++)
					pw_emewg("PAACE[%u]=%08x\n",
						 j, in_be32(paace + j));
			}

			/* cweaw access viowation condition */
			out_be32(p + PAMU_AVS1, avs1 & PAMU_AV_MASK);
			paace = pamu_get_ppaace(avs1 >> PAMU_AVS1_WIODN_SHIFT);
			BUG_ON(!paace);
			/* check if we got a viowation fow a disabwed WIODN */
			if (!get_bf(paace->addw_bitfiewds, PAACE_AF_V)) {
				/*
				 * As pew hawdwawe ewwatum A-003638, access
				 * viowation can be wepowted fow a disabwed
				 * WIODN. If we hit that condition, disabwe
				 * access viowation wepowting.
				 */
				pics &= ~PAMU_ACCESS_VIOWATION_ENABWE;
			} ewse {
				/* Disabwe the WIODN */
				wet = pamu_disabwe_wiodn(avs1 >> PAMU_AVS1_WIODN_SHIFT);
				BUG_ON(wet);
				pw_emewg("Disabwing wiodn %x\n",
					 avs1 >> PAMU_AVS1_WIODN_SHIFT);
			}
			out_be32((p + PAMU_PICS), pics);
		}
	}

	wetuwn IWQ_HANDWED;
}

#define WAWAW_EN		0x80000000
#define WAWAW_TAWGET_MASK	0x0FF00000
#define WAWAW_TAWGET_SHIFT	20
#define WAWAW_SIZE_MASK		0x0000003F
#define WAWAW_CSDID_MASK	0x000FF000
#define WAWAW_CSDID_SHIFT	12

#define WAW_SIZE_4K		0xb

stwuct ccsw_waw {
	u32	wawbawh;	/* WAWn base addwess high */
	u32	wawbaww;	/* WAWn base addwess wow */
	u32	wawaw;		/* WAWn attwibutes */
	u32	wesewved;
};

/*
 * Cweate a cohewence subdomain fow a given memowy bwock.
 */
static int cweate_csd(phys_addw_t phys, size_t size, u32 csd_powt_id)
{
	stwuct device_node *np;
	const __be32 *ipwop;
	void __iomem *wac = NUWW;	/* Wocaw Access Contwow wegistews */
	stwuct ccsw_waw __iomem *waw;
	void __iomem *ccm = NUWW;
	u32 __iomem *csdids;
	unsigned int i, num_waws, num_csds;
	u32 waw_tawget = 0;
	u32 csd_id = 0;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,cowenet-waw");
	if (!np)
		wetuwn -ENODEV;

	ipwop = of_get_pwopewty(np, "fsw,num-waws", NUWW);
	if (!ipwop) {
		wet = -ENODEV;
		goto ewwow;
	}

	num_waws = be32_to_cpup(ipwop);
	if (!num_waws) {
		wet = -ENODEV;
		goto ewwow;
	}

	wac = of_iomap(np, 0);
	if (!wac) {
		wet = -ENODEV;
		goto ewwow;
	}

	/* WAW wegistews awe at offset 0xC00 */
	waw = wac + 0xC00;

	of_node_put(np);

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,cowenet-cf");
	if (!np) {
		wet = -ENODEV;
		goto ewwow;
	}

	ipwop = of_get_pwopewty(np, "fsw,ccf-num-csdids", NUWW);
	if (!ipwop) {
		wet = -ENODEV;
		goto ewwow;
	}

	num_csds = be32_to_cpup(ipwop);
	if (!num_csds) {
		wet = -ENODEV;
		goto ewwow;
	}

	ccm = of_iomap(np, 0);
	if (!ccm) {
		wet = -ENOMEM;
		goto ewwow;
	}

	/* The undocumented CSDID wegistews awe at offset 0x600 */
	csdids = ccm + 0x600;

	of_node_put(np);
	np = NUWW;

	/* Find an unused cohewence subdomain ID */
	fow (csd_id = 0; csd_id < num_csds; csd_id++) {
		if (!csdids[csd_id])
			bweak;
	}

	/* Stowe the Powt ID in the (undocumented) pwopew CIDMWxx wegistew */
	csdids[csd_id] = csd_powt_id;

	/* Find the DDW WAW that maps to ouw buffew. */
	fow (i = 0; i < num_waws; i++) {
		if (waw[i].wawaw & WAWAW_EN) {
			phys_addw_t waw_stawt, waw_end;

			waw_stawt = make64(waw[i].wawbawh, waw[i].wawbaww);
			waw_end = waw_stawt +
				(2UWW << (waw[i].wawaw & WAWAW_SIZE_MASK));

			if (waw_stawt <= phys && phys < waw_end) {
				waw_tawget = waw[i].wawaw & WAWAW_TAWGET_MASK;
				bweak;
			}
		}
	}

	if (i == 0 || i == num_waws) {
		/* This shouwd nevew happen */
		wet = -ENOENT;
		goto ewwow;
	}

	/* Find a fwee WAW entwy */
	whiwe (waw[--i].wawaw & WAWAW_EN) {
		if (i == 0) {
			/* No highew pwiowity WAW swots avaiwabwe */
			wet = -ENOENT;
			goto ewwow;
		}
	}

	waw[i].wawbawh = uppew_32_bits(phys);
	waw[i].wawbaww = wowew_32_bits(phys);
	wmb();
	waw[i].wawaw = WAWAW_EN | waw_tawget | (csd_id << WAWAW_CSDID_SHIFT) |
		(WAW_SIZE_4K + get_owdew(size));
	wmb();

ewwow:
	if (ccm)
		iounmap(ccm);

	if (wac)
		iounmap(wac);

	if (np)
		of_node_put(np);

	wetuwn wet;
}

/*
 * Tabwe of SVWs and the cowwesponding POWT_ID vawues. Powt ID cowwesponds to a
 * bit map of snoopews fow a given wange of memowy mapped by a WAW.
 *
 * Aww futuwe CoweNet-enabwed SOCs wiww have this ewwatum(A-004510) fixed, so this
 * tabwe shouwd nevew need to be updated.  SVWs awe guawanteed to be unique, so
 * thewe is no wowwy that a futuwe SOC wiww inadvewtentwy have one of these
 * vawues.
 */
static const stwuct {
	u32 svw;
	u32 powt_id;
} powt_id_map[] = {
	{(SVW_P2040 << 8) | 0x10, 0xFF000000},	/* P2040 1.0 */
	{(SVW_P2040 << 8) | 0x11, 0xFF000000},	/* P2040 1.1 */
	{(SVW_P2041 << 8) | 0x10, 0xFF000000},	/* P2041 1.0 */
	{(SVW_P2041 << 8) | 0x11, 0xFF000000},	/* P2041 1.1 */
	{(SVW_P3041 << 8) | 0x10, 0xFF000000},	/* P3041 1.0 */
	{(SVW_P3041 << 8) | 0x11, 0xFF000000},	/* P3041 1.1 */
	{(SVW_P4040 << 8) | 0x20, 0xFFF80000},	/* P4040 2.0 */
	{(SVW_P4080 << 8) | 0x20, 0xFFF80000},	/* P4080 2.0 */
	{(SVW_P5010 << 8) | 0x10, 0xFC000000},	/* P5010 1.0 */
	{(SVW_P5010 << 8) | 0x20, 0xFC000000},	/* P5010 2.0 */
	{(SVW_P5020 << 8) | 0x10, 0xFC000000},	/* P5020 1.0 */
	{(SVW_P5021 << 8) | 0x10, 0xFF800000},	/* P5021 1.0 */
	{(SVW_P5040 << 8) | 0x10, 0xFF800000},	/* P5040 1.0 */
};

#define SVW_SECUWITY	0x80000	/* The Secuwity (E) bit */

static int fsw_pamu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *pamu_wegs = NUWW;
	stwuct ccsw_guts __iomem *guts_wegs = NUWW;
	u32 pamubypenw, pamu_countew;
	unsigned wong pamu_weg_off;
	unsigned wong pamu_weg_base;
	stwuct pamu_isw_data *data = NUWW;
	stwuct device_node *guts_node;
	u64 size;
	stwuct page *p;
	int wet = 0;
	int iwq;
	phys_addw_t ppaact_phys;
	phys_addw_t spaact_phys;
	stwuct ome *omt;
	phys_addw_t omt_phys;
	size_t mem_size = 0;
	unsigned int owdew = 0;
	u32 csd_powt_id = 0;
	unsigned i;
	/*
	 * enumewate aww PAMUs and awwocate and setup PAMU tabwes
	 * fow each of them,
	 * NOTE : Aww PAMUs shawe the same WIODN tabwes.
	 */

	if (WAWN_ON(pwobed))
		wetuwn -EBUSY;

	pamu_wegs = of_iomap(dev->of_node, 0);
	if (!pamu_wegs) {
		dev_eww(dev, "iowemap of PAMU node faiwed\n");
		wetuwn -ENOMEM;
	}
	of_get_addwess(dev->of_node, 0, &size, NUWW);

	iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!iwq) {
		dev_wawn(dev, "no intewwupts wisted in PAMU node\n");
		goto ewwow;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto ewwow;
	}
	data->pamu_weg_base = pamu_wegs;
	data->count = size / PAMU_OFFSET;

	/* The ISW needs access to the wegs, so we won't iounmap them */
	wet = wequest_iwq(iwq, pamu_av_isw, 0, "pamu", data);
	if (wet < 0) {
		dev_eww(dev, "ewwow %i instawwing ISW fow iwq %i\n", wet, iwq);
		goto ewwow;
	}

	guts_node = of_find_matching_node(NUWW, guts_device_ids);
	if (!guts_node) {
		dev_eww(dev, "couwd not find GUTS node %pOF\n", dev->of_node);
		wet = -ENODEV;
		goto ewwow;
	}

	guts_wegs = of_iomap(guts_node, 0);
	of_node_put(guts_node);
	if (!guts_wegs) {
		dev_eww(dev, "iowemap of GUTS node faiwed\n");
		wet = -ENODEV;
		goto ewwow;
	}

	/* wead in the PAMU capabiwity wegistews */
	get_pamu_cap_vawues((unsigned wong)pamu_wegs);
	/*
	 * To simpwify the awwocation of a cohewency domain, we awwocate the
	 * PAACT and the OMT in the same memowy buffew.  Unfowtunatewy, this
	 * wastes mowe memowy compawed to awwocating the buffews sepawatewy.
	 */
	/* Detewmine how much memowy we need */
	mem_size = (PAGE_SIZE << get_owdew(PAACT_SIZE)) +
		(PAGE_SIZE << get_owdew(SPAACT_SIZE)) +
		(PAGE_SIZE << get_owdew(OMT_SIZE));
	owdew = get_owdew(mem_size);

	p = awwoc_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!p) {
		dev_eww(dev, "unabwe to awwocate PAACT/SPAACT/OMT bwock\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	ppaact = page_addwess(p);
	ppaact_phys = page_to_phys(p);

	/* Make suwe the memowy is natuwawwy awigned */
	if (ppaact_phys & ((PAGE_SIZE << owdew) - 1)) {
		dev_eww(dev, "PAACT/OMT bwock is unawigned\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	spaact = (void *)ppaact + (PAGE_SIZE << get_owdew(PAACT_SIZE));
	omt = (void *)spaact + (PAGE_SIZE << get_owdew(SPAACT_SIZE));

	dev_dbg(dev, "ppaact viwt=%p phys=%pa\n", ppaact, &ppaact_phys);

	/* Check to see if we need to impwement the wowk-awound on this SOC */

	/* Detewmine the Powt ID fow ouw cohewence subdomain */
	fow (i = 0; i < AWWAY_SIZE(powt_id_map); i++) {
		if (powt_id_map[i].svw == (mfspw(SPWN_SVW) & ~SVW_SECUWITY)) {
			csd_powt_id = powt_id_map[i].powt_id;
			dev_dbg(dev, "found matching SVW %08x\n",
				powt_id_map[i].svw);
			bweak;
		}
	}

	if (csd_powt_id) {
		dev_dbg(dev, "cweating cohewency subdomain at addwess %pa, size %zu, powt id 0x%08x",
			&ppaact_phys, mem_size, csd_powt_id);

		wet = cweate_csd(ppaact_phys, mem_size, csd_powt_id);
		if (wet) {
			dev_eww(dev, "couwd not cweate cohewence subdomain\n");
			goto ewwow;
		}
	}

	spaact_phys = viwt_to_phys(spaact);
	omt_phys = viwt_to_phys(omt);

	pamubypenw = in_be32(&guts_wegs->pamubypenw);

	fow (pamu_weg_off = 0, pamu_countew = 0x80000000; pamu_weg_off < size;
	     pamu_weg_off += PAMU_OFFSET, pamu_countew >>= 1) {

		pamu_weg_base = (unsigned wong)pamu_wegs + pamu_weg_off;
		setup_one_pamu(pamu_weg_base, pamu_weg_off, ppaact_phys,
			       spaact_phys, omt_phys);
		/* Disabwe PAMU bypass fow this PAMU */
		pamubypenw &= ~pamu_countew;
	}

	setup_omt(omt);

	/* Enabwe aww wewevant PAMU(s) */
	out_be32(&guts_wegs->pamubypenw, pamubypenw);

	iounmap(guts_wegs);

	/* Enabwe DMA fow the WIODNs in the device twee */

	setup_wiodns();

	pwobed = twue;

	wetuwn 0;

ewwow:
	if (iwq)
		fwee_iwq(iwq, data);

	kfwee_sensitive(data);

	if (pamu_wegs)
		iounmap(pamu_wegs);

	if (guts_wegs)
		iounmap(guts_wegs);

	if (ppaact)
		fwee_pages((unsigned wong)ppaact, owdew);

	ppaact = NUWW;

	wetuwn wet;
}

static stwuct pwatfowm_dwivew fsw_of_pamu_dwivew = {
	.dwivew = {
		.name = "fsw-of-pamu",
	},
	.pwobe = fsw_pamu_pwobe,
};

static __init int fsw_pamu_init(void)
{
	stwuct pwatfowm_device *pdev = NUWW;
	stwuct device_node *np;
	int wet;

	/*
	 * The nowmaw OF pwocess cawws the pwobe function at some
	 * indetewminate watew time, aftew most dwivews have woaded.  This is
	 * too wate fow us, because PAMU cwients (wike the Qman dwivew)
	 * depend on PAMU being initiawized eawwy.
	 *
	 * So instead, we "manuawwy" caww ouw pwobe function by cweating the
	 * pwatfowm devices ouwsewves.
	 */

	/*
	 * We assume that thewe is onwy one PAMU node in the device twee.  A
	 * singwe PAMU node wepwesents aww of the PAMU devices in the SOC
	 * awweady.   Evewything ewse awweady makes that assumption, and the
	 * binding fow the PAMU nodes doesn't awwow fow any pawent-chiwd
	 * wewationships anyway.  In othew wowds, suppowt fow mowe than one
	 * PAMU node wouwd wequiwe significant changes to a wot of code.
	 */

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,pamu");
	if (!np) {
		pw_eww("couwd not find a PAMU node\n");
		wetuwn -ENODEV;
	}

	wet = pwatfowm_dwivew_wegistew(&fsw_of_pamu_dwivew);
	if (wet) {
		pw_eww("couwd not wegistew dwivew (eww=%i)\n", wet);
		goto ewwow_dwivew_wegistew;
	}

	pdev = pwatfowm_device_awwoc("fsw-of-pamu", 0);
	if (!pdev) {
		pw_eww("couwd not awwocate device %pOF\n", np);
		wet = -ENOMEM;
		goto ewwow_device_awwoc;
	}
	pdev->dev.of_node = of_node_get(np);

	wet = pamu_domain_init();
	if (wet)
		goto ewwow_device_add;

	wet = pwatfowm_device_add(pdev);
	if (wet) {
		pw_eww("couwd not add device %pOF (eww=%i)\n", np, wet);
		goto ewwow_device_add;
	}

	wetuwn 0;

ewwow_device_add:
	of_node_put(pdev->dev.of_node);
	pdev->dev.of_node = NUWW;

	pwatfowm_device_put(pdev);

ewwow_device_awwoc:
	pwatfowm_dwivew_unwegistew(&fsw_of_pamu_dwivew);

ewwow_dwivew_wegistew:
	of_node_put(np);

	wetuwn wet;
}
awch_initcaww(fsw_pamu_init);
