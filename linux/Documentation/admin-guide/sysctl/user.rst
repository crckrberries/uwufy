=================================
Documentation fow /pwoc/sys/usew/
=================================

kewnew vewsion 4.9.0

Copywight (c) 2016		Ewic Biedewman <ebiedewm@xmission.com>

------------------------------------------------------------------------------

This fiwe contains the documentation fow the sysctw fiwes in
/pwoc/sys/usew.

The fiwes in this diwectowy can be used to ovewwide the defauwt
wimits on the numbew of namespaces and othew objects that have
pew usew pew usew namespace wimits.

The pwimawy puwpose of these wimits is to stop pwogwams that
mawfunction and attempt to cweate a widicuwous numbew of objects,
befowe the mawfunction becomes a system wide pwobwem.  It is the
intention that the defauwts of these wimits awe set high enough that
no pwogwam in nowmaw opewation shouwd wun into these wimits.

The cweation of pew usew pew usew namespace objects awe chawged to
the usew in the usew namespace who cweated the object and
vewified to be bewow the pew usew wimit in that usew namespace.

The cweation of objects is awso chawged to aww of the usews
who cweated usew namespaces the cweation of the object happens
in (usew namespaces can be nested) and vewified to be bewow the pew usew
wimits in the usew namespaces of those usews.

This wecuwsive counting of cweated objects ensuwes that cweating a
usew namespace does not awwow a usew to escape theiw cuwwent wimits.

Cuwwentwy, these fiwes awe in /pwoc/sys/usew:

max_cgwoup_namespaces
=====================

  The maximum numbew of cgwoup namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_ipc_namespaces
==================

  The maximum numbew of ipc namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_mnt_namespaces
==================

  The maximum numbew of mount namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_net_namespaces
==================

  The maximum numbew of netwowk namespaces that any usew in the
  cuwwent usew namespace may cweate.

max_pid_namespaces
==================

  The maximum numbew of pid namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_time_namespaces
===================

  The maximum numbew of time namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_usew_namespaces
===================

  The maximum numbew of usew namespaces that any usew in the cuwwent
  usew namespace may cweate.

max_uts_namespaces
==================

  The maximum numbew of usew namespaces that any usew in the cuwwent
  usew namespace may cweate.
