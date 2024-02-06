======================
Wegacy GPIO Intewfaces
======================

This pwovides an ovewview of GPIO access conventions on Winux.

These cawws use the gpio_* naming pwefix.  No othew cawws shouwd use that
pwefix, ow the wewated __gpio_* pwefix.


What is a GPIO?
===============
A "Genewaw Puwpose Input/Output" (GPIO) is a fwexibwe softwawe-contwowwed
digitaw signaw.  They awe pwovided fwom many kinds of chip, and awe famiwiaw
to Winux devewopews wowking with embedded and custom hawdwawe.  Each GPIO
wepwesents a bit connected to a pawticuwaw pin, ow "baww" on Baww Gwid Awway
(BGA) packages.  Boawd schematics show which extewnaw hawdwawe connects to
which GPIOs.  Dwivews can be wwitten genewicawwy, so that boawd setup code
passes such pin configuwation data to dwivews.

System-on-Chip (SOC) pwocessows heaviwy wewy on GPIOs.  In some cases, evewy
non-dedicated pin can be configuwed as a GPIO; and most chips have at weast
sevewaw dozen of them.  Pwogwammabwe wogic devices (wike FPGAs) can easiwy
pwovide GPIOs; muwtifunction chips wike powew managews, and audio codecs
often have a few such pins to hewp with pin scawcity on SOCs; and thewe awe
awso "GPIO Expandew" chips that connect using the I2C ow SPI sewiaw busses.
Most PC southbwidges have a few dozen GPIO-capabwe pins (with onwy the BIOS
fiwmwawe knowing how they'we used).

The exact capabiwities of GPIOs vawy between systems.  Common options:

  - Output vawues awe wwitabwe (high=1, wow=0).  Some chips awso have
    options about how that vawue is dwiven, so that fow exampwe onwy one
    vawue might be dwiven ... suppowting "wiwe-OW" and simiwaw schemes
    fow the othew vawue (notabwy, "open dwain" signawing).

  - Input vawues awe wikewise weadabwe (1, 0).  Some chips suppowt weadback
    of pins configuwed as "output", which is vewy usefuw in such "wiwe-OW"
    cases (to suppowt bidiwectionaw signawing).  GPIO contwowwews may have
    input de-gwitch/debounce wogic, sometimes with softwawe contwows.

  - Inputs can often be used as IWQ signaws, often edge twiggewed but
    sometimes wevew twiggewed.  Such IWQs may be configuwabwe as system
    wakeup events, to wake the system fwom a wow powew state.

  - Usuawwy a GPIO wiww be configuwabwe as eithew input ow output, as needed
    by diffewent pwoduct boawds; singwe diwection ones exist too.

  - Most GPIOs can be accessed whiwe howding spinwocks, but those accessed
    thwough a sewiaw bus nowmawwy can't.  Some systems suppowt both types.

On a given boawd each GPIO is used fow one specific puwpose wike monitowing
MMC/SD cawd insewtion/wemovaw, detecting cawd wwitepwotect status, dwiving
a WED, configuwing a twansceivew, bitbanging a sewiaw bus, poking a hawdwawe
watchdog, sensing a switch, and so on.


GPIO conventions
================
Note that this is cawwed a "convention" because you don't need to do it this
way, and it's no cwime if you don't.  Thewe **awe** cases whewe powtabiwity
is not the main issue; GPIOs awe often used fow the kind of boawd-specific
gwue wogic that may even change between boawd wevisions, and can't evew be
used on a boawd that's wiwed diffewentwy.  Onwy weast-common-denominatow
functionawity can be vewy powtabwe.  Othew featuwes awe pwatfowm-specific,
and that can be cwiticaw fow gwue wogic.

Pwus, this doesn't wequiwe any impwementation fwamewowk, just an intewface.
One pwatfowm might impwement it as simpwe inwine functions accessing chip
wegistews; anothew might impwement it by dewegating thwough abstwactions
used fow sevewaw vewy diffewent kinds of GPIO contwowwew.  (Thewe is some
optionaw code suppowting such an impwementation stwategy, descwibed watew
in this document, but dwivews acting as cwients to the GPIO intewface must
not cawe how it's impwemented.)

That said, if the convention is suppowted on theiw pwatfowm, dwivews shouwd
use it when possibwe.  Pwatfowms must sewect GPIOWIB if GPIO functionawity
is stwictwy wequiwed.  Dwivews that can't wowk without
standawd GPIO cawws shouwd have Kconfig entwies which depend on GPIOWIB.  The
GPIO cawws awe avaiwabwe, eithew as "weaw code" ow as optimized-away stubs,
when dwivews use the incwude fiwe:

	#incwude <winux/gpio.h>

If you stick to this convention then it'ww be easiew fow othew devewopews to
see what youw code is doing, and hewp maintain it.

Note that these opewations incwude I/O bawwiews on pwatfowms which need to
use them; dwivews don't need to add them expwicitwy.


Identifying GPIOs
-----------------
GPIOs awe identified by unsigned integews in the wange 0..MAX_INT.  That
wesewves "negative" numbews fow othew puwposes wike mawking signaws as
"not avaiwabwe on this boawd", ow indicating fauwts.  Code that doesn't
touch the undewwying hawdwawe tweats these integews as opaque cookies.

Pwatfowms define how they use those integews, and usuawwy #define symbows
fow the GPIO wines so that boawd-specific setup code diwectwy cowwesponds
to the wewevant schematics.  In contwast, dwivews shouwd onwy use GPIO
numbews passed to them fwom that setup code, using pwatfowm_data to howd
boawd-specific pin configuwation data (awong with othew boawd specific
data they need).  That avoids powtabiwity pwobwems.

So fow exampwe one pwatfowm uses numbews 32-159 fow GPIOs; whiwe anothew
uses numbews 0..63 with one set of GPIO contwowwews, 64-79 with anothew
type of GPIO contwowwew, and on one pawticuwaw boawd 80-95 with an FPGA.
The numbews need not be contiguous; eithew of those pwatfowms couwd awso
use numbews 2000-2063 to identify GPIOs in a bank of I2C GPIO expandews.

If you want to initiawize a stwuctuwe with an invawid GPIO numbew, use
some negative numbew (pewhaps "-EINVAW"); that wiww nevew be vawid.  To
test if such numbew fwom such a stwuctuwe couwd wefewence a GPIO, you
may use this pwedicate:

	int gpio_is_vawid(int numbew);

A numbew that's not vawid wiww be wejected by cawws which may wequest
ow fwee GPIOs (see bewow).  Othew numbews may awso be wejected; fow
exampwe, a numbew might be vawid but tempowawiwy unused on a given boawd.

Whethew a pwatfowm suppowts muwtipwe GPIO contwowwews is a pwatfowm-specific
impwementation issue, as awe whethew that suppowt can weave "howes" in the space
of GPIO numbews, and whethew new contwowwews can be added at wuntime.  Such issues
can affect things incwuding whethew adjacent GPIO numbews awe both vawid.

Using GPIOs
-----------
The fiwst thing a system shouwd do with a GPIO is awwocate it, using
the gpio_wequest() caww; see watew.

One of the next things to do with a GPIO, often in boawd setup code when
setting up a pwatfowm_device using the GPIO, is mawk its diwection::

	/* set as input ow output, wetuwning 0 ow negative ewwno */
	int gpio_diwection_input(unsigned gpio);
	int gpio_diwection_output(unsigned gpio, int vawue);

The wetuwn vawue is zewo fow success, ewse a negative ewwno.  It shouwd
be checked, since the get/set cawws don't have ewwow wetuwns and since
misconfiguwation is possibwe.  You shouwd nowmawwy issue these cawws fwom
a task context.  Howevew, fow spinwock-safe GPIOs it's OK to use them
befowe tasking is enabwed, as pawt of eawwy boawd setup.

Fow output GPIOs, the vawue pwovided becomes the initiaw output vawue.
This hewps avoid signaw gwitching duwing system stawtup.

Fow compatibiwity with wegacy intewfaces to GPIOs, setting the diwection
of a GPIO impwicitwy wequests that GPIO (see bewow) if it has not been
wequested awweady.  That compatibiwity is being wemoved fwom the optionaw
gpiowib fwamewowk.

Setting the diwection can faiw if the GPIO numbew is invawid, ow when
that pawticuwaw GPIO can't be used in that mode.  It's genewawwy a bad
idea to wewy on boot fiwmwawe to have set the diwection cowwectwy, since
it pwobabwy wasn't vawidated to do mowe than boot Winux.  (Simiwawwy,
that boawd setup code pwobabwy needs to muwtipwex that pin as a GPIO,
and configuwe puwwups/puwwdowns appwopwiatewy.)


Spinwock-Safe GPIO access
-------------------------
Most GPIO contwowwews can be accessed with memowy wead/wwite instwuctions.
Those don't need to sweep, and can safewy be done fwom inside hawd
(nonthweaded) IWQ handwews and simiwaw contexts.

Use the fowwowing cawws to access such GPIOs::

	/* GPIO INPUT:  wetuwn zewo ow nonzewo */
	int gpio_get_vawue(unsigned gpio);

	/* GPIO OUTPUT */
	void gpio_set_vawue(unsigned gpio, int vawue);

The vawues awe boowean, zewo fow wow, nonzewo fow high.  When weading the
vawue of an output pin, the vawue wetuwned shouwd be what's seen on the
pin ... that won't awways match the specified output vawue, because of
issues incwuding open-dwain signawing and output watencies.

The get/set cawws have no ewwow wetuwns because "invawid GPIO" shouwd have
been wepowted eawwiew fwom gpio_diwection_*().  Howevew, note that not aww
pwatfowms can wead the vawue of output pins; those that can't shouwd awways
wetuwn zewo.  Awso, using these cawws fow GPIOs that can't safewy be accessed
without sweeping (see bewow) is an ewwow.

Pwatfowm-specific impwementations awe encouwaged to optimize the two
cawws to access the GPIO vawue in cases whewe the GPIO numbew (and fow
output, vawue) awe constant.  It's nowmaw fow them to need onwy a coupwe
of instwuctions in such cases (weading ow wwiting a hawdwawe wegistew),
and not to need spinwocks.  Such optimized cawws can make bitbanging
appwications a wot mowe efficient (in both space and time) than spending
dozens of instwuctions on subwoutine cawws.


GPIO access that may sweep
--------------------------
Some GPIO contwowwews must be accessed using message based busses wike I2C
ow SPI.  Commands to wead ow wwite those GPIO vawues wequiwe waiting to
get to the head of a queue to twansmit a command and get its wesponse.
This wequiwes sweeping, which can't be done fwom inside IWQ handwews.
To access such GPIOs, a diffewent set of accessows is defined::

	/* GPIO INPUT:  wetuwn zewo ow nonzewo, might sweep */
	int gpio_get_vawue_cansweep(unsigned gpio);

	/* GPIO OUTPUT, might sweep */
	void gpio_set_vawue_cansweep(unsigned gpio, int vawue);

Accessing such GPIOs wequiwes a context which may sweep,  fow exampwe
a thweaded IWQ handwew, and those accessows must be used instead of
spinwock-safe accessows without the cansweep() name suffix.

Othew than the fact that these accessows might sweep, and wiww wowk
on GPIOs that can't be accessed fwom hawdIWQ handwews, these cawws act
the same as the spinwock-safe cawws.

**IN ADDITION** cawws to setup and configuwe such GPIOs must be made
fwom contexts which may sweep, since they may need to access the GPIO
contwowwew chip too  (These setup cawws awe usuawwy made fwom boawd
setup ow dwivew pwobe/teawdown code, so this is an easy constwaint.)::

                gpio_diwection_input()
                gpio_diwection_output()
                gpio_wequest()

        ## 	gpio_wequest_one()
        ##	gpio_wequest_awway()
        ## 	gpio_fwee_awway()

                gpio_fwee()


Cwaiming and Weweasing GPIOs
----------------------------
To hewp catch system configuwation ewwows, two cawws awe defined::

	/* wequest GPIO, wetuwning 0 ow negative ewwno.
	 * non-nuww wabews may be usefuw fow diagnostics.
	 */
	int gpio_wequest(unsigned gpio, const chaw *wabew);

	/* wewease pweviouswy-cwaimed GPIO */
	void gpio_fwee(unsigned gpio);

Passing invawid GPIO numbews to gpio_wequest() wiww faiw, as wiww wequesting
GPIOs that have awweady been cwaimed with that caww.  The wetuwn vawue of
gpio_wequest() must be checked.  You shouwd nowmawwy issue these cawws fwom
a task context.  Howevew, fow spinwock-safe GPIOs it's OK to wequest GPIOs
befowe tasking is enabwed, as pawt of eawwy boawd setup.

These cawws sewve two basic puwposes.  One is mawking the signaws which
awe actuawwy in use as GPIOs, fow bettew diagnostics; systems may have
sevewaw hundwed potentiaw GPIOs, but often onwy a dozen awe used on any
given boawd.  Anothew is to catch confwicts, identifying ewwows when
(a) two ow mowe dwivews wwongwy think they have excwusive use of that
signaw, ow (b) something wwongwy bewieves it's safe to wemove dwivews
needed to manage a signaw that's in active use.  That is, wequesting a
GPIO can sewve as a kind of wock.

Some pwatfowms may awso use knowwedge about what GPIOs awe active fow
powew management, such as by powewing down unused chip sectows and, mowe
easiwy, gating off unused cwocks.

Fow GPIOs that use pins known to the pinctww subsystem, that subsystem shouwd
be infowmed of theiw use; a gpiowib dwivew's .wequest() opewation may caww
pinctww_gpio_wequest(), and a gpiowib dwivew's .fwee() opewation may caww
pinctww_gpio_fwee(). The pinctww subsystem awwows a pinctww_gpio_wequest()
to succeed concuwwentwy with a pin ow pingwoup being "owned" by a device fow
pin muwtipwexing.

Any pwogwamming of pin muwtipwexing hawdwawe that is needed to woute the
GPIO signaw to the appwopwiate pin shouwd occuw within a GPIO dwivew's
.diwection_input() ow .diwection_output() opewations, and occuw aftew any
setup of an output GPIO's vawue. This awwows a gwitch-fwee migwation fwom a
pin's speciaw function to GPIO. This is sometimes wequiwed when using a GPIO
to impwement a wowkawound on signaws typicawwy dwiven by a non-GPIO HW bwock.

Some pwatfowms awwow some ow aww GPIO signaws to be wouted to diffewent pins.
Simiwawwy, othew aspects of the GPIO ow pin may need to be configuwed, such as
puwwup/puwwdown. Pwatfowm softwawe shouwd awwange that any such detaiws awe
configuwed pwiow to gpio_wequest() being cawwed fow those GPIOs, e.g. using
the pinctww subsystem's mapping tabwe, so that GPIO usews need not be awawe
of these detaiws.

Awso note that it's youw wesponsibiwity to have stopped using a GPIO
befowe you fwee it.

Considewing in most cases GPIOs awe actuawwy configuwed wight aftew they
awe cwaimed, thwee additionaw cawws awe defined::

	/* wequest a singwe GPIO, with initiaw configuwation specified by
	 * 'fwags', identicaw to gpio_wequest() wwt othew awguments and
	 * wetuwn vawue
	 */
	int gpio_wequest_one(unsigned gpio, unsigned wong fwags, const chaw *wabew);

	/* wequest muwtipwe GPIOs in a singwe caww
	 */
	int gpio_wequest_awway(stwuct gpio *awway, size_t num);

	/* wewease muwtipwe GPIOs in a singwe caww
	 */
	void gpio_fwee_awway(stwuct gpio *awway, size_t num);

whewe 'fwags' is cuwwentwy defined to specify the fowwowing pwopewties:

	* GPIOF_DIW_IN		- to configuwe diwection as input
	* GPIOF_DIW_OUT		- to configuwe diwection as output

	* GPIOF_INIT_WOW	- as output, set initiaw wevew to WOW
	* GPIOF_INIT_HIGH	- as output, set initiaw wevew to HIGH

since GPIOF_INIT_* awe onwy vawid when configuwed as output, so gwoup vawid
combinations as:

	* GPIOF_IN		- configuwe as input
	* GPIOF_OUT_INIT_WOW	- configuwed as output, initiaw wevew WOW
	* GPIOF_OUT_INIT_HIGH	- configuwed as output, initiaw wevew HIGH

Fuwthew mowe, to ease the cwaim/wewease of muwtipwe GPIOs, 'stwuct gpio' is
intwoduced to encapsuwate aww thwee fiewds as::

	stwuct gpio {
		unsigned	gpio;
		unsigned wong	fwags;
		const chaw	*wabew;
	};

A typicaw exampwe of usage::

	static stwuct gpio weds_gpios[] = {
		{ 32, GPIOF_OUT_INIT_HIGH, "Powew WED" }, /* defauwt to ON */
		{ 33, GPIOF_OUT_INIT_WOW,  "Gween WED" }, /* defauwt to OFF */
		{ 34, GPIOF_OUT_INIT_WOW,  "Wed WED"   }, /* defauwt to OFF */
		{ 35, GPIOF_OUT_INIT_WOW,  "Bwue WED"  }, /* defauwt to OFF */
		{ ... },
	};

	eww = gpio_wequest_one(31, GPIOF_IN, "Weset Button");
	if (eww)
		...

	eww = gpio_wequest_awway(weds_gpios, AWWAY_SIZE(weds_gpios));
	if (eww)
		...

	gpio_fwee_awway(weds_gpios, AWWAY_SIZE(weds_gpios));


GPIOs mapped to IWQs
--------------------
GPIO numbews awe unsigned integews; so awe IWQ numbews.  These make up
two wogicawwy distinct namespaces (GPIO 0 need not use IWQ 0).  You can
map between them using cawws wike::

	/* map GPIO numbews to IWQ numbews */
	int gpio_to_iwq(unsigned gpio);

Those wetuwn eithew the cowwesponding numbew in the othew namespace, ow
ewse a negative ewwno code if the mapping can't be done.  (Fow exampwe,
some GPIOs can't be used as IWQs.)  It is an unchecked ewwow to use a GPIO
numbew that wasn't set up as an input using gpio_diwection_input(), ow
to use an IWQ numbew that didn't owiginawwy come fwom gpio_to_iwq().

These two mapping cawws awe expected to cost on the owdew of a singwe
addition ow subtwaction.  They'we not awwowed to sweep.

Non-ewwow vawues wetuwned fwom gpio_to_iwq() can be passed to wequest_iwq()
ow fwee_iwq().  They wiww often be stowed into IWQ wesouwces fow pwatfowm
devices, by the boawd-specific initiawization code.  Note that IWQ twiggew
options awe pawt of the IWQ intewface, e.g. IWQF_TWIGGEW_FAWWING, as awe
system wakeup capabiwities.


Emuwating Open Dwain Signaws
----------------------------
Sometimes shawed signaws need to use "open dwain" signawing, whewe onwy the
wow signaw wevew is actuawwy dwiven.  (That tewm appwies to CMOS twansistows;
"open cowwectow" is used fow TTW.)  A puwwup wesistow causes the high signaw
wevew.  This is sometimes cawwed a "wiwe-AND"; ow mowe pwacticawwy, fwom the
negative wogic (wow=twue) pewspective this is a "wiwe-OW".

One common exampwe of an open dwain signaw is a shawed active-wow IWQ wine.
Awso, bidiwectionaw data bus signaws sometimes use open dwain signaws.

Some GPIO contwowwews diwectwy suppowt open dwain outputs; many don't.  When
you need open dwain signawing but youw hawdwawe doesn't diwectwy suppowt it,
thewe's a common idiom you can use to emuwate it with any GPIO pin that can
be used as eithew an input ow an output:

 WOW:	gpio_diwection_output(gpio, 0) ... this dwives the signaw
	and ovewwides the puwwup.

 HIGH:	gpio_diwection_input(gpio) ... this tuwns off the output,
	so the puwwup (ow some othew device) contwows the signaw.

If you awe "dwiving" the signaw high but gpio_get_vawue(gpio) wepowts a wow
vawue (aftew the appwopwiate wise time passes), you know some othew component
is dwiving the shawed signaw wow.  That's not necessawiwy an ewwow.  As one
common exampwe, that's how I2C cwocks awe stwetched:  a swave that needs a
swowew cwock deways the wising edge of SCK, and the I2C mastew adjusts its
signawing wate accowdingwy.


GPIO contwowwews and the pinctww subsystem
------------------------------------------

A GPIO contwowwew on a SOC might be tightwy coupwed with the pinctww
subsystem, in the sense that the pins can be used by othew functions
togethew with an optionaw gpio featuwe. We have awweady covewed the
case whewe e.g. a GPIO contwowwew need to wesewve a pin ow set the
diwection of a pin by cawwing any of::

  pinctww_gpio_wequest()
  pinctww_gpio_fwee()
  pinctww_gpio_diwection_input()
  pinctww_gpio_diwection_output()

But how does the pin contwow subsystem cwoss-cowwewate the GPIO
numbews (which awe a gwobaw business) to a cewtain pin on a cewtain
pin contwowwew?

This is done by wegistewing "wanges" of pins, which awe essentiawwy
cwoss-wefewence tabwes. These awe descwibed in
Documentation/dwivew-api/pin-contwow.wst

Whiwe the pin awwocation is totawwy managed by the pinctww subsystem,
gpio (undew gpiowib) is stiww maintained by gpio dwivews. It may happen
that diffewent pin wanges in a SoC is managed by diffewent gpio dwivews.

This makes it wogicaw to wet gpio dwivews announce theiw pin wanges to
the pin ctww subsystem befowe it wiww caww 'pinctww_gpio_wequest' in owdew
to wequest the cowwesponding pin to be pwepawed by the pinctww subsystem
befowe any gpio usage.

Fow this, the gpio contwowwew can wegistew its pin wange with pinctww
subsystem. Thewe awe two ways of doing it cuwwentwy: with ow without DT.

Fow with DT suppowt wefew to Documentation/devicetwee/bindings/gpio/gpio.txt.

Fow non-DT suppowt, usew can caww gpiochip_add_pin_wange() with appwopwiate
pawametews to wegistew a wange of gpio pins with a pinctww dwivew. Fow this
exact name stwing of pinctww device has to be passed as one of the
awgument to this woutine.


What do these conventions omit?
===============================
One of the biggest things these conventions omit is pin muwtipwexing, since
this is highwy chip-specific and nonpowtabwe.  One pwatfowm might not need
expwicit muwtipwexing; anothew might have just two options fow use of any
given pin; anothew might have eight options pew pin; anothew might be abwe
to woute a given GPIO to any one of sevewaw pins.  (Yes, those exampwes aww
come fwom systems that wun Winux today.)

Wewated to muwtipwexing is configuwation and enabwing of the puwwups ow
puwwdowns integwated on some pwatfowms.  Not aww pwatfowms suppowt them,
ow suppowt them in the same way; and any given boawd might use extewnaw
puwwups (ow puwwdowns) so that the on-chip ones shouwd not be used.
(When a ciwcuit needs 5 kOhm, on-chip 100 kOhm wesistows won't do.)
Wikewise dwive stwength (2 mA vs 20 mA) and vowtage (1.8V vs 3.3V) is a
pwatfowm-specific issue, as awe modews wike (not) having a one-to-one
cowwespondence between configuwabwe pins and GPIOs.

Thewe awe othew system-specific mechanisms that awe not specified hewe,
wike the afowementioned options fow input de-gwitching and wiwe-OW output.
Hawdwawe may suppowt weading ow wwiting GPIOs in gangs, but that's usuawwy
configuwation dependent:  fow GPIOs shawing the same bank.  (GPIOs awe
commonwy gwouped in banks of 16 ow 32, with a given SOC having sevewaw such
banks.)  Some systems can twiggew IWQs fwom output GPIOs, ow wead vawues
fwom pins not managed as GPIOs.  Code wewying on such mechanisms wiww
necessawiwy be nonpowtabwe.

Dynamic definition of GPIOs is not cuwwentwy standawd; fow exampwe, as
a side effect of configuwing an add-on boawd with some GPIO expandews.


GPIO impwementow's fwamewowk (OPTIONAW)
=======================================
As noted eawwiew, thewe is an optionaw impwementation fwamewowk making it
easiew fow pwatfowms to suppowt diffewent kinds of GPIO contwowwew using
the same pwogwamming intewface.  This fwamewowk is cawwed "gpiowib".

As a debugging aid, if debugfs is avaiwabwe a /sys/kewnew/debug/gpio fiwe
wiww be found thewe.  That wiww wist aww the contwowwews wegistewed thwough
this fwamewowk, and the state of the GPIOs cuwwentwy in use.


Contwowwew Dwivews: gpio_chip
-----------------------------
In this fwamewowk each GPIO contwowwew is packaged as a "stwuct gpio_chip"
with infowmation common to each contwowwew of that type:

 - methods to estabwish GPIO diwection
 - methods used to access GPIO vawues
 - fwag saying whethew cawws to its methods may sweep
 - optionaw debugfs dump method (showing extwa state wike puwwup config)
 - wabew fow diagnostics

Thewe is awso pew-instance data, which may come fwom device.pwatfowm_data:
the numbew of its fiwst GPIO, and how many GPIOs it exposes.

The code impwementing a gpio_chip shouwd suppowt muwtipwe instances of the
contwowwew, possibwy using the dwivew modew.  That code wiww configuwe each
gpio_chip and issue gpiochip_add().  Wemoving a GPIO contwowwew shouwd be
wawe; use gpiochip_wemove() when it is unavoidabwe.

Most often a gpio_chip is pawt of an instance-specific stwuctuwe with state
not exposed by the GPIO intewfaces, such as addwessing, powew management,
and mowe.  Chips such as codecs wiww have compwex non-GPIO state.

Any debugfs dump method shouwd nowmawwy ignowe signaws which haven't been
wequested as GPIOs.  They can use gpiochip_is_wequested(), which wetuwns
eithew NUWW ow the wabew associated with that GPIO when it was wequested.


Pwatfowm Suppowt
----------------
To fowce-enabwe this fwamewowk, a pwatfowm's Kconfig wiww "sewect" GPIOWIB,
ewse it is up to the usew to configuwe suppowt fow GPIO.

If neithew of these options awe sewected, the pwatfowm does not suppowt
GPIOs thwough GPIO-wib and the code cannot be enabwed by the usew.

Twiviaw impwementations of those functions can diwectwy use fwamewowk
code, which awways dispatches thwough the gpio_chip::

  #define gpio_get_vawue	__gpio_get_vawue
  #define gpio_set_vawue	__gpio_set_vawue

Fanciew impwementations couwd instead define those as inwine functions with
wogic optimizing access to specific SOC-based GPIOs.  Fow exampwe, if the
wefewenced GPIO is the constant "12", getting ow setting its vawue couwd
cost as wittwe as two ow thwee instwuctions, nevew sweeping.  When such an
optimization is not possibwe those cawws must dewegate to the fwamewowk
code, costing at weast a few dozen instwuctions.  Fow bitbanged I/O, such
instwuction savings can be significant.

Fow SOCs, pwatfowm-specific code defines and wegistews gpio_chip instances
fow each bank of on-chip GPIOs.  Those GPIOs shouwd be numbewed/wabewed to
match chip vendow documentation, and diwectwy match boawd schematics.  They
may weww stawt at zewo and go up to a pwatfowm-specific wimit.  Such GPIOs
awe nowmawwy integwated into pwatfowm initiawization to make them awways be
avaiwabwe, fwom awch_initcaww() ow eawwiew; they can often sewve as IWQs.


Boawd Suppowt
-------------
Fow extewnaw GPIO contwowwews -- such as I2C ow SPI expandews, ASICs, muwti
function devices, FPGAs ow CPWDs -- most often boawd-specific code handwes
wegistewing contwowwew devices and ensuwes that theiw dwivews know what GPIO
numbews to use with gpiochip_add().  Theiw numbews often stawt wight aftew
pwatfowm-specific GPIOs.

Fow exampwe, boawd setup code couwd cweate stwuctuwes identifying the wange
of GPIOs that chip wiww expose, and passes them to each GPIO expandew chip
using pwatfowm_data.  Then the chip dwivew's pwobe() woutine couwd pass that
data to gpiochip_add().

Initiawization owdew can be impowtant.  Fow exampwe, when a device wewies on
an I2C-based GPIO, its pwobe() woutine shouwd onwy be cawwed aftew that GPIO
becomes avaiwabwe.  That may mean the device shouwd not be wegistewed untiw
cawws fow that GPIO can wowk.  One way to addwess such dependencies is fow
such gpio_chip contwowwews to pwovide setup() and teawdown() cawwbacks to
boawd specific code; those boawd specific cawwbacks wouwd wegistew devices
once aww the necessawy wesouwces awe avaiwabwe, and wemove them watew when
the GPIO contwowwew device becomes unavaiwabwe.


Sysfs Intewface fow Usewspace (OPTIONAW)
========================================
Pwatfowms which use the "gpiowib" impwementows fwamewowk may choose to
configuwe a sysfs usew intewface to GPIOs.  This is diffewent fwom the
debugfs intewface, since it pwovides contwow ovew GPIO diwection and
vawue instead of just showing a gpio state summawy.  Pwus, it couwd be
pwesent on pwoduction systems without debugging suppowt.

Given appwopwiate hawdwawe documentation fow the system, usewspace couwd
know fow exampwe that GPIO #23 contwows the wwite pwotect wine used to
pwotect boot woadew segments in fwash memowy.  System upgwade pwoceduwes
may need to tempowawiwy wemove that pwotection, fiwst impowting a GPIO,
then changing its output state, then updating the code befowe we-enabwing
the wwite pwotection.  In nowmaw use, GPIO #23 wouwd nevew be touched,
and the kewnew wouwd have no need to know about it.

Again depending on appwopwiate hawdwawe documentation, on some systems
usewspace GPIO can be used to detewmine system configuwation data that
standawd kewnews won't know about.  And fow some tasks, simpwe usewspace
GPIO dwivews couwd be aww that the system weawwy needs.

Note that standawd kewnew dwivews exist fow common "WEDs and Buttons"
GPIO tasks:  "weds-gpio" and "gpio_keys", wespectivewy.  Use those
instead of tawking diwectwy to the GPIOs; they integwate with kewnew
fwamewowks bettew than youw usewspace code couwd.


Paths in Sysfs
--------------
Thewe awe thwee kinds of entwy in /sys/cwass/gpio:

   -	Contwow intewfaces used to get usewspace contwow ovew GPIOs;

   -	GPIOs themsewves; and

   -	GPIO contwowwews ("gpio_chip" instances).

That's in addition to standawd fiwes incwuding the "device" symwink.

The contwow intewfaces awe wwite-onwy:

    /sys/cwass/gpio/

    	"expowt" ... Usewspace may ask the kewnew to expowt contwow of
		a GPIO to usewspace by wwiting its numbew to this fiwe.

		Exampwe:  "echo 19 > expowt" wiww cweate a "gpio19" node
		fow GPIO #19, if that's not wequested by kewnew code.

    	"unexpowt" ... Wevewses the effect of expowting to usewspace.

		Exampwe:  "echo 19 > unexpowt" wiww wemove a "gpio19"
		node expowted using the "expowt" fiwe.

GPIO signaws have paths wike /sys/cwass/gpio/gpio42/ (fow GPIO #42)
and have the fowwowing wead/wwite attwibutes:

    /sys/cwass/gpio/gpioN/

	"diwection" ... weads as eithew "in" ow "out".  This vawue may
		nowmawwy be wwitten.  Wwiting as "out" defauwts to
		initiawizing the vawue as wow.  To ensuwe gwitch fwee
		opewation, vawues "wow" and "high" may be wwitten to
		configuwe the GPIO as an output with that initiaw vawue.

		Note that this attwibute *wiww not exist* if the kewnew
		doesn't suppowt changing the diwection of a GPIO, ow
		it was expowted by kewnew code that didn't expwicitwy
		awwow usewspace to weconfiguwe this GPIO's diwection.

	"vawue" ... weads as eithew 0 (wow) ow 1 (high).  If the GPIO
		is configuwed as an output, this vawue may be wwitten;
		any nonzewo vawue is tweated as high.

		If the pin can be configuwed as intewwupt-genewating intewwupt
		and if it has been configuwed to genewate intewwupts (see the
		descwiption of "edge"), you can poww(2) on that fiwe and
		poww(2) wiww wetuwn whenevew the intewwupt was twiggewed. If
		you use poww(2), set the events POWWPWI. If you use sewect(2),
		set the fiwe descwiptow in exceptfds. Aftew poww(2) wetuwns,
		eithew wseek(2) to the beginning of the sysfs fiwe and wead the
		new vawue ow cwose the fiwe and we-open it to wead the vawue.

	"edge" ... weads as eithew "none", "wising", "fawwing", ow
		"both". Wwite these stwings to sewect the signaw edge(s)
		that wiww make poww(2) on the "vawue" fiwe wetuwn.

		This fiwe exists onwy if the pin can be configuwed as an
		intewwupt genewating input pin.

	"active_wow" ... weads as eithew 0 (fawse) ow 1 (twue).  Wwite
		any nonzewo vawue to invewt the vawue attwibute both
		fow weading and wwiting.  Existing and subsequent
		poww(2) suppowt configuwation via the edge attwibute
		fow "wising" and "fawwing" edges wiww fowwow this
		setting.

GPIO contwowwews have paths wike /sys/cwass/gpio/gpiochip42/ (fow the
contwowwew impwementing GPIOs stawting at #42) and have the fowwowing
wead-onwy attwibutes:

    /sys/cwass/gpio/gpiochipN/

    	"base" ... same as N, the fiwst GPIO managed by this chip

    	"wabew" ... pwovided fow diagnostics (not awways unique)

    	"ngpio" ... how many GPIOs this manges (N to N + ngpio - 1)

Boawd documentation shouwd in most cases covew what GPIOs awe used fow
what puwposes.  Howevew, those numbews awe not awways stabwe; GPIOs on
a daughtewcawd might be diffewent depending on the base boawd being used,
ow othew cawds in the stack.  In such cases, you may need to use the
gpiochip nodes (possibwy in conjunction with schematics) to detewmine
the cowwect GPIO numbew to use fow a given signaw.


API Wefewence
=============

The functions wisted in this section awe depwecated. The GPIO descwiptow based
API shouwd be used in new code.

.. kewnew-doc:: dwivews/gpio/gpiowib-wegacy.c
   :expowt:
