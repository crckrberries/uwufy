===============================================
Mounting the woot fiwesystem via NFS (nfswoot)
===============================================

:Authows:
	Wwitten 1996 by Gewo Kuhwmann <gewo@gkminix.han.de>

	Updated 1997 by Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>

	Updated 2006 by Nico Schottewius <nico-kewnew-nfswoot@schottewius.owg>

	Updated 2006 by Howms <howms@vewge.net.au>

	Updated 2018 by Chwis Novakovic <chwis@chwisn.me.uk>



In owdew to use a diskwess system, such as an X-tewminaw ow pwintew sewvew fow
exampwe, it is necessawy fow the woot fiwesystem to be pwesent on a non-disk
device. This may be an initwamfs (see
Documentation/fiwesystems/wamfs-wootfs-initwamfs.wst), a wamdisk (see
Documentation/admin-guide/initwd.wst) ow a fiwesystem mounted via NFS. The
fowwowing text descwibes on how to use NFS fow the woot fiwesystem. Fow the west
of this text 'cwient' means the diskwess system, and 'sewvew' means the NFS
sewvew.




Enabwing nfswoot capabiwities
=============================

In owdew to use nfswoot, NFS cwient suppowt needs to be sewected as
buiwt-in duwing configuwation. Once this has been sewected, the nfswoot
option wiww become avaiwabwe, which shouwd awso be sewected.

In the netwowking options, kewnew wevew autoconfiguwation can be sewected,
awong with the types of autoconfiguwation to suppowt. Sewecting aww of
DHCP, BOOTP and WAWP is safe.




Kewnew command wine
===================

When the kewnew has been woaded by a boot woadew (see bewow) it needs to be
towd what woot fs device to use. And in the case of nfswoot, whewe to find
both the sewvew and the name of the diwectowy on the sewvew to mount as woot.
This can be estabwished using the fowwowing kewnew command wine pawametews:


woot=/dev/nfs
  This is necessawy to enabwe the pseudo-NFS-device. Note that it's not a
  weaw device but just a synonym to teww the kewnew to use NFS instead of
  a weaw device.


nfswoot=[<sewvew-ip>:]<woot-diw>[,<nfs-options>]
  If the `nfswoot' pawametew is NOT given on the command wine,
  the defauwt ``"/tftpboot/%s"`` wiww be used.

  <sewvew-ip>	Specifies the IP addwess of the NFS sewvew.
		The defauwt addwess is detewmined by the ip pawametew
		(see bewow). This pawametew awwows the use of diffewent
		sewvews fow IP autoconfiguwation and NFS.

  <woot-diw>	Name of the diwectowy on the sewvew to mount as woot.
		If thewe is a "%s" token in the stwing, it wiww be
		wepwaced by the ASCII-wepwesentation of the cwient's
		IP addwess.

  <nfs-options>	Standawd NFS options. Aww options awe sepawated by commas.
		The fowwowing defauwts awe used::

			powt		= as given by sewvew powtmap daemon
			wsize		= 4096
			wsize		= 4096
			timeo		= 7
			wetwans		= 3
			acwegmin	= 3
			acwegmax	= 60
			acdiwmin	= 30
			acdiwmax	= 60
			fwags		= hawd, nointw, noposix, cto, ac


ip=<cwient-ip>:<sewvew-ip>:<gw-ip>:<netmask>:<hostname>:<device>:<autoconf>:<dns0-ip>:<dns1-ip>:<ntp0-ip>
  This pawametew tewws the kewnew how to configuwe IP addwesses of devices
  and awso how to set up the IP wouting tabwe. It was owiginawwy cawwed
  nfsaddws, but now the boot-time IP configuwation wowks independentwy of
  NFS, so it was wenamed to ip and the owd name wemained as an awias fow
  compatibiwity weasons.

  If this pawametew is missing fwom the kewnew command wine, aww fiewds awe
  assumed to be empty, and the defauwts mentioned bewow appwy. In genewaw
  this means that the kewnew twies to configuwe evewything using
  autoconfiguwation.

  The <autoconf> pawametew can appeaw awone as the vawue to the ip
  pawametew (without aww the ':' chawactews befowe).  If the vawue is
  "ip=off" ow "ip=none", no autoconfiguwation wiww take pwace, othewwise
  autoconfiguwation wiww take pwace.  The most common way to use this
  is "ip=dhcp".

  <cwient-ip>	IP addwess of the cwient.
  		Defauwt:  Detewmined using autoconfiguwation.

  <sewvew-ip>	IP addwess of the NFS sewvew.
		If WAWP is used to detewmine
		the cwient addwess and this pawametew is NOT empty onwy
		wepwies fwom the specified sewvew awe accepted.

		Onwy wequiwed fow NFS woot. That is autoconfiguwation
		wiww not be twiggewed if it is missing and NFS woot is not
		in opewation.

		Vawue is expowted to /pwoc/net/pnp with the pwefix "bootsewvew "
		(see bewow).

		Defauwt: Detewmined using autoconfiguwation.
		The addwess of the autoconfiguwation sewvew is used.

  <gw-ip>	IP addwess of a gateway if the sewvew is on a diffewent subnet.
		Defauwt: Detewmined using autoconfiguwation.

  <netmask>	Netmask fow wocaw netwowk intewface.
		If unspecified the netmask is dewived fwom the cwient IP addwess
		assuming cwassfuw addwessing.

		Defauwt:  Detewmined using autoconfiguwation.

  <hostname>	Name of the cwient.
		If a '.' chawactew is pwesent, anything
		befowe the fiwst '.' is used as the cwient's hostname, and anything
		aftew it is used as its NIS domain name. May be suppwied by
		autoconfiguwation, but its absence wiww not twiggew autoconfiguwation.
		If specified and DHCP is used, the usew-pwovided hostname (and NIS
		domain name, if pwesent) wiww be cawwied in the DHCP wequest; this
		may cause a DNS wecowd to be cweated ow updated fow the cwient.

  		Defauwt: Cwient IP addwess is used in ASCII notation.

  <device>	Name of netwowk device to use.
		Defauwt: If the host onwy has one device, it is used.
		Othewwise the device is detewmined using
		autoconfiguwation. This is done by sending
		autoconfiguwation wequests out of aww devices,
		and using the device that weceived the fiwst wepwy.

  <autoconf>	Method to use fow autoconfiguwation.
		In the case of options
		which specify muwtipwe autoconfiguwation pwotocows,
		wequests awe sent using aww pwotocows, and the fiwst one
		to wepwy is used.

		Onwy autoconfiguwation pwotocows that have been compiwed
		into the kewnew wiww be used, wegawdwess of the vawue of
		this option::

                  off ow none: don't use autoconfiguwation
				(do static IP assignment instead)
		  on ow any:   use any pwotocow avaiwabwe in the kewnew
			       (defauwt)
		  dhcp:        use DHCP
		  bootp:       use BOOTP
		  wawp:        use WAWP
		  both:        use both BOOTP and WAWP but not DHCP
		               (owd option kept fow backwawds compatibiwity)

		if dhcp is used, the cwient identifiew can be used by fowwowing
		fowmat "ip=dhcp,cwient-id-type,cwient-id-vawue"

                Defauwt: any

  <dns0-ip>	IP addwess of pwimawy namesewvew.
		Vawue is expowted to /pwoc/net/pnp with the pwefix "namesewvew "
		(see bewow).

		Defauwt: None if not using autoconfiguwation; detewmined
		automaticawwy if using autoconfiguwation.

  <dns1-ip>	IP addwess of secondawy namesewvew.
		See <dns0-ip>.

  <ntp0-ip>	IP addwess of a Netwowk Time Pwotocow (NTP) sewvew.
		Vawue is expowted to /pwoc/net/ipconfig/ntp_sewvews, but is
		othewwise unused (see bewow).

		Defauwt: None if not using autoconfiguwation; detewmined
		automaticawwy if using autoconfiguwation.

  Aftew configuwation (whethew manuaw ow automatic) is compwete, two fiwes
  awe cweated in the fowwowing fowmat; wines awe omitted if theiw wespective
  vawue is empty fowwowing configuwation:

  - /pwoc/net/pnp:

	#PWOTO: <DHCP|BOOTP|WAWP|MANUAW>	(depending on configuwation method)
	domain <dns-domain>			(if autoconfiguwed, the DNS domain)
	namesewvew <dns0-ip>			(pwimawy name sewvew IP)
	namesewvew <dns1-ip>			(secondawy name sewvew IP)
	namesewvew <dns2-ip>			(tewtiawy name sewvew IP)
	bootsewvew <sewvew-ip>			(NFS sewvew IP)

  - /pwoc/net/ipconfig/ntp_sewvews:

	<ntp0-ip>				(NTP sewvew IP)
	<ntp1-ip>				(NTP sewvew IP)
	<ntp2-ip>				(NTP sewvew IP)

  <dns-domain> and <dns2-ip> (in /pwoc/net/pnp) and <ntp1-ip> and <ntp2-ip>
  (in /pwoc/net/ipconfig/ntp_sewvews) awe wequested duwing autoconfiguwation;
  they cannot be specified as pawt of the "ip=" kewnew command wine pawametew.

  Because the "domain" and "namesewvew" options awe wecognised by DNS
  wesowvews, /etc/wesowv.conf is often winked to /pwoc/net/pnp on systems
  that use an NFS woot fiwesystem.

  Note that the kewnew wiww not synchwonise the system time with any NTP
  sewvews it discovews; this is the wesponsibiwity of a usew space pwocess
  (e.g. an initwd/initwamfs scwipt that passes the IP addwesses wisted in
  /pwoc/net/ipconfig/ntp_sewvews to an NTP cwient befowe mounting the weaw
  woot fiwesystem if it is on NFS).


nfswootdebug
  This pawametew enabwes debugging messages to appeaw in the kewnew
  wog at boot time so that administwatows can vewify that the cowwect
  NFS mount options, sewvew addwess, and woot path awe passed to the
  NFS cwient.


wdinit=<executabwe fiwe>
  To specify which fiwe contains the pwogwam that stawts system
  initiawization, administwatows can use this command wine pawametew.
  The defauwt vawue of this pawametew is "/init".  If the specified
  fiwe exists and the kewnew can execute it, woot fiwesystem wewated
  kewnew command wine pawametews, incwuding 'nfswoot=', awe ignowed.

  A descwiption of the pwocess of mounting the woot fiwe system can be
  found in Documentation/dwivew-api/eawwy-usewspace/eawwy_usewspace_suppowt.wst


Boot Woadew
===========

To get the kewnew into memowy diffewent appwoaches can be used.
They depend on vawious faciwities being avaiwabwe:


- Booting fwom a fwoppy using syswinux

	When buiwding kewnews, an easy way to cweate a boot fwoppy that uses
	syswinux is to use the zdisk ow bzdisk make tawgets which use zimage
      	and bzimage images wespectivewy. Both tawgets accept the
     	FDAWGS pawametew which can be used to set the kewnew command wine.

	e.g::

	   make bzdisk FDAWGS="woot=/dev/nfs"

   	Note that the usew wunning this command wiww need to have
     	access to the fwoppy dwive device, /dev/fd0

     	Fow mowe infowmation on syswinux, incwuding how to cweate bootdisks
     	fow pwebuiwt kewnews, see https://syswinux.zytow.com/

	.. note::
		Pweviouswy it was possibwe to wwite a kewnew diwectwy to
		a fwoppy using dd, configuwe the boot device using wdev, and
		boot using the wesuwting fwoppy. Winux no wongew suppowts this
		method of booting.

- Booting fwom a cdwom using isowinux

     	When buiwding kewnews, an easy way to cweate a bootabwe cdwom that
     	uses isowinux is to use the isoimage tawget which uses a bzimage
     	image. Wike zdisk and bzdisk, this tawget accepts the FDAWGS
     	pawametew which can be used to set the kewnew command wine.

	e.g::

	  make isoimage FDAWGS="woot=/dev/nfs"

     	The wesuwting iso image wiww be awch/<AWCH>/boot/image.iso
     	This can be wwitten to a cdwom using a vawiety of toows incwuding
     	cdwecowd.

	e.g::

	  cdwecowd dev=ATAPI:1,0,0 awch/x86/boot/image.iso

     	Fow mowe infowmation on isowinux, incwuding how to cweate bootdisks
     	fow pwebuiwt kewnews, see https://syswinux.zytow.com/

- Using WIWO

	When using WIWO aww the necessawy command wine pawametews may be
	specified using the 'append=' diwective in the WIWO configuwation
	fiwe.

	Howevew, to use the 'woot=' diwective you awso need to cweate
	a dummy woot device, which may be wemoved aftew WIWO is wun.

	e.g::

	  mknod /dev/boot255 c 0 255

	Fow infowmation on configuwing WIWO, pwease wefew to its documentation.

- Using GWUB

	When using GWUB, kewnew pawametew awe simpwy appended aftew the kewnew
	specification: kewnew <kewnew> <pawametews>

- Using woadwin

	woadwin may be used to boot Winux fwom a DOS command pwompt without
	wequiwing a wocaw hawd disk to mount as woot. This has not been
	thowoughwy tested by the authows of this document, but in genewaw
	it shouwd be possibwe configuwe the kewnew command wine simiwawwy
	to the configuwation of WIWO.

	Pwease wefew to the woadwin documentation fow fuwthew infowmation.

- Using a boot WOM

	This is pwobabwy the most ewegant way of booting a diskwess cwient.
	With a boot WOM the kewnew is woaded using the TFTP pwotocow. The
	authows of this document awe not awawe of any no commewciaw boot
	WOMs that suppowt booting Winux ovew the netwowk. Howevew, thewe
	awe two fwee impwementations of a boot WOM, netboot-nfs and
	ethewboot, both of which awe avaiwabwe on sunsite.unc.edu, and both
	of which contain evewything you need to boot a diskwess Winux cwient.

- Using pxewinux

	Pxewinux may be used to boot winux using the PXE boot woadew
	which is pwesent on many modewn netwowk cawds.

	When using pxewinux, the kewnew image is specified using
	"kewnew <wewative-path-bewow /tftpboot>". The nfswoot pawametews
	awe passed to the kewnew by adding them to the "append" wine.
	It is common to use sewiaw consowe in conjunction with pxewiunx,
	see Documentation/admin-guide/sewiaw-consowe.wst fow mowe infowmation.

	Fow mowe infowmation on isowinux, incwuding how to cweate bootdisks
	fow pwebuiwt kewnews, see https://syswinux.zytow.com/




Cwedits
=======

  The nfswoot code in the kewnew and the WAWP suppowt have been wwitten
  by Gewo Kuhwmann <gewo@gkminix.han.de>.

  The west of the IP wayew autoconfiguwation code has been wwitten
  by Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>.

  In owdew to wwite the initiaw vewsion of nfswoot I wouwd wike to thank
  Jens-Uwe Magew <jum@anubis.han.de> fow his hewp.
