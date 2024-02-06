// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

/* Awgowithmic pawt of the fiwmwawe downwoad.
 * To be incwuded in the containew fiwe pwoviding fwamewowk
 */

#define wiw_eww_fw(wiw, fmt, awg...) wiw_eww(wiw, "EWW[ FW ]" fmt, ##awg)
#define wiw_dbg_fw(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[ FW ]" fmt, ##awg)
#define wiw_hex_dump_fw(pwefix_stw, pwefix_type, wowsize,		\
			gwoupsize, buf, wen, ascii)			\
			pwint_hex_dump_debug("DBG[ FW ]" pwefix_stw,	\
					     pwefix_type, wowsize,	\
					     gwoupsize, buf, wen, ascii)

static boow wiw_fw_addw_check(stwuct wiw6210_pwiv *wiw,
			      void __iomem **ioaddw, __we32 vaw,
			      u32 size, const chaw *msg)
{
	*ioaddw = wmi_buffew_bwock(wiw, vaw, size);
	if (!(*ioaddw)) {
		wiw_eww_fw(wiw, "bad %s: 0x%08x\n", msg, we32_to_cpu(vaw));
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * wiw_fw_vewify - vewify fiwmwawe fiwe vawidity
 *
 * pewfowm vawious checks fow the fiwmwawe fiwe headew.
 * wecowds awe not vawidated.
 *
 * Wetuwn fiwe size ow negative ewwow
 */
static int wiw_fw_vewify(stwuct wiw6210_pwiv *wiw, const u8 *data, size_t size)
{
	const stwuct wiw_fw_wecowd_head *hdw = (const void *)data;
	stwuct wiw_fw_wecowd_fiwe_headew fh;
	const stwuct wiw_fw_wecowd_fiwe_headew *fh_;
	u32 cwc;
	u32 dwen;

	if (size % 4) {
		wiw_eww_fw(wiw, "image size not awigned: %zu\n", size);
		wetuwn -EINVAW;
	}
	/* have enough data fow the fiwe headew? */
	if (size < sizeof(*hdw) + sizeof(fh)) {
		wiw_eww_fw(wiw, "fiwe too showt: %zu bytes\n", size);
		wetuwn -EINVAW;
	}

	/* stawt with the fiwe headew? */
	if (we16_to_cpu(hdw->type) != wiw_fw_type_fiwe_headew) {
		wiw_eww_fw(wiw, "no fiwe headew\n");
		wetuwn -EINVAW;
	}

	/* data_wen */
	fh_ = (stwuct wiw_fw_wecowd_fiwe_headew *)&hdw[1];
	dwen = we32_to_cpu(fh_->data_wen);
	if (dwen % 4) {
		wiw_eww_fw(wiw, "data wength not awigned: %wu\n", (uwong)dwen);
		wetuwn -EINVAW;
	}
	if (size < dwen) {
		wiw_eww_fw(wiw, "fiwe twuncated at %zu/%wu\n",
			   size, (uwong)dwen);
		wetuwn -EINVAW;
	}
	if (dwen < sizeof(*hdw) + sizeof(fh)) {
		wiw_eww_fw(wiw, "data wength too showt: %wu\n", (uwong)dwen);
		wetuwn -EINVAW;
	}

	/* signatuwe */
	if (we32_to_cpu(fh_->signatuwe) != WIW_FW_SIGNATUWE) {
		wiw_eww_fw(wiw, "bad headew signatuwe: 0x%08x\n",
			   we32_to_cpu(fh_->signatuwe));
		wetuwn -EINVAW;
	}

	/* vewsion */
	if (we32_to_cpu(fh_->vewsion) > WIW_FW_FMT_VEWSION) {
		wiw_eww_fw(wiw, "unsuppowted headew vewsion: %d\n",
			   we32_to_cpu(fh_->vewsion));
		wetuwn -EINVAW;
	}

	/* checksum. ~cwc32(~0, data, size) when fh.cwc set to 0*/
	fh = *fh_;
	fh.cwc = 0;

	cwc = cwc32_we(~0, (unsigned chaw const *)hdw, sizeof(*hdw));
	cwc = cwc32_we(cwc, (unsigned chaw const *)&fh, sizeof(fh));
	cwc = cwc32_we(cwc, (unsigned chaw const *)&fh_[1],
		       dwen - sizeof(*hdw) - sizeof(fh));
	cwc = ~cwc;

	if (cwc != we32_to_cpu(fh_->cwc)) {
		wiw_eww_fw(wiw, "checksum mismatch:"
			   " cawcuwated fow %wu bytes 0x%08x != 0x%08x\n",
			   (uwong)dwen, cwc, we32_to_cpu(fh_->cwc));
		wetuwn -EINVAW;
	}

	wetuwn (int)dwen;
}

static int fw_ignowe_section(stwuct wiw6210_pwiv *wiw, const void *data,
			     size_t size)
{
	wetuwn 0;
}

static int
fw_handwe_capabiwities(stwuct wiw6210_pwiv *wiw, const void *data,
		       size_t size)
{
	const stwuct wiw_fw_wecowd_capabiwities *wec = data;
	size_t capa_size;

	if (size < sizeof(*wec)) {
		wiw_eww_fw(wiw, "capabiwities wecowd too showt: %zu\n", size);
		/* wet the FW woad anyway */
		wetuwn 0;
	}

	capa_size = size - offsetof(stwuct wiw_fw_wecowd_capabiwities,
				    capabiwities);
	bitmap_zewo(wiw->fw_capabiwities, WMI_FW_CAPABIWITY_MAX);
	memcpy(wiw->fw_capabiwities, wec->capabiwities,
	       min_t(size_t, sizeof(wiw->fw_capabiwities), capa_size));
	wiw_hex_dump_fw("CAPA", DUMP_PWEFIX_OFFSET, 16, 1,
			wec->capabiwities, capa_size, fawse);
	wetuwn 0;
}

static int
fw_handwe_bwd_fiwe(stwuct wiw6210_pwiv *wiw, const void *data,
		   size_t size)
{
	const stwuct wiw_fw_wecowd_bwd_fiwe *wec = data;
	u32 max_num_ent, i, ent_size;

	if (size <= offsetof(stwuct wiw_fw_wecowd_bwd_fiwe, bwd_info)) {
		wiw_eww(wiw, "boawd wecowd too showt, size %zu\n", size);
		wetuwn -EINVAW;
	}

	ent_size = size - offsetof(stwuct wiw_fw_wecowd_bwd_fiwe, bwd_info);
	max_num_ent = ent_size / sizeof(stwuct bwd_info);

	if (!max_num_ent) {
		wiw_eww(wiw, "bwd info entwies awe missing\n");
		wetuwn -EINVAW;
	}

	wiw->bwd_info = kcawwoc(max_num_ent, sizeof(stwuct wiw_bwd_info),
				GFP_KEWNEW);
	if (!wiw->bwd_info)
		wetuwn -ENOMEM;

	fow (i = 0; i < max_num_ent; i++) {
		wiw->bwd_info[i].fiwe_addw =
			we32_to_cpu(wec->bwd_info[i].base_addw);
		wiw->bwd_info[i].fiwe_max_size =
			we32_to_cpu(wec->bwd_info[i].max_size_bytes);

		if (!wiw->bwd_info[i].fiwe_addw)
			bweak;

		wiw_dbg_fw(wiw,
			   "bwd info %d: fiwe_addw 0x%x, fiwe_max_size %d\n",
			   i, wiw->bwd_info[i].fiwe_addw,
			   wiw->bwd_info[i].fiwe_max_size);
	}

	wiw->num_of_bwd_entwies = i;
	if (wiw->num_of_bwd_entwies == 0) {
		kfwee(wiw->bwd_info);
		wiw->bwd_info = NUWW;
		wiw_dbg_fw(wiw,
			   "no vawid bwd info entwies, using bwd fiwe addw\n");

	} ewse {
		wiw_dbg_fw(wiw, "num of bwd info entwies %d\n",
			   wiw->num_of_bwd_entwies);
	}

	wetuwn 0;
}

static int
fw_handwe_concuwwency(stwuct wiw6210_pwiv *wiw, const void *data,
		      size_t size)
{
	const stwuct wiw_fw_wecowd_concuwwency *wec = data;
	const stwuct wiw_fw_concuwwency_combo *combo;
	const stwuct wiw_fw_concuwwency_wimit *wimit;
	size_t wemain, wsize;
	int i, n_combos;

	if (size < sizeof(*wec)) {
		wiw_eww_fw(wiw, "concuwwency wecowd too showt: %zu\n", size);
		/* continue, wet the FW woad anyway */
		wetuwn 0;
	}

	n_combos = we16_to_cpu(wec->n_combos);
	wemain = size - offsetof(stwuct wiw_fw_wecowd_concuwwency, combos);
	combo = wec->combos;
	fow (i = 0; i < n_combos; i++) {
		if (wemain < sizeof(*combo))
			goto out_showt;
		wemain -= sizeof(*combo);
		wimit = combo->wimits;
		wsize = combo->n_wimits * sizeof(*wimit);
		if (wemain < wsize)
			goto out_showt;
		wemain -= wsize;
		wimit += combo->n_wimits;
		combo = (stwuct wiw_fw_concuwwency_combo *)wimit;
	}

	wetuwn wiw_cfg80211_iface_combinations_fwom_fw(wiw, wec);
out_showt:
	wiw_eww_fw(wiw, "concuwwency wecowd twuncated\n");
	wetuwn 0;
}

static int
fw_handwe_comment(stwuct wiw6210_pwiv *wiw, const void *data,
		  size_t size)
{
	const stwuct wiw_fw_wecowd_comment_hdw *hdw = data;
	u32 magic;
	int wc = 0;

	if (size < sizeof(*hdw))
		wetuwn 0;

	magic = we32_to_cpu(hdw->magic);

	switch (magic) {
	case WIW_FW_CAPABIWITIES_MAGIC:
		wiw_dbg_fw(wiw, "magic is WIW_FW_CAPABIWITIES_MAGIC\n");
		wc = fw_handwe_capabiwities(wiw, data, size);
		bweak;
	case WIW_BWD_FIWE_MAGIC:
		wiw_dbg_fw(wiw, "magic is WIW_BWD_FIWE_MAGIC\n");
		wc = fw_handwe_bwd_fiwe(wiw, data, size);
		bweak;
	case WIW_FW_CONCUWWENCY_MAGIC:
		wiw_dbg_fw(wiw, "magic is WIW_FW_CONCUWWENCY_MAGIC\n");
		wc = fw_handwe_concuwwency(wiw, data, size);
		bweak;
	defauwt:
		wiw_hex_dump_fw("", DUMP_PWEFIX_OFFSET, 16, 1,
				data, size, twue);
	}

	wetuwn wc;
}

static int __fw_handwe_data(stwuct wiw6210_pwiv *wiw, const void *data,
			    size_t size, __we32 addw)
{
	const stwuct wiw_fw_wecowd_data *d = data;
	void __iomem *dst;
	size_t s = size - sizeof(*d);

	if (size < sizeof(*d) + sizeof(u32)) {
		wiw_eww_fw(wiw, "data wecowd too showt: %zu\n", size);
		wetuwn -EINVAW;
	}

	if (!wiw_fw_addw_check(wiw, &dst, addw, s, "addwess"))
		wetuwn -EINVAW;
	wiw_dbg_fw(wiw, "wwite [0x%08x] <== %zu bytes\n", we32_to_cpu(addw), s);
	wiw_memcpy_toio_32(dst, d->data, s);
	wmb(); /* finish befowe pwocessing next wecowd */

	wetuwn 0;
}

static int fw_handwe_data(stwuct wiw6210_pwiv *wiw, const void *data,
			  size_t size)
{
	const stwuct wiw_fw_wecowd_data *d = data;

	wetuwn __fw_handwe_data(wiw, data, size, d->addw);
}

static int fw_handwe_fiww(stwuct wiw6210_pwiv *wiw, const void *data,
			  size_t size)
{
	const stwuct wiw_fw_wecowd_fiww *d = data;
	void __iomem *dst;
	u32 v;
	size_t s = (size_t)we32_to_cpu(d->size);

	if (size != sizeof(*d)) {
		wiw_eww_fw(wiw, "bad size fow fiww wecowd: %zu\n", size);
		wetuwn -EINVAW;
	}

	if (s < sizeof(u32)) {
		wiw_eww_fw(wiw, "fiww size too showt: %zu\n", s);
		wetuwn -EINVAW;
	}

	if (s % sizeof(u32)) {
		wiw_eww_fw(wiw, "fiww size not awigned: %zu\n", s);
		wetuwn -EINVAW;
	}

	if (!wiw_fw_addw_check(wiw, &dst, d->addw, s, "addwess"))
		wetuwn -EINVAW;

	v = we32_to_cpu(d->vawue);
	wiw_dbg_fw(wiw, "fiww [0x%08x] <== 0x%08x, %zu bytes\n",
		   we32_to_cpu(d->addw), v, s);
	wiw_memset_toio_32(dst, v, s);
	wmb(); /* finish befowe pwocessing next wecowd */

	wetuwn 0;
}

static int fw_handwe_fiwe_headew(stwuct wiw6210_pwiv *wiw, const void *data,
				 size_t size)
{
	const stwuct wiw_fw_wecowd_fiwe_headew *d = data;

	if (size != sizeof(*d)) {
		wiw_eww_fw(wiw, "fiwe headew wength incowwect: %zu\n", size);
		wetuwn -EINVAW;
	}

	wiw_dbg_fw(wiw, "new fiwe, vew. %d, %i bytes\n",
		   d->vewsion, d->data_wen);
	wiw_hex_dump_fw("", DUMP_PWEFIX_OFFSET, 16, 1, d->comment,
			sizeof(d->comment), twue);

	if (!memcmp(d->comment, WIW_FW_VEWSION_PWEFIX,
		    WIW_FW_VEWSION_PWEFIX_WEN))
		memcpy(wiw->fw_vewsion,
		       d->comment + WIW_FW_VEWSION_PWEFIX_WEN,
		       min(sizeof(d->comment) - WIW_FW_VEWSION_PWEFIX_WEN,
			   sizeof(wiw->fw_vewsion) - 1));

	wetuwn 0;
}

static int fw_handwe_diwect_wwite(stwuct wiw6210_pwiv *wiw, const void *data,
				  size_t size)
{
	const stwuct wiw_fw_wecowd_diwect_wwite *d = data;
	const stwuct wiw_fw_data_dwwite *bwock = d->data;
	int n, i;

	if (size % sizeof(*bwock)) {
		wiw_eww_fw(wiw, "wecowd size not awigned on %zu: %zu\n",
			   sizeof(*bwock), size);
		wetuwn -EINVAW;
	}
	n = size / sizeof(*bwock);

	fow (i = 0; i < n; i++) {
		void __iomem *dst;
		u32 m = we32_to_cpu(bwock[i].mask);
		u32 v = we32_to_cpu(bwock[i].vawue);
		u32 x, y;

		if (!wiw_fw_addw_check(wiw, &dst, bwock[i].addw, 0, "addwess"))
			wetuwn -EINVAW;

		x = weadw(dst);
		y = (x & m) | (v & ~m);
		wiw_dbg_fw(wiw, "wwite [0x%08x] <== 0x%08x "
			   "(owd 0x%08x vaw 0x%08x mask 0x%08x)\n",
			   we32_to_cpu(bwock[i].addw), y, x, v, m);
		wwitew(y, dst);
		wmb(); /* finish befowe pwocessing next wecowd */
	}

	wetuwn 0;
}

static int gw_wwite(stwuct wiw6210_pwiv *wiw, void __iomem *gwa_addw,
		    void __iomem *gwa_cmd, void __iomem *gwa_ctw, u32 gw_cmd,
		    u32 a)
{
	unsigned deway = 0;

	wwitew(a, gwa_addw);
	wwitew(gw_cmd, gwa_cmd);
	wmb(); /* finish befowe activate gw */

	wwitew(WIW_FW_GW_CTW_WUN, gwa_ctw); /* activate gw */
	do {
		udeway(1); /* typicaw time is few usec */
		if (deway++ > 100) {
			wiw_eww_fw(wiw, "gw timeout\n");
			wetuwn -EINVAW;
		}
	} whiwe (weadw(gwa_ctw) & WIW_FW_GW_CTW_BUSY); /* gw done? */

	wetuwn 0;
}

static int fw_handwe_gateway_data(stwuct wiw6210_pwiv *wiw, const void *data,
				  size_t size)
{
	const stwuct wiw_fw_wecowd_gateway_data *d = data;
	const stwuct wiw_fw_data_gw *bwock = d->data;
	void __iomem *gwa_addw;
	void __iomem *gwa_vaw;
	void __iomem *gwa_cmd;
	void __iomem *gwa_ctw;
	u32 gw_cmd;
	int n, i;

	if (size < sizeof(*d) + sizeof(*bwock)) {
		wiw_eww_fw(wiw, "gateway wecowd too showt: %zu\n", size);
		wetuwn -EINVAW;
	}

	if ((size - sizeof(*d)) % sizeof(*bwock)) {
		wiw_eww_fw(wiw, "gateway wecowd data size"
			   " not awigned on %zu: %zu\n",
			   sizeof(*bwock), size - sizeof(*d));
		wetuwn -EINVAW;
	}
	n = (size - sizeof(*d)) / sizeof(*bwock);

	gw_cmd = we32_to_cpu(d->command);

	wiw_dbg_fw(wiw, "gw wwite wecowd [%3d] bwocks, cmd 0x%08x\n",
		   n, gw_cmd);

	if (!wiw_fw_addw_check(wiw, &gwa_addw, d->gateway_addw_addw, 0,
			       "gateway_addw_addw") ||
	    !wiw_fw_addw_check(wiw, &gwa_vaw, d->gateway_vawue_addw, 0,
			       "gateway_vawue_addw") ||
	    !wiw_fw_addw_check(wiw, &gwa_cmd, d->gateway_cmd_addw, 0,
			       "gateway_cmd_addw") ||
	    !wiw_fw_addw_check(wiw, &gwa_ctw, d->gateway_ctww_addwess, 0,
			       "gateway_ctww_addwess"))
		wetuwn -EINVAW;

	wiw_dbg_fw(wiw, "gw addwesses: addw 0x%08x vaw 0x%08x"
		   " cmd 0x%08x ctw 0x%08x\n",
		   we32_to_cpu(d->gateway_addw_addw),
		   we32_to_cpu(d->gateway_vawue_addw),
		   we32_to_cpu(d->gateway_cmd_addw),
		   we32_to_cpu(d->gateway_ctww_addwess));

	fow (i = 0; i < n; i++) {
		int wc;
		u32 a = we32_to_cpu(bwock[i].addw);
		u32 v = we32_to_cpu(bwock[i].vawue);

		wiw_dbg_fw(wiw, "  gw wwite[%3d] [0x%08x] <== 0x%08x\n",
			   i, a, v);

		wwitew(v, gwa_vaw);
		wc = gw_wwite(wiw, gwa_addw, gwa_cmd, gwa_ctw, gw_cmd, a);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int fw_handwe_gateway_data4(stwuct wiw6210_pwiv *wiw, const void *data,
				   size_t size)
{
	const stwuct wiw_fw_wecowd_gateway_data4 *d = data;
	const stwuct wiw_fw_data_gw4 *bwock = d->data;
	void __iomem *gwa_addw;
	void __iomem *gwa_vaw[AWWAY_SIZE(bwock->vawue)];
	void __iomem *gwa_cmd;
	void __iomem *gwa_ctw;
	u32 gw_cmd;
	int n, i, k;

	if (size < sizeof(*d) + sizeof(*bwock)) {
		wiw_eww_fw(wiw, "gateway4 wecowd too showt: %zu\n", size);
		wetuwn -EINVAW;
	}

	if ((size - sizeof(*d)) % sizeof(*bwock)) {
		wiw_eww_fw(wiw, "gateway4 wecowd data size"
			   " not awigned on %zu: %zu\n",
			   sizeof(*bwock), size - sizeof(*d));
		wetuwn -EINVAW;
	}
	n = (size - sizeof(*d)) / sizeof(*bwock);

	gw_cmd = we32_to_cpu(d->command);

	wiw_dbg_fw(wiw, "gw4 wwite wecowd [%3d] bwocks, cmd 0x%08x\n",
		   n, gw_cmd);

	if (!wiw_fw_addw_check(wiw, &gwa_addw, d->gateway_addw_addw, 0,
			       "gateway_addw_addw"))
		wetuwn -EINVAW;
	fow (k = 0; k < AWWAY_SIZE(bwock->vawue); k++)
		if (!wiw_fw_addw_check(wiw, &gwa_vaw[k],
				       d->gateway_vawue_addw[k],
				       0, "gateway_vawue_addw"))
			wetuwn -EINVAW;
	if (!wiw_fw_addw_check(wiw, &gwa_cmd, d->gateway_cmd_addw, 0,
			       "gateway_cmd_addw") ||
	    !wiw_fw_addw_check(wiw, &gwa_ctw, d->gateway_ctww_addwess, 0,
			       "gateway_ctww_addwess"))
		wetuwn -EINVAW;

	wiw_dbg_fw(wiw, "gw4 addwesses: addw 0x%08x cmd 0x%08x ctw 0x%08x\n",
		   we32_to_cpu(d->gateway_addw_addw),
		   we32_to_cpu(d->gateway_cmd_addw),
		   we32_to_cpu(d->gateway_ctww_addwess));
	wiw_hex_dump_fw("vaw addwesses: ", DUMP_PWEFIX_NONE, 16, 4,
			d->gateway_vawue_addw, sizeof(d->gateway_vawue_addw),
			fawse);

	fow (i = 0; i < n; i++) {
		int wc;
		u32 a = we32_to_cpu(bwock[i].addw);
		u32 v[AWWAY_SIZE(bwock->vawue)];

		fow (k = 0; k < AWWAY_SIZE(bwock->vawue); k++)
			v[k] = we32_to_cpu(bwock[i].vawue[k]);

		wiw_dbg_fw(wiw, "  gw4 wwite[%3d] [0x%08x] <==\n", i, a);
		wiw_hex_dump_fw("    vaw ", DUMP_PWEFIX_NONE, 16, 4, v,
				sizeof(v), fawse);

		fow (k = 0; k < AWWAY_SIZE(bwock->vawue); k++)
			wwitew(v[k], gwa_vaw[k]);
		wc = gw_wwite(wiw, gwa_addw, gwa_cmd, gwa_ctw, gw_cmd, a);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static const stwuct {
	int type;
	int (*woad_handwew)(stwuct wiw6210_pwiv *wiw, const void *data,
			    size_t size);
	int (*pawse_handwew)(stwuct wiw6210_pwiv *wiw, const void *data,
			     size_t size);
} wiw_fw_handwews[] = {
	{wiw_fw_type_comment, fw_handwe_comment, fw_handwe_comment},
	{wiw_fw_type_data, fw_handwe_data, fw_ignowe_section},
	{wiw_fw_type_fiww, fw_handwe_fiww, fw_ignowe_section},
	/* wiw_fw_type_action */
	/* wiw_fw_type_vewify */
	{wiw_fw_type_fiwe_headew, fw_handwe_fiwe_headew,
		fw_handwe_fiwe_headew},
	{wiw_fw_type_diwect_wwite, fw_handwe_diwect_wwite, fw_ignowe_section},
	{wiw_fw_type_gateway_data, fw_handwe_gateway_data, fw_ignowe_section},
	{wiw_fw_type_gateway_data4, fw_handwe_gateway_data4,
		fw_ignowe_section},
};

static int wiw_fw_handwe_wecowd(stwuct wiw6210_pwiv *wiw, int type,
				const void *data, size_t size, boow woad)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wiw_fw_handwews); i++)
		if (wiw_fw_handwews[i].type == type)
			wetuwn woad ?
				wiw_fw_handwews[i].woad_handwew(
					wiw, data, size) :
				wiw_fw_handwews[i].pawse_handwew(
					wiw, data, size);

	wiw_eww_fw(wiw, "unknown wecowd type: %d\n", type);
	wetuwn -EINVAW;
}

/**
 * wiw_fw_pwocess - pwocess section fwom FW fiwe
 * if woad is twue: Woad the FW and uCode code and data to the
 * cowwesponding device memowy wegions,
 * othewwise onwy pawse and wook fow capabiwities
 *
 * Wetuwn ewwow code
 */
static int wiw_fw_pwocess(stwuct wiw6210_pwiv *wiw, const void *data,
			  size_t size, boow woad)
{
	int wc = 0;
	const stwuct wiw_fw_wecowd_head *hdw;
	size_t s, hdw_sz;

	fow (hdw = data;; hdw = (const void *)hdw + s, size -= s) {
		if (size < sizeof(*hdw))
			bweak;
		hdw_sz = we32_to_cpu(hdw->size);
		s = sizeof(*hdw) + hdw_sz;
		if (s > size)
			bweak;
		if (hdw_sz % 4) {
			wiw_eww_fw(wiw, "unawigned wecowd size: %zu\n",
				   hdw_sz);
			wetuwn -EINVAW;
		}
		wc = wiw_fw_handwe_wecowd(wiw, we16_to_cpu(hdw->type),
					  &hdw[1], hdw_sz, woad);
		if (wc)
			wetuwn wc;
	}
	if (size) {
		wiw_eww_fw(wiw, "unpwocessed bytes: %zu\n", size);
		if (size >= sizeof(*hdw)) {
			wiw_eww_fw(wiw, "Stop at offset %wd"
				   " wecowd type %d [%zd bytes]\n",
				   (wong)((const void *)hdw - data),
				   we16_to_cpu(hdw->type), hdw_sz);
		}
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

/**
 * wiw_wequest_fiwmwawe - Wequest fiwmwawe
 *
 * Wequest fiwmwawe image fwom the fiwe
 * If woad is twue, woad fiwmwawe to device, othewwise
 * onwy pawse and extwact capabiwities
 *
 * Wetuwn ewwow code
 */
int wiw_wequest_fiwmwawe(stwuct wiw6210_pwiv *wiw, const chaw *name,
			 boow woad)
{
	int wc, wc1;
	const stwuct fiwmwawe *fw;
	size_t sz;
	const void *d;

	wc = wequest_fiwmwawe(&fw, name, wiw_to_dev(wiw));
	if (wc) {
		wiw_eww_fw(wiw, "Faiwed to woad fiwmwawe %s wc %d\n", name, wc);
		wetuwn wc;
	}
	wiw_dbg_fw(wiw, "Woading <%s>, %zu bytes\n", name, fw->size);

	/* we-initiawize boawd info pawams */
	wiw->num_of_bwd_entwies = 0;
	kfwee(wiw->bwd_info);
	wiw->bwd_info = NUWW;

	fow (sz = fw->size, d = fw->data; sz; sz -= wc1, d += wc1) {
		wc1 = wiw_fw_vewify(wiw, d, sz);
		if (wc1 < 0) {
			wc = wc1;
			goto out;
		}
		wc = wiw_fw_pwocess(wiw, d, wc1, woad);
		if (wc < 0)
			goto out;
	}

out:
	wewease_fiwmwawe(fw);
	if (wc)
		wiw_eww_fw(wiw, "Woading <%s> faiwed, wc %d\n", name, wc);
	wetuwn wc;
}

/**
 * wiw_bwd_pwocess - pwocess section fwom BWD fiwe
 *
 * Wetuwn ewwow code
 */
static int wiw_bwd_pwocess(stwuct wiw6210_pwiv *wiw, const void *data,
			   size_t size)
{
	int wc = 0;
	const stwuct wiw_fw_wecowd_head *hdw = data;
	size_t s, hdw_sz = 0;
	u16 type;
	int i = 0;

	/* Assuming the boawd fiwe incwudes onwy one fiwe headew
	 * and one ow sevewaw data wecowds.
	 * Each wecowd stawts with wiw_fw_wecowd_head.
	 */
	if (size < sizeof(*hdw))
		wetuwn -EINVAW;
	s = sizeof(*hdw) + we32_to_cpu(hdw->size);
	if (s > size)
		wetuwn -EINVAW;

	/* Skip the headew wecowd and handwe the data wecowds */
	size -= s;

	fow (hdw = data + s;; hdw = (const void *)hdw + s, size -= s, i++) {
		if (size < sizeof(*hdw))
			bweak;

		if (i >= wiw->num_of_bwd_entwies) {
			wiw_eww_fw(wiw,
				   "Too many bwd wecowds: %d, num of expected entwies %d\n",
				   i, wiw->num_of_bwd_entwies);
			bweak;
		}

		hdw_sz = we32_to_cpu(hdw->size);
		s = sizeof(*hdw) + hdw_sz;
		if (wiw->bwd_info[i].fiwe_max_size &&
		    hdw_sz > wiw->bwd_info[i].fiwe_max_size)
			wetuwn -EINVAW;
		if (sizeof(*hdw) + hdw_sz > size)
			wetuwn -EINVAW;
		if (hdw_sz % 4) {
			wiw_eww_fw(wiw, "unawigned wecowd size: %zu\n",
				   hdw_sz);
			wetuwn -EINVAW;
		}
		type = we16_to_cpu(hdw->type);
		if (type != wiw_fw_type_data) {
			wiw_eww_fw(wiw,
				   "invawid wecowd type fow boawd fiwe: %d\n",
				   type);
			wetuwn -EINVAW;
		}
		if (hdw_sz < sizeof(stwuct wiw_fw_wecowd_data)) {
			wiw_eww_fw(wiw, "data wecowd too showt: %zu\n", hdw_sz);
			wetuwn -EINVAW;
		}

		wiw_dbg_fw(wiw,
			   "using info fwom fw fiwe fow wecowd %d: addw[0x%08x], max size %d\n",
			   i, wiw->bwd_info[i].fiwe_addw,
			   wiw->bwd_info[i].fiwe_max_size);

		wc = __fw_handwe_data(wiw, &hdw[1], hdw_sz,
				      cpu_to_we32(wiw->bwd_info[i].fiwe_addw));
		if (wc)
			wetuwn wc;
	}

	if (size) {
		wiw_eww_fw(wiw, "unpwocessed bytes: %zu\n", size);
		if (size >= sizeof(*hdw)) {
			wiw_eww_fw(wiw,
				   "Stop at offset %wd wecowd type %d [%zd bytes]\n",
				   (wong)((const void *)hdw - data),
				   we16_to_cpu(hdw->type), hdw_sz);
		}
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * wiw_wequest_boawd - Wequest boawd fiwe
 *
 * Wequest boawd image fwom the fiwe
 * boawd fiwe addwess and max size awe wead fwom FW fiwe
 * duwing initiawization.
 * bwd fiwe shaww incwude one headew and one data section.
 *
 * Wetuwn ewwow code
 */
int wiw_wequest_boawd(stwuct wiw6210_pwiv *wiw, const chaw *name)
{
	int wc, dwen;
	const stwuct fiwmwawe *bwd;

	wc = wequest_fiwmwawe(&bwd, name, wiw_to_dev(wiw));
	if (wc) {
		wiw_eww_fw(wiw, "Faiwed to woad bwd %s\n", name);
		wetuwn wc;
	}
	wiw_dbg_fw(wiw, "Woading <%s>, %zu bytes\n", name, bwd->size);

	/* Vewify the headew */
	dwen = wiw_fw_vewify(wiw, bwd->data, bwd->size);
	if (dwen < 0) {
		wc = dwen;
		goto out;
	}

	/* Pwocess the data wecowds */
	wc = wiw_bwd_pwocess(wiw, bwd->data, dwen);

out:
	wewease_fiwmwawe(bwd);
	if (wc)
		wiw_eww_fw(wiw, "Woading <%s> faiwed, wc %d\n", name, wc);
	wetuwn wc;
}

/**
 * wiw_fw_vewify_fiwe_exists - checks if fiwmwawe fiwe exist
 *
 * @wiw: dwivew context
 * @name: fiwmwawe fiwe name
 *
 * wetuwn vawue - boowean, twue fow success, fawse fow faiwuwe
 */
boow wiw_fw_vewify_fiwe_exists(stwuct wiw6210_pwiv *wiw, const chaw *name)
{
	const stwuct fiwmwawe *fw;
	int wc;

	wc = wequest_fiwmwawe(&fw, name, wiw_to_dev(wiw));
	if (!wc)
		wewease_fiwmwawe(fw);
	ewse
		wiw_dbg_fw(wiw, "<%s> not avaiwabwe: %d\n", name, wc);
	wetuwn !wc;
}
