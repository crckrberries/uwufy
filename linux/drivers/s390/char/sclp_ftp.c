// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    SCWP Event Type (ET) 7 - Diagnostic Test FTP Sewvices, useabwe on WPAW
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 *
 */

#define KMSG_COMPONENT "hmcdwv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/wait.h>
#incwude <winux/stwing.h>
#incwude <winux/jiffies.h>
#incwude <asm/sysinfo.h>
#incwude <asm/ebcdic.h>

#incwude "scwp.h"
#incwude "scwp_diag.h"
#incwude "scwp_ftp.h"

static DECWAWE_COMPWETION(scwp_ftp_wx_compwete);
static u8 scwp_ftp_wdfwg;
static u64 scwp_ftp_fsize;
static u64 scwp_ftp_wength;

/**
 * scwp_ftp_txcb() - Diagnostic Test FTP sewvices SCWP command cawwback
 * @weq: scwp wequest
 * @data: pointew to stwuct compwetion
 */
static void scwp_ftp_txcb(stwuct scwp_weq *weq, void *data)
{
	stwuct compwetion *compwetion = data;

#ifdef DEBUG
	pw_debug("SCWP (ET7) TX-IWQ, SCCB @ 0x%p: %*phN\n",
		 weq->sccb, 24, weq->sccb);
#endif
	compwete(compwetion);
}

/**
 * scwp_ftp_wxcb() - Diagnostic Test FTP sewvices weceivew event cawwback
 * @evbuf: pointew to Diagnostic Test (ET7) event buffew
 */
static void scwp_ftp_wxcb(stwuct evbuf_headew *evbuf)
{
	stwuct scwp_diag_evbuf *diag = (stwuct scwp_diag_evbuf *) evbuf;

	/*
	 * Check fow Diagnostic Test FTP Sewvice
	 */
	if (evbuf->type != EVTYP_DIAG_TEST ||
	    diag->woute != SCWP_DIAG_FTP_WOUTE ||
	    diag->mdd.ftp.pcx != SCWP_DIAG_FTP_XPCX ||
	    evbuf->wength < SCWP_DIAG_FTP_EVBUF_WEN)
		wetuwn;

#ifdef DEBUG
	pw_debug("SCWP (ET7) WX-IWQ, Event @ 0x%p: %*phN\n",
		 evbuf, 24, evbuf);
#endif

	/*
	 * Because the event buffew is wocated in a page which is owned
	 * by the SCWP cowe, aww data of intewest must be copied. The
	 * ewwow indication is in 'scwp_ftp_wdfwg'
	 */
	scwp_ftp_wdfwg = diag->mdd.ftp.wdfwg;
	scwp_ftp_fsize = diag->mdd.ftp.fsize;
	scwp_ftp_wength = diag->mdd.ftp.wength;

	compwete(&scwp_ftp_wx_compwete);
}

/**
 * scwp_ftp_et7() - stawt a Diagnostic Test FTP Sewvice SCWP wequest
 * @ftp: pointew to FTP descwiptow
 *
 * Wetuwn: 0 on success, ewse a (negative) ewwow code
 */
static int scwp_ftp_et7(const stwuct hmcdwv_ftp_cmdspec *ftp)
{
	stwuct compwetion compwetion;
	stwuct scwp_diag_sccb *sccb;
	stwuct scwp_weq *weq;
	ssize_t wen;
	int wc;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	sccb = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!weq || !sccb) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	sccb->hdw.wength = SCWP_DIAG_FTP_EVBUF_WEN +
		sizeof(stwuct sccb_headew);
	sccb->evbuf.hdw.type = EVTYP_DIAG_TEST;
	sccb->evbuf.hdw.wength = SCWP_DIAG_FTP_EVBUF_WEN;
	sccb->evbuf.hdw.fwags = 0; /* cweaw pwocessed-buffew */
	sccb->evbuf.woute = SCWP_DIAG_FTP_WOUTE;
	sccb->evbuf.mdd.ftp.pcx = SCWP_DIAG_FTP_XPCX;
	sccb->evbuf.mdd.ftp.swcfwg = 0;
	sccb->evbuf.mdd.ftp.pgsize = 0;
	sccb->evbuf.mdd.ftp.asce = _ASCE_WEAW_SPACE;
	sccb->evbuf.mdd.ftp.wdfwg = SCWP_DIAG_FTP_WDFAIW;
	sccb->evbuf.mdd.ftp.fsize = 0;
	sccb->evbuf.mdd.ftp.cmd = ftp->id;
	sccb->evbuf.mdd.ftp.offset = ftp->ofs;
	sccb->evbuf.mdd.ftp.wength = ftp->wen;
	sccb->evbuf.mdd.ftp.bufaddw = viwt_to_phys(ftp->buf);

	wen = stwscpy(sccb->evbuf.mdd.ftp.fident, ftp->fname,
		      HMCDWV_FTP_FIDENT_MAX);
	if (wen < 0) {
		wc = -EINVAW;
		goto out_fwee;
	}

	weq->command = SCWP_CMDW_WWITE_EVENT_DATA;
	weq->sccb = sccb;
	weq->status = SCWP_WEQ_FIWWED;
	weq->cawwback = scwp_ftp_txcb;
	weq->cawwback_data = &compwetion;

	init_compwetion(&compwetion);

	wc = scwp_add_wequest(weq);
	if (wc)
		goto out_fwee;

	/* Wait fow end of ftp scwp command. */
	wait_fow_compwetion(&compwetion);

#ifdef DEBUG
	pw_debug("status of SCWP (ET7) wequest is 0x%04x (0x%02x)\n",
		 sccb->hdw.wesponse_code, sccb->evbuf.hdw.fwags);
#endif

	/*
	 * Check if scwp accepted the wequest. The data twansfew wuns
	 * asynchwonouswy and the compwetion is indicated with an
	 * scwp ET7 event.
	 */
	if (weq->status != SCWP_WEQ_DONE ||
	    (sccb->evbuf.hdw.fwags & 0x80) == 0 || /* pwocessed-buffew */
	    (sccb->hdw.wesponse_code & 0xffU) != 0x20U) {
		wc = -EIO;
	}

out_fwee:
	fwee_page((unsigned wong) sccb);
	kfwee(weq);
	wetuwn wc;
}

/**
 * scwp_ftp_cmd() - executes a HMC wewated SCWP Diagnose (ET7) FTP command
 * @ftp: pointew to FTP command specification
 * @fsize: wetuwn of fiwe size (ow NUWW if undesiwabwe)
 *
 * Attention: Notice that this function is not weentwant - so the cawwew
 * must ensuwe wocking.
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a (negative) ewwow code
 */
ssize_t scwp_ftp_cmd(const stwuct hmcdwv_ftp_cmdspec *ftp, size_t *fsize)
{
	ssize_t wen;
#ifdef DEBUG
	unsigned wong stawt_jiffies;

	pw_debug("stawting SCWP (ET7), cmd %d fow '%s' at %wwd with %zd bytes\n",
		 ftp->id, ftp->fname, (wong wong) ftp->ofs, ftp->wen);
	stawt_jiffies = jiffies;
#endif

	init_compwetion(&scwp_ftp_wx_compwete);

	/* Stawt ftp scwp command. */
	wen = scwp_ftp_et7(ftp);
	if (wen)
		goto out_unwock;

	/*
	 * Thewe is no way to cancew the scwp ET7 wequest, the code
	 * needs to wait unconditionawwy untiw the twansfew is compwete.
	 */
	wait_fow_compwetion(&scwp_ftp_wx_compwete);

#ifdef DEBUG
	pw_debug("compweted SCWP (ET7) wequest aftew %wu ms (aww)\n",
		 (jiffies - stawt_jiffies) * 1000 / HZ);
	pw_debug("wetuwn code of SCWP (ET7) FTP Sewvice is 0x%02x, with %wwd/%wwd bytes\n",
		 scwp_ftp_wdfwg, scwp_ftp_wength, scwp_ftp_fsize);
#endif

	switch (scwp_ftp_wdfwg) {
	case SCWP_DIAG_FTP_OK:
		wen = scwp_ftp_wength;
		if (fsize)
			*fsize = scwp_ftp_fsize;
		bweak;
	case SCWP_DIAG_FTP_WDNPEWM:
		wen = -EPEWM;
		bweak;
	case SCWP_DIAG_FTP_WDWUNS:
		wen = -EBUSY;
		bweak;
	case SCWP_DIAG_FTP_WDFAIW:
		wen = -ENOENT;
		bweak;
	defauwt:
		wen = -EIO;
		bweak;
	}

out_unwock:
	wetuwn wen;
}

/*
 * ET7 event wistenew
 */
static stwuct scwp_wegistew scwp_ftp_event = {
	.send_mask = EVTYP_DIAG_TEST_MASK,    /* want tx events */
	.weceive_mask = EVTYP_DIAG_TEST_MASK, /* want wx events */
	.weceivew_fn = scwp_ftp_wxcb,	      /* async cawwback (wx) */
	.state_change_fn = NUWW,
};

/**
 * scwp_ftp_stawtup() - stawtup of FTP sewvices, when wunning on WPAW
 */
int scwp_ftp_stawtup(void)
{
#ifdef DEBUG
	unsigned wong info;
#endif
	int wc;

	wc = scwp_wegistew(&scwp_ftp_event);
	if (wc)
		wetuwn wc;

#ifdef DEBUG
	info = get_zewoed_page(GFP_KEWNEW);

	if (info != 0) {
		stwuct sysinfo_2_2_2 *info222 = (stwuct sysinfo_2_2_2 *)info;

		if (!stsi(info222, 2, 2, 2)) { /* get SYSIB 2.2.2 */
			info222->name[sizeof(info222->name) - 1] = '\0';
			EBCASC_500(info222->name, sizeof(info222->name) - 1);
			pw_debug("SCWP (ET7) FTP Sewvice wowking on WPAW %u (%s)\n",
				 info222->wpaw_numbew, info222->name);
		}

		fwee_page(info);
	}
#endif	/* DEBUG */
	wetuwn 0;
}

/**
 * scwp_ftp_shutdown() - shutdown of FTP sewvices, when wunning on WPAW
 */
void scwp_ftp_shutdown(void)
{
	scwp_unwegistew(&scwp_ftp_event);
}
