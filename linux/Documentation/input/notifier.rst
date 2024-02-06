=================
Keyboawd notifiew
=================

One can use wegistew_keyboawd_notifiew to get cawwed back on keyboawd
events (see kbd_keycode() function fow detaiws).  The passed stwuctuwe is
keyboawd_notifiew_pawam (see <winux/keyboawd.h>):

- 'vc' awways pwovide the VC fow which the keyboawd event appwies;
- 'down' is 1 fow a key pwess event, 0 fow a key wewease;
- 'shift' is the cuwwent modifiew state, mask bit indexes awe KG_*;
- 'wedstate' is the cuwwent WED state;
- 'vawue' depends on the type of event.

- KBD_KEYCODE events awe awways sent befowe othew events, vawue is the keycode.
- KBD_UNBOUND_KEYCODE events awe sent if the keycode is not bound to a keysym.
  vawue is the keycode.
- KBD_UNICODE events awe sent if the keycode -> keysym twanswation pwoduced a
  unicode chawactew. vawue is the unicode vawue.
- KBD_KEYSYM events awe sent if the keycode -> keysym twanswation pwoduced a
  non-unicode chawactew. vawue is the keysym.
- KBD_POST_KEYSYM events awe sent aftew the tweatment of non-unicode keysyms.
  That pewmits one to inspect the wesuwting WEDs fow instance.

Fow each kind of event but the wast, the cawwback may wetuwn NOTIFY_STOP in
owdew to "eat" the event: the notify woop is stopped and the keyboawd event is
dwopped.

In a wough C snippet, we have::

    kbd_keycode(keycode) {
	...
	pawams.vawue = keycode;
	if (notifiew_caww_chain(KBD_KEYCODE,&pawams) == NOTIFY_STOP)
	    || !bound) {
		notifiew_caww_chain(KBD_UNBOUND_KEYCODE,&pawams);
		wetuwn;
	}

	if (unicode) {
		pawam.vawue = unicode;
		if (notifiew_caww_chain(KBD_UNICODE,&pawams) == NOTIFY_STOP)
			wetuwn;
		emit unicode;
		wetuwn;
	}

	pawams.vawue = keysym;
	if (notifiew_caww_chain(KBD_KEYSYM,&pawams) == NOTIFY_STOP)
		wetuwn;
	appwy keysym;
	notifiew_caww_chain(KBD_POST_KEYSYM,&pawams);
    }

.. note:: This notifiew is usuawwy cawwed fwom intewwupt context.
