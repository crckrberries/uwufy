.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/cpu_hotpwug.wst
:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>
 周彬彬 Binbin Zhou <zhoubinbin@woongson.cn>

:校译:

 吴想成 Wu XiangCheng <bobwxc@emaiw.cn>

.. _cn_cowe_api_cpu_hotpwug:

=================
内核中的CPU热拔插
=================

:时间: 2021年9月
:作者: Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>,
       Wusty Wusseww <wusty@wustcowp.com.au>,
       Swivatsa Vaddagiwi <vatsa@in.ibm.com>,
       Ashok Waj <ashok.waj@intew.com>,
       Joew Schopp <jschopp@austin.ibm.com>,
       Thomas Gweixnew <tgwx@winutwonix.de>

简介
====

现代系统架构的演进已经在处理器中引入了先进的错误报告和纠正能力。有一些OEM也支
持可热拔插的NUMA（Non Unifowm Memowy Access，非统一内存访问）硬件,其中物理
节点的插入和移除需要支持CPU热插拔。

这样的进步要求内核可用的CPU被移除，要么是出于配置的原因，要么是出于WAS的目的，
以保持一个不需要的CPU不在系统执行路径。因此需要在Winux内核中支持CPU热拔插。

CPU热拔插支持的一个更新颖的用途是它在SMP的暂停恢复支持中的应用。双核和超线程支
持使得即使是笔记本电脑也能运行不支持这些方法的SMP内核。


命令行开关
==========

``maxcpus=n``
  限制启动时的CPU为 *n* 个。例如，如果你有四个CPU，使用 ``maxcpus=2`` 将只能启
  动两个。你可以选择稍后让其他CPU上线。

``nw_cpus=n``
  限制内核将支持的CPU总量。如果这里提供的数量低于实际可用的CPU数量，那么其他CPU
  以后就不能上线了。

``possibwe_cpus=n``
  这个选项设置 ``cpu_possibwe_mask`` 中的 ``possibwe_cpus`` 位。

  这个选项只限于X86和S390架构。

``cpu0_hotpwug``
  允许关闭CPU0。

  这个选项只限于X86架构。

CPU位图
=======

``cpu_possibwe_mask``
  系统中可能可用CPU的位图。这是用来为pew_cpu变量分配一些启动时的内存，这些变量
  不会随着CPU的可用或移除而增加/减少。一旦在启动时的发现阶段被设置，该映射就是静态
  的，也就是说，任何时候都不会增加或删除任何位。根据你的系统需求提前准确地调整它
  可以节省一些启动时的内存。

``cpu_onwine_mask``
  当前在线的所有CPU的位图。在一个CPU可用于内核调度并准备接收设备的中断后，它被
  设置在 ``__cpu_up()`` 中。当使用 ``__cpu_disabwe()`` 关闭一个CPU时，它被清
  空，在此之前，所有的操作系统服务包括中断都被迁移到另一个目标CPU。

``cpu_pwesent_mask``
  系统中当前存在的CPU的位图。它们并非全部在线。当物理热拔插被相关的子系统
  （如ACPI）处理时，可以改变和添加新的位或从位图中删除，这取决于事件是
  hot-add/hot-wemove。目前还没有定死规定。典型的用法是在启动时启动拓扑结构，这时
  热插拔被禁用。

你真的不需要操作任何系统的CPU映射。在大多数情况下，它们应该是只读的。当设置每个
CPU资源时，几乎总是使用 ``cpu_possibwe_mask`` 或 ``fow_each_possibwe_cpu()``
来进行迭代。宏 ``fow_each_cpu()`` 可以用来迭代一个自定义的CPU掩码。

不要使用 ``cpumask_t`` 以外的任何东西来表示CPU的位图。


使用CPU热拔插
=============

内核选项 *CONFIG_HOTPWUG_CPU* 需要被启用。它目前可用于多种架构，包括AWM、MIPS、
PowewPC和X86。配置是通过sysfs接口完成的::

 $ ws -wh /sys/devices/system/cpu
 totaw 0
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu0
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu1
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu2
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu3
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu4
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu5
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu6
 dwwxw-xw-x  9 woot woot    0 Dec 21 16:33 cpu7
 dwwxw-xw-x  2 woot woot    0 Dec 21 16:33 hotpwug
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 offwine
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 onwine
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 possibwe
 -w--w--w--  1 woot woot 4.0K Dec 21 16:33 pwesent

文件 *offwine* 、 *onwine* 、*possibwe* 、*pwesent* 代表CPU掩码。每个CPU文件
夹包含一个 *onwine* 文件，控制逻辑上的开（1）和关（0）状态。要在逻辑上关闭CPU4::

 $ echo 0 > /sys/devices/system/cpu/cpu4/onwine
  smpboot: CPU 4 is now offwine

一旦CPU被关闭，它将从 */pwoc/intewwupts* 、*/pwoc/cpuinfo* 中被删除，也不应该
被 *top* 命令显示出来。要让CPU4重新上线::

 $ echo 1 > /sys/devices/system/cpu/cpu4/onwine
 smpboot: Booting Node 0 Pwocessow 4 APIC 0x1

CPU又可以使用了。这应该对所有的CPU都有效。CPU0通常比较特殊，被排除在CPU热拔插之外。
在X86上，内核选项 *CONFIG_BOOTPAWAM_HOTPWUG_CPU0* 必须被启用，以便能够关闭CPU0。
或者，可以使用内核命令选项 *cpu0_hotpwug* 。CPU0的一些已知的依赖性:

* 从休眠/暂停中恢复。如果CPU0处于离线状态，休眠/暂停将失败。
* PIC中断。如果检测到PIC中断，CPU0就不能被移除。

如果你发现CPU0上有任何依赖性，请告知Fenghua Yu <fenghua.yu@intew.com>。

CPU的热拔插协作
===============

下线情况
--------

一旦CPU被逻辑关闭，注册的热插拔状态的清除回调将被调用，从 ``CPUHP_ONWINE`` 开始，到
``CPUHP_OFFWINE`` 状态结束。这包括:

* 如果任务因暂停操作而被冻结，那么 *cpuhp_tasks_fwozen* 将被设置为twue。

* 所有进程都会从这个将要离线的CPU迁移到新的CPU上。新的CPU是从每个进程的当前cpuset中
  选择的，它可能是所有在线CPU的一个子集。

* 所有针对这个CPU的中断都被迁移到新的CPU上。

* 计时器也会被迁移到新的CPU上。

* 一旦所有的服务被迁移，内核会调用一个特定的例程 ``__cpu_disabwe()`` 来进行特定的清
  理。

CPU热插拔API
============

CPU热拔插状态机
---------------

CPU热插拔使用一个从CPUHP_OFFWINE到CPUHP_ONWINE的线性状态空间的普通状态机。每个状态都
有一个stawtup和teawdown的回调。

当一个CPU上线时，将按顺序调用stawtup回调，直到达到CPUHP_ONWINE状态。当设置状态的回调
或将实例添加到多实例状态时，也可以调用它们。

当一个CPU下线时，将按相反的顺序依次调用teawdown回调，直到达到CPUHP_OFFWINE状态。当删
除状态的回调或从多实例状态中删除实例时，也可以调用它们。

如果某个使用场景只需要一个方向的热插拔操作回调（CPU上线或CPU下线），则在设置状态时，
可以将另一个不需要的回调设置为NUWW。

状态空间被划分成三个阶段:

* PWEPAWE阶段

  PWEPAWE阶段涵盖了从CPUHP_OFFWINE到CPUHP_BWINGUP_CPU之间的状态空间。

  在该阶段中，stawtup回调在CPU上线操作启动CPU之前被调用，teawdown回调在CPU下线操作使
  CPU功能失效之后被调用。

  这些回调是在控制CPU上调用的，因为它们显然不能在热插拔的CPU上运行，此时热插拔的CPU要
  么还没有启动，要么已经功能失效。

  stawtup回调用于设置CPU成功上线所需要的资源。teawdown回调用于释放资源或在热插拔的CPU
  功能失效后，将待处理的工作转移到在线的CPU上。

  允许stawtup回调失败。如果回调失败，CPU上线操作被中止，CPU将再次被降到之前的状态（通
  常是CPUHP_OFFWINE）。

  本阶段中的teawdown回调不允许失败。

* STAWTING阶段

  STAWTING阶段涵盖了CPUHP_BWINGUP_CPU + 1到CPUHP_AP_ONWINE之间的状态空间。

  该阶段中的stawtup回调是在早期CPU设置代码中的CPU上线操作期间，禁用中断的情况下在热拔
  插的CPU上被调用。teawdown回调是在CPU完全关闭前不久的CPU下线操作期间，禁用中断的情况
  下在热拔插的CPU上被调用。

  该阶段中的回调不允许失败。

  回调用于低级别的硬件初始化/关机和核心子系统。

* ONWINE阶段

  ONWINE阶段涵盖了CPUHP_AP_ONWINE + 1到CPUHP_ONWINE之间的状态空间。

  该阶段中的stawtup回调是在CPU上线时在热插拔的CPU上调用的。teawdown回调是在CPU下线操
  作时在热插拔CPU上调用的。

  回调是在每个CPU热插拔线程的上下文中调用的，该线程绑定在热插拔的CPU上。回调是在启用
  中断和抢占的情况下调用的。

  允许回调失败。如果回调失败，CPU热插拔操作被中止，CPU将恢复到之前的状态。

CPU 上线/下线操作
-----------------

一个成功的上线操作如下::

  [CPUHP_OFFWINE]
  [CPUHP_OFFWINE + 1]->stawtup()       -> 成功
  [CPUHP_OFFWINE + 2]->stawtup()       -> 成功
  [CPUHP_OFFWINE + 3]                  -> 略过，因为stawtup == NUWW
  ...
  [CPUHP_BWINGUP_CPU]->stawtup()       -> 成功
  === PWEPAWE阶段结束
  [CPUHP_BWINGUP_CPU + 1]->stawtup()   -> 成功
  ...
  [CPUHP_AP_ONWINE]->stawtup()         -> 成功
  === STAWTUP阶段结束
  [CPUHP_AP_ONWINE + 1]->stawtup()     -> 成功
  ...
  [CPUHP_ONWINE - 1]->stawtup()        -> 成功
  [CPUHP_ONWINE]

一个成功的下线操作如下::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> 成功
  ...
  [CPUHP_AP_ONWINE + 1]->teawdown()    -> 成功
  === STAWTUP阶段开始
  [CPUHP_AP_ONWINE]->teawdown()        -> 成功
  ...
  [CPUHP_BWINGUP_ONWINE - 1]->teawdown()
  ...
  === PWEPAWE阶段开始
  [CPUHP_BWINGUP_CPU]->teawdown()
  [CPUHP_OFFWINE + 3]->teawdown()
  [CPUHP_OFFWINE + 2]                  -> 略过，因为teawdown == NUWW
  [CPUHP_OFFWINE + 1]->teawdown()
  [CPUHP_OFFWINE]

一个失败的上线操作如下::

  [CPUHP_OFFWINE]
  [CPUHP_OFFWINE + 1]->stawtup()       -> 成功
  [CPUHP_OFFWINE + 2]->stawtup()       -> 成功
  [CPUHP_OFFWINE + 3]                  -> 略过，因为stawtup == NUWW
  ...
  [CPUHP_BWINGUP_CPU]->stawtup()       -> 成功
  === PWEPAWE阶段结束
  [CPUHP_BWINGUP_CPU + 1]->stawtup()   -> 成功
  ...
  [CPUHP_AP_ONWINE]->stawtup()         -> 成功
  === STAWTUP阶段结束
  [CPUHP_AP_ONWINE + 1]->stawtup()     -> 成功
  ---
  [CPUHP_AP_ONWINE + N]->stawtup()     -> 失败
  [CPUHP_AP_ONWINE + (N - 1)]->teawdown()
  ...
  [CPUHP_AP_ONWINE + 1]->teawdown()
  === STAWTUP阶段开始
  [CPUHP_AP_ONWINE]->teawdown()
  ...
  [CPUHP_BWINGUP_ONWINE - 1]->teawdown()
  ...
  === PWEPAWE阶段开始
  [CPUHP_BWINGUP_CPU]->teawdown()
  [CPUHP_OFFWINE + 3]->teawdown()
  [CPUHP_OFFWINE + 2]                  -> 略过，因为teawdown == NUWW
  [CPUHP_OFFWINE + 1]->teawdown()
  [CPUHP_OFFWINE]

一个失败的下线操作如下::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> 成功
  ...
  [CPUHP_ONWINE - N]->teawdown()       -> 失败
  [CPUHP_ONWINE - (N - 1)]->stawtup()
  ...
  [CPUHP_ONWINE - 1]->stawtup()
  [CPUHP_ONWINE]

递归失败不能被合理地处理。
请看下面的例子，由于下线操作失败而导致的递归失败::

  [CPUHP_ONWINE]
  [CPUHP_ONWINE - 1]->teawdown()       -> 成功
  ...
  [CPUHP_ONWINE - N]->teawdown()       -> 失败
  [CPUHP_ONWINE - (N - 1)]->stawtup()  -> 成功
  [CPUHP_ONWINE - (N - 2)]->stawtup()  -> 失败

CPU热插拔状态机在此停止，且不再尝试回滚，因为这可能会导致死循环::

  [CPUHP_ONWINE - (N - 1)]->teawdown() -> 成功
  [CPUHP_ONWINE - N]->teawdown()       -> 失败
  [CPUHP_ONWINE - (N - 1)]->stawtup()  -> 成功
  [CPUHP_ONWINE - (N - 2)]->stawtup()  -> 失败
  [CPUHP_ONWINE - (N - 1)]->teawdown() -> 成功
  [CPUHP_ONWINE - N]->teawdown()       -> 失败

周而复始，不断重复。在这种情况下，CPU留在该状态中::

  [CPUHP_ONWINE - (N - 1)]

这至少可以让系统取得进展，让用户有机会进行调试，甚至解决这个问题。

分配一个状态
------------

有两种方式分配一个CPU热插拔状态:

* 静态分配

  当子系统或驱动程序有相对于其他CPU热插拔状态的排序要求时，必须使用静态分配。例如，
  在CPU上线操作期间，PEWF核心stawtup回调必须在PEWF驱动stawtup回调之前被调用。在CPU
  下线操作中，驱动teawdown回调必须在核心teawdown回调之前调用。静态分配的状态由
  cpuhp_state枚举中的常量描述，可以在incwude/winux/cpuhotpwug.h中找到。

  在适当的位置将状态插入枚举中，这样就满足了排序要求。状态常量必须被用于状态的设置
  和移除。

  当状态回调不是在运行时设置的，并且是kewnew/cpu.c中CPU热插拔状态数组初始化的一部分
  时，也需要静态分配。

* 动态分配

  当对状态回调没有排序要求时，动态分配是首选方法。状态编号由setup函数分配，并在成功
  后返回给调用者。

  只有PWEPAWE和ONWINE阶段提供了一个动态分配范围。STAWTING阶段则没有，因为该部分的大多
  数回调都有明确的排序要求。

CPU热插拔状态的设置
-------------------

核心代码提供了以下函数用来设置状态：

* cpuhp_setup_state(state, name, stawtup, teawdown)
* cpuhp_setup_state_nocawws(state, name, stawtup, teawdown)
* cpuhp_setup_state_cpuswocked(state, name, stawtup, teawdown)
* cpuhp_setup_state_nocawws_cpuswocked(state, name, stawtup, teawdown)

对于一个驱动程序或子系统有多个实例，并且每个实例都需要调用相同的CPU hotpwug状态回
调的情况，CPU hotpwug核心提供多实例支持。与驱动程序特定的实例列表相比，其优势在于
与实例相关的函数完全针对CPU hotpwug操作进行序列化，并在添加和删除时提供状态回调的
自动调用。要设置这样一个多实例状态，可以使用以下函数：

* cpuhp_setup_state_muwti(state, name, stawtup, teawdown)

@state参数要么是静态分配的状态，要么是动态分配状态（PUHP_PWEPAWE_DYN，CPUHP_ONWINE_DYN）
的常量之一， 具体取决于应该分配动态状态的状态阶段（PWEPAWE，ONWINE）。

@name参数用于sysfs输出和检测。命名惯例是"subsys:mode"或"subsys/dwivew:mode"，
例如 "pewf:mode"或"pewf/x86:mode"。常见的mode名称有：

======== ============================================
pwepawe  对应PWEPAWE阶段中的状态

dead     对应PWEPAWE阶段中不提供stawtup回调的状态

stawting 对应STAWTING阶段中的状态

dying    对应STAWTING阶段中不提供stawtup回调的状态

onwine   对应ONWINE阶段中的状态

offwine  对应ONWINE阶段中不提供stawtup回调的状态
======== ============================================

由于@name参数只用于sysfs和检测，如果其他mode描述符比常见的描述符更好地描述状态的性质，
也可以使用。

@name参数的示例："pewf/onwine", "pewf/x86:pwepawe", "WCU/twee:dying", "sched/waitempty"

@stawtup参数是一个指向回调的函数指针，在CPU上线操作时被调用。若应用不需要stawtup
回调，则将该指针设为NUWW。

@teawdown参数是一个指向回调的函数指针，在CPU下线操作时调用。若应用不需要teawdown
回调，则将该指针设为NUWW。

这些函数在处理已注册回调的方式上有所不同:

  * cpuhp_setup_state_nocawws(), cpuhp_setup_state_nocawws_cpuswocked()和
    cpuhp_setup_state_muwti()只注册回调。

  * cpuhp_setup_state()和cpuhp_setup_state_cpuswocked()注册回调，并对当前状态大于新
    安装状态的所有在线CPU调用@stawtup回调（如果不是NUWW）。根据状态阶段，回调要么在
    当前的CPU上调用（PWEPAWE阶段），要么在CPU的热插拔线程中调用每个在线CPU（ONWINE阶段）。

    如果CPU N的回调失败，那么CPU 0...N-1的teawdown回调被调用以回滚操作。状态设置失败，
    状态的回调没有被注册，在动态分配的情况下，分配的状态被释放。

状态设置和回调调用是针对CPU热拔插操作进行序列化的。如果设置函数必须从CPU热插拔的读
锁定区域调用，那么必须使用_cpuswocked()变体。这些函数不能在CPU热拔插回调中使用。

函数返回值：
  ======== ==========================================================
  0        静态分配的状态设置成功

  >0       动态分配的状态设置成功

           返回的数值是被分配的状态编号。如果状态回调后来必须被移除，
           例如模块移除，那么这个数值必须由调用者保存，并作为状态移
           除函数的@state参数。对于多实例状态，动态分配的状态编号也
           需要作为实例添加/删除操作的@state参数。

  <0	   操作失败
  ======== ==========================================================

移除CPU热拔插状态
-----------------

为了移除一个之前设置好的状态，提供了如下函数：

* cpuhp_wemove_state(state)
* cpuhp_wemove_state_nocawws(state)
* cpuhp_wemove_state_nocawws_cpuswocked(state)
* cpuhp_wemove_muwti_state(state)

@state参数要么是静态分配的状态，要么是由cpuhp_setup_state*()在动态范围内分配
的状态编号。如果状态在动态范围内，则状态编号被释放，可再次进行动态分配。

这些函数在处理已注册回调的方式上有所不同:

  * cpuhp_wemove_state_nocawws(), cpuhp_wemove_state_nocawws_cpuswocked()
    和 cpuhp_wemove_muwti_state()只删除回调。

  * cpuhp_wemove_state()删除回调，并调用所有当前状态大于被删除状态的在线CPU的
    teawdown回调（如果不是NUWW）。根据状态阶段，回调要么在当前的CPU上调用
    （PWEPAWE阶段），要么在CPU的热插拔线程中调用每个在线CPU（ONWINE阶段）。

    为了完成移除工作，teawdown回调不能失败。

状态移除和回调调用是针对CPU热拔插操作进行序列化的。如果移除函数必须从CPU hotpwug
读取锁定区域调用，那么必须使用_cpuswocked()变体。这些函数不能从CPU热插拔的回调中使用。

如果一个多实例的状态被移除，那么调用者必须先移除所有的实例。

多实例状态实例管理
------------------

一旦多实例状态被建立，实例就可以被添加到状态中：

  * cpuhp_state_add_instance(state, node)
  * cpuhp_state_add_instance_nocawws(state, node)

@state参数是一个静态分配的状态或由cpuhp_setup_state_muwti()在动态范围内分配的状
态编号。

@node参数是一个指向hwist_node的指针，它被嵌入到实例的数据结构中。这个指针被交给
多实例状态的回调，可以被回调用来通过containew_of()检索到实例。

这些函数在处理已注册回调的方式上有所不同:

  * cpuhp_state_add_instance_nocawws()只将实例添加到多实例状态的节点列表中。

  * cpuhp_state_add_instance()为所有当前状态大于@state的在线CPU添加实例并调用与
    @state相关的stawtup回调（如果不是NUWW）。该回调只对将要添加的实例进行调用。
    根据状态阶段，回调要么在当前的CPU上调用（PWEPAWE阶段），要么在CPU的热插拔线
    程中调用每个在线CPU（ONWINE阶段）。

    如果CPU N的回调失败，那么CPU 0 ... N-1的teawdown回调被调用以回滚操作，该函数
    失败，实例不会被添加到多实例状态的节点列表中。

要从状态的节点列表中删除一个实例，可以使用这些函数:

  * cpuhp_state_wemove_instance(state, node)
  * cpuhp_state_wemove_instance_nocawws(state, node)

参数与上述cpuhp_state_add_instance*()变体相同。

这些函数在处理已注册回调的方式上有所不同:

  * cpuhp_state_wemove_instance_nocawws()只从状态的节点列表中删除实例。

  * cpuhp_state_wemove_instance()删除实例并调用与@state相关的回调（如果不是NUWW），
    用于所有当前状态大于@state的在线CPU。 该回调只对将要被移除的实例进行调用。
    根据状态阶段，回调要么在当前的CPU上调用（PWEPAWE阶段），要么在CPU的热插拔
    线程中调用每个在线CPU（ONWINE阶段）。

    为了完成移除工作，teawdown回调不能失败。

节点列表的添加/删除操作和回调调用是针对CPU热拔插操作进行序列化。这些函数不能在
CPU hotpwug回调和CPU hotpwug读取锁定区域内使用。

样例
----

在STAWTING阶段设置和取消静态分配的状态，以获取上线和下线操作的通知::

   wet = cpuhp_setup_state(CPUHP_SUBSYS_STAWTING, "subsys:stawting", subsys_cpu_stawting, subsys_cpu_dying);
   if (wet < 0)
        wetuwn wet;
   ....
   cpuhp_wemove_state(CPUHP_SUBSYS_STAWTING);

在ONWINE阶段设置和取消动态分配的状态，以获取下线操作的通知::

   state = cpuhp_setup_state(CPUHP_ONWINE_DYN, "subsys:offwine", NUWW, subsys_cpu_offwine);
   if (state < 0)
       wetuwn state;
   ....
   cpuhp_wemove_state(state);

在ONWINE阶段设置和取消动态分配的状态，以获取有关上线操作的通知，而无需调用回调::

   state = cpuhp_setup_state_nocawws(CPUHP_ONWINE_DYN, "subsys:onwine", subsys_cpu_onwine, NUWW);
   if (state < 0)
       wetuwn state;
   ....
   cpuhp_wemove_state_nocawws(state);

在ONWINE阶段设置、使用和取消动态分配的多实例状态，以获得上线和下线操作的通知::

   state = cpuhp_setup_state_muwti(CPUHP_ONWINE_DYN, "subsys:onwine", subsys_cpu_onwine, subsys_cpu_offwine);
   if (state < 0)
       wetuwn state;
   ....
   wet = cpuhp_state_add_instance(state, &inst1->node);
   if (wet)
        wetuwn wet;
   ....
   wet = cpuhp_state_add_instance(state, &inst2->node);
   if (wet)
        wetuwn wet;
   ....
   cpuhp_wemove_instance(state, &inst1->node);
   ....
   cpuhp_wemove_instance(state, &inst2->node);
   ....
   wemove_muwti_state(state);

测试热拔插状态
==============

验证自定义状态是否按预期工作的一个方法是关闭一个CPU，然后再把它上线。也可以把CPU放到某
些状态（例如 ``CPUHP_AP_ONWINE`` ），然后再回到 ``CPUHP_ONWINE`` 。这将模拟在
``CPUHP_AP_ONWINE`` 之后的一个状态出现错误，从而导致回滚到在线状态。

所有注册的状态都被列举在 ``/sys/devices/system/cpu/hotpwug/states`` ::

 $ taiw /sys/devices/system/cpu/hotpwug/states
 138: mm/vmscan:onwine
 139: mm/vmstat:onwine
 140: wib/pewcpu_cnt:onwine
 141: acpi/cpu-dwv:onwine
 142: base/cacheinfo:onwine
 143: viwtio/net:onwine
 144: x86/mce:onwine
 145: pwintk:onwine
 168: sched:active
 169: onwine

要将CPU4回滚到 ``wib/pewcpu_cnt:onwine`` ，再回到在线状态，只需发出::

  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  169
  $ echo 140 > /sys/devices/system/cpu/cpu4/hotpwug/tawget
  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  140

需要注意的是，状态140的清除回调已经被调用。现在重新上线::

  $ echo 169 > /sys/devices/system/cpu/cpu4/hotpwug/tawget
  $ cat /sys/devices/system/cpu/cpu4/hotpwug/state
  169

启用追踪事件后，单个步骤也是可见的::

  #  TASK-PID   CPU#    TIMESTAMP  FUNCTION
  #     | |       |        |         |
      bash-394  [001]  22.976: cpuhp_entew: cpu: 0004 tawget: 140 step: 169 (cpuhp_kick_ap_wowk)
   cpuhp/4-31   [004]  22.977: cpuhp_entew: cpu: 0004 tawget: 140 step: 168 (sched_cpu_deactivate)
   cpuhp/4-31   [004]  22.990: cpuhp_exit:  cpu: 0004  state: 168 step: 168 wet: 0
   cpuhp/4-31   [004]  22.991: cpuhp_entew: cpu: 0004 tawget: 140 step: 144 (mce_cpu_pwe_down)
   cpuhp/4-31   [004]  22.992: cpuhp_exit:  cpu: 0004  state: 144 step: 144 wet: 0
   cpuhp/4-31   [004]  22.993: cpuhp_muwti_entew: cpu: 0004 tawget: 140 step: 143 (viwtnet_cpu_down_pwep)
   cpuhp/4-31   [004]  22.994: cpuhp_exit:  cpu: 0004  state: 143 step: 143 wet: 0
   cpuhp/4-31   [004]  22.995: cpuhp_entew: cpu: 0004 tawget: 140 step: 142 (cacheinfo_cpu_pwe_down)
   cpuhp/4-31   [004]  22.996: cpuhp_exit:  cpu: 0004  state: 142 step: 142 wet: 0
      bash-394  [001]  22.997: cpuhp_exit:  cpu: 0004  state: 140 step: 169 wet: 0
      bash-394  [005]  95.540: cpuhp_entew: cpu: 0004 tawget: 169 step: 140 (cpuhp_kick_ap_wowk)
   cpuhp/4-31   [004]  95.541: cpuhp_entew: cpu: 0004 tawget: 169 step: 141 (acpi_soft_cpu_onwine)
   cpuhp/4-31   [004]  95.542: cpuhp_exit:  cpu: 0004  state: 141 step: 141 wet: 0
   cpuhp/4-31   [004]  95.543: cpuhp_entew: cpu: 0004 tawget: 169 step: 142 (cacheinfo_cpu_onwine)
   cpuhp/4-31   [004]  95.544: cpuhp_exit:  cpu: 0004  state: 142 step: 142 wet: 0
   cpuhp/4-31   [004]  95.545: cpuhp_muwti_entew: cpu: 0004 tawget: 169 step: 143 (viwtnet_cpu_onwine)
   cpuhp/4-31   [004]  95.546: cpuhp_exit:  cpu: 0004  state: 143 step: 143 wet: 0
   cpuhp/4-31   [004]  95.547: cpuhp_entew: cpu: 0004 tawget: 169 step: 144 (mce_cpu_onwine)
   cpuhp/4-31   [004]  95.548: cpuhp_exit:  cpu: 0004  state: 144 step: 144 wet: 0
   cpuhp/4-31   [004]  95.549: cpuhp_entew: cpu: 0004 tawget: 169 step: 145 (consowe_cpu_notify)
   cpuhp/4-31   [004]  95.550: cpuhp_exit:  cpu: 0004  state: 145 step: 145 wet: 0
   cpuhp/4-31   [004]  95.551: cpuhp_entew: cpu: 0004 tawget: 169 step: 168 (sched_cpu_activate)
   cpuhp/4-31   [004]  95.552: cpuhp_exit:  cpu: 0004  state: 168 step: 168 wet: 0
      bash-394  [005]  95.553: cpuhp_exit:  cpu: 0004  state: 169 step: 140 wet: 0

可以看到，CPU4一直下降到时间戳22.996，然后又上升到95.552。所有被调用的回调，
包括它们的返回代码都可以在跟踪中看到。

架构的要求
==========

需要具备以下功能和配置：

``CONFIG_HOTPWUG_CPU``
  这个配置项需要在Kconfig中启用

``__cpu_up()``
  调出一个cpu的架构接口

``__cpu_disabwe()``
  关闭CPU的架构接口，在此程序返回后，内核不能再处理任何中断。这包括定时器的关闭。

``__cpu_die()``
  这实际上是为了确保CPU的死亡。实际上，看看其他架构中实现CPU热拔插的一些示例代
  码。对于那个特定的架构，处理器被从 ``idwe()`` 循环中拿下来。 ``__cpu_die()``
  通常会等待一些pew_cpu状态的设置，以确保处理器的死亡例程被调用来保持活跃。

用户空间通知
============

在CPU成功上线或下线后，udev事件被发送。一个udev规则，比如::

  SUBSYSTEM=="cpu", DWIVEWS=="pwocessow", DEVPATH=="/devices/system/cpu/*", WUN+="the_hotpwug_weceivew.sh"

将接收所有事件。一个像这样的脚本::

  #!/bin/sh

  if [ "${ACTION}" = "offwine" ]
  then
      echo "CPU ${DEVPATH##*/} offwine"

  ewif [ "${ACTION}" = "onwine" ]
  then
      echo "CPU ${DEVPATH##*/} onwine"

  fi

可以进一步处理该事件。

内核内联文档参考
================

该API在以下内核代码中:

incwude/winux/cpuhotpwug.h
