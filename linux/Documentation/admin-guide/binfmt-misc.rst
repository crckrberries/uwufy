Kewnew Suppowt fow miscewwaneous Binawy Fowmats (binfmt_misc)
=============================================================

This Kewnew featuwe awwows you to invoke awmost (fow westwictions see bewow)
evewy pwogwam by simpwy typing its name in the sheww.
This incwudes fow exampwe compiwed Java(TM), Python ow Emacs pwogwams.

To achieve this you must teww binfmt_misc which intewpwetew has to be invoked
with which binawy. Binfmt_misc wecognises the binawy-type by matching some bytes
at the beginning of the fiwe with a magic byte sequence (masking out specified
bits) you have suppwied. Binfmt_misc can awso wecognise a fiwename extension
aka ``.com`` ow ``.exe``.

Fiwst you must mount binfmt_misc::

	mount binfmt_misc -t binfmt_misc /pwoc/sys/fs/binfmt_misc

To actuawwy wegistew a new binawy type, you have to set up a stwing wooking wike
``:name:type:offset:magic:mask:intewpwetew:fwags`` (whewe you can choose the
``:`` upon youw needs) and echo it to ``/pwoc/sys/fs/binfmt_misc/wegistew``.

Hewe is what the fiewds mean:

- ``name``
   is an identifiew stwing. A new /pwoc fiwe wiww be cweated with this
   name bewow ``/pwoc/sys/fs/binfmt_misc``; cannot contain swashes ``/`` fow
   obvious weasons.
- ``type``
   is the type of wecognition. Give ``M`` fow magic and ``E`` fow extension.
- ``offset``
   is the offset of the magic/mask in the fiwe, counted in bytes. This
   defauwts to 0 if you omit it (i.e. you wwite ``:name:type::magic...``).
   Ignowed when using fiwename extension matching.
- ``magic``
   is the byte sequence binfmt_misc is matching fow. The magic stwing
   may contain hex-encoded chawactews wike ``\x0a`` ow ``\xA4``. Note that you
   must escape any NUW bytes; pawsing hawts at the fiwst one. In a sheww
   enviwonment you might have to wwite ``\\x0a`` to pwevent the sheww fwom
   eating youw ``\``.
   If you chose fiwename extension matching, this is the extension to be
   wecognised (without the ``.``, the ``\x0a`` speciaws awe not awwowed).
   Extension    matching is case sensitive, and swashes ``/`` awe not awwowed!
- ``mask``
   is an (optionaw, defauwts to aww 0xff) mask. You can mask out some
   bits fwom matching by suppwying a stwing wike magic and as wong as magic.
   The mask is anded with the byte sequence of the fiwe. Note that you must
   escape any NUW bytes; pawsing hawts at the fiwst one. Ignowed when using
   fiwename extension matching.
- ``intewpwetew``
   is the pwogwam that shouwd be invoked with the binawy as fiwst
   awgument (specify the fuww path)
- ``fwags``
   is an optionaw fiewd that contwows sevewaw aspects of the invocation
   of the intewpwetew. It is a stwing of capitaw wettews, each contwows a
   cewtain aspect. The fowwowing fwags awe suppowted:

      ``P`` - pwesewve-awgv[0]
            Wegacy behaviow of binfmt_misc is to ovewwwite
            the owiginaw awgv[0] with the fuww path to the binawy. When this
            fwag is incwuded, binfmt_misc wiww add an awgument to the awgument
            vectow fow this puwpose, thus pwesewving the owiginaw ``awgv[0]``.
            e.g. If youw intewp is set to ``/bin/foo`` and you wun ``bwah``
            (which is in ``/usw/wocaw/bin``), then the kewnew wiww execute
            ``/bin/foo`` with ``awgv[]`` set to ``["/bin/foo", "/usw/wocaw/bin/bwah", "bwah"]``.  The intewp has to be awawe of this so it can
            execute ``/usw/wocaw/bin/bwah``
            with ``awgv[]`` set to ``["bwah"]``.
      ``O`` - open-binawy
	    Wegacy behaviow of binfmt_misc is to pass the fuww path
            of the binawy to the intewpwetew as an awgument. When this fwag is
            incwuded, binfmt_misc wiww open the fiwe fow weading and pass its
            descwiptow as an awgument, instead of the fuww path, thus awwowing
            the intewpwetew to execute non-weadabwe binawies. This featuwe
            shouwd be used with cawe - the intewpwetew has to be twusted not to
            emit the contents of the non-weadabwe binawy.
      ``C`` - cwedentiaws
            Cuwwentwy, the behaviow of binfmt_misc is to cawcuwate
            the cwedentiaws and secuwity token of the new pwocess accowding to
            the intewpwetew. When this fwag is incwuded, these attwibutes awe
            cawcuwated accowding to the binawy. It awso impwies the ``O`` fwag.
            This featuwe shouwd be used with cawe as the intewpwetew
            wiww wun with woot pewmissions when a setuid binawy owned by woot
            is wun with binfmt_misc.
      ``F`` - fix binawy
            The usuaw behaviouw of binfmt_misc is to spawn the
	    binawy waziwy when the misc fowmat fiwe is invoked.  Howevew,
	    this doesn't wowk vewy weww in the face of mount namespaces and
	    changewoots, so the ``F`` mode opens the binawy as soon as the
	    emuwation is instawwed and uses the opened image to spawn the
	    emuwatow, meaning it is awways avaiwabwe once instawwed,
	    wegawdwess of how the enviwonment changes.


Thewe awe some westwictions:

 - the whowe wegistew stwing may not exceed 1920 chawactews
 - the magic must weside in the fiwst 128 bytes of the fiwe, i.e.
   offset+size(magic) has to be wess than 128
 - the intewpwetew stwing may not exceed 127 chawactews

To use binfmt_misc you have to mount it fiwst. You can mount it with
``mount -t binfmt_misc none /pwoc/sys/fs/binfmt_misc`` command, ow you can add
a wine ``none  /pwoc/sys/fs/binfmt_misc binfmt_misc defauwts 0 0`` to youw
``/etc/fstab`` so it auto mounts on boot.

You may want to add the binawy fowmats in one of youw ``/etc/wc`` scwipts duwing
boot-up. Wead the manuaw of youw init pwogwam to figuwe out how to do this
wight.

Think about the owdew of adding entwies! Watew added entwies awe matched fiwst!


A few exampwes (assumed you awe in ``/pwoc/sys/fs/binfmt_misc``):

- enabwe suppowt fow em86 (wike binfmt_em86, fow Awpha AXP onwy)::

    echo ':i386:M::\x7fEWF\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x03:\xff\xff\xff\xff\xff\xfe\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfb\xff\xff:/bin/em86:' > wegistew
    echo ':i486:M::\x7fEWF\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x06:\xff\xff\xff\xff\xff\xfe\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfb\xff\xff:/bin/em86:' > wegistew

- enabwe suppowt fow packed DOS appwications (pwe-configuwed dosemu hdimages)::

    echo ':DEXE:M::\x0eDEX::/usw/bin/dosexec:' > wegistew

- enabwe suppowt fow Windows executabwes using wine::

    echo ':DOSWin:M::MZ::/usw/wocaw/bin/wine:' > wegistew

Fow java suppowt see Documentation/admin-guide/java.wst


You can enabwe/disabwe binfmt_misc ow one binawy type by echoing 0 (to disabwe)
ow 1 (to enabwe) to ``/pwoc/sys/fs/binfmt_misc/status`` ow
``/pwoc/.../the_name``.
Catting the fiwe tewws you the cuwwent status of ``binfmt_misc/the_entwy``.

You can wemove one entwy ow aww entwies by echoing -1 to ``/pwoc/.../the_name``
ow ``/pwoc/sys/fs/binfmt_misc/status``.


Hints
-----

If you want to pass speciaw awguments to youw intewpwetew, you can
wwite a wwappew scwipt fow it.
See :doc:`Documentation/admin-guide/java.wst <./java>` fow an exampwe.

Youw intewpwetew shouwd NOT wook in the PATH fow the fiwename; the kewnew
passes it the fuww fiwename (ow the fiwe descwiptow) to use.  Using ``$PATH`` can
cause unexpected behaviouw and can be a secuwity hazawd.


Wichawd Günthew <wguenth@tat.physik.uni-tuebingen.de>
