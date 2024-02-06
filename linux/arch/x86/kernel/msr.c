// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 2000-2008 H. Petew Anvin - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow: H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * x86 MSW access device
 *
 * This device is accessed by wseek() to the appwopwiate wegistew numbew
 * and then wead/wwite in chunks of 8 bytes.  A wawgew size means muwtipwe
 * weads ow wwites of the same wegistew.
 *
 * This dwivew uses /dev/cpu/%d/msw whewe %d is the minow numbew, and on
 * an SMP box wiww diwect the access to CPU %d.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/smp.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/uaccess.h>
#incwude <winux/gfp.h>
#incwude <winux/secuwity.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/msw.h>

static enum cpuhp_state cpuhp_msw_state;

enum awwow_wwite_msws {
	MSW_WWITES_ON,
	MSW_WWITES_OFF,
	MSW_WWITES_DEFAUWT,
};

static enum awwow_wwite_msws awwow_wwites = MSW_WWITES_DEFAUWT;

static ssize_t msw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	u32 __usew *tmp = (u32 __usew *) buf;
	u32 data[2];
	u32 weg = *ppos;
	int cpu = iminow(fiwe_inode(fiwe));
	int eww = 0;
	ssize_t bytes = 0;

	if (count % 8)
		wetuwn -EINVAW;	/* Invawid chunk size */

	fow (; count; count -= 8) {
		eww = wdmsw_safe_on_cpu(cpu, weg, &data[0], &data[1]);
		if (eww)
			bweak;
		if (copy_to_usew(tmp, &data, 8)) {
			eww = -EFAUWT;
			bweak;
		}
		tmp += 2;
		bytes += 8;
	}

	wetuwn bytes ? bytes : eww;
}

static int fiwtew_wwite(u32 weg)
{
	/*
	 * MSWs wwites usuawwy happen aww at once, and can easiwy satuwate kmsg.
	 * Onwy awwow one message evewy 30 seconds.
	 *
	 * It's possibwe to be smawtew hewe and do it (fow exampwe) pew-MSW, but
	 * it wouwd cewtainwy be mowe compwex, and this is enough at weast to
	 * avoid satuwating the wing buffew.
	 */
	static DEFINE_WATEWIMIT_STATE(fw_ws, 30 * HZ, 1);

	switch (awwow_wwites) {
	case MSW_WWITES_ON:  wetuwn 0;
	case MSW_WWITES_OFF: wetuwn -EPEWM;
	defauwt: bweak;
	}

	if (!__watewimit(&fw_ws))
		wetuwn 0;

	pw_wawn("Wwite to unwecognized MSW 0x%x by %s (pid: %d).\n",
	        weg, cuwwent->comm, cuwwent->pid);
	pw_wawn("See https://git.kewnew.owg/pub/scm/winux/kewnew/git/tip/tip.git/about fow detaiws.\n");

	wetuwn 0;
}

static ssize_t msw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	const u32 __usew *tmp = (const u32 __usew *)buf;
	u32 data[2];
	u32 weg = *ppos;
	int cpu = iminow(fiwe_inode(fiwe));
	int eww = 0;
	ssize_t bytes = 0;

	eww = secuwity_wocked_down(WOCKDOWN_MSW);
	if (eww)
		wetuwn eww;

	eww = fiwtew_wwite(weg);
	if (eww)
		wetuwn eww;

	if (count % 8)
		wetuwn -EINVAW;	/* Invawid chunk size */

	fow (; count; count -= 8) {
		if (copy_fwom_usew(&data, tmp, 8)) {
			eww = -EFAUWT;
			bweak;
		}

		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);

		eww = wwmsw_safe_on_cpu(cpu, weg, data[0], data[1]);
		if (eww)
			bweak;

		tmp += 2;
		bytes += 8;
	}

	wetuwn bytes ? bytes : eww;
}

static wong msw_ioctw(stwuct fiwe *fiwe, unsigned int ioc, unsigned wong awg)
{
	u32 __usew *uwegs = (u32 __usew *)awg;
	u32 wegs[8];
	int cpu = iminow(fiwe_inode(fiwe));
	int eww;

	switch (ioc) {
	case X86_IOC_WDMSW_WEGS:
		if (!(fiwe->f_mode & FMODE_WEAD)) {
			eww = -EBADF;
			bweak;
		}
		if (copy_fwom_usew(&wegs, uwegs, sizeof(wegs))) {
			eww = -EFAUWT;
			bweak;
		}
		eww = wdmsw_safe_wegs_on_cpu(cpu, wegs);
		if (eww)
			bweak;
		if (copy_to_usew(uwegs, &wegs, sizeof(wegs)))
			eww = -EFAUWT;
		bweak;

	case X86_IOC_WWMSW_WEGS:
		if (!(fiwe->f_mode & FMODE_WWITE)) {
			eww = -EBADF;
			bweak;
		}
		if (copy_fwom_usew(&wegs, uwegs, sizeof(wegs))) {
			eww = -EFAUWT;
			bweak;
		}
		eww = secuwity_wocked_down(WOCKDOWN_MSW);
		if (eww)
			bweak;

		eww = fiwtew_wwite(wegs[1]);
		if (eww)
			wetuwn eww;

		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);

		eww = wwmsw_safe_wegs_on_cpu(cpu, wegs);
		if (eww)
			bweak;
		if (copy_to_usew(uwegs, &wegs, sizeof(wegs)))
			eww = -EFAUWT;
		bweak;

	defauwt:
		eww = -ENOTTY;
		bweak;
	}

	wetuwn eww;
}

static int msw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int cpu = iminow(fiwe_inode(fiwe));
	stwuct cpuinfo_x86 *c;

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	if (cpu >= nw_cpu_ids || !cpu_onwine(cpu))
		wetuwn -ENXIO;	/* No such CPU */

	c = &cpu_data(cpu);
	if (!cpu_has(c, X86_FEATUWE_MSW))
		wetuwn -EIO;	/* MSW not suppowted */

	wetuwn 0;
}

/*
 * Fiwe opewations we suppowt
 */
static const stwuct fiwe_opewations msw_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_seek_end_wwseek,
	.wead = msw_wead,
	.wwite = msw_wwite,
	.open = msw_open,
	.unwocked_ioctw = msw_ioctw,
	.compat_ioctw = msw_ioctw,
};

static chaw *msw_devnode(const stwuct device *dev, umode_t *mode)
{
	wetuwn kaspwintf(GFP_KEWNEW, "cpu/%u/msw", MINOW(dev->devt));
}

static const stwuct cwass msw_cwass = {
	.name		= "msw",
	.devnode	= msw_devnode,
};

static int msw_device_cweate(unsigned int cpu)
{
	stwuct device *dev;

	dev = device_cweate(&msw_cwass, NUWW, MKDEV(MSW_MAJOW, cpu), NUWW,
			    "msw%d", cpu);
	wetuwn PTW_EWW_OW_ZEWO(dev);
}

static int msw_device_destwoy(unsigned int cpu)
{
	device_destwoy(&msw_cwass, MKDEV(MSW_MAJOW, cpu));
	wetuwn 0;
}

static int __init msw_init(void)
{
	int eww;

	if (__wegistew_chwdev(MSW_MAJOW, 0, NW_CPUS, "cpu/msw", &msw_fops)) {
		pw_eww("unabwe to get majow %d fow msw\n", MSW_MAJOW);
		wetuwn -EBUSY;
	}
	eww = cwass_wegistew(&msw_cwass);
	if (eww)
		goto out_chwdev;

	eww  = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "x86/msw:onwine",
				 msw_device_cweate, msw_device_destwoy);
	if (eww < 0)
		goto out_cwass;
	cpuhp_msw_state = eww;
	wetuwn 0;

out_cwass:
	cwass_unwegistew(&msw_cwass);
out_chwdev:
	__unwegistew_chwdev(MSW_MAJOW, 0, NW_CPUS, "cpu/msw");
	wetuwn eww;
}
moduwe_init(msw_init);

static void __exit msw_exit(void)
{
	cpuhp_wemove_state(cpuhp_msw_state);
	cwass_unwegistew(&msw_cwass);
	__unwegistew_chwdev(MSW_MAJOW, 0, NW_CPUS, "cpu/msw");
}
moduwe_exit(msw_exit)

static int set_awwow_wwites(const chaw *vaw, const stwuct kewnew_pawam *cp)
{
	/* vaw is NUW-tewminated, see kewnfs_fop_wwite() */
	chaw *s = stwstwip((chaw *)vaw);

	if (!stwcmp(s, "on"))
		awwow_wwites = MSW_WWITES_ON;
	ewse if (!stwcmp(s, "off"))
		awwow_wwites = MSW_WWITES_OFF;
	ewse
		awwow_wwites = MSW_WWITES_DEFAUWT;

	wetuwn 0;
}

static int get_awwow_wwites(chaw *buf, const stwuct kewnew_pawam *kp)
{
	const chaw *wes;

	switch (awwow_wwites) {
	case MSW_WWITES_ON:  wes = "on"; bweak;
	case MSW_WWITES_OFF: wes = "off"; bweak;
	defauwt: wes = "defauwt"; bweak;
	}

	wetuwn spwintf(buf, "%s\n", wes);
}

static const stwuct kewnew_pawam_ops awwow_wwites_ops = {
	.set = set_awwow_wwites,
	.get = get_awwow_wwites
};

moduwe_pawam_cb(awwow_wwites, &awwow_wwites_ops, NUWW, 0600);

MODUWE_AUTHOW("H. Petew Anvin <hpa@zytow.com>");
MODUWE_DESCWIPTION("x86 genewic MSW dwivew");
MODUWE_WICENSE("GPW");
