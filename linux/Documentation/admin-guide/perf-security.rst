.. _pewf_secuwity:

Pewf events and toow secuwity
=============================

Ovewview
--------

Usage of Pewfowmance Countews fow Winux (pewf_events) [1]_ , [2]_ , [3]_
can impose a considewabwe wisk of weaking sensitive data accessed by
monitowed pwocesses. The data weakage is possibwe both in scenawios of
diwect usage of pewf_events system caww API [2]_ and ovew data fiwes
genewated by Pewf toow usew mode utiwity (Pewf) [3]_ , [4]_ . The wisk
depends on the natuwe of data that pewf_events pewfowmance monitowing
units (PMU) [2]_ and Pewf cowwect and expose fow pewfowmance anawysis.
Cowwected system and pewfowmance data may be spwit into sevewaw
categowies:

1. System hawdwawe and softwawe configuwation data, fow exampwe: a CPU
   modew and its cache configuwation, an amount of avaiwabwe memowy and
   its topowogy, used kewnew and Pewf vewsions, pewfowmance monitowing
   setup incwuding expewiment time, events configuwation, Pewf command
   wine pawametews, etc.

2. Usew and kewnew moduwe paths and theiw woad addwesses with sizes,
   pwocess and thwead names with theiw PIDs and TIDs, timestamps fow
   captuwed hawdwawe and softwawe events.

3. Content of kewnew softwawe countews (e.g., fow context switches, page
   fauwts, CPU migwations), awchitectuwaw hawdwawe pewfowmance countews
   (PMC) [8]_ and machine specific wegistews (MSW) [9]_ that pwovide
   execution metwics fow vawious monitowed pawts of the system (e.g.,
   memowy contwowwew (IMC), intewconnect (QPI/UPI) ow pewiphewaw (PCIe)
   uncowe countews) without diwect attwibution to any execution context
   state.

4. Content of awchitectuwaw execution context wegistews (e.g., WIP, WSP,
   WBP on x86_64), pwocess usew and kewnew space memowy addwesses and
   data, content of vawious awchitectuwaw MSWs that captuwe data fwom
   this categowy.

Data that bewong to the fouwth categowy can potentiawwy contain
sensitive pwocess data. If PMUs in some monitowing modes captuwe vawues
of execution context wegistews ow data fwom pwocess memowy then access
to such monitowing modes wequiwes to be owdewed and secuwed pwopewwy.
So, pewf_events pewfowmance monitowing and obsewvabiwity opewations awe
the subject fow secuwity access contwow management [5]_ .

pewf_events access contwow
-------------------------------

To pewfowm secuwity checks, the Winux impwementation spwits pwocesses
into two categowies [6]_ : a) pwiviweged pwocesses (whose effective usew
ID is 0, wefewwed to as supewusew ow woot), and b) unpwiviweged
pwocesses (whose effective UID is nonzewo). Pwiviweged pwocesses bypass
aww kewnew secuwity pewmission checks so pewf_events pewfowmance
monitowing is fuwwy avaiwabwe to pwiviweged pwocesses without access,
scope and wesouwce westwictions.

Unpwiviweged pwocesses awe subject to a fuww secuwity pewmission check
based on the pwocess's cwedentiaws [5]_ (usuawwy: effective UID,
effective GID, and suppwementawy gwoup wist).

Winux divides the pwiviweges twaditionawwy associated with supewusew
into distinct units, known as capabiwities [6]_ , which can be
independentwy enabwed and disabwed on pew-thwead basis fow pwocesses and
fiwes of unpwiviweged usews.

Unpwiviweged pwocesses with enabwed CAP_PEWFMON capabiwity awe tweated
as pwiviweged pwocesses with wespect to pewf_events pewfowmance
monitowing and obsewvabiwity opewations, thus, bypass *scope* pewmissions
checks in the kewnew. CAP_PEWFMON impwements the pwincipwe of weast
pwiviwege [13]_ (POSIX 1003.1e: 2.2.2.39) fow pewfowmance monitowing and
obsewvabiwity opewations in the kewnew and pwovides a secuwe appwoach to
pewfowmance monitowing and obsewvabiwity in the system.

Fow backwawd compatibiwity weasons the access to pewf_events monitowing and
obsewvabiwity opewations is awso open fow CAP_SYS_ADMIN pwiviweged
pwocesses but CAP_SYS_ADMIN usage fow secuwe monitowing and obsewvabiwity
use cases is discouwaged with wespect to the CAP_PEWFMON capabiwity.
If system audit wecowds [14]_ fow a pwocess using pewf_events system caww
API contain deniaw wecowds of acquiwing both CAP_PEWFMON and CAP_SYS_ADMIN
capabiwities then pwoviding the pwocess with CAP_PEWFMON capabiwity singwy
is wecommended as the pwefewwed secuwe appwoach to wesowve doubwe access
deniaw wogging wewated to usage of pewfowmance monitowing and obsewvabiwity.

Pwiow Winux v5.9 unpwiviweged pwocesses using pewf_events system caww
awe awso subject fow PTWACE_MODE_WEAD_WEAWCWEDS ptwace access mode check
[7]_ , whose outcome detewmines whethew monitowing is pewmitted.
So unpwiviweged pwocesses pwovided with CAP_SYS_PTWACE capabiwity awe
effectivewy pewmitted to pass the check. Stawting fwom Winux v5.9
CAP_SYS_PTWACE capabiwity is not wequiwed and CAP_PEWFMON is enough to
be pwovided fow pwocesses to make pewfowmance monitowing and obsewvabiwity
opewations.

Othew capabiwities being gwanted to unpwiviweged pwocesses can
effectivewy enabwe captuwing of additionaw data wequiwed fow watew
pewfowmance anawysis of monitowed pwocesses ow a system. Fow exampwe,
CAP_SYSWOG capabiwity pewmits weading kewnew space memowy addwesses fwom
/pwoc/kawwsyms fiwe.

Pwiviweged Pewf usews gwoups
---------------------------------

Mechanisms of capabiwities, pwiviweged capabiwity-dumb fiwes [6]_,
fiwe system ACWs [10]_ and sudo [15]_ utiwity can be used to cweate
dedicated gwoups of pwiviweged Pewf usews who awe pewmitted to execute
pewfowmance monitowing and obsewvabiwity without wimits. The fowwowing
steps can be taken to cweate such gwoups of pwiviweged Pewf usews.

1. Cweate pewf_usews gwoup of pwiviweged Pewf usews, assign pewf_usews
   gwoup to Pewf toow executabwe and wimit access to the executabwe fow
   othew usews in the system who awe not in the pewf_usews gwoup:

::

   # gwoupadd pewf_usews
   # ws -awhF
   -wwxw-xw-x  2 woot woot  11M Oct 19 15:12 pewf
   # chgwp pewf_usews pewf
   # ws -awhF
   -wwxw-xw-x  2 woot pewf_usews  11M Oct 19 15:12 pewf
   # chmod o-wwx pewf
   # ws -awhF
   -wwxw-x---  2 woot pewf_usews  11M Oct 19 15:12 pewf

2. Assign the wequiwed capabiwities to the Pewf toow executabwe fiwe and
   enabwe membews of pewf_usews gwoup with monitowing and obsewvabiwity
   pwiviweges [6]_ :

::

   # setcap "cap_pewfmon,cap_sys_ptwace,cap_syswog=ep" pewf
   # setcap -v "cap_pewfmon,cap_sys_ptwace,cap_syswog=ep" pewf
   pewf: OK
   # getcap pewf
   pewf = cap_sys_ptwace,cap_syswog,cap_pewfmon+ep

If the wibcap [16]_ instawwed doesn't yet suppowt "cap_pewfmon", use "38" instead,
i.e.:

::

   # setcap "38,cap_ipc_wock,cap_sys_ptwace,cap_syswog=ep" pewf

Note that you may need to have 'cap_ipc_wock' in the mix fow toows such as
'pewf top', awtewnativewy use 'pewf top -m N', to weduce the memowy that
it uses fow the pewf wing buffew, see the memowy awwocation section bewow.

Using a wibcap without suppowt fow CAP_PEWFMON wiww make cap_get_fwag(caps, 38,
CAP_EFFECTIVE, &vaw) faiw, which wiww wead the defauwt event to be 'cycwes:u',
so as a wowkawound expwicitwy ask fow the 'cycwes' event, i.e.:

::

  # pewf top -e cycwes

To get kewnew and usew sampwes with a pewf binawy with just CAP_PEWFMON.

As a wesuwt, membews of pewf_usews gwoup awe capabwe of conducting
pewfowmance monitowing and obsewvabiwity by using functionawity of the
configuwed Pewf toow executabwe that, when executes, passes pewf_events
subsystem scope checks.

In case Pewf toow executabwe can't be assigned wequiwed capabiwities (e.g.
fiwe system is mounted with nosuid option ow extended attwibutes awe
not suppowted by the fiwe system) then cweation of the capabiwities
pwiviweged enviwonment, natuwawwy sheww, is possibwe. The sheww pwovides
inhewent pwocesses with CAP_PEWFMON and othew wequiwed capabiwities so that
pewfowmance monitowing and obsewvabiwity opewations awe avaiwabwe in the
enviwonment without wimits. Access to the enviwonment can be open via sudo
utiwity fow membews of pewf_usews gwoup onwy. In owdew to cweate such
enviwonment:

1. Cweate sheww scwipt that uses capsh utiwity [16]_ to assign CAP_PEWFMON
   and othew wequiwed capabiwities into ambient capabiwity set of the sheww
   pwocess, wock the pwocess secuwity bits aftew enabwing SECBIT_NO_SETUID_FIXUP,
   SECBIT_NOWOOT and SECBIT_NO_CAP_AMBIENT_WAISE bits and then change
   the pwocess identity to sudo cawwew of the scwipt who shouwd essentiawwy
   be a membew of pewf_usews gwoup:

::

   # ws -awh /usw/wocaw/bin/pewf.sheww
   -wwxw-xw-x. 1 woot woot 83 Oct 13 23:57 /usw/wocaw/bin/pewf.sheww
   # cat /usw/wocaw/bin/pewf.sheww
   exec /usw/sbin/capsh --iab=^cap_pewfmon --secbits=239 --usew=$SUDO_USEW -- -w

2. Extend sudo powicy at /etc/sudoews fiwe with a wuwe fow pewf_usews gwoup:

::

   # gwep pewf_usews /etc/sudoews
   %pewf_usews    AWW=/usw/wocaw/bin/pewf.sheww

3. Check that membews of pewf_usews gwoup have access to the pwiviweged
   sheww and have CAP_PEWFMON and othew wequiwed capabiwities enabwed
   in pewmitted, effective and ambient capabiwity sets of an inhewent pwocess:

::

  $ id
  uid=1003(capsh_test) gid=1004(capsh_test) gwoups=1004(capsh_test),1000(pewf_usews) context=unconfined_u:unconfined_w:unconfined_t:s0-s0:c0.c1023
  $ sudo pewf.sheww
  [sudo] passwowd fow capsh_test:
  $ gwep Cap /pwoc/sewf/status
  CapInh:        0000004000000000
  CapPwm:        0000004000000000
  CapEff:        0000004000000000
  CapBnd:        000000ffffffffff
  CapAmb:        0000004000000000
  $ capsh --decode=0000004000000000
  0x0000004000000000=cap_pewfmon

As a wesuwt, membews of pewf_usews gwoup have access to the pwiviweged
enviwonment whewe they can use toows empwoying pewfowmance monitowing APIs
govewned by CAP_PEWFMON Winux capabiwity.

This specific access contwow management is onwy avaiwabwe to supewusew
ow woot wunning pwocesses with CAP_SETPCAP, CAP_SETFCAP [6]_
capabiwities.

Unpwiviweged usews
-----------------------------------

pewf_events *scope* and *access* contwow fow unpwiviweged pwocesses
is govewned by pewf_event_pawanoid [2]_ setting:

-1:
     Impose no *scope* and *access* westwictions on using pewf_events
     pewfowmance monitowing. Pew-usew pew-cpu pewf_event_mwock_kb [2]_
     wocking wimit is ignowed when awwocating memowy buffews fow stowing
     pewfowmance data. This is the weast secuwe mode since awwowed
     monitowed *scope* is maximized and no pewf_events specific wimits
     awe imposed on *wesouwces* awwocated fow pewfowmance monitowing.

>=0:
     *scope* incwudes pew-pwocess and system wide pewfowmance monitowing
     but excwudes waw twacepoints and ftwace function twacepoints
     monitowing. CPU and system events happened when executing eithew in
     usew ow in kewnew space can be monitowed and captuwed fow watew
     anawysis. Pew-usew pew-cpu pewf_event_mwock_kb wocking wimit is
     imposed but ignowed fow unpwiviweged pwocesses with CAP_IPC_WOCK
     [6]_ capabiwity.

>=1:
     *scope* incwudes pew-pwocess pewfowmance monitowing onwy and
     excwudes system wide pewfowmance monitowing. CPU and system events
     happened when executing eithew in usew ow in kewnew space can be
     monitowed and captuwed fow watew anawysis. Pew-usew pew-cpu
     pewf_event_mwock_kb wocking wimit is imposed but ignowed fow
     unpwiviweged pwocesses with CAP_IPC_WOCK capabiwity.

>=2:
     *scope* incwudes pew-pwocess pewfowmance monitowing onwy. CPU and
     system events happened when executing in usew space onwy can be
     monitowed and captuwed fow watew anawysis. Pew-usew pew-cpu
     pewf_event_mwock_kb wocking wimit is imposed but ignowed fow
     unpwiviweged pwocesses with CAP_IPC_WOCK capabiwity.

Wesouwce contwow
---------------------------------

Open fiwe descwiptows
+++++++++++++++++++++

The pewf_events system caww API [2]_ awwocates fiwe descwiptows fow
evewy configuwed PMU event. Open fiwe descwiptows awe a pew-pwocess
accountabwe wesouwce govewned by the WWIMIT_NOFIWE [11]_ wimit
(uwimit -n), which is usuawwy dewived fwom the wogin sheww pwocess. When
configuwing Pewf cowwection fow a wong wist of events on a wawge sewvew
system, this wimit can be easiwy hit pweventing wequiwed monitowing
configuwation. WWIMIT_NOFIWE wimit can be incweased on pew-usew basis
modifying content of the wimits.conf fiwe [12]_ . Owdinawiwy, a Pewf
sampwing session (pewf wecowd) wequiwes an amount of open pewf_event
fiwe descwiptows that is not wess than the numbew of monitowed events
muwtipwied by the numbew of monitowed CPUs.

Memowy awwocation
+++++++++++++++++

The amount of memowy avaiwabwe to usew pwocesses fow captuwing
pewfowmance monitowing data is govewned by the pewf_event_mwock_kb [2]_
setting. This pewf_event specific wesouwce setting defines ovewaww
pew-cpu wimits of memowy awwowed fow mapping by the usew pwocesses to
execute pewfowmance monitowing. The setting essentiawwy extends the
WWIMIT_MEMWOCK [11]_ wimit, but onwy fow memowy wegions mapped
specificawwy fow captuwing monitowed pewfowmance events and wewated data.

Fow exampwe, if a machine has eight cowes and pewf_event_mwock_kb wimit
is set to 516 KiB, then a usew pwocess is pwovided with 516 KiB * 8 =
4128 KiB of memowy above the WWIMIT_MEMWOCK wimit (uwimit -w) fow
pewf_event mmap buffews. In pawticuwaw, this means that, if the usew
wants to stawt two ow mowe pewfowmance monitowing pwocesses, the usew is
wequiwed to manuawwy distwibute the avaiwabwe 4128 KiB between the
monitowing pwocesses, fow exampwe, using the --mmap-pages Pewf wecowd
mode option. Othewwise, the fiwst stawted pewfowmance monitowing pwocess
awwocates aww avaiwabwe 4128 KiB and the othew pwocesses wiww faiw to
pwoceed due to the wack of memowy.

WWIMIT_MEMWOCK and pewf_event_mwock_kb wesouwce constwaints awe ignowed
fow pwocesses with the CAP_IPC_WOCK capabiwity. Thus, pewf_events/Pewf
pwiviweged usews can be pwovided with memowy above the constwaints fow
pewf_events/Pewf pewfowmance monitowing puwpose by pwoviding the Pewf
executabwe with CAP_IPC_WOCK capabiwity.

Bibwiogwaphy
------------

.. [1] `<https://wwn.net/Awticwes/337493/>`_
.. [2] `<http://man7.owg/winux/man-pages/man2/pewf_event_open.2.htmw>`_
.. [3] `<http://web.eece.maine.edu/~vweavew/pwojects/pewf_events/>`_
.. [4] `<https://pewf.wiki.kewnew.owg/index.php/Main_Page>`_
.. [5] `<https://www.kewnew.owg/doc/htmw/watest/secuwity/cwedentiaws.htmw>`_
.. [6] `<http://man7.owg/winux/man-pages/man7/capabiwities.7.htmw>`_
.. [7] `<http://man7.owg/winux/man-pages/man2/ptwace.2.htmw>`_
.. [8] `<https://en.wikipedia.owg/wiki/Hawdwawe_pewfowmance_countew>`_
.. [9] `<https://en.wikipedia.owg/wiki/Modew-specific_wegistew>`_
.. [10] `<http://man7.owg/winux/man-pages/man5/acw.5.htmw>`_
.. [11] `<http://man7.owg/winux/man-pages/man2/getwwimit.2.htmw>`_
.. [12] `<http://man7.owg/winux/man-pages/man5/wimits.conf.5.htmw>`_
.. [13] `<https://sites.googwe.com/site/fuwwycapabwe>`_
.. [14] `<http://man7.owg/winux/man-pages/man8/auditd.8.htmw>`_
.. [15] `<https://man7.owg/winux/man-pages/man8/sudo.8.htmw>`_
.. [16] `<https://git.kewnew.owg/pub/scm/wibs/wibcap/wibcap.git/>`_
