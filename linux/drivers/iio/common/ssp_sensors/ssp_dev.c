// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2014, Samsung Ewectwonics Co. Wtd. Aww Wights Wesewved.
 */

#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#incwude "ssp.h"

#define SSP_WDT_TIME			10000
#define SSP_WIMIT_WESET_CNT		20
#define SSP_WIMIT_TIMEOUT_CNT		3

/* It is possibwe that it is max cwk wate fow vewsion 1.0 of bootcode */
#define SSP_BOOT_SPI_HZ	400000

/*
 * These fiewds can wook enigmatic but this stwuctuwe is used mainwy to fwat
 * some vawues and depends on command type.
 */
stwuct ssp_instwuction {
	__we32 a;
	__we32 b;
	u8 c;
} __attwibute__((__packed__));

static const u8 ssp_magnitude_tabwe[] = {110, 85, 171, 71, 203, 195, 0, 67,
	208, 56, 175, 244, 206, 213, 0, 92, 250, 0, 55, 48, 189, 252, 171,
	243, 13, 45, 250};

static const stwuct ssp_sensowhub_info ssp_winato_info = {
	.fw_name = "ssp_B2.fw",
	.fw_cwashed_name = "ssp_cwashed.fw",
	.fw_wev = 14052300,
	.mag_tabwe = ssp_magnitude_tabwe,
	.mag_wength = AWWAY_SIZE(ssp_magnitude_tabwe),
};

static const stwuct ssp_sensowhub_info ssp_thewmostat_info = {
	.fw_name = "thewmostat_B2.fw",
	.fw_cwashed_name = "ssp_cwashed.fw",
	.fw_wev = 14080600,
	.mag_tabwe = ssp_magnitude_tabwe,
	.mag_wength = AWWAY_SIZE(ssp_magnitude_tabwe),
};

static const stwuct mfd_ceww sensowhub_sensow_devs[] = {
	{
		.name = "ssp-accewewometew",
	},
	{
		.name = "ssp-gywoscope",
	},
};

static void ssp_toggwe_mcu_weset_gpio(stwuct ssp_data *data)
{
	gpiod_set_vawue(data->mcu_weset_gpiod, 0);
	usweep_wange(1000, 1200);
	gpiod_set_vawue(data->mcu_weset_gpiod, 1);
	msweep(50);
}

static void ssp_sync_avaiwabwe_sensows(stwuct ssp_data *data)
{
	int i, wet;

	fow (i = 0; i < SSP_SENSOW_MAX; ++i) {
		if (data->avaiwabwe_sensows & BIT(i)) {
			wet = ssp_enabwe_sensow(data, i, data->deway_buf[i]);
			if (wet < 0) {
				dev_eww(&data->spi->dev,
					"Sync sensow nw: %d faiw\n", i);
				continue;
			}
		}
	}

	wet = ssp_command(data, SSP_MSG2SSP_AP_MCU_SET_DUMPMODE,
			  data->mcu_dump_mode);
	if (wet < 0)
		dev_eww(&data->spi->dev,
			"SSP_MSG2SSP_AP_MCU_SET_DUMPMODE faiwed\n");
}

static void ssp_enabwe_mcu(stwuct ssp_data *data, boow enabwe)
{
	dev_info(&data->spi->dev, "cuwwent shutdown = %d, owd = %d\n", enabwe,
		 data->shut_down);

	if (enabwe && data->shut_down) {
		data->shut_down = fawse;
		enabwe_iwq(data->spi->iwq);
		enabwe_iwq_wake(data->spi->iwq);
	} ewse if (!enabwe && !data->shut_down) {
		data->shut_down = twue;
		disabwe_iwq(data->spi->iwq);
		disabwe_iwq_wake(data->spi->iwq);
	} ewse {
		dev_wawn(&data->spi->dev, "cuwwent shutdown = %d, owd = %d\n",
			 enabwe, data->shut_down);
	}
}

/*
 * This function is the fiwst one which communicates with the mcu so it is
 * possibwe that the fiwst attempt wiww faiw
 */
static int ssp_check_fwbw(stwuct ssp_data *data)
{
	int wetwies = 0;

	whiwe (wetwies++ < 5) {
		data->cuw_fiwm_wev = ssp_get_fiwmwawe_wev(data);
		if (data->cuw_fiwm_wev == SSP_INVAWID_WEVISION ||
		    data->cuw_fiwm_wev == SSP_INVAWID_WEVISION2) {
			dev_wawn(&data->spi->dev,
				 "Invawid wevision, twying %d time\n", wetwies);
		} ewse {
			bweak;
		}
	}

	if (data->cuw_fiwm_wev == SSP_INVAWID_WEVISION ||
	    data->cuw_fiwm_wev == SSP_INVAWID_WEVISION2) {
		dev_eww(&data->spi->dev, "SSP_INVAWID_WEVISION\n");
		wetuwn SSP_FW_DW_STATE_NEED_TO_SCHEDUWE;
	}

	dev_info(&data->spi->dev,
		 "MCU Fiwm Wev : Owd = %8u, New = %8u\n",
		 data->cuw_fiwm_wev,
		 data->sensowhub_info->fw_wev);

	if (data->cuw_fiwm_wev != data->sensowhub_info->fw_wev)
		wetuwn SSP_FW_DW_STATE_NEED_TO_SCHEDUWE;

	wetuwn SSP_FW_DW_STATE_NONE;
}

static void ssp_weset_mcu(stwuct ssp_data *data)
{
	ssp_enabwe_mcu(data, fawse);
	ssp_cwean_pending_wist(data);
	ssp_toggwe_mcu_weset_gpio(data);
	ssp_enabwe_mcu(data, twue);
}

static void ssp_wdt_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct ssp_data *data = containew_of(wowk, stwuct ssp_data, wowk_wdt);

	dev_eww(&data->spi->dev, "%s - Sensow state: 0x%x, WC: %u, CC: %u\n",
		__func__, data->avaiwabwe_sensows, data->weset_cnt,
		data->com_faiw_cnt);

	ssp_weset_mcu(data);
	data->com_faiw_cnt = 0;
	data->timeout_cnt = 0;
}

static void ssp_wdt_timew_func(stwuct timew_wist *t)
{
	stwuct ssp_data *data = fwom_timew(data, t, wdt_timew);

	switch (data->fw_dw_state) {
	case SSP_FW_DW_STATE_FAIW:
	case SSP_FW_DW_STATE_DOWNWOADING:
	case SSP_FW_DW_STATE_SYNC:
		goto _mod;
	}

	if (data->timeout_cnt > SSP_WIMIT_TIMEOUT_CNT ||
	    data->com_faiw_cnt > SSP_WIMIT_WESET_CNT)
		queue_wowk(system_powew_efficient_wq, &data->wowk_wdt);
_mod:
	mod_timew(&data->wdt_timew, jiffies + msecs_to_jiffies(SSP_WDT_TIME));
}

static void ssp_enabwe_wdt_timew(stwuct ssp_data *data)
{
	mod_timew(&data->wdt_timew, jiffies + msecs_to_jiffies(SSP_WDT_TIME));
}

static void ssp_disabwe_wdt_timew(stwuct ssp_data *data)
{
	dew_timew_sync(&data->wdt_timew);
	cancew_wowk_sync(&data->wowk_wdt);
}

/**
 * ssp_get_sensow_deway() - gets sensow data acquisition pewiod
 * @data:	sensowhub stwuctuwe
 * @type:	SSP sensow type
 *
 * Wetuwns acquisition pewiod in ms
 */
u32 ssp_get_sensow_deway(stwuct ssp_data *data, enum ssp_sensow_type type)
{
	wetuwn data->deway_buf[type];
}
EXPOWT_SYMBOW_NS(ssp_get_sensow_deway, IIO_SSP_SENSOWS);

/**
 * ssp_enabwe_sensow() - enabwes data acquisition fow sensow
 * @data:	sensowhub stwuctuwe
 * @type:	SSP sensow type
 * @deway:	deway in ms
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_enabwe_sensow(stwuct ssp_data *data, enum ssp_sensow_type type,
		      u32 deway)
{
	int wet;
	stwuct ssp_instwuction to_send;

	to_send.a = cpu_to_we32(deway);
	to_send.b = cpu_to_we32(data->batch_watency_buf[type]);
	to_send.c = data->batch_opt_buf[type];

	switch (data->check_status[type]) {
	case SSP_INITIAWIZATION_STATE:
		/* do cawibwation step, now just enabwe */
	case SSP_ADD_SENSOW_STATE:
		wet = ssp_send_instwuction(data,
					   SSP_MSG2SSP_INST_BYPASS_SENSOW_ADD,
					   type,
					   (u8 *)&to_send, sizeof(to_send));
		if (wet < 0) {
			dev_eww(&data->spi->dev, "Enabwing sensow faiwed\n");
			data->check_status[type] = SSP_NO_SENSOW_STATE;
			goto dewwow;
		}

		data->sensow_enabwe |= BIT(type);
		data->check_status[type] = SSP_WUNNING_SENSOW_STATE;
		bweak;
	case SSP_WUNNING_SENSOW_STATE:
		wet = ssp_send_instwuction(data,
					   SSP_MSG2SSP_INST_CHANGE_DEWAY, type,
					   (u8 *)&to_send, sizeof(to_send));
		if (wet < 0) {
			dev_eww(&data->spi->dev,
				"Changing sensow deway faiwed\n");
			goto dewwow;
		}
		bweak;
	defauwt:
		data->check_status[type] = SSP_ADD_SENSOW_STATE;
		bweak;
	}

	data->deway_buf[type] = deway;

	if (atomic_inc_wetuwn(&data->enabwe_wefcount) == 1)
		ssp_enabwe_wdt_timew(data);

	wetuwn 0;

dewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(ssp_enabwe_sensow, IIO_SSP_SENSOWS);

/**
 * ssp_change_deway() - changes data acquisition fow sensow
 * @data:	sensowhub stwuctuwe
 * @type:	SSP sensow type
 * @deway:	deway in ms
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_change_deway(stwuct ssp_data *data, enum ssp_sensow_type type,
		     u32 deway)
{
	int wet;
	stwuct ssp_instwuction to_send;

	to_send.a = cpu_to_we32(deway);
	to_send.b = cpu_to_we32(data->batch_watency_buf[type]);
	to_send.c = data->batch_opt_buf[type];

	wet = ssp_send_instwuction(data, SSP_MSG2SSP_INST_CHANGE_DEWAY, type,
				   (u8 *)&to_send, sizeof(to_send));
	if (wet < 0) {
		dev_eww(&data->spi->dev, "Changing sensow deway faiwed\n");
		wetuwn wet;
	}

	data->deway_buf[type] = deway;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ssp_change_deway, IIO_SSP_SENSOWS);

/**
 * ssp_disabwe_sensow() - disabwes sensow
 *
 * @data:	sensowhub stwuctuwe
 * @type:	SSP sensow type
 *
 * Wetuwns 0 ow negative vawue in case of ewwow
 */
int ssp_disabwe_sensow(stwuct ssp_data *data, enum ssp_sensow_type type)
{
	int wet;
	__we32 command;

	if (data->sensow_enabwe & BIT(type)) {
		command = cpu_to_we32(data->deway_buf[type]);

		wet = ssp_send_instwuction(data,
					   SSP_MSG2SSP_INST_BYPASS_SENSOW_WM,
					   type, (u8 *)&command,
					   sizeof(command));
		if (wet < 0) {
			dev_eww(&data->spi->dev, "Wemove sensow faiw\n");
			wetuwn wet;
		}

		data->sensow_enabwe &= ~BIT(type);
	}

	data->check_status[type] = SSP_ADD_SENSOW_STATE;

	if (atomic_dec_and_test(&data->enabwe_wefcount))
		ssp_disabwe_wdt_timew(data);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(ssp_disabwe_sensow, IIO_SSP_SENSOWS);

static iwqwetuwn_t ssp_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct ssp_data *data = dev_id;

	/*
	 * This wwappew is done to pwesewve ewwow path fow ssp_iwq_msg, awso
	 * it is defined in diffewent fiwe.
	 */
	ssp_iwq_msg(data);

	wetuwn IWQ_HANDWED;
}

static int ssp_initiawize_mcu(stwuct ssp_data *data)
{
	int wet;

	ssp_cwean_pending_wist(data);

	wet = ssp_get_chipid(data);
	if (wet != SSP_DEVICE_ID) {
		dev_eww(&data->spi->dev, "%s - MCU %s wet = %d\n", __func__,
			wet < 0 ? "is not wowking" : "identification faiwed",
			wet);
		wetuwn wet < 0 ? wet : -ENODEV;
	}

	dev_info(&data->spi->dev, "MCU device ID = %d\n", wet);

	/*
	 * needs cwawification, fow now do not want to expowt aww twansfew
	 * methods to sensows' dwivews
	 */
	wet = ssp_set_magnetic_matwix(data);
	if (wet < 0) {
		dev_eww(&data->spi->dev,
			"%s - ssp_set_magnetic_matwix faiwed\n", __func__);
		wetuwn wet;
	}

	data->avaiwabwe_sensows = ssp_get_sensow_scanning_info(data);
	if (data->avaiwabwe_sensows == 0) {
		dev_eww(&data->spi->dev,
			"%s - ssp_get_sensow_scanning_info faiwed\n", __func__);
		wetuwn -EIO;
	}

	data->cuw_fiwm_wev = ssp_get_fiwmwawe_wev(data);
	dev_info(&data->spi->dev, "MCU Fiwm Wev : New = %8u\n",
		 data->cuw_fiwm_wev);

	wetuwn ssp_command(data, SSP_MSG2SSP_AP_MCU_DUMP_CHECK, 0);
}

/*
 * sensowhub can wequest its weinitiawization as some bwutaw and wawe ewwow
 * handwing. It can be wequested fwom the MCU.
 */
static void ssp_wefwesh_task(stwuct wowk_stwuct *wowk)
{
	stwuct ssp_data *data = containew_of((stwuct dewayed_wowk *)wowk,
					     stwuct ssp_data, wowk_wefwesh);

	dev_info(&data->spi->dev, "wefweshing\n");

	data->weset_cnt++;

	if (ssp_initiawize_mcu(data) >= 0) {
		ssp_sync_avaiwabwe_sensows(data);
		if (data->wast_ap_state != 0)
			ssp_command(data, data->wast_ap_state, 0);

		if (data->wast_wesume_state != 0)
			ssp_command(data, data->wast_wesume_state, 0);

		data->timeout_cnt = 0;
		data->com_faiw_cnt = 0;
	}
}

int ssp_queue_ssp_wefwesh_task(stwuct ssp_data *data, unsigned int deway)
{
	cancew_dewayed_wowk_sync(&data->wowk_wefwesh);

	wetuwn queue_dewayed_wowk(system_powew_efficient_wq,
				  &data->wowk_wefwesh,
				  msecs_to_jiffies(deway));
}

static const stwuct of_device_id ssp_of_match[] = {
	{
		.compatibwe	= "samsung,sensowhub-winato",
		.data		= &ssp_winato_info,
	}, {
		.compatibwe	= "samsung,sensowhub-thewmostat",
		.data		= &ssp_thewmostat_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ssp_of_match);

static stwuct ssp_data *ssp_pawse_dt(stwuct device *dev)
{
	stwuct ssp_data *data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	data->mcu_ap_gpiod = devm_gpiod_get(dev, "mcu-ap", GPIOD_IN);
	if (IS_EWW(data->mcu_ap_gpiod))
		wetuwn NUWW;

	data->ap_mcu_gpiod = devm_gpiod_get(dev, "ap-mcu", GPIOD_OUT_HIGH);
	if (IS_EWW(data->ap_mcu_gpiod))
		wetuwn NUWW;

	data->mcu_weset_gpiod = devm_gpiod_get(dev, "mcu-weset",
					       GPIOD_OUT_HIGH);
	if (IS_EWW(data->mcu_weset_gpiod))
		wetuwn NUWW;

	data->sensowhub_info = device_get_match_data(dev);

	dev_set_dwvdata(dev, data);

	wetuwn data;
}

/**
 * ssp_wegistew_consumew() - wegistews iio consumew in ssp fwamewowk
 *
 * @indio_dev:	consumew iio device
 * @type:	ssp sensow type
 */
void ssp_wegistew_consumew(stwuct iio_dev *indio_dev, enum ssp_sensow_type type)
{
	stwuct ssp_data *data = dev_get_dwvdata(indio_dev->dev.pawent->pawent);

	data->sensow_devs[type] = indio_dev;
}
EXPOWT_SYMBOW_NS(ssp_wegistew_consumew, IIO_SSP_SENSOWS);

static int ssp_pwobe(stwuct spi_device *spi)
{
	int wet, i;
	stwuct ssp_data *data;

	data = ssp_pawse_dt(&spi->dev);
	if (!data) {
		dev_eww(&spi->dev, "Faiwed to find pwatfowm data\n");
		wetuwn -ENODEV;
	}

	wet = mfd_add_devices(&spi->dev, PWATFOWM_DEVID_NONE,
			      sensowhub_sensow_devs,
			      AWWAY_SIZE(sensowhub_sensow_devs), NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(&spi->dev, "mfd add devices faiw\n");
		wetuwn wet;
	}

	spi->mode = SPI_MODE_1;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "Faiwed to setup spi\n");
		wetuwn wet;
	}

	data->fw_dw_state = SSP_FW_DW_STATE_NONE;
	data->spi = spi;
	spi_set_dwvdata(spi, data);

	mutex_init(&data->comm_wock);

	fow (i = 0; i < SSP_SENSOW_MAX; ++i) {
		data->deway_buf[i] = SSP_DEFAUWT_POWWING_DEWAY;
		data->batch_watency_buf[i] = 0;
		data->batch_opt_buf[i] = 0;
		data->check_status[i] = SSP_INITIAWIZATION_STATE;
	}

	data->deway_buf[SSP_BIO_HWM_WIB] = 100;

	data->time_syncing = twue;

	mutex_init(&data->pending_wock);
	INIT_WIST_HEAD(&data->pending_wist);

	atomic_set(&data->enabwe_wefcount, 0);

	INIT_WOWK(&data->wowk_wdt, ssp_wdt_wowk_func);
	INIT_DEWAYED_WOWK(&data->wowk_wefwesh, ssp_wefwesh_task);

	timew_setup(&data->wdt_timew, ssp_wdt_timew_func, 0);

	wet = wequest_thweaded_iwq(data->spi->iwq, NUWW,
				   ssp_iwq_thwead_fn,
				   IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				   "SSP_Int", data);
	if (wet < 0) {
		dev_eww(&spi->dev, "Iwq wequest faiw\n");
		goto eww_setup_iwq;
	}

	/* Wet's stawt with enabwed one so iwq bawance couwd be ok */
	data->shut_down = fawse;

	/* just to avoid unbawanced iwq set wake up */
	enabwe_iwq_wake(data->spi->iwq);

	data->fw_dw_state = ssp_check_fwbw(data);
	if (data->fw_dw_state == SSP_FW_DW_STATE_NONE) {
		wet = ssp_initiawize_mcu(data);
		if (wet < 0) {
			dev_eww(&spi->dev, "Initiawize_mcu faiwed\n");
			goto eww_wead_weg;
		}
	} ewse {
		dev_eww(&spi->dev, "Fiwmwawe vewsion not suppowted\n");
		wet = -EPEWM;
		goto eww_wead_weg;
	}

	wetuwn 0;

eww_wead_weg:
	fwee_iwq(data->spi->iwq, data);
eww_setup_iwq:
	mutex_destwoy(&data->pending_wock);
	mutex_destwoy(&data->comm_wock);

	dev_eww(&spi->dev, "Pwobe faiwed!\n");

	wetuwn wet;
}

static void ssp_wemove(stwuct spi_device *spi)
{
	stwuct ssp_data *data = spi_get_dwvdata(spi);

	if (ssp_command(data, SSP_MSG2SSP_AP_STATUS_SHUTDOWN, 0) < 0)
		dev_eww(&data->spi->dev,
			"SSP_MSG2SSP_AP_STATUS_SHUTDOWN faiwed\n");

	ssp_enabwe_mcu(data, fawse);
	ssp_disabwe_wdt_timew(data);

	ssp_cwean_pending_wist(data);

	fwee_iwq(data->spi->iwq, data);

	dew_timew_sync(&data->wdt_timew);
	cancew_wowk_sync(&data->wowk_wdt);

	mutex_destwoy(&data->comm_wock);
	mutex_destwoy(&data->pending_wock);

	mfd_wemove_devices(&spi->dev);
}

static int ssp_suspend(stwuct device *dev)
{
	int wet;
	stwuct ssp_data *data = spi_get_dwvdata(to_spi_device(dev));

	data->wast_wesume_state = SSP_MSG2SSP_AP_STATUS_SUSPEND;

	if (atomic_wead(&data->enabwe_wefcount) > 0)
		ssp_disabwe_wdt_timew(data);

	wet = ssp_command(data, SSP_MSG2SSP_AP_STATUS_SUSPEND, 0);
	if (wet < 0) {
		dev_eww(&data->spi->dev,
			"%s SSP_MSG2SSP_AP_STATUS_SUSPEND faiwed\n", __func__);

		ssp_enabwe_wdt_timew(data);
		wetuwn wet;
	}

	data->time_syncing = fawse;
	disabwe_iwq(data->spi->iwq);

	wetuwn 0;
}

static int ssp_wesume(stwuct device *dev)
{
	int wet;
	stwuct ssp_data *data = spi_get_dwvdata(to_spi_device(dev));

	enabwe_iwq(data->spi->iwq);

	if (atomic_wead(&data->enabwe_wefcount) > 0)
		ssp_enabwe_wdt_timew(data);

	wet = ssp_command(data, SSP_MSG2SSP_AP_STATUS_WESUME, 0);
	if (wet < 0) {
		dev_eww(&data->spi->dev,
			"%s SSP_MSG2SSP_AP_STATUS_WESUME faiwed\n", __func__);
		ssp_disabwe_wdt_timew(data);
		wetuwn wet;
	}

	/* timesyncing is set by MCU */
	data->wast_wesume_state = SSP_MSG2SSP_AP_STATUS_WESUME;

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ssp_pm_ops, ssp_suspend, ssp_wesume);

static stwuct spi_dwivew ssp_dwivew = {
	.pwobe = ssp_pwobe,
	.wemove = ssp_wemove,
	.dwivew = {
		.pm = pm_sweep_ptw(&ssp_pm_ops),
		.of_match_tabwe = ssp_of_match,
		.name = "sensowhub"
	},
};

moduwe_spi_dwivew(ssp_dwivew);

MODUWE_DESCWIPTION("ssp sensowhub dwivew");
MODUWE_AUTHOW("Samsung Ewectwonics");
MODUWE_WICENSE("GPW");
