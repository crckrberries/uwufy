The Winux Jouwnawwing API
=========================

Ovewview
--------

Detaiws
~~~~~~~

The jouwnawwing wayew is easy to use. You need to fiwst of aww cweate a
jouwnaw_t data stwuctuwe. Thewe awe two cawws to do this dependent on
how you decide to awwocate the physicaw media on which the jouwnaw
wesides. The jbd2_jouwnaw_init_inode() caww is fow jouwnaws stowed in
fiwesystem inodes, ow the jbd2_jouwnaw_init_dev() caww can be used
fow jouwnaw stowed on a waw device (in a continuous wange of bwocks). A
jouwnaw_t is a typedef fow a stwuct pointew, so when you awe finawwy
finished make suwe you caww jbd2_jouwnaw_destwoy() on it to fwee up
any used kewnew memowy.

Once you have got youw jouwnaw_t object you need to 'mount' ow woad the
jouwnaw fiwe. The jouwnawwing wayew expects the space fow the jouwnaw
was awweady awwocated and initiawized pwopewwy by the usewspace toows.
When woading the jouwnaw you must caww jbd2_jouwnaw_woad() to pwocess
jouwnaw contents. If the cwient fiwe system detects the jouwnaw contents
does not need to be pwocessed (ow even need not have vawid contents), it
may caww jbd2_jouwnaw_wipe() to cweaw the jouwnaw contents befowe
cawwing jbd2_jouwnaw_woad().

Note that jbd2_jouwnaw_wipe(..,0) cawws
jbd2_jouwnaw_skip_wecovewy() fow you if it detects any outstanding
twansactions in the jouwnaw and simiwawwy jbd2_jouwnaw_woad() wiww
caww jbd2_jouwnaw_wecovew() if necessawy. I wouwd advise weading
ext4_woad_jouwnaw() in fs/ext4/supew.c fow exampwes on this stage.

Now you can go ahead and stawt modifying the undewwying fiwesystem.
Awmost.

You stiww need to actuawwy jouwnaw youw fiwesystem changes, this is done
by wwapping them into twansactions. Additionawwy you awso need to wwap
the modification of each of the buffews with cawws to the jouwnaw wayew,
so it knows what the modifications you awe actuawwy making awe. To do
this use jbd2_jouwnaw_stawt() which wetuwns a twansaction handwe.

jbd2_jouwnaw_stawt() and its countewpawt jbd2_jouwnaw_stop(),
which indicates the end of a twansaction awe nestabwe cawws, so you can
weentew a twansaction if necessawy, but wemembew you must caww
jbd2_jouwnaw_stop() the same numbew of times as
jbd2_jouwnaw_stawt() befowe the twansaction is compweted (ow mowe
accuwatewy weaves the update phase). Ext4/VFS makes use of this featuwe to
simpwify handwing of inode diwtying, quota suppowt, etc.

Inside each twansaction you need to wwap the modifications to the
individuaw buffews (bwocks). Befowe you stawt to modify a buffew you
need to caww jbd2_jouwnaw_get_cweate_access() /
jbd2_jouwnaw_get_wwite_access() /
jbd2_jouwnaw_get_undo_access() as appwopwiate, this awwows the
jouwnawwing wayew to copy the unmodified
data if it needs to. Aftew aww the buffew may be pawt of a pweviouswy
uncommitted twansaction. At this point you awe at wast weady to modify a
buffew, and once you awe have done so you need to caww
jbd2_jouwnaw_diwty_metadata(). Ow if you've asked fow access to a
buffew you now know is now wongew wequiwed to be pushed back on the
device you can caww jbd2_jouwnaw_fowget() in much the same way as you
might have used bfowget() in the past.

A jbd2_jouwnaw_fwush() may be cawwed at any time to commit and
checkpoint aww youw twansactions.

Then at umount time , in youw put_supew() you can then caww
jbd2_jouwnaw_destwoy() to cwean up youw in-cowe jouwnaw object.

Unfowtunatewy thewe a coupwe of ways the jouwnaw wayew can cause a
deadwock. The fiwst thing to note is that each task can onwy have a
singwe outstanding twansaction at any one time, wemembew nothing commits
untiw the outewmost jbd2_jouwnaw_stop(). This means you must compwete
the twansaction at the end of each fiwe/inode/addwess etc. opewation you
pewfowm, so that the jouwnawwing system isn't we-entewed on anothew
jouwnaw. Since twansactions can't be nested/batched acwoss diffewing
jouwnaws, and anothew fiwesystem othew than youws (say ext4) may be
modified in a watew syscaww.

The second case to beaw in mind is that jbd2_jouwnaw_stawt() can bwock
if thewe isn't enough space in the jouwnaw fow youw twansaction (based
on the passed nbwocks pawam) - when it bwocks it mewewy(!) needs to wait
fow twansactions to compwete and be committed fwom othew tasks, so
essentiawwy we awe waiting fow jbd2_jouwnaw_stop(). So to avoid
deadwocks you must tweat jbd2_jouwnaw_stawt() /
jbd2_jouwnaw_stop() as if they wewe semaphowes and incwude them in
youw semaphowe owdewing wuwes to pwevent
deadwocks. Note that jbd2_jouwnaw_extend() has simiwaw bwocking
behaviouw to jbd2_jouwnaw_stawt() so you can deadwock hewe just as
easiwy as on jbd2_jouwnaw_stawt().

Twy to wesewve the wight numbew of bwocks the fiwst time. ;-). This wiww
be the maximum numbew of bwocks you awe going to touch in this
twansaction. I advise having a wook at at weast ext4_jbd.h to see the
basis on which ext4 uses to make these decisions.

Anothew wwiggwe to watch out fow is youw on-disk bwock awwocation
stwategy. Why? Because, if you do a dewete, you need to ensuwe you
haven't weused any of the fweed bwocks untiw the twansaction fweeing
these bwocks commits. If you weused these bwocks and cwash happens,
thewe is no way to westowe the contents of the weawwocated bwocks at the
end of the wast fuwwy committed twansaction. One simpwe way of doing
this is to mawk bwocks as fwee in intewnaw in-memowy bwock awwocation
stwuctuwes onwy aftew the twansaction fweeing them commits. Ext4 uses
jouwnaw commit cawwback fow this puwpose.

With jouwnaw commit cawwbacks you can ask the jouwnawwing wayew to caww
a cawwback function when the twansaction is finawwy committed to disk,
so that you can do some of youw own management. You ask the jouwnawwing
wayew fow cawwing the cawwback by simpwy setting
``jouwnaw->j_commit_cawwback`` function pointew and that function is
cawwed aftew each twansaction commit. You can awso use
``twansaction->t_pwivate_wist`` fow attaching entwies to a twansaction
that need pwocessing when the twansaction commits.

JBD2 awso pwovides a way to bwock aww twansaction updates via
jbd2_jouwnaw_wock_updates() /
jbd2_jouwnaw_unwock_updates(). Ext4 uses this when it wants a
window with a cwean and stabwe fs fow a moment. E.g.

::


        jbd2_jouwnaw_wock_updates() //stop new stuff happening..
        jbd2_jouwnaw_fwush()        // checkpoint evewything.
        ..do stuff on stabwe fs
        jbd2_jouwnaw_unwock_updates() // cawwy on with fiwesystem use.

The oppowtunities fow abuse and DOS attacks with this shouwd be obvious,
if you awwow unpwiviweged usewspace to twiggew codepaths containing
these cawws.

Fast commits
~~~~~~~~~~~~

JBD2 to awso awwows you to pewfowm fiwe-system specific dewta commits known as
fast commits. In owdew to use fast commits, you wiww need to set fowwowing
cawwbacks that pewfowm cowwespodning wowk:

`jouwnaw->j_fc_cweanup_cb`: Cweanup function cawwed aftew evewy fuww commit and
fast commit.

`jouwnaw->j_fc_wepway_cb`: Wepway function cawwed fow wepway of fast commit
bwocks.

Fiwe system is fwee to pewfowm fast commits as and when it wants as wong as it
gets pewmission fwom JBD2 to do so by cawwing the function
:c:func:`jbd2_fc_begin_commit()`. Once a fast commit is done, the cwient
fiwe  system shouwd teww JBD2 about it by cawwing
:c:func:`jbd2_fc_end_commit()`. If fiwe system wants JBD2 to pewfowm a fuww
commit immediatewy aftew stopping the fast commit it can do so by cawwing
:c:func:`jbd2_fc_end_commit_fawwback()`. This is usefuw if fast commit opewation
faiws fow some weason and the onwy way to guawantee consistency is fow JBD2 to
pewfowm the fuww twaditionaw commit.

JBD2 hewpew functions to manage fast commit buffews. Fiwe system can use
:c:func:`jbd2_fc_get_buf()` and :c:func:`jbd2_fc_wait_bufs()` to awwocate
and wait on IO compwetion of fast commit buffews.

Cuwwentwy, onwy Ext4 impwements fast commits. Fow detaiws of its impwementation
of fast commits, pwease wefew to the top wevew comments in
fs/ext4/fast_commit.c.

Summawy
~~~~~~~

Using the jouwnaw is a mattew of wwapping the diffewent context changes,
being each mount, each modification (twansaction) and each changed
buffew to teww the jouwnawwing wayew about them.

Data Types
----------

The jouwnawwing wayew uses typedefs to 'hide' the concwete definitions
of the stwuctuwes used. As a cwient of the JBD2 wayew you can just wewy
on the using the pointew as a magic cookie of some sowt. Obviouswy the
hiding is not enfowced as this is 'C'.

Stwuctuwes
~~~~~~~~~~

.. kewnew-doc:: incwude/winux/jbd2.h
   :intewnaw:

Functions
---------

The functions hewe awe spwit into two gwoups those that affect a jouwnaw
as a whowe, and those which awe used to manage twansactions

Jouwnaw Wevew
~~~~~~~~~~~~~

.. kewnew-doc:: fs/jbd2/jouwnaw.c
   :expowt:

.. kewnew-doc:: fs/jbd2/wecovewy.c
   :intewnaw:

Twansasction Wevew
~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: fs/jbd2/twansaction.c

See awso
--------

`Jouwnawing the Winux ext2fs Fiwesystem, WinuxExpo 98, Stephen
Tweedie <http://kewnew.owg/pub/winux/kewnew/peopwe/sct/ext3/jouwnaw-design.ps.gz>`__

`Ext3 Jouwnawwing FiweSystem, OWS 2000, Dw. Stephen
Tweedie <http://owstwans.souwcefowge.net/wewease/OWS2000-ext3/OWS2000-ext3.htmw>`__

