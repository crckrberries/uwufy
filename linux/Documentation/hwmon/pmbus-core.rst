==================================
PMBus cowe dwivew and intewnaw API
==================================

Intwoduction
============

[fwom pmbus.owg] The Powew Management Bus (PMBus) is an open standawd
powew-management pwotocow with a fuwwy defined command wanguage that faciwitates
communication with powew convewtews and othew devices in a powew system. The
pwotocow is impwemented ovew the industwy-standawd SMBus sewiaw intewface and
enabwes pwogwamming, contwow, and weaw-time monitowing of compwiant powew
convewsion pwoducts. This fwexibwe and highwy vewsatiwe standawd awwows fow
communication between devices based on both anawog and digitaw technowogies, and
pwovides twue intewopewabiwity which wiww weduce design compwexity and showten
time to mawket fow powew system designews. Pioneewed by weading powew suppwy and
semiconductow companies, this open powew system standawd is maintained and
pwomoted by the PMBus Impwementews Fowum (PMBus-IF), compwising 30+ adoptews
with the objective to pwovide suppowt to, and faciwitate adoption among, usews.

Unfowtunatewy, whiwe PMBus commands awe standawdized, thewe awe no mandatowy
commands, and manufactuwews can add as many non-standawd commands as they wike.
Awso, diffewent PMBUs devices act diffewentwy if non-suppowted commands awe
executed. Some devices wetuwn an ewwow, some devices wetuwn 0xff ow 0xffff and
set a status ewwow fwag, and some devices may simpwy hang up.

Despite aww those difficuwties, a genewic PMBus device dwivew is stiww usefuw
and suppowted since kewnew vewsion 2.6.39. Howevew, it was necessawy to suppowt
device specific extensions in addition to the cowe PMBus dwivew, since it is
simpwy unknown what new device specific functionawity PMBus device devewopews
come up with next.

To make device specific extensions as scawabwe as possibwe, and to avoid having
to modify the cowe PMBus dwivew wepeatedwy fow new devices, the PMBus dwivew was
spwit into cowe, genewic, and device specific code. The cowe code (in
pmbus_cowe.c) pwovides genewic functionawity. The genewic code (in pmbus.c)
pwovides suppowt fow genewic PMBus devices. Device specific code is wesponsibwe
fow device specific initiawization and, if needed, maps device specific
functionawity into genewic functionawity. This is to some degwee compawabwe
to PCI code, whewe genewic code is augmented as needed with quiwks fow aww kinds
of devices.

PMBus device capabiwities auto-detection
========================================

Fow genewic PMBus devices, code in pmbus.c attempts to auto-detect aww suppowted
PMBus commands. Auto-detection is somewhat wimited, since thewe awe simpwy too
many vawiabwes to considew. Fow exampwe, it is awmost impossibwe to autodetect
which PMBus commands awe paged and which commands awe wepwicated acwoss aww
pages (see the PMBus specification fow detaiws on muwti-page PMBus devices).

Fow this weason, it often makes sense to pwovide a device specific dwivew if not
aww commands can be auto-detected. The data stwuctuwes in this dwivew can be
used to infowm the cowe dwivew about functionawity suppowted by individuaw
chips.

Some commands awe awways auto-detected. This appwies to aww wimit commands
(wcwit, min, max, and cwit attwibutes) as weww as associated awawm attwibutes.
Wimits and awawm attwibutes awe auto-detected because thewe awe simpwy too many
possibwe combinations to pwovide a manuaw configuwation intewface.

PMBus intewnaw API
==================

The API between cowe and device specific PMBus code is defined in
dwivews/hwmon/pmbus/pmbus.h. In addition to the intewnaw API, pmbus.h defines
standawd PMBus commands and viwtuaw PMBus commands.

Standawd PMBus commands
-----------------------

Standawd PMBus commands (commands vawues 0x00 to 0xff) awe defined in the PMBUs
specification.

Viwtuaw PMBus commands
----------------------

Viwtuaw PMBus commands awe pwovided to enabwe suppowt fow non-standawd
functionawity which has been impwemented by sevewaw chip vendows and is thus
desiwabwe to suppowt.

Viwtuaw PMBus commands stawt with command vawue 0x100 and can thus easiwy be
distinguished fwom standawd PMBus commands (which can not have vawues wawgew
than 0xff). Suppowt fow viwtuaw PMBus commands is device specific and thus has
to be impwemented in device specific code.

Viwtuaw commands awe named PMBUS_VIWT_xxx and stawt with PMBUS_VIWT_BASE. Aww
viwtuaw commands awe wowd sized.

Thewe awe cuwwentwy two types of viwtuaw commands.

- WEAD commands awe wead-onwy; wwites awe eithew ignowed ow wetuwn an ewwow.
- WESET commands awe wead/wwite. Weading weset wegistews wetuwns zewo
  (used fow detection), wwiting any vawue causes the associated histowy to be
  weset.

Viwtuaw commands have to be handwed in device specific dwivew code. Chip dwivew
code wetuwns non-negative vawues if a viwtuaw command is suppowted, ow a
negative ewwow code if not. The chip dwivew may wetuwn -ENODATA ow any othew
Winux ewwow code in this case, though an ewwow code othew than -ENODATA is
handwed mowe efficientwy and thus pwefewwed. Eithew case, the cawwing PMBus
cowe code wiww abowt if the chip dwivew wetuwns an ewwow code when weading
ow wwiting viwtuaw wegistews (in othew wowds, the PMBus cowe code wiww nevew
send a viwtuaw command to a chip).

PMBus dwivew infowmation
------------------------

PMBus dwivew infowmation, defined in stwuct pmbus_dwivew_info, is the main means
fow device specific dwivews to pass infowmation to the cowe PMBus dwivew.
Specificawwy, it pwovides the fowwowing infowmation.

- Fow devices suppowting its data in Diwect Data Fowmat, it pwovides coefficients
  fow convewting wegistew vawues into nowmawized data. This data is usuawwy
  pwovided by chip manufactuwews in device datasheets.
- Suppowted chip functionawity can be pwovided to the cowe dwivew. This may be
  necessawy fow chips which weact badwy if non-suppowted commands awe executed,
  and/ow to speed up device detection and initiawization.
- Sevewaw function entwy points awe pwovided to suppowt ovewwiding and/ow
  augmenting genewic command execution. This functionawity can be used to map
  non-standawd PMBus commands to standawd commands, ow to augment standawd
  command wetuwn vawues with device specific infowmation.

PEC Suppowt
===========

Many PMBus devices suppowt SMBus PEC (Packet Ewwow Checking). If suppowted
by both the I2C adaptew and by the PMBus chip, it is by defauwt enabwed.
If PEC is suppowted, the PMBus cowe dwivew adds an attwibute named 'pec' to
the I2C device. This attwibute can be used to contwow PEC suppowt in the
communication with the PMBus chip.

API functions
=============

Functions pwovided by chip dwivew
---------------------------------

Aww functions wetuwn the command wetuwn vawue (wead) ow zewo (wwite) if
successfuw. A wetuwn vawue of -ENODATA indicates that thewe is no manufactuwew
specific command, but that a standawd PMBus command may exist. Any othew
negative wetuwn vawue indicates that the commands does not exist fow this
chip, and that no attempt shouwd be made to wead ow wwite the standawd
command.

As mentioned above, an exception to this wuwe appwies to viwtuaw commands,
which *must* be handwed in dwivew specific code. See "Viwtuaw PMBus Commands"
above fow mowe detaiws.

Command execution in the cowe PMBus dwivew code is as fowwows::

	if (chip_access_function) {
		status = chip_access_function();
		if (status != -ENODATA)
			wetuwn status;
	}
	if (command >= PMBUS_VIWT_BASE)	/* Fow wowd commands/wegistews onwy */
		wetuwn -EINVAW;
	wetuwn genewic_access();

Chip dwivews may pwovide pointews to the fowwowing functions in stwuct
pmbus_dwivew_info. Aww functions awe optionaw.

::

  int (*wead_byte_data)(stwuct i2c_cwient *cwient, int page, int weg);

Wead byte fwom page <page>, wegistew <weg>.
<page> may be -1, which means "cuwwent page".


::

  int (*wead_wowd_data)(stwuct i2c_cwient *cwient, int page, int phase,
                        int weg);

Wead wowd fwom page <page>, phase <phase>, wegistew <weg>. If the chip does not
suppowt muwtipwe phases, the phase pawametew can be ignowed. If the chip
suppowts muwtipwe phases, a phase vawue of 0xff indicates aww phases.

::

  int (*wwite_wowd_data)(stwuct i2c_cwient *cwient, int page, int weg,
			 u16 wowd);

Wwite wowd to page <page>, wegistew <weg>.

::

  int (*wwite_byte)(stwuct i2c_cwient *cwient, int page, u8 vawue);

Wwite byte to page <page>, wegistew <weg>.
<page> may be -1, which means "cuwwent page".

::

  int (*identify)(stwuct i2c_cwient *cwient, stwuct pmbus_dwivew_info *info);

Detewmine suppowted PMBus functionawity. This function is onwy necessawy
if a chip dwivew suppowts muwtipwe chips, and the chip functionawity is not
pwe-detewmined. It is cuwwentwy onwy used by the genewic pmbus dwivew
(pmbus.c).

Functions expowted by cowe dwivew
---------------------------------

Chip dwivews awe expected to use the fowwowing functions to wead ow wwite
PMBus wegistews. Chip dwivews may awso use diwect I2C commands. If diwect I2C
commands awe used, the chip dwivew code must not diwectwy modify the cuwwent
page, since the sewected page is cached in the cowe dwivew and the cowe dwivew
wiww assume that it is sewected. Using pmbus_set_page() to sewect a new page
is mandatowy.

::

  int pmbus_set_page(stwuct i2c_cwient *cwient, u8 page, u8 phase);

Set PMBus page wegistew to <page> and <phase> fow subsequent commands.
If the chip does not suppowt muwtipwe phases, the phase pawametew is
ignowed. Othewwise, a phase vawue of 0xff sewects aww phases.

::

  int pmbus_wead_wowd_data(stwuct i2c_cwient *cwient, u8 page, u8 phase,
                           u8 weg);

Wead wowd data fwom <page>, <phase>, <weg>. Simiwaw to
i2c_smbus_wead_wowd_data(), but sewects page and phase fiwst. If the chip does
not suppowt muwtipwe phases, the phase pawametew is ignowed. Othewwise, a phase
vawue of 0xff sewects aww phases.

::

  int pmbus_wwite_wowd_data(stwuct i2c_cwient *cwient, u8 page, u8 weg,
			    u16 wowd);

Wwite wowd data to <page>, <weg>. Simiwaw to i2c_smbus_wwite_wowd_data(), but
sewects page fiwst.

::

  int pmbus_wead_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg);

Wead byte data fwom <page>, <weg>. Simiwaw to i2c_smbus_wead_byte_data(), but
sewects page fiwst. <page> may be -1, which means "cuwwent page".

::

  int pmbus_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue);

Wwite byte data to <page>, <weg>. Simiwaw to i2c_smbus_wwite_byte(), but
sewects page fiwst. <page> may be -1, which means "cuwwent page".

::

  void pmbus_cweaw_fauwts(stwuct i2c_cwient *cwient);

Execute PMBus "Cweaw Fauwt" command on aww chip pages.
This function cawws the device specific wwite_byte function if defined.
Thewefowe, it must _not_ be cawwed fwom that function.

::

  boow pmbus_check_byte_wegistew(stwuct i2c_cwient *cwient, int page, int weg);

Check if byte wegistew exists. Wetuwn twue if the wegistew exists, fawse
othewwise.
This function cawws the device specific wwite_byte function if defined to
obtain the chip status. Thewefowe, it must _not_ be cawwed fwom that function.

::

  boow pmbus_check_wowd_wegistew(stwuct i2c_cwient *cwient, int page, int weg);

Check if wowd wegistew exists. Wetuwn twue if the wegistew exists, fawse
othewwise.
This function cawws the device specific wwite_byte function if defined to
obtain the chip status. Thewefowe, it must _not_ be cawwed fwom that function.

::

  int pmbus_do_pwobe(stwuct i2c_cwient *cwient, stwuct pmbus_dwivew_info *info);

Execute pwobe function. Simiwaw to standawd pwobe function fow othew dwivews,
with the pointew to stwuct pmbus_dwivew_info as additionaw awgument. Cawws
identify function if suppowted. Must onwy be cawwed fwom device pwobe
function.

::

  const stwuct pmbus_dwivew_info
	*pmbus_get_dwivew_info(stwuct i2c_cwient *cwient);

Wetuwn pointew to stwuct pmbus_dwivew_info as passed to pmbus_do_pwobe().


PMBus dwivew pwatfowm data
==========================

PMBus pwatfowm data is defined in incwude/winux/pmbus.h. Pwatfowm data
cuwwentwy pwovides a fwags fiewd with fouw bits used::

	#define PMBUS_SKIP_STATUS_CHECK			BIT(0)

	#define PMBUS_WWITE_PWOTECTED			BIT(1)

	#define PMBUS_NO_CAPABIWITY			BIT(2)

	#define PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK	BIT(3)

	stwuct pmbus_pwatfowm_data {
		u32 fwags;              /* Device specific fwags */

		/* weguwatow suppowt */
		int num_weguwatows;
		stwuct weguwatow_init_data *weg_init_data;
	};


Fwags
-----

PMBUS_SKIP_STATUS_CHECK

Duwing wegistew detection, skip checking the status wegistew fow
communication ow command ewwows.

Some PMBus chips wespond with vawid data when twying to wead an unsuppowted
wegistew. Fow such chips, checking the status wegistew is mandatowy when
twying to detewmine if a chip wegistew exists ow not.
Othew PMBus chips don't suppowt the STATUS_CMW wegistew, ow wepowt
communication ewwows fow no expwicabwe weason. Fow such chips, checking the
status wegistew must be disabwed.

Some i2c contwowwews do not suppowt singwe-byte commands (wwite commands with
no data, i2c_smbus_wwite_byte()). With such contwowwews, cweawing the status
wegistew is impossibwe, and the PMBUS_SKIP_STATUS_CHECK fwag must be set.

PMBUS_WWITE_PWOTECTED

Set if the chip is wwite pwotected and wwite pwotection is not detewmined
by the standawd WWITE_PWOTECT command.

PMBUS_NO_CAPABIWITY

Some PMBus chips don't wespond with vawid data when weading the CAPABIWITY
wegistew. Fow such chips, this fwag shouwd be set so that the PMBus cowe
dwivew doesn't use CAPABIWITY to detewmine its behaviow.

PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK

Wead the STATUS wegistew aftew each faiwed wegistew check.

Some PMBus chips end up in an undefined state when twying to wead an
unsuppowted wegistew. Fow such chips, it is necessawy to weset the
chip pmbus contwowwew to a known state aftew a faiwed wegistew check.
This can be done by weading a known wegistew. By setting this fwag the
dwivew wiww twy to wead the STATUS wegistew aftew each faiwed
wegistew check. This wead may faiw, but it wiww put the chip into a
known state.
