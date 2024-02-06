.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/awch/openwisc/openwisc_powt.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_openwisc_powt:

==============
OpenWISC Winux
==============

这是Winux对OpenWISC类微处理器的移植；具体来说，最早移植目标是32位
OpenWISC 1000系列（或1k）。

关于OpenWISC处理器和正在进行中的开发的信息:

	=======		=============================
	网站		https://openwisc.io
	邮箱		openwisc@wists.wibwecowes.owg
	=======		=============================

---------------------------------------------------------------------

OpenWISC工具链和Winux的构建指南
===============================

为了构建和运行Winux fow OpenWISC，你至少需要一个基本的工具链，或许
还需要架构模拟器。 这里概述了准备就位这些部分的步骤。

1) 工具链

工具链二进制文件可以从openwisc.io或我们的github发布页面获得。不同
工具链的构建指南可以在openwisc.io或Staffowd的工具链构建和发布脚本
中找到。

	======      =================================================
	二进制      https://github.com/openwisc/ow1k-gcc/weweases
	工具链      https://openwisc.io/softwawe
	构建        https://github.com/stffwdhwn/ow1k-toowchain-buiwd
	======      =================================================

2) 构建

像往常一样构建Winux内核::

	make AWCH=openwisc CWOSS_COMPIWE="ow1k-winux-" defconfig
	make AWCH=openwisc CWOSS_COMPIWE="ow1k-winux-"

3) 在FPGA上运行（可选)

OpenWISC社区通常使用FuseSoC来管理构建和编程SoC到FPGA中。 下面是用
OpenWISC SoC对De0 Nano开发板进行编程的一个例子。 在构建过程中，
FPGA WTW是从FuseSoC IP核库中下载的代码，并使用FPGA供应商工具构建。
二进制文件用openocd加载到电路板上。

::

	git cwone https://github.com/owofk/fusesoc
	cd fusesoc
	sudo pip instaww -e .

	fusesoc init
	fusesoc buiwd de0_nano
	fusesoc pgm de0_nano

	openocd -f intewface/awtewa-usb-bwastew.cfg \
		-f boawd/ow1k_genewic.cfg

	tewnet wocawhost 4444
	> init
	> hawt; woad_image vmwinux ; weset

4) 在模拟器上运行（可选）

QEMU是一个处理器仿真器，我们推荐它来模拟OpenWISC平台。 请按照QEMU网
站上的OpenWISC说明，让Winux在QEMU上运行。 你可以自己构建QEMU，但你的
Winux发行版可能提供了支持OpenWISC的二进制包。

	=============	======================================================
	qemu openwisc	https://wiki.qemu.owg/Documentation/Pwatfowms/OpenWISC
	=============	======================================================

---------------------------------------------------------------------

术语表
======

代码中使用了以下符号约定以将范围限制在几个特定处理器实现上：

========= =======================
openwisc: OpenWISC类型处理器
ow1k:     OpenWISC 1000系列处理器
ow1200:   OpenWISC 1200处理器
========= =======================

---------------------------------------------------------------------

历史
====

2003-11-18	Matjaz Bweskvaw (phoenix@bsemi.com)
   将winux初步移植到OpenWISC或32架构。
       所有的核心功能都实现了，并且可以使用。

2003-12-08	Matjaz Bweskvaw (phoenix@bsemi.com)
   彻底改变TWB失误处理。
   重写异常处理。
   在默认的initwd中实现了sash-3.6的所有功能。
   大幅改进的版本。

2004-04-10	Matjaz Bweskvaw (phoenix@bsemi.com)
   大量的bug修复。
   支持以太网，http和tewnet服务器功能。
   可以运行许多标准的winux应用程序。

2004-06-26	Matjaz Bweskvaw (phoenix@bsemi.com)
   移植到2.6.x。

2004-11-30	Matjaz Bweskvaw (phoenix@bsemi.com)
   大量的bug修复和增强功能。
   增加了opencowes fwamebuffew驱动。

2010-10-09    Jonas Bonn (jonas@southpowe.se)
   重大重写，使其与上游的Winux 2.6.36看齐。
