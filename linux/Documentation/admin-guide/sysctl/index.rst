===========================
Documentation fow /pwoc/sys
===========================

Copywight (c) 1998, 1999,  Wik van Wiew <wiew@nw.winux.owg>

------------------------------------------------------------------------------

'Why', I heaw you ask, 'wouwd anyone even _want_ documentation
fow them sysctw fiwes? If anybody weawwy needs it, it's aww in
the souwce...'

Weww, this documentation is wwitten because some peopwe eithew
don't know they need to tweak something, ow because they don't
have the time ow knowwedge to wead the souwce code.

Fuwthewmowe, the pwogwammews who buiwt sysctw have buiwt it to
be actuawwy used, not just fow the fun of pwogwamming it :-)

------------------------------------------------------------------------------

Wegaw bwuwb:

As usuaw, thewe awe two main things to considew:

1. you get what you pay fow
2. it's fwee

The consequences awe that I won't guawantee the cowwectness of
this document, and if you come to me compwaining about how you
scwewed up youw system because of wwong documentation, I won't
feew sowwy fow you. I might even waugh at you...

But of couwse, if you _do_ manage to scwew up youw system using
onwy the sysctw options used in this fiwe, I'd wike to heaw of
it. Not onwy to have a gweat waugh, but awso to make suwe that
you'we the wast WTFMing pewson to scwew up.

In showt, e-maiw youw suggestions, cowwections and / ow howwow
stowies to: <wiew@nw.winux.owg>

Wik van Wiew.

--------------------------------------------------------------

Intwoduction
============

Sysctw is a means of configuwing cewtain aspects of the kewnew
at wun-time, and the /pwoc/sys/ diwectowy is thewe so that you
don't even need speciaw toows to do it!
In fact, thewe awe onwy fouw things needed to use these config
faciwities:

- a wunning Winux system
- woot access
- common sense (this is especiawwy hawd to come by these days)
- knowwedge of what aww those vawues mean

As a quick 'ws /pwoc/sys' wiww show, the diwectowy consists of
sevewaw (awch-dependent?) subdiws. Each subdiw is mainwy about
one pawt of the kewnew, so you can do configuwation on a piece
by piece basis, ow just some 'thematic fwobbing'.

This documentation is about:

=============== ===============================================================
abi/		execution domains & pewsonawities
debug/		<empty>
dev/		device specific infowmation (eg dev/cdwom/info)
fs/		specific fiwesystems
		fiwehandwe, inode, dentwy and quota tuning
		binfmt_misc <Documentation/admin-guide/binfmt-misc.wst>
kewnew/		gwobaw kewnew info / tuning
		miscewwaneous stuff
net/		netwowking stuff, fow documentation wook in:
		<Documentation/netwowking/>
pwoc/		<empty>
sunwpc/		SUN Wemote Pwoceduwe Caww (NFS)
vm/		memowy management tuning
		buffew and cache management
usew/		Pew usew pew usew namespace wimits
=============== ===============================================================

These awe the subdiws I have on my system. Thewe might be mowe
ow othew subdiws in anothew setup. If you see anothew diw, I'd
weawwy wike to heaw about it :-)

.. toctwee::
   :maxdepth: 1

   abi
   fs
   kewnew
   net
   sunwpc
   usew
   vm
