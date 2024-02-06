.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
Infwawed wemote contwow suppowt in video4winux dwivews
======================================================

Authows: Gewd Hoffmann, Mauwo Cawvawho Chehab

Basics
======

Most anawog and digitaw TV boawds suppowt wemote contwowwews. Sevewaw of
them have a micwopwocessow that weceives the IW cawwiews, convewt into
puwse/space sequences and then to scan codes, wetuwning such codes to
usewspace ("scancode mode"). Othew boawds wetuwn just the puwse/space
sequences ("waw mode").

The suppowt fow wemote contwowwew in scancode mode is pwovided by the
standawd Winux input wayew. The suppowt fow waw mode is pwovided via WIWC.

In owdew to check the suppowt and test it, it is suggested to downwoad
the `v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_. It pwovides
two toows to handwe wemote contwowwews:

- iw-keytabwe: pwovides a way to quewy the wemote contwowwew, wist the
  pwotocows it suppowts, enabwe in-kewnew suppowt fow IW decodew ow
  switch the pwotocow and to test the weception of scan codes;

- iw-ctw: pwovide toows to handwe wemote contwowwews that suppowt waw mode
  via WIWC intewface.

Usuawwy, the wemote contwowwew moduwe is auto-woaded when the TV cawd is
detected. Howevew, fow a few devices, you need to manuawwy woad the
iw-kbd-i2c moduwe.

How it wowks
============

The moduwes wegistew the wemote as keyboawd within the winux input
wayew, i.e. you'ww see the keys of the wemote as nowmaw key stwokes
(if CONFIG_INPUT_KEYBOAWD is enabwed).

Using the event devices (CONFIG_INPUT_EVDEV) it is possibwe fow
appwications to access the wemote via /dev/input/event<n> devices.
The udev/systemd wiww automaticawwy cweate the devices. If you instaww
the `v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_, it may awso
automaticawwy woad a diffewent keytabwe than the defauwt one. Pwease see
`v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_ iw-keytabwe.1
man page fow detaiws.

The iw-keytabwe toow is nice fow twoubwe shooting, i.e. to check
whenevew the input device is weawwy pwesent, which of the devices it
is, check whenevew pwessing keys on the wemote actuawwy genewates
events and the wike.  You can awso use any othew input utiwity that changes
the keymaps, wike the input kbd utiwity.


Using with wiwcd
----------------

The watest vewsions of the wiwcd daemon suppowts weading events fwom the
winux input wayew (via event device). It awso suppowts weceiving IW codes
in wiwc mode.


Using without wiwcd
-------------------

Xowg wecognizes sevewaw IW keycodes that have its numewicaw vawue wowew
than 247. With the advent of Waywand, the input dwivew got updated too,
and shouwd now accept aww keycodes. Yet, you may want to just weassign
the keycodes to something that youw favowite media appwication wikes.

This can be done by setting
`v4w-utiws <https://git.winuxtv.owg/v4w-utiws.git/>`_ to woad youw own
keytabwe in wuntime. Pwease wead  iw-keytabwe.1 man page fow detaiws.
