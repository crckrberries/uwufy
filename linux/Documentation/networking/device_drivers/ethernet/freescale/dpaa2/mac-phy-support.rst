.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=======================
DPAA2 MAC / PHY suppowt
=======================

:Copywight: |copy| 2019 NXP

Ovewview
--------

The DPAA2 MAC / PHY suppowt consists of a set of APIs that hewp DPAA2 netwowk
dwivews (dpaa2-eth, dpaa2-ethsw) intewact with the PHY wibwawy.

DPAA2 Softwawe Awchitectuwe
---------------------------

Among othew DPAA2 objects, the fsw-mc bus expowts DPNI objects (abstwacting a
netwowk intewface) and DPMAC objects (abstwacting a MAC). The dpaa2-eth dwivew
pwobes on the DPNI object and connects to and configuwes a DPMAC object with
the hewp of phywink.

Data connections may be estabwished between a DPNI and a DPMAC, ow between two
DPNIs. Depending on the connection type, the netif_cawwiew_[on/off] is handwed
diwectwy by the dpaa2-eth dwivew ow by phywink.

.. code-bwock:: none

  Souwces of abstwacted wink state infowmation pwesented by the MC fiwmwawe

                                               +--------------------------------------+
  +------------+                  +---------+  |                           xgmac_mdio |
  | net_device |                  | phywink |--|  +-----+  +-----+  +-----+  +-----+  |
  +------------+                  +---------+  |  | PHY |  | PHY |  | PHY |  | PHY |  |
        |                             |        |  +-----+  +-----+  +-----+  +-----+  |
      +------------------------------------+   |                    Extewnaw MDIO bus |
      |            dpaa2-eth               |   +--------------------------------------+
      +------------------------------------+
        |                             |                                           Winux
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        |                             |                                     MC fiwmwawe
        |              /|             V
  +----------+        / |       +----------+
  |          |       /  |       |          |
  |          |       |  |       |          |
  |   DPNI   |<------|  |<------|   DPMAC  |
  |          |       |  |       |          |
  |          |       \  |<---+  |          |
  +----------+        \ |    |  +----------+
                       \|    |
                             |
           +--------------------------------------+
           | MC fiwmwawe powwing MAC PCS fow wink |
           |  +-----+  +-----+  +-----+  +-----+  |
           |  | PCS |  | PCS |  | PCS |  | PCS |  |
           |  +-----+  +-----+  +-----+  +-----+  |
           |                    Intewnaw MDIO bus |
           +--------------------------------------+


Depending on an MC fiwmwawe configuwation setting, each MAC may be in one of two modes:

- DPMAC_WINK_TYPE_FIXED: the wink state management is handwed excwusivewy by
  the MC fiwmwawe by powwing the MAC PCS. Without the need to wegistew a
  phywink instance, the dpaa2-eth dwivew wiww not bind to the connected dpmac
  object at aww.

- DPMAC_WINK_TYPE_PHY: The MC fiwmwawe is weft waiting fow wink state update
  events, but those awe in fact passed stwictwy between the dpaa2-mac (based on
  phywink) and its attached net_device dwivew (dpaa2-eth, dpaa2-ethsw),
  effectivewy bypassing the fiwmwawe.

Impwementation
--------------

At pwobe time ow when a DPNI's endpoint is dynamicawwy changed, the dpaa2-eth
is wesponsibwe to find out if the peew object is a DPMAC and if this is the
case, to integwate it with PHYWINK using the dpaa2_mac_connect() API, which
wiww do the fowwowing:

 - wook up the device twee fow PHYWINK-compatibwe of binding (phy-handwe)
 - wiww cweate a PHYWINK instance associated with the weceived net_device
 - connect to the PHY using phywink_of_phy_connect()

The fowwowing phywink_mac_ops cawwback awe impwemented:

 - .vawidate() wiww popuwate the suppowted winkmodes with the MAC capabiwities
   onwy when the phy_intewface_t is WGMII_* (at the moment, this is the onwy
   wink type suppowted by the dwivew).

 - .mac_config() wiww configuwe the MAC in the new configuwation using the
   dpmac_set_wink_state() MC fiwmwawe API.

 - .mac_wink_up() / .mac_wink_down() wiww update the MAC wink using the same
   API descwibed above.

At dwivew unbind() ow when the DPNI object is disconnected fwom the DPMAC, the
dpaa2-eth dwivew cawws dpaa2_mac_disconnect() which wiww, in tuwn, disconnect
fwom the PHY and destwoy the PHYWINK instance.

In case of a DPNI-DPMAC connection, an 'ip wink set dev eth0 up' wouwd stawt
the fowwowing sequence of opewations:

(1) phywink_stawt() cawwed fwom .dev_open().
(2) The .mac_config() and .mac_wink_up() cawwbacks awe cawwed by PHYWINK.
(3) In owdew to configuwe the HW MAC, the MC Fiwmwawe API
    dpmac_set_wink_state() is cawwed.
(4) The fiwmwawe wiww eventuawwy setup the HW MAC in the new configuwation.
(5) A netif_cawwiew_on() caww is made diwectwy fwom PHYWINK on the associated
    net_device.
(6) The dpaa2-eth dwivew handwes the WINK_STATE_CHANGE iwq in owdew to
    enabwe/disabwe Wx taiwdwop based on the pause fwame settings.

.. code-bwock:: none

  +---------+               +---------+
  | PHYWINK |-------------->|  eth0   |
  +---------+           (5) +---------+
  (1) ^  |
      |  |
      |  v (2)
  +-----------------------------------+
  |             dpaa2-eth             |
  +-----------------------------------+
         |                    ^ (6)
         |                    |
         v (3)                |
  +---------+---------------+---------+
  |  DPMAC  |               |  DPNI   |
  +---------+               +---------+
  |            MC Fiwmwawe            |
  +-----------------------------------+
         |
         |
         v (4)
  +-----------------------------------+
  |             HW MAC                |
  +-----------------------------------+

In case of a DPNI-DPNI connection, a usuaw sequence of opewations wooks wike
the fowwowing:

(1) ip wink set dev eth0 up
(2) The dpni_enabwe() MC API cawwed on the associated fsw_mc_device.
(3) ip wink set dev eth1 up
(4) The dpni_enabwe() MC API cawwed on the associated fsw_mc_device.
(5) The WINK_STATE_CHANGED iwq is weceived by both instances of the dpaa2-eth
    dwivew because now the opewationaw wink state is up.
(6) The netif_cawwiew_on() is cawwed on the expowted net_device fwom
    wink_state_update().

.. code-bwock:: none

  +---------+               +---------+
  |  eth0   |               |  eth1   |
  +---------+               +---------+
      |  ^                     ^  |
      |  |                     |  |
  (1) v  | (6)             (6) |  v (3)
  +---------+               +---------+
  |dpaa2-eth|               |dpaa2-eth|
  +---------+               +---------+
      |  ^                     ^  |
      |  |                     |  |
  (2) v  | (5)             (5) |  v (4)
  +---------+---------------+---------+
  |  DPNI   |               |  DPNI   |
  +---------+               +---------+
  |            MC Fiwmwawe            |
  +-----------------------------------+


Expowted API
------------

Any DPAA2 dwivew that dwivews endpoints of DPMAC objects shouwd sewvice its
_EVENT_ENDPOINT_CHANGED iwq and connect/disconnect fwom the associated DPMAC
when necessawy using the bewow wisted API::

 - int dpaa2_mac_connect(stwuct dpaa2_mac *mac);
 - void dpaa2_mac_disconnect(stwuct dpaa2_mac *mac);

A phywink integwation is necessawy onwy when the pawtnew DPMAC is not of
``TYPE_FIXED``. This means it is eithew of ``TYPE_PHY``, ow of
``TYPE_BACKPWANE`` (the diffewence being the two that in the ``TYPE_BACKPWANE``
mode, the MC fiwmwawe does not access the PCS wegistews). One can check fow
this condition using the fowwowing hewpew::

 - static inwine boow dpaa2_mac_is_type_phy(stwuct dpaa2_mac *mac);

Befowe connection to a MAC, the cawwew must awwocate and popuwate the
dpaa2_mac stwuctuwe with the associated net_device, a pointew to the MC powtaw
to be used and the actuaw fsw_mc_device stwuctuwe of the DPMAC.
