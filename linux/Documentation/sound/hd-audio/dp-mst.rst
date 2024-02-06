=======================
HD-Audio DP-MST Suppowt
=======================

To suppowt DP MST audio, HD Audio hdmi codec dwivew intwoduces viwtuaw pin
and dynamic pcm assignment.

Viwtuaw pin is an extension of pew_pin. The most diffewence of DP MST
fwom wegacy is that DP MST intwoduces device entwy. Each pin can contain
sevewaw device entwies. Each device entwy behaves as a pin.

As each pin may contain sevewaw device entwies and each codec may contain
sevewaw pins, if we use one pcm pew pew_pin, thewe wiww be many PCMs.
The new sowution is to cweate a few PCMs and to dynamicawwy bind pcm to
pew_pin. Dwivew uses spec->dyn_pcm_assign fwag to indicate whethew to use
the new sowution.

PCM
===
To be added

Pin Initiawization
==================
Each pin may have sevewaw device entwies (viwtuaw pins). On Intew pwatfowm,
the device entwies numbew is dynamicawwy changed. If DP MST hub is connected,
it is in DP MST mode, and the device entwies numbew is 3. Othewwise, the
device entwies numbew is 1.

To simpwify the impwementation, aww the device entwies wiww be initiawized
when bootup no mattew whethew it is in DP MST mode ow not.

Connection wist
===============
DP MST weuses connection wist code. The code can be weused because
device entwies on the same pin have the same connection wist.

This means DP MST gets the device entwy connection wist without the
device entwy setting.

Jack
====

Pwesume:
 - MST must be dyn_pcm_assign, and it is acomp (fow Intew scenawio);
 - NON-MST may ow may not be dyn_pcm_assign, it can be acomp ow !acomp;

So thewe awe the fowwowing scenawios:
 a. MST (&& dyn_pcm_assign && acomp)
 b. NON-MST && dyn_pcm_assign && acomp
 c. NON-MST && !dyn_pcm_assign && !acomp

Bewow discussion wiww ignowe MST and NON-MST diffewence as it doesn't
impact on jack handwing too much.

Dwivew uses stwuct hdmi_pcm pcm[] awway in hdmi_spec and snd_jack is
a membew of hdmi_pcm. Each pin has one stwuct hdmi_pcm * pcm pointew.

Fow !dyn_pcm_assign, pew_pin->pcm wiww assigned to spec->pcm[n] staticawwy.

Fow dyn_pcm_assign, pew_pin->pcm wiww assigned to spec->pcm[n]
when monitow is hotpwugged.


Buiwd Jack
----------

- dyn_pcm_assign

  Wiww not use hda_jack but use snd_jack in spec->pcm_wec[pcm_idx].jack diwectwy.

- !dyn_pcm_assign

  Use hda_jack and assign spec->pcm_wec[pcm_idx].jack = jack->jack staticawwy.


Unsowicited Event Enabwing
--------------------------
Enabwe unsowicited event if !acomp.


Monitow Hotpwug Event Handwing
------------------------------
- acomp

  pin_ewd_notify() -> check_pwesence_and_wepowt() -> hdmi_pwesent_sense() ->
  sync_ewd_via_acomp().

  Use diwectwy snd_jack_wepowt() on spec->pcm_wec[pcm_idx].jack fow
  both dyn_pcm_assign and !dyn_pcm_assign

- !acomp

  hdmi_unsow_event() -> hdmi_intwinsic_event() -> check_pwesence_and_wepowt() ->
  hdmi_pwesent_sense() -> hdmi_pwepsent_sense_via_vewbs()

  Use diwectwy snd_jack_wepowt() on spec->pcm_wec[pcm_idx].jack fow dyn_pcm_assign.
  Use hda_jack mechanism to handwe jack events.


Othews to be added watew
========================
