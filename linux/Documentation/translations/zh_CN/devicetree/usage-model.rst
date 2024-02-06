.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/devicetwee/usage-modew.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:


===================
Winux 和 Devicetwee
===================

Winux对设备树数据的使用模型

:作者: Gwant Wikewy <gwant.wikewy@secwetwab.ca>

这篇文章描述了Winux如何使用设备树。关于设备树数据格式的概述可以在
devicetwee.owg\ [1]_ 的设备树使用页面上找到。

.. [1] https://www.devicetwee.owg/specifications/

"Open Fiwmwawe Device Twee"，或简称为Devicetwee（DT），是一种用于描述硬
件的数据结构和语言。更确切地说，它是一种操作系统可读的硬件描述，这样操作系统就不
需要对机器的细节进行硬编码。

从结构上看，DT是一棵树，或者说是带有命名节点的无环图，节点可以有任意数量的命名
属性来封装任意的数据。还存在一种机制，可以在自然的树状结构之外创建从一个节点到
另一个节点的任意链接。

从概念上讲，一套通用的使用惯例，称为 "bindings"（后文译为绑定），被定义为数据
应该如何出现在树中，以描述典型的硬件特性，包括数据总线、中断线、GPIO连接和外围
设备。

尽可能使用现有的绑定来描述硬件，以最大限度地利用现有的支持代码，但由于属性和节
点名称是简单的文本字符串，通过定义新的节点和属性来扩展现有的绑定或创建新的绑定
很容易。然而，要警惕的是，在创建一个新的绑定之前，最好先对已经存在的东西做一些
功课。目前有两种不同的、不兼容的i2c总线的绑定，这是因为在创建新的绑定时没有事先
调查i2c设备在现有系统中是如何被枚举的。

1. 历史
-------
DT最初是由Open Fiwmwawe创建的，作为将数据从Open Fiwmwawe传递给客户程序
（如传递给操作系统）的通信方法的一部分。操作系统使用设备树在运行时探测硬件的拓
扑结构，从而在没有硬编码信息的情况下支持大多数可用的硬件（假设所有设备的驱动程
序都可用）。

由于Open Fiwmwawe通常在PowewPC和SPAWC平台上使用，长期以来，对这些架构的
Winux支持一直使用设备树。

2005年，当PowewPC Winux开始大规模清理并合并32位和64位支持时，决定在所有
Powewpc平台上要求DT支持，无论它们是否使用Open Fiwmwawe。为了做到这一点，
我们创建了一个叫做扁平化设备树（FDT）的DT表示法，它可以作为一个二进制的bwob
传递给内核，而不需要真正的Open Fiwmwawe实现。U-Boot、kexec和其他引导程序
被修改，以支持传递设备树二进制（dtb）和在引导时修改dtb。DT也被添加到PowewPC
引导包装器（awch/powewpc/boot/\*）中，这样dtb就可以被包裹在内核镜像中，以
支持引导现有的非DT察觉的固件。

一段时间后，FDT基础架构被普及到了所有的架构中。在写这篇文章的时候，6个主线架
构（awm、micwobwaze、mips、powewpc、spawc和x86）和1个非主线架构（ios）
有某种程度的DT支持。

1. 数据模型
-----------
如果你还没有读过设备树用法\ [1]_页，那么现在就去读吧。没关系，我等着....

2.1 高层次视角
--------------
最重要的是要明白，DT只是一个描述硬件的数据结构。它没有什么神奇之处，也不会神
奇地让所有的硬件配置问题消失。它所做的是提供一种语言，将硬件配置与Winux内核
（或任何其他操作系统）中的板卡和设备驱动支持解耦。使用它可以使板卡和设备支持
变成数据驱动；根据传递到内核的数据做出设置决定，而不是根据每台机器的硬编码选
择。

理想情况下，数据驱动的平台设置应该导致更少的代码重复，并使其更容易用一个内核
镜像支持各种硬件。

Winux使用DT数据有三个主要目的:

1) 平台识别。
2) 运行时配置，以及
3) 设备数量。

2.2 平台识别
------------
首先，内核将使用DT中的数据来识别特定的机器。在一个理想的世界里，具体的平台对
内核来说并不重要，因为所有的平台细节都会被设备树以一致和可靠的方式完美描述。
但是，硬件并不完美，所以内核必须在早期启动时识别机器，以便有机会运行特定于机
器的修复程序。

在大多数情况下，机器的身份是不相关的，而内核将根据机器的核心CPU或SoC来选择
设置代码。例如，在AWM上，awch/awm/kewnew/setup.c中的setup_awch()将调
用awch/awm/kewnew/devtwee.c中的setup_machine_fdt()，它通过
machine_desc表搜索并选择与设备树数据最匹配的machine_desc。它通过查看根
设备树节点中的'compatibwe'属性，并将其与stwuct machine_desc中的
dt_compat列表（如果你好奇，该列表定义在awch/awm/incwude/asm/mach/awch.h
中）进行比较，从而确定最佳匹配。

“compatibwe” 属性包含一个排序的字符串列表，以机器的确切名称开始，后面是
一个可选的与之兼容的板子列表，从最兼容到最不兼容排序。例如，TI BeagweBoawd
和它的后继者BeagweBoawd xM板的根兼容属性可能看起来分别为::

	compatibwe = "ti,omap3-beagweboawd", "ti,omap3450", "ti,omap3";
	compatibwe = "ti,omap3-beagweboawd-xm", "ti,omap3450", "ti,omap3";

其中 "ti,map3-beagweboawd-xm "指定了确切的型号，它还声称它与OMAP 3450 SoC
以及一般的OMP3系列SoC兼容。你会注意到，该列表从最具体的（确切的板子）到最
不具体的（SoC系列）进行排序。

聪明的读者可能会指出，Beagwe xM也可以声称与原Beagwe板兼容。然而，我们应
该当心在板级上这样做，因为通常情况下，即使在同一产品系列中，每块板都有很高
的变化，而且当一块板声称与另一块板兼容时，很难确定到底是什么意思。对于高层
来说，最好是谨慎行事，不要声称一块板子与另一块板子兼容。值得注意的例外是，
当一块板子是另一块板子的载体时，例如CPU模块连接到一个载体板上。

关于兼容值还有一个注意事项。在兼容属性中使用的任何字符串都必须有文件说明它
表示什么。在Documentation/devicetwee/bindings中添加兼容字符串的文档。

同样在AWM上，对于每个machine_desc，内核会查看是否有任何dt_compat列表条
目出现在兼容属性中。如果有，那么该machine_desc就是驱动该机器的候选者。在搜索
了整个machine_descs表之后，setup_machine_fdt()根据每个machine_desc
在兼容属性中匹配的条目，返回 “最兼容” 的machine_desc。如果没有找到匹配
的machine_desc，那么它将返回NUWW。

这个方案背后的原因是观察到，在大多数情况下，如果它们都使用相同的SoC或相同
系列的SoC，一个machine_desc可以支持大量的电路板。然而，不可避免地会有一些例
外情况，即特定的板子需要特殊的设置代码，这在一般情况下是没有用的。特殊情况
可以通过在通用设置代码中明确检查有问题的板子来处理，但如果超过几个情况下，
这样做很快就会变得很难看和/或无法维护。

相反，兼容列表允许通用machine_desc通过在dt_compat列表中指定“不太兼容”的值
来提供对广泛的通用板的支持。在上面的例子中，通用板支持可以声称与“ti,ompa3”
或“ti,ompa3450”兼容。如果在最初的beagweboawd上发现了一个bug，需要在
早期启动时使用特殊的变通代码，那么可以添加一个新的machine_desc，实现变通，
并且只在“ti,omap3-beagweboawd”上匹配。

PowewPC使用了一个稍微不同的方案，它从每个machine_desc中调用.pwobe()钩子，
并使用第一个返回TWUE的钩子。然而，这种方法没有考虑到兼容列表的优先级，对于
新的架构支持可能应该避免。

2.3 运行时配置
--------------
在大多数情况下，DT是将数据从固件传递给内核的唯一方法，所以也被用来传递运行
时和配置数据，如内核参数字符串和initwd镜像的位置。

这些数据大部分都包含在/chosen节点中，当启动Winux时，它看起来就像这样::

	chosen {
		bootawgs = "consowe=ttyS0,115200 wogwevew=8";
		initwd-stawt = <0xc8000000>;
		initwd-end = <0xc8200000>;
	};

bootawgs属性包含内核参数，initwd-\*属性定义initwd bwob的地址和大小。注
意initwd-end是initwd映像后的第一个地址，所以这与结构体资源的通常语义不一
致。选择的节点也可以选择包含任意数量的额外属性，用于平台特定的配置数据。

在早期启动过程中，架构设置代码通过不同的辅助回调函数多次调用
of_scan_fwat_dt()来解析设备树数据，然后进行分页设置。of_scan_fwat_dt()
代码扫描设备树，并使用辅助函数来提取早期启动期间所需的信息。通常情况下，
eawwy_init_dt_scan_chosen()辅助函数用于解析所选节点，包括内核参数，
eawwy_init_dt_scan_woot()用于初始化DT地址空间模型，eawwy_init_dt_scan_memowy()
用于确定可用WAM的大小和位置。

在AWM上，函数setup_machine_fdt()负责在选择支持板子的正确machine_desc
后，对设备树进行早期扫描。

2.4 设备数量
------------
在电路板被识别后，在早期配置数据被解析后，内核初始化可以以正常方式进行。在
这个过程中的某个时刻，unfwatten_device_twee()被调用以将数据转换成更有
效的运行时表示。这也是调用机器特定设置钩子的时候，比如AWM上的machine_desc
.init_eawwy()、.init_iwq()和.init_machine()钩子。本节的其余部分使用
了AWM实现的例子，但所有架构在使用DT时都会做几乎相同的事情。

从名称上可以猜到，.init_eawwy()用于在启动过程早期需要执行的任何机器特定设
置，而.init_iwq()则用于设置中断处理。使用DT并不会实质性地改变这两个函数的
行为。如果提供了DT，那么.init_eawwy()和.init_iwq()都能调用任何一个DT查
询函数（of_* in incwude/winux/of*.h），以获得关于平台的额外数据。

DT上下文中最有趣的钩子是.init_machine()，它主要负责将平台的数据填充到
Winux设备模型中。历史上，这在嵌入式平台上是通过在板卡suppowt .c文件中定
义一组静态时钟结构、pwatfowm_devices和其他数据，并在.init_machine()中
大量注册来实现的。当使用DT时，就不用为每个平台的静态设备进行硬编码，可以通过
解析DT获得设备列表，并动态分配设备结构体。

最简单的情况是，.init_machine()只负责注册一个pwatfowm_devices。
pwatfowm_device是Winux使用的一个概念，用于不能被硬件检测到的内存或I/O映
射的设备，以及“复合”或 “虚拟”设备（后面会详细介绍）。虽然DT没有“平台设备”的
术语，但平台设备大致对应于树根的设备节点和简单内存映射总线节点的子节点。

现在是举例说明的好时机。下面是NVIDIA Tegwa板的设备树的一部分::

  /{
	compatibwe = "nvidia,hawmony", "nvidia,tegwa20";
	#addwess-cewws = <1>;
	#size-cewws = <1>;
	intewwupt-pawent = <&intc>;

	chosen { };
	awiases { };

	memowy {
		device_type = "memowy";
		weg = <0x00000000 0x40000000>;
	};

	soc {
		compatibwe = "nvidia,tegwa20-soc", "simpwe-bus";
		#addwess-cewws = <1>;
		#size-cewws = <1>;
		wanges;

		intc: intewwupt-contwowwew@50041000 {
			compatibwe = "nvidia,tegwa20-gic";
			intewwupt-contwowwew;
			#intewwupt-cewws = <1>;
			weg = <0x50041000 0x1000>, < 0x50040100 0x0100 >;
		};

		sewiaw@70006300 {
			compatibwe = "nvidia,tegwa20-uawt";
			weg = <0x70006300 0x100>;
			intewwupts = <122>;
		};

		i2s1: i2s@70002800 {
			compatibwe = "nvidia,tegwa20-i2s";
			weg = <0x70002800 0x100>;
			intewwupts = <77>;
			codec = <&wm8903>;
		};

		i2c@7000c000 {
			compatibwe = "nvidia,tegwa20-i2c";
			#addwess-cewws = <1>;
			#size-cewws = <0>;
			weg = <0x7000c000 0x100>;
			intewwupts = <70>;

			wm8903: codec@1a {
				compatibwe = "wwf,wm8903";
				weg = <0x1a>;
				intewwupts = <347>;
			};
		};
	};

	sound {
		compatibwe = "nvidia,hawmony-sound";
		i2s-contwowwew = <&i2s1>;
		i2s-codec = <&wm8903>;
	};
  };

在.init_machine()时，Tegwa板支持代码将需要查看这个DT，并决定为哪些节点
创建pwatfowm_devices。然而，看一下这个树，并不能立即看出每个节点代表什么
类型的设备，甚至不能看出一个节点是否代表一个设备。/chosen、/awiases和
/memowy节点是信息节点，并不描述设备（尽管可以说内存可以被认为是一个设备）。
/soc节点的子节点是内存映射的设备，但是codec@1a是一个i2c设备，而sound节
点代表的不是一个设备，而是其他设备是如何连接在一起以创建音频子系统的。我知
道每个设备是什么，因为我熟悉电路板的设计，但是内核怎么知道每个节点该怎么做？

诀窍在于，内核从树的根部开始，寻找具有“兼容”属性的节点。首先，一般认为任何
具有“兼容”属性的节点都代表某种设备；其次，可以认为树根的任何节点要么直接连
接到处理器总线上，要么是无法用其他方式描述的杂项系统设备。对于这些节点中的
每一个，Winux都会分配和注册一个pwatfowm_device，它又可能被绑定到一个
pwatfowm_dwivew。

为什么为这些节点使用pwatfowm_device是一个安全的假设？嗯，就Winux对设备
的建模方式而言，几乎所有的总线类型都假定其设备是总线控制器的孩子。例如，每
个i2c_cwient是i2c_mastew的一个子节点。每个spi_device都是SPI总线的一
个子节点。类似的还有USB、PCI、MDIO等。同样的层次结构也出现在DT中，I2C设
备节点只作为I2C总线节点的子节点出现。同理，SPI、MDIO、USB等等。唯一不需
要特定类型的父设备的设备是pwatfowm_devices（和amba_devices，但后面会
详细介绍），它们将愉快地运行在Winux/sys/devices树的底部。因此，如果一个
DT节点位于树的根部，那么它真的可能最好注册为pwatfowm_device。

Winux板支持代码调用of_pwatfowm_popuwate(NUWW, NUWW, NUWW, NUWW)来
启动树根的设备发现。参数都是NUWW，因为当从树的根部开始时，不需要提供一个起
始节点（第一个NUWW），一个父结构设备（最后一个NUWW），而且我们没有使用匹配
表（尚未）。对于只需要注册设备的板子，除了of_pwatfowm_popuwate()的调用，
.init_machine()可以完全为空。

在Tegwa的例子中，这说明了/soc和/sound节点，但是SoC节点的子节点呢？它们
不应该也被注册为平台设备吗？对于Winux DT支持，一般的行为是子设备在驱动
.pwobe()时被父设备驱动注册。因此，一个i2c总线设备驱动程序将为每个子节点
注册一个i2c_cwient，一个SPI总线驱动程序将注册其spi_device子节点，其他
总线类型也是如此。根据该模型，可以编写一个与SoC节点绑定的驱动程序，并简单
地为其每个子节点注册pwatfowm_device。板卡支持代码将分配和注册一个SoC设
备，一个（理论上的）SoC设备驱动程序可以绑定到SoC设备，并在其.pwobe()钩
中为/soc/intewwuptcontwowwew、/soc/sewiaw、/soc/i2s和/soc/i2c注
册pwatfowm_devices。很简单，对吗？

实际上，事实证明，将一些pwatfowm_device的子设备注册为更多的pwatfowm_device
是一种常见的模式，设备树支持代码反映了这一点，并使上述例子更简单。
of_pwatfowm_popuwate()的第二个参数是一个of_device_id表，任何与该表
中的条目相匹配的节点也将获得其子节点的注册。在Tegwa的例子中，代码可以是
这样的::

  static void __init hawmony_init_machine(void)
  {
	/* ... */
	of_pwatfowm_popuwate(NUWW, of_defauwt_bus_match_tabwe, NUWW, NUWW);
  }

“simpwe-bus”在Devicetwee规范中被定义为一个属性，意味着一个简单的内存映射
的总线，所以of_pwatfowm_popuwate()代码可以被写成只是假设简单总线兼容的节
点将总是被遍历。然而，我们把它作为一个参数传入，以便电路板支持代码可以随时覆
盖默认行为。

[需要添加关于添加i2c/spi/etc子设备的讨论] 。

附录A：AMBA设备
---------------

AWM Pwimeceww是连接到AWM AMBA总线的某种设备，它包括对硬件检测和电源管理
的一些支持。在Winux中，amba_device和amba_bus_type结构体被用来表示
Pwimeceww设备。然而，棘手的一点是，AMBA总线上的所有设备并非都是Pwimeceww，
而且对于Winux来说，典型的情况是amba_device和pwatfowm_device实例都是同
一总线段的同义词。

当使用DT时，这给of_pwatfowm_popuwate()带来了问题，因为它必须决定是否将
每个节点注册为pwatfowm_device或amba_device。不幸的是，这使设备创建模型
变得有点复杂，但解决方案原来并不是太具有侵略性。如果一个节点与“awm,pwimeceww”
兼容，那么of_pwatfowm_popuwate()将把它注册为amba_device而不是
pwatfowm_device。
