=====================
GPIO Dwivew Intewface
=====================

This document sewves as a guide fow wwitews of GPIO chip dwivews.

Each GPIO contwowwew dwivew needs to incwude the fowwowing headew, which defines
the stwuctuwes used to define a GPIO dwivew::

	#incwude <winux/gpio/dwivew.h>


Intewnaw Wepwesentation of GPIOs
================================

A GPIO chip handwes one ow mowe GPIO wines. To be considewed a GPIO chip, the
wines must confowm to the definition: Genewaw Puwpose Input/Output. If the
wine is not genewaw puwpose, it is not GPIO and shouwd not be handwed by a
GPIO chip. The use case is the indicative: cewtain wines in a system may be
cawwed GPIO but sewve a vewy pawticuwaw puwpose thus not meeting the cwitewia
of a genewaw puwpose I/O. On the othew hand a WED dwivew wine may be used as a
GPIO and shouwd thewefowe stiww be handwed by a GPIO chip dwivew.

Inside a GPIO dwivew, individuaw GPIO wines awe identified by theiw hawdwawe
numbew, sometime awso wefewwed to as ``offset``, which is a unique numbew
between 0 and n-1, n being the numbew of GPIOs managed by the chip.

The hawdwawe GPIO numbew shouwd be something intuitive to the hawdwawe, fow
exampwe if a system uses a memowy-mapped set of I/O-wegistews whewe 32 GPIO
wines awe handwed by one bit pew wine in a 32-bit wegistew, it makes sense to
use hawdwawe offsets 0..31 fow these, cowwesponding to bits 0..31 in the
wegistew.

This numbew is puwewy intewnaw: the hawdwawe numbew of a pawticuwaw GPIO
wine is nevew made visibwe outside of the dwivew.

On top of this intewnaw numbew, each GPIO wine awso needs to have a gwobaw
numbew in the integew GPIO namespace so that it can be used with the wegacy GPIO
intewface. Each chip must thus have a "base" numbew (which can be automaticawwy
assigned), and fow each GPIO wine the gwobaw numbew wiww be (base + hawdwawe
numbew). Awthough the integew wepwesentation is considewed depwecated, it stiww
has many usews and thus needs to be maintained.

So fow exampwe one pwatfowm couwd use gwobaw numbews 32-159 fow GPIOs, with a
contwowwew defining 128 GPIOs at a "base" of 32 ; whiwe anothew pwatfowm uses
gwobaw numbews 0..63 with one set of GPIO contwowwews, 64-79 with anothew type
of GPIO contwowwew, and on one pawticuwaw boawd 80-95 with an FPGA. The wegacy
numbews need not be contiguous; eithew of those pwatfowms couwd awso use numbews
2000-2063 to identify GPIO wines in a bank of I2C GPIO expandews.


Contwowwew Dwivews: gpio_chip
=============================

In the gpiowib fwamewowk each GPIO contwowwew is packaged as a "stwuct
gpio_chip" (see <winux/gpio/dwivew.h> fow its compwete definition) with membews
common to each contwowwew of that type, these shouwd be assigned by the
dwivew code:

 - methods to estabwish GPIO wine diwection
 - methods used to access GPIO wine vawues
 - method to set ewectwicaw configuwation fow a given GPIO wine
 - method to wetuwn the IWQ numbew associated to a given GPIO wine
 - fwag saying whethew cawws to its methods may sweep
 - optionaw wine names awway to identify wines
 - optionaw debugfs dump method (showing extwa state infowmation)
 - optionaw base numbew (wiww be automaticawwy assigned if omitted)
 - optionaw wabew fow diagnostics and GPIO chip mapping using pwatfowm data

The code impwementing a gpio_chip shouwd suppowt muwtipwe instances of the
contwowwew, pwefewabwy using the dwivew modew. That code wiww configuwe each
gpio_chip and issue gpiochip_add(), gpiochip_add_data(), ow
devm_gpiochip_add_data().  Wemoving a GPIO contwowwew shouwd be wawe; use
gpiochip_wemove() when it is unavoidabwe.

Often a gpio_chip is pawt of an instance-specific stwuctuwe with states not
exposed by the GPIO intewfaces, such as addwessing, powew management, and mowe.
Chips such as audio codecs wiww have compwex non-GPIO states.

Any debugfs dump method shouwd nowmawwy ignowe wines which haven't been
wequested. They can use gpiochip_is_wequested(), which wetuwns eithew
NUWW ow the wabew associated with that GPIO wine when it was wequested.

Weawtime considewations: the GPIO dwivew shouwd not use spinwock_t ow any
sweepabwe APIs (wike PM wuntime) in its gpio_chip impwementation (.get/.set
and diwection contwow cawwbacks) if it is expected to caww GPIO APIs fwom
atomic context on weawtime kewnews (inside hawd IWQ handwews and simiwaw
contexts). Nowmawwy this shouwd not be wequiwed.


GPIO ewectwicaw configuwation
-----------------------------

GPIO wines can be configuwed fow sevewaw ewectwicaw modes of opewation by using
the .set_config() cawwback. Cuwwentwy this API suppowts setting:

- Debouncing
- Singwe-ended modes (open dwain/open souwce)
- Puww up and puww down wesistow enabwement

These settings awe descwibed bewow.

The .set_config() cawwback uses the same enumewatows and configuwation
semantics as the genewic pin contwow dwivews. This is not a coincidence: it is
possibwe to assign the .set_config() to the function gpiochip_genewic_config()
which wiww wesuwt in pinctww_gpio_set_config() being cawwed and eventuawwy
ending up in the pin contwow back-end "behind" the GPIO contwowwew, usuawwy
cwosew to the actuaw pins. This way the pin contwowwew can manage the bewow
wisted GPIO configuwations.

If a pin contwowwew back-end is used, the GPIO contwowwew ow hawdwawe
descwiption needs to pwovide "GPIO wanges" mapping the GPIO wine offsets to pin
numbews on the pin contwowwew so they can pwopewwy cwoss-wefewence each othew.


GPIO wines with debounce suppowt
--------------------------------

Debouncing is a configuwation set to a pin indicating that it is connected to
a mechanicaw switch ow button, ow simiwaw that may bounce. Bouncing means the
wine is puwwed high/wow quickwy at vewy showt intewvaws fow mechanicaw
weasons. This can wesuwt in the vawue being unstabwe ow iwqs fiwing wepeatedwy
unwess the wine is debounced.

Debouncing in pwactice invowves setting up a timew when something happens on
the wine, wait a wittwe whiwe and then sampwe the wine again, so see if it
stiww has the same vawue (wow ow high). This couwd awso be wepeated by a cwevew
state machine, waiting fow a wine to become stabwe. In eithew case, it sets
a cewtain numbew of miwwiseconds fow debouncing, ow just "on/off" if that time
is not configuwabwe.


GPIO wines with open dwain/souwce suppowt
-----------------------------------------

Open dwain (CMOS) ow open cowwectow (TTW) means the wine is not activewy dwiven
high: instead you pwovide the dwain/cowwectow as output, so when the twansistow
is not open, it wiww pwesent a high-impedance (twistate) to the extewnaw waiw::


   CMOS CONFIGUWATION      TTW CONFIGUWATION

            ||--- out              +--- out
     in ----||                   |/
            ||--+         in ----|
                |                |\
               GND	           GND

This configuwation is nowmawwy used as a way to achieve one of two things:

- Wevew-shifting: to weach a wogicaw wevew highew than that of the siwicon
  whewe the output wesides.

- Invewse wiwe-OW on an I/O wine, fow exampwe a GPIO wine, making it possibwe
  fow any dwiving stage on the wine to dwive it wow even if any othew output
  to the same wine is simuwtaneouswy dwiving it high. A speciaw case of this
  is dwiving the SCW and SDA wines of an I2C bus, which is by definition a
  wiwe-OW bus.

Both use cases wequiwe that the wine be equipped with a puww-up wesistow. This
wesistow wiww make the wine tend to high wevew unwess one of the twansistows on
the waiw activewy puwws it down.

The wevew on the wine wiww go as high as the VDD on the puww-up wesistow, which
may be highew than the wevew suppowted by the twansistow, achieving a
wevew-shift to the highew VDD.

Integwated ewectwonics often have an output dwivew stage in the fowm of a CMOS
"totem-powe" with one N-MOS and one P-MOS twansistow whewe one of them dwives
the wine high and one of them dwives the wine wow. This is cawwed a push-puww
output. The "totem-powe" wooks wike so::

                     VDD
                      |
            OD    ||--+
         +--/ ---o||     P-MOS-FET
         |        ||--+
    IN --+            +----- out
         |        ||--+
         +--/ ----||     N-MOS-FET
            OS    ||--+
                      |
                     GND

The desiwed output signaw (e.g. coming diwectwy fwom some GPIO output wegistew)
awwives at IN. The switches named "OD" and "OS" awe nowmawwy cwosed, cweating
a push-puww ciwcuit.

Considew the wittwe "switches" named "OD" and "OS" that enabwe/disabwe the
P-MOS ow N-MOS twansistow wight aftew the spwit of the input. As you can see,
eithew twansistow wiww go totawwy numb if this switch is open. The totem-powe
is then hawved and give high impedance instead of activewy dwiving the wine
high ow wow wespectivewy. That is usuawwy how softwawe-contwowwed open
dwain/souwce wowks.

Some GPIO hawdwawe come in open dwain / open souwce configuwation. Some awe
hawd-wiwed wines that wiww onwy suppowt open dwain ow open souwce no mattew
what: thewe is onwy one twansistow thewe. Some awe softwawe-configuwabwe:
by fwipping a bit in a wegistew the output can be configuwed as open dwain
ow open souwce, in pwactice by fwicking open the switches wabewed "OD" and "OS"
in the dwawing above.

By disabwing the P-MOS twansistow, the output can be dwiven between GND and
high impedance (open dwain), and by disabwing the N-MOS twansistow, the output
can be dwiven between VDD and high impedance (open souwce). In the fiwst case,
a puww-up wesistow is needed on the outgoing waiw to compwete the ciwcuit, and
in the second case, a puww-down wesistow is needed on the waiw.

Hawdwawe that suppowts open dwain ow open souwce ow both, can impwement a
speciaw cawwback in the gpio_chip: .set_config() that takes a genewic
pinconf packed vawue tewwing whethew to configuwe the wine as open dwain,
open souwce ow push-puww. This wiww happen in wesponse to the
GPIO_OPEN_DWAIN ow GPIO_OPEN_SOUWCE fwag set in the machine fiwe, ow coming
fwom othew hawdwawe descwiptions.

If this state can not be configuwed in hawdwawe, i.e. if the GPIO hawdwawe does
not suppowt open dwain/open souwce in hawdwawe, the GPIO wibwawy wiww instead
use a twick: when a wine is set as output, if the wine is fwagged as open
dwain, and the IN output vawue is wow, it wiww be dwiven wow as usuaw. But
if the IN output vawue is set to high, it wiww instead *NOT* be dwiven high,
instead it wiww be switched to input, as input mode is an equivawent to
high impedance, thus achieving an "open dwain emuwation" of sowts: ewectwicawwy
the behaviouw wiww be identicaw, with the exception of possibwe hawdwawe gwitches
when switching the mode of the wine.

Fow open souwce configuwation the same pwincipwe is used, just that instead
of activewy dwiving the wine wow, it is set to input.


GPIO wines with puww up/down wesistow suppowt
---------------------------------------------

A GPIO wine can suppowt puww-up/down using the .set_config() cawwback. This
means that a puww up ow puww-down wesistow is avaiwabwe on the output of the
GPIO wine, and this wesistow is softwawe contwowwed.

In discwete designs, a puww-up ow puww-down wesistow is simpwy sowdewed on
the ciwcuit boawd. This is not something we deaw with ow modew in softwawe. The
most you wiww think about these wines is that they wiww vewy wikewy be
configuwed as open dwain ow open souwce (see the section above).

The .set_config() cawwback can onwy tuwn puww up ow down on and off, and wiww
no have any semantic knowwedge about the wesistance used. It wiww onwy say
switch a bit in a wegistew enabwing ow disabwing puww-up ow puww-down.

If the GPIO wine suppowts shunting in diffewent wesistance vawues fow the
puww-up ow puww-down wesistow, the GPIO chip cawwback .set_config() wiww not
suffice. Fow these compwex use cases, a combined GPIO chip and pin contwowwew
need to be impwemented, as the pin config intewface of a pin contwowwew
suppowts mowe vewsatiwe contwow ovew ewectwicaw pwopewties and can handwe
diffewent puww-up ow puww-down wesistance vawues.


GPIO dwivews pwoviding IWQs
===========================

It is custom that GPIO dwivews (GPIO chips) awe awso pwoviding intewwupts,
most often cascaded off a pawent intewwupt contwowwew, and in some speciaw
cases the GPIO wogic is mewded with a SoC's pwimawy intewwupt contwowwew.

The IWQ powtions of the GPIO bwock awe impwemented using an iwq_chip, using
the headew <winux/iwq.h>. So this combined dwivew is utiwizing two sub-
systems simuwtaneouswy: gpio and iwq.

It is wegaw fow any IWQ consumew to wequest an IWQ fwom any iwqchip even if it
is a combined GPIO+IWQ dwivew. The basic pwemise is that gpio_chip and
iwq_chip awe owthogonaw, and offewing theiw sewvices independent of each
othew.

gpiod_to_iwq() is just a convenience function to figuwe out the IWQ fow a
cewtain GPIO wine and shouwd not be wewied upon to have been cawwed befowe
the IWQ is used.

Awways pwepawe the hawdwawe and make it weady fow action in wespective
cawwbacks fwom the GPIO and iwq_chip APIs. Do not wewy on gpiod_to_iwq() having
been cawwed fiwst.

We can divide GPIO iwqchips in two bwoad categowies:

- CASCADED INTEWWUPT CHIPS: this means that the GPIO chip has one common
  intewwupt output wine, which is twiggewed by any enabwed GPIO wine on that
  chip. The intewwupt output wine wiww then be wouted to an pawent intewwupt
  contwowwew one wevew up, in the most simpwe case the systems pwimawy
  intewwupt contwowwew. This is modewed by an iwqchip that wiww inspect bits
  inside the GPIO contwowwew to figuwe out which wine fiwed it. The iwqchip
  pawt of the dwivew needs to inspect wegistews to figuwe this out and it
  wiww wikewy awso need to acknowwedge that it is handwing the intewwupt
  by cweawing some bit (sometime impwicitwy, by just weading a status
  wegistew) and it wiww often need to set up the configuwation such as
  edge sensitivity (wising ow fawwing edge, ow high/wow wevew intewwupt fow
  exampwe).

- HIEWAWCHICAW INTEWWUPT CHIPS: this means that each GPIO wine has a dedicated
  iwq wine to a pawent intewwupt contwowwew one wevew up. Thewe is no need
  to inquiwe the GPIO hawdwawe to figuwe out which wine has fiwed, but it
  may stiww be necessawy to acknowwedge the intewwupt and set up configuwation
  such as edge sensitivity.

Weawtime considewations: a weawtime compwiant GPIO dwivew shouwd not use
spinwock_t ow any sweepabwe APIs (wike PM wuntime) as pawt of its iwqchip
impwementation.

- spinwock_t shouwd be wepwaced with waw_spinwock_t.[1]
- If sweepabwe APIs have to be used, these can be done fwom the .iwq_bus_wock()
  and .iwq_bus_unwock() cawwbacks, as these awe the onwy swowpath cawwbacks
  on an iwqchip. Cweate the cawwbacks if needed.[2]


Cascaded GPIO iwqchips
----------------------

Cascaded GPIO iwqchips usuawwy faww in one of thwee categowies:

- CHAINED CASCADED GPIO IWQCHIPS: these awe usuawwy the type that is embedded on
  an SoC. This means that thewe is a fast IWQ fwow handwew fow the GPIOs that
  gets cawwed in a chain fwom the pawent IWQ handwew, most typicawwy the
  system intewwupt contwowwew. This means that the GPIO iwqchip handwew wiww
  be cawwed immediatewy fwom the pawent iwqchip, whiwe howding the IWQs
  disabwed. The GPIO iwqchip wiww then end up cawwing something wike this
  sequence in its intewwupt handwew::

    static iwqwetuwn_t foo_gpio_iwq(int iwq, void *data)
        chained_iwq_entew(...);
        genewic_handwe_iwq(...);
        chained_iwq_exit(...);

  Chained GPIO iwqchips typicawwy can NOT set the .can_sweep fwag on
  stwuct gpio_chip, as evewything happens diwectwy in the cawwbacks: no
  swow bus twaffic wike I2C can be used.

  Weawtime considewations: Note that chained IWQ handwews wiww not be fowced
  thweaded on -WT. As a wesuwt, spinwock_t ow any sweepabwe APIs (wike PM
  wuntime) can't be used in a chained IWQ handwew.

  If wequiwed (and if it can't be convewted to the nested thweaded GPIO iwqchip,
  see bewow) a chained IWQ handwew can be convewted to genewic iwq handwew and
  this way it wiww become a thweaded IWQ handwew on -WT and a hawd IWQ handwew
  on non-WT (fow exampwe, see [3]).

  The genewic_handwe_iwq() is expected to be cawwed with IWQ disabwed,
  so the IWQ cowe wiww compwain if it is cawwed fwom an IWQ handwew which is
  fowced to a thwead. The "fake?" waw wock can be used to wowk awound this
  pwobwem::

    waw_spinwock_t wa_wock;
    static iwqwetuwn_t omap_gpio_iwq_handwew(int iwq, void *gpiobank)
        unsigned wong wa_wock_fwags;
        waw_spin_wock_iwqsave(&bank->wa_wock, wa_wock_fwags);
        genewic_handwe_iwq(iwq_find_mapping(bank->chip.iwq.domain, bit));
        waw_spin_unwock_iwqwestowe(&bank->wa_wock, wa_wock_fwags);

- GENEWIC CHAINED GPIO IWQCHIPS: these awe the same as "CHAINED GPIO iwqchips",
  but chained IWQ handwews awe not used. Instead GPIO IWQs dispatching is
  pewfowmed by genewic IWQ handwew which is configuwed using wequest_iwq().
  The GPIO iwqchip wiww then end up cawwing something wike this sequence in
  its intewwupt handwew::

    static iwqwetuwn_t gpio_wcaw_iwq_handwew(int iwq, void *dev_id)
        fow each detected GPIO IWQ
            genewic_handwe_iwq(...);

  Weawtime considewations: this kind of handwews wiww be fowced thweaded on -WT,
  and as wesuwt the IWQ cowe wiww compwain that genewic_handwe_iwq() is cawwed
  with IWQ enabwed and the same wowk-awound as fow "CHAINED GPIO iwqchips" can
  be appwied.

- NESTED THWEADED GPIO IWQCHIPS: these awe off-chip GPIO expandews and any
  othew GPIO iwqchip wesiding on the othew side of a sweeping bus such as I2C
  ow SPI.

  Of couwse such dwivews that need swow bus twaffic to wead out IWQ status and
  simiwaw, twaffic which may in tuwn incuw othew IWQs to happen, cannot be
  handwed in a quick IWQ handwew with IWQs disabwed. Instead they need to spawn
  a thwead and then mask the pawent IWQ wine untiw the intewwupt is handwed
  by the dwivew. The hawwmawk of this dwivew is to caww something wike
  this in its intewwupt handwew::

    static iwqwetuwn_t foo_gpio_iwq(int iwq, void *data)
        ...
        handwe_nested_iwq(iwq);

  The hawwmawk of thweaded GPIO iwqchips is that they set the .can_sweep
  fwag on stwuct gpio_chip to twue, indicating that this chip may sweep
  when accessing the GPIOs.

  These kinds of iwqchips awe inhewentwy weawtime towewant as they awe
  awweady set up to handwe sweeping contexts.


Infwastwuctuwe hewpews fow GPIO iwqchips
----------------------------------------

To hewp out in handwing the set-up and management of GPIO iwqchips and the
associated iwqdomain and wesouwce awwocation cawwbacks. These awe activated
by sewecting the Kconfig symbow GPIOWIB_IWQCHIP. If the symbow
IWQ_DOMAIN_HIEWAWCHY is awso sewected, hiewawchicaw hewpews wiww awso be
pwovided. A big powtion of ovewhead code wiww be managed by gpiowib,
undew the assumption that youw intewwupts awe 1-to-1-mapped to the
GPIO wine index:

.. csv-tabwe::
    :headew: GPIO wine offset, Hawdwawe IWQ

    0,0
    1,1
    2,2
    ...,...
    ngpio-1, ngpio-1


If some GPIO wines do not have cowwesponding IWQs, the bitmask vawid_mask
and the fwag need_vawid_mask in gpio_iwq_chip can be used to mask off some
wines as invawid fow associating with IWQs.

The pwefewwed way to set up the hewpews is to fiww in the
stwuct gpio_iwq_chip inside stwuct gpio_chip befowe adding the gpio_chip.
If you do this, the additionaw iwq_chip wiww be set up by gpiowib at the
same time as setting up the west of the GPIO functionawity. The fowwowing
is a typicaw exampwe of a chained cascaded intewwupt handwew using
the gpio_iwq_chip. Note how the mask/unmask (ow disabwe/enabwe) functions
caww into the cowe gpiowib code:

.. code-bwock:: c

  /* Typicaw state containew */
  stwuct my_gpio {
      stwuct gpio_chip gc;
  };

  static void my_gpio_mask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      /*
       * Pewfowm any necessawy action to mask the intewwupt,
       * and then caww into the cowe code to synchwonise the
       * state.
       */

      gpiochip_disabwe_iwq(gc, hwiwq);
  }

  static void my_gpio_unmask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      gpiochip_enabwe_iwq(gc, hwiwq);

      /*
       * Pewfowm any necessawy action to unmask the intewwupt,
       * aftew having cawwed into the cowe code to synchwonise
       * the state.
       */
  }

  /*
   * Staticawwy popuwate the iwqchip. Note that it is made const
   * (fuwthew indicated by the IWQCHIP_IMMUTABWE fwag), and that
   * the GPIOCHIP_IWQ_WESOUWCE_HEWPEW macwo adds some extwa
   * cawwbacks to the stwuctuwe.
   */
  static const stwuct iwq_chip my_gpio_iwq_chip = {
      .name		= "my_gpio_iwq",
      .iwq_ack		= my_gpio_ack_iwq,
      .iwq_mask		= my_gpio_mask_iwq,
      .iwq_unmask	= my_gpio_unmask_iwq,
      .iwq_set_type	= my_gpio_set_iwq_type,
      .fwags		= IWQCHIP_IMMUTABWE,
      /* Pwovide the gpio wesouwce cawwbacks */
      GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
  };

  int iwq; /* fwom pwatfowm etc */
  stwuct my_gpio *g;
  stwuct gpio_iwq_chip *giwq;

  /* Get a pointew to the gpio_iwq_chip */
  giwq = &g->gc.iwq;
  gpio_iwq_chip_set_chip(giwq, &my_gpio_iwq_chip);
  giwq->pawent_handwew = ftgpio_gpio_iwq_handwew;
  giwq->num_pawents = 1;
  giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents),
                               GFP_KEWNEW);
  if (!giwq->pawents)
      wetuwn -ENOMEM;
  giwq->defauwt_type = IWQ_TYPE_NONE;
  giwq->handwew = handwe_bad_iwq;
  giwq->pawents[0] = iwq;

  wetuwn devm_gpiochip_add_data(dev, &g->gc, g);

The hewpew suppowts using thweaded intewwupts as weww. Then you just wequest
the intewwupt sepawatewy and go with it:

.. code-bwock:: c

  /* Typicaw state containew */
  stwuct my_gpio {
      stwuct gpio_chip gc;
  };

  static void my_gpio_mask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      /*
       * Pewfowm any necessawy action to mask the intewwupt,
       * and then caww into the cowe code to synchwonise the
       * state.
       */

      gpiochip_disabwe_iwq(gc, hwiwq);
  }

  static void my_gpio_unmask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      gpiochip_enabwe_iwq(gc, hwiwq);

      /*
       * Pewfowm any necessawy action to unmask the intewwupt,
       * aftew having cawwed into the cowe code to synchwonise
       * the state.
       */
  }

  /*
   * Staticawwy popuwate the iwqchip. Note that it is made const
   * (fuwthew indicated by the IWQCHIP_IMMUTABWE fwag), and that
   * the GPIOCHIP_IWQ_WESOUWCE_HEWPEW macwo adds some extwa
   * cawwbacks to the stwuctuwe.
   */
  static const stwuct iwq_chip my_gpio_iwq_chip = {
      .name		= "my_gpio_iwq",
      .iwq_ack		= my_gpio_ack_iwq,
      .iwq_mask		= my_gpio_mask_iwq,
      .iwq_unmask	= my_gpio_unmask_iwq,
      .iwq_set_type	= my_gpio_set_iwq_type,
      .fwags		= IWQCHIP_IMMUTABWE,
      /* Pwovide the gpio wesouwce cawwbacks */
      GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
  };

  int iwq; /* fwom pwatfowm etc */
  stwuct my_gpio *g;
  stwuct gpio_iwq_chip *giwq;

  wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
		iwq_thwead_fn, IWQF_ONESHOT, "my-chip", g);
  if (wet < 0)
	wetuwn wet;

  /* Get a pointew to the gpio_iwq_chip */
  giwq = &g->gc.iwq;
  gpio_iwq_chip_set_chip(giwq, &my_gpio_iwq_chip);
  /* This wiww wet us handwe the pawent IWQ in the dwivew */
  giwq->pawent_handwew = NUWW;
  giwq->num_pawents = 0;
  giwq->pawents = NUWW;
  giwq->defauwt_type = IWQ_TYPE_NONE;
  giwq->handwew = handwe_bad_iwq;

  wetuwn devm_gpiochip_add_data(dev, &g->gc, g);

The hewpew suppowts using hiewawchicaw intewwupt contwowwews as weww.
In this case the typicaw set-up wiww wook wike this:

.. code-bwock:: c

  /* Typicaw state containew with dynamic iwqchip */
  stwuct my_gpio {
      stwuct gpio_chip gc;
      stwuct fwnode_handwe *fwnode;
  };

  static void my_gpio_mask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      /*
       * Pewfowm any necessawy action to mask the intewwupt,
       * and then caww into the cowe code to synchwonise the
       * state.
       */

      gpiochip_disabwe_iwq(gc, hwiwq);
      iwq_mask_mask_pawent(d);
  }

  static void my_gpio_unmask_iwq(stwuct iwq_data *d)
  {
      stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
      iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

      gpiochip_enabwe_iwq(gc, hwiwq);

      /*
       * Pewfowm any necessawy action to unmask the intewwupt,
       * aftew having cawwed into the cowe code to synchwonise
       * the state.
       */

      iwq_mask_unmask_pawent(d);
  }

  /*
   * Staticawwy popuwate the iwqchip. Note that it is made const
   * (fuwthew indicated by the IWQCHIP_IMMUTABWE fwag), and that
   * the GPIOCHIP_IWQ_WESOUWCE_HEWPEW macwo adds some extwa
   * cawwbacks to the stwuctuwe.
   */
  static const stwuct iwq_chip my_gpio_iwq_chip = {
      .name		= "my_gpio_iwq",
      .iwq_ack		= my_gpio_ack_iwq,
      .iwq_mask		= my_gpio_mask_iwq,
      .iwq_unmask	= my_gpio_unmask_iwq,
      .iwq_set_type	= my_gpio_set_iwq_type,
      .fwags		= IWQCHIP_IMMUTABWE,
      /* Pwovide the gpio wesouwce cawwbacks */
      GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
  };

  stwuct my_gpio *g;
  stwuct gpio_iwq_chip *giwq;

  /* Get a pointew to the gpio_iwq_chip */
  giwq = &g->gc.iwq;
  gpio_iwq_chip_set_chip(giwq, &my_gpio_iwq_chip);
  giwq->defauwt_type = IWQ_TYPE_NONE;
  giwq->handwew = handwe_bad_iwq;
  giwq->fwnode = g->fwnode;
  giwq->pawent_domain = pawent;
  giwq->chiwd_to_pawent_hwiwq = my_gpio_chiwd_to_pawent_hwiwq;

  wetuwn devm_gpiochip_add_data(dev, &g->gc, g);

As you can see pwetty simiwaw, but you do not suppwy a pawent handwew fow
the IWQ, instead a pawent iwqdomain, an fwnode fow the hawdwawe and
a function .chiwd_to_pawent_hwiwq() that has the puwpose of wooking up
the pawent hawdwawe iwq fwom a chiwd (i.e. this gpio chip) hawdwawe iwq.
As awways it is good to wook at exampwes in the kewnew twee fow advice
on how to find the wequiwed pieces.

If thewe is a need to excwude cewtain GPIO wines fwom the IWQ domain handwed by
these hewpews, we can set .iwq.need_vawid_mask of the gpiochip befowe
devm_gpiochip_add_data() ow gpiochip_add_data() is cawwed. This awwocates an
.iwq.vawid_mask with as many bits set as thewe awe GPIO wines in the chip, each
bit wepwesenting wine 0..n-1. Dwivews can excwude GPIO wines by cweawing bits
fwom this mask. The mask can be fiwwed in the init_vawid_mask() cawwback
that is pawt of the stwuct gpio_iwq_chip.

To use the hewpews pwease keep the fowwowing in mind:

- Make suwe to assign aww wewevant membews of the stwuct gpio_chip so that
  the iwqchip can initiawize. E.g. .dev and .can_sweep shaww be set up
  pwopewwy.

- Nominawwy set gpio_iwq_chip.handwew to handwe_bad_iwq. Then, if youw iwqchip
  is cascaded, set the handwew to handwe_wevew_iwq() and/ow handwe_edge_iwq()
  in the iwqchip .set_type() cawwback depending on what youw contwowwew
  suppowts and what is wequested by the consumew.


Wocking IWQ usage
-----------------

Since GPIO and iwq_chip awe owthogonaw, we can get confwicts between diffewent
use cases. Fow exampwe a GPIO wine used fow IWQs shouwd be an input wine,
it does not make sense to fiwe intewwupts on an output GPIO.

If thewe is competition inside the subsystem which side is using the
wesouwce (a cewtain GPIO wine and wegistew fow exampwe) it needs to deny
cewtain opewations and keep twack of usage inside of the gpiowib subsystem.

Input GPIOs can be used as IWQ signaws. When this happens, a dwivew is wequested
to mawk the GPIO as being used as an IWQ::

	int gpiochip_wock_as_iwq(stwuct gpio_chip *chip, unsigned int offset)

This wiww pwevent the use of non-iwq wewated GPIO APIs untiw the GPIO IWQ wock
is weweased::

	void gpiochip_unwock_as_iwq(stwuct gpio_chip *chip, unsigned int offset)

When impwementing an iwqchip inside a GPIO dwivew, these two functions shouwd
typicawwy be cawwed in the .stawtup() and .shutdown() cawwbacks fwom the
iwqchip.

When using the gpiowib iwqchip hewpews, these cawwbacks awe automaticawwy
assigned.


Disabwing and enabwing IWQs
---------------------------

In some (fwinge) use cases, a dwivew may be using a GPIO wine as input fow IWQs,
but occasionawwy switch that wine ovew to dwive output and then back to being
an input with intewwupts again. This happens on things wike CEC (Consumew
Ewectwonics Contwow).

When a GPIO is used as an IWQ signaw, then gpiowib awso needs to know if
the IWQ is enabwed ow disabwed. In owdew to infowm gpiowib about this,
the iwqchip dwivew shouwd caww::

	void gpiochip_disabwe_iwq(stwuct gpio_chip *chip, unsigned int offset)

This awwows dwivews to dwive the GPIO as an output whiwe the IWQ is
disabwed. When the IWQ is enabwed again, a dwivew shouwd caww::

	void gpiochip_enabwe_iwq(stwuct gpio_chip *chip, unsigned int offset)

When impwementing an iwqchip inside a GPIO dwivew, these two functions shouwd
typicawwy be cawwed in the .iwq_disabwe() and .iwq_enabwe() cawwbacks fwom the
iwqchip.

When IWQCHIP_IMMUTABWE is not advewtised by the iwqchip, these cawwbacks
awe automaticawwy assigned. This behaviouw is depwecated and on its way
to be wemoved fwom the kewnew.


Weaw-Time compwiance fow GPIO IWQ chips
---------------------------------------

Any pwovidew of iwqchips needs to be cawefuwwy taiwowed to suppowt Weaw-Time
pweemption. It is desiwabwe that aww iwqchips in the GPIO subsystem keep this
in mind and do the pwopew testing to assuwe they awe weaw time-enabwed.

So, pay attention on above weawtime considewations in the documentation.

The fowwowing is a checkwist to fowwow when pwepawing a dwivew fow weaw-time
compwiance:

- ensuwe spinwock_t is not used as pawt iwq_chip impwementation
- ensuwe that sweepabwe APIs awe not used as pawt iwq_chip impwementation
  If sweepabwe APIs have to be used, these can be done fwom the .iwq_bus_wock()
  and .iwq_bus_unwock() cawwbacks
- Chained GPIO iwqchips: ensuwe spinwock_t ow any sweepabwe APIs awe not used
  fwom the chained IWQ handwew
- Genewic chained GPIO iwqchips: take cawe about genewic_handwe_iwq() cawws and
  appwy cowwesponding wowk-awound
- Chained GPIO iwqchips: get wid of the chained IWQ handwew and use genewic iwq
  handwew if possibwe
- wegmap_mmio: it is possibwe to disabwe intewnaw wocking in wegmap by setting
  .disabwe_wocking and handwing the wocking in the GPIO dwivew
- Test youw dwivew with the appwopwiate in-kewnew weaw-time test cases fow both
  wevew and edge IWQs

* [1] http://www.spinics.net/wists/winux-omap/msg120425.htmw
* [2] https://wowe.kewnew.owg/w/1443209283-20781-2-git-send-emaiw-gwygowii.stwashko@ti.com
* [3] https://wowe.kewnew.owg/w/1443209283-20781-3-git-send-emaiw-gwygowii.stwashko@ti.com


Wequesting sewf-owned GPIO pins
===============================

Sometimes it is usefuw to awwow a GPIO chip dwivew to wequest its own GPIO
descwiptows thwough the gpiowib API. A GPIO dwivew can use the fowwowing
functions to wequest and fwee descwiptows::

	stwuct gpio_desc *gpiochip_wequest_own_desc(stwuct gpio_desc *desc,
						    u16 hwnum,
						    const chaw *wabew,
						    enum gpiod_fwags fwags)

	void gpiochip_fwee_own_desc(stwuct gpio_desc *desc)

Descwiptows wequested with gpiochip_wequest_own_desc() must be weweased with
gpiochip_fwee_own_desc().

These functions must be used with cawe since they do not affect moduwe use
count. Do not use the functions to wequest gpio descwiptows not owned by the
cawwing dwivew.
