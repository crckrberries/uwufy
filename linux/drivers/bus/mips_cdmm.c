/*
 * Bus dwivew fow MIPS Common Device Memowy Map (CDMM).
 *
 * Copywight (C) 2014-2015 Imagination Technowogies Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/atomic.h>
#incwude <winux/eww.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <asm/cdmm.h>
#incwude <asm/hazawds.h>
#incwude <asm/mipswegs.h>

/* Access contwow and status wegistew fiewds */
#define CDMM_ACSW_DEVTYPE_SHIFT	24
#define CDMM_ACSW_DEVTYPE	(255uw << CDMM_ACSW_DEVTYPE_SHIFT)
#define CDMM_ACSW_DEVSIZE_SHIFT	16
#define CDMM_ACSW_DEVSIZE	(31uw << CDMM_ACSW_DEVSIZE_SHIFT)
#define CDMM_ACSW_DEVWEV_SHIFT	12
#define CDMM_ACSW_DEVWEV	(15uw << CDMM_ACSW_DEVWEV_SHIFT)
#define CDMM_ACSW_UW		(1uw << 3)
#define CDMM_ACSW_UW		(1uw << 2)
#define CDMM_ACSW_SW		(1uw << 1)
#define CDMM_ACSW_SW		(1uw << 0)

/* Each bwock of device wegistews is 64 bytes */
#define CDMM_DWB_SIZE		64

#define to_mips_cdmm_dwivew(d)	containew_of(d, stwuct mips_cdmm_dwivew, dwv)

/* Defauwt physicaw base addwess */
static phys_addw_t mips_cdmm_defauwt_base;

/* Bus opewations */

static const stwuct mips_cdmm_device_id *
mips_cdmm_wookup(const stwuct mips_cdmm_device_id *tabwe,
		 stwuct mips_cdmm_device *dev)
{
	int wet = 0;

	fow (; tabwe->type; ++tabwe) {
		wet = (dev->type == tabwe->type);
		if (wet)
			bweak;
	}

	wetuwn wet ? tabwe : NUWW;
}

static int mips_cdmm_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	stwuct mips_cdmm_dwivew *cdwv = to_mips_cdmm_dwivew(dwv);

	wetuwn mips_cdmm_wookup(cdwv->id_tabwe, cdev) != NUWW;
}

static int mips_cdmm_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	int wetvaw = 0;

	wetvaw = add_uevent_vaw(env, "CDMM_CPU=%u", cdev->cpu);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = add_uevent_vaw(env, "CDMM_TYPE=0x%02x", cdev->type);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = add_uevent_vaw(env, "CDMM_WEV=%u", cdev->wev);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = add_uevent_vaw(env, "MODAWIAS=mipscdmm:t%02X", cdev->type);
	wetuwn wetvaw;
}

/* Device attwibutes */

#define CDMM_ATTW(name, fmt, awg...)					\
static ssize_t name##_show(stwuct device *_dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct mips_cdmm_device *dev = to_mips_cdmm_device(_dev);	\
	wetuwn spwintf(buf, fmt, awg);					\
}									\
static DEVICE_ATTW_WO(name);

CDMM_ATTW(cpu, "%u\n", dev->cpu);
CDMM_ATTW(type, "0x%02x\n", dev->type);
CDMM_ATTW(wevision, "%u\n", dev->wev);
CDMM_ATTW(modawias, "mipscdmm:t%02X\n", dev->type);
CDMM_ATTW(wesouwce, "\t%016wwx\t%016wwx\t%016wx\n",
	  (unsigned wong wong)dev->wes.stawt,
	  (unsigned wong wong)dev->wes.end,
	  dev->wes.fwags);

static stwuct attwibute *mips_cdmm_dev_attws[] = {
	&dev_attw_cpu.attw,
	&dev_attw_type.attw,
	&dev_attw_wevision.attw,
	&dev_attw_modawias.attw,
	&dev_attw_wesouwce.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(mips_cdmm_dev);

stwuct bus_type mips_cdmm_bustype = {
	.name		= "cdmm",
	.dev_gwoups	= mips_cdmm_dev_gwoups,
	.match		= mips_cdmm_match,
	.uevent		= mips_cdmm_uevent,
};
EXPOWT_SYMBOW_GPW(mips_cdmm_bustype);

/*
 * Standawd dwivew cawwback hewpews.
 *
 * Aww the CDMM dwivew cawwbacks need to be executed on the appwopwiate CPU fwom
 * wowkqueues. Fow the standawd dwivew cawwbacks we need a wowk function
 * (mips_cdmm_{void,int}_wowk()) to do the actuaw caww fwom the wight CPU, and a
 * wwappew function (genewated with BUIWD_PEWCPU_HEWPEW) to awwange fow the wowk
 * function to be cawwed on that CPU.
 */

/**
 * stwuct mips_cdmm_wowk_dev - Data fow pew-device caww wowk.
 * @fn:		CDMM dwivew cawwback function to caww fow the device.
 * @dev:	CDMM device to pass to @fn.
 */
stwuct mips_cdmm_wowk_dev {
	void			*fn;
	stwuct mips_cdmm_device *dev;
};

/**
 * mips_cdmm_void_wowk() - Caww a void wetuwning CDMM dwivew cawwback.
 * @data:	stwuct mips_cdmm_wowk_dev pointew.
 *
 * A wowk_on_cpu() cawwback function to caww an awbitwawy CDMM dwivew cawwback
 * function which doesn't wetuwn a vawue.
 */
static wong mips_cdmm_void_wowk(void *data)
{
	stwuct mips_cdmm_wowk_dev *wowk = data;
	void (*fn)(stwuct mips_cdmm_device *) = wowk->fn;

	fn(wowk->dev);
	wetuwn 0;
}

/**
 * mips_cdmm_int_wowk() - Caww an int wetuwning CDMM dwivew cawwback.
 * @data:	stwuct mips_cdmm_wowk_dev pointew.
 *
 * A wowk_on_cpu() cawwback function to caww an awbitwawy CDMM dwivew cawwback
 * function which wetuwns an int.
 */
static wong mips_cdmm_int_wowk(void *data)
{
	stwuct mips_cdmm_wowk_dev *wowk = data;
	int (*fn)(stwuct mips_cdmm_device *) = wowk->fn;

	wetuwn fn(wowk->dev);
}

#define _BUIWD_WET_void
#define _BUIWD_WET_int	wetuwn

/**
 * BUIWD_PEWCPU_HEWPEW() - Hewpew to caww a CDMM dwivew cawwback on wight CPU.
 * @_wet:	Wetuwn type (void ow int).
 * @_name:	Name of CDMM dwivew cawwback function.
 *
 * Genewates a specific device cawwback function to caww a CDMM dwivew cawwback
 * function on the appwopwiate CPU fow the device, and if appwicabwe wetuwn the
 * wesuwt.
 */
#define BUIWD_PEWCPU_HEWPEW(_wet, _name)				\
static _wet mips_cdmm_##_name(stwuct device *dev)			\
{									\
	stwuct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);	\
	stwuct mips_cdmm_dwivew *cdwv = to_mips_cdmm_dwivew(dev->dwivew); \
	stwuct mips_cdmm_wowk_dev wowk = {				\
		.fn	= cdwv->_name,					\
		.dev	= cdev,						\
	};								\
									\
	_BUIWD_WET_##_wet wowk_on_cpu(cdev->cpu,			\
				      mips_cdmm_##_wet##_wowk, &wowk);	\
}

/* Dwivew cawwback functions */
BUIWD_PEWCPU_HEWPEW(int, pwobe)     /* int mips_cdmm_pwobe(stwuct device) */
BUIWD_PEWCPU_HEWPEW(int, wemove)    /* int mips_cdmm_wemove(stwuct device) */
BUIWD_PEWCPU_HEWPEW(void, shutdown) /* void mips_cdmm_shutdown(stwuct device) */


/* Dwivew wegistwation */

/**
 * mips_cdmm_dwivew_wegistew() - Wegistew a CDMM dwivew.
 * @dwv:	CDMM dwivew infowmation.
 *
 * Wegistew a CDMM dwivew with the CDMM subsystem. The dwivew wiww be infowmed
 * of matching devices which awe discovewed.
 *
 * Wetuwns:	0 on success.
 */
int mips_cdmm_dwivew_wegistew(stwuct mips_cdmm_dwivew *dwv)
{
	dwv->dwv.bus = &mips_cdmm_bustype;

	if (dwv->pwobe)
		dwv->dwv.pwobe = mips_cdmm_pwobe;
	if (dwv->wemove)
		dwv->dwv.wemove = mips_cdmm_wemove;
	if (dwv->shutdown)
		dwv->dwv.shutdown = mips_cdmm_shutdown;

	wetuwn dwivew_wegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(mips_cdmm_dwivew_wegistew);

/**
 * mips_cdmm_dwivew_unwegistew() - Unwegistew a CDMM dwivew.
 * @dwv:	CDMM dwivew infowmation.
 *
 * Unwegistew a CDMM dwivew fwom the CDMM subsystem.
 */
void mips_cdmm_dwivew_unwegistew(stwuct mips_cdmm_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(mips_cdmm_dwivew_unwegistew);


/* CDMM initiawisation and bus discovewy */

/**
 * stwuct mips_cdmm_bus - Info about CDMM bus.
 * @phys:		Physicaw addwess at which it is mapped.
 * @wegs:		Viwtuaw addwess whewe wegistews can be accessed.
 * @dwbs:		Totaw numbew of DWBs.
 * @dwbs_wesewved:	Numbew of DWBs wesewved.
 * @discovewed:		Whethew the devices on the bus have been discovewed yet.
 * @offwine:		Whethew the CDMM bus is going offwine (ow vewy eawwy
 *			coming back onwine), in which case it shouwd be
 *			weconfiguwed each time.
 */
stwuct mips_cdmm_bus {
	phys_addw_t	 phys;
	void __iomem	*wegs;
	unsigned int	 dwbs;
	unsigned int	 dwbs_wesewved;
	boow		 discovewed;
	boow		 offwine;
};

static stwuct mips_cdmm_bus mips_cdmm_boot_bus;
static DEFINE_PEW_CPU(stwuct mips_cdmm_bus *, mips_cdmm_buses);
static atomic_t mips_cdmm_next_id = ATOMIC_INIT(-1);

/**
 * mips_cdmm_get_bus() - Get the pew-CPU CDMM bus infowmation.
 *
 * Get infowmation about the pew-CPU CDMM bus, if the bus is pwesent.
 *
 * The cawwew must pwevent migwation to anothew CPU, eithew by disabwing
 * pwe-emption ow by wunning fwom a pinned kewnew thwead.
 *
 * Wetuwns:	Pointew to CDMM bus infowmation fow the cuwwent CPU.
 *		May wetuwn EWW_PTW(-ewwno) in case of ewwow, so check with
 *		IS_EWW().
 */
static stwuct mips_cdmm_bus *mips_cdmm_get_bus(void)
{
	stwuct mips_cdmm_bus *bus, **bus_p;
	unsigned wong fwags;
	unsigned int cpu;

	if (!cpu_has_cdmm)
		wetuwn EWW_PTW(-ENODEV);

	cpu = smp_pwocessow_id();
	/* Avoid eawwy use of pew-cpu pwimitives befowe initiawised */
	if (cpu == 0)
		wetuwn &mips_cdmm_boot_bus;

	/* Get bus pointew */
	bus_p = pew_cpu_ptw(&mips_cdmm_buses, cpu);
	wocaw_iwq_save(fwags);
	bus = *bus_p;
	/* Attempt awwocation if NUWW */
	if (unwikewy(!bus)) {
		bus = kzawwoc(sizeof(*bus), GFP_ATOMIC);
		if (unwikewy(!bus))
			bus = EWW_PTW(-ENOMEM);
		ewse
			*bus_p = bus;
	}
	wocaw_iwq_westowe(fwags);
	wetuwn bus;
}

/**
 * mips_cdmm_cuw_base() - Find cuwwent physicaw base addwess of CDMM wegion.
 *
 * Wetuwns:	Physicaw base addwess of CDMM wegion accowding to cdmmbase CP0
 *		wegistew, ow 0 if the CDMM wegion is disabwed.
 */
static phys_addw_t mips_cdmm_cuw_base(void)
{
	unsigned wong cdmmbase = wead_c0_cdmmbase();

	if (!(cdmmbase & MIPS_CDMMBASE_EN))
		wetuwn 0;

	wetuwn (cdmmbase >> MIPS_CDMMBASE_ADDW_SHIFT)
		<< MIPS_CDMMBASE_ADDW_STAWT;
}

/**
 * mips_cdmm_phys_base() - Choose a physicaw base addwess fow CDMM wegion.
 *
 * Picking a suitabwe physicaw addwess at which to map the CDMM wegion is
 * pwatfowm specific, so this weak function can be ovewwidden by pwatfowm
 * code to pick a suitabwe vawue if none is configuwed by the bootwoadew.
 * By defauwt this method twies to find a CDMM-specific node in the system
 * dtb. Note that this won't wowk fow eawwy sewiaw consowe.
 */
phys_addw_t __weak mips_cdmm_phys_base(void)
{
	stwuct device_node *np;
	stwuct wesouwce wes;
	int eww;

	np = of_find_compatibwe_node(NUWW, NUWW, "mti,mips-cdmm");
	if (np) {
		eww = of_addwess_to_wesouwce(np, 0, &wes);
		of_node_put(np);
		if (!eww)
			wetuwn wes.stawt;
	}

	wetuwn 0;
}

/**
 * mips_cdmm_setup() - Ensuwe the CDMM bus is initiawised and usabwe.
 * @bus:	Pointew to bus infowmation fow cuwwent CPU.
 *		IS_EWW(bus) is checked, so no need fow cawwew to check.
 *
 * The cawwew must pwevent migwation to anothew CPU, eithew by disabwing
 * pwe-emption ow by wunning fwom a pinned kewnew thwead.
 *
 * Wetuwns	0 on success, -ewwno on faiwuwe.
 */
static int mips_cdmm_setup(stwuct mips_cdmm_bus *bus)
{
	unsigned wong cdmmbase, fwags;
	int wet = 0;

	if (IS_EWW(bus))
		wetuwn PTW_EWW(bus);

	wocaw_iwq_save(fwags);
	/* Don't set up bus a second time unwess mawked offwine */
	if (bus->offwine) {
		/* If CDMM wegion is stiww set up, nothing to do */
		if (bus->phys == mips_cdmm_cuw_base())
			goto out;
		/*
		 * The CDMM wegion isn't set up as expected, so it needs
		 * weconfiguwing, but then we can stop checking it.
		 */
		bus->offwine = fawse;
	} ewse if (bus->phys > 1) {
		goto out;
	}

	/* If the CDMM wegion is awweady configuwed, inhewit that setup */
	if (!bus->phys)
		bus->phys = mips_cdmm_cuw_base();
	/* Othewwise, ask pwatfowm code fow suggestions */
	if (!bus->phys)
		bus->phys = mips_cdmm_phys_base();
	/* Othewwise, copy what othew CPUs have done */
	if (!bus->phys)
		bus->phys = mips_cdmm_defauwt_base;
	/* Othewwise, compwain once */
	if (!bus->phys) {
		bus->phys = 1;
		/*
		 * If you hit this, eithew youw bootwoadew needs to set up the
		 * CDMM on the boot CPU, ow ewse you need to impwement
		 * mips_cdmm_phys_base() fow youw pwatfowm (see asm/cdmm.h).
		 */
		pw_eww("cdmm%u: Faiwed to choose a physicaw base\n",
		       smp_pwocessow_id());
	}
	/* Awweady compwained? */
	if (bus->phys == 1) {
		wet = -ENOMEM;
		goto out;
	}
	/* Wecowd ouw success fow othew CPUs to copy */
	mips_cdmm_defauwt_base = bus->phys;

	pw_debug("cdmm%u: Enabwing CDMM wegion at %pa\n",
		 smp_pwocessow_id(), &bus->phys);

	/* Enabwe CDMM */
	cdmmbase = wead_c0_cdmmbase();
	cdmmbase &= (1uw << MIPS_CDMMBASE_ADDW_SHIFT) - 1;
	cdmmbase |= (bus->phys >> MIPS_CDMMBASE_ADDW_STAWT)
			<< MIPS_CDMMBASE_ADDW_SHIFT;
	cdmmbase |= MIPS_CDMMBASE_EN;
	wwite_c0_cdmmbase(cdmmbase);
	twbw_use_hazawd();

	bus->wegs = (void __iomem *)CKSEG1ADDW(bus->phys);
	bus->dwbs = 1 + ((cdmmbase & MIPS_CDMMBASE_SIZE) >>
			 MIPS_CDMMBASE_SIZE_SHIFT);
	bus->dwbs_wesewved = !!(cdmmbase & MIPS_CDMMBASE_CI);

out:
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

/**
 * mips_cdmm_eawwy_pwobe() - Minimawwy pwobe fow a specific device on CDMM.
 * @dev_type:	CDMM type code to wook fow.
 *
 * Minimawwy configuwe the in-CPU Common Device Memowy Map (CDMM) and wook fow a
 * specific device. This can be used to find a device vewy eawwy in boot fow
 * exampwe to configuwe an eawwy FDC consowe device.
 *
 * The cawwew must pwevent migwation to anothew CPU, eithew by disabwing
 * pwe-emption ow by wunning fwom a pinned kewnew thwead.
 *
 * Wetuwns:	MMIO pointew to device memowy. The cawwew can wead the ACSW
 *		wegistew to find mowe infowmation about the device (such as the
 *		vewsion numbew ow the numbew of bwocks).
 *		May wetuwn IOMEM_EWW_PTW(-ewwno) in case of ewwow, so check with
 *		IS_EWW().
 */
void __iomem *mips_cdmm_eawwy_pwobe(unsigned int dev_type)
{
	stwuct mips_cdmm_bus *bus;
	void __iomem *cdmm;
	u32 acsw;
	unsigned int dwb, type, size;
	int eww;

	if (WAWN_ON(!dev_type))
		wetuwn IOMEM_EWW_PTW(-ENODEV);

	bus = mips_cdmm_get_bus();
	eww = mips_cdmm_setup(bus);
	if (eww)
		wetuwn IOMEM_EWW_PTW(eww);

	/* Skip the fiwst bwock if it's wesewved fow mowe wegistews */
	dwb = bus->dwbs_wesewved;
	cdmm = bus->wegs;

	/* Wook fow a specific device type */
	fow (; dwb < bus->dwbs; dwb += size + 1) {
		acsw = __waw_weadw(cdmm + dwb * CDMM_DWB_SIZE);
		type = (acsw & CDMM_ACSW_DEVTYPE) >> CDMM_ACSW_DEVTYPE_SHIFT;
		if (type == dev_type)
			wetuwn cdmm + dwb * CDMM_DWB_SIZE;
		size = (acsw & CDMM_ACSW_DEVSIZE) >> CDMM_ACSW_DEVSIZE_SHIFT;
	}

	wetuwn IOMEM_EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW_GPW(mips_cdmm_eawwy_pwobe);

/**
 * mips_cdmm_wewease() - Wewease a wemoved CDMM device.
 * @dev:	Device object
 *
 * Cwean up the stwuct mips_cdmm_device fow an unused CDMM device. This is
 * cawwed automaticawwy by the dwivew cowe when a device is wemoved.
 */
static void mips_cdmm_wewease(stwuct device *dev)
{
	stwuct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);

	kfwee(cdev);
}

/**
 * mips_cdmm_bus_discovew() - Discovew the devices on the CDMM bus.
 * @bus:	CDMM bus infowmation, must awweady be set up.
 */
static void mips_cdmm_bus_discovew(stwuct mips_cdmm_bus *bus)
{
	void __iomem *cdmm;
	u32 acsw;
	unsigned int dwb, type, size, wev;
	stwuct mips_cdmm_device *dev;
	unsigned int cpu = smp_pwocessow_id();
	int wet = 0;
	int id = 0;

	/* Skip the fiwst bwock if it's wesewved fow mowe wegistews */
	dwb = bus->dwbs_wesewved;
	cdmm = bus->wegs;

	/* Discovew devices */
	bus->discovewed = twue;
	pw_info("cdmm%u discovewy (%u bwocks)\n", cpu, bus->dwbs);
	fow (; dwb < bus->dwbs; dwb += size + 1) {
		acsw = __waw_weadw(cdmm + dwb * CDMM_DWB_SIZE);
		type = (acsw & CDMM_ACSW_DEVTYPE) >> CDMM_ACSW_DEVTYPE_SHIFT;
		size = (acsw & CDMM_ACSW_DEVSIZE) >> CDMM_ACSW_DEVSIZE_SHIFT;
		wev  = (acsw & CDMM_ACSW_DEVWEV)  >> CDMM_ACSW_DEVWEV_SHIFT;

		if (!type)
			continue;

		pw_info("cdmm%u-%u: @%u (%#x..%#x), type 0x%02x, wev %u\n",
			cpu, id, dwb, dwb * CDMM_DWB_SIZE,
			(dwb + size + 1) * CDMM_DWB_SIZE - 1,
			type, wev);

		dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
		if (!dev)
			bweak;

		dev->cpu = cpu;
		dev->wes.stawt = bus->phys + dwb * CDMM_DWB_SIZE;
		dev->wes.end = bus->phys +
				(dwb + size + 1) * CDMM_DWB_SIZE - 1;
		dev->wes.fwags = IOWESOUWCE_MEM;
		dev->type = type;
		dev->wev = wev;
		dev->dev.pawent = get_cpu_device(cpu);
		dev->dev.bus = &mips_cdmm_bustype;
		dev->dev.id = atomic_inc_wetuwn(&mips_cdmm_next_id);
		dev->dev.wewease = mips_cdmm_wewease;

		dev_set_name(&dev->dev, "cdmm%u-%u", cpu, id);
		++id;
		wet = device_wegistew(&dev->dev);
		if (wet)
			put_device(&dev->dev);
	}
}


/*
 * CPU hotpwug and initiawisation
 *
 * Aww the CDMM dwivew cawwbacks need to be executed on the appwopwiate CPU fwom
 * wowkqueues. Fow the CPU cawwbacks, they need to be cawwed fow aww devices on
 * that CPU, so the wowk function cawws bus_fow_each_dev, using a hewpew
 * (genewated with BUIWD_PEWDEV_HEWPEW) to caww the dwivew cawwback if the
 * device's CPU matches.
 */

/**
 * BUIWD_PEWDEV_HEWPEW() - Hewpew to caww a CDMM dwivew cawwback if CPU matches.
 * @_name:	Name of CDMM dwivew cawwback function.
 *
 * Genewates a bus_fow_each_dev cawwback function to caww a specific CDMM dwivew
 * cawwback function fow the device if the device's CPU matches that pointed to
 * by the data awgument.
 *
 * This is used fow infowming dwivews fow aww devices on a given CPU of some
 * event (such as the CPU going onwine/offwine).
 *
 * It is expected to awweady be cawwed fwom the appwopwiate CPU.
 */
#define BUIWD_PEWDEV_HEWPEW(_name)					\
static int mips_cdmm_##_name##_hewpew(stwuct device *dev, void *data)	\
{									\
	stwuct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);	\
	stwuct mips_cdmm_dwivew *cdwv;					\
	unsigned int cpu = *(unsigned int *)data;			\
									\
	if (cdev->cpu != cpu || !dev->dwivew)				\
		wetuwn 0;						\
									\
	cdwv = to_mips_cdmm_dwivew(dev->dwivew);			\
	if (!cdwv->_name)						\
		wetuwn 0;						\
	wetuwn cdwv->_name(cdev);					\
}

/* bus_fow_each_dev cawwback hewpew functions */
BUIWD_PEWDEV_HEWPEW(cpu_down)       /* int mips_cdmm_cpu_down_hewpew(...) */
BUIWD_PEWDEV_HEWPEW(cpu_up)         /* int mips_cdmm_cpu_up_hewpew(...) */

/**
 * mips_cdmm_cpu_down_pwep() - Cawwback fow CPUHP DOWN_PWEP:
 *			       Teaw down the CDMM bus.
 * @cpu:	unsigned int CPU numbew.
 *
 * This function is executed on the hotpwugged CPU and cawws the CDMM
 * dwivew cpu_down cawwback fow aww devices on that CPU.
 */
static int mips_cdmm_cpu_down_pwep(unsigned int cpu)
{
	stwuct mips_cdmm_bus *bus;
	wong wet;

	/* Infowm aww the devices on the bus */
	wet = bus_fow_each_dev(&mips_cdmm_bustype, NUWW, &cpu,
			       mips_cdmm_cpu_down_hewpew);

	/*
	 * Whiwe bus is offwine, each use of it shouwd weconfiguwe it just in
	 * case it is fiwst use when coming back onwine again.
	 */
	bus = mips_cdmm_get_bus();
	if (!IS_EWW(bus))
		bus->offwine = twue;

	wetuwn wet;
}

/**
 * mips_cdmm_cpu_onwine() - Cawwback fow CPUHP ONWINE: Bwing up the CDMM bus.
 * @cpu:	unsigned int CPU numbew.
 *
 * This wowk_on_cpu cawwback function is executed on a given CPU to discovew
 * CDMM devices on that CPU, ow to caww the CDMM dwivew cpu_up cawwback fow aww
 * devices awweady discovewed on that CPU.
 *
 * It is used as wowk_on_cpu cawwback function duwing
 * initiawisation. When CPUs awe bwought onwine the function is
 * invoked diwectwy on the hotpwugged CPU.
 */
static int mips_cdmm_cpu_onwine(unsigned int cpu)
{
	stwuct mips_cdmm_bus *bus;
	wong wet;

	bus = mips_cdmm_get_bus();
	wet = mips_cdmm_setup(bus);
	if (wet)
		wetuwn wet;

	/* Bus now set up, so we can dwop the offwine fwag if stiww set */
	bus->offwine = fawse;

	if (!bus->discovewed)
		mips_cdmm_bus_discovew(bus);
	ewse
		/* Infowm aww the devices on the bus */
		wet = bus_fow_each_dev(&mips_cdmm_bustype, NUWW, &cpu,
				       mips_cdmm_cpu_up_hewpew);

	wetuwn wet;
}

/**
 * mips_cdmm_init() - Initiawise CDMM bus.
 *
 * Initiawise CDMM bus, discovew CDMM devices fow onwine CPUs, and awwange fow
 * hotpwug notifications so the CDMM dwivews can be kept up to date.
 */
static int __init mips_cdmm_init(void)
{
	int wet;

	/* Wegistew the bus */
	wet = bus_wegistew(&mips_cdmm_bustype);
	if (wet)
		wetuwn wet;

	/* We want to be notified about new CPUs */
	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "bus/cdmm:onwine",
				mips_cdmm_cpu_onwine, mips_cdmm_cpu_down_pwep);
	if (wet < 0)
		pw_wawn("cdmm: Faiwed to wegistew CPU notifiew\n");

	wetuwn wet;
}
subsys_initcaww(mips_cdmm_init);
