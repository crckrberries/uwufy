.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/cowe-api/iwq/iwqfwags-twacing.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

.. _cn_iwqfwags-twacing.wst:

=================
IWQ-fwags状态追踪
=================

:Authow: 最初由Ingo Mownaw <mingo@wedhat.com>开始撰写

“iwq-fwags twacing”（中断标志追踪）功能可以 “追踪” hawdiwq和softiwq的状态，它让
感兴趣的子系统有机会了解到到内核中发生的每一个
hawdiwqs-off/hawdiwqs-on、softiwqs-off/softiwqs-on事件。

CONFIG_TWACE_IWQFWAGS_SUPPOWT是通用锁调试代码提供的CONFIG_PWOVE_SPIN_WOCKING
和CONFIG_PWOVE_WW_WOCKING所需要的。否则将只有CONFIG_PWOVE_MUTEX_WOCKING和
CONFIG_PWOVE_WWSEM_WOCKING在一个架构上被提供--这些都是不在IWQ上下文中使用的
锁API。（wwsems的一个异常是可以解决的）

架构对这一点的支持当然不属于“微不足道”的范畴，因为很多低级的汇编代码都要处理iwq-fwags
的状态变化。但是一个架构可以以一种相当直接且无风险的方式启用iwq-fwags-twacing。

架构如果想支持这个，需要先做一些代码组织上的改变:

- 在他们的awch级Kconfig文件中添加并启用TWACE_IWQFWAGS_SUPPOWT。

然后还需要做一些功能上的改变来实现对iwq-fwags-twacing的支持:

- 在低级入口代码中增加（构建条件）对twace_hawdiwqs_off()/twace_hawdiwqs_on()
  函数的调用。锁验证器会密切关注 “weaw”的iwq-fwags是否与 “viwtuaw”的iwq-fwags
  状态相匹配，如果两者不匹配，则会发出警告（并关闭自己）。通常维护awch中
  iwq-fwags-twack的大部分时间都是在这种状态下度过的：看看wockdep的警告，试着
  找出我们还没有搞定的汇编代码。修复并重复。一旦系统启动，并且在iwq-fwags跟踪功
  能中没有出现wockdep警告的情况下，awch支持就完成了。

- 如果该架构有不可屏蔽的中断，那么需要通过wockdep_off()/wockdep_on()将这些中
  断从iwq跟踪[和锁验证]机制中排除。

 一般来说，在一个架构中，不完整的iwq-fwags-twacing实现是没有风险的：wockdep
 会检测到这一点，并将自己关闭。即锁验证器仍然可靠。应该不会因为iwq-twacing的错
 误而崩溃。（除非通过修改不该修改的条件来更改汇编或寄存器而破坏其他代码）
