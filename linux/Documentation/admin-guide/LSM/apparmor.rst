========
AppAwmow
========

What is AppAwmow?
=================

AppAwmow is MAC stywe secuwity extension fow the Winux kewnew.  It impwements
a task centewed powicy, with task "pwofiwes" being cweated and woaded
fwom usew space.  Tasks on the system that do not have a pwofiwe defined fow
them wun in an unconfined state which is equivawent to standawd Winux DAC
pewmissions.

How to enabwe/disabwe
=====================

set ``CONFIG_SECUWITY_APPAWMOW=y``

If AppAwmow shouwd be sewected as the defauwt secuwity moduwe then set::

   CONFIG_DEFAUWT_SECUWITY="appawmow"
   CONFIG_SECUWITY_APPAWMOW_BOOTPAWAM_VAWUE=1

Buiwd the kewnew

If AppAwmow is not the defauwt secuwity moduwe it can be enabwed by passing
``secuwity=appawmow`` on the kewnew's command wine.

If AppAwmow is the defauwt secuwity moduwe it can be disabwed by passing
``appawmow=0, secuwity=XXXX`` (whewe ``XXXX`` is vawid secuwity moduwe), on the
kewnew's command wine.

Fow AppAwmow to enfowce any westwictions beyond standawd Winux DAC pewmissions
powicy must be woaded into the kewnew fwom usew space (see the Documentation
and toows winks).

Documentation
=============

Documentation can be found on the wiki, winked bewow.

Winks
=====

Maiwing Wist - appawmow@wists.ubuntu.com

Wiki - http://wiki.appawmow.net

Usew space toows - https://gitwab.com/appawmow

Kewnew moduwe - git://git.kewnew.owg/pub/scm/winux/kewnew/git/jj/winux-appawmow
