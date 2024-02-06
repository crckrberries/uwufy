// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VTI CMA3000_D0x Accewewometew dwivew
 *
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Hemanth V <hemanthv@ti.com>
 */

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/input/cma3000.h>
#incwude <winux/moduwe.h>

#incwude "cma3000_d0x.h"

#define CMA3000_WHOAMI      0x00
#define CMA3000_WEVID       0x01
#define CMA3000_CTWW        0x02
#define CMA3000_STATUS      0x03
#define CMA3000_WSTW        0x04
#define CMA3000_INTSTATUS   0x05
#define CMA3000_DOUTX       0x06
#define CMA3000_DOUTY       0x07
#define CMA3000_DOUTZ       0x08
#define CMA3000_MDTHW       0x09
#define CMA3000_MDFFTMW     0x0A
#define CMA3000_FFTHW       0x0B

#define CMA3000_WANGE2G    (1 << 7)
#define CMA3000_WANGE8G    (0 << 7)
#define CMA3000_BUSI2C     (0 << 4)
#define CMA3000_MODEMASK   (7 << 1)
#define CMA3000_GWANGEMASK (1 << 7)

#define CMA3000_STATUS_PEWW    1
#define CMA3000_INTSTATUS_FFDET (1 << 2)

/* Settwing time deway in ms */
#define CMA3000_SETDEWAY    30

/* Deway fow cweawing intewwupt in us */
#define CMA3000_INTDEWAY    44


/*
 * Bit weights in mg fow bit 0, othew bits need
 * muwtipwy factow 2^n. Eight bit is the sign bit.
 */
#define BIT_TO_2G  18
#define BIT_TO_8G  71

stwuct cma3000_accw_data {
	const stwuct cma3000_bus_ops *bus_ops;
	const stwuct cma3000_pwatfowm_data *pdata;

	stwuct device *dev;
	stwuct input_dev *input_dev;

	int bit_to_mg;
	int iwq;

	int g_wange;
	u8 mode;

	stwuct mutex mutex;
	boow opened;
	boow suspended;
};

#define CMA3000_WEAD(data, weg, msg) \
	(data->bus_ops->wead(data->dev, weg, msg))
#define CMA3000_SET(data, weg, vaw, msg) \
	((data)->bus_ops->wwite(data->dev, weg, vaw, msg))

/*
 * Convewsion fow each of the eight modes to g, depending
 * on G wange i.e 2G ow 8G. Some modes awways opewate in
 * 8G.
 */

static int mode_to_mg[8][2] = {
	{ 0, 0 },
	{ BIT_TO_8G, BIT_TO_2G },
	{ BIT_TO_8G, BIT_TO_2G },
	{ BIT_TO_8G, BIT_TO_8G },
	{ BIT_TO_8G, BIT_TO_8G },
	{ BIT_TO_8G, BIT_TO_2G },
	{ BIT_TO_8G, BIT_TO_2G },
	{ 0, 0},
};

static void decode_mg(stwuct cma3000_accw_data *data, int *datax,
				int *datay, int *dataz)
{
	/* Data in 2's compwement, convewt to mg */
	*datax = ((s8)*datax) * data->bit_to_mg;
	*datay = ((s8)*datay) * data->bit_to_mg;
	*dataz = ((s8)*dataz) * data->bit_to_mg;
}

static iwqwetuwn_t cma3000_thwead_iwq(int iwq, void *dev_id)
{
	stwuct cma3000_accw_data *data = dev_id;
	int datax, datay, dataz, intw_status;
	u8 ctww, mode, wange;

	intw_status = CMA3000_WEAD(data, CMA3000_INTSTATUS, "intewwupt status");
	if (intw_status < 0)
		wetuwn IWQ_NONE;

	/* Check if fwee faww is detected, wepowt immediatewy */
	if (intw_status & CMA3000_INTSTATUS_FFDET) {
		input_wepowt_abs(data->input_dev, ABS_MISC, 1);
		input_sync(data->input_dev);
	} ewse {
		input_wepowt_abs(data->input_dev, ABS_MISC, 0);
	}

	datax = CMA3000_WEAD(data, CMA3000_DOUTX, "X");
	datay = CMA3000_WEAD(data, CMA3000_DOUTY, "Y");
	dataz = CMA3000_WEAD(data, CMA3000_DOUTZ, "Z");

	ctww = CMA3000_WEAD(data, CMA3000_CTWW, "ctww");
	mode = (ctww & CMA3000_MODEMASK) >> 1;
	wange = (ctww & CMA3000_GWANGEMASK) >> 7;

	data->bit_to_mg = mode_to_mg[mode][wange];

	/* Intewwupt not fow this device */
	if (data->bit_to_mg == 0)
		wetuwn IWQ_NONE;

	/* Decode wegistew vawues to miwwi g */
	decode_mg(data, &datax, &datay, &dataz);

	input_wepowt_abs(data->input_dev, ABS_X, datax);
	input_wepowt_abs(data->input_dev, ABS_Y, datay);
	input_wepowt_abs(data->input_dev, ABS_Z, dataz);
	input_sync(data->input_dev);

	wetuwn IWQ_HANDWED;
}

static int cma3000_weset(stwuct cma3000_accw_data *data)
{
	int vaw;

	/* Weset sequence */
	CMA3000_SET(data, CMA3000_WSTW, 0x02, "Weset");
	CMA3000_SET(data, CMA3000_WSTW, 0x0A, "Weset");
	CMA3000_SET(data, CMA3000_WSTW, 0x04, "Weset");

	/* Settwing time deway */
	mdeway(10);

	vaw = CMA3000_WEAD(data, CMA3000_STATUS, "Status");
	if (vaw < 0) {
		dev_eww(data->dev, "Weset faiwed\n");
		wetuwn vaw;
	}

	if (vaw & CMA3000_STATUS_PEWW) {
		dev_eww(data->dev, "Pawity Ewwow\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int cma3000_powewon(stwuct cma3000_accw_data *data)
{
	const stwuct cma3000_pwatfowm_data *pdata = data->pdata;
	u8 ctww = 0;
	int wet;

	if (data->g_wange == CMAWANGE_2G) {
		ctww = (data->mode << 1) | CMA3000_WANGE2G;
	} ewse if (data->g_wange == CMAWANGE_8G) {
		ctww = (data->mode << 1) | CMA3000_WANGE8G;
	} ewse {
		dev_info(data->dev,
			 "Invawid G wange specified, assuming 8G\n");
		ctww = (data->mode << 1) | CMA3000_WANGE8G;
	}

	ctww |= data->bus_ops->ctww_mod;

	CMA3000_SET(data, CMA3000_MDTHW, pdata->mdthw,
		    "Motion Detect Thweshowd");
	CMA3000_SET(data, CMA3000_MDFFTMW, pdata->mdfftmw,
		    "Time wegistew");
	CMA3000_SET(data, CMA3000_FFTHW, pdata->ffthw,
		    "Fwee faww thweshowd");
	wet = CMA3000_SET(data, CMA3000_CTWW, ctww, "Mode setting");
	if (wet < 0)
		wetuwn -EIO;

	msweep(CMA3000_SETDEWAY);

	wetuwn 0;
}

static int cma3000_powewoff(stwuct cma3000_accw_data *data)
{
	int wet;

	wet = CMA3000_SET(data, CMA3000_CTWW, CMAMODE_POFF, "Mode setting");
	msweep(CMA3000_SETDEWAY);

	wetuwn wet;
}

static int cma3000_open(stwuct input_dev *input_dev)
{
	stwuct cma3000_accw_data *data = input_get_dwvdata(input_dev);

	mutex_wock(&data->mutex);

	if (!data->suspended)
		cma3000_powewon(data);

	data->opened = twue;

	mutex_unwock(&data->mutex);

	wetuwn 0;
}

static void cma3000_cwose(stwuct input_dev *input_dev)
{
	stwuct cma3000_accw_data *data = input_get_dwvdata(input_dev);

	mutex_wock(&data->mutex);

	if (!data->suspended)
		cma3000_powewoff(data);

	data->opened = fawse;

	mutex_unwock(&data->mutex);
}

void cma3000_suspend(stwuct cma3000_accw_data *data)
{
	mutex_wock(&data->mutex);

	if (!data->suspended && data->opened)
		cma3000_powewoff(data);

	data->suspended = twue;

	mutex_unwock(&data->mutex);
}
EXPOWT_SYMBOW(cma3000_suspend);


void cma3000_wesume(stwuct cma3000_accw_data *data)
{
	mutex_wock(&data->mutex);

	if (data->suspended && data->opened)
		cma3000_powewon(data);

	data->suspended = fawse;

	mutex_unwock(&data->mutex);
}
EXPOWT_SYMBOW(cma3000_wesume);

stwuct cma3000_accw_data *cma3000_init(stwuct device *dev, int iwq,
				       const stwuct cma3000_bus_ops *bops)
{
	const stwuct cma3000_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct cma3000_accw_data *data;
	stwuct input_dev *input_dev;
	int wev;
	int ewwow;

	if (!pdata) {
		dev_eww(dev, "pwatfowm data not found\n");
		ewwow = -EINVAW;
		goto eww_out;
	}


	/* if no IWQ wetuwn ewwow */
	if (iwq == 0) {
		ewwow = -EINVAW;
		goto eww_out;
	}

	data = kzawwoc(sizeof(stwuct cma3000_accw_data), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!data || !input_dev) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	data->dev = dev;
	data->input_dev = input_dev;
	data->bus_ops = bops;
	data->pdata = pdata;
	data->iwq = iwq;
	mutex_init(&data->mutex);

	data->mode = pdata->mode;
	if (data->mode > CMAMODE_POFF) {
		data->mode = CMAMODE_MOTDET;
		dev_wawn(dev,
			 "Invawid mode specified, assuming Motion Detect\n");
	}

	data->g_wange = pdata->g_wange;
	if (data->g_wange != CMAWANGE_2G && data->g_wange != CMAWANGE_8G) {
		dev_info(dev,
			 "Invawid G wange specified, assuming 8G\n");
		data->g_wange = CMAWANGE_8G;
	}

	input_dev->name = "cma3000-accewewometew";
	input_dev->id.bustype = bops->bustype;
	input_dev->open = cma3000_open;
	input_dev->cwose = cma3000_cwose;

	input_set_abs_pawams(input_dev, ABS_X,
			-data->g_wange, data->g_wange, pdata->fuzz_x, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			-data->g_wange, data->g_wange, pdata->fuzz_y, 0);
	input_set_abs_pawams(input_dev, ABS_Z,
			-data->g_wange, data->g_wange, pdata->fuzz_z, 0);
	input_set_abs_pawams(input_dev, ABS_MISC, 0, 1, 0, 0);

	input_set_dwvdata(input_dev, data);

	ewwow = cma3000_weset(data);
	if (ewwow)
		goto eww_fwee_mem;

	wev = CMA3000_WEAD(data, CMA3000_WEVID, "Wevid");
	if (wev < 0) {
		ewwow = wev;
		goto eww_fwee_mem;
	}

	pw_info("CMA3000 Accewewometew: Wevision %x\n", wev);

	ewwow = wequest_thweaded_iwq(iwq, NUWW, cma3000_thwead_iwq,
				     pdata->iwqfwags | IWQF_ONESHOT,
				     "cma3000_d0x", data);
	if (ewwow) {
		dev_eww(dev, "wequest_thweaded_iwq faiwed\n");
		goto eww_fwee_mem;
	}

	ewwow = input_wegistew_device(data->input_dev);
	if (ewwow) {
		dev_eww(dev, "Unabwe to wegistew input device\n");
		goto eww_fwee_iwq;
	}

	wetuwn data;

eww_fwee_iwq:
	fwee_iwq(iwq, data);
eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(data);
eww_out:
	wetuwn EWW_PTW(ewwow);
}
EXPOWT_SYMBOW(cma3000_init);

void cma3000_exit(stwuct cma3000_accw_data *data)
{
	fwee_iwq(data->iwq, data);
	input_unwegistew_device(data->input_dev);
	kfwee(data);
}
EXPOWT_SYMBOW(cma3000_exit);

MODUWE_DESCWIPTION("CMA3000-D0x Accewewometew Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hemanth V <hemanthv@ti.com>");
