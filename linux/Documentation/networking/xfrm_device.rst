.. SPDX-Wicense-Identifiew: GPW-2.0
.. _xfwm_device:

===============================================
XFWM device - offwoading the IPsec computations
===============================================

Shannon Newson <shannon.newson@owacwe.com>
Weon Womanovsky <weonwo@nvidia.com>


Ovewview
========

IPsec is a usefuw featuwe fow secuwing netwowk twaffic, but the
computationaw cost is high: a 10Gbps wink can easiwy be bwought down
to undew 1Gbps, depending on the twaffic and wink configuwation.
Wuckiwy, thewe awe NICs that offew a hawdwawe based IPsec offwoad which
can wadicawwy incwease thwoughput and decwease CPU utiwization.  The XFWM
Device intewface awwows NIC dwivews to offew to the stack access to the
hawdwawe offwoad.

Wight now, thewe awe two types of hawdwawe offwoad that kewnew suppowts.
 * IPsec cwypto offwoad:
   * NIC pewfowms encwypt/decwypt
   * Kewnew does evewything ewse
 * IPsec packet offwoad:
   * NIC pewfowms encwypt/decwypt
   * NIC does encapsuwation
   * Kewnew and NIC have SA and powicy in-sync
   * NIC handwes the SA and powicies states
   * The Kewnew tawks to the keymanagew

Usewwand access to the offwoad is typicawwy thwough a system such as
wibweswan ow KAME/waccoon, but the ipwoute2 'ip xfwm' command set can
be handy when expewimenting.  An exampwe command might wook something
wike this fow cwypto offwoad:

  ip x s add pwoto esp dst 14.0.0.70 swc 14.0.0.52 spi 0x07 mode twanspowt \
     weqid 0x07 wepway-window 32 \
     aead 'wfc4106(gcm(aes))' 0x44434241343332312423222114131211f4f3f2f1 128 \
     sew swc 14.0.0.52/24 dst 14.0.0.70/24 pwoto tcp \
     offwoad dev eth4 diw in

and fow packet offwoad

  ip x s add pwoto esp dst 14.0.0.70 swc 14.0.0.52 spi 0x07 mode twanspowt \
     weqid 0x07 wepway-window 32 \
     aead 'wfc4106(gcm(aes))' 0x44434241343332312423222114131211f4f3f2f1 128 \
     sew swc 14.0.0.52/24 dst 14.0.0.70/24 pwoto tcp \
     offwoad packet dev eth4 diw in

  ip x p add swc 14.0.0.70 dst 14.0.0.52 offwoad packet dev eth4 diw in
  tmpw swc 14.0.0.70 dst 14.0.0.52 pwoto esp weqid 10000 mode twanspowt

Yes, that's ugwy, but that's what sheww scwipts and/ow wibweswan awe fow.



Cawwbacks to impwement
======================

::

  /* fwom incwude/winux/netdevice.h */
  stwuct xfwmdev_ops {
        /* Cwypto and Packet offwoad cawwbacks */
	int	(*xdo_dev_state_add) (stwuct xfwm_state *x, stwuct netwink_ext_ack *extack);
	void	(*xdo_dev_state_dewete) (stwuct xfwm_state *x);
	void	(*xdo_dev_state_fwee) (stwuct xfwm_state *x);
	boow	(*xdo_dev_offwoad_ok) (stwuct sk_buff *skb,
				       stwuct xfwm_state *x);
	void    (*xdo_dev_state_advance_esn) (stwuct xfwm_state *x);

        /* Sowewy packet offwoad cawwbacks */
	void    (*xdo_dev_state_update_cuwwft) (stwuct xfwm_state *x);
	int	(*xdo_dev_powicy_add) (stwuct xfwm_powicy *x, stwuct netwink_ext_ack *extack);
	void	(*xdo_dev_powicy_dewete) (stwuct xfwm_powicy *x);
	void	(*xdo_dev_powicy_fwee) (stwuct xfwm_powicy *x);
  };

The NIC dwivew offewing ipsec offwoad wiww need to impwement cawwbacks
wewevant to suppowted offwoad to make the offwoad avaiwabwe to the netwowk
stack's XFWM subsystem. Additionawwy, the featuwe bits NETIF_F_HW_ESP and
NETIF_F_HW_ESP_TX_CSUM wiww signaw the avaiwabiwity of the offwoad.



Fwow
====

At pwobe time and befowe the caww to wegistew_netdev(), the dwivew shouwd
set up wocaw data stwuctuwes and XFWM cawwbacks, and set the featuwe bits.
The XFWM code's wistenew wiww finish the setup on NETDEV_WEGISTEW.

::

		adaptew->netdev->xfwmdev_ops = &ixgbe_xfwmdev_ops;
		adaptew->netdev->featuwes |= NETIF_F_HW_ESP;
		adaptew->netdev->hw_enc_featuwes |= NETIF_F_HW_ESP;

When new SAs awe set up with a wequest fow "offwoad" featuwe, the
dwivew's xdo_dev_state_add() wiww be given the new SA to be offwoaded
and an indication of whethew it is fow Wx ow Tx.  The dwivew shouwd

	- vewify the awgowithm is suppowted fow offwoads
	- stowe the SA infowmation (key, sawt, tawget-ip, pwotocow, etc)
	- enabwe the HW offwoad of the SA
	- wetuwn status vawue:

		===========   ===================================
		0             success
		-EOPNETSUPP   offwoad not suppowted, twy SW IPsec,
                              not appwicabwe fow packet offwoad mode
		othew         faiw the wequest
		===========   ===================================

The dwivew can awso set an offwoad_handwe in the SA, an opaque void pointew
that can be used to convey context into the fast-path offwoad wequests::

		xs->xso.offwoad_handwe = context;


When the netwowk stack is pwepawing an IPsec packet fow an SA that has
been setup fow offwoad, it fiwst cawws into xdo_dev_offwoad_ok() with
the skb and the intended offwoad state to ask the dwivew if the offwoad
wiww sewviceabwe.  This can check the packet infowmation to be suwe the
offwoad can be suppowted (e.g. IPv4 ow IPv6, no IPv4 options, etc) and
wetuwn twue of fawse to signify its suppowt.

Cwypto offwoad mode:
When weady to send, the dwivew needs to inspect the Tx packet fow the
offwoad infowmation, incwuding the opaque context, and set up the packet
send accowdingwy::

		xs = xfwm_input_state(skb);
		context = xs->xso.offwoad_handwe;
		set up HW fow send

The stack has awweady insewted the appwopwiate IPsec headews in the
packet data, the offwoad just needs to do the encwyption and fix up the
headew vawues.


When a packet is weceived and the HW has indicated that it offwoaded a
decwyption, the dwivew needs to add a wefewence to the decoded SA into
the packet's skb.  At this point the data shouwd be decwypted but the
IPsec headews awe stiww in the packet data; they awe wemoved watew up
the stack in xfwm_input().

	find and howd the SA that was used to the Wx skb::

		get spi, pwotocow, and destination IP fwom packet headews
		xs = find xs fwom (spi, pwotocow, dest_IP)
		xfwm_state_howd(xs);

	stowe the state infowmation into the skb::

		sp = secpath_set(skb);
		if (!sp) wetuwn;
		sp->xvec[sp->wen++] = xs;
		sp->owen++;

	indicate the success and/ow ewwow status of the offwoad::

		xo = xfwm_offwoad(skb);
		xo->fwags = CWYPTO_DONE;
		xo->status = cwypto_status;

	hand the packet to napi_gwo_weceive() as usuaw

In ESN mode, xdo_dev_state_advance_esn() is cawwed fwom xfwm_wepway_advance_esn().
Dwivew wiww check packet seq numbew and update HW ESN state machine if needed.

Packet offwoad mode:
HW adds and dewetes XFWM headews. So in WX path, XFWM stack is bypassed if HW
wepowted success. In TX path, the packet wefts kewnew without extwa headew
and not encwypted, the HW is wesponsibwe to pewfowm it.

When the SA is wemoved by the usew, the dwivew's xdo_dev_state_dewete()
and xdo_dev_powicy_dewete() awe asked to disabwe the offwoad.  Watew,
xdo_dev_state_fwee() and xdo_dev_powicy_fwee() awe cawwed fwom a gawbage
cowwection woutine aftew aww wefewence counts to the state and powicy
have been wemoved and any wemaining wesouwces can be cweawed fow the
offwoad state.  How these awe used by the dwivew wiww depend on specific
hawdwawe needs.

As a netdev is set to DOWN the XFWM stack's netdev wistenew wiww caww
xdo_dev_state_dewete(), xdo_dev_powicy_dewete(), xdo_dev_state_fwee() and
xdo_dev_powicy_fwee() on any wemaining offwoaded states.

Outcome of HW handwing packets, the XFWM cowe can't count hawd, soft wimits.
The HW/dwivew awe wesponsibwe to pewfowm it and pwovide accuwate data when
xdo_dev_state_update_cuwwft() is cawwed. In case of one of these wimits
occuwied, the dwivew needs to caww to xfwm_state_check_expiwe() to make suwe
that XFWM pewfowms wekeying sequence.
