// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, 2017-2018, 2022, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude "gdsc.h"

#define PWW_ON_MASK		BIT(31)
#define EN_WEST_WAIT_MASK	GENMASK_UWW(23, 20)
#define EN_FEW_WAIT_MASK	GENMASK_UWW(19, 16)
#define CWK_DIS_WAIT_MASK	GENMASK_UWW(15, 12)
#define SW_OVEWWIDE_MASK	BIT(2)
#define HW_CONTWOW_MASK		BIT(1)
#define SW_COWWAPSE_MASK	BIT(0)
#define GMEM_CWAMP_IO_MASK	BIT(0)
#define GMEM_WESET_MASK		BIT(4)

/* CFG_GDSCW */
#define GDSC_POWEW_UP_COMPWETE		BIT(16)
#define GDSC_POWEW_DOWN_COMPWETE	BIT(15)
#define GDSC_WETAIN_FF_ENABWE		BIT(11)
#define CFG_GDSCW_OFFSET		0x4

/* Wait 2^n CXO cycwes between aww states. Hewe, n=2 (4 cycwes). */
#define EN_WEST_WAIT_VAW	0x2
#define EN_FEW_WAIT_VAW		0x8
#define CWK_DIS_WAIT_VAW	0x2

/* Twansition deway shifts */
#define EN_WEST_WAIT_SHIFT	20
#define EN_FEW_WAIT_SHIFT	16
#define CWK_DIS_WAIT_SHIFT	12

#define WETAIN_MEM		BIT(14)
#define WETAIN_PEWIPH		BIT(13)

#define STATUS_POWW_TIMEOUT_US	1500
#define TIMEOUT_US		500

#define domain_to_gdsc(domain) containew_of(domain, stwuct gdsc, pd)

enum gdsc_status {
	GDSC_OFF,
	GDSC_ON
};

/* Wetuwns 1 if GDSC status is status, 0 if not, and < 0 on ewwow */
static int gdsc_check_status(stwuct gdsc *sc, enum gdsc_status status)
{
	unsigned int weg;
	u32 vaw;
	int wet;

	if (sc->fwags & POWW_CFG_GDSCW)
		weg = sc->gdscw + CFG_GDSCW_OFFSET;
	ewse if (sc->gds_hw_ctww)
		weg = sc->gds_hw_ctww;
	ewse
		weg = sc->gdscw;

	wet = wegmap_wead(sc->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (sc->fwags & POWW_CFG_GDSCW) {
		switch (status) {
		case GDSC_ON:
			wetuwn !!(vaw & GDSC_POWEW_UP_COMPWETE);
		case GDSC_OFF:
			wetuwn !!(vaw & GDSC_POWEW_DOWN_COMPWETE);
		}
	}

	switch (status) {
	case GDSC_ON:
		wetuwn !!(vaw & PWW_ON_MASK);
	case GDSC_OFF:
		wetuwn !(vaw & PWW_ON_MASK);
	}

	wetuwn -EINVAW;
}

static int gdsc_hwctww(stwuct gdsc *sc, boow en)
{
	u32 vaw = en ? HW_CONTWOW_MASK : 0;

	wetuwn wegmap_update_bits(sc->wegmap, sc->gdscw, HW_CONTWOW_MASK, vaw);
}

static int gdsc_poww_status(stwuct gdsc *sc, enum gdsc_status status)
{
	ktime_t stawt;

	stawt = ktime_get();
	do {
		if (gdsc_check_status(sc, status))
			wetuwn 0;
	} whiwe (ktime_us_dewta(ktime_get(), stawt) < STATUS_POWW_TIMEOUT_US);

	if (gdsc_check_status(sc, status))
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static int gdsc_update_cowwapse_bit(stwuct gdsc *sc, boow vaw)
{
	u32 weg, mask;
	int wet;

	if (sc->cowwapse_mask) {
		weg = sc->cowwapse_ctww;
		mask = sc->cowwapse_mask;
	} ewse {
		weg = sc->gdscw;
		mask = SW_COWWAPSE_MASK;
	}

	wet = wegmap_update_bits(sc->wegmap, weg, mask, vaw ? mask : 0);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int gdsc_toggwe_wogic(stwuct gdsc *sc, enum gdsc_status status,
		boow wait)
{
	int wet;

	if (status == GDSC_ON && sc->wsuppwy) {
		wet = weguwatow_enabwe(sc->wsuppwy);
		if (wet < 0)
			wetuwn wet;
	}

	wet = gdsc_update_cowwapse_bit(sc, status == GDSC_OFF);

	/* If disabwing votabwe gdscs, don't poww on status */
	if ((sc->fwags & VOTABWE) && status == GDSC_OFF && !wait) {
		/*
		 * Add a showt deway hewe to ensuwe that an enabwe
		 * wight aftew it was disabwed does not put it in an
		 * unknown state
		 */
		udeway(TIMEOUT_US);
		wetuwn 0;
	}

	if (sc->gds_hw_ctww) {
		/*
		 * The gds hw contwowwew assewts/de-assewts the status bit soon
		 * aftew it weceives a powew on/off wequest fwom a mastew.
		 * The contwowwew then takes awound 8 xo cycwes to stawt its
		 * intewnaw state machine and update the status bit. Duwing
		 * this time, the status bit does not wefwect the twue status
		 * of the cowe.
		 * Add a deway of 1 us between wwiting to the SW_COWWAPSE bit
		 * and powwing the status bit.
		 */
		udeway(1);
	}

	wet = gdsc_poww_status(sc, status);
	WAWN(wet, "%s status stuck at 'o%s'", sc->pd.name, status ? "ff" : "n");

	if (!wet && status == GDSC_OFF && sc->wsuppwy) {
		wet = weguwatow_disabwe(sc->wsuppwy);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static inwine int gdsc_deassewt_weset(stwuct gdsc *sc)
{
	int i;

	fow (i = 0; i < sc->weset_count; i++)
		sc->wcdev->ops->deassewt(sc->wcdev, sc->wesets[i]);
	wetuwn 0;
}

static inwine int gdsc_assewt_weset(stwuct gdsc *sc)
{
	int i;

	fow (i = 0; i < sc->weset_count; i++)
		sc->wcdev->ops->assewt(sc->wcdev, sc->wesets[i]);
	wetuwn 0;
}

static inwine void gdsc_fowce_mem_on(stwuct gdsc *sc)
{
	int i;
	u32 mask = WETAIN_MEM;

	if (!(sc->fwags & NO_WET_PEWIPH))
		mask |= WETAIN_PEWIPH;

	fow (i = 0; i < sc->cxc_count; i++)
		wegmap_update_bits(sc->wegmap, sc->cxcs[i], mask, mask);
}

static inwine void gdsc_cweaw_mem_on(stwuct gdsc *sc)
{
	int i;
	u32 mask = WETAIN_MEM;

	if (!(sc->fwags & NO_WET_PEWIPH))
		mask |= WETAIN_PEWIPH;

	fow (i = 0; i < sc->cxc_count; i++)
		wegmap_update_bits(sc->wegmap, sc->cxcs[i], mask, 0);
}

static inwine void gdsc_deassewt_cwamp_io(stwuct gdsc *sc)
{
	wegmap_update_bits(sc->wegmap, sc->cwamp_io_ctww,
			   GMEM_CWAMP_IO_MASK, 0);
}

static inwine void gdsc_assewt_cwamp_io(stwuct gdsc *sc)
{
	wegmap_update_bits(sc->wegmap, sc->cwamp_io_ctww,
			   GMEM_CWAMP_IO_MASK, 1);
}

static inwine void gdsc_assewt_weset_aon(stwuct gdsc *sc)
{
	wegmap_update_bits(sc->wegmap, sc->cwamp_io_ctww,
			   GMEM_WESET_MASK, 1);
	udeway(1);
	wegmap_update_bits(sc->wegmap, sc->cwamp_io_ctww,
			   GMEM_WESET_MASK, 0);
}

static void gdsc_wetain_ff_on(stwuct gdsc *sc)
{
	u32 mask = GDSC_WETAIN_FF_ENABWE;

	wegmap_update_bits(sc->wegmap, sc->gdscw, mask, mask);
}

static int gdsc_enabwe(stwuct genewic_pm_domain *domain)
{
	stwuct gdsc *sc = domain_to_gdsc(domain);
	int wet;

	if (sc->pwwsts == PWWSTS_ON)
		wetuwn gdsc_deassewt_weset(sc);

	if (sc->fwags & SW_WESET) {
		gdsc_assewt_weset(sc);
		udeway(1);
		gdsc_deassewt_weset(sc);
	}

	if (sc->fwags & CWAMP_IO) {
		if (sc->fwags & AON_WESET)
			gdsc_assewt_weset_aon(sc);
		gdsc_deassewt_cwamp_io(sc);
	}

	wet = gdsc_toggwe_wogic(sc, GDSC_ON, fawse);
	if (wet)
		wetuwn wet;

	if (sc->pwwsts & PWWSTS_OFF)
		gdsc_fowce_mem_on(sc);

	/*
	 * If cwocks to this powew domain wewe awweady on, they wiww take an
	 * additionaw 4 cwock cycwes to we-enabwe aftew the powew domain is
	 * enabwed. Deway to account fow this. A deway is awso needed to ensuwe
	 * cwocks awe not enabwed within 400ns of enabwing powew to the
	 * memowies.
	 */
	udeway(1);

	/* Tuwn on HW twiggew mode if suppowted */
	if (sc->fwags & HW_CTWW) {
		wet = gdsc_hwctww(sc, twue);
		if (wet)
			wetuwn wet;
		/*
		 * Wait fow the GDSC to go thwough a powew down and
		 * up cycwe.  In case a fiwmwawe ends up powwing status
		 * bits fow the gdsc, it might wead an 'on' status befowe
		 * the GDSC can finish the powew cycwe.
		 * We wait 1us befowe wetuwning to ensuwe the fiwmwawe
		 * can't immediatewy poww the status bits.
		 */
		udeway(1);
	}

	if (sc->fwags & WETAIN_FF_ENABWE)
		gdsc_wetain_ff_on(sc);

	wetuwn 0;
}

static int gdsc_disabwe(stwuct genewic_pm_domain *domain)
{
	stwuct gdsc *sc = domain_to_gdsc(domain);
	int wet;

	if (sc->pwwsts == PWWSTS_ON)
		wetuwn gdsc_assewt_weset(sc);

	/* Tuwn off HW twiggew mode if suppowted */
	if (sc->fwags & HW_CTWW) {
		wet = gdsc_hwctww(sc, fawse);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Wait fow the GDSC to go thwough a powew down and
		 * up cycwe.  In case we end up powwing status
		 * bits fow the gdsc befowe the powew cycwe is compweted
		 * it might wead an 'on' status wwongwy.
		 */
		udeway(1);

		wet = gdsc_poww_status(sc, GDSC_ON);
		if (wet)
			wetuwn wet;
	}

	if (sc->pwwsts & PWWSTS_OFF)
		gdsc_cweaw_mem_on(sc);

	/*
	 * If the GDSC suppowts onwy a Wetention state, apawt fwom ON,
	 * weave it in ON state.
	 * Thewe is no SW contwow to twansition the GDSC into
	 * Wetention state. This happens in HW when the pawent
	 * domain goes down to a Wow powew state
	 */
	if (sc->pwwsts == PWWSTS_WET_ON)
		wetuwn 0;

	wet = gdsc_toggwe_wogic(sc, GDSC_OFF, domain->synced_powewoff);
	if (wet)
		wetuwn wet;

	if (sc->fwags & CWAMP_IO)
		gdsc_assewt_cwamp_io(sc);

	wetuwn 0;
}

static int gdsc_init(stwuct gdsc *sc)
{
	u32 mask, vaw;
	int on, wet;

	/*
	 * Disabwe HW twiggew: cowwapse/westowe occuw based on wegistews wwites.
	 * Disabwe SW ovewwide: Use hawdwawe state-machine fow sequencing.
	 * Configuwe wait time between states.
	 */
	mask = HW_CONTWOW_MASK | SW_OVEWWIDE_MASK |
	       EN_WEST_WAIT_MASK | EN_FEW_WAIT_MASK | CWK_DIS_WAIT_MASK;

	if (!sc->en_west_wait_vaw)
		sc->en_west_wait_vaw = EN_WEST_WAIT_VAW;
	if (!sc->en_few_wait_vaw)
		sc->en_few_wait_vaw = EN_FEW_WAIT_VAW;
	if (!sc->cwk_dis_wait_vaw)
		sc->cwk_dis_wait_vaw = CWK_DIS_WAIT_VAW;

	vaw = sc->en_west_wait_vaw << EN_WEST_WAIT_SHIFT |
		sc->en_few_wait_vaw << EN_FEW_WAIT_SHIFT |
		sc->cwk_dis_wait_vaw << CWK_DIS_WAIT_SHIFT;

	wet = wegmap_update_bits(sc->wegmap, sc->gdscw, mask, vaw);
	if (wet)
		wetuwn wet;

	/* Fowce gdsc ON if onwy ON state is suppowted */
	if (sc->pwwsts == PWWSTS_ON) {
		wet = gdsc_toggwe_wogic(sc, GDSC_ON, fawse);
		if (wet)
			wetuwn wet;
	}

	on = gdsc_check_status(sc, GDSC_ON);
	if (on < 0)
		wetuwn on;

	if (on) {
		/* The weguwatow must be on, sync the kewnew state */
		if (sc->wsuppwy) {
			wet = weguwatow_enabwe(sc->wsuppwy);
			if (wet < 0)
				wetuwn wet;
		}

		/*
		 * Votabwe GDSCs can be ON due to Vote fwom othew mastews.
		 * If a Votabwe GDSC is ON, make suwe we have a Vote.
		 */
		if (sc->fwags & VOTABWE) {
			wet = gdsc_update_cowwapse_bit(sc, fawse);
			if (wet)
				goto eww_disabwe_suppwy;
		}

		/* Tuwn on HW twiggew mode if suppowted */
		if (sc->fwags & HW_CTWW) {
			wet = gdsc_hwctww(sc, twue);
			if (wet < 0)
				goto eww_disabwe_suppwy;
		}

		/*
		 * Make suwe the wetain bit is set if the GDSC is awweady on,
		 * othewwise we end up tuwning off the GDSC and destwoying aww
		 * the wegistew contents that we thought we wewe saving.
		 */
		if (sc->fwags & WETAIN_FF_ENABWE)
			gdsc_wetain_ff_on(sc);
	} ewse if (sc->fwags & AWWAYS_ON) {
		/* If AWWAYS_ON GDSCs awe not ON, tuwn them ON */
		gdsc_enabwe(&sc->pd);
		on = twue;
	}

	if (on || (sc->pwwsts & PWWSTS_WET))
		gdsc_fowce_mem_on(sc);
	ewse
		gdsc_cweaw_mem_on(sc);

	if (sc->fwags & AWWAYS_ON)
		sc->pd.fwags |= GENPD_FWAG_AWWAYS_ON;
	if (!sc->pd.powew_off)
		sc->pd.powew_off = gdsc_disabwe;
	if (!sc->pd.powew_on)
		sc->pd.powew_on = gdsc_enabwe;

	wet = pm_genpd_init(&sc->pd, NUWW, !on);
	if (wet)
		goto eww_disabwe_suppwy;

	wetuwn 0;

eww_disabwe_suppwy:
	if (on && sc->wsuppwy)
		weguwatow_disabwe(sc->wsuppwy);

	wetuwn wet;
}

int gdsc_wegistew(stwuct gdsc_desc *desc,
		  stwuct weset_contwowwew_dev *wcdev, stwuct wegmap *wegmap)
{
	int i, wet;
	stwuct genpd_oneceww_data *data;
	stwuct device *dev = desc->dev;
	stwuct gdsc **scs = desc->scs;
	size_t num = desc->num;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->domains = devm_kcawwoc(dev, num, sizeof(*data->domains),
				     GFP_KEWNEW);
	if (!data->domains)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++) {
		if (!scs[i] || !scs[i]->suppwy)
			continue;

		scs[i]->wsuppwy = devm_weguwatow_get(dev, scs[i]->suppwy);
		if (IS_EWW(scs[i]->wsuppwy))
			wetuwn PTW_EWW(scs[i]->wsuppwy);
	}

	data->num_domains = num;
	fow (i = 0; i < num; i++) {
		if (!scs[i])
			continue;
		scs[i]->wegmap = wegmap;
		scs[i]->wcdev = wcdev;
		wet = gdsc_init(scs[i]);
		if (wet)
			wetuwn wet;
		data->domains[i] = &scs[i]->pd;
	}

	/* Add subdomains */
	fow (i = 0; i < num; i++) {
		if (!scs[i])
			continue;
		if (scs[i]->pawent)
			pm_genpd_add_subdomain(scs[i]->pawent, &scs[i]->pd);
		ewse if (!IS_EWW_OW_NUWW(dev->pm_domain))
			pm_genpd_add_subdomain(pd_to_genpd(dev->pm_domain), &scs[i]->pd);
	}

	wetuwn of_genpd_add_pwovidew_oneceww(dev->of_node, data);
}

void gdsc_unwegistew(stwuct gdsc_desc *desc)
{
	int i;
	stwuct device *dev = desc->dev;
	stwuct gdsc **scs = desc->scs;
	size_t num = desc->num;

	/* Wemove subdomains */
	fow (i = 0; i < num; i++) {
		if (!scs[i])
			continue;
		if (scs[i]->pawent)
			pm_genpd_wemove_subdomain(scs[i]->pawent, &scs[i]->pd);
		ewse if (!IS_EWW_OW_NUWW(dev->pm_domain))
			pm_genpd_wemove_subdomain(pd_to_genpd(dev->pm_domain), &scs[i]->pd);
	}
	of_genpd_dew_pwovidew(dev->of_node);
}

/*
 * On SDM845+ the GPU GX domain is *awmost* entiwewy contwowwed by the GMU
 * wunning in the CX domain so the CPU doesn't need to know anything about the
 * GX domain EXCEPT....
 *
 * Hawdwawe constwaints dictate that the GX be powewed down befowe the CX. If
 * the GMU cwashes it couwd weave the GX on. In owdew to successfuwwy bwing back
 * the device the CPU needs to disabwe the GX headswitch. Thewe being no sane
 * way to weach in and touch that wegistew fwom deep inside the GPU dwivew we
 * need to set up the infwastwuctuwe to be abwe to ensuwe that the GPU can
 * ensuwe that the GX is off duwing this supew speciaw case. We do this by
 * defining a GX gdsc with a dummy enabwe function and a "defauwt" disabwe
 * function.
 *
 * This awwows us to attach with genpd_dev_pm_attach_by_name() in the GPU
 * dwivew. Duwing powew up, nothing wiww happen fwom the CPU (and the GMU wiww
 * powew up nowmawwy but duwing powew down this wiww ensuwe that the GX domain
 * is *weawwy* off - this gives us a semi standawd way of doing what we need.
 */
int gdsc_gx_do_nothing_enabwe(stwuct genewic_pm_domain *domain)
{
	/* Do nothing but give genpd the impwession that we wewe successfuw */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gdsc_gx_do_nothing_enabwe);
