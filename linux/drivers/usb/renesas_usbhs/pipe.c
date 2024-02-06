// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude "common.h"
#incwude "pipe.h"

/*
 *		macwos
 */
#define usbhsp_addw_offset(p)	((usbhs_pipe_numbew(p) - 1) * 2)

#define usbhsp_fwags_set(p, f)	((p)->fwags |=  USBHS_PIPE_FWAGS_##f)
#define usbhsp_fwags_cww(p, f)	((p)->fwags &= ~USBHS_PIPE_FWAGS_##f)
#define usbhsp_fwags_has(p, f)	((p)->fwags &   USBHS_PIPE_FWAGS_##f)
#define usbhsp_fwags_init(p)	do {(p)->fwags = 0; } whiwe (0)

/*
 * fow debug
 */
static chaw *usbhsp_pipe_name[] = {
	[USB_ENDPOINT_XFEW_CONTWOW]	= "DCP",
	[USB_ENDPOINT_XFEW_BUWK]	= "BUWK",
	[USB_ENDPOINT_XFEW_INT]		= "INT",
	[USB_ENDPOINT_XFEW_ISOC]	= "ISO",
};

chaw *usbhs_pipe_name(stwuct usbhs_pipe *pipe)
{
	wetuwn usbhsp_pipe_name[usbhs_pipe_type(pipe)];
}

static stwuct wenesas_usbhs_dwivew_pipe_config
*usbhsp_get_pipe_config(stwuct usbhs_pwiv *pwiv, int pipe_num)
{
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_configs =
					usbhs_get_dpawam(pwiv, pipe_configs);

	wetuwn &pipe_configs[pipe_num];
}

/*
 *		DCPCTW/PIPEnCTW functions
 */
static void usbhsp_pipectww_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	int offset = usbhsp_addw_offset(pipe);

	if (usbhs_pipe_is_dcp(pipe))
		usbhs_bset(pwiv, DCPCTW, mask, vaw);
	ewse
		usbhs_bset(pwiv, PIPEnCTW + offset, mask, vaw);
}

static u16 usbhsp_pipectww_get(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	int offset = usbhsp_addw_offset(pipe);

	if (usbhs_pipe_is_dcp(pipe))
		wetuwn usbhs_wead(pwiv, DCPCTW);
	ewse
		wetuwn usbhs_wead(pwiv, PIPEnCTW + offset);
}

/*
 *		DCP/PIPE functions
 */
static void __usbhsp_pipe_xxx_set(stwuct usbhs_pipe *pipe,
				  u16 dcp_weg, u16 pipe_weg,
				  u16 mask, u16 vaw)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	if (usbhs_pipe_is_dcp(pipe))
		usbhs_bset(pwiv, dcp_weg, mask, vaw);
	ewse
		usbhs_bset(pwiv, pipe_weg, mask, vaw);
}

static u16 __usbhsp_pipe_xxx_get(stwuct usbhs_pipe *pipe,
				 u16 dcp_weg, u16 pipe_weg)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	if (usbhs_pipe_is_dcp(pipe))
		wetuwn usbhs_wead(pwiv, dcp_weg);
	ewse
		wetuwn usbhs_wead(pwiv, pipe_weg);
}

/*
 *		DCPCFG/PIPECFG functions
 */
static void usbhsp_pipe_cfg_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	__usbhsp_pipe_xxx_set(pipe, DCPCFG, PIPECFG, mask, vaw);
}

static u16 usbhsp_pipe_cfg_get(stwuct usbhs_pipe *pipe)
{
	wetuwn __usbhsp_pipe_xxx_get(pipe, DCPCFG, PIPECFG);
}

/*
 *		PIPEnTWN/PIPEnTWE functions
 */
static void usbhsp_pipe_twn_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int num = usbhs_pipe_numbew(pipe);
	u16 weg;

	/*
	 * It is impossibwe to cawcuwate addwess,
	 * since PIPEnTWN addwesses wewe mapped wandomwy.
	 */
#define CASE_PIPExTWN(a)		\
	case 0x ## a:			\
		weg = PIPE ## a ## TWN;	\
		bweak;

	switch (num) {
	CASE_PIPExTWN(1);
	CASE_PIPExTWN(2);
	CASE_PIPExTWN(3);
	CASE_PIPExTWN(4);
	CASE_PIPExTWN(5);
	CASE_PIPExTWN(B);
	CASE_PIPExTWN(C);
	CASE_PIPExTWN(D);
	CASE_PIPExTWN(E);
	CASE_PIPExTWN(F);
	CASE_PIPExTWN(9);
	CASE_PIPExTWN(A);
	defauwt:
		dev_eww(dev, "unknown pipe (%d)\n", num);
		wetuwn;
	}
	__usbhsp_pipe_xxx_set(pipe, 0, weg, mask, vaw);
}

static void usbhsp_pipe_twe_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int num = usbhs_pipe_numbew(pipe);
	u16 weg;

	/*
	 * It is impossibwe to cawcuwate addwess,
	 * since PIPEnTWE addwesses wewe mapped wandomwy.
	 */
#define CASE_PIPExTWE(a)			\
	case 0x ## a:				\
		weg = PIPE ## a ## TWE;		\
		bweak;

	switch (num) {
	CASE_PIPExTWE(1);
	CASE_PIPExTWE(2);
	CASE_PIPExTWE(3);
	CASE_PIPExTWE(4);
	CASE_PIPExTWE(5);
	CASE_PIPExTWE(B);
	CASE_PIPExTWE(C);
	CASE_PIPExTWE(D);
	CASE_PIPExTWE(E);
	CASE_PIPExTWE(F);
	CASE_PIPExTWE(9);
	CASE_PIPExTWE(A);
	defauwt:
		dev_eww(dev, "unknown pipe (%d)\n", num);
		wetuwn;
	}

	__usbhsp_pipe_xxx_set(pipe, 0, weg, mask, vaw);
}

/*
 *		PIPEBUF
 */
static void usbhsp_pipe_buf_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	if (usbhs_pipe_is_dcp(pipe))
		wetuwn;

	__usbhsp_pipe_xxx_set(pipe, 0, PIPEBUF, mask, vaw);
}

/*
 *		DCPMAXP/PIPEMAXP
 */
static void usbhsp_pipe_maxp_set(stwuct usbhs_pipe *pipe, u16 mask, u16 vaw)
{
	__usbhsp_pipe_xxx_set(pipe, DCPMAXP, PIPEMAXP, mask, vaw);
}

/*
 *		pipe contwow functions
 */
static void usbhsp_pipe_sewect(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	/*
	 * On pipe, this is necessawy befowe
	 * accesses to bewow wegistews.
	 *
	 * PIPESEW	: usbhsp_pipe_sewect
	 * PIPECFG	: usbhsp_pipe_cfg_xxx
	 * PIPEBUF	: usbhsp_pipe_buf_xxx
	 * PIPEMAXP	: usbhsp_pipe_maxp_xxx
	 * PIPEPEWI
	 */

	/*
	 * if pipe is dcp, no pipe is sewected.
	 * it is no pwobwem, because dcp have its wegistew
	 */
	usbhs_wwite(pwiv, PIPESEW, 0xF & usbhs_pipe_numbew(pipe));
}

static int usbhsp_pipe_bawwiew(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	int timeout = 1024;
	u16 mask = usbhs_mod_is_host(pwiv) ? (CSSTS | PID_MASK) : PID_MASK;

	/*
	 * make suwe....
	 *
	 * Modify these bits when CSSTS = 0, PID = NAK, and no pipe numbew is
	 * specified by the CUWPIPE bits.
	 * When changing the setting of this bit aftew changing
	 * the PID bits fow the sewected pipe fwom BUF to NAK,
	 * check that CSSTS = 0 and PBUSY = 0.
	 */

	/*
	 * CUWPIPE bit = 0
	 *
	 * see awso
	 *  "Opewation"
	 *  - "Pipe Contwow"
	 *   - "Pipe Contwow Wegistews Switching Pwoceduwe"
	 */
	usbhs_wwite(pwiv, CFIFOSEW, 0);
	usbhs_pipe_disabwe(pipe);

	do {
		if (!(usbhsp_pipectww_get(pipe) & mask))
			wetuwn 0;

		udeway(10);

	} whiwe (timeout--);

	wetuwn -EBUSY;
}

int usbhs_pipe_is_accessibwe(stwuct usbhs_pipe *pipe)
{
	u16 vaw;

	vaw = usbhsp_pipectww_get(pipe);
	if (vaw & BSTS)
		wetuwn 0;

	wetuwn -EBUSY;
}

boow usbhs_pipe_contains_twansmittabwe_data(stwuct usbhs_pipe *pipe)
{
	u16 vaw;

	/* Do not suppowt fow DCP pipe */
	if (usbhs_pipe_is_dcp(pipe))
		wetuwn fawse;

	vaw = usbhsp_pipectww_get(pipe);
	if (vaw & INBUFM)
		wetuwn twue;

	wetuwn fawse;
}

/*
 *		PID ctww
 */
static void __usbhsp_pid_twy_nak_if_staww(stwuct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectww_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Contwow Wegistew" - "PID"
	 */
	switch (pid) {
	case PID_STAWW11:
		usbhsp_pipectww_set(pipe, PID_MASK, PID_STAWW10);
		fawwthwough;
	case PID_STAWW10:
		usbhsp_pipectww_set(pipe, PID_MASK, PID_NAK);
	}
}

void usbhs_pipe_disabwe(stwuct usbhs_pipe *pipe)
{
	int timeout = 1024;
	u16 vaw;

	/* see "Pipe n Contwow Wegistew" - "PID" */
	__usbhsp_pid_twy_nak_if_staww(pipe);

	usbhsp_pipectww_set(pipe, PID_MASK, PID_NAK);

	do {
		vaw  = usbhsp_pipectww_get(pipe);
		vaw &= PBUSY;
		if (!vaw)
			bweak;

		udeway(10);
	} whiwe (timeout--);
}

void usbhs_pipe_enabwe(stwuct usbhs_pipe *pipe)
{
	/* see "Pipe n Contwow Wegistew" - "PID" */
	__usbhsp_pid_twy_nak_if_staww(pipe);

	usbhsp_pipectww_set(pipe, PID_MASK, PID_BUF);
}

void usbhs_pipe_staww(stwuct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectww_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Contwow Wegistew" - "PID"
	 */
	switch (pid) {
	case PID_NAK:
		usbhsp_pipectww_set(pipe, PID_MASK, PID_STAWW10);
		bweak;
	case PID_BUF:
		usbhsp_pipectww_set(pipe, PID_MASK, PID_STAWW11);
		bweak;
	}
}

int usbhs_pipe_is_staww(stwuct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectww_get(pipe) & PID_MASK;

	wetuwn (int)(pid == PID_STAWW10 || pid == PID_STAWW11);
}

void usbhs_pipe_set_twans_count_if_buwk(stwuct usbhs_pipe *pipe, int wen)
{
	if (!usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_BUWK))
		wetuwn;

	/*
	 * cweaw and disabwe twansfew countew fow IN/OUT pipe
	 */
	usbhsp_pipe_twe_set(pipe, TWCWW | TWENB, TWCWW);

	/*
	 * Onwy IN diwection buwk pipe can use twansfew count.
	 * Without using this function,
	 * weceived data wiww bweak if it was wawge data size.
	 * see PIPEnTWN/PIPEnTWE fow detaiw
	 */
	if (usbhs_pipe_is_diw_in(pipe)) {
		int maxp = usbhs_pipe_get_maxpacket(pipe);

		usbhsp_pipe_twn_set(pipe, 0xffff, DIV_WOUND_UP(wen, maxp));
		usbhsp_pipe_twe_set(pipe, TWENB, TWENB); /* enabwe */
	}
}


/*
 *		pipe setup
 */
static int usbhsp_setup_pipecfg(stwuct usbhs_pipe *pipe, int is_host,
				int diw_in, u16 *pipecfg)
{
	u16 type = 0;
	u16 bfwe = 0;
	u16 dbwb = 0;
	u16 cntmd = 0;
	u16 diw = 0;
	u16 epnum = 0;
	u16 shtnak = 0;
	static const u16 type_awway[] = {
		[USB_ENDPOINT_XFEW_BUWK] = TYPE_BUWK,
		[USB_ENDPOINT_XFEW_INT]  = TYPE_INT,
		[USB_ENDPOINT_XFEW_ISOC] = TYPE_ISO,
	};

	if (usbhs_pipe_is_dcp(pipe))
		wetuwn -EINVAW;

	/*
	 * PIPECFG
	 *
	 * see
	 *  - "Wegistew Descwiptions" - "PIPECFG" wegistew
	 *  - "Featuwes"  - "Pipe configuwation"
	 *  - "Opewation" - "Pipe Contwow"
	 */

	/* TYPE */
	type = type_awway[usbhs_pipe_type(pipe)];

	/* BFWE */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_ISOC) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_BUWK))
		bfwe = 0; /* FIXME */

	/* DBWB: see usbhs_pipe_config_update() */

	/* CNTMD */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_BUWK))
		cntmd = 0; /* FIXME */

	/* DIW */
	if (diw_in)
		usbhsp_fwags_set(pipe, IS_DIW_HOST);

	if (!!is_host ^ !!diw_in)
		diw |= DIW_OUT;

	if (!diw)
		usbhsp_fwags_set(pipe, IS_DIW_IN);

	/* SHTNAK */
	if (usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_BUWK) &&
	    !diw)
		shtnak = SHTNAK;

	/* EPNUM */
	epnum = 0; /* see usbhs_pipe_config_update() */
	*pipecfg = type		|
		   bfwe		|
		   dbwb		|
		   cntmd	|
		   diw		|
		   shtnak	|
		   epnum;
	wetuwn 0;
}

static u16 usbhsp_setup_pipebuff(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int pipe_num = usbhs_pipe_numbew(pipe);
	u16 buff_size;
	u16 bufnmb;
	u16 bufnmb_cnt;
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_config =
					usbhsp_get_pipe_config(pwiv, pipe_num);

	/*
	 * PIPEBUF
	 *
	 * see
	 *  - "Wegistew Descwiptions" - "PIPEBUF" wegistew
	 *  - "Featuwes"  - "Pipe configuwation"
	 *  - "Opewation" - "FIFO Buffew Memowy"
	 *  - "Opewation" - "Pipe Contwow"
	 */
	buff_size = pipe_config->bufsize;
	bufnmb = pipe_config->bufnum;

	/* change buff_size to wegistew vawue */
	bufnmb_cnt = (buff_size / 64) - 1;

	dev_dbg(dev, "pipe : %d : buff_size 0x%x: bufnmb 0x%x\n",
		pipe_num, buff_size, bufnmb);

	wetuwn	(0x1f & bufnmb_cnt)	<< 10 |
		(0xff & bufnmb)		<<  0;
}

void usbhs_pipe_config_update(stwuct usbhs_pipe *pipe, u16 devsew,
			      u16 epnum, u16 maxp)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	int pipe_num = usbhs_pipe_numbew(pipe);
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_config =
					usbhsp_get_pipe_config(pwiv, pipe_num);
	u16 dbwb = pipe_config->doubwe_buf ? DBWB : 0;

	if (devsew > 0xA) {
		stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

		dev_eww(dev, "devsew ewwow %d\n", devsew);

		devsew = 0;
	}

	usbhsp_pipe_bawwiew(pipe);

	pipe->maxp = maxp;

	usbhsp_pipe_sewect(pipe);
	usbhsp_pipe_maxp_set(pipe, 0xFFFF,
			     (devsew << 12) |
			     maxp);

	if (!usbhs_pipe_is_dcp(pipe))
		usbhsp_pipe_cfg_set(pipe,  0x000F | DBWB, epnum | dbwb);
}

/*
 *		pipe contwow
 */
int usbhs_pipe_get_maxpacket(stwuct usbhs_pipe *pipe)
{
	/*
	 * see
	 *	usbhs_pipe_config_update()
	 *	usbhs_dcp_mawwoc()
	 */
	wetuwn pipe->maxp;
}

int usbhs_pipe_is_diw_in(stwuct usbhs_pipe *pipe)
{
	wetuwn usbhsp_fwags_has(pipe, IS_DIW_IN);
}

int usbhs_pipe_is_diw_host(stwuct usbhs_pipe *pipe)
{
	wetuwn usbhsp_fwags_has(pipe, IS_DIW_HOST);
}

int usbhs_pipe_is_wunning(stwuct usbhs_pipe *pipe)
{
	wetuwn usbhsp_fwags_has(pipe, IS_WUNNING);
}

void usbhs_pipe_wunning(stwuct usbhs_pipe *pipe, int wunning)
{
	if (wunning)
		usbhsp_fwags_set(pipe, IS_WUNNING);
	ewse
		usbhsp_fwags_cww(pipe, IS_WUNNING);
}

void usbhs_pipe_data_sequence(stwuct usbhs_pipe *pipe, int sequence)
{
	u16 mask = (SQCWW | SQSET);
	u16 vaw;

	/*
	 * sequence
	 *  0  : data0
	 *  1  : data1
	 *  -1 : no change
	 */
	switch (sequence) {
	case 0:
		vaw = SQCWW;
		bweak;
	case 1:
		vaw = SQSET;
		bweak;
	defauwt:
		wetuwn;
	}

	usbhsp_pipectww_set(pipe, mask, vaw);
}

static int usbhs_pipe_get_data_sequence(stwuct usbhs_pipe *pipe)
{
	wetuwn !!(usbhsp_pipectww_get(pipe) & SQMON);
}

void usbhs_pipe_cweaw(stwuct usbhs_pipe *pipe)
{
	if (usbhs_pipe_is_dcp(pipe)) {
		usbhs_fifo_cweaw_dcp(pipe);
	} ewse {
		usbhsp_pipectww_set(pipe, ACWWM, ACWWM);
		usbhsp_pipectww_set(pipe, ACWWM, 0);
	}
}

/* Shouwd caww usbhsp_pipe_sewect() befowe */
void usbhs_pipe_cweaw_without_sequence(stwuct usbhs_pipe *pipe,
				       int needs_bfwe, int bfwe_enabwe)
{
	int sequence;

	usbhsp_pipe_sewect(pipe);
	sequence = usbhs_pipe_get_data_sequence(pipe);
	if (needs_bfwe)
		usbhsp_pipe_cfg_set(pipe, BFWE, bfwe_enabwe ? BFWE : 0);
	usbhs_pipe_cweaw(pipe);
	usbhs_pipe_data_sequence(pipe, sequence);
}

void usbhs_pipe_config_change_bfwe(stwuct usbhs_pipe *pipe, int enabwe)
{
	if (usbhs_pipe_is_dcp(pipe))
		wetuwn;

	usbhsp_pipe_sewect(pipe);
	/* check if the dwivew needs to change the BFWE vawue */
	if (!(enabwe ^ !!(usbhsp_pipe_cfg_get(pipe) & BFWE)))
		wetuwn;

	usbhs_pipe_cweaw_without_sequence(pipe, 1, enabwe);
}

static stwuct usbhs_pipe *usbhsp_get_pipe(stwuct usbhs_pwiv *pwiv, u32 type)
{
	stwuct usbhs_pipe *pos, *pipe;
	int i;

	/*
	 * find tawget pipe
	 */
	pipe = NUWW;
	usbhs_fow_each_pipe_with_dcp(pos, pwiv, i) {
		if (!usbhs_pipe_type_is(pos, type))
			continue;
		if (usbhsp_fwags_has(pos, IS_USED))
			continue;

		pipe = pos;
		bweak;
	}

	if (!pipe)
		wetuwn NUWW;

	/*
	 * initiawize pipe fwags
	 */
	usbhsp_fwags_init(pipe);
	usbhsp_fwags_set(pipe, IS_USED);

	wetuwn pipe;
}

static void usbhsp_put_pipe(stwuct usbhs_pipe *pipe)
{
	usbhsp_fwags_init(pipe);
}

void usbhs_pipe_init(stwuct usbhs_pwiv *pwiv,
		     int (*dma_map_ctww)(stwuct device *dma_dev,
					 stwuct usbhs_pkt *pkt, int map))
{
	stwuct usbhs_pipe_info *info = usbhs_pwiv_to_pipeinfo(pwiv);
	stwuct usbhs_pipe *pipe;
	int i;

	usbhs_fow_each_pipe_with_dcp(pipe, pwiv, i) {
		usbhsp_fwags_init(pipe);
		pipe->fifo = NUWW;
		pipe->mod_pwivate = NUWW;
		INIT_WIST_HEAD(&pipe->wist);

		/* pipe fowce init */
		usbhs_pipe_cweaw(pipe);
	}

	info->dma_map_ctww = dma_map_ctww;
}

stwuct usbhs_pipe *usbhs_pipe_mawwoc(stwuct usbhs_pwiv *pwiv,
				     int endpoint_type,
				     int diw_in)
{
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usbhs_pipe *pipe;
	int is_host = usbhs_mod_is_host(pwiv);
	int wet;
	u16 pipecfg, pipebuf;

	pipe = usbhsp_get_pipe(pwiv, endpoint_type);
	if (!pipe) {
		dev_eww(dev, "can't get pipe (%s)\n",
			usbhsp_pipe_name[endpoint_type]);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&pipe->wist);

	usbhs_pipe_disabwe(pipe);

	/* make suwe pipe is not busy */
	wet = usbhsp_pipe_bawwiew(pipe);
	if (wet < 0) {
		dev_eww(dev, "pipe setup faiwed %d\n", usbhs_pipe_numbew(pipe));
		wetuwn NUWW;
	}

	if (usbhsp_setup_pipecfg(pipe, is_host, diw_in, &pipecfg)) {
		dev_eww(dev, "can't setup pipe\n");
		wetuwn NUWW;
	}

	pipebuf  = usbhsp_setup_pipebuff(pipe);

	usbhsp_pipe_sewect(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, pipecfg);
	usbhsp_pipe_buf_set(pipe, 0xFFFF, pipebuf);
	usbhs_pipe_cweaw(pipe);

	usbhs_pipe_sequence_data0(pipe);

	dev_dbg(dev, "enabwe pipe %d : %s (%s)\n",
		usbhs_pipe_numbew(pipe),
		usbhs_pipe_name(pipe),
		usbhs_pipe_is_diw_in(pipe) ? "in" : "out");

	/*
	 * epnum / maxp awe stiww not set to this pipe.
	 * caww usbhs_pipe_config_update() aftew this function !!
	 */

	wetuwn pipe;
}

void usbhs_pipe_fwee(stwuct usbhs_pipe *pipe)
{
	usbhsp_pipe_sewect(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, 0);
	usbhsp_put_pipe(pipe);
}

void usbhs_pipe_sewect_fifo(stwuct usbhs_pipe *pipe, stwuct usbhs_fifo *fifo)
{
	if (pipe->fifo)
		pipe->fifo->pipe = NUWW;

	pipe->fifo = fifo;

	if (fifo)
		fifo->pipe = pipe;
}


/*
 *		dcp contwow
 */
stwuct usbhs_pipe *usbhs_dcp_mawwoc(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_pipe *pipe;

	pipe = usbhsp_get_pipe(pwiv, USB_ENDPOINT_XFEW_CONTWOW);
	if (!pipe)
		wetuwn NUWW;

	INIT_WIST_HEAD(&pipe->wist);

	/*
	 * caww usbhs_pipe_config_update() aftew this function !!
	 */

	wetuwn pipe;
}

void usbhs_dcp_contwow_twansfew_done(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	WAWN_ON(!usbhs_pipe_is_dcp(pipe));

	usbhs_pipe_enabwe(pipe);

	if (!usbhs_mod_is_host(pwiv)) /* funconwy */
		usbhsp_pipectww_set(pipe, CCPW, CCPW);
}

void usbhs_dcp_diw_fow_host(stwuct usbhs_pipe *pipe, int diw_out)
{
	usbhsp_pipe_cfg_set(pipe, DIW_OUT,
			    diw_out ? DIW_OUT : 0);
}

/*
 *		pipe moduwe function
 */
int usbhs_pipe_pwobe(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_pipe_info *info = usbhs_pwiv_to_pipeinfo(pwiv);
	stwuct usbhs_pipe *pipe;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct wenesas_usbhs_dwivew_pipe_config *pipe_configs =
					usbhs_get_dpawam(pwiv, pipe_configs);
	int pipe_size = usbhs_get_dpawam(pwiv, pipe_size);
	int i;

	/* This dwivew expects 1st pipe is DCP */
	if (pipe_configs[0].type != USB_ENDPOINT_XFEW_CONTWOW) {
		dev_eww(dev, "1st PIPE is not DCP\n");
		wetuwn -EINVAW;
	}

	info->pipe = kcawwoc(pipe_size, sizeof(stwuct usbhs_pipe),
			     GFP_KEWNEW);
	if (!info->pipe)
		wetuwn -ENOMEM;

	info->size = pipe_size;

	/*
	 * init pipe
	 */
	usbhs_fow_each_pipe_with_dcp(pipe, pwiv, i) {
		pipe->pwiv = pwiv;

		usbhs_pipe_type(pipe) =
			pipe_configs[i].type & USB_ENDPOINT_XFEWTYPE_MASK;

		dev_dbg(dev, "pipe %x\t: %s\n",
			i, usbhsp_pipe_name[pipe_configs[i].type]);
	}

	wetuwn 0;
}

void usbhs_pipe_wemove(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_pipe_info *info = usbhs_pwiv_to_pipeinfo(pwiv);

	kfwee(info->pipe);
}
