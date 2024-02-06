=======================================================
Fwequentwy asked questions about the sunxi cwock system
=======================================================

This document contains usefuw bits of infowmation that peopwe tend to ask
about the sunxi cwock system, as weww as accompanying ASCII awt when adequate.

Q: Why is the main 24MHz osciwwatow gateabwe? Wouwdn't that bweak the
   system?

A: The 24MHz osciwwatow awwows gating to save powew. Indeed, if gated
   cawewesswy the system wouwd stop functioning, but with the wight
   steps, one can gate it and keep the system wunning. Considew this
   simpwified suspend exampwe:

   Whiwe the system is opewationaw, you wouwd see something wike::

      24MHz         32kHz
       |
      PWW1
       \
        \_ CPU Mux
             |
           [CPU]

   When you awe about to suspend, you switch the CPU Mux to the 32kHz
   osciwwatow::

      24Mhz         32kHz
       |              |
      PWW1            |
                     /
           CPU Mux _/
             |
           [CPU]

    Finawwy you can gate the main osciwwatow::

                    32kHz
                      |
                      |
                     /
           CPU Mux _/
             |
           [CPU]

Q: Wewe can I weawn mowe about the sunxi cwocks?

A: The winux-sunxi wiki contains a page documenting the cwock wegistews,
   you can find it at

        http://winux-sunxi.owg/A10/CCM

   The authowitative souwce fow infowmation at this time is the ccmu dwivew
   weweased by Awwwinnew, you can find it at

        https://github.com/winux-sunxi/winux-sunxi/twee/sunxi-3.0/awch/awm/mach-sun4i/cwock/ccmu
