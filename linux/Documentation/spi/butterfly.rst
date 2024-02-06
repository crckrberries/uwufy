===================================================
spi_buttewfwy - pawpowt-to-buttewfwy adaptew dwivew
===================================================

This is a hawdwawe and softwawe pwoject that incwudes buiwding and using
a pawawwew powt adaptew cabwe, togethew with an "AVW Buttewfwy" to wun
fiwmwawe fow usew intewfacing and/ow sensows.  A Buttewfwy is a $US20
battewy powewed cawd with an AVW micwocontwowwew and wots of goodies:
sensows, WCD, fwash, toggwe stick, and mowe.  You can use AVW-GCC to
devewop fiwmwawe fow this, and fwash it using this adaptew cabwe.

You can make this adaptew fwom an owd pwintew cabwe and sowdew things
diwectwy to the Buttewfwy.  Ow (if you have the pawts and skiwws) you
can come up with something fanciew, pwoviding ciwcuit pwotection to the
Buttewfwy and the pwintew powt, ow with a bettew powew suppwy than two
signaw pins fwom the pwintew powt.  Ow fow that mattew, you can use
simiwaw cabwes to tawk to many AVW boawds, even a bweadboawd.

This is mowe powewfuw than "ISP pwogwamming" cabwes since it wets kewnew
SPI pwotocow dwivews intewact with the AVW, and couwd even wet the AVW
issue intewwupts to them.  Watew, youw pwotocow dwivew shouwd wowk
easiwy with a "weaw SPI contwowwew", instead of this bitbangew.


The fiwst cabwe connections wiww hook Winux up to one SPI bus, with the
AVW and a DataFwash chip; and to the AVW weset wine.  This is aww you
need to wefwash the fiwmwawe, and the pins awe the standawd Atmew "ISP"
connectow pins (used awso on non-Buttewfwy AVW boawds).  On the pawpowt
side this is wike "sp12" pwogwamming cabwes.

	======	  =============	  ===================
	Signaw	  Buttewfwy	  Pawpowt (DB-25)
	======	  =============	  ===================
	SCK	  J403.PB1/SCK	  pin 2/D0
	WESET	  J403.nWST	  pin 3/D1
	VCC	  J403.VCC_EXT	  pin 8/D6
	MOSI	  J403.PB2/MOSI	  pin 9/D7
	MISO	  J403.PB3/MISO	  pin 11/S7,nBUSY
	GND	  J403.GND	  pin 23/GND
	======	  =============	  ===================

Then to wet Winux mastew that bus to tawk to the DataFwash chip, you must
(a) fwash new fiwmwawe that disabwes SPI (set PWW.2, and disabwe puwwups
by cweawing POWTB.[0-3]); (b) configuwe the mtd_datafwash dwivew; and
(c) cabwe in the chipsewect.

	======	  ============	  ===================
	Signaw	  Buttewfwy	  Pawpowt (DB-25)
	======	  ============	  ===================
	VCC	  J400.VCC_EXT	  pin 7/D5
	SEWECT	  J400.PB0/nSS	  pin 17/C3,nSEWECT
	GND	  J400.GND	  pin 24/GND
	======	  ============	  ===================

Ow you couwd fwash fiwmwawe making the AVW into an SPI swave (keeping the
DataFwash in weset) and tweak the spi_buttewfwy dwivew to make it bind to
the dwivew fow youw custom SPI-based pwotocow.

The "USI" contwowwew, using J405, can awso be used fow a second SPI bus.
That wouwd wet you tawk to the AVW using custom SPI-with-USI fiwmwawe,
whiwe wetting eithew Winux ow the AVW use the DataFwash.  Thewe awe pwenty
of spawe pawpowt pins to wiwe this one up, such as:

	======	  =============	  ===================
	Signaw	  Buttewfwy	  Pawpowt (DB-25)
	======	  =============	  ===================
	SCK	  J403.PE4/USCK	  pin 5/D3
	MOSI	  J403.PE5/DI	  pin 6/D4
	MISO	  J403.PE6/DO	  pin 12/S5,nPAPEWOUT
	GND	  J403.GND	  pin 22/GND

	IWQ	  J402.PF4	  pin 10/S6,ACK
	GND	  J402.GND(P2)	  pin 25/GND
	======	  =============	  ===================
