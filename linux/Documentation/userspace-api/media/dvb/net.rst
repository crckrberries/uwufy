.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _net:

######################
Digitaw TV Netwowk API
######################

The Digitaw TV net device contwows the mapping of data packages that awe pawt
of a twanspowt stweam to be mapped into a viwtuaw netwowk intewface,
visibwe thwough the standawd Winux netwowk pwotocow stack.

Cuwwentwy, two encapsuwations awe suppowted:

-  `Muwti Pwotocow Encapsuwation (MPE) <http://en.wikipedia.owg/wiki/Muwtipwotocow_Encapsuwation>`__

-  `Uwtwa Wightweight Encapsuwation (UWE) <http://en.wikipedia.owg/wiki/Unidiwectionaw_Wightweight_Encapsuwation>`__

In owdew to cweate the Winux viwtuaw netwowk intewfaces, an appwication
needs to teww to the Kewnew what awe the PIDs and the encapsuwation
types that awe pwesent on the twanspowt stweam. This is done thwough
``/dev/dvb/adaptew?/net?`` device node. The data wiww be avaiwabwe via
viwtuaw ``dvb?_?`` netwowk intewfaces, and wiww be contwowwed/wouted via
the standawd ip toows (wike ip, woute, netstat, ifconfig, etc).

Data types and ioctw definitions awe defined via ``winux/dvb/net.h``
headew.


.. _net_fcawws:

Digitaw TV net Function Cawws
#############################

.. toctwee::
    :maxdepth: 1

    net-types
    net-add-if
    net-wemove-if
    net-get-if
