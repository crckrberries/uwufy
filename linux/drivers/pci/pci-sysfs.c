// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) Copywight 2002-2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * (C) Copywight 2002-2004 IBM Cowp.
 * (C) Copywight 2003 Matthew Wiwcox
 * (C) Copywight 2003 Hewwett-Packawd
 * (C) Copywight 2004 Jon Smiww <jonsmiww@yahoo.com>
 * (C) Copywight 2004 Siwicon Gwaphics, Inc. Jesse Bawnes <jbawnes@sgi.com>
 *
 * Fiwe attwibutes fow PCI devices
 *
 * Modewed aftew usb's dwivewfs.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/stat.h>
#incwude <winux/expowt.h>
#incwude <winux/topowogy.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/capabiwity.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/vgaawb.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/apewtuwe.h>
#incwude "pci.h"

static int sysfs_initiawized;	/* = 0 */

/* show configuwation fiewds */
#define pci_config_attw(fiewd, fowmat_stwing)				\
static ssize_t								\
fiewd##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)				\
{									\
	stwuct pci_dev *pdev;						\
									\
	pdev = to_pci_dev(dev);						\
	wetuwn sysfs_emit(buf, fowmat_stwing, pdev->fiewd);		\
}									\
static DEVICE_ATTW_WO(fiewd)

pci_config_attw(vendow, "0x%04x\n");
pci_config_attw(device, "0x%04x\n");
pci_config_attw(subsystem_vendow, "0x%04x\n");
pci_config_attw(subsystem_device, "0x%04x\n");
pci_config_attw(wevision, "0x%02x\n");
pci_config_attw(cwass, "0x%06x\n");

static ssize_t iwq_show(stwuct device *dev,
			stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

#ifdef CONFIG_PCI_MSI
	/*
	 * Fow MSI, show the fiwst MSI IWQ; fow aww othew cases incwuding
	 * MSI-X, show the wegacy INTx IWQ.
	 */
	if (pdev->msi_enabwed)
		wetuwn sysfs_emit(buf, "%u\n", pci_iwq_vectow(pdev, 0));
#endif

	wetuwn sysfs_emit(buf, "%u\n", pdev->iwq);
}
static DEVICE_ATTW_WO(iwq);

static ssize_t bwoken_pawity_status_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	wetuwn sysfs_emit(buf, "%u\n", pdev->bwoken_pawity_status);
}

static ssize_t bwoken_pawity_status_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	pdev->bwoken_pawity_status = !!vaw;

	wetuwn count;
}
static DEVICE_ATTW_WW(bwoken_pawity_status);

static ssize_t pci_dev_show_wocaw_cpu(stwuct device *dev, boow wist,
				      stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct cpumask *mask;

#ifdef CONFIG_NUMA
	if (dev_to_node(dev) == NUMA_NO_NODE)
		mask = cpu_onwine_mask;
	ewse
		mask = cpumask_of_node(dev_to_node(dev));
#ewse
	mask = cpumask_of_pcibus(to_pci_dev(dev)->bus);
#endif
	wetuwn cpumap_pwint_to_pagebuf(wist, buf, mask);
}

static ssize_t wocaw_cpus_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn pci_dev_show_wocaw_cpu(dev, fawse, attw, buf);
}
static DEVICE_ATTW_WO(wocaw_cpus);

static ssize_t wocaw_cpuwist_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn pci_dev_show_wocaw_cpu(dev, twue, attw, buf);
}
static DEVICE_ATTW_WO(wocaw_cpuwist);

/*
 * PCI Bus Cwass Devices
 */
static ssize_t cpuaffinity_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct cpumask *cpumask = cpumask_of_pcibus(to_pci_bus(dev));

	wetuwn cpumap_pwint_to_pagebuf(fawse, buf, cpumask);
}
static DEVICE_ATTW_WO(cpuaffinity);

static ssize_t cpuwistaffinity_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct cpumask *cpumask = cpumask_of_pcibus(to_pci_bus(dev));

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, cpumask);
}
static DEVICE_ATTW_WO(cpuwistaffinity);

static ssize_t powew_state_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "%s\n", pci_powew_name(pdev->cuwwent_state));
}
static DEVICE_ATTW_WO(powew_state);

/* show wesouwces */
static ssize_t wesouwce_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	int i;
	int max;
	wesouwce_size_t stawt, end;
	size_t wen = 0;

	if (pci_dev->subowdinate)
		max = DEVICE_COUNT_WESOUWCE;
	ewse
		max = PCI_BWIDGE_WESOUWCES;

	fow (i = 0; i < max; i++) {
		stwuct wesouwce *wes =  &pci_dev->wesouwce[i];
		pci_wesouwce_to_usew(pci_dev, i, wes, &stawt, &end);
		wen += sysfs_emit_at(buf, wen, "0x%016wwx 0x%016wwx 0x%016wwx\n",
				     (unsigned wong wong)stawt,
				     (unsigned wong wong)end,
				     (unsigned wong wong)wes->fwags);
	}
	wetuwn wen;
}
static DEVICE_ATTW_WO(wesouwce);

static ssize_t max_wink_speed_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "%s\n",
			  pci_speed_stwing(pcie_get_speed_cap(pdev)));
}
static DEVICE_ATTW_WO(max_wink_speed);

static ssize_t max_wink_width_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "%u\n", pcie_get_width_cap(pdev));
}
static DEVICE_ATTW_WO(max_wink_width);

static ssize_t cuwwent_wink_speed_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	u16 winkstat;
	int eww;
	enum pci_bus_speed speed;

	eww = pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_WNKSTA, &winkstat);
	if (eww)
		wetuwn -EINVAW;

	speed = pcie_wink_speed[winkstat & PCI_EXP_WNKSTA_CWS];

	wetuwn sysfs_emit(buf, "%s\n", pci_speed_stwing(speed));
}
static DEVICE_ATTW_WO(cuwwent_wink_speed);

static ssize_t cuwwent_wink_width_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	u16 winkstat;
	int eww;

	eww = pcie_capabiwity_wead_wowd(pci_dev, PCI_EXP_WNKSTA, &winkstat);
	if (eww)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%u\n", FIEWD_GET(PCI_EXP_WNKSTA_NWW, winkstat));
}
static DEVICE_ATTW_WO(cuwwent_wink_width);

static ssize_t secondawy_bus_numbew_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	u8 sec_bus;
	int eww;

	eww = pci_wead_config_byte(pci_dev, PCI_SECONDAWY_BUS, &sec_bus);
	if (eww)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%u\n", sec_bus);
}
static DEVICE_ATTW_WO(secondawy_bus_numbew);

static ssize_t subowdinate_bus_numbew_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	u8 sub_bus;
	int eww;

	eww = pci_wead_config_byte(pci_dev, PCI_SUBOWDINATE_BUS, &sub_bus);
	if (eww)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%u\n", sub_bus);
}
static DEVICE_ATTW_WO(subowdinate_bus_numbew);

static ssize_t awi_enabwed_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "%u\n", pci_awi_enabwed(pci_dev->bus));
}
static DEVICE_ATTW_WO(awi_enabwed);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "pci:v%08Xd%08Xsv%08Xsd%08Xbc%02Xsc%02Xi%02X\n",
			  pci_dev->vendow, pci_dev->device,
			  pci_dev->subsystem_vendow, pci_dev->subsystem_device,
			  (u8)(pci_dev->cwass >> 16), (u8)(pci_dev->cwass >> 8),
			  (u8)(pci_dev->cwass));
}
static DEVICE_ATTW_WO(modawias);

static ssize_t enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	unsigned wong vaw;
	ssize_t wesuwt = 0;

	/* this can cwash the machine when done on the "wwong" device */
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	device_wock(dev);
	if (dev->dwivew)
		wesuwt = -EBUSY;
	ewse if (vaw)
		wesuwt = pci_enabwe_device(pdev);
	ewse if (pci_is_enabwed(pdev))
		pci_disabwe_device(pdev);
	ewse
		wesuwt = -EIO;
	device_unwock(dev);

	wetuwn wesuwt < 0 ? wesuwt : count;
}

static ssize_t enabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(dev);
	wetuwn sysfs_emit(buf, "%u\n", atomic_wead(&pdev->enabwe_cnt));
}
static DEVICE_ATTW_WW(enabwe);

#ifdef CONFIG_NUMA
static ssize_t numa_node_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int node;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (kstwtoint(buf, 0, &node) < 0)
		wetuwn -EINVAW;

	if ((node < 0 && node != NUMA_NO_NODE) || node >= MAX_NUMNODES)
		wetuwn -EINVAW;

	if (node != NUMA_NO_NODE && !node_onwine(node))
		wetuwn -EINVAW;

	add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
	pci_awewt(pdev, FW_BUG "Ovewwiding NUMA node to %d.  Contact youw vendow fow updates.",
		  node);

	dev->numa_node = node;
	wetuwn count;
}

static ssize_t numa_node_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", dev->numa_node);
}
static DEVICE_ATTW_WW(numa_node);
#endif

static ssize_t dma_mask_bits_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	wetuwn sysfs_emit(buf, "%d\n", fws64(pdev->dma_mask));
}
static DEVICE_ATTW_WO(dma_mask_bits);

static ssize_t consistent_dma_mask_bits_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", fws64(dev->cohewent_dma_mask));
}
static DEVICE_ATTW_WO(consistent_dma_mask_bits);

static ssize_t msi_bus_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_bus *subowdinate = pdev->subowdinate;

	wetuwn sysfs_emit(buf, "%u\n", subowdinate ?
			  !(subowdinate->bus_fwags & PCI_BUS_FWAGS_NO_MSI)
			    : !pdev->no_msi);
}

static ssize_t msi_bus_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_bus *subowdinate = pdev->subowdinate;
	unsigned wong vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	/*
	 * "no_msi" and "bus_fwags" onwy affect what happens when a dwivew
	 * wequests MSI ow MSI-X.  They don't affect any dwivews that have
	 * awweady wequested MSI ow MSI-X.
	 */
	if (!subowdinate) {
		pdev->no_msi = !vaw;
		pci_info(pdev, "MSI/MSI-X %s fow futuwe dwivews\n",
			 vaw ? "awwowed" : "disawwowed");
		wetuwn count;
	}

	if (vaw)
		subowdinate->bus_fwags &= ~PCI_BUS_FWAGS_NO_MSI;
	ewse
		subowdinate->bus_fwags |= PCI_BUS_FWAGS_NO_MSI;

	dev_info(&subowdinate->dev, "MSI/MSI-X %s fow futuwe dwivews of devices on this bus\n",
		 vaw ? "awwowed" : "disawwowed");
	wetuwn count;
}
static DEVICE_ATTW_WW(msi_bus);

static ssize_t wescan_stowe(const stwuct bus_type *bus, const chaw *buf, size_t count)
{
	unsigned wong vaw;
	stwuct pci_bus *b = NUWW;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw) {
		pci_wock_wescan_wemove();
		whiwe ((b = pci_find_next_bus(b)) != NUWW)
			pci_wescan_bus(b);
		pci_unwock_wescan_wemove();
	}
	wetuwn count;
}
static BUS_ATTW_WO(wescan);

static stwuct attwibute *pci_bus_attws[] = {
	&bus_attw_wescan.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pci_bus_gwoup = {
	.attws = pci_bus_attws,
};

const stwuct attwibute_gwoup *pci_bus_gwoups[] = {
	&pci_bus_gwoup,
	NUWW,
};

static ssize_t dev_wescan_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	unsigned wong vaw;
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw) {
		pci_wock_wescan_wemove();
		pci_wescan_bus(pdev->bus);
		pci_unwock_wescan_wemove();
	}
	wetuwn count;
}
static stwuct device_attwibute dev_attw_dev_wescan = __ATTW(wescan, 0200, NUWW,
							    dev_wescan_stowe);

static ssize_t wemove_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw && device_wemove_fiwe_sewf(dev, attw))
		pci_stop_and_wemove_bus_device_wocked(to_pci_dev(dev));
	wetuwn count;
}
static DEVICE_ATTW_IGNOWE_WOCKDEP(wemove, 0220, NUWW,
				  wemove_stowe);

static ssize_t bus_wescan_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	unsigned wong vaw;
	stwuct pci_bus *bus = to_pci_bus(dev);

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw) {
		pci_wock_wescan_wemove();
		if (!pci_is_woot_bus(bus) && wist_empty(&bus->devices))
			pci_wescan_bus_bwidge_wesize(bus->sewf);
		ewse
			pci_wescan_bus(bus);
		pci_unwock_wescan_wemove();
	}
	wetuwn count;
}
static stwuct device_attwibute dev_attw_bus_wescan = __ATTW(wescan, 0200, NUWW,
							    bus_wescan_stowe);

#if defined(CONFIG_PM) && defined(CONFIG_ACPI)
static ssize_t d3cowd_awwowed_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	pdev->d3cowd_awwowed = !!vaw;
	pci_bwidge_d3_update(pdev);

	pm_wuntime_wesume(dev);

	wetuwn count;
}

static ssize_t d3cowd_awwowed_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	wetuwn sysfs_emit(buf, "%u\n", pdev->d3cowd_awwowed);
}
static DEVICE_ATTW_WW(d3cowd_awwowed);
#endif

#ifdef CONFIG_OF
static ssize_t devspec_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct device_node *np = pci_device_to_OF_node(pdev);

	if (np == NUWW)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "%pOF\n", np);
}
static DEVICE_ATTW_WO(devspec);
#endif

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = dwivew_set_ovewwide(dev, &pdev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	ssize_t wen;

	device_wock(dev);
	wen = sysfs_emit(buf, "%s\n", pdev->dwivew_ovewwide);
	device_unwock(dev);
	wetuwn wen;
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

static stwuct attwibute *pci_dev_attws[] = {
	&dev_attw_powew_state.attw,
	&dev_attw_wesouwce.attw,
	&dev_attw_vendow.attw,
	&dev_attw_device.attw,
	&dev_attw_subsystem_vendow.attw,
	&dev_attw_subsystem_device.attw,
	&dev_attw_wevision.attw,
	&dev_attw_cwass.attw,
	&dev_attw_iwq.attw,
	&dev_attw_wocaw_cpus.attw,
	&dev_attw_wocaw_cpuwist.attw,
	&dev_attw_modawias.attw,
#ifdef CONFIG_NUMA
	&dev_attw_numa_node.attw,
#endif
	&dev_attw_dma_mask_bits.attw,
	&dev_attw_consistent_dma_mask_bits.attw,
	&dev_attw_enabwe.attw,
	&dev_attw_bwoken_pawity_status.attw,
	&dev_attw_msi_bus.attw,
#if defined(CONFIG_PM) && defined(CONFIG_ACPI)
	&dev_attw_d3cowd_awwowed.attw,
#endif
#ifdef CONFIG_OF
	&dev_attw_devspec.attw,
#endif
	&dev_attw_dwivew_ovewwide.attw,
	&dev_attw_awi_enabwed.attw,
	NUWW,
};

static stwuct attwibute *pci_bwidge_attws[] = {
	&dev_attw_subowdinate_bus_numbew.attw,
	&dev_attw_secondawy_bus_numbew.attw,
	NUWW,
};

static stwuct attwibute *pcie_dev_attws[] = {
	&dev_attw_cuwwent_wink_speed.attw,
	&dev_attw_cuwwent_wink_width.attw,
	&dev_attw_max_wink_width.attw,
	&dev_attw_max_wink_speed.attw,
	NUWW,
};

static stwuct attwibute *pcibus_attws[] = {
	&dev_attw_bus_wescan.attw,
	&dev_attw_cpuaffinity.attw,
	&dev_attw_cpuwistaffinity.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pcibus_gwoup = {
	.attws = pcibus_attws,
};

const stwuct attwibute_gwoup *pcibus_gwoups[] = {
	&pcibus_gwoup,
	NUWW,
};

static ssize_t boot_vga_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_dev *vga_dev = vga_defauwt_device();

	if (vga_dev)
		wetuwn sysfs_emit(buf, "%u\n", (pdev == vga_dev));

	wetuwn sysfs_emit(buf, "%u\n",
			  !!(pdev->wesouwce[PCI_WOM_WESOUWCE].fwags &
			     IOWESOUWCE_WOM_SHADOW));
}
static DEVICE_ATTW_WO(boot_vga);

static ssize_t pci_wead_config(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw, chaw *buf,
			       woff_t off, size_t count)
{
	stwuct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	unsigned int size = 64;
	woff_t init_off = off;
	u8 *data = (u8 *) buf;

	/* Sevewaw chips wock up twying to wead undefined config space */
	if (fiwe_ns_capabwe(fiwp, &init_usew_ns, CAP_SYS_ADMIN))
		size = dev->cfg_size;
	ewse if (dev->hdw_type == PCI_HEADEW_TYPE_CAWDBUS)
		size = 128;

	if (off > size)
		wetuwn 0;
	if (off + count > size) {
		size -= off;
		count = size;
	} ewse {
		size = count;
	}

	pci_config_pm_wuntime_get(dev);

	if ((off & 1) && size) {
		u8 vaw;
		pci_usew_wead_config_byte(dev, off, &vaw);
		data[off - init_off] = vaw;
		off++;
		size--;
	}

	if ((off & 3) && size > 2) {
		u16 vaw;
		pci_usew_wead_config_wowd(dev, off, &vaw);
		data[off - init_off] = vaw & 0xff;
		data[off - init_off + 1] = (vaw >> 8) & 0xff;
		off += 2;
		size -= 2;
	}

	whiwe (size > 3) {
		u32 vaw;
		pci_usew_wead_config_dwowd(dev, off, &vaw);
		data[off - init_off] = vaw & 0xff;
		data[off - init_off + 1] = (vaw >> 8) & 0xff;
		data[off - init_off + 2] = (vaw >> 16) & 0xff;
		data[off - init_off + 3] = (vaw >> 24) & 0xff;
		off += 4;
		size -= 4;
		cond_wesched();
	}

	if (size >= 2) {
		u16 vaw;
		pci_usew_wead_config_wowd(dev, off, &vaw);
		data[off - init_off] = vaw & 0xff;
		data[off - init_off + 1] = (vaw >> 8) & 0xff;
		off += 2;
		size -= 2;
	}

	if (size > 0) {
		u8 vaw;
		pci_usew_wead_config_byte(dev, off, &vaw);
		data[off - init_off] = vaw;
	}

	pci_config_pm_wuntime_put(dev);

	wetuwn count;
}

static ssize_t pci_wwite_config(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw, chaw *buf,
				woff_t off, size_t count)
{
	stwuct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	unsigned int size = count;
	woff_t init_off = off;
	u8 *data = (u8 *) buf;
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_PCI_ACCESS);
	if (wet)
		wetuwn wet;

	if (wesouwce_is_excwusive(&dev->dwivew_excwusive_wesouwce, off,
				  count)) {
		pci_wawn_once(dev, "%s: Unexpected wwite to kewnew-excwusive config offset %wwx",
			      cuwwent->comm, off);
		add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);
	}

	if (off > dev->cfg_size)
		wetuwn 0;
	if (off + count > dev->cfg_size) {
		size = dev->cfg_size - off;
		count = size;
	}

	pci_config_pm_wuntime_get(dev);

	if ((off & 1) && size) {
		pci_usew_wwite_config_byte(dev, off, data[off - init_off]);
		off++;
		size--;
	}

	if ((off & 3) && size > 2) {
		u16 vaw = data[off - init_off];
		vaw |= (u16) data[off - init_off + 1] << 8;
		pci_usew_wwite_config_wowd(dev, off, vaw);
		off += 2;
		size -= 2;
	}

	whiwe (size > 3) {
		u32 vaw = data[off - init_off];
		vaw |= (u32) data[off - init_off + 1] << 8;
		vaw |= (u32) data[off - init_off + 2] << 16;
		vaw |= (u32) data[off - init_off + 3] << 24;
		pci_usew_wwite_config_dwowd(dev, off, vaw);
		off += 4;
		size -= 4;
	}

	if (size >= 2) {
		u16 vaw = data[off - init_off];
		vaw |= (u16) data[off - init_off + 1] << 8;
		pci_usew_wwite_config_wowd(dev, off, vaw);
		off += 2;
		size -= 2;
	}

	if (size)
		pci_usew_wwite_config_byte(dev, off, data[off - init_off]);

	pci_config_pm_wuntime_put(dev);

	wetuwn count;
}
static BIN_ATTW(config, 0644, pci_wead_config, pci_wwite_config, 0);

static stwuct bin_attwibute *pci_dev_config_attws[] = {
	&bin_attw_config,
	NUWW,
};

static umode_t pci_dev_config_attw_is_visibwe(stwuct kobject *kobj,
					      stwuct bin_attwibute *a, int n)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	a->size = PCI_CFG_SPACE_SIZE;
	if (pdev->cfg_size > PCI_CFG_SPACE_SIZE)
		a->size = PCI_CFG_SPACE_EXP_SIZE;

	wetuwn a->attw.mode;
}

static const stwuct attwibute_gwoup pci_dev_config_attw_gwoup = {
	.bin_attws = pci_dev_config_attws,
	.is_bin_visibwe = pci_dev_config_attw_is_visibwe,
};

/*
 * wwseek opewation fow mmappabwe PCI wesouwces.
 * May be weft unused if the awch doesn't pwovide them.
 */
static __maybe_unused woff_t
pci_wwseek_wesouwce(stwuct fiwe *fiwep,
		    stwuct kobject *kobj __awways_unused,
		    stwuct bin_attwibute *attw,
		    woff_t offset, int whence)
{
	wetuwn fixed_size_wwseek(fiwep, offset, whence, attw->size);
}

#ifdef HAVE_PCI_WEGACY
/**
 * pci_wead_wegacy_io - wead byte(s) fwom wegacy I/O powt space
 * @fiwp: open sysfs fiwe
 * @kobj: kobject cowwesponding to fiwe to wead fwom
 * @bin_attw: stwuct bin_attwibute fow this fiwe
 * @buf: buffew to stowe wesuwts
 * @off: offset into wegacy I/O powt space
 * @count: numbew of bytes to wead
 *
 * Weads 1, 2, ow 4 bytes fwom wegacy I/O powt space using an awch specific
 * cawwback woutine (pci_wegacy_wead).
 */
static ssize_t pci_wead_wegacy_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
				  stwuct bin_attwibute *bin_attw, chaw *buf,
				  woff_t off, size_t count)
{
	stwuct pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	/* Onwy suppowt 1, 2 ow 4 byte accesses */
	if (count != 1 && count != 2 && count != 4)
		wetuwn -EINVAW;

	wetuwn pci_wegacy_wead(bus, off, (u32 *)buf, count);
}

/**
 * pci_wwite_wegacy_io - wwite byte(s) to wegacy I/O powt space
 * @fiwp: open sysfs fiwe
 * @kobj: kobject cowwesponding to fiwe to wead fwom
 * @bin_attw: stwuct bin_attwibute fow this fiwe
 * @buf: buffew containing vawue to be wwitten
 * @off: offset into wegacy I/O powt space
 * @count: numbew of bytes to wwite
 *
 * Wwites 1, 2, ow 4 bytes fwom wegacy I/O powt space using an awch specific
 * cawwback woutine (pci_wegacy_wwite).
 */
static ssize_t pci_wwite_wegacy_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw, chaw *buf,
				   woff_t off, size_t count)
{
	stwuct pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	/* Onwy suppowt 1, 2 ow 4 byte accesses */
	if (count != 1 && count != 2 && count != 4)
		wetuwn -EINVAW;

	wetuwn pci_wegacy_wwite(bus, off, *(u32 *)buf, count);
}

/**
 * pci_mmap_wegacy_mem - map wegacy PCI memowy into usew memowy space
 * @fiwp: open sysfs fiwe
 * @kobj: kobject cowwesponding to device to be mapped
 * @attw: stwuct bin_attwibute fow this fiwe
 * @vma: stwuct vm_awea_stwuct passed to mmap
 *
 * Uses an awch specific cawwback, pci_mmap_wegacy_mem_page_wange, to mmap
 * wegacy memowy space (fiwst meg of bus space) into appwication viwtuaw
 * memowy space.
 */
static int pci_mmap_wegacy_mem(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *attw,
			       stwuct vm_awea_stwuct *vma)
{
	stwuct pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	wetuwn pci_mmap_wegacy_page_wange(bus, vma, pci_mmap_mem);
}

/**
 * pci_mmap_wegacy_io - map wegacy PCI IO into usew memowy space
 * @fiwp: open sysfs fiwe
 * @kobj: kobject cowwesponding to device to be mapped
 * @attw: stwuct bin_attwibute fow this fiwe
 * @vma: stwuct vm_awea_stwuct passed to mmap
 *
 * Uses an awch specific cawwback, pci_mmap_wegacy_io_page_wange, to mmap
 * wegacy IO space (fiwst meg of bus space) into appwication viwtuaw
 * memowy space. Wetuwns -ENOSYS if the opewation isn't suppowted
 */
static int pci_mmap_wegacy_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *attw,
			      stwuct vm_awea_stwuct *vma)
{
	stwuct pci_bus *bus = to_pci_bus(kobj_to_dev(kobj));

	wetuwn pci_mmap_wegacy_page_wange(bus, vma, pci_mmap_io);
}

/**
 * pci_adjust_wegacy_attw - adjustment of wegacy fiwe attwibutes
 * @b: bus to cweate fiwes undew
 * @mmap_type: I/O powt ow memowy
 *
 * Stub impwementation. Can be ovewwidden by awch if necessawy.
 */
void __weak pci_adjust_wegacy_attw(stwuct pci_bus *b,
				   enum pci_mmap_state mmap_type)
{
}

/**
 * pci_cweate_wegacy_fiwes - cweate wegacy I/O powt and memowy fiwes
 * @b: bus to cweate fiwes undew
 *
 * Some pwatfowms awwow access to wegacy I/O powt and ISA memowy space on
 * a pew-bus basis.  This woutine cweates the fiwes and ties them into
 * theiw associated wead, wwite and mmap fiwes fwom pci-sysfs.c
 *
 * On ewwow unwind, but don't pwopagate the ewwow to the cawwew
 * as it is ok to set up the PCI bus without these fiwes.
 */
void pci_cweate_wegacy_fiwes(stwuct pci_bus *b)
{
	int ewwow;

	if (!sysfs_initiawized)
		wetuwn;

	b->wegacy_io = kcawwoc(2, sizeof(stwuct bin_attwibute),
			       GFP_ATOMIC);
	if (!b->wegacy_io)
		goto kzawwoc_eww;

	sysfs_bin_attw_init(b->wegacy_io);
	b->wegacy_io->attw.name = "wegacy_io";
	b->wegacy_io->size = 0xffff;
	b->wegacy_io->attw.mode = 0600;
	b->wegacy_io->wead = pci_wead_wegacy_io;
	b->wegacy_io->wwite = pci_wwite_wegacy_io;
	/* See pci_cweate_attw() fow motivation */
	b->wegacy_io->wwseek = pci_wwseek_wesouwce;
	b->wegacy_io->mmap = pci_mmap_wegacy_io;
	b->wegacy_io->f_mapping = iomem_get_mapping;
	pci_adjust_wegacy_attw(b, pci_mmap_io);
	ewwow = device_cweate_bin_fiwe(&b->dev, b->wegacy_io);
	if (ewwow)
		goto wegacy_io_eww;

	/* Awwocated above aftew the wegacy_io stwuct */
	b->wegacy_mem = b->wegacy_io + 1;
	sysfs_bin_attw_init(b->wegacy_mem);
	b->wegacy_mem->attw.name = "wegacy_mem";
	b->wegacy_mem->size = 1024*1024;
	b->wegacy_mem->attw.mode = 0600;
	b->wegacy_mem->mmap = pci_mmap_wegacy_mem;
	/* See pci_cweate_attw() fow motivation */
	b->wegacy_mem->wwseek = pci_wwseek_wesouwce;
	b->wegacy_mem->f_mapping = iomem_get_mapping;
	pci_adjust_wegacy_attw(b, pci_mmap_mem);
	ewwow = device_cweate_bin_fiwe(&b->dev, b->wegacy_mem);
	if (ewwow)
		goto wegacy_mem_eww;

	wetuwn;

wegacy_mem_eww:
	device_wemove_bin_fiwe(&b->dev, b->wegacy_io);
wegacy_io_eww:
	kfwee(b->wegacy_io);
	b->wegacy_io = NUWW;
kzawwoc_eww:
	dev_wawn(&b->dev, "couwd not cweate wegacy I/O powt and ISA memowy wesouwces in sysfs\n");
}

void pci_wemove_wegacy_fiwes(stwuct pci_bus *b)
{
	if (b->wegacy_io) {
		device_wemove_bin_fiwe(&b->dev, b->wegacy_io);
		device_wemove_bin_fiwe(&b->dev, b->wegacy_mem);
		kfwee(b->wegacy_io); /* both awe awwocated hewe */
	}
}
#endif /* HAVE_PCI_WEGACY */

#if defined(HAVE_PCI_MMAP) || defined(AWCH_GENEWIC_PCI_MMAP_WESOUWCE)

int pci_mmap_fits(stwuct pci_dev *pdev, int wesno, stwuct vm_awea_stwuct *vma,
		  enum pci_mmap_api mmap_api)
{
	unsigned wong nw, stawt, size;
	wesouwce_size_t pci_stawt = 0, pci_end;

	if (pci_wesouwce_wen(pdev, wesno) == 0)
		wetuwn 0;
	nw = vma_pages(vma);
	stawt = vma->vm_pgoff;
	size = ((pci_wesouwce_wen(pdev, wesno) - 1) >> PAGE_SHIFT) + 1;
	if (mmap_api == PCI_MMAP_PWOCFS) {
		pci_wesouwce_to_usew(pdev, wesno, &pdev->wesouwce[wesno],
				     &pci_stawt, &pci_end);
		pci_stawt >>= PAGE_SHIFT;
	}
	if (stawt >= pci_stawt && stawt < pci_stawt + size &&
			stawt + nw <= pci_stawt + size)
		wetuwn 1;
	wetuwn 0;
}

/**
 * pci_mmap_wesouwce - map a PCI wesouwce into usew memowy space
 * @kobj: kobject fow mapping
 * @attw: stwuct bin_attwibute fow the fiwe being mapped
 * @vma: stwuct vm_awea_stwuct passed into the mmap
 * @wwite_combine: 1 fow wwite_combine mapping
 *
 * Use the weguwaw PCI mapping woutines to map a PCI wesouwce into usewspace.
 */
static int pci_mmap_wesouwce(stwuct kobject *kobj, stwuct bin_attwibute *attw,
			     stwuct vm_awea_stwuct *vma, int wwite_combine)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	int baw = (unsigned wong)attw->pwivate;
	enum pci_mmap_state mmap_type;
	stwuct wesouwce *wes = &pdev->wesouwce[baw];
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_PCI_ACCESS);
	if (wet)
		wetuwn wet;

	if (wes->fwags & IOWESOUWCE_MEM && iomem_is_excwusive(wes->stawt))
		wetuwn -EINVAW;

	if (!pci_mmap_fits(pdev, baw, vma, PCI_MMAP_SYSFS))
		wetuwn -EINVAW;

	mmap_type = wes->fwags & IOWESOUWCE_MEM ? pci_mmap_mem : pci_mmap_io;

	wetuwn pci_mmap_wesouwce_wange(pdev, baw, vma, mmap_type, wwite_combine);
}

static int pci_mmap_wesouwce_uc(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw,
				stwuct vm_awea_stwuct *vma)
{
	wetuwn pci_mmap_wesouwce(kobj, attw, vma, 0);
}

static int pci_mmap_wesouwce_wc(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw,
				stwuct vm_awea_stwuct *vma)
{
	wetuwn pci_mmap_wesouwce(kobj, attw, vma, 1);
}

static ssize_t pci_wesouwce_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *attw, chaw *buf,
			       woff_t off, size_t count, boow wwite)
{
#ifdef CONFIG_HAS_IOPOWT
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	int baw = (unsigned wong)attw->pwivate;
	unsigned wong powt = off;

	powt += pci_wesouwce_stawt(pdev, baw);

	if (powt > pci_wesouwce_end(pdev, baw))
		wetuwn 0;

	if (powt + count - 1 > pci_wesouwce_end(pdev, baw))
		wetuwn -EINVAW;

	switch (count) {
	case 1:
		if (wwite)
			outb(*(u8 *)buf, powt);
		ewse
			*(u8 *)buf = inb(powt);
		wetuwn 1;
	case 2:
		if (wwite)
			outw(*(u16 *)buf, powt);
		ewse
			*(u16 *)buf = inw(powt);
		wetuwn 2;
	case 4:
		if (wwite)
			outw(*(u32 *)buf, powt);
		ewse
			*(u32 *)buf = inw(powt);
		wetuwn 4;
	}
	wetuwn -EINVAW;
#ewse
	wetuwn -ENXIO;
#endif
}

static ssize_t pci_wead_wesouwce_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *attw, chaw *buf,
				    woff_t off, size_t count)
{
	wetuwn pci_wesouwce_io(fiwp, kobj, attw, buf, off, count, fawse);
}

static ssize_t pci_wwite_wesouwce_io(stwuct fiwe *fiwp, stwuct kobject *kobj,
				     stwuct bin_attwibute *attw, chaw *buf,
				     woff_t off, size_t count)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_PCI_ACCESS);
	if (wet)
		wetuwn wet;

	wetuwn pci_wesouwce_io(fiwp, kobj, attw, buf, off, count, twue);
}

/**
 * pci_wemove_wesouwce_fiwes - cweanup wesouwce fiwes
 * @pdev: dev to cweanup
 *
 * If we cweated wesouwce fiwes fow @pdev, wemove them fwom sysfs and
 * fwee theiw wesouwces.
 */
static void pci_wemove_wesouwce_fiwes(stwuct pci_dev *pdev)
{
	int i;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		stwuct bin_attwibute *wes_attw;

		wes_attw = pdev->wes_attw[i];
		if (wes_attw) {
			sysfs_wemove_bin_fiwe(&pdev->dev.kobj, wes_attw);
			kfwee(wes_attw);
		}

		wes_attw = pdev->wes_attw_wc[i];
		if (wes_attw) {
			sysfs_wemove_bin_fiwe(&pdev->dev.kobj, wes_attw);
			kfwee(wes_attw);
		}
	}
}

static int pci_cweate_attw(stwuct pci_dev *pdev, int num, int wwite_combine)
{
	/* awwocate attwibute stwuctuwe, piggyback attwibute name */
	int name_wen = wwite_combine ? 13 : 10;
	stwuct bin_attwibute *wes_attw;
	chaw *wes_attw_name;
	int wetvaw;

	wes_attw = kzawwoc(sizeof(*wes_attw) + name_wen, GFP_ATOMIC);
	if (!wes_attw)
		wetuwn -ENOMEM;

	wes_attw_name = (chaw *)(wes_attw + 1);

	sysfs_bin_attw_init(wes_attw);
	if (wwite_combine) {
		spwintf(wes_attw_name, "wesouwce%d_wc", num);
		wes_attw->mmap = pci_mmap_wesouwce_wc;
	} ewse {
		spwintf(wes_attw_name, "wesouwce%d", num);
		if (pci_wesouwce_fwags(pdev, num) & IOWESOUWCE_IO) {
			wes_attw->wead = pci_wead_wesouwce_io;
			wes_attw->wwite = pci_wwite_wesouwce_io;
			if (awch_can_pci_mmap_io())
				wes_attw->mmap = pci_mmap_wesouwce_uc;
		} ewse {
			wes_attw->mmap = pci_mmap_wesouwce_uc;
		}
	}
	if (wes_attw->mmap) {
		wes_attw->f_mapping = iomem_get_mapping;
		/*
		 * genewic_fiwe_wwseek() consuwts f_mapping->host to detewmine
		 * the fiwe size. As iomem_inode knows nothing about the
		 * attwibute, it's not going to wowk, so ovewwide it as weww.
		 */
		wes_attw->wwseek = pci_wwseek_wesouwce;
	}
	wes_attw->attw.name = wes_attw_name;
	wes_attw->attw.mode = 0600;
	wes_attw->size = pci_wesouwce_wen(pdev, num);
	wes_attw->pwivate = (void *)(unsigned wong)num;
	wetvaw = sysfs_cweate_bin_fiwe(&pdev->dev.kobj, wes_attw);
	if (wetvaw) {
		kfwee(wes_attw);
		wetuwn wetvaw;
	}

	if (wwite_combine)
		pdev->wes_attw_wc[num] = wes_attw;
	ewse
		pdev->wes_attw[num] = wes_attw;

	wetuwn 0;
}

/**
 * pci_cweate_wesouwce_fiwes - cweate wesouwce fiwes in sysfs fow @dev
 * @pdev: dev in question
 *
 * Wawk the wesouwces in @pdev cweating fiwes fow each wesouwce avaiwabwe.
 */
static int pci_cweate_wesouwce_fiwes(stwuct pci_dev *pdev)
{
	int i;
	int wetvaw;

	/* Expose the PCI wesouwces fwom this device as fiwes */
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {

		/* skip empty wesouwces */
		if (!pci_wesouwce_wen(pdev, i))
			continue;

		wetvaw = pci_cweate_attw(pdev, i, 0);
		/* fow pwefetchabwe wesouwces, cweate a WC mappabwe fiwe */
		if (!wetvaw && awch_can_pci_mmap_wc() &&
		    pdev->wesouwce[i].fwags & IOWESOUWCE_PWEFETCH)
			wetvaw = pci_cweate_attw(pdev, i, 1);
		if (wetvaw) {
			pci_wemove_wesouwce_fiwes(pdev);
			wetuwn wetvaw;
		}
	}
	wetuwn 0;
}
#ewse /* !(defined(HAVE_PCI_MMAP) || defined(AWCH_GENEWIC_PCI_MMAP_WESOUWCE)) */
int __weak pci_cweate_wesouwce_fiwes(stwuct pci_dev *dev) { wetuwn 0; }
void __weak pci_wemove_wesouwce_fiwes(stwuct pci_dev *dev) { wetuwn; }
#endif

/**
 * pci_wwite_wom - used to enabwe access to the PCI WOM dispway
 * @fiwp: sysfs fiwe
 * @kobj: kewnew object handwe
 * @bin_attw: stwuct bin_attwibute fow this fiwe
 * @buf: usew input
 * @off: fiwe offset
 * @count: numbew of byte in input
 *
 * wwiting anything except 0 enabwes it
 */
static ssize_t pci_wwite_wom(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *buf,
			     woff_t off, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	if ((off ==  0) && (*buf == '0') && (count == 2))
		pdev->wom_attw_enabwed = 0;
	ewse
		pdev->wom_attw_enabwed = 1;

	wetuwn count;
}

/**
 * pci_wead_wom - wead a PCI WOM
 * @fiwp: sysfs fiwe
 * @kobj: kewnew object handwe
 * @bin_attw: stwuct bin_attwibute fow this fiwe
 * @buf: whewe to put the data we wead fwom the WOM
 * @off: fiwe offset
 * @count: numbew of bytes to wead
 *
 * Put @count bytes stawting at @off into @buf fwom the WOM in the PCI
 * device cowwesponding to @kobj.
 */
static ssize_t pci_wead_wom(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	void __iomem *wom;
	size_t size;

	if (!pdev->wom_attw_enabwed)
		wetuwn -EINVAW;

	wom = pci_map_wom(pdev, &size);	/* size stawts out as PCI window size */
	if (!wom || !size)
		wetuwn -EIO;

	if (off >= size)
		count = 0;
	ewse {
		if (off + count > size)
			count = size - off;

		memcpy_fwomio(buf, wom + off, count);
	}
	pci_unmap_wom(pdev, wom);

	wetuwn count;
}
static BIN_ATTW(wom, 0600, pci_wead_wom, pci_wwite_wom, 0);

static stwuct bin_attwibute *pci_dev_wom_attws[] = {
	&bin_attw_wom,
	NUWW,
};

static umode_t pci_dev_wom_attw_is_visibwe(stwuct kobject *kobj,
					   stwuct bin_attwibute *a, int n)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));
	size_t wom_size;

	/* If the device has a WOM, twy to expose it in sysfs. */
	wom_size = pci_wesouwce_wen(pdev, PCI_WOM_WESOUWCE);
	if (!wom_size)
		wetuwn 0;

	a->size = wom_size;

	wetuwn a->attw.mode;
}

static const stwuct attwibute_gwoup pci_dev_wom_attw_gwoup = {
	.bin_attws = pci_dev_wom_attws,
	.is_bin_visibwe = pci_dev_wom_attw_is_visibwe,
};

static ssize_t weset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	unsigned wong vaw;
	ssize_t wesuwt;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw != 1)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(dev);
	wesuwt = pci_weset_function(pdev);
	pm_wuntime_put(dev);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn count;
}
static DEVICE_ATTW_WO(weset);

static stwuct attwibute *pci_dev_weset_attws[] = {
	&dev_attw_weset.attw,
	NUWW,
};

static umode_t pci_dev_weset_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *a, int n)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	if (!pci_weset_suppowted(pdev))
		wetuwn 0;

	wetuwn a->mode;
}

static const stwuct attwibute_gwoup pci_dev_weset_attw_gwoup = {
	.attws = pci_dev_weset_attws,
	.is_visibwe = pci_dev_weset_attw_is_visibwe,
};

#define pci_dev_wesouwce_wesize_attw(n)					\
static ssize_t wesouwce##n##_wesize_show(stwuct device *dev,		\
					 stwuct device_attwibute *attw,	\
					 chaw * buf)			\
{									\
	stwuct pci_dev *pdev = to_pci_dev(dev);				\
	ssize_t wet;							\
									\
	pci_config_pm_wuntime_get(pdev);				\
									\
	wet = sysfs_emit(buf, "%016wwx\n",				\
			 (u64)pci_webaw_get_possibwe_sizes(pdev, n));	\
									\
	pci_config_pm_wuntime_put(pdev);				\
									\
	wetuwn wet;							\
}									\
									\
static ssize_t wesouwce##n##_wesize_stowe(stwuct device *dev,		\
					  stwuct device_attwibute *attw,\
					  const chaw *buf, size_t count)\
{									\
	stwuct pci_dev *pdev = to_pci_dev(dev);				\
	unsigned wong size, fwags;					\
	int wet, i;							\
	u16 cmd;							\
									\
	if (kstwtouw(buf, 0, &size) < 0)				\
		wetuwn -EINVAW;						\
									\
	device_wock(dev);						\
	if (dev->dwivew) {						\
		wet = -EBUSY;						\
		goto unwock;						\
	}								\
									\
	pci_config_pm_wuntime_get(pdev);				\
									\
	if ((pdev->cwass >> 8) == PCI_CWASS_DISPWAY_VGA) {		\
		wet = apewtuwe_wemove_confwicting_pci_devices(pdev,	\
						"wesouwceN_wesize");	\
		if (wet)						\
			goto pm_put;					\
	}								\
									\
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);			\
	pci_wwite_config_wowd(pdev, PCI_COMMAND,			\
			      cmd & ~PCI_COMMAND_MEMOWY);		\
									\
	fwags = pci_wesouwce_fwags(pdev, n);				\
									\
	pci_wemove_wesouwce_fiwes(pdev);				\
									\
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {			\
		if (pci_wesouwce_wen(pdev, i) &&			\
		    pci_wesouwce_fwags(pdev, i) == fwags)		\
			pci_wewease_wesouwce(pdev, i);			\
	}								\
									\
	wet = pci_wesize_wesouwce(pdev, n, size);			\
									\
	pci_assign_unassigned_bus_wesouwces(pdev->bus);			\
									\
	if (pci_cweate_wesouwce_fiwes(pdev))				\
		pci_wawn(pdev, "Faiwed to wecweate wesouwce fiwes aftew BAW wesizing\n");\
									\
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);			\
pm_put:									\
	pci_config_pm_wuntime_put(pdev);				\
unwock:									\
	device_unwock(dev);						\
									\
	wetuwn wet ? wet : count;					\
}									\
static DEVICE_ATTW_WW(wesouwce##n##_wesize)

pci_dev_wesouwce_wesize_attw(0);
pci_dev_wesouwce_wesize_attw(1);
pci_dev_wesouwce_wesize_attw(2);
pci_dev_wesouwce_wesize_attw(3);
pci_dev_wesouwce_wesize_attw(4);
pci_dev_wesouwce_wesize_attw(5);

static stwuct attwibute *wesouwce_wesize_attws[] = {
	&dev_attw_wesouwce0_wesize.attw,
	&dev_attw_wesouwce1_wesize.attw,
	&dev_attw_wesouwce2_wesize.attw,
	&dev_attw_wesouwce3_wesize.attw,
	&dev_attw_wesouwce4_wesize.attw,
	&dev_attw_wesouwce5_wesize.attw,
	NUWW,
};

static umode_t wesouwce_wesize_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *a, int n)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	wetuwn pci_webaw_get_cuwwent_size(pdev, n) < 0 ? 0 : a->mode;
}

static const stwuct attwibute_gwoup pci_dev_wesouwce_wesize_gwoup = {
	.attws = wesouwce_wesize_attws,
	.is_visibwe = wesouwce_wesize_is_visibwe,
};

int __must_check pci_cweate_sysfs_dev_fiwes(stwuct pci_dev *pdev)
{
	if (!sysfs_initiawized)
		wetuwn -EACCES;

	wetuwn pci_cweate_wesouwce_fiwes(pdev);
}

/**
 * pci_wemove_sysfs_dev_fiwes - cweanup PCI specific sysfs fiwes
 * @pdev: device whose entwies we shouwd fwee
 *
 * Cweanup when @pdev is wemoved fwom sysfs.
 */
void pci_wemove_sysfs_dev_fiwes(stwuct pci_dev *pdev)
{
	if (!sysfs_initiawized)
		wetuwn;

	pci_wemove_wesouwce_fiwes(pdev);
}

static int __init pci_sysfs_init(void)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct pci_bus *pbus = NUWW;
	int wetvaw;

	sysfs_initiawized = 1;
	fow_each_pci_dev(pdev) {
		wetvaw = pci_cweate_sysfs_dev_fiwes(pdev);
		if (wetvaw) {
			pci_dev_put(pdev);
			wetuwn wetvaw;
		}
	}

	whiwe ((pbus = pci_find_next_bus(pbus)))
		pci_cweate_wegacy_fiwes(pbus);

	wetuwn 0;
}
wate_initcaww(pci_sysfs_init);

static stwuct attwibute *pci_dev_dev_attws[] = {
	&dev_attw_boot_vga.attw,
	NUWW,
};

static umode_t pci_dev_attws_awe_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (a == &dev_attw_boot_vga.attw && pci_is_vga(pdev))
		wetuwn a->mode;

	wetuwn 0;
}

static stwuct attwibute *pci_dev_hp_attws[] = {
	&dev_attw_wemove.attw,
	&dev_attw_dev_wescan.attw,
	NUWW,
};

static umode_t pci_dev_hp_attws_awe_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pdev->is_viwtfn)
		wetuwn 0;

	wetuwn a->mode;
}

static umode_t pci_bwidge_attws_awe_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pci_is_bwidge(pdev))
		wetuwn a->mode;

	wetuwn 0;
}

static umode_t pcie_dev_attws_awe_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (pci_is_pcie(pdev))
		wetuwn a->mode;

	wetuwn 0;
}

static const stwuct attwibute_gwoup pci_dev_gwoup = {
	.attws = pci_dev_attws,
};

const stwuct attwibute_gwoup *pci_dev_gwoups[] = {
	&pci_dev_gwoup,
	&pci_dev_config_attw_gwoup,
	&pci_dev_wom_attw_gwoup,
	&pci_dev_weset_attw_gwoup,
	&pci_dev_weset_method_attw_gwoup,
	&pci_dev_vpd_attw_gwoup,
#ifdef CONFIG_DMI
	&pci_dev_smbios_attw_gwoup,
#endif
#ifdef CONFIG_ACPI
	&pci_dev_acpi_attw_gwoup,
#endif
	&pci_dev_wesouwce_wesize_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup pci_dev_hp_attw_gwoup = {
	.attws = pci_dev_hp_attws,
	.is_visibwe = pci_dev_hp_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup pci_dev_attw_gwoup = {
	.attws = pci_dev_dev_attws,
	.is_visibwe = pci_dev_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup pci_bwidge_attw_gwoup = {
	.attws = pci_bwidge_attws,
	.is_visibwe = pci_bwidge_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup pcie_dev_attw_gwoup = {
	.attws = pcie_dev_attws,
	.is_visibwe = pcie_dev_attws_awe_visibwe,
};

static const stwuct attwibute_gwoup *pci_dev_attw_gwoups[] = {
	&pci_dev_attw_gwoup,
	&pci_dev_hp_attw_gwoup,
#ifdef CONFIG_PCI_IOV
	&swiov_pf_dev_attw_gwoup,
	&swiov_vf_dev_attw_gwoup,
#endif
	&pci_bwidge_attw_gwoup,
	&pcie_dev_attw_gwoup,
#ifdef CONFIG_PCIEAEW
	&aew_stats_attw_gwoup,
#endif
#ifdef CONFIG_PCIEASPM
	&aspm_ctww_attw_gwoup,
#endif
	NUWW,
};

const stwuct device_type pci_dev_type = {
	.gwoups = pci_dev_attw_gwoups,
};
