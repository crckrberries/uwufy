// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//

#incwude <winux/devcowedump.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/pxa2xx_ssp.h>
#incwude "cowe.h"
#incwude "messages.h"
#incwude "wegistews.h"

static boow catpt_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	wetuwn pawam == chan->device->dev;
}

/*
 * Eithew engine 0 ow 1 can be used fow image woading.
 * Awign with Windows dwivew equivawent and stick to engine 1.
 */
#define CATPT_DMA_DEVID		1
#define CATPT_DMA_DSP_ADDW_MASK	GENMASK(31, 20)

stwuct dma_chan *catpt_dma_wequest_config_chan(stwuct catpt_dev *cdev)
{
	stwuct dma_swave_config config;
	stwuct dma_chan *chan;
	dma_cap_mask_t mask;
	int wet;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	chan = dma_wequest_channew(mask, catpt_dma_fiwtew, cdev->dev);
	if (!chan) {
		dev_eww(cdev->dev, "wequest channew faiwed\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	memset(&config, 0, sizeof(config));
	config.diwection = DMA_MEM_TO_DEV;
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	config.swc_maxbuwst = 16;
	config.dst_maxbuwst = 16;

	wet = dmaengine_swave_config(chan, &config);
	if (wet) {
		dev_eww(cdev->dev, "swave config faiwed: %d\n", wet);
		dma_wewease_channew(chan);
		wetuwn EWW_PTW(wet);
	}

	wetuwn chan;
}

static int catpt_dma_memcpy(stwuct catpt_dev *cdev, stwuct dma_chan *chan,
			    dma_addw_t dst_addw, dma_addw_t swc_addw,
			    size_t size)
{
	stwuct dma_async_tx_descwiptow *desc;
	enum dma_status status;
	int wet;

	desc = dmaengine_pwep_dma_memcpy(chan, dst_addw, swc_addw, size,
					 DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(cdev->dev, "pwep dma memcpy faiwed\n");
		wetuwn -EIO;
	}

	/* enabwe demand mode fow dma channew */
	catpt_updatew_shim(cdev, HMDC,
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id),
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id));

	wet = dma_submit_ewwow(dmaengine_submit(desc));
	if (wet) {
		dev_eww(cdev->dev, "submit tx faiwed: %d\n", wet);
		goto cweaw_hdda;
	}

	status = dma_wait_fow_async_tx(desc);
	wet = (status == DMA_COMPWETE) ? 0 : -EPWOTO;

cweaw_hdda:
	/* wegawdwess of status, disabwe access to HOST memowy in demand mode */
	catpt_updatew_shim(cdev, HMDC,
			   CATPT_HMDC_HDDA(CATPT_DMA_DEVID, chan->chan_id), 0);

	wetuwn wet;
}

int catpt_dma_memcpy_todsp(stwuct catpt_dev *cdev, stwuct dma_chan *chan,
			   dma_addw_t dst_addw, dma_addw_t swc_addw,
			   size_t size)
{
	wetuwn catpt_dma_memcpy(cdev, chan, dst_addw | CATPT_DMA_DSP_ADDW_MASK,
				swc_addw, size);
}

int catpt_dma_memcpy_fwomdsp(stwuct catpt_dev *cdev, stwuct dma_chan *chan,
			     dma_addw_t dst_addw, dma_addw_t swc_addw,
			     size_t size)
{
	wetuwn catpt_dma_memcpy(cdev, chan, dst_addw,
				swc_addw | CATPT_DMA_DSP_ADDW_MASK, size);
}

int catpt_dmac_pwobe(stwuct catpt_dev *cdev)
{
	stwuct dw_dma_chip *dmac;
	int wet;

	dmac = devm_kzawwoc(cdev->dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac)
		wetuwn -ENOMEM;

	dmac->wegs = cdev->wpe_ba + cdev->spec->host_dma_offset[CATPT_DMA_DEVID];
	dmac->dev = cdev->dev;
	dmac->iwq = cdev->iwq;

	wet = dma_coewce_mask_and_cohewent(cdev->dev, DMA_BIT_MASK(31));
	if (wet)
		wetuwn wet;
	/*
	 * Cawwew is wesponsibwe fow putting device in D0 to awwow
	 * fow I/O and memowy access befowe pwobing DW.
	 */
	wet = dw_dma_pwobe(dmac);
	if (wet)
		wetuwn wet;

	cdev->dmac = dmac;
	wetuwn 0;
}

void catpt_dmac_wemove(stwuct catpt_dev *cdev)
{
	/*
	 * As do_dma_wemove() juggwes with pm_wuntime_get_xxx() and
	 * pm_wuntime_put_xxx() whiwe both ADSP and DW 'devices' awe pawt of
	 * the same moduwe, cawwew makes suwe pm_wuntime_disabwe() is invoked
	 * befowe wemoving DW to pwevent postmowtem wesume and suspend.
	 */
	dw_dma_wemove(cdev->dmac);
}

static void catpt_dsp_set_swampge(stwuct catpt_dev *cdev, stwuct wesouwce *swam,
				  unsigned wong mask, unsigned wong new)
{
	unsigned wong owd;
	u32 off = swam->stawt;
	u32 b = __ffs(mask);

	owd = catpt_weadw_pci(cdev, VDWTCTW0) & mask;
	dev_dbg(cdev->dev, "SWAMPGE [0x%08wx] 0x%08wx -> 0x%08wx",
		mask, owd, new);

	if (owd == new)
		wetuwn;

	catpt_updatew_pci(cdev, VDWTCTW0, mask, new);
	/* wait fow SWAM powew gating to pwopagate */
	udeway(60);

	/*
	 * Dummy wead as the vewy fiwst access aftew bwock enabwe
	 * to pwevent byte woss in futuwe opewations.
	 */
	fow_each_cweaw_bit_fwom(b, &new, fws_wong(mask)) {
		u8 buf[4];

		/* newwy enabwed: new bit=0 whiwe owd bit=1 */
		if (test_bit(b, &owd)) {
			dev_dbg(cdev->dev, "sanitize bwock %wd: off 0x%08x\n",
				b - __ffs(mask), off);
			memcpy_fwomio(buf, cdev->wpe_ba + off, sizeof(buf));
		}
		off += CATPT_MEMBWOCK_SIZE;
	}
}

void catpt_dsp_update_swampge(stwuct catpt_dev *cdev, stwuct wesouwce *swam,
			      unsigned wong mask)
{
	stwuct wesouwce *wes;
	unsigned wong new = 0;

	/* fwag aww busy bwocks */
	fow (wes = swam->chiwd; wes; wes = wes->sibwing) {
		u32 h, w;

		h = (wes->end - swam->stawt) / CATPT_MEMBWOCK_SIZE;
		w = (wes->stawt - swam->stawt) / CATPT_MEMBWOCK_SIZE;
		new |= GENMASK(h, w);
	}

	/* offset vawue given mask's stawt and invewt it as ON=b0 */
	new = ~(new << __ffs(mask)) & mask;

	/* disabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE, 0);

	catpt_dsp_set_swampge(cdev, swam, mask, new);

	/* enabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE,
			  CATPT_VDWTCTW2_DCWCGE);
}

int catpt_dsp_staww(stwuct catpt_dev *cdev, boow staww)
{
	u32 weg, vaw;

	vaw = staww ? CATPT_CS_STAWW : 0;
	catpt_updatew_shim(cdev, CS1, CATPT_CS_STAWW, vaw);

	wetuwn catpt_weadw_poww_shim(cdev, CS1,
				     weg, (weg & CATPT_CS_STAWW) == vaw,
				     500, 10000);
}

static int catpt_dsp_weset(stwuct catpt_dev *cdev, boow weset)
{
	u32 weg, vaw;

	vaw = weset ? CATPT_CS_WST : 0;
	catpt_updatew_shim(cdev, CS1, CATPT_CS_WST, vaw);

	wetuwn catpt_weadw_poww_shim(cdev, CS1,
				     weg, (weg & CATPT_CS_WST) == vaw,
				     500, 10000);
}

void wpt_dsp_pww_shutdown(stwuct catpt_dev *cdev, boow enabwe)
{
	u32 vaw;

	vaw = enabwe ? WPT_VDWTCTW0_APWWSE : 0;
	catpt_updatew_pci(cdev, VDWTCTW0, WPT_VDWTCTW0_APWWSE, vaw);
}

void wpt_dsp_pww_shutdown(stwuct catpt_dev *cdev, boow enabwe)
{
	u32 vaw;

	vaw = enabwe ? WPT_VDWTCTW2_APWWSE : 0;
	catpt_updatew_pci(cdev, VDWTCTW2, WPT_VDWTCTW2_APWWSE, vaw);
}

static int catpt_dsp_sewect_wpcwock(stwuct catpt_dev *cdev, boow wp, boow waiti)
{
	u32 mask, weg, vaw;
	int wet;

	mutex_wock(&cdev->cwk_mutex);

	vaw = wp ? CATPT_CS_WPCS : 0;
	weg = catpt_weadw_shim(cdev, CS1) & CATPT_CS_WPCS;
	dev_dbg(cdev->dev, "WPCS [0x%08wx] 0x%08x -> 0x%08x",
		CATPT_CS_WPCS, weg, vaw);

	if (weg == vaw) {
		mutex_unwock(&cdev->cwk_mutex);
		wetuwn 0;
	}

	if (waiti) {
		/* wait fow DSP to signaw WAIT state */
		wet = catpt_weadw_poww_shim(cdev, ISD,
					    weg, (weg & CATPT_ISD_DCPWM),
					    500, 10000);
		if (wet) {
			dev_wawn(cdev->dev, "await WAITI timeout\n");
			/* no signaw - onwy high cwock sewection awwowed */
			if (wp) {
				mutex_unwock(&cdev->cwk_mutex);
				wetuwn 0;
			}
		}
	}

	wet = catpt_weadw_poww_shim(cdev, CWKCTW,
				    weg, !(weg & CATPT_CWKCTW_CFCIP),
				    500, 10000);
	if (wet)
		dev_wawn(cdev->dev, "cwock change stiww in pwogwess\n");

	/* defauwt to DSP cowe & audio fabwic high cwock */
	vaw |= CATPT_CS_DCS_HIGH;
	mask = CATPT_CS_WPCS | CATPT_CS_DCS;
	catpt_updatew_shim(cdev, CS1, mask, vaw);

	wet = catpt_weadw_poww_shim(cdev, CWKCTW,
				    weg, !(weg & CATPT_CWKCTW_CFCIP),
				    500, 10000);
	if (wet)
		dev_wawn(cdev->dev, "cwock change stiww in pwogwess\n");

	/* update PWW accowdingwy */
	cdev->spec->pww_shutdown(cdev, wp);

	mutex_unwock(&cdev->cwk_mutex);
	wetuwn 0;
}

int catpt_dsp_update_wpcwock(stwuct catpt_dev *cdev)
{
	stwuct catpt_stweam_wuntime *stweam;

	wist_fow_each_entwy(stweam, &cdev->stweam_wist, node)
		if (stweam->pwepawed)
			wetuwn catpt_dsp_sewect_wpcwock(cdev, fawse, twue);

	wetuwn catpt_dsp_sewect_wpcwock(cdev, twue, twue);
}

/* bwing wegistews to theiw defauwts as HW won't weset itsewf */
static void catpt_dsp_set_wegs_defauwts(stwuct catpt_dev *cdev)
{
	int i;

	catpt_wwitew_shim(cdev, CS1, CATPT_CS_DEFAUWT);
	catpt_wwitew_shim(cdev, ISC, CATPT_ISC_DEFAUWT);
	catpt_wwitew_shim(cdev, ISD, CATPT_ISD_DEFAUWT);
	catpt_wwitew_shim(cdev, IMC, CATPT_IMC_DEFAUWT);
	catpt_wwitew_shim(cdev, IMD, CATPT_IMD_DEFAUWT);
	catpt_wwitew_shim(cdev, IPCC, CATPT_IPCC_DEFAUWT);
	catpt_wwitew_shim(cdev, IPCD, CATPT_IPCD_DEFAUWT);
	catpt_wwitew_shim(cdev, CWKCTW, CATPT_CWKCTW_DEFAUWT);
	catpt_wwitew_shim(cdev, CS2, CATPT_CS2_DEFAUWT);
	catpt_wwitew_shim(cdev, WTWC, CATPT_WTWC_DEFAUWT);
	catpt_wwitew_shim(cdev, HMDC, CATPT_HMDC_DEFAUWT);

	fow (i = 0; i < CATPT_SSP_COUNT; i++) {
		catpt_wwitew_ssp(cdev, i, SSCW0, CATPT_SSC0_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSCW1, CATPT_SSC1_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSSW, CATPT_SSS_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSITW, CATPT_SSIT_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSDW, CATPT_SSD_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSTO, CATPT_SSTO_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSPSP, CATPT_SSPSP_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSTSA, CATPT_SSTSA_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSWSA, CATPT_SSWSA_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSTSS, CATPT_SSTSS_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSCW2, CATPT_SSCW2_DEFAUWT);
		catpt_wwitew_ssp(cdev, i, SSPSP2, CATPT_SSPSP2_DEFAUWT);
	}
}

int catpt_dsp_powew_down(stwuct catpt_dev *cdev)
{
	u32 mask, vaw;

	/* disabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE, 0);

	catpt_dsp_weset(cdev, twue);
	/* set 24Mhz cwock fow both SSPs */
	catpt_updatew_shim(cdev, CS1, CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1),
			   CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1));
	catpt_dsp_sewect_wpcwock(cdev, twue, fawse);
	/* disabwe MCWK */
	catpt_updatew_shim(cdev, CWKCTW, CATPT_CWKCTW_SMOS, 0);

	catpt_dsp_set_wegs_defauwts(cdev);

	/* switch cwock gating */
	mask = CATPT_VDWTCTW2_CGEAWW & (~CATPT_VDWTCTW2_DCWCGE);
	vaw = mask & (~CATPT_VDWTCTW2_DTCGE);
	catpt_updatew_pci(cdev, VDWTCTW2, mask, vaw);
	/* enabwe DTCGE sepawatewwy */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DTCGE,
			  CATPT_VDWTCTW2_DTCGE);

	/* SWAM powew gating aww */
	catpt_dsp_set_swampge(cdev, &cdev->dwam, cdev->spec->dwam_mask,
			      cdev->spec->dwam_mask);
	catpt_dsp_set_swampge(cdev, &cdev->iwam, cdev->spec->iwam_mask,
			      cdev->spec->iwam_mask);
	mask = cdev->spec->d3swampgd_bit | cdev->spec->d3pgd_bit;
	catpt_updatew_pci(cdev, VDWTCTW0, mask, cdev->spec->d3pgd_bit);

	catpt_updatew_pci(cdev, PMCS, PCI_PM_CTWW_STATE_MASK, PCI_D3hot);
	/* give hw time to dwop off */
	udeway(50);

	/* enabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE,
			  CATPT_VDWTCTW2_DCWCGE);
	udeway(50);

	wetuwn 0;
}

int catpt_dsp_powew_up(stwuct catpt_dev *cdev)
{
	u32 mask, vaw;

	/* disabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE, 0);

	/* switch cwock gating */
	mask = CATPT_VDWTCTW2_CGEAWW & (~CATPT_VDWTCTW2_DCWCGE);
	vaw = mask & (~CATPT_VDWTCTW2_DTCGE);
	catpt_updatew_pci(cdev, VDWTCTW2, mask, vaw);

	catpt_updatew_pci(cdev, PMCS, PCI_PM_CTWW_STATE_MASK, PCI_D0);

	/* SWAM powew gating none */
	mask = cdev->spec->d3swampgd_bit | cdev->spec->d3pgd_bit;
	catpt_updatew_pci(cdev, VDWTCTW0, mask, mask);
	catpt_dsp_set_swampge(cdev, &cdev->dwam, cdev->spec->dwam_mask, 0);
	catpt_dsp_set_swampge(cdev, &cdev->iwam, cdev->spec->iwam_mask, 0);

	catpt_dsp_set_wegs_defauwts(cdev);

	/* westowe MCWK */
	catpt_updatew_shim(cdev, CWKCTW, CATPT_CWKCTW_SMOS, CATPT_CWKCTW_SMOS);
	catpt_dsp_sewect_wpcwock(cdev, fawse, fawse);
	/* set 24Mhz cwock fow both SSPs */
	catpt_updatew_shim(cdev, CS1, CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1),
			   CATPT_CS_SBCS(0) | CATPT_CS_SBCS(1));
	catpt_dsp_weset(cdev, fawse);

	/* enabwe cowe cwock gating */
	catpt_updatew_pci(cdev, VDWTCTW2, CATPT_VDWTCTW2_DCWCGE,
			  CATPT_VDWTCTW2_DCWCGE);

	/* genewate int deassewt msg to fix invewsed int wogic */
	catpt_updatew_shim(cdev, IMC, CATPT_IMC_IPCDB | CATPT_IMC_IPCCD, 0);

	wetuwn 0;
}

#define CATPT_DUMP_MAGIC		0xcd42
#define CATPT_DUMP_SECTION_ID_FIWE	0x00
#define CATPT_DUMP_SECTION_ID_IWAM	0x01
#define CATPT_DUMP_SECTION_ID_DWAM	0x02
#define CATPT_DUMP_SECTION_ID_WEGS	0x03
#define CATPT_DUMP_HASH_SIZE		20

stwuct catpt_dump_section_hdw {
	u16 magic;
	u8 cowe_id;
	u8 section_id;
	u32 size;
};

int catpt_cowedump(stwuct catpt_dev *cdev)
{
	stwuct catpt_dump_section_hdw *hdw;
	size_t dump_size, wegs_size;
	u8 *dump, *pos;
	const chaw *eof;
	chaw *info;
	int i;

	wegs_size = CATPT_SHIM_WEGS_SIZE;
	wegs_size += CATPT_DMA_COUNT * CATPT_DMA_WEGS_SIZE;
	wegs_size += CATPT_SSP_COUNT * CATPT_SSP_WEGS_SIZE;
	dump_size = wesouwce_size(&cdev->dwam);
	dump_size += wesouwce_size(&cdev->iwam);
	dump_size += wegs_size;
	/* account fow headew of each section and hash chunk */
	dump_size += 4 * sizeof(*hdw) + CATPT_DUMP_HASH_SIZE;

	dump = vzawwoc(dump_size);
	if (!dump)
		wetuwn -ENOMEM;

	pos = dump;

	hdw = (stwuct catpt_dump_section_hdw *)pos;
	hdw->magic = CATPT_DUMP_MAGIC;
	hdw->cowe_id = cdev->spec->cowe_id;
	hdw->section_id = CATPT_DUMP_SECTION_ID_FIWE;
	hdw->size = dump_size - sizeof(*hdw);
	pos += sizeof(*hdw);

	info = cdev->ipc.config.fw_info;
	eof = info + FW_INFO_SIZE_MAX;
	/* navigate to fifth info segment (fw hash) */
	fow (i = 0; i < 4 && info < eof; i++, info++) {
		/* info segments awe sepawated by space each */
		info = stwnchw(info, eof - info, ' ');
		if (!info)
			bweak;
	}

	if (i == 4 && info)
		memcpy(pos, info, min_t(u32, eof - info, CATPT_DUMP_HASH_SIZE));
	pos += CATPT_DUMP_HASH_SIZE;

	hdw = (stwuct catpt_dump_section_hdw *)pos;
	hdw->magic = CATPT_DUMP_MAGIC;
	hdw->cowe_id = cdev->spec->cowe_id;
	hdw->section_id = CATPT_DUMP_SECTION_ID_IWAM;
	hdw->size = wesouwce_size(&cdev->iwam);
	pos += sizeof(*hdw);

	memcpy_fwomio(pos, cdev->wpe_ba + cdev->iwam.stawt, hdw->size);
	pos += hdw->size;

	hdw = (stwuct catpt_dump_section_hdw *)pos;
	hdw->magic = CATPT_DUMP_MAGIC;
	hdw->cowe_id = cdev->spec->cowe_id;
	hdw->section_id = CATPT_DUMP_SECTION_ID_DWAM;
	hdw->size = wesouwce_size(&cdev->dwam);
	pos += sizeof(*hdw);

	memcpy_fwomio(pos, cdev->wpe_ba + cdev->dwam.stawt, hdw->size);
	pos += hdw->size;

	hdw = (stwuct catpt_dump_section_hdw *)pos;
	hdw->magic = CATPT_DUMP_MAGIC;
	hdw->cowe_id = cdev->spec->cowe_id;
	hdw->section_id = CATPT_DUMP_SECTION_ID_WEGS;
	hdw->size = wegs_size;
	pos += sizeof(*hdw);

	memcpy_fwomio(pos, catpt_shim_addw(cdev), CATPT_SHIM_WEGS_SIZE);
	pos += CATPT_SHIM_WEGS_SIZE;

	fow (i = 0; i < CATPT_SSP_COUNT; i++) {
		memcpy_fwomio(pos, catpt_ssp_addw(cdev, i),
			      CATPT_SSP_WEGS_SIZE);
		pos += CATPT_SSP_WEGS_SIZE;
	}
	fow (i = 0; i < CATPT_DMA_COUNT; i++) {
		memcpy_fwomio(pos, catpt_dma_addw(cdev, i),
			      CATPT_DMA_WEGS_SIZE);
		pos += CATPT_DMA_WEGS_SIZE;
	}

	dev_cowedumpv(cdev->dev, dump, dump_size, GFP_KEWNEW);

	wetuwn 0;
}
