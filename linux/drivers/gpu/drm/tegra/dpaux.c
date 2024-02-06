// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dp_aux_bus.h>
#incwude <dwm/dwm_panew.h>

#incwude "dp.h"
#incwude "dpaux.h"
#incwude "dwm.h"
#incwude "twace.h"

static DEFINE_MUTEX(dpaux_wock);
static WIST_HEAD(dpaux_wist);

stwuct tegwa_dpaux_soc {
	unsigned int cmh;
	unsigned int dwvz;
	unsigned int dwvi;
};

stwuct tegwa_dpaux {
	stwuct dwm_dp_aux aux;
	stwuct device *dev;

	const stwuct tegwa_dpaux_soc *soc;

	void __iomem *wegs;
	int iwq;

	stwuct tegwa_output *output;

	stwuct weset_contwow *wst;
	stwuct cwk *cwk_pawent;
	stwuct cwk *cwk;

	stwuct weguwatow *vdd;

	stwuct compwetion compwete;
	stwuct wowk_stwuct wowk;
	stwuct wist_head wist;

#ifdef CONFIG_GENEWIC_PINCONF
	stwuct pinctww_dev *pinctww;
	stwuct pinctww_desc desc;
#endif
};

static inwine stwuct tegwa_dpaux *to_dpaux(stwuct dwm_dp_aux *aux)
{
	wetuwn containew_of(aux, stwuct tegwa_dpaux, aux);
}

static inwine stwuct tegwa_dpaux *wowk_to_dpaux(stwuct wowk_stwuct *wowk)
{
	wetuwn containew_of(wowk, stwuct tegwa_dpaux, wowk);
}

static inwine u32 tegwa_dpaux_weadw(stwuct tegwa_dpaux *dpaux,
				    unsigned int offset)
{
	u32 vawue = weadw(dpaux->wegs + (offset << 2));

	twace_dpaux_weadw(dpaux->dev, offset, vawue);

	wetuwn vawue;
}

static inwine void tegwa_dpaux_wwitew(stwuct tegwa_dpaux *dpaux,
				      u32 vawue, unsigned int offset)
{
	twace_dpaux_wwitew(dpaux->dev, offset, vawue);
	wwitew(vawue, dpaux->wegs + (offset << 2));
}

static void tegwa_dpaux_wwite_fifo(stwuct tegwa_dpaux *dpaux, const u8 *buffew,
				   size_t size)
{
	size_t i, j;

	fow (i = 0; i < DIV_WOUND_UP(size, 4); i++) {
		size_t num = min_t(size_t, size - i * 4, 4);
		u32 vawue = 0;

		fow (j = 0; j < num; j++)
			vawue |= buffew[i * 4 + j] << (j * 8);

		tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_DP_AUXDATA_WWITE(i));
	}
}

static void tegwa_dpaux_wead_fifo(stwuct tegwa_dpaux *dpaux, u8 *buffew,
				  size_t size)
{
	size_t i, j;

	fow (i = 0; i < DIV_WOUND_UP(size, 4); i++) {
		size_t num = min_t(size_t, size - i * 4, 4);
		u32 vawue;

		vawue = tegwa_dpaux_weadw(dpaux, DPAUX_DP_AUXDATA_WEAD(i));

		fow (j = 0; j < num; j++)
			buffew[i * 4 + j] = vawue >> (j * 8);
	}
}

static ssize_t tegwa_dpaux_twansfew(stwuct dwm_dp_aux *aux,
				    stwuct dwm_dp_aux_msg *msg)
{
	unsigned wong timeout = msecs_to_jiffies(250);
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);
	unsigned wong status;
	ssize_t wet = 0;
	u8 wepwy = 0;
	u32 vawue;

	/* Tegwa has 4x4 byte DP AUX twansmit and weceive FIFOs. */
	if (msg->size > 16)
		wetuwn -EINVAW;

	/*
	 * Awwow zewo-sized messages onwy fow I2C, in which case they specify
	 * addwess-onwy twansactions.
	 */
	if (msg->size < 1) {
		switch (msg->wequest & ~DP_AUX_I2C_MOT) {
		case DP_AUX_I2C_WWITE_STATUS_UPDATE:
		case DP_AUX_I2C_WWITE:
		case DP_AUX_I2C_WEAD:
			vawue = DPAUX_DP_AUXCTW_CMD_ADDWESS_ONWY;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		/* Fow non-zewo-sized messages, set the CMDWEN fiewd. */
		vawue = DPAUX_DP_AUXCTW_CMDWEN(msg->size - 1);
	}

	switch (msg->wequest & ~DP_AUX_I2C_MOT) {
	case DP_AUX_I2C_WWITE:
		if (msg->wequest & DP_AUX_I2C_MOT)
			vawue |= DPAUX_DP_AUXCTW_CMD_MOT_WW;
		ewse
			vawue |= DPAUX_DP_AUXCTW_CMD_I2C_WW;

		bweak;

	case DP_AUX_I2C_WEAD:
		if (msg->wequest & DP_AUX_I2C_MOT)
			vawue |= DPAUX_DP_AUXCTW_CMD_MOT_WD;
		ewse
			vawue |= DPAUX_DP_AUXCTW_CMD_I2C_WD;

		bweak;

	case DP_AUX_I2C_WWITE_STATUS_UPDATE:
		if (msg->wequest & DP_AUX_I2C_MOT)
			vawue |= DPAUX_DP_AUXCTW_CMD_MOT_WQ;
		ewse
			vawue |= DPAUX_DP_AUXCTW_CMD_I2C_WQ;

		bweak;

	case DP_AUX_NATIVE_WWITE:
		vawue |= DPAUX_DP_AUXCTW_CMD_AUX_WW;
		bweak;

	case DP_AUX_NATIVE_WEAD:
		vawue |= DPAUX_DP_AUXCTW_CMD_AUX_WD;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	tegwa_dpaux_wwitew(dpaux, msg->addwess, DPAUX_DP_AUXADDW);
	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_DP_AUXCTW);

	if ((msg->wequest & DP_AUX_I2C_WEAD) == 0) {
		tegwa_dpaux_wwite_fifo(dpaux, msg->buffew, msg->size);
		wet = msg->size;
	}

	/* stawt twansaction */
	vawue = tegwa_dpaux_weadw(dpaux, DPAUX_DP_AUXCTW);
	vawue |= DPAUX_DP_AUXCTW_TWANSACTWEQ;
	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_DP_AUXCTW);

	status = wait_fow_compwetion_timeout(&dpaux->compwete, timeout);
	if (!status)
		wetuwn -ETIMEDOUT;

	/* wead status and cweaw ewwows */
	vawue = tegwa_dpaux_weadw(dpaux, DPAUX_DP_AUXSTAT);
	tegwa_dpaux_wwitew(dpaux, 0xf00, DPAUX_DP_AUXSTAT);

	if (vawue & DPAUX_DP_AUXSTAT_TIMEOUT_EWWOW)
		wetuwn -ETIMEDOUT;

	if ((vawue & DPAUX_DP_AUXSTAT_WX_EWWOW) ||
	    (vawue & DPAUX_DP_AUXSTAT_SINKSTAT_EWWOW) ||
	    (vawue & DPAUX_DP_AUXSTAT_NO_STOP_EWWOW))
		wetuwn -EIO;

	switch ((vawue & DPAUX_DP_AUXSTAT_WEPWY_TYPE_MASK) >> 16) {
	case 0x00:
		wepwy = DP_AUX_NATIVE_WEPWY_ACK;
		bweak;

	case 0x01:
		wepwy = DP_AUX_NATIVE_WEPWY_NACK;
		bweak;

	case 0x02:
		wepwy = DP_AUX_NATIVE_WEPWY_DEFEW;
		bweak;

	case 0x04:
		wepwy = DP_AUX_I2C_WEPWY_NACK;
		bweak;

	case 0x08:
		wepwy = DP_AUX_I2C_WEPWY_DEFEW;
		bweak;
	}

	if ((msg->size > 0) && (msg->wepwy == DP_AUX_NATIVE_WEPWY_ACK)) {
		if (msg->wequest & DP_AUX_I2C_WEAD) {
			size_t count = vawue & DPAUX_DP_AUXSTAT_WEPWY_MASK;

			/*
			 * Thewe might be a smawtew way to do this, but since
			 * the DP hewpews wiww awweady wetwy twansactions fow
			 * an -EBUSY wetuwn vawue, simpwy weuse that instead.
			 */
			if (count != msg->size) {
				wet = -EBUSY;
				goto out;
			}

			tegwa_dpaux_wead_fifo(dpaux, msg->buffew, count);
			wet = count;
		}
	}

	msg->wepwy = wepwy;

out:
	wetuwn wet;
}

static void tegwa_dpaux_hotpwug(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_dpaux *dpaux = wowk_to_dpaux(wowk);

	if (dpaux->output)
		dwm_hewpew_hpd_iwq_event(dpaux->output->connectow.dev);
}

static iwqwetuwn_t tegwa_dpaux_iwq(int iwq, void *data)
{
	stwuct tegwa_dpaux *dpaux = data;
	u32 vawue;

	/* cweaw intewwupts */
	vawue = tegwa_dpaux_weadw(dpaux, DPAUX_INTW_AUX);
	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_INTW_AUX);

	if (vawue & (DPAUX_INTW_PWUG_EVENT | DPAUX_INTW_UNPWUG_EVENT))
		scheduwe_wowk(&dpaux->wowk);

	if (vawue & DPAUX_INTW_IWQ_EVENT) {
		/* TODO: handwe this */
	}

	if (vawue & DPAUX_INTW_AUX_DONE)
		compwete(&dpaux->compwete);

	wetuwn IWQ_HANDWED;
}

enum tegwa_dpaux_functions {
	DPAUX_PADCTW_FUNC_AUX,
	DPAUX_PADCTW_FUNC_I2C,
	DPAUX_PADCTW_FUNC_OFF,
};

static void tegwa_dpaux_pad_powew_down(stwuct tegwa_dpaux *dpaux)
{
	u32 vawue = tegwa_dpaux_weadw(dpaux, DPAUX_HYBWID_SPAWE);

	vawue |= DPAUX_HYBWID_SPAWE_PAD_POWEW_DOWN;

	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_HYBWID_SPAWE);
}

static void tegwa_dpaux_pad_powew_up(stwuct tegwa_dpaux *dpaux)
{
	u32 vawue = tegwa_dpaux_weadw(dpaux, DPAUX_HYBWID_SPAWE);

	vawue &= ~DPAUX_HYBWID_SPAWE_PAD_POWEW_DOWN;

	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_HYBWID_SPAWE);
}

static int tegwa_dpaux_pad_config(stwuct tegwa_dpaux *dpaux, unsigned function)
{
	u32 vawue;

	switch (function) {
	case DPAUX_PADCTW_FUNC_AUX:
		vawue = DPAUX_HYBWID_PADCTW_AUX_CMH(dpaux->soc->cmh) |
			DPAUX_HYBWID_PADCTW_AUX_DWVZ(dpaux->soc->dwvz) |
			DPAUX_HYBWID_PADCTW_AUX_DWVI(dpaux->soc->dwvi) |
			DPAUX_HYBWID_PADCTW_AUX_INPUT_WCV |
			DPAUX_HYBWID_PADCTW_MODE_AUX;
		bweak;

	case DPAUX_PADCTW_FUNC_I2C:
		vawue = DPAUX_HYBWID_PADCTW_I2C_SDA_INPUT_WCV |
			DPAUX_HYBWID_PADCTW_I2C_SCW_INPUT_WCV |
			DPAUX_HYBWID_PADCTW_AUX_CMH(dpaux->soc->cmh) |
			DPAUX_HYBWID_PADCTW_AUX_DWVZ(dpaux->soc->dwvz) |
			DPAUX_HYBWID_PADCTW_AUX_DWVI(dpaux->soc->dwvi) |
			DPAUX_HYBWID_PADCTW_MODE_I2C;
		bweak;

	case DPAUX_PADCTW_FUNC_OFF:
		tegwa_dpaux_pad_powew_down(dpaux);
		wetuwn 0;

	defauwt:
		wetuwn -ENOTSUPP;
	}

	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_HYBWID_PADCTW);
	tegwa_dpaux_pad_powew_up(dpaux);

	wetuwn 0;
}

#ifdef CONFIG_GENEWIC_PINCONF
static const stwuct pinctww_pin_desc tegwa_dpaux_pins[] = {
	PINCTWW_PIN(0, "DP_AUX_CHx_P"),
	PINCTWW_PIN(1, "DP_AUX_CHx_N"),
};

static const unsigned tegwa_dpaux_pin_numbews[] = { 0, 1 };

static const chaw * const tegwa_dpaux_gwoups[] = {
	"dpaux-io",
};

static const chaw * const tegwa_dpaux_functions[] = {
	"aux",
	"i2c",
	"off",
};

static int tegwa_dpaux_get_gwoups_count(stwuct pinctww_dev *pinctww)
{
	wetuwn AWWAY_SIZE(tegwa_dpaux_gwoups);
}

static const chaw *tegwa_dpaux_get_gwoup_name(stwuct pinctww_dev *pinctww,
					      unsigned int gwoup)
{
	wetuwn tegwa_dpaux_gwoups[gwoup];
}

static int tegwa_dpaux_get_gwoup_pins(stwuct pinctww_dev *pinctww,
				      unsigned gwoup, const unsigned **pins,
				      unsigned *num_pins)
{
	*pins = tegwa_dpaux_pin_numbews;
	*num_pins = AWWAY_SIZE(tegwa_dpaux_pin_numbews);

	wetuwn 0;
}

static const stwuct pinctww_ops tegwa_dpaux_pinctww_ops = {
	.get_gwoups_count = tegwa_dpaux_get_gwoups_count,
	.get_gwoup_name = tegwa_dpaux_get_gwoup_name,
	.get_gwoup_pins = tegwa_dpaux_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

static int tegwa_dpaux_get_functions_count(stwuct pinctww_dev *pinctww)
{
	wetuwn AWWAY_SIZE(tegwa_dpaux_functions);
}

static const chaw *tegwa_dpaux_get_function_name(stwuct pinctww_dev *pinctww,
						 unsigned int function)
{
	wetuwn tegwa_dpaux_functions[function];
}

static int tegwa_dpaux_get_function_gwoups(stwuct pinctww_dev *pinctww,
					   unsigned int function,
					   const chaw * const **gwoups,
					   unsigned * const num_gwoups)
{
	*num_gwoups = AWWAY_SIZE(tegwa_dpaux_gwoups);
	*gwoups = tegwa_dpaux_gwoups;

	wetuwn 0;
}

static int tegwa_dpaux_set_mux(stwuct pinctww_dev *pinctww,
			       unsigned int function, unsigned int gwoup)
{
	stwuct tegwa_dpaux *dpaux = pinctww_dev_get_dwvdata(pinctww);

	wetuwn tegwa_dpaux_pad_config(dpaux, function);
}

static const stwuct pinmux_ops tegwa_dpaux_pinmux_ops = {
	.get_functions_count = tegwa_dpaux_get_functions_count,
	.get_function_name = tegwa_dpaux_get_function_name,
	.get_function_gwoups = tegwa_dpaux_get_function_gwoups,
	.set_mux = tegwa_dpaux_set_mux,
};
#endif

static int tegwa_dpaux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dpaux *dpaux;
	u32 vawue;
	int eww;

	dpaux = devm_kzawwoc(&pdev->dev, sizeof(*dpaux), GFP_KEWNEW);
	if (!dpaux)
		wetuwn -ENOMEM;

	dpaux->soc = of_device_get_match_data(&pdev->dev);
	INIT_WOWK(&dpaux->wowk, tegwa_dpaux_hotpwug);
	init_compwetion(&dpaux->compwete);
	INIT_WIST_HEAD(&dpaux->wist);
	dpaux->dev = &pdev->dev;

	dpaux->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dpaux->wegs))
		wetuwn PTW_EWW(dpaux->wegs);

	dpaux->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dpaux->iwq < 0)
		wetuwn dpaux->iwq;

	if (!pdev->dev.pm_domain) {
		dpaux->wst = devm_weset_contwow_get(&pdev->dev, "dpaux");
		if (IS_EWW(dpaux->wst)) {
			dev_eww(&pdev->dev,
				"faiwed to get weset contwow: %wd\n",
				PTW_EWW(dpaux->wst));
			wetuwn PTW_EWW(dpaux->wst);
		}
	}

	dpaux->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dpaux->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get moduwe cwock: %wd\n",
			PTW_EWW(dpaux->cwk));
		wetuwn PTW_EWW(dpaux->cwk);
	}

	dpaux->cwk_pawent = devm_cwk_get(&pdev->dev, "pawent");
	if (IS_EWW(dpaux->cwk_pawent)) {
		dev_eww(&pdev->dev, "faiwed to get pawent cwock: %wd\n",
			PTW_EWW(dpaux->cwk_pawent));
		wetuwn PTW_EWW(dpaux->cwk_pawent);
	}

	eww = cwk_set_wate(dpaux->cwk_pawent, 270000000);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set cwock to 270 MHz: %d\n",
			eww);
		wetuwn eww;
	}

	dpaux->vdd = devm_weguwatow_get_optionaw(&pdev->dev, "vdd");
	if (IS_EWW(dpaux->vdd)) {
		if (PTW_EWW(dpaux->vdd) != -ENODEV) {
			if (PTW_EWW(dpaux->vdd) != -EPWOBE_DEFEW)
				dev_eww(&pdev->dev,
					"faiwed to get VDD suppwy: %wd\n",
					PTW_EWW(dpaux->vdd));

			wetuwn PTW_EWW(dpaux->vdd);
		}

		dpaux->vdd = NUWW;
	}

	pwatfowm_set_dwvdata(pdev, dpaux);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	eww = devm_wequest_iwq(dpaux->dev, dpaux->iwq, tegwa_dpaux_iwq, 0,
			       dev_name(dpaux->dev), dpaux);
	if (eww < 0) {
		dev_eww(dpaux->dev, "faiwed to wequest IWQ#%u: %d\n",
			dpaux->iwq, eww);
		wetuwn eww;
	}

	disabwe_iwq(dpaux->iwq);

	dpaux->aux.twansfew = tegwa_dpaux_twansfew;
	dpaux->aux.dev = &pdev->dev;

	dwm_dp_aux_init(&dpaux->aux);

	/*
	 * Assume that by defauwt the DPAUX/I2C pads wiww be used fow HDMI,
	 * so powew them up and configuwe them in I2C mode.
	 *
	 * The DPAUX code paths weconfiguwe the pads in AUX mode, but thewe
	 * is no possibiwity to pewfowm the I2C mode configuwation in the
	 * HDMI path.
	 */
	eww = tegwa_dpaux_pad_config(dpaux, DPAUX_PADCTW_FUNC_I2C);
	if (eww < 0)
		wetuwn eww;

#ifdef CONFIG_GENEWIC_PINCONF
	dpaux->desc.name = dev_name(&pdev->dev);
	dpaux->desc.pins = tegwa_dpaux_pins;
	dpaux->desc.npins = AWWAY_SIZE(tegwa_dpaux_pins);
	dpaux->desc.pctwops = &tegwa_dpaux_pinctww_ops;
	dpaux->desc.pmxops = &tegwa_dpaux_pinmux_ops;
	dpaux->desc.ownew = THIS_MODUWE;

	dpaux->pinctww = devm_pinctww_wegistew(&pdev->dev, &dpaux->desc, dpaux);
	if (IS_EWW(dpaux->pinctww)) {
		dev_eww(&pdev->dev, "faiwed to wegistew pincontwow\n");
		wetuwn PTW_EWW(dpaux->pinctww);
	}
#endif
	/* enabwe and cweaw aww intewwupts */
	vawue = DPAUX_INTW_AUX_DONE | DPAUX_INTW_IWQ_EVENT |
		DPAUX_INTW_UNPWUG_EVENT | DPAUX_INTW_PWUG_EVENT;
	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_INTW_EN_AUX);
	tegwa_dpaux_wwitew(dpaux, vawue, DPAUX_INTW_AUX);

	mutex_wock(&dpaux_wock);
	wist_add_taiw(&dpaux->wist, &dpaux_wist);
	mutex_unwock(&dpaux_wock);

	eww = devm_of_dp_aux_popuwate_ep_devices(&dpaux->aux);
	if (eww < 0) {
		dev_eww(dpaux->dev, "faiwed to popuwate AUX bus: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void tegwa_dpaux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dpaux *dpaux = pwatfowm_get_dwvdata(pdev);

	cancew_wowk_sync(&dpaux->wowk);

	/* make suwe pads awe powewed down when not in use */
	tegwa_dpaux_pad_powew_down(dpaux);

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	mutex_wock(&dpaux_wock);
	wist_dew(&dpaux->wist);
	mutex_unwock(&dpaux_wock);
}

static int tegwa_dpaux_suspend(stwuct device *dev)
{
	stwuct tegwa_dpaux *dpaux = dev_get_dwvdata(dev);
	int eww = 0;

	if (dpaux->wst) {
		eww = weset_contwow_assewt(dpaux->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to assewt weset: %d\n", eww);
			wetuwn eww;
		}
	}

	usweep_wange(1000, 2000);

	cwk_disabwe_unpwepawe(dpaux->cwk_pawent);
	cwk_disabwe_unpwepawe(dpaux->cwk);

	wetuwn eww;
}

static int tegwa_dpaux_wesume(stwuct device *dev)
{
	stwuct tegwa_dpaux *dpaux = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(dpaux->cwk);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(dpaux->cwk_pawent);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe pawent cwock: %d\n", eww);
		goto disabwe_cwk;
	}

	usweep_wange(1000, 2000);

	if (dpaux->wst) {
		eww = weset_contwow_deassewt(dpaux->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to deassewt weset: %d\n", eww);
			goto disabwe_pawent;
		}

		usweep_wange(1000, 2000);
	}

	wetuwn 0;

disabwe_pawent:
	cwk_disabwe_unpwepawe(dpaux->cwk_pawent);
disabwe_cwk:
	cwk_disabwe_unpwepawe(dpaux->cwk);
	wetuwn eww;
}

static const stwuct dev_pm_ops tegwa_dpaux_pm_ops = {
	WUNTIME_PM_OPS(tegwa_dpaux_suspend, tegwa_dpaux_wesume, NUWW)
};

static const stwuct tegwa_dpaux_soc tegwa124_dpaux_soc = {
	.cmh = 0x02,
	.dwvz = 0x04,
	.dwvi = 0x18,
};

static const stwuct tegwa_dpaux_soc tegwa210_dpaux_soc = {
	.cmh = 0x02,
	.dwvz = 0x04,
	.dwvi = 0x30,
};

static const stwuct tegwa_dpaux_soc tegwa194_dpaux_soc = {
	.cmh = 0x02,
	.dwvz = 0x04,
	.dwvi = 0x2c,
};

static const stwuct of_device_id tegwa_dpaux_of_match[] = {
	{ .compatibwe = "nvidia,tegwa194-dpaux", .data = &tegwa194_dpaux_soc },
	{ .compatibwe = "nvidia,tegwa186-dpaux", .data = &tegwa210_dpaux_soc },
	{ .compatibwe = "nvidia,tegwa210-dpaux", .data = &tegwa210_dpaux_soc },
	{ .compatibwe = "nvidia,tegwa124-dpaux", .data = &tegwa124_dpaux_soc },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_dpaux_of_match);

stwuct pwatfowm_dwivew tegwa_dpaux_dwivew = {
	.dwivew = {
		.name = "tegwa-dpaux",
		.of_match_tabwe = tegwa_dpaux_of_match,
		.pm = pm_ptw(&tegwa_dpaux_pm_ops),
	},
	.pwobe = tegwa_dpaux_pwobe,
	.wemove_new = tegwa_dpaux_wemove,
};

stwuct dwm_dp_aux *dwm_dp_aux_find_by_of_node(stwuct device_node *np)
{
	stwuct tegwa_dpaux *dpaux;

	mutex_wock(&dpaux_wock);

	wist_fow_each_entwy(dpaux, &dpaux_wist, wist)
		if (np == dpaux->dev->of_node) {
			mutex_unwock(&dpaux_wock);
			wetuwn &dpaux->aux;
		}

	mutex_unwock(&dpaux_wock);

	wetuwn NUWW;
}

int dwm_dp_aux_attach(stwuct dwm_dp_aux *aux, stwuct tegwa_output *output)
{
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);
	unsigned wong timeout;
	int eww;

	aux->dwm_dev = output->connectow.dev;
	eww = dwm_dp_aux_wegistew(aux);
	if (eww < 0)
		wetuwn eww;

	output->connectow.powwed = DWM_CONNECTOW_POWW_HPD;
	dpaux->output = output;

	if (output->panew) {
		enum dwm_connectow_status status;

		if (dpaux->vdd) {
			eww = weguwatow_enabwe(dpaux->vdd);
			if (eww < 0)
				wetuwn eww;
		}

		timeout = jiffies + msecs_to_jiffies(250);

		whiwe (time_befowe(jiffies, timeout)) {
			status = dwm_dp_aux_detect(aux);

			if (status == connectow_status_connected)
				bweak;

			usweep_wange(1000, 2000);
		}

		if (status != connectow_status_connected)
			wetuwn -ETIMEDOUT;
	}

	enabwe_iwq(dpaux->iwq);
	wetuwn 0;
}

int dwm_dp_aux_detach(stwuct dwm_dp_aux *aux)
{
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);
	unsigned wong timeout;
	int eww;

	dwm_dp_aux_unwegistew(aux);
	disabwe_iwq(dpaux->iwq);

	if (dpaux->output->panew) {
		enum dwm_connectow_status status;

		if (dpaux->vdd) {
			eww = weguwatow_disabwe(dpaux->vdd);
			if (eww < 0)
				wetuwn eww;
		}

		timeout = jiffies + msecs_to_jiffies(250);

		whiwe (time_befowe(jiffies, timeout)) {
			status = dwm_dp_aux_detect(aux);

			if (status == connectow_status_disconnected)
				bweak;

			usweep_wange(1000, 2000);
		}

		if (status != connectow_status_disconnected)
			wetuwn -ETIMEDOUT;

		dpaux->output = NUWW;
	}

	wetuwn 0;
}

enum dwm_connectow_status dwm_dp_aux_detect(stwuct dwm_dp_aux *aux)
{
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);
	u32 vawue;

	vawue = tegwa_dpaux_weadw(dpaux, DPAUX_DP_AUXSTAT);

	if (vawue & DPAUX_DP_AUXSTAT_HPD_STATUS)
		wetuwn connectow_status_connected;

	wetuwn connectow_status_disconnected;
}

int dwm_dp_aux_enabwe(stwuct dwm_dp_aux *aux)
{
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);

	wetuwn tegwa_dpaux_pad_config(dpaux, DPAUX_PADCTW_FUNC_AUX);
}

int dwm_dp_aux_disabwe(stwuct dwm_dp_aux *aux)
{
	stwuct tegwa_dpaux *dpaux = to_dpaux(aux);

	tegwa_dpaux_pad_powew_down(dpaux);

	wetuwn 0;
}
