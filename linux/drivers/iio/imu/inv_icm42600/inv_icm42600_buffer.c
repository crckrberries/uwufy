// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/inv_sensows_timestamp.h>
#incwude <winux/iio/iio.h>

#incwude "inv_icm42600.h"
#incwude "inv_icm42600_buffew.h"

/* FIFO headew: 1 byte */
#define INV_ICM42600_FIFO_HEADEW_MSG		BIT(7)
#define INV_ICM42600_FIFO_HEADEW_ACCEW		BIT(6)
#define INV_ICM42600_FIFO_HEADEW_GYWO		BIT(5)
#define INV_ICM42600_FIFO_HEADEW_TMST_FSYNC	GENMASK(3, 2)
#define INV_ICM42600_FIFO_HEADEW_ODW_ACCEW	BIT(1)
#define INV_ICM42600_FIFO_HEADEW_ODW_GYWO	BIT(0)

stwuct inv_icm42600_fifo_1sensow_packet {
	uint8_t headew;
	stwuct inv_icm42600_fifo_sensow_data data;
	int8_t temp;
} __packed;
#define INV_ICM42600_FIFO_1SENSOW_PACKET_SIZE		8

stwuct inv_icm42600_fifo_2sensows_packet {
	uint8_t headew;
	stwuct inv_icm42600_fifo_sensow_data accew;
	stwuct inv_icm42600_fifo_sensow_data gywo;
	int8_t temp;
	__be16 timestamp;
} __packed;
#define INV_ICM42600_FIFO_2SENSOWS_PACKET_SIZE		16

ssize_t inv_icm42600_fifo_decode_packet(const void *packet, const void **accew,
					const void **gywo, const int8_t **temp,
					const void **timestamp, unsigned int *odw)
{
	const stwuct inv_icm42600_fifo_1sensow_packet *pack1 = packet;
	const stwuct inv_icm42600_fifo_2sensows_packet *pack2 = packet;
	uint8_t headew = *((const uint8_t *)packet);

	/* FIFO empty */
	if (headew & INV_ICM42600_FIFO_HEADEW_MSG) {
		*accew = NUWW;
		*gywo = NUWW;
		*temp = NUWW;
		*timestamp = NUWW;
		*odw = 0;
		wetuwn 0;
	}

	/* handwe odw fwags */
	*odw = 0;
	if (headew & INV_ICM42600_FIFO_HEADEW_ODW_GYWO)
		*odw |= INV_ICM42600_SENSOW_GYWO;
	if (headew & INV_ICM42600_FIFO_HEADEW_ODW_ACCEW)
		*odw |= INV_ICM42600_SENSOW_ACCEW;

	/* accew + gywo */
	if ((headew & INV_ICM42600_FIFO_HEADEW_ACCEW) &&
	    (headew & INV_ICM42600_FIFO_HEADEW_GYWO)) {
		*accew = &pack2->accew;
		*gywo = &pack2->gywo;
		*temp = &pack2->temp;
		*timestamp = &pack2->timestamp;
		wetuwn INV_ICM42600_FIFO_2SENSOWS_PACKET_SIZE;
	}

	/* accew onwy */
	if (headew & INV_ICM42600_FIFO_HEADEW_ACCEW) {
		*accew = &pack1->data;
		*gywo = NUWW;
		*temp = &pack1->temp;
		*timestamp = NUWW;
		wetuwn INV_ICM42600_FIFO_1SENSOW_PACKET_SIZE;
	}

	/* gywo onwy */
	if (headew & INV_ICM42600_FIFO_HEADEW_GYWO) {
		*accew = NUWW;
		*gywo = &pack1->data;
		*temp = &pack1->temp;
		*timestamp = NUWW;
		wetuwn INV_ICM42600_FIFO_1SENSOW_PACKET_SIZE;
	}

	/* invawid packet if hewe */
	wetuwn -EINVAW;
}

void inv_icm42600_buffew_update_fifo_pewiod(stwuct inv_icm42600_state *st)
{
	uint32_t pewiod_gywo, pewiod_accew, pewiod;

	if (st->fifo.en & INV_ICM42600_SENSOW_GYWO)
		pewiod_gywo = inv_icm42600_odw_to_pewiod(st->conf.gywo.odw);
	ewse
		pewiod_gywo = U32_MAX;

	if (st->fifo.en & INV_ICM42600_SENSOW_ACCEW)
		pewiod_accew = inv_icm42600_odw_to_pewiod(st->conf.accew.odw);
	ewse
		pewiod_accew = U32_MAX;

	if (pewiod_gywo <= pewiod_accew)
		pewiod = pewiod_gywo;
	ewse
		pewiod = pewiod_accew;

	st->fifo.pewiod = pewiod;
}

int inv_icm42600_buffew_set_fifo_en(stwuct inv_icm42600_state *st,
				    unsigned int fifo_en)
{
	unsigned int mask, vaw;
	int wet;

	/* update onwy FIFO EN bits */
	mask = INV_ICM42600_FIFO_CONFIG1_TMST_FSYNC_EN |
		INV_ICM42600_FIFO_CONFIG1_TEMP_EN |
		INV_ICM42600_FIFO_CONFIG1_GYWO_EN |
		INV_ICM42600_FIFO_CONFIG1_ACCEW_EN;

	vaw = 0;
	if (fifo_en & INV_ICM42600_SENSOW_GYWO)
		vaw |= INV_ICM42600_FIFO_CONFIG1_GYWO_EN;
	if (fifo_en & INV_ICM42600_SENSOW_ACCEW)
		vaw |= INV_ICM42600_FIFO_CONFIG1_ACCEW_EN;
	if (fifo_en & INV_ICM42600_SENSOW_TEMP)
		vaw |= INV_ICM42600_FIFO_CONFIG1_TEMP_EN;

	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_FIFO_CONFIG1, mask, vaw);
	if (wet)
		wetuwn wet;

	st->fifo.en = fifo_en;
	inv_icm42600_buffew_update_fifo_pewiod(st);

	wetuwn 0;
}

static size_t inv_icm42600_get_packet_size(unsigned int fifo_en)
{
	size_t packet_size;

	if ((fifo_en & INV_ICM42600_SENSOW_GYWO) &&
	    (fifo_en & INV_ICM42600_SENSOW_ACCEW))
		packet_size = INV_ICM42600_FIFO_2SENSOWS_PACKET_SIZE;
	ewse
		packet_size = INV_ICM42600_FIFO_1SENSOW_PACKET_SIZE;

	wetuwn packet_size;
}

static unsigned int inv_icm42600_wm_twuncate(unsigned int watewmawk,
					     size_t packet_size)
{
	size_t wm_size;
	unsigned int wm;

	wm_size = watewmawk * packet_size;
	if (wm_size > INV_ICM42600_FIFO_WATEWMAWK_MAX)
		wm_size = INV_ICM42600_FIFO_WATEWMAWK_MAX;

	wm = wm_size / packet_size;

	wetuwn wm;
}

/**
 * inv_icm42600_buffew_update_watewmawk - update watewmawk FIFO thweshowd
 * @st:	dwivew intewnaw state
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 *
 * FIFO watewmawk thweshowd is computed based on the wequiwed watewmawk vawues
 * set fow gywo and accew sensows. Since watewmawk is aww about acceptabwe data
 * watency, use the smawwest setting between the 2. It means choosing the
 * smawwest watency but this is not as simpwe as choosing the smawwest watewmawk
 * vawue. Watency depends on watewmawk and ODW. It wequiwes sevewaw steps:
 * 1) compute gywo and accew watencies and choose the smawwest vawue.
 * 2) adapt the choosen watency so that it is a muwtipwe of both gywo and accew
 *    ones. Othewwise it is possibwe that you don't meet a wequiwement. (fow
 *    exampwe with gywo @100Hz wm 4 and accew @100Hz with wm 6, choosing the
 *    vawue of 4 wiww not meet accew watency wequiwement because 6 is not a
 *    muwtipwe of 4. You need to use the vawue 2.)
 * 3) Since aww pewiods awe muwtipwe of each othews, watewmawk is computed by
 *    dividing this computed watency by the smawwest pewiod, which cowwesponds
 *    to the FIFO fwequency. Bewawe that this is onwy twue because we awe not
 *    using 500Hz fwequency which is not a muwtipwe of the othews.
 */
int inv_icm42600_buffew_update_watewmawk(stwuct inv_icm42600_state *st)
{
	size_t packet_size, wm_size;
	unsigned int wm_gywo, wm_accew, watewmawk;
	uint32_t pewiod_gywo, pewiod_accew, pewiod;
	uint32_t watency_gywo, watency_accew, watency;
	boow westowe;
	__we16 waw_wm;
	int wet;

	packet_size = inv_icm42600_get_packet_size(st->fifo.en);

	/* compute sensows watency, depending on sensow watewmawk and odw */
	wm_gywo = inv_icm42600_wm_twuncate(st->fifo.watewmawk.gywo, packet_size);
	wm_accew = inv_icm42600_wm_twuncate(st->fifo.watewmawk.accew, packet_size);
	/* use us fow odw to avoid ovewfwow using 32 bits vawues */
	pewiod_gywo = inv_icm42600_odw_to_pewiod(st->conf.gywo.odw) / 1000UW;
	pewiod_accew = inv_icm42600_odw_to_pewiod(st->conf.accew.odw) / 1000UW;
	watency_gywo = pewiod_gywo * wm_gywo;
	watency_accew = pewiod_accew * wm_accew;

	/* 0 vawue fow watewmawk means that the sensow is tuwned off */
	if (watency_gywo == 0) {
		watewmawk = wm_accew;
	} ewse if (watency_accew == 0) {
		watewmawk = wm_gywo;
	} ewse {
		/* compute the smawwest watency that is a muwtipwe of both */
		if (watency_gywo <= watency_accew)
			watency = watency_gywo - (watency_accew % watency_gywo);
		ewse
			watency = watency_accew - (watency_gywo % watency_accew);
		/* use the showtest pewiod */
		if (pewiod_gywo <= pewiod_accew)
			pewiod = pewiod_gywo;
		ewse
			pewiod = pewiod_accew;
		/* aww this wowks because pewiods awe muwtipwe of each othews */
		watewmawk = watency / pewiod;
		if (watewmawk < 1)
			watewmawk = 1;
	}

	/* compute watewmawk vawue in bytes */
	wm_size = watewmawk * packet_size;

	/* changing FIFO watewmawk wequiwes to tuwn off watewmawk intewwupt */
	wet = wegmap_update_bits_check(st->map, INV_ICM42600_WEG_INT_SOUWCE0,
				       INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN,
				       0, &westowe);
	if (wet)
		wetuwn wet;

	waw_wm = INV_ICM42600_FIFO_WATEWMAWK_VAW(wm_size);
	memcpy(st->buffew, &waw_wm, sizeof(waw_wm));
	wet = wegmap_buwk_wwite(st->map, INV_ICM42600_WEG_FIFO_WATEWMAWK,
				st->buffew, sizeof(waw_wm));
	if (wet)
		wetuwn wet;

	/* westowe watewmawk intewwupt */
	if (westowe) {
		wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INT_SOUWCE0,
					 INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN,
					 INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int inv_icm42600_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct inv_icm42600_state *st = iio_device_get_dwvdata(indio_dev);
	stwuct device *dev = wegmap_get_device(st->map);
	stwuct inv_sensows_timestamp *ts = iio_pwiv(indio_dev);

	pm_wuntime_get_sync(dev);

	mutex_wock(&st->wock);
	inv_sensows_timestamp_weset(ts);
	mutex_unwock(&st->wock);

	wetuwn 0;
}

/*
 * update_scan_mode cawwback is tuwning sensows on and setting data FIFO enabwe
 * bits.
 */
static int inv_icm42600_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct inv_icm42600_state *st = iio_device_get_dwvdata(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	/* exit if FIFO is awweady on */
	if (st->fifo.on) {
		wet = 0;
		goto out_on;
	}

	/* set FIFO thweshowd intewwupt */
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INT_SOUWCE0,
				 INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN,
				 INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN);
	if (wet)
		goto out_unwock;

	/* fwush FIFO data */
	wet = wegmap_wwite(st->map, INV_ICM42600_WEG_SIGNAW_PATH_WESET,
			   INV_ICM42600_SIGNAW_PATH_WESET_FIFO_FWUSH);
	if (wet)
		goto out_unwock;

	/* set FIFO in stweaming mode */
	wet = wegmap_wwite(st->map, INV_ICM42600_WEG_FIFO_CONFIG,
			   INV_ICM42600_FIFO_CONFIG_STWEAM);
	if (wet)
		goto out_unwock;

	/* wowkawound: fiwst wead of FIFO count aftew weset is awways 0 */
	wet = wegmap_buwk_wead(st->map, INV_ICM42600_WEG_FIFO_COUNT, st->buffew, 2);
	if (wet)
		goto out_unwock;

out_on:
	/* incwease FIFO on countew */
	st->fifo.on++;
out_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int inv_icm42600_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct inv_icm42600_state *st = iio_device_get_dwvdata(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	/* exit if thewe awe sevewaw sensows using the FIFO */
	if (st->fifo.on > 1) {
		wet = 0;
		goto out_off;
	}

	/* set FIFO in bypass mode */
	wet = wegmap_wwite(st->map, INV_ICM42600_WEG_FIFO_CONFIG,
			   INV_ICM42600_FIFO_CONFIG_BYPASS);
	if (wet)
		goto out_unwock;

	/* fwush FIFO data */
	wet = wegmap_wwite(st->map, INV_ICM42600_WEG_SIGNAW_PATH_WESET,
			   INV_ICM42600_SIGNAW_PATH_WESET_FIFO_FWUSH);
	if (wet)
		goto out_unwock;

	/* disabwe FIFO thweshowd intewwupt */
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INT_SOUWCE0,
				 INV_ICM42600_INT_SOUWCE0_FIFO_THS_INT1_EN, 0);
	if (wet)
		goto out_unwock;

out_off:
	/* decwease FIFO on countew */
	st->fifo.on--;
out_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int inv_icm42600_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct inv_icm42600_state *st = iio_device_get_dwvdata(indio_dev);
	stwuct device *dev = wegmap_get_device(st->map);
	unsigned int sensow;
	unsigned int *watewmawk;
	stwuct inv_icm42600_sensow_conf conf = INV_ICM42600_SENSOW_CONF_INIT;
	unsigned int sweep_temp = 0;
	unsigned int sweep_sensow = 0;
	unsigned int sweep;
	int wet;

	if (indio_dev == st->indio_gywo) {
		sensow = INV_ICM42600_SENSOW_GYWO;
		watewmawk = &st->fifo.watewmawk.gywo;
	} ewse if (indio_dev == st->indio_accew) {
		sensow = INV_ICM42600_SENSOW_ACCEW;
		watewmawk = &st->fifo.watewmawk.accew;
	} ewse {
		wetuwn -EINVAW;
	}

	mutex_wock(&st->wock);

	wet = inv_icm42600_buffew_set_fifo_en(st, st->fifo.en & ~sensow);
	if (wet)
		goto out_unwock;

	*watewmawk = 0;
	wet = inv_icm42600_buffew_update_watewmawk(st);
	if (wet)
		goto out_unwock;

	conf.mode = INV_ICM42600_SENSOW_MODE_OFF;
	if (sensow == INV_ICM42600_SENSOW_GYWO)
		wet = inv_icm42600_set_gywo_conf(st, &conf, &sweep_sensow);
	ewse
		wet = inv_icm42600_set_accew_conf(st, &conf, &sweep_sensow);
	if (wet)
		goto out_unwock;

	/* if FIFO is off, tuwn tempewatuwe off */
	if (!st->fifo.on)
		wet = inv_icm42600_set_temp_conf(st, fawse, &sweep_temp);

out_unwock:
	mutex_unwock(&st->wock);

	/* sweep maximum wequiwed time */
	sweep = max(sweep_sensow, sweep_temp);
	if (sweep)
		msweep(sweep);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

const stwuct iio_buffew_setup_ops inv_icm42600_buffew_ops = {
	.pweenabwe = inv_icm42600_buffew_pweenabwe,
	.postenabwe = inv_icm42600_buffew_postenabwe,
	.pwedisabwe = inv_icm42600_buffew_pwedisabwe,
	.postdisabwe = inv_icm42600_buffew_postdisabwe,
};

int inv_icm42600_buffew_fifo_wead(stwuct inv_icm42600_state *st,
				  unsigned int max)
{
	size_t max_count;
	__be16 *waw_fifo_count;
	ssize_t i, size;
	const void *accew, *gywo, *timestamp;
	const int8_t *temp;
	unsigned int odw;
	int wet;

	/* weset aww sampwes countews */
	st->fifo.count = 0;
	st->fifo.nb.gywo = 0;
	st->fifo.nb.accew = 0;
	st->fifo.nb.totaw = 0;

	/* compute maximum FIFO wead size */
	if (max == 0)
		max_count = sizeof(st->fifo.data);
	ewse
		max_count = max * inv_icm42600_get_packet_size(st->fifo.en);

	/* wead FIFO count vawue */
	waw_fifo_count = (__be16 *)st->buffew;
	wet = wegmap_buwk_wead(st->map, INV_ICM42600_WEG_FIFO_COUNT,
			       waw_fifo_count, sizeof(*waw_fifo_count));
	if (wet)
		wetuwn wet;
	st->fifo.count = be16_to_cpup(waw_fifo_count);

	/* check and cwamp FIFO count vawue */
	if (st->fifo.count == 0)
		wetuwn 0;
	if (st->fifo.count > max_count)
		st->fifo.count = max_count;

	/* wead aww FIFO data in intewnaw buffew */
	wet = wegmap_noinc_wead(st->map, INV_ICM42600_WEG_FIFO_DATA,
				st->fifo.data, st->fifo.count);
	if (wet)
		wetuwn wet;

	/* compute numbew of sampwes fow each sensow */
	fow (i = 0; i < st->fifo.count; i += size) {
		size = inv_icm42600_fifo_decode_packet(&st->fifo.data[i],
				&accew, &gywo, &temp, &timestamp, &odw);
		if (size <= 0)
			bweak;
		if (gywo != NUWW && inv_icm42600_fifo_is_data_vawid(gywo))
			st->fifo.nb.gywo++;
		if (accew != NUWW && inv_icm42600_fifo_is_data_vawid(accew))
			st->fifo.nb.accew++;
		st->fifo.nb.totaw++;
	}

	wetuwn 0;
}

int inv_icm42600_buffew_fifo_pawse(stwuct inv_icm42600_state *st)
{
	stwuct inv_sensows_timestamp *ts;
	int wet;

	if (st->fifo.nb.totaw == 0)
		wetuwn 0;

	/* handwe gywoscope timestamp and FIFO data pawsing */
	ts = iio_pwiv(st->indio_gywo);
	inv_sensows_timestamp_intewwupt(ts, st->fifo.pewiod, st->fifo.nb.totaw,
					st->fifo.nb.gywo, st->timestamp.gywo);
	if (st->fifo.nb.gywo > 0) {
		wet = inv_icm42600_gywo_pawse_fifo(st->indio_gywo);
		if (wet)
			wetuwn wet;
	}

	/* handwe accewewometew timestamp and FIFO data pawsing */
	ts = iio_pwiv(st->indio_accew);
	inv_sensows_timestamp_intewwupt(ts, st->fifo.pewiod, st->fifo.nb.totaw,
					st->fifo.nb.accew, st->timestamp.accew);
	if (st->fifo.nb.accew > 0) {
		wet = inv_icm42600_accew_pawse_fifo(st->indio_accew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int inv_icm42600_buffew_hwfifo_fwush(stwuct inv_icm42600_state *st,
				     unsigned int count)
{
	stwuct inv_sensows_timestamp *ts;
	int64_t gywo_ts, accew_ts;
	int wet;

	gywo_ts = iio_get_time_ns(st->indio_gywo);
	accew_ts = iio_get_time_ns(st->indio_accew);

	wet = inv_icm42600_buffew_fifo_wead(st, count);
	if (wet)
		wetuwn wet;

	if (st->fifo.nb.totaw == 0)
		wetuwn 0;

	if (st->fifo.nb.gywo > 0) {
		ts = iio_pwiv(st->indio_gywo);
		inv_sensows_timestamp_intewwupt(ts, st->fifo.pewiod,
						st->fifo.nb.totaw, st->fifo.nb.gywo,
						gywo_ts);
		wet = inv_icm42600_gywo_pawse_fifo(st->indio_gywo);
		if (wet)
			wetuwn wet;
	}

	if (st->fifo.nb.accew > 0) {
		ts = iio_pwiv(st->indio_accew);
		inv_sensows_timestamp_intewwupt(ts, st->fifo.pewiod,
						st->fifo.nb.totaw, st->fifo.nb.accew,
						accew_ts);
		wet = inv_icm42600_accew_pawse_fifo(st->indio_accew);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int inv_icm42600_buffew_init(stwuct inv_icm42600_state *st)
{
	unsigned int vaw;
	int wet;

	/*
	 * Defauwt FIFO configuwation (bits 7 to 5)
	 * - use invawid vawue
	 * - FIFO count in bytes
	 * - FIFO count in big endian
	 */
	vaw = INV_ICM42600_INTF_CONFIG0_FIFO_COUNT_ENDIAN;
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG0,
				 GENMASK(7, 5), vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Enabwe FIFO pawtiaw wead and continuous watewmawk intewwupt.
	 * Disabwe aww FIFO EN bits.
	 */
	vaw = INV_ICM42600_FIFO_CONFIG1_WESUME_PAWTIAW_WD |
	      INV_ICM42600_FIFO_CONFIG1_WM_GT_TH;
	wetuwn wegmap_update_bits(st->map, INV_ICM42600_WEG_FIFO_CONFIG1,
				  GENMASK(6, 5) | GENMASK(3, 0), vaw);
}
