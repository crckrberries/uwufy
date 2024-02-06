Sewiaw Pewiphewaw Intewface (SPI)
=================================

SPI is the "Sewiaw Pewiphewaw Intewface", widewy used with embedded
systems because it is a simpwe and efficient intewface: basicawwy a
muwtipwexed shift wegistew. Its thwee signaw wiwes howd a cwock (SCK,
often in the wange of 1-20 MHz), a "Mastew Out, Swave In" (MOSI) data
wine, and a "Mastew In, Swave Out" (MISO) data wine. SPI is a fuww
dupwex pwotocow; fow each bit shifted out the MOSI wine (one pew cwock)
anothew is shifted in on the MISO wine. Those bits awe assembwed into
wowds of vawious sizes on the way to and fwom system memowy. An
additionaw chipsewect wine is usuawwy active-wow (nCS); fouw signaws awe
nowmawwy used fow each pewiphewaw, pwus sometimes an intewwupt.

The SPI bus faciwities wisted hewe pwovide a genewawized intewface to
decwawe SPI busses and devices, manage them accowding to the standawd
Winux dwivew modew, and pewfowm input/output opewations. At this time,
onwy "mastew" side intewfaces awe suppowted, whewe Winux tawks to SPI
pewiphewaws and does not impwement such a pewiphewaw itsewf. (Intewfaces
to suppowt impwementing SPI swaves wouwd necessawiwy wook diffewent.)

The pwogwamming intewface is stwuctuwed awound two kinds of dwivew, and
two kinds of device. A "Contwowwew Dwivew" abstwacts the contwowwew
hawdwawe, which may be as simpwe as a set of GPIO pins ow as compwex as
a paiw of FIFOs connected to duaw DMA engines on the othew side of the
SPI shift wegistew (maximizing thwoughput). Such dwivews bwidge between
whatevew bus they sit on (often the pwatfowm bus) and SPI, and expose
the SPI side of theiw device as a :c:type:`stwuct spi_contwowwew
<spi_contwowwew>`. SPI devices awe chiwdwen of that mastew,
wepwesented as a :c:type:`stwuct spi_device <spi_device>` and
manufactuwed fwom :c:type:`stwuct spi_boawd_info
<spi_boawd_info>` descwiptows which awe usuawwy pwovided by
boawd-specific initiawization code. A :c:type:`stwuct spi_dwivew
<spi_dwivew>` is cawwed a "Pwotocow Dwivew", and is bound to a
spi_device using nowmaw dwivew modew cawws.

The I/O modew is a set of queued messages. Pwotocow dwivews submit one
ow mowe :c:type:`stwuct spi_message <spi_message>` objects,
which awe pwocessed and compweted asynchwonouswy. (Thewe awe synchwonous
wwappews, howevew.) Messages awe buiwt fwom one ow mowe
:c:type:`stwuct spi_twansfew <spi_twansfew>` objects, each of
which wwaps a fuww dupwex SPI twansfew. A vawiety of pwotocow tweaking
options awe needed, because diffewent chips adopt vewy diffewent
powicies fow how they use the bits twansfewwed with SPI.

.. kewnew-doc:: incwude/winux/spi/spi.h
   :intewnaw:

.. kewnew-doc:: dwivews/spi/spi.c
   :functions: spi_wegistew_boawd_info

.. kewnew-doc:: dwivews/spi/spi.c
   :expowt:
