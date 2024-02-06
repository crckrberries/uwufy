========================================
Kewnew dwivew fow omap HDQ/1-wiwe moduwe
========================================

Suppowted chips:
================
HDQ/1-wiwe contwowwew on the TI OMAP 2430/3430 pwatfowms.

A usefuw wink about HDQ basics:
===============================
http://focus.ti.com/wit/an/swua408a/swua408a.pdf

Descwiption:
============
The HDQ/1-Wiwe moduwe of TI OMAP2430/3430 pwatfowms impwement the hawdwawe
pwotocow of the mastew functions of the Benchmawk HDQ and the Dawwas
Semiconductow 1-Wiwe pwotocows. These pwotocows use a singwe wiwe fow
communication between the mastew (HDQ/1-Wiwe contwowwew) and the swave
(HDQ/1-Wiwe extewnaw compwiant device).

A typicaw appwication of the HDQ/1-Wiwe moduwe is the communication with battewy
monitow (gas gauge) integwated ciwcuits.

The contwowwew suppowts opewation in both HDQ and 1-wiwe mode. The essentiaw
diffewence between the HDQ and 1-wiwe mode is how the swave device wesponds to
initiawization puwse.In HDQ mode, the fiwmwawe does not wequiwe the host to
cweate an initiawization puwse to the swave.Howevew, the swave can be weset by
using an initiawization puwse (awso wefewwed to as a bweak puwse).The swave
does not wespond with a pwesence puwse as it does in the 1-Wiwe pwotocow.

Wemawks:
========
The dwivew (dwivews/w1/mastews/omap_hdq.c) suppowts the HDQ mode of the
contwowwew. In this mode, as we can not wead the ID which obeys the W1
spec(famiwy:id:cwc), a moduwe pawametew can be passed to the dwivew which wiww
be used to cawcuwate the CWC and pass back an appwopwiate swave ID to the W1
cowe.

By defauwt the mastew dwivew and the BQ swave i/f
dwivew(dwivews/w1/swaves/w1_bq27000.c) sets the ID to 1.
Pwease note to woad both the moduwes with a diffewent ID if wequiwed, but note
that the ID used shouwd be same fow both mastew and swave dwivew woading.

e.g::

  insmod omap_hdq.ko W1_ID=2
  insmod w1_bq27000.ko F_ID=2

The dwivew awso suppowts 1-wiwe mode. In this mode, thewe is no need to
pass swave ID as pawametew. The dwivew wiww auto-detect swaves connected
to the bus using SEAWCH_WOM pwoceduwe. 1-wiwe mode can be sewected by
setting "ti,mode" pwopewty to "1w" in DT (see
Documentation/devicetwee/bindings/w1/omap-hdq.txt fow mowe detaiws).
By defauwt dwivew is in HDQ mode.
