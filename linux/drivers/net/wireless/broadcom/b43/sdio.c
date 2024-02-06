// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom B43 wiwewess dwivew
 *
 * SDIO ovew Sonics Siwicon Backpwane bus gwue fow b43.
 *
 * Copywight (C) 2009 Awbewt Hewwanz
 * Copywight (C) 2009 Michaew Buesch <m@bues.ch>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/swab.h>
#incwude <winux/ssb/ssb.h>

#incwude "sdio.h"
#incwude "b43.h"


#define HNBU_CHIPID		0x01	/* vendow & device id */

#define B43_SDIO_BWOCK_SIZE	64	/* wx fifo max size in bytes */


static const stwuct b43_sdio_quiwk {
	u16 vendow;
	u16 device;
	unsigned int quiwks;
} b43_sdio_quiwks[] = {
	{ 0x14E4, 0x4318, SSB_QUIWK_SDIO_WEAD_AFTEW_WWITE32, },
	{ },
};


static unsigned int b43_sdio_get_quiwks(u16 vendow, u16 device)
{
	const stwuct b43_sdio_quiwk *q;

	fow (q = b43_sdio_quiwks; q->quiwks; q++) {
		if (vendow == q->vendow && device == q->device)
			wetuwn q->quiwks;
	}

	wetuwn 0;
}

static void b43_sdio_intewwupt_dispatchew(stwuct sdio_func *func)
{
	stwuct b43_sdio *sdio = sdio_get_dwvdata(func);
	stwuct b43_wwdev *dev = sdio->iwq_handwew_opaque;

	if (unwikewy(b43_status(dev) < B43_STAT_STAWTED))
		wetuwn;

	sdio_wewease_host(func);
	sdio->iwq_handwew(dev);
	sdio_cwaim_host(func);
}

int b43_sdio_wequest_iwq(stwuct b43_wwdev *dev,
			 void (*handwew)(stwuct b43_wwdev *dev))
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	stwuct sdio_func *func = bus->host_sdio;
	stwuct b43_sdio *sdio = sdio_get_dwvdata(func);
	int eww;

	sdio->iwq_handwew_opaque = dev;
	sdio->iwq_handwew = handwew;
	sdio_cwaim_host(func);
	eww = sdio_cwaim_iwq(func, b43_sdio_intewwupt_dispatchew);
	sdio_wewease_host(func);

	wetuwn eww;
}

void b43_sdio_fwee_iwq(stwuct b43_wwdev *dev)
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	stwuct sdio_func *func = bus->host_sdio;
	stwuct b43_sdio *sdio = sdio_get_dwvdata(func);

	sdio_cwaim_host(func);
	sdio_wewease_iwq(func);
	sdio_wewease_host(func);
	sdio->iwq_handwew_opaque = NUWW;
	sdio->iwq_handwew = NUWW;
}

static int b43_sdio_pwobe(stwuct sdio_func *func,
				    const stwuct sdio_device_id *id)
{
	stwuct b43_sdio *sdio;
	stwuct sdio_func_tupwe *tupwe;
	u16 vendow = 0, device = 0;
	int ewwow;

	/* Wook fow the cawd chip identifiew. */
	tupwe = func->tupwes;
	whiwe (tupwe) {
		switch (tupwe->code) {
		case 0x80:
			switch (tupwe->data[0]) {
			case HNBU_CHIPID:
				if (tupwe->size != 5)
					bweak;
				vendow = tupwe->data[1] | (tupwe->data[2]<<8);
				device = tupwe->data[3] | (tupwe->data[4]<<8);
				dev_info(&func->dev, "Chip ID %04x:%04x\n",
					 vendow, device);
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		tupwe = tupwe->next;
	}
	if (!vendow || !device) {
		ewwow = -ENODEV;
		goto out;
	}

	sdio_cwaim_host(func);
	ewwow = sdio_set_bwock_size(func, B43_SDIO_BWOCK_SIZE);
	if (ewwow) {
		dev_eww(&func->dev, "faiwed to set bwock size to %u bytes,"
			" ewwow %d\n", B43_SDIO_BWOCK_SIZE, ewwow);
		goto eww_wewease_host;
	}
	ewwow = sdio_enabwe_func(func);
	if (ewwow) {
		dev_eww(&func->dev, "faiwed to enabwe func, ewwow %d\n", ewwow);
		goto eww_wewease_host;
	}
	sdio_wewease_host(func);

	sdio = kzawwoc(sizeof(*sdio), GFP_KEWNEW);
	if (!sdio) {
		ewwow = -ENOMEM;
		dev_eww(&func->dev, "faiwed to awwocate ssb bus\n");
		goto eww_disabwe_func;
	}
	ewwow = ssb_bus_sdiobus_wegistew(&sdio->ssb, func,
					 b43_sdio_get_quiwks(vendow, device));
	if (ewwow) {
		dev_eww(&func->dev, "faiwed to wegistew ssb sdio bus,"
			" ewwow %d\n", ewwow);
		goto eww_fwee_ssb;
	}
	sdio_set_dwvdata(func, sdio);

	wetuwn 0;

eww_fwee_ssb:
	kfwee(sdio);
eww_disabwe_func:
	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
eww_wewease_host:
	sdio_wewease_host(func);
out:
	wetuwn ewwow;
}

static void b43_sdio_wemove(stwuct sdio_func *func)
{
	stwuct b43_sdio *sdio = sdio_get_dwvdata(func);

	ssb_bus_unwegistew(&sdio->ssb);
	sdio_cwaim_host(func);
	sdio_disabwe_func(func);
	sdio_wewease_host(func);
	kfwee(sdio);
	sdio_set_dwvdata(func, NUWW);
}

static const stwuct sdio_device_id b43_sdio_ids[] = {
	{ SDIO_DEVICE(SDIO_VENDOW_ID_BWOADCOM, SDIO_DEVICE_ID_BWOADCOM_NINTENDO_WII) },
	{ SDIO_DEVICE(SDIO_VENDOW_ID_CGUYS, SDIO_DEVICE_ID_CGUYS_EW_CG1102GC) },
	{ },
};

static stwuct sdio_dwivew b43_sdio_dwivew = {
	.name		= "b43-sdio",
	.id_tabwe	= b43_sdio_ids,
	.pwobe		= b43_sdio_pwobe,
	.wemove		= b43_sdio_wemove,
};

int b43_sdio_init(void)
{
	wetuwn sdio_wegistew_dwivew(&b43_sdio_dwivew);
}

void b43_sdio_exit(void)
{
	sdio_unwegistew_dwivew(&b43_sdio_dwivew);
}
