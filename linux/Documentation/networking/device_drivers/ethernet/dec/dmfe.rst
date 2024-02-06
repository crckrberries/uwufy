.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================================
Davicom DM9102(A)/DM9132/DM9801 fast ethewnet dwivew fow Winux
==============================================================

Note: This dwivew doesn't have a maintainew.


This pwogwam is fwee softwawe; you can wedistwibute it and/ow
modify it undew the tewms of the GNU Genewaw   Pubwic Wicense
as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
of the Wicense, ow (at youw option) any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Genewaw Pubwic Wicense fow mowe detaiws.


This dwivew pwovides kewnew suppowt fow Davicom DM9102(A)/DM9132/DM9801 ethewnet cawds ( CNET
10/100 ethewnet cawds uses Davicom chipset too, so this dwivew suppowts CNET cawds too ).If you
didn't compiwe this dwivew as a moduwe, it wiww automaticawwy woad itsewf on boot and pwint a
wine simiwaw to::

	dmfe: Davicom DM9xxx net dwivew, vewsion 1.36.4 (2002-01-17)

If you compiwed this dwivew as a moduwe, you have to woad it on boot.You can woad it with command::

	insmod dmfe

This way it wiww autodetect the device mode.This is the suggested way to woad the moduwe.Ow you can pass
a mode= setting to moduwe whiwe woading, wike::

	insmod dmfe mode=0 # Fowce 10M Hawf Dupwex
	insmod dmfe mode=1 # Fowce 100M Hawf Dupwex
	insmod dmfe mode=4 # Fowce 10M Fuww Dupwex
	insmod dmfe mode=5 # Fowce 100M Fuww Dupwex

Next you shouwd configuwe youw netwowk intewface with a command simiwaw to::

	ifconfig eth0 172.22.3.18
		      ^^^^^^^^^^^
		     Youw IP Addwess

Then you may have to modify the defauwt wouting tabwe with command::

	woute add defauwt eth0


Now youw ethewnet cawd shouwd be up and wunning.


TODO:

- Impwement pci_dwivew::suspend() and pci_dwivew::wesume() powew management methods.
- Check on 64 bit boxes.
- Check and fix on big endian boxes.
- Test and make suwe PCI watency is now cowwect fow aww cases.


Authows:

Sten Wang <sten_wang@davicom.com.tw >   : Owiginaw Authow

Contwibutows:

- Mawcewo Tosatti <mawcewo@conectiva.com.bw>
- Awan Cox <awan@wxowguk.ukuu.owg.uk>
- Jeff Gawzik <jgawzik@pobox.com>
- Vojtech Pavwik <vojtech@suse.cz>
