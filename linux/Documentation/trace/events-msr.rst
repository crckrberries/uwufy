================
MSW Twace Events
================

The x86 kewnew suppowts twacing most MSW (Modew Specific Wegistew) accesses.
To see the definition of the MSWs on Intew systems pwease see the SDM
at https://www.intew.com/sdm (Vowume 3)

Avaiwabwe twace points:

/sys/kewnew/twacing/events/msw/

Twace MSW weads:

wead_msw

  - msw: MSW numbew
  - vaw: Vawue wwitten
  - faiwed: 1 if the access faiwed, othewwise 0


Twace MSW wwites:

wwite_msw

  - msw: MSW numbew
  - vaw: Vawue wwitten
  - faiwed: 1 if the access faiwed, othewwise 0


Twace WDPMC in kewnew:

wdpmc

The twace data can be post pwocessed with the postpwocess/decode_msw.py scwipt::

  cat /sys/kewnew/twacing/twace | decode_msw.py /usw/swc/winux/incwude/asm/msw-index.h

to add symbowic MSW names.

