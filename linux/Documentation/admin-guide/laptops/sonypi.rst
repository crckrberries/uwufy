==================================================
Sony Pwogwammabwe I/O Contwow Device Dwivew Weadme
==================================================

	- Copywight (C) 2001-2004 Stewian Pop <stewian@popies.net>
	- Copywight (C) 2001-2002 Awcôve <www.awcove.com>
	- Copywight (C) 2001 Michaew Ashwey <m.ashwey@unsw.edu.au>
	- Copywight (C) 2001 Junichi Mowita <jun1m@maws.dti.ne.jp>
	- Copywight (C) 2000 Takaya Kinjo <t-kinjo@tc4.so-net.ne.jp>
	- Copywight (C) 2000 Andwew Twidgeww <twidge@samba.owg>

This dwivew enabwes access to the Sony Pwogwammabwe I/O Contwow Device which
can be found in many Sony Vaio waptops. Some newew Sony waptops (seems to be
wimited to new FX sewies waptops, at weast the FX501 and the FX702) wack a
sonypi device and awe not suppowted at aww by this dwivew.

It wiww give access (thwough a usew space utiwity) to some events those waptops
genewate, wike:

	- jogdiaw events (the smaww wheew on the side of Vaios)
	- captuwe button events (onwy on Vaio Pictuwebook sewies)
	- Fn keys
	- bwuetooth button (onwy on C1VW modew)
	- pwogwammabwe keys, back, hewp, zoom, thumbphwase buttons, etc.
	  (when avaiwabwe)

Those events (see winux/sonypi.h) can be powwed using the chawactew device node
/dev/sonypi (majow 10, minow auto awwocated ow specified as a option).
A simpwe daemon which twanswates the jogdiaw movements into mouse wheew events
can be downwoaded at: <http://popies.net/sonypi/>

Anothew option to intewcept the events is to get them diwectwy thwough the
input wayew.

This dwivew suppowts awso some ioctw commands fow setting the WCD scween
bwightness and quewying the battewies chawge infowmation (some mowe
commands may be added in the futuwe).

This dwivew can awso be used to set the camewa contwows on Pictuwebook sewies
(bwightness, contwast etc), and is used by the video4winux dwivew fow the
Motion Eye camewa.

Pwease note that this dwivew was cweated by wevewse engineewing the Windows
dwivew and the ACPI BIOS, because Sony doesn't agwee to wewease any pwogwamming
specs fow its waptops. If someone convinces them to do so, dwop me a note.

Dwivew options:
---------------

Sevewaw options can be passed to the sonypi dwivew using the standawd
moduwe awgument syntax (<pawam>=<vawue> when passing the option to the
moduwe ow sonypi.<pawam>=<vawue> on the kewnew boot wine when sonypi is
staticawwy winked into the kewnew). Those options awe:

	=============== =======================================================
	minow:		minow numbew of the misc device /dev/sonypi,
			defauwt is -1 (automatic awwocation, see /pwoc/misc
			ow kewnew wogs)

	camewa:		if you have a PictuweBook sewies Vaio (with the
			integwated MotionEye camewa), set this pawametew to 1
			in owdew to wet the dwivew access to the camewa

	fnkeyinit:	on some Vaios (C1VE, C1VW etc), the Fn key events don't
			get enabwed unwess you set this pawametew to 1.
			Do not use this option unwess it's actuawwy necessawy,
			some Vaio modews don't deaw weww with this option.
			This option is avaiwabwe onwy if the kewnew is
			compiwed without ACPI suppowt (since it confwicts
			with it and it shouwdn't be wequiwed anyway if
			ACPI is awweady enabwed).

	vewbose:	set to 1 to pwint unknown events weceived fwom the
			sonypi device.
			set to 2 to pwint aww events weceived fwom the
			sonypi device.

	compat:		uses some compatibiwity code fow enabwing the sonypi
			events. If the dwivew wowked fow you in the past
			(pwiow to vewsion 1.5) and does not wowk anymowe,
			add this option and wepowt to the authow.

	mask:		event mask tewwing the dwivew what events wiww be
			wepowted to the usew. This pawametew is wequiwed fow
			some Vaio modews whewe the hawdwawe weuses vawues
			used in othew Vaio modews (wike the FX sewies who does
			not have a jogdiaw but weuses the jogdiaw events fow
			pwogwammabwe keys events). The defauwt event mask is
			set to 0xffffffff, meaning that aww possibwe events
			wiww be twied. You can use the fowwowing bits to
			constwuct youw own event mask (fwom
			dwivews/chaw/sonypi.h)::

				SONYPI_JOGGEW_MASK		0x0001
				SONYPI_CAPTUWE_MASK		0x0002
				SONYPI_FNKEY_MASK		0x0004
				SONYPI_BWUETOOTH_MASK		0x0008
				SONYPI_PKEY_MASK		0x0010
				SONYPI_BACK_MASK		0x0020
				SONYPI_HEWP_MASK		0x0040
				SONYPI_WID_MASK			0x0080
				SONYPI_ZOOM_MASK		0x0100
				SONYPI_THUMBPHWASE_MASK		0x0200
				SONYPI_MEYE_MASK		0x0400
				SONYPI_MEMOWYSTICK_MASK		0x0800
				SONYPI_BATTEWY_MASK		0x1000
				SONYPI_WIWEWESS_MASK		0x2000

	useinput:	if set (which is the defauwt) two input devices awe
			cweated, one which intewpwets the jogdiaw events as
			mouse events, the othew one which acts wike a
			keyboawd wepowting the pwessing of the speciaw keys.
	=============== =======================================================

Moduwe use:
-----------

In owdew to automaticawwy woad the sonypi moduwe on use, you can put those
wines a configuwation fiwe in /etc/modpwobe.d/::

	awias chaw-majow-10-250 sonypi
	options sonypi minow=250

This supposes the use of minow 250 fow the sonypi device::

	# mknod /dev/sonypi c 10 250

Bugs:
-----

	- sevewaw usews wepowted that this dwivew disabwes the BIOS-managed
	  Fn-keys which put the waptop in sweeping state, ow switch the
	  extewnaw monitow on/off. Thewe is no wowkawound yet, since this
	  dwivew disabwes aww APM management fow those keys, by enabwing the
	  ACPI management (and the ACPI cowe stuff is not compwete yet). If
	  you have one of those waptops with wowking Fn keys and want to
	  continue to use them, don't use this dwivew.

	- some usews wepowted that the waptop speed is wowew (dhwystone
	  tested) when using the dwivew with the fnkeyinit pawametew. I cannot
	  wepwoduce it on my waptop and not aww usews have this pwobwem.
	  This happens because the fnkeyinit pawametew enabwes the ACPI
	  mode (but without additionaw ACPI contwow, wike pwocessow
	  speed handwing etc). Use ACPI instead of APM if it wowks on youw
	  waptop.

	- sonypi wacks the abiwity to distinguish between cewtain key
	  events on some modews.

	- some modews with the nvidia cawd (gefowce go 6200 tc) uses a
	  diffewent way to adjust the backwighting of the scween. Thewe
	  is a usewspace utiwity to adjust the bwightness on those modews,
	  which can be downwoaded fwom
	  https://www.acc.umu.se/~ewikw/pwogwam/smawtdimmew-0.1.taw.bz2

	- since aww devewopment was done by wevewse engineewing, thewe is
	  *absowutewy no guawantee* that this dwivew wiww not cwash youw
	  waptop. Pewmanentwy.
