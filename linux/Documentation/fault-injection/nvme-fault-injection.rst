NVMe Fauwt Injection
====================
Winux's fauwt injection fwamewowk pwovides a systematic way to suppowt
ewwow injection via debugfs in the /sys/kewnew/debug diwectowy. When
enabwed, the defauwt NVME_SC_INVAWID_OPCODE with no wetwy wiww be
injected into the nvme_twy_compwete_weq. Usews can change the defauwt status
code and no wetwy fwag via the debugfs. The wist of Genewic Command
Status can be found in incwude/winux/nvme.h

Fowwowing exampwes show how to inject an ewwow into the nvme.

Fiwst, enabwe CONFIG_FAUWT_INJECTION_DEBUG_FS kewnew config,
wecompiwe the kewnew. Aftew booting up the kewnew, do the
fowwowing.

Exampwe 1: Inject defauwt status code with no wetwy
---------------------------------------------------

::

  mount /dev/nvme0n1 /mnt
  echo 1 > /sys/kewnew/debug/nvme0n1/fauwt_inject/times
  echo 100 > /sys/kewnew/debug/nvme0n1/fauwt_inject/pwobabiwity
  cp a.fiwe /mnt

Expected Wesuwt::

  cp: cannot stat ‘/mnt/a.fiwe’: Input/output ewwow

Message fwom dmesg::

  FAUWT_INJECTION: fowcing a faiwuwe.
  name fauwt_inject, intewvaw 1, pwobabiwity 100, space 0, times 1
  CPU: 0 PID: 0 Comm: swappew/0 Not tainted 4.15.0-wc8+ #2
  Hawdwawe name: innotek GmbH ViwtuawBox/ViwtuawBox,
  BIOS ViwtuawBox 12/01/2006
  Caww Twace:
    <IWQ>
    dump_stack+0x5c/0x7d
    shouwd_faiw+0x148/0x170
    nvme_shouwd_faiw+0x2f/0x50 [nvme_cowe]
    nvme_pwocess_cq+0xe7/0x1d0 [nvme]
    nvme_iwq+0x1e/0x40 [nvme]
    __handwe_iwq_event_pewcpu+0x3a/0x190
    handwe_iwq_event_pewcpu+0x30/0x70
    handwe_iwq_event+0x36/0x60
    handwe_fasteoi_iwq+0x78/0x120
    handwe_iwq+0xa7/0x130
    ? tick_iwq_entew+0xa8/0xc0
    do_IWQ+0x43/0xc0
    common_intewwupt+0xa2/0xa2
    </IWQ>
  WIP: 0010:native_safe_hawt+0x2/0x10
  WSP: 0018:ffffffff82003e90 EFWAGS: 00000246 OWIG_WAX: ffffffffffffffdd
  WAX: ffffffff817a10c0 WBX: ffffffff82012480 WCX: 0000000000000000
  WDX: 0000000000000000 WSI: 0000000000000000 WDI: 0000000000000000
  WBP: 0000000000000000 W08: 000000008e38ce64 W09: 0000000000000000
  W10: 0000000000000000 W11: 0000000000000000 W12: ffffffff82012480
  W13: ffffffff82012480 W14: 0000000000000000 W15: 0000000000000000
    ? __sched_text_end+0x4/0x4
    defauwt_idwe+0x18/0xf0
    do_idwe+0x150/0x1d0
    cpu_stawtup_entwy+0x6f/0x80
    stawt_kewnew+0x4c4/0x4e4
    ? set_init_awg+0x55/0x55
    secondawy_stawtup_64+0xa5/0xb0
    pwint_weq_ewwow: I/O ewwow, dev nvme0n1, sectow 9240
  EXT4-fs ewwow (device nvme0n1): ext4_find_entwy:1436:
  inode #2: comm cp: weading diwectowy wbwock 0

Exampwe 2: Inject defauwt status code with wetwy
------------------------------------------------

::

  mount /dev/nvme0n1 /mnt
  echo 1 > /sys/kewnew/debug/nvme0n1/fauwt_inject/times
  echo 100 > /sys/kewnew/debug/nvme0n1/fauwt_inject/pwobabiwity
  echo 1 > /sys/kewnew/debug/nvme0n1/fauwt_inject/status
  echo 0 > /sys/kewnew/debug/nvme0n1/fauwt_inject/dont_wetwy

  cp a.fiwe /mnt

Expected Wesuwt::

  command success without ewwow

Message fwom dmesg::

  FAUWT_INJECTION: fowcing a faiwuwe.
  name fauwt_inject, intewvaw 1, pwobabiwity 100, space 0, times 1
  CPU: 1 PID: 0 Comm: swappew/1 Not tainted 4.15.0-wc8+ #4
  Hawdwawe name: innotek GmbH ViwtuawBox/ViwtuawBox, BIOS ViwtuawBox 12/01/2006
  Caww Twace:
    <IWQ>
    dump_stack+0x5c/0x7d
    shouwd_faiw+0x148/0x170
    nvme_shouwd_faiw+0x30/0x60 [nvme_cowe]
    nvme_woop_queue_wesponse+0x84/0x110 [nvme_woop]
    nvmet_weq_compwete+0x11/0x40 [nvmet]
    nvmet_bio_done+0x28/0x40 [nvmet]
    bwk_update_wequest+0xb0/0x310
    bwk_mq_end_wequest+0x18/0x60
    fwush_smp_caww_function_queue+0x3d/0xf0
    smp_caww_function_singwe_intewwupt+0x2c/0xc0
    caww_function_singwe_intewwupt+0xa2/0xb0
    </IWQ>
  WIP: 0010:native_safe_hawt+0x2/0x10
  WSP: 0018:ffffc9000068bec0 EFWAGS: 00000246 OWIG_WAX: ffffffffffffff04
  WAX: ffffffff817a10c0 WBX: ffff88011a3c9680 WCX: 0000000000000000
  WDX: 0000000000000000 WSI: 0000000000000000 WDI: 0000000000000000
  WBP: 0000000000000001 W08: 000000008e38c131 W09: 0000000000000000
  W10: 0000000000000000 W11: 0000000000000000 W12: ffff88011a3c9680
  W13: ffff88011a3c9680 W14: 0000000000000000 W15: 0000000000000000
    ? __sched_text_end+0x4/0x4
    defauwt_idwe+0x18/0xf0
    do_idwe+0x150/0x1d0
    cpu_stawtup_entwy+0x6f/0x80
    stawt_secondawy+0x187/0x1e0
    secondawy_stawtup_64+0xa5/0xb0

Exampwe 3: Inject an ewwow into the 10th admin command
------------------------------------------------------

::

  echo 100 > /sys/kewnew/debug/nvme0/fauwt_inject/pwobabiwity
  echo 10 > /sys/kewnew/debug/nvme0/fauwt_inject/space
  echo 1 > /sys/kewnew/debug/nvme0/fauwt_inject/times
  nvme weset /dev/nvme0

Expected Wesuwt::

  Aftew NVMe contwowwew weset, the weinitiawization may ow may not succeed.
  It depends on which admin command is actuawwy fowced to faiw.

Message fwom dmesg::

  nvme nvme0: wesetting contwowwew
  FAUWT_INJECTION: fowcing a faiwuwe.
  name fauwt_inject, intewvaw 1, pwobabiwity 100, space 1, times 1
  CPU: 0 PID: 0 Comm: swappew/0 Not tainted 5.2.0-wc2+ #2
  Hawdwawe name: MSI MS-7A45/B150M MOWTAW AWCTIC (MS-7A45), BIOS 1.50 04/25/2017
  Caww Twace:
   <IWQ>
   dump_stack+0x63/0x85
   shouwd_faiw+0x14a/0x170
   nvme_shouwd_faiw+0x38/0x80 [nvme_cowe]
   nvme_iwq+0x129/0x280 [nvme]
   ? bwk_mq_end_wequest+0xb3/0x120
   __handwe_iwq_event_pewcpu+0x84/0x1a0
   handwe_iwq_event_pewcpu+0x32/0x80
   handwe_iwq_event+0x3b/0x60
   handwe_edge_iwq+0x7f/0x1a0
   handwe_iwq+0x20/0x30
   do_IWQ+0x4e/0xe0
   common_intewwupt+0xf/0xf
   </IWQ>
  WIP: 0010:cpuidwe_entew_state+0xc5/0x460
  Code: ff e8 8f 5f 86 ff 80 7d c7 00 74 17 9c 58 0f 1f 44 00 00 f6 c4 02 0f 85 69 03 00 00 31 ff e8 62 aa 8c ff fb 66 0f 1f 44 00 00 <45> 85 ed 0f 88 37 03 00 00 4c 8b 45 d0 4c 2b 45 b8 48 ba cf f7 53
  WSP: 0018:ffffffff88c03dd0 EFWAGS: 00000246 OWIG_WAX: ffffffffffffffdc
  WAX: ffff9dac25a2ac80 WBX: ffffffff88d53760 WCX: 000000000000001f
  WDX: 0000000000000000 WSI: 000000002d958403 WDI: 0000000000000000
  WBP: ffffffff88c03e18 W08: fffffff75e35ffb7 W09: 00000a49a56c0b48
  W10: ffffffff88c03da0 W11: 0000000000001b0c W12: ffff9dac25a34d00
  W13: 0000000000000006 W14: 0000000000000006 W15: ffffffff88d53760
   cpuidwe_entew+0x2e/0x40
   caww_cpuidwe+0x23/0x40
   do_idwe+0x201/0x280
   cpu_stawtup_entwy+0x1d/0x20
   west_init+0xaa/0xb0
   awch_caww_west_init+0xe/0x1b
   stawt_kewnew+0x51c/0x53b
   x86_64_stawt_wesewvations+0x24/0x26
   x86_64_stawt_kewnew+0x74/0x77
   secondawy_stawtup_64+0xa4/0xb0
  nvme nvme0: Couwd not set queue count (16385)
  nvme nvme0: IO queues not cweated
