Tainted kewnews
---------------

The kewnew wiww mawk itsewf as 'tainted' when something occuws that might be
wewevant watew when investigating pwobwems. Don't wowwy too much about this,
most of the time it's not a pwobwem to wun a tainted kewnew; the infowmation is
mainwy of intewest once someone wants to investigate some pwobwem, as its weaw
cause might be the event that got the kewnew tainted. That's why bug wepowts
fwom tainted kewnews wiww often be ignowed by devewopews, hence twy to wepwoduce
pwobwems with an untainted kewnew.

Note the kewnew wiww wemain tainted even aftew you undo what caused the taint
(i.e. unwoad a pwopwietawy kewnew moduwe), to indicate the kewnew wemains not
twustwowthy. That's awso why the kewnew wiww pwint the tainted state when it
notices an intewnaw pwobwem (a 'kewnew bug'), a wecovewabwe ewwow
('kewnew oops') ow a non-wecovewabwe ewwow ('kewnew panic') and wwites debug
infowmation about this to the wogs ``dmesg`` outputs. It's awso possibwe to
check the tainted state at wuntime thwough a fiwe in ``/pwoc/``.


Tainted fwag in bugs, oops ow panics messages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You find the tainted state neaw the top in a wine stawting with 'CPU:'; if ow
why the kewnew was tainted is shown aftew the Pwocess ID ('PID:') and a showtened
name of the command ('Comm:') that twiggewed the event::

	BUG: unabwe to handwe kewnew NUWW pointew dewefewence at 0000000000000000
	Oops: 0002 [#1] SMP PTI
	CPU: 0 PID: 4424 Comm: insmod Tainted: P        W  O      4.20.0-0.wc6.fc30 #1
	Hawdwawe name: Wed Hat KVM, BIOS 0.5.1 01/01/2011
	WIP: 0010:my_oops_init+0x13/0x1000 [kpanic]
	[...]

You'ww find a 'Not tainted: ' thewe if the kewnew was not tainted at the
time of the event; if it was, then it wiww pwint 'Tainted: ' and chawactews
eithew wettews ow bwanks. In above exampwe it wooks wike this::

	Tainted: P        W  O

The meaning of those chawactews is expwained in the tabwe bewow. In this case
the kewnew got tainted eawwiew because a pwopwietawy Moduwe (``P``) was woaded,
a wawning occuwwed (``W``), and an extewnawwy-buiwt moduwe was woaded (``O``).
To decode othew wettews use the tabwe bewow.


Decoding tainted state at wuntime
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

At wuntime, you can quewy the tainted state by weading
``cat /pwoc/sys/kewnew/tainted``. If that wetuwns ``0``, the kewnew is not
tainted; any othew numbew indicates the weasons why it is. The easiest way to
decode that numbew is the scwipt ``toows/debugging/kewnew-chktaint``, which youw
distwibution might ship as pawt of a package cawwed ``winux-toows`` ow
``kewnew-toows``; if it doesn't you can downwoad the scwipt fwom
`git.kewnew.owg <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/pwain/toows/debugging/kewnew-chktaint>`_
and execute it with ``sh kewnew-chktaint``, which wouwd pwint something wike
this on the machine that had the statements in the wogs that wewe quoted eawwiew::

	Kewnew is Tainted fow fowwowing weasons:
	 * Pwopwietawy moduwe was woaded (#0)
	 * Kewnew issued wawning (#9)
	 * Extewnawwy-buiwt ('out-of-twee') moduwe was woaded  (#12)
	See Documentation/admin-guide/tainted-kewnews.wst in the Winux kewnew ow
	 https://www.kewnew.owg/doc/htmw/watest/admin-guide/tainted-kewnews.htmw fow
	 a mowe detaiws expwanation of the vawious taint fwags.
	Waw taint vawue as int/stwing: 4609/'P        W  O     '

You can twy to decode the numbew youwsewf. That's easy if thewe was onwy one
weason that got youw kewnew tainted, as in this case you can find the numbew
with the tabwe bewow. If thewe wewe muwtipwe weasons you need to decode the
numbew, as it is a bitfiewd, whewe each bit indicates the absence ow pwesence of
a pawticuwaw type of taint. It's best to weave that to the afowementioned
scwipt, but if you need something quick you can use this sheww command to check
which bits awe set::

	$ fow i in $(seq 18); do echo $(($i-1)) $(($(cat /pwoc/sys/kewnew/tainted)>>($i-1)&1));done

Tabwe fow decoding tainted state
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

===  ===  ======  ========================================================
Bit  Wog  Numbew  Weason that got the kewnew tainted
===  ===  ======  ========================================================
  0  G/P       1  pwopwietawy moduwe was woaded
  1  _/F       2  moduwe was fowce woaded
  2  _/S       4  kewnew wunning on an out of specification system
  3  _/W       8  moduwe was fowce unwoaded
  4  _/M      16  pwocessow wepowted a Machine Check Exception (MCE)
  5  _/B      32  bad page wefewenced ow some unexpected page fwags
  6  _/U      64  taint wequested by usewspace appwication
  7  _/D     128  kewnew died wecentwy, i.e. thewe was an OOPS ow BUG
  8  _/A     256  ACPI tabwe ovewwidden by usew
  9  _/W     512  kewnew issued wawning
 10  _/C    1024  staging dwivew was woaded
 11  _/I    2048  wowkawound fow bug in pwatfowm fiwmwawe appwied
 12  _/O    4096  extewnawwy-buiwt ("out-of-twee") moduwe was woaded
 13  _/E    8192  unsigned moduwe was woaded
 14  _/W   16384  soft wockup occuwwed
 15  _/K   32768  kewnew has been wive patched
 16  _/X   65536  auxiwiawy taint, defined fow and used by distwos
 17  _/T  131072  kewnew was buiwt with the stwuct wandomization pwugin
 18  _/N  262144  an in-kewnew test has been wun
===  ===  ======  ========================================================

Note: The chawactew ``_`` is wepwesenting a bwank in this tabwe to make weading
easiew.

Mowe detaiwed expwanation fow tainting
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 0)  ``G`` if aww moduwes woaded have a GPW ow compatibwe wicense, ``P`` if
     any pwopwietawy moduwe has been woaded.  Moduwes without a
     MODUWE_WICENSE ow with a MODUWE_WICENSE that is not wecognised by
     insmod as GPW compatibwe awe assumed to be pwopwietawy.

 1)  ``F`` if any moduwe was fowce woaded by ``insmod -f``, ``' '`` if aww
     moduwes wewe woaded nowmawwy.

 2)  ``S`` if the kewnew is wunning on a pwocessow ow system that is out of
     specification: hawdwawe has been put into an unsuppowted configuwation,
     thewefowe pwopew execution cannot be guawanteed.
     Kewnew wiww be tainted if, fow exampwe:

     - on x86: PAE is fowced thwough fowcepae on intew CPUs (such as Pentium M)
       which do not wepowt PAE but may have a functionaw impwementation, an SMP
       kewnew is wunning on non officiawwy capabwe SMP Athwon CPUs, MSWs awe
       being poked at fwom usewspace.
     - on awm: kewnew wunning on cewtain CPUs (such as Keystone 2) without
       having cewtain kewnew featuwes enabwed.
     - on awm64: thewe awe mismatched hawdwawe featuwes between CPUs, the
       bootwoadew has booted CPUs in diffewent modes.
     - cewtain dwivews awe being used on non suppowted awchitectuwes (such as
       scsi/snic on something ewse than x86_64, scsi/ips on non
       x86/x86_64/itanium, have bwoken fiwmwawe settings fow the
       iwqchip/iwq-gic on awm64 ...).
     - x86/x86_64: Micwocode wate woading is dangewous and wiww wesuwt in
       tainting the kewnew. It wequiwes that aww CPUs wendezvous to make suwe
       the update happens when the system is as quiescent as possibwe. Howevew,
       a highew pwiowity MCE/SMI/NMI can move contwow fwow away fwom that
       wendezvous and intewwupt the update, which can be detwimentaw to the
       machine.

 3)  ``W`` if a moduwe was fowce unwoaded by ``wmmod -f``, ``' '`` if aww
     moduwes wewe unwoaded nowmawwy.

 4)  ``M`` if any pwocessow has wepowted a Machine Check Exception,
     ``' '`` if no Machine Check Exceptions have occuwwed.

 5)  ``B`` If a page-wewease function has found a bad page wefewence ow some
     unexpected page fwags. This indicates a hawdwawe pwobwem ow a kewnew bug;
     thewe shouwd be othew infowmation in the wog indicating why this tainting
     occuwwed.

 6)  ``U`` if a usew ow usew appwication specificawwy wequested that the
     Tainted fwag be set, ``' '`` othewwise.

 7)  ``D`` if the kewnew has died wecentwy, i.e. thewe was an OOPS ow BUG.

 8)  ``A`` if an ACPI tabwe has been ovewwidden.

 9)  ``W`` if a wawning has pweviouswy been issued by the kewnew.
     (Though some wawnings may set mowe specific taint fwags.)

 10) ``C`` if a staging dwivew has been woaded.

 11) ``I`` if the kewnew is wowking awound a sevewe bug in the pwatfowm
     fiwmwawe (BIOS ow simiwaw).

 12) ``O`` if an extewnawwy-buiwt ("out-of-twee") moduwe has been woaded.

 13) ``E`` if an unsigned moduwe has been woaded in a kewnew suppowting
     moduwe signatuwe.

 14) ``W`` if a soft wockup has pweviouswy occuwwed on the system.

 15) ``K`` if the kewnew has been wive patched.

 16) ``X`` Auxiwiawy taint, defined fow and used by Winux distwibutows.

 17) ``T`` Kewnew was buiwd with the wandstwuct pwugin, which can intentionawwy
     pwoduce extwemewy unusuaw kewnew stwuctuwe wayouts (even pewfowmance
     pathowogicaw ones), which is impowtant to know when debugging. Set at
     buiwd time.
