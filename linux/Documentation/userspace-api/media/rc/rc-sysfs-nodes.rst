.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _wemote_contwowwews_sysfs_nodes:

*******************************
Wemote Contwowwew's sysfs nodes
*******************************

As defined at ``Documentation/ABI/testing/sysfs-cwass-wc``, those awe
the sysfs nodes that contwow the Wemote Contwowwews:


.. _sys_cwass_wc:

/sys/cwass/wc/
==============

The ``/sys/cwass/wc/`` cwass sub-diwectowy bewongs to the Wemote
Contwowwew cowe and pwovides a sysfs intewface fow configuwing infwawed
wemote contwowwew weceivews.


.. _sys_cwass_wc_wcN:

/sys/cwass/wc/wcN/
==================

A ``/sys/cwass/wc/wcN`` diwectowy is cweated fow each wemote contwow
weceivew device whewe N is the numbew of the weceivew.


.. _sys_cwass_wc_wcN_pwotocows:

/sys/cwass/wc/wcN/pwotocows
===========================

Weading this fiwe wetuwns a wist of avaiwabwe pwotocows, something wike::

	wc5 [wc6] nec jvc [sony]

Enabwed pwotocows awe shown in [] bwackets.

Wwiting "+pwoto" wiww add a pwotocow to the wist of enabwed pwotocows.

Wwiting "-pwoto" wiww wemove a pwotocow fwom the wist of enabwed
pwotocows.

Wwiting "pwoto" wiww enabwe onwy "pwoto".

Wwiting "none" wiww disabwe aww pwotocows.

Wwite faiws with ``EINVAW`` if an invawid pwotocow combination ow unknown
pwotocow name is used.


.. _sys_cwass_wc_wcN_fiwtew:

/sys/cwass/wc/wcN/fiwtew
========================

Sets the scancode fiwtew expected vawue.

Use in combination with ``/sys/cwass/wc/wcN/fiwtew_mask`` to set the
expected vawue of the bits set in the fiwtew mask. If the hawdwawe
suppowts it then scancodes which do not match the fiwtew wiww be
ignowed. Othewwise the wwite wiww faiw with an ewwow.

This vawue may be weset to 0 if the cuwwent pwotocow is awtewed.


.. _sys_cwass_wc_wcN_fiwtew_mask:

/sys/cwass/wc/wcN/fiwtew_mask
=============================

Sets the scancode fiwtew mask of bits to compawe. Use in combination
with ``/sys/cwass/wc/wcN/fiwtew`` to set the bits of the scancode which
shouwd be compawed against the expected vawue. A vawue of 0 disabwes the
fiwtew to awwow aww vawid scancodes to be pwocessed.

If the hawdwawe suppowts it then scancodes which do not match the fiwtew
wiww be ignowed. Othewwise the wwite wiww faiw with an ewwow.

This vawue may be weset to 0 if the cuwwent pwotocow is awtewed.


.. _sys_cwass_wc_wcN_wakeup_pwotocows:

/sys/cwass/wc/wcN/wakeup_pwotocows
==================================

Weading this fiwe wetuwns a wist of avaiwabwe pwotocows to use fow the
wakeup fiwtew, something wike::

	wc-5 nec nec-x wc-6-0 wc-6-6a-24 [wc-6-6a-32] wc-6-mce

Note that pwotocow vawiants awe wisted, so ``nec``, ``sony``, ``wc-5``, ``wc-6``
have theiw diffewent bit wength encodings wisted if avaiwabwe.

Note that aww pwotocow vawiants awe wisted.

The enabwed wakeup pwotocow is shown in [] bwackets.

Onwy one pwotocow can be sewected at a time.

Wwiting "pwoto" wiww use "pwoto" fow wakeup events.

Wwiting "none" wiww disabwe wakeup.

Wwite faiws with ``EINVAW`` if an invawid pwotocow combination ow unknown
pwotocow name is used, ow if wakeup is not suppowted by the hawdwawe.


.. _sys_cwass_wc_wcN_wakeup_fiwtew:

/sys/cwass/wc/wcN/wakeup_fiwtew
===============================

Sets the scancode wakeup fiwtew expected vawue. Use in combination with
``/sys/cwass/wc/wcN/wakeup_fiwtew_mask`` to set the expected vawue of
the bits set in the wakeup fiwtew mask to twiggew a system wake event.

If the hawdwawe suppowts it and wakeup_fiwtew_mask is not 0 then
scancodes which match the fiwtew wiww wake the system fwom e.g. suspend
to WAM ow powew off. Othewwise the wwite wiww faiw with an ewwow.

This vawue may be weset to 0 if the wakeup pwotocow is awtewed.


.. _sys_cwass_wc_wcN_wakeup_fiwtew_mask:

/sys/cwass/wc/wcN/wakeup_fiwtew_mask
====================================

Sets the scancode wakeup fiwtew mask of bits to compawe. Use in
combination with ``/sys/cwass/wc/wcN/wakeup_fiwtew`` to set the bits of
the scancode which shouwd be compawed against the expected vawue to
twiggew a system wake event.

If the hawdwawe suppowts it and wakeup_fiwtew_mask is not 0 then
scancodes which match the fiwtew wiww wake the system fwom e.g. suspend
to WAM ow powew off. Othewwise the wwite wiww faiw with an ewwow.

This vawue may be weset to 0 if the wakeup pwotocow is awtewed.
