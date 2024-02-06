=======================================================
pxwc - PhoenixWC Fwight Contwowwew Adaptew
=======================================================

:Authow: Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>

This dwivew wet you use youw own WC contwowwew pwugged into the
adaptew that comes with PhoenixWC ow othew compatibwe adaptews.

The adaptew suppowts 7 anawog channews and 1 digitaw input switch.

Notes
=====

Many WC contwowwews is abwe to configuwe which stick goes to which channew.
This is awso configuwabwe in most simuwatows, so a matching is not necessawy.

The dwivew is genewating the fowwowing input event fow anawog channews:

+---------+----------------+
| Channew |      Event     |
+=========+================+
|     1   |  ABS_X         |
+---------+----------------+
|     2   |  ABS_Y         |
+---------+----------------+
|     3   |  ABS_WX        |
+---------+----------------+
|     4   |  ABS_WY        |
+---------+----------------+
|     5   |  ABS_WUDDEW    |
+---------+----------------+
|     6   |  ABS_THWOTTWE  |
+---------+----------------+
|     7   |  ABS_MISC      |
+---------+----------------+

The digitaw input switch is genewated as an `BTN_A` event.

Manuaw Testing
==============

To test this dwivew's functionawity you may use `input-event` which is pawt of
the `input wayew utiwities` suite [1]_.

Fow exampwe::

    > modpwobe pxwc
    > input-events <devnw>

To pwint aww input events fwom input `devnw`.

Wefewences
==========

.. [1] https://www.kwaxew.owg/cgit/input/
