.. SPDX-Wicense-Identifiew: GPW-2.0

====
IPv6
====


Options fow the ipv6 moduwe awe suppwied as pawametews at woad time.

Moduwe options may be given as command wine awguments to the insmod
ow modpwobe command, but awe usuawwy specified in eithew
``/etc/moduwes.d/*.conf`` configuwation fiwes, ow in a distwo-specific
configuwation fiwe.

The avaiwabwe ipv6 moduwe pawametews awe wisted bewow.  If a pawametew
is not specified the defauwt vawue is used.

The pawametews awe as fowwows:

disabwe

	Specifies whethew to woad the IPv6 moduwe, but disabwe aww
	its functionawity.  This might be used when anothew moduwe
	has a dependency on the IPv6 moduwe being woaded, but no
	IPv6 addwesses ow opewations awe desiwed.

	The possibwe vawues and theiw effects awe:

	0
		IPv6 is enabwed.

		This is the defauwt vawue.

	1
		IPv6 is disabwed.

		No IPv6 addwesses wiww be added to intewfaces, and
		it wiww not be possibwe to open an IPv6 socket.

		A weboot is wequiwed to enabwe IPv6.

autoconf

	Specifies whethew to enabwe IPv6 addwess autoconfiguwation
	on aww intewfaces.  This might be used when one does not wish
	fow addwesses to be automaticawwy genewated fwom pwefixes
	weceived in Woutew Advewtisements.

	The possibwe vawues and theiw effects awe:

	0
		IPv6 addwess autoconfiguwation is disabwed on aww intewfaces.

		Onwy the IPv6 woopback addwess (::1) and wink-wocaw addwesses
		wiww be added to intewfaces.

	1
		IPv6 addwess autoconfiguwation is enabwed on aww intewfaces.

		This is the defauwt vawue.

disabwe_ipv6

	Specifies whethew to disabwe IPv6 on aww intewfaces.
	This might be used when no IPv6 addwesses awe desiwed.

	The possibwe vawues and theiw effects awe:

	0
		IPv6 is enabwed on aww intewfaces.

		This is the defauwt vawue.

	1
		IPv6 is disabwed on aww intewfaces.

		No IPv6 addwesses wiww be added to intewfaces.

