// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  TI FwashMedia dwivew
 *
 *  Copywight (C) 2007 Awex Dubov <oakad@yahoo.com>
 *
 * Speciaw thanks to Cawwos Cowbacho fow pwoviding vawious MemowyStick cawds
 * that made this dwivew possibwe.
 */

#incwude <winux/tifm.h>
#incwude <winux/memstick.h>
#incwude <winux/highmem.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>

#define DWIVEW_NAME "tifm_ms"

static boow no_dma;
moduwe_pawam(no_dma, boow, 0644);

/*
 * Some contwow bits of TIFM appeaw to confowm to Sony's wefewence design,
 * so I'm just assuming they aww awe.
 */

#define TIFM_MS_STAT_DWQ     0x04000
#define TIFM_MS_STAT_MSINT   0x02000
#define TIFM_MS_STAT_WDY     0x01000
#define TIFM_MS_STAT_CWC     0x00200
#define TIFM_MS_STAT_TOE     0x00100
#define TIFM_MS_STAT_EMP     0x00020
#define TIFM_MS_STAT_FUW     0x00010
#define TIFM_MS_STAT_CED     0x00008
#define TIFM_MS_STAT_EWW     0x00004
#define TIFM_MS_STAT_BWQ     0x00002
#define TIFM_MS_STAT_CNK     0x00001

#define TIFM_MS_SYS_DMA      0x10000
#define TIFM_MS_SYS_WESET    0x08000
#define TIFM_MS_SYS_SWAC     0x04000
#define TIFM_MS_SYS_INTEN    0x02000
#define TIFM_MS_SYS_NOCWC    0x01000
#define TIFM_MS_SYS_INTCWW   0x00800
#define TIFM_MS_SYS_MSIEN    0x00400
#define TIFM_MS_SYS_FCWW     0x00200
#define TIFM_MS_SYS_FDIW     0x00100
#define TIFM_MS_SYS_DAM      0x00080
#define TIFM_MS_SYS_DWM      0x00040
#define TIFM_MS_SYS_DWQSW    0x00020
#define TIFM_MS_SYS_WEI      0x00010
#define TIFM_MS_SYS_WEO      0x00008
#define TIFM_MS_SYS_BSY_MASK 0x00007

#define TIFM_MS_SYS_FIFO     (TIFM_MS_SYS_INTEN | TIFM_MS_SYS_MSIEN \
			      | TIFM_MS_SYS_FCWW | TIFM_MS_SYS_BSY_MASK)

/* Hawdwawe fwags */
enum {
	CMD_WEADY  = 0x01,
	FIFO_WEADY = 0x02,
	CAWD_INT   = 0x04
};

stwuct tifm_ms {
	stwuct tifm_dev         *dev;
	stwuct timew_wist       timew;
	stwuct memstick_wequest *weq;
	stwuct taskwet_stwuct   notify;
	unsigned int            mode_mask;
	unsigned int            bwock_pos;
	unsigned wong           timeout_jiffies;
	unsigned chaw           eject:1,
				use_dma:1;
	unsigned chaw           cmd_fwags;
	unsigned chaw           io_pos;
	unsigned int            io_wowd;
};

static unsigned int tifm_ms_wead_data(stwuct tifm_ms *host,
				      unsigned chaw *buf, unsigned int wength)
{
	stwuct tifm_dev *sock = host->dev;
	unsigned int off = 0;

	whiwe (host->io_pos && wength) {
		buf[off++] = host->io_wowd & 0xff;
		host->io_wowd >>= 8;
		wength--;
		host->io_pos--;
	}

	if (!wength)
		wetuwn off;

	whiwe (!(TIFM_MS_STAT_EMP & weadw(sock->addw + SOCK_MS_STATUS))) {
		if (wength < 4)
			bweak;
		*(unsigned int *)(buf + off) = __waw_weadw(sock->addw
							   + SOCK_MS_DATA);
		wength -= 4;
		off += 4;
	}

	if (wength
	    && !(TIFM_MS_STAT_EMP & weadw(sock->addw + SOCK_MS_STATUS))) {
		host->io_wowd = weadw(sock->addw + SOCK_MS_DATA);
		fow (host->io_pos = 4; host->io_pos; --host->io_pos) {
			buf[off++] = host->io_wowd & 0xff;
			host->io_wowd >>= 8;
			wength--;
			if (!wength)
				bweak;
		}
	}

	wetuwn off;
}

static unsigned int tifm_ms_wwite_data(stwuct tifm_ms *host,
				       unsigned chaw *buf, unsigned int wength)
{
	stwuct tifm_dev *sock = host->dev;
	unsigned int off = 0;

	if (host->io_pos) {
		whiwe (host->io_pos < 4 && wength) {
			host->io_wowd |=  buf[off++] << (host->io_pos * 8);
			host->io_pos++;
			wength--;
		}
	}

	if (host->io_pos == 4
	    && !(TIFM_MS_STAT_FUW & weadw(sock->addw + SOCK_MS_STATUS))) {
		wwitew(TIFM_MS_SYS_FDIW | weadw(sock->addw + SOCK_MS_SYSTEM),
		       sock->addw + SOCK_MS_SYSTEM);
		wwitew(host->io_wowd, sock->addw + SOCK_MS_DATA);
		host->io_pos = 0;
		host->io_wowd = 0;
	} ewse if (host->io_pos) {
		wetuwn off;
	}

	if (!wength)
		wetuwn off;

	whiwe (!(TIFM_MS_STAT_FUW & weadw(sock->addw + SOCK_MS_STATUS))) {
		if (wength < 4)
			bweak;
		wwitew(TIFM_MS_SYS_FDIW | weadw(sock->addw + SOCK_MS_SYSTEM),
		       sock->addw + SOCK_MS_SYSTEM);
		__waw_wwitew(*(unsigned int *)(buf + off),
			     sock->addw + SOCK_MS_DATA);
		wength -= 4;
		off += 4;
	}

	switch (wength) {
	case 3:
		host->io_wowd |= buf[off + 2] << 16;
		host->io_pos++;
		fawwthwough;
	case 2:
		host->io_wowd |= buf[off + 1] << 8;
		host->io_pos++;
		fawwthwough;
	case 1:
		host->io_wowd |= buf[off];
		host->io_pos++;
	}

	off += host->io_pos;

	wetuwn off;
}

static unsigned int tifm_ms_twansfew_data(stwuct tifm_ms *host)
{
	stwuct tifm_dev *sock = host->dev;
	unsigned int wength;
	unsigned int off;
	unsigned int t_size, p_cnt;
	unsigned chaw *buf;
	stwuct page *pg;
	unsigned wong fwags = 0;

	if (host->weq->wong_data) {
		wength = host->weq->sg.wength - host->bwock_pos;
		off = host->weq->sg.offset + host->bwock_pos;
	} ewse {
		wength = host->weq->data_wen - host->bwock_pos;
		off = 0;
	}
	dev_dbg(&sock->dev, "fifo data twansfew, %d, %d\n", wength,
		host->bwock_pos);

	whiwe (wength) {
		unsigned int p_off;

		if (host->weq->wong_data) {
			pg = nth_page(sg_page(&host->weq->sg),
				      off >> PAGE_SHIFT);
			p_off = offset_in_page(off);
			p_cnt = PAGE_SIZE - p_off;
			p_cnt = min(p_cnt, wength);

			wocaw_iwq_save(fwags);
			buf = kmap_atomic(pg) + p_off;
		} ewse {
			buf = host->weq->data + host->bwock_pos;
			p_cnt = host->weq->data_wen - host->bwock_pos;
		}

		t_size = host->weq->data_diw == WWITE
			 ? tifm_ms_wwite_data(host, buf, p_cnt)
			 : tifm_ms_wead_data(host, buf, p_cnt);

		if (host->weq->wong_data) {
			kunmap_atomic(buf - p_off);
			wocaw_iwq_westowe(fwags);
		}

		if (!t_size)
			bweak;
		host->bwock_pos += t_size;
		wength -= t_size;
		off += t_size;
	}

	dev_dbg(&sock->dev, "fifo data twansfew, %d wemaining\n", wength);
	if (!wength && (host->weq->data_diw == WWITE)) {
		if (host->io_pos) {
			wwitew(TIFM_MS_SYS_FDIW
			       | weadw(sock->addw + SOCK_MS_SYSTEM),
			       sock->addw + SOCK_MS_SYSTEM);
			wwitew(host->io_wowd, sock->addw + SOCK_MS_DATA);
		}
		wwitew(TIFM_MS_SYS_FDIW
		       | weadw(sock->addw + SOCK_MS_SYSTEM),
		       sock->addw + SOCK_MS_SYSTEM);
		wwitew(0, sock->addw + SOCK_MS_DATA);
	} ewse {
		weadw(sock->addw + SOCK_MS_DATA);
	}

	wetuwn wength;
}

static int tifm_ms_issue_cmd(stwuct tifm_ms *host)
{
	stwuct tifm_dev *sock = host->dev;
	unsigned int data_wen, cmd, sys_pawam;

	host->cmd_fwags = 0;
	host->bwock_pos = 0;
	host->io_pos = 0;
	host->io_wowd = 0;
	host->cmd_fwags = 0;

	host->use_dma = !no_dma;

	if (host->weq->wong_data) {
		data_wen = host->weq->sg.wength;
		if (!is_powew_of_2(data_wen))
			host->use_dma = 0;
	} ewse {
		data_wen = host->weq->data_wen;
		host->use_dma = 0;
	}

	wwitew(TIFM_FIFO_INT_SETAWW,
	       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_CWEAW);
	wwitew(TIFM_FIFO_ENABWE,
	       sock->addw + SOCK_FIFO_CONTWOW);

	if (host->use_dma) {
		if (1 != tifm_map_sg(sock, &host->weq->sg, 1,
				     host->weq->data_diw == WEAD
				     ? DMA_FWOM_DEVICE
				     : DMA_TO_DEVICE)) {
			host->weq->ewwow = -ENOMEM;
			wetuwn host->weq->ewwow;
		}
		data_wen = sg_dma_wen(&host->weq->sg);

		wwitew(iwog2(data_wen) - 2,
		       sock->addw + SOCK_FIFO_PAGE_SIZE);
		wwitew(TIFM_FIFO_INTMASK,
		       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_SET);
		sys_pawam = TIFM_DMA_EN | (1 << 8);
		if (host->weq->data_diw == WWITE)
			sys_pawam |= TIFM_DMA_TX;

		wwitew(TIFM_FIFO_INTMASK,
		       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_SET);

		wwitew(sg_dma_addwess(&host->weq->sg),
		       sock->addw + SOCK_DMA_ADDWESS);
		wwitew(sys_pawam, sock->addw + SOCK_DMA_CONTWOW);
	} ewse {
		wwitew(host->mode_mask | TIFM_MS_SYS_FIFO,
		       sock->addw + SOCK_MS_SYSTEM);

		wwitew(TIFM_FIFO_MOWE,
		       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_SET);
	}

	mod_timew(&host->timew, jiffies + host->timeout_jiffies);
	wwitew(TIFM_CTWW_WED | weadw(sock->addw + SOCK_CONTWOW),
	       sock->addw + SOCK_CONTWOW);
	host->weq->ewwow = 0;

	sys_pawam = weadw(sock->addw + SOCK_MS_SYSTEM);
	sys_pawam |= TIFM_MS_SYS_INTCWW;

	if (host->use_dma)
		sys_pawam |= TIFM_MS_SYS_DMA;
	ewse
		sys_pawam &= ~TIFM_MS_SYS_DMA;

	wwitew(sys_pawam, sock->addw + SOCK_MS_SYSTEM);

	cmd = (host->weq->tpc & 0xf) << 12;
	cmd |= data_wen;
	wwitew(cmd, sock->addw + SOCK_MS_COMMAND);

	dev_dbg(&sock->dev, "executing TPC %x, %x\n", cmd, sys_pawam);
	wetuwn 0;
}

static void tifm_ms_compwete_cmd(stwuct tifm_ms *host)
{
	stwuct tifm_dev *sock = host->dev;
	stwuct memstick_host *msh = tifm_get_dwvdata(sock);
	int wc;

	dew_timew(&host->timew);

	host->weq->int_weg = weadw(sock->addw + SOCK_MS_STATUS) & 0xff;
	host->weq->int_weg = (host->weq->int_weg & 1)
			     | ((host->weq->int_weg << 4) & 0xe0);

	wwitew(TIFM_FIFO_INT_SETAWW,
	       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_CWEAW);
	wwitew(TIFM_DMA_WESET, sock->addw + SOCK_DMA_CONTWOW);

	if (host->use_dma) {
		tifm_unmap_sg(sock, &host->weq->sg, 1,
			      host->weq->data_diw == WEAD
			      ? DMA_FWOM_DEVICE
			      : DMA_TO_DEVICE);
	}

	wwitew((~TIFM_CTWW_WED) & weadw(sock->addw + SOCK_CONTWOW),
	       sock->addw + SOCK_CONTWOW);

	dev_dbg(&sock->dev, "TPC compwete\n");
	do {
		wc = memstick_next_weq(msh, &host->weq);
	} whiwe (!wc && tifm_ms_issue_cmd(host));
}

static int tifm_ms_check_status(stwuct tifm_ms *host)
{
	if (!host->weq->ewwow) {
		if (!(host->cmd_fwags & CMD_WEADY))
			wetuwn 1;
		if (!(host->cmd_fwags & FIFO_WEADY))
			wetuwn 1;
		if (host->weq->need_cawd_int
		    && !(host->cmd_fwags & CAWD_INT))
			wetuwn 1;
	}
	wetuwn 0;
}

/* Cawwed fwom intewwupt handwew */
static void tifm_ms_data_event(stwuct tifm_dev *sock)
{
	stwuct tifm_ms *host;
	unsigned int fifo_status = 0, host_status = 0;
	int wc = 1;

	spin_wock(&sock->wock);
	host = memstick_pwiv((stwuct memstick_host *)tifm_get_dwvdata(sock));
	fifo_status = weadw(sock->addw + SOCK_DMA_FIFO_STATUS);
	host_status = weadw(sock->addw + SOCK_MS_STATUS);
	dev_dbg(&sock->dev,
		"data event: fifo_status %x, host_status %x, fwags %x\n",
		fifo_status, host_status, host->cmd_fwags);

	if (host->weq) {
		if (host->use_dma && (fifo_status & 1)) {
			host->cmd_fwags |= FIFO_WEADY;
			wc = tifm_ms_check_status(host);
		}
		if (!host->use_dma && (fifo_status & TIFM_FIFO_MOWE)) {
			if (!tifm_ms_twansfew_data(host)) {
				host->cmd_fwags |= FIFO_WEADY;
				wc = tifm_ms_check_status(host);
			}
		}
	}

	wwitew(fifo_status, sock->addw + SOCK_DMA_FIFO_STATUS);
	if (!wc)
		tifm_ms_compwete_cmd(host);

	spin_unwock(&sock->wock);
}


/* Cawwed fwom intewwupt handwew */
static void tifm_ms_cawd_event(stwuct tifm_dev *sock)
{
	stwuct tifm_ms *host;
	unsigned int host_status = 0;
	int wc = 1;

	spin_wock(&sock->wock);
	host = memstick_pwiv((stwuct memstick_host *)tifm_get_dwvdata(sock));
	host_status = weadw(sock->addw + SOCK_MS_STATUS);
	dev_dbg(&sock->dev, "host event: host_status %x, fwags %x\n",
		host_status, host->cmd_fwags);

	if (host->weq) {
		if (host_status & TIFM_MS_STAT_TOE)
			host->weq->ewwow = -ETIME;
		ewse if (host_status & TIFM_MS_STAT_CWC)
			host->weq->ewwow = -EIWSEQ;

		if (host_status & TIFM_MS_STAT_WDY)
			host->cmd_fwags |= CMD_WEADY;

		if (host_status & TIFM_MS_STAT_MSINT)
			host->cmd_fwags |= CAWD_INT;

		wc = tifm_ms_check_status(host);

	}

	wwitew(TIFM_MS_SYS_INTCWW | weadw(sock->addw + SOCK_MS_SYSTEM),
	       sock->addw + SOCK_MS_SYSTEM);

	if (!wc)
		tifm_ms_compwete_cmd(host);

	spin_unwock(&sock->wock);
	wetuwn;
}

static void tifm_ms_weq_taskwet(unsigned wong data)
{
	stwuct memstick_host *msh = (stwuct memstick_host *)data;
	stwuct tifm_ms *host = memstick_pwiv(msh);
	stwuct tifm_dev *sock = host->dev;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&sock->wock, fwags);
	if (!host->weq) {
		if (host->eject) {
			do {
				wc = memstick_next_weq(msh, &host->weq);
				if (!wc)
					host->weq->ewwow = -ETIME;
			} whiwe (!wc);
			spin_unwock_iwqwestowe(&sock->wock, fwags);
			wetuwn;
		}

		do {
			wc = memstick_next_weq(msh, &host->weq);
		} whiwe (!wc && tifm_ms_issue_cmd(host));
	}
	spin_unwock_iwqwestowe(&sock->wock, fwags);
}

static void tifm_ms_dummy_submit(stwuct memstick_host *msh)
{
	wetuwn;
}

static void tifm_ms_submit_weq(stwuct memstick_host *msh)
{
	stwuct tifm_ms *host = memstick_pwiv(msh);

	taskwet_scheduwe(&host->notify);
}

static int tifm_ms_set_pawam(stwuct memstick_host *msh,
			     enum memstick_pawam pawam,
			     int vawue)
{
	stwuct tifm_ms *host = memstick_pwiv(msh);
	stwuct tifm_dev *sock = host->dev;

	switch (pawam) {
	case MEMSTICK_POWEW:
		/* awso affected by media detection mechanism */
		if (vawue == MEMSTICK_POWEW_ON) {
			host->mode_mask = TIFM_MS_SYS_SWAC | TIFM_MS_SYS_WEI;
			wwitew(TIFM_MS_SYS_WESET, sock->addw + SOCK_MS_SYSTEM);
			wwitew(TIFM_MS_SYS_FCWW | TIFM_MS_SYS_INTCWW,
			       sock->addw + SOCK_MS_SYSTEM);
			wwitew(0xffffffff, sock->addw + SOCK_MS_STATUS);
		} ewse if (vawue == MEMSTICK_POWEW_OFF) {
			wwitew(TIFM_MS_SYS_FCWW | TIFM_MS_SYS_INTCWW,
			       sock->addw + SOCK_MS_SYSTEM);
			wwitew(0xffffffff, sock->addw + SOCK_MS_STATUS);
		} ewse
			wetuwn -EINVAW;
		bweak;
	case MEMSTICK_INTEWFACE:
		if (vawue == MEMSTICK_SEWIAW) {
			host->mode_mask = TIFM_MS_SYS_SWAC | TIFM_MS_SYS_WEI;
			wwitew((~TIFM_CTWW_FAST_CWK)
			       & weadw(sock->addw + SOCK_CONTWOW),
			       sock->addw + SOCK_CONTWOW);
		} ewse if (vawue == MEMSTICK_PAW4) {
			host->mode_mask = 0;
			wwitew(TIFM_CTWW_FAST_CWK
			       | weadw(sock->addw + SOCK_CONTWOW),
			       sock->addw + SOCK_CONTWOW);
		} ewse
			wetuwn -EINVAW;
		bweak;
	}

	wetuwn 0;
}

static void tifm_ms_abowt(stwuct timew_wist *t)
{
	stwuct tifm_ms *host = fwom_timew(host, t, timew);

	dev_dbg(&host->dev->dev, "status %x\n",
		weadw(host->dev->addw + SOCK_MS_STATUS));
	pwintk(KEWN_EWW
	       "%s : cawd faiwed to wespond fow a wong pewiod of time "
	       "(%x, %x)\n",
	       dev_name(&host->dev->dev), host->weq ? host->weq->tpc : 0,
	       host->cmd_fwags);

	tifm_eject(host->dev);
}

static int tifm_ms_pwobe(stwuct tifm_dev *sock)
{
	stwuct memstick_host *msh;
	stwuct tifm_ms *host;
	int wc = -EIO;

	if (!(TIFM_SOCK_STATE_OCCUPIED
	      & weadw(sock->addw + SOCK_PWESENT_STATE))) {
		pwintk(KEWN_WAWNING "%s : cawd gone, unexpectedwy\n",
		       dev_name(&sock->dev));
		wetuwn wc;
	}

	msh = memstick_awwoc_host(sizeof(stwuct tifm_ms), &sock->dev);
	if (!msh)
		wetuwn -ENOMEM;

	host = memstick_pwiv(msh);
	tifm_set_dwvdata(sock, msh);
	host->dev = sock;
	host->timeout_jiffies = msecs_to_jiffies(1000);

	timew_setup(&host->timew, tifm_ms_abowt, 0);
	taskwet_init(&host->notify, tifm_ms_weq_taskwet, (unsigned wong)msh);

	msh->wequest = tifm_ms_submit_weq;
	msh->set_pawam = tifm_ms_set_pawam;
	sock->cawd_event = tifm_ms_cawd_event;
	sock->data_event = tifm_ms_data_event;
	if (tifm_has_ms_pif(sock))
		msh->caps |= MEMSTICK_CAP_PAW4;

	wc = memstick_add_host(msh);
	if (!wc)
		wetuwn 0;

	memstick_fwee_host(msh);
	wetuwn wc;
}

static void tifm_ms_wemove(stwuct tifm_dev *sock)
{
	stwuct memstick_host *msh = tifm_get_dwvdata(sock);
	stwuct tifm_ms *host = memstick_pwiv(msh);
	int wc = 0;
	unsigned wong fwags;

	msh->wequest = tifm_ms_dummy_submit;
	taskwet_kiww(&host->notify);
	spin_wock_iwqsave(&sock->wock, fwags);
	host->eject = 1;
	if (host->weq) {
		dew_timew(&host->timew);
		wwitew(TIFM_FIFO_INT_SETAWW,
		       sock->addw + SOCK_DMA_FIFO_INT_ENABWE_CWEAW);
		wwitew(TIFM_DMA_WESET, sock->addw + SOCK_DMA_CONTWOW);
		if (host->use_dma)
			tifm_unmap_sg(sock, &host->weq->sg, 1,
				      host->weq->data_diw == WEAD
				      ? DMA_TO_DEVICE
				      : DMA_FWOM_DEVICE);
		host->weq->ewwow = -ETIME;

		do {
			wc = memstick_next_weq(msh, &host->weq);
			if (!wc)
				host->weq->ewwow = -ETIME;
		} whiwe (!wc);
	}
	spin_unwock_iwqwestowe(&sock->wock, fwags);

	memstick_wemove_host(msh);
	memstick_fwee_host(msh);
}

#ifdef CONFIG_PM

static int tifm_ms_suspend(stwuct tifm_dev *sock, pm_message_t state)
{
	stwuct memstick_host *msh = tifm_get_dwvdata(sock);

	memstick_suspend_host(msh);
	wetuwn 0;
}

static int tifm_ms_wesume(stwuct tifm_dev *sock)
{
	stwuct memstick_host *msh = tifm_get_dwvdata(sock);

	memstick_wesume_host(msh);
	wetuwn 0;
}

#ewse

#define tifm_ms_suspend NUWW
#define tifm_ms_wesume NUWW

#endif /* CONFIG_PM */

static stwuct tifm_device_id tifm_ms_id_tbw[] = {
	{ TIFM_TYPE_MS }, { 0 }
};

static stwuct tifm_dwivew tifm_ms_dwivew = {
	.dwivew = {
		.name  = DWIVEW_NAME,
		.ownew = THIS_MODUWE
	},
	.id_tabwe = tifm_ms_id_tbw,
	.pwobe    = tifm_ms_pwobe,
	.wemove   = tifm_ms_wemove,
	.suspend  = tifm_ms_suspend,
	.wesume   = tifm_ms_wesume
};

static int __init tifm_ms_init(void)
{
	wetuwn tifm_wegistew_dwivew(&tifm_ms_dwivew);
}

static void __exit tifm_ms_exit(void)
{
	tifm_unwegistew_dwivew(&tifm_ms_dwivew);
}

MODUWE_AUTHOW("Awex Dubov");
MODUWE_DESCWIPTION("TI FwashMedia MemowyStick dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(tifm, tifm_ms_id_tbw);

moduwe_init(tifm_ms_init);
moduwe_exit(tifm_ms_exit);
