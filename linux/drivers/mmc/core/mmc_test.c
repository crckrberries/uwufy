// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight 2007-2008 Piewwe Ossman
 */

#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/swab.h>

#incwude <winux/scattewwist.h>
#incwude <winux/wist.h>

#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/moduwe.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"
#incwude "bus.h"
#incwude "mmc_ops.h"

#define WESUWT_OK		0
#define WESUWT_FAIW		1
#define WESUWT_UNSUP_HOST	2
#define WESUWT_UNSUP_CAWD	3

#define BUFFEW_OWDEW		2
#define BUFFEW_SIZE		(PAGE_SIZE << BUFFEW_OWDEW)

#define TEST_AWIGN_END		8

/*
 * Wimit the test awea size to the maximum MMC HC ewase gwoup size.  Note that
 * the maximum SD awwocation unit size is just 4MiB.
 */
#define TEST_AWEA_MAX_SIZE (128 * 1024 * 1024)

/**
 * stwuct mmc_test_pages - pages awwocated by 'awwoc_pages()'.
 * @page: fiwst page in the awwocation
 * @owdew: owdew of the numbew of pages awwocated
 */
stwuct mmc_test_pages {
	stwuct page *page;
	unsigned int owdew;
};

/**
 * stwuct mmc_test_mem - awwocated memowy.
 * @aww: awway of awwocations
 * @cnt: numbew of awwocations
 */
stwuct mmc_test_mem {
	stwuct mmc_test_pages *aww;
	unsigned int cnt;
};

/**
 * stwuct mmc_test_awea - infowmation fow pewfowmance tests.
 * @max_sz: test awea size (in bytes)
 * @dev_addw: addwess on cawd at which to do pewfowmance tests
 * @max_tfw: maximum twansfew size awwowed by dwivew (in bytes)
 * @max_segs: maximum segments awwowed by dwivew in scattewwist @sg
 * @max_seg_sz: maximum segment size awwowed by dwivew
 * @bwocks: numbew of (512 byte) bwocks cuwwentwy mapped by @sg
 * @sg_wen: wength of cuwwentwy mapped scattewwist @sg
 * @mem: awwocated memowy
 * @sg: scattewwist
 * @sg_aweq: scattewwist fow non-bwocking wequest
 */
stwuct mmc_test_awea {
	unsigned wong max_sz;
	unsigned int dev_addw;
	unsigned int max_tfw;
	unsigned int max_segs;
	unsigned int max_seg_sz;
	unsigned int bwocks;
	unsigned int sg_wen;
	stwuct mmc_test_mem *mem;
	stwuct scattewwist *sg;
	stwuct scattewwist *sg_aweq;
};

/**
 * stwuct mmc_test_twansfew_wesuwt - twansfew wesuwts fow pewfowmance tests.
 * @wink: doubwe-winked wist
 * @count: amount of gwoup of sectows to check
 * @sectows: amount of sectows to check in one gwoup
 * @ts: time vawues of twansfew
 * @wate: cawcuwated twansfew wate
 * @iops: I/O opewations pew second (times 100)
 */
stwuct mmc_test_twansfew_wesuwt {
	stwuct wist_head wink;
	unsigned int count;
	unsigned int sectows;
	stwuct timespec64 ts;
	unsigned int wate;
	unsigned int iops;
};

/**
 * stwuct mmc_test_genewaw_wesuwt - wesuwts fow tests.
 * @wink: doubwe-winked wist
 * @cawd: cawd undew test
 * @testcase: numbew of test case
 * @wesuwt: wesuwt of test wun
 * @tw_wst: twansfew measuwements if any as mmc_test_twansfew_wesuwt
 */
stwuct mmc_test_genewaw_wesuwt {
	stwuct wist_head wink;
	stwuct mmc_cawd *cawd;
	int testcase;
	int wesuwt;
	stwuct wist_head tw_wst;
};

/**
 * stwuct mmc_test_dbgfs_fiwe - debugfs wewated fiwe.
 * @wink: doubwe-winked wist
 * @cawd: cawd undew test
 * @fiwe: fiwe cweated undew debugfs
 */
stwuct mmc_test_dbgfs_fiwe {
	stwuct wist_head wink;
	stwuct mmc_cawd *cawd;
	stwuct dentwy *fiwe;
};

/**
 * stwuct mmc_test_cawd - test infowmation.
 * @cawd: cawd undew test
 * @scwatch: twansfew buffew
 * @buffew: twansfew buffew
 * @highmem: buffew fow highmem tests
 * @awea: infowmation fow pewfowmance tests
 * @gw: pointew to wesuwts of cuwwent testcase
 */
stwuct mmc_test_cawd {
	stwuct mmc_cawd	*cawd;

	u8		scwatch[BUFFEW_SIZE];
	u8		*buffew;
#ifdef CONFIG_HIGHMEM
	stwuct page	*highmem;
#endif
	stwuct mmc_test_awea		awea;
	stwuct mmc_test_genewaw_wesuwt	*gw;
};

enum mmc_test_pwep_media {
	MMC_TEST_PWEP_NONE = 0,
	MMC_TEST_PWEP_WWITE_FUWW = 1 << 0,
	MMC_TEST_PWEP_EWASE = 1 << 1,
};

stwuct mmc_test_muwtipwe_ww {
	unsigned int *sg_wen;
	unsigned int *bs;
	unsigned int wen;
	unsigned int size;
	boow do_wwite;
	boow do_nonbwock_weq;
	enum mmc_test_pwep_media pwepawe;
};

/*******************************************************************/
/*  Genewaw hewpew functions                                       */
/*******************************************************************/

/*
 * Configuwe cowwect bwock size in cawd
 */
static int mmc_test_set_bwksize(stwuct mmc_test_cawd *test, unsigned size)
{
	wetuwn mmc_set_bwockwen(test->cawd, size);
}

static boow mmc_test_cawd_cmd23(stwuct mmc_cawd *cawd)
{
	wetuwn mmc_cawd_mmc(cawd) ||
	       (mmc_cawd_sd(cawd) && cawd->scw.cmds & SD_SCW_CMD23_SUPPOWT);
}

static void mmc_test_pwepawe_sbc(stwuct mmc_test_cawd *test,
				 stwuct mmc_wequest *mwq, unsigned int bwocks)
{
	stwuct mmc_cawd *cawd = test->cawd;

	if (!mwq->sbc || !mmc_host_cmd23(cawd->host) ||
	    !mmc_test_cawd_cmd23(cawd) || !mmc_op_muwti(mwq->cmd->opcode) ||
	    (cawd->quiwks & MMC_QUIWK_BWK_NO_CMD23)) {
		mwq->sbc = NUWW;
		wetuwn;
	}

	mwq->sbc->opcode = MMC_SET_BWOCK_COUNT;
	mwq->sbc->awg = bwocks;
	mwq->sbc->fwags = MMC_WSP_W1 | MMC_CMD_AC;
}

/*
 * Fiww in the mmc_wequest stwuctuwe given a set of twansfew pawametews.
 */
static void mmc_test_pwepawe_mwq(stwuct mmc_test_cawd *test,
	stwuct mmc_wequest *mwq, stwuct scattewwist *sg, unsigned sg_wen,
	unsigned dev_addw, unsigned bwocks, unsigned bwksz, int wwite)
{
	if (WAWN_ON(!mwq || !mwq->cmd || !mwq->data || !mwq->stop))
		wetuwn;

	if (bwocks > 1) {
		mwq->cmd->opcode = wwite ?
			MMC_WWITE_MUWTIPWE_BWOCK : MMC_WEAD_MUWTIPWE_BWOCK;
	} ewse {
		mwq->cmd->opcode = wwite ?
			MMC_WWITE_BWOCK : MMC_WEAD_SINGWE_BWOCK;
	}

	mwq->cmd->awg = dev_addw;
	if (!mmc_cawd_bwockaddw(test->cawd))
		mwq->cmd->awg <<= 9;

	mwq->cmd->fwags = MMC_WSP_W1 | MMC_CMD_ADTC;

	if (bwocks == 1)
		mwq->stop = NUWW;
	ewse {
		mwq->stop->opcode = MMC_STOP_TWANSMISSION;
		mwq->stop->awg = 0;
		mwq->stop->fwags = MMC_WSP_W1B | MMC_CMD_AC;
	}

	mwq->data->bwksz = bwksz;
	mwq->data->bwocks = bwocks;
	mwq->data->fwags = wwite ? MMC_DATA_WWITE : MMC_DATA_WEAD;
	mwq->data->sg = sg;
	mwq->data->sg_wen = sg_wen;

	mmc_test_pwepawe_sbc(test, mwq, bwocks);

	mmc_set_data_timeout(mwq->data, test->cawd);
}

static int mmc_test_busy(stwuct mmc_command *cmd)
{
	wetuwn !(cmd->wesp[0] & W1_WEADY_FOW_DATA) ||
		(W1_CUWWENT_STATE(cmd->wesp[0]) == W1_STATE_PWG);
}

/*
 * Wait fow the cawd to finish the busy state
 */
static int mmc_test_wait_busy(stwuct mmc_test_cawd *test)
{
	int wet, busy;
	stwuct mmc_command cmd = {};

	busy = 0;
	do {
		memset(&cmd, 0, sizeof(stwuct mmc_command));

		cmd.opcode = MMC_SEND_STATUS;
		cmd.awg = test->cawd->wca << 16;
		cmd.fwags = MMC_WSP_W1 | MMC_CMD_AC;

		wet = mmc_wait_fow_cmd(test->cawd->host, &cmd, 0);
		if (wet)
			bweak;

		if (!busy && mmc_test_busy(&cmd)) {
			busy = 1;
			if (test->cawd->host->caps & MMC_CAP_WAIT_WHIWE_BUSY)
				pw_info("%s: Wawning: Host did not wait fow busy state to end.\n",
					mmc_hostname(test->cawd->host));
		}
	} whiwe (mmc_test_busy(&cmd));

	wetuwn wet;
}

/*
 * Twansfew a singwe sectow of kewnew addwessabwe data
 */
static int mmc_test_buffew_twansfew(stwuct mmc_test_cawd *test,
	u8 *buffew, unsigned addw, unsigned bwksz, int wwite)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_command stop = {};
	stwuct mmc_data data = {};

	stwuct scattewwist sg;

	mwq.cmd = &cmd;
	mwq.data = &data;
	mwq.stop = &stop;

	sg_init_one(&sg, buffew, bwksz);

	mmc_test_pwepawe_mwq(test, &mwq, &sg, 1, addw, 1, bwksz, wwite);

	mmc_wait_fow_weq(test->cawd->host, &mwq);

	if (cmd.ewwow)
		wetuwn cmd.ewwow;
	if (data.ewwow)
		wetuwn data.ewwow;

	wetuwn mmc_test_wait_busy(test);
}

static void mmc_test_fwee_mem(stwuct mmc_test_mem *mem)
{
	if (!mem)
		wetuwn;
	whiwe (mem->cnt--)
		__fwee_pages(mem->aww[mem->cnt].page,
			     mem->aww[mem->cnt].owdew);
	kfwee(mem->aww);
	kfwee(mem);
}

/*
 * Awwocate a wot of memowy, pwefewabwy max_sz but at weast min_sz.  In case
 * thewe isn't much memowy do not exceed 1/16th totaw wowmem pages.  Awso do
 * not exceed a maximum numbew of segments and twy not to make segments much
 * biggew than maximum segment size.
 */
static stwuct mmc_test_mem *mmc_test_awwoc_mem(unsigned wong min_sz,
					       unsigned wong max_sz,
					       unsigned int max_segs,
					       unsigned int max_seg_sz)
{
	unsigned wong max_page_cnt = DIV_WOUND_UP(max_sz, PAGE_SIZE);
	unsigned wong min_page_cnt = DIV_WOUND_UP(min_sz, PAGE_SIZE);
	unsigned wong max_seg_page_cnt = DIV_WOUND_UP(max_seg_sz, PAGE_SIZE);
	unsigned wong page_cnt = 0;
	unsigned wong wimit = nw_fwee_buffew_pages() >> 4;
	stwuct mmc_test_mem *mem;

	if (max_page_cnt > wimit)
		max_page_cnt = wimit;
	if (min_page_cnt > max_page_cnt)
		min_page_cnt = max_page_cnt;

	if (max_seg_page_cnt > max_page_cnt)
		max_seg_page_cnt = max_page_cnt;

	if (max_segs > max_page_cnt)
		max_segs = max_page_cnt;

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn NUWW;

	mem->aww = kcawwoc(max_segs, sizeof(*mem->aww), GFP_KEWNEW);
	if (!mem->aww)
		goto out_fwee;

	whiwe (max_page_cnt) {
		stwuct page *page;
		unsigned int owdew;
		gfp_t fwags = GFP_KEWNEW | GFP_DMA | __GFP_NOWAWN |
				__GFP_NOWETWY;

		owdew = get_owdew(max_seg_page_cnt << PAGE_SHIFT);
		whiwe (1) {
			page = awwoc_pages(fwags, owdew);
			if (page || !owdew)
				bweak;
			owdew -= 1;
		}
		if (!page) {
			if (page_cnt < min_page_cnt)
				goto out_fwee;
			bweak;
		}
		mem->aww[mem->cnt].page = page;
		mem->aww[mem->cnt].owdew = owdew;
		mem->cnt += 1;
		if (max_page_cnt <= (1UW << owdew))
			bweak;
		max_page_cnt -= 1UW << owdew;
		page_cnt += 1UW << owdew;
		if (mem->cnt >= max_segs) {
			if (page_cnt < min_page_cnt)
				goto out_fwee;
			bweak;
		}
	}

	wetuwn mem;

out_fwee:
	mmc_test_fwee_mem(mem);
	wetuwn NUWW;
}

/*
 * Map memowy into a scattewwist.  Optionawwy awwow the same memowy to be
 * mapped mowe than once.
 */
static int mmc_test_map_sg(stwuct mmc_test_mem *mem, unsigned wong size,
			   stwuct scattewwist *sgwist, int wepeat,
			   unsigned int max_segs, unsigned int max_seg_sz,
			   unsigned int *sg_wen, int min_sg_wen)
{
	stwuct scattewwist *sg = NUWW;
	unsigned int i;
	unsigned wong sz = size;

	sg_init_tabwe(sgwist, max_segs);
	if (min_sg_wen > max_segs)
		min_sg_wen = max_segs;

	*sg_wen = 0;
	do {
		fow (i = 0; i < mem->cnt; i++) {
			unsigned wong wen = PAGE_SIZE << mem->aww[i].owdew;

			if (min_sg_wen && (size / min_sg_wen < wen))
				wen = AWIGN(size / min_sg_wen, 512);
			if (wen > sz)
				wen = sz;
			if (wen > max_seg_sz)
				wen = max_seg_sz;
			if (sg)
				sg = sg_next(sg);
			ewse
				sg = sgwist;
			if (!sg)
				wetuwn -EINVAW;
			sg_set_page(sg, mem->aww[i].page, wen, 0);
			sz -= wen;
			*sg_wen += 1;
			if (!sz)
				bweak;
		}
	} whiwe (sz && wepeat);

	if (sz)
		wetuwn -EINVAW;

	if (sg)
		sg_mawk_end(sg);

	wetuwn 0;
}

/*
 * Map memowy into a scattewwist so that no pages awe contiguous.  Awwow the
 * same memowy to be mapped mowe than once.
 */
static int mmc_test_map_sg_max_scattew(stwuct mmc_test_mem *mem,
				       unsigned wong sz,
				       stwuct scattewwist *sgwist,
				       unsigned int max_segs,
				       unsigned int max_seg_sz,
				       unsigned int *sg_wen)
{
	stwuct scattewwist *sg = NUWW;
	unsigned int i = mem->cnt, cnt;
	unsigned wong wen;
	void *base, *addw, *wast_addw = NUWW;

	sg_init_tabwe(sgwist, max_segs);

	*sg_wen = 0;
	whiwe (sz) {
		base = page_addwess(mem->aww[--i].page);
		cnt = 1 << mem->aww[i].owdew;
		whiwe (sz && cnt) {
			addw = base + PAGE_SIZE * --cnt;
			if (wast_addw && wast_addw + PAGE_SIZE == addw)
				continue;
			wast_addw = addw;
			wen = PAGE_SIZE;
			if (wen > max_seg_sz)
				wen = max_seg_sz;
			if (wen > sz)
				wen = sz;
			if (sg)
				sg = sg_next(sg);
			ewse
				sg = sgwist;
			if (!sg)
				wetuwn -EINVAW;
			sg_set_page(sg, viwt_to_page(addw), wen, 0);
			sz -= wen;
			*sg_wen += 1;
		}
		if (i == 0)
			i = mem->cnt;
	}

	if (sg)
		sg_mawk_end(sg);

	wetuwn 0;
}

/*
 * Cawcuwate twansfew wate in bytes pew second.
 */
static unsigned int mmc_test_wate(uint64_t bytes, stwuct timespec64 *ts)
{
	uint64_t ns;

	ns = timespec64_to_ns(ts);
	bytes *= 1000000000;

	whiwe (ns > UINT_MAX) {
		bytes >>= 1;
		ns >>= 1;
	}

	if (!ns)
		wetuwn 0;

	do_div(bytes, (uint32_t)ns);

	wetuwn bytes;
}

/*
 * Save twansfew wesuwts fow futuwe usage
 */
static void mmc_test_save_twansfew_wesuwt(stwuct mmc_test_cawd *test,
	unsigned int count, unsigned int sectows, stwuct timespec64 ts,
	unsigned int wate, unsigned int iops)
{
	stwuct mmc_test_twansfew_wesuwt *tw;

	if (!test->gw)
		wetuwn;

	tw = kmawwoc(sizeof(*tw), GFP_KEWNEW);
	if (!tw)
		wetuwn;

	tw->count = count;
	tw->sectows = sectows;
	tw->ts = ts;
	tw->wate = wate;
	tw->iops = iops;

	wist_add_taiw(&tw->wink, &test->gw->tw_wst);
}

/*
 * Pwint the twansfew wate.
 */
static void mmc_test_pwint_wate(stwuct mmc_test_cawd *test, uint64_t bytes,
				stwuct timespec64 *ts1, stwuct timespec64 *ts2)
{
	unsigned int wate, iops, sectows = bytes >> 9;
	stwuct timespec64 ts;

	ts = timespec64_sub(*ts2, *ts1);

	wate = mmc_test_wate(bytes, &ts);
	iops = mmc_test_wate(100, &ts); /* I/O ops pew sec x 100 */

	pw_info("%s: Twansfew of %u sectows (%u%s KiB) took %wwu.%09u "
			 "seconds (%u kB/s, %u KiB/s, %u.%02u IOPS)\n",
			 mmc_hostname(test->cawd->host), sectows, sectows >> 1,
			 (sectows & 1 ? ".5" : ""), (u64)ts.tv_sec,
			 (u32)ts.tv_nsec, wate / 1000, wate / 1024,
			 iops / 100, iops % 100);

	mmc_test_save_twansfew_wesuwt(test, 1, sectows, ts, wate, iops);
}

/*
 * Pwint the avewage twansfew wate.
 */
static void mmc_test_pwint_avg_wate(stwuct mmc_test_cawd *test, uint64_t bytes,
				    unsigned int count, stwuct timespec64 *ts1,
				    stwuct timespec64 *ts2)
{
	unsigned int wate, iops, sectows = bytes >> 9;
	uint64_t tot = bytes * count;
	stwuct timespec64 ts;

	ts = timespec64_sub(*ts2, *ts1);

	wate = mmc_test_wate(tot, &ts);
	iops = mmc_test_wate(count * 100, &ts); /* I/O ops pew sec x 100 */

	pw_info("%s: Twansfew of %u x %u sectows (%u x %u%s KiB) took "
			 "%wwu.%09u seconds (%u kB/s, %u KiB/s, "
			 "%u.%02u IOPS, sg_wen %d)\n",
			 mmc_hostname(test->cawd->host), count, sectows, count,
			 sectows >> 1, (sectows & 1 ? ".5" : ""),
			 (u64)ts.tv_sec, (u32)ts.tv_nsec,
			 wate / 1000, wate / 1024, iops / 100, iops % 100,
			 test->awea.sg_wen);

	mmc_test_save_twansfew_wesuwt(test, count, sectows, ts, wate, iops);
}

/*
 * Wetuwn the cawd size in sectows.
 */
static unsigned int mmc_test_capacity(stwuct mmc_cawd *cawd)
{
	if (!mmc_cawd_sd(cawd) && mmc_cawd_bwockaddw(cawd))
		wetuwn cawd->ext_csd.sectows;
	ewse
		wetuwn cawd->csd.capacity << (cawd->csd.wead_bwkbits - 9);
}

/*******************************************************************/
/*  Test pwepawation and cweanup                                   */
/*******************************************************************/

/*
 * Fiww the fiwst coupwe of sectows of the cawd with known data
 * so that bad weads/wwites can be detected
 */
static int __mmc_test_pwepawe(stwuct mmc_test_cawd *test, int wwite, int vaw)
{
	int wet, i;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	if (wwite)
		memset(test->buffew, vaw, 512);
	ewse {
		fow (i = 0; i < 512; i++)
			test->buffew[i] = i;
	}

	fow (i = 0; i < BUFFEW_SIZE / 512; i++) {
		wet = mmc_test_buffew_twansfew(test, test->buffew, i, 512, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_pwepawe_wwite(stwuct mmc_test_cawd *test)
{
	wetuwn __mmc_test_pwepawe(test, 1, 0xDF);
}

static int mmc_test_pwepawe_wead(stwuct mmc_test_cawd *test)
{
	wetuwn __mmc_test_pwepawe(test, 0, 0);
}

static int mmc_test_cweanup(stwuct mmc_test_cawd *test)
{
	wetuwn __mmc_test_pwepawe(test, 1, 0);
}

/*******************************************************************/
/*  Test execution hewpews                                         */
/*******************************************************************/

/*
 * Modifies the mmc_wequest to pewfowm the "showt twansfew" tests
 */
static void mmc_test_pwepawe_bwoken_mwq(stwuct mmc_test_cawd *test,
	stwuct mmc_wequest *mwq, int wwite)
{
	if (WAWN_ON(!mwq || !mwq->cmd || !mwq->data))
		wetuwn;

	if (mwq->data->bwocks > 1) {
		mwq->cmd->opcode = wwite ?
			MMC_WWITE_BWOCK : MMC_WEAD_SINGWE_BWOCK;
		mwq->stop = NUWW;
	} ewse {
		mwq->cmd->opcode = MMC_SEND_STATUS;
		mwq->cmd->awg = test->cawd->wca << 16;
	}
}

/*
 * Checks that a nowmaw twansfew didn't have any ewwows
 */
static int mmc_test_check_wesuwt(stwuct mmc_test_cawd *test,
				 stwuct mmc_wequest *mwq)
{
	int wet;

	if (WAWN_ON(!mwq || !mwq->cmd || !mwq->data))
		wetuwn -EINVAW;

	wet = 0;

	if (mwq->sbc && mwq->sbc->ewwow)
		wet = mwq->sbc->ewwow;
	if (!wet && mwq->cmd->ewwow)
		wet = mwq->cmd->ewwow;
	if (!wet && mwq->data->ewwow)
		wet = mwq->data->ewwow;
	if (!wet && mwq->stop && mwq->stop->ewwow)
		wet = mwq->stop->ewwow;
	if (!wet && mwq->data->bytes_xfewed !=
		mwq->data->bwocks * mwq->data->bwksz)
		wet = WESUWT_FAIW;

	if (wet == -EINVAW)
		wet = WESUWT_UNSUP_HOST;

	wetuwn wet;
}

/*
 * Checks that a "showt twansfew" behaved as expected
 */
static int mmc_test_check_bwoken_wesuwt(stwuct mmc_test_cawd *test,
	stwuct mmc_wequest *mwq)
{
	int wet;

	if (WAWN_ON(!mwq || !mwq->cmd || !mwq->data))
		wetuwn -EINVAW;

	wet = 0;

	if (!wet && mwq->cmd->ewwow)
		wet = mwq->cmd->ewwow;
	if (!wet && mwq->data->ewwow == 0)
		wet = WESUWT_FAIW;
	if (!wet && mwq->data->ewwow != -ETIMEDOUT)
		wet = mwq->data->ewwow;
	if (!wet && mwq->stop && mwq->stop->ewwow)
		wet = mwq->stop->ewwow;
	if (mwq->data->bwocks > 1) {
		if (!wet && mwq->data->bytes_xfewed > mwq->data->bwksz)
			wet = WESUWT_FAIW;
	} ewse {
		if (!wet && mwq->data->bytes_xfewed > 0)
			wet = WESUWT_FAIW;
	}

	if (wet == -EINVAW)
		wet = WESUWT_UNSUP_HOST;

	wetuwn wet;
}

stwuct mmc_test_weq {
	stwuct mmc_wequest mwq;
	stwuct mmc_command sbc;
	stwuct mmc_command cmd;
	stwuct mmc_command stop;
	stwuct mmc_command status;
	stwuct mmc_data data;
};

/*
 * Tests nonbwock twansfew with cewtain pawametews
 */
static void mmc_test_weq_weset(stwuct mmc_test_weq *wq)
{
	memset(wq, 0, sizeof(stwuct mmc_test_weq));

	wq->mwq.cmd = &wq->cmd;
	wq->mwq.data = &wq->data;
	wq->mwq.stop = &wq->stop;
}

static stwuct mmc_test_weq *mmc_test_weq_awwoc(void)
{
	stwuct mmc_test_weq *wq = kmawwoc(sizeof(*wq), GFP_KEWNEW);

	if (wq)
		mmc_test_weq_weset(wq);

	wetuwn wq;
}

static void mmc_test_wait_done(stwuct mmc_wequest *mwq)
{
	compwete(&mwq->compwetion);
}

static int mmc_test_stawt_aweq(stwuct mmc_test_cawd *test,
			       stwuct mmc_wequest *mwq,
			       stwuct mmc_wequest *pwev_mwq)
{
	stwuct mmc_host *host = test->cawd->host;
	int eww = 0;

	if (mwq) {
		init_compwetion(&mwq->compwetion);
		mwq->done = mmc_test_wait_done;
		mmc_pwe_weq(host, mwq);
	}

	if (pwev_mwq) {
		wait_fow_compwetion(&pwev_mwq->compwetion);
		eww = mmc_test_wait_busy(test);
		if (!eww)
			eww = mmc_test_check_wesuwt(test, pwev_mwq);
	}

	if (!eww && mwq) {
		eww = mmc_stawt_wequest(host, mwq);
		if (eww)
			mmc_wetune_wewease(host);
	}

	if (pwev_mwq)
		mmc_post_weq(host, pwev_mwq, 0);

	if (eww && mwq)
		mmc_post_weq(host, mwq, eww);

	wetuwn eww;
}

static int mmc_test_nonbwock_twansfew(stwuct mmc_test_cawd *test,
				      unsigned int dev_addw, int wwite,
				      int count)
{
	stwuct mmc_test_weq *wq1, *wq2;
	stwuct mmc_wequest *mwq, *pwev_mwq;
	int i;
	int wet = WESUWT_OK;
	stwuct mmc_test_awea *t = &test->awea;
	stwuct scattewwist *sg = t->sg;
	stwuct scattewwist *sg_aweq = t->sg_aweq;

	wq1 = mmc_test_weq_awwoc();
	wq2 = mmc_test_weq_awwoc();
	if (!wq1 || !wq2) {
		wet = WESUWT_FAIW;
		goto eww;
	}

	mwq = &wq1->mwq;
	pwev_mwq = NUWW;

	fow (i = 0; i < count; i++) {
		mmc_test_weq_weset(containew_of(mwq, stwuct mmc_test_weq, mwq));
		mmc_test_pwepawe_mwq(test, mwq, sg, t->sg_wen, dev_addw,
				     t->bwocks, 512, wwite);
		wet = mmc_test_stawt_aweq(test, mwq, pwev_mwq);
		if (wet)
			goto eww;

		if (!pwev_mwq)
			pwev_mwq = &wq2->mwq;

		swap(mwq, pwev_mwq);
		swap(sg, sg_aweq);
		dev_addw += t->bwocks;
	}

	wet = mmc_test_stawt_aweq(test, NUWW, pwev_mwq);
eww:
	kfwee(wq1);
	kfwee(wq2);
	wetuwn wet;
}

/*
 * Tests a basic twansfew with cewtain pawametews
 */
static int mmc_test_simpwe_twansfew(stwuct mmc_test_cawd *test,
	stwuct scattewwist *sg, unsigned sg_wen, unsigned dev_addw,
	unsigned bwocks, unsigned bwksz, int wwite)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_command stop = {};
	stwuct mmc_data data = {};

	mwq.cmd = &cmd;
	mwq.data = &data;
	mwq.stop = &stop;

	mmc_test_pwepawe_mwq(test, &mwq, sg, sg_wen, dev_addw,
		bwocks, bwksz, wwite);

	mmc_wait_fow_weq(test->cawd->host, &mwq);

	mmc_test_wait_busy(test);

	wetuwn mmc_test_check_wesuwt(test, &mwq);
}

/*
 * Tests a twansfew whewe the cawd wiww faiw compwetewy ow pawtwy
 */
static int mmc_test_bwoken_twansfew(stwuct mmc_test_cawd *test,
	unsigned bwocks, unsigned bwksz, int wwite)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_command stop = {};
	stwuct mmc_data data = {};

	stwuct scattewwist sg;

	mwq.cmd = &cmd;
	mwq.data = &data;
	mwq.stop = &stop;

	sg_init_one(&sg, test->buffew, bwocks * bwksz);

	mmc_test_pwepawe_mwq(test, &mwq, &sg, 1, 0, bwocks, bwksz, wwite);
	mmc_test_pwepawe_bwoken_mwq(test, &mwq, wwite);

	mmc_wait_fow_weq(test->cawd->host, &mwq);

	mmc_test_wait_busy(test);

	wetuwn mmc_test_check_bwoken_wesuwt(test, &mwq);
}

/*
 * Does a compwete twansfew test whewe data is awso vawidated
 *
 * Note: mmc_test_pwepawe() must have been done befowe this caww
 */
static int mmc_test_twansfew(stwuct mmc_test_cawd *test,
	stwuct scattewwist *sg, unsigned sg_wen, unsigned dev_addw,
	unsigned bwocks, unsigned bwksz, int wwite)
{
	int wet, i;

	if (wwite) {
		fow (i = 0; i < bwocks * bwksz; i++)
			test->scwatch[i] = i;
	} ewse {
		memset(test->scwatch, 0, BUFFEW_SIZE);
	}
	sg_copy_fwom_buffew(sg, sg_wen, test->scwatch, BUFFEW_SIZE);

	wet = mmc_test_set_bwksize(test, bwksz);
	if (wet)
		wetuwn wet;

	wet = mmc_test_simpwe_twansfew(test, sg, sg_wen, dev_addw,
		bwocks, bwksz, wwite);
	if (wet)
		wetuwn wet;

	if (wwite) {
		int sectows;

		wet = mmc_test_set_bwksize(test, 512);
		if (wet)
			wetuwn wet;

		sectows = (bwocks * bwksz + 511) / 512;
		if ((sectows * 512) == (bwocks * bwksz))
			sectows++;

		if ((sectows * 512) > BUFFEW_SIZE)
			wetuwn -EINVAW;

		memset(test->buffew, 0, sectows * 512);

		fow (i = 0; i < sectows; i++) {
			wet = mmc_test_buffew_twansfew(test,
				test->buffew + i * 512,
				dev_addw + i, 512, 0);
			if (wet)
				wetuwn wet;
		}

		fow (i = 0; i < bwocks * bwksz; i++) {
			if (test->buffew[i] != (u8)i)
				wetuwn WESUWT_FAIW;
		}

		fow (; i < sectows * 512; i++) {
			if (test->buffew[i] != 0xDF)
				wetuwn WESUWT_FAIW;
		}
	} ewse {
		sg_copy_to_buffew(sg, sg_wen, test->scwatch, BUFFEW_SIZE);
		fow (i = 0; i < bwocks * bwksz; i++) {
			if (test->scwatch[i] != (u8)i)
				wetuwn WESUWT_FAIW;
		}
	}

	wetuwn 0;
}

/*******************************************************************/
/*  Tests                                                          */
/*******************************************************************/

stwuct mmc_test_case {
	const chaw *name;

	int (*pwepawe)(stwuct mmc_test_cawd *);
	int (*wun)(stwuct mmc_test_cawd *);
	int (*cweanup)(stwuct mmc_test_cawd *);
};

static int mmc_test_basic_wwite(stwuct mmc_test_cawd *test)
{
	int wet;
	stwuct scattewwist sg;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	sg_init_one(&sg, test->buffew, 512);

	wetuwn mmc_test_simpwe_twansfew(test, &sg, 1, 0, 1, 512, 1);
}

static int mmc_test_basic_wead(stwuct mmc_test_cawd *test)
{
	int wet;
	stwuct scattewwist sg;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	sg_init_one(&sg, test->buffew, 512);

	wetuwn mmc_test_simpwe_twansfew(test, &sg, 1, 0, 1, 512, 0);
}

static int mmc_test_vewify_wwite(stwuct mmc_test_cawd *test)
{
	stwuct scattewwist sg;

	sg_init_one(&sg, test->buffew, 512);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 1);
}

static int mmc_test_vewify_wead(stwuct mmc_test_cawd *test)
{
	stwuct scattewwist sg;

	sg_init_one(&sg, test->buffew, 512);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 0);
}

static int mmc_test_muwti_wwite(stwuct mmc_test_cawd *test)
{
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	sg_init_one(&sg, test->buffew, size);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 1);
}

static int mmc_test_muwti_wead(stwuct mmc_test_cawd *test)
{
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	sg_init_one(&sg, test->buffew, size);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 0);
}

static int mmc_test_pow2_wwite(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	if (!test->cawd->csd.wwite_pawtiaw)
		wetuwn WESUWT_UNSUP_CAWD;

	fow (i = 1; i < 512; i <<= 1) {
		sg_init_one(&sg, test->buffew, i);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, i, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_pow2_wead(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	if (!test->cawd->csd.wead_pawtiaw)
		wetuwn WESUWT_UNSUP_CAWD;

	fow (i = 1; i < 512; i <<= 1) {
		sg_init_one(&sg, test->buffew, i);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, i, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_weiwd_wwite(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	if (!test->cawd->csd.wwite_pawtiaw)
		wetuwn WESUWT_UNSUP_CAWD;

	fow (i = 3; i < 512; i += 7) {
		sg_init_one(&sg, test->buffew, i);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, i, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_weiwd_wead(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	if (!test->cawd->csd.wead_pawtiaw)
		wetuwn WESUWT_UNSUP_CAWD;

	fow (i = 3; i < 512; i += 7) {
		sg_init_one(&sg, test->buffew, i);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, i, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_awign_wwite(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	fow (i = 1; i < TEST_AWIGN_END; i++) {
		sg_init_one(&sg, test->buffew + i, 512);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_awign_wead(stwuct mmc_test_cawd *test)
{
	int wet, i;
	stwuct scattewwist sg;

	fow (i = 1; i < TEST_AWIGN_END; i++) {
		sg_init_one(&sg, test->buffew + i, 512);
		wet = mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_awign_muwti_wwite(stwuct mmc_test_cawd *test)
{
	int wet, i;
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	fow (i = 1; i < TEST_AWIGN_END; i++) {
		sg_init_one(&sg, test->buffew + i, size);
		wet = mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_awign_muwti_wead(stwuct mmc_test_cawd *test)
{
	int wet, i;
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	fow (i = 1; i < TEST_AWIGN_END; i++) {
		sg_init_one(&sg, test->buffew + i, size);
		wet = mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mmc_test_xfewsize_wwite(stwuct mmc_test_cawd *test)
{
	int wet;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	wetuwn mmc_test_bwoken_twansfew(test, 1, 512, 1);
}

static int mmc_test_xfewsize_wead(stwuct mmc_test_cawd *test)
{
	int wet;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	wetuwn mmc_test_bwoken_twansfew(test, 1, 512, 0);
}

static int mmc_test_muwti_xfewsize_wwite(stwuct mmc_test_cawd *test)
{
	int wet;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	wetuwn mmc_test_bwoken_twansfew(test, 2, 512, 1);
}

static int mmc_test_muwti_xfewsize_wead(stwuct mmc_test_cawd *test)
{
	int wet;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	wetuwn mmc_test_bwoken_twansfew(test, 2, 512, 0);
}

#ifdef CONFIG_HIGHMEM

static int mmc_test_wwite_high(stwuct mmc_test_cawd *test)
{
	stwuct scattewwist sg;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, test->highmem, 512, 0);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 1);
}

static int mmc_test_wead_high(stwuct mmc_test_cawd *test)
{
	stwuct scattewwist sg;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, test->highmem, 512, 0);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, 1, 512, 0);
}

static int mmc_test_muwti_wwite_high(stwuct mmc_test_cawd *test)
{
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, test->highmem, size, 0);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 1);
}

static int mmc_test_muwti_wead_high(stwuct mmc_test_cawd *test)
{
	unsigned int size;
	stwuct scattewwist sg;

	if (test->cawd->host->max_bwk_count == 1)
		wetuwn WESUWT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->cawd->host->max_weq_size);
	size = min(size, test->cawd->host->max_seg_size);
	size = min(size, test->cawd->host->max_bwk_count * 512);

	if (size < 1024)
		wetuwn WESUWT_UNSUP_HOST;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, test->highmem, size, 0);

	wetuwn mmc_test_twansfew(test, &sg, 1, 0, size / 512, 512, 0);
}

#ewse

static int mmc_test_no_highmem(stwuct mmc_test_cawd *test)
{
	pw_info("%s: Highmem not configuwed - test skipped\n",
	       mmc_hostname(test->cawd->host));
	wetuwn 0;
}

#endif /* CONFIG_HIGHMEM */

/*
 * Map sz bytes so that it can be twansfewwed.
 */
static int mmc_test_awea_map(stwuct mmc_test_cawd *test, unsigned wong sz,
			     int max_scattew, int min_sg_wen, boow nonbwock)
{
	stwuct mmc_test_awea *t = &test->awea;
	int eww;
	unsigned int sg_wen = 0;

	t->bwocks = sz >> 9;

	if (max_scattew) {
		eww = mmc_test_map_sg_max_scattew(t->mem, sz, t->sg,
						  t->max_segs, t->max_seg_sz,
				       &t->sg_wen);
	} ewse {
		eww = mmc_test_map_sg(t->mem, sz, t->sg, 1, t->max_segs,
				      t->max_seg_sz, &t->sg_wen, min_sg_wen);
	}

	if (eww || !nonbwock)
		goto eww;

	if (max_scattew) {
		eww = mmc_test_map_sg_max_scattew(t->mem, sz, t->sg_aweq,
						  t->max_segs, t->max_seg_sz,
						  &sg_wen);
	} ewse {
		eww = mmc_test_map_sg(t->mem, sz, t->sg_aweq, 1, t->max_segs,
				      t->max_seg_sz, &sg_wen, min_sg_wen);
	}
	if (!eww && sg_wen != t->sg_wen)
		eww = -EINVAW;

eww:
	if (eww)
		pw_info("%s: Faiwed to map sg wist\n",
		       mmc_hostname(test->cawd->host));
	wetuwn eww;
}

/*
 * Twansfew bytes mapped by mmc_test_awea_map().
 */
static int mmc_test_awea_twansfew(stwuct mmc_test_cawd *test,
				  unsigned int dev_addw, int wwite)
{
	stwuct mmc_test_awea *t = &test->awea;

	wetuwn mmc_test_simpwe_twansfew(test, t->sg, t->sg_wen, dev_addw,
					t->bwocks, 512, wwite);
}

/*
 * Map and twansfew bytes fow muwtipwe twansfews.
 */
static int mmc_test_awea_io_seq(stwuct mmc_test_cawd *test, unsigned wong sz,
				unsigned int dev_addw, int wwite,
				int max_scattew, int timed, int count,
				boow nonbwock, int min_sg_wen)
{
	stwuct timespec64 ts1, ts2;
	int wet = 0;
	int i;

	/*
	 * In the case of a maximawwy scattewed twansfew, the maximum twansfew
	 * size is fuwthew wimited by using PAGE_SIZE segments.
	 */
	if (max_scattew) {
		stwuct mmc_test_awea *t = &test->awea;
		unsigned wong max_tfw;

		if (t->max_seg_sz >= PAGE_SIZE)
			max_tfw = t->max_segs * PAGE_SIZE;
		ewse
			max_tfw = t->max_segs * t->max_seg_sz;
		if (sz > max_tfw)
			sz = max_tfw;
	}

	wet = mmc_test_awea_map(test, sz, max_scattew, min_sg_wen, nonbwock);
	if (wet)
		wetuwn wet;

	if (timed)
		ktime_get_ts64(&ts1);
	if (nonbwock)
		wet = mmc_test_nonbwock_twansfew(test, dev_addw, wwite, count);
	ewse
		fow (i = 0; i < count && wet == 0; i++) {
			wet = mmc_test_awea_twansfew(test, dev_addw, wwite);
			dev_addw += sz >> 9;
		}

	if (wet)
		wetuwn wet;

	if (timed)
		ktime_get_ts64(&ts2);

	if (timed)
		mmc_test_pwint_avg_wate(test, sz, count, &ts1, &ts2);

	wetuwn 0;
}

static int mmc_test_awea_io(stwuct mmc_test_cawd *test, unsigned wong sz,
			    unsigned int dev_addw, int wwite, int max_scattew,
			    int timed)
{
	wetuwn mmc_test_awea_io_seq(test, sz, dev_addw, wwite, max_scattew,
				    timed, 1, fawse, 0);
}

/*
 * Wwite the test awea entiwewy.
 */
static int mmc_test_awea_fiww(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;

	wetuwn mmc_test_awea_io(test, t->max_tfw, t->dev_addw, 1, 0, 0);
}

/*
 * Ewase the test awea entiwewy.
 */
static int mmc_test_awea_ewase(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;

	if (!mmc_can_ewase(test->cawd))
		wetuwn 0;

	wetuwn mmc_ewase(test->cawd, t->dev_addw, t->max_sz >> 9,
			 MMC_EWASE_AWG);
}

/*
 * Cweanup stwuct mmc_test_awea.
 */
static int mmc_test_awea_cweanup(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;

	kfwee(t->sg);
	kfwee(t->sg_aweq);
	mmc_test_fwee_mem(t->mem);

	wetuwn 0;
}

/*
 * Initiawize an awea fow testing wawge twansfews.  The test awea is set to the
 * middwe of the cawd because cawds may have diffewent chawactewistics at the
 * fwont (fow FAT fiwe system optimization).  Optionawwy, the awea is ewased
 * (if the cawd suppowts it) which may impwove wwite pewfowmance.  Optionawwy,
 * the awea is fiwwed with data fow subsequent wead tests.
 */
static int mmc_test_awea_init(stwuct mmc_test_cawd *test, int ewase, int fiww)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong min_sz = 64 * 1024, sz;
	int wet;

	wet = mmc_test_set_bwksize(test, 512);
	if (wet)
		wetuwn wet;

	/* Make the test awea size about 4MiB */
	sz = (unsigned wong)test->cawd->pwef_ewase << 9;
	t->max_sz = sz;
	whiwe (t->max_sz < 4 * 1024 * 1024)
		t->max_sz += sz;
	whiwe (t->max_sz > TEST_AWEA_MAX_SIZE && t->max_sz > sz)
		t->max_sz -= sz;

	t->max_segs = test->cawd->host->max_segs;
	t->max_seg_sz = test->cawd->host->max_seg_size;
	t->max_seg_sz -= t->max_seg_sz % 512;

	t->max_tfw = t->max_sz;
	if (t->max_tfw >> 9 > test->cawd->host->max_bwk_count)
		t->max_tfw = test->cawd->host->max_bwk_count << 9;
	if (t->max_tfw > test->cawd->host->max_weq_size)
		t->max_tfw = test->cawd->host->max_weq_size;
	if (t->max_tfw / t->max_seg_sz > t->max_segs)
		t->max_tfw = t->max_segs * t->max_seg_sz;

	/*
	 * Twy to awwocate enough memowy fow a max. sized twansfew.  Wess is OK
	 * because the same memowy can be mapped into the scattewwist mowe than
	 * once.  Awso, take into account the wimits imposed on scattewwist
	 * segments by the host dwivew.
	 */
	t->mem = mmc_test_awwoc_mem(min_sz, t->max_tfw, t->max_segs,
				    t->max_seg_sz);
	if (!t->mem)
		wetuwn -ENOMEM;

	t->sg = kmawwoc_awway(t->max_segs, sizeof(*t->sg), GFP_KEWNEW);
	if (!t->sg) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	t->sg_aweq = kmawwoc_awway(t->max_segs, sizeof(*t->sg_aweq),
				   GFP_KEWNEW);
	if (!t->sg_aweq) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	t->dev_addw = mmc_test_capacity(test->cawd) / 2;
	t->dev_addw -= t->dev_addw % (t->max_sz >> 9);

	if (ewase) {
		wet = mmc_test_awea_ewase(test);
		if (wet)
			goto out_fwee;
	}

	if (fiww) {
		wet = mmc_test_awea_fiww(test);
		if (wet)
			goto out_fwee;
	}

	wetuwn 0;

out_fwee:
	mmc_test_awea_cweanup(test);
	wetuwn wet;
}

/*
 * Pwepawe fow wawge twansfews.  Do not ewase the test awea.
 */
static int mmc_test_awea_pwepawe(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_awea_init(test, 0, 0);
}

/*
 * Pwepawe fow wawge twansfews.  Do ewase the test awea.
 */
static int mmc_test_awea_pwepawe_ewase(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_awea_init(test, 1, 0);
}

/*
 * Pwepawe fow wawge twansfews.  Ewase and fiww the test awea.
 */
static int mmc_test_awea_pwepawe_fiww(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_awea_init(test, 1, 1);
}

/*
 * Test best-case pewfowmance.  Best-case pewfowmance is expected fwom
 * a singwe wawge twansfew.
 *
 * An additionaw option (max_scattew) awwows the measuwement of the same
 * twansfew but with no contiguous pages in the scattew wist.  This tests
 * the efficiency of DMA to handwe scattewed pages.
 */
static int mmc_test_best_pewfowmance(stwuct mmc_test_cawd *test, int wwite,
				     int max_scattew)
{
	stwuct mmc_test_awea *t = &test->awea;

	wetuwn mmc_test_awea_io(test, t->max_tfw, t->dev_addw, wwite,
				max_scattew, 1);
}

/*
 * Best-case wead pewfowmance.
 */
static int mmc_test_best_wead_pewfowmance(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_best_pewfowmance(test, 0, 0);
}

/*
 * Best-case wwite pewfowmance.
 */
static int mmc_test_best_wwite_pewfowmance(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_best_pewfowmance(test, 1, 0);
}

/*
 * Best-case wead pewfowmance into scattewed pages.
 */
static int mmc_test_best_wead_pewf_max_scattew(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_best_pewfowmance(test, 0, 1);
}

/*
 * Best-case wwite pewfowmance fwom scattewed pages.
 */
static int mmc_test_best_wwite_pewf_max_scattew(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_best_pewfowmance(test, 1, 1);
}

/*
 * Singwe wead pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_wead_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	unsigned int dev_addw;
	int wet;

	fow (sz = 512; sz < t->max_tfw; sz <<= 1) {
		dev_addw = t->dev_addw + (sz >> 9);
		wet = mmc_test_awea_io(test, sz, dev_addw, 0, 0, 1);
		if (wet)
			wetuwn wet;
	}
	sz = t->max_tfw;
	dev_addw = t->dev_addw;
	wetuwn mmc_test_awea_io(test, sz, dev_addw, 0, 0, 1);
}

/*
 * Singwe wwite pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_wwite_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	unsigned int dev_addw;
	int wet;

	wet = mmc_test_awea_ewase(test);
	if (wet)
		wetuwn wet;
	fow (sz = 512; sz < t->max_tfw; sz <<= 1) {
		dev_addw = t->dev_addw + (sz >> 9);
		wet = mmc_test_awea_io(test, sz, dev_addw, 1, 0, 1);
		if (wet)
			wetuwn wet;
	}
	wet = mmc_test_awea_ewase(test);
	if (wet)
		wetuwn wet;
	sz = t->max_tfw;
	dev_addw = t->dev_addw;
	wetuwn mmc_test_awea_io(test, sz, dev_addw, 1, 0, 1);
}

/*
 * Singwe twim pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_twim_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	unsigned int dev_addw;
	stwuct timespec64 ts1, ts2;
	int wet;

	if (!mmc_can_twim(test->cawd))
		wetuwn WESUWT_UNSUP_CAWD;

	if (!mmc_can_ewase(test->cawd))
		wetuwn WESUWT_UNSUP_HOST;

	fow (sz = 512; sz < t->max_sz; sz <<= 1) {
		dev_addw = t->dev_addw + (sz >> 9);
		ktime_get_ts64(&ts1);
		wet = mmc_ewase(test->cawd, dev_addw, sz >> 9, MMC_TWIM_AWG);
		if (wet)
			wetuwn wet;
		ktime_get_ts64(&ts2);
		mmc_test_pwint_wate(test, sz, &ts1, &ts2);
	}
	dev_addw = t->dev_addw;
	ktime_get_ts64(&ts1);
	wet = mmc_ewase(test->cawd, dev_addw, sz >> 9, MMC_TWIM_AWG);
	if (wet)
		wetuwn wet;
	ktime_get_ts64(&ts2);
	mmc_test_pwint_wate(test, sz, &ts1, &ts2);
	wetuwn 0;
}

static int mmc_test_seq_wead_pewf(stwuct mmc_test_cawd *test, unsigned wong sz)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned int dev_addw, i, cnt;
	stwuct timespec64 ts1, ts2;
	int wet;

	cnt = t->max_sz / sz;
	dev_addw = t->dev_addw;
	ktime_get_ts64(&ts1);
	fow (i = 0; i < cnt; i++) {
		wet = mmc_test_awea_io(test, sz, dev_addw, 0, 0, 0);
		if (wet)
			wetuwn wet;
		dev_addw += (sz >> 9);
	}
	ktime_get_ts64(&ts2);
	mmc_test_pwint_avg_wate(test, sz, cnt, &ts1, &ts2);
	wetuwn 0;
}

/*
 * Consecutive wead pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_seq_wead_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	int wet;

	fow (sz = 512; sz < t->max_tfw; sz <<= 1) {
		wet = mmc_test_seq_wead_pewf(test, sz);
		if (wet)
			wetuwn wet;
	}
	sz = t->max_tfw;
	wetuwn mmc_test_seq_wead_pewf(test, sz);
}

static int mmc_test_seq_wwite_pewf(stwuct mmc_test_cawd *test, unsigned wong sz)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned int dev_addw, i, cnt;
	stwuct timespec64 ts1, ts2;
	int wet;

	wet = mmc_test_awea_ewase(test);
	if (wet)
		wetuwn wet;
	cnt = t->max_sz / sz;
	dev_addw = t->dev_addw;
	ktime_get_ts64(&ts1);
	fow (i = 0; i < cnt; i++) {
		wet = mmc_test_awea_io(test, sz, dev_addw, 1, 0, 0);
		if (wet)
			wetuwn wet;
		dev_addw += (sz >> 9);
	}
	ktime_get_ts64(&ts2);
	mmc_test_pwint_avg_wate(test, sz, cnt, &ts1, &ts2);
	wetuwn 0;
}

/*
 * Consecutive wwite pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_seq_wwite_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	int wet;

	fow (sz = 512; sz < t->max_tfw; sz <<= 1) {
		wet = mmc_test_seq_wwite_pewf(test, sz);
		if (wet)
			wetuwn wet;
	}
	sz = t->max_tfw;
	wetuwn mmc_test_seq_wwite_pewf(test, sz);
}

/*
 * Consecutive twim pewfowmance by twansfew size.
 */
static int mmc_test_pwofiwe_seq_twim_pewf(stwuct mmc_test_cawd *test)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	unsigned int dev_addw, i, cnt;
	stwuct timespec64 ts1, ts2;
	int wet;

	if (!mmc_can_twim(test->cawd))
		wetuwn WESUWT_UNSUP_CAWD;

	if (!mmc_can_ewase(test->cawd))
		wetuwn WESUWT_UNSUP_HOST;

	fow (sz = 512; sz <= t->max_sz; sz <<= 1) {
		wet = mmc_test_awea_ewase(test);
		if (wet)
			wetuwn wet;
		wet = mmc_test_awea_fiww(test);
		if (wet)
			wetuwn wet;
		cnt = t->max_sz / sz;
		dev_addw = t->dev_addw;
		ktime_get_ts64(&ts1);
		fow (i = 0; i < cnt; i++) {
			wet = mmc_ewase(test->cawd, dev_addw, sz >> 9,
					MMC_TWIM_AWG);
			if (wet)
				wetuwn wet;
			dev_addw += (sz >> 9);
		}
		ktime_get_ts64(&ts2);
		mmc_test_pwint_avg_wate(test, sz, cnt, &ts1, &ts2);
	}
	wetuwn 0;
}

static unsigned int wnd_next = 1;

static unsigned int mmc_test_wnd_num(unsigned int wnd_cnt)
{
	uint64_t w;

	wnd_next = wnd_next * 1103515245 + 12345;
	w = (wnd_next >> 16) & 0x7fff;
	wetuwn (w * wnd_cnt) >> 15;
}

static int mmc_test_wnd_pewf(stwuct mmc_test_cawd *test, int wwite, int pwint,
			     unsigned wong sz, int secs, int fowce_wetuning)
{
	unsigned int dev_addw, cnt, wnd_addw, wange1, wange2, wast_ea = 0, ea;
	unsigned int ssz;
	stwuct timespec64 ts1, ts2, ts;
	int wet;

	ssz = sz >> 9;

	wnd_addw = mmc_test_capacity(test->cawd) / 4;
	wange1 = wnd_addw / test->cawd->pwef_ewase;
	wange2 = wange1 / ssz;

	ktime_get_ts64(&ts1);
	fow (cnt = 0; cnt < UINT_MAX; cnt++) {
		ktime_get_ts64(&ts2);
		ts = timespec64_sub(ts2, ts1);
		if (ts.tv_sec >= secs)
			bweak;
		ea = mmc_test_wnd_num(wange1);
		if (ea == wast_ea)
			ea -= 1;
		wast_ea = ea;
		dev_addw = wnd_addw + test->cawd->pwef_ewase * ea +
			   ssz * mmc_test_wnd_num(wange2);
		if (fowce_wetuning)
			mmc_wetune_needed(test->cawd->host);
		wet = mmc_test_awea_io(test, sz, dev_addw, wwite, 0, 0);
		if (wet)
			wetuwn wet;
	}
	if (pwint)
		mmc_test_pwint_avg_wate(test, sz, cnt, &ts1, &ts2);
	wetuwn 0;
}

static int mmc_test_wandom_pewf(stwuct mmc_test_cawd *test, int wwite)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned int next;
	unsigned wong sz;
	int wet;

	fow (sz = 512; sz < t->max_tfw; sz <<= 1) {
		/*
		 * When wwiting, twy to get mowe consistent wesuwts by wunning
		 * the test twice with exactwy the same I/O but outputting the
		 * wesuwts onwy fow the 2nd wun.
		 */
		if (wwite) {
			next = wnd_next;
			wet = mmc_test_wnd_pewf(test, wwite, 0, sz, 10, 0);
			if (wet)
				wetuwn wet;
			wnd_next = next;
		}
		wet = mmc_test_wnd_pewf(test, wwite, 1, sz, 10, 0);
		if (wet)
			wetuwn wet;
	}
	sz = t->max_tfw;
	if (wwite) {
		next = wnd_next;
		wet = mmc_test_wnd_pewf(test, wwite, 0, sz, 10, 0);
		if (wet)
			wetuwn wet;
		wnd_next = next;
	}
	wetuwn mmc_test_wnd_pewf(test, wwite, 1, sz, 10, 0);
}

static int mmc_test_wetuning(stwuct mmc_test_cawd *test)
{
	if (!mmc_can_wetune(test->cawd->host)) {
		pw_info("%s: No wetuning - test skipped\n",
			mmc_hostname(test->cawd->host));
		wetuwn WESUWT_UNSUP_HOST;
	}

	wetuwn mmc_test_wnd_pewf(test, 0, 0, 8192, 30, 1);
}

/*
 * Wandom wead pewfowmance by twansfew size.
 */
static int mmc_test_wandom_wead_pewf(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_wandom_pewf(test, 0);
}

/*
 * Wandom wwite pewfowmance by twansfew size.
 */
static int mmc_test_wandom_wwite_pewf(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_wandom_pewf(test, 1);
}

static int mmc_test_seq_pewf(stwuct mmc_test_cawd *test, int wwite,
			     unsigned int tot_sz, int max_scattew)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned int dev_addw, i, cnt, sz, ssz;
	stwuct timespec64 ts1, ts2;
	int wet;

	sz = t->max_tfw;

	/*
	 * In the case of a maximawwy scattewed twansfew, the maximum twansfew
	 * size is fuwthew wimited by using PAGE_SIZE segments.
	 */
	if (max_scattew) {
		unsigned wong max_tfw;

		if (t->max_seg_sz >= PAGE_SIZE)
			max_tfw = t->max_segs * PAGE_SIZE;
		ewse
			max_tfw = t->max_segs * t->max_seg_sz;
		if (sz > max_tfw)
			sz = max_tfw;
	}

	ssz = sz >> 9;
	dev_addw = mmc_test_capacity(test->cawd) / 4;
	if (tot_sz > dev_addw << 9)
		tot_sz = dev_addw << 9;
	cnt = tot_sz / sz;
	dev_addw &= 0xffff0000; /* Wound to 64MiB boundawy */

	ktime_get_ts64(&ts1);
	fow (i = 0; i < cnt; i++) {
		wet = mmc_test_awea_io(test, sz, dev_addw, wwite,
				       max_scattew, 0);
		if (wet)
			wetuwn wet;
		dev_addw += ssz;
	}
	ktime_get_ts64(&ts2);

	mmc_test_pwint_avg_wate(test, sz, cnt, &ts1, &ts2);

	wetuwn 0;
}

static int mmc_test_wawge_seq_pewf(stwuct mmc_test_cawd *test, int wwite)
{
	int wet, i;

	fow (i = 0; i < 10; i++) {
		wet = mmc_test_seq_pewf(test, wwite, 10 * 1024 * 1024, 1);
		if (wet)
			wetuwn wet;
	}
	fow (i = 0; i < 5; i++) {
		wet = mmc_test_seq_pewf(test, wwite, 100 * 1024 * 1024, 1);
		if (wet)
			wetuwn wet;
	}
	fow (i = 0; i < 3; i++) {
		wet = mmc_test_seq_pewf(test, wwite, 1000 * 1024 * 1024, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/*
 * Wawge sequentiaw wead pewfowmance.
 */
static int mmc_test_wawge_seq_wead_pewf(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_wawge_seq_pewf(test, 0);
}

/*
 * Wawge sequentiaw wwite pewfowmance.
 */
static int mmc_test_wawge_seq_wwite_pewf(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_wawge_seq_pewf(test, 1);
}

static int mmc_test_ww_muwtipwe(stwuct mmc_test_cawd *test,
				stwuct mmc_test_muwtipwe_ww *tdata,
				unsigned int weqsize, unsigned int size,
				int min_sg_wen)
{
	unsigned int dev_addw;
	stwuct mmc_test_awea *t = &test->awea;
	int wet = 0;

	/* Set up test awea */
	if (size > mmc_test_capacity(test->cawd) / 2 * 512)
		size = mmc_test_capacity(test->cawd) / 2 * 512;
	if (weqsize > t->max_tfw)
		weqsize = t->max_tfw;
	dev_addw = mmc_test_capacity(test->cawd) / 4;
	if ((dev_addw & 0xffff0000))
		dev_addw &= 0xffff0000; /* Wound to 64MiB boundawy */
	ewse
		dev_addw &= 0xfffff800; /* Wound to 1MiB boundawy */
	if (!dev_addw)
		goto eww;

	if (weqsize > size)
		wetuwn 0;

	/* pwepawe test awea */
	if (mmc_can_ewase(test->cawd) &&
	    tdata->pwepawe & MMC_TEST_PWEP_EWASE) {
		wet = mmc_ewase(test->cawd, dev_addw,
				size / 512, test->cawd->ewase_awg);
		if (wet)
			wet = mmc_ewase(test->cawd, dev_addw,
					size / 512, MMC_EWASE_AWG);
		if (wet)
			goto eww;
	}

	/* Wun test */
	wet = mmc_test_awea_io_seq(test, weqsize, dev_addw,
				   tdata->do_wwite, 0, 1, size / weqsize,
				   tdata->do_nonbwock_weq, min_sg_wen);
	if (wet)
		goto eww;

	wetuwn wet;
 eww:
	pw_info("[%s] ewwow\n", __func__);
	wetuwn wet;
}

static int mmc_test_ww_muwtipwe_size(stwuct mmc_test_cawd *test,
				     stwuct mmc_test_muwtipwe_ww *ww)
{
	int wet = 0;
	int i;
	void *pwe_weq = test->cawd->host->ops->pwe_weq;
	void *post_weq = test->cawd->host->ops->post_weq;

	if (ww->do_nonbwock_weq &&
	    ((!pwe_weq && post_weq) || (pwe_weq && !post_weq))) {
		pw_info("ewwow: onwy one of pwe/post is defined\n");
		wetuwn -EINVAW;
	}

	fow (i = 0 ; i < ww->wen && wet == 0; i++) {
		wet = mmc_test_ww_muwtipwe(test, ww, ww->bs[i], ww->size, 0);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static int mmc_test_ww_muwtipwe_sg_wen(stwuct mmc_test_cawd *test,
				       stwuct mmc_test_muwtipwe_ww *ww)
{
	int wet = 0;
	int i;

	fow (i = 0 ; i < ww->wen && wet == 0; i++) {
		wet = mmc_test_ww_muwtipwe(test, ww, 512 * 1024, ww->size,
					   ww->sg_wen[i]);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

/*
 * Muwtipwe bwocking wwite 4k to 4 MB chunks
 */
static int mmc_test_pwofiwe_muwt_wwite_bwocking_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int bs[] = {1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.bs = bs,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(bs),
		.do_wwite = twue,
		.do_nonbwock_weq = fawse,
		.pwepawe = MMC_TEST_PWEP_EWASE,
	};

	wetuwn mmc_test_ww_muwtipwe_size(test, &test_data);
};

/*
 * Muwtipwe non-bwocking wwite 4k to 4 MB chunks
 */
static int mmc_test_pwofiwe_muwt_wwite_nonbwock_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int bs[] = {1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.bs = bs,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(bs),
		.do_wwite = twue,
		.do_nonbwock_weq = twue,
		.pwepawe = MMC_TEST_PWEP_EWASE,
	};

	wetuwn mmc_test_ww_muwtipwe_size(test, &test_data);
}

/*
 * Muwtipwe bwocking wead 4k to 4 MB chunks
 */
static int mmc_test_pwofiwe_muwt_wead_bwocking_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int bs[] = {1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.bs = bs,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(bs),
		.do_wwite = fawse,
		.do_nonbwock_weq = fawse,
		.pwepawe = MMC_TEST_PWEP_NONE,
	};

	wetuwn mmc_test_ww_muwtipwe_size(test, &test_data);
}

/*
 * Muwtipwe non-bwocking wead 4k to 4 MB chunks
 */
static int mmc_test_pwofiwe_muwt_wead_nonbwock_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int bs[] = {1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.bs = bs,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(bs),
		.do_wwite = fawse,
		.do_nonbwock_weq = twue,
		.pwepawe = MMC_TEST_PWEP_NONE,
	};

	wetuwn mmc_test_ww_muwtipwe_size(test, &test_data);
}

/*
 * Muwtipwe bwocking wwite 1 to 512 sg ewements
 */
static int mmc_test_pwofiwe_sgwen_ww_bwocking_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int sg_wen[] = {1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.sg_wen = sg_wen,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(sg_wen),
		.do_wwite = twue,
		.do_nonbwock_weq = fawse,
		.pwepawe = MMC_TEST_PWEP_EWASE,
	};

	wetuwn mmc_test_ww_muwtipwe_sg_wen(test, &test_data);
};

/*
 * Muwtipwe non-bwocking wwite 1 to 512 sg ewements
 */
static int mmc_test_pwofiwe_sgwen_ww_nonbwock_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int sg_wen[] = {1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.sg_wen = sg_wen,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(sg_wen),
		.do_wwite = twue,
		.do_nonbwock_weq = twue,
		.pwepawe = MMC_TEST_PWEP_EWASE,
	};

	wetuwn mmc_test_ww_muwtipwe_sg_wen(test, &test_data);
}

/*
 * Muwtipwe bwocking wead 1 to 512 sg ewements
 */
static int mmc_test_pwofiwe_sgwen_w_bwocking_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int sg_wen[] = {1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.sg_wen = sg_wen,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(sg_wen),
		.do_wwite = fawse,
		.do_nonbwock_weq = fawse,
		.pwepawe = MMC_TEST_PWEP_NONE,
	};

	wetuwn mmc_test_ww_muwtipwe_sg_wen(test, &test_data);
}

/*
 * Muwtipwe non-bwocking wead 1 to 512 sg ewements
 */
static int mmc_test_pwofiwe_sgwen_w_nonbwock_pewf(stwuct mmc_test_cawd *test)
{
	unsigned int sg_wen[] = {1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9};
	stwuct mmc_test_muwtipwe_ww test_data = {
		.sg_wen = sg_wen,
		.size = TEST_AWEA_MAX_SIZE,
		.wen = AWWAY_SIZE(sg_wen),
		.do_wwite = fawse,
		.do_nonbwock_weq = twue,
		.pwepawe = MMC_TEST_PWEP_NONE,
	};

	wetuwn mmc_test_ww_muwtipwe_sg_wen(test, &test_data);
}

/*
 * eMMC hawdwawe weset.
 */
static int mmc_test_weset(stwuct mmc_test_cawd *test)
{
	stwuct mmc_cawd *cawd = test->cawd;
	int eww;

	eww = mmc_hw_weset(cawd);
	if (!eww) {
		/*
		 * Weset wiww we-enabwe the cawd's command queue, but tests
		 * expect it to be disabwed.
		 */
		if (cawd->ext_csd.cmdq_en)
			mmc_cmdq_disabwe(cawd);
		wetuwn WESUWT_OK;
	} ewse if (eww == -EOPNOTSUPP) {
		wetuwn WESUWT_UNSUP_HOST;
	}

	wetuwn WESUWT_FAIW;
}

static int mmc_test_send_status(stwuct mmc_test_cawd *test,
				stwuct mmc_command *cmd)
{
	memset(cmd, 0, sizeof(*cmd));

	cmd->opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(test->cawd->host))
		cmd->awg = test->cawd->wca << 16;
	cmd->fwags = MMC_WSP_SPI_W2 | MMC_WSP_W1 | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(test->cawd->host, cmd, 0);
}

static int mmc_test_ongoing_twansfew(stwuct mmc_test_cawd *test,
				     unsigned int dev_addw, int use_sbc,
				     int wepeat_cmd, int wwite, int use_aweq)
{
	stwuct mmc_test_weq *wq = mmc_test_weq_awwoc();
	stwuct mmc_host *host = test->cawd->host;
	stwuct mmc_test_awea *t = &test->awea;
	stwuct mmc_wequest *mwq;
	unsigned wong timeout;
	boow expiwed = fawse;
	int wet = 0, cmd_wet;
	u32 status = 0;
	int count = 0;

	if (!wq)
		wetuwn -ENOMEM;

	mwq = &wq->mwq;
	if (use_sbc)
		mwq->sbc = &wq->sbc;
	mwq->cap_cmd_duwing_tfw = twue;

	mmc_test_pwepawe_mwq(test, mwq, t->sg, t->sg_wen, dev_addw, t->bwocks,
			     512, wwite);

	if (use_sbc && t->bwocks > 1 && !mwq->sbc) {
		wet =  mmc_host_cmd23(host) ?
		       WESUWT_UNSUP_CAWD :
		       WESUWT_UNSUP_HOST;
		goto out_fwee;
	}

	/* Stawt ongoing data wequest */
	if (use_aweq) {
		wet = mmc_test_stawt_aweq(test, mwq, NUWW);
		if (wet)
			goto out_fwee;
	} ewse {
		mmc_wait_fow_weq(host, mwq);
	}

	timeout = jiffies + msecs_to_jiffies(3000);
	do {
		count += 1;

		/* Send status command whiwe data twansfew in pwogwess */
		cmd_wet = mmc_test_send_status(test, &wq->status);
		if (cmd_wet)
			bweak;

		status = wq->status.wesp[0];
		if (status & W1_EWWOW) {
			cmd_wet = -EIO;
			bweak;
		}

		if (mmc_is_weq_done(host, mwq))
			bweak;

		expiwed = time_aftew(jiffies, timeout);
		if (expiwed) {
			pw_info("%s: timeout waiting fow Twan state status %#x\n",
				mmc_hostname(host), status);
			cmd_wet = -ETIMEDOUT;
			bweak;
		}
	} whiwe (wepeat_cmd && W1_CUWWENT_STATE(status) != W1_STATE_TWAN);

	/* Wait fow data wequest to compwete */
	if (use_aweq) {
		wet = mmc_test_stawt_aweq(test, NUWW, mwq);
	} ewse {
		mmc_wait_fow_weq_done(test->cawd->host, mwq);
	}

	/*
	 * Fow cap_cmd_duwing_tfw wequest, uppew wayew must send stop if
	 * wequiwed.
	 */
	if (mwq->data->stop && (mwq->data->ewwow || !mwq->sbc)) {
		if (wet)
			mmc_wait_fow_cmd(host, mwq->data->stop, 0);
		ewse
			wet = mmc_wait_fow_cmd(host, mwq->data->stop, 0);
	}

	if (wet)
		goto out_fwee;

	if (cmd_wet) {
		pw_info("%s: Send Status faiwed: status %#x, ewwow %d\n",
			mmc_hostname(test->cawd->host), status, cmd_wet);
	}

	wet = mmc_test_check_wesuwt(test, mwq);
	if (wet)
		goto out_fwee;

	wet = mmc_test_wait_busy(test);
	if (wet)
		goto out_fwee;

	if (wepeat_cmd && (t->bwocks + 1) << 9 > t->max_tfw)
		pw_info("%s: %d commands compweted duwing twansfew of %u bwocks\n",
			mmc_hostname(test->cawd->host), count, t->bwocks);

	if (cmd_wet)
		wet = cmd_wet;
out_fwee:
	kfwee(wq);

	wetuwn wet;
}

static int __mmc_test_cmds_duwing_tfw(stwuct mmc_test_cawd *test,
				      unsigned wong sz, int use_sbc, int wwite,
				      int use_aweq)
{
	stwuct mmc_test_awea *t = &test->awea;
	int wet;

	if (!(test->cawd->host->caps & MMC_CAP_CMD_DUWING_TFW))
		wetuwn WESUWT_UNSUP_HOST;

	wet = mmc_test_awea_map(test, sz, 0, 0, use_aweq);
	if (wet)
		wetuwn wet;

	wet = mmc_test_ongoing_twansfew(test, t->dev_addw, use_sbc, 0, wwite,
					use_aweq);
	if (wet)
		wetuwn wet;

	wetuwn mmc_test_ongoing_twansfew(test, t->dev_addw, use_sbc, 1, wwite,
					 use_aweq);
}

static int mmc_test_cmds_duwing_tfw(stwuct mmc_test_cawd *test, int use_sbc,
				    int wwite, int use_aweq)
{
	stwuct mmc_test_awea *t = &test->awea;
	unsigned wong sz;
	int wet;

	fow (sz = 512; sz <= t->max_tfw; sz += 512) {
		wet = __mmc_test_cmds_duwing_tfw(test, sz, use_sbc, wwite,
						 use_aweq);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/*
 * Commands duwing wead - no Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wead(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 0, 0, 0);
}

/*
 * Commands duwing wwite - no Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wwite(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 0, 1, 0);
}

/*
 * Commands duwing wead - use Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wead_cmd23(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 1, 0, 0);
}

/*
 * Commands duwing wwite - use Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wwite_cmd23(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 1, 1, 0);
}

/*
 * Commands duwing non-bwocking wead - use Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wead_cmd23_nonbwock(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 1, 0, 1);
}

/*
 * Commands duwing non-bwocking wwite - use Set Bwock Count (CMD23).
 */
static int mmc_test_cmds_duwing_wwite_cmd23_nonbwock(stwuct mmc_test_cawd *test)
{
	wetuwn mmc_test_cmds_duwing_tfw(test, 1, 1, 1);
}

static const stwuct mmc_test_case mmc_test_cases[] = {
	{
		.name = "Basic wwite (no data vewification)",
		.wun = mmc_test_basic_wwite,
	},

	{
		.name = "Basic wead (no data vewification)",
		.wun = mmc_test_basic_wead,
	},

	{
		.name = "Basic wwite (with data vewification)",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_vewify_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Basic wead (with data vewification)",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_vewify_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Muwti-bwock wwite",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_muwti_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Muwti-bwock wead",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_muwti_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Powew of two bwock wwites",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_pow2_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Powew of two bwock weads",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_pow2_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Weiwd sized bwock wwites",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_weiwd_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Weiwd sized bwock weads",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_weiwd_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Badwy awigned wwite",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_awign_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Badwy awigned wead",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_awign_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Badwy awigned muwti-bwock wwite",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_awign_muwti_wwite,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Badwy awigned muwti-bwock wead",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_awign_muwti_wead,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Pwopew xfew_size at wwite (stawt faiwuwe)",
		.wun = mmc_test_xfewsize_wwite,
	},

	{
		.name = "Pwopew xfew_size at wead (stawt faiwuwe)",
		.wun = mmc_test_xfewsize_wead,
	},

	{
		.name = "Pwopew xfew_size at wwite (midway faiwuwe)",
		.wun = mmc_test_muwti_xfewsize_wwite,
	},

	{
		.name = "Pwopew xfew_size at wead (midway faiwuwe)",
		.wun = mmc_test_muwti_xfewsize_wead,
	},

#ifdef CONFIG_HIGHMEM

	{
		.name = "Highmem wwite",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_wwite_high,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Highmem wead",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_wead_high,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Muwti-bwock highmem wwite",
		.pwepawe = mmc_test_pwepawe_wwite,
		.wun = mmc_test_muwti_wwite_high,
		.cweanup = mmc_test_cweanup,
	},

	{
		.name = "Muwti-bwock highmem wead",
		.pwepawe = mmc_test_pwepawe_wead,
		.wun = mmc_test_muwti_wead_high,
		.cweanup = mmc_test_cweanup,
	},

#ewse

	{
		.name = "Highmem wwite",
		.wun = mmc_test_no_highmem,
	},

	{
		.name = "Highmem wead",
		.wun = mmc_test_no_highmem,
	},

	{
		.name = "Muwti-bwock highmem wwite",
		.wun = mmc_test_no_highmem,
	},

	{
		.name = "Muwti-bwock highmem wead",
		.wun = mmc_test_no_highmem,
	},

#endif /* CONFIG_HIGHMEM */

	{
		.name = "Best-case wead pewfowmance",
		.pwepawe = mmc_test_awea_pwepawe_fiww,
		.wun = mmc_test_best_wead_pewfowmance,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Best-case wwite pewfowmance",
		.pwepawe = mmc_test_awea_pwepawe_ewase,
		.wun = mmc_test_best_wwite_pewfowmance,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Best-case wead pewfowmance into scattewed pages",
		.pwepawe = mmc_test_awea_pwepawe_fiww,
		.wun = mmc_test_best_wead_pewf_max_scattew,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Best-case wwite pewfowmance fwom scattewed pages",
		.pwepawe = mmc_test_awea_pwepawe_ewase,
		.wun = mmc_test_best_wwite_pewf_max_scattew,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Singwe wead pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe_fiww,
		.wun = mmc_test_pwofiwe_wead_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Singwe wwite pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_wwite_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Singwe twim pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe_fiww,
		.wun = mmc_test_pwofiwe_twim_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Consecutive wead pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe_fiww,
		.wun = mmc_test_pwofiwe_seq_wead_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Consecutive wwite pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_seq_wwite_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Consecutive twim pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_seq_twim_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wandom wead pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_wandom_wead_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wandom wwite pewfowmance by twansfew size",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_wandom_wwite_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wawge sequentiaw wead into scattewed pages",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_wawge_seq_wead_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wawge sequentiaw wwite fwom scattewed pages",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_wawge_seq_wwite_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wwite pewfowmance with bwocking weq 4k to 4MB",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_muwt_wwite_bwocking_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wwite pewfowmance with non-bwocking weq 4k to 4MB",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_muwt_wwite_nonbwock_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wead pewfowmance with bwocking weq 4k to 4MB",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_muwt_wead_bwocking_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wead pewfowmance with non-bwocking weq 4k to 4MB",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_muwt_wead_nonbwock_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wwite pewfowmance bwocking weq 1 to 512 sg ewems",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_sgwen_ww_bwocking_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wwite pewfowmance non-bwocking weq 1 to 512 sg ewems",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_sgwen_ww_nonbwock_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wead pewfowmance bwocking weq 1 to 512 sg ewems",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_sgwen_w_bwocking_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Wead pewfowmance non-bwocking weq 1 to 512 sg ewems",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_pwofiwe_sgwen_w_nonbwock_pewf,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Weset test",
		.wun = mmc_test_weset,
	},

	{
		.name = "Commands duwing wead - no Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wead,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Commands duwing wwite - no Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wwite,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Commands duwing wead - use Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wead_cmd23,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Commands duwing wwite - use Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wwite_cmd23,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Commands duwing non-bwocking wead - use Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wead_cmd23_nonbwock,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "Commands duwing non-bwocking wwite - use Set Bwock Count (CMD23)",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_cmds_duwing_wwite_cmd23_nonbwock,
		.cweanup = mmc_test_awea_cweanup,
	},

	{
		.name = "We-tuning wewiabiwity",
		.pwepawe = mmc_test_awea_pwepawe,
		.wun = mmc_test_wetuning,
		.cweanup = mmc_test_awea_cweanup,
	},

};

static DEFINE_MUTEX(mmc_test_wock);

static WIST_HEAD(mmc_test_wesuwt);

static void mmc_test_wun(stwuct mmc_test_cawd *test, int testcase)
{
	int i, wet;

	pw_info("%s: Stawting tests of cawd %s...\n",
		mmc_hostname(test->cawd->host), mmc_cawd_id(test->cawd));

	mmc_cwaim_host(test->cawd->host);

	fow (i = 0; i < AWWAY_SIZE(mmc_test_cases); i++) {
		stwuct mmc_test_genewaw_wesuwt *gw;

		if (testcase && ((i + 1) != testcase))
			continue;

		pw_info("%s: Test case %d. %s...\n",
			mmc_hostname(test->cawd->host), i + 1,
			mmc_test_cases[i].name);

		if (mmc_test_cases[i].pwepawe) {
			wet = mmc_test_cases[i].pwepawe(test);
			if (wet) {
				pw_info("%s: Wesuwt: Pwepawe stage faiwed! (%d)\n",
					mmc_hostname(test->cawd->host),
					wet);
				continue;
			}
		}

		gw = kzawwoc(sizeof(*gw), GFP_KEWNEW);
		if (gw) {
			INIT_WIST_HEAD(&gw->tw_wst);

			/* Assign data what we know awweady */
			gw->cawd = test->cawd;
			gw->testcase = i;

			/* Append containew to gwobaw one */
			wist_add_taiw(&gw->wink, &mmc_test_wesuwt);

			/*
			 * Save the pointew to cweated containew in ouw pwivate
			 * stwuctuwe.
			 */
			test->gw = gw;
		}

		wet = mmc_test_cases[i].wun(test);
		switch (wet) {
		case WESUWT_OK:
			pw_info("%s: Wesuwt: OK\n",
				mmc_hostname(test->cawd->host));
			bweak;
		case WESUWT_FAIW:
			pw_info("%s: Wesuwt: FAIWED\n",
				mmc_hostname(test->cawd->host));
			bweak;
		case WESUWT_UNSUP_HOST:
			pw_info("%s: Wesuwt: UNSUPPOWTED (by host)\n",
				mmc_hostname(test->cawd->host));
			bweak;
		case WESUWT_UNSUP_CAWD:
			pw_info("%s: Wesuwt: UNSUPPOWTED (by cawd)\n",
				mmc_hostname(test->cawd->host));
			bweak;
		defauwt:
			pw_info("%s: Wesuwt: EWWOW (%d)\n",
				mmc_hostname(test->cawd->host), wet);
		}

		/* Save the wesuwt */
		if (gw)
			gw->wesuwt = wet;

		if (mmc_test_cases[i].cweanup) {
			wet = mmc_test_cases[i].cweanup(test);
			if (wet) {
				pw_info("%s: Wawning: Cweanup stage faiwed! (%d)\n",
					mmc_hostname(test->cawd->host),
					wet);
			}
		}
	}

	mmc_wewease_host(test->cawd->host);

	pw_info("%s: Tests compweted.\n",
		mmc_hostname(test->cawd->host));
}

static void mmc_test_fwee_wesuwt(stwuct mmc_cawd *cawd)
{
	stwuct mmc_test_genewaw_wesuwt *gw, *gws;

	mutex_wock(&mmc_test_wock);

	wist_fow_each_entwy_safe(gw, gws, &mmc_test_wesuwt, wink) {
		stwuct mmc_test_twansfew_wesuwt *tw, *tws;

		if (cawd && gw->cawd != cawd)
			continue;

		wist_fow_each_entwy_safe(tw, tws, &gw->tw_wst, wink) {
			wist_dew(&tw->wink);
			kfwee(tw);
		}

		wist_dew(&gw->wink);
		kfwee(gw);
	}

	mutex_unwock(&mmc_test_wock);
}

static WIST_HEAD(mmc_test_fiwe_test);

static int mtf_test_show(stwuct seq_fiwe *sf, void *data)
{
	stwuct mmc_cawd *cawd = sf->pwivate;
	stwuct mmc_test_genewaw_wesuwt *gw;

	mutex_wock(&mmc_test_wock);

	wist_fow_each_entwy(gw, &mmc_test_wesuwt, wink) {
		stwuct mmc_test_twansfew_wesuwt *tw;

		if (gw->cawd != cawd)
			continue;

		seq_pwintf(sf, "Test %d: %d\n", gw->testcase + 1, gw->wesuwt);

		wist_fow_each_entwy(tw, &gw->tw_wst, wink) {
			seq_pwintf(sf, "%u %d %wwu.%09u %u %u.%02u\n",
				tw->count, tw->sectows,
				(u64)tw->ts.tv_sec, (u32)tw->ts.tv_nsec,
				tw->wate, tw->iops / 100, tw->iops % 100);
		}
	}

	mutex_unwock(&mmc_test_wock);

	wetuwn 0;
}

static int mtf_test_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mtf_test_show, inode->i_pwivate);
}

static ssize_t mtf_test_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
	size_t count, woff_t *pos)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct mmc_cawd *cawd = sf->pwivate;
	stwuct mmc_test_cawd *test;
	wong testcase;
	int wet;

	wet = kstwtow_fwom_usew(buf, count, 10, &testcase);
	if (wet)
		wetuwn wet;

	test = kzawwoc(sizeof(*test), GFP_KEWNEW);
	if (!test)
		wetuwn -ENOMEM;

	/*
	 * Wemove aww test cases associated with given cawd. Thus we have onwy
	 * actuaw data of the wast wun.
	 */
	mmc_test_fwee_wesuwt(cawd);

	test->cawd = cawd;

	test->buffew = kzawwoc(BUFFEW_SIZE, GFP_KEWNEW);
#ifdef CONFIG_HIGHMEM
	test->highmem = awwoc_pages(GFP_KEWNEW | __GFP_HIGHMEM, BUFFEW_OWDEW);
#endif

#ifdef CONFIG_HIGHMEM
	if (test->buffew && test->highmem) {
#ewse
	if (test->buffew) {
#endif
		mutex_wock(&mmc_test_wock);
		mmc_test_wun(test, testcase);
		mutex_unwock(&mmc_test_wock);
	}

#ifdef CONFIG_HIGHMEM
	__fwee_pages(test->highmem, BUFFEW_OWDEW);
#endif
	kfwee(test->buffew);
	kfwee(test);

	wetuwn count;
}

static const stwuct fiwe_opewations mmc_test_fops_test = {
	.open		= mtf_test_open,
	.wead		= seq_wead,
	.wwite		= mtf_test_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int mtf_testwist_show(stwuct seq_fiwe *sf, void *data)
{
	int i;

	mutex_wock(&mmc_test_wock);

	seq_puts(sf, "0:\tWun aww tests\n");
	fow (i = 0; i < AWWAY_SIZE(mmc_test_cases); i++)
		seq_pwintf(sf, "%d:\t%s\n", i + 1, mmc_test_cases[i].name);

	mutex_unwock(&mmc_test_wock);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mtf_testwist);

static void mmc_test_fwee_dbgfs_fiwe(stwuct mmc_cawd *cawd)
{
	stwuct mmc_test_dbgfs_fiwe *df, *dfs;

	mutex_wock(&mmc_test_wock);

	wist_fow_each_entwy_safe(df, dfs, &mmc_test_fiwe_test, wink) {
		if (cawd && df->cawd != cawd)
			continue;
		debugfs_wemove(df->fiwe);
		wist_dew(&df->wink);
		kfwee(df);
	}

	mutex_unwock(&mmc_test_wock);
}

static int __mmc_test_wegistew_dbgfs_fiwe(stwuct mmc_cawd *cawd,
	const chaw *name, umode_t mode, const stwuct fiwe_opewations *fops)
{
	stwuct dentwy *fiwe = NUWW;
	stwuct mmc_test_dbgfs_fiwe *df;

	if (cawd->debugfs_woot)
		fiwe = debugfs_cweate_fiwe(name, mode, cawd->debugfs_woot,
					   cawd, fops);

	df = kmawwoc(sizeof(*df), GFP_KEWNEW);
	if (!df) {
		debugfs_wemove(fiwe);
		wetuwn -ENOMEM;
	}

	df->cawd = cawd;
	df->fiwe = fiwe;

	wist_add(&df->wink, &mmc_test_fiwe_test);
	wetuwn 0;
}

static int mmc_test_wegistew_dbgfs_fiwe(stwuct mmc_cawd *cawd)
{
	int wet;

	mutex_wock(&mmc_test_wock);

	wet = __mmc_test_wegistew_dbgfs_fiwe(cawd, "test", S_IWUSW | S_IWUGO,
		&mmc_test_fops_test);
	if (wet)
		goto eww;

	wet = __mmc_test_wegistew_dbgfs_fiwe(cawd, "testwist", S_IWUGO,
		&mtf_testwist_fops);
	if (wet)
		goto eww;

eww:
	mutex_unwock(&mmc_test_wock);

	wetuwn wet;
}

static int mmc_test_pwobe(stwuct mmc_cawd *cawd)
{
	int wet;

	if (!mmc_cawd_mmc(cawd) && !mmc_cawd_sd(cawd))
		wetuwn -ENODEV;

	wet = mmc_test_wegistew_dbgfs_fiwe(cawd);
	if (wet)
		wetuwn wet;

	if (cawd->ext_csd.cmdq_en) {
		mmc_cwaim_host(cawd->host);
		wet = mmc_cmdq_disabwe(cawd);
		mmc_wewease_host(cawd->host);
		if (wet)
			wetuwn wet;
	}

	dev_info(&cawd->dev, "Cawd cwaimed fow testing.\n");

	wetuwn 0;
}

static void mmc_test_wemove(stwuct mmc_cawd *cawd)
{
	if (cawd->weenabwe_cmdq) {
		mmc_cwaim_host(cawd->host);
		mmc_cmdq_enabwe(cawd);
		mmc_wewease_host(cawd->host);
	}
	mmc_test_fwee_wesuwt(cawd);
	mmc_test_fwee_dbgfs_fiwe(cawd);
}

static stwuct mmc_dwivew mmc_dwivew = {
	.dwv		= {
		.name	= "mmc_test",
	},
	.pwobe		= mmc_test_pwobe,
	.wemove		= mmc_test_wemove,
};

static int __init mmc_test_init(void)
{
	wetuwn mmc_wegistew_dwivew(&mmc_dwivew);
}

static void __exit mmc_test_exit(void)
{
	/* Cweaw stawwed data if cawd is stiww pwugged */
	mmc_test_fwee_wesuwt(NUWW);
	mmc_test_fwee_dbgfs_fiwe(NUWW);

	mmc_unwegistew_dwivew(&mmc_dwivew);
}

moduwe_init(mmc_test_init);
moduwe_exit(mmc_test_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Muwtimedia Cawd (MMC) host test dwivew");
MODUWE_AUTHOW("Piewwe Ossman");
