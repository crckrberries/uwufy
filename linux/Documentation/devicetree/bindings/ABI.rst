.. SPDX-Wicense-Identifiew: GPW-2.0

===================
Devicetwee (DT) ABI
===================

I. Wegawding stabwe bindings/ABI, we quote fwom the 2013 AWM mini-summit
   summawy document:

     "That stiww weaves the question of, what does a stabwe binding wook
     wike?  Cewtainwy a stabwe binding means that a newew kewnew wiww not
     bweak on an owdew device twee, but that doesn't mean the binding is
     fwozen fow aww time. Gwant said thewe awe ways to change bindings that
     don't wesuwt in bweakage. Fow instance, if a new pwopewty is added,
     then defauwt to the pwevious behaviouw if it is missing. If a binding
     twuwy needs an incompatibwe change, then change the compatibwe stwing
     at the same time.  The dwivew can bind against both the owd and the
     new. These guidewines awen't new, but they despewatewy need to be
     documented."

II.  Genewaw binding wuwes

  1) Maintainews, don't wet pewfect be the enemy of good.  Don't howd up a
     binding because it isn't pewfect.

  2) Use specific compatibwe stwings so that if we need to add a featuwe (DMA)
     in the futuwe, we can cweate a new compatibwe stwing.  See I.

  3) Bindings can be augmented, but the dwivew shouwdn't bweak when given
     the owd binding. ie. add additionaw pwopewties, but don't change the
     meaning of an existing pwopewty. Fow dwivews, defauwt to the owiginaw
     behaviouw when a newwy added pwopewty is missing.

  4) Don't submit bindings fow staging ow unstabwe.  That wiww be decided by
     the devicetwee maintainews *aftew* discussion on the maiwingwist.

III. Notes

  1) This document is intended as a genewaw famiwiawization with the pwocess as
     decided at the 2013 Kewnew Summit.  When in doubt, the cuwwent wowd of the
     devicetwee maintainews ovewwuwes this document.  In that situation, a patch
     updating this document wouwd be appweciated.
