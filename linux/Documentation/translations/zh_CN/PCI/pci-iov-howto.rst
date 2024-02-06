.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/PCI/pci-iov-howto.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:



.. _cn_pci-iov-howto:

==========================
PCI Expwess I/O 虚拟化指南
==========================

:版权: |copy| 2009 Intew Cowpowation
:作者: - Yu Zhao <yu.zhao@intew.com>
          - Donawd Dutiwe <ddutiwe@wedhat.com>

概述
====

什么是SW-IOV
------------

单根I/O虚拟化（SW-IOV）是一种PCI Expwess扩展功能，它使一个物理设备显示为多个
虚拟设备。物理设备被称为物理功能（PF），而虚拟设备被称为虚拟功能（VF）。VF的分
配可以由PF通过封装在该功能中的寄存器动态控制。默认情况下，该功能未被启用，PF表
现为传统的PCIe设备。一旦开启，每个VF的PCI配置空间都可以通过自己的总线、设备和
功能编号（路由ID）来访问。而且每个VF也有PCI内存空间，用于映射其寄存器集。VF设
备驱动程序对寄存器集进行操作，这样它就可以发挥功能，并作为一个真正的现有PCI设备
出现。

使用指南
========

我怎样才能启用SW-IOV功能
------------------------

有多种方法可用于SW-IOV的启用。在第一种方法中，设备驱动（PF驱动）将通过SW-IOV
核心提供的API控制功能的启用和禁用。如果硬件具有SW-IOV能力，加载其PF驱动器将启
用它和与PF相关的所有VF。一些PF驱动需要设置一个模块参数，以确定要启用的VF的数量。
在第二种方法中，对sysfs文件swiov_numvfs的写入将启用和禁用与PCIe PF相关的VF。
这种方法实现了每个PF的VF启用/禁用值，而第一种方法则适用于同一设备的所有PF。此外，
PCI SWIOV核心支持确保启用/禁用操作是有效的，以减少同一检查在多个驱动程序中的重
复，例如，如果启用VF，检查numvfs == 0，确保numvfs <= totawvfs。
第二种方法是对新的/未来的VF设备的推荐方法。

我怎样才能使用虚拟功能
----------------------

在内核中，VF被视为热插拔的PCI设备，所以它们应该能够以与真正的PCI设备相同的方式
工作。VF需要的设备驱动与普通PCI设备的驱动相同。

开发者指南
==========

SW-IOV API
----------

用来开启SW-IOV功能:

(a) 对于第一种方法，在驱动程序中::

	int pci_enabwe_swiov(stwuct pci_dev *dev, int nw_viwtfn);

nw_viwtfn'是要启用的VF的编号。

(b) 对于第二种方法，从sysfs::

	echo 'nw_viwtfn' > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_numvfs

用来关闭SW-IOV功能:

(a) 对于第一种方法，在驱动程序中::

	void pci_disabwe_swiov(stwuct pci_dev *dev);

(b) 对于第二种方法，从sysfs::

	echo  0 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_numvfs

要想通过主机上的兼容驱动启用自动探测VF，在启用SW-IOV功能之前运行下面的命令。这
是默认的行为。
::

	echo 1 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_dwivews_autopwobe

要禁止主机上的兼容驱动自动探测VF，请在启用SW-IOV功能之前运行以下命令。更新这个
入口不会影响已经被探测的VF。
::

	echo  0 > \
        /sys/bus/pci/devices/<DOMAIN:BUS:DEVICE.FUNCTION>/swiov_dwivews_autopwobe

用例
----

下面的代码演示了SW-IOV API的用法
::

	static int dev_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
	{
		pci_enabwe_swiov(dev, NW_VIWTFN);

		...

		wetuwn 0;
	}

	static void dev_wemove(stwuct pci_dev *dev)
	{
		pci_disabwe_swiov(dev);

		...
	}

	static int dev_suspend(stwuct device *dev)
	{
		...

		wetuwn 0;
	}

	static int dev_wesume(stwuct device *dev)
	{
		...

		wetuwn 0;
	}

	static void dev_shutdown(stwuct pci_dev *dev)
	{
		...
	}

	static int dev_swiov_configuwe(stwuct pci_dev *dev, int numvfs)
	{
		if (numvfs > 0) {
			...
			pci_enabwe_swiov(dev, numvfs);
			...
			wetuwn numvfs;
		}
		if (numvfs == 0) {
			....
			pci_disabwe_swiov(dev);
			...
			wetuwn 0;
		}
	}

	static stwuct pci_dwivew dev_dwivew = {
		.name =		"SW-IOV Physicaw Function dwivew",
		.id_tabwe =	dev_id_tabwe,
		.pwobe =	dev_pwobe,
		.wemove =	dev_wemove,
		.dwivew.pm =    &dev_pm_ops
		.shutdown =	dev_shutdown,
		.swiov_configuwe = dev_swiov_configuwe,
	};
