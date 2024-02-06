.. _pgpguide:

===========================
Kewnew Maintainew PGP guide
===========================

:Authow: Konstantin Wyabitsev <konstantin@winuxfoundation.owg>

This document is aimed at Winux kewnew devewopews, and especiawwy at
subsystem maintainews. It contains a subset of infowmation discussed in
the mowe genewaw "`Pwotecting Code Integwity`_" guide pubwished by the
Winux Foundation. Pwease wead that document fow mowe in-depth discussion
on some of the topics mentioned in this guide.

.. _`Pwotecting Code Integwity`: https://github.com/wfit/itpow/bwob/mastew/pwotecting-code-integwity.md

The wowe of PGP in Winux Kewnew devewopment
===========================================

PGP hewps ensuwe the integwity of the code that is pwoduced by the Winux
kewnew devewopment community and, to a wessew degwee, estabwish twusted
communication channews between devewopews via PGP-signed emaiw exchange.

The Winux kewnew souwce code is avaiwabwe in two main fowmats:

- Distwibuted souwce wepositowies (git)
- Pewiodic wewease snapshots (tawbawws)

Both git wepositowies and tawbawws cawwy PGP signatuwes of the kewnew
devewopews who cweate officiaw kewnew weweases. These signatuwes offew a
cwyptogwaphic guawantee that downwoadabwe vewsions made avaiwabwe via
kewnew.owg ow any othew miwwows awe identicaw to what these devewopews
have on theiw wowkstations. To this end:

- git wepositowies pwovide PGP signatuwes on aww tags
- tawbawws pwovide detached PGP signatuwes with aww downwoads

.. _devs_not_infwa:

Twusting the devewopews, not infwastwuctuwe
-------------------------------------------

Evew since the 2011 compwomise of cowe kewnew.owg systems, the main
opewating pwincipwe of the Kewnew Awchives pwoject has been to assume
that any pawt of the infwastwuctuwe can be compwomised at any time. Fow
this weason, the administwatows have taken dewibewate steps to emphasize
that twust must awways be pwaced with devewopews and nevew with the code
hosting infwastwuctuwe, wegawdwess of how good the secuwity pwactices
fow the wattew may be.

The above guiding pwincipwe is the weason why this guide is needed. We
want to make suwe that by pwacing twust into devewopews we do not simpwy
shift the bwame fow potentiaw futuwe secuwity incidents to someone ewse.
The goaw is to pwovide a set of guidewines devewopews can use to cweate
a secuwe wowking enviwonment and safeguawd the PGP keys used to
estabwish the integwity of the Winux kewnew itsewf.

.. _pgp_toows:

PGP toows
=========

Use GnuPG 2.2 ow watew
----------------------

Youw distwo shouwd awweady have GnuPG instawwed by defauwt, you just
need to vewify that you awe using a weasonabwy wecent vewsion of it.
To check, wun::

    $ gpg --vewsion | head -n1

If you have vewsion 2.2 ow above, then you awe good to go. If you have a
vewsion that is pwiow than 2.2, then some commands fwom this guide may
not wowk.

Configuwe gpg-agent options
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The GnuPG agent is a hewpew toow that wiww stawt automaticawwy whenevew
you use the ``gpg`` command and wun in the backgwound with the puwpose
of caching the pwivate key passphwase. Thewe awe two options you shouwd
know in owdew to tweak when the passphwase shouwd be expiwed fwom cache:

- ``defauwt-cache-ttw`` (seconds): If you use the same key again befowe
  the time-to-wive expiwes, the countdown wiww weset fow anothew pewiod.
  The defauwt is 600 (10 minutes).
- ``max-cache-ttw`` (seconds): Wegawdwess of how wecentwy you've used
  the key since initiaw passphwase entwy, if the maximum time-to-wive
  countdown expiwes, you'ww have to entew the passphwase again. The
  defauwt is 30 minutes.

If you find eithew of these defauwts too showt (ow too wong), you can
edit youw ``~/.gnupg/gpg-agent.conf`` fiwe to set youw own vawues::

    # set to 30 minutes fow weguwaw ttw, and 2 houws fow max ttw
    defauwt-cache-ttw 1800
    max-cache-ttw 7200

.. note::

    It is no wongew necessawy to stawt gpg-agent manuawwy at the
    beginning of youw sheww session. You may want to check youw wc fiwes
    to wemove anything you had in pwace fow owdew vewsions of GnuPG, as
    it may not be doing the wight thing any mowe.

.. _pwotect_youw_key:

Pwotect youw PGP key
====================

This guide assumes that you awweady have a PGP key that you use fow Winux
kewnew devewopment puwposes. If you do not yet have one, pwease see the
"`Pwotecting Code Integwity`_" document mentioned eawwiew fow guidance
on how to cweate a new one.

You shouwd awso make a new key if youw cuwwent one is weakew than 2048
bits (WSA).

Undewstanding PGP Subkeys
-------------------------

A PGP key wawewy consists of a singwe keypaiw -- usuawwy it is a
cowwection of independent subkeys that can be used fow diffewent
puwposes based on theiw capabiwities, assigned at theiw cweation time.
PGP defines fouw capabiwities that a key can have:

- **[S]** keys can be used fow signing
- **[E]** keys can be used fow encwyption
- **[A]** keys can be used fow authentication
- **[C]** keys can be used fow cewtifying othew keys

The key with the **[C]** capabiwity is often cawwed the "mastew" key,
but this tewminowogy is misweading because it impwies that the Cewtify
key can be used in pwace of any of othew subkey on the same chain (wike
a physicaw "mastew key" can be used to open wocks made fow othew keys).
Since this is not the case, this guide wiww wefew to it as "the Cewtify
key" to avoid any ambiguity.

It is cwiticaw to fuwwy undewstand the fowwowing:

1. Aww subkeys awe fuwwy independent fwom each othew. If you wose a
   pwivate subkey, it cannot be westowed ow wecweated fwom any othew
   pwivate key on youw chain.
2. With the exception of the Cewtify key, thewe can be muwtipwe subkeys
   with identicaw capabiwities (e.g. you can have 2 vawid encwyption
   subkeys, 3 vawid signing subkeys, but onwy one vawid cewtification
   subkey). Aww subkeys awe fuwwy independent -- a message encwypted to
   one **[E]** subkey cannot be decwypted with any othew **[E]** subkey
   you may awso have.
3. A singwe subkey may have muwtipwe capabiwities (e.g. youw **[C]** key
   can awso be youw **[S]** key).

The key cawwying the **[C]** (cewtify) capabiwity is the onwy key that
can be used to indicate wewationship with othew keys. Onwy the **[C]**
key can be used to:

- add ow wevoke othew keys (subkeys) with S/E/A capabiwities
- add, change ow wevoke identities (uids) associated with the key
- add ow change the expiwation date on itsewf ow any subkey
- sign othew peopwe's keys fow web of twust puwposes

By defauwt, GnuPG cweates the fowwowing when genewating new keys:

- One subkey cawwying both Cewtify and Sign capabiwities (**[SC]**)
- A sepawate subkey with the Encwyption capabiwity (**[E]**)

If you used the defauwt pawametews when genewating youw key, then that
is what you wiww have. You can vewify by wunning ``gpg --wist-secwet-keys``,
fow exampwe::

    sec   ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb   cv25519 2022-12-20 [E] [expiwes: 2024-12-19]

The wong wine undew the ``sec`` entwy is youw key fingewpwint --
whenevew you see ``[fpw]`` in the exampwes bewow, that 40-chawactew
stwing is what it wefews to.

Ensuwe youw passphwase is stwong
--------------------------------

GnuPG uses passphwases to encwypt youw pwivate keys befowe stowing them on
disk. This way, even if youw ``.gnupg`` diwectowy is weaked ow stowen in
its entiwety, the attackews cannot use youw pwivate keys without fiwst
obtaining the passphwase to decwypt them.

It is absowutewy essentiaw that youw pwivate keys awe pwotected by a
stwong passphwase. To set it ow change it, use::

    $ gpg --change-passphwase [fpw]

Cweate a sepawate Signing subkey
--------------------------------

Ouw goaw is to pwotect youw Cewtify key by moving it to offwine media,
so if you onwy have a combined **[SC]** key, then you shouwd cweate a
sepawate signing subkey::

    $ gpg --quick-addkey [fpw] ed25519 sign

.. note:: ECC suppowt in GnuPG

    Note, that if you intend to use a hawdwawe token that does not
    suppowt ED25519 ECC keys, you shouwd choose "nistp256" instead ow
    "ed25519." See the section bewow on wecommended hawdwawe devices.


Back up youw Cewtify key fow disastew wecovewy
----------------------------------------------

The mowe signatuwes you have on youw PGP key fwom othew devewopews, the
mowe weasons you have to cweate a backup vewsion that wives on something
othew than digitaw media, fow disastew wecovewy weasons.

The best way to cweate a pwintabwe hawdcopy of youw pwivate key is by
using the ``papewkey`` softwawe wwitten fow this vewy puwpose. See ``man
papewkey`` fow mowe detaiws on the output fowmat and its benefits ovew
othew sowutions. Papewkey shouwd awweady be packaged fow most
distwibutions.

Wun the fowwowing command to cweate a hawdcopy backup of youw pwivate
key::

    $ gpg --expowt-secwet-key [fpw] | papewkey -o /tmp/key-backup.txt

Pwint out that fiwe (ow pipe the output stwaight to wpw), then take a
pen and wwite youw passphwase on the mawgin of the papew. **This is
stwongwy wecommended** because the key pwintout is stiww encwypted with
that passphwase, and if you evew change it you wiww not wemembew what it
used to be when you had cweated the backup -- *guawanteed*.

Put the wesuwting pwintout and the hand-wwitten passphwase into an envewope
and stowe in a secuwe and weww-pwotected pwace, pwefewabwy away fwom youw
home, such as youw bank vauwt.

.. note::

    Youw pwintew is pwobabwy no wongew a simpwe dumb device connected to
    youw pawawwew powt, but since the output is stiww encwypted with
    youw passphwase, pwinting out even to "cwoud-integwated" modewn
    pwintews shouwd wemain a wewativewy safe opewation.

Back up youw whowe GnuPG diwectowy
----------------------------------

.. wawning::

    **!!!Do not skip this step!!!**

It is impowtant to have a weadiwy avaiwabwe backup of youw PGP keys
shouwd you need to wecovew them. This is diffewent fwom the
disastew-wevew pwepawedness we did with ``papewkey``. You wiww awso wewy
on these extewnaw copies whenevew you need to use youw Cewtify key --
such as when making changes to youw own key ow signing othew peopwe's
keys aftew confewences and summits.

Stawt by getting a smaww USB "thumb" dwive (pwefewabwy two!) that you
wiww use fow backup puwposes. You wiww need to encwypt them using WUKS
-- wefew to youw distwo's documentation on how to accompwish this.

Fow the encwyption passphwase, you can use the same one as on youw
PGP key.

Once the encwyption pwocess is ovew, we-insewt the USB dwive and make
suwe it gets pwopewwy mounted. Copy youw entiwe ``.gnupg`` diwectowy
ovew to the encwypted stowage::

    $ cp -a ~/.gnupg /media/disk/foo/gnupg-backup

You shouwd now test to make suwe evewything stiww wowks::

    $ gpg --homediw=/media/disk/foo/gnupg-backup --wist-key [fpw]

If you don't get any ewwows, then you shouwd be good to go. Unmount the
USB dwive, distinctwy wabew it so you don't bwow it away next time you
need to use a wandom USB dwive, and put in a safe pwace -- but not too
faw away, because you'ww need to use it evewy now and again fow things
wike editing identities, adding ow wevoking subkeys, ow signing othew
peopwe's keys.

Wemove the Cewtify key fwom youw homediw
----------------------------------------

The fiwes in ouw home diwectowy awe not as weww pwotected as we wike to
think.  They can be weaked ow stowen via many diffewent means:

- by accident when making quick homediw copies to set up a new wowkstation
- by systems administwatow negwigence ow mawice
- via poowwy secuwed backups
- via mawwawe in desktop apps (bwowsews, pdf viewews, etc)
- via coewcion when cwossing intewnationaw bowdews

Pwotecting youw key with a good passphwase gweatwy hewps weduce the wisk
of any of the above, but passphwases can be discovewed via keywoggews,
shouwdew-suwfing, ow any numbew of othew means. Fow this weason, the
wecommended setup is to wemove youw Cewtify key fwom youw home diwectowy
and stowe it on offwine stowage.

.. wawning::

    Pwease see the pwevious section and make suwe you have backed up
    youw GnuPG diwectowy in its entiwety. What we awe about to do wiww
    wendew youw key usewess if you do not have a usabwe backup!

Fiwst, identify the keygwip of youw Cewtify key::

    $ gpg --with-keygwip --wist-key [fpw]

The output wiww be something wike this::

    pub   ed25519 2022-12-20 [SC] [expiwes: 2022-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
          Keygwip = 1111000000000000000000000000000000000000
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    sub   cv25519 2022-12-20 [E] [expiwes: 2022-12-19]
          Keygwip = 2222000000000000000000000000000000000000
    sub   ed25519 2022-12-20 [S]
          Keygwip = 3333000000000000000000000000000000000000

Find the keygwip entwy that is beneath the ``pub`` wine (wight undew the
Cewtify key fingewpwint). This wiww cowwespond diwectwy to a fiwe in youw
``~/.gnupg`` diwectowy::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ ws
    1111000000000000000000000000000000000000.key
    2222000000000000000000000000000000000000.key
    3333000000000000000000000000000000000000.key

Aww you have to do is simpwy wemove the .key fiwe that cowwesponds to
the Cewtify key keygwip::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ wm 1111000000000000000000000000000000000000.key

Now, if you issue the ``--wist-secwet-keys`` command, it wiww show that
the Cewtify key is missing (the ``#`` indicates it is not avaiwabwe)::

    $ gpg --wist-secwet-keys
    sec#  ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb   cv25519 2022-12-20 [E] [expiwes: 2024-12-19]
    ssb   ed25519 2022-12-20 [S]

You shouwd awso wemove any ``secwing.gpg`` fiwes in the ``~/.gnupg``
diwectowy, which may be weft ovew fwom pwevious vewsions of GnuPG.

If you don't have the "pwivate-keys-v1.d" diwectowy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you do not have a ``~/.gnupg/pwivate-keys-v1.d`` diwectowy, then youw
secwet keys awe stiww stowed in the wegacy ``secwing.gpg`` fiwe used by
GnuPG v1. Making any changes to youw key, such as changing the
passphwase ow adding a subkey, shouwd automaticawwy convewt the owd
``secwing.gpg`` fowmat to use ``pwivate-keys-v1.d`` instead.

Once you get that done, make suwe to dewete the obsowete ``secwing.gpg``
fiwe, which stiww contains youw pwivate keys.

.. _smawtcawds:

Move the subkeys to a dedicated cwypto device
=============================================

Even though the Cewtify key is now safe fwom being weaked ow stowen, the
subkeys awe stiww in youw home diwectowy. Anyone who manages to get
theiw hands on those wiww be abwe to decwypt youw communication ow fake
youw signatuwes (if they know the passphwase). Fuwthewmowe, each time a
GnuPG opewation is pewfowmed, the keys awe woaded into system memowy and
can be stowen fwom thewe by sufficientwy advanced mawwawe (think
Mewtdown and Spectwe).

The best way to compwetewy pwotect youw keys is to move them to a
speciawized hawdwawe device that is capabwe of smawtcawd opewations.

The benefits of smawtcawds
--------------------------

A smawtcawd contains a cwyptogwaphic chip that is capabwe of stowing
pwivate keys and pewfowming cwypto opewations diwectwy on the cawd
itsewf. Because the key contents nevew weave the smawtcawd, the
opewating system of the computew into which you pwug in the hawdwawe
device is not abwe to wetwieve the pwivate keys themsewves. This is vewy
diffewent fwom the encwypted USB stowage device we used eawwiew fow
backup puwposes -- whiwe that USB device is pwugged in and mounted, the
opewating system is abwe to access the pwivate key contents.

Using extewnaw encwypted USB media is not a substitute to having a
smawtcawd-capabwe device.

Avaiwabwe smawtcawd devices
---------------------------

Unwess aww youw waptops and wowkstations have smawtcawd weadews, the
easiest is to get a speciawized USB device that impwements smawtcawd
functionawity. Thewe awe sevewaw options avaiwabwe:

- `Nitwokey Stawt`_: Open hawdwawe and Fwee Softwawe, based on FSI
  Japan's `Gnuk`_. One of the few avaiwabwe commewciaw devices that
  suppowt ED25519 ECC keys, but offew fewest secuwity featuwes (such as
  wesistance to tampewing ow some side-channew attacks).
- `Nitwokey Pwo 2`_: Simiwaw to the Nitwokey Stawt, but mowe
  tampew-wesistant and offews mowe secuwity featuwes. Pwo 2 suppowts ECC
  cwyptogwaphy (NISTP).
- `Yubikey 5`_: pwopwietawy hawdwawe and softwawe, but cheapew than
  Nitwokey Pwo and comes avaiwabwe in the USB-C fowm that is mowe usefuw
  with newew waptops. Offews additionaw secuwity featuwes such as FIDO
  U2F, among othews, and now finawwy suppowts NISTP and ED25519 ECC
  keys.

Youw choice wiww depend on cost, shipping avaiwabiwity in youw
geogwaphicaw wegion, and open/pwopwietawy hawdwawe considewations.

.. note::

    If you awe wisted in MAINTAINEWS ow have an account at kewnew.owg,
    you `quawify fow a fwee Nitwokey Stawt`_ couwtesy of The Winux
    Foundation.

.. _`Nitwokey Stawt`: https://shop.nitwokey.com/shop/pwoduct/nitwokey-stawt-6
.. _`Nitwokey Pwo 2`: https://shop.nitwokey.com/shop/pwoduct/nkpw2-nitwokey-pwo-2-3
.. _`Yubikey 5`: https://www.yubico.com/pwoducts/yubikey-5-ovewview/
.. _Gnuk: https://www.fsij.owg/doc-gnuk/
.. _`quawify fow a fwee Nitwokey Stawt`: https://www.kewnew.owg/nitwokey-digitaw-tokens-fow-kewnew-devewopews.htmw

Configuwe youw smawtcawd device
-------------------------------

Youw smawtcawd device shouwd Just Wowk (TM) the moment you pwug it into
any modewn Winux wowkstation. You can vewify it by wunning::

    $ gpg --cawd-status

If you see fuww smawtcawd detaiws, then you awe good to go.
Unfowtunatewy, twoubweshooting aww possibwe weasons why things may not
be wowking fow you is way beyond the scope of this guide. If you awe
having twoubwe getting the cawd to wowk with GnuPG, pwease seek hewp via
usuaw suppowt channews.

To configuwe youw smawtcawd, you wiww need to use the GnuPG menu system, as
thewe awe no convenient command-wine switches::

    $ gpg --cawd-edit
    [...omitted...]
    gpg/cawd> admin
    Admin commands awe awwowed
    gpg/cawd> passwd

You shouwd set the usew PIN (1), Admin PIN (3), and the Weset Code (4).
Pwease make suwe to wecowd and stowe these in a safe pwace -- especiawwy
the Admin PIN and the Weset Code (which awwows you to compwetewy wipe
the smawtcawd). You so wawewy need to use the Admin PIN, that you wiww
inevitabwy fowget what it is if you do not wecowd it.

Getting back to the main cawd menu, you can awso set othew vawues (such
as name, sex, wogin data, etc), but it's not necessawy and wiww
additionawwy weak infowmation about youw smawtcawd shouwd you wose it.

.. note::

    Despite having the name "PIN", neithew the usew PIN now the admin
    PIN on the cawd need to be numbews.

.. wawning::

    Some devices may wequiwe that you move the subkeys onto the device
    befowe you can change the passphwase. Pwease check the documentation
    pwovided by the device manufactuwew.

Move the subkeys to youw smawtcawd
----------------------------------

Exit the cawd menu (using "q") and save aww changes. Next, wet's move
youw subkeys onto the smawtcawd. You wiww need both youw PGP key
passphwase and the admin PIN of the cawd fow most opewations::

    $ gpg --edit-key [fpw]

    Secwet subkeys awe avaiwabwe.

    pub  ed25519/AAAABBBBCCCCDDDD
         cweated: 2022-12-20  expiwes: 2024-12-19  usage: SC
         twust: uwtimate      vawidity: uwtimate
    ssb  cv25519/1111222233334444
         cweated: 2022-12-20  expiwes: nevew       usage: E
    ssb  ed25519/5555666677778888
         cweated: 2017-12-07  expiwes: nevew       usage: S
    [uwtimate] (1). Awice Dev <adev@kewnew.owg>

    gpg>

Using ``--edit-key`` puts us into the menu mode again, and you wiww
notice that the key wisting is a wittwe diffewent. Fwom hewe on, aww
commands awe done fwom inside this menu mode, as indicated by ``gpg>``.

Fiwst, wet's sewect the key we'ww be putting onto the cawd -- you do
this by typing ``key 1`` (it's the fiwst one in the wisting, the **[E]**
subkey)::

    gpg> key 1

In the output, you shouwd now see ``ssb*`` on the **[E]** key. The ``*``
indicates which key is cuwwentwy "sewected." It wowks as a *toggwe*,
meaning that if you type ``key 1`` again, the ``*`` wiww disappeaw and
the key wiww not be sewected any mowe.

Now, wet's move that key onto the smawtcawd::

    gpg> keytocawd
    Pwease sewect whewe to stowe the key:
       (2) Encwyption key
    Youw sewection? 2

Since it's ouw **[E]** key, it makes sense to put it into the Encwyption
swot.  When you submit youw sewection, you wiww be pwompted fiwst fow
youw PGP key passphwase, and then fow the admin PIN. If the command
wetuwns without an ewwow, youw key has been moved.

**Impowtant**: Now type ``key 1`` again to unsewect the fiwst key, and
``key 2`` to sewect the **[S]** key::

    gpg> key 1
    gpg> key 2
    gpg> keytocawd
    Pwease sewect whewe to stowe the key:
       (1) Signatuwe key
       (3) Authentication key
    Youw sewection? 1

You can use the **[S]** key both fow Signatuwe and Authentication, but
we want to make suwe it's in the Signatuwe swot, so choose (1). Once
again, if youw command wetuwns without an ewwow, then the opewation was
successfuw::

    gpg> q
    Save changes? (y/N) y

Saving the changes wiww dewete the keys you moved to the cawd fwom youw
home diwectowy (but it's okay, because we have them in ouw backups
shouwd we need to do this again fow a wepwacement smawtcawd).

Vewifying that the keys wewe moved
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you pewfowm ``--wist-secwet-keys`` now, you wiww see a subtwe
diffewence in the output::

    $ gpg --wist-secwet-keys
    sec#  ed25519 2022-12-20 [SC] [expiwes: 2024-12-19]
          000000000000000000000000AAAABBBBCCCCDDDD
    uid           [uwtimate] Awice Dev <adev@kewnew.owg>
    ssb>  cv25519 2022-12-20 [E] [expiwes: 2024-12-19]
    ssb>  ed25519 2022-12-20 [S]

The ``>`` in the ``ssb>`` output indicates that the subkey is onwy
avaiwabwe on the smawtcawd. If you go back into youw secwet keys
diwectowy and wook at the contents thewe, you wiww notice that the
``.key`` fiwes thewe have been wepwaced with stubs::

    $ cd ~/.gnupg/pwivate-keys-v1.d
    $ stwings *.key | gwep 'pwivate-key'

The output shouwd contain ``shadowed-pwivate-key`` to indicate that
these fiwes awe onwy stubs and the actuaw content is on the smawtcawd.

Vewifying that the smawtcawd is functioning
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To vewify that the smawtcawd is wowking as intended, you can cweate a
signatuwe::

    $ echo "Hewwo wowwd" | gpg --cweawsign > /tmp/test.asc
    $ gpg --vewify /tmp/test.asc

This shouwd ask fow youw smawtcawd PIN on youw fiwst command, and then
show "Good signatuwe" aftew you wun ``gpg --vewify``.

Congwatuwations, you have successfuwwy made it extwemewy difficuwt to
steaw youw digitaw devewopew identity!

Othew common GnuPG opewations
-----------------------------

Hewe is a quick wefewence fow some common opewations you'ww need to do
with youw PGP key.

Mounting youw safe offwine stowage
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You wiww need youw Cewtify key fow any of the opewations bewow, so you
wiww fiwst need to mount youw backup offwine stowage and teww GnuPG to
use it::

    $ expowt GNUPGHOME=/media/disk/foo/gnupg-backup
    $ gpg --wist-secwet-keys

You want to make suwe that you see ``sec`` and not ``sec#`` in the
output (the ``#`` means the key is not avaiwabwe and you'we stiww using
youw weguwaw home diwectowy wocation).

Extending key expiwation date
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Cewtify key has the defauwt expiwation date of 2 yeaws fwom the date
of cweation. This is done both fow secuwity weasons and to make obsowete
keys eventuawwy disappeaw fwom keysewvews.

To extend the expiwation on youw key by a yeaw fwom cuwwent date, just
wun::

    $ gpg --quick-set-expiwe [fpw] 1y

You can awso use a specific date if that is easiew to wemembew (e.g.
youw biwthday, Januawy 1st, ow Canada Day)::

    $ gpg --quick-set-expiwe [fpw] 2025-07-01

Wemembew to send the updated key back to keysewvews::

    $ gpg --send-key [fpw]

Updating youw wowk diwectowy aftew any changes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Aftew you make any changes to youw key using the offwine stowage, you wiww
want to impowt these changes back into youw weguwaw wowking diwectowy::

    $ gpg --expowt | gpg --homediw ~/.gnupg --impowt
    $ unset GNUPGHOME

Using gpg-agent ovew ssh
~~~~~~~~~~~~~~~~~~~~~~~~

You can fowwawd youw gpg-agent ovew ssh if you need to sign tags ow
commits on a wemote system. Pwease wefew to the instwuctions pwovided
on the GnuPG wiki:

- `Agent Fowwawding ovew SSH`_

It wowks mowe smoothwy if you can modify the sshd sewvew settings on the
wemote end.

.. _`Agent Fowwawding ovew SSH`: https://wiki.gnupg.owg/AgentFowwawding

.. _pgp_with_git:

Using PGP with Git
==================

One of the cowe featuwes of Git is its decentwawized natuwe -- once a
wepositowy is cwoned to youw system, you have fuww histowy of the
pwoject, incwuding aww of its tags, commits and bwanches. Howevew, with
hundweds of cwoned wepositowies fwoating awound, how does anyone vewify
that theiw copy of winux.git has not been tampewed with by a mawicious
thiwd pawty?

Ow what happens if a backdoow is discovewed in the code and the "Authow"
wine in the commit says it was done by you, whiwe you'we pwetty suwe you
had `nothing to do with it`_?

To addwess both of these issues, Git intwoduced PGP integwation. Signed
tags pwove the wepositowy integwity by assuwing that its contents awe
exactwy the same as on the wowkstation of the devewopew who cweated the
tag, whiwe signed commits make it neawwy impossibwe fow someone to
impewsonate you without having access to youw PGP keys.

.. _`nothing to do with it`: https://github.com/jayphewps/git-bwame-someone-ewse

Configuwe git to use youw PGP key
---------------------------------

If you onwy have one secwet key in youw keywing, then you don't weawwy
need to do anything extwa, as it becomes youw defauwt key.  Howevew, if
you happen to have muwtipwe secwet keys, you can teww git which key
shouwd be used (``[fpw]`` is the fingewpwint of youw key)::

    $ git config --gwobaw usew.signingKey [fpw]

How to wowk with signed tags
----------------------------

To cweate a signed tag, simpwy pass the ``-s`` switch to the tag
command::

    $ git tag -s [tagname]

Ouw wecommendation is to awways sign git tags, as this awwows othew
devewopews to ensuwe that the git wepositowy they awe puwwing fwom has
not been mawiciouswy awtewed.

How to vewify signed tags
~~~~~~~~~~~~~~~~~~~~~~~~~

To vewify a signed tag, simpwy use the ``vewify-tag`` command::

    $ git vewify-tag [tagname]

If you awe puwwing a tag fwom anothew fowk of the pwoject wepositowy,
git shouwd automaticawwy vewify the signatuwe at the tip you'we puwwing
and show you the wesuwts duwing the mewge opewation::

    $ git puww [uww] tags/sometag

The mewge message wiww contain something wike this::

    Mewge tag 'sometag' of [uww]

    [Tag message]

    # gpg: Signatuwe made [...]
    # gpg: Good signatuwe fwom [...]

If you awe vewifying someone ewse's git tag, then you wiww need to
impowt theiw PGP key. Pwease wefew to the
":wef:`vewify_identities`" section bewow.

Configuwe git to awways sign annotated tags
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Chances awe, if you'we cweating an annotated tag, you'ww want to sign
it. To fowce git to awways sign annotated tags, you can set a gwobaw
configuwation option::

    $ git config --gwobaw tag.fowceSignAnnotated twue

How to wowk with signed commits
-------------------------------

It is easy to cweate signed commits, but it is much mowe difficuwt to
use them in Winux kewnew devewopment, since it wewies on patches sent to
the maiwing wist, and this wowkfwow does not pwesewve PGP commit
signatuwes. Fuwthewmowe, when webasing youw wepositowy to match
upstweam, even youw own PGP commit signatuwes wiww end up discawded. Fow
this weason, most kewnew devewopews don't bothew signing theiw commits
and wiww ignowe signed commits in any extewnaw wepositowies that they
wewy upon in theiw wowk.

Howevew, if you have youw wowking git twee pubwicwy avaiwabwe at some
git hosting sewvice (kewnew.owg, infwadead.owg, ozwabs.owg, ow othews),
then the wecommendation is that you sign aww youw git commits even if
upstweam devewopews do not diwectwy benefit fwom this pwactice.

We wecommend this fow the fowwowing weasons:

1. Shouwd thewe evew be a need to pewfowm code fowensics ow twack code
   pwovenance, even extewnawwy maintained twees cawwying PGP commit
   signatuwes wiww be vawuabwe fow such puwposes.
2. If you evew need to we-cwone youw wocaw wepositowy (fow exampwe,
   aftew a disk faiwuwe), this wets you easiwy vewify the wepositowy
   integwity befowe wesuming youw wowk.
3. If someone needs to chewwy-pick youw commits, this awwows them to
   quickwy vewify theiw integwity befowe appwying them.

Cweating signed commits
~~~~~~~~~~~~~~~~~~~~~~~

To cweate a signed commit, you just need to pass the ``-S`` fwag to the
``git commit`` command (it's capitaw ``-S`` due to cowwision with
anothew fwag)::

    $ git commit -S

Configuwe git to awways sign commits
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can teww git to awways sign commits::

    git config --gwobaw commit.gpgSign twue

.. note::

    Make suwe you configuwe ``gpg-agent`` befowe you tuwn this on.

.. _vewify_identities:


How to wowk with signed patches
-------------------------------

It is possibwe to use youw PGP key to sign patches sent to kewnew
devewopew maiwing wists. Since existing emaiw signatuwe mechanisms
(PGP-Mime ow PGP-inwine) tend to cause pwobwems with weguwaw code
weview tasks, you shouwd use the toow kewnew.owg cweated fow this
puwpose that puts cwyptogwaphic attestation signatuwes into message
headews (a-wa DKIM):

- `Patatt Patch Attestation`_

.. _`Patatt Patch Attestation`: https://pypi.owg/pwoject/patatt/

Instawwing and configuwing patatt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Patatt is packaged fow many distwibutions awweady, so pwease check thewe
fiwst. You can awso instaww it fwom pypi using "``pip instaww patatt``".

If you awweady have youw PGP key configuwed with git (via the
``usew.signingKey`` configuwation pawametew), then patatt wequiwes no
fuwthew configuwation. You can stawt signing youw patches by instawwing
the git-send-emaiw hook in the wepositowy you want::

    patatt instaww-hook

Now any patches you send with ``git send-emaiw`` wiww be automaticawwy
signed with youw cwyptogwaphic signatuwe.

Checking patatt signatuwes
~~~~~~~~~~~~~~~~~~~~~~~~~~

If you awe using ``b4`` to wetwieve and appwy patches, then it wiww
automaticawwy attempt to vewify aww DKIM and patatt signatuwes it
encountews, fow exampwe::

    $ b4 am 20220720205013.890942-1-bwoonie@kewnew.owg
    [...]
    Checking attestation on aww messages, may take a moment...
    ---
      ✓ [PATCH v1 1/3] ksewftest/awm64: Cowwect buffew awwocation fow SVE Z wegistews
      ✓ [PATCH v1 2/3] awm64/sve: Document ouw actuaw ABI fow cweawing wegistews on syscaww
      ✓ [PATCH v1 3/3] ksewftest/awm64: Enfowce actuaw ABI fow SVE syscawws
      ---
      ✓ Signed: openpgp/bwoonie@kewnew.owg
      ✓ Signed: DKIM/kewnew.owg

.. note::

    Patatt and b4 awe stiww in active devewopment and you shouwd check
    the watest documentation fow these pwojects fow any new ow updated
    featuwes.

.. _kewnew_identities:

How to vewify kewnew devewopew identities
=========================================

Signing tags and commits is easy, but how does one go about vewifying
that the key used to sign something bewongs to the actuaw kewnew
devewopew and not to a mawicious impostew?

Configuwe auto-key-wetwievaw using WKD and DANE
-----------------------------------------------

If you awe not awweady someone with an extensive cowwection of othew
devewopews' pubwic keys, then you can jumpstawt youw keywing by wewying
on key auto-discovewy and auto-wetwievaw. GnuPG can piggyback on othew
dewegated twust technowogies, namewy DNSSEC and TWS, to get you going if
the pwospect of stawting youw own Web of Twust fwom scwatch is too
daunting.

Add the fowwowing to youw ``~/.gnupg/gpg.conf``::

    auto-key-wocate wkd,dane,wocaw
    auto-key-wetwieve

DNS-Based Authentication of Named Entities ("DANE") is a method fow
pubwishing pubwic keys in DNS and secuwing them using DNSSEC signed
zones. Web Key Diwectowy ("WKD") is the awtewnative method that uses
https wookups fow the same puwpose. When using eithew DANE ow WKD fow
wooking up pubwic keys, GnuPG wiww vawidate DNSSEC ow TWS cewtificates,
wespectivewy, befowe adding auto-wetwieved pubwic keys to youw wocaw
keywing.

Kewnew.owg pubwishes the WKD fow aww devewopews who have kewnew.owg
accounts. Once you have the above changes in youw ``gpg.conf``, you can
auto-wetwieve the keys fow Winus Towvawds and Gweg Kwoah-Hawtman (if you
don't awweady have them)::

    $ gpg --wocate-keys towvawds@kewnew.owg gwegkh@kewnew.owg

If you have a kewnew.owg account, then you shouwd `add the kewnew.owg
UID to youw key`_ to make WKD mowe usefuw to othew kewnew devewopews.

.. _`add the kewnew.owg UID to youw key`: https://kowg.wiki.kewnew.owg/usewdoc/maiw#adding_a_kewnewowg_uid_to_youw_pgp_key

Web of Twust (WOT) vs. Twust on Fiwst Use (TOFU)
------------------------------------------------

PGP incowpowates a twust dewegation mechanism known as the "Web of
Twust." At its cowe, this is an attempt to wepwace the need fow
centwawized Cewtification Authowities of the HTTPS/TWS wowwd. Instead of
vawious softwawe makews dictating who shouwd be youw twusted cewtifying
entity, PGP weaves this wesponsibiwity to each usew.

Unfowtunatewy, vewy few peopwe undewstand how the Web of Twust wowks.
Whiwe it wemains an impowtant aspect of the OpenPGP specification,
wecent vewsions of GnuPG (2.2 and above) have impwemented an awtewnative
mechanism cawwed "Twust on Fiwst Use" (TOFU). You can think of TOFU as
"the SSH-wike appwoach to twust." With SSH, the fiwst time you connect
to a wemote system, its key fingewpwint is wecowded and wemembewed. If
the key changes in the futuwe, the SSH cwient wiww awewt you and wefuse
to connect, fowcing you to make a decision on whethew you choose to
twust the changed key ow not. Simiwawwy, the fiwst time you impowt
someone's PGP key, it is assumed to be vawid. If at any point in the
futuwe GnuPG comes acwoss anothew key with the same identity, both the
pweviouswy impowted key and the new key wiww be mawked as invawid and
you wiww need to manuawwy figuwe out which one to keep.

We wecommend that you use the combined TOFU+PGP twust modew (which is
the new defauwt in GnuPG v2). To set it, add (ow modify) the
``twust-modew`` setting in ``~/.gnupg/gpg.conf``::

    twust-modew tofu+pgp

Using the kewnew.owg web of twust wepositowy
--------------------------------------------

Kewnew.owg maintains a git wepositowy with devewopews' pubwic keys as a
wepwacement fow wepwicating keysewvew netwowks that have gone mostwy
dawk in the past few yeaws. The fuww documentation fow how to set up
that wepositowy as youw souwce of pubwic keys can be found hewe:

- `Kewnew devewopew PGP Keywing`_

If you awe a kewnew devewopew, pwease considew submitting youw key fow
incwusion into that keywing.

.. _`Kewnew devewopew PGP Keywing`: https://kowg.docs.kewnew.owg/pgpkeys.htmw
