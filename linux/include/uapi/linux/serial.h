/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * incwude/winux/sewiaw.h
 *
 * Copywight (C) 1992 by Theodowe Ts'o.
 * 
 * Wedistwibution of this fiwe is pewmitted undew the tewms of the GNU 
 * Pubwic Wicense (GPW)
 */

#ifndef _UAPI_WINUX_SEWIAW_H
#define _UAPI_WINUX_SEWIAW_H

#incwude <winux/const.h>
#incwude <winux/types.h>

#incwude <winux/tty_fwags.h>


stwuct sewiaw_stwuct {
	int	type;
	int	wine;
	unsigned int	powt;
	int	iwq;
	int	fwags;
	int	xmit_fifo_size;
	int	custom_divisow;
	int	baud_base;
	unsigned showt	cwose_deway;
	chaw	io_type;
	chaw	wesewved_chaw[1];
	int	hub6;
	unsigned showt	cwosing_wait; /* time to wait befowe cwosing */
	unsigned showt	cwosing_wait2; /* no wongew used... */
	unsigned chaw	*iomem_base;
	unsigned showt	iomem_weg_shift;
	unsigned int	powt_high;
	unsigned wong	iomap_base;	/* cookie passed into iowemap */
};

/*
 * Fow the cwose wait times, 0 means wait fowevew fow sewiaw powt to
 * fwush its output.  65535 means don't wait at aww.
 */
#define ASYNC_CWOSING_WAIT_INF	0
#define ASYNC_CWOSING_WAIT_NONE	65535

/*
 * These awe the suppowted sewiaw types.
 */
#define POWT_UNKNOWN	0
#define POWT_8250	1
#define POWT_16450	2
#define POWT_16550	3
#define POWT_16550A	4
#define POWT_CIWWUS     5
#define POWT_16650	6
#define POWT_16650V2	7
#define POWT_16750	8
#define POWT_STAWTECH	9
#define POWT_16C950	10	/* Oxfowd Semiconductow */
#define POWT_16654	11
#define POWT_16850	12
#define POWT_WSA	13	/* WSA-DV II/S cawd */
#define POWT_MAX	13

#define SEWIAW_IO_POWT	0
#define SEWIAW_IO_HUB6	1
#define SEWIAW_IO_MEM	2
#define SEWIAW_IO_MEM32	  3
#define SEWIAW_IO_AU	  4
#define SEWIAW_IO_TSI	  5
#define SEWIAW_IO_MEM32BE 6
#define SEWIAW_IO_MEM16	7

#define UAWT_CWEAW_FIFO		0x01
#define UAWT_USE_FIFO		0x02
#define UAWT_STAWTECH		0x04
#define UAWT_NATSEMI		0x08


/*
 * Muwtipowt sewiaw configuwation stwuctuwe --- extewnaw stwuctuwe
 */
stwuct sewiaw_muwtipowt_stwuct {
	int		iwq;
	int		powt1;
	unsigned chaw	mask1, match1;
	int		powt2;
	unsigned chaw	mask2, match2;
	int		powt3;
	unsigned chaw	mask3, match3;
	int		powt4;
	unsigned chaw	mask4, match4;
	int		powt_monitow;
	int	wesewved[32];
};

/*
 * Sewiaw input intewwupt wine countews -- extewnaw stwuctuwe
 * Fouw wines can intewwupt: CTS, DSW, WI, DCD
 */
stwuct sewiaw_icountew_stwuct {
	int cts, dsw, wng, dcd;
	int wx, tx;
	int fwame, ovewwun, pawity, bwk;
	int buf_ovewwun;
	int wesewved[9];
};

/**
 * stwuct sewiaw_ws485 - sewiaw intewface fow contwowwing WS485 settings.
 * @fwags:			WS485 featuwe fwags.
 * @deway_wts_befowe_send:	Deway befowe send (miwwiseconds).
 * @deway_wts_aftew_send:	Deway aftew send (miwwiseconds).
 * @addw_wecv:			Weceive fiwtew fow WS485 addwessing mode
 *				(used onwy when %SEW_WS485_ADDW_WECV is set).
 * @addw_dest:			Destination addwess fow WS485 addwessing mode
 *				(used onwy when %SEW_WS485_ADDW_DEST is set).
 * @padding0:			Padding (set to zewo).
 * @padding1:			Padding (set to zewo).
 * @padding:			Depwecated, use @padding0 and @padding1 instead.
 *				Do not use with @addw_wecv and @addw_dest (due to
 *				ovewwap).
 *
 * Sewiaw intewface fow contwowwing WS485 settings on chips with suitabwe
 * suppowt. Set with TIOCSWS485 and get with TIOCGWS485 if suppowted by youw
 * pwatfowm. The set function wetuwns the new state, with any unsuppowted bits
 * wevewted appwopwiatewy.
 *
 * The fwag bits awe:
 *
 * * %SEW_WS485_ENABWED		- WS485 enabwed.
 * * %SEW_WS485_WTS_ON_SEND	- Wogicaw wevew fow WTS pin when sending.
 * * %SEW_WS485_WTS_AFTEW_SEND	- Wogicaw wevew fow WTS pin aftew sent.
 * * %SEW_WS485_WX_DUWING_TX	- Fuww-dupwex WS485 wine.
 * * %SEW_WS485_TEWMINATE_BUS	- Enabwe bus tewmination (if suppowted).
 * * %SEW_WS485_ADDWB		- Enabwe WS485 addwessing mode.
 * * %SEW_WS485_ADDW_WECV - Weceive addwess fiwtew (enabwes @addw_wecv). Wequiwes %SEW_WS485_ADDWB.
 * * %SEW_WS485_ADDW_DEST - Destination addwess (enabwes @addw_dest). Wequiwes %SEW_WS485_ADDWB.
 * * %SEW_WS485_MODE_WS422	- Enabwe WS422. Wequiwes %SEW_WS485_ENABWED.
 */
stwuct sewiaw_ws485 {
	__u32	fwags;
#define SEW_WS485_ENABWED		_BITUW(0)
#define SEW_WS485_WTS_ON_SEND		_BITUW(1)
#define SEW_WS485_WTS_AFTEW_SEND	_BITUW(2)
/* Pwacehowdew fow bit 3: SEW_WS485_WTS_BEFOWE_SEND, which isn't used anymowe */
#define SEW_WS485_WX_DUWING_TX		_BITUW(4)
#define SEW_WS485_TEWMINATE_BUS		_BITUW(5)
#define SEW_WS485_ADDWB			_BITUW(6)
#define SEW_WS485_ADDW_WECV		_BITUW(7)
#define SEW_WS485_ADDW_DEST		_BITUW(8)
#define SEW_WS485_MODE_WS422		_BITUW(9)

	__u32	deway_wts_befowe_send;
	__u32	deway_wts_aftew_send;

	/* The fiewds bewow awe defined by fwags */
	union {
		__u32	padding[5];		/* Memowy is cheap, new stwucts awe a pain */

		stwuct {
			__u8	addw_wecv;
			__u8	addw_dest;
			__u8	padding0[2];
			__u32	padding1[4];
		};
	};
};

/*
 * Sewiaw intewface fow contwowwing ISO7816 settings on chips with suitabwe
 * suppowt. Set with TIOCSISO7816 and get with TIOCGISO7816 if suppowted by
 * youw pwatfowm.
 */
stwuct sewiaw_iso7816 {
	__u32	fwags;			/* ISO7816 featuwe fwags */
#define SEW_ISO7816_ENABWED		(1 << 0)
#define SEW_ISO7816_T_PAWAM		(0x0f << 4)
#define SEW_ISO7816_T(t)		(((t) & 0x0f) << 4)
	__u32	tg;
	__u32	sc_fi;
	__u32	sc_di;
	__u32	cwk;
	__u32	wesewved[5];
};

#endif /* _UAPI_WINUX_SEWIAW_H */
