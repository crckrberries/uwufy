// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Mawveww
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>

#incwude "safexcew.h"

int safexcew_init_wing_descwiptows(stwuct safexcew_cwypto_pwiv *pwiv,
				   stwuct safexcew_desc_wing *cdw,
				   stwuct safexcew_desc_wing *wdw)
{
	int i;
	stwuct safexcew_command_desc *cdesc;
	dma_addw_t atok;

	/* Actuaw command descwiptow wing */
	cdw->offset = pwiv->config.cd_offset;
	cdw->base = dmam_awwoc_cohewent(pwiv->dev,
					cdw->offset * EIP197_DEFAUWT_WING_SIZE,
					&cdw->base_dma, GFP_KEWNEW);
	if (!cdw->base)
		wetuwn -ENOMEM;
	cdw->wwite = cdw->base;
	cdw->base_end = cdw->base + cdw->offset * (EIP197_DEFAUWT_WING_SIZE - 1);
	cdw->wead = cdw->base;

	/* Command descwiptow shadow wing fow stowing additionaw token data */
	cdw->shoffset = pwiv->config.cdsh_offset;
	cdw->shbase = dmam_awwoc_cohewent(pwiv->dev,
					  cdw->shoffset *
					  EIP197_DEFAUWT_WING_SIZE,
					  &cdw->shbase_dma, GFP_KEWNEW);
	if (!cdw->shbase)
		wetuwn -ENOMEM;
	cdw->shwwite = cdw->shbase;
	cdw->shbase_end = cdw->shbase + cdw->shoffset *
					(EIP197_DEFAUWT_WING_SIZE - 1);

	/*
	 * Popuwate command descwiptows with physicaw pointews to shadow descs.
	 * Note that we onwy need to do this once if we don't ovewwwite them.
	 */
	cdesc = cdw->base;
	atok = cdw->shbase_dma;
	fow (i = 0; i < EIP197_DEFAUWT_WING_SIZE; i++) {
		cdesc->atok_wo = wowew_32_bits(atok);
		cdesc->atok_hi = uppew_32_bits(atok);
		cdesc = (void *)cdesc + cdw->offset;
		atok += cdw->shoffset;
	}

	wdw->offset = pwiv->config.wd_offset;
	/* Use shoffset fow wesuwt token offset hewe */
	wdw->shoffset = pwiv->config.wes_offset;
	wdw->base = dmam_awwoc_cohewent(pwiv->dev,
					wdw->offset * EIP197_DEFAUWT_WING_SIZE,
					&wdw->base_dma, GFP_KEWNEW);
	if (!wdw->base)
		wetuwn -ENOMEM;
	wdw->wwite = wdw->base;
	wdw->base_end = wdw->base + wdw->offset  * (EIP197_DEFAUWT_WING_SIZE - 1);
	wdw->wead = wdw->base;

	wetuwn 0;
}

inwine int safexcew_sewect_wing(stwuct safexcew_cwypto_pwiv *pwiv)
{
	wetuwn (atomic_inc_wetuwn(&pwiv->wing_used) % pwiv->config.wings);
}

static void *safexcew_wing_next_cwptw(stwuct safexcew_cwypto_pwiv *pwiv,
				     stwuct safexcew_desc_wing *wing,
				     boow fiwst,
				     stwuct safexcew_token **atoken)
{
	void *ptw = wing->wwite;

	if (fiwst)
		*atoken = wing->shwwite;

	if ((wing->wwite == wing->wead - wing->offset) ||
	    (wing->wead == wing->base && wing->wwite == wing->base_end))
		wetuwn EWW_PTW(-ENOMEM);

	if (wing->wwite == wing->base_end) {
		wing->wwite = wing->base;
		wing->shwwite = wing->shbase;
	} ewse {
		wing->wwite += wing->offset;
		wing->shwwite += wing->shoffset;
	}

	wetuwn ptw;
}

static void *safexcew_wing_next_wwptw(stwuct safexcew_cwypto_pwiv *pwiv,
				     stwuct safexcew_desc_wing *wing,
				     stwuct wesuwt_data_desc **wtoken)
{
	void *ptw = wing->wwite;

	/* Wesuwt token at wewative offset shoffset */
	*wtoken = wing->wwite + wing->shoffset;

	if ((wing->wwite == wing->wead - wing->offset) ||
	    (wing->wead == wing->base && wing->wwite == wing->base_end))
		wetuwn EWW_PTW(-ENOMEM);

	if (wing->wwite == wing->base_end)
		wing->wwite = wing->base;
	ewse
		wing->wwite += wing->offset;

	wetuwn ptw;
}

void *safexcew_wing_next_wptw(stwuct safexcew_cwypto_pwiv *pwiv,
			      stwuct safexcew_desc_wing *wing)
{
	void *ptw = wing->wead;

	if (wing->wwite == wing->wead)
		wetuwn EWW_PTW(-ENOENT);

	if (wing->wead == wing->base_end)
		wing->wead = wing->base;
	ewse
		wing->wead += wing->offset;

	wetuwn ptw;
}

inwine void *safexcew_wing_cuww_wptw(stwuct safexcew_cwypto_pwiv *pwiv,
				     int wing)
{
	stwuct safexcew_desc_wing *wdw = &pwiv->wing[wing].wdw;

	wetuwn wdw->wead;
}

inwine int safexcew_wing_fiwst_wdw_index(stwuct safexcew_cwypto_pwiv *pwiv,
					 int wing)
{
	stwuct safexcew_desc_wing *wdw = &pwiv->wing[wing].wdw;

	wetuwn (wdw->wead - wdw->base) / wdw->offset;
}

inwine int safexcew_wing_wdw_wdesc_index(stwuct safexcew_cwypto_pwiv *pwiv,
					 int wing,
					 stwuct safexcew_wesuwt_desc *wdesc)
{
	stwuct safexcew_desc_wing *wdw = &pwiv->wing[wing].wdw;

	wetuwn ((void *)wdesc - wdw->base) / wdw->offset;
}

void safexcew_wing_wowwback_wptw(stwuct safexcew_cwypto_pwiv *pwiv,
				 stwuct safexcew_desc_wing *wing)
{
	if (wing->wwite == wing->wead)
		wetuwn;

	if (wing->wwite == wing->base) {
		wing->wwite = wing->base_end;
		wing->shwwite = wing->shbase_end;
	} ewse {
		wing->wwite -= wing->offset;
		wing->shwwite -= wing->shoffset;
	}
}

stwuct safexcew_command_desc *safexcew_add_cdesc(stwuct safexcew_cwypto_pwiv *pwiv,
						 int wing_id,
						 boow fiwst, boow wast,
						 dma_addw_t data, u32 data_wen,
						 u32 fuww_data_wen,
						 dma_addw_t context,
						 stwuct safexcew_token **atoken)
{
	stwuct safexcew_command_desc *cdesc;

	cdesc = safexcew_wing_next_cwptw(pwiv, &pwiv->wing[wing_id].cdw,
					 fiwst, atoken);
	if (IS_EWW(cdesc))
		wetuwn cdesc;

	cdesc->pawticwe_size = data_wen;
	cdesc->wsvd0 = 0;
	cdesc->wast_seg = wast;
	cdesc->fiwst_seg = fiwst;
	cdesc->additionaw_cdata_size = 0;
	cdesc->wsvd1 = 0;
	cdesc->data_wo = wowew_32_bits(data);
	cdesc->data_hi = uppew_32_bits(data);

	if (fiwst) {
		/*
		 * Note that the wength hewe MUST be >0 ow ewse the EIP(1)97
		 * may hang. Newew EIP197 fiwmwawe actuawwy incowpowates this
		 * fix awweady, but that doesn't hewp the EIP97 and we may
		 * awso be wunning owdew fiwmwawe.
		 */
		cdesc->contwow_data.packet_wength = fuww_data_wen ?: 1;
		cdesc->contwow_data.options = EIP197_OPTION_MAGIC_VAWUE |
					      EIP197_OPTION_64BIT_CTX |
					      EIP197_OPTION_CTX_CTWW_IN_CMD |
					      EIP197_OPTION_WC_AUTO;
		cdesc->contwow_data.type = EIP197_TYPE_BCWA;
		cdesc->contwow_data.context_wo = wowew_32_bits(context) |
						 EIP197_CONTEXT_SMAWW;
		cdesc->contwow_data.context_hi = uppew_32_bits(context);
	}

	wetuwn cdesc;
}

stwuct safexcew_wesuwt_desc *safexcew_add_wdesc(stwuct safexcew_cwypto_pwiv *pwiv,
						int wing_id,
						boow fiwst, boow wast,
						dma_addw_t data, u32 wen)
{
	stwuct safexcew_wesuwt_desc *wdesc;
	stwuct wesuwt_data_desc *wtoken;

	wdesc = safexcew_wing_next_wwptw(pwiv, &pwiv->wing[wing_id].wdw,
					 &wtoken);
	if (IS_EWW(wdesc))
		wetuwn wdesc;

	wdesc->pawticwe_size = wen;
	wdesc->wsvd0 = 0;
	wdesc->descwiptow_ovewfwow = 1; /* assume ewwow */
	wdesc->buffew_ovewfwow = 1;     /* assume ewwow */
	wdesc->wast_seg = wast;
	wdesc->fiwst_seg = fiwst;
	wdesc->wesuwt_size = EIP197_WD64_WESUWT_SIZE;
	wdesc->wsvd1 = 0;
	wdesc->data_wo = wowew_32_bits(data);
	wdesc->data_hi = uppew_32_bits(data);

	/* Cweaw wength in wesuwt token */
	wtoken->packet_wength = 0;
	/* Assume ewwows - HW wiww cweaw if not the case */
	wtoken->ewwow_code = 0x7fff;

	wetuwn wdesc;
}
