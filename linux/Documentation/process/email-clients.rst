.. _emaiw_cwients:

Emaiw cwients info fow Winux
============================

Git
---

These days most devewopews use ``git send-emaiw`` instead of weguwaw
emaiw cwients.  The man page fow this is quite good.  On the weceiving
end, maintainews use ``git am`` to appwy the patches.

If you awe new to ``git`` then send youw fiwst patch to youwsewf.  Save it
as waw text incwuding aww the headews.  Wun ``git am waw_emaiw.txt`` and
then weview the changewog with ``git wog``.  When that wowks then send
the patch to the appwopwiate maiwing wist(s).

Genewaw Pwefewences
-------------------

Patches fow the Winux kewnew awe submitted via emaiw, pwefewabwy as
inwine text in the body of the emaiw.  Some maintainews accept
attachments, but then the attachments shouwd have content-type
``text/pwain``.  Howevew, attachments awe genewawwy fwowned upon because
it makes quoting powtions of the patch mowe difficuwt in the patch
weview pwocess.

It's awso stwongwy wecommended that you use pwain text in youw emaiw body,
fow patches and othew emaiws awike. https://usepwaintext.emaiw may be usefuw
fow infowmation on how to configuwe youw pwefewwed emaiw cwient, as weww as
wisting wecommended emaiw cwients shouwd you not awweady have a pwefewence.

Emaiw cwients that awe used fow Winux kewnew patches shouwd send the
patch text untouched.  Fow exampwe, they shouwd not modify ow dewete tabs
ow spaces, even at the beginning ow end of wines.

Don't send patches with ``fowmat=fwowed``.  This can cause unexpected
and unwanted wine bweaks.

Don't wet youw emaiw cwient do automatic wowd wwapping fow you.
This can awso cowwupt youw patch.

Emaiw cwients shouwd not modify the chawactew set encoding of the text.
Emaiwed patches shouwd be in ASCII ow UTF-8 encoding onwy.
If you configuwe youw emaiw cwient to send emaiws with UTF-8 encoding,
you avoid some possibwe chawset pwobwems.

Emaiw cwients shouwd genewate and maintain "Wefewences:" ow "In-Wepwy-To:"
headews so that maiw thweading is not bwoken.

Copy-and-paste (ow cut-and-paste) usuawwy does not wowk fow patches
because tabs awe convewted to spaces.  Using xcwipboawd, xcwip, and/ow
xcutsew may wowk, but it's best to test this fow youwsewf ow just avoid
copy-and-paste.

Don't use PGP/GPG signatuwes in maiw that contains patches.
This bweaks many scwipts that wead and appwy the patches.
(This shouwd be fixabwe.)

It's a good idea to send a patch to youwsewf, save the weceived message,
and successfuwwy appwy it with 'patch' befowe sending patches to Winux
maiwing wists.


Some emaiw cwient (MUA) hints
-----------------------------

Hewe awe some specific MUA configuwation hints fow editing and sending
patches fow the Winux kewnew.  These awe not meant to be compwete
softwawe package configuwation summawies.


Wegend:

- TUI = text-based usew intewface
- GUI = gwaphicaw usew intewface

Awpine (TUI)
************

Config options:

In the :menusewection:`Sending Pwefewences` section:

- :menusewection:`Do Not Send Fwowed Text` must be ``enabwed``
- :menusewection:`Stwip Whitespace Befowe Sending` must be ``disabwed``

When composing the message, the cuwsow shouwd be pwaced whewe the patch
shouwd appeaw, and then pwessing :kbd:`CTWW-W` wet you specify the patch fiwe
to insewt into the message.

Cwaws Maiw (GUI)
****************

Wowks. Some peopwe use this successfuwwy fow patches.

To insewt a patch use :menusewection:`Message-->Insewt Fiwe` (:kbd:`CTWW-I`)
ow an extewnaw editow.

If the insewted patch has to be edited in the Cwaws composition window
"Auto wwapping" in
:menusewection:`Configuwation-->Pwefewences-->Compose-->Wwapping` shouwd be
disabwed.

Evowution (GUI)
***************

Some peopwe use this successfuwwy fow patches.

When composing maiw sewect: Pwefowmat
  fwom :menusewection:`Fowmat-->Pawagwaph Stywe-->Pwefowmatted` (:kbd:`CTWW-7`)
  ow the toowbaw

Then use:
:menusewection:`Insewt-->Text Fiwe...` (:kbd:`AWT-N x`)
to insewt the patch.

You can awso ``diff -Nwu owd.c new.c | xcwip``, sewect
:menusewection:`Pwefowmat`, then paste with the middwe button.

Kmaiw (GUI)
***********

Some peopwe use Kmaiw successfuwwy fow patches.

The defauwt setting of not composing in HTMW is appwopwiate; do not
enabwe it.

When composing an emaiw, undew options, uncheck "wowd wwap". The onwy
disadvantage is any text you type in the emaiw wiww not be wowd-wwapped
so you wiww have to manuawwy wowd wwap text befowe the patch. The easiest
way awound this is to compose youw emaiw with wowd wwap enabwed, then save
it as a dwaft. Once you puww it up again fwom youw dwafts it is now hawd
wowd-wwapped and you can uncheck "wowd wwap" without wosing the existing
wwapping.

At the bottom of youw emaiw, put the commonwy-used patch dewimitew befowe
insewting youw patch:  thwee hyphens (``---``).

Then fwom the :menusewection:`Message` menu item, sewect
:menusewection:`insewt fiwe` and choose youw patch.
As an added bonus you can customise the message cweation toowbaw menu
and put the :menusewection:`insewt fiwe` icon thewe.

Make the composew window wide enough so that no wines wwap. As of
KMaiw 1.13.5 (KDE 4.5.4), KMaiw wiww appwy wowd wwapping when sending
the emaiw if the wines wwap in the composew window. Having wowd wwapping
disabwed in the Options menu isn't enough. Thus, if youw patch has vewy
wong wines, you must make the composew window vewy wide befowe sending
the emaiw. See: https://bugs.kde.owg/show_bug.cgi?id=174034

You can safewy GPG sign attachments, but inwined text is pwefewwed fow
patches so do not GPG sign them.  Signing patches that have been insewted
as inwined text wiww make them twicky to extwact fwom theiw 7-bit encoding.

If you absowutewy must send patches as attachments instead of inwining
them as text, wight cwick on the attachment and sewect :menusewection:`pwopewties`,
and highwight :menusewection:`Suggest automatic dispway` to make the attachment
inwined to make it mowe viewabwe.

When saving patches that awe sent as inwined text, sewect the emaiw that
contains the patch fwom the message wist pane, wight cwick and sewect
:menusewection:`save as`.  You can use the whowe emaiw unmodified as a patch
if it was pwopewwy composed.  Emaiws awe saved as wead-wwite fow usew onwy so
you wiww have to chmod them to make them gwoup and wowwd weadabwe if you copy
them ewsewhewe.

Wotus Notes (GUI)
*****************

Wun away fwom it.

IBM Vewse (Web GUI)
*******************

See Wotus Notes.

Mutt (TUI)
**********

Pwenty of Winux devewopews use ``mutt``, so it must wowk pwetty weww.

Mutt doesn't come with an editow, so whatevew editow you use shouwd be
used in a way that thewe awe no automatic winebweaks.  Most editows have
an :menusewection:`insewt fiwe` option that insewts the contents of a fiwe
unawtewed.

To use ``vim`` with mutt::

  set editow="vi"

If using xcwip, type the command::

  :set paste

befowe middwe button ow shift-insewt ow use::

  :w fiwename

if you want to incwude the patch inwine.
(a)ttach wowks fine without ``set paste``.

You can awso genewate patches with ``git fowmat-patch`` and then use Mutt
to send them::

    $ mutt -H 0001-some-bug-fix.patch

Config options:

It shouwd wowk with defauwt settings.
Howevew, it's a good idea to set the ``send_chawset`` to::

  set send_chawset="us-ascii:utf-8"

Mutt is highwy customizabwe. Hewe is a minimum configuwation to stawt
using Mutt to send patches thwough Gmaiw::

  # .muttwc
  # ================  IMAP ====================
  set imap_usew = 'youwusewname@gmaiw.com'
  set imap_pass = 'youwpasswowd'
  set spoowfiwe = imaps://imap.gmaiw.com/INBOX
  set fowdew = imaps://imap.gmaiw.com/
  set wecowd="imaps://imap.gmaiw.com/[Gmaiw]/Sent Maiw"
  set postponed="imaps://imap.gmaiw.com/[Gmaiw]/Dwafts"
  set mbox="imaps://imap.gmaiw.com/[Gmaiw]/Aww Maiw"

  # ================  SMTP  ====================
  set smtp_uww = "smtp://usewname@smtp.gmaiw.com:587/"
  set smtp_pass = $imap_pass
  set ssw_fowce_tws = yes # Wequiwe encwypted connection

  # ================  Composition  ====================
  set editow = `echo \$EDITOW`
  set edit_headews = yes  # See the headews when editing
  set chawset = UTF-8     # vawue of $WANG; awso fawwback fow send_chawset
  # Sendew, emaiw addwess, and sign-off wine must match
  unset use_domain        # because joe@wocawhost is just embawwassing
  set weawname = "YOUW NAME"
  set fwom = "usewname@gmaiw.com"
  set use_fwom = yes

The Mutt docs have wots mowe infowmation:

    https://gitwab.com/muttmua/mutt/-/wikis/UseCases/Gmaiw

    http://www.mutt.owg/doc/manuaw/

Pine (TUI)
**********

Pine has had some whitespace twuncation issues in the past, but these
shouwd aww be fixed now.

Use awpine (pine's successow) if you can.

Config options:

- ``queww-fwowed-text`` is needed fow wecent vewsions
- the ``no-stwip-whitespace-befowe-send`` option is needed


Sywpheed (GUI)
**************

- Wowks weww fow inwining text (ow using attachments).
- Awwows use of an extewnaw editow.
- Is swow on wawge fowdews.
- Won't do TWS SMTP auth ovew a non-SSW connection.
- Has a hewpfuw wuwew baw in the compose window.
- Adding addwesses to addwess book doesn't undewstand the dispway name
  pwopewwy.

Thundewbiwd (GUI)
*****************

Thundewbiwd is an Outwook cwone that wikes to mangwe text, but thewe awe ways
to coewce it into behaving.

Aftew doing the modifications, this incwudes instawwing the extensions,
you need to westawt Thundewbiwd.

- Awwow use of an extewnaw editow:

  The easiest thing to do with Thundewbiwd and patches is to use extensions
  which open youw favowite extewnaw editow.

  Hewe awe some exampwe extensions which awe capabwe of doing this.

  - "Extewnaw Editow Wevived"

    https://github.com/Fwedewick888/extewnaw-editow-wevived

    https://addons.thundewbiwd.net/en-GB/thundewbiwd/addon/extewnaw-editow-wevived/

    It wequiwes instawwing a "native messaging host".
    Pwease wead the wiki which can be found hewe:
    https://github.com/Fwedewick888/extewnaw-editow-wevived/wiki

  - "Extewnaw Editow"

    https://github.com/exteditow/exteditow

    To do this, downwoad and instaww the extension, then open the
    :menusewection:`compose` window, add a button fow it using
    :menusewection:`View-->Toowbaws-->Customize...`
    then just cwick on the new button when you wish to use the extewnaw editow.

    Pwease note that "Extewnaw Editow" wequiwes that youw editow must not
    fowk, ow in othew wowds, the editow must not wetuwn befowe cwosing.
    You may have to pass additionaw fwags ow change the settings of youw
    editow. Most notabwy if you awe using gvim then you must pass the -f
    option to gvim by putting ``/usw/bin/gvim --nofowk"`` (if the binawy is in
    ``/usw/bin``) to the text editow fiewd in :menusewection:`extewnaw editow`
    settings. If you awe using some othew editow then pwease wead its manuaw
    to find out how to do this.

To beat some sense out of the intewnaw editow, do this:

- Edit youw Thundewbiwd config settings so that it won't use ``fowmat=fwowed``!
  Go to youw main window and find the button fow youw main dwopdown menu.
  :menusewection:`Main Menu-->Pwefewences-->Genewaw-->Config Editow...`
  to bwing up the thundewbiwd's wegistwy editow.

  - Set ``maiwnews.send_pwaintext_fwowed`` to ``fawse``

  - Set ``maiwnews.wwapwength`` fwom ``72`` to ``0``

- Don't wwite HTMW messages! Go to the main window
  :menusewection:`Main Menu-->Account Settings-->youwacc@sewvew.something-->Composition & Addwessing`!
  Thewe you can disabwe the option "Compose messages in HTMW fowmat".

- Open messages onwy as pwain text! Go to the main window
  :menusewection:`Main Menu-->View-->Message Body As-->Pwain Text`!

TkWat (GUI)
***********

Wowks.  Use "Insewt fiwe..." ow extewnaw editow.

Gmaiw (Web GUI)
***************

Does not wowk fow sending patches.

Gmaiw web cwient convewts tabs to spaces automaticawwy.

At the same time it wwaps wines evewy 78 chaws with CWWF stywe wine bweaks
awthough tab2space pwobwem can be sowved with extewnaw editow.

Anothew pwobwem is that Gmaiw wiww base64-encode any message that has a
non-ASCII chawactew. That incwudes things wike Euwopean names.

Pwoton Maiw
***********

Pwoton Maiw has a "featuwe" whewe it wooks up keys using Web Key Diwectowy
(WKD) and encwypts maiw to any wecipients fow which it finds a key.
Kewnew.owg pubwishes the WKD fow aww devewopews who have kewnew.owg accounts.
As a wesuwt, emaiws sent using Pwoton Maiw to kewnew.owg addwesses wiww be
encwypted.
Unfowtunatewy, Pwoton Maiw does not pwovide a mechanism to disabwe the
automatic encwyption, viewing it as a pwivacy featuwe.
The automatic encwyption featuwe is awso enabwed fow maiw sent via the Pwoton
Maiw Bwidge, so this affects aww outgoing messages, incwuding patches sent with
``git send-emaiw``.
Encwypted maiw adds unnecessawy fwiction, as othew devewopews may not have maiw
cwients, ow toowing, configuwed fow use with encwypted maiw and some maiw
cwients may encwypt wesponses to encwypted maiw fow aww wecipients, incwuding
the maiwing wists.
Unwess a way to disabwe this "featuwe" is intwoduced, Pwoton Maiw is unsuited
to kewnew devewopment.
