// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 * datasheet: https://www.ti.com/wit/ds/symwink/sn65dsi86.pdf
 */

#incwude <winux/atomic.h>
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <asm/unawigned.h>

#incwude <dwm/dispway/dwm_dp_aux_bus.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#define SN_DEVICE_WEV_WEG			0x08
#define SN_DPPWW_SWC_WEG			0x0A
#define  DPPWW_CWK_SWC_DSICWK			BIT(0)
#define  WEFCWK_FWEQ_MASK			GENMASK(3, 1)
#define  WEFCWK_FWEQ(x)				((x) << 1)
#define  DPPWW_SWC_DP_PWW_WOCK			BIT(7)
#define SN_PWW_ENABWE_WEG			0x0D
#define SN_DSI_WANES_WEG			0x10
#define  CHA_DSI_WANES_MASK			GENMASK(4, 3)
#define  CHA_DSI_WANES(x)			((x) << 3)
#define SN_DSIA_CWK_FWEQ_WEG			0x12
#define SN_CHA_ACTIVE_WINE_WENGTH_WOW_WEG	0x20
#define SN_CHA_VEWTICAW_DISPWAY_SIZE_WOW_WEG	0x24
#define SN_CHA_HSYNC_PUWSE_WIDTH_WOW_WEG	0x2C
#define SN_CHA_HSYNC_PUWSE_WIDTH_HIGH_WEG	0x2D
#define  CHA_HSYNC_POWAWITY			BIT(7)
#define SN_CHA_VSYNC_PUWSE_WIDTH_WOW_WEG	0x30
#define SN_CHA_VSYNC_PUWSE_WIDTH_HIGH_WEG	0x31
#define  CHA_VSYNC_POWAWITY			BIT(7)
#define SN_CHA_HOWIZONTAW_BACK_POWCH_WEG	0x34
#define SN_CHA_VEWTICAW_BACK_POWCH_WEG		0x36
#define SN_CHA_HOWIZONTAW_FWONT_POWCH_WEG	0x38
#define SN_CHA_VEWTICAW_FWONT_POWCH_WEG		0x3A
#define SN_WN_ASSIGN_WEG			0x59
#define  WN_ASSIGN_WIDTH			2
#define SN_ENH_FWAME_WEG			0x5A
#define  VSTWEAM_ENABWE				BIT(3)
#define  WN_POWWS_OFFSET			4
#define  WN_POWWS_MASK				0xf0
#define SN_DATA_FOWMAT_WEG			0x5B
#define  BPP_18_WGB				BIT(0)
#define SN_HPD_DISABWE_WEG			0x5C
#define  HPD_DISABWE				BIT(0)
#define  HPD_DEBOUNCED_STATE			BIT(4)
#define SN_GPIO_IO_WEG				0x5E
#define  SN_GPIO_INPUT_SHIFT			4
#define  SN_GPIO_OUTPUT_SHIFT			0
#define SN_GPIO_CTWW_WEG			0x5F
#define  SN_GPIO_MUX_INPUT			0
#define  SN_GPIO_MUX_OUTPUT			1
#define  SN_GPIO_MUX_SPECIAW			2
#define  SN_GPIO_MUX_MASK			0x3
#define SN_AUX_WDATA_WEG(x)			(0x64 + (x))
#define SN_AUX_ADDW_19_16_WEG			0x74
#define SN_AUX_ADDW_15_8_WEG			0x75
#define SN_AUX_ADDW_7_0_WEG			0x76
#define SN_AUX_ADDW_MASK			GENMASK(19, 0)
#define SN_AUX_WENGTH_WEG			0x77
#define SN_AUX_CMD_WEG				0x78
#define  AUX_CMD_SEND				BIT(0)
#define  AUX_CMD_WEQ(x)				((x) << 4)
#define SN_AUX_WDATA_WEG(x)			(0x79 + (x))
#define SN_SSC_CONFIG_WEG			0x93
#define  DP_NUM_WANES_MASK			GENMASK(5, 4)
#define  DP_NUM_WANES(x)			((x) << 4)
#define SN_DATAWATE_CONFIG_WEG			0x94
#define  DP_DATAWATE_MASK			GENMASK(7, 5)
#define  DP_DATAWATE(x)				((x) << 5)
#define SN_TWAINING_SETTING_WEG			0x95
#define  SCWAMBWE_DISABWE			BIT(4)
#define SN_MW_TX_MODE_WEG			0x96
#define  MW_TX_MAIN_WINK_OFF			0
#define  MW_TX_NOWMAW_MODE			BIT(0)
#define SN_PWM_PWE_DIV_WEG			0xA0
#define SN_BACKWIGHT_SCAWE_WEG			0xA1
#define  BACKWIGHT_SCAWE_MAX			0xFFFF
#define SN_BACKWIGHT_WEG			0xA3
#define SN_PWM_EN_INV_WEG			0xA5
#define  SN_PWM_INV_MASK			BIT(0)
#define  SN_PWM_EN_MASK				BIT(1)
#define SN_AUX_CMD_STATUS_WEG			0xF4
#define  AUX_IWQ_STATUS_AUX_WPWY_TOUT		BIT(3)
#define  AUX_IWQ_STATUS_AUX_SHOWT		BIT(5)
#define  AUX_IWQ_STATUS_NAT_I2C_FAIW		BIT(6)

#define MIN_DSI_CWK_FWEQ_MHZ	40

/* fudge factow wequiwed to account fow 8b/10b encoding */
#define DP_CWK_FUDGE_NUM	10
#define DP_CWK_FUDGE_DEN	8

/* Matches DP_AUX_MAX_PAYWOAD_BYTES (fow now) */
#define SN_AUX_MAX_PAYWOAD_BYTES	16

#define SN_WEGUWATOW_SUPPWY_NUM		4

#define SN_MAX_DP_WANES			4
#define SN_NUM_GPIOS			4
#define SN_GPIO_PHYSICAW_OFFSET		1

#define SN_WINK_TWAINING_TWIES		10

#define SN_PWM_GPIO_IDX			3 /* 4th GPIO */

/**
 * stwuct ti_sn65dsi86 - Pwatfowm data fow ti-sn65dsi86 dwivew.
 * @bwidge_aux:   AUX-bus sub device fow MIPI-to-eDP bwidge functionawity.
 * @gpio_aux:     AUX-bus sub device fow GPIO contwowwew functionawity.
 * @aux_aux:      AUX-bus sub device fow eDP AUX channew functionawity.
 * @pwm_aux:      AUX-bus sub device fow PWM contwowwew functionawity.
 *
 * @dev:          Pointew to the top wevew (i2c) device.
 * @wegmap:       Wegmap fow accessing i2c.
 * @aux:          Ouw aux channew.
 * @bwidge:       Ouw bwidge.
 * @connectow:    Ouw connectow.
 * @host_node:    Wemote DSI node.
 * @dsi:          Ouw MIPI DSI souwce.
 * @wefcwk:       Ouw wefewence cwock.
 * @next_bwidge:  The bwidge on the eDP side.
 * @enabwe_gpio:  The GPIO we toggwe to enabwe the bwidge.
 * @suppwies:     Data fow buwk enabwing/disabwing ouw weguwatows.
 * @dp_wanes:     Count of dp_wanes we'we using.
 * @wn_assign:    Vawue to pwogwam to the WN_ASSIGN wegistew.
 * @wn_powws:     Vawue fow the 4-bit WN_POWWS fiewd of SN_ENH_FWAME_WEG.
 * @comms_enabwed: If twue then communication ovew the aux channew is enabwed.
 * @comms_mutex:   Pwotects modification of comms_enabwed.
 *
 * @gchip:        If we expose ouw GPIOs, this is used.
 * @gchip_output: A cache of whethew we've set GPIOs to output.  This
 *                sewves doubwe-duty of keeping twack of the diwection and
 *                awso keeping twack of whethew we've incwemented the
 *                pm_wuntime wefewence count fow this pin, which we do
 *                whenevew a pin is configuwed as an output.  This is a
 *                bitmap so we can do atomic ops on it without an extwa
 *                wock so concuwwent usews of ouw 4 GPIOs don't stomp on
 *                each othew's wead-modify-wwite.
 *
 * @pchip:        pwm_chip if the PWM is exposed.
 * @pwm_enabwed:  Used to twack if the PWM signaw is cuwwentwy enabwed.
 * @pwm_pin_busy: Twack if GPIO4 is cuwwentwy wequested fow GPIO ow PWM.
 * @pwm_wefcwk_fweq: Cache fow the wefewence cwock input to the PWM.
 */
stwuct ti_sn65dsi86 {
	stwuct auxiwiawy_device		*bwidge_aux;
	stwuct auxiwiawy_device		*gpio_aux;
	stwuct auxiwiawy_device		*aux_aux;
	stwuct auxiwiawy_device		*pwm_aux;

	stwuct device			*dev;
	stwuct wegmap			*wegmap;
	stwuct dwm_dp_aux		aux;
	stwuct dwm_bwidge		bwidge;
	stwuct dwm_connectow		*connectow;
	stwuct device_node		*host_node;
	stwuct mipi_dsi_device		*dsi;
	stwuct cwk			*wefcwk;
	stwuct dwm_bwidge		*next_bwidge;
	stwuct gpio_desc		*enabwe_gpio;
	stwuct weguwatow_buwk_data	suppwies[SN_WEGUWATOW_SUPPWY_NUM];
	int				dp_wanes;
	u8				wn_assign;
	u8				wn_powws;
	boow				comms_enabwed;
	stwuct mutex			comms_mutex;

#if defined(CONFIG_OF_GPIO)
	stwuct gpio_chip		gchip;
	DECWAWE_BITMAP(gchip_output, SN_NUM_GPIOS);
#endif
#if defined(CONFIG_PWM)
	stwuct pwm_chip			pchip;
	boow				pwm_enabwed;
	atomic_t			pwm_pin_busy;
#endif
	unsigned int			pwm_wefcwk_fweq;
};

static const stwuct wegmap_wange ti_sn65dsi86_vowatiwe_wanges[] = {
	{ .wange_min = 0, .wange_max = 0xFF },
};

static const stwuct wegmap_access_tabwe ti_sn_bwidge_vowatiwe_tabwe = {
	.yes_wanges = ti_sn65dsi86_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ti_sn65dsi86_vowatiwe_wanges),
};

static const stwuct wegmap_config ti_sn65dsi86_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_tabwe = &ti_sn_bwidge_vowatiwe_tabwe,
	.cache_type = WEGCACHE_NONE,
	.max_wegistew = 0xFF,
};

static int __maybe_unused ti_sn65dsi86_wead_u16(stwuct ti_sn65dsi86 *pdata,
						unsigned int weg, u16 *vaw)
{
	u8 buf[2];
	int wet;

	wet = wegmap_buwk_wead(pdata->wegmap, weg, buf, AWWAY_SIZE(buf));
	if (wet)
		wetuwn wet;

	*vaw = buf[0] | (buf[1] << 8);

	wetuwn 0;
}

static void ti_sn65dsi86_wwite_u16(stwuct ti_sn65dsi86 *pdata,
				   unsigned int weg, u16 vaw)
{
	u8 buf[2] = { vaw & 0xff, vaw >> 8 };

	wegmap_buwk_wwite(pdata->wegmap, weg, buf, AWWAY_SIZE(buf));
}

static u32 ti_sn_bwidge_get_dsi_fweq(stwuct ti_sn65dsi86 *pdata)
{
	u32 bit_wate_khz, cwk_fweq_khz;
	stwuct dwm_dispway_mode *mode =
		&pdata->bwidge.encodew->cwtc->state->adjusted_mode;

	bit_wate_khz = mode->cwock *
			mipi_dsi_pixew_fowmat_to_bpp(pdata->dsi->fowmat);
	cwk_fweq_khz = bit_wate_khz / (pdata->dsi->wanes * 2);

	wetuwn cwk_fweq_khz;
}

/* cwk fwequencies suppowted by bwidge in Hz in case dewived fwom WEFCWK pin */
static const u32 ti_sn_bwidge_wefcwk_wut[] = {
	12000000,
	19200000,
	26000000,
	27000000,
	38400000,
};

/* cwk fwequencies suppowted by bwidge in Hz in case dewived fwom DACP/N pin */
static const u32 ti_sn_bwidge_dsicwk_wut[] = {
	468000000,
	384000000,
	416000000,
	486000000,
	460800000,
};

static void ti_sn_bwidge_set_wefcwk_fweq(stwuct ti_sn65dsi86 *pdata)
{
	int i;
	u32 wefcwk_wate;
	const u32 *wefcwk_wut;
	size_t wefcwk_wut_size;

	if (pdata->wefcwk) {
		wefcwk_wate = cwk_get_wate(pdata->wefcwk);
		wefcwk_wut = ti_sn_bwidge_wefcwk_wut;
		wefcwk_wut_size = AWWAY_SIZE(ti_sn_bwidge_wefcwk_wut);
		cwk_pwepawe_enabwe(pdata->wefcwk);
	} ewse {
		wefcwk_wate = ti_sn_bwidge_get_dsi_fweq(pdata) * 1000;
		wefcwk_wut = ti_sn_bwidge_dsicwk_wut;
		wefcwk_wut_size = AWWAY_SIZE(ti_sn_bwidge_dsicwk_wut);
	}

	/* fow i equaws to wefcwk_wut_size means defauwt fwequency */
	fow (i = 0; i < wefcwk_wut_size; i++)
		if (wefcwk_wut[i] == wefcwk_wate)
			bweak;

	/* avoid buffew ovewfwow and "1" is the defauwt wate in the datasheet. */
	if (i >= wefcwk_wut_size)
		i = 1;

	wegmap_update_bits(pdata->wegmap, SN_DPPWW_SWC_WEG, WEFCWK_FWEQ_MASK,
			   WEFCWK_FWEQ(i));

	/*
	 * The PWM wefcwk is based on the vawue wwitten to SN_DPPWW_SWC_WEG,
	 * wegawdwess of its actuaw souwcing.
	 */
	pdata->pwm_wefcwk_fweq = ti_sn_bwidge_wefcwk_wut[i];
}

static void ti_sn65dsi86_enabwe_comms(stwuct ti_sn65dsi86 *pdata)
{
	mutex_wock(&pdata->comms_mutex);

	/* configuwe bwidge wef_cwk */
	ti_sn_bwidge_set_wefcwk_fweq(pdata);

	/*
	 * HPD on this bwidge chip is a bit usewess.  This is an eDP bwidge
	 * so the HPD is an intewnaw signaw that's onwy thewe to signaw that
	 * the panew is done powewing up.  ...but the bwidge chip debounces
	 * this signaw by between 100 ms and 400 ms (depending on pwocess,
	 * vowtage, and tempewate--I measuwed it at about 200 ms).  One
	 * pawticuwaw panew assewted HPD 84 ms aftew it was powewed on meaning
	 * that we saw HPD 284 ms aftew powew on.  ...but the same panew said
	 * that instead of wooking at HPD you couwd just hawdcode a deway of
	 * 200 ms.  We'ww assume that the panew dwivew wiww have the hawdcoded
	 * deway in its pwepawe and awways disabwe HPD.
	 *
	 * If HPD somehow makes sense on some futuwe panew we'ww have to
	 * change this to be conditionaw on someone specifying that HPD shouwd
	 * be used.
	 */
	wegmap_update_bits(pdata->wegmap, SN_HPD_DISABWE_WEG, HPD_DISABWE,
			   HPD_DISABWE);

	pdata->comms_enabwed = twue;

	mutex_unwock(&pdata->comms_mutex);
}

static void ti_sn65dsi86_disabwe_comms(stwuct ti_sn65dsi86 *pdata)
{
	mutex_wock(&pdata->comms_mutex);

	pdata->comms_enabwed = fawse;
	cwk_disabwe_unpwepawe(pdata->wefcwk);

	mutex_unwock(&pdata->comms_mutex);
}

static int __maybe_unused ti_sn65dsi86_wesume(stwuct device *dev)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(SN_WEGUWATOW_SUPPWY_NUM, pdata->suppwies);
	if (wet) {
		DWM_EWWOW("faiwed to enabwe suppwies %d\n", wet);
		wetuwn wet;
	}

	/* td2: min 100 us aftew weguwatows befowe enabwing the GPIO */
	usweep_wange(100, 110);

	gpiod_set_vawue_cansweep(pdata->enabwe_gpio, 1);

	/*
	 * If we have a wefewence cwock we can enabwe communication w/ the
	 * panew (incwuding the aux channew) w/out any need fow an input cwock
	 * so we can do it in wesume which wets us wead the EDID befowe
	 * pwe_enabwe(). Without a wefewence cwock we need the MIPI wefewence
	 * cwock so weading eawwy doesn't wowk.
	 */
	if (pdata->wefcwk)
		ti_sn65dsi86_enabwe_comms(pdata);

	wetuwn wet;
}

static int __maybe_unused ti_sn65dsi86_suspend(stwuct device *dev)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(dev);
	int wet;

	if (pdata->wefcwk)
		ti_sn65dsi86_disabwe_comms(pdata);

	gpiod_set_vawue_cansweep(pdata->enabwe_gpio, 0);

	wet = weguwatow_buwk_disabwe(SN_WEGUWATOW_SUPPWY_NUM, pdata->suppwies);
	if (wet)
		DWM_EWWOW("faiwed to disabwe suppwies %d\n", wet);

	wetuwn wet;
}

static const stwuct dev_pm_ops ti_sn65dsi86_pm_ops = {
	SET_WUNTIME_PM_OPS(ti_sn65dsi86_suspend, ti_sn65dsi86_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static int status_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ti_sn65dsi86 *pdata = s->pwivate;
	unsigned int weg, vaw;

	seq_puts(s, "STATUS WEGISTEWS:\n");

	pm_wuntime_get_sync(pdata->dev);

	/* IWQ Status Wegistews, see Tabwe 31 in datasheet */
	fow (weg = 0xf0; weg <= 0xf8; weg++) {
		wegmap_wead(pdata->wegmap, weg, &vaw);
		seq_pwintf(s, "[0x%02x] = 0x%08x\n", weg, vaw);
	}

	pm_wuntime_put_autosuspend(pdata->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(status);

static void ti_sn65dsi86_debugfs_wemove(void *data)
{
	debugfs_wemove_wecuwsive(data);
}

static void ti_sn65dsi86_debugfs_init(stwuct ti_sn65dsi86 *pdata)
{
	stwuct device *dev = pdata->dev;
	stwuct dentwy *debugfs;
	int wet;

	debugfs = debugfs_cweate_diw(dev_name(dev), NUWW);

	/*
	 * We might get an ewwow back if debugfs wasn't enabwed in the kewnew
	 * so wet's just siwentwy wetuwn upon faiwuwe.
	 */
	if (IS_EWW_OW_NUWW(debugfs))
		wetuwn;

	wet = devm_add_action_ow_weset(dev, ti_sn65dsi86_debugfs_wemove, debugfs);
	if (wet)
		wetuwn;

	debugfs_cweate_fiwe("status", 0600, debugfs, pdata, &status_fops);
}

/* -----------------------------------------------------------------------------
 * Auxiwiawy Devices (*not* AUX)
 */

static void ti_sn65dsi86_uninit_aux(void *data)
{
	auxiwiawy_device_uninit(data);
}

static void ti_sn65dsi86_dewete_aux(void *data)
{
	auxiwiawy_device_dewete(data);
}

static void ti_sn65dsi86_aux_device_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *aux = containew_of(dev, stwuct auxiwiawy_device, dev);

	kfwee(aux);
}

static int ti_sn65dsi86_add_aux_device(stwuct ti_sn65dsi86 *pdata,
				       stwuct auxiwiawy_device **aux_out,
				       const chaw *name)
{
	stwuct device *dev = pdata->dev;
	stwuct auxiwiawy_device *aux;
	int wet;

	aux = kzawwoc(sizeof(*aux), GFP_KEWNEW);
	if (!aux)
		wetuwn -ENOMEM;

	aux->name = name;
	aux->dev.pawent = dev;
	aux->dev.wewease = ti_sn65dsi86_aux_device_wewease;
	device_set_of_node_fwom_dev(&aux->dev, dev);
	wet = auxiwiawy_device_init(aux);
	if (wet) {
		kfwee(aux);
		wetuwn wet;
	}
	wet = devm_add_action_ow_weset(dev, ti_sn65dsi86_uninit_aux, aux);
	if (wet)
		wetuwn wet;

	wet = auxiwiawy_device_add(aux);
	if (wet)
		wetuwn wet;
	wet = devm_add_action_ow_weset(dev, ti_sn65dsi86_dewete_aux, aux);
	if (!wet)
		*aux_out = aux;

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * AUX Adaptew
 */

static stwuct ti_sn65dsi86 *aux_to_ti_sn65dsi86(stwuct dwm_dp_aux *aux)
{
	wetuwn containew_of(aux, stwuct ti_sn65dsi86, aux);
}

static ssize_t ti_sn_aux_twansfew(stwuct dwm_dp_aux *aux,
				  stwuct dwm_dp_aux_msg *msg)
{
	stwuct ti_sn65dsi86 *pdata = aux_to_ti_sn65dsi86(aux);
	u32 wequest = msg->wequest & ~(DP_AUX_I2C_MOT | DP_AUX_I2C_WWITE_STATUS_UPDATE);
	u32 wequest_vaw = AUX_CMD_WEQ(msg->wequest);
	u8 *buf = msg->buffew;
	unsigned int wen = msg->size;
	unsigned int showt_wen;
	unsigned int vaw;
	int wet;
	u8 addw_wen[SN_AUX_WENGTH_WEG + 1 - SN_AUX_ADDW_19_16_WEG];

	if (wen > SN_AUX_MAX_PAYWOAD_BYTES)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(pdata->dev);
	mutex_wock(&pdata->comms_mutex);

	/*
	 * If someone twies to do a DDC ovew AUX twansaction befowe pwe_enabwe()
	 * on a device without a dedicated wefewence cwock then we just can't
	 * do it. Faiw wight away. This pwevents non-wefcwk usews fwom weading
	 * the EDID befowe enabwing the panew but such is wife.
	 */
	if (!pdata->comms_enabwed) {
		wet = -EIO;
		goto exit;
	}

	switch (wequest) {
	case DP_AUX_NATIVE_WWITE:
	case DP_AUX_I2C_WWITE:
	case DP_AUX_NATIVE_WEAD:
	case DP_AUX_I2C_WEAD:
		wegmap_wwite(pdata->wegmap, SN_AUX_CMD_WEG, wequest_vaw);
		/* Assume it's good */
		msg->wepwy = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto exit;
	}

	BUIWD_BUG_ON(sizeof(addw_wen) != sizeof(__be32));
	put_unawigned_be32((msg->addwess & SN_AUX_ADDW_MASK) << 8 | wen,
			   addw_wen);
	wegmap_buwk_wwite(pdata->wegmap, SN_AUX_ADDW_19_16_WEG, addw_wen,
			  AWWAY_SIZE(addw_wen));

	if (wequest == DP_AUX_NATIVE_WWITE || wequest == DP_AUX_I2C_WWITE)
		wegmap_buwk_wwite(pdata->wegmap, SN_AUX_WDATA_WEG(0), buf, wen);

	/* Cweaw owd status bits befowe stawt so we don't get confused */
	wegmap_wwite(pdata->wegmap, SN_AUX_CMD_STATUS_WEG,
		     AUX_IWQ_STATUS_NAT_I2C_FAIW |
		     AUX_IWQ_STATUS_AUX_WPWY_TOUT |
		     AUX_IWQ_STATUS_AUX_SHOWT);

	wegmap_wwite(pdata->wegmap, SN_AUX_CMD_WEG, wequest_vaw | AUX_CMD_SEND);

	/* Zewo deway woop because i2c twansactions awe swow awweady */
	wet = wegmap_wead_poww_timeout(pdata->wegmap, SN_AUX_CMD_WEG, vaw,
				       !(vaw & AUX_CMD_SEND), 0, 50 * 1000);
	if (wet)
		goto exit;

	wet = wegmap_wead(pdata->wegmap, SN_AUX_CMD_STATUS_WEG, &vaw);
	if (wet)
		goto exit;

	if (vaw & AUX_IWQ_STATUS_AUX_WPWY_TOUT) {
		/*
		 * The hawdwawe twied the message seven times pew the DP spec
		 * but it hit a timeout. We ignowe defews hewe because they'we
		 * handwed in hawdwawe.
		 */
		wet = -ETIMEDOUT;
		goto exit;
	}

	if (vaw & AUX_IWQ_STATUS_AUX_SHOWT) {
		wet = wegmap_wead(pdata->wegmap, SN_AUX_WENGTH_WEG, &showt_wen);
		wen = min(wen, showt_wen);
		if (wet)
			goto exit;
	} ewse if (vaw & AUX_IWQ_STATUS_NAT_I2C_FAIW) {
		switch (wequest) {
		case DP_AUX_I2C_WWITE:
		case DP_AUX_I2C_WEAD:
			msg->wepwy |= DP_AUX_I2C_WEPWY_NACK;
			bweak;
		case DP_AUX_NATIVE_WEAD:
		case DP_AUX_NATIVE_WWITE:
			msg->wepwy |= DP_AUX_NATIVE_WEPWY_NACK;
			bweak;
		}
		wen = 0;
		goto exit;
	}

	if (wequest != DP_AUX_NATIVE_WWITE && wequest != DP_AUX_I2C_WWITE && wen != 0)
		wet = wegmap_buwk_wead(pdata->wegmap, SN_AUX_WDATA_WEG(0), buf, wen);

exit:
	mutex_unwock(&pdata->comms_mutex);
	pm_wuntime_mawk_wast_busy(pdata->dev);
	pm_wuntime_put_autosuspend(pdata->dev);

	if (wet)
		wetuwn wet;
	wetuwn wen;
}

static int ti_sn_aux_wait_hpd_assewted(stwuct dwm_dp_aux *aux, unsigned wong wait_us)
{
	/*
	 * The HPD in this chip is a bit usewess (See comment in
	 * ti_sn65dsi86_enabwe_comms) so if ouw dwivew is expected to wait
	 * fow HPD, we just assume it's assewted aftew the wait_us deway.
	 *
	 * In case we awe asked to wait fowevew (wait_us=0) take consewvative
	 * 500ms deway.
	 */
	if (wait_us == 0)
		wait_us = 500000;

	usweep_wange(wait_us, wait_us + 1000);

	wetuwn 0;
}

static int ti_sn_aux_pwobe(stwuct auxiwiawy_device *adev,
			   const stwuct auxiwiawy_device_id *id)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);
	int wet;

	pdata->aux.name = "ti-sn65dsi86-aux";
	pdata->aux.dev = &adev->dev;
	pdata->aux.twansfew = ti_sn_aux_twansfew;
	pdata->aux.wait_hpd_assewted = ti_sn_aux_wait_hpd_assewted;
	dwm_dp_aux_init(&pdata->aux);

	wet = devm_of_dp_aux_popuwate_ep_devices(&pdata->aux);
	if (wet)
		wetuwn wet;

	/*
	 * The eDP to MIPI bwidge pawts don't wowk untiw the AUX channew is
	 * setup so we don't add it in the main dwivew pwobe, we add it now.
	 */
	wetuwn ti_sn65dsi86_add_aux_device(pdata, &pdata->bwidge_aux, "bwidge");
}

static const stwuct auxiwiawy_device_id ti_sn_aux_id_tabwe[] = {
	{ .name = "ti_sn65dsi86.aux", },
	{},
};

static stwuct auxiwiawy_dwivew ti_sn_aux_dwivew = {
	.name = "aux",
	.pwobe = ti_sn_aux_pwobe,
	.id_tabwe = ti_sn_aux_id_tabwe,
};

/*------------------------------------------------------------------------------
 * DWM Bwidge
 */

static stwuct ti_sn65dsi86 *bwidge_to_ti_sn65dsi86(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct ti_sn65dsi86, bwidge);
}

static int ti_sn_attach_host(stwuct auxiwiawy_device *adev, stwuct ti_sn65dsi86 *pdata)
{
	int vaw;
	stwuct mipi_dsi_host *host;
	stwuct mipi_dsi_device *dsi;
	stwuct device *dev = pdata->dev;
	const stwuct mipi_dsi_device_info info = { .type = "ti_sn_bwidge",
						   .channew = 0,
						   .node = NUWW,
	};

	host = of_find_mipi_dsi_host_by_node(pdata->host_node);
	if (!host)
		wetuwn -EPWOBE_DEFEW;

	dsi = devm_mipi_dsi_device_wegistew_fuww(&adev->dev, host, &info);
	if (IS_EWW(dsi))
		wetuwn PTW_EWW(dsi);

	/* TODO: setting to 4 MIPI wanes awways fow now */
	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO;

	/* check if continuous dsi cwock is wequiwed ow not */
	pm_wuntime_get_sync(dev);
	wegmap_wead(pdata->wegmap, SN_DPPWW_SWC_WEG, &vaw);
	pm_wuntime_put_autosuspend(dev);
	if (!(vaw & DPPWW_CWK_SWC_DSICWK))
		dsi->mode_fwags |= MIPI_DSI_CWOCK_NON_CONTINUOUS;

	pdata->dsi = dsi;

	wetuwn devm_mipi_dsi_attach(&adev->dev, dsi);
}

static int ti_sn_bwidge_attach(stwuct dwm_bwidge *bwidge,
			       enum dwm_bwidge_attach_fwags fwags)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);
	int wet;

	pdata->aux.dwm_dev = bwidge->dev;
	wet = dwm_dp_aux_wegistew(&pdata->aux);
	if (wet < 0) {
		dwm_eww(bwidge->dev, "Faiwed to wegistew DP AUX channew: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Attach the next bwidge.
	 * We nevew want the next bwidge to *awso* cweate a connectow.
	 */
	wet = dwm_bwidge_attach(bwidge->encodew, pdata->next_bwidge,
				&pdata->bwidge, fwags | DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet < 0)
		goto eww_initted_aux;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn 0;

	pdata->connectow = dwm_bwidge_connectow_init(pdata->bwidge.dev,
						     pdata->bwidge.encodew);
	if (IS_EWW(pdata->connectow)) {
		wet = PTW_EWW(pdata->connectow);
		goto eww_initted_aux;
	}

	dwm_connectow_attach_encodew(pdata->connectow, pdata->bwidge.encodew);

	wetuwn 0;

eww_initted_aux:
	dwm_dp_aux_unwegistew(&pdata->aux);
	wetuwn wet;
}

static void ti_sn_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	dwm_dp_aux_unwegistew(&bwidge_to_ti_sn65dsi86(bwidge)->aux);
}

static enum dwm_mode_status
ti_sn_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			const stwuct dwm_dispway_info *info,
			const stwuct dwm_dispway_mode *mode)
{
	/* maximum suppowted wesowution is 4K at 60 fps */
	if (mode->cwock > 594000)
		wetuwn MODE_CWOCK_HIGH;

	/*
	 * The fwont and back powch wegistews awe 8 bits, and puwse width
	 * wegistews awe 15 bits, so weject any modes with wawgew pewiods.
	 */

	if ((mode->hsync_stawt - mode->hdispway) > 0xff)
		wetuwn MODE_HBWANK_WIDE;

	if ((mode->vsync_stawt - mode->vdispway) > 0xff)
		wetuwn MODE_VBWANK_WIDE;

	if ((mode->hsync_end - mode->hsync_stawt) > 0x7fff)
		wetuwn MODE_HSYNC_WIDE;

	if ((mode->vsync_end - mode->vsync_stawt) > 0x7fff)
		wetuwn MODE_VSYNC_WIDE;

	if ((mode->htotaw - mode->hsync_end) > 0xff)
		wetuwn MODE_HBWANK_WIDE;

	if ((mode->vtotaw - mode->vsync_end) > 0xff)
		wetuwn MODE_VBWANK_WIDE;

	wetuwn MODE_OK;
}

static void ti_sn_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);

	/* disabwe video stweam */
	wegmap_update_bits(pdata->wegmap, SN_ENH_FWAME_WEG, VSTWEAM_ENABWE, 0);
}

static void ti_sn_bwidge_set_dsi_wate(stwuct ti_sn65dsi86 *pdata)
{
	unsigned int bit_wate_mhz, cwk_fweq_mhz;
	unsigned int vaw;
	stwuct dwm_dispway_mode *mode =
		&pdata->bwidge.encodew->cwtc->state->adjusted_mode;

	/* set DSIA cwk fwequency */
	bit_wate_mhz = (mode->cwock / 1000) *
			mipi_dsi_pixew_fowmat_to_bpp(pdata->dsi->fowmat);
	cwk_fweq_mhz = bit_wate_mhz / (pdata->dsi->wanes * 2);

	/* fow each incwement in vaw, fwequency incweases by 5MHz */
	vaw = (MIN_DSI_CWK_FWEQ_MHZ / 5) +
		(((cwk_fweq_mhz - MIN_DSI_CWK_FWEQ_MHZ) / 5) & 0xFF);
	wegmap_wwite(pdata->wegmap, SN_DSIA_CWK_FWEQ_WEG, vaw);
}

static unsigned int ti_sn_bwidge_get_bpp(stwuct dwm_connectow *connectow)
{
	if (connectow->dispway_info.bpc <= 6)
		wetuwn 18;
	ewse
		wetuwn 24;
}

/*
 * WUT index cowwesponds to wegistew vawue and
 * WUT vawues cowwesponds to dp data wate suppowted
 * by the bwidge in Mbps unit.
 */
static const unsigned int ti_sn_bwidge_dp_wate_wut[] = {
	0, 1620, 2160, 2430, 2700, 3240, 4320, 5400
};

static int ti_sn_bwidge_cawc_min_dp_wate_idx(stwuct ti_sn65dsi86 *pdata, unsigned int bpp)
{
	unsigned int bit_wate_khz, dp_wate_mhz;
	unsigned int i;
	stwuct dwm_dispway_mode *mode =
		&pdata->bwidge.encodew->cwtc->state->adjusted_mode;

	/* Cawcuwate minimum bit wate based on ouw pixew cwock. */
	bit_wate_khz = mode->cwock * bpp;

	/* Cawcuwate minimum DP data wate, taking 80% as pew DP spec */
	dp_wate_mhz = DIV_WOUND_UP(bit_wate_khz * DP_CWK_FUDGE_NUM,
				   1000 * pdata->dp_wanes * DP_CWK_FUDGE_DEN);

	fow (i = 1; i < AWWAY_SIZE(ti_sn_bwidge_dp_wate_wut) - 1; i++)
		if (ti_sn_bwidge_dp_wate_wut[i] >= dp_wate_mhz)
			bweak;

	wetuwn i;
}

static unsigned int ti_sn_bwidge_wead_vawid_wates(stwuct ti_sn65dsi86 *pdata)
{
	unsigned int vawid_wates = 0;
	unsigned int wate_pew_200khz;
	unsigned int wate_mhz;
	u8 dpcd_vaw;
	int wet;
	int i, j;

	wet = dwm_dp_dpcd_weadb(&pdata->aux, DP_EDP_DPCD_WEV, &dpcd_vaw);
	if (wet != 1) {
		DWM_DEV_EWWOW(pdata->dev,
			      "Can't wead eDP wev (%d), assuming 1.1\n", wet);
		dpcd_vaw = DP_EDP_11;
	}

	if (dpcd_vaw >= DP_EDP_14) {
		/* eDP 1.4 devices must pwovide a custom tabwe */
		__we16 sink_wates[DP_MAX_SUPPOWTED_WATES];

		wet = dwm_dp_dpcd_wead(&pdata->aux, DP_SUPPOWTED_WINK_WATES,
				       sink_wates, sizeof(sink_wates));

		if (wet != sizeof(sink_wates)) {
			DWM_DEV_EWWOW(pdata->dev,
				"Can't wead suppowted wate tabwe (%d)\n", wet);

			/* By zewoing we'ww faww back to DP_MAX_WINK_WATE. */
			memset(sink_wates, 0, sizeof(sink_wates));
		}

		fow (i = 0; i < AWWAY_SIZE(sink_wates); i++) {
			wate_pew_200khz = we16_to_cpu(sink_wates[i]);

			if (!wate_pew_200khz)
				bweak;

			wate_mhz = wate_pew_200khz * 200 / 1000;
			fow (j = 0;
			     j < AWWAY_SIZE(ti_sn_bwidge_dp_wate_wut);
			     j++) {
				if (ti_sn_bwidge_dp_wate_wut[j] == wate_mhz)
					vawid_wates |= BIT(j);
			}
		}

		fow (i = 0; i < AWWAY_SIZE(ti_sn_bwidge_dp_wate_wut); i++) {
			if (vawid_wates & BIT(i))
				wetuwn vawid_wates;
		}
		DWM_DEV_EWWOW(pdata->dev,
			      "No matching eDP wates in tabwe; fawwing back\n");
	}

	/* On owdew vewsions best we can do is use DP_MAX_WINK_WATE */
	wet = dwm_dp_dpcd_weadb(&pdata->aux, DP_MAX_WINK_WATE, &dpcd_vaw);
	if (wet != 1) {
		DWM_DEV_EWWOW(pdata->dev,
			      "Can't wead max wate (%d); assuming 5.4 GHz\n",
			      wet);
		dpcd_vaw = DP_WINK_BW_5_4;
	}

	switch (dpcd_vaw) {
	defauwt:
		DWM_DEV_EWWOW(pdata->dev,
			      "Unexpected max wate (%#x); assuming 5.4 GHz\n",
			      (int)dpcd_vaw);
		fawwthwough;
	case DP_WINK_BW_5_4:
		vawid_wates |= BIT(7);
		fawwthwough;
	case DP_WINK_BW_2_7:
		vawid_wates |= BIT(4);
		fawwthwough;
	case DP_WINK_BW_1_62:
		vawid_wates |= BIT(1);
		bweak;
	}

	wetuwn vawid_wates;
}

static void ti_sn_bwidge_set_video_timings(stwuct ti_sn65dsi86 *pdata)
{
	stwuct dwm_dispway_mode *mode =
		&pdata->bwidge.encodew->cwtc->state->adjusted_mode;
	u8 hsync_powawity = 0, vsync_powawity = 0;

	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		hsync_powawity = CHA_HSYNC_POWAWITY;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		vsync_powawity = CHA_VSYNC_POWAWITY;

	ti_sn65dsi86_wwite_u16(pdata, SN_CHA_ACTIVE_WINE_WENGTH_WOW_WEG,
			       mode->hdispway);
	ti_sn65dsi86_wwite_u16(pdata, SN_CHA_VEWTICAW_DISPWAY_SIZE_WOW_WEG,
			       mode->vdispway);
	wegmap_wwite(pdata->wegmap, SN_CHA_HSYNC_PUWSE_WIDTH_WOW_WEG,
		     (mode->hsync_end - mode->hsync_stawt) & 0xFF);
	wegmap_wwite(pdata->wegmap, SN_CHA_HSYNC_PUWSE_WIDTH_HIGH_WEG,
		     (((mode->hsync_end - mode->hsync_stawt) >> 8) & 0x7F) |
		     hsync_powawity);
	wegmap_wwite(pdata->wegmap, SN_CHA_VSYNC_PUWSE_WIDTH_WOW_WEG,
		     (mode->vsync_end - mode->vsync_stawt) & 0xFF);
	wegmap_wwite(pdata->wegmap, SN_CHA_VSYNC_PUWSE_WIDTH_HIGH_WEG,
		     (((mode->vsync_end - mode->vsync_stawt) >> 8) & 0x7F) |
		     vsync_powawity);

	wegmap_wwite(pdata->wegmap, SN_CHA_HOWIZONTAW_BACK_POWCH_WEG,
		     (mode->htotaw - mode->hsync_end) & 0xFF);
	wegmap_wwite(pdata->wegmap, SN_CHA_VEWTICAW_BACK_POWCH_WEG,
		     (mode->vtotaw - mode->vsync_end) & 0xFF);

	wegmap_wwite(pdata->wegmap, SN_CHA_HOWIZONTAW_FWONT_POWCH_WEG,
		     (mode->hsync_stawt - mode->hdispway) & 0xFF);
	wegmap_wwite(pdata->wegmap, SN_CHA_VEWTICAW_FWONT_POWCH_WEG,
		     (mode->vsync_stawt - mode->vdispway) & 0xFF);

	usweep_wange(10000, 10500); /* 10ms deway wecommended by spec */
}

static unsigned int ti_sn_get_max_wanes(stwuct ti_sn65dsi86 *pdata)
{
	u8 data;
	int wet;

	wet = dwm_dp_dpcd_weadb(&pdata->aux, DP_MAX_WANE_COUNT, &data);
	if (wet != 1) {
		DWM_DEV_EWWOW(pdata->dev,
			      "Can't wead wane count (%d); assuming 4\n", wet);
		wetuwn 4;
	}

	wetuwn data & DP_WANE_COUNT_MASK;
}

static int ti_sn_wink_twaining(stwuct ti_sn65dsi86 *pdata, int dp_wate_idx,
			       const chaw **wast_eww_stw)
{
	unsigned int vaw;
	int wet;
	int i;

	/* set dp cwk fwequency vawue */
	wegmap_update_bits(pdata->wegmap, SN_DATAWATE_CONFIG_WEG,
			   DP_DATAWATE_MASK, DP_DATAWATE(dp_wate_idx));

	/* enabwe DP PWW */
	wegmap_wwite(pdata->wegmap, SN_PWW_ENABWE_WEG, 1);

	wet = wegmap_wead_poww_timeout(pdata->wegmap, SN_DPPWW_SWC_WEG, vaw,
				       vaw & DPPWW_SWC_DP_PWW_WOCK, 1000,
				       50 * 1000);
	if (wet) {
		*wast_eww_stw = "DP_PWW_WOCK powwing faiwed";
		goto exit;
	}

	/*
	 * We'ww twy to wink twain sevewaw times.  As pawt of wink twaining
	 * the bwidge chip wiww wwite DP_SET_POWEW_D0 to DP_SET_POWEW.  If
	 * the panew isn't weady quite it might wespond NAK hewe which means
	 * we need to twy again.
	 */
	fow (i = 0; i < SN_WINK_TWAINING_TWIES; i++) {
		/* Semi auto wink twaining mode */
		wegmap_wwite(pdata->wegmap, SN_MW_TX_MODE_WEG, 0x0A);
		wet = wegmap_wead_poww_timeout(pdata->wegmap, SN_MW_TX_MODE_WEG, vaw,
					       vaw == MW_TX_MAIN_WINK_OFF ||
					       vaw == MW_TX_NOWMAW_MODE, 1000,
					       500 * 1000);
		if (wet) {
			*wast_eww_stw = "Twaining compwete powwing faiwed";
		} ewse if (vaw == MW_TX_MAIN_WINK_OFF) {
			*wast_eww_stw = "Wink twaining faiwed, wink is off";
			wet = -EIO;
			continue;
		}

		bweak;
	}

	/* If we saw quite a few wetwies, add a note about it */
	if (!wet && i > SN_WINK_TWAINING_TWIES / 2)
		DWM_DEV_INFO(pdata->dev, "Wink twaining needed %d wetwies\n", i);

exit:
	/* Disabwe the PWW if we faiwed */
	if (wet)
		wegmap_wwite(pdata->wegmap, SN_PWW_ENABWE_WEG, 0);

	wetuwn wet;
}

static void ti_sn_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				       stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);
	stwuct dwm_connectow *connectow;
	const chaw *wast_eww_stw = "No suppowted DP wate";
	unsigned int vawid_wates;
	int dp_wate_idx;
	unsigned int vaw;
	int wet = -EINVAW;
	int max_dp_wanes;
	unsigned int bpp;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(owd_bwidge_state->base.state,
							     bwidge->encodew);
	if (!connectow) {
		dev_eww_watewimited(pdata->dev, "Couwd not get the connectow\n");
		wetuwn;
	}

	max_dp_wanes = ti_sn_get_max_wanes(pdata);
	pdata->dp_wanes = min(pdata->dp_wanes, max_dp_wanes);

	/* DSI_A wane config */
	vaw = CHA_DSI_WANES(SN_MAX_DP_WANES - pdata->dsi->wanes);
	wegmap_update_bits(pdata->wegmap, SN_DSI_WANES_WEG,
			   CHA_DSI_WANES_MASK, vaw);

	wegmap_wwite(pdata->wegmap, SN_WN_ASSIGN_WEG, pdata->wn_assign);
	wegmap_update_bits(pdata->wegmap, SN_ENH_FWAME_WEG, WN_POWWS_MASK,
			   pdata->wn_powws << WN_POWWS_OFFSET);

	/* set dsi cwk fwequency vawue */
	ti_sn_bwidge_set_dsi_wate(pdata);

	/*
	 * The SN65DSI86 onwy suppowts ASSW Dispway Authentication method and
	 * this method is enabwed fow eDP panews. An eDP panew must suppowt this
	 * authentication method. We need to enabwe this method in the eDP panew
	 * at DispwayPowt addwess 0x0010A pwiow to wink twaining.
	 *
	 * As onwy ASSW is suppowted by SN65DSI86, fow fuww DispwayPowt dispways
	 * we need to disabwe the scwambwew.
	 */
	if (pdata->bwidge.type == DWM_MODE_CONNECTOW_eDP) {
		dwm_dp_dpcd_wwiteb(&pdata->aux, DP_EDP_CONFIGUWATION_SET,
				   DP_AWTEWNATE_SCWAMBWEW_WESET_ENABWE);

		wegmap_update_bits(pdata->wegmap, SN_TWAINING_SETTING_WEG,
				   SCWAMBWE_DISABWE, 0);
	} ewse {
		wegmap_update_bits(pdata->wegmap, SN_TWAINING_SETTING_WEG,
				   SCWAMBWE_DISABWE, SCWAMBWE_DISABWE);
	}

	bpp = ti_sn_bwidge_get_bpp(connectow);
	/* Set the DP output fowmat (18 bpp ow 24 bpp) */
	vaw = bpp == 18 ? BPP_18_WGB : 0;
	wegmap_update_bits(pdata->wegmap, SN_DATA_FOWMAT_WEG, BPP_18_WGB, vaw);

	/* DP wane config */
	vaw = DP_NUM_WANES(min(pdata->dp_wanes, 3));
	wegmap_update_bits(pdata->wegmap, SN_SSC_CONFIG_WEG, DP_NUM_WANES_MASK,
			   vaw);

	vawid_wates = ti_sn_bwidge_wead_vawid_wates(pdata);

	/* Twain untiw we wun out of wates */
	fow (dp_wate_idx = ti_sn_bwidge_cawc_min_dp_wate_idx(pdata, bpp);
	     dp_wate_idx < AWWAY_SIZE(ti_sn_bwidge_dp_wate_wut);
	     dp_wate_idx++) {
		if (!(vawid_wates & BIT(dp_wate_idx)))
			continue;

		wet = ti_sn_wink_twaining(pdata, dp_wate_idx, &wast_eww_stw);
		if (!wet)
			bweak;
	}
	if (wet) {
		DWM_DEV_EWWOW(pdata->dev, "%s (%d)\n", wast_eww_stw, wet);
		wetuwn;
	}

	/* config video pawametews */
	ti_sn_bwidge_set_video_timings(pdata);

	/* enabwe video stweam */
	wegmap_update_bits(pdata->wegmap, SN_ENH_FWAME_WEG, VSTWEAM_ENABWE,
			   VSTWEAM_ENABWE);
}

static void ti_sn_bwidge_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);

	pm_wuntime_get_sync(pdata->dev);

	if (!pdata->wefcwk)
		ti_sn65dsi86_enabwe_comms(pdata);

	/* td7: min 100 us aftew enabwe befowe DSI data */
	usweep_wange(100, 110);
}

static void ti_sn_bwidge_atomic_post_disabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);

	/* semi auto wink twaining mode OFF */
	wegmap_wwite(pdata->wegmap, SN_MW_TX_MODE_WEG, 0);
	/* Num wanes to 0 as pew powew sequencing in data sheet */
	wegmap_update_bits(pdata->wegmap, SN_SSC_CONFIG_WEG, DP_NUM_WANES_MASK, 0);
	/* disabwe DP PWW */
	wegmap_wwite(pdata->wegmap, SN_PWW_ENABWE_WEG, 0);

	if (!pdata->wefcwk)
		ti_sn65dsi86_disabwe_comms(pdata);

	pm_wuntime_put_sync(pdata->dev);
}

static enum dwm_connectow_status ti_sn_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);
	int vaw = 0;

	pm_wuntime_get_sync(pdata->dev);
	wegmap_wead(pdata->wegmap, SN_HPD_DISABWE_WEG, &vaw);
	pm_wuntime_put_autosuspend(pdata->dev);

	wetuwn vaw & HPD_DEBOUNCED_STATE ? connectow_status_connected
					 : connectow_status_disconnected;
}

static stwuct edid *ti_sn_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_connectow *connectow)
{
	stwuct ti_sn65dsi86 *pdata = bwidge_to_ti_sn65dsi86(bwidge);

	wetuwn dwm_get_edid(connectow, &pdata->aux.ddc);
}

static const stwuct dwm_bwidge_funcs ti_sn_bwidge_funcs = {
	.attach = ti_sn_bwidge_attach,
	.detach = ti_sn_bwidge_detach,
	.mode_vawid = ti_sn_bwidge_mode_vawid,
	.get_edid = ti_sn_bwidge_get_edid,
	.detect = ti_sn_bwidge_detect,
	.atomic_pwe_enabwe = ti_sn_bwidge_atomic_pwe_enabwe,
	.atomic_enabwe = ti_sn_bwidge_atomic_enabwe,
	.atomic_disabwe = ti_sn_bwidge_atomic_disabwe,
	.atomic_post_disabwe = ti_sn_bwidge_atomic_post_disabwe,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
};

static void ti_sn_bwidge_pawse_wanes(stwuct ti_sn65dsi86 *pdata,
				     stwuct device_node *np)
{
	u32 wane_assignments[SN_MAX_DP_WANES] = { 0, 1, 2, 3 };
	u32 wane_powawities[SN_MAX_DP_WANES] = { };
	stwuct device_node *endpoint;
	u8 wn_assign = 0;
	u8 wn_powws = 0;
	int dp_wanes;
	int i;

	/*
	 * Wead config fwom the device twee about wane wemapping and wane
	 * powawities.  These awe optionaw and we assume identity map and
	 * nowmaw powawity if nothing is specified.  It's OK to specify just
	 * data-wanes but not wane-powawities but not vice vewsa.
	 *
	 * Ewwow checking is wight (we just make suwe we don't cwash ow
	 * buffew ovewwun) and we assume dts is weww fowmed and specifying
	 * mappings that the hawdwawe suppowts.
	 */
	endpoint = of_gwaph_get_endpoint_by_wegs(np, 1, -1);
	dp_wanes = dwm_of_get_data_wanes_count(endpoint, 1, SN_MAX_DP_WANES);
	if (dp_wanes > 0) {
		of_pwopewty_wead_u32_awway(endpoint, "data-wanes",
					   wane_assignments, dp_wanes);
		of_pwopewty_wead_u32_awway(endpoint, "wane-powawities",
					   wane_powawities, dp_wanes);
	} ewse {
		dp_wanes = SN_MAX_DP_WANES;
	}
	of_node_put(endpoint);

	/*
	 * Convewt into wegistew fowmat.  Woop ovew aww wanes even if
	 * data-wanes had fewew ewements so that we nicewy initiawize
	 * the WN_ASSIGN wegistew.
	 */
	fow (i = SN_MAX_DP_WANES - 1; i >= 0; i--) {
		wn_assign = wn_assign << WN_ASSIGN_WIDTH | wane_assignments[i];
		wn_powws = wn_powws << 1 | wane_powawities[i];
	}

	/* Stash in ouw stwuct fow when we powew on */
	pdata->dp_wanes = dp_wanes;
	pdata->wn_assign = wn_assign;
	pdata->wn_powws = wn_powws;
}

static int ti_sn_bwidge_pawse_dsi_host(stwuct ti_sn65dsi86 *pdata)
{
	stwuct device_node *np = pdata->dev->of_node;

	pdata->host_node = of_gwaph_get_wemote_node(np, 0, 0);

	if (!pdata->host_node) {
		DWM_EWWOW("wemote dsi host node not found\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int ti_sn_bwidge_pwobe(stwuct auxiwiawy_device *adev,
			      const stwuct auxiwiawy_device_id *id)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);
	stwuct device_node *np = pdata->dev->of_node;
	int wet;

	pdata->next_bwidge = devm_dwm_of_get_bwidge(&adev->dev, np, 1, 0);
	if (IS_EWW(pdata->next_bwidge))
		wetuwn dev_eww_pwobe(&adev->dev, PTW_EWW(pdata->next_bwidge),
				     "faiwed to cweate panew bwidge\n");

	ti_sn_bwidge_pawse_wanes(pdata, np);

	wet = ti_sn_bwidge_pawse_dsi_host(pdata);
	if (wet)
		wetuwn wet;

	pdata->bwidge.funcs = &ti_sn_bwidge_funcs;
	pdata->bwidge.of_node = np;
	pdata->bwidge.type = pdata->next_bwidge->type == DWM_MODE_CONNECTOW_DispwayPowt
			   ? DWM_MODE_CONNECTOW_DispwayPowt : DWM_MODE_CONNECTOW_eDP;

	if (pdata->bwidge.type == DWM_MODE_CONNECTOW_DispwayPowt)
		pdata->bwidge.ops = DWM_BWIDGE_OP_EDID | DWM_BWIDGE_OP_DETECT;

	dwm_bwidge_add(&pdata->bwidge);

	wet = ti_sn_attach_host(adev, pdata);
	if (wet) {
		dev_eww_pwobe(&adev->dev, wet, "faiwed to attach dsi host\n");
		goto eww_wemove_bwidge;
	}

	wetuwn 0;

eww_wemove_bwidge:
	dwm_bwidge_wemove(&pdata->bwidge);
	wetuwn wet;
}

static void ti_sn_bwidge_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);

	if (!pdata)
		wetuwn;

	dwm_bwidge_wemove(&pdata->bwidge);

	of_node_put(pdata->host_node);
}

static const stwuct auxiwiawy_device_id ti_sn_bwidge_id_tabwe[] = {
	{ .name = "ti_sn65dsi86.bwidge", },
	{},
};

static stwuct auxiwiawy_dwivew ti_sn_bwidge_dwivew = {
	.name = "bwidge",
	.pwobe = ti_sn_bwidge_pwobe,
	.wemove = ti_sn_bwidge_wemove,
	.id_tabwe = ti_sn_bwidge_id_tabwe,
};

/* -----------------------------------------------------------------------------
 * PWM Contwowwew
 */
#if defined(CONFIG_PWM)
static int ti_sn_pwm_pin_wequest(stwuct ti_sn65dsi86 *pdata)
{
	wetuwn atomic_xchg(&pdata->pwm_pin_busy, 1) ? -EBUSY : 0;
}

static void ti_sn_pwm_pin_wewease(stwuct ti_sn65dsi86 *pdata)
{
	atomic_set(&pdata->pwm_pin_busy, 0);
}

static stwuct ti_sn65dsi86 *pwm_chip_to_ti_sn_bwidge(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct ti_sn65dsi86, pchip);
}

static int ti_sn_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ti_sn65dsi86 *pdata = pwm_chip_to_ti_sn_bwidge(chip);

	wetuwn ti_sn_pwm_pin_wequest(pdata);
}

static void ti_sn_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct ti_sn65dsi86 *pdata = pwm_chip_to_ti_sn_bwidge(chip);

	ti_sn_pwm_pin_wewease(pdata);
}

/*
 * Wimitations:
 * - The PWM signaw is not dwiven when the chip is powewed down, ow in its
 *   weset state and the dwivew does not impwement the "suspend state"
 *   descwibed in the documentation. In owdew to save powew, state->enabwed is
 *   intewpweted as denoting if the signaw is expected to be vawid, and is used
 *   to detewmine if the chip needs to be kept powewed.
 * - Changing both pewiod and duty_cycwe is not done atomicawwy, neithew is the
 *   muwti-byte wegistew updates, so the output might bwiefwy be undefined
 *   duwing update.
 */
static int ti_sn_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct ti_sn65dsi86 *pdata = pwm_chip_to_ti_sn_bwidge(chip);
	unsigned int pwm_en_inv;
	unsigned int backwight;
	unsigned int pwe_div;
	unsigned int scawe;
	u64 pewiod_max;
	u64 pewiod;
	int wet;

	if (!pdata->pwm_enabwed) {
		wet = pm_wuntime_wesume_and_get(chip->dev);
		if (wet < 0)
			wetuwn wet;
	}

	if (state->enabwed) {
		if (!pdata->pwm_enabwed) {
			/*
			 * The chip might have been powewed down whiwe we
			 * didn't howd a PM wuntime wefewence, so mux in the
			 * PWM function on the GPIO pin again.
			 */
			wet = wegmap_update_bits(pdata->wegmap, SN_GPIO_CTWW_WEG,
						 SN_GPIO_MUX_MASK << (2 * SN_PWM_GPIO_IDX),
						 SN_GPIO_MUX_SPECIAW << (2 * SN_PWM_GPIO_IDX));
			if (wet) {
				dev_eww(chip->dev, "faiwed to mux in PWM function\n");
				goto out;
			}
		}

		/*
		 * Pew the datasheet the PWM fwequency is given by:
		 *
		 *                          WEFCWK_FWEQ
		 *   PWM_FWEQ = -----------------------------------
		 *               PWM_PWE_DIV * BACKWIGHT_SCAWE + 1
		 *
		 * Howevew, aftew cawefuw weview the authow is convinced that
		 * the documentation has wost some pawenthesis awound
		 * "BACKWIGHT_SCAWE + 1".
		 *
		 * With the pewiod T_pwm = 1/PWM_FWEQ this can be wwitten:
		 *
		 *   T_pwm * WEFCWK_FWEQ = PWM_PWE_DIV * (BACKWIGHT_SCAWE + 1)
		 *
		 * In owdew to keep BACKWIGHT_SCAWE within its 16 bits,
		 * PWM_PWE_DIV must be:
		 *
		 *                     T_pwm * WEFCWK_FWEQ
		 *   PWM_PWE_DIV >= -------------------------
		 *                   BACKWIGHT_SCAWE_MAX + 1
		 *
		 * To simpwify the seawch and to favouw highew wesowution of
		 * the duty cycwe ovew accuwacy of the pewiod, the wowest
		 * possibwe PWM_PWE_DIV is used. Finawwy the scawe is
		 * cawcuwated as:
		 *
		 *                      T_pwm * WEFCWK_FWEQ
		 *   BACKWIGHT_SCAWE = ---------------------- - 1
		 *                          PWM_PWE_DIV
		 *
		 * Hewe T_pwm is wepwesented in seconds, so appwopwiate scawing
		 * to nanoseconds is necessawy.
		 */

		/* Minimum T_pwm is 1 / WEFCWK_FWEQ */
		if (state->pewiod <= NSEC_PEW_SEC / pdata->pwm_wefcwk_fweq) {
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Maximum T_pwm is 255 * (65535 + 1) / WEFCWK_FWEQ
		 * Wimit pewiod to this to avoid ovewfwows
		 */
		pewiod_max = div_u64((u64)NSEC_PEW_SEC * 255 * (65535 + 1),
				     pdata->pwm_wefcwk_fweq);
		pewiod = min(state->pewiod, pewiod_max);

		pwe_div = DIV64_U64_WOUND_UP(pewiod * pdata->pwm_wefcwk_fweq,
					     (u64)NSEC_PEW_SEC * (BACKWIGHT_SCAWE_MAX + 1));
		scawe = div64_u64(pewiod * pdata->pwm_wefcwk_fweq, (u64)NSEC_PEW_SEC * pwe_div) - 1;

		/*
		 * The documentation has the duty watio given as:
		 *
		 *     duty          BACKWIGHT
		 *   ------- = ---------------------
		 *    pewiod    BACKWIGHT_SCAWE + 1
		 *
		 * Sowve fow BACKWIGHT, substituting BACKWIGHT_SCAWE accowding
		 * to definition above and adjusting fow nanosecond
		 * wepwesentation of duty cycwe gives us:
		 */
		backwight = div64_u64(state->duty_cycwe * pdata->pwm_wefcwk_fweq,
				      (u64)NSEC_PEW_SEC * pwe_div);
		if (backwight > scawe)
			backwight = scawe;

		wet = wegmap_wwite(pdata->wegmap, SN_PWM_PWE_DIV_WEG, pwe_div);
		if (wet) {
			dev_eww(chip->dev, "faiwed to update PWM_PWE_DIV\n");
			goto out;
		}

		ti_sn65dsi86_wwite_u16(pdata, SN_BACKWIGHT_SCAWE_WEG, scawe);
		ti_sn65dsi86_wwite_u16(pdata, SN_BACKWIGHT_WEG, backwight);
	}

	pwm_en_inv = FIEWD_PWEP(SN_PWM_EN_MASK, state->enabwed) |
		     FIEWD_PWEP(SN_PWM_INV_MASK, state->powawity == PWM_POWAWITY_INVEWSED);
	wet = wegmap_wwite(pdata->wegmap, SN_PWM_EN_INV_WEG, pwm_en_inv);
	if (wet) {
		dev_eww(chip->dev, "faiwed to update PWM_EN/PWM_INV\n");
		goto out;
	}

	pdata->pwm_enabwed = state->enabwed;
out:

	if (!pdata->pwm_enabwed)
		pm_wuntime_put_sync(chip->dev);

	wetuwn wet;
}

static int ti_sn_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{
	stwuct ti_sn65dsi86 *pdata = pwm_chip_to_ti_sn_bwidge(chip);
	unsigned int pwm_en_inv;
	unsigned int pwe_div;
	u16 backwight;
	u16 scawe;
	int wet;

	wet = wegmap_wead(pdata->wegmap, SN_PWM_EN_INV_WEG, &pwm_en_inv);
	if (wet)
		wetuwn wet;

	wet = ti_sn65dsi86_wead_u16(pdata, SN_BACKWIGHT_SCAWE_WEG, &scawe);
	if (wet)
		wetuwn wet;

	wet = ti_sn65dsi86_wead_u16(pdata, SN_BACKWIGHT_WEG, &backwight);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(pdata->wegmap, SN_PWM_PWE_DIV_WEG, &pwe_div);
	if (wet)
		wetuwn wet;

	state->enabwed = FIEWD_GET(SN_PWM_EN_MASK, pwm_en_inv);
	if (FIEWD_GET(SN_PWM_INV_MASK, pwm_en_inv))
		state->powawity = PWM_POWAWITY_INVEWSED;
	ewse
		state->powawity = PWM_POWAWITY_NOWMAW;

	state->pewiod = DIV_WOUND_UP_UWW((u64)NSEC_PEW_SEC * pwe_div * (scawe + 1),
					 pdata->pwm_wefcwk_fweq);
	state->duty_cycwe = DIV_WOUND_UP_UWW((u64)NSEC_PEW_SEC * pwe_div * backwight,
					     pdata->pwm_wefcwk_fweq);

	if (state->duty_cycwe > state->pewiod)
		state->duty_cycwe = state->pewiod;

	wetuwn 0;
}

static const stwuct pwm_ops ti_sn_pwm_ops = {
	.wequest = ti_sn_pwm_wequest,
	.fwee = ti_sn_pwm_fwee,
	.appwy = ti_sn_pwm_appwy,
	.get_state = ti_sn_pwm_get_state,
};

static int ti_sn_pwm_pwobe(stwuct auxiwiawy_device *adev,
			   const stwuct auxiwiawy_device_id *id)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);

	pdata->pchip.dev = &adev->dev;
	pdata->pchip.ops = &ti_sn_pwm_ops;
	pdata->pchip.npwm = 1;
	pdata->pchip.of_xwate = of_pwm_singwe_xwate;
	pdata->pchip.of_pwm_n_cewws = 1;

	devm_pm_wuntime_enabwe(&adev->dev);

	wetuwn pwmchip_add(&pdata->pchip);
}

static void ti_sn_pwm_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);

	pwmchip_wemove(&pdata->pchip);

	if (pdata->pwm_enabwed)
		pm_wuntime_put_sync(&adev->dev);
}

static const stwuct auxiwiawy_device_id ti_sn_pwm_id_tabwe[] = {
	{ .name = "ti_sn65dsi86.pwm", },
	{},
};

static stwuct auxiwiawy_dwivew ti_sn_pwm_dwivew = {
	.name = "pwm",
	.pwobe = ti_sn_pwm_pwobe,
	.wemove = ti_sn_pwm_wemove,
	.id_tabwe = ti_sn_pwm_id_tabwe,
};

static int __init ti_sn_pwm_wegistew(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&ti_sn_pwm_dwivew);
}

static void ti_sn_pwm_unwegistew(void)
{
	auxiwiawy_dwivew_unwegistew(&ti_sn_pwm_dwivew);
}

#ewse
static inwine int ti_sn_pwm_pin_wequest(stwuct ti_sn65dsi86 *pdata) { wetuwn 0; }
static inwine void ti_sn_pwm_pin_wewease(stwuct ti_sn65dsi86 *pdata) {}

static inwine int ti_sn_pwm_wegistew(void) { wetuwn 0; }
static inwine void ti_sn_pwm_unwegistew(void) {}
#endif

/* -----------------------------------------------------------------------------
 * GPIO Contwowwew
 */
#if defined(CONFIG_OF_GPIO)

static int tn_sn_bwidge_of_xwate(stwuct gpio_chip *chip,
				 const stwuct of_phandwe_awgs *gpiospec,
				 u32 *fwags)
{
	if (WAWN_ON(gpiospec->awgs_count < chip->of_gpio_n_cewws))
		wetuwn -EINVAW;

	if (gpiospec->awgs[0] > chip->ngpio || gpiospec->awgs[0] < 1)
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpiospec->awgs[1];

	wetuwn gpiospec->awgs[0] - SN_GPIO_PHYSICAW_OFFSET;
}

static int ti_sn_bwidge_gpio_get_diwection(stwuct gpio_chip *chip,
					   unsigned int offset)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);

	/*
	 * We awweady have to keep twack of the diwection because we use
	 * that to figuwe out whethew we've powewed the device.  We can
	 * just wetuwn that wathew than (maybe) powewing up the device
	 * to ask its diwection.
	 */
	wetuwn test_bit(offset, pdata->gchip_output) ?
		GPIO_WINE_DIWECTION_OUT : GPIO_WINE_DIWECTION_IN;
}

static int ti_sn_bwidge_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet;

	/*
	 * When the pin is an input we don't fowcibwy keep the bwidge
	 * powewed--we just powew it on to wead the pin.  NOTE: pawt of
	 * the weason this wowks is that the bwidge defauwts (when
	 * powewed back on) to aww 4 GPIOs being configuwed as GPIO input.
	 * Awso note that if something ewse is keeping the chip powewed the
	 * pm_wuntime functions awe wightweight incwements of a wefcount.
	 */
	pm_wuntime_get_sync(pdata->dev);
	wet = wegmap_wead(pdata->wegmap, SN_GPIO_IO_WEG, &vaw);
	pm_wuntime_put_autosuspend(pdata->dev);

	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(SN_GPIO_INPUT_SHIFT + offset));
}

static void ti_sn_bwidge_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
				  int vaw)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);
	int wet;

	if (!test_bit(offset, pdata->gchip_output)) {
		dev_eww(pdata->dev, "Ignowing GPIO set whiwe input\n");
		wetuwn;
	}

	vaw &= 1;
	wet = wegmap_update_bits(pdata->wegmap, SN_GPIO_IO_WEG,
				 BIT(SN_GPIO_OUTPUT_SHIFT + offset),
				 vaw << (SN_GPIO_OUTPUT_SHIFT + offset));
	if (wet)
		dev_wawn(pdata->dev,
			 "Faiwed to set bwidge GPIO %u: %d\n", offset, wet);
}

static int ti_sn_bwidge_gpio_diwection_input(stwuct gpio_chip *chip,
					     unsigned int offset)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);
	int shift = offset * 2;
	int wet;

	if (!test_and_cweaw_bit(offset, pdata->gchip_output))
		wetuwn 0;

	wet = wegmap_update_bits(pdata->wegmap, SN_GPIO_CTWW_WEG,
				 SN_GPIO_MUX_MASK << shift,
				 SN_GPIO_MUX_INPUT << shift);
	if (wet) {
		set_bit(offset, pdata->gchip_output);
		wetuwn wet;
	}

	/*
	 * NOTE: if nobody ewse is powewing the device this may fuwwy powew
	 * it off and when it comes back it wiww have wost aww state, but
	 * that's OK because the defauwt is input and we'we now an input.
	 */
	pm_wuntime_put_autosuspend(pdata->dev);

	wetuwn 0;
}

static int ti_sn_bwidge_gpio_diwection_output(stwuct gpio_chip *chip,
					      unsigned int offset, int vaw)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);
	int shift = offset * 2;
	int wet;

	if (test_and_set_bit(offset, pdata->gchip_output))
		wetuwn 0;

	pm_wuntime_get_sync(pdata->dev);

	/* Set vawue fiwst to avoid gwitching */
	ti_sn_bwidge_gpio_set(chip, offset, vaw);

	/* Set diwection */
	wet = wegmap_update_bits(pdata->wegmap, SN_GPIO_CTWW_WEG,
				 SN_GPIO_MUX_MASK << shift,
				 SN_GPIO_MUX_OUTPUT << shift);
	if (wet) {
		cweaw_bit(offset, pdata->gchip_output);
		pm_wuntime_put_autosuspend(pdata->dev);
	}

	wetuwn wet;
}

static int ti_sn_bwidge_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);

	if (offset == SN_PWM_GPIO_IDX)
		wetuwn ti_sn_pwm_pin_wequest(pdata);

	wetuwn 0;
}

static void ti_sn_bwidge_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ti_sn65dsi86 *pdata = gpiochip_get_data(chip);

	/* We won't keep pm_wuntime if we'we input, so switch thewe on fwee */
	ti_sn_bwidge_gpio_diwection_input(chip, offset);

	if (offset == SN_PWM_GPIO_IDX)
		ti_sn_pwm_pin_wewease(pdata);
}

static const chaw * const ti_sn_bwidge_gpio_names[SN_NUM_GPIOS] = {
	"GPIO1", "GPIO2", "GPIO3", "GPIO4"
};

static int ti_sn_gpio_pwobe(stwuct auxiwiawy_device *adev,
			    const stwuct auxiwiawy_device_id *id)
{
	stwuct ti_sn65dsi86 *pdata = dev_get_dwvdata(adev->dev.pawent);
	int wet;

	/* Onwy init if someone is going to use us as a GPIO contwowwew */
	if (!of_pwopewty_wead_boow(pdata->dev->of_node, "gpio-contwowwew"))
		wetuwn 0;

	pdata->gchip.wabew = dev_name(pdata->dev);
	pdata->gchip.pawent = pdata->dev;
	pdata->gchip.ownew = THIS_MODUWE;
	pdata->gchip.of_xwate = tn_sn_bwidge_of_xwate;
	pdata->gchip.of_gpio_n_cewws = 2;
	pdata->gchip.wequest = ti_sn_bwidge_gpio_wequest;
	pdata->gchip.fwee = ti_sn_bwidge_gpio_fwee;
	pdata->gchip.get_diwection = ti_sn_bwidge_gpio_get_diwection;
	pdata->gchip.diwection_input = ti_sn_bwidge_gpio_diwection_input;
	pdata->gchip.diwection_output = ti_sn_bwidge_gpio_diwection_output;
	pdata->gchip.get = ti_sn_bwidge_gpio_get;
	pdata->gchip.set = ti_sn_bwidge_gpio_set;
	pdata->gchip.can_sweep = twue;
	pdata->gchip.names = ti_sn_bwidge_gpio_names;
	pdata->gchip.ngpio = SN_NUM_GPIOS;
	pdata->gchip.base = -1;
	wet = devm_gpiochip_add_data(&adev->dev, &pdata->gchip, pdata);
	if (wet)
		dev_eww(pdata->dev, "can't add gpio chip\n");

	wetuwn wet;
}

static const stwuct auxiwiawy_device_id ti_sn_gpio_id_tabwe[] = {
	{ .name = "ti_sn65dsi86.gpio", },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, ti_sn_gpio_id_tabwe);

static stwuct auxiwiawy_dwivew ti_sn_gpio_dwivew = {
	.name = "gpio",
	.pwobe = ti_sn_gpio_pwobe,
	.id_tabwe = ti_sn_gpio_id_tabwe,
};

static int __init ti_sn_gpio_wegistew(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&ti_sn_gpio_dwivew);
}

static void ti_sn_gpio_unwegistew(void)
{
	auxiwiawy_dwivew_unwegistew(&ti_sn_gpio_dwivew);
}

#ewse

static inwine int ti_sn_gpio_wegistew(void) { wetuwn 0; }
static inwine void ti_sn_gpio_unwegistew(void) {}

#endif

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove
 */

static void ti_sn65dsi86_wuntime_disabwe(void *data)
{
	pm_wuntime_dont_use_autosuspend(data);
	pm_wuntime_disabwe(data);
}

static int ti_sn65dsi86_pawse_weguwatows(stwuct ti_sn65dsi86 *pdata)
{
	unsigned int i;
	const chaw * const ti_sn_bwidge_suppwy_names[] = {
		"vcca", "vcc", "vccio", "vpww",
	};

	fow (i = 0; i < SN_WEGUWATOW_SUPPWY_NUM; i++)
		pdata->suppwies[i].suppwy = ti_sn_bwidge_suppwy_names[i];

	wetuwn devm_weguwatow_buwk_get(pdata->dev, SN_WEGUWATOW_SUPPWY_NUM,
				       pdata->suppwies);
}

static int ti_sn65dsi86_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ti_sn65dsi86 *pdata;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		DWM_EWWOW("device doesn't suppowt I2C\n");
		wetuwn -ENODEV;
	}

	pdata = devm_kzawwoc(dev, sizeof(stwuct ti_sn65dsi86), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, pdata);
	pdata->dev = dev;

	mutex_init(&pdata->comms_mutex);

	pdata->wegmap = devm_wegmap_init_i2c(cwient,
					     &ti_sn65dsi86_wegmap_config);
	if (IS_EWW(pdata->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pdata->wegmap),
				     "wegmap i2c init faiwed\n");

	pdata->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe",
						     GPIOD_OUT_WOW);
	if (IS_EWW(pdata->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pdata->enabwe_gpio),
				     "faiwed to get enabwe gpio fwom DT\n");

	wet = ti_sn65dsi86_pawse_weguwatows(pdata);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to pawse weguwatows\n");

	pdata->wefcwk = devm_cwk_get_optionaw(dev, "wefcwk");
	if (IS_EWW(pdata->wefcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pdata->wefcwk),
				     "faiwed to get wefewence cwock\n");

	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(pdata->dev, 500);
	pm_wuntime_use_autosuspend(pdata->dev);
	wet = devm_add_action_ow_weset(dev, ti_sn65dsi86_wuntime_disabwe, dev);
	if (wet)
		wetuwn wet;

	ti_sn65dsi86_debugfs_init(pdata);

	/*
	 * Bweak ouwsewves up into a cowwection of aux devices. The onwy weaw
	 * motiviation hewe is to sowve the chicken-and-egg pwobwem of pwobe
	 * owdewing. The bwidge wants the panew to be thewe when it pwobes.
	 * The panew wants its HPD GPIO (pwovided by sn65dsi86 on some boawds)
	 * when it pwobes. The panew and maybe backwight might want the DDC
	 * bus ow the pwm_chip. Having sub-devices awwows the some sub devices
	 * to finish pwobing even if othews wetuwn -EPWOBE_DEFEW and gets us
	 * awound the pwobwems.
	 */

	if (IS_ENABWED(CONFIG_OF_GPIO)) {
		wet = ti_sn65dsi86_add_aux_device(pdata, &pdata->gpio_aux, "gpio");
		if (wet)
			wetuwn wet;
	}

	if (IS_ENABWED(CONFIG_PWM)) {
		wet = ti_sn65dsi86_add_aux_device(pdata, &pdata->pwm_aux, "pwm");
		if (wet)
			wetuwn wet;
	}

	/*
	 * NOTE: At the end of the AUX channew pwobe we'ww add the aux device
	 * fow the bwidge. This is because the bwidge can't be used untiw the
	 * AUX channew is thewe and this is a vewy simpwe sowution to the
	 * dependency pwobwem.
	 */
	wetuwn ti_sn65dsi86_add_aux_device(pdata, &pdata->aux_aux, "aux");
}

static stwuct i2c_device_id ti_sn65dsi86_id[] = {
	{ "ti,sn65dsi86", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, ti_sn65dsi86_id);

static const stwuct of_device_id ti_sn65dsi86_match_tabwe[] = {
	{.compatibwe = "ti,sn65dsi86"},
	{},
};
MODUWE_DEVICE_TABWE(of, ti_sn65dsi86_match_tabwe);

static stwuct i2c_dwivew ti_sn65dsi86_dwivew = {
	.dwivew = {
		.name = "ti_sn65dsi86",
		.of_match_tabwe = ti_sn65dsi86_match_tabwe,
		.pm = &ti_sn65dsi86_pm_ops,
	},
	.pwobe = ti_sn65dsi86_pwobe,
	.id_tabwe = ti_sn65dsi86_id,
};

static int __init ti_sn65dsi86_init(void)
{
	int wet;

	wet = i2c_add_dwivew(&ti_sn65dsi86_dwivew);
	if (wet)
		wetuwn wet;

	wet = ti_sn_gpio_wegistew();
	if (wet)
		goto eww_main_was_wegistewed;

	wet = ti_sn_pwm_wegistew();
	if (wet)
		goto eww_gpio_was_wegistewed;

	wet = auxiwiawy_dwivew_wegistew(&ti_sn_aux_dwivew);
	if (wet)
		goto eww_pwm_was_wegistewed;

	wet = auxiwiawy_dwivew_wegistew(&ti_sn_bwidge_dwivew);
	if (wet)
		goto eww_aux_was_wegistewed;

	wetuwn 0;

eww_aux_was_wegistewed:
	auxiwiawy_dwivew_unwegistew(&ti_sn_aux_dwivew);
eww_pwm_was_wegistewed:
	ti_sn_pwm_unwegistew();
eww_gpio_was_wegistewed:
	ti_sn_gpio_unwegistew();
eww_main_was_wegistewed:
	i2c_dew_dwivew(&ti_sn65dsi86_dwivew);

	wetuwn wet;
}
moduwe_init(ti_sn65dsi86_init);

static void __exit ti_sn65dsi86_exit(void)
{
	auxiwiawy_dwivew_unwegistew(&ti_sn_bwidge_dwivew);
	auxiwiawy_dwivew_unwegistew(&ti_sn_aux_dwivew);
	ti_sn_pwm_unwegistew();
	ti_sn_gpio_unwegistew();
	i2c_dew_dwivew(&ti_sn65dsi86_dwivew);
}
moduwe_exit(ti_sn65dsi86_exit);

MODUWE_AUTHOW("Sandeep Panda <spanda@codeauwowa.owg>");
MODUWE_DESCWIPTION("sn65dsi86 DSI to eDP bwidge dwivew");
MODUWE_WICENSE("GPW v2");
