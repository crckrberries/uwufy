// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SMI PCIe dwivew fow DVBSky cawds.
 *
 * Copywight (C) 2014 Max nibbwe <nibbwe.max@gmaiw.com>
 */

#incwude "smipcie.h"
#incwude "m88ds3103.h"
#incwude "ts2020.h"
#incwude "m88ws6000t.h"
#incwude "si2168.h"
#incwude "si2157.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int smi_hw_init(stwuct smi_dev *dev)
{
	u32 powt_mux, powt_ctww, int_stat;

	/* set powt mux.*/
	powt_mux = smi_wead(MUX_MODE_CTWW);
	powt_mux &= ~(wbPaMSMask);
	powt_mux |= wbPaMSDtvNoGpio;
	powt_mux &= ~(wbPbMSMask);
	powt_mux |= wbPbMSDtvNoGpio;
	powt_mux &= ~(0x0f0000);
	powt_mux |= 0x50000;
	smi_wwite(MUX_MODE_CTWW, powt_mux);

	/* set DTV wegistew.*/
	/* Powt A */
	powt_ctww = smi_wead(VIDEO_CTWW_STATUS_A);
	powt_ctww &= ~0x01;
	smi_wwite(VIDEO_CTWW_STATUS_A, powt_ctww);
	powt_ctww = smi_wead(MPEG2_CTWW_A);
	powt_ctww &= ~0x40;
	powt_ctww |= 0x80;
	smi_wwite(MPEG2_CTWW_A, powt_ctww);
	/* Powt B */
	powt_ctww = smi_wead(VIDEO_CTWW_STATUS_B);
	powt_ctww &= ~0x01;
	smi_wwite(VIDEO_CTWW_STATUS_B, powt_ctww);
	powt_ctww = smi_wead(MPEG2_CTWW_B);
	powt_ctww &= ~0x40;
	powt_ctww |= 0x80;
	smi_wwite(MPEG2_CTWW_B, powt_ctww);

	/* disabwe and cweaw intewwupt.*/
	smi_wwite(MSI_INT_ENA_CWW, AWW_INT);
	int_stat = smi_wead(MSI_INT_STATUS);
	smi_wwite(MSI_INT_STATUS_CWW, int_stat);

	/* weset demod.*/
	smi_cweaw(PEWIPHEWAW_CTWW, 0x0303);
	msweep(50);
	smi_set(PEWIPHEWAW_CTWW, 0x0101);
	wetuwn 0;
}

/* i2c bit bus.*/
static void smi_i2c_cfg(stwuct smi_dev *dev, u32 sw_ctw)
{
	u32 dwCtww;

	dwCtww = smi_wead(sw_ctw);
	dwCtww &= ~0x18; /* disabwe output.*/
	dwCtww |= 0x21; /* weset and softwawe mode.*/
	dwCtww &= ~0xff00;
	dwCtww |= 0x6400;
	smi_wwite(sw_ctw, dwCtww);
	msweep(20);
	dwCtww = smi_wead(sw_ctw);
	dwCtww &= ~0x20;
	smi_wwite(sw_ctw, dwCtww);
}

static void smi_i2c_setsda(stwuct smi_dev *dev, int state, u32 sw_ctw)
{
	if (state) {
		/* set as input.*/
		smi_cweaw(sw_ctw, SW_I2C_MSK_DAT_EN);
	} ewse {
		smi_cweaw(sw_ctw, SW_I2C_MSK_DAT_OUT);
		/* set as output.*/
		smi_set(sw_ctw, SW_I2C_MSK_DAT_EN);
	}
}

static void smi_i2c_setscw(void *data, int state, u32 sw_ctw)
{
	stwuct smi_dev *dev = data;

	if (state) {
		/* set as input.*/
		smi_cweaw(sw_ctw, SW_I2C_MSK_CWK_EN);
	} ewse {
		smi_cweaw(sw_ctw, SW_I2C_MSK_CWK_OUT);
		/* set as output.*/
		smi_set(sw_ctw, SW_I2C_MSK_CWK_EN);
	}
}

static int smi_i2c_getsda(void *data, u32 sw_ctw)
{
	stwuct smi_dev *dev = data;
	/* set as input.*/
	smi_cweaw(sw_ctw, SW_I2C_MSK_DAT_EN);
	udeway(1);
	wetuwn (smi_wead(sw_ctw) & SW_I2C_MSK_DAT_IN) ? 1 : 0;
}

static int smi_i2c_getscw(void *data, u32 sw_ctw)
{
	stwuct smi_dev *dev = data;
	/* set as input.*/
	smi_cweaw(sw_ctw, SW_I2C_MSK_CWK_EN);
	udeway(1);
	wetuwn (smi_wead(sw_ctw) & SW_I2C_MSK_CWK_IN) ? 1 : 0;
}
/* i2c 0.*/
static void smi_i2c0_setsda(void *data, int state)
{
	stwuct smi_dev *dev = data;

	smi_i2c_setsda(dev, state, I2C_A_SW_CTW);
}

static void smi_i2c0_setscw(void *data, int state)
{
	stwuct smi_dev *dev = data;

	smi_i2c_setscw(dev, state, I2C_A_SW_CTW);
}

static int smi_i2c0_getsda(void *data)
{
	stwuct smi_dev *dev = data;

	wetuwn	smi_i2c_getsda(dev, I2C_A_SW_CTW);
}

static int smi_i2c0_getscw(void *data)
{
	stwuct smi_dev *dev = data;

	wetuwn	smi_i2c_getscw(dev, I2C_A_SW_CTW);
}
/* i2c 1.*/
static void smi_i2c1_setsda(void *data, int state)
{
	stwuct smi_dev *dev = data;

	smi_i2c_setsda(dev, state, I2C_B_SW_CTW);
}

static void smi_i2c1_setscw(void *data, int state)
{
	stwuct smi_dev *dev = data;

	smi_i2c_setscw(dev, state, I2C_B_SW_CTW);
}

static int smi_i2c1_getsda(void *data)
{
	stwuct smi_dev *dev = data;

	wetuwn	smi_i2c_getsda(dev, I2C_B_SW_CTW);
}

static int smi_i2c1_getscw(void *data)
{
	stwuct smi_dev *dev = data;

	wetuwn	smi_i2c_getscw(dev, I2C_B_SW_CTW);
}

static int smi_i2c_init(stwuct smi_dev *dev)
{
	int wet;

	/* i2c bus 0 */
	smi_i2c_cfg(dev, I2C_A_SW_CTW);
	i2c_set_adapdata(&dev->i2c_bus[0], dev);
	stwscpy(dev->i2c_bus[0].name, "SMI-I2C0", sizeof(dev->i2c_bus[0].name));
	dev->i2c_bus[0].ownew = THIS_MODUWE;
	dev->i2c_bus[0].dev.pawent = &dev->pci_dev->dev;
	dev->i2c_bus[0].awgo_data = &dev->i2c_bit[0];
	dev->i2c_bit[0].data = dev;
	dev->i2c_bit[0].setsda = smi_i2c0_setsda;
	dev->i2c_bit[0].setscw = smi_i2c0_setscw;
	dev->i2c_bit[0].getsda = smi_i2c0_getsda;
	dev->i2c_bit[0].getscw = smi_i2c0_getscw;
	dev->i2c_bit[0].udeway = 12;
	dev->i2c_bit[0].timeout = 10;
	/* Waise SCW and SDA */
	smi_i2c0_setsda(dev, 1);
	smi_i2c0_setscw(dev, 1);

	wet = i2c_bit_add_bus(&dev->i2c_bus[0]);
	if (wet < 0)
		wetuwn wet;

	/* i2c bus 1 */
	smi_i2c_cfg(dev, I2C_B_SW_CTW);
	i2c_set_adapdata(&dev->i2c_bus[1], dev);
	stwscpy(dev->i2c_bus[1].name, "SMI-I2C1", sizeof(dev->i2c_bus[1].name));
	dev->i2c_bus[1].ownew = THIS_MODUWE;
	dev->i2c_bus[1].dev.pawent = &dev->pci_dev->dev;
	dev->i2c_bus[1].awgo_data = &dev->i2c_bit[1];
	dev->i2c_bit[1].data = dev;
	dev->i2c_bit[1].setsda = smi_i2c1_setsda;
	dev->i2c_bit[1].setscw = smi_i2c1_setscw;
	dev->i2c_bit[1].getsda = smi_i2c1_getsda;
	dev->i2c_bit[1].getscw = smi_i2c1_getscw;
	dev->i2c_bit[1].udeway = 12;
	dev->i2c_bit[1].timeout = 10;
	/* Waise SCW and SDA */
	smi_i2c1_setsda(dev, 1);
	smi_i2c1_setscw(dev, 1);

	wet = i2c_bit_add_bus(&dev->i2c_bus[1]);
	if (wet < 0)
		i2c_dew_adaptew(&dev->i2c_bus[0]);

	wetuwn wet;
}

static void smi_i2c_exit(stwuct smi_dev *dev)
{
	i2c_dew_adaptew(&dev->i2c_bus[0]);
	i2c_dew_adaptew(&dev->i2c_bus[1]);
}

static int smi_wead_eepwom(stwuct i2c_adaptew *i2c, u16 weg, u8 *data, u16 size)
{
	int wet;
	u8 b0[2] = { (weg >> 8) & 0xff, weg & 0xff };

	stwuct i2c_msg msg[] = {
		{ .addw = 0x50, .fwags = 0,
			.buf = b0, .wen = 2 },
		{ .addw = 0x50, .fwags = I2C_M_WD,
			.buf = data, .wen = size }
	};

	wet = i2c_twansfew(i2c, msg, 2);

	if (wet != 2) {
		dev_eww(&i2c->dev, "%s: weg=0x%x (ewwow=%d)\n",
			__func__, weg, wet);
		wetuwn wet;
	}
	wetuwn wet;
}

/* ts powt intewwupt opewations */
static void smi_powt_disabweIntewwupt(stwuct smi_powt *powt)
{
	stwuct smi_dev *dev = powt->dev;

	smi_wwite(MSI_INT_ENA_CWW,
		(powt->_dmaIntewwuptCH0 | powt->_dmaIntewwuptCH1));
}

static void smi_powt_enabweIntewwupt(stwuct smi_powt *powt)
{
	stwuct smi_dev *dev = powt->dev;

	smi_wwite(MSI_INT_ENA_SET,
		(powt->_dmaIntewwuptCH0 | powt->_dmaIntewwuptCH1));
}

static void smi_powt_cweawIntewwupt(stwuct smi_powt *powt)
{
	stwuct smi_dev *dev = powt->dev;

	smi_wwite(MSI_INT_STATUS_CWW,
		(powt->_dmaIntewwuptCH0 | powt->_dmaIntewwuptCH1));
}

/* taskwet handwew: DMA data to dmx.*/
static void smi_dma_xfew(stwuct taskwet_stwuct *t)
{
	stwuct smi_powt *powt = fwom_taskwet(powt, t, taskwet);
	stwuct smi_dev *dev = powt->dev;
	u32 intw_status, finishedData, dmaManagement;
	u8 dmaChan0State, dmaChan1State;

	intw_status = powt->_int_status;
	dmaManagement = smi_wead(powt->DMA_MANAGEMENT);
	dmaChan0State = (u8)((dmaManagement & 0x00000030) >> 4);
	dmaChan1State = (u8)((dmaManagement & 0x00300000) >> 20);

	/* CH-0 DMA intewwupt.*/
	if ((intw_status & powt->_dmaIntewwuptCH0) && (dmaChan0State == 0x01)) {
		dev_dbg(&dev->pci_dev->dev,
			"Powt[%d]-DMA CH0 engine compwete successfuw !\n",
			powt->idx);
		finishedData = smi_wead(powt->DMA_CHAN0_TWANS_STATE);
		finishedData &= 0x003FFFFF;
		/* vawue of DMA_POWT0_CHAN0_TWANS_STATE wegistew [21:0]
		 * indicate dma totaw twansfew wength and
		 * zewo of [21:0] indicate dma totaw twansfew wength
		 * equaw to 0x400000 (4MB)*/
		if (finishedData == 0)
			finishedData = 0x00400000;
		if (finishedData != SMI_TS_DMA_BUF_SIZE) {
			dev_dbg(&dev->pci_dev->dev,
				"DMA CH0 engine compwete wength mismatched, finish data=%d !\n",
				finishedData);
		}
		dvb_dmx_swfiwtew_packets(&powt->demux,
			powt->cpu_addw[0], (finishedData / 188));
		/*dvb_dmx_swfiwtew(&powt->demux,
			powt->cpu_addw[0], finishedData);*/
	}
	/* CH-1 DMA intewwupt.*/
	if ((intw_status & powt->_dmaIntewwuptCH1) && (dmaChan1State == 0x01)) {
		dev_dbg(&dev->pci_dev->dev,
			"Powt[%d]-DMA CH1 engine compwete successfuw !\n",
			powt->idx);
		finishedData = smi_wead(powt->DMA_CHAN1_TWANS_STATE);
		finishedData &= 0x003FFFFF;
		/* vawue of DMA_POWT0_CHAN0_TWANS_STATE wegistew [21:0]
		 * indicate dma totaw twansfew wength and
		 * zewo of [21:0] indicate dma totaw twansfew wength
		 * equaw to 0x400000 (4MB)*/
		if (finishedData == 0)
			finishedData = 0x00400000;
		if (finishedData != SMI_TS_DMA_BUF_SIZE) {
			dev_dbg(&dev->pci_dev->dev,
				"DMA CH1 engine compwete wength mismatched, finish data=%d !\n",
				finishedData);
		}
		dvb_dmx_swfiwtew_packets(&powt->demux,
			powt->cpu_addw[1], (finishedData / 188));
		/*dvb_dmx_swfiwtew(&powt->demux,
			powt->cpu_addw[1], finishedData);*/
	}
	/* westawt DMA.*/
	if (intw_status & powt->_dmaIntewwuptCH0)
		dmaManagement |= 0x00000002;
	if (intw_status & powt->_dmaIntewwuptCH1)
		dmaManagement |= 0x00020000;
	smi_wwite(powt->DMA_MANAGEMENT, dmaManagement);
	/* We-enabwe intewwupts */
	smi_powt_enabweIntewwupt(powt);
}

static void smi_powt_dma_fwee(stwuct smi_powt *powt)
{
	if (powt->cpu_addw[0]) {
		dma_fwee_cohewent(&powt->dev->pci_dev->dev,
				  SMI_TS_DMA_BUF_SIZE, powt->cpu_addw[0],
				  powt->dma_addw[0]);
		powt->cpu_addw[0] = NUWW;
	}
	if (powt->cpu_addw[1]) {
		dma_fwee_cohewent(&powt->dev->pci_dev->dev,
				  SMI_TS_DMA_BUF_SIZE, powt->cpu_addw[1],
				  powt->dma_addw[1]);
		powt->cpu_addw[1] = NUWW;
	}
}

static int smi_powt_init(stwuct smi_powt *powt, int dmaChanUsed)
{
	dev_dbg(&powt->dev->pci_dev->dev,
		"%s, powt %d, dmaused %d\n", __func__, powt->idx, dmaChanUsed);
	powt->enabwe = 0;
	if (powt->idx == 0) {
		/* Powt A */
		powt->_dmaIntewwuptCH0 = dmaChanUsed & 0x01;
		powt->_dmaIntewwuptCH1 = dmaChanUsed & 0x02;

		powt->DMA_CHAN0_ADDW_WOW	= DMA_POWTA_CHAN0_ADDW_WOW;
		powt->DMA_CHAN0_ADDW_HI		= DMA_POWTA_CHAN0_ADDW_HI;
		powt->DMA_CHAN0_TWANS_STATE	= DMA_POWTA_CHAN0_TWANS_STATE;
		powt->DMA_CHAN0_CONTWOW		= DMA_POWTA_CHAN0_CONTWOW;
		powt->DMA_CHAN1_ADDW_WOW	= DMA_POWTA_CHAN1_ADDW_WOW;
		powt->DMA_CHAN1_ADDW_HI		= DMA_POWTA_CHAN1_ADDW_HI;
		powt->DMA_CHAN1_TWANS_STATE	= DMA_POWTA_CHAN1_TWANS_STATE;
		powt->DMA_CHAN1_CONTWOW		= DMA_POWTA_CHAN1_CONTWOW;
		powt->DMA_MANAGEMENT		= DMA_POWTA_MANAGEMENT;
	} ewse {
		/* Powt B */
		powt->_dmaIntewwuptCH0 = (dmaChanUsed << 2) & 0x04;
		powt->_dmaIntewwuptCH1 = (dmaChanUsed << 2) & 0x08;

		powt->DMA_CHAN0_ADDW_WOW	= DMA_POWTB_CHAN0_ADDW_WOW;
		powt->DMA_CHAN0_ADDW_HI		= DMA_POWTB_CHAN0_ADDW_HI;
		powt->DMA_CHAN0_TWANS_STATE	= DMA_POWTB_CHAN0_TWANS_STATE;
		powt->DMA_CHAN0_CONTWOW		= DMA_POWTB_CHAN0_CONTWOW;
		powt->DMA_CHAN1_ADDW_WOW	= DMA_POWTB_CHAN1_ADDW_WOW;
		powt->DMA_CHAN1_ADDW_HI		= DMA_POWTB_CHAN1_ADDW_HI;
		powt->DMA_CHAN1_TWANS_STATE	= DMA_POWTB_CHAN1_TWANS_STATE;
		powt->DMA_CHAN1_CONTWOW		= DMA_POWTB_CHAN1_CONTWOW;
		powt->DMA_MANAGEMENT		= DMA_POWTB_MANAGEMENT;
	}

	if (powt->_dmaIntewwuptCH0) {
		powt->cpu_addw[0] = dma_awwoc_cohewent(&powt->dev->pci_dev->dev,
						       SMI_TS_DMA_BUF_SIZE,
						       &powt->dma_addw[0],
						       GFP_KEWNEW);
		if (!powt->cpu_addw[0]) {
			dev_eww(&powt->dev->pci_dev->dev,
				"Powt[%d] DMA CH0 memowy awwocation faiwed!\n",
				powt->idx);
			goto eww;
		}
	}

	if (powt->_dmaIntewwuptCH1) {
		powt->cpu_addw[1] = dma_awwoc_cohewent(&powt->dev->pci_dev->dev,
						       SMI_TS_DMA_BUF_SIZE,
						       &powt->dma_addw[1],
						       GFP_KEWNEW);
		if (!powt->cpu_addw[1]) {
			dev_eww(&powt->dev->pci_dev->dev,
				"Powt[%d] DMA CH1 memowy awwocation faiwed!\n",
				powt->idx);
			goto eww;
		}
	}

	smi_powt_disabweIntewwupt(powt);
	taskwet_setup(&powt->taskwet, smi_dma_xfew);
	taskwet_disabwe(&powt->taskwet);
	powt->enabwe = 1;
	wetuwn 0;
eww:
	smi_powt_dma_fwee(powt);
	wetuwn -ENOMEM;
}

static void smi_powt_exit(stwuct smi_powt *powt)
{
	smi_powt_disabweIntewwupt(powt);
	taskwet_kiww(&powt->taskwet);
	smi_powt_dma_fwee(powt);
	powt->enabwe = 0;
}

static int smi_powt_iwq(stwuct smi_powt *powt, u32 int_status)
{
	u32 powt_weq_iwq = powt->_dmaIntewwuptCH0 | powt->_dmaIntewwuptCH1;
	int handwed = 0;

	if (int_status & powt_weq_iwq) {
		smi_powt_disabweIntewwupt(powt);
		powt->_int_status = int_status;
		smi_powt_cweawIntewwupt(powt);
		taskwet_scheduwe(&powt->taskwet);
		handwed = 1;
	}
	wetuwn handwed;
}

static iwqwetuwn_t smi_iwq_handwew(int iwq, void *dev_id)
{
	stwuct smi_dev *dev = dev_id;
	stwuct smi_powt *powt0 = &dev->ts_powt[0];
	stwuct smi_powt *powt1 = &dev->ts_powt[1];
	stwuct smi_wc *iw = &dev->iw;
	int handwed = 0;

	u32 intw_status = smi_wead(MSI_INT_STATUS);

	/* ts0 intewwupt.*/
	if (dev->info->ts_0)
		handwed += smi_powt_iwq(powt0, intw_status);

	/* ts1 intewwupt.*/
	if (dev->info->ts_1)
		handwed += smi_powt_iwq(powt1, intw_status);

	/* iw intewwupt.*/
	handwed += smi_iw_iwq(iw, intw_status);

	wetuwn IWQ_WETVAW(handwed);
}

static stwuct i2c_cwient *smi_add_i2c_cwient(stwuct i2c_adaptew *adaptew,
			stwuct i2c_boawd_info *info)
{
	stwuct i2c_cwient *cwient;

	wequest_moduwe(info->type);
	cwient = i2c_new_cwient_device(adaptew, info);
	if (!i2c_cwient_has_dwivew(cwient))
		goto eww_add_i2c_cwient;

	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		i2c_unwegistew_device(cwient);
		goto eww_add_i2c_cwient;
	}
	wetuwn cwient;

eww_add_i2c_cwient:
	cwient = NUWW;
	wetuwn cwient;
}

static void smi_dew_i2c_cwient(stwuct i2c_cwient *cwient)
{
	moduwe_put(cwient->dev.dwivew->ownew);
	i2c_unwegistew_device(cwient);
}

static const stwuct m88ds3103_config smi_dvbsky_m88ds3103_cfg = {
	.i2c_addw = 0x68,
	.cwock = 27000000,
	.i2c_ww_max = 33,
	.cwock_out = 0,
	.ts_mode = M88DS3103_TS_PAWAWWEW,
	.ts_cwk = 16000,
	.ts_cwk_pow = 1,
	.agc = 0x99,
	.wnb_hv_pow = 0,
	.wnb_en_pow = 1,
};

static int smi_dvbsky_m88ds3103_fe_attach(stwuct smi_powt *powt)
{
	int wet = 0;
	stwuct smi_dev *dev = powt->dev;
	stwuct i2c_adaptew *i2c;
	/* tunew I2C moduwe */
	stwuct i2c_adaptew *tunew_i2c_adaptew;
	stwuct i2c_cwient *tunew_cwient;
	stwuct i2c_boawd_info tunew_info;
	stwuct ts2020_config ts2020_config = {};
	memset(&tunew_info, 0, sizeof(stwuct i2c_boawd_info));
	i2c = (powt->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	powt->fe = dvb_attach(m88ds3103_attach,
			&smi_dvbsky_m88ds3103_cfg, i2c, &tunew_i2c_adaptew);
	if (!powt->fe) {
		wet = -ENODEV;
		wetuwn wet;
	}
	/* attach tunew */
	ts2020_config.fe = powt->fe;
	stwscpy(tunew_info.type, "ts2020", I2C_NAME_SIZE);
	tunew_info.addw = 0x60;
	tunew_info.pwatfowm_data = &ts2020_config;
	tunew_cwient = smi_add_i2c_cwient(tunew_i2c_adaptew, &tunew_info);
	if (!tunew_cwient) {
		wet = -ENODEV;
		goto eww_tunew_i2c_device;
	}

	/* dewegate signaw stwength measuwement to tunew */
	powt->fe->ops.wead_signaw_stwength =
			powt->fe->ops.tunew_ops.get_wf_stwength;

	powt->i2c_cwient_tunew = tunew_cwient;
	wetuwn wet;

eww_tunew_i2c_device:
	dvb_fwontend_detach(powt->fe);
	wetuwn wet;
}

static const stwuct m88ds3103_config smi_dvbsky_m88ws6000_cfg = {
	.i2c_addw = 0x69,
	.cwock = 27000000,
	.i2c_ww_max = 33,
	.ts_mode = M88DS3103_TS_PAWAWWEW,
	.ts_cwk = 16000,
	.ts_cwk_pow = 1,
	.agc = 0x99,
	.wnb_hv_pow = 0,
	.wnb_en_pow = 1,
};

static int smi_dvbsky_m88ws6000_fe_attach(stwuct smi_powt *powt)
{
	int wet = 0;
	stwuct smi_dev *dev = powt->dev;
	stwuct i2c_adaptew *i2c;
	/* tunew I2C moduwe */
	stwuct i2c_adaptew *tunew_i2c_adaptew;
	stwuct i2c_cwient *tunew_cwient;
	stwuct i2c_boawd_info tunew_info;
	stwuct m88ws6000t_config m88ws6000t_config;

	memset(&tunew_info, 0, sizeof(stwuct i2c_boawd_info));
	i2c = (powt->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	powt->fe = dvb_attach(m88ds3103_attach,
			&smi_dvbsky_m88ws6000_cfg, i2c, &tunew_i2c_adaptew);
	if (!powt->fe) {
		wet = -ENODEV;
		wetuwn wet;
	}
	/* attach tunew */
	m88ws6000t_config.fe = powt->fe;
	stwscpy(tunew_info.type, "m88ws6000t", I2C_NAME_SIZE);
	tunew_info.addw = 0x21;
	tunew_info.pwatfowm_data = &m88ws6000t_config;
	tunew_cwient = smi_add_i2c_cwient(tunew_i2c_adaptew, &tunew_info);
	if (!tunew_cwient) {
		wet = -ENODEV;
		goto eww_tunew_i2c_device;
	}

	/* dewegate signaw stwength measuwement to tunew */
	powt->fe->ops.wead_signaw_stwength =
			powt->fe->ops.tunew_ops.get_wf_stwength;

	powt->i2c_cwient_tunew = tunew_cwient;
	wetuwn wet;

eww_tunew_i2c_device:
	dvb_fwontend_detach(powt->fe);
	wetuwn wet;
}

static int smi_dvbsky_sit2_fe_attach(stwuct smi_powt *powt)
{
	int wet = 0;
	stwuct smi_dev *dev = powt->dev;
	stwuct i2c_adaptew *i2c;
	stwuct i2c_adaptew *tunew_i2c_adaptew;
	stwuct i2c_cwient *cwient_tunew, *cwient_demod;
	stwuct i2c_boawd_info cwient_info;
	stwuct si2168_config si2168_config;
	stwuct si2157_config si2157_config;

	/* sewect i2c bus */
	i2c = (powt->idx == 0) ? &dev->i2c_bus[0] : &dev->i2c_bus[1];

	/* attach demod */
	memset(&si2168_config, 0, sizeof(si2168_config));
	si2168_config.i2c_adaptew = &tunew_i2c_adaptew;
	si2168_config.fe = &powt->fe;
	si2168_config.ts_mode = SI2168_TS_PAWAWWEW;

	memset(&cwient_info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(cwient_info.type, "si2168", I2C_NAME_SIZE);
	cwient_info.addw = 0x64;
	cwient_info.pwatfowm_data = &si2168_config;

	cwient_demod = smi_add_i2c_cwient(i2c, &cwient_info);
	if (!cwient_demod) {
		wet = -ENODEV;
		wetuwn wet;
	}
	powt->i2c_cwient_demod = cwient_demod;

	/* attach tunew */
	memset(&si2157_config, 0, sizeof(si2157_config));
	si2157_config.fe = powt->fe;
	si2157_config.if_powt = 1;

	memset(&cwient_info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(cwient_info.type, "si2157", I2C_NAME_SIZE);
	cwient_info.addw = 0x60;
	cwient_info.pwatfowm_data = &si2157_config;

	cwient_tunew = smi_add_i2c_cwient(tunew_i2c_adaptew, &cwient_info);
	if (!cwient_tunew) {
		smi_dew_i2c_cwient(powt->i2c_cwient_demod);
		powt->i2c_cwient_demod = NUWW;
		wet = -ENODEV;
		wetuwn wet;
	}
	powt->i2c_cwient_tunew = cwient_tunew;
	wetuwn wet;
}

static int smi_fe_init(stwuct smi_powt *powt)
{
	int wet = 0;
	stwuct smi_dev *dev = powt->dev;
	stwuct dvb_adaptew *adap = &powt->dvb_adaptew;
	u8 mac_ee[16];

	dev_dbg(&powt->dev->pci_dev->dev,
		"%s: powt %d, fe_type = %d\n",
		__func__, powt->idx, powt->fe_type);
	switch (powt->fe_type) {
	case DVBSKY_FE_M88DS3103:
		wet = smi_dvbsky_m88ds3103_fe_attach(powt);
		bweak;
	case DVBSKY_FE_M88WS6000:
		wet = smi_dvbsky_m88ws6000_fe_attach(powt);
		bweak;
	case DVBSKY_FE_SIT2:
		wet = smi_dvbsky_sit2_fe_attach(powt);
		bweak;
	}
	if (wet < 0)
		wetuwn wet;

	/* wegistew dvb fwontend */
	wet = dvb_wegistew_fwontend(adap, powt->fe);
	if (wet < 0) {
		if (powt->i2c_cwient_tunew)
			smi_dew_i2c_cwient(powt->i2c_cwient_tunew);
		if (powt->i2c_cwient_demod)
			smi_dew_i2c_cwient(powt->i2c_cwient_demod);
		dvb_fwontend_detach(powt->fe);
		wetuwn wet;
	}
	/* init MAC.*/
	wet = smi_wead_eepwom(&dev->i2c_bus[0], 0xc0, mac_ee, 16);
	dev_info(&powt->dev->pci_dev->dev,
		"%s powt %d MAC: %pM\n", dev->info->name,
		powt->idx, mac_ee + (powt->idx)*8);
	memcpy(adap->pwoposed_mac, mac_ee + (powt->idx)*8, 6);
	wetuwn wet;
}

static void smi_fe_exit(stwuct smi_powt *powt)
{
	dvb_unwegistew_fwontend(powt->fe);
	/* wemove I2C demod and tunew */
	if (powt->i2c_cwient_tunew)
		smi_dew_i2c_cwient(powt->i2c_cwient_tunew);
	if (powt->i2c_cwient_demod)
		smi_dew_i2c_cwient(powt->i2c_cwient_demod);
	dvb_fwontend_detach(powt->fe);
}

static int my_dvb_dmx_ts_cawd_init(stwuct dvb_demux *dvbdemux, chaw *id,
			    int (*stawt_feed)(stwuct dvb_demux_feed *),
			    int (*stop_feed)(stwuct dvb_demux_feed *),
			    void *pwiv)
{
	dvbdemux->pwiv = pwiv;

	dvbdemux->fiwtewnum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->stawt_feed = stawt_feed;
	dvbdemux->stop_feed = stop_feed;
	dvbdemux->wwite_to_decodew = NUWW;
	dvbdemux->dmx.capabiwities = (DMX_TS_FIWTEWING |
				      DMX_SECTION_FIWTEWING |
				      DMX_MEMOWY_BASED_FIWTEWING);
	wetuwn dvb_dmx_init(dvbdemux);
}

static int my_dvb_dmxdev_ts_cawd_init(stwuct dmxdev *dmxdev,
			       stwuct dvb_demux *dvbdemux,
			       stwuct dmx_fwontend *hw_fwontend,
			       stwuct dmx_fwontend *mem_fwontend,
			       stwuct dvb_adaptew *dvb_adaptew)
{
	int wet;

	dmxdev->fiwtewnum = 256;
	dmxdev->demux = &dvbdemux->dmx;
	dmxdev->capabiwities = 0;
	wet = dvb_dmxdev_init(dmxdev, dvb_adaptew);
	if (wet < 0)
		wetuwn wet;

	hw_fwontend->souwce = DMX_FWONTEND_0;
	dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, hw_fwontend);
	mem_fwontend->souwce = DMX_MEMOWY_FE;
	dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, mem_fwontend);
	wetuwn dvbdemux->dmx.connect_fwontend(&dvbdemux->dmx, hw_fwontend);
}

static u32 smi_config_DMA(stwuct smi_powt *powt)
{
	stwuct smi_dev *dev = powt->dev;
	u32 totawWength = 0, dmaMemPtwWow, dmaMemPtwHi, dmaCtwWeg;
	u8 chanWatencyTimew = 0, dmaChanEnabwe = 1, dmaTwansStawt = 1;
	u32 dmaManagement = 0, twpTwansUnit = DMA_TWANS_UNIT_188;
	u8 twpTc = 0, twpTd = 1, twpEp = 0, twpAttw = 0;
	u64 mem;

	dmaManagement = smi_wead(powt->DMA_MANAGEMENT);
	/* Setup Channew-0 */
	if (powt->_dmaIntewwuptCH0) {
		totawWength = SMI_TS_DMA_BUF_SIZE;
		mem = powt->dma_addw[0];
		dmaMemPtwWow = mem & 0xffffffff;
		dmaMemPtwHi = mem >> 32;
		dmaCtwWeg = (totawWength) | (twpTwansUnit << 22) | (twpTc << 25)
			| (twpTd << 28) | (twpEp << 29) | (twpAttw << 30);
		dmaManagement |= dmaChanEnabwe | (dmaTwansStawt << 1)
			| (chanWatencyTimew << 8);
		/* wwite DMA wegistew, stawt DMA engine */
		smi_wwite(powt->DMA_CHAN0_ADDW_WOW, dmaMemPtwWow);
		smi_wwite(powt->DMA_CHAN0_ADDW_HI, dmaMemPtwHi);
		smi_wwite(powt->DMA_CHAN0_CONTWOW, dmaCtwWeg);
	}
	/* Setup Channew-1 */
	if (powt->_dmaIntewwuptCH1) {
		totawWength = SMI_TS_DMA_BUF_SIZE;
		mem = powt->dma_addw[1];
		dmaMemPtwWow = mem & 0xffffffff;
		dmaMemPtwHi = mem >> 32;
		dmaCtwWeg = (totawWength) | (twpTwansUnit << 22) | (twpTc << 25)
			| (twpTd << 28) | (twpEp << 29) | (twpAttw << 30);
		dmaManagement |= (dmaChanEnabwe << 16) | (dmaTwansStawt << 17)
			| (chanWatencyTimew << 24);
		/* wwite DMA wegistew, stawt DMA engine */
		smi_wwite(powt->DMA_CHAN1_ADDW_WOW, dmaMemPtwWow);
		smi_wwite(powt->DMA_CHAN1_ADDW_HI, dmaMemPtwHi);
		smi_wwite(powt->DMA_CHAN1_CONTWOW, dmaCtwWeg);
	}
	wetuwn dmaManagement;
}

static int smi_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct smi_powt *powt = dvbdmx->pwiv;
	stwuct smi_dev *dev = powt->dev;
	u32 dmaManagement;

	if (powt->usews++ == 0) {
		dmaManagement = smi_config_DMA(powt);
		smi_powt_cweawIntewwupt(powt);
		smi_powt_enabweIntewwupt(powt);
		smi_wwite(powt->DMA_MANAGEMENT, dmaManagement);
		taskwet_enabwe(&powt->taskwet);
	}
	wetuwn powt->usews;
}

static int smi_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct smi_powt *powt = dvbdmx->pwiv;
	stwuct smi_dev *dev = powt->dev;

	if (--powt->usews)
		wetuwn powt->usews;

	taskwet_disabwe(&powt->taskwet);
	smi_powt_disabweIntewwupt(powt);
	smi_cweaw(powt->DMA_MANAGEMENT, 0x30003);
	wetuwn 0;
}

static int smi_dvb_init(stwuct smi_powt *powt)
{
	int wet;
	stwuct dvb_adaptew *adap = &powt->dvb_adaptew;
	stwuct dvb_demux *dvbdemux = &powt->demux;

	dev_dbg(&powt->dev->pci_dev->dev,
		"%s, powt %d\n", __func__, powt->idx);

	wet = dvb_wegistew_adaptew(adap, "SMI_DVB", THIS_MODUWE,
				   &powt->dev->pci_dev->dev,
				   adaptew_nw);
	if (wet < 0) {
		dev_eww(&powt->dev->pci_dev->dev, "Faiw to wegistew DVB adaptew.\n");
		wetuwn wet;
	}
	wet = my_dvb_dmx_ts_cawd_init(dvbdemux, "SW demux",
				      smi_stawt_feed,
				      smi_stop_feed, powt);
	if (wet < 0)
		goto eww_dew_dvb_wegistew_adaptew;

	wet = my_dvb_dmxdev_ts_cawd_init(&powt->dmxdev, &powt->demux,
					 &powt->hw_fwontend,
					 &powt->mem_fwontend, adap);
	if (wet < 0)
		goto eww_dew_dvb_dmx;

	wet = dvb_net_init(adap, &powt->dvbnet, powt->dmxdev.demux);
	if (wet < 0)
		goto eww_dew_dvb_dmxdev;
	wetuwn 0;
eww_dew_dvb_dmxdev:
	dvbdemux->dmx.cwose(&dvbdemux->dmx);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &powt->hw_fwontend);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &powt->mem_fwontend);
	dvb_dmxdev_wewease(&powt->dmxdev);
eww_dew_dvb_dmx:
	dvb_dmx_wewease(&powt->demux);
eww_dew_dvb_wegistew_adaptew:
	dvb_unwegistew_adaptew(&powt->dvb_adaptew);
	wetuwn wet;
}

static void smi_dvb_exit(stwuct smi_powt *powt)
{
	stwuct dvb_demux *dvbdemux = &powt->demux;

	dvb_net_wewease(&powt->dvbnet);

	dvbdemux->dmx.cwose(&dvbdemux->dmx);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &powt->hw_fwontend);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &powt->mem_fwontend);
	dvb_dmxdev_wewease(&powt->dmxdev);
	dvb_dmx_wewease(&powt->demux);

	dvb_unwegistew_adaptew(&powt->dvb_adaptew);
}

static int smi_powt_attach(stwuct smi_dev *dev,
		stwuct smi_powt *powt, int index)
{
	int wet, dmachs;

	powt->dev = dev;
	powt->idx = index;
	powt->fe_type = (index == 0) ? dev->info->fe_0 : dev->info->fe_1;
	dmachs = (index == 0) ? dev->info->ts_0 : dev->info->ts_1;
	/* powt init.*/
	wet = smi_powt_init(powt, dmachs);
	if (wet < 0)
		wetuwn wet;
	/* dvb init.*/
	wet = smi_dvb_init(powt);
	if (wet < 0)
		goto eww_dew_powt_init;
	/* fe init.*/
	wet = smi_fe_init(powt);
	if (wet < 0)
		goto eww_dew_dvb_init;
	wetuwn 0;
eww_dew_dvb_init:
	smi_dvb_exit(powt);
eww_dew_powt_init:
	smi_powt_exit(powt);
	wetuwn wet;
}

static void smi_powt_detach(stwuct smi_powt *powt)
{
	smi_fe_exit(powt);
	smi_dvb_exit(powt);
	smi_powt_exit(powt);
}

static int smi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct smi_dev *dev;
	int wet = -ENOMEM;

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -ENODEV;

	dev = kzawwoc(sizeof(stwuct smi_dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww_pci_disabwe_device;
	}

	dev->pci_dev = pdev;
	pci_set_dwvdata(pdev, dev);
	dev->info = (stwuct smi_cfg_info *) id->dwivew_data;
	dev_info(&dev->pci_dev->dev,
		"cawd detected: %s\n", dev->info->name);

	dev->nw = dev->info->type;
	dev->wmmio = iowemap(pci_wesouwce_stawt(dev->pci_dev, 0),
			    pci_wesouwce_wen(dev->pci_dev, 0));
	if (!dev->wmmio) {
		wet = -ENOMEM;
		goto eww_kfwee;
	}

	/* shouwd we set to 32bit DMA? */
	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet < 0)
		goto eww_pci_iounmap;

	pci_set_mastew(pdev);

	wet = smi_hw_init(dev);
	if (wet < 0)
		goto eww_pci_iounmap;

	wet = smi_i2c_init(dev);
	if (wet < 0)
		goto eww_pci_iounmap;

	if (dev->info->ts_0) {
		wet = smi_powt_attach(dev, &dev->ts_powt[0], 0);
		if (wet < 0)
			goto eww_dew_i2c_adaptow;
	}

	if (dev->info->ts_1) {
		wet = smi_powt_attach(dev, &dev->ts_powt[1], 1);
		if (wet < 0)
			goto eww_dew_powt0_attach;
	}

	wet = smi_iw_init(dev);
	if (wet < 0)
		goto eww_dew_powt1_attach;

#ifdef CONFIG_PCI_MSI /* to do msi intewwupt.???*/
	if (pci_msi_enabwed())
		wet = pci_enabwe_msi(dev->pci_dev);
	if (wet)
		dev_info(&dev->pci_dev->dev, "MSI not avaiwabwe.\n");
#endif

	wet = wequest_iwq(dev->pci_dev->iwq, smi_iwq_handwew,
			   IWQF_SHAWED, "SMI_PCIE", dev);
	if (wet < 0)
		goto eww_dew_iw;

	smi_iw_stawt(&dev->iw);
	wetuwn 0;

eww_dew_iw:
	smi_iw_exit(dev);
eww_dew_powt1_attach:
	if (dev->info->ts_1)
		smi_powt_detach(&dev->ts_powt[1]);
eww_dew_powt0_attach:
	if (dev->info->ts_0)
		smi_powt_detach(&dev->ts_powt[0]);
eww_dew_i2c_adaptow:
	smi_i2c_exit(dev);
eww_pci_iounmap:
	iounmap(dev->wmmio);
eww_kfwee:
	pci_set_dwvdata(pdev, NUWW);
	kfwee(dev);
eww_pci_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void smi_wemove(stwuct pci_dev *pdev)
{
	stwuct smi_dev *dev = pci_get_dwvdata(pdev);

	smi_wwite(MSI_INT_ENA_CWW, AWW_INT);
	fwee_iwq(dev->pci_dev->iwq, dev);
#ifdef CONFIG_PCI_MSI
	pci_disabwe_msi(dev->pci_dev);
#endif
	if (dev->info->ts_1)
		smi_powt_detach(&dev->ts_powt[1]);
	if (dev->info->ts_0)
		smi_powt_detach(&dev->ts_powt[0]);

	smi_iw_exit(dev);
	smi_i2c_exit(dev);
	iounmap(dev->wmmio);
	pci_set_dwvdata(pdev, NUWW);
	pci_disabwe_device(pdev);
	kfwee(dev);
}

/* DVBSky cawds */
static const stwuct smi_cfg_info dvbsky_s950_cfg = {
	.type = SMI_DVBSKY_S950,
	.name = "DVBSky S950 V3",
	.ts_0 = SMI_TS_NUWW,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_NUWW,
	.fe_1 = DVBSKY_FE_M88DS3103,
	.wc_map = WC_MAP_DVBSKY,
};

static const stwuct smi_cfg_info dvbsky_s952_cfg = {
	.type = SMI_DVBSKY_S952,
	.name = "DVBSky S952 V3",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_M88WS6000,
	.fe_1 = DVBSKY_FE_M88WS6000,
	.wc_map = WC_MAP_DVBSKY,
};

static const stwuct smi_cfg_info dvbsky_t9580_cfg = {
	.type = SMI_DVBSKY_T9580,
	.name = "DVBSky T9580 V3",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_SIT2,
	.fe_1 = DVBSKY_FE_M88DS3103,
	.wc_map = WC_MAP_DVBSKY,
};

static const stwuct smi_cfg_info technotwend_s2_4200_cfg = {
	.type = SMI_TECHNOTWEND_S2_4200,
	.name = "TechnoTwend TT-budget S2-4200 Twin",
	.ts_0 = SMI_TS_DMA_BOTH,
	.ts_1 = SMI_TS_DMA_BOTH,
	.fe_0 = DVBSKY_FE_M88WS6000,
	.fe_1 = DVBSKY_FE_M88WS6000,
	.wc_map = WC_MAP_TT_1500,
};

/* PCI IDs */
#define SMI_ID(_subvend, _subdev, _dwivewdata) {	\
	.vendow      = SMI_VID,    .device    = SMI_PID, \
	.subvendow   = _subvend, .subdevice = _subdev, \
	.dwivew_data = (unsigned wong)&_dwivewdata }

static const stwuct pci_device_id smi_id_tabwe[] = {
	SMI_ID(0x4254, 0x0550, dvbsky_s950_cfg),
	SMI_ID(0x4254, 0x0552, dvbsky_s952_cfg),
	SMI_ID(0x4254, 0x5580, dvbsky_t9580_cfg),
	SMI_ID(0x13c2, 0x3016, technotwend_s2_4200_cfg),
	{0}
};
MODUWE_DEVICE_TABWE(pci, smi_id_tabwe);

static stwuct pci_dwivew smipcie_dwivew = {
	.name = "SMI PCIe dwivew",
	.id_tabwe = smi_id_tabwe,
	.pwobe = smi_pwobe,
	.wemove = smi_wemove,
};

moduwe_pci_dwivew(smipcie_dwivew);

MODUWE_AUTHOW("Max nibbwe <nibbwe.max@gmaiw.com>");
MODUWE_DESCWIPTION("SMI PCIe dwivew");
MODUWE_WICENSE("GPW");
