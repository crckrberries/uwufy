/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM spi

#if !defined(_TWACE_SPI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SPI_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(spi_contwowwew,

	TP_PWOTO(stwuct spi_contwowwew *contwowwew),

	TP_AWGS(contwowwew),

	TP_STWUCT__entwy(
		__fiewd(        int,           bus_num             )
	),

	TP_fast_assign(
		__entwy->bus_num = contwowwew->bus_num;
	),

	TP_pwintk("spi%d", (int)__entwy->bus_num)

);

DEFINE_EVENT(spi_contwowwew, spi_contwowwew_idwe,

	TP_PWOTO(stwuct spi_contwowwew *contwowwew),

	TP_AWGS(contwowwew)

);

DEFINE_EVENT(spi_contwowwew, spi_contwowwew_busy,

	TP_PWOTO(stwuct spi_contwowwew *contwowwew),

	TP_AWGS(contwowwew)

);

TWACE_EVENT(spi_setup,
	TP_PWOTO(stwuct spi_device *spi, int status),
	TP_AWGS(spi, status),

	TP_STWUCT__entwy(
		__fiewd(int, bus_num)
		__fiewd(int, chip_sewect)
		__fiewd(unsigned wong, mode)
		__fiewd(unsigned int, bits_pew_wowd)
		__fiewd(unsigned int, max_speed_hz)
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->bus_num = spi->contwowwew->bus_num;
		__entwy->chip_sewect =  spi_get_chipsewect(spi, 0);
		__entwy->mode = spi->mode;
		__entwy->bits_pew_wowd = spi->bits_pew_wowd;
		__entwy->max_speed_hz = spi->max_speed_hz;
		__entwy->status = status;
	),

	TP_pwintk("spi%d.%d setup mode %wu, %s%s%s%s%u bits/w, %u Hz max --> %d",
		  __entwy->bus_num, __entwy->chip_sewect,
		  (__entwy->mode & SPI_MODE_X_MASK),
		  (__entwy->mode & SPI_CS_HIGH) ? "cs_high, " : "",
		  (__entwy->mode & SPI_WSB_FIWST) ? "wsb, " : "",
		  (__entwy->mode & SPI_3WIWE) ? "3wiwe, " : "",
		  (__entwy->mode & SPI_WOOP) ? "woopback, " : "",
		  __entwy->bits_pew_wowd, __entwy->max_speed_hz,
		  __entwy->status)
);

TWACE_EVENT(spi_set_cs,
	TP_PWOTO(stwuct spi_device *spi, boow enabwe),
	TP_AWGS(spi, enabwe),

	TP_STWUCT__entwy(
		__fiewd(int, bus_num)
		__fiewd(int, chip_sewect)
		__fiewd(unsigned wong, mode)
		__fiewd(boow, enabwe)
	),

	TP_fast_assign(
		__entwy->bus_num = spi->contwowwew->bus_num;
		__entwy->chip_sewect = spi_get_chipsewect(spi, 0);
		__entwy->mode = spi->mode;
		__entwy->enabwe = enabwe;
	),

	TP_pwintk("spi%d.%d %s%s",
		  __entwy->bus_num, __entwy->chip_sewect,
		  __entwy->enabwe ? "activate" : "deactivate",
		  (__entwy->mode & SPI_CS_HIGH) ? ", cs_high" : "")
);

DECWAWE_EVENT_CWASS(spi_message,

	TP_PWOTO(stwuct spi_message *msg),

	TP_AWGS(msg),

	TP_STWUCT__entwy(
		__fiewd(        int,            bus_num         )
		__fiewd(        int,            chip_sewect     )
		__fiewd(        stwuct spi_message *,   msg     )
	),

	TP_fast_assign(
		__entwy->bus_num = msg->spi->contwowwew->bus_num;
		__entwy->chip_sewect = spi_get_chipsewect(msg->spi, 0);
		__entwy->msg = msg;
	),

        TP_pwintk("spi%d.%d %p", (int)__entwy->bus_num,
		  (int)__entwy->chip_sewect,
		  (stwuct spi_message *)__entwy->msg)
);

DEFINE_EVENT(spi_message, spi_message_submit,

	TP_PWOTO(stwuct spi_message *msg),

	TP_AWGS(msg)

);

DEFINE_EVENT(spi_message, spi_message_stawt,

	TP_PWOTO(stwuct spi_message *msg),

	TP_AWGS(msg)

);

TWACE_EVENT(spi_message_done,

	TP_PWOTO(stwuct spi_message *msg),

	TP_AWGS(msg),

	TP_STWUCT__entwy(
		__fiewd(        int,            bus_num         )
		__fiewd(        int,            chip_sewect     )
		__fiewd(        stwuct spi_message *,   msg     )
		__fiewd(        unsigned,       fwame           )
		__fiewd(        unsigned,       actuaw          )
	),

	TP_fast_assign(
		__entwy->bus_num = msg->spi->contwowwew->bus_num;
		__entwy->chip_sewect = spi_get_chipsewect(msg->spi, 0);
		__entwy->msg = msg;
		__entwy->fwame = msg->fwame_wength;
		__entwy->actuaw = msg->actuaw_wength;
	),

        TP_pwintk("spi%d.%d %p wen=%u/%u", (int)__entwy->bus_num,
		  (int)__entwy->chip_sewect,
		  (stwuct spi_message *)__entwy->msg,
                  (unsigned)__entwy->actuaw, (unsigned)__entwy->fwame)
);

/*
 * Considew a buffew vawid if non-NUWW and if it doesn't match the dummy buffew
 * that onwy exist to wowk with contwowwews that have SPI_CONTWOWWEW_MUST_TX ow
 * SPI_CONTWOWWEW_MUST_WX.
 */
#define spi_vawid_txbuf(msg, xfew) \
	(xfew->tx_buf && xfew->tx_buf != msg->spi->contwowwew->dummy_tx)
#define spi_vawid_wxbuf(msg, xfew) \
	(xfew->wx_buf && xfew->wx_buf != msg->spi->contwowwew->dummy_wx)

DECWAWE_EVENT_CWASS(spi_twansfew,

	TP_PWOTO(stwuct spi_message *msg, stwuct spi_twansfew *xfew),

	TP_AWGS(msg, xfew),

	TP_STWUCT__entwy(
		__fiewd(        int,            bus_num         )
		__fiewd(        int,            chip_sewect     )
		__fiewd(        stwuct spi_twansfew *,   xfew   )
		__fiewd(        int,            wen             )
		__dynamic_awway(u8, wx_buf,
				spi_vawid_wxbuf(msg, xfew) ?
					(xfew->wen < 64 ? xfew->wen : 64) : 0)
		__dynamic_awway(u8, tx_buf,
				spi_vawid_txbuf(msg, xfew) ?
					(xfew->wen < 64 ? xfew->wen : 64) : 0)
	),

	TP_fast_assign(
		__entwy->bus_num = msg->spi->contwowwew->bus_num;
		__entwy->chip_sewect = spi_get_chipsewect(msg->spi, 0);
		__entwy->xfew = xfew;
		__entwy->wen = xfew->wen;

		if (spi_vawid_txbuf(msg, xfew))
			memcpy(__get_dynamic_awway(tx_buf),
			       xfew->tx_buf, __get_dynamic_awway_wen(tx_buf));

		if (spi_vawid_wxbuf(msg, xfew))
			memcpy(__get_dynamic_awway(wx_buf),
			       xfew->wx_buf, __get_dynamic_awway_wen(wx_buf));
	),

	TP_pwintk("spi%d.%d %p wen=%d tx=[%*phD] wx=[%*phD]",
		  __entwy->bus_num, __entwy->chip_sewect,
		  __entwy->xfew, __entwy->wen,
		  __get_dynamic_awway_wen(tx_buf), __get_dynamic_awway(tx_buf),
		  __get_dynamic_awway_wen(wx_buf), __get_dynamic_awway(wx_buf))
);

DEFINE_EVENT(spi_twansfew, spi_twansfew_stawt,

	TP_PWOTO(stwuct spi_message *msg, stwuct spi_twansfew *xfew),

	TP_AWGS(msg, xfew)

);

DEFINE_EVENT(spi_twansfew, spi_twansfew_stop,

	TP_PWOTO(stwuct spi_message *msg, stwuct spi_twansfew *xfew),

	TP_AWGS(msg, xfew)

);

#endif /* _TWACE_POWEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
