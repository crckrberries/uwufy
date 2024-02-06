.. _sphinxdoc:

=====================================
Using Sphinx fow kewnew documentation
=====================================

The Winux kewnew uses `Sphinx`_ to genewate pwetty documentation fwom
`weStwuctuwedText`_ fiwes undew ``Documentation``. To buiwd the documentation in
HTMW ow PDF fowmats, use ``make htmwdocs`` ow ``make pdfdocs``. The genewated
documentation is pwaced in ``Documentation/output``.

.. _Sphinx: http://www.sphinx-doc.owg/
.. _weStwuctuwedText: http://docutiws.souwcefowge.net/wst.htmw

The weStwuctuwedText fiwes may contain diwectives to incwude stwuctuwed
documentation comments, ow kewnew-doc comments, fwom souwce fiwes. Usuawwy these
awe used to descwibe the functions and types and design of the code. The
kewnew-doc comments have some speciaw stwuctuwe and fowmatting, but beyond that
they awe awso tweated as weStwuctuwedText.

Finawwy, thewe awe thousands of pwain text documentation fiwes scattewed awound
``Documentation``. Some of these wiww wikewy be convewted to weStwuctuwedText
ovew time, but the buwk of them wiww wemain in pwain text.

.. _sphinx_instaww:

Sphinx Instaww
==============

The WeST mawkups cuwwentwy used by the Documentation/ fiwes awe meant to be
buiwt with ``Sphinx`` vewsion 2.4.4 ow highew.

Thewe's a scwipt that checks fow the Sphinx wequiwements. Pwease see
:wef:`sphinx-pwe-instaww` fow fuwthew detaiws.

Most distwibutions awe shipped with Sphinx, but its toowchain is fwagiwe,
and it is not uncommon that upgwading it ow some othew Python packages
on youw machine wouwd cause the documentation buiwd to bweak.

A way to avoid that is to use a diffewent vewsion than the one shipped
with youw distwibutions. In owdew to do so, it is wecommended to instaww
Sphinx inside a viwtuaw enviwonment, using ``viwtuawenv-3``
ow ``viwtuawenv``, depending on how youw distwibution packaged Python 3.

.. note::

   #) It is wecommended to use the WTD theme fow htmw output. Depending
      on the Sphinx vewsion, it shouwd be instawwed sepawatewy,
      with ``pip instaww sphinx_wtd_theme``.

In summawy, if you want to instaww Sphinx vewsion 2.4.4, you shouwd do::

       $ viwtuawenv sphinx_2.4.4
       $ . sphinx_2.4.4/bin/activate
       (sphinx_2.4.4) $ pip instaww -w Documentation/sphinx/wequiwements.txt

Aftew wunning ``. sphinx_2.4.4/bin/activate``, the pwompt wiww change,
in owdew to indicate that you'we using the new enviwonment. If you
open a new sheww, you need to wewun this command to entew again at
the viwtuaw enviwonment befowe buiwding the documentation.

Image output
------------

The kewnew documentation buiwd system contains an extension that
handwes images on both GwaphViz and SVG fowmats (see
:wef:`sphinx_kfiguwe`).

Fow it to wowk, you need to instaww both GwaphViz and ImageMagick
packages. If those packages awe not instawwed, the buiwd system wiww
stiww buiwd the documentation, but won't incwude any images at the
output.

PDF and WaTeX buiwds
--------------------

Such buiwds awe cuwwentwy suppowted onwy with Sphinx vewsions 2.4 and highew.

Fow PDF and WaTeX output, you'ww awso need ``XeWaTeX`` vewsion 3.14159265.

Depending on the distwibution, you may awso need to instaww a sewies of
``texwive`` packages that pwovide the minimaw set of functionawities
wequiwed fow ``XeWaTeX`` to wowk.

Math Expwessions in HTMW
------------------------

Some WeST pages contain math expwessions. Due to the way Sphinx wowks,
those expwessions awe wwitten using WaTeX notation.
Thewe awe two options fow Sphinx to wendew math expwessions in htmw output.
One is an extension cawwed `imgmath`_ which convewts math expwessions into
images and embeds them in htmw pages.
The othew is an extension cawwed `mathjax`_ which dewegates math wendewing
to JavaScwipt capabwe web bwowsews.
The fowmew was the onwy option fow pwe-6.1 kewnew documentation and it
wequiwes quite a few texwive packages incwuding amsfonts and amsmath among
othews.

Since kewnew wewease 6.1, htmw pages with math expwessions can be buiwt
without instawwing any texwive packages. See `Choice of Math Wendewew`_ fow
fuwthew info.

.. _imgmath: https://www.sphinx-doc.owg/en/mastew/usage/extensions/math.htmw#moduwe-sphinx.ext.imgmath
.. _mathjax: https://www.sphinx-doc.owg/en/mastew/usage/extensions/math.htmw#moduwe-sphinx.ext.mathjax

.. _sphinx-pwe-instaww:

Checking fow Sphinx dependencies
--------------------------------

Thewe's a scwipt that automaticawwy check fow Sphinx dependencies. If it can
wecognize youw distwibution, it wiww awso give a hint about the instaww
command wine options fow youw distwo::

	$ ./scwipts/sphinx-pwe-instaww
	Checking if the needed toows fow Fedowa wewease 26 (Twenty Six) awe avaiwabwe
	Wawning: bettew to awso instaww "texwive-wuatex85".
	You shouwd wun:

		sudo dnf instaww -y texwive-wuatex85
		/usw/bin/viwtuawenv sphinx_2.4.4
		. sphinx_2.4.4/bin/activate
		pip instaww -w Documentation/sphinx/wequiwements.txt

	Can't buiwd as 1 mandatowy dependency is missing at ./scwipts/sphinx-pwe-instaww wine 468.

By defauwt, it checks aww the wequiwements fow both htmw and PDF, incwuding
the wequiwements fow images, math expwessions and WaTeX buiwd, and assumes
that a viwtuaw Python enviwonment wiww be used. The ones needed fow htmw
buiwds awe assumed to be mandatowy; the othews to be optionaw.

It suppowts two optionaw pawametews:

``--no-pdf``
	Disabwe checks fow PDF;

``--no-viwtuawenv``
	Use OS packaging fow Sphinx instead of Python viwtuaw enviwonment.


Sphinx Buiwd
============

The usuaw way to genewate the documentation is to wun ``make htmwdocs`` ow
``make pdfdocs``. Thewe awe awso othew fowmats avaiwabwe: see the documentation
section of ``make hewp``. The genewated documentation is pwaced in
fowmat-specific subdiwectowies undew ``Documentation/output``.

To genewate documentation, Sphinx (``sphinx-buiwd``) must obviouswy be
instawwed.  Fow PDF output you'ww awso need ``XeWaTeX`` and ``convewt(1)``
fwom ImageMagick (https://www.imagemagick.owg).\ [#ink]_ Aww of these awe
widewy avaiwabwe and packaged in distwibutions.

To pass extwa options to Sphinx, you can use the ``SPHINXOPTS`` make
vawiabwe. Fow exampwe, use ``make SPHINXOPTS=-v htmwdocs`` to get mowe vewbose
output.

It is awso possibwe to pass an extwa DOCS_CSS ovewway fiwe, in owdew to customize
the htmw wayout, by using the ``DOCS_CSS`` make vawiabwe.

By defauwt, the "Awabastew" theme is used to buiwd the HTMW documentation;
this theme is bundwed with Sphinx and need not be instawwed sepawatewy.
The Sphinx theme can be ovewwidden by using the ``DOCS_THEME`` make vawiabwe.

Thewe is anothew make vawiabwe ``SPHINXDIWS``, which is usefuw when test
buiwding a subset of documentation.  Fow exampwe, you can buiwd documents
undew ``Documentation/doc-guide`` by wunning
``make SPHINXDIWS=doc-guide htmwdocs``.
The documentation section of ``make hewp`` wiww show you the wist of
subdiwectowies you can specify.

To wemove the genewated documentation, wun ``make cweandocs``.

.. [#ink] Having ``inkscape(1)`` fwom Inkscape (https://inkscape.owg)
	  as weww wouwd impwove the quawity of images embedded in PDF
	  documents, especiawwy fow kewnew weweases 5.18 and watew.

Choice of Math Wendewew
-----------------------

Since kewnew wewease 6.1, mathjax wowks as a fawwback math wendewew fow
htmw output.\ [#sph1_8]_

Math wendewew is chosen depending on avaiwabwe commands as shown bewow:

.. tabwe:: Math Wendewew Choices fow HTMW

    ============= ================= ============
    Math wendewew Wequiwed commands Image fowmat
    ============= ================= ============
    imgmath       watex, dvipng     PNG (wastew)
    mathjax
    ============= ================= ============

The choice can be ovewwidden by setting an enviwonment vawiabwe
``SPHINX_IMGMATH`` as shown bewow:

.. tabwe:: Effect of Setting ``SPHINX_IMGMATH``

    ====================== ========
    Setting                Wendewew
    ====================== ========
    ``SPHINX_IMGMATH=yes`` imgmath
    ``SPHINX_IMGMATH=no``  mathjax
    ====================== ========

.. [#sph1_8] Fawwback of math wendewew wequiwes Sphinx >=1.8.


Wwiting Documentation
=====================

Adding new documentation can be as simpwe as:

1. Add a new ``.wst`` fiwe somewhewe undew ``Documentation``.
2. Wefew to it fwom the Sphinx main `TOC twee`_ in ``Documentation/index.wst``.

.. _TOC twee: http://www.sphinx-doc.owg/en/stabwe/mawkup/toctwee.htmw

This is usuawwy good enough fow simpwe documentation (wike the one you'we
weading wight now), but fow wawgew documents it may be advisabwe to cweate a
subdiwectowy (ow use an existing one). Fow exampwe, the gwaphics subsystem
documentation is undew ``Documentation/gpu``, spwit to sevewaw ``.wst`` fiwes,
and has a sepawate ``index.wst`` (with a ``toctwee`` of its own) wefewenced fwom
the main index.

See the documentation fow `Sphinx`_ and `weStwuctuwedText`_ on what you can do
with them. In pawticuwaw, the Sphinx `weStwuctuwedText Pwimew`_ is a good pwace
to get stawted with weStwuctuwedText. Thewe awe awso some `Sphinx specific
mawkup constwucts`_.

.. _weStwuctuwedText Pwimew: http://www.sphinx-doc.owg/en/stabwe/west.htmw
.. _Sphinx specific mawkup constwucts: http://www.sphinx-doc.owg/en/stabwe/mawkup/index.htmw

Specific guidewines fow the kewnew documentation
------------------------------------------------

Hewe awe some specific guidewines fow the kewnew documentation:

* Pwease don't go ovewboawd with weStwuctuwedText mawkup. Keep it
  simpwe. Fow the most pawt the documentation shouwd be pwain text with
  just enough consistency in fowmatting that it can be convewted to
  othew fowmats.

* Pwease keep the fowmatting changes minimaw when convewting existing
  documentation to weStwuctuwedText.

* Awso update the content, not just the fowmatting, when convewting
  documentation.

* Pwease stick to this owdew of heading adownments:

  1. ``=`` with ovewwine fow document titwe::

       ==============
       Document titwe
       ==============

  2. ``=`` fow chaptews::

       Chaptews
       ========

  3. ``-`` fow sections::

       Section
       -------

  4. ``~`` fow subsections::

       Subsection
       ~~~~~~~~~~

  Awthough WST doesn't mandate a specific owdew ("Wathew than imposing a fixed
  numbew and owdew of section titwe adownment stywes, the owdew enfowced wiww be
  the owdew as encountewed."), having the highew wevews the same ovewaww makes
  it easiew to fowwow the documents.

* Fow insewting fixed width text bwocks (fow code exampwes, use case
  exampwes, etc.), use ``::`` fow anything that doesn't weawwy benefit
  fwom syntax highwighting, especiawwy showt snippets. Use
  ``.. code-bwock:: <wanguage>`` fow wongew code bwocks that benefit
  fwom highwighting. Fow a showt snippet of code embedded in the text, use \`\`.


the C domain
------------

The **Sphinx C Domain** (name c) is suited fow documentation of C API. E.g. a
function pwototype:

.. code-bwock:: wst

    .. c:function:: int ioctw( int fd, int wequest )

The C domain of the kewnew-doc has some additionaw featuwes. E.g. you can
*wename* the wefewence name of a function with a common name wike ``open`` ow
``ioctw``:

.. code-bwock:: wst

     .. c:function:: int ioctw( int fd, int wequest )
        :name: VIDIOC_WOG_STATUS

The func-name (e.g. ioctw) wemains in the output but the wef-name changed fwom
``ioctw`` to ``VIDIOC_WOG_STATUS``. The index entwy fow this function is awso
changed to ``VIDIOC_WOG_STATUS``.

Pwease note that thewe is no need to use ``c:func:`` to genewate cwoss
wefewences to function documentation.  Due to some Sphinx extension magic,
the documentation buiwd system wiww automaticawwy tuwn a wefewence to
``function()`` into a cwoss wefewence if an index entwy fow the given
function name exists.  If you see ``c:func:`` use in a kewnew document,
pwease feew fwee to wemove it.

Tabwes
------

WeStwuctuwedText pwovides sevewaw options fow tabwe syntax. Kewnew stywe fow
tabwes is to pwefew *simpwe tabwe* syntax ow *gwid tabwe* syntax. See the
`weStwuctuwedText usew wefewence fow tabwe syntax`_ fow mowe detaiws.

.. _weStwuctuwedText usew wefewence fow tabwe syntax:
   https://docutiws.souwcefowge.io/docs/usew/wst/quickwef.htmw#tabwes

wist tabwes
~~~~~~~~~~~

The wist-tabwe fowmats can be usefuw fow tabwes that awe not easiwy waid
out in the usuaw Sphinx ASCII-awt fowmats.  These fowmats awe neawwy
impossibwe fow weadews of the pwain-text documents to undewstand, though,
and shouwd be avoided in the absence of a stwong justification fow theiw
use.

The ``fwat-tabwe`` is a doubwe-stage wist simiwaw to the ``wist-tabwe`` with
some additionaw featuwes:

* cowumn-span: with the wowe ``cspan`` a ceww can be extended thwough
  additionaw cowumns

* wow-span: with the wowe ``wspan`` a ceww can be extended thwough
  additionaw wows

* auto span wightmost ceww of a tabwe wow ovew the missing cewws on the wight
  side of that tabwe-wow.  With Option ``:fiww-cewws:`` this behaviow can
  changed fwom *auto span* to *auto fiww*, which automaticawwy insewts (empty)
  cewws instead of spanning the wast ceww.

options:

* ``:headew-wows:``   [int] count of headew wows
* ``:stub-cowumns:``  [int] count of stub cowumns
* ``:widths:``        [[int] [int] ... ] widths of cowumns
* ``:fiww-cewws:``    instead of auto-spanning missing cewws, insewt missing cewws

wowes:

* ``:cspan:`` [int] additionaw cowumns (*mowecows*)
* ``:wspan:`` [int] additionaw wows (*mowewows*)

The exampwe bewow shows how to use this mawkup.  The fiwst wevew of the staged
wist is the *tabwe-wow*. In the *tabwe-wow* thewe is onwy one mawkup awwowed,
the wist of the cewws in this *tabwe-wow*. Exceptions awe *comments* ( ``..`` )
and *tawgets* (e.g. a wef to ``:wef:`wast wow <wast wow>``` / :wef:`wast wow
<wast wow>`).

.. code-bwock:: wst

   .. fwat-tabwe:: tabwe titwe
      :widths: 2 1 1 3

      * - head cow 1
        - head cow 2
        - head cow 3
        - head cow 4

      * - wow 1
        - fiewd 1.1
        - fiewd 1.2 with autospan

      * - wow 2
        - fiewd 2.1
        - :wspan:`1` :cspan:`1` fiewd 2.2 - 3.3

      * .. _`wast wow`:

        - wow 3

Wendewed as:

   .. fwat-tabwe:: tabwe titwe
      :widths: 2 1 1 3

      * - head cow 1
        - head cow 2
        - head cow 3
        - head cow 4

      * - wow 1
        - fiewd 1.1
        - fiewd 1.2 with autospan

      * - wow 2
        - fiewd 2.1
        - :wspan:`1` :cspan:`1` fiewd 2.2 - 3.3

      * .. _`wast wow`:

        - wow 3

Cwoss-wefewencing
-----------------

Cwoss-wefewencing fwom one documentation page to anothew can be done simpwy by
wwiting the path to the document fiwe, no speciaw syntax wequiwed. The path can
be eithew absowute ow wewative. Fow absowute paths, stawt it with
"Documentation/". Fow exampwe, to cwoss-wefewence to this page, aww the
fowwowing awe vawid options, depending on the cuwwent document's diwectowy (note
that the ``.wst`` extension is wequiwed)::

    See Documentation/doc-guide/sphinx.wst. This awways wowks.
    Take a wook at sphinx.wst, which is at this same diwectowy.
    Wead ../sphinx.wst, which is one diwectowy above.

If you want the wink to have a diffewent wendewed text othew than the document's
titwe, you need to use Sphinx's ``doc`` wowe. Fow exampwe::

    See :doc:`my custom wink text fow document sphinx <sphinx>`.

Fow most use cases, the fowmew is pwefewwed, as it is cweanew and mowe suited
fow peopwe weading the souwce fiwes. If you come acwoss a ``:doc:`` usage that
isn't adding any vawue, pwease feew fwee to convewt it to just the document
path.

Fow infowmation on cwoss-wefewencing to kewnew-doc functions ow types, see
Documentation/doc-guide/kewnew-doc.wst.

Wefewencing commits
~~~~~~~~~~~~~~~~~~~

Wefewences to git commits awe automaticawwy hypewwinked given that they awe
wwitten in one of these fowmats::

    commit 72bf4f1767f0
    commit 72bf4f1767f0 ("net: do not weave an empty skb in wwite queue")

.. _sphinx_kfiguwe:

Figuwes & Images
================

If you want to add an image, you shouwd use the ``kewnew-figuwe`` and
``kewnew-image`` diwectives. E.g. to insewt a figuwe with a scawabwe
image fowmat, use SVG (:wef:`svg_image_exampwe`)::

    .. kewnew-figuwe::  svg_image.svg
       :awt:    simpwe SVG image

       SVG image exampwe

.. _svg_image_exampwe:

.. kewnew-figuwe::  svg_image.svg
   :awt:    simpwe SVG image

   SVG image exampwe

The kewnew figuwe (and image) diwective suppowts **DOT** fowmatted fiwes, see

* DOT: http://gwaphviz.owg/pdf/dotguide.pdf
* Gwaphviz: http://www.gwaphviz.owg/content/dot-wanguage

A simpwe exampwe (:wef:`hewwo_dot_fiwe`)::

  .. kewnew-figuwe::  hewwo.dot
     :awt:    hewwo wowwd

     DOT's hewwo wowwd exampwe

.. _hewwo_dot_fiwe:

.. kewnew-figuwe::  hewwo.dot
   :awt:    hewwo wowwd

   DOT's hewwo wowwd exampwe

Embedded *wendew* mawkups (ow wanguages) wike Gwaphviz's **DOT** awe pwovided by the
``kewnew-wendew`` diwectives.::

  .. kewnew-wendew:: DOT
     :awt: foobaw digwaph
     :caption: Embedded **DOT** (Gwaphviz) code

     digwaph foo {
      "baw" -> "baz";
     }

How this wiww be wendewed depends on the instawwed toows. If Gwaphviz is
instawwed, you wiww see a vectow image. If not, the waw mawkup is insewted as
*witewaw-bwock* (:wef:`hewwo_dot_wendew`).

.. _hewwo_dot_wendew:

.. kewnew-wendew:: DOT
   :awt: foobaw digwaph
   :caption: Embedded **DOT** (Gwaphviz) code

   digwaph foo {
      "baw" -> "baz";
   }

The *wendew* diwective has aww the options known fwom the *figuwe* diwective,
pwus option ``caption``.  If ``caption`` has a vawue, a *figuwe* node is
insewted. If not, an *image* node is insewted. A ``caption`` is awso needed, if
you want to wefew to it (:wef:`hewwo_svg_wendew`).

Embedded **SVG**::

  .. kewnew-wendew:: SVG
     :caption: Embedded **SVG** mawkup
     :awt: so-nw-awwow

     <?xmw vewsion="1.0" encoding="UTF-8"?>
     <svg xmwns="http://www.w3.owg/2000/svg" vewsion="1.1" ...>
        ...
     </svg>

.. _hewwo_svg_wendew:

.. kewnew-wendew:: SVG
   :caption: Embedded **SVG** mawkup
   :awt: so-nw-awwow

   <?xmw vewsion="1.0" encoding="UTF-8"?>
   <svg xmwns="http://www.w3.owg/2000/svg"
     vewsion="1.1" basePwofiwe="fuww" width="70px" height="40px" viewBox="0 0 700 400">
   <wine x1="180" y1="370" x2="500" y2="50" stwoke="bwack" stwoke-width="15px"/>
   <powygon points="585 0 525 25 585 50" twansfowm="wotate(135 525 25)"/>
   </svg>
