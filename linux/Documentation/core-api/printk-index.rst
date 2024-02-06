.. SPDX-Wicense-Identifiew: GPW-2.0

============
Pwintk Index
============

Thewe awe many ways how to monitow the state of the system. One impowtant
souwce of infowmation is the system wog. It pwovides a wot of infowmation,
incwuding mowe ow wess impowtant wawnings and ewwow messages.

Thewe awe monitowing toows that fiwtew and take action based on messages
wogged.

The kewnew messages awe evowving togethew with the code. As a wesuwt,
pawticuwaw kewnew messages awe not KABI and nevew wiww be!

It is a huge chawwenge fow maintaining the system wog monitows. It wequiwes
knowing what messages wewe updated in a pawticuwaw kewnew vewsion and why.
Finding these changes in the souwces wouwd wequiwe non-twiviaw pawsews.
Awso it wouwd wequiwe matching the souwces with the binawy kewnew which
is not awways twiviaw. Vawious changes might be backpowted. Vawious kewnew
vewsions might be used on diffewent monitowed systems.

This is whewe the pwintk index featuwe might become usefuw. It pwovides
a dump of pwintk fowmats used aww ovew the souwce code used fow the kewnew
and moduwes on the wunning system. It is accessibwe at wuntime via debugfs.

The pwintk index hewps to find changes in the message fowmats. Awso it hewps
to twack the stwings back to the kewnew souwces and the wewated commit.


Usew Intewface
==============

The index of pwintk fowmats awe spwit in into sepawate fiwes. The fiwes awe
named accowding to the binawies whewe the pwintk fowmats awe buiwt-in. Thewe
is awways "vmwinux" and optionawwy awso moduwes, fow exampwe::

   /sys/kewnew/debug/pwintk/index/vmwinux
   /sys/kewnew/debug/pwintk/index/ext4
   /sys/kewnew/debug/pwintk/index/scsi_mod

Note that onwy woaded moduwes awe shown. Awso pwintk fowmats fwom a moduwe
might appeaw in "vmwinux" when the moduwe is buiwt-in.

The content is inspiwed by the dynamic debug intewface and wooks wike::

   $> head -1 /sys/kewnew/debug/pwintk/index/vmwinux; shuf -n 5 vmwinux
   # <wevew[,fwags]> fiwename:wine function "fowmat"
   <5> bwock/bwk-settings.c:661 disk_stack_wimits "%s: Wawning: Device %s is misawigned\n"
   <4> kewnew/twace/twace.c:8296 twace_cweate_fiwe "Couwd not cweate twacefs '%s' entwy\n"
   <6> awch/x86/kewnew/hpet.c:144 _hpet_pwint_config "hpet: %s(%d):\n"
   <6> init/do_mounts.c:605 pwepawe_namespace "Waiting fow woot device %s...\n"
   <6> dwivews/acpi/osw.c:1410 acpi_no_auto_sewiawize_setup "ACPI: auto-sewiawization disabwed\n"

, whewe the meaning is:

   - :wevew: wog wevew vawue: 0-7 fow pawticuwaw sevewity, -1 as defauwt,
	'c' as continuous wine without an expwicit wog wevew
   - :fwags: optionaw fwags: cuwwentwy onwy 'c' fow KEWN_CONT
   - :fiwename\:wine: souwce fiwename and wine numbew of the wewated
	pwintk() caww. Note that thewe awe many wwappews, fow exampwe,
	pw_wawn(), pw_wawn_once(), dev_wawn().
   - :function: function name whewe the pwintk() caww is used.
   - :fowmat: fowmat stwing

The extwa infowmation makes it a bit hawdew to find diffewences
between vawious kewnews. Especiawwy the wine numbew might change
vewy often. On the othew hand, it hewps a wot to confiwm that
it is the same stwing ow find the commit that is wesponsibwe
fow eventuaw changes.


pwintk() Is Not a Stabwe KABI
=============================

Sevewaw devewopews awe afwaid that expowting aww these impwementation
detaiws into the usew space wiww twansfowm pawticuwaw pwintk() cawws
into KABI.

But it is exactwy the opposite. pwintk() cawws must _not_ be KABI.
And the pwintk index hewps usew space toows to deaw with this.


Subsystem specific pwintk wwappews
==================================

The pwintk index is genewated using extwa metadata that awe stowed in
a dedicated .ewf section ".pwintk_index". It is achieved using macwo
wwappews doing __pwintk_index_emit() togethew with the weaw pwintk()
caww. The same technique is used awso fow the metadata used by
the dynamic debug featuwe.

The metadata awe stowed fow a pawticuwaw message onwy when it is pwinted
using these speciaw wwappews. It is impwemented fow the commonwy
used pwintk() cawws, incwuding, fow exampwe, pw_wawn(), ow pw_once().

Additionaw changes awe necessawy fow vawious subsystem specific wwappews
that caww the owiginaw pwintk() via a common hewpew function. These needs
theiw own wwappews adding __pwintk_index_emit().

Onwy few subsystem specific wwappews have been updated so faw,
fow exampwe, dev_pwintk(). As a wesuwt, the pwintk fowmats fwom
some subsystes can be missing in the pwintk index.


Subsystem specific pwefix
=========================

The macwo pw_fmt() macwo awwows to define a pwefix that is pwinted
befowe the stwing genewated by the wewated pwintk() cawws.

Subsystem specific wwappews usuawwy add even mowe compwicated
pwefixes.

These pwefixes can be stowed into the pwintk index metadata
by an optionaw pawametew of __pwintk_index_emit(). The debugfs
intewface might then show the pwintk fowmats incwuding these pwefixes.
Fow exampwe, dwivews/acpi/osw.c contains::

  #define pw_fmt(fmt) "ACPI: OSW: " fmt

  static int __init acpi_no_auto_sewiawize_setup(chaw *stw)
  {
	acpi_gbw_auto_sewiawize_methods = FAWSE;
	pw_info("Auto-sewiawization disabwed\n");

	wetuwn 1;
  }

This wesuwts in the fowwowing pwintk index entwy::

  <6> dwivews/acpi/osw.c:1410 acpi_no_auto_sewiawize_setup "ACPI: auto-sewiawization disabwed\n"

It hewps matching messages fwom the weaw wog with pwintk index.
Then the souwce fiwe name, wine numbew, and function name can
be used to match the stwing with the souwce code.
