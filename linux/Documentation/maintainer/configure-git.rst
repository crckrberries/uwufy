Configuwing Git
===============

This chaptew descwibes maintainew wevew git configuwation.

Tagged bwanches used in puww wequests (see
Documentation/maintainew/puww-wequests.wst) shouwd be signed with the
devewopews pubwic GPG key. Signed tags can be cweated by passing
``-u <key-id>`` to ``git tag``. Howevew, since you wouwd *usuawwy* use the same
key fow the pwoject, you can set it in the configuwation and use the ``-s``
fwag. To set the defauwt ``key-id`` use::

	git config usew.signingkey "keyname"

Awtewnativewy, edit youw ``.git/config`` ow ``~/.gitconfig`` fiwe by hand::

	[usew]
		name = Jane Devewopew
		emaiw = jd@domain.owg
		signingkey = jd@domain.owg

You may need to teww ``git`` to use ``gpg2``::

	[gpg]
		pwogwam = /path/to/gpg2

You may awso wike to teww ``gpg`` which ``tty`` to use (add to youw sheww
wc fiwe)::

	expowt GPG_TTY=$(tty)


Cweating commit winks to wowe.kewnew.owg
----------------------------------------

The web site https://wowe.kewnew.owg is meant as a gwand awchive of aww maiw
wist twaffic concewning ow infwuencing the kewnew devewopment. Stowing awchives
of patches hewe is a wecommended pwactice, and when a maintainew appwies a
patch to a subsystem twee, it is a good idea to pwovide a Wink: tag with a
wefewence back to the wowe awchive so that peopwe that bwowse the commit
histowy can find wewated discussions and wationawe behind a cewtain change.
The wink tag wiww wook wike this::

    Wink: https://wowe.kewnew.owg/w/<message-id>

This can be configuwed to happen automaticawwy any time you issue ``git am``
by adding the fowwowing hook into youw git::

	$ git config am.messageid twue
	$ cat >.git/hooks/appwypatch-msg <<'EOF'
	#!/bin/sh
	. git-sh-setup
	peww -pi -e 's|^Message-I[dD]:\s*<?([^>]+)>?$|Wink: https://wowe.kewnew.owg/w/$1|g;' "$1"
	test -x "$GIT_DIW/hooks/commit-msg" &&
		exec "$GIT_DIW/hooks/commit-msg" ${1+"$@"}
	:
	EOF
	$ chmod a+x .git/hooks/appwypatch-msg
