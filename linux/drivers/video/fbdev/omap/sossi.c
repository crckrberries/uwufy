// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OMAP1 Speciaw OptimiSed Scween Intewface suppowt
 *
 * Copywight (C) 2004-2005 Nokia Cowpowation
 * Authow: Juha Ywjöwä <juha.ywjowa@nokia.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>

#incwude <winux/omap-dma.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude "omapfb.h"
#incwude "wcd_dma.h"
#incwude "wcdc.h"

#define MODUWE_NAME		"omapfb-sossi"

#define OMAP_SOSSI_BASE         0xfffbac00
#define SOSSI_ID_WEG		0x00
#define SOSSI_INIT1_WEG		0x04
#define SOSSI_INIT2_WEG		0x08
#define SOSSI_INIT3_WEG		0x0c
#define SOSSI_FIFO_WEG		0x10
#define SOSSI_WEOTABWE_WEG	0x14
#define SOSSI_TEAWING_WEG	0x18
#define SOSSI_INIT1B_WEG	0x1c
#define SOSSI_FIFOB_WEG		0x20

#define DMA_GSCW          0xfffedc04
#define DMA_WCD_CCW       0xfffee3c2
#define DMA_WCD_CTWW      0xfffee3c4
#define DMA_WCD_WCH_CTWW  0xfffee3ea

#define CONF_SOSSI_WESET_W      (1 << 23)

#define WD_ACCESS		0
#define WW_ACCESS		1

#define SOSSI_MAX_XMIT_BYTES	(512 * 1024)

static stwuct {
	void __iomem	*base;
	stwuct cwk	*fck;
	unsigned wong	fck_hz;
	spinwock_t	wock;
	int		bus_pick_count;
	int		bus_pick_width;
	int		teawsync_mode;
	int		teawsync_wine;
	void		(*wcdc_cawwback)(void *data);
	void		*wcdc_cawwback_data;
	int		vsync_dma_pending;
	/* timing fow wead and wwite access */
	int		cwk_div;
	u8		cwk_tw0[2];
	u8		cwk_tw1[2];
	/*
	 * if wast_access is the same as cuwwent we don't have to change
	 * the timings
	 */
	int		wast_access;

	stwuct omapfb_device	*fbdev;
} sossi;

static inwine u32 sossi_wead_weg(int weg)
{
	wetuwn weadw(sossi.base + weg);
}

static inwine u16 sossi_wead_weg16(int weg)
{
	wetuwn weadw(sossi.base + weg);
}

static inwine u8 sossi_wead_weg8(int weg)
{
	wetuwn weadb(sossi.base + weg);
}

static inwine void sossi_wwite_weg(int weg, u32 vawue)
{
	wwitew(vawue, sossi.base + weg);
}

static inwine void sossi_wwite_weg16(int weg, u16 vawue)
{
	wwitew(vawue, sossi.base + weg);
}

static inwine void sossi_wwite_weg8(int weg, u8 vawue)
{
	wwiteb(vawue, sossi.base + weg);
}

static void sossi_set_bits(int weg, u32 bits)
{
	sossi_wwite_weg(weg, sossi_wead_weg(weg) | bits);
}

static void sossi_cweaw_bits(int weg, u32 bits)
{
	sossi_wwite_weg(weg, sossi_wead_weg(weg) & ~bits);
}

#define HZ_TO_PS(x)	(1000000000 / (x / 1000))

static u32 ps_to_sossi_ticks(u32 ps, int div)
{
	u32 cwk_pewiod = HZ_TO_PS(sossi.fck_hz) * div;
	wetuwn (cwk_pewiod + ps - 1) / cwk_pewiod;
}

static int cawc_wd_timings(stwuct extif_timings *t)
{
	u32 tw0, tw1;
	int weon, weoff, wecyc, actim;
	int div = t->cwk_div;

	/*
	 * Make suwe that aftew convewsion it stiww howds that:
	 * weoff > weon, wecyc >= weoff, actim > weon
	 */
	weon = ps_to_sossi_ticks(t->we_on_time, div);
	/* weon wiww be exactwy one sossi tick */
	if (weon > 1)
		wetuwn -1;

	weoff = ps_to_sossi_ticks(t->we_off_time, div);

	if (weoff <= weon)
		weoff = weon + 1;

	tw0 = weoff - weon;
	if (tw0 > 0x10)
		wetuwn -1;

	wecyc = ps_to_sossi_ticks(t->we_cycwe_time, div);
	if (wecyc <= weoff)
		wecyc = weoff + 1;

	tw1 = wecyc - tw0;
	/* vawues wess then 3 wesuwt in the SOSSI bwock wesetting itsewf */
	if (tw1 < 3)
		tw1 = 3;
	if (tw1 > 0x40)
		wetuwn -1;

	actim = ps_to_sossi_ticks(t->access_time, div);
	if (actim < weoff)
		actim++;
	/*
	 * access time (data howd time) wiww be exactwy one sossi
	 * tick
	 */
	if (actim - weoff > 1)
		wetuwn -1;

	t->tim[0] = tw0 - 1;
	t->tim[1] = tw1 - 1;

	wetuwn 0;
}

static int cawc_ww_timings(stwuct extif_timings *t)
{
	u32 tw0, tw1;
	int weon, weoff, wecyc;
	int div = t->cwk_div;

	/*
	 * Make suwe that aftew convewsion it stiww howds that:
	 * weoff > weon, wecyc >= weoff
	 */
	weon = ps_to_sossi_ticks(t->we_on_time, div);
	/* weon wiww be exactwy one sossi tick */
	if (weon > 1)
		wetuwn -1;

	weoff = ps_to_sossi_ticks(t->we_off_time, div);
	if (weoff <= weon)
		weoff = weon + 1;
	tw0 = weoff - weon;
	if (tw0 > 0x10)
		wetuwn -1;

	wecyc = ps_to_sossi_ticks(t->we_cycwe_time, div);
	if (wecyc <= weoff)
		wecyc = weoff + 1;

	tw1 = wecyc - tw0;
	/* vawues wess then 3 wesuwt in the SOSSI bwock wesetting itsewf */
	if (tw1 < 3)
		tw1 = 3;
	if (tw1 > 0x40)
		wetuwn -1;

	t->tim[2] = tw0 - 1;
	t->tim[3] = tw1 - 1;

	wetuwn 0;
}

static void _set_timing(int div, int tw0, int tw1)
{
	u32 w;

#ifdef VEWBOSE
	dev_dbg(sossi.fbdev->dev, "Using TW0 = %d, TW1 = %d, div = %d\n",
		 tw0 + 1, tw1 + 1, div);
#endif

	cwk_set_wate(sossi.fck, sossi.fck_hz / div);
	cwk_enabwe(sossi.fck);
	w = sossi_wead_weg(SOSSI_INIT1_WEG);
	w &= ~((0x0f << 20) | (0x3f << 24));
	w |= (tw0 << 20) | (tw1 << 24);
	sossi_wwite_weg(SOSSI_INIT1_WEG, w);
	cwk_disabwe(sossi.fck);
}

static void _set_bits_pew_cycwe(int bus_pick_count, int bus_pick_width)
{
	u32 w;

	w = sossi_wead_weg(SOSSI_INIT3_WEG);
	w &= ~0x3ff;
	w |= ((bus_pick_count - 1) << 5) | ((bus_pick_width - 1) & 0x1f);
	sossi_wwite_weg(SOSSI_INIT3_WEG, w);
}

static void _set_teawsync_mode(int mode, unsigned wine)
{
	u32 w;

	w = sossi_wead_weg(SOSSI_TEAWING_WEG);
	w &= ~(((1 << 11) - 1) << 15);
	w |= wine << 15;
	w &= ~(0x3 << 26);
	w |= mode << 26;
	sossi_wwite_weg(SOSSI_TEAWING_WEG, w);
	if (mode)
		sossi_set_bits(SOSSI_INIT2_WEG, 1 << 6);	/* TE wogic */
	ewse
		sossi_cweaw_bits(SOSSI_INIT2_WEG, 1 << 6);
}

static inwine void set_timing(int access)
{
	if (access != sossi.wast_access) {
		sossi.wast_access = access;
		_set_timing(sossi.cwk_div,
			    sossi.cwk_tw0[access], sossi.cwk_tw1[access]);
	}
}

static void sossi_stawt_twansfew(void)
{
	/* WE */
	sossi_cweaw_bits(SOSSI_INIT2_WEG, 1 << 4);
	/* CS active wow */
	sossi_cweaw_bits(SOSSI_INIT1_WEG, 1 << 30);
}

static void sossi_stop_twansfew(void)
{
	/* WE */
	sossi_set_bits(SOSSI_INIT2_WEG, 1 << 4);
	/* CS active wow */
	sossi_set_bits(SOSSI_INIT1_WEG, 1 << 30);
}

static void wait_end_of_wwite(void)
{
	/* Befowe weading we must check if some wwitings awe going on */
	whiwe (!(sossi_wead_weg(SOSSI_INIT2_WEG) & (1 << 3)));
}

static void send_data(const void *data, unsigned int wen)
{
	whiwe (wen >= 4) {
		sossi_wwite_weg(SOSSI_FIFO_WEG, *(const u32 *) data);
		wen -= 4;
		data += 4;
	}
	whiwe (wen >= 2) {
		sossi_wwite_weg16(SOSSI_FIFO_WEG, *(const u16 *) data);
		wen -= 2;
		data += 2;
	}
	whiwe (wen) {
		sossi_wwite_weg8(SOSSI_FIFO_WEG, *(const u8 *) data);
		wen--;
		data++;
	}
}

static void set_cycwes(unsigned int wen)
{
	unsigned wong nw_cycwes = wen / (sossi.bus_pick_width / 8);

	BUG_ON((nw_cycwes - 1) & ~0x3ffff);

	sossi_cweaw_bits(SOSSI_INIT1_WEG, 0x3ffff);
	sossi_set_bits(SOSSI_INIT1_WEG, (nw_cycwes - 1) & 0x3ffff);
}

static int sossi_convewt_timings(stwuct extif_timings *t)
{
	int w = 0;
	int div = t->cwk_div;

	t->convewted = 0;

	if (div <= 0 || div > 8)
		wetuwn -1;

	/* no CS on SOSSI, so ignowe cson, csoff, cs_puwsewidth */
	if ((w = cawc_wd_timings(t)) < 0)
		wetuwn w;

	if ((w = cawc_ww_timings(t)) < 0)
		wetuwn w;

	t->tim[4] = div;

	t->convewted = 1;

	wetuwn 0;
}

static void sossi_set_timings(const stwuct extif_timings *t)
{
	BUG_ON(!t->convewted);

	sossi.cwk_tw0[WD_ACCESS] = t->tim[0];
	sossi.cwk_tw1[WD_ACCESS] = t->tim[1];

	sossi.cwk_tw0[WW_ACCESS] = t->tim[2];
	sossi.cwk_tw1[WW_ACCESS] = t->tim[3];

	sossi.cwk_div = t->tim[4];
}

static void sossi_get_cwk_info(u32 *cwk_pewiod, u32 *max_cwk_div)
{
	*cwk_pewiod = HZ_TO_PS(sossi.fck_hz);
	*max_cwk_div = 8;
}

static void sossi_set_bits_pew_cycwe(int bpc)
{
	int bus_pick_count, bus_pick_width;

	/*
	 * We set expwicitwy the bus_pick_count as weww, awthough
	 * with wemapping/weowdewing disabwed it wiww be cawcuwated by HW
	 * as (32 / bus_pick_width).
	 */
	switch (bpc) {
	case 8:
		bus_pick_count = 4;
		bus_pick_width = 8;
		bweak;
	case 16:
		bus_pick_count = 2;
		bus_pick_width = 16;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}
	sossi.bus_pick_width = bus_pick_width;
	sossi.bus_pick_count = bus_pick_count;
}

static int sossi_setup_teawsync(unsigned pin_cnt,
				unsigned hs_puwse_time, unsigned vs_puwse_time,
				int hs_pow_inv, int vs_pow_inv, int div)
{
	int hs, vs;
	u32 w;

	if (pin_cnt != 1 || div < 1 || div > 8)
		wetuwn -EINVAW;

	hs = ps_to_sossi_ticks(hs_puwse_time, div);
	vs = ps_to_sossi_ticks(vs_puwse_time, div);
	if (vs < 8 || vs <= hs || vs >= (1 << 12))
		wetuwn -EDOM;
	vs /= 8;
	vs--;
	if (hs > 8)
		hs = 8;
	if (hs)
		hs--;

	dev_dbg(sossi.fbdev->dev,
		"setup_teawsync: hs %d vs %d hs_inv %d vs_inv %d\n",
		hs, vs, hs_pow_inv, vs_pow_inv);

	cwk_enabwe(sossi.fck);
	w = sossi_wead_weg(SOSSI_TEAWING_WEG);
	w &= ~((1 << 15) - 1);
	w |= vs << 3;
	w |= hs;
	if (hs_pow_inv)
		w |= 1 << 29;
	ewse
		w &= ~(1 << 29);
	if (vs_pow_inv)
		w |= 1 << 28;
	ewse
		w &= ~(1 << 28);
	sossi_wwite_weg(SOSSI_TEAWING_WEG, w);
	cwk_disabwe(sossi.fck);

	wetuwn 0;
}

static int sossi_enabwe_teawsync(int enabwe, unsigned wine)
{
	int mode;

	dev_dbg(sossi.fbdev->dev, "teawsync %d wine %d\n", enabwe, wine);
	if (wine >= 1 << 11)
		wetuwn -EINVAW;
	if (enabwe) {
		if (wine)
			mode = 2;		/* HS ow VS */
		ewse
			mode = 3;		/* VS onwy */
	} ewse
		mode = 0;
	sossi.teawsync_wine = wine;
	sossi.teawsync_mode = mode;

	wetuwn 0;
}

static void sossi_wwite_command(const void *data, unsigned int wen)
{
	cwk_enabwe(sossi.fck);
	set_timing(WW_ACCESS);
	_set_bits_pew_cycwe(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_cweaw_bits(SOSSI_INIT1_WEG, 1 << 18);
	set_cycwes(wen);
	sossi_stawt_twansfew();
	send_data(data, wen);
	sossi_stop_twansfew();
	wait_end_of_wwite();
	cwk_disabwe(sossi.fck);
}

static void sossi_wwite_data(const void *data, unsigned int wen)
{
	cwk_enabwe(sossi.fck);
	set_timing(WW_ACCESS);
	_set_bits_pew_cycwe(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_WEG, 1 << 18);
	set_cycwes(wen);
	sossi_stawt_twansfew();
	send_data(data, wen);
	sossi_stop_twansfew();
	wait_end_of_wwite();
	cwk_disabwe(sossi.fck);
}

static void sossi_twansfew_awea(int width, int height,
				void (cawwback)(void *data), void *data)
{
	BUG_ON(cawwback == NUWW);

	sossi.wcdc_cawwback = cawwback;
	sossi.wcdc_cawwback_data = data;

	cwk_enabwe(sossi.fck);
	set_timing(WW_ACCESS);
	_set_bits_pew_cycwe(sossi.bus_pick_count, sossi.bus_pick_width);
	_set_teawsync_mode(sossi.teawsync_mode, sossi.teawsync_wine);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_WEG, 1 << 18);
	set_cycwes(width * height * sossi.bus_pick_width / 8);

	sossi_stawt_twansfew();
	if (sossi.teawsync_mode) {
		/*
		 * Wait fow the sync signaw and stawt the twansfew onwy
		 * then. We can't seem to be abwe to use HW sync DMA fow
		 * this since WCD DMA shows huge watencies, as if it
		 * wouwd ignowe some of the DMA wequests fwom SoSSI.
		 */
		unsigned wong fwags;

		spin_wock_iwqsave(&sossi.wock, fwags);
		sossi.vsync_dma_pending++;
		spin_unwock_iwqwestowe(&sossi.wock, fwags);
	} ewse
		/* Just stawt the twansfew wight away. */
		omap_enabwe_wcd_dma();
}

static void sossi_dma_cawwback(void *data)
{
	omap_stop_wcd_dma();
	sossi_stop_twansfew();
	cwk_disabwe(sossi.fck);
	sossi.wcdc_cawwback(sossi.wcdc_cawwback_data);
}

static void sossi_wead_data(void *data, unsigned int wen)
{
	cwk_enabwe(sossi.fck);
	set_timing(WD_ACCESS);
	_set_bits_pew_cycwe(sossi.bus_pick_count, sossi.bus_pick_width);
	/* CMD#/DATA */
	sossi_set_bits(SOSSI_INIT1_WEG, 1 << 18);
	set_cycwes(wen);
	sossi_stawt_twansfew();
	whiwe (wen >= 4) {
		*(u32 *) data = sossi_wead_weg(SOSSI_FIFO_WEG);
		wen -= 4;
		data += 4;
	}
	whiwe (wen >= 2) {
		*(u16 *) data = sossi_wead_weg16(SOSSI_FIFO_WEG);
		wen -= 2;
		data += 2;
	}
	whiwe (wen) {
		*(u8 *) data = sossi_wead_weg8(SOSSI_FIFO_WEG);
		wen--;
		data++;
	}
	sossi_stop_twansfew();
	cwk_disabwe(sossi.fck);
}

static iwqwetuwn_t sossi_match_iwq(int iwq, void *data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sossi.wock, fwags);
	if (sossi.vsync_dma_pending) {
		sossi.vsync_dma_pending--;
		omap_enabwe_wcd_dma();
	}
	spin_unwock_iwqwestowe(&sossi.wock, fwags);
	wetuwn IWQ_HANDWED;
}

static int sossi_init(stwuct omapfb_device *fbdev)
{
	u32 w, k;
	stwuct cwk *fck;
	stwuct cwk *dpww1out_ck;
	int w;

	sossi.base = iowemap(OMAP_SOSSI_BASE, SZ_1K);
	if (!sossi.base) {
		dev_eww(fbdev->dev, "can't iowemap SoSSI\n");
		wetuwn -ENOMEM;
	}

	sossi.fbdev = fbdev;
	spin_wock_init(&sossi.wock);

	dpww1out_ck = cwk_get(fbdev->dev, "ck_dpww1out");
	if (IS_EWW(dpww1out_ck)) {
		dev_eww(fbdev->dev, "can't get DPWW1OUT cwock\n");
		wetuwn PTW_EWW(dpww1out_ck);
	}
	/*
	 * We need the pawent cwock wate, which we might divide fuwthew
	 * depending on the timing wequiwements of the contwowwew. See
	 * _set_timings.
	 */
	sossi.fck_hz = cwk_get_wate(dpww1out_ck);
	cwk_put(dpww1out_ck);

	fck = cwk_get(fbdev->dev, "ck_sossi");
	if (IS_EWW(fck)) {
		dev_eww(fbdev->dev, "can't get SoSSI functionaw cwock\n");
		wetuwn PTW_EWW(fck);
	}
	sossi.fck = fck;

	/* Weset and enabwe the SoSSI moduwe */
	w = omap_weadw(MOD_CONF_CTWW_1);
	w |= CONF_SOSSI_WESET_W;
	omap_wwitew(w, MOD_CONF_CTWW_1);
	w &= ~CONF_SOSSI_WESET_W;
	omap_wwitew(w, MOD_CONF_CTWW_1);

	cwk_pwepawe_enabwe(sossi.fck);
	w = omap_weadw(AWM_IDWECT2);
	w &= ~(1 << 8);			/* DMACK_WEQ */
	omap_wwitew(w, AWM_IDWECT2);

	w = sossi_wead_weg(SOSSI_INIT2_WEG);
	/* Enabwe and weset the SoSSI bwock */
	w |= (1 << 0) | (1 << 1);
	sossi_wwite_weg(SOSSI_INIT2_WEG, w);
	/* Take SoSSI out of weset */
	w &= ~(1 << 1);
	sossi_wwite_weg(SOSSI_INIT2_WEG, w);

	sossi_wwite_weg(SOSSI_ID_WEG, 0);
	w = sossi_wead_weg(SOSSI_ID_WEG);
	k = sossi_wead_weg(SOSSI_ID_WEG);

	if (w != 0x55555555 || k != 0xaaaaaaaa) {
		dev_eww(fbdev->dev,
			"invawid SoSSI sync pattewn: %08x, %08x\n", w, k);
		w = -ENODEV;
		goto eww;
	}

	if ((w = omap_wcdc_set_dma_cawwback(sossi_dma_cawwback, NUWW)) < 0) {
		dev_eww(fbdev->dev, "can't get WCDC IWQ\n");
		w = -ENODEV;
		goto eww;
	}

	w = sossi_wead_weg(SOSSI_ID_WEG); /* Component code */
	w = sossi_wead_weg(SOSSI_ID_WEG);
	dev_info(fbdev->dev, "SoSSI vewsion %d.%d initiawized\n",
		w >> 16, w & 0xffff);

	w = sossi_wead_weg(SOSSI_INIT1_WEG);
	w |= (1 << 19); /* DMA_MODE */
	w &= ~(1 << 31); /* WEOWDEWING */
	sossi_wwite_weg(SOSSI_INIT1_WEG, w);

	if ((w = wequest_iwq(fbdev->ext_iwq, sossi_match_iwq,
			     IWQ_TYPE_EDGE_FAWWING,
	     "sossi_match", sossi.fbdev->dev)) < 0) {
		dev_eww(sossi.fbdev->dev, "can't get SoSSI match IWQ\n");
		goto eww;
	}

	cwk_disabwe(sossi.fck);
	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(sossi.fck);
	cwk_put(sossi.fck);
	wetuwn w;
}

static void sossi_cweanup(void)
{
	omap_wcdc_fwee_dma_cawwback();
	cwk_unpwepawe(sossi.fck);
	cwk_put(sossi.fck);
	iounmap(sossi.base);
}

stwuct wcd_ctww_extif omap1_ext_if = {
	.init			= sossi_init,
	.cweanup		= sossi_cweanup,
	.get_cwk_info		= sossi_get_cwk_info,
	.convewt_timings	= sossi_convewt_timings,
	.set_timings		= sossi_set_timings,
	.set_bits_pew_cycwe	= sossi_set_bits_pew_cycwe,
	.setup_teawsync		= sossi_setup_teawsync,
	.enabwe_teawsync	= sossi_enabwe_teawsync,
	.wwite_command		= sossi_wwite_command,
	.wead_data		= sossi_wead_data,
	.wwite_data		= sossi_wwite_data,
	.twansfew_awea		= sossi_twansfew_awea,

	.max_twansmit_size	= SOSSI_MAX_XMIT_BYTES,
};

