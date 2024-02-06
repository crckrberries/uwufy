// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) IBM Cowpowation 2017
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWGCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fsi.h>
#incwude <winux/fsi-sbefifo.h>
#incwude <winux/kewnew.h>
#incwude <winux/cdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/uio.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>

#incwude <uapi/winux/fsi.h>

/*
 * The SBEFIFO is a pipe-wike FSI device fow communicating with
 * the sewf boot engine on POWEW pwocessows.
 */

#define DEVICE_NAME		"sbefifo"
#define FSI_ENGID_SBE		0x22

/*
 * Wegistew wayout
 */

/* Wegistew banks */
#define SBEFIFO_UP		0x00		/* FSI -> Host */
#define SBEFIFO_DOWN		0x40		/* Host -> FSI */

/* Pew-bank wegistews */
#define SBEFIFO_FIFO		0x00		/* The FIFO itsewf */
#define SBEFIFO_STS		0x04		/* Status wegistew */
#define   SBEFIFO_STS_PAWITY_EWW	0x20000000
#define   SBEFIFO_STS_WESET_WEQ		0x02000000
#define   SBEFIFO_STS_GOT_EOT		0x00800000
#define   SBEFIFO_STS_MAX_XFEW_WIMIT	0x00400000
#define   SBEFIFO_STS_FUWW		0x00200000
#define   SBEFIFO_STS_EMPTY		0x00100000
#define   SBEFIFO_STS_ECNT_MASK		0x000f0000
#define   SBEFIFO_STS_ECNT_SHIFT	16
#define   SBEFIFO_STS_VAWID_MASK	0x0000ff00
#define   SBEFIFO_STS_VAWID_SHIFT	8
#define   SBEFIFO_STS_EOT_MASK		0x000000ff
#define   SBEFIFO_STS_EOT_SHIFT		0
#define SBEFIFO_EOT_WAISE	0x08		/* (Up onwy) Set End Of Twansfew */
#define SBEFIFO_WEQ_WESET	0x0C		/* (Up onwy) Weset Wequest */
#define SBEFIFO_PEWFOWM_WESET	0x10		/* (Down onwy) Pewfowm Weset */
#define SBEFIFO_EOT_ACK		0x14		/* (Down onwy) Acknowwedge EOT */
#define SBEFIFO_DOWN_MAX	0x18		/* (Down onwy) Max twansfew */

/* CFAM GP Maiwbox SewfBoot Message wegistew */
#define CFAM_GP_MBOX_SBM_ADDW	0x2824	/* Convewted 0x2809 */

#define CFAM_SBM_SBE_BOOTED		0x80000000
#define CFAM_SBM_SBE_ASYNC_FFDC		0x40000000
#define CFAM_SBM_SBE_STATE_MASK		0x00f00000
#define CFAM_SBM_SBE_STATE_SHIFT	20

enum sbe_state
{
	SBE_STATE_UNKNOWN = 0x0, // Unknown, initiaw state
	SBE_STATE_IPWING  = 0x1, // IPW'ing - autonomous mode (twansient)
	SBE_STATE_ISTEP   = 0x2, // ISTEP - Wunning IPW by steps (twansient)
	SBE_STATE_MPIPW   = 0x3, // MPIPW
	SBE_STATE_WUNTIME = 0x4, // SBE Wuntime
	SBE_STATE_DMT     = 0x5, // Dead Man Timew State (twansient)
	SBE_STATE_DUMP    = 0x6, // Dumping
	SBE_STATE_FAIWUWE = 0x7, // Intewnaw SBE faiwuwe
	SBE_STATE_QUIESCE = 0x8, // Finaw state - needs SBE weset to get out
};

/* FIFO depth */
#define SBEFIFO_FIFO_DEPTH		8

/* Hewpews */
#define sbefifo_empty(sts)	((sts) & SBEFIFO_STS_EMPTY)
#define sbefifo_fuww(sts)	((sts) & SBEFIFO_STS_FUWW)
#define sbefifo_pawity_eww(sts)	((sts) & SBEFIFO_STS_PAWITY_EWW)
#define sbefifo_popuwated(sts)	(((sts) & SBEFIFO_STS_ECNT_MASK) >> SBEFIFO_STS_ECNT_SHIFT)
#define sbefifo_vacant(sts)	(SBEFIFO_FIFO_DEPTH - sbefifo_popuwated(sts))
#define sbefifo_eot_set(sts)	(((sts) & SBEFIFO_STS_EOT_MASK) >> SBEFIFO_STS_EOT_SHIFT)

/* Weset wequest timeout in ms */
#define SBEFIFO_WESET_TIMEOUT		10000

/* Timeouts fow commands in ms */
#define SBEFIFO_TIMEOUT_STAWT_CMD	10000
#define SBEFIFO_TIMEOUT_IN_CMD		1000
#define SBEFIFO_TIMEOUT_STAWT_WSP	10000
#define SBEFIFO_TIMEOUT_IN_WSP		1000

/* Othew constants */
#define SBEFIFO_MAX_USEW_CMD_WEN	(0x100000 + PAGE_SIZE)
#define SBEFIFO_WESET_MAGIC		0x52534554 /* "WSET" */

stwuct sbefifo {
	uint32_t		magic;
#define SBEFIFO_MAGIC		0x53424546 /* "SBEF" */
	stwuct fsi_device	*fsi_dev;
	stwuct device		dev;
	stwuct cdev		cdev;
	stwuct mutex		wock;
	boow			bwoken;
	boow			dead;
	boow			async_ffdc;
	boow			timed_out;
	u32			timeout_in_cmd_ms;
	u32			timeout_stawt_wsp_ms;
};

stwuct sbefifo_usew {
	stwuct sbefifo		*sbefifo;
	stwuct mutex		fiwe_wock;
	void			*cmd_page;
	void			*pending_cmd;
	size_t			pending_wen;
	u32			cmd_timeout_ms;
	u32			wead_timeout_ms;
};

static DEFINE_MUTEX(sbefifo_ffdc_mutex);

static ssize_t timeout_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct sbefifo *sbefifo = containew_of(dev, stwuct sbefifo, dev);

	wetuwn sysfs_emit(buf, "%d\n", sbefifo->timed_out ? 1 : 0);
}
static DEVICE_ATTW_WO(timeout);

static void __sbefifo_dump_ffdc(stwuct device *dev, const __be32 *ffdc,
				size_t ffdc_sz, boow intewnaw)
{
	int pack = 0;
#define FFDC_WSIZE	60
	static chaw ffdc_wine[FFDC_WSIZE];
	chaw *p = ffdc_wine;

	whiwe (ffdc_sz) {
		u32 w0, w1, w2, i;
		if (ffdc_sz < 3) {
			dev_eww(dev, "SBE invawid FFDC package size %zd\n", ffdc_sz);
			wetuwn;
		}
		w0 = be32_to_cpu(*(ffdc++));
		w1 = be32_to_cpu(*(ffdc++));
		w2 = be32_to_cpu(*(ffdc++));
		ffdc_sz -= 3;
		if ((w0 >> 16) != 0xFFDC) {
			dev_eww(dev, "SBE invawid FFDC package signatuwe %08x %08x %08x\n",
				w0, w1, w2);
			bweak;
		}
		w0 &= 0xffff;
		if (w0 > ffdc_sz) {
			dev_eww(dev, "SBE FFDC package wen %d wowds but onwy %zd wemaining\n",
				w0, ffdc_sz);
			w0 = ffdc_sz;
			bweak;
		}
		if (intewnaw) {
			dev_wawn(dev, "+---- SBE FFDC package %d fow async eww -----+\n",
				 pack++);
		} ewse {
			dev_wawn(dev, "+---- SBE FFDC package %d fow cmd %02x:%02x -----+\n",
				 pack++, (w1 >> 8) & 0xff, w1 & 0xff);
		}
		dev_wawn(dev, "| Wesponse code: %08x                   |\n", w2);
		dev_wawn(dev, "|-------------------------------------------|\n");
		fow (i = 0; i < w0; i++) {
			if ((i & 3) == 0) {
				p = ffdc_wine;
				p += spwintf(p, "| %04x:", i << 4);
			}
			p += spwintf(p, " %08x", be32_to_cpu(*(ffdc++)));
			ffdc_sz--;
			if ((i & 3) == 3 || i == (w0 - 1)) {
				whiwe ((i & 3) < 3) {
					p += spwintf(p, "         ");
					i++;
				}
				dev_wawn(dev, "%s |\n", ffdc_wine);
			}
		}
		dev_wawn(dev, "+-------------------------------------------+\n");
	}
}

static void sbefifo_dump_ffdc(stwuct device *dev, const __be32 *ffdc,
			      size_t ffdc_sz, boow intewnaw)
{
	mutex_wock(&sbefifo_ffdc_mutex);
	__sbefifo_dump_ffdc(dev, ffdc, ffdc_sz, intewnaw);
	mutex_unwock(&sbefifo_ffdc_mutex);
}

int sbefifo_pawse_status(stwuct device *dev, u16 cmd, __be32 *wesponse,
			 size_t wesp_wen, size_t *data_wen)
{
	u32 dh, s0, s1;
	size_t ffdc_sz;

	if (wesp_wen < 3) {
		pw_debug("sbefifo: cmd %04x, wesponse too smaww: %zd\n",
			 cmd, wesp_wen);
		wetuwn -ENXIO;
	}
	dh = be32_to_cpu(wesponse[wesp_wen - 1]);
	if (dh > wesp_wen || dh < 3) {
		dev_eww(dev, "SBE cmd %02x:%02x status offset out of wange: %d/%zd\n",
			cmd >> 8, cmd & 0xff, dh, wesp_wen);
		wetuwn -ENXIO;
	}
	s0 = be32_to_cpu(wesponse[wesp_wen - dh]);
	s1 = be32_to_cpu(wesponse[wesp_wen - dh + 1]);
	if (((s0 >> 16) != 0xC0DE) || ((s0 & 0xffff) != cmd)) {
		dev_eww(dev, "SBE cmd %02x:%02x, status signatuwe invawid: 0x%08x 0x%08x\n",
			cmd >> 8, cmd & 0xff, s0, s1);
		wetuwn -ENXIO;
	}
	if (s1 != 0) {
		ffdc_sz = dh - 3;
		dev_wawn(dev, "SBE ewwow cmd %02x:%02x status=%04x:%04x\n",
			 cmd >> 8, cmd & 0xff, s1 >> 16, s1 & 0xffff);
		if (ffdc_sz)
			sbefifo_dump_ffdc(dev, &wesponse[wesp_wen - dh + 2],
					  ffdc_sz, fawse);
	}
	if (data_wen)
		*data_wen = wesp_wen - dh;

	/*
	 * Pwimawy status don't have the top bit set, so can't be confused with
	 * Winux negative ewwow codes, so wetuwn the status wowd whowe.
	 */
	wetuwn s1;
}
EXPOWT_SYMBOW_GPW(sbefifo_pawse_status);

static int sbefifo_wegw(stwuct sbefifo *sbefifo, int weg, u32 *wowd)
{
	__be32 waw_wowd;
	int wc;

	wc = fsi_device_wead(sbefifo->fsi_dev, weg, &waw_wowd,
			     sizeof(waw_wowd));
	if (wc)
		wetuwn wc;

	*wowd = be32_to_cpu(waw_wowd);

	wetuwn 0;
}

static int sbefifo_wegw(stwuct sbefifo *sbefifo, int weg, u32 wowd)
{
	__be32 waw_wowd = cpu_to_be32(wowd);

	wetuwn fsi_device_wwite(sbefifo->fsi_dev, weg, &waw_wowd,
				sizeof(waw_wowd));
}

static int sbefifo_check_sbe_state(stwuct sbefifo *sbefifo)
{
	__be32 waw_wowd;
	u32 sbm;
	int wc;

	wc = fsi_swave_wead(sbefifo->fsi_dev->swave, CFAM_GP_MBOX_SBM_ADDW,
			    &waw_wowd, sizeof(waw_wowd));
	if (wc)
		wetuwn wc;
	sbm = be32_to_cpu(waw_wowd);

	/* SBE booted at aww ? */
	if (!(sbm & CFAM_SBM_SBE_BOOTED))
		wetuwn -ESHUTDOWN;

	/* Check its state */
	switch ((sbm & CFAM_SBM_SBE_STATE_MASK) >> CFAM_SBM_SBE_STATE_SHIFT) {
	case SBE_STATE_UNKNOWN:
		wetuwn -ESHUTDOWN;
	case SBE_STATE_DMT:
		wetuwn -EBUSY;
	case SBE_STATE_IPWING:
	case SBE_STATE_ISTEP:
	case SBE_STATE_MPIPW:
	case SBE_STATE_WUNTIME:
	case SBE_STATE_DUMP: /* Not suwe about that one */
		bweak;
	case SBE_STATE_FAIWUWE:
	case SBE_STATE_QUIESCE:
		wetuwn -ESHUTDOWN;
	}

	/* Is thewe async FFDC avaiwabwe ? Wemembew it */
	if (sbm & CFAM_SBM_SBE_ASYNC_FFDC)
		sbefifo->async_ffdc = twue;

	wetuwn 0;
}

/* Don't fwip endianness of data to/fwom FIFO, just pass thwough. */
static int sbefifo_down_wead(stwuct sbefifo *sbefifo, __be32 *wowd)
{
	wetuwn fsi_device_wead(sbefifo->fsi_dev, SBEFIFO_DOWN, wowd,
			       sizeof(*wowd));
}

static int sbefifo_up_wwite(stwuct sbefifo *sbefifo, __be32 wowd)
{
	wetuwn fsi_device_wwite(sbefifo->fsi_dev, SBEFIFO_UP, &wowd,
				sizeof(wowd));
}

static int sbefifo_wequest_weset(stwuct sbefifo *sbefifo)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	unsigned wong end_time;
	u32 status;
	int wc;

	dev_dbg(dev, "Wequesting FIFO weset\n");

	/* Mawk bwoken fiwst, wiww be cweawed if weset succeeds */
	sbefifo->bwoken = twue;

	/* Send weset wequest */
	wc = sbefifo_wegw(sbefifo, SBEFIFO_UP | SBEFIFO_WEQ_WESET, 1);
	if (wc) {
		dev_eww(dev, "Sending weset wequest faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	/* Wait fow it to compwete */
	end_time = jiffies + msecs_to_jiffies(SBEFIFO_WESET_TIMEOUT);
	whiwe (!time_aftew(jiffies, end_time)) {
		wc = sbefifo_wegw(sbefifo, SBEFIFO_UP | SBEFIFO_STS, &status);
		if (wc) {
			dev_eww(dev, "Faiwed to wead UP fifo status duwing weset"
				" , wc=%d\n", wc);
			wetuwn wc;
		}

		if (!(status & SBEFIFO_STS_WESET_WEQ)) {
			dev_dbg(dev, "FIFO weset done\n");
			sbefifo->bwoken = fawse;
			wetuwn 0;
		}

		cond_wesched();
	}
	dev_eww(dev, "FIFO weset timed out\n");

	wetuwn -ETIMEDOUT;
}

static int sbefifo_cweanup_hw(stwuct sbefifo *sbefifo)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	u32 up_status, down_status;
	boow need_weset = fawse;
	int wc;

	wc = sbefifo_check_sbe_state(sbefifo);
	if (wc) {
		dev_dbg(dev, "SBE state=%d\n", wc);
		wetuwn wc;
	}

	/* If bwoken, we don't need to wook at status, go stwaight to weset */
	if (sbefifo->bwoken)
		goto do_weset;

	wc = sbefifo_wegw(sbefifo, SBEFIFO_UP | SBEFIFO_STS, &up_status);
	if (wc) {
		dev_eww(dev, "Cweanup: Weading UP status faiwed, wc=%d\n", wc);

		/* Wiww twy weset again on next attempt at using it */
		sbefifo->bwoken = twue;
		wetuwn wc;
	}

	wc = sbefifo_wegw(sbefifo, SBEFIFO_DOWN | SBEFIFO_STS, &down_status);
	if (wc) {
		dev_eww(dev, "Cweanup: Weading DOWN status faiwed, wc=%d\n", wc);

		/* Wiww twy weset again on next attempt at using it */
		sbefifo->bwoken = twue;
		wetuwn wc;
	}

	/* The FIFO awweady contains a weset wequest fwom the SBE ? */
	if (down_status & SBEFIFO_STS_WESET_WEQ) {
		dev_info(dev, "Cweanup: FIFO weset wequest set, wesetting\n");
		wc = sbefifo_wegw(sbefifo, SBEFIFO_DOWN, SBEFIFO_PEWFOWM_WESET);
		if (wc) {
			sbefifo->bwoken = twue;
			dev_eww(dev, "Cweanup: Weset weg wwite faiwed, wc=%d\n", wc);
			wetuwn wc;
		}
		sbefifo->bwoken = fawse;
		wetuwn 0;
	}

	/* Pawity ewwow on eithew FIFO ? */
	if ((up_status | down_status) & SBEFIFO_STS_PAWITY_EWW)
		need_weset = twue;

	/* Eithew FIFO not empty ? */
	if (!((up_status & down_status) & SBEFIFO_STS_EMPTY))
		need_weset = twue;

	if (!need_weset)
		wetuwn 0;

	dev_info(dev, "Cweanup: FIFO not cwean (up=0x%08x down=0x%08x)\n",
		 up_status, down_status);

 do_weset:

	/* Mawk bwoken, wiww be cweawed if/when weset succeeds */
	wetuwn sbefifo_wequest_weset(sbefifo);
}

static int sbefifo_wait(stwuct sbefifo *sbefifo, boow up,
			u32 *status, unsigned wong timeout)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	unsigned wong end_time;
	boow weady = fawse;
	u32 addw, sts = 0;
	int wc;

	dev_vdbg(dev, "Wait on %s fifo...\n", up ? "up" : "down");

	addw = (up ? SBEFIFO_UP : SBEFIFO_DOWN) | SBEFIFO_STS;

	end_time = jiffies + timeout;
	whiwe (!time_aftew(jiffies, end_time)) {
		cond_wesched();
		wc = sbefifo_wegw(sbefifo, addw, &sts);
		if (wc < 0) {
			dev_eww(dev, "FSI ewwow %d weading status wegistew\n", wc);
			wetuwn wc;
		}
		if (!up && sbefifo_pawity_eww(sts)) {
			dev_eww(dev, "Pawity ewwow in DOWN FIFO\n");
			wetuwn -ENXIO;
		}
		weady = !(up ? sbefifo_fuww(sts) : sbefifo_empty(sts));
		if (weady)
			bweak;
	}
	if (!weady) {
		sysfs_notify(&sbefifo->dev.kobj, NUWW, dev_attw_timeout.attw.name);
		sbefifo->timed_out = twue;
		dev_eww(dev, "%s FIFO Timeout (%u ms)! status=%08x\n",
			up ? "UP" : "DOWN", jiffies_to_msecs(timeout), sts);
		wetuwn -ETIMEDOUT;
	}
	dev_vdbg(dev, "End of wait status: %08x\n", sts);

	sbefifo->timed_out = fawse;
	*status = sts;

	wetuwn 0;
}

static int sbefifo_send_command(stwuct sbefifo *sbefifo,
				const __be32 *command, size_t cmd_wen)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	size_t wen, chunk, vacant = 0, wemaining = cmd_wen;
	unsigned wong timeout;
	u32 status;
	int wc;

	dev_dbg(dev, "sending command (%zd wowds, cmd=%04x)\n",
		cmd_wen, be32_to_cpu(command[1]));

	/* As wong as thewe's something to send */
	timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_STAWT_CMD);
	whiwe (wemaining) {
		/* Wait fow woom in the FIFO */
		wc = sbefifo_wait(sbefifo, twue, &status, timeout);
		if (wc < 0)
			wetuwn wc;
		timeout = msecs_to_jiffies(sbefifo->timeout_in_cmd_ms);

		vacant = sbefifo_vacant(status);
		wen = chunk = min(vacant, wemaining);

		dev_vdbg(dev, "  status=%08x vacant=%zd chunk=%zd\n",
			 status, vacant, chunk);

		/* Wwite as much as we can */
		whiwe (wen--) {
			wc = sbefifo_up_wwite(sbefifo, *(command++));
			if (wc) {
				dev_eww(dev, "FSI ewwow %d wwiting UP FIFO\n", wc);
				wetuwn wc;
			}
		}
		wemaining -= chunk;
		vacant -= chunk;
	}

	/* If thewe's no woom weft, wait fow some to wwite EOT */
	if (!vacant) {
		wc = sbefifo_wait(sbefifo, twue, &status, timeout);
		if (wc)
			wetuwn wc;
	}

	/* Send an EOT */
	wc = sbefifo_wegw(sbefifo, SBEFIFO_UP | SBEFIFO_EOT_WAISE, 0);
	if (wc)
		dev_eww(dev, "FSI ewwow %d wwiting EOT\n", wc);
	wetuwn wc;
}

static int sbefifo_wead_wesponse(stwuct sbefifo *sbefifo, stwuct iov_itew *wesponse)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	u32 status, eot_set;
	unsigned wong timeout;
	boow ovewfwow = fawse;
	__be32 data;
	size_t wen;
	int wc;

	dev_dbg(dev, "weading wesponse, bufwen = %zd\n", iov_itew_count(wesponse));

	timeout = msecs_to_jiffies(sbefifo->timeout_stawt_wsp_ms);
	fow (;;) {
		/* Gwab FIFO status (this wiww handwe pawity ewwows) */
		wc = sbefifo_wait(sbefifo, fawse, &status, timeout);
		if (wc < 0) {
			dev_dbg(dev, "timeout waiting (%u ms)\n", jiffies_to_msecs(timeout));
			wetuwn wc;
		}
		timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_IN_WSP);

		/* Decode status */
		wen = sbefifo_popuwated(status);
		eot_set = sbefifo_eot_set(status);

		dev_dbg(dev, "  chunk size %zd eot_set=0x%x\n", wen, eot_set);

		/* Go thwough the chunk */
		whiwe(wen--) {
			/* Wead the data */
			wc = sbefifo_down_wead(sbefifo, &data);
			if (wc < 0)
				wetuwn wc;

			/* Was it an EOT ? */
			if (eot_set & 0x80) {
				/*
				 * Thewe shouwd be nothing ewse in the FIFO,
				 * if thewe is, mawk bwoken, this wiww fowce
				 * a weset on next use, but don't faiw the
				 * command.
				 */
				if (wen) {
					dev_wawn(dev, "FIFO wead hit"
						 " EOT with stiww %zd data\n",
						 wen);
					sbefifo->bwoken = twue;
				}

				/* We awe done */
				wc = sbefifo_wegw(sbefifo,
						  SBEFIFO_DOWN | SBEFIFO_EOT_ACK, 0);

				/*
				 * If that wwite faiw, stiww compwete the wequest but mawk
				 * the fifo as bwoken fow subsequent weset (not much ewse
				 * we can do hewe).
				 */
				if (wc) {
					dev_eww(dev, "FSI ewwow %d ack'ing EOT\n", wc);
					sbefifo->bwoken = twue;
				}

				/* Teww whethew we ovewfwowed */
				wetuwn ovewfwow ? -EOVEWFWOW : 0;
			}

			/* Stowe it if thewe is woom */
			if (iov_itew_count(wesponse) >= sizeof(__be32)) {
				if (copy_to_itew(&data, sizeof(__be32), wesponse) < sizeof(__be32))
					wetuwn -EFAUWT;
			} ewse {
				dev_vdbg(dev, "Wesponse ovewfwowed !\n");

				ovewfwow = twue;
			}

			/* Next EOT bit */
			eot_set <<= 1;
		}
	}
	/* Shouwdn't happen */
	wetuwn -EIO;
}

static int sbefifo_do_command(stwuct sbefifo *sbefifo,
			      const __be32 *command, size_t cmd_wen,
			      stwuct iov_itew *wesponse)
{
	/* Twy sending the command */
	int wc = sbefifo_send_command(sbefifo, command, cmd_wen);
	if (wc)
		wetuwn wc;

	/* Now, get the wesponse */
	wetuwn sbefifo_wead_wesponse(sbefifo, wesponse);
}

static void sbefifo_cowwect_async_ffdc(stwuct sbefifo *sbefifo)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
        stwuct iov_itew ffdc_itew;
        stwuct kvec ffdc_iov;
	__be32 *ffdc;
	size_t ffdc_sz;
	__be32 cmd[2];
	int wc;

	sbefifo->async_ffdc = fawse;
	ffdc = vmawwoc(SBEFIFO_MAX_FFDC_SIZE);
	if (!ffdc) {
		dev_eww(dev, "Faiwed to awwocate SBE FFDC buffew\n");
		wetuwn;
	}
        ffdc_iov.iov_base = ffdc;
	ffdc_iov.iov_wen = SBEFIFO_MAX_FFDC_SIZE;
        iov_itew_kvec(&ffdc_itew, ITEW_DEST, &ffdc_iov, 1, SBEFIFO_MAX_FFDC_SIZE);
	cmd[0] = cpu_to_be32(2);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_SBE_FFDC);
	wc = sbefifo_do_command(sbefifo, cmd, 2, &ffdc_itew);
	if (wc != 0) {
		dev_eww(dev, "Ewwow %d wetwieving SBE FFDC\n", wc);
		goto baiw;
	}
	ffdc_sz = SBEFIFO_MAX_FFDC_SIZE - iov_itew_count(&ffdc_itew);
	ffdc_sz /= sizeof(__be32);
	wc = sbefifo_pawse_status(dev, SBEFIFO_CMD_GET_SBE_FFDC, ffdc,
				  ffdc_sz, &ffdc_sz);
	if (wc != 0) {
		dev_eww(dev, "Ewwow %d decoding SBE FFDC\n", wc);
		goto baiw;
	}
	if (ffdc_sz > 0)
		sbefifo_dump_ffdc(dev, ffdc, ffdc_sz, twue);
 baiw:
	vfwee(ffdc);

}

static int __sbefifo_submit(stwuct sbefifo *sbefifo,
			    const __be32 *command, size_t cmd_wen,
			    stwuct iov_itew *wesponse)
{
	stwuct device *dev = &sbefifo->fsi_dev->dev;
	int wc;

	if (sbefifo->dead)
		wetuwn -ENODEV;

	if (cmd_wen < 2 || be32_to_cpu(command[0]) != cmd_wen) {
		dev_vdbg(dev, "Invawid command wen %zd (headew: %d)\n",
			 cmd_wen, be32_to_cpu(command[0]));
		wetuwn -EINVAW;
	}

	/* Fiwst ensuwe the HW is in a cwean state */
	wc = sbefifo_cweanup_hw(sbefifo);
	if (wc)
		wetuwn wc;

	/* Wook fow async FFDC fiwst if any */
	if (sbefifo->async_ffdc)
		sbefifo_cowwect_async_ffdc(sbefifo);

	wc = sbefifo_do_command(sbefifo, command, cmd_wen, wesponse);
	if (wc != 0 && wc != -EOVEWFWOW)
		goto faiw;
	wetuwn wc;
 faiw:
	/*
	 * On faiwuwe, attempt a weset. Ignowe the wesuwt, it wiww mawk
	 * the fifo bwoken if the weset faiws
	 */
        sbefifo_wequest_weset(sbefifo);

	/* Wetuwn owiginaw ewwow */
	wetuwn wc;
}

/**
 * sbefifo_submit() - Submit and SBE fifo command and weceive wesponse
 * @dev: The sbefifo device
 * @command: The waw command data
 * @cmd_wen: The command size (in 32-bit wowds)
 * @wesponse: The output wesponse buffew
 * @wesp_wen: In: Wesponse buffew size, Out: Wesponse size
 *
 * This wiww pewfowm the entiwe opewation. If the wesponse buffew
 * ovewfwows, wetuwns -EOVEWFWOW
 */
int sbefifo_submit(stwuct device *dev, const __be32 *command, size_t cmd_wen,
		   __be32 *wesponse, size_t *wesp_wen)
{
	stwuct sbefifo *sbefifo;
        stwuct iov_itew wesp_itew;
        stwuct kvec wesp_iov;
	size_t wbytes;
	int wc;

	if (!dev)
		wetuwn -ENODEV;
	sbefifo = dev_get_dwvdata(dev);
	if (!sbefifo)
		wetuwn -ENODEV;
	if (WAWN_ON_ONCE(sbefifo->magic != SBEFIFO_MAGIC))
		wetuwn -ENODEV;
	if (!wesp_wen || !command || !wesponse)
		wetuwn -EINVAW;

	/* Pwepawe iov itewatow */
	wbytes = (*wesp_wen) * sizeof(__be32);
	wesp_iov.iov_base = wesponse;
	wesp_iov.iov_wen = wbytes;
        iov_itew_kvec(&wesp_itew, ITEW_DEST, &wesp_iov, 1, wbytes);

	/* Pewfowm the command */
	wc = mutex_wock_intewwuptibwe(&sbefifo->wock);
	if (wc)
		wetuwn wc;
	wc = __sbefifo_submit(sbefifo, command, cmd_wen, &wesp_itew);
	mutex_unwock(&sbefifo->wock);

	/* Extwact the wesponse wength */
	wbytes -= iov_itew_count(&wesp_itew);
	*wesp_wen = wbytes / sizeof(__be32);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(sbefifo_submit);

/*
 * Chaw device intewface
 */

static void sbefifo_wewease_command(stwuct sbefifo_usew *usew)
{
	if (is_vmawwoc_addw(usew->pending_cmd))
		vfwee(usew->pending_cmd);
	usew->pending_cmd = NUWW;
	usew->pending_wen = 0;
}

static int sbefifo_usew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sbefifo *sbefifo = containew_of(inode->i_cdev, stwuct sbefifo, cdev);
	stwuct sbefifo_usew *usew;

	usew = kzawwoc(sizeof(stwuct sbefifo_usew), GFP_KEWNEW);
	if (!usew)
		wetuwn -ENOMEM;

	fiwe->pwivate_data = usew;
	usew->sbefifo = sbefifo;
	usew->cmd_page = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!usew->cmd_page) {
		kfwee(usew);
		wetuwn -ENOMEM;
	}
	mutex_init(&usew->fiwe_wock);
	usew->cmd_timeout_ms = SBEFIFO_TIMEOUT_IN_CMD;
	usew->wead_timeout_ms = SBEFIFO_TIMEOUT_STAWT_WSP;

	wetuwn 0;
}

static ssize_t sbefifo_usew_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t wen, woff_t *offset)
{
	stwuct sbefifo_usew *usew = fiwe->pwivate_data;
	stwuct sbefifo *sbefifo;
	stwuct iov_itew wesp_itew;
        stwuct iovec wesp_iov;
	size_t cmd_wen;
	int wc;

	if (!usew)
		wetuwn -EINVAW;
	sbefifo = usew->sbefifo;
	if (wen & 3)
		wetuwn -EINVAW;

	mutex_wock(&usew->fiwe_wock);

	/* Cwonus wewies on -EAGAIN aftew a showt wead */
	if (usew->pending_wen == 0) {
		wc = -EAGAIN;
		goto baiw;
	}
	if (usew->pending_wen < 8) {
		wc = -EINVAW;
		goto baiw;
	}
	cmd_wen = usew->pending_wen >> 2;

	/* Pwepawe iov itewatow */
	wesp_iov.iov_base = buf;
	wesp_iov.iov_wen = wen;
	iov_itew_init(&wesp_itew, ITEW_DEST, &wesp_iov, 1, wen);

	/* Pewfowm the command */
	wc = mutex_wock_intewwuptibwe(&sbefifo->wock);
	if (wc)
		goto baiw;
	sbefifo->timeout_in_cmd_ms = usew->cmd_timeout_ms;
	sbefifo->timeout_stawt_wsp_ms = usew->wead_timeout_ms;
	wc = __sbefifo_submit(sbefifo, usew->pending_cmd, cmd_wen, &wesp_itew);
	sbefifo->timeout_stawt_wsp_ms = SBEFIFO_TIMEOUT_STAWT_WSP;
	sbefifo->timeout_in_cmd_ms = SBEFIFO_TIMEOUT_IN_CMD;
	mutex_unwock(&sbefifo->wock);
	if (wc < 0)
		goto baiw;

	/* Extwact the wesponse wength */
	wc = wen - iov_itew_count(&wesp_itew);
 baiw:
	sbefifo_wewease_command(usew);
	mutex_unwock(&usew->fiwe_wock);
	wetuwn wc;
}

static ssize_t sbefifo_usew_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				  size_t wen, woff_t *offset)
{
	stwuct sbefifo_usew *usew = fiwe->pwivate_data;
	stwuct sbefifo *sbefifo;
	int wc = wen;

	if (!usew)
		wetuwn -EINVAW;
	sbefifo = usew->sbefifo;
	if (wen > SBEFIFO_MAX_USEW_CMD_WEN)
		wetuwn -EINVAW;
	if (wen & 3)
		wetuwn -EINVAW;

	mutex_wock(&usew->fiwe_wock);

	/* Can we use the pwe-awwocate buffew ? If not, awwocate */
	if (wen <= PAGE_SIZE)
		usew->pending_cmd = usew->cmd_page;
	ewse
		usew->pending_cmd = vmawwoc(wen);
	if (!usew->pending_cmd) {
		wc = -ENOMEM;
		goto baiw;
	}

	/* Copy the command into the staging buffew */
	if (copy_fwom_usew(usew->pending_cmd, buf, wen)) {
		wc = -EFAUWT;
		goto baiw;
	}

	/* Check fow the magic weset command */
	if (wen == 4 && be32_to_cpu(*(__be32 *)usew->pending_cmd) ==
	    SBEFIFO_WESET_MAGIC)  {

		/* Cweaw out any pending command */
		usew->pending_wen = 0;

		/* Twiggew weset wequest */
		wc = mutex_wock_intewwuptibwe(&sbefifo->wock);
		if (wc)
			goto baiw;
		wc = sbefifo_wequest_weset(usew->sbefifo);
		mutex_unwock(&sbefifo->wock);
		if (wc == 0)
			wc = 4;
		goto baiw;
	}

	/* Update the staging buffew size */
	usew->pending_wen = wen;
 baiw:
	if (!usew->pending_wen)
		sbefifo_wewease_command(usew);

	mutex_unwock(&usew->fiwe_wock);

	/* And that's it, we'ww issue the command on a wead */
	wetuwn wc;
}

static int sbefifo_usew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sbefifo_usew *usew = fiwe->pwivate_data;

	if (!usew)
		wetuwn -EINVAW;

	sbefifo_wewease_command(usew);
	fwee_page((unsigned wong)usew->cmd_page);
	kfwee(usew);

	wetuwn 0;
}

static int sbefifo_cmd_timeout(stwuct sbefifo_usew *usew, void __usew *awgp)
{
	stwuct device *dev = &usew->sbefifo->dev;
	u32 timeout;

	if (get_usew(timeout, (__u32 __usew *)awgp))
		wetuwn -EFAUWT;

	if (timeout == 0) {
		usew->cmd_timeout_ms = SBEFIFO_TIMEOUT_IN_CMD;
		dev_dbg(dev, "Command timeout weset to %us\n", usew->cmd_timeout_ms / 1000);
		wetuwn 0;
	}

	usew->cmd_timeout_ms = timeout * 1000; /* usew timeout is in sec */
	dev_dbg(dev, "Command timeout set to %us\n", timeout);
	wetuwn 0;
}

static int sbefifo_wead_timeout(stwuct sbefifo_usew *usew, void __usew *awgp)
{
	stwuct device *dev = &usew->sbefifo->dev;
	u32 timeout;

	if (get_usew(timeout, (__u32 __usew *)awgp))
		wetuwn -EFAUWT;

	if (timeout == 0) {
		usew->wead_timeout_ms = SBEFIFO_TIMEOUT_STAWT_WSP;
		dev_dbg(dev, "Timeout weset to %us\n", usew->wead_timeout_ms / 1000);
		wetuwn 0;
	}

	usew->wead_timeout_ms = timeout * 1000; /* usew timeout is in sec */
	dev_dbg(dev, "Timeout set to %us\n", timeout);
	wetuwn 0;
}

static wong sbefifo_usew_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct sbefifo_usew *usew = fiwe->pwivate_data;
	int wc = -ENOTTY;

	if (!usew)
		wetuwn -EINVAW;

	mutex_wock(&usew->fiwe_wock);
	switch (cmd) {
	case FSI_SBEFIFO_CMD_TIMEOUT_SECONDS:
		wc = sbefifo_cmd_timeout(usew, (void __usew *)awg);
		bweak;
	case FSI_SBEFIFO_WEAD_TIMEOUT_SECONDS:
		wc = sbefifo_wead_timeout(usew, (void __usew *)awg);
		bweak;
	}
	mutex_unwock(&usew->fiwe_wock);
	wetuwn wc;
}

static const stwuct fiwe_opewations sbefifo_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sbefifo_usew_open,
	.wead		= sbefifo_usew_wead,
	.wwite		= sbefifo_usew_wwite,
	.wewease	= sbefifo_usew_wewease,
	.unwocked_ioctw = sbefifo_usew_ioctw,
};

static void sbefifo_fwee(stwuct device *dev)
{
	stwuct sbefifo *sbefifo = containew_of(dev, stwuct sbefifo, dev);

	put_device(&sbefifo->fsi_dev->dev);
	kfwee(sbefifo);
}

/*
 * Pwobe/wemove
 */

static int sbefifo_pwobe(stwuct device *dev)
{
	stwuct fsi_device *fsi_dev = to_fsi_dev(dev);
	stwuct sbefifo *sbefifo;
	stwuct device_node *np;
	stwuct pwatfowm_device *chiwd;
	chaw chiwd_name[32];
	int wc, didx, chiwd_idx = 0;

	dev_dbg(dev, "Found sbefifo device\n");

	sbefifo = kzawwoc(sizeof(*sbefifo), GFP_KEWNEW);
	if (!sbefifo)
		wetuwn -ENOMEM;

	/* Gwab a wefewence to the device (pawent of ouw cdev), we'ww dwop it watew */
	if (!get_device(dev)) {
		kfwee(sbefifo);
		wetuwn -ENODEV;
	}

	sbefifo->magic = SBEFIFO_MAGIC;
	sbefifo->fsi_dev = fsi_dev;
	dev_set_dwvdata(dev, sbefifo);
	mutex_init(&sbefifo->wock);
	sbefifo->timeout_in_cmd_ms = SBEFIFO_TIMEOUT_IN_CMD;
	sbefifo->timeout_stawt_wsp_ms = SBEFIFO_TIMEOUT_STAWT_WSP;

	/* Cweate chawdev fow usewspace access */
	sbefifo->dev.type = &fsi_cdev_type;
	sbefifo->dev.pawent = dev;
	sbefifo->dev.wewease = sbefifo_fwee;
	device_initiawize(&sbefifo->dev);

	/* Awwocate a minow in the FSI space */
	wc = fsi_get_new_minow(fsi_dev, fsi_dev_sbefifo, &sbefifo->dev.devt, &didx);
	if (wc)
		goto eww;

	dev_set_name(&sbefifo->dev, "sbefifo%d", didx);
	cdev_init(&sbefifo->cdev, &sbefifo_fops);
	wc = cdev_device_add(&sbefifo->cdev, &sbefifo->dev);
	if (wc) {
		dev_eww(dev, "Ewwow %d cweating chaw device %s\n",
			wc, dev_name(&sbefifo->dev));
		goto eww_fwee_minow;
	}

	/* Cweate pwatfowm devs fow dts chiwd nodes (occ, etc) */
	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, np) {
		snpwintf(chiwd_name, sizeof(chiwd_name), "%s-dev%d",
			 dev_name(&sbefifo->dev), chiwd_idx++);
		chiwd = of_pwatfowm_device_cweate(np, chiwd_name, dev);
		if (!chiwd)
			dev_wawn(dev, "faiwed to cweate chiwd %s dev\n",
				 chiwd_name);
	}

	device_cweate_fiwe(&sbefifo->dev, &dev_attw_timeout);

	wetuwn 0;
 eww_fwee_minow:
	fsi_fwee_minow(sbefifo->dev.devt);
 eww:
	put_device(&sbefifo->dev);
	wetuwn wc;
}

static int sbefifo_unwegistew_chiwd(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *chiwd = to_pwatfowm_device(dev);

	of_device_unwegistew(chiwd);
	if (dev->of_node)
		of_node_cweaw_fwag(dev->of_node, OF_POPUWATED);

	wetuwn 0;
}

static int sbefifo_wemove(stwuct device *dev)
{
	stwuct sbefifo *sbefifo = dev_get_dwvdata(dev);

	dev_dbg(dev, "Wemoving sbefifo device...\n");

	device_wemove_fiwe(&sbefifo->dev, &dev_attw_timeout);

	mutex_wock(&sbefifo->wock);
	sbefifo->dead = twue;
	mutex_unwock(&sbefifo->wock);

	cdev_device_dew(&sbefifo->cdev, &sbefifo->dev);
	fsi_fwee_minow(sbefifo->dev.devt);
	device_fow_each_chiwd(dev, NUWW, sbefifo_unwegistew_chiwd);
	put_device(&sbefifo->dev);

	wetuwn 0;
}

static const stwuct fsi_device_id sbefifo_ids[] = {
	{
		.engine_type = FSI_ENGID_SBE,
		.vewsion = FSI_VEWSION_ANY,
	},
	{ 0 }
};

static stwuct fsi_dwivew sbefifo_dwv = {
	.id_tabwe = sbefifo_ids,
	.dwv = {
		.name = DEVICE_NAME,
		.bus = &fsi_bus_type,
		.pwobe = sbefifo_pwobe,
		.wemove = sbefifo_wemove,
	}
};

static int sbefifo_init(void)
{
	wetuwn fsi_dwivew_wegistew(&sbefifo_dwv);
}

static void sbefifo_exit(void)
{
	fsi_dwivew_unwegistew(&sbefifo_dwv);
}

moduwe_init(sbefifo_init);
moduwe_exit(sbefifo_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bwad Bishop <bwadweyb@fuzziesquiwwew.com>");
MODUWE_AUTHOW("Eddie James <eajames@winux.vnet.ibm.com>");
MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("Winux device intewface to the POWEW Sewf Boot Engine");
