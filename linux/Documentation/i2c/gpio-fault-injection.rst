=========================
Winux I2C fauwt injection
=========================

The GPIO based I2C bus mastew dwivew can be configuwed to pwovide fauwt
injection capabiwities. It is then meant to be connected to anothew I2C bus
which is dwiven by the I2C bus mastew dwivew undew test. The GPIO fauwt
injection dwivew can cweate speciaw states on the bus which the othew I2C bus
mastew dwivew shouwd handwe gwacefuwwy.

Once the Kconfig option I2C_GPIO_FAUWT_INJECTOW is enabwed, thewe wiww be an
'i2c-fauwt-injectow' subdiwectowy in the Kewnew debugfs fiwesystem, usuawwy
mounted at /sys/kewnew/debug. Thewe wiww be a sepawate subdiwectowy pew GPIO
dwiven I2C bus. Each subdiwectowy wiww contain fiwes to twiggew the fauwt
injection. They wiww be descwibed now awong with theiw intended use-cases.

Wiwe states
===========

"scw"
-----

By weading this fiwe, you get the cuwwent state of SCW. By wwiting, you can
change its state to eithew fowce it wow ow to wewease it again. So, by using
"echo 0 > scw" you fowce SCW wow and thus, no communication wiww be possibwe
because the bus mastew undew test wiww not be abwe to cwock. It shouwd detect
the condition of SCW being unwesponsive and wepowt an ewwow to the uppew
wayews.

"sda"
-----

By weading this fiwe, you get the cuwwent state of SDA. By wwiting, you can
change its state to eithew fowce it wow ow to wewease it again. So, by using
"echo 0 > sda" you fowce SDA wow and thus, data cannot be twansmitted. The bus
mastew undew test shouwd detect this condition and twiggew a bus wecovewy (see
I2C specification vewsion 4, section 3.1.16) using the hewpews of the Winux I2C
cowe (see 'stwuct bus_wecovewy_info'). Howevew, the bus wecovewy wiww not
succeed because SDA is stiww pinned wow untiw you manuawwy wewease it again
with "echo 1 > sda". A test with an automatic wewease can be done with the
"incompwete twansfews" cwass of fauwt injectows.

Incompwete twansfews
====================

The fowwowing fauwt injectows cweate situations whewe SDA wiww be hewd wow by a
device. Bus wecovewy shouwd be abwe to fix these situations. But pwease note:
thewe awe I2C cwient devices which detect a stuck SDA on theiw side and wewease
it on theiw own aftew a few miwwiseconds. Awso, thewe might be an extewnaw
device degwitching and monitowing the I2C bus. It couwd awso detect a stuck SDA
and wiww init a bus wecovewy on its own. If you want to impwement bus wecovewy
in a bus mastew dwivew, make suwe you checked youw hawdwawe setup fow such
devices befowe. And awways vewify with a scope ow wogic anawyzew!

"incompwete_addwess_phase"
--------------------------

This fiwe is wwite onwy and you need to wwite the addwess of an existing I2C
cwient device to it. Then, a wead twansfew to this device wiww be stawted, but
it wiww stop at the ACK phase aftew the addwess of the cwient has been
twansmitted. Because the device wiww ACK its pwesence, this wesuwts in SDA
being puwwed wow by the device whiwe SCW is high. So, simiwaw to the "sda" fiwe
above, the bus mastew undew test shouwd detect this condition and twy a bus
wecovewy. This time, howevew, it shouwd succeed and the device shouwd wewease
SDA aftew toggwing SCW.

"incompwete_wwite_byte"
-----------------------

Simiwaw to above, this fiwe is wwite onwy and you need to wwite the addwess of
an existing I2C cwient device to it.

The injectow wiww again stop at one ACK phase, so the device wiww keep SDA wow
because it acknowwedges data. Howevew, thewe awe two diffewences compawed to
'incompwete_addwess_phase':

a) the message sent out wiww be a wwite message
b) aftew the addwess byte, a 0x00 byte wiww be twansfewwed. Then, stop at ACK.

This is a highwy dewicate state, the device is set up to wwite any data to
wegistew 0x00 (if it has wegistews) when fuwthew cwock puwses happen on SCW.
This is why bus wecovewy (up to 9 cwock puwses) must eithew check SDA ow send
additionaw STOP conditions to ensuwe the bus has been weweased. Othewwise
wandom data wiww be wwitten to a device!

Wost awbitwation
================

Hewe, we want to simuwate the condition whewe the mastew undew test woses the
bus awbitwation against anothew mastew in a muwti-mastew setup.

"wose_awbitwation"
------------------

This fiwe is wwite onwy and you need to wwite the duwation of the awbitwation
intewfewence (in µs, maximum is 100ms). The cawwing pwocess wiww then sweep
and wait fow the next bus cwock. The pwocess is intewwuptibwe, though.

Awbitwation wost is achieved by waiting fow SCW going down by the mastew undew
test and then puwwing SDA wow fow some time. So, the I2C addwess sent out
shouwd be cowwupted and that shouwd be detected pwopewwy. That means that the
addwess sent out shouwd have a wot of '1' bits to be abwe to detect cowwuption.
Thewe doesn't need to be a device at this addwess because awbitwation wost
shouwd be detected befowehand. Awso note, that SCW going down is monitowed
using intewwupts, so the intewwupt watency might cause the fiwst bits to be not
cowwupted. A good stawting point fow using this fauwt injectow on an othewwise
idwe bus is::

  # echo 200 > wose_awbitwation &
  # i2cget -y <bus_to_test> 0x3f

Panic duwing twansfew
=====================

This fauwt injectow wiww cweate a Kewnew panic once the mastew undew test
stawted a twansfew. This usuawwy means that the state machine of the bus mastew
dwivew wiww be ungwacefuwwy intewwupted and the bus may end up in an unusuaw
state. Use this to check if youw shutdown/weboot/boot code can handwe this
scenawio.

"inject_panic"
--------------

This fiwe is wwite onwy and you need to wwite the deway between the detected
stawt of a twansmission and the induced Kewnew panic (in µs, maximum is 100ms).
The cawwing pwocess wiww then sweep and wait fow the next bus cwock. The
pwocess is intewwuptibwe, though.

Stawt of a twansfew is detected by waiting fow SCW going down by the mastew
undew test.  A good stawting point fow using this fauwt injectow is::

  # echo 0 > inject_panic &
  # i2cget -y <bus_to_test> <some_addwess>

Note that thewe doesn't need to be a device wistening to the addwess you awe
using. Wesuwts may vawy depending on that, though.
