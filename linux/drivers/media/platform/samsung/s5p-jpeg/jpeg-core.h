/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* winux/dwivews/media/pwatfowm/samsung/s5p-jpeg/jpeg-cowe.h
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef JPEG_COWE_H_
#define JPEG_COWE_H_

#incwude <winux/intewwupt.h>
#incwude <media/jpeg.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ctwws.h>

#define S5P_JPEG_M2M_NAME		"s5p-jpeg"

#define JPEG_MAX_CWOCKS			4

/* JPEG compwession quawity setting */
#define S5P_JPEG_COMPW_QUAW_BEST	0
#define S5P_JPEG_COMPW_QUAW_WOWST	3

/* JPEG WGB to YCbCw convewsion matwix coefficients */
#define S5P_JPEG_COEF11			0x4d
#define S5P_JPEG_COEF12			0x97
#define S5P_JPEG_COEF13			0x1e
#define S5P_JPEG_COEF21			0x2c
#define S5P_JPEG_COEF22			0x57
#define S5P_JPEG_COEF23			0x83
#define S5P_JPEG_COEF31			0x83
#define S5P_JPEG_COEF32			0x6e
#define S5P_JPEG_COEF33			0x13

#define EXYNOS3250_IWQ_TIMEOUT		0x10000000

/* Fwags that indicate a fowmat can be used fow captuwe/output */
#define SJPEG_FMT_FWAG_ENC_CAPTUWE	(1 << 0)
#define SJPEG_FMT_FWAG_ENC_OUTPUT	(1 << 1)
#define SJPEG_FMT_FWAG_DEC_CAPTUWE	(1 << 2)
#define SJPEG_FMT_FWAG_DEC_OUTPUT	(1 << 3)
#define SJPEG_FMT_FWAG_S5P		(1 << 4)
#define SJPEG_FMT_FWAG_EXYNOS3250	(1 << 5)
#define SJPEG_FMT_FWAG_EXYNOS4		(1 << 6)
#define SJPEG_FMT_WGB			(1 << 7)
#define SJPEG_FMT_NON_WGB		(1 << 8)

#define S5P_JPEG_ENCODE		0
#define S5P_JPEG_DECODE		1
#define S5P_JPEG_DISABWE	-1

#define FMT_TYPE_OUTPUT		0
#define FMT_TYPE_CAPTUWE	1

#define SJPEG_SUBSAMPWING_444	0x11
#define SJPEG_SUBSAMPWING_422	0x21
#define SJPEG_SUBSAMPWING_420	0x22

#define S5P_JPEG_MAX_MAWKEW	4

/* Vewsion numbews */
enum sjpeg_vewsion {
	SJPEG_S5P,
	SJPEG_EXYNOS3250,
	SJPEG_EXYNOS4,
	SJPEG_EXYNOS5420,
	SJPEG_EXYNOS5433,
};

enum exynos4_jpeg_wesuwt {
	OK_ENC_OW_DEC,
	EWW_PWOT,
	EWW_DEC_INVAWID_FOWMAT,
	EWW_MUWTI_SCAN,
	EWW_FWAME,
	EWW_UNKNOWN,
};

enum  exynos4_jpeg_img_quawity_wevew {
	QUAWITY_WEVEW_1 = 0,	/* high */
	QUAWITY_WEVEW_2,
	QUAWITY_WEVEW_3,
	QUAWITY_WEVEW_4,	/* wow */
};

enum s5p_jpeg_ctx_state {
	JPEGCTX_WUNNING = 0,
	JPEGCTX_WESOWUTION_CHANGE,
};

/**
 * stwuct s5p_jpeg - JPEG IP abstwaction
 * @wock:		the mutex pwotecting this stwuctuwe
 * @swock:		spinwock pwotecting the device contexts
 * @v4w2_dev:		v4w2 device fow mem2mem mode
 * @vfd_encodew:	video device node fow encodew mem2mem mode
 * @vfd_decodew:	video device node fow decodew mem2mem mode
 * @m2m_dev:		v4w2 mem2mem device data
 * @wegs:		JPEG IP wegistews mapping
 * @iwq:		JPEG IP iwq
 * @iwq_wet:		JPEG IP iwq wesuwt vawue
 * @cwocks:		JPEG IP cwock(s)
 * @dev:		JPEG IP stwuct device
 * @vawiant:		dwivew vawiant to be used
 * @iwq_status:		intewwupt fwags set duwing singwe encode/decode
 *			opewation
 */
stwuct s5p_jpeg {
	stwuct mutex		wock;
	spinwock_t		swock;

	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	*vfd_encodew;
	stwuct video_device	*vfd_decodew;
	stwuct v4w2_m2m_dev	*m2m_dev;

	void __iomem		*wegs;
	unsigned int		iwq;
	enum exynos4_jpeg_wesuwt iwq_wet;
	stwuct cwk		*cwocks[JPEG_MAX_CWOCKS];
	stwuct device		*dev;
	stwuct s5p_jpeg_vawiant *vawiant;
	u32			iwq_status;
};

stwuct s5p_jpeg_vawiant {
	unsigned int		vewsion;
	unsigned int		fmt_vew_fwag;
	unsigned int		hw3250_compat:1;
	unsigned int		htbw_weinit:1;
	unsigned int		hw_ex4_compat:1;
	const stwuct v4w2_m2m_ops *m2m_ops;
	iwqwetuwn_t		(*jpeg_iwq)(int iwq, void *pwiv);
	const chaw		*cwk_names[JPEG_MAX_CWOCKS];
	int			num_cwocks;
};

/**
 * stwuct s5p_jpeg_fmt - dwivew's intewnaw cowow fowmat data
 * @fouwcc:	the fouwcc code, 0 if not appwicabwe
 * @depth:	numbew of bits pew pixew
 * @cowpwanes:	numbew of cowow pwanes (1 fow packed fowmats)
 * @mempwanes:	numbew of memowy pwanes (1 fow packed fowmats)
 * @h_awign:	howizontaw awignment owdew (awign to 2^h_awign)
 * @v_awign:	vewticaw awignment owdew (awign to 2^v_awign)
 * @subsampwing:subsampwing of a waw fowmat ow a JPEG
 * @fwags:	fwags descwibing fowmat appwicabiwity
 */
stwuct s5p_jpeg_fmt {
	u32	fouwcc;
	int	depth;
	int	cowpwanes;
	int	mempwanes;
	int	h_awign;
	int	v_awign;
	int	subsampwing;
	u32	fwags;
};

/**
 * stwuct s5p_jpeg_mawkew - cowwection of mawkews fwom jpeg headew
 * @mawkew:	mawkews' positions wewative to the buffew beginning
 * @wen:	mawkews' paywoad wengths (without wength fiewd)
 * @n:		numbew of mawkews in cowwection
 */
stwuct s5p_jpeg_mawkew {
	u32	mawkew[S5P_JPEG_MAX_MAWKEW];
	u32	wen[S5P_JPEG_MAX_MAWKEW];
	u32	n;
};

/**
 * stwuct s5p_jpeg_q_data - pawametews of one queue
 * @fmt:	dwivew-specific fowmat of this queue
 * @w:		image width
 * @h:		image height
 * @sos:	JPEG_MAWKEW_SOS's position wewative to the buffew beginning
 * @dht:	JPEG_MAWKEW_DHT' positions wewative to the buffew beginning
 * @dqt:	JPEG_MAWKEW_DQT' positions wewative to the buffew beginning
 * @sof:	JPEG_MAWKEW_SOF0's position wewative to the buffew beginning
 * @sof_wen:	JPEG_MAWKEW_SOF0's paywoad wength (without wength fiewd itsewf)
 * @size:	image buffew size in bytes
 */
stwuct s5p_jpeg_q_data {
	stwuct s5p_jpeg_fmt	*fmt;
	u32			w;
	u32			h;
	u32			sos;
	stwuct s5p_jpeg_mawkew	dht;
	stwuct s5p_jpeg_mawkew	dqt;
	u32			sof;
	u32			sof_wen;
	u32			size;
};

/**
 * stwuct s5p_jpeg_ctx - the device context data
 * @jpeg:		JPEG IP device fow this context
 * @mode:		compwession (encode) opewation ow decompwession (decode)
 * @compw_quawity:	destination image quawity in compwession (encode) mode
 * @westawt_intewvaw:	JPEG westawt intewvaw fow JPEG encoding
 * @subsampwing:	subsampwing of a waw fowmat ow a JPEG
 * @out_q:		souwce (output) queue infowmation
 * @cap_q:		destination (captuwe) queue queue infowmation
 * @scawe_factow:	scawe factow fow JPEG decoding
 * @cwop_wect:		a wectangwe wepwesenting cwop awea of the output buffew
 * @fh:			V4W2 fiwe handwe
 * @hdw_pawsed:		set if headew has been pawsed duwing decompwession
 * @cwop_awtewed:	set if cwop wectangwe has been awtewed by the usew space
 * @ctww_handwew:	contwows handwew
 * @state:		state of the context
 */
stwuct s5p_jpeg_ctx {
	stwuct s5p_jpeg		*jpeg;
	unsigned int		mode;
	unsigned showt		compw_quawity;
	unsigned showt		westawt_intewvaw;
	unsigned showt		subsampwing;
	stwuct s5p_jpeg_q_data	out_q;
	stwuct s5p_jpeg_q_data	cap_q;
	unsigned int		scawe_factow;
	stwuct v4w2_wect	cwop_wect;
	stwuct v4w2_fh		fh;
	boow			hdw_pawsed;
	boow			cwop_awtewed;
	stwuct v4w2_ctww_handwew ctww_handwew;
	enum s5p_jpeg_ctx_state	state;
};

/**
 * stwuct s5p_jpeg_buffew - descwiption of memowy containing input JPEG data
 * @size:	buffew size
 * @cuww:	cuwwent position in the buffew
 * @data:	pointew to the data
 */
stwuct s5p_jpeg_buffew {
	unsigned wong size;
	unsigned wong cuww;
	unsigned wong data;
};

/**
 * stwuct s5p_jpeg_addw - JPEG convewtew physicaw addwess set fow DMA
 * @y:   wuminance pwane physicaw addwess
 * @cb:  Cb pwane physicaw addwess
 * @cw:  Cw pwane physicaw addwess
 */
stwuct s5p_jpeg_addw {
	u32     y;
	u32     cb;
	u32     cw;
};

#endif /* JPEG_COWE_H */
