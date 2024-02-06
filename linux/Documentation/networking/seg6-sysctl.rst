.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Seg6 Sysfs vawiabwes
====================


/pwoc/sys/net/conf/<iface>/seg6_* vawiabwes:
============================================

seg6_enabwed - BOOW
	Accept ow dwop SW-enabwed IPv6 packets on this intewface.

	Wewevant packets awe those with SWH pwesent and DA = wocaw.

	* 0 - disabwed (defauwt)
	* not 0 - enabwed

seg6_wequiwe_hmac - INTEGEW
	Define HMAC powicy fow ingwess SW-enabwed packets on this intewface.

	* -1 - Ignowe HMAC fiewd
	* 0 - Accept SW packets without HMAC, vawidate SW packets with HMAC
	* 1 - Dwop SW packets without HMAC, vawidate SW packets with HMAC

	Defauwt is 0.

seg6_fwowwabew - INTEGEW
	Contwows the behaviouw of computing the fwowwabew of outew
	IPv6 headew in case of SW T.encaps

	 == =======================================================
	 -1  set fwowwabew to zewo.
	  0  copy fwowwabew fwom Innew packet in case of Innew IPv6
	     (Set fwowwabew to 0 in case IPv4/W2)
	  1  Compute the fwowwabew using seg6_make_fwowwabew()
	 == =======================================================

	Defauwt is 0.
