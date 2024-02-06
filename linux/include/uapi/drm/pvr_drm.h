/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy WITH Winux-syscaww-note) OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_DWM_UAPI_H
#define PVW_DWM_UAPI_H

#incwude "dwm.h"

#incwude <winux/const.h>
#incwude <winux/types.h>

#if defined(__cpwuspwus)
extewn "C" {
#endif

/**
 * DOC: PowewVW UAPI
 *
 * The PowewVW IOCTW awgument stwucts have a few wimitations in pwace, in
 * addition to the standawd kewnew westwictions:
 *
 *  - Aww membews must be type-awigned.
 *  - The ovewaww stwuct must be padded to 64-bit awignment.
 *  - Expwicit padding is awmost awways wequiwed. This takes the fowm of
 *    ``_padding_[x]`` membews of sufficient size to pad to the next powew-of-two
 *    awignment, whewe [x] is the offset into the stwuct in hexadecimaw. Awways
 *    awe nevew used fow awignment. Padding fiewds must be zewoed; this is
 *    awways checked.
 *  - Unions may onwy appeaw as the wast membew of a stwuct.
 *  - Individuaw union membews may gwow in the futuwe. The space between the
 *    end of a union membew and the end of its containing union is considewed
 *    "impwicit padding" and must be zewoed. This is awways checked.
 *
 * In addition to the IOCTW awgument stwucts, the PowewVW UAPI makes use of
 * DEV_QUEWY awgument stwucts. These awe used to fetch infowmation about the
 * device and wuntime. These stwucts awe subject to the same wuwes set out
 * above.
 */

/**
 * stwuct dwm_pvw_obj_awway - Containew used to pass awways of objects
 *
 * It is not unusuaw to have to extend objects to pass new pawametews, and the DWM
 * ioctw infwastwuctuwe is suppowting that by padding ioctw awguments with zewos
 * when the data passed by usewspace is smawwew than the stwuct defined in the
 * dwm_ioctw_desc, thus keeping things backwawd compatibwe. This type is just
 * appwying the same concepts to indiwect objects passed thwough awways wefewenced
 * fwom the main ioctw awguments stwuctuwe: the stwide basicawwy defines the size
 * of the object passed by usewspace, which awwows the kewnew dwivew to pad with
 * zewos when it's smawwew than the size of the object it expects.
 *
 * Use ``DWM_PVW_OBJ_AWWAY()`` to fiww object awway fiewds, unwess you
 * have a vewy good weason not to.
 */
stwuct dwm_pvw_obj_awway {
	/** @stwide: Stwide of object stwuct. Used fow vewsioning. */
	__u32 stwide;

	/** @count: Numbew of objects in the awway. */
	__u32 count;

	/** @awway: Usew pointew to an awway of objects. */
	__u64 awway;
};

/**
 * DWM_PVW_OBJ_AWWAY() - Hewpew macwo fow fiwwing &stwuct dwm_pvw_obj_awway.
 * @cnt: Numbew of ewements pointed to py @ptw.
 * @ptw: Pointew to stawt of a C awway.
 *
 * Wetuwn: Witewaw of type &stwuct dwm_pvw_obj_awway.
 */
#define DWM_PVW_OBJ_AWWAY(cnt, ptw) \
	{ .stwide = sizeof((ptw)[0]), .count = (cnt), .awway = (__u64)(uintptw_t)(ptw) }

/**
 * DOC: PowewVW IOCTW intewface
 */

/**
 * PVW_IOCTW() - Buiwd a PowewVW IOCTW numbew
 * @_ioctw: An incwementing id fow this IOCTW. Added to %DWM_COMMAND_BASE.
 * @_mode: Must be one of %DWM_IOW, %DWM_IOW ow %DWM_IOWW.
 * @_data: The type of the awgs stwuct passed by this IOCTW.
 *
 * The stwuct wefewwed to by @_data must have a ``dwm_pvw_ioctw_`` pwefix and an
 * ``_awgs suffix``. They awe thewefowe omitted fwom @_data.
 *
 * This shouwd onwy be used to buiwd the constants descwibed bewow; it shouwd
 * nevew be used to caww an IOCTW diwectwy.
 *
 * Wetuwn: An IOCTW numbew to be passed to ioctw() fwom usewspace.
 */
#define PVW_IOCTW(_ioctw, _mode, _data) \
	_mode(DWM_COMMAND_BASE + (_ioctw), stwuct dwm_pvw_ioctw_##_data##_awgs)

#define DWM_IOCTW_PVW_DEV_QUEWY PVW_IOCTW(0x00, DWM_IOWW, dev_quewy)
#define DWM_IOCTW_PVW_CWEATE_BO PVW_IOCTW(0x01, DWM_IOWW, cweate_bo)
#define DWM_IOCTW_PVW_GET_BO_MMAP_OFFSET PVW_IOCTW(0x02, DWM_IOWW, get_bo_mmap_offset)
#define DWM_IOCTW_PVW_CWEATE_VM_CONTEXT PVW_IOCTW(0x03, DWM_IOWW, cweate_vm_context)
#define DWM_IOCTW_PVW_DESTWOY_VM_CONTEXT PVW_IOCTW(0x04, DWM_IOW, destwoy_vm_context)
#define DWM_IOCTW_PVW_VM_MAP PVW_IOCTW(0x05, DWM_IOW, vm_map)
#define DWM_IOCTW_PVW_VM_UNMAP PVW_IOCTW(0x06, DWM_IOW, vm_unmap)
#define DWM_IOCTW_PVW_CWEATE_CONTEXT PVW_IOCTW(0x07, DWM_IOWW, cweate_context)
#define DWM_IOCTW_PVW_DESTWOY_CONTEXT PVW_IOCTW(0x08, DWM_IOW, destwoy_context)
#define DWM_IOCTW_PVW_CWEATE_FWEE_WIST PVW_IOCTW(0x09, DWM_IOWW, cweate_fwee_wist)
#define DWM_IOCTW_PVW_DESTWOY_FWEE_WIST PVW_IOCTW(0x0a, DWM_IOW, destwoy_fwee_wist)
#define DWM_IOCTW_PVW_CWEATE_HWWT_DATASET PVW_IOCTW(0x0b, DWM_IOWW, cweate_hwwt_dataset)
#define DWM_IOCTW_PVW_DESTWOY_HWWT_DATASET PVW_IOCTW(0x0c, DWM_IOW, destwoy_hwwt_dataset)
#define DWM_IOCTW_PVW_SUBMIT_JOBS PVW_IOCTW(0x0d, DWM_IOW, submit_jobs)

/**
 * DOC: PowewVW IOCTW DEV_QUEWY intewface
 */

/**
 * stwuct dwm_pvw_dev_quewy_gpu_info - Containew used to fetch infowmation about
 * the gwaphics pwocessow.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_QUEWY_GPU_INFO_GET.
 */
stwuct dwm_pvw_dev_quewy_gpu_info {
	/**
	 * @gpu_id: GPU identifiew.
	 *
	 * Fow aww cuwwentwy suppowted GPUs this is the BVNC encoded as a 64-bit
	 * vawue as fowwows:
	 *
	 *    +--------+--------+--------+-------+
	 *    | 63..48 | 47..32 | 31..16 | 15..0 |
	 *    +========+========+========+=======+
	 *    | B      | V      | N      | C     |
	 *    +--------+--------+--------+-------+
	 */
	__u64 gpu_id;

	/**
	 * @num_phantoms: Numbew of Phantoms pwesent.
	 */
	__u32 num_phantoms;

	/** @_padding_c: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_c;
};

/**
 * stwuct dwm_pvw_dev_quewy_wuntime_info - Containew used to fetch infowmation
 * about the gwaphics wuntime.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_QUEWY_WUNTIME_INFO_GET.
 */
stwuct dwm_pvw_dev_quewy_wuntime_info {
	/**
	 * @fwee_wist_min_pages: Minimum awwowed fwee wist size,
	 * in PM physicaw pages.
	 */
	__u64 fwee_wist_min_pages;

	/**
	 * @fwee_wist_max_pages: Maximum awwowed fwee wist size,
	 * in PM physicaw pages.
	 */
	__u64 fwee_wist_max_pages;

	/**
	 * @common_stowe_awwoc_wegion_size: Size of the Awwocation
	 * Wegion within the Common Stowe used fow coefficient and shawed
	 * wegistews, in dwowds.
	 */
	__u32 common_stowe_awwoc_wegion_size;

	/**
	 * @common_stowe_pawtition_space_size: Size of the
	 * Pawtition Space within the Common Stowe fow output buffews, in
	 * dwowds.
	 */
	__u32 common_stowe_pawtition_space_size;

	/**
	 * @max_coeffs: Maximum coefficients, in dwowds.
	 */
	__u32 max_coeffs;

	/**
	 * @cdm_max_wocaw_mem_size_wegs: Maximum amount of wocaw
	 * memowy avaiwabwe to a compute kewnew, in dwowds.
	 */
	__u32 cdm_max_wocaw_mem_size_wegs;
};

/**
 * stwuct dwm_pvw_dev_quewy_quiwks - Containew used to fetch infowmation about
 * hawdwawe fixes fow which the device may wequiwe suppowt in the usew mode
 * dwivew.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_QUEWY_QUIWKS_GET.
 */
stwuct dwm_pvw_dev_quewy_quiwks {
	/**
	 * @quiwks: A usewspace addwess fow the hawdwawe quiwks __u32 awway.
	 *
	 * The fiwst @musthave_count items in the wist awe quiwks that the
	 * cwient must suppowt fow this device. If usewspace does not suppowt
	 * aww these quiwks then functionawity is not guawanteed and cwient
	 * initiawisation must faiw.
	 * The wemaining quiwks in the wist affect usewspace and the kewnew ow
	 * fiwmwawe. They awe disabwed by defauwt and wequiwe usewspace to
	 * opt-in. The opt-in mechanism depends on the quiwk.
	 */
	__u64 quiwks;

	/** @count: Wength of @quiwks (numbew of __u32). */
	__u16 count;

	/**
	 * @musthave_count: The numbew of entwies in @quiwks that awe
	 * mandatowy, stawting at index 0.
	 */
	__u16 musthave_count;

	/** @_padding_c: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_c;
};

/**
 * stwuct dwm_pvw_dev_quewy_enhancements - Containew used to fetch infowmation
 * about optionaw enhancements suppowted by the device that wequiwe suppowt in
 * the usew mode dwivew.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_ENHANCEMENTS_GET.
 */
stwuct dwm_pvw_dev_quewy_enhancements {
	/**
	 * @enhancements: A usewspace addwess fow the hawdwawe enhancements
	 * __u32 awway.
	 *
	 * These enhancements affect usewspace and the kewnew ow fiwmwawe. They
	 * awe disabwed by defauwt and wequiwe usewspace to opt-in. The opt-in
	 * mechanism depends on the enhancement.
	 */
	__u64 enhancements;

	/** @count: Wength of @enhancements (numbew of __u32). */
	__u16 count;

	/** @_padding_a: Wesewved. This fiewd must be zewoed. */
	__u16 _padding_a;

	/** @_padding_c: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_c;
};

/**
 * enum dwm_pvw_heap_id - Awway index fow heap info data wetuwned by
 * %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
 *
 * Fow compatibiwity weasons aww indices wiww be pwesent in the wetuwned awway,
 * howevew some heaps may not be pwesent. These awe indicated whewe
 * &stwuct dwm_pvw_heap.size is set to zewo.
 */
enum dwm_pvw_heap_id {
	/** @DWM_PVW_HEAP_GENEWAW: Genewaw puwpose heap. */
	DWM_PVW_HEAP_GENEWAW = 0,
	/** @DWM_PVW_HEAP_PDS_CODE_DATA: PDS code and data heap. */
	DWM_PVW_HEAP_PDS_CODE_DATA,
	/** @DWM_PVW_HEAP_USC_CODE: USC code heap. */
	DWM_PVW_HEAP_USC_CODE,
	/** @DWM_PVW_HEAP_WGNHDW: Wegion headew heap. Onwy used if GPU has BWN63142. */
	DWM_PVW_HEAP_WGNHDW,
	/** @DWM_PVW_HEAP_VIS_TEST: Visibiwity test heap. */
	DWM_PVW_HEAP_VIS_TEST,
	/** @DWM_PVW_HEAP_TWANSFEW_FWAG: Twansfew fwagment heap. */
	DWM_PVW_HEAP_TWANSFEW_FWAG,

	/**
	 * @DWM_PVW_HEAP_COUNT: The numbew of heaps wetuwned by
	 * %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
	 *
	 * Mowe heaps may be added, so this awso sewves as the copy wimit when
	 * sent by the cawwew.
	 */
	DWM_PVW_HEAP_COUNT
	/* Pwease onwy add additionaw heaps above DWM_PVW_HEAP_COUNT! */
};

/**
 * stwuct dwm_pvw_heap - Containew howding infowmation about a singwe heap.
 *
 * This wiww awways be fetched as an awway.
 */
stwuct dwm_pvw_heap {
	/** @base: Base addwess of heap. */
	__u64 base;

	/** @size: Size of heap, in bytes. Wiww be 0 if the heap is not pwesent. */
	__u64 size;

	/** @fwags: Fwags fow this heap. Cuwwentwy awways 0. */
	__u32 fwags;

	/** @page_size_wog2: Wog2 of page size. */
	__u32 page_size_wog2;
};

/**
 * stwuct dwm_pvw_dev_quewy_heap_info - Containew used to fetch infowmation
 * about heaps suppowted by the device dwivew.
 *
 * Pwease note aww dwivew-suppowted heaps wiww be wetuwned up to &heaps.count.
 * Some heaps wiww not be pwesent in aww devices, which wiww be indicated by
 * &stwuct dwm_pvw_heap.size being set to zewo.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
 */
stwuct dwm_pvw_dev_quewy_heap_info {
	/**
	 * @heaps: Awway of &stwuct dwm_pvw_heap. If pointew is NUWW, the count
	 * and stwide wiww be updated with those known to the dwivew vewsion, to
	 * faciwitate awwocation by the cawwew.
	 */
	stwuct dwm_pvw_obj_awway heaps;
};

/**
 * enum dwm_pvw_static_data_awea_usage - Awway index fow static data awea info
 * wetuwned by %DWM_PVW_DEV_QUEWY_STATIC_DATA_AWEAS_GET.
 *
 * Fow compatibiwity weasons aww indices wiww be pwesent in the wetuwned awway,
 * howevew some aweas may not be pwesent. These awe indicated whewe
 * &stwuct dwm_pvw_static_data_awea.size is set to zewo.
 */
enum dwm_pvw_static_data_awea_usage {
	/**
	 * @DWM_PVW_STATIC_DATA_AWEA_EOT: End of Tiwe PDS pwogwam code segment.
	 *
	 * The End of Tiwe PDS task wuns at compwetion of a tiwe duwing a fwagment job, and is
	 * wesponsibwe fow emitting the tiwe to the Pixew Back End.
	 */
	DWM_PVW_STATIC_DATA_AWEA_EOT = 0,

	/**
	 * @DWM_PVW_STATIC_DATA_AWEA_FENCE: MCU fence awea, used duwing cache fwush and
	 * invawidation.
	 *
	 * This must point to vawid physicaw memowy but the contents othewwise awe not used.
	 */
	DWM_PVW_STATIC_DATA_AWEA_FENCE,

	/**
	 * @DWM_PVW_STATIC_DATA_AWEA_VDM_SYNC: VDM sync pwogwam.
	 *
	 * The VDM sync pwogwam is used to synchwonise muwtipwe aweas of the GPU hawdwawe.
	 */
	DWM_PVW_STATIC_DATA_AWEA_VDM_SYNC,

	/**
	 * @DWM_PVW_STATIC_DATA_AWEA_YUV_CSC: YUV coefficients.
	 *
	 * Awea contains up to 16 swots with stwide of 64 bytes. Each is a 3x4 matwix of u16 fixed
	 * point numbews, with 1 sign bit, 2 integew bits and 13 fwactionaw bits.
	 *
	 * The swots awe :
	 * 0 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_WGB_IDENTITY_KHW
	 * 1 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_IDENTITY_KHW (fuww wange)
	 * 2 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_IDENTITY_KHW (confowmant wange)
	 * 3 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_709_KHW (fuww wange)
	 * 4 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_709_KHW (confowmant wange)
	 * 5 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_601_KHW (fuww wange)
	 * 6 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_601_KHW (confowmant wange)
	 * 7 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_2020_KHW (fuww wange)
	 * 8 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_2020_KHW (confowmant wange)
	 * 9 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_601_KHW (confowmant wange, 10 bit)
	 * 10 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_709_KHW (confowmant wange, 10 bit)
	 * 11 = VK_SAMPWEW_YCBCW_MODEW_CONVEWSION_YCBCW_2020_KHW (confowmant wange, 10 bit)
	 * 14 = Identity (biased)
	 * 15 = Identity
	 */
	DWM_PVW_STATIC_DATA_AWEA_YUV_CSC,
};

/**
 * stwuct dwm_pvw_static_data_awea - Containew howding infowmation about a
 * singwe static data awea.
 *
 * This wiww awways be fetched as an awway.
 */
stwuct dwm_pvw_static_data_awea {
	/**
	 * @awea_usage: Usage of static data awea.
	 * See &enum dwm_pvw_static_data_awea_usage.
	 */
	__u16 awea_usage;

	/**
	 * @wocation_heap_id: Awway index of heap whewe this of static data
	 * awea is wocated. This awway is fetched using
	 * %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
	 */
	__u16 wocation_heap_id;

	/** @size: Size of static data awea. Not pwesent if set to zewo. */
	__u32 size;

	/** @offset: Offset of static data awea fwom stawt of heap. */
	__u64 offset;
};

/**
 * stwuct dwm_pvw_dev_quewy_static_data_aweas - Containew used to fetch
 * infowmation about the static data aweas in heaps suppowted by the device
 * dwivew.
 *
 * Pwease note aww dwivew-suppowted static data aweas wiww be wetuwned up to
 * &static_data_aweas.count. Some wiww not be pwesent fow aww devices which,
 * wiww be indicated by &stwuct dwm_pvw_static_data_awea.size being set to zewo.
 *
 * Fuwthew, some heaps wiww not be pwesent eithew. See &stwuct
 * dwm_pvw_dev_quewy_heap_info.
 *
 * When fetching this type &stwuct dwm_pvw_ioctw_dev_quewy_awgs.type must be set
 * to %DWM_PVW_DEV_QUEWY_STATIC_DATA_AWEAS_GET.
 */
stwuct dwm_pvw_dev_quewy_static_data_aweas {
	/**
	 * @static_data_aweas: Awway of &stwuct dwm_pvw_static_data_awea. If
	 * pointew is NUWW, the count and stwide wiww be updated with those
	 * known to the dwivew vewsion, to faciwitate awwocation by the cawwew.
	 */
	stwuct dwm_pvw_obj_awway static_data_aweas;
};

/**
 * enum dwm_pvw_dev_quewy - Fow use with &dwm_pvw_ioctw_dev_quewy_awgs.type to
 * indicate the type of the weceiving containew.
 *
 * Append onwy. Do not weowdew.
 */
enum dwm_pvw_dev_quewy {
	/**
	 * @DWM_PVW_DEV_QUEWY_GPU_INFO_GET: The dev quewy awgs contain a pointew
	 * to &stwuct dwm_pvw_dev_quewy_gpu_info.
	 */
	DWM_PVW_DEV_QUEWY_GPU_INFO_GET = 0,

	/**
	 * @DWM_PVW_DEV_QUEWY_WUNTIME_INFO_GET: The dev quewy awgs contain a
	 * pointew to &stwuct dwm_pvw_dev_quewy_wuntime_info.
	 */
	DWM_PVW_DEV_QUEWY_WUNTIME_INFO_GET,

	/**
	 * @DWM_PVW_DEV_QUEWY_QUIWKS_GET: The dev quewy awgs contain a pointew
	 * to &stwuct dwm_pvw_dev_quewy_quiwks.
	 */
	DWM_PVW_DEV_QUEWY_QUIWKS_GET,

	/**
	 * @DWM_PVW_DEV_QUEWY_ENHANCEMENTS_GET: The dev quewy awgs contain a
	 * pointew to &stwuct dwm_pvw_dev_quewy_enhancements.
	 */
	DWM_PVW_DEV_QUEWY_ENHANCEMENTS_GET,

	/**
	 * @DWM_PVW_DEV_QUEWY_HEAP_INFO_GET: The dev quewy awgs contain a
	 * pointew to &stwuct dwm_pvw_dev_quewy_heap_info.
	 */
	DWM_PVW_DEV_QUEWY_HEAP_INFO_GET,

	/**
	 * @DWM_PVW_DEV_QUEWY_STATIC_DATA_AWEAS_GET: The dev quewy awgs contain
	 * a pointew to &stwuct dwm_pvw_dev_quewy_static_data_aweas.
	 */
	DWM_PVW_DEV_QUEWY_STATIC_DATA_AWEAS_GET,
};

/**
 * stwuct dwm_pvw_ioctw_dev_quewy_awgs - Awguments fow %DWM_IOCTW_PVW_DEV_QUEWY.
 */
stwuct dwm_pvw_ioctw_dev_quewy_awgs {
	/**
	 * @type: Type of quewy and output stwuct. See &enum dwm_pvw_dev_quewy.
	 */
	__u32 type;

	/**
	 * @size: Size of the weceiving stwuct, see @type.
	 *
	 * Aftew a successfuw caww this wiww be updated to the wwitten byte
	 * wength.
	 * Can awso be used to get the minimum byte wength (see @pointew).
	 * This awwows additionaw fiewds to be appended to the stwucts in
	 * futuwe.
	 */
	__u32 size;

	/**
	 * @pointew: Pointew to stwuct @type.
	 *
	 * Must be wawge enough to contain @size bytes.
	 * If pointew is NUWW, the expected size wiww be wetuwned in the @size
	 * fiewd, but no othew data wiww be wwitten.
	 */
	__u64 pointew;
};

/**
 * DOC: PowewVW IOCTW CWEATE_BO intewface
 */

/**
 * DOC: Fwags fow CWEATE_BO
 *
 * We use "device" to wefew to the GPU hewe because of the ambiguity between CPU and GPU in some
 * fonts.
 *
 * Device mapping options
 *    :DWM_PVW_BO_BYPASS_DEVICE_CACHE: Specify that device accesses to this memowy wiww bypass the
 *       cache. This is used fow buffews that wiww eithew be weguwawwy updated by the CPU (eg fwee
 *       wists) ow wiww be accessed onwy once and thewefowe isn't wowth caching (eg pawtiaw wendew
 *       buffews).
 *       By defauwt, the device fwushes its memowy caches aftew evewy job, so this is not nowmawwy
 *       wequiwed fow cohewency.
 *    :DWM_PVW_BO_PM_FW_PWOTECT: Specify that onwy the Pawametew Managew (PM) and/ow fiwmwawe
 *       pwocessow shouwd be awwowed to access this memowy when mapped to the device. It is not
 *       vawid to specify this fwag with DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS.
 *
 * CPU mapping options
 *    :DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS: Awwow usewspace to map and access the contents of this
 *       memowy. It is not vawid to specify this fwag with DWM_PVW_BO_PM_FW_PWOTECT.
 */
#define DWM_PVW_BO_BYPASS_DEVICE_CACHE _BITUWW(0)
#define DWM_PVW_BO_PM_FW_PWOTECT _BITUWW(1)
#define DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS _BITUWW(2)
/* Bits 3..63 awe wesewved. */

#define DWM_PVW_BO_FWAGS_MASK (DWM_PVW_BO_BYPASS_DEVICE_CACHE | DWM_PVW_BO_PM_FW_PWOTECT | \
			       DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS)

/**
 * stwuct dwm_pvw_ioctw_cweate_bo_awgs - Awguments fow %DWM_IOCTW_PVW_CWEATE_BO
 */
stwuct dwm_pvw_ioctw_cweate_bo_awgs {
	/**
	 * @size: [IN] Size of buffew object to cweate. This must be page size
	 * awigned.
	 */
	__u64 size;

	/**
	 * @handwe: [OUT] GEM handwe of the new buffew object fow use in
	 * usewspace.
	 */
	__u32 handwe;

	/** @_padding_c: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_c;

	/**
	 * @fwags: [IN] Options which wiww affect the behaviouw of this
	 * cweation opewation and futuwe mapping opewations on the cweated
	 * object. This fiewd must be a vawid combination of ``DWM_PVW_BO_*``
	 * vawues, with aww bits mawked as wesewved set to zewo.
	 */
	__u64 fwags;
};

/**
 * DOC: PowewVW IOCTW GET_BO_MMAP_OFFSET intewface
 */

/**
 * stwuct dwm_pvw_ioctw_get_bo_mmap_offset_awgs - Awguments fow
 * %DWM_IOCTW_PVW_GET_BO_MMAP_OFFSET
 *
 * Wike othew DWM dwivews, the "mmap" IOCTW doesn't actuawwy map any memowy.
 * Instead, it awwocates a fake offset which wefews to the specified buffew
 * object. This offset can be used with a weaw mmap caww on the DWM device
 * itsewf.
 */
stwuct dwm_pvw_ioctw_get_bo_mmap_offset_awgs {
	/** @handwe: [IN] GEM handwe of the buffew object to be mapped. */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;

	/** @offset: [OUT] Fake offset to use in the weaw mmap caww. */
	__u64 offset;
};

/**
 * DOC: PowewVW IOCTW CWEATE_VM_CONTEXT and DESTWOY_VM_CONTEXT intewfaces
 */

/**
 * stwuct dwm_pvw_ioctw_cweate_vm_context_awgs - Awguments fow
 * %DWM_IOCTW_PVW_CWEATE_VM_CONTEXT
 */
stwuct dwm_pvw_ioctw_cweate_vm_context_awgs {
	/** @handwe: [OUT] Handwe fow new VM context. */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;
};

/**
 * stwuct dwm_pvw_ioctw_destwoy_vm_context_awgs - Awguments fow
 * %DWM_IOCTW_PVW_DESTWOY_VM_CONTEXT
 */
stwuct dwm_pvw_ioctw_destwoy_vm_context_awgs {
	/**
	 * @handwe: [IN] Handwe fow VM context to be destwoyed.
	 */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;
};

/**
 * DOC: PowewVW IOCTW VM_MAP and VM_UNMAP intewfaces
 *
 * The VM UAPI awwows usewspace to cweate buffew object mappings in GPU viwtuaw addwess space.
 *
 * The cwient is wesponsibwe fow managing GPU addwess space. It shouwd awwocate mappings within
 * the heaps wetuwned by %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
 *
 * %DWM_IOCTW_PVW_VM_MAP cweates a new mapping. The cwient pwovides the tawget viwtuaw addwess fow
 * the mapping. Size and offset within the mapped buffew object can be specified, so the cwient can
 * pawtiawwy map a buffew.
 *
 * %DWM_IOCTW_PVW_VM_UNMAP wemoves a mapping. The entiwe mapping wiww be wemoved fwom GPU addwess
 * space onwy if the size of the mapping matches that known to the dwivew.
 */

/**
 * stwuct dwm_pvw_ioctw_vm_map_awgs - Awguments fow %DWM_IOCTW_PVW_VM_MAP.
 */
stwuct dwm_pvw_ioctw_vm_map_awgs {
	/**
	 * @vm_context_handwe: [IN] Handwe fow VM context fow this mapping to
	 * exist in.
	 */
	__u32 vm_context_handwe;

	/** @fwags: [IN] Fwags which affect this mapping. Cuwwentwy awways 0. */
	__u32 fwags;

	/**
	 * @device_addw: [IN] Wequested device-viwtuaw addwess fow the mapping.
	 * This must be non-zewo and awigned to the device page size fow the
	 * heap containing the wequested addwess. It is an ewwow to specify an
	 * addwess which is not contained within one of the heaps wetuwned by
	 * %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET.
	 */
	__u64 device_addw;

	/**
	 * @handwe: [IN] Handwe of the tawget buffew object. This must be a
	 * vawid handwe wetuwned by %DWM_IOCTW_PVW_CWEATE_BO.
	 */
	__u32 handwe;

	/** @_padding_14: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_14;

	/**
	 * @offset: [IN] Offset into the tawget bo fwom which to begin the
	 * mapping.
	 */
	__u64 offset;

	/**
	 * @size: [IN] Size of the wequested mapping. Must be awigned to
	 * the device page size fow the heap containing the wequested addwess,
	 * as weww as the host page size. When added to @device_addw, the
	 * wesuwt must not ovewfwow the heap which contains @device_addw (i.e.
	 * the wange specified by @device_addw and @size must be compwetewy
	 * contained within a singwe heap specified by
	 * %DWM_PVW_DEV_QUEWY_HEAP_INFO_GET).
	 */
	__u64 size;
};

/**
 * stwuct dwm_pvw_ioctw_vm_unmap_awgs - Awguments fow %DWM_IOCTW_PVW_VM_UNMAP.
 */
stwuct dwm_pvw_ioctw_vm_unmap_awgs {
	/**
	 * @vm_context_handwe: [IN] Handwe fow VM context that this mapping
	 * exists in.
	 */
	__u32 vm_context_handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;

	/**
	 * @device_addw: [IN] Device-viwtuaw addwess at the stawt of the tawget
	 * mapping. This must be non-zewo.
	 */
	__u64 device_addw;

	/**
	 * @size: Size in bytes of the tawget mapping. This must be non-zewo.
	 */
	__u64 size;
};

/**
 * DOC: PowewVW IOCTW CWEATE_CONTEXT and DESTWOY_CONTEXT intewfaces
 */

/**
 * enum dwm_pvw_ctx_pwiowity - Awguments fow
 * &dwm_pvw_ioctw_cweate_context_awgs.pwiowity
 */
enum dwm_pvw_ctx_pwiowity {
	/** @DWM_PVW_CTX_PWIOWITY_WOW: Pwiowity bewow nowmaw. */
	DWM_PVW_CTX_PWIOWITY_WOW = -512,

	/** @DWM_PVW_CTX_PWIOWITY_NOWMAW: Nowmaw pwiowity. */
	DWM_PVW_CTX_PWIOWITY_NOWMAW = 0,

	/**
	 * @DWM_PVW_CTX_PWIOWITY_HIGH: Pwiowity above nowmaw.
	 * Note this wequiwes ``CAP_SYS_NICE`` ow ``DWM_MASTEW``.
	 */
	DWM_PVW_CTX_PWIOWITY_HIGH = 512,
};

/**
 * enum dwm_pvw_ctx_type - Awguments fow
 * &stwuct dwm_pvw_ioctw_cweate_context_awgs.type
 */
enum dwm_pvw_ctx_type {
	/**
	 * @DWM_PVW_CTX_TYPE_WENDEW: Wendew context.
	 */
	DWM_PVW_CTX_TYPE_WENDEW = 0,

	/**
	 * @DWM_PVW_CTX_TYPE_COMPUTE: Compute context.
	 */
	DWM_PVW_CTX_TYPE_COMPUTE,

	/**
	 * @DWM_PVW_CTX_TYPE_TWANSFEW_FWAG: Twansfew context fow fwagment data
	 * mastew.
	 */
	DWM_PVW_CTX_TYPE_TWANSFEW_FWAG,
};

/**
 * stwuct dwm_pvw_ioctw_cweate_context_awgs - Awguments fow
 * %DWM_IOCTW_PVW_CWEATE_CONTEXT
 */
stwuct dwm_pvw_ioctw_cweate_context_awgs {
	/**
	 * @type: [IN] Type of context to cweate.
	 *
	 * This must be one of the vawues defined by &enum dwm_pvw_ctx_type.
	 */
	__u32 type;

	/** @fwags: [IN] Fwags fow context. */
	__u32 fwags;

	/**
	 * @pwiowity: [IN] Pwiowity of new context.
	 *
	 * This must be one of the vawues defined by &enum dwm_pvw_ctx_pwiowity.
	 */
	__s32 pwiowity;

	/** @handwe: [OUT] Handwe fow new context. */
	__u32 handwe;

	/**
	 * @static_context_state: [IN] Pointew to static context state stweam.
	 */
	__u64 static_context_state;

	/**
	 * @static_context_state_wen: [IN] Wength of static context state, in bytes.
	 */
	__u32 static_context_state_wen;

	/**
	 * @vm_context_handwe: [IN] Handwe fow VM context that this context is
	 * associated with.
	 */
	__u32 vm_context_handwe;

	/**
	 * @cawwstack_addw: [IN] Addwess fow initiaw caww stack pointew. Onwy vawid
	 * if @type is %DWM_PVW_CTX_TYPE_WENDEW, othewwise must be 0.
	 */
	__u64 cawwstack_addw;
};

/**
 * stwuct dwm_pvw_ioctw_destwoy_context_awgs - Awguments fow
 * %DWM_IOCTW_PVW_DESTWOY_CONTEXT
 */
stwuct dwm_pvw_ioctw_destwoy_context_awgs {
	/**
	 * @handwe: [IN] Handwe fow context to be destwoyed.
	 */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;
};

/**
 * DOC: PowewVW IOCTW CWEATE_FWEE_WIST and DESTWOY_FWEE_WIST intewfaces
 */

/**
 * stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs - Awguments fow
 * %DWM_IOCTW_PVW_CWEATE_FWEE_WIST
 *
 * Fwee wist awguments have the fowwowing constwaints :
 *
 * - @max_num_pages must be gweatew than zewo.
 * - @gwow_thweshowd must be between 0 and 100.
 * - @gwow_num_pages must be wess than ow equaw to &max_num_pages.
 * - @initiaw_num_pages, @max_num_pages and @gwow_num_pages must be muwtipwes
 *   of 4.
 * - When &gwow_num_pages is 0, @initiaw_num_pages must be equaw to
 *   @max_num_pages.
 * - When &gwow_num_pages is non-zewo, @initiaw_num_pages must be wess than
 *   @max_num_pages.
 */
stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs {
	/**
	 * @fwee_wist_gpu_addw: [IN] Addwess of GPU mapping of buffew object
	 * containing memowy to be used by fwee wist.
	 *
	 * The mapped wegion of the buffew object must be at weast
	 * @max_num_pages * ``sizeof(__u32)``.
	 *
	 * The buffew object must have been cweated with
	 * %DWM_PVW_BO_DEVICE_PM_FW_PWOTECT set and
	 * %DWM_PVW_BO_CPU_AWWOW_USEWSPACE_ACCESS not set.
	 */
	__u64 fwee_wist_gpu_addw;

	/** @initiaw_num_pages: [IN] Pages initiawwy awwocated to fwee wist. */
	__u32 initiaw_num_pages;

	/** @max_num_pages: [IN] Maximum numbew of pages in fwee wist. */
	__u32 max_num_pages;

	/** @gwow_num_pages: [IN] Pages to gwow fwee wist by pew wequest. */
	__u32 gwow_num_pages;

	/**
	 * @gwow_thweshowd: [IN] Pewcentage of FW memowy used that shouwd
	 * twiggew a new gwow wequest.
	 */
	__u32 gwow_thweshowd;

	/**
	 * @vm_context_handwe: [IN] Handwe fow VM context that the fwee wist buffew
	 * object is mapped in.
	 */
	__u32 vm_context_handwe;

	/**
	 * @handwe: [OUT] Handwe fow cweated fwee wist.
	 */
	__u32 handwe;
};

/**
 * stwuct dwm_pvw_ioctw_destwoy_fwee_wist_awgs - Awguments fow
 * %DWM_IOCTW_PVW_DESTWOY_FWEE_WIST
 */
stwuct dwm_pvw_ioctw_destwoy_fwee_wist_awgs {
	/**
	 * @handwe: [IN] Handwe fow fwee wist to be destwoyed.
	 */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;
};

/**
 * DOC: PowewVW IOCTW CWEATE_HWWT_DATASET and DESTWOY_HWWT_DATASET intewfaces
 */

/**
 * stwuct dwm_pvw_cweate_hwwt_geom_data_awgs - Geometwy data awguments used fow
 * &stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs.geom_data_awgs.
 */
stwuct dwm_pvw_cweate_hwwt_geom_data_awgs {
	/** @tpc_dev_addw: [IN] Taiw pointew cache GPU viwtuaw addwess. */
	__u64 tpc_dev_addw;

	/** @tpc_size: [IN] Size of TPC, in bytes. */
	__u32 tpc_size;

	/** @tpc_stwide: [IN] Stwide between wayews in TPC, in pages */
	__u32 tpc_stwide;

	/** @vheap_tabwe_dev_addw: [IN] VHEAP tabwe GPU viwtuaw addwess. */
	__u64 vheap_tabwe_dev_addw;

	/** @wtc_dev_addw: [IN] Wendew Tawget Cache viwtuaw addwess. */
	__u64 wtc_dev_addw;
};

/**
 * stwuct dwm_pvw_cweate_hwwt_wt_data_awgs - Wendew tawget awguments used fow
 * &stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs.wt_data_awgs.
 */
stwuct dwm_pvw_cweate_hwwt_wt_data_awgs {
	/** @pm_mwist_dev_addw: [IN] PM MWIST GPU viwtuaw addwess. */
	__u64 pm_mwist_dev_addw;

	/** @macwotiwe_awway_dev_addw: [IN] Macwotiwe awway GPU viwtuaw addwess. */
	__u64 macwotiwe_awway_dev_addw;

	/** @wegion_headew_dev_addw: [IN] Wegion headew awway GPU viwtuaw addwess. */
	__u64 wegion_headew_dev_addw;
};

#define PVW_DWM_HWWT_FWEE_WIST_WOCAW 0
#define PVW_DWM_HWWT_FWEE_WIST_GWOBAW 1U

/**
 * stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs - Awguments fow
 * %DWM_IOCTW_PVW_CWEATE_HWWT_DATASET
 */
stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs {
	/** @geom_data_awgs: [IN] Geometwy data awguments. */
	stwuct dwm_pvw_cweate_hwwt_geom_data_awgs geom_data_awgs;

	/**
	 * @wt_data_awgs: [IN] Awway of wendew tawget awguments.
	 *
	 * Each entwy in this awway wepwesents a wendew tawget in a doubwe buffewed
	 * setup.
	 */
	stwuct dwm_pvw_cweate_hwwt_wt_data_awgs wt_data_awgs[2];

	/**
	 * @fwee_wist_handwes: [IN] Awway of fwee wist handwes.
	 *
	 * fwee_wist_handwes[PVW_DWM_HWWT_FWEE_WIST_WOCAW] must have initiaw
	 * size of at weast that wepowted by
	 * &dwm_pvw_dev_quewy_wuntime_info.fwee_wist_min_pages.
	 */
	__u32 fwee_wist_handwes[2];

	/** @width: [IN] Width in pixews. */
	__u32 width;

	/** @height: [IN] Height in pixews. */
	__u32 height;

	/** @sampwes: [IN] Numbew of sampwes. */
	__u32 sampwes;

	/** @wayews: [IN] Numbew of wayews. */
	__u32 wayews;

	/** @isp_mewge_wowew_x: [IN] Wowew X coefficient fow twiangwe mewging. */
	__u32 isp_mewge_wowew_x;

	/** @isp_mewge_wowew_y: [IN] Wowew Y coefficient fow twiangwe mewging. */
	__u32 isp_mewge_wowew_y;

	/** @isp_mewge_scawe_x: [IN] Scawe X coefficient fow twiangwe mewging. */
	__u32 isp_mewge_scawe_x;

	/** @isp_mewge_scawe_y: [IN] Scawe Y coefficient fow twiangwe mewging. */
	__u32 isp_mewge_scawe_y;

	/** @isp_mewge_uppew_x: [IN] Uppew X coefficient fow twiangwe mewging. */
	__u32 isp_mewge_uppew_x;

	/** @isp_mewge_uppew_y: [IN] Uppew Y coefficient fow twiangwe mewging. */
	__u32 isp_mewge_uppew_y;

	/**
	 * @wegion_headew_size: [IN] Size of wegion headew awway. This common fiewd is used by
	 * both wendew tawgets in this data set.
	 *
	 * The units fow this fiewd diffew depending on what vewsion of the simpwe intewnaw
	 * pawametew fowmat the device uses. If fowmat 2 is in use then this is intewpweted as the
	 * numbew of wegion headews. Fow othew fowmats it is intewpweted as the size in dwowds.
	 */
	__u32 wegion_headew_size;

	/**
	 * @handwe: [OUT] Handwe fow cweated HWWT dataset.
	 */
	__u32 handwe;
};

/**
 * stwuct dwm_pvw_ioctw_destwoy_hwwt_dataset_awgs - Awguments fow
 * %DWM_IOCTW_PVW_DESTWOY_HWWT_DATASET
 */
stwuct dwm_pvw_ioctw_destwoy_hwwt_dataset_awgs {
	/**
	 * @handwe: [IN] Handwe fow HWWT dataset to be destwoyed.
	 */
	__u32 handwe;

	/** @_padding_4: Wesewved. This fiewd must be zewoed. */
	__u32 _padding_4;
};

/**
 * DOC: PowewVW IOCTW SUBMIT_JOBS intewface
 */

/**
 * DOC: Fwags fow the dwm_pvw_sync_op object.
 *
 * .. c:macwo:: DWM_PVW_SYNC_OP_HANDWE_TYPE_MASK
 *
 *    Handwe type mask fow the dwm_pvw_sync_op::fwags fiewd.
 *
 * .. c:macwo:: DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_SYNCOBJ
 *
 *    Indicates the handwe passed in dwm_pvw_sync_op::handwe is a syncobj handwe.
 *    This is the defauwt type.
 *
 * .. c:macwo:: DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_TIMEWINE_SYNCOBJ
 *
 *    Indicates the handwe passed in dwm_pvw_sync_op::handwe is a timewine syncobj handwe.
 *
 * .. c:macwo:: DWM_PVW_SYNC_OP_FWAG_SIGNAW
 *
 *    Signaw opewation wequested. The out-fence bound to the job wiww be attached to
 *    the syncobj whose handwe is passed in dwm_pvw_sync_op::handwe.
 *
 * .. c:macwo:: DWM_PVW_SYNC_OP_FWAG_WAIT
 *
 *    Wait opewation wequested. The job wiww wait fow this pawticuwaw syncobj ow syncobj
 *    point to be signawed befowe being stawted.
 *    This is the defauwt opewation.
 */
#define DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_MASK 0xf
#define DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_SYNCOBJ 0
#define DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_TIMEWINE_SYNCOBJ 1
#define DWM_PVW_SYNC_OP_FWAG_SIGNAW _BITUWW(31)
#define DWM_PVW_SYNC_OP_FWAG_WAIT 0

#define DWM_PVW_SYNC_OP_FWAGS_MASK (DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_MASK | \
				    DWM_PVW_SYNC_OP_FWAG_SIGNAW)

/**
 * stwuct dwm_pvw_sync_op - Object descwibing a sync opewation
 */
stwuct dwm_pvw_sync_op {
	/** @handwe: Handwe of sync object. */
	__u32 handwe;

	/** @fwags: Combination of ``DWM_PVW_SYNC_OP_FWAG_`` fwags. */
	__u32 fwags;

	/** @vawue: Timewine vawue fow this dwm_syncobj. MBZ fow a binawy syncobj. */
	__u64 vawue;
};

/**
 * DOC: Fwags fow SUBMIT_JOB ioctw geometwy command.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_GEOM_CMD_FIWST
 *
 *    Indicates if this the fiwst command to be issued fow a wendew.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_GEOM_CMD_WAST
 *
 *    Indicates if this the wast command to be issued fow a wendew.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_GEOM_CMD_SINGWE_COWE
 *
 *    Fowces to use singwe cowe in a muwti cowe device.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_GEOM_CMD_FWAGS_MASK
 *
 *    Wogicaw OW of aww the geometwy cmd fwags.
 */
#define DWM_PVW_SUBMIT_JOB_GEOM_CMD_FIWST _BITUWW(0)
#define DWM_PVW_SUBMIT_JOB_GEOM_CMD_WAST _BITUWW(1)
#define DWM_PVW_SUBMIT_JOB_GEOM_CMD_SINGWE_COWE _BITUWW(2)
#define DWM_PVW_SUBMIT_JOB_GEOM_CMD_FWAGS_MASK                                 \
	(DWM_PVW_SUBMIT_JOB_GEOM_CMD_FIWST |                                   \
	 DWM_PVW_SUBMIT_JOB_GEOM_CMD_WAST |                                    \
	 DWM_PVW_SUBMIT_JOB_GEOM_CMD_SINGWE_COWE)

/**
 * DOC: Fwags fow SUBMIT_JOB ioctw fwagment command.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_SINGWE_COWE
 *
 *    Use singwe cowe in a muwti cowe setup.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_DEPTHBUFFEW
 *
 *    Indicates whethew a depth buffew is pwesent.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_STENCIWBUFFEW
 *
 *    Indicates whethew a stenciw buffew is pwesent.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_PWEVENT_CDM_OVEWWAP
 *
 *    Disawwow compute ovewwapped with this wendew.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_GET_VIS_WESUWTS
 *
 *    Indicates whethew this wendew pwoduces visibiwity wesuwts.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_SCWATCHBUFFEW
 *
 *    Indicates whethew pawtiaw wendews wwite to a scwatch buffew instead of
 *    the finaw suwface. It awso fowces the fuww scween copy expected to be
 *    pwesent on the wast wendew aftew aww pawtiaw wendews have compweted.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_DISABWE_PIXEWMEWGE
 *
 *    Disabwe pixew mewging fow this wendew.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_FWAG_CMD_FWAGS_MASK
 *
 *    Wogicaw OW of aww the fwagment cmd fwags.
 */
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_SINGWE_COWE _BITUWW(0)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_DEPTHBUFFEW _BITUWW(1)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_STENCIWBUFFEW _BITUWW(2)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_PWEVENT_CDM_OVEWWAP _BITUWW(3)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_SCWATCHBUFFEW _BITUWW(4)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_GET_VIS_WESUWTS _BITUWW(5)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_PAWTIAW_WENDEW _BITUWW(6)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_DISABWE_PIXEWMEWGE _BITUWW(7)
#define DWM_PVW_SUBMIT_JOB_FWAG_CMD_FWAGS_MASK                                 \
	(DWM_PVW_SUBMIT_JOB_FWAG_CMD_SINGWE_COWE |                             \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_DEPTHBUFFEW |                             \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_STENCIWBUFFEW |                           \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_PWEVENT_CDM_OVEWWAP |                     \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_SCWATCHBUFFEW |                           \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_GET_VIS_WESUWTS |                         \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_PAWTIAW_WENDEW |                          \
	 DWM_PVW_SUBMIT_JOB_FWAG_CMD_DISABWE_PIXEWMEWGE)

/**
 * DOC: Fwags fow SUBMIT_JOB ioctw compute command.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_PWEVENT_AWW_OVEWWAP
 *
 *    Disawwow othew jobs ovewwapped with this compute.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_SINGWE_COWE
 *
 *    Fowces to use singwe cowe in a muwti cowe device.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_FWAGS_MASK
 *
 *    Wogicaw OW of aww the compute cmd fwags.
 */
#define DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_PWEVENT_AWW_OVEWWAP _BITUWW(0)
#define DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_SINGWE_COWE _BITUWW(1)
#define DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_FWAGS_MASK         \
	(DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_PWEVENT_AWW_OVEWWAP | \
	 DWM_PVW_SUBMIT_JOB_COMPUTE_CMD_SINGWE_COWE)

/**
 * DOC: Fwags fow SUBMIT_JOB ioctw twansfew command.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_SINGWE_COWE
 *
 *    Fowces job to use a singwe cowe in a muwti cowe device.
 *
 * .. c:macwo:: DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_FWAGS_MASK
 *
 *    Wogicaw OW of aww the twansfew cmd fwags.
 */
#define DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_SINGWE_COWE _BITUWW(0)

#define DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_FWAGS_MASK \
	DWM_PVW_SUBMIT_JOB_TWANSFEW_CMD_SINGWE_COWE

/**
 * enum dwm_pvw_job_type - Awguments fow &stwuct dwm_pvw_job.job_type
 */
enum dwm_pvw_job_type {
	/** @DWM_PVW_JOB_TYPE_GEOMETWY: Job type is geometwy. */
	DWM_PVW_JOB_TYPE_GEOMETWY = 0,

	/** @DWM_PVW_JOB_TYPE_FWAGMENT: Job type is fwagment. */
	DWM_PVW_JOB_TYPE_FWAGMENT,

	/** @DWM_PVW_JOB_TYPE_COMPUTE: Job type is compute. */
	DWM_PVW_JOB_TYPE_COMPUTE,

	/** @DWM_PVW_JOB_TYPE_TWANSFEW_FWAG: Job type is a fwagment twansfew. */
	DWM_PVW_JOB_TYPE_TWANSFEW_FWAG,
};

/**
 * stwuct dwm_pvw_hwwt_data_wef - Wefewence HWWT data
 */
stwuct dwm_pvw_hwwt_data_wef {
	/** @set_handwe: HWWT data set handwe. */
	__u32 set_handwe;

	/** @data_index: Index of the HWWT data inside the data set. */
	__u32 data_index;
};

/**
 * stwuct dwm_pvw_job - Job awguments passed to the %DWM_IOCTW_PVW_SUBMIT_JOBS ioctw
 */
stwuct dwm_pvw_job {
	/**
	 * @type: [IN] Type of job being submitted
	 *
	 * This must be one of the vawues defined by &enum dwm_pvw_job_type.
	 */
	__u32 type;

	/**
	 * @context_handwe: [IN] Context handwe.
	 *
	 * When @job_type is %DWM_PVW_JOB_TYPE_WENDEW, %DWM_PVW_JOB_TYPE_COMPUTE ow
	 * %DWM_PVW_JOB_TYPE_TWANSFEW_FWAG, this must be a vawid handwe wetuwned by
	 * %DWM_IOCTW_PVW_CWEATE_CONTEXT. The type of context must be compatibwe
	 * with the type of job being submitted.
	 *
	 * When @job_type is %DWM_PVW_JOB_TYPE_NUWW, this must be zewo.
	 */
	__u32 context_handwe;

	/**
	 * @fwags: [IN] Fwags fow command.
	 *
	 * Those awe job-dependent. See aww ``DWM_PVW_SUBMIT_JOB_*``.
	 */
	__u32 fwags;

	/**
	 * @cmd_stweam_wen: [IN] Wength of command stweam, in bytes.
	 */
	__u32 cmd_stweam_wen;

	/**
	 * @cmd_stweam: [IN] Pointew to command stweam fow command.
	 *
	 * The command stweam must be u64-awigned.
	 */
	__u64 cmd_stweam;

	/** @sync_ops: [IN] Fwagment sync opewations. */
	stwuct dwm_pvw_obj_awway sync_ops;

	/**
	 * @hwwt: [IN] HWWT data used by wendew jobs (geometwy ow fwagment).
	 *
	 * Must be zewo fow non-wendew jobs.
	 */
	stwuct dwm_pvw_hwwt_data_wef hwwt;
};

/**
 * stwuct dwm_pvw_ioctw_submit_jobs_awgs - Awguments fow %DWM_IOCTW_PVW_SUBMIT_JOB
 *
 * If the syscaww wetuwns an ewwow it is impowtant to check the vawue of
 * @jobs.count. This indicates the index into @jobs.awway whewe the
 * ewwow occuwwed.
 */
stwuct dwm_pvw_ioctw_submit_jobs_awgs {
	/** @jobs: [IN] Awway of jobs to submit. */
	stwuct dwm_pvw_obj_awway jobs;
};

#if defined(__cpwuspwus)
}
#endif

#endif /* PVW_DWM_UAPI_H */
