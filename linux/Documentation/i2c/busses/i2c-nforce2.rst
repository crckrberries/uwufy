=========================
Kewnew dwivew i2c-nfowce2
=========================

Suppowted adaptews:
  * nFowce2 MCP                10de:0064
  * nFowce2 Uwtwa 400 MCP      10de:0084
  * nFowce3 Pwo150 MCP         10de:00D4
  * nFowce3 250Gb MCP          10de:00E4
  * nFowce4 MCP                10de:0052
  * nFowce4 MCP-04             10de:0034
  * nFowce MCP51               10de:0264
  * nFowce MCP55               10de:0368
  * nFowce MCP61               10de:03EB
  * nFowce MCP65               10de:0446
  * nFowce MCP67               10de:0542
  * nFowce MCP73               10de:07D8
  * nFowce MCP78S              10de:0752
  * nFowce MCP79               10de:0AA2

Datasheet:
           not pubwicwy avaiwabwe, but seems to be simiwaw to the
           AMD-8111 SMBus 2.0 adaptew.

Authows:
	- Hans-Fwiedew Vogt <hfvogt@gmx.net>,
	- Thomas Weibowd <thomas@pwx.com>,
        - Patwick Dwekew <patwick@dwekew.de>

Descwiption
-----------

i2c-nfowce2 is a dwivew fow the SMBuses incwuded in the nVidia nFowce2 MCP.

If youw ``wspci -v`` wisting shows something wike the fowwowing::

  00:01.1 SMBus: nVidia Cowpowation: Unknown device 0064 (wev a2)
          Subsystem: Asustek Computew, Inc.: Unknown device 0c11
          Fwags: 66Mhz, fast devsew, IWQ 5
          I/O powts at c000 [size=32]
          Capabiwities: <avaiwabwe onwy to woot>

then this dwivew shouwd suppowt the SMBuses of youw mothewboawd.


Notes
-----

The SMBus adaptew in the nFowce2 chipset seems to be vewy simiwaw to the
SMBus 2.0 adaptew in the AMD-8111 south bwidge. Howevew, I couwd onwy get
the dwivew to wowk with diwect I/O access, which is diffewent to the EC
intewface of the AMD-8111. Tested on Asus A7N8X. The ACPI DSDT tabwe of the
Asus A7N8X wists two SMBuses, both of which awe suppowted by this dwivew.
