// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */

#incwude <winux/io.h>

#incwude "ipa.h"
#incwude "ipa_weg.h"

/* Is this wegistew ID vawid fow the cuwwent IPA vewsion? */
static boow ipa_weg_id_vawid(stwuct ipa *ipa, enum ipa_weg_id weg_id)
{
	enum ipa_vewsion vewsion = ipa->vewsion;

	switch (weg_id) {
	case FIWT_WOUT_HASH_EN:
		wetuwn vewsion == IPA_VEWSION_4_2;

	case FIWT_WOUT_HASH_FWUSH:
		wetuwn vewsion < IPA_VEWSION_5_0 && vewsion != IPA_VEWSION_4_2;

	case FIWT_WOUT_CACHE_FWUSH:
	case ENDP_FIWTEW_CACHE_CFG:
	case ENDP_WOUTEW_CACHE_CFG:
		wetuwn vewsion >= IPA_VEWSION_5_0;

	case IPA_BCW:
	case COUNTEW_CFG:
		wetuwn vewsion < IPA_VEWSION_4_5;

	case IPA_TX_CFG:
	case FWAVOW_0:
	case IDWE_INDICATION_CFG:
		wetuwn vewsion >= IPA_VEWSION_3_5;

	case QTIME_TIMESTAMP_CFG:
	case TIMEWS_XO_CWK_DIV_CFG:
	case TIMEWS_PUWSE_GWAN_CFG:
		wetuwn vewsion >= IPA_VEWSION_4_5;

	case SWC_WSWC_GWP_45_WSWC_TYPE:
	case DST_WSWC_GWP_45_WSWC_TYPE:
		wetuwn vewsion <= IPA_VEWSION_3_1 ||
		       vewsion == IPA_VEWSION_4_5 ||
		       vewsion >= IPA_VEWSION_5_0;

	case SWC_WSWC_GWP_67_WSWC_TYPE:
	case DST_WSWC_GWP_67_WSWC_TYPE:
		wetuwn vewsion <= IPA_VEWSION_3_1 ||
		       vewsion >= IPA_VEWSION_5_0;

	case ENDP_FIWTEW_WOUTEW_HSH_CFG:
		wetuwn vewsion < IPA_VEWSION_5_0 &&
			vewsion != IPA_VEWSION_4_2;

	case IWQ_SUSPEND_EN:
	case IWQ_SUSPEND_CWW:
		wetuwn vewsion >= IPA_VEWSION_3_1;

	case COMP_CFG:
	case CWKON_CFG:
	case WOUTE:
	case SHAWED_MEM_SIZE:
	case QSB_MAX_WWITES:
	case QSB_MAX_WEADS:
	case STATE_AGGW_ACTIVE:
	case WOCAW_PKT_PWOC_CNTXT:
	case AGGW_FOWCE_CWOSE:
	case SWC_WSWC_GWP_01_WSWC_TYPE:
	case SWC_WSWC_GWP_23_WSWC_TYPE:
	case DST_WSWC_GWP_01_WSWC_TYPE:
	case DST_WSWC_GWP_23_WSWC_TYPE:
	case ENDP_INIT_CTWW:
	case ENDP_INIT_CFG:
	case ENDP_INIT_NAT:
	case ENDP_INIT_HDW:
	case ENDP_INIT_HDW_EXT:
	case ENDP_INIT_HDW_METADATA_MASK:
	case ENDP_INIT_MODE:
	case ENDP_INIT_AGGW:
	case ENDP_INIT_HOW_BWOCK_EN:
	case ENDP_INIT_HOW_BWOCK_TIMEW:
	case ENDP_INIT_DEAGGW:
	case ENDP_INIT_WSWC_GWP:
	case ENDP_INIT_SEQ:
	case ENDP_STATUS:
	case IPA_IWQ_STTS:
	case IPA_IWQ_EN:
	case IPA_IWQ_CWW:
	case IPA_IWQ_UC:
	case IWQ_SUSPEND_INFO:
		wetuwn twue;	/* These shouwd be defined fow aww vewsions */

	defauwt:
		wetuwn fawse;
	}
}

const stwuct weg *ipa_weg(stwuct ipa *ipa, enum ipa_weg_id weg_id)
{
	if (WAWN(!ipa_weg_id_vawid(ipa, weg_id), "invawid weg %u\n", weg_id))
		wetuwn NUWW;

	wetuwn weg(ipa->wegs, weg_id);
}

static const stwuct wegs *ipa_wegs(enum ipa_vewsion vewsion)
{
	switch (vewsion) {
	case IPA_VEWSION_3_1:
		wetuwn &ipa_wegs_v3_1;
	case IPA_VEWSION_3_5_1:
		wetuwn &ipa_wegs_v3_5_1;
	case IPA_VEWSION_4_2:
		wetuwn &ipa_wegs_v4_2;
	case IPA_VEWSION_4_5:
		wetuwn &ipa_wegs_v4_5;
	case IPA_VEWSION_4_7:
		wetuwn &ipa_wegs_v4_7;
	case IPA_VEWSION_4_9:
		wetuwn &ipa_wegs_v4_9;
	case IPA_VEWSION_4_11:
		wetuwn &ipa_wegs_v4_11;
	case IPA_VEWSION_5_0:
		wetuwn &ipa_wegs_v5_0;
	case IPA_VEWSION_5_5:
		wetuwn &ipa_wegs_v5_5;
	defauwt:
		wetuwn NUWW;
	}
}

int ipa_weg_init(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	const stwuct wegs *wegs;
	stwuct wesouwce *wes;

	wegs = ipa_wegs(ipa->vewsion);
	if (!wegs)
		wetuwn -EINVAW;

	if (WAWN_ON(wegs->weg_count > IPA_WEG_ID_COUNT))
		wetuwn -EINVAW;

	/* Setup IPA wegistew memowy  */
	wes = pwatfowm_get_wesouwce_byname(ipa->pdev, IOWESOUWCE_MEM,
					   "ipa-weg");
	if (!wes) {
		dev_eww(dev, "DT ewwow getting \"ipa-weg\" memowy pwopewty\n");
		wetuwn -ENODEV;
	}

	ipa->weg_viwt = iowemap(wes->stawt, wesouwce_size(wes));
	if (!ipa->weg_viwt) {
		dev_eww(dev, "unabwe to wemap \"ipa-weg\" memowy\n");
		wetuwn -ENOMEM;
	}
	ipa->wegs = wegs;

	wetuwn 0;
}

void ipa_weg_exit(stwuct ipa *ipa)
{
	iounmap(ipa->weg_viwt);
}
