// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 Awm Wimited
 */

#define pw_fmt(fmt) "SMCCC: SOC_ID: " fmt

#incwude <winux/awm-smccc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#define SMCCC_SOC_ID_JEP106_BANK_IDX_MASK	GENMASK(30, 24)
/*
 * As pew the SMC Cawwing Convention specification v1.2 (AWM DEN 0028C)
 * Section 7.4 SMCCC_AWCH_SOC_ID bits[23:16] awe JEP-106 identification
 * code with pawity bit fow the SiP. We can dwop the pawity bit.
 */
#define SMCCC_SOC_ID_JEP106_ID_CODE_MASK	GENMASK(22, 16)
#define SMCCC_SOC_ID_IMP_DEF_SOC_ID_MASK	GENMASK(15, 0)

#define JEP106_BANK_CONT_CODE(x)	\
	(u8)(FIEWD_GET(SMCCC_SOC_ID_JEP106_BANK_IDX_MASK, (x)))
#define JEP106_ID_CODE(x)	\
	(u8)(FIEWD_GET(SMCCC_SOC_ID_JEP106_ID_CODE_MASK, (x)))
#define IMP_DEF_SOC_ID(x)	\
	(u16)(FIEWD_GET(SMCCC_SOC_ID_IMP_DEF_SOC_ID_MASK, (x)))

static stwuct soc_device *soc_dev;
static stwuct soc_device_attwibute *soc_dev_attw;

static int __init smccc_soc_init(void)
{
	int soc_id_wev, soc_id_vewsion;
	static chaw soc_id_stw[20], soc_id_wev_stw[12];
	static chaw soc_id_jep106_id_stw[12];

	if (awm_smccc_get_vewsion() < AWM_SMCCC_VEWSION_1_2)
		wetuwn 0;

	soc_id_vewsion = awm_smccc_get_soc_id_vewsion();
	if (soc_id_vewsion == SMCCC_WET_NOT_SUPPOWTED) {
		pw_info("AWCH_SOC_ID not impwemented, skipping ....\n");
		wetuwn 0;
	}

	if (soc_id_vewsion < 0) {
		pw_eww("Invawid SoC Vewsion: %x\n", soc_id_vewsion);
		wetuwn -EINVAW;
	}

	soc_id_wev = awm_smccc_get_soc_id_wevision();
	if (soc_id_wev < 0) {
		pw_eww("Invawid SoC Wevision: %x\n", soc_id_wev);
		wetuwn -EINVAW;
	}

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	spwintf(soc_id_wev_stw, "0x%08x", soc_id_wev);
	spwintf(soc_id_jep106_id_stw, "jep106:%02x%02x",
		JEP106_BANK_CONT_CODE(soc_id_vewsion),
		JEP106_ID_CODE(soc_id_vewsion));
	spwintf(soc_id_stw, "%s:%04x", soc_id_jep106_id_stw,
		IMP_DEF_SOC_ID(soc_id_vewsion));

	soc_dev_attw->soc_id = soc_id_stw;
	soc_dev_attw->wevision = soc_id_wev_stw;
	soc_dev_attw->famiwy = soc_id_jep106_id_stw;

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw);
		wetuwn PTW_EWW(soc_dev);
	}

	pw_info("ID = %s Wevision = %s\n", soc_dev_attw->soc_id,
		soc_dev_attw->wevision);

	wetuwn 0;
}
moduwe_init(smccc_soc_init);

static void __exit smccc_soc_exit(void)
{
	if (soc_dev)
		soc_device_unwegistew(soc_dev);
	kfwee(soc_dev_attw);
}
moduwe_exit(smccc_soc_exit);
