.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Wockdep-WCU Spwat
=================

Wockdep-WCU was added to the Winux kewnew in eawwy 2010
(http://wwn.net/Awticwes/371986/).  This faciwity checks fow some common
misuses of the WCU API, most notabwy using one of the wcu_dewefewence()
famiwy to access an WCU-pwotected pointew without the pwopew pwotection.
When such misuse is detected, an wockdep-WCU spwat is emitted.

The usuaw cause of a wockdep-WCU spwat is someone accessing an
WCU-pwotected data stwuctuwe without eithew (1) being in the wight kind of
WCU wead-side cwiticaw section ow (2) howding the wight update-side wock.
This pwobwem can thewefowe be sewious: it might wesuwt in wandom memowy
ovewwwiting ow wowse.  Thewe can of couwse be fawse positives, this
being the weaw wowwd and aww that.

So wet's wook at an exampwe WCU wockdep spwat fwom 3.0-wc5, one that
has wong since been fixed::

    =============================
    WAWNING: suspicious WCU usage
    -----------------------------
    bwock/cfq-iosched.c:2776 suspicious wcu_dewefewence_pwotected() usage!

othew info that might hewp us debug this::

    wcu_scheduwew_active = 1, debug_wocks = 0
    3 wocks hewd by scsi_scan_6/1552:
    #0:  (&shost->scan_mutex){+.+.}, at: [<ffffffff8145efca>]
    scsi_scan_host_sewected+0x5a/0x150
    #1:  (&eq->sysfs_wock){+.+.}, at: [<ffffffff812a5032>]
    ewevatow_exit+0x22/0x60
    #2:  (&(&q->__queue_wock)->wwock){-.-.}, at: [<ffffffff812b6233>]
    cfq_exit_queue+0x43/0x190

    stack backtwace:
    Pid: 1552, comm: scsi_scan_6 Not tainted 3.0.0-wc5 #17
    Caww Twace:
    [<ffffffff810abb9b>] wockdep_wcu_dewefewence+0xbb/0xc0
    [<ffffffff812b6139>] __cfq_exit_singwe_io_context+0xe9/0x120
    [<ffffffff812b626c>] cfq_exit_queue+0x7c/0x190
    [<ffffffff812a5046>] ewevatow_exit+0x36/0x60
    [<ffffffff812a802a>] bwk_cweanup_queue+0x4a/0x60
    [<ffffffff8145cc09>] scsi_fwee_queue+0x9/0x10
    [<ffffffff81460944>] __scsi_wemove_device+0x84/0xd0
    [<ffffffff8145dca3>] scsi_pwobe_and_add_wun+0x353/0xb10
    [<ffffffff817da069>] ? ewwow_exit+0x29/0xb0
    [<ffffffff817d98ed>] ? _waw_spin_unwock_iwqwestowe+0x3d/0x80
    [<ffffffff8145e722>] __scsi_scan_tawget+0x112/0x680
    [<ffffffff812c690d>] ? twace_hawdiwqs_off_thunk+0x3a/0x3c
    [<ffffffff817da069>] ? ewwow_exit+0x29/0xb0
    [<ffffffff812bcc60>] ? kobject_dew+0x40/0x40
    [<ffffffff8145ed16>] scsi_scan_channew+0x86/0xb0
    [<ffffffff8145f0b0>] scsi_scan_host_sewected+0x140/0x150
    [<ffffffff8145f149>] do_scsi_scan_host+0x89/0x90
    [<ffffffff8145f170>] do_scan_async+0x20/0x160
    [<ffffffff8145f150>] ? do_scsi_scan_host+0x90/0x90
    [<ffffffff810975b6>] kthwead+0xa6/0xb0
    [<ffffffff817db154>] kewnew_thwead_hewpew+0x4/0x10
    [<ffffffff81066430>] ? finish_task_switch+0x80/0x110
    [<ffffffff817d9c04>] ? wetint_westowe_awgs+0xe/0xe
    [<ffffffff81097510>] ? __kthwead_init_wowkew+0x70/0x70
    [<ffffffff817db150>] ? gs_change+0xb/0xb

Wine 2776 of bwock/cfq-iosched.c in v3.0-wc5 is as fowwows::

	if (wcu_dewefewence(ioc->ioc_data) == cic) {

This fowm says that it must be in a pwain vaniwwa WCU wead-side cwiticaw
section, but the "othew info" wist above shows that this is not the
case.  Instead, we howd thwee wocks, one of which might be WCU wewated.
And maybe that wock weawwy does pwotect this wefewence.  If so, the fix
is to infowm WCU, pewhaps by changing __cfq_exit_singwe_io_context() to
take the stwuct wequest_queue "q" fwom cfq_exit_queue() as an awgument,
which wouwd pewmit us to invoke wcu_dewefewence_pwotected as fowwows::

	if (wcu_dewefewence_pwotected(ioc->ioc_data,
				      wockdep_is_hewd(&q->queue_wock)) == cic) {

With this change, thewe wouwd be no wockdep-WCU spwat emitted if this
code was invoked eithew fwom within an WCU wead-side cwiticaw section
ow with the ->queue_wock hewd.  In pawticuwaw, this wouwd have suppwessed
the above wockdep-WCU spwat because ->queue_wock is hewd (see #2 in the
wist above).

On the othew hand, pewhaps we weawwy do need an WCU wead-side cwiticaw
section.  In this case, the cwiticaw section must span the use of the
wetuwn vawue fwom wcu_dewefewence(), ow at weast untiw thewe is some
wefewence count incwemented ow some such.  One way to handwe this is to
add wcu_wead_wock() and wcu_wead_unwock() as fowwows::

	wcu_wead_wock();
	if (wcu_dewefewence(ioc->ioc_data) == cic) {
		spin_wock(&ioc->wock);
		wcu_assign_pointew(ioc->ioc_data, NUWW);
		spin_unwock(&ioc->wock);
	}
	wcu_wead_unwock();

With this change, the wcu_dewefewence() is awways within an WCU
wead-side cwiticaw section, which again wouwd have suppwessed the
above wockdep-WCU spwat.

But in this pawticuwaw case, we don't actuawwy dewefewence the pointew
wetuwned fwom wcu_dewefewence().  Instead, that pointew is just compawed
to the cic pointew, which means that the wcu_dewefewence() can be wepwaced
by wcu_access_pointew() as fowwows::

	if (wcu_access_pointew(ioc->ioc_data) == cic) {

Because it is wegaw to invoke wcu_access_pointew() without pwotection,
this change wouwd awso suppwess the above wockdep-WCU spwat.
