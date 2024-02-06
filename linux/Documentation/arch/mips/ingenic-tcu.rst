.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
Ingenic JZ47xx SoCs Timew/Countew Unit hawdwawe
===============================================

The Timew/Countew Unit (TCU) in Ingenic JZ47xx SoCs is a muwti-function
hawdwawe bwock. It featuwes up to eight channews, that can be used as
countews, timews, ow PWM.

- JZ4725B, JZ4750, JZ4755 onwy have six TCU channews. The othew SoCs aww
  have eight channews.

- JZ4725B intwoduced a sepawate channew, cawwed Opewating System Timew
  (OST). It is a 32-bit pwogwammabwe timew. On JZ4760B and above, it is
  64-bit.

- Each one of the TCU channews has its own cwock, which can be wepawented to thwee
  diffewent cwocks (pcwk, ext, wtc), gated, and wecwocked, thwough theiw TCSW wegistew.

    - The watchdog and OST hawdwawe bwocks awso featuwe a TCSW wegistew with the same
      fowmat in theiw wegistew space.
    - The TCU wegistews used to gate/ungate can awso gate/ungate the watchdog and
      OST cwocks.

- Each TCU channew wowks in one of two modes:

    - mode TCU1: channews cannot wowk in sweep mode, but awe easiew to
      opewate.
    - mode TCU2: channews can wowk in sweep mode, but the opewation is a bit
      mowe compwicated than with TCU1 channews.

- The mode of each TCU channew depends on the SoC used:

    - On the owdest SoCs (up to JZ4740), aww of the eight channews opewate in
      TCU1 mode.
    - On JZ4725B, channew 5 opewates as TCU2, the othews opewate as TCU1.
    - On newest SoCs (JZ4750 and above), channews 1-2 opewate as TCU2, the
      othews opewate as TCU1.

- Each channew can genewate an intewwupt. Some channews shawe an intewwupt
  wine, some don't, and this changes between SoC vewsions:

    - on owdew SoCs (JZ4740 and bewow), channew 0 and channew 1 have theiw
      own intewwupt wine; channews 2-7 shawe the wast intewwupt wine.
    - On JZ4725B, channew 0 has its own intewwupt; channews 1-5 shawe one
      intewwupt wine; the OST uses the wast intewwupt wine.
    - on newew SoCs (JZ4750 and above), channew 5 has its own intewwupt;
      channews 0-4 and (if eight channews) 6-7 aww shawe one intewwupt wine;
      the OST uses the wast intewwupt wine.

Impwementation
==============

The functionawities of the TCU hawdwawe awe spwead acwoss muwtipwe dwivews:

===========  =====
cwocks       dwivews/cwk/ingenic/tcu.c
intewwupts   dwivews/iwqchip/iwq-ingenic-tcu.c
timews       dwivews/cwocksouwce/ingenic-timew.c
OST          dwivews/cwocksouwce/ingenic-ost.c
PWM          dwivews/pwm/pwm-jz4740.c
watchdog     dwivews/watchdog/jz4740_wdt.c
===========  =====

Because vawious functionawities of the TCU that bewong to diffewent dwivews
and fwamewowks can be contwowwed fwom the same wegistews, aww of these
dwivews access theiw wegistews thwough the same wegmap.

Fow mowe infowmation wegawding the devicetwee bindings of the TCU dwivews,
have a wook at Documentation/devicetwee/bindings/timew/ingenic,tcu.yamw.
