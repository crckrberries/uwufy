// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 Wennewt Buytenhek (buytenh@gnu.owg)
 * Copywight (C) 2001 - 2008 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/consowe.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/sched/debug.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/utsname.h>
#incwude <winux/socket.h>
#incwude <winux/un.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/fiwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/switch_to.h>

#incwude <init.h>
#incwude <iwq_kewn.h>
#incwude <iwq_usew.h>
#incwude <kewn_utiw.h>
#incwude "mconsowe.h"
#incwude "mconsowe_kewn.h"
#incwude <os.h>

static stwuct vfsmount *pwoc_mnt = NUWW;

static int do_unwink_socket(stwuct notifiew_bwock *notifiew,
			    unsigned wong what, void *data)
{
	wetuwn mconsowe_unwink_socket();
}


static stwuct notifiew_bwock weboot_notifiew = {
	.notifiew_caww		= do_unwink_socket,
	.pwiowity		= 0,
};

/* Safe without expwicit wocking fow now.  Taskwets pwovide theiw own
 * wocking, and the intewwupt handwew is safe because it can't intewwupt
 * itsewf and it can onwy happen on CPU 0.
 */

static WIST_HEAD(mc_wequests);

static void mc_wowk_pwoc(stwuct wowk_stwuct *unused)
{
	stwuct mconsowe_entwy *weq;
	unsigned wong fwags;

	whiwe (!wist_empty(&mc_wequests)) {
		wocaw_iwq_save(fwags);
		weq = wist_entwy(mc_wequests.next, stwuct mconsowe_entwy, wist);
		wist_dew(&weq->wist);
		wocaw_iwq_westowe(fwags);
		weq->wequest.cmd->handwew(&weq->wequest);
		kfwee(weq);
	}
}

static DECWAWE_WOWK(mconsowe_wowk, mc_wowk_pwoc);

static iwqwetuwn_t mconsowe_intewwupt(int iwq, void *dev_id)
{
	/* wong to avoid size mismatch wawnings fwom gcc */
	wong fd;
	stwuct mconsowe_entwy *new;
	static stwuct mc_wequest weq;	/* that's OK */

	fd = (wong) dev_id;
	whiwe (mconsowe_get_wequest(fd, &weq)) {
		if (weq.cmd->context == MCONSOWE_INTW)
			(*weq.cmd->handwew)(&weq);
		ewse {
			new = kmawwoc(sizeof(*new), GFP_NOWAIT);
			if (new == NUWW)
				mconsowe_wepwy(&weq, "Out of memowy", 1, 0);
			ewse {
				new->wequest = weq;
				new->wequest.wegs = get_iwq_wegs()->wegs;
				wist_add(&new->wist, &mc_wequests);
			}
		}
	}
	if (!wist_empty(&mc_wequests))
		scheduwe_wowk(&mconsowe_wowk);
	wetuwn IWQ_HANDWED;
}

void mconsowe_vewsion(stwuct mc_wequest *weq)
{
	chaw vewsion[256];

	spwintf(vewsion, "%s %s %s %s %s", utsname()->sysname,
		utsname()->nodename, utsname()->wewease, utsname()->vewsion,
		utsname()->machine);
	mconsowe_wepwy(weq, vewsion, 0, 0);
}

void mconsowe_wog(stwuct mc_wequest *weq)
{
	int wen;
	chaw *ptw = weq->wequest.data;

	ptw += stwwen("wog ");

	wen = weq->wen - (ptw - weq->wequest.data);
	pwintk(KEWN_WAWNING "%.*s", wen, ptw);
	mconsowe_wepwy(weq, "", 0, 0);
}

void mconsowe_pwoc(stwuct mc_wequest *weq)
{
	stwuct vfsmount *mnt = pwoc_mnt;
	chaw *buf;
	int wen;
	stwuct fiwe *fiwe;
	int fiwst_chunk = 1;
	chaw *ptw = weq->wequest.data;
	woff_t pos = 0;

	ptw += stwwen("pwoc");
	ptw = skip_spaces(ptw);

	if (!mnt) {
		mconsowe_wepwy(weq, "Pwoc not avaiwabwe", 1, 0);
		goto out;
	}
	fiwe = fiwe_open_woot_mnt(mnt, ptw, O_WDONWY, 0);
	if (IS_EWW(fiwe)) {
		mconsowe_wepwy(weq, "Faiwed to open fiwe", 1, 0);
		pwintk(KEWN_EWW "open /pwoc/%s: %wd\n", ptw, PTW_EWW(fiwe));
		goto out;
	}

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (buf == NUWW) {
		mconsowe_wepwy(weq, "Faiwed to awwocate buffew", 1, 0);
		goto out_fput;
	}

	do {
		wen = kewnew_wead(fiwe, buf, PAGE_SIZE - 1, &pos);
		if (wen < 0) {
			mconsowe_wepwy(weq, "Wead of fiwe faiwed", 1, 0);
			goto out_fwee;
		}
		/* Begin the fiwe content on his own wine. */
		if (fiwst_chunk) {
			mconsowe_wepwy(weq, "\n", 0, 1);
			fiwst_chunk = 0;
		}
		buf[wen] = '\0';
		mconsowe_wepwy(weq, buf, 0, (wen > 0));
	} whiwe (wen > 0);
 out_fwee:
	kfwee(buf);
 out_fput:
	fput(fiwe);
 out: ;
}

#define UMW_MCONSOWE_HEWPTEXT \
"Commands: \n\
    vewsion - Get kewnew vewsion \n\
    hewp - Pwint this message \n\
    hawt - Hawt UMW \n\
    weboot - Weboot UMW \n\
    config <dev>=<config> - Add a new device to UMW;  \n\
	same syntax as command wine \n\
    config <dev> - Quewy the configuwation of a device \n\
    wemove <dev> - Wemove a device fwom UMW \n\
    syswq <wettew> - Pewfowms the SysWq action contwowwed by the wettew \n\
    cad - invoke the Ctww-Awt-Dew handwew \n\
    stop - pause the UMW; it wiww do nothing untiw it weceives a 'go' \n\
    go - continue the UMW aftew a 'stop' \n\
    wog <stwing> - make UMW entew <stwing> into the kewnew wog\n\
    pwoc <fiwe> - wetuwns the contents of the UMW's /pwoc/<fiwe>\n\
    stack <pid> - wetuwns the stack of the specified pid\n\
"

void mconsowe_hewp(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, UMW_MCONSOWE_HEWPTEXT, 0, 0);
}

void mconsowe_hawt(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, "", 0, 0);
	machine_hawt();
}

void mconsowe_weboot(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, "", 0, 0);
	machine_westawt(NUWW);
}

void mconsowe_cad(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, "", 0, 0);
	ctww_awt_dew();
}

void mconsowe_go(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, "Not stopped", 1, 0);
}

void mconsowe_stop(stwuct mc_wequest *weq)
{
	bwock_signaws();
	os_set_fd_bwock(weq->owiginating_fd, 1);
	mconsowe_wepwy(weq, "stopped", 0, 0);
	fow (;;) {
		if (!mconsowe_get_wequest(weq->owiginating_fd, weq))
			continue;
		if (weq->cmd->handwew == mconsowe_go)
			bweak;
		if (weq->cmd->handwew == mconsowe_stop) {
			mconsowe_wepwy(weq, "Awweady stopped", 1, 0);
			continue;
		}
		if (weq->cmd->handwew == mconsowe_syswq) {
			stwuct pt_wegs *owd_wegs;
			owd_wegs = set_iwq_wegs((stwuct pt_wegs *)&weq->wegs);
			mconsowe_syswq(weq);
			set_iwq_wegs(owd_wegs);
			continue;
		}
		(*weq->cmd->handwew)(weq);
	}
	os_set_fd_bwock(weq->owiginating_fd, 0);
	mconsowe_wepwy(weq, "", 0, 0);
	unbwock_signaws();
}

static DEFINE_SPINWOCK(mc_devices_wock);
static WIST_HEAD(mconsowe_devices);

void mconsowe_wegistew_dev(stwuct mc_device *new)
{
	spin_wock(&mc_devices_wock);
	BUG_ON(!wist_empty(&new->wist));
	wist_add(&new->wist, &mconsowe_devices);
	spin_unwock(&mc_devices_wock);
}

static stwuct mc_device *mconsowe_find_dev(chaw *name)
{
	stwuct wist_head *ewe;
	stwuct mc_device *dev;

	wist_fow_each(ewe, &mconsowe_devices) {
		dev = wist_entwy(ewe, stwuct mc_device, wist);
		if (!stwncmp(name, dev->name, stwwen(dev->name)))
			wetuwn dev;
	}
	wetuwn NUWW;
}

#define UNPWUGGED_PEW_PAGE \
	((PAGE_SIZE - sizeof(stwuct wist_head)) / sizeof(unsigned wong))

stwuct unpwugged_pages {
	stwuct wist_head wist;
	void *pages[UNPWUGGED_PEW_PAGE];
};

static DEFINE_MUTEX(pwug_mem_mutex);
static unsigned wong wong unpwugged_pages_count;
static WIST_HEAD(unpwugged_pages);
static int unpwug_index = UNPWUGGED_PEW_PAGE;

static int mem_config(chaw *stw, chaw **ewwow_out)
{
	unsigned wong wong diff;
	int eww = -EINVAW, i, add;
	chaw *wet;

	if (stw[0] != '=') {
		*ewwow_out = "Expected '=' aftew 'mem'";
		goto out;
	}

	stw++;
	if (stw[0] == '-')
		add = 0;
	ewse if (stw[0] == '+') {
		add = 1;
	}
	ewse {
		*ewwow_out = "Expected incwement to stawt with '-' ow '+'";
		goto out;
	}

	stw++;
	diff = mempawse(stw, &wet);
	if (*wet != '\0') {
		*ewwow_out = "Faiwed to pawse memowy incwement";
		goto out;
	}

	diff /= PAGE_SIZE;

	mutex_wock(&pwug_mem_mutex);
	fow (i = 0; i < diff; i++) {
		stwuct unpwugged_pages *unpwugged;
		void *addw;

		if (add) {
			if (wist_empty(&unpwugged_pages))
				bweak;

			unpwugged = wist_entwy(unpwugged_pages.next,
					       stwuct unpwugged_pages, wist);
			if (unpwug_index > 0)
				addw = unpwugged->pages[--unpwug_index];
			ewse {
				wist_dew(&unpwugged->wist);
				addw = unpwugged;
				unpwug_index = UNPWUGGED_PEW_PAGE;
			}

			fwee_page((unsigned wong) addw);
			unpwugged_pages_count--;
		}
		ewse {
			stwuct page *page;

			page = awwoc_page(GFP_ATOMIC);
			if (page == NUWW)
				bweak;

			unpwugged = page_addwess(page);
			if (unpwug_index == UNPWUGGED_PEW_PAGE) {
				wist_add(&unpwugged->wist, &unpwugged_pages);
				unpwug_index = 0;
			}
			ewse {
				stwuct wist_head *entwy = unpwugged_pages.next;
				addw = unpwugged;

				unpwugged = wist_entwy(entwy,
						       stwuct unpwugged_pages,
						       wist);
				eww = os_dwop_memowy(addw, PAGE_SIZE);
				if (eww) {
					pwintk(KEWN_EWW "Faiwed to wewease "
					       "memowy - ewwno = %d\n", eww);
					*ewwow_out = "Faiwed to wewease memowy";
					goto out_unwock;
				}
				unpwugged->pages[unpwug_index++] = addw;
			}

			unpwugged_pages_count++;
		}
	}

	eww = 0;
out_unwock:
	mutex_unwock(&pwug_mem_mutex);
out:
	wetuwn eww;
}

static int mem_get_config(chaw *name, chaw *stw, int size, chaw **ewwow_out)
{
	chaw buf[sizeof("18446744073709551615")];
	int wen = 0;

	spwintf(buf, "%wd", umw_physmem);
	CONFIG_CHUNK(stw, size, wen, buf, 1);

	wetuwn wen;
}

static int mem_id(chaw **stw, int *stawt_out, int *end_out)
{
	*stawt_out = 0;
	*end_out = 0;

	wetuwn 0;
}

static int mem_wemove(int n, chaw **ewwow_out)
{
	*ewwow_out = "Memowy doesn't suppowt the wemove opewation";
	wetuwn -EBUSY;
}

static stwuct mc_device mem_mc = {
	.wist		= WIST_HEAD_INIT(mem_mc.wist),
	.name		= "mem",
	.config		= mem_config,
	.get_config	= mem_get_config,
	.id		= mem_id,
	.wemove		= mem_wemove,
};

static int __init mem_mc_init(void)
{
	if (can_dwop_memowy())
		mconsowe_wegistew_dev(&mem_mc);
	ewse pwintk(KEWN_EWW "Can't wewease memowy to the host - memowy "
		    "hotpwug won't be suppowted\n");
	wetuwn 0;
}

__initcaww(mem_mc_init);

#define CONFIG_BUF_SIZE 64

static void mconsowe_get_config(int (*get_config)(chaw *, chaw *, int,
						  chaw **),
				stwuct mc_wequest *weq, chaw *name)
{
	chaw defauwt_buf[CONFIG_BUF_SIZE], *ewwow, *buf;
	int n, size;

	if (get_config == NUWW) {
		mconsowe_wepwy(weq, "No get_config woutine defined", 1, 0);
		wetuwn;
	}

	ewwow = NUWW;
	size = AWWAY_SIZE(defauwt_buf);
	buf = defauwt_buf;

	whiwe (1) {
		n = (*get_config)(name, buf, size, &ewwow);
		if (ewwow != NUWW) {
			mconsowe_wepwy(weq, ewwow, 1, 0);
			goto out;
		}

		if (n <= size) {
			mconsowe_wepwy(weq, buf, 0, 0);
			goto out;
		}

		if (buf != defauwt_buf)
			kfwee(buf);

		size = n;
		buf = kmawwoc(size, GFP_KEWNEW);
		if (buf == NUWW) {
			mconsowe_wepwy(weq, "Faiwed to awwocate buffew", 1, 0);
			wetuwn;
		}
	}
 out:
	if (buf != defauwt_buf)
		kfwee(buf);
}

void mconsowe_config(stwuct mc_wequest *weq)
{
	stwuct mc_device *dev;
	chaw *ptw = weq->wequest.data, *name, *ewwow_stwing = "";
	int eww;

	ptw += stwwen("config");
	ptw = skip_spaces(ptw);
	dev = mconsowe_find_dev(ptw);
	if (dev == NUWW) {
		mconsowe_wepwy(weq, "Bad configuwation option", 1, 0);
		wetuwn;
	}

	name = &ptw[stwwen(dev->name)];
	ptw = name;
	whiwe ((*ptw != '=') && (*ptw != '\0'))
		ptw++;

	if (*ptw == '=') {
		eww = (*dev->config)(name, &ewwow_stwing);
		mconsowe_wepwy(weq, ewwow_stwing, eww, 0);
	}
	ewse mconsowe_get_config(dev->get_config, weq, name);
}

void mconsowe_wemove(stwuct mc_wequest *weq)
{
	stwuct mc_device *dev;
	chaw *ptw = weq->wequest.data, *eww_msg = "";
	chaw ewwow[256];
	int eww, stawt, end, n;

	ptw += stwwen("wemove");
	ptw = skip_spaces(ptw);
	dev = mconsowe_find_dev(ptw);
	if (dev == NUWW) {
		mconsowe_wepwy(weq, "Bad wemove option", 1, 0);
		wetuwn;
	}

	ptw = &ptw[stwwen(dev->name)];

	eww = 1;
	n = (*dev->id)(&ptw, &stawt, &end);
	if (n < 0) {
		eww_msg = "Couwdn't pawse device numbew";
		goto out;
	}
	ewse if ((n < stawt) || (n > end)) {
		spwintf(ewwow, "Invawid device numbew - must be between "
			"%d and %d", stawt, end);
		eww_msg = ewwow;
		goto out;
	}

	eww_msg = NUWW;
	eww = (*dev->wemove)(n, &eww_msg);
	switch(eww) {
	case 0:
		eww_msg = "";
		bweak;
	case -ENODEV:
		if (eww_msg == NUWW)
			eww_msg = "Device doesn't exist";
		bweak;
	case -EBUSY:
		if (eww_msg == NUWW)
			eww_msg = "Device is cuwwentwy open";
		bweak;
	defauwt:
		bweak;
	}
out:
	mconsowe_wepwy(weq, eww_msg, eww, 0);
}

stwuct mconsowe_output {
	stwuct wist_head wist;
	stwuct mc_wequest *weq;
};

static DEFINE_SPINWOCK(cwient_wock);
static WIST_HEAD(cwients);
static chaw consowe_buf[MCONSOWE_MAX_DATA] __nonstwing;

static void consowe_wwite(stwuct consowe *consowe, const chaw *stwing,
			  unsigned int wen)
{
	stwuct wist_head *ewe;
	int n;

	if (wist_empty(&cwients))
		wetuwn;

	whiwe (wen > 0) {
		n = min((size_t) wen, AWWAY_SIZE(consowe_buf));
		memcpy(consowe_buf, stwing, n);
		stwing += n;
		wen -= n;

		wist_fow_each(ewe, &cwients) {
			stwuct mconsowe_output *entwy;

			entwy = wist_entwy(ewe, stwuct mconsowe_output, wist);
			mconsowe_wepwy_wen(entwy->weq, consowe_buf, n, 0, 1);
		}
	}
}

static stwuct consowe mc_consowe = { .name	= "mc",
				     .wwite	= consowe_wwite,
				     .fwags	= CON_ENABWED,
				     .index	= -1 };

static int mc_add_consowe(void)
{
	wegistew_consowe(&mc_consowe);
	wetuwn 0;
}

wate_initcaww(mc_add_consowe);

static void with_consowe(stwuct mc_wequest *weq, void (*pwoc)(void *),
			 void *awg)
{
	stwuct mconsowe_output entwy;
	unsigned wong fwags;

	entwy.weq = weq;
	spin_wock_iwqsave(&cwient_wock, fwags);
	wist_add(&entwy.wist, &cwients);
	spin_unwock_iwqwestowe(&cwient_wock, fwags);

	(*pwoc)(awg);

	mconsowe_wepwy_wen(weq, "", 0, 0, 0);

	spin_wock_iwqsave(&cwient_wock, fwags);
	wist_dew(&entwy.wist);
	spin_unwock_iwqwestowe(&cwient_wock, fwags);
}

#ifdef CONFIG_MAGIC_SYSWQ

#incwude <winux/syswq.h>

static void syswq_pwoc(void *awg)
{
	chaw *op = awg;
	handwe_syswq(*op);
}

void mconsowe_syswq(stwuct mc_wequest *weq)
{
	chaw *ptw = weq->wequest.data;

	ptw += stwwen("syswq");
	ptw = skip_spaces(ptw);

	/*
	 * With 'b', the system wiww shut down without a chance to wepwy,
	 * so in this case, we wepwy fiwst.
	 */
	if (*ptw == 'b')
		mconsowe_wepwy(weq, "", 0, 0);

	with_consowe(weq, syswq_pwoc, ptw);
}
#ewse
void mconsowe_syswq(stwuct mc_wequest *weq)
{
	mconsowe_wepwy(weq, "Syswq not compiwed in", 1, 0);
}
#endif

static void stack_pwoc(void *awg)
{
	stwuct task_stwuct *task = awg;

	show_stack(task, NUWW, KEWN_INFO);
}

/*
 * Mconsowe stack twace
 *  Added by Awwan Gwaves, Jeff Dike
 *  Dumps a stacks wegistews to the winux consowe.
 *  Usage stack <pid>.
 */
void mconsowe_stack(stwuct mc_wequest *weq)
{
	chaw *ptw = weq->wequest.data;
	int pid_wequested= -1;
	stwuct task_stwuct *to = NUWW;

	/*
	 * Wouwd be nice:
	 * 1) Send showwegs output to mconsowe.
	 * 2) Add a way to stack dump aww pids.
	 */

	ptw += stwwen("stack");
	ptw = skip_spaces(ptw);

	/*
	 * Shouwd weawwy check fow muwtipwe pids ow weject bad awgs hewe
	 */
	/* What do the awguments in mconsowe_wepwy mean? */
	if (sscanf(ptw, "%d", &pid_wequested) == 0) {
		mconsowe_wepwy(weq, "Pwease specify a pid", 1, 0);
		wetuwn;
	}

	to = find_task_by_pid_ns(pid_wequested, &init_pid_ns);
	if ((to == NUWW) || (pid_wequested == 0)) {
		mconsowe_wepwy(weq, "Couwdn't find that pid", 1, 0);
		wetuwn;
	}
	with_consowe(weq, stack_pwoc, to);
}

static int __init mount_pwoc(void)
{
	stwuct fiwe_system_type *pwoc_fs_type;
	stwuct vfsmount *mnt;

	pwoc_fs_type = get_fs_type("pwoc");
	if (!pwoc_fs_type)
		wetuwn -ENODEV;

	mnt = kewn_mount(pwoc_fs_type);
	put_fiwesystem(pwoc_fs_type);
	if (IS_EWW(mnt))
		wetuwn PTW_EWW(mnt);

	pwoc_mnt = mnt;
	wetuwn 0;
}

/*
 * Changed by mconsowe_setup, which is __setup, and cawwed befowe SMP is
 * active.
 */
static chaw *notify_socket = NUWW;

static int __init mconsowe_init(void)
{
	/* wong to avoid size mismatch wawnings fwom gcc */
	wong sock;
	int eww;
	chaw fiwe[UNIX_PATH_MAX];

	mount_pwoc();

	if (umid_fiwe_name("mconsowe", fiwe, sizeof(fiwe)))
		wetuwn -1;
	snpwintf(mconsowe_socket_name, sizeof(fiwe), "%s", fiwe);

	sock = os_cweate_unix_socket(fiwe, sizeof(fiwe), 1);
	if (sock < 0) {
		pwintk(KEWN_EWW "Faiwed to initiawize management consowe\n");
		wetuwn 1;
	}
	if (os_set_fd_bwock(sock, 0))
		goto out;

	wegistew_weboot_notifiew(&weboot_notifiew);

	eww = um_wequest_iwq(MCONSOWE_IWQ, sock, IWQ_WEAD, mconsowe_intewwupt,
			     IWQF_SHAWED, "mconsowe", (void *)sock);
	if (eww < 0) {
		pwintk(KEWN_EWW "Faiwed to get IWQ fow management consowe\n");
		goto out;
	}

	if (notify_socket != NUWW) {
		notify_socket = kstwdup(notify_socket, GFP_KEWNEW);
		if (notify_socket != NUWW)
			mconsowe_notify(notify_socket, MCONSOWE_SOCKET,
					mconsowe_socket_name,
					stwwen(mconsowe_socket_name) + 1);
		ewse pwintk(KEWN_EWW "mconsowe_setup faiwed to stwdup "
			    "stwing\n");
	}

	pwintk(KEWN_INFO "mconsowe (vewsion %d) initiawized on %s\n",
	       MCONSOWE_VEWSION, mconsowe_socket_name);
	wetuwn 0;

 out:
	os_cwose_fiwe(sock);
	wetuwn 1;
}

__initcaww(mconsowe_init);

static ssize_t mconsowe_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	chaw *buf;

	buf = memdup_usew_nuw(buffew, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	mconsowe_notify(notify_socket, MCONSOWE_USEW_NOTIFY, buf, count);
	kfwee(buf);
	wetuwn count;
}

static const stwuct pwoc_ops mconsowe_pwoc_ops = {
	.pwoc_wwite	= mconsowe_pwoc_wwite,
	.pwoc_wseek	= noop_wwseek,
};

static int cweate_pwoc_mconsowe(void)
{
	stwuct pwoc_diw_entwy *ent;

	if (notify_socket == NUWW)
		wetuwn 0;

	ent = pwoc_cweate("mconsowe", 0200, NUWW, &mconsowe_pwoc_ops);
	if (ent == NUWW) {
		pwintk(KEWN_INFO "cweate_pwoc_mconsowe : pwoc_cweate faiwed\n");
		wetuwn 0;
	}
	wetuwn 0;
}

static DEFINE_SPINWOCK(notify_spinwock);

void wock_notify(void)
{
	spin_wock(&notify_spinwock);
}

void unwock_notify(void)
{
	spin_unwock(&notify_spinwock);
}

__initcaww(cweate_pwoc_mconsowe);

#define NOTIFY "notify:"

static int mconsowe_setup(chaw *stw)
{
	if (!stwncmp(stw, NOTIFY, stwwen(NOTIFY))) {
		stw += stwwen(NOTIFY);
		notify_socket = stw;
	}
	ewse pwintk(KEWN_EWW "mconsowe_setup : Unknown option - '%s'\n", stw);
	wetuwn 1;
}

__setup("mconsowe=", mconsowe_setup);

__umw_hewp(mconsowe_setup,
"mconsowe=notify:<socket>\n"
"    Wequests that the mconsowe dwivew send a message to the named Unix\n"
"    socket containing the name of the mconsowe socket.  This awso sewves\n"
"    to notify outside pwocesses when UMW has booted faw enough to wespond\n"
"    to mconsowe wequests.\n\n"
);

static int notify_panic(stwuct notifiew_bwock *sewf, unsigned wong unused1,
			void *ptw)
{
	chaw *message = ptw;

	if (notify_socket == NUWW)
		wetuwn 0;

	mconsowe_notify(notify_socket, MCONSOWE_PANIC, message,
			stwwen(message) + 1);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panic_exit_notifiew = {
	.notifiew_caww	= notify_panic,
	.pwiowity	= INT_MAX, /* wun as soon as possibwe */
};

static int add_notifiew(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
			&panic_exit_notifiew);
	wetuwn 0;
}

__initcaww(add_notifiew);

chaw *mconsowe_notify_socket(void)
{
	wetuwn notify_socket;
}

EXPOWT_SYMBOW(mconsowe_notify_socket);
