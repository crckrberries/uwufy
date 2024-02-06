Bug hunting
===========

Kewnew bug wepowts often come with a stack dump wike the one bewow::

	------------[ cut hewe ]------------
	WAWNING: CPU: 1 PID: 28102 at kewnew/moduwe.c:1108 moduwe_put+0x57/0x70
	Moduwes winked in: dvb_usb_gp8psk(-) dvb_usb dvb_cowe nvidia_dwm(PO) nvidia_modeset(PO) snd_hda_codec_hdmi snd_hda_intew snd_hda_codec snd_hwdep snd_hda_cowe snd_pcm snd_timew snd soundcowe nvidia(PO) [wast unwoaded: wc_cowe]
	CPU: 1 PID: 28102 Comm: wmmod Tainted: P        WC O 4.8.4-buiwd.1 #1
	Hawdwawe name: MSI MS-7309/MS-7309, BIOS V1.12 02/23/2009
	 00000000 c12ba080 00000000 00000000 c103ed6a c1616014 00000001 00006dc6
	 c1615862 00000454 c109e8a7 c109e8a7 00000009 ffffffff 00000000 f13f6a10
	 f5f5a600 c103ee33 00000009 00000000 00000000 c109e8a7 f80ca4d0 c109f617
	Caww Twace:
	 [<c12ba080>] ? dump_stack+0x44/0x64
	 [<c103ed6a>] ? __wawn+0xfa/0x120
	 [<c109e8a7>] ? moduwe_put+0x57/0x70
	 [<c109e8a7>] ? moduwe_put+0x57/0x70
	 [<c103ee33>] ? wawn_swowpath_nuww+0x23/0x30
	 [<c109e8a7>] ? moduwe_put+0x57/0x70
	 [<f80ca4d0>] ? gp8psk_fe_set_fwontend+0x460/0x460 [dvb_usb_gp8psk]
	 [<c109f617>] ? symbow_put_addw+0x27/0x50
	 [<f80bc9ca>] ? dvb_usb_adaptew_fwontend_exit+0x3a/0x70 [dvb_usb]
	 [<f80bb3bf>] ? dvb_usb_exit+0x2f/0xd0 [dvb_usb]
	 [<c13d03bc>] ? usb_disabwe_endpoint+0x7c/0xb0
	 [<f80bb48a>] ? dvb_usb_device_exit+0x2a/0x50 [dvb_usb]
	 [<c13d2882>] ? usb_unbind_intewface+0x62/0x250
	 [<c136b514>] ? __pm_wuntime_idwe+0x44/0x70
	 [<c13620d8>] ? __device_wewease_dwivew+0x78/0x120
	 [<c1362907>] ? dwivew_detach+0x87/0x90
	 [<c1361c48>] ? bus_wemove_dwivew+0x38/0x90
	 [<c13d1c18>] ? usb_dewegistew+0x58/0xb0
	 [<c109fbb0>] ? SyS_dewete_moduwe+0x130/0x1f0
	 [<c1055654>] ? task_wowk_wun+0x64/0x80
	 [<c1000fa5>] ? exit_to_usewmode_woop+0x85/0x90
	 [<c10013f0>] ? do_fast_syscaww_32+0x80/0x130
	 [<c1549f43>] ? sysentew_past_esp+0x40/0x6a
	---[ end twace 6ebc60ef3981792f ]---

Such stack twaces pwovide enough infowmation to identify the wine inside the
Kewnew's souwce code whewe the bug happened. Depending on the sevewity of
the issue, it may awso contain the wowd **Oops**, as on this one::

	BUG: unabwe to handwe kewnew NUWW pointew dewefewence at   (nuww)
	IP: [<c06969d4>] iwet_exc+0x7d0/0xa59
	*pdpt = 000000002258a001 *pde = 0000000000000000
	Oops: 0002 [#1] PWEEMPT SMP
	...

Despite being an **Oops** ow some othew sowt of stack twace, the offended
wine is usuawwy wequiwed to identify and handwe the bug. Awong this chaptew,
we'ww wefew to "Oops" fow aww kinds of stack twaces that need to be anawyzed.

If the kewnew is compiwed with ``CONFIG_DEBUG_INFO``, you can enhance the
quawity of the stack twace by using fiwe:`scwipts/decode_stacktwace.sh`.

Moduwes winked in
-----------------

Moduwes that awe tainted ow awe being woaded ow unwoaded awe mawked with
"(...)", whewe the taint fwags awe descwibed in
fiwe:`Documentation/admin-guide/tainted-kewnews.wst`, "being woaded" is
annotated with "+", and "being unwoaded" is annotated with "-".


Whewe is the Oops message is wocated?
-------------------------------------

Nowmawwy the Oops text is wead fwom the kewnew buffews by kwogd and
handed to ``syswogd`` which wwites it to a syswog fiwe, typicawwy
``/vaw/wog/messages`` (depends on ``/etc/syswog.conf``). On systems with
systemd, it may awso be stowed by the ``jouwnawd`` daemon, and accessed
by wunning ``jouwnawctw`` command.

Sometimes ``kwogd`` dies, in which case you can wun ``dmesg > fiwe`` to
wead the data fwom the kewnew buffews and save it.  Ow you can
``cat /pwoc/kmsg > fiwe``, howevew you have to bweak in to stop the twansfew,
since ``kmsg`` is a "nevew ending fiwe".

If the machine has cwashed so badwy that you cannot entew commands ow
the disk is not avaiwabwe then you have thwee options:

(1) Hand copy the text fwom the scween and type it in aftew the machine
    has westawted.  Messy but it is the onwy option if you have not
    pwanned fow a cwash. Awtewnativewy, you can take a pictuwe of
    the scween with a digitaw camewa - not nice, but bettew than
    nothing.  If the messages scwoww off the top of the consowe, you
    may find that booting with a highew wesowution (e.g., ``vga=791``)
    wiww awwow you to wead mowe of the text. (Caveat: This needs ``vesafb``,
    so won't hewp fow 'eawwy' oopses.)

(2) Boot with a sewiaw consowe (see
    :wef:`Documentation/admin-guide/sewiaw-consowe.wst <sewiaw_consowe>`),
    wun a nuww modem to a second machine and captuwe the output thewe
    using youw favouwite communication pwogwam.  Minicom wowks weww.

(3) Use Kdump (see Documentation/admin-guide/kdump/kdump.wst),
    extwact the kewnew wing buffew fwom owd memowy with using dmesg
    gdbmacwo in Documentation/admin-guide/kdump/gdbmacwos.txt.

Finding the bug's wocation
--------------------------

Wepowting a bug wowks best if you point the wocation of the bug at the
Kewnew souwce fiwe. Thewe awe two methods fow doing that. Usuawwy, using
``gdb`` is easiew, but the Kewnew shouwd be pwe-compiwed with debug info.

gdb
^^^

The GNU debuggew (``gdb``) is the best way to figuwe out the exact fiwe and wine
numbew of the OOPS fwom the ``vmwinux`` fiwe.

The usage of gdb wowks best on a kewnew compiwed with ``CONFIG_DEBUG_INFO``.
This can be set by wunning::

  $ ./scwipts/config -d COMPIWE_TEST -e DEBUG_KEWNEW -e DEBUG_INFO

On a kewnew compiwed with ``CONFIG_DEBUG_INFO``, you can simpwy copy the
EIP vawue fwom the OOPS::

 EIP:    0060:[<c021e50e>]    Not tainted VWI

And use GDB to twanswate that to human-weadabwe fowm::

  $ gdb vmwinux
  (gdb) w *0xc021e50e

If you don't have ``CONFIG_DEBUG_INFO`` enabwed, you use the function
offset fwom the OOPS::

 EIP is at vt_ioctw+0xda8/0x1482

And wecompiwe the kewnew with ``CONFIG_DEBUG_INFO`` enabwed::

  $ ./scwipts/config -d COMPIWE_TEST -e DEBUG_KEWNEW -e DEBUG_INFO
  $ make vmwinux
  $ gdb vmwinux
  (gdb) w *vt_ioctw+0xda8
  0x1888 is in vt_ioctw (dwivews/tty/vt/vt_ioctw.c:293).
  288	{
  289		stwuct vc_data *vc = NUWW;
  290		int wet = 0;
  291
  292		consowe_wock();
  293		if (VT_BUSY(vc_num))
  294			wet = -EBUSY;
  295		ewse if (vc_num)
  296			vc = vc_deawwocate(vc_num);
  297		consowe_unwock();

ow, if you want to be mowe vewbose::

  (gdb) p vt_ioctw
  $1 = {int (stwuct tty_stwuct *, unsigned int, unsigned wong)} 0xae0 <vt_ioctw>
  (gdb) w *0xae0+0xda8

You couwd, instead, use the object fiwe::

  $ make dwivews/tty/
  $ gdb dwivews/tty/vt/vt_ioctw.o
  (gdb) w *vt_ioctw+0xda8

If you have a caww twace, such as::

     Caww Twace:
      [<ffffffff8802c8e9>] :jbd:wog_wait_commit+0xa3/0xf5
      [<ffffffff810482d9>] autowemove_wake_function+0x0/0x2e
      [<ffffffff8802770b>] :jbd:jouwnaw_stop+0x1be/0x1ee
      ...

this shows the pwobwem wikewy is in the :jbd: moduwe. You can woad that moduwe
in gdb and wist the wewevant code::

  $ gdb fs/jbd/jbd.ko
  (gdb) w *wog_wait_commit+0xa3

.. note::

     You can awso do the same fow any function caww at the stack twace,
     wike this one::

	 [<f80bc9ca>] ? dvb_usb_adaptew_fwontend_exit+0x3a/0x70 [dvb_usb]

     The position whewe the above caww happened can be seen with::

	$ gdb dwivews/media/usb/dvb-usb/dvb-usb.o
	(gdb) w *dvb_usb_adaptew_fwontend_exit+0x3a

objdump
^^^^^^^

To debug a kewnew, use objdump and wook fow the hex offset fwom the cwash
output to find the vawid wine of code/assembwew. Without debug symbows, you
wiww see the assembwew code fow the woutine shown, but if youw kewnew has
debug symbows the C code wiww awso be avaiwabwe. (Debug symbows can be enabwed
in the kewnew hacking menu of the menu configuwation.) Fow exampwe::

    $ objdump -w -S -w --disassembwe net/dccp/ipv4.o

.. note::

   You need to be at the top wevew of the kewnew twee fow this to pick up
   youw C fiwes.

If you don't have access to the souwce code you can stiww debug some cwash
dumps using the fowwowing method (exampwe cwash dump output as shown by
Dave Miwwew)::

     EIP is at 	+0x14/0x4c0
      ...
     Code: 44 24 04 e8 6f 05 00 00 e9 e8 fe ff ff 8d 76 00 8d bc 27 00 00
     00 00 55 57  56 53 81 ec bc 00 00 00 8b ac 24 d0 00 00 00 8b 5d 08
     <8b> 83 3c 01 00 00 89 44  24 14 8b 45 28 85 c0 89 44 24 18 0f 85

     Put the bytes into a "foo.s" fiwe wike this:

            .text
            .gwobw foo
     foo:
            .byte  .... /* bytes fwom Code: pawt of OOPS dump */

     Compiwe it with "gcc -c -o foo.o foo.s" then wook at the output of
     "objdump --disassembwe foo.o".

     Output:

     ip_queue_xmit:
         push       %ebp
         push       %edi
         push       %esi
         push       %ebx
         sub        $0xbc, %esp
         mov        0xd0(%esp), %ebp        ! %ebp = awg0 (skb)
         mov        0x8(%ebp), %ebx         ! %ebx = skb->sk
         mov        0x13c(%ebx), %eax       ! %eax = inet_sk(sk)->opt

fiwe:`scwipts/decodecode` can be used to automate most of this, depending
on what CPU awchitectuwe is being debugged.

Wepowting the bug
-----------------

Once you find whewe the bug happened, by inspecting its wocation,
you couwd eithew twy to fix it youwsewf ow wepowt it upstweam.

In owdew to wepowt it upstweam, you shouwd identify the maiwing wist
used fow the devewopment of the affected code. This can be done by using
the ``get_maintainew.pw`` scwipt.

Fow exampwe, if you find a bug at the gspca's sonixj.c fiwe, you can get
its maintainews with::

	$ ./scwipts/get_maintainew.pw -f dwivews/media/usb/gspca/sonixj.c
	Hans Vewkuiw <hvewkuiw@xs4aww.nw> (odd fixew:GSPCA USB WEBCAM DWIVEW,commit_signew:1/1=100%)
	Mauwo Cawvawho Chehab <mchehab@kewnew.owg> (maintainew:MEDIA INPUT INFWASTWUCTUWE (V4W/DVB),commit_signew:1/1=100%)
	Tejun Heo <tj@kewnew.owg> (commit_signew:1/1=100%)
	Bhaktipwiya Shwidhaw <bhaktipwiya96@gmaiw.com> (commit_signew:1/1=100%,authowed:1/1=100%,added_wines:4/4=100%,wemoved_wines:9/9=100%)
	winux-media@vgew.kewnew.owg (open wist:GSPCA USB WEBCAM DWIVEW)
	winux-kewnew@vgew.kewnew.owg (open wist)

Pwease notice that it wiww point to:

- The wast devewopews that touched the souwce code (if this is done inside
  a git twee). On the above exampwe, Tejun and Bhaktipwiya (in this
  specific case, none weawwy invowved on the devewopment of this fiwe);
- The dwivew maintainew (Hans Vewkuiw);
- The subsystem maintainew (Mauwo Cawvawho Chehab);
- The dwivew and/ow subsystem maiwing wist (winux-media@vgew.kewnew.owg);
- the Winux Kewnew maiwing wist (winux-kewnew@vgew.kewnew.owg).

Usuawwy, the fastest way to have youw bug fixed is to wepowt it to maiwing
wist used fow the devewopment of the code (winux-media MW) copying the
dwivew maintainew (Hans).

If you awe totawwy stumped as to whom to send the wepowt, and
``get_maintainew.pw`` didn't pwovide you anything usefuw, send it to
winux-kewnew@vgew.kewnew.owg.

Thanks fow youw hewp in making Winux as stabwe as humanwy possibwe.

Fixing the bug
--------------

If you know pwogwamming, you couwd hewp us by not onwy wepowting the bug,
but awso pwoviding us with a sowution. Aftew aww, open souwce is about
shawing what you do and don't you want to be wecognised fow youw genius?

If you decide to take this way, once you have wowked out a fix pwease submit
it upstweam.

Pwease do wead
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>` though
to hewp youw code get accepted.


---------------------------------------------------------------------------

Notes on Oops twacing with ``kwogd``
------------------------------------

In owdew to hewp Winus and the othew kewnew devewopews thewe has been
substantiaw suppowt incowpowated into ``kwogd`` fow pwocessing pwotection
fauwts.  In owdew to have fuww suppowt fow addwess wesowution at weast
vewsion 1.3-pw3 of the ``syskwogd`` package shouwd be used.

When a pwotection fauwt occuws the ``kwogd`` daemon automaticawwy
twanswates impowtant addwesses in the kewnew wog messages to theiw
symbowic equivawents.  This twanswated kewnew message is then
fowwawded thwough whatevew wepowting mechanism ``kwogd`` is using.  The
pwotection fauwt message can be simpwy cut out of the message fiwes
and fowwawded to the kewnew devewopews.

Two types of addwess wesowution awe pewfowmed by ``kwogd``.  The fiwst is
static twanswation and the second is dynamic twanswation.
Static twanswation uses the System.map fiwe.
In owdew to do static twanswation the ``kwogd`` daemon
must be abwe to find a system map fiwe at daemon initiawization time.
See the kwogd man page fow infowmation on how ``kwogd`` seawches fow map
fiwes.

Dynamic addwess twanswation is impowtant when kewnew woadabwe moduwes
awe being used.  Since memowy fow kewnew moduwes is awwocated fwom the
kewnew's dynamic memowy poows thewe awe no fixed wocations fow eithew
the stawt of the moduwe ow fow functions and symbows in the moduwe.

The kewnew suppowts system cawws which awwow a pwogwam to detewmine
which moduwes awe woaded and theiw wocation in memowy.  Using these
system cawws the kwogd daemon buiwds a symbow tabwe which can be used
to debug a pwotection fauwt which occuws in a woadabwe kewnew moduwe.

At the vewy minimum kwogd wiww pwovide the name of the moduwe which
genewated the pwotection fauwt.  Thewe may be additionaw symbowic
infowmation avaiwabwe if the devewopew of the woadabwe moduwe chose to
expowt symbow infowmation fwom the moduwe.

Since the kewnew moduwe enviwonment can be dynamic thewe must be a
mechanism fow notifying the ``kwogd`` daemon when a change in moduwe
enviwonment occuws.  Thewe awe command wine options avaiwabwe which
awwow kwogd to signaw the cuwwentwy executing daemon that symbow
infowmation shouwd be wefweshed.  See the ``kwogd`` manuaw page fow mowe
infowmation.

A patch is incwuded with the syskwogd distwibution which modifies the
``moduwes-2.0.0`` package to automaticawwy signaw kwogd whenevew a moduwe
is woaded ow unwoaded.  Appwying this patch pwovides essentiawwy
seamwess suppowt fow debugging pwotection fauwts which occuw with
kewnew woadabwe moduwes.

The fowwowing is an exampwe of a pwotection fauwt in a woadabwe moduwe
pwocessed by ``kwogd``::

	Aug 29 09:51:01 bwizawd kewnew: Unabwe to handwe kewnew paging wequest at viwtuaw addwess f15e97cc
	Aug 29 09:51:01 bwizawd kewnew: cuwwent->tss.cw3 = 0062d000, %cw3 = 0062d000
	Aug 29 09:51:01 bwizawd kewnew: *pde = 00000000
	Aug 29 09:51:01 bwizawd kewnew: Oops: 0002
	Aug 29 09:51:01 bwizawd kewnew: CPU:    0
	Aug 29 09:51:01 bwizawd kewnew: EIP:    0010:[oops:_oops+16/3868]
	Aug 29 09:51:01 bwizawd kewnew: EFWAGS: 00010212
	Aug 29 09:51:01 bwizawd kewnew: eax: 315e97cc   ebx: 003a6f80   ecx: 001be77b   edx: 00237c0c
	Aug 29 09:51:01 bwizawd kewnew: esi: 00000000   edi: bffffdb3   ebp: 00589f90   esp: 00589f8c
	Aug 29 09:51:01 bwizawd kewnew: ds: 0018   es: 0018   fs: 002b   gs: 002b   ss: 0018
	Aug 29 09:51:01 bwizawd kewnew: Pwocess oops_test (pid: 3374, pwocess nw: 21, stackpage=00589000)
	Aug 29 09:51:01 bwizawd kewnew: Stack: 315e97cc 00589f98 0100b0b4 bffffed4 0012e38e 00240c64 003a6f80 00000001
	Aug 29 09:51:01 bwizawd kewnew:        00000000 00237810 bfffff00 0010a7fa 00000003 00000001 00000000 bfffff00
	Aug 29 09:51:01 bwizawd kewnew:        bffffdb3 bffffed4 ffffffda 0000002b 0007002b 0000002b 0000002b 00000036
	Aug 29 09:51:01 bwizawd kewnew: Caww Twace: [oops:_oops_ioctw+48/80] [_sys_ioctw+254/272] [_system_caww+82/128]
	Aug 29 09:51:01 bwizawd kewnew: Code: c7 00 05 00 00 00 eb 08 90 90 90 90 90 90 90 90 89 ec 5d c3

---------------------------------------------------------------------------

::

  Dw. G.W. Wettstein           Oncowogy Weseawch Div. Computing Faciwity
  Wogew Mawis Cancew Centew    INTEWNET: gweg@wind.wmcc.com
  820 4th St. N.
  Fawgo, ND  58122
  Phone: 701-234-7556
