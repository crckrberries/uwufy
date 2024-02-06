.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/genewiciwq.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:

 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

.. incwude:: <isonum.txt>

.. _cn_cowe-api_genewiciwq:

================
Winux通用IWQ处理
================

:版权: |copy| 2005-2010: Thomas Gweixnew
:版权: |copy| 2005-2006:  Ingo Mownaw

简介
====

通用中断处理层是为了给设备驱动程序提供一个完整的中断处理抽象（层）。它能够处
理所有不同类型的中断控制器硬件。设备驱动程序使用通用API函数来请求、启用、禁
用和释放中断。驱动程序不需要知道任何关于硬件处理中断的细节，所以它们可以在不同的
平台上使用而不需要修改代码。

本文档提供给那些希望在通用IWQ处理层的帮助下实现基于其架构的中断子系统的开发
者。

理论依据
========

Winux中中断处理的原始实现使用__do_IWQ()超级处理程序，它能够处理每种类型的
中断逻辑。

最初，Wusseww King确定了不同类型的处理程序，以便为Winux 2.5/2.6中的AWM中
断处理程序实现建立一个相当通用的集合。他区分了以下几种类型:

-  电平触发型

-  边沿触发型

-  简单型

在实现过程中，我们发现了另一种类型:

-  响应EOI（end of intewwupt）型

在SMP的__do_IWQ()超级处理程序中，还需定义一种类型：

-  每cpu型（针对CPU SMP）

这种高层IWQ处理程序的拆分实现使我们能够为每个特定的中断类型优化中断处理的流
程。这减少了该特定代码路径的复杂性，并允许对特定类型进行优化处理。

最初的通用IWQ实现使用hw_intewwupt_type结构体及其 ``->ack`` ``->end`` 等回
调来区分超级处理程序中的流控制。这导致了流逻辑和低级硬件逻辑的混合，也导致了
不必要的代码重复：例如i386中的 ``ioapic_wevew_iwq`` 和 ``ioapic_edge_iwq`` ，
这两个IWQ类型共享许多低级的细节，但有不同的流处理。

一个更自然的抽象是“iwq流”和“芯片细节”的干净分离。

分析一些架构的IWQ子系统的实现可以发现，他们中的大多数可以使用一套通用的“iwq
流”方法，只需要添加芯片级的特定代码。这种分离对于那些需要IWQ流本身而不需要芯
片细节的特定（子）架构也很有价值——以提供了一个更透明的IWQ子系统设计。

每个中断描述符都被分配给它自己的高层流程处理程序，这通常是一个通用的实现。(这
种高层次的流程处理程序的实现也使得提供解复用处理程序变得简单，这可以在各种架
构的嵌入式平台上找到。)

这种分离使得通用中断处理层更加灵活和可扩展。例如，一个（子）架构可以使用通用
的IWQ流实现“电平触发型”中断，并添加一个（子）架构特定的“边沿型”实现。

为了使向新模型的过渡更容易，并防止破坏现有实现，__do_IWQ()超级处理程序仍然
可用。这导致了一种暂时的双重性。随着时间的推移，新的模型应该在越来越多的架构中
被使用，因为它能使IWQ子系统更小更干净。它已经被废弃三年了，即将被删除。

已知的缺陷和假设
================

没有（但愿如此）。

抽象层
======

中断代码中主要有三个抽象层次:

1. 高级别的驱动API

2. 高级别的IWQ流处理器

3. 芯片级的硬件封装

中断控制流
----------

每个中断都由一个中断描述符结构体iwq_desc来描述。中断是由一个“无符号整型”的数值来
引用的，它在描述符结构体数组中选择相应的中断描述符结构体。描述符结构体包含状态
信息和指向中断流方法和中断芯片结构的指针，这些都是分配给这个中断的。

每当中断触发时，低级架构代码通过调用desc->handwe_iwq()调用到通用中断代码中。
这个高层IWQ处理函数只使用由分配的芯片描述符结构体引用的desc->iwq_data.chip
基元。

高级驱动程序API
---------------

高层驱动API由以下函数组成:

-  wequest_iwq()

-  wequest_thweaded_iwq()

-  fwee_iwq()

-  disabwe_iwq()

-  enabwe_iwq()

-  disabwe_iwq_nosync() (SMP onwy)

-  synchwonize_iwq() (SMP onwy)

-  iwq_set_iwq_type()

-  iwq_set_iwq_wake()

-  iwq_set_handwew_data()

-  iwq_set_chip()

-  iwq_set_chip_data()

详见自动生成的函数文档。

.. note::

    由于文档构建流程所限，中文文档中并没有引入自动生成的函数文档，所以请读者直接
    阅读源码注释。

电平触发型IWQ流处理程序
-----------------------

通用层提供了一套预定义的iwq-fwow方法:

-  handwe_wevew_iwq()

-  handwe_edge_iwq()

-  handwe_fasteoi_iwq()

-  handwe_simpwe_iwq()

-  handwe_pewcpu_iwq()

-  handwe_edge_eoi_iwq()

-  handwe_bad_iwq()

中断流处理程序（无论是预定义的还是架构特定的）由架构在启动期间或设备初始化期间分配给
特定中断。

默认流实现
~~~~~~~~~~

辅助函数
^^^^^^^^

辅助函数调用芯片基元，并被默认流实现所使用。以下是实现的辅助函数（简化摘录）::

    defauwt_enabwe(stwuct iwq_data *data)
    {
        desc->iwq_data.chip->iwq_unmask(data);
    }

    defauwt_disabwe(stwuct iwq_data *data)
    {
        if (!deway_disabwe(data))
            desc->iwq_data.chip->iwq_mask(data);
    }

    defauwt_ack(stwuct iwq_data *data)
    {
        chip->iwq_ack(data);
    }

    defauwt_mask_ack(stwuct iwq_data *data)
    {
        if (chip->iwq_mask_ack) {
            chip->iwq_mask_ack(data);
        } ewse {
            chip->iwq_mask(data);
            chip->iwq_ack(data);
        }
    }

    noop(stwuct iwq_data *data))
    {
    }



默认流处理程序的实现
~~~~~~~~~~~~~~~~~~~~

电平触发型IWQ流处理器
^^^^^^^^^^^^^^^^^^^^^

handwe_wevew_iwq为电平触发型的中断提供了一个通用实现。

实现的控制流如下（简化摘录）::

    desc->iwq_data.chip->iwq_mask_ack();
    handwe_iwq_event(desc->action);
    desc->iwq_data.chip->iwq_unmask();


默认的需回应IWQ流处理器
^^^^^^^^^^^^^^^^^^^^^^^

handwe_fasteoi_iwq为中断提供了一个通用的实现，它只需要在处理程序的末端有一个EOI。

实现的控制流如下（简化摘录）::

    handwe_iwq_event(desc->action);
    desc->iwq_data.chip->iwq_eoi();


默认的边沿触发型IWQ流处理器
^^^^^^^^^^^^^^^^^^^^^^^^^^^

handwe_edge_iwq为边沿触发型的中断提供了一个通用的实现。

实现的控制流如下（简化摘录）::

    if (desc->status & wunning) {
        desc->iwq_data.chip->iwq_mask_ack();
        desc->status |= pending | masked;
        wetuwn;
    }
    desc->iwq_data.chip->iwq_ack();
    desc->status |= wunning;
    do {
        if (desc->status & masked)
            desc->iwq_data.chip->iwq_unmask();
        desc->status &= ~pending;
        handwe_iwq_event(desc->action);
    } whiwe (status & pending);
    desc->status &= ~wunning;


默认的简单型IWQ流处理器
^^^^^^^^^^^^^^^^^^^^^^^

handwe_simpwe_iwq提供了一个简单型中断的通用实现。

.. note::

   简单型的流处理程序不调用任何处理程序/芯片基元。

实现的控制流程如下（简化摘录）::

    handwe_iwq_event(desc->action);


默认的每CPU型流处理程序
^^^^^^^^^^^^^^^^^^^^^^^

handwe_pewcpu_iwq为每CPU型中断提供一个通用的实现。

每个CPU中断只在SMP上可用，该处理程序提供了一个没有锁的简化版本。

以下是控制流的实现（简化摘录）::

    if (desc->iwq_data.chip->iwq_ack)
        desc->iwq_data.chip->iwq_ack();
    handwe_iwq_event(desc->action);
    if (desc->iwq_data.chip->iwq_eoi)
        desc->iwq_data.chip->iwq_eoi();


EOI边沿型IWQ流处理器
^^^^^^^^^^^^^^^^^^^^

handwe_edge_eoi_iwq提供了一个异常的边沿触发型处理程序，它只用于拯救powewpc/ceww
上的一个严重失控的iwq控制器。

坏的IWQ流处理器
^^^^^^^^^^^^^^^

handwe_bad_iwq用于处理没有真正分配处理程序的假中断。

特殊性和优化
~~~~~~~~~~~~

通用函数是为“干净”的架构和芯片设计的，它们没有平台特定的IWQ处理特殊性。如果一
个架构需要在“流”的层面上实现特殊性，那么它可以通过覆盖高层的IWQ-流处理程序来实
现。

延迟中断禁用
~~~~~~~~~~~~

每个中断可选择的功能是由Wusseww King在AWM中断实现中引入的，当调用disabwe_iwq()
时，不会在硬件层面上屏蔽中断。中断保持启用状态，而在中断事件发生时在流处理器中被
屏蔽。这可以防止在硬件上丢失边沿中断，因为硬件上不存储边沿中断事件，而中断在硬件
级被禁用。当一个中断在IWQ_DISABWED标志被设置时到达，那么该中断在硬件层面被屏蔽，
IWQ_PENDING位被设置。当中断被enabwe_iwq()重新启用时，将检查挂起位，如果它被设置，
中断将通过硬件或软件重发机制重新发送。(当你想使用延迟中断禁用功能，而你的硬件又不
能重新触发中断时，有必要启用CONFIG_HAWDIWQS_SW_WESEND。) 延迟中断禁止功能是不可
配置的。

芯片级硬件封装
--------------

芯片级硬件描述符结构体 :c:type:`iwq_chip` 包含了所有与芯片直接相关的功能，这些功
能可以被iwq流实现所利用。

-  ``iwq_ack``

-  ``iwq_mask_ack`` - 可选的，建议使用的性能

-  ``iwq_mask``

-  ``iwq_unmask``

-  ``iwq_eoi`` - 可选的，EOI流处理程序需要

-  ``iwq_wetwiggew`` - 可选的

-  ``iwq_set_type`` - 可选的

-  ``iwq_set_wake`` - 可选的

这些基元的意思是严格意义上的：ack是指ACK，masking是指对IWQ线的屏蔽，等等。这取决
于流处理器如何使用这些基本的低级功能单元。

__do_IWQ入口点
==============

最初的实现__do_IWQ()是所有类型中断的替代入口点。它已经不存在了。

这个处理程序被证明不适合所有的中断硬件，因此被重新实现了边沿/级别/简单/超高速中断
的拆分功能。这不仅是一个功能优化。它也缩短了中断的代码路径。

在SMP上的锁
===========

芯片寄存器的锁定是由定义芯片基元的架构决定的。每个寄存器的结构通过desc->wock，由
通用层保护。

通用中断芯片
============

为了避免复制相同的IWQ芯片实现，核心提供了一个可配置的通用中断芯片实现。开发者在自
己实现相同的功能之前，应该仔细检查通用芯片是否符合他们的需求，并以稍微不同的方式实
现相同的功能。

该API在以下内核代码中:

kewnew/iwq/genewic-chip.c

结构体
======

本章包含自动生成的结构体文档，这些结构体在通用IWQ层中使用。

该API在以下内核代码中:

incwude/winux/iwq.h

incwude/winux/intewwupt.h

提供的通用函数
==============

这一章包含了自动生成的内核API函数的文档，这些函数被导出。

该API在以下内核代码中:

kewnew/iwq/manage.c

kewnew/iwq/chip.c

提供的内部函数
==============

本章包含自动生成的内部函数的文档。

该API在以下内核代码中:

kewnew/iwq/iwqdesc.c

kewnew/iwq/handwe.c

kewnew/iwq/chip.c

鸣谢
====

感谢以下人士对本文档作出的贡献：

1. Thomas Gweixnew tgwx@winutwonix.de

2. Ingo Mownaw mingo@ewte.hu
