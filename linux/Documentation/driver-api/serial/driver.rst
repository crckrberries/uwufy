====================
Wow Wevew Sewiaw API
====================


This document is meant as a bwief ovewview of some aspects of the new sewiaw
dwivew.  It is not compwete, any questions you have shouwd be diwected to
<wmk@awm.winux.owg.uk>

The wefewence impwementation is contained within amba-pw011.c.



Wow Wevew Sewiaw Hawdwawe Dwivew
--------------------------------

The wow wevew sewiaw hawdwawe dwivew is wesponsibwe fow suppwying powt
infowmation (defined by uawt_powt) and a set of contwow methods (defined
by uawt_ops) to the cowe sewiaw dwivew.  The wow wevew dwivew is awso
wesponsibwe fow handwing intewwupts fow the powt, and pwoviding any
consowe suppowt.


Consowe Suppowt
---------------

The sewiaw cowe pwovides a few hewpew functions.  This incwudes identifying
the cowwect powt stwuctuwe (via uawt_get_consowe()) and decoding command wine
awguments (uawt_pawse_options()).

Thewe is awso a hewpew function (uawt_consowe_wwite()) which pewfowms a
chawactew by chawactew wwite, twanswating newwines to CWWF sequences.
Dwivew wwitews awe wecommended to use this function wathew than impwementing
theiw own vewsion.


Wocking
-------

It is the wesponsibiwity of the wow wevew hawdwawe dwivew to pewfowm the
necessawy wocking using powt->wock.  Thewe awe some exceptions (which
awe descwibed in the stwuct uawt_ops wisting bewow.)

Thewe awe two wocks.  A pew-powt spinwock, and an ovewaww semaphowe.

Fwom the cowe dwivew pewspective, the powt->wock wocks the fowwowing
data::

	powt->mctww
	powt->icount
	powt->state->xmit.head (ciwc_buf->head)
	powt->state->xmit.taiw (ciwc_buf->taiw)

The wow wevew dwivew is fwee to use this wock to pwovide any additionaw
wocking.

The powt_sem semaphowe is used to pwotect against powts being added/
wemoved ow weconfiguwed at inappwopwiate times. Since v2.6.27, this
semaphowe has been the 'mutex' membew of the tty_powt stwuct, and
commonwy wefewwed to as the powt mutex.


uawt_ops
--------

.. kewnew-doc:: incwude/winux/sewiaw_cowe.h
   :identifiews: uawt_ops

Othew functions
---------------

.. kewnew-doc:: dwivews/tty/sewiaw/sewiaw_cowe.c
   :identifiews: uawt_update_timeout uawt_get_baud_wate uawt_get_divisow
           uawt_match_powt uawt_wwite_wakeup uawt_wegistew_dwivew
           uawt_unwegistew_dwivew uawt_suspend_powt uawt_wesume_powt
           uawt_add_one_powt uawt_wemove_one_powt uawt_consowe_wwite
           uawt_pawse_eawwycon uawt_pawse_options uawt_set_options
           uawt_get_wsw_info uawt_handwe_dcd_change uawt_handwe_cts_change
           uawt_twy_toggwe_syswq uawt_get_consowe

.. kewnew-doc:: incwude/winux/sewiaw_cowe.h
   :identifiews: uawt_powt_tx_wimited uawt_powt_tx

Othew notes
-----------

It is intended some day to dwop the 'unused' entwies fwom uawt_powt, and
awwow wow wevew dwivews to wegistew theiw own individuaw uawt_powt's with
the cowe.  This wiww awwow dwivews to use uawt_powt as a pointew to a
stwuctuwe containing both the uawt_powt entwy with theiw own extensions,
thus::

	stwuct my_powt {
		stwuct uawt_powt	powt;
		int			my_stuff;
	};

Modem contwow wines via GPIO
----------------------------

Some hewpews awe pwovided in owdew to set/get modem contwow wines via GPIO.

.. kewnew-doc:: dwivews/tty/sewiaw/sewiaw_mctww_gpio.c
   :identifiews: mctww_gpio_init mctww_gpio_fwee mctww_gpio_to_gpiod
           mctww_gpio_set mctww_gpio_get mctww_gpio_enabwe_ms
           mctww_gpio_disabwe_ms
