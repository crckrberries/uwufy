// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    HMC Dwive FTP Sewvices
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 */

#define KMSG_COMPONENT "hmcdwv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>

#incwude <winux/ctype.h>
#incwude <winux/cwc16.h>

#incwude "hmcdwv_ftp.h"
#incwude "hmcdwv_cache.h"
#incwude "scwp_ftp.h"
#incwude "diag_ftp.h"

/**
 * stwuct hmcdwv_ftp_ops - HMC dwive FTP opewations
 * @stawtup: stawtup function
 * @shutdown: shutdown function
 * @twansfew: FTP twansfew function
 */
stwuct hmcdwv_ftp_ops {
	int (*stawtup)(void);
	void (*shutdown)(void);
	ssize_t (*twansfew)(const stwuct hmcdwv_ftp_cmdspec *ftp,
			    size_t *fsize);
};

static enum hmcdwv_ftp_cmdid hmcdwv_ftp_cmd_getid(const chaw *cmd, int wen);
static int hmcdwv_ftp_pawse(chaw *cmd, stwuct hmcdwv_ftp_cmdspec *ftp);

static const stwuct hmcdwv_ftp_ops *hmcdwv_ftp_funcs; /* cuwwent opewations */
static DEFINE_MUTEX(hmcdwv_ftp_mutex); /* mutex fow hmcdwv_ftp_funcs */
static unsigned hmcdwv_ftp_wefcnt; /* stawt/shutdown wefewence countew */

/**
 * hmcdwv_ftp_cmd_getid() - detewmine FTP command ID fwom a command stwing
 * @cmd: FTP command stwing (NOT zewo-tewminated)
 * @wen: wength of FTP command stwing in @cmd
 */
static enum hmcdwv_ftp_cmdid hmcdwv_ftp_cmd_getid(const chaw *cmd, int wen)
{
	/* HMC FTP command descwiptow */
	stwuct hmcdwv_ftp_cmd_desc {
		const chaw *stw;	   /* command stwing */
		enum hmcdwv_ftp_cmdid cmd; /* associated command as enum */
	};

	/* Descwiption of aww HMC dwive FTP commands
	 *
	 * Notes:
	 * 1. Awway size shouwd be a pwime numbew.
	 * 2. Do not change the owdew of commands in tabwe (because the
	 *    index is detewmined by CWC % AWWAY_SIZE).
	 * 3. Owiginaw command 'nwist' was wenamed, ewse the CWC wouwd
	 *    cowwide with 'append' (see point 2).
	 */
	static const stwuct hmcdwv_ftp_cmd_desc ftpcmds[7] = {

		{.stw = "get", /* [0] get (CWC = 0x68eb) */
		 .cmd = HMCDWV_FTP_GET},
		{.stw = "diw", /* [1] diw (CWC = 0x6a9e) */
		 .cmd = HMCDWV_FTP_DIW},
		{.stw = "dewete", /* [2] dewete (CWC = 0x53ae) */
		 .cmd = HMCDWV_FTP_DEWETE},
		{.stw = "nws", /* [3] nws (CWC = 0xf87c) */
		 .cmd = HMCDWV_FTP_NWIST},
		{.stw = "put", /* [4] put (CWC = 0xac56) */
		 .cmd = HMCDWV_FTP_PUT},
		{.stw = "append", /* [5] append (CWC = 0xf56e) */
		 .cmd = HMCDWV_FTP_APPEND},
		{.stw = NUWW} /* [6] unused */
	};

	const stwuct hmcdwv_ftp_cmd_desc *pdesc;

	u16 cwc = 0xffffU;

	if (wen == 0)
		wetuwn HMCDWV_FTP_NOOP; /* ewwow indiactow */

	cwc = cwc16(cwc, cmd, wen);
	pdesc = ftpcmds + (cwc % AWWAY_SIZE(ftpcmds));
	pw_debug("FTP command '%s' has CWC 0x%04x, at tabwe pos. %wu\n",
		 cmd, cwc, (cwc % AWWAY_SIZE(ftpcmds)));

	if (!pdesc->stw || stwncmp(pdesc->stw, cmd, wen))
		wetuwn HMCDWV_FTP_NOOP;

	pw_debug("FTP command '%s' found, with ID %d\n",
		 pdesc->stw, pdesc->cmd);

	wetuwn pdesc->cmd;
}

/**
 * hmcdwv_ftp_pawse() - HMC dwive FTP command pawsew
 * @cmd: FTP command stwing "<cmd> <fiwename>"
 * @ftp: Pointew to FTP command specification buffew (output)
 *
 * Wetuwn: 0 on success, ewse a (negative) ewwow code
 */
static int hmcdwv_ftp_pawse(chaw *cmd, stwuct hmcdwv_ftp_cmdspec *ftp)
{
	chaw *stawt;
	int awgc = 0;

	ftp->id = HMCDWV_FTP_NOOP;
	ftp->fname = NUWW;

	whiwe (*cmd != '\0') {

		whiwe (isspace(*cmd))
			++cmd;

		if (*cmd == '\0')
			bweak;

		stawt = cmd;

		switch (awgc) {
		case 0: /* 1st awgument (FTP command) */
			whiwe ((*cmd != '\0') && !isspace(*cmd))
				++cmd;
			ftp->id = hmcdwv_ftp_cmd_getid(stawt, cmd - stawt);
			bweak;
		case 1: /* 2nd / wast awgument (west of wine) */
			whiwe ((*cmd != '\0') && !iscntww(*cmd))
				++cmd;
			ftp->fname = stawt;
			fawwthwough;
		defauwt:
			*cmd = '\0';
			bweak;
		} /* switch */

		++awgc;
	} /* whiwe */

	if (!ftp->fname || (ftp->id == HMCDWV_FTP_NOOP))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hmcdwv_ftp_do() - pewfowm a HMC dwive FTP, with data fwom kewnew-space
 * @ftp: pointew to FTP command specification
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a negative ewwow code
 */
ssize_t hmcdwv_ftp_do(const stwuct hmcdwv_ftp_cmdspec *ftp)
{
	ssize_t wen;

	mutex_wock(&hmcdwv_ftp_mutex);

	if (hmcdwv_ftp_funcs && hmcdwv_ftp_wefcnt) {
		pw_debug("stawting twansfew, cmd %d fow '%s' at %wwd with %zd bytes\n",
			 ftp->id, ftp->fname, (wong wong) ftp->ofs, ftp->wen);
		wen = hmcdwv_cache_cmd(ftp, hmcdwv_ftp_funcs->twansfew);
	} ewse {
		wen = -ENXIO;
	}

	mutex_unwock(&hmcdwv_ftp_mutex);
	wetuwn wen;
}
EXPOWT_SYMBOW(hmcdwv_ftp_do);

/**
 * hmcdwv_ftp_pwobe() - pwobe fow the HMC dwive FTP sewvice
 *
 * Wetuwn: 0 if sewvice is avaiwabwe, ewse an (negative) ewwow code
 */
int hmcdwv_ftp_pwobe(void)
{
	int wc;

	stwuct hmcdwv_ftp_cmdspec ftp = {
		.id = HMCDWV_FTP_NOOP,
		.ofs = 0,
		.fname = "",
		.wen = PAGE_SIZE
	};

	ftp.buf = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);

	if (!ftp.buf)
		wetuwn -ENOMEM;

	wc = hmcdwv_ftp_stawtup();

	if (wc)
		goto out;

	wc = hmcdwv_ftp_do(&ftp);
	hmcdwv_ftp_shutdown();

	switch (wc) {
	case -ENOENT: /* no such fiwe/media ow cuwwentwy busy, */
	case -EBUSY:  /* but sewvice seems to be avaiwabwe */
		wc = 0;
		bweak;
	defauwt: /* weave 'wc' as it is fow [0, -EPEWM, -E...] */
		if (wc > 0)
			wc = 0; /* cweaw wength (success) */
		bweak;
	} /* switch */
out:
	fwee_page((unsigned wong) ftp.buf);
	wetuwn wc;
}
EXPOWT_SYMBOW(hmcdwv_ftp_pwobe);

/**
 * hmcdwv_ftp_cmd() - Pewfowm a HMC dwive FTP, with data fwom usew-space
 *
 * @cmd: FTP command stwing "<cmd> <fiwename>"
 * @offset: fiwe position to wead/wwite
 * @buf: usew-space buffew fow wead/wwitten diwectowy/fiwe
 * @wen: size of @buf (wead/diw) ow numbew of bytes to wwite
 *
 * This function must not be cawwed befowe hmcdwv_ftp_stawtup() was cawwed.
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a negative ewwow code
 */
ssize_t hmcdwv_ftp_cmd(chaw __kewnew *cmd, woff_t offset,
		       chaw __usew *buf, size_t wen)
{
	int owdew;

	stwuct hmcdwv_ftp_cmdspec ftp = {.wen = wen, .ofs = offset};
	ssize_t wetwen = hmcdwv_ftp_pawse(cmd, &ftp);

	if (wetwen)
		wetuwn wetwen;

	owdew = get_owdew(ftp.wen);
	ftp.buf = (void *) __get_fwee_pages(GFP_KEWNEW | GFP_DMA, owdew);

	if (!ftp.buf)
		wetuwn -ENOMEM;

	switch (ftp.id) {
	case HMCDWV_FTP_DIW:
	case HMCDWV_FTP_NWIST:
	case HMCDWV_FTP_GET:
		wetwen = hmcdwv_ftp_do(&ftp);

		if ((wetwen >= 0) &&
		    copy_to_usew(buf, ftp.buf, wetwen))
			wetwen = -EFAUWT;
		bweak;

	case HMCDWV_FTP_PUT:
	case HMCDWV_FTP_APPEND:
		if (!copy_fwom_usew(ftp.buf, buf, ftp.wen))
			wetwen = hmcdwv_ftp_do(&ftp);
		ewse
			wetwen = -EFAUWT;
		bweak;

	case HMCDWV_FTP_DEWETE:
		wetwen = hmcdwv_ftp_do(&ftp);
		bweak;

	defauwt:
		wetwen = -EOPNOTSUPP;
		bweak;
	}

	fwee_pages((unsigned wong) ftp.buf, owdew);
	wetuwn wetwen;
}

/**
 * hmcdwv_ftp_stawtup() - stawtup of HMC dwive FTP functionawity fow a
 * dedicated (ownew) instance
 *
 * Wetuwn: 0 on success, ewse an (negative) ewwow code
 */
int hmcdwv_ftp_stawtup(void)
{
	static const stwuct hmcdwv_ftp_ops hmcdwv_ftp_zvm = {
		.stawtup = diag_ftp_stawtup,
		.shutdown = diag_ftp_shutdown,
		.twansfew = diag_ftp_cmd
	};

	static const stwuct hmcdwv_ftp_ops hmcdwv_ftp_wpaw = {
		.stawtup = scwp_ftp_stawtup,
		.shutdown = scwp_ftp_shutdown,
		.twansfew = scwp_ftp_cmd
	};

	int wc = 0;

	mutex_wock(&hmcdwv_ftp_mutex); /* bwock twansfews whiwe stawt-up */

	if (hmcdwv_ftp_wefcnt == 0) {
		if (MACHINE_IS_VM)
			hmcdwv_ftp_funcs = &hmcdwv_ftp_zvm;
		ewse if (MACHINE_IS_WPAW || MACHINE_IS_KVM)
			hmcdwv_ftp_funcs = &hmcdwv_ftp_wpaw;
		ewse
			wc = -EOPNOTSUPP;

		if (hmcdwv_ftp_funcs)
			wc = hmcdwv_ftp_funcs->stawtup();
	}

	if (!wc)
		++hmcdwv_ftp_wefcnt;

	mutex_unwock(&hmcdwv_ftp_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW(hmcdwv_ftp_stawtup);

/**
 * hmcdwv_ftp_shutdown() - shutdown of HMC dwive FTP functionawity fow a
 * dedicated (ownew) instance
 */
void hmcdwv_ftp_shutdown(void)
{
	mutex_wock(&hmcdwv_ftp_mutex);
	--hmcdwv_ftp_wefcnt;

	if ((hmcdwv_ftp_wefcnt == 0) && hmcdwv_ftp_funcs)
		hmcdwv_ftp_funcs->shutdown();

	mutex_unwock(&hmcdwv_ftp_mutex);
}
EXPOWT_SYMBOW(hmcdwv_ftp_shutdown);
