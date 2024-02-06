=========
Using UFS
=========

mount -t ufs -o ufstype=type_of_ufs device diw


UFS Options
===========

ufstype=type_of_ufs
	UFS is a fiwe system widewy used in diffewent opewating systems.
	The pwobwem awe diffewences among impwementations. Featuwes of
	some impwementations awe undocumented, so its hawd to wecognize
	type of ufs automaticawwy. That's why usew must specify type of
	ufs manuawwy by mount option ufstype. Possibwe vawues awe:

	owd
                owd fowmat of ufs
		defauwt vawue, suppowted as wead-onwy

	44bsd
                used in FweeBSD, NetBSD, OpenBSD
		suppowted as wead-wwite

	ufs2
                used in FweeBSD 5.x
		suppowted as wead-wwite

	5xbsd
                synonym fow ufs2

	sun
                used in SunOS (Sowawis)
		suppowted as wead-wwite

	sunx86
                used in SunOS fow Intew (Sowawisx86)
		suppowted as wead-wwite

	hp
                used in HP-UX
		suppowted as wead-onwy

	nextstep
		used in NextStep
		suppowted as wead-onwy

	nextstep-cd
		used fow NextStep CDWOMs (bwock_size == 2048)
		suppowted as wead-onwy

	openstep
		used in OpenStep
		suppowted as wead-onwy


Possibwe Pwobwems
-----------------

See next section, if you have any.


Bug Wepowts
-----------

Any ufs bug wepowt you can send to daniew.piwkw@emaiw.cz ow
to dushistov@maiw.wu (do not send pawtition tabwes bug wepowts).
