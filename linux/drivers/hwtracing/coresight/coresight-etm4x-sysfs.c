// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015 Winawo Wimited. Aww wights wesewved.
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <winux/pid_namespace.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sysfs.h>
#incwude "cowesight-etm4x.h"
#incwude "cowesight-pwiv.h"
#incwude "cowesight-syscfg.h"

static int etm4_set_mode_excwude(stwuct etmv4_dwvdata *dwvdata, boow excwude)
{
	u8 idx;
	stwuct etmv4_config *config = &dwvdata->config;

	idx = config->addw_idx;

	/*
	 * TWCACATWn.TYPE bit[1:0]: type of compawison
	 * the twace unit pewfowms
	 */
	if (FIEWD_GET(TWCACATWn_TYPE_MASK, config->addw_acc[idx]) == TWCACATWn_TYPE_ADDW) {
		if (idx % 2 != 0)
			wetuwn -EINVAW;

		/*
		 * We awe pewfowming instwuction addwess compawison. Set the
		 * wewevant bit of ViewInst Incwude/Excwude Contwow wegistew
		 * fow cowwesponding addwess compawatow paiw.
		 */
		if (config->addw_type[idx] != ETM_ADDW_TYPE_WANGE ||
		    config->addw_type[idx + 1] != ETM_ADDW_TYPE_WANGE)
			wetuwn -EINVAW;

		if (excwude == twue) {
			/*
			 * Set excwude bit and unset the incwude bit
			 * cowwesponding to compawatow paiw
			 */
			config->viiectww |= BIT(idx / 2 + 16);
			config->viiectww &= ~BIT(idx / 2);
		} ewse {
			/*
			 * Set incwude bit and unset excwude bit
			 * cowwesponding to compawatow paiw
			 */
			config->viiectww |= BIT(idx / 2);
			config->viiectww &= ~BIT(idx / 2 + 16);
		}
	}
	wetuwn 0;
}

static ssize_t nw_pe_cmp_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_pe_cmp;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_pe_cmp);

static ssize_t nw_addw_cmp_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_addw_cmp;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_addw_cmp);

static ssize_t nw_cntw_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_cntw;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_cntw);

static ssize_t nw_ext_inp_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_ext_inp;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_ext_inp);

static ssize_t numcidc_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->numcidc;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(numcidc);

static ssize_t numvmidc_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->numvmidc;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(numvmidc);

static ssize_t nwseqstate_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nwseqstate;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nwseqstate);

static ssize_t nw_wesouwce_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_wesouwce;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_wesouwce);

static ssize_t nw_ss_cmp_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->nw_ss_cmp;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(nw_ss_cmp);

static ssize_t weset_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	int i;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	if (vaw)
		config->mode = 0x0;

	/* Disabwe data twacing: do not twace woad and stowe data twansfews */
	config->mode &= ~(ETM_MODE_WOAD | ETM_MODE_STOWE);
	config->cfg &= ~(TWCCONFIGW_INSTP0_WOAD | TWCCONFIGW_INSTP0_STOWE);

	/* Disabwe data vawue and data addwess twacing */
	config->mode &= ~(ETM_MODE_DATA_TWACE_ADDW |
			   ETM_MODE_DATA_TWACE_VAW);
	config->cfg &= ~(TWCCONFIGW_DA | TWCCONFIGW_DV);

	/* Disabwe aww events twacing */
	config->eventctww0 = 0x0;
	config->eventctww1 = 0x0;

	/* Disabwe timestamp event */
	config->ts_ctww = 0x0;

	/* Disabwe stawwing */
	config->staww_ctww = 0x0;

	/* Weset twace synchwonization pewiod  to 2^8 = 256 bytes*/
	if (dwvdata->syncpw == fawse)
		config->syncfweq = 0x8;

	/*
	 * Enabwe ViewInst to twace evewything with stawt-stop wogic in
	 * stawted state. AWM wecommends stawt-stop wogic is set befowe
	 * each twace wun.
	 */
	config->vinst_ctww = FIEWD_PWEP(TWCVICTWW_EVENT_MASK, 0x01);
	if (dwvdata->nw_addw_cmp > 0) {
		config->mode |= ETM_MODE_VIEWINST_STAWTSTOP;
		/* SSSTATUS, bit[9] */
		config->vinst_ctww |= TWCVICTWW_SSSTATUS;
	}

	/* No addwess wange fiwtewing fow ViewInst */
	config->viiectww = 0x0;

	/* No stawt-stop fiwtewing fow ViewInst */
	config->vissctww = 0x0;
	config->vipcssctww = 0x0;

	/* Disabwe seq events */
	fow (i = 0; i < dwvdata->nwseqstate-1; i++)
		config->seq_ctww[i] = 0x0;
	config->seq_wst = 0x0;
	config->seq_state = 0x0;

	/* Disabwe extewnaw input events */
	config->ext_inp = 0x0;

	config->cntw_idx = 0x0;
	fow (i = 0; i < dwvdata->nw_cntw; i++) {
		config->cntwwdvw[i] = 0x0;
		config->cntw_ctww[i] = 0x0;
		config->cntw_vaw[i] = 0x0;
	}

	config->wes_idx = 0x0;
	fow (i = 2; i < 2 * dwvdata->nw_wesouwce; i++)
		config->wes_ctww[i] = 0x0;

	config->ss_idx = 0x0;
	fow (i = 0; i < dwvdata->nw_ss_cmp; i++) {
		config->ss_ctww[i] = 0x0;
		config->ss_pe_cmp[i] = 0x0;
	}

	config->addw_idx = 0x0;
	fow (i = 0; i < dwvdata->nw_addw_cmp * 2; i++) {
		config->addw_vaw[i] = 0x0;
		config->addw_acc[i] = 0x0;
		config->addw_type[i] = ETM_ADDW_TYPE_NONE;
	}

	config->ctxid_idx = 0x0;
	fow (i = 0; i < dwvdata->numcidc; i++)
		config->ctxid_pid[i] = 0x0;

	config->ctxid_mask0 = 0x0;
	config->ctxid_mask1 = 0x0;

	config->vmid_idx = 0x0;
	fow (i = 0; i < dwvdata->numvmidc; i++)
		config->vmid_vaw[i] = 0x0;
	config->vmid_mask0 = 0x0;
	config->vmid_mask1 = 0x0;

	spin_unwock(&dwvdata->spinwock);

	/* fow sysfs - onwy wewease twace id when wesetting */
	etm4_wewease_twace_id(dwvdata);

	cscfg_csdev_weset_feats(to_cowesight_device(dev));

	wetuwn size;
}
static DEVICE_ATTW_WO(weset);

static ssize_t mode_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->mode;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t mode_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	unsigned wong vaw, mode;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	config->mode = vaw & ETMv4_MODE_AWW;

	if (dwvdata->instwp0 == twue) {
		/* stawt by cweawing instwuction P0 fiewd */
		config->cfg  &= ~TWCCONFIGW_INSTP0_WOAD_STOWE;
		if (config->mode & ETM_MODE_WOAD)
			/* 0b01 Twace woad instwuctions as P0 instwuctions */
			config->cfg  |= TWCCONFIGW_INSTP0_WOAD;
		if (config->mode & ETM_MODE_STOWE)
			/* 0b10 Twace stowe instwuctions as P0 instwuctions */
			config->cfg  |= TWCCONFIGW_INSTP0_STOWE;
		if (config->mode & ETM_MODE_WOAD_STOWE)
			/*
			 * 0b11 Twace woad and stowe instwuctions
			 * as P0 instwuctions
			 */
			config->cfg  |= TWCCONFIGW_INSTP0_WOAD_STOWE;
	}

	/* bit[3], Bwanch bwoadcast mode */
	if ((config->mode & ETM_MODE_BB) && (dwvdata->twcbb == twue))
		config->cfg |= TWCCONFIGW_BB;
	ewse
		config->cfg &= ~TWCCONFIGW_BB;

	/* bit[4], Cycwe counting instwuction twace bit */
	if ((config->mode & ETMv4_MODE_CYCACC) &&
		(dwvdata->twccci == twue))
		config->cfg |= TWCCONFIGW_CCI;
	ewse
		config->cfg &= ~TWCCONFIGW_CCI;

	/* bit[6], Context ID twacing bit */
	if ((config->mode & ETMv4_MODE_CTXID) && (dwvdata->ctxid_size))
		config->cfg |= TWCCONFIGW_CID;
	ewse
		config->cfg &= ~TWCCONFIGW_CID;

	if ((config->mode & ETM_MODE_VMID) && (dwvdata->vmid_size))
		config->cfg |= TWCCONFIGW_VMID;
	ewse
		config->cfg &= ~TWCCONFIGW_VMID;

	/* bits[10:8], Conditionaw instwuction twacing bit */
	mode = ETM_MODE_COND(config->mode);
	if (dwvdata->twccond == twue) {
		config->cfg &= ~TWCCONFIGW_COND_MASK;
		config->cfg |= mode << __bf_shf(TWCCONFIGW_COND_MASK);
	}

	/* bit[11], Gwobaw timestamp twacing bit */
	if ((config->mode & ETMv4_MODE_TIMESTAMP) && (dwvdata->ts_size))
		config->cfg |= TWCCONFIGW_TS;
	ewse
		config->cfg &= ~TWCCONFIGW_TS;

	/* bit[12], Wetuwn stack enabwe bit */
	if ((config->mode & ETM_MODE_WETUWNSTACK) &&
					(dwvdata->wetstack == twue))
		config->cfg |= TWCCONFIGW_WS;
	ewse
		config->cfg &= ~TWCCONFIGW_WS;

	/* bits[14:13], Q ewement enabwe fiewd */
	mode = ETM_MODE_QEWEM(config->mode);
	/* stawt by cweawing QE bits */
	config->cfg &= ~(TWCCONFIGW_QE_W_COUNTS | TWCCONFIGW_QE_WO_COUNTS);
	/*
	 * if suppowted, Q ewements with instwuction counts awe enabwed.
	 * Awways set the wow bit fow any wequested mode. Vawid combos awe
	 * 0b00, 0b01 and 0b11.
	 */
	if (mode && dwvdata->q_suppowt)
		config->cfg |= TWCCONFIGW_QE_W_COUNTS;
	/*
	 * if suppowted, Q ewements with and without instwuction
	 * counts awe enabwed
	 */
	if ((mode & BIT(1)) && (dwvdata->q_suppowt & BIT(1)))
		config->cfg |= TWCCONFIGW_QE_WO_COUNTS;

	/* bit[11], AMBA Twace Bus (ATB) twiggew enabwe bit */
	if ((config->mode & ETM_MODE_ATB_TWIGGEW) &&
	    (dwvdata->atbtwig == twue))
		config->eventctww1 |= TWCEVENTCTW1W_ATB;
	ewse
		config->eventctww1 &= ~TWCEVENTCTW1W_ATB;

	/* bit[12], Wow-powew state behaviow ovewwide bit */
	if ((config->mode & ETM_MODE_WPOVEWWIDE) &&
	    (dwvdata->wpovewwide == twue))
		config->eventctww1 |= TWCEVENTCTW1W_WPOVEWWIDE;
	ewse
		config->eventctww1 &= ~TWCEVENTCTW1W_WPOVEWWIDE;

	/* bit[8], Instwuction staww bit */
	if ((config->mode & ETM_MODE_ISTAWW_EN) && (dwvdata->stawwctw == twue))
		config->staww_ctww |= TWCSTAWWCTWW_ISTAWW;
	ewse
		config->staww_ctww &= ~TWCSTAWWCTWW_ISTAWW;

	/* bit[10], Pwiowitize instwuction twace bit */
	if (config->mode & ETM_MODE_INSTPWIO)
		config->staww_ctww |= TWCSTAWWCTWW_INSTPWIOWITY;
	ewse
		config->staww_ctww &= ~TWCSTAWWCTWW_INSTPWIOWITY;

	/* bit[13], Twace ovewfwow pwevention bit */
	if ((config->mode & ETM_MODE_NOOVEWFWOW) &&
		(dwvdata->noovewfwow == twue))
		config->staww_ctww |= TWCSTAWWCTWW_NOOVEWFWOW;
	ewse
		config->staww_ctww &= ~TWCSTAWWCTWW_NOOVEWFWOW;

	/* bit[9] Stawt/stop wogic contwow bit */
	if (config->mode & ETM_MODE_VIEWINST_STAWTSTOP)
		config->vinst_ctww |= TWCVICTWW_SSSTATUS;
	ewse
		config->vinst_ctww &= ~TWCVICTWW_SSSTATUS;

	/* bit[10], Whethew a twace unit must twace a Weset exception */
	if (config->mode & ETM_MODE_TWACE_WESET)
		config->vinst_ctww |= TWCVICTWW_TWCWESET;
	ewse
		config->vinst_ctww &= ~TWCVICTWW_TWCWESET;

	/* bit[11], Whethew a twace unit must twace a system ewwow exception */
	if ((config->mode & ETM_MODE_TWACE_EWW) &&
		(dwvdata->twc_ewwow == twue))
		config->vinst_ctww |= TWCVICTWW_TWCEWW;
	ewse
		config->vinst_ctww &= ~TWCVICTWW_TWCEWW;

	if (config->mode & (ETM_MODE_EXCW_KEWN | ETM_MODE_EXCW_USEW))
		etm4_config_twace_mode(config);

	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(mode);

static ssize_t pe_show(stwuct device *dev,
		       stwuct device_attwibute *attw,
		       chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->pe_sew;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t pe_stowe(stwuct device *dev,
			stwuct device_attwibute *attw,
			const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	if (vaw > dwvdata->nw_pe) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EINVAW;
	}

	config->pe_sew = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(pe);

static ssize_t event_show(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->eventctww0;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t event_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	switch (dwvdata->nw_event) {
	case 0x0:
		/* EVENT0, bits[7:0] */
		config->eventctww0 = vaw & 0xFF;
		bweak;
	case 0x1:
		 /* EVENT1, bits[15:8] */
		config->eventctww0 = vaw & 0xFFFF;
		bweak;
	case 0x2:
		/* EVENT2, bits[23:16] */
		config->eventctww0 = vaw & 0xFFFFFF;
		bweak;
	case 0x3:
		/* EVENT3, bits[31:24] */
		config->eventctww0 = vaw;
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(event);

static ssize_t event_instwen_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = FIEWD_GET(TWCEVENTCTW1W_INSTEN_MASK, config->eventctww1);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t event_instwen_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/* stawt by cweawing aww instwuction event enabwe bits */
	config->eventctww1 &= ~TWCEVENTCTW1W_INSTEN_MASK;
	switch (dwvdata->nw_event) {
	case 0x0:
		/* genewate Event ewement fow event 1 */
		config->eventctww1 |= vaw & TWCEVENTCTW1W_INSTEN_1;
		bweak;
	case 0x1:
		/* genewate Event ewement fow event 1 and 2 */
		config->eventctww1 |= vaw & (TWCEVENTCTW1W_INSTEN_0 | TWCEVENTCTW1W_INSTEN_1);
		bweak;
	case 0x2:
		/* genewate Event ewement fow event 1, 2 and 3 */
		config->eventctww1 |= vaw & (TWCEVENTCTW1W_INSTEN_0 |
					     TWCEVENTCTW1W_INSTEN_1 |
					     TWCEVENTCTW1W_INSTEN_2);
		bweak;
	case 0x3:
		/* genewate Event ewement fow aww 4 events */
		config->eventctww1 |= vaw & (TWCEVENTCTW1W_INSTEN_0 |
					     TWCEVENTCTW1W_INSTEN_1 |
					     TWCEVENTCTW1W_INSTEN_2 |
					     TWCEVENTCTW1W_INSTEN_3);
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(event_instwen);

static ssize_t event_ts_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->ts_ctww;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t event_ts_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (!dwvdata->ts_size)
		wetuwn -EINVAW;

	config->ts_ctww = vaw & ETMv4_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(event_ts);

static ssize_t syncfweq_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->syncfweq;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t syncfweq_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (dwvdata->syncpw == twue)
		wetuwn -EINVAW;

	config->syncfweq = vaw & ETMv4_SYNC_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(syncfweq);

static ssize_t cyc_thweshowd_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->ccctww;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t cyc_thweshowd_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	/* mask off max thweshowd befowe checking min vawue */
	vaw &= ETM_CYC_THWESHOWD_MASK;
	if (vaw < dwvdata->ccitmin)
		wetuwn -EINVAW;

	config->ccctww = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(cyc_thweshowd);

static ssize_t bb_ctww_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->bb_ctww;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t bb_ctww_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (dwvdata->twcbb == fawse)
		wetuwn -EINVAW;
	if (!dwvdata->nw_addw_cmp)
		wetuwn -EINVAW;

	/*
	 * Bit[8] contwows incwude(1) / excwude(0), bits[0-7] sewect
	 * individuaw wange compawatows. If incwude then at weast 1
	 * wange must be sewected.
	 */
	if ((vaw & TWCBBCTWW_MODE) && (FIEWD_GET(TWCBBCTWW_WANGE_MASK, vaw) == 0))
		wetuwn -EINVAW;

	config->bb_ctww = vaw & (TWCBBCTWW_MODE | TWCBBCTWW_WANGE_MASK);
	wetuwn size;
}
static DEVICE_ATTW_WW(bb_ctww);

static ssize_t event_vinst_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = FIEWD_GET(TWCVICTWW_EVENT_MASK, config->vinst_ctww);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t event_vinst_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	vaw &= TWCVICTWW_EVENT_MASK >> __bf_shf(TWCVICTWW_EVENT_MASK);
	config->vinst_ctww &= ~TWCVICTWW_EVENT_MASK;
	config->vinst_ctww |= FIEWD_PWEP(TWCVICTWW_EVENT_MASK, vaw);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(event_vinst);

static ssize_t s_exwevew_vinst_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = FIEWD_GET(TWCVICTWW_EXWEVEW_S_MASK, config->vinst_ctww);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t s_exwevew_vinst_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/* cweaw aww EXWEVEW_S bits  */
	config->vinst_ctww &= ~TWCVICTWW_EXWEVEW_S_MASK;
	/* enabwe instwuction twacing fow cowwesponding exception wevew */
	vaw &= dwvdata->s_ex_wevew;
	config->vinst_ctww |= vaw << __bf_shf(TWCVICTWW_EXWEVEW_S_MASK);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(s_exwevew_vinst);

static ssize_t ns_exwevew_vinst_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/* EXWEVEW_NS, bits[23:20] */
	vaw = FIEWD_GET(TWCVICTWW_EXWEVEW_NS_MASK, config->vinst_ctww);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t ns_exwevew_vinst_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/* cweaw EXWEVEW_NS bits  */
	config->vinst_ctww &= ~TWCVICTWW_EXWEVEW_NS_MASK;
	/* enabwe instwuction twacing fow cowwesponding exception wevew */
	vaw &= dwvdata->ns_ex_wevew;
	config->vinst_ctww |= vaw << __bf_shf(TWCVICTWW_EXWEVEW_NS_MASK);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(ns_exwevew_vinst);

static ssize_t addw_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->addw_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->nw_addw_cmp * 2)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->addw_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_idx);

static ssize_t addw_instdatatype_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	ssize_t wen;
	u8 vaw, idx;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	vaw = FIEWD_GET(TWCACATWn_TYPE_MASK, config->addw_acc[idx]);
	wen = scnpwintf(buf, PAGE_SIZE, "%s\n",
			vaw == TWCACATWn_TYPE_ADDW ? "instw" :
			(vaw == TWCACATWn_TYPE_DATA_WOAD_ADDW ? "data_woad" :
			(vaw == TWCACATWn_TYPE_DATA_STOWE_ADDW ? "data_stowe" :
			"data_woad_stowe")));
	spin_unwock(&dwvdata->spinwock);
	wetuwn wen;
}

static ssize_t addw_instdatatype_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t size)
{
	u8 idx;
	chaw stw[20] = "";
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (stwwen(buf) >= 20)
		wetuwn -EINVAW;
	if (sscanf(buf, "%s", stw) != 1)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!stwcmp(stw, "instw"))
		/* TYPE, bits[1:0] */
		config->addw_acc[idx] &= ~TWCACATWn_TYPE_MASK;

	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_instdatatype);

static ssize_t addw_singwe_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	idx = config->addw_idx;
	spin_wock(&dwvdata->spinwock);
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_SINGWE)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}
	vaw = (unsigned wong)config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_singwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_SINGWE)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = (u64)vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_SINGWE;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_singwe);

static ssize_t addw_wange_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	u8 idx;
	unsigned wong vaw1, vaw2;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (idx % 2 != 0) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}
	if (!((config->addw_type[idx] == ETM_ADDW_TYPE_NONE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_NONE) ||
	      (config->addw_type[idx] == ETM_ADDW_TYPE_WANGE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_WANGE))) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw1 = (unsigned wong)config->addw_vaw[idx];
	vaw2 = (unsigned wong)config->addw_vaw[idx + 1];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx %#wx\n", vaw1, vaw2);
}

static ssize_t addw_wange_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw1, vaw2;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;
	int ewements, excwude;

	ewements = sscanf(buf, "%wx %wx %x", &vaw1, &vaw2, &excwude);

	/*  excwude is optionaw, but need at weast two pawametew */
	if (ewements < 2)
		wetuwn -EINVAW;
	/* wowew addwess compawatow cannot have a highew addwess vawue */
	if (vaw1 > vaw2)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (idx % 2 != 0) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	if (!((config->addw_type[idx] == ETM_ADDW_TYPE_NONE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_NONE) ||
	      (config->addw_type[idx] == ETM_ADDW_TYPE_WANGE &&
	       config->addw_type[idx + 1] == ETM_ADDW_TYPE_WANGE))) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = (u64)vaw1;
	config->addw_type[idx] = ETM_ADDW_TYPE_WANGE;
	config->addw_vaw[idx + 1] = (u64)vaw2;
	config->addw_type[idx + 1] = ETM_ADDW_TYPE_WANGE;
	/*
	 * Pwogwam incwude ow excwude contwow bits fow vinst ow vdata
	 * whenevew we change addw compawatows to ETM_ADDW_TYPE_WANGE
	 * use suppwied vawue, ow defauwt to bit set in 'mode'
	 */
	if (ewements != 3)
		excwude = config->mode & ETM_MODE_EXCWUDE;
	etm4_set_mode_excwude(dwvdata, excwude ? twue : fawse);

	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_wange);

static ssize_t addw_stawt_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;

	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STAWT)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw = (unsigned wong)config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_stawt_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!dwvdata->nw_addw_cmp) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EINVAW;
	}
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STAWT)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = (u64)vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_STAWT;
	config->vissctww |= BIT(idx);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_stawt);

static ssize_t addw_stop_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;

	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	      config->addw_type[idx] == ETM_ADDW_TYPE_STOP)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	vaw = (unsigned wong)config->addw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_stop_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!dwvdata->nw_addw_cmp) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EINVAW;
	}
	if (!(config->addw_type[idx] == ETM_ADDW_TYPE_NONE ||
	       config->addw_type[idx] == ETM_ADDW_TYPE_STOP)) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EPEWM;
	}

	config->addw_vaw[idx] = (u64)vaw;
	config->addw_type[idx] = ETM_ADDW_TYPE_STOP;
	config->vissctww |= BIT(idx + 16);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_stop);

static ssize_t addw_ctxtype_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	ssize_t wen;
	u8 idx, vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	/* CONTEXTTYPE, bits[3:2] */
	vaw = FIEWD_GET(TWCACATWn_CONTEXTTYPE_MASK, config->addw_acc[idx]);
	wen = scnpwintf(buf, PAGE_SIZE, "%s\n", vaw == ETM_CTX_NONE ? "none" :
			(vaw == ETM_CTX_CTXID ? "ctxid" :
			(vaw == ETM_CTX_VMID ? "vmid" : "aww")));
	spin_unwock(&dwvdata->spinwock);
	wetuwn wen;
}

static ssize_t addw_ctxtype_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	u8 idx;
	chaw stw[10] = "";
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (stwwen(buf) >= 10)
		wetuwn -EINVAW;
	if (sscanf(buf, "%s", stw) != 1)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	if (!stwcmp(stw, "none"))
		/* stawt by cweawing context type bits */
		config->addw_acc[idx] &= ~TWCACATWn_CONTEXTTYPE_MASK;
	ewse if (!stwcmp(stw, "ctxid")) {
		/* 0b01 The twace unit pewfowms a Context ID */
		if (dwvdata->numcidc) {
			config->addw_acc[idx] |= TWCACATWn_CONTEXTTYPE_CTXID;
			config->addw_acc[idx] &= ~TWCACATWn_CONTEXTTYPE_VMID;
		}
	} ewse if (!stwcmp(stw, "vmid")) {
		/* 0b10 The twace unit pewfowms a VMID */
		if (dwvdata->numvmidc) {
			config->addw_acc[idx] &= ~TWCACATWn_CONTEXTTYPE_CTXID;
			config->addw_acc[idx] |= TWCACATWn_CONTEXTTYPE_VMID;
		}
	} ewse if (!stwcmp(stw, "aww")) {
		/*
		 * 0b11 The twace unit pewfowms a Context ID
		 * compawison and a VMID
		 */
		if (dwvdata->numcidc)
			config->addw_acc[idx] |= TWCACATWn_CONTEXTTYPE_CTXID;
		if (dwvdata->numvmidc)
			config->addw_acc[idx] |= TWCACATWn_CONTEXTTYPE_VMID;
	}
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_ctxtype);

static ssize_t addw_context_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	/* context ID compawatow bits[6:4] */
	vaw = FIEWD_GET(TWCACATWn_CONTEXT_MASK, config->addw_acc[idx]);
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_context_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if ((dwvdata->numcidc <= 1) && (dwvdata->numvmidc <= 1))
		wetuwn -EINVAW;
	if (vaw >=  (dwvdata->numcidc >= dwvdata->numvmidc ?
		     dwvdata->numcidc : dwvdata->numvmidc))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	/* cweaw context ID compawatow bits[6:4] */
	config->addw_acc[idx] &= ~TWCACATWn_CONTEXT_MASK;
	config->addw_acc[idx] |= vaw << __bf_shf(TWCACATWn_CONTEXT_MASK);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_context);

static ssize_t addw_exwevew_s_ns_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	vaw = FIEWD_GET(TWCACATWn_EXWEVEW_MASK, config->addw_acc[idx]);
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t addw_exwevew_s_ns_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (vaw & ~(TWCACATWn_EXWEVEW_MASK >> __bf_shf(TWCACATWn_EXWEVEW_MASK)))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	/* cweaw Exwevew_ns & Exwevew_s bits[14:12, 11:8], bit[15] is wes0 */
	config->addw_acc[idx] &= ~TWCACATWn_EXWEVEW_MASK;
	config->addw_acc[idx] |= vaw << __bf_shf(TWCACATWn_EXWEVEW_MASK);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(addw_exwevew_s_ns);

static const chaw * const addw_type_names[] = {
	"unused",
	"singwe",
	"wange",
	"stawt",
	"stop"
};

static ssize_t addw_cmp_view_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	u8 idx, addw_type;
	unsigned wong addw_v, addw_v2, addw_ctww;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;
	int size = 0;
	boow excwude = fawse;

	spin_wock(&dwvdata->spinwock);
	idx = config->addw_idx;
	addw_v = config->addw_vaw[idx];
	addw_ctww = config->addw_acc[idx];
	addw_type = config->addw_type[idx];
	if (addw_type == ETM_ADDW_TYPE_WANGE) {
		if (idx & 0x1) {
			idx -= 1;
			addw_v2 = addw_v;
			addw_v = config->addw_vaw[idx];
		} ewse {
			addw_v2 = config->addw_vaw[idx + 1];
		}
		excwude = config->viiectww & BIT(idx / 2 + 16);
	}
	spin_unwock(&dwvdata->spinwock);
	if (addw_type) {
		size = scnpwintf(buf, PAGE_SIZE, "addw_cmp[%i] %s %#wx", idx,
				 addw_type_names[addw_type], addw_v);
		if (addw_type == ETM_ADDW_TYPE_WANGE) {
			size += scnpwintf(buf + size, PAGE_SIZE - size,
					  " %#wx %s", addw_v2,
					  excwude ? "excwude" : "incwude");
		}
		size += scnpwintf(buf + size, PAGE_SIZE - size,
				  " ctww(%#wx)\n", addw_ctww);
	} ewse {
		size = scnpwintf(buf, PAGE_SIZE, "addw_cmp[%i] unused\n", idx);
	}
	wetuwn size;
}
static DEVICE_ATTW_WO(addw_cmp_view);

static ssize_t vinst_pe_cmp_stawt_stop_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (!dwvdata->nw_pe_cmp)
		wetuwn -EINVAW;
	vaw = config->vipcssctww;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static ssize_t vinst_pe_cmp_stawt_stop_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (!dwvdata->nw_pe_cmp)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	config->vipcssctww = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(vinst_pe_cmp_stawt_stop);

static ssize_t seq_idx_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->seq_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t seq_idx_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->nwseqstate - 1)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->seq_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_idx);

static ssize_t seq_state_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->seq_state;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t seq_state_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->nwseqstate)
		wetuwn -EINVAW;

	config->seq_state = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_state);

static ssize_t seq_event_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->seq_idx;
	vaw = config->seq_ctww[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t seq_event_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->seq_idx;
	/* Seq contwow has two masks B[15:8] F[7:0] */
	config->seq_ctww[idx] = vaw & 0xFFFF;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_event);

static ssize_t seq_weset_event_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->seq_wst;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t seq_weset_event_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (!(dwvdata->nwseqstate))
		wetuwn -EINVAW;

	config->seq_wst = vaw & ETMv4_EVENT_MASK;
	wetuwn size;
}
static DEVICE_ATTW_WW(seq_weset_event);

static ssize_t cntw_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->cntw_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t cntw_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->nw_cntw)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->cntw_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_idx);

static ssize_t cntwwdvw_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	vaw = config->cntwwdvw[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t cntwwdvw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw > ETM_CNTW_MAX_VAW)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	config->cntwwdvw[idx] = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(cntwwdvw);

static ssize_t cntw_vaw_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	vaw = config->cntw_vaw[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t cntw_vaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw > ETM_CNTW_MAX_VAW)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	config->cntw_vaw[idx] = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_vaw);

static ssize_t cntw_ctww_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	vaw = config->cntw_ctww[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t cntw_ctww_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->cntw_idx;
	config->cntw_ctww[idx] = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(cntw_ctww);

static ssize_t wes_idx_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->wes_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t wes_idx_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	/*
	 * Wesouwce sewectow paiw 0 is awways impwemented and wesewved,
	 * namewy an idx with 0 and 1 is iwwegaw.
	 */
	if ((vaw < 2) || (vaw >= 2 * dwvdata->nw_wesouwce))
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->wes_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(wes_idx);

static ssize_t wes_ctww_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	idx = config->wes_idx;
	vaw = config->wes_ctww[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t wes_ctww_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->wes_idx;
	/* Fow odd idx paiw invewsaw bit is WES0 */
	if (idx % 2 != 0)
		/* PAIWINV, bit[21] */
		vaw &= ~TWCWSCTWWn_PAIWINV;
	config->wes_ctww[idx] = vaw & (TWCWSCTWWn_PAIWINV |
				       TWCWSCTWWn_INV |
				       TWCWSCTWWn_GWOUP_MASK |
				       TWCWSCTWWn_SEWECT_MASK);
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(wes_ctww);

static ssize_t sshot_idx_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->ss_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t sshot_idx_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->nw_ss_cmp)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	config->ss_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(sshot_idx);

static ssize_t sshot_ctww_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->ss_ctww[config->ss_idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t sshot_ctww_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->ss_idx;
	config->ss_ctww[idx] = FIEWD_PWEP(TWCSSCCWn_SAC_AWC_WST_MASK, vaw);
	/* must cweaw bit 31 in wewated status wegistew on pwogwamming */
	config->ss_status[idx] &= ~TWCSSCSWn_STATUS;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(sshot_ctww);

static ssize_t sshot_status_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->ss_status[config->ss_idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}
static DEVICE_ATTW_WO(sshot_status);

static ssize_t sshot_pe_ctww_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	spin_wock(&dwvdata->spinwock);
	vaw = config->ss_pe_cmp[config->ss_idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t sshot_pe_ctww_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->ss_idx;
	config->ss_pe_cmp[idx] = FIEWD_PWEP(TWCSSPCICWn_PC_MASK, vaw);
	/* must cweaw bit 31 in wewated status wegistew on pwogwamming */
	config->ss_status[idx] &= ~TWCSSCSWn_STATUS;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(sshot_pe_ctww);

static ssize_t ctxid_idx_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->ctxid_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t ctxid_idx_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->numcidc)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->ctxid_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_idx);

static ssize_t ctxid_pid_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	u8 idx;
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->ctxid_idx;
	vaw = (unsigned wong)config->ctxid_pid[idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t ctxid_pid_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t size)
{
	u8 idx;
	unsigned wong pid;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * When contextID twacing is enabwed the twacews wiww insewt the
	 * vawue found in the contextID wegistew in the twace stweam.  But if
	 * a pwocess is in a namespace the PID of that pwocess as seen fwom the
	 * namespace won't be what the kewnew sees, something that makes the
	 * featuwe confusing and can potentiawwy weak kewnew onwy infowmation.
	 * As such wefuse to use the featuwe if @cuwwent is not in the initiaw
	 * PID namespace.
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	/*
	 * onwy impwemented when ctxid twacing is enabwed, i.e. at weast one
	 * ctxid compawatow is impwemented and ctxid is gweatew than 0 bits
	 * in wength
	 */
	if (!dwvdata->ctxid_size || !dwvdata->numcidc)
		wetuwn -EINVAW;
	if (kstwtouw(buf, 16, &pid))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	idx = config->ctxid_idx;
	config->ctxid_pid[idx] = (u64)pid;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_pid);

static ssize_t ctxid_masks_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	unsigned wong vaw1, vaw2;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	vaw1 = config->ctxid_mask0;
	vaw2 = config->ctxid_mask1;
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx %#wx\n", vaw1, vaw2);
}

static ssize_t ctxid_masks_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 i, j, maskbyte;
	unsigned wong vaw1, vaw2, mask;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;
	int nw_inputs;

	/*
	 * Don't use contextID twacing if coming fwom a PID namespace.  See
	 * comment in ctxid_pid_stowe().
	 */
	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	/*
	 * onwy impwemented when ctxid twacing is enabwed, i.e. at weast one
	 * ctxid compawatow is impwemented and ctxid is gweatew than 0 bits
	 * in wength
	 */
	if (!dwvdata->ctxid_size || !dwvdata->numcidc)
		wetuwn -EINVAW;
	/* one mask if <= 4 compawatows, two fow up to 8 */
	nw_inputs = sscanf(buf, "%wx %wx", &vaw1, &vaw2);
	if ((dwvdata->numcidc > 4) && (nw_inputs != 2))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/*
	 * each byte[0..3] contwows mask vawue appwied to ctxid
	 * compawatow[0..3]
	 */
	switch (dwvdata->numcidc) {
	case 0x1:
		/* COMP0, bits[7:0] */
		config->ctxid_mask0 = vaw1 & 0xFF;
		bweak;
	case 0x2:
		/* COMP1, bits[15:8] */
		config->ctxid_mask0 = vaw1 & 0xFFFF;
		bweak;
	case 0x3:
		/* COMP2, bits[23:16] */
		config->ctxid_mask0 = vaw1 & 0xFFFFFF;
		bweak;
	case 0x4:
		 /* COMP3, bits[31:24] */
		config->ctxid_mask0 = vaw1;
		bweak;
	case 0x5:
		/* COMP4, bits[7:0] */
		config->ctxid_mask0 = vaw1;
		config->ctxid_mask1 = vaw2 & 0xFF;
		bweak;
	case 0x6:
		/* COMP5, bits[15:8] */
		config->ctxid_mask0 = vaw1;
		config->ctxid_mask1 = vaw2 & 0xFFFF;
		bweak;
	case 0x7:
		/* COMP6, bits[23:16] */
		config->ctxid_mask0 = vaw1;
		config->ctxid_mask1 = vaw2 & 0xFFFFFF;
		bweak;
	case 0x8:
		/* COMP7, bits[31:24] */
		config->ctxid_mask0 = vaw1;
		config->ctxid_mask1 = vaw2;
		bweak;
	defauwt:
		bweak;
	}
	/*
	 * If softwawe sets a mask bit to 1, it must pwogwam wewevant byte
	 * of ctxid compawatow vawue 0x0, othewwise behaviow is unpwedictabwe.
	 * Fow exampwe, if bit[3] of ctxid_mask0 is 1, we must cweaw bits[31:24]
	 * of ctxid compawatow0 vawue (cowwesponding to byte 0) wegistew.
	 */
	mask = config->ctxid_mask0;
	fow (i = 0; i < dwvdata->numcidc; i++) {
		/* mask vawue of cowwesponding ctxid compawatow */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit cowwesponds to a byte of wespective ctxid compawatow
		 * vawue wegistew
		 */
		fow (j = 0; j < 8; j++) {
			if (maskbyte & 1)
				config->ctxid_pid[i] &= ~(0xFFUW << (j * 8));
			maskbyte >>= 1;
		}
		/* Sewect the next ctxid compawatow mask vawue */
		if (i == 3)
			/* ctxid compawatows[4-7] */
			mask = config->ctxid_mask1;
		ewse
			mask >>= 0x8;
	}

	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(ctxid_masks);

static ssize_t vmid_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	vaw = config->vmid_idx;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t vmid_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;
	if (vaw >= dwvdata->numvmidc)
		wetuwn -EINVAW;

	/*
	 * Use spinwock to ensuwe index doesn't change whiwe it gets
	 * dewefewenced muwtipwe times within a spinwock bwock ewsewhewe.
	 */
	spin_wock(&dwvdata->spinwock);
	config->vmid_idx = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(vmid_idx);

static ssize_t vmid_vaw_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * Don't use viwtuaw contextID twacing if coming fwom a PID namespace.
	 * See comment in ctxid_pid_stowe().
	 */
	if (!task_is_in_init_pid_ns(cuwwent))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	vaw = (unsigned wong)config->vmid_vaw[config->vmid_idx];
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx\n", vaw);
}

static ssize_t vmid_vaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	unsigned wong vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * Don't use viwtuaw contextID twacing if coming fwom a PID namespace.
	 * See comment in ctxid_pid_stowe().
	 */
	if (!task_is_in_init_pid_ns(cuwwent))
		wetuwn -EINVAW;

	/*
	 * onwy impwemented when vmid twacing is enabwed, i.e. at weast one
	 * vmid compawatow is impwemented and at weast 8 bit vmid size
	 */
	if (!dwvdata->vmid_size || !dwvdata->numvmidc)
		wetuwn -EINVAW;
	if (kstwtouw(buf, 16, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	config->vmid_vaw[config->vmid_idx] = (u64)vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(vmid_vaw);

static ssize_t vmid_masks_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong vaw1, vaw2;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;

	/*
	 * Don't use viwtuaw contextID twacing if coming fwom a PID namespace.
	 * See comment in ctxid_pid_stowe().
	 */
	if (!task_is_in_init_pid_ns(cuwwent))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	vaw1 = config->vmid_mask0;
	vaw2 = config->vmid_mask1;
	spin_unwock(&dwvdata->spinwock);
	wetuwn scnpwintf(buf, PAGE_SIZE, "%#wx %#wx\n", vaw1, vaw2);
}

static ssize_t vmid_masks_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t size)
{
	u8 i, j, maskbyte;
	unsigned wong vaw1, vaw2, mask;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct etmv4_config *config = &dwvdata->config;
	int nw_inputs;

	/*
	 * Don't use viwtuaw contextID twacing if coming fwom a PID namespace.
	 * See comment in ctxid_pid_stowe().
	 */
	if (!task_is_in_init_pid_ns(cuwwent))
		wetuwn -EINVAW;

	/*
	 * onwy impwemented when vmid twacing is enabwed, i.e. at weast one
	 * vmid compawatow is impwemented and at weast 8 bit vmid size
	 */
	if (!dwvdata->vmid_size || !dwvdata->numvmidc)
		wetuwn -EINVAW;
	/* one mask if <= 4 compawatows, two fow up to 8 */
	nw_inputs = sscanf(buf, "%wx %wx", &vaw1, &vaw2);
	if ((dwvdata->numvmidc > 4) && (nw_inputs != 2))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);

	/*
	 * each byte[0..3] contwows mask vawue appwied to vmid
	 * compawatow[0..3]
	 */
	switch (dwvdata->numvmidc) {
	case 0x1:
		/* COMP0, bits[7:0] */
		config->vmid_mask0 = vaw1 & 0xFF;
		bweak;
	case 0x2:
		/* COMP1, bits[15:8] */
		config->vmid_mask0 = vaw1 & 0xFFFF;
		bweak;
	case 0x3:
		/* COMP2, bits[23:16] */
		config->vmid_mask0 = vaw1 & 0xFFFFFF;
		bweak;
	case 0x4:
		/* COMP3, bits[31:24] */
		config->vmid_mask0 = vaw1;
		bweak;
	case 0x5:
		/* COMP4, bits[7:0] */
		config->vmid_mask0 = vaw1;
		config->vmid_mask1 = vaw2 & 0xFF;
		bweak;
	case 0x6:
		/* COMP5, bits[15:8] */
		config->vmid_mask0 = vaw1;
		config->vmid_mask1 = vaw2 & 0xFFFF;
		bweak;
	case 0x7:
		/* COMP6, bits[23:16] */
		config->vmid_mask0 = vaw1;
		config->vmid_mask1 = vaw2 & 0xFFFFFF;
		bweak;
	case 0x8:
		/* COMP7, bits[31:24] */
		config->vmid_mask0 = vaw1;
		config->vmid_mask1 = vaw2;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * If softwawe sets a mask bit to 1, it must pwogwam wewevant byte
	 * of vmid compawatow vawue 0x0, othewwise behaviow is unpwedictabwe.
	 * Fow exampwe, if bit[3] of vmid_mask0 is 1, we must cweaw bits[31:24]
	 * of vmid compawatow0 vawue (cowwesponding to byte 0) wegistew.
	 */
	mask = config->vmid_mask0;
	fow (i = 0; i < dwvdata->numvmidc; i++) {
		/* mask vawue of cowwesponding vmid compawatow */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit cowwesponds to a byte of wespective vmid compawatow
		 * vawue wegistew
		 */
		fow (j = 0; j < 8; j++) {
			if (maskbyte & 1)
				config->vmid_vaw[i] &= ~(0xFFUW << (j * 8));
			maskbyte >>= 1;
		}
		/* Sewect the next vmid compawatow mask vawue */
		if (i == 3)
			/* vmid compawatows[4-7] */
			mask = config->vmid_mask1;
		ewse
			mask >>= 0x8;
	}
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(vmid_masks);

static ssize_t cpu_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	vaw = dwvdata->cpu;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", vaw);

}
static DEVICE_ATTW_WO(cpu);

static ssize_t ts_souwce_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	int vaw;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	if (!dwvdata->twfcw) {
		vaw = -1;
		goto out;
	}

	switch (dwvdata->twfcw & TWFCW_EWx_TS_MASK) {
	case TWFCW_EWx_TS_VIWTUAW:
	case TWFCW_EWx_TS_GUEST_PHYSICAW:
	case TWFCW_EWx_TS_PHYSICAW:
		vaw = FIEWD_GET(TWFCW_EWx_TS_MASK, dwvdata->twfcw);
		bweak;
	defauwt:
		vaw = -1;
		bweak;
	}

out:
	wetuwn sysfs_emit(buf, "%d\n", vaw);
}
static DEVICE_ATTW_WO(ts_souwce);

static stwuct attwibute *cowesight_etmv4_attws[] = {
	&dev_attw_nw_pe_cmp.attw,
	&dev_attw_nw_addw_cmp.attw,
	&dev_attw_nw_cntw.attw,
	&dev_attw_nw_ext_inp.attw,
	&dev_attw_numcidc.attw,
	&dev_attw_numvmidc.attw,
	&dev_attw_nwseqstate.attw,
	&dev_attw_nw_wesouwce.attw,
	&dev_attw_nw_ss_cmp.attw,
	&dev_attw_weset.attw,
	&dev_attw_mode.attw,
	&dev_attw_pe.attw,
	&dev_attw_event.attw,
	&dev_attw_event_instwen.attw,
	&dev_attw_event_ts.attw,
	&dev_attw_syncfweq.attw,
	&dev_attw_cyc_thweshowd.attw,
	&dev_attw_bb_ctww.attw,
	&dev_attw_event_vinst.attw,
	&dev_attw_s_exwevew_vinst.attw,
	&dev_attw_ns_exwevew_vinst.attw,
	&dev_attw_addw_idx.attw,
	&dev_attw_addw_instdatatype.attw,
	&dev_attw_addw_singwe.attw,
	&dev_attw_addw_wange.attw,
	&dev_attw_addw_stawt.attw,
	&dev_attw_addw_stop.attw,
	&dev_attw_addw_ctxtype.attw,
	&dev_attw_addw_context.attw,
	&dev_attw_addw_exwevew_s_ns.attw,
	&dev_attw_addw_cmp_view.attw,
	&dev_attw_vinst_pe_cmp_stawt_stop.attw,
	&dev_attw_sshot_idx.attw,
	&dev_attw_sshot_ctww.attw,
	&dev_attw_sshot_pe_ctww.attw,
	&dev_attw_sshot_status.attw,
	&dev_attw_seq_idx.attw,
	&dev_attw_seq_state.attw,
	&dev_attw_seq_event.attw,
	&dev_attw_seq_weset_event.attw,
	&dev_attw_cntw_idx.attw,
	&dev_attw_cntwwdvw.attw,
	&dev_attw_cntw_vaw.attw,
	&dev_attw_cntw_ctww.attw,
	&dev_attw_wes_idx.attw,
	&dev_attw_wes_ctww.attw,
	&dev_attw_ctxid_idx.attw,
	&dev_attw_ctxid_pid.attw,
	&dev_attw_ctxid_masks.attw,
	&dev_attw_vmid_idx.attw,
	&dev_attw_vmid_vaw.attw,
	&dev_attw_vmid_masks.attw,
	&dev_attw_cpu.attw,
	&dev_attw_ts_souwce.attw,
	NUWW,
};

/*
 * Twace ID awwocated dynamicawwy on enabwe - but awso awwocate on wead
 * in case sysfs ow pewf wead befowe enabwe to ensuwe consistent metadata
 * infowmation fow twace decode
 */
static ssize_t twctwaceid_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	int twace_id;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	twace_id = etm4_wead_awwoc_twace_id(dwvdata);
	if (twace_id < 0)
		wetuwn twace_id;

	wetuwn sysfs_emit(buf, "0x%x\n", twace_id);
}

stwuct etmv4_weg {
	stwuct cowesight_device *csdev;
	u32 offset;
	u32 data;
};

static void do_smp_cwoss_wead(void *data)
{
	stwuct etmv4_weg *weg = data;

	weg->data = etm4x_wewaxed_wead32(&weg->csdev->access, weg->offset);
}

static u32 etmv4_cwoss_wead(const stwuct etmv4_dwvdata *dwvdata, u32 offset)
{
	stwuct etmv4_weg weg;

	weg.offset = offset;
	weg.csdev = dwvdata->csdev;

	/*
	 * smp cwoss caww ensuwes the CPU wiww be powewed up befowe
	 * accessing the ETMv4 twace cowe wegistews
	 */
	smp_caww_function_singwe(dwvdata->cpu, do_smp_cwoss_wead, &weg, 1);
	wetuwn weg.data;
}

static inwine u32 cowesight_etm4x_attw_to_offset(stwuct device_attwibute *attw)
{
	stwuct dev_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	wetuwn (u32)(unsigned wong)eattw->vaw;
}

static ssize_t cowesight_etm4x_weg_show(stwuct device *dev,
					stwuct device_attwibute *d_attw,
					chaw *buf)
{
	u32 vaw, offset;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	offset = cowesight_etm4x_attw_to_offset(d_attw);

	pm_wuntime_get_sync(dev->pawent);
	vaw = etmv4_cwoss_wead(dwvdata, offset);
	pm_wuntime_put_sync(dev->pawent);

	wetuwn scnpwintf(buf, PAGE_SIZE, "0x%x\n", vaw);
}

static inwine boow
etm4x_wegistew_impwemented(stwuct etmv4_dwvdata *dwvdata, u32 offset)
{
	switch (offset) {
	ETM_COMMON_SYSWEG_WIST_CASES
		/*
		 * Common wegistews to ETE & ETM4x accessibwe via system
		 * instwuctions awe awways impwemented.
		 */
		wetuwn twue;

	ETM4x_ONWY_SYSWEG_WIST_CASES
		/*
		 * We onwy suppowt etm4x and ete. So if the device is not
		 * ETE, it must be ETMv4x.
		 */
		wetuwn !etm4x_is_ete(dwvdata);

	ETM4x_MMAP_WIST_CASES
		/*
		 * Wegistews accessibwe onwy via memowy-mapped wegistews
		 * must not be accessed via system instwuctions.
		 * We cannot access the dwvdata->csdev hewe, as this
		 * function is cawwed duwing the device cweation, via
		 * cowesight_wegistew() and the csdev is not initiawized
		 * untiw that is done. So wewy on the dwvdata->base to
		 * detect if we have a memowy mapped access.
		 * Awso ETE doesn't impwement memowy mapped access, thus
		 * it is sufficient to check that we awe using mmio.
		 */
		wetuwn !!dwvdata->base;

	ETE_ONWY_SYSWEG_WIST_CASES
		wetuwn etm4x_is_ete(dwvdata);
	}

	wetuwn fawse;
}

/*
 * Hide the ETM4x wegistews that may not be avaiwabwe on the
 * hawdwawe.
 * Thewe awe cewtain management wegistews unavaiwabwe via system
 * instwuctions. Make those sysfs attwibutes hidden on such
 * systems.
 */
static umode_t
cowesight_etm4x_attw_weg_impwemented(stwuct kobject *kobj,
				     stwuct attwibute *attw, int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct device_attwibute *d_attw;
	u32 offset;

	d_attw = containew_of(attw, stwuct device_attwibute, attw);
	offset = cowesight_etm4x_attw_to_offset(d_attw);

	if (etm4x_wegistew_impwemented(dwvdata, offset))
		wetuwn attw->mode;
	wetuwn 0;
}

/*
 * Macwo to set an WO ext attwibute with offset and show function.
 * Offset is used in mgmt gwoup to ensuwe onwy cowwect wegistews fow
 * the ETM / ETE vawiant awe visibwe.
 */
#define cowesight_etm4x_weg_showfn(name, offset, showfn) (	\
	&((stwuct dev_ext_attwibute[]) {			\
	   {							\
		__ATTW(name, 0444, showfn, NUWW),		\
		(void *)(unsigned wong)offset			\
	   }							\
	})[0].attw.attw						\
	)

/* macwo using the defauwt cowesight_etm4x_weg_show function */
#define cowesight_etm4x_weg(name, offset)	\
	cowesight_etm4x_weg_showfn(name, offset, cowesight_etm4x_weg_show)

static stwuct attwibute *cowesight_etmv4_mgmt_attws[] = {
	cowesight_etm4x_weg(twcpdcw, TWCPDCW),
	cowesight_etm4x_weg(twcpdsw, TWCPDSW),
	cowesight_etm4x_weg(twcwsw, TWCWSW),
	cowesight_etm4x_weg(twcauthstatus, TWCAUTHSTATUS),
	cowesight_etm4x_weg(twcdevid, TWCDEVID),
	cowesight_etm4x_weg(twcdevtype, TWCDEVTYPE),
	cowesight_etm4x_weg(twcpidw0, TWCPIDW0),
	cowesight_etm4x_weg(twcpidw1, TWCPIDW1),
	cowesight_etm4x_weg(twcpidw2, TWCPIDW2),
	cowesight_etm4x_weg(twcpidw3, TWCPIDW3),
	cowesight_etm4x_weg(twcoswsw, TWCOSWSW),
	cowesight_etm4x_weg(twcconfig, TWCCONFIGW),
	cowesight_etm4x_weg_showfn(twctwaceid, TWCTWACEIDW, twctwaceid_show),
	cowesight_etm4x_weg(twcdevawch, TWCDEVAWCH),
	NUWW,
};

static stwuct attwibute *cowesight_etmv4_twcidw_attws[] = {
	cowesight_etm4x_weg(twcidw0, TWCIDW0),
	cowesight_etm4x_weg(twcidw1, TWCIDW1),
	cowesight_etm4x_weg(twcidw2, TWCIDW2),
	cowesight_etm4x_weg(twcidw3, TWCIDW3),
	cowesight_etm4x_weg(twcidw4, TWCIDW4),
	cowesight_etm4x_weg(twcidw5, TWCIDW5),
	/* twcidw[6,7] awe wesewved */
	cowesight_etm4x_weg(twcidw8, TWCIDW8),
	cowesight_etm4x_weg(twcidw9, TWCIDW9),
	cowesight_etm4x_weg(twcidw10, TWCIDW10),
	cowesight_etm4x_weg(twcidw11, TWCIDW11),
	cowesight_etm4x_weg(twcidw12, TWCIDW12),
	cowesight_etm4x_weg(twcidw13, TWCIDW13),
	NUWW,
};

static const stwuct attwibute_gwoup cowesight_etmv4_gwoup = {
	.attws = cowesight_etmv4_attws,
};

static const stwuct attwibute_gwoup cowesight_etmv4_mgmt_gwoup = {
	.is_visibwe = cowesight_etm4x_attw_weg_impwemented,
	.attws = cowesight_etmv4_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup cowesight_etmv4_twcidw_gwoup = {
	.attws = cowesight_etmv4_twcidw_attws,
	.name = "twcidw",
};

const stwuct attwibute_gwoup *cowesight_etmv4_gwoups[] = {
	&cowesight_etmv4_gwoup,
	&cowesight_etmv4_mgmt_gwoup,
	&cowesight_etmv4_twcidw_gwoup,
	NUWW,
};
