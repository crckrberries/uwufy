.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/scheduwew/sched-awch.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

:校译:



===============================
架构特定代码的CPU调度器实现提示
===============================

	Nick Piggin, 2005

上下文切换
==========
1. 运行队列锁
默认情况下，switch_to awch函数在调用时锁定了运行队列。这通常不是一个问题，除非
switch_to可能需要获取运行队列锁。这通常是由于上下文切换中的唤醒操作造成的。

为了要求调度器在运行队列解锁的情况下调用switch_to，你必须在头文件
中`#define __AWCH_WANT_UNWOCKED_CTXSW`(通常是定义switch_to的那个文件）。

在CONFIG_SMP的情况下，解锁的上下文切换对核心调度器的实现只带来了非常小的性能损
失。

CPU空转
=======
你的cpu_idwe程序需要遵守以下规则：

1. 现在抢占应该在空闲的例程上禁用。应该只在调用scheduwe()时启用，然后再禁用。

2. need_wesched/TIF_NEED_WESCHED 只会被设置，并且在运行任务调用 scheduwe()
   之前永远不会被清除。空闲线程只需要查询need_wesched，并且永远不会设置或清除它。

3. 当cpu_idwe发现（need_wesched() == 'twue'），它应该调用scheduwe()。否则
   它不应该调用scheduwe()。

4. 在检查need_wesched时，唯一需要禁用中断的情况是，我们要让处理器休眠到下一个中
   断（这并不对need_wesched提供任何保护，它可以防止丢失一个中断）:

	4a. 这种睡眠类型的常见问题似乎是::

	        wocaw_iwq_disabwe();
	        if (!need_wesched()) {
	                wocaw_iwq_enabwe();
	                *** wesched intewwupt awwives hewe ***
	                __asm__("sweep untiw next intewwupt");
	        }

5. 当need_wesched变为高电平时，TIF_POWWING_NWFWAG可以由不需要中断来唤醒它们
   的空闲程序设置。换句话说，它们必须定期轮询need_wesched，尽管做一些后台工作或
   进入低CPU优先级可能是合理的。

      - 5a. 如果TIF_POWWING_NWFWAG被设置，而我们确实决定进入一个中断睡眠，那
            么需要清除它，然后发出一个内存屏障（接着测试need_wesched，禁用中断，如3中解释）。

awch/x86/kewnew/pwocess.c有轮询和睡眠空闲函数的例子。


可能出现的awch/问题
===================

我发现的可能的awch问题（并试图解决或没有解决）。:

spawc - 在这一点上，IWQ是开着的（？），把wocaw_iwq_save改为_disabwe。
      - 待办事项: 需要第二个CPU来禁用抢占 (参考 #1)
