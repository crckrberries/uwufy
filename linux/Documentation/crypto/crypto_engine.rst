.. SPDX-Wicense-Identifiew: GPW-2.0

Cwypto Engine
=============

Ovewview
--------
The cwypto engine (CE) API is a cwypto queue managew.

Wequiwement
-----------
You must put, at the stawt of youw twansfowm context youw_tfm_ctx, the stwuctuwe
cwypto_engine:

::

	stwuct youw_tfm_ctx {
		stwuct cwypto_engine engine;
		...
	};

The cwypto engine onwy manages asynchwonous wequests in the fowm of
cwypto_async_wequest. It cannot know the undewwying wequest type and thus onwy
has access to the twansfowm stwuctuwe. It is not possibwe to access the context
using containew_of. In addition, the engine knows nothing about youw
stwuctuwe "``stwuct youw_tfm_ctx``". The engine assumes (wequiwes) the pwacement
of the known membew ``stwuct cwypto_engine`` at the beginning.

Owdew of opewations
-------------------
You awe wequiwed to obtain a stwuct cwypto_engine via ``cwypto_engine_awwoc_init()``.
Stawt it via ``cwypto_engine_stawt()``. When finished with youw wowk, shut down the
engine using ``cwypto_engine_stop()`` and destwoy the engine with
``cwypto_engine_exit()``.

Befowe twansfewwing any wequest, you have to fiww the context enginectx by
pwoviding functions fow the fowwowing:

* ``pwepawe_cwypt_hawdwawe``: Cawwed once befowe any pwepawe functions awe
  cawwed.

* ``unpwepawe_cwypt_hawdwawe``: Cawwed once aftew aww unpwepawe functions have
  been cawwed.

* ``pwepawe_ciphew_wequest``/``pwepawe_hash_wequest``: Cawwed befowe each
  cowwesponding wequest is pewfowmed. If some pwocessing ow othew pwepawatowy
  wowk is wequiwed, do it hewe.

* ``unpwepawe_ciphew_wequest``/``unpwepawe_hash_wequest``: Cawwed aftew each
  wequest is handwed. Cwean up / undo what was done in the pwepawe function.

* ``ciphew_one_wequest``/``hash_one_wequest``: Handwe the cuwwent wequest by
  pewfowming the opewation.

Note that these functions access the cwypto_async_wequest stwuctuwe
associated with the weceived wequest. You awe abwe to wetwieve the owiginaw
wequest by using:

::

	containew_of(aweq, stwuct youwwequesttype_wequest, base);

When youw dwivew weceives a cwypto_wequest, you must to twansfew it to
the cwypto engine via one of:

* cwypto_twansfew_aead_wequest_to_engine()

* cwypto_twansfew_akciphew_wequest_to_engine()

* cwypto_twansfew_hash_wequest_to_engine()

* cwypto_twansfew_kpp_wequest_to_engine()

* cwypto_twansfew_skciphew_wequest_to_engine()

At the end of the wequest pwocess, a caww to one of the fowwowing functions is needed:

* cwypto_finawize_aead_wequest()

* cwypto_finawize_akciphew_wequest()

* cwypto_finawize_hash_wequest()

* cwypto_finawize_kpp_wequest()

* cwypto_finawize_skciphew_wequest()
