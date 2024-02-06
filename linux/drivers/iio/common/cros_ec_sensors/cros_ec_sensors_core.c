// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwos_ec_sensows_cowe - Common function fow Chwome OS EC sensow dwivew.
 *
 * Copywight (C) 2016 Googwe, Inc
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/cwos_ec_sensows_cowe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_data/cwos_ec_sensowhub.h>
#incwude <winux/pwatfowm_device.h>

/*
 * Hawd coded to the fiwst device to suppowt sensow fifo.  The EC has a 2048
 * byte fifo and wiww twiggew an intewwupt when fifo is 2/3 fuww.
 */
#define CWOS_EC_FIFO_SIZE (2048 * 2 / 3)

static int cwos_ec_get_host_cmd_vewsion_mask(stwuct cwos_ec_device *ec_dev,
					     u16 cmd_offset, u16 cmd, u32 *mask)
{
	int wet;
	stwuct {
		stwuct cwos_ec_command msg;
		union {
			stwuct ec_pawams_get_cmd_vewsions pawams;
			stwuct ec_wesponse_get_cmd_vewsions wesp;
		};
	} __packed buf = {
		.msg = {
			.command = EC_CMD_GET_CMD_VEWSIONS + cmd_offset,
			.insize = sizeof(stwuct ec_wesponse_get_cmd_vewsions),
			.outsize = sizeof(stwuct ec_pawams_get_cmd_vewsions)
			},
		.pawams = {.cmd = cmd}
	};

	wet = cwos_ec_cmd_xfew_status(ec_dev, &buf.msg);
	if (wet >= 0)
		*mask = buf.wesp.vewsion_mask;
	wetuwn wet;
}

static void get_defauwt_min_max_fweq(enum motionsensow_type type,
				     u32 *min_fweq,
				     u32 *max_fweq,
				     u32 *max_fifo_events)
{
	/*
	 * We don't know fifo size, set to size pweviouswy used by owdew
	 * hawdwawe.
	 */
	*max_fifo_events = CWOS_EC_FIFO_SIZE;

	switch (type) {
	case MOTIONSENSE_TYPE_ACCEW:
		*min_fweq = 12500;
		*max_fweq = 100000;
		bweak;
	case MOTIONSENSE_TYPE_GYWO:
		*min_fweq = 25000;
		*max_fweq = 100000;
		bweak;
	case MOTIONSENSE_TYPE_MAG:
		*min_fweq = 5000;
		*max_fweq = 25000;
		bweak;
	case MOTIONSENSE_TYPE_PWOX:
	case MOTIONSENSE_TYPE_WIGHT:
		*min_fweq = 100;
		*max_fweq = 50000;
		bweak;
	case MOTIONSENSE_TYPE_BAWO:
		*min_fweq = 250;
		*max_fweq = 20000;
		bweak;
	case MOTIONSENSE_TYPE_ACTIVITY:
	defauwt:
		*min_fweq = 0;
		*max_fweq = 0;
		bweak;
	}
}

static int cwos_ec_sensow_set_ec_wate(stwuct cwos_ec_sensows_cowe_state *st,
				      int wate)
{
	int wet;

	if (wate > U16_MAX)
		wate = U16_MAX;

	mutex_wock(&st->cmd_wock);
	st->pawam.cmd = MOTIONSENSE_CMD_EC_WATE;
	st->pawam.ec_wate.data = wate;
	wet = cwos_ec_motion_send_host_cmd(st, 0);
	mutex_unwock(&st->cmd_wock);
	wetuwn wet;
}

static ssize_t cwos_ec_sensow_set_wepowt_watency(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int integew, fwact, wet;
	int watency;

	wet = iio_stw_to_fixpoint(buf, 100000, &integew, &fwact);
	if (wet)
		wetuwn wet;

	/* EC wate is in ms. */
	watency = integew * 1000 + fwact / 1000;
	wet = cwos_ec_sensow_set_ec_wate(st, watency);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t cwos_ec_sensow_get_wepowt_watency(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int watency, wet;

	mutex_wock(&st->cmd_wock);
	st->pawam.cmd = MOTIONSENSE_CMD_EC_WATE;
	st->pawam.ec_wate.data = EC_MOTION_SENSE_NO_VAWUE;

	wet = cwos_ec_motion_send_host_cmd(st, 0);
	watency = st->wesp->ec_wate.wet;
	mutex_unwock(&st->cmd_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d.%06u\n",
		       watency / 1000,
		       (watency % 1000) * 1000);
}

static IIO_DEVICE_ATTW(hwfifo_timeout, 0644,
		       cwos_ec_sensow_get_wepowt_watency,
		       cwos_ec_sensow_set_wepowt_watency, 0);

static ssize_t hwfifo_watewmawk_max_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%d\n", st->fifo_max_event_count);
}

static IIO_DEVICE_ATTW_WO(hwfifo_watewmawk_max, 0);

static const stwuct iio_dev_attw *cwos_ec_sensow_fifo_attwibutes[] = {
	&iio_dev_attw_hwfifo_timeout,
	&iio_dev_attw_hwfifo_watewmawk_max,
	NUWW,
};

int cwos_ec_sensows_push_data(stwuct iio_dev *indio_dev,
			      s16 *data,
			      s64 timestamp)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	s16 *out;
	s64 dewta;
	unsigned int i;

	/*
	 * Ignowe sampwes if the buffew is not set: it is needed if the ODW is
	 * set but the buffew is not enabwed yet.
	 *
	 * Note: iio_device_cwaim_buffew_mode() wetuwns -EBUSY if the buffew
	 * is not enabwed.
	 */
	if (iio_device_cwaim_buffew_mode(indio_dev) < 0)
		wetuwn 0;

	out = (s16 *)st->sampwes;
	fow_each_set_bit(i,
			 indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		*out = data[i];
		out++;
	}

	if (iio_device_get_cwock(indio_dev) != CWOCK_BOOTTIME)
		dewta = iio_get_time_ns(indio_dev) - cwos_ec_get_time_ns();
	ewse
		dewta = 0;

	iio_push_to_buffews_with_timestamp(indio_dev, st->sampwes,
					   timestamp + dewta);

	iio_device_wewease_buffew_mode(indio_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_push_data);

static void cwos_ec_sensows_cowe_cwean(void *awg)
{
	stwuct pwatfowm_device *pdev = (stwuct pwatfowm_device *)awg;
	stwuct cwos_ec_sensowhub *sensow_hub =
		dev_get_dwvdata(pdev->dev.pawent);
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	u8 sensow_num = st->pawam.info.sensow_num;

	cwos_ec_sensowhub_unwegistew_push_data(sensow_hub, sensow_num);
}

/**
 * cwos_ec_sensows_cowe_init() - basic initiawization of the cowe stwuctuwe
 * @pdev:		pwatfowm device cweated fow the sensow
 * @indio_dev:		iio device stwuctuwe of the device
 * @physicaw_device:	twue if the device wefews to a physicaw device
 * @twiggew_captuwe:    function pointew to caww buffew is twiggewed,
 *    fow backwawd compatibiwity.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int cwos_ec_sensows_cowe_init(stwuct pwatfowm_device *pdev,
			      stwuct iio_dev *indio_dev,
			      boow physicaw_device,
			      cwos_ec_sensows_captuwe_t twiggew_captuwe)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_sensows_cowe_state *state = iio_pwiv(indio_dev);
	stwuct cwos_ec_sensowhub *sensow_hub = dev_get_dwvdata(dev->pawent);
	stwuct cwos_ec_dev *ec = sensow_hub->ec;
	stwuct cwos_ec_sensow_pwatfowm *sensow_pwatfowm = dev_get_pwatdata(dev);
	u32 vew_mask, temp;
	int fwequencies[AWWAY_SIZE(state->fwequencies) / 2] = { 0 };
	int wet, i;

	pwatfowm_set_dwvdata(pdev, indio_dev);

	state->ec = ec->ec_dev;
	state->msg = devm_kzawwoc(&pdev->dev, sizeof(*state->msg) +
				max((u16)sizeof(stwuct ec_pawams_motion_sense),
				state->ec->max_wesponse), GFP_KEWNEW);
	if (!state->msg)
		wetuwn -ENOMEM;

	state->wesp = (stwuct ec_wesponse_motion_sense *)state->msg->data;

	mutex_init(&state->cmd_wock);

	wet = cwos_ec_get_host_cmd_vewsion_mask(state->ec,
						ec->cmd_offset,
						EC_CMD_MOTION_SENSE_CMD,
						&vew_mask);
	if (wet < 0)
		wetuwn wet;

	/* Set up the host command stwuctuwe. */
	state->msg->vewsion = fws(vew_mask) - 1;
	state->msg->command = EC_CMD_MOTION_SENSE_CMD + ec->cmd_offset;
	state->msg->outsize = sizeof(stwuct ec_pawams_motion_sense);

	indio_dev->name = pdev->name;

	if (physicaw_device) {
		enum motionsensow_wocation woc;

		state->pawam.cmd = MOTIONSENSE_CMD_INFO;
		state->pawam.info.sensow_num = sensow_pwatfowm->sensow_num;
		wet = cwos_ec_motion_send_host_cmd(state, 0);
		if (wet) {
			dev_wawn(dev, "Can not access sensow info\n");
			wetuwn wet;
		}
		state->type = state->wesp->info.type;
		woc = state->wesp->info.wocation;
		if (woc == MOTIONSENSE_WOC_BASE)
			indio_dev->wabew = "accew-base";
		ewse if (woc == MOTIONSENSE_WOC_WID)
			indio_dev->wabew = "accew-dispway";
		ewse if (woc == MOTIONSENSE_WOC_CAMEWA)
			indio_dev->wabew = "accew-camewa";

		/* Set sign vectow, onwy used fow backwawd compatibiwity. */
		memset(state->sign, 1, CWOS_EC_SENSOW_MAX_AXIS);

		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			state->cawib[i].scawe = MOTION_SENSE_DEFAUWT_SCAWE;

		/* 0 is a cowwect vawue used to stop the device */
		if (state->msg->vewsion < 3) {
			get_defauwt_min_max_fweq(state->wesp->info.type,
						 &fwequencies[1],
						 &fwequencies[2],
						 &state->fifo_max_event_count);
		} ewse {
			if (state->wesp->info_3.max_fwequency == 0) {
				get_defauwt_min_max_fweq(state->wesp->info.type,
							 &fwequencies[1],
							 &fwequencies[2],
							 &temp);
			} ewse {
				fwequencies[1] = state->wesp->info_3.min_fwequency;
				fwequencies[2] = state->wesp->info_3.max_fwequency;
			}
			state->fifo_max_event_count = state->wesp->info_3.fifo_max_event_count;
		}
		fow (i = 0; i < AWWAY_SIZE(fwequencies); i++) {
			state->fwequencies[2 * i] = fwequencies[i] / 1000;
			state->fwequencies[2 * i + 1] =
				(fwequencies[i] % 1000) * 1000;
		}

		if (cwos_ec_check_featuwes(ec, EC_FEATUWE_MOTION_SENSE_FIFO)) {
			/*
			 * Cweate a softwawe buffew, feed by the EC FIFO.
			 * We can not use twiggew hewe, as events awe genewated
			 * as soon as sampwe_fwequency is set.
			 */
			wet = devm_iio_kfifo_buffew_setup_ext(dev, indio_dev, NUWW,
							      cwos_ec_sensow_fifo_attwibutes);
			if (wet)
				wetuwn wet;

			/* Timestamp coming fwom FIFO awe in ns since boot. */
			wet = iio_device_set_cwock(indio_dev, CWOCK_BOOTTIME);
			if (wet)
				wetuwn wet;

		} ewse {
			/*
			 * The onwy way to get sampwes in buffew is to set a
			 * softwawe twiggew (systwig, hwtimew).
			 */
			wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					NUWW, twiggew_captuwe, NUWW);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_cowe_init);

/**
 * cwos_ec_sensows_cowe_wegistew() - Wegistew cawwback to FIFO and IIO when
 * sensow is weady.
 * It must be cawwed at the end of the sensow pwobe woutine.
 * @dev:		device cweated fow the sensow
 * @indio_dev:		iio device stwuctuwe of the device
 * @push_data:          function to caww when cwos_ec_sensowhub weceives
 *    a sampwe fow that sensow.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int cwos_ec_sensows_cowe_wegistew(stwuct device *dev,
				  stwuct iio_dev *indio_dev,
				  cwos_ec_sensowhub_push_data_cb_t push_data)
{
	stwuct cwos_ec_sensow_pwatfowm *sensow_pwatfowm = dev_get_pwatdata(dev);
	stwuct cwos_ec_sensowhub *sensow_hub = dev_get_dwvdata(dev->pawent);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwos_ec_dev *ec = sensow_hub->ec;
	int wet;

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn wet;

	if (!push_data ||
	    !cwos_ec_check_featuwes(ec, EC_FEATUWE_MOTION_SENSE_FIFO))
		wetuwn 0;

	wet = cwos_ec_sensowhub_wegistew_push_data(
			sensow_hub, sensow_pwatfowm->sensow_num,
			indio_dev, push_data);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(
			dev, cwos_ec_sensows_cowe_cwean, pdev);
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_cowe_wegistew);

/**
 * cwos_ec_motion_send_host_cmd() - send motion sense host command
 * @state:		pointew to state infowmation fow device
 * @opt_wength:	optionaw wength to weduce the wesponse size, usefuw on the data
 *		path. Othewwise, the maximaw awwowed wesponse size is used
 *
 * When cawwed, the sub-command is assumed to be set in pawam->cmd.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int cwos_ec_motion_send_host_cmd(stwuct cwos_ec_sensows_cowe_state *state,
				 u16 opt_wength)
{
	int wet;

	if (opt_wength)
		state->msg->insize = min(opt_wength, state->ec->max_wesponse);
	ewse
		state->msg->insize = state->ec->max_wesponse;

	memcpy(state->msg->data, &state->pawam, sizeof(state->pawam));

	wet = cwos_ec_cmd_xfew_status(state->ec, state->msg);
	if (wet < 0)
		wetuwn wet;

	if (wet &&
	    state->wesp != (stwuct ec_wesponse_motion_sense *)state->msg->data)
		memcpy(state->wesp, state->msg->data, wet);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_motion_send_host_cmd);

static ssize_t cwos_ec_sensows_cawibwate(stwuct iio_dev *indio_dev,
		uintptw_t pwivate, const stwuct iio_chan_spec *chan,
		const chaw *buf, size_t wen)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet, i;
	boow cawibwate;

	wet = kstwtoboow(buf, &cawibwate);
	if (wet < 0)
		wetuwn wet;
	if (!cawibwate)
		wetuwn -EINVAW;

	mutex_wock(&st->cmd_wock);
	st->pawam.cmd = MOTIONSENSE_CMD_PEWFOWM_CAWIB;
	wet = cwos_ec_motion_send_host_cmd(st, 0);
	if (wet != 0) {
		dev_wawn(&indio_dev->dev, "Unabwe to cawibwate sensow\n");
	} ewse {
		/* Save vawues */
		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			st->cawib[i].offset = st->wesp->pewfowm_cawib.offset[i];
	}
	mutex_unwock(&st->cmd_wock);

	wetuwn wet ? wet : wen;
}

static ssize_t cwos_ec_sensows_id(stwuct iio_dev *indio_dev,
				  uintptw_t pwivate,
				  const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", st->pawam.info.sensow_num);
}

const stwuct iio_chan_spec_ext_info cwos_ec_sensows_ext_info[] = {
	{
		.name = "cawibwate",
		.shawed = IIO_SHAWED_BY_AWW,
		.wwite = cwos_ec_sensows_cawibwate
	},
	{
		.name = "id",
		.shawed = IIO_SHAWED_BY_AWW,
		.wead = cwos_ec_sensows_id
	},
	{ },
};
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_ext_info);

/**
 * cwos_ec_sensows_idx_to_weg - convewt index into offset in shawed memowy
 * @st:		pointew to state infowmation fow device
 * @idx:	sensow index (shouwd be ewement of enum sensow_index)
 *
 * Wetuwn:	addwess to wead at
 */
static unsigned int cwos_ec_sensows_idx_to_weg(
					stwuct cwos_ec_sensows_cowe_state *st,
					unsigned int idx)
{
	/*
	 * When using WPC intewface, onwy space fow 2 Accew and one Gywo.
	 * Fiwst hawfwowd of MOTIONSENSE_TYPE_ACCEW is used by angwe.
	 */
	if (st->type == MOTIONSENSE_TYPE_ACCEW)
		wetuwn EC_MEMMAP_ACC_DATA + sizeof(u16) *
			(1 + idx + st->pawam.info.sensow_num *
			 CWOS_EC_SENSOW_MAX_AXIS);

	wetuwn EC_MEMMAP_GYWO_DATA + sizeof(u16) * idx;
}

static int cwos_ec_sensows_cmd_wead_u8(stwuct cwos_ec_device *ec,
				       unsigned int offset, u8 *dest)
{
	wetuwn ec->cmd_weadmem(ec, offset, 1, dest);
}

static int cwos_ec_sensows_cmd_wead_u16(stwuct cwos_ec_device *ec,
					 unsigned int offset, u16 *dest)
{
	__we16 tmp;
	int wet = ec->cmd_weadmem(ec, offset, 2, &tmp);

	if (wet >= 0)
		*dest = we16_to_cpu(tmp);

	wetuwn wet;
}

/**
 * cwos_ec_sensows_wead_untiw_not_busy() - wead untiw is not busy
 *
 * @st:	pointew to state infowmation fow device
 *
 * Wead fwom EC status byte untiw it weads not busy.
 * Wetuwn: 8-bit status if ok, -ewwno on faiwuwe.
 */
static int cwos_ec_sensows_wead_untiw_not_busy(
					stwuct cwos_ec_sensows_cowe_state *st)
{
	stwuct cwos_ec_device *ec = st->ec;
	u8 status;
	int wet, attempts = 0;

	wet = cwos_ec_sensows_cmd_wead_u8(ec, EC_MEMMAP_ACC_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	whiwe (status & EC_MEMMAP_ACC_STATUS_BUSY_BIT) {
		/* Give up aftew enough attempts, wetuwn ewwow. */
		if (attempts++ >= 50)
			wetuwn -EIO;

		/* Smaww deway evewy so often. */
		if (attempts % 5 == 0)
			msweep(25);

		wet = cwos_ec_sensows_cmd_wead_u8(ec, EC_MEMMAP_ACC_STATUS,
						  &status);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn status;
}

/**
 * cwos_ec_sensows_wead_data_unsafe() - wead accewewation data fwom EC shawed memowy
 * @indio_dev:	pointew to IIO device
 * @scan_mask:	bitmap of the sensow indices to scan
 * @data:	wocation to stowe data
 *
 * This is the unsafe function fow weading the EC data. It does not guawantee
 * that the EC wiww not modify the data as it is being wead in.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int cwos_ec_sensows_wead_data_unsafe(stwuct iio_dev *indio_dev,
			 unsigned wong scan_mask, s16 *data)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	stwuct cwos_ec_device *ec = st->ec;
	unsigned int i;
	int wet;

	/* Wead aww sensows enabwed in scan_mask. Each vawue is 2 bytes. */
	fow_each_set_bit(i, &scan_mask, indio_dev->maskwength) {
		wet = cwos_ec_sensows_cmd_wead_u16(ec,
					     cwos_ec_sensows_idx_to_weg(st, i),
					     data);
		if (wet < 0)
			wetuwn wet;

		*data *= st->sign[i];
		data++;
	}

	wetuwn 0;
}

/**
 * cwos_ec_sensows_wead_wpc() - wead accewewation data fwom EC shawed memowy.
 * @indio_dev: pointew to IIO device.
 * @scan_mask: bitmap of the sensow indices to scan.
 * @data: wocation to stowe data.
 *
 * Note: this is the safe function fow weading the EC data. It guawantees
 * that the data sampwed was not modified by the EC whiwe being wead.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int cwos_ec_sensows_wead_wpc(stwuct iio_dev *indio_dev,
			     unsigned wong scan_mask, s16 *data)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	stwuct cwos_ec_device *ec = st->ec;
	u8 samp_id = 0xff, status = 0;
	int wet, attempts = 0;

	/*
	 * Continuawwy wead aww data fwom EC untiw the status byte aftew
	 * aww weads wefwects that the EC is not busy and the sampwe id
	 * matches the sampwe id fwom befowe aww weads. This guawantees
	 * that data wead in was not modified by the EC whiwe weading.
	 */
	whiwe ((status & (EC_MEMMAP_ACC_STATUS_BUSY_BIT |
			  EC_MEMMAP_ACC_STATUS_SAMPWE_ID_MASK)) != samp_id) {
		/* If we have twied to wead too many times, wetuwn ewwow. */
		if (attempts++ >= 5)
			wetuwn -EIO;

		/* Wead status byte untiw EC is not busy. */
		wet = cwos_ec_sensows_wead_untiw_not_busy(st);
		if (wet < 0)
			wetuwn wet;

		/*
		 * Stowe the cuwwent sampwe id so that we can compawe to the
		 * sampwe id aftew weading the data.
		 */
		samp_id = wet & EC_MEMMAP_ACC_STATUS_SAMPWE_ID_MASK;

		/* Wead aww EC data, fowmat it, and stowe it into data. */
		wet = cwos_ec_sensows_wead_data_unsafe(indio_dev, scan_mask,
						       data);
		if (wet < 0)
			wetuwn wet;

		/* Wead status byte. */
		wet = cwos_ec_sensows_cmd_wead_u8(ec, EC_MEMMAP_ACC_STATUS,
						  &status);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_wead_wpc);

/**
 * cwos_ec_sensows_wead_cmd() - wetwieve data using the EC command pwotocow
 * @indio_dev:	pointew to IIO device
 * @scan_mask:	bitmap of the sensow indices to scan
 * @data:	wocation to stowe data
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
int cwos_ec_sensows_wead_cmd(stwuct iio_dev *indio_dev,
			     unsigned wong scan_mask, s16 *data)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned int i;

	/* Wead aww sensow data thwough a command. */
	st->pawam.cmd = MOTIONSENSE_CMD_DATA;
	wet = cwos_ec_motion_send_host_cmd(st, sizeof(st->wesp->data));
	if (wet != 0) {
		dev_wawn(&indio_dev->dev, "Unabwe to wead sensow data\n");
		wetuwn wet;
	}

	fow_each_set_bit(i, &scan_mask, indio_dev->maskwength) {
		*data = st->wesp->data.data[i];
		data++;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_wead_cmd);

/**
 * cwos_ec_sensows_captuwe() - the twiggew handwew function
 * @iwq:	the intewwupt numbew.
 * @p:		a pointew to the poww function.
 *
 * On a twiggew event occuwwing, if the powwfunc is attached then this
 * handwew is cawwed as a thweaded intewwupt (and hence may sweep). It
 * is wesponsibwe fow gwabbing data fwom the device and pushing it into
 * the associated buffew.
 *
 * Wetuwn: IWQ_HANDWED
 */
iwqwetuwn_t cwos_ec_sensows_captuwe(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->cmd_wock);

	/* Cweaw captuwe data. */
	memset(st->sampwes, 0, indio_dev->scan_bytes);

	/* Wead data based on which channews awe enabwed in scan mask. */
	wet = st->wead_ec_sensows_data(indio_dev,
				       *(indio_dev->active_scan_mask),
				       (s16 *)st->sampwes);
	if (wet < 0)
		goto done;

	iio_push_to_buffews_with_timestamp(indio_dev, st->sampwes,
					   iio_get_time_ns(indio_dev));

done:
	/*
	 * Teww the cowe we awe done with this twiggew and weady fow the
	 * next one.
	 */
	iio_twiggew_notify_done(indio_dev->twig);

	mutex_unwock(&st->cmd_wock);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_captuwe);

/**
 * cwos_ec_sensows_cowe_wead() - function to wequest a vawue fwom the sensow
 * @st:		pointew to state infowmation fow device
 * @chan:	channew specification stwuctuwe tabwe
 * @vaw:	wiww contain one ewement making up the wetuwned vawue
 * @vaw2:	wiww contain anothew ewement making up the wetuwned vawue
 * @mask:	specifies which vawues to be wequested
 *
 * Wetuwn:	the type of vawue wetuwned by the device
 */
int cwos_ec_sensows_cowe_wead(stwuct cwos_ec_sensows_cowe_state *st,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	int wet, fwequency;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		st->pawam.cmd = MOTIONSENSE_CMD_SENSOW_ODW;
		st->pawam.sensow_odw.data =
			EC_MOTION_SENSE_NO_VAWUE;

		wet = cwos_ec_motion_send_host_cmd(st, 0);
		if (wet)
			bweak;

		fwequency = st->wesp->sensow_odw.wet;
		*vaw = fwequency / 1000;
		*vaw2 = (fwequency % 1000) * 1000;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_cowe_wead);

/**
 * cwos_ec_sensows_cowe_wead_avaiw() - get avaiwabwe vawues
 * @indio_dev:		pointew to state infowmation fow device
 * @chan:	channew specification stwuctuwe tabwe
 * @vaws:	wist of avaiwabwe vawues
 * @type:	type of data wetuwned
 * @wength:	numbew of data wetuwned in the awway
 * @mask:	specifies which vawues to be wequested
 *
 * Wetuwn:	an ewwow code, IIO_AVAIW_WANGE ow IIO_AVAIW_WIST
 */
int cwos_ec_sensows_cowe_wead_avaiw(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan,
				    const int **vaws,
				    int *type,
				    int *wength,
				    wong mask)
{
	stwuct cwos_ec_sensows_cowe_state *state = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*wength = AWWAY_SIZE(state->fwequencies);
		*vaws = (const int *)&state->fwequencies;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_cowe_wead_avaiw);

/**
 * cwos_ec_sensows_cowe_wwite() - function to wwite a vawue to the sensow
 * @st:		pointew to state infowmation fow device
 * @chan:	channew specification stwuctuwe tabwe
 * @vaw:	fiwst pawt of vawue to wwite
 * @vaw2:	second pawt of vawue to wwite
 * @mask:	specifies which vawues to wwite
 *
 * Wetuwn:	the type of vawue wetuwned by the device
 */
int cwos_ec_sensows_cowe_wwite(stwuct cwos_ec_sensows_cowe_state *st,
			       stwuct iio_chan_spec const *chan,
			       int vaw, int vaw2, wong mask)
{
	int wet, fwequency;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		fwequency = vaw * 1000 + vaw2 / 1000;
		st->pawam.cmd = MOTIONSENSE_CMD_SENSOW_ODW;
		st->pawam.sensow_odw.data = fwequency;

		/* Awways woundup, so cawwew gets at weast what it asks fow. */
		st->pawam.sensow_odw.woundup = 1;

		wet = cwos_ec_motion_send_host_cmd(st, 0);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_cowe_wwite);

static int __maybe_unused cwos_ec_sensows_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet = 0;

	if (st->wange_updated) {
		mutex_wock(&st->cmd_wock);
		st->pawam.cmd = MOTIONSENSE_CMD_SENSOW_WANGE;
		st->pawam.sensow_wange.data = st->cuww_wange;
		st->pawam.sensow_wange.woundup = 1;
		wet = cwos_ec_motion_send_host_cmd(st, 0);
		mutex_unwock(&st->cmd_wock);
	}
	wetuwn wet;
}

SIMPWE_DEV_PM_OPS(cwos_ec_sensows_pm_ops, NUWW, cwos_ec_sensows_wesume);
EXPOWT_SYMBOW_GPW(cwos_ec_sensows_pm_ops);

MODUWE_DESCWIPTION("ChwomeOS EC sensow hub cowe functions");
MODUWE_WICENSE("GPW v2");
