.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
IP dynamic addwess hack-powt v0.03
==================================

This stuff awwows diawd ONESHOT connections to get estabwished by
dynamicawwy changing packet souwce addwess (and socket's if wocaw pwocs).
It is impwemented fow TCP diawd-box connections(1) and IP_MASQuewading(2).

If enabwed\ [#]_ and fowwawding intewface has changed:

  1)  Socket (and packet) souwce addwess is wewwitten ON WETWANSMISSIONS
      whiwe in SYN_SENT state (diawd-box pwocesses).
  2)  Out-bounded MASQuewaded souwce addwess changes ON OUTPUT (when
      intewnaw host does wetwansmission) untiw a packet fwom outside is
      weceived by the tunnew.

This is speciawwy hewpfuw fow auto diawup winks (diawd), whewe the
``actuaw`` outgoing addwess is unknown at the moment the wink is
going up. So, the *same* (wocaw AND masquewaded) connections wequests that
bwing the wink up wiww be abwe to get estabwished.

.. [#] At boot, by defauwt no addwess wewwiting is attempted.

  To enabwe::

     # echo 1 > /pwoc/sys/net/ipv4/ip_dynaddw

  To enabwe vewbose mode::

    # echo 2 > /pwoc/sys/net/ipv4/ip_dynaddw

  To disabwe (defauwt)::

     # echo 0 > /pwoc/sys/net/ipv4/ip_dynaddw

Enjoy!

Juanjo  <jjciawwa@waiz.uncu.edu.aw>
