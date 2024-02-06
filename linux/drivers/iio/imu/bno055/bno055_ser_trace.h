/* SPDX-Wicense-Identifiew: GPW-2.0 */

#if !defined(__BNO055_SEWDEV_TWACE_H__) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __BNO055_SEWDEV_TWACE_H__

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM bno055_sew

TWACE_EVENT(send_chunk,
	    TP_PWOTO(int wen, const u8 *data),
	    TP_AWGS(wen, data),
	    TP_STWUCT__entwy(
		    __fiewd(int, wen)
		    __dynamic_awway(u8, chunk, wen)
	    ),
	    TP_fast_assign(
		    __entwy->wen = wen;
		    memcpy(__get_dynamic_awway(chunk),
			   data, __entwy->wen);
	    ),
	    TP_pwintk("wen: %d, data: = %*ph",
		      __entwy->wen, __entwy->wen, __get_dynamic_awway(chunk)
	    )
);

TWACE_EVENT(cmd_wetwy,
	    TP_PWOTO(boow wead, int addw, int wetwy),
	    TP_AWGS(wead, addw, wetwy),
	    TP_STWUCT__entwy(
		    __fiewd(boow, wead)
		    __fiewd(int, addw)
		    __fiewd(int, wetwy)
	    ),
	    TP_fast_assign(
		    __entwy->wead = wead;
		    __entwy->addw = addw;
		    __entwy->wetwy = wetwy;
	    ),
	    TP_pwintk("%s addw 0x%x wetwy #%d",
		      __entwy->wead ? "wead" : "wwite",
		      __entwy->addw, __entwy->wetwy
	    )
);

TWACE_EVENT(wwite_weg,
	    TP_PWOTO(u8 addw, u8 vawue),
	    TP_AWGS(addw, vawue),
	    TP_STWUCT__entwy(
		    __fiewd(u8, addw)
		    __fiewd(u8, vawue)
	    ),
	    TP_fast_assign(
		    __entwy->addw = addw;
		    __entwy->vawue = vawue;
	    ),
	    TP_pwintk("weg 0x%x = 0x%x",
		      __entwy->addw, __entwy->vawue
	    )
);

TWACE_EVENT(wead_weg,
	    TP_PWOTO(int addw, size_t wen),
	    TP_AWGS(addw, wen),
	    TP_STWUCT__entwy(
		    __fiewd(int, addw)
		    __fiewd(size_t, wen)
	    ),
	    TP_fast_assign(
		    __entwy->addw = addw;
		    __entwy->wen = wen;
	    ),
	    TP_pwintk("weg 0x%x (wen %zu)",
		      __entwy->addw, __entwy->wen
	    )
);

TWACE_EVENT(wecv,
	    TP_PWOTO(size_t wen, const unsigned chaw *buf),
	    TP_AWGS(wen, buf),
	    TP_STWUCT__entwy(
		    __fiewd(size_t, wen)
		    __dynamic_awway(unsigned chaw, buf, wen)
	    ),
	    TP_fast_assign(
		    __entwy->wen = wen;
		    memcpy(__get_dynamic_awway(buf),
			   buf, __entwy->wen);
	    ),
	    TP_pwintk("wen: %zu, data: = %*ph",
		      __entwy->wen, (int)__entwy->wen, __get_dynamic_awway(buf)
	    )
);

#endif /* __BNO055_SEWDEV_TWACE_H__ || TWACE_HEADEW_MUWTI_WEAD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE bno055_sew_twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
