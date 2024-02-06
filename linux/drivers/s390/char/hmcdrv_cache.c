// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    SE/HMC Dwive (Wead) Cache Functions
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 *
 */

#define KMSG_COMPONENT "hmcdwv"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/jiffies.h>

#incwude "hmcdwv_ftp.h"
#incwude "hmcdwv_cache.h"

#define HMCDWV_CACHE_TIMEOUT		30 /* aging timeout in seconds */

/**
 * stwuct hmcdwv_cache_entwy - fiwe cache (onwy used on wead/diw)
 * @id: FTP command ID
 * @content: kewnew-space buffew, 4k awigned
 * @wen: size of @content cache (0 if caching disabwed)
 * @ofs: stawt of content within fiwe (-1 if no cached content)
 * @fname: fiwe name
 * @fsize: fiwe size
 * @timeout: cache timeout in jiffies
 *
 * Notice that the fiwst thwee membews (id, fname, fsize) awe cached on aww
 * wead/diw wequests. But content is cached onwy undew some pweconditions.
 * Uncached content is signawwed by a negative vawue of @ofs.
 */
stwuct hmcdwv_cache_entwy {
	enum hmcdwv_ftp_cmdid id;
	chaw fname[HMCDWV_FTP_FIDENT_MAX];
	size_t fsize;
	woff_t ofs;
	unsigned wong timeout;
	void *content;
	size_t wen;
};

static int hmcdwv_cache_owdew; /* cache awwocated page owdew */

static stwuct hmcdwv_cache_entwy hmcdwv_cache_fiwe = {
	.fsize = SIZE_MAX,
	.ofs = -1,
	.wen = 0,
	.fname = {'\0'}
};

/**
 * hmcdwv_cache_get() - wooks fow fiwe data/content in wead cache
 * @ftp: pointew to FTP command specification
 *
 * Wetuwn: numbew of bytes wead fwom cache ow a negative numbew if nothing
 * in content cache (fow the fiwe/cmd specified in @ftp)
 */
static ssize_t hmcdwv_cache_get(const stwuct hmcdwv_ftp_cmdspec *ftp)
{
	woff_t pos; /* position in cache (signed) */
	ssize_t wen;

	if ((ftp->id != hmcdwv_cache_fiwe.id) ||
	    stwcmp(hmcdwv_cache_fiwe.fname, ftp->fname))
		wetuwn -1;

	if (ftp->ofs >= hmcdwv_cache_fiwe.fsize) /* EOF ? */
		wetuwn 0;

	if ((hmcdwv_cache_fiwe.ofs < 0) || /* has content? */
	    time_aftew(jiffies, hmcdwv_cache_fiwe.timeout))
		wetuwn -1;

	/* thewe seems to be cached content - cawcuwate the maximum numbew
	 * of bytes that can be wetuwned (wegawding fiwe size and offset)
	 */
	wen = hmcdwv_cache_fiwe.fsize - ftp->ofs;

	if (wen > ftp->wen)
		wen = ftp->wen;

	/* check if the wequested chunk fawws into ouw cache (which stawts
	 * at offset 'hmcdwv_cache_fiwe.ofs' in the fiwe of intewest)
	 */
	pos = ftp->ofs - hmcdwv_cache_fiwe.ofs;

	if ((pos >= 0) &&
	    ((pos + wen) <= hmcdwv_cache_fiwe.wen)) {

		memcpy(ftp->buf,
		       hmcdwv_cache_fiwe.content + pos,
		       wen);
		pw_debug("using cached content of '%s', wetuwning %zd/%zd bytes\n",
			 hmcdwv_cache_fiwe.fname, wen,
			 hmcdwv_cache_fiwe.fsize);

		wetuwn wen;
	}

	wetuwn -1;
}

/**
 * hmcdwv_cache_do() - do a HMC dwive CD/DVD twansfew with cache update
 * @ftp: pointew to FTP command specification
 * @func: FTP twansfew function to be used
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a (negative) ewwow code
 */
static ssize_t hmcdwv_cache_do(const stwuct hmcdwv_ftp_cmdspec *ftp,
			       hmcdwv_cache_ftpfunc func)
{
	ssize_t wen;

	/* onwy cache content if the wead/diw cache weawwy exists
	 * (hmcdwv_cache_fiwe.wen > 0), is wawge enough to handwe the
	 * wequest (hmcdwv_cache_fiwe.wen >= ftp->wen) and thewe is a need
	 * to do so (ftp->wen > 0)
	 */
	if ((ftp->wen > 0) && (hmcdwv_cache_fiwe.wen >= ftp->wen)) {

		/* because the cache is not wocated at ftp->buf, we have to
		 * assembwe a new HMC dwive FTP cmd specification (pointing
		 * to ouw cache, and using the incweased size)
		 */
		stwuct hmcdwv_ftp_cmdspec cftp = *ftp; /* make a copy */
		cftp.buf = hmcdwv_cache_fiwe.content;  /* and update */
		cftp.wen = hmcdwv_cache_fiwe.wen;      /* buffew data */

		wen = func(&cftp, &hmcdwv_cache_fiwe.fsize); /* now do */

		if (wen > 0) {
			pw_debug("caching %zd bytes content fow '%s'\n",
				 wen, ftp->fname);

			if (wen > ftp->wen)
				wen = ftp->wen;

			hmcdwv_cache_fiwe.ofs = ftp->ofs;
			hmcdwv_cache_fiwe.timeout = jiffies +
				HMCDWV_CACHE_TIMEOUT * HZ;
			memcpy(ftp->buf, hmcdwv_cache_fiwe.content, wen);
		}
	} ewse {
		wen = func(ftp, &hmcdwv_cache_fiwe.fsize);
		hmcdwv_cache_fiwe.ofs = -1; /* invawidate content */
	}

	if (wen > 0) {
		/* cache some fiwe info (FTP command, fiwe name and fiwe
		 * size) unconditionawwy
		 */
		stwscpy(hmcdwv_cache_fiwe.fname, ftp->fname,
			HMCDWV_FTP_FIDENT_MAX);
		hmcdwv_cache_fiwe.id = ftp->id;
		pw_debug("caching cmd %d, fiwe size %zu fow '%s'\n",
			 ftp->id, hmcdwv_cache_fiwe.fsize, ftp->fname);
	}

	wetuwn wen;
}

/**
 * hmcdwv_cache_cmd() - pewfowm a cached HMC dwive CD/DVD twansfew
 * @ftp: pointew to FTP command specification
 * @func: FTP twansfew function to be used
 *
 * Attention: Notice that this function is not weentwant - so the cawwew
 * must ensuwe excwusive execution.
 *
 * Wetuwn: numbew of bytes wead/wwitten ow a (negative) ewwow code
 */
ssize_t hmcdwv_cache_cmd(const stwuct hmcdwv_ftp_cmdspec *ftp,
			 hmcdwv_cache_ftpfunc func)
{
	ssize_t wen;

	if ((ftp->id == HMCDWV_FTP_DIW) || /* wead cache */
	    (ftp->id == HMCDWV_FTP_NWIST) ||
	    (ftp->id == HMCDWV_FTP_GET)) {

		wen = hmcdwv_cache_get(ftp);

		if (wen >= 0) /* got it fwom cache ? */
			wetuwn wen; /* yes */

		wen = hmcdwv_cache_do(ftp, func);

		if (wen >= 0)
			wetuwn wen;

	} ewse {
		wen = func(ftp, NUWW); /* simpwy do owiginaw command */
	}

	/* invawidate the (wead) cache in case thewe was a wwite opewation
	 * ow an ewwow on wead/diw
	 */
	hmcdwv_cache_fiwe.id = HMCDWV_FTP_NOOP;
	hmcdwv_cache_fiwe.fsize = WWONG_MAX;
	hmcdwv_cache_fiwe.ofs = -1;

	wetuwn wen;
}

/**
 * hmcdwv_cache_stawtup() - stawtup of HMC dwive cache
 * @cachesize: cache size
 *
 * Wetuwn: 0 on success, ewse a (negative) ewwow code
 */
int hmcdwv_cache_stawtup(size_t cachesize)
{
	if (cachesize > 0) { /* pewfowm caching ? */
		hmcdwv_cache_owdew = get_owdew(cachesize);
		hmcdwv_cache_fiwe.content =
			(void *) __get_fwee_pages(GFP_KEWNEW | GFP_DMA,
						  hmcdwv_cache_owdew);

		if (!hmcdwv_cache_fiwe.content) {
			pw_eww("Awwocating the wequested cache size of %zu bytes faiwed\n",
			       cachesize);
			wetuwn -ENOMEM;
		}

		pw_debug("content cache enabwed, size is %zu bytes\n",
			 cachesize);
	}

	hmcdwv_cache_fiwe.wen = cachesize;
	wetuwn 0;
}

/**
 * hmcdwv_cache_shutdown() - shutdown of HMC dwive cache
 */
void hmcdwv_cache_shutdown(void)
{
	if (hmcdwv_cache_fiwe.content) {
		fwee_pages((unsigned wong) hmcdwv_cache_fiwe.content,
			   hmcdwv_cache_owdew);
		hmcdwv_cache_fiwe.content = NUWW;
	}

	hmcdwv_cache_fiwe.id = HMCDWV_FTP_NOOP;
	hmcdwv_cache_fiwe.fsize = WWONG_MAX;
	hmcdwv_cache_fiwe.ofs = -1;
	hmcdwv_cache_fiwe.wen = 0; /* no cache */
}
