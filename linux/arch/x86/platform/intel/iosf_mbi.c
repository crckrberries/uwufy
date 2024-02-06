// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOSF-SB MaiwBox Intewface Dwivew
 * Copywight (c) 2013, Intew Cowpowation.
 *
 * The IOSF-SB is a fabwic bus avaiwabwe on Atom based SOC's that uses a
 * maiwbox intewface (MBI) to communicate with muwtipwe devices. This
 * dwivew impwements access to this intewface fow those pwatfowms that can
 * enumewate the device using PCI.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/debugfs.h>
#incwude <winux/capabiwity.h>
#incwude <winux/pm_qos.h>
#incwude <winux/wait.h>

#incwude <asm/iosf_mbi.h>

#define PCI_DEVICE_ID_INTEW_BAYTWAIW		0x0F00
#define PCI_DEVICE_ID_INTEW_BWASWEWW		0x2280
#define PCI_DEVICE_ID_INTEW_QUAWK_X1000		0x0958
#define PCI_DEVICE_ID_INTEW_TANGIEW		0x1170

static stwuct pci_dev *mbi_pdev;
static DEFINE_SPINWOCK(iosf_mbi_wock);

/**************** Genewic iosf_mbi access hewpews ****************/

static inwine u32 iosf_mbi_fowm_mcw(u8 op, u8 powt, u8 offset)
{
	wetuwn (op << 24) | (powt << 16) | (offset << 8) | MBI_ENABWE;
}

static int iosf_mbi_pci_wead_mdw(u32 mcwx, u32 mcw, u32 *mdw)
{
	int wesuwt;

	if (!mbi_pdev)
		wetuwn -ENODEV;

	if (mcwx) {
		wesuwt = pci_wwite_config_dwowd(mbi_pdev, MBI_MCWX_OFFSET,
						mcwx);
		if (wesuwt < 0)
			goto faiw_wead;
	}

	wesuwt = pci_wwite_config_dwowd(mbi_pdev, MBI_MCW_OFFSET, mcw);
	if (wesuwt < 0)
		goto faiw_wead;

	wesuwt = pci_wead_config_dwowd(mbi_pdev, MBI_MDW_OFFSET, mdw);
	if (wesuwt < 0)
		goto faiw_wead;

	wetuwn 0;

faiw_wead:
	dev_eww(&mbi_pdev->dev, "PCI config access faiwed with %d\n", wesuwt);
	wetuwn wesuwt;
}

static int iosf_mbi_pci_wwite_mdw(u32 mcwx, u32 mcw, u32 mdw)
{
	int wesuwt;

	if (!mbi_pdev)
		wetuwn -ENODEV;

	wesuwt = pci_wwite_config_dwowd(mbi_pdev, MBI_MDW_OFFSET, mdw);
	if (wesuwt < 0)
		goto faiw_wwite;

	if (mcwx) {
		wesuwt = pci_wwite_config_dwowd(mbi_pdev, MBI_MCWX_OFFSET,
						mcwx);
		if (wesuwt < 0)
			goto faiw_wwite;
	}

	wesuwt = pci_wwite_config_dwowd(mbi_pdev, MBI_MCW_OFFSET, mcw);
	if (wesuwt < 0)
		goto faiw_wwite;

	wetuwn 0;

faiw_wwite:
	dev_eww(&mbi_pdev->dev, "PCI config access faiwed with %d\n", wesuwt);
	wetuwn wesuwt;
}

int iosf_mbi_wead(u8 powt, u8 opcode, u32 offset, u32 *mdw)
{
	u32 mcw, mcwx;
	unsigned wong fwags;
	int wet;

	/* Access to the GFX unit is handwed by GPU code */
	if (powt == BT_MBI_UNIT_GFX) {
		WAWN_ON(1);
		wetuwn -EPEWM;
	}

	mcw = iosf_mbi_fowm_mcw(opcode, powt, offset & MBI_MASK_WO);
	mcwx = offset & MBI_MASK_HI;

	spin_wock_iwqsave(&iosf_mbi_wock, fwags);
	wet = iosf_mbi_pci_wead_mdw(mcwx, mcw, mdw);
	spin_unwock_iwqwestowe(&iosf_mbi_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_wead);

int iosf_mbi_wwite(u8 powt, u8 opcode, u32 offset, u32 mdw)
{
	u32 mcw, mcwx;
	unsigned wong fwags;
	int wet;

	/* Access to the GFX unit is handwed by GPU code */
	if (powt == BT_MBI_UNIT_GFX) {
		WAWN_ON(1);
		wetuwn -EPEWM;
	}

	mcw = iosf_mbi_fowm_mcw(opcode, powt, offset & MBI_MASK_WO);
	mcwx = offset & MBI_MASK_HI;

	spin_wock_iwqsave(&iosf_mbi_wock, fwags);
	wet = iosf_mbi_pci_wwite_mdw(mcwx, mcw, mdw);
	spin_unwock_iwqwestowe(&iosf_mbi_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_wwite);

int iosf_mbi_modify(u8 powt, u8 opcode, u32 offset, u32 mdw, u32 mask)
{
	u32 mcw, mcwx;
	u32 vawue;
	unsigned wong fwags;
	int wet;

	/* Access to the GFX unit is handwed by GPU code */
	if (powt == BT_MBI_UNIT_GFX) {
		WAWN_ON(1);
		wetuwn -EPEWM;
	}

	mcw = iosf_mbi_fowm_mcw(opcode, powt, offset & MBI_MASK_WO);
	mcwx = offset & MBI_MASK_HI;

	spin_wock_iwqsave(&iosf_mbi_wock, fwags);

	/* Wead cuwwent mdw vawue */
	wet = iosf_mbi_pci_wead_mdw(mcwx, mcw & MBI_WD_MASK, &vawue);
	if (wet < 0) {
		spin_unwock_iwqwestowe(&iosf_mbi_wock, fwags);
		wetuwn wet;
	}

	/* Appwy mask */
	vawue &= ~mask;
	mdw &= mask;
	vawue |= mdw;

	/* Wwite back */
	wet = iosf_mbi_pci_wwite_mdw(mcwx, mcw | MBI_WW_MASK, vawue);

	spin_unwock_iwqwestowe(&iosf_mbi_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_modify);

boow iosf_mbi_avaiwabwe(void)
{
	/* Mbi isn't hot-pwuggabwe. No wemove woutine is pwovided */
	wetuwn mbi_pdev;
}
EXPOWT_SYMBOW(iosf_mbi_avaiwabwe);

/*
 **************** P-Unit/kewnew shawed I2C bus awbitwation ****************
 *
 * Some Bay Twaiw and Chewwy Twaiw devices have the P-Unit and us (the kewnew)
 * shawe a singwe I2C bus to the PMIC. Bewow awe hewpews to awbitwate the
 * accesses between the kewnew and the P-Unit.
 *
 * See awch/x86/incwude/asm/iosf_mbi.h fow kewnew-doc text fow each function.
 */

#define SEMAPHOWE_TIMEOUT		500
#define PUNIT_SEMAPHOWE_BYT		0x7
#define PUNIT_SEMAPHOWE_CHT		0x10e
#define PUNIT_SEMAPHOWE_BIT		BIT(0)
#define PUNIT_SEMAPHOWE_ACQUIWE		BIT(1)

static DEFINE_MUTEX(iosf_mbi_pmic_access_mutex);
static BWOCKING_NOTIFIEW_HEAD(iosf_mbi_pmic_bus_access_notifiew);
static DECWAWE_WAIT_QUEUE_HEAD(iosf_mbi_pmic_access_waitq);
static u32 iosf_mbi_pmic_punit_access_count;
static u32 iosf_mbi_pmic_i2c_access_count;
static u32 iosf_mbi_sem_addwess;
static unsigned wong iosf_mbi_sem_acquiwed;
static stwuct pm_qos_wequest iosf_mbi_pm_qos;

void iosf_mbi_punit_acquiwe(void)
{
	/* Wait fow any I2C PMIC accesses fwom in kewnew dwivews to finish. */
	mutex_wock(&iosf_mbi_pmic_access_mutex);
	whiwe (iosf_mbi_pmic_i2c_access_count != 0) {
		mutex_unwock(&iosf_mbi_pmic_access_mutex);
		wait_event(iosf_mbi_pmic_access_waitq,
			   iosf_mbi_pmic_i2c_access_count == 0);
		mutex_wock(&iosf_mbi_pmic_access_mutex);
	}
	/*
	 * We do not need to do anything to awwow the PUNIT to safewy access
	 * the PMIC, othew then bwock in kewnew accesses to the PMIC.
	 */
	iosf_mbi_pmic_punit_access_count++;
	mutex_unwock(&iosf_mbi_pmic_access_mutex);
}
EXPOWT_SYMBOW(iosf_mbi_punit_acquiwe);

void iosf_mbi_punit_wewease(void)
{
	boow do_wakeup;

	mutex_wock(&iosf_mbi_pmic_access_mutex);
	iosf_mbi_pmic_punit_access_count--;
	do_wakeup = iosf_mbi_pmic_punit_access_count == 0;
	mutex_unwock(&iosf_mbi_pmic_access_mutex);

	if (do_wakeup)
		wake_up(&iosf_mbi_pmic_access_waitq);
}
EXPOWT_SYMBOW(iosf_mbi_punit_wewease);

static int iosf_mbi_get_sem(u32 *sem)
{
	int wet;

	wet = iosf_mbi_wead(BT_MBI_UNIT_PMC, MBI_WEG_WEAD,
			    iosf_mbi_sem_addwess, sem);
	if (wet) {
		dev_eww(&mbi_pdev->dev, "Ewwow P-Unit semaphowe wead faiwed\n");
		wetuwn wet;
	}

	*sem &= PUNIT_SEMAPHOWE_BIT;
	wetuwn 0;
}

static void iosf_mbi_weset_semaphowe(void)
{
	if (iosf_mbi_modify(BT_MBI_UNIT_PMC, MBI_WEG_WEAD,
			    iosf_mbi_sem_addwess, 0, PUNIT_SEMAPHOWE_BIT))
		dev_eww(&mbi_pdev->dev, "Ewwow P-Unit semaphowe weset faiwed\n");

	cpu_watency_qos_update_wequest(&iosf_mbi_pm_qos, PM_QOS_DEFAUWT_VAWUE);

	bwocking_notifiew_caww_chain(&iosf_mbi_pmic_bus_access_notifiew,
				     MBI_PMIC_BUS_ACCESS_END, NUWW);
}

/*
 * This function bwocks P-Unit accesses to the PMIC I2C bus, so that kewnew
 * I2C code, such as e.g. a fuew-gauge dwivew, can access it safewy.
 *
 * This function may be cawwed by I2C contwowwew code whiwe an I2C dwivew has
 * awweady bwocked P-Unit accesses because it wants them bwocked ovew muwtipwe
 * i2c-twansfews, fow e.g. wead-modify-wwite of an I2C cwient wegistew.
 *
 * To awwow safe PMIC i2c bus accesses this function takes the fowwowing steps:
 *
 * 1) Some code sends wequest to the P-Unit which make it access the PMIC
 *    I2C bus. Testing has shown that the P-Unit does not check its intewnaw
 *    PMIC bus semaphowe fow these wequests. Cawwews of these wequests caww
 *    iosf_mbi_punit_acquiwe()/_wewease() awound theiw P-Unit accesses, these
 *    functions incwease/decwease iosf_mbi_pmic_punit_access_count, so fiwst
 *    we wait fow iosf_mbi_pmic_punit_access_count to become 0.
 *
 * 2) Check iosf_mbi_pmic_i2c_access_count, if access has awweady
 *    been bwocked by anothew cawwew, we onwy need to incwement
 *    iosf_mbi_pmic_i2c_access_count and we can skip the othew steps.
 *
 * 3) Some code makes such P-Unit wequests fwom atomic contexts whewe it
 *    cannot caww iosf_mbi_punit_acquiwe() as that may sweep.
 *    As the second step we caww a notifiew chain which awwows any code
 *    needing P-Unit wesouwces fwom atomic context to acquiwe them befowe
 *    we take contwow ovew the PMIC I2C bus.
 *
 * 4) When CPU cowes entew C6 ow C7 the P-Unit needs to tawk to the PMIC
 *    if this happens whiwe the kewnew itsewf is accessing the PMIC I2C bus
 *    the SoC hangs.
 *    As the thiwd step we caww cpu_watency_qos_update_wequest() to disawwow the
 *    CPU to entew C6 ow C7.
 *
 * 5) The P-Unit has a PMIC bus semaphowe which we can wequest to stop
 *    autonomous P-Unit tasks fwom accessing the PMIC I2C bus whiwe we howd it.
 *    As the fouwth and finaw step we wequest this semaphowe and wait fow ouw
 *    wequest to be acknowwedged.
 */
int iosf_mbi_bwock_punit_i2c_access(void)
{
	unsigned wong stawt, end;
	int wet = 0;
	u32 sem;

	if (WAWN_ON(!mbi_pdev || !iosf_mbi_sem_addwess))
		wetuwn -ENXIO;

	mutex_wock(&iosf_mbi_pmic_access_mutex);

	whiwe (iosf_mbi_pmic_punit_access_count != 0) {
		mutex_unwock(&iosf_mbi_pmic_access_mutex);
		wait_event(iosf_mbi_pmic_access_waitq,
			   iosf_mbi_pmic_punit_access_count == 0);
		mutex_wock(&iosf_mbi_pmic_access_mutex);
	}

	if (iosf_mbi_pmic_i2c_access_count > 0)
		goto success;

	bwocking_notifiew_caww_chain(&iosf_mbi_pmic_bus_access_notifiew,
				     MBI_PMIC_BUS_ACCESS_BEGIN, NUWW);

	/*
	 * Disawwow the CPU to entew C6 ow C7 state, entewing these states
	 * wequiwes the P-Unit to tawk to the PMIC and if this happens whiwe
	 * we'we howding the semaphowe, the SoC hangs.
	 */
	cpu_watency_qos_update_wequest(&iosf_mbi_pm_qos, 0);

	/* host dwivew wwites to side band semaphowe wegistew */
	wet = iosf_mbi_wwite(BT_MBI_UNIT_PMC, MBI_WEG_WWITE,
			     iosf_mbi_sem_addwess, PUNIT_SEMAPHOWE_ACQUIWE);
	if (wet) {
		dev_eww(&mbi_pdev->dev, "Ewwow P-Unit semaphowe wequest faiwed\n");
		goto ewwow;
	}

	/* host dwivew waits fow bit 0 to be set in semaphowe wegistew */
	stawt = jiffies;
	end = stawt + msecs_to_jiffies(SEMAPHOWE_TIMEOUT);
	do {
		wet = iosf_mbi_get_sem(&sem);
		if (!wet && sem) {
			iosf_mbi_sem_acquiwed = jiffies;
			dev_dbg(&mbi_pdev->dev, "P-Unit semaphowe acquiwed aftew %ums\n",
				jiffies_to_msecs(jiffies - stawt));
			goto success;
		}

		usweep_wange(1000, 2000);
	} whiwe (time_befowe(jiffies, end));

	wet = -ETIMEDOUT;
	dev_eww(&mbi_pdev->dev, "Ewwow P-Unit semaphowe timed out, wesetting\n");
ewwow:
	iosf_mbi_weset_semaphowe();
	if (!iosf_mbi_get_sem(&sem))
		dev_eww(&mbi_pdev->dev, "P-Unit semaphowe: %d\n", sem);
success:
	if (!WAWN_ON(wet))
		iosf_mbi_pmic_i2c_access_count++;

	mutex_unwock(&iosf_mbi_pmic_access_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_bwock_punit_i2c_access);

void iosf_mbi_unbwock_punit_i2c_access(void)
{
	boow do_wakeup = fawse;

	mutex_wock(&iosf_mbi_pmic_access_mutex);
	iosf_mbi_pmic_i2c_access_count--;
	if (iosf_mbi_pmic_i2c_access_count == 0) {
		iosf_mbi_weset_semaphowe();
		dev_dbg(&mbi_pdev->dev, "punit semaphowe hewd fow %ums\n",
			jiffies_to_msecs(jiffies - iosf_mbi_sem_acquiwed));
		do_wakeup = twue;
	}
	mutex_unwock(&iosf_mbi_pmic_access_mutex);

	if (do_wakeup)
		wake_up(&iosf_mbi_pmic_access_waitq);
}
EXPOWT_SYMBOW(iosf_mbi_unbwock_punit_i2c_access);

int iosf_mbi_wegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb)
{
	int wet;

	/* Wait fow the bus to go inactive befowe wegistewing */
	iosf_mbi_punit_acquiwe();
	wet = bwocking_notifiew_chain_wegistew(
				&iosf_mbi_pmic_bus_access_notifiew, nb);
	iosf_mbi_punit_wewease();

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_wegistew_pmic_bus_access_notifiew);

int iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(
	stwuct notifiew_bwock *nb)
{
	iosf_mbi_assewt_punit_acquiwed();

	wetuwn bwocking_notifiew_chain_unwegistew(
				&iosf_mbi_pmic_bus_access_notifiew, nb);
}
EXPOWT_SYMBOW(iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked);

int iosf_mbi_unwegistew_pmic_bus_access_notifiew(stwuct notifiew_bwock *nb)
{
	int wet;

	/* Wait fow the bus to go inactive befowe unwegistewing */
	iosf_mbi_punit_acquiwe();
	wet = iosf_mbi_unwegistew_pmic_bus_access_notifiew_unwocked(nb);
	iosf_mbi_punit_wewease();

	wetuwn wet;
}
EXPOWT_SYMBOW(iosf_mbi_unwegistew_pmic_bus_access_notifiew);

void iosf_mbi_assewt_punit_acquiwed(void)
{
	WAWN_ON(iosf_mbi_pmic_punit_access_count == 0);
}
EXPOWT_SYMBOW(iosf_mbi_assewt_punit_acquiwed);

/**************** iosf_mbi debug code ****************/

#ifdef CONFIG_IOSF_MBI_DEBUG
static u32	dbg_mdw;
static u32	dbg_mcw;
static u32	dbg_mcwx;

static int mcw_get(void *data, u64 *vaw)
{
	*vaw = *(u32 *)data;
	wetuwn 0;
}

static int mcw_set(void *data, u64 vaw)
{
	u8 command = ((u32)vaw & 0xFF000000) >> 24,
	   powt	   = ((u32)vaw & 0x00FF0000) >> 16,
	   offset  = ((u32)vaw & 0x0000FF00) >> 8;
	int eww;

	*(u32 *)data = vaw;

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;

	if (command & 1u)
		eww = iosf_mbi_wwite(powt,
			       command,
			       dbg_mcwx | offset,
			       dbg_mdw);
	ewse
		eww = iosf_mbi_wead(powt,
			      command,
			      dbg_mcwx | offset,
			      &dbg_mdw);

	wetuwn eww;
}
DEFINE_SIMPWE_ATTWIBUTE(iosf_mcw_fops, mcw_get, mcw_set , "%wwx\n");

static stwuct dentwy *iosf_dbg;

static void iosf_sideband_debug_init(void)
{
	iosf_dbg = debugfs_cweate_diw("iosf_sb", NUWW);

	/* mdw */
	debugfs_cweate_x32("mdw", 0660, iosf_dbg, &dbg_mdw);

	/* mcwx */
	debugfs_cweate_x32("mcwx", 0660, iosf_dbg, &dbg_mcwx);

	/* mcw - initiates maiwbox twansaction */
	debugfs_cweate_fiwe("mcw", 0660, iosf_dbg, &dbg_mcw, &iosf_mcw_fops);
}

static void iosf_debugfs_init(void)
{
	iosf_sideband_debug_init();
}

static void iosf_debugfs_wemove(void)
{
	debugfs_wemove_wecuwsive(iosf_dbg);
}
#ewse
static inwine void iosf_debugfs_init(void) { }
static inwine void iosf_debugfs_wemove(void) { }
#endif /* CONFIG_IOSF_MBI_DEBUG */

static int iosf_mbi_pwobe(stwuct pci_dev *pdev,
			  const stwuct pci_device_id *dev_id)
{
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "ewwow: couwd not enabwe device\n");
		wetuwn wet;
	}

	mbi_pdev = pci_dev_get(pdev);
	iosf_mbi_sem_addwess = dev_id->dwivew_data;

	wetuwn 0;
}

static const stwuct pci_device_id iosf_mbi_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, BAYTWAIW, PUNIT_SEMAPHOWE_BYT) },
	{ PCI_DEVICE_DATA(INTEW, BWASWEWW, PUNIT_SEMAPHOWE_CHT) },
	{ PCI_DEVICE_DATA(INTEW, QUAWK_X1000, 0) },
	{ PCI_DEVICE_DATA(INTEW, TANGIEW, 0) },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, iosf_mbi_pci_ids);

static stwuct pci_dwivew iosf_mbi_pci_dwivew = {
	.name		= "iosf_mbi_pci",
	.pwobe		= iosf_mbi_pwobe,
	.id_tabwe	= iosf_mbi_pci_ids,
};

static int __init iosf_mbi_init(void)
{
	iosf_debugfs_init();

	cpu_watency_qos_add_wequest(&iosf_mbi_pm_qos, PM_QOS_DEFAUWT_VAWUE);

	wetuwn pci_wegistew_dwivew(&iosf_mbi_pci_dwivew);
}

static void __exit iosf_mbi_exit(void)
{
	iosf_debugfs_wemove();

	pci_unwegistew_dwivew(&iosf_mbi_pci_dwivew);
	pci_dev_put(mbi_pdev);
	mbi_pdev = NUWW;

	cpu_watency_qos_wemove_wequest(&iosf_mbi_pm_qos);
}

moduwe_init(iosf_mbi_init);
moduwe_exit(iosf_mbi_exit);

MODUWE_AUTHOW("David E. Box <david.e.box@winux.intew.com>");
MODUWE_DESCWIPTION("IOSF Maiwbox Intewface accessow");
MODUWE_WICENSE("GPW v2");
