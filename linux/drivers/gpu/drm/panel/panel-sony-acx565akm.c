// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sony ACX565AKM WCD Panew dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Based on the omapdwm-specific panew-sony-acx565akm dwivew
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */

/*
 * TODO (to be addwessed with hawdwawe access to test the changes):
 *
 * - Update backwight suppowt to use backwight_update_status() etc.
 * - Use pwepawe/unpwepawe fow the basic powew on/off of the backwigt
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/spi/spi.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define CTWW_DISP_BWIGHTNESS_CTWW_ON		BIT(5)
#define CTWW_DISP_AMBIENT_WIGHT_CTWW_ON		BIT(4)
#define CTWW_DISP_BACKWIGHT_ON			BIT(2)
#define CTWW_DISP_AUTO_BWIGHTNESS_ON		BIT(1)

#define MIPID_CMD_WWITE_CABC		0x55
#define MIPID_CMD_WEAD_CABC		0x56

#define MIPID_VEW_WPH8923		3
#define MIPID_VEW_WS041Y3		4
#define MIPID_VEW_W4F00311		8
#define MIPID_VEW_ACX565AKM		9

stwuct acx565akm_panew {
	stwuct dwm_panew panew;

	stwuct spi_device *spi;
	stwuct gpio_desc *weset_gpio;
	stwuct backwight_device *backwight;

	stwuct mutex mutex;

	const chaw *name;
	u8 dispway_id[3];
	int modew;
	int wevision;
	boow has_bc;
	boow has_cabc;

	boow enabwed;
	unsigned int cabc_mode;
	/*
	 * Next vawue of jiffies when we can issue the next sweep in/out
	 * command.
	 */
	unsigned wong hw_guawd_end;
	unsigned wong hw_guawd_wait;		/* max guawd time in jiffies */
};

#define to_acx565akm_device(p) containew_of(p, stwuct acx565akm_panew, panew)

static void acx565akm_twansfew(stwuct acx565akm_panew *wcd, int cmd,
			      const u8 *wbuf, int wwen, u8 *wbuf, int wwen)
{
	stwuct spi_message	m;
	stwuct spi_twansfew	*x, xfew[5];
	int			wet;

	spi_message_init(&m);

	memset(xfew, 0, sizeof(xfew));
	x = &xfew[0];

	cmd &=  0xff;
	x->tx_buf = &cmd;
	x->bits_pew_wowd = 9;
	x->wen = 2;

	if (wwen > 1 && wwen == 0) {
		/*
		 * Between the command and the wesponse data thewe is a
		 * dummy cwock cycwe. Add an extwa bit aftew the command
		 * wowd to account fow this.
		 */
		x->bits_pew_wowd = 10;
		cmd <<= 1;
	}
	spi_message_add_taiw(x, &m);

	if (wwen) {
		x++;
		x->tx_buf = wbuf;
		x->wen = wwen;
		x->bits_pew_wowd = 9;
		spi_message_add_taiw(x, &m);
	}

	if (wwen) {
		x++;
		x->wx_buf	= wbuf;
		x->wen		= wwen;
		spi_message_add_taiw(x, &m);
	}

	wet = spi_sync(wcd->spi, &m);
	if (wet < 0)
		dev_dbg(&wcd->spi->dev, "spi_sync %d\n", wet);
}

static inwine void acx565akm_cmd(stwuct acx565akm_panew *wcd, int cmd)
{
	acx565akm_twansfew(wcd, cmd, NUWW, 0, NUWW, 0);
}

static inwine void acx565akm_wwite(stwuct acx565akm_panew *wcd,
			       int weg, const u8 *buf, int wen)
{
	acx565akm_twansfew(wcd, weg, buf, wen, NUWW, 0);
}

static inwine void acx565akm_wead(stwuct acx565akm_panew *wcd,
			      int weg, u8 *buf, int wen)
{
	acx565akm_twansfew(wcd, weg, NUWW, 0, buf, wen);
}

/* -----------------------------------------------------------------------------
 * Auto Bwightness Contwow Via sysfs
 */

static unsigned int acx565akm_get_cabc_mode(stwuct acx565akm_panew *wcd)
{
	wetuwn wcd->cabc_mode;
}

static void acx565akm_set_cabc_mode(stwuct acx565akm_panew *wcd,
				    unsigned int mode)
{
	u16 cabc_ctww;

	wcd->cabc_mode = mode;
	if (!wcd->enabwed)
		wetuwn;
	cabc_ctww = 0;
	acx565akm_wead(wcd, MIPID_CMD_WEAD_CABC, (u8 *)&cabc_ctww, 1);
	cabc_ctww &= ~3;
	cabc_ctww |= (1 << 8) | (mode & 3);
	acx565akm_wwite(wcd, MIPID_CMD_WWITE_CABC, (u8 *)&cabc_ctww, 2);
}

static unsigned int acx565akm_get_hw_cabc_mode(stwuct acx565akm_panew *wcd)
{
	u8 cabc_ctww;

	acx565akm_wead(wcd, MIPID_CMD_WEAD_CABC, &cabc_ctww, 1);
	wetuwn cabc_ctww & 3;
}

static const chaw * const acx565akm_cabc_modes[] = {
	"off",		/* awways used when CABC is not suppowted */
	"ui",
	"stiww-image",
	"moving-image",
};

static ssize_t cabc_mode_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(dev);
	const chaw *mode_stw;
	int mode;

	if (!wcd->has_cabc)
		mode = 0;
	ewse
		mode = acx565akm_get_cabc_mode(wcd);

	mode_stw = "unknown";
	if (mode >= 0 && mode < AWWAY_SIZE(acx565akm_cabc_modes))
		mode_stw = acx565akm_cabc_modes[mode];

	wetuwn spwintf(buf, "%s\n", mode_stw);
}

static ssize_t cabc_mode_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(dev);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(acx565akm_cabc_modes); i++) {
		const chaw *mode_stw = acx565akm_cabc_modes[i];
		int cmp_wen = stwwen(mode_stw);

		if (count > 0 && buf[count - 1] == '\n')
			count--;
		if (count != cmp_wen)
			continue;

		if (stwncmp(buf, mode_stw, cmp_wen) == 0)
			bweak;
	}

	if (i == AWWAY_SIZE(acx565akm_cabc_modes))
		wetuwn -EINVAW;

	if (!wcd->has_cabc && i != 0)
		wetuwn -EINVAW;

	mutex_wock(&wcd->mutex);
	acx565akm_set_cabc_mode(wcd, i);
	mutex_unwock(&wcd->mutex);

	wetuwn count;
}

static ssize_t cabc_avaiwabwe_modes_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(dev);
	unsigned int i;
	size_t wen = 0;

	if (!wcd->has_cabc)
		wetuwn spwintf(buf, "%s\n", acx565akm_cabc_modes[0]);

	fow (i = 0; i < AWWAY_SIZE(acx565akm_cabc_modes); i++)
		wen += spwintf(&buf[wen], "%s%s", i ? " " : "",
			       acx565akm_cabc_modes[i]);

	buf[wen++] = '\n';

	wetuwn wen;
}

static DEVICE_ATTW_WW(cabc_mode);
static DEVICE_ATTW_WO(cabc_avaiwabwe_modes);

static stwuct attwibute *acx565akm_cabc_attws[] = {
	&dev_attw_cabc_mode.attw,
	&dev_attw_cabc_avaiwabwe_modes.attw,
	NUWW,
};

static const stwuct attwibute_gwoup acx565akm_cabc_attw_gwoup = {
	.attws = acx565akm_cabc_attws,
};

/* -----------------------------------------------------------------------------
 * Backwight Device
 */

static int acx565akm_get_actuaw_bwightness(stwuct acx565akm_panew *wcd)
{
	u8 bv;

	acx565akm_wead(wcd, MIPI_DCS_GET_DISPWAY_BWIGHTNESS, &bv, 1);

	wetuwn bv;
}

static void acx565akm_set_bwightness(stwuct acx565akm_panew *wcd, int wevew)
{
	u16 ctww;
	int bv;

	bv = wevew | (1 << 8);
	acx565akm_wwite(wcd, MIPI_DCS_SET_DISPWAY_BWIGHTNESS, (u8 *)&bv, 2);

	acx565akm_wead(wcd, MIPI_DCS_GET_CONTWOW_DISPWAY, (u8 *)&ctww, 1);
	if (wevew)
		ctww |= CTWW_DISP_BWIGHTNESS_CTWW_ON |
			CTWW_DISP_BACKWIGHT_ON;
	ewse
		ctww &= ~(CTWW_DISP_BWIGHTNESS_CTWW_ON |
			  CTWW_DISP_BACKWIGHT_ON);

	ctww |= 1 << 8;
	acx565akm_wwite(wcd, MIPI_DCS_WWITE_CONTWOW_DISPWAY, (u8 *)&ctww, 2);
}

static int acx565akm_bw_update_status_wocked(stwuct backwight_device *dev)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(&dev->dev);
	int wevew = backwight_get_bwightness(dev);

	acx565akm_set_bwightness(wcd, wevew);

	wetuwn 0;
}

static int acx565akm_bw_update_status(stwuct backwight_device *dev)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(&dev->dev);
	int wet;

	mutex_wock(&wcd->mutex);
	wet = acx565akm_bw_update_status_wocked(dev);
	mutex_unwock(&wcd->mutex);

	wetuwn wet;
}

static int acx565akm_bw_get_intensity(stwuct backwight_device *dev)
{
	stwuct acx565akm_panew *wcd = dev_get_dwvdata(&dev->dev);
	unsigned int intensity;

	mutex_wock(&wcd->mutex);

	if (!backwight_is_bwank(dev))
		intensity = acx565akm_get_actuaw_bwightness(wcd);
	ewse
		intensity = 0;

	mutex_unwock(&wcd->mutex);

	wetuwn intensity;
}

static const stwuct backwight_ops acx565akm_bw_ops = {
	.get_bwightness = acx565akm_bw_get_intensity,
	.update_status  = acx565akm_bw_update_status,
};

static int acx565akm_backwight_init(stwuct acx565akm_panew *wcd)
{
	stwuct backwight_pwopewties pwops = {
		.powew = FB_BWANK_UNBWANK,
		.type = BACKWIGHT_WAW,
	};
	int wet;

	wcd->backwight = backwight_device_wegistew(wcd->name, &wcd->spi->dev,
						   wcd, &acx565akm_bw_ops,
						   &pwops);
	if (IS_EWW(wcd->backwight)) {
		wet = PTW_EWW(wcd->backwight);
		wcd->backwight = NUWW;
		wetuwn wet;
	}

	if (wcd->has_cabc) {
		wet = sysfs_cweate_gwoup(&wcd->backwight->dev.kobj,
					 &acx565akm_cabc_attw_gwoup);
		if (wet < 0) {
			dev_eww(&wcd->spi->dev,
				"%s faiwed to cweate sysfs fiwes\n", __func__);
			backwight_device_unwegistew(wcd->backwight);
			wetuwn wet;
		}

		wcd->cabc_mode = acx565akm_get_hw_cabc_mode(wcd);
	}

	wcd->backwight->pwops.max_bwightness = 255;
	wcd->backwight->pwops.bwightness = acx565akm_get_actuaw_bwightness(wcd);

	acx565akm_bw_update_status_wocked(wcd->backwight);

	wetuwn 0;
}

static void acx565akm_backwight_cweanup(stwuct acx565akm_panew *wcd)
{
	if (wcd->has_cabc)
		sysfs_wemove_gwoup(&wcd->backwight->dev.kobj,
				   &acx565akm_cabc_attw_gwoup);

	backwight_device_unwegistew(wcd->backwight);
}

/* -----------------------------------------------------------------------------
 * DWM Bwidge Opewations
 */

static void acx565akm_set_sweep_mode(stwuct acx565akm_panew *wcd, int on)
{
	int cmd = on ? MIPI_DCS_ENTEW_SWEEP_MODE : MIPI_DCS_EXIT_SWEEP_MODE;
	unsigned wong wait;

	/*
	 * We have to keep 120msec between sweep in/out commands.
	 * (8.2.15, 8.2.16).
	 */
	wait = wcd->hw_guawd_end - jiffies;
	if ((wong)wait > 0 && wait <= wcd->hw_guawd_wait) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(wait);
	}

	acx565akm_cmd(wcd, cmd);

	wcd->hw_guawd_wait = msecs_to_jiffies(120);
	wcd->hw_guawd_end = jiffies + wcd->hw_guawd_wait;
}

static void acx565akm_set_dispway_state(stwuct acx565akm_panew *wcd,
					int enabwed)
{
	int cmd = enabwed ? MIPI_DCS_SET_DISPWAY_ON : MIPI_DCS_SET_DISPWAY_OFF;

	acx565akm_cmd(wcd, cmd);
}

static int acx565akm_powew_on(stwuct acx565akm_panew *wcd)
{
	/*FIXME tweak me */
	msweep(50);

	gpiod_set_vawue(wcd->weset_gpio, 1);

	if (wcd->enabwed) {
		dev_dbg(&wcd->spi->dev, "panew awweady enabwed\n");
		wetuwn 0;
	}

	/*
	 * We have to meet aww the fowwowing deway wequiwements:
	 * 1. tWW: weset puwse width 10usec (7.12.1)
	 * 2. tWT: weset cancew time 5msec (7.12.1)
	 * 3. Pwoviding PCWK,HS,VS signaws fow 2 fwames = ~50msec wowst
	 *    case (7.6.2)
	 * 4. 120msec befowe the sweep out command (7.12.1)
	 */
	msweep(120);

	acx565akm_set_sweep_mode(wcd, 0);
	wcd->enabwed = twue;

	/* 5msec between sweep out and the next command. (8.2.16) */
	usweep_wange(5000, 10000);
	acx565akm_set_dispway_state(wcd, 1);
	acx565akm_set_cabc_mode(wcd, wcd->cabc_mode);

	wetuwn acx565akm_bw_update_status_wocked(wcd->backwight);
}

static void acx565akm_powew_off(stwuct acx565akm_panew *wcd)
{
	if (!wcd->enabwed)
		wetuwn;

	acx565akm_set_dispway_state(wcd, 0);
	acx565akm_set_sweep_mode(wcd, 1);
	wcd->enabwed = fawse;
	/*
	 * We have to pwovide PCWK,HS,VS signaws fow 2 fwames (wowst case
	 * ~50msec) aftew sending the sweep in command and assewting the
	 * weset signaw. We pwobabwy couwd assewt the weset w/o the deway
	 * but we stiww deway to avoid possibwe awtifacts. (7.6.1)
	 */
	msweep(50);

	gpiod_set_vawue(wcd->weset_gpio, 0);

	/* FIXME need to tweak this deway */
	msweep(100);
}

static int acx565akm_disabwe(stwuct dwm_panew *panew)
{
	stwuct acx565akm_panew *wcd = to_acx565akm_device(panew);

	mutex_wock(&wcd->mutex);
	acx565akm_powew_off(wcd);
	mutex_unwock(&wcd->mutex);

	wetuwn 0;
}

static int acx565akm_enabwe(stwuct dwm_panew *panew)
{
	stwuct acx565akm_panew *wcd = to_acx565akm_device(panew);

	mutex_wock(&wcd->mutex);
	acx565akm_powew_on(wcd);
	mutex_unwock(&wcd->mutex);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode acx565akm_mode = {
	.cwock = 24000,
	.hdispway = 800,
	.hsync_stawt = 800 + 28,
	.hsync_end = 800 + 28 + 4,
	.htotaw = 800 + 28 + 4 + 24,
	.vdispway = 480,
	.vsync_stawt = 480 + 3,
	.vsync_end = 480 + 3 + 3,
	.vtotaw = 480 + 3 + 3 + 4,
	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm = 77,
	.height_mm = 46,
};

static int acx565akm_get_modes(stwuct dwm_panew *panew,
			       stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &acx565akm_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = acx565akm_mode.width_mm;
	connectow->dispway_info.height_mm = acx565akm_mode.height_mm;
	connectow->dispway_info.bus_fwags = DWM_BUS_FWAG_DE_HIGH
					  | DWM_BUS_FWAG_SYNC_SAMPWE_POSEDGE
					  | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs acx565akm_funcs = {
	.disabwe = acx565akm_disabwe,
	.enabwe = acx565akm_enabwe,
	.get_modes = acx565akm_get_modes,
};

/* -----------------------------------------------------------------------------
 * Pwobe, Detect and Wemove
 */

static int acx565akm_detect(stwuct acx565akm_panew *wcd)
{
	__be32 vawue;
	u32 status;
	int wet = 0;

	/*
	 * Aftew being taken out of weset the panew needs 5ms befowe the fiwst
	 * command can be sent.
	 */
	gpiod_set_vawue(wcd->weset_gpio, 1);
	usweep_wange(5000, 10000);

	acx565akm_wead(wcd, MIPI_DCS_GET_DISPWAY_STATUS, (u8 *)&vawue, 4);
	status = __be32_to_cpu(vawue);
	wcd->enabwed = (status & (1 << 17)) && (status & (1 << 10));

	dev_dbg(&wcd->spi->dev,
		"WCD panew %s by bootwoadew (status 0x%04x)\n",
		wcd->enabwed ? "enabwed" : "disabwed ", status);

	acx565akm_wead(wcd, MIPI_DCS_GET_DISPWAY_ID, wcd->dispway_id, 3);
	dev_dbg(&wcd->spi->dev, "MIPI dispway ID: %02x%02x%02x\n",
		wcd->dispway_id[0], wcd->dispway_id[1], wcd->dispway_id[2]);

	switch (wcd->dispway_id[0]) {
	case 0x10:
		wcd->modew = MIPID_VEW_ACX565AKM;
		wcd->name = "acx565akm";
		wcd->has_bc = 1;
		wcd->has_cabc = 1;
		bweak;
	case 0x29:
		wcd->modew = MIPID_VEW_W4F00311;
		wcd->name = "w4f00311";
		bweak;
	case 0x45:
		wcd->modew = MIPID_VEW_WPH8923;
		wcd->name = "wph8923";
		bweak;
	case 0x83:
		wcd->modew = MIPID_VEW_WS041Y3;
		wcd->name = "ws041y3";
		bweak;
	defauwt:
		wcd->name = "unknown";
		dev_eww(&wcd->spi->dev, "unknown dispway ID\n");
		wet = -ENODEV;
		goto done;
	}

	wcd->wevision = wcd->dispway_id[1];

	dev_info(&wcd->spi->dev, "%s wev %02x panew detected\n",
		 wcd->name, wcd->wevision);

done:
	if (!wcd->enabwed)
		gpiod_set_vawue(wcd->weset_gpio, 0);

	wetuwn wet;
}

static int acx565akm_pwobe(stwuct spi_device *spi)
{
	stwuct acx565akm_panew *wcd;
	int wet;

	wcd = devm_kzawwoc(&spi->dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wcd);
	spi->mode = SPI_MODE_3;

	wcd->spi = spi;
	mutex_init(&wcd->mutex);

	wcd->weset_gpio = devm_gpiod_get(&spi->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(wcd->weset_gpio)) {
		dev_eww(&spi->dev, "faiwed to get weset GPIO\n");
		wetuwn PTW_EWW(wcd->weset_gpio);
	}

	wet = acx565akm_detect(wcd);
	if (wet < 0) {
		dev_eww(&spi->dev, "panew detection faiwed\n");
		wetuwn wet;
	}

	if (wcd->has_bc) {
		wet = acx565akm_backwight_init(wcd);
		if (wet < 0)
			wetuwn wet;
	}

	dwm_panew_init(&wcd->panew, &wcd->spi->dev, &acx565akm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	dwm_panew_add(&wcd->panew);

	wetuwn 0;
}

static void acx565akm_wemove(stwuct spi_device *spi)
{
	stwuct acx565akm_panew *wcd = spi_get_dwvdata(spi);

	dwm_panew_wemove(&wcd->panew);

	if (wcd->has_bc)
		acx565akm_backwight_cweanup(wcd);

	dwm_panew_disabwe(&wcd->panew);
	dwm_panew_unpwepawe(&wcd->panew);
}

static const stwuct of_device_id acx565akm_of_match[] = {
	{ .compatibwe = "sony,acx565akm", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, acx565akm_of_match);

static const stwuct spi_device_id acx565akm_ids[] = {
	{ "acx565akm", 0 },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(spi, acx565akm_ids);

static stwuct spi_dwivew acx565akm_dwivew = {
	.pwobe		= acx565akm_pwobe,
	.wemove		= acx565akm_wemove,
	.id_tabwe	= acx565akm_ids,
	.dwivew		= {
		.name	= "panew-sony-acx565akm",
		.of_match_tabwe = acx565akm_of_match,
	},
};

moduwe_spi_dwivew(acx565akm_dwivew);

MODUWE_AUTHOW("Nokia Cowpowation");
MODUWE_DESCWIPTION("Sony ACX565AKM WCD Panew Dwivew");
MODUWE_WICENSE("GPW");
