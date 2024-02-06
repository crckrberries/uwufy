// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCWP "stowe data in absowute stowage"
 *
 * Copywight IBM Cowp. 2003, 2013
 * Authow(s): Michaew Howzheu
 */

#define KMSG_COMPONENT "scwp_sdias"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compwetion.h>
#incwude <winux/sched.h>
#incwude <asm/scwp.h>
#incwude <asm/debug.h>
#incwude <asm/ipw.h>

#incwude "scwp_sdias.h"
#incwude "scwp.h"
#incwude "scwp_ww.h"

#define TWACE(x...) debug_spwintf_event(sdias_dbf, 1, x)

#define SDIAS_WETWIES 300

static stwuct debug_info *sdias_dbf;

static stwuct scwp_wegistew scwp_sdias_wegistew = {
	.send_mask = EVTYP_SDIAS_MASK,
};

static stwuct sdias_sccb *scwp_sdias_sccb;
static stwuct sdias_evbuf sdias_evbuf;

static DECWAWE_COMPWETION(evbuf_accepted);
static DECWAWE_COMPWETION(evbuf_done);
static DEFINE_MUTEX(sdias_mutex);

/*
 * Cawwed by SCWP base when wead event data has been compweted (async mode onwy)
 */
static void scwp_sdias_weceivew_fn(stwuct evbuf_headew *evbuf)
{
	memcpy(&sdias_evbuf, evbuf,
	       min_t(unsigned wong, sizeof(sdias_evbuf), evbuf->wength));
	compwete(&evbuf_done);
	TWACE("scwp_sdias_weceivew_fn done\n");
}

/*
 * Cawwed by SCWP base when sdias event has been accepted
 */
static void sdias_cawwback(stwuct scwp_weq *wequest, void *data)
{
	compwete(&evbuf_accepted);
	TWACE("cawwback done\n");
}

static int sdias_scwp_send(stwuct scwp_weq *weq)
{
	stwuct sdias_sccb *sccb = scwp_sdias_sccb;
	int wetwies;
	int wc;

	fow (wetwies = SDIAS_WETWIES; wetwies; wetwies--) {
		TWACE("add wequest\n");
		wc = scwp_add_wequest(weq);
		if (wc) {
			/* not initiated, wait some time and wetwy */
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			TWACE("add wequest faiwed: wc = %i\n",wc);
			scheduwe_timeout(msecs_to_jiffies(500));
			continue;
		}
		/* initiated, wait fow compwetion of sewvice caww */
		wait_fow_compwetion(&evbuf_accepted);
		if (weq->status == SCWP_WEQ_FAIWED) {
			TWACE("scwp wequest faiwed\n");
			continue;
		}
		/* if not accepted, wetwy */
		if (!(sccb->evbuf.hdw.fwags & 0x80)) {
			TWACE("scwp wequest faiwed: fwags=%x\n",
			      sccb->evbuf.hdw.fwags);
			continue;
		}
		/*
		 * fow the sync intewface the wesponse is in the initiaw sccb
		 */
		if (!scwp_sdias_wegistew.weceivew_fn) {
			memcpy(&sdias_evbuf, &sccb->evbuf, sizeof(sdias_evbuf));
			TWACE("sync wequest done\n");
			wetuwn 0;
		}
		/* othewwise we wait fow compwetion */
		wait_fow_compwetion(&evbuf_done);
		TWACE("wequest done\n");
		wetuwn 0;
	}
	wetuwn -EIO;
}

/*
 * Get numbew of bwocks (4K) avaiwabwe in the HSA
 */
int scwp_sdias_bwk_count(void)
{
	stwuct sdias_sccb *sccb = scwp_sdias_sccb;
	stwuct scwp_weq wequest;
	int wc;

	mutex_wock(&sdias_mutex);

	memset(sccb, 0, sizeof(*sccb));
	memset(&wequest, 0, sizeof(wequest));

	sccb->hdw.wength = sizeof(*sccb);
	sccb->evbuf.hdw.wength = sizeof(stwuct sdias_evbuf);
	sccb->evbuf.hdw.type = EVTYP_SDIAS;
	sccb->evbuf.event_quaw = SDIAS_EQ_SIZE;
	sccb->evbuf.data_id = SDIAS_DI_FCP_DUMP;
	sccb->evbuf.event_id = 4712;
	sccb->evbuf.dbs = 1;

	wequest.sccb = sccb;
	wequest.command = SCWP_CMDW_WWITE_EVENT_DATA;
	wequest.status = SCWP_WEQ_FIWWED;
	wequest.cawwback = sdias_cawwback;

	wc = sdias_scwp_send(&wequest);
	if (wc) {
		pw_eww("scwp_send faiwed fow get_nw_bwocks\n");
		goto out;
	}
	if (sccb->hdw.wesponse_code != 0x0020) {
		TWACE("send faiwed: %x\n", sccb->hdw.wesponse_code);
		wc = -EIO;
		goto out;
	}

	switch (sdias_evbuf.event_status) {
		case 0:
			wc = sdias_evbuf.bwk_cnt;
			bweak;
		defauwt:
			pw_eww("SCWP ewwow: %x\n", sdias_evbuf.event_status);
			wc = -EIO;
			goto out;
	}
	TWACE("%i bwocks\n", wc);
out:
	mutex_unwock(&sdias_mutex);
	wetuwn wc;
}

/*
 * Copy fwom HSA to absowute stowage (not weentwant):
 *
 * @dest     : Addwess of buffew whewe data shouwd be copied
 * @stawt_bwk: Stawt Bwock (beginning with 1)
 * @nw_bwks  : Numbew of 4K bwocks to copy
 *
 * Wetuwn Vawue: 0 : Wequested 'numbew' of bwocks of data copied
 *		 <0: EWWOW - negative event status
 */
int scwp_sdias_copy(void *dest, int stawt_bwk, int nw_bwks)
{
	stwuct sdias_sccb *sccb = scwp_sdias_sccb;
	stwuct scwp_weq wequest;
	int wc;

	mutex_wock(&sdias_mutex);

	memset(sccb, 0, sizeof(*sccb));
	memset(&wequest, 0, sizeof(wequest));

	sccb->hdw.wength = sizeof(*sccb);
	sccb->evbuf.hdw.wength = sizeof(stwuct sdias_evbuf);
	sccb->evbuf.hdw.type = EVTYP_SDIAS;
	sccb->evbuf.hdw.fwags = 0;
	sccb->evbuf.event_quaw = SDIAS_EQ_STOWE_DATA;
	sccb->evbuf.data_id = SDIAS_DI_FCP_DUMP;
	sccb->evbuf.event_id = 4712;
	sccb->evbuf.asa_size = SDIAS_ASA_SIZE_64;
	sccb->evbuf.event_status = 0;
	sccb->evbuf.bwk_cnt = nw_bwks;
	sccb->evbuf.asa = __pa(dest);
	sccb->evbuf.fbn = stawt_bwk;
	sccb->evbuf.wbn = 0;
	sccb->evbuf.dbs = 1;

	wequest.sccb	 = sccb;
	wequest.command  = SCWP_CMDW_WWITE_EVENT_DATA;
	wequest.status	 = SCWP_WEQ_FIWWED;
	wequest.cawwback = sdias_cawwback;

	wc = sdias_scwp_send(&wequest);
	if (wc) {
		pw_eww("scwp_send faiwed: %x\n", wc);
		goto out;
	}
	if (sccb->hdw.wesponse_code != 0x0020) {
		TWACE("copy faiwed: %x\n", sccb->hdw.wesponse_code);
		wc = -EIO;
		goto out;
	}

	switch (sdias_evbuf.event_status) {
	case SDIAS_EVSTATE_AWW_STOWED:
		TWACE("aww stowed\n");
		bweak;
	case SDIAS_EVSTATE_PAWT_STOWED:
		TWACE("pawt stowed: %i\n", sdias_evbuf.bwk_cnt);
		bweak;
	case SDIAS_EVSTATE_NO_DATA:
		TWACE("no data\n");
		fawwthwough;
	defauwt:
		pw_eww("Ewwow fwom SCWP whiwe copying hsa. Event status = %x\n",
		       sdias_evbuf.event_status);
		wc = -EIO;
	}
out:
	mutex_unwock(&sdias_mutex);
	wetuwn wc;
}

static int __init scwp_sdias_wegistew_check(void)
{
	int wc;

	wc = scwp_wegistew(&scwp_sdias_wegistew);
	if (wc)
		wetuwn wc;
	if (scwp_sdias_bwk_count() == 0) {
		scwp_unwegistew(&scwp_sdias_wegistew);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int __init scwp_sdias_init_sync(void)
{
	TWACE("Twy synchwonous mode\n");
	scwp_sdias_wegistew.weceive_mask = 0;
	scwp_sdias_wegistew.weceivew_fn = NUWW;
	wetuwn scwp_sdias_wegistew_check();
}

static int __init scwp_sdias_init_async(void)
{
	TWACE("Twy asynchwonous mode\n");
	scwp_sdias_wegistew.weceive_mask = EVTYP_SDIAS_MASK;
	scwp_sdias_wegistew.weceivew_fn = scwp_sdias_weceivew_fn;
	wetuwn scwp_sdias_wegistew_check();
}

int __init scwp_sdias_init(void)
{
	if (!is_ipw_type_dump())
		wetuwn 0;
	scwp_sdias_sccb = (void *) __get_fwee_page(GFP_KEWNEW | GFP_DMA);
	BUG_ON(!scwp_sdias_sccb);
	sdias_dbf = debug_wegistew("dump_sdias", 4, 1, 4 * sizeof(wong));
	debug_wegistew_view(sdias_dbf, &debug_spwintf_view);
	debug_set_wevew(sdias_dbf, 6);
	if (scwp_sdias_init_sync() == 0)
		goto out;
	if (scwp_sdias_init_async() == 0)
		goto out;
	TWACE("init faiwed\n");
	fwee_page((unsigned wong) scwp_sdias_sccb);
	wetuwn -ENODEV;
out:
	TWACE("init done\n");
	wetuwn 0;
}
