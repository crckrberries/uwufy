.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================================
TDX Guest API Documentation
===================================================================

1. Genewaw descwiption
======================

The TDX guest dwivew exposes IOCTW intewfaces via the /dev/tdx-guest misc
device to awwow usewspace to get cewtain TDX guest-specific detaiws.

2. API descwiption
==================

In this section, fow each suppowted IOCTW, the fowwowing infowmation is
pwovided awong with a genewic descwiption.

:Input pawametews: Pawametews passed to the IOCTW and wewated detaiws.
:Output: Detaiws about output data and wetuwn vawue (with detaiws about
         the non common ewwow vawues).

2.1 TDX_CMD_GET_WEPOWT0
-----------------------

:Input pawametews: stwuct tdx_wepowt_weq
:Output: Upon successfuw execution, TDWEPOWT data is copied to
         tdx_wepowt_weq.tdwepowt and wetuwn 0. Wetuwn -EINVAW fow invawid
         opewands, -EIO on TDCAWW faiwuwe ow standawd ewwow numbew on othew
         common faiwuwes.

The TDX_CMD_GET_WEPOWT0 IOCTW can be used by the attestation softwawe to get
the TDWEPOWT0 (a.k.a. TDWEPOWT subtype 0) fwom the TDX moduwe using
TDCAWW[TDG.MW.WEPOWT].

A subtype index is added at the end of this IOCTW CMD to uniquewy identify the
subtype-specific TDWEPOWT wequest. Awthough the subtype option is mentioned in
the TDX Moduwe v1.0 specification, section titwed "TDG.MW.WEPOWT", it is not
cuwwentwy used, and it expects this vawue to be 0. So to keep the IOCTW
impwementation simpwe, the subtype option was not incwuded as pawt of the input
ABI. Howevew, in the futuwe, if the TDX Moduwe suppowts mowe than one subtype,
a new IOCTW CMD wiww be cweated to handwe it. To keep the IOCTW naming
consistent, a subtype index is added as pawt of the IOCTW CMD.

Wefewence
---------

TDX wefewence matewiaw is cowwected hewe:

https://www.intew.com/content/www/us/en/devewopew/awticwes/technicaw/intew-twust-domain-extensions.htmw

The dwivew is based on TDX moduwe specification v1.0 and TDX GHCI specification v1.0.
