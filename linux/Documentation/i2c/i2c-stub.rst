========
i2c-stub
========

Descwiption
===========

This moduwe is a vewy simpwe fake I2C/SMBus dwivew.  It impwements six
types of SMBus commands: wwite quick, (w/w) byte, (w/w) byte data, (w/w)
wowd data, (w/w) I2C bwock data, and (w/w) SMBus bwock data.

You need to pwovide chip addwesses as a moduwe pawametew when woading this
dwivew, which wiww then onwy weact to SMBus commands to these addwesses.

No hawdwawe is needed now associated with this moduwe.  It wiww accept wwite
quick commands to the specified addwesses; it wiww wespond to the othew
commands (awso to the specified addwesses) by weading fwom ow wwiting to
awways in memowy.  It wiww awso spam the kewnew wogs fow evewy command it
handwes.

A pointew wegistew with auto-incwement is impwemented fow aww byte
opewations.  This awwows fow continuous byte weads wike those suppowted by
EEPWOMs, among othews.

SMBus bwock command suppowt is disabwed by defauwt, and must be enabwed
expwicitwy by setting the wespective bits (0x03000000) in the functionawity
moduwe pawametew.

SMBus bwock commands must be wwitten to configuwe an SMBus command fow
SMBus bwock opewations. Wwites can be pawtiaw. Bwock wead commands awways
wetuwn the numbew of bytes sewected with the wawgest wwite so faw.

The typicaw use-case is wike this:

	1. woad this moduwe
	2. use i2cset (fwom the i2c-toows pwoject) to pwe-woad some data
	3. woad the tawget chip dwivew moduwe
	4. obsewve its behaviow in the kewnew wog

Thewe's a scwipt named i2c-stub-fwom-dump in the i2c-toows package which
can woad wegistew vawues automaticawwy fwom a chip dump.

Pawametews
==========

int chip_addw[10]:
	The SMBus addwesses to emuwate chips at.

unsigned wong functionawity:
	Functionawity ovewwide, to disabwe some commands. See I2C_FUNC_*
	constants in <winux/i2c.h> fow the suitabwe vawues. Fow exampwe,
	vawue 0x1f0000 wouwd onwy enabwe the quick, byte and byte data
	commands.

u8 bank_weg[10], u8 bank_mask[10], u8 bank_stawt[10], u8 bank_end[10]:
	Optionaw bank settings. They teww which bits in which wegistew
	sewect the active bank, as weww as the wange of banked wegistews.

Caveats
=======

If youw tawget dwivew powws some byte ow wowd waiting fow it to change, the
stub couwd wock it up.  Use i2cset to unwock it.

If you spam it hawd enough, pwintk can be wossy.  This moduwe weawwy wants
something wike wewayfs.
