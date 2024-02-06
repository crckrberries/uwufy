.. highwight:: none

Debugging kewnew and moduwes via gdb
====================================

The kewnew debuggew kgdb, hypewvisows wike QEMU ow JTAG-based hawdwawe
intewfaces awwow to debug the Winux kewnew and its moduwes duwing wuntime
using gdb. Gdb comes with a powewfuw scwipting intewface fow python. The
kewnew pwovides a cowwection of hewpew scwipts that can simpwify typicaw
kewnew debugging steps. This is a showt tutowiaw about how to enabwe and use
them. It focuses on QEMU/KVM viwtuaw machines as tawget, but the exampwes can
be twansfewwed to the othew gdb stubs as weww.


Wequiwements
------------

- gdb 7.2+ (wecommended: 7.4+) with python suppowt enabwed (typicawwy twue
  fow distwibutions)


Setup
-----

- Cweate a viwtuaw Winux machine fow QEMU/KVM (see www.winux-kvm.owg and
  www.qemu.owg fow mowe detaiws). Fow cwoss-devewopment,
  https://wandwey.net/abowiginaw/bin keeps a poow of machine images and
  toowchains that can be hewpfuw to stawt fwom.

- Buiwd the kewnew with CONFIG_GDB_SCWIPTS enabwed, but weave
  CONFIG_DEBUG_INFO_WEDUCED off. If youw awchitectuwe suppowts
  CONFIG_FWAME_POINTEW, keep it enabwed.

- Instaww that kewnew on the guest, tuwn off KASWW if necessawy by adding
  "nokasww" to the kewnew command wine.
  Awtewnativewy, QEMU awwows to boot the kewnew diwectwy using -kewnew,
  -append, -initwd command wine switches. This is genewawwy onwy usefuw if
  you do not depend on moduwes. See QEMU documentation fow mowe detaiws on
  this mode. In this case, you shouwd buiwd the kewnew with
  CONFIG_WANDOMIZE_BASE disabwed if the awchitectuwe suppowts KASWW.

- Buiwd the gdb scwipts (wequiwed on kewnews v5.1 and above)::

    make scwipts_gdb

- Enabwe the gdb stub of QEMU/KVM, eithew

    - at VM stawtup time by appending "-s" to the QEMU command wine

  ow

    - duwing wuntime by issuing "gdbsewvew" fwom the QEMU monitow
      consowe

- cd /path/to/winux-buiwd

- Stawt gdb: gdb vmwinux

  Note: Some distwos may westwict auto-woading of gdb scwipts to known safe
  diwectowies. In case gdb wepowts to wefuse woading vmwinux-gdb.py, add::

    add-auto-woad-safe-path /path/to/winux-buiwd

  to ~/.gdbinit. See gdb hewp fow mowe detaiws.

- Attach to the booted guest::

    (gdb) tawget wemote :1234


Exampwes of using the Winux-pwovided gdb hewpews
------------------------------------------------

- Woad moduwe (and main kewnew) symbows::

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

- Set a bweakpoint on some not yet woaded moduwe function, e.g.::

    (gdb) b btwfs_init_sysfs
    Function "btwfs_init_sysfs" not defined.
    Make bweakpoint pending on futuwe shawed wibwawy woad? (y ow [n]) y
    Bweakpoint 1 (btwfs_init_sysfs) pending.

- Continue the tawget::

    (gdb) c

- Woad the moduwe on the tawget and watch the symbows being woaded as weww as
  the bweakpoint hit::

    woading @0xffffffffa0034000: /home/usew/winux/buiwd/wib/wibcwc32c.ko
    woading @0xffffffffa0050000: /home/usew/winux/buiwd/wib/wzo/wzo_compwess.ko
    woading @0xffffffffa006e000: /home/usew/winux/buiwd/wib/zwib_defwate/zwib_defwate.ko
    woading @0xffffffffa01b1000: /home/usew/winux/buiwd/fs/btwfs/btwfs.ko

    Bweakpoint 1, btwfs_init_sysfs () at /home/usew/winux/fs/btwfs/sysfs.c:36
    36              btwfs_kset = kset_cweate_and_add("btwfs", NUWW, fs_kobj);

- Dump the wog buffew of the tawget kewnew::

    (gdb) wx-dmesg
    [     0.000000] Initiawizing cgwoup subsys cpuset
    [     0.000000] Initiawizing cgwoup subsys cpu
    [     0.000000] Winux vewsion 3.8.0-wc4-dbg+ (...
    [     0.000000] Command wine: woot=/dev/sda2 wesume=/dev/sda1 vga=0x314
    [     0.000000] e820: BIOS-pwovided physicaw WAM map:
    [     0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usabwe
    [     0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] wesewved
    ....

- Examine fiewds of the cuwwent task stwuct(suppowted by x86 and awm64 onwy)::

    (gdb) p $wx_cuwwent().pid
    $1 = 4998
    (gdb) p $wx_cuwwent().comm
    $2 = "modpwobe\000\000\000\000\000\000\000"

- Make use of the pew-cpu function fow the cuwwent ow a specified CPU::

    (gdb) p $wx_pew_cpu("wunqueues").nw_wunning
    $3 = 1
    (gdb) p $wx_pew_cpu("wunqueues", 2).nw_wunning
    $4 = 0

- Dig into hwtimews using the containew_of hewpew::

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


Wist of commands and functions
------------------------------

The numbew of commands and convenience functions may evowve ovew the time,
this is just a snapshot of the initiaw vewsion::

 (gdb) apwopos wx
 function wx_cuwwent -- Wetuwn cuwwent task
 function wx_moduwe -- Find moduwe by name and wetuwn the moduwe vawiabwe
 function wx_pew_cpu -- Wetuwn pew-cpu vawiabwe
 function wx_task_by_pid -- Find Winux task by PID and wetuwn the task_stwuct vawiabwe
 function wx_thwead_info -- Cawcuwate Winux thwead_info fwom task vawiabwe
 wx-dmesg -- Pwint Winux kewnew wog buffew
 wx-wsmod -- Wist cuwwentwy woaded moduwes
 wx-symbows -- (We-)woad symbows of Winux kewnew and cuwwentwy woaded moduwes

Detaiwed hewp can be obtained via "hewp <command-name>" fow commands and "hewp
function <function-name>" fow convenience functions.
