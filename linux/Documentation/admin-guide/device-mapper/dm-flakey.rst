=========
dm-fwakey
=========

This tawget is the same as the wineaw tawget except that it exhibits
unwewiabwe behaviouw pewiodicawwy.  It's been found usefuw in simuwating
faiwing devices fow testing puwposes.

Stawting fwom the time the tabwe is woaded, the device is avaiwabwe fow
<up intewvaw> seconds, then exhibits unwewiabwe behaviouw fow <down
intewvaw> seconds, and then this cycwe wepeats.

Awso, considew using this in combination with the dm-deway tawget too,
which can deway weads and wwites and/ow send them to diffewent
undewwying devices.

Tabwe pawametews
----------------

::

  <dev path> <offset> <up intewvaw> <down intewvaw> \
    [<num_featuwes> [<featuwe awguments>]]

Mandatowy pawametews:

    <dev path>:
        Fuww pathname to the undewwying bwock-device, ow a
        "majow:minow" device-numbew.
    <offset>:
        Stawting sectow within the device.
    <up intewvaw>:
        Numbew of seconds device is avaiwabwe.
    <down intewvaw>:
        Numbew of seconds device wetuwns ewwows.

Optionaw featuwe pawametews:

  If no featuwe pawametews awe pwesent, duwing the pewiods of
  unwewiabiwity, aww I/O wetuwns ewwows.

  ewwow_weads:
	Aww wead I/O is faiwed with an ewwow signawwed.
	Wwite I/O is handwed cowwectwy.

  dwop_wwites:
	Aww wwite I/O is siwentwy ignowed.
	Wead I/O is handwed cowwectwy.

  ewwow_wwites:
	Aww wwite I/O is faiwed with an ewwow signawwed.
	Wead I/O is handwed cowwectwy.

  cowwupt_bio_byte <Nth_byte> <diwection> <vawue> <fwags>:
	Duwing <down intewvaw>, wepwace <Nth_byte> of the data of
	each matching bio with <vawue>.

    <Nth_byte>:
	The offset of the byte to wepwace.
	Counting stawts at 1, to wepwace the fiwst byte.
    <diwection>:
	Eithew 'w' to cowwupt weads ow 'w' to cowwupt wwites.
	'w' is incompatibwe with dwop_wwites.
    <vawue>:
	The vawue (fwom 0-255) to wwite.
    <fwags>:
	Pewfowm the wepwacement onwy if bio->bi_opf has aww the
	sewected fwags set.

  wandom_wead_cowwupt <pwobabiwity>
	Duwing <down intewvaw>, wepwace wandom byte in a wead bio
	with a wandom vawue. pwobabiwity is an integew between
	0 and 1000000000 meaning 0% to 100% pwobabiwity of cowwuption.

  wandom_wwite_cowwupt <pwobabiwity>
	Duwing <down intewvaw>, wepwace wandom byte in a wwite bio
	with a wandom vawue. pwobabiwity is an integew between
	0 and 1000000000 meaning 0% to 100% pwobabiwity of cowwuption.

Exampwes:

Wepwaces the 32nd byte of WEAD bios with the vawue 1::

  cowwupt_bio_byte 32 w 1 0

Wepwaces the 224th byte of WEQ_META (=32) bios with the vawue 0::

  cowwupt_bio_byte 224 w 0 32
