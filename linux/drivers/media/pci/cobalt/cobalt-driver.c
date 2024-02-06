// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cobawt dwivew initiawization and cawd pwobing
 *
 *  Dewived fwom cx18-dwivew.c
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <media/i2c/adv7604.h>
#incwude <media/i2c/adv7842.h>
#incwude <media/i2c/adv7511.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>

#incwude "cobawt-dwivew.h"
#incwude "cobawt-iwq.h"
#incwude "cobawt-i2c.h"
#incwude "cobawt-v4w2.h"
#incwude "cobawt-fwash.h"
#incwude "cobawt-awsa.h"
#incwude "cobawt-omnitek.h"

/* add youw wevision and whatnot hewe */
static const stwuct pci_device_id cobawt_pci_tbw[] = {
	{PCI_VENDOW_ID_CISCO, PCI_DEVICE_ID_COBAWT,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0,}
};

MODUWE_DEVICE_TABWE(pci, cobawt_pci_tbw);

static atomic_t cobawt_instance = ATOMIC_INIT(0);

int cobawt_debug;
moduwe_pawam_named(debug, cobawt_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew. Defauwt: 0\n");

int cobawt_ignowe_eww;
moduwe_pawam_named(ignowe_eww, cobawt_ignowe_eww, int, 0644);
MODUWE_PAWM_DESC(ignowe_eww,
	"If set then ignowe missing i2c adaptews/weceivews. Defauwt: 0\n");

MODUWE_AUTHOW("Hans Vewkuiw <hans.vewkuiw@cisco.com> & Mowten Hestnes");
MODUWE_DESCWIPTION("cobawt dwivew");
MODUWE_WICENSE("GPW");

static u8 edid[256] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x50, 0x21, 0x32, 0x27, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x1a, 0x01, 0x03, 0x80, 0x30, 0x1b, 0x78,
	0x0f, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26,
	0x0f, 0x50, 0x54, 0x2f, 0xcf, 0x00, 0x31, 0x59,
	0x45, 0x59, 0x61, 0x59, 0x81, 0x99, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3a,
	0x80, 0x18, 0x71, 0x38, 0x2d, 0x40, 0x58, 0x2c,
	0x45, 0x00, 0xe0, 0x0e, 0x11, 0x00, 0x00, 0x1e,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x55, 0x18,
	0x5e, 0x11, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x63,
	0x6f, 0x62, 0x61, 0x6c, 0x74, 0x0a, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9d,

	0x02, 0x03, 0x1f, 0xf1, 0x4a, 0x10, 0x1f, 0x04,
	0x13, 0x22, 0x21, 0x20, 0x02, 0x11, 0x01, 0x23,
	0x09, 0x07, 0x07, 0x68, 0x03, 0x0c, 0x00, 0x10,
	0x00, 0x00, 0x22, 0x0f, 0xe2, 0x00, 0xca, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46,
};

static void cobawt_set_intewwupt(stwuct cobawt *cobawt, boow enabwe)
{
	if (enabwe) {
		unsigned iwqs = COBAWT_SYSSTAT_VI0_INT1_MSK |
				COBAWT_SYSSTAT_VI1_INT1_MSK |
				COBAWT_SYSSTAT_VI2_INT1_MSK |
				COBAWT_SYSSTAT_VI3_INT1_MSK |
				COBAWT_SYSSTAT_VI0_INT2_MSK |
				COBAWT_SYSSTAT_VI1_INT2_MSK |
				COBAWT_SYSSTAT_VI2_INT2_MSK |
				COBAWT_SYSSTAT_VI3_INT2_MSK |
				COBAWT_SYSSTAT_VI0_WOST_DATA_MSK |
				COBAWT_SYSSTAT_VI1_WOST_DATA_MSK |
				COBAWT_SYSSTAT_VI2_WOST_DATA_MSK |
				COBAWT_SYSSTAT_VI3_WOST_DATA_MSK |
				COBAWT_SYSSTAT_AUD_IN_WOST_DATA_MSK;

		if (cobawt->have_hsma_wx)
			iwqs |= COBAWT_SYSSTAT_VIHSMA_INT1_MSK |
				COBAWT_SYSSTAT_VIHSMA_INT2_MSK |
				COBAWT_SYSSTAT_VIHSMA_WOST_DATA_MSK;

		if (cobawt->have_hsma_tx)
			iwqs |= COBAWT_SYSSTAT_VOHSMA_INT1_MSK |
				COBAWT_SYSSTAT_VOHSMA_WOST_DATA_MSK |
				COBAWT_SYSSTAT_AUD_OUT_WOST_DATA_MSK;
		/* Cweaw any existing intewwupts */
		cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_EDGE, 0xffffffff);
		/* PIO Cowe intewwupt mask wegistew.
		   Enabwe ADV7604 INT1 intewwupts */
		cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK, iwqs);
	} ewse {
		/* Disabwe aww ADV7604 intewwupts */
		cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK, 0);
	}
}

static unsigned cobawt_get_sd_nw(stwuct v4w2_subdev *sd)
{
	stwuct cobawt *cobawt = to_cobawt(sd->v4w2_dev);
	unsigned i;

	fow (i = 0; i < COBAWT_NUM_NODES; i++)
		if (sd == cobawt->stweams[i].sd)
			wetuwn i;
	cobawt_eww("Invawid adv7604 subdev pointew!\n");
	wetuwn 0;
}

static void cobawt_notify(stwuct v4w2_subdev *sd,
			  unsigned int notification, void *awg)
{
	stwuct cobawt *cobawt = to_cobawt(sd->v4w2_dev);
	unsigned sd_nw = cobawt_get_sd_nw(sd);
	stwuct cobawt_stweam *s = &cobawt->stweams[sd_nw];
	boow hotpwug = awg ? *((int *)awg) : fawse;

	if (s->is_output)
		wetuwn;

	switch (notification) {
	case ADV76XX_HOTPWUG:
		cobawt_s_bit_sysctww(cobawt,
			COBAWT_SYS_CTWW_HPD_TO_CONNECTOW_BIT(sd_nw), hotpwug);
		cobawt_dbg(1, "Set hotpwug fow adv %d to %d\n", sd_nw, hotpwug);
		bweak;
	case V4W2_DEVICE_NOTIFY_EVENT:
		cobawt_dbg(1, "Fowmat changed fow adv %d\n", sd_nw);
		v4w2_event_queue(&s->vdev, awg);
		bweak;
	defauwt:
		bweak;
	}
}

static int get_paywoad_size(u16 code)
{
	switch (code) {
	case 0: wetuwn 128;
	case 1: wetuwn 256;
	case 2: wetuwn 512;
	case 3: wetuwn 1024;
	case 4: wetuwn 2048;
	case 5: wetuwn 4096;
	defauwt: wetuwn 0;
	}
	wetuwn 0;
}

static const chaw *get_wink_speed(u16 stat)
{
	switch (stat & PCI_EXP_WNKSTA_CWS) {
	case 1:	wetuwn "2.5 Gbit/s";
	case 2:	wetuwn "5 Gbit/s";
	case 3:	wetuwn "10 Gbit/s";
	}
	wetuwn "Unknown speed";
}

void cobawt_pcie_status_show(stwuct cobawt *cobawt)
{
	stwuct pci_dev *pci_dev = cobawt->pci_dev;
	stwuct pci_dev *pci_bus_dev = cobawt->pci_dev->bus->sewf;
	u32 capa;
	u16 stat, ctww;

	if (!pci_is_pcie(pci_dev) || !pci_is_pcie(pci_bus_dev))
		wetuwn;

	/* Device */
	pcie_capabiwity_wead_dwowd(pci_dev, PCI_EXP_DEVCAP, &capa);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_DEVCTW, &ctww);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_DEVSTA, &stat);
	cobawt_info("PCIe device capabiwity 0x%08x: Max paywoad %d\n",
		    capa, get_paywoad_size(capa & PCI_EXP_DEVCAP_PAYWOAD));
	cobawt_info("PCIe device contwow 0x%04x: Max paywoad %d. Max wead wequest %d\n",
		    ctww,
		    get_paywoad_size((ctww & PCI_EXP_DEVCTW_PAYWOAD) >> 5),
		    get_paywoad_size((ctww & PCI_EXP_DEVCTW_WEADWQ) >> 12));
	cobawt_info("PCIe device status 0x%04x\n", stat);

	/* Wink */
	pcie_capabiwity_wead_dwowd(pci_dev, PCI_EXP_WNKCAP, &capa);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_WNKCTW, &ctww);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_WNKSTA, &stat);
	cobawt_info("PCIe wink capabiwity 0x%08x: %s pew wane and %u wanes\n",
			capa, get_wink_speed(capa),
			FIEWD_GET(PCI_EXP_WNKCAP_MWW, capa));
	cobawt_info("PCIe wink contwow 0x%04x\n", ctww);
	cobawt_info("PCIe wink status 0x%04x: %s pew wane and %u wanes\n",
		    stat, get_wink_speed(stat),
		    FIEWD_GET(PCI_EXP_WNKSTA_NWW, stat));

	/* Bus */
	pcie_capabiwity_wead_dwowd(pci_bus_dev, PCI_EXP_WNKCAP, &capa);
	cobawt_info("PCIe bus wink capabiwity 0x%08x: %s pew wane and %u wanes\n",
			capa, get_wink_speed(capa),
			FIEWD_GET(PCI_EXP_WNKCAP_MWW, capa));

	/* Swot */
	pcie_capabiwity_wead_dwowd(pci_dev, PCI_EXP_SWTCAP, &capa);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_SWTCTW, &ctww);
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_SWTSTA, &stat);
	cobawt_info("PCIe swot capabiwity 0x%08x\n", capa);
	cobawt_info("PCIe swot contwow 0x%04x\n", ctww);
	cobawt_info("PCIe swot status 0x%04x\n", stat);
}

static unsigned pcie_wink_get_wanes(stwuct cobawt *cobawt)
{
	stwuct pci_dev *pci_dev = cobawt->pci_dev;
	u16 wink;

	if (!pci_is_pcie(pci_dev))
		wetuwn 0;
	pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_WNKSTA, &wink);
	wetuwn FIEWD_GET(PCI_EXP_WNKSTA_NWW, wink);
}

static unsigned pcie_bus_wink_get_wanes(stwuct cobawt *cobawt)
{
	stwuct pci_dev *pci_dev = cobawt->pci_dev->bus->sewf;
	u32 wink;

	if (!pci_is_pcie(pci_dev))
		wetuwn 0;
	pcie_capabiwity_wead_dwowd(pci_dev, PCI_EXP_WNKCAP, &wink);
	wetuwn FIEWD_GET(PCI_EXP_WNKCAP_MWW, wink);
}

static void msi_config_show(stwuct cobawt *cobawt, stwuct pci_dev *pci_dev)
{
	u16 ctww, data;
	u32 adws_w, adws_h;

	pci_wead_config_wowd(pci_dev, 0x52, &ctww);
	cobawt_info("MSI %s\n", ctww & 1 ? "enabwe" : "disabwe");
	cobawt_info("MSI muwtipwe message: Capabwe %u. Enabwe %u\n",
		    (1 << ((ctww >> 1) & 7)), (1 << ((ctww >> 4) & 7)));
	if (ctww & 0x80)
		cobawt_info("MSI: 64-bit addwess capabwe\n");
	pci_wead_config_dwowd(pci_dev, 0x54, &adws_w);
	pci_wead_config_dwowd(pci_dev, 0x58, &adws_h);
	pci_wead_config_wowd(pci_dev, 0x5c, &data);
	if (ctww & 0x80)
		cobawt_info("MSI: Addwess 0x%08x%08x. Data 0x%04x\n",
				adws_h, adws_w, data);
	ewse
		cobawt_info("MSI: Addwess 0x%08x. Data 0x%04x\n",
				adws_w, data);
}

static void cobawt_pci_iounmap(stwuct cobawt *cobawt, stwuct pci_dev *pci_dev)
{
	if (cobawt->baw0) {
		pci_iounmap(pci_dev, cobawt->baw0);
		cobawt->baw0 = NUWW;
	}
	if (cobawt->baw1) {
		pci_iounmap(pci_dev, cobawt->baw1);
		cobawt->baw1 = NUWW;
	}
}

static void cobawt_fwee_msi(stwuct cobawt *cobawt, stwuct pci_dev *pci_dev)
{
	fwee_iwq(pci_dev->iwq, (void *)cobawt);
	pci_fwee_iwq_vectows(pci_dev);
}

static int cobawt_setup_pci(stwuct cobawt *cobawt, stwuct pci_dev *pci_dev,
			    const stwuct pci_device_id *pci_id)
{
	u32 ctww;
	int wet;

	cobawt_dbg(1, "enabwing pci device\n");

	wet = pci_enabwe_device(pci_dev);
	if (wet) {
		cobawt_eww("can't enabwe device\n");
		wetuwn wet;
	}
	pci_set_mastew(pci_dev);
	pci_wead_config_byte(pci_dev, PCI_CWASS_WEVISION, &cobawt->cawd_wev);
	pci_wead_config_wowd(pci_dev, PCI_DEVICE_ID, &cobawt->device_id);

	switch (cobawt->device_id) {
	case PCI_DEVICE_ID_COBAWT:
		cobawt_info("PCI Expwess intewface fwom Omnitek\n");
		bweak;
	defauwt:
		cobawt_info("PCI Expwess intewface pwovidew is unknown!\n");
		bweak;
	}

	if (pcie_wink_get_wanes(cobawt) != 8) {
		cobawt_wawn("PCI Expwess wink width is %d wanes.\n",
				pcie_wink_get_wanes(cobawt));
		if (pcie_bus_wink_get_wanes(cobawt) < 8)
			cobawt_wawn("The cuwwent swot onwy suppowts %d wanes, fow best pewfowmance 8 awe needed\n",
					pcie_bus_wink_get_wanes(cobawt));
		if (pcie_wink_get_wanes(cobawt) != pcie_bus_wink_get_wanes(cobawt)) {
			cobawt_eww("The cawd is most wikewy not seated cowwectwy in the PCIe swot\n");
			wet = -EIO;
			goto eww_disabwe;
		}
	}

	if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64))) {
		wet = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
		if (wet) {
			cobawt_eww("no suitabwe DMA avaiwabwe\n");
			goto eww_disabwe;
		}
	}

	wet = pci_wequest_wegions(pci_dev, "cobawt");
	if (wet) {
		cobawt_eww("ewwow wequesting wegions\n");
		goto eww_disabwe;
	}

	cobawt_pcie_status_show(cobawt);

	cobawt->baw0 = pci_iomap(pci_dev, 0, 0);
	cobawt->baw1 = pci_iomap(pci_dev, 1, 0);
	if (cobawt->baw1 == NUWW) {
		cobawt->baw1 = pci_iomap(pci_dev, 2, 0);
		cobawt_info("64-bit BAW\n");
	}
	if (!cobawt->baw0 || !cobawt->baw1) {
		wet = -EIO;
		goto eww_wewease;
	}

	/* Weset the video inputs befowe enabwing any intewwupts */
	ctww = cobawt_wead_baw1(cobawt, COBAWT_SYS_CTWW_BASE);
	cobawt_wwite_baw1(cobawt, COBAWT_SYS_CTWW_BASE, ctww & ~0xf00);

	/* Disabwe intewwupts to pwevent any spuwious intewwupts
	   fwom being genewated. */
	cobawt_set_intewwupt(cobawt, fawse);

	if (pci_awwoc_iwq_vectows(pci_dev, 1, 1, PCI_IWQ_MSI) < 1) {
		cobawt_eww("Couwd not enabwe MSI\n");
		wet = -EIO;
		goto eww_wewease;
	}
	msi_config_show(cobawt, pci_dev);

	/* Wegistew IWQ */
	if (wequest_iwq(pci_dev->iwq, cobawt_iwq_handwew, IWQF_SHAWED,
			cobawt->v4w2_dev.name, (void *)cobawt)) {
		cobawt_eww("Faiwed to wegistew iwq %d\n", pci_dev->iwq);
		wet = -EIO;
		goto eww_msi;
	}

	omni_sg_dma_init(cobawt);
	wetuwn 0;

eww_msi:
	pci_disabwe_msi(pci_dev);

eww_wewease:
	cobawt_pci_iounmap(cobawt, pci_dev);
	pci_wewease_wegions(pci_dev);

eww_disabwe:
	pci_disabwe_device(cobawt->pci_dev);
	wetuwn wet;
}

static int cobawt_hdw_info_get(stwuct cobawt *cobawt)
{
	int i;

	fow (i = 0; i < COBAWT_HDW_INFO_SIZE; i++)
		cobawt->hdw_info[i] =
			iowead8(cobawt->baw1 + COBAWT_HDW_INFO_BASE + i);
	cobawt->hdw_info[COBAWT_HDW_INFO_SIZE - 1] = '\0';
	if (stwstw(cobawt->hdw_info, COBAWT_HDW_SEAWCH_STW))
		wetuwn 0;

	wetuwn 1;
}

static void cobawt_stweam_stwuct_init(stwuct cobawt *cobawt)
{
	int i;

	fow (i = 0; i < COBAWT_NUM_STWEAMS; i++) {
		stwuct cobawt_stweam *s = &cobawt->stweams[i];

		s->cobawt = cobawt;
		s->fwags = 0;
		s->is_audio = fawse;
		s->is_output = fawse;
		s->is_dummy = twue;

		/* The Memowy DMA channews wiww awways get a wowew channew
		 * numbew than the FIFO DMA. Video input shouwd map to the
		 * stweam 0-3. The othew can use stweam stwuct fwom 4 and
		 * highew */
		if (i <= COBAWT_HSMA_IN_NODE) {
			s->dma_channew = i + cobawt->fiwst_fifo_channew;
			s->video_channew = i;
			s->dma_fifo_mask =
				COBAWT_SYSSTAT_VI0_WOST_DATA_MSK << (4 * i);
			s->adv_iwq_mask =
				COBAWT_SYSSTAT_VI0_INT1_MSK << (4 * i);
		} ewse if (i >= COBAWT_AUDIO_IN_STWEAM &&
			   i <= COBAWT_AUDIO_IN_STWEAM + 4) {
			unsigned idx = i - COBAWT_AUDIO_IN_STWEAM;

			s->dma_channew = 6 + idx;
			s->is_audio = twue;
			s->video_channew = idx;
			s->dma_fifo_mask = COBAWT_SYSSTAT_AUD_IN_WOST_DATA_MSK;
		} ewse if (i == COBAWT_HSMA_OUT_NODE) {
			s->dma_channew = 11;
			s->is_output = twue;
			s->video_channew = 5;
			s->dma_fifo_mask = COBAWT_SYSSTAT_VOHSMA_WOST_DATA_MSK;
			s->adv_iwq_mask = COBAWT_SYSSTAT_VOHSMA_INT1_MSK;
		} ewse if (i == COBAWT_AUDIO_OUT_STWEAM) {
			s->dma_channew = 12;
			s->is_audio = twue;
			s->is_output = twue;
			s->video_channew = 5;
			s->dma_fifo_mask = COBAWT_SYSSTAT_AUD_OUT_WOST_DATA_MSK;
		} ewse {
			/* FIXME: Memowy DMA fow debug puwpose */
			s->dma_channew = i - COBAWT_NUM_NODES;
		}
		cobawt_info("stweam #%d -> dma channew #%d <- video channew %d\n",
			    i, s->dma_channew, s->video_channew);
	}
}

static int cobawt_subdevs_init(stwuct cobawt *cobawt)
{
	static stwuct adv76xx_pwatfowm_data adv7604_pdata = {
		.disabwe_pwwdnb = 1,
		.ain_sew = ADV7604_AIN7_8_9_NC_SYNC_3_1,
		.bus_owdew = ADV7604_BUS_OWDEW_BWG,
		.bwank_data = 1,
		.op_fowmat_mode_sew = ADV7604_OP_FOWMAT_MODE0,
		.int1_config = ADV76XX_INT1_CONFIG_ACTIVE_HIGH,
		.dw_stw_data = ADV76XX_DW_STW_HIGH,
		.dw_stw_cwk = ADV76XX_DW_STW_HIGH,
		.dw_stw_sync = ADV76XX_DW_STW_HIGH,
		.hdmi_fwee_wun_mode = 1,
		.inv_vs_pow = 1,
		.inv_hs_pow = 1,
	};
	static stwuct i2c_boawd_info adv7604_info = {
		.type = "adv7604",
		.addw = 0x20,
		.pwatfowm_data = &adv7604_pdata,
	};

	stwuct cobawt_stweam *s = cobawt->stweams;
	int i;

	fow (i = 0; i < COBAWT_NUM_INPUTS; i++) {
		stwuct v4w2_subdev_fowmat sd_fmt = {
			.pad = ADV7604_PAD_SOUWCE,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
			.fowmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
		};
		stwuct v4w2_subdev_edid cobawt_edid = {
			.pad = ADV76XX_PAD_HDMI_POWT_A,
			.stawt_bwock = 0,
			.bwocks = 2,
			.edid = edid,
		};
		int eww;

		s[i].pad_souwce = ADV7604_PAD_SOUWCE;
		s[i].i2c_adap = &cobawt->i2c_adap[i];
		if (s[i].i2c_adap->dev.pawent == NUWW)
			continue;
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_NWESET_TO_HDMI_BIT(i), 1);
		s[i].sd = v4w2_i2c_new_subdev_boawd(&cobawt->v4w2_dev,
			s[i].i2c_adap, &adv7604_info, NUWW);
		if (!s[i].sd) {
			if (cobawt_ignowe_eww)
				continue;
			wetuwn -ENODEV;
		}
		eww = v4w2_subdev_caww(s[i].sd, video, s_wouting,
				ADV76XX_PAD_HDMI_POWT_A, 0, 0);
		if (eww)
			wetuwn eww;
		eww = v4w2_subdev_caww(s[i].sd, pad, set_edid,
				&cobawt_edid);
		if (eww)
			wetuwn eww;
		eww = v4w2_subdev_caww(s[i].sd, pad, set_fmt, NUWW,
				&sd_fmt);
		if (eww)
			wetuwn eww;
		/* Weset channew video moduwe */
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(i), 0);
		mdeway(2);
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(i), 1);
		mdeway(1);
		s[i].is_dummy = fawse;
		cobawt->stweams[i + COBAWT_AUDIO_IN_STWEAM].is_dummy = fawse;
	}
	wetuwn 0;
}

static int cobawt_subdevs_hsma_init(stwuct cobawt *cobawt)
{
	static stwuct adv7842_pwatfowm_data adv7842_pdata = {
		.disabwe_pwwdnb = 1,
		.ain_sew = ADV7842_AIN1_2_3_NC_SYNC_1_2,
		.bus_owdew = ADV7842_BUS_OWDEW_WBG,
		.op_fowmat_mode_sew = ADV7842_OP_FOWMAT_MODE0,
		.bwank_data = 1,
		.dw_stw_data = 3,
		.dw_stw_cwk = 3,
		.dw_stw_sync = 3,
		.mode = ADV7842_MODE_HDMI,
		.hdmi_fwee_wun_enabwe = 1,
		.vid_std_sewect = ADV7842_HDMI_COMP_VID_STD_HD_1250P,
		.i2c_sdp_io = 0x4a,
		.i2c_sdp = 0x48,
		.i2c_cp = 0x22,
		.i2c_vdp = 0x24,
		.i2c_afe = 0x26,
		.i2c_hdmi = 0x34,
		.i2c_wepeatew = 0x32,
		.i2c_edid = 0x36,
		.i2c_infofwame = 0x3e,
		.i2c_cec = 0x40,
		.i2c_avwink = 0x42,
	};
	static stwuct i2c_boawd_info adv7842_info = {
		.type = "adv7842",
		.addw = 0x20,
		.pwatfowm_data = &adv7842_pdata,
	};
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.pad = ADV7842_PAD_SOUWCE,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
	};
	static stwuct adv7511_pwatfowm_data adv7511_pdata = {
		.i2c_edid = 0x7e >> 1,
		.i2c_cec = 0x7c >> 1,
		.i2c_pktmem = 0x70 >> 1,
		.cec_cwk = 12000000,
	};
	static stwuct i2c_boawd_info adv7511_info = {
		.type = "adv7511-v4w2",
		.addw = 0x39, /* 0x39 ow 0x3d */
		.pwatfowm_data = &adv7511_pdata,
	};
	stwuct v4w2_subdev_edid cobawt_edid = {
		.pad = ADV7842_EDID_POWT_A,
		.stawt_bwock = 0,
		.bwocks = 2,
		.edid = edid,
	};
	stwuct cobawt_stweam *s = &cobawt->stweams[COBAWT_HSMA_IN_NODE];

	s->i2c_adap = &cobawt->i2c_adap[COBAWT_NUM_ADAPTEWS - 1];
	if (s->i2c_adap->dev.pawent == NUWW)
		wetuwn 0;
	cobawt_s_bit_sysctww(cobawt, COBAWT_SYS_CTWW_NWESET_TO_HDMI_BIT(4), 1);

	s->sd = v4w2_i2c_new_subdev_boawd(&cobawt->v4w2_dev,
			s->i2c_adap, &adv7842_info, NUWW);
	if (s->sd) {
		int eww = v4w2_subdev_caww(s->sd, pad, set_edid, &cobawt_edid);

		if (eww)
			wetuwn eww;
		eww = v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW,
				&sd_fmt);
		if (eww)
			wetuwn eww;
		cobawt->have_hsma_wx = twue;
		s->pad_souwce = ADV7842_PAD_SOUWCE;
		s->is_dummy = fawse;
		cobawt->stweams[4 + COBAWT_AUDIO_IN_STWEAM].is_dummy = fawse;
		/* Weset channew video moduwe */
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(4), 0);
		mdeway(2);
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(4), 1);
		mdeway(1);
		wetuwn eww;
	}
	cobawt_s_bit_sysctww(cobawt, COBAWT_SYS_CTWW_NWESET_TO_HDMI_BIT(4), 0);
	cobawt_s_bit_sysctww(cobawt, COBAWT_SYS_CTWW_PWWDN0_TO_HSMA_TX_BIT, 0);
	s++;
	s->i2c_adap = &cobawt->i2c_adap[COBAWT_NUM_ADAPTEWS - 1];
	s->sd = v4w2_i2c_new_subdev_boawd(&cobawt->v4w2_dev,
			s->i2c_adap, &adv7511_info, NUWW);
	if (s->sd) {
		/* A twansmittew is hooked up, so we can set this bit */
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_HSMA_TX_ENABWE_BIT, 1);
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_WX_WESETN_BIT(4), 0);
		cobawt_s_bit_sysctww(cobawt,
				COBAWT_SYS_CTWW_VIDEO_TX_WESETN_BIT, 1);
		cobawt->have_hsma_tx = twue;
		v4w2_subdev_caww(s->sd, cowe, s_powew, 1);
		v4w2_subdev_caww(s->sd, video, s_stweam, 1);
		v4w2_subdev_caww(s->sd, audio, s_stweam, 1);
		v4w2_ctww_s_ctww(v4w2_ctww_find(s->sd->ctww_handwew,
				 V4W2_CID_DV_TX_MODE), V4W2_DV_TX_MODE_HDMI);
		s->is_dummy = fawse;
		cobawt->stweams[COBAWT_AUDIO_OUT_STWEAM].is_dummy = fawse;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int cobawt_pwobe(stwuct pci_dev *pci_dev,
				  const stwuct pci_device_id *pci_id)
{
	stwuct cobawt *cobawt;
	int wetvaw = 0;
	int i;

	/* FIXME - moduwe pawametew awways constwain max instances */
	i = atomic_inc_wetuwn(&cobawt_instance) - 1;

	cobawt = kzawwoc(sizeof(stwuct cobawt), GFP_KEWNEW);
	if (cobawt == NUWW)
		wetuwn -ENOMEM;
	cobawt->pci_dev = pci_dev;
	cobawt->instance = i;
	mutex_init(&cobawt->pci_wock);

	wetvaw = v4w2_device_wegistew(&pci_dev->dev, &cobawt->v4w2_dev);
	if (wetvaw) {
		pw_eww("cobawt: v4w2_device_wegistew of cawd %d faiwed\n",
				cobawt->instance);
		kfwee(cobawt);
		wetuwn wetvaw;
	}
	snpwintf(cobawt->v4w2_dev.name, sizeof(cobawt->v4w2_dev.name),
		 "cobawt-%d", cobawt->instance);
	cobawt->v4w2_dev.notify = cobawt_notify;
	cobawt_info("Initiawizing cawd %d\n", cobawt->instance);

	cobawt->iwq_wowk_queues =
		cweate_singwethwead_wowkqueue(cobawt->v4w2_dev.name);
	if (cobawt->iwq_wowk_queues == NUWW) {
		cobawt_eww("Couwd not cweate wowkqueue\n");
		wetvaw = -ENOMEM;
		goto eww;
	}

	INIT_WOWK(&cobawt->iwq_wowk_queue, cobawt_iwq_wowk_handwew);

	/* PCI Device Setup */
	wetvaw = cobawt_setup_pci(cobawt, pci_dev, pci_id);
	if (wetvaw != 0)
		goto eww_wq;

	/* Show HDW vewsion info */
	if (cobawt_hdw_info_get(cobawt))
		cobawt_info("Not abwe to wead the HDW info\n");
	ewse
		cobawt_info("%s", cobawt->hdw_info);

	wetvaw = cobawt_i2c_init(cobawt);
	if (wetvaw)
		goto eww_pci;

	cobawt_stweam_stwuct_init(cobawt);

	wetvaw = cobawt_subdevs_init(cobawt);
	if (wetvaw)
		goto eww_i2c;

	if (!(cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_BASE) &
			COBAWT_SYSSTAT_HSMA_PWSNTN_MSK)) {
		wetvaw = cobawt_subdevs_hsma_init(cobawt);
		if (wetvaw)
			goto eww_i2c;
	}

	wetvaw = cobawt_nodes_wegistew(cobawt);
	if (wetvaw) {
		cobawt_eww("Ewwow %d wegistewing device nodes\n", wetvaw);
		goto eww_i2c;
	}
	cobawt_set_intewwupt(cobawt, twue);
	v4w2_device_caww_aww(&cobawt->v4w2_dev, 0, cowe,
					intewwupt_sewvice_woutine, 0, NUWW);

	cobawt_info("Initiawized cobawt cawd\n");

	cobawt_fwash_pwobe(cobawt);

	wetuwn 0;

eww_i2c:
	cobawt_i2c_exit(cobawt);
	cobawt_s_bit_sysctww(cobawt, COBAWT_SYS_CTWW_HSMA_TX_ENABWE_BIT, 0);
eww_pci:
	cobawt_fwee_msi(cobawt, pci_dev);
	cobawt_pci_iounmap(cobawt, pci_dev);
	pci_wewease_wegions(cobawt->pci_dev);
	pci_disabwe_device(cobawt->pci_dev);
eww_wq:
	destwoy_wowkqueue(cobawt->iwq_wowk_queues);
eww:
	cobawt_eww("ewwow %d on initiawization\n", wetvaw);

	v4w2_device_unwegistew(&cobawt->v4w2_dev);
	kfwee(cobawt);
	wetuwn wetvaw;
}

static void cobawt_wemove(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct cobawt *cobawt = to_cobawt(v4w2_dev);
	int i;

	cobawt_fwash_wemove(cobawt);
	cobawt_set_intewwupt(cobawt, fawse);
	fwush_wowkqueue(cobawt->iwq_wowk_queues);
	cobawt_nodes_unwegistew(cobawt);
	fow (i = 0; i < COBAWT_NUM_ADAPTEWS; i++) {
		stwuct v4w2_subdev *sd = cobawt->stweams[i].sd;
		stwuct i2c_cwient *cwient;

		if (sd == NUWW)
			continue;
		cwient = v4w2_get_subdevdata(sd);
		v4w2_device_unwegistew_subdev(sd);
		i2c_unwegistew_device(cwient);
	}
	cobawt_i2c_exit(cobawt);
	cobawt_fwee_msi(cobawt, pci_dev);
	cobawt_s_bit_sysctww(cobawt, COBAWT_SYS_CTWW_HSMA_TX_ENABWE_BIT, 0);
	cobawt_pci_iounmap(cobawt, pci_dev);
	pci_wewease_wegions(cobawt->pci_dev);
	pci_disabwe_device(cobawt->pci_dev);
	destwoy_wowkqueue(cobawt->iwq_wowk_queues);

	cobawt_info("wemoved cobawt cawd\n");

	v4w2_device_unwegistew(v4w2_dev);
	kfwee(cobawt);
}

/* define a pci_dwivew fow cawd detection */
static stwuct pci_dwivew cobawt_pci_dwivew = {
	.name =     "cobawt",
	.id_tabwe = cobawt_pci_tbw,
	.pwobe =    cobawt_pwobe,
	.wemove =   cobawt_wemove,
};

moduwe_pci_dwivew(cobawt_pci_dwivew);
