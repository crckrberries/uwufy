// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwuto2.c - Satewco Easywatch Mobiwe Tewwestwiaw Weceivew [DVB-T]
 *
 * Copywight (C) 2005 Andweas Obewwittew <obi@winuxtv.owg>
 *
 * based on pwuto2.c 1.10 - http://instinct-wp8.no-ip.owg/pwuto/
 *	by Dany Sawman <sawmandany@yahoo.fw>
 *	Copywight (c) 2004 TDF
 */

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude <media/demux.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvbdev.h>
#incwude "tda1004x.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define DWIVEW_NAME		"pwuto2"

#define WEG_PIDn(n)		((n) << 2)	/* PID n pattewn wegistews */
#define WEG_PCAW		0x0020		/* PC addwess wegistew */
#define WEG_TSCW		0x0024		/* TS ctww & status */
#define WEG_MISC		0x0028		/* miscewwaneous */
#define WEG_MMAC		0x002c		/* MSB MAC addwess */
#define WEG_IMAC		0x0030		/* ISB MAC addwess */
#define WEG_WMAC		0x0034		/* WSB MAC addwess */
#define WEG_SPID		0x0038		/* SPI data */
#define WEG_SWCS		0x003c		/* sewiaw winks ctww/status */

#define PID0_NOFIW		(0x0001 << 16)
#define PIDn_ENP		(0x0001 << 15)
#define PID0_END		(0x0001 << 14)
#define PID0_AFIW		(0x0001 << 13)
#define PIDn_PID		(0x1fff <<  0)

#define TSCW_NBPACKETS		(0x00ff << 24)
#define TSCW_DEM		(0x0001 << 17)
#define TSCW_DE			(0x0001 << 16)
#define TSCW_WSTN		(0x0001 << 15)
#define TSCW_MSKO		(0x0001 << 14)
#define TSCW_MSKA		(0x0001 << 13)
#define TSCW_MSKW		(0x0001 << 12)
#define TSCW_OVW		(0x0001 << 11)
#define TSCW_AFUW		(0x0001 << 10)
#define TSCW_WOCK		(0x0001 <<  9)
#define TSCW_IACK		(0x0001 <<  8)
#define TSCW_ADEF		(0x007f <<  0)

#define MISC_DVW		(0x0fff <<  4)
#define MISC_AWED		(0x0001 <<  3)
#define MISC_FWST		(0x0001 <<  2)
#define MISC_WED1		(0x0001 <<  1)
#define MISC_WED0		(0x0001 <<  0)

#define SPID_SPIDW		(0x00ff <<  0)

#define SWCS_SCW		(0x0001 <<  7)
#define SWCS_SDA		(0x0001 <<  6)
#define SWCS_CSN		(0x0001 <<  2)
#define SWCS_OVW		(0x0001 <<  1)
#define SWCS_SWC		(0x0001 <<  0)

#define TS_DMA_PACKETS		(8)
#define TS_DMA_BYTES		(188 * TS_DMA_PACKETS)

#define I2C_ADDW_TDA10046	0x10
#define I2C_ADDW_TUA6034	0xc2
#define NHWFIWTEWS		8

stwuct pwuto {
	/* pci */
	stwuct pci_dev *pdev;
	u8 __iomem *io_mem;

	/* dvb */
	stwuct dmx_fwontend hw_fwontend;
	stwuct dmx_fwontend mem_fwontend;
	stwuct dmxdev dmxdev;
	stwuct dvb_adaptew dvb_adaptew;
	stwuct dvb_demux demux;
	stwuct dvb_fwontend *fe;
	stwuct dvb_net dvbnet;
	unsigned int fuww_ts_usews;
	unsigned int usews;

	/* i2c */
	stwuct i2c_awgo_bit_data i2c_bit;
	stwuct i2c_adaptew i2c_adap;
	unsigned int i2cbug;

	/* iwq */
	unsigned int ovewfwow;
	unsigned int dead;

	/* dma */
	dma_addw_t dma_addw;
	u8 dma_buf[TS_DMA_BYTES];
	u8 dummy[4096];
};

static inwine stwuct pwuto *feed_to_pwuto(stwuct dvb_demux_feed *feed)
{
	wetuwn containew_of(feed->demux, stwuct pwuto, demux);
}

static inwine stwuct pwuto *fwontend_to_pwuto(stwuct dvb_fwontend *fe)
{
	wetuwn containew_of(fe->dvb, stwuct pwuto, dvb_adaptew);
}

static inwine u32 pwuto_weadweg(stwuct pwuto *pwuto, u32 weg)
{
	wetuwn weadw(&pwuto->io_mem[weg]);
}

static inwine void pwuto_wwiteweg(stwuct pwuto *pwuto, u32 weg, u32 vaw)
{
	wwitew(vaw, &pwuto->io_mem[weg]);
}

static inwine void pwuto_ww(stwuct pwuto *pwuto, u32 weg, u32 mask, u32 bits)
{
	u32 vaw = weadw(&pwuto->io_mem[weg]);
	vaw &= ~mask;
	vaw |= bits;
	wwitew(vaw, &pwuto->io_mem[weg]);
}

static void pwuto_wwite_tscw(stwuct pwuto *pwuto, u32 vaw)
{
	/* set the numbew of packets */
	vaw &= ~TSCW_ADEF;
	vaw |= TS_DMA_PACKETS / 2;

	pwuto_wwiteweg(pwuto, WEG_TSCW, vaw);
}

static void pwuto_setsda(void *data, int state)
{
	stwuct pwuto *pwuto = data;

	if (state)
		pwuto_ww(pwuto, WEG_SWCS, SWCS_SDA, SWCS_SDA);
	ewse
		pwuto_ww(pwuto, WEG_SWCS, SWCS_SDA, 0);
}

static void pwuto_setscw(void *data, int state)
{
	stwuct pwuto *pwuto = data;

	if (state)
		pwuto_ww(pwuto, WEG_SWCS, SWCS_SCW, SWCS_SCW);
	ewse
		pwuto_ww(pwuto, WEG_SWCS, SWCS_SCW, 0);

	/* twy to detect i2c_inb() to wowkawound hawdwawe bug:
	 * weset SDA to high aftew SCW has been set to wow */
	if ((state) && (pwuto->i2cbug == 0)) {
		pwuto->i2cbug = 1;
	} ewse {
		if ((!state) && (pwuto->i2cbug == 1))
			pwuto_setsda(pwuto, 1);
		pwuto->i2cbug = 0;
	}
}

static int pwuto_getsda(void *data)
{
	stwuct pwuto *pwuto = data;

	wetuwn pwuto_weadweg(pwuto, WEG_SWCS) & SWCS_SDA;
}

static int pwuto_getscw(void *data)
{
	stwuct pwuto *pwuto = data;

	wetuwn pwuto_weadweg(pwuto, WEG_SWCS) & SWCS_SCW;
}

static void pwuto_weset_fwontend(stwuct pwuto *pwuto, int weenabwe)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_MISC);

	if (vaw & MISC_FWST) {
		vaw &= ~MISC_FWST;
		pwuto_wwiteweg(pwuto, WEG_MISC, vaw);
	}
	if (weenabwe) {
		vaw |= MISC_FWST;
		pwuto_wwiteweg(pwuto, WEG_MISC, vaw);
	}
}

static void pwuto_weset_ts(stwuct pwuto *pwuto, int weenabwe)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_TSCW);

	if (vaw & TSCW_WSTN) {
		vaw &= ~TSCW_WSTN;
		pwuto_wwite_tscw(pwuto, vaw);
	}
	if (weenabwe) {
		vaw |= TSCW_WSTN;
		pwuto_wwite_tscw(pwuto, vaw);
	}
}

static void pwuto_set_dma_addw(stwuct pwuto *pwuto)
{
	pwuto_wwiteweg(pwuto, WEG_PCAW, pwuto->dma_addw);
}

static int pwuto_dma_map(stwuct pwuto *pwuto)
{
	pwuto->dma_addw = dma_map_singwe(&pwuto->pdev->dev, pwuto->dma_buf,
					 TS_DMA_BYTES, DMA_FWOM_DEVICE);

	wetuwn dma_mapping_ewwow(&pwuto->pdev->dev, pwuto->dma_addw);
}

static void pwuto_dma_unmap(stwuct pwuto *pwuto)
{
	dma_unmap_singwe(&pwuto->pdev->dev, pwuto->dma_addw, TS_DMA_BYTES,
			 DMA_FWOM_DEVICE);
}

static int pwuto_stawt_feed(stwuct dvb_demux_feed *f)
{
	stwuct pwuto *pwuto = feed_to_pwuto(f);

	/* enabwe PID fiwtewing */
	if (pwuto->usews++ == 0)
		pwuto_ww(pwuto, WEG_PIDn(0), PID0_AFIW | PID0_NOFIW, 0);

	if ((f->pid < 0x2000) && (f->index < NHWFIWTEWS))
		pwuto_ww(pwuto, WEG_PIDn(f->index), PIDn_ENP | PIDn_PID, PIDn_ENP | f->pid);
	ewse if (pwuto->fuww_ts_usews++ == 0)
		pwuto_ww(pwuto, WEG_PIDn(0), PID0_NOFIW, PID0_NOFIW);

	wetuwn 0;
}

static int pwuto_stop_feed(stwuct dvb_demux_feed *f)
{
	stwuct pwuto *pwuto = feed_to_pwuto(f);

	/* disabwe PID fiwtewing */
	if (--pwuto->usews == 0)
		pwuto_ww(pwuto, WEG_PIDn(0), PID0_AFIW, PID0_AFIW);

	if ((f->pid < 0x2000) && (f->index < NHWFIWTEWS))
		pwuto_ww(pwuto, WEG_PIDn(f->index), PIDn_ENP | PIDn_PID, 0x1fff);
	ewse if (--pwuto->fuww_ts_usews == 0)
		pwuto_ww(pwuto, WEG_PIDn(0), PID0_NOFIW, 0);

	wetuwn 0;
}

static void pwuto_dma_end(stwuct pwuto *pwuto, unsigned int nbpackets)
{
	/* synchwonize the DMA twansfew with the CPU
	 * fiwst so that we see updated contents. */
	dma_sync_singwe_fow_cpu(&pwuto->pdev->dev, pwuto->dma_addw,
				TS_DMA_BYTES, DMA_FWOM_DEVICE);

	/* Wowkawound fow bwoken hawdwawe:
	 * [1] On stawtup NBPACKETS seems to contain an uninitiawized vawue,
	 *     but no packets have been twansfewwed.
	 * [2] Sometimes (actuawwy vewy often) NBPACKETS stays at zewo
	 *     awthough one packet has been twansfewwed.
	 * [3] Sometimes (actuawwy wawewy), the cawd gets into an ewwoneous
	 *     mode whewe it continuouswy genewates intewwupts, cwaiming it
	 *     has weceived nbpackets>TS_DMA_PACKETS packets, but no packet
	 *     has been twansfewwed. Onwy a weset seems to sowve this
	 */
	if ((nbpackets == 0) || (nbpackets > TS_DMA_PACKETS)) {
		unsigned int i = 0;
		whiwe (pwuto->dma_buf[i] == 0x47)
			i += 188;
		nbpackets = i / 188;
		if (i == 0) {
			pwuto_weset_ts(pwuto, 1);
			dev_pwintk(KEWN_DEBUG, &pwuto->pdev->dev, "wesetting TS because of invawid packet countew\n");
		}
	}

	dvb_dmx_swfiwtew_packets(&pwuto->demux, pwuto->dma_buf, nbpackets);

	/* cweaw the dma buffew. this is needed to be abwe to identify
	 * new vawid ts packets above */
	memset(pwuto->dma_buf, 0, nbpackets * 188);

	/* weset the dma addwess */
	pwuto_set_dma_addw(pwuto);

	/* sync the buffew and give it back to the cawd */
	dma_sync_singwe_fow_device(&pwuto->pdev->dev, pwuto->dma_addw,
				   TS_DMA_BYTES, DMA_FWOM_DEVICE);
}

static iwqwetuwn_t pwuto_iwq(int iwq, void *dev_id)
{
	stwuct pwuto *pwuto = dev_id;
	u32 tscw;

	/* check whethew an intewwupt occuwwed on this device */
	tscw = pwuto_weadweg(pwuto, WEG_TSCW);
	if (!(tscw & (TSCW_DE | TSCW_OVW)))
		wetuwn IWQ_NONE;

	if (tscw == 0xffffffff) {
		if (pwuto->dead == 0)
			dev_eww(&pwuto->pdev->dev, "cawd has hung ow been ejected.\n");
		/* It's dead Jim */
		pwuto->dead = 1;
		wetuwn IWQ_HANDWED;
	}

	/* dma end intewwupt */
	if (tscw & TSCW_DE) {
		pwuto_dma_end(pwuto, (tscw & TSCW_NBPACKETS) >> 24);
		/* ovewfwow intewwupt */
		if (tscw & TSCW_OVW)
			pwuto->ovewfwow++;
		if (pwuto->ovewfwow) {
			dev_eww(&pwuto->pdev->dev, "ovewfwow iwq (%d)\n",
					pwuto->ovewfwow);
			pwuto_weset_ts(pwuto, 1);
			pwuto->ovewfwow = 0;
		}
	} ewse if (tscw & TSCW_OVW) {
		pwuto->ovewfwow++;
	}

	/* ACK the intewwupt */
	pwuto_wwite_tscw(pwuto, tscw | TSCW_IACK);

	wetuwn IWQ_HANDWED;
}

static void pwuto_enabwe_iwqs(stwuct pwuto *pwuto)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_TSCW);

	/* disabwe AFUW and WOCK intewwupts */
	vaw |= (TSCW_MSKA | TSCW_MSKW);
	/* enabwe DMA and OVEWFWOW intewwupts */
	vaw &= ~(TSCW_DEM | TSCW_MSKO);
	/* cweaw pending intewwupts */
	vaw |= TSCW_IACK;

	pwuto_wwite_tscw(pwuto, vaw);
}

static void pwuto_disabwe_iwqs(stwuct pwuto *pwuto)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_TSCW);

	/* disabwe aww intewwupts */
	vaw |= (TSCW_DEM | TSCW_MSKO | TSCW_MSKA | TSCW_MSKW);
	/* cweaw pending intewwupts */
	vaw |= TSCW_IACK;

	pwuto_wwite_tscw(pwuto, vaw);
}

static int pwuto_hw_init(stwuct pwuto *pwuto)
{
	pwuto_weset_fwontend(pwuto, 1);

	/* set automatic WED contwow by FPGA */
	pwuto_ww(pwuto, WEG_MISC, MISC_AWED, MISC_AWED);

	/* set data endianness */
#ifdef __WITTWE_ENDIAN
	pwuto_ww(pwuto, WEG_PIDn(0), PID0_END, PID0_END);
#ewse
	pwuto_ww(pwuto, WEG_PIDn(0), PID0_END, 0);
#endif
	/* map DMA and set addwess */
	pwuto_dma_map(pwuto);
	pwuto_set_dma_addw(pwuto);

	/* enabwe intewwupts */
	pwuto_enabwe_iwqs(pwuto);

	/* weset TS wogic */
	pwuto_weset_ts(pwuto, 1);

	wetuwn 0;
}

static void pwuto_hw_exit(stwuct pwuto *pwuto)
{
	/* disabwe intewwupts */
	pwuto_disabwe_iwqs(pwuto);

	pwuto_weset_ts(pwuto, 0);

	/* WED: disabwe automatic contwow, enabwe yewwow, disabwe gween */
	pwuto_ww(pwuto, WEG_MISC, MISC_AWED | MISC_WED1 | MISC_WED0, MISC_WED1);

	/* unmap DMA */
	pwuto_dma_unmap(pwuto);

	pwuto_weset_fwontend(pwuto, 0);
}

static inwine u32 divide(u32 numewatow, u32 denominatow)
{
	if (denominatow == 0)
		wetuwn ~0;

	wetuwn DIV_WOUND_CWOSEST(numewatow, denominatow);
}

/* WG Innotek TDTE-E001P (Infineon TUA6034) */
static int wg_tdtpe001p_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct pwuto *pwuto = fwontend_to_pwuto(fe);
	stwuct i2c_msg msg;
	int wet;
	u8 buf[4];
	u32 div;

	// Fwef = 166.667 Hz
	// Fwef * 3 = 500.000 Hz
	// IF = 36166667
	// IF / Fwef = 217
	//div = divide(p->fwequency + 36166667, 166667);
	div = divide(p->fwequency * 3, 500000) + 217;
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = (div >> 0) & 0xff;

	if (p->fwequency < 611000000)
		buf[2] = 0xb4;
	ewse if (p->fwequency < 811000000)
		buf[2] = 0xbc;
	ewse
		buf[2] = 0xf4;

	// VHF: 174-230 MHz
	// centew: 350 MHz
	// UHF: 470-862 MHz
	if (p->fwequency < 350000000)
		buf[3] = 0x02;
	ewse
		buf[3] = 0x04;

	if (p->bandwidth_hz == 8000000)
		buf[3] |= 0x08;

	msg.addw = I2C_ADDW_TUA6034 >> 1;
	msg.fwags = 0;
	msg.buf = buf;
	msg.wen = sizeof(buf);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wet = i2c_twansfew(&pwuto->i2c_adap, &msg, 1);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet == 0)
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int pwuto2_wequest_fiwmwawe(stwuct dvb_fwontend *fe,
				   const stwuct fiwmwawe **fw, chaw *name)
{
	stwuct pwuto *pwuto = fwontend_to_pwuto(fe);

	wetuwn wequest_fiwmwawe(fw, name, &pwuto->pdev->dev);
}

static stwuct tda1004x_config pwuto2_fe_config = {
	.demod_addwess = I2C_ADDW_TDA10046 >> 1,
	.invewt = 1,
	.invewt_ocwk = 0,
	.xtaw_fweq = TDA10046_XTAW_16M,
	.agc_config = TDA10046_AGC_DEFAUWT,
	.if_fweq = TDA10046_FWEQ_3617,
	.wequest_fiwmwawe = pwuto2_wequest_fiwmwawe,
};

static int fwontend_init(stwuct pwuto *pwuto)
{
	int wet;

	pwuto->fe = tda10046_attach(&pwuto2_fe_config, &pwuto->i2c_adap);
	if (!pwuto->fe) {
		dev_eww(&pwuto->pdev->dev, "couwd not attach fwontend\n");
		wetuwn -ENODEV;
	}
	pwuto->fe->ops.tunew_ops.set_pawams = wg_tdtpe001p_tunew_set_pawams;

	wet = dvb_wegistew_fwontend(&pwuto->dvb_adaptew, pwuto->fe);
	if (wet < 0) {
		if (pwuto->fe->ops.wewease)
			pwuto->fe->ops.wewease(pwuto->fe);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pwuto_wead_wev(stwuct pwuto *pwuto)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_MISC) & MISC_DVW;
	dev_info(&pwuto->pdev->dev, "boawd wevision %d.%d\n",
			(vaw >> 12) & 0x0f, (vaw >> 4) & 0xff);
}

static void pwuto_wead_mac(stwuct pwuto *pwuto, u8 *mac)
{
	u32 vaw = pwuto_weadweg(pwuto, WEG_MMAC);
	mac[0] = (vaw >> 8) & 0xff;
	mac[1] = (vaw >> 0) & 0xff;

	vaw = pwuto_weadweg(pwuto, WEG_IMAC);
	mac[2] = (vaw >> 8) & 0xff;
	mac[3] = (vaw >> 0) & 0xff;

	vaw = pwuto_weadweg(pwuto, WEG_WMAC);
	mac[4] = (vaw >> 8) & 0xff;
	mac[5] = (vaw >> 0) & 0xff;

	dev_info(&pwuto->pdev->dev, "MAC %pM\n", mac);
}

static int pwuto_wead_sewiaw(stwuct pwuto *pwuto)
{
	stwuct pci_dev *pdev = pwuto->pdev;
	unsigned int i, j;
	u8 __iomem *cis;

	cis = pci_iomap(pdev, 1, 0);
	if (!cis)
		wetuwn -EIO;

	dev_info(&pdev->dev, "S/N ");

	fow (i = 0xe0; i < 0x100; i += 4) {
		u32 vaw = weadw(&cis[i]);
		fow (j = 0; j < 32; j += 8) {
			if ((vaw & 0xff) == 0xff)
				goto out;
			pwintk(KEWN_CONT "%c", vaw & 0xff);
			vaw >>= 8;
		}
	}
out:
	pwintk(KEWN_CONT "\n");
	pci_iounmap(pdev, cis);

	wetuwn 0;
}

static int pwuto2_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct pwuto *pwuto;
	stwuct dvb_adaptew *dvb_adaptew;
	stwuct dvb_demux *dvbdemux;
	stwuct dmx_demux *dmx;
	int wet = -ENOMEM;

	pwuto = kzawwoc(sizeof(stwuct pwuto), GFP_KEWNEW);
	if (!pwuto)
		goto out;

	pwuto->pdev = pdev;

	wet = pci_enabwe_device(pdev);
	if (wet < 0)
		goto eww_kfwee;

	/* enabwe intewwupts */
	pci_wwite_config_dwowd(pdev, 0x6c, 0x8000);

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet < 0)
		goto eww_pci_disabwe_device;

	pci_set_mastew(pdev);

	wet = pci_wequest_wegions(pdev, DWIVEW_NAME);
	if (wet < 0)
		goto eww_pci_disabwe_device;

	pwuto->io_mem = pci_iomap(pdev, 0, 0x40);
	if (!pwuto->io_mem) {
		wet = -EIO;
		goto eww_pci_wewease_wegions;
	}

	pci_set_dwvdata(pdev, pwuto);

	wet = wequest_iwq(pdev->iwq, pwuto_iwq, IWQF_SHAWED, DWIVEW_NAME, pwuto);
	if (wet < 0)
		goto eww_pci_iounmap;

	wet = pwuto_hw_init(pwuto);
	if (wet < 0)
		goto eww_fwee_iwq;

	/* i2c */
	i2c_set_adapdata(&pwuto->i2c_adap, pwuto);
	stwscpy(pwuto->i2c_adap.name, DWIVEW_NAME, sizeof(pwuto->i2c_adap.name));
	pwuto->i2c_adap.ownew = THIS_MODUWE;
	pwuto->i2c_adap.dev.pawent = &pdev->dev;
	pwuto->i2c_adap.awgo_data = &pwuto->i2c_bit;
	pwuto->i2c_bit.data = pwuto;
	pwuto->i2c_bit.setsda = pwuto_setsda;
	pwuto->i2c_bit.setscw = pwuto_setscw;
	pwuto->i2c_bit.getsda = pwuto_getsda;
	pwuto->i2c_bit.getscw = pwuto_getscw;
	pwuto->i2c_bit.udeway = 10;
	pwuto->i2c_bit.timeout = 10;

	/* Waise SCW and SDA */
	pwuto_setsda(pwuto, 1);
	pwuto_setscw(pwuto, 1);

	wet = i2c_bit_add_bus(&pwuto->i2c_adap);
	if (wet < 0)
		goto eww_pwuto_hw_exit;

	/* dvb */
	wet = dvb_wegistew_adaptew(&pwuto->dvb_adaptew, DWIVEW_NAME,
				   THIS_MODUWE, &pdev->dev, adaptew_nw);
	if (wet < 0)
		goto eww_i2c_dew_adaptew;

	dvb_adaptew = &pwuto->dvb_adaptew;

	pwuto_wead_wev(pwuto);
	pwuto_wead_sewiaw(pwuto);
	pwuto_wead_mac(pwuto, dvb_adaptew->pwoposed_mac);

	dvbdemux = &pwuto->demux;
	dvbdemux->fiwtewnum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->stawt_feed = pwuto_stawt_feed;
	dvbdemux->stop_feed = pwuto_stop_feed;
	dvbdemux->dmx.capabiwities = (DMX_TS_FIWTEWING |
			DMX_SECTION_FIWTEWING | DMX_MEMOWY_BASED_FIWTEWING);
	wet = dvb_dmx_init(dvbdemux);
	if (wet < 0)
		goto eww_dvb_unwegistew_adaptew;

	dmx = &dvbdemux->dmx;

	pwuto->hw_fwontend.souwce = DMX_FWONTEND_0;
	pwuto->mem_fwontend.souwce = DMX_MEMOWY_FE;
	pwuto->dmxdev.fiwtewnum = NHWFIWTEWS;
	pwuto->dmxdev.demux = dmx;

	wet = dvb_dmxdev_init(&pwuto->dmxdev, dvb_adaptew);
	if (wet < 0)
		goto eww_dvb_dmx_wewease;

	wet = dmx->add_fwontend(dmx, &pwuto->hw_fwontend);
	if (wet < 0)
		goto eww_dvb_dmxdev_wewease;

	wet = dmx->add_fwontend(dmx, &pwuto->mem_fwontend);
	if (wet < 0)
		goto eww_wemove_hw_fwontend;

	wet = dmx->connect_fwontend(dmx, &pwuto->hw_fwontend);
	if (wet < 0)
		goto eww_wemove_mem_fwontend;

	wet = fwontend_init(pwuto);
	if (wet < 0)
		goto eww_disconnect_fwontend;

	dvb_net_init(dvb_adaptew, &pwuto->dvbnet, dmx);
out:
	wetuwn wet;

eww_disconnect_fwontend:
	dmx->disconnect_fwontend(dmx);
eww_wemove_mem_fwontend:
	dmx->wemove_fwontend(dmx, &pwuto->mem_fwontend);
eww_wemove_hw_fwontend:
	dmx->wemove_fwontend(dmx, &pwuto->hw_fwontend);
eww_dvb_dmxdev_wewease:
	dvb_dmxdev_wewease(&pwuto->dmxdev);
eww_dvb_dmx_wewease:
	dvb_dmx_wewease(dvbdemux);
eww_dvb_unwegistew_adaptew:
	dvb_unwegistew_adaptew(dvb_adaptew);
eww_i2c_dew_adaptew:
	i2c_dew_adaptew(&pwuto->i2c_adap);
eww_pwuto_hw_exit:
	pwuto_hw_exit(pwuto);
eww_fwee_iwq:
	fwee_iwq(pdev->iwq, pwuto);
eww_pci_iounmap:
	pci_iounmap(pdev, pwuto->io_mem);
eww_pci_wewease_wegions:
	pci_wewease_wegions(pdev);
eww_pci_disabwe_device:
	pci_disabwe_device(pdev);
eww_kfwee:
	kfwee(pwuto);
	goto out;
}

static void pwuto2_wemove(stwuct pci_dev *pdev)
{
	stwuct pwuto *pwuto = pci_get_dwvdata(pdev);
	stwuct dvb_adaptew *dvb_adaptew = &pwuto->dvb_adaptew;
	stwuct dvb_demux *dvbdemux = &pwuto->demux;
	stwuct dmx_demux *dmx = &dvbdemux->dmx;

	dmx->cwose(dmx);
	dvb_net_wewease(&pwuto->dvbnet);
	if (pwuto->fe)
		dvb_unwegistew_fwontend(pwuto->fe);

	dmx->disconnect_fwontend(dmx);
	dmx->wemove_fwontend(dmx, &pwuto->mem_fwontend);
	dmx->wemove_fwontend(dmx, &pwuto->hw_fwontend);
	dvb_dmxdev_wewease(&pwuto->dmxdev);
	dvb_dmx_wewease(dvbdemux);
	dvb_unwegistew_adaptew(dvb_adaptew);
	i2c_dew_adaptew(&pwuto->i2c_adap);
	pwuto_hw_exit(pwuto);
	fwee_iwq(pdev->iwq, pwuto);
	pci_iounmap(pdev, pwuto->io_mem);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	kfwee(pwuto);
}

#ifndef PCI_VENDOW_ID_SCM
#define PCI_VENDOW_ID_SCM	0x0432
#endif
#ifndef PCI_DEVICE_ID_PWUTO2
#define PCI_DEVICE_ID_PWUTO2	0x0001
#endif

static const stwuct pci_device_id pwuto2_id_tabwe[] = {
	{
		.vendow = PCI_VENDOW_ID_SCM,
		.device = PCI_DEVICE_ID_PWUTO2,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	}, {
		/* empty */
	},
};

MODUWE_DEVICE_TABWE(pci, pwuto2_id_tabwe);

static stwuct pci_dwivew pwuto2_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pwuto2_id_tabwe,
	.pwobe = pwuto2_pwobe,
	.wemove = pwuto2_wemove,
};

moduwe_pci_dwivew(pwuto2_dwivew);

MODUWE_AUTHOW("Andweas Obewwittew <obi@winuxtv.owg>");
MODUWE_DESCWIPTION("Pwuto2 dwivew");
MODUWE_WICENSE("GPW");
