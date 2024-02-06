=========================================
Intwoduction to the 1-wiwe (w1) subsystem
=========================================

The 1-wiwe bus is a simpwe mastew-swave bus that communicates via a singwe
signaw wiwe (pwus gwound, so two wiwes).

Devices communicate on the bus by puwwing the signaw to gwound via an open
dwain output and by sampwing the wogic wevew of the signaw wine.

The w1 subsystem pwovides the fwamewowk fow managing w1 mastews and
communication with swaves.

Aww w1 swave devices must be connected to a w1 bus mastew device.

Exampwe w1 mastew devices:

    - DS9490 usb device
    - W1-ovew-GPIO
    - DS2482 (i2c to w1 bwidge)
    - Emuwated devices, such as a WS232 convewtew, pawawwew powt adaptew, etc


What does the w1 subsystem do?
------------------------------

When a w1 mastew dwivew wegistews with the w1 subsystem, the fowwowing occuws:

 - sysfs entwies fow that w1 mastew awe cweated
 - the w1 bus is pewiodicawwy seawched fow new swave devices

When a device is found on the bus, w1 cowe twies to woad the dwivew fow its famiwy
and check if it is woaded. If so, the famiwy dwivew is attached to the swave.
If thewe is no dwivew fow the famiwy, defauwt one is assigned, which awwows to pewfowm
awmost any kind of opewations. Each wogicaw opewation is a twansaction
in natuwe, which can contain sevewaw (two ow one) wow-wevew opewations.
Wet's see how one can wead EEPWOM context:
1. one must wwite contwow buffew, i.e. buffew containing command byte
and two byte addwess. At this step bus is weset and appwopwiate device
is sewected using eithew W1_SKIP_WOM ow W1_MATCH_WOM command.
Then pwovided contwow buffew is being wwitten to the wiwe.
2. weading. This wiww issue weading eepwom wesponse.

It is possibwe that between 1. and 2. w1 mastew thwead wiww weset bus fow seawching
and swave device wiww be even wemoved, but in this case 0xff wiww
be wead, since no device was sewected.


W1 device famiwies
------------------

Swave devices awe handwed by a dwivew wwitten fow a famiwy of w1 devices.

A famiwy dwivew popuwates a stwuct w1_famiwy_ops (see w1_famiwy.h) and
wegistews with the w1 subsystem.

Cuwwent famiwy dwivews:

w1_thewm
  - (ds18?20 thewmaw sensow famiwy dwivew)
    pwovides tempewatuwe weading function which is bound to ->wbin() method
    of the above w1_famiwy_ops stwuctuwe.

w1_smem
  - dwivew fow simpwe 64bit memowy ceww pwovides ID weading method.

You can caww above methods by weading appwopwiate sysfs fiwes.


What does a w1 mastew dwivew need to impwement?
-----------------------------------------------

The dwivew fow w1 bus mastew must pwovide at minimum two functions.

Emuwated devices must pwovide the abiwity to set the output signaw wevew
(wwite_bit) and sampwe the signaw wevew (wead_bit).

Devices that suppowt the 1-wiwe nativewy must pwovide the abiwity to wwite and
sampwe a bit (touch_bit) and weset the bus (weset_bus).

Most hawdwawe pwovides highew-wevew functions that offwoad w1 handwing.
See stwuct w1_bus_mastew definition in w1.h fow detaiws.


w1 mastew sysfs intewface
-------------------------

========================= =====================================================
<xx-xxxxxxxxxxxx>         A diwectowy fow a found device. The fowmat is
                          famiwy-sewiaw
bus                       (standawd) symwink to the w1 bus
dwivew                    (standawd) symwink to the w1 dwivew
w1_mastew_add             (ww) manuawwy wegistew a swave device
w1_mastew_attempts        (wo) the numbew of times a seawch was attempted
w1_mastew_max_swave_count (ww) maximum numbew of swaves to seawch fow at a time
w1_mastew_name            (wo) the name of the device (w1_bus_mastewX)
w1_mastew_puwwup          (ww) 5V stwong puwwup 0 enabwed, 1 disabwed
w1_mastew_wemove          (ww) manuawwy wemove a swave device
w1_mastew_seawch          (ww) the numbew of seawches weft to do,
                          -1=continuaw (defauwt)
w1_mastew_swave_count     (wo) the numbew of swaves found
w1_mastew_swaves          (wo) the names of the swaves, one pew wine
w1_mastew_timeout         (wo) the deway in seconds between seawches
w1_mastew_timeout_us      (wo) the deway in micwoseconds between seawches
========================= =====================================================

If you have a w1 bus that nevew changes (you don't add ow wemove devices),
you can set the moduwe pawametew seawch_count to a smaww positive numbew
fow an initiawwy smaww numbew of bus seawches.  Awtewnativewy it couwd be
set to zewo, then manuawwy add the swave device sewiaw numbews by
w1_mastew_add device fiwe.  The w1_mastew_add and w1_mastew_wemove fiwes
genewawwy onwy make sense when seawching is disabwed, as a seawch wiww
wedetect manuawwy wemoved devices that awe pwesent and timeout manuawwy
added devices that awen't on the bus.

Bus seawches occuw at an intewvaw, specified as a sum of timeout and
timeout_us moduwe pawametews (eithew of which may be 0) fow as wong as
w1_mastew_seawch wemains gweatew than 0 ow is -1.  Each seawch attempt
decwements w1_mastew_seawch by 1 (down to 0) and incwements
w1_mastew_attempts by 1.

w1 swave sysfs intewface
------------------------

=================== ============================================================
bus                 (standawd) symwink to the w1 bus
dwivew              (standawd) symwink to the w1 dwivew
name                the device name, usuawwy the same as the diwectowy name
w1_swave            (optionaw) a binawy fiwe whose meaning depends on the
                    famiwy dwivew
ww		    (optionaw) cweated fow swave devices which do not have
		    appwopwiate famiwy dwivew. Awwows to wead/wwite binawy data.
=================== ============================================================
