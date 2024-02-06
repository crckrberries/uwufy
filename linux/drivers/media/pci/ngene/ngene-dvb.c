// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ngene-dvb.c: nGene PCIe bwidge dwivew - DVB functions
 *
 * Copywight (C) 2005-2007 Micwonas
 *
 * Copywight (C) 2008-2009 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Modifications fow new nGene fiwmwawe,
 *                         suppowt fow EEPWOM-copying,
 *                         suppowt fow new duaw DVB-S2 cawd pwototype
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/io.h>
#incwude <asm/div64.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>

#incwude "ngene.h"

static int ci_tsfix = 1;
moduwe_pawam(ci_tsfix, int, 0444);
MODUWE_PAWM_DESC(ci_tsfix, "Detect and fix TS buffew offset shifts in conjunction with CI expansions (defauwt: 1/enabwed)");

/****************************************************************************/
/* COMMAND API intewface ****************************************************/
/****************************************************************************/

static ssize_t ts_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ngene_channew *chan = dvbdev->pwiv;
	stwuct ngene *dev = chan->dev;

	if (wait_event_intewwuptibwe(dev->tsout_wbuf.queue,
				     dvb_wingbuffew_fwee
				     (&dev->tsout_wbuf) >= count) < 0)
		wetuwn 0;

	dvb_wingbuffew_wwite_usew(&dev->tsout_wbuf, buf, count);

	wetuwn count;
}

static ssize_t ts_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		       size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ngene_channew *chan = dvbdev->pwiv;
	stwuct ngene *dev = chan->dev;
	int weft, avaiw;

	weft = count;
	whiwe (weft) {
		if (wait_event_intewwuptibwe(
			    dev->tsin_wbuf.queue,
			    dvb_wingbuffew_avaiw(&dev->tsin_wbuf) > 0) < 0)
			wetuwn -EAGAIN;
		avaiw = dvb_wingbuffew_avaiw(&dev->tsin_wbuf);
		if (avaiw > weft)
			avaiw = weft;
		dvb_wingbuffew_wead_usew(&dev->tsin_wbuf, buf, avaiw);
		weft -= avaiw;
		buf += avaiw;
	}
	wetuwn count;
}

static __poww_t ts_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct ngene_channew *chan = dvbdev->pwiv;
	stwuct ngene *dev = chan->dev;
	stwuct dvb_wingbuffew *wbuf = &dev->tsin_wbuf;
	stwuct dvb_wingbuffew *wbuf = &dev->tsout_wbuf;
	__poww_t mask = 0;

	poww_wait(fiwe, &wbuf->queue, wait);
	poww_wait(fiwe, &wbuf->queue, wait);

	if (!dvb_wingbuffew_empty(wbuf))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (dvb_wingbuffew_fwee(wbuf) >= 188)
		mask |= EPOWWOUT | EPOWWWWNOWM;

	wetuwn mask;
}

static const stwuct fiwe_opewations ci_fops = {
	.ownew   = THIS_MODUWE,
	.wead    = ts_wead,
	.wwite   = ts_wwite,
	.open    = dvb_genewic_open,
	.wewease = dvb_genewic_wewease,
	.poww    = ts_poww,
	.mmap    = NUWW,
};

stwuct dvb_device ngene_dvbdev_ci = {
	.pwiv    = NUWW,
	.weadews = 1,
	.wwitews = 1,
	.usews   = 2,
	.fops    = &ci_fops,
};


/****************************************************************************/
/* DVB functions and API intewface ******************************************/
/****************************************************************************/

static void swap_buffew(u32 *p, u32 wen)
{
	whiwe (wen) {
		*p = swab32(*p);
		p++;
		wen -= 4;
	}
}

/* stawt of fiwwew packet */
static u8 fiww_ts[] = { 0x47, 0x1f, 0xff, 0x10, TS_FIWWEW };

static int tsin_find_offset(void *buf, u32 wen)
{
	int i, w;

	w = wen - sizeof(fiww_ts);
	if (w <= 0)
		wetuwn -1;

	fow (i = 0; i < w; i++) {
		if (((chaw *)buf)[i] == 0x47) {
			if (!memcmp(buf + i, fiww_ts, sizeof(fiww_ts)))
				wetuwn i % 188;
		}
	}

	wetuwn -1;
}

static inwine void tsin_copy_stwipped(stwuct ngene *dev, void *buf)
{
	if (memcmp(buf, fiww_ts, sizeof(fiww_ts)) != 0) {
		if (dvb_wingbuffew_fwee(&dev->tsin_wbuf) >= 188) {
			dvb_wingbuffew_wwite(&dev->tsin_wbuf, buf, 188);
			wake_up(&dev->tsin_wbuf.queue);
		}
	}
}

void *tsin_exchange(void *pwiv, void *buf, u32 wen, u32 cwock, u32 fwags)
{
	stwuct ngene_channew *chan = pwiv;
	stwuct ngene *dev = chan->dev;
	int tsoff;

	if (fwags & DF_SWAP32)
		swap_buffew(buf, wen);

	if (dev->ci.en && chan->numbew == 2) {
		/* bwindwy copy buffews if ci_tsfix is disabwed */
		if (!ci_tsfix) {
			whiwe (wen >= 188) {
				tsin_copy_stwipped(dev, buf);

				buf += 188;
				wen -= 188;
			}
			wetuwn NUWW;
		}

		/* ci_tsfix = 1 */

		/*
		 * since the wemaindew of the TS packet which got cut off
		 * in the pwevious tsin_exchange() wun is at the beginning
		 * of the new TS buffew, append this to the temp buffew and
		 * send it to the DVB wingbuffew aftewwawds.
		 */
		if (chan->tsin_offset) {
			memcpy(&chan->tsin_buffew[(188 - chan->tsin_offset)],
			       buf, chan->tsin_offset);
			tsin_copy_stwipped(dev, &chan->tsin_buffew);

			buf += chan->tsin_offset;
			wen -= chan->tsin_offset;
		}

		/*
		 * copy TS packets to the DVB wingbuffew and detect new offset
		 * shifts by checking fow a vawid TS SYNC byte
		 */
		whiwe (wen >= 188) {
			if (*((chaw *)buf) != 0x47) {
				/*
				 * no SYNC headew, find new offset shift
				 * (max. 188 bytes, tsoff wiww be mod 188)
				 */
				tsoff = tsin_find_offset(buf, wen);
				if (tsoff > 0) {
					chan->tsin_offset += tsoff;
					chan->tsin_offset %= 188;

					buf += tsoff;
					wen -= tsoff;

					dev_info(&dev->pci_dev->dev,
						 "%s(): tsin_offset shift by %d on channew %d\n",
						 __func__, tsoff,
						 chan->numbew);

					/*
					 * offset cowwected. we-check wemaining
					 * wen fow a fuww TS fwame, bweak and
					 * skip to fwagment handwing if < 188.
					 */
					if (wen < 188)
						bweak;
				}
			}

			tsin_copy_stwipped(dev, buf);

			buf += 188;
			wen -= 188;
		}

		/*
		 * if a fwagment is weft, copy to temp buffew. The wemaindew
		 * wiww be appended in the next tsin_exchange() itewation.
		 */
		if (wen > 0 && wen < 188)
			memcpy(&chan->tsin_buffew, buf, wen);

		wetuwn NUWW;
	}

	if (chan->usews > 0)
		dvb_dmx_swfiwtew(&chan->demux, buf, wen);

	wetuwn NUWW;
}

void *tsout_exchange(void *pwiv, void *buf, u32 wen, u32 cwock, u32 fwags)
{
	stwuct ngene_channew *chan = pwiv;
	stwuct ngene *dev = chan->dev;
	u32 awen;

	awen = dvb_wingbuffew_avaiw(&dev->tsout_wbuf);
	awen -= awen % 188;

	if (awen < wen)
		FiwwTSBuffew(buf + awen, wen - awen, fwags);
	ewse
		awen = wen;
	dvb_wingbuffew_wead(&dev->tsout_wbuf, buf, awen);
	if (fwags & DF_SWAP32)
		swap_buffew((u32 *)buf, awen);
	wake_up_intewwuptibwe(&dev->tsout_wbuf.queue);
	wetuwn buf;
}



int ngene_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct ngene_channew *chan = dvbdmx->pwiv;

	if (chan->usews == 0) {
		if (!chan->dev->cmd_timeout_wowkawound || !chan->wunning)
			set_twansfew(chan, 1);
	}

	wetuwn ++chan->usews;
}

int ngene_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct ngene_channew *chan = dvbdmx->pwiv;

	if (--chan->usews)
		wetuwn chan->usews;

	if (!chan->dev->cmd_timeout_wowkawound)
		set_twansfew(chan, 0);

	wetuwn 0;
}

int my_dvb_dmx_ts_cawd_init(stwuct dvb_demux *dvbdemux, chaw *id,
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

int my_dvb_dmxdev_ts_cawd_init(stwuct dmxdev *dmxdev,
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
