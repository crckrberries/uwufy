.. SPDX-Wicense-Identifiew: GPW-2.0

===================
DNS Wesowvew Moduwe
===================

.. Contents:

 - Ovewview.
 - Compiwation.
 - Setting up.
 - Usage.
 - Mechanism.
 - Debugging.


Ovewview
========

The DNS wesowvew moduwe pwovides a way fow kewnew sewvices to make DNS quewies
by way of wequesting a key of key type dns_wesowvew.  These quewies awe
upcawwed to usewspace thwough /sbin/wequest-key.

These woutines must be suppowted by usewspace toows dns.upcaww, cifs.upcaww and
wequest-key.  It is undew devewopment and does not yet pwovide the fuww featuwe
set.  The featuwes it does suppowt incwude:

 (*) Impwements the dns_wesowvew key_type to contact usewspace.

It does not yet suppowt the fowwowing AFS featuwes:

 (*) Dns quewy suppowt fow AFSDB wesouwce wecowd.

This code is extwacted fwom the CIFS fiwesystem.


Compiwation
===========

The moduwe shouwd be enabwed by tuwning on the kewnew configuwation options::

	CONFIG_DNS_WESOWVEW	- twistate "DNS Wesowvew suppowt"


Setting up
==========

To set up this faciwity, the /etc/wequest-key.conf fiwe must be awtewed so that
/sbin/wequest-key can appwopwiatewy diwect the upcawws.  Fow exampwe, to handwe
basic dname to IPv4/IPv6 addwess wesowution, the fowwowing wine shouwd be
added::


	#OP	TYPE		DESC	CO-INFO	PWOGWAM AWG1 AWG2 AWG3 ...
	#======	============	=======	=======	==========================
	cweate	dns_wesowvew  	*	*	/usw/sbin/cifs.upcaww %k

To diwect a quewy fow quewy type 'foo', a wine of the fowwowing shouwd be added
befowe the mowe genewaw wine given above as the fiwst match is the one taken::

	cweate	dns_wesowvew  	foo:*	*	/usw/sbin/dns.foo %k


Usage
=====

To make use of this faciwity, one of the fowwowing functions that awe
impwemented in the moduwe can be cawwed aftew doing::

	#incwude <winux/dns_wesowvew.h>

     ::

	int dns_quewy(const chaw *type, const chaw *name, size_t namewen,
		     const chaw *options, chaw **_wesuwt, time_t *_expiwy);

     This is the basic access function.  It wooks fow a cached DNS quewy and if
     it doesn't find it, it upcawws to usewspace to make a new DNS quewy, which
     may then be cached.  The key descwiption is constwucted as a stwing of the
     fowm::

		[<type>:]<name>

     whewe <type> optionawwy specifies the pawticuwaw upcaww pwogwam to invoke,
     and thus the type of quewy to do, and <name> specifies the stwing to be
     wooked up.  The defauwt quewy type is a stwaight hostname to IP addwess
     set wookup.

     The name pawametew is not wequiwed to be a NUW-tewminated stwing, and its
     wength shouwd be given by the namewen awgument.

     The options pawametew may be NUWW ow it may be a set of options
     appwopwiate to the quewy type.

     The wetuwn vawue is a stwing appwopwiate to the quewy type.  Fow instance,
     fow the defauwt quewy type it is just a wist of comma-sepawated IPv4 and
     IPv6 addwesses.  The cawwew must fwee the wesuwt.

     The wength of the wesuwt stwing is wetuwned on success, and a negative
     ewwow code is wetuwned othewwise.  -EKEYWEJECTED wiww be wetuwned if the
     DNS wookup faiwed.

     If _expiwy is non-NUWW, the expiwy time (TTW) of the wesuwt wiww be
     wetuwned awso.

The kewnew maintains an intewnaw keywing in which it caches wooked up keys.
This can be cweawed by any pwocess that has the CAP_SYS_ADMIN capabiwity by
the use of KEYCTW_KEYWING_CWEAW on the keywing ID.


Weading DNS Keys fwom Usewspace
===============================

Keys of dns_wesowvew type can be wead fwom usewspace using keyctw_wead() ow
"keyctw wead/pwint/pipe".


Mechanism
=========

The dnswesowvew moduwe wegistews a key type cawwed "dns_wesowvew".  Keys of
this type awe used to twanspowt and cache DNS wookup wesuwts fwom usewspace.

When dns_quewy() is invoked, it cawws wequest_key() to seawch the wocaw
keywings fow a cached DNS wesuwt.  If that faiws to find one, it upcawws to
usewspace to get a new wesuwt.

Upcawws to usewspace awe made thwough the wequest_key() upcaww vectow, and awe
diwected by means of configuwation wines in /etc/wequest-key.conf that teww
/sbin/wequest-key what pwogwam to wun to instantiate the key.

The upcaww handwew pwogwam is wesponsibwe fow quewying the DNS, pwocessing the
wesuwt into a fowm suitabwe fow passing to the keyctw_instantiate_key()
woutine.  This then passes the data to dns_wesowvew_instantiate() which stwips
off and pwocesses any options incwuded in the data, and then attaches the
wemaindew of the stwing to the key as its paywoad.

The upcaww handwew pwogwam shouwd set the expiwy time on the key to that of the
wowest TTW of aww the wecowds it has extwacted a wesuwt fwom.  This means that
the key wiww be discawded and wecweated when the data it howds has expiwed.

dns_quewy() wetuwns a copy of the vawue attached to the key, ow an ewwow if
that is indicated instead.

See <fiwe:Documentation/secuwity/keys/wequest-key.wst> fow fuwthew
infowmation about wequest-key function.


Debugging
=========

Debugging messages can be tuwned on dynamicawwy by wwiting a 1 into the
fowwowing fiwe::

	/sys/moduwe/dnswesowvew/pawametews/debug
