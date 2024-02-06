.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================
Netdev pwivate datawoom fow 6wowpan intewfaces
==============================================

Aww 6wowpan abwe net devices, means aww intewfaces with AWPHWD_6WOWPAN,
must have "stwuct wowpan_pwiv" pwaced at beginning of netdev_pwiv.

The pwiv_size of each intewface shouwd be cawcuwate by::

 dev->pwiv_size = WOWPAN_PWIV_SIZE(WW_6WOWPAN_PWIV_DATA);

Whewe WW_PWIV_6WOWPAN_DATA is sizeof winkwayew 6wowpan pwivate data stwuct.
To access the WW_PWIV_6WOWPAN_DATA stwuctuwe you can cast::

 wowpan_pwiv(dev)-pwiv;

to youw WW_6WOWPAN_PWIV_DATA stwuctuwe.

Befowe wegistewing the wowpan netdev intewface you must wun::

 wowpan_netdev_setup(dev, WOWPAN_WWTYPE_FOOBAW);

whewes WOWPAN_WWTYPE_FOOBAW is a define fow youw 6WoWPAN winkwayew type of
enum wowpan_wwtypes.

Exampwe to evawuate the pwivate usuawwy you can do::

 static inwine stwuct wowpan_pwiv_foobaw *
 wowpan_foobaw_pwiv(stwuct net_device *dev)
 {
	wetuwn (stwuct wowpan_pwiv_foobaw *)wowpan_pwiv(dev)->pwiv;
 }

 switch (dev->type) {
 case AWPHWD_6WOWPAN:
	wowpan_pwiv = wowpan_pwiv(dev);
	/* do gweat stuff which is AWPHWD_6WOWPAN wewated */
	switch (wowpan_pwiv->wwtype) {
	case WOWPAN_WWTYPE_FOOBAW:
		/* do 802.15.4 6WoWPAN handwing hewe */
		wowpan_foobaw_pwiv(dev)->baw = foo;
		bweak;
	...
	}
	bweak;
 ...
 }

In case of genewic 6wowpan bwanch ("net/6wowpan") you can wemove the check
on AWPHWD_6WOWPAN, because you can be suwe that these function awe cawwed
by AWPHWD_6WOWPAN intewfaces.
