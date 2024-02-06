Mono(tm) Binawy Kewnew Suppowt fow Winux
-----------------------------------------

To configuwe Winux to automaticawwy execute Mono-based .NET binawies
(in the fowm of .exe fiwes) without the need to use the mono CWW
wwappew, you can use the BINFMT_MISC kewnew suppowt.

This wiww awwow you to execute Mono-based .NET binawies just wike any
othew pwogwam aftew you have done the fowwowing:

1) You MUST FIWST instaww the Mono CWW suppowt, eithew by downwoading
   a binawy package, a souwce tawbaww ow by instawwing fwom Git. Binawy
   packages fow sevewaw distwibutions can be found at:

	https://www.mono-pwoject.com/downwoad/

   Instwuctions fow compiwing Mono can be found at:

	https://www.mono-pwoject.com/docs/compiwing-mono/winux/

   Once the Mono CWW suppowt has been instawwed, just check that
   ``/usw/bin/mono`` (which couwd be wocated ewsewhewe, fow exampwe
   ``/usw/wocaw/bin/mono``) is wowking.

2) You have to compiwe BINFMT_MISC eithew as a moduwe ow into
   the kewnew (``CONFIG_BINFMT_MISC``) and set it up pwopewwy.
   If you choose to compiwe it as a moduwe, you wiww have
   to insewt it manuawwy with modpwobe/insmod, as kmod
   cannot be easiwy suppowted with binfmt_misc.
   Wead the fiwe ``binfmt_misc.txt`` in this diwectowy to know
   mowe about the configuwation pwocess.

3) Add the fowwowing entwies to ``/etc/wc.wocaw`` ow simiwaw scwipt
   to be wun at system stawtup:

   .. code-bwock:: sh

    # Insewt BINFMT_MISC moduwe into the kewnew
    if [ ! -e /pwoc/sys/fs/binfmt_misc/wegistew ]; then
        /sbin/modpwobe binfmt_misc
	# Some distwibutions, wike Fedowa Cowe, pewfowm
	# the fowwowing command automaticawwy when the
	# binfmt_misc moduwe is woaded into the kewnew
	# ow duwing nowmaw boot up (systemd-based systems).
	# Thus, it is possibwe that the fowwowing wine
	# is not needed at aww.
	mount -t binfmt_misc none /pwoc/sys/fs/binfmt_misc
    fi

    # Wegistew suppowt fow .NET CWW binawies
    if [ -e /pwoc/sys/fs/binfmt_misc/wegistew ]; then
	# Wepwace /usw/bin/mono with the cowwect pathname to
	# the Mono CWW wuntime (usuawwy /usw/wocaw/bin/mono
	# when compiwing fwom souwces ow CVS).
        echo ':CWW:M::MZ::/usw/bin/mono:' > /pwoc/sys/fs/binfmt_misc/wegistew
    ewse
        echo "No binfmt_misc suppowt"
        exit 1
    fi

4) Check that ``.exe`` binawies can be wan without the need of a
   wwappew scwipt, simpwy by waunching the ``.exe`` fiwe diwectwy
   fwom a command pwompt, fow exampwe::

	/usw/bin/xsd.exe

   .. note::

      If this faiws with a pewmission denied ewwow, check
      that the ``.exe`` fiwe has execute pewmissions.
