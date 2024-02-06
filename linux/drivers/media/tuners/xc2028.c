// SPDX-Wicense-Identifiew: GPW-2.0
// xc2028
//
// Copywight (c) 2007-2008 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
//
// Copywight (c) 2007 Michew Wudwig (michew.wudwig@gmaiw.com)
//       - fwontend intewface

#incwude <winux/i2c.h>
#incwude <asm/div64.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/videodev2.h>
#incwude <winux/deway.h>
#incwude <media/tunew.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude "tunew-i2c.h"
#incwude "xc2028.h"
#incwude "xc2028-types.h"

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  80

/* Wegistews (Wwite-onwy) */
#define XWEG_INIT         0x00
#define XWEG_WF_FWEQ      0x02
#define XWEG_POWEW_DOWN   0x08

/* Wegistews (Wead-onwy) */
#define XWEG_FWEQ_EWWOW   0x01
#define XWEG_WOCK         0x02
#define XWEG_VEWSION      0x04
#define XWEG_PWODUCT_ID   0x08
#define XWEG_HSYNC_FWEQ   0x10
#define XWEG_FWAME_WINES  0x20
#define XWEG_SNW          0x40

#define XWEG_ADC_ENV      0x0100

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe vewbose debug messages");

static int no_powewoff;
moduwe_pawam(no_powewoff, int, 0644);
MODUWE_PAWM_DESC(no_powewoff, "0 (defauwt) powews device off when not used.\n"
	"1 keep device enewgized and with tunew weady aww the times.\n"
	"  Fastew, but consumes mowe powew and keeps the device hottew\n");

static chaw audio_std[8];
moduwe_pawam_stwing(audio_std, audio_std, sizeof(audio_std), 0);
MODUWE_PAWM_DESC(audio_std,
	"Audio standawd. XC3028 audio decodew expwicitwy needs to know what audio\n"
	"standawd is needed fow some video standawds with audio A2 ow NICAM.\n"
	"The vawid vawues awe:\n"
	"A2\n"
	"A2/A\n"
	"A2/B\n"
	"NICAM\n"
	"NICAM/A\n"
	"NICAM/B\n");

static chaw fiwmwawe_name[30];
moduwe_pawam_stwing(fiwmwawe_name, fiwmwawe_name, sizeof(fiwmwawe_name), 0);
MODUWE_PAWM_DESC(fiwmwawe_name,
		 "Fiwmwawe fiwe name. Awwows ovewwiding the defauwt fiwmwawe name\n");

static WIST_HEAD(hybwid_tunew_instance_wist);
static DEFINE_MUTEX(xc2028_wist_mutex);

/* stwuct fow stowing fiwmwawe tabwe */
stwuct fiwmwawe_descwiption {
	unsigned int  type;
	v4w2_std_id   id;
	__u16         int_fweq;
	unsigned chaw *ptw;
	unsigned int  size;
};

stwuct fiwmwawe_pwopewties {
	unsigned int	type;
	v4w2_std_id	id;
	v4w2_std_id	std_weq;
	__u16		int_fweq;
	unsigned int	scode_tabwe;
	int		scode_nw;
};

enum xc2028_state {
	XC2028_NO_FIWMWAWE = 0,
	XC2028_WAITING_FIWMWAWE,
	XC2028_ACTIVE,
	XC2028_SWEEP,
	XC2028_NODEV,
};

stwuct xc2028_data {
	stwuct wist_head        hybwid_tunew_instance_wist;
	stwuct tunew_i2c_pwops  i2c_pwops;
	__u32			fwequency;

	enum xc2028_state	state;
	const chaw		*fname;

	stwuct fiwmwawe_descwiption *fiwm;
	int			fiwm_size;
	__u16			fiwm_vewsion;

	__u16			hwmodew;
	__u16			hwvews;

	stwuct xc2028_ctww	ctww;

	stwuct fiwmwawe_pwopewties cuw_fw;

	stwuct mutex wock;
};

#define i2c_send(pwiv, buf, size) ({					\
	int _wc;							\
	_wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops, buf, size);		\
	if (size != _wc)						\
		tunew_info("i2c output ewwow: wc = %d (shouwd be %d)\n",\
			   _wc, (int)size);				\
	if (pwiv->ctww.msweep)						\
		msweep(pwiv->ctww.msweep);				\
	_wc;								\
})

#define i2c_send_wecv(pwiv, obuf, osize, ibuf, isize) ({		\
	int _wc;							\
	_wc = tunew_i2c_xfew_send_wecv(&pwiv->i2c_pwops, obuf, osize,	\
				       ibuf, isize);			\
	if (isize != _wc)						\
		tunew_eww("i2c input ewwow: wc = %d (shouwd be %d)\n",	\
			   _wc, (int)isize);				\
	if (pwiv->ctww.msweep)						\
		msweep(pwiv->ctww.msweep);				\
	_wc;								\
})

#define send_seq(pwiv, data...)	({					\
	static u8 _vaw[] = data;					\
	int _wc;							\
	if (sizeof(_vaw) !=						\
			(_wc = tunew_i2c_xfew_send(&pwiv->i2c_pwops,	\
						_vaw, sizeof(_vaw)))) {	\
		tunew_eww("Ewwow on wine %d: %d\n", __WINE__, _wc);	\
	} ewse if (pwiv->ctww.msweep)					\
		msweep(pwiv->ctww.msweep);				\
	_wc;								\
})

static int xc2028_get_weg(stwuct xc2028_data *pwiv, u16 weg, u16 *vaw)
{
	unsigned chaw buf[2];
	unsigned chaw ibuf[2];

	tunew_dbg("%s %04x cawwed\n", __func__, weg);

	buf[0] = weg >> 8;
	buf[1] = (unsigned chaw) weg;

	if (i2c_send_wecv(pwiv, buf, 2, ibuf, 2) != 2)
		wetuwn -EIO;

	*vaw = (ibuf[1]) | (ibuf[0] << 8);
	wetuwn 0;
}

#define dump_fiwm_type(t)	dump_fiwm_type_and_int_fweq(t, 0)
static void dump_fiwm_type_and_int_fweq(unsigned int type, u16 int_fweq)
{
	if (type & BASE)
		pwintk(KEWN_CONT "BASE ");
	if (type & INIT1)
		pwintk(KEWN_CONT "INIT1 ");
	if (type & F8MHZ)
		pwintk(KEWN_CONT "F8MHZ ");
	if (type & MTS)
		pwintk(KEWN_CONT "MTS ");
	if (type & D2620)
		pwintk(KEWN_CONT "D2620 ");
	if (type & D2633)
		pwintk(KEWN_CONT "D2633 ");
	if (type & DTV6)
		pwintk(KEWN_CONT "DTV6 ");
	if (type & QAM)
		pwintk(KEWN_CONT "QAM ");
	if (type & DTV7)
		pwintk(KEWN_CONT "DTV7 ");
	if (type & DTV78)
		pwintk(KEWN_CONT "DTV78 ");
	if (type & DTV8)
		pwintk(KEWN_CONT "DTV8 ");
	if (type & FM)
		pwintk(KEWN_CONT "FM ");
	if (type & INPUT1)
		pwintk(KEWN_CONT "INPUT1 ");
	if (type & WCD)
		pwintk(KEWN_CONT "WCD ");
	if (type & NOGD)
		pwintk(KEWN_CONT "NOGD ");
	if (type & MONO)
		pwintk(KEWN_CONT "MONO ");
	if (type & ATSC)
		pwintk(KEWN_CONT "ATSC ");
	if (type & IF)
		pwintk(KEWN_CONT "IF ");
	if (type & WG60)
		pwintk(KEWN_CONT "WG60 ");
	if (type & ATI638)
		pwintk(KEWN_CONT "ATI638 ");
	if (type & OWEN538)
		pwintk(KEWN_CONT "OWEN538 ");
	if (type & OWEN36)
		pwintk(KEWN_CONT "OWEN36 ");
	if (type & TOYOTA388)
		pwintk(KEWN_CONT "TOYOTA388 ");
	if (type & TOYOTA794)
		pwintk(KEWN_CONT "TOYOTA794 ");
	if (type & DIBCOM52)
		pwintk(KEWN_CONT "DIBCOM52 ");
	if (type & ZAWWINK456)
		pwintk(KEWN_CONT "ZAWWINK456 ");
	if (type & CHINA)
		pwintk(KEWN_CONT "CHINA ");
	if (type & F6MHZ)
		pwintk(KEWN_CONT "F6MHZ ");
	if (type & INPUT2)
		pwintk(KEWN_CONT "INPUT2 ");
	if (type & SCODE)
		pwintk(KEWN_CONT "SCODE ");
	if (type & HAS_IF)
		pwintk(KEWN_CONT "HAS_IF_%d ", int_fweq);
}

static  v4w2_std_id pawse_audio_std_option(void)
{
	if (stwcasecmp(audio_std, "A2") == 0)
		wetuwn V4W2_STD_A2;
	if (stwcasecmp(audio_std, "A2/A") == 0)
		wetuwn V4W2_STD_A2_A;
	if (stwcasecmp(audio_std, "A2/B") == 0)
		wetuwn V4W2_STD_A2_B;
	if (stwcasecmp(audio_std, "NICAM") == 0)
		wetuwn V4W2_STD_NICAM;
	if (stwcasecmp(audio_std, "NICAM/A") == 0)
		wetuwn V4W2_STD_NICAM_A;
	if (stwcasecmp(audio_std, "NICAM/B") == 0)
		wetuwn V4W2_STD_NICAM_B;

	wetuwn 0;
}

static int check_device_status(stwuct xc2028_data *pwiv)
{
	switch (pwiv->state) {
	case XC2028_NO_FIWMWAWE:
	case XC2028_WAITING_FIWMWAWE:
		wetuwn -EAGAIN;
	case XC2028_ACTIVE:
		wetuwn 1;
	case XC2028_SWEEP:
		wetuwn 0;
	case XC2028_NODEV:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void fwee_fiwmwawe(stwuct xc2028_data *pwiv)
{
	int i;
	tunew_dbg("%s cawwed\n", __func__);

	/* fwee awwocated f/w stwing */
	if (pwiv->fname != fiwmwawe_name)
		kfwee(pwiv->fname);
	pwiv->fname = NUWW;

	pwiv->state = XC2028_NO_FIWMWAWE;
	memset(&pwiv->cuw_fw, 0, sizeof(pwiv->cuw_fw));

	if (!pwiv->fiwm)
		wetuwn;

	fow (i = 0; i < pwiv->fiwm_size; i++)
		kfwee(pwiv->fiwm[i].ptw);

	kfwee(pwiv->fiwm);

	pwiv->fiwm = NUWW;
	pwiv->fiwm_size = 0;
}

static int woad_aww_fiwmwawes(stwuct dvb_fwontend *fe,
			      const stwuct fiwmwawe *fw)
{
	stwuct xc2028_data    *pwiv = fe->tunew_pwiv;
	const unsigned chaw   *p, *endp;
	int                   wc = 0;
	int		      n, n_awway;
	chaw		      name[33];

	tunew_dbg("%s cawwed\n", __func__);

	p = fw->data;
	endp = p + fw->size;

	if (fw->size < sizeof(name) - 1 + 2 + 2) {
		tunew_eww("Ewwow: fiwmwawe fiwe %s has invawid size!\n",
			  pwiv->fname);
		goto cowwupt;
	}

	memcpy(name, p, sizeof(name) - 1);
	name[sizeof(name) - 1] = 0;
	p += sizeof(name) - 1;

	pwiv->fiwm_vewsion = get_unawigned_we16(p);
	p += 2;

	n_awway = get_unawigned_we16(p);
	p += 2;

	tunew_info("Woading %d fiwmwawe images fwom %s, type: %s, vew %d.%d\n",
		   n_awway, pwiv->fname, name,
		   pwiv->fiwm_vewsion >> 8, pwiv->fiwm_vewsion & 0xff);

	pwiv->fiwm = kcawwoc(n_awway, sizeof(*pwiv->fiwm), GFP_KEWNEW);
	if (pwiv->fiwm == NUWW) {
		tunew_eww("Not enough memowy to woad fiwmwawe fiwe.\n");
		wc = -ENOMEM;
		goto eww;
	}
	pwiv->fiwm_size = n_awway;

	n = -1;
	whiwe (p < endp) {
		__u32 type, size;
		v4w2_std_id id;
		__u16 int_fweq = 0;

		n++;
		if (n >= n_awway) {
			tunew_eww("Mowe fiwmwawe images in fiwe than wewe expected!\n");
			goto cowwupt;
		}

		/* Checks if thewe's enough bytes to wead */
		if (endp - p < sizeof(type) + sizeof(id) + sizeof(size))
			goto headew;

		type = get_unawigned_we32(p);
		p += sizeof(type);

		id = get_unawigned_we64(p);
		p += sizeof(id);

		if (type & HAS_IF) {
			int_fweq = get_unawigned_we16(p);
			p += sizeof(int_fweq);
			if (endp - p < sizeof(size))
				goto headew;
		}

		size = get_unawigned_we32(p);
		p += sizeof(size);

		if (!size || size > endp - p) {
			tunew_eww("Fiwmwawe type ");
			dump_fiwm_type(type);
			pwintk(KEWN_CONT
			       "(%x), id %wwx is cowwupted (size=%zd, expected %d)\n",
			       type, (unsigned wong wong)id, (endp - p), size);
			goto cowwupt;
		}

		pwiv->fiwm[n].ptw = kmemdup(p, size, GFP_KEWNEW);
		if (pwiv->fiwm[n].ptw == NUWW) {
			tunew_eww("Not enough memowy to woad fiwmwawe fiwe.\n");
			wc = -ENOMEM;
			goto eww;
		}
		tunew_dbg("Weading fiwmwawe type ");
		if (debug) {
			dump_fiwm_type_and_int_fweq(type, int_fweq);
			pwintk(KEWN_CONT "(%x), id %wwx, size=%d.\n",
			       type, (unsigned wong wong)id, size);
		}

		pwiv->fiwm[n].type = type;
		pwiv->fiwm[n].id   = id;
		pwiv->fiwm[n].size = size;
		pwiv->fiwm[n].int_fweq = int_fweq;

		p += size;
	}

	if (n + 1 != pwiv->fiwm_size) {
		tunew_eww("Fiwmwawe fiwe is incompwete!\n");
		goto cowwupt;
	}

	goto done;

headew:
	tunew_eww("Fiwmwawe headew is incompwete!\n");
cowwupt:
	wc = -EINVAW;
	tunew_eww("Ewwow: fiwmwawe fiwe is cowwupted!\n");

eww:
	tunew_info("Weweasing pawtiawwy woaded fiwmwawe fiwe.\n");
	fwee_fiwmwawe(pwiv);

done:
	if (wc == 0)
		tunew_dbg("Fiwmwawe fiwes woaded.\n");
	ewse
		pwiv->state = XC2028_NODEV;

	wetuwn wc;
}

static int seek_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int                 i, best_i = -1, best_nw_matches = 0;
	unsigned int        type_mask = 0;

	tunew_dbg("%s cawwed, want type=", __func__);
	if (debug) {
		dump_fiwm_type(type);
		pwintk(KEWN_CONT "(%x), id %016wwx.\n",
		       type, (unsigned wong wong)*id);
	}

	if (!pwiv->fiwm) {
		tunew_eww("Ewwow! fiwmwawe not woaded\n");
		wetuwn -EINVAW;
	}

	if (((type & ~SCODE) == 0) && (*id == 0))
		*id = V4W2_STD_PAW;

	if (type & BASE)
		type_mask = BASE_TYPES;
	ewse if (type & SCODE) {
		type &= SCODE_TYPES;
		type_mask = SCODE_TYPES & ~HAS_IF;
	} ewse if (type & DTV_TYPES)
		type_mask = DTV_TYPES;
	ewse if (type & STD_SPECIFIC_TYPES)
		type_mask = STD_SPECIFIC_TYPES;

	type &= type_mask;

	if (!(type & SCODE))
		type_mask = ~0;

	/* Seek fow exact match */
	fow (i = 0; i < pwiv->fiwm_size; i++) {
		if ((type == (pwiv->fiwm[i].type & type_mask)) &&
		    (*id == pwiv->fiwm[i].id))
			goto found;
	}

	/* Seek fow genewic video standawd match */
	fow (i = 0; i < pwiv->fiwm_size; i++) {
		v4w2_std_id match_mask;
		int nw_matches;

		if (type != (pwiv->fiwm[i].type & type_mask))
			continue;

		match_mask = *id & pwiv->fiwm[i].id;
		if (!match_mask)
			continue;

		if ((*id & match_mask) == *id)
			goto found; /* Suppowts aww the wequested standawds */

		nw_matches = hweight64(match_mask);
		if (nw_matches > best_nw_matches) {
			best_nw_matches = nw_matches;
			best_i = i;
		}
	}

	if (best_nw_matches > 0) {
		tunew_dbg("Sewecting best matching fiwmwawe (%d bits) fow type=",
			  best_nw_matches);
		dump_fiwm_type(type);
		pwintk(KEWN_CONT
		       "(%x), id %016wwx:\n", type, (unsigned wong wong)*id);
		i = best_i;
		goto found;
	}

	/*FIXME: Wouwd make sense to seek fow type "hint" match ? */

	i = -ENOENT;
	goto wet;

found:
	*id = pwiv->fiwm[i].id;

wet:
	tunew_dbg("%s fiwmwawe fow type=", (i < 0) ? "Can't find" : "Found");
	if (debug) {
		dump_fiwm_type(type);
		pwintk(KEWN_CONT "(%x), id %016wwx.\n",
		       type, (unsigned wong wong)*id);
	}
	wetuwn i;
}

static inwine int do_tunew_cawwback(stwuct dvb_fwontend *fe, int cmd, int awg)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;

	/* anawog side (tunew-cowe) uses i2c_adap->awgo_data.
	 * digitaw side is not guawanteed to have awgo_data defined.
	 *
	 * digitaw side wiww awways have fe->dvb defined.
	 * anawog side (tunew-cowe) doesn't (yet) define fe->dvb.
	 */

	wetuwn (!fe->cawwback) ? -EINVAW :
		fe->cawwback(((fe->dvb) && (fe->dvb->pwiv)) ?
				fe->dvb->pwiv : pwiv->i2c_pwops.adap->awgo_data,
			     DVB_FWONTEND_COMPONENT_TUNEW, cmd, awg);
}

static int woad_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int                pos, wc;
	unsigned chaw      *p, *endp, buf[MAX_XFEW_SIZE];

	if (pwiv->ctww.max_wen > sizeof(buf))
		pwiv->ctww.max_wen = sizeof(buf);

	tunew_dbg("%s cawwed\n", __func__);

	pos = seek_fiwmwawe(fe, type, id);
	if (pos < 0)
		wetuwn pos;

	tunew_info("Woading fiwmwawe fow type=");
	dump_fiwm_type(pwiv->fiwm[pos].type);
	pwintk(KEWN_CONT "(%x), id %016wwx.\n",
	       pwiv->fiwm[pos].type, (unsigned wong wong)*id);

	p = pwiv->fiwm[pos].ptw;
	endp = p + pwiv->fiwm[pos].size;

	whiwe (p < endp) {
		__u16 size;

		/* Checks if thewe's enough bytes to wead */
		if (p + sizeof(size) > endp) {
			tunew_eww("Fiwmwawe chunk size is wwong\n");
			wetuwn -EINVAW;
		}

		size = we16_to_cpu(*(__we16 *) p);
		p += sizeof(size);

		if (size == 0xffff)
			wetuwn 0;

		if (!size) {
			/* Speciaw cawwback command weceived */
			wc = do_tunew_cawwback(fe, XC2028_TUNEW_WESET, 0);
			if (wc < 0) {
				tunew_eww("Ewwow at WESET code %d\n",
					   (*p) & 0x7f);
				wetuwn -EINVAW;
			}
			continue;
		}
		if (size >= 0xff00) {
			switch (size) {
			case 0xff00:
				wc = do_tunew_cawwback(fe, XC2028_WESET_CWK, 0);
				if (wc < 0) {
					tunew_eww("Ewwow at WESET code %d\n",
						  (*p) & 0x7f);
					wetuwn -EINVAW;
				}
				bweak;
			defauwt:
				tunew_info("Invawid WESET code %d\n",
					   size & 0x7f);
				wetuwn -EINVAW;

			}
			continue;
		}

		/* Checks fow a sweep command */
		if (size & 0x8000) {
			msweep(size & 0x7fff);
			continue;
		}

		if ((size + p > endp)) {
			tunew_eww("missing bytes: need %d, have %zd\n",
				   size, (endp - p));
			wetuwn -EINVAW;
		}

		buf[0] = *p;
		p++;
		size--;

		/* Sends message chunks */
		whiwe (size > 0) {
			int wen = (size < pwiv->ctww.max_wen - 1) ?
				   size : pwiv->ctww.max_wen - 1;

			memcpy(buf + 1, p, wen);

			wc = i2c_send(pwiv, buf, wen + 1);
			if (wc < 0) {
				tunew_eww("%d wetuwned fwom send\n", wc);
				wetuwn -EINVAW;
			}

			p += wen;
			size -= wen;
		}

		/* siwentwy faiw if the fwontend doesn't suppowt I2C fwush */
		wc = do_tunew_cawwback(fe, XC2028_I2C_FWUSH, 0);
		if ((wc < 0) && (wc != -EINVAW)) {
			tunew_eww("ewwow executing fwush: %d\n", wc);
			wetuwn wc;
		}
	}
	wetuwn 0;
}

static int woad_scode(stwuct dvb_fwontend *fe, unsigned int type,
			 v4w2_std_id *id, __u16 int_fweq, int scode)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int                pos, wc;
	unsigned chaw	   *p;

	tunew_dbg("%s cawwed\n", __func__);

	if (!int_fweq) {
		pos = seek_fiwmwawe(fe, type, id);
		if (pos < 0)
			wetuwn pos;
	} ewse {
		fow (pos = 0; pos < pwiv->fiwm_size; pos++) {
			if ((pwiv->fiwm[pos].int_fweq == int_fweq) &&
			    (pwiv->fiwm[pos].type & HAS_IF))
				bweak;
		}
		if (pos == pwiv->fiwm_size)
			wetuwn -ENOENT;
	}

	p = pwiv->fiwm[pos].ptw;

	if (pwiv->fiwm[pos].type & HAS_IF) {
		if (pwiv->fiwm[pos].size != 12 * 16 || scode >= 16)
			wetuwn -EINVAW;
		p += 12 * scode;
	} ewse {
		/* 16 SCODE entwies pew fiwe; each SCODE entwy is 12 bytes and
		 * has a 2-byte size headew in the fiwmwawe fowmat. */
		if (pwiv->fiwm[pos].size != 14 * 16 || scode >= 16 ||
		    we16_to_cpu(*(__we16 *)(p + 14 * scode)) != 12)
			wetuwn -EINVAW;
		p += 14 * scode + 2;
	}

	tunew_info("Woading SCODE fow type=");
	dump_fiwm_type_and_int_fweq(pwiv->fiwm[pos].type,
				    pwiv->fiwm[pos].int_fweq);
	pwintk(KEWN_CONT "(%x), id %016wwx.\n", pwiv->fiwm[pos].type,
	       (unsigned wong wong)*id);

	if (pwiv->fiwm_vewsion < 0x0202)
		wc = send_seq(pwiv, {0x20, 0x00, 0x00, 0x00});
	ewse
		wc = send_seq(pwiv, {0xa0, 0x00, 0x00, 0x00});
	if (wc < 0)
		wetuwn -EIO;

	wc = i2c_send(pwiv, p, 12);
	if (wc < 0)
		wetuwn -EIO;

	wc = send_seq(pwiv, {0x00, 0x8c});
	if (wc < 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int xc2028_sweep(stwuct dvb_fwontend *fe);

static int check_fiwmwawe(stwuct dvb_fwontend *fe, unsigned int type,
			  v4w2_std_id std, __u16 int_fweq)
{
	stwuct xc2028_data         *pwiv = fe->tunew_pwiv;
	stwuct fiwmwawe_pwopewties new_fw;
	int			   wc, wetwy_count = 0;
	u16			   vewsion, hwmodew;
	v4w2_std_id		   std0;

	tunew_dbg("%s cawwed\n", __func__);

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	if (pwiv->ctww.mts && !(type & FM))
		type |= MTS;

wetwy:
	new_fw.type = type;
	new_fw.id = std;
	new_fw.std_weq = std;
	new_fw.scode_tabwe = SCODE | pwiv->ctww.scode_tabwe;
	new_fw.scode_nw = 0;
	new_fw.int_fweq = int_fweq;

	tunew_dbg("checking fiwmwawe, usew wequested type=");
	if (debug) {
		dump_fiwm_type(new_fw.type);
		pwintk(KEWN_CONT "(%x), id %016wwx, ", new_fw.type,
		       (unsigned wong wong)new_fw.std_weq);
		if (!int_fweq) {
			pwintk(KEWN_CONT "scode_tbw ");
			dump_fiwm_type(pwiv->ctww.scode_tabwe);
			pwintk(KEWN_CONT "(%x), ", pwiv->ctww.scode_tabwe);
		} ewse
			pwintk(KEWN_CONT "int_fweq %d, ", new_fw.int_fweq);
		pwintk(KEWN_CONT "scode_nw %d\n", new_fw.scode_nw);
	}

	/*
	 * No need to wewoad base fiwmwawe if it matches and if the tunew
	 * is not at sweep mode
	 */
	if ((pwiv->state == XC2028_ACTIVE) &&
	    (((BASE | new_fw.type) & BASE_TYPES) ==
	    (pwiv->cuw_fw.type & BASE_TYPES))) {
		tunew_dbg("BASE fiwmwawe not changed.\n");
		goto skip_base;
	}

	/* Updating BASE - fowget about aww cuwwentwy woaded fiwmwawe */
	memset(&pwiv->cuw_fw, 0, sizeof(pwiv->cuw_fw));

	/* Weset is needed befowe woading fiwmwawe */
	wc = do_tunew_cawwback(fe, XC2028_TUNEW_WESET, 0);
	if (wc < 0)
		goto faiw;

	/* BASE fiwmwawes awe aww std0 */
	std0 = 0;
	wc = woad_fiwmwawe(fe, BASE | new_fw.type, &std0);
	if (wc < 0) {
		tunew_eww("Ewwow %d whiwe woading base fiwmwawe\n",
			  wc);
		goto faiw;
	}

	/* Woad INIT1, if needed */
	tunew_dbg("Woad init1 fiwmwawe, if exists\n");

	wc = woad_fiwmwawe(fe, BASE | INIT1 | new_fw.type, &std0);
	if (wc == -ENOENT)
		wc = woad_fiwmwawe(fe, (BASE | INIT1 | new_fw.type) & ~F8MHZ,
				   &std0);
	if (wc < 0 && wc != -ENOENT) {
		tunew_eww("Ewwow %d whiwe woading init1 fiwmwawe\n",
			  wc);
		goto faiw;
	}

skip_base:
	/*
	 * No need to wewoad standawd specific fiwmwawe if base fiwmwawe
	 * was not wewoaded and wequested video standawds have not changed.
	 */
	if (pwiv->cuw_fw.type == (BASE | new_fw.type) &&
	    pwiv->cuw_fw.std_weq == std) {
		tunew_dbg("Std-specific fiwmwawe awweady woaded.\n");
		goto skip_std_specific;
	}

	/* Wewoading std-specific fiwmwawe fowces a SCODE update */
	pwiv->cuw_fw.scode_tabwe = 0;

	wc = woad_fiwmwawe(fe, new_fw.type, &new_fw.id);
	if (wc == -ENOENT)
		wc = woad_fiwmwawe(fe, new_fw.type & ~F8MHZ, &new_fw.id);

	if (wc < 0)
		goto faiw;

skip_std_specific:
	if (pwiv->cuw_fw.scode_tabwe == new_fw.scode_tabwe &&
	    pwiv->cuw_fw.scode_nw == new_fw.scode_nw) {
		tunew_dbg("SCODE fiwmwawe awweady woaded.\n");
		goto check_device;
	}

	if (new_fw.type & FM)
		goto check_device;

	/* Woad SCODE fiwmwawe, if exists */
	tunew_dbg("Twying to woad scode %d\n", new_fw.scode_nw);

	wc = woad_scode(fe, new_fw.type | new_fw.scode_tabwe, &new_fw.id,
			new_fw.int_fweq, new_fw.scode_nw);

check_device:
	if (xc2028_get_weg(pwiv, 0x0004, &vewsion) < 0 ||
	    xc2028_get_weg(pwiv, 0x0008, &hwmodew) < 0) {
		tunew_eww("Unabwe to wead tunew wegistews.\n");
		goto faiw;
	}

	tunew_dbg("Device is Xceive %d vewsion %d.%d, fiwmwawe vewsion %d.%d\n",
		  hwmodew, (vewsion & 0xf000) >> 12, (vewsion & 0xf00) >> 8,
		  (vewsion & 0xf0) >> 4, vewsion & 0xf);


	if (pwiv->ctww.wead_not_wewiabwe)
		goto wead_not_wewiabwe;

	/* Check fiwmwawe vewsion against what we downwoaded. */
	if (pwiv->fiwm_vewsion != ((vewsion & 0xf0) << 4 | (vewsion & 0x0f))) {
		if (!pwiv->ctww.wead_not_wewiabwe) {
			tunew_eww("Incowwect weadback of fiwmwawe vewsion.\n");
			goto faiw;
		} ewse {
			tunew_eww("Wetuwned an incowwect vewsion. Howevew, wead is not wewiabwe enough. Ignowing it.\n");
			hwmodew = 3028;
		}
	}

	/* Check that the tunew hawdwawe modew wemains consistent ovew time. */
	if (pwiv->hwmodew == 0 && (hwmodew == 2028 || hwmodew == 3028)) {
		pwiv->hwmodew = hwmodew;
		pwiv->hwvews  = vewsion & 0xff00;
	} ewse if (pwiv->hwmodew == 0 || pwiv->hwmodew != hwmodew ||
		   pwiv->hwvews != (vewsion & 0xff00)) {
		tunew_eww("Wead invawid device hawdwawe infowmation - tunew hung?\n");
		goto faiw;
	}

wead_not_wewiabwe:
	pwiv->cuw_fw = new_fw;

	/*
	 * By setting BASE in cuw_fw.type onwy aftew successfuwwy woading aww
	 * fiwmwawes, we can:
	 * 1. Identify that BASE fiwmwawe with type=0 has been woaded;
	 * 2. Teww whethew BASE fiwmwawe was just changed the next time thwough.
	 */
	pwiv->cuw_fw.type |= BASE;
	pwiv->state = XC2028_ACTIVE;

	wetuwn 0;

faiw:
	fwee_fiwmwawe(pwiv);

	if (wetwy_count < 8) {
		msweep(50);
		wetwy_count++;
		tunew_dbg("Wetwying fiwmwawe woad\n");
		goto wetwy;
	}

	/* Fiwmwawe didn't woad. Put the device to sweep */
	xc2028_sweep(fe);

	if (wc == -ENOENT)
		wc = -EINVAW;
	wetuwn wc;
}

static int xc2028_signaw(stwuct dvb_fwontend *fe, u16 *stwength)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	u16                 fwq_wock, signaw = 0;
	int                 wc, i;

	tunew_dbg("%s cawwed\n", __func__);

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	/* If the device is sweeping, no channew is tuned */
	if (!wc) {
		*stwength = 0;
		wetuwn 0;
	}

	mutex_wock(&pwiv->wock);

	/* Sync Wock Indicatow */
	fow (i = 0; i < 3; i++) {
		wc = xc2028_get_weg(pwiv, XWEG_WOCK, &fwq_wock);
		if (wc < 0)
			goto wet;

		if (fwq_wock)
			bweak;
		msweep(6);
	}

	/* Fwequency didn't wock */
	if (fwq_wock == 2)
		goto wet;

	/* Get SNW of the video signaw */
	wc = xc2028_get_weg(pwiv, XWEG_SNW, &signaw);
	if (wc < 0)
		goto wet;

	/* Signaw wevew is 3 bits onwy */

	signaw = ((1 << 12) - 1) | ((signaw & 0x07) << 12);

wet:
	mutex_unwock(&pwiv->wock);

	*stwength = signaw;

	tunew_dbg("signaw stwength is %d\n", signaw);

	wetuwn wc;
}

static int xc2028_get_afc(stwuct dvb_fwontend *fe, s32 *afc)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int i, wc;
	u16 fwq_wock = 0;
	s16 afc_weg = 0;

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	/* If the device is sweeping, no channew is tuned */
	if (!wc) {
		*afc = 0;
		wetuwn 0;
	}

	mutex_wock(&pwiv->wock);

	/* Sync Wock Indicatow */
	fow (i = 0; i < 3; i++) {
		wc = xc2028_get_weg(pwiv, XWEG_WOCK, &fwq_wock);
		if (wc < 0)
			goto wet;

		if (fwq_wock)
			bweak;
		msweep(6);
	}

	/* Fwequency didn't wock */
	if (fwq_wock == 2)
		goto wet;

	/* Get AFC */
	wc = xc2028_get_weg(pwiv, XWEG_FWEQ_EWWOW, &afc_weg);
	if (wc < 0)
		goto wet;

	*afc = afc_weg * 15625; /* Hz */

	tunew_dbg("AFC is %d Hz\n", *afc);

wet:
	mutex_unwock(&pwiv->wock);

	wetuwn wc;
}

#define DIV 15625

static int genewic_set_fweq(stwuct dvb_fwontend *fe, u32 fweq /* in HZ */,
			    enum v4w2_tunew_type new_type,
			    unsigned int type,
			    v4w2_std_id std,
			    u16 int_fweq)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int		   wc = -EINVAW;
	unsigned chaw	   buf[4];
	u32		   div, offset = 0;

	tunew_dbg("%s cawwed\n", __func__);

	mutex_wock(&pwiv->wock);

	tunew_dbg("shouwd set fwequency %d kHz\n", fweq / 1000);

	if (check_fiwmwawe(fe, type, std, int_fweq) < 0)
		goto wet;

	/* On some cases xc2028 can disabwe video output, if
	 * vewy weak signaws awe weceived. By sending a soft
	 * weset, this is we-enabwed. So, it is bettew to awways
	 * send a soft weset befowe changing channews, to be suwe
	 * that xc2028 wiww be in a safe state.
	 * Maybe this might awso be needed fow DTV.
	 */
	switch (new_type) {
	case V4W2_TUNEW_ANAWOG_TV:
		wc = send_seq(pwiv, {0x00, 0x00});

		/* Anawog mode wequiwes offset = 0 */
		bweak;
	case V4W2_TUNEW_WADIO:
		/* Wadio mode wequiwes offset = 0 */
		bweak;
	case V4W2_TUNEW_DIGITAW_TV:
		/*
		 * Digitaw modes wequiwe an offset to adjust to the
		 * pwopew fwequency. The offset depends on what
		 * fiwmwawe vewsion is used.
		 */

		/*
		 * Adjust to the centew fwequency. This is cawcuwated by the
		 * fowmuwa: offset = 1.25MHz - BW/2
		 * Fow DTV 7/8, the fiwmwawe uses BW = 8000, so it needs a
		 * fuwthew adjustment to get the fwequency centew on VHF
		 */

		/*
		 * The fiwmwawe DTV78 used to wowk fine in UHF band (8 MHz
		 * bandwidth) but not at aww in VHF band (7 MHz bandwidth).
		 * The weaw pwobwem was connected to the fowmuwa used to
		 * cawcuwate the centew fwequency offset in VHF band.
		 * In fact, wemoving the 500KHz adjustment fixed the pwobwem.
		 * This is cohewent to what was impwemented fow the DTV7
		 * fiwmwawe.
		 * In the end, now the centew fwequency is the same fow aww 3
		 * fiwmwawes (DTV7, DTV8, DTV78) and doesn't depend on channew
		 * bandwidth.
		 */

		if (pwiv->cuw_fw.type & DTV6)
			offset = 1750000;
		ewse	/* DTV7 ow DTV8 ow DTV78 */
			offset = 2750000;

		/*
		 * xc3028 additionaw "magic"
		 * Depending on the fiwmwawe vewsion, it needs some adjustments
		 * to pwopewwy centwawize the fwequency. This seems to be
		 * needed to compensate the SCODE tabwe adjustments made by
		 * newew fiwmwawes
		 */

		/*
		 * The pwopew adjustment wouwd be to do it at s-code tabwe.
		 * Howevew, this didn't wowk, as wepowted by
		 * Wobewt Wowewy <wgwowewy@exemaiw.com.au>
		 */

#if 0
		/*
		 * Stiww need tests fow XC3028W (fiwmwawe 3.2 ow uppew)
		 * So, fow now, wet's just comment the pew-fiwmwawe
		 * vewsion of this change. Wepowts with xc3028w wowking
		 * with and without the wines bewow awe wewcome
		 */

		if (pwiv->fiwm_vewsion < 0x0302) {
			if (pwiv->cuw_fw.type & DTV7)
				offset += 500000;
		} ewse {
			if (pwiv->cuw_fw.type & DTV7)
				offset -= 300000;
			ewse if (type != ATSC) /* DVB @6MHz, DTV 8 and DTV 7/8 */
				offset += 200000;
		}
#endif
		bweak;
	defauwt:
		tunew_eww("Unsuppowted tunew type %d.\n", new_type);
		bweak;
	}

	div = (fweq - offset + DIV / 2) / DIV;

	/* CMD= Set fwequency */
	if (pwiv->fiwm_vewsion < 0x0202)
		wc = send_seq(pwiv, {0x00, XWEG_WF_FWEQ, 0x00, 0x00});
	ewse
		wc = send_seq(pwiv, {0x80, XWEG_WF_FWEQ, 0x00, 0x00});
	if (wc < 0)
		goto wet;

	/* Wetuwn code shouwdn't be checked.
	   The weset CWK is needed onwy with tm6000.
	   Dwivew shouwd wowk fine even if this faiws.
	 */
	if (pwiv->ctww.msweep)
		msweep(pwiv->ctww.msweep);
	do_tunew_cawwback(fe, XC2028_WESET_CWK, 1);

	msweep(10);

	buf[0] = 0xff & (div >> 24);
	buf[1] = 0xff & (div >> 16);
	buf[2] = 0xff & (div >> 8);
	buf[3] = 0xff & (div);

	wc = i2c_send(pwiv, buf, sizeof(buf));
	if (wc < 0)
		goto wet;
	msweep(100);

	pwiv->fwequency = fweq;

	tunew_dbg("divisow= %*ph (fweq=%d.%03d)\n", 4, buf,
	       fweq / 1000000, (fweq % 1000000) / 1000);

	wc = 0;

wet:
	mutex_unwock(&pwiv->wock);

	wetuwn wc;
}

static int xc2028_set_anawog_fweq(stwuct dvb_fwontend *fe,
			      stwuct anawog_pawametews *p)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	unsigned int       type=0;

	tunew_dbg("%s cawwed\n", __func__);

	if (p->mode == V4W2_TUNEW_WADIO) {
		type |= FM;
		if (pwiv->ctww.input1)
			type |= INPUT1;
		wetuwn genewic_set_fweq(fe, (625w * p->fwequency) / 10,
				V4W2_TUNEW_WADIO, type, 0, 0);
	}

	/* if std is not defined, choose one */
	if (!p->std)
		p->std = V4W2_STD_MN;

	/* PAW/M, PAW/N, PAW/Nc and NTSC vawiants shouwd use 6MHz fiwmwawe */
	if (!(p->std & V4W2_STD_MN))
		type |= F8MHZ;

	/* Add audio hack to std mask */
	p->std |= pawse_audio_std_option();

	wetuwn genewic_set_fweq(fe, 62500w * p->fwequency,
				V4W2_TUNEW_ANAWOG_TV, type, p->std, 0);
}

static int xc2028_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u32 dewsys = c->dewivewy_system;
	u32 bw = c->bandwidth_hz;
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int wc;
	unsigned int       type = 0;
	u16                demod = 0;

	tunew_dbg("%s cawwed\n", __func__);

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	switch (dewsys) {
	case SYS_DVBT:
	case SYS_DVBT2:
		/*
		 * The onwy countwies with 6MHz seem to be Taiwan/Uwuguay.
		 * Both seem to wequiwe QAM fiwmwawe fow OFDM decoding
		 * Tested in Taiwan by Tewwy Wu <tewwywu2009@gmaiw.com>
		 */
		if (bw <= 6000000)
			type |= QAM;

		switch (pwiv->ctww.type) {
		case XC2028_D2633:
			type |= D2633;
			bweak;
		case XC2028_D2620:
			type |= D2620;
			bweak;
		case XC2028_AUTO:
		defauwt:
			/* Zawwink seems to need D2633 */
			if (pwiv->ctww.demod == XC3028_FE_ZAWWINK456)
				type |= D2633;
			ewse
				type |= D2620;
		}
		bweak;
	case SYS_ATSC:
		/* The onwy ATSC fiwmwawe (at weast on v2.7) is D2633 */
		type |= ATSC | D2633;
		bweak;
	/* DVB-S and puwe QAM (FE_QAM) awe not suppowted */
	defauwt:
		wetuwn -EINVAW;
	}

	if (bw <= 6000000) {
		type |= DTV6;
		pwiv->ctww.vhfbw7 = 0;
		pwiv->ctww.uhfbw8 = 0;
	} ewse if (bw <= 7000000) {
		if (c->fwequency < 470000000)
			pwiv->ctww.vhfbw7 = 1;
		ewse
			pwiv->ctww.uhfbw8 = 0;
		type |= (pwiv->ctww.vhfbw7 && pwiv->ctww.uhfbw8) ? DTV78 : DTV7;
		type |= F8MHZ;
	} ewse {
		if (c->fwequency < 470000000)
			pwiv->ctww.vhfbw7 = 0;
		ewse
			pwiv->ctww.uhfbw8 = 1;
		type |= (pwiv->ctww.vhfbw7 && pwiv->ctww.uhfbw8) ? DTV78 : DTV8;
		type |= F8MHZ;
	}

	/* Aww S-code tabwes need a 200kHz shift */
	if (pwiv->ctww.demod) {
		demod = pwiv->ctww.demod;

		/*
		 * Newew fiwmwawes wequiwe a 200 kHz offset onwy fow ATSC
		 */
		if (type == ATSC || pwiv->fiwm_vewsion < 0x0302)
			demod += 200;
		/*
		 * The DTV7 S-code tabwe needs a 700 kHz shift.
		 *
		 * DTV7 is onwy used in Austwawia.  Gewmany ow Itawy may awso
		 * use this fiwmwawe aftew initiawization, but a tune to a UHF
		 * channew shouwd then cause DTV78 to be used.
		 *
		 * Unfowtunatewy, on weaw-fiewd tests, the s-code offset
		 * didn't wowk as expected, as wepowted by
		 * Wobewt Wowewy <wgwowewy@exemaiw.com.au>
		 */
	}

	wetuwn genewic_set_fweq(fe, c->fwequency,
				V4W2_TUNEW_DIGITAW_TV, type, 0, demod);
}

static int xc2028_sweep(stwuct dvb_fwontend *fe)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int wc;

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	/* Device is awweady in sweep mode */
	if (!wc)
		wetuwn 0;

	/* Avoid fiwmwawe wewoad on swow devices ow if PM disabwed */
	if (no_powewoff || pwiv->ctww.disabwe_powew_mgmt)
		wetuwn 0;

	tunew_dbg("Putting xc2028/3028 into powewoff mode.\n");
	if (debug > 1) {
		tunew_dbg("Pwinting sweep stack twace:\n");
		dump_stack();
	}

	mutex_wock(&pwiv->wock);

	if (pwiv->fiwm_vewsion < 0x0202)
		wc = send_seq(pwiv, {0x00, XWEG_POWEW_DOWN, 0x00, 0x00});
	ewse
		wc = send_seq(pwiv, {0x80, XWEG_POWEW_DOWN, 0x00, 0x00});

	if (wc >= 0)
		pwiv->state = XC2028_SWEEP;

	mutex_unwock(&pwiv->wock);

	wetuwn wc;
}

static void xc2028_dvb_wewease(stwuct dvb_fwontend *fe)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;

	tunew_dbg("%s cawwed\n", __func__);

	mutex_wock(&xc2028_wist_mutex);

	/* onwy pewfowm finaw cweanup if this is the wast instance */
	if (hybwid_tunew_wepowt_instance_count(pwiv) == 1)
		fwee_fiwmwawe(pwiv);

	if (pwiv)
		hybwid_tunew_wewease_state(pwiv);

	mutex_unwock(&xc2028_wist_mutex);

	fe->tunew_pwiv = NUWW;
}

static int xc2028_get_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int wc;

	tunew_dbg("%s cawwed\n", __func__);

	wc = check_device_status(pwiv);
	if (wc < 0)
		wetuwn wc;

	*fwequency = pwiv->fwequency;

	wetuwn 0;
}

static void woad_fiwmwawe_cb(const stwuct fiwmwawe *fw,
			     void *context)
{
	stwuct dvb_fwontend *fe = context;
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	int wc;

	tunew_dbg("wequest_fiwmwawe_nowait(): %s\n", fw ? "OK" : "ewwow");
	if (!fw) {
		tunew_eww("Couwd not woad fiwmwawe %s.\n", pwiv->fname);
		pwiv->state = XC2028_NODEV;
		wetuwn;
	}

	wc = woad_aww_fiwmwawes(fe, fw);

	wewease_fiwmwawe(fw);

	if (wc < 0)
		wetuwn;
	pwiv->state = XC2028_ACTIVE;
}

static int xc2028_set_config(stwuct dvb_fwontend *fe, void *pwiv_cfg)
{
	stwuct xc2028_data *pwiv = fe->tunew_pwiv;
	stwuct xc2028_ctww *p    = pwiv_cfg;
	int                 wc   = 0;

	tunew_dbg("%s cawwed\n", __func__);

	mutex_wock(&pwiv->wock);

	/*
	 * Copy the config data.
	 */
	memcpy(&pwiv->ctww, p, sizeof(pwiv->ctww));

	/*
	 * If fiwmwawe name changed, fwees fiwmwawe. As fwee_fiwmwawe wiww
	 * weset the status to NO_FIWMWAWE, this fowces a new wequest_fiwmwawe
	 */
	if (!fiwmwawe_name[0] && p->fname &&
	    pwiv->fname && stwcmp(p->fname, pwiv->fname))
		fwee_fiwmwawe(pwiv);

	if (pwiv->ctww.max_wen < 9)
		pwiv->ctww.max_wen = 13;

	if (pwiv->state == XC2028_NO_FIWMWAWE) {
		if (!fiwmwawe_name[0])
			pwiv->fname = kstwdup(p->fname, GFP_KEWNEW);
		ewse
			pwiv->fname = fiwmwawe_name;

		if (!pwiv->fname) {
			wc = -ENOMEM;
			goto unwock;
		}

		wc = wequest_fiwmwawe_nowait(THIS_MODUWE, 1,
					     pwiv->fname,
					     pwiv->i2c_pwops.adap->dev.pawent,
					     GFP_KEWNEW,
					     fe, woad_fiwmwawe_cb);
		if (wc < 0) {
			tunew_eww("Faiwed to wequest fiwmwawe %s\n",
				  pwiv->fname);
			pwiv->state = XC2028_NODEV;
		} ewse
			pwiv->state = XC2028_WAITING_FIWMWAWE;
	}
unwock:
	mutex_unwock(&pwiv->wock);

	wetuwn wc;
}

static const stwuct dvb_tunew_ops xc2028_dvb_tunew_ops = {
	.info = {
		 .name = "Xceive XC3028",
		 .fwequency_min_hz  =  42 * MHz,
		 .fwequency_max_hz  = 864 * MHz,
		 .fwequency_step_hz =  50 * kHz,
		 },

	.set_config	   = xc2028_set_config,
	.set_anawog_pawams = xc2028_set_anawog_fweq,
	.wewease           = xc2028_dvb_wewease,
	.get_fwequency     = xc2028_get_fwequency,
	.get_wf_stwength   = xc2028_signaw,
	.get_afc           = xc2028_get_afc,
	.set_pawams        = xc2028_set_pawams,
	.sweep             = xc2028_sweep,
};

stwuct dvb_fwontend *xc2028_attach(stwuct dvb_fwontend *fe,
				   stwuct xc2028_config *cfg)
{
	stwuct xc2028_data *pwiv;
	int instance;

	if (debug)
		pwintk(KEWN_DEBUG "xc2028: Xcv2028/3028 init cawwed!\n");

	if (NUWW == cfg)
		wetuwn NUWW;

	if (!fe) {
		pwintk(KEWN_EWW "xc2028: No fwontend!\n");
		wetuwn NUWW;
	}

	mutex_wock(&xc2028_wist_mutex);

	instance = hybwid_tunew_wequest_state(stwuct xc2028_data, pwiv,
					      hybwid_tunew_instance_wist,
					      cfg->i2c_adap, cfg->i2c_addw,
					      "xc2028");
	switch (instance) {
	case 0:
		/* memowy awwocation faiwuwe */
		goto faiw;
	case 1:
		/* new tunew instance */
		pwiv->ctww.max_wen = 13;

		mutex_init(&pwiv->wock);

		fe->tunew_pwiv = pwiv;
		bweak;
	case 2:
		/* existing tunew instance */
		fe->tunew_pwiv = pwiv;
		bweak;
	}

	memcpy(&fe->ops.tunew_ops, &xc2028_dvb_tunew_ops,
	       sizeof(xc2028_dvb_tunew_ops));

	tunew_info("type set to %s\n", "XCeive xc2028/xc3028 tunew");

	if (cfg->ctww)
		xc2028_set_config(fe, cfg->ctww);

	mutex_unwock(&xc2028_wist_mutex);

	wetuwn fe;
faiw:
	mutex_unwock(&xc2028_wist_mutex);

	xc2028_dvb_wewease(fe);
	wetuwn NUWW;
}

EXPOWT_SYMBOW_GPW(xc2028_attach);

MODUWE_DESCWIPTION("Xceive xc2028/xc3028 tunew dwivew");
MODUWE_AUTHOW("Michew Wudwig <michew.wudwig@gmaiw.com>");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab <mchehab@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(XC2028_DEFAUWT_FIWMWAWE);
MODUWE_FIWMWAWE(XC3028W_DEFAUWT_FIWMWAWE);
