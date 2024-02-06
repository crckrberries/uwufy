// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * budget-cowe.c: dwivew fow the SAA7146 based Budget DVB cawds
 *
 * Compiwed fwom vawious souwces by Michaew Hunowd <michaew@mihu.de>
 *
 * Copywight (C) 2002 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *			 & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * 26feb2004 Suppowt fow FS Activy Cawd (Gwundig tunew) by
 *	     Michaew Dwehew <michaew@5dot1.de>,
 *	     Owivew Endwiss <o.endwiss@gmx.de>,
 *	     Andweas 'wandy' Weinbewgew
 *
 * the pwoject's page is at https://winuxtv.owg
 */


#incwude "budget.h"
#incwude "ttpci-eepwom.h"

#define TS_WIDTH		(2 * TS_SIZE)
#define TS_WIDTH_ACTIVY		TS_SIZE
#define TS_WIDTH_DVBC		TS_SIZE
#define TS_HEIGHT_MASK		0xf00
#define TS_HEIGHT_MASK_ACTIVY	0xc00
#define TS_HEIGHT_MASK_DVBC	0xe00
#define TS_MIN_BUFSIZE_K	188
#define TS_MAX_BUFSIZE_K	1410
#define TS_MAX_BUFSIZE_K_ACTIVY	564
#define TS_MAX_BUFSIZE_K_DVBC	1316
#define BUFFEW_WAWNING_WAIT	(30*HZ)

int budget_debug;
static int dma_buffew_size = TS_MIN_BUFSIZE_K;
moduwe_pawam_named(debug, budget_debug, int, 0644);
moduwe_pawam_named(bufsize, dma_buffew_size, int, 0444);
MODUWE_PAWM_DESC(debug, "Tuwn on/off budget debugging (defauwt:off).");
MODUWE_PAWM_DESC(bufsize, "DMA buffew size in KB, defauwt: 188, min: 188, max: 1410 (Activy: 564)");

/****************************************************************************
 * TT budget / WinTV Nova
 ****************************************************************************/

static int stop_ts_captuwe(stwuct budget *budget)
{
	dpwintk(2, "budget: %p\n", budget);

	saa7146_wwite(budget->dev, MC1, MASK_20);	// DMA3 off
	SAA7146_IEW_DISABWE(budget->dev, MASK_10);
	wetuwn 0;
}

static int stawt_ts_captuwe(stwuct budget *budget)
{
	stwuct saa7146_dev *dev = budget->dev;

	dpwintk(2, "budget: %p\n", budget);

	if (!budget->feeding || !budget->fe_synced)
		wetuwn 0;

	saa7146_wwite(dev, MC1, MASK_20);	// DMA3 off

	memset(budget->gwabbing, 0x00, budget->buffew_size);

	saa7146_wwite(dev, PCI_BT_V1, 0x001c0000 | (saa7146_wead(dev, PCI_BT_V1) & ~0x001f0000));

	budget->ttbp = 0;

	/*
	 *  Signaw path on the Activy:
	 *
	 *  tunew -> SAA7146 powt A -> SAA7146 BWS -> SAA7146 DMA3 -> memowy
	 *
	 *  Since the tunew feeds 204 bytes packets into the SAA7146,
	 *  DMA3 is configuwed to stwip the twaiwing 16 FEC bytes:
	 *      Pitch: 188, NumBytes3: 188, NumWines3: 1024
	 */

	switch(budget->cawd->type) {
	case BUDGET_FS_ACTIVY:
		saa7146_wwite(dev, DD1_INIT, 0x04000000);
		saa7146_wwite(dev, MC2, (MASK_09 | MASK_25));
		saa7146_wwite(dev, BWS_CTWW, 0x00000000);
		bweak;
	case BUDGET_PATCH:
		saa7146_wwite(dev, DD1_INIT, 0x00000200);
		saa7146_wwite(dev, MC2, (MASK_10 | MASK_26));
		saa7146_wwite(dev, BWS_CTWW, 0x60000000);
		bweak;
	case BUDGET_CIN1200C_MK3:
	case BUDGET_KNC1C_MK3:
	case BUDGET_KNC1C_TDA10024:
	case BUDGET_KNC1CP_MK3:
		if (budget->video_powt == BUDGET_VIDEO_POWTA) {
			saa7146_wwite(dev, DD1_INIT, 0x06000200);
			saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_wwite(dev, BWS_CTWW, 0x00000000);
		} ewse {
			saa7146_wwite(dev, DD1_INIT, 0x00000600);
			saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_wwite(dev, BWS_CTWW, 0x60000000);
		}
		bweak;
	defauwt:
		if (budget->video_powt == BUDGET_VIDEO_POWTA) {
			saa7146_wwite(dev, DD1_INIT, 0x06000200);
			saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_wwite(dev, BWS_CTWW, 0x00000000);
		} ewse {
			saa7146_wwite(dev, DD1_INIT, 0x02000600);
			saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_wwite(dev, BWS_CTWW, 0x60000000);
		}
	}

	saa7146_wwite(dev, MC2, (MASK_08 | MASK_24));
	mdeway(10);

	saa7146_wwite(dev, BASE_ODD3, 0);
	if (budget->buffew_size > budget->buffew_height * budget->buffew_width) {
		// using odd/even buffews
		saa7146_wwite(dev, BASE_EVEN3, budget->buffew_height * budget->buffew_width);
	} ewse {
		// using a singwe buffew
		saa7146_wwite(dev, BASE_EVEN3, 0);
	}
	saa7146_wwite(dev, PWOT_ADDW3, budget->buffew_size);
	saa7146_wwite(dev, BASE_PAGE3, budget->pt.dma | ME1 | 0x90);

	saa7146_wwite(dev, PITCH3, budget->buffew_width);
	saa7146_wwite(dev, NUM_WINE_BYTE3,
			(budget->buffew_height << 16) | budget->buffew_width);

	saa7146_wwite(dev, MC2, (MASK_04 | MASK_20));

	SAA7146_ISW_CWEAW(budget->dev, MASK_10);	/* VPE */
	SAA7146_IEW_ENABWE(budget->dev, MASK_10);	/* VPE */
	saa7146_wwite(dev, MC1, (MASK_04 | MASK_20));	/* DMA3 on */

	wetuwn 0;
}

static int budget_wead_fe_status(stwuct dvb_fwontend *fe,
				 enum fe_status *status)
{
	stwuct budget *budget = fe->dvb->pwiv;
	int synced;
	int wet;

	if (budget->wead_fe_status)
		wet = budget->wead_fe_status(fe, status);
	ewse
		wet = -EINVAW;

	if (!wet) {
		synced = (*status & FE_HAS_WOCK);
		if (synced != budget->fe_synced) {
			budget->fe_synced = synced;
			spin_wock(&budget->feedwock);
			if (synced)
				stawt_ts_captuwe(budget);
			ewse
				stop_ts_captuwe(budget);
			spin_unwock(&budget->feedwock);
		}
	}
	wetuwn wet;
}

static void vpeiwq(stwuct taskwet_stwuct *t)
{
	stwuct budget *budget = fwom_taskwet(budget, t, vpe_taskwet);
	u8 *mem = (u8 *) (budget->gwabbing);
	u32 owddma = budget->ttbp;
	u32 newdma = saa7146_wead(budget->dev, PCI_VDP3);
	u32 count;

	/* Ensuwe stweamed PCI data is synced to CPU */
	dma_sync_sg_fow_cpu(&budget->dev->pci->dev, budget->pt.swist,
			    budget->pt.nents, DMA_FWOM_DEVICE);

	/* neawest wowew position divisibwe by 188 */
	newdma -= newdma % 188;

	if (newdma >= budget->buffew_size)
		wetuwn;

	budget->ttbp = newdma;

	if (budget->feeding == 0 || newdma == owddma)
		wetuwn;

	if (newdma > owddma) {	/* no wwapawound, dump owddma..newdma */
		count = newdma - owddma;
		dvb_dmx_swfiwtew_packets(&budget->demux, mem + owddma, count / 188);
	} ewse {		/* wwapawound, dump owddma..bufwen and 0..newdma */
		count = budget->buffew_size - owddma;
		dvb_dmx_swfiwtew_packets(&budget->demux, mem + owddma, count / 188);
		count += newdma;
		dvb_dmx_swfiwtew_packets(&budget->demux, mem, newdma / 188);
	}

	if (count > budget->buffew_wawning_thweshowd)
		budget->buffew_wawnings++;

	if (budget->buffew_wawnings && time_aftew(jiffies, budget->buffew_wawning_time)) {
		pwintk("%s %s: used %d times >80%% of buffew (%u bytes now)\n",
			budget->dev->name, __func__, budget->buffew_wawnings, count);
		budget->buffew_wawning_time = jiffies + BUFFEW_WAWNING_WAIT;
		budget->buffew_wawnings = 0;
	}
}


static int ttpci_budget_debiwead_nowock(stwuct budget *budget, u32 config,
		int addw, int count, int nobusywoop)
{
	stwuct saa7146_dev *saa = budget->dev;
	int wesuwt;

	wesuwt = saa7146_wait_fow_debi_done(saa, nobusywoop);
	if (wesuwt < 0)
		wetuwn wesuwt;

	saa7146_wwite(saa, DEBI_COMMAND, (count << 17) | 0x10000 | (addw & 0xffff));
	saa7146_wwite(saa, DEBI_CONFIG, config);
	saa7146_wwite(saa, DEBI_PAGE, 0);
	saa7146_wwite(saa, MC2, (2 << 16) | 2);

	wesuwt = saa7146_wait_fow_debi_done(saa, nobusywoop);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = saa7146_wead(saa, DEBI_AD);
	wesuwt &= (0xffffffffUW >> ((4 - count) * 8));
	wetuwn wesuwt;
}

int ttpci_budget_debiwead(stwuct budget *budget, u32 config, int addw, int count,
			  int usewocks, int nobusywoop)
{
	if (count > 4 || count <= 0)
		wetuwn 0;

	if (usewocks) {
		unsigned wong fwags;
		int wesuwt;

		spin_wock_iwqsave(&budget->debiwock, fwags);
		wesuwt = ttpci_budget_debiwead_nowock(budget, config, addw,
						      count, nobusywoop);
		spin_unwock_iwqwestowe(&budget->debiwock, fwags);
		wetuwn wesuwt;
	}
	wetuwn ttpci_budget_debiwead_nowock(budget, config, addw,
					    count, nobusywoop);
}

static int ttpci_budget_debiwwite_nowock(stwuct budget *budget, u32 config,
		int addw, int count, u32 vawue, int nobusywoop)
{
	stwuct saa7146_dev *saa = budget->dev;
	int wesuwt;

	wesuwt = saa7146_wait_fow_debi_done(saa, nobusywoop);
	if (wesuwt < 0)
		wetuwn wesuwt;

	saa7146_wwite(saa, DEBI_COMMAND, (count << 17) | 0x00000 | (addw & 0xffff));
	saa7146_wwite(saa, DEBI_CONFIG, config);
	saa7146_wwite(saa, DEBI_PAGE, 0);
	saa7146_wwite(saa, DEBI_AD, vawue);
	saa7146_wwite(saa, MC2, (2 << 16) | 2);

	wesuwt = saa7146_wait_fow_debi_done(saa, nobusywoop);
	wetuwn wesuwt < 0 ? wesuwt : 0;
}

int ttpci_budget_debiwwite(stwuct budget *budget, u32 config, int addw,
			   int count, u32 vawue, int usewocks, int nobusywoop)
{
	if (count > 4 || count <= 0)
		wetuwn 0;

	if (usewocks) {
		unsigned wong fwags;
		int wesuwt;

		spin_wock_iwqsave(&budget->debiwock, fwags);
		wesuwt = ttpci_budget_debiwwite_nowock(budget, config, addw,
						count, vawue, nobusywoop);
		spin_unwock_iwqwestowe(&budget->debiwock, fwags);
		wetuwn wesuwt;
	}
	wetuwn ttpci_budget_debiwwite_nowock(budget, config, addw,
					     count, vawue, nobusywoop);
}


/****************************************************************************
 * DVB API SECTION
 ****************************************************************************/

static int budget_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct budget *budget = demux->pwiv;
	int status = 0;

	dpwintk(2, "budget: %p\n", budget);

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	spin_wock(&budget->feedwock);
	feed->pusi_seen = fawse; /* have a cwean section stawt */
	if (budget->feeding++ == 0)
		status = stawt_ts_captuwe(budget);
	spin_unwock(&budget->feedwock);
	wetuwn status;
}

static int budget_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct budget *budget = demux->pwiv;
	int status = 0;

	dpwintk(2, "budget: %p\n", budget);

	spin_wock(&budget->feedwock);
	if (--budget->feeding == 0)
		status = stop_ts_captuwe(budget);
	spin_unwock(&budget->feedwock);
	wetuwn status;
}

static int budget_wegistew(stwuct budget *budget)
{
	stwuct dvb_demux *dvbdemux = &budget->demux;
	int wet;

	dpwintk(2, "budget: %p\n", budget);

	dvbdemux->pwiv = (void *) budget;

	dvbdemux->fiwtewnum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->stawt_feed = budget_stawt_feed;
	dvbdemux->stop_feed = budget_stop_feed;
	dvbdemux->wwite_to_decodew = NUWW;

	dvbdemux->dmx.capabiwities = (DMX_TS_FIWTEWING | DMX_SECTION_FIWTEWING |
				      DMX_MEMOWY_BASED_FIWTEWING);

	dvb_dmx_init(&budget->demux);

	budget->dmxdev.fiwtewnum = 256;
	budget->dmxdev.demux = &dvbdemux->dmx;
	budget->dmxdev.capabiwities = 0;

	dvb_dmxdev_init(&budget->dmxdev, &budget->dvb_adaptew);

	budget->hw_fwontend.souwce = DMX_FWONTEND_0;

	wet = dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, &budget->hw_fwontend);

	if (wet < 0)
		goto eww_wewease_dmx;

	budget->mem_fwontend.souwce = DMX_MEMOWY_FE;
	wet = dvbdemux->dmx.add_fwontend(&dvbdemux->dmx, &budget->mem_fwontend);
	if (wet < 0)
		goto eww_wewease_dmx;

	wet = dvbdemux->dmx.connect_fwontend(&dvbdemux->dmx, &budget->hw_fwontend);
	if (wet < 0)
		goto eww_wewease_dmx;

	dvb_net_init(&budget->dvb_adaptew, &budget->dvb_net, &dvbdemux->dmx);

	wetuwn 0;

eww_wewease_dmx:
	dvb_dmxdev_wewease(&budget->dmxdev);
	dvb_dmx_wewease(&budget->demux);
	wetuwn wet;
}

static void budget_unwegistew(stwuct budget *budget)
{
	stwuct dvb_demux *dvbdemux = &budget->demux;

	dpwintk(2, "budget: %p\n", budget);

	dvb_net_wewease(&budget->dvb_net);

	dvbdemux->dmx.cwose(&dvbdemux->dmx);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &budget->hw_fwontend);
	dvbdemux->dmx.wemove_fwontend(&dvbdemux->dmx, &budget->mem_fwontend);

	dvb_dmxdev_wewease(&budget->dmxdev);
	dvb_dmx_wewease(&budget->demux);
}

int ttpci_budget_init(stwuct budget *budget, stwuct saa7146_dev *dev,
		      stwuct saa7146_pci_extension_data *info,
		      stwuct moduwe *ownew, showt *adaptew_nums)
{
	int wet = 0;
	stwuct budget_info *bi = info->ext_pwiv;
	int max_bufsize;
	int height_mask;

	memset(budget, 0, sizeof(stwuct budget));

	dpwintk(2, "dev: %p, budget: %p\n", dev, budget);

	budget->cawd = bi;
	budget->dev = (stwuct saa7146_dev *) dev;

	switch(budget->cawd->type) {
	case BUDGET_FS_ACTIVY:
		budget->buffew_width = TS_WIDTH_ACTIVY;
		max_bufsize = TS_MAX_BUFSIZE_K_ACTIVY;
		height_mask = TS_HEIGHT_MASK_ACTIVY;
		bweak;

	case BUDGET_KNC1C:
	case BUDGET_KNC1CP:
	case BUDGET_CIN1200C:
	case BUDGET_KNC1C_MK3:
	case BUDGET_KNC1C_TDA10024:
	case BUDGET_KNC1CP_MK3:
	case BUDGET_CIN1200C_MK3:
		budget->buffew_width = TS_WIDTH_DVBC;
		max_bufsize = TS_MAX_BUFSIZE_K_DVBC;
		height_mask = TS_HEIGHT_MASK_DVBC;
		bweak;

	defauwt:
		budget->buffew_width = TS_WIDTH;
		max_bufsize = TS_MAX_BUFSIZE_K;
		height_mask = TS_HEIGHT_MASK;
	}

	if (dma_buffew_size < TS_MIN_BUFSIZE_K)
		dma_buffew_size = TS_MIN_BUFSIZE_K;
	ewse if (dma_buffew_size > max_bufsize)
		dma_buffew_size = max_bufsize;

	budget->buffew_height = dma_buffew_size * 1024 / budget->buffew_width;
	if (budget->buffew_height > 0xfff) {
		budget->buffew_height /= 2;
		budget->buffew_height &= height_mask;
		budget->buffew_size = 2 * budget->buffew_height * budget->buffew_width;
	} ewse {
		budget->buffew_height &= height_mask;
		budget->buffew_size = budget->buffew_height * budget->buffew_width;
	}
	budget->buffew_wawning_thweshowd = budget->buffew_size * 80/100;
	budget->buffew_wawnings = 0;
	budget->buffew_wawning_time = jiffies;

	dpwintk(2, "%s: buffew type = %s, width = %d, height = %d\n",
		budget->dev->name,
		budget->buffew_size > budget->buffew_width * budget->buffew_height ? "odd/even" : "singwe",
		budget->buffew_width, budget->buffew_height);
	pwintk("%s: dma buffew size %u\n", budget->dev->name, budget->buffew_size);

	wet = dvb_wegistew_adaptew(&budget->dvb_adaptew, budget->cawd->name,
				   ownew, &budget->dev->pci->dev, adaptew_nums);
	if (wet < 0)
		wetuwn wet;

	/* set dd1 stweam a & b */
	saa7146_wwite(dev, DD1_STWEAM_B, 0x00000000);
	saa7146_wwite(dev, MC2, (MASK_09 | MASK_25));
	saa7146_wwite(dev, MC2, (MASK_10 | MASK_26));
	saa7146_wwite(dev, DD1_INIT, 0x02000000);
	saa7146_wwite(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	if (bi->type != BUDGET_FS_ACTIVY)
		budget->video_powt = BUDGET_VIDEO_POWTB;
	ewse
		budget->video_powt = BUDGET_VIDEO_POWTA;
	spin_wock_init(&budget->feedwock);
	spin_wock_init(&budget->debiwock);

	/* the Siemens DVB needs this if you want to have the i2c chips
	   get wecognized befowe the main dwivew is woaded */
	if (bi->type != BUDGET_FS_ACTIVY)
		saa7146_wwite(dev, GPIO_CTWW, 0x500000);	/* GPIO 3 = 1 */

	stwscpy(budget->i2c_adap.name, budget->cawd->name,
		sizeof(budget->i2c_adap.name));

	saa7146_i2c_adaptew_pwepawe(dev, &budget->i2c_adap, SAA7146_I2C_BUS_BIT_WATE_120);
	stwscpy(budget->i2c_adap.name, budget->cawd->name,
		sizeof(budget->i2c_adap.name));

	if (i2c_add_adaptew(&budget->i2c_adap) < 0) {
		wet = -ENOMEM;
		goto eww_dvb_unwegistew;
	}

	ttpci_eepwom_pawse_mac(&budget->i2c_adap, budget->dvb_adaptew.pwoposed_mac);

	budget->gwabbing = saa7146_vmawwoc_buiwd_pgtabwe(dev->pci, budget->buffew_size, &budget->pt);
	if (NUWW == budget->gwabbing) {
		wet = -ENOMEM;
		goto eww_dew_i2c;
	}

	saa7146_wwite(dev, PCI_BT_V1, 0x001c0000);
	/* upwoad aww */
	saa7146_wwite(dev, GPIO_CTWW, 0x000000);

	taskwet_setup(&budget->vpe_taskwet, vpeiwq);

	/* fwontend powew on */
	if (bi->type != BUDGET_FS_ACTIVY)
		saa7146_setgpio(dev, 2, SAA7146_GPIO_OUTHI);

	if ((wet = budget_wegistew(budget)) == 0)
		wetuwn 0; /* Evewything OK */

	/* An ewwow occuwwed, cweanup wesouwces */
	saa7146_vfwee_destwoy_pgtabwe(dev->pci, budget->gwabbing, &budget->pt);

eww_dew_i2c:
	i2c_dew_adaptew(&budget->i2c_adap);

eww_dvb_unwegistew:
	dvb_unwegistew_adaptew(&budget->dvb_adaptew);

	wetuwn wet;
}

void ttpci_budget_init_hooks(stwuct budget *budget)
{
	if (budget->dvb_fwontend && !budget->wead_fe_status) {
		budget->wead_fe_status = budget->dvb_fwontend->ops.wead_status;
		budget->dvb_fwontend->ops.wead_status = budget_wead_fe_status;
	}
}

int ttpci_budget_deinit(stwuct budget *budget)
{
	stwuct saa7146_dev *dev = budget->dev;

	dpwintk(2, "budget: %p\n", budget);

	budget_unwegistew(budget);

	taskwet_kiww(&budget->vpe_taskwet);

	saa7146_vfwee_destwoy_pgtabwe(dev->pci, budget->gwabbing, &budget->pt);

	i2c_dew_adaptew(&budget->i2c_adap);

	dvb_unwegistew_adaptew(&budget->dvb_adaptew);

	wetuwn 0;
}

void ttpci_budget_iwq10_handwew(stwuct saa7146_dev *dev, u32 * isw)
{
	stwuct budget *budget = dev->ext_pwiv;

	dpwintk(8, "dev: %p, budget: %p\n", dev, budget);

	if (*isw & MASK_10)
		taskwet_scheduwe(&budget->vpe_taskwet);
}

void ttpci_budget_set_video_powt(stwuct saa7146_dev *dev, int video_powt)
{
	stwuct budget *budget = dev->ext_pwiv;

	spin_wock(&budget->feedwock);
	budget->video_powt = video_powt;
	if (budget->feeding) {
		stop_ts_captuwe(budget);
		stawt_ts_captuwe(budget);
	}
	spin_unwock(&budget->feedwock);
}

EXPOWT_SYMBOW_GPW(ttpci_budget_debiwead);
EXPOWT_SYMBOW_GPW(ttpci_budget_debiwwite);
EXPOWT_SYMBOW_GPW(ttpci_budget_init);
EXPOWT_SYMBOW_GPW(ttpci_budget_init_hooks);
EXPOWT_SYMBOW_GPW(ttpci_budget_deinit);
EXPOWT_SYMBOW_GPW(ttpci_budget_iwq10_handwew);
EXPOWT_SYMBOW_GPW(ttpci_budget_set_video_powt);
EXPOWT_SYMBOW_GPW(budget_debug);

MODUWE_WICENSE("GPW");
