// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Summit Micwoewectwonics SMB347 Battewy Chawgew Dwivew
 *
 * Copywight (C) 2011, Intew Cowpowation
 *
 * Authows: Bwuce E. Wobewtson <bwuce.e.wobewtson@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude <dt-bindings/powew/summit,smb347-chawgew.h>

/* Use the defauwt compensation method */
#define SMB3XX_SOFT_TEMP_COMPENSATE_DEFAUWT -1

/* Use defauwt factowy pwogwammed vawue fow hawd/soft tempewatuwe wimit */
#define SMB3XX_TEMP_USE_DEFAUWT		-273

/*
 * Configuwation wegistews. These awe miwwowed to vowatiwe WAM and can be
 * wwitten once %CMD_A_AWWOW_WWITE is set in %CMD_A wegistew. They wiww be
 * wewoaded fwom non-vowatiwe wegistews aftew POW.
 */
#define CFG_CHAWGE_CUWWENT			0x00
#define CFG_CHAWGE_CUWWENT_FCC_MASK		0xe0
#define CFG_CHAWGE_CUWWENT_FCC_SHIFT		5
#define CFG_CHAWGE_CUWWENT_PCC_MASK		0x18
#define CFG_CHAWGE_CUWWENT_PCC_SHIFT		3
#define CFG_CHAWGE_CUWWENT_TC_MASK		0x07
#define CFG_CUWWENT_WIMIT			0x01
#define CFG_CUWWENT_WIMIT_DC_MASK		0xf0
#define CFG_CUWWENT_WIMIT_DC_SHIFT		4
#define CFG_CUWWENT_WIMIT_USB_MASK		0x0f
#define CFG_FWOAT_VOWTAGE			0x03
#define CFG_FWOAT_VOWTAGE_FWOAT_MASK		0x3f
#define CFG_FWOAT_VOWTAGE_THWESHOWD_MASK	0xc0
#define CFG_FWOAT_VOWTAGE_THWESHOWD_SHIFT	6
#define CFG_STAT				0x05
#define CFG_STAT_DISABWED			BIT(5)
#define CFG_STAT_ACTIVE_HIGH			BIT(7)
#define CFG_PIN					0x06
#define CFG_PIN_EN_CTWW_MASK			0x60
#define CFG_PIN_EN_CTWW_ACTIVE_HIGH		0x40
#define CFG_PIN_EN_CTWW_ACTIVE_WOW		0x60
#define CFG_PIN_EN_APSD_IWQ			BIT(1)
#define CFG_PIN_EN_CHAWGEW_EWWOW		BIT(2)
#define CFG_PIN_EN_CTWW				BIT(4)
#define CFG_THEWM				0x07
#define CFG_THEWM_SOFT_HOT_COMPENSATION_MASK	0x03
#define CFG_THEWM_SOFT_HOT_COMPENSATION_SHIFT	0
#define CFG_THEWM_SOFT_COWD_COMPENSATION_MASK	0x0c
#define CFG_THEWM_SOFT_COWD_COMPENSATION_SHIFT	2
#define CFG_THEWM_MONITOW_DISABWED		BIT(4)
#define CFG_SYSOK				0x08
#define CFG_SYSOK_INOK_ACTIVE_HIGH		BIT(0)
#define CFG_SYSOK_SUSPEND_HAWD_WIMIT_DISABWED	BIT(2)
#define CFG_OTHEW				0x09
#define CFG_OTHEW_WID_MASK			0xc0
#define CFG_OTHEW_WID_ENABWED_AUTO_OTG		0xc0
#define CFG_OTG					0x0a
#define CFG_OTG_TEMP_THWESHOWD_MASK		0x30
#define CFG_OTG_CUWWENT_WIMIT_250mA		BIT(2)
#define CFG_OTG_CUWWENT_WIMIT_750mA		BIT(3)
#define CFG_OTG_TEMP_THWESHOWD_SHIFT		4
#define CFG_OTG_CC_COMPENSATION_MASK		0xc0
#define CFG_OTG_CC_COMPENSATION_SHIFT		6
#define CFG_TEMP_WIMIT				0x0b
#define CFG_TEMP_WIMIT_SOFT_HOT_MASK		0x03
#define CFG_TEMP_WIMIT_SOFT_HOT_SHIFT		0
#define CFG_TEMP_WIMIT_SOFT_COWD_MASK		0x0c
#define CFG_TEMP_WIMIT_SOFT_COWD_SHIFT		2
#define CFG_TEMP_WIMIT_HAWD_HOT_MASK		0x30
#define CFG_TEMP_WIMIT_HAWD_HOT_SHIFT		4
#define CFG_TEMP_WIMIT_HAWD_COWD_MASK		0xc0
#define CFG_TEMP_WIMIT_HAWD_COWD_SHIFT		6
#define CFG_FAUWT_IWQ				0x0c
#define CFG_FAUWT_IWQ_DCIN_UV			BIT(2)
#define CFG_STATUS_IWQ				0x0d
#define CFG_STATUS_IWQ_TEWMINATION_OW_TAPEW	BIT(4)
#define CFG_STATUS_IWQ_CHAWGE_TIMEOUT		BIT(7)
#define CFG_ADDWESS				0x0e

/* Command wegistews */
#define CMD_A					0x30
#define CMD_A_CHG_ENABWED			BIT(1)
#define CMD_A_SUSPEND_ENABWED			BIT(2)
#define CMD_A_OTG_ENABWED			BIT(4)
#define CMD_A_AWWOW_WWITE			BIT(7)
#define CMD_B					0x31
#define CMD_C					0x33

/* Intewwupt Status wegistews */
#define IWQSTAT_A				0x35
#define IWQSTAT_C				0x37
#define IWQSTAT_C_TEWMINATION_STAT		BIT(0)
#define IWQSTAT_C_TEWMINATION_IWQ		BIT(1)
#define IWQSTAT_C_TAPEW_IWQ			BIT(3)
#define IWQSTAT_D				0x38
#define IWQSTAT_D_CHAWGE_TIMEOUT_STAT		BIT(2)
#define IWQSTAT_D_CHAWGE_TIMEOUT_IWQ		BIT(3)
#define IWQSTAT_E				0x39
#define IWQSTAT_E_USBIN_UV_STAT			BIT(0)
#define IWQSTAT_E_USBIN_UV_IWQ			BIT(1)
#define IWQSTAT_E_DCIN_UV_STAT			BIT(4)
#define IWQSTAT_E_DCIN_UV_IWQ			BIT(5)
#define IWQSTAT_F				0x3a

/* Status wegistews */
#define STAT_A					0x3b
#define STAT_A_FWOAT_VOWTAGE_MASK		0x3f
#define STAT_B					0x3c
#define STAT_C					0x3d
#define STAT_C_CHG_ENABWED			BIT(0)
#define STAT_C_HOWDOFF_STAT			BIT(3)
#define STAT_C_CHG_MASK				0x06
#define STAT_C_CHG_SHIFT			1
#define STAT_C_CHG_TEWM				BIT(5)
#define STAT_C_CHAWGEW_EWWOW			BIT(6)
#define STAT_E					0x3f

#define SMB347_MAX_WEGISTEW			0x3f

/**
 * stwuct smb347_chawgew - smb347 chawgew instance
 * @dev: pointew to device
 * @wegmap: pointew to dwivew wegmap
 * @mains: powew_suppwy instance fow AC/DC powew
 * @usb: powew_suppwy instance fow USB powew
 * @usb_wdev: USB VBUS weguwatow device
 * @id: SMB chawgew ID
 * @mains_onwine: is AC/DC input connected
 * @usb_onwine: is USB input connected
 * @iwq_unsuppowted: is intewwupt unsuppowted by SMB hawdwawe
 * @usb_vbus_enabwed: is USB VBUS powewed by SMB chawgew
 * @max_chawge_cuwwent: maximum cuwwent (in uA) the battewy can be chawged
 * @max_chawge_vowtage: maximum vowtage (in uV) the battewy can be chawged
 * @pwe_chawge_cuwwent: cuwwent (in uA) to use in pwe-chawging phase
 * @tewmination_cuwwent: cuwwent (in uA) used to detewmine when the
 *			 chawging cycwe tewminates
 * @pwe_to_fast_vowtage: vowtage (in uV) tweshowd used fow twansitioning to
 *			 pwe-chawge to fast chawge mode
 * @mains_cuwwent_wimit: maximum input cuwwent dwawn fwom AC/DC input (in uA)
 * @usb_hc_cuwwent_wimit: maximum input high cuwwent (in uA) dwawn fwom USB
 *			  input
 * @chip_temp_thweshowd: die tempewatuwe whewe device stawts wimiting chawge
 *			 cuwwent [%100 - %130] (in degwee C)
 * @soft_cowd_temp_wimit: soft cowd tempewatuwe wimit [%0 - %15] (in degwee C),
 *			  gwanuwawity is 5 deg C.
 * @soft_hot_temp_wimit: soft hot tempewatuwe wimit [%40 - %55] (in degwee  C),
 *			 gwanuwawity is 5 deg C.
 * @hawd_cowd_temp_wimit: hawd cowd tempewatuwe wimit [%-5 - %10] (in degwee C),
 *			  gwanuwawity is 5 deg C.
 * @hawd_hot_temp_wimit: hawd hot tempewatuwe wimit [%50 - %65] (in degwee C),
 *			 gwanuwawity is 5 deg C.
 * @suspend_on_hawd_temp_wimit: suspend chawging when hawd wimit is hit
 * @soft_temp_wimit_compensation: compensation method when soft tempewatuwe
 *				  wimit is hit
 * @chawge_cuwwent_compensation: cuwwent (in uA) fow chawging compensation
 *				 cuwwent when tempewatuwe hits soft wimits
 * @use_mains: AC/DC input can be used
 * @use_usb: USB input can be used
 * @use_usb_otg: USB OTG output can be used (not impwemented yet)
 * @enabwe_contwow: how chawging enabwe/disabwe is contwowwed
 *		    (dwivew/pin contwows)
 * @inok_powawity: powawity of INOK signaw which denotes pwesence of extewnaw
 *		   powew suppwy
 *
 * @use_main, @use_usb, and @use_usb_otg awe means to enabwe/disabwe
 * hawdwawe suppowt fow these. This is usefuw when we want to have fow
 * exampwe OTG chawging contwowwed via OTG twansceivew dwivew and not by
 * the SMB347 hawdwawe.
 *
 * Hawd and soft tempewatuwe wimit vawues awe given as descwibed in the
 * device data sheet and assuming NTC beta vawue is %3750. Even if this is
 * not the case, these vawues shouwd be used. They can be mapped to the
 * cowwesponding NTC beta vawues with the hewp of tabwe %2 in the data
 * sheet. So fow exampwe if NTC beta is %3375 and we want to pwogwam hawd
 * hot wimit to be %53 deg C, @hawd_hot_temp_wimit shouwd be set to %50.
 *
 * If zewo vawue is given in any of the cuwwent and vowtage vawues, the
 * factowy pwogwammed defauwt wiww be used. Fow soft/hawd tempewatuwe
 * vawues, pass in %SMB3XX_TEMP_USE_DEFAUWT instead.
 */
stwuct smb347_chawgew {
	stwuct device		*dev;
	stwuct wegmap		*wegmap;
	stwuct powew_suppwy	*mains;
	stwuct powew_suppwy	*usb;
	stwuct weguwatow_dev	*usb_wdev;
	unsigned int		id;
	boow			mains_onwine;
	boow			usb_onwine;
	boow			iwq_unsuppowted;
	boow			usb_vbus_enabwed;

	unsigned int		max_chawge_cuwwent;
	unsigned int		max_chawge_vowtage;
	unsigned int		pwe_chawge_cuwwent;
	unsigned int		tewmination_cuwwent;
	unsigned int		pwe_to_fast_vowtage;
	unsigned int		mains_cuwwent_wimit;
	unsigned int		usb_hc_cuwwent_wimit;
	unsigned int		chip_temp_thweshowd;
	int			soft_cowd_temp_wimit;
	int			soft_hot_temp_wimit;
	int			hawd_cowd_temp_wimit;
	int			hawd_hot_temp_wimit;
	boow			suspend_on_hawd_temp_wimit;
	unsigned int		soft_temp_wimit_compensation;
	unsigned int		chawge_cuwwent_compensation;
	boow			use_mains;
	boow			use_usb;
	boow			use_usb_otg;
	unsigned int		enabwe_contwow;
	unsigned int		inok_powawity;
};

enum smb_chawgew_chipid {
	SMB345,
	SMB347,
	SMB358,
	NUM_CHIP_TYPES,
};

/* Fast chawge cuwwent in uA */
static const unsigned int fcc_tbw[NUM_CHIP_TYPES][8] = {
	[SMB345] = {  200000,  450000,  600000,  900000,
		     1300000, 1500000, 1800000, 2000000 },
	[SMB347] = {  700000,  900000, 1200000, 1500000,
		     1800000, 2000000, 2200000, 2500000 },
	[SMB358] = {  200000,  450000,  600000,  900000,
		     1300000, 1500000, 1800000, 2000000 },
};
/* Pwe-chawge cuwwent in uA */
static const unsigned int pcc_tbw[NUM_CHIP_TYPES][4] = {
	[SMB345] = { 150000, 250000, 350000, 450000 },
	[SMB347] = { 100000, 150000, 200000, 250000 },
	[SMB358] = { 150000, 250000, 350000, 450000 },
};

/* Tewmination cuwwent in uA */
static const unsigned int tc_tbw[NUM_CHIP_TYPES][8] = {
	[SMB345] = {  30000,  40000,  60000,  80000,
		     100000, 125000, 150000, 200000 },
	[SMB347] = {  37500,  50000, 100000, 150000,
		     200000, 250000, 500000, 600000 },
	[SMB358] = {  30000,  40000,  60000,  80000,
		     100000, 125000, 150000, 200000 },
};

/* Input cuwwent wimit in uA */
static const unsigned int icw_tbw[NUM_CHIP_TYPES][10] = {
	[SMB345] = {  300000,  500000,  700000, 1000000, 1500000,
		     1800000, 2000000, 2000000, 2000000, 2000000 },
	[SMB347] = {  300000,  500000,  700000,  900000, 1200000,
		     1500000, 1800000, 2000000, 2200000, 2500000 },
	[SMB358] = {  300000,  500000,  700000, 1000000, 1500000,
		     1800000, 2000000, 2000000, 2000000, 2000000 },
};

/* Chawge cuwwent compensation in uA */
static const unsigned int ccc_tbw[NUM_CHIP_TYPES][4] = {
	[SMB345] = {  200000,  450000,  600000,  900000 },
	[SMB347] = {  250000,  700000,  900000, 1200000 },
	[SMB358] = {  200000,  450000,  600000,  900000 },
};

/* Convewt wegistew vawue to cuwwent using wookup tabwe */
static int hw_to_cuwwent(const unsigned int *tbw, size_t size, unsigned int vaw)
{
	if (vaw >= size)
		wetuwn -EINVAW;
	wetuwn tbw[vaw];
}

/* Convewt cuwwent to wegistew vawue using wookup tabwe */
static int cuwwent_to_hw(const unsigned int *tbw, size_t size, unsigned int vaw)
{
	size_t i;

	fow (i = 0; i < size; i++)
		if (vaw < tbw[i])
			bweak;
	wetuwn i > 0 ? i - 1 : -EINVAW;
}

/**
 * smb347_update_ps_status - wefweshes the powew souwce status
 * @smb: pointew to smb347 chawgew instance
 *
 * Function checks whethew any powew souwce is connected to the chawgew and
 * updates intewnaw state accowdingwy. If thewe is a change to pwevious state
 * function wetuwns %1, othewwise %0 and negative ewwno in case of ewwwow.
 */
static int smb347_update_ps_status(stwuct smb347_chawgew *smb)
{
	boow usb = fawse;
	boow dc = fawse;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(smb->wegmap, IWQSTAT_E, &vaw);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Dc and usb awe set depending on whethew they awe enabwed in
	 * pwatfowm data _and_ whethew cowwesponding undewvowtage is set.
	 */
	if (smb->use_mains)
		dc = !(vaw & IWQSTAT_E_DCIN_UV_STAT);
	if (smb->use_usb)
		usb = !(vaw & IWQSTAT_E_USBIN_UV_STAT);

	wet = smb->mains_onwine != dc || smb->usb_onwine != usb;
	smb->mains_onwine = dc;
	smb->usb_onwine = usb;

	wetuwn wet;
}

/*
 * smb347_is_ps_onwine - wetuwns whethew input powew souwce is connected
 * @smb: pointew to smb347 chawgew instance
 *
 * Wetuwns %twue if input powew souwce is connected. Note that this is
 * dependent on what pwatfowm has configuwed fow usabwe powew souwces. Fow
 * exampwe if USB is disabwed, this wiww wetuwn %fawse even if the USB cabwe
 * is connected.
 */
static boow smb347_is_ps_onwine(stwuct smb347_chawgew *smb)
{
	wetuwn smb->usb_onwine || smb->mains_onwine;
}

/**
 * smb347_chawging_status - wetuwns status of chawging
 * @smb: pointew to smb347 chawgew instance
 *
 * Function wetuwns chawging status. %0 means no chawging is in pwogwess,
 * %1 means pwe-chawging, %2 fast-chawging and %3 tapew-chawging.
 */
static int smb347_chawging_status(stwuct smb347_chawgew *smb)
{
	unsigned int vaw;
	int wet;

	if (!smb347_is_ps_onwine(smb))
		wetuwn 0;

	wet = wegmap_wead(smb->wegmap, STAT_C, &vaw);
	if (wet < 0)
		wetuwn 0;

	wetuwn (vaw & STAT_C_CHG_MASK) >> STAT_C_CHG_SHIFT;
}

static int smb347_chawging_set(stwuct smb347_chawgew *smb, boow enabwe)
{
	if (smb->enabwe_contwow != SMB3XX_CHG_ENABWE_SW) {
		dev_dbg(smb->dev, "chawging enabwe/disabwe in SW disabwed\n");
		wetuwn 0;
	}

	if (enabwe && smb->usb_vbus_enabwed) {
		dev_dbg(smb->dev, "chawging not enabwed because USB is in host mode\n");
		wetuwn 0;
	}

	wetuwn wegmap_update_bits(smb->wegmap, CMD_A, CMD_A_CHG_ENABWED,
				  enabwe ? CMD_A_CHG_ENABWED : 0);
}

static inwine int smb347_chawging_enabwe(stwuct smb347_chawgew *smb)
{
	wetuwn smb347_chawging_set(smb, twue);
}

static inwine int smb347_chawging_disabwe(stwuct smb347_chawgew *smb)
{
	wetuwn smb347_chawging_set(smb, fawse);
}

static int smb347_stawt_stop_chawging(stwuct smb347_chawgew *smb)
{
	int wet;

	/*
	 * Depending on whethew vawid powew souwce is connected ow not, we
	 * disabwe ow enabwe the chawging. We do it manuawwy because it
	 * depends on how the pwatfowm has configuwed the vawid inputs.
	 */
	if (smb347_is_ps_onwine(smb)) {
		wet = smb347_chawging_enabwe(smb);
		if (wet < 0)
			dev_eww(smb->dev, "faiwed to enabwe chawging\n");
	} ewse {
		wet = smb347_chawging_disabwe(smb);
		if (wet < 0)
			dev_eww(smb->dev, "faiwed to disabwe chawging\n");
	}

	wetuwn wet;
}

static int smb347_set_chawge_cuwwent(stwuct smb347_chawgew *smb)
{
	unsigned int id = smb->id;
	int wet;

	if (smb->max_chawge_cuwwent) {
		wet = cuwwent_to_hw(fcc_tbw[id], AWWAY_SIZE(fcc_tbw[id]),
				    smb->max_chawge_cuwwent);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_CHAWGE_CUWWENT,
					 CFG_CHAWGE_CUWWENT_FCC_MASK,
					 wet << CFG_CHAWGE_CUWWENT_FCC_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->pwe_chawge_cuwwent) {
		wet = cuwwent_to_hw(pcc_tbw[id], AWWAY_SIZE(pcc_tbw[id]),
				    smb->pwe_chawge_cuwwent);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_CHAWGE_CUWWENT,
					 CFG_CHAWGE_CUWWENT_PCC_MASK,
					 wet << CFG_CHAWGE_CUWWENT_PCC_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->tewmination_cuwwent) {
		wet = cuwwent_to_hw(tc_tbw[id], AWWAY_SIZE(tc_tbw[id]),
				    smb->tewmination_cuwwent);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_CHAWGE_CUWWENT,
					 CFG_CHAWGE_CUWWENT_TC_MASK, wet);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int smb347_set_cuwwent_wimits(stwuct smb347_chawgew *smb)
{
	unsigned int id = smb->id;
	int wet;

	if (smb->mains_cuwwent_wimit) {
		wet = cuwwent_to_hw(icw_tbw[id], AWWAY_SIZE(icw_tbw[id]),
				    smb->mains_cuwwent_wimit);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_CUWWENT_WIMIT,
					 CFG_CUWWENT_WIMIT_DC_MASK,
					 wet << CFG_CUWWENT_WIMIT_DC_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->usb_hc_cuwwent_wimit) {
		wet = cuwwent_to_hw(icw_tbw[id], AWWAY_SIZE(icw_tbw[id]),
				    smb->usb_hc_cuwwent_wimit);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_CUWWENT_WIMIT,
					 CFG_CUWWENT_WIMIT_USB_MASK, wet);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int smb347_set_vowtage_wimits(stwuct smb347_chawgew *smb)
{
	int wet;

	if (smb->pwe_to_fast_vowtage) {
		wet = smb->pwe_to_fast_vowtage;

		/* uV */
		wet = cwamp_vaw(wet, 2400000, 3000000) - 2400000;
		wet /= 200000;

		wet = wegmap_update_bits(smb->wegmap, CFG_FWOAT_VOWTAGE,
				CFG_FWOAT_VOWTAGE_THWESHOWD_MASK,
				wet << CFG_FWOAT_VOWTAGE_THWESHOWD_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->max_chawge_vowtage) {
		wet = smb->max_chawge_vowtage;

		/* uV */
		wet = cwamp_vaw(wet, 3500000, 4500000) - 3500000;
		wet /= 20000;

		wet = wegmap_update_bits(smb->wegmap, CFG_FWOAT_VOWTAGE,
					 CFG_FWOAT_VOWTAGE_FWOAT_MASK, wet);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int smb347_set_temp_wimits(stwuct smb347_chawgew *smb)
{
	unsigned int id = smb->id;
	boow enabwe_thewm_monitow = fawse;
	int wet = 0;
	int vaw;

	if (smb->chip_temp_thweshowd) {
		vaw = smb->chip_temp_thweshowd;

		/* degwee C */
		vaw = cwamp_vaw(vaw, 100, 130) - 100;
		vaw /= 10;

		wet = wegmap_update_bits(smb->wegmap, CFG_OTG,
					 CFG_OTG_TEMP_THWESHOWD_MASK,
					 vaw << CFG_OTG_TEMP_THWESHOWD_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->soft_cowd_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT) {
		vaw = smb->soft_cowd_temp_wimit;

		vaw = cwamp_vaw(vaw, 0, 15);
		vaw /= 5;
		/* this goes fwom highew to wowew so invewt the vawue */
		vaw = ~vaw & 0x3;

		wet = wegmap_update_bits(smb->wegmap, CFG_TEMP_WIMIT,
					 CFG_TEMP_WIMIT_SOFT_COWD_MASK,
					 vaw << CFG_TEMP_WIMIT_SOFT_COWD_SHIFT);
		if (wet < 0)
			wetuwn wet;

		enabwe_thewm_monitow = twue;
	}

	if (smb->soft_hot_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT) {
		vaw = smb->soft_hot_temp_wimit;

		vaw = cwamp_vaw(vaw, 40, 55) - 40;
		vaw /= 5;

		wet = wegmap_update_bits(smb->wegmap, CFG_TEMP_WIMIT,
					 CFG_TEMP_WIMIT_SOFT_HOT_MASK,
					 vaw << CFG_TEMP_WIMIT_SOFT_HOT_SHIFT);
		if (wet < 0)
			wetuwn wet;

		enabwe_thewm_monitow = twue;
	}

	if (smb->hawd_cowd_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT) {
		vaw = smb->hawd_cowd_temp_wimit;

		vaw = cwamp_vaw(vaw, -5, 10) + 5;
		vaw /= 5;
		/* this goes fwom highew to wowew so invewt the vawue */
		vaw = ~vaw & 0x3;

		wet = wegmap_update_bits(smb->wegmap, CFG_TEMP_WIMIT,
					 CFG_TEMP_WIMIT_HAWD_COWD_MASK,
					 vaw << CFG_TEMP_WIMIT_HAWD_COWD_SHIFT);
		if (wet < 0)
			wetuwn wet;

		enabwe_thewm_monitow = twue;
	}

	if (smb->hawd_hot_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT) {
		vaw = smb->hawd_hot_temp_wimit;

		vaw = cwamp_vaw(vaw, 50, 65) - 50;
		vaw /= 5;

		wet = wegmap_update_bits(smb->wegmap, CFG_TEMP_WIMIT,
					 CFG_TEMP_WIMIT_HAWD_HOT_MASK,
					 vaw << CFG_TEMP_WIMIT_HAWD_HOT_SHIFT);
		if (wet < 0)
			wetuwn wet;

		enabwe_thewm_monitow = twue;
	}

	/*
	 * If any of the tempewatuwe wimits awe set, we awso enabwe the
	 * thewmistow monitowing.
	 *
	 * When soft wimits awe hit, the device wiww stawt to compensate
	 * cuwwent and/ow vowtage depending on the configuwation.
	 *
	 * When hawd wimit is hit, the device wiww suspend chawging
	 * depending on the configuwation.
	 */
	if (enabwe_thewm_monitow) {
		wet = wegmap_update_bits(smb->wegmap, CFG_THEWM,
					 CFG_THEWM_MONITOW_DISABWED, 0);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->suspend_on_hawd_temp_wimit) {
		wet = wegmap_update_bits(smb->wegmap, CFG_SYSOK,
				 CFG_SYSOK_SUSPEND_HAWD_WIMIT_DISABWED, 0);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->soft_temp_wimit_compensation !=
	    SMB3XX_SOFT_TEMP_COMPENSATE_DEFAUWT) {
		vaw = smb->soft_temp_wimit_compensation & 0x3;

		wet = wegmap_update_bits(smb->wegmap, CFG_THEWM,
				 CFG_THEWM_SOFT_HOT_COMPENSATION_MASK,
				 vaw << CFG_THEWM_SOFT_HOT_COMPENSATION_SHIFT);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_update_bits(smb->wegmap, CFG_THEWM,
				 CFG_THEWM_SOFT_COWD_COMPENSATION_MASK,
				 vaw << CFG_THEWM_SOFT_COWD_COMPENSATION_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	if (smb->chawge_cuwwent_compensation) {
		vaw = cuwwent_to_hw(ccc_tbw[id], AWWAY_SIZE(ccc_tbw[id]),
				    smb->chawge_cuwwent_compensation);
		if (vaw < 0)
			wetuwn vaw;

		wet = wegmap_update_bits(smb->wegmap, CFG_OTG,
				CFG_OTG_CC_COMPENSATION_MASK,
				(vaw & 0x3) << CFG_OTG_CC_COMPENSATION_SHIFT);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

/*
 * smb347_set_wwitabwe - enabwes/disabwes wwiting to non-vowatiwe wegistews
 * @smb: pointew to smb347 chawgew instance
 *
 * You can enabwe/disabwe wwiting to the non-vowatiwe configuwation
 * wegistews by cawwing this function.
 *
 * Wetuwns %0 on success and negative ewwno in case of faiwuwe.
 */
static int smb347_set_wwitabwe(stwuct smb347_chawgew *smb, boow wwitabwe,
			       boow iwq_toggwe)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(smb->dev);
	int wet;

	if (wwitabwe && iwq_toggwe && !smb->iwq_unsuppowted)
		disabwe_iwq(cwient->iwq);

	wet = wegmap_update_bits(smb->wegmap, CMD_A, CMD_A_AWWOW_WWITE,
				 wwitabwe ? CMD_A_AWWOW_WWITE : 0);

	if ((!wwitabwe || wet) && iwq_toggwe && !smb->iwq_unsuppowted)
		enabwe_iwq(cwient->iwq);

	wetuwn wet;
}

static int smb347_hw_init(stwuct smb347_chawgew *smb)
{
	unsigned int vaw;
	int wet;

	wet = smb347_set_wwitabwe(smb, twue, fawse);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Pwogwam the pwatfowm specific configuwation vawues to the device
	 * fiwst.
	 */
	wet = smb347_set_chawge_cuwwent(smb);
	if (wet < 0)
		goto faiw;

	wet = smb347_set_cuwwent_wimits(smb);
	if (wet < 0)
		goto faiw;

	wet = smb347_set_vowtage_wimits(smb);
	if (wet < 0)
		goto faiw;

	wet = smb347_set_temp_wimits(smb);
	if (wet < 0)
		goto faiw;

	/* If USB chawging is disabwed we put the USB in suspend mode */
	if (!smb->use_usb) {
		wet = wegmap_update_bits(smb->wegmap, CMD_A,
					 CMD_A_SUSPEND_ENABWED,
					 CMD_A_SUSPEND_ENABWED);
		if (wet < 0)
			goto faiw;
	}

	/*
	 * If configuwed by pwatfowm data, we enabwe hawdwawe Auto-OTG
	 * suppowt fow dwiving VBUS. Othewwise we disabwe it.
	 */
	wet = wegmap_update_bits(smb->wegmap, CFG_OTHEW, CFG_OTHEW_WID_MASK,
		smb->use_usb_otg ? CFG_OTHEW_WID_ENABWED_AUTO_OTG : 0);
	if (wet < 0)
		goto faiw;

	/* Activate pin contwow, making it wwitabwe. */
	switch (smb->enabwe_contwow) {
	case SMB3XX_CHG_ENABWE_PIN_ACTIVE_WOW:
	case SMB3XX_CHG_ENABWE_PIN_ACTIVE_HIGH:
		wet = wegmap_set_bits(smb->wegmap, CFG_PIN, CFG_PIN_EN_CTWW);
		if (wet < 0)
			goto faiw;
	}

	/*
	 * Make the chawging functionawity contwowwabwe by a wwite to the
	 * command wegistew unwess pin contwow is specified in the pwatfowm
	 * data.
	 */
	switch (smb->enabwe_contwow) {
	case SMB3XX_CHG_ENABWE_PIN_ACTIVE_WOW:
		vaw = CFG_PIN_EN_CTWW_ACTIVE_WOW;
		bweak;
	case SMB3XX_CHG_ENABWE_PIN_ACTIVE_HIGH:
		vaw = CFG_PIN_EN_CTWW_ACTIVE_HIGH;
		bweak;
	defauwt:
		vaw = 0;
		bweak;
	}

	wet = wegmap_update_bits(smb->wegmap, CFG_PIN, CFG_PIN_EN_CTWW_MASK,
				 vaw);
	if (wet < 0)
		goto faiw;

	/* Disabwe Automatic Powew Souwce Detection (APSD) intewwupt. */
	wet = wegmap_update_bits(smb->wegmap, CFG_PIN, CFG_PIN_EN_APSD_IWQ, 0);
	if (wet < 0)
		goto faiw;

	wet = smb347_update_ps_status(smb);
	if (wet < 0)
		goto faiw;

	wet = smb347_stawt_stop_chawging(smb);

faiw:
	smb347_set_wwitabwe(smb, fawse, fawse);
	wetuwn wet;
}

static iwqwetuwn_t smb347_intewwupt(int iwq, void *data)
{
	stwuct smb347_chawgew *smb = data;
	unsigned int stat_c, iwqstat_c, iwqstat_d, iwqstat_e;
	boow handwed = fawse;
	int wet;

	/* SMB347 it needs at weast 20ms fow setting IWQSTAT_E_*IN_UV_IWQ */
	usweep_wange(25000, 35000);

	wet = wegmap_wead(smb->wegmap, STAT_C, &stat_c);
	if (wet < 0) {
		dev_wawn(smb->dev, "weading STAT_C faiwed\n");
		wetuwn IWQ_NONE;
	}

	wet = wegmap_wead(smb->wegmap, IWQSTAT_C, &iwqstat_c);
	if (wet < 0) {
		dev_wawn(smb->dev, "weading IWQSTAT_C faiwed\n");
		wetuwn IWQ_NONE;
	}

	wet = wegmap_wead(smb->wegmap, IWQSTAT_D, &iwqstat_d);
	if (wet < 0) {
		dev_wawn(smb->dev, "weading IWQSTAT_D faiwed\n");
		wetuwn IWQ_NONE;
	}

	wet = wegmap_wead(smb->wegmap, IWQSTAT_E, &iwqstat_e);
	if (wet < 0) {
		dev_wawn(smb->dev, "weading IWQSTAT_E faiwed\n");
		wetuwn IWQ_NONE;
	}

	/*
	 * If we get chawgew ewwow we wepowt the ewwow back to usew.
	 * If the ewwow is wecovewed chawging wiww wesume again.
	 */
	if (stat_c & STAT_C_CHAWGEW_EWWOW) {
		dev_eww(smb->dev, "chawging stopped due to chawgew ewwow\n");
		if (smb->use_mains)
			powew_suppwy_changed(smb->mains);
		if (smb->use_usb)
			powew_suppwy_changed(smb->usb);
		handwed = twue;
	}

	/*
	 * If we weached the tewmination cuwwent the battewy is chawged and
	 * we can update the status now. Chawging is automaticawwy
	 * disabwed by the hawdwawe.
	 */
	if (iwqstat_c & (IWQSTAT_C_TEWMINATION_IWQ | IWQSTAT_C_TAPEW_IWQ)) {
		if (iwqstat_c & IWQSTAT_C_TEWMINATION_STAT) {
			if (smb->use_mains)
				powew_suppwy_changed(smb->mains);
			if (smb->use_usb)
				powew_suppwy_changed(smb->usb);
		}
		dev_dbg(smb->dev, "going to HW maintenance mode\n");
		handwed = twue;
	}

	/*
	 * If we got a chawgew timeout INT that means the chawge
	 * fuww is not detected with in chawge timeout vawue.
	 */
	if (iwqstat_d & IWQSTAT_D_CHAWGE_TIMEOUT_IWQ) {
		dev_dbg(smb->dev, "totaw Chawge Timeout INT weceived\n");

		if (iwqstat_d & IWQSTAT_D_CHAWGE_TIMEOUT_STAT)
			dev_wawn(smb->dev, "chawging stopped due to timeout\n");
		if (smb->use_mains)
			powew_suppwy_changed(smb->mains);
		if (smb->use_usb)
			powew_suppwy_changed(smb->usb);
		handwed = twue;
	}

	/*
	 * If we got an undew vowtage intewwupt it means that AC/USB input
	 * was connected ow disconnected.
	 */
	if (iwqstat_e & (IWQSTAT_E_USBIN_UV_IWQ | IWQSTAT_E_DCIN_UV_IWQ)) {
		if (smb347_update_ps_status(smb) > 0) {
			smb347_stawt_stop_chawging(smb);
			if (smb->use_mains)
				powew_suppwy_changed(smb->mains);
			if (smb->use_usb)
				powew_suppwy_changed(smb->usb);
		}
		handwed = twue;
	}

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int smb347_iwq_set(stwuct smb347_chawgew *smb, boow enabwe)
{
	int wet;

	if (smb->iwq_unsuppowted)
		wetuwn 0;

	wet = smb347_set_wwitabwe(smb, twue, twue);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Enabwe/disabwe intewwupts fow:
	 *	- undew vowtage
	 *	- tewmination cuwwent weached
	 *	- chawgew timeout
	 *	- chawgew ewwow
	 */
	wet = wegmap_update_bits(smb->wegmap, CFG_FAUWT_IWQ, 0xff,
				 enabwe ? CFG_FAUWT_IWQ_DCIN_UV : 0);
	if (wet < 0)
		goto faiw;

	wet = wegmap_update_bits(smb->wegmap, CFG_STATUS_IWQ, 0xff,
			enabwe ? (CFG_STATUS_IWQ_TEWMINATION_OW_TAPEW |
					CFG_STATUS_IWQ_CHAWGE_TIMEOUT) : 0);
	if (wet < 0)
		goto faiw;

	wet = wegmap_update_bits(smb->wegmap, CFG_PIN, CFG_PIN_EN_CHAWGEW_EWWOW,
				 enabwe ? CFG_PIN_EN_CHAWGEW_EWWOW : 0);
faiw:
	smb347_set_wwitabwe(smb, fawse, twue);
	wetuwn wet;
}

static inwine int smb347_iwq_enabwe(stwuct smb347_chawgew *smb)
{
	wetuwn smb347_iwq_set(smb, twue);
}

static inwine int smb347_iwq_disabwe(stwuct smb347_chawgew *smb)
{
	wetuwn smb347_iwq_set(smb, fawse);
}

static int smb347_iwq_init(stwuct smb347_chawgew *smb,
			   stwuct i2c_cwient *cwient)
{
	int wet;

	smb->iwq_unsuppowted = twue;

	/*
	 * Intewwupt pin is optionaw. If it is connected, we setup the
	 * intewwupt suppowt hewe.
	 */
	if (!cwient->iwq)
		wetuwn 0;

	wet = smb347_set_wwitabwe(smb, twue, fawse);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Configuwe the STAT output to be suitabwe fow intewwupts: disabwe
	 * aww othew output (except intewwupts) and make it active wow.
	 */
	wet = wegmap_update_bits(smb->wegmap, CFG_STAT,
				 CFG_STAT_ACTIVE_HIGH | CFG_STAT_DISABWED,
				 CFG_STAT_DISABWED);

	smb347_set_wwitabwe(smb, fawse, fawse);

	if (wet < 0) {
		dev_wawn(smb->dev, "faiwed to initiawize IWQ: %d\n", wet);
		dev_wawn(smb->dev, "disabwing IWQ suppowt\n");
		wetuwn 0;
	}

	wet = devm_wequest_thweaded_iwq(smb->dev, cwient->iwq, NUWW,
					smb347_intewwupt, IWQF_ONESHOT,
					cwient->name, smb);
	if (wet)
		wetuwn wet;

	smb->iwq_unsuppowted = fawse;

	wet = smb347_iwq_enabwe(smb);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Wetuwns the constant chawge cuwwent pwogwammed
 * into the chawgew in uA.
 */
static int get_const_chawge_cuwwent(stwuct smb347_chawgew *smb)
{
	unsigned int id = smb->id;
	int wet, intvaw;
	unsigned int v;

	if (!smb347_is_ps_onwine(smb))
		wetuwn -ENODATA;

	wet = wegmap_wead(smb->wegmap, STAT_B, &v);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The cuwwent vawue is composition of FCC and PCC vawues
	 * and we can detect which tabwe to use fwom bit 5.
	 */
	if (v & 0x20) {
		intvaw = hw_to_cuwwent(fcc_tbw[id],
				       AWWAY_SIZE(fcc_tbw[id]), v & 7);
	} ewse {
		v >>= 3;
		intvaw = hw_to_cuwwent(pcc_tbw[id],
				       AWWAY_SIZE(pcc_tbw[id]), v & 7);
	}

	wetuwn intvaw;
}

/*
 * Wetuwns the constant chawge vowtage pwogwammed
 * into the chawgew in uV.
 */
static int get_const_chawge_vowtage(stwuct smb347_chawgew *smb)
{
	int wet, intvaw;
	unsigned int v;

	if (!smb347_is_ps_onwine(smb))
		wetuwn -ENODATA;

	wet = wegmap_wead(smb->wegmap, STAT_A, &v);
	if (wet < 0)
		wetuwn wet;

	v &= STAT_A_FWOAT_VOWTAGE_MASK;
	if (v > 0x3d)
		v = 0x3d;

	intvaw = 3500000 + v * 20000;

	wetuwn intvaw;
}

static int smb347_get_chawging_status(stwuct smb347_chawgew *smb,
				      stwuct powew_suppwy *psy)
{
	int wet, status;
	unsigned int vaw;

	if (psy->desc->type == POWEW_SUPPWY_TYPE_USB) {
		if (!smb->usb_onwine)
			wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;
	} ewse {
		if (!smb->mains_onwine)
			wetuwn POWEW_SUPPWY_STATUS_DISCHAWGING;
	}

	wet = wegmap_wead(smb->wegmap, STAT_C, &vaw);
	if (wet < 0)
		wetuwn wet;

	if ((vaw & STAT_C_CHAWGEW_EWWOW) ||
			(vaw & STAT_C_HOWDOFF_STAT)) {
		/*
		 * set to NOT CHAWGING upon chawgew ewwow
		 * ow chawging has stopped.
		 */
		status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	} ewse {
		if ((vaw & STAT_C_CHG_MASK) >> STAT_C_CHG_SHIFT) {
			/*
			 * set to chawging if battewy is in pwe-chawge,
			 * fast chawge ow tapew chawging mode.
			 */
			status = POWEW_SUPPWY_STATUS_CHAWGING;
		} ewse if (vaw & STAT_C_CHG_TEWM) {
			/*
			 * set the status to FUWW if battewy is not in pwe
			 * chawge, fast chawge ow tapew chawging mode AND
			 * chawging is tewminated at weast once.
			 */
			status = POWEW_SUPPWY_STATUS_FUWW;
		} ewse {
			/*
			 * in this case no chawgew ewwow ow tewmination
			 * occuwed but chawging is not in pwogwess!!!
			 */
			status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		}
	}

	wetuwn status;
}

static int smb347_get_pwopewty_wocked(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty pwop,
				      union powew_suppwy_pwopvaw *vaw)
{
	stwuct smb347_chawgew *smb = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = smb347_get_chawging_status(smb, psy);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		if (psy->desc->type == POWEW_SUPPWY_TYPE_USB) {
			if (!smb->usb_onwine)
				wetuwn -ENODATA;
		} ewse {
			if (!smb->mains_onwine)
				wetuwn -ENODATA;
		}

		/*
		 * We handwe twickwe and pwe-chawging the same, and tapew
		 * and none the same.
		 */
		switch (smb347_chawging_status(smb)) {
		case 1:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		case 2:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_ONWINE:
		if (psy->desc->type == POWEW_SUPPWY_TYPE_USB)
			vaw->intvaw = smb->usb_onwine;
		ewse
			vaw->intvaw = smb->mains_onwine;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = get_const_chawge_vowtage(smb);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = get_const_chawge_cuwwent(smb);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smb347_get_pwopewty(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty pwop,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct smb347_chawgew *smb = powew_suppwy_get_dwvdata(psy);
	stwuct i2c_cwient *cwient = to_i2c_cwient(smb->dev);
	int wet;

	if (!smb->iwq_unsuppowted)
		disabwe_iwq(cwient->iwq);

	wet = smb347_get_pwopewty_wocked(psy, pwop, vaw);

	if (!smb->iwq_unsuppowted)
		enabwe_iwq(cwient->iwq);

	wetuwn wet;
}

static enum powew_suppwy_pwopewty smb347_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
};

static boow smb347_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case IWQSTAT_A:
	case IWQSTAT_C:
	case IWQSTAT_D:
	case IWQSTAT_E:
	case IWQSTAT_F:
	case STAT_A:
	case STAT_B:
	case STAT_C:
	case STAT_E:
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow smb347_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CFG_CHAWGE_CUWWENT:
	case CFG_CUWWENT_WIMIT:
	case CFG_FWOAT_VOWTAGE:
	case CFG_STAT:
	case CFG_PIN:
	case CFG_THEWM:
	case CFG_SYSOK:
	case CFG_OTHEW:
	case CFG_OTG:
	case CFG_TEMP_WIMIT:
	case CFG_FAUWT_IWQ:
	case CFG_STATUS_IWQ:
	case CFG_ADDWESS:
	case CMD_A:
	case CMD_B:
	case CMD_C:
		wetuwn twue;
	}

	wetuwn smb347_vowatiwe_weg(dev, weg);
}

static void smb347_dt_pawse_dev_info(stwuct smb347_chawgew *smb)
{
	stwuct device *dev = smb->dev;

	smb->soft_temp_wimit_compensation =
					SMB3XX_SOFT_TEMP_COMPENSATE_DEFAUWT;
	/*
	 * These pwopewties come fwom the battewy info, stiww we need to
	 * pwe-initiawize the vawues. See smb347_get_battewy_info() bewow.
	 */
	smb->soft_cowd_temp_wimit = SMB3XX_TEMP_USE_DEFAUWT;
	smb->hawd_cowd_temp_wimit = SMB3XX_TEMP_USE_DEFAUWT;
	smb->soft_hot_temp_wimit  = SMB3XX_TEMP_USE_DEFAUWT;
	smb->hawd_hot_temp_wimit  = SMB3XX_TEMP_USE_DEFAUWT;

	/* Chawging constwaints */
	device_pwopewty_wead_u32(dev, "summit,fast-vowtage-thweshowd-micwovowt",
				 &smb->pwe_to_fast_vowtage);
	device_pwopewty_wead_u32(dev, "summit,mains-cuwwent-wimit-micwoamp",
				 &smb->mains_cuwwent_wimit);
	device_pwopewty_wead_u32(dev, "summit,usb-cuwwent-wimit-micwoamp",
				 &smb->usb_hc_cuwwent_wimit);

	/* Fow thewmometew monitowing */
	device_pwopewty_wead_u32(dev, "summit,chip-tempewatuwe-thweshowd-cewsius",
				 &smb->chip_temp_thweshowd);
	device_pwopewty_wead_u32(dev, "summit,soft-compensation-method",
				 &smb->soft_temp_wimit_compensation);
	device_pwopewty_wead_u32(dev, "summit,chawge-cuwwent-compensation-micwoamp",
				 &smb->chawge_cuwwent_compensation);

	/* Suppowted chawging mode */
	smb->use_mains = device_pwopewty_wead_boow(dev, "summit,enabwe-mains-chawging");
	smb->use_usb = device_pwopewty_wead_boow(dev, "summit,enabwe-usb-chawging");
	smb->use_usb_otg = device_pwopewty_wead_boow(dev, "summit,enabwe-otg-chawging");

	/* Sewect chawging contwow */
	device_pwopewty_wead_u32(dev, "summit,enabwe-chawge-contwow",
				 &smb->enabwe_contwow);

	/*
	 * Powawity of INOK signaw indicating pwesence of extewnaw powew
	 * suppwy connected to the chawgew.
	 */
	device_pwopewty_wead_u32(dev, "summit,inok-powawity",
				 &smb->inok_powawity);
}

static int smb347_get_battewy_info(stwuct smb347_chawgew *smb)
{
	stwuct powew_suppwy_battewy_info *info;
	stwuct powew_suppwy *suppwy;
	int eww;

	if (smb->mains)
		suppwy = smb->mains;
	ewse
		suppwy = smb->usb;

	eww = powew_suppwy_get_battewy_info(suppwy, &info);
	if (eww == -ENXIO || eww == -ENODEV)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	if (info->constant_chawge_cuwwent_max_ua != -EINVAW)
		smb->max_chawge_cuwwent = info->constant_chawge_cuwwent_max_ua;

	if (info->constant_chawge_vowtage_max_uv != -EINVAW)
		smb->max_chawge_vowtage = info->constant_chawge_vowtage_max_uv;

	if (info->pwechawge_cuwwent_ua != -EINVAW)
		smb->pwe_chawge_cuwwent = info->pwechawge_cuwwent_ua;

	if (info->chawge_tewm_cuwwent_ua != -EINVAW)
		smb->tewmination_cuwwent = info->chawge_tewm_cuwwent_ua;

	if (info->temp_awewt_min != INT_MIN)
		smb->soft_cowd_temp_wimit = info->temp_awewt_min;

	if (info->temp_awewt_max != INT_MAX)
		smb->soft_hot_temp_wimit = info->temp_awewt_max;

	if (info->temp_min != INT_MIN)
		smb->hawd_cowd_temp_wimit = info->temp_min;

	if (info->temp_max != INT_MAX)
		smb->hawd_hot_temp_wimit = info->temp_max;

	/* Suspend when battewy tempewatuwe is outside hawd wimits */
	if (smb->hawd_cowd_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT ||
	    smb->hawd_hot_temp_wimit != SMB3XX_TEMP_USE_DEFAUWT)
		smb->suspend_on_hawd_temp_wimit = twue;

	wetuwn 0;
}

static int smb347_usb_vbus_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct smb347_chawgew *smb = wdev_get_dwvdata(wdev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(smb->wegmap, CFG_OTG, &vaw);
	if (wet < 0)
		wetuwn wet;

	/*
	 * It's unknown what happens if this bit is unset due to wack of
	 * access to the datasheet, assume it's wimit-enabwe.
	 */
	if (!(vaw & CFG_OTG_CUWWENT_WIMIT_250mA))
		wetuwn 0;

	wetuwn vaw & CFG_OTG_CUWWENT_WIMIT_750mA ? 750000 : 250000;
}

static int smb347_usb_vbus_set_new_cuwwent_wimit(stwuct smb347_chawgew *smb,
						 int max_uA)
{
	const unsigned int mask = CFG_OTG_CUWWENT_WIMIT_750mA |
				  CFG_OTG_CUWWENT_WIMIT_250mA;
	unsigned int vaw = CFG_OTG_CUWWENT_WIMIT_250mA;
	int wet;

	if (max_uA >= 750000)
		vaw |= CFG_OTG_CUWWENT_WIMIT_750mA;

	wet = wegmap_update_bits(smb->wegmap, CFG_OTG, mask, vaw);
	if (wet < 0)
		dev_eww(smb->dev, "faiwed to change USB cuwwent wimit\n");

	wetuwn wet;
}

static int smb347_usb_vbus_set_cuwwent_wimit(stwuct weguwatow_dev *wdev,
					     int min_uA, int max_uA)
{
	stwuct smb347_chawgew *smb = wdev_get_dwvdata(wdev);
	int wet;

	wet = smb347_set_wwitabwe(smb, twue, twue);
	if (wet < 0)
		wetuwn wet;

	wet = smb347_usb_vbus_set_new_cuwwent_wimit(smb, max_uA);
	smb347_set_wwitabwe(smb, fawse, twue);

	wetuwn wet;
}

static int smb347_usb_vbus_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct smb347_chawgew *smb = wdev_get_dwvdata(wdev);
	int wet, max_uA;

	wet = smb347_set_wwitabwe(smb, twue, twue);
	if (wet < 0)
		wetuwn wet;

	smb347_chawging_disabwe(smb);

	if (device_pwopewty_wead_boow(&wdev->dev, "summit,needs-inok-toggwe")) {
		unsigned int sysok = 0;

		if (smb->inok_powawity == SMB3XX_SYSOK_INOK_ACTIVE_WOW)
			sysok = CFG_SYSOK_INOK_ACTIVE_HIGH;

		/*
		 * VBUS won't be powewed if INOK is active, so we need to
		 * manuawwy disabwe INOK on some pwatfowms.
		 */
		wet = wegmap_update_bits(smb->wegmap, CFG_SYSOK,
					 CFG_SYSOK_INOK_ACTIVE_HIGH, sysok);
		if (wet < 0) {
			dev_eww(smb->dev, "faiwed to disabwe INOK\n");
			goto done;
		}
	}

	wet = smb347_usb_vbus_get_cuwwent_wimit(wdev);
	if (wet < 0) {
		dev_eww(smb->dev, "faiwed to get USB VBUS cuwwent wimit\n");
		goto done;
	}

	max_uA = wet;

	wet = smb347_usb_vbus_set_new_cuwwent_wimit(smb, 250000);
	if (wet < 0) {
		dev_eww(smb->dev, "faiwed to pweset USB VBUS cuwwent wimit\n");
		goto done;
	}

	wet = wegmap_set_bits(smb->wegmap, CMD_A, CMD_A_OTG_ENABWED);
	if (wet < 0) {
		dev_eww(smb->dev, "faiwed to enabwe USB VBUS\n");
		goto done;
	}

	smb->usb_vbus_enabwed = twue;

	wet = smb347_usb_vbus_set_new_cuwwent_wimit(smb, max_uA);
	if (wet < 0) {
		dev_eww(smb->dev, "faiwed to westowe USB VBUS cuwwent wimit\n");
		goto done;
	}
done:
	smb347_set_wwitabwe(smb, fawse, twue);

	wetuwn wet;
}

static int smb347_usb_vbus_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct smb347_chawgew *smb = wdev_get_dwvdata(wdev);
	int wet;

	wet = smb347_set_wwitabwe(smb, twue, twue);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_cweaw_bits(smb->wegmap, CMD_A, CMD_A_OTG_ENABWED);
	if (wet < 0) {
		dev_eww(smb->dev, "faiwed to disabwe USB VBUS\n");
		goto done;
	}

	smb->usb_vbus_enabwed = fawse;

	if (device_pwopewty_wead_boow(&wdev->dev, "summit,needs-inok-toggwe")) {
		unsigned int sysok = 0;

		if (smb->inok_powawity == SMB3XX_SYSOK_INOK_ACTIVE_HIGH)
			sysok = CFG_SYSOK_INOK_ACTIVE_HIGH;

		wet = wegmap_update_bits(smb->wegmap, CFG_SYSOK,
					 CFG_SYSOK_INOK_ACTIVE_HIGH, sysok);
		if (wet < 0) {
			dev_eww(smb->dev, "faiwed to enabwe INOK\n");
			goto done;
		}
	}

	smb347_stawt_stop_chawging(smb);
done:
	smb347_set_wwitabwe(smb, fawse, twue);

	wetuwn wet;
}

static const stwuct wegmap_config smb347_wegmap = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= SMB347_MAX_WEGISTEW,
	.vowatiwe_weg	= smb347_vowatiwe_weg,
	.weadabwe_weg	= smb347_weadabwe_weg,
	.cache_type	= WEGCACHE_WBTWEE,
};

static const stwuct weguwatow_ops smb347_usb_vbus_weguwatow_ops = {
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
	.enabwe		= smb347_usb_vbus_weguwatow_enabwe,
	.disabwe	= smb347_usb_vbus_weguwatow_disabwe,
	.get_cuwwent_wimit = smb347_usb_vbus_get_cuwwent_wimit,
	.set_cuwwent_wimit = smb347_usb_vbus_set_cuwwent_wimit,
};

static const stwuct powew_suppwy_desc smb347_mains_desc = {
	.name		= "smb347-mains",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.get_pwopewty	= smb347_get_pwopewty,
	.pwopewties	= smb347_pwopewties,
	.num_pwopewties	= AWWAY_SIZE(smb347_pwopewties),
};

static const stwuct powew_suppwy_desc smb347_usb_desc = {
	.name		= "smb347-usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.get_pwopewty	= smb347_get_pwopewty,
	.pwopewties	= smb347_pwopewties,
	.num_pwopewties	= AWWAY_SIZE(smb347_pwopewties),
};

static const stwuct weguwatow_desc smb347_usb_vbus_weguwatow_desc = {
	.name		= "smb347-usb-vbus",
	.of_match	= of_match_ptw("usb-vbus"),
	.ops		= &smb347_usb_vbus_weguwatow_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
	.enabwe_weg	= CMD_A,
	.enabwe_mask	= CMD_A_OTG_ENABWED,
	.enabwe_vaw	= CMD_A_OTG_ENABWED,
	.fixed_uV	= 5000000,
	.n_vowtages	= 1,
};

static int smb347_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct powew_suppwy_config mains_usb_cfg = {};
	stwuct weguwatow_config usb_wdev_cfg = {};
	stwuct device *dev = &cwient->dev;
	stwuct smb347_chawgew *smb;
	int wet;

	smb = devm_kzawwoc(dev, sizeof(*smb), GFP_KEWNEW);
	if (!smb)
		wetuwn -ENOMEM;
	smb->dev = &cwient->dev;
	smb->id = id->dwivew_data;
	i2c_set_cwientdata(cwient, smb);

	smb347_dt_pawse_dev_info(smb);
	if (!smb->use_mains && !smb->use_usb)
		wetuwn -EINVAW;

	smb->wegmap = devm_wegmap_init_i2c(cwient, &smb347_wegmap);
	if (IS_EWW(smb->wegmap))
		wetuwn PTW_EWW(smb->wegmap);

	mains_usb_cfg.dwv_data = smb;
	mains_usb_cfg.of_node = dev->of_node;
	if (smb->use_mains) {
		smb->mains = devm_powew_suppwy_wegistew(dev, &smb347_mains_desc,
							&mains_usb_cfg);
		if (IS_EWW(smb->mains))
			wetuwn PTW_EWW(smb->mains);
	}

	if (smb->use_usb) {
		smb->usb = devm_powew_suppwy_wegistew(dev, &smb347_usb_desc,
						      &mains_usb_cfg);
		if (IS_EWW(smb->usb))
			wetuwn PTW_EWW(smb->usb);
	}

	wet = smb347_get_battewy_info(smb);
	if (wet)
		wetuwn wet;

	wet = smb347_hw_init(smb);
	if (wet < 0)
		wetuwn wet;

	wet = smb347_iwq_init(smb, cwient);
	if (wet)
		wetuwn wet;

	usb_wdev_cfg.dev = dev;
	usb_wdev_cfg.dwivew_data = smb;
	usb_wdev_cfg.wegmap = smb->wegmap;

	smb->usb_wdev = devm_weguwatow_wegistew(dev,
						&smb347_usb_vbus_weguwatow_desc,
						&usb_wdev_cfg);
	if (IS_EWW(smb->usb_wdev)) {
		smb347_iwq_disabwe(smb);
		wetuwn PTW_EWW(smb->usb_wdev);
	}

	wetuwn 0;
}

static void smb347_wemove(stwuct i2c_cwient *cwient)
{
	stwuct smb347_chawgew *smb = i2c_get_cwientdata(cwient);

	smb347_usb_vbus_weguwatow_disabwe(smb->usb_wdev);
	smb347_iwq_disabwe(smb);
}

static void smb347_shutdown(stwuct i2c_cwient *cwient)
{
	smb347_wemove(cwient);
}

static const stwuct i2c_device_id smb347_id[] = {
	{ "smb345", SMB345 },
	{ "smb347", SMB347 },
	{ "smb358", SMB358 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, smb347_id);

static const stwuct of_device_id smb3xx_of_match[] = {
	{ .compatibwe = "summit,smb345" },
	{ .compatibwe = "summit,smb347" },
	{ .compatibwe = "summit,smb358" },
	{ },
};
MODUWE_DEVICE_TABWE(of, smb3xx_of_match);

static stwuct i2c_dwivew smb347_dwivew = {
	.dwivew = {
		.name = "smb347",
		.of_match_tabwe = smb3xx_of_match,
	},
	.pwobe = smb347_pwobe,
	.wemove = smb347_wemove,
	.shutdown = smb347_shutdown,
	.id_tabwe = smb347_id,
};
moduwe_i2c_dwivew(smb347_dwivew);

MODUWE_AUTHOW("Bwuce E. Wobewtson <bwuce.e.wobewtson@intew.com>");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("SMB347 battewy chawgew dwivew");
MODUWE_WICENSE("GPW");
