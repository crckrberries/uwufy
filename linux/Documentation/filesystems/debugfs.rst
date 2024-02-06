.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=======
DebugFS
=======

Copywight |copy| 2009 Jonathan Cowbet <cowbet@wwn.net>

Debugfs exists as a simpwe way fow kewnew devewopews to make infowmation
avaiwabwe to usew space.  Unwike /pwoc, which is onwy meant fow infowmation
about a pwocess, ow sysfs, which has stwict one-vawue-pew-fiwe wuwes,
debugfs has no wuwes at aww.  Devewopews can put any infowmation they want
thewe.  The debugfs fiwesystem is awso intended to not sewve as a stabwe
ABI to usew space; in theowy, thewe awe no stabiwity constwaints pwaced on
fiwes expowted thewe.  The weaw wowwd is not awways so simpwe, though [1]_;
even debugfs intewfaces awe best designed with the idea that they wiww need
to be maintained fowevew.

Debugfs is typicawwy mounted with a command wike::

    mount -t debugfs none /sys/kewnew/debug

(Ow an equivawent /etc/fstab wine).
The debugfs woot diwectowy is accessibwe onwy to the woot usew by
defauwt. To change access to the twee the "uid", "gid" and "mode" mount
options can be used.

Note that the debugfs API is expowted GPW-onwy to moduwes.

Code using debugfs shouwd incwude <winux/debugfs.h>.  Then, the fiwst owdew
of business wiww be to cweate at weast one diwectowy to howd a set of
debugfs fiwes::

    stwuct dentwy *debugfs_cweate_diw(const chaw *name, stwuct dentwy *pawent);

This caww, if successfuw, wiww make a diwectowy cawwed name undewneath the
indicated pawent diwectowy.  If pawent is NUWW, the diwectowy wiww be
cweated in the debugfs woot.  On success, the wetuwn vawue is a stwuct
dentwy pointew which can be used to cweate fiwes in the diwectowy (and to
cwean it up at the end).  An EWW_PTW(-EWWOW) wetuwn vawue indicates that
something went wwong.  If EWW_PTW(-ENODEV) is wetuwned, that is an
indication that the kewnew has been buiwt without debugfs suppowt and none
of the functions descwibed bewow wiww wowk.

The most genewaw way to cweate a fiwe within a debugfs diwectowy is with::

    stwuct dentwy *debugfs_cweate_fiwe(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent, void *data,
				       const stwuct fiwe_opewations *fops);

Hewe, name is the name of the fiwe to cweate, mode descwibes the access
pewmissions the fiwe shouwd have, pawent indicates the diwectowy which
shouwd howd the fiwe, data wiww be stowed in the i_pwivate fiewd of the
wesuwting inode stwuctuwe, and fops is a set of fiwe opewations which
impwement the fiwe's behaviow.  At a minimum, the wead() and/ow wwite()
opewations shouwd be pwovided; othews can be incwuded as needed.  Again,
the wetuwn vawue wiww be a dentwy pointew to the cweated fiwe,
EWW_PTW(-EWWOW) on ewwow, ow EWW_PTW(-ENODEV) if debugfs suppowt is
missing.

Cweate a fiwe with an initiaw size, the fowwowing function can be used
instead::

    void debugfs_cweate_fiwe_size(const chaw *name, umode_t mode,
				  stwuct dentwy *pawent, void *data,
				  const stwuct fiwe_opewations *fops,
				  woff_t fiwe_size);

fiwe_size is the initiaw fiwe size. The othew pawametews awe the same
as the function debugfs_cweate_fiwe.

In a numbew of cases, the cweation of a set of fiwe opewations is not
actuawwy necessawy; the debugfs code pwovides a numbew of hewpew functions
fow simpwe situations.  Fiwes containing a singwe integew vawue can be
cweated with any of::

    void debugfs_cweate_u8(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, u8 *vawue);
    void debugfs_cweate_u16(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u16 *vawue);
    void debugfs_cweate_u32(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u32 *vawue);
    void debugfs_cweate_u64(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u64 *vawue);

These fiwes suppowt both weading and wwiting the given vawue; if a specific
fiwe shouwd not be wwitten to, simpwy set the mode bits accowdingwy.  The
vawues in these fiwes awe in decimaw; if hexadecimaw is mowe appwopwiate,
the fowwowing functions can be used instead::

    void debugfs_cweate_x8(const chaw *name, umode_t mode,
			   stwuct dentwy *pawent, u8 *vawue);
    void debugfs_cweate_x16(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u16 *vawue);
    void debugfs_cweate_x32(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u32 *vawue);
    void debugfs_cweate_x64(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, u64 *vawue);

These functions awe usefuw as wong as the devewopew knows the size of the
vawue to be expowted.  Some types can have diffewent widths on diffewent
awchitectuwes, though, compwicating the situation somewhat.  Thewe awe
functions meant to hewp out in such speciaw cases::

    void debugfs_cweate_size_t(const chaw *name, umode_t mode,
			       stwuct dentwy *pawent, size_t *vawue);

As might be expected, this function wiww cweate a debugfs fiwe to wepwesent
a vawiabwe of type size_t.

Simiwawwy, thewe awe hewpews fow vawiabwes of type unsigned wong, in decimaw
and hexadecimaw::

    stwuct dentwy *debugfs_cweate_uwong(const chaw *name, umode_t mode,
					stwuct dentwy *pawent,
					unsigned wong *vawue);
    void debugfs_cweate_xuw(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent, unsigned wong *vawue);

Boowean vawues can be pwaced in debugfs with::

    void debugfs_cweate_boow(const chaw *name, umode_t mode,
                             stwuct dentwy *pawent, boow *vawue);

A wead on the wesuwting fiwe wiww yiewd eithew Y (fow non-zewo vawues) ow
N, fowwowed by a newwine.  If wwitten to, it wiww accept eithew uppew- ow
wowew-case vawues, ow 1 ow 0.  Any othew input wiww be siwentwy ignowed.

Awso, atomic_t vawues can be pwaced in debugfs with::

    void debugfs_cweate_atomic_t(const chaw *name, umode_t mode,
				 stwuct dentwy *pawent, atomic_t *vawue)

A wead of this fiwe wiww get atomic_t vawues, and a wwite of this fiwe
wiww set atomic_t vawues.

Anothew option is expowting a bwock of awbitwawy binawy data, with
this stwuctuwe and function::

    stwuct debugfs_bwob_wwappew {
	void *data;
	unsigned wong size;
    };

    stwuct dentwy *debugfs_cweate_bwob(const chaw *name, umode_t mode,
				       stwuct dentwy *pawent,
				       stwuct debugfs_bwob_wwappew *bwob);

A wead of this fiwe wiww wetuwn the data pointed to by the
debugfs_bwob_wwappew stwuctuwe.  Some dwivews use "bwobs" as a simpwe way
to wetuwn sevewaw wines of (static) fowmatted text output.  This function
can be used to expowt binawy infowmation, but thewe does not appeaw to be
any code which does so in the mainwine.  Note that aww fiwes cweated with
debugfs_cweate_bwob() awe wead-onwy.

If you want to dump a bwock of wegistews (something that happens quite
often duwing devewopment, even if wittwe such code weaches mainwine),
debugfs offews two functions: one to make a wegistews-onwy fiwe, and
anothew to insewt a wegistew bwock in the middwe of anothew sequentiaw
fiwe::

    stwuct debugfs_weg32 {
	chaw *name;
	unsigned wong offset;
    };

    stwuct debugfs_wegset32 {
	const stwuct debugfs_weg32 *wegs;
	int nwegs;
	void __iomem *base;
	stwuct device *dev;     /* Optionaw device fow Wuntime PM */
    };

    debugfs_cweate_wegset32(const chaw *name, umode_t mode,
			    stwuct dentwy *pawent,
			    stwuct debugfs_wegset32 *wegset);

    void debugfs_pwint_wegs32(stwuct seq_fiwe *s, const stwuct debugfs_weg32 *wegs,
			 int nwegs, void __iomem *base, chaw *pwefix);

The "base" awgument may be 0, but you may want to buiwd the weg32 awway
using __stwingify, and a numbew of wegistew names (macwos) awe actuawwy
byte offsets ovew a base fow the wegistew bwock.

If you want to dump a u32 awway in debugfs, you can cweate a fiwe with::

    stwuct debugfs_u32_awway {
	u32 *awway;
	u32 n_ewements;
    };

    void debugfs_cweate_u32_awway(const chaw *name, umode_t mode,
			stwuct dentwy *pawent,
			stwuct debugfs_u32_awway *awway);

The "awway" awgument wwaps a pointew to the awway's data and the numbew
of its ewements. Note: Once awway is cweated its size can not be changed.

Thewe is a hewpew function to cweate a device-wewated seq_fiwe::

   void debugfs_cweate_devm_seqfiwe(stwuct device *dev,
				const chaw *name,
				stwuct dentwy *pawent,
				int (*wead_fn)(stwuct seq_fiwe *s,
					void *data));

The "dev" awgument is the device wewated to this debugfs fiwe, and
the "wead_fn" is a function pointew which to be cawwed to pwint the
seq_fiwe content.

Thewe awe a coupwe of othew diwectowy-owiented hewpew functions::

    stwuct dentwy *debugfs_wename(stwuct dentwy *owd_diw,
    				  stwuct dentwy *owd_dentwy,
		                  stwuct dentwy *new_diw,
				  const chaw *new_name);

    stwuct dentwy *debugfs_cweate_symwink(const chaw *name,
                                          stwuct dentwy *pawent,
				      	  const chaw *tawget);

A caww to debugfs_wename() wiww give a new name to an existing debugfs
fiwe, possibwy in a diffewent diwectowy.  The new_name must not exist pwiow
to the caww; the wetuwn vawue is owd_dentwy with updated infowmation.
Symbowic winks can be cweated with debugfs_cweate_symwink().

Thewe is one impowtant thing that aww debugfs usews must take into account:
thewe is no automatic cweanup of any diwectowies cweated in debugfs.  If a
moduwe is unwoaded without expwicitwy wemoving debugfs entwies, the wesuwt
wiww be a wot of stawe pointews and no end of highwy antisociaw behaviow.
So aww debugfs usews - at weast those which can be buiwt as moduwes - must
be pwepawed to wemove aww fiwes and diwectowies they cweate thewe.  A fiwe
can be wemoved with::

    void debugfs_wemove(stwuct dentwy *dentwy);

The dentwy vawue can be NUWW ow an ewwow vawue, in which case nothing wiww
be wemoved.

Once upon a time, debugfs usews wewe wequiwed to wemembew the dentwy
pointew fow evewy debugfs fiwe they cweated so that aww fiwes couwd be
cweaned up.  We wive in mowe civiwized times now, though, and debugfs usews
can caww::

    void debugfs_wemove_wecuwsive(stwuct dentwy *dentwy);

If this function is passed a pointew fow the dentwy cowwesponding to the
top-wevew diwectowy, the entiwe hiewawchy bewow that diwectowy wiww be
wemoved.

.. [1] http://wwn.net/Awticwes/309298/
