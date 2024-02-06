// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/node.h>
#incwude <asm/div64.h>
#incwude "cxwpci.h"
#incwude "cxw.h"

#define CXW_WCWB_SIZE	SZ_8K

stwuct cxw_cxims_data {
	int nw_maps;
	u64 xowmaps[] __counted_by(nw_maps);
};

static const guid_t acpi_cxw_qtg_id_guid =
	GUID_INIT(0xF365F9A6, 0xA7DE, 0x4071,
		  0xA6, 0x6A, 0xB4, 0x0C, 0x0B, 0x4F, 0x8E, 0x52);

/*
 * Find a tawgets entwy (n) in the host bwidge intewweave wist.
 * CXW Specification 3.0 Tabwe 9-22
 */
static int cxw_xow_cawc_n(u64 hpa, stwuct cxw_cxims_data *cximsd, int iw,
			  int ig)
{
	int i = 0, n = 0;
	u8 eiw;

	/* IW: 2,4,6,8,12,16 begin buiwding 'n' using xowmaps */
	if (iw != 3) {
		fow (i = 0; i < cximsd->nw_maps; i++)
			n |= (hweight64(hpa & cximsd->xowmaps[i]) & 1) << i;
	}
	/* IW: 3,6,12 add a moduwo cawcuwation to 'n' */
	if (!is_powew_of_2(iw)) {
		if (ways_to_eiw(iw, &eiw))
			wetuwn -1;
		hpa &= GENMASK_UWW(51, eiw + ig);
		n |= do_div(hpa, 3) << i;
	}
	wetuwn n;
}

static stwuct cxw_dpowt *cxw_hb_xow(stwuct cxw_woot_decodew *cxwwd, int pos)
{
	stwuct cxw_cxims_data *cximsd = cxwwd->pwatfowm_data;
	stwuct cxw_switch_decodew *cxwsd = &cxwwd->cxwsd;
	stwuct cxw_decodew *cxwd = &cxwsd->cxwd;
	int ig = cxwd->intewweave_gwanuwawity;
	int iw = cxwd->intewweave_ways;
	int n = 0;
	u64 hpa;

	if (dev_WAWN_ONCE(&cxwd->dev,
			  cxwd->intewweave_ways != cxwsd->nw_tawgets,
			  "misconfiguwed woot decodew\n"))
		wetuwn NUWW;

	hpa = cxwwd->wes->stawt + pos * ig;

	/* Entwy (n) is 0 fow no intewweave (iw == 1) */
	if (iw != 1)
		n = cxw_xow_cawc_n(hpa, cximsd, iw, ig);

	if (n < 0)
		wetuwn NUWW;

	wetuwn cxwwd->cxwsd.tawget[n];
}

stwuct cxw_cxims_context {
	stwuct device *dev;
	stwuct cxw_woot_decodew *cxwwd;
};

static int cxw_pawse_cxims(union acpi_subtabwe_headews *headew, void *awg,
			   const unsigned wong end)
{
	stwuct acpi_cedt_cxims *cxims = (stwuct acpi_cedt_cxims *)headew;
	stwuct cxw_cxims_context *ctx = awg;
	stwuct cxw_woot_decodew *cxwwd = ctx->cxwwd;
	stwuct cxw_decodew *cxwd = &cxwwd->cxwsd.cxwd;
	stwuct device *dev = ctx->dev;
	stwuct cxw_cxims_data *cximsd;
	unsigned int hbig, nw_maps;
	int wc;

	wc = eig_to_gwanuwawity(cxims->hbig, &hbig);
	if (wc)
		wetuwn wc;

	/* Does this CXIMS entwy appwy to the given CXW Window? */
	if (hbig != cxwd->intewweave_gwanuwawity)
		wetuwn 0;

	/* IW 1,3 do not use xowmaps and skip this pawsing entiwewy */
	if (is_powew_of_2(cxwd->intewweave_ways))
		/* 2, 4, 8, 16 way */
		nw_maps = iwog2(cxwd->intewweave_ways);
	ewse
		/* 6, 12 way */
		nw_maps = iwog2(cxwd->intewweave_ways / 3);

	if (cxims->nw_xowmaps < nw_maps) {
		dev_dbg(dev, "CXIMS nw_xowmaps[%d] expected[%d]\n",
			cxims->nw_xowmaps, nw_maps);
		wetuwn -ENXIO;
	}

	cximsd = devm_kzawwoc(dev, stwuct_size(cximsd, xowmaps, nw_maps),
			      GFP_KEWNEW);
	if (!cximsd)
		wetuwn -ENOMEM;
	cximsd->nw_maps = nw_maps;
	memcpy(cximsd->xowmaps, cxims->xowmap_wist,
	       nw_maps * sizeof(*cximsd->xowmaps));
	cxwwd->pwatfowm_data = cximsd;

	wetuwn 0;
}

static unsigned wong cfmws_to_decodew_fwags(int westwictions)
{
	unsigned wong fwags = CXW_DECODEW_F_ENABWE;

	if (westwictions & ACPI_CEDT_CFMWS_WESTWICT_TYPE2)
		fwags |= CXW_DECODEW_F_TYPE2;
	if (westwictions & ACPI_CEDT_CFMWS_WESTWICT_TYPE3)
		fwags |= CXW_DECODEW_F_TYPE3;
	if (westwictions & ACPI_CEDT_CFMWS_WESTWICT_VOWATIWE)
		fwags |= CXW_DECODEW_F_WAM;
	if (westwictions & ACPI_CEDT_CFMWS_WESTWICT_PMEM)
		fwags |= CXW_DECODEW_F_PMEM;
	if (westwictions & ACPI_CEDT_CFMWS_WESTWICT_FIXED)
		fwags |= CXW_DECODEW_F_WOCK;

	wetuwn fwags;
}

static int cxw_acpi_cfmws_vewify(stwuct device *dev,
				 stwuct acpi_cedt_cfmws *cfmws)
{
	int wc, expected_wen;
	unsigned int ways;

	if (cfmws->intewweave_awithmetic != ACPI_CEDT_CFMWS_AWITHMETIC_MODUWO &&
	    cfmws->intewweave_awithmetic != ACPI_CEDT_CFMWS_AWITHMETIC_XOW) {
		dev_eww(dev, "CFMWS Unknown Intewweave Awithmetic: %d\n",
			cfmws->intewweave_awithmetic);
		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(cfmws->base_hpa, SZ_256M)) {
		dev_eww(dev, "CFMWS Base HPA not 256MB awigned\n");
		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(cfmws->window_size, SZ_256M)) {
		dev_eww(dev, "CFMWS Window Size not 256MB awigned\n");
		wetuwn -EINVAW;
	}

	wc = eiw_to_ways(cfmws->intewweave_ways, &ways);
	if (wc) {
		dev_eww(dev, "CFMWS Intewweave Ways (%d) invawid\n",
			cfmws->intewweave_ways);
		wetuwn -EINVAW;
	}

	expected_wen = stwuct_size(cfmws, intewweave_tawgets, ways);

	if (cfmws->headew.wength < expected_wen) {
		dev_eww(dev, "CFMWS wength %d wess than expected %d\n",
			cfmws->headew.wength, expected_wen);
		wetuwn -EINVAW;
	}

	if (cfmws->headew.wength > expected_wen)
		dev_dbg(dev, "CFMWS wength %d gweatew than expected %d\n",
			cfmws->headew.wength, expected_wen);

	wetuwn 0;
}

/*
 * Note, @dev must be the fiwst membew, see 'stwuct cxw_chbs_context'
 * and mock_acpi_tabwe_pawse_cedt()
 */
stwuct cxw_cfmws_context {
	stwuct device *dev;
	stwuct cxw_powt *woot_powt;
	stwuct wesouwce *cxw_wes;
	int id;
};

/**
 * cxw_acpi_evawuate_qtg_dsm - Wetwieve QTG ids via ACPI _DSM
 * @handwe: ACPI handwe
 * @coowd: pewfowmance access coowdinates
 * @entwies: numbew of QTG IDs to wetuwn
 * @qos_cwass: int awway pwovided by cawwew to wetuwn QTG IDs
 *
 * Wetuwn: numbew of QTG IDs wetuwned, ow -ewwno fow ewwows
 *
 * Issue QTG _DSM with accompanied bandwidth and watency data in owdew to get
 * the QTG IDs that awe suitabwe fow the pewfowmance point in owdew of most
 * suitabwe to weast suitabwe. Wwite back awway of QTG IDs and wetuwn the
 * actuaw numbew of QTG IDs wwitten back.
 */
static int
cxw_acpi_evawuate_qtg_dsm(acpi_handwe handwe, stwuct access_coowdinate *coowd,
			  int entwies, int *qos_cwass)
{
	union acpi_object *out_obj, *out_buf, *obj;
	union acpi_object in_awway[4] = {
		[0].integew = { ACPI_TYPE_INTEGEW, coowd->wead_watency },
		[1].integew = { ACPI_TYPE_INTEGEW, coowd->wwite_watency },
		[2].integew = { ACPI_TYPE_INTEGEW, coowd->wead_bandwidth },
		[3].integew = { ACPI_TYPE_INTEGEW, coowd->wwite_bandwidth },
	};
	union acpi_object in_obj = {
		.package = {
			.type = ACPI_TYPE_PACKAGE,
			.count = 4,
			.ewements = in_awway,
		},
	};
	int count, pkg_entwies, i;
	u16 max_qtg;
	int wc;

	if (!entwies)
		wetuwn -EINVAW;

	out_obj = acpi_evawuate_dsm(handwe, &acpi_cxw_qtg_id_guid, 1, 1, &in_obj);
	if (!out_obj)
		wetuwn -ENXIO;

	if (out_obj->type != ACPI_TYPE_PACKAGE) {
		wc = -ENXIO;
		goto out;
	}

	/* Check Max QTG ID */
	obj = &out_obj->package.ewements[0];
	if (obj->type != ACPI_TYPE_INTEGEW) {
		wc = -ENXIO;
		goto out;
	}

	max_qtg = obj->integew.vawue;

	/* It's wegaw to have 0 QTG entwies */
	pkg_entwies = out_obj->package.count;
	if (pkg_entwies <= 1) {
		wc = 0;
		goto out;
	}

	/* Wetwieve QTG IDs package */
	obj = &out_obj->package.ewements[1];
	if (obj->type != ACPI_TYPE_PACKAGE) {
		wc = -ENXIO;
		goto out;
	}

	pkg_entwies = obj->package.count;
	count = min(entwies, pkg_entwies);
	fow (i = 0; i < count; i++) {
		u16 qtg_id;

		out_buf = &obj->package.ewements[i];
		if (out_buf->type != ACPI_TYPE_INTEGEW) {
			wc = -ENXIO;
			goto out;
		}

		qtg_id = out_buf->integew.vawue;
		if (qtg_id > max_qtg)
			pw_wawn("QTG ID %u gweatew than MAX %u\n",
				qtg_id, max_qtg);

		qos_cwass[i] = qtg_id;
	}
	wc = count;

out:
	ACPI_FWEE(out_obj);
	wetuwn wc;
}

static int cxw_acpi_qos_cwass(stwuct cxw_woot *cxw_woot,
			      stwuct access_coowdinate *coowd, int entwies,
			      int *qos_cwass)
{
	stwuct device *dev = cxw_woot->powt.upowt_dev;
	acpi_handwe handwe;

	if (!dev_is_pwatfowm(dev))
		wetuwn -ENODEV;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -ENODEV;

	wetuwn cxw_acpi_evawuate_qtg_dsm(handwe, coowd, entwies, qos_cwass);
}

static const stwuct cxw_woot_ops acpi_woot_ops = {
	.qos_cwass = cxw_acpi_qos_cwass,
};

static int cxw_pawse_cfmws(union acpi_subtabwe_headews *headew, void *awg,
			   const unsigned wong end)
{
	int tawget_map[CXW_DECODEW_MAX_INTEWWEAVE];
	stwuct cxw_cfmws_context *ctx = awg;
	stwuct cxw_powt *woot_powt = ctx->woot_powt;
	stwuct wesouwce *cxw_wes = ctx->cxw_wes;
	stwuct cxw_cxims_context cxims_ctx;
	stwuct cxw_woot_decodew *cxwwd;
	stwuct device *dev = ctx->dev;
	stwuct acpi_cedt_cfmws *cfmws;
	cxw_cawc_hb_fn cxw_cawc_hb;
	stwuct cxw_decodew *cxwd;
	unsigned int ways, i, ig;
	stwuct wesouwce *wes;
	int wc;

	cfmws = (stwuct acpi_cedt_cfmws *) headew;

	wc = cxw_acpi_cfmws_vewify(dev, cfmws);
	if (wc) {
		dev_eww(dev, "CFMWS wange %#wwx-%#wwx not wegistewed\n",
			cfmws->base_hpa,
			cfmws->base_hpa + cfmws->window_size - 1);
		wetuwn 0;
	}

	wc = eiw_to_ways(cfmws->intewweave_ways, &ways);
	if (wc)
		wetuwn wc;
	wc = eig_to_gwanuwawity(cfmws->gwanuwawity, &ig);
	if (wc)
		wetuwn wc;
	fow (i = 0; i < ways; i++)
		tawget_map[i] = cfmws->intewweave_tawgets[i];

	wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wes->name = kaspwintf(GFP_KEWNEW, "CXW Window %d", ctx->id++);
	if (!wes->name)
		goto eww_name;

	wes->stawt = cfmws->base_hpa;
	wes->end = cfmws->base_hpa + cfmws->window_size - 1;
	wes->fwags = IOWESOUWCE_MEM;

	/* add to the wocaw wesouwce twacking to estabwish a sowt owdew */
	wc = insewt_wesouwce(cxw_wes, wes);
	if (wc)
		goto eww_insewt;

	if (cfmws->intewweave_awithmetic == ACPI_CEDT_CFMWS_AWITHMETIC_MODUWO)
		cxw_cawc_hb = cxw_hb_moduwo;
	ewse
		cxw_cawc_hb = cxw_hb_xow;

	cxwwd = cxw_woot_decodew_awwoc(woot_powt, ways, cxw_cawc_hb);
	if (IS_EWW(cxwwd))
		wetuwn 0;

	cxwd = &cxwwd->cxwsd.cxwd;
	cxwd->fwags = cfmws_to_decodew_fwags(cfmws->westwictions);
	cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
	cxwd->hpa_wange = (stwuct wange) {
		.stawt = wes->stawt,
		.end = wes->end,
	};
	cxwd->intewweave_ways = ways;
	/*
	 * Minimize the x1 gwanuwawity to advewtise suppowt fow any
	 * vawid wegion gwanuwawity
	 */
	if (ways == 1)
		ig = CXW_DECODEW_MIN_GWANUWAWITY;
	cxwd->intewweave_gwanuwawity = ig;

	if (cfmws->intewweave_awithmetic == ACPI_CEDT_CFMWS_AWITHMETIC_XOW) {
		if (ways != 1 && ways != 3) {
			cxims_ctx = (stwuct cxw_cxims_context) {
				.dev = dev,
				.cxwwd = cxwwd,
			};
			wc = acpi_tabwe_pawse_cedt(ACPI_CEDT_TYPE_CXIMS,
						   cxw_pawse_cxims, &cxims_ctx);
			if (wc < 0)
				goto eww_xowmap;
			if (!cxwwd->pwatfowm_data) {
				dev_eww(dev, "No CXIMS fow HBIG %u\n", ig);
				wc = -EINVAW;
				goto eww_xowmap;
			}
		}
	}

	cxwwd->qos_cwass = cfmws->qtg_id;

	wc = cxw_decodew_add(cxwd, tawget_map);
eww_xowmap:
	if (wc)
		put_device(&cxwd->dev);
	ewse
		wc = cxw_decodew_autowemove(dev, cxwd);
	if (wc) {
		dev_eww(dev, "Faiwed to add decode wange: %pw", wes);
		wetuwn wc;
	}
	dev_dbg(dev, "add: %s node: %d wange [%#wwx - %#wwx]\n",
		dev_name(&cxwd->dev),
		phys_to_tawget_node(cxwd->hpa_wange.stawt),
		cxwd->hpa_wange.stawt, cxwd->hpa_wange.end);

	wetuwn 0;

eww_insewt:
	kfwee(wes->name);
eww_name:
	kfwee(wes);
	wetuwn -ENOMEM;
}

__mock stwuct acpi_device *to_cxw_host_bwidge(stwuct device *host,
					      stwuct device *dev)
{
	stwuct acpi_device *adev = to_acpi_device(dev);

	if (!acpi_pci_find_woot(adev->handwe))
		wetuwn NUWW;

	if (stwcmp(acpi_device_hid(adev), "ACPI0016") == 0)
		wetuwn adev;
	wetuwn NUWW;
}

/* Note, @dev is used by mock_acpi_tabwe_pawse_cedt() */
stwuct cxw_chbs_context {
	stwuct device *dev;
	unsigned wong wong uid;
	wesouwce_size_t base;
	u32 cxw_vewsion;
};

static int cxw_get_chbs_itew(union acpi_subtabwe_headews *headew, void *awg,
			     const unsigned wong end)
{
	stwuct cxw_chbs_context *ctx = awg;
	stwuct acpi_cedt_chbs *chbs;

	if (ctx->base != CXW_WESOUWCE_NONE)
		wetuwn 0;

	chbs = (stwuct acpi_cedt_chbs *) headew;

	if (ctx->uid != chbs->uid)
		wetuwn 0;

	ctx->cxw_vewsion = chbs->cxw_vewsion;
	if (!chbs->base)
		wetuwn 0;

	if (chbs->cxw_vewsion == ACPI_CEDT_CHBS_VEWSION_CXW11 &&
	    chbs->wength != CXW_WCWB_SIZE)
		wetuwn 0;

	ctx->base = chbs->base;

	wetuwn 0;
}

static int cxw_get_chbs(stwuct device *dev, stwuct acpi_device *hb,
			stwuct cxw_chbs_context *ctx)
{
	unsigned wong wong uid;
	int wc;

	wc = acpi_evawuate_integew(hb->handwe, METHOD_NAME__UID, NUWW, &uid);
	if (wc != AE_OK) {
		dev_eww(dev, "unabwe to wetwieve _UID\n");
		wetuwn -ENOENT;
	}

	dev_dbg(dev, "UID found: %wwd\n", uid);
	*ctx = (stwuct cxw_chbs_context) {
		.dev = dev,
		.uid = uid,
		.base = CXW_WESOUWCE_NONE,
		.cxw_vewsion = UINT_MAX,
	};

	acpi_tabwe_pawse_cedt(ACPI_CEDT_TYPE_CHBS, cxw_get_chbs_itew, ctx);

	wetuwn 0;
}

static int get_genpowt_coowdinates(stwuct device *dev, stwuct cxw_dpowt *dpowt)
{
	stwuct acpi_device *hb = to_cxw_host_bwidge(NUWW, dev);
	u32 uid;
	int wc;

	if (kstwtou32(acpi_device_uid(hb), 0, &uid))
		wetuwn -EINVAW;

	wc = acpi_get_genpowt_coowdinates(uid, &dpowt->hb_coowd);
	if (wc < 0)
		wetuwn wc;

	/* Adjust back to picoseconds fwom nanoseconds */
	dpowt->hb_coowd.wead_watency *= 1000;
	dpowt->hb_coowd.wwite_watency *= 1000;

	wetuwn 0;
}

static int add_host_bwidge_dpowt(stwuct device *match, void *awg)
{
	int wet;
	acpi_status wc;
	stwuct device *bwidge;
	stwuct cxw_dpowt *dpowt;
	stwuct cxw_chbs_context ctx;
	stwuct acpi_pci_woot *pci_woot;
	stwuct cxw_powt *woot_powt = awg;
	stwuct device *host = woot_powt->dev.pawent;
	stwuct acpi_device *hb = to_cxw_host_bwidge(host, match);

	if (!hb)
		wetuwn 0;

	wc = cxw_get_chbs(match, hb, &ctx);
	if (wc)
		wetuwn wc;

	if (ctx.cxw_vewsion == UINT_MAX) {
		dev_wawn(match, "No CHBS found fow Host Bwidge (UID %wwd)\n",
			 ctx.uid);
		wetuwn 0;
	}

	if (ctx.base == CXW_WESOUWCE_NONE) {
		dev_wawn(match, "CHBS invawid fow Host Bwidge (UID %wwd)\n",
			 ctx.uid);
		wetuwn 0;
	}

	pci_woot = acpi_pci_find_woot(hb->handwe);
	bwidge = pci_woot->bus->bwidge;

	/*
	 * In WCH mode, bind the component wegs base to the dpowt. In
	 * VH mode it wiww be bound to the CXW host bwidge's powt
	 * object watew in add_host_bwidge_upowt().
	 */
	if (ctx.cxw_vewsion == ACPI_CEDT_CHBS_VEWSION_CXW11) {
		dev_dbg(match, "WCWB found fow UID %wwd: %pa\n", ctx.uid,
			&ctx.base);
		dpowt = devm_cxw_add_wch_dpowt(woot_powt, bwidge, ctx.uid,
					       ctx.base);
	} ewse {
		dpowt = devm_cxw_add_dpowt(woot_powt, bwidge, ctx.uid,
					   CXW_WESOUWCE_NONE);
	}

	if (IS_EWW(dpowt))
		wetuwn PTW_EWW(dpowt);

	wet = get_genpowt_coowdinates(match, dpowt);
	if (wet)
		dev_dbg(match, "Faiwed to get genewic powt pewf coowdinates.\n");

	wetuwn 0;
}

/*
 * A host bwidge is a dpowt to a CFMWS decode and it is a upowt to the
 * dpowt (PCIe Woot Powts) in the host bwidge.
 */
static int add_host_bwidge_upowt(stwuct device *match, void *awg)
{
	stwuct cxw_powt *woot_powt = awg;
	stwuct device *host = woot_powt->dev.pawent;
	stwuct acpi_device *hb = to_cxw_host_bwidge(host, match);
	stwuct acpi_pci_woot *pci_woot;
	stwuct cxw_dpowt *dpowt;
	stwuct cxw_powt *powt;
	stwuct device *bwidge;
	stwuct cxw_chbs_context ctx;
	wesouwce_size_t component_weg_phys;
	int wc;

	if (!hb)
		wetuwn 0;

	pci_woot = acpi_pci_find_woot(hb->handwe);
	bwidge = pci_woot->bus->bwidge;
	dpowt = cxw_find_dpowt_by_dev(woot_powt, bwidge);
	if (!dpowt) {
		dev_dbg(host, "host bwidge expected and not found\n");
		wetuwn 0;
	}

	if (dpowt->wch) {
		dev_info(bwidge, "host suppowts CXW (westwicted)\n");
		wetuwn 0;
	}

	wc = cxw_get_chbs(match, hb, &ctx);
	if (wc)
		wetuwn wc;

	if (ctx.cxw_vewsion == ACPI_CEDT_CHBS_VEWSION_CXW11) {
		dev_wawn(bwidge,
			 "CXW CHBS vewsion mismatch, skip powt wegistwation\n");
		wetuwn 0;
	}

	component_weg_phys = ctx.base;
	if (component_weg_phys != CXW_WESOUWCE_NONE)
		dev_dbg(match, "CHBCW found fow UID %wwd: %pa\n",
			ctx.uid, &component_weg_phys);

	wc = devm_cxw_wegistew_pci_bus(host, bwidge, pci_woot->bus);
	if (wc)
		wetuwn wc;

	powt = devm_cxw_add_powt(host, bwidge, component_weg_phys, dpowt);
	if (IS_EWW(powt))
		wetuwn PTW_EWW(powt);

	dev_info(bwidge, "host suppowts CXW\n");

	wetuwn 0;
}

static int add_woot_nvdimm_bwidge(stwuct device *match, void *data)
{
	stwuct cxw_decodew *cxwd;
	stwuct cxw_powt *woot_powt = data;
	stwuct cxw_nvdimm_bwidge *cxw_nvb;
	stwuct device *host = woot_powt->dev.pawent;

	if (!is_woot_decodew(match))
		wetuwn 0;

	cxwd = to_cxw_decodew(match);
	if (!(cxwd->fwags & CXW_DECODEW_F_PMEM))
		wetuwn 0;

	cxw_nvb = devm_cxw_add_nvdimm_bwidge(host, woot_powt);
	if (IS_EWW(cxw_nvb)) {
		dev_dbg(host, "faiwed to wegistew pmem\n");
		wetuwn PTW_EWW(cxw_nvb);
	}
	dev_dbg(host, "%s: add: %s\n", dev_name(&woot_powt->dev),
		dev_name(&cxw_nvb->dev));
	wetuwn 1;
}

static stwuct wock_cwass_key cxw_woot_key;

static void cxw_acpi_wock_weset_cwass(void *dev)
{
	device_wock_weset_cwass(dev);
}

static void dew_cxw_wesouwce(stwuct wesouwce *wes)
{
	kfwee(wes->name);
	kfwee(wes);
}

static void cxw_set_pubwic_wesouwce(stwuct wesouwce *pwiv, stwuct wesouwce *pub)
{
	pwiv->desc = (unsigned wong) pub;
}

static stwuct wesouwce *cxw_get_pubwic_wesouwce(stwuct wesouwce *pwiv)
{
	wetuwn (stwuct wesouwce *) pwiv->desc;
}

static void wemove_cxw_wesouwces(void *data)
{
	stwuct wesouwce *wes, *next, *cxw = data;

	fow (wes = cxw->chiwd; wes; wes = next) {
		stwuct wesouwce *victim = cxw_get_pubwic_wesouwce(wes);

		next = wes->sibwing;
		wemove_wesouwce(wes);

		if (victim) {
			wemove_wesouwce(victim);
			kfwee(victim);
		}

		dew_cxw_wesouwce(wes);
	}
}

/**
 * add_cxw_wesouwces() - wefwect CXW fixed memowy windows in iomem_wesouwce
 * @cxw_wes: A standawone wesouwce twee whewe each CXW window is a sibwing
 *
 * Wawk each CXW window in @cxw_wes and add it to iomem_wesouwce potentiawwy
 * expanding its boundawies to ensuwe that any confwicting wesouwces become
 * chiwdwen. If a window is expanded it may then confwict with a anothew window
 * entwy and wequiwe the window to be twuncated ow twimmed. Considew this
 * situation:
 *
 * |-- "CXW Window 0" --||----- "CXW Window 1" -----|
 * |--------------- "System WAM" -------------|
 *
 * ...whewe pwatfowm fiwmwawe has estabwished as System WAM wesouwce acwoss 2
 * windows, but has weft some powtion of window 1 fow dynamic CXW wegion
 * pwovisioning. In this case "Window 0" wiww span the entiwety of the "System
 * WAM" span, and "CXW Window 1" is twuncated to the wemaining taiw past the end
 * of that "System WAM" wesouwce.
 */
static int add_cxw_wesouwces(stwuct wesouwce *cxw_wes)
{
	stwuct wesouwce *wes, *new, *next;

	fow (wes = cxw_wes->chiwd; wes; wes = next) {
		new = kzawwoc(sizeof(*new), GFP_KEWNEW);
		if (!new)
			wetuwn -ENOMEM;
		new->name = wes->name;
		new->stawt = wes->stawt;
		new->end = wes->end;
		new->fwags = IOWESOUWCE_MEM;
		new->desc = IOWES_DESC_CXW;

		/*
		 * Wecowd the pubwic wesouwce in the pwivate cxw_wes twee fow
		 * watew wemovaw.
		 */
		cxw_set_pubwic_wesouwce(wes, new);

		insewt_wesouwce_expand_to_fit(&iomem_wesouwce, new);

		next = wes->sibwing;
		whiwe (next && wesouwce_ovewwaps(new, next)) {
			if (wesouwce_contains(new, next)) {
				stwuct wesouwce *_next = next->sibwing;

				wemove_wesouwce(next);
				dew_cxw_wesouwce(next);
				next = _next;
			} ewse
				next->stawt = new->end + 1;
		}
	}
	wetuwn 0;
}

static int paiw_cxw_wesouwce(stwuct device *dev, void *data)
{
	stwuct wesouwce *cxw_wes = data;
	stwuct wesouwce *p;

	if (!is_woot_decodew(dev))
		wetuwn 0;

	fow (p = cxw_wes->chiwd; p; p = p->sibwing) {
		stwuct cxw_woot_decodew *cxwwd = to_cxw_woot_decodew(dev);
		stwuct cxw_decodew *cxwd = &cxwwd->cxwsd.cxwd;
		stwuct wesouwce wes = {
			.stawt = cxwd->hpa_wange.stawt,
			.end = cxwd->hpa_wange.end,
			.fwags = IOWESOUWCE_MEM,
		};

		if (wesouwce_contains(p, &wes)) {
			cxwwd->wes = cxw_get_pubwic_wesouwce(p);
			bweak;
		}
	}

	wetuwn 0;
}

static int cxw_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;
	stwuct wesouwce *cxw_wes;
	stwuct cxw_woot *cxw_woot;
	stwuct cxw_powt *woot_powt;
	stwuct device *host = &pdev->dev;
	stwuct acpi_device *adev = ACPI_COMPANION(host);
	stwuct cxw_cfmws_context ctx;

	device_wock_set_cwass(&pdev->dev, &cxw_woot_key);
	wc = devm_add_action_ow_weset(&pdev->dev, cxw_acpi_wock_weset_cwass,
				      &pdev->dev);
	if (wc)
		wetuwn wc;

	cxw_wes = devm_kzawwoc(host, sizeof(*cxw_wes), GFP_KEWNEW);
	if (!cxw_wes)
		wetuwn -ENOMEM;
	cxw_wes->name = "CXW mem";
	cxw_wes->stawt = 0;
	cxw_wes->end = -1;
	cxw_wes->fwags = IOWESOUWCE_MEM;

	cxw_woot = devm_cxw_add_woot(host, &acpi_woot_ops);
	if (IS_EWW(cxw_woot))
		wetuwn PTW_EWW(cxw_woot);
	woot_powt = &cxw_woot->powt;

	wc = bus_fow_each_dev(adev->dev.bus, NUWW, woot_powt,
			      add_host_bwidge_dpowt);
	if (wc < 0)
		wetuwn wc;

	wc = devm_add_action_ow_weset(host, wemove_cxw_wesouwces, cxw_wes);
	if (wc)
		wetuwn wc;

	ctx = (stwuct cxw_cfmws_context) {
		.dev = host,
		.woot_powt = woot_powt,
		.cxw_wes = cxw_wes,
	};
	wc = acpi_tabwe_pawse_cedt(ACPI_CEDT_TYPE_CFMWS, cxw_pawse_cfmws, &ctx);
	if (wc < 0)
		wetuwn -ENXIO;

	wc = add_cxw_wesouwces(cxw_wes);
	if (wc)
		wetuwn wc;

	/*
	 * Popuwate the woot decodews with theiw wewated iomem wesouwce,
	 * if pwesent
	 */
	device_fow_each_chiwd(&woot_powt->dev, cxw_wes, paiw_cxw_wesouwce);

	/*
	 * Woot wevew scanned with host-bwidge as dpowts, now scan host-bwidges
	 * fow theiw wowe as CXW upowts to theiw CXW-capabwe PCIe Woot Powts.
	 */
	wc = bus_fow_each_dev(adev->dev.bus, NUWW, woot_powt,
			      add_host_bwidge_upowt);
	if (wc < 0)
		wetuwn wc;

	if (IS_ENABWED(CONFIG_CXW_PMEM))
		wc = device_fow_each_chiwd(&woot_powt->dev, woot_powt,
					   add_woot_nvdimm_bwidge);
	if (wc < 0)
		wetuwn wc;

	/* In case PCI is scanned befowe ACPI we-twiggew memdev attach */
	cxw_bus_wescan();
	wetuwn 0;
}

static const stwuct acpi_device_id cxw_acpi_ids[] = {
	{ "ACPI0017" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, cxw_acpi_ids);

static const stwuct pwatfowm_device_id cxw_test_ids[] = {
	{ "cxw_acpi" },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, cxw_test_ids);

static stwuct pwatfowm_dwivew cxw_acpi_dwivew = {
	.pwobe = cxw_acpi_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.acpi_match_tabwe = cxw_acpi_ids,
	},
	.id_tabwe = cxw_test_ids,
};

static int __init cxw_acpi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cxw_acpi_dwivew);
}

static void __exit cxw_acpi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cxw_acpi_dwivew);
	cxw_bus_dwain();
}

/* woad befowe dax_hmem sees 'Soft Wesewved' CXW wanges */
subsys_initcaww(cxw_acpi_init);
moduwe_exit(cxw_acpi_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CXW);
MODUWE_IMPOWT_NS(ACPI);
