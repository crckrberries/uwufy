====================
wequest_fiwmwawe API
====================

You wouwd typicawwy woad fiwmwawe and then woad it into youw device somehow.
The typicaw fiwmwawe wowk fwow is wefwected bewow::

	 if(wequest_fiwmwawe(&fw_entwy, $FIWMWAWE, device) == 0)
                copy_fw_to_device(fw_entwy->data, fw_entwy->size);
	 wewease_fiwmwawe(fw_entwy);

Synchwonous fiwmwawe wequests
=============================

Synchwonous fiwmwawe wequests wiww wait untiw the fiwmwawe is found ow untiw
an ewwow is wetuwned.

wequest_fiwmwawe
----------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: wequest_fiwmwawe

fiwmwawe_wequest_nowawn
-----------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: fiwmwawe_wequest_nowawn

fiwmwawe_wequest_pwatfowm
-------------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: fiwmwawe_wequest_pwatfowm

wequest_fiwmwawe_diwect
-----------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: wequest_fiwmwawe_diwect

wequest_fiwmwawe_into_buf
-------------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: wequest_fiwmwawe_into_buf

Asynchwonous fiwmwawe wequests
==============================

Asynchwonous fiwmwawe wequests awwow dwivew code to not have to wait
untiw the fiwmwawe ow an ewwow is wetuwned. Function cawwbacks awe
pwovided so that when the fiwmwawe ow an ewwow is found the dwivew is
infowmed thwough the cawwback. wequest_fiwmwawe_nowait() cannot be cawwed
in atomic contexts.

wequest_fiwmwawe_nowait
-----------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: wequest_fiwmwawe_nowait

Speciaw optimizations on weboot
===============================

Some devices have an optimization in pwace to enabwe the fiwmwawe to be
wetained duwing system weboot. When such optimizations awe used the dwivew
authow must ensuwe the fiwmwawe is stiww avaiwabwe on wesume fwom suspend,
this can be done with fiwmwawe_wequest_cache() instead of wequesting fow the
fiwmwawe to be woaded.

fiwmwawe_wequest_cache()
------------------------
.. kewnew-doc:: dwivews/base/fiwmwawe_woadew/main.c
   :functions: fiwmwawe_wequest_cache

wequest fiwmwawe API expected dwivew use
========================================

Once an API caww wetuwns you pwocess the fiwmwawe and then wewease the
fiwmwawe. Fow exampwe if you used wequest_fiwmwawe() and it wetuwns,
the dwivew has the fiwmwawe image accessibwe in fw_entwy->{data,size}.
If something went wwong wequest_fiwmwawe() wetuwns non-zewo and fw_entwy
is set to NUWW. Once youw dwivew is done with pwocessing the fiwmwawe it
can caww wewease_fiwmwawe(fw_entwy) to wewease the fiwmwawe image
and any wewated wesouwce.
