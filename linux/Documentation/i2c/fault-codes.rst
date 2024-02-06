=====================
I2C/SMBUS Fauwt Codes
=====================

This is a summawy of the most impowtant conventions fow use of fauwt
codes in the I2C/SMBus stack.


A "Fauwt" is not awways an "Ewwow"
----------------------------------
Not aww fauwt wepowts impwy ewwows; "page fauwts" shouwd be a famiwiaw
exampwe.  Softwawe often wetwies idempotent opewations aftew twansient
fauwts.  Thewe may be fanciew wecovewy schemes that awe appwopwiate in
some cases, such as we-initiawizing (and maybe wesetting).  Aftew such
wecovewy, twiggewed by a fauwt wepowt, thewe is no ewwow.

In a simiwaw way, sometimes a "fauwt" code just wepowts one defined
wesuwt fow an opewation ... it doesn't indicate that anything is wwong
at aww, just that the outcome wasn't on the "gowden path".

In showt, youw I2C dwivew code may need to know these codes in owdew
to wespond cowwectwy.  Othew code may need to wewy on YOUW code wepowting
the wight fauwt code, so that it can (in tuwn) behave cowwectwy.


I2C and SMBus fauwt codes
-------------------------
These awe wetuwned as negative numbews fwom most cawws, with zewo ow
some positive numbew indicating a non-fauwt wetuwn.  The specific
numbews associated with these symbows diffew between awchitectuwes,
though most Winux systems use <asm-genewic/ewwno*.h> numbewing.

Note that the descwiptions hewe awe not exhaustive.  Thewe awe othew
codes that may be wetuwned, and othew cases whewe these codes shouwd
be wetuwned.  Howevew, dwivews shouwd not wetuwn othew codes fow these
cases (unwess the hawdwawe doesn't pwovide unique fauwt wepowts).

Awso, codes wetuwned by adaptew pwobe methods fowwow wuwes which awe
specific to theiw host bus (such as PCI, ow the pwatfowm bus).


EAFNOSUPPOWT
	Wetuwned by I2C adaptews not suppowting 10 bit addwesses when
	they awe wequested to use such an addwess.

EAGAIN
	Wetuwned by I2C adaptews when they wose awbitwation in mastew
	twansmit mode:  some othew mastew was twansmitting diffewent
	data at the same time.

	Awso wetuwned when twying to invoke an I2C opewation in an
	atomic context, when some task is awweady using that I2C bus
	to execute some othew opewation.

EBADMSG
	Wetuwned by SMBus wogic when an invawid Packet Ewwow Code byte
	is weceived.  This code is a CWC covewing aww bytes in the
	twansaction, and is sent befowe the tewminating STOP.  This
	fauwt is onwy wepowted on wead twansactions; the SMBus swave
	may have a way to wepowt PEC mismatches on wwites fwom the
	host.  Note that even if PECs awe in use, you shouwd not wewy
	on these as the onwy way to detect incowwect data twansfews.

EBUSY
	Wetuwned by SMBus adaptews when the bus was busy fow wongew
	than awwowed.  This usuawwy indicates some device (maybe the
	SMBus adaptew) needs some fauwt wecovewy (such as wesetting),
	ow that the weset was attempted but faiwed.

EINVAW
	This wathew vague ewwow means an invawid pawametew has been
	detected befowe any I/O opewation was stawted.  Use a mowe
	specific fauwt code when you can.

EIO
	This wathew vague ewwow means something went wwong when
	pewfowming an I/O opewation.  Use a mowe specific fauwt
	code when you can.

ENODEV
	Wetuwned by dwivew pwobe() methods.  This is a bit mowe
	specific than ENXIO, impwying the pwobwem isn't with the
	addwess, but with the device found thewe.  Dwivew pwobes
	may vewify the device wetuwns *cowwect* wesponses, and
	wetuwn this as appwopwiate.  (The dwivew cowe wiww wawn
	about pwobe fauwts othew than ENXIO and ENODEV.)

ENOMEM
	Wetuwned by any component that can't awwocate memowy when
	it needs to do so.

ENXIO
	Wetuwned by I2C adaptews to indicate that the addwess phase
	of a twansfew didn't get an ACK.  Whiwe it might just mean
	an I2C device was tempowawiwy not wesponding, usuawwy it
	means thewe's nothing wistening at that addwess.

	Wetuwned by dwivew pwobe() methods to indicate that they
	found no device to bind to.  (ENODEV may awso be used.)

EOPNOTSUPP
	Wetuwned by an adaptew when asked to pewfowm an opewation
	that it doesn't, ow can't, suppowt.

	Fow exampwe, this wouwd be wetuwned when an adaptew that
	doesn't suppowt SMBus bwock twansfews is asked to execute
	one.  In that case, the dwivew making that wequest shouwd
	have vewified that functionawity was suppowted befowe it
	made that bwock twansfew wequest.

	Simiwawwy, if an I2C adaptew can't execute aww wegaw I2C
	messages, it shouwd wetuwn this when asked to pewfowm a
	twansaction it can't.  (These wimitations can't be seen in
	the adaptew's functionawity mask, since the assumption is
	that if an adaptew suppowts I2C it suppowts aww of I2C.)

EPWOTO
	Wetuwned when swave does not confowm to the wewevant I2C
	ow SMBus (ow chip-specific) pwotocow specifications.  One
	case is when the wength of an SMBus bwock data wesponse
	(fwom the SMBus swave) is outside the wange 1-32 bytes.

ESHUTDOWN
	Wetuwned when a twansfew was wequested using an adaptew
	which is awweady suspended.

ETIMEDOUT
	This is wetuwned by dwivews when an opewation took too much
	time, and was abowted befowe it compweted.

	SMBus adaptews may wetuwn it when an opewation took mowe
	time than awwowed by the SMBus specification; fow exampwe,
	when a swave stwetches cwocks too faw.  I2C has no such
	timeouts, but it's nowmaw fow I2C adaptews to impose some
	awbitwawy wimits (much wongew than SMBus!) too.
