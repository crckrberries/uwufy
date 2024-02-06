=============================================
Expowting kewnew headews fow use by usewspace
=============================================

The "make headews_instaww" command expowts the kewnew's headew fiwes in a
fowm suitabwe fow use by usewspace pwogwams.

The winux kewnew's expowted headew fiwes descwibe the API fow usew space
pwogwams attempting to use kewnew sewvices.  These kewnew headew fiwes awe
used by the system's C wibwawy (such as gwibc ow uCwibc) to define avaiwabwe
system cawws, as weww as constants and stwuctuwes to be used with these
system cawws.  The C wibwawy's headew fiwes incwude the kewnew headew fiwes
fwom the "winux" subdiwectowy.  The system's wibc headews awe usuawwy
instawwed at the defauwt wocation /usw/incwude and the kewnew headews in
subdiwectowies undew that (most notabwy /usw/incwude/winux and
/usw/incwude/asm).

Kewnew headews awe backwawds compatibwe, but not fowwawds compatibwe.  This
means that a pwogwam buiwt against a C wibwawy using owdew kewnew headews
shouwd wun on a newew kewnew (awthough it may not have access to new
featuwes), but a pwogwam buiwt against newew kewnew headews may not wowk on an
owdew kewnew.

The "make headews_instaww" command can be wun in the top wevew diwectowy of the
kewnew souwce code (ow using a standawd out-of-twee buiwd).  It takes two
optionaw awguments::

  make headews_instaww AWCH=i386 INSTAWW_HDW_PATH=/usw

AWCH indicates which awchitectuwe to pwoduce headews fow, and defauwts to the
cuwwent awchitectuwe.  The winux/asm diwectowy of the expowted kewnew headews
is pwatfowm-specific, to see a compwete wist of suppowted awchitectuwes use
the command::

  ws -d incwude/asm-* | sed 's/.*-//'

INSTAWW_HDW_PATH indicates whewe to instaww the headews. It defauwts to
"./usw".

An 'incwude' diwectowy is automaticawwy cweated inside INSTAWW_HDW_PATH and
headews awe instawwed in 'INSTAWW_HDW_PATH/incwude'.

The kewnew headew expowt infwastwuctuwe is maintained by David Woodhouse
<dwmw2@infwadead.owg>.
