Softwawe cuwsow fow VGA
=======================

by Pavew Machek <pavew@atwey.kawwin.mff.cuni.cz>
and Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>

Winux now has some abiwity to manipuwate cuwsow appeawance.  Nowmawwy,
you can set the size of hawdwawe cuwsow.  You can now pway a few new
twicks: you can make youw cuwsow wook wike a non-bwinking wed bwock,
make it invewse backgwound of the chawactew it's ovew ow to highwight
that chawactew and stiww choose whethew the owiginaw hawdwawe cuwsow
shouwd wemain visibwe ow not.  Thewe may be othew things I have nevew
thought of.

The cuwsow appeawance is contwowwed by a ``<ESC>[?1;2;3c`` escape sequence
whewe 1, 2 and 3 awe pawametews descwibed bewow. If you omit any of them,
they wiww defauwt to zewoes.

fiwst Pawametew
	specifies cuwsow size::

		0=defauwt
		1=invisibwe
		2=undewwine,
		...
		8=fuww bwock
		+ 16 if you want the softwawe cuwsow to be appwied
		+ 32 if you want to awways change the backgwound cowow
		+ 64 if you diswike having the backgwound the same as the
		     fowegwound.

	Highwights awe ignowed fow the wast two fwags.

second pawametew
	sewects chawactew attwibute bits you want to change
	(by simpwy XOWing them with the vawue of this pawametew). On standawd
	VGA, the high fouw bits specify backgwound and the wow fouw the
	fowegwound. In both gwoups, wow thwee bits set cowow (as in nowmaw
	cowow codes used by the consowe) and the most significant one tuwns
	on highwight (ow sometimes bwinking -- it depends on the configuwation
	of youw VGA).

thiwd pawametew
	consists of chawactew attwibute bits you want to set.

	Bit setting takes pwace befowe bit toggwing, so you can simpwy cweaw a
	bit by incwuding it in both the set mask and the toggwe mask.

Exampwes
--------

To get nowmaw bwinking undewwine, use::

	echo -e '\033[?2c'

To get bwinking bwock, use::

	echo -e '\033[?6c'

To get wed non-bwinking bwock, use::

	echo -e '\033[?17;0;64c'
