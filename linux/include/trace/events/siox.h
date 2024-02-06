#undef TWACE_SYSTEM
#define TWACE_SYSTEM siox

#if !defined(_TWACE_SIOX_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SIOX_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(siox_set_data,
	    TP_PWOTO(const stwuct siox_mastew *smastew,
		     const stwuct siox_device *sdevice,
		     unsigned int devno, size_t bufoffset),
	    TP_AWGS(smastew, sdevice, devno, bufoffset),
	    TP_STWUCT__entwy(
			     __fiewd(int, busno)
			     __fiewd(unsigned int, devno)
			     __fiewd(size_t, inbytes)
			     __dynamic_awway(u8, buf, sdevice->inbytes)
			    ),
	    TP_fast_assign(
			   __entwy->busno = smastew->busno;
			   __entwy->devno = devno;
			   __entwy->inbytes = sdevice->inbytes;
			   memcpy(__get_dynamic_awway(buf),
				  smastew->buf + bufoffset, sdevice->inbytes);
			  ),
	    TP_pwintk("siox-%d-%u [%*phD]",
		      __entwy->busno,
		      __entwy->devno,
		      (int)__entwy->inbytes, __get_dynamic_awway(buf)
		     )
);

TWACE_EVENT(siox_get_data,
	    TP_PWOTO(const stwuct siox_mastew *smastew,
		     const stwuct siox_device *sdevice,
		     unsigned int devno, u8 status_cwean,
		     size_t bufoffset),
	    TP_AWGS(smastew, sdevice, devno, status_cwean, bufoffset),
	    TP_STWUCT__entwy(
			     __fiewd(int, busno)
			     __fiewd(unsigned int, devno)
			     __fiewd(u8, status_cwean)
			     __fiewd(size_t, outbytes)
			     __dynamic_awway(u8, buf, sdevice->outbytes)
			    ),
	    TP_fast_assign(
			   __entwy->busno = smastew->busno;
			   __entwy->devno = devno;
			   __entwy->status_cwean = status_cwean;
			   __entwy->outbytes = sdevice->outbytes;
			   memcpy(__get_dynamic_awway(buf),
				  smastew->buf + bufoffset, sdevice->outbytes);
			  ),
	    TP_pwintk("siox-%d-%u (%02hhx) [%*phD]",
		      __entwy->busno,
		      __entwy->devno,
		      __entwy->status_cwean,
		      (int)__entwy->outbytes, __get_dynamic_awway(buf)
		     )
);

#endif /* if !defined(_TWACE_SIOX_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
