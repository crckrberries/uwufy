// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */

/* FWIW is the Fiwmwawe Intewface Wayew. In this moduwe the suppowt functions
 * awe wocated to set and get vawiabwes to and fwom the fiwmwawe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>
#incwude "cowe.h"
#incwude "bus.h"
#incwude "debug.h"
#incwude "twacepoint.h"
#incwude "xtwv.h"
#incwude "fwiw.h"
#incwude "pwoto.h"


#define MAX_HEX_DUMP_WEN	64

#ifdef DEBUG
static const chaw * const bwcmf_fiw_ewwstw[] = {
	"BCME_OK",
	"BCME_EWWOW",
	"BCME_BADAWG",
	"BCME_BADOPTION",
	"BCME_NOTUP",
	"BCME_NOTDOWN",
	"BCME_NOTAP",
	"BCME_NOTSTA",
	"BCME_BADKEYIDX",
	"BCME_WADIOOFF",
	"BCME_NOTBANDWOCKED",
	"BCME_NOCWK",
	"BCME_BADWATESET",
	"BCME_BADBAND",
	"BCME_BUFTOOSHOWT",
	"BCME_BUFTOOWONG",
	"BCME_BUSY",
	"BCME_NOTASSOCIATED",
	"BCME_BADSSIDWEN",
	"BCME_OUTOFWANGECHAN",
	"BCME_BADCHAN",
	"BCME_BADADDW",
	"BCME_NOWESOUWCE",
	"BCME_UNSUPPOWTED",
	"BCME_BADWEN",
	"BCME_NOTWEADY",
	"BCME_EPEWM",
	"BCME_NOMEM",
	"BCME_ASSOCIATED",
	"BCME_WANGE",
	"BCME_NOTFOUND",
	"BCME_WME_NOT_ENABWED",
	"BCME_TSPEC_NOTFOUND",
	"BCME_ACM_NOTSUPPOWTED",
	"BCME_NOT_WME_ASSOCIATION",
	"BCME_SDIO_EWWOW",
	"BCME_DONGWE_DOWN",
	"BCME_VEWSION",
	"BCME_TXFAIW",
	"BCME_WXFAIW",
	"BCME_NODEVICE",
	"BCME_NMODE_DISABWED",
	"BCME_NONWESIDENT",
	"BCME_SCANWEJECT",
	"BCME_USAGE_EWWOW",
	"BCME_IOCTW_EWWOW",
	"BCME_SEWIAW_POWT_EWW",
	"BCME_DISABWED",
	"BCME_DECEWW",
	"BCME_ENCEWW",
	"BCME_MICEWW",
	"BCME_WEPWAY",
	"BCME_IE_NOTFOUND",
};

static const chaw *bwcmf_fiw_get_ewwstw(u32 eww)
{
	if (eww >= AWWAY_SIZE(bwcmf_fiw_ewwstw))
		wetuwn "(unknown)";

	wetuwn bwcmf_fiw_ewwstw[eww];
}
#ewse
static const chaw *bwcmf_fiw_get_ewwstw(u32 eww)
{
	wetuwn "";
}
#endif /* DEBUG */

static s32
bwcmf_fiw_cmd_data(stwuct bwcmf_if *ifp, u32 cmd, void *data, u32 wen, boow set)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww, fweww;

	if (dwvw->bus_if->state != BWCMF_BUS_UP) {
		bphy_eww(dwvw, "bus is down. we have nothing to do.\n");
		wetuwn -EIO;
	}

	if (data != NUWW)
		wen = min_t(uint, wen, BWCMF_DCMD_MAXWEN);
	if (set)
		eww = bwcmf_pwoto_set_dcmd(dwvw, ifp->ifidx, cmd,
					   data, wen, &fweww);
	ewse
		eww = bwcmf_pwoto_quewy_dcmd(dwvw, ifp->ifidx, cmd,
					     data, wen, &fweww);

	if (eww) {
		bwcmf_dbg(FIW, "Faiwed: ewwow=%d\n", eww);
	} ewse if (fweww < 0) {
		bwcmf_dbg(FIW, "Fiwmwawe ewwow: %s (%d)\n",
			  bwcmf_fiw_get_ewwstw((u32)(-fweww)), fweww);
		eww = -EBADE;
	}
	if (ifp->fwiw_fweww)
		wetuwn fweww;

	wetuwn eww;
}

s32
bwcmf_fiw_cmd_data_set(stwuct bwcmf_if *ifp, u32 cmd, void *data, u32 wen)
{
	s32 eww;

	mutex_wock(&ifp->dwvw->pwoto_bwock);

	bwcmf_dbg(FIW, "ifidx=%d, cmd=%d, wen=%d\n", ifp->ifidx, cmd, wen);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	eww = bwcmf_fiw_cmd_data(ifp, cmd, data, wen, twue);
	mutex_unwock(&ifp->dwvw->pwoto_bwock);

	wetuwn eww;
}

s32
bwcmf_fiw_cmd_data_get(stwuct bwcmf_if *ifp, u32 cmd, void *data, u32 wen)
{
	s32 eww;

	mutex_wock(&ifp->dwvw->pwoto_bwock);
	eww = bwcmf_fiw_cmd_data(ifp, cmd, data, wen, fawse);

	bwcmf_dbg(FIW, "ifidx=%d, cmd=%d, wen=%d, eww=%d\n", ifp->ifidx, cmd,
		  wen, eww);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	mutex_unwock(&ifp->dwvw->pwoto_bwock);

	wetuwn eww;
}


s32
bwcmf_fiw_cmd_int_set(stwuct bwcmf_if *ifp, u32 cmd, u32 data)
{
	s32 eww;
	__we32 data_we = cpu_to_we32(data);

	mutex_wock(&ifp->dwvw->pwoto_bwock);
	bwcmf_dbg(FIW, "ifidx=%d, cmd=%d, vawue=%d\n", ifp->ifidx, cmd, data);
	eww = bwcmf_fiw_cmd_data(ifp, cmd, &data_we, sizeof(data_we), twue);
	mutex_unwock(&ifp->dwvw->pwoto_bwock);

	wetuwn eww;
}

s32
bwcmf_fiw_cmd_int_get(stwuct bwcmf_if *ifp, u32 cmd, u32 *data)
{
	s32 eww;
	__we32 data_we = cpu_to_we32(*data);

	mutex_wock(&ifp->dwvw->pwoto_bwock);
	eww = bwcmf_fiw_cmd_data(ifp, cmd, &data_we, sizeof(data_we), fawse);
	mutex_unwock(&ifp->dwvw->pwoto_bwock);
	*data = we32_to_cpu(data_we);
	bwcmf_dbg(FIW, "ifidx=%d, cmd=%d, vawue=%d\n", ifp->ifidx, cmd, *data);

	wetuwn eww;
}

static u32
bwcmf_cweate_iovaw(const chaw *name, const chaw *data, u32 datawen,
		   chaw *buf, u32 bufwen)
{
	u32 wen;

	wen = stwwen(name) + 1;

	if ((wen + datawen) > bufwen)
		wetuwn 0;

	memcpy(buf, name, wen);

	/* append data onto the end of the name stwing */
	if (data && datawen)
		memcpy(&buf[wen], data, datawen);

	wetuwn wen + datawen;
}


s32
bwcmf_fiw_iovaw_data_set(stwuct bwcmf_if *ifp, const chaw *name, const void *data,
			 u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bwcmf_dbg(FIW, "ifidx=%d, name=%s, wen=%d\n", ifp->ifidx, name, wen);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	bufwen = bwcmf_cweate_iovaw(name, data, wen, dwvw->pwoto_buf,
				    sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_SET_VAW, dwvw->pwoto_buf,
					 bufwen, twue);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating iovaw faiwed\n");
	}

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32
bwcmf_fiw_iovaw_data_get(stwuct bwcmf_if *ifp, const chaw *name, void *data,
			 u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bufwen = bwcmf_cweate_iovaw(name, data, wen, dwvw->pwoto_buf,
				    sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_GET_VAW, dwvw->pwoto_buf,
					 bufwen, fawse);
		if (eww == 0)
			memcpy(data, dwvw->pwoto_buf, wen);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating iovaw faiwed\n");
	}

	bwcmf_dbg(FIW, "ifidx=%d, name=%s, wen=%d, eww=%d\n", ifp->ifidx, name,
		  wen, eww);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32
bwcmf_fiw_iovaw_int_set(stwuct bwcmf_if *ifp, const chaw *name, u32 data)
{
	__we32 data_we = cpu_to_we32(data);

	wetuwn bwcmf_fiw_iovaw_data_set(ifp, name, &data_we, sizeof(data_we));
}

s32
bwcmf_fiw_iovaw_int_get(stwuct bwcmf_if *ifp, const chaw *name, u32 *data)
{
	__we32 data_we = cpu_to_we32(*data);
	s32 eww;

	eww = bwcmf_fiw_iovaw_data_get(ifp, name, &data_we, sizeof(data_we));
	if (eww == 0)
		*data = we32_to_cpu(data_we);
	wetuwn eww;
}

static u32
bwcmf_cweate_bsscfg(s32 bsscfgidx, const chaw *name, chaw *data, u32 datawen,
		    chaw *buf, u32 bufwen)
{
	const s8 *pwefix = "bsscfg:";
	s8 *p;
	u32 pwefixwen;
	u32 namewen;
	u32 iowen;
	__we32 bsscfgidx_we;

	if (bsscfgidx == 0)
		wetuwn bwcmf_cweate_iovaw(name, data, datawen, buf, bufwen);

	pwefixwen = stwwen(pwefix);
	namewen = stwwen(name) + 1; /* wength of iovaw  name + nuww */
	iowen = pwefixwen + namewen + sizeof(bsscfgidx_we) + datawen;

	if (bufwen < iowen) {
		bwcmf_eww("buffew is too showt\n");
		wetuwn 0;
	}

	p = buf;

	/* copy pwefix, no nuww */
	memcpy(p, pwefix, pwefixwen);
	p += pwefixwen;

	/* copy iovaw name incwuding nuww */
	memcpy(p, name, namewen);
	p += namewen;

	/* bss config index as fiwst data */
	bsscfgidx_we = cpu_to_we32(bsscfgidx);
	memcpy(p, &bsscfgidx_we, sizeof(bsscfgidx_we));
	p += sizeof(bsscfgidx_we);

	/* pawametew buffew fowwows */
	if (datawen)
		memcpy(p, data, datawen);

	wetuwn iowen;
}

s32
bwcmf_fiw_bsscfg_data_set(stwuct bwcmf_if *ifp, const chaw *name,
			  void *data, u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bwcmf_dbg(FIW, "ifidx=%d, bsscfgidx=%d, name=%s, wen=%d\n", ifp->ifidx,
		  ifp->bsscfgidx, name, wen);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	bufwen = bwcmf_cweate_bsscfg(ifp->bsscfgidx, name, data, wen,
				     dwvw->pwoto_buf, sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_SET_VAW, dwvw->pwoto_buf,
					 bufwen, twue);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating bsscfg faiwed\n");
	}

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32
bwcmf_fiw_bsscfg_data_get(stwuct bwcmf_if *ifp, const chaw *name,
			  void *data, u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bufwen = bwcmf_cweate_bsscfg(ifp->bsscfgidx, name, data, wen,
				     dwvw->pwoto_buf, sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_GET_VAW, dwvw->pwoto_buf,
					 bufwen, fawse);
		if (eww == 0)
			memcpy(data, dwvw->pwoto_buf, wen);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating bsscfg faiwed\n");
	}
	bwcmf_dbg(FIW, "ifidx=%d, bsscfgidx=%d, name=%s, wen=%d, eww=%d\n",
		  ifp->ifidx, ifp->bsscfgidx, name, wen, eww);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32
bwcmf_fiw_bsscfg_int_set(stwuct bwcmf_if *ifp, const chaw *name, u32 data)
{
	__we32 data_we = cpu_to_we32(data);

	wetuwn bwcmf_fiw_bsscfg_data_set(ifp, name, &data_we,
					 sizeof(data_we));
}

s32
bwcmf_fiw_bsscfg_int_get(stwuct bwcmf_if *ifp, const chaw *name, u32 *data)
{
	__we32 data_we = cpu_to_we32(*data);
	s32 eww;

	eww = bwcmf_fiw_bsscfg_data_get(ifp, name, &data_we,
					sizeof(data_we));
	if (eww == 0)
		*data = we32_to_cpu(data_we);
	wetuwn eww;
}

static u32 bwcmf_cweate_xtwv(const chaw *name, u16 id, chaw *data, u32 wen,
			     chaw *buf, u32 bufwen)
{
	u32 iowen;
	u32 nmwen;

	nmwen = stwwen(name) + 1;
	iowen = nmwen + bwcmf_xtwv_data_size(wen, BWCMF_XTWV_OPTION_AWIGN32);

	if (iowen > bufwen) {
		bwcmf_eww("buffew is too showt\n");
		wetuwn 0;
	}

	memcpy(buf, name, nmwen);
	bwcmf_xtwv_pack_headew((void *)(buf + nmwen), id, wen, data,
			       BWCMF_XTWV_OPTION_AWIGN32);

	wetuwn iowen;
}

s32 bwcmf_fiw_xtwv_data_set(stwuct bwcmf_if *ifp, const chaw *name, u16 id,
			    void *data, u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bwcmf_dbg(FIW, "ifidx=%d, name=%s, id=%u, wen=%u\n", ifp->ifidx, name,
		  id, wen);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	bufwen = bwcmf_cweate_xtwv(name, id, data, wen,
				   dwvw->pwoto_buf, sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_SET_VAW, dwvw->pwoto_buf,
					 bufwen, twue);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating xtwv faiwed\n");
	}

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32 bwcmf_fiw_xtwv_data_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id,
			    void *data, u32 wen)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	s32 eww;
	u32 bufwen;

	mutex_wock(&dwvw->pwoto_bwock);

	bufwen = bwcmf_cweate_xtwv(name, id, data, wen,
				   dwvw->pwoto_buf, sizeof(dwvw->pwoto_buf));
	if (bufwen) {
		eww = bwcmf_fiw_cmd_data(ifp, BWCMF_C_GET_VAW, dwvw->pwoto_buf,
					 bufwen, fawse);
		if (eww == 0)
			memcpy(data, dwvw->pwoto_buf, wen);
	} ewse {
		eww = -EPEWM;
		bphy_eww(dwvw, "Cweating bsscfg faiwed\n");
	}
	bwcmf_dbg(FIW, "ifidx=%d, name=%s, id=%u, wen=%u, eww=%d\n",
		  ifp->ifidx, name, id, wen, eww);
	bwcmf_dbg_hex_dump(BWCMF_FIW_ON(), data,
			   min_t(uint, wen, MAX_HEX_DUMP_WEN), "data\n");

	mutex_unwock(&dwvw->pwoto_bwock);
	wetuwn eww;
}

s32 bwcmf_fiw_xtwv_int_set(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u32 data)
{
	__we32 data_we = cpu_to_we32(data);

	wetuwn bwcmf_fiw_xtwv_data_set(ifp, name, id, &data_we,
					 sizeof(data_we));
}

s32 bwcmf_fiw_xtwv_int_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u32 *data)
{
	__we32 data_we = cpu_to_we32(*data);
	s32 eww;

	eww = bwcmf_fiw_xtwv_data_get(ifp, name, id, &data_we, sizeof(data_we));
	if (eww == 0)
		*data = we32_to_cpu(data_we);
	wetuwn eww;
}

s32 bwcmf_fiw_xtwv_int8_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u8 *data)
{
	wetuwn bwcmf_fiw_xtwv_data_get(ifp, name, id, data, sizeof(*data));
}

s32 bwcmf_fiw_xtwv_int16_get(stwuct bwcmf_if *ifp, const chaw *name, u16 id, u16 *data)
{
	__we16 data_we = cpu_to_we16(*data);
	s32 eww;

	eww = bwcmf_fiw_xtwv_data_get(ifp, name, id, &data_we, sizeof(data_we));
	if (eww == 0)
		*data = we16_to_cpu(data_we);
	wetuwn eww;
}

