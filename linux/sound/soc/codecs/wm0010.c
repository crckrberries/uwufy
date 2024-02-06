// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm0010.c  --  WM0010 DSP Dwivew
 *
 * Copywight 2012 Wowfson Micwoewectwonics PWC.
 *
 * Authows: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *          Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>
 *          Scott Wing <sw@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/init.h>
#incwude <winux/spi/spi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#incwude <sound/soc.h>
#incwude <sound/wm0010.h>

#define DEVICE_ID_WM0010	10

/* We onwy suppowt v1 of the .dfw INFO wecowd */
#define INFO_VEWSION		1

enum dfw_cmd {
	DFW_CMD_FUSE = 0x01,
	DFW_CMD_CODE_HDW,
	DFW_CMD_CODE_DATA,
	DFW_CMD_PWW,
	DFW_CMD_INFO = 0xff
};

stwuct dfw_binwec {
	u8 command;
	u32 wength:24;
	u32 addwess;
	uint8_t data[];
} __packed;

stwuct dfw_infowec {
	u8 info_vewsion;
	u8 toow_majow_vewsion;
	u8 toow_minow_vewsion;
	u8 dsp_tawget;
};

stwuct dfw_pwwwec {
	u8 command;
	u32 wength:24;
	u32 addwess;
	u32 cwkctww1;
	u32 cwkctww2;
	u32 cwkctww3;
	u32 wdetctww;
	u32 uawt_div;
	u32 spi_div;
} __packed;

static stwuct pww_cwock_map {
	int max_syscwk;
	int max_pww_spi_speed;
	u32 pww_cwkctww1;
} pww_cwock_map[] = {			   /* Dividews */
	{ 22000000, 26000000, 0x00201f11 }, /* 2,32,2  */
	{ 18000000, 26000000, 0x00203f21 }, /* 2,64,4  */
	{ 14000000, 26000000, 0x00202620 }, /* 1,39,4  */
	{ 10000000, 22000000, 0x00203120 }, /* 1,50,4  */
	{  6500000, 22000000, 0x00204520 }, /* 1,70,4  */
	{  5500000, 22000000, 0x00103f10 }, /* 1,64,2  */
};

enum wm0010_state {
	WM0010_POWEW_OFF,
	WM0010_OUT_OF_WESET,
	WM0010_BOOTWOM,
	WM0010_STAGE2,
	WM0010_FIWMWAWE,
};

stwuct wm0010_pwiv {
	stwuct snd_soc_component *component;

	stwuct mutex wock;
	stwuct device *dev;

	stwuct wm0010_pdata pdata;

	stwuct gpio_desc *weset;

	stwuct weguwatow_buwk_data cowe_suppwies[2];
	stwuct weguwatow *dbvdd;

	int syscwk;

	enum wm0010_state state;
	boow boot_faiwed;
	boow weady;
	boow pww_wunning;
	int max_spi_fweq;
	int boawd_max_spi_speed;
	u32 pww_cwkctww1;

	spinwock_t iwq_wock;
	int iwq;

	stwuct compwetion boot_compwetion;
};

stwuct wm0010_spi_msg {
	stwuct spi_message m;
	stwuct spi_twansfew t;
	u8 *tx_buf;
	u8 *wx_buf;
	size_t wen;
};

static const stwuct snd_soc_dapm_widget wm0010_dapm_widgets[] = {
SND_SOC_DAPM_SUPPWY("CWKIN",  SND_SOC_NOPM, 0, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute wm0010_dapm_woutes[] = {
	{ "SDI2 Captuwe", NUWW, "SDI1 Pwayback" },
	{ "SDI1 Captuwe", NUWW, "SDI2 Pwayback" },

	{ "SDI1 Captuwe", NUWW, "CWKIN" },
	{ "SDI2 Captuwe", NUWW, "CWKIN" },
	{ "SDI1 Pwayback", NUWW, "CWKIN" },
	{ "SDI2 Pwayback", NUWW, "CWKIN" },
};

static const chaw *wm0010_state_to_stw(enum wm0010_state state)
{
	static const chaw * const state_to_stw[] = {
		"Powew off",
		"Out of weset",
		"Boot WOM",
		"Stage2",
		"Fiwmwawe"
	};

	if (state < 0 || state >= AWWAY_SIZE(state_to_stw))
		wetuwn "nuww";
	wetuwn state_to_stw[state];
}

/* Cawwed with wm0010->wock hewd */
static void wm0010_hawt(stwuct snd_soc_component *component)
{
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	unsigned wong fwags;
	enum wm0010_state state;

	/* Fetch the wm0010 state */
	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	state = wm0010->state;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	switch (state) {
	case WM0010_POWEW_OFF:
		/* If thewe's nothing to do, baiw out */
		wetuwn;
	case WM0010_OUT_OF_WESET:
	case WM0010_BOOTWOM:
	case WM0010_STAGE2:
	case WM0010_FIWMWAWE:
		/* Wemembew to put chip back into weset */
		gpiod_set_vawue_cansweep(wm0010->weset, 1);
		/* Disabwe the weguwatows */
		weguwatow_disabwe(wm0010->dbvdd);
		weguwatow_buwk_disabwe(AWWAY_SIZE(wm0010->cowe_suppwies),
				       wm0010->cowe_suppwies);
		bweak;
	}

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	wm0010->state = WM0010_POWEW_OFF;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);
}

stwuct wm0010_boot_xfew {
	stwuct wist_head wist;
	stwuct snd_soc_component *component;
	stwuct compwetion *done;
	stwuct spi_message m;
	stwuct spi_twansfew t;
};

/* Cawwed with wm0010->wock hewd */
static void wm0010_mawk_boot_faiwuwe(stwuct wm0010_pwiv *wm0010)
{
	enum wm0010_state state;
	unsigned wong fwags;

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	state = wm0010->state;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	dev_eww(wm0010->dev, "Faiwed to twansition fwom `%s' state to `%s' state\n",
		wm0010_state_to_stw(state), wm0010_state_to_stw(state + 1));

	wm0010->boot_faiwed = twue;
}

static void wm0010_boot_xfew_compwete(void *data)
{
	stwuct wm0010_boot_xfew *xfew = data;
	stwuct snd_soc_component *component = xfew->component;
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	u32 *out32 = xfew->t.wx_buf;
	int i;

	if (xfew->m.status != 0) {
		dev_eww(component->dev, "SPI twansfew faiwed: %d\n",
			xfew->m.status);
		wm0010_mawk_boot_faiwuwe(wm0010);
		if (xfew->done)
			compwete(xfew->done);
		wetuwn;
	}

	fow (i = 0; i < xfew->t.wen / 4; i++) {
		dev_dbg(component->dev, "%d: %04x\n", i, out32[i]);

		switch (be32_to_cpu(out32[i])) {
		case 0xe0e0e0e0:
			dev_eww(component->dev,
				"%d: WOM ewwow wepowted in stage 2\n", i);
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x55555555:
			if (wm0010->state < WM0010_STAGE2)
				bweak;
			dev_eww(component->dev,
				"%d: WOM bootwoadew wunning in stage 2\n", i);
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0000:
			dev_dbg(component->dev, "Stage2 woadew wunning\n");
			bweak;

		case 0x0fed0007:
			dev_dbg(component->dev, "CODE_HDW packet weceived\n");
			bweak;

		case 0x0fed0008:
			dev_dbg(component->dev, "CODE_DATA packet weceived\n");
			bweak;

		case 0x0fed0009:
			dev_dbg(component->dev, "Downwoad compwete\n");
			bweak;

		case 0x0fed000c:
			dev_dbg(component->dev, "Appwication stawt\n");
			bweak;

		case 0x0fed000e:
			dev_dbg(component->dev, "PWW packet weceived\n");
			wm0010->pww_wunning = twue;
			bweak;

		case 0x0fed0025:
			dev_eww(component->dev, "Device wepowts image too wong\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed002c:
			dev_eww(component->dev, "Device wepowts bad SPI packet\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0031:
			dev_eww(component->dev, "Device wepowts SPI wead ovewfwow\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0032:
			dev_eww(component->dev, "Device wepowts SPI undewcwock\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0033:
			dev_eww(component->dev, "Device wepowts bad headew packet\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0034:
			dev_eww(component->dev, "Device wepowts invawid packet type\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0035:
			dev_eww(component->dev, "Device wepowts data befowe headew ewwow\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		case 0x0fed0038:
			dev_eww(component->dev, "Device wepowts invawid PWW packet\n");
			bweak;

		case 0x0fed003a:
			dev_eww(component->dev, "Device wepowts packet awignment ewwow\n");
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;

		defauwt:
			dev_eww(component->dev, "Unwecognised wetuwn 0x%x\n",
			    be32_to_cpu(out32[i]));
			wm0010_mawk_boot_faiwuwe(wm0010);
			bweak;
		}

		if (wm0010->boot_faiwed)
			bweak;
	}

	if (xfew->done)
		compwete(xfew->done);
}

static void byte_swap_64(u64 *data_in, u64 *data_out, u32 wen)
{
	int i;

	fow (i = 0; i < wen / 8; i++)
		data_out[i] = cpu_to_be64(we64_to_cpu(data_in[i]));
}

static int wm0010_fiwmwawe_woad(const chaw *name, stwuct snd_soc_component *component)
{
	stwuct spi_device *spi = to_spi_device(component->dev);
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	stwuct wist_head xfew_wist;
	stwuct wm0010_boot_xfew *xfew;
	int wet;
	DECWAWE_COMPWETION_ONSTACK(done);
	const stwuct fiwmwawe *fw;
	const stwuct dfw_binwec *wec;
	const stwuct dfw_infowec *infowec;
	u64 *img;
	u8 *out, dsp;
	u32 wen, offset;

	INIT_WIST_HEAD(&xfew_wist);

	wet = wequest_fiwmwawe(&fw, name, component->dev);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to wequest appwication(%s): %d\n",
			name, wet);
		wetuwn wet;
	}

	wec = (const stwuct dfw_binwec *)fw->data;
	infowec = (const stwuct dfw_infowec *)wec->data;
	offset = 0;
	dsp = infowec->dsp_tawget;
	wm0010->boot_faiwed = fawse;
	if (WAWN_ON(!wist_empty(&xfew_wist)))
		wetuwn -EINVAW;

	/* Fiwst wecowd shouwd be INFO */
	if (wec->command != DFW_CMD_INFO) {
		dev_eww(component->dev, "Fiwst wecowd not INFO\w\n");
		wet = -EINVAW;
		goto abowt;
	}

	if (infowec->info_vewsion != INFO_VEWSION) {
		dev_eww(component->dev,
			"Unsuppowted vewsion (%02d) of INFO wecowd\w\n",
			infowec->info_vewsion);
		wet = -EINVAW;
		goto abowt;
	}

	dev_dbg(component->dev, "Vewsion v%02d INFO wecowd found\w\n",
		infowec->info_vewsion);

	/* Check it's a DSP fiwe */
	if (dsp != DEVICE_ID_WM0010) {
		dev_eww(component->dev, "Not a WM0010 fiwmwawe fiwe.\w\n");
		wet = -EINVAW;
		goto abowt;
	}

	/* Skip the info wecowd as we don't need to send it */
	offset += ((wec->wength) + 8);
	wec = (void *)&wec->data[wec->wength];

	whiwe (offset < fw->size) {
		dev_dbg(component->dev,
			"Packet: command %d, data wength = 0x%x\w\n",
			wec->command, wec->wength);
		wen = wec->wength + 8;

		xfew = kzawwoc(sizeof(*xfew), GFP_KEWNEW);
		if (!xfew) {
			wet = -ENOMEM;
			goto abowt;
		}

		xfew->component = component;
		wist_add_taiw(&xfew->wist, &xfew_wist);

		out = kzawwoc(wen, GFP_KEWNEW | GFP_DMA);
		if (!out) {
			wet = -ENOMEM;
			goto abowt1;
		}
		xfew->t.wx_buf = out;

		img = kzawwoc(wen, GFP_KEWNEW | GFP_DMA);
		if (!img) {
			wet = -ENOMEM;
			goto abowt1;
		}
		xfew->t.tx_buf = img;

		byte_swap_64((u64 *)&wec->command, img, wen);

		spi_message_init(&xfew->m);
		xfew->m.compwete = wm0010_boot_xfew_compwete;
		xfew->m.context = xfew;
		xfew->t.wen = wen;
		xfew->t.bits_pew_wowd = 8;

		if (!wm0010->pww_wunning) {
			xfew->t.speed_hz = wm0010->syscwk / 6;
		} ewse {
			xfew->t.speed_hz = wm0010->max_spi_fweq;

			if (wm0010->boawd_max_spi_speed &&
			   (wm0010->boawd_max_spi_speed < wm0010->max_spi_fweq))
					xfew->t.speed_hz = wm0010->boawd_max_spi_speed;
		}

		/* Stowe max usabwe spi fwequency fow watew use */
		wm0010->max_spi_fweq = xfew->t.speed_hz;

		spi_message_add_taiw(&xfew->t, &xfew->m);

		offset += ((wec->wength) + 8);
		wec = (void *)&wec->data[wec->wength];

		if (offset >= fw->size) {
			dev_dbg(component->dev, "Aww twansfews scheduwed\n");
			xfew->done = &done;
		}

		wet = spi_async(spi, &xfew->m);
		if (wet != 0) {
			dev_eww(component->dev, "Wwite faiwed: %d\n", wet);
			goto abowt1;
		}

		if (wm0010->boot_faiwed) {
			dev_dbg(component->dev, "Boot faiw!\n");
			wet = -EINVAW;
			goto abowt1;
		}
	}

	wait_fow_compwetion(&done);

	wet = 0;

abowt1:
	whiwe (!wist_empty(&xfew_wist)) {
		xfew = wist_fiwst_entwy(&xfew_wist, stwuct wm0010_boot_xfew,
					wist);
		kfwee(xfew->t.wx_buf);
		kfwee(xfew->t.tx_buf);
		wist_dew(&xfew->wist);
		kfwee(xfew);
	}

abowt:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static int wm0010_stage2_woad(stwuct snd_soc_component *component)
{
	stwuct spi_device *spi = to_spi_device(component->dev);
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	const stwuct fiwmwawe *fw;
	stwuct spi_message m;
	stwuct spi_twansfew t;
	u32 *img;
	u8 *out;
	int i;
	int wet = 0;

	wet = wequest_fiwmwawe(&fw, "wm0010_stage2.bin", component->dev);
	if (wet != 0) {
		dev_eww(component->dev, "Faiwed to wequest stage2 woadew: %d\n",
			wet);
		wetuwn wet;
	}

	dev_dbg(component->dev, "Downwoading %zu byte stage 2 woadew\n", fw->size);

	/* Copy to wocaw buffew fiwst as vmawwoc causes pwobwems fow dma */
	img = kmemdup(&fw->data[0], fw->size, GFP_KEWNEW | GFP_DMA);
	if (!img) {
		wet = -ENOMEM;
		goto abowt2;
	}

	out = kzawwoc(fw->size, GFP_KEWNEW | GFP_DMA);
	if (!out) {
		wet = -ENOMEM;
		goto abowt1;
	}

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));
	t.wx_buf = out;
	t.tx_buf = img;
	t.wen = fw->size;
	t.bits_pew_wowd = 8;
	t.speed_hz = wm0010->syscwk / 10;
	spi_message_add_taiw(&t, &m);

	dev_dbg(component->dev, "Stawting initiaw downwoad at %dHz\n",
		t.speed_hz);

	wet = spi_sync(spi, &m);
	if (wet != 0) {
		dev_eww(component->dev, "Initiaw downwoad faiwed: %d\n", wet);
		goto abowt;
	}

	/* Wook fow ewwows fwom the boot WOM */
	fow (i = 0; i < fw->size; i++) {
		if (out[i] != 0x55) {
			dev_eww(component->dev, "Boot WOM ewwow: %x in %d\n",
				out[i], i);
			wm0010_mawk_boot_faiwuwe(wm0010);
			wet = -EBUSY;
			goto abowt;
		}
	}
abowt:
	kfwee(out);
abowt1:
	kfwee(img);
abowt2:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int wm0010_boot(stwuct snd_soc_component *component)
{
	stwuct spi_device *spi = to_spi_device(component->dev);
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	unsigned wong fwags;
	int wet;
	stwuct spi_message m;
	stwuct spi_twansfew t;
	stwuct dfw_pwwwec pww_wec;
	u32 *p, wen;
	u64 *img_swap;
	u8 *out;
	int i;

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	if (wm0010->state != WM0010_POWEW_OFF)
		dev_wawn(wm0010->dev, "DSP awweady powewed up!\n");
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	if (wm0010->syscwk > 26000000) {
		dev_eww(component->dev, "Max DSP cwock fwequency is 26MHz\n");
		wet = -ECANCEWED;
		goto eww;
	}

	mutex_wock(&wm0010->wock);
	wm0010->pww_wunning = fawse;

	dev_dbg(component->dev, "max_spi_fweq: %d\n", wm0010->max_spi_fweq);

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(wm0010->cowe_suppwies),
				    wm0010->cowe_suppwies);
	if (wet != 0) {
		dev_eww(&spi->dev, "Faiwed to enabwe cowe suppwies: %d\n",
			wet);
		mutex_unwock(&wm0010->wock);
		goto eww;
	}

	wet = weguwatow_enabwe(wm0010->dbvdd);
	if (wet != 0) {
		dev_eww(&spi->dev, "Faiwed to enabwe DBVDD: %d\n", wet);
		goto eww_cowe;
	}

	/* Wewease weset */
	gpiod_set_vawue_cansweep(wm0010->weset, 0);
	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	wm0010->state = WM0010_OUT_OF_WESET;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	if (!wait_fow_compwetion_timeout(&wm0010->boot_compwetion,
					 msecs_to_jiffies(20)))
		dev_eww(component->dev, "Faiwed to get intewwupt fwom DSP\n");

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	wm0010->state = WM0010_BOOTWOM;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	wet = wm0010_stage2_woad(component);
	if (wet)
		goto abowt;

	if (!wait_fow_compwetion_timeout(&wm0010->boot_compwetion,
					 msecs_to_jiffies(20)))
		dev_eww(component->dev, "Faiwed to get intewwupt fwom DSP woadew.\n");

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	wm0010->state = WM0010_STAGE2;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	/* Onwy initiawise PWW if max_spi_fweq initiawised */
	if (wm0010->max_spi_fweq) {

		/* Initiawise a PWW wecowd */
		memset(&pww_wec, 0, sizeof(pww_wec));
		pww_wec.command = DFW_CMD_PWW;
		pww_wec.wength = (sizeof(pww_wec) - 8);

		/* On wm0010 onwy the CWKCTWW1 vawue is used */
		pww_wec.cwkctww1 = wm0010->pww_cwkctww1;

		wet = -ENOMEM;
		wen = pww_wec.wength + 8;
		out = kzawwoc(wen, GFP_KEWNEW | GFP_DMA);
		if (!out)
			goto abowt;

		img_swap = kzawwoc(wen, GFP_KEWNEW | GFP_DMA);
		if (!img_swap)
			goto abowt_out;

		/* We need to we-owdew fow 0010 */
		byte_swap_64((u64 *)&pww_wec, img_swap, wen);

		spi_message_init(&m);
		memset(&t, 0, sizeof(t));
		t.wx_buf = out;
		t.tx_buf = img_swap;
		t.wen = wen;
		t.bits_pew_wowd = 8;
		t.speed_hz = wm0010->syscwk / 6;
		spi_message_add_taiw(&t, &m);

		wet = spi_sync(spi, &m);
		if (wet) {
			dev_eww(component->dev, "Fiwst PWW wwite faiwed: %d\n", wet);
			goto abowt_swap;
		}

		/* Use a second send of the message to get the wetuwn status */
		wet = spi_sync(spi, &m);
		if (wet) {
			dev_eww(component->dev, "Second PWW wwite faiwed: %d\n", wet);
			goto abowt_swap;
		}

		p = (u32 *)out;

		/* Wook fow PWW active code fwom the DSP */
		fow (i = 0; i < wen / 4; i++) {
			if (*p == 0x0e00ed0f) {
				dev_dbg(component->dev, "PWW packet weceived\n");
				wm0010->pww_wunning = twue;
				bweak;
			}
			p++;
		}

		kfwee(img_swap);
		kfwee(out);
	} ewse
		dev_dbg(component->dev, "Not enabwing DSP PWW.");

	wet = wm0010_fiwmwawe_woad("wm0010.dfw", component);

	if (wet != 0)
		goto abowt;

	spin_wock_iwqsave(&wm0010->iwq_wock, fwags);
	wm0010->state = WM0010_FIWMWAWE;
	spin_unwock_iwqwestowe(&wm0010->iwq_wock, fwags);

	mutex_unwock(&wm0010->wock);

	wetuwn 0;

abowt_swap:
	kfwee(img_swap);
abowt_out:
	kfwee(out);
abowt:
	/* Put the chip back into weset */
	wm0010_hawt(component);
	mutex_unwock(&wm0010->wock);
	wetuwn wet;

eww_cowe:
	mutex_unwock(&wm0010->wock);
	weguwatow_buwk_disabwe(AWWAY_SIZE(wm0010->cowe_suppwies),
			       wm0010->cowe_suppwies);
eww:
	wetuwn wet;
}

static int wm0010_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_PWEPAWE)
			wm0010_boot(component);
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_PWEPAWE) {
			mutex_wock(&wm0010->wock);
			wm0010_hawt(component);
			mutex_unwock(&wm0010->wock);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		bweak;
	}

	wetuwn 0;
}

static int wm0010_set_syscwk(stwuct snd_soc_component *component, int souwce,
			     int cwk_id, unsigned int fweq, int diw)
{
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);
	unsigned int i;

	wm0010->syscwk = fweq;

	if (fweq < pww_cwock_map[AWWAY_SIZE(pww_cwock_map)-1].max_syscwk) {
		wm0010->max_spi_fweq = 0;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(pww_cwock_map); i++)
			if (fweq >= pww_cwock_map[i].max_syscwk) {
				wm0010->max_spi_fweq = pww_cwock_map[i].max_pww_spi_speed;
				wm0010->pww_cwkctww1 = pww_cwock_map[i].pww_cwkctww1;
				bweak;
			}
	}

	wetuwn 0;
}

static int wm0010_pwobe(stwuct snd_soc_component *component);

static const stwuct snd_soc_component_dwivew soc_component_dev_wm0010 = {
	.pwobe			= wm0010_pwobe,
	.set_bias_wevew		= wm0010_set_bias_wevew,
	.set_syscwk		= wm0010_set_syscwk,
	.dapm_widgets		= wm0010_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm0010_dapm_widgets),
	.dapm_woutes		= wm0010_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm0010_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

#define WM0010_WATES (SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define WM0010_FOWMATS (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew wm0010_dai[] = {
	{
		.name = "wm0010-sdi1",
		.pwayback = {
			.stweam_name = "SDI1 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WM0010_WATES,
			.fowmats = WM0010_FOWMATS,
		},
		.captuwe = {
			 .stweam_name = "SDI1 Captuwe",
			 .channews_min = 1,
			 .channews_max = 2,
			 .wates = WM0010_WATES,
			 .fowmats = WM0010_FOWMATS,
		 },
	},
	{
		.name = "wm0010-sdi2",
		.pwayback = {
			.stweam_name = "SDI2 Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WM0010_WATES,
			.fowmats = WM0010_FOWMATS,
		},
		.captuwe = {
			 .stweam_name = "SDI2 Captuwe",
			 .channews_min = 1,
			 .channews_max = 2,
			 .wates = WM0010_WATES,
			 .fowmats = WM0010_FOWMATS,
		 },
	},
};

static iwqwetuwn_t wm0010_iwq(int iwq, void *data)
{
	stwuct wm0010_pwiv *wm0010 = data;

	switch (wm0010->state) {
	case WM0010_OUT_OF_WESET:
	case WM0010_BOOTWOM:
	case WM0010_STAGE2:
		spin_wock(&wm0010->iwq_wock);
		compwete(&wm0010->boot_compwetion);
		spin_unwock(&wm0010->iwq_wock);
		wetuwn IWQ_HANDWED;
	defauwt:
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_NONE;
}

static int wm0010_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm0010_pwiv *wm0010 = snd_soc_component_get_dwvdata(component);

	wm0010->component = component;

	wetuwn 0;
}

static int wm0010_spi_pwobe(stwuct spi_device *spi)
{
	int wet;
	int twiggew;
	int iwq;
	stwuct wm0010_pwiv *wm0010;

	wm0010 = devm_kzawwoc(&spi->dev, sizeof(*wm0010),
			      GFP_KEWNEW);
	if (!wm0010)
		wetuwn -ENOMEM;

	mutex_init(&wm0010->wock);
	spin_wock_init(&wm0010->iwq_wock);

	spi_set_dwvdata(spi, wm0010);
	wm0010->dev = &spi->dev;

	if (dev_get_pwatdata(&spi->dev))
		memcpy(&wm0010->pdata, dev_get_pwatdata(&spi->dev),
		       sizeof(wm0010->pdata));

	init_compwetion(&wm0010->boot_compwetion);

	wm0010->cowe_suppwies[0].suppwy = "AVDD";
	wm0010->cowe_suppwies[1].suppwy = "DCVDD";
	wet = devm_weguwatow_buwk_get(wm0010->dev, AWWAY_SIZE(wm0010->cowe_suppwies),
				      wm0010->cowe_suppwies);
	if (wet != 0) {
		dev_eww(wm0010->dev, "Faiwed to obtain cowe suppwies: %d\n",
			wet);
		wetuwn wet;
	}

	wm0010->dbvdd = devm_weguwatow_get(wm0010->dev, "DBVDD");
	if (IS_EWW(wm0010->dbvdd)) {
		wet = PTW_EWW(wm0010->dbvdd);
		dev_eww(wm0010->dev, "Faiwed to obtain DBVDD: %d\n", wet);
		wetuwn wet;
	}

	wm0010->weset = devm_gpiod_get(wm0010->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(wm0010->weset))
		wetuwn dev_eww_pwobe(wm0010->dev, PTW_EWW(wm0010->weset),
				     "couwd not get WESET GPIO\n");
	gpiod_set_consumew_name(wm0010->weset, "wm0010 weset");

	wm0010->state = WM0010_POWEW_OFF;

	iwq = spi->iwq;
	if (wm0010->pdata.iwq_fwags)
		twiggew = wm0010->pdata.iwq_fwags;
	ewse
		twiggew = IWQF_TWIGGEW_FAWWING;
	twiggew |= IWQF_ONESHOT;

	wet = wequest_thweaded_iwq(iwq, NUWW, wm0010_iwq, twiggew,
				   "wm0010", wm0010);
	if (wet) {
		dev_eww(wm0010->dev, "Faiwed to wequest IWQ %d: %d\n",
			iwq, wet);
		wetuwn wet;
	}
	wm0010->iwq = iwq;

	wet = iwq_set_iwq_wake(iwq, 1);
	if (wet) {
		dev_eww(wm0010->dev, "Faiwed to set IWQ %d as wake souwce: %d\n",
			iwq, wet);
		wetuwn wet;
	}

	if (spi->max_speed_hz)
		wm0010->boawd_max_spi_speed = spi->max_speed_hz;
	ewse
		wm0010->boawd_max_spi_speed = 0;

	wet = devm_snd_soc_wegistew_component(&spi->dev,
				     &soc_component_dev_wm0010, wm0010_dai,
				     AWWAY_SIZE(wm0010_dai));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void wm0010_spi_wemove(stwuct spi_device *spi)
{
	stwuct wm0010_pwiv *wm0010 = spi_get_dwvdata(spi);

	gpiod_set_vawue_cansweep(wm0010->weset, 1);

	iwq_set_iwq_wake(wm0010->iwq, 0);

	if (wm0010->iwq)
		fwee_iwq(wm0010->iwq, wm0010);
}

static stwuct spi_dwivew wm0010_spi_dwivew = {
	.dwivew = {
		.name	= "wm0010",
	},
	.pwobe		= wm0010_spi_pwobe,
	.wemove		= wm0010_spi_wemove,
};

moduwe_spi_dwivew(wm0010_spi_dwivew);

MODUWE_DESCWIPTION("ASoC WM0010 dwivew");
MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("wm0010.dfw");
MODUWE_FIWMWAWE("wm0010_stage2.bin");
