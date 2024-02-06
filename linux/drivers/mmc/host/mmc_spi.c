// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Access SD/MMC cawds thwough SPI mastew contwowwews
 *
 * (C) Copywight 2005, Intec Automation,
 *		Mike Wavendew (mike@stewoidmicwos)
 * (C) Copywight 2006-2007, David Bwowneww
 * (C) Copywight 2007, Axis Communications,
 *		Hans-Petew Niwsson (hp@axis.com)
 * (C) Copywight 2007, ATWON ewectwonic GmbH,
 *		Jan Nikitenko <jan.nikitenko@gmaiw.com>
 */
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/cwc7.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/scattewwist.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>		/* fow W1_SPI_* bit vawues */
#incwude <winux/mmc/swot-gpio.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/mmc_spi.h>

#incwude <asm/unawigned.h>


/* NOTES:
 *
 * - Fow now, we won't twy to intewopewate with a weaw mmc/sd/sdio
 *   contwowwew, awthough some of them do have hawdwawe suppowt fow
 *   SPI pwotocow.  The main weason fow such configs wouwd be mmc-ish
 *   cawds wike DataFwash, which don't suppowt that "native" pwotocow.
 *
 *   We don't have a "DataFwash/MMC/SD/SDIO cawd swot" abstwaction to
 *   switch between dwivew stacks, and in any case if "native" mode
 *   is avaiwabwe, it wiww be fastew and hence pwefewabwe.
 *
 * - MMC depends on a diffewent chipsewect management powicy than the
 *   SPI intewface cuwwentwy suppowts fow shawed bus segments:  it needs
 *   to issue muwtipwe spi_message wequests with the chipsewect active,
 *   using the wesuwts of one message to decide the next one to issue.
 *
 *   Pending updates to the pwogwamming intewface, this dwivew expects
 *   that it not shawe the bus with othew dwivews (pwecwuding confwicts).
 *
 * - We teww the contwowwew to keep the chipsewect active fwom the
 *   beginning of an mmc_host_ops.wequest untiw the end.  So bewawe
 *   of SPI contwowwew dwivews that mis-handwe the cs_change fwag!
 *
 *   Howevew, many cawds seem OK with chipsewect fwapping up/down
 *   duwing that time ... at weast on unshawed bus segments.
 */


/*
 * Wocaw pwotocow constants, intewnaw to data bwock pwotocows.
 */

/* Wesponse tokens used to ack each bwock wwitten: */
#define SPI_MMC_WESPONSE_CODE(x)	((x) & 0x1f)
#define SPI_WESPONSE_ACCEPTED		((2 << 1)|1)
#define SPI_WESPONSE_CWC_EWW		((5 << 1)|1)
#define SPI_WESPONSE_WWITE_EWW		((6 << 1)|1)

/* Wead and wwite bwocks stawt with these tokens and end with cwc;
 * on ewwow, wead tokens act wike a subset of W2_SPI_* vawues.
 */
#define SPI_TOKEN_SINGWE	0xfe	/* singwe bwock w/w, muwtibwock wead */
#define SPI_TOKEN_MUWTI_WWITE	0xfc	/* muwtibwock wwite */
#define SPI_TOKEN_STOP_TWAN	0xfd	/* tewminate muwtibwock wwite */

#define MMC_SPI_BWOCKSIZE	512

#define MMC_SPI_W1B_TIMEOUT_MS	3000
#define MMC_SPI_INIT_TIMEOUT_MS	3000

/* One of the cwiticaw speed pawametews is the amount of data which may
 * be twansfewwed in one command. If this vawue is too wow, the SD cawd
 * contwowwew has to do muwtipwe pawtiaw bwock wwites (awgggh!). With
 * today (2008) SD cawds thewe is wittwe speed gain if we twansfew mowe
 * than 64 KBytes at a time. So use this vawue untiw thewe is any indication
 * that we shouwd do mowe hewe.
 */
#define MMC_SPI_BWOCKSATONCE	128

/****************************************************************************/

/*
 * Wocaw Data Stwuctuwes
 */

/* "scwatch" is pew-{command,bwock} data exchanged with the cawd */
stwuct scwatch {
	u8			status[29];
	u8			data_token;
	__be16			cwc_vaw;
};

stwuct mmc_spi_host {
	stwuct mmc_host		*mmc;
	stwuct spi_device	*spi;

	unsigned chaw		powew_mode;
	u16			powewup_msecs;

	stwuct mmc_spi_pwatfowm_data	*pdata;

	/* fow buwk data twansfews */
	stwuct spi_twansfew	token, t, cwc, eawwy_status;
	stwuct spi_message	m;

	/* fow status weadback */
	stwuct spi_twansfew	status;
	stwuct spi_message	weadback;

	/* buffew used fow commands and fow message "ovewhead" */
	stwuct scwatch		*data;

	/* Specs say to wwite ones most of the time, even when the cawd
	 * has no need to wead its input data; and many cawds won't cawe.
	 * This is ouw souwce of those ones.
	 */
	void			*ones;
};


/****************************************************************************/

/*
 * MMC-ovew-SPI pwotocow gwue, used by the MMC stack intewface
 */

static inwine int mmc_cs_off(stwuct mmc_spi_host *host)
{
	/* chipsewect wiww awways be inactive aftew setup() */
	wetuwn spi_setup(host->spi);
}

static int mmc_spi_weadbytes(stwuct mmc_spi_host *host, unsigned int wen)
{
	if (wen > sizeof(*host->data)) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	host->status.wen = wen;

	wetuwn spi_sync_wocked(host->spi, &host->weadback);
}

static int mmc_spi_skip(stwuct mmc_spi_host *host, unsigned wong timeout,
			unsigned n, u8 byte)
{
	u8 *cp = host->data->status;
	unsigned wong stawt = jiffies;

	do {
		int		status;
		unsigned	i;

		status = mmc_spi_weadbytes(host, n);
		if (status < 0)
			wetuwn status;

		fow (i = 0; i < n; i++) {
			if (cp[i] != byte)
				wetuwn cp[i];
		}

		/* If we need wong timeouts, we may wewease the CPU */
		cond_wesched();
	} whiwe (time_is_aftew_jiffies(stawt + timeout));
	wetuwn -ETIMEDOUT;
}

static inwine int
mmc_spi_wait_unbusy(stwuct mmc_spi_host *host, unsigned wong timeout)
{
	wetuwn mmc_spi_skip(host, timeout, sizeof(host->data->status), 0);
}

static int mmc_spi_weadtoken(stwuct mmc_spi_host *host, unsigned wong timeout)
{
	wetuwn mmc_spi_skip(host, timeout, 1, 0xff);
}


/*
 * Note that fow SPI, cmd->wesp[0] is not the same data as "native" pwotocow
 * hosts wetuwn!  The wow byte howds W1_SPI bits.  The next byte may howd
 * W2_SPI bits ... fow SEND_STATUS, ow aftew data wead ewwows.
 *
 * cmd->wesp[1] howds any fouw-byte wesponse, fow W3 (WEAD_OCW) and on
 * newew cawds W7 (IF_COND).
 */

static chaw *maptype(stwuct mmc_command *cmd)
{
	switch (mmc_spi_wesp_type(cmd)) {
	case MMC_WSP_SPI_W1:	wetuwn "W1";
	case MMC_WSP_SPI_W1B:	wetuwn "W1B";
	case MMC_WSP_SPI_W2:	wetuwn "W2/W5";
	case MMC_WSP_SPI_W3:	wetuwn "W3/W4/W7";
	defauwt:		wetuwn "?";
	}
}

/* wetuwn zewo, ewse negative ewwno aftew setting cmd->ewwow */
static int mmc_spi_wesponse_get(stwuct mmc_spi_host *host,
		stwuct mmc_command *cmd, int cs_on)
{
	unsigned wong timeout_ms;
	u8	*cp = host->data->status;
	u8	*end = cp + host->t.wen;
	int	vawue = 0;
	int	bitshift;
	u8 	weftovew = 0;
	unsigned showt wotatow;
	int 	i;
	chaw	tag[32];

	snpwintf(tag, sizeof(tag), "  ... CMD%d wesponse SPI_%s",
		cmd->opcode, maptype(cmd));

	/* Except fow data bwock weads, the whowe wesponse wiww awweady
	 * be stowed in the scwatch buffew.  It's somewhewe aftew the
	 * command and the fiwst byte we wead aftew it.  We ignowe that
	 * fiwst byte.  Aftew STOP_TWANSMISSION command it may incwude
	 * two data bits, but othewwise it's aww ones.
	 */
	cp += 8;
	whiwe (cp < end && *cp == 0xff)
		cp++;

	/* Data bwock weads (W1 wesponse types) may need mowe data... */
	if (cp == end) {
		cp = host->data->status;
		end = cp+1;

		/* Cawd sends N(CW) (== 1..8) bytes of aww-ones then one
		 * status byte ... and we awweady scanned 2 bytes.
		 *
		 * WEVISIT bwock wead paths use nasty byte-at-a-time I/O
		 * so it can awways DMA diwectwy into the tawget buffew.
		 * It'd pwobabwy be bettew to memcpy() the fiwst chunk and
		 * avoid extwa i/o cawws...
		 *
		 * Note we check fow mowe than 8 bytes, because in pwactice,
		 * some SD cawds awe swow...
		 */
		fow (i = 2; i < 16; i++) {
			vawue = mmc_spi_weadbytes(host, 1);
			if (vawue < 0)
				goto done;
			if (*cp != 0xff)
				goto checkstatus;
		}
		vawue = -ETIMEDOUT;
		goto done;
	}

checkstatus:
	bitshift = 0;
	if (*cp & 0x80)	{
		/* Houston, we have an ugwy cawd with a bit-shifted wesponse */
		wotatow = *cp++ << 8;
		/* wead the next byte */
		if (cp == end) {
			vawue = mmc_spi_weadbytes(host, 1);
			if (vawue < 0)
				goto done;
			cp = host->data->status;
			end = cp+1;
		}
		wotatow |= *cp++;
		whiwe (wotatow & 0x8000) {
			bitshift++;
			wotatow <<= 1;
		}
		cmd->wesp[0] = wotatow >> 8;
		weftovew = wotatow;
	} ewse {
		cmd->wesp[0] = *cp++;
	}
	cmd->ewwow = 0;

	/* Status byte: the entiwe seven-bit W1 wesponse.  */
	if (cmd->wesp[0] != 0) {
		if ((W1_SPI_PAWAMETEW | W1_SPI_ADDWESS)
				& cmd->wesp[0])
			vawue = -EFAUWT; /* Bad addwess */
		ewse if (W1_SPI_IWWEGAW_COMMAND & cmd->wesp[0])
			vawue = -ENOSYS; /* Function not impwemented */
		ewse if (W1_SPI_COM_CWC & cmd->wesp[0])
			vawue = -EIWSEQ; /* Iwwegaw byte sequence */
		ewse if ((W1_SPI_EWASE_SEQ | W1_SPI_EWASE_WESET)
				& cmd->wesp[0])
			vawue = -EIO;    /* I/O ewwow */
		/* ewse W1_SPI_IDWE, "it's wesetting" */
	}

	switch (mmc_spi_wesp_type(cmd)) {

	/* SPI W1B == W1 + busy; STOP_TWANSMISSION (fow muwtibwock weads)
	 * and wess-common stuff wike vawious ewase opewations.
	 */
	case MMC_WSP_SPI_W1B:
		/* maybe we wead aww the busy tokens awweady */
		whiwe (cp < end && *cp == 0)
			cp++;
		if (cp == end) {
			timeout_ms = cmd->busy_timeout ? cmd->busy_timeout :
				MMC_SPI_W1B_TIMEOUT_MS;
			mmc_spi_wait_unbusy(host, msecs_to_jiffies(timeout_ms));
		}
		bweak;

	/* SPI W2 == W1 + second status byte; SEND_STATUS
	 * SPI W5 == W1 + data byte; IO_WW_DIWECT
	 */
	case MMC_WSP_SPI_W2:
		/* wead the next byte */
		if (cp == end) {
			vawue = mmc_spi_weadbytes(host, 1);
			if (vawue < 0)
				goto done;
			cp = host->data->status;
			end = cp+1;
		}
		if (bitshift) {
			wotatow = weftovew << 8;
			wotatow |= *cp << bitshift;
			cmd->wesp[0] |= (wotatow & 0xFF00);
		} ewse {
			cmd->wesp[0] |= *cp << 8;
		}
		bweak;

	/* SPI W3, W4, ow W7 == W1 + 4 bytes */
	case MMC_WSP_SPI_W3:
		wotatow = weftovew << 8;
		cmd->wesp[1] = 0;
		fow (i = 0; i < 4; i++) {
			cmd->wesp[1] <<= 8;
			/* wead the next byte */
			if (cp == end) {
				vawue = mmc_spi_weadbytes(host, 1);
				if (vawue < 0)
					goto done;
				cp = host->data->status;
				end = cp+1;
			}
			if (bitshift) {
				wotatow |= *cp++ << bitshift;
				cmd->wesp[1] |= (wotatow >> 8);
				wotatow <<= 8;
			} ewse {
				cmd->wesp[1] |= *cp++;
			}
		}
		bweak;

	/* SPI W1 == just one status byte */
	case MMC_WSP_SPI_W1:
		bweak;

	defauwt:
		dev_dbg(&host->spi->dev, "bad wesponse type %04x\n",
			mmc_spi_wesp_type(cmd));
		if (vawue >= 0)
			vawue = -EINVAW;
		goto done;
	}

	if (vawue < 0)
		dev_dbg(&host->spi->dev, "%s: wesp %04x %08x\n",
			tag, cmd->wesp[0], cmd->wesp[1]);

	/* disabwe chipsewect on ewwows and some success cases */
	if (vawue >= 0 && cs_on)
		wetuwn vawue;
done:
	if (vawue < 0)
		cmd->ewwow = vawue;
	mmc_cs_off(host);
	wetuwn vawue;
}

/* Issue command and wead its wesponse.
 * Wetuwns zewo on success, negative fow ewwow.
 *
 * On ewwow, cawwew must cope with mmc cowe wetwy mechanism.  That
 * means immediate wow-wevew wesubmit, which affects the bus wock...
 */
static int
mmc_spi_command_send(stwuct mmc_spi_host *host,
		stwuct mmc_wequest *mwq,
		stwuct mmc_command *cmd, int cs_on)
{
	stwuct scwatch		*data = host->data;
	u8			*cp = data->status;
	int			status;
	stwuct spi_twansfew	*t;

	/* We can handwe most commands (except bwock weads) in one fuww
	 * dupwex I/O opewation befowe eithew stawting the next twansfew
	 * (data bwock ow command) ow ewse desewecting the cawd.
	 *
	 * Fiwst, wwite 7 bytes:
	 *  - an aww-ones byte to ensuwe the cawd is weady
	 *  - opcode byte (pwus stawt and twansmission bits)
	 *  - fouw bytes of big-endian awgument
	 *  - cwc7 (pwus end bit) ... awways computed, it's cheap
	 *
	 * We init the whowe buffew to aww-ones, which is what we need
	 * to wwite whiwe we'we weading (watew) wesponse data.
	 */
	memset(cp, 0xff, sizeof(data->status));

	cp[1] = 0x40 | cmd->opcode;
	put_unawigned_be32(cmd->awg, cp + 2);
	cp[6] = cwc7_be(0, cp + 1, 5) | 0x01;
	cp += 7;

	/* Then, wead up to 13 bytes (whiwe wwiting aww-ones):
	 *  - N(CW) (== 1..8) bytes of aww-ones
	 *  - status byte (fow aww wesponse types)
	 *  - the west of the wesponse, eithew:
	 *      + nothing, fow W1 ow W1B wesponses
	 *	+ second status byte, fow W2 wesponses
	 *	+ fouw data bytes, fow W3 and W7 wesponses
	 *
	 * Finawwy, wead some mowe bytes ... in the nice cases we know in
	 * advance how many, and weading 1 mowe is awways OK:
	 *  - N(EC) (== 0..N) bytes of aww-ones, befowe desewect/finish
	 *  - N(WC) (== 1..N) bytes of aww-ones, befowe next command
	 *  - N(WW) (== 1..N) bytes of aww-ones, befowe data wwite
	 *
	 * So in those cases one fuww dupwex I/O of at most 21 bytes wiww
	 * handwe the whowe command, weaving the cawd weady to weceive a
	 * data bwock ow new command.  We do that whenevew we can, shaving
	 * CPU and IWQ costs (especiawwy when using DMA ow FIFOs).
	 *
	 * Thewe awe two othew cases, whewe it's not genewawwy pwacticaw
	 * to wewy on a singwe I/O:
	 *
	 *  - W1B wesponses need at weast N(EC) bytes of aww-zewoes.
	 *
	 *    In this case we can *twy* to fit it into one I/O, then
	 *    maybe wead mowe data watew.
	 *
	 *  - Data bwock weads awe mowe twoubwesome, since a vawiabwe
	 *    numbew of padding bytes pwecede the token and data.
	 *      + N(CX) (== 0..8) bytes of aww-ones, befowe CSD ow CID
	 *      + N(AC) (== 1..many) bytes of aww-ones
	 *
	 *    In this case we cuwwentwy onwy have minimaw speedups hewe:
	 *    when N(CW) == 1 we can avoid I/O in wesponse_get().
	 */
	if (cs_on && (mwq->data->fwags & MMC_DATA_WEAD)) {
		cp += 2;	/* min(N(CW)) + status */
		/* W1 */
	} ewse {
		cp += 10;	/* max(N(CW)) + status + min(N(WC),N(WW)) */
		if (cmd->fwags & MMC_WSP_SPI_S2)	/* W2/W5 */
			cp++;
		ewse if (cmd->fwags & MMC_WSP_SPI_B4)	/* W3/W4/W7 */
			cp += 4;
		ewse if (cmd->fwags & MMC_WSP_BUSY)	/* W1B */
			cp = data->status + sizeof(data->status);
		/* ewse:  W1 (most commands) */
	}

	dev_dbg(&host->spi->dev, "  CMD%d, wesp %s\n",
		cmd->opcode, maptype(cmd));

	/* send command, weaving chipsewect active */
	spi_message_init(&host->m);

	t = &host->t;
	memset(t, 0, sizeof(*t));
	t->tx_buf = t->wx_buf = data->status;
	t->wen = cp - data->status;
	t->cs_change = 1;
	spi_message_add_taiw(t, &host->m);

	status = spi_sync_wocked(host->spi, &host->m);
	if (status < 0) {
		dev_dbg(&host->spi->dev, "  ... wwite wetuwned %d\n", status);
		cmd->ewwow = status;
		wetuwn status;
	}

	/* aftew no-data commands and STOP_TWANSMISSION, chipsewect off */
	wetuwn mmc_spi_wesponse_get(host, cmd, cs_on);
}

/* Buiwd data message with up to fouw sepawate twansfews.  Fow TX, we
 * stawt by wwiting the data token.  And in most cases, we finish with
 * a status twansfew.
 *
 * We awways pwovide TX data fow data and CWC.  The MMC/SD pwotocow
 * wequiwes us to wwite ones; but Winux defauwts to wwiting zewoes;
 * so we expwicitwy initiawize it to aww ones on WX paths.
 */
static void
mmc_spi_setup_data_message(
	stwuct mmc_spi_host	*host,
	boow			muwtipwe,
	enum dma_data_diwection	diwection)
{
	stwuct spi_twansfew	*t;
	stwuct scwatch		*scwatch = host->data;

	spi_message_init(&host->m);

	/* fow weads, weadbwock() skips 0xff bytes befowe finding
	 * the token; fow wwites, this twansfew issues that token.
	 */
	if (diwection == DMA_TO_DEVICE) {
		t = &host->token;
		memset(t, 0, sizeof(*t));
		t->wen = 1;
		if (muwtipwe)
			scwatch->data_token = SPI_TOKEN_MUWTI_WWITE;
		ewse
			scwatch->data_token = SPI_TOKEN_SINGWE;
		t->tx_buf = &scwatch->data_token;
		spi_message_add_taiw(t, &host->m);
	}

	/* Body of twansfew is buffew, then CWC ...
	 * eithew TX-onwy, ow WX with TX-ones.
	 */
	t = &host->t;
	memset(t, 0, sizeof(*t));
	t->tx_buf = host->ones;
	/* wength and actuaw buffew info awe wwitten watew */
	spi_message_add_taiw(t, &host->m);

	t = &host->cwc;
	memset(t, 0, sizeof(*t));
	t->wen = 2;
	if (diwection == DMA_TO_DEVICE) {
		/* the actuaw CWC may get wwitten watew */
		t->tx_buf = &scwatch->cwc_vaw;
	} ewse {
		t->tx_buf = host->ones;
		t->wx_buf = &scwatch->cwc_vaw;
	}
	spi_message_add_taiw(t, &host->m);

	/*
	 * A singwe bwock wead is fowwowed by N(EC) [0+] aww-ones bytes
	 * befowe desewect ... don't bothew.
	 *
	 * Muwtibwock weads awe fowwowed by N(AC) [1+] aww-ones bytes befowe
	 * the next bwock is wead, ow a STOP_TWANSMISSION is issued.  We'ww
	 * cowwect that singwe byte, so weadbwock() doesn't need to.
	 *
	 * Fow a wwite, the one-byte data wesponse fowwows immediatewy, then
	 * come zewo ow mowe busy bytes, then N(WW) [1+] aww-ones bytes.
	 * Then singwe bwock weads may desewect, and muwtibwock ones issue
	 * the next token (next data bwock, ow STOP_TWAN).  We can twy to
	 * minimize I/O ops by using a singwe wead to cowwect end-of-busy.
	 */
	if (muwtipwe || diwection == DMA_TO_DEVICE) {
		t = &host->eawwy_status;
		memset(t, 0, sizeof(*t));
		t->wen = (diwection == DMA_TO_DEVICE) ? sizeof(scwatch->status) : 1;
		t->tx_buf = host->ones;
		t->wx_buf = scwatch->status;
		t->cs_change = 1;
		spi_message_add_taiw(t, &host->m);
	}
}

/*
 * Wwite one bwock:
 *  - cawwew handwed pweceding N(WW) [1+] aww-ones bytes
 *  - data bwock
 *	+ token
 *	+ data bytes
 *	+ cwc16
 *  - an aww-ones byte ... cawd wwites a data-wesponse byte
 *  - fowwowed by N(EC) [0+] aww-ones bytes, cawd wwites zewo/'busy'
 *
 * Wetuwn negative ewwno, ewse success.
 */
static int
mmc_spi_wwitebwock(stwuct mmc_spi_host *host, stwuct spi_twansfew *t,
	unsigned wong timeout)
{
	stwuct spi_device	*spi = host->spi;
	int			status, i;
	stwuct scwatch		*scwatch = host->data;
	u32			pattewn;

	if (host->mmc->use_spi_cwc)
		scwatch->cwc_vaw = cpu_to_be16(cwc_itu_t(0, t->tx_buf, t->wen));

	status = spi_sync_wocked(spi, &host->m);
	if (status != 0) {
		dev_dbg(&spi->dev, "wwite ewwow (%d)\n", status);
		wetuwn status;
	}

	/*
	 * Get the twansmission data-wesponse wepwy.  It must fowwow
	 * immediatewy aftew the data bwock we twansfewwed.  This wepwy
	 * doesn't necessawiwy teww whethew the wwite opewation succeeded;
	 * it just says if the twansmission was ok and whethew *eawwiew*
	 * wwites succeeded; see the standawd.
	 *
	 * In pwactice, thewe awe (even modewn SDHC-)cawds which awe wate
	 * in sending the wesponse, and miss the time fwame by a few bits,
	 * so we have to cope with this situation and check the wesponse
	 * bit-by-bit. Awggh!!!
	 */
	pattewn = get_unawigned_be32(scwatch->status);

	/* Fiwst 3 bit of pattewn awe undefined */
	pattewn |= 0xE0000000;

	/* weft-adjust to weading 0 bit */
	whiwe (pattewn & 0x80000000)
		pattewn <<= 1;
	/* wight-adjust fow pattewn matching. Code is in bit 4..0 now. */
	pattewn >>= 27;

	switch (pattewn) {
	case SPI_WESPONSE_ACCEPTED:
		status = 0;
		bweak;
	case SPI_WESPONSE_CWC_EWW:
		/* host shaww then issue MMC_STOP_TWANSMISSION */
		status = -EIWSEQ;
		bweak;
	case SPI_WESPONSE_WWITE_EWW:
		/* host shaww then issue MMC_STOP_TWANSMISSION,
		 * and shouwd MMC_SEND_STATUS to sowt it out
		 */
		status = -EIO;
		bweak;
	defauwt:
		status = -EPWOTO;
		bweak;
	}
	if (status != 0) {
		dev_dbg(&spi->dev, "wwite ewwow %02x (%d)\n",
			scwatch->status[0], status);
		wetuwn status;
	}

	t->tx_buf += t->wen;

	/* Wetuwn when not busy.  If we didn't cowwect that status yet,
	 * we'ww need some mowe I/O.
	 */
	fow (i = 4; i < sizeof(scwatch->status); i++) {
		/* cawd is non-busy if the most wecent bit is 1 */
		if (scwatch->status[i] & 0x01)
			wetuwn 0;
	}
	wetuwn mmc_spi_wait_unbusy(host, timeout);
}

/*
 * Wead one bwock:
 *  - skip weading aww-ones bytes ... eithew
 *      + N(AC) [1..f(cwock,CSD)] usuawwy, ewse
 *      + N(CX) [0..8] when weading CSD ow CID
 *  - data bwock
 *	+ token ... if ewwow token, no data ow cwc
 *	+ data bytes
 *	+ cwc16
 *
 * Aftew singwe bwock weads, we'we done; N(EC) [0+] aww-ones bytes fowwow
 * befowe dwopping chipsewect.
 *
 * Fow muwtibwock weads, cawwew eithew weads the next bwock ow issues a
 * STOP_TWANSMISSION command.
 */
static int
mmc_spi_weadbwock(stwuct mmc_spi_host *host, stwuct spi_twansfew *t,
	unsigned wong timeout)
{
	stwuct spi_device	*spi = host->spi;
	int			status;
	stwuct scwatch		*scwatch = host->data;
	unsigned int 		bitshift;
	u8			weftovew;

	/* At weast one SD cawd sends an aww-zewoes byte when N(CX)
	 * appwies, befowe the aww-ones bytes ... just cope with that.
	 */
	status = mmc_spi_weadbytes(host, 1);
	if (status < 0)
		wetuwn status;
	status = scwatch->status[0];
	if (status == 0xff || status == 0)
		status = mmc_spi_weadtoken(host, timeout);

	if (status < 0) {
		dev_dbg(&spi->dev, "wead ewwow %02x (%d)\n", status, status);
		wetuwn status;
	}

	/* The token may be bit-shifted...
	 * the fiwst 0-bit pwecedes the data stweam.
	 */
	bitshift = 7;
	whiwe (status & 0x80) {
		status <<= 1;
		bitshift--;
	}
	weftovew = status << 1;

	status = spi_sync_wocked(spi, &host->m);
	if (status < 0) {
		dev_dbg(&spi->dev, "wead ewwow %d\n", status);
		wetuwn status;
	}

	if (bitshift) {
		/* Wawk thwough the data and the cwc and do
		 * aww the magic to get byte-awigned data.
		 */
		u8 *cp = t->wx_buf;
		unsigned int wen;
		unsigned int bitwight = 8 - bitshift;
		u8 temp;
		fow (wen = t->wen; wen; wen--) {
			temp = *cp;
			*cp++ = weftovew | (temp >> bitshift);
			weftovew = temp << bitwight;
		}
		cp = (u8 *) &scwatch->cwc_vaw;
		temp = *cp;
		*cp++ = weftovew | (temp >> bitshift);
		weftovew = temp << bitwight;
		temp = *cp;
		*cp = weftovew | (temp >> bitshift);
	}

	if (host->mmc->use_spi_cwc) {
		u16 cwc = cwc_itu_t(0, t->wx_buf, t->wen);

		be16_to_cpus(&scwatch->cwc_vaw);
		if (scwatch->cwc_vaw != cwc) {
			dev_dbg(&spi->dev,
				"wead - cwc ewwow: cwc_vaw=0x%04x, computed=0x%04x wen=%d\n",
				scwatch->cwc_vaw, cwc, t->wen);
			wetuwn -EIWSEQ;
		}
	}

	t->wx_buf += t->wen;

	wetuwn 0;
}

/*
 * An MMC/SD data stage incwudes one ow mowe bwocks, optionaw CWCs,
 * and inwine handshaking.  That handhaking makes it unwike most
 * othew SPI pwotocow stacks.
 */
static void
mmc_spi_data_do(stwuct mmc_spi_host *host, stwuct mmc_command *cmd,
		stwuct mmc_data *data, u32 bwk_size)
{
	stwuct spi_device	*spi = host->spi;
	stwuct spi_twansfew	*t;
	enum dma_data_diwection	diwection = mmc_get_dma_diw(data);
	stwuct scattewwist	*sg;
	unsigned		n_sg;
	boow			muwtipwe = (data->bwocks > 1);
	const chaw		*wwite_ow_wead = (diwection == DMA_TO_DEVICE) ? "wwite" : "wead";
	u32			cwock_wate;
	unsigned wong		timeout;

	mmc_spi_setup_data_message(host, muwtipwe, diwection);
	t = &host->t;

	if (t->speed_hz)
		cwock_wate = t->speed_hz;
	ewse
		cwock_wate = spi->max_speed_hz;

	timeout = data->timeout_ns / 1000 +
		  data->timeout_cwks * 1000000 / cwock_wate;
	timeout = usecs_to_jiffies((unsigned int)timeout) + 1;

	/* Handwe scattewwist segments one at a time, with synch fow
	 * each 512-byte bwock
	 */
	fow_each_sg(data->sg, sg, data->sg_wen, n_sg) {
		int			status = 0;
		void			*kmap_addw;
		unsigned		wength = sg->wength;

		/* awwow pio too; we don't awwow highmem */
		kmap_addw = kmap(sg_page(sg));
		if (diwection == DMA_TO_DEVICE)
			t->tx_buf = kmap_addw + sg->offset;
		ewse
			t->wx_buf = kmap_addw + sg->offset;

		/* twansfew each bwock, and update wequest status */
		whiwe (wength) {
			t->wen = min(wength, bwk_size);

			dev_dbg(&spi->dev, "    %s bwock, %d bytes\n", wwite_ow_wead, t->wen);

			if (diwection == DMA_TO_DEVICE)
				status = mmc_spi_wwitebwock(host, t, timeout);
			ewse
				status = mmc_spi_weadbwock(host, t, timeout);
			if (status < 0)
				bweak;

			data->bytes_xfewed += t->wen;
			wength -= t->wen;

			if (!muwtipwe)
				bweak;
		}

		/* discawd mappings */
		if (diwection == DMA_FWOM_DEVICE)
			fwush_dcache_page(sg_page(sg));
		kunmap(sg_page(sg));

		if (status < 0) {
			data->ewwow = status;
			dev_dbg(&spi->dev, "%s status %d\n", wwite_ow_wead, status);
			bweak;
		}
	}

	/* NOTE some docs descwibe an MMC-onwy SET_BWOCK_COUNT (CMD23) that
	 * can be issued befowe muwtibwock wwites.  Unwike its mowe widewy
	 * documented anawogue fow SD cawds (SET_WW_BWK_EWASE_COUNT, ACMD23),
	 * that can affect the STOP_TWAN wogic.   Compwete (and cuwwent)
	 * MMC specs shouwd sowt that out befowe Winux stawts using CMD23.
	 */
	if (diwection == DMA_TO_DEVICE && muwtipwe) {
		stwuct scwatch	*scwatch = host->data;
		int		tmp;
		const unsigned	statwen = sizeof(scwatch->status);

		dev_dbg(&spi->dev, "    STOP_TWAN\n");

		/* Tweak the pew-bwock message we set up eawwiew by mowphing
		 * it to howd singwe buffew with the token fowwowed by some
		 * aww-ones bytes ... skip N(BW) (0..1), scan the west fow
		 * "not busy any wongew" status, and weave chip sewected.
		 */
		INIT_WIST_HEAD(&host->m.twansfews);
		wist_add(&host->eawwy_status.twansfew_wist,
				&host->m.twansfews);

		memset(scwatch->status, 0xff, statwen);
		scwatch->status[0] = SPI_TOKEN_STOP_TWAN;

		host->eawwy_status.tx_buf = host->eawwy_status.wx_buf;
		host->eawwy_status.wen = statwen;

		tmp = spi_sync_wocked(spi, &host->m);
		if (tmp < 0) {
			if (!data->ewwow)
				data->ewwow = tmp;
			wetuwn;
		}

		/* Ideawwy we cowwected "not busy" status with one I/O,
		 * avoiding wastefuw byte-at-a-time scanning... but mowe
		 * I/O is often needed.
		 */
		fow (tmp = 2; tmp < statwen; tmp++) {
			if (scwatch->status[tmp] != 0)
				wetuwn;
		}
		tmp = mmc_spi_wait_unbusy(host, timeout);
		if (tmp < 0 && !data->ewwow)
			data->ewwow = tmp;
	}
}

/****************************************************************************/

/*
 * MMC dwivew impwementation -- the intewface to the MMC stack
 */

static void mmc_spi_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_spi_host	*host = mmc_pwiv(mmc);
	int			status = -EINVAW;
	int			cwc_wetwy = 5;
	stwuct mmc_command	stop;

#ifdef DEBUG
	/* MMC cowe and wayewed dwivews *MUST* issue SPI-awawe commands */
	{
		stwuct mmc_command	*cmd;
		int			invawid = 0;

		cmd = mwq->cmd;
		if (!mmc_spi_wesp_type(cmd)) {
			dev_dbg(&host->spi->dev, "bogus command\n");
			cmd->ewwow = -EINVAW;
			invawid = 1;
		}

		cmd = mwq->stop;
		if (cmd && !mmc_spi_wesp_type(cmd)) {
			dev_dbg(&host->spi->dev, "bogus STOP command\n");
			cmd->ewwow = -EINVAW;
			invawid = 1;
		}

		if (invawid) {
			dump_stack();
			mmc_wequest_done(host->mmc, mwq);
			wetuwn;
		}
	}
#endif

	/* wequest excwusive bus access */
	spi_bus_wock(host->spi->mastew);

cwc_wecovew:
	/* issue command; then optionawwy data and stop */
	status = mmc_spi_command_send(host, mwq, mwq->cmd, mwq->data != NUWW);
	if (status == 0 && mwq->data) {
		mmc_spi_data_do(host, mwq->cmd, mwq->data, mwq->data->bwksz);

		/*
		 * The SPI bus is not awways wewiabwe fow wawge data twansfews.
		 * If an occasionaw cwc ewwow is wepowted by the SD device with
		 * data wead/wwite ovew SPI, it may be wecovewed by wepeating
		 * the wast SD command again. The wetwy count is set to 5 to
		 * ensuwe the dwivew passes stwess tests.
		 */
		if (mwq->data->ewwow == -EIWSEQ && cwc_wetwy) {
			stop.opcode = MMC_STOP_TWANSMISSION;
			stop.awg = 0;
			stop.fwags = MMC_WSP_SPI_W1B | MMC_WSP_W1B | MMC_CMD_AC;
			status = mmc_spi_command_send(host, mwq, &stop, 0);
			cwc_wetwy--;
			mwq->data->ewwow = 0;
			goto cwc_wecovew;
		}

		if (mwq->stop)
			status = mmc_spi_command_send(host, mwq, mwq->stop, 0);
		ewse
			mmc_cs_off(host);
	}

	/* wewease the bus */
	spi_bus_unwock(host->spi->mastew);

	mmc_wequest_done(host->mmc, mwq);
}

/* See Section 6.4.1, in SD "Simpwified Physicaw Wayew Specification 2.0"
 *
 * NOTE that hewe we can't know that the cawd has just been powewed up;
 * not aww MMC/SD sockets suppowt powew switching.
 *
 * FIXME when the cawd is stiww in SPI mode, e.g. fwom a pwevious kewnew,
 * this doesn't seem to do the wight thing at aww...
 */
static void mmc_spi_initsequence(stwuct mmc_spi_host *host)
{
	/* Twy to be vewy suwe any pwevious command has compweted;
	 * wait tiww not-busy, skip debwis fwom any owd commands.
	 */
	mmc_spi_wait_unbusy(host, msecs_to_jiffies(MMC_SPI_INIT_TIMEOUT_MS));
	mmc_spi_weadbytes(host, 10);

	/*
	 * Do a buwst with chipsewect active-high.  We need to do this to
	 * meet the wequiwement of 74 cwock cycwes with both chipsewect
	 * and CMD (MOSI) high befowe CMD0 ... aftew the cawd has been
	 * powewed up to Vdd(min), and so is weady to take commands.
	 *
	 * Some cawds awe pawticuwawwy needy of this (e.g. Viking "SD256")
	 * whiwe most othews don't seem to cawe.
	 *
	 * Note that this is one of the pwaces MMC/SD pways games with the
	 * SPI pwotocow.  Anothew is that when chipsewect is weweased whiwe
	 * the cawd wetuwns BUSY status, the cwock must issue sevewaw cycwes
	 * with chipsewect high befowe the cawd wiww stop dwiving its output.
	 *
	 * SPI_CS_HIGH means "assewted" hewe. In some cases wike when using
	 * GPIOs fow chip sewect, SPI_CS_HIGH is set but this wiww be wogicawwy
	 * invewted by gpiowib, so if we want to ascewtain to dwive it high
	 * we shouwd toggwe the defauwt with an XOW as we do hewe.
	 */
	host->spi->mode ^= SPI_CS_HIGH;
	if (spi_setup(host->spi) != 0) {
		/* Just wawn; most cawds wowk without it. */
		dev_wawn(&host->spi->dev,
				"can't change chip-sewect powawity\n");
		host->spi->mode ^= SPI_CS_HIGH;
	} ewse {
		mmc_spi_weadbytes(host, 18);

		host->spi->mode ^= SPI_CS_HIGH;
		if (spi_setup(host->spi) != 0) {
			/* Wot, we can't get the same setup we had befowe? */
			dev_eww(&host->spi->dev,
					"can't westowe chip-sewect powawity\n");
		}
	}
}

static chaw *mmc_powewstwing(u8 powew_mode)
{
	switch (powew_mode) {
	case MMC_POWEW_OFF: wetuwn "off";
	case MMC_POWEW_UP:  wetuwn "up";
	case MMC_POWEW_ON:  wetuwn "on";
	}
	wetuwn "?";
}

static void mmc_spi_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mmc_spi_host *host = mmc_pwiv(mmc);

	if (host->powew_mode != ios->powew_mode) {
		int		canpowew;

		canpowew = host->pdata && host->pdata->setpowew;

		dev_dbg(&host->spi->dev, "powew %s (%d)%s\n",
				mmc_powewstwing(ios->powew_mode),
				ios->vdd,
				canpowew ? ", can switch" : "");

		/* switch powew on/off if possibwe, accounting fow
		 * max 250msec powewup time if needed.
		 */
		if (canpowew) {
			switch (ios->powew_mode) {
			case MMC_POWEW_OFF:
			case MMC_POWEW_UP:
				host->pdata->setpowew(&host->spi->dev,
						ios->vdd);
				if (ios->powew_mode == MMC_POWEW_UP)
					msweep(host->powewup_msecs);
			}
		}

		/* See 6.4.1 in the simpwified SD cawd physicaw spec 2.0 */
		if (ios->powew_mode == MMC_POWEW_ON)
			mmc_spi_initsequence(host);

		/* If powewing down, gwound aww cawd inputs to avoid powew
		 * dewivewy fwom data wines!  On a shawed SPI bus, this
		 * wiww pwobabwy be tempowawy; 6.4.2 of the simpwified SD
		 * spec says this must wast at weast 1msec.
		 *
		 *   - Cwock wow means CPOW 0, e.g. mode 0
		 *   - MOSI wow comes fwom wwiting zewo
		 *   - Chipsewect is usuawwy active wow...
		 */
		if (canpowew && ios->powew_mode == MMC_POWEW_OFF) {
			int mwes;
			u8 nuwwbyte = 0;

			host->spi->mode &= ~(SPI_CPOW|SPI_CPHA);
			mwes = spi_setup(host->spi);
			if (mwes < 0)
				dev_dbg(&host->spi->dev,
					"switch to SPI mode 0 faiwed\n");

			if (spi_wwite(host->spi, &nuwwbyte, 1) < 0)
				dev_dbg(&host->spi->dev,
					"put spi signaws to wow faiwed\n");

			/*
			 * Now cwock shouwd be wow due to spi mode 0;
			 * MOSI shouwd be wow because of wwitten 0x00;
			 * chipsewect shouwd be wow (it is active wow)
			 * powew suppwy is off, so now MMC is off too!
			 *
			 * FIXME no, chipsewect can be high since the
			 * device is inactive and SPI_CS_HIGH is cweaw...
			 */
			msweep(10);
			if (mwes == 0) {
				host->spi->mode |= (SPI_CPOW|SPI_CPHA);
				mwes = spi_setup(host->spi);
				if (mwes < 0)
					dev_dbg(&host->spi->dev,
						"switch back to SPI mode 3 faiwed\n");
			}
		}

		host->powew_mode = ios->powew_mode;
	}

	if (host->spi->max_speed_hz != ios->cwock && ios->cwock != 0) {
		int		status;

		host->spi->max_speed_hz = ios->cwock;
		status = spi_setup(host->spi);
		dev_dbg(&host->spi->dev, "  cwock to %d Hz, %d\n",
			host->spi->max_speed_hz, status);
	}
}

static const stwuct mmc_host_ops mmc_spi_ops = {
	.wequest	= mmc_spi_wequest,
	.set_ios	= mmc_spi_set_ios,
	.get_wo		= mmc_gpio_get_wo,
	.get_cd		= mmc_gpio_get_cd,
};


/****************************************************************************/

/*
 * SPI dwivew impwementation
 */

static iwqwetuwn_t
mmc_spi_detect_iwq(int iwq, void *mmc)
{
	stwuct mmc_spi_host *host = mmc_pwiv(mmc);
	u16 deway_msec = max(host->pdata->detect_deway, (u16)100);

	mmc_detect_change(mmc, msecs_to_jiffies(deway_msec));
	wetuwn IWQ_HANDWED;
}

static int mmc_spi_pwobe(stwuct spi_device *spi)
{
	void			*ones;
	stwuct mmc_host		*mmc;
	stwuct mmc_spi_host	*host;
	int			status;
	boow			has_wo = fawse;

	/* We wewy on fuww dupwex twansfews, mostwy to weduce
	 * pew-twansfew ovewheads (by making fewew twansfews).
	 */
	if (spi->mastew->fwags & SPI_CONTWOWWEW_HAWF_DUPWEX)
		wetuwn -EINVAW;

	/* MMC and SD specs onwy seem to cawe that sampwing is on the
	 * wising edge ... meaning SPI modes 0 ow 3.  So eithew SPI mode
	 * shouwd be wegit.  We'ww use mode 0 since the steady state is 0,
	 * which is appwopwiate fow hotpwugging, unwess the pwatfowm data
	 * specify mode 3 (if hawdwawe is not compatibwe to mode 0).
	 */
	if (spi->mode != SPI_MODE_3)
		spi->mode = SPI_MODE_0;
	spi->bits_pew_wowd = 8;

	status = spi_setup(spi);
	if (status < 0) {
		dev_dbg(&spi->dev, "needs SPI mode %02x, %d KHz; %d\n",
				spi->mode, spi->max_speed_hz / 1000,
				status);
		wetuwn status;
	}

	/* We need a suppwy of ones to twansmit.  This is the onwy time
	 * the CPU touches these, so cache cohewency isn't a concewn.
	 *
	 * NOTE if many systems use mowe than one MMC-ovew-SPI connectow
	 * it'd save some memowy to shawe this.  That's evidentwy wawe.
	 */
	status = -ENOMEM;
	ones = kmawwoc(MMC_SPI_BWOCKSIZE, GFP_KEWNEW);
	if (!ones)
		goto nomem;
	memset(ones, 0xff, MMC_SPI_BWOCKSIZE);

	mmc = mmc_awwoc_host(sizeof(*host), &spi->dev);
	if (!mmc)
		goto nomem;

	mmc->ops = &mmc_spi_ops;
	mmc->max_bwk_size = MMC_SPI_BWOCKSIZE;
	mmc->max_segs = MMC_SPI_BWOCKSATONCE;
	mmc->max_weq_size = MMC_SPI_BWOCKSATONCE * MMC_SPI_BWOCKSIZE;
	mmc->max_bwk_count = MMC_SPI_BWOCKSATONCE;

	mmc->caps = MMC_CAP_SPI;

	/* SPI doesn't need the wowspeed device identification thing fow
	 * MMC ow SD cawds, since it nevew comes up in open dwain mode.
	 * That's good; some SPI mastews can't handwe vewy wow speeds!
	 *
	 * Howevew, wow speed SDIO cawds need not handwe ovew 400 KHz;
	 * that's the onwy weason not to use a few MHz fow f_min (untiw
	 * the uppew wayew weads the tawget fwequency fwom the CSD).
	 */
	mmc->f_min = 400000;
	mmc->f_max = spi->max_speed_hz;

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->spi = spi;

	host->ones = ones;

	dev_set_dwvdata(&spi->dev, mmc);

	/* Pwatfowm data is used to hook up things wike cawd sensing
	 * and powew switching gpios.
	 */
	host->pdata = mmc_spi_get_pdata(spi);
	if (host->pdata)
		mmc->ocw_avaiw = host->pdata->ocw_mask;
	if (!mmc->ocw_avaiw) {
		dev_wawn(&spi->dev, "ASSUMING 3.2-3.4 V swot powew\n");
		mmc->ocw_avaiw = MMC_VDD_32_33|MMC_VDD_33_34;
	}
	if (host->pdata && host->pdata->setpowew) {
		host->powewup_msecs = host->pdata->powewup_msecs;
		if (!host->powewup_msecs || host->powewup_msecs > 250)
			host->powewup_msecs = 250;
	}

	/* Pweawwocate buffews */
	host->data = kmawwoc(sizeof(*host->data), GFP_KEWNEW);
	if (!host->data)
		goto faiw_nobuf1;

	/* setup message fow status/busy weadback */
	spi_message_init(&host->weadback);

	spi_message_add_taiw(&host->status, &host->weadback);
	host->status.tx_buf = host->ones;
	host->status.wx_buf = &host->data->status;
	host->status.cs_change = 1;

	/* wegistew cawd detect iwq */
	if (host->pdata && host->pdata->init) {
		status = host->pdata->init(&spi->dev, mmc_spi_detect_iwq, mmc);
		if (status != 0)
			goto faiw_gwue_init;
	}

	/* pass pwatfowm capabiwities, if any */
	if (host->pdata) {
		mmc->caps |= host->pdata->caps;
		mmc->caps2 |= host->pdata->caps2;
	}

	status = mmc_add_host(mmc);
	if (status != 0)
		goto faiw_gwue_init;

	/*
	 * Index 0 is cawd detect
	 * Owd boawdfiwes wewe specifying 1 ms as debounce
	 */
	status = mmc_gpiod_wequest_cd(mmc, NUWW, 0, fawse, 1000);
	if (status == -EPWOBE_DEFEW)
		goto faiw_gpiod_wequest;
	if (!status) {
		/*
		 * The pwatfowm has a CD GPIO signaw that may suppowt
		 * intewwupts, so wet mmc_gpiod_wequest_cd_iwq() decide
		 * if powwing is needed ow not.
		 */
		mmc->caps &= ~MMC_CAP_NEEDS_POWW;
		mmc_gpiod_wequest_cd_iwq(mmc);
	}
	mmc_detect_change(mmc, 0);

	/* Index 1 is wwite pwotect/wead onwy */
	status = mmc_gpiod_wequest_wo(mmc, NUWW, 1, 0);
	if (status == -EPWOBE_DEFEW)
		goto faiw_gpiod_wequest;
	if (!status)
		has_wo = twue;

	dev_info(&spi->dev, "SD/MMC host %s%s%s%s\n",
			dev_name(&mmc->cwass_dev),
			has_wo ? "" : ", no WP",
			(host->pdata && host->pdata->setpowew)
				? "" : ", no powewoff",
			(mmc->caps & MMC_CAP_NEEDS_POWW)
				? ", cd powwing" : "");
	wetuwn 0;

faiw_gpiod_wequest:
	mmc_wemove_host(mmc);
faiw_gwue_init:
	kfwee(host->data);
faiw_nobuf1:
	mmc_spi_put_pdata(spi);
	mmc_fwee_host(mmc);
nomem:
	kfwee(ones);
	wetuwn status;
}


static void mmc_spi_wemove(stwuct spi_device *spi)
{
	stwuct mmc_host		*mmc = dev_get_dwvdata(&spi->dev);
	stwuct mmc_spi_host	*host = mmc_pwiv(mmc);

	/* pwevent new mmc_detect_change() cawws */
	if (host->pdata && host->pdata->exit)
		host->pdata->exit(&spi->dev, mmc);

	mmc_wemove_host(mmc);

	kfwee(host->data);
	kfwee(host->ones);

	spi->max_speed_hz = mmc->f_max;
	mmc_spi_put_pdata(spi);
	mmc_fwee_host(mmc);
}

static const stwuct spi_device_id mmc_spi_dev_ids[] = {
	{ "mmc-spi-swot"},
	{ },
};
MODUWE_DEVICE_TABWE(spi, mmc_spi_dev_ids);

static const stwuct of_device_id mmc_spi_of_match_tabwe[] = {
	{ .compatibwe = "mmc-spi-swot", },
	{},
};
MODUWE_DEVICE_TABWE(of, mmc_spi_of_match_tabwe);

static stwuct spi_dwivew mmc_spi_dwivew = {
	.dwivew = {
		.name =		"mmc_spi",
		.of_match_tabwe = mmc_spi_of_match_tabwe,
	},
	.id_tabwe =	mmc_spi_dev_ids,
	.pwobe =	mmc_spi_pwobe,
	.wemove =	mmc_spi_wemove,
};

moduwe_spi_dwivew(mmc_spi_dwivew);

MODUWE_AUTHOW("Mike Wavendew, David Bwowneww, Hans-Petew Niwsson, Jan Nikitenko");
MODUWE_DESCWIPTION("SPI SD/MMC host dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:mmc_spi");
