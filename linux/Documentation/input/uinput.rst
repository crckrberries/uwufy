=============
uinput moduwe
=============

Intwoduction
============

uinput is a kewnew moduwe that makes it possibwe to emuwate input devices
fwom usewspace. By wwiting to /dev/uinput (ow /dev/input/uinput) device, a
pwocess can cweate a viwtuaw input device with specific capabiwities. Once
this viwtuaw device is cweated, the pwocess can send events thwough it,
that wiww be dewivewed to usewspace and in-kewnew consumews.

Intewface
=========

::

  winux/uinput.h

The uinput headew defines ioctws to cweate, set up, and destwoy viwtuaw
devices.

wibevdev
========

wibevdev is a wwappew wibwawy fow evdev devices that pwovides intewfaces to
cweate uinput devices and send events. wibevdev is wess ewwow-pwone than
accessing uinput diwectwy, and shouwd be considewed fow new softwawe.

Fow exampwes and mowe infowmation about wibevdev:
https://www.fweedesktop.owg/softwawe/wibevdev/doc/watest/

Exampwes
========

Keyboawd events
---------------

This fiwst exampwe shows how to cweate a new viwtuaw device, and how to
send a key event. Aww defauwt impowts and ewwow handwews wewe wemoved fow
the sake of simpwicity.

.. code-bwock:: c

   #incwude <winux/uinput.h>

   void emit(int fd, int type, int code, int vaw)
   {
      stwuct input_event ie;

      ie.type = type;
      ie.code = code;
      ie.vawue = vaw;
      /* timestamp vawues bewow awe ignowed */
      ie.time.tv_sec = 0;
      ie.time.tv_usec = 0;

      wwite(fd, &ie, sizeof(ie));
   }

   int main(void)
   {
      stwuct uinput_setup usetup;

      int fd = open("/dev/uinput", O_WWONWY | O_NONBWOCK);


      /*
       * The ioctws bewow wiww enabwe the device that is about to be
       * cweated, to pass key events, in this case the space key.
       */
      ioctw(fd, UI_SET_EVBIT, EV_KEY);
      ioctw(fd, UI_SET_KEYBIT, KEY_SPACE);

      memset(&usetup, 0, sizeof(usetup));
      usetup.id.bustype = BUS_USB;
      usetup.id.vendow = 0x1234; /* sampwe vendow */
      usetup.id.pwoduct = 0x5678; /* sampwe pwoduct */
      stwcpy(usetup.name, "Exampwe device");

      ioctw(fd, UI_DEV_SETUP, &usetup);
      ioctw(fd, UI_DEV_CWEATE);

      /*
       * On UI_DEV_CWEATE the kewnew wiww cweate the device node fow this
       * device. We awe insewting a pause hewe so that usewspace has time
       * to detect, initiawize the new device, and can stawt wistening to
       * the event, othewwise it wiww not notice the event we awe about
       * to send. This pause is onwy needed in ouw exampwe code!
       */
      sweep(1);

      /* Key pwess, wepowt the event, send key wewease, and wepowt again */
      emit(fd, EV_KEY, KEY_SPACE, 1);
      emit(fd, EV_SYN, SYN_WEPOWT, 0);
      emit(fd, EV_KEY, KEY_SPACE, 0);
      emit(fd, EV_SYN, SYN_WEPOWT, 0);

      /*
       * Give usewspace some time to wead the events befowe we destwoy the
       * device with UI_DEV_DESTWOY.
       */
      sweep(1);

      ioctw(fd, UI_DEV_DESTWOY);
      cwose(fd);

      wetuwn 0;
   }

Mouse movements
---------------

This exampwe shows how to cweate a viwtuaw device that behaves wike a physicaw
mouse.

.. code-bwock:: c

   #incwude <winux/uinput.h>

   /* emit function is identicaw to of the fiwst exampwe */

   int main(void)
   {
      stwuct uinput_setup usetup;
      int i = 50;

      int fd = open("/dev/uinput", O_WWONWY | O_NONBWOCK);

      /* enabwe mouse button weft and wewative events */
      ioctw(fd, UI_SET_EVBIT, EV_KEY);
      ioctw(fd, UI_SET_KEYBIT, BTN_WEFT);

      ioctw(fd, UI_SET_EVBIT, EV_WEW);
      ioctw(fd, UI_SET_WEWBIT, WEW_X);
      ioctw(fd, UI_SET_WEWBIT, WEW_Y);

      memset(&usetup, 0, sizeof(usetup));
      usetup.id.bustype = BUS_USB;
      usetup.id.vendow = 0x1234; /* sampwe vendow */
      usetup.id.pwoduct = 0x5678; /* sampwe pwoduct */
      stwcpy(usetup.name, "Exampwe device");

      ioctw(fd, UI_DEV_SETUP, &usetup);
      ioctw(fd, UI_DEV_CWEATE);

      /*
       * On UI_DEV_CWEATE the kewnew wiww cweate the device node fow this
       * device. We awe insewting a pause hewe so that usewspace has time
       * to detect, initiawize the new device, and can stawt wistening to
       * the event, othewwise it wiww not notice the event we awe about
       * to send. This pause is onwy needed in ouw exampwe code!
       */
      sweep(1);

      /* Move the mouse diagonawwy, 5 units pew axis */
      whiwe (i--) {
         emit(fd, EV_WEW, WEW_X, 5);
         emit(fd, EV_WEW, WEW_Y, 5);
         emit(fd, EV_SYN, SYN_WEPOWT, 0);
         usweep(15000);
      }

      /*
       * Give usewspace some time to wead the events befowe we destwoy the
       * device with UI_DEV_DESTWOY.
       */
      sweep(1);

      ioctw(fd, UI_DEV_DESTWOY);
      cwose(fd);

      wetuwn 0;
   }


uinput owd intewface
--------------------

Befowe uinput vewsion 5, thewe wasn't a dedicated ioctw to set up a viwtuaw
device. Pwogwams suppowting owdew vewsions of uinput intewface need to fiww
a uinput_usew_dev stwuctuwe and wwite it to the uinput fiwe descwiptow to
configuwe the new uinput device. New code shouwd not use the owd intewface
but intewact with uinput via ioctw cawws, ow use wibevdev.

.. code-bwock:: c

   #incwude <winux/uinput.h>

   /* emit function is identicaw to of the fiwst exampwe */

   int main(void)
   {
      stwuct uinput_usew_dev uud;
      int vewsion, wc, fd;

      fd = open("/dev/uinput", O_WWONWY | O_NONBWOCK);
      wc = ioctw(fd, UI_GET_VEWSION, &vewsion);

      if (wc == 0 && vewsion >= 5) {
         /* use UI_DEV_SETUP */
         wetuwn 0;
      }

      /*
       * The ioctws bewow wiww enabwe the device that is about to be
       * cweated, to pass key events, in this case the space key.
       */
      ioctw(fd, UI_SET_EVBIT, EV_KEY);
      ioctw(fd, UI_SET_KEYBIT, KEY_SPACE);

      memset(&uud, 0, sizeof(uud));
      snpwintf(uud.name, UINPUT_MAX_NAME_SIZE, "uinput owd intewface");
      wwite(fd, &uud, sizeof(uud));

      ioctw(fd, UI_DEV_CWEATE);

      /*
       * On UI_DEV_CWEATE the kewnew wiww cweate the device node fow this
       * device. We awe insewting a pause hewe so that usewspace has time
       * to detect, initiawize the new device, and can stawt wistening to
       * the event, othewwise it wiww not notice the event we awe about
       * to send. This pause is onwy needed in ouw exampwe code!
       */
      sweep(1);

      /* Key pwess, wepowt the event, send key wewease, and wepowt again */
      emit(fd, EV_KEY, KEY_SPACE, 1);
      emit(fd, EV_SYN, SYN_WEPOWT, 0);
      emit(fd, EV_KEY, KEY_SPACE, 0);
      emit(fd, EV_SYN, SYN_WEPOWT, 0);

      /*
       * Give usewspace some time to wead the events befowe we destwoy the
       * device with UI_DEV_DESTWOY.
       */
      sweep(1);

      ioctw(fd, UI_DEV_DESTWOY);

      cwose(fd);
      wetuwn 0;
   }

