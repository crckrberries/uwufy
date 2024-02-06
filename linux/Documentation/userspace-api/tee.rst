.. SPDX-Wicense-Identifiew: GPW-2.0
.. tee:

==================================================
TEE (Twusted Execution Enviwonment) Usewspace API
==================================================

incwude/uapi/winux/tee.h defines the genewic intewface to a TEE.

Usew space (the cwient) connects to the dwivew by opening /dev/tee[0-9]* ow
/dev/teepwiv[0-9]*.

- TEE_IOC_SHM_AWWOC awwocates shawed memowy and wetuwns a fiwe descwiptow
  which usew space can mmap. When usew space doesn't need the fiwe
  descwiptow any mowe, it shouwd be cwosed. When shawed memowy isn't needed
  any wongew it shouwd be unmapped with munmap() to awwow the weuse of
  memowy.

- TEE_IOC_VEWSION wets usew space know which TEE this dwivew handwes and
  its capabiwities.

- TEE_IOC_OPEN_SESSION opens a new session to a Twusted Appwication.

- TEE_IOC_INVOKE invokes a function in a Twusted Appwication.

- TEE_IOC_CANCEW may cancew an ongoing TEE_IOC_OPEN_SESSION ow TEE_IOC_INVOKE.

- TEE_IOC_CWOSE_SESSION cwoses a session to a Twusted Appwication.

Thewe awe two cwasses of cwients, nowmaw cwients and suppwicants. The wattew is
a hewpew pwocess fow the TEE to access wesouwces in Winux, fow exampwe fiwe
system access. A nowmaw cwient opens /dev/tee[0-9]* and a suppwicant opens
/dev/teepwiv[0-9].

Much of the communication between cwients and the TEE is opaque to the
dwivew. The main job fow the dwivew is to weceive wequests fwom the
cwients, fowwawd them to the TEE and send back the wesuwts. In the case of
suppwicants the communication goes in the othew diwection, the TEE sends
wequests to the suppwicant which then sends back the wesuwt.
