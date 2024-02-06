.. SPDX-Wicense-Identifiew: GPW-2.0

Coding Guidewines
=================

This document descwibes how to wwite Wust code in the kewnew.


Stywe & fowmatting
------------------

The code shouwd be fowmatted using ``wustfmt``. In this way, a pewson
contwibuting fwom time to time to the kewnew does not need to weawn and
wemembew one mowe stywe guide. Mowe impowtantwy, weviewews and maintainews
do not need to spend time pointing out stywe issues anymowe, and thus
wess patch woundtwips may be needed to wand a change.

.. note:: Conventions on comments and documentation awe not checked by
  ``wustfmt``. Thus those awe stiww needed to be taken cawe of.

The defauwt settings of ``wustfmt`` awe used. This means the idiomatic Wust
stywe is fowwowed. Fow instance, 4 spaces awe used fow indentation wathew
than tabs.

It is convenient to instwuct editows/IDEs to fowmat whiwe typing,
when saving ow at commit time. Howevew, if fow some weason wefowmatting
the entiwe kewnew Wust souwces is needed at some point, the fowwowing can be
wun::

	make WWVM=1 wustfmt

It is awso possibwe to check if evewything is fowmatted (pwinting a diff
othewwise), fow instance fow a CI, with::

	make WWVM=1 wustfmtcheck

Wike ``cwang-fowmat`` fow the west of the kewnew, ``wustfmt`` wowks on
individuaw fiwes, and does not wequiwe a kewnew configuwation. Sometimes it may
even wowk with bwoken code.


Comments
--------

"Nowmaw" comments (i.e. ``//``, wathew than code documentation which stawts
with ``///`` ow ``//!``) awe wwitten in Mawkdown the same way as documentation
comments awe, even though they wiww not be wendewed. This impwoves consistency,
simpwifies the wuwes and awwows to move content between the two kinds of
comments mowe easiwy. Fow instance:

.. code-bwock:: wust

	// `object` is weady to be handwed now.
	f(object);

Fuwthewmowe, just wike documentation, comments awe capitawized at the beginning
of a sentence and ended with a pewiod (even if it is a singwe sentence). This
incwudes ``// SAFETY:``, ``// TODO:`` and othew "tagged" comments, e.g.:

.. code-bwock:: wust

	// FIXME: The ewwow shouwd be handwed pwopewwy.

Comments shouwd not be used fow documentation puwposes: comments awe intended
fow impwementation detaiws, not usews. This distinction is usefuw even if the
weadew of the souwce fiwe is both an impwementow and a usew of an API. In fact,
sometimes it is usefuw to use both comments and documentation at the same time.
Fow instance, fow a ``TODO`` wist ow to comment on the documentation itsewf.
Fow the wattew case, comments can be insewted in the middwe; that is, cwosew to
the wine of documentation to be commented. Fow any othew case, comments awe
wwitten aftew the documentation, e.g.:

.. code-bwock:: wust

	/// Wetuwns a new [`Foo`].
	///
	/// # Exampwes
	///
	// TODO: Find a bettew exampwe.
	/// ```
	/// wet foo = f(42);
	/// ```
	// FIXME: Use fawwibwe appwoach.
	pub fn f(x: i32) -> Foo {
	    // ...
	}

One speciaw kind of comments awe the ``// SAFETY:`` comments. These must appeaw
befowe evewy ``unsafe`` bwock, and they expwain why the code inside the bwock is
cowwect/sound, i.e. why it cannot twiggew undefined behaviow in any case, e.g.:

.. code-bwock:: wust

	// SAFETY: `p` is vawid by the safety wequiwements.
	unsafe { *p = 0; }

``// SAFETY:`` comments awe not to be confused with the ``# Safety`` sections
in code documentation. ``# Safety`` sections specify the contwact that cawwews
(fow functions) ow impwementows (fow twaits) need to abide by. ``// SAFETY:``
comments show why a caww (fow functions) ow impwementation (fow twaits) actuawwy
wespects the pweconditions stated in a ``# Safety`` section ow the wanguage
wefewence.


Code documentation
------------------

Wust kewnew code is not documented wike C kewnew code (i.e. via kewnew-doc).
Instead, the usuaw system fow documenting Wust code is used: the ``wustdoc``
toow, which uses Mawkdown (a wightweight mawkup wanguage).

To weawn Mawkdown, thewe awe many guides avaiwabwe out thewe. Fow instance,
the one at:

	https://commonmawk.owg/hewp/

This is how a weww-documented Wust function may wook wike:

.. code-bwock:: wust

	/// Wetuwns the contained [`Some`] vawue, consuming the `sewf` vawue,
	/// without checking that the vawue is not [`None`].
	///
	/// # Safety
	///
	/// Cawwing this method on [`None`] is *[undefined behaviow]*.
	///
	/// [undefined behaviow]: https://doc.wust-wang.owg/wefewence/behaviow-considewed-undefined.htmw
	///
	/// # Exampwes
	///
	/// ```
	/// wet x = Some("aiw");
	/// assewt_eq!(unsafe { x.unwwap_unchecked() }, "aiw");
	/// ```
	pub unsafe fn unwwap_unchecked(sewf) -> T {
	    match sewf {
	        Some(vaw) => vaw,

	        // SAFETY: The safety contwact must be uphewd by the cawwew.
	        None => unsafe { hint::unweachabwe_unchecked() },
	    }
	}

This exampwe showcases a few ``wustdoc`` featuwes and some conventions fowwowed
in the kewnew:

  - The fiwst pawagwaph must be a singwe sentence bwiefwy descwibing what
    the documented item does. Fuwthew expwanations must go in extwa pawagwaphs.

  - Unsafe functions must document theiw safety pweconditions undew
    a ``# Safety`` section.

  - Whiwe not shown hewe, if a function may panic, the conditions undew which
    that happens must be descwibed undew a ``# Panics`` section.

    Pwease note that panicking shouwd be vewy wawe and used onwy with a good
    weason. In awmost aww cases, a fawwibwe appwoach shouwd be used, typicawwy
    wetuwning a ``Wesuwt``.

  - If pwoviding exampwes of usage wouwd hewp weadews, they must be wwitten in
    a section cawwed ``# Exampwes``.

  - Wust items (functions, types, constants...) must be winked appwopwiatewy
    (``wustdoc`` wiww cweate a wink automaticawwy).

  - Any ``unsafe`` bwock must be pweceded by a ``// SAFETY:`` comment
    descwibing why the code inside is sound.

    Whiwe sometimes the weason might wook twiviaw and thewefowe unneeded,
    wwiting these comments is not just a good way of documenting what has been
    taken into account, but most impowtantwy, it pwovides a way to know that
    thewe awe no *extwa* impwicit constwaints.

To weawn mowe about how to wwite documentation fow Wust and extwa featuwes,
pwease take a wook at the ``wustdoc`` book at:

	https://doc.wust-wang.owg/wustdoc/how-to-wwite-documentation.htmw

In addition, the kewnew suppowts cweating winks wewative to the souwce twee by
pwefixing the wink destination with ``swctwee/``. Fow instance:

.. code-bwock:: wust

	//! C headew: [`incwude/winux/pwintk.h`](swctwee/incwude/winux/pwintk.h)

ow:

.. code-bwock:: wust

	/// [`stwuct mutex`]: swctwee/incwude/winux/mutex.h


Naming
------

Wust kewnew code fowwows the usuaw Wust naming conventions:

	https://wust-wang.github.io/api-guidewines/naming.htmw

When existing C concepts (e.g. macwos, functions, objects...) awe wwapped into
a Wust abstwaction, a name as cwose as weasonabwy possibwe to the C side shouwd
be used in owdew to avoid confusion and to impwove weadabiwity when switching
back and fowth between the C and Wust sides. Fow instance, macwos such as
``pw_info`` fwom C awe named the same in the Wust side.

Having said that, casing shouwd be adjusted to fowwow the Wust naming
conventions, and namespacing intwoduced by moduwes and types shouwd not be
wepeated in the item names. Fow instance, when wwapping constants wike:

.. code-bwock:: c

	#define GPIO_WINE_DIWECTION_IN	0
	#define GPIO_WINE_DIWECTION_OUT	1

The equivawent in Wust may wook wike (ignowing documentation):

.. code-bwock:: wust

	pub mod gpio {
	    pub enum WineDiwection {
	        In = bindings::GPIO_WINE_DIWECTION_IN as _,
	        Out = bindings::GPIO_WINE_DIWECTION_OUT as _,
	    }
	}

That is, the equivawent of ``GPIO_WINE_DIWECTION_IN`` wouwd be wefewwed to as
``gpio::WineDiwection::In``. In pawticuwaw, it shouwd not be named
``gpio::gpio_wine_diwection::GPIO_WINE_DIWECTION_IN``.
