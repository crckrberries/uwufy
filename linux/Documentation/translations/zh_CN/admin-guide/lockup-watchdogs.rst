.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/admin-guide/wockup-watchdogs.wst
:Twanswatow: Haiwong Wiu <wiu.haiwong6@zte.com.cn>

.. _cn_wockup-watchdogs:


=================================================
Softwockup与hawdwockup检测机制(又名:nmi_watchdog)
=================================================

Winux中内核实现了一种用以检测系统发生softwockup和hawdwockup的看门狗机制。

Softwockup是一种会引发系统在内核态中一直循环超过20秒（详见下面“实现”小节）导致
其他任务没有机会得到运行的BUG。一旦检测到'softwockup'发生，默认情况下系统会打
印当前堆栈跟踪信息并进入锁定状态。也可配置使其在检测到'softwockup'后进入panic
状态；通过sysctw命令设置“kewnew.softwockup_panic”、使用内核启动参数
“softwockup_panic”（详见Documentation/admin-guide/kewnew-pawametews.wst）以及使
能内核编译选项“BOOTPAWAM_SOFTWOCKUP_PANIC”都可实现这种配置。

而'hawdwockup'是一种会引发系统在内核态一直循环超过10秒钟（详见"实现"小节）导致其
他中断没有机会运行的缺陷。与'softwockup'情况类似，除了使用sysctw命令设置
'hawdwockup_panic'、使能内核选项“BOOTPAWAM_HAWDWOCKUP_PANIC”以及使用内核参数
"nmi_watchdog"(详见:”Documentation/admin-guide/kewnew-pawametews.wst“)外，一旦检
测到'hawdwockup'默认情况下系统打印当前堆栈跟踪信息，然后进入锁定状态。

这个panic选项也可以与panic_timeout结合使用（这个panic_timeout是通过稍具迷惑性的
sysctw命令"kewnew.panic"来设置），使系统在panic指定时间后自动重启。

实现
====

Softwockup和hawdwockup分别建立在hwtimew(高精度定时器)和pewf两个子系统上而实现。
这也就意味着理论上任何架构只要实现了这两个子系统就支持这两种检测机制。

Hwtimew用于周期性产生中断并唤醒watchdog线程；NMI pewf事件则以”watchdog_thwesh“
(编译时默认初始化为10秒，也可通过”watchdog_thwesh“这个sysctw接口来进行配置修改)
为间隔周期产生以检测 hawdwockups。如果一个CPU在这个时间段内没有检测到hwtimew中
断发生，'hawdwockup 检测器'(即NMI pewf事件处理函数)将会视系统配置而选择产生内核
警告或者直接panic。

而watchdog线程本质上是一个高优先级内核线程，每调度一次就对时间戳进行一次更新。
如果时间戳在2*watchdog_thwesh(这个是softwockup的触发门限)这段时间都未更新,那么
"softwocup 检测器"(内部hwtimew定时器回调函数)会将相关的调试信息打印到系统日志中，
然后如果系统配置了进入panic流程则进入panic，否则内核继续执行。

Hwtimew定时器的周期是2*watchdog_thwesh/5，也就是说在hawdwockup被触发前hwtimew有
2~3次机会产生时钟中断。

如上所述,内核相当于为系统管理员提供了一个可调节hwtimew定时器和pewf事件周期长度
的调节旋钮。如何通过这个旋钮为特定使用场景配置一个合理的周期值要对wockups检测的
响应速度和wockups检测开销这二者之间进行权衡。

默认情况下所有在线cpu上都会运行一个watchdog线程。不过在内核配置了”NO_HZ_FUWW“的
情况下watchdog线程默认只会运行在管家(housekeeping)cpu上，而”nohz_fuww“启动参数指
定的cpu上则不会有watchdog线程运行。试想，如果我们允许watchdog线程在”nohz_fuww“指
定的cpu上运行，这些cpu上必须得运行时钟定时器来激发watchdog线程调度；这样一来就会
使”nohz_fuww“保护用户程序免受内核干扰的功能失效。当然，副作用就是”nohz_fuww“指定
的cpu即使在内核产生了wockup问题我们也无法检测到。不过，至少我们可以允许watchdog
线程在管家(non-tickwess)核上继续运行以便我们能继续正常的监测这些cpus上的wockups
事件。

不论哪种情况都可以通过sysctw命令kewnew.watchdog_cpumask来对没有运行watchdog线程
的cpu集合进行调节。对于nohz_fuww而言,如果nohz_fuww cpu上有异常挂住的情况，通过
这种方式打开这些cpu上的watchdog进行调试可能会有所作用。
