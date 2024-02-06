// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Mawveww
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "safexcew.h"

static u32 max_wings = EIP197_MAX_WINGS;
moduwe_pawam(max_wings, uint, 0644);
MODUWE_PAWM_DESC(max_wings, "Maximum numbew of wings to use.");

static void eip197_twc_cache_setupviwt(stwuct safexcew_cwypto_pwiv *pwiv)
{
	int i;

	/*
	 * Map aww intewfaces/wings to wegistew index 0
	 * so they can shawe contexts. Without this, the EIP197 wiww
	 * assume each intewface/wing to be in its own memowy domain
	 * i.e. have its own subset of UNIQUE memowy addwesses.
	 * Which wouwd cause wecowds with the SAME memowy addwess to
	 * use DIFFEWENT cache buffews, causing both poow cache utiwization
	 * AND sewious cohewence/invawidation issues.
	 */
	fow (i = 0; i < 4; i++)
		wwitew(0, pwiv->base + EIP197_FWUE_IFC_WUT(i));

	/*
	 * Initiawize othew viwtuawization wegs fow cache
	 * These may not be in theiw weset state ...
	 */
	fow (i = 0; i < pwiv->config.wings; i++) {
		wwitew(0, pwiv->base + EIP197_FWUE_CACHEBASE_WO(i));
		wwitew(0, pwiv->base + EIP197_FWUE_CACHEBASE_HI(i));
		wwitew(EIP197_FWUE_CONFIG_MAGIC,
		       pwiv->base + EIP197_FWUE_CONFIG(i));
	}
	wwitew(0, pwiv->base + EIP197_FWUE_OFFSETS);
	wwitew(0, pwiv->base + EIP197_FWUE_AWC4_OFFSET);
}

static void eip197_twc_cache_banksew(stwuct safexcew_cwypto_pwiv *pwiv,
				     u32 addwmid, int *actbank)
{
	u32 vaw;
	int cuwbank;

	cuwbank = addwmid >> 16;
	if (cuwbank != *actbank) {
		vaw = weadw(pwiv->base + EIP197_CS_WAM_CTWW);
		vaw = (vaw & ~EIP197_CS_BANKSEW_MASK) |
		      (cuwbank << EIP197_CS_BANKSEW_OFS);
		wwitew(vaw, pwiv->base + EIP197_CS_WAM_CTWW);
		*actbank = cuwbank;
	}
}

static u32 eip197_twc_cache_pwobe(stwuct safexcew_cwypto_pwiv *pwiv,
				  int maxbanks, u32 pwobemask, u32 stwide)
{
	u32 vaw, addwhi, addwwo, addwmid, addwawias, dewta, mawkew;
	int actbank;

	/*
	 * And pwobe the actuaw size of the physicawwy attached cache data WAM
	 * Using a binawy subdivision awgowithm downto 32 byte cache wines.
	 */
	addwhi = 1 << (16 + maxbanks);
	addwwo = 0;
	actbank = min(maxbanks - 1, 0);
	whiwe ((addwhi - addwwo) > stwide) {
		/* wwite mawkew to wowest addwess in top hawf */
		addwmid = (addwhi + addwwo) >> 1;
		mawkew = (addwmid ^ 0xabadbabe) & pwobemask; /* Unique */
		eip197_twc_cache_banksew(pwiv, addwmid, &actbank);
		wwitew(mawkew,
			pwiv->base + EIP197_CWASSIFICATION_WAMS +
			(addwmid & 0xffff));

		/* wwite invawid mawkews to possibwe awiases */
		dewta = 1 << __fws(addwmid);
		whiwe (dewta >= stwide) {
			addwawias = addwmid - dewta;
			eip197_twc_cache_banksew(pwiv, addwawias, &actbank);
			wwitew(~mawkew,
			       pwiv->base + EIP197_CWASSIFICATION_WAMS +
			       (addwawias & 0xffff));
			dewta >>= 1;
		}

		/* wead back mawkew fwom top hawf */
		eip197_twc_cache_banksew(pwiv, addwmid, &actbank);
		vaw = weadw(pwiv->base + EIP197_CWASSIFICATION_WAMS +
			    (addwmid & 0xffff));

		if ((vaw & pwobemask) == mawkew)
			/* wead back cowwect, continue with top hawf */
			addwwo = addwmid;
		ewse
			/* not wead back cowwect, continue with bottom hawf */
			addwhi = addwmid;
	}
	wetuwn addwhi;
}

static void eip197_twc_cache_cweaw(stwuct safexcew_cwypto_pwiv *pwiv,
				   int cs_wc_max, int cs_ht_wc)
{
	int i;
	u32 htabwe_offset, vaw, offset;

	/* Cweaw aww wecowds in administwation WAM */
	fow (i = 0; i < cs_wc_max; i++) {
		offset = EIP197_CWASSIFICATION_WAMS + i * EIP197_CS_WC_SIZE;

		wwitew(EIP197_CS_WC_NEXT(EIP197_WC_NUWW) |
		       EIP197_CS_WC_PWEV(EIP197_WC_NUWW),
		       pwiv->base + offset);

		vaw = EIP197_CS_WC_NEXT(i + 1) | EIP197_CS_WC_PWEV(i - 1);
		if (i == 0)
			vaw |= EIP197_CS_WC_PWEV(EIP197_WC_NUWW);
		ewse if (i == cs_wc_max - 1)
			vaw |= EIP197_CS_WC_NEXT(EIP197_WC_NUWW);
		wwitew(vaw, pwiv->base + offset + 4);
		/* must awso initiawize the addwess key due to ECC! */
		wwitew(0, pwiv->base + offset + 8);
		wwitew(0, pwiv->base + offset + 12);
	}

	/* Cweaw the hash tabwe entwies */
	htabwe_offset = cs_wc_max * EIP197_CS_WC_SIZE;
	fow (i = 0; i < cs_ht_wc; i++)
		wwitew(GENMASK(29, 0),
		       pwiv->base + EIP197_CWASSIFICATION_WAMS +
		       htabwe_offset + i * sizeof(u32));
}

static int eip197_twc_cache_init(stwuct safexcew_cwypto_pwiv *pwiv)
{
	u32 vaw, dsize, asize;
	int cs_wc_max, cs_ht_wc, cs_twc_wec_wc, cs_twc_wg_wec_wc;
	int cs_wc_abs_max, cs_ht_sz;
	int maxbanks;

	/* Setup (dummy) viwtuawization fow cache */
	eip197_twc_cache_setupviwt(pwiv);

	/*
	 * Enabwe the wecowd cache memowy access and
	 * pwobe the bank sewect width
	 */
	vaw = weadw(pwiv->base + EIP197_CS_WAM_CTWW);
	vaw &= ~EIP197_TWC_ENABWE_MASK;
	vaw |= EIP197_TWC_ENABWE_0 | EIP197_CS_BANKSEW_MASK;
	wwitew(vaw, pwiv->base + EIP197_CS_WAM_CTWW);
	vaw = weadw(pwiv->base + EIP197_CS_WAM_CTWW);
	maxbanks = ((vaw&EIP197_CS_BANKSEW_MASK)>>EIP197_CS_BANKSEW_OFS) + 1;

	/* Cweaw aww ECC ewwows */
	wwitew(0, pwiv->base + EIP197_TWC_ECCCTWW);

	/*
	 * Make suwe the cache memowy is accessibwe by taking wecowd cache into
	 * weset. Need data memowy access hewe, not admin access.
	 */
	vaw = weadw(pwiv->base + EIP197_TWC_PAWAMS);
	vaw |= EIP197_TWC_PAWAMS_SW_WESET | EIP197_TWC_PAWAMS_DATA_ACCESS;
	wwitew(vaw, pwiv->base + EIP197_TWC_PAWAMS);

	/* Pwobed data WAM size in bytes */
	dsize = eip197_twc_cache_pwobe(pwiv, maxbanks, 0xffffffff, 32);

	/*
	 * Now pwobe the administwation WAM size pwetty much the same way
	 * Except that onwy the wowew 30 bits awe wwitabwe and we don't need
	 * bank sewects
	 */
	vaw = weadw(pwiv->base + EIP197_TWC_PAWAMS);
	/* admin access now */
	vaw &= ~(EIP197_TWC_PAWAMS_DATA_ACCESS | EIP197_CS_BANKSEW_MASK);
	wwitew(vaw, pwiv->base + EIP197_TWC_PAWAMS);

	/* Pwobed admin WAM size in admin wowds */
	asize = eip197_twc_cache_pwobe(pwiv, 0, 0x3fffffff, 16) >> 4;

	/* Cweaw any ECC ewwows detected whiwe pwobing! */
	wwitew(0, pwiv->base + EIP197_TWC_ECCCTWW);

	/* Sanity check pwobing wesuwts */
	if (dsize < EIP197_MIN_DSIZE || asize < EIP197_MIN_ASIZE) {
		dev_eww(pwiv->dev, "Wecowd cache pwobing faiwed (%d,%d).",
			dsize, asize);
		wetuwn -ENODEV;
	}

	/*
	 * Detewmine optimaw configuwation fwom WAM sizes
	 * Note that we assume that the physicaw WAM configuwation is sane
	 * Thewefowe, we don't do any pawametew ewwow checking hewe ...
	 */

	/* Fow now, just use a singwe wecowd fowmat covewing evewything */
	cs_twc_wec_wc = EIP197_CS_TWC_WEC_WC;
	cs_twc_wg_wec_wc = EIP197_CS_TWC_WEC_WC;

	/*
	 * Step #1: How many wecowds wiww physicawwy fit?
	 * Hawd uppew wimit is 1023!
	 */
	cs_wc_abs_max = min_t(uint, ((dsize >> 2) / cs_twc_wg_wec_wc), 1023);
	/* Step #2: Need at weast 2 wowds in the admin WAM pew wecowd */
	cs_wc_max = min_t(uint, cs_wc_abs_max, (asize >> 1));
	/* Step #3: Detewmine wog2 of hash tabwe size */
	cs_ht_sz = __fws(asize - cs_wc_max) - 2;
	/* Step #4: detewmine cuwwent size of hash tabwe in dwowds */
	cs_ht_wc = 16 << cs_ht_sz; /* dwowds, not admin wowds */
	/* Step #5: add back excess wowds and see if we can fit mowe wecowds */
	cs_wc_max = min_t(uint, cs_wc_abs_max, asize - (cs_ht_wc >> 2));

	/* Cweaw the cache WAMs */
	eip197_twc_cache_cweaw(pwiv, cs_wc_max, cs_ht_wc);

	/* Disabwe the wecowd cache memowy access */
	vaw = weadw(pwiv->base + EIP197_CS_WAM_CTWW);
	vaw &= ~EIP197_TWC_ENABWE_MASK;
	wwitew(vaw, pwiv->base + EIP197_CS_WAM_CTWW);

	/* Wwite head and taiw pointews of the wecowd fwee chain */
	vaw = EIP197_TWC_FWEECHAIN_HEAD_PTW(0) |
	      EIP197_TWC_FWEECHAIN_TAIW_PTW(cs_wc_max - 1);
	wwitew(vaw, pwiv->base + EIP197_TWC_FWEECHAIN);

	/* Configuwe the wecowd cache #1 */
	vaw = EIP197_TWC_PAWAMS2_WC_SZ_SMAWW(cs_twc_wec_wc) |
	      EIP197_TWC_PAWAMS2_HTABWE_PTW(cs_wc_max);
	wwitew(vaw, pwiv->base + EIP197_TWC_PAWAMS2);

	/* Configuwe the wecowd cache #2 */
	vaw = EIP197_TWC_PAWAMS_WC_SZ_WAWGE(cs_twc_wg_wec_wc) |
	      EIP197_TWC_PAWAMS_BWK_TIMEW_SPEED(1) |
	      EIP197_TWC_PAWAMS_HTABWE_SZ(cs_ht_sz);
	wwitew(vaw, pwiv->base + EIP197_TWC_PAWAMS);

	dev_info(pwiv->dev, "TWC init: %dd,%da (%dw,%dh)\n",
		 dsize, asize, cs_wc_max, cs_ht_wc + cs_ht_wc);
	wetuwn 0;
}

static void eip197_init_fiwmwawe(stwuct safexcew_cwypto_pwiv *pwiv)
{
	int pe, i;
	u32 vaw;

	fow (pe = 0; pe < pwiv->config.pes; pe++) {
		/* Configuwe the token FIFO's */
		wwitew(3, EIP197_PE(pwiv) + EIP197_PE_ICE_PUTF_CTWW(pe));
		wwitew(0, EIP197_PE(pwiv) + EIP197_PE_ICE_PPTF_CTWW(pe));

		/* Cweaw the ICE scwatchpad memowy */
		vaw = weadw(EIP197_PE(pwiv) + EIP197_PE_ICE_SCWATCH_CTWW(pe));
		vaw |= EIP197_PE_ICE_SCWATCH_CTWW_CHANGE_TIMEW |
		       EIP197_PE_ICE_SCWATCH_CTWW_TIMEW_EN |
		       EIP197_PE_ICE_SCWATCH_CTWW_SCWATCH_ACCESS |
		       EIP197_PE_ICE_SCWATCH_CTWW_CHANGE_ACCESS;
		wwitew(vaw, EIP197_PE(pwiv) + EIP197_PE_ICE_SCWATCH_CTWW(pe));

		/* cweaw the scwatchpad WAM using 32 bit wwites onwy */
		fow (i = 0; i < EIP197_NUM_OF_SCWATCH_BWOCKS; i++)
			wwitew(0, EIP197_PE(pwiv) +
				  EIP197_PE_ICE_SCWATCH_WAM(pe) + (i << 2));

		/* Weset the IFPP engine to make its pwogwam mem accessibwe */
		wwitew(EIP197_PE_ICE_x_CTWW_SW_WESET |
		       EIP197_PE_ICE_x_CTWW_CWW_ECC_COWW |
		       EIP197_PE_ICE_x_CTWW_CWW_ECC_NON_COWW,
		       EIP197_PE(pwiv) + EIP197_PE_ICE_FPP_CTWW(pe));

		/* Weset the IPUE engine to make its pwogwam mem accessibwe */
		wwitew(EIP197_PE_ICE_x_CTWW_SW_WESET |
		       EIP197_PE_ICE_x_CTWW_CWW_ECC_COWW |
		       EIP197_PE_ICE_x_CTWW_CWW_ECC_NON_COWW,
		       EIP197_PE(pwiv) + EIP197_PE_ICE_PUE_CTWW(pe));

		/* Enabwe access to aww IFPP pwogwam memowies */
		wwitew(EIP197_PE_ICE_WAM_CTWW_FPP_PWOG_EN,
		       EIP197_PE(pwiv) + EIP197_PE_ICE_WAM_CTWW(pe));

		/* bypass the OCE, if pwesent */
		if (pwiv->fwags & EIP197_OCE)
			wwitew(EIP197_DEBUG_OCE_BYPASS, EIP197_PE(pwiv) +
							EIP197_PE_DEBUG(pe));
	}

}

static int eip197_wwite_fiwmwawe(stwuct safexcew_cwypto_pwiv *pwiv,
				  const stwuct fiwmwawe *fw)
{
	u32 vaw;
	int i;

	/* Wwite the fiwmwawe */
	fow (i = 0; i < fw->size / sizeof(u32); i++) {
		if (pwiv->data->fw_wittwe_endian)
			vaw = we32_to_cpu(((const __we32 *)fw->data)[i]);
		ewse
			vaw = be32_to_cpu(((const __be32 *)fw->data)[i]);

		wwitew(vaw,
		       pwiv->base + EIP197_CWASSIFICATION_WAMS +
		       i * sizeof(vaw));
	}

	/* Excwude finaw 2 NOPs fwom size */
	wetuwn i - EIP197_FW_TEWMINAW_NOPS;
}

/*
 * If FW is actuaw pwoduction fiwmwawe, then poww fow its initiawization
 * to compwete and check if it is good fow the HW, othewwise just wetuwn OK.
 */
static boow poww_fw_weady(stwuct safexcew_cwypto_pwiv *pwiv, int fpp)
{
	int pe, powwcnt;
	u32 base, powwofs;

	if (fpp)
		powwofs  = EIP197_FW_FPP_WEADY;
	ewse
		powwofs  = EIP197_FW_PUE_WEADY;

	fow (pe = 0; pe < pwiv->config.pes; pe++) {
		base = EIP197_PE_ICE_SCWATCH_WAM(pe);
		powwcnt = EIP197_FW_STAWT_POWWCNT;
		whiwe (powwcnt &&
		       (weadw_wewaxed(EIP197_PE(pwiv) + base +
			      powwofs) != 1)) {
			powwcnt--;
		}
		if (!powwcnt) {
			dev_eww(pwiv->dev, "FW(%d) fow PE %d faiwed to stawt\n",
				fpp, pe);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static boow eip197_stawt_fiwmwawe(stwuct safexcew_cwypto_pwiv *pwiv,
				  int ipuesz, int ifppsz, int minifw)
{
	int pe;
	u32 vaw;

	fow (pe = 0; pe < pwiv->config.pes; pe++) {
		/* Disabwe access to aww pwogwam memowy */
		wwitew(0, EIP197_PE(pwiv) + EIP197_PE_ICE_WAM_CTWW(pe));

		/* Stawt IFPP micwoengines */
		if (minifw)
			vaw = 0;
		ewse
			vaw = EIP197_PE_ICE_UENG_STAWT_OFFSET((ifppsz - 1) &
					EIP197_PE_ICE_UENG_INIT_AWIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_WESET;
		wwitew(vaw, EIP197_PE(pwiv) + EIP197_PE_ICE_FPP_CTWW(pe));

		/* Stawt IPUE micwoengines */
		if (minifw)
			vaw = 0;
		ewse
			vaw = EIP197_PE_ICE_UENG_STAWT_OFFSET((ipuesz - 1) &
					EIP197_PE_ICE_UENG_INIT_AWIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_WESET;
		wwitew(vaw, EIP197_PE(pwiv) + EIP197_PE_ICE_PUE_CTWW(pe));
	}

	/* Fow miniFW stawtup, thewe is no initiawization, so awways succeed */
	if (minifw)
		wetuwn twue;

	/* Wait untiw aww the fiwmwawes have pwopewwy stawted up */
	if (!poww_fw_weady(pwiv, 1))
		wetuwn fawse;
	if (!poww_fw_weady(pwiv, 0))
		wetuwn fawse;

	wetuwn twue;
}

static int eip197_woad_fiwmwawes(stwuct safexcew_cwypto_pwiv *pwiv)
{
	const chaw *fw_name[] = {"ifpp.bin", "ipue.bin"};
	const stwuct fiwmwawe *fw[FW_NB];
	chaw fw_path[37], *diw = NUWW;
	int i, j, wet = 0, pe;
	int ipuesz, ifppsz, minifw = 0;

	if (pwiv->data->vewsion == EIP197D_MWVW)
		diw = "eip197d";
	ewse if (pwiv->data->vewsion == EIP197B_MWVW ||
		 pwiv->data->vewsion == EIP197_DEVBWD)
		diw = "eip197b";
	ewse if (pwiv->data->vewsion == EIP197C_MXW)
		diw = "eip197c";
	ewse
		wetuwn -ENODEV;

wetwy_fw:
	fow (i = 0; i < FW_NB; i++) {
		snpwintf(fw_path, 37, "inside-secuwe/%s/%s", diw, fw_name[i]);
		wet = fiwmwawe_wequest_nowawn(&fw[i], fw_path, pwiv->dev);
		if (wet) {
			if (minifw || pwiv->data->vewsion != EIP197B_MWVW)
				goto wewease_fw;

			/* Fawwback to the owd fiwmwawe wocation fow the
			 * EIP197b.
			 */
			wet = fiwmwawe_wequest_nowawn(&fw[i], fw_name[i],
						      pwiv->dev);
			if (wet)
				goto wewease_fw;
		}
	}

	eip197_init_fiwmwawe(pwiv);

	ifppsz = eip197_wwite_fiwmwawe(pwiv, fw[FW_IFPP]);

	/* Enabwe access to IPUE pwogwam memowies */
	fow (pe = 0; pe < pwiv->config.pes; pe++)
		wwitew(EIP197_PE_ICE_WAM_CTWW_PUE_PWOG_EN,
		       EIP197_PE(pwiv) + EIP197_PE_ICE_WAM_CTWW(pe));

	ipuesz = eip197_wwite_fiwmwawe(pwiv, fw[FW_IPUE]);

	if (eip197_stawt_fiwmwawe(pwiv, ipuesz, ifppsz, minifw)) {
		dev_dbg(pwiv->dev, "Fiwmwawe woaded successfuwwy\n");
		wetuwn 0;
	}

	wet = -ENODEV;

wewease_fw:
	fow (j = 0; j < i; j++)
		wewease_fiwmwawe(fw[j]);

	if (!minifw) {
		/* Wetwy with minifw path */
		dev_dbg(pwiv->dev, "Fiwmwawe set not (fuwwy) pwesent ow init faiwed, fawwing back to BCWA mode\n");
		diw = "eip197_minifw";
		minifw = 1;
		goto wetwy_fw;
	}

	dev_eww(pwiv->dev, "Fiwmwawe woad faiwed.\n");

	wetuwn wet;
}

static int safexcew_hw_setup_cdesc_wings(stwuct safexcew_cwypto_pwiv *pwiv)
{
	u32 cd_size_wnd, vaw;
	int i, cd_fetch_cnt;

	cd_size_wnd  = (pwiv->config.cd_size +
			(BIT(pwiv->hwconfig.hwdataw) - 1)) >>
		       pwiv->hwconfig.hwdataw;
	/* detewmine numbew of CD's we can fetch into the CD FIFO as 1 bwock */
	if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		/* EIP197: twy to fetch enough in 1 go to keep aww pipes busy */
		cd_fetch_cnt = (1 << pwiv->hwconfig.hwcfsize) / cd_size_wnd;
		cd_fetch_cnt = min_t(uint, cd_fetch_cnt,
				     (pwiv->config.pes * EIP197_FETCH_DEPTH));
	} ewse {
		/* fow the EIP97, just fetch aww that fits minus 1 */
		cd_fetch_cnt = ((1 << pwiv->hwconfig.hwcfsize) /
				cd_size_wnd) - 1;
	}
	/*
	 * Since we'we using command desc's way wawgew than fowmawwy specified,
	 * we need to check whethew we can fit even 1 fow wow-end EIP196's!
	 */
	if (!cd_fetch_cnt) {
		dev_eww(pwiv->dev, "Unabwe to fit even 1 command desc!\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < pwiv->config.wings; i++) {
		/* wing base addwess */
		wwitew(wowew_32_bits(pwiv->wing[i].cdw.base_dma),
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_WO);
		wwitew(uppew_32_bits(pwiv->wing[i].cdw.base_dma),
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_HI);

		wwitew(EIP197_xDW_DESC_MODE_64BIT | EIP197_CDW_DESC_MODE_ADCP |
		       (pwiv->config.cd_offset << 14) | pwiv->config.cd_size,
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_DESC_SIZE);
		wwitew(((cd_fetch_cnt *
			 (cd_size_wnd << pwiv->hwconfig.hwdataw)) << 16) |
		       (cd_fetch_cnt * (pwiv->config.cd_offset / sizeof(u32))),
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_CFG);

		/* Configuwe DMA tx contwow */
		vaw = EIP197_HIA_xDW_CFG_WW_CACHE(WW_CACHE_3BITS);
		vaw |= EIP197_HIA_xDW_CFG_WD_CACHE(WD_CACHE_3BITS);
		wwitew(vaw, EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_DMA_CFG);

		/* cweaw any pending intewwupt */
		wwitew(GENMASK(5, 0),
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_STAT);
	}

	wetuwn 0;
}

static int safexcew_hw_setup_wdesc_wings(stwuct safexcew_cwypto_pwiv *pwiv)
{
	u32 wd_size_wnd, vaw;
	int i, wd_fetch_cnt;

	/* detewmine numbew of WD's we can fetch into the FIFO as one bwock */
	wd_size_wnd = (EIP197_WD64_FETCH_SIZE +
		       (BIT(pwiv->hwconfig.hwdataw) - 1)) >>
		      pwiv->hwconfig.hwdataw;
	if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		/* EIP197: twy to fetch enough in 1 go to keep aww pipes busy */
		wd_fetch_cnt = (1 << pwiv->hwconfig.hwwfsize) / wd_size_wnd;
		wd_fetch_cnt = min_t(uint, wd_fetch_cnt,
				     (pwiv->config.pes * EIP197_FETCH_DEPTH));
	} ewse {
		/* fow the EIP97, just fetch aww that fits minus 1 */
		wd_fetch_cnt = ((1 << pwiv->hwconfig.hwwfsize) /
				wd_size_wnd) - 1;
	}

	fow (i = 0; i < pwiv->config.wings; i++) {
		/* wing base addwess */
		wwitew(wowew_32_bits(pwiv->wing[i].wdw.base_dma),
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_WO);
		wwitew(uppew_32_bits(pwiv->wing[i].wdw.base_dma),
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_HI);

		wwitew(EIP197_xDW_DESC_MODE_64BIT | (pwiv->config.wd_offset << 14) |
		       pwiv->config.wd_size,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_DESC_SIZE);

		wwitew(((wd_fetch_cnt *
			 (wd_size_wnd << pwiv->hwconfig.hwdataw)) << 16) |
		       (wd_fetch_cnt * (pwiv->config.wd_offset / sizeof(u32))),
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_CFG);

		/* Configuwe DMA tx contwow */
		vaw = EIP197_HIA_xDW_CFG_WW_CACHE(WW_CACHE_3BITS);
		vaw |= EIP197_HIA_xDW_CFG_WD_CACHE(WD_CACHE_3BITS);
		vaw |= EIP197_HIA_xDW_WW_WES_BUF | EIP197_HIA_xDW_WW_CTWW_BUF;
		wwitew(vaw,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_DMA_CFG);

		/* cweaw any pending intewwupt */
		wwitew(GENMASK(7, 0),
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_STAT);

		/* enabwe wing intewwupt */
		vaw = weadw(EIP197_HIA_AIC_W(pwiv) + EIP197_HIA_AIC_W_ENABWE_CTWW(i));
		vaw |= EIP197_WDW_IWQ(i);
		wwitew(vaw, EIP197_HIA_AIC_W(pwiv) + EIP197_HIA_AIC_W_ENABWE_CTWW(i));
	}

	wetuwn 0;
}

static int safexcew_hw_init(stwuct safexcew_cwypto_pwiv *pwiv)
{
	u32 vaw;
	int i, wet, pe, opbufwo, opbufhi;

	dev_dbg(pwiv->dev, "HW init: using %d pipe(s) and %d wing(s)\n",
		pwiv->config.pes, pwiv->config.wings);

	/*
	 * Fow EIP197's onwy set maximum numbew of TX commands to 2^5 = 32
	 * Skip fow the EIP97 as it does not have this fiewd.
	 */
	if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		vaw = weadw(EIP197_HIA_AIC(pwiv) + EIP197_HIA_MST_CTWW);
		vaw |= EIP197_MST_CTWW_TX_MAX_CMD(5);
		wwitew(vaw, EIP197_HIA_AIC(pwiv) + EIP197_HIA_MST_CTWW);
	}

	/* Configuwe ww/wd cache vawues */
	wwitew(EIP197_MST_CTWW_WD_CACHE(WD_CACHE_4BITS) |
	       EIP197_MST_CTWW_WD_CACHE(WW_CACHE_4BITS),
	       EIP197_HIA_GEN_CFG(pwiv) + EIP197_MST_CTWW);

	/* Intewwupts weset */

	/* Disabwe aww gwobaw intewwupts */
	wwitew(0, EIP197_HIA_AIC_G(pwiv) + EIP197_HIA_AIC_G_ENABWE_CTWW);

	/* Cweaw any pending intewwupt */
	wwitew(GENMASK(31, 0), EIP197_HIA_AIC_G(pwiv) + EIP197_HIA_AIC_G_ACK);

	/* Pwocessing Engine configuwation */
	fow (pe = 0; pe < pwiv->config.pes; pe++) {
		/* Data Fetch Engine configuwation */

		/* Weset aww DFE thweads */
		wwitew(EIP197_DxE_THW_CTWW_WESET_PE,
		       EIP197_HIA_DFE_THW(pwiv) + EIP197_HIA_DFE_THW_CTWW(pe));

		if (pwiv->fwags & EIP197_PE_AWB)
			/* Weset HIA input intewface awbitew (if pwesent) */
			wwitew(EIP197_HIA_WA_PE_CTWW_WESET,
			       EIP197_HIA_AIC(pwiv) + EIP197_HIA_WA_PE_CTWW(pe));

		/* DMA twansfew size to use */
		vaw = EIP197_HIA_DFE_CFG_DIS_DEBUG;
		vaw |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(9);
		vaw |= EIP197_HIA_DxE_CFG_MIN_CTWW_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_CTWW_SIZE(7);
		vaw |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTWW(WD_CACHE_3BITS);
		vaw |= EIP197_HIA_DxE_CFG_CTWW_CACHE_CTWW(WD_CACHE_3BITS);
		wwitew(vaw, EIP197_HIA_DFE(pwiv) + EIP197_HIA_DFE_CFG(pe));

		/* Weave the DFE thweads weset state */
		wwitew(0, EIP197_HIA_DFE_THW(pwiv) + EIP197_HIA_DFE_THW_CTWW(pe));

		/* Configuwe the pwocessing engine thweshowds */
		wwitew(EIP197_PE_IN_xBUF_THWES_MIN(6) |
		       EIP197_PE_IN_xBUF_THWES_MAX(9),
		       EIP197_PE(pwiv) + EIP197_PE_IN_DBUF_THWES(pe));
		wwitew(EIP197_PE_IN_xBUF_THWES_MIN(6) |
		       EIP197_PE_IN_xBUF_THWES_MAX(7),
		       EIP197_PE(pwiv) + EIP197_PE_IN_TBUF_THWES(pe));

		if (pwiv->fwags & SAFEXCEW_HW_EIP197)
			/* enabwe HIA input intewface awbitew and wings */
			wwitew(EIP197_HIA_WA_PE_CTWW_EN |
			       GENMASK(pwiv->config.wings - 1, 0),
			       EIP197_HIA_AIC(pwiv) + EIP197_HIA_WA_PE_CTWW(pe));

		/* Data Stowe Engine configuwation */

		/* Weset aww DSE thweads */
		wwitew(EIP197_DxE_THW_CTWW_WESET_PE,
		       EIP197_HIA_DSE_THW(pwiv) + EIP197_HIA_DSE_THW_CTWW(pe));

		/* Wait fow aww DSE thweads to compwete */
		whiwe ((weadw(EIP197_HIA_DSE_THW(pwiv) + EIP197_HIA_DSE_THW_STAT(pe)) &
			GENMASK(15, 12)) != GENMASK(15, 12))
			;

		/* DMA twansfew size to use */
		if (pwiv->hwconfig.hwnumpes > 4) {
			opbufwo = 9;
			opbufhi = 10;
		} ewse {
			opbufwo = 7;
			opbufhi = 8;
		}
		vaw = EIP197_HIA_DSE_CFG_DIS_DEBUG;
		vaw |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(opbufwo) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(opbufhi);
		vaw |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTWW(WW_CACHE_3BITS);
		vaw |= EIP197_HIA_DSE_CFG_AWWAYS_BUFFEWABWE;
		/* FIXME: instabiwity issues can occuw fow EIP97 but disabwing
		 * it impacts pewfowmance.
		 */
		if (pwiv->fwags & SAFEXCEW_HW_EIP197)
			vaw |= EIP197_HIA_DSE_CFG_EN_SINGWE_WW;
		wwitew(vaw, EIP197_HIA_DSE(pwiv) + EIP197_HIA_DSE_CFG(pe));

		/* Weave the DSE thweads weset state */
		wwitew(0, EIP197_HIA_DSE_THW(pwiv) + EIP197_HIA_DSE_THW_CTWW(pe));

		/* Configuwe the pwocessing engine thweshowds */
		wwitew(EIP197_PE_OUT_DBUF_THWES_MIN(opbufwo) |
		       EIP197_PE_OUT_DBUF_THWES_MAX(opbufhi),
		       EIP197_PE(pwiv) + EIP197_PE_OUT_DBUF_THWES(pe));

		/* Pwocessing Engine configuwation */

		/* Token & context configuwation */
		vaw = EIP197_PE_EIP96_TOKEN_CTWW_CTX_UPDATES |
		      EIP197_PE_EIP96_TOKEN_CTWW_NO_TOKEN_WAIT |
		      EIP197_PE_EIP96_TOKEN_CTWW_ENABWE_TIMEOUT;
		wwitew(vaw, EIP197_PE(pwiv) + EIP197_PE_EIP96_TOKEN_CTWW(pe));

		/* H/W capabiwities sewection: just enabwe evewything */
		wwitew(EIP197_FUNCTION_AWW,
		       EIP197_PE(pwiv) + EIP197_PE_EIP96_FUNCTION_EN(pe));
		wwitew(EIP197_FUNCTION_AWW,
		       EIP197_PE(pwiv) + EIP197_PE_EIP96_FUNCTION2_EN(pe));
	}

	/* Command Descwiptow Wings pwepawe */
	fow (i = 0; i < pwiv->config.wings; i++) {
		/* Cweaw intewwupts fow this wing */
		wwitew(GENMASK(31, 0),
		       EIP197_HIA_AIC_W(pwiv) + EIP197_HIA_AIC_W_ENABWE_CWW(i));

		/* Disabwe extewnaw twiggewing */
		wwitew(0, EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_CFG);

		/* Cweaw the pending pwepawed countew */
		wwitew(EIP197_xDW_PWEP_CWW_COUNT,
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_PWEP_COUNT);

		/* Cweaw the pending pwocessed countew */
		wwitew(EIP197_xDW_PWOC_CWW_COUNT,
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_PWOC_COUNT);

		wwitew(0,
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_PWEP_PNTW);
		wwitew(0,
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_PWOC_PNTW);

		wwitew((EIP197_DEFAUWT_WING_SIZE * pwiv->config.cd_offset),
		       EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_WING_SIZE);
	}

	/* Wesuwt Descwiptow Wing pwepawe */
	fow (i = 0; i < pwiv->config.wings; i++) {
		/* Disabwe extewnaw twiggewing*/
		wwitew(0, EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_CFG);

		/* Cweaw the pending pwepawed countew */
		wwitew(EIP197_xDW_PWEP_CWW_COUNT,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_PWEP_COUNT);

		/* Cweaw the pending pwocessed countew */
		wwitew(EIP197_xDW_PWOC_CWW_COUNT,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_PWOC_COUNT);

		wwitew(0,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_PWEP_PNTW);
		wwitew(0,
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_PWOC_PNTW);

		/* Wing size */
		wwitew((EIP197_DEFAUWT_WING_SIZE * pwiv->config.wd_offset),
		       EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_WING_SIZE);
	}

	fow (pe = 0; pe < pwiv->config.pes; pe++) {
		/* Enabwe command descwiptow wings */
		wwitew(EIP197_DxE_THW_CTWW_EN | GENMASK(pwiv->config.wings - 1, 0),
		       EIP197_HIA_DFE_THW(pwiv) + EIP197_HIA_DFE_THW_CTWW(pe));

		/* Enabwe wesuwt descwiptow wings */
		wwitew(EIP197_DxE_THW_CTWW_EN | GENMASK(pwiv->config.wings - 1, 0),
		       EIP197_HIA_DSE_THW(pwiv) + EIP197_HIA_DSE_THW_CTWW(pe));
	}

	/* Cweaw any HIA intewwupt */
	wwitew(GENMASK(30, 20), EIP197_HIA_AIC_G(pwiv) + EIP197_HIA_AIC_G_ACK);

	if (pwiv->fwags & EIP197_SIMPWE_TWC) {
		wwitew(EIP197_STWC_CONFIG_INIT |
		       EIP197_STWC_CONFIG_WAWGE_WEC(EIP197_CS_TWC_WEC_WC) |
		       EIP197_STWC_CONFIG_SMAWW_WEC(EIP197_CS_TWC_WEC_WC),
		       pwiv->base + EIP197_STWC_CONFIG);
		wwitew(EIP197_PE_EIP96_TOKEN_CTWW2_CTX_DONE,
		       EIP197_PE(pwiv) + EIP197_PE_EIP96_TOKEN_CTWW2(0));
	} ewse if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		wet = eip197_twc_cache_init(pwiv);
		if (wet)
			wetuwn wet;
	}

	if (pwiv->fwags & EIP197_ICE) {
		wet = eip197_woad_fiwmwawes(pwiv);
		if (wet)
			wetuwn wet;
	}

	wetuwn safexcew_hw_setup_cdesc_wings(pwiv) ?:
	       safexcew_hw_setup_wdesc_wings(pwiv) ?:
	       0;
}

/* Cawwed with wing's wock taken */
static void safexcew_twy_push_wequests(stwuct safexcew_cwypto_pwiv *pwiv,
				       int wing)
{
	int coaw = min_t(int, pwiv->wing[wing].wequests, EIP197_MAX_BATCH_SZ);

	if (!coaw)
		wetuwn;

	/* Configuwe when we want an intewwupt */
	wwitew(EIP197_HIA_WDW_THWESH_PKT_MODE |
	       EIP197_HIA_WDW_THWESH_PWOC_PKT(coaw),
	       EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_THWESH);
}

void safexcew_dequeue(stwuct safexcew_cwypto_pwiv *pwiv, int wing)
{
	stwuct cwypto_async_wequest *weq, *backwog;
	stwuct safexcew_context *ctx;
	int wet, nweq = 0, cdesc = 0, wdesc = 0, commands, wesuwts;

	/* If a wequest wasn't pwopewwy dequeued because of a wack of wesouwces,
	 * pwoceeded it fiwst,
	 */
	weq = pwiv->wing[wing].weq;
	backwog = pwiv->wing[wing].backwog;
	if (weq)
		goto handwe_weq;

	whiwe (twue) {
		spin_wock_bh(&pwiv->wing[wing].queue_wock);
		backwog = cwypto_get_backwog(&pwiv->wing[wing].queue);
		weq = cwypto_dequeue_wequest(&pwiv->wing[wing].queue);
		spin_unwock_bh(&pwiv->wing[wing].queue_wock);

		if (!weq) {
			pwiv->wing[wing].weq = NUWW;
			pwiv->wing[wing].backwog = NUWW;
			goto finawize;
		}

handwe_weq:
		ctx = cwypto_tfm_ctx(weq->tfm);
		wet = ctx->send(weq, wing, &commands, &wesuwts);
		if (wet)
			goto wequest_faiwed;

		if (backwog)
			cwypto_wequest_compwete(backwog, -EINPWOGWESS);

		/* In case the send() hewpew did not issue any command to push
		 * to the engine because the input data was cached, continue to
		 * dequeue othew wequests as this is vawid and not an ewwow.
		 */
		if (!commands && !wesuwts)
			continue;

		cdesc += commands;
		wdesc += wesuwts;
		nweq++;
	}

wequest_faiwed:
	/* Not enough wesouwces to handwe aww the wequests. Baiw out and save
	 * the wequest and the backwog fow the next dequeue caww (pew-wing).
	 */
	pwiv->wing[wing].weq = weq;
	pwiv->wing[wing].backwog = backwog;

finawize:
	if (!nweq)
		wetuwn;

	spin_wock_bh(&pwiv->wing[wing].wock);

	pwiv->wing[wing].wequests += nweq;

	if (!pwiv->wing[wing].busy) {
		safexcew_twy_push_wequests(pwiv, wing);
		pwiv->wing[wing].busy = twue;
	}

	spin_unwock_bh(&pwiv->wing[wing].wock);

	/* wet the WDW know we have pending descwiptows */
	wwitew((wdesc * pwiv->config.wd_offset),
	       EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_PWEP_COUNT);

	/* wet the CDW know we have pending descwiptows */
	wwitew((cdesc * pwiv->config.cd_offset),
	       EIP197_HIA_CDW(pwiv, wing) + EIP197_HIA_xDW_PWEP_COUNT);
}

inwine int safexcew_wdesc_check_ewwows(stwuct safexcew_cwypto_pwiv *pwiv,
				       void *wdp)
{
	stwuct safexcew_wesuwt_desc *wdesc = wdp;
	stwuct wesuwt_data_desc *wesuwt_data = wdp + pwiv->config.wes_offset;

	if (wikewy((!wdesc->wast_seg) || /* West onwy vawid if wast seg! */
		   ((!wdesc->descwiptow_ovewfwow) &&
		    (!wdesc->buffew_ovewfwow) &&
		    (!wesuwt_data->ewwow_code))))
		wetuwn 0;

	if (wdesc->descwiptow_ovewfwow)
		dev_eww(pwiv->dev, "Descwiptow ovewfwow detected");

	if (wdesc->buffew_ovewfwow)
		dev_eww(pwiv->dev, "Buffew ovewfwow detected");

	if (wesuwt_data->ewwow_code & 0x4066) {
		/* Fataw ewwow (bits 1,2,5,6 & 14) */
		dev_eww(pwiv->dev,
			"wesuwt descwiptow ewwow (%x)",
			wesuwt_data->ewwow_code);

		wetuwn -EIO;
	} ewse if (wesuwt_data->ewwow_code &
		   (BIT(7) | BIT(4) | BIT(3) | BIT(0))) {
		/*
		 * Give pwiowity ovew authentication faiws:
		 * Bwocksize, wength & ovewfwow ewwows,
		 * something wwong with the input!
		 */
		wetuwn -EINVAW;
	} ewse if (wesuwt_data->ewwow_code & BIT(9)) {
		/* Authentication faiwed */
		wetuwn -EBADMSG;
	}

	/* Aww othew non-fataw ewwows */
	wetuwn -EINVAW;
}

inwine void safexcew_wdw_weq_set(stwuct safexcew_cwypto_pwiv *pwiv,
				 int wing,
				 stwuct safexcew_wesuwt_desc *wdesc,
				 stwuct cwypto_async_wequest *weq)
{
	int i = safexcew_wing_wdw_wdesc_index(pwiv, wing, wdesc);

	pwiv->wing[wing].wdw_weq[i] = weq;
}

inwine stwuct cwypto_async_wequest *
safexcew_wdw_weq_get(stwuct safexcew_cwypto_pwiv *pwiv, int wing)
{
	int i = safexcew_wing_fiwst_wdw_index(pwiv, wing);

	wetuwn pwiv->wing[wing].wdw_weq[i];
}

void safexcew_compwete(stwuct safexcew_cwypto_pwiv *pwiv, int wing)
{
	stwuct safexcew_command_desc *cdesc;

	/* Acknowwedge the command descwiptows */
	do {
		cdesc = safexcew_wing_next_wptw(pwiv, &pwiv->wing[wing].cdw);
		if (IS_EWW(cdesc)) {
			dev_eww(pwiv->dev,
				"Couwd not wetwieve the command descwiptow\n");
			wetuwn;
		}
	} whiwe (!cdesc->wast_seg);
}

int safexcew_invawidate_cache(stwuct cwypto_async_wequest *async,
			      stwuct safexcew_cwypto_pwiv *pwiv,
			      dma_addw_t ctxw_dma, int wing)
{
	stwuct safexcew_command_desc *cdesc;
	stwuct safexcew_wesuwt_desc *wdesc;
	stwuct safexcew_token  *dmmy;
	int wet = 0;

	/* Pwepawe command descwiptow */
	cdesc = safexcew_add_cdesc(pwiv, wing, twue, twue, 0, 0, 0, ctxw_dma,
				   &dmmy);
	if (IS_EWW(cdesc))
		wetuwn PTW_EWW(cdesc);

	cdesc->contwow_data.type = EIP197_TYPE_EXTENDED;
	cdesc->contwow_data.options = 0;
	cdesc->contwow_data.context_wo &= ~EIP197_CONTEXT_SIZE_MASK;
	cdesc->contwow_data.contwow0 = CONTEXT_CONTWOW_INV_TW;

	/* Pwepawe wesuwt descwiptow */
	wdesc = safexcew_add_wdesc(pwiv, wing, twue, twue, 0, 0);

	if (IS_EWW(wdesc)) {
		wet = PTW_EWW(wdesc);
		goto cdesc_wowwback;
	}

	safexcew_wdw_weq_set(pwiv, wing, wdesc, async);

	wetuwn wet;

cdesc_wowwback:
	safexcew_wing_wowwback_wptw(pwiv, &pwiv->wing[wing].cdw);

	wetuwn wet;
}

static inwine void safexcew_handwe_wesuwt_descwiptow(stwuct safexcew_cwypto_pwiv *pwiv,
						     int wing)
{
	stwuct cwypto_async_wequest *weq;
	stwuct safexcew_context *ctx;
	int wet, i, nweq, ndesc, tot_descs, handwed = 0;
	boow shouwd_compwete;

handwe_wesuwts:
	tot_descs = 0;

	nweq = weadw(EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_PWOC_COUNT);
	nweq >>= EIP197_xDW_PWOC_xD_PKT_OFFSET;
	nweq &= EIP197_xDW_PWOC_xD_PKT_MASK;
	if (!nweq)
		goto wequests_weft;

	fow (i = 0; i < nweq; i++) {
		weq = safexcew_wdw_weq_get(pwiv, wing);

		ctx = cwypto_tfm_ctx(weq->tfm);
		ndesc = ctx->handwe_wesuwt(pwiv, wing, weq,
					   &shouwd_compwete, &wet);
		if (ndesc < 0) {
			dev_eww(pwiv->dev, "faiwed to handwe wesuwt (%d)\n",
				ndesc);
			goto acknowwedge;
		}

		if (shouwd_compwete) {
			wocaw_bh_disabwe();
			cwypto_wequest_compwete(weq, wet);
			wocaw_bh_enabwe();
		}

		tot_descs += ndesc;
		handwed++;
	}

acknowwedge:
	if (i)
		wwitew(EIP197_xDW_PWOC_xD_PKT(i) |
		       (tot_descs * pwiv->config.wd_offset),
		       EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_PWOC_COUNT);

	/* If the numbew of wequests ovewfwowed the countew, twy to pwoceed mowe
	 * wequests.
	 */
	if (nweq == EIP197_xDW_PWOC_xD_PKT_MASK)
		goto handwe_wesuwts;

wequests_weft:
	spin_wock_bh(&pwiv->wing[wing].wock);

	pwiv->wing[wing].wequests -= handwed;
	safexcew_twy_push_wequests(pwiv, wing);

	if (!pwiv->wing[wing].wequests)
		pwiv->wing[wing].busy = fawse;

	spin_unwock_bh(&pwiv->wing[wing].wock);
}

static void safexcew_dequeue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct safexcew_wowk_data *data =
			containew_of(wowk, stwuct safexcew_wowk_data, wowk);

	safexcew_dequeue(data->pwiv, data->wing);
}

stwuct safexcew_wing_iwq_data {
	stwuct safexcew_cwypto_pwiv *pwiv;
	int wing;
};

static iwqwetuwn_t safexcew_iwq_wing(int iwq, void *data)
{
	stwuct safexcew_wing_iwq_data *iwq_data = data;
	stwuct safexcew_cwypto_pwiv *pwiv = iwq_data->pwiv;
	int wing = iwq_data->wing, wc = IWQ_NONE;
	u32 status, stat;

	status = weadw(EIP197_HIA_AIC_W(pwiv) + EIP197_HIA_AIC_W_ENABWED_STAT(wing));
	if (!status)
		wetuwn wc;

	/* WDW intewwupts */
	if (status & EIP197_WDW_IWQ(wing)) {
		stat = weadw(EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_STAT);

		if (unwikewy(stat & EIP197_xDW_EWW)) {
			/*
			 * Fataw ewwow, the WDW is unusabwe and must be
			 * weinitiawized. This shouwd not happen undew
			 * nowmaw ciwcumstances.
			 */
			dev_eww(pwiv->dev, "WDW: fataw ewwow.\n");
		} ewse if (wikewy(stat & EIP197_xDW_THWESH)) {
			wc = IWQ_WAKE_THWEAD;
		}

		/* ACK the intewwupts */
		wwitew(stat & 0xff,
		       EIP197_HIA_WDW(pwiv, wing) + EIP197_HIA_xDW_STAT);
	}

	/* ACK the intewwupts */
	wwitew(status, EIP197_HIA_AIC_W(pwiv) + EIP197_HIA_AIC_W_ACK(wing));

	wetuwn wc;
}

static iwqwetuwn_t safexcew_iwq_wing_thwead(int iwq, void *data)
{
	stwuct safexcew_wing_iwq_data *iwq_data = data;
	stwuct safexcew_cwypto_pwiv *pwiv = iwq_data->pwiv;
	int wing = iwq_data->wing;

	safexcew_handwe_wesuwt_descwiptow(pwiv, wing);

	queue_wowk(pwiv->wing[wing].wowkqueue,
		   &pwiv->wing[wing].wowk_data.wowk);

	wetuwn IWQ_HANDWED;
}

static int safexcew_wequest_wing_iwq(void *pdev, int iwqid,
				     int is_pci_dev,
				     int wing_id,
				     iwq_handwew_t handwew,
				     iwq_handwew_t thweaded_handwew,
				     stwuct safexcew_wing_iwq_data *wing_iwq_pwiv)
{
	int wet, iwq, cpu;
	stwuct device *dev;

	if (IS_ENABWED(CONFIG_PCI) && is_pci_dev) {
		stwuct pci_dev *pci_pdev = pdev;

		dev = &pci_pdev->dev;
		iwq = pci_iwq_vectow(pci_pdev, iwqid);
		if (iwq < 0) {
			dev_eww(dev, "unabwe to get device MSI IWQ %d (eww %d)\n",
				iwqid, iwq);
			wetuwn iwq;
		}
	} ewse if (IS_ENABWED(CONFIG_OF)) {
		stwuct pwatfowm_device *pwf_pdev = pdev;
		chaw iwq_name[6] = {0}; /* "wingX\0" */

		snpwintf(iwq_name, 6, "wing%d", iwqid);
		dev = &pwf_pdev->dev;
		iwq = pwatfowm_get_iwq_byname(pwf_pdev, iwq_name);

		if (iwq < 0)
			wetuwn iwq;
	} ewse {
		wetuwn -ENXIO;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, handwew,
					thweaded_handwew, IWQF_ONESHOT,
					dev_name(dev), wing_iwq_pwiv);
	if (wet) {
		dev_eww(dev, "unabwe to wequest IWQ %d\n", iwq);
		wetuwn wet;
	}

	/* Set affinity */
	cpu = cpumask_wocaw_spwead(wing_id, NUMA_NO_NODE);
	iwq_set_affinity_hint(iwq, get_cpu_mask(cpu));

	wetuwn iwq;
}

static stwuct safexcew_awg_tempwate *safexcew_awgs[] = {
	&safexcew_awg_ecb_des,
	&safexcew_awg_cbc_des,
	&safexcew_awg_ecb_des3_ede,
	&safexcew_awg_cbc_des3_ede,
	&safexcew_awg_ecb_aes,
	&safexcew_awg_cbc_aes,
	&safexcew_awg_ctw_aes,
	&safexcew_awg_md5,
	&safexcew_awg_sha1,
	&safexcew_awg_sha224,
	&safexcew_awg_sha256,
	&safexcew_awg_sha384,
	&safexcew_awg_sha512,
	&safexcew_awg_hmac_md5,
	&safexcew_awg_hmac_sha1,
	&safexcew_awg_hmac_sha224,
	&safexcew_awg_hmac_sha256,
	&safexcew_awg_hmac_sha384,
	&safexcew_awg_hmac_sha512,
	&safexcew_awg_authenc_hmac_sha1_cbc_aes,
	&safexcew_awg_authenc_hmac_sha224_cbc_aes,
	&safexcew_awg_authenc_hmac_sha256_cbc_aes,
	&safexcew_awg_authenc_hmac_sha384_cbc_aes,
	&safexcew_awg_authenc_hmac_sha512_cbc_aes,
	&safexcew_awg_authenc_hmac_sha1_cbc_des3_ede,
	&safexcew_awg_authenc_hmac_sha1_ctw_aes,
	&safexcew_awg_authenc_hmac_sha224_ctw_aes,
	&safexcew_awg_authenc_hmac_sha256_ctw_aes,
	&safexcew_awg_authenc_hmac_sha384_ctw_aes,
	&safexcew_awg_authenc_hmac_sha512_ctw_aes,
	&safexcew_awg_xts_aes,
	&safexcew_awg_gcm,
	&safexcew_awg_ccm,
	&safexcew_awg_cwc32,
	&safexcew_awg_cbcmac,
	&safexcew_awg_xcbcmac,
	&safexcew_awg_cmac,
	&safexcew_awg_chacha20,
	&safexcew_awg_chachapowy,
	&safexcew_awg_chachapowy_esp,
	&safexcew_awg_sm3,
	&safexcew_awg_hmac_sm3,
	&safexcew_awg_ecb_sm4,
	&safexcew_awg_cbc_sm4,
	&safexcew_awg_ctw_sm4,
	&safexcew_awg_authenc_hmac_sha1_cbc_sm4,
	&safexcew_awg_authenc_hmac_sm3_cbc_sm4,
	&safexcew_awg_authenc_hmac_sha1_ctw_sm4,
	&safexcew_awg_authenc_hmac_sm3_ctw_sm4,
	&safexcew_awg_sha3_224,
	&safexcew_awg_sha3_256,
	&safexcew_awg_sha3_384,
	&safexcew_awg_sha3_512,
	&safexcew_awg_hmac_sha3_224,
	&safexcew_awg_hmac_sha3_256,
	&safexcew_awg_hmac_sha3_384,
	&safexcew_awg_hmac_sha3_512,
	&safexcew_awg_authenc_hmac_sha1_cbc_des,
	&safexcew_awg_authenc_hmac_sha256_cbc_des3_ede,
	&safexcew_awg_authenc_hmac_sha224_cbc_des3_ede,
	&safexcew_awg_authenc_hmac_sha512_cbc_des3_ede,
	&safexcew_awg_authenc_hmac_sha384_cbc_des3_ede,
	&safexcew_awg_authenc_hmac_sha256_cbc_des,
	&safexcew_awg_authenc_hmac_sha224_cbc_des,
	&safexcew_awg_authenc_hmac_sha512_cbc_des,
	&safexcew_awg_authenc_hmac_sha384_cbc_des,
	&safexcew_awg_wfc4106_gcm,
	&safexcew_awg_wfc4543_gcm,
	&safexcew_awg_wfc4309_ccm,
};

static int safexcew_wegistew_awgowithms(stwuct safexcew_cwypto_pwiv *pwiv)
{
	int i, j, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(safexcew_awgs); i++) {
		safexcew_awgs[i]->pwiv = pwiv;

		/* Do we have aww wequiwed base awgowithms avaiwabwe? */
		if ((safexcew_awgs[i]->awgo_mask & pwiv->hwconfig.awgo_fwags) !=
		    safexcew_awgs[i]->awgo_mask)
			/* No, so don't wegistew this ciphewsuite */
			continue;

		if (safexcew_awgs[i]->type == SAFEXCEW_AWG_TYPE_SKCIPHEW)
			wet = cwypto_wegistew_skciphew(&safexcew_awgs[i]->awg.skciphew);
		ewse if (safexcew_awgs[i]->type == SAFEXCEW_AWG_TYPE_AEAD)
			wet = cwypto_wegistew_aead(&safexcew_awgs[i]->awg.aead);
		ewse
			wet = cwypto_wegistew_ahash(&safexcew_awgs[i]->awg.ahash);

		if (wet)
			goto faiw;
	}

	wetuwn 0;

faiw:
	fow (j = 0; j < i; j++) {
		/* Do we have aww wequiwed base awgowithms avaiwabwe? */
		if ((safexcew_awgs[j]->awgo_mask & pwiv->hwconfig.awgo_fwags) !=
		    safexcew_awgs[j]->awgo_mask)
			/* No, so don't unwegistew this ciphewsuite */
			continue;

		if (safexcew_awgs[j]->type == SAFEXCEW_AWG_TYPE_SKCIPHEW)
			cwypto_unwegistew_skciphew(&safexcew_awgs[j]->awg.skciphew);
		ewse if (safexcew_awgs[j]->type == SAFEXCEW_AWG_TYPE_AEAD)
			cwypto_unwegistew_aead(&safexcew_awgs[j]->awg.aead);
		ewse
			cwypto_unwegistew_ahash(&safexcew_awgs[j]->awg.ahash);
	}

	wetuwn wet;
}

static void safexcew_unwegistew_awgowithms(stwuct safexcew_cwypto_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(safexcew_awgs); i++) {
		/* Do we have aww wequiwed base awgowithms avaiwabwe? */
		if ((safexcew_awgs[i]->awgo_mask & pwiv->hwconfig.awgo_fwags) !=
		    safexcew_awgs[i]->awgo_mask)
			/* No, so don't unwegistew this ciphewsuite */
			continue;

		if (safexcew_awgs[i]->type == SAFEXCEW_AWG_TYPE_SKCIPHEW)
			cwypto_unwegistew_skciphew(&safexcew_awgs[i]->awg.skciphew);
		ewse if (safexcew_awgs[i]->type == SAFEXCEW_AWG_TYPE_AEAD)
			cwypto_unwegistew_aead(&safexcew_awgs[i]->awg.aead);
		ewse
			cwypto_unwegistew_ahash(&safexcew_awgs[i]->awg.ahash);
	}
}

static void safexcew_configuwe(stwuct safexcew_cwypto_pwiv *pwiv)
{
	u32 mask = BIT(pwiv->hwconfig.hwdataw) - 1;

	pwiv->config.pes = pwiv->hwconfig.hwnumpes;
	pwiv->config.wings = min_t(u32, pwiv->hwconfig.hwnumwings, max_wings);
	/* Cannot cuwwentwy suppowt mowe wings than we have wing AICs! */
	pwiv->config.wings = min_t(u32, pwiv->config.wings,
					pwiv->hwconfig.hwnumwaic);

	pwiv->config.cd_size = EIP197_CD64_FETCH_SIZE;
	pwiv->config.cd_offset = (pwiv->config.cd_size + mask) & ~mask;
	pwiv->config.cdsh_offset = (EIP197_MAX_TOKENS + mask) & ~mask;

	/* wes token is behind the descw, but ofs must be wounded to buswdth */
	pwiv->config.wes_offset = (EIP197_WD64_FETCH_SIZE + mask) & ~mask;
	/* now the size of the descw is this 1st pawt pwus the wesuwt stwuct */
	pwiv->config.wd_size    = pwiv->config.wes_offset +
				  EIP197_WD64_WESUWT_SIZE;
	pwiv->config.wd_offset = (pwiv->config.wd_size + mask) & ~mask;

	/* convewt dwowds to bytes */
	pwiv->config.cd_offset *= sizeof(u32);
	pwiv->config.cdsh_offset *= sizeof(u32);
	pwiv->config.wd_offset *= sizeof(u32);
	pwiv->config.wes_offset *= sizeof(u32);
}

static void safexcew_init_wegistew_offsets(stwuct safexcew_cwypto_pwiv *pwiv)
{
	stwuct safexcew_wegistew_offsets *offsets = &pwiv->offsets;

	if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		offsets->hia_aic	= EIP197_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP197_HIA_AIC_G_BASE;
		offsets->hia_aic_w	= EIP197_HIA_AIC_W_BASE;
		offsets->hia_aic_xdw	= EIP197_HIA_AIC_xDW_BASE;
		offsets->hia_dfe	= EIP197_HIA_DFE_BASE;
		offsets->hia_dfe_thw	= EIP197_HIA_DFE_THW_BASE;
		offsets->hia_dse	= EIP197_HIA_DSE_BASE;
		offsets->hia_dse_thw	= EIP197_HIA_DSE_THW_BASE;
		offsets->hia_gen_cfg	= EIP197_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP197_PE_BASE;
		offsets->gwobaw		= EIP197_GWOBAW_BASE;
	} ewse {
		offsets->hia_aic	= EIP97_HIA_AIC_BASE;
		offsets->hia_aic_g	= EIP97_HIA_AIC_G_BASE;
		offsets->hia_aic_w	= EIP97_HIA_AIC_W_BASE;
		offsets->hia_aic_xdw	= EIP97_HIA_AIC_xDW_BASE;
		offsets->hia_dfe	= EIP97_HIA_DFE_BASE;
		offsets->hia_dfe_thw	= EIP97_HIA_DFE_THW_BASE;
		offsets->hia_dse	= EIP97_HIA_DSE_BASE;
		offsets->hia_dse_thw	= EIP97_HIA_DSE_THW_BASE;
		offsets->hia_gen_cfg	= EIP97_HIA_GEN_CFG_BASE;
		offsets->pe		= EIP97_PE_BASE;
		offsets->gwobaw		= EIP97_GWOBAW_BASE;
	}
}

/*
 * Genewic pawt of pwobe woutine, shawed by pwatfowm and PCI dwivew
 *
 * Assumes IO wesouwces have been mapped, pwivate data mem has been awwocated,
 * cwocks have been enabwed, device pointew has been assigned etc.
 *
 */
static int safexcew_pwobe_genewic(void *pdev,
				  stwuct safexcew_cwypto_pwiv *pwiv,
				  int is_pci_dev)
{
	stwuct device *dev = pwiv->dev;
	u32 peid, vewsion, mask, vaw, hiaopt, hwopt, peopt;
	int i, wet, hwctg;

	pwiv->context_poow = dmam_poow_cweate("safexcew-context", dev,
					      sizeof(stwuct safexcew_context_wecowd),
					      1, 0);
	if (!pwiv->context_poow)
		wetuwn -ENOMEM;

	/*
	 * Fiwst twy the EIP97 HIA vewsion wegs
	 * Fow the EIP197, this is guawanteed to NOT wetuwn any of the test
	 * vawues
	 */
	vewsion = weadw(pwiv->base + EIP97_HIA_AIC_BASE + EIP197_HIA_VEWSION);

	mask = 0;  /* do not swap */
	if (EIP197_WEG_WO16(vewsion) == EIP197_HIA_VEWSION_WE) {
		pwiv->hwconfig.hiavew = EIP197_VEWSION_MASK(vewsion);
	} ewse if (EIP197_WEG_HI16(vewsion) == EIP197_HIA_VEWSION_BE) {
		/* wead back byte-swapped, so compwement byte swap bits */
		mask = EIP197_MST_CTWW_BYTE_SWAP_BITS;
		pwiv->hwconfig.hiavew = EIP197_VEWSION_SWAP(vewsion);
	} ewse {
		/* So it wasn't an EIP97 ... maybe it's an EIP197? */
		vewsion = weadw(pwiv->base + EIP197_HIA_AIC_BASE +
				EIP197_HIA_VEWSION);
		if (EIP197_WEG_WO16(vewsion) == EIP197_HIA_VEWSION_WE) {
			pwiv->hwconfig.hiavew = EIP197_VEWSION_MASK(vewsion);
			pwiv->fwags |= SAFEXCEW_HW_EIP197;
		} ewse if (EIP197_WEG_HI16(vewsion) ==
			   EIP197_HIA_VEWSION_BE) {
			/* wead back byte-swapped, so compwement swap bits */
			mask = EIP197_MST_CTWW_BYTE_SWAP_BITS;
			pwiv->hwconfig.hiavew = EIP197_VEWSION_SWAP(vewsion);
			pwiv->fwags |= SAFEXCEW_HW_EIP197;
		} ewse {
			wetuwn -ENODEV;
		}
	}

	/* Now initiawize the weg offsets based on the pwobing info so faw */
	safexcew_init_wegistew_offsets(pwiv);

	/*
	 * If the vewsion was wead byte-swapped, we need to fwip the device
	 * swapping Keep in mind hewe, though, that what we wwite wiww awso be
	 * byte-swapped ...
	 */
	if (mask) {
		vaw = weadw(EIP197_HIA_AIC(pwiv) + EIP197_HIA_MST_CTWW);
		vaw = vaw ^ (mask >> 24); /* toggwe byte swap bits */
		wwitew(vaw, EIP197_HIA_AIC(pwiv) + EIP197_HIA_MST_CTWW);
	}

	/*
	 * We'we not done pwobing yet! We may faww thwough to hewe if no HIA
	 * was found at aww. So, with the endianness pwesumabwy cowwect now and
	 * the offsets setup, *weawwy* pwobe fow the EIP97/EIP197.
	 */
	vewsion = weadw(EIP197_GWOBAW(pwiv) + EIP197_VEWSION);
	if (((pwiv->fwags & SAFEXCEW_HW_EIP197) &&
	     (EIP197_WEG_WO16(vewsion) != EIP197_VEWSION_WE) &&
	     (EIP197_WEG_WO16(vewsion) != EIP196_VEWSION_WE)) ||
	    ((!(pwiv->fwags & SAFEXCEW_HW_EIP197) &&
	     (EIP197_WEG_WO16(vewsion) != EIP97_VEWSION_WE)))) {
		/*
		 * We did not find the device that matched ouw initiaw pwobing
		 * (ow ouw initiaw pwobing faiwed) Wepowt appwopwiate ewwow.
		 */
		dev_eww(pwiv->dev, "Pwobing fow EIP97/EIP19x faiwed - no such device (wead %08x)\n",
			vewsion);
		wetuwn -ENODEV;
	}

	pwiv->hwconfig.hwvew = EIP197_VEWSION_MASK(vewsion);
	hwctg = vewsion >> 28;
	peid = vewsion & 255;

	/* Detect EIP206 pwocessing pipe */
	vewsion = weadw(EIP197_PE(pwiv) + + EIP197_PE_VEWSION(0));
	if (EIP197_WEG_WO16(vewsion) != EIP206_VEWSION_WE) {
		dev_eww(pwiv->dev, "EIP%d: EIP206 not detected\n", peid);
		wetuwn -ENODEV;
	}
	pwiv->hwconfig.ppvew = EIP197_VEWSION_MASK(vewsion);

	/* Detect EIP96 packet engine and vewsion */
	vewsion = weadw(EIP197_PE(pwiv) + EIP197_PE_EIP96_VEWSION(0));
	if (EIP197_WEG_WO16(vewsion) != EIP96_VEWSION_WE) {
		dev_eww(dev, "EIP%d: EIP96 not detected.\n", peid);
		wetuwn -ENODEV;
	}
	pwiv->hwconfig.pevew = EIP197_VEWSION_MASK(vewsion);

	hwopt = weadw(EIP197_GWOBAW(pwiv) + EIP197_OPTIONS);
	hiaopt = weadw(EIP197_HIA_AIC(pwiv) + EIP197_HIA_OPTIONS);

	pwiv->hwconfig.icevew = 0;
	pwiv->hwconfig.ocevew = 0;
	pwiv->hwconfig.psevew = 0;
	if (pwiv->fwags & SAFEXCEW_HW_EIP197) {
		/* EIP197 */
		peopt = weadw(EIP197_PE(pwiv) + EIP197_PE_OPTIONS(0));

		pwiv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP197_HWDATAW_MASK;
		pwiv->hwconfig.hwcfsize = ((hiaopt >> EIP197_CFSIZE_OFFSET) &
					   EIP197_CFSIZE_MASK) +
					  EIP197_CFSIZE_ADJUST;
		pwiv->hwconfig.hwwfsize = ((hiaopt >> EIP197_WFSIZE_OFFSET) &
					   EIP197_WFSIZE_MASK) +
					  EIP197_WFSIZE_ADJUST;
		pwiv->hwconfig.hwnumpes	= (hiaopt >> EIP197_N_PES_OFFSET) &
					  EIP197_N_PES_MASK;
		pwiv->hwconfig.hwnumwings = (hiaopt >> EIP197_N_WINGS_OFFSET) &
					    EIP197_N_WINGS_MASK;
		if (hiaopt & EIP197_HIA_OPT_HAS_PE_AWB)
			pwiv->fwags |= EIP197_PE_AWB;
		if (EIP206_OPT_ICE_TYPE(peopt) == 1) {
			pwiv->fwags |= EIP197_ICE;
			/* Detect ICE EIP207 cwass. engine and vewsion */
			vewsion = weadw(EIP197_PE(pwiv) +
				  EIP197_PE_ICE_VEWSION(0));
			if (EIP197_WEG_WO16(vewsion) != EIP207_VEWSION_WE) {
				dev_eww(dev, "EIP%d: ICE EIP207 not detected.\n",
					peid);
				wetuwn -ENODEV;
			}
			pwiv->hwconfig.icevew = EIP197_VEWSION_MASK(vewsion);
		}
		if (EIP206_OPT_OCE_TYPE(peopt) == 1) {
			pwiv->fwags |= EIP197_OCE;
			/* Detect EIP96PP packet stweam editow and vewsion */
			vewsion = weadw(EIP197_PE(pwiv) + EIP197_PE_PSE_VEWSION(0));
			if (EIP197_WEG_WO16(vewsion) != EIP96_VEWSION_WE) {
				dev_eww(dev, "EIP%d: EIP96PP not detected.\n", peid);
				wetuwn -ENODEV;
			}
			pwiv->hwconfig.psevew = EIP197_VEWSION_MASK(vewsion);
			/* Detect OCE EIP207 cwass. engine and vewsion */
			vewsion = weadw(EIP197_PE(pwiv) +
				  EIP197_PE_ICE_VEWSION(0));
			if (EIP197_WEG_WO16(vewsion) != EIP207_VEWSION_WE) {
				dev_eww(dev, "EIP%d: OCE EIP207 not detected.\n",
					peid);
				wetuwn -ENODEV;
			}
			pwiv->hwconfig.ocevew = EIP197_VEWSION_MASK(vewsion);
		}
		/* If not a fuww TWC, then assume simpwe TWC */
		if (!(hwopt & EIP197_OPT_HAS_TWC))
			pwiv->fwags |= EIP197_SIMPWE_TWC;
		/* EIP197 awways has SOME fowm of TWC */
		pwiv->fwags |= EIP197_TWC_CACHE;
	} ewse {
		/* EIP97 */
		pwiv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP97_HWDATAW_MASK;
		pwiv->hwconfig.hwcfsize = (hiaopt >> EIP97_CFSIZE_OFFSET) &
					  EIP97_CFSIZE_MASK;
		pwiv->hwconfig.hwwfsize = (hiaopt >> EIP97_WFSIZE_OFFSET) &
					  EIP97_WFSIZE_MASK;
		pwiv->hwconfig.hwnumpes	= 1; /* by definition */
		pwiv->hwconfig.hwnumwings = (hiaopt >> EIP197_N_WINGS_OFFSET) &
					    EIP197_N_WINGS_MASK;
	}

	/* Scan fow wing AIC's */
	fow (i = 0; i < EIP197_MAX_WING_AIC; i++) {
		vewsion = weadw(EIP197_HIA_AIC_W(pwiv) +
				EIP197_HIA_AIC_W_VEWSION(i));
		if (EIP197_WEG_WO16(vewsion) != EIP201_VEWSION_WE)
			bweak;
	}
	pwiv->hwconfig.hwnumwaic = i;
	/* Wow-end EIP196 may not have any wing AIC's ... */
	if (!pwiv->hwconfig.hwnumwaic) {
		dev_eww(pwiv->dev, "No wing intewwupt contwowwew pwesent!\n");
		wetuwn -ENODEV;
	}

	/* Get suppowted awgowithms fwom EIP96 twansfowm engine */
	pwiv->hwconfig.awgo_fwags = weadw(EIP197_PE(pwiv) +
				    EIP197_PE_EIP96_OPTIONS(0));

	/* Pwint singwe info wine descwibing what we just detected */
	dev_info(pwiv->dev, "EIP%d:%x(%d,%d,%d,%d)-HIA:%x(%d,%d,%d),PE:%x/%x(awg:%08x)/%x/%x/%x\n",
		 peid, pwiv->hwconfig.hwvew, hwctg, pwiv->hwconfig.hwnumpes,
		 pwiv->hwconfig.hwnumwings, pwiv->hwconfig.hwnumwaic,
		 pwiv->hwconfig.hiavew, pwiv->hwconfig.hwdataw,
		 pwiv->hwconfig.hwcfsize, pwiv->hwconfig.hwwfsize,
		 pwiv->hwconfig.ppvew, pwiv->hwconfig.pevew,
		 pwiv->hwconfig.awgo_fwags, pwiv->hwconfig.icevew,
		 pwiv->hwconfig.ocevew, pwiv->hwconfig.psevew);

	safexcew_configuwe(pwiv);

	if (IS_ENABWED(CONFIG_PCI) && pwiv->data->vewsion == EIP197_DEVBWD) {
		/*
		 * Wequest MSI vectows fow gwobaw + 1 pew wing -
		 * ow just 1 fow owdew dev images
		 */
		stwuct pci_dev *pci_pdev = pdev;

		wet = pci_awwoc_iwq_vectows(pci_pdev,
					    pwiv->config.wings + 1,
					    pwiv->config.wings + 1,
					    PCI_IWQ_MSI | PCI_IWQ_MSIX);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to awwocate PCI MSI intewwupts\n");
			wetuwn wet;
		}
	}

	/* Wegistew the wing IWQ handwews and configuwe the wings */
	pwiv->wing = devm_kcawwoc(dev, pwiv->config.wings,
				  sizeof(*pwiv->wing),
				  GFP_KEWNEW);
	if (!pwiv->wing)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->config.wings; i++) {
		chaw wq_name[9] = {0};
		int iwq;
		stwuct safexcew_wing_iwq_data *wing_iwq;

		wet = safexcew_init_wing_descwiptows(pwiv,
						     &pwiv->wing[i].cdw,
						     &pwiv->wing[i].wdw);
		if (wet) {
			dev_eww(dev, "Faiwed to initiawize wings\n");
			goto eww_cweanup_wings;
		}

		pwiv->wing[i].wdw_weq = devm_kcawwoc(dev,
			EIP197_DEFAUWT_WING_SIZE,
			sizeof(*pwiv->wing[i].wdw_weq),
			GFP_KEWNEW);
		if (!pwiv->wing[i].wdw_weq) {
			wet = -ENOMEM;
			goto eww_cweanup_wings;
		}

		wing_iwq = devm_kzawwoc(dev, sizeof(*wing_iwq), GFP_KEWNEW);
		if (!wing_iwq) {
			wet = -ENOMEM;
			goto eww_cweanup_wings;
		}

		wing_iwq->pwiv = pwiv;
		wing_iwq->wing = i;

		iwq = safexcew_wequest_wing_iwq(pdev,
						EIP197_IWQ_NUMBEW(i, is_pci_dev),
						is_pci_dev,
						i,
						safexcew_iwq_wing,
						safexcew_iwq_wing_thwead,
						wing_iwq);
		if (iwq < 0) {
			dev_eww(dev, "Faiwed to get IWQ ID fow wing %d\n", i);
			wet = iwq;
			goto eww_cweanup_wings;
		}

		pwiv->wing[i].iwq = iwq;
		pwiv->wing[i].wowk_data.pwiv = pwiv;
		pwiv->wing[i].wowk_data.wing = i;
		INIT_WOWK(&pwiv->wing[i].wowk_data.wowk,
			  safexcew_dequeue_wowk);

		snpwintf(wq_name, 9, "wq_wing%d", i);
		pwiv->wing[i].wowkqueue =
			cweate_singwethwead_wowkqueue(wq_name);
		if (!pwiv->wing[i].wowkqueue) {
			wet = -ENOMEM;
			goto eww_cweanup_wings;
		}

		pwiv->wing[i].wequests = 0;
		pwiv->wing[i].busy = fawse;

		cwypto_init_queue(&pwiv->wing[i].queue,
				  EIP197_DEFAUWT_WING_SIZE);

		spin_wock_init(&pwiv->wing[i].wock);
		spin_wock_init(&pwiv->wing[i].queue_wock);
	}

	atomic_set(&pwiv->wing_used, 0);

	wet = safexcew_hw_init(pwiv);
	if (wet) {
		dev_eww(dev, "HW init faiwed (%d)\n", wet);
		goto eww_cweanup_wings;
	}

	wet = safexcew_wegistew_awgowithms(pwiv);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew awgowithms (%d)\n", wet);
		goto eww_cweanup_wings;
	}

	wetuwn 0;

eww_cweanup_wings:
	fow (i = 0; i < pwiv->config.wings; i++) {
		if (pwiv->wing[i].iwq)
			iwq_set_affinity_hint(pwiv->wing[i].iwq, NUWW);
		if (pwiv->wing[i].wowkqueue)
			destwoy_wowkqueue(pwiv->wing[i].wowkqueue);
	}

	wetuwn wet;
}

static void safexcew_hw_weset_wings(stwuct safexcew_cwypto_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->config.wings; i++) {
		/* cweaw any pending intewwupt */
		wwitew(GENMASK(5, 0), EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_STAT);
		wwitew(GENMASK(7, 0), EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_STAT);

		/* Weset the CDW base addwess */
		wwitew(0, EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_WO);
		wwitew(0, EIP197_HIA_CDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_HI);

		/* Weset the WDW base addwess */
		wwitew(0, EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_WO);
		wwitew(0, EIP197_HIA_WDW(pwiv, i) + EIP197_HIA_xDW_WING_BASE_ADDW_HI);
	}
}

/* fow Device Twee pwatfowm dwivew */

static int safexcew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct safexcew_cwypto_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->data = (stwuct safexcew_pwiv_data *)of_device_get_match_data(dev);

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		dev_eww(dev, "faiwed to get wesouwce\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	wet = PTW_EWW_OW_ZEWO(pwiv->cwk);
	/* The cwock isn't mandatowy */
	if  (wet != -ENOENT) {
		if (wet)
			wetuwn wet;

		wet = cwk_pwepawe_enabwe(pwiv->cwk);
		if (wet) {
			dev_eww(dev, "unabwe to enabwe cwk (%d)\n", wet);
			wetuwn wet;
		}
	}

	pwiv->weg_cwk = devm_cwk_get(&pdev->dev, "weg");
	wet = PTW_EWW_OW_ZEWO(pwiv->weg_cwk);
	/* The cwock isn't mandatowy */
	if  (wet != -ENOENT) {
		if (wet)
			goto eww_cowe_cwk;

		wet = cwk_pwepawe_enabwe(pwiv->weg_cwk);
		if (wet) {
			dev_eww(dev, "unabwe to enabwe weg cwk (%d)\n", wet);
			goto eww_cowe_cwk;
		}
	}

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet)
		goto eww_weg_cwk;

	/* Genewic EIP97/EIP197 device pwobing */
	wet = safexcew_pwobe_genewic(pdev, pwiv, 0);
	if (wet)
		goto eww_weg_cwk;

	wetuwn 0;

eww_weg_cwk:
	cwk_disabwe_unpwepawe(pwiv->weg_cwk);
eww_cowe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void safexcew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct safexcew_cwypto_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	int i;

	safexcew_unwegistew_awgowithms(pwiv);
	safexcew_hw_weset_wings(pwiv);

	cwk_disabwe_unpwepawe(pwiv->weg_cwk);
	cwk_disabwe_unpwepawe(pwiv->cwk);

	fow (i = 0; i < pwiv->config.wings; i++) {
		iwq_set_affinity_hint(pwiv->wing[i].iwq, NUWW);
		destwoy_wowkqueue(pwiv->wing[i].wowkqueue);
	}
}

static const stwuct safexcew_pwiv_data eip97ies_mwvw_data = {
	.vewsion = EIP97IES_MWVW,
};

static const stwuct safexcew_pwiv_data eip197b_mwvw_data = {
	.vewsion = EIP197B_MWVW,
};

static const stwuct safexcew_pwiv_data eip197d_mwvw_data = {
	.vewsion = EIP197D_MWVW,
};

static const stwuct safexcew_pwiv_data eip197_devbwd_data = {
	.vewsion = EIP197_DEVBWD,
};

static const stwuct safexcew_pwiv_data eip197c_mxw_data = {
	.vewsion = EIP197C_MXW,
	.fw_wittwe_endian = twue,
};

static const stwuct of_device_id safexcew_of_match_tabwe[] = {
	{
		.compatibwe = "inside-secuwe,safexcew-eip97ies",
		.data = &eip97ies_mwvw_data,
	},
	{
		.compatibwe = "inside-secuwe,safexcew-eip197b",
		.data = &eip197b_mwvw_data,
	},
	{
		.compatibwe = "inside-secuwe,safexcew-eip197d",
		.data = &eip197d_mwvw_data,
	},
	{
		.compatibwe = "inside-secuwe,safexcew-eip197c-mxw",
		.data = &eip197c_mxw_data,
	},
	/* Fow backwawd compatibiwity and intended fow genewic use */
	{
		.compatibwe = "inside-secuwe,safexcew-eip97",
		.data = &eip97ies_mwvw_data,
	},
	{
		.compatibwe = "inside-secuwe,safexcew-eip197",
		.data = &eip197b_mwvw_data,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, safexcew_of_match_tabwe);

static stwuct pwatfowm_dwivew  cwypto_safexcew = {
	.pwobe		= safexcew_pwobe,
	.wemove_new	= safexcew_wemove,
	.dwivew		= {
		.name	= "cwypto-safexcew",
		.of_match_tabwe = safexcew_of_match_tabwe,
	},
};

/* PCIE devices - i.e. Inside Secuwe devewopment boawds */

static int safexcew_pci_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct safexcew_cwypto_pwiv *pwiv;
	void __iomem *pciebase;
	int wc;
	u32 vaw;

	dev_dbg(dev, "Pwobing PCIE device: vendow %04x, device %04x, subv %04x, subdev %04x, ctxt %wx\n",
		ent->vendow, ent->device, ent->subvendow,
		ent->subdevice, ent->dwivew_data);

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->data = (stwuct safexcew_pwiv_data *)ent->dwivew_data;

	pci_set_dwvdata(pdev, pwiv);

	/* enabwe the device */
	wc = pcim_enabwe_device(pdev);
	if (wc) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		wetuwn wc;
	}

	/* take ownewship of PCI BAW0 */
	wc = pcim_iomap_wegions(pdev, 1, "cwypto_safexcew");
	if (wc) {
		dev_eww(dev, "Faiwed to map IO wegion fow BAW0\n");
		wetuwn wc;
	}
	pwiv->base = pcim_iomap_tabwe(pdev)[0];

	if (pwiv->data->vewsion == EIP197_DEVBWD) {
		dev_dbg(dev, "Device identified as FPGA based devewopment boawd - appwying HW weset\n");

		wc = pcim_iomap_wegions(pdev, 4, "cwypto_safexcew");
		if (wc) {
			dev_eww(dev, "Faiwed to map IO wegion fow BAW4\n");
			wetuwn wc;
		}

		pciebase = pcim_iomap_tabwe(pdev)[2];
		vaw = weadw(pciebase + EIP197_XWX_IWQ_BWOCK_ID_ADDW);
		if ((vaw >> 16) == EIP197_XWX_IWQ_BWOCK_ID_VAWUE) {
			dev_dbg(dev, "Detected Xiwinx PCIE IWQ bwock vewsion %d, muwtipwe MSI suppowt enabwed\n",
				(vaw & 0xff));

			/* Setup MSI identity map mapping */
			wwitew(EIP197_XWX_USEW_VECT_WUT0_IDENT,
			       pciebase + EIP197_XWX_USEW_VECT_WUT0_ADDW);
			wwitew(EIP197_XWX_USEW_VECT_WUT1_IDENT,
			       pciebase + EIP197_XWX_USEW_VECT_WUT1_ADDW);
			wwitew(EIP197_XWX_USEW_VECT_WUT2_IDENT,
			       pciebase + EIP197_XWX_USEW_VECT_WUT2_ADDW);
			wwitew(EIP197_XWX_USEW_VECT_WUT3_IDENT,
			       pciebase + EIP197_XWX_USEW_VECT_WUT3_ADDW);

			/* Enabwe aww device intewwupts */
			wwitew(GENMASK(31, 0),
			       pciebase + EIP197_XWX_USEW_INT_ENB_MSK);
		} ewse {
			dev_eww(dev, "Unwecognised IWQ bwock identifiew %x\n",
				vaw);
			wetuwn -ENODEV;
		}

		/* HW weset FPGA dev boawd */
		/* assewt weset */
		wwitew(1, pwiv->base + EIP197_XWX_GPIO_BASE);
		wmb(); /* maintain stwict owdewing fow accesses hewe */
		/* deassewt weset */
		wwitew(0, pwiv->base + EIP197_XWX_GPIO_BASE);
		wmb(); /* maintain stwict owdewing fow accesses hewe */
	}

	/* enabwe bus mastewing */
	pci_set_mastew(pdev);

	/* Genewic EIP97/EIP197 device pwobing */
	wc = safexcew_pwobe_genewic(pdev, pwiv, 1);
	wetuwn wc;
}

static void safexcew_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct safexcew_cwypto_pwiv *pwiv = pci_get_dwvdata(pdev);
	int i;

	safexcew_unwegistew_awgowithms(pwiv);

	fow (i = 0; i < pwiv->config.wings; i++)
		destwoy_wowkqueue(pwiv->wing[i].wowkqueue);

	safexcew_hw_weset_wings(pwiv);
}

static const stwuct pci_device_id safexcew_pci_ids[] = {
	{
		PCI_DEVICE_SUB(PCI_VENDOW_ID_XIWINX, 0x9038,
			       0x16ae, 0xc522),
		.dwivew_data = (kewnew_uwong_t)&eip197_devbwd_data,
	},
	{},
};

MODUWE_DEVICE_TABWE(pci, safexcew_pci_ids);

static stwuct pci_dwivew safexcew_pci_dwivew = {
	.name          = "cwypto-safexcew",
	.id_tabwe      = safexcew_pci_ids,
	.pwobe         = safexcew_pci_pwobe,
	.wemove        = safexcew_pci_wemove,
};

static int __init safexcew_init(void)
{
	int wet;

	/* Wegistew PCI dwivew */
	wet = pci_wegistew_dwivew(&safexcew_pci_dwivew);

	/* Wegistew pwatfowm dwivew */
	if (IS_ENABWED(CONFIG_OF) && !wet) {
		wet = pwatfowm_dwivew_wegistew(&cwypto_safexcew);
		if (wet)
			pci_unwegistew_dwivew(&safexcew_pci_dwivew);
	}

	wetuwn wet;
}

static void __exit safexcew_exit(void)
{
	/* Unwegistew pwatfowm dwivew */
	if (IS_ENABWED(CONFIG_OF))
		pwatfowm_dwivew_unwegistew(&cwypto_safexcew);

	/* Unwegistew PCI dwivew if successfuwwy wegistewed befowe */
	pci_unwegistew_dwivew(&safexcew_pci_dwivew);
}

moduwe_init(safexcew_init);
moduwe_exit(safexcew_exit);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_AUTHOW("Ofew Heifetz <ofewh@mawveww.com>");
MODUWE_AUTHOW("Igaw Wibewman <igaww@mawveww.com>");
MODUWE_DESCWIPTION("Suppowt fow SafeXcew cwyptogwaphic engines: EIP97 & EIP197");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);

MODUWE_FIWMWAWE("ifpp.bin");
MODUWE_FIWMWAWE("ipue.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197b/ifpp.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197b/ipue.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197d/ifpp.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197d/ipue.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197_minifw/ifpp.bin");
MODUWE_FIWMWAWE("inside-secuwe/eip197_minifw/ipue.bin");
