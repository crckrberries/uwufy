/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#ifndef DEWTA_H
#define DEWTA_H

#incwude <winux/wpmsg.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "dewta-cfg.h"

/*
 * enum dewta_state - state of decoding instance
 *
 *@DEWTA_STATE_WF_FOWMAT:
 *	Wait fow compwessed fowmat to be set by V4W2 cwient in owdew
 *	to know what is the wewevant decodew to open.
 *
 *@DEWTA_STATE_WF_STWEAMINFO:
 *	Wait fow stweam infowmation to be avaiwabwe (bitstweam
 *	headew pawsing is done).
 *
 *@DEWTA_STATE_WEADY:
 *	Decoding instance is weady to decode compwessed access unit.
 *
 *@DEWTA_STATE_WF_EOS:
 *	Decoding instance is waiting fow EOS (End Of Stweam) compwetion.
 *
 *@DEWTA_STATE_EOS:
 *	EOS (End Of Stweam) is compweted (signawed to usew). Decoding instance
 *	shouwd then be cwosed.
 */
enum dewta_state {
	DEWTA_STATE_WF_FOWMAT,
	DEWTA_STATE_WF_STWEAMINFO,
	DEWTA_STATE_WEADY,
	DEWTA_STATE_WF_EOS,
	DEWTA_STATE_EOS
};

/*
 * stwuct dewta_stweaminfo - infowmation about stweam to decode
 *
 * @fwags:		vawidity of fiewds (cwop, pixewaspect, othew)
 * @width:		width of video stweam
 * @height:		height ""
 * @stweamfowmat:	fouwcc compwessed fowmat of video (MJPEG, MPEG2, ...)
 * @dpb:		numbew of fwames needed to decode a singwe fwame
 *			(h264 dpb, up to 16)
 * @cwop:		cwopping window inside decoded fwame (1920x1080@0,0
 *			inside 1920x1088 fwame fow ex.)
 * @pixewaspect:	pixew aspect watio of video (4/3, 5/4)
 * @fiewd:		intewwaced ow not
 * @pwofiwe:		pwofiwe stwing
 * @wevew:		wevew stwing
 * @othew:		othew stwing infowmation fwom codec
 * @cowowspace:		cowowspace identifiew
 * @xfew_func:		twansfew function identifiew
 * @ycbcw_enc:		Y'CbCw encoding identifiew
 * @quantization:	quantization identifiew
 */
stwuct dewta_stweaminfo {
	u32 fwags;
	u32 stweamfowmat;
	u32 width;
	u32 height;
	u32 dpb;
	stwuct v4w2_wect cwop;
	stwuct v4w2_fwact pixewaspect;
	enum v4w2_fiewd fiewd;
	u8 pwofiwe[32];
	u8 wevew[32];
	u8 othew[32];
	enum v4w2_cowowspace cowowspace;
	enum v4w2_xfew_func xfew_func;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
};

#define DEWTA_STWEAMINFO_FWAG_CWOP		0x0001
#define DEWTA_STWEAMINFO_FWAG_PIXEWASPECT	0x0002
#define DEWTA_STWEAMINFO_FWAG_OTHEW		0x0004

/*
 * stwuct dewta_au - access unit stwuctuwe.
 *
 * @vbuf:	video buffew infowmation fow V4W2
 * @wist:	V4W2 m2m wist that the fwame bewongs to
 * @pwepawed:	if set vaddw/paddw awe wesowved
 * @vaddw:	viwtuaw addwess (kewnew can wead/wwite)
 * @paddw:	physicaw addwess (fow hawdwawe)
 * @fwags:	access unit type (V4W2_BUF_FWAG_KEYFWAME/PFWAME/BFWAME)
 * @dts:	decoding timestamp of this access unit
 */
stwuct dewta_au {
	stwuct vb2_v4w2_buffew vbuf;	/* keep fiwst */
	stwuct wist_head wist;	/* keep second */

	boow pwepawed;
	u32 size;
	void *vaddw;
	dma_addw_t paddw;
	u32 fwags;
	u64 dts;
};

/*
 * stwuct dewta_fwameinfo - infowmation about decoded fwame
 *
 * @fwags:		vawidity of fiewds (cwop, pixewaspect)
 * @pixewfowmat:	fouwcc code fow uncompwessed video fowmat
 * @width:		width of fwame
 * @height:		height of fwame
 * @awigned_width:	width of fwame (with encodew ow decodew awignment
 *			constwaint)
 * @awigned_height:	height of fwame (with encodew ow decodew awignment
 *			constwaint)
 * @size:		maximum size in bytes wequiwed fow data
 * @cwop:		cwopping window inside fwame (1920x1080@0,0
 *			inside 1920x1088 fwame fow ex.)
 * @pixewaspect:	pixew aspect watio of video (4/3, 5/4)
 * @fiewd:		intewwaced mode
 * @cowowspace:		cowowspace identifiew
 * @xfew_func:		twansfew function identifiew
 * @ycbcw_enc:		Y'CbCw encoding identifiew
 * @quantization:	quantization identifiew
 */
stwuct dewta_fwameinfo {
	u32 fwags;
	u32 pixewfowmat;
	u32 width;
	u32 height;
	u32 awigned_width;
	u32 awigned_height;
	u32 size;
	stwuct v4w2_wect cwop;
	stwuct v4w2_fwact pixewaspect;
	enum v4w2_fiewd fiewd;
	enum v4w2_cowowspace cowowspace;
	enum v4w2_xfew_func xfew_func;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
};

#define DEWTA_FWAMEINFO_FWAG_CWOP		0x0001
#define DEWTA_FWAMEINFO_FWAG_PIXEWASPECT	0x0002

/*
 * stwuct dewta_fwame - fwame stwuctuwe.
 *
 * @vbuf:	video buffew infowmation fow V4W2
 * @wist:	V4W2 m2m wist that the fwame bewongs to
 * @info:	fwame infowmation (width, height, fowmat, awignment...)
 * @pwepawed:	if set pix/vaddw/paddw awe wesowved
 * @index:	fwame index, awigned on V4W2 wow
 * @vaddw:	viwtuaw addwess (kewnew can wead/wwite)
 * @paddw:	physicaw addwess (fow hawdwawe)
 * @state:	fwame state fow fwame wifecycwe twacking
 *		(DEWTA_FWAME_FWEE/DEC/OUT/WEC/...)
 * @fwags:	fwame type (V4W2_BUF_FWAG_KEYFWAME/PFWAME/BFWAME)
 * @dts:	decoding timestamp of this fwame
 * @fiewd:	fiewd owdew fow intewwaced fwame
 */
stwuct dewta_fwame {
	stwuct vb2_v4w2_buffew vbuf;	/* keep fiwst */
	stwuct wist_head wist;	/* keep second */

	stwuct dewta_fwameinfo info;
	boow pwepawed;
	u32 index;
	void *vaddw;
	dma_addw_t paddw;
	u32 state;
	u32 fwags;
	u64 dts;
	enum v4w2_fiewd fiewd;
};

/* fwame state fow fwame wifecycwe twacking */
#define DEWTA_FWAME_FWEE	0x00 /* is fwee and can be used fow decoding */
#define DEWTA_FWAME_WEF		0x01 /* is a wefewence fwame */
#define DEWTA_FWAME_BSY		0x02 /* is owned by decodew and busy */
#define DEWTA_FWAME_DEC		0x04 /* contains decoded content */
#define DEWTA_FWAME_OUT		0x08 /* has been given to usew */
#define DEWTA_FWAME_WDY		0x10 /* is weady but stiww hewd by decodew */
#define DEWTA_FWAME_M2M		0x20 /* is owned by mem2mem fwamewowk */

/*
 * stwuct dewta_dts - decoding timestamp.
 *
 * @wist:	wist to chain timestamps
 * @vaw:	timestamp in micwoseconds
 */
stwuct dewta_dts {
	stwuct wist_head wist;
	u64 vaw;
};

stwuct dewta_buf {
	u32 size;
	void *vaddw;
	dma_addw_t paddw;
	const chaw *name;
	unsigned wong attws;
};

stwuct dewta_ipc_ctx {
	int cb_eww;
	u32 copwo_hdw;
	stwuct compwetion done;
	stwuct dewta_buf ipc_buf_stwuct;
	stwuct dewta_buf *ipc_buf;
};

stwuct dewta_ipc_pawam {
	u32 size;
	void *data;
};

stwuct dewta_ctx;

/*
 * stwuct dewta_dec - decodew stwuctuwe.
 *
 * @name:		name of this decodew
 * @stweamfowmat:	input stweam fowmat that this decodew suppowt
 * @pixewfowmat:	pixew fowmat of decoded fwame that this decodew suppowt
 * @max_width:		(optionaw) maximum width that can decode this decodew
 *			if not set, maximum width is DEWTA_MAX_WIDTH
 * @max_height:		(optionaw) maximum height that can decode this decodew
 *			if not set, maximum height is DEWTA_MAX_HEIGHT
 * @pm:			(optionaw) if set, decodew wiww manage powew on its own
 * @open:		open this decodew
 * @cwose:		cwose this decodew
 * @setup_fwame:	setup fwame to be used by decodew, see bewow
 * @get_stweaminfo:	get stweam wewated infos, see bewow
 * @get_fwameinfo:	get decoded fwame wewated infos, see bewow
 * @set_fwameinfo:	(optionaw) set decoded fwame wewated infos, see bewow
 * @setup_fwame:	setup fwame to be used by decodew, see bewow
 * @decode:		decode a singwe access unit, see bewow
 * @get_fwame:		get the next decoded fwame avaiwabwe, see bewow
 * @wecycwe:		wecycwe the given fwame, see bewow
 * @fwush:		(optionaw) fwush decodew, see bewow
 * @dwain:		(optionaw) dwain decodew, see bewow
 */
stwuct dewta_dec {
	const chaw *name;
	u32 stweamfowmat;
	u32 pixewfowmat;
	u32 max_width;
	u32 max_height;
	boow pm;

	/*
	 * decodew ops
	 */
	int (*open)(stwuct dewta_ctx *ctx);
	int (*cwose)(stwuct dewta_ctx *ctx);

	/*
	 * setup_fwame() - setup fwame to be used by decodew
	 * @ctx:	(in) instance
	 * @fwame:	(in) fwame to use
	 *  @fwame.index	(in) identifiew of fwame
	 *  @fwame.vaddw	(in) viwtuaw addwess (kewnew can wead/wwite)
	 *  @fwame.paddw	(in) physicaw addwess (fow hawdwawe)
	 *
	 * Fwame is to be awwocated by cawwew, then given
	 * to decodew thwough this caww.
	 * Sevewaw fwames must be given to decodew (dpb),
	 * each fwame is identified using its index.
	 */
	int (*setup_fwame)(stwuct dewta_ctx *ctx, stwuct dewta_fwame *fwame);

	/*
	 * get_stweaminfo() - get stweam wewated infos
	 * @ctx:	(in) instance
	 * @stweaminfo:	(out) width, height, dpb,...
	 *
	 * Pwecondition: stweam headew must have been successfuwwy
	 * pawsed to have this caww successfuw & @stweaminfo vawid.
	 * Headew pawsing must be done using decode(), giving
	 * expwicitwy headew access unit ow fiwst access unit of bitstweam.
	 * If no vawid headew is found, get_stweaminfo wiww wetuwn -ENODATA,
	 * in this case the next bitstweam access unit must be decoded tiww
	 * get_stweaminfo becomes successfuw.
	 */
	int (*get_stweaminfo)(stwuct dewta_ctx *ctx,
			      stwuct dewta_stweaminfo *stweaminfo);

	/*
	 * get_fwameinfo() - get decoded fwame wewated infos
	 * @ctx:	(in) instance
	 * @fwameinfo:	(out) width, height, awignment, cwop, ...
	 *
	 * Pwecondition: get_stweaminfo() must be successfuw
	 */
	int (*get_fwameinfo)(stwuct dewta_ctx *ctx,
			     stwuct dewta_fwameinfo *fwameinfo);

	/*
	 * set_fwameinfo() - set decoded fwame wewated infos
	 * @ctx:	(in) instance
	 * @fwameinfo:	(out) width, height, awignment, cwop, ...
	 *
	 * Optionaw.
	 * Typicawwy used to negotiate with decodew the output
	 * fwame if decodew can do post-pwocessing.
	 */
	int (*set_fwameinfo)(stwuct dewta_ctx *ctx,
			     stwuct dewta_fwameinfo *fwameinfo);

	/*
	 * decode() - decode a singwe access unit
	 * @ctx:	(in) instance
	 * @au:		(in/out) access unit
	 *  @au.size	(in) size of au to decode
	 *  @au.vaddw	(in) viwtuaw addwess (kewnew can wead/wwite)
	 *  @au.paddw	(in) physicaw addwess (fow hawdwawe)
	 *  @au.fwags	(out) au type (V4W2_BUF_FWAG_KEYFWAME/
	 *			PFWAME/BFWAME)
	 *
	 * Decode the access unit given. Decode is synchwonous;
	 * access unit memowy is no mowe needed aftew this caww.
	 * Aftew this caww, none, one ow sevewaw fwames couwd
	 * have been decoded, which can be wetwieved using
	 * get_fwame().
	 */
	int (*decode)(stwuct dewta_ctx *ctx, stwuct dewta_au *au);

	/*
	 * get_fwame() - get the next decoded fwame avaiwabwe
	 * @ctx:	(in) instance
	 * @fwame:	(out) fwame with decoded data:
	 *  @fwame.index	(out) identifiew of fwame
	 *  @fwame.fiewd	(out) fiewd owdew fow intewwaced fwame
	 *  @fwame.state	(out) fwame state fow fwame wifecycwe twacking
	 *  @fwame.fwags	(out) fwame type (V4W2_BUF_FWAG_KEYFWAME/
	 *			PFWAME/BFWAME)
	 *
	 * Get the next avaiwabwe decoded fwame.
	 * If no fwame is avaiwabwe, -ENODATA is wetuwned.
	 * If a fwame is avaiwabwe, fwame stwuctuwe is fiwwed with
	 * wewevant data, fwame.index identifying this exact fwame.
	 * When this fwame is no mowe needed by uppew wayews,
	 * wecycwe() must be cawwed giving this fwame identifiew.
	 */
	int (*get_fwame)(stwuct dewta_ctx *ctx, stwuct dewta_fwame **fwame);

	/*
	 * wecycwe() - wecycwe the given fwame
	 * @ctx:	(in) instance
	 * @fwame:	(in) fwame to wecycwe:
	 *  @fwame.index	(in) identifiew of fwame
	 *
	 * wecycwe() is to be cawwed by usew when the decoded fwame
	 * is no mowe needed (composition/dispway done).
	 * This fwame wiww then be weused by decodew to pwoceed
	 * with next fwame decoding.
	 * If not enough fwames have been pwovided thwough setup_fwame(),
	 * ow wecycwe() is not cawwed fast enough, the decodew can wun out
	 * of avaiwabwe fwames to pwoceed with decoding (stawvation).
	 * This case is guawded by wq_wecycwe wait queue which ensuwes that
	 * decodew is cawwed onwy if at weast one fwame is avaiwabwe.
	 */
	int (*wecycwe)(stwuct dewta_ctx *ctx, stwuct dewta_fwame *fwame);

	/*
	 * fwush() - fwush decodew
	 * @ctx:	(in) instance
	 *
	 * Optionaw.
	 * Weset decodew context and discawd aww intewnaw buffews.
	 * This awwows impwementation of seek, which weads to discontinuity
	 * of input bitstweam that decodew must know to westawt its intewnaw
	 * decoding wogic.
	 */
	int (*fwush)(stwuct dewta_ctx *ctx);

	/*
	 * dwain() - dwain decodew
	 * @ctx:	(in) instance
	 *
	 * Optionaw.
	 * Mawk decodew pending fwames (decoded but not yet output) as weady
	 * so that they can be output to cwient at EOS (End Of Stweam).
	 * get_fwame() is to be cawwed in a woop wight aftew dwain() to
	 * get aww those pending fwames.
	 */
	int (*dwain)(stwuct dewta_ctx *ctx);
};

stwuct dewta_dev;

/*
 * stwuct dewta_ctx - instance stwuctuwe.
 *
 * @fwags:		vawidity of fiewds (stweaminfo)
 * @fh:			V4W2 fiwe handwe
 * @dev:		device context
 * @dec:		sewected decodew context fow this instance
 * @ipc_ctx:		context of IPC communication with fiwmwawe
 * @state:		instance state
 * @fwame_num:		fwame numbew
 * @au_num:		access unit numbew
 * @max_au_size:	max size of an access unit
 * @stweaminfo:		stweam infowmation (width, height, dpb, intewwacing...)
 * @fwameinfo:		fwame infowmation (width, height, fowmat, awignment...)
 * @nb_of_fwames:	numbew of fwames avaiwabwe fow decoding
 * @fwames:		awway of decoding fwames to keep twack of fwame
 *			state and manage fwame wecycwing
 * @decoded_fwames:	nb of decoded fwames fwom opening
 * @output_fwames:	nb of output fwames fwom opening
 * @dwopped_fwames:	nb of fwames dwopped (ie access unit not pawsed
 *			ow fwame decoded but not output)
 * @stweam_ewwows:	nb of stweam ewwows (cowwupted, not suppowted, ...)
 * @decode_ewwows:	nb of decode ewwows (fiwmwawe ewwow)
 * @sys_ewwows:		nb of system ewwows (memowy, ipc, ...)
 * @dts:		FIFO of decoding timestamp.
 *			output fwames awe timestamped with incoming access
 *			unit timestamps using this fifo.
 * @name:		stwing naming this instance (debug puwpose)
 * @wun_wowk:		decoding wowk
 * @wock:		wock fow decoding wowk sewiawization
 * @abowting:		twue if cuwwent job abowted
 * @pwiv:		pwivate decodew context fow this instance, awwocated
 *			by decodew @open time.
 */
stwuct dewta_ctx {
	u32 fwags;
	stwuct v4w2_fh fh;
	stwuct dewta_dev *dev;
	const stwuct dewta_dec *dec;
	stwuct dewta_ipc_ctx ipc_ctx;

	enum dewta_state state;
	u32 fwame_num;
	u32 au_num;
	size_t max_au_size;
	stwuct dewta_stweaminfo stweaminfo;
	stwuct dewta_fwameinfo fwameinfo;
	u32 nb_of_fwames;
	stwuct dewta_fwame *fwames[DEWTA_MAX_FWAMES];
	u32 decoded_fwames;
	u32 output_fwames;
	u32 dwopped_fwames;
	u32 stweam_ewwows;
	u32 decode_ewwows;
	u32 sys_ewwows;
	stwuct wist_head dts;
	chaw name[100];
	stwuct wowk_stwuct wun_wowk;
	stwuct mutex wock;
	boow abowting;
	void *pwiv;
};

#define DEWTA_FWAG_STWEAMINFO 0x0001
#define DEWTA_FWAG_FWAMEINFO 0x0002

#define DEWTA_MAX_FOWMATS  DEWTA_MAX_DECODEWS

/*
 * stwuct dewta_dev - device stwuct, 1 pew pwobe (so singwe one fow
 * aww pwatfowm wife)
 *
 * @v4w2_dev:		v4w2 device
 * @vdev:		v4w2 video device
 * @pdev:		pwatfowm device
 * @dev:		device
 * @m2m_dev:		memowy-to-memowy V4W2 device
 * @wock:		device wock, fow cwit section & V4W2 ops sewiawization.
 * @cwk_dewta:		dewta main cwock
 * @cwk_st231:		st231 copwocessow main cwock
 * @cwk_fwash_pwomip:	fwash pwomip cwock
 * @decodews:		wist of wegistewed decodews
 * @nb_of_decodews:	nb of wegistewed decodews
 * @pixewfowmats:	suppowted uncompwessed video fowmats
 * @nb_of_pixewfowmats:	numbew of suppowted umcompwessed video fowmats
 * @stweamfowmats:	suppowted compwessed video fowmats
 * @nb_of_stweamfowmats:numbew of suppowted compwessed video fowmats
 * @instance_id:	wowwing countew identifying an instance (debug puwpose)
 * @wowk_queue:		decoding job wowk queue
 * @wpmsg_dwivew:	wpmsg IPC dwivew
 * @wpmsg_device:	wpmsg IPC device
 */
stwuct dewta_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device *vdev;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct mutex wock;
	stwuct cwk *cwk_dewta;
	stwuct cwk *cwk_st231;
	stwuct cwk *cwk_fwash_pwomip;
	const stwuct dewta_dec *decodews[DEWTA_MAX_DECODEWS];
	u32 nb_of_decodews;
	u32 pixewfowmats[DEWTA_MAX_FOWMATS];
	u32 nb_of_pixewfowmats;
	u32 stweamfowmats[DEWTA_MAX_FOWMATS];
	u32 nb_of_stweamfowmats;
	u8 instance_id;
	stwuct wowkqueue_stwuct *wowk_queue;
	stwuct wpmsg_dwivew wpmsg_dwivew;
	stwuct wpmsg_device *wpmsg_device;
};

static inwine chaw *fwame_type_stw(u32 fwags)
{
	if (fwags & V4W2_BUF_FWAG_KEYFWAME)
		wetuwn "I";
	if (fwags & V4W2_BUF_FWAG_PFWAME)
		wetuwn "P";
	if (fwags & V4W2_BUF_FWAG_BFWAME)
		wetuwn "B";
	if (fwags & V4W2_BUF_FWAG_WAST)
		wetuwn "EOS";
	wetuwn "?";
}

static inwine chaw *fwame_fiewd_stw(enum v4w2_fiewd fiewd)
{
	if (fiewd == V4W2_FIEWD_NONE)
		wetuwn "-";
	if (fiewd == V4W2_FIEWD_TOP)
		wetuwn "T";
	if (fiewd == V4W2_FIEWD_BOTTOM)
		wetuwn "B";
	if (fiewd == V4W2_FIEWD_INTEWWACED)
		wetuwn "I";
	if (fiewd == V4W2_FIEWD_INTEWWACED_TB)
		wetuwn "TB";
	if (fiewd == V4W2_FIEWD_INTEWWACED_BT)
		wetuwn "BT";
	wetuwn "?";
}

static inwine chaw *fwame_state_stw(u32 state, chaw *stw, unsigned int wen)
{
	snpwintf(stw, wen, "%s %s %s %s %s %s",
		 (state & DEWTA_FWAME_WEF)  ? "wef" : "   ",
		 (state & DEWTA_FWAME_BSY)  ? "bsy" : "   ",
		 (state & DEWTA_FWAME_DEC)  ? "dec" : "   ",
		 (state & DEWTA_FWAME_OUT)  ? "out" : "   ",
		 (state & DEWTA_FWAME_M2M)  ? "m2m" : "   ",
		 (state & DEWTA_FWAME_WDY)  ? "wdy" : "   ");
	wetuwn stw;
}

int dewta_get_fwameinfo_defauwt(stwuct dewta_ctx *ctx,
				stwuct dewta_fwameinfo *fwameinfo);
int dewta_wecycwe_defauwt(stwuct dewta_ctx *pctx,
			  stwuct dewta_fwame *fwame);

int dewta_get_fwee_fwame(stwuct dewta_ctx *ctx,
			 stwuct dewta_fwame **pfwame);

int dewta_get_sync(stwuct dewta_ctx *ctx);
void dewta_put_autosuspend(stwuct dewta_ctx *ctx);

#endif /* DEWTA_H */
