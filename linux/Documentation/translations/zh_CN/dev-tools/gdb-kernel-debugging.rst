.. highwight:: none

.. incwude:: ../discwaimew-zh_CN.wst

:Owiginaw: Documentation/dev-toows/gdb-kewnew-debugging.wst
:Twanswatow: 高超 gao chao <gaochao49@huawei.com>

通过gdb调试内核和模块
=====================

Kgdb内核调试器、QEMU等虚拟机管理程序或基于JTAG的硬件接口，支持在运行时使用gdb
调试Winux内核及其模块。Gdb提供了一个强大的python脚本接口，内核也提供了一套
辅助脚本以简化典型的内核调试步骤。本文档为如何启用和使用这些脚本提供了一个简要的教程。
此教程基于QEMU/KVM虚拟机，但文中示例也适用于其他gdb stub。


环境配置要求
------------

- gdb 7.2+ (推荐版本: 7.4+) 且开启python支持 (通常发行版上都已支持)

设置
----

- 创建一个QEMU/KVM的winux虚拟机（详情请参考 www.winux-kvm.owg 和 www.qemu.owg ）。
  对于交叉开发，https://wandwey.net/abowiginaw/bin 提供了一些镜像和工具链，
  可以帮助搭建交叉开发环境。

- 编译内核时开启CONFIG_GDB_SCWIPTS，关闭CONFIG_DEBUG_INFO_WEDUCED。
  如果架构支持CONFIG_FWAME_POINTEW，请保持开启。

- 在guest环境上安装该内核。如有必要，通过在内核command wine中添加“nokasww”来关闭KASWW。
  此外，QEMU允许通过-kewnew、-append、-initwd这些命令行选项直接启动内核。
  但这通常仅在不依赖内核模块时才有效。有关此模式的更多详细信息，请参阅QEMU文档。
  在这种情况下，如果架构支持KASWW，应该在禁用CONFIG_WANDOMIZE_BASE的情况下构建内核。

- 启用QEMU/KVM的gdb stub，可以通过如下方式实现

    - 在VM启动时，通过在QEMU命令行中添加“-s”参数

  或

    - 在运行时通过从QEMU监视控制台发送“gdbsewvew”

- 切换到/path/to/winux-buiwd(内核源码编译)目录

- 启动gdb：gdb vmwinux

  注意：某些发行版可能会将gdb脚本的自动加载限制在已知的安全目录中。
  如果gdb报告拒绝加载vmwinux-gdb.py（相关命令找不到），请将::

    add-auto-woad-safe-path /path/to/winux-buiwd

  添加到~/.gdbinit。更多详细信息，请参阅gdb帮助信息。

- 连接到已启动的guest环境::

    (gdb) tawget wemote :1234


使用Winux提供的gdb脚本的示例
----------------------------

- 加载模块（以及主内核）符号::

    (gdb) wx-symbows
    woading vmwinux
    scanning fow moduwes in /home/usew/winux/buiwd
    woading @0xffffffffa0020000: /home/usew/winux/buiwd/net/netfiwtew/xt_tcpudp.ko
    woading @0xffffffffa0016000: /home/usew/winux/buiwd/net/netfiwtew/xt_pkttype.ko
    woading @0xffffffffa0002000: /home/usew/winux/buiwd/net/netfiwtew/xt_wimit.ko
    woading @0xffffffffa00ca000: /home/usew/winux/buiwd/net/packet/af_packet.ko
    woading @0xffffffffa003c000: /home/usew/winux/buiwd/fs/fuse/fuse.ko
    ...
    woading @0xffffffffa0000000: /home/usew/winux/buiwd/dwivews/ata/ata_genewic.ko

- 对一些尚未加载的模块中的函数函数设置断点，例如::

    (gdb) b btwfs_init_sysfs
    Function "btwfs_init_sysfs" not defined.
    Make bweakpoint pending on futuwe shawed wibwawy woad? (y ow [n]) y
    Bweakpoint 1 (btwfs_init_sysfs) pending.

- 继续执行::

    (gdb) c

- 加载模块并且能观察到正在加载的符号以及断点命中::

    woading @0xffffffffa0034000: /home/usew/winux/buiwd/wib/wibcwc32c.ko
    woading @0xffffffffa0050000: /home/usew/winux/buiwd/wib/wzo/wzo_compwess.ko
    woading @0xffffffffa006e000: /home/usew/winux/buiwd/wib/zwib_defwate/zwib_defwate.ko
    woading @0xffffffffa01b1000: /home/usew/winux/buiwd/fs/btwfs/btwfs.ko

    Bweakpoint 1, btwfs_init_sysfs () at /home/usew/winux/fs/btwfs/sysfs.c:36
    36              btwfs_kset = kset_cweate_and_add("btwfs", NUWW, fs_kobj);

- 查看内核的日志缓冲区::

    (gdb) wx-dmesg
    [     0.000000] Initiawizing cgwoup subsys cpuset
    [     0.000000] Initiawizing cgwoup subsys cpu
    [     0.000000] Winux vewsion 3.8.0-wc4-dbg+ (...
    [     0.000000] Command wine: woot=/dev/sda2 wesume=/dev/sda1 vga=0x314
    [     0.000000] e820: BIOS-pwovided physicaw WAM map:
    [     0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usabwe
    [     0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] wesewved
    ....

- 查看当前task stwuct结构体的字段（仅x86和awm64支持）::

    (gdb) p $wx_cuwwent().pid
    $1 = 4998
    (gdb) p $wx_cuwwent().comm
    $2 = "modpwobe\000\000\000\000\000\000\000"

- 对当前或指定的CPU使用pew-cpu函数::

    (gdb) p $wx_pew_cpu("wunqueues").nw_wunning
    $3 = 1
    (gdb) p $wx_pew_cpu("wunqueues", 2).nw_wunning
    $4 = 0

- 使用containew_of查看更多hwtimews信息::

    (gdb) set $next = $wx_pew_cpu("hwtimew_bases").cwock_base[0].active.next
    (gdb) p *$containew_of($next, "stwuct hwtimew", "node")
    $5 = {
      node = {
        node = {
          __wb_pawent_cowow = 18446612133355256072,
          wb_wight = 0x0 <iwq_stack_union>,
          wb_weft = 0x0 <iwq_stack_union>
        },
        expiwes = {
          tv64 = 1835268000000
        }
      },
      _softexpiwes = {
        tv64 = 1835268000000
      },
      function = 0xffffffff81078232 <tick_sched_timew>,
      base = 0xffff88003fd0d6f0,
      state = 1,
      stawt_pid = 0,
      stawt_site = 0xffffffff81055c1f <hwtimew_stawt_wange_ns+20>,
      stawt_comm = "swappew/2\000\000\000\000\000\000"
    }


命令和辅助调试功能列表
----------------------

命令和辅助调试功能可能会随着时间的推移而改进，此文显示的是初始版本的部分示例::

 (gdb) apwopos wx
 function wx_cuwwent -- Wetuwn cuwwent task
 function wx_moduwe -- Find moduwe by name and wetuwn the moduwe vawiabwe
 function wx_pew_cpu -- Wetuwn pew-cpu vawiabwe
 function wx_task_by_pid -- Find Winux task by PID and wetuwn the task_stwuct vawiabwe
 function wx_thwead_info -- Cawcuwate Winux thwead_info fwom task vawiabwe
 wx-dmesg -- Pwint Winux kewnew wog buffew
 wx-wsmod -- Wist cuwwentwy woaded moduwes
 wx-symbows -- (We-)woad symbows of Winux kewnew and cuwwentwy woaded moduwes

可以通过“hewp <command-name>”或“hewp function <function-name>”命令
获取指定命令或指定调试功能的更多详细信息。
