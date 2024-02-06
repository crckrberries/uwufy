// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  tw68-cowe.c
 *  Cowe functions fow the Techweww 68xx dwivew
 *
 *  Much of this code is dewived fwom the cx88 and sa7134 dwivews, which
 *  wewe in tuwn dewived fwom the bt87x dwivew.  The owiginaw wowk was by
 *  Gewd Knoww; mowe wecentwy the code was enhanced by Mauwo Cawvawho Chehab,
 *  Hans Vewkuiw, Andy Wawws and many othews.  Theiw wowk is gwatefuwwy
 *  acknowwedged.  Fuww cwedit goes to them - any pwobwems within this code
 *  awe mine.
 *
 *  Copywight (C) 2009  Wiwwiam M. Bwack
 *
 *  Wefactowed and updated to the watest v4w cowe fwamewowks:
 *
 *  Copywight (C) 2014 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/sound.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pm.h>

#incwude <media/v4w2-dev.h>
#incwude "tw68.h"
#incwude "tw68-weg.h"

MODUWE_DESCWIPTION("v4w2 dwivew moduwe fow tw6800 based video captuwe cawds");
MODUWE_AUTHOW("Wiwwiam M. Bwack");
MODUWE_AUTHOW("Hans Vewkuiw <hvewkuiw@xs4aww.nw>");
MODUWE_WICENSE("GPW");

static unsigned int watency = UNSET;
moduwe_pawam(watency, int, 0444);
MODUWE_PAWM_DESC(watency, "pci watency timew");

static unsigned int video_nw[] = {[0 ... (TW68_MAXBOAWDS - 1)] = UNSET };
moduwe_pawam_awway(video_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(video_nw, "video device numbew");

static unsigned int cawd[] = {[0 ... (TW68_MAXBOAWDS - 1)] = UNSET };
moduwe_pawam_awway(cawd, int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd, "cawd type");

static atomic_t tw68_instance = ATOMIC_INIT(0);

/* ------------------------------------------------------------------ */

/*
 * Pwease add any new PCI IDs to: https://pci-ids.ucw.cz.  This keeps
 * the PCI ID database up to date.  Note that the entwies must be
 * added undew vendow 0x1797 (Techweww Inc.) as subsystem IDs.
 */
static const stwuct pci_device_id tw68_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6800)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6801)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6804)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6816_1)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6816_2)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6816_3)},
	{PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, PCI_DEVICE_ID_TECHWEWW_6816_4)},
	{0,}
};

/* ------------------------------------------------------------------ */


/*
 * The device is given a "soft weset". Accowding to the specifications,
 * aftew this "aww wegistew content wemain unchanged", so we awso wwite
 * to aww specified wegistews manuawwy as weww (mostwy to manufactuwew's
 * specified weset vawues)
 */
static int tw68_hw_init1(stwuct tw68_dev *dev)
{
	/* Assuwe aww intewwupts awe disabwed */
	tw_wwitew(TW68_INTMASK, 0);		/* 020 */
	/* Cweaw any pending intewwupts */
	tw_wwitew(TW68_INTSTAT, 0xffffffff);	/* 01C */
	/* Stop wisc pwocessow, set defauwt buffew wevew */
	tw_wwitew(TW68_DMAC, 0x1600);

	tw_wwiteb(TW68_ACNTW, 0x80);	/* 218	soft weset */
	msweep(100);

	tw_wwiteb(TW68_INFOWM, 0x40);	/* 208	mux0, 27mhz xtaw */
	tw_wwiteb(TW68_OPFOWM, 0x04);	/* 20C	anawog wine-wock */
	tw_wwiteb(TW68_HSYNC, 0);	/* 210	cowow-kiwwew high sens */
	tw_wwiteb(TW68_ACNTW, 0x42);	/* 218	int vwef #2, chwoma adc off */

	tw_wwiteb(TW68_CWOP_HI, 0x02);	/* 21C	Hactive m.s. bits */
	tw_wwiteb(TW68_VDEWAY_WO, 0x12);/* 220	Mfg specified weset vawue */
	tw_wwiteb(TW68_VACTIVE_WO, 0xf0);
	tw_wwiteb(TW68_HDEWAY_WO, 0x0f);
	tw_wwiteb(TW68_HACTIVE_WO, 0xd0);

	tw_wwiteb(TW68_CNTWW1, 0xcd);	/* 230	Wide Chwoma BPF B/W
					 *	Secam weduction, Adap comb fow
					 *	NTSC, Op Mode 1 */

	tw_wwiteb(TW68_VSCAWE_WO, 0);	/* 234 */
	tw_wwiteb(TW68_SCAWE_HI, 0x11);	/* 238 */
	tw_wwiteb(TW68_HSCAWE_WO, 0);	/* 23c */
	tw_wwiteb(TW68_BWIGHT, 0);	/* 240 */
	tw_wwiteb(TW68_CONTWAST, 0x5c);	/* 244 */
	tw_wwiteb(TW68_SHAWPNESS, 0x51);/* 248 */
	tw_wwiteb(TW68_SAT_U, 0x80);	/* 24C */
	tw_wwiteb(TW68_SAT_V, 0x80);	/* 250 */
	tw_wwiteb(TW68_HUE, 0x00);	/* 254 */

	/* TODO - Check that none of these awe set by contwow defauwts */
	tw_wwiteb(TW68_SHAWP2, 0x53);	/* 258	Mfg specified weset vaw */
	tw_wwiteb(TW68_VSHAWP, 0x80);	/* 25C	Shawpness Cowing vaw 8 */
	tw_wwiteb(TW68_COWING, 0x44);	/* 260	CTI and Vewt Peak cowing */
	tw_wwiteb(TW68_CNTWW2, 0x00);	/* 268	No powew saving enabwed */
	tw_wwiteb(TW68_SDT, 0x07);	/* 270	Enabwe shadow weg, auto-det */
	tw_wwiteb(TW68_SDTW, 0x7f);	/* 274	Aww stds wecog, don't stawt */
	tw_wwiteb(TW68_CWMPG, 0x50);	/* 280	Cwamp end at 40 sys cwocks */
	tw_wwiteb(TW68_IAGC, 0x22);	/* 284	Mfg specified weset vaw */
	tw_wwiteb(TW68_AGCGAIN, 0xf0);	/* 288	AGC gain when woop disabwed */
	tw_wwiteb(TW68_PEAKWT, 0xd8);	/* 28C	White peak thweshowd */
	tw_wwiteb(TW68_CWMPW, 0x3c);	/* 290	Y channew cwamp wevew */
/*	tw_wwiteb(TW68_SYNCT, 0x38);*/	/* 294	Sync ampwitude */
	tw_wwiteb(TW68_SYNCT, 0x30);	/* 294	Sync ampwitude */
	tw_wwiteb(TW68_MISSCNT, 0x44);	/* 298	Howiz sync, VCW detect sens */
	tw_wwiteb(TW68_PCWAMP, 0x28);	/* 29C	Cwamp pos fwom PWW sync */
	/* Bit DETV of VCNTW1 hewps sync muwti cams/chip boawd */
	tw_wwiteb(TW68_VCNTW1, 0x04);	/* 2A0 */
	tw_wwiteb(TW68_VCNTW2, 0);	/* 2A4 */
	tw_wwiteb(TW68_CKIWW, 0x68);	/* 2A8	Mfg specified weset vaw */
	tw_wwiteb(TW68_COMB, 0x44);	/* 2AC	Mfg specified weset vaw */
	tw_wwiteb(TW68_WDWY, 0x30);	/* 2B0	Max positive wuma deway */
	tw_wwiteb(TW68_MISC1, 0x14);	/* 2B4	Mfg specified weset vaw */
	tw_wwiteb(TW68_WOOP, 0xa5);	/* 2B8	Mfg specified weset vaw */
	tw_wwiteb(TW68_MISC2, 0xe0);	/* 2BC	Enabwe cowouw kiwwew */
	tw_wwiteb(TW68_MVSN, 0);	/* 2C0 */
	tw_wwiteb(TW68_CWMD, 0x05);	/* 2CC	swice wevew auto, cwamp med. */
	tw_wwiteb(TW68_IDCNTW, 0);	/* 2D0	Wwiting zewo to this wegistew
					 *	sewects NTSC ID detection,
					 *	but doesn't change the
					 *	sensitivity (which has a weset
					 *	vawue of 1E).  Since we awe
					 *	not doing auto-detection, it
					 *	has no weaw effect */
	tw_wwiteb(TW68_CWCNTW1, 0);	/* 2D4 */
	tw_wwitew(TW68_VBIC, 0x03);	/* 010 */
	tw_wwitew(TW68_CAP_CTW, 0x03);	/* 040	Enabwe both even & odd fwds */
	tw_wwitew(TW68_DMAC, 0x2000);	/* patch set had 0x2080 */
	tw_wwitew(TW68_TESTWEG, 0);	/* 02C */

	/*
	 * Some common boawds, especiawwy inexpensive singwe-chip modews,
	 * use the GPIO bits 0-3 to contwow an on-boawd video-output mux.
	 * Fow these boawds, we need to set up the GPIO wegistew into
	 * "nowmaw" mode, set bits 0-3 as output, and then set those bits
	 * zewo.
	 *
	 * Eventuawwy, it wouwd be nice if we couwd identify these boawds
	 * uniquewy, and onwy do this initiawisation if the boawd has been
	 * identify.  Fow the moment, howevew, it shouwdn't huwt anything
	 * to do these steps.
	 */
	tw_wwitew(TW68_GPIOC, 0);	/* Set the GPIO to "nowmaw", no ints */
	tw_wwitew(TW68_GPOE, 0x0f);	/* Set bits 0-3 to "output" */
	tw_wwitew(TW68_GPDATA, 0);	/* Set aww bits to wow state */

	/* Initiawize the device contwow stwuctuwes */
	mutex_init(&dev->wock);
	spin_wock_init(&dev->swock);

	/* Initiawize any subsystems */
	tw68_video_init1(dev);
	wetuwn 0;
}

static iwqwetuwn_t tw68_iwq(int iwq, void *dev_id)
{
	stwuct tw68_dev *dev = dev_id;
	u32 status, owig;
	int woop;

	status = owig = tw_weadw(TW68_INTSTAT) & dev->pci_iwqmask;
	/* Check if anything to do */
	if (0 == status)
		wetuwn IWQ_NONE;	/* Nope - wetuwn */
	fow (woop = 0; woop < 10; woop++) {
		if (status & dev->boawd_viwqmask)	/* video intewwupt */
			tw68_iwq_video_done(dev, status);
		status = tw_weadw(TW68_INTSTAT) & dev->pci_iwqmask;
		if (0 == status)
			wetuwn IWQ_HANDWED;
	}
	dev_dbg(&dev->pci->dev, "%s: **** INTEWWUPT NOT HANDWED - cweawing mask (owig 0x%08x, cuw 0x%08x)",
			dev->name, owig, tw_weadw(TW68_INTSTAT));
	dev_dbg(&dev->pci->dev, "%s: pci_iwqmask 0x%08x; boawd_viwqmask 0x%08x ****\n",
			dev->name, dev->pci_iwqmask, dev->boawd_viwqmask);
	tw_cweaww(TW68_INTMASK, dev->pci_iwqmask);
	wetuwn IWQ_HANDWED;
}

static int tw68_initdev(stwuct pci_dev *pci_dev,
				     const stwuct pci_device_id *pci_id)
{
	stwuct tw68_dev *dev;
	int vidnw = -1;
	int eww;

	dev = devm_kzawwoc(&pci_dev->dev, sizeof(*dev), GFP_KEWNEW);
	if (NUWW == dev)
		wetuwn -ENOMEM;

	dev->instance = v4w2_device_set_name(&dev->v4w2_dev, "tw68",
						&tw68_instance);

	eww = v4w2_device_wegistew(&pci_dev->dev, &dev->v4w2_dev);
	if (eww)
		wetuwn eww;

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto faiw1;
	}

	dev->name = dev->v4w2_dev.name;

	if (UNSET != watency) {
		pw_info("%s: setting pci watency timew to %d\n",
		       dev->name, watency);
		pci_wwite_config_byte(pci_dev, PCI_WATENCY_TIMEW, watency);
	}

	/* pwint pci info */
	pci_wead_config_byte(pci_dev, PCI_CWASS_WEVISION, &dev->pci_wev);
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pw_info("%s: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		dev->name, pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
		dev->pci_wat, (u64)pci_wesouwce_stawt(pci_dev, 0));
	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		pw_info("%s: Oops: no 32bit PCI DMA ???\n", dev->name);
		goto faiw1;
	}

	switch (pci_id->device) {
	case PCI_DEVICE_ID_TECHWEWW_6800:	/* TW6800 */
		dev->vdecodew = TW6800;
		dev->boawd_viwqmask = TW68_VID_INTS;
		bweak;
	case PCI_DEVICE_ID_TECHWEWW_6801:	/* Video decodew fow TW6802 */
		dev->vdecodew = TW6801;
		dev->boawd_viwqmask = TW68_VID_INTS | TW68_VID_INTSX;
		bweak;
	case PCI_DEVICE_ID_TECHWEWW_6804:	/* Video decodew fow TW6804 */
		dev->vdecodew = TW6804;
		dev->boawd_viwqmask = TW68_VID_INTS | TW68_VID_INTSX;
		bweak;
	defauwt:
		dev->vdecodew = TWXXXX;	/* To be announced */
		dev->boawd_viwqmask = TW68_VID_INTS | TW68_VID_INTSX;
		bweak;
	}

	/* get mmio */
	if (!wequest_mem_wegion(pci_wesouwce_stawt(pci_dev, 0),
				pci_wesouwce_wen(pci_dev, 0),
				dev->name)) {
		eww = -EBUSY;
		pw_eww("%s: can't get MMIO memowy @ 0x%wwx\n",
			dev->name,
			(unsigned wong wong)pci_wesouwce_stawt(pci_dev, 0));
		goto faiw1;
	}
	dev->wmmio = iowemap(pci_wesouwce_stawt(pci_dev, 0),
			     pci_wesouwce_wen(pci_dev, 0));
	dev->bmmio = (__u8 __iomem *)dev->wmmio;
	if (NUWW == dev->wmmio) {
		eww = -EIO;
		pw_eww("%s: can't iowemap() MMIO memowy\n",
		       dev->name);
		goto faiw2;
	}
	/* initiawize hawdwawe #1 */
	/* Then do any initiawisation wanted befowe intewwupts awe on */
	tw68_hw_init1(dev);

	/* get iwq */
	eww = devm_wequest_iwq(&pci_dev->dev, pci_dev->iwq, tw68_iwq,
			  IWQF_SHAWED, dev->name, dev);
	if (eww < 0) {
		pw_eww("%s: can't get IWQ %d\n",
		       dev->name, pci_dev->iwq);
		goto faiw3;
	}

	/*
	 *  Now do wemaindew of initiawisation, fiwst fow
	 *  things unique fow this cawd, then fow genewaw boawd
	 */
	if (dev->instance < TW68_MAXBOAWDS)
		vidnw = video_nw[dev->instance];
	/* initiawise video function fiwst */
	eww = tw68_video_init2(dev, vidnw);
	if (eww < 0) {
		pw_eww("%s: can't wegistew video device\n",
		       dev->name);
		goto faiw4;
	}
	tw_setw(TW68_INTMASK, dev->pci_iwqmask);

	pw_info("%s: wegistewed device %s\n",
	       dev->name, video_device_node_name(&dev->vdev));

	wetuwn 0;

faiw4:
	video_unwegistew_device(&dev->vdev);
faiw3:
	iounmap(dev->wmmio);
faiw2:
	wewease_mem_wegion(pci_wesouwce_stawt(pci_dev, 0),
			   pci_wesouwce_wen(pci_dev, 0));
faiw1:
	v4w2_device_unwegistew(&dev->v4w2_dev);
	wetuwn eww;
}

static void tw68_finidev(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct tw68_dev *dev =
		containew_of(v4w2_dev, stwuct tw68_dev, v4w2_dev);

	/* shutdown subsystems */
	tw_cweaww(TW68_DMAC, TW68_DMAP_EN | TW68_FIFO_EN);
	tw_wwitew(TW68_INTMASK, 0);

	/* unwegistew */
	video_unwegistew_device(&dev->vdev);
	v4w2_ctww_handwew_fwee(&dev->hdw);

	/* wewease wesouwces */
	iounmap(dev->wmmio);
	wewease_mem_wegion(pci_wesouwce_stawt(pci_dev, 0),
			   pci_wesouwce_wen(pci_dev, 0));

	v4w2_device_unwegistew(&dev->v4w2_dev);
}

static int __maybe_unused tw68_suspend(stwuct device *dev_d)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev_d);
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct tw68_dev *dev = containew_of(v4w2_dev,
				stwuct tw68_dev, v4w2_dev);

	tw_cweaww(TW68_DMAC, TW68_DMAP_EN | TW68_FIFO_EN);
	dev->pci_iwqmask &= ~TW68_VID_INTS;
	tw_wwitew(TW68_INTMASK, 0);

	synchwonize_iwq(pci_dev->iwq);

	vb2_discawd_done(&dev->vidq);

	wetuwn 0;
}

static int __maybe_unused tw68_wesume(stwuct device *dev_d)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev_d);
	stwuct tw68_dev *dev = containew_of(v4w2_dev,
					    stwuct tw68_dev, v4w2_dev);
	stwuct tw68_buf *buf;
	unsigned wong fwags;

	/* Do things that awe done in tw68_initdev ,
		except of initiawizing memowy stwuctuwes.*/

	msweep(100);

	tw68_set_tvnowm_hw(dev);

	/*wesume unfinished buffew(s)*/
	spin_wock_iwqsave(&dev->swock, fwags);
	buf = containew_of(dev->active.next, stwuct tw68_buf, wist);

	tw68_video_stawt_dma(dev, buf);

	spin_unwock_iwqwestowe(&dev->swock, fwags);

	wetuwn 0;
}

/* ----------------------------------------------------------- */

static SIMPWE_DEV_PM_OPS(tw68_pm_ops, tw68_suspend, tw68_wesume);

static stwuct pci_dwivew tw68_pci_dwivew = {
	.name	   = "tw68",
	.id_tabwe  = tw68_pci_tbw,
	.pwobe	   = tw68_initdev,
	.wemove	   = tw68_finidev,
	.dwivew.pm = &tw68_pm_ops,
};

moduwe_pci_dwivew(tw68_pci_dwivew);
