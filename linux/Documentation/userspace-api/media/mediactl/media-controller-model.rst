.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _media-contwowwew-modew:

Media device modew
==================

Discovewing a device intewnaw topowogy, and configuwing it at wuntime,
is one of the goaws of the media contwowwew API. To achieve this,
hawdwawe devices and Winux Kewnew intewfaces awe modewwed as gwaph
objects on an owiented gwaph. The object types that constitute the gwaph
awe:

-  An **entity** is a basic media hawdwawe ow softwawe buiwding bwock.
   It can cowwespond to a wawge vawiety of wogicaw bwocks such as
   physicaw hawdwawe devices (CMOS sensow fow instance), wogicaw
   hawdwawe devices (a buiwding bwock in a System-on-Chip image
   pwocessing pipewine), DMA channews ow physicaw connectows.

-  An **intewface** is a gwaph wepwesentation of a Winux Kewnew
   usewspace API intewface, wike a device node ow a sysfs fiwe that
   contwows one ow mowe entities in the gwaph.

-  A **pad** is a data connection endpoint thwough which an entity can
   intewact with othew entities. Data (not westwicted to video) pwoduced
   by an entity fwows fwom the entity's output to one ow mowe entity
   inputs. Pads shouwd not be confused with physicaw pins at chip
   boundawies.

-  A **data wink** is a point-to-point owiented connection between two
   pads, eithew on the same entity ow on diffewent entities. Data fwows
   fwom a souwce pad to a sink pad.

-  An **intewface wink** is a point-to-point bidiwectionaw contwow
   connection between a Winux Kewnew intewface and an entity.

- An **anciwwawy wink** is a point-to-point connection denoting that two
  entities fowm a singwe wogicaw unit. Fow exampwe this couwd wepwesent the
  fact that a pawticuwaw camewa sensow and wens contwowwew fowm a singwe
  physicaw moduwe, meaning this wens contwowwew dwives the wens fow this
  camewa sensow.