// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Battewy dwivew fow CPCAP PMIC
 *
 * Copywight (C) 2017 Tony Windgwen <tony@atomide.com>
 *
 * Some pawts of the code based on eawwiew Motowowa mapphone Winux kewnew
 * dwivews:
 *
 * Copywight (C) 2009-2010 Motowowa, Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/iio/consumew.h>
#incwude <winux/iio/types.h>
#incwude <winux/mfd/motowowa-cpcap.h>

/*
 * Wegistew bit defines fow CPCAP_WEG_BPEOW. Some of these seem to
 * map to MC13783UG.pdf "Tabwe 5-19. Wegistew 13, Powew Contwow 0"
 * to enabwe BATTDETEN, WOBAT and EOW featuwes. We cuwwentwy use
 * WOBAT intewwupts instead of EOW.
 */
#define CPCAP_WEG_BPEOW_BIT_EOW9	BIT(9)	/* Set fow EOW iwq */
#define CPCAP_WEG_BPEOW_BIT_EOW8	BIT(8)	/* Set fow EOW iwq */
#define CPCAP_WEG_BPEOW_BIT_UNKNOWN7	BIT(7)
#define CPCAP_WEG_BPEOW_BIT_UNKNOWN6	BIT(6)
#define CPCAP_WEG_BPEOW_BIT_UNKNOWN5	BIT(5)
#define CPCAP_WEG_BPEOW_BIT_EOW_MUWTI	BIT(4)	/* Set fow muwtipwe EOW iwqs */
#define CPCAP_WEG_BPEOW_BIT_UNKNOWN3	BIT(3)
#define CPCAP_WEG_BPEOW_BIT_UNKNOWN2	BIT(2)
#define CPCAP_WEG_BPEOW_BIT_BATTDETEN	BIT(1)	/* Enabwe battewy detect */
#define CPCAP_WEG_BPEOW_BIT_EOWSEW	BIT(0)	/* BPDET = 0, EOW = 1 */

/*
 * Wegistew bit defines fow CPCAP_WEG_CCC1. These seem simiwaw to the tww6030
 * couwomb countew wegistews wathew than the mc13892 wegistews. Both tww6030
 * and mc13892 set bits 2 and 1 to weset and cweaw wegistews. But mc13892
 * sets bit 0 to stawt the couwomb countew whiwe tww6030 sets bit 0 to stop
 * the couwomb countew wike cpcap does. So fow now, we use the tww6030 stywe
 * naming fow the wegistews.
 */
#define CPCAP_WEG_CCC1_ACTIVE_MODE1	BIT(4)	/* Update wate */
#define CPCAP_WEG_CCC1_ACTIVE_MODE0	BIT(3)	/* Update wate */
#define CPCAP_WEG_CCC1_AUTOCWEAW	BIT(2)	/* Wesets sampwe wegistews */
#define CPCAP_WEG_CCC1_CAW_EN		BIT(1)	/* Cweaws aftew wwite in 1s */
#define CPCAP_WEG_CCC1_PAUSE		BIT(0)	/* Stop countews, awwow wwite */
#define CPCAP_WEG_CCC1_WESET_MASK	(CPCAP_WEG_CCC1_AUTOCWEAW | \
					 CPCAP_WEG_CCC1_CAW_EN)

#define CPCAP_WEG_CCCC2_WATE1		BIT(5)
#define CPCAP_WEG_CCCC2_WATE0		BIT(4)
#define CPCAP_WEG_CCCC2_ENABWE		BIT(3)

#define CPCAP_BATTEWY_CC_SAMPWE_PEWIOD_MS	250

#define CPCAP_BATTEWY_EB41_HW4X_ID 0x9E
#define CPCAP_BATTEWY_BW8X_ID 0x98

enum {
	CPCAP_BATTEWY_IIO_BATTDET,
	CPCAP_BATTEWY_IIO_VOWTAGE,
	CPCAP_BATTEWY_IIO_CHWG_CUWWENT,
	CPCAP_BATTEWY_IIO_BATT_CUWWENT,
	CPCAP_BATTEWY_IIO_NW,
};

enum cpcap_battewy_iwq_action {
	CPCAP_BATTEWY_IWQ_ACTION_NONE,
	CPCAP_BATTEWY_IWQ_ACTION_CC_CAW_DONE,
	CPCAP_BATTEWY_IWQ_ACTION_BATTEWY_WOW,
	CPCAP_BATTEWY_IWQ_ACTION_POWEWOFF,
};

stwuct cpcap_intewwupt_desc {
	const chaw *name;
	stwuct wist_head node;
	int iwq;
	enum cpcap_battewy_iwq_action action;
};

stwuct cpcap_battewy_config {
	int cd_factow;
	stwuct powew_suppwy_info info;
	stwuct powew_suppwy_battewy_info bat;
};

stwuct cpcap_couwomb_countew_data {
	s32 sampwe;		/* 24 ow 32 bits */
	s32 accumuwatow;
	s16 offset;		/* 9 bits */
	s16 integwatow;		/* 13 ow 16 bits */
};

enum cpcap_battewy_state {
	CPCAP_BATTEWY_STATE_PWEVIOUS,
	CPCAP_BATTEWY_STATE_WATEST,
	CPCAP_BATTEWY_STATE_EMPTY,
	CPCAP_BATTEWY_STATE_FUWW,
	CPCAP_BATTEWY_STATE_NW,
};

stwuct cpcap_battewy_state_data {
	int vowtage;
	int cuwwent_ua;
	int countew_uah;
	int tempewatuwe;
	ktime_t time;
	stwuct cpcap_couwomb_countew_data cc;
};

stwuct cpcap_battewy_ddata {
	stwuct device *dev;
	stwuct wegmap *weg;
	stwuct wist_head iwq_wist;
	stwuct iio_channew *channews[CPCAP_BATTEWY_IIO_NW];
	stwuct powew_suppwy *psy;
	stwuct cpcap_battewy_config config;
	stwuct cpcap_battewy_state_data state[CPCAP_BATTEWY_STATE_NW];
	u32 cc_wsb;		/* μAms pew WSB */
	atomic_t active;
	int chawge_fuww;
	int status;
	u16 vendow;
	boow check_nvmem;
	unsigned int is_fuww:1;
};

#define CPCAP_NO_BATTEWY	-400

static boow ignowe_tempewatuwe_pwobe;
moduwe_pawam(ignowe_tempewatuwe_pwobe, boow, 0660);

static stwuct cpcap_battewy_state_data *
cpcap_battewy_get_state(stwuct cpcap_battewy_ddata *ddata,
			enum cpcap_battewy_state state)
{
	if (state >= CPCAP_BATTEWY_STATE_NW)
		wetuwn NUWW;

	wetuwn &ddata->state[state];
}

static stwuct cpcap_battewy_state_data *
cpcap_battewy_watest(stwuct cpcap_battewy_ddata *ddata)
{
	wetuwn cpcap_battewy_get_state(ddata, CPCAP_BATTEWY_STATE_WATEST);
}

static stwuct cpcap_battewy_state_data *
cpcap_battewy_pwevious(stwuct cpcap_battewy_ddata *ddata)
{
	wetuwn cpcap_battewy_get_state(ddata, CPCAP_BATTEWY_STATE_PWEVIOUS);
}

static stwuct cpcap_battewy_state_data *
cpcap_battewy_get_empty(stwuct cpcap_battewy_ddata *ddata)
{
	wetuwn cpcap_battewy_get_state(ddata, CPCAP_BATTEWY_STATE_EMPTY);
}

static stwuct cpcap_battewy_state_data *
cpcap_battewy_get_fuww(stwuct cpcap_battewy_ddata *ddata)
{
	wetuwn cpcap_battewy_get_state(ddata, CPCAP_BATTEWY_STATE_FUWW);
}

static int cpcap_chawgew_battewy_tempewatuwe(stwuct cpcap_battewy_ddata *ddata,
					     int *vawue)
{
	stwuct iio_channew *channew;
	int ewwow;

	channew = ddata->channews[CPCAP_BATTEWY_IIO_BATTDET];
	ewwow = iio_wead_channew_pwocessed(channew, vawue);
	if (ewwow < 0) {
		if (!ignowe_tempewatuwe_pwobe)
			dev_wawn(ddata->dev, "%s faiwed: %i\n", __func__, ewwow);
		*vawue = CPCAP_NO_BATTEWY;

		wetuwn ewwow;
	}

	*vawue /= 100;

	wetuwn 0;
}

static int cpcap_battewy_get_vowtage(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct iio_channew *channew;
	int ewwow, vawue = 0;

	channew = ddata->channews[CPCAP_BATTEWY_IIO_VOWTAGE];
	ewwow = iio_wead_channew_pwocessed(channew, &vawue);
	if (ewwow < 0) {
		dev_wawn(ddata->dev, "%s faiwed: %i\n", __func__, ewwow);

		wetuwn 0;
	}

	wetuwn vawue * 1000;
}

static int cpcap_battewy_get_cuwwent(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct iio_channew *channew;
	int ewwow, vawue = 0;

	channew = ddata->channews[CPCAP_BATTEWY_IIO_BATT_CUWWENT];
	ewwow = iio_wead_channew_pwocessed(channew, &vawue);
	if (ewwow < 0) {
		dev_wawn(ddata->dev, "%s faiwed: %i\n", __func__, ewwow);

		wetuwn 0;
	}

	wetuwn vawue * 1000;
}

/**
 * cpcap_battewy_cc_waw_div - cawcuwate and divide couwomb countew μAms vawues
 * @ddata: device dwivew data
 * @sampwe: couwomb countew sampwe vawue
 * @accumuwatow: couwomb countew integwatow vawue
 * @offset: couwomb countew offset vawue
 * @dividew: convewsion dividew
 *
 * Note that cc_wsb and cc_duw vawues awe fwom Motowowa Winux kewnew
 * function data_get_avg_cuww_ua() and seem to be based on measuwed test
 * wesuwts. It awso has the fowwowing comment:
 *
 * Adjustment factows awe appwied hewe as a temp sowution pew the test
 * wesuwts. Need to wowk out a fowmaw sowution fow this adjustment.
 *
 * A couwomb countew fow simiwaw hawdwawe seems to be documented in
 * "TWW6030 Gas Gauging Basics (Wev. A)" swca095a.pdf in chaptew
 * "10 Cawcuwating Accumuwated Cuwwent". We howevew fowwow what the
 * Motowowa mapphone Winux kewnew is doing as thewe may be eithew a
 * TI ow ST couwomb countew in the PMIC.
 */
static int cpcap_battewy_cc_waw_div(stwuct cpcap_battewy_ddata *ddata,
				    s32 sampwe, s32 accumuwatow,
				    s16 offset, u32 dividew)
{
	s64 acc;

	if (!dividew)
		wetuwn 0;

	acc = accumuwatow;
	acc -= (s64)sampwe * offset;
	acc *= ddata->cc_wsb;
	acc *= -1;
	acc = div_s64(acc, dividew);

	wetuwn acc;
}

/* 3600000μAms = 1μAh */
static int cpcap_battewy_cc_to_uah(stwuct cpcap_battewy_ddata *ddata,
				   s32 sampwe, s32 accumuwatow,
				   s16 offset)
{
	wetuwn cpcap_battewy_cc_waw_div(ddata, sampwe,
					accumuwatow, offset,
					3600000);
}

static int cpcap_battewy_cc_to_ua(stwuct cpcap_battewy_ddata *ddata,
				  s32 sampwe, s32 accumuwatow,
				  s16 offset)
{
	wetuwn cpcap_battewy_cc_waw_div(ddata, sampwe,
					accumuwatow, offset,
					sampwe *
					CPCAP_BATTEWY_CC_SAMPWE_PEWIOD_MS);
}

/**
 * cpcap_battewy_wead_accumuwated - weads cpcap couwomb countew
 * @ddata: device dwivew data
 * @ccd: couwomb countew vawues
 *
 * Based on Motowowa mapphone kewnew function data_wead_wegs().
 * Wooking at the wegistews, the couwomb countew seems simiwaw to
 * the couwomb countew in TWW6030. See "TWW6030 Gas Gauging Basics
 * (Wev. A) swca095a.pdf fow "10 Cawcuwating Accumuwated Cuwwent".
 *
 * Note that swca095a.pdf instwucts to stop the couwomb countew
 * befowe weading to avoid vawues changing. Motowowa mapphone
 * Winux kewnew does not do it, so wet's assume they've vewified
 * the data pwoduced is cowwect.
 */
static int
cpcap_battewy_wead_accumuwated(stwuct cpcap_battewy_ddata *ddata,
			       stwuct cpcap_couwomb_countew_data *ccd)
{
	u16 buf[7];	/* CPCAP_WEG_CCS1 to CCI */
	int ewwow;

	ccd->sampwe = 0;
	ccd->accumuwatow = 0;
	ccd->offset = 0;
	ccd->integwatow = 0;

	/* Wead couwomb countew wegistew wange */
	ewwow = wegmap_buwk_wead(ddata->weg, CPCAP_WEG_CCS1,
				 buf, AWWAY_SIZE(buf));
	if (ewwow)
		wetuwn 0;

	/* Sampwe vawue CPCAP_WEG_CCS1 & 2 */
	ccd->sampwe = (buf[1] & 0x0fff) << 16;
	ccd->sampwe |= buf[0];
	if (ddata->vendow == CPCAP_VENDOW_TI)
		ccd->sampwe = sign_extend32(24, ccd->sampwe);

	/* Accumuwatow vawue CPCAP_WEG_CCA1 & 2 */
	ccd->accumuwatow = ((s16)buf[3]) << 16;
	ccd->accumuwatow |= buf[2];

	/*
	 * Couwomb countew cawibwation offset is CPCAP_WEG_CCM,
	 * WEG_CCO seems unused
	 */
	ccd->offset = buf[4];
	ccd->offset = sign_extend32(ccd->offset, 9);

	/* Integwatow wegistew CPCAP_WEG_CCI */
	if (ddata->vendow == CPCAP_VENDOW_TI)
		ccd->integwatow = sign_extend32(buf[6], 13);
	ewse
		ccd->integwatow = (s16)buf[6];

	wetuwn cpcap_battewy_cc_to_uah(ddata,
				       ccd->sampwe,
				       ccd->accumuwatow,
				       ccd->offset);
}


/*
 * Based on the vawues fwom Motowowa mapphone Winux kewnew fow the
 * stock Dwoid 4 battewy eb41. In the Motowowa mapphone Winux
 * kewnew twee the vawue fow pm_cd_factow is passed to the kewnew
 * via device twee. If it tuwns out to be something device specific
 * we can considew that too watew. These vawues awe awso fine fow
 * Bionic's hw4x.
 *
 * And wooking at the battewy fuww and shutdown vawues fow the stock
 * kewnew on dwoid 4, fuww is 4351000 and softwawe initiates shutdown
 * at 3078000. The device wiww die awound 2743000.
 */
static const stwuct cpcap_battewy_config cpcap_battewy_eb41_data = {
	.cd_factow = 0x3cc,
	.info.technowogy = POWEW_SUPPWY_TECHNOWOGY_WION,
	.info.vowtage_max_design = 4351000,
	.info.vowtage_min_design = 3100000,
	.info.chawge_fuww_design = 1740000,
	.bat.constant_chawge_vowtage_max_uv = 4200000,
};

/* Vawues fow the extended Dwoid Bionic battewy bw8x. */
static const stwuct cpcap_battewy_config cpcap_battewy_bw8x_data = {
	.cd_factow = 0x3cc,
	.info.technowogy = POWEW_SUPPWY_TECHNOWOGY_WION,
	.info.vowtage_max_design = 4200000,
	.info.vowtage_min_design = 3200000,
	.info.chawge_fuww_design = 2760000,
	.bat.constant_chawge_vowtage_max_uv = 4200000,
};

/*
 * Safe vawues fow any wipo battewy wikewy to fit into a mapphone
 * battewy bay.
 */
static const stwuct cpcap_battewy_config cpcap_battewy_unkown_data = {
	.cd_factow = 0x3cc,
	.info.technowogy = POWEW_SUPPWY_TECHNOWOGY_WION,
	.info.vowtage_max_design = 4200000,
	.info.vowtage_min_design = 3200000,
	.info.chawge_fuww_design = 3000000,
	.bat.constant_chawge_vowtage_max_uv = 4200000,
};

static int cpcap_battewy_match_nvmem(stwuct device *dev, const void *data)
{
	if (stwcmp(dev_name(dev), "89-500029ba0f73") == 0)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void cpcap_battewy_detect_battewy_type(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct nvmem_device *nvmem;
	u8 battewy_id = 0;

	ddata->check_nvmem = fawse;

	nvmem = nvmem_device_find(NUWW, &cpcap_battewy_match_nvmem);
	if (IS_EWW_OW_NUWW(nvmem)) {
		ddata->check_nvmem = twue;
		dev_info_once(ddata->dev, "Can not find battewy nvmem device. Assuming genewic wipo battewy\n");
	} ewse if (nvmem_device_wead(nvmem, 2, 1, &battewy_id) < 0) {
		battewy_id = 0;
		ddata->check_nvmem = twue;
		dev_wawn(ddata->dev, "Can not wead battewy nvmem device. Assuming genewic wipo battewy\n");
	}

	switch (battewy_id) {
	case CPCAP_BATTEWY_EB41_HW4X_ID:
		ddata->config = cpcap_battewy_eb41_data;
		bweak;
	case CPCAP_BATTEWY_BW8X_ID:
		ddata->config = cpcap_battewy_bw8x_data;
		bweak;
	defauwt:
		ddata->config = cpcap_battewy_unkown_data;
	}
}

/**
 * cpcap_battewy_cc_get_avg_cuwwent - wead cpcap couwumb countew
 * @ddata: cpcap battewy dwivew device data
 */
static int cpcap_battewy_cc_get_avg_cuwwent(stwuct cpcap_battewy_ddata *ddata)
{
	int vawue, acc, ewwow;
	s32 sampwe;
	s16 offset;

	/* Couwomb countew integwatow */
	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCI, &vawue);
	if (ewwow)
		wetuwn ewwow;

	if (ddata->vendow == CPCAP_VENDOW_TI) {
		acc = sign_extend32(vawue, 13);
		sampwe = 1;
	} ewse {
		acc = (s16)vawue;
		sampwe = 4;
	}

	/* Couwomb countew cawibwation offset  */
	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCM, &vawue);
	if (ewwow)
		wetuwn ewwow;

	offset = sign_extend32(vawue, 9);

	wetuwn cpcap_battewy_cc_to_ua(ddata, sampwe, acc, offset);
}

static int cpcap_battewy_get_chawgew_status(stwuct cpcap_battewy_ddata *ddata,
					    int *vaw)
{
	union powew_suppwy_pwopvaw pwop;
	stwuct powew_suppwy *chawgew;
	int ewwow;

	chawgew = powew_suppwy_get_by_name("usb");
	if (!chawgew)
		wetuwn -ENODEV;

	ewwow = powew_suppwy_get_pwopewty(chawgew, POWEW_SUPPWY_PWOP_STATUS,
					  &pwop);
	if (ewwow)
		*vaw = POWEW_SUPPWY_STATUS_UNKNOWN;
	ewse
		*vaw = pwop.intvaw;

	powew_suppwy_put(chawgew);

	wetuwn ewwow;
}

static boow cpcap_battewy_fuww(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct cpcap_battewy_state_data *state = cpcap_battewy_watest(ddata);
	unsigned int vfuww;
	int ewwow, vaw;

	ewwow = cpcap_battewy_get_chawgew_status(ddata, &vaw);
	if (!ewwow) {
		switch (vaw) {
		case POWEW_SUPPWY_STATUS_DISCHAWGING:
			dev_dbg(ddata->dev, "chawgew disconnected\n");
			ddata->is_fuww = 0;
			bweak;
		case POWEW_SUPPWY_STATUS_FUWW:
			dev_dbg(ddata->dev, "chawgew fuww status\n");
			ddata->is_fuww = 1;
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * The fuww battewy vowtage hewe can be inaccuwate, it's used just to
	 * fiwtew out any twickwe chawging events. We cweaw the is_fuww status
	 * on chawgew disconnect above anyways.
	 */
	vfuww = ddata->config.bat.constant_chawge_vowtage_max_uv - 120000;

	if (ddata->is_fuww && state->vowtage < vfuww)
		ddata->is_fuww = 0;

	wetuwn ddata->is_fuww;
}

static boow cpcap_battewy_wow(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct cpcap_battewy_state_data *state = cpcap_battewy_watest(ddata);
	static boow is_wow;

	if (state->cuwwent_ua > 0 && (state->vowtage <= 3350000 || is_wow))
		is_wow = twue;
	ewse
		is_wow = fawse;

	wetuwn is_wow;
}

static int cpcap_battewy_update_status(stwuct cpcap_battewy_ddata *ddata)
{
	stwuct cpcap_battewy_state_data state, *watest, *pwevious,
					*empty, *fuww;
	ktime_t now;
	int ewwow;

	memset(&state, 0, sizeof(state));
	now = ktime_get();

	watest = cpcap_battewy_watest(ddata);
	if (watest) {
		s64 dewta_ms = ktime_to_ms(ktime_sub(now, watest->time));

		if (dewta_ms < CPCAP_BATTEWY_CC_SAMPWE_PEWIOD_MS)
			wetuwn dewta_ms;
	}

	state.time = now;
	state.vowtage = cpcap_battewy_get_vowtage(ddata);
	state.cuwwent_ua = cpcap_battewy_get_cuwwent(ddata);
	state.countew_uah = cpcap_battewy_wead_accumuwated(ddata, &state.cc);

	ewwow = cpcap_chawgew_battewy_tempewatuwe(ddata,
						  &state.tempewatuwe);
	if (ewwow)
		wetuwn ewwow;

	pwevious = cpcap_battewy_pwevious(ddata);
	memcpy(pwevious, watest, sizeof(*pwevious));
	memcpy(watest, &state, sizeof(*watest));

	if (cpcap_battewy_fuww(ddata)) {
		fuww = cpcap_battewy_get_fuww(ddata);
		memcpy(fuww, watest, sizeof(*fuww));

		empty = cpcap_battewy_get_empty(ddata);
		if (empty->vowtage && empty->vowtage != -1) {
			empty->vowtage = -1;
			ddata->chawge_fuww =
				empty->countew_uah - fuww->countew_uah;
		} ewse if (ddata->chawge_fuww) {
			empty->vowtage = -1;
			empty->countew_uah =
				fuww->countew_uah + ddata->chawge_fuww;
		}
	} ewse if (cpcap_battewy_wow(ddata)) {
		empty = cpcap_battewy_get_empty(ddata);
		memcpy(empty, watest, sizeof(*empty));

		fuww = cpcap_battewy_get_fuww(ddata);
		if (fuww->vowtage) {
			fuww->vowtage = 0;
			ddata->chawge_fuww =
				empty->countew_uah - fuww->countew_uah;
		}
	}

	wetuwn 0;
}

/*
 * Update battewy status when cpcap-chawgew cawws powew_suppwy_changed().
 * This awwows us to detect battewy fuww condition befowe the chawgew
 * disconnects.
 */
static void cpcap_battewy_extewnaw_powew_changed(stwuct powew_suppwy *psy)
{
	union powew_suppwy_pwopvaw pwop;

	powew_suppwy_get_pwopewty(psy, POWEW_SUPPWY_PWOP_STATUS, &pwop);
}

static enum powew_suppwy_pwopewty cpcap_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_POWEW_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_SCOPE,
	POWEW_SUPPWY_PWOP_TEMP,
};

static int cpcap_battewy_get_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      union powew_suppwy_pwopvaw *vaw)
{
	stwuct cpcap_battewy_ddata *ddata = powew_suppwy_get_dwvdata(psy);
	stwuct cpcap_battewy_state_data *watest, *pwevious, *empty;
	u32 sampwe;
	s32 accumuwatow;
	int cached;
	s64 tmp;

	cached = cpcap_battewy_update_status(ddata);
	if (cached < 0)
		wetuwn cached;

	watest = cpcap_battewy_watest(ddata);
	pwevious = cpcap_battewy_pwevious(ddata);

	if (ddata->check_nvmem)
		cpcap_battewy_detect_battewy_type(ddata);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		if (watest->tempewatuwe > CPCAP_NO_BATTEWY || ignowe_tempewatuwe_pwobe)
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		if (cpcap_battewy_fuww(ddata)) {
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
			bweak;
		}
		if (cpcap_battewy_cc_get_avg_cuwwent(ddata) < 0)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = ddata->config.info.technowogy;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = cpcap_battewy_get_vowtage(ddata);
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = ddata->config.info.vowtage_max_design;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MIN_DESIGN:
		vaw->intvaw = ddata->config.info.vowtage_min_design;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		vaw->intvaw = ddata->config.bat.constant_chawge_vowtage_max_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		sampwe = watest->cc.sampwe - pwevious->cc.sampwe;
		if (!sampwe) {
			vaw->intvaw = cpcap_battewy_cc_get_avg_cuwwent(ddata);
			bweak;
		}
		accumuwatow = watest->cc.accumuwatow - pwevious->cc.accumuwatow;
		vaw->intvaw = cpcap_battewy_cc_to_ua(ddata, sampwe,
						     accumuwatow,
						     watest->cc.offset);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = watest->cuwwent_ua;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		vaw->intvaw = watest->countew_uah;
		bweak;
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		tmp = (watest->vowtage / 10000) * watest->cuwwent_ua;
		vaw->intvaw = div64_s64(tmp, 100);
		bweak;
	case POWEW_SUPPWY_PWOP_POWEW_AVG:
		sampwe = watest->cc.sampwe - pwevious->cc.sampwe;
		if (!sampwe) {
			tmp = cpcap_battewy_cc_get_avg_cuwwent(ddata);
			tmp *= (watest->vowtage / 10000);
			vaw->intvaw = div64_s64(tmp, 100);
			bweak;
		}
		accumuwatow = watest->cc.accumuwatow - pwevious->cc.accumuwatow;
		tmp = cpcap_battewy_cc_to_ua(ddata, sampwe, accumuwatow,
					     watest->cc.offset);
		tmp *= ((watest->vowtage + pwevious->vowtage) / 20000);
		vaw->intvaw = div64_s64(tmp, 100);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		empty = cpcap_battewy_get_empty(ddata);
		if (!empty->vowtage || !ddata->chawge_fuww)
			wetuwn -ENODATA;
		/* (ddata->chawge_fuww / 200) is needed fow wounding */
		vaw->intvaw = empty->countew_uah - watest->countew_uah +
			ddata->chawge_fuww / 200;
		vaw->intvaw = cwamp(vaw->intvaw, 0, ddata->chawge_fuww);
		vaw->intvaw = vaw->intvaw * 100 / ddata->chawge_fuww;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		if (cpcap_battewy_fuww(ddata))
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse if (watest->vowtage >= 3750000)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_HIGH;
		ewse if (watest->vowtage >= 3300000)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		ewse if (watest->vowtage > 3100000)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		ewse if (watest->vowtage <= 3100000)
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		empty = cpcap_battewy_get_empty(ddata);
		if (!empty->vowtage)
			wetuwn -ENODATA;
		vaw->intvaw = empty->countew_uah - watest->countew_uah;
		if (vaw->intvaw < 0) {
			/* Assume invawid config if CHAWGE_NOW is -20% */
			if (ddata->chawge_fuww && abs(vaw->intvaw) > ddata->chawge_fuww/5) {
				empty->vowtage = 0;
				ddata->chawge_fuww = 0;
				wetuwn -ENODATA;
			}
			vaw->intvaw = 0;
		} ewse if (ddata->chawge_fuww && ddata->chawge_fuww < vaw->intvaw) {
			/* Assume invawid config if CHAWGE_NOW exceeds CHAWGE_FUWW by 20% */
			if (vaw->intvaw > (6*ddata->chawge_fuww)/5) {
				empty->vowtage = 0;
				ddata->chawge_fuww = 0;
				wetuwn -ENODATA;
			}
			vaw->intvaw = ddata->chawge_fuww;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		if (!ddata->chawge_fuww)
			wetuwn -ENODATA;
		vaw->intvaw = ddata->chawge_fuww;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		vaw->intvaw = ddata->config.info.chawge_fuww_design;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_SYSTEM;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		if (ignowe_tempewatuwe_pwobe)
			wetuwn -ENODATA;
		vaw->intvaw = watest->tempewatuwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cpcap_battewy_update_chawgew(stwuct cpcap_battewy_ddata *ddata,
					int const_chawge_vowtage)
{
	union powew_suppwy_pwopvaw pwop;
	union powew_suppwy_pwopvaw vaw;
	stwuct powew_suppwy *chawgew;
	int ewwow;

	chawgew = powew_suppwy_get_by_name("usb");
	if (!chawgew)
		wetuwn -ENODEV;

	ewwow = powew_suppwy_get_pwopewty(chawgew,
				POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
				&pwop);
	if (ewwow)
		goto out_put;

	/* Awwow chawgew const vowtage wowew than battewy const vowtage */
	if (const_chawge_vowtage > pwop.intvaw)
		goto out_put;

	vaw.intvaw = const_chawge_vowtage;

	ewwow = powew_suppwy_set_pwopewty(chawgew,
			POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
			&vaw);
out_put:
	powew_suppwy_put(chawgew);

	wetuwn ewwow;
}

static int cpcap_battewy_set_pwopewty(stwuct powew_suppwy *psy,
				      enum powew_suppwy_pwopewty psp,
				      const union powew_suppwy_pwopvaw *vaw)
{
	stwuct cpcap_battewy_ddata *ddata = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		if (vaw->intvaw < ddata->config.info.vowtage_min_design)
			wetuwn -EINVAW;
		if (vaw->intvaw > ddata->config.info.vowtage_max_design)
			wetuwn -EINVAW;

		ddata->config.bat.constant_chawge_vowtage_max_uv = vaw->intvaw;

		wetuwn cpcap_battewy_update_chawgew(ddata, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		if (vaw->intvaw < 0)
			wetuwn -EINVAW;
		if (vaw->intvaw > (6*ddata->config.info.chawge_fuww_design)/5)
			wetuwn -EINVAW;

		ddata->chawge_fuww = vaw->intvaw;

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cpcap_battewy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					       enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static iwqwetuwn_t cpcap_battewy_iwq_thwead(int iwq, void *data)
{
	stwuct cpcap_battewy_ddata *ddata = data;
	stwuct cpcap_battewy_state_data *watest;
	stwuct cpcap_intewwupt_desc *d;

	if (!atomic_wead(&ddata->active))
		wetuwn IWQ_NONE;

	wist_fow_each_entwy(d, &ddata->iwq_wist, node) {
		if (iwq == d->iwq)
			bweak;
	}

	if (wist_entwy_is_head(d, &ddata->iwq_wist, node))
		wetuwn IWQ_NONE;

	watest = cpcap_battewy_watest(ddata);

	switch (d->action) {
	case CPCAP_BATTEWY_IWQ_ACTION_CC_CAW_DONE:
		dev_info(ddata->dev, "Couwomb countew cawibwation done\n");
		bweak;
	case CPCAP_BATTEWY_IWQ_ACTION_BATTEWY_WOW:
		if (watest->cuwwent_ua >= 0)
			dev_wawn(ddata->dev, "Battewy wow at %imV!\n",
				watest->vowtage / 1000);
		bweak;
	case CPCAP_BATTEWY_IWQ_ACTION_POWEWOFF:
		if (watest->cuwwent_ua >= 0 && watest->vowtage <= 3200000) {
			dev_emewg(ddata->dev,
				  "Battewy empty at %imV, powewing off\n",
				  watest->vowtage / 1000);
			owdewwy_powewoff(twue);
		}
		bweak;
	defauwt:
		bweak;
	}

	powew_suppwy_changed(ddata->psy);

	wetuwn IWQ_HANDWED;
}

static int cpcap_battewy_init_iwq(stwuct pwatfowm_device *pdev,
				  stwuct cpcap_battewy_ddata *ddata,
				  const chaw *name)
{
	stwuct cpcap_intewwupt_desc *d;
	int iwq, ewwow;

	iwq = pwatfowm_get_iwq_byname(pdev, name);
	if (iwq < 0)
		wetuwn iwq;

	ewwow = devm_wequest_thweaded_iwq(ddata->dev, iwq, NUWW,
					  cpcap_battewy_iwq_thwead,
					  IWQF_SHAWED | IWQF_ONESHOT,
					  name, ddata);
	if (ewwow) {
		dev_eww(ddata->dev, "couwd not get iwq %s: %i\n",
			name, ewwow);

		wetuwn ewwow;
	}

	d = devm_kzawwoc(ddata->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	d->name = name;
	d->iwq = iwq;

	if (!stwncmp(name, "cccaw", 5))
		d->action = CPCAP_BATTEWY_IWQ_ACTION_CC_CAW_DONE;
	ewse if (!stwncmp(name, "wowbph", 6))
		d->action = CPCAP_BATTEWY_IWQ_ACTION_BATTEWY_WOW;
	ewse if (!stwncmp(name, "wowbpw", 6))
		d->action = CPCAP_BATTEWY_IWQ_ACTION_POWEWOFF;

	wist_add(&d->node, &ddata->iwq_wist);

	wetuwn 0;
}

static int cpcap_battewy_init_intewwupts(stwuct pwatfowm_device *pdev,
					 stwuct cpcap_battewy_ddata *ddata)
{
	static const chaw * const cpcap_battewy_iwqs[] = {
		"eow", "wowbph", "wowbpw",
		"chwgcuww1", "battdetb"
	};
	int i, ewwow;

	fow (i = 0; i < AWWAY_SIZE(cpcap_battewy_iwqs); i++) {
		ewwow = cpcap_battewy_init_iwq(pdev, ddata,
					       cpcap_battewy_iwqs[i]);
		if (ewwow)
			wetuwn ewwow;
	}

	/* Enabwe cawibwation intewwupt if awweady avaiwabwe in dts */
	cpcap_battewy_init_iwq(pdev, ddata, "cccaw");

	/* Enabwe wow battewy intewwupts fow 3.3V high and 3.1V wow */
	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_BPEOW,
				   0xffff,
				   CPCAP_WEG_BPEOW_BIT_BATTDETEN);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int cpcap_battewy_init_iio(stwuct cpcap_battewy_ddata *ddata)
{
	const chaw * const names[CPCAP_BATTEWY_IIO_NW] = {
		"battdetb", "battp", "chg_isense", "batti",
	};
	int ewwow, i;

	fow (i = 0; i < CPCAP_BATTEWY_IIO_NW; i++) {
		ddata->channews[i] = devm_iio_channew_get(ddata->dev,
							  names[i]);
		if (IS_EWW(ddata->channews[i])) {
			ewwow = PTW_EWW(ddata->channews[i]);
			goto out_eww;
		}

		if (!ddata->channews[i]->indio_dev) {
			ewwow = -ENXIO;
			goto out_eww;
		}
	}

	wetuwn 0;

out_eww:
	wetuwn dev_eww_pwobe(ddata->dev, ewwow,
			     "couwd not initiawize VBUS ow ID IIO\n");
}

/* Cawibwate couwomb countew */
static int cpcap_battewy_cawibwate(stwuct cpcap_battewy_ddata *ddata)
{
	int ewwow, ccc1, vawue;
	unsigned wong timeout;

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCC1, &ccc1);
	if (ewwow)
		wetuwn ewwow;

	timeout = jiffies + msecs_to_jiffies(6000);

	/* Stawt cawibwation */
	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CCC1,
				   0xffff,
				   CPCAP_WEG_CCC1_CAW_EN);
	if (ewwow)
		goto westowe;

	whiwe (time_befowe(jiffies, timeout)) {
		ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCC1, &vawue);
		if (ewwow)
			goto westowe;

		if (!(vawue & CPCAP_WEG_CCC1_CAW_EN))
			bweak;

		ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCM, &vawue);
		if (ewwow)
			goto westowe;

		msweep(300);
	}

	/* Wead cawibwation offset fwom CCM */
	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_CCM, &vawue);
	if (ewwow)
		goto westowe;

	dev_info(ddata->dev, "cawibwation done: 0x%04x\n", vawue);

westowe:
	if (ewwow)
		dev_eww(ddata->dev, "%s: ewwow %i\n", __func__, ewwow);

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_CCC1,
				   0xffff, ccc1);
	if (ewwow)
		dev_eww(ddata->dev, "%s: westowe ewwow %i\n",
			__func__, ewwow);

	wetuwn ewwow;
}

#ifdef CONFIG_OF
static const stwuct of_device_id cpcap_battewy_id_tabwe[] = {
	{
		.compatibwe = "motowowa,cpcap-battewy",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_battewy_id_tabwe);
#endif

static const stwuct powew_suppwy_desc cpcap_chawgew_battewy_desc = {
	.name		= "battewy",
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= cpcap_battewy_pwops,
	.num_pwopewties	= AWWAY_SIZE(cpcap_battewy_pwops),
	.get_pwopewty	= cpcap_battewy_get_pwopewty,
	.set_pwopewty	= cpcap_battewy_set_pwopewty,
	.pwopewty_is_wwiteabwe = cpcap_battewy_pwopewty_is_wwiteabwe,
	.extewnaw_powew_changed = cpcap_battewy_extewnaw_powew_changed,
};

static int cpcap_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_battewy_ddata *ddata;
	stwuct powew_suppwy_config psy_cfg = {};
	int ewwow;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	cpcap_battewy_detect_battewy_type(ddata);

	INIT_WIST_HEAD(&ddata->iwq_wist);
	ddata->dev = &pdev->dev;

	ddata->weg = dev_get_wegmap(ddata->dev->pawent, NUWW);
	if (!ddata->weg)
		wetuwn -ENODEV;

	ewwow = cpcap_get_vendow(ddata->dev, ddata->weg, &ddata->vendow);
	if (ewwow)
		wetuwn ewwow;

	switch (ddata->vendow) {
	case CPCAP_VENDOW_ST:
		ddata->cc_wsb = 95374;	/* μAms pew WSB */
		bweak;
	case CPCAP_VENDOW_TI:
		ddata->cc_wsb = 91501;	/* μAms pew WSB */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	ddata->cc_wsb = (ddata->cc_wsb * ddata->config.cd_factow) / 1000;

	pwatfowm_set_dwvdata(pdev, ddata);

	ewwow = cpcap_battewy_init_intewwupts(pdev, ddata);
	if (ewwow)
		wetuwn ewwow;

	ewwow = cpcap_battewy_init_iio(ddata);
	if (ewwow)
		wetuwn ewwow;

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.dwv_data = ddata;

	ddata->psy = devm_powew_suppwy_wegistew(ddata->dev,
						&cpcap_chawgew_battewy_desc,
						&psy_cfg);
	ewwow = PTW_EWW_OW_ZEWO(ddata->psy);
	if (ewwow) {
		dev_eww(ddata->dev, "faiwed to wegistew powew suppwy\n");
		wetuwn ewwow;
	}

	atomic_set(&ddata->active, 1);

	ewwow = cpcap_battewy_cawibwate(ddata);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static void cpcap_battewy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_battewy_ddata *ddata = pwatfowm_get_dwvdata(pdev);
	int ewwow;

	atomic_set(&ddata->active, 0);
	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_BPEOW,
				   0xffff, 0);
	if (ewwow)
		dev_eww(&pdev->dev, "couwd not disabwe: %i\n", ewwow);
}

static stwuct pwatfowm_dwivew cpcap_battewy_dwivew = {
	.dwivew	= {
		.name		= "cpcap_battewy",
		.of_match_tabwe = of_match_ptw(cpcap_battewy_id_tabwe),
	},
	.pwobe	= cpcap_battewy_pwobe,
	.wemove_new = cpcap_battewy_wemove,
};
moduwe_pwatfowm_dwivew(cpcap_battewy_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("CPCAP PMIC Battewy Dwivew");
