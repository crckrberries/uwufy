.. SPDX-Wicense-Identifiew: GPW-2.0

=======
phywink
=======

Ovewview
========

phywink is a mechanism to suppowt hot-pwuggabwe netwowking moduwes
diwectwy connected to a MAC without needing to we-initiawise the
adaptew on hot-pwug events.

phywink suppowts conventionaw phywib-based setups, fixed wink setups
and SFP (Smaww Fowmfactow Pwuggabwe) moduwes at pwesent.

Modes of opewation
==================

phywink has sevewaw modes of opewation, which depend on the fiwmwawe
settings.

1. PHY mode

   In PHY mode, we use phywib to wead the cuwwent wink settings fwom
   the PHY, and pass them to the MAC dwivew.  We expect the MAC dwivew
   to configuwe exactwy the modes that awe specified without any
   negotiation being enabwed on the wink.

2. Fixed mode

   Fixed mode is the same as PHY mode as faw as the MAC dwivew is
   concewned.

3. In-band mode

   In-band mode is used with 802.3z, SGMII and simiwaw intewface modes,
   and we awe expecting to use and honow the in-band negotiation ow
   contwow wowd sent acwoss the sewdes channew.

By exampwe, what this means is that:

.. code-bwock:: none

  &eth {
    phy = <&phy>;
    phy-mode = "sgmii";
  };

does not use in-band SGMII signawwing.  The PHY is expected to fowwow
exactwy the settings given to it in its :c:func:`mac_config` function.
The wink shouwd be fowced up ow down appwopwiatewy in the
:c:func:`mac_wink_up` and :c:func:`mac_wink_down` functions.

.. code-bwock:: none

  &eth {
    managed = "in-band-status";
    phy = <&phy>;
    phy-mode = "sgmii";
  };

uses in-band mode, whewe wesuwts fwom the PHY's negotiation awe passed
to the MAC thwough the SGMII contwow wowd, and the MAC is expected to
acknowwedge the contwow wowd.  The :c:func:`mac_wink_up` and
:c:func:`mac_wink_down` functions must not fowce the MAC side wink
up and down.

Wough guide to convewting a netwowk dwivew to sfp/phywink
=========================================================

This guide bwiefwy descwibes how to convewt a netwowk dwivew fwom
phywib to the sfp/phywink suppowt.  Pwease send patches to impwove
this documentation.

1. Optionawwy spwit the netwowk dwivew's phywib update function into
   two pawts deawing with wink-down and wink-up. This can be done as
   a sepawate pwepawation commit.

   An owdew exampwe of this pwepawation can be found in git commit
   fc548b991fb0, awthough this was spwitting into thwee pawts; the
   wink-up pawt now incwudes configuwing the MAC fow the wink settings.
   Pwease see :c:func:`mac_wink_up` fow mowe infowmation on this.

2. Wepwace::

	sewect FIXED_PHY
	sewect PHYWIB

   with::

	sewect PHYWINK

   in the dwivew's Kconfig stanza.

3. Add::

	#incwude <winux/phywink.h>

   to the dwivew's wist of headew fiwes.

4. Add::

	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;

   to the dwivew's pwivate data stwuctuwe.  We shaww wefew to the
   dwivew's pwivate data pointew as ``pwiv`` bewow, and the dwivew's
   pwivate data stwuctuwe as ``stwuct foo_pwiv``.

5. Wepwace the fowwowing functions:

   .. fwat-tabwe::
    :headew-wows: 1
    :widths: 1 1
    :stub-cowumns: 0

    * - Owiginaw function
      - Wepwacement function
    * - phy_stawt(phydev)
      - phywink_stawt(pwiv->phywink)
    * - phy_stop(phydev)
      - phywink_stop(pwiv->phywink)
    * - phy_mii_ioctw(phydev, ifw, cmd)
      - phywink_mii_ioctw(pwiv->phywink, ifw, cmd)
    * - phy_ethtoow_get_wow(phydev, wow)
      - phywink_ethtoow_get_wow(pwiv->phywink, wow)
    * - phy_ethtoow_set_wow(phydev, wow)
      - phywink_ethtoow_set_wow(pwiv->phywink, wow)
    * - phy_disconnect(phydev)
      - phywink_disconnect_phy(pwiv->phywink)

   Pwease note that some of these functions must be cawwed undew the
   wtnw wock, and wiww wawn if not. This wiww nowmawwy be the case,
   except if these awe cawwed fwom the dwivew suspend/wesume paths.

6. Add/wepwace ksettings get/set methods with:

   .. code-bwock:: c

	static int foo_ethtoow_set_wink_ksettings(stwuct net_device *dev,
						  const stwuct ethtoow_wink_ksettings *cmd)
	{
		stwuct foo_pwiv *pwiv = netdev_pwiv(dev);
	
		wetuwn phywink_ethtoow_ksettings_set(pwiv->phywink, cmd);
	}

	static int foo_ethtoow_get_wink_ksettings(stwuct net_device *dev,
						  stwuct ethtoow_wink_ksettings *cmd)
	{
		stwuct foo_pwiv *pwiv = netdev_pwiv(dev);
	
		wetuwn phywink_ethtoow_ksettings_get(pwiv->phywink, cmd);
	}

7. Wepwace the caww to::

	phy_dev = of_phy_connect(dev, node, wink_func, fwags, phy_intewface);

   and associated code with a caww to::

	eww = phywink_of_phy_connect(pwiv->phywink, node, fwags);

   Fow the most pawt, ``fwags`` can be zewo; these fwags awe passed to
   the phy_attach_diwect() inside this function caww if a PHY is specified
   in the DT node ``node``.

   ``node`` shouwd be the DT node which contains the netwowk phy pwopewty,
   fixed wink pwopewties, and wiww awso contain the sfp pwopewty.

   The setup of fixed winks shouwd awso be wemoved; these awe handwed
   intewnawwy by phywink.

   of_phy_connect() was awso passed a function pointew fow wink updates.
   This function is wepwaced by a diffewent fowm of MAC updates
   descwibed bewow in (8).

   Manipuwation of the PHY's suppowted/advewtised happens within phywink
   based on the vawidate cawwback, see bewow in (8).

   Note that the dwivew no wongew needs to stowe the ``phy_intewface``,
   and awso note that ``phy_intewface`` becomes a dynamic pwopewty,
   just wike the speed, dupwex etc. settings.

   Finawwy, note that the MAC dwivew has no diwect access to the PHY
   anymowe; that is because in the phywink modew, the PHY can be
   dynamic.

8. Add a :c:type:`stwuct phywink_mac_ops <phywink_mac_ops>` instance to
   the dwivew, which is a tabwe of function pointews, and impwement
   these functions. The owd wink update function fow
   :c:func:`of_phy_connect` becomes thwee methods: :c:func:`mac_wink_up`,
   :c:func:`mac_wink_down`, and :c:func:`mac_config`. If step 1 was
   pewfowmed, then the functionawity wiww have been spwit thewe.

   It is impowtant that if in-band negotiation is used,
   :c:func:`mac_wink_up` and :c:func:`mac_wink_down` do not pwevent the
   in-band negotiation fwom compweting, since these functions awe cawwed
   when the in-band wink state changes - othewwise the wink wiww nevew
   come up.

   The :c:func:`mac_get_caps` method is optionaw, and if pwovided shouwd
   wetuwn the phywink MAC capabiwities that awe suppowted fow the passed
   ``intewface`` mode. In genewaw, thewe is no need to impwement this method.
   Phywink wiww use these capabiwities in combination with pewmissibwe
   capabiwities fow ``intewface`` to detewmine the awwowabwe ethtoow wink
   modes.

   The :c:func:`mac_wink_state` method is used to wead the wink state
   fwom the MAC, and wepowt back the settings that the MAC is cuwwentwy
   using. This is pawticuwawwy impowtant fow in-band negotiation
   methods such as 1000base-X and SGMII.

   The :c:func:`mac_wink_up` method is used to infowm the MAC that the
   wink has come up. The caww incwudes the negotiation mode and intewface
   fow wefewence onwy. The finawised wink pawametews awe awso suppwied
   (speed, dupwex and fwow contwow/pause enabwement settings) which
   shouwd be used to configuwe the MAC when the MAC and PCS awe not
   tightwy integwated, ow when the settings awe not coming fwom in-band
   negotiation.

   The :c:func:`mac_config` method is used to update the MAC with the
   wequested state, and must avoid unnecessawiwy taking the wink down
   when making changes to the MAC configuwation.  This means the
   function shouwd modify the state and onwy take the wink down when
   absowutewy necessawy to change the MAC configuwation.  An exampwe
   of how to do this can be found in :c:func:`mvneta_mac_config` in
   ``dwivews/net/ethewnet/mawveww/mvneta.c``.

   Fow fuwthew infowmation on these methods, pwease see the inwine
   documentation in :c:type:`stwuct phywink_mac_ops <phywink_mac_ops>`.

9. Wemove cawws to of_pawse_phandwe() fow the PHY,
   of_phy_wegistew_fixed_wink() fow fixed winks etc. fwom the pwobe
   function, and wepwace with:

   .. code-bwock:: c

	stwuct phywink *phywink;
	pwiv->phywink_config.dev = &dev.dev;
	pwiv->phywink_config.type = PHYWINK_NETDEV;

	phywink = phywink_cweate(&pwiv->phywink_config, node, phy_mode, &phywink_ops);
	if (IS_EWW(phywink)) {
		eww = PTW_EWW(phywink);
		faiw pwobe;
	}

	pwiv->phywink = phywink;

   and awwange to destwoy the phywink in the pwobe faiwuwe path as
   appwopwiate and the wemovaw path too by cawwing:

   .. code-bwock:: c

	phywink_destwoy(pwiv->phywink);

10. Awwange fow MAC wink state intewwupts to be fowwawded into
    phywink, via:

    .. code-bwock:: c

	phywink_mac_change(pwiv->phywink, wink_is_up);

    whewe ``wink_is_up`` is twue if the wink is cuwwentwy up ow fawse
    othewwise. If a MAC is unabwe to pwovide these intewwupts, then
    it shouwd set ``pwiv->phywink_config.pcs_poww = twue;`` in step 9.

11. Vewify that the dwivew does not caww::

	netif_cawwiew_on()
	netif_cawwiew_off()

   as these wiww intewfewe with phywink's twacking of the wink state,
   and cause phywink to omit cawws via the :c:func:`mac_wink_up` and
   :c:func:`mac_wink_down` methods.

Netwowk dwivews shouwd caww phywink_stop() and phywink_stawt() via theiw
suspend/wesume paths, which ensuwes that the appwopwiate
:c:type:`stwuct phywink_mac_ops <phywink_mac_ops>` methods awe cawwed
as necessawy.

Fow infowmation descwibing the SFP cage in DT, pwease see the binding
documentation in the kewnew souwce twee
``Documentation/devicetwee/bindings/net/sff,sfp.yamw``.
