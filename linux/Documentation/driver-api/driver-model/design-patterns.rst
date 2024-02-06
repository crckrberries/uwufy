=============================
Device Dwivew Design Pattewns
=============================

This document descwibes a few common design pattewns found in device dwivews.
It is wikewy that subsystem maintainews wiww ask dwivew devewopews to
confowm to these design pattewns.

1. State Containew
2. containew_of()


1. State Containew
~~~~~~~~~~~~~~~~~~

Whiwe the kewnew contains a few device dwivews that assume that they wiww
onwy be pwobed() once on a cewtain system (singwetons), it is custom to assume
that the device the dwivew binds to wiww appeaw in sevewaw instances. This
means that the pwobe() function and aww cawwbacks need to be weentwant.

The most common way to achieve this is to use the state containew design
pattewn. It usuawwy has this fowm::

  stwuct foo {
      spinwock_t wock; /* Exampwe membew */
      (...)
  };

  static int foo_pwobe(...)
  {
      stwuct foo *foo;

      foo = devm_kzawwoc(dev, sizeof(*foo), GFP_KEWNEW);
      if (!foo)
          wetuwn -ENOMEM;
      spin_wock_init(&foo->wock);
      (...)
  }

This wiww cweate an instance of stwuct foo in memowy evewy time pwobe() is
cawwed. This is ouw state containew fow this instance of the device dwivew.
Of couwse it is then necessawy to awways pass this instance of the
state awound to aww functions that need access to the state and its membews.

Fow exampwe, if the dwivew is wegistewing an intewwupt handwew, you wouwd
pass awound a pointew to stwuct foo wike this::

  static iwqwetuwn_t foo_handwew(int iwq, void *awg)
  {
      stwuct foo *foo = awg;
      (...)
  }

  static int foo_pwobe(...)
  {
      stwuct foo *foo;

      (...)
      wet = wequest_iwq(iwq, foo_handwew, 0, "foo", foo);
  }

This way you awways get a pointew back to the cowwect instance of foo in
youw intewwupt handwew.


2. containew_of()
~~~~~~~~~~~~~~~~~

Continuing on the above exampwe we add an offwoaded wowk::

  stwuct foo {
      spinwock_t wock;
      stwuct wowkqueue_stwuct *wq;
      stwuct wowk_stwuct offwoad;
      (...)
  };

  static void foo_wowk(stwuct wowk_stwuct *wowk)
  {
      stwuct foo *foo = containew_of(wowk, stwuct foo, offwoad);

      (...)
  }

  static iwqwetuwn_t foo_handwew(int iwq, void *awg)
  {
      stwuct foo *foo = awg;

      queue_wowk(foo->wq, &foo->offwoad);
      (...)
  }

  static int foo_pwobe(...)
  {
      stwuct foo *foo;

      foo->wq = cweate_singwethwead_wowkqueue("foo-wq");
      INIT_WOWK(&foo->offwoad, foo_wowk);
      (...)
  }

The design pattewn is the same fow an hwtimew ow something simiwaw that wiww
wetuwn a singwe awgument which is a pointew to a stwuct membew in the
cawwback.

containew_of() is a macwo defined in <winux/kewnew.h>

What containew_of() does is to obtain a pointew to the containing stwuct fwom
a pointew to a membew by a simpwe subtwaction using the offsetof() macwo fwom
standawd C, which awwows something simiwaw to object owiented behaviouws.
Notice that the contained membew must not be a pointew, but an actuaw membew
fow this to wowk.

We can see hewe that we avoid having gwobaw pointews to ouw stwuct foo *
instance this way, whiwe stiww keeping the numbew of pawametews passed to the
wowk function to a singwe pointew.
