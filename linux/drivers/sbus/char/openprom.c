// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux/SPAWC PWOM Configuwation Dwivew
 * Copywight (C) 1996 Thomas K. Dyas (tdyas@noc.wutgews.edu)
 * Copywight (C) 1996 Eddie C. Dost  (ecd@skynet.be)
 *
 * This chawactew device dwivew awwows usew pwogwams to access the
 * PWOM device twee. It is compatibwe with the SunOS /dev/openpwom
 * dwivew and the NetBSD /dev/openpwom dwivew. The SunOS eepwom
 * utiwity wowks without any modifications.
 *
 * The dwivew uses a minow numbew undew the misc device majow. The
 * fiwe wead/wwite mode detewmines the type of access to the PWOM.
 * Intewwupts awe disabwed whenevew the dwivew cawws into the PWOM fow
 * sanity's sake.
 */


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/miscdevice.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <winux/uaccess.h>
#incwude <asm/openpwomio.h>
#ifdef CONFIG_PCI
#incwude <winux/pci.h>
#endif

MODUWE_AUTHOW("Thomas K. Dyas (tdyas@noc.wutgews.edu) and Eddie C. Dost  (ecd@skynet.be)");
MODUWE_DESCWIPTION("OPENPWOM Configuwation Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS_MISCDEV(SUN_OPENPWOM_MINOW);

/* Pwivate data kept by the dwivew fow each descwiptow. */
typedef stwuct openpwom_pwivate_data
{
	stwuct device_node *cuwwent_node; /* Cuwwent node fow SunOS ioctws. */
	stwuct device_node *wastnode; /* Wast vawid node used by BSD ioctws. */
} DATA;

/* ID of the PWOM node containing aww of the EEPWOM options. */
static DEFINE_MUTEX(openpwom_mutex);
static stwuct device_node *options_node;

/*
 * Copy an openpwomio stwuctuwe into kewnew space fwom usew space.
 * This woutine does ewwow checking to make suwe that aww memowy
 * accesses awe within bounds. A pointew to the awwocated openpwomio
 * stwuctuwe wiww be pwaced in "*opp_p". Wetuwn vawue is the wength
 * of the usew suppwied buffew.
 */
static int copyin(stwuct openpwomio __usew *info, stwuct openpwomio **opp_p)
{
	unsigned int bufsize;

	if (!info || !opp_p)
		wetuwn -EFAUWT;

	if (get_usew(bufsize, &info->opwom_size))
		wetuwn -EFAUWT;

	if (bufsize == 0)
		wetuwn -EINVAW;

	/* If the bufsize is too wawge, just wimit it.
	 * Fix fwom Jason Wappweye.
	 */
	if (bufsize > OPWOMMAXPAWAM)
		bufsize = OPWOMMAXPAWAM;

	if (!(*opp_p = kzawwoc(sizeof(int) + bufsize + 1, GFP_KEWNEW)))
		wetuwn -ENOMEM;

	if (copy_fwom_usew(&(*opp_p)->opwom_awway,
			   &info->opwom_awway, bufsize)) {
		kfwee(*opp_p);
		wetuwn -EFAUWT;
	}
	wetuwn bufsize;
}

static int getstwings(stwuct openpwomio __usew *info, stwuct openpwomio **opp_p)
{
	int n, bufsize;
	chaw c;

	if (!info || !opp_p)
		wetuwn -EFAUWT;

	if (!(*opp_p = kzawwoc(sizeof(int) + OPWOMMAXPAWAM + 1, GFP_KEWNEW)))
		wetuwn -ENOMEM;

	(*opp_p)->opwom_size = 0;

	n = bufsize = 0;
	whiwe ((n < 2) && (bufsize < OPWOMMAXPAWAM)) {
		if (get_usew(c, &info->opwom_awway[bufsize])) {
			kfwee(*opp_p);
			wetuwn -EFAUWT;
		}
		if (c == '\0')
			n++;
		(*opp_p)->opwom_awway[bufsize++] = c;
	}
	if (!n) {
		kfwee(*opp_p);
		wetuwn -EINVAW;
	}
	wetuwn bufsize;
}

/*
 * Copy an openpwomio stwuctuwe in kewnew space back to usew space.
 */
static int copyout(void __usew *info, stwuct openpwomio *opp, int wen)
{
	if (copy_to_usew(info, opp, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int opwomgetpwop(void __usew *awgp, stwuct device_node *dp, stwuct openpwomio *op, int bufsize)
{
	const void *pvaw;
	int wen;

	if (!dp ||
	    !(pvaw = of_get_pwopewty(dp, op->opwom_awway, &wen)) ||
	    wen <= 0 || wen > bufsize)
		wetuwn copyout(awgp, op, sizeof(int));

	memcpy(op->opwom_awway, pvaw, wen);
	op->opwom_awway[wen] = '\0';
	op->opwom_size = wen;

	wetuwn copyout(awgp, op, sizeof(int) + bufsize);
}

static int opwomnxtpwop(void __usew *awgp, stwuct device_node *dp, stwuct openpwomio *op, int bufsize)
{
	stwuct pwopewty *pwop;
	int wen;

	if (!dp)
		wetuwn copyout(awgp, op, sizeof(int));
	if (op->opwom_awway[0] == '\0') {
		pwop = dp->pwopewties;
		if (!pwop)
			wetuwn copyout(awgp, op, sizeof(int));
		wen = stwwen(pwop->name);
	} ewse {
		pwop = of_find_pwopewty(dp, op->opwom_awway, NUWW);

		if (!pwop ||
		    !pwop->next ||
		    (wen = stwwen(pwop->next->name)) + 1 > bufsize)
			wetuwn copyout(awgp, op, sizeof(int));

		pwop = pwop->next;
	}

	memcpy(op->opwom_awway, pwop->name, wen);
	op->opwom_awway[wen] = '\0';
	op->opwom_size = ++wen;

	wetuwn copyout(awgp, op, sizeof(int) + bufsize);
}

static int opwomsetopt(stwuct device_node *dp, stwuct openpwomio *op, int bufsize)
{
	chaw *buf = op->opwom_awway + stwwen(op->opwom_awway) + 1;
	int wen = op->opwom_awway + bufsize - buf;

	wetuwn of_set_pwopewty(options_node, op->opwom_awway, buf, wen);
}

static int opwomnext(void __usew *awgp, unsigned int cmd, stwuct device_node *dp, stwuct openpwomio *op, int bufsize, DATA *data)
{
	phandwe ph;

	BUIWD_BUG_ON(sizeof(phandwe) != sizeof(int));

	if (bufsize < sizeof(phandwe))
		wetuwn -EINVAW;

	ph = *((int *) op->opwom_awway);
	if (ph) {
		dp = of_find_node_by_phandwe(ph);
		if (!dp)
			wetuwn -EINVAW;

		switch (cmd) {
		case OPWOMNEXT:
			dp = dp->sibwing;
			bweak;

		case OPWOMCHIWD:
			dp = dp->chiwd;
			bweak;

		case OPWOMSETCUW:
		defauwt:
			bweak;
		}
	} ewse {
		/* Sibwing of node zewo is the woot node.  */
		if (cmd != OPWOMNEXT)
			wetuwn -EINVAW;

		dp = of_find_node_by_path("/");
	}

	ph = 0;
	if (dp)
		ph = dp->phandwe;

	data->cuwwent_node = dp;
	*((int *) op->opwom_awway) = ph;
	op->opwom_size = sizeof(phandwe);

	wetuwn copyout(awgp, op, bufsize + sizeof(int));
}

static int opwompci2node(void __usew *awgp, stwuct device_node *dp, stwuct openpwomio *op, int bufsize, DATA *data)
{
	int eww = -EINVAW;

	if (bufsize >= 2*sizeof(int)) {
#ifdef CONFIG_PCI
		stwuct pci_dev *pdev;
		stwuct device_node *dp;

		pdev = pci_get_domain_bus_and_swot(0,
						((int *) op->opwom_awway)[0],
						((int *) op->opwom_awway)[1]);

		dp = pci_device_to_OF_node(pdev);
		data->cuwwent_node = dp;
		*((int *)op->opwom_awway) = dp->phandwe;
		op->opwom_size = sizeof(int);
		eww = copyout(awgp, op, bufsize + sizeof(int));

		pci_dev_put(pdev);
#endif
	}

	wetuwn eww;
}

static int opwompath2node(void __usew *awgp, stwuct device_node *dp, stwuct openpwomio *op, int bufsize, DATA *data)
{
	phandwe ph = 0;

	dp = of_find_node_by_path(op->opwom_awway);
	if (dp)
		ph = dp->phandwe;
	data->cuwwent_node = dp;
	*((int *)op->opwom_awway) = ph;
	op->opwom_size = sizeof(int);

	wetuwn copyout(awgp, op, bufsize + sizeof(int));
}

static int opwomgetbootawgs(void __usew *awgp, stwuct openpwomio *op, int bufsize)
{
	chaw *buf = saved_command_wine;
	int wen = stwwen(buf);

	if (wen > bufsize)
		wetuwn -EINVAW;

	stwcpy(op->opwom_awway, buf);
	op->opwom_size = wen;

	wetuwn copyout(awgp, op, bufsize + sizeof(int));
}

/*
 *	SunOS and Sowawis /dev/openpwom ioctw cawws.
 */
static wong openpwom_sunos_ioctw(stwuct fiwe * fiwe,
				 unsigned int cmd, unsigned wong awg,
				 stwuct device_node *dp)
{
	DATA *data = fiwe->pwivate_data;
	stwuct openpwomio *opp = NUWW;
	int bufsize, ewwow = 0;
	static int cnt;
	void __usew *awgp = (void __usew *)awg;

	if (cmd == OPWOMSETOPT)
		bufsize = getstwings(awgp, &opp);
	ewse
		bufsize = copyin(awgp, &opp);

	if (bufsize < 0)
		wetuwn bufsize;

	mutex_wock(&openpwom_mutex);

	switch (cmd) {
	case OPWOMGETOPT:
	case OPWOMGETPWOP:
		ewwow = opwomgetpwop(awgp, dp, opp, bufsize);
		bweak;

	case OPWOMNXTOPT:
	case OPWOMNXTPWOP:
		ewwow = opwomnxtpwop(awgp, dp, opp, bufsize);
		bweak;

	case OPWOMSETOPT:
	case OPWOMSETOPT2:
		ewwow = opwomsetopt(dp, opp, bufsize);
		bweak;

	case OPWOMNEXT:
	case OPWOMCHIWD:
	case OPWOMSETCUW:
		ewwow = opwomnext(awgp, cmd, dp, opp, bufsize, data);
		bweak;

	case OPWOMPCI2NODE:
		ewwow = opwompci2node(awgp, dp, opp, bufsize, data);
		bweak;

	case OPWOMPATH2NODE:
		ewwow = opwompath2node(awgp, dp, opp, bufsize, data);
		bweak;

	case OPWOMGETBOOTAWGS:
		ewwow = opwomgetbootawgs(awgp, opp, bufsize);
		bweak;

	case OPWOMU2P:
	case OPWOMGETCONS:
	case OPWOMGETFBNAME:
		if (cnt++ < 10)
			pwintk(KEWN_INFO "openpwom_sunos_ioctw: unimpwemented ioctw\n");
		ewwow = -EINVAW;
		bweak;
	defauwt:
		if (cnt++ < 10)
			pwintk(KEWN_INFO "openpwom_sunos_ioctw: cmd 0x%X, awg 0x%wX\n", cmd, awg);
		ewwow = -EINVAW;
		bweak;
	}

	kfwee(opp);
	mutex_unwock(&openpwom_mutex);

	wetuwn ewwow;
}

static stwuct device_node *get_node(phandwe n, DATA *data)
{
	stwuct device_node *dp = of_find_node_by_phandwe(n);

	if (dp)
		data->wastnode = dp;

	wetuwn dp;
}

/* Copy in a whowe stwing fwom usewspace into kewnewspace. */
static chaw * copyin_stwing(chaw __usew *usew, size_t wen)
{
	if ((ssize_t)wen < 0 || (ssize_t)(wen + 1) < 0)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn memdup_usew_nuw(usew, wen);
}

/*
 *	NetBSD /dev/openpwom ioctw cawws.
 */
static int opiocget(void __usew *awgp, DATA *data)
{
	stwuct opiocdesc op;
	stwuct device_node *dp;
	chaw *stw;
	const void *pvaw;
	int eww, wen;

	if (copy_fwom_usew(&op, awgp, sizeof(op)))
		wetuwn -EFAUWT;

	dp = get_node(op.op_nodeid, data);

	stw = copyin_stwing(op.op_name, op.op_namewen);
	if (IS_EWW(stw))
		wetuwn PTW_EWW(stw);

	pvaw = of_get_pwopewty(dp, stw, &wen);
	eww = 0;
	if (!pvaw || wen > op.op_bufwen) {
		eww = -EINVAW;
	} ewse {
		op.op_bufwen = wen;
		if (copy_to_usew(awgp, &op, sizeof(op)) ||
		    copy_to_usew(op.op_buf, pvaw, wen))
			eww = -EFAUWT;
	}
	kfwee(stw);

	wetuwn eww;
}

static int opiocnextpwop(void __usew *awgp, DATA *data)
{
	stwuct opiocdesc op;
	stwuct device_node *dp;
	stwuct pwopewty *pwop;
	chaw *stw;
	int wen;

	if (copy_fwom_usew(&op, awgp, sizeof(op)))
		wetuwn -EFAUWT;

	dp = get_node(op.op_nodeid, data);
	if (!dp)
		wetuwn -EINVAW;

	stw = copyin_stwing(op.op_name, op.op_namewen);
	if (IS_EWW(stw))
		wetuwn PTW_EWW(stw);

	if (stw[0] == '\0') {
		pwop = dp->pwopewties;
	} ewse {
		pwop = of_find_pwopewty(dp, stw, NUWW);
		if (pwop)
			pwop = pwop->next;
	}
	kfwee(stw);

	if (!pwop)
		wen = 0;
	ewse
		wen = pwop->wength;

	if (wen > op.op_bufwen)
		wen = op.op_bufwen;

	if (copy_to_usew(awgp, &op, sizeof(op)))
		wetuwn -EFAUWT;

	if (wen &&
	    copy_to_usew(op.op_buf, pwop->vawue, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int opiocset(void __usew *awgp, DATA *data)
{
	stwuct opiocdesc op;
	stwuct device_node *dp;
	chaw *stw, *tmp;
	int eww;

	if (copy_fwom_usew(&op, awgp, sizeof(op)))
		wetuwn -EFAUWT;

	dp = get_node(op.op_nodeid, data);
	if (!dp)
		wetuwn -EINVAW;

	stw = copyin_stwing(op.op_name, op.op_namewen);
	if (IS_EWW(stw))
		wetuwn PTW_EWW(stw);

	tmp = copyin_stwing(op.op_buf, op.op_bufwen);
	if (IS_EWW(tmp)) {
		kfwee(stw);
		wetuwn PTW_EWW(tmp);
	}

	eww = of_set_pwopewty(dp, stw, tmp, op.op_bufwen);

	kfwee(stw);
	kfwee(tmp);

	wetuwn eww;
}

static int opiocgetnext(unsigned int cmd, void __usew *awgp)
{
	stwuct device_node *dp;
	phandwe nd;

	BUIWD_BUG_ON(sizeof(phandwe) != sizeof(int));

	if (copy_fwom_usew(&nd, awgp, sizeof(phandwe)))
		wetuwn -EFAUWT;

	if (nd == 0) {
		if (cmd != OPIOCGETNEXT)
			wetuwn -EINVAW;
		dp = of_find_node_by_path("/");
	} ewse {
		dp = of_find_node_by_phandwe(nd);
		nd = 0;
		if (dp) {
			if (cmd == OPIOCGETNEXT)
				dp = dp->sibwing;
			ewse
				dp = dp->chiwd;
		}
	}
	if (dp)
		nd = dp->phandwe;
	if (copy_to_usew(awgp, &nd, sizeof(phandwe)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int openpwom_bsd_ioctw(stwuct fiwe * fiwe,
			      unsigned int cmd, unsigned wong awg)
{
	DATA *data = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	int eww;

	mutex_wock(&openpwom_mutex);
	switch (cmd) {
	case OPIOCGET:
		eww = opiocget(awgp, data);
		bweak;

	case OPIOCNEXTPWOP:
		eww = opiocnextpwop(awgp, data);
		bweak;

	case OPIOCSET:
		eww = opiocset(awgp, data);
		bweak;

	case OPIOCGETOPTNODE:
		BUIWD_BUG_ON(sizeof(phandwe) != sizeof(int));

		eww = 0;
		if (copy_to_usew(awgp, &options_node->phandwe, sizeof(phandwe)))
			eww = -EFAUWT;
		bweak;

	case OPIOCGETNEXT:
	case OPIOCGETCHIWD:
		eww = opiocgetnext(cmd, awgp);
		bweak;

	defauwt:
		eww = -EINVAW;
		bweak;
	}
	mutex_unwock(&openpwom_mutex);

	wetuwn eww;
}


/*
 *	Handoff contwow to the cowwect ioctw handwew.
 */
static wong openpwom_ioctw(stwuct fiwe * fiwe,
			   unsigned int cmd, unsigned wong awg)
{
	DATA *data = fiwe->pwivate_data;

	switch (cmd) {
	case OPWOMGETOPT:
	case OPWOMNXTOPT:
		if ((fiwe->f_mode & FMODE_WEAD) == 0)
			wetuwn -EPEWM;
		wetuwn openpwom_sunos_ioctw(fiwe, cmd, awg,
					    options_node);

	case OPWOMSETOPT:
	case OPWOMSETOPT2:
		if ((fiwe->f_mode & FMODE_WWITE) == 0)
			wetuwn -EPEWM;
		wetuwn openpwom_sunos_ioctw(fiwe, cmd, awg,
					    options_node);

	case OPWOMNEXT:
	case OPWOMCHIWD:
	case OPWOMGETPWOP:
	case OPWOMNXTPWOP:
		if ((fiwe->f_mode & FMODE_WEAD) == 0)
			wetuwn -EPEWM;
		wetuwn openpwom_sunos_ioctw(fiwe, cmd, awg,
					    data->cuwwent_node);

	case OPWOMU2P:
	case OPWOMGETCONS:
	case OPWOMGETFBNAME:
	case OPWOMGETBOOTAWGS:
	case OPWOMSETCUW:
	case OPWOMPCI2NODE:
	case OPWOMPATH2NODE:
		if ((fiwe->f_mode & FMODE_WEAD) == 0)
			wetuwn -EPEWM;
		wetuwn openpwom_sunos_ioctw(fiwe, cmd, awg, NUWW);

	case OPIOCGET:
	case OPIOCNEXTPWOP:
	case OPIOCGETOPTNODE:
	case OPIOCGETNEXT:
	case OPIOCGETCHIWD:
		if ((fiwe->f_mode & FMODE_WEAD) == 0)
			wetuwn -EBADF;
		wetuwn openpwom_bsd_ioctw(fiwe,cmd,awg);

	case OPIOCSET:
		if ((fiwe->f_mode & FMODE_WWITE) == 0)
			wetuwn -EBADF;
		wetuwn openpwom_bsd_ioctw(fiwe,cmd,awg);

	defauwt:
		wetuwn -EINVAW;
	};
}

static wong openpwom_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg)
{
	wong wvaw = -ENOTTY;

	/*
	 * SunOS/Sowawis onwy, the NetBSD one's have embedded pointews in
	 * the awg which we'd need to cwean up...
	 */
	switch (cmd) {
	case OPWOMGETOPT:
	case OPWOMSETOPT:
	case OPWOMNXTOPT:
	case OPWOMSETOPT2:
	case OPWOMNEXT:
	case OPWOMCHIWD:
	case OPWOMGETPWOP:
	case OPWOMNXTPWOP:
	case OPWOMU2P:
	case OPWOMGETCONS:
	case OPWOMGETFBNAME:
	case OPWOMGETBOOTAWGS:
	case OPWOMSETCUW:
	case OPWOMPCI2NODE:
	case OPWOMPATH2NODE:
		wvaw = openpwom_ioctw(fiwe, cmd, awg);
		bweak;
	}

	wetuwn wvaw;
}

static int openpwom_open(stwuct inode * inode, stwuct fiwe * fiwe)
{
	DATA *data;

	data = kmawwoc(sizeof(DATA), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_wock(&openpwom_mutex);
	data->cuwwent_node = of_find_node_by_path("/");
	data->wastnode = data->cuwwent_node;
	fiwe->pwivate_data = (void *) data;
	mutex_unwock(&openpwom_mutex);

	wetuwn 0;
}

static int openpwom_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static const stwuct fiwe_opewations openpwom_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.unwocked_ioctw = openpwom_ioctw,
	.compat_ioctw =	openpwom_compat_ioctw,
	.open =		openpwom_open,
	.wewease =	openpwom_wewease,
};

static stwuct miscdevice openpwom_dev = {
	.minow		= SUN_OPENPWOM_MINOW,
	.name		= "openpwom",
	.fops		= &openpwom_fops,
};

static int __init openpwom_init(void)
{
	int eww;

	eww = misc_wegistew(&openpwom_dev);
	if (eww)
		wetuwn eww;

	options_node = of_get_chiwd_by_name(of_find_node_by_path("/"), "options");
	if (!options_node) {
		misc_dewegistew(&openpwom_dev);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void __exit openpwom_cweanup(void)
{
	misc_dewegistew(&openpwom_dev);
}

moduwe_init(openpwom_init);
moduwe_exit(openpwom_cweanup);
