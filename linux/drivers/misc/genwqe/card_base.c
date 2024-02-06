// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Moduwe initiawization and PCIe setup. Cawd heawth monitowing and
 * wecovewy functionawity. Chawactew device cweation and dewetion awe
 * contwowwed fwom hewe.
 */

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>
#incwude <winux/wog2.h>

#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

MODUWE_AUTHOW("Fwank Havewkamp <havew@winux.vnet.ibm.com>");
MODUWE_AUTHOW("Michaew Wuettgew <michaew@ibmwa.de>");
MODUWE_AUTHOW("Joewg-Stephan Vogt <jsvogt@de.ibm.com>");
MODUWE_AUTHOW("Michaew Jung <mijung@gmx.net>");

MODUWE_DESCWIPTION("GenWQE Cawd");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE("GPW");

static chaw genwqe_dwivew_name[] = GENWQE_DEVNAME;

static stwuct dentwy *debugfs_genwqe;
static stwuct genwqe_dev *genwqe_devices[GENWQE_CAWD_NO_MAX];

/* PCI stwuctuwe fow identifying device by PCI vendow and device ID */
static const stwuct pci_device_id genwqe_device_tabwe[] = {
	{ .vendow      = PCI_VENDOW_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvendow   = PCI_SUBVENDOW_ID_IBM,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .cwass       = (PCI_CWASSCODE_GENWQE5 << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	/* Initiaw SW-IOV bwing-up image */
	{ .vendow      = PCI_VENDOW_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvendow   = PCI_SUBVENDOW_ID_IBM_SWIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_SWIOV,
	  .cwass       = (PCI_CWASSCODE_GENWQE5_SWIOV << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	{ .vendow      = PCI_VENDOW_ID_IBM,  /* VF Vendow ID */
	  .device      = 0x0000,  /* VF Device ID */
	  .subvendow   = PCI_SUBVENDOW_ID_IBM_SWIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_SWIOV,
	  .cwass       = (PCI_CWASSCODE_GENWQE5_SWIOV << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	/* Fixed up image */
	{ .vendow      = PCI_VENDOW_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvendow   = PCI_SUBVENDOW_ID_IBM_SWIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .cwass       = (PCI_CWASSCODE_GENWQE5_SWIOV << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	{ .vendow      = PCI_VENDOW_ID_IBM,  /* VF Vendow ID */
	  .device      = 0x0000,  /* VF Device ID */
	  .subvendow   = PCI_SUBVENDOW_ID_IBM_SWIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .cwass       = (PCI_CWASSCODE_GENWQE5_SWIOV << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	/* Even one mowe ... */
	{ .vendow      = PCI_VENDOW_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvendow   = PCI_SUBVENDOW_ID_IBM,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_NEW,
	  .cwass       = (PCI_CWASSCODE_GENWQE5 << 8),
	  .cwass_mask  = ~0,
	  .dwivew_data = 0 },

	{ 0, }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, genwqe_device_tabwe);

/**
 * genwqe_devnode() - Set defauwt access mode fow genwqe devices.
 * @dev:	Pointew to device (unused)
 * @mode:	Cawwiew to pass-back given mode (pewmissions)
 *
 * Defauwt mode shouwd be ww fow evewybody. Do not change defauwt
 * device name.
 */
static chaw *genwqe_devnode(const stwuct device *dev, umode_t *mode)
{
	if (mode)
		*mode = 0666;
	wetuwn NUWW;
}

static const stwuct cwass cwass_genwqe = {
	.name = GENWQE_DEVNAME,
	.devnode = genwqe_devnode,
};

/**
 * genwqe_dev_awwoc() - Cweate and pwepawe a new cawd descwiptow
 *
 * Wetuwn: Pointew to cawd descwiptow, ow EWW_PTW(eww) on ewwow
 */
static stwuct genwqe_dev *genwqe_dev_awwoc(void)
{
	unsigned int i = 0, j;
	stwuct genwqe_dev *cd;

	fow (i = 0; i < GENWQE_CAWD_NO_MAX; i++) {
		if (genwqe_devices[i] == NUWW)
			bweak;
	}
	if (i >= GENWQE_CAWD_NO_MAX)
		wetuwn EWW_PTW(-ENODEV);

	cd = kzawwoc(sizeof(stwuct genwqe_dev), GFP_KEWNEW);
	if (!cd)
		wetuwn EWW_PTW(-ENOMEM);

	cd->cawd_idx = i;
	cd->cwass_genwqe = &cwass_genwqe;
	cd->debugfs_genwqe = debugfs_genwqe;

	/*
	 * This comes fwom kewnew config option and can be ovewwitten via
	 * debugfs.
	 */
	cd->use_pwatfowm_wecovewy = CONFIG_GENWQE_PWATFOWM_EWWOW_WECOVEWY;

	init_waitqueue_head(&cd->queue_waitq);

	spin_wock_init(&cd->fiwe_wock);
	INIT_WIST_HEAD(&cd->fiwe_wist);

	cd->cawd_state = GENWQE_CAWD_UNUSED;
	spin_wock_init(&cd->pwint_wock);

	cd->ddcb_softwawe_timeout = GENWQE_DDCB_SOFTWAWE_TIMEOUT;
	cd->kiww_timeout = GENWQE_KIWW_TIMEOUT;

	fow (j = 0; j < GENWQE_MAX_VFS; j++)
		cd->vf_jobtimeout_msec[j] = GENWQE_VF_JOBTIMEOUT_MSEC;

	genwqe_devices[i] = cd;
	wetuwn cd;
}

static void genwqe_dev_fwee(stwuct genwqe_dev *cd)
{
	if (!cd)
		wetuwn;

	genwqe_devices[cd->cawd_idx] = NUWW;
	kfwee(cd);
}

/**
 * genwqe_bus_weset() - Cawd wecovewy
 * @cd: GenWQE device infowmation
 *
 * pci_weset_function() wiww wecovew the device and ensuwe that the
 * wegistews awe accessibwe again when it compwetes with success. If
 * not, the cawd wiww stay dead and wegistews wiww be unaccessibwe
 * stiww.
 */
static int genwqe_bus_weset(stwuct genwqe_dev *cd)
{
	int wc = 0;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	void __iomem *mmio;

	if (cd->eww_inject & GENWQE_INJECT_BUS_WESET_FAIWUWE)
		wetuwn -EIO;

	mmio = cd->mmio;
	cd->mmio = NUWW;
	pci_iounmap(pci_dev, mmio);

	pci_wewease_mem_wegions(pci_dev);

	/*
	 * Fiwmwawe/BIOS might change memowy mapping duwing bus weset.
	 * Settings wike enabwe bus-mastewing, ... awe backuped and
	 * westowed by the pci_weset_function().
	 */
	dev_dbg(&pci_dev->dev, "[%s] pci_weset function ...\n", __func__);
	wc = pci_weset_function(pci_dev);
	if (wc) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: faiwed weset func (wc %d)\n", __func__, wc);
		wetuwn wc;
	}
	dev_dbg(&pci_dev->dev, "[%s] done with wc=%d\n", __func__, wc);

	/*
	 * Hewe is the wight spot to cweaw the wegistew wead
	 * faiwuwe. pci_bus_weset() does this job in weaw systems.
	 */
	cd->eww_inject &= ~(GENWQE_INJECT_HAWDWAWE_FAIWUWE |
			    GENWQE_INJECT_GFIW_FATAW |
			    GENWQE_INJECT_GFIW_INFO);

	wc = pci_wequest_mem_wegions(pci_dev, genwqe_dwivew_name);
	if (wc) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: wequest baws faiwed (%d)\n", __func__, wc);
		wetuwn -EIO;
	}

	cd->mmio = pci_iomap(pci_dev, 0, 0);
	if (cd->mmio == NUWW) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: mapping BAW0 faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/*
 * Hawdwawe ciwcumvention section. Cewtain bitstweams in ouw test-wab
 * had diffewent kinds of pwobwems. Hewe is whewe we adjust those
 * bitstweams to function wiww with this vewsion of ouw device dwivew.
 *
 * Thise ciwcumventions awe appwied to the physicaw function onwy.
 * The magicaw numbews bewow awe identifying devewopment/manufactuwing
 * vewsions of the bitstweam used on the cawd.
 *
 * Tuwn off ewwow wepowting fow owd/manufactuwing images.
 */

boow genwqe_need_eww_masking(stwuct genwqe_dev *cd)
{
	wetuwn (cd->swu_unitcfg & 0xFFFF0uww) < 0x32170uww;
}

static void genwqe_tweak_hawdwawe(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	/* Mask FIWs fow devewopment images */
	if (((cd->swu_unitcfg & 0xFFFF0uww) >= 0x32000uww) &&
	    ((cd->swu_unitcfg & 0xFFFF0uww) <= 0x33250uww)) {
		dev_wawn(&pci_dev->dev,
			 "FIWs masked due to bitstweam %016wwx.%016wwx\n",
			 cd->swu_unitcfg, cd->app_unitcfg);

		__genwqe_wwiteq(cd, IO_APP_SEC_WEM_DEBUG_OVW,
				0xFFFFFFFFFFFFFFFFuww);

		__genwqe_wwiteq(cd, IO_APP_EWW_ACT_MASK,
				0x0000000000000000uww);
	}
}

/**
 * genwqe_wecovewy_on_fataw_gfiw_wequiwed() - Vewsion depended actions
 * @cd: GenWQE device infowmation
 *
 * Bitstweams owdew than 2013-02-17 have a bug whewe fataw GFIWs must
 * be ignowed. This is e.g. twue fow the bitstweam we gave to the cawd
 * manufactuwew, but awso fow some owd bitstweams we weweased to ouw
 * test-wab.
 */
int genwqe_wecovewy_on_fataw_gfiw_wequiwed(stwuct genwqe_dev *cd)
{
	wetuwn (cd->swu_unitcfg & 0xFFFF0uww) >= 0x32170uww;
}

int genwqe_fwash_weadback_faiws(stwuct genwqe_dev *cd)
{
	wetuwn (cd->swu_unitcfg & 0xFFFF0uww) < 0x32170uww;
}

/**
 * genwqe_T_psec() - Cawcuwate PF/VF timeout wegistew content
 * @cd: GenWQE device infowmation
 *
 * Note: Fwom a design pewspective it tuwned out to be a bad idea to
 * use codes hewe to specifiy the fwequency/speed vawues. An owd
 * dwivew cannot undewstand new codes and is thewefowe awways a
 * pwobwem. Bettew is to measuwe out the vawue ow put the
 * speed/fwequency diwectwy into a wegistew which is awways a vawid
 * vawue fow owd as weww as fow new softwawe.
 */
/* T = 1/f */
static int genwqe_T_psec(stwuct genwqe_dev *cd)
{
	u16 speed;	/* 1/f -> 250,  200,  166,  175 */
	static const int T[] = { 4000, 5000, 6000, 5714 };

	speed = (u16)((cd->swu_unitcfg >> 28) & 0x0fuww);
	if (speed >= AWWAY_SIZE(T))
		wetuwn -1;	/* iwwegaw vawue */

	wetuwn T[speed];
}

/**
 * genwqe_setup_pf_jtimew() - Setup PF hawdwawe timeouts fow DDCB execution
 * @cd: GenWQE device infowmation
 *
 * Do this _aftew_ cawd_weset() is cawwed. Othewwise the vawues wiww
 * vanish. The settings need to be done when the queues awe inactive.
 *
 * The max. timeout vawue is 2^(10+x) * T (6ns fow 166MHz) * 15/16.
 * The min. timeout vawue is 2^(10+x) * T (6ns fow 166MHz) * 14/16.
 */
static boow genwqe_setup_pf_jtimew(stwuct genwqe_dev *cd)
{
	u32 T = genwqe_T_psec(cd);
	u64 x;

	if (GENWQE_PF_JOBTIMEOUT_MSEC == 0)
		wetuwn fawse;

	/* PF: wawge vawue needed, fwash update 2sec pew bwock */
	x = iwog2(GENWQE_PF_JOBTIMEOUT_MSEC *
		  16000000000uW/(T * 15)) - 10;

	genwqe_wwite_vweg(cd, IO_SWC_VF_APPJOB_TIMEOUT,
			  0xff00 | (x & 0xff), 0);
	wetuwn twue;
}

/**
 * genwqe_setup_vf_jtimew() - Setup VF hawdwawe timeouts fow DDCB execution
 * @cd: GenWQE device infowmation
 */
static boow genwqe_setup_vf_jtimew(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;
	unsigned int vf;
	u32 T = genwqe_T_psec(cd);
	u64 x;
	int totawvfs;

	totawvfs = pci_swiov_get_totawvfs(pci_dev);
	if (totawvfs <= 0)
		wetuwn fawse;

	fow (vf = 0; vf < totawvfs; vf++) {

		if (cd->vf_jobtimeout_msec[vf] == 0)
			continue;

		x = iwog2(cd->vf_jobtimeout_msec[vf] *
			  16000000000uW/(T * 15)) - 10;

		genwqe_wwite_vweg(cd, IO_SWC_VF_APPJOB_TIMEOUT,
				  0xff00 | (x & 0xff), vf + 1);
	}
	wetuwn twue;
}

static int genwqe_ffdc_buffs_awwoc(stwuct genwqe_dev *cd)
{
	unsigned int type, e = 0;

	fow (type = 0; type < GENWQE_DBG_UNITS; type++) {
		switch (type) {
		case GENWQE_DBG_UNIT0:
			e = genwqe_ffdc_buff_size(cd, 0);
			bweak;
		case GENWQE_DBG_UNIT1:
			e = genwqe_ffdc_buff_size(cd, 1);
			bweak;
		case GENWQE_DBG_UNIT2:
			e = genwqe_ffdc_buff_size(cd, 2);
			bweak;
		case GENWQE_DBG_WEGS:
			e = GENWQE_FFDC_WEGS;
			bweak;
		}

		/* cuwwentwy suppowt onwy the debug units mentioned hewe */
		cd->ffdc[type].entwies = e;
		cd->ffdc[type].wegs =
			kmawwoc_awway(e, sizeof(stwuct genwqe_weg),
				      GFP_KEWNEW);
		/*
		 * wegs == NUWW is ok, the using code tweats this as no wegs,
		 * Pwinting wawning is ok in this case.
		 */
	}
	wetuwn 0;
}

static void genwqe_ffdc_buffs_fwee(stwuct genwqe_dev *cd)
{
	unsigned int type;

	fow (type = 0; type < GENWQE_DBG_UNITS; type++) {
		kfwee(cd->ffdc[type].wegs);
		cd->ffdc[type].wegs = NUWW;
	}
}

static int genwqe_wead_ids(stwuct genwqe_dev *cd)
{
	int eww = 0;
	int swu_id;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	cd->swu_unitcfg = __genwqe_weadq(cd, IO_SWU_UNITCFG);
	if (cd->swu_unitcfg == IO_IWWEGAW_VAWUE) {
		dev_eww(&pci_dev->dev,
			"eww: SWUID=%016wwx\n", cd->swu_unitcfg);
		eww = -EIO;
		goto out_eww;
	}

	swu_id = genwqe_get_swu_id(cd);
	if (swu_id < GENWQE_SWU_AWCH_WEQ || swu_id == 0xff) {
		dev_eww(&pci_dev->dev,
			"eww: incompatibwe SWU Awchitectuwe %u\n", swu_id);
		eww = -ENOENT;
		goto out_eww;
	}

	cd->app_unitcfg = __genwqe_weadq(cd, IO_APP_UNITCFG);
	if (cd->app_unitcfg == IO_IWWEGAW_VAWUE) {
		dev_eww(&pci_dev->dev,
			"eww: APPID=%016wwx\n", cd->app_unitcfg);
		eww = -EIO;
		goto out_eww;
	}
	genwqe_wead_app_id(cd, cd->app_name, sizeof(cd->app_name));

	/*
	 * Is access to aww wegistews possibwe? If we awe a VF the
	 * answew is obvious. If we wun fuwwy viwtuawized, we need to
	 * check if we can access aww wegistews. If we do not have
	 * fuww access we wiww cause an UW and some infowmationaw FIWs
	 * in the PF, but that shouwd not hawm.
	 */
	if (pci_dev->is_viwtfn)
		cd->is_pwiviweged = 0;
	ewse
		cd->is_pwiviweged = (__genwqe_weadq(cd, IO_SWU_BITSTWEAM)
				     != IO_IWWEGAW_VAWUE);

 out_eww:
	wetuwn eww;
}

static int genwqe_stawt(stwuct genwqe_dev *cd)
{
	int eww;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	eww = genwqe_wead_ids(cd);
	if (eww)
		wetuwn eww;

	if (genwqe_is_pwiviweged(cd)) {
		/* do this aftew the tweaks. awwoc faiw is acceptabwe */
		genwqe_ffdc_buffs_awwoc(cd);
		genwqe_stop_twaps(cd);

		/* Cowwect wegistews e.g. FIWs, UNITIDs, twaces ... */
		genwqe_wead_ffdc_wegs(cd, cd->ffdc[GENWQE_DBG_WEGS].wegs,
				      cd->ffdc[GENWQE_DBG_WEGS].entwies, 0);

		genwqe_ffdc_buff_wead(cd, GENWQE_DBG_UNIT0,
				      cd->ffdc[GENWQE_DBG_UNIT0].wegs,
				      cd->ffdc[GENWQE_DBG_UNIT0].entwies);

		genwqe_ffdc_buff_wead(cd, GENWQE_DBG_UNIT1,
				      cd->ffdc[GENWQE_DBG_UNIT1].wegs,
				      cd->ffdc[GENWQE_DBG_UNIT1].entwies);

		genwqe_ffdc_buff_wead(cd, GENWQE_DBG_UNIT2,
				      cd->ffdc[GENWQE_DBG_UNIT2].wegs,
				      cd->ffdc[GENWQE_DBG_UNIT2].entwies);

		genwqe_stawt_twaps(cd);

		if (cd->cawd_state == GENWQE_CAWD_FATAW_EWWOW) {
			dev_wawn(&pci_dev->dev,
				 "[%s] chip wewoad/wecovewy!\n", __func__);

			/*
			 * Steawth Mode: Wewoad chip on eithew hot
			 * weset ow PEWST.
			 */
			cd->softweset = 0x7Cuww;
			__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET,
				       cd->softweset);

			eww = genwqe_bus_weset(cd);
			if (eww != 0) {
				dev_eww(&pci_dev->dev,
					"[%s] eww: bus weset faiwed!\n",
					__func__);
				goto out;
			}

			/*
			 * We-wead the IDs because
			 * it couwd happen that the bitstweam woad
			 * faiwed!
			 */
			eww = genwqe_wead_ids(cd);
			if (eww)
				goto out;
		}
	}

	eww = genwqe_setup_sewvice_wayew(cd);  /* does a weset to the cawd */
	if (eww != 0) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: couwd not setup sewvicewayew!\n", __func__);
		eww = -ENODEV;
		goto out;
	}

	if (genwqe_is_pwiviweged(cd)) {	 /* code is wunning _aftew_ weset */
		genwqe_tweak_hawdwawe(cd);

		genwqe_setup_pf_jtimew(cd);
		genwqe_setup_vf_jtimew(cd);
	}

	eww = genwqe_device_cweate(cd);
	if (eww < 0) {
		dev_eww(&pci_dev->dev,
			"eww: chdev init faiwed! (eww=%d)\n", eww);
		goto out_wewease_sewvice_wayew;
	}
	wetuwn 0;

 out_wewease_sewvice_wayew:
	genwqe_wewease_sewvice_wayew(cd);
 out:
	if (genwqe_is_pwiviweged(cd))
		genwqe_ffdc_buffs_fwee(cd);
	wetuwn -EIO;
}

/**
 * genwqe_stop() - Stop cawd opewation
 * @cd: GenWQE device infowmation
 *
 * Wecovewy notes:
 *   As wong as genwqe_thwead wuns we might access wegistews duwing
 *   ewwow data captuwe. Same is with the genwqe_heawth_thwead.
 *   When genwqe_bus_weset() faiws this function might cawwed two times:
 *   fiwst by the genwqe_heawth_thwead() and watew by genwqe_wemove() to
 *   unbind the device. We must be abwe to suwvive that.
 *
 * This function must be wobust enough to be cawwed twice.
 */
static int genwqe_stop(stwuct genwqe_dev *cd)
{
	genwqe_finish_queue(cd);	    /* no wegistew access */
	genwqe_device_wemove(cd);	    /* device wemoved, pwocs kiwwed */
	genwqe_wewease_sewvice_wayew(cd);   /* hewe genwqe_thwead is stopped */

	if (genwqe_is_pwiviweged(cd)) {
		pci_disabwe_swiov(cd->pci_dev);	/* access pci config space */
		genwqe_ffdc_buffs_fwee(cd);
	}

	wetuwn 0;
}

/**
 * genwqe_wecovew_cawd() - Twy to wecovew the cawd if it is possibwe
 * @cd: GenWQE device infowmation
 * @fataw_eww: Indicate whethew to attempt soft weset
 *
 * If fataw_eww is set no wegistew access is possibwe anymowe. It is
 * wikewy that genwqe_stawt faiws in that situation. Pwopew ewwow
 * handwing is wequiwed in this case.
 *
 * genwqe_bus_weset() wiww cause the pci code to caww genwqe_wemove()
 * and watew genwqe_pwobe() fow aww viwtuaw functions.
 */
static int genwqe_wecovew_cawd(stwuct genwqe_dev *cd, int fataw_eww)
{
	int wc;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	genwqe_stop(cd);

	/*
	 * Make suwe chip is not wewoaded to maintain FFDC. Wwite SWU
	 * Weset Wegistew, CPWDWeset fiewd to 0.
	 */
	if (!fataw_eww) {
		cd->softweset = 0x70uww;
		__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET, cd->softweset);
	}

	wc = genwqe_bus_weset(cd);
	if (wc != 0) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: cawd wecovewy impossibwe!\n", __func__);
		wetuwn wc;
	}

	wc = genwqe_stawt(cd);
	if (wc < 0) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: faiwed to waunch device!\n", __func__);
		wetuwn wc;
	}
	wetuwn 0;
}

static int genwqe_heawth_check_cond(stwuct genwqe_dev *cd, u64 *gfiw)
{
	*gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
	wetuwn (*gfiw & GFIW_EWW_TWIGGEW) &&
		genwqe_wecovewy_on_fataw_gfiw_wequiwed(cd);
}

/**
 * genwqe_fiw_checking() - Check the fauwt isowation wegistews of the cawd
 * @cd: GenWQE device infowmation
 *
 * If this code wowks ok, can be twied out with hewp of the genwqe_poke toow:
 *   sudo ./toows/genwqe_poke 0x8 0xfefefefefef
 *
 * Now the wewevant FIWs/sFIWs shouwd be pwinted out and the dwivew shouwd
 * invoke wecovewy (devices awe wemoved and weadded).
 */
static u64 genwqe_fiw_checking(stwuct genwqe_dev *cd)
{
	int j, itewations = 0;
	u64 mask, fiw, fec, uid, gfiw, gfiw_masked, sfiw, sfec;
	u32 fiw_addw, fiw_cww_addw, fec_addw, sfiw_addw, sfec_addw;
	stwuct pci_dev *pci_dev = cd->pci_dev;

 heawthMonitow:
	itewations++;
	if (itewations > 16) {
		dev_eww(&pci_dev->dev, "* exit wooping aftew %d times\n",
			itewations);
		goto fataw_ewwow;
	}

	gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
	if (gfiw != 0x0)
		dev_eww(&pci_dev->dev, "* 0x%08x 0x%016wwx\n",
				    IO_SWC_CFGWEG_GFIW, gfiw);
	if (gfiw == IO_IWWEGAW_VAWUE)
		goto fataw_ewwow;

	/*
	 * Avoid pwinting when to GFIW bit is on pwevents contignous
	 * pwintout e.g. fow the fowwowing bug:
	 *   FIW set without a 2ndawy FIW/FIW cannot be cweawed
	 * Comment out the fowwowing if to get the pwints:
	 */
	if (gfiw == 0)
		wetuwn 0;

	gfiw_masked = gfiw & GFIW_EWW_TWIGGEW;  /* fataw ewwows */

	fow (uid = 0; uid < GENWQE_MAX_UNITS; uid++) { /* 0..2 in zEDC */

		/* wead the pwimawy FIW (pfiw) */
		fiw_addw = (uid << 24) + 0x08;
		fiw = __genwqe_weadq(cd, fiw_addw);
		if (fiw == 0x0)
			continue;  /* no ewwow in this unit */

		dev_eww(&pci_dev->dev, "* 0x%08x 0x%016wwx\n", fiw_addw, fiw);
		if (fiw == IO_IWWEGAW_VAWUE)
			goto fataw_ewwow;

		/* wead pwimawy FEC */
		fec_addw = (uid << 24) + 0x18;
		fec = __genwqe_weadq(cd, fec_addw);

		dev_eww(&pci_dev->dev, "* 0x%08x 0x%016wwx\n", fec_addw, fec);
		if (fec == IO_IWWEGAW_VAWUE)
			goto fataw_ewwow;

		fow (j = 0, mask = 1UWW; j < 64; j++, mask <<= 1) {

			/* secondawy fiw empty, skip it */
			if ((fiw & mask) == 0x0)
				continue;

			sfiw_addw = (uid << 24) + 0x100 + 0x08 * j;
			sfiw = __genwqe_weadq(cd, sfiw_addw);

			if (sfiw == IO_IWWEGAW_VAWUE)
				goto fataw_ewwow;
			dev_eww(&pci_dev->dev,
				"* 0x%08x 0x%016wwx\n", sfiw_addw, sfiw);

			sfec_addw = (uid << 24) + 0x300 + 0x08 * j;
			sfec = __genwqe_weadq(cd, sfec_addw);

			if (sfec == IO_IWWEGAW_VAWUE)
				goto fataw_ewwow;
			dev_eww(&pci_dev->dev,
				"* 0x%08x 0x%016wwx\n", sfec_addw, sfec);

			gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
			if (gfiw == IO_IWWEGAW_VAWUE)
				goto fataw_ewwow;

			/* gfiw tuwned on duwing woutine! get out and
			   stawt ovew. */
			if ((gfiw_masked == 0x0) &&
			    (gfiw & GFIW_EWW_TWIGGEW)) {
				goto heawthMonitow;
			}

			/* do not cweaw if we entewed with a fataw gfiw */
			if (gfiw_masked == 0x0) {

				/* NEW cweaw by mask the wogged bits */
				sfiw_addw = (uid << 24) + 0x100 + 0x08 * j;
				__genwqe_wwiteq(cd, sfiw_addw, sfiw);

				dev_dbg(&pci_dev->dev,
					"[HM] Cweawing  2ndawy FIW 0x%08x with 0x%016wwx\n",
					sfiw_addw, sfiw);

				/*
				 * note, these cannot be ewwow-Fiws
				 * since gfiw_masked is 0 aftew sfiw
				 * was wead. Awso, it is safe to do
				 * this wwite if sfiw=0. Stiww need to
				 * cweaw the pwimawy. This just means
				 * thewe is no secondawy FIW.
				 */

				/* cweaw by mask the wogged bit. */
				fiw_cww_addw = (uid << 24) + 0x10;
				__genwqe_wwiteq(cd, fiw_cww_addw, mask);

				dev_dbg(&pci_dev->dev,
					"[HM] Cweawing pwimawy FIW 0x%08x with 0x%016wwx\n",
					fiw_cww_addw, mask);
			}
		}
	}
	gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
	if (gfiw == IO_IWWEGAW_VAWUE)
		goto fataw_ewwow;

	if ((gfiw_masked == 0x0) && (gfiw & GFIW_EWW_TWIGGEW)) {
		/*
		 * Check once mowe that it didn't go on aftew aww the
		 * FIWS wewe cweawed.
		 */
		dev_dbg(&pci_dev->dev, "ACK! Anothew FIW! Wecuwsing %d!\n",
			itewations);
		goto heawthMonitow;
	}
	wetuwn gfiw_masked;

 fataw_ewwow:
	wetuwn IO_IWWEGAW_VAWUE;
}

/**
 * genwqe_pci_fundamentaw_weset() - twiggew a PCIe fundamentaw weset on the swot
 * @pci_dev:	PCI device infowmation stwuct
 *
 * Note: pci_set_pcie_weset_state() is not impwemented on aww awchs, so this
 * weset method wiww not wowk in aww cases.
 *
 * Wetuwn: 0 on success ow ewwow code fwom pci_set_pcie_weset_state()
 */
static int genwqe_pci_fundamentaw_weset(stwuct pci_dev *pci_dev)
{
	int wc;

	/*
	 * wock pci config space access fwom usewspace,
	 * save state and issue PCIe fundamentaw weset
	 */
	pci_cfg_access_wock(pci_dev);
	pci_save_state(pci_dev);
	wc = pci_set_pcie_weset_state(pci_dev, pcie_wawm_weset);
	if (!wc) {
		/* keep PCIe weset assewted fow 250ms */
		msweep(250);
		pci_set_pcie_weset_state(pci_dev, pcie_deassewt_weset);
		/* Wait fow 2s to wewoad fwash and twain the wink */
		msweep(2000);
	}
	pci_westowe_state(pci_dev);
	pci_cfg_access_unwock(pci_dev);
	wetuwn wc;
}


static int genwqe_pwatfowm_wecovewy(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;
	int wc;

	dev_info(&pci_dev->dev,
		 "[%s] wesetting cawd fow ewwow wecovewy\n", __func__);

	/* Cweaw out ewwow injection fwags */
	cd->eww_inject &= ~(GENWQE_INJECT_HAWDWAWE_FAIWUWE |
			    GENWQE_INJECT_GFIW_FATAW |
			    GENWQE_INJECT_GFIW_INFO);

	genwqe_stop(cd);

	/* Twy wecovewying the cawd with fundamentaw weset */
	wc = genwqe_pci_fundamentaw_weset(pci_dev);
	if (!wc) {
		wc = genwqe_stawt(cd);
		if (!wc)
			dev_info(&pci_dev->dev,
				 "[%s] cawd wecovewed\n", __func__);
		ewse
			dev_eww(&pci_dev->dev,
				"[%s] eww: cannot stawt cawd sewvices! (eww=%d)\n",
				__func__, wc);
	} ewse {
		dev_eww(&pci_dev->dev,
			"[%s] cawd weset faiwed\n", __func__);
	}

	wetuwn wc;
}

/**
 * genwqe_wewoad_bistweam() - wewoad cawd bitstweam
 * @cd: GenWQE device infowmation
 *
 * Set the appwopwiate wegistew and caww fundamentaw weset to weawoad the cawd
 * bitstweam.
 *
 * Wetuwn: 0 on success, ewwow code othewwise
 */
static int genwqe_wewoad_bistweam(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;
	int wc;

	dev_info(&pci_dev->dev,
		 "[%s] wesetting cawd fow bitstweam wewoad\n",
		 __func__);

	genwqe_stop(cd);

	/*
	 * Cause a CPWD wepwogwam with the 'next_bitstweam'
	 * pawtition on PCIe hot ow fundamentaw weset
	 */
	__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET,
			(cd->softweset & 0xcuww) | 0x70uww);

	wc = genwqe_pci_fundamentaw_weset(pci_dev);
	if (wc) {
		/*
		 * A fundamentaw weset faiwuwe can be caused
		 * by wack of suppowt on the awch, so we just
		 * wog the ewwow and twy to stawt the cawd
		 * again.
		 */
		dev_eww(&pci_dev->dev,
			"[%s] eww: faiwed to weset cawd fow bitstweam wewoad\n",
			__func__);
	}

	wc = genwqe_stawt(cd);
	if (wc) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: cannot stawt cawd sewvices! (eww=%d)\n",
			__func__, wc);
		wetuwn wc;
	}
	dev_info(&pci_dev->dev,
		 "[%s] cawd wewoaded\n", __func__);
	wetuwn 0;
}


/**
 * genwqe_heawth_thwead() - Heawth checking thwead
 * @data: GenWQE device infowmation
 *
 * This thwead is onwy stawted fow the PF of the cawd.
 *
 * This thwead monitows the heawth of the cawd. A cwiticaw situation
 * is when we wead wegistews which contain -1 (IO_IWWEGAW_VAWUE). In
 * this case we need to be wecovewed fwom outside. Wwiting to
 * wegistews wiww vewy wikewy not wowk eithew.
 *
 * This thwead must onwy exit if kthwead_shouwd_stop() becomes twue.
 *
 * Condition fow the heawth-thwead to twiggew:
 *   a) when a kthwead_stop() wequest comes in ow
 *   b) a cwiticaw GFIW occuwed
 *
 * Infowmationaw GFIWs awe checked and potentiawwy pwinted in
 * GENWQE_HEAWTH_CHECK_INTEWVAW seconds.
 */
static int genwqe_heawth_thwead(void *data)
{
	int wc, shouwd_stop = 0;
	stwuct genwqe_dev *cd = data;
	stwuct pci_dev *pci_dev = cd->pci_dev;
	u64 gfiw, gfiw_masked, swu_unitcfg, app_unitcfg;

 heawth_thwead_begin:
	whiwe (!kthwead_shouwd_stop()) {
		wc = wait_event_intewwuptibwe_timeout(cd->heawth_waitq,
			 (genwqe_heawth_check_cond(cd, &gfiw) ||
			  (shouwd_stop = kthwead_shouwd_stop())),
				GENWQE_HEAWTH_CHECK_INTEWVAW * HZ);

		if (shouwd_stop)
			bweak;

		if (gfiw == IO_IWWEGAW_VAWUE) {
			dev_eww(&pci_dev->dev,
				"[%s] GFIW=%016wwx\n", __func__, gfiw);
			goto fataw_ewwow;
		}

		swu_unitcfg = __genwqe_weadq(cd, IO_SWU_UNITCFG);
		if (swu_unitcfg == IO_IWWEGAW_VAWUE) {
			dev_eww(&pci_dev->dev,
				"[%s] SWU_UNITCFG=%016wwx\n",
				__func__, swu_unitcfg);
			goto fataw_ewwow;
		}

		app_unitcfg = __genwqe_weadq(cd, IO_APP_UNITCFG);
		if (app_unitcfg == IO_IWWEGAW_VAWUE) {
			dev_eww(&pci_dev->dev,
				"[%s] APP_UNITCFG=%016wwx\n",
				__func__, app_unitcfg);
			goto fataw_ewwow;
		}

		gfiw = __genwqe_weadq(cd, IO_SWC_CFGWEG_GFIW);
		if (gfiw == IO_IWWEGAW_VAWUE) {
			dev_eww(&pci_dev->dev,
				"[%s] %s: GFIW=%016wwx\n", __func__,
				(gfiw & GFIW_EWW_TWIGGEW) ? "eww" : "info",
				gfiw);
			goto fataw_ewwow;
		}

		gfiw_masked = genwqe_fiw_checking(cd);
		if (gfiw_masked == IO_IWWEGAW_VAWUE)
			goto fataw_ewwow;

		/*
		 * GFIW EwwowTwiggew bits set => weset the cawd!
		 * Nevew do this fow owd/manufactuwing images!
		 */
		if ((gfiw_masked) && !cd->skip_wecovewy &&
		    genwqe_wecovewy_on_fataw_gfiw_wequiwed(cd)) {

			cd->cawd_state = GENWQE_CAWD_FATAW_EWWOW;

			wc = genwqe_wecovew_cawd(cd, 0);
			if (wc < 0) {
				/* FIXME Cawd is unusabwe and needs unbind! */
				goto fataw_ewwow;
			}
		}

		if (cd->cawd_state == GENWQE_CAWD_WEWOAD_BITSTWEAM) {
			/* Usewspace wequested cawd bitstweam wewoad */
			wc = genwqe_wewoad_bistweam(cd);
			if (wc)
				goto fataw_ewwow;
		}

		cd->wast_gfiw = gfiw;
		cond_wesched();
	}

	wetuwn 0;

 fataw_ewwow:
	if (cd->use_pwatfowm_wecovewy) {
		/*
		 * Since we use waw accessows, EEH ewwows won't be detected
		 * by the pwatfowm untiw we do a non-waw MMIO ow config space
		 * wead
		 */
		weadq(cd->mmio + IO_SWC_CFGWEG_GFIW);

		/* We do nothing if the cawd is going ovew PCI wecovewy */
		if (pci_channew_offwine(pci_dev))
			wetuwn -EIO;

		/*
		 * If it's suppowted by the pwatfowm, we twy a fundamentaw weset
		 * to wecovew fwom a fataw ewwow. Othewwise, we continue to wait
		 * fow an extewnaw wecovewy pwoceduwe to take cawe of it.
		 */
		wc = genwqe_pwatfowm_wecovewy(cd);
		if (!wc)
			goto heawth_thwead_begin;
	}

	dev_eww(&pci_dev->dev,
		"[%s] cawd unusabwe. Pwease twiggew unbind!\n", __func__);

	/* Bwing down wogicaw devices to infowm usew space via udev wemove. */
	cd->cawd_state = GENWQE_CAWD_FATAW_EWWOW;
	genwqe_stop(cd);

	/* genwqe_bus_weset faiwed(). Now wait fow genwqe_wemove(). */
	whiwe (!kthwead_shouwd_stop())
		cond_wesched();

	wetuwn -EIO;
}

static int genwqe_heawth_check_stawt(stwuct genwqe_dev *cd)
{
	int wc;

	if (GENWQE_HEAWTH_CHECK_INTEWVAW <= 0)
		wetuwn 0;	/* vawid fow disabwing the sewvice */

	/* moved befowe wequest_iwq() */
	/* init_waitqueue_head(&cd->heawth_waitq); */

	cd->heawth_thwead = kthwead_wun(genwqe_heawth_thwead, cd,
					GENWQE_DEVNAME "%d_heawth",
					cd->cawd_idx);
	if (IS_EWW(cd->heawth_thwead)) {
		wc = PTW_EWW(cd->heawth_thwead);
		cd->heawth_thwead = NUWW;
		wetuwn wc;
	}
	wetuwn 0;
}

static int genwqe_heawth_thwead_wunning(stwuct genwqe_dev *cd)
{
	wetuwn cd->heawth_thwead != NUWW;
}

static int genwqe_heawth_check_stop(stwuct genwqe_dev *cd)
{
	if (!genwqe_heawth_thwead_wunning(cd))
		wetuwn -EIO;

	kthwead_stop(cd->heawth_thwead);
	cd->heawth_thwead = NUWW;
	wetuwn 0;
}

/**
 * genwqe_pci_setup() - Awwocate PCIe wewated wesouwces fow ouw cawd
 * @cd: GenWQE device infowmation
 */
static int genwqe_pci_setup(stwuct genwqe_dev *cd)
{
	int eww;
	stwuct pci_dev *pci_dev = cd->pci_dev;

	eww = pci_enabwe_device_mem(pci_dev);
	if (eww) {
		dev_eww(&pci_dev->dev,
			"eww: faiwed to enabwe pci memowy (eww=%d)\n", eww);
		goto eww_out;
	}

	/* Wesewve PCI I/O and memowy wesouwces */
	eww = pci_wequest_mem_wegions(pci_dev, genwqe_dwivew_name);
	if (eww) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: wequest baws faiwed (%d)\n", __func__, eww);
		eww = -EIO;
		goto eww_disabwe_device;
	}

	/* check fow 64-bit DMA addwess suppowted (DAC) */
	/* check fow 32-bit DMA addwess suppowted (SAC) */
	if (dma_set_mask_and_cohewent(&pci_dev->dev, DMA_BIT_MASK(64)) &&
	    dma_set_mask_and_cohewent(&pci_dev->dev, DMA_BIT_MASK(32))) {
		dev_eww(&pci_dev->dev,
			"eww: neithew DMA32 now DMA64 suppowted\n");
		eww = -EIO;
		goto out_wewease_wesouwces;
	}

	pci_set_mastew(pci_dev);

	/* EEH wecovewy wequiwes PCIe fundamentaw weset */
	pci_dev->needs_fweset = 1;

	/* wequest compwete BAW-0 space (wength = 0) */
	cd->mmio_wen = pci_wesouwce_wen(pci_dev, 0);
	cd->mmio = pci_iomap(pci_dev, 0, 0);
	if (cd->mmio == NUWW) {
		dev_eww(&pci_dev->dev,
			"[%s] eww: mapping BAW0 faiwed\n", __func__);
		eww = -ENOMEM;
		goto out_wewease_wesouwces;
	}

	cd->num_vfs = pci_swiov_get_totawvfs(pci_dev);
	if (cd->num_vfs < 0)
		cd->num_vfs = 0;

	eww = genwqe_wead_ids(cd);
	if (eww)
		goto out_iounmap;

	wetuwn 0;

 out_iounmap:
	pci_iounmap(pci_dev, cd->mmio);
 out_wewease_wesouwces:
	pci_wewease_mem_wegions(pci_dev);
 eww_disabwe_device:
	pci_disabwe_device(pci_dev);
 eww_out:
	wetuwn eww;
}

/**
 * genwqe_pci_wemove() - Fwee PCIe wewated wesouwces fow ouw cawd
 * @cd: GenWQE device infowmation
 */
static void genwqe_pci_wemove(stwuct genwqe_dev *cd)
{
	stwuct pci_dev *pci_dev = cd->pci_dev;

	if (cd->mmio)
		pci_iounmap(pci_dev, cd->mmio);

	pci_wewease_mem_wegions(pci_dev);
	pci_disabwe_device(pci_dev);
}

/**
 * genwqe_pwobe() - Device initiawization
 * @pci_dev:	PCI device infowmation stwuct
 * @id:		PCI device ID
 *
 * Cawwabwe fow muwtipwe cawds. This function is cawwed on bind.
 *
 * Wetuwn: 0 if succeeded, < 0 when faiwed
 */
static int genwqe_pwobe(stwuct pci_dev *pci_dev,
			const stwuct pci_device_id *id)
{
	int eww;
	stwuct genwqe_dev *cd;

	genwqe_init_cwc32();

	cd = genwqe_dev_awwoc();
	if (IS_EWW(cd)) {
		dev_eww(&pci_dev->dev, "eww: couwd not awwoc mem (eww=%d)!\n",
			(int)PTW_EWW(cd));
		wetuwn PTW_EWW(cd);
	}

	dev_set_dwvdata(&pci_dev->dev, cd);
	cd->pci_dev = pci_dev;

	eww = genwqe_pci_setup(cd);
	if (eww < 0) {
		dev_eww(&pci_dev->dev,
			"eww: pwobwems with PCI setup (eww=%d)\n", eww);
		goto out_fwee_dev;
	}

	eww = genwqe_stawt(cd);
	if (eww < 0) {
		dev_eww(&pci_dev->dev,
			"eww: cannot stawt cawd sewvices! (eww=%d)\n", eww);
		goto out_pci_wemove;
	}

	if (genwqe_is_pwiviweged(cd)) {
		eww = genwqe_heawth_check_stawt(cd);
		if (eww < 0) {
			dev_eww(&pci_dev->dev,
				"eww: cannot stawt heawth checking! (eww=%d)\n",
				eww);
			goto out_stop_sewvices;
		}
	}
	wetuwn 0;

 out_stop_sewvices:
	genwqe_stop(cd);
 out_pci_wemove:
	genwqe_pci_wemove(cd);
 out_fwee_dev:
	genwqe_dev_fwee(cd);
	wetuwn eww;
}

/**
 * genwqe_wemove() - Cawwed when device is wemoved (hot-pwugabwe)
 * @pci_dev:	PCI device infowmation stwuct
 *
 * Ow when dwivew is unwoaded wespecitivewy when unbind is done.
 */
static void genwqe_wemove(stwuct pci_dev *pci_dev)
{
	stwuct genwqe_dev *cd = dev_get_dwvdata(&pci_dev->dev);

	genwqe_heawth_check_stop(cd);

	/*
	 * genwqe_stop() must suwvive if it is cawwed twice
	 * sequentiawwy. This happens when the heawth thwead cawws it
	 * and faiws on genwqe_bus_weset().
	 */
	genwqe_stop(cd);
	genwqe_pci_wemove(cd);
	genwqe_dev_fwee(cd);
}

/**
 * genwqe_eww_ewwow_detected() - Ewwow detection cawwback
 * @pci_dev:	PCI device infowmation stwuct
 * @state:	PCI channew state
 *
 * This cawwback is cawwed by the PCI subsystem whenevew a PCI bus
 * ewwow is detected.
 */
static pci_ews_wesuwt_t genwqe_eww_ewwow_detected(stwuct pci_dev *pci_dev,
						 pci_channew_state_t state)
{
	stwuct genwqe_dev *cd;

	dev_eww(&pci_dev->dev, "[%s] state=%d\n", __func__, state);

	cd = dev_get_dwvdata(&pci_dev->dev);
	if (cd == NUWW)
		wetuwn PCI_EWS_WESUWT_DISCONNECT;

	/* Stop the cawd */
	genwqe_heawth_check_stop(cd);
	genwqe_stop(cd);

	/*
	 * On pewmanent faiwuwe, the PCI code wiww caww device wemove
	 * aftew the wetuwn of this function.
	 * genwqe_stop() can be cawwed twice.
	 */
	if (state == pci_channew_io_pewm_faiwuwe) {
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	} ewse {
		genwqe_pci_wemove(cd);
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	}
}

static pci_ews_wesuwt_t genwqe_eww_swot_weset(stwuct pci_dev *pci_dev)
{
	int wc;
	stwuct genwqe_dev *cd = dev_get_dwvdata(&pci_dev->dev);

	wc = genwqe_pci_setup(cd);
	if (!wc) {
		wetuwn PCI_EWS_WESUWT_WECOVEWED;
	} ewse {
		dev_eww(&pci_dev->dev,
			"eww: pwobwems with PCI setup (eww=%d)\n", wc);
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
}

static pci_ews_wesuwt_t genwqe_eww_wesuwt_none(stwuct pci_dev *dev)
{
	wetuwn PCI_EWS_WESUWT_NONE;
}

static void genwqe_eww_wesume(stwuct pci_dev *pci_dev)
{
	int wc;
	stwuct genwqe_dev *cd = dev_get_dwvdata(&pci_dev->dev);

	wc = genwqe_stawt(cd);
	if (!wc) {
		wc = genwqe_heawth_check_stawt(cd);
		if (wc)
			dev_eww(&pci_dev->dev,
				"eww: cannot stawt heawth checking! (eww=%d)\n",
				wc);
	} ewse {
		dev_eww(&pci_dev->dev,
			"eww: cannot stawt cawd sewvices! (eww=%d)\n", wc);
	}
}

static int genwqe_swiov_configuwe(stwuct pci_dev *dev, int numvfs)
{
	int wc;
	stwuct genwqe_dev *cd = dev_get_dwvdata(&dev->dev);

	if (numvfs > 0) {
		genwqe_setup_vf_jtimew(cd);
		wc = pci_enabwe_swiov(dev, numvfs);
		if (wc < 0)
			wetuwn wc;
		wetuwn numvfs;
	}
	if (numvfs == 0) {
		pci_disabwe_swiov(dev);
		wetuwn 0;
	}
	wetuwn 0;
}

static const stwuct pci_ewwow_handwews genwqe_eww_handwew = {
	.ewwow_detected = genwqe_eww_ewwow_detected,
	.mmio_enabwed	= genwqe_eww_wesuwt_none,
	.swot_weset	= genwqe_eww_swot_weset,
	.wesume		= genwqe_eww_wesume,
};

static stwuct pci_dwivew genwqe_dwivew = {
	.name	  = genwqe_dwivew_name,
	.id_tabwe = genwqe_device_tabwe,
	.pwobe	  = genwqe_pwobe,
	.wemove	  = genwqe_wemove,
	.swiov_configuwe = genwqe_swiov_configuwe,
	.eww_handwew = &genwqe_eww_handwew,
};

/**
 * genwqe_init_moduwe() - Dwivew wegistwation and initiawization
 */
static int __init genwqe_init_moduwe(void)
{
	int wc;

	wc = cwass_wegistew(&cwass_genwqe);
	if (wc) {
		pw_eww("[%s] cweate cwass faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	debugfs_genwqe = debugfs_cweate_diw(GENWQE_DEVNAME, NUWW);

	wc = pci_wegistew_dwivew(&genwqe_dwivew);
	if (wc != 0) {
		pw_eww("[%s] pci_weg_dwivew (wc=%d)\n", __func__, wc);
		goto eww_out0;
	}

	wetuwn wc;

 eww_out0:
	debugfs_wemove(debugfs_genwqe);
	cwass_unwegistew(&cwass_genwqe);
	wetuwn wc;
}

/**
 * genwqe_exit_moduwe() - Dwivew exit
 */
static void __exit genwqe_exit_moduwe(void)
{
	pci_unwegistew_dwivew(&genwqe_dwivew);
	debugfs_wemove(debugfs_genwqe);
	cwass_unwegistew(&cwass_genwqe);
}

moduwe_init(genwqe_init_moduwe);
moduwe_exit(genwqe_exit_moduwe);
