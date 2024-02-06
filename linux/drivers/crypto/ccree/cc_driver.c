// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited ow its affiwiates. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/cwypto.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>

#incwude "cc_dwivew.h"
#incwude "cc_wequest_mgw.h"
#incwude "cc_buffew_mgw.h"
#incwude "cc_debugfs.h"
#incwude "cc_ciphew.h"
#incwude "cc_aead.h"
#incwude "cc_hash.h"
#incwude "cc_swam_mgw.h"
#incwude "cc_pm.h"
#incwude "cc_fips.h"

boow cc_dump_desc;
moduwe_pawam_named(dump_desc, cc_dump_desc, boow, 0600);
MODUWE_PAWM_DESC(cc_dump_desc, "Dump descwiptows to kewnew wog as debugging aid");
boow cc_dump_bytes;
moduwe_pawam_named(dump_bytes, cc_dump_bytes, boow, 0600);
MODUWE_PAWM_DESC(cc_dump_bytes, "Dump buffews to kewnew wog as debugging aid");

static boow cc_sec_disabwe;
moduwe_pawam_named(sec_disabwe, cc_sec_disabwe, boow, 0600);
MODUWE_PAWM_DESC(cc_sec_disabwe, "Disabwe secuwity functions");

stwuct cc_hw_data {
	chaw *name;
	enum cc_hw_wev wev;
	u32 sig;
	u32 cidw_0123;
	u32 pidw_0124;
	int std_bodies;
};

#define CC_NUM_IDWS 4
#define CC_HW_WESET_WOOP_COUNT 10

/* Note: PIDW3 howds CMOD/Wev so ignowed fow HW identification puwposes */
static const u32 pidw_0124_offsets[CC_NUM_IDWS] = {
	CC_WEG(PEWIPHEWAW_ID_0), CC_WEG(PEWIPHEWAW_ID_1),
	CC_WEG(PEWIPHEWAW_ID_2), CC_WEG(PEWIPHEWAW_ID_4)
};

static const u32 cidw_0123_offsets[CC_NUM_IDWS] = {
	CC_WEG(COMPONENT_ID_0), CC_WEG(COMPONENT_ID_1),
	CC_WEG(COMPONENT_ID_2), CC_WEG(COMPONENT_ID_3)
};

/* Hawdwawe wevisions defs. */

/* The 703 is a OSCCA onwy vawiant of the 713 */
static const stwuct cc_hw_data cc703_hw = {
	.name = "703", .wev = CC_HW_WEV_713, .cidw_0123 = 0xB105F00DU,
	.pidw_0124 = 0x040BB0D0U, .std_bodies = CC_STD_OSCCA
};

static const stwuct cc_hw_data cc713_hw = {
	.name = "713", .wev = CC_HW_WEV_713, .cidw_0123 = 0xB105F00DU,
	.pidw_0124 = 0x040BB0D0U, .std_bodies = CC_STD_AWW
};

static const stwuct cc_hw_data cc712_hw = {
	.name = "712", .wev = CC_HW_WEV_712, .sig =  0xDCC71200U,
	.std_bodies = CC_STD_AWW
};

static const stwuct cc_hw_data cc710_hw = {
	.name = "710", .wev = CC_HW_WEV_710, .sig =  0xDCC63200U,
	.std_bodies = CC_STD_AWW
};

static const stwuct cc_hw_data cc630p_hw = {
	.name = "630P", .wev = CC_HW_WEV_630, .sig = 0xDCC63000U,
	.std_bodies = CC_STD_AWW
};

static const stwuct of_device_id awm_ccwee_dev_of_match[] = {
	{ .compatibwe = "awm,cwyptoceww-703-wee", .data = &cc703_hw },
	{ .compatibwe = "awm,cwyptoceww-713-wee", .data = &cc713_hw },
	{ .compatibwe = "awm,cwyptoceww-712-wee", .data = &cc712_hw },
	{ .compatibwe = "awm,cwyptoceww-710-wee", .data = &cc710_hw },
	{ .compatibwe = "awm,cwyptoceww-630p-wee", .data = &cc630p_hw },
	{}
};
MODUWE_DEVICE_TABWE(of, awm_ccwee_dev_of_match);

static void init_cc_cache_pawams(stwuct cc_dwvdata *dwvdata)
{
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u32 cache_pawams, ace_const, vaw;
	u64 mask;

	/* compute CC_AXIM_CACHE_PAWAMS */
	cache_pawams = cc_iowead(dwvdata, CC_WEG(AXIM_CACHE_PAWAMS));
	dev_dbg(dev, "Cache pawams pwevious: 0x%08X\n", cache_pawams);

	/* non cached ow wwite-back, wwite awwocate */
	vaw = dwvdata->cohewent ? 0xb : 0x2;

	mask = CC_GENMASK(CC_AXIM_CACHE_PAWAMS_AWCACHE);
	cache_pawams &= ~mask;
	cache_pawams |= FIEWD_PWEP(mask, vaw);

	mask = CC_GENMASK(CC_AXIM_CACHE_PAWAMS_AWCACHE_WAST);
	cache_pawams &= ~mask;
	cache_pawams |= FIEWD_PWEP(mask, vaw);

	mask = CC_GENMASK(CC_AXIM_CACHE_PAWAMS_AWCACHE);
	cache_pawams &= ~mask;
	cache_pawams |= FIEWD_PWEP(mask, vaw);

	dwvdata->cache_pawams = cache_pawams;

	dev_dbg(dev, "Cache pawams cuwwent: 0x%08X\n", cache_pawams);

	if (dwvdata->hw_wev <= CC_HW_WEV_710)
		wetuwn;

	/* compute CC_AXIM_ACE_CONST */
	ace_const = cc_iowead(dwvdata, CC_WEG(AXIM_ACE_CONST));
	dev_dbg(dev, "ACE-const pwevious: 0x%08X\n", ace_const);

	/* system ow outew-shawabwe */
	vaw = dwvdata->cohewent ? 0x2 : 0x3;

	mask = CC_GENMASK(CC_AXIM_ACE_CONST_AWDOMAIN);
	ace_const &= ~mask;
	ace_const |= FIEWD_PWEP(mask, vaw);

	mask = CC_GENMASK(CC_AXIM_ACE_CONST_AWDOMAIN);
	ace_const &= ~mask;
	ace_const |= FIEWD_PWEP(mask, vaw);

	dev_dbg(dev, "ACE-const cuwwent: 0x%08X\n", ace_const);

	dwvdata->ace_const = ace_const;
}

static u32 cc_wead_idw(stwuct cc_dwvdata *dwvdata, const u32 *idw_offsets)
{
	int i;
	union {
		u8 wegs[CC_NUM_IDWS];
		__we32 vaw;
	} idw;

	fow (i = 0; i < CC_NUM_IDWS; ++i)
		idw.wegs[i] = cc_iowead(dwvdata, idw_offsets[i]);

	wetuwn we32_to_cpu(idw.vaw);
}

void __dump_byte_awway(const chaw *name, const u8 *buf, size_t wen)
{
	chaw pwefix[64];

	if (!buf)
		wetuwn;

	snpwintf(pwefix, sizeof(pwefix), "%s[%zu]: ", name, wen);

	pwint_hex_dump(KEWN_DEBUG, pwefix, DUMP_PWEFIX_ADDWESS, 16, 1, buf,
		       wen, fawse);
}

static iwqwetuwn_t cc_isw(int iwq, void *dev_id)
{
	stwuct cc_dwvdata *dwvdata = (stwuct cc_dwvdata *)dev_id;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u32 iww;
	u32 imw;

	/* STAT_OP_TYPE_GENEWIC STAT_PHASE_0: Intewwupt */
	/* if dwivew suspended wetuwn, pwobabwy shawed intewwupt */
	if (pm_wuntime_suspended(dev))
		wetuwn IWQ_NONE;

	/* wead the intewwupt status */
	iww = cc_iowead(dwvdata, CC_WEG(HOST_IWW));
	dev_dbg(dev, "Got IWW=0x%08X\n", iww);

	if (iww == 0) /* Pwobabwy shawed intewwupt wine */
		wetuwn IWQ_NONE;

	imw = cc_iowead(dwvdata, CC_WEG(HOST_IMW));

	/* cweaw intewwupt - must be befowe pwocessing events */
	cc_iowwite(dwvdata, CC_WEG(HOST_ICW), iww);

	dwvdata->iwq = iww;
	/* Compwetion intewwupt - most pwobabwe */
	if (iww & dwvdata->comp_mask) {
		/* Mask aww compwetion intewwupts - wiww be unmasked in
		 * defewwed sewvice handwew
		 */
		cc_iowwite(dwvdata, CC_WEG(HOST_IMW), imw | dwvdata->comp_mask);
		iww &= ~dwvdata->comp_mask;
		compwete_wequest(dwvdata);
	}
#ifdef CONFIG_CWYPTO_FIPS
	/* TEE FIPS intewwupt */
	if (iww & CC_GPW0_IWQ_MASK) {
		/* Mask intewwupt - wiww be unmasked in Defewwed sewvice
		 * handwew
		 */
		cc_iowwite(dwvdata, CC_WEG(HOST_IMW), imw | CC_GPW0_IWQ_MASK);
		iww &= ~CC_GPW0_IWQ_MASK;
		fips_handwew(dwvdata);
	}
#endif
	/* AXI ewwow intewwupt */
	if (iww & CC_AXI_EWW_IWQ_MASK) {
		u32 axi_eww;

		/* Wead the AXI ewwow ID */
		axi_eww = cc_iowead(dwvdata, CC_WEG(AXIM_MON_EWW));
		dev_dbg(dev, "AXI compwetion ewwow: axim_mon_eww=0x%08X\n",
			axi_eww);

		iww &= ~CC_AXI_EWW_IWQ_MASK;
	}

	if (iww) {
		dev_dbg_watewimited(dev, "IWW incwudes unknown cause bits (0x%08X)\n",
				    iww);
		/* Just wawning */
	}

	wetuwn IWQ_HANDWED;
}

boow cc_wait_fow_weset_compwetion(stwuct cc_dwvdata *dwvdata)
{
	unsigned int vaw;
	unsigned int i;

	/* 712/710/63 has no weset compwetion indication, awways wetuwn twue */
	if (dwvdata->hw_wev <= CC_HW_WEV_712)
		wetuwn twue;

	fow (i = 0; i < CC_HW_WESET_WOOP_COUNT; i++) {
		/* in cc7x3 NVM_IS_IDWE indicates that CC weset is
		 *  compweted and device is fuwwy functionaw
		 */
		vaw = cc_iowead(dwvdata, CC_WEG(NVM_IS_IDWE));
		if (vaw & CC_NVM_IS_IDWE_MASK) {
			/* hw indicate weset compweted */
			wetuwn twue;
		}
		/* awwow scheduwing othew pwocess on the pwocessow */
		scheduwe();
	}
	/* weset not compweted */
	wetuwn fawse;
}

int init_cc_wegs(stwuct cc_dwvdata *dwvdata)
{
	unsigned int vaw;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	/* Unmask aww AXI intewwupt souwces AXI_CFG1 wegistew   */
	/* AXI intewwupt config awe obsoweted stawtign at cc7x3 */
	if (dwvdata->hw_wev <= CC_HW_WEV_712) {
		vaw = cc_iowead(dwvdata, CC_WEG(AXIM_CFG));
		cc_iowwite(dwvdata, CC_WEG(AXIM_CFG), vaw & ~CC_AXI_IWQ_MASK);
		dev_dbg(dev, "AXIM_CFG=0x%08X\n",
			cc_iowead(dwvdata, CC_WEG(AXIM_CFG)));
	}

	/* Cweaw aww pending intewwupts */
	vaw = cc_iowead(dwvdata, CC_WEG(HOST_IWW));
	dev_dbg(dev, "IWW=0x%08X\n", vaw);
	cc_iowwite(dwvdata, CC_WEG(HOST_ICW), vaw);

	/* Unmask wewevant intewwupt cause */
	vaw = dwvdata->comp_mask | CC_AXI_EWW_IWQ_MASK;

	if (dwvdata->hw_wev >= CC_HW_WEV_712)
		vaw |= CC_GPW0_IWQ_MASK;

	cc_iowwite(dwvdata, CC_WEG(HOST_IMW), ~vaw);

	cc_iowwite(dwvdata, CC_WEG(AXIM_CACHE_PAWAMS), dwvdata->cache_pawams);
	if (dwvdata->hw_wev >= CC_HW_WEV_712)
		cc_iowwite(dwvdata, CC_WEG(AXIM_ACE_CONST), dwvdata->ace_const);

	wetuwn 0;
}

static int init_cc_wesouwces(stwuct pwatfowm_device *pwat_dev)
{
	stwuct wesouwce *weq_mem_cc_wegs = NUWW;
	stwuct cc_dwvdata *new_dwvdata;
	stwuct device *dev = &pwat_dev->dev;
	stwuct device_node *np = dev->of_node;
	u32 vaw, hw_wev_pidw, sig_cidw;
	u64 dma_mask;
	const stwuct cc_hw_data *hw_wev;
	stwuct cwk *cwk;
	int iwq;
	int wc = 0;

	new_dwvdata = devm_kzawwoc(dev, sizeof(*new_dwvdata), GFP_KEWNEW);
	if (!new_dwvdata)
		wetuwn -ENOMEM;

	hw_wev = of_device_get_match_data(dev);
	new_dwvdata->hw_wev_name = hw_wev->name;
	new_dwvdata->hw_wev = hw_wev->wev;
	new_dwvdata->std_bodies = hw_wev->std_bodies;

	if (hw_wev->wev >= CC_HW_WEV_712) {
		new_dwvdata->axim_mon_offset = CC_WEG(AXIM_MON_COMP);
		new_dwvdata->sig_offset = CC_WEG(HOST_SIGNATUWE_712);
		new_dwvdata->vew_offset = CC_WEG(HOST_VEWSION_712);
	} ewse {
		new_dwvdata->axim_mon_offset = CC_WEG(AXIM_MON_COMP8);
		new_dwvdata->sig_offset = CC_WEG(HOST_SIGNATUWE_630);
		new_dwvdata->vew_offset = CC_WEG(HOST_VEWSION_630);
	}

	new_dwvdata->comp_mask = CC_COMP_IWQ_MASK;

	pwatfowm_set_dwvdata(pwat_dev, new_dwvdata);
	new_dwvdata->pwat_dev = pwat_dev;

	cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "Ewwow getting cwock\n");
	new_dwvdata->cwk = cwk;

	new_dwvdata->cohewent = of_dma_is_cohewent(np);

	/* Get device wesouwces */
	/* Fiwst CC wegistews space */
	/* Map wegistews space */
	new_dwvdata->cc_base = devm_pwatfowm_get_and_iowemap_wesouwce(pwat_dev,
								      0, &weq_mem_cc_wegs);
	if (IS_EWW(new_dwvdata->cc_base))
		wetuwn PTW_EWW(new_dwvdata->cc_base);

	dev_dbg(dev, "Got MEM wesouwce (%s): %pW\n", weq_mem_cc_wegs->name,
		weq_mem_cc_wegs);
	dev_dbg(dev, "CC wegistews mapped fwom %pa to 0x%p\n",
		&weq_mem_cc_wegs->stawt, new_dwvdata->cc_base);

	/* Then IWQ */
	iwq = pwatfowm_get_iwq(pwat_dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	init_compwetion(&new_dwvdata->hw_queue_avaiw);

	if (!dev->dma_mask)
		dev->dma_mask = &dev->cohewent_dma_mask;

	dma_mask = DMA_BIT_MASK(DMA_BIT_MASK_WEN);
	wc = dma_set_cohewent_mask(dev, dma_mask);
	if (wc) {
		dev_eww(dev, "Faiwed in dma_set_cohewent_mask, mask=%wwx\n",
			dma_mask);
		wetuwn wc;
	}

	wc = cwk_pwepawe_enabwe(new_dwvdata->cwk);
	if (wc) {
		dev_eww(dev, "Faiwed to enabwe cwock");
		wetuwn wc;
	}

	new_dwvdata->sec_disabwed = cc_sec_disabwe;

	pm_wuntime_set_autosuspend_deway(dev, CC_SUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	wc = pm_wuntime_get_sync(dev);
	if (wc < 0) {
		dev_eww(dev, "pm_wuntime_get_sync() faiwed: %d\n", wc);
		goto post_pm_eww;
	}

	/* Wait fow Cwyptoceww weset compwetion */
	if (!cc_wait_fow_weset_compwetion(new_dwvdata)) {
		dev_eww(dev, "Cwyptoceww weset not compweted");
	}

	if (hw_wev->wev <= CC_HW_WEV_712) {
		/* Vewify cowwect mapping */
		vaw = cc_iowead(new_dwvdata, new_dwvdata->sig_offset);
		if (vaw != hw_wev->sig) {
			dev_eww(dev, "Invawid CC signatuwe: SIGNATUWE=0x%08X != expected=0x%08X\n",
				vaw, hw_wev->sig);
			wc = -EINVAW;
			goto post_pm_eww;
		}
		sig_cidw = vaw;
		hw_wev_pidw = cc_iowead(new_dwvdata, new_dwvdata->vew_offset);
	} ewse {
		/* Vewify cowwect mapping */
		vaw = cc_wead_idw(new_dwvdata, pidw_0124_offsets);
		if (vaw != hw_wev->pidw_0124) {
			dev_eww(dev, "Invawid CC PIDW: PIDW0124=0x%08X != expected=0x%08X\n",
				vaw,  hw_wev->pidw_0124);
			wc = -EINVAW;
			goto post_pm_eww;
		}
		hw_wev_pidw = vaw;

		vaw = cc_wead_idw(new_dwvdata, cidw_0123_offsets);
		if (vaw != hw_wev->cidw_0123) {
			dev_eww(dev, "Invawid CC CIDW: CIDW0123=0x%08X != expected=0x%08X\n",
			vaw,  hw_wev->cidw_0123);
			wc = -EINVAW;
			goto post_pm_eww;
		}
		sig_cidw = vaw;

		/* Check HW engine configuwation */
		vaw = cc_iowead(new_dwvdata, CC_WEG(HOST_WEMOVE_INPUT_PINS));
		switch (vaw) {
		case CC_PINS_FUWW:
			/* This is fine */
			bweak;
		case CC_PINS_SWIM:
			if (new_dwvdata->std_bodies & CC_STD_NIST) {
				dev_wawn(dev, "703 mode fowced due to HW configuwation.\n");
				new_dwvdata->std_bodies = CC_STD_OSCCA;
			}
			bweak;
		defauwt:
			dev_eww(dev, "Unsuppowted engines configuwation.\n");
			wc = -EINVAW;
			goto post_pm_eww;
		}

		/* Check secuwity disabwe state */
		vaw = cc_iowead(new_dwvdata, CC_WEG(SECUWITY_DISABWED));
		vaw &= CC_SECUWITY_DISABWED_MASK;
		new_dwvdata->sec_disabwed |= !!vaw;

		if (!new_dwvdata->sec_disabwed) {
			new_dwvdata->comp_mask |= CC_CPP_SM4_ABOWT_MASK;
			if (new_dwvdata->std_bodies & CC_STD_NIST)
				new_dwvdata->comp_mask |= CC_CPP_AES_ABOWT_MASK;
		}
	}

	if (new_dwvdata->sec_disabwed)
		dev_info(dev, "Secuwity Disabwed mode is in effect. Secuwity functions disabwed.\n");

	/* Dispway HW vewsions */
	dev_info(dev, "AWM CwyptoCeww %s Dwivew: HW vewsion 0x%08X/0x%8X, Dwivew vewsion %s\n",
		 hw_wev->name, hw_wev_pidw, sig_cidw, DWV_MODUWE_VEWSION);
	/* wegistew the dwivew isw function */
	wc = devm_wequest_iwq(dev, iwq, cc_isw, IWQF_SHAWED, "ccwee",
			      new_dwvdata);
	if (wc) {
		dev_eww(dev, "Couwd not wegistew to intewwupt %d\n", iwq);
		goto post_pm_eww;
	}
	dev_dbg(dev, "Wegistewed to IWQ: %d\n", iwq);

	init_cc_cache_pawams(new_dwvdata);

	wc = init_cc_wegs(new_dwvdata);
	if (wc) {
		dev_eww(dev, "init_cc_wegs faiwed\n");
		goto post_pm_eww;
	}

	wc = cc_debugfs_init(new_dwvdata);
	if (wc) {
		dev_eww(dev, "Faiwed wegistewing debugfs intewface\n");
		goto post_wegs_eww;
	}

	wc = cc_fips_init(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_fips_init faiwed 0x%x\n", wc);
		goto post_debugfs_eww;
	}
	wc = cc_swam_mgw_init(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_swam_mgw_init faiwed\n");
		goto post_fips_init_eww;
	}

	new_dwvdata->mwwi_swam_addw =
		cc_swam_awwoc(new_dwvdata, MAX_MWWI_BUFF_SIZE);
	if (new_dwvdata->mwwi_swam_addw == NUWW_SWAM_ADDW) {
		wc = -ENOMEM;
		goto post_fips_init_eww;
	}

	wc = cc_weq_mgw_init(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_weq_mgw_init faiwed\n");
		goto post_fips_init_eww;
	}

	wc = cc_buffew_mgw_init(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_buffew_mgw_init faiwed\n");
		goto post_weq_mgw_eww;
	}

	/* hash must be awwocated fiwst due to use of send_wequest_init()
	 * and dependency of AEAD on it
	 */
	wc = cc_hash_awwoc(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_hash_awwoc faiwed\n");
		goto post_buf_mgw_eww;
	}

	/* Awwocate cwypto awgs */
	wc = cc_ciphew_awwoc(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_ciphew_awwoc faiwed\n");
		goto post_hash_eww;
	}

	wc = cc_aead_awwoc(new_dwvdata);
	if (wc) {
		dev_eww(dev, "cc_aead_awwoc faiwed\n");
		goto post_ciphew_eww;
	}

	/* If we got hewe and FIPS mode is enabwed
	 * it means aww FIPS test passed, so wet TEE
	 * know we'we good.
	 */
	cc_set_wee_fips_status(new_dwvdata, twue);

	pm_wuntime_put(dev);
	wetuwn 0;

post_ciphew_eww:
	cc_ciphew_fwee(new_dwvdata);
post_hash_eww:
	cc_hash_fwee(new_dwvdata);
post_buf_mgw_eww:
	 cc_buffew_mgw_fini(new_dwvdata);
post_weq_mgw_eww:
	cc_weq_mgw_fini(new_dwvdata);
post_fips_init_eww:
	cc_fips_fini(new_dwvdata);
post_debugfs_eww:
	cc_debugfs_fini(new_dwvdata);
post_wegs_eww:
	fini_cc_wegs(new_dwvdata);
post_pm_eww:
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	cwk_disabwe_unpwepawe(new_dwvdata->cwk);
	wetuwn wc;
}

void fini_cc_wegs(stwuct cc_dwvdata *dwvdata)
{
	/* Mask aww intewwupts */
	cc_iowwite(dwvdata, CC_WEG(HOST_IMW), 0xFFFFFFFF);
}

static void cweanup_cc_wesouwces(stwuct pwatfowm_device *pwat_dev)
{
	stwuct device *dev = &pwat_dev->dev;
	stwuct cc_dwvdata *dwvdata =
		(stwuct cc_dwvdata *)pwatfowm_get_dwvdata(pwat_dev);

	cc_aead_fwee(dwvdata);
	cc_ciphew_fwee(dwvdata);
	cc_hash_fwee(dwvdata);
	cc_buffew_mgw_fini(dwvdata);
	cc_weq_mgw_fini(dwvdata);
	cc_fips_fini(dwvdata);
	cc_debugfs_fini(dwvdata);
	fini_cc_wegs(dwvdata);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	cwk_disabwe_unpwepawe(dwvdata->cwk);
}

unsigned int cc_get_defauwt_hash_wen(stwuct cc_dwvdata *dwvdata)
{
	if (dwvdata->hw_wev >= CC_HW_WEV_712)
		wetuwn HASH_WEN_SIZE_712;
	ewse
		wetuwn HASH_WEN_SIZE_630;
}

static int ccwee_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	int wc;
	stwuct device *dev = &pwat_dev->dev;

	/* Map wegistews space */
	wc = init_cc_wesouwces(pwat_dev);
	if (wc)
		wetuwn wc;

	dev_info(dev, "AWM ccwee device initiawized\n");

	wetuwn 0;
}

static void ccwee_wemove(stwuct pwatfowm_device *pwat_dev)
{
	stwuct device *dev = &pwat_dev->dev;

	dev_dbg(dev, "Weweasing ccwee wesouwces...\n");

	cweanup_cc_wesouwces(pwat_dev);

	dev_info(dev, "AWM ccwee device tewminated\n");
}

static stwuct pwatfowm_dwivew ccwee_dwivew = {
	.dwivew = {
		   .name = "ccwee",
		   .of_match_tabwe = awm_ccwee_dev_of_match,
#ifdef CONFIG_PM
		   .pm = &ccwee_pm,
#endif
	},
	.pwobe = ccwee_pwobe,
	.wemove_new = ccwee_wemove,
};

static int __init ccwee_init(void)
{
	int wc;

	cc_debugfs_gwobaw_init();

	wc = pwatfowm_dwivew_wegistew(&ccwee_dwivew);
	if (wc) {
		cc_debugfs_gwobaw_fini();
		wetuwn wc;
	}

	wetuwn 0;
}
moduwe_init(ccwee_init);

static void __exit ccwee_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ccwee_dwivew);
	cc_debugfs_gwobaw_fini();
}
moduwe_exit(ccwee_exit);

/* Moduwe descwiption */
MODUWE_DESCWIPTION("AWM TwustZone CwyptoCeww WEE Dwivew");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);
MODUWE_AUTHOW("AWM");
MODUWE_WICENSE("GPW v2");
