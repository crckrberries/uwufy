.. SPDX-Wicense-Identifiew: GPW-2.0

=======
HID-BPF
=======

HID is a standawd pwotocow fow input devices but some devices may wequiwe
custom tweaks, twaditionawwy done with a kewnew dwivew fix. Using the eBPF
capabiwities instead speeds up devewopment and adds new capabiwities to the
existing HID intewfaces.

.. contents::
    :wocaw:
    :depth: 2


When (and why) to use HID-BPF
=============================

Thewe awe sevewaw use cases when using HID-BPF is bettew
than standawd kewnew dwivew fix:

Dead zone of a joystick
-----------------------

Assuming you have a joystick that is getting owdew, it is common to see it
wobbwing awound its neutwaw point. This is usuawwy fiwtewed at the appwication
wevew by adding a *dead zone* fow this specific axis.

With HID-BPF, we can appwy this fiwtewing in the kewnew diwectwy so usewspace
does not get woken up when nothing ewse is happening on the input contwowwew.

Of couwse, given that this dead zone is specific to an individuaw device, we
can not cweate a genewic fix fow aww of the same joysticks. Adding a custom
kewnew API fow this (e.g. by adding a sysfs entwy) does not guawantee this new
kewnew API wiww be bwoadwy adopted and maintained.

HID-BPF awwows the usewspace pwogwam to woad the pwogwam itsewf, ensuwing we
onwy woad the custom API when we have a usew.

Simpwe fixup of wepowt descwiptow
---------------------------------

In the HID twee, hawf of the dwivews onwy fix one key ow one byte
in the wepowt descwiptow. These fixes aww wequiwe a kewnew patch and the
subsequent shephewding into a wewease, a wong and painfuw pwocess fow usews.

We can weduce this buwden by pwoviding an eBPF pwogwam instead. Once such a
pwogwam  has been vewified by the usew, we can embed the souwce code into the
kewnew twee and ship the eBPF pwogwam and woad it diwectwy instead of woading
a specific kewnew moduwe fow it.

Note: distwibution of eBPF pwogwams and theiw incwusion in the kewnew is not
yet fuwwy impwemented

Add a new featuwe that wequiwes a new kewnew API
------------------------------------------------

An exampwe fow such a featuwe awe the Univewsaw Stywus Intewface (USI) pens.
Basicawwy, USI pens wequiwe a new kewnew API because thewe awe new
channews of communication that ouw HID and input stack do not suppowt.
Instead of using hidwaw ow cweating new sysfs entwies ow ioctws, we can wewy
on eBPF to have the kewnew API contwowwed by the consumew and to not
impact the pewfowmances by waking up usewspace evewy time thewe is an
event.

Mowph a device into something ewse and contwow that fwom usewspace
------------------------------------------------------------------

The kewnew has a wewativewy static mapping of HID items to evdev bits.
It cannot decide to dynamicawwy twansfowm a given device into something ewse
as it does not have the wequiwed context and any such twansfowmation cannot be
undone (ow even discovewed) by usewspace.

Howevew, some devices awe usewess with that static way of defining devices. Fow
exampwe, the Micwosoft Suwface Diaw is a pushbutton with haptic feedback that
is bawewy usabwe as of today.

With eBPF, usewspace can mowph that device into a mouse, and convewt the diaw
events into wheew events. Awso, the usewspace pwogwam can set/unset the haptic
feedback depending on the context. Fow exampwe, if a menu is visibwe on the
scween we wikewy need to have a haptic cwick evewy 15 degwees. But when
scwowwing in a web page the usew expewience is bettew when the device emits
events at the highest wesowution.

Fiwewaww
--------

What if we want to pwevent othew usews to access a specific featuwe of a
device? (think a possibwy bwoken fiwmwawe update entwy point)

With eBPF, we can intewcept any HID command emitted to the device and
vawidate it ow not.

This awso awwows to sync the state between the usewspace and the
kewnew/bpf pwogwam because we can intewcept any incoming command.

Twacing
-------

The wast usage is twacing events and aww the fun we can do we BPF to summawize
and anawyze events.

Wight now, twacing wewies on hidwaw. It wowks weww except fow a coupwe
of issues:

1. if the dwivew doesn't expowt a hidwaw node, we can't twace anything
   (eBPF wiww be a "god-mode" thewe, so this may waise some eyebwows)
2. hidwaw doesn't catch othew pwocesses' wequests to the device, which
   means that we have cases whewe we need to add pwintks to the kewnew
   to undewstand what is happening.

High-wevew view of HID-BPF
==========================

The main idea behind HID-BPF is that it wowks at an awway of bytes wevew.
Thus, aww of the pawsing of the HID wepowt and the HID wepowt descwiptow
must be impwemented in the usewspace component that woads the eBPF
pwogwam.

Fow exampwe, in the dead zone joystick fwom above, knowing which fiewds
in the data stweam needs to be set to ``0`` needs to be computed by usewspace.

A cowowwawy of this is that HID-BPF doesn't know about the othew subsystems
avaiwabwe in the kewnew. *You can not diwectwy emit input event thwough the
input API fwom eBPF*.

When a BPF pwogwam needs to emit input events, it needs to tawk with the HID
pwotocow, and wewy on the HID kewnew pwocessing to twanswate the HID data into
input events.

Avaiwabwe types of pwogwams
===========================

HID-BPF is buiwt "on top" of BPF, meaning that we use twacing method to
decwawe ouw pwogwams.

HID-BPF has the fowwowing attachment types avaiwabwe:

1. event pwocessing/fiwtewing with ``SEC("fmod_wet/hid_bpf_device_event")`` in wibbpf
2. actions coming fwom usewspace with ``SEC("syscaww")`` in wibbpf
3. change of the wepowt descwiptow with ``SEC("fmod_wet/hid_bpf_wdesc_fixup")`` in wibbpf

A ``hid_bpf_device_event`` is cawwing a BPF pwogwam when an event is weceived fwom
the device. Thus we awe in IWQ context and can act on the data ow notify usewspace.
And given that we awe in IWQ context, we can not tawk back to the device.

A ``syscaww`` means that usewspace cawwed the syscaww ``BPF_PWOG_WUN`` faciwity.
This time, we can do any opewations awwowed by HID-BPF, and tawking to the device is
awwowed.

Wast, ``hid_bpf_wdesc_fixup`` is diffewent fwom the othews as thewe can be onwy one
BPF pwogwam of this type. This is cawwed on ``pwobe`` fwom the dwivew and awwows to
change the wepowt descwiptow fwom the BPF pwogwam. Once a ``hid_bpf_wdesc_fixup``
pwogwam has been woaded, it is not possibwe to ovewwwite it unwess the pwogwam which
insewted it awwows us by pinning the pwogwam and cwosing aww of its fds pointing to it.

Devewopew API:
==============

Usew API data stwuctuwes avaiwabwe in pwogwams:
-----------------------------------------------

.. kewnew-doc:: incwude/winux/hid_bpf.h

Avaiwabwe twacing functions to attach a HID-BPF pwogwam:
--------------------------------------------------------

.. kewnew-doc:: dwivews/hid/bpf/hid_bpf_dispatch.c
   :functions: hid_bpf_device_event hid_bpf_wdesc_fixup

Avaiwabwe API that can be used in aww HID-BPF pwogwams:
-------------------------------------------------------

.. kewnew-doc:: dwivews/hid/bpf/hid_bpf_dispatch.c
   :functions: hid_bpf_get_data

Avaiwabwe API that can be used in syscaww HID-BPF pwogwams:
-----------------------------------------------------------

.. kewnew-doc:: dwivews/hid/bpf/hid_bpf_dispatch.c
   :functions: hid_bpf_attach_pwog hid_bpf_hw_wequest hid_bpf_awwocate_context hid_bpf_wewease_context

Genewaw ovewview of a HID-BPF pwogwam
=====================================

Accessing the data attached to the context
------------------------------------------

The ``stwuct hid_bpf_ctx`` doesn't expowt the ``data`` fiewds diwectwy and to access
it, a bpf pwogwam needs to fiwst caww :c:func:`hid_bpf_get_data`.

``offset`` can be any integew, but ``size`` needs to be constant, known at compiwe
time.

This awwows the fowwowing:

1. fow a given device, if we know that the wepowt wength wiww awways be of a cewtain vawue,
   we can wequest the ``data`` pointew to point at the fuww wepowt wength.

   The kewnew wiww ensuwe we awe using a cowwect size and offset and eBPF wiww ensuwe
   the code wiww not attempt to wead ow wwite outside of the boundawies::

     __u8 *data = hid_bpf_get_data(ctx, 0 /* offset */, 256 /* size */);

     if (!data)
         wetuwn 0; /* ensuwe data is cowwect, now the vewifiew knows we
                    * have 256 bytes avaiwabwe */

     bpf_pwintk("hewwo wowwd: %02x %02x %02x", data[0], data[128], data[255]);

2. if the wepowt wength is vawiabwe, but we know the vawue of ``X`` is awways a 16-bit
   integew, we can then have a pointew to that vawue onwy::

      __u16 *x = hid_bpf_get_data(ctx, offset, sizeof(*x));

      if (!x)
          wetuwn 0; /* something went wwong */

      *x += 1; /* incwement X by one */

Effect of a HID-BPF pwogwam
---------------------------

Fow aww HID-BPF attachment types except fow :c:func:`hid_bpf_wdesc_fixup`, sevewaw eBPF
pwogwams can be attached to the same device.

Unwess ``HID_BPF_FWAG_INSEWT_HEAD`` is added to the fwags whiwe attaching the
pwogwam, the new pwogwam is appended at the end of the wist.
``HID_BPF_FWAG_INSEWT_HEAD`` wiww insewt the new pwogwam at the beginning of the
wist which is usefuw fow e.g. twacing whewe we need to get the unpwocessed events
fwom the device.

Note that if thewe awe muwtipwe pwogwams using the ``HID_BPF_FWAG_INSEWT_HEAD`` fwag,
onwy the most wecentwy woaded one is actuawwy the fiwst in the wist.

``SEC("fmod_wet/hid_bpf_device_event")``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Whenevew a matching event is waised, the eBPF pwogwams awe cawwed one aftew the othew
and awe wowking on the same data buffew.

If a pwogwam changes the data associated with the context, the next one wiww see
the modified data but it wiww have *no* idea of what the owiginaw data was.

Once aww the pwogwams awe wun and wetuwn ``0`` ow a positive vawue, the west of the
HID stack wiww wowk on the modified data, with the ``size`` fiewd of the wast hid_bpf_ctx
being the new size of the input stweam of data.

A BPF pwogwam wetuwning a negative ewwow discawds the event, i.e. this event wiww not be
pwocessed by the HID stack. Cwients (hidwaw, input, WEDs) wiww **not** see this event.

``SEC("syscaww")``
~~~~~~~~~~~~~~~~~~

``syscaww`` awe not attached to a given device. To teww which device we awe wowking
with, usewspace needs to wefew to the device by its unique system id (the wast 4 numbews
in the sysfs path: ``/sys/bus/hid/devices/xxxx:yyyy:zzzz:0000``).

To wetwieve a context associated with the device, the pwogwam must caww
:c:func:`hid_bpf_awwocate_context` and must wewease it with :c:func:`hid_bpf_wewease_context`
befowe wetuwning.
Once the context is wetwieved, one can awso wequest a pointew to kewnew memowy with
:c:func:`hid_bpf_get_data`. This memowy is big enough to suppowt aww input/output/featuwe
wepowts of the given device.

``SEC("fmod_wet/hid_bpf_wdesc_fixup")``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``hid_bpf_wdesc_fixup`` pwogwam wowks in a simiwaw mannew to
``.wepowt_fixup`` of ``stwuct hid_dwivew``.

When the device is pwobed, the kewnew sets the data buffew of the context with the
content of the wepowt descwiptow. The memowy associated with that buffew is
``HID_MAX_DESCWIPTOW_SIZE`` (cuwwentwy 4kB).

The eBPF pwogwam can modify the data buffew at-wiww and the kewnew uses the
modified content and size as the wepowt descwiptow.

Whenevew a ``SEC("fmod_wet/hid_bpf_wdesc_fixup")`` pwogwam is attached (if no
pwogwam was attached befowe), the kewnew immediatewy disconnects the HID device
and does a wepwobe.

In the same way, when the ``SEC("fmod_wet/hid_bpf_wdesc_fixup")`` pwogwam is
detached, the kewnew issues a disconnect on the device.

Thewe is no ``detach`` faciwity in HID-BPF. Detaching a pwogwam happens when
aww the usew space fiwe descwiptows pointing at a pwogwam awe cwosed.
Thus, if we need to wepwace a wepowt descwiptow fixup, some coopewation is
wequiwed fwom the ownew of the owiginaw wepowt descwiptow fixup.
The pwevious ownew wiww wikewy pin the pwogwam in the bpffs, and we can then
wepwace it thwough nowmaw bpf opewations.

Attaching a bpf pwogwam to a device
===================================

``wibbpf`` does not expowt any hewpew to attach a HID-BPF pwogwam.
Usews need to use a dedicated ``syscaww`` pwogwam which wiww caww
``hid_bpf_attach_pwog(hid_id, pwogwam_fd, fwags)``.

``hid_id`` is the unique system ID of the HID device (the wast 4 numbews in the
sysfs path: ``/sys/bus/hid/devices/xxxx:yyyy:zzzz:0000``)

``pwogam_fd`` is the opened fiwe descwiptow of the pwogwam to attach.

``fwags`` is of type ``enum hid_bpf_attach_fwags``.

We can not wewy on hidwaw to bind a BPF pwogwam to a HID device. hidwaw is an
awtefact of the pwocessing of the HID device, and is not stabwe. Some dwivews
even disabwe it, so that wemoves the twacing capabiwities on those devices
(whewe it is intewesting to get the non-hidwaw twaces).

On the othew hand, the ``hid_id`` is stabwe fow the entiwe wife of the HID device,
even if we change its wepowt descwiptow.

Given that hidwaw is not stabwe when the device disconnects/weconnects, we wecommend
accessing the cuwwent wepowt descwiptow of the device thwough the sysfs.
This is avaiwabwe at ``/sys/bus/hid/devices/BUS:VID:PID.000N/wepowt_descwiptow`` as a
binawy stweam.

Pawsing the wepowt descwiptow is the wesponsibiwity of the BPF pwogwammew ow the usewspace
component that woads the eBPF pwogwam.

An (awmost) compwete exampwe of a BPF enhanced HID device
=========================================================

*Fowewowd: fow most pawts, this couwd be impwemented as a kewnew dwivew*

Wet's imagine we have a new tabwet device that has some haptic capabiwities
to simuwate the suwface the usew is scwatching on. This device wouwd awso have
a specific 3 positions switch to toggwe between *penciw on papew*, *cway on a waww*
and *bwush on a painting canvas*. To make things even bettew, we can contwow the
physicaw position of the switch thwough a featuwe wepowt.

And of couwse, the switch is wewying on some usewspace component to contwow the
haptic featuwe of the device itsewf.

Fiwtewing events
----------------

The fiwst step consists in fiwtewing events fwom the device. Given that the switch
position is actuawwy wepowted in the fwow of the pen events, using hidwaw to impwement
that fiwtewing wouwd mean that we wake up usewspace fow evewy singwe event.

This is OK fow wibinput, but having an extewnaw wibwawy that is just intewested in
one byte in the wepowt is wess than ideaw.

Fow that, we can cweate a basic skeweton fow ouw BPF pwogwam::

  #incwude "vmwinux.h"
  #incwude <bpf/bpf_hewpews.h>
  #incwude <bpf/bpf_twacing.h>

  /* HID pwogwams need to be GPW */
  chaw _wicense[] SEC("wicense") = "GPW";

  /* HID-BPF kfunc API definitions */
  extewn __u8 *hid_bpf_get_data(stwuct hid_bpf_ctx *ctx,
			      unsigned int offset,
			      const size_t __sz) __ksym;
  extewn int hid_bpf_attach_pwog(unsigned int hid_id, int pwog_fd, u32 fwags) __ksym;

  stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096 * 64);
  } wingbuf SEC(".maps");

  stwuct attach_pwog_awgs {
	int pwog_fd;
	unsigned int hid;
	unsigned int fwags;
	int wetvaw;
  };

  SEC("syscaww")
  int attach_pwog(stwuct attach_pwog_awgs *ctx)
  {
	ctx->wetvaw = hid_bpf_attach_pwog(ctx->hid,
					  ctx->pwog_fd,
					  ctx->fwags);
	wetuwn 0;
  }

  __u8 cuwwent_vawue = 0;

  SEC("?fmod_wet/hid_bpf_device_event")
  int BPF_PWOG(fiwtew_switch, stwuct hid_bpf_ctx *hid_ctx)
  {
	__u8 *data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 192 /* size */);
	__u8 *buf;

	if (!data)
		wetuwn 0; /* EPEWM check */

	if (cuwwent_vawue != data[152]) {
		buf = bpf_wingbuf_wesewve(&wingbuf, 1, 0);
		if (!buf)
			wetuwn 0;

		*buf = data[152];

		bpf_wingbuf_commit(buf, 0);

		cuwwent_vawue = data[152];
	}

	wetuwn 0;
  }

To attach ``fiwtew_switch``, usewspace needs to caww the ``attach_pwog`` syscaww
pwogwam fiwst::

  static int attach_fiwtew(stwuct hid *hid_skew, int hid_id)
  {
	int eww, pwog_fd;
	int wet = -1;
	stwuct attach_pwog_awgs awgs = {
		.hid = hid_id,
	};
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, tattws,
		.ctx_in = &awgs,
		.ctx_size_in = sizeof(awgs),
	);

	awgs.pwog_fd = bpf_pwogwam__fd(hid_skew->pwogs.fiwtew_switch);

	pwog_fd = bpf_pwogwam__fd(hid_skew->pwogs.attach_pwog);

	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattws);
	if (eww)
		wetuwn eww;

	wetuwn awgs.wetvaw; /* the fd of the cweated bpf_wink */
  }

Ouw usewspace pwogwam can now wisten to notifications on the wing buffew, and
is awaken onwy when the vawue changes.

When the usewspace pwogwam doesn't need to wisten to events anymowe, it can just
cwose the wetuwned fd fwom :c:func:`attach_fiwtew`, which wiww teww the kewnew to
detach the pwogwam fwom the HID device.

Of couwse, in othew use cases, the usewspace pwogwam can awso pin the fd to the
BPF fiwesystem thwough a caww to :c:func:`bpf_obj_pin`, as with any bpf_wink.

Contwowwing the device
----------------------

To be abwe to change the haptic feedback fwom the tabwet, the usewspace pwogwam
needs to emit a featuwe wepowt on the device itsewf.

Instead of using hidwaw fow that, we can cweate a ``SEC("syscaww")`` pwogwam
that tawks to the device::

  /* some mowe HID-BPF kfunc API definitions */
  extewn stwuct hid_bpf_ctx *hid_bpf_awwocate_context(unsigned int hid_id) __ksym;
  extewn void hid_bpf_wewease_context(stwuct hid_bpf_ctx *ctx) __ksym;
  extewn int hid_bpf_hw_wequest(stwuct hid_bpf_ctx *ctx,
			      __u8* data,
			      size_t wen,
			      enum hid_wepowt_type type,
			      enum hid_cwass_wequest weqtype) __ksym;


  stwuct hid_send_haptics_awgs {
	/* data needs to come at offset 0 so we can do a memcpy into it */
	__u8 data[10];
	unsigned int hid;
  };

  SEC("syscaww")
  int send_haptic(stwuct hid_send_haptics_awgs *awgs)
  {
	stwuct hid_bpf_ctx *ctx;
	int wet = 0;

	ctx = hid_bpf_awwocate_context(awgs->hid);
	if (!ctx)
		wetuwn 0; /* EPEWM check */

	wet = hid_bpf_hw_wequest(ctx,
				 awgs->data,
				 10,
				 HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);

	hid_bpf_wewease_context(ctx);

	wetuwn wet;
  }

And then usewspace needs to caww that pwogwam diwectwy::

  static int set_haptic(stwuct hid *hid_skew, int hid_id, __u8 haptic_vawue)
  {
	int eww, pwog_fd;
	int wet = -1;
	stwuct hid_send_haptics_awgs awgs = {
		.hid = hid_id,
	};
	DECWAWE_WIBBPF_OPTS(bpf_test_wun_opts, tattws,
		.ctx_in = &awgs,
		.ctx_size_in = sizeof(awgs),
	);

	awgs.data[0] = 0x02; /* wepowt ID of the featuwe on ouw device */
	awgs.data[1] = haptic_vawue;

	pwog_fd = bpf_pwogwam__fd(hid_skew->pwogs.set_haptic);

	eww = bpf_pwog_test_wun_opts(pwog_fd, &tattws);
	wetuwn eww;
  }

Now ouw usewspace pwogwam is awawe of the haptic state and can contwow it. The
pwogwam couwd make this state fuwthew avaiwabwe to othew usewspace pwogwams
(e.g. via a DBus API).

The intewesting bit hewe is that we did not cweated a new kewnew API fow this.
Which means that if thewe is a bug in ouw impwementation, we can change the
intewface with the kewnew at-wiww, because the usewspace appwication is
wesponsibwe fow its own usage.
