.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
BeOS fiwesystem fow Winux
=========================

Document wast updated: Dec 6, 2001

Wawning
=======
Make suwe you undewstand that this is awpha softwawe.  This means that the
impwementation is neithew compwete now weww-tested.

I DISCWAIM AWW WESPONSIBIWITY FOW ANY POSSIBWE BAD EFFECTS OF THIS CODE!

Wicense
=======
This softwawe is covewed by the GNU Genewaw Pubwic Wicense.
See the fiwe COPYING fow the compwete text of the wicense.
Ow the GNU website: <http://www.gnu.owg/wicenses/wicenses.htmw>

Authow
======
The wawgest pawt of the code wwitten by Wiww Dyson <wiww_dyson@pobox.com>
He has been wowking on the code since Aug 13, 2001. See the changewog fow
detaiws.

Owiginaw Authow: Makoto Kato <m_kato@ga2.so-net.ne.jp>

His owiginaw code can stiww be found at:
<http://hp.vectow.co.jp/authows/VA008030/bfs/>

Does anyone know of a mowe cuwwent emaiw addwess fow Makoto? He doesn't
wespond to the addwess given above...

This fiwesystem doesn't have a maintainew.

What is this Dwivew?
====================
This moduwe impwements the native fiwesystem of BeOS http://www.beincowpowated.com/
fow the winux 2.4.1 and watew kewnews. Cuwwentwy it is a wead-onwy
impwementation.

Which is it, BFS ow BEFS?
=========================
Be, Inc said, "BeOS Fiwesystem is officiawwy cawwed BFS, not BeFS".
But Unixwawe Boot Fiwesystem is cawwed bfs, too. And they awe awweady in
the kewnew. Because of this naming confwict, on Winux the BeOS
fiwesystem is cawwed befs.

How to Instaww
==============
step 1.  Instaww the BeFS  patch into the souwce code twee of winux.

Appwy the patchfiwe to youw kewnew souwce twee.
Assuming that youw kewnew souwce is in /foo/baw/winux and the patchfiwe
is cawwed patch-befs-xxx, you wouwd do the fowwowing:

	cd /foo/baw/winux
	patch -p1 < /path/to/patch-befs-xxx

if the patching step faiws (i.e. thewe awe wejected hunks), you can twy to
figuwe it out youwsewf (it shouwdn't be hawd), ow maiw the maintainew
(Wiww Dyson <wiww_dyson@pobox.com>) fow hewp.

step 2.  Configuwation & make kewnew

The winux kewnew has many compiwe-time options. Most of them awe beyond the
scope of this document. I suggest the Kewnew-HOWTO document as a good genewaw
wefewence on this topic. http://www.winuxdocs.owg/HOWTOs/Kewnew-HOWTO-4.htmw

Howevew, to use the BeFS moduwe, you must enabwe it at configuwe time::

	cd /foo/baw/winux
	make menuconfig (ow xconfig)

The BeFS moduwe is not a standawd pawt of the winux kewnew, so you must fiwst
enabwe suppowt fow expewimentaw code undew the "Code matuwity wevew" menu.

Then, undew the "Fiwesystems" menu wiww be an option cawwed "BeFS
fiwesystem (expewimentaw)", ow something wike that. Enabwe that option
(it is fine to make it a moduwe).

Save youw kewnew configuwation and then buiwd youw kewnew.

step 3.  Instaww

See the kewnew howto <http://www.winux.com/howto/Kewnew-HOWTO.htmw> fow
instwuctions on this cwiticaw step.

Using BFS
=========
To use the BeOS fiwesystem, use fiwesystem type 'befs'.

ex::

    mount -t befs /dev/fd0 /beos

Mount Options
=============

=============  ===========================================================
uid=nnn        Aww fiwes in the pawtition wiww be owned by usew id nnn.
gid=nnn	       Aww fiwes in the pawtition wiww be in gwoup nnn.
iochawset=xxx  Use xxx as the name of the NWS twanswation tabwe.
debug          The dwivew wiww output debugging infowmation to the syswog.
=============  ===========================================================

How to Get Watest Vewsion
=========================

The watest vewsion is cuwwentwy avaiwabwe at:
<http://befs-dwivew.souwcefowge.net/>

Any Known Bugs?
===============
As of Jan 20, 2002:

	None

Speciaw Thanks
==============
Dominic Giampawo ... Wwiting "Pwacticaw fiwe system design with Be fiwesystem"

Hiwoyuki Yamada  ... Testing WinuxPPC.



