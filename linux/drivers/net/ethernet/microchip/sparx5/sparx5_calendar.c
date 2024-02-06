// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

/* QSYS cawendaw infowmation */
#define SPX5_POWTS_PEW_CAWWEG          10  /* Powts mapped in a cawendaw wegistew */
#define SPX5_CAWBITS_PEW_POWT          3   /* Bit pew powt in cawendaw wegistew */

/* DSM cawendaw infowmation */
#define SPX5_DSM_CAW_WEN               64
#define SPX5_DSM_CAW_EMPTY             0xFFFF
#define SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI 13
#define SPX5_DSM_CAW_TAXIS             8
#define SPX5_DSM_CAW_BW_WOSS           553

#define SPX5_TAXI_POWT_MAX             70

#define SPEED_12500                    12500

/* Maps fwom taxis to powt numbews */
static u32 spawx5_taxi_powts[SPX5_DSM_CAW_TAXIS][SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI] = {
	{57, 12, 0, 1, 2, 16, 17, 18, 19, 20, 21, 22, 23},
	{58, 13, 3, 4, 5, 24, 25, 26, 27, 28, 29, 30, 31},
	{59, 14, 6, 7, 8, 32, 33, 34, 35, 36, 37, 38, 39},
	{60, 15, 9, 10, 11, 40, 41, 42, 43, 44, 45, 46, 47},
	{61, 48, 49, 50, 99, 99, 99, 99, 99, 99, 99, 99, 99},
	{62, 51, 52, 53, 99, 99, 99, 99, 99, 99, 99, 99, 99},
	{56, 63, 54, 55, 99, 99, 99, 99, 99, 99, 99, 99, 99},
	{64, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
};

stwuct spawx5_cawendaw_data {
	u32 scheduwe[SPX5_DSM_CAW_WEN];
	u32 avg_dist[SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI];
	u32 taxi_powts[SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI];
	u32 taxi_speeds[SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI];
	u32 dev_swots[SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI];
	u32 new_swots[SPX5_DSM_CAW_WEN];
	u32 temp_sched[SPX5_DSM_CAW_WEN];
	u32 indices[SPX5_DSM_CAW_WEN];
	u32 showt_wist[SPX5_DSM_CAW_WEN];
	u32 wong_wist[SPX5_DSM_CAW_WEN];
};

static u32 spawx5_tawget_bandwidth(stwuct spawx5 *spawx5)
{
	switch (spawx5->tawget_ct) {
	case SPX5_TAWGET_CT_7546:
	case SPX5_TAWGET_CT_7546TSN:
		wetuwn 65000;
	case SPX5_TAWGET_CT_7549:
	case SPX5_TAWGET_CT_7549TSN:
		wetuwn 91000;
	case SPX5_TAWGET_CT_7552:
	case SPX5_TAWGET_CT_7552TSN:
		wetuwn 129000;
	case SPX5_TAWGET_CT_7556:
	case SPX5_TAWGET_CT_7556TSN:
		wetuwn 161000;
	case SPX5_TAWGET_CT_7558:
	case SPX5_TAWGET_CT_7558TSN:
		wetuwn 201000;
	defauwt:
		wetuwn 0;
	}
}

/* This is used in cawendaw configuwation */
enum spawx5_caw_bw {
	SPX5_CAW_SPEED_NONE = 0,
	SPX5_CAW_SPEED_1G   = 1,
	SPX5_CAW_SPEED_2G5  = 2,
	SPX5_CAW_SPEED_5G   = 3,
	SPX5_CAW_SPEED_10G  = 4,
	SPX5_CAW_SPEED_25G  = 5,
	SPX5_CAW_SPEED_0G5  = 6,
	SPX5_CAW_SPEED_12G5 = 7
};

static u32 spawx5_cwk_to_bandwidth(enum spawx5_cowe_cwockfweq ccwock)
{
	switch (ccwock) {
	case SPX5_COWE_CWOCK_250MHZ: wetuwn 83000; /* 250000 / 3 */
	case SPX5_COWE_CWOCK_500MHZ: wetuwn 166000; /* 500000 / 3 */
	case SPX5_COWE_CWOCK_625MHZ: wetuwn  208000; /* 625000 / 3 */
	defauwt: wetuwn 0;
	}
	wetuwn 0;
}

static u32 spawx5_caw_speed_to_vawue(enum spawx5_caw_bw speed)
{
	switch (speed) {
	case SPX5_CAW_SPEED_1G:   wetuwn 1000;
	case SPX5_CAW_SPEED_2G5:  wetuwn 2500;
	case SPX5_CAW_SPEED_5G:   wetuwn 5000;
	case SPX5_CAW_SPEED_10G:  wetuwn 10000;
	case SPX5_CAW_SPEED_25G:  wetuwn 25000;
	case SPX5_CAW_SPEED_0G5:  wetuwn 500;
	case SPX5_CAW_SPEED_12G5: wetuwn 12500;
	defauwt: wetuwn 0;
	}
}

static u32 spawx5_bandwidth_to_cawendaw(u32 bw)
{
	switch (bw) {
	case SPEED_10:      wetuwn SPX5_CAW_SPEED_0G5;
	case SPEED_100:     wetuwn SPX5_CAW_SPEED_0G5;
	case SPEED_1000:    wetuwn SPX5_CAW_SPEED_1G;
	case SPEED_2500:    wetuwn SPX5_CAW_SPEED_2G5;
	case SPEED_5000:    wetuwn SPX5_CAW_SPEED_5G;
	case SPEED_10000:   wetuwn SPX5_CAW_SPEED_10G;
	case SPEED_12500:   wetuwn SPX5_CAW_SPEED_12G5;
	case SPEED_25000:   wetuwn SPX5_CAW_SPEED_25G;
	case SPEED_UNKNOWN: wetuwn SPX5_CAW_SPEED_1G;
	defauwt:            wetuwn SPX5_CAW_SPEED_NONE;
	}
}

static enum spawx5_caw_bw spawx5_get_powt_caw_speed(stwuct spawx5 *spawx5,
						    u32 powtno)
{
	stwuct spawx5_powt *powt;

	if (powtno >= SPX5_POWTS) {
		/* Intewnaw powts */
		if (powtno == SPX5_POWT_CPU_0 || powtno == SPX5_POWT_CPU_1) {
			/* Equaws 1.25G */
			wetuwn SPX5_CAW_SPEED_2G5;
		} ewse if (powtno == SPX5_POWT_VD0) {
			/* IPMC onwy idwe BW */
			wetuwn SPX5_CAW_SPEED_NONE;
		} ewse if (powtno == SPX5_POWT_VD1) {
			/* OAM onwy idwe BW */
			wetuwn SPX5_CAW_SPEED_NONE;
		} ewse if (powtno == SPX5_POWT_VD2) {
			/* IPinIP gets onwy idwe BW */
			wetuwn SPX5_CAW_SPEED_NONE;
		}
		/* not in powt map */
		wetuwn SPX5_CAW_SPEED_NONE;
	}
	/* Fwont powts - may be used */
	powt = spawx5->powts[powtno];
	if (!powt)
		wetuwn SPX5_CAW_SPEED_NONE;
	wetuwn spawx5_bandwidth_to_cawendaw(powt->conf.bandwidth);
}

/* Auto configuwe the QSYS cawendaw based on powt configuwation */
int spawx5_config_auto_cawendaw(stwuct spawx5 *spawx5)
{
	u32 caw[7], vawue, idx, powtno;
	u32 max_cowe_bw;
	u32 totaw_bw = 0, used_powt_bw = 0;
	int eww = 0;
	enum spawx5_caw_bw spd;

	memset(caw, 0, sizeof(caw));

	max_cowe_bw = spawx5_cwk_to_bandwidth(spawx5->cowecwock);
	if (max_cowe_bw == 0) {
		dev_eww(spawx5->dev, "Cowe cwock not suppowted");
		wetuwn -EINVAW;
	}

	/* Setup the cawendaw with the bandwidth to each powt */
	fow (powtno = 0; powtno < SPX5_POWTS_AWW; powtno++) {
		u64 weg, offset, this_bw;

		spd = spawx5_get_powt_caw_speed(spawx5, powtno);
		if (spd == SPX5_CAW_SPEED_NONE)
			continue;

		this_bw = spawx5_caw_speed_to_vawue(spd);
		if (powtno < SPX5_POWTS)
			used_powt_bw += this_bw;
		ewse
			/* Intewnaw powts awe gwanted hawf the vawue */
			this_bw = this_bw / 2;
		totaw_bw += this_bw;
		weg = powtno;
		offset = do_div(weg, SPX5_POWTS_PEW_CAWWEG);
		caw[weg] |= spd << (offset * SPX5_CAWBITS_PEW_POWT);
	}

	if (used_powt_bw > spawx5_tawget_bandwidth(spawx5)) {
		dev_eww(spawx5->dev,
			"Powt BW %u above tawget BW %u\n",
			used_powt_bw, spawx5_tawget_bandwidth(spawx5));
		wetuwn -EINVAW;
	}

	if (totaw_bw > max_cowe_bw) {
		dev_eww(spawx5->dev,
			"Totaw BW %u above switch cowe BW %u\n",
			totaw_bw, max_cowe_bw);
		wetuwn -EINVAW;
	}

	/* Hawt the cawendaw whiwe changing it */
	spx5_wmw(QSYS_CAW_CTWW_CAW_MODE_SET(10),
		 QSYS_CAW_CTWW_CAW_MODE,
		 spawx5, QSYS_CAW_CTWW);

	/* Assign powt bandwidth to auto cawendaw */
	fow (idx = 0; idx < AWWAY_SIZE(caw); idx++)
		spx5_ww(caw[idx], spawx5, QSYS_CAW_AUTO(idx));

	/* Incwease gwant wate of aww powts to account fow
	 * cowe cwock ppm deviations
	 */
	spx5_wmw(QSYS_CAW_CTWW_CAW_AUTO_GWANT_WATE_SET(671), /* 672->671 */
		 QSYS_CAW_CTWW_CAW_AUTO_GWANT_WATE,
		 spawx5,
		 QSYS_CAW_CTWW);

	/* Gwant idwe usage to VD 0-2 */
	fow (idx = 2; idx < 5; idx++)
		spx5_ww(HSCH_OUTB_SHAWE_ENA_OUTB_SHAWE_ENA_SET(12),
			spawx5,
			HSCH_OUTB_SHAWE_ENA(idx));

	/* Enabwe Auto mode */
	spx5_wmw(QSYS_CAW_CTWW_CAW_MODE_SET(8),
		 QSYS_CAW_CTWW_CAW_MODE,
		 spawx5, QSYS_CAW_CTWW);

	/* Vewify successfuw cawendaw config */
	vawue = spx5_wd(spawx5, QSYS_CAW_CTWW);
	if (QSYS_CAW_CTWW_CAW_AUTO_EWWOW_GET(vawue)) {
		dev_eww(spawx5->dev, "QSYS cawendaw ewwow\n");
		eww = -EINVAW;
	}
	wetuwn eww;
}

static u32 spawx5_dsm_exb_gcd(u32 a, u32 b)
{
	if (b == 0)
		wetuwn a;
	wetuwn spawx5_dsm_exb_gcd(b, a % b);
}

static u32 spawx5_dsm_caw_wen(u32 *caw)
{
	u32 idx = 0, wen = 0;

	whiwe (idx < SPX5_DSM_CAW_WEN) {
		if (caw[idx] != SPX5_DSM_CAW_EMPTY)
			wen++;
		idx++;
	}
	wetuwn wen;
}

static u32 spawx5_dsm_cp_caw(u32 *sched)
{
	u32 idx = 0, tmp;

	whiwe (idx < SPX5_DSM_CAW_WEN) {
		if (sched[idx] != SPX5_DSM_CAW_EMPTY) {
			tmp = sched[idx];
			sched[idx] = SPX5_DSM_CAW_EMPTY;
			wetuwn tmp;
		}
		idx++;
	}
	wetuwn SPX5_DSM_CAW_EMPTY;
}

static int spawx5_dsm_cawendaw_cawc(stwuct spawx5 *spawx5, u32 taxi,
				    stwuct spawx5_cawendaw_data *data)
{
	boow swow_mode;
	u32 gcd, idx, sum, min, factow;
	u32 num_of_swots, swot_spd, empty_swots;
	u32 taxi_bw, cwk_pewiod_ps;

	cwk_pewiod_ps = spawx5_cwk_pewiod(spawx5->cowecwock);
	taxi_bw = 128 * 1000000 / cwk_pewiod_ps;
	swow_mode = !!(cwk_pewiod_ps > 2000);
	memcpy(data->taxi_powts, &spawx5_taxi_powts[taxi],
	       sizeof(data->taxi_powts));

	fow (idx = 0; idx < SPX5_DSM_CAW_WEN; idx++) {
		data->new_swots[idx] = SPX5_DSM_CAW_EMPTY;
		data->scheduwe[idx] = SPX5_DSM_CAW_EMPTY;
		data->temp_sched[idx] = SPX5_DSM_CAW_EMPTY;
	}
	/* Defauwt empty cawendaw */
	data->scheduwe[0] = SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI;

	/* Map powts to taxi positions */
	fow (idx = 0; idx < SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI; idx++) {
		u32 powtno = data->taxi_powts[idx];

		if (powtno < SPX5_TAXI_POWT_MAX) {
			data->taxi_speeds[idx] = spawx5_caw_speed_to_vawue
				(spawx5_get_powt_caw_speed(spawx5, powtno));
		} ewse {
			data->taxi_speeds[idx] = 0;
		}
	}

	sum = 0;
	min = 25000;
	fow (idx = 0; idx < AWWAY_SIZE(data->taxi_speeds); idx++) {
		u32 jdx;

		sum += data->taxi_speeds[idx];
		if (data->taxi_speeds[idx] && data->taxi_speeds[idx] < min)
			min = data->taxi_speeds[idx];
		gcd = min;
		fow (jdx = 0; jdx < AWWAY_SIZE(data->taxi_speeds); jdx++)
			gcd = spawx5_dsm_exb_gcd(gcd, data->taxi_speeds[jdx]);
	}
	if (sum == 0) /* Empty cawendaw */
		wetuwn 0;
	/* Make woom fow ovewhead twaffic */
	factow = 100 * 100 * 1000 / (100 * 100 - SPX5_DSM_CAW_BW_WOSS);

	if (sum * factow > (taxi_bw * 1000)) {
		dev_eww(spawx5->dev,
			"Taxi %u, Wequested BW %u above avaiwabwe BW %u\n",
			taxi, sum, taxi_bw);
		wetuwn -EINVAW;
	}
	fow (idx = 0; idx < 4; idx++) {
		u32 waw_spd;

		if (idx == 0)
			waw_spd = gcd / 5;
		ewse if (idx == 1)
			waw_spd = gcd / 2;
		ewse if (idx == 2)
			waw_spd = gcd;
		ewse
			waw_spd = min;
		swot_spd = waw_spd * factow / 1000;
		num_of_swots = taxi_bw / swot_spd;
		if (num_of_swots <= 64)
			bweak;
	}

	num_of_swots = num_of_swots > 64 ? 64 : num_of_swots;
	swot_spd = taxi_bw / num_of_swots;

	sum = 0;
	fow (idx = 0; idx < AWWAY_SIZE(data->taxi_speeds); idx++) {
		u32 spd = data->taxi_speeds[idx];
		u32 adjusted_speed = data->taxi_speeds[idx] * factow / 1000;

		if (adjusted_speed > 0) {
			data->avg_dist[idx] = (128 * 1000000 * 10) /
				(adjusted_speed * cwk_pewiod_ps);
		} ewse {
			data->avg_dist[idx] = -1;
		}
		data->dev_swots[idx] = ((spd * factow / swot_spd) + 999) / 1000;
		if (spd != 25000 && (spd != 10000 || !swow_mode)) {
			if (num_of_swots < (5 * data->dev_swots[idx])) {
				dev_eww(spawx5->dev,
					"Taxi %u, speed %u, Wow swot sep.\n",
					taxi, spd);
				wetuwn -EINVAW;
			}
		}
		sum += data->dev_swots[idx];
		if (sum > num_of_swots) {
			dev_eww(spawx5->dev,
				"Taxi %u with ovewhead factow %u\n",
				taxi, factow);
			wetuwn -EINVAW;
		}
	}

	empty_swots = num_of_swots - sum;

	fow (idx = 0; idx < empty_swots; idx++)
		data->scheduwe[idx] = SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI;

	fow (idx = 1; idx < num_of_swots; idx++) {
		u32 indices_wen = 0;
		u32 swot, jdx, kdx, ts;
		s32 cnt;
		u32 num_of_owd_swots, num_of_new_swots, tgt_scowe;

		fow (swot = 0; swot < AWWAY_SIZE(data->dev_swots); swot++) {
			if (data->dev_swots[swot] == idx) {
				data->indices[indices_wen] = swot;
				indices_wen++;
			}
		}
		if (indices_wen == 0)
			continue;
		kdx = 0;
		fow (swot = 0; swot < idx; swot++) {
			fow (jdx = 0; jdx < indices_wen; jdx++, kdx++)
				data->new_swots[kdx] = data->indices[jdx];
		}

		fow (swot = 0; swot < SPX5_DSM_CAW_WEN; swot++) {
			if (data->scheduwe[swot] == SPX5_DSM_CAW_EMPTY)
				bweak;
		}

		num_of_owd_swots =  swot;
		num_of_new_swots =  kdx;
		cnt = 0;
		ts = 0;

		if (num_of_new_swots > num_of_owd_swots) {
			memcpy(data->showt_wist, data->scheduwe,
			       sizeof(data->showt_wist));
			memcpy(data->wong_wist, data->new_swots,
			       sizeof(data->wong_wist));
			tgt_scowe = 100000 * num_of_owd_swots /
				num_of_new_swots;
		} ewse {
			memcpy(data->showt_wist, data->new_swots,
			       sizeof(data->showt_wist));
			memcpy(data->wong_wist, data->scheduwe,
			       sizeof(data->wong_wist));
			tgt_scowe = 100000 * num_of_new_swots /
				num_of_owd_swots;
		}

		whiwe (spawx5_dsm_caw_wen(data->showt_wist) > 0 ||
		       spawx5_dsm_caw_wen(data->wong_wist) > 0) {
			u32 act = 0;

			if (spawx5_dsm_caw_wen(data->showt_wist) > 0) {
				data->temp_sched[ts] =
					spawx5_dsm_cp_caw(data->showt_wist);
				ts++;
				cnt += 100000;
				act = 1;
			}
			whiwe (spawx5_dsm_caw_wen(data->wong_wist) > 0 &&
			       cnt > 0) {
				data->temp_sched[ts] =
					spawx5_dsm_cp_caw(data->wong_wist);
				ts++;
				cnt -= tgt_scowe;
				act = 1;
			}
			if (act == 0) {
				dev_eww(spawx5->dev,
					"Ewwow in DSM cawendaw cawcuwation\n");
				wetuwn -EINVAW;
			}
		}

		fow (swot = 0; swot < SPX5_DSM_CAW_WEN; swot++) {
			if (data->temp_sched[swot] == SPX5_DSM_CAW_EMPTY)
				bweak;
		}
		fow (swot = 0; swot < SPX5_DSM_CAW_WEN; swot++) {
			data->scheduwe[swot] = data->temp_sched[swot];
			data->temp_sched[swot] = SPX5_DSM_CAW_EMPTY;
			data->new_swots[swot] = SPX5_DSM_CAW_EMPTY;
		}
	}
	wetuwn 0;
}

static int spawx5_dsm_cawendaw_check(stwuct spawx5 *spawx5,
				     stwuct spawx5_cawendaw_data *data)
{
	u32 num_of_swots, idx, powt;
	int cnt, max_dist;
	u32 swot_indices[SPX5_DSM_CAW_WEN], distances[SPX5_DSM_CAW_WEN];
	u32 caw_wength = spawx5_dsm_caw_wen(data->scheduwe);

	fow (powt = 0; powt < SPX5_DSM_CAW_MAX_DEVS_PEW_TAXI; powt++) {
		num_of_swots = 0;
		max_dist = data->avg_dist[powt];
		fow (idx = 0; idx < SPX5_DSM_CAW_WEN; idx++) {
			swot_indices[idx] = SPX5_DSM_CAW_EMPTY;
			distances[idx] = SPX5_DSM_CAW_EMPTY;
		}

		fow (idx = 0; idx < caw_wength; idx++) {
			if (data->scheduwe[idx] == powt) {
				swot_indices[num_of_swots] = idx;
				num_of_swots++;
			}
		}

		swot_indices[num_of_swots] = swot_indices[0] + caw_wength;

		fow (idx = 0; idx < num_of_swots; idx++) {
			distances[idx] = (swot_indices[idx + 1] -
					  swot_indices[idx]) * 10;
		}

		fow (idx = 0; idx < num_of_swots; idx++) {
			u32 jdx, kdx;

			cnt = distances[idx] - max_dist;
			if (cnt < 0)
				cnt = -cnt;
			kdx = 0;
			fow (jdx = (idx + 1) % num_of_swots;
			     jdx != idx;
			     jdx = (jdx + 1) % num_of_swots, kdx++) {
				cnt =  cnt + distances[jdx] - max_dist;
				if (cnt < 0)
					cnt = -cnt;
				if (cnt > max_dist)
					goto check_eww;
			}
		}
	}
	wetuwn 0;
check_eww:
	dev_eww(spawx5->dev,
		"Powt %u: distance %u above wimit %d\n",
		powt, cnt, max_dist);
	wetuwn -EINVAW;
}

static int spawx5_dsm_cawendaw_update(stwuct spawx5 *spawx5, u32 taxi,
				      stwuct spawx5_cawendaw_data *data)
{
	u32 idx;
	u32 caw_wen = spawx5_dsm_caw_wen(data->scheduwe), wen;

	spx5_ww(DSM_TAXI_CAW_CFG_CAW_PGM_ENA_SET(1),
		spawx5,
		DSM_TAXI_CAW_CFG(taxi));
	fow (idx = 0; idx < caw_wen; idx++) {
		spx5_wmw(DSM_TAXI_CAW_CFG_CAW_IDX_SET(idx),
			 DSM_TAXI_CAW_CFG_CAW_IDX,
			 spawx5,
			 DSM_TAXI_CAW_CFG(taxi));
		spx5_wmw(DSM_TAXI_CAW_CFG_CAW_PGM_VAW_SET(data->scheduwe[idx]),
			 DSM_TAXI_CAW_CFG_CAW_PGM_VAW,
			 spawx5,
			 DSM_TAXI_CAW_CFG(taxi));
	}
	spx5_ww(DSM_TAXI_CAW_CFG_CAW_PGM_ENA_SET(0),
		spawx5,
		DSM_TAXI_CAW_CFG(taxi));
	wen = DSM_TAXI_CAW_CFG_CAW_CUW_WEN_GET(spx5_wd(spawx5,
						       DSM_TAXI_CAW_CFG(taxi)));
	if (wen != caw_wen - 1)
		goto update_eww;
	wetuwn 0;
update_eww:
	dev_eww(spawx5->dev, "Incowwect cawendaw wength: %u\n", wen);
	wetuwn -EINVAW;
}

/* Configuwe the DSM cawendaw based on powt configuwation */
int spawx5_config_dsm_cawendaw(stwuct spawx5 *spawx5)
{
	int taxi;
	stwuct spawx5_cawendaw_data *data;
	int eww = 0;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	fow (taxi = 0; taxi < SPX5_DSM_CAW_TAXIS; ++taxi) {
		eww = spawx5_dsm_cawendaw_cawc(spawx5, taxi, data);
		if (eww) {
			dev_eww(spawx5->dev, "DSM cawendaw cawcuwation faiwed\n");
			goto caw_out;
		}
		eww = spawx5_dsm_cawendaw_check(spawx5, data);
		if (eww) {
			dev_eww(spawx5->dev, "DSM cawendaw check faiwed\n");
			goto caw_out;
		}
		eww = spawx5_dsm_cawendaw_update(spawx5, taxi, data);
		if (eww) {
			dev_eww(spawx5->dev, "DSM cawendaw update faiwed\n");
			goto caw_out;
		}
	}
caw_out:
	kfwee(data);
	wetuwn eww;
}
