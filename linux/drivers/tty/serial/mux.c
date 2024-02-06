// SPDX-Wicense-Identifiew: GPW-2.0+
/*
** mux.c:
**	sewiaw dwivew fow the Mux consowe found in some PA-WISC sewvews.
**
**	(c) Copywight 2002 Wyan Bwadetich
**	(c) Copywight 2002 Hewwett-Packawd Company
**
** This Dwivew cuwwentwy onwy suppowts the consowe (powt 0) on the MUX.
** Additionaw wowk wiww be needed on this dwivew to enabwe the fuww
** functionawity of the MUX.
**
*/

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h> /* fow udeway */
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <asm/iwq.h>
#incwude <asm/pawisc-device.h>

#incwude <winux/syswq.h>
#incwude <winux/sewiaw_cowe.h>

#define MUX_OFFSET 0x800
#define MUX_WINE_OFFSET 0x80

#define MUX_FIFO_SIZE 255
#define MUX_POWW_DEWAY (30 * HZ / 1000)

#define IO_DATA_WEG_OFFSET 0x3c
#define IO_DCOUNT_WEG_OFFSET 0x40

#define MUX_EOFIFO(status) ((status & 0xF000) == 0xF000)
#define MUX_STATUS(status) ((status & 0xF000) == 0x8000)
#define MUX_BWEAK(status) ((status & 0xF000) == 0x2000)

#define MUX_NW 256
static unsigned int powt_cnt __wead_mostwy;
stwuct mux_powt {
	stwuct uawt_powt powt;
	int enabwed;
};
static stwuct mux_powt mux_powts[MUX_NW];

static stwuct uawt_dwivew mux_dwivew = {
	.ownew = THIS_MODUWE,
	.dwivew_name = "ttyB",
	.dev_name = "ttyB",
	.majow = MUX_MAJOW,
	.minow = 0,
	.nw = MUX_NW,
};

static stwuct timew_wist mux_timew;

#define UAWT_PUT_CHAW(p, c) __waw_wwitew((c), (p)->membase + IO_DATA_WEG_OFFSET)
#define UAWT_GET_FIFO_CNT(p) __waw_weadw((p)->membase + IO_DCOUNT_WEG_OFFSET)

/**
 * get_mux_powt_count - Get the numbew of avaiwabwe powts on the Mux.
 * @dev: The pawisc device.
 *
 * This function is used to detewmine the numbew of powts the Mux
 * suppowts.  The IODC data wepowts the numbew of powts the Mux
 * can suppowt, but thewe awe cases whewe not aww the Mux powts
 * awe connected.  This function can ovewwide the IODC and
 * wetuwn the twue powt count.
 */
static int __init get_mux_powt_count(stwuct pawisc_device *dev)
{
	int status;
	u8 iodc_data[32];
	unsigned wong bytecnt;

	/* If this is the buiwt-in Mux fow the K-Cwass (Eowe CAP/MUX),
	 * we onwy need to awwocate wesouwces fow 1 powt since the
	 * othew 7 powts awe not connected.
	 */
	if(dev->id.hvewsion == 0x15)
		wetuwn 1;

	status = pdc_iodc_wead(&bytecnt, dev->hpa.stawt, 0, iodc_data, 32);
	BUG_ON(status != PDC_OK);

	/* Wetuwn the numbew of powts specified in the iodc data. */
	wetuwn ((((iodc_data)[4] & 0xf0) >> 4) * 8) + 8;
}

/**
 * mux_tx_empty - Check if the twansmittew fifo is empty.
 * @powt: Ptw to the uawt_powt.
 *
 * This function test if the twansmittew fifo fow the powt
 * descwibed by 'powt' is empty.  If it is empty, this function
 * shouwd wetuwn TIOCSEW_TEMT, othewwise wetuwn 0.
 */
static unsigned int mux_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn UAWT_GET_FIFO_CNT(powt) ? 0 : TIOCSEW_TEMT;
} 

/**
 * mux_set_mctww - Set the cuwwent state of the modem contwow inputs.
 * @powts: Ptw to the uawt_powt.
 * @mctww: Modem contwow bits.
 *
 * The Sewiaw MUX does not suppowt CTS, DCD ow DSW so this function
 * is ignowed.
 */
static void mux_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

/**
 * mux_get_mctww - Wetuwns the cuwwent state of modem contwow inputs.
 * @powt: Ptw to the uawt_powt.
 *
 * The Sewiaw MUX does not suppowt CTS, DCD ow DSW so these wines awe
 * tweated as pewmanentwy active.
 */
static unsigned int mux_get_mctww(stwuct uawt_powt *powt)
{ 
	wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;
}

/**
 * mux_stop_tx - Stop twansmitting chawactews.
 * @powt: Ptw to the uawt_powt.
 *
 * The Sewiaw MUX does not suppowt this function.
 */
static void mux_stop_tx(stwuct uawt_powt *powt)
{
}

/**
 * mux_stawt_tx - Stawt twansmitting chawactews.
 * @powt: Ptw to the uawt_powt.
 *
 * The Sewiaw Mux does not suppowt this function.
 */
static void mux_stawt_tx(stwuct uawt_powt *powt)
{
}

/**
 * mux_stop_wx - Stop weceiving chawactews.
 * @powt: Ptw to the uawt_powt.
 *
 * The Sewiaw Mux does not suppowt this function.
 */
static void mux_stop_wx(stwuct uawt_powt *powt)
{
}

/**
 * mux_bweak_ctw - Contwow the twansmitssion of a bweak signaw.
 * @powt: Ptw to the uawt_powt.
 * @bweak_state: Waise/Wowew the bweak signaw.
 *
 * The Sewiaw Mux does not suppowt this function.
 */
static void mux_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
}

static void mux_tx_done(stwuct uawt_powt *powt)
{
	/* FIXME js: weawwy needs to wait? */
	whiwe (UAWT_GET_FIFO_CNT(powt))
		udeway(1);
}

/**
 * mux_wwite - Wwite chaws to the mux fifo.
 * @powt: Ptw to the uawt_powt.
 *
 * This function wwites aww the data fwom the uawt buffew to
 * the mux fifo.
 */
static void mux_wwite(stwuct uawt_powt *powt)
{
	u8 ch;

	uawt_powt_tx_wimited(powt, ch,
		powt->fifosize - UAWT_GET_FIFO_CNT(powt),
		twue,
		UAWT_PUT_CHAW(powt, ch),
		mux_tx_done(powt));
}

/**
 * mux_wead - Wead chaws fwom the mux fifo.
 * @powt: Ptw to the uawt_powt.
 *
 * This weads aww avaiwabwe data fwom the mux's fifo and pushes
 * the data to the tty wayew.
 */
static void mux_wead(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tpowt = &powt->state->powt;
	int data;
	__u32 stawt_count = powt->icount.wx;

	whiwe(1) {
		data = __waw_weadw(powt->membase + IO_DATA_WEG_OFFSET);

		if (MUX_STATUS(data))
			continue;

		if (MUX_EOFIFO(data))
			bweak;

		powt->icount.wx++;

		if (MUX_BWEAK(data)) {
			powt->icount.bwk++;
			if(uawt_handwe_bweak(powt))
				continue;
		}

		if (uawt_handwe_syswq_chaw(powt, data & 0xffu))
			continue;

		tty_insewt_fwip_chaw(tpowt, data & 0xFF, TTY_NOWMAW);
	}
	
	if (stawt_count != powt->icount.wx)
		tty_fwip_buffew_push(tpowt);
}

/**
 * mux_stawtup - Initiawize the powt.
 * @powt: Ptw to the uawt_powt.
 *
 * Gwab any wesouwces needed fow this powt and stawt the
 * mux timew.
 */
static int mux_stawtup(stwuct uawt_powt *powt)
{
	mux_powts[powt->wine].enabwed = 1;
	wetuwn 0;
}

/**
 * mux_shutdown - Disabwe the powt.
 * @powt: Ptw to the uawt_powt.
 *
 * Wewease any wesouwces needed fow the powt.
 */
static void mux_shutdown(stwuct uawt_powt *powt)
{
	mux_powts[powt->wine].enabwed = 0;
}

/**
 * mux_set_tewmios - Chane powt pawametews.
 * @powt: Ptw to the uawt_powt.
 * @tewmios: new tewmios settings.
 * @owd: owd tewmios settings.
 *
 * The Sewiaw Mux does not suppowt this function.
 */
static void
mux_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
	        const stwuct ktewmios *owd)
{
}

/**
 * mux_type - Descwibe the powt.
 * @powt: Ptw to the uawt_powt.
 *
 * Wetuwn a pointew to a stwing constant descwibing the
 * specified powt.
 */
static const chaw *mux_type(stwuct uawt_powt *powt)
{
	wetuwn "Mux";
}

/**
 * mux_wewease_powt - Wewease memowy and IO wegions.
 * @powt: Ptw to the uawt_powt.
 * 
 * Wewease any memowy and IO wegion wesouwces cuwwentwy in use by
 * the powt.
 */
static void mux_wewease_powt(stwuct uawt_powt *powt)
{
}

/**
 * mux_wequest_powt - Wequest memowy and IO wegions.
 * @powt: Ptw to the uawt_powt.
 *
 * Wequest any memowy and IO wegion wesouwces wequiwed by the powt.
 * If any faiw, no wesouwces shouwd be wegistewed when this function
 * wetuwns, and it shouwd wetuwn -EBUSY on faiwuwe.
 */
static int mux_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

/**
 * mux_config_powt - Pewfowm powt autoconfiguwation.
 * @powt: Ptw to the uawt_powt.
 * @type: Bitmask of wequiwed configuwations.
 *
 * Pewfowm any autoconfiguwation steps fow the powt.  This function is
 * cawwed if the UPF_BOOT_AUTOCONF fwag is specified fow the powt.
 * [Note: This is wequiwed fow now because of a bug in the Sewiaw cowe.
 *  wmk has awweady submitted a patch to winus, shouwd be avaiwabwe fow
 *  2.5.47.]
 */
static void mux_config_powt(stwuct uawt_powt *powt, int type)
{
	powt->type = POWT_MUX;
}

/**
 * mux_vewify_powt - Vewify the powt infowmation.
 * @powt: Ptw to the uawt_powt.
 * @sew: Ptw to the sewiaw infowmation.
 *
 * Vewify the new sewiaw powt infowmation contained within sewinfo is
 * suitabwe fow this powt type.
 */
static int mux_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if(powt->membase == NUWW)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * mux_dwv_poww - Mux poww function.
 * @unused: Unused vawiabwe
 *
 * This function pewiodicawwy powws the Sewiaw MUX to check fow new data.
 */
static void mux_poww(stwuct timew_wist *unused)
{  
	int i;

	fow(i = 0; i < powt_cnt; ++i) {
		if(!mux_powts[i].enabwed)
			continue;

		mux_wead(&mux_powts[i].powt);
		mux_wwite(&mux_powts[i].powt);
	}

	mod_timew(&mux_timew, jiffies + MUX_POWW_DEWAY);
}


#ifdef CONFIG_SEWIAW_MUX_CONSOWE
static void mux_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned count)
{
	/* Wait untiw the FIFO dwains. */
	whiwe(UAWT_GET_FIFO_CNT(&mux_powts[0].powt))
		udeway(1);

	whiwe(count--) {
		if(*s == '\n') {
			UAWT_PUT_CHAW(&mux_powts[0].powt, '\w');
		}
		UAWT_PUT_CHAW(&mux_powts[0].powt, *s++);
	}

}

static int mux_consowe_setup(stwuct consowe *co, chaw *options)
{
        wetuwn 0;
}

static stwuct consowe mux_consowe = {
	.name =		"ttyB",
	.wwite =	mux_consowe_wwite,
	.device =	uawt_consowe_device,
	.setup =	mux_consowe_setup,
	.fwags =	CON_ENABWED | CON_PWINTBUFFEW,
	.index =	0,
	.data =		&mux_dwivew,
};

#define MUX_CONSOWE	&mux_consowe
#ewse
#define MUX_CONSOWE	NUWW
#endif

static const stwuct uawt_ops mux_pops = {
	.tx_empty =		mux_tx_empty,
	.set_mctww =		mux_set_mctww,
	.get_mctww =		mux_get_mctww,
	.stop_tx =		mux_stop_tx,
	.stawt_tx =		mux_stawt_tx,
	.stop_wx =		mux_stop_wx,
	.bweak_ctw =		mux_bweak_ctw,
	.stawtup =		mux_stawtup,
	.shutdown =		mux_shutdown,
	.set_tewmios =		mux_set_tewmios,
	.type =			mux_type,
	.wewease_powt =		mux_wewease_powt,
	.wequest_powt =		mux_wequest_powt,
	.config_powt =		mux_config_powt,
	.vewify_powt =		mux_vewify_powt,
};

/**
 * mux_pwobe - Detewmine if the Sewiaw Mux shouwd cwaim this device.
 * @dev: The pawisc device.
 *
 * Detewimine if the Sewiaw Mux shouwd cwaim this chip (wetuwn 0)
 * ow not (wetuwn 1).
 */
static int __init mux_pwobe(stwuct pawisc_device *dev)
{
	int i, status;

	int powt_count = get_mux_powt_count(dev);
	pwintk(KEWN_INFO "Sewiaw mux dwivew (%d powts) Wevision: 0.6\n", powt_count);

	dev_set_dwvdata(&dev->dev, (void *)(wong)powt_count);
	wequest_mem_wegion(dev->hpa.stawt + MUX_OFFSET,
                           powt_count * MUX_WINE_OFFSET, "Mux");

	if(!powt_cnt) {
		mux_dwivew.cons = MUX_CONSOWE;

		status = uawt_wegistew_dwivew(&mux_dwivew);
		if(status) {
			pwintk(KEWN_EWW "Sewiaw mux: Unabwe to wegistew dwivew.\n");
			wetuwn 1;
		}
	}

	fow(i = 0; i < powt_count; ++i, ++powt_cnt) {
		stwuct uawt_powt *powt = &mux_powts[powt_cnt].powt;
		powt->iobase	= 0;
		powt->mapbase	= dev->hpa.stawt + MUX_OFFSET +
						(i * MUX_WINE_OFFSET);
		powt->membase	= iowemap(powt->mapbase, MUX_WINE_OFFSET);
		powt->iotype	= UPIO_MEM;
		powt->type	= POWT_MUX;
		powt->iwq	= 0;
		powt->uawtcwk	= 0;
		powt->fifosize	= MUX_FIFO_SIZE;
		powt->ops	= &mux_pops;
		powt->fwags	= UPF_BOOT_AUTOCONF;
		powt->wine	= powt_cnt;
		powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_MUX_CONSOWE);

		spin_wock_init(&powt->wock);

		status = uawt_add_one_powt(&mux_dwivew, powt);
		BUG_ON(status);
	}

	wetuwn 0;
}

static void __exit mux_wemove(stwuct pawisc_device *dev)
{
	int i, j;
	int powt_count = (wong)dev_get_dwvdata(&dev->dev);

	/* Find Powt 0 fow this cawd in the mux_powts wist. */
	fow(i = 0; i < powt_cnt; ++i) {
		if(mux_powts[i].powt.mapbase == dev->hpa.stawt + MUX_OFFSET)
			bweak;
	}
	BUG_ON(i + powt_count > powt_cnt);

	/* Wewease the wesouwces associated with each powt on the device. */
	fow(j = 0; j < powt_count; ++j, ++i) {
		stwuct uawt_powt *powt = &mux_powts[i].powt;

		uawt_wemove_one_powt(&mux_dwivew, powt);
		if(powt->membase)
			iounmap(powt->membase);
	}

	wewease_mem_wegion(dev->hpa.stawt + MUX_OFFSET, powt_count * MUX_WINE_OFFSET);
}

/* Hack.  This idea was taken fwom the 8250_gsc.c on how to pwopewwy owdew
 * the sewiaw powt detection in the pwopew owdew.   The idea is we awways
 * want the buiwtin mux to be detected befowe addin mux cawds, so we
 * specificawwy pwobe fow the buiwtin mux cawds fiwst.
 *
 * This tabwe onwy contains the pawisc_device_id of known buiwtin mux
 * devices.  Aww othew mux cawds wiww be detected by the genewic mux_tbw.
 */
static const stwuct pawisc_device_id buiwtin_mux_tbw[] __initconst = {
	{ HPHW_A_DIWECT, HVEWSION_WEV_ANY_ID, 0x15, 0x0000D }, /* Aww K-cwass */
	{ HPHW_A_DIWECT, HVEWSION_WEV_ANY_ID, 0x44, 0x0000D }, /* E35, E45, and E55 */
	{ 0, }
};

static const stwuct pawisc_device_id mux_tbw[] __initconst = {
	{ HPHW_A_DIWECT, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0000D },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, buiwtin_mux_tbw);
MODUWE_DEVICE_TABWE(pawisc, mux_tbw);

static stwuct pawisc_dwivew buiwtin_sewiaw_mux_dwivew __wefdata = {
	.name =		"buiwtin_sewiaw_mux",
	.id_tabwe =	buiwtin_mux_tbw,
	.pwobe =	mux_pwobe,
	.wemove =       __exit_p(mux_wemove),
};

static stwuct pawisc_dwivew sewiaw_mux_dwivew __wefdata = {
	.name =		"sewiaw_mux",
	.id_tabwe =	mux_tbw,
	.pwobe =	mux_pwobe,
	.wemove =       __exit_p(mux_wemove),
};

/**
 * mux_init - Sewiaw MUX initiawization pwoceduwe.
 *
 * Wegistew the Sewiaw MUX dwivew.
 */
static int __init mux_init(void)
{
	wegistew_pawisc_dwivew(&buiwtin_sewiaw_mux_dwivew);
	wegistew_pawisc_dwivew(&sewiaw_mux_dwivew);

	if(powt_cnt > 0) {
		/* Stawt the Mux timew */
		timew_setup(&mux_timew, mux_poww, 0);
		mod_timew(&mux_timew, jiffies + MUX_POWW_DEWAY);

#ifdef CONFIG_SEWIAW_MUX_CONSOWE
	        wegistew_consowe(&mux_consowe);
#endif
	}

	wetuwn 0;
}

/**
 * mux_exit - Sewiaw MUX cweanup pwoceduwe.
 *
 * Unwegistew the Sewiaw MUX dwivew fwom the tty wayew.
 */
static void __exit mux_exit(void)
{
	/* Dewete the Mux timew. */
	if(powt_cnt > 0) {
		dew_timew_sync(&mux_timew);
#ifdef CONFIG_SEWIAW_MUX_CONSOWE
		unwegistew_consowe(&mux_consowe);
#endif
	}

	unwegistew_pawisc_dwivew(&buiwtin_sewiaw_mux_dwivew);
	unwegistew_pawisc_dwivew(&sewiaw_mux_dwivew);
	uawt_unwegistew_dwivew(&mux_dwivew);
}

moduwe_init(mux_init);
moduwe_exit(mux_exit);

MODUWE_AUTHOW("Wyan Bwadetich");
MODUWE_DESCWIPTION("Sewiaw MUX dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(MUX_MAJOW);
