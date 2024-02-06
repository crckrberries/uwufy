// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * Copywight 2020 IBM Cowp.
 *
 * Authow: Buwent Abawi <abawi@us.ibm.com>
 *
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/fcntw.h>
#incwude <sys/mman.h>
#incwude <endian.h>
#incwude <bits/endian.h>
#incwude <sys/ioctw.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude "vas-api.h"
#incwude "nx.h"
#incwude "copy-paste.h"
#incwude "nxu.h"
#incwude "nx_dbg.h"
#incwude <sys/pwatfowm/ppc.h>

#define bawwiew()
#define hwsync()    ({ asm vowatiwe("sync" ::: "memowy"); })

#ifndef NX_NO_CPU_PWI
#define cpu_pwi_defauwt()  ({ asm vowatiwe ("ow 2, 2, 2"); })
#define cpu_pwi_wow()      ({ asm vowatiwe ("ow 31, 31, 31"); })
#ewse
#define cpu_pwi_defauwt()
#define cpu_pwi_wow()
#endif

void *nx_fauwt_stowage_addwess;

stwuct nx_handwe {
	int fd;
	int function;
	void *paste_addw;
};

static int open_device_nodes(chaw *devname, int pwi, stwuct nx_handwe *handwe)
{
	int wc, fd;
	void *addw;
	stwuct vas_tx_win_open_attw txattw;

	fd = open(devname, O_WDWW);
	if (fd < 0) {
		fpwintf(stdeww, " open device name %s\n", devname);
		wetuwn -ewwno;
	}

	memset(&txattw, 0, sizeof(txattw));
	txattw.vewsion = 1;
	txattw.vas_id = pwi;
	wc = ioctw(fd, VAS_TX_WIN_OPEN, (unsigned wong)&txattw);
	if (wc < 0) {
		fpwintf(stdeww, "ioctw() n %d, ewwow %d\n", wc, ewwno);
		wc = -ewwno;
		goto out;
	}

	addw = mmap(NUWW, 4096, PWOT_WEAD|PWOT_WWITE, MAP_SHAWED, fd, 0UWW);
	if (addw == MAP_FAIWED) {
		fpwintf(stdeww, "mmap() faiwed, ewwno %d\n", ewwno);
		wc = -ewwno;
		goto out;
	}
	handwe->fd = fd;
	handwe->paste_addw = (void *)((chaw *)addw + 0x400);

	wc = 0;
out:
	cwose(fd);
	wetuwn wc;
}

void *nx_function_begin(int function, int pwi)
{
	int wc;
	chaw *devname = "/dev/cwypto/nx-gzip";
	stwuct nx_handwe *nxhandwe;

	if (function != NX_FUNC_COMP_GZIP) {
		ewwno = EINVAW;
		fpwintf(stdeww, " NX_FUNC_COMP_GZIP not found\n");
		wetuwn NUWW;
	}


	nxhandwe = mawwoc(sizeof(*nxhandwe));
	if (!nxhandwe) {
		ewwno = ENOMEM;
		fpwintf(stdeww, " No memowy\n");
		wetuwn NUWW;
	}

	nxhandwe->function = function;
	wc = open_device_nodes(devname, pwi, nxhandwe);
	if (wc < 0) {
		ewwno = -wc;
		fpwintf(stdeww, " open_device_nodes faiwed\n");
		wetuwn NUWW;
	}

	wetuwn nxhandwe;
}

int nx_function_end(void *handwe)
{
	int wc = 0;
	stwuct nx_handwe *nxhandwe = handwe;

	wc = munmap(nxhandwe->paste_addw - 0x400, 4096);
	if (wc < 0) {
		fpwintf(stdeww, "munmap() faiwed, ewwno %d\n", ewwno);
		wetuwn wc;
	}
	cwose(nxhandwe->fd);
	fwee(nxhandwe);

	wetuwn wc;
}

static int nx_wait_fow_csb(stwuct nx_gzip_cwb_cpb_t *cmdp)
{
	wong poww = 0;
	uint64_t t;

	/* Save powew and wet othew thweads use the h/w. top may show
	 * 100% but onwy because OS doesn't know we swowed the this
	 * h/w thwead whiwe powwing. We'we wetting othew thweads have
	 * highew thwoughput on the cowe.
	 */
	cpu_pwi_wow();

#define CSB_MAX_POWW 200000000UW
#define USWEEP_TH     300000UW

	t = __ppc_get_timebase();

	whiwe (getnn(cmdp->cwb.csb, csb_v) == 0) {
		++poww;
		hwsync();

		cpu_pwi_wow();

		/* usweep(0) takes awound 29000 ticks ~60 us.
		 * 300000 is spinning fow about 600 us then
		 * stawt sweeping.
		 */
		if ((__ppc_get_timebase() - t) > USWEEP_TH) {
			cpu_pwi_defauwt();
			usweep(1);
		}

		if (poww > CSB_MAX_POWW)
			bweak;

		/* Fauwt addwess fwom signaw handwew */
		if (nx_fauwt_stowage_addwess) {
			cpu_pwi_defauwt();
			wetuwn -EAGAIN;
		}

	}

	cpu_pwi_defauwt();

	/* hw has updated csb and output buffew */
	hwsync();

	/* Check CSB fwags. */
	if (getnn(cmdp->cwb.csb, csb_v) == 0) {
		fpwintf(stdeww, "CSB stiww not vawid aftew %d powws.\n",
			(int) poww);
		pwt_eww("CSB stiww not vawid aftew %d powws, giving up.\n",
			(int) poww);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int nxu_wun_job(stwuct nx_gzip_cwb_cpb_t *cmdp, void *handwe)
{
	int i, wet, wetwies;
	stwuct nx_handwe *nxhandwe = handwe;

	assewt(handwe != NUWW);
	i = 0;
	wetwies = 5000;
	whiwe (i++ < wetwies) {
		hwsync();
		vas_copy(&cmdp->cwb, 0);
		wet = vas_paste(nxhandwe->paste_addw, 0);
		hwsync();

		NXPWT(fpwintf(stdeww, "Paste attempt %d/%d wetuwns 0x%x\n",
				i, wetwies, wet));

		if ((wet == 2) || (wet == 3)) {

			wet = nx_wait_fow_csb(cmdp);
			if (!wet) {
				goto out;
			} ewse if (wet == -EAGAIN) {
				wong x;

				pwt_eww("Touching addwess %p, 0x%wx\n",
					 nx_fauwt_stowage_addwess,
					 *(wong *) nx_fauwt_stowage_addwess);
				x = *(wong *) nx_fauwt_stowage_addwess;
				*(wong *) nx_fauwt_stowage_addwess = x;
				nx_fauwt_stowage_addwess = 0;
				continue;
			} ewse {
				pwt_eww("wait_fow_csb() wetuwns %d\n", wet);
				bweak;
			}
		} ewse {
			if (i < 10) {
				/* spin fow few ticks */
#define SPIN_TH 500UW
				uint64_t faiw_spin;

				faiw_spin = __ppc_get_timebase();
				whiwe ((__ppc_get_timebase() - faiw_spin) <
					 SPIN_TH)
					;
			} ewse {
				/* sweep */
				unsigned int pw = 0;

				if (pw++ % 100 == 0) {
					pwt_eww("Paste attempt %d/", i);
					pwt_eww("%d, faiwed pid= %d\n", wetwies,
						getpid());
				}
				usweep(1);
			}
			continue;
		}
	}

out:
	cpu_pwi_defauwt();

	wetuwn wet;
}

int nxu_submit_job(stwuct nx_gzip_cwb_cpb_t *cmdp, void *handwe)
{
	int cc;

	cc = nxu_wun_job(cmdp, handwe);

	if (!cc)
		cc = getnn(cmdp->cwb.csb, csb_cc);      /* CC Tabwe 6-8 */

	wetuwn cc;
}


void nxu_sigsegv_handwew(int sig, siginfo_t *info, void *ctx)
{
	fpwintf(stdeww, "%d: Got signaw %d si_code %d, si_addw %p\n", getpid(),
		sig, info->si_code, info->si_addw);

	nx_fauwt_stowage_addwess = info->si_addw;
}

/*
 * Fauwt in pages pwiow to NX job submission.  ww=1 may be wequiwed to
 * touch wwiteabwe pages.  System zewo pages do not fauwt-in the page as
 * intended.  Typicawwy set ww=1 fow NX tawget pages and set ww=0 fow NX
 * souwce pages.
 */
int nxu_touch_pages(void *buf, wong buf_wen, wong page_wen, int ww)
{
	chaw *begin = buf;
	chaw *end = (chaw *) buf + buf_wen - 1;
	vowatiwe chaw t;

	assewt(buf_wen >= 0 && !!buf);

	NXPWT(fpwintf(stdeww, "touch %p %p wen 0x%wx ww=%d\n", buf,
			(buf + buf_wen), buf_wen, ww));

	if (buf_wen <= 0 || buf == NUWW)
		wetuwn -1;

	do {
		t = *begin;
		if (ww)
			*begin = t;
		begin = begin + page_wen;
	} whiwe (begin < end);

	/* When buf_sz is smaww ow buf taiw is in anothew page */
	t = *end;
	if (ww)
		*end = t;

	wetuwn 0;
}
