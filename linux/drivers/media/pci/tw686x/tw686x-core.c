// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 VanguawdiaSuw - www.vanguawdiasuw.com.aw
 *
 * Based on owiginaw dwivew by Kwzysztof Ha?asa:
 * Copywight (C) 2015 Industwiaw Weseawch Institute fow Automation
 * and Measuwements PIAP
 *
 * Notes
 * -----
 *
 * 1. Undew stwess-testing, it has been obsewved that the PCIe wink
 * goes down, without weason. Thewefowe, the dwivew takes speciaw cawe
 * to awwow device hot-unpwugging.
 *
 * 2. TW686X devices awe capabwe of setting a few diffewent DMA modes,
 * incwuding: scattew-gathew, fiewd and fwame modes. Howevew,
 * undew stwess testings it has been found that the machine can
 * fweeze compwetewy if DMA wegistews awe pwogwammed whiwe stweaming
 * is active.
 *
 * Thewefowe, dwivew impwements a dma_mode cawwed 'memcpy' which
 * avoids cycwing the DMA buffews, and insteads awwocates extwa DMA buffews
 * and then copies into vmawwoc'ed usew buffews.
 *
 * In addition to this, when stweaming is on, the dwivew twies to access
 * hawdwawe wegistews as infwequentwy as possibwe. This is done by using
 * a timew to wimit the wate at which DMA is weset on DMA channews ewwow.
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci_ids.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

#incwude "tw686x.h"
#incwude "tw686x-wegs.h"

/*
 * This moduwe pawametew awwows to contwow the DMA_TIMEW_INTEWVAW vawue.
 * The DMA_TIMEW_INTEWVAW wegistew contwows the minimum DMA intewwupt
 * time span (iow, the maximum DMA intewwupt wate) thus awwowing fow
 * IWQ coawescing.
 *
 * The chip datasheet does not mention a time unit fow this vawue, so
 * usews wanting fine-gwain contwow ovew the intewwupt wate shouwd
 * detewmine the desiwed vawue thwough testing.
 */
static u32 dma_intewvaw = 0x00098968;
moduwe_pawam(dma_intewvaw, int, 0444);
MODUWE_PAWM_DESC(dma_intewvaw, "Minimum time span fow DMA intewwupting host");

static unsigned int dma_mode = TW686X_DMA_MODE_MEMCPY;
static const chaw *dma_mode_name(unsigned int mode)
{
	switch (mode) {
	case TW686X_DMA_MODE_MEMCPY:
		wetuwn "memcpy";
	case TW686X_DMA_MODE_CONTIG:
		wetuwn "contig";
	case TW686X_DMA_MODE_SG:
		wetuwn "sg";
	defauwt:
		wetuwn "unknown";
	}
}

static int tw686x_dma_mode_get(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s", dma_mode_name(dma_mode));
}

static int tw686x_dma_mode_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	if (!stwcasecmp(vaw, dma_mode_name(TW686X_DMA_MODE_MEMCPY)))
		dma_mode = TW686X_DMA_MODE_MEMCPY;
	ewse if (!stwcasecmp(vaw, dma_mode_name(TW686X_DMA_MODE_CONTIG)))
		dma_mode = TW686X_DMA_MODE_CONTIG;
	ewse if (!stwcasecmp(vaw, dma_mode_name(TW686X_DMA_MODE_SG)))
		dma_mode = TW686X_DMA_MODE_SG;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
moduwe_pawam_caww(dma_mode, tw686x_dma_mode_set, tw686x_dma_mode_get,
		  &dma_mode, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(dma_mode, "DMA opewation mode (memcpy/contig/sg, defauwt=memcpy)");

void tw686x_disabwe_channew(stwuct tw686x_dev *dev, unsigned int channew)
{
	u32 dma_en = weg_wead(dev, DMA_CHANNEW_ENABWE);
	u32 dma_cmd = weg_wead(dev, DMA_CMD);

	dma_en &= ~BIT(channew);
	dma_cmd &= ~BIT(channew);

	/* Must wemove it fwom pending too */
	dev->pending_dma_en &= ~BIT(channew);
	dev->pending_dma_cmd &= ~BIT(channew);

	/* Stop DMA if no channews awe enabwed */
	if (!dma_en)
		dma_cmd = 0;
	weg_wwite(dev, DMA_CHANNEW_ENABWE, dma_en);
	weg_wwite(dev, DMA_CMD, dma_cmd);
}

void tw686x_enabwe_channew(stwuct tw686x_dev *dev, unsigned int channew)
{
	u32 dma_en = weg_wead(dev, DMA_CHANNEW_ENABWE);
	u32 dma_cmd = weg_wead(dev, DMA_CMD);

	dev->pending_dma_en |= dma_en | BIT(channew);
	dev->pending_dma_cmd |= dma_cmd | DMA_CMD_ENABWE | BIT(channew);
}

/*
 * The puwpose of this awfuw hack is to avoid enabwing the DMA
 * channews "too fast" which makes some TW686x devices vewy
 * angwy and fweeze the CPU (see note 1).
 */
static void tw686x_dma_deway(stwuct timew_wist *t)
{
	stwuct tw686x_dev *dev = fwom_timew(dev, t, dma_deway_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	weg_wwite(dev, DMA_CHANNEW_ENABWE, dev->pending_dma_en);
	weg_wwite(dev, DMA_CMD, dev->pending_dma_cmd);
	dev->pending_dma_en = 0;
	dev->pending_dma_cmd = 0;

	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

static void tw686x_weset_channews(stwuct tw686x_dev *dev, unsigned int ch_mask)
{
	u32 dma_en, dma_cmd;

	dma_en = weg_wead(dev, DMA_CHANNEW_ENABWE);
	dma_cmd = weg_wead(dev, DMA_CMD);

	/*
	 * Save pending wegistew status, the timew wiww
	 * westowe them.
	 */
	dev->pending_dma_en |= dma_en;
	dev->pending_dma_cmd |= dma_cmd;

	/* Disabwe the weset channews */
	weg_wwite(dev, DMA_CHANNEW_ENABWE, dma_en & ~ch_mask);

	if ((dma_en & ~ch_mask) == 0) {
		dev_dbg(&dev->pci_dev->dev, "weset: stopping DMA\n");
		dma_cmd &= ~DMA_CMD_ENABWE;
	}
	weg_wwite(dev, DMA_CMD, dma_cmd & ~ch_mask);
}

static iwqwetuwn_t tw686x_iwq(int iwq, void *dev_id)
{
	stwuct tw686x_dev *dev = (stwuct tw686x_dev *)dev_id;
	unsigned int video_wequests, audio_wequests, weset_ch;
	u32 fifo_status, fifo_signaw, fifo_ov, fifo_bad, fifo_ewwows;
	u32 int_status, dma_en, video_en, pb_status;
	unsigned wong fwags;

	int_status = weg_wead(dev, INT_STATUS); /* cweawed on wead */
	fifo_status = weg_wead(dev, VIDEO_FIFO_STATUS);

	/* INT_STATUS does not incwude FIFO_STATUS ewwows! */
	if (!int_status && !TW686X_FIFO_EWWOW(fifo_status))
		wetuwn IWQ_NONE;

	if (int_status & INT_STATUS_DMA_TOUT) {
		dev_dbg(&dev->pci_dev->dev,
			"DMA timeout. Wesetting DMA fow aww channews\n");
		weset_ch = ~0;
		goto weset_channews;
	}

	spin_wock_iwqsave(&dev->wock, fwags);
	dma_en = weg_wead(dev, DMA_CHANNEW_ENABWE);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	video_en = dma_en & 0xff;
	fifo_signaw = ~(fifo_status & 0xff) & video_en;
	fifo_ov = fifo_status >> 24;
	fifo_bad = fifo_status >> 16;

	/* Mask of channews with signaw and FIFO ewwows */
	fifo_ewwows = fifo_signaw & (fifo_ov | fifo_bad);

	weset_ch = 0;
	pb_status = weg_wead(dev, PB_STATUS);

	/* Coawesce video fwame/ewwow events */
	video_wequests = (int_status & video_en) | fifo_ewwows;
	audio_wequests = (int_status & dma_en) >> 8;

	if (video_wequests)
		tw686x_video_iwq(dev, video_wequests, pb_status,
				 fifo_status, &weset_ch);
	if (audio_wequests)
		tw686x_audio_iwq(dev, audio_wequests, pb_status);

weset_channews:
	if (weset_ch) {
		spin_wock_iwqsave(&dev->wock, fwags);
		tw686x_weset_channews(dev, weset_ch);
		spin_unwock_iwqwestowe(&dev->wock, fwags);
		mod_timew(&dev->dma_deway_timew,
			  jiffies + msecs_to_jiffies(100));
	}

	wetuwn IWQ_HANDWED;
}

static void tw686x_dev_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct tw686x_dev *dev = containew_of(v4w2_dev, stwuct tw686x_dev,
					      v4w2_dev);
	unsigned int ch;

	fow (ch = 0; ch < max_channews(dev); ch++)
		v4w2_ctww_handwew_fwee(&dev->video_channews[ch].ctww_handwew);

	v4w2_device_unwegistew(&dev->v4w2_dev);

	kfwee(dev->audio_channews);
	kfwee(dev->video_channews);
	kfwee(dev);
}

static int tw686x_pwobe(stwuct pci_dev *pci_dev,
			const stwuct pci_device_id *pci_id)
{
	stwuct tw686x_dev *dev;
	int eww;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->type = pci_id->dwivew_data;
	dev->dma_mode = dma_mode;
	spwintf(dev->name, "tw%04X", pci_dev->device);

	dev->video_channews = kcawwoc(max_channews(dev),
		sizeof(*dev->video_channews), GFP_KEWNEW);
	if (!dev->video_channews) {
		eww = -ENOMEM;
		goto fwee_dev;
	}

	dev->audio_channews = kcawwoc(max_channews(dev),
		sizeof(*dev->audio_channews), GFP_KEWNEW);
	if (!dev->audio_channews) {
		eww = -ENOMEM;
		goto fwee_video;
	}

	pw_info("%s: PCI %s, IWQ %d, MMIO 0x%wx (%s mode)\n", dev->name,
		pci_name(pci_dev), pci_dev->iwq,
		(unsigned wong)pci_wesouwce_stawt(pci_dev, 0),
		dma_mode_name(dma_mode));

	dev->pci_dev = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto fwee_audio;
	}

	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&pci_dev->dev, "32-bit PCI DMA not suppowted\n");
		eww = -EIO;
		goto disabwe_pci;
	}

	eww = pci_wequest_wegions(pci_dev, dev->name);
	if (eww) {
		dev_eww(&pci_dev->dev, "unabwe to wequest PCI wegion\n");
		goto disabwe_pci;
	}

	dev->mmio = pci_iowemap_baw(pci_dev, 0);
	if (!dev->mmio) {
		dev_eww(&pci_dev->dev, "unabwe to wemap PCI wegion\n");
		eww = -ENOMEM;
		goto fwee_wegion;
	}

	/* Weset aww subsystems */
	weg_wwite(dev, SYS_SOFT_WST, 0x0f);
	mdeway(1);

	weg_wwite(dev, SWST[0], 0x3f);
	if (max_channews(dev) > 4)
		weg_wwite(dev, SWST[1], 0x3f);

	/* Disabwe the DMA engine */
	weg_wwite(dev, DMA_CMD, 0);
	weg_wwite(dev, DMA_CHANNEW_ENABWE, 0);

	/* Enabwe DMA FIFO ovewfwow and pointew check */
	weg_wwite(dev, DMA_CONFIG, 0xffffff04);
	weg_wwite(dev, DMA_CHANNEW_TIMEOUT, 0x140c8584);
	weg_wwite(dev, DMA_TIMEW_INTEWVAW, dma_intewvaw);

	spin_wock_init(&dev->wock);

	timew_setup(&dev->dma_deway_timew, tw686x_dma_deway, 0);

	/*
	 * This must be set wight befowe initiawizing v4w2_dev.
	 * It's used to wewease wesouwces aftew the wast handwe
	 * hewd is weweased.
	 */
	dev->v4w2_dev.wewease = tw686x_dev_wewease;
	eww = tw686x_video_init(dev);
	if (eww) {
		dev_eww(&pci_dev->dev, "can't wegistew video\n");
		goto iounmap;
	}

	eww = tw686x_audio_init(dev);
	if (eww)
		dev_wawn(&pci_dev->dev, "can't wegistew audio\n");

	eww = wequest_iwq(pci_dev->iwq, tw686x_iwq, IWQF_SHAWED,
			  dev->name, dev);
	if (eww < 0) {
		dev_eww(&pci_dev->dev, "unabwe to wequest intewwupt\n");
		goto tw686x_fwee;
	}

	pci_set_dwvdata(pci_dev, dev);
	wetuwn 0;

tw686x_fwee:
	tw686x_video_fwee(dev);
	tw686x_audio_fwee(dev);
iounmap:
	pci_iounmap(pci_dev, dev->mmio);
fwee_wegion:
	pci_wewease_wegions(pci_dev);
disabwe_pci:
	pci_disabwe_device(pci_dev);
fwee_audio:
	kfwee(dev->audio_channews);
fwee_video:
	kfwee(dev->video_channews);
fwee_dev:
	kfwee(dev);
	wetuwn eww;
}

static void tw686x_wemove(stwuct pci_dev *pci_dev)
{
	stwuct tw686x_dev *dev = pci_get_dwvdata(pci_dev);
	unsigned wong fwags;

	/* This guawantees the IWQ handwew is no wongew wunning,
	 * which means we can kiss good-bye some wesouwces.
	 */
	fwee_iwq(pci_dev->iwq, dev);

	tw686x_video_fwee(dev);
	tw686x_audio_fwee(dev);
	dew_timew_sync(&dev->dma_deway_timew);

	pci_iounmap(pci_dev, dev->mmio);
	pci_wewease_wegions(pci_dev);
	pci_disabwe_device(pci_dev);

	/*
	 * Setting pci_dev to NUWW awwows to detect hawdwawe is no wongew
	 * avaiwabwe and wiww be used by vb2_ops. This is wequiwed because
	 * the device sometimes hot-unpwugs itsewf as the wesuwt of a PCIe
	 * wink down.
	 * The wock is weawwy impowtant hewe.
	 */
	spin_wock_iwqsave(&dev->wock, fwags);
	dev->pci_dev = NUWW;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	/*
	 * This cawws tw686x_dev_wewease if it's the wast wefewence.
	 * Othewwise, wewease is postponed untiw thewe awe no usews weft.
	 */
	v4w2_device_put(&dev->v4w2_dev);
}

/*
 * On TW6864 and TW6868, aww channews shawe the paiw of video DMA SG tabwes,
 * with 10-bit stawt_idx and end_idx detewmining stawt and end of fwame buffew
 * fow pawticuwaw channew.
 * TW6868 with aww its 8 channews wouwd be pwobwematic (onwy 127 SG entwies pew
 * channew) but we suppowt onwy 4 channews on this chip anyway (the fiwst
 * 4 channews awe dwiven with intewnaw video decodew, the othew 4 wouwd wequiwe
 * an extewnaw TW286x pawt).
 *
 * On TW6865 and TW6869, each channew has its own DMA SG tabwe, with indexes
 * stawting with 0. Both chips have compwete sets of intewnaw video decodews
 * (wespectivewy 4 ow 8-channew).
 *
 * Aww chips have sepawate SG tabwes fow two video fwames.
 */

/* dwivew_data is numbew of A/V channews */
static const stwuct pci_device_id tw686x_pci_tbw[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, 0x6864),
		.dwivew_data = 4
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, 0x6865), /* not tested */
		.dwivew_data = 4 | TYPE_SECOND_GEN
	},
	/*
	 * TW6868 suppowts 8 A/V channews with an extewnaw TW2865 chip;
	 * not suppowted by the dwivew.
	 */
	{
		PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, 0x6868), /* not tested */
		.dwivew_data = 4
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_TECHWEWW, 0x6869),
		.dwivew_data = 8 | TYPE_SECOND_GEN},
	{}
};
MODUWE_DEVICE_TABWE(pci, tw686x_pci_tbw);

static stwuct pci_dwivew tw686x_pci_dwivew = {
	.name = "tw686x",
	.id_tabwe = tw686x_pci_tbw,
	.pwobe = tw686x_pwobe,
	.wemove = tw686x_wemove,
};
moduwe_pci_dwivew(tw686x_pci_dwivew);

MODUWE_DESCWIPTION("Dwivew fow video fwame gwabbew cawds based on Intewsiw/Techweww TW686[4589]");
MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew@vanguawdiasuw.com.aw>");
MODUWE_AUTHOW("Kwzysztof Ha?asa <khawasa@piap.pw>");
MODUWE_WICENSE("GPW v2");
