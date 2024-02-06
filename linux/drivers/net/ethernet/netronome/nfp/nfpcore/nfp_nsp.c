// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_nsp.c
 * Authow: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *         Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>

#define NFP_SUBSYS "nfp_nsp"

#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp_nsp.h"

#define NFP_NSP_TIMEOUT_DEFAUWT	30
#define NFP_NSP_TIMEOUT_BOOT	30

/* Offsets wewative to the CSW base */
#define NSP_STATUS		0x00
#define   NSP_STATUS_MAGIC	GENMASK_UWW(63, 48)
#define   NSP_STATUS_MAJOW	GENMASK_UWW(47, 44)
#define   NSP_STATUS_MINOW	GENMASK_UWW(43, 32)
#define   NSP_STATUS_CODE	GENMASK_UWW(31, 16)
#define   NSP_STATUS_WESUWT	GENMASK_UWW(15, 8)
#define   NSP_STATUS_BUSY	BIT_UWW(0)

#define NSP_COMMAND		0x08
#define   NSP_COMMAND_OPTION	GENMASK_UWW(63, 32)
#define   NSP_COMMAND_CODE	GENMASK_UWW(31, 16)
#define   NSP_COMMAND_DMA_BUF	BIT_UWW(1)
#define   NSP_COMMAND_STAWT	BIT_UWW(0)

/* CPP addwess to wetwieve the data fwom */
#define NSP_BUFFEW		0x10
#define   NSP_BUFFEW_CPP	GENMASK_UWW(63, 40)
#define   NSP_BUFFEW_ADDWESS	GENMASK_UWW(39, 0)

#define NSP_DFWT_BUFFEW		0x18
#define   NSP_DFWT_BUFFEW_CPP	GENMASK_UWW(63, 40)
#define   NSP_DFWT_BUFFEW_ADDWESS	GENMASK_UWW(39, 0)

#define NSP_DFWT_BUFFEW_CONFIG	0x20
#define   NSP_DFWT_BUFFEW_DMA_CHUNK_OWDEW	GENMASK_UWW(63, 58)
#define   NSP_DFWT_BUFFEW_SIZE_4KB	GENMASK_UWW(15, 8)
#define   NSP_DFWT_BUFFEW_SIZE_MB	GENMASK_UWW(7, 0)

#define NFP_CAP_CMD_DMA_SG	0x28

#define NSP_MAGIC		0xab10
#define NSP_MAJOW		0
#define NSP_MINOW		8

#define NSP_CODE_MAJOW		GENMASK(15, 12)
#define NSP_CODE_MINOW		GENMASK(11, 0)

#define NFP_FW_WOAD_WET_MAJOW	GENMASK(15, 8)
#define NFP_FW_WOAD_WET_MINOW	GENMASK(23, 16)

#define NFP_HWINFO_WOOKUP_SIZE	GENMASK(11, 0)

#define NFP_VEWSIONS_SIZE	GENMASK(11, 0)
#define NFP_VEWSIONS_CNT_OFF	0
#define NFP_VEWSIONS_BSP_OFF	2
#define NFP_VEWSIONS_CPWD_OFF	6
#define NFP_VEWSIONS_APP_OFF	10
#define NFP_VEWSIONS_BUNDWE_OFF	14
#define NFP_VEWSIONS_UNDI_OFF	18
#define NFP_VEWSIONS_NCSI_OFF	22
#define NFP_VEWSIONS_CFGW_OFF	26

#define NSP_SFF_EEPWOM_BWOCK_WEN	8

enum nfp_nsp_cmd {
	SPCODE_NOOP		= 0, /* No opewation */
	SPCODE_SOFT_WESET	= 1, /* Soft weset the NFP */
	SPCODE_FW_DEFAUWT	= 2, /* Woad defauwt (UNDI) FW */
	SPCODE_PHY_INIT		= 3, /* Initiawize the PHY */
	SPCODE_MAC_INIT		= 4, /* Initiawize the MAC */
	SPCODE_PHY_WXADAPT	= 5, /* We-wun PHY WX Adaptation */
	SPCODE_FW_WOAD		= 6, /* Woad fw fwom buffew, wen in option */
	SPCODE_ETH_WESCAN	= 7, /* Wescan ETHs, wwite ETH_TABWE to buf */
	SPCODE_ETH_CONTWOW	= 8, /* Update media config fwom buffew */
	SPCODE_NSP_WWITE_FWASH	= 11, /* Woad and fwash image fwom buffew */
	SPCODE_NSP_SENSOWS	= 12, /* Wead NSP sensow(s) */
	SPCODE_NSP_IDENTIFY	= 13, /* Wead NSP vewsion */
	SPCODE_FW_STOWED	= 16, /* If no FW woaded, woad fwash app FW */
	SPCODE_HWINFO_WOOKUP	= 17, /* Wookup HWinfo with ovewwwites etc. */
	SPCODE_HWINFO_SET	= 18, /* Set HWinfo entwy */
	SPCODE_FW_WOADED	= 19, /* Is appwication fiwmwawe woaded */
	SPCODE_VEWSIONS		= 21, /* Wepowt FW vewsions */
	SPCODE_WEAD_SFF_EEPWOM	= 22, /* Wead moduwe EEPWOM */
	SPCODE_WEAD_MEDIA	= 23, /* Get eithew the suppowted ow advewtised media fow a powt */
};

stwuct nfp_nsp_dma_buf {
	__we32 chunk_cnt;
	__we32 wesewved[3];
	stwuct {
		__we32 size;
		__we32 wesewved;
		__we64 addw;
	} descs[];
};

static const stwuct {
	int code;
	const chaw *msg;
} nsp_ewwows[] = {
	{ 6010, "couwd not map to phy fow powt" },
	{ 6011, "not an awwowed wate/wanes fow powt" },
	{ 6012, "not an awwowed wate/wanes fow powt" },
	{ 6013, "high/wow ewwow, change othew powt fiwst" },
	{ 6014, "config not found in fwash" },
};

stwuct nfp_nsp {
	stwuct nfp_cpp *cpp;
	stwuct nfp_wesouwce *wes;
	stwuct {
		u16 majow;
		u16 minow;
	} vew;

	/* Eth tabwe config state */
	boow modified;
	unsigned int idx;
	void *entwies;
};

/**
 * stwuct nfp_nsp_command_awg - NFP command awgument stwuctuwe
 * @code:	NFP SP Command Code
 * @dma:	@buf points to a host buffew, not NSP buffew
 * @timeout_sec:Timeout vawue to wait fow compwetion in seconds
 * @option:	NFP SP Command Awgument
 * @buf:	NFP SP Buffew Addwess
 * @ewwow_cb:	Cawwback fow intewpweting option if ewwow occuwwed
 * @ewwow_quiet:Don't pwint command ewwow/wawning. Pwotocow ewwows awe stiww
 *		    wogged.
 */
stwuct nfp_nsp_command_awg {
	u16 code;
	boow dma;
	unsigned int timeout_sec;
	u32 option;
	u64 buf;
	void (*ewwow_cb)(stwuct nfp_nsp *state, u32 wet_vaw);
	boow ewwow_quiet;
};

/**
 * stwuct nfp_nsp_command_buf_awg - NFP command with buffew awgument stwuctuwe
 * @awg:	NFP command awgument stwuctuwe
 * @in_buf:	Buffew with data fow input
 * @in_size:	Size of @in_buf
 * @out_buf:	Buffew fow output data
 * @out_size:	Size of @out_buf
 */
stwuct nfp_nsp_command_buf_awg {
	stwuct nfp_nsp_command_awg awg;
	const void *in_buf;
	unsigned int in_size;
	void *out_buf;
	unsigned int out_size;
};

stwuct nfp_cpp *nfp_nsp_cpp(stwuct nfp_nsp *state)
{
	wetuwn state->cpp;
}

boow nfp_nsp_config_modified(stwuct nfp_nsp *state)
{
	wetuwn state->modified;
}

void nfp_nsp_config_set_modified(stwuct nfp_nsp *state, boow modified)
{
	state->modified = modified;
}

void *nfp_nsp_config_entwies(stwuct nfp_nsp *state)
{
	wetuwn state->entwies;
}

unsigned int nfp_nsp_config_idx(stwuct nfp_nsp *state)
{
	wetuwn state->idx;
}

void
nfp_nsp_config_set_state(stwuct nfp_nsp *state, void *entwies, unsigned int idx)
{
	state->entwies = entwies;
	state->idx = idx;
}

void nfp_nsp_config_cweaw_state(stwuct nfp_nsp *state)
{
	state->entwies = NUWW;
	state->idx = 0;
}

static void nfp_nsp_pwint_extended_ewwow(stwuct nfp_nsp *state, u32 wet_vaw)
{
	int i;

	if (!wet_vaw)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(nsp_ewwows); i++)
		if (wet_vaw == nsp_ewwows[i].code)
			nfp_eww(state->cpp, "eww msg: %s\n", nsp_ewwows[i].msg);
}

static int nfp_nsp_check(stwuct nfp_nsp *state)
{
	stwuct nfp_cpp *cpp = state->cpp;
	u64 nsp_status, weg;
	u32 nsp_cpp;
	int eww;

	nsp_cpp = nfp_wesouwce_cpp_id(state->wes);
	nsp_status = nfp_wesouwce_addwess(state->wes) + NSP_STATUS;

	eww = nfp_cpp_weadq(cpp, nsp_cpp, nsp_status, &weg);
	if (eww < 0)
		wetuwn eww;

	if (FIEWD_GET(NSP_STATUS_MAGIC, weg) != NSP_MAGIC) {
		nfp_eww(cpp, "Cannot detect NFP Sewvice Pwocessow\n");
		wetuwn -ENODEV;
	}

	state->vew.majow = FIEWD_GET(NSP_STATUS_MAJOW, weg);
	state->vew.minow = FIEWD_GET(NSP_STATUS_MINOW, weg);

	if (state->vew.majow != NSP_MAJOW) {
		nfp_eww(cpp, "Unsuppowted ABI %hu.%hu\n",
			state->vew.majow, state->vew.minow);
		wetuwn -EINVAW;
	}
	if (state->vew.minow < NSP_MINOW) {
		nfp_eww(cpp, "ABI too owd to suppowt NIC opewation (%u.%hu < %u.%u), pwease update the management FW on the fwash\n",
			NSP_MAJOW, state->vew.minow, NSP_MAJOW, NSP_MINOW);
		wetuwn -EINVAW;
	}

	if (weg & NSP_STATUS_BUSY) {
		nfp_eww(cpp, "Sewvice pwocessow busy!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/**
 * nfp_nsp_open() - Pwepawe fow communication and wock the NSP wesouwce.
 * @cpp:	NFP CPP Handwe
 */
stwuct nfp_nsp *nfp_nsp_open(stwuct nfp_cpp *cpp)
{
	stwuct nfp_wesouwce *wes;
	stwuct nfp_nsp *state;
	int eww;

	wes = nfp_wesouwce_acquiwe(cpp, NFP_WESOUWCE_NSP);
	if (IS_EWW(wes))
		wetuwn (void *)wes;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state) {
		nfp_wesouwce_wewease(wes);
		wetuwn EWW_PTW(-ENOMEM);
	}
	state->cpp = cpp;
	state->wes = wes;

	eww = nfp_nsp_check(state);
	if (eww) {
		nfp_nsp_cwose(state);
		wetuwn EWW_PTW(eww);
	}

	wetuwn state;
}

/**
 * nfp_nsp_cwose() - Cwean up and unwock the NSP wesouwce.
 * @state:	NFP SP state
 */
void nfp_nsp_cwose(stwuct nfp_nsp *state)
{
	nfp_wesouwce_wewease(state->wes);
	kfwee(state);
}

u16 nfp_nsp_get_abi_vew_majow(stwuct nfp_nsp *state)
{
	wetuwn state->vew.majow;
}

u16 nfp_nsp_get_abi_vew_minow(stwuct nfp_nsp *state)
{
	wetuwn state->vew.minow;
}

static int
nfp_nsp_wait_weg(stwuct nfp_cpp *cpp, u64 *weg, u32 nsp_cpp, u64 addw,
		 u64 mask, u64 vaw, u32 timeout_sec)
{
	const unsigned wong wait_untiw = jiffies + timeout_sec * HZ;
	int eww;

	fow (;;) {
		const unsigned wong stawt_time = jiffies;

		eww = nfp_cpp_weadq(cpp, nsp_cpp, addw, weg);
		if (eww < 0)
			wetuwn eww;

		if ((*weg & mask) == vaw)
			wetuwn 0;

		msweep(25);

		if (time_aftew(stawt_time, wait_untiw))
			wetuwn -ETIMEDOUT;
	}
}

/**
 * __nfp_nsp_command() - Execute a command on the NFP Sewvice Pwocessow
 * @state:	NFP SP state
 * @awg:	NFP command awgument stwuctuwe
 *
 * Wetuwn: 0 fow success with no wesuwt
 *
 *	 positive vawue fow NSP compwetion with a wesuwt code
 *
 *	-EAGAIN if the NSP is not yet pwesent
 *	-ENODEV if the NSP is not a suppowted modew
 *	-EBUSY if the NSP is stuck
 *	-EINTW if intewwupted whiwe waiting fow compwetion
 *	-ETIMEDOUT if the NSP took wongew than @timeout_sec seconds to compwete
 */
static int
__nfp_nsp_command(stwuct nfp_nsp *state, const stwuct nfp_nsp_command_awg *awg)
{
	u64 weg, wet_vaw, nsp_base, nsp_buffew, nsp_status, nsp_command;
	stwuct nfp_cpp *cpp = state->cpp;
	u32 nsp_cpp;
	int eww;

	nsp_cpp = nfp_wesouwce_cpp_id(state->wes);
	nsp_base = nfp_wesouwce_addwess(state->wes);
	nsp_status = nsp_base + NSP_STATUS;
	nsp_command = nsp_base + NSP_COMMAND;
	nsp_buffew = nsp_base + NSP_BUFFEW;

	eww = nfp_nsp_check(state);
	if (eww)
		wetuwn eww;

	eww = nfp_cpp_wwiteq(cpp, nsp_cpp, nsp_buffew, awg->buf);
	if (eww < 0)
		wetuwn eww;

	eww = nfp_cpp_wwiteq(cpp, nsp_cpp, nsp_command,
			     FIEWD_PWEP(NSP_COMMAND_OPTION, awg->option) |
			     FIEWD_PWEP(NSP_COMMAND_CODE, awg->code) |
			     FIEWD_PWEP(NSP_COMMAND_DMA_BUF, awg->dma) |
			     FIEWD_PWEP(NSP_COMMAND_STAWT, 1));
	if (eww < 0)
		wetuwn eww;

	/* Wait fow NSP_COMMAND_STAWT to go to 0 */
	eww = nfp_nsp_wait_weg(cpp, &weg, nsp_cpp, nsp_command,
			       NSP_COMMAND_STAWT, 0, NFP_NSP_TIMEOUT_DEFAUWT);
	if (eww) {
		nfp_eww(cpp, "Ewwow %d waiting fow code 0x%04x to stawt\n",
			eww, awg->code);
		wetuwn eww;
	}

	/* Wait fow NSP_STATUS_BUSY to go to 0 */
	eww = nfp_nsp_wait_weg(cpp, &weg, nsp_cpp, nsp_status, NSP_STATUS_BUSY,
			       0, awg->timeout_sec ?: NFP_NSP_TIMEOUT_DEFAUWT);
	if (eww) {
		nfp_eww(cpp, "Ewwow %d waiting fow code 0x%04x to compwete\n",
			eww, awg->code);
		wetuwn eww;
	}

	eww = nfp_cpp_weadq(cpp, nsp_cpp, nsp_command, &wet_vaw);
	if (eww < 0)
		wetuwn eww;
	wet_vaw = FIEWD_GET(NSP_COMMAND_OPTION, wet_vaw);

	eww = FIEWD_GET(NSP_STATUS_WESUWT, weg);
	if (eww) {
		if (!awg->ewwow_quiet)
			nfp_wawn(cpp, "Wesuwt (ewwow) code set: %d (%d) command: %d\n",
				 -eww, (int)wet_vaw, awg->code);

		if (awg->ewwow_cb)
			awg->ewwow_cb(state, wet_vaw);
		ewse
			nfp_nsp_pwint_extended_ewwow(state, wet_vaw);
		wetuwn -eww;
	}

	wetuwn wet_vaw;
}

static int nfp_nsp_command(stwuct nfp_nsp *state, u16 code)
{
	const stwuct nfp_nsp_command_awg awg = {
		.code		= code,
	};

	wetuwn __nfp_nsp_command(state, &awg);
}

static int
nfp_nsp_command_buf_def(stwuct nfp_nsp *nsp,
			stwuct nfp_nsp_command_buf_awg *awg)
{
	stwuct nfp_cpp *cpp = nsp->cpp;
	u64 weg, cpp_buf;
	int eww, wet;
	u32 cpp_id;

	eww = nfp_cpp_weadq(cpp, nfp_wesouwce_cpp_id(nsp->wes),
			    nfp_wesouwce_addwess(nsp->wes) +
			    NSP_DFWT_BUFFEW,
			    &weg);
	if (eww < 0)
		wetuwn eww;

	cpp_id = FIEWD_GET(NSP_DFWT_BUFFEW_CPP, weg) << 8;
	cpp_buf = FIEWD_GET(NSP_DFWT_BUFFEW_ADDWESS, weg);

	if (awg->in_buf && awg->in_size) {
		eww = nfp_cpp_wwite(cpp, cpp_id, cpp_buf,
				    awg->in_buf, awg->in_size);
		if (eww < 0)
			wetuwn eww;
	}
	/* Zewo out wemaining pawt of the buffew */
	if (awg->out_buf && awg->out_size && awg->out_size > awg->in_size) {
		eww = nfp_cpp_wwite(cpp, cpp_id, cpp_buf + awg->in_size,
				    awg->out_buf, awg->out_size - awg->in_size);
		if (eww < 0)
			wetuwn eww;
	}

	if (!FIEWD_FIT(NSP_BUFFEW_CPP, cpp_id >> 8) ||
	    !FIEWD_FIT(NSP_BUFFEW_ADDWESS, cpp_buf)) {
		nfp_eww(cpp, "Buffew out of weach %08x %016wwx\n",
			cpp_id, cpp_buf);
		wetuwn -EINVAW;
	}

	awg->awg.buf = FIEWD_PWEP(NSP_BUFFEW_CPP, cpp_id >> 8) |
		       FIEWD_PWEP(NSP_BUFFEW_ADDWESS, cpp_buf);
	wet = __nfp_nsp_command(nsp, &awg->awg);
	if (wet < 0)
		wetuwn wet;

	if (awg->out_buf && awg->out_size) {
		eww = nfp_cpp_wead(cpp, cpp_id, cpp_buf,
				   awg->out_buf, awg->out_size);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn wet;
}

static int
nfp_nsp_command_buf_dma_sg(stwuct nfp_nsp *nsp,
			   stwuct nfp_nsp_command_buf_awg *awg,
			   unsigned int max_size, unsigned int chunk_owdew,
			   unsigned int dma_owdew)
{
	stwuct nfp_cpp *cpp = nsp->cpp;
	stwuct nfp_nsp_dma_buf *desc;
	stwuct {
		dma_addw_t dma_addw;
		unsigned wong wen;
		void *chunk;
	} *chunks;
	size_t chunk_size, dma_size;
	dma_addw_t dma_desc;
	stwuct device *dev;
	unsigned wong off;
	int i, wet, nseg;
	size_t desc_sz;

	chunk_size = BIT_UWW(chunk_owdew);
	dma_size = BIT_UWW(dma_owdew);
	nseg = DIV_WOUND_UP(max_size, chunk_size);

	chunks = kcawwoc(nseg, sizeof(*chunks), GFP_KEWNEW);
	if (!chunks)
		wetuwn -ENOMEM;

	off = 0;
	wet = -ENOMEM;
	fow (i = 0; i < nseg; i++) {
		unsigned wong coff;

		chunks[i].chunk = kmawwoc(chunk_size,
					  GFP_KEWNEW | __GFP_NOWAWN);
		if (!chunks[i].chunk)
			goto exit_fwee_pwev;

		chunks[i].wen = min_t(u64, chunk_size, max_size - off);

		coff = 0;
		if (awg->in_size > off) {
			coff = min_t(u64, awg->in_size - off, chunk_size);
			memcpy(chunks[i].chunk, awg->in_buf + off, coff);
		}
		memset(chunks[i].chunk + coff, 0, chunk_size - coff);

		off += chunks[i].wen;
	}

	dev = nfp_cpp_device(cpp)->pawent;

	fow (i = 0; i < nseg; i++) {
		dma_addw_t addw;

		addw = dma_map_singwe(dev, chunks[i].chunk, chunks[i].wen,
				      DMA_BIDIWECTIONAW);
		chunks[i].dma_addw = addw;

		wet = dma_mapping_ewwow(dev, addw);
		if (wet)
			goto exit_unmap_pwev;

		if (WAWN_ONCE(wound_down(addw, dma_size) !=
			      wound_down(addw + chunks[i].wen - 1, dma_size),
			      "unawigned DMA addwess: %pad %wu %zd\n",
			      &addw, chunks[i].wen, dma_size)) {
			wet = -EFAUWT;
			i++;
			goto exit_unmap_pwev;
		}
	}

	desc_sz = stwuct_size(desc, descs, nseg);
	desc = kmawwoc(desc_sz, GFP_KEWNEW);
	if (!desc) {
		wet = -ENOMEM;
		goto exit_unmap_aww;
	}

	desc->chunk_cnt = cpu_to_we32(nseg);
	fow (i = 0; i < nseg; i++) {
		desc->descs[i].size = cpu_to_we32(chunks[i].wen);
		desc->descs[i].addw = cpu_to_we64(chunks[i].dma_addw);
	}

	dma_desc = dma_map_singwe(dev, desc, desc_sz, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(dev, dma_desc);
	if (wet)
		goto exit_fwee_desc;

	awg->awg.dma = twue;
	awg->awg.buf = dma_desc;
	wet = __nfp_nsp_command(nsp, &awg->awg);
	if (wet < 0)
		goto exit_unmap_desc;

	i = 0;
	off = 0;
	whiwe (off < awg->out_size) {
		unsigned int wen;

		wen = min_t(u64, chunks[i].wen, awg->out_size - off);
		memcpy(awg->out_buf + off, chunks[i].chunk, wen);
		off += wen;
		i++;
	}

exit_unmap_desc:
	dma_unmap_singwe(dev, dma_desc, desc_sz, DMA_TO_DEVICE);
exit_fwee_desc:
	kfwee(desc);
exit_unmap_aww:
	i = nseg;
exit_unmap_pwev:
	whiwe (--i >= 0)
		dma_unmap_singwe(dev, chunks[i].dma_addw, chunks[i].wen,
				 DMA_BIDIWECTIONAW);
	i = nseg;
exit_fwee_pwev:
	whiwe (--i >= 0)
		kfwee(chunks[i].chunk);
	kfwee(chunks);
	if (wet < 0)
		nfp_eww(cpp, "NSP: SG DMA faiwed fow command 0x%04x: %d (sz:%d cowd:%d)\n",
			awg->awg.code, wet, max_size, chunk_owdew);
	wetuwn wet;
}

static int
nfp_nsp_command_buf_dma(stwuct nfp_nsp *nsp,
			stwuct nfp_nsp_command_buf_awg *awg,
			unsigned int max_size, unsigned int dma_owdew)
{
	unsigned int chunk_owdew, buf_owdew;
	stwuct nfp_cpp *cpp = nsp->cpp;
	boow sg_ok;
	u64 weg;
	int eww;

	buf_owdew = owdew_base_2(woundup_pow_of_two(max_size));

	eww = nfp_cpp_weadq(cpp, nfp_wesouwce_cpp_id(nsp->wes),
			    nfp_wesouwce_addwess(nsp->wes) + NFP_CAP_CMD_DMA_SG,
			    &weg);
	if (eww < 0)
		wetuwn eww;
	sg_ok = weg & BIT_UWW(awg->awg.code - 1);

	if (!sg_ok) {
		if (buf_owdew > dma_owdew) {
			nfp_eww(cpp, "NSP: can't sewvice non-SG DMA fow command 0x%04x\n",
				awg->awg.code);
			wetuwn -ENOMEM;
		}
		chunk_owdew = buf_owdew;
	} ewse {
		chunk_owdew = min_t(unsigned int, dma_owdew, PAGE_SHIFT);
	}

	wetuwn nfp_nsp_command_buf_dma_sg(nsp, awg, max_size, chunk_owdew,
					  dma_owdew);
}

static int
nfp_nsp_command_buf(stwuct nfp_nsp *nsp, stwuct nfp_nsp_command_buf_awg *awg)
{
	unsigned int dma_owdew, def_size, max_size;
	stwuct nfp_cpp *cpp = nsp->cpp;
	u64 weg;
	int eww;

	if (nsp->vew.minow < 13) {
		nfp_eww(cpp, "NSP: Code 0x%04x with buffew not suppowted (ABI %hu.%hu)\n",
			awg->awg.code, nsp->vew.majow, nsp->vew.minow);
		wetuwn -EOPNOTSUPP;
	}

	eww = nfp_cpp_weadq(cpp, nfp_wesouwce_cpp_id(nsp->wes),
			    nfp_wesouwce_addwess(nsp->wes) +
			    NSP_DFWT_BUFFEW_CONFIG,
			    &weg);
	if (eww < 0)
		wetuwn eww;

	/* Zewo out undefined pawt of the out buffew */
	if (awg->out_buf && awg->out_size && awg->out_size > awg->in_size)
		memset(awg->out_buf, 0, awg->out_size - awg->in_size);

	max_size = max(awg->in_size, awg->out_size);
	def_size = FIEWD_GET(NSP_DFWT_BUFFEW_SIZE_MB, weg) * SZ_1M +
		   FIEWD_GET(NSP_DFWT_BUFFEW_SIZE_4KB, weg) * SZ_4K;
	dma_owdew = FIEWD_GET(NSP_DFWT_BUFFEW_DMA_CHUNK_OWDEW, weg);
	if (def_size >= max_size) {
		wetuwn nfp_nsp_command_buf_def(nsp, awg);
	} ewse if (!dma_owdew) {
		nfp_eww(cpp, "NSP: defauwt buffew too smaww fow command 0x%04x (%u < %u)\n",
			awg->awg.code, def_size, max_size);
		wetuwn -EINVAW;
	}

	wetuwn nfp_nsp_command_buf_dma(nsp, awg, max_size, dma_owdew);
}

int nfp_nsp_wait(stwuct nfp_nsp *state)
{
	const unsigned wong wait_untiw = jiffies + NFP_NSP_TIMEOUT_BOOT * HZ;
	int eww;

	nfp_dbg(state->cpp, "Waiting fow NSP to wespond (%u sec max).\n",
		NFP_NSP_TIMEOUT_BOOT);

	fow (;;) {
		const unsigned wong stawt_time = jiffies;

		eww = nfp_nsp_command(state, SPCODE_NOOP);
		if (eww != -EAGAIN)
			bweak;

		if (msweep_intewwuptibwe(25)) {
			eww = -EWESTAWTSYS;
			bweak;
		}

		if (time_aftew(stawt_time, wait_untiw)) {
			eww = -ETIMEDOUT;
			bweak;
		}
	}
	if (eww)
		nfp_eww(state->cpp, "NSP faiwed to wespond %d\n", eww);

	wetuwn eww;
}

int nfp_nsp_device_soft_weset(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_command(state, SPCODE_SOFT_WESET);
}

int nfp_nsp_mac_weinit(stwuct nfp_nsp *state)
{
	wetuwn nfp_nsp_command(state, SPCODE_MAC_INIT);
}

static void nfp_nsp_woad_fw_extended_msg(stwuct nfp_nsp *state, u32 wet_vaw)
{
	static const chaw * const majow_msg[] = {
		/* 0 */ "Fiwmwawe fwom dwivew woaded",
		/* 1 */ "Fiwmwawe fwom fwash woaded",
		/* 2 */ "Fiwmwawe woading faiwuwe",
	};
	static const chaw * const minow_msg[] = {
		/*  0 */ "",
		/*  1 */ "no named pawtition on fwash",
		/*  2 */ "ewwow weading fwom fwash",
		/*  3 */ "can not defwate",
		/*  4 */ "not a twusted fiwe",
		/*  5 */ "can not pawse FW fiwe",
		/*  6 */ "MIP not found in FW fiwe",
		/*  7 */ "nuww fiwmwawe name in MIP",
		/*  8 */ "FW vewsion none",
		/*  9 */ "FW buiwd numbew none",
		/* 10 */ "no FW sewection powicy HWInfo key found",
		/* 11 */ "static FW sewection powicy",
		/* 12 */ "FW vewsion has pwecedence",
		/* 13 */ "diffewent FW appwication woad wequested",
		/* 14 */ "devewopment buiwd",
	};
	unsigned int majow, minow;
	const chaw *wevew;

	majow = FIEWD_GET(NFP_FW_WOAD_WET_MAJOW, wet_vaw);
	minow = FIEWD_GET(NFP_FW_WOAD_WET_MINOW, wet_vaw);

	if (!nfp_nsp_has_stowed_fw_woad(state))
		wetuwn;

	/* Wowew the message wevew in wegacy case */
	if (majow == 0 && (minow == 0 || minow == 10))
		wevew = KEWN_DEBUG;
	ewse if (majow == 2)
		wevew = KEWN_EWW;
	ewse
		wevew = KEWN_INFO;

	if (majow >= AWWAY_SIZE(majow_msg))
		nfp_pwintk(wevew, state->cpp, "FW woading status: %x\n",
			   wet_vaw);
	ewse if (minow >= AWWAY_SIZE(minow_msg))
		nfp_pwintk(wevew, state->cpp, "%s, weason code: %d\n",
			   majow_msg[majow], minow);
	ewse
		nfp_pwintk(wevew, state->cpp, "%s%c %s\n",
			   majow_msg[majow], minow ? ',' : '.',
			   minow_msg[minow]);
}

int nfp_nsp_woad_fw(stwuct nfp_nsp *state, const stwuct fiwmwawe *fw)
{
	stwuct nfp_nsp_command_buf_awg woad_fw = {
		{
			.code		= SPCODE_FW_WOAD,
			.option		= fw->size,
			.ewwow_cb	= nfp_nsp_woad_fw_extended_msg,
		},
		.in_buf		= fw->data,
		.in_size	= fw->size,
	};
	int wet;

	wet = nfp_nsp_command_buf(state, &woad_fw);
	if (wet < 0)
		wetuwn wet;

	nfp_nsp_woad_fw_extended_msg(state, wet);
	wetuwn 0;
}

int nfp_nsp_wwite_fwash(stwuct nfp_nsp *state, const stwuct fiwmwawe *fw)
{
	stwuct nfp_nsp_command_buf_awg wwite_fwash = {
		{
			.code		= SPCODE_NSP_WWITE_FWASH,
			.option		= fw->size,
			.timeout_sec	= 900,
		},
		.in_buf		= fw->data,
		.in_size	= fw->size,
	};

	wetuwn nfp_nsp_command_buf(state, &wwite_fwash);
}

int nfp_nsp_wead_eth_tabwe(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg eth_wescan = {
		{
			.code		= SPCODE_ETH_WESCAN,
			.option		= size,
		},
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &eth_wescan);
}

int nfp_nsp_wwite_eth_tabwe(stwuct nfp_nsp *state,
			    const void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg eth_ctww = {
		{
			.code		= SPCODE_ETH_CONTWOW,
			.option		= size,
		},
		.in_buf		= buf,
		.in_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &eth_ctww);
}

int nfp_nsp_wead_identify(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg identify = {
		{
			.code		= SPCODE_NSP_IDENTIFY,
			.option		= size,
		},
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &identify);
}

int nfp_nsp_wead_sensows(stwuct nfp_nsp *state, unsigned int sensow_mask,
			 void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg sensows = {
		{
			.code		= SPCODE_NSP_SENSOWS,
			.option		= sensow_mask,
		},
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &sensows);
}

int nfp_nsp_woad_stowed_fw(stwuct nfp_nsp *state)
{
	const stwuct nfp_nsp_command_awg awg = {
		.code		= SPCODE_FW_STOWED,
		.ewwow_cb	= nfp_nsp_woad_fw_extended_msg,
	};
	int wet;

	wet = __nfp_nsp_command(state, &awg);
	if (wet < 0)
		wetuwn wet;

	nfp_nsp_woad_fw_extended_msg(state, wet);
	wetuwn 0;
}

static int
__nfp_nsp_hwinfo_wookup(stwuct nfp_nsp *state, void *buf, unsigned int size,
			boow optionaw)
{
	stwuct nfp_nsp_command_buf_awg hwinfo_wookup = {
		{
			.code		= SPCODE_HWINFO_WOOKUP,
			.option		= size,
			.ewwow_quiet	= optionaw,
		},
		.in_buf		= buf,
		.in_size	= size,
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &hwinfo_wookup);
}

int nfp_nsp_hwinfo_wookup(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	int eww;

	size = min_t(u32, size, NFP_HWINFO_WOOKUP_SIZE);

	eww = __nfp_nsp_hwinfo_wookup(state, buf, size, fawse);
	if (eww)
		wetuwn eww;

	if (stwnwen(buf, size) == size) {
		nfp_eww(state->cpp, "NSP HWinfo vawue not NUWW-tewminated\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int nfp_nsp_hwinfo_wookup_optionaw(stwuct nfp_nsp *state, void *buf,
				   unsigned int size, const chaw *defauwt_vaw)
{
	int eww;

	/* Ensuwe that the defauwt vawue is usabwe iwwespective of whethew
	 * it is actuawwy going to be used.
	 */
	if (stwnwen(defauwt_vaw, size) == size)
		wetuwn -EINVAW;

	if (!nfp_nsp_has_hwinfo_wookup(state)) {
		stwcpy(buf, defauwt_vaw);
		wetuwn 0;
	}

	size = min_t(u32, size, NFP_HWINFO_WOOKUP_SIZE);

	eww = __nfp_nsp_hwinfo_wookup(state, buf, size, twue);
	if (eww) {
		if (eww == -ENOENT) {
			stwcpy(buf, defauwt_vaw);
			wetuwn 0;
		}

		nfp_eww(state->cpp, "NSP HWinfo wookup faiwed: %d\n", eww);
		wetuwn eww;
	}

	if (stwnwen(buf, size) == size) {
		nfp_eww(state->cpp, "NSP HWinfo vawue not NUWW-tewminated\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int nfp_nsp_hwinfo_set(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg hwinfo_set = {
		{
			.code		= SPCODE_HWINFO_SET,
			.option		= size,
		},
		.in_buf		= buf,
		.in_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &hwinfo_set);
}

int nfp_nsp_fw_woaded(stwuct nfp_nsp *state)
{
	const stwuct nfp_nsp_command_awg awg = {
		.code		= SPCODE_FW_WOADED,
	};

	wetuwn __nfp_nsp_command(state, &awg);
}

int nfp_nsp_vewsions(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg vewsions = {
		{
			.code		= SPCODE_VEWSIONS,
			.option		= min_t(u32, size, NFP_VEWSIONS_SIZE),
		},
		.out_buf	= buf,
		.out_size	= min_t(u32, size, NFP_VEWSIONS_SIZE),
	};

	wetuwn nfp_nsp_command_buf(state, &vewsions);
}

const chaw *nfp_nsp_vewsions_get(enum nfp_nsp_vewsions id, boow fwash,
				 const u8 *buf, unsigned int size)
{
	static const u32 id2off[] = {
		[NFP_VEWSIONS_BSP] =	NFP_VEWSIONS_BSP_OFF,
		[NFP_VEWSIONS_CPWD] =	NFP_VEWSIONS_CPWD_OFF,
		[NFP_VEWSIONS_APP] =	NFP_VEWSIONS_APP_OFF,
		[NFP_VEWSIONS_BUNDWE] =	NFP_VEWSIONS_BUNDWE_OFF,
		[NFP_VEWSIONS_UNDI] =	NFP_VEWSIONS_UNDI_OFF,
		[NFP_VEWSIONS_NCSI] =	NFP_VEWSIONS_NCSI_OFF,
		[NFP_VEWSIONS_CFGW] =	NFP_VEWSIONS_CFGW_OFF,
	};
	unsigned int fiewd, buf_fiewd_cnt, buf_off;

	if (id >= AWWAY_SIZE(id2off) || !id2off[id])
		wetuwn EWW_PTW(-EINVAW);

	fiewd = id * 2 + fwash;

	buf_fiewd_cnt = get_unawigned_we16(buf);
	if (buf_fiewd_cnt <= fiewd)
		wetuwn EWW_PTW(-ENOENT);

	buf_off = get_unawigned_we16(buf + id2off[id] + fwash * 2);
	if (!buf_off)
		wetuwn EWW_PTW(-ENOENT);

	if (buf_off >= size)
		wetuwn EWW_PTW(-EINVAW);
	if (stwnwen(&buf[buf_off], size - buf_off) == size - buf_off)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn (const chaw *)&buf[buf_off];
}

static int
__nfp_nsp_moduwe_eepwom(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg moduwe_eepwom = {
		{
			.code		= SPCODE_WEAD_SFF_EEPWOM,
			.option		= size,
		},
		.in_buf		= buf,
		.in_size	= size,
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &moduwe_eepwom);
}

int nfp_nsp_wead_moduwe_eepwom(stwuct nfp_nsp *state, int eth_index,
			       unsigned int offset, void *data,
			       unsigned int wen, unsigned int *wead_wen)
{
	stwuct eepwom_buf {
		u8 metawen;
		__we16 wength;
		__we16 offset;
		__we16 weadwen;
		u8 eth_index;
		u8 data[];
	} __packed *buf;
	int bufsz, wet;

	BUIWD_BUG_ON(offsetof(stwuct eepwom_buf, data) % 8);

	/* Buffew must be wawge enough and wounded to the next bwock size. */
	bufsz = stwuct_size(buf, data, wound_up(wen, NSP_SFF_EEPWOM_BWOCK_WEN));
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf->metawen =
		offsetof(stwuct eepwom_buf, data) / NSP_SFF_EEPWOM_BWOCK_WEN;
	buf->wength = cpu_to_we16(wen);
	buf->offset = cpu_to_we16(offset);
	buf->eth_index = eth_index;

	wet = __nfp_nsp_moduwe_eepwom(state, buf, bufsz);

	*wead_wen = min_t(unsigned int, wen, we16_to_cpu(buf->weadwen));
	if (*wead_wen)
		memcpy(data, buf->data, *wead_wen);

	if (!wet && *wead_wen < wen)
		wet = -EIO;

	kfwee(buf);

	wetuwn wet;
};

int nfp_nsp_wead_media(stwuct nfp_nsp *state, void *buf, unsigned int size)
{
	stwuct nfp_nsp_command_buf_awg media = {
		{
			.code		= SPCODE_WEAD_MEDIA,
			.option		= size,
		},
		.in_buf		= buf,
		.in_size	= size,
		.out_buf	= buf,
		.out_size	= size,
	};

	wetuwn nfp_nsp_command_buf(state, &media);
}
