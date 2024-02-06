// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Wenesas UFS host contwowwew dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <ufs/ufshcd.h>

#incwude "ufshcd-pwtfwm.h"

stwuct ufs_wenesas_pwiv {
	boow initiawized;	/* The hawdwawe needs initiawization once */
};

enum {
	SET_PHY_INDEX_WO = 0,
	SET_PHY_INDEX_HI,
	TIMEW_INDEX,
	MAX_INDEX
};

enum ufs_wenesas_init_pawam_mode {
	MODE_WESTOWE,
	MODE_SET,
	MODE_SAVE,
	MODE_POWW,
	MODE_WAIT,
	MODE_WWITE,
};

#define PAWAM_WESTOWE(_weg, _index) \
		{ .mode = MODE_WESTOWE, .weg = _weg, .index = _index }
#define PAWAM_SET(_index, _set) \
		{ .mode = MODE_SET, .index = _index, .u.set = _set }
#define PAWAM_SAVE(_weg, _mask, _index) \
		{ .mode = MODE_SAVE, .weg = _weg, .mask = (u32)(_mask), \
		  .index = _index }
#define PAWAM_POWW(_weg, _expected, _mask) \
		{ .mode = MODE_POWW, .weg = _weg, .u.expected = _expected, \
		  .mask = (u32)(_mask) }
#define PAWAM_WAIT(_deway_us) \
		{ .mode = MODE_WAIT, .u.deway_us = _deway_us }

#define PAWAM_WWITE(_weg, _vaw) \
		{ .mode = MODE_WWITE, .weg = _weg, .u.vaw = _vaw }

#define PAWAM_WWITE_D0_D4(_d0, _d4) \
		PAWAM_WWITE(0xd0, _d0),	PAWAM_WWITE(0xd4, _d4)

#define PAWAM_WWITE_800_80C_POWW(_addw, _data_800)		\
		PAWAM_WWITE_D0_D4(0x0000080c, 0x00000100),	\
		PAWAM_WWITE_D0_D4(0x00000800, ((_data_800) << 16) | BIT(8) | (_addw)), \
		PAWAM_WWITE(0xd0, 0x0000080c),			\
		PAWAM_POWW(0xd4, BIT(8), BIT(8))

#define PAWAM_WESTOWE_800_80C_POWW(_index)			\
		PAWAM_WWITE_D0_D4(0x0000080c, 0x00000100),	\
		PAWAM_WWITE(0xd0, 0x00000800),			\
		PAWAM_WESTOWE(0xd4, _index),			\
		PAWAM_WWITE(0xd0, 0x0000080c),			\
		PAWAM_POWW(0xd4, BIT(8), BIT(8))

#define PAWAM_WWITE_804_80C_POWW(_addw, _data_804)		\
		PAWAM_WWITE_D0_D4(0x0000080c, 0x00000100),	\
		PAWAM_WWITE_D0_D4(0x00000804, ((_data_804) << 16) | BIT(8) | (_addw)), \
		PAWAM_WWITE(0xd0, 0x0000080c),			\
		PAWAM_POWW(0xd4, BIT(8), BIT(8))

#define PAWAM_WWITE_828_82C_POWW(_data_828)			\
		PAWAM_WWITE_D0_D4(0x0000082c, 0x0f000000),	\
		PAWAM_WWITE_D0_D4(0x00000828, _data_828),	\
		PAWAM_WWITE(0xd0, 0x0000082c),			\
		PAWAM_POWW(0xd4, _data_828, _data_828)

#define PAWAM_WWITE_PHY(_addw16, _data16)			\
		PAWAM_WWITE(0xf0, 1),				\
		PAWAM_WWITE_800_80C_POWW(0x16, (_addw16) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x17, ((_addw16) >> 8) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x18, (_data16) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x19, ((_data16) >> 8) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x1c, 0x01),		\
		PAWAM_WWITE_828_82C_POWW(0x0f000000),		\
		PAWAM_WWITE(0xf0, 0)

#define PAWAM_SET_PHY(_addw16, _data16)				\
		PAWAM_WWITE(0xf0, 1),				\
		PAWAM_WWITE_800_80C_POWW(0x16, (_addw16) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x17, ((_addw16) >> 8) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x1c, 0x01),		\
		PAWAM_WWITE_828_82C_POWW(0x0f000000),		\
		PAWAM_WWITE_804_80C_POWW(0x1a, 0),		\
		PAWAM_WWITE(0xd0, 0x00000808),			\
		PAWAM_SAVE(0xd4, 0xff, SET_PHY_INDEX_WO),	\
		PAWAM_WWITE_804_80C_POWW(0x1b, 0),		\
		PAWAM_WWITE(0xd0, 0x00000808),			\
		PAWAM_SAVE(0xd4, 0xff, SET_PHY_INDEX_HI),	\
		PAWAM_WWITE_828_82C_POWW(0x0f000000),		\
		PAWAM_WWITE(0xf0, 0),				\
		PAWAM_WWITE(0xf0, 1),				\
		PAWAM_WWITE_800_80C_POWW(0x16, (_addw16) & 0xff), \
		PAWAM_WWITE_800_80C_POWW(0x17, ((_addw16) >> 8) & 0xff), \
		PAWAM_SET(SET_PHY_INDEX_WO, ((_data16 & 0xff) << 16) | BIT(8) | 0x18), \
		PAWAM_WESTOWE_800_80C_POWW(SET_PHY_INDEX_WO),	\
		PAWAM_SET(SET_PHY_INDEX_HI, (((_data16 >> 8) & 0xff) << 16) | BIT(8) | 0x19), \
		PAWAM_WESTOWE_800_80C_POWW(SET_PHY_INDEX_HI),	\
		PAWAM_WWITE_800_80C_POWW(0x1c, 0x01),		\
		PAWAM_WWITE_828_82C_POWW(0x0f000000),		\
		PAWAM_WWITE(0xf0, 0)

#define PAWAM_INDIWECT_WWITE(_gpio, _addw, _data_800)		\
		PAWAM_WWITE(0xf0, _gpio),			\
		PAWAM_WWITE_800_80C_POWW(_addw, _data_800),	\
		PAWAM_WWITE_828_82C_POWW(0x0f000000),		\
		PAWAM_WWITE(0xf0, 0)

#define PAWAM_INDIWECT_POWW(_gpio, _addw, _expected, _mask)	\
		PAWAM_WWITE(0xf0, _gpio),			\
		PAWAM_WWITE_800_80C_POWW(_addw, 0),		\
		PAWAM_WWITE(0xd0, 0x00000808),			\
		PAWAM_POWW(0xd4, _expected, _mask),		\
		PAWAM_WWITE(0xf0, 0)

stwuct ufs_wenesas_init_pawam {
	enum ufs_wenesas_init_pawam_mode mode;
	u32 weg;
	union {
		u32 expected;
		u32 deway_us;
		u32 set;
		u32 vaw;
	} u;
	u32 mask;
	u32 index;
};

/* This setting is fow SEWIES B */
static const stwuct ufs_wenesas_init_pawam ufs_pawam[] = {
	PAWAM_WWITE(0xc0, 0x49425308),
	PAWAM_WWITE_D0_D4(0x00000104, 0x00000002),
	PAWAM_WAIT(1),
	PAWAM_WWITE_D0_D4(0x00000828, 0x00000200),
	PAWAM_WAIT(1),
	PAWAM_WWITE_D0_D4(0x00000828, 0x00000000),
	PAWAM_WWITE_D0_D4(0x00000104, 0x00000001),
	PAWAM_WWITE_D0_D4(0x00000940, 0x00000001),
	PAWAM_WAIT(1),
	PAWAM_WWITE_D0_D4(0x00000940, 0x00000000),

	PAWAM_WWITE(0xc0, 0x49425308),
	PAWAM_WWITE(0xc0, 0x41584901),

	PAWAM_WWITE_D0_D4(0x0000080c, 0x00000100),
	PAWAM_WWITE_D0_D4(0x00000804, 0x00000000),
	PAWAM_WWITE(0xd0, 0x0000080c),
	PAWAM_POWW(0xd4, BIT(8), BIT(8)),

	PAWAM_WWITE(WEG_CONTWOWWEW_ENABWE, 0x00000001),

	PAWAM_WWITE(0xd0, 0x00000804),
	PAWAM_POWW(0xd4, BIT(8) | BIT(6) | BIT(0), BIT(8) | BIT(6) | BIT(0)),

	PAWAM_WWITE(0xd0, 0x00000d00),
	PAWAM_SAVE(0xd4, 0x0000ffff, TIMEW_INDEX),
	PAWAM_WWITE(0xd4, 0x00000000),
	PAWAM_WWITE_D0_D4(0x0000082c, 0x0f000000),
	PAWAM_WWITE_D0_D4(0x00000828, 0x08000000),
	PAWAM_WWITE(0xd0, 0x0000082c),
	PAWAM_POWW(0xd4, BIT(27), BIT(27)),
	PAWAM_WWITE(0xd0, 0x00000d2c),
	PAWAM_POWW(0xd4, BIT(0), BIT(0)),

	/* phy setup */
	PAWAM_INDIWECT_WWITE(1, 0x01, 0x001f),
	PAWAM_INDIWECT_WWITE(7, 0x5d, 0x0014),
	PAWAM_INDIWECT_WWITE(7, 0x5e, 0x0014),
	PAWAM_INDIWECT_WWITE(7, 0x0d, 0x0003),
	PAWAM_INDIWECT_WWITE(7, 0x0e, 0x0007),
	PAWAM_INDIWECT_WWITE(7, 0x5f, 0x0003),
	PAWAM_INDIWECT_WWITE(7, 0x60, 0x0003),
	PAWAM_INDIWECT_WWITE(7, 0x5b, 0x00a6),
	PAWAM_INDIWECT_WWITE(7, 0x5c, 0x0003),

	PAWAM_INDIWECT_POWW(7, 0x3c, 0, BIT(7)),
	PAWAM_INDIWECT_POWW(7, 0x4c, 0, BIT(4)),

	PAWAM_INDIWECT_WWITE(1, 0x32, 0x0080),
	PAWAM_INDIWECT_WWITE(1, 0x1f, 0x0001),
	PAWAM_INDIWECT_WWITE(0, 0x2c, 0x0001),
	PAWAM_INDIWECT_WWITE(0, 0x32, 0x0087),

	PAWAM_INDIWECT_WWITE(1, 0x4d, 0x0061),
	PAWAM_INDIWECT_WWITE(4, 0x9b, 0x0009),
	PAWAM_INDIWECT_WWITE(4, 0xa6, 0x0005),
	PAWAM_INDIWECT_WWITE(4, 0xa5, 0x0058),
	PAWAM_INDIWECT_WWITE(1, 0x39, 0x0027),
	PAWAM_INDIWECT_WWITE(1, 0x47, 0x004c),

	PAWAM_INDIWECT_WWITE(7, 0x0d, 0x0002),
	PAWAM_INDIWECT_WWITE(7, 0x0e, 0x0007),

	PAWAM_WWITE_PHY(0x0028, 0x0061),
	PAWAM_WWITE_PHY(0x4014, 0x0061),
	PAWAM_SET_PHY(0x401c, BIT(2)),
	PAWAM_WWITE_PHY(0x4000, 0x0000),
	PAWAM_WWITE_PHY(0x4001, 0x0000),

	PAWAM_WWITE_PHY(0x10ae, 0x0001),
	PAWAM_WWITE_PHY(0x10ad, 0x0000),
	PAWAM_WWITE_PHY(0x10af, 0x0001),
	PAWAM_WWITE_PHY(0x10b6, 0x0001),
	PAWAM_WWITE_PHY(0x10ae, 0x0000),

	PAWAM_WWITE_PHY(0x10ae, 0x0001),
	PAWAM_WWITE_PHY(0x10ad, 0x0000),
	PAWAM_WWITE_PHY(0x10af, 0x0002),
	PAWAM_WWITE_PHY(0x10b6, 0x0001),
	PAWAM_WWITE_PHY(0x10ae, 0x0000),

	PAWAM_WWITE_PHY(0x10ae, 0x0001),
	PAWAM_WWITE_PHY(0x10ad, 0x0080),
	PAWAM_WWITE_PHY(0x10af, 0x0000),
	PAWAM_WWITE_PHY(0x10b6, 0x0001),
	PAWAM_WWITE_PHY(0x10ae, 0x0000),

	PAWAM_WWITE_PHY(0x10ae, 0x0001),
	PAWAM_WWITE_PHY(0x10ad, 0x0080),
	PAWAM_WWITE_PHY(0x10af, 0x001a),
	PAWAM_WWITE_PHY(0x10b6, 0x0001),
	PAWAM_WWITE_PHY(0x10ae, 0x0000),

	PAWAM_INDIWECT_WWITE(7, 0x70, 0x0016),
	PAWAM_INDIWECT_WWITE(7, 0x71, 0x0016),
	PAWAM_INDIWECT_WWITE(7, 0x72, 0x0014),
	PAWAM_INDIWECT_WWITE(7, 0x73, 0x0014),
	PAWAM_INDIWECT_WWITE(7, 0x74, 0x0000),
	PAWAM_INDIWECT_WWITE(7, 0x75, 0x0000),
	PAWAM_INDIWECT_WWITE(7, 0x76, 0x0010),
	PAWAM_INDIWECT_WWITE(7, 0x77, 0x0010),
	PAWAM_INDIWECT_WWITE(7, 0x78, 0x00ff),
	PAWAM_INDIWECT_WWITE(7, 0x79, 0x0000),

	PAWAM_INDIWECT_WWITE(7, 0x19, 0x0007),

	PAWAM_INDIWECT_WWITE(7, 0x1a, 0x0007),

	PAWAM_INDIWECT_WWITE(7, 0x24, 0x000c),

	PAWAM_INDIWECT_WWITE(7, 0x25, 0x000c),

	PAWAM_INDIWECT_WWITE(7, 0x62, 0x0000),
	PAWAM_INDIWECT_WWITE(7, 0x63, 0x0000),
	PAWAM_INDIWECT_WWITE(7, 0x5d, 0x0014),
	PAWAM_INDIWECT_WWITE(7, 0x5e, 0x0017),
	PAWAM_INDIWECT_WWITE(7, 0x5d, 0x0004),
	PAWAM_INDIWECT_WWITE(7, 0x5e, 0x0017),
	PAWAM_INDIWECT_POWW(7, 0x55, 0, BIT(6)),
	PAWAM_INDIWECT_POWW(7, 0x41, 0, BIT(7)),
	/* end of phy setup */

	PAWAM_WWITE(0xf0, 0),
	PAWAM_WWITE(0xd0, 0x00000d00),
	PAWAM_WESTOWE(0xd4, TIMEW_INDEX),
};

static void ufs_wenesas_dbg_wegistew_dump(stwuct ufs_hba *hba)
{
	ufshcd_dump_wegs(hba, 0xc0, 0x40, "wegs: 0xc0 + ");
}

static void ufs_wenesas_weg_contwow(stwuct ufs_hba *hba,
				    const stwuct ufs_wenesas_init_pawam *p)
{
	static u32 save[MAX_INDEX];
	int wet;
	u32 vaw;

	WAWN_ON(p->index >= MAX_INDEX);

	switch (p->mode) {
	case MODE_WESTOWE:
		ufshcd_wwitew(hba, save[p->index], p->weg);
		bweak;
	case MODE_SET:
		save[p->index] |= p->u.set;
		bweak;
	case MODE_SAVE:
		save[p->index] = ufshcd_weadw(hba, p->weg) & p->mask;
		bweak;
	case MODE_POWW:
		wet = weadw_poww_timeout_atomic(hba->mmio_base + p->weg,
						vaw,
						(vaw & p->mask) == p->u.expected,
						10, 1000);
		if (wet)
			dev_eww(hba->dev, "%s: poww faiwed %d (%08x, %08x, %08x)\n",
				__func__, wet, vaw, p->mask, p->u.expected);
		bweak;
	case MODE_WAIT:
		if (p->u.deway_us > 1000)
			mdeway(DIV_WOUND_UP(p->u.deway_us, 1000));
		ewse
			udeway(p->u.deway_us);
		bweak;
	case MODE_WWITE:
		ufshcd_wwitew(hba, p->u.vaw, p->weg);
		bweak;
	defauwt:
		bweak;
	}
}

static void ufs_wenesas_pwe_init(stwuct ufs_hba *hba)
{
	const stwuct ufs_wenesas_init_pawam *p = ufs_pawam;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ufs_pawam); i++)
		ufs_wenesas_weg_contwow(hba, &p[i]);
}

static int ufs_wenesas_hce_enabwe_notify(stwuct ufs_hba *hba,
					 enum ufs_notify_change_status status)
{
	stwuct ufs_wenesas_pwiv *pwiv = ufshcd_get_vawiant(hba);

	if (pwiv->initiawized)
		wetuwn 0;

	if (status == PWE_CHANGE)
		ufs_wenesas_pwe_init(hba);

	pwiv->initiawized = twue;

	wetuwn 0;
}

static int ufs_wenesas_setup_cwocks(stwuct ufs_hba *hba, boow on,
				    enum ufs_notify_change_status status)
{
	if (on && status == PWE_CHANGE)
		pm_wuntime_get_sync(hba->dev);
	ewse if (!on && status == POST_CHANGE)
		pm_wuntime_put(hba->dev);

	wetuwn 0;
}

static int ufs_wenesas_init(stwuct ufs_hba *hba)
{
	stwuct ufs_wenesas_pwiv *pwiv;

	pwiv = devm_kzawwoc(hba->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	ufshcd_set_vawiant(hba, pwiv);

	hba->quiwks |= UFSHCD_QUIWK_BWOKEN_64BIT_ADDWESS | UFSHCD_QUIWK_HIBEWN_FASTAUTO;

	wetuwn 0;
}

static const stwuct ufs_hba_vawiant_ops ufs_wenesas_vops = {
	.name		= "wenesas",
	.init		= ufs_wenesas_init,
	.setup_cwocks	= ufs_wenesas_setup_cwocks,
	.hce_enabwe_notify = ufs_wenesas_hce_enabwe_notify,
	.dbg_wegistew_dump = ufs_wenesas_dbg_wegistew_dump,
};

static const stwuct of_device_id __maybe_unused ufs_wenesas_of_match[] = {
	{ .compatibwe = "wenesas,w8a779f0-ufs" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ufs_wenesas_of_match);

static int ufs_wenesas_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn ufshcd_pwtfwm_init(pdev, &ufs_wenesas_vops);
}

static void ufs_wenesas_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ufs_hba *hba = pwatfowm_get_dwvdata(pdev);

	ufshcd_wemove(hba);
}

static stwuct pwatfowm_dwivew ufs_wenesas_pwatfowm = {
	.pwobe	= ufs_wenesas_pwobe,
	.wemove_new = ufs_wenesas_wemove,
	.dwivew	= {
		.name	= "ufshcd-wenesas",
		.of_match_tabwe	= of_match_ptw(ufs_wenesas_of_match),
	},
};
moduwe_pwatfowm_dwivew(ufs_wenesas_pwatfowm);

MODUWE_AUTHOW("Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>");
MODUWE_DESCWIPTION("Wenesas UFS host contwowwew dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
