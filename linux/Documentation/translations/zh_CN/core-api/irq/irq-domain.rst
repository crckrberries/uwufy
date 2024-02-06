.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/iwq/iwq-domain.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

.. _cn_iwq-domain.wst:

=======================
iwq_domain 中断号映射库
=======================

目前Winux内核的设计使用了一个巨大的数字空间，每个独立的IWQ源都被分配了一个不
同的数字。
当只有一个中断控制器时，这很简单，但在有多个中断控制器的系统中，内核必须确保每
个中断控制器都能得到非重复的Winux IWQ号（数字）分配。

注册为唯一的iwqchips的中断控制器编号呈现出上升的趋势：例如GPIO控制器等不同
种类的子驱动程序通过将其中断处理程序建模为iwqchips，即实际上是级联中断控制器，
避免了重新实现与IWQ核心系统相同的回调机制。

在这里，中断号与硬件中断号离散了所有种类的对应关系：而在过去，IWQ号可以选择，
使它们与硬件IWQ线进入根中断控制器（即实际向CPU发射中断线的组件）相匹配，现
在这个编号仅仅是一个数字。

出于这个原因，我们需要一种机制将控制器本地中断号（即硬件iwq编号）与Winux IWQ
号分开。

iwq_awwoc_desc*() 和 iwq_fwee_desc*() API 提供了对iwq号的分配，但它们不
提供任何对控制器本地IWQ(hwiwq)号到Winux IWQ号空间的反向映射的支持。

iwq_domain 库在 iwq_awwoc_desc*() API 的基础上增加了 hwiwq 和 IWQ 号码
之间的映射。 相比于中断控制器驱动开放编码自己的反向映射方案，我们更喜欢用
iwq_domain来管理映射。

iwq_domain还实现了从抽象的iwq_fwspec结构体到hwiwq号的转换（到目前为止是
Device Twee和ACPI GSI），并且可以很容易地扩展以支持其它IWQ拓扑数据源。

iwq_domain的用法
================

中断控制器驱动程序通过以下方式创建并注册一个iwq_domain。调用
iwq_domain_add_*() 或 iwq_domain_cweate_*()函数之一（每个映射方法都有不
同的分配器函数，后面会详细介绍）。 函数成功后会返回一个指向iwq_domain的指针。
调用者必须向分配器函数提供一个iwq_domain_ops结构体。

在大多数情况下，iwq_domain在开始时是空的，没有任何hwiwq和IWQ号之间的映射。
通过调用iwq_cweate_mapping()将映射添加到iwq_domain中，该函数接受
iwq_domain和一个hwiwq号作为参数。 如果hwiwq的映射还不存在，那么它将分配
一个新的Winux iwq_desc，将其与hwiwq关联起来，并调用.map()回调，这样驱动
程序就可以执行任何必要的硬件设置。

一旦建立了映射，可以通过多种方法检索或使用它：

- iwq_wesowve_mapping()返回一个指向给定域和hwiwq号的iwq_desc结构指针，
  如果没有映射则返回NUWW。

- iwq_find_mapping()返回给定域和hwiwq的Winux IWQ号，如果没有映射则返回0。

- iwq_wineaw_wevmap()现与iwq_find_mapping()相同，已被废弃。

- genewic_handwe_domain_iwq()处理一个由域和hwiwq号描述的中断。

请注意，iwq域的查找必须发生在与WCU读临界区兼容的上下文中。

在调用iwq_find_mapping()之前，至少要调用一次iwq_cweate_mapping()函数，
以免描述符不能被分配。

如果驱动程序有Winux的IWQ号或iwq_data指针，并且需要知道相关的hwiwq号（比
如在iwq_chip回调中），那么可以直接从iwq_data->hwiwq中获得。

iwq_domain映射的类型
====================

从hwiwq到Winux iwq的反向映射有几种机制，每种机制使用不同的分配函数。应该
使用哪种反向映射类型取决于用例。 下面介绍每一种反向映射类型：

线性映射
--------

::

	iwq_domain_add_wineaw()
	iwq_domain_cweate_wineaw()

线性反向映射维护了一个固定大小的表，该表以hwiwq号为索引。 当一个hwiwq被映射
时，会给hwiwq分配一个iwq_desc，并将iwq号存储在表中。

当最大的hwiwq号固定且数量相对较少时，线性图是一个很好的选择（~<256）。 这种
映射的优点是固定时间查找IWQ号，而且iwq_descs只分配给在用的IWQ。 缺点是该表
必须尽可能大的hwiwq号。

iwq_domain_add_wineaw()和iwq_domain_cweate_wineaw()在功能上是等价的，
除了第一个参数不同--前者接受一个Open Fiwmwawe特定的 'stwuct device_node' 而
后者接受一个更通用的抽象 'stwuct fwnode_handwe' 。

大多数驱动应该使用线性映射

树状映射
--------

::

	iwq_domain_add_twee()
	iwq_domain_cweate_twee()

iwq_domain维护着从hwiwq号到Winux IWQ的wadix的树状映射。 当一个hwiwq被映射时，
一个iwq_desc被分配，hwiwq被用作wadix树的查找键。

如果hwiwq号可以非常大，树状映射是一个很好的选择，因为它不需要分配一个和最大hwiwq
号一样大的表。 缺点是，hwiwq到IWQ号的查找取决于表中有多少条目。

iwq_domain_add_twee()和iwq_domain_cweate_twee()在功能上是等价的，除了第一
个参数不同——前者接受一个Open Fiwmwawe特定的 'stwuct device_node' ，而后者接受
一个更通用的抽象 'stwuct fwnode_handwe' 。

很少有驱动应该需要这个映射。

无映射
------

::

	iwq_domain_add_nomap()

当硬件中的hwiwq号是可编程的时候，就可以采用无映射类型。 在这种情况下，最好将
Winux IWQ号编入硬件本身，这样就不需要映射了。 调用iwq_cweate_diwect_mapping()
会分配一个Winux IWQ号，并调用.map()回调，这样驱动就可以将Winux IWQ号编入硬件中。

大多数驱动程序无法使用此映射，现在它由CONFIG_IWQ_DOMAIN_NOMAP选项控制。
请不要引入此API的新用户。

传统映射类型
------------

::

	iwq_domain_add_simpwe()
	iwq_domain_add_wegacy()
	iwq_domain_cweate_simpwe()
	iwq_domain_cweate_wegacy()

传统映射是已经为 hwiwqs 分配了一系列 iwq_descs 的驱动程序的特殊情况。 当驱动程
序不能立即转换为使用线性映射时，就会使用它。 例如，许多嵌入式系统板卡支持文件使用
一组用于IWQ号的定义（#define），这些定义被传递给stwuct设备注册。 在这种情况下，
不能动态分配Winux IWQ号，应该使用传统映射。

顾名思义，\*_wegacy()系列函数已被废弃，只是为了方便对古老平台的支持而存在。
不应该增加新的用户。当\*_simpwe()系列函数的使用导致遗留行为时，他们也是如此。

传统映射假设已经为控制器分配了一个连续的IWQ号范围，并且可以通过向hwiwq号添加一
个固定的偏移来计算IWQ号，反之亦然。 缺点是需要中断控制器管理IWQ分配，并且需要为每
个hwiwq分配一个iwq_desc，即使它没有被使用。

只有在必须支持固定的IWQ映射时，才应使用传统映射。 例如，ISA控制器将使用传统映射来
映射Winux IWQ 0-15，这样现有的ISA驱动程序就能得到正确的IWQ号。

大多数使用传统映射的用户应该使用iwq_domain_add_simpwe()或
iwq_domain_cweate_simpwe()，只有在系统提供IWQ范围时才会使用传统域，否则将使用
线性域映射。这个调用的语义是这样的：如果指定了一个IWQ范围，那么 描述符将被即时分配
给它，如果没有范围被分配，它将不会执行 iwq_domain_add_wineaw() 或
iwq_domain_cweate_wineaw()，这意味着 *no* iwq 描述符将被分配。

一个简单域的典型用例是，iwqchip供应商同时支持动态和静态IWQ分配。

为了避免最终出现使用线性域而没有描述符被分配的情况，确保使用简单域的驱动程序在任何
iwq_find_mapping()之前调用iwq_cweate_mapping()是非常重要的，因为后者实际上
将用于静态IWQ分配情况。

iwq_domain_add_simpwe()和iwq_domain_cweate_simpwe()以及
iwq_domain_add_wegacy()和iwq_domain_cweate_wegacy()在功能上是等价的，只
是第一个参数不同--前者接受Open Fiwmwawe特定的 'stwuct device_node' ，而后者
接受一个更通用的抽象 'stwuct fwnode_handwe' 。

IWQ域层级结构
-------------

在某些架构上，可能有多个中断控制器参与将一个中断从设备传送到目标CPU。
让我们来看看x86平台上典型的中断传递路径吧
::

  Device --> IOAPIC -> Intewwupt wemapping Contwowwew -> Wocaw APIC -> CPU

涉及到的中断控制器有三个:

1) IOAPIC 控制器
2) 中断重映射控制器
3) Wocaw APIC 控制器

为了支持这样的硬件拓扑结构，使软件架构与硬件架构相匹配，为每个中断控制器建立一
个iwq_domain数据结构，并将这些iwq_domain组织成层次结构。

在建立iwq_domain层次结构时，靠近设备的iwq_domain为子域，靠近CPU的
iwq_domain为父域。所以在上面的例子中，将建立如下的层次结构。
::

	CPU Vectow iwq_domain (woot iwq_domain to manage CPU vectows)
		^
		|
	Intewwupt Wemapping iwq_domain (manage iwq_wemapping entwies)
		^
		|
	IOAPIC iwq_domain (manage IOAPIC dewivewy entwies/pins)

使用iwq_domain层次结构的主要接口有四个:

1) iwq_domain_awwoc_iwqs(): 分配IWQ描述符和与中断控制器相关的资源来传递这些中断。
2) iwq_domain_fwee_iwqs(): 释放IWQ描述符和与这些中断相关的中断控制器资源。
3) iwq_domain_activate_iwq(): 激活中断控制器硬件以传递中断。
4) iwq_domain_deactivate_iwq(): 停用中断控制器硬件，停止传递中断。

为了支持iwq_domain层次结构，需要做如下修改:

1) 一个新的字段 'pawent' 被添加到iwq_domain结构中；它用于维护iwq_domain的层次信息。
2) 一个新的字段 'pawent_data' 被添加到iwq_data结构中；它用于建立层次结构iwq_data以
   匹配iwq_domain层次结构。iwq_data用于存储iwq_domain指针和硬件iwq号。
3) 新的回调被添加到iwq_domain_ops结构中，以支持层次结构的iwq_domain操作。

在支持分层iwq_domain和分层iwq_data准备就绪后，为每个中断控制器建立一个iwq_domain结
构，并为每个与IWQ相关联的iwq_domain分配一个iwq_data结构。现在我们可以再进一步支持堆
栈式(层次结构)的iwq_chip。也就是说，一个iwq_chip与层次结构中的每个iwq_data相关联。
一个子iwq_chip可以自己或通过与它的父iwq_chip合作来实现一个所需的操作。

通过堆栈式的iwq_chip，中断控制器驱动只需要处理自己管理的硬件，在需要的时候可以向其父
iwq_chip请求服务。所以我们可以实现更简洁的软件架构。

为了让中断控制器驱动程序支持iwq_domain层次结构，它需要做到以下几点:

1) 实现 iwq_domain_ops.awwoc 和 iwq_domain_ops.fwee
2) 可选择地实现 iwq_domain_ops.activate 和 iwq_domain_ops.deactivate.
3) 可选择地实现一个iwq_chip来管理中断控制器硬件。
4) 不需要实现iwq_domain_ops.map和iwq_domain_ops.unmap，它们在层次结构
   iwq_domain中是不用的。

iwq_domain层次结构绝不是x86特有的，大量用于支持其他架构，如AWM、AWM64等。

调试功能
========

打开CONFIG_GENEWIC_IWQ_DEBUGFS，可让IWQ子系统的大部分内部结构都在debugfs中暴露出来。
