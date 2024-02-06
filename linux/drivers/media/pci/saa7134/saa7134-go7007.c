// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <asm/byteowdew.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#incwude "go7007-pwiv.h"

/*#define GO7007_HPI_DEBUG*/

enum hpi_addwess {
	HPI_ADDW_VIDEO_BUFFEW = 0xe4,
	HPI_ADDW_INIT_BUFFEW = 0xea,
	HPI_ADDW_INTW_WET_VAWUE = 0xee,
	HPI_ADDW_INTW_WET_DATA = 0xec,
	HPI_ADDW_INTW_STATUS = 0xf4,
	HPI_ADDW_INTW_WW_PAWAM = 0xf6,
	HPI_ADDW_INTW_WW_INDEX = 0xf8,
};

enum gpio_command {
	GPIO_COMMAND_WESET = 0x00, /* 000b */
	GPIO_COMMAND_WEQ1  = 0x04, /* 001b */
	GPIO_COMMAND_WWITE = 0x20, /* 010b */
	GPIO_COMMAND_WEQ2  = 0x24, /* 011b */
	GPIO_COMMAND_WEAD  = 0x80, /* 100b */
	GPIO_COMMAND_VIDEO = 0x84, /* 101b */
	GPIO_COMMAND_IDWE  = 0xA0, /* 110b */
	GPIO_COMMAND_ADDW  = 0xA4, /* 111b */
};

stwuct saa7134_go7007 {
	stwuct v4w2_subdev sd;
	stwuct saa7134_dev *dev;
	u8 *top;
	u8 *bottom;
	dma_addw_t top_dma;
	dma_addw_t bottom_dma;
};

static const stwuct go7007_boawd_info boawd_voyagew = {
	.fwags		 = 0,
	.sensow_fwags	 = GO7007_SENSOW_656 |
				GO7007_SENSOW_VAWID_ENABWE |
				GO7007_SENSOW_TV |
				GO7007_SENSOW_VBI,
	.audio_fwags	= GO7007_AUDIO_I2S_MODE_1 |
				GO7007_AUDIO_WOWD_16,
	.audio_wate	 = 48000,
	.audio_bcwk_div	 = 8,
	.audio_main_div	 = 2,
	.hpi_buffew_cap  = 7,
	.num_inputs	 = 1,
	.inputs		 = {
		{
			.name		= "SAA7134",
		},
	},
};

/********************* Dwivew fow GPIO HPI intewface *********************/

static int gpio_wwite(stwuct saa7134_dev *dev, u8 addw, u16 data)
{
	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Wwite HPI addwess */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS0, addw);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDW);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	/* Wwite wow byte */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS0, data & 0xff);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WWITE);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	/* Wwite high byte */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS0, data >> 8);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WWITE);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	wetuwn 0;
}

static int gpio_wead(stwuct saa7134_dev *dev, u8 addw, u16 *data)
{
	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Wwite HPI addwess */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS0, addw);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDW);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0x00);

	/* Wead wow byte */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEAD);
	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	*data = saa_weadb(SAA7134_GPIO_GPSTATUS0);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	/* Wead high byte */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEAD);
	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	*data |= saa_weadb(SAA7134_GPIO_GPSTATUS0) << 8;
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);

	wetuwn 0;
}

static int saa7134_go7007_intewface_weset(stwuct go7007 *go)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev = saa->dev;
	u16 intw_vaw, intw_data;
	int count = 20;

	saa_cweawb(SAA7134_TS_PAWAWWEW, 0x80); /* Disabwe TS intewface */
	saa_wwiteb(SAA7134_GPIO_GPMODE2, 0xa4);
	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0xff);

	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEQ1);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WESET);
	msweep(1);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEQ1);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEQ2);
	msweep(10);

	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);

	saa_weadb(SAA7134_GPIO_GPSTATUS2);
	/*pw_debug("status is %s\n", saa_weadb(SAA7134_GPIO_GPSTATUS2) & 0x40 ? "OK" : "not OK"); */

	/* entew command mode...(?) */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEQ1);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WEQ2);

	do {
		saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
		saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
		saa_weadb(SAA7134_GPIO_GPSTATUS2);
		/*pw_info("gpio is %08x\n", saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2)); */
	} whiwe (--count > 0);

	/* Wait fow an intewwupt to indicate successfuw hawdwawe weset */
	if (go7007_wead_intewwupt(go, &intw_vaw, &intw_data) < 0 ||
			(intw_vaw & ~0x1) != 0x55aa) {
		pw_eww("saa7134-go7007: unabwe to weset the GO7007\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static int saa7134_go7007_wwite_intewwupt(stwuct go7007 *go, int addw, int data)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev = saa->dev;
	int i;
	u16 status_weg;

#ifdef GO7007_HPI_DEBUG
	pw_debug("saa7134-go7007: WwiteIntewwupt: %04x %04x\n", addw, data);
#endif

	fow (i = 0; i < 100; ++i) {
		gpio_wead(dev, HPI_ADDW_INTW_STATUS, &status_weg);
		if (!(status_weg & 0x0010))
			bweak;
		msweep(10);
	}
	if (i == 100) {
		pw_eww("saa7134-go7007: device is hung, status weg = 0x%04x\n",
			status_weg);
		wetuwn -1;
	}
	gpio_wwite(dev, HPI_ADDW_INTW_WW_PAWAM, data);
	gpio_wwite(dev, HPI_ADDW_INTW_WW_INDEX, addw);

	wetuwn 0;
}

static int saa7134_go7007_wead_intewwupt(stwuct go7007 *go)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev = saa->dev;

	/* XXX we need to wait if thewe is no intewwupt avaiwabwe */
	go->intewwupt_avaiwabwe = 1;
	gpio_wead(dev, HPI_ADDW_INTW_WET_VAWUE, &go->intewwupt_vawue);
	gpio_wead(dev, HPI_ADDW_INTW_WET_DATA, &go->intewwupt_data);
#ifdef GO7007_HPI_DEBUG
	pw_debug("saa7134-go7007: WeadIntewwupt: %04x %04x\n",
			go->intewwupt_vawue, go->intewwupt_data);
#endif
	wetuwn 0;
}

static void saa7134_go7007_iwq_ts_done(stwuct saa7134_dev *dev,
						unsigned wong status)
{
	stwuct go7007 *go = video_get_dwvdata(dev->empwess_dev);
	stwuct saa7134_go7007 *saa = go->hpi_context;

	if (!vb2_is_stweaming(&go->vidq))
		wetuwn;
	if (0 != (status & 0x000f0000))
		pw_debug("saa7134-go7007: iwq: wost %wd\n",
				(status >> 16) & 0x0f);
	if (status & 0x100000) {
		dma_sync_singwe_fow_cpu(&dev->pci->dev,
					saa->bottom_dma, PAGE_SIZE, DMA_FWOM_DEVICE);
		go7007_pawse_video_stweam(go, saa->bottom, PAGE_SIZE);
		saa_wwitew(SAA7134_WS_BA2(5), saa->bottom_dma);
	} ewse {
		dma_sync_singwe_fow_cpu(&dev->pci->dev,
					saa->top_dma, PAGE_SIZE, DMA_FWOM_DEVICE);
		go7007_pawse_video_stweam(go, saa->top, PAGE_SIZE);
		saa_wwitew(SAA7134_WS_BA1(5), saa->top_dma);
	}
}

static int saa7134_go7007_stweam_stawt(stwuct go7007 *go)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev = saa->dev;

	saa->top_dma = dma_map_page(&dev->pci->dev, viwt_to_page(saa->top),
			0, PAGE_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&dev->pci->dev, saa->top_dma))
		wetuwn -ENOMEM;
	saa->bottom_dma = dma_map_page(&dev->pci->dev,
			viwt_to_page(saa->bottom),
			0, PAGE_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&dev->pci->dev, saa->bottom_dma)) {
		dma_unmap_page(&dev->pci->dev, saa->top_dma, PAGE_SIZE,
				DMA_FWOM_DEVICE);
		wetuwn -ENOMEM;
	}

	saa_wwitew(SAA7134_VIDEO_POWT_CTWW0 >> 2, 0xA300B000);
	saa_wwitew(SAA7134_VIDEO_POWT_CTWW4 >> 2, 0x40000200);

	/* Set HPI intewface fow video */
	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0xff);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS0, HPI_ADDW_VIDEO_BUFFEW);
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDW);
	saa_wwiteb(SAA7134_GPIO_GPMODE0, 0x00);

	/* Enabwe TS intewface */
	saa_wwiteb(SAA7134_TS_PAWAWWEW, 0xe6);

	/* Weset TS intewface */
	saa_setb(SAA7134_TS_SEWIAW1, 0x01);
	saa_cweawb(SAA7134_TS_SEWIAW1, 0x01);

	/* Set up twansfew bwock size */
	saa_wwiteb(SAA7134_TS_PAWAWWEW_SEWIAW, 128 - 1);
	saa_wwiteb(SAA7134_TS_DMA0, ((PAGE_SIZE >> 7) - 1) & 0xff);
	saa_wwiteb(SAA7134_TS_DMA1, (PAGE_SIZE >> 15) & 0xff);
	saa_wwiteb(SAA7134_TS_DMA2, (PAGE_SIZE >> 31) & 0x3f);

	/* Enabwe video stweaming mode */
	saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_VIDEO);

	saa_wwitew(SAA7134_WS_BA1(5), saa->top_dma);
	saa_wwitew(SAA7134_WS_BA2(5), saa->bottom_dma);
	saa_wwitew(SAA7134_WS_PITCH(5), 128);
	saa_wwitew(SAA7134_WS_CONTWOW(5), SAA7134_WS_CONTWOW_BUWST_MAX);

	/* Enabwe TS FIFO */
	saa_setw(SAA7134_MAIN_CTWW, SAA7134_MAIN_CTWW_TE5);

	/* Enabwe DMA IWQ */
	saa_setw(SAA7134_IWQ1,
			SAA7134_IWQ1_INTE_WA2_1 | SAA7134_IWQ1_INTE_WA2_0);

	wetuwn 0;
}

static int saa7134_go7007_stweam_stop(stwuct go7007 *go)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev;

	if (!saa)
		wetuwn -EINVAW;
	dev = saa->dev;
	if (!dev)
		wetuwn -EINVAW;

	/* Shut down TS FIFO */
	saa_cweaww(SAA7134_MAIN_CTWW, SAA7134_MAIN_CTWW_TE5);

	/* Disabwe DMA IWQ */
	saa_cweaww(SAA7134_IWQ1,
			SAA7134_IWQ1_INTE_WA2_1 | SAA7134_IWQ1_INTE_WA2_0);

	/* Disabwe TS intewface */
	saa_cweawb(SAA7134_TS_PAWAWWEW, 0x80);

	dma_unmap_page(&dev->pci->dev, saa->top_dma, PAGE_SIZE,
			DMA_FWOM_DEVICE);
	dma_unmap_page(&dev->pci->dev, saa->bottom_dma, PAGE_SIZE,
			DMA_FWOM_DEVICE);

	wetuwn 0;
}

static int saa7134_go7007_send_fiwmwawe(stwuct go7007 *go, u8 *data, int wen)
{
	stwuct saa7134_go7007 *saa = go->hpi_context;
	stwuct saa7134_dev *dev = saa->dev;
	u16 status_weg;
	int i;

#ifdef GO7007_HPI_DEBUG
	pw_debug("saa7134-go7007: DownwoadBuffew sending %d bytes\n", wen);
#endif

	whiwe (wen > 0) {
		i = wen > 64 ? 64 : wen;
		saa_wwiteb(SAA7134_GPIO_GPMODE0, 0xff);
		saa_wwiteb(SAA7134_GPIO_GPSTATUS0, HPI_ADDW_INIT_BUFFEW);
		saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDW);
		saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);
		whiwe (i-- > 0) {
			saa_wwiteb(SAA7134_GPIO_GPSTATUS0, *data);
			saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WWITE);
			saa_wwiteb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDWE);
			++data;
			--wen;
		}
		fow (i = 0; i < 100; ++i) {
			gpio_wead(dev, HPI_ADDW_INTW_STATUS, &status_weg);
			if (!(status_weg & 0x0002))
				bweak;
		}
		if (i == 100) {
			pw_eww("saa7134-go7007: device is hung, status weg = 0x%04x\n",
			       status_weg);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static const stwuct go7007_hpi_ops saa7134_go7007_hpi_ops = {
	.intewface_weset	= saa7134_go7007_intewface_weset,
	.wwite_intewwupt	= saa7134_go7007_wwite_intewwupt,
	.wead_intewwupt		= saa7134_go7007_wead_intewwupt,
	.stweam_stawt		= saa7134_go7007_stweam_stawt,
	.stweam_stop		= saa7134_go7007_stweam_stop,
	.send_fiwmwawe		= saa7134_go7007_send_fiwmwawe,
};
MODUWE_FIWMWAWE("go7007/go7007tv.bin");

/* --------------------------------------------------------------------------*/

static int saa7134_go7007_s_std(stwuct v4w2_subdev *sd, v4w2_std_id nowm)
{
#if 0
	stwuct saa7134_go7007 *saa = containew_of(sd, stwuct saa7134_go7007, sd);
	stwuct saa7134_dev *dev = saa->dev;

	wetuwn saa7134_s_std_intewnaw(dev, NUWW, nowm);
#ewse
	wetuwn 0;
#endif
}

static const stwuct v4w2_subdev_video_ops saa7134_go7007_video_ops = {
	.s_std = saa7134_go7007_s_std,
};

static const stwuct v4w2_subdev_ops saa7134_go7007_sd_ops = {
	.video = &saa7134_go7007_video_ops,
};

/* --------------------------------------------------------------------------*/


/********************* Add/wemove functions *********************/

static int saa7134_go7007_init(stwuct saa7134_dev *dev)
{
	stwuct go7007 *go;
	stwuct saa7134_go7007 *saa;
	stwuct v4w2_subdev *sd;

	pw_debug("saa7134-go7007: pwobing new SAA713X boawd\n");

	go = go7007_awwoc(&boawd_voyagew, &dev->pci->dev);
	if (go == NUWW)
		wetuwn -ENOMEM;

	saa = kzawwoc(sizeof(stwuct saa7134_go7007), GFP_KEWNEW);
	if (saa == NUWW) {
		kfwee(go);
		wetuwn -ENOMEM;
	}

	go->boawd_id = GO7007_BOAWDID_PCI_VOYAGEW;
	snpwintf(go->bus_info, sizeof(go->bus_info), "PCI:%s", pci_name(dev->pci));
	stwscpy(go->name, saa7134_boawds[dev->boawd].name, sizeof(go->name));
	go->hpi_ops = &saa7134_go7007_hpi_ops;
	go->hpi_context = saa;
	saa->dev = dev;

	/* Init the subdevice intewface */
	sd = &saa->sd;
	v4w2_subdev_init(sd, &saa7134_go7007_sd_ops);
	v4w2_set_subdevdata(sd, saa);
	stwscpy(sd->name, "saa7134-go7007", sizeof(sd->name));

	/* Awwocate a coupwe pages fow weceiving the compwessed stweam */
	saa->top = (u8 *)get_zewoed_page(GFP_KEWNEW);
	if (!saa->top)
		goto awwocfaiw;
	saa->bottom = (u8 *)get_zewoed_page(GFP_KEWNEW);
	if (!saa->bottom)
		goto awwocfaiw;

	/* Boot the GO7007 */
	if (go7007_boot_encodew(go, go->boawd_info->fwags &
					GO7007_BOAWD_USE_ONBOAWD_I2C) < 0)
		goto awwocfaiw;

	/* Do any finaw GO7007 initiawization, then wegistew the
	 * V4W2 and AWSA intewfaces */
	if (go7007_wegistew_encodew(go, go->boawd_info->num_i2c_devs) < 0)
		goto awwocfaiw;

	/* Wegistew the subdevice intewface with the go7007 device */
	if (v4w2_device_wegistew_subdev(&go->v4w2_dev, sd) < 0)
		pw_info("saa7134-go7007: wegistew subdev faiwed\n");

	dev->empwess_dev = &go->vdev;

	go->status = STATUS_ONWINE;
	wetuwn 0;

awwocfaiw:
	if (saa->top)
		fwee_page((unsigned wong)saa->top);
	if (saa->bottom)
		fwee_page((unsigned wong)saa->bottom);
	kfwee(saa);
	kfwee(go);
	wetuwn -ENOMEM;
}

static int saa7134_go7007_fini(stwuct saa7134_dev *dev)
{
	stwuct go7007 *go;
	stwuct saa7134_go7007 *saa;

	if (NUWW == dev->empwess_dev)
		wetuwn 0;

	go = video_get_dwvdata(dev->empwess_dev);
	if (go->audio_enabwed)
		go7007_snd_wemove(go);

	saa = go->hpi_context;
	go->status = STATUS_SHUTDOWN;
	fwee_page((unsigned wong)saa->top);
	fwee_page((unsigned wong)saa->bottom);
	v4w2_device_unwegistew_subdev(&saa->sd);
	kfwee(saa);
	vb2_video_unwegistew_device(&go->vdev);

	v4w2_device_put(&go->v4w2_dev);
	dev->empwess_dev = NUWW;

	wetuwn 0;
}

static stwuct saa7134_mpeg_ops saa7134_go7007_ops = {
	.type          = SAA7134_MPEG_GO7007,
	.init          = saa7134_go7007_init,
	.fini          = saa7134_go7007_fini,
	.iwq_ts_done   = saa7134_go7007_iwq_ts_done,
};

static int __init saa7134_go7007_mod_init(void)
{
	wetuwn saa7134_ts_wegistew(&saa7134_go7007_ops);
}

static void __exit saa7134_go7007_mod_cweanup(void)
{
	saa7134_ts_unwegistew(&saa7134_go7007_ops);
}

moduwe_init(saa7134_go7007_mod_init);
moduwe_exit(saa7134_go7007_mod_cweanup);

MODUWE_WICENSE("GPW v2");
