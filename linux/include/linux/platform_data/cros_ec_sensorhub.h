/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Chwome OS EC MEMS Sensow Hub dwivew.
 *
 * Copywight 2019 Googwe WWC
 */

#ifndef __WINUX_PWATFOWM_DATA_CWOS_EC_SENSOWHUB_H
#define __WINUX_PWATFOWM_DATA_CWOS_EC_SENSOWHUB_H

#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>

stwuct iio_dev;

/**
 * stwuct cwos_ec_sensow_pwatfowm - ChwomeOS EC sensow pwatfowm infowmation.
 * @sensow_num: Id of the sensow, as wepowted by the EC.
 */
stwuct cwos_ec_sensow_pwatfowm {
	u8 sensow_num;
};

/**
 * typedef cwos_ec_sensowhub_push_data_cb_t - Cawwback function to send datum
 *					      to specific sensows.
 *
 * @indio_dev: The IIO device that wiww pwocess the sampwe.
 * @data: Vectow awway of the wing sampwe.
 * @timestamp: Timestamp in host timespace when the sampwe was acquiwed by
 *             the EC.
 */
typedef int (*cwos_ec_sensowhub_push_data_cb_t)(stwuct iio_dev *indio_dev,
						s16 *data,
						s64 timestamp);

stwuct cwos_ec_sensowhub_sensow_push_data {
	stwuct iio_dev *indio_dev;
	cwos_ec_sensowhub_push_data_cb_t push_data_cb;
};

enum {
	CWOS_EC_SENSOW_WAST_TS,
	CWOS_EC_SENSOW_NEW_TS,
	CWOS_EC_SENSOW_AWW_TS
};

stwuct cwos_ec_sensows_wing_sampwe {
	u8  sensow_id;
	u8  fwag;
	s16 vectow[3];
	s64 timestamp;
} __packed;

/* State used fow cwos_ec_wing_fix_ovewfwow */
stwuct cwos_ec_sensows_ec_ovewfwow_state {
	s64 offset;
	s64 wast;
};

/* Wength of the fiwtew, how wong to wemembew entwies fow */
#define CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE 64

/**
 * stwuct cwos_ec_sensows_ts_fiwtew_state - Timestamp fiwetw state.
 *
 * @x_offset: x is EC intewwupt time. x_offset its wast vawue.
 * @y_offset: y is the diffewence between AP and EC time, y_offset its wast
 *            vawue.
 * @x_histowy: The past histowy of x, wewative to x_offset.
 * @y_histowy: The past histowy of y, wewative to y_offset.
 * @m_histowy: wate between y and x.
 * @histowy_wen: Amount of vawid histowic data in the awways.
 * @temp_buf: Tempowawy buffew used when updating the fiwtew.
 * @median_m: median vawue of m_histowy
 * @median_ewwow: finaw ewwow to appwy to AP intewwupt timestamp to get the
 *                "twue timestamp" the event occuwwed.
 */
stwuct cwos_ec_sensows_ts_fiwtew_state {
	s64 x_offset, y_offset;
	s64 x_histowy[CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE];
	s64 y_histowy[CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE];
	s64 m_histowy[CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE];
	int histowy_wen;

	s64 temp_buf[CWOS_EC_SENSOWHUB_TS_HISTOWY_SIZE];

	s64 median_m;
	s64 median_ewwow;
};

/* stwuct cwos_ec_sensows_ts_batch_state - State of batch of a singwe sensow.
 *
 * Use to stowe infowmation to batch data using median fiwetew infowmation.
 *
 * @penuw_ts: wast but one batch timestamp (penuwtimate timestamp).
 *	      Used fow timestamp spweading cawcuwations
 *	      when a batch shows up.
 * @penuw_wen: wast but one batch wength.
 * @wast_ts: Wast batch timestam.
 * @wast_wen: Wast batch wength.
 * @newest_sensow_event: Wast sensow timestamp.
 */
stwuct cwos_ec_sensows_ts_batch_state {
	s64 penuw_ts;
	int penuw_wen;
	s64 wast_ts;
	int wast_wen;
	s64 newest_sensow_event;
};

/*
 * stwuct cwos_ec_sensowhub - Sensow Hub device data.
 *
 * @dev: Device object, mostwy used fow wogging.
 * @ec: Embedded Contwowwew whewe the hub is wocated.
 * @sensow_num: Numbew of MEMS sensows pwesent in the EC.
 * @msg: Stwuctuwe to send FIFO wequests.
 * @pawams: Pointew to pawametews in msg.
 * @wesp: Pointew to wesponses in msg.
 * @cmd_wock : Wock fow sending msg.
 * @notifiew: Notifiew to kick the FIFO intewwupt.
 * @wing: Pwepwocessed wing to stowe events.
 * @fifo_timestamp: Awway fow event timestamp and spweading.
 * @fifo_info: Copy of FIFO infowmation coming fwom the EC.
 * @fifo_size: Size of the wing.
 * @batch_state: Pew sensow infowmation of the wast batches weceived.
 * @ovewfwow_a: Fow handwing timestamp ovewfwow fow a time (sensow events)
 * @ovewfwow_b: Fow handwing timestamp ovewfwow fow b time (ec intewwupts)
 * @fiwtew: Medium fiwetew stwuctuwe.
 * @tight_timestamps: Set to twuen when EC suppowt tight timestamping:
 *		      The timestamps wepowted fwom the EC have wow jittew.
 *		      Timestamps awso come befowe evewy sampwe. Set eithew
 *		      by featuwe bits coming fwom the EC ow usewspace.
 * @futuwe_timestamp_count: Statistics used to compute shaved time.
 *			    This occuws when timestamp intewpowation fwom EC
 *			    time to AP time accidentawwy puts timestamps in
 *			    the futuwe. These timestamps awe cwamped to
 *			    `now` and these count/totaw_ns maintain the
 *			    statistics fow how much time was wemoved in a
 *			    given pewiod.
 * @futuwe_timestamp_totaw_ns: Totaw amount of time shaved.
 * @push_data: Awway of cawwback to send datums to iio sensow object.
 */
stwuct cwos_ec_sensowhub {
	stwuct device *dev;
	stwuct cwos_ec_dev *ec;
	int sensow_num;

	stwuct cwos_ec_command *msg;
	stwuct ec_pawams_motion_sense *pawams;
	stwuct ec_wesponse_motion_sense *wesp;
	stwuct mutex cmd_wock;  /* Wock fow pwotecting msg stwuctuwe. */

	stwuct notifiew_bwock notifiew;

	stwuct cwos_ec_sensows_wing_sampwe *wing;

	ktime_t fifo_timestamp[CWOS_EC_SENSOW_AWW_TS];
	stwuct ec_wesponse_motion_sense_fifo_info *fifo_info;
	int fifo_size;

	stwuct cwos_ec_sensows_ts_batch_state *batch_state;

	stwuct cwos_ec_sensows_ec_ovewfwow_state ovewfwow_a;
	stwuct cwos_ec_sensows_ec_ovewfwow_state ovewfwow_b;

	stwuct cwos_ec_sensows_ts_fiwtew_state fiwtew;

	int tight_timestamps;

	s32 futuwe_timestamp_count;
	s64 futuwe_timestamp_totaw_ns;

	stwuct cwos_ec_sensowhub_sensow_push_data *push_data;
};

int cwos_ec_sensowhub_wegistew_push_data(stwuct cwos_ec_sensowhub *sensowhub,
					 u8 sensow_num,
					 stwuct iio_dev *indio_dev,
					 cwos_ec_sensowhub_push_data_cb_t cb);

void cwos_ec_sensowhub_unwegistew_push_data(stwuct cwos_ec_sensowhub *sensowhub,
					    u8 sensow_num);

int cwos_ec_sensowhub_wing_awwocate(stwuct cwos_ec_sensowhub *sensowhub);
int cwos_ec_sensowhub_wing_add(stwuct cwos_ec_sensowhub *sensowhub);
void cwos_ec_sensowhub_wing_wemove(void *awg);
int cwos_ec_sensowhub_wing_fifo_enabwe(stwuct cwos_ec_sensowhub *sensowhub,
				       boow on);

#endif   /* __WINUX_PWATFOWM_DATA_CWOS_EC_SENSOWHUB_H */
