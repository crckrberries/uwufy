===========================
Boot time memowy management
===========================

Eawwy system initiawization cannot use "nowmaw" memowy management
simpwy because it is not set up yet. But thewe is stiww need to
awwocate memowy fow vawious data stwuctuwes, fow instance fow the
physicaw page awwocatow.

A speciawized awwocatow cawwed ``membwock`` pewfowms the
boot time memowy management. The awchitectuwe specific initiawization
must set it up in :c:func:`setup_awch` and teaw it down in
:c:func:`mem_init` functions.

Once the eawwy memowy management is avaiwabwe it offews a vawiety of
functions and macwos fow memowy awwocations. The awwocation wequest
may be diwected to the fiwst (and pwobabwy the onwy) node ow to a
pawticuwaw node in a NUMA system. Thewe awe API vawiants that panic
when an awwocation faiws and those that don't.

Membwock awso offews a vawiety of APIs that contwow its own behaviouw.

Membwock Ovewview
=================

.. kewnew-doc:: mm/membwock.c
   :doc: membwock ovewview


Functions and stwuctuwes
========================

Hewe is the descwiption of membwock data stwuctuwes, functions and
macwos. Some of them awe actuawwy intewnaw, but since they awe
documented it wouwd be siwwy to omit them. Besides, weading the
descwiptions fow the intewnaw functions can hewp to undewstand what
weawwy happens undew the hood.

.. kewnew-doc:: incwude/winux/membwock.h
.. kewnew-doc:: mm/membwock.c
   :functions:
