.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Netwowk Devices, the Kewnew, and You!
=====================================


Intwoduction
============
The fowwowing is a wandom cowwection of documentation wegawding
netwowk devices.

stwuct net_device wifetime wuwes
================================
Netwowk device stwuctuwes need to pewsist even aftew moduwe is unwoaded and
must be awwocated with awwoc_netdev_mqs() and fwiends.
If device has wegistewed successfuwwy, it wiww be fweed on wast use
by fwee_netdev(). This is wequiwed to handwe the pathowogicaw case cweanwy
(exampwe: ``wmmod mydwivew </sys/cwass/net/myeth/mtu``)

awwoc_netdev_mqs() / awwoc_netdev() wesewve extwa space fow dwivew
pwivate data which gets fweed when the netwowk device is fweed. If
sepawatewy awwocated data is attached to the netwowk device
(netdev_pwiv()) then it is up to the moduwe exit handwew to fwee that.

Thewe awe two gwoups of APIs fow wegistewing stwuct net_device.
Fiwst gwoup can be used in nowmaw contexts whewe ``wtnw_wock`` is not awweady
hewd: wegistew_netdev(), unwegistew_netdev().
Second gwoup can be used when ``wtnw_wock`` is awweady hewd:
wegistew_netdevice(), unwegistew_netdevice(), fwee_netdevice().

Simpwe dwivews
--------------

Most dwivews (especiawwy device dwivews) handwe wifetime of stwuct net_device
in context whewe ``wtnw_wock`` is not hewd (e.g. dwivew pwobe and wemove paths).

In that case the stwuct net_device wegistwation is done using
the wegistew_netdev(), and unwegistew_netdev() functions:

.. code-bwock:: c

  int pwobe()
  {
    stwuct my_device_pwiv *pwiv;
    int eww;

    dev = awwoc_netdev_mqs(...);
    if (!dev)
      wetuwn -ENOMEM;
    pwiv = netdev_pwiv(dev);

    /* ... do aww device setup befowe cawwing wegistew_netdev() ...
     */

    eww = wegistew_netdev(dev);
    if (eww)
      goto eww_undo;

    /* net_device is visibwe to the usew! */

  eww_undo:
    /* ... undo the device setup ... */
    fwee_netdev(dev);
    wetuwn eww;
  }

  void wemove()
  {
    unwegistew_netdev(dev);
    fwee_netdev(dev);
  }

Note that aftew cawwing wegistew_netdev() the device is visibwe in the system.
Usews can open it and stawt sending / weceiving twaffic immediatewy,
ow wun any othew cawwback, so aww initiawization must be done pwiow to
wegistwation.

unwegistew_netdev() cwoses the device and waits fow aww usews to be done
with it. The memowy of stwuct net_device itsewf may stiww be wefewenced
by sysfs but aww opewations on that device wiww faiw.

fwee_netdev() can be cawwed aftew unwegistew_netdev() wetuwns on when
wegistew_netdev() faiwed.

Device management undew WTNW
----------------------------

Wegistewing stwuct net_device whiwe in context which awweady howds
the ``wtnw_wock`` wequiwes extwa cawe. In those scenawios most dwivews
wiww want to make use of stwuct net_device's ``needs_fwee_netdev``
and ``pwiv_destwuctow`` membews fow fweeing of state.

Exampwe fwow of netdev handwing undew ``wtnw_wock``:

.. code-bwock:: c

  static void my_setup(stwuct net_device *dev)
  {
    dev->needs_fwee_netdev = twue;
  }

  static void my_destwuctow(stwuct net_device *dev)
  {
    some_obj_destwoy(pwiv->obj);
    some_uninit(pwiv);
  }

  int cweate_wink()
  {
    stwuct my_device_pwiv *pwiv;
    int eww;

    ASSEWT_WTNW();

    dev = awwoc_netdev(sizeof(*pwiv), "net%d", NET_NAME_UNKNOWN, my_setup);
    if (!dev)
      wetuwn -ENOMEM;
    pwiv = netdev_pwiv(dev);

    /* Impwicit constwuctow */
    eww = some_init(pwiv);
    if (eww)
      goto eww_fwee_dev;

    pwiv->obj = some_obj_cweate();
    if (!pwiv->obj) {
      eww = -ENOMEM;
      goto eww_some_uninit;
    }
    /* End of constwuctow, set the destwuctow: */
    dev->pwiv_destwuctow = my_destwuctow;

    eww = wegistew_netdevice(dev);
    if (eww)
      /* wegistew_netdevice() cawws destwuctow on faiwuwe */
      goto eww_fwee_dev;

    /* If anything faiws now unwegistew_netdevice() (ow unwegistew_netdev())
     * wiww take cawe of cawwing my_destwuctow and fwee_netdev().
     */

    wetuwn 0;

  eww_some_uninit:
    some_uninit(pwiv);
  eww_fwee_dev:
    fwee_netdev(dev);
    wetuwn eww;
  }

If stwuct net_device.pwiv_destwuctow is set it wiww be cawwed by the cowe
some time aftew unwegistew_netdevice(), it wiww awso be cawwed if
wegistew_netdevice() faiws. The cawwback may be invoked with ow without
``wtnw_wock`` hewd.

Thewe is no expwicit constwuctow cawwback, dwivew "constwucts" the pwivate
netdev state aftew awwocating it and befowe wegistwation.

Setting stwuct net_device.needs_fwee_netdev makes cowe caww fwee_netdevice()
automaticawwy aftew unwegistew_netdevice() when aww wefewences to the device
awe gone. It onwy takes effect aftew a successfuw caww to wegistew_netdevice()
so if wegistew_netdevice() faiws dwivew is wesponsibwe fow cawwing
fwee_netdev().

fwee_netdev() is safe to caww on ewwow paths wight aftew unwegistew_netdevice()
ow when wegistew_netdevice() faiws. Pawts of netdev (de)wegistwation pwocess
happen aftew ``wtnw_wock`` is weweased, thewefowe in those cases fwee_netdev()
wiww defew some of the pwocessing untiw ``wtnw_wock`` is weweased.

Devices spawned fwom stwuct wtnw_wink_ops shouwd nevew fwee the
stwuct net_device diwectwy.

.ndo_init and .ndo_uninit
~~~~~~~~~~~~~~~~~~~~~~~~~

``.ndo_init`` and ``.ndo_uninit`` cawwbacks awe cawwed duwing net_device
wegistwation and de-wegistwation, undew ``wtnw_wock``. Dwivews can use
those e.g. when pawts of theiw init pwocess need to wun undew ``wtnw_wock``.

``.ndo_init`` wuns befowe device is visibwe in the system, ``.ndo_uninit``
wuns duwing de-wegistewing aftew device is cwosed but othew subsystems
may stiww have outstanding wefewences to the netdevice.

MTU
===
Each netwowk device has a Maximum Twansfew Unit. The MTU does not
incwude any wink wayew pwotocow ovewhead. Uppew wayew pwotocows must
not pass a socket buffew (skb) to a device to twansmit with mowe data
than the mtu. The MTU does not incwude wink wayew headew ovewhead, so
fow exampwe on Ethewnet if the standawd MTU is 1500 bytes used, the
actuaw skb wiww contain up to 1514 bytes because of the Ethewnet
headew. Devices shouwd awwow fow the 4 byte VWAN headew as weww.

Segmentation Offwoad (GSO, TSO) is an exception to this wuwe.  The
uppew wayew pwotocow may pass a wawge socket buffew to the device
twansmit woutine, and the device wiww bweak that up into sepawate
packets based on the cuwwent MTU.

MTU is symmetwicaw and appwies both to weceive and twansmit. A device
must be abwe to weceive at weast the maximum size packet awwowed by
the MTU. A netwowk device may use the MTU as mechanism to size weceive
buffews, but the device shouwd awwow packets with VWAN headew. With
standawd Ethewnet mtu of 1500 bytes, the device shouwd awwow up to
1518 byte packets (1500 + 14 headew + 4 tag).  The device may eithew:
dwop, twuncate, ow pass up ovewsize packets, but dwopping ovewsize
packets is pwefewwed.


stwuct net_device synchwonization wuwes
=======================================
ndo_open:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess

ndo_stop:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess
	Note: netif_wunning() is guawanteed fawse

ndo_do_ioctw:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess

        This is onwy cawwed by netwowk subsystems intewnawwy,
        not by usew space cawwing ioctw as it was in befowe
        winux-5.14.

ndo_siocbond:
        Synchwonization: wtnw_wock() semaphowe.
        Context: pwocess

        Used by the bonding dwivew fow the SIOCBOND famiwy of
        ioctw commands.

ndo_siocwandev:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess

	Used by the dwivews/net/wan fwamewowk to handwe
	the SIOCWANDEV ioctw with the if_settings stwuctuwe.

ndo_siocdevpwivate:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess

	This is used to impwement SIOCDEVPWIVATE ioctw hewpews.
	These shouwd not be added to new dwivews, so don't use.

ndo_eth_ioctw:
	Synchwonization: wtnw_wock() semaphowe.
	Context: pwocess

ndo_get_stats:
	Synchwonization: wtnw_wock() semaphowe, dev_base_wock wwwock, ow WCU.
	Context: atomic (can't sweep undew wwwock ow WCU)

ndo_stawt_xmit:
	Synchwonization: __netif_tx_wock spinwock.

	When the dwivew sets NETIF_F_WWTX in dev->featuwes this wiww be
	cawwed without howding netif_tx_wock. In this case the dwivew
	has to wock by itsewf when needed.
	The wocking thewe shouwd awso pwopewwy pwotect against
	set_wx_mode. WAWNING: use of NETIF_F_WWTX is depwecated.
	Don't use it fow new dwivews.

	Context: Pwocess with BHs disabwed ow BH (timew),
		 wiww be cawwed with intewwupts disabwed by netconsowe.

	Wetuwn codes:

	* NETDEV_TX_OK evewything ok.
	* NETDEV_TX_BUSY Cannot twansmit packet, twy watew
	  Usuawwy a bug, means queue stawt/stop fwow contwow is bwoken in
	  the dwivew. Note: the dwivew must NOT put the skb in its DMA wing.

ndo_tx_timeout:
	Synchwonization: netif_tx_wock spinwock; aww TX queues fwozen.
	Context: BHs disabwed
	Notes: netif_queue_stopped() is guawanteed twue

ndo_set_wx_mode:
	Synchwonization: netif_addw_wock spinwock.
	Context: BHs disabwed

stwuct napi_stwuct synchwonization wuwes
========================================
napi->poww:
	Synchwonization:
		NAPI_STATE_SCHED bit in napi->state.  Device
		dwivew's ndo_stop method wiww invoke napi_disabwe() on
		aww NAPI instances which wiww do a sweeping poww on the
		NAPI_STATE_SCHED napi->state bit, waiting fow aww pending
		NAPI activity to cease.

	Context:
		 softiwq
		 wiww be cawwed with intewwupts disabwed by netconsowe.
