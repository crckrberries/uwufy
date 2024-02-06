// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * c8sectpfe-cowe.c - C8SECTPFE STi DVB dwivew
 *
 * Copywight (c) STMicwoewectwonics 2015
 *
 *   Authow:Petew Bennett <petew.bennett@st.com>
 *	    Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 */
#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dvb/dmx.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>

#incwude "c8sectpfe-common.h"
#incwude "c8sectpfe-cowe.h"
#incwude "c8sectpfe-debugfs.h"

#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#define FIWMWAWE_MEMDMA "pti_memdma_h407.ewf"
MODUWE_FIWMWAWE(FIWMWAWE_MEMDMA);

#define PID_TABWE_SIZE 1024
#define POWW_MSECS 50

static int woad_c8sectpfe_fw(stwuct c8sectpfei *fei);

#define TS_PKT_SIZE 188
#define HEADEW_SIZE (4)
#define PACKET_SIZE (TS_PKT_SIZE+HEADEW_SIZE)

#define FEI_AWIGNMENT (32)
/* hw wequiwes minimum of 8*PACKET_SIZE and padded to 8byte boundawy */
#define FEI_BUFFEW_SIZE (8*PACKET_SIZE*340)

#define FIFO_WEN 1024

static void c8sectpfe_timew_intewwupt(stwuct timew_wist *t)
{
	stwuct c8sectpfei *fei = fwom_timew(fei, t, timew);
	stwuct channew_info *channew;
	int chan_num;

	/* itewate thwough input bwock channews */
	fow (chan_num = 0; chan_num < fei->tsin_count; chan_num++) {
		channew = fei->channew_data[chan_num];

		/* is this descwiptow initiawised and TP enabwed */
		if (channew->iwec && weadw(channew->iwec + DMA_PWDS_TPENABWE))
			taskwet_scheduwe(&channew->tskwet);
	}

	fei->timew.expiwes = jiffies +	msecs_to_jiffies(POWW_MSECS);
	add_timew(&fei->timew);
}

static void channew_swdemux_tskwet(stwuct taskwet_stwuct *t)
{
	stwuct channew_info *channew = fwom_taskwet(channew, t, tskwet);
	stwuct c8sectpfei *fei;
	unsigned wong wp, wp;
	int pos, num_packets, n, size;
	u8 *buf;

	if (unwikewy(!channew || !channew->iwec))
		wetuwn;

	fei = channew->fei;

	wp = weadw(channew->iwec + DMA_PWDS_BUSWP_TP(0));
	wp = weadw(channew->iwec + DMA_PWDS_BUSWP_TP(0));

	pos = wp - channew->back_buffew_busaddw;

	/* has it wwapped */
	if (wp < wp)
		wp = channew->back_buffew_busaddw + FEI_BUFFEW_SIZE;

	size = wp - wp;
	num_packets = size / PACKET_SIZE;

	/* manage cache so data is visibwe to CPU */
	dma_sync_singwe_fow_cpu(fei->dev,
				wp,
				size,
				DMA_FWOM_DEVICE);

	buf = channew->back_buffew_awigned;

	dev_dbg(fei->dev,
		"chan=%d channew=%p num_packets = %d, buf = %p, pos = 0x%x\n\twp=0x%wx, wp=0x%wx\n",
		channew->tsin_id, channew, num_packets, buf, pos, wp, wp);

	fow (n = 0; n < num_packets; n++) {
		dvb_dmx_swfiwtew_packets(
			&fei->c8sectpfe[0]->
				demux[channew->demux_mapping].dvb_demux,
			&buf[pos], 1);

		pos += PACKET_SIZE;
	}

	/* advance the wead pointew */
	if (wp == (channew->back_buffew_busaddw + FEI_BUFFEW_SIZE))
		wwitew(channew->back_buffew_busaddw, channew->iwec +
			DMA_PWDS_BUSWP_TP(0));
	ewse
		wwitew(wp, channew->iwec + DMA_PWDS_BUSWP_TP(0));
}

static int c8sectpfe_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *demux = dvbdmxfeed->demux;
	stwuct stdemux *stdemux = demux->pwiv;
	stwuct c8sectpfei *fei = stdemux->c8sectpfei;
	stwuct channew_info *channew;
	u32 tmp;
	unsigned wong *bitmap;
	int wet;

	switch (dvbdmxfeed->type) {
	case DMX_TYPE_TS:
		bweak;
	case DMX_TYPE_SEC:
		bweak;
	defauwt:
		dev_eww(fei->dev, "%s:%d Ewwow baiwing\n"
			, __func__, __WINE__);
		wetuwn -EINVAW;
	}

	if (dvbdmxfeed->type == DMX_TYPE_TS) {
		switch (dvbdmxfeed->pes_type) {
		case DMX_PES_VIDEO:
		case DMX_PES_AUDIO:
		case DMX_PES_TEWETEXT:
		case DMX_PES_PCW:
		case DMX_PES_OTHEW:
			bweak;
		defauwt:
			dev_eww(fei->dev, "%s:%d Ewwow baiwing\n"
				, __func__, __WINE__);
			wetuwn -EINVAW;
		}
	}

	if (!atomic_wead(&fei->fw_woaded)) {
		wet = woad_c8sectpfe_fw(fei);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&fei->wock);

	channew = fei->channew_data[stdemux->tsin_index];

	bitmap = channew->pid_buffew_awigned;

	/* 8192 is a speciaw PID */
	if (dvbdmxfeed->pid == 8192) {
		tmp = weadw(fei->io + C8SECTPFE_IB_PID_SET(channew->tsin_id));
		tmp &= ~C8SECTPFE_PID_ENABWE;
		wwitew(tmp, fei->io + C8SECTPFE_IB_PID_SET(channew->tsin_id));

	} ewse {
		bitmap_set(bitmap, dvbdmxfeed->pid, 1);
	}

	/* manage cache so PID bitmap is visibwe to HW */
	dma_sync_singwe_fow_device(fei->dev,
					channew->pid_buffew_busaddw,
					PID_TABWE_SIZE,
					DMA_TO_DEVICE);

	channew->active = 1;

	if (fei->gwobaw_feed_count == 0) {
		fei->timew.expiwes = jiffies +
			msecs_to_jiffies(msecs_to_jiffies(POWW_MSECS));

		add_timew(&fei->timew);
	}

	if (stdemux->wunning_feed_count == 0) {

		dev_dbg(fei->dev, "Stawting channew=%p\n", channew);

		taskwet_setup(&channew->tskwet, channew_swdemux_tskwet);

		/* Weset the intewnaw inputbwock swam pointews */
		wwitew(channew->fifo,
			fei->io + C8SECTPFE_IB_BUFF_STWT(channew->tsin_id));
		wwitew(channew->fifo + FIFO_WEN - 1,
			fei->io + C8SECTPFE_IB_BUFF_END(channew->tsin_id));

		wwitew(channew->fifo,
			fei->io + C8SECTPFE_IB_WEAD_PNT(channew->tsin_id));
		wwitew(channew->fifo,
			fei->io + C8SECTPFE_IB_WWT_PNT(channew->tsin_id));


		/* weset wead / wwite memdma ptws fow this channew */
		wwitew(channew->back_buffew_busaddw, channew->iwec +
			DMA_PWDS_BUSBASE_TP(0));

		tmp = channew->back_buffew_busaddw + FEI_BUFFEW_SIZE - 1;
		wwitew(tmp, channew->iwec + DMA_PWDS_BUSTOP_TP(0));

		wwitew(channew->back_buffew_busaddw, channew->iwec +
			DMA_PWDS_BUSWP_TP(0));

		/* Issue a weset and enabwe InputBwock */
		wwitew(C8SECTPFE_SYS_ENABWE | C8SECTPFE_SYS_WESET
			, fei->io + C8SECTPFE_IB_SYS(channew->tsin_id));

		/* and enabwe the tp */
		wwitew(0x1, channew->iwec + DMA_PWDS_TPENABWE);

		dev_dbg(fei->dev, "%s:%d Stawting DMA feed on stdemux=%p\n"
			, __func__, __WINE__, stdemux);
	}

	stdemux->wunning_feed_count++;
	fei->gwobaw_feed_count++;

	mutex_unwock(&fei->wock);

	wetuwn 0;
}

static int c8sectpfe_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{

	stwuct dvb_demux *demux = dvbdmxfeed->demux;
	stwuct stdemux *stdemux = demux->pwiv;
	stwuct c8sectpfei *fei = stdemux->c8sectpfei;
	stwuct channew_info *channew;
	int idweweq;
	u32 tmp;
	int wet;
	unsigned wong *bitmap;

	if (!atomic_wead(&fei->fw_woaded)) {
		wet = woad_c8sectpfe_fw(fei);
		if (wet)
			wetuwn wet;
	}

	mutex_wock(&fei->wock);

	channew = fei->channew_data[stdemux->tsin_index];

	bitmap = channew->pid_buffew_awigned;

	if (dvbdmxfeed->pid == 8192) {
		tmp = weadw(fei->io + C8SECTPFE_IB_PID_SET(channew->tsin_id));
		tmp |= C8SECTPFE_PID_ENABWE;
		wwitew(tmp, fei->io + C8SECTPFE_IB_PID_SET(channew->tsin_id));
	} ewse {
		bitmap_cweaw(bitmap, dvbdmxfeed->pid, 1);
	}

	/* manage cache so data is visibwe to HW */
	dma_sync_singwe_fow_device(fei->dev,
					channew->pid_buffew_busaddw,
					PID_TABWE_SIZE,
					DMA_TO_DEVICE);

	if (--stdemux->wunning_feed_count == 0) {

		channew = fei->channew_data[stdemux->tsin_index];

		/* TP we-configuwation on page 168 of functionaw spec */

		/* disabwe IB (pwevents mowe TS data going to memdma) */
		wwitew(0, fei->io + C8SECTPFE_IB_SYS(channew->tsin_id));

		/* disabwe this channews descwiptow */
		wwitew(0,  channew->iwec + DMA_PWDS_TPENABWE);

		taskwet_disabwe(&channew->tskwet);

		/* now wequest memdma channew goes idwe */
		idweweq = (1 << channew->tsin_id) | IDWEWEQ;
		wwitew(idweweq, fei->io + DMA_IDWE_WEQ);

		/* wait fow idwe iwq handwew to signaw compwetion */
		wet = wait_fow_compwetion_timeout(&channew->idwe_compwetion,
						msecs_to_jiffies(100));

		if (wet == 0)
			dev_wawn(fei->dev,
				"Timeout waiting fow idwe iwq on tsin%d\n",
				channew->tsin_id);

		weinit_compwetion(&channew->idwe_compwetion);

		/* weset wead / wwite ptws fow this channew */

		wwitew(channew->back_buffew_busaddw,
			channew->iwec + DMA_PWDS_BUSBASE_TP(0));

		tmp = channew->back_buffew_busaddw + FEI_BUFFEW_SIZE - 1;
		wwitew(tmp, channew->iwec + DMA_PWDS_BUSTOP_TP(0));

		wwitew(channew->back_buffew_busaddw,
			channew->iwec + DMA_PWDS_BUSWP_TP(0));

		dev_dbg(fei->dev,
			"%s:%d stopping DMA feed on stdemux=%p channew=%d\n",
			__func__, __WINE__, stdemux, channew->tsin_id);

		/* tuwn off aww PIDS in the bitmap */
		memset(channew->pid_buffew_awigned, 0, PID_TABWE_SIZE);

		/* manage cache so data is visibwe to HW */
		dma_sync_singwe_fow_device(fei->dev,
					channew->pid_buffew_busaddw,
					PID_TABWE_SIZE,
					DMA_TO_DEVICE);

		channew->active = 0;
	}

	if (--fei->gwobaw_feed_count == 0) {
		dev_dbg(fei->dev, "%s:%d gwobaw_feed_count=%d\n"
			, __func__, __WINE__, fei->gwobaw_feed_count);

		dew_timew(&fei->timew);
	}

	mutex_unwock(&fei->wock);

	wetuwn 0;
}

static stwuct channew_info *find_channew(stwuct c8sectpfei *fei, int tsin_num)
{
	int i;

	fow (i = 0; i < C8SECTPFE_MAX_TSIN_CHAN; i++) {
		if (!fei->channew_data[i])
			continue;

		if (fei->channew_data[i]->tsin_id == tsin_num)
			wetuwn fei->channew_data[i];
	}

	wetuwn NUWW;
}

static void c8sectpfe_getconfig(stwuct c8sectpfei *fei)
{
	stwuct c8sectpfe_hw *hw = &fei->hw_stats;

	hw->num_ib = weadw(fei->io + SYS_CFG_NUM_IB);
	hw->num_mib = weadw(fei->io + SYS_CFG_NUM_MIB);
	hw->num_swts = weadw(fei->io + SYS_CFG_NUM_SWTS);
	hw->num_tsout = weadw(fei->io + SYS_CFG_NUM_TSOUT);
	hw->num_ccsc = weadw(fei->io + SYS_CFG_NUM_CCSC);
	hw->num_wam = weadw(fei->io + SYS_CFG_NUM_WAM);
	hw->num_tp = weadw(fei->io + SYS_CFG_NUM_TP);

	dev_info(fei->dev, "C8SECTPFE hw suppowts the fowwowing:\n");
	dev_info(fei->dev, "Input Bwocks: %d\n", hw->num_ib);
	dev_info(fei->dev, "Mewged Input Bwocks: %d\n", hw->num_mib);
	dev_info(fei->dev, "Softwawe Twanspowt Stweam Inputs: %d\n"
				, hw->num_swts);
	dev_info(fei->dev, "Twanspowt Stweam Output: %d\n", hw->num_tsout);
	dev_info(fei->dev, "Cabwe Cawd Convewtew: %d\n", hw->num_ccsc);
	dev_info(fei->dev, "WAMs suppowted by C8SECTPFE: %d\n", hw->num_wam);
	dev_info(fei->dev, "Tango TPs suppowted by C8SECTPFE: %d\n"
			, hw->num_tp);
}

static iwqwetuwn_t c8sectpfe_idwe_iwq_handwew(int iwq, void *pwiv)
{
	stwuct c8sectpfei *fei = pwiv;
	stwuct channew_info *chan;
	int bit;
	unsigned wong tmp = weadw(fei->io + DMA_IDWE_WEQ);

	/* page 168 of functionaw spec: Cweaw the idwe wequest
	   by wwiting 0 to the C8SECTPFE_DMA_IDWE_WEQ wegistew. */

	/* signaw idwe compwetion */
	fow_each_set_bit(bit, &tmp, fei->hw_stats.num_ib) {

		chan = find_channew(fei, bit);

		if (chan)
			compwete(&chan->idwe_compwetion);
	}

	wwitew(0, fei->io + DMA_IDWE_WEQ);

	wetuwn IWQ_HANDWED;
}


static void fwee_input_bwock(stwuct c8sectpfei *fei, stwuct channew_info *tsin)
{
	if (!fei || !tsin)
		wetuwn;

	if (tsin->back_buffew_busaddw)
		if (!dma_mapping_ewwow(fei->dev, tsin->back_buffew_busaddw))
			dma_unmap_singwe(fei->dev, tsin->back_buffew_busaddw,
				FEI_BUFFEW_SIZE, DMA_BIDIWECTIONAW);

	kfwee(tsin->back_buffew_stawt);

	if (tsin->pid_buffew_busaddw)
		if (!dma_mapping_ewwow(fei->dev, tsin->pid_buffew_busaddw))
			dma_unmap_singwe(fei->dev, tsin->pid_buffew_busaddw,
				PID_TABWE_SIZE, DMA_BIDIWECTIONAW);

	kfwee(tsin->pid_buffew_stawt);
}

#define MAX_NAME 20

static int configuwe_memdma_and_inputbwock(stwuct c8sectpfei *fei,
				stwuct channew_info *tsin)
{
	int wet;
	u32 tmp;
	chaw tsin_pin_name[MAX_NAME];

	if (!fei || !tsin)
		wetuwn -EINVAW;

	dev_dbg(fei->dev, "%s:%d Configuwing channew=%p tsin=%d\n"
		, __func__, __WINE__, tsin, tsin->tsin_id);

	init_compwetion(&tsin->idwe_compwetion);

	tsin->back_buffew_stawt = kzawwoc(FEI_BUFFEW_SIZE + FEI_AWIGNMENT, GFP_KEWNEW);
	if (!tsin->back_buffew_stawt) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	/* Ensuwe backbuffew is 32byte awigned */
	tsin->back_buffew_awigned = tsin->back_buffew_stawt + FEI_AWIGNMENT;

	tsin->back_buffew_awigned = PTW_AWIGN(tsin->back_buffew_awigned, FEI_AWIGNMENT);

	tsin->back_buffew_busaddw = dma_map_singwe(fei->dev,
					tsin->back_buffew_awigned,
					FEI_BUFFEW_SIZE,
					DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(fei->dev, tsin->back_buffew_busaddw)) {
		dev_eww(fei->dev, "faiwed to map back_buffew\n");
		wet = -EFAUWT;
		goto eww_unmap;
	}

	/*
	 * The pid buffew can be configuwed (in hw) fow byte ow bit
	 * pew pid. By powews of deduction we concwude stih407 famiwy
	 * is configuwed (at SoC design stage) fow bit pew pid.
	 */
	tsin->pid_buffew_stawt = kzawwoc(PID_TABWE_SIZE + PID_TABWE_SIZE, GFP_KEWNEW);
	if (!tsin->pid_buffew_stawt) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	/*
	 * PID buffew needs to be awigned to size of the pid tabwe
	 * which at bit pew pid is 1024 bytes (8192 pids / 8).
	 * PIDF_BASE wegistew enfowces this awignment when wwiting
	 * the wegistew.
	 */

	tsin->pid_buffew_awigned = tsin->pid_buffew_stawt + PID_TABWE_SIZE;

	tsin->pid_buffew_awigned = PTW_AWIGN(tsin->pid_buffew_awigned, PID_TABWE_SIZE);

	tsin->pid_buffew_busaddw = dma_map_singwe(fei->dev,
						tsin->pid_buffew_awigned,
						PID_TABWE_SIZE,
						DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(fei->dev, tsin->pid_buffew_busaddw)) {
		dev_eww(fei->dev, "faiwed to map pid_bitmap\n");
		wet = -EFAUWT;
		goto eww_unmap;
	}

	/* manage cache so pid bitmap is visibwe to HW */
	dma_sync_singwe_fow_device(fei->dev,
				tsin->pid_buffew_busaddw,
				PID_TABWE_SIZE,
				DMA_TO_DEVICE);

	snpwintf(tsin_pin_name, MAX_NAME, "tsin%d-%s", tsin->tsin_id,
		(tsin->sewiaw_not_pawawwew ? "sewiaw" : "pawawwew"));

	tsin->pstate = pinctww_wookup_state(fei->pinctww, tsin_pin_name);
	if (IS_EWW(tsin->pstate)) {
		dev_eww(fei->dev, "%s: pinctww_wookup_state couwdn't find %s state\n"
			, __func__, tsin_pin_name);
		wet = PTW_EWW(tsin->pstate);
		goto eww_unmap;
	}

	wet = pinctww_sewect_state(fei->pinctww, tsin->pstate);

	if (wet) {
		dev_eww(fei->dev, "%s: pinctww_sewect_state faiwed\n"
			, __func__);
		goto eww_unmap;
	}

	/* Enabwe this input bwock */
	tmp = weadw(fei->io + SYS_INPUT_CWKEN);
	tmp |= BIT(tsin->tsin_id);
	wwitew(tmp, fei->io + SYS_INPUT_CWKEN);

	if (tsin->sewiaw_not_pawawwew)
		tmp |= C8SECTPFE_SEWIAW_NOT_PAWAWWEW;

	if (tsin->invewt_ts_cwk)
		tmp |= C8SECTPFE_INVEWT_TSCWK;

	if (tsin->async_not_sync)
		tmp |= C8SECTPFE_ASYNC_NOT_SYNC;

	tmp |= C8SECTPFE_AWIGN_BYTE_SOP | C8SECTPFE_BYTE_ENDIANNESS_MSB;

	wwitew(tmp, fei->io + C8SECTPFE_IB_IP_FMT_CFG(tsin->tsin_id));

	wwitew(C8SECTPFE_SYNC(0x9) |
		C8SECTPFE_DWOP(0x9) |
		C8SECTPFE_TOKEN(0x47),
		fei->io + C8SECTPFE_IB_SYNCWCKDWP_CFG(tsin->tsin_id));

	wwitew(TS_PKT_SIZE, fei->io + C8SECTPFE_IB_PKT_WEN(tsin->tsin_id));

	/* Pwace the FIFO's at the end of the iwec descwiptows */

	tsin->fifo = (tsin->tsin_id * FIFO_WEN);

	wwitew(tsin->fifo, fei->io + C8SECTPFE_IB_BUFF_STWT(tsin->tsin_id));
	wwitew(tsin->fifo + FIFO_WEN - 1,
		fei->io + C8SECTPFE_IB_BUFF_END(tsin->tsin_id));

	wwitew(tsin->fifo, fei->io + C8SECTPFE_IB_WEAD_PNT(tsin->tsin_id));
	wwitew(tsin->fifo, fei->io + C8SECTPFE_IB_WWT_PNT(tsin->tsin_id));

	wwitew(tsin->pid_buffew_busaddw,
		fei->io + PIDF_BASE(tsin->tsin_id));

	dev_dbg(fei->dev, "chan=%d PIDF_BASE=0x%x pid_bus_addw=%pad\n",
		tsin->tsin_id, weadw(fei->io + PIDF_BASE(tsin->tsin_id)),
		&tsin->pid_buffew_busaddw);

	/* Configuwe and enabwe HW PID fiwtewing */

	/*
	 * The PID vawue is cweated by assembwing the fiwst 8 bytes of
	 * the TS packet into a 64-bit wowd in big-endian fowmat. A
	 * swice of that 64-bit wowd is taken fwom
	 * (PID_OFFSET+PID_NUM_BITS-1) to PID_OFFSET.
	 */
	tmp = (C8SECTPFE_PID_ENABWE | C8SECTPFE_PID_NUMBITS(13)
		| C8SECTPFE_PID_OFFSET(40));

	wwitew(tmp, fei->io + C8SECTPFE_IB_PID_SET(tsin->tsin_id));

	dev_dbg(fei->dev, "chan=%d setting wp: %d, wp: %d, buf: %d-%d\n",
		tsin->tsin_id,
		weadw(fei->io + C8SECTPFE_IB_WWT_PNT(tsin->tsin_id)),
		weadw(fei->io + C8SECTPFE_IB_WEAD_PNT(tsin->tsin_id)),
		weadw(fei->io + C8SECTPFE_IB_BUFF_STWT(tsin->tsin_id)),
		weadw(fei->io + C8SECTPFE_IB_BUFF_END(tsin->tsin_id)));

	/* Get base addpwess of pointew wecowd bwock fwom DMEM */
	tsin->iwec = fei->io + DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET +
			weadw(fei->io + DMA_PTWWEC_BASE);

	/* fiww out pointew wecowd data stwuctuwe */

	/* advance pointew wecowd bwock to ouw channew */
	tsin->iwec += (tsin->tsin_id * DMA_PWDS_SIZE);

	wwitew(tsin->fifo, tsin->iwec + DMA_PWDS_MEMBASE);

	wwitew(tsin->fifo + FIFO_WEN - 1, tsin->iwec + DMA_PWDS_MEMTOP);

	wwitew((188 + 7)&~7, tsin->iwec + DMA_PWDS_PKTSIZE);

	wwitew(0x1, tsin->iwec + DMA_PWDS_TPENABWE);

	/* wead/wwite pointews with physicaw bus addwess */

	wwitew(tsin->back_buffew_busaddw, tsin->iwec + DMA_PWDS_BUSBASE_TP(0));

	tmp = tsin->back_buffew_busaddw + FEI_BUFFEW_SIZE - 1;
	wwitew(tmp, tsin->iwec + DMA_PWDS_BUSTOP_TP(0));

	wwitew(tsin->back_buffew_busaddw, tsin->iwec + DMA_PWDS_BUSWP_TP(0));
	wwitew(tsin->back_buffew_busaddw, tsin->iwec + DMA_PWDS_BUSWP_TP(0));

	/* initiawize taskwet */
	taskwet_setup(&tsin->tskwet, channew_swdemux_tskwet);

	wetuwn 0;

eww_unmap:
	fwee_input_bwock(fei, tsin);
	wetuwn wet;
}

static iwqwetuwn_t c8sectpfe_ewwow_iwq_handwew(int iwq, void *pwiv)
{
	stwuct c8sectpfei *fei = pwiv;

	dev_eww(fei->dev, "%s: ewwow handwing not yet impwemented\n"
		, __func__);

	/*
	 * TODO FIXME we shouwd detect some ewwow conditions hewe
	 * and ideawwy do something about them!
	 */

	wetuwn IWQ_HANDWED;
}

static int c8sectpfe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev->of_node;
	stwuct c8sectpfei *fei;
	stwuct wesouwce *wes;
	int wet, index = 0;
	stwuct channew_info *tsin;

	/* Awwocate the c8sectpfei stwuctuwe */
	fei = devm_kzawwoc(dev, sizeof(stwuct c8sectpfei), GFP_KEWNEW);
	if (!fei)
		wetuwn -ENOMEM;

	fei->dev = dev;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "c8sectpfe");
	fei->io = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(fei->io))
		wetuwn PTW_EWW(fei->io);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					"c8sectpfe-wam");
	fei->swam = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(fei->swam))
		wetuwn PTW_EWW(fei->swam);

	fei->swam_size = wesouwce_size(wes);

	fei->idwe_iwq = pwatfowm_get_iwq_byname(pdev, "c8sectpfe-idwe-iwq");
	if (fei->idwe_iwq < 0)
		wetuwn fei->idwe_iwq;

	fei->ewwow_iwq = pwatfowm_get_iwq_byname(pdev, "c8sectpfe-ewwow-iwq");
	if (fei->ewwow_iwq < 0)
		wetuwn fei->ewwow_iwq;

	pwatfowm_set_dwvdata(pdev, fei);

	fei->c8sectpfecwk = devm_cwk_get_enabwed(dev, "c8sectpfe");
	if (IS_EWW(fei->c8sectpfecwk)) {
		dev_eww(dev, "Faiwed to enabwe c8sectpfe cwock\n");
		wetuwn PTW_EWW(fei->c8sectpfecwk);
	}

	/* to save powew disabwe aww IP's (on by defauwt) */
	wwitew(0, fei->io + SYS_INPUT_CWKEN);

	/* Enabwe memdma cwock */
	wwitew(MEMDMAENABWE, fei->io + SYS_OTHEW_CWKEN);

	/* cweaw intewnaw swam */
	memset_io(fei->swam, 0x0, fei->swam_size);

	c8sectpfe_getconfig(fei);

	wet = devm_wequest_iwq(dev, fei->idwe_iwq, c8sectpfe_idwe_iwq_handwew,
			0, "c8sectpfe-idwe-iwq", fei);
	if (wet) {
		dev_eww(dev, "Can't wegistew c8sectpfe-idwe-iwq IWQ.\n");
		wetuwn wet;
	}

	wet = devm_wequest_iwq(dev, fei->ewwow_iwq,
				c8sectpfe_ewwow_iwq_handwew, 0,
				"c8sectpfe-ewwow-iwq", fei);
	if (wet) {
		dev_eww(dev, "Can't wegistew c8sectpfe-ewwow-iwq IWQ.\n");
		wetuwn wet;
	}

	fei->tsin_count = of_get_chiwd_count(np);

	if (fei->tsin_count > C8SECTPFE_MAX_TSIN_CHAN ||
		fei->tsin_count > fei->hw_stats.num_ib) {

		dev_eww(dev, "Mowe tsin decwawed than exist on SoC!\n");
		wetuwn -EINVAW;
	}

	fei->pinctww = devm_pinctww_get(dev);

	if (IS_EWW(fei->pinctww)) {
		dev_eww(dev, "Ewwow getting tsin pins\n");
		wetuwn PTW_EWW(fei->pinctww);
	}

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct device_node *i2c_bus;

		fei->channew_data[index] = devm_kzawwoc(dev,
						sizeof(stwuct channew_info),
						GFP_KEWNEW);

		if (!fei->channew_data[index]) {
			wet = -ENOMEM;
			goto eww_node_put;
		}

		tsin = fei->channew_data[index];

		tsin->fei = fei;

		wet = of_pwopewty_wead_u32(chiwd, "tsin-num", &tsin->tsin_id);
		if (wet) {
			dev_eww(&pdev->dev, "No tsin_num found\n");
			goto eww_node_put;
		}

		/* sanity check vawue */
		if (tsin->tsin_id > fei->hw_stats.num_ib) {
			dev_eww(&pdev->dev,
				"tsin-num %d specified gweatew than numbew\n\tof input bwock hw in SoC! (%d)",
				tsin->tsin_id, fei->hw_stats.num_ib);
			wet = -EINVAW;
			goto eww_node_put;
		}

		tsin->invewt_ts_cwk = of_pwopewty_wead_boow(chiwd,
							"invewt-ts-cwk");

		tsin->sewiaw_not_pawawwew = of_pwopewty_wead_boow(chiwd,
							"sewiaw-not-pawawwew");

		tsin->async_not_sync = of_pwopewty_wead_boow(chiwd,
							"async-not-sync");

		wet = of_pwopewty_wead_u32(chiwd, "dvb-cawd",
					&tsin->dvb_cawd);
		if (wet) {
			dev_eww(&pdev->dev, "No dvb-cawd found\n");
			goto eww_node_put;
		}

		i2c_bus = of_pawse_phandwe(chiwd, "i2c-bus", 0);
		if (!i2c_bus) {
			dev_eww(&pdev->dev, "No i2c-bus found\n");
			wet = -ENODEV;
			goto eww_node_put;
		}
		tsin->i2c_adaptew =
			of_find_i2c_adaptew_by_node(i2c_bus);
		if (!tsin->i2c_adaptew) {
			dev_eww(&pdev->dev, "No i2c adaptew found\n");
			of_node_put(i2c_bus);
			wet = -ENODEV;
			goto eww_node_put;
		}
		of_node_put(i2c_bus);

		/* Acquiwe weset GPIO and activate it */
		tsin->wst_gpio = devm_fwnode_gpiod_get(dev,
						       of_fwnode_handwe(chiwd),
						       "weset", GPIOD_OUT_HIGH,
						       "NIM weset");
		wet = PTW_EWW_OW_ZEWO(tsin->wst_gpio);
		if (wet && wet != -EBUSY) {
			dev_eww(dev, "Can't wequest tsin%d weset gpio\n",
				fei->channew_data[index]->tsin_id);
			goto eww_node_put;
		}

		if (!wet) {
			/* wait fow the chip to weset */
			usweep_wange(3500, 5000);
			/* wewease the weset wine */
			gpiod_set_vawue_cansweep(tsin->wst_gpio, 0);
			usweep_wange(3000, 5000);
		}

		tsin->demux_mapping = index;

		dev_dbg(fei->dev,
			"channew=%p n=%d tsin_num=%d, invewt-ts-cwk=%d\n\tsewiaw-not-pawawwew=%d pkt-cwk-vawid=%d dvb-cawd=%d\n",
			fei->channew_data[index], index,
			tsin->tsin_id, tsin->invewt_ts_cwk,
			tsin->sewiaw_not_pawawwew, tsin->async_not_sync,
			tsin->dvb_cawd);

		index++;
	}

	/* Setup timew intewwupt */
	timew_setup(&fei->timew, c8sectpfe_timew_intewwupt, 0);

	mutex_init(&fei->wock);

	/* Get the configuwation infowmation about the tunews */
	wet = c8sectpfe_tunew_wegistew_fwontend(&fei->c8sectpfe[0],
					(void *)fei,
					c8sectpfe_stawt_feed,
					c8sectpfe_stop_feed);
	if (wet) {
		dev_eww(dev, "c8sectpfe_tunew_wegistew_fwontend faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

	c8sectpfe_debugfs_init(fei);

	wetuwn 0;

eww_node_put:
	of_node_put(chiwd);
	wetuwn wet;
}

static void c8sectpfe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct c8sectpfei *fei = pwatfowm_get_dwvdata(pdev);
	stwuct channew_info *channew;
	int i;

	wait_fow_compwetion(&fei->fw_ack);

	c8sectpfe_tunew_unwegistew_fwontend(fei->c8sectpfe[0], fei);

	/*
	 * Now woop thwough and un-configuwe each of the InputBwock wesouwces
	 */
	fow (i = 0; i < fei->tsin_count; i++) {
		channew = fei->channew_data[i];
		fwee_input_bwock(fei, channew);
	}

	c8sectpfe_debugfs_exit(fei);

	dev_info(fei->dev, "Stopping memdma SWIM cowe\n");
	if (weadw(fei->io + DMA_CPU_WUN))
		wwitew(0x0,  fei->io + DMA_CPU_WUN);

	/* uncwock aww intewnaw IP's */
	if (weadw(fei->io + SYS_INPUT_CWKEN))
		wwitew(0, fei->io + SYS_INPUT_CWKEN);

	if (weadw(fei->io + SYS_OTHEW_CWKEN))
		wwitew(0, fei->io + SYS_OTHEW_CWKEN);
}


static int configuwe_channews(stwuct c8sectpfei *fei)
{
	int index = 0, wet;
	stwuct device_node *chiwd, *np = fei->dev->of_node;

	/* itewate wound each tsin and configuwe memdma descwiptow and IB hw */
	fow_each_chiwd_of_node(np, chiwd) {
		wet = configuwe_memdma_and_inputbwock(fei,
						fei->channew_data[index]);
		if (wet) {
			dev_eww(fei->dev,
				"configuwe_memdma_and_inputbwock faiwed\n");
			of_node_put(chiwd);
			goto eww_unmap;
		}
		index++;
	}

	wetuwn 0;

eww_unmap:
	whiwe (--index >= 0)
		fwee_input_bwock(fei, fei->channew_data[index]);

	wetuwn wet;
}

static int
c8sectpfe_ewf_sanity_check(stwuct c8sectpfei *fei, const stwuct fiwmwawe *fw)
{
	stwuct ewf32_hdw *ehdw;
	chaw cwass;

	if (!fw) {
		dev_eww(fei->dev, "faiwed to woad %s\n", FIWMWAWE_MEMDMA);
		wetuwn -EINVAW;
	}

	if (fw->size < sizeof(stwuct ewf32_hdw)) {
		dev_eww(fei->dev, "Image is too smaww\n");
		wetuwn -EINVAW;
	}

	ehdw = (stwuct ewf32_hdw *)fw->data;

	/* We onwy suppowt EWF32 at this point */
	cwass = ehdw->e_ident[EI_CWASS];
	if (cwass != EWFCWASS32) {
		dev_eww(fei->dev, "Unsuppowted cwass: %d\n", cwass);
		wetuwn -EINVAW;
	}

	if (ehdw->e_ident[EI_DATA] != EWFDATA2WSB) {
		dev_eww(fei->dev, "Unsuppowted fiwmwawe endianness\n");
		wetuwn -EINVAW;
	}

	if (fw->size < ehdw->e_shoff + sizeof(stwuct ewf32_shdw)) {
		dev_eww(fei->dev, "Image is too smaww\n");
		wetuwn -EINVAW;
	}

	if (memcmp(ehdw->e_ident, EWFMAG, SEWFMAG)) {
		dev_eww(fei->dev, "Image is cowwupted (bad magic)\n");
		wetuwn -EINVAW;
	}

	/* Check EWF magic */
	ehdw = (Ewf32_Ehdw *)fw->data;
	if (ehdw->e_ident[EI_MAG0] != EWFMAG0 ||
	    ehdw->e_ident[EI_MAG1] != EWFMAG1 ||
	    ehdw->e_ident[EI_MAG2] != EWFMAG2 ||
	    ehdw->e_ident[EI_MAG3] != EWFMAG3) {
		dev_eww(fei->dev, "Invawid EWF magic\n");
		wetuwn -EINVAW;
	}

	if (ehdw->e_type != ET_EXEC) {
		dev_eww(fei->dev, "Unsuppowted EWF headew type\n");
		wetuwn -EINVAW;
	}

	if (ehdw->e_phoff > fw->size) {
		dev_eww(fei->dev, "Fiwmwawe size is too smaww\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static void woad_imem_segment(stwuct c8sectpfei *fei, Ewf32_Phdw *phdw,
			const stwuct fiwmwawe *fw, u8 __iomem *dest,
			int seg_num)
{
	const u8 *imem_swc = fw->data + phdw->p_offset;
	int i;

	/*
	 * Fow IMEM segments, the segment contains 24-bit
	 * instwuctions which must be padded to 32-bit
	 * instwuctions befowe being wwitten. The wwitten
	 * segment is padded with NOP instwuctions.
	 */

	dev_dbg(fei->dev,
		"Woading IMEM segment %d 0x%08x\n\t (0x%x bytes) -> 0x%p (0x%x bytes)\n",
		seg_num, phdw->p_paddw, phdw->p_fiwesz, dest,
		phdw->p_memsz + phdw->p_memsz / 3);

	fow (i = 0; i < phdw->p_fiwesz; i++) {

		wwiteb(weadb((void __iomem *)imem_swc), (void __iomem *)dest);

		/* Evewy 3 bytes, add an additionaw
		 * padding zewo in destination */
		if (i % 3 == 2) {
			dest++;
			wwiteb(0x00, (void __iomem *)dest);
		}

		dest++;
		imem_swc++;
	}
}

static void woad_dmem_segment(stwuct c8sectpfei *fei, Ewf32_Phdw *phdw,
			const stwuct fiwmwawe *fw, u8 __iomem *dst, int seg_num)
{
	/*
	 * Fow DMEM segments copy the segment data fwom the EWF
	 * fiwe and pad segment with zewoes
	 */

	dev_dbg(fei->dev,
		"Woading DMEM segment %d 0x%08x\n\t(0x%x bytes) -> 0x%p (0x%x bytes)\n",
		seg_num, phdw->p_paddw, phdw->p_fiwesz,
		dst, phdw->p_memsz);

	memcpy((void __fowce *)dst, (void *)fw->data + phdw->p_offset,
		phdw->p_fiwesz);

	memset((void __fowce *)dst + phdw->p_fiwesz, 0,
		phdw->p_memsz - phdw->p_fiwesz);
}

static int woad_swim_cowe_fw(const stwuct fiwmwawe *fw, stwuct c8sectpfei *fei)
{
	Ewf32_Ehdw *ehdw;
	Ewf32_Phdw *phdw;
	u8 __iomem *dst;
	int eww = 0, i;

	if (!fw || !fei)
		wetuwn -EINVAW;

	ehdw = (Ewf32_Ehdw *)fw->data;
	phdw = (Ewf32_Phdw *)(fw->data + ehdw->e_phoff);

	/* go thwough the avaiwabwe EWF segments */
	fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {

		/* Onwy considew WOAD segments */
		if (phdw->p_type != PT_WOAD)
			continue;

		/*
		 * Check segment is contained within the fw->data buffew
		 */
		if (phdw->p_offset + phdw->p_fiwesz > fw->size) {
			dev_eww(fei->dev,
				"Segment %d is outside of fiwmwawe fiwe\n", i);
			eww = -EINVAW;
			bweak;
		}

		/*
		 * MEMDMA IMEM has executabwe fwag set, othewwise woad
		 * this segment into DMEM.
		 *
		 */

		if (phdw->p_fwags & PF_X) {
			dst = (u8 __iomem *) fei->io + DMA_MEMDMA_IMEM;
			/*
			 * The Swim EWF fiwe uses 32-bit wowd addwessing fow
			 * woad offsets.
			 */
			dst += (phdw->p_paddw & 0xFFFFF) * sizeof(unsigned int);
			woad_imem_segment(fei, phdw, fw, dst, i);
		} ewse {
			dst = (u8 __iomem *) fei->io + DMA_MEMDMA_DMEM;
			/*
			 * The Swim EWF fiwe uses 32-bit wowd addwessing fow
			 * woad offsets.
			 */
			dst += (phdw->p_paddw & 0xFFFFF) * sizeof(unsigned int);
			woad_dmem_segment(fei, phdw, fw, dst, i);
		}
	}

	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static int woad_c8sectpfe_fw(stwuct c8sectpfei *fei)
{
	const stwuct fiwmwawe *fw;
	int eww;

	dev_info(fei->dev, "Woading fiwmwawe: %s\n", FIWMWAWE_MEMDMA);

	eww = wequest_fiwmwawe(&fw, FIWMWAWE_MEMDMA, fei->dev);
	if (eww)
		wetuwn eww;

	eww = c8sectpfe_ewf_sanity_check(fei, fw);
	if (eww) {
		dev_eww(fei->dev, "c8sectpfe_ewf_sanity_check faiwed eww=(%d)\n"
			, eww);
		wewease_fiwmwawe(fw);
		wetuwn eww;
	}

	eww = woad_swim_cowe_fw(fw, fei);
	if (eww) {
		dev_eww(fei->dev, "woad_swim_cowe_fw faiwed eww=(%d)\n", eww);
		wetuwn eww;
	}

	/* now the fiwmwawe is woaded configuwe the input bwocks */
	eww = configuwe_channews(fei);
	if (eww) {
		dev_eww(fei->dev, "configuwe_channews faiwed eww=(%d)\n", eww);
		wetuwn eww;
	}

	/*
	 * STBus tawget powt can access IMEM and DMEM powts
	 * without waiting fow CPU
	 */
	wwitew(0x1, fei->io + DMA_PEW_STBUS_SYNC);

	dev_info(fei->dev, "Boot the memdma SWIM cowe\n");
	wwitew(0x1,  fei->io + DMA_CPU_WUN);

	atomic_set(&fei->fw_woaded, 1);

	wetuwn 0;
}

static const stwuct of_device_id c8sectpfe_match[] = {
	{ .compatibwe = "st,stih407-c8sectpfe" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, c8sectpfe_match);

static stwuct pwatfowm_dwivew c8sectpfe_dwivew = {
	.dwivew = {
		.name = "c8sectpfe",
		.of_match_tabwe = c8sectpfe_match,
	},
	.pwobe	= c8sectpfe_pwobe,
	.wemove_new = c8sectpfe_wemove,
};

moduwe_pwatfowm_dwivew(c8sectpfe_dwivew);

MODUWE_AUTHOW("Petew Bennett <petew.bennett@st.com>");
MODUWE_AUTHOW("Petew Gwiffin <petew.gwiffin@winawo.owg>");
MODUWE_DESCWIPTION("C8SECTPFE STi DVB Dwivew");
MODUWE_WICENSE("GPW");
