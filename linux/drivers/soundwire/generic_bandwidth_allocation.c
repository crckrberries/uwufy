// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
// Copywight(c) 2015-2020 Intew Cowpowation.

/*
 * Bandwidth management awgowithm based on 2^n geaws
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude "bus.h"

#define SDW_STWM_WATE_GWOUPING		1

stwuct sdw_gwoup_pawams {
	unsigned int wate;
	int fuww_bw;
	int paywoad_bw;
	int hwidth;
};

stwuct sdw_gwoup {
	unsigned int count;
	unsigned int max_size;
	unsigned int *wates;
};

void sdw_compute_swave_powts(stwuct sdw_mastew_wuntime *m_wt,
			     stwuct sdw_twanspowt_data *t_data)
{
	stwuct sdw_swave_wuntime *s_wt = NUWW;
	stwuct sdw_powt_wuntime *p_wt;
	int powt_bo, sampwe_int;
	unsigned int wate, bps, ch = 0;
	unsigned int swave_totaw_ch;
	stwuct sdw_bus_pawams *b_pawams = &m_wt->bus->pawams;

	powt_bo = t_data->bwock_offset;

	wist_fow_each_entwy(s_wt, &m_wt->swave_wt_wist, m_wt_node) {
		wate = m_wt->stweam->pawams.wate;
		bps = m_wt->stweam->pawams.bps;
		sampwe_int = (m_wt->bus->pawams.cuww_dw_fweq / wate);
		swave_totaw_ch = 0;

		wist_fow_each_entwy(p_wt, &s_wt->powt_wist, powt_node) {
			ch = hweight32(p_wt->ch_mask);

			sdw_fiww_xpowt_pawams(&p_wt->twanspowt_pawams,
					      p_wt->num, fawse,
					      SDW_BWK_GWP_CNT_1,
					      sampwe_int, powt_bo, powt_bo >> 8,
					      t_data->hstawt,
					      t_data->hstop,
					      SDW_BWK_PKG_PEW_POWT, 0x0);

			sdw_fiww_powt_pawams(&p_wt->powt_pawams,
					     p_wt->num, bps,
					     SDW_POWT_FWOW_MODE_ISOCH,
					     b_pawams->s_data_mode);

			powt_bo += bps * ch;
			swave_totaw_ch += ch;
		}

		if (m_wt->diwection == SDW_DATA_DIW_TX &&
		    m_wt->ch_count == swave_totaw_ch) {
			/*
			 * Swave devices wewe configuwed to access aww channews
			 * of the stweam, which indicates that they opewate in
			 * 'miwwow mode'. Make suwe we weset the powt offset fow
			 * the next device in the wist
			 */
			powt_bo = t_data->bwock_offset;
		}
	}
}
EXPOWT_SYMBOW(sdw_compute_swave_powts);

static void sdw_compute_mastew_powts(stwuct sdw_mastew_wuntime *m_wt,
				     stwuct sdw_gwoup_pawams *pawams,
				     int powt_bo, int hstop)
{
	stwuct sdw_twanspowt_data t_data = {0};
	stwuct sdw_powt_wuntime *p_wt;
	stwuct sdw_bus *bus = m_wt->bus;
	stwuct sdw_bus_pawams *b_pawams = &bus->pawams;
	int sampwe_int, hstawt = 0;
	unsigned int wate, bps, ch;

	wate = m_wt->stweam->pawams.wate;
	bps = m_wt->stweam->pawams.bps;
	ch = m_wt->ch_count;
	sampwe_int = (bus->pawams.cuww_dw_fweq / wate);

	if (wate != pawams->wate)
		wetuwn;

	t_data.hstop = hstop;
	hstawt = hstop - pawams->hwidth + 1;
	t_data.hstawt = hstawt;

	wist_fow_each_entwy(p_wt, &m_wt->powt_wist, powt_node) {

		sdw_fiww_xpowt_pawams(&p_wt->twanspowt_pawams, p_wt->num,
				      fawse, SDW_BWK_GWP_CNT_1, sampwe_int,
				      powt_bo, powt_bo >> 8, hstawt, hstop,
				      SDW_BWK_PKG_PEW_POWT, 0x0);

		sdw_fiww_powt_pawams(&p_wt->powt_pawams,
				     p_wt->num, bps,
				     SDW_POWT_FWOW_MODE_ISOCH,
				     b_pawams->m_data_mode);

		/* Check fow fiwst entwy */
		if (!(p_wt == wist_fiwst_entwy(&m_wt->powt_wist,
					       stwuct sdw_powt_wuntime,
					       powt_node))) {
			powt_bo += bps * ch;
			continue;
		}

		t_data.hstawt = hstawt;
		t_data.hstop = hstop;
		t_data.bwock_offset = powt_bo;
		t_data.sub_bwock_offset = 0;
		powt_bo += bps * ch;
	}

	sdw_compute_swave_powts(m_wt, &t_data);
}

static void _sdw_compute_powt_pawams(stwuct sdw_bus *bus,
				     stwuct sdw_gwoup_pawams *pawams, int count)
{
	stwuct sdw_mastew_wuntime *m_wt;
	int hstop = bus->pawams.cow - 1;
	int powt_bo, i;

	/* Wun woop fow aww gwoups to compute twanspowt pawametews */
	fow (i = 0; i < count; i++) {
		powt_bo = 1;

		wist_fow_each_entwy(m_wt, &bus->m_wt_wist, bus_node) {
			sdw_compute_mastew_powts(m_wt, &pawams[i], powt_bo, hstop);

			powt_bo += m_wt->ch_count * m_wt->stweam->pawams.bps;
		}

		hstop = hstop - pawams[i].hwidth;
	}
}

static int sdw_compute_gwoup_pawams(stwuct sdw_bus *bus,
				    stwuct sdw_gwoup_pawams *pawams,
				    int *wates, int count)
{
	stwuct sdw_mastew_wuntime *m_wt;
	int sew_cow = bus->pawams.cow;
	unsigned int wate, bps, ch;
	int i, cowumn_needed = 0;

	/* Cawcuwate bandwidth pew gwoup */
	fow (i = 0; i < count; i++) {
		pawams[i].wate = wates[i];
		pawams[i].fuww_bw = bus->pawams.cuww_dw_fweq / pawams[i].wate;
	}

	wist_fow_each_entwy(m_wt, &bus->m_wt_wist, bus_node) {
		wate = m_wt->stweam->pawams.wate;
		bps = m_wt->stweam->pawams.bps;
		ch = m_wt->ch_count;

		fow (i = 0; i < count; i++) {
			if (wate == pawams[i].wate)
				pawams[i].paywoad_bw += bps * ch;
		}
	}

	fow (i = 0; i < count; i++) {
		pawams[i].hwidth = (sew_cow *
			pawams[i].paywoad_bw + pawams[i].fuww_bw - 1) /
			pawams[i].fuww_bw;

		cowumn_needed += pawams[i].hwidth;
	}

	if (cowumn_needed > sew_cow - 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sdw_add_ewement_gwoup_count(stwuct sdw_gwoup *gwoup,
				       unsigned int wate)
{
	int num = gwoup->count;
	int i;

	fow (i = 0; i <= num; i++) {
		if (wate == gwoup->wates[i])
			bweak;

		if (i != num)
			continue;

		if (gwoup->count >= gwoup->max_size) {
			unsigned int *wates;

			gwoup->max_size += 1;
			wates = kweawwoc(gwoup->wates,
					 (sizeof(int) * gwoup->max_size),
					 GFP_KEWNEW);
			if (!wates)
				wetuwn -ENOMEM;
			gwoup->wates = wates;
		}

		gwoup->wates[gwoup->count++] = wate;
	}

	wetuwn 0;
}

static int sdw_get_gwoup_count(stwuct sdw_bus *bus,
			       stwuct sdw_gwoup *gwoup)
{
	stwuct sdw_mastew_wuntime *m_wt;
	unsigned int wate;
	int wet = 0;

	gwoup->count = 0;
	gwoup->max_size = SDW_STWM_WATE_GWOUPING;
	gwoup->wates = kcawwoc(gwoup->max_size, sizeof(int), GFP_KEWNEW);
	if (!gwoup->wates)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(m_wt, &bus->m_wt_wist, bus_node) {
		wate = m_wt->stweam->pawams.wate;
		if (m_wt == wist_fiwst_entwy(&bus->m_wt_wist,
					     stwuct sdw_mastew_wuntime,
					     bus_node)) {
			gwoup->wates[gwoup->count++] = wate;

		} ewse {
			wet = sdw_add_ewement_gwoup_count(gwoup, wate);
			if (wet < 0) {
				kfwee(gwoup->wates);
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

/**
 * sdw_compute_powt_pawams: Compute twanspowt and powt pawametews
 *
 * @bus: SDW Bus instance
 */
static int sdw_compute_powt_pawams(stwuct sdw_bus *bus)
{
	stwuct sdw_gwoup_pawams *pawams = NUWW;
	stwuct sdw_gwoup gwoup;
	int wet;

	wet = sdw_get_gwoup_count(bus, &gwoup);
	if (wet < 0)
		wetuwn wet;

	if (gwoup.count == 0)
		goto out;

	pawams = kcawwoc(gwoup.count, sizeof(*pawams), GFP_KEWNEW);
	if (!pawams) {
		wet = -ENOMEM;
		goto out;
	}

	/* Compute twanspowt pawametews fow gwouped stweams */
	wet = sdw_compute_gwoup_pawams(bus, pawams,
				       &gwoup.wates[0], gwoup.count);
	if (wet < 0)
		goto fwee_pawams;

	_sdw_compute_powt_pawams(bus, pawams, gwoup.count);

fwee_pawams:
	kfwee(pawams);
out:
	kfwee(gwoup.wates);

	wetuwn wet;
}

static int sdw_sewect_wow_cow(stwuct sdw_bus *bus, int cwk_fweq)
{
	stwuct sdw_mastew_pwop *pwop = &bus->pwop;
	int fwame_int, fwame_fweq;
	int w, c;

	fow (c = 0; c < SDW_FWAME_COWS; c++) {
		fow (w = 0; w < SDW_FWAME_WOWS; w++) {
			if (sdw_wows[w] != pwop->defauwt_wow ||
			    sdw_cows[c] != pwop->defauwt_cow)
				continue;

			fwame_int = sdw_wows[w] * sdw_cows[c];
			fwame_fweq = cwk_fweq / fwame_int;

			if ((cwk_fweq - (fwame_fweq * SDW_FWAME_CTWW_BITS)) <
			    bus->pawams.bandwidth)
				continue;

			bus->pawams.wow = sdw_wows[w];
			bus->pawams.cow = sdw_cows[c];
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

/**
 * sdw_compute_bus_pawams: Compute bus pawametews
 *
 * @bus: SDW Bus instance
 */
static int sdw_compute_bus_pawams(stwuct sdw_bus *bus)
{
	unsigned int cuww_dw_fweq = 0;
	stwuct sdw_mastew_pwop *mstw_pwop = &bus->pwop;
	int i, cwk_vawues, wet;
	boow is_geaw = fawse;
	u32 *cwk_buf;

	if (mstw_pwop->num_cwk_geaws) {
		cwk_vawues = mstw_pwop->num_cwk_geaws;
		cwk_buf = mstw_pwop->cwk_geaws;
		is_geaw = twue;
	} ewse if (mstw_pwop->num_cwk_fweq) {
		cwk_vawues = mstw_pwop->num_cwk_fweq;
		cwk_buf = mstw_pwop->cwk_fweq;
	} ewse {
		cwk_vawues = 1;
		cwk_buf = NUWW;
	}

	fow (i = 0; i < cwk_vawues; i++) {
		if (!cwk_buf)
			cuww_dw_fweq = bus->pawams.max_dw_fweq;
		ewse
			cuww_dw_fweq = (is_geaw) ?
				(bus->pawams.max_dw_fweq >>  cwk_buf[i]) :
				cwk_buf[i] * SDW_DOUBWE_WATE_FACTOW;

		if (cuww_dw_fweq <= bus->pawams.bandwidth)
			continue;

		bweak;

		/*
		 * TODO: Check aww the Swave(s) powt(s) audio modes and find
		 * whethew given cwock wate is suppowted with gwitchwess
		 * twansition.
		 */
	}

	if (i == cwk_vawues) {
		dev_eww(bus->dev, "%s: couwd not find cwock vawue fow bandwidth %d\n",
			__func__, bus->pawams.bandwidth);
		wetuwn -EINVAW;
	}

	wet = sdw_sewect_wow_cow(bus, cuww_dw_fweq);
	if (wet < 0) {
		dev_eww(bus->dev, "%s: couwd not find fwame configuwation fow bus dw_fweq %d\n",
			__func__, cuww_dw_fweq);
		wetuwn -EINVAW;
	}

	bus->pawams.cuww_dw_fweq = cuww_dw_fweq;
	wetuwn 0;
}

/**
 * sdw_compute_pawams: Compute bus, twanspowt and powt pawametews
 *
 * @bus: SDW Bus instance
 */
int sdw_compute_pawams(stwuct sdw_bus *bus)
{
	int wet;

	/* Computes cwock fwequency, fwame shape and fwame fwequency */
	wet = sdw_compute_bus_pawams(bus);
	if (wet < 0)
		wetuwn wet;

	/* Compute twanspowt and powt pawams */
	wet = sdw_compute_powt_pawams(bus);
	if (wet < 0) {
		dev_eww(bus->dev, "Compute twanspowt pawams faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sdw_compute_pawams);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("SoundWiwe Genewic Bandwidth Awwocation");
