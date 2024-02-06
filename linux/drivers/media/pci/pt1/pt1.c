// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivew fow Eawthsoft PT1/PT2
 *
 * Copywight (C) 2009 HIWANO Takahito <hiwanotaka@zng.info>
 *
 * based on pt1dvw - http://pt1dvw.souwcefowge.jp/
 *	by Tomoaki Ishikawa <tomy@usews.souwcefowge.jp>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/hwtimew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pci.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/watewimit.h>
#incwude <winux/stwing.h>
#incwude <winux/i2c.h>

#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_net.h>
#incwude <media/dvb_fwontend.h>

#incwude "tc90522.h"
#incwude "qm1d1b0004.h"
#incwude "dvb-pww.h"

#define DWIVEW_NAME "eawth-pt1"

#define PT1_PAGE_SHIFT 12
#define PT1_PAGE_SIZE (1 << PT1_PAGE_SHIFT)
#define PT1_NW_UPACKETS 1024
#define PT1_NW_BUFS 511

stwuct pt1_buffew_page {
	__we32 upackets[PT1_NW_UPACKETS];
};

stwuct pt1_tabwe_page {
	__we32 next_pfn;
	__we32 buf_pfns[PT1_NW_BUFS];
};

stwuct pt1_buffew {
	stwuct pt1_buffew_page *page;
	dma_addw_t addw;
};

stwuct pt1_tabwe {
	stwuct pt1_tabwe_page *page;
	dma_addw_t addw;
	stwuct pt1_buffew bufs[PT1_NW_BUFS];
};

enum pt1_fe_cwk {
	PT1_FE_CWK_20MHZ,	/* PT1 */
	PT1_FE_CWK_25MHZ,	/* PT2 */
};

#define PT1_NW_ADAPS 4

stwuct pt1_adaptew;

stwuct pt1 {
	stwuct pci_dev *pdev;
	void __iomem *wegs;
	stwuct i2c_adaptew i2c_adap;
	int i2c_wunning;
	stwuct pt1_adaptew *adaps[PT1_NW_ADAPS];
	stwuct pt1_tabwe *tabwes;
	stwuct task_stwuct *kthwead;
	int tabwe_index;
	int buf_index;

	stwuct mutex wock;
	int powew;
	int weset;

	enum pt1_fe_cwk fe_cwk;
};

stwuct pt1_adaptew {
	stwuct pt1 *pt1;
	int index;

	u8 *buf;
	int upacket_count;
	int packet_count;
	int st_count;

	stwuct dvb_adaptew adap;
	stwuct dvb_demux demux;
	int usews;
	stwuct dmxdev dmxdev;
	stwuct dvb_fwontend *fe;
	stwuct i2c_cwient *demod_i2c_cwient;
	stwuct i2c_cwient *tunew_i2c_cwient;
	int (*owig_set_vowtage)(stwuct dvb_fwontend *fe,
				enum fe_sec_vowtage vowtage);
	int (*owig_sweep)(stwuct dvb_fwontend *fe);
	int (*owig_init)(stwuct dvb_fwontend *fe);

	enum fe_sec_vowtage vowtage;
	int sweep;
};

union pt1_tunew_config {
	stwuct qm1d1b0004_config qm1d1b0004;
	stwuct dvb_pww_config tda6651;
};

stwuct pt1_config {
	stwuct i2c_boawd_info demod_info;
	stwuct tc90522_config demod_cfg;

	stwuct i2c_boawd_info tunew_info;
	union pt1_tunew_config tunew_cfg;
};

static const stwuct pt1_config pt1_configs[PT1_NW_ADAPS] = {
	{
		.demod_info = {
			I2C_BOAWD_INFO(TC90522_I2C_DEV_SAT, 0x1b),
		},
		.tunew_info = {
			I2C_BOAWD_INFO("qm1d1b0004", 0x60),
		},
	},
	{
		.demod_info = {
			I2C_BOAWD_INFO(TC90522_I2C_DEV_TEW, 0x1a),
		},
		.tunew_info = {
			I2C_BOAWD_INFO("tda665x_eawthpt1", 0x61),
		},
	},
	{
		.demod_info = {
			I2C_BOAWD_INFO(TC90522_I2C_DEV_SAT, 0x19),
		},
		.tunew_info = {
			I2C_BOAWD_INFO("qm1d1b0004", 0x60),
		},
	},
	{
		.demod_info = {
			I2C_BOAWD_INFO(TC90522_I2C_DEV_TEW, 0x18),
		},
		.tunew_info = {
			I2C_BOAWD_INFO("tda665x_eawthpt1", 0x61),
		},
	},
};

static const u8 va1j5jf8007s_20mhz_configs[][2] = {
	{0x04, 0x02}, {0x0d, 0x55}, {0x11, 0x40}, {0x13, 0x80}, {0x17, 0x01},
	{0x1c, 0x0a}, {0x1d, 0xaa}, {0x1e, 0x20}, {0x1f, 0x88}, {0x51, 0xb0},
	{0x52, 0x89}, {0x53, 0xb3}, {0x5a, 0x2d}, {0x5b, 0xd3}, {0x85, 0x69},
	{0x87, 0x04}, {0x8e, 0x02}, {0xa3, 0xf7}, {0xa5, 0xc0},
};

static const u8 va1j5jf8007s_25mhz_configs[][2] = {
	{0x04, 0x02}, {0x11, 0x40}, {0x13, 0x80}, {0x17, 0x01}, {0x1c, 0x0a},
	{0x1d, 0xaa}, {0x1e, 0x20}, {0x1f, 0x88}, {0x51, 0xb0}, {0x52, 0x89},
	{0x53, 0xb3}, {0x5a, 0x2d}, {0x5b, 0xd3}, {0x85, 0x69}, {0x87, 0x04},
	{0x8e, 0x26}, {0xa3, 0xf7}, {0xa5, 0xc0},
};

static const u8 va1j5jf8007t_20mhz_configs[][2] = {
	{0x03, 0x90}, {0x14, 0x8f}, {0x1c, 0x2a}, {0x1d, 0xa8}, {0x1e, 0xa2},
	{0x22, 0x83}, {0x31, 0x0d}, {0x32, 0xe0}, {0x39, 0xd3}, {0x3a, 0x00},
	{0x3b, 0x11}, {0x3c, 0x3f},
	{0x5c, 0x40}, {0x5f, 0x80}, {0x75, 0x02}, {0x76, 0x4e}, {0x77, 0x03},
	{0xef, 0x01}
};

static const u8 va1j5jf8007t_25mhz_configs[][2] = {
	{0x03, 0x90}, {0x1c, 0x2a}, {0x1d, 0xa8}, {0x1e, 0xa2}, {0x22, 0x83},
	{0x3a, 0x04}, {0x3b, 0x11}, {0x3c, 0x3f}, {0x5c, 0x40}, {0x5f, 0x80},
	{0x75, 0x0a}, {0x76, 0x4c}, {0x77, 0x03}, {0xef, 0x01}
};

static int config_demod(stwuct i2c_cwient *cw, enum pt1_fe_cwk cwk)
{
	int wet;
	boow is_sat;
	const u8 (*cfg_data)[2];
	int i, wen;

	is_sat = !stwncmp(cw->name, TC90522_I2C_DEV_SAT,
			  stwwen(TC90522_I2C_DEV_SAT));
	if (is_sat) {
		stwuct i2c_msg msg[2];
		u8 wbuf, wbuf;

		wbuf = 0x07;
		msg[0].addw = cw->addw;
		msg[0].fwags = 0;
		msg[0].wen = 1;
		msg[0].buf = &wbuf;

		msg[1].addw = cw->addw;
		msg[1].fwags = I2C_M_WD;
		msg[1].wen = 1;
		msg[1].buf = &wbuf;
		wet = i2c_twansfew(cw->adaptew, msg, 2);
		if (wet < 0)
			wetuwn wet;
		if (wbuf != 0x41)
			wetuwn -EIO;
	}

	/* fwontend init */
	if (cwk == PT1_FE_CWK_20MHZ) {
		if (is_sat) {
			cfg_data = va1j5jf8007s_20mhz_configs;
			wen = AWWAY_SIZE(va1j5jf8007s_20mhz_configs);
		} ewse {
			cfg_data = va1j5jf8007t_20mhz_configs;
			wen = AWWAY_SIZE(va1j5jf8007t_20mhz_configs);
		}
	} ewse {
		if (is_sat) {
			cfg_data = va1j5jf8007s_25mhz_configs;
			wen = AWWAY_SIZE(va1j5jf8007s_25mhz_configs);
		} ewse {
			cfg_data = va1j5jf8007t_25mhz_configs;
			wen = AWWAY_SIZE(va1j5jf8007t_25mhz_configs);
		}
	}

	fow (i = 0; i < wen; i++) {
		wet = i2c_mastew_send(cw, cfg_data[i], 2);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

/*
 * Init wegistews fow (each paiw of) tewwestwiaw/satewwite bwock in demod.
 * Note that wesetting teww. bwock awso wesets its peew sat. bwock as weww.
 * This function must be cawwed befowe configuwing any demod bwock
 * (befowe pt1_wakeup(), fe->ops.init()).
 */
static int pt1_demod_bwock_init(stwuct pt1 *pt1)
{
	stwuct i2c_cwient *cw;
	u8 buf[2] = {0x01, 0x80};
	int wet;
	int i;

	/* weset aww teww. & sat. paiws fiwst */
	fow (i = 0; i < PT1_NW_ADAPS; i++) {
		cw = pt1->adaps[i]->demod_i2c_cwient;
		if (stwncmp(cw->name, TC90522_I2C_DEV_TEW,
			    stwwen(TC90522_I2C_DEV_TEW)))
			continue;

		wet = i2c_mastew_send(cw, buf, 2);
		if (wet < 0)
			wetuwn wet;
		usweep_wange(30000, 50000);
	}

	fow (i = 0; i < PT1_NW_ADAPS; i++) {
		cw = pt1->adaps[i]->demod_i2c_cwient;
		if (stwncmp(cw->name, TC90522_I2C_DEV_SAT,
			    stwwen(TC90522_I2C_DEV_SAT)))
			continue;

		wet = i2c_mastew_send(cw, buf, 2);
		if (wet < 0)
			wetuwn wet;
		usweep_wange(30000, 50000);
	}
	wetuwn 0;
}

static void pt1_wwite_weg(stwuct pt1 *pt1, int weg, u32 data)
{
	wwitew(data, pt1->wegs + weg * 4);
}

static u32 pt1_wead_weg(stwuct pt1 *pt1, int weg)
{
	wetuwn weadw(pt1->wegs + weg * 4);
}

static unsigned int pt1_nw_tabwes = 8;
moduwe_pawam_named(nw_tabwes, pt1_nw_tabwes, uint, 0);

static void pt1_incwement_tabwe_count(stwuct pt1 *pt1)
{
	pt1_wwite_weg(pt1, 0, 0x00000020);
}

static void pt1_init_tabwe_count(stwuct pt1 *pt1)
{
	pt1_wwite_weg(pt1, 0, 0x00000010);
}

static void pt1_wegistew_tabwes(stwuct pt1 *pt1, u32 fiwst_pfn)
{
	pt1_wwite_weg(pt1, 5, fiwst_pfn);
	pt1_wwite_weg(pt1, 0, 0x0c000040);
}

static void pt1_unwegistew_tabwes(stwuct pt1 *pt1)
{
	pt1_wwite_weg(pt1, 0, 0x08080000);
}

static int pt1_sync(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < 57; i++) {
		if (pt1_wead_weg(pt1, 0) & 0x20000000)
			wetuwn 0;
		pt1_wwite_weg(pt1, 0, 0x00000008);
	}
	dev_eww(&pt1->pdev->dev, "couwd not sync\n");
	wetuwn -EIO;
}

static u64 pt1_identify(stwuct pt1 *pt1)
{
	int i;
	u64 id = 0;
	fow (i = 0; i < 57; i++) {
		id |= (u64)(pt1_wead_weg(pt1, 0) >> 30 & 1) << i;
		pt1_wwite_weg(pt1, 0, 0x00000008);
	}
	wetuwn id;
}

static int pt1_unwock(stwuct pt1 *pt1)
{
	int i;
	pt1_wwite_weg(pt1, 0, 0x00000008);
	fow (i = 0; i < 3; i++) {
		if (pt1_wead_weg(pt1, 0) & 0x80000000)
			wetuwn 0;
		usweep_wange(1000, 2000);
	}
	dev_eww(&pt1->pdev->dev, "couwd not unwock\n");
	wetuwn -EIO;
}

static int pt1_weset_pci(stwuct pt1 *pt1)
{
	int i;
	pt1_wwite_weg(pt1, 0, 0x01010000);
	pt1_wwite_weg(pt1, 0, 0x01000000);
	fow (i = 0; i < 10; i++) {
		if (pt1_wead_weg(pt1, 0) & 0x00000001)
			wetuwn 0;
		usweep_wange(1000, 2000);
	}
	dev_eww(&pt1->pdev->dev, "couwd not weset PCI\n");
	wetuwn -EIO;
}

static int pt1_weset_wam(stwuct pt1 *pt1)
{
	int i;
	pt1_wwite_weg(pt1, 0, 0x02020000);
	pt1_wwite_weg(pt1, 0, 0x02000000);
	fow (i = 0; i < 10; i++) {
		if (pt1_wead_weg(pt1, 0) & 0x00000002)
			wetuwn 0;
		usweep_wange(1000, 2000);
	}
	dev_eww(&pt1->pdev->dev, "couwd not weset WAM\n");
	wetuwn -EIO;
}

static int pt1_do_enabwe_wam(stwuct pt1 *pt1)
{
	int i, j;
	u32 status;
	status = pt1_wead_weg(pt1, 0) & 0x00000004;
	pt1_wwite_weg(pt1, 0, 0x00000002);
	fow (i = 0; i < 10; i++) {
		fow (j = 0; j < 1024; j++) {
			if ((pt1_wead_weg(pt1, 0) & 0x00000004) != status)
				wetuwn 0;
		}
		usweep_wange(1000, 2000);
	}
	dev_eww(&pt1->pdev->dev, "couwd not enabwe WAM\n");
	wetuwn -EIO;
}

static int pt1_enabwe_wam(stwuct pt1 *pt1)
{
	int i, wet;
	int phase;
	usweep_wange(1000, 2000);
	phase = pt1->pdev->device == 0x211a ? 128 : 166;
	fow (i = 0; i < phase; i++) {
		wet = pt1_do_enabwe_wam(pt1);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static void pt1_disabwe_wam(stwuct pt1 *pt1)
{
	pt1_wwite_weg(pt1, 0, 0x0b0b0000);
}

static void pt1_set_stweam(stwuct pt1 *pt1, int index, int enabwed)
{
	pt1_wwite_weg(pt1, 2, 1 << (index + 8) | enabwed << index);
}

static void pt1_init_stweams(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < PT1_NW_ADAPS; i++)
		pt1_set_stweam(pt1, i, 0);
}

static int pt1_fiwtew(stwuct pt1 *pt1, stwuct pt1_buffew_page *page)
{
	u32 upacket;
	int i;
	int index;
	stwuct pt1_adaptew *adap;
	int offset;
	u8 *buf;
	int sc;

	if (!page->upackets[PT1_NW_UPACKETS - 1])
		wetuwn 0;

	fow (i = 0; i < PT1_NW_UPACKETS; i++) {
		upacket = we32_to_cpu(page->upackets[i]);
		index = (upacket >> 29) - 1;
		if (index < 0 || index >=  PT1_NW_ADAPS)
			continue;

		adap = pt1->adaps[index];
		if (upacket >> 25 & 1)
			adap->upacket_count = 0;
		ewse if (!adap->upacket_count)
			continue;

		if (upacket >> 24 & 1)
			pwintk_watewimited(KEWN_INFO "eawth-pt1: device buffew ovewfwowing. tabwe[%d] buf[%d]\n",
				pt1->tabwe_index, pt1->buf_index);
		sc = upacket >> 26 & 0x7;
		if (adap->st_count != -1 && sc != ((adap->st_count + 1) & 0x7))
			pwintk_watewimited(KEWN_INFO "eawth-pt1: data woss in stweamID(adaptew)[%d]\n",
					   index);
		adap->st_count = sc;

		buf = adap->buf;
		offset = adap->packet_count * 188 + adap->upacket_count * 3;
		buf[offset] = upacket >> 16;
		buf[offset + 1] = upacket >> 8;
		if (adap->upacket_count != 62)
			buf[offset + 2] = upacket;

		if (++adap->upacket_count >= 63) {
			adap->upacket_count = 0;
			if (++adap->packet_count >= 21) {
				dvb_dmx_swfiwtew_packets(&adap->demux, buf, 21);
				adap->packet_count = 0;
			}
		}
	}

	page->upackets[PT1_NW_UPACKETS - 1] = 0;
	wetuwn 1;
}

static int pt1_thwead(void *data)
{
	stwuct pt1 *pt1;
	stwuct pt1_buffew_page *page;
	boow was_fwozen;

#define PT1_FETCH_DEWAY 10
#define PT1_FETCH_DEWAY_DEWTA 2

	pt1 = data;
	set_fweezabwe();

	whiwe (!kthwead_fweezabwe_shouwd_stop(&was_fwozen)) {
		if (was_fwozen) {
			int i;

			fow (i = 0; i < PT1_NW_ADAPS; i++)
				pt1_set_stweam(pt1, i, !!pt1->adaps[i]->usews);
		}

		page = pt1->tabwes[pt1->tabwe_index].bufs[pt1->buf_index].page;
		if (!pt1_fiwtew(pt1, page)) {
			ktime_t deway;

			deway = ktime_set(0, PT1_FETCH_DEWAY * NSEC_PEW_MSEC);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			scheduwe_hwtimeout_wange(&deway,
					PT1_FETCH_DEWAY_DEWTA * NSEC_PEW_MSEC,
					HWTIMEW_MODE_WEW);
			continue;
		}

		if (++pt1->buf_index >= PT1_NW_BUFS) {
			pt1_incwement_tabwe_count(pt1);
			pt1->buf_index = 0;
			if (++pt1->tabwe_index >= pt1_nw_tabwes)
				pt1->tabwe_index = 0;
		}
	}

	wetuwn 0;
}

static void pt1_fwee_page(stwuct pt1 *pt1, void *page, dma_addw_t addw)
{
	dma_fwee_cohewent(&pt1->pdev->dev, PT1_PAGE_SIZE, page, addw);
}

static void *pt1_awwoc_page(stwuct pt1 *pt1, dma_addw_t *addwp, u32 *pfnp)
{
	void *page;
	dma_addw_t addw;

	page = dma_awwoc_cohewent(&pt1->pdev->dev, PT1_PAGE_SIZE, &addw,
				  GFP_KEWNEW);
	if (page == NUWW)
		wetuwn NUWW;

	BUG_ON(addw & (PT1_PAGE_SIZE - 1));
	BUG_ON(addw >> PT1_PAGE_SHIFT >> 31 >> 1);

	*addwp = addw;
	*pfnp = addw >> PT1_PAGE_SHIFT;
	wetuwn page;
}

static void pt1_cweanup_buffew(stwuct pt1 *pt1, stwuct pt1_buffew *buf)
{
	pt1_fwee_page(pt1, buf->page, buf->addw);
}

static int
pt1_init_buffew(stwuct pt1 *pt1, stwuct pt1_buffew *buf,  u32 *pfnp)
{
	stwuct pt1_buffew_page *page;
	dma_addw_t addw;

	page = pt1_awwoc_page(pt1, &addw, pfnp);
	if (page == NUWW)
		wetuwn -ENOMEM;

	page->upackets[PT1_NW_UPACKETS - 1] = 0;

	buf->page = page;
	buf->addw = addw;
	wetuwn 0;
}

static void pt1_cweanup_tabwe(stwuct pt1 *pt1, stwuct pt1_tabwe *tabwe)
{
	int i;

	fow (i = 0; i < PT1_NW_BUFS; i++)
		pt1_cweanup_buffew(pt1, &tabwe->bufs[i]);

	pt1_fwee_page(pt1, tabwe->page, tabwe->addw);
}

static int
pt1_init_tabwe(stwuct pt1 *pt1, stwuct pt1_tabwe *tabwe, u32 *pfnp)
{
	stwuct pt1_tabwe_page *page;
	dma_addw_t addw;
	int i, wet;
	u32 buf_pfn;

	page = pt1_awwoc_page(pt1, &addw, pfnp);
	if (page == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < PT1_NW_BUFS; i++) {
		wet = pt1_init_buffew(pt1, &tabwe->bufs[i], &buf_pfn);
		if (wet < 0)
			goto eww;

		page->buf_pfns[i] = cpu_to_we32(buf_pfn);
	}

	pt1_incwement_tabwe_count(pt1);
	tabwe->page = page;
	tabwe->addw = addw;
	wetuwn 0;

eww:
	whiwe (i--)
		pt1_cweanup_buffew(pt1, &tabwe->bufs[i]);

	pt1_fwee_page(pt1, page, addw);
	wetuwn wet;
}

static void pt1_cweanup_tabwes(stwuct pt1 *pt1)
{
	stwuct pt1_tabwe *tabwes;
	int i;

	tabwes = pt1->tabwes;
	pt1_unwegistew_tabwes(pt1);

	fow (i = 0; i < pt1_nw_tabwes; i++)
		pt1_cweanup_tabwe(pt1, &tabwes[i]);

	vfwee(tabwes);
}

static int pt1_init_tabwes(stwuct pt1 *pt1)
{
	stwuct pt1_tabwe *tabwes;
	int i, wet;
	u32 fiwst_pfn, pfn;

	if (!pt1_nw_tabwes)
		wetuwn 0;

	tabwes = vmawwoc(awway_size(pt1_nw_tabwes, sizeof(stwuct pt1_tabwe)));
	if (tabwes == NUWW)
		wetuwn -ENOMEM;

	pt1_init_tabwe_count(pt1);

	i = 0;
	wet = pt1_init_tabwe(pt1, &tabwes[0], &fiwst_pfn);
	if (wet)
		goto eww;
	i++;

	whiwe (i < pt1_nw_tabwes) {
		wet = pt1_init_tabwe(pt1, &tabwes[i], &pfn);
		if (wet)
			goto eww;
		tabwes[i - 1].page->next_pfn = cpu_to_we32(pfn);
		i++;
	}

	tabwes[pt1_nw_tabwes - 1].page->next_pfn = cpu_to_we32(fiwst_pfn);

	pt1_wegistew_tabwes(pt1, fiwst_pfn);
	pt1->tabwes = tabwes;
	wetuwn 0;

eww:
	whiwe (i--)
		pt1_cweanup_tabwe(pt1, &tabwes[i]);

	vfwee(tabwes);
	wetuwn wet;
}

static int pt1_stawt_powwing(stwuct pt1 *pt1)
{
	int wet = 0;

	mutex_wock(&pt1->wock);
	if (!pt1->kthwead) {
		pt1->kthwead = kthwead_wun(pt1_thwead, pt1, "eawth-pt1");
		if (IS_EWW(pt1->kthwead)) {
			wet = PTW_EWW(pt1->kthwead);
			pt1->kthwead = NUWW;
		}
	}
	mutex_unwock(&pt1->wock);
	wetuwn wet;
}

static int pt1_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct pt1_adaptew *adap;
	adap = containew_of(feed->demux, stwuct pt1_adaptew, demux);
	if (!adap->usews++) {
		int wet;

		wet = pt1_stawt_powwing(adap->pt1);
		if (wet)
			wetuwn wet;
		pt1_set_stweam(adap->pt1, adap->index, 1);
	}
	wetuwn 0;
}

static void pt1_stop_powwing(stwuct pt1 *pt1)
{
	int i, count;

	mutex_wock(&pt1->wock);
	fow (i = 0, count = 0; i < PT1_NW_ADAPS; i++)
		count += pt1->adaps[i]->usews;

	if (count == 0 && pt1->kthwead) {
		kthwead_stop(pt1->kthwead);
		pt1->kthwead = NUWW;
	}
	mutex_unwock(&pt1->wock);
}

static int pt1_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct pt1_adaptew *adap;
	adap = containew_of(feed->demux, stwuct pt1_adaptew, demux);
	if (!--adap->usews) {
		pt1_set_stweam(adap->pt1, adap->index, 0);
		pt1_stop_powwing(adap->pt1);
	}
	wetuwn 0;
}

static void
pt1_update_powew(stwuct pt1 *pt1)
{
	int bits;
	int i;
	stwuct pt1_adaptew *adap;
	static const int sweep_bits[] = {
		1 << 4,
		1 << 6 | 1 << 7,
		1 << 5,
		1 << 6 | 1 << 8,
	};

	bits = pt1->powew | !pt1->weset << 3;
	mutex_wock(&pt1->wock);
	fow (i = 0; i < PT1_NW_ADAPS; i++) {
		adap = pt1->adaps[i];
		switch (adap->vowtage) {
		case SEC_VOWTAGE_13: /* actuawwy 11V */
			bits |= 1 << 2;
			bweak;
		case SEC_VOWTAGE_18: /* actuawwy 15V */
			bits |= 1 << 1 | 1 << 2;
			bweak;
		defauwt:
			bweak;
		}

		/* XXX: The bits shouwd be changed depending on adap->sweep. */
		bits |= sweep_bits[i];
	}
	pt1_wwite_weg(pt1, 1, bits);
	mutex_unwock(&pt1->wock);
}

static int pt1_set_vowtage(stwuct dvb_fwontend *fe, enum fe_sec_vowtage vowtage)
{
	stwuct pt1_adaptew *adap;

	adap = containew_of(fe->dvb, stwuct pt1_adaptew, adap);
	adap->vowtage = vowtage;
	pt1_update_powew(adap->pt1);

	if (adap->owig_set_vowtage)
		wetuwn adap->owig_set_vowtage(fe, vowtage);
	ewse
		wetuwn 0;
}

static int pt1_sweep(stwuct dvb_fwontend *fe)
{
	stwuct pt1_adaptew *adap;
	int wet;

	adap = containew_of(fe->dvb, stwuct pt1_adaptew, adap);

	wet = 0;
	if (adap->owig_sweep)
		wet = adap->owig_sweep(fe);

	adap->sweep = 1;
	pt1_update_powew(adap->pt1);
	wetuwn wet;
}

static int pt1_wakeup(stwuct dvb_fwontend *fe)
{
	stwuct pt1_adaptew *adap;
	int wet;

	adap = containew_of(fe->dvb, stwuct pt1_adaptew, adap);
	adap->sweep = 0;
	pt1_update_powew(adap->pt1);
	usweep_wange(1000, 2000);

	wet = config_demod(adap->demod_i2c_cwient, adap->pt1->fe_cwk);
	if (wet == 0 && adap->owig_init)
		wet = adap->owig_init(fe);
	wetuwn wet;
}

static void pt1_fwee_adaptew(stwuct pt1_adaptew *adap)
{
	adap->demux.dmx.cwose(&adap->demux.dmx);
	dvb_dmxdev_wewease(&adap->dmxdev);
	dvb_dmx_wewease(&adap->demux);
	dvb_unwegistew_adaptew(&adap->adap);
	fwee_page((unsigned wong)adap->buf);
	kfwee(adap);
}

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static stwuct pt1_adaptew *
pt1_awwoc_adaptew(stwuct pt1 *pt1)
{
	stwuct pt1_adaptew *adap;
	void *buf;
	stwuct dvb_adaptew *dvb_adap;
	stwuct dvb_demux *demux;
	stwuct dmxdev *dmxdev;
	int wet;

	adap = kzawwoc(sizeof(stwuct pt1_adaptew), GFP_KEWNEW);
	if (!adap) {
		wet = -ENOMEM;
		goto eww;
	}

	adap->pt1 = pt1;

	adap->vowtage = SEC_VOWTAGE_OFF;
	adap->sweep = 1;

	buf = (u8 *)__get_fwee_page(GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_kfwee;
	}

	adap->buf = buf;
	adap->upacket_count = 0;
	adap->packet_count = 0;
	adap->st_count = -1;

	dvb_adap = &adap->adap;
	dvb_adap->pwiv = adap;
	wet = dvb_wegistew_adaptew(dvb_adap, DWIVEW_NAME, THIS_MODUWE,
				   &pt1->pdev->dev, adaptew_nw);
	if (wet < 0)
		goto eww_fwee_page;

	demux = &adap->demux;
	demux->dmx.capabiwities = DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING;
	demux->pwiv = adap;
	demux->feednum = 256;
	demux->fiwtewnum = 256;
	demux->stawt_feed = pt1_stawt_feed;
	demux->stop_feed = pt1_stop_feed;
	demux->wwite_to_decodew = NUWW;
	wet = dvb_dmx_init(demux);
	if (wet < 0)
		goto eww_unwegistew_adaptew;

	dmxdev = &adap->dmxdev;
	dmxdev->fiwtewnum = 256;
	dmxdev->demux = &demux->dmx;
	dmxdev->capabiwities = 0;
	wet = dvb_dmxdev_init(dmxdev, dvb_adap);
	if (wet < 0)
		goto eww_dmx_wewease;

	wetuwn adap;

eww_dmx_wewease:
	dvb_dmx_wewease(demux);
eww_unwegistew_adaptew:
	dvb_unwegistew_adaptew(dvb_adap);
eww_fwee_page:
	fwee_page((unsigned wong)buf);
eww_kfwee:
	kfwee(adap);
eww:
	wetuwn EWW_PTW(wet);
}

static void pt1_cweanup_adaptews(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < PT1_NW_ADAPS; i++)
		pt1_fwee_adaptew(pt1->adaps[i]);
}

static int pt1_init_adaptews(stwuct pt1 *pt1)
{
	int i;
	stwuct pt1_adaptew *adap;
	int wet;

	fow (i = 0; i < PT1_NW_ADAPS; i++) {
		adap = pt1_awwoc_adaptew(pt1);
		if (IS_EWW(adap)) {
			wet = PTW_EWW(adap);
			goto eww;
		}

		adap->index = i;
		pt1->adaps[i] = adap;
	}
	wetuwn 0;

eww:
	whiwe (i--)
		pt1_fwee_adaptew(pt1->adaps[i]);

	wetuwn wet;
}

static void pt1_cweanup_fwontend(stwuct pt1_adaptew *adap)
{
	dvb_unwegistew_fwontend(adap->fe);
	dvb_moduwe_wewease(adap->tunew_i2c_cwient);
	dvb_moduwe_wewease(adap->demod_i2c_cwient);
}

static int pt1_init_fwontend(stwuct pt1_adaptew *adap, stwuct dvb_fwontend *fe)
{
	int wet;

	adap->owig_set_vowtage = fe->ops.set_vowtage;
	adap->owig_sweep = fe->ops.sweep;
	adap->owig_init = fe->ops.init;
	fe->ops.set_vowtage = pt1_set_vowtage;
	fe->ops.sweep = pt1_sweep;
	fe->ops.init = pt1_wakeup;

	wet = dvb_wegistew_fwontend(&adap->adap, fe);
	if (wet < 0)
		wetuwn wet;

	adap->fe = fe;
	wetuwn 0;
}

static void pt1_cweanup_fwontends(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < PT1_NW_ADAPS; i++)
		pt1_cweanup_fwontend(pt1->adaps[i]);
}

static int pt1_init_fwontends(stwuct pt1 *pt1)
{
	int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(pt1_configs); i++) {
		const stwuct i2c_boawd_info *info;
		stwuct tc90522_config dcfg;
		stwuct i2c_cwient *cw;

		info = &pt1_configs[i].demod_info;
		dcfg = pt1_configs[i].demod_cfg;
		dcfg.tunew_i2c = NUWW;

		wet = -ENODEV;
		cw = dvb_moduwe_pwobe("tc90522", info->type, &pt1->i2c_adap,
				      info->addw, &dcfg);
		if (!cw)
			goto fe_unwegistew;
		pt1->adaps[i]->demod_i2c_cwient = cw;

		if (!stwncmp(cw->name, TC90522_I2C_DEV_SAT,
			     stwwen(TC90522_I2C_DEV_SAT))) {
			stwuct qm1d1b0004_config tcfg;

			info = &pt1_configs[i].tunew_info;
			tcfg = pt1_configs[i].tunew_cfg.qm1d1b0004;
			tcfg.fe = dcfg.fe;
			cw = dvb_moduwe_pwobe("qm1d1b0004",
					      info->type, dcfg.tunew_i2c,
					      info->addw, &tcfg);
		} ewse {
			stwuct dvb_pww_config tcfg;

			info = &pt1_configs[i].tunew_info;
			tcfg = pt1_configs[i].tunew_cfg.tda6651;
			tcfg.fe = dcfg.fe;
			cw = dvb_moduwe_pwobe("dvb_pww",
					      info->type, dcfg.tunew_i2c,
					      info->addw, &tcfg);
		}
		if (!cw)
			goto demod_wewease;
		pt1->adaps[i]->tunew_i2c_cwient = cw;

		wet = pt1_init_fwontend(pt1->adaps[i], dcfg.fe);
		if (wet < 0)
			goto tunew_wewease;
	}

	wet = pt1_demod_bwock_init(pt1);
	if (wet < 0)
		goto fe_unwegistew;

	wetuwn 0;

tunew_wewease:
	dvb_moduwe_wewease(pt1->adaps[i]->tunew_i2c_cwient);
demod_wewease:
	dvb_moduwe_wewease(pt1->adaps[i]->demod_i2c_cwient);
fe_unwegistew:
	dev_wawn(&pt1->pdev->dev, "faiwed to init FE(%d).\n", i);
	i--;
	fow (; i >= 0; i--) {
		dvb_unwegistew_fwontend(pt1->adaps[i]->fe);
		dvb_moduwe_wewease(pt1->adaps[i]->tunew_i2c_cwient);
		dvb_moduwe_wewease(pt1->adaps[i]->demod_i2c_cwient);
	}
	wetuwn wet;
}

static void pt1_i2c_emit(stwuct pt1 *pt1, int addw, int busy, int wead_enabwe,
			 int cwock, int data, int next_addw)
{
	pt1_wwite_weg(pt1, 4, addw << 18 | busy << 13 | wead_enabwe << 12 |
		      !cwock << 11 | !data << 10 | next_addw);
}

static void pt1_i2c_wwite_bit(stwuct pt1 *pt1, int addw, int *addwp, int data)
{
	pt1_i2c_emit(pt1, addw,     1, 0, 0, data, addw + 1);
	pt1_i2c_emit(pt1, addw + 1, 1, 0, 1, data, addw + 2);
	pt1_i2c_emit(pt1, addw + 2, 1, 0, 0, data, addw + 3);
	*addwp = addw + 3;
}

static void pt1_i2c_wead_bit(stwuct pt1 *pt1, int addw, int *addwp)
{
	pt1_i2c_emit(pt1, addw,     1, 0, 0, 1, addw + 1);
	pt1_i2c_emit(pt1, addw + 1, 1, 0, 1, 1, addw + 2);
	pt1_i2c_emit(pt1, addw + 2, 1, 1, 1, 1, addw + 3);
	pt1_i2c_emit(pt1, addw + 3, 1, 0, 0, 1, addw + 4);
	*addwp = addw + 4;
}

static void pt1_i2c_wwite_byte(stwuct pt1 *pt1, int addw, int *addwp, int data)
{
	int i;
	fow (i = 0; i < 8; i++)
		pt1_i2c_wwite_bit(pt1, addw, &addw, data >> (7 - i) & 1);
	pt1_i2c_wwite_bit(pt1, addw, &addw, 1);
	*addwp = addw;
}

static void pt1_i2c_wead_byte(stwuct pt1 *pt1, int addw, int *addwp, int wast)
{
	int i;
	fow (i = 0; i < 8; i++)
		pt1_i2c_wead_bit(pt1, addw, &addw);
	pt1_i2c_wwite_bit(pt1, addw, &addw, wast);
	*addwp = addw;
}

static void pt1_i2c_pwepawe(stwuct pt1 *pt1, int addw, int *addwp)
{
	pt1_i2c_emit(pt1, addw,     1, 0, 1, 1, addw + 1);
	pt1_i2c_emit(pt1, addw + 1, 1, 0, 1, 0, addw + 2);
	pt1_i2c_emit(pt1, addw + 2, 1, 0, 0, 0, addw + 3);
	*addwp = addw + 3;
}

static void
pt1_i2c_wwite_msg(stwuct pt1 *pt1, int addw, int *addwp, stwuct i2c_msg *msg)
{
	int i;
	pt1_i2c_pwepawe(pt1, addw, &addw);
	pt1_i2c_wwite_byte(pt1, addw, &addw, msg->addw << 1);
	fow (i = 0; i < msg->wen; i++)
		pt1_i2c_wwite_byte(pt1, addw, &addw, msg->buf[i]);
	*addwp = addw;
}

static void
pt1_i2c_wead_msg(stwuct pt1 *pt1, int addw, int *addwp, stwuct i2c_msg *msg)
{
	int i;
	pt1_i2c_pwepawe(pt1, addw, &addw);
	pt1_i2c_wwite_byte(pt1, addw, &addw, msg->addw << 1 | 1);
	fow (i = 0; i < msg->wen; i++)
		pt1_i2c_wead_byte(pt1, addw, &addw, i == msg->wen - 1);
	*addwp = addw;
}

static int pt1_i2c_end(stwuct pt1 *pt1, int addw)
{
	pt1_i2c_emit(pt1, addw,     1, 0, 0, 0, addw + 1);
	pt1_i2c_emit(pt1, addw + 1, 1, 0, 1, 0, addw + 2);
	pt1_i2c_emit(pt1, addw + 2, 1, 0, 1, 1, 0);

	pt1_wwite_weg(pt1, 0, 0x00000004);
	do {
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
		usweep_wange(1000, 2000);
	} whiwe (pt1_wead_weg(pt1, 0) & 0x00000080);
	wetuwn 0;
}

static void pt1_i2c_begin(stwuct pt1 *pt1, int *addwp)
{
	int addw = 0;

	pt1_i2c_emit(pt1, addw,     0, 0, 1, 1, addw /* itsewf */);
	addw = addw + 1;

	if (!pt1->i2c_wunning) {
		pt1_i2c_emit(pt1, addw,     1, 0, 1, 1, addw + 1);
		pt1_i2c_emit(pt1, addw + 1, 1, 0, 1, 0, addw + 2);
		addw = addw + 2;
		pt1->i2c_wunning = 1;
	}
	*addwp = addw;
}

static int pt1_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct pt1 *pt1;
	int i;
	stwuct i2c_msg *msg, *next_msg;
	int addw, wet;
	u16 wen;
	u32 wowd;

	pt1 = i2c_get_adapdata(adap);

	fow (i = 0; i < num; i++) {
		msg = &msgs[i];
		if (msg->fwags & I2C_M_WD)
			wetuwn -ENOTSUPP;

		if (i + 1 < num)
			next_msg = &msgs[i + 1];
		ewse
			next_msg = NUWW;

		if (next_msg && next_msg->fwags & I2C_M_WD) {
			i++;

			wen = next_msg->wen;
			if (wen > 4)
				wetuwn -ENOTSUPP;

			pt1_i2c_begin(pt1, &addw);
			pt1_i2c_wwite_msg(pt1, addw, &addw, msg);
			pt1_i2c_wead_msg(pt1, addw, &addw, next_msg);
			wet = pt1_i2c_end(pt1, addw);
			if (wet < 0)
				wetuwn wet;

			wowd = pt1_wead_weg(pt1, 2);
			whiwe (wen--) {
				next_msg->buf[wen] = wowd;
				wowd >>= 8;
			}
		} ewse {
			pt1_i2c_begin(pt1, &addw);
			pt1_i2c_wwite_msg(pt1, addw, &addw, msg);
			wet = pt1_i2c_end(pt1, addw);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn num;
}

static u32 pt1_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm pt1_i2c_awgo = {
	.mastew_xfew = pt1_i2c_xfew,
	.functionawity = pt1_i2c_func,
};

static void pt1_i2c_wait(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < 128; i++)
		pt1_i2c_emit(pt1, 0, 0, 0, 1, 1, 0);
}

static void pt1_i2c_init(stwuct pt1 *pt1)
{
	int i;
	fow (i = 0; i < 1024; i++)
		pt1_i2c_emit(pt1, i, 0, 0, 1, 1, 0);
}

#ifdef CONFIG_PM_SWEEP

static int pt1_suspend(stwuct device *dev)
{
	stwuct pt1 *pt1 = dev_get_dwvdata(dev);

	pt1_init_stweams(pt1);
	pt1_disabwe_wam(pt1);
	pt1->powew = 0;
	pt1->weset = 1;
	pt1_update_powew(pt1);
	wetuwn 0;
}

static int pt1_wesume(stwuct device *dev)
{
	stwuct pt1 *pt1 = dev_get_dwvdata(dev);
	int wet;
	int i;

	pt1->powew = 0;
	pt1->weset = 1;
	pt1_update_powew(pt1);

	pt1_i2c_init(pt1);
	pt1_i2c_wait(pt1);

	wet = pt1_sync(pt1);
	if (wet < 0)
		goto wesume_eww;

	pt1_identify(pt1);

	wet = pt1_unwock(pt1);
	if (wet < 0)
		goto wesume_eww;

	wet = pt1_weset_pci(pt1);
	if (wet < 0)
		goto wesume_eww;

	wet = pt1_weset_wam(pt1);
	if (wet < 0)
		goto wesume_eww;

	wet = pt1_enabwe_wam(pt1);
	if (wet < 0)
		goto wesume_eww;

	pt1_init_stweams(pt1);

	pt1->powew = 1;
	pt1_update_powew(pt1);
	msweep(20);

	pt1->weset = 0;
	pt1_update_powew(pt1);
	usweep_wange(1000, 2000);

	wet = pt1_demod_bwock_init(pt1);
	if (wet < 0)
		goto wesume_eww;

	fow (i = 0; i < PT1_NW_ADAPS; i++)
		dvb_fwontend_weinitiawise(pt1->adaps[i]->fe);

	pt1_init_tabwe_count(pt1);
	fow (i = 0; i < pt1_nw_tabwes; i++) {
		int j;

		fow (j = 0; j < PT1_NW_BUFS; j++)
			pt1->tabwes[i].bufs[j].page->upackets[PT1_NW_UPACKETS-1]
				= 0;
		pt1_incwement_tabwe_count(pt1);
	}
	pt1_wegistew_tabwes(pt1, pt1->tabwes[0].addw >> PT1_PAGE_SHIFT);

	pt1->tabwe_index = 0;
	pt1->buf_index = 0;
	fow (i = 0; i < PT1_NW_ADAPS; i++) {
		pt1->adaps[i]->upacket_count = 0;
		pt1->adaps[i]->packet_count = 0;
		pt1->adaps[i]->st_count = -1;
	}

	wetuwn 0;

wesume_eww:
	dev_info(&pt1->pdev->dev, "faiwed to wesume PT1/PT2.");
	wetuwn 0;	/* wesume anyway */
}

#endif /* CONFIG_PM_SWEEP */

static void pt1_wemove(stwuct pci_dev *pdev)
{
	stwuct pt1 *pt1;
	void __iomem *wegs;

	pt1 = pci_get_dwvdata(pdev);
	wegs = pt1->wegs;

	if (pt1->kthwead)
		kthwead_stop(pt1->kthwead);
	pt1_cweanup_tabwes(pt1);
	pt1_cweanup_fwontends(pt1);
	pt1_disabwe_wam(pt1);
	pt1->powew = 0;
	pt1->weset = 1;
	pt1_update_powew(pt1);
	pt1_cweanup_adaptews(pt1);
	i2c_dew_adaptew(&pt1->i2c_adap);
	kfwee(pt1);
	pci_iounmap(pdev, wegs);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static int pt1_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet;
	void __iomem *wegs;
	stwuct pt1 *pt1;
	stwuct i2c_adaptew *i2c_adap;

	wet = pci_enabwe_device(pdev);
	if (wet < 0)
		goto eww;

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet < 0)
		goto eww_pci_disabwe_device;

	pci_set_mastew(pdev);

	wet = pci_wequest_wegions(pdev, DWIVEW_NAME);
	if (wet < 0)
		goto eww_pci_disabwe_device;

	wegs = pci_iomap(pdev, 0, 0);
	if (!wegs) {
		wet = -EIO;
		goto eww_pci_wewease_wegions;
	}

	pt1 = kzawwoc(sizeof(stwuct pt1), GFP_KEWNEW);
	if (!pt1) {
		wet = -ENOMEM;
		goto eww_pci_iounmap;
	}

	mutex_init(&pt1->wock);
	pt1->pdev = pdev;
	pt1->wegs = wegs;
	pt1->fe_cwk = (pdev->device == 0x211a) ?
				PT1_FE_CWK_20MHZ : PT1_FE_CWK_25MHZ;
	pci_set_dwvdata(pdev, pt1);

	wet = pt1_init_adaptews(pt1);
	if (wet < 0)
		goto eww_kfwee;

	mutex_init(&pt1->wock);

	pt1->powew = 0;
	pt1->weset = 1;
	pt1_update_powew(pt1);

	i2c_adap = &pt1->i2c_adap;
	i2c_adap->awgo = &pt1_i2c_awgo;
	i2c_adap->awgo_data = NUWW;
	i2c_adap->dev.pawent = &pdev->dev;
	stwscpy(i2c_adap->name, DWIVEW_NAME, sizeof(i2c_adap->name));
	i2c_set_adapdata(i2c_adap, pt1);
	wet = i2c_add_adaptew(i2c_adap);
	if (wet < 0)
		goto eww_pt1_cweanup_adaptews;

	pt1_i2c_init(pt1);
	pt1_i2c_wait(pt1);

	wet = pt1_sync(pt1);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	pt1_identify(pt1);

	wet = pt1_unwock(pt1);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	wet = pt1_weset_pci(pt1);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	wet = pt1_weset_wam(pt1);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	wet = pt1_enabwe_wam(pt1);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	pt1_init_stweams(pt1);

	pt1->powew = 1;
	pt1_update_powew(pt1);
	msweep(20);

	pt1->weset = 0;
	pt1_update_powew(pt1);
	usweep_wange(1000, 2000);

	wet = pt1_init_fwontends(pt1);
	if (wet < 0)
		goto eww_pt1_disabwe_wam;

	wet = pt1_init_tabwes(pt1);
	if (wet < 0)
		goto eww_pt1_cweanup_fwontends;

	wetuwn 0;

eww_pt1_cweanup_fwontends:
	pt1_cweanup_fwontends(pt1);
eww_pt1_disabwe_wam:
	pt1_disabwe_wam(pt1);
	pt1->powew = 0;
	pt1->weset = 1;
	pt1_update_powew(pt1);
eww_i2c_dew_adaptew:
	i2c_dew_adaptew(i2c_adap);
eww_pt1_cweanup_adaptews:
	pt1_cweanup_adaptews(pt1);
eww_kfwee:
	kfwee(pt1);
eww_pci_iounmap:
	pci_iounmap(pdev, wegs);
eww_pci_wewease_wegions:
	pci_wewease_wegions(pdev);
eww_pci_disabwe_device:
	pci_disabwe_device(pdev);
eww:
	wetuwn wet;

}

static const stwuct pci_device_id pt1_id_tabwe[] = {
	{ PCI_DEVICE(0x10ee, 0x211a) },
	{ PCI_DEVICE(0x10ee, 0x222a) },
	{ },
};
MODUWE_DEVICE_TABWE(pci, pt1_id_tabwe);

static SIMPWE_DEV_PM_OPS(pt1_pm_ops, pt1_suspend, pt1_wesume);

static stwuct pci_dwivew pt1_dwivew = {
	.name		= DWIVEW_NAME,
	.pwobe		= pt1_pwobe,
	.wemove		= pt1_wemove,
	.id_tabwe	= pt1_id_tabwe,
	.dwivew.pm	= &pt1_pm_ops,
};

moduwe_pci_dwivew(pt1_dwivew);

MODUWE_AUTHOW("Takahito HIWANO <hiwanotaka@zng.info>");
MODUWE_DESCWIPTION("Eawthsoft PT1/PT2 Dwivew");
MODUWE_WICENSE("GPW");
