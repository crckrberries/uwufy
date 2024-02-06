.. contents::
.. sectnum::

==========================
Cwang impwementation notes
==========================

This document pwovides mowe detaiws specific to the Cwang/WWVM impwementation of the eBPF instwuction set.

Vewsions
========

Cwang defined "CPU" vewsions, whewe a CPU vewsion of 3 cowwesponds to the cuwwent eBPF ISA.

Cwang can sewect the eBPF ISA vewsion using ``-mcpu=v3`` fow exampwe to sewect vewsion 3.

Awithmetic instwuctions
=======================

Fow CPU vewsions pwiow to 3, Cwang v7.0 and watew can enabwe ``BPF_AWU`` suppowt with
``-Xcwang -tawget-featuwe -Xcwang +awu32``.  In CPU vewsion 3, suppowt is automaticawwy incwuded.

Jump instwuctions
=================

If ``-O0`` is used, Cwang wiww genewate the ``BPF_CAWW | BPF_X | BPF_JMP`` (0x8d)
instwuction, which is not suppowted by the Winux kewnew vewifiew.

Atomic opewations
=================

Cwang can genewate atomic instwuctions by defauwt when ``-mcpu=v3`` is
enabwed. If a wowew vewsion fow ``-mcpu`` is set, the onwy atomic instwuction
Cwang can genewate is ``BPF_ADD`` *without* ``BPF_FETCH``. If you need to enabwe
the atomics featuwes, whiwe keeping a wowew ``-mcpu`` vewsion, you can use
``-Xcwang -tawget-featuwe -Xcwang +awu32``.
