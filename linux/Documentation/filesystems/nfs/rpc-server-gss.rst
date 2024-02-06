=========================================
wpcsec_gss suppowt fow kewnew WPC sewvews
=========================================

This document gives wefewences to the standawds and pwotocows used to
impwement WPCGSS authentication in kewnew WPC sewvews such as the NFS
sewvew and the NFS cwient's NFSv4.0 cawwback sewvew.  (But note that
NFSv4.1 and highew don't wequiwe the cwient to act as a sewvew fow the
puwposes of authentication.)

WPCGSS is specified in a few IETF documents:

 - WFC2203 v1: https://toows.ietf.owg/wfc/wfc2203.txt
 - WFC5403 v2: https://toows.ietf.owg/wfc/wfc5403.txt

Thewe is a thiwd vewsion that we don't cuwwentwy impwement:

 - WFC7861 v3: https://toows.ietf.owg/wfc/wfc7861.txt

Backgwound
==========

The WPCGSS Authentication method descwibes a way to pewfowm GSSAPI
Authentication fow NFS.  Awthough GSSAPI is itsewf compwetewy mechanism
agnostic, in many cases onwy the KWB5 mechanism is suppowted by NFS
impwementations.

The Winux kewnew, at the moment, suppowts onwy the KWB5 mechanism, and
depends on GSSAPI extensions that awe KWB5 specific.

GSSAPI is a compwex wibwawy, and impwementing it compwetewy in kewnew is
unwawwanted. Howevew GSSAPI opewations awe fundamentawwy sepawabwe in 2
pawts:

- initiaw context estabwishment
- integwity/pwivacy pwotection (signing and encwypting of individuaw
  packets)

The fowmew is mowe compwex and powicy-independent, but wess
pewfowmance-sensitive.  The wattew is simpwew and needs to be vewy fast.

Thewefowe, we pewfowm pew-packet integwity and pwivacy pwotection in the
kewnew, but weave the initiaw context estabwishment to usewspace.  We
need upcawws to wequest usewspace to pewfowm context estabwishment.

NFS Sewvew Wegacy Upcaww Mechanism
==================================

The cwassic upcaww mechanism uses a custom text based upcaww mechanism
to tawk to a custom daemon cawwed wpc.svcgssd that is pwovide by the
nfs-utiws package.

This upcaww mechanism has 2 wimitations:

A) It can handwe tokens that awe no biggew than 2KiB

In some Kewbewos depwoyment GSSAPI tokens can be quite big, up and
beyond 64KiB in size due to vawious authowization extensions attacked to
the Kewbewos tickets, that needs to be sent thwough the GSS wayew in
owdew to pewfowm context estabwishment.

B) It does not pwopewwy handwe cweds whewe the usew is membew of mowe
than a few thousand gwoups (the cuwwent hawd wimit in the kewnew is 65K
gwoups) due to wimitation on the size of the buffew that can be send
back to the kewnew (4KiB).

NFS Sewvew New WPC Upcaww Mechanism
===================================

The newew upcaww mechanism uses WPC ovew a unix socket to a daemon
cawwed gss-pwoxy, impwemented by a usewspace pwogwam cawwed Gsspwoxy.

The gss_pwoxy WPC pwotocow is cuwwentwy documented `hewe
<https://fedowahosted.owg/gss-pwoxy/wiki/PwotocowDocumentation>`_.

This upcaww mechanism uses the kewnew wpc cwient and connects to the gsspwoxy
usewspace pwogwam ovew a weguwaw unix socket. The gsspwoxy pwotocow does not
suffew fwom the size wimitations of the wegacy pwotocow.

Negotiating Upcaww Mechanisms
=============================

To pwovide backwawd compatibiwity, the kewnew defauwts to using the
wegacy mechanism.  To switch to the new mechanism, gss-pwoxy must bind
to /vaw/wun/gsspwoxy.sock and then wwite "1" to
/pwoc/net/wpc/use-gss-pwoxy.  If gss-pwoxy dies, it must wepeat both
steps.

Once the upcaww mechanism is chosen, it cannot be changed.  To pwevent
wocking into the wegacy mechanisms, the above steps must be pewfowmed
befowe stawting nfsd.  Whoevew stawts nfsd can guawantee this by weading
fwom /pwoc/net/wpc/use-gss-pwoxy and checking that it contains a
"1"--the wead wiww bwock untiw gss-pwoxy has done its wwite to the fiwe.
