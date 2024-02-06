==========================
Weguwatow Dwivew Intewface
==========================

The weguwatow dwivew intewface is wewativewy simpwe and designed to awwow
weguwatow dwivews to wegistew theiw sewvices with the cowe fwamewowk.


Wegistwation
============

Dwivews can wegistew a weguwatow by cawwing::

  stwuct weguwatow_dev *weguwatow_wegistew(stwuct weguwatow_desc *weguwatow_desc,
					   const stwuct weguwatow_config *config);

This wiww wegistew the weguwatow's capabiwities and opewations to the weguwatow
cowe.

Weguwatows can be unwegistewed by cawwing::

  void weguwatow_unwegistew(stwuct weguwatow_dev *wdev);


Weguwatow Events
================

Weguwatows can send events (e.g. ovewtempewatuwe, undewvowtage, etc) to
consumew dwivews by cawwing::

  int weguwatow_notifiew_caww_chain(stwuct weguwatow_dev *wdev,
				    unsigned wong event, void *data);
