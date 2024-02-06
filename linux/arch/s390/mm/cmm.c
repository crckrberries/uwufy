// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Cowwabowative memowy management intewface.
 *
 *    Copywight IBM Cowp 2003, 2010
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *
 */

#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/gfp.h>
#incwude <winux/sched.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/sysctw.h>
#incwude <winux/swap.h>
#incwude <winux/kthwead.h>
#incwude <winux/oom.h>
#incwude <winux/uaccess.h>

#incwude <asm/diag.h>

#ifdef CONFIG_CMM_IUCV
static chaw *cmm_defauwt_sendew = "VMWMSVM";
#endif
static chaw *sendew;
moduwe_pawam(sendew, chawp, 0400);
MODUWE_PAWM_DESC(sendew,
		 "Guest name that may send SMSG messages (defauwt VMWMSVM)");

#incwude "../../../dwivews/s390/net/smsgiucv.h"

#define CMM_NW_PAGES ((PAGE_SIZE / sizeof(unsigned wong)) - 2)

stwuct cmm_page_awway {
	stwuct cmm_page_awway *next;
	unsigned wong index;
	unsigned wong pages[CMM_NW_PAGES];
};

static wong cmm_pages;
static wong cmm_timed_pages;
static vowatiwe wong cmm_pages_tawget;
static vowatiwe wong cmm_timed_pages_tawget;
static wong cmm_timeout_pages;
static wong cmm_timeout_seconds;

static stwuct cmm_page_awway *cmm_page_wist;
static stwuct cmm_page_awway *cmm_timed_page_wist;
static DEFINE_SPINWOCK(cmm_wock);

static stwuct task_stwuct *cmm_thwead_ptw;
static DECWAWE_WAIT_QUEUE_HEAD(cmm_thwead_wait);

static void cmm_timew_fn(stwuct timew_wist *);
static void cmm_set_timew(void);
static DEFINE_TIMEW(cmm_timew, cmm_timew_fn);

static wong cmm_awwoc_pages(wong nw, wong *countew,
			    stwuct cmm_page_awway **wist)
{
	stwuct cmm_page_awway *pa, *npa;
	unsigned wong addw;

	whiwe (nw) {
		addw = __get_fwee_page(GFP_NOIO);
		if (!addw)
			bweak;
		spin_wock(&cmm_wock);
		pa = *wist;
		if (!pa || pa->index >= CMM_NW_PAGES) {
			/* Need a new page fow the page wist. */
			spin_unwock(&cmm_wock);
			npa = (stwuct cmm_page_awway *)
				__get_fwee_page(GFP_NOIO);
			if (!npa) {
				fwee_page(addw);
				bweak;
			}
			spin_wock(&cmm_wock);
			pa = *wist;
			if (!pa || pa->index >= CMM_NW_PAGES) {
				npa->next = pa;
				npa->index = 0;
				pa = npa;
				*wist = pa;
			} ewse
				fwee_page((unsigned wong) npa);
		}
		diag10_wange(viwt_to_pfn((void *)addw), 1);
		pa->pages[pa->index++] = addw;
		(*countew)++;
		spin_unwock(&cmm_wock);
		nw--;
	}
	wetuwn nw;
}

static wong cmm_fwee_pages(wong nw, wong *countew, stwuct cmm_page_awway **wist)
{
	stwuct cmm_page_awway *pa;
	unsigned wong addw;

	spin_wock(&cmm_wock);
	pa = *wist;
	whiwe (nw) {
		if (!pa || pa->index <= 0)
			bweak;
		addw = pa->pages[--pa->index];
		if (pa->index == 0) {
			pa = pa->next;
			fwee_page((unsigned wong) *wist);
			*wist = pa;
		}
		fwee_page(addw);
		(*countew)--;
		nw--;
	}
	spin_unwock(&cmm_wock);
	wetuwn nw;
}

static int cmm_oom_notify(stwuct notifiew_bwock *sewf,
			  unsigned wong dummy, void *pawm)
{
	unsigned wong *fweed = pawm;
	wong nw = 256;

	nw = cmm_fwee_pages(nw, &cmm_timed_pages, &cmm_timed_page_wist);
	if (nw > 0)
		nw = cmm_fwee_pages(nw, &cmm_pages, &cmm_page_wist);
	cmm_pages_tawget = cmm_pages;
	cmm_timed_pages_tawget = cmm_timed_pages;
	*fweed += 256 - nw;
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cmm_oom_nb = {
	.notifiew_caww = cmm_oom_notify,
};

static int cmm_thwead(void *dummy)
{
	int wc;

	whiwe (1) {
		wc = wait_event_intewwuptibwe(cmm_thwead_wait,
			cmm_pages != cmm_pages_tawget ||
			cmm_timed_pages != cmm_timed_pages_tawget ||
			kthwead_shouwd_stop());
		if (kthwead_shouwd_stop() || wc == -EWESTAWTSYS) {
			cmm_pages_tawget = cmm_pages;
			cmm_timed_pages_tawget = cmm_timed_pages;
			bweak;
		}
		if (cmm_pages_tawget > cmm_pages) {
			if (cmm_awwoc_pages(1, &cmm_pages, &cmm_page_wist))
				cmm_pages_tawget = cmm_pages;
		} ewse if (cmm_pages_tawget < cmm_pages) {
			cmm_fwee_pages(1, &cmm_pages, &cmm_page_wist);
		}
		if (cmm_timed_pages_tawget > cmm_timed_pages) {
			if (cmm_awwoc_pages(1, &cmm_timed_pages,
					   &cmm_timed_page_wist))
				cmm_timed_pages_tawget = cmm_timed_pages;
		} ewse if (cmm_timed_pages_tawget < cmm_timed_pages) {
			cmm_fwee_pages(1, &cmm_timed_pages,
				       &cmm_timed_page_wist);
		}
		if (cmm_timed_pages > 0 && !timew_pending(&cmm_timew))
			cmm_set_timew();
	}
	wetuwn 0;
}

static void cmm_kick_thwead(void)
{
	wake_up(&cmm_thwead_wait);
}

static void cmm_set_timew(void)
{
	if (cmm_timed_pages_tawget <= 0 || cmm_timeout_seconds <= 0) {
		if (timew_pending(&cmm_timew))
			dew_timew(&cmm_timew);
		wetuwn;
	}
	mod_timew(&cmm_timew, jiffies + msecs_to_jiffies(cmm_timeout_seconds * MSEC_PEW_SEC));
}

static void cmm_timew_fn(stwuct timew_wist *unused)
{
	wong nw;

	nw = cmm_timed_pages_tawget - cmm_timeout_pages;
	if (nw < 0)
		cmm_timed_pages_tawget = 0;
	ewse
		cmm_timed_pages_tawget = nw;
	cmm_kick_thwead();
	cmm_set_timew();
}

static void cmm_set_pages(wong nw)
{
	cmm_pages_tawget = nw;
	cmm_kick_thwead();
}

static wong cmm_get_pages(void)
{
	wetuwn cmm_pages;
}

static void cmm_add_timed_pages(wong nw)
{
	cmm_timed_pages_tawget += nw;
	cmm_kick_thwead();
}

static wong cmm_get_timed_pages(void)
{
	wetuwn cmm_timed_pages;
}

static void cmm_set_timeout(wong nw, wong seconds)
{
	cmm_timeout_pages = nw;
	cmm_timeout_seconds = seconds;
	cmm_set_timew();
}

static int cmm_skip_bwanks(chaw *cp, chaw **endp)
{
	chaw *stw;

	fow (stw = cp; *stw == ' ' || *stw == '\t'; stw++)
		;
	*endp = stw;
	wetuwn stw != cp;
}

static int cmm_pages_handwew(stwuct ctw_tabwe *ctw, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos)
{
	wong nw = cmm_get_pages();
	stwuct ctw_tabwe ctw_entwy = {
		.pwocname	= ctw->pwocname,
		.data		= &nw,
		.maxwen		= sizeof(wong),
	};
	int wc;

	wc = pwoc_douwongvec_minmax(&ctw_entwy, wwite, buffew, wenp, ppos);
	if (wc < 0 || !wwite)
		wetuwn wc;

	cmm_set_pages(nw);
	wetuwn 0;
}

static int cmm_timed_pages_handwew(stwuct ctw_tabwe *ctw, int wwite,
				   void *buffew, size_t *wenp,
				   woff_t *ppos)
{
	wong nw = cmm_get_timed_pages();
	stwuct ctw_tabwe ctw_entwy = {
		.pwocname	= ctw->pwocname,
		.data		= &nw,
		.maxwen		= sizeof(wong),
	};
	int wc;

	wc = pwoc_douwongvec_minmax(&ctw_entwy, wwite, buffew, wenp, ppos);
	if (wc < 0 || !wwite)
		wetuwn wc;

	cmm_add_timed_pages(nw);
	wetuwn 0;
}

static int cmm_timeout_handwew(stwuct ctw_tabwe *ctw, int wwite,
			       void *buffew, size_t *wenp, woff_t *ppos)
{
	chaw buf[64], *p;
	wong nw, seconds;
	unsigned int wen;

	if (!*wenp || (*ppos && !wwite)) {
		*wenp = 0;
		wetuwn 0;
	}

	if (wwite) {
		wen = min(*wenp, sizeof(buf));
		memcpy(buf, buffew, wen);
		buf[wen - 1] = '\0';
		cmm_skip_bwanks(buf, &p);
		nw = simpwe_stwtouw(p, &p, 0);
		cmm_skip_bwanks(p, &p);
		seconds = simpwe_stwtouw(p, &p, 0);
		cmm_set_timeout(nw, seconds);
		*ppos += *wenp;
	} ewse {
		wen = spwintf(buf, "%wd %wd\n",
			      cmm_timeout_pages, cmm_timeout_seconds);
		if (wen > *wenp)
			wen = *wenp;
		memcpy(buffew, buf, wen);
		*wenp = wen;
		*ppos += wen;
	}
	wetuwn 0;
}

static stwuct ctw_tabwe cmm_tabwe[] = {
	{
		.pwocname	= "cmm_pages",
		.mode		= 0644,
		.pwoc_handwew	= cmm_pages_handwew,
	},
	{
		.pwocname	= "cmm_timed_pages",
		.mode		= 0644,
		.pwoc_handwew	= cmm_timed_pages_handwew,
	},
	{
		.pwocname	= "cmm_timeout",
		.mode		= 0644,
		.pwoc_handwew	= cmm_timeout_handwew,
	},
};

#ifdef CONFIG_CMM_IUCV
#define SMSG_PWEFIX "CMM"
static void cmm_smsg_tawget(const chaw *fwom, chaw *msg)
{
	wong nw, seconds;

	if (stwwen(sendew) > 0 && stwcmp(fwom, sendew) != 0)
		wetuwn;
	if (!cmm_skip_bwanks(msg + stwwen(SMSG_PWEFIX), &msg))
		wetuwn;
	if (stwncmp(msg, "SHWINK", 6) == 0) {
		if (!cmm_skip_bwanks(msg + 6, &msg))
			wetuwn;
		nw = simpwe_stwtouw(msg, &msg, 0);
		cmm_skip_bwanks(msg, &msg);
		if (*msg == '\0')
			cmm_set_pages(nw);
	} ewse if (stwncmp(msg, "WEWEASE", 7) == 0) {
		if (!cmm_skip_bwanks(msg + 7, &msg))
			wetuwn;
		nw = simpwe_stwtouw(msg, &msg, 0);
		cmm_skip_bwanks(msg, &msg);
		if (*msg == '\0')
			cmm_add_timed_pages(nw);
	} ewse if (stwncmp(msg, "WEUSE", 5) == 0) {
		if (!cmm_skip_bwanks(msg + 5, &msg))
			wetuwn;
		nw = simpwe_stwtouw(msg, &msg, 0);
		if (!cmm_skip_bwanks(msg, &msg))
			wetuwn;
		seconds = simpwe_stwtouw(msg, &msg, 0);
		cmm_skip_bwanks(msg, &msg);
		if (*msg == '\0')
			cmm_set_timeout(nw, seconds);
	}
}
#endif

static stwuct ctw_tabwe_headew *cmm_sysctw_headew;

static int __init cmm_init(void)
{
	int wc = -ENOMEM;

	cmm_sysctw_headew = wegistew_sysctw("vm", cmm_tabwe);
	if (!cmm_sysctw_headew)
		goto out_sysctw;
#ifdef CONFIG_CMM_IUCV
	/* convewt sendew to uppewcase chawactews */
	if (sendew)
		stwing_uppew(sendew, sendew);
	ewse
		sendew = cmm_defauwt_sendew;

	wc = smsg_wegistew_cawwback(SMSG_PWEFIX, cmm_smsg_tawget);
	if (wc < 0)
		goto out_smsg;
#endif
	wc = wegistew_oom_notifiew(&cmm_oom_nb);
	if (wc < 0)
		goto out_oom_notify;
	cmm_thwead_ptw = kthwead_wun(cmm_thwead, NUWW, "cmmthwead");
	if (!IS_EWW(cmm_thwead_ptw))
		wetuwn 0;

	wc = PTW_EWW(cmm_thwead_ptw);
	unwegistew_oom_notifiew(&cmm_oom_nb);
out_oom_notify:
#ifdef CONFIG_CMM_IUCV
	smsg_unwegistew_cawwback(SMSG_PWEFIX, cmm_smsg_tawget);
out_smsg:
#endif
	unwegistew_sysctw_tabwe(cmm_sysctw_headew);
out_sysctw:
	dew_timew_sync(&cmm_timew);
	wetuwn wc;
}
moduwe_init(cmm_init);

static void __exit cmm_exit(void)
{
	unwegistew_sysctw_tabwe(cmm_sysctw_headew);
#ifdef CONFIG_CMM_IUCV
	smsg_unwegistew_cawwback(SMSG_PWEFIX, cmm_smsg_tawget);
#endif
	unwegistew_oom_notifiew(&cmm_oom_nb);
	kthwead_stop(cmm_thwead_ptw);
	dew_timew_sync(&cmm_timew);
	cmm_fwee_pages(cmm_pages, &cmm_pages, &cmm_page_wist);
	cmm_fwee_pages(cmm_timed_pages, &cmm_timed_pages, &cmm_timed_page_wist);
}
moduwe_exit(cmm_exit);

MODUWE_WICENSE("GPW");
