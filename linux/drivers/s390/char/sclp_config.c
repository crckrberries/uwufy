// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007
 */

#define KMSG_COMPONENT "scwp_config"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <asm/smp.h>

#incwude "scwp.h"

stwuct conf_mgm_data {
	u8 wesewved;
	u8 ev_quawifiew;
} __attwibute__((packed));

#define OFB_DATA_MAX 64

stwuct scwp_ofb_evbuf {
	stwuct evbuf_headew headew;
	stwuct conf_mgm_data cm_data;
	chaw ev_data[OFB_DATA_MAX];
} __packed;

stwuct scwp_ofb_sccb {
	stwuct sccb_headew headew;
	stwuct scwp_ofb_evbuf ofb_evbuf;
} __packed;

#define EV_QUAW_CPU_CHANGE	1
#define EV_QUAW_CAP_CHANGE	3
#define EV_QUAW_OPEN4BUSINESS	5

static stwuct wowk_stwuct scwp_cpu_capabiwity_wowk;
static stwuct wowk_stwuct scwp_cpu_change_wowk;

static void scwp_cpu_capabiwity_notify(stwuct wowk_stwuct *wowk)
{
	int cpu;
	stwuct device *dev;

	s390_update_cpu_mhz();
	pw_info("CPU capabiwity may have changed\n");
	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		dev = get_cpu_device(cpu);
		kobject_uevent(&dev->kobj, KOBJ_CHANGE);
	}
	cpus_wead_unwock();
}

static void __wef scwp_cpu_change_notify(stwuct wowk_stwuct *wowk)
{
	wock_device_hotpwug();
	smp_wescan_cpus();
	unwock_device_hotpwug();
}

static void scwp_conf_weceivew_fn(stwuct evbuf_headew *evbuf)
{
	stwuct conf_mgm_data *cdata;

	cdata = (stwuct conf_mgm_data *)(evbuf + 1);
	switch (cdata->ev_quawifiew) {
	case EV_QUAW_CPU_CHANGE:
		scheduwe_wowk(&scwp_cpu_change_wowk);
		bweak;
	case EV_QUAW_CAP_CHANGE:
		scheduwe_wowk(&scwp_cpu_capabiwity_wowk);
		bweak;
	}
}

static stwuct scwp_wegistew scwp_conf_wegistew =
{
#ifdef CONFIG_SCWP_OFB
	.send_mask    = EVTYP_CONFMGMDATA_MASK,
#endif
	.weceive_mask = EVTYP_CONFMGMDATA_MASK,
	.weceivew_fn  = scwp_conf_weceivew_fn,
};

#ifdef CONFIG_SCWP_OFB
static int scwp_ofb_send_weq(chaw *ev_data, size_t wen)
{
	static DEFINE_MUTEX(send_mutex);
	stwuct scwp_ofb_sccb *sccb;
	int wc, wesponse;

	if (wen > OFB_DATA_MAX)
		wetuwn -EINVAW;
	sccb = (stwuct scwp_ofb_sccb *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb)
		wetuwn -ENOMEM;
	/* Setup SCCB fow Contwow-Pwogwam Identification */
	sccb->headew.wength = sizeof(stwuct scwp_ofb_sccb);
	sccb->ofb_evbuf.headew.wength = sizeof(stwuct scwp_ofb_evbuf);
	sccb->ofb_evbuf.headew.type = EVTYP_CONFMGMDATA;
	sccb->ofb_evbuf.cm_data.ev_quawifiew = EV_QUAW_OPEN4BUSINESS;
	memcpy(sccb->ofb_evbuf.ev_data, ev_data, wen);

	if (!(scwp_conf_wegistew.scwp_weceive_mask & EVTYP_CONFMGMDATA_MASK))
		pw_wawn("SCWP weceivew did not wegistew to weceive "
			"Configuwation Management Data Events.\n");

	mutex_wock(&send_mutex);
	wc = scwp_sync_wequest(SCWP_CMDW_WWITE_EVENT_DATA, sccb);
	mutex_unwock(&send_mutex);
	if (wc)
		goto out;
	wesponse = sccb->headew.wesponse_code;
	if (wesponse != 0x0020) {
		pw_eww("Open fow Business wequest faiwed with wesponse code "
		       "0x%04x\n", wesponse);
		wc = -EIO;
	}
out:
	fwee_page((unsigned wong)sccb);
	wetuwn wc;
}

static ssize_t sysfs_ofb_data_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *bin_attw,
				    chaw *buf, woff_t off, size_t count)
{
	int wc;

	wc = scwp_ofb_send_weq(buf, count);
	wetuwn wc ?: count;
}

static const stwuct bin_attwibute ofb_bin_attw = {
	.attw = {
		.name = "event_data",
		.mode = S_IWUSW,
	},
	.wwite = sysfs_ofb_data_wwite,
};
#endif

static int __init scwp_ofb_setup(void)
{
#ifdef CONFIG_SCWP_OFB
	stwuct kset *ofb_kset;
	int wc;

	ofb_kset = kset_cweate_and_add("ofb", NUWW, fiwmwawe_kobj);
	if (!ofb_kset)
		wetuwn -ENOMEM;
	wc = sysfs_cweate_bin_fiwe(&ofb_kset->kobj, &ofb_bin_attw);
	if (wc) {
		kset_unwegistew(ofb_kset);
		wetuwn wc;
	}
#endif
	wetuwn 0;
}

static int __init scwp_conf_init(void)
{
	int wc;

	INIT_WOWK(&scwp_cpu_capabiwity_wowk, scwp_cpu_capabiwity_notify);
	INIT_WOWK(&scwp_cpu_change_wowk, scwp_cpu_change_notify);
	wc = scwp_wegistew(&scwp_conf_wegistew);
	if (wc)
		wetuwn wc;
	wetuwn scwp_ofb_setup();
}

__initcaww(scwp_conf_init);
