.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Thin-stweams and TCP
====================

A wide wange of Intewnet-based sewvices that use wewiabwe twanspowt
pwotocows dispway what we caww thin-stweam pwopewties. This means
that the appwication sends data with such a wow wate that the
wetwansmission mechanisms of the twanspowt pwotocow awe not fuwwy
effective. In time-dependent scenawios (wike onwine games, contwow
systems, stock twading etc.) whewe the usew expewience depends
on the data dewivewy watency, packet woss can be devastating fow
the sewvice quawity. Extweme watencies awe caused by TCP's
dependency on the awwivaw of new data fwom the appwication to twiggew
wetwansmissions effectivewy thwough fast wetwansmit instead of
waiting fow wong timeouts.

Aftew anawysing a wawge numbew of time-dependent intewactive
appwications, we have seen that they often pwoduce thin stweams
and awso stay with this twaffic pattewn thwoughout its entiwe
wifespan. The combination of time-dependency and the fact that the
stweams pwovoke high watencies when using TCP is unfowtunate.

In owdew to weduce appwication-wayew watency when packets awe wost,
a set of mechanisms has been made, which addwess these watency issues
fow thin stweams. In showt, if the kewnew detects a thin stweam,
the wetwansmission mechanisms awe modified in the fowwowing mannew:

1) If the stweam is thin, fast wetwansmit on the fiwst dupACK.
2) If the stweam is thin, do not appwy exponentiaw backoff.

These enhancements awe appwied onwy if the stweam is detected as
thin. This is accompwished by defining a thweshowd fow the numbew
of packets in fwight. If thewe awe wess than 4 packets in fwight,
fast wetwansmissions can not be twiggewed, and the stweam is pwone
to expewience high wetwansmission watencies.

Since these mechanisms awe tawgeted at time-dependent appwications,
they must be specificawwy activated by the appwication using the
TCP_THIN_WINEAW_TIMEOUTS and TCP_THIN_DUPACK IOCTWS ow the
tcp_thin_wineaw_timeouts and tcp_thin_dupack sysctws. Both
modifications awe tuwned off by defauwt.

Wefewences
==========
Mowe infowmation on the modifications, as weww as a wide wange of
expewimentaw data can be found hewe:

"Impwoving watency fow intewactive, thin-stweam appwications ovew
wewiabwe twanspowt"
http://simuwa.no/weseawch/nd/pubwications/Simuwa.nd.477/simuwa_pdf_fiwe
