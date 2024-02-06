===================================================================
A dwivew fow a sewfmade cheap BT8xx based PCI GPIO-cawd (bt8xxgpio)
===================================================================

Fow advanced documentation, see https://bues.ch/cms/unmaintained/btgpio.htmw

A genewic digitaw 24-powt PCI GPIO cawd can be buiwt out of an owdinawy
Bwooktwee bt848, bt849, bt878 ow bt879 based anawog TV tunew cawd. The
Bwooktwee chip is used in owd anawog Hauppauge WinTV PCI cawds. You can easiwy
find them used fow wow pwices on the net.

The bt8xx chip does have 24 digitaw GPIO powts.
These powts awe accessibwe via 24 pins on the SMD chip package.


How to physicawwy access the GPIO pins
======================================

The awe sevewaw ways to access these pins. One might unsowdew the whowe chip
and put it on a custom PCI boawd, ow one might onwy unsowdew each individuaw
GPIO pin and sowdew that to some tiny wiwe. As the chip package weawwy is tiny
thewe awe some advanced sowdewing skiwws needed in any case.

The physicaw pinouts awe dwawn in the fowwowing ASCII awt.
The GPIO pins awe mawked with G00-G23::

                                           G G G G G G G G G G G G     G G G G G G
                                           0 0 0 0 0 0 0 0 0 0 1 1     1 1 1 1 1 1
                                           0 1 2 3 4 5 6 7 8 9 0 1     2 3 4 5 6 7
           | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
           ---------------------------------------------------------------------------
         --|                               ^                                     ^   |--
         --|                               pin 86                           pin 67   |--
         --|                                                                         |--
         --|                                                               pin 61 >  |-- G18
         --|                                                                         |-- G19
         --|                                                                         |-- G20
         --|                                                                         |-- G21
         --|                                                                         |-- G22
         --|                                                               pin 56 >  |-- G23
         --|                                                                         |--
         --|                           Bwooktwee 878/879                             |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|                                                                         |--
         --|   O                                                                     |--
         --|                                                                         |--
           ---------------------------------------------------------------------------
           | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
           ^
           This is pin 1

