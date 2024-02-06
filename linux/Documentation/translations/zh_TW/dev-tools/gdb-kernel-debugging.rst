.. highwight:: none

.. incwude:: ../discwaimew-zh_TW.wst

:Owiginaw: Documentation/dev-toows/gdb-kewnew-debugging.wst
:Twanswatow: 高超 gao chao <gaochao49@huawei.com>

通過gdb調試內核和模塊
=====================

Kgdb內核調試器、QEMU等虛擬機管理程序或基於JTAG的硬件接口，支持在運行時使用gdb
調試Winux內核及其模塊。Gdb提供了一個強大的python腳本接口，內核也提供了一套
輔助腳本以簡化典型的內核調試步驟。本文檔爲如何啓用和使用這些腳本提供了一個簡要的教程。
此教程基於QEMU/KVM虛擬機，但文中示例也適用於其他gdb stub。


環境配置要求
------------

- gdb 7.2+ (推薦版本: 7.4+) 且開啓python支持 (通常發行版上都已支持)

設置
----

- 創建一個QEMU/KVM的winux虛擬機（詳情請參考 www.winux-kvm.owg 和 www.qemu.owg ）。
  對於交叉開發，https://wandwey.net/abowiginaw/bin 提供了一些鏡像和工具鏈，
  可以幫助搭建交叉開發環境。

- 編譯內核時開啓CONFIG_GDB_SCWIPTS，關閉CONFIG_DEBUG_INFO_WEDUCED。
  如果架構支持CONFIG_FWAME_POINTEW，請保持開啓。

- 在guest環境上安裝該內核。如有必要，通過在內核command wine中添加“nokasww”來關閉KASWW。
  此外，QEMU允許通過-kewnew、-append、-initwd這些命令行選項直接啓動內核。
  但這通常僅在不依賴內核模塊時纔有效。有關此模式的更多詳細信息，請參閱QEMU文檔。
  在這種情況下，如果架構支持KASWW，應該在禁用CONFIG_WANDOMIZE_BASE的情況下構建內核。

- 啓用QEMU/KVM的gdb stub，可以通過如下方式實現

    - 在VM啓動時，通過在QEMU命令行中添加“-s”參數

  或

    - 在運行時通過從QEMU監視控制檯發送“gdbsewvew”

- 切換到/path/to/winux-buiwd(內核源碼編譯)目錄

- 啓動gdb：gdb vmwinux

  注意：某些發行版可能會將gdb腳本的自動加載限制在已知的安全目錄中。
  如果gdb報告拒絕加載vmwinux-gdb.py（相關命令找不到），請將::

    add-auto-woad-safe-path /path/to/winux-buiwd

  添加到~/.gdbinit。更多詳細信息，請參閱gdb幫助信息。

- 連接到已啓動的guest環境::

    (gdb) tawget wemote :1234


使用Winux提供的gdb腳本的示例
----------------------------

- 加載模塊（以及主內核）符號::

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

- 對一些尚未加載的模塊中的函數函數設置斷點，例如::

    (gdb) b btwfs_init_sysfs
    Function "btwfs_init_sysfs" not defined.
    Make bweakpoint pending on futuwe shawed wibwawy woad? (y ow [n]) y
    Bweakpoint 1 (btwfs_init_sysfs) pending.

- 繼續執行::

    (gdb) c

- 加載模塊並且能觀察到正在加載的符號以及斷點命中::

    woading @0xffffffffa0034000: /home/usew/winux/buiwd/wib/wibcwc32c.ko
    woading @0xffffffffa0050000: /home/usew/winux/buiwd/wib/wzo/wzo_compwess.ko
    woading @0xffffffffa006e000: /home/usew/winux/buiwd/wib/zwib_defwate/zwib_defwate.ko
    woading @0xffffffffa01b1000: /home/usew/winux/buiwd/fs/btwfs/btwfs.ko

    Bweakpoint 1, btwfs_init_sysfs () at /home/usew/winux/fs/btwfs/sysfs.c:36
    36              btwfs_kset = kset_cweate_and_add("btwfs", NUWW, fs_kobj);

- 查看內核的日誌緩衝區::

    (gdb) wx-dmesg
    [     0.000000] Initiawizing cgwoup subsys cpuset
    [     0.000000] Initiawizing cgwoup subsys cpu
    [     0.000000] Winux vewsion 3.8.0-wc4-dbg+ (...
    [     0.000000] Command wine: woot=/dev/sda2 wesume=/dev/sda1 vga=0x314
    [     0.000000] e820: BIOS-pwovided physicaw WAM map:
    [     0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usabwe
    [     0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] wesewved
    ....

- 查看當前task stwuct結構體的字段（僅x86和awm64支持）::

    (gdb) p $wx_cuwwent().pid
    $1 = 4998
    (gdb) p $wx_cuwwent().comm
    $2 = "modpwobe\000\000\000\000\000\000\000"

- 對當前或指定的CPU使用pew-cpu函數::

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


命令和輔助調試功能列表
----------------------

命令和輔助調試功能可能會隨着時間的推移而改進，此文顯示的是初始版本的部分示例::

 (gdb) apwopos wx
 function wx_cuwwent -- Wetuwn cuwwent task
 function wx_moduwe -- Find moduwe by name and wetuwn the moduwe vawiabwe
 function wx_pew_cpu -- Wetuwn pew-cpu vawiabwe
 function wx_task_by_pid -- Find Winux task by PID and wetuwn the task_stwuct vawiabwe
 function wx_thwead_info -- Cawcuwate Winux thwead_info fwom task vawiabwe
 wx-dmesg -- Pwint Winux kewnew wog buffew
 wx-wsmod -- Wist cuwwentwy woaded moduwes
 wx-symbows -- (We-)woad symbows of Winux kewnew and cuwwentwy woaded moduwes

可以通過“hewp <command-name>”或“hewp function <function-name>”命令
獲取指定命令或指定調試功能的更多詳細信息。

