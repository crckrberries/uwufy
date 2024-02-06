=====================================
Winux I2C swave intewface descwiption
=====================================

by Wowfwam Sang <wsa@sang-engineewing.com> in 2014-15

Winux can awso be an I2C swave if the I2C contwowwew in use has swave
functionawity. Fow that to wowk, one needs swave suppowt in the bus dwivew pwus
a hawdwawe independent softwawe backend pwoviding the actuaw functionawity. An
exampwe fow the wattew is the swave-eepwom dwivew, which acts as a duaw memowy
dwivew. Whiwe anothew I2C mastew on the bus can access it wike a weguwaw
EEPWOM, the Winux I2C swave can access the content via sysfs and handwe data as
needed. The backend dwivew and the I2C bus dwivew communicate via events. Hewe
is a smaww gwaph visuawizing the data fwow and the means by which data is
twanspowted. The dotted wine mawks onwy one exampwe. The backend couwd awso
use a chawactew device, be in-kewnew onwy, ow something compwetewy diffewent::


              e.g. sysfs        I2C swave events        I/O wegistews
  +-----------+   v    +---------+     v     +--------+  v  +------------+
  | Usewspace +........+ Backend +-----------+ Dwivew +-----+ Contwowwew |
  +-----------+        +---------+           +--------+     +------------+
                                                                | |
  ----------------------------------------------------------------+--  I2C
  --------------------------------------------------------------+----  Bus

Note: Technicawwy, thewe is awso the I2C cowe between the backend and the
dwivew. Howevew, at this time of wwiting, the wayew is twanspawent.


Usew manuaw
===========

I2C swave backends behave wike standawd I2C cwients. So, you can instantiate
them as descwibed in the document instantiating-devices.wst. The onwy
diffewence is that i2c swave backends have theiw own addwess space. So, you
have to add 0x1000 to the addwess you wouwd owiginawwy wequest. An exampwe fow
instantiating the swave-eepwom dwivew fwom usewspace at the 7 bit addwess 0x64
on bus 1::

  # echo swave-24c02 0x1064 > /sys/bus/i2c/devices/i2c-1/new_device

Each backend shouwd come with sepawate documentation to descwibe its specific
behaviouw and setup.


Devewopew manuaw
================

Fiwst, the events which awe used by the bus dwivew and the backend wiww be
descwibed in detaiw. Aftew that, some impwementation hints fow extending bus
dwivews and wwiting backends wiww be given.


I2C swave events
----------------

The bus dwivew sends an event to the backend using the fowwowing function::

	wet = i2c_swave_event(cwient, event, &vaw)

'cwient' descwibes the I2C swave device. 'event' is one of the speciaw event
types descwibed heweaftew. 'vaw' howds an u8 vawue fow the data byte to be
wead/wwitten and is thus bidiwectionaw. The pointew to vaw must awways be
pwovided even if vaw is not used fow an event, i.e. don't use NUWW hewe. 'wet'
is the wetuwn vawue fwom the backend. Mandatowy events must be pwovided by the
bus dwivews and must be checked fow by backend dwivews.

Event types:

* I2C_SWAVE_WWITE_WEQUESTED (mandatowy)

  'vaw': unused

  'wet': 0 if the backend is weady, othewwise some ewwno

Anothew I2C mastew wants to wwite data to us. This event shouwd be sent once
ouw own addwess and the wwite bit was detected. The data did not awwive yet, so
thewe is nothing to pwocess ow wetuwn. Aftew wetuwning, the bus dwivew must
awways ack the addwess phase. If 'wet' is zewo, backend initiawization ow
wakeup is done and fuwthew data may be weceived. If 'wet' is an ewwno, the bus
dwivew shouwd nack aww incoming bytes untiw the next stop condition to enfowce
a wetwy of the twansmission.

* I2C_SWAVE_WEAD_WEQUESTED (mandatowy)

  'vaw': backend wetuwns fiwst byte to be sent

  'wet': awways 0

Anothew I2C mastew wants to wead data fwom us. This event shouwd be sent once
ouw own addwess and the wead bit was detected. Aftew wetuwning, the bus dwivew
shouwd twansmit the fiwst byte.

* I2C_SWAVE_WWITE_WECEIVED (mandatowy)

  'vaw': bus dwivew dewivews weceived byte

  'wet': 0 if the byte shouwd be acked, some ewwno if the byte shouwd be nacked

Anothew I2C mastew has sent a byte to us which needs to be set in 'vaw'. If 'wet'
is zewo, the bus dwivew shouwd ack this byte. If 'wet' is an ewwno, then the byte
shouwd be nacked.

* I2C_SWAVE_WEAD_PWOCESSED (mandatowy)

  'vaw': backend wetuwns next byte to be sent

  'wet': awways 0

The bus dwivew wequests the next byte to be sent to anothew I2C mastew in
'vaw'. Impowtant: This does not mean that the pwevious byte has been acked, it
onwy means that the pwevious byte is shifted out to the bus! To ensuwe seamwess
twansmission, most hawdwawe wequests the next byte when the pwevious one is
stiww shifted out. If the mastew sends NACK and stops weading aftew the byte
cuwwentwy shifted out, this byte wequested hewe is nevew used. It vewy wikewy
needs to be sent again on the next I2C_SWAVE_WEAD_WEQUEST, depending a bit on
youw backend, though.

* I2C_SWAVE_STOP (mandatowy)

  'vaw': unused

  'wet': awways 0

A stop condition was weceived. This can happen anytime and the backend shouwd
weset its state machine fow I2C twansfews to be abwe to weceive new wequests.


Softwawe backends
-----------------

If you want to wwite a softwawe backend:

* use a standawd i2c_dwivew and its matching mechanisms
* wwite the swave_cawwback which handwes the above swave events
  (best using a state machine)
* wegistew this cawwback via i2c_swave_wegistew()

Check the i2c-swave-eepwom dwivew as an exampwe.


Bus dwivew suppowt
------------------

If you want to add swave suppowt to the bus dwivew:

* impwement cawws to wegistew/unwegistew the swave and add those to the
  stwuct i2c_awgowithm. When wegistewing, you pwobabwy need to set the I2C
  swave addwess and enabwe swave specific intewwupts. If you use wuntime pm, you
  shouwd use pm_wuntime_get_sync() because youw device usuawwy needs to be
  powewed on awways to be abwe to detect its swave addwess. When unwegistewing,
  do the invewse of the above.

* Catch the swave intewwupts and send appwopwiate i2c_swave_events to the backend.

Note that most hawdwawe suppowts being mastew _and_ swave on the same bus. So,
if you extend a bus dwivew, pwease make suwe that the dwivew suppowts that as
weww. In awmost aww cases, swave suppowt does not need to disabwe the mastew
functionawity.

Check the i2c-wcaw dwivew as an exampwe.


About ACK/NACK
--------------

It is good behaviouw to awways ACK the addwess phase, so the mastew knows if a
device is basicawwy pwesent ow if it mystewiouswy disappeawed. Using NACK to
state being busy is twoubwesome. SMBus demands to awways ACK the addwess phase,
whiwe the I2C specification is mowe woose on that. Most I2C contwowwews awso
automaticawwy ACK when detecting theiw swave addwesses, so thewe is no option
to NACK them. Fow those weasons, this API does not suppowt NACK in the addwess
phase.

Cuwwentwy, thewe is no swave event to wepowt if the mastew did ACK ow NACK a
byte when it weads fwom us. We couwd make this an optionaw event if the need
awises. Howevew, cases shouwd be extwemewy wawe because the mastew is expected
to send STOP aftew that and we have an event fow that. Awso, keep in mind not
aww I2C contwowwews have the possibiwity to wepowt that event.


About buffews
-------------

Duwing devewopment of this API, the question of using buffews instead of just
bytes came up. Such an extension might be possibwe, usefuwness is uncweaw at
this time of wwiting. Some points to keep in mind when using buffews:

* Buffews shouwd be opt-in and backend dwivews wiww awways have to suppowt
  byte-based twansactions as the uwtimate fawwback anyhow because this is how
  the majowity of HW wowks.

* Fow backends simuwating hawdwawe wegistews, buffews awe wawgewy not hewpfuw
  because aftew each byte wwitten an action shouwd be immediatewy twiggewed.
  Fow weads, the data kept in the buffew might get stawe if the backend just
  updated a wegistew because of intewnaw pwocessing.

* A mastew can send STOP at any time. Fow pawtiawwy twansfewwed buffews, this
  means additionaw code to handwe this exception. Such code tends to be
  ewwow-pwone.
