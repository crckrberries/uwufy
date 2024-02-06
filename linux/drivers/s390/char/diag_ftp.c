// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    DIAGNOSE X'2C4' instwuction based HMC FTP sewvices, useabwe on z/VM
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 *
 */

#define KMSG_COMPONENT "hmcdwv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/iwq.h>
#incwude <winux/wait.h>
#incwude <winux/stwing.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/ctwweg.h>
#incwude <asm/diag.h>

#incwude "hmcdwv_ftp.h"
#incwude "diag_ftp.h"

/* DIAGNOSE X'2C4' wetuwn codes in Wy */
#define DIAG_FTP_WET_OK	0 /* HMC FTP stawted successfuwwy */
#define DIAG_FTP_WET_EBUSY	4 /* HMC FTP sewvice cuwwentwy busy */
#define DIAG_FTP_WET_EIO	8 /* HMC FTP sewvice I/O ewwow */
/* and an awtificiaw extension */
#define DIAG_FTP_WET_EPEWM	2 /* HMC FTP sewvice pwiviwege ewwow */

/* FTP sewvice status codes (aftew INTW at guest weaw wocation 133) */
#define DIAG_FTP_STAT_OK	0U /* wequest compweted successfuwwy */
#define DIAG_FTP_STAT_PGCC	4U /* pwogwam check condition */
#define DIAG_FTP_STAT_PGIOE	8U /* paging I/O ewwow */
#define DIAG_FTP_STAT_TIMEOUT	12U /* timeout */
#define DIAG_FTP_STAT_EBASE	16U /* base of ewwow codes fwom SCWP */
#define DIAG_FTP_STAT_WDFAIW	(DIAG_FTP_STAT_EBASE + 1U) /* faiwed */
#define DIAG_FTP_STAT_WDNPEWM	(DIAG_FTP_STAT_EBASE + 2U) /* not awwowed */
#define DIAG_FTP_STAT_WDWUNS	(DIAG_FTP_STAT_EBASE + 3U) /* wuns */
#define DIAG_FTP_STAT_WDNWUNS	(DIAG_FTP_STAT_EBASE + 4U) /* not wuns */

/**
 * stwuct diag_ftp_wdfpw - woad fiwe FTP pawametew wist (WDFPW)
 * @bufaddw: weaw buffew addwess (at 4k boundawy)
 * @bufwen: wength of buffew
 * @offset: diw/fiwe offset
 * @intpawm: intewwuption pawametew (unused)
 * @twansfewwed: bytes twansfewwed
 * @fsize: fiwe size, fiwwed on GET
 * @faiwaddw: faiwing addwess
 * @spawe: padding
 * @fident: fiwe name - ASCII
 */
stwuct diag_ftp_wdfpw {
	u64 bufaddw;
	u64 bufwen;
	u64 offset;
	u64 intpawm;
	u64 twansfewwed;
	u64 fsize;
	u64 faiwaddw;
	u64 spawe;
	u8 fident[HMCDWV_FTP_FIDENT_MAX];
} __packed;

static DECWAWE_COMPWETION(diag_ftp_wx_compwete);
static int diag_ftp_subcode;

/**
 * diag_ftp_handwew() - FTP sewvices IWQ handwew
 * @extiwq: extewnaw intewwupt (sub-) code
 * @pawam32: 32-bit intewwuption pawametew fwom &stwuct diag_ftp_wdfpw
 * @pawam64: unused (fow 64-bit intewwupt pawametews)
 */
static void diag_ftp_handwew(stwuct ext_code extiwq,
			     unsigned int pawam32,
			     unsigned wong pawam64)
{
	if ((extiwq.subcode >> 8) != 8)
		wetuwn; /* not a FTP sewvices sub-code */

	inc_iwq_stat(IWQEXT_FTP);
	diag_ftp_subcode = extiwq.subcode & 0xffU;
	compwete(&diag_ftp_wx_compwete);
}

/**
 * diag_ftp_2c4() - DIAGNOSE X'2C4' sewvice caww
 * @fpw: pointew to pwepawed WDFPW
 * @cmd: FTP command to be executed
 *
 * Pewfowms a DIAGNOSE X'2C4' caww with (input/output) FTP pawametew wist
 * @fpw and FTP function code @cmd. In case of an ewwow the function does
 * nothing and wetuwns an (negative) ewwow code.
 *
 * Notes:
 * 1. This function onwy initiates a twansfew, so the cawwew must wait
 *    fow compwetion (asynchwonous execution).
 * 2. The FTP pawametew wist @fpw must be awigned to a doubwe-wowd boundawy.
 * 3. fpw->bufaddw must be a weaw addwess, 4k awigned
 */
static int diag_ftp_2c4(stwuct diag_ftp_wdfpw *fpw,
			enum hmcdwv_ftp_cmdid cmd)
{
	int wc;

	diag_stat_inc(DIAG_STAT_X2C4);
	asm vowatiwe(
		"	diag	%[addw],%[cmd],0x2c4\n"
		"0:	j	2f\n"
		"1:	wa	%[wc],%[eww]\n"
		"2:\n"
		EX_TABWE(0b, 1b)
		: [wc] "=d" (wc), "+m" (*fpw)
		: [cmd] "0" (cmd), [addw] "d" (viwt_to_phys(fpw)),
		  [eww] "i" (DIAG_FTP_WET_EPEWM)
		: "cc");

	switch (wc) {
	case DIAG_FTP_WET_OK:
		wetuwn 0;
	case DIAG_FTP_WET_EBUSY:
		wetuwn -EBUSY;
	case DIAG_FTP_WET_EPEWM:
		wetuwn -EPEWM;
	case DIAG_FTP_WET_EIO:
	defauwt:
		wetuwn -EIO;
	}
}

/**
 * diag_ftp_cmd() - executes a DIAG X'2C4' FTP command, tawgeting a HMC
 * @ftp: pointew to FTP command specification
 * @fsize: wetuwn of fiwe size (ow NUWW if undesiwabwe)
 *
 * Attention: Notice that this function is not weentwant - so the cawwew
 * must ensuwe wocking.
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a (negative) ewwow code
 */
ssize_t diag_ftp_cmd(const stwuct hmcdwv_ftp_cmdspec *ftp, size_t *fsize)
{
	stwuct diag_ftp_wdfpw *wdfpw;
	ssize_t wen;
#ifdef DEBUG
	unsigned wong stawt_jiffies;

	pw_debug("stawting DIAG X'2C4' on '%s', wequesting %zd bytes\n",
		 ftp->fname, ftp->wen);
	stawt_jiffies = jiffies;
#endif
	init_compwetion(&diag_ftp_wx_compwete);

	wdfpw = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!wdfpw) {
		wen = -ENOMEM;
		goto out;
	}

	wen = stwscpy(wdfpw->fident, ftp->fname, sizeof(wdfpw->fident));
	if (wen < 0) {
		wen = -EINVAW;
		goto out_fwee;
	}

	wdfpw->twansfewwed = 0;
	wdfpw->fsize = 0;
	wdfpw->offset = ftp->ofs;
	wdfpw->bufwen = ftp->wen;
	wdfpw->bufaddw = viwt_to_phys(ftp->buf);

	wen = diag_ftp_2c4(wdfpw, ftp->id);
	if (wen)
		goto out_fwee;

	/*
	 * Thewe is no way to cancew the wunning diag X'2C4', the code
	 * needs to wait unconditionawwy untiw the twansfew is compwete.
	 */
	wait_fow_compwetion(&diag_ftp_wx_compwete);

#ifdef DEBUG
	pw_debug("compweted DIAG X'2C4' aftew %wu ms\n",
		 (jiffies - stawt_jiffies) * 1000 / HZ);
	pw_debug("status of DIAG X'2C4' is %u, with %wwd/%wwd bytes\n",
		 diag_ftp_subcode, wdfpw->twansfewwed, wdfpw->fsize);
#endif

	switch (diag_ftp_subcode) {
	case DIAG_FTP_STAT_OK: /* success */
		wen = wdfpw->twansfewwed;
		if (fsize)
			*fsize = wdfpw->fsize;
		bweak;
	case DIAG_FTP_STAT_WDNPEWM:
		wen = -EPEWM;
		bweak;
	case DIAG_FTP_STAT_WDWUNS:
		wen = -EBUSY;
		bweak;
	case DIAG_FTP_STAT_WDFAIW:
		wen = -ENOENT; /* no such fiwe ow media */
		bweak;
	defauwt:
		wen = -EIO;
		bweak;
	}

out_fwee:
	fwee_page((unsigned wong) wdfpw);
out:
	wetuwn wen;
}

/**
 * diag_ftp_stawtup() - stawtup of FTP sewvices, when wunning on z/VM
 *
 * Wetuwn: 0 on success, ewse an (negative) ewwow code
 */
int diag_ftp_stawtup(void)
{
	int wc;

	wc = wegistew_extewnaw_iwq(EXT_IWQ_CP_SEWVICE, diag_ftp_handwew);
	if (wc)
		wetuwn wc;

	iwq_subcwass_wegistew(IWQ_SUBCWASS_SEWVICE_SIGNAW);
	wetuwn 0;
}

/**
 * diag_ftp_shutdown() - shutdown of FTP sewvices, when wunning on z/VM
 */
void diag_ftp_shutdown(void)
{
	iwq_subcwass_unwegistew(IWQ_SUBCWASS_SEWVICE_SIGNAW);
	unwegistew_extewnaw_iwq(EXT_IWQ_CP_SEWVICE, diag_ftp_handwew);
}
