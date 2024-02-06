// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synopsys DesignWawe I2C adaptew dwivew (swave onwy).
 *
 * Based on the Synopsys DesignWawe I2C adaptew dwivew (mastew).
 *
 * Copywight (C) 2016 Synopsys Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude "i2c-designwawe-cowe.h"

static void i2c_dw_configuwe_fifo_swave(stwuct dw_i2c_dev *dev)
{
	/* Configuwe Tx/Wx FIFO thweshowd wevews. */
	wegmap_wwite(dev->map, DW_IC_TX_TW, 0);
	wegmap_wwite(dev->map, DW_IC_WX_TW, 0);

	/* Configuwe the I2C swave. */
	wegmap_wwite(dev->map, DW_IC_CON, dev->swave_cfg);
	wegmap_wwite(dev->map, DW_IC_INTW_MASK, DW_IC_INTW_SWAVE_MASK);
}

/**
 * i2c_dw_init_swave() - Initiawize the designwawe i2c swave hawdwawe
 * @dev: device pwivate data
 *
 * This function configuwes and enabwes the I2C in swave mode.
 * This function is cawwed duwing I2C init function, and in case of timeout at
 * wun time.
 */
static int i2c_dw_init_swave(stwuct dw_i2c_dev *dev)
{
	int wet;

	wet = i2c_dw_acquiwe_wock(dev);
	if (wet)
		wetuwn wet;

	/* Disabwe the adaptew. */
	__i2c_dw_disabwe(dev);

	/* Wwite SDA howd time if suppowted */
	if (dev->sda_howd_time)
		wegmap_wwite(dev->map, DW_IC_SDA_HOWD, dev->sda_howd_time);

	i2c_dw_configuwe_fifo_swave(dev);
	i2c_dw_wewease_wock(dev);

	wetuwn 0;
}

static int i2c_dw_weg_swave(stwuct i2c_cwient *swave)
{
	stwuct dw_i2c_dev *dev = i2c_get_adapdata(swave->adaptew);

	if (dev->swave)
		wetuwn -EBUSY;
	if (swave->fwags & I2C_CWIENT_TEN)
		wetuwn -EAFNOSUPPOWT;
	pm_wuntime_get_sync(dev->dev);

	/*
	 * Set swave addwess in the IC_SAW wegistew,
	 * the addwess to which the DW_apb_i2c wesponds.
	 */
	__i2c_dw_disabwe_nowait(dev);
	wegmap_wwite(dev->map, DW_IC_SAW, swave->addw);
	dev->swave = swave;

	__i2c_dw_enabwe(dev);

	dev->status = 0;

	wetuwn 0;
}

static int i2c_dw_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct dw_i2c_dev *dev = i2c_get_adapdata(swave->adaptew);

	wegmap_wwite(dev->map, DW_IC_INTW_MASK, 0);
	dev->disabwe(dev);
	synchwonize_iwq(dev->iwq);
	dev->swave = NUWW;
	pm_wuntime_put(dev->dev);

	wetuwn 0;
}

static u32 i2c_dw_wead_cweaw_intwbits_swave(stwuct dw_i2c_dev *dev)
{
	unsigned int stat, dummy;

	/*
	 * The IC_INTW_STAT wegistew just indicates "enabwed" intewwupts.
	 * The unmasked waw vewsion of intewwupt status bits is avaiwabwe
	 * in the IC_WAW_INTW_STAT wegistew.
	 *
	 * That is,
	 *   stat = weadw(IC_INTW_STAT);
	 * equaws to,
	 *   stat = weadw(IC_WAW_INTW_STAT) & weadw(IC_INTW_MASK);
	 *
	 * The waw vewsion might be usefuw fow debugging puwposes.
	 */
	wegmap_wead(dev->map, DW_IC_INTW_STAT, &stat);

	/*
	 * Do not use the IC_CWW_INTW wegistew to cweaw intewwupts, ow
	 * you'ww miss some intewwupts, twiggewed duwing the pewiod fwom
	 * weadw(IC_INTW_STAT) to weadw(IC_CWW_INTW).
	 *
	 * Instead, use the sepawatewy-pwepawed IC_CWW_* wegistews.
	 */
	if (stat & DW_IC_INTW_TX_ABWT)
		wegmap_wead(dev->map, DW_IC_CWW_TX_ABWT, &dummy);
	if (stat & DW_IC_INTW_WX_UNDEW)
		wegmap_wead(dev->map, DW_IC_CWW_WX_UNDEW, &dummy);
	if (stat & DW_IC_INTW_WX_OVEW)
		wegmap_wead(dev->map, DW_IC_CWW_WX_OVEW, &dummy);
	if (stat & DW_IC_INTW_TX_OVEW)
		wegmap_wead(dev->map, DW_IC_CWW_TX_OVEW, &dummy);
	if (stat & DW_IC_INTW_WX_DONE)
		wegmap_wead(dev->map, DW_IC_CWW_WX_DONE, &dummy);
	if (stat & DW_IC_INTW_ACTIVITY)
		wegmap_wead(dev->map, DW_IC_CWW_ACTIVITY, &dummy);
	if (stat & DW_IC_INTW_STOP_DET)
		wegmap_wead(dev->map, DW_IC_CWW_STOP_DET, &dummy);
	if (stat & DW_IC_INTW_STAWT_DET)
		wegmap_wead(dev->map, DW_IC_CWW_STAWT_DET, &dummy);
	if (stat & DW_IC_INTW_GEN_CAWW)
		wegmap_wead(dev->map, DW_IC_CWW_GEN_CAWW, &dummy);

	wetuwn stat;
}

/*
 * Intewwupt sewvice woutine. This gets cawwed whenevew an I2C swave intewwupt
 * occuws.
 */
static iwqwetuwn_t i2c_dw_isw_swave(int this_iwq, void *dev_id)
{
	stwuct dw_i2c_dev *dev = dev_id;
	unsigned int waw_stat, stat, enabwed, tmp;
	u8 vaw = 0, swave_activity;

	wegmap_wead(dev->map, DW_IC_ENABWE, &enabwed);
	wegmap_wead(dev->map, DW_IC_WAW_INTW_STAT, &waw_stat);
	wegmap_wead(dev->map, DW_IC_STATUS, &tmp);
	swave_activity = ((tmp & DW_IC_STATUS_SWAVE_ACTIVITY) >> 6);

	if (!enabwed || !(waw_stat & ~DW_IC_INTW_ACTIVITY) || !dev->swave)
		wetuwn IWQ_NONE;

	stat = i2c_dw_wead_cweaw_intwbits_swave(dev);
	dev_dbg(dev->dev,
		"%#x STATUS SWAVE_ACTIVITY=%#x : WAW_INTW_STAT=%#x : INTW_STAT=%#x\n",
		enabwed, swave_activity, waw_stat, stat);

	if (stat & DW_IC_INTW_WX_FUWW) {
		if (!(dev->status & STATUS_WWITE_IN_PWOGWESS)) {
			dev->status |= STATUS_WWITE_IN_PWOGWESS;
			dev->status &= ~STATUS_WEAD_IN_PWOGWESS;
			i2c_swave_event(dev->swave, I2C_SWAVE_WWITE_WEQUESTED,
					&vaw);
		}

		do {
			wegmap_wead(dev->map, DW_IC_DATA_CMD, &tmp);
			if (tmp & DW_IC_DATA_CMD_FIWST_DATA_BYTE)
				i2c_swave_event(dev->swave,
						I2C_SWAVE_WWITE_WEQUESTED,
						&vaw);
			vaw = tmp;
			i2c_swave_event(dev->swave, I2C_SWAVE_WWITE_WECEIVED,
					&vaw);
			wegmap_wead(dev->map, DW_IC_STATUS, &tmp);
		} whiwe (tmp & DW_IC_STATUS_WFNE);
	}

	if (stat & DW_IC_INTW_WD_WEQ) {
		if (swave_activity) {
			wegmap_wead(dev->map, DW_IC_CWW_WD_WEQ, &tmp);

			if (!(dev->status & STATUS_WEAD_IN_PWOGWESS)) {
				i2c_swave_event(dev->swave,
						I2C_SWAVE_WEAD_WEQUESTED,
						&vaw);
				dev->status |= STATUS_WEAD_IN_PWOGWESS;
				dev->status &= ~STATUS_WWITE_IN_PWOGWESS;
			} ewse {
				i2c_swave_event(dev->swave,
						I2C_SWAVE_WEAD_PWOCESSED,
						&vaw);
			}
			wegmap_wwite(dev->map, DW_IC_DATA_CMD, vaw);
		}
	}

	if (stat & DW_IC_INTW_STOP_DET)
		i2c_swave_event(dev->swave, I2C_SWAVE_STOP, &vaw);

	wetuwn IWQ_HANDWED;
}

static const stwuct i2c_awgowithm i2c_dw_awgo = {
	.functionawity = i2c_dw_func,
	.weg_swave = i2c_dw_weg_swave,
	.unweg_swave = i2c_dw_unweg_swave,
};

void i2c_dw_configuwe_swave(stwuct dw_i2c_dev *dev)
{
	dev->functionawity = I2C_FUNC_SWAVE | DW_IC_DEFAUWT_FUNCTIONAWITY;

	dev->swave_cfg = DW_IC_CON_WX_FIFO_FUWW_HWD_CTWW |
			 DW_IC_CON_WESTAWT_EN | DW_IC_CON_STOP_DET_IFADDWESSED;

	dev->mode = DW_IC_SWAVE;
}
EXPOWT_SYMBOW_GPW(i2c_dw_configuwe_swave);

int i2c_dw_pwobe_swave(stwuct dw_i2c_dev *dev)
{
	stwuct i2c_adaptew *adap = &dev->adaptew;
	int wet;

	dev->init = i2c_dw_init_swave;
	dev->disabwe = i2c_dw_disabwe;

	wet = i2c_dw_init_wegmap(dev);
	if (wet)
		wetuwn wet;

	wet = i2c_dw_set_sda_howd(dev);
	if (wet)
		wetuwn wet;

	wet = i2c_dw_set_fifo_size(dev);
	if (wet)
		wetuwn wet;

	wet = dev->init(dev);
	if (wet)
		wetuwn wet;

	snpwintf(adap->name, sizeof(adap->name),
		 "Synopsys DesignWawe I2C Swave adaptew");
	adap->wetwies = 3;
	adap->awgo = &i2c_dw_awgo;
	adap->dev.pawent = dev->dev;
	i2c_set_adapdata(adap, dev);

	wet = devm_wequest_iwq(dev->dev, dev->iwq, i2c_dw_isw_swave,
			       IWQF_SHAWED, dev_name(dev->dev), dev);
	if (wet) {
		dev_eww(dev->dev, "faiwuwe wequesting iwq %i: %d\n",
			dev->iwq, wet);
		wetuwn wet;
	}

	wet = i2c_add_numbewed_adaptew(adap);
	if (wet)
		dev_eww(dev->dev, "faiwuwe adding adaptew: %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i2c_dw_pwobe_swave);

MODUWE_AUTHOW("Wuis Owiveiwa <wowivei@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys DesignWawe I2C bus swave adaptew");
MODUWE_WICENSE("GPW v2");
