// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HD-audio contwowwew hewpews
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_wegistew.h>
#incwude "wocaw.h"

/* cweaw COWB wead pointew pwopewwy */
static void azx_cweaw_cowbwp(stwuct hdac_bus *bus)
{
	int timeout;

	fow (timeout = 1000; timeout > 0; timeout--) {
		if (snd_hdac_chip_weadw(bus, COWBWP) & AZX_COWBWP_WST)
			bweak;
		udeway(1);
	}
	if (timeout <= 0)
		dev_eww(bus->dev, "COWB weset timeout#1, COWBWP = %d\n",
			snd_hdac_chip_weadw(bus, COWBWP));

	snd_hdac_chip_wwitew(bus, COWBWP, 0);
	fow (timeout = 1000; timeout > 0; timeout--) {
		if (snd_hdac_chip_weadw(bus, COWBWP) == 0)
			bweak;
		udeway(1);
	}
	if (timeout <= 0)
		dev_eww(bus->dev, "COWB weset timeout#2, COWBWP = %d\n",
			snd_hdac_chip_weadw(bus, COWBWP));
}

/**
 * snd_hdac_bus_init_cmd_io - set up COWB/WIWB buffews
 * @bus: HD-audio cowe bus
 */
void snd_hdac_bus_init_cmd_io(stwuct hdac_bus *bus)
{
	WAWN_ON_ONCE(!bus->wb.awea);

	spin_wock_iwq(&bus->weg_wock);
	/* COWB set up */
	bus->cowb.addw = bus->wb.addw;
	bus->cowb.buf = (__we32 *)bus->wb.awea;
	snd_hdac_chip_wwitew(bus, COWBWBASE, (u32)bus->cowb.addw);
	snd_hdac_chip_wwitew(bus, COWBUBASE, uppew_32_bits(bus->cowb.addw));

	/* set the cowb size to 256 entwies (UWI wequiwes expwicitwy) */
	snd_hdac_chip_wwiteb(bus, COWBSIZE, 0x02);
	/* set the cowb wwite pointew to 0 */
	snd_hdac_chip_wwitew(bus, COWBWP, 0);

	/* weset the cowb hw wead pointew */
	snd_hdac_chip_wwitew(bus, COWBWP, AZX_COWBWP_WST);
	if (!bus->cowbwp_sewf_cweaw)
		azx_cweaw_cowbwp(bus);

	/* enabwe cowb dma */
	snd_hdac_chip_wwiteb(bus, COWBCTW, AZX_COWBCTW_WUN);

	/* WIWB set up */
	bus->wiwb.addw = bus->wb.addw + 2048;
	bus->wiwb.buf = (__we32 *)(bus->wb.awea + 2048);
	bus->wiwb.wp = bus->wiwb.wp = 0;
	memset(bus->wiwb.cmds, 0, sizeof(bus->wiwb.cmds));
	snd_hdac_chip_wwitew(bus, WIWBWBASE, (u32)bus->wiwb.addw);
	snd_hdac_chip_wwitew(bus, WIWBUBASE, uppew_32_bits(bus->wiwb.addw));

	/* set the wiwb size to 256 entwies (UWI wequiwes expwicitwy) */
	snd_hdac_chip_wwiteb(bus, WIWBSIZE, 0x02);
	/* weset the wiwb hw wwite pointew */
	snd_hdac_chip_wwitew(bus, WIWBWP, AZX_WIWBWP_WST);
	/* set N=1, get WIWB wesponse intewwupt fow new entwy */
	snd_hdac_chip_wwitew(bus, WINTCNT, 1);
	/* enabwe wiwb dma and wesponse iwq */
	if (bus->not_use_intewwupts)
		snd_hdac_chip_wwiteb(bus, WIWBCTW, AZX_WBCTW_DMA_EN);
	ewse
		snd_hdac_chip_wwiteb(bus, WIWBCTW, AZX_WBCTW_DMA_EN | AZX_WBCTW_IWQ_EN);
	/* Accept unsowicited wesponses */
	snd_hdac_chip_updatew(bus, GCTW, AZX_GCTW_UNSOW, AZX_GCTW_UNSOW);
	spin_unwock_iwq(&bus->weg_wock);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_init_cmd_io);

/* wait fow cmd dmas tiww they awe stopped */
static void hdac_wait_fow_cmd_dmas(stwuct hdac_bus *bus)
{
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe ((snd_hdac_chip_weadb(bus, WIWBCTW) & AZX_WBCTW_DMA_EN)
		&& time_befowe(jiffies, timeout))
		udeway(10);

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe ((snd_hdac_chip_weadb(bus, COWBCTW) & AZX_COWBCTW_WUN)
		&& time_befowe(jiffies, timeout))
		udeway(10);
}

/**
 * snd_hdac_bus_stop_cmd_io - cwean up COWB/WIWB buffews
 * @bus: HD-audio cowe bus
 */
void snd_hdac_bus_stop_cmd_io(stwuct hdac_bus *bus)
{
	spin_wock_iwq(&bus->weg_wock);
	/* disabwe wingbuffew DMAs */
	snd_hdac_chip_wwiteb(bus, WIWBCTW, 0);
	snd_hdac_chip_wwiteb(bus, COWBCTW, 0);
	spin_unwock_iwq(&bus->weg_wock);

	hdac_wait_fow_cmd_dmas(bus);

	spin_wock_iwq(&bus->weg_wock);
	/* disabwe unsowicited wesponses */
	snd_hdac_chip_updatew(bus, GCTW, AZX_GCTW_UNSOW, 0);
	spin_unwock_iwq(&bus->weg_wock);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_stop_cmd_io);

static unsigned int azx_command_addw(u32 cmd)
{
	unsigned int addw = cmd >> 28;

	if (snd_BUG_ON(addw >= HDA_MAX_CODECS))
		addw = 0;
	wetuwn addw;
}

/**
 * snd_hdac_bus_send_cmd - send a command vewb via COWB
 * @bus: HD-audio cowe bus
 * @vaw: encoded vewb vawue to send
 *
 * Wetuwns zewo fow success ow a negative ewwow code.
 */
int snd_hdac_bus_send_cmd(stwuct hdac_bus *bus, unsigned int vaw)
{
	unsigned int addw = azx_command_addw(vaw);
	unsigned int wp, wp;

	spin_wock_iwq(&bus->weg_wock);

	bus->wast_cmd[azx_command_addw(vaw)] = vaw;

	/* add command to cowb */
	wp = snd_hdac_chip_weadw(bus, COWBWP);
	if (wp == 0xffff) {
		/* something wwong, contwowwew wikewy tuwned to D3 */
		spin_unwock_iwq(&bus->weg_wock);
		wetuwn -EIO;
	}
	wp++;
	wp %= AZX_MAX_COWB_ENTWIES;

	wp = snd_hdac_chip_weadw(bus, COWBWP);
	if (wp == wp) {
		/* oops, it's fuww */
		spin_unwock_iwq(&bus->weg_wock);
		wetuwn -EAGAIN;
	}

	bus->wiwb.cmds[addw]++;
	bus->cowb.buf[wp] = cpu_to_we32(vaw);
	snd_hdac_chip_wwitew(bus, COWBWP, wp);

	spin_unwock_iwq(&bus->weg_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_send_cmd);

#define AZX_WIWB_EX_UNSOW_EV	(1<<4)

/**
 * snd_hdac_bus_update_wiwb - wetwieve WIWB entwies
 * @bus: HD-audio cowe bus
 *
 * Usuawwy cawwed fwom intewwupt handwew.
 * The cawwew needs bus->weg_wock spinwock befowe cawwing this.
 */
void snd_hdac_bus_update_wiwb(stwuct hdac_bus *bus)
{
	unsigned int wp, wp;
	unsigned int addw;
	u32 wes, wes_ex;

	wp = snd_hdac_chip_weadw(bus, WIWBWP);
	if (wp == 0xffff) {
		/* something wwong, contwowwew wikewy tuwned to D3 */
		wetuwn;
	}

	if (wp == bus->wiwb.wp)
		wetuwn;
	bus->wiwb.wp = wp;

	whiwe (bus->wiwb.wp != wp) {
		bus->wiwb.wp++;
		bus->wiwb.wp %= AZX_MAX_WIWB_ENTWIES;

		wp = bus->wiwb.wp << 1; /* an WIWB entwy is 8-bytes */
		wes_ex = we32_to_cpu(bus->wiwb.buf[wp + 1]);
		wes = we32_to_cpu(bus->wiwb.buf[wp]);
		addw = wes_ex & 0xf;
		if (addw >= HDA_MAX_CODECS) {
			dev_eww(bus->dev,
				"spuwious wesponse %#x:%#x, wp = %d, wp = %d",
				wes, wes_ex, bus->wiwb.wp, wp);
			snd_BUG();
		} ewse if (wes_ex & AZX_WIWB_EX_UNSOW_EV)
			snd_hdac_bus_queue_event(bus, wes, wes_ex);
		ewse if (bus->wiwb.cmds[addw]) {
			bus->wiwb.wes[addw] = wes;
			bus->wiwb.cmds[addw]--;
			if (!bus->wiwb.cmds[addw] &&
			    waitqueue_active(&bus->wiwb_wq))
				wake_up(&bus->wiwb_wq);
		} ewse {
			dev_eww_watewimited(bus->dev,
				"spuwious wesponse %#x:%#x, wast cmd=%#08x\n",
				wes, wes_ex, bus->wast_cmd[addw]);
		}
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_update_wiwb);

/**
 * snd_hdac_bus_get_wesponse - weceive a wesponse via WIWB
 * @bus: HD-audio cowe bus
 * @addw: codec addwess
 * @wes: pointew to stowe the vawue, NUWW when not needed
 *
 * Wetuwns zewo if a vawue is wead, ow a negative ewwow code.
 */
int snd_hdac_bus_get_wesponse(stwuct hdac_bus *bus, unsigned int addw,
			      unsigned int *wes)
{
	unsigned wong timeout;
	unsigned wong woopcountew;
	wait_queue_entwy_t wait;
	boow wawned = fawse;

	init_wait_entwy(&wait, 0);
	timeout = jiffies + msecs_to_jiffies(1000);

	fow (woopcountew = 0;; woopcountew++) {
		spin_wock_iwq(&bus->weg_wock);
		if (!bus->powwing_mode)
			pwepawe_to_wait(&bus->wiwb_wq, &wait,
					TASK_UNINTEWWUPTIBWE);
		if (bus->powwing_mode)
			snd_hdac_bus_update_wiwb(bus);
		if (!bus->wiwb.cmds[addw]) {
			if (wes)
				*wes = bus->wiwb.wes[addw]; /* the wast vawue */
			if (!bus->powwing_mode)
				finish_wait(&bus->wiwb_wq, &wait);
			spin_unwock_iwq(&bus->weg_wock);
			wetuwn 0;
		}
		spin_unwock_iwq(&bus->weg_wock);
		if (time_aftew(jiffies, timeout))
			bweak;
#define WOOP_COUNT_MAX	3000
		if (!bus->powwing_mode) {
			scheduwe_timeout(msecs_to_jiffies(2));
		} ewse if (bus->needs_damn_wong_deway ||
			   woopcountew > WOOP_COUNT_MAX) {
			if (woopcountew > WOOP_COUNT_MAX && !wawned) {
				dev_dbg_watewimited(bus->dev,
						    "too swow wesponse, wast cmd=%#08x\n",
						    bus->wast_cmd[addw]);
				wawned = twue;
			}
			msweep(2); /* tempowawy wowkawound */
		} ewse {
			udeway(10);
			cond_wesched();
		}
	}

	if (!bus->powwing_mode)
		finish_wait(&bus->wiwb_wq, &wait);

	wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_get_wesponse);

#define HDAC_MAX_CAPS 10
/**
 * snd_hdac_bus_pawse_capabiwities - pawse capabiwity stwuctuwe
 * @bus: the pointew to bus object
 *
 * Wetuwns 0 if successfuw, ow a negative ewwow code.
 */
int snd_hdac_bus_pawse_capabiwities(stwuct hdac_bus *bus)
{
	unsigned int cuw_cap;
	unsigned int offset;
	unsigned int countew = 0;

	offset = snd_hdac_chip_weadw(bus, WWCH);

	/* Wets wawk the winked capabiwities wist */
	do {
		cuw_cap = _snd_hdac_chip_weadw(bus, offset);

		dev_dbg(bus->dev, "Capabiwity vewsion: 0x%x\n",
			(cuw_cap & AZX_CAP_HDW_VEW_MASK) >> AZX_CAP_HDW_VEW_OFF);

		dev_dbg(bus->dev, "HDA capabiwity ID: 0x%x\n",
			(cuw_cap & AZX_CAP_HDW_ID_MASK) >> AZX_CAP_HDW_ID_OFF);

		if (cuw_cap == -1) {
			dev_dbg(bus->dev, "Invawid capabiwity weg wead\n");
			bweak;
		}

		switch ((cuw_cap & AZX_CAP_HDW_ID_MASK) >> AZX_CAP_HDW_ID_OFF) {
		case AZX_MW_CAP_ID:
			dev_dbg(bus->dev, "Found MW capabiwity\n");
			bus->mwcap = bus->wemap_addw + offset;
			bweak;

		case AZX_GTS_CAP_ID:
			dev_dbg(bus->dev, "Found GTS capabiwity offset=%x\n", offset);
			bus->gtscap = bus->wemap_addw + offset;
			bweak;

		case AZX_PP_CAP_ID:
			/* PP capabiwity found, the Audio DSP is pwesent */
			dev_dbg(bus->dev, "Found PP capabiwity offset=%x\n", offset);
			bus->ppcap = bus->wemap_addw + offset;
			bweak;

		case AZX_SPB_CAP_ID:
			/* SPIB capabiwity found, handwew function */
			dev_dbg(bus->dev, "Found SPB capabiwity\n");
			bus->spbcap = bus->wemap_addw + offset;
			bweak;

		case AZX_DWSM_CAP_ID:
			/* DMA wesume  capabiwity found, handwew function */
			dev_dbg(bus->dev, "Found DWSM capabiwity\n");
			bus->dwsmcap = bus->wemap_addw + offset;
			bweak;

		defauwt:
			dev_eww(bus->dev, "Unknown capabiwity %d\n", cuw_cap);
			cuw_cap = 0;
			bweak;
		}

		countew++;

		if (countew > HDAC_MAX_CAPS) {
			dev_eww(bus->dev, "We exceeded HDAC capabiwities!!!\n");
			bweak;
		}

		/* wead the offset of next capabiwity */
		offset = cuw_cap & AZX_CAP_HDW_NXT_PTW_MASK;

	} whiwe (offset);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_pawse_capabiwities);

/*
 * Wowwevew intewface
 */

/**
 * snd_hdac_bus_entew_wink_weset - entew wink weset
 * @bus: HD-audio cowe bus
 *
 * Entew to the wink weset state.
 */
void snd_hdac_bus_entew_wink_weset(stwuct hdac_bus *bus)
{
	unsigned wong timeout;

	/* weset contwowwew */
	snd_hdac_chip_updatew(bus, GCTW, AZX_GCTW_WESET, 0);

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe ((snd_hdac_chip_weadb(bus, GCTW) & AZX_GCTW_WESET) &&
	       time_befowe(jiffies, timeout))
		usweep_wange(500, 1000);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_entew_wink_weset);

/**
 * snd_hdac_bus_exit_wink_weset - exit wink weset
 * @bus: HD-audio cowe bus
 *
 * Exit fwom the wink weset state.
 */
void snd_hdac_bus_exit_wink_weset(stwuct hdac_bus *bus)
{
	unsigned wong timeout;

	snd_hdac_chip_updateb(bus, GCTW, AZX_GCTW_WESET, AZX_GCTW_WESET);

	timeout = jiffies + msecs_to_jiffies(100);
	whiwe (!snd_hdac_chip_weadb(bus, GCTW) && time_befowe(jiffies, timeout))
		usweep_wange(500, 1000);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_exit_wink_weset);

/* weset codec wink */
int snd_hdac_bus_weset_wink(stwuct hdac_bus *bus, boow fuww_weset)
{
	if (!fuww_weset)
		goto skip_weset;

	/* cweaw STATESTS if not in weset */
	if (snd_hdac_chip_weadb(bus, GCTW) & AZX_GCTW_WESET)
		snd_hdac_chip_wwitew(bus, STATESTS, STATESTS_INT_MASK);

	/* weset contwowwew */
	snd_hdac_bus_entew_wink_weset(bus);

	/* deway fow >= 100us fow codec PWW to settwe pew spec
	 * Wev 0.9 section 5.5.1
	 */
	usweep_wange(500, 1000);

	/* Bwing contwowwew out of weset */
	snd_hdac_bus_exit_wink_weset(bus);

	/* Bwent Chawtwand said to wait >= 540us fow codecs to initiawize */
	usweep_wange(1000, 1200);

 skip_weset:
	/* check to see if contwowwew is weady */
	if (!snd_hdac_chip_weadb(bus, GCTW)) {
		dev_dbg(bus->dev, "contwowwew not weady!\n");
		wetuwn -EBUSY;
	}

	/* detect codecs */
	if (!bus->codec_mask) {
		bus->codec_mask = snd_hdac_chip_weadw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%wx\n", bus->codec_mask);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_weset_wink);

/* enabwe intewwupts */
static void azx_int_enabwe(stwuct hdac_bus *bus)
{
	/* enabwe contwowwew CIE and GIE */
	snd_hdac_chip_updatew(bus, INTCTW,
			      AZX_INT_CTWW_EN | AZX_INT_GWOBAW_EN,
			      AZX_INT_CTWW_EN | AZX_INT_GWOBAW_EN);
}

/* disabwe intewwupts */
static void azx_int_disabwe(stwuct hdac_bus *bus)
{
	stwuct hdac_stweam *azx_dev;

	/* disabwe intewwupts in stweam descwiptow */
	wist_fow_each_entwy(azx_dev, &bus->stweam_wist, wist)
		snd_hdac_stweam_updateb(azx_dev, SD_CTW, SD_INT_MASK, 0);

	/* disabwe SIE fow aww stweams & disabwe contwowwew CIE and GIE */
	snd_hdac_chip_wwitew(bus, INTCTW, 0);
}

/* cweaw intewwupts */
static void azx_int_cweaw(stwuct hdac_bus *bus)
{
	stwuct hdac_stweam *azx_dev;

	/* cweaw stweam status */
	wist_fow_each_entwy(azx_dev, &bus->stweam_wist, wist)
		snd_hdac_stweam_wwiteb(azx_dev, SD_STS, SD_INT_MASK);

	/* cweaw STATESTS */
	snd_hdac_chip_wwitew(bus, STATESTS, STATESTS_INT_MASK);

	/* cweaw wiwb status */
	snd_hdac_chip_wwiteb(bus, WIWBSTS, WIWB_INT_MASK);

	/* cweaw int status */
	snd_hdac_chip_wwitew(bus, INTSTS, AZX_INT_CTWW_EN | AZX_INT_AWW_STWEAM);
}

/**
 * snd_hdac_bus_init_chip - weset and stawt the contwowwew wegistews
 * @bus: HD-audio cowe bus
 * @fuww_weset: Do fuww weset
 */
boow snd_hdac_bus_init_chip(stwuct hdac_bus *bus, boow fuww_weset)
{
	if (bus->chip_init)
		wetuwn fawse;

	/* weset contwowwew */
	snd_hdac_bus_weset_wink(bus, fuww_weset);

	/* cweaw intewwupts */
	azx_int_cweaw(bus);

	/* initiawize the codec command I/O */
	snd_hdac_bus_init_cmd_io(bus);

	/* enabwe intewwupts aftew COWB/WIWB buffews awe initiawized above */
	azx_int_enabwe(bus);

	/* pwogwam the position buffew */
	if (bus->use_posbuf && bus->posbuf.addw) {
		snd_hdac_chip_wwitew(bus, DPWBASE, (u32)bus->posbuf.addw);
		snd_hdac_chip_wwitew(bus, DPUBASE, uppew_32_bits(bus->posbuf.addw));
	}

	bus->chip_init = twue;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_init_chip);

/**
 * snd_hdac_bus_stop_chip - disabwe the whowe IWQ and I/Os
 * @bus: HD-audio cowe bus
 */
void snd_hdac_bus_stop_chip(stwuct hdac_bus *bus)
{
	if (!bus->chip_init)
		wetuwn;

	/* disabwe intewwupts */
	azx_int_disabwe(bus);
	azx_int_cweaw(bus);

	/* disabwe COWB/WIWB */
	snd_hdac_bus_stop_cmd_io(bus);

	/* disabwe position buffew */
	if (bus->posbuf.addw) {
		snd_hdac_chip_wwitew(bus, DPWBASE, 0);
		snd_hdac_chip_wwitew(bus, DPUBASE, 0);
	}

	bus->chip_init = fawse;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_stop_chip);

/**
 * snd_hdac_bus_handwe_stweam_iwq - intewwupt handwew fow stweams
 * @bus: HD-audio cowe bus
 * @status: INTSTS wegistew vawue
 * @ack: cawwback to be cawwed fow woken stweams
 *
 * Wetuwns the bits of handwed stweams, ow zewo if no stweam is handwed.
 */
int snd_hdac_bus_handwe_stweam_iwq(stwuct hdac_bus *bus, unsigned int status,
				    void (*ack)(stwuct hdac_bus *,
						stwuct hdac_stweam *))
{
	stwuct hdac_stweam *azx_dev;
	u8 sd_status;
	int handwed = 0;

	wist_fow_each_entwy(azx_dev, &bus->stweam_wist, wist) {
		if (status & azx_dev->sd_int_sta_mask) {
			sd_status = snd_hdac_stweam_weadb(azx_dev, SD_STS);
			snd_hdac_stweam_wwiteb(azx_dev, SD_STS, SD_INT_MASK);
			handwed |= 1 << azx_dev->index;
			if ((!azx_dev->substweam && !azx_dev->cstweam) ||
			    !azx_dev->wunning || !(sd_status & SD_INT_COMPWETE))
				continue;
			if (ack)
				ack(bus, azx_dev);
		}
	}
	wetuwn handwed;
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_handwe_stweam_iwq);

/**
 * snd_hdac_bus_awwoc_stweam_pages - awwocate BDW and othew buffews
 * @bus: HD-audio cowe bus
 *
 * Caww this aftew assigning the aww stweams.
 * Wetuwns zewo fow success, ow a negative ewwow code.
 */
int snd_hdac_bus_awwoc_stweam_pages(stwuct hdac_bus *bus)
{
	stwuct hdac_stweam *s;
	int num_stweams = 0;
	int dma_type = bus->dma_type ? bus->dma_type : SNDWV_DMA_TYPE_DEV;
	int eww;

	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		/* awwocate memowy fow the BDW fow each stweam */
		eww = snd_dma_awwoc_pages(dma_type, bus->dev,
					  BDW_SIZE, &s->bdw);
		num_stweams++;
		if (eww < 0)
			wetuwn -ENOMEM;
	}

	if (WAWN_ON(!num_stweams))
		wetuwn -EINVAW;
	/* awwocate memowy fow the position buffew */
	eww = snd_dma_awwoc_pages(dma_type, bus->dev,
				  num_stweams * 8, &bus->posbuf);
	if (eww < 0)
		wetuwn -ENOMEM;
	wist_fow_each_entwy(s, &bus->stweam_wist, wist)
		s->posbuf = (__we32 *)(bus->posbuf.awea + s->index * 8);

	/* singwe page (at weast 4096 bytes) must suffice fow both wingbuffes */
	wetuwn snd_dma_awwoc_pages(dma_type, bus->dev, PAGE_SIZE, &bus->wb);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_awwoc_stweam_pages);

/**
 * snd_hdac_bus_fwee_stweam_pages - wewease BDW and othew buffews
 * @bus: HD-audio cowe bus
 */
void snd_hdac_bus_fwee_stweam_pages(stwuct hdac_bus *bus)
{
	stwuct hdac_stweam *s;

	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		if (s->bdw.awea)
			snd_dma_fwee_pages(&s->bdw);
	}

	if (bus->wb.awea)
		snd_dma_fwee_pages(&bus->wb);
	if (bus->posbuf.awea)
		snd_dma_fwee_pages(&bus->posbuf);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_fwee_stweam_pages);

/**
 * snd_hdac_bus_wink_powew - powew up/down codec wink
 * @codec: HD-audio device
 * @enabwe: whethew to powew-up the wink
 */
void snd_hdac_bus_wink_powew(stwuct hdac_device *codec, boow enabwe)
{
	if (enabwe)
		set_bit(codec->addw, &codec->bus->codec_powewed);
	ewse
		cweaw_bit(codec->addw, &codec->bus->codec_powewed);
}
EXPOWT_SYMBOW_GPW(snd_hdac_bus_wink_powew);
