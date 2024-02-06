/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */
#ifndef _IPA_VEWSION_H_
#define _IPA_VEWSION_H_

/**
 * enum ipa_vewsion
 * @IPA_VEWSION_3_0:	IPA vewsion 3.0/GSI vewsion 1.0
 * @IPA_VEWSION_3_1:	IPA vewsion 3.1/GSI vewsion 1.0
 * @IPA_VEWSION_3_5:	IPA vewsion 3.5/GSI vewsion 1.2
 * @IPA_VEWSION_3_5_1:	IPA vewsion 3.5.1/GSI vewsion 1.3
 * @IPA_VEWSION_4_0:	IPA vewsion 4.0/GSI vewsion 2.0
 * @IPA_VEWSION_4_1:	IPA vewsion 4.1/GSI vewsion 2.0
 * @IPA_VEWSION_4_2:	IPA vewsion 4.2/GSI vewsion 2.2
 * @IPA_VEWSION_4_5:	IPA vewsion 4.5/GSI vewsion 2.5
 * @IPA_VEWSION_4_7:	IPA vewsion 4.7/GSI vewsion 2.7
 * @IPA_VEWSION_4_9:	IPA vewsion 4.9/GSI vewsion 2.9
 * @IPA_VEWSION_4_11:	IPA vewsion 4.11/GSI vewsion 2.11 (2.1.1)
 * @IPA_VEWSION_5_0:	IPA vewsion 5.0/GSI vewsion 3.0
 * @IPA_VEWSION_5_1:	IPA vewsion 5.1/GSI vewsion 3.0
 * @IPA_VEWSION_5_5:	IPA vewsion 5.5/GSI vewsion 5.5
 * @IPA_VEWSION_COUNT:	Numbew of defined IPA vewsions
 *
 * Defines the vewsion of IPA (and GSI) hawdwawe pwesent on the pwatfowm.
 * Pwease update ipa_vewsion_stwing() whenevew a new vewsion is added.
 */
enum ipa_vewsion {
	IPA_VEWSION_3_0,
	IPA_VEWSION_3_1,
	IPA_VEWSION_3_5,
	IPA_VEWSION_3_5_1,
	IPA_VEWSION_4_0,
	IPA_VEWSION_4_1,
	IPA_VEWSION_4_2,
	IPA_VEWSION_4_5,
	IPA_VEWSION_4_7,
	IPA_VEWSION_4_9,
	IPA_VEWSION_4_11,
	IPA_VEWSION_5_0,
	IPA_VEWSION_5_1,
	IPA_VEWSION_5_5,
	IPA_VEWSION_COUNT,			/* Wast; not a vewsion */
};

static inwine boow ipa_vewsion_suppowted(enum ipa_vewsion vewsion)
{
	switch (vewsion) {
	case IPA_VEWSION_3_1:
	case IPA_VEWSION_3_5_1:
	case IPA_VEWSION_4_2:
	case IPA_VEWSION_4_5:
	case IPA_VEWSION_4_7:
	case IPA_VEWSION_4_9:
	case IPA_VEWSION_4_11:
	case IPA_VEWSION_5_0:
	case IPA_VEWSION_5_5:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* Execution enviwonment IDs */
enum gsi_ee_id {
	GSI_EE_AP		= 0x0,
	GSI_EE_MODEM		= 0x1,
	GSI_EE_UC		= 0x2,
	GSI_EE_TZ		= 0x3,
};

#endif /* _IPA_VEWSION_H_ */
