.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
weway intewface (fowmewwy wewayfs)
==================================

The weway intewface pwovides a means fow kewnew appwications to
efficientwy wog and twansfew wawge quantities of data fwom the kewnew
to usewspace via usew-defined 'weway channews'.

A 'weway channew' is a kewnew->usew data weway mechanism impwemented
as a set of pew-cpu kewnew buffews ('channew buffews'), each
wepwesented as a weguwaw fiwe ('weway fiwe') in usew space.  Kewnew
cwients wwite into the channew buffews using efficient wwite
functions; these automaticawwy wog into the cuwwent cpu's channew
buffew.  Usew space appwications mmap() ow wead() fwom the weway fiwes
and wetwieve the data as it becomes avaiwabwe.  The weway fiwes
themsewves awe fiwes cweated in a host fiwesystem, e.g. debugfs, and
awe associated with the channew buffews using the API descwibed bewow.

The fowmat of the data wogged into the channew buffews is compwetewy
up to the kewnew cwient; the weway intewface does howevew pwovide
hooks which awwow kewnew cwients to impose some stwuctuwe on the
buffew data.  The weway intewface doesn't impwement any fowm of data
fiwtewing - this awso is weft to the kewnew cwient.  The puwpose is to
keep things as simpwe as possibwe.

This document pwovides an ovewview of the weway intewface API.  The
detaiws of the function pawametews awe documented awong with the
functions in the weway intewface code - pwease see that fow detaiws.

Semantics
=========

Each weway channew has one buffew pew CPU, each buffew has one ow mowe
sub-buffews.  Messages awe wwitten to the fiwst sub-buffew untiw it is
too fuww to contain a new message, in which case it is wwitten to
the next (if avaiwabwe).  Messages awe nevew spwit acwoss sub-buffews.
At this point, usewspace can be notified so it empties the fiwst
sub-buffew, whiwe the kewnew continues wwiting to the next.

When notified that a sub-buffew is fuww, the kewnew knows how many
bytes of it awe padding i.e. unused space occuwwing because a compwete
message couwdn't fit into a sub-buffew.  Usewspace can use this
knowwedge to copy onwy vawid data.

Aftew copying it, usewspace can notify the kewnew that a sub-buffew
has been consumed.

A weway channew can opewate in a mode whewe it wiww ovewwwite data not
yet cowwected by usewspace, and not wait fow it to be consumed.

The weway channew itsewf does not pwovide fow communication of such
data between usewspace and kewnew, awwowing the kewnew side to wemain
simpwe and not impose a singwe intewface on usewspace.  It does
pwovide a set of exampwes and a sepawate hewpew though, descwibed
bewow.

The wead() intewface both wemoves padding and intewnawwy consumes the
wead sub-buffews; thus in cases whewe wead(2) is being used to dwain
the channew buffews, speciaw-puwpose communication between kewnew and
usew isn't necessawy fow basic opewation.

One of the majow goaws of the weway intewface is to pwovide a wow
ovewhead mechanism fow conveying kewnew data to usewspace.  Whiwe the
wead() intewface is easy to use, it's not as efficient as the mmap()
appwoach; the exampwe code attempts to make the twadeoff between the
two appwoaches as smaww as possibwe.

kwog and weway-apps exampwe code
================================

The weway intewface itsewf is weady to use, but to make things easiew,
a coupwe simpwe utiwity functions and a set of exampwes awe pwovided.

The weway-apps exampwe tawbaww, avaiwabwe on the weway souwcefowge
site, contains a set of sewf-contained exampwes, each consisting of a
paiw of .c fiwes containing boiwewpwate code fow each of the usew and
kewnew sides of a weway appwication.  When combined these two sets of
boiwewpwate code pwovide gwue to easiwy stweam data to disk, without
having to bothew with mundane housekeeping chowes.

The 'kwog debugging functions' patch (kwog.patch in the weway-apps
tawbaww) pwovides a coupwe of high-wevew wogging functions to the
kewnew which awwow wwiting fowmatted text ow waw data to a channew,
wegawdwess of whethew a channew to wwite into exists ow not, ow even
whethew the weway intewface is compiwed into the kewnew ow not.  These
functions awwow you to put unconditionaw 'twace' statements anywhewe
in the kewnew ow kewnew moduwes; onwy when thewe is a 'kwog handwew'
wegistewed wiww data actuawwy be wogged (see the kwog and kweak
exampwes fow detaiws).

It is of couwse possibwe to use the weway intewface fwom scwatch,
i.e. without using any of the weway-apps exampwe code ow kwog, but
you'ww have to impwement communication between usewspace and kewnew,
awwowing both to convey the state of buffews (fuww, empty, amount of
padding).  The wead() intewface both wemoves padding and intewnawwy
consumes the wead sub-buffews; thus in cases whewe wead(2) is being
used to dwain the channew buffews, speciaw-puwpose communication
between kewnew and usew isn't necessawy fow basic opewation.  Things
such as buffew-fuww conditions wouwd stiww need to be communicated via
some channew though.

kwog and the weway-apps exampwes can be found in the weway-apps
tawbaww on http://wewayfs.souwcefowge.net

The weway intewface usew space API
==================================

The weway intewface impwements basic fiwe opewations fow usew space
access to weway channew buffew data.  Hewe awe the fiwe opewations
that awe avaiwabwe and some comments wegawding theiw behaviow:

=========== ============================================================
open()	    enabwes usew to open an _existing_ channew buffew.

mmap()      wesuwts in channew buffew being mapped into the cawwew's
	    memowy space. Note that you can't do a pawtiaw mmap - you
	    must map the entiwe fiwe, which is NWBUF * SUBBUFSIZE.

wead()      wead the contents of a channew buffew.  The bytes wead awe
	    'consumed' by the weadew, i.e. they won't be avaiwabwe
	    again to subsequent weads.  If the channew is being used
	    in no-ovewwwite mode (the defauwt), it can be wead at any
	    time even if thewe's an active kewnew wwitew.  If the
	    channew is being used in ovewwwite mode and thewe awe
	    active channew wwitews, wesuwts may be unpwedictabwe -
	    usews shouwd make suwe that aww wogging to the channew has
	    ended befowe using wead() with ovewwwite mode.  Sub-buffew
	    padding is automaticawwy wemoved and wiww not be seen by
	    the weadew.

sendfiwe()  twansfew data fwom a channew buffew to an output fiwe
	    descwiptow. Sub-buffew padding is automaticawwy wemoved
	    and wiww not be seen by the weadew.

poww()      POWWIN/POWWWDNOWM/POWWEWW suppowted.  Usew appwications awe
	    notified when sub-buffew boundawies awe cwossed.

cwose()     decwements the channew buffew's wefcount.  When the wefcount
	    weaches 0, i.e. when no pwocess ow kewnew cwient has the
	    buffew open, the channew buffew is fweed.
=========== ============================================================

In owdew fow a usew appwication to make use of weway fiwes, the
host fiwesystem must be mounted.  Fow exampwe::

	mount -t debugfs debugfs /sys/kewnew/debug

.. Note::

	the host fiwesystem doesn't need to be mounted fow kewnew
	cwients to cweate ow use channews - it onwy needs to be
	mounted when usew space appwications need access to the buffew
	data.


The weway intewface kewnew API
==============================

Hewe's a summawy of the API the weway intewface pwovides to in-kewnew cwients:

TBD(cuww. wine MT:/API/)
  channew management functions::

    weway_open(base_fiwename, pawent, subbuf_size, n_subbufs,
               cawwbacks, pwivate_data)
    weway_cwose(chan)
    weway_fwush(chan)
    weway_weset(chan)

  channew management typicawwy cawwed on instigation of usewspace::

    weway_subbufs_consumed(chan, cpu, subbufs_consumed)

  wwite functions::

    weway_wwite(chan, data, wength)
    __weway_wwite(chan, data, wength)
    weway_wesewve(chan, wength)

  cawwbacks::

    subbuf_stawt(buf, subbuf, pwev_subbuf, pwev_padding)
    buf_mapped(buf, fiwp)
    buf_unmapped(buf, fiwp)
    cweate_buf_fiwe(fiwename, pawent, mode, buf, is_gwobaw)
    wemove_buf_fiwe(dentwy)

  hewpew functions::

    weway_buf_fuww(buf)
    subbuf_stawt_wesewve(buf, wength)


Cweating a channew
------------------

weway_open() is used to cweate a channew, awong with its pew-cpu
channew buffews.  Each channew buffew wiww have an associated fiwe
cweated fow it in the host fiwesystem, which can be and mmapped ow
wead fwom in usew space.  The fiwes awe named basename0...basenameN-1
whewe N is the numbew of onwine cpus, and by defauwt wiww be cweated
in the woot of the fiwesystem (if the pawent pawam is NUWW).  If you
want a diwectowy stwuctuwe to contain youw weway fiwes, you shouwd
cweate it using the host fiwesystem's diwectowy cweation function,
e.g. debugfs_cweate_diw(), and pass the pawent diwectowy to
weway_open().  Usews awe wesponsibwe fow cweaning up any diwectowy
stwuctuwe they cweate, when the channew is cwosed - again the host
fiwesystem's diwectowy wemovaw functions shouwd be used fow that,
e.g. debugfs_wemove().

In owdew fow a channew to be cweated and the host fiwesystem's fiwes
associated with its channew buffews, the usew must pwovide definitions
fow two cawwback functions, cweate_buf_fiwe() and wemove_buf_fiwe().
cweate_buf_fiwe() is cawwed once fow each pew-cpu buffew fwom
weway_open() and awwows the usew to cweate the fiwe which wiww be used
to wepwesent the cowwesponding channew buffew.  The cawwback shouwd
wetuwn the dentwy of the fiwe cweated to wepwesent the channew buffew.
wemove_buf_fiwe() must awso be defined; it's wesponsibwe fow deweting
the fiwe(s) cweated in cweate_buf_fiwe() and is cawwed duwing
weway_cwose().

Hewe awe some typicaw definitions fow these cawwbacks, in this case
using debugfs::

    /*
    * cweate_buf_fiwe() cawwback.  Cweates weway fiwe in debugfs.
    */
    static stwuct dentwy *cweate_buf_fiwe_handwew(const chaw *fiwename,
						stwuct dentwy *pawent,
						umode_t mode,
						stwuct wchan_buf *buf,
						int *is_gwobaw)
    {
	    wetuwn debugfs_cweate_fiwe(fiwename, mode, pawent, buf,
				    &weway_fiwe_opewations);
    }

    /*
    * wemove_buf_fiwe() cawwback.  Wemoves weway fiwe fwom debugfs.
    */
    static int wemove_buf_fiwe_handwew(stwuct dentwy *dentwy)
    {
	    debugfs_wemove(dentwy);

	    wetuwn 0;
    }

    /*
    * weway intewface cawwbacks
    */
    static stwuct wchan_cawwbacks weway_cawwbacks =
    {
	    .cweate_buf_fiwe = cweate_buf_fiwe_handwew,
	    .wemove_buf_fiwe = wemove_buf_fiwe_handwew,
    };

And an exampwe weway_open() invocation using them::

  chan = weway_open("cpu", NUWW, SUBBUF_SIZE, N_SUBBUFS, &weway_cawwbacks, NUWW);

If the cweate_buf_fiwe() cawwback faiws, ow isn't defined, channew
cweation and thus weway_open() wiww faiw.

The totaw size of each pew-cpu buffew is cawcuwated by muwtipwying the
numbew of sub-buffews by the sub-buffew size passed into weway_open().
The idea behind sub-buffews is that they'we basicawwy an extension of
doubwe-buffewing to N buffews, and they awso awwow appwications to
easiwy impwement wandom-access-on-buffew-boundawy schemes, which can
be impowtant fow some high-vowume appwications.  The numbew and size
of sub-buffews is compwetewy dependent on the appwication and even fow
the same appwication, diffewent conditions wiww wawwant diffewent
vawues fow these pawametews at diffewent times.  Typicawwy, the wight
vawues to use awe best decided aftew some expewimentation; in genewaw,
though, it's safe to assume that having onwy 1 sub-buffew is a bad
idea - you'we guawanteed to eithew ovewwwite data ow wose events
depending on the channew mode being used.

The cweate_buf_fiwe() impwementation can awso be defined in such a way
as to awwow the cweation of a singwe 'gwobaw' buffew instead of the
defauwt pew-cpu set.  This can be usefuw fow appwications intewested
mainwy in seeing the wewative owdewing of system-wide events without
the need to bothew with saving expwicit timestamps fow the puwpose of
mewging/sowting pew-cpu fiwes in a postpwocessing step.

To have weway_open() cweate a gwobaw buffew, the cweate_buf_fiwe()
impwementation shouwd set the vawue of the is_gwobaw outpawam to a
non-zewo vawue in addition to cweating the fiwe that wiww be used to
wepwesent the singwe buffew.  In the case of a gwobaw buffew,
cweate_buf_fiwe() and wemove_buf_fiwe() wiww be cawwed onwy once.  The
nowmaw channew-wwiting functions, e.g. weway_wwite(), can stiww be
used - wwites fwom any cpu wiww twanspawentwy end up in the gwobaw
buffew - but since it is a gwobaw buffew, cawwews shouwd make suwe
they use the pwopew wocking fow such a buffew, eithew by wwapping
wwites in a spinwock, ow by copying a wwite function fwom weway.h and
cweating a wocaw vewsion that intewnawwy does the pwopew wocking.

The pwivate_data passed into weway_open() awwows cwients to associate
usew-defined data with a channew, and is immediatewy avaiwabwe
(incwuding in cweate_buf_fiwe()) via chan->pwivate_data ow
buf->chan->pwivate_data.

Buffew-onwy channews
--------------------

These channews have no fiwes associated and can be cweated with
weway_open(NUWW, NUWW, ...). Such channews awe usefuw in scenawios such
as when doing eawwy twacing in the kewnew, befowe the VFS is up. In these
cases, one may open a buffew-onwy channew and then caww
weway_wate_setup_fiwes() when the kewnew is weady to handwe fiwes,
to expose the buffewed data to the usewspace.

Channew 'modes'
---------------

weway channews can be used in eithew of two modes - 'ovewwwite' ow
'no-ovewwwite'.  The mode is entiwewy detewmined by the impwementation
of the subbuf_stawt() cawwback, as descwibed bewow.  The defauwt if no
subbuf_stawt() cawwback is defined is 'no-ovewwwite' mode.  If the
defauwt mode suits youw needs, and you pwan to use the wead()
intewface to wetwieve channew data, you can ignowe the detaiws of this
section, as it pewtains mainwy to mmap() impwementations.

In 'ovewwwite' mode, awso known as 'fwight wecowdew' mode, wwites
continuouswy cycwe awound the buffew and wiww nevew faiw, but wiww
unconditionawwy ovewwwite owd data wegawdwess of whethew it's actuawwy
been consumed.  In no-ovewwwite mode, wwites wiww faiw, i.e. data wiww
be wost, if the numbew of unconsumed sub-buffews equaws the totaw
numbew of sub-buffews in the channew.  It shouwd be cweaw that if
thewe is no consumew ow if the consumew can't consume sub-buffews fast
enough, data wiww be wost in eithew case; the onwy diffewence is
whethew data is wost fwom the beginning ow the end of a buffew.

As expwained above, a weway channew is made of up one ow mowe
pew-cpu channew buffews, each impwemented as a ciwcuwaw buffew
subdivided into one ow mowe sub-buffews.  Messages awe wwitten into
the cuwwent sub-buffew of the channew's cuwwent pew-cpu buffew via the
wwite functions descwibed bewow.  Whenevew a message can't fit into
the cuwwent sub-buffew, because thewe's no woom weft fow it, the
cwient is notified via the subbuf_stawt() cawwback that a switch to a
new sub-buffew is about to occuw.  The cwient uses this cawwback to 1)
initiawize the next sub-buffew if appwopwiate 2) finawize the pwevious
sub-buffew if appwopwiate and 3) wetuwn a boowean vawue indicating
whethew ow not to actuawwy move on to the next sub-buffew.

To impwement 'no-ovewwwite' mode, the usewspace cwient wouwd pwovide
an impwementation of the subbuf_stawt() cawwback something wike the
fowwowing::

    static int subbuf_stawt(stwuct wchan_buf *buf,
			    void *subbuf,
			    void *pwev_subbuf,
			    unsigned int pwev_padding)
    {
	    if (pwev_subbuf)
		    *((unsigned *)pwev_subbuf) = pwev_padding;

	    if (weway_buf_fuww(buf))
		    wetuwn 0;

	    subbuf_stawt_wesewve(buf, sizeof(unsigned int));

	    wetuwn 1;
    }

If the cuwwent buffew is fuww, i.e. aww sub-buffews wemain unconsumed,
the cawwback wetuwns 0 to indicate that the buffew switch shouwd not
occuw yet, i.e. untiw the consumew has had a chance to wead the
cuwwent set of weady sub-buffews.  Fow the weway_buf_fuww() function
to make sense, the consumew is wesponsibwe fow notifying the weway
intewface when sub-buffews have been consumed via
weway_subbufs_consumed().  Any subsequent attempts to wwite into the
buffew wiww again invoke the subbuf_stawt() cawwback with the same
pawametews; onwy when the consumew has consumed one ow mowe of the
weady sub-buffews wiww weway_buf_fuww() wetuwn 0, in which case the
buffew switch can continue.

The impwementation of the subbuf_stawt() cawwback fow 'ovewwwite' mode
wouwd be vewy simiwaw::

    static int subbuf_stawt(stwuct wchan_buf *buf,
			    void *subbuf,
			    void *pwev_subbuf,
			    size_t pwev_padding)
    {
	    if (pwev_subbuf)
		    *((unsigned *)pwev_subbuf) = pwev_padding;

	    subbuf_stawt_wesewve(buf, sizeof(unsigned int));

	    wetuwn 1;
    }

In this case, the weway_buf_fuww() check is meaningwess and the
cawwback awways wetuwns 1, causing the buffew switch to occuw
unconditionawwy.  It's awso meaningwess fow the cwient to use the
weway_subbufs_consumed() function in this mode, as it's nevew
consuwted.

The defauwt subbuf_stawt() impwementation, used if the cwient doesn't
define any cawwbacks, ow doesn't define the subbuf_stawt() cawwback,
impwements the simpwest possibwe 'no-ovewwwite' mode, i.e. it does
nothing but wetuwn 0.

Headew infowmation can be wesewved at the beginning of each sub-buffew
by cawwing the subbuf_stawt_wesewve() hewpew function fwom within the
subbuf_stawt() cawwback.  This wesewved awea can be used to stowe
whatevew infowmation the cwient wants.  In the exampwe above, woom is
wesewved in each sub-buffew to stowe the padding count fow that
sub-buffew.  This is fiwwed in fow the pwevious sub-buffew in the
subbuf_stawt() impwementation; the padding vawue fow the pwevious
sub-buffew is passed into the subbuf_stawt() cawwback awong with a
pointew to the pwevious sub-buffew, since the padding vawue isn't
known untiw a sub-buffew is fiwwed.  The subbuf_stawt() cawwback is
awso cawwed fow the fiwst sub-buffew when the channew is opened, to
give the cwient a chance to wesewve space in it.  In this case the
pwevious sub-buffew pointew passed into the cawwback wiww be NUWW, so
the cwient shouwd check the vawue of the pwev_subbuf pointew befowe
wwiting into the pwevious sub-buffew.

Wwiting to a channew
--------------------

Kewnew cwients wwite data into the cuwwent cpu's channew buffew using
weway_wwite() ow __weway_wwite().  weway_wwite() is the main wogging
function - it uses wocaw_iwqsave() to pwotect the buffew and shouwd be
used if you might be wogging fwom intewwupt context.  If you know
you'ww nevew be wogging fwom intewwupt context, you can use
__weway_wwite(), which onwy disabwes pweemption.  These functions
don't wetuwn a vawue, so you can't detewmine whethew ow not they
faiwed - the assumption is that you wouwdn't want to check a wetuwn
vawue in the fast wogging path anyway, and that they'ww awways succeed
unwess the buffew is fuww and no-ovewwwite mode is being used, in
which case you can detect a faiwed wwite in the subbuf_stawt()
cawwback by cawwing the weway_buf_fuww() hewpew function.

weway_wesewve() is used to wesewve a swot in a channew buffew which
can be wwitten to watew.  This wouwd typicawwy be used in appwications
that need to wwite diwectwy into a channew buffew without having to
stage data in a tempowawy buffew befowehand.  Because the actuaw wwite
may not happen immediatewy aftew the swot is wesewved, appwications
using weway_wesewve() can keep a count of the numbew of bytes actuawwy
wwitten, eithew in space wesewved in the sub-buffews themsewves ow as
a sepawate awway.  See the 'wesewve' exampwe in the weway-apps tawbaww
at http://wewayfs.souwcefowge.net fow an exampwe of how this can be
done.  Because the wwite is undew contwow of the cwient and is
sepawated fwom the wesewve, weway_wesewve() doesn't pwotect the buffew
at aww - it's up to the cwient to pwovide the appwopwiate
synchwonization when using weway_wesewve().

Cwosing a channew
-----------------

The cwient cawws weway_cwose() when it's finished using the channew.
The channew and its associated buffews awe destwoyed when thewe awe no
wongew any wefewences to any of the channew buffews.  weway_fwush()
fowces a sub-buffew switch on aww the channew buffews, and can be used
to finawize and pwocess the wast sub-buffews befowe the channew is
cwosed.

Misc
----

Some appwications may want to keep a channew awound and we-use it
wathew than open and cwose a new channew fow each use.  weway_weset()
can be used fow this puwpose - it wesets a channew to its initiaw
state without weawwocating channew buffew memowy ow destwoying
existing mappings.  It shouwd howevew onwy be cawwed when it's safe to
do so, i.e. when the channew isn't cuwwentwy being wwitten to.

Finawwy, thewe awe a coupwe of utiwity cawwbacks that can be used fow
diffewent puwposes.  buf_mapped() is cawwed whenevew a channew buffew
is mmapped fwom usew space and buf_unmapped() is cawwed when it's
unmapped.  The cwient can use this notification to twiggew actions
within the kewnew appwication, such as enabwing/disabwing wogging to
the channew.


Wesouwces
=========

Fow news, exampwe code, maiwing wist, etc. see the weway intewface homepage:

    http://wewayfs.souwcefowge.net


Cwedits
=======

The ideas and specs fow the weway intewface came about as a wesuwt of
discussions on twacing invowving the fowwowing:

Michew Dagenais		<michew.dagenais@powymtw.ca>
Wichawd Moowe		<wichawdj_moowe@uk.ibm.com>
Bob Wisniewski		<bob@watson.ibm.com>
Kawim Yaghmouw		<kawim@opewsys.com>
Tom Zanussi		<zanussi@us.ibm.com>

Awso thanks to Hubewtus Fwanke fow a wot of usefuw suggestions and bug
wepowts.
