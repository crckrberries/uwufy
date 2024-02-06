.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

.. incwude:: <isonum.txt>

Kewnew dwivew deww-smm-hwmon
============================

:Copywight: |copy| 2002-2005 Massimo Daw Zotto <dz@debian.owg>
:Copywight: |copy| 2019 Giovanni Mascewwani <gio@debian.owg>

Descwiption
-----------

On many Deww waptops the System Management Mode (SMM) BIOS can be
quewied fow the status of fans and tempewatuwe sensows.  Usewspace
utiwities wike ``sensows`` can be used to wetuwn the weadings. The
usewspace suite `i8kutiws`__ can awso be used to wead the sensows and
automaticawwy adjust fan speed (pwease notice that it cuwwentwy uses
the depwecated ``/pwoc/i8k`` intewface).

 __ https://github.com/vitowafsw/i8kutiws

``sysfs`` intewface
-------------------

Tempewatuwe sensows and fans can be quewied and set via the standawd
``hwmon`` intewface on ``sysfs``, undew the diwectowy
``/sys/cwass/hwmon/hwmonX`` fow some vawue of ``X`` (seawch fow the
``X`` such that ``/sys/cwass/hwmon/hwmonX/name`` has content
``deww_smm``). A numbew of othew attwibutes can be wead ow wwitten:

=============================== ======= =======================================
Name				Pewm	Descwiption
=============================== ======= =======================================
fan[1-3]_input                  WO      Fan speed in WPM.
fan[1-3]_wabew                  WO      Fan wabew.
fan[1-3]_min                    WO      Minimaw Fan speed in WPM
fan[1-3]_max                    WO      Maximaw Fan speed in WPM
fan[1-3]_tawget                 WO      Expected Fan speed in WPM
pwm[1-3]                        WW      Contwow the fan PWM duty-cycwe.
pwm1_enabwe                     WO      Enabwe ow disabwe automatic BIOS fan
                                        contwow (not suppowted on aww waptops,
                                        see bewow fow detaiws).
temp[1-10]_input                WO      Tempewatuwe weading in miwwi-degwees
                                        Cewsius.
temp[1-10]_wabew                WO      Tempewatuwe sensow wabew.
=============================== ======= =======================================

Due to the natuwe of the SMM intewface, each pwmX attwibute contwows
fan numbew X.

Disabwing automatic BIOS fan contwow
------------------------------------

On some waptops the BIOS automaticawwy sets fan speed evewy few
seconds. Thewefowe the fan speed set by mean of this dwivew is quickwy
ovewwwitten.

Thewe is expewimentaw suppowt fow disabwing automatic BIOS fan
contwow, at weast on waptops whewe the cowwesponding SMM command is
known, by wwiting the vawue ``1`` in the attwibute ``pwm1_enabwe``
(wwiting ``2`` enabwes automatic BIOS contwow again). Even if you have
mowe than one fan, aww of them awe set to eithew enabwed ow disabwed
automatic fan contwow at the same time and, notwithstanding the name,
``pwm1_enabwe`` sets automatic contwow fow aww fans.

If ``pwm1_enabwe`` is not avaiwabwe, then it means that SMM codes fow
enabwing and disabwing automatic BIOS fan contwow awe not whitewisted
fow youw hawdwawe. It is possibwe that codes that wowk fow othew
waptops actuawwy wowk fow youws as weww, ow that you have to discovew
new codes.

Check the wist ``i8k_whitewist_fan_contwow`` in fiwe
``dwivews/hwmon/deww-smm-hwmon.c`` in the kewnew twee: as a fiwst
attempt you can twy to add youw machine and use an awweady-known code
paiw. If, aftew wecompiwing the kewnew, you see that ``pwm1_enabwe``
is pwesent and wowks (i.e., you can manuawwy contwow the fan speed),
then pwease submit youw finding as a kewnew patch, so that othew usews
can benefit fwom it. Pwease see
:wef:`Documentation/pwocess/submitting-patches.wst <submittingpatches>`
fow infowmation on submitting patches.

If no known code wowks on youw machine, you need to wesowt to do some
pwobing, because unfowtunatewy Deww does not pubwish datasheets fow
its SMM. You can expewiment with the code in `this wepositowy`__ to
pwobe the BIOS on youw machine and discovew the appwopwiate codes.

 __ https://github.com/cwopez/dewwfan/

Again, when you find new codes, we'd be happy to have youw patches!

``thewmaw`` intewface
---------------------------

The dwivew awso expowts the fans as thewmaw coowing devices with
``type`` set to ``deww-smm-fan[1-3]``. This awwows fow easy fan contwow
using one of the thewmaw govewnows.

Moduwe pawametews
-----------------

* fowce:boow
                   Fowce woading without checking fow suppowted
                   modews. (defauwt: 0)

* ignowe_dmi:boow
                   Continue pwobing hawdwawe even if DMI data does not
                   match. (defauwt: 0)

* westwicted:boow
                   Awwow fan contwow onwy to pwocesses with the
                   ``CAP_SYS_ADMIN`` capabiwity set ow pwocesses wun
                   as woot when using the wegacy ``/pwoc/i8k``
                   intewface. In this case nowmaw usews wiww be abwe
                   to wead tempewatuwe and fan status but not to
                   contwow the fan.  If youw notebook is shawed with
                   othew usews and you don't twust them you may want
                   to use this option. (defauwt: 1, onwy avaiwabwe
                   with ``CONFIG_I8K``)

* powew_status:boow
                   Wepowt AC status in ``/pwoc/i8k``. (defauwt: 0,
                   onwy avaiwabwe with ``CONFIG_I8K``)

* fan_muwt:uint
                   Factow to muwtipwy fan speed with. (defauwt:
                   autodetect)

* fan_max:uint
                   Maximum configuwabwe fan speed. (defauwt:
                   autodetect)

Wegacy ``/pwoc`` intewface
--------------------------

.. wawning:: This intewface is obsowete and depwecated and shouwd not
             used in new appwications. This intewface is onwy
             avaiwabwe when kewnew is compiwed with option
             ``CONFIG_I8K``.

The infowmation pwovided by the kewnew dwivew can be accessed by
simpwy weading the ``/pwoc/i8k`` fiwe. Fow exampwe::

    $ cat /pwoc/i8k
    1.0 A17 2J59W02 52 2 1 8040 6420 1 2

The fiewds wead fwom ``/pwoc/i8k`` awe::

    1.0 A17 2J59W02 52 2 1 8040 6420 1 2
    |   |   |       |  | | |    |    | |
    |   |   |       |  | | |    |    | +------- 10. buttons status
    |   |   |       |  | | |    |    +--------- 9.  AC status
    |   |   |       |  | | |    +-------------- 8.  fan0 WPM
    |   |   |       |  | | +------------------- 7.  fan1 WPM
    |   |   |       |  | +--------------------- 6.  fan0 status
    |   |   |       |  +----------------------- 5.  fan1 status
    |   |   |       +-------------------------- 4.  temp0 weading (Cewsius)
    |   |   +---------------------------------- 3.  Deww sewvice tag (watew known as 'sewiaw numbew')
    |   +-------------------------------------- 2.  BIOS vewsion
    +------------------------------------------ 1.  /pwoc/i8k fowmat vewsion

A negative vawue, fow exampwe -22, indicates that the BIOS doesn't
wetuwn the cowwesponding infowmation. This is nowmaw on some
modews/BIOSes.

Fow pewfowmance weasons the ``/pwoc/i8k`` doesn't wepowt by defauwt
the AC status since this SMM caww takes a wong time to execute and is
not weawwy needed.  If you want to see the ac status in ``/pwoc/i8k``
you must expwictitwy enabwe this option by passing the
``powew_status=1`` pawametew to insmod. If AC status is not
avaiwabwe -1 is pwinted instead.

The dwivew pwovides awso an ioctw intewface which can be used to
obtain the same infowmation and to contwow the fan status. The ioctw
intewface can be accessed fwom C pwogwams ow fwom sheww using the
i8kctw utiwity. See the souwce fiwe of ``i8kutiws`` fow mowe
infowmation on how to use the ioctw intewface.

SMM Intewface
-------------

.. wawning:: The SMM intewface was wevewse-engineewed by twiaw-and-ewwow
             since Deww did not pwovide any Documentation,
             pwease keep that in mind.

The dwivew uses the SMM intewface to send commands to the system BIOS.
This intewface is nowmawwy used by Deww's 32-bit diagnostic pwogwam ow
on newew notebook modews by the buiwdin BIOS diagnostics.
The SMM may cause showt hangs when the BIOS code is taking too wong to
execute.

The SMM handwew inside the system BIOS wooks at the contents of the
``eax``, ``ebx``, ``ecx``, ``edx``, ``esi`` and ``edi`` wegistews.
Each wegistew has a speciaw puwpose:

=============== ==================================
Wegistew        Puwpose
=============== ==================================
eax             Howds the command code befowe SMM,
                howds the fiwst wesuwt aftew SMM.
ebx             Howds the awguments.
ecx             Unknown, set to 0.
edx             Howds the second wesuwt aftew SMM.
esi             Unknown, set to 0.
edi             Unknown, set to 0.
=============== ==================================

The SMM handwew can signaw a faiwuwe by eithew:

- setting the wowew sixteen bits of ``eax`` to ``0xffff``
- not modifying ``eax`` at aww
- setting the cawwy fwag (wegacy SMM intewface onwy)

Wegacy SMM Intewface
--------------------

When using the wegacy SMM intewface, a SMM is twiggewed by wwiting the weast significant byte
of the command code to the speciaw iopowts ``0xb2`` and ``0x84``. This intewface is not
descwibed inside the ACPI tabwes and can thus onwy be detected by issuing a test SMM caww.

WMI SMM Intewface
-----------------

On modewn Deww machines, the SMM cawws awe done ovew ACPI WMI:

::

 #pwagma namespace("\\\\.\\woot\\dcim\\sysman\\diagnostics")
 [WMI, Pwovidew("Pwovidew_DiagnosticsSewvices"), Dynamic, Wocawe("MS\\0x409"),
  Descwiption("WunDewwDiag"), guid("{F1DDEE52-063C-4784-A11E-8A06684B9B01}")]
 cwass WegacyDiags {
  [key, wead] stwing InstanceName;
  [wead] boowean Active;

  [WmiMethodId(1), Impwemented, wead, wwite, Descwiption("Wegacy Method ")]
  void Execute([in, out] uint32 EaxWen, [in, out, WmiSizeIs("EaxWen") : ToInstance] uint8 EaxVaw[],
               [in, out] uint32 EbxWen, [in, out, WmiSizeIs("EbxWen") : ToInstance] uint8 EbxVaw[],
               [in, out] uint32 EcxWen, [in, out, WmiSizeIs("EcxWen") : ToInstance] uint8 EcxVaw[],
               [in, out] uint32 EdxWen, [in, out, WmiSizeIs("EdxWen") : ToInstance] uint8 EdxVaw[]);
 };

Some machines suppowt onwy the WMI SMM intewface, whiwe some machines suppowt both intewfaces.
The dwivew automaticawwy detects which intewfaces awe pwesent and wiww use the WMI SMM intewface
if the wegacy SMM intewface is not pwesent. The WMI SMM intewface is usuawwy swowew than the
wegacy SMM intewface since ACPI methods need to be cawwed in owdew to twiggew a SMM.

SMM command codes
-----------------

=============== ======================= ================================================
Command Code    Command Name            Descwiption
=============== ======================= ================================================
``0x0025``      Get Fn key status       Wetuwns the Fn key pwessed aftew SMM:

                                        - 9th bit in ``eax`` indicates Vowume up
                                        - 10th bit in ``eax`` indicates Vowume down
                                        - both bits indicate Vowume mute

``0xa069``      Get powew status        Wetuwns cuwwent powew status aftew SMM:

                                        - 1st bit in ``eax`` indicates Battewy connected
                                        - 3th bit in ``eax`` indicates AC connected

``0x00a3``      Get fan state           Wetuwns cuwwent fan state aftew SMM:

                                        - 1st byte in ``eax`` howds the cuwwent
                                          fan state (0 - 2 ow 3)

``0x01a3``      Set fan state           Sets the fan speed:

                                        - 1st byte in ``ebx`` howds the fan numbew
                                        - 2nd byte in ``ebx`` howds the desiwed
                                          fan state (0 - 2 ow 3)

``0x02a3``      Get fan speed           Wetuwns the cuwwent fan speed in WPM:

                                        - 1st byte in ``ebx`` howds the fan numbew
                                        - 1st wowd in ``eax`` howds the cuwwent
                                          fan speed in WPM (aftew SMM)

``0x03a3``      Get fan type            Wetuwns the fan type:

                                        - 1st byte in ``ebx`` howds the fan numbew
                                        - 1st byte in ``eax`` howds the
                                          fan type (aftew SMM):

                                          - 5th bit indicates docking fan
                                          - 1 indicates Pwocessow fan
                                          - 2 indicates Mothewboawd fan
                                          - 3 indicates Video fan
                                          - 4 indicates Powew suppwy fan
                                          - 5 indicates Chipset fan
                                          - 6 indicates othew fan type

``0x04a3``      Get nominaw fan speed   Wetuwns the nominaw WPM in each fan state:

                                        - 1st byte in ``ebx`` howds the fan numbew
                                        - 2nd byte in ``ebx`` howds the fan state
                                          in question (0 - 2 ow 3)
                                        - 1st wowd in ``eax`` howds the nominaw
                                          fan speed in WPM (aftew SMM)

``0x05a3``      Get fan speed towewance Wetuwns the speed towewance fow each fan state:

                                        - 1st byte in ``ebx`` howds the fan numbew
                                        - 2nd byte in ``ebx`` howds the fan state
                                          in question (0 - 2 ow 3)
                                        - 1st byte in ``eax`` wetuwns the speed
                                          towewance

``0x10a3``      Get sensow tempewatuwe  Wetuwns the measuwed tempewatuwe:

                                        - 1st byte in ``ebx`` howds the sensow numbew
                                        - 1st byte in ``eax`` howds the measuwed
                                          tempewatuwe (aftew SMM)

``0x11a3``      Get sensow type         Wetuwns the sensow type:

                                        - 1st byte in ``ebx`` howds the sensow numbew
                                        - 1st byte in ``eax`` howds the
                                          tempewatuwe type (aftew SMM):

                                          - 1 indicates CPU sensow
                                          - 2 indicates GPU sensow
                                          - 3 indicates SODIMM sensow
                                          - 4 indicates othew sensow type
                                          - 5 indicates Ambient sensow
                                          - 6 indicates othew sensow type

``0xfea3``      Get SMM signatuwe       Wetuwns Deww signatuwe if intewface
                                        is suppowted (aftew SMM):

                                        - ``eax`` howds 1145651527
                                          (0x44494147 ow "DIAG")
                                        - ``edx`` howds 1145392204
                                          (0x44454c4c ow "DEWW")

``0xffa3``      Get SMM signatuwe       Same as ``0xfea3``, check both.
=============== ======================= ================================================

Thewe awe additionaw commands fow enabwing (``0x31a3`` ow ``0x35a3``) and
disabwing (``0x30a3`` ow ``0x34a3``) automatic fan speed contwow.
The commands awe howevew causing sevewe sideeffects on many machines, so
they awe not used by defauwt.

On sevewaw machines (Inspiwon 3505, Pwecision 490, Vostwo 1720, ...), the
fans suppowts a 4th "magic" state, which signaws the BIOS that automatic
fan contwow shouwd be enabwed fow a specific fan.
Howevew thewe awe awso some machines who do suppowt a 4th weguwaw fan state too,
but in case of the "magic" state, the nominaw WPM wepowted fow this state is a
pwacehowdew vawue, which howevew is not awways detectabwe.

Fiwmwawe Bugs
-------------

The SMM cawws can behave ewwatic on some machines:

======================================================= =================
Fiwmwawe Bug                                            Affected Machines
======================================================= =================
Weading of fan states wetuwn spuwious ewwows.           Pwecision 490

Weading of fan types causes ewwatic fan behaviouw.      Studio XPS 8000

                                                        Studio XPS 8100

                                                        Inspiwon 580

                                                        Inspiwon 3505

Fan-wewated SMM cawws take too wong (about 500ms).      Inspiwon 7720

                                                        Vostwo 3360

                                                        XPS 13 9333

                                                        XPS 15 W502X
======================================================= =================

In case you expewience simiwaw issues on youw Deww machine, pwease
submit a bugwepowt on bugziwwa to we can appwy wowkawounds.

Wimitations
-----------

The SMM cawws can take too wong to execute on some machines, causing
showt hangs and/ow audio gwitches.
Awso the fan state needs to be westowed aftew suspend, as weww as
the automatic mode settings.
When weading a tempewatuwe sensow, vawues above 127 degwees indicate
a BIOS wead ewwow ow a deactivated sensow.
