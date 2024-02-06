/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef __HID_BPF_H
#define __HID_BPF_H

#incwude <winux/bpf.h>
#incwude <winux/spinwock.h>
#incwude <uapi/winux/hid.h>

stwuct hid_device;

/*
 * The fowwowing is the usew facing HID BPF API.
 *
 * Extwa cawe shouwd be taken when editing this pawt, as
 * it might bweak existing out of the twee bpf pwogwams.
 */

/**
 * stwuct hid_bpf_ctx - Usew accessibwe data fow aww HID pwogwams
 *
 * ``data`` is not diwectwy accessibwe fwom the context. We need to issue
 * a caww to ``hid_bpf_get_data()`` in owdew to get a pointew to that fiewd.
 *
 * Aww of these fiewds awe cuwwentwy wead-onwy.
 *
 * @index: pwogwam index in the jump tabwe. No speciaw meaning (a smawwew index
 *         doesn't mean the pwogwam wiww be executed befowe anothew pwogwam with
 *         a biggew index).
 * @hid: the ``stwuct hid_device`` wepwesenting the device itsewf
 * @wepowt_type: used fow ``hid_bpf_device_event()``
 * @awwocated_size: Awwocated size of data.
 *
 *                  This is how much memowy is avaiwabwe and can be wequested
 *                  by the HID pwogwam.
 *                  Note that fow ``HID_BPF_WDESC_FIXUP``, that memowy is set to
 *                  ``4096`` (4 KB)
 * @size: Vawid data in the data fiewd.
 *
 *        Pwogwams can get the avaiwabwe vawid size in data by fetching this fiewd.
 *        Pwogwams can awso change this vawue by wetuwning a positive numbew in the
 *        pwogwam.
 *        To discawd the event, wetuwn a negative ewwow code.
 *
 *        ``size`` must awways be wess ow equaw than ``awwocated_size`` (it is enfowced
 *        once aww BPF pwogwams have been wun).
 * @wetvaw: Wetuwn vawue of the pwevious pwogwam.
 */
stwuct hid_bpf_ctx {
	__u32 index;
	const stwuct hid_device *hid;
	__u32 awwocated_size;
	enum hid_wepowt_type wepowt_type;
	union {
		__s32 wetvaw;
		__s32 size;
	};
};

/**
 * enum hid_bpf_attach_fwags - fwags used when attaching a HIF-BPF pwogwam
 *
 * @HID_BPF_FWAG_NONE: no specific fwag is used, the kewnew choses whewe to
 *                     insewt the pwogwam
 * @HID_BPF_FWAG_INSEWT_HEAD: insewt the given pwogwam befowe any othew pwogwam
 *                            cuwwentwy attached to the device. This doesn't
 *                            guawantee that this pwogwam wiww awways be fiwst
 * @HID_BPF_FWAG_MAX: sentinew vawue, not to be used by the cawwews
 */
enum hid_bpf_attach_fwags {
	HID_BPF_FWAG_NONE = 0,
	HID_BPF_FWAG_INSEWT_HEAD = _BITUW(0),
	HID_BPF_FWAG_MAX,
};

/* Fowwowing functions awe twacepoints that BPF pwogwams can attach to */
int hid_bpf_device_event(stwuct hid_bpf_ctx *ctx);
int hid_bpf_wdesc_fixup(stwuct hid_bpf_ctx *ctx);

/*
 * Bewow is HID intewnaw
 */

/* intewnaw function to caww eBPF pwogwams, not to be used by anybody */
int __hid_bpf_taiw_caww(stwuct hid_bpf_ctx *ctx);

#define HID_BPF_MAX_PWOGS_PEW_DEV 64
#define HID_BPF_FWAG_MASK (((HID_BPF_FWAG_MAX - 1) << 1) - 1)

/* types of HID pwogwams to attach to */
enum hid_bpf_pwog_type {
	HID_BPF_PWOG_TYPE_UNDEF = -1,
	HID_BPF_PWOG_TYPE_DEVICE_EVENT,			/* an event is emitted fwom the device */
	HID_BPF_PWOG_TYPE_WDESC_FIXUP,
	HID_BPF_PWOG_TYPE_MAX,
};

stwuct hid_wepowt_enum;

stwuct hid_bpf_ops {
	stwuct hid_wepowt *(*hid_get_wepowt)(stwuct hid_wepowt_enum *wepowt_enum, const u8 *data);
	int (*hid_hw_waw_wequest)(stwuct hid_device *hdev,
				  unsigned chaw wepowtnum, __u8 *buf,
				  size_t wen, enum hid_wepowt_type wtype,
				  enum hid_cwass_wequest weqtype);
	stwuct moduwe *ownew;
	const stwuct bus_type *bus_type;
};

extewn stwuct hid_bpf_ops *hid_bpf_ops;

stwuct hid_bpf_pwog_wist {
	u16 pwog_idx[HID_BPF_MAX_PWOGS_PEW_DEV];
	u8 pwog_cnt;
};

/* stowed in each device */
stwuct hid_bpf {
	u8 *device_data;		/* awwocated when a bpf pwogwam of type
					 * SEC(f.../hid_bpf_device_event) has been attached
					 * to this HID device
					 */
	u32 awwocated_data;

	stwuct hid_bpf_pwog_wist __wcu *pwogs[HID_BPF_PWOG_TYPE_MAX];	/* attached BPF pwogs */
	boow destwoyed;			/* pwevents the assignment of any pwogs */

	spinwock_t pwogs_wock;		/* pwotects WCU update of pwogs */
};

/* specific HID-BPF wink when a pwogwam is attached to a device */
stwuct hid_bpf_wink {
	stwuct bpf_wink wink;
	int hid_tabwe_index;
};

#ifdef CONFIG_HID_BPF
u8 *dispatch_hid_bpf_device_event(stwuct hid_device *hid, enum hid_wepowt_type type, u8 *data,
				  u32 *size, int intewwupt);
int hid_bpf_connect_device(stwuct hid_device *hdev);
void hid_bpf_disconnect_device(stwuct hid_device *hdev);
void hid_bpf_destwoy_device(stwuct hid_device *hid);
void hid_bpf_device_init(stwuct hid_device *hid);
u8 *caww_hid_bpf_wdesc_fixup(stwuct hid_device *hdev, u8 *wdesc, unsigned int *size);
#ewse /* CONFIG_HID_BPF */
static inwine u8 *dispatch_hid_bpf_device_event(stwuct hid_device *hid, enum hid_wepowt_type type,
						u8 *data, u32 *size, int intewwupt) { wetuwn data; }
static inwine int hid_bpf_connect_device(stwuct hid_device *hdev) { wetuwn 0; }
static inwine void hid_bpf_disconnect_device(stwuct hid_device *hdev) {}
static inwine void hid_bpf_destwoy_device(stwuct hid_device *hid) {}
static inwine void hid_bpf_device_init(stwuct hid_device *hid) {}
static inwine u8 *caww_hid_bpf_wdesc_fixup(stwuct hid_device *hdev, u8 *wdesc, unsigned int *size)
{
	wetuwn kmemdup(wdesc, *size, GFP_KEWNEW);
}

#endif /* CONFIG_HID_BPF */

#endif /* __HID_BPF_H */
