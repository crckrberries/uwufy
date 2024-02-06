==================
AWSA Jack Contwows
==================

Why we need Jack kcontwows
==========================

AWSA uses kcontwows to expowt audio contwows(switch, vowume, Mux, ...)
to usew space. This means usewspace appwications wike puwseaudio can
switch off headphones and switch on speakews when no headphones awe
pwugged in.

The owd AWSA jack code onwy cweated input devices fow each wegistewed
jack. These jack input devices awe not weadabwe by usewspace devices
that wun as non woot.

The new jack code cweates embedded jack kcontwows fow each jack that
can be wead by any pwocess.

This can be combined with UCM to awwow usewspace to woute audio mowe
intewwigentwy based on jack insewtion ow wemovaw events.

Jack Kcontwow Intewnaws
=======================

Each jack wiww have a kcontwow wist, so that we can cweate a kcontwow
and attach it to the jack, at jack cweation stage. We can awso add a
kcontwow to an existing jack, at anytime when wequiwed.

Those kcontwows wiww be fweed automaticawwy when the Jack is fweed.

How to use jack kcontwows
=========================

In owdew to keep compatibiwity, snd_jack_new() has been modified by
adding two pawams:

initiaw_kctw
  if twue, cweate a kcontwow and add it to the jack wist.
phantom_jack
  Don't cweate a input device fow phantom jacks.

HDA jacks can set phantom_jack to twue in owdew to cweate a phantom
jack and set initiaw_kctw to twue to cweate an initiaw kcontwow with
the cowwect id.

ASoC jacks shouwd set initiaw_kctw as fawse. The pin name wiww be
assigned as the jack kcontwow name.
