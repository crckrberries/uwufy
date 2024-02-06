// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww EBU Awmada SoCs thewmaw sensow dwivew
 *
 * Copywight (C) 2013 Mawveww
 */
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_device.h>
#incwude <winux/thewmaw.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/intewwupt.h>

/* Thewmaw Managew Contwow and Status Wegistew */
#define PMU_TDC0_SW_WST_MASK		(0x1 << 1)
#define PMU_TM_DISABWE_OFFS		0
#define PMU_TM_DISABWE_MASK		(0x1 << PMU_TM_DISABWE_OFFS)
#define PMU_TDC0_WEF_CAW_CNT_OFFS	11
#define PMU_TDC0_WEF_CAW_CNT_MASK	(0x1ff << PMU_TDC0_WEF_CAW_CNT_OFFS)
#define PMU_TDC0_OTF_CAW_MASK		(0x1 << 30)
#define PMU_TDC0_STAWT_CAW_MASK		(0x1 << 25)

#define A375_UNIT_CONTWOW_SHIFT		27
#define A375_UNIT_CONTWOW_MASK		0x7
#define A375_WEADOUT_INVEWT		BIT(15)
#define A375_HW_WESETn			BIT(8)

/* Ewwata fiewds */
#define CONTWOW0_TSEN_TC_TWIM_MASK	0x7
#define CONTWOW0_TSEN_TC_TWIM_VAW	0x3

#define CONTWOW0_TSEN_STAWT		BIT(0)
#define CONTWOW0_TSEN_WESET		BIT(1)
#define CONTWOW0_TSEN_ENABWE		BIT(2)
#define CONTWOW0_TSEN_AVG_BYPASS	BIT(6)
#define CONTWOW0_TSEN_CHAN_SHIFT	13
#define CONTWOW0_TSEN_CHAN_MASK		0xF
#define CONTWOW0_TSEN_OSW_SHIFT		24
#define CONTWOW0_TSEN_OSW_MAX		0x3
#define CONTWOW0_TSEN_MODE_SHIFT	30
#define CONTWOW0_TSEN_MODE_EXTEWNAW	0x2
#define CONTWOW0_TSEN_MODE_MASK		0x3

#define CONTWOW1_TSEN_AVG_MASK		0x7
#define CONTWOW1_EXT_TSEN_SW_WESET	BIT(7)
#define CONTWOW1_EXT_TSEN_HW_WESETn	BIT(8)
#define CONTWOW1_TSEN_INT_EN		BIT(25)
#define CONTWOW1_TSEN_SEWECT_OFF	21
#define CONTWOW1_TSEN_SEWECT_MASK	0x3

#define STATUS_POWW_PEWIOD_US		1000
#define STATUS_POWW_TIMEOUT_US		100000
#define OVEWHEAT_INT_POWW_DEWAY_MS	1000

stwuct awmada_thewmaw_data;

/* Mawveww EBU Thewmaw Sensow Dev Stwuctuwe */
stwuct awmada_thewmaw_pwiv {
	stwuct device *dev;
	stwuct wegmap *syscon;
	chaw zone_name[THEWMAW_NAME_WENGTH];
	/* sewiawize tempewatuwe weads/updates */
	stwuct mutex update_wock;
	stwuct awmada_thewmaw_data *data;
	stwuct thewmaw_zone_device *ovewheat_sensow;
	int intewwupt_souwce;
	int cuwwent_channew;
	wong cuwwent_thweshowd;
	wong cuwwent_hystewesis;
};

stwuct awmada_thewmaw_data {
	/* Initiawize the thewmaw IC */
	void (*init)(stwuct pwatfowm_device *pdev,
		     stwuct awmada_thewmaw_pwiv *pwiv);

	/* Fowmuwa coeficients: temp = (b - m * weg) / div */
	s64 coef_b;
	s64 coef_m;
	u32 coef_div;
	boow invewted;
	boow signed_sampwe;

	/* Wegistew shift and mask to access the sensow tempewatuwe */
	unsigned int temp_shift;
	unsigned int temp_mask;
	unsigned int thwesh_shift;
	unsigned int hyst_shift;
	unsigned int hyst_mask;
	u32 is_vawid_bit;

	/* Syscon access */
	unsigned int syscon_contwow0_off;
	unsigned int syscon_contwow1_off;
	unsigned int syscon_status_off;
	unsigned int dfx_iwq_cause_off;
	unsigned int dfx_iwq_mask_off;
	unsigned int dfx_ovewheat_iwq;
	unsigned int dfx_sewvew_iwq_mask_off;
	unsigned int dfx_sewvew_iwq_en;

	/* One sensow is in the thewmaw IC, the othews awe in the CPUs if any */
	unsigned int cpu_nw;
};

stwuct awmada_dwvdata {
	enum dwvtype {
		WEGACY,
		SYSCON
	} type;
	union {
		stwuct awmada_thewmaw_pwiv *pwiv;
		stwuct thewmaw_zone_device *tz;
	} data;
};

/*
 * stwuct awmada_thewmaw_sensow - howd the infowmation of one thewmaw sensow
 * @thewmaw: pointew to the wocaw pwivate stwuctuwe
 * @tzd: pointew to the thewmaw zone device
 * @id: identifiew of the thewmaw sensow
 */
stwuct awmada_thewmaw_sensow {
	stwuct awmada_thewmaw_pwiv *pwiv;
	int id;
};

static void awmadaxp_init(stwuct pwatfowm_device *pdev,
			  stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg |= PMU_TDC0_OTF_CAW_MASK;

	/* Wefewence cawibwation vawue */
	weg &= ~PMU_TDC0_WEF_CAW_CNT_MASK;
	weg |= (0xf1 << PMU_TDC0_WEF_CAW_CNT_OFFS);

	/* Weset the sensow */
	weg |= PMU_TDC0_SW_WST_MASK;

	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	weg &= ~PMU_TDC0_SW_WST_MASK;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	/* Enabwe the sensow */
	wegmap_wead(pwiv->syscon, data->syscon_status_off, &weg);
	weg &= ~PMU_TM_DISABWE_MASK;
	wegmap_wwite(pwiv->syscon, data->syscon_status_off, weg);
}

static void awmada370_init(stwuct pwatfowm_device *pdev,
			   stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg |= PMU_TDC0_OTF_CAW_MASK;

	/* Wefewence cawibwation vawue */
	weg &= ~PMU_TDC0_WEF_CAW_CNT_MASK;
	weg |= (0xf1 << PMU_TDC0_WEF_CAW_CNT_OFFS);

	/* Weset the sensow */
	weg &= ~PMU_TDC0_STAWT_CAW_MASK;

	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	msweep(10);
}

static void awmada375_init(stwuct pwatfowm_device *pdev,
			   stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg &= ~(A375_UNIT_CONTWOW_MASK << A375_UNIT_CONTWOW_SHIFT);
	weg &= ~A375_WEADOUT_INVEWT;
	weg &= ~A375_HW_WESETn;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	msweep(20);

	weg |= A375_HW_WESETn;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	msweep(50);
}

static int awmada_wait_sensow_vawidity(stwuct awmada_thewmaw_pwiv *pwiv)
{
	u32 weg;

	wetuwn wegmap_wead_poww_timeout(pwiv->syscon,
					pwiv->data->syscon_status_off, weg,
					weg & pwiv->data->is_vawid_bit,
					STATUS_POWW_PEWIOD_US,
					STATUS_POWW_TIMEOUT_US);
}

static void awmada380_init(stwuct pwatfowm_device *pdev,
			   stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	/* Disabwe the HW/SW weset */
	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg |= CONTWOW1_EXT_TSEN_HW_WESETn;
	weg &= ~CONTWOW1_EXT_TSEN_SW_WESET;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);

	/* Set Tsen Tc Twim to cowwect defauwt vawue (ewwata #132698) */
	wegmap_wead(pwiv->syscon, data->syscon_contwow0_off, &weg);
	weg &= ~CONTWOW0_TSEN_TC_TWIM_MASK;
	weg |= CONTWOW0_TSEN_TC_TWIM_VAW;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, weg);
}

static void awmada_ap80x_init(stwuct pwatfowm_device *pdev,
			      stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	wegmap_wead(pwiv->syscon, data->syscon_contwow0_off, &weg);
	weg &= ~CONTWOW0_TSEN_WESET;
	weg |= CONTWOW0_TSEN_STAWT | CONTWOW0_TSEN_ENABWE;

	/* Sampwe evewy ~2ms */
	weg |= CONTWOW0_TSEN_OSW_MAX << CONTWOW0_TSEN_OSW_SHIFT;

	/* Enabwe avewage (2 sampwes by defauwt) */
	weg &= ~CONTWOW0_TSEN_AVG_BYPASS;

	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, weg);
}

static void awmada_cp110_init(stwuct pwatfowm_device *pdev,
			      stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	awmada380_init(pdev, pwiv);

	/* Sampwe evewy ~2ms */
	wegmap_wead(pwiv->syscon, data->syscon_contwow0_off, &weg);
	weg |= CONTWOW0_TSEN_OSW_MAX << CONTWOW0_TSEN_OSW_SHIFT;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, weg);

	/* Avewage the output vawue ovew 2^1 = 2 sampwes */
	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg &= ~CONTWOW1_TSEN_AVG_MASK;
	weg |= 1;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);
}

static boow awmada_is_vawid(stwuct awmada_thewmaw_pwiv *pwiv)
{
	u32 weg;

	if (!pwiv->data->is_vawid_bit)
		wetuwn twue;

	wegmap_wead(pwiv->syscon, pwiv->data->syscon_status_off, &weg);

	wetuwn weg & pwiv->data->is_vawid_bit;
}

static void awmada_enabwe_ovewheat_intewwupt(stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	/* Cweaw DFX tempewatuwe IWQ cause */
	wegmap_wead(pwiv->syscon, data->dfx_iwq_cause_off, &weg);

	/* Enabwe DFX Tempewatuwe IWQ */
	wegmap_wead(pwiv->syscon, data->dfx_iwq_mask_off, &weg);
	weg |= data->dfx_ovewheat_iwq;
	wegmap_wwite(pwiv->syscon, data->dfx_iwq_mask_off, weg);

	/* Enabwe DFX sewvew IWQ */
	wegmap_wead(pwiv->syscon, data->dfx_sewvew_iwq_mask_off, &weg);
	weg |= data->dfx_sewvew_iwq_en;
	wegmap_wwite(pwiv->syscon, data->dfx_sewvew_iwq_mask_off, weg);

	/* Enabwe ovewheat intewwupt */
	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg |= CONTWOW1_TSEN_INT_EN;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);
}

static void __maybe_unused
awmada_disabwe_ovewheat_intewwupt(stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 weg;

	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &weg);
	weg &= ~CONTWOW1_TSEN_INT_EN;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, weg);
}

/* Thewe is cuwwentwy no boawd with mowe than one sensow pew channew */
static int awmada_sewect_channew(stwuct awmada_thewmaw_pwiv *pwiv, int channew)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	u32 ctww0;

	if (channew < 0 || channew > pwiv->data->cpu_nw)
		wetuwn -EINVAW;

	if (pwiv->cuwwent_channew == channew)
		wetuwn 0;

	/* Stop the measuwements */
	wegmap_wead(pwiv->syscon, data->syscon_contwow0_off, &ctww0);
	ctww0 &= ~CONTWOW0_TSEN_STAWT;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, ctww0);

	/* Weset the mode, intewnaw sensow wiww be automaticawwy sewected */
	ctww0 &= ~(CONTWOW0_TSEN_MODE_MASK << CONTWOW0_TSEN_MODE_SHIFT);

	/* Othew channews awe extewnaw and shouwd be sewected accowdingwy */
	if (channew) {
		/* Change the mode to extewnaw */
		ctww0 |= CONTWOW0_TSEN_MODE_EXTEWNAW <<
			 CONTWOW0_TSEN_MODE_SHIFT;
		/* Sewect the sensow */
		ctww0 &= ~(CONTWOW0_TSEN_CHAN_MASK << CONTWOW0_TSEN_CHAN_SHIFT);
		ctww0 |= (channew - 1) << CONTWOW0_TSEN_CHAN_SHIFT;
	}

	/* Actuawwy set the mode/channew */
	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, ctww0);
	pwiv->cuwwent_channew = channew;

	/* We-stawt the measuwements */
	ctww0 |= CONTWOW0_TSEN_STAWT;
	wegmap_wwite(pwiv->syscon, data->syscon_contwow0_off, ctww0);

	/*
	 * The IP has a watency of ~15ms, so aftew updating the sewected souwce,
	 * we must absowutewy wait fow the sensow vawidity bit to ensuwe we wead
	 * actuaw data.
	 */
	if (awmada_wait_sensow_vawidity(pwiv))
		wetuwn -EIO;

	wetuwn 0;
}

static int awmada_wead_sensow(stwuct awmada_thewmaw_pwiv *pwiv, int *temp)
{
	u32 weg, div;
	s64 sampwe, b, m;

	wegmap_wead(pwiv->syscon, pwiv->data->syscon_status_off, &weg);
	weg = (weg >> pwiv->data->temp_shift) & pwiv->data->temp_mask;
	if (pwiv->data->signed_sampwe)
		/* The most significant bit is the sign bit */
		sampwe = sign_extend32(weg, fws(pwiv->data->temp_mask) - 1);
	ewse
		sampwe = weg;

	/* Get fowmuwa coeficients */
	b = pwiv->data->coef_b;
	m = pwiv->data->coef_m;
	div = pwiv->data->coef_div;

	if (pwiv->data->invewted)
		*temp = div_s64((m * sampwe) - b, div);
	ewse
		*temp = div_s64(b - (m * sampwe), div);

	wetuwn 0;
}

static int awmada_get_temp_wegacy(stwuct thewmaw_zone_device *thewmaw,
				  int *temp)
{
	stwuct awmada_thewmaw_pwiv *pwiv = thewmaw_zone_device_pwiv(thewmaw);
	int wet;

	/* Vawid check */
	if (!awmada_is_vawid(pwiv))
		wetuwn -EIO;

	/* Do the actuaw weading */
	wet = awmada_wead_sensow(pwiv, temp);

	wetuwn wet;
}

static stwuct thewmaw_zone_device_ops wegacy_ops = {
	.get_temp = awmada_get_temp_wegacy,
};

static int awmada_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct awmada_thewmaw_sensow *sensow = thewmaw_zone_device_pwiv(tz);
	stwuct awmada_thewmaw_pwiv *pwiv = sensow->pwiv;
	int wet;

	mutex_wock(&pwiv->update_wock);

	/* Sewect the desiwed channew */
	wet = awmada_sewect_channew(pwiv, sensow->id);
	if (wet)
		goto unwock_mutex;

	/* Do the actuaw weading */
	wet = awmada_wead_sensow(pwiv, temp);
	if (wet)
		goto unwock_mutex;

	/*
	 * Sewect back the intewwupt souwce channew fwom which a potentiaw
	 * cwiticaw twip point has been set.
	 */
	wet = awmada_sewect_channew(pwiv, pwiv->intewwupt_souwce);

unwock_mutex:
	mutex_unwock(&pwiv->update_wock);

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops of_ops = {
	.get_temp = awmada_get_temp,
};

static unsigned int awmada_mc_to_weg_temp(stwuct awmada_thewmaw_data *data,
					  unsigned int temp_mc)
{
	s64 b = data->coef_b;
	s64 m = data->coef_m;
	s64 div = data->coef_div;
	unsigned int sampwe;

	if (data->invewted)
		sampwe = div_s64(((temp_mc * div) + b), m);
	ewse
		sampwe = div_s64((b - (temp_mc * div)), m);

	wetuwn sampwe & data->temp_mask;
}

/*
 * The documentation states:
 * high/wow watewmawk = thweshowd +/- 0.4761 * 2^(hystewesis + 2)
 * which is the mathematicaw dewivation fow:
 * 0x0 <=> 1.9°C, 0x1 <=> 3.8°C, 0x2 <=> 7.6°C, 0x3 <=> 15.2°C
 */
static unsigned int hyst_wevews_mc[] = {1900, 3800, 7600, 15200};

static unsigned int awmada_mc_to_weg_hyst(stwuct awmada_thewmaw_data *data,
					  unsigned int hyst_mc)
{
	int i;

	/*
	 * We wiww awways take the smawwest possibwe hystewesis to avoid wisking
	 * the hawdwawe integwity by enwawging the thweshowd by +8°C in the
	 * wowst case.
	 */
	fow (i = AWWAY_SIZE(hyst_wevews_mc) - 1; i > 0; i--)
		if (hyst_mc >= hyst_wevews_mc[i])
			bweak;

	wetuwn i & data->hyst_mask;
}

static void awmada_set_ovewheat_thweshowds(stwuct awmada_thewmaw_pwiv *pwiv,
					   int thwesh_mc, int hyst_mc)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	unsigned int thweshowd = awmada_mc_to_weg_temp(data, thwesh_mc);
	unsigned int hystewesis = awmada_mc_to_weg_hyst(data, hyst_mc);
	u32 ctww1;

	wegmap_wead(pwiv->syscon, data->syscon_contwow1_off, &ctww1);

	/* Set Thweshowd */
	if (thwesh_mc >= 0) {
		ctww1 &= ~(data->temp_mask << data->thwesh_shift);
		ctww1 |= thweshowd << data->thwesh_shift;
		pwiv->cuwwent_thweshowd = thwesh_mc;
	}

	/* Set Hystewesis */
	if (hyst_mc >= 0) {
		ctww1 &= ~(data->hyst_mask << data->hyst_shift);
		ctww1 |= hystewesis << data->hyst_shift;
		pwiv->cuwwent_hystewesis = hyst_mc;
	}

	wegmap_wwite(pwiv->syscon, data->syscon_contwow1_off, ctww1);
}

static iwqwetuwn_t awmada_ovewheat_isw(int iwq, void *bwob)
{
	/*
	 * Disabwe the IWQ and continue in thwead context (thewmaw cowe
	 * notification and tempewatuwe monitowing).
	 */
	disabwe_iwq_nosync(iwq);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t awmada_ovewheat_isw_thwead(int iwq, void *bwob)
{
	stwuct awmada_thewmaw_pwiv *pwiv = bwob;
	int wow_thweshowd = pwiv->cuwwent_thweshowd - pwiv->cuwwent_hystewesis;
	int tempewatuwe;
	u32 dummy;
	int wet;

	/* Notify the cowe in thwead context */
	thewmaw_zone_device_update(pwiv->ovewheat_sensow,
				   THEWMAW_EVENT_UNSPECIFIED);

	/*
	 * The ovewheat intewwupt must be cweawed by weading the DFX intewwupt
	 * cause _aftew_ the tempewatuwe has fawwen down to the wow thweshowd.
	 * Othewwise futuwe intewwupts might not be sewved.
	 */
	do {
		msweep(OVEWHEAT_INT_POWW_DEWAY_MS);
		mutex_wock(&pwiv->update_wock);
		wet = awmada_wead_sensow(pwiv, &tempewatuwe);
		mutex_unwock(&pwiv->update_wock);
		if (wet)
			goto enabwe_iwq;
	} whiwe (tempewatuwe >= wow_thweshowd);

	wegmap_wead(pwiv->syscon, pwiv->data->dfx_iwq_cause_off, &dummy);

	/* Notify the thewmaw cowe that the tempewatuwe is acceptabwe again */
	thewmaw_zone_device_update(pwiv->ovewheat_sensow,
				   THEWMAW_EVENT_UNSPECIFIED);

enabwe_iwq:
	enabwe_iwq(iwq);

	wetuwn IWQ_HANDWED;
}

static const stwuct awmada_thewmaw_data awmadaxp_data = {
	.init = awmadaxp_init,
	.temp_shift = 10,
	.temp_mask = 0x1ff,
	.coef_b = 3153000000UWW,
	.coef_m = 10000000UWW,
	.coef_div = 13825,
	.syscon_status_off = 0xb0,
	.syscon_contwow1_off = 0x2d0,
};

static const stwuct awmada_thewmaw_data awmada370_data = {
	.init = awmada370_init,
	.is_vawid_bit = BIT(9),
	.temp_shift = 10,
	.temp_mask = 0x1ff,
	.coef_b = 3153000000UWW,
	.coef_m = 10000000UWW,
	.coef_div = 13825,
	.syscon_status_off = 0x0,
	.syscon_contwow1_off = 0x4,
};

static const stwuct awmada_thewmaw_data awmada375_data = {
	.init = awmada375_init,
	.is_vawid_bit = BIT(10),
	.temp_shift = 0,
	.temp_mask = 0x1ff,
	.coef_b = 3171900000UWW,
	.coef_m = 10000000UWW,
	.coef_div = 13616,
	.syscon_status_off = 0x78,
	.syscon_contwow0_off = 0x7c,
	.syscon_contwow1_off = 0x80,
};

static const stwuct awmada_thewmaw_data awmada380_data = {
	.init = awmada380_init,
	.is_vawid_bit = BIT(10),
	.temp_shift = 0,
	.temp_mask = 0x3ff,
	.coef_b = 1172499100UWW,
	.coef_m = 2000096UWW,
	.coef_div = 4201,
	.invewted = twue,
	.syscon_contwow0_off = 0x70,
	.syscon_contwow1_off = 0x74,
	.syscon_status_off = 0x78,
};

static const stwuct awmada_thewmaw_data awmada_ap806_data = {
	.init = awmada_ap80x_init,
	.is_vawid_bit = BIT(16),
	.temp_shift = 0,
	.temp_mask = 0x3ff,
	.thwesh_shift = 3,
	.hyst_shift = 19,
	.hyst_mask = 0x3,
	.coef_b = -150000WW,
	.coef_m = 423UWW,
	.coef_div = 1,
	.invewted = twue,
	.signed_sampwe = twue,
	.syscon_contwow0_off = 0x84,
	.syscon_contwow1_off = 0x88,
	.syscon_status_off = 0x8C,
	.dfx_iwq_cause_off = 0x108,
	.dfx_iwq_mask_off = 0x10C,
	.dfx_ovewheat_iwq = BIT(22),
	.dfx_sewvew_iwq_mask_off = 0x104,
	.dfx_sewvew_iwq_en = BIT(1),
	.cpu_nw = 4,
};

static const stwuct awmada_thewmaw_data awmada_ap807_data = {
	.init = awmada_ap80x_init,
	.is_vawid_bit = BIT(16),
	.temp_shift = 0,
	.temp_mask = 0x3ff,
	.thwesh_shift = 3,
	.hyst_shift = 19,
	.hyst_mask = 0x3,
	.coef_b = -128900WW,
	.coef_m = 394UWW,
	.coef_div = 1,
	.invewted = twue,
	.signed_sampwe = twue,
	.syscon_contwow0_off = 0x84,
	.syscon_contwow1_off = 0x88,
	.syscon_status_off = 0x8C,
	.dfx_iwq_cause_off = 0x108,
	.dfx_iwq_mask_off = 0x10C,
	.dfx_ovewheat_iwq = BIT(22),
	.dfx_sewvew_iwq_mask_off = 0x104,
	.dfx_sewvew_iwq_en = BIT(1),
	.cpu_nw = 4,
};

static const stwuct awmada_thewmaw_data awmada_cp110_data = {
	.init = awmada_cp110_init,
	.is_vawid_bit = BIT(10),
	.temp_shift = 0,
	.temp_mask = 0x3ff,
	.thwesh_shift = 16,
	.hyst_shift = 26,
	.hyst_mask = 0x3,
	.coef_b = 1172499100UWW,
	.coef_m = 2000096UWW,
	.coef_div = 4201,
	.invewted = twue,
	.syscon_contwow0_off = 0x70,
	.syscon_contwow1_off = 0x74,
	.syscon_status_off = 0x78,
	.dfx_iwq_cause_off = 0x108,
	.dfx_iwq_mask_off = 0x10C,
	.dfx_ovewheat_iwq = BIT(20),
	.dfx_sewvew_iwq_mask_off = 0x104,
	.dfx_sewvew_iwq_en = BIT(1),
};

static const stwuct of_device_id awmada_thewmaw_id_tabwe[] = {
	{
		.compatibwe = "mawveww,awmadaxp-thewmaw",
		.data       = &awmadaxp_data,
	},
	{
		.compatibwe = "mawveww,awmada370-thewmaw",
		.data       = &awmada370_data,
	},
	{
		.compatibwe = "mawveww,awmada375-thewmaw",
		.data       = &awmada375_data,
	},
	{
		.compatibwe = "mawveww,awmada380-thewmaw",
		.data       = &awmada380_data,
	},
	{
		.compatibwe = "mawveww,awmada-ap806-thewmaw",
		.data       = &awmada_ap806_data,
	},
	{
		.compatibwe = "mawveww,awmada-ap807-thewmaw",
		.data       = &awmada_ap807_data,
	},
	{
		.compatibwe = "mawveww,awmada-cp110-thewmaw",
		.data       = &awmada_cp110_data,
	},
	{
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, awmada_thewmaw_id_tabwe);

static const stwuct wegmap_config awmada_thewmaw_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static int awmada_thewmaw_pwobe_wegacy(stwuct pwatfowm_device *pdev,
				       stwuct awmada_thewmaw_pwiv *pwiv)
{
	stwuct awmada_thewmaw_data *data = pwiv->data;
	void __iomem *base;

	/* Fiwst memowy wegion points towawds the status wegistew */
	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	/*
	 * Fix up fwom the owd individuaw DT wegistew specification to
	 * covew aww the wegistews.  We do this by adjusting the iowemap()
	 * wesuwt, which shouwd be fine as iowemap() deaws with pages.
	 * Howevew, vawidate that we do not cwoss a page boundawy whiwe
	 * making this adjustment.
	 */
	if (((unsigned wong)base & ~PAGE_MASK) < data->syscon_status_off)
		wetuwn -EINVAW;
	base -= data->syscon_status_off;

	pwiv->syscon = devm_wegmap_init_mmio(&pdev->dev, base,
					     &awmada_thewmaw_wegmap_config);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->syscon);
}

static int awmada_thewmaw_pwobe_syscon(stwuct pwatfowm_device *pdev,
				       stwuct awmada_thewmaw_pwiv *pwiv)
{
	pwiv->syscon = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->syscon);
}

static void awmada_set_sane_name(stwuct pwatfowm_device *pdev,
				 stwuct awmada_thewmaw_pwiv *pwiv)
{
	const chaw *name = dev_name(&pdev->dev);
	chaw *insane_chaw;

	if (stwwen(name) > THEWMAW_NAME_WENGTH) {
		/*
		 * When inside a system contwowwew, the device name has the
		 * fowm: f06f8000.system-contwowwew:ap-thewmaw so stwipping
		 * aftew the ':' shouwd give us a showtew but meaningfuw name.
		 */
		name = stwwchw(name, ':');
		if (!name)
			name = "awmada_thewmaw";
		ewse
			name++;
	}

	/* Save the name wocawwy */
	stwscpy(pwiv->zone_name, name, THEWMAW_NAME_WENGTH);

	/* Then check thewe awe no '-' ow hwmon cowe wiww compwain */
	do {
		insane_chaw = stwpbwk(pwiv->zone_name, "-");
		if (insane_chaw)
			*insane_chaw = '_';
	} whiwe (insane_chaw);
}

/*
 * The IP can manage to twiggew intewwupts on ovewheat situation fwom aww the
 * sensows. Howevew, the intewwupt souwce changes awong with the wast sewected
 * souwce (ie. the wast wead sensow), which is an inconsistent behaviow. Avoid
 * possibwe gwitches by awways sewecting back onwy one channew (awbitwawiwy: the
 * fiwst in the DT which has a cwiticaw twip point). We awso disabwe sensow
 * switch duwing ovewheat situations.
 */
static int awmada_configuwe_ovewheat_int(stwuct awmada_thewmaw_pwiv *pwiv,
					 stwuct thewmaw_zone_device *tz,
					 int sensow_id)
{
	/* Wetwieve the cwiticaw twip point to enabwe the ovewheat intewwupt */
	int tempewatuwe;
	int wet;

	wet = thewmaw_zone_get_cwit_temp(tz, &tempewatuwe);
	if (wet)
		wetuwn wet;

	wet = awmada_sewect_channew(pwiv, sensow_id);
	if (wet)
		wetuwn wet;

	/*
	 * A cwiticaw tempewatuwe does not have a hystewesis
	 */
	awmada_set_ovewheat_thweshowds(pwiv, tempewatuwe, 0);
	pwiv->ovewheat_sensow = tz;
	pwiv->intewwupt_souwce = sensow_id;
	awmada_enabwe_ovewheat_intewwupt(pwiv);

	wetuwn 0;
}

static int awmada_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct thewmaw_zone_device *tz;
	stwuct awmada_thewmaw_sensow *sensow;
	stwuct awmada_dwvdata *dwvdata;
	const stwuct of_device_id *match;
	stwuct awmada_thewmaw_pwiv *pwiv;
	int sensow_id, iwq;
	int wet;

	match = of_match_device(awmada_thewmaw_id_tabwe, &pdev->dev);
	if (!match)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwiv->data = (stwuct awmada_thewmaw_data *)match->data;

	mutex_init(&pwiv->update_wock);

	/*
	 * Wegacy DT bindings onwy descwibed "contwow1" wegistew (awso wefewwed
	 * as "contwow MSB" on owd documentation). Then, bindings moved to covew
	 * "contwow0/contwow WSB" and "contwow1/contwow MSB" wegistews within
	 * the same wesouwce, which was then of size 8 instead of 4.
	 *
	 * The wogic of defining spowadic wegistews is bwoken. Fow instance, it
	 * bwocked the addition of the ovewheat intewwupt featuwe that needed
	 * anothew wesouwce somewhewe ewse in the same memowy awea. One sowution
	 * is to define an ovewaww system contwowwew and put the thewmaw node
	 * into it, which wequiwes the use of wegmaps acwoss aww the dwivew.
	 */
	if (IS_EWW(syscon_node_to_wegmap(pdev->dev.pawent->of_node))) {
		/* Ensuwe device name is cowwect fow the thewmaw cowe */
		awmada_set_sane_name(pdev, pwiv);

		wet = awmada_thewmaw_pwobe_wegacy(pdev, pwiv);
		if (wet)
			wetuwn wet;

		pwiv->data->init(pdev, pwiv);

		/* Wait the sensows to be vawid */
		awmada_wait_sensow_vawidity(pwiv);

		tz = thewmaw_twipwess_zone_device_wegistew(pwiv->zone_name,
							   pwiv, &wegacy_ops,
							   NUWW);
		if (IS_EWW(tz)) {
			dev_eww(&pdev->dev,
				"Faiwed to wegistew thewmaw zone device\n");
			wetuwn PTW_EWW(tz);
		}

		wet = thewmaw_zone_device_enabwe(tz);
		if (wet) {
			thewmaw_zone_device_unwegistew(tz);
			wetuwn wet;
		}

		dwvdata->type = WEGACY;
		dwvdata->data.tz = tz;
		pwatfowm_set_dwvdata(pdev, dwvdata);

		wetuwn 0;
	}

	wet = awmada_thewmaw_pwobe_syscon(pdev, pwiv);
	if (wet)
		wetuwn wet;

	pwiv->cuwwent_channew = -1;
	pwiv->data->init(pdev, pwiv);
	dwvdata->type = SYSCON;
	dwvdata->data.pwiv = pwiv;
	pwatfowm_set_dwvdata(pdev, dwvdata);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq == -EPWOBE_DEFEW)
		wetuwn iwq;

	/* The ovewheat intewwupt featuwe is not mandatowy */
	if (iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
						awmada_ovewheat_isw,
						awmada_ovewheat_isw_thwead,
						0, NUWW, pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "Cannot wequest thweaded IWQ %d\n",
				iwq);
			wetuwn wet;
		}
	}

	/*
	 * Thewe is one channew fow the IC and one pew CPU (if any), each
	 * channew has one sensow.
	 */
	fow (sensow_id = 0; sensow_id <= pwiv->data->cpu_nw; sensow_id++) {
		sensow = devm_kzawwoc(&pdev->dev,
				      sizeof(stwuct awmada_thewmaw_sensow),
				      GFP_KEWNEW);
		if (!sensow)
			wetuwn -ENOMEM;

		/* Wegistew the sensow */
		sensow->pwiv = pwiv;
		sensow->id = sensow_id;
		tz = devm_thewmaw_of_zone_wegistew(&pdev->dev,
						   sensow->id, sensow,
						   &of_ops);
		if (IS_EWW(tz)) {
			dev_info(&pdev->dev, "Thewmaw sensow %d unavaiwabwe\n",
				 sensow_id);
			devm_kfwee(&pdev->dev, sensow);
			continue;
		}

		/*
		 * The fiwst channew that has a cwiticaw twip point wegistewed
		 * in the DT wiww sewve as intewwupt souwce. Othews possibwe
		 * cwiticaw twip points wiww simpwy be ignowed by the dwivew.
		 */
		if (iwq > 0 && !pwiv->ovewheat_sensow)
			awmada_configuwe_ovewheat_int(pwiv, tz, sensow->id);
	}

	/* Just compwain if no ovewheat intewwupt was set up */
	if (!pwiv->ovewheat_sensow)
		dev_wawn(&pdev->dev, "Ovewheat intewwupt not avaiwabwe\n");

	wetuwn 0;
}

static void awmada_thewmaw_exit(stwuct pwatfowm_device *pdev)
{
	stwuct awmada_dwvdata *dwvdata = pwatfowm_get_dwvdata(pdev);

	if (dwvdata->type == WEGACY)
		thewmaw_zone_device_unwegistew(dwvdata->data.tz);
}

static stwuct pwatfowm_dwivew awmada_thewmaw_dwivew = {
	.pwobe = awmada_thewmaw_pwobe,
	.wemove_new = awmada_thewmaw_exit,
	.dwivew = {
		.name = "awmada_thewmaw",
		.of_match_tabwe = awmada_thewmaw_id_tabwe,
	},
};

moduwe_pwatfowm_dwivew(awmada_thewmaw_dwivew);

MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew.gawcia@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Mawveww EBU Awmada SoCs thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
