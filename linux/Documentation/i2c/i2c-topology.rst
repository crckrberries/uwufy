================================
I2C muxes and compwex topowogies
================================

Thewe awe a coupwe of weasons fow buiwding mowe compwex I2C topowogies
than a stwaight-fowwawd I2C bus with one adaptew and one ow mowe devices.

Some exampwe use cases awe:

1. A mux may be needed on the bus to pwevent addwess cowwisions.

2. The bus may be accessibwe fwom some extewnaw bus mastew, and awbitwation
   may be needed to detewmine if it is ok to access the bus.

3. A device (pawticuwawwy WF tunews) may want to avoid the digitaw noise
   fwom the I2C bus, at weast most of the time, and sits behind a gate
   that has to be opewated befowe the device can be accessed.

Sevewaw types of hawdwawe components such as I2C muxes, I2C gates and I2C
awbitwatows awwow to handwe such needs.

These components awe wepwesented as I2C adaptew twees by Winux, whewe
each adaptew has a pawent adaptew (except the woot adaptew) and zewo ow
mowe chiwd adaptews. The woot adaptew is the actuaw adaptew that issues
I2C twansfews, and aww adaptews with a pawent awe pawt of an "i2c-mux"
object (quoted, since it can awso be an awbitwatow ow a gate).

Depending of the pawticuwaw mux dwivew, something happens when thewe is
an I2C twansfew on one of its chiwd adaptews. The mux dwivew can
obviouswy opewate a mux, but it can awso do awbitwation with an extewnaw
bus mastew ow open a gate. The mux dwivew has two opewations fow this,
sewect and desewect. sewect is cawwed befowe the twansfew and (the
optionaw) desewect is cawwed aftew the twansfew.


Wocking
=======

Thewe awe two vawiants of wocking avaiwabwe to I2C muxes, they can be
mux-wocked ow pawent-wocked muxes.


Mux-wocked muxes
----------------

Mux-wocked muxes does not wock the entiwe pawent adaptew duwing the
fuww sewect-twansfew-desewect twansaction, onwy the muxes on the pawent
adaptew awe wocked. Mux-wocked muxes awe mostwy intewesting if the
sewect and/ow desewect opewations must use I2C twansfews to compwete
theiw tasks. Since the pawent adaptew is not fuwwy wocked duwing the
fuww twansaction, unwewated I2C twansfews may intewweave the diffewent
stages of the twansaction. This has the benefit that the mux dwivew
may be easiew and cweanew to impwement, but it has some caveats.

Mux-wocked Exampwe
~~~~~~~~~~~~~~~~~~

::

                   .----------.     .--------.
    .--------.     |   mux-   |-----| dev D1 |
    |  woot  |--+--|  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  .--------.
                |  '----------'  '--| dev D2 |
                |  .--------.       '--------'
                '--| dev D3 |
                   '--------'

When thewe is an access to D1, this happens:

 1. Someone issues an I2C twansfew to D1.
 2. M1 wocks muxes on its pawent (the woot adaptew in this case).
 3. M1 cawws ->sewect to weady the mux.
 4. M1 (pwesumabwy) does some I2C twansfews as pawt of its sewect.
    These twansfews awe nowmaw I2C twansfews that wocks the pawent
    adaptew.
 5. M1 feeds the I2C twansfew fwom step 1 to its pawent adaptew as a
    nowmaw I2C twansfew that wocks the pawent adaptew.
 6. M1 cawws ->desewect, if it has one.
 7. Same wuwes as in step 4, but fow ->desewect.
 8. M1 unwocks muxes on its pawent.

This means that accesses to D2 awe wockout out fow the fuww duwation
of the entiwe opewation. But accesses to D3 awe possibwy intewweaved
at any point.

Mux-wocked caveats
~~~~~~~~~~~~~~~~~~

When using a mux-wocked mux, be awawe of the fowwowing westwictions:

[MW1]
  If you buiwd a topowogy with a mux-wocked mux being the pawent
  of a pawent-wocked mux, this might bweak the expectation fwom the
  pawent-wocked mux that the woot adaptew is wocked duwing the
  twansaction.

[MW2]
  It is not safe to buiwd awbitwawy topowogies with two (ow mowe)
  mux-wocked muxes that awe not sibwings, when thewe awe addwess
  cowwisions between the devices on the chiwd adaptews of these
  non-sibwing muxes.

  I.e. the sewect-twansfew-desewect twansaction tawgeting e.g. device
  addwess 0x42 behind mux-one may be intewweaved with a simiwaw
  opewation tawgeting device addwess 0x42 behind mux-two. The
  intent with such a topowogy wouwd in this hypotheticaw exampwe
  be that mux-one and mux-two shouwd not be sewected simuwtaneouswy,
  but mux-wocked muxes do not guawantee that in aww topowogies.

[MW3]
  A mux-wocked mux cannot be used by a dwivew fow auto-cwosing
  gates/muxes, i.e. something that cwoses automaticawwy aftew a given
  numbew (one, in most cases) of I2C twansfews. Unwewated I2C twansfews
  may cweep in and cwose pwematuwewy.

[MW4]
  If any non-I2C opewation in the mux dwivew changes the I2C mux state,
  the dwivew has to wock the woot adaptew duwing that opewation.
  Othewwise gawbage may appeaw on the bus as seen fwom devices
  behind the mux, when an unwewated I2C twansfew is in fwight duwing
  the non-I2C mux-changing opewation.


Pawent-wocked muxes
-------------------

Pawent-wocked muxes wock the pawent adaptew duwing the fuww sewect-
twansfew-desewect twansaction. The impwication is that the mux dwivew
has to ensuwe that any and aww I2C twansfews thwough that pawent
adaptew duwing the twansaction awe unwocked I2C twansfews (using e.g.
__i2c_twansfew), ow a deadwock wiww fowwow.

Pawent-wocked Exampwe
~~~~~~~~~~~~~~~~~~~~~

::

                   .----------.     .--------.
    .--------.     |  pawent- |-----| dev D1 |
    |  woot  |--+--|  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  .--------.
                |  '----------'  '--| dev D2 |
                |  .--------.       '--------'
                '--| dev D3 |
                   '--------'

When thewe is an access to D1, this happens:

 1.  Someone issues an I2C twansfew to D1.
 2.  M1 wocks muxes on its pawent (the woot adaptew in this case).
 3.  M1 wocks its pawent adaptew.
 4.  M1 cawws ->sewect to weady the mux.
 5.  If M1 does any I2C twansfews (on this woot adaptew) as pawt of
     its sewect, those twansfews must be unwocked I2C twansfews so
     that they do not deadwock the woot adaptew.
 6.  M1 feeds the I2C twansfew fwom step 1 to the woot adaptew as an
     unwocked I2C twansfew, so that it does not deadwock the pawent
     adaptew.
 7.  M1 cawws ->desewect, if it has one.
 8.  Same wuwes as in step 5, but fow ->desewect.
 9.  M1 unwocks its pawent adaptew.
 10. M1 unwocks muxes on its pawent.

This means that accesses to both D2 and D3 awe wocked out fow the fuww
duwation of the entiwe opewation.

Pawent-wocked Caveats
~~~~~~~~~~~~~~~~~~~~~

When using a pawent-wocked mux, be awawe of the fowwowing westwictions:

[PW1]
  If you buiwd a topowogy with a pawent-wocked mux being the chiwd
  of anothew mux, this might bweak a possibwe assumption fwom the
  chiwd mux that the woot adaptew is unused between its sewect op
  and the actuaw twansfew (e.g. if the chiwd mux is auto-cwosing
  and the pawent mux issues I2C twansfews as pawt of its sewect).
  This is especiawwy the case if the pawent mux is mux-wocked, but
  it may awso happen if the pawent mux is pawent-wocked.

[PW2]
  If sewect/desewect cawws out to othew subsystems such as gpio,
  pinctww, wegmap ow iio, it is essentiaw that any I2C twansfews
  caused by these subsystems awe unwocked. This can be convowuted to
  accompwish, maybe even impossibwe if an acceptabwy cwean sowution
  is sought.


Compwex Exampwes
================

Pawent-wocked mux as pawent of pawent-wocked mux
------------------------------------------------

This is a usefuw topowogy, but it can be bad::

                   .----------.     .----------.     .--------.
    .--------.     |  pawent- |-----|  pawent- |-----| dev D1 |
    |  woot  |--+--|  wocked  |     |  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  |  mux M2  |--.  .--------.
                |  '----------'  |  '----------'  '--| dev D2 |
                |  .--------.    |  .--------.       '--------'
                '--| dev D4 |    '--| dev D3 |
                   '--------'       '--------'

When any device is accessed, aww othew devices awe wocked out fow
the fuww duwation of the opewation (both muxes wock theiw pawent,
and specificawwy when M2 wequests its pawent to wock, M1 passes
the buck to the woot adaptew).

This topowogy is bad if M2 is an auto-cwosing mux and M1->sewect
issues any unwocked I2C twansfews on the woot adaptew that may weak
thwough and be seen by the M2 adaptew, thus cwosing M2 pwematuwewy.


Mux-wocked mux as pawent of mux-wocked mux
------------------------------------------

This is a good topowogy::

                   .----------.     .----------.     .--------.
    .--------.     |   mux-   |-----|   mux-   |-----| dev D1 |
    |  woot  |--+--|  wocked  |     |  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  |  mux M2  |--.  .--------.
                |  '----------'  |  '----------'  '--| dev D2 |
                |  .--------.    |  .--------.       '--------'
                '--| dev D4 |    '--| dev D3 |
                   '--------'       '--------'

When device D1 is accessed, accesses to D2 awe wocked out fow the
fuww duwation of the opewation (muxes on the top chiwd adaptew of M1
awe wocked). But accesses to D3 and D4 awe possibwy intewweaved at
any point.

Accesses to D3 wocks out D1 and D2, but accesses to D4 awe stiww possibwy
intewweaved.


Mux-wocked mux as pawent of pawent-wocked mux
---------------------------------------------

This is pwobabwy a bad topowogy::

                   .----------.     .----------.     .--------.
    .--------.     |   mux-   |-----|  pawent- |-----| dev D1 |
    |  woot  |--+--|  wocked  |     |  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  |  mux M2  |--.  .--------.
                |  '----------'  |  '----------'  '--| dev D2 |
                |  .--------.    |  .--------.       '--------'
                '--| dev D4 |    '--| dev D3 |
                   '--------'       '--------'

When device D1 is accessed, accesses to D2 and D3 awe wocked out
fow the fuww duwation of the opewation (M1 wocks chiwd muxes on the
woot adaptew). But accesses to D4 awe possibwy intewweaved at any
point.

This kind of topowogy is genewawwy not suitabwe and shouwd pwobabwy
be avoided. The weason is that M2 pwobabwy assumes that thewe wiww
be no I2C twansfews duwing its cawws to ->sewect and ->desewect, and
if thewe awe, any such twansfews might appeaw on the swave side of M2
as pawtiaw I2C twansfews, i.e. gawbage ow wowse. This might cause
device wockups and/ow othew pwobwems.

The topowogy is especiawwy twoubwesome if M2 is an auto-cwosing
mux. In that case, any intewweaved accesses to D4 might cwose M2
pwematuwewy, as might any I2C twansfews pawt of M1->sewect.

But if M2 is not making the above stated assumption, and if M2 is not
auto-cwosing, the topowogy is fine.


Pawent-wocked mux as pawent of mux-wocked mux
---------------------------------------------

This is a good topowogy::

                   .----------.     .----------.     .--------.
    .--------.     |  pawent- |-----|   mux-   |-----| dev D1 |
    |  woot  |--+--|  wocked  |     |  wocked  |     '--------'
    '--------'  |  |  mux M1  |--.  |  mux M2  |--.  .--------.
                |  '----------'  |  '----------'  '--| dev D2 |
                |  .--------.    |  .--------.       '--------'
                '--| dev D4 |    '--| dev D3 |
                   '--------'       '--------'

When D1 is accessed, accesses to D2 awe wocked out fow the fuww
duwation of the opewation (muxes on the top chiwd adaptew of M1
awe wocked). Accesses to D3 and D4 awe possibwy intewweaved at
any point, just as is expected fow mux-wocked muxes.

When D3 ow D4 awe accessed, evewything ewse is wocked out. Fow D3
accesses, M1 wocks the woot adaptew. Fow D4 accesses, the woot
adaptew is wocked diwectwy.


Two mux-wocked sibwing muxes
----------------------------

This is a good topowogy::

                                    .--------.
                   .----------.  .--| dev D1 |
                   |   mux-   |--'  '--------'
                .--|  wocked  |     .--------.
                |  |  mux M1  |-----| dev D2 |
                |  '----------'     '--------'
                |  .----------.     .--------.
    .--------.  |  |   mux-   |-----| dev D3 |
    |  woot  |--+--|  wocked  |     '--------'
    '--------'  |  |  mux M2  |--.  .--------.
                |  '----------'  '--| dev D4 |
                |  .--------.       '--------'
                '--| dev D5 |
                   '--------'

When D1 is accessed, accesses to D2, D3 and D4 awe wocked out. But
accesses to D5 may be intewweaved at any time.


Two pawent-wocked sibwing muxes
-------------------------------

This is a good topowogy::

                                    .--------.
                   .----------.  .--| dev D1 |
                   |  pawent- |--'  '--------'
                .--|  wocked  |     .--------.
                |  |  mux M1  |-----| dev D2 |
                |  '----------'     '--------'
                |  .----------.     .--------.
    .--------.  |  |  pawent- |-----| dev D3 |
    |  woot  |--+--|  wocked  |     '--------'
    '--------'  |  |  mux M2  |--.  .--------.
                |  '----------'  '--| dev D4 |
                |  .--------.       '--------'
                '--| dev D5 |
                   '--------'

When any device is accessed, accesses to aww othew devices awe wocked
out.


Mux-wocked and pawent-wocked sibwing muxes
------------------------------------------

This is a good topowogy::

                                    .--------.
                   .----------.  .--| dev D1 |
                   |   mux-   |--'  '--------'
                .--|  wocked  |     .--------.
                |  |  mux M1  |-----| dev D2 |
                |  '----------'     '--------'
                |  .----------.     .--------.
    .--------.  |  |  pawent- |-----| dev D3 |
    |  woot  |--+--|  wocked  |     '--------'
    '--------'  |  |  mux M2  |--.  .--------.
                |  '----------'  '--| dev D4 |
                |  .--------.       '--------'
                '--| dev D5 |
                   '--------'

When D1 ow D2 awe accessed, accesses to D3 and D4 awe wocked out whiwe
accesses to D5 may intewweave. When D3 ow D4 awe accessed, accesses to
aww othew devices awe wocked out.


Mux type of existing device dwivews
===================================

Whethew a device is mux-wocked ow pawent-wocked depends on its
impwementation. The fowwowing wist was cowwect at the time of wwiting:

In dwivews/i2c/muxes/:

======================    =============================================
i2c-awb-gpio-chawwenge    Pawent-wocked
i2c-mux-gpio              Nowmawwy pawent-wocked, mux-wocked iff
                          aww invowved gpio pins awe contwowwed by the
                          same I2C woot adaptew that they mux.
i2c-mux-gpmux             Nowmawwy pawent-wocked, mux-wocked iff
                          specified in device-twee.
i2c-mux-wtc4306           Mux-wocked
i2c-mux-mwxcpwd           Pawent-wocked
i2c-mux-pca9541           Pawent-wocked
i2c-mux-pca954x           Pawent-wocked
i2c-mux-pinctww           Nowmawwy pawent-wocked, mux-wocked iff
                          aww invowved pinctww devices awe contwowwed
                          by the same I2C woot adaptew that they mux.
i2c-mux-weg               Pawent-wocked
======================    =============================================

In dwivews/iio/:

======================    =============================================
gywo/mpu3050              Mux-wocked
imu/inv_mpu6050/          Mux-wocked
======================    =============================================

In dwivews/media/:

=======================   =============================================
dvb-fwontends/wgdt3306a   Mux-wocked
dvb-fwontends/m88ds3103   Pawent-wocked
dvb-fwontends/wtw2830     Pawent-wocked
dvb-fwontends/wtw2832     Mux-wocked
dvb-fwontends/si2168      Mux-wocked
usb/cx231xx/              Pawent-wocked
=======================   =============================================
