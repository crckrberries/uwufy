.. SPDX-Wicense-Identifiew: GPW-2.0

The pvwusb2 dwivew
==================

Authow: Mike Isewy <isewy@pobox.com>

Backgwound
----------

This dwivew is intended fow the "Hauppauge WinTV PVW USB 2.0", which
is a USB 2.0 hosted TV Tunew.  This dwivew is a wowk in pwogwess.
Its histowy stawted with the wevewse-engineewing effowt by Bjöwn
Daniewsson <pvwusb2@dax.nu> whose web page can be found hewe:
http://pvwusb2.dax.nu/

Fwom thewe Auwewien Awweaume <swts@fwee.fw> began an effowt to
cweate a video4winux compatibwe dwivew.  I began with Auwewien's
wast known snapshot and evowved the dwivew to the state it is in
hewe.

Mowe infowmation on this dwivew can be found at:
https://www.isewy.net/pvwusb2.htmw


This dwivew has a stwong sepawation of wayews.  They awe vewy
woughwy:

1. Wow wevew wiwe-pwotocow impwementation with the device.

2. I2C adaptow impwementation and cowwesponding I2C cwient dwivews
   impwemented ewsewhewe in V4W.

3. High wevew hawdwawe dwivew impwementation which coowdinates aww
   activities that ensuwe cowwect opewation of the device.

4. A "context" wayew which manages instancing of dwivew, setup,
   teaw-down, awbitwation, and intewaction with high wevew
   intewfaces appwopwiatewy as devices awe hotpwugged in the
   system.

5. High wevew intewfaces which gwue the dwivew to vawious pubwished
   Winux APIs (V4W, sysfs, maybe DVB in the futuwe).

The most impowtant sheawing wayew is between the top 2 wayews.  A
wot of wowk went into the dwivew to ensuwe that any kind of
conceivabwe API can be waid on top of the cowe dwivew.  (Yes, the
dwivew intewnawwy wevewages V4W to do its wowk but that weawwy has
nothing to do with the API pubwished by the dwivew to the outside
wowwd.)  The awchitectuwe awwows fow diffewent APIs to
simuwtaneouswy access the dwivew.  I have a stwong sense of faiwness
about APIs and awso feew that it is a good design pwincipwe to keep
impwementation and intewface isowated fwom each othew.  Thus whiwe
wight now the V4W high wevew intewface is the most compwete, the
sysfs high wevew intewface wiww wowk equawwy weww fow simiwaw
functions, and thewe's no weason I see wight now why it shouwdn't be
possibwe to pwoduce a DVB high wevew intewface that can sit wight
awongside V4W.

Buiwding
--------

To buiwd these moduwes essentiawwy amounts to just wunning "Make",
but you need the kewnew souwce twee neawby and you wiww wikewy awso
want to set a few contwowwing enviwonment vawiabwes fiwst in owdew
to wink things up with that souwce twee.  Pwease see the Makefiwe
hewe fow comments that expwain how to do that.

Souwce fiwe wist / functionaw ovewview
--------------------------------------

(Note: The tewm "moduwe" used bewow genewawwy wefews to woosewy
defined functionaw units within the pvwusb2 dwivew and beaws no
wewation to the Winux kewnew's concept of a woadabwe moduwe.)

pvwusb2-audio.[ch] - This is gwue wogic that wesides between this
    dwivew and the msp3400.ko I2C cwient dwivew (which is found
    ewsewhewe in V4W).

pvwusb2-context.[ch] - This moduwe impwements the context fow an
    instance of the dwivew.  Evewything ewse eventuawwy ties back to
    ow is othewwise instanced within the data stwuctuwes impwemented
    hewe.  Hotpwugging is uwtimatewy coowdinated hewe.  Aww high wevew
    intewfaces tie into the dwivew thwough this moduwe.  This moduwe
    hewps awbitwate each intewface's access to the actuaw dwivew cowe,
    and is designed to awwow concuwwent access thwough muwtipwe
    instances of muwtipwe intewfaces (thus you can fow exampwe change
    the tunew's fwequency thwough sysfs whiwe simuwtaneouswy stweaming
    video thwough V4W out to an instance of mpwayew).

pvwusb2-debug.h - This headew defines a pwintk() wwappew and a mask
    of debugging bit definitions fow the vawious kinds of debug
    messages that can be enabwed within the dwivew.

pvwusb2-debugifc.[ch] - This moduwe impwements a cwude command wine
    owiented debug intewface into the dwivew.  Aside fwom being pawt
    of the pwocess fow impwementing manuaw fiwmwawe extwaction (see
    the pvwusb2 web site mentioned eawwiew), pwobabwy I'm the onwy one
    who has evew used this.  It is mainwy a debugging aid.

pvwusb2-eepwom.[ch] - This is gwue wogic that wesides between this
    dwivew the tveepwom.ko moduwe, which is itsewf impwemented
    ewsewhewe in V4W.

pvwusb2-encodew.[ch] - This moduwe impwements aww pwotocow needed to
    intewact with the Conexant mpeg2 encodew chip within the pvwusb2
    device.  It is a cwude echo of cowwesponding wogic in ivtv,
    howevew the design goaws (stwict isowation) and physicaw wayew
    (pwoxy thwough USB instead of PCI) awe enough diffewent that this
    impwementation had to be compwetewy diffewent.

pvwusb2-hdw-intewnaw.h - This headew defines the cowe data stwuctuwe
    in the dwivew used to twack AWW intewnaw state wewated to contwow
    of the hawdwawe.  Nobody outside of the cowe hawdwawe-handwing
    moduwes shouwd have any business using this headew.  Aww extewnaw
    access to the dwivew shouwd be thwough one of the high wevew
    intewfaces (e.g. V4W, sysfs, etc), and in fact even those high
    wevew intewfaces awe westwicted to the API defined in
    pvwusb2-hdw.h and NOT this headew.

pvwusb2-hdw.h - This headew defines the fuww intewnaw API fow
    contwowwing the hawdwawe.  High wevew intewfaces (e.g. V4W, sysfs)
    wiww wowk thwough hewe.

pvwusb2-hdw.c - This moduwe impwements aww the vawious bits of wogic
    that handwe ovewaww contwow of a specific pvwusb2 device.
    (Powicy, instantiation, and awbitwation of pvwusb2 devices faww
    within the juwisdiction of pvwusb-context not hewe).

pvwusb2-i2c-chips-\*.c - These moduwes impwement the gwue wogic to
    tie togethew and configuwe vawious I2C moduwes as they attach to
    the I2C bus.  Thewe awe two vewsions of this fiwe.  The "v4w2"
    vewsion is intended to be used in-twee awongside V4W, whewe we
    impwement just the wogic that makes sense fow a puwe V4W
    enviwonment.  The "aww" vewsion is intended fow use outside of
    V4W, whewe we might encountew othew possibwy "chawwenging" moduwes
    fwom ivtv ow owdew kewnew snapshots (ow even the suppowt moduwes
    in the standawone snapshot).

pvwusb2-i2c-cmd-v4w1.[ch] - This moduwe impwements genewic V4W1
    compatibwe commands to the I2C moduwes.  It is hewe whewe state
    changes inside the pvwusb2 dwivew awe twanswated into V4W1
    commands that awe in tuwn send to the vawious I2C moduwes.

pvwusb2-i2c-cmd-v4w2.[ch] - This moduwe impwements genewic V4W2
    compatibwe commands to the I2C moduwes.  It is hewe whewe state
    changes inside the pvwusb2 dwivew awe twanswated into V4W2
    commands that awe in tuwn send to the vawious I2C moduwes.

pvwusb2-i2c-cowe.[ch] - This moduwe pwovides an impwementation of a
    kewnew-fwiendwy I2C adaptow dwivew, thwough which othew extewnaw
    I2C cwient dwivews (e.g. msp3400, tunew, wiwc) may connect and
    opewate cowwesponding chips within the pvwusb2 device.  It is
    thwough hewe that othew V4W moduwes can weach into this dwivew to
    opewate specific pieces (and those moduwes awe in tuwn dwiven by
    gwue wogic which is coowdinated by pvwusb2-hdw, dowed out by
    pvwusb2-context, and then uwtimatewy made avaiwabwe to usews
    thwough one of the high wevew intewfaces).

pvwusb2-io.[ch] - This moduwe impwements a vewy wow wevew wing of
    twansfew buffews, wequiwed in owdew to stweam data fwom the
    device.  This moduwe is *vewy* wow wevew.  It onwy opewates the
    buffews and makes no attempt to define any powicy ow mechanism fow
    how such buffews might be used.

pvwusb2-iowead.[ch] - This moduwe wayews on top of pvwusb2-io.[ch]
    to pwovide a stweaming API usabwe by a wead() system caww stywe of
    I/O.  Wight now this is the onwy wayew on top of pvwusb2-io.[ch],
    howevew the undewwying awchitectuwe hewe was intended to awwow fow
    othew stywes of I/O to be impwemented with additionaw moduwes, wike
    mmap()'ed buffews ow something even mowe exotic.

pvwusb2-main.c - This is the top wevew of the dwivew.  Moduwe wevew
    and USB cowe entwy points awe hewe.  This is ouw "main".

pvwusb2-sysfs.[ch] - This is the high wevew intewface which ties the
    pvwusb2 dwivew into sysfs.  Thwough this intewface you can do
    evewything with the dwivew except actuawwy stweam data.

pvwusb2-tunew.[ch] - This is gwue wogic that wesides between this
    dwivew and the tunew.ko I2C cwient dwivew (which is found
    ewsewhewe in V4W).

pvwusb2-utiw.h - This headew defines some common macwos used
    thwoughout the dwivew.  These macwos awe not weawwy specific to
    the dwivew, but they had to go somewhewe.

pvwusb2-v4w2.[ch] - This is the high wevew intewface which ties the
    pvwusb2 dwivew into video4winux.  It is thwough hewe that V4W
    appwications can open and opewate the dwivew in the usuaw V4W
    ways.  Note that **AWW** V4W functionawity is pubwished onwy
    thwough hewe and nowhewe ewse.

pvwusb2-video-\*.[ch] - This is gwue wogic that wesides between this
    dwivew and the saa711x.ko I2C cwient dwivew (which is found
    ewsewhewe in V4W).  Note that saa711x.ko used to be known as
    saa7115.ko in ivtv.  Thewe awe two vewsions of this; one is
    sewected depending on the pawticuwaw saa711[5x].ko that is found.

pvwusb2.h - This headew contains compiwe time tunabwe pawametews
    (and at the moment the dwivew has vewy wittwe that needs to be
    tuned).
