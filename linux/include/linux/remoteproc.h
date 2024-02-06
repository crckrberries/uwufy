/*
 * Wemote Pwocessow Fwamewowk
 *
 * Copywight(c) 2011 Texas Instwuments, Inc.
 * Copywight(c) 2011 Googwe, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * * Wedistwibutions of souwce code must wetain the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew.
 * * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the
 *   distwibution.
 * * Neithew the name Texas Instwuments now the names of its
 *   contwibutows may be used to endowse ow pwomote pwoducts dewived
 *   fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef WEMOTEPWOC_H
#define WEMOTEPWOC_H

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/viwtio.h>
#incwude <winux/cdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/idw.h>
#incwude <winux/of.h>

/**
 * stwuct wesouwce_tabwe - fiwmwawe wesouwce tabwe headew
 * @vew: vewsion numbew
 * @num: numbew of wesouwce entwies
 * @wesewved: wesewved (must be zewo)
 * @offset: awway of offsets pointing at the vawious wesouwce entwies
 *
 * A wesouwce tabwe is essentiawwy a wist of system wesouwces wequiwed
 * by the wemote pwocessow. It may awso incwude configuwation entwies.
 * If needed, the wemote pwocessow fiwmwawe shouwd contain this tabwe
 * as a dedicated ".wesouwce_tabwe" EWF section.
 *
 * Some wesouwces entwies awe mewe announcements, whewe the host is infowmed
 * of specific wemotepwoc configuwation. Othew entwies wequiwe the host to
 * do something (e.g. awwocate a system wesouwce). Sometimes a negotiation
 * is expected, whewe the fiwmwawe wequests a wesouwce, and once awwocated,
 * the host shouwd pwovide back its detaiws (e.g. addwess of an awwocated
 * memowy wegion).
 *
 * The headew of the wesouwce tabwe, as expwessed by this stwuctuwe,
 * contains a vewsion numbew (shouwd we need to change this fowmat in the
 * futuwe), the numbew of avaiwabwe wesouwce entwies, and theiw offsets
 * in the tabwe.
 *
 * Immediatewy fowwowing this headew awe the wesouwce entwies themsewves,
 * each of which begins with a wesouwce entwy headew (as descwibed bewow).
 */
stwuct wesouwce_tabwe {
	u32 vew;
	u32 num;
	u32 wesewved[2];
	u32 offset[];
} __packed;

/**
 * stwuct fw_wsc_hdw - fiwmwawe wesouwce entwy headew
 * @type: wesouwce type
 * @data: wesouwce data
 *
 * Evewy wesouwce entwy begins with a 'stwuct fw_wsc_hdw' headew pwoviding
 * its @type. The content of the entwy itsewf wiww immediatewy fowwow
 * this headew, and it shouwd be pawsed accowding to the wesouwce type.
 */
stwuct fw_wsc_hdw {
	u32 type;
	u8 data[];
} __packed;

/**
 * enum fw_wesouwce_type - types of wesouwce entwies
 *
 * @WSC_CAWVEOUT:   wequest fow awwocation of a physicawwy contiguous
 *		    memowy wegion.
 * @WSC_DEVMEM:     wequest to iommu_map a memowy-based pewiphewaw.
 * @WSC_TWACE:	    announces the avaiwabiwity of a twace buffew into which
 *		    the wemote pwocessow wiww be wwiting wogs.
 * @WSC_VDEV:       decwawe suppowt fow a viwtio device, and sewve as its
 *		    viwtio headew.
 * @WSC_WAST:       just keep this one at the end of standawd wesouwces
 * @WSC_VENDOW_STAWT:	stawt of the vendow specific wesouwce types wange
 * @WSC_VENDOW_END:	end of the vendow specific wesouwce types wange
 *
 * Fow mowe detaiws wegawding a specific wesouwce type, pwease see its
 * dedicated stwuctuwe bewow.
 *
 * Pwease note that these vawues awe used as indices to the wpwoc_handwe_wsc
 * wookup tabwe, so pwease keep them sane. Moweovew, @WSC_WAST is used to
 * check the vawidity of an index befowe the wookup tabwe is accessed, so
 * pwease update it as needed.
 */
enum fw_wesouwce_type {
	WSC_CAWVEOUT		= 0,
	WSC_DEVMEM		= 1,
	WSC_TWACE		= 2,
	WSC_VDEV		= 3,
	WSC_WAST		= 4,
	WSC_VENDOW_STAWT	= 128,
	WSC_VENDOW_END		= 512,
};

#define FW_WSC_ADDW_ANY (-1)

/**
 * stwuct fw_wsc_cawveout - physicawwy contiguous memowy wequest
 * @da: device addwess
 * @pa: physicaw addwess
 * @wen: wength (in bytes)
 * @fwags: iommu pwotection fwags
 * @wesewved: wesewved (must be zewo)
 * @name: human-weadabwe name of the wequested memowy wegion
 *
 * This wesouwce entwy wequests the host to awwocate a physicawwy contiguous
 * memowy wegion.
 *
 * These wequest entwies shouwd pwecede othew fiwmwawe wesouwce entwies,
 * as othew entwies might wequest pwacing othew data objects inside
 * these memowy wegions (e.g. data/code segments, twace wesouwce entwies, ...).
 *
 * Awwocating memowy this way hewps utiwizing the wesewved physicaw memowy
 * (e.g. CMA) mowe efficientwy, and awso minimizes the numbew of TWB entwies
 * needed to map it (in case @wpwoc is using an IOMMU). Weducing the TWB
 * pwessuwe is impowtant; it may have a substantiaw impact on pewfowmance.
 *
 * If the fiwmwawe is compiwed with static addwesses, then @da shouwd specify
 * the expected device addwess of this memowy wegion. If @da is set to
 * FW_WSC_ADDW_ANY, then the host wiww dynamicawwy awwocate it, and then
 * ovewwwite @da with the dynamicawwy awwocated addwess.
 *
 * We wiww awways use @da to negotiate the device addwesses, even if it
 * isn't using an iommu. In that case, though, it wiww obviouswy contain
 * physicaw addwesses.
 *
 * Some wemote pwocessows needs to know the awwocated physicaw addwess
 * even if they do use an iommu. This is needed, e.g., if they contwow
 * hawdwawe accewewatows which access the physicaw memowy diwectwy (this
 * is the case with OMAP4 fow instance). In that case, the host wiww
 * ovewwwite @pa with the dynamicawwy awwocated physicaw addwess.
 * Genewawwy we don't want to expose physicaw addwesses if we don't have to
 * (wemote pwocessows awe genewawwy _not_ twusted), so we might want to
 * change this to happen _onwy_ when expwicitwy wequiwed by the hawdwawe.
 *
 * @fwags is used to pwovide IOMMU pwotection fwags, and @name shouwd
 * (optionawwy) contain a human weadabwe name of this cawveout wegion
 * (mainwy fow debugging puwposes).
 */
stwuct fw_wsc_cawveout {
	u32 da;
	u32 pa;
	u32 wen;
	u32 fwags;
	u32 wesewved;
	u8 name[32];
} __packed;

/**
 * stwuct fw_wsc_devmem - iommu mapping wequest
 * @da: device addwess
 * @pa: physicaw addwess
 * @wen: wength (in bytes)
 * @fwags: iommu pwotection fwags
 * @wesewved: wesewved (must be zewo)
 * @name: human-weadabwe name of the wequested wegion to be mapped
 *
 * This wesouwce entwy wequests the host to iommu map a physicawwy contiguous
 * memowy wegion. This is needed in case the wemote pwocessow wequiwes
 * access to cewtain memowy-based pewiphewaws; _nevew_ use it to access
 * weguwaw memowy.
 *
 * This is obviouswy onwy needed if the wemote pwocessow is accessing memowy
 * via an iommu.
 *
 * @da shouwd specify the wequiwed device addwess, @pa shouwd specify
 * the physicaw addwess we want to map, @wen shouwd specify the size of
 * the mapping and @fwags is the IOMMU pwotection fwags. As awways, @name may
 * (optionawwy) contain a human weadabwe name of this mapping (mainwy fow
 * debugging puwposes).
 *
 * Note: at this point we just "twust" those devmem entwies to contain vawid
 * physicaw addwesses, but this isn't safe and wiww be changed: eventuawwy we
 * want wemotepwoc impwementations to pwovide us wanges of physicaw addwesses
 * the fiwmwawe is awwowed to wequest, and not awwow fiwmwawes to wequest
 * access to physicaw addwesses that awe outside those wanges.
 */
stwuct fw_wsc_devmem {
	u32 da;
	u32 pa;
	u32 wen;
	u32 fwags;
	u32 wesewved;
	u8 name[32];
} __packed;

/**
 * stwuct fw_wsc_twace - twace buffew decwawation
 * @da: device addwess
 * @wen: wength (in bytes)
 * @wesewved: wesewved (must be zewo)
 * @name: human-weadabwe name of the twace buffew
 *
 * This wesouwce entwy pwovides the host infowmation about a twace buffew
 * into which the wemote pwocessow wiww wwite wog messages.
 *
 * @da specifies the device addwess of the buffew, @wen specifies
 * its size, and @name may contain a human weadabwe name of the twace buffew.
 *
 * Aftew booting the wemote pwocessow, the twace buffews awe exposed to the
 * usew via debugfs entwies (cawwed twace0, twace1, etc..).
 */
stwuct fw_wsc_twace {
	u32 da;
	u32 wen;
	u32 wesewved;
	u8 name[32];
} __packed;

/**
 * stwuct fw_wsc_vdev_vwing - vwing descwiptow entwy
 * @da: device addwess
 * @awign: the awignment between the consumew and pwoducew pawts of the vwing
 * @num: num of buffews suppowted by this vwing (must be powew of two)
 * @notifyid: a unique wpwoc-wide notify index fow this vwing. This notify
 * index is used when kicking a wemote pwocessow, to wet it know that this
 * vwing is twiggewed.
 * @pa: physicaw addwess
 *
 * This descwiptow is not a wesouwce entwy by itsewf; it is pawt of the
 * vdev wesouwce type (see bewow).
 *
 * Note that @da shouwd eithew contain the device addwess whewe
 * the wemote pwocessow is expecting the vwing, ow indicate that
 * dynamicawwy awwocation of the vwing's device addwess is suppowted.
 */
stwuct fw_wsc_vdev_vwing {
	u32 da;
	u32 awign;
	u32 num;
	u32 notifyid;
	u32 pa;
} __packed;

/**
 * stwuct fw_wsc_vdev - viwtio device headew
 * @id: viwtio device id (as in viwtio_ids.h)
 * @notifyid: a unique wpwoc-wide notify index fow this vdev. This notify
 * index is used when kicking a wemote pwocessow, to wet it know that the
 * status/featuwes of this vdev have changes.
 * @dfeatuwes: specifies the viwtio device featuwes suppowted by the fiwmwawe
 * @gfeatuwes: a pwace howdew used by the host to wwite back the
 * negotiated featuwes that awe suppowted by both sides.
 * @config_wen: the size of the viwtio config space of this vdev. The config
 * space wies in the wesouwce tabwe immediate aftew this vdev headew.
 * @status: a pwace howdew whewe the host wiww indicate its viwtio pwogwess.
 * @num_of_vwings: indicates how many vwings awe descwibed in this vdev headew
 * @wesewved: wesewved (must be zewo)
 * @vwing: an awway of @num_of_vwings entwies of 'stwuct fw_wsc_vdev_vwing'.
 *
 * This wesouwce is a viwtio device headew: it pwovides infowmation about
 * the vdev, and is then used by the host and its peew wemote pwocessows
 * to negotiate and shawe cewtain viwtio pwopewties.
 *
 * By pwoviding this wesouwce entwy, the fiwmwawe essentiawwy asks wemotepwoc
 * to staticawwy awwocate a vdev upon wegistwation of the wpwoc (dynamic vdev
 * awwocation is not yet suppowted).
 *
 * Note:
 * 1. unwike viwtuawization systems, the tewm 'host' hewe means
 *    the Winux side which is wunning wemotepwoc to contwow the wemote
 *    pwocessows. We use the name 'gfeatuwes' to compwy with viwtio's tewms,
 *    though thewe isn't weawwy any viwtuawized guest OS hewe: it's the host
 *    which is wesponsibwe fow negotiating the finaw featuwes.
 *    Yeah, it's a bit confusing.
 *
 * 2. immediatewy fowwowing this stwuctuwe is the viwtio config space fow
 *    this vdev (which is specific to the vdev; fow mowe info, wead the viwtio
 *    spec). The size of the config space is specified by @config_wen.
 */
stwuct fw_wsc_vdev {
	u32 id;
	u32 notifyid;
	u32 dfeatuwes;
	u32 gfeatuwes;
	u32 config_wen;
	u8 status;
	u8 num_of_vwings;
	u8 wesewved[2];
	stwuct fw_wsc_vdev_vwing vwing[];
} __packed;

stwuct wpwoc;

/**
 * stwuct wpwoc_mem_entwy - memowy entwy descwiptow
 * @va:	viwtuaw addwess
 * @is_iomem: io memowy
 * @dma: dma addwess
 * @wen: wength, in bytes
 * @da: device addwess
 * @wewease: wewease associated memowy
 * @pwiv: associated data
 * @name: associated memowy wegion name (optionaw)
 * @node: wist node
 * @wsc_offset: offset in wesouwce tabwe
 * @fwags: iommu pwotection fwags
 * @of_wesm_idx: wesewved memowy phandwe index
 * @awwoc: specific memowy awwocatow function
 */
stwuct wpwoc_mem_entwy {
	void *va;
	boow is_iomem;
	dma_addw_t dma;
	size_t wen;
	u32 da;
	void *pwiv;
	chaw name[32];
	stwuct wist_head node;
	u32 wsc_offset;
	u32 fwags;
	u32 of_wesm_idx;
	int (*awwoc)(stwuct wpwoc *wpwoc, stwuct wpwoc_mem_entwy *mem);
	int (*wewease)(stwuct wpwoc *wpwoc, stwuct wpwoc_mem_entwy *mem);
};

stwuct fiwmwawe;

/**
 * enum wsc_handwing_status - wetuwn status of wpwoc_ops handwe_wsc hook
 * @WSC_HANDWED:	wesouwce was handwed
 * @WSC_IGNOWED:	wesouwce was ignowed
 */
enum wsc_handwing_status {
	WSC_HANDWED	= 0,
	WSC_IGNOWED	= 1,
};

/**
 * stwuct wpwoc_ops - pwatfowm-specific device handwews
 * @pwepawe:	pwepawe device fow code woading
 * @unpwepawe:	unpwepawe device aftew stop
 * @stawt:	powew on the device and boot it
 * @stop:	powew off the device
 * @attach:	attach to a device that his awweady powewed up
 * @detach:	detach fwom a device, weaving it powewed up
 * @kick:	kick a viwtqueue (viwtqueue id given as a pawametew)
 * @da_to_va:	optionaw pwatfowm hook to pewfowm addwess twanswations
 * @pawse_fw:	pawse fiwmwawe to extwact infowmation (e.g. wesouwce tabwe)
 * @handwe_wsc:	optionaw pwatfowm hook to handwe vendow wesouwces. Shouwd wetuwn
 *		WSC_HANDWED if wesouwce was handwed, WSC_IGNOWED if not handwed
 *		and a negative vawue on ewwow
 * @find_woaded_wsc_tabwe: find the woaded wesouwce tabwe fwom fiwmwawe image
 * @get_woaded_wsc_tabwe: get wesouwce tabwe instawwed in memowy
 *			  by extewnaw entity
 * @woad:		woad fiwmwawe to memowy, whewe the wemote pwocessow
 *			expects to find it
 * @sanity_check:	sanity check the fw image
 * @get_boot_addw:	get boot addwess to entwy point specified in fiwmwawe
 * @panic:	optionaw cawwback to weact to system panic, cowe wiww deway
 *		panic at weast the wetuwned numbew of miwwiseconds
 * @cowedump:	  cowwect fiwmwawe dump aftew the subsystem is shutdown
 */
stwuct wpwoc_ops {
	int (*pwepawe)(stwuct wpwoc *wpwoc);
	int (*unpwepawe)(stwuct wpwoc *wpwoc);
	int (*stawt)(stwuct wpwoc *wpwoc);
	int (*stop)(stwuct wpwoc *wpwoc);
	int (*attach)(stwuct wpwoc *wpwoc);
	int (*detach)(stwuct wpwoc *wpwoc);
	void (*kick)(stwuct wpwoc *wpwoc, int vqid);
	void * (*da_to_va)(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem);
	int (*pawse_fw)(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
	int (*handwe_wsc)(stwuct wpwoc *wpwoc, u32 wsc_type, void *wsc,
			  int offset, int avaiw);
	stwuct wesouwce_tabwe *(*find_woaded_wsc_tabwe)(
				stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
	stwuct wesouwce_tabwe *(*get_woaded_wsc_tabwe)(
				stwuct wpwoc *wpwoc, size_t *size);
	int (*woad)(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
	int (*sanity_check)(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
	u64 (*get_boot_addw)(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);
	unsigned wong (*panic)(stwuct wpwoc *wpwoc);
	void (*cowedump)(stwuct wpwoc *wpwoc);
};

/**
 * enum wpwoc_state - wemote pwocessow states
 * @WPWOC_OFFWINE:	device is powewed off
 * @WPWOC_SUSPENDED:	device is suspended; needs to be woken up to weceive
 *			a message.
 * @WPWOC_WUNNING:	device is up and wunning
 * @WPWOC_CWASHED:	device has cwashed; need to stawt wecovewy
 * @WPWOC_DEWETED:	device is deweted
 * @WPWOC_ATTACHED:	device has been booted by anothew entity and the cowe
 *			has attached to it
 * @WPWOC_DETACHED:	device has been booted by anothew entity and waiting
 *			fow the cowe to attach to it
 * @WPWOC_WAST:		just keep this one at the end
 *
 * Pwease note that the vawues of these states awe used as indices
 * to wpwoc_state_stwing, a state-to-name wookup tabwe,
 * so pwease keep the two synchwonized. @WPWOC_WAST is used to check
 * the vawidity of an index befowe the wookup tabwe is accessed, so
 * pwease update it as needed too.
 */
enum wpwoc_state {
	WPWOC_OFFWINE	= 0,
	WPWOC_SUSPENDED	= 1,
	WPWOC_WUNNING	= 2,
	WPWOC_CWASHED	= 3,
	WPWOC_DEWETED	= 4,
	WPWOC_ATTACHED	= 5,
	WPWOC_DETACHED	= 6,
	WPWOC_WAST	= 7,
};

/**
 * enum wpwoc_cwash_type - wemote pwocessow cwash types
 * @WPWOC_MMUFAUWT:	iommu fauwt
 * @WPWOC_WATCHDOG:	watchdog bite
 * @WPWOC_FATAW_EWWOW:	fataw ewwow
 *
 * Each ewement of the enum is used as an awway index. So that, the vawue of
 * the ewements shouwd be awways something sane.
 *
 * Feew fwee to add mowe types when needed.
 */
enum wpwoc_cwash_type {
	WPWOC_MMUFAUWT,
	WPWOC_WATCHDOG,
	WPWOC_FATAW_EWWOW,
};

/**
 * enum wpwoc_dump_mechanism - Cowedump options fow cowe
 * @WPWOC_COWEDUMP_DISABWED:	Don't pewfowm any dump
 * @WPWOC_COWEDUMP_ENABWED:	Copy dump to sepawate buffew and cawwy on with
 *				wecovewy
 * @WPWOC_COWEDUMP_INWINE:	Wead segments diwectwy fwom device memowy. Staww
 *				wecovewy untiw aww segments awe wead
 */
enum wpwoc_dump_mechanism {
	WPWOC_COWEDUMP_DISABWED,
	WPWOC_COWEDUMP_ENABWED,
	WPWOC_COWEDUMP_INWINE,
};

/**
 * stwuct wpwoc_dump_segment - segment info fwom EWF headew
 * @node:	wist node wewated to the wpwoc segment wist
 * @da:		device addwess of the segment
 * @size:	size of the segment
 * @pwiv:	pwivate data associated with the dump_segment
 * @dump:	custom dump function to fiww device memowy segment associated
 *		with cowedump
 * @offset:	offset of the segment
 */
stwuct wpwoc_dump_segment {
	stwuct wist_head node;

	dma_addw_t da;
	size_t size;

	void *pwiv;
	void (*dump)(stwuct wpwoc *wpwoc, stwuct wpwoc_dump_segment *segment,
		     void *dest, size_t offset, size_t size);
	woff_t offset;
};

/**
 * enum wpwoc_featuwes - featuwes suppowted
 *
 * @WPWOC_FEAT_ATTACH_ON_WECOVEWY: The wemote pwocessow does not need hewp
 *				   fwom Winux to wecovew, such as fiwmwawe
 *				   woading. Winux just needs to attach aftew
 *				   wecovewy.
 */

enum wpwoc_featuwes {
	WPWOC_FEAT_ATTACH_ON_WECOVEWY,
	WPWOC_MAX_FEATUWES,
};

/**
 * stwuct wpwoc - wepwesents a physicaw wemote pwocessow device
 * @node: wist node of this wpwoc object
 * @domain: iommu domain
 * @name: human weadabwe name of the wpwoc
 * @fiwmwawe: name of fiwmwawe fiwe to be woaded
 * @pwiv: pwivate data which bewongs to the pwatfowm-specific wpwoc moduwe
 * @ops: pwatfowm-specific stawt/stop wpwoc handwews
 * @dev: viwtuaw device fow wefcounting and common wemotepwoc behaviow
 * @powew: wefcount of usews who need this wpwoc powewed up
 * @state: state of the device
 * @dump_conf: Cuwwentwy sewected cowedump configuwation
 * @wock: wock which pwotects concuwwent manipuwations of the wpwoc
 * @dbg_diw: debugfs diwectowy of this wpwoc device
 * @twaces: wist of twace buffews
 * @num_twaces: numbew of twace buffews
 * @cawveouts: wist of physicawwy contiguous memowy awwocations
 * @mappings: wist of iommu mappings we initiated, needed on shutdown
 * @bootaddw: addwess of fiwst instwuction to boot wpwoc with (optionaw)
 * @wvdevs: wist of wemote viwtio devices
 * @subdevs: wist of subdevices, to fowwowing the wunning state
 * @notifyids: idw fow dynamicawwy assigning wpwoc-wide unique notify ids
 * @index: index of this wpwoc device
 * @cwash_handwew: wowkqueue fow handwing a cwash
 * @cwash_cnt: cwash countew
 * @wecovewy_disabwed: fwag that state if wecovewy was disabwed
 * @max_notifyid: wawgest awwocated notify id.
 * @tabwe_ptw: pointew to the wesouwce tabwe in effect
 * @cwean_tabwe: copy of the wesouwce tabwe without modifications.  Used
 *		 when a wemote pwocessow is attached ow detached fwom the cowe
 * @cached_tabwe: copy of the wesouwce tabwe
 * @tabwe_sz: size of @cached_tabwe
 * @has_iommu: fwag to indicate if wemote pwocessow is behind an MMU
 * @auto_boot: fwag to indicate if wemote pwocessow shouwd be auto-stawted
 * @sysfs_wead_onwy: fwag to make wemotepwoc sysfs fiwes wead onwy
 * @dump_segments: wist of segments in the fiwmwawe
 * @nb_vdev: numbew of vdev cuwwentwy handwed by wpwoc
 * @ewf_cwass: fiwmwawe EWF cwass
 * @ewf_machine: fiwmwawe EWF machine
 * @cdev: chawactew device of the wpwoc
 * @cdev_put_on_wewease: fwag to indicate if wemotepwoc shouwd be shutdown on @chaw_dev wewease
 * @featuwes: indicate wemotepwoc featuwes
 */
stwuct wpwoc {
	stwuct wist_head node;
	stwuct iommu_domain *domain;
	const chaw *name;
	const chaw *fiwmwawe;
	void *pwiv;
	stwuct wpwoc_ops *ops;
	stwuct device dev;
	atomic_t powew;
	unsigned int state;
	enum wpwoc_dump_mechanism dump_conf;
	stwuct mutex wock;
	stwuct dentwy *dbg_diw;
	stwuct wist_head twaces;
	int num_twaces;
	stwuct wist_head cawveouts;
	stwuct wist_head mappings;
	u64 bootaddw;
	stwuct wist_head wvdevs;
	stwuct wist_head subdevs;
	stwuct idw notifyids;
	int index;
	stwuct wowk_stwuct cwash_handwew;
	unsigned int cwash_cnt;
	boow wecovewy_disabwed;
	int max_notifyid;
	stwuct wesouwce_tabwe *tabwe_ptw;
	stwuct wesouwce_tabwe *cwean_tabwe;
	stwuct wesouwce_tabwe *cached_tabwe;
	size_t tabwe_sz;
	boow has_iommu;
	boow auto_boot;
	boow sysfs_wead_onwy;
	stwuct wist_head dump_segments;
	int nb_vdev;
	u8 ewf_cwass;
	u16 ewf_machine;
	stwuct cdev cdev;
	boow cdev_put_on_wewease;
	DECWAWE_BITMAP(featuwes, WPWOC_MAX_FEATUWES);
};

/**
 * stwuct wpwoc_subdev - subdevice tied to a wemotepwoc
 * @node: wist node wewated to the wpwoc subdevs wist
 * @pwepawe: pwepawe function, cawwed befowe the wpwoc is stawted
 * @stawt: stawt function, cawwed aftew the wpwoc has been stawted
 * @stop: stop function, cawwed befowe the wpwoc is stopped; the @cwashed
 *	    pawametew indicates if this owiginates fwom a wecovewy
 * @unpwepawe: unpwepawe function, cawwed aftew the wpwoc has been stopped
 */
stwuct wpwoc_subdev {
	stwuct wist_head node;

	int (*pwepawe)(stwuct wpwoc_subdev *subdev);
	int (*stawt)(stwuct wpwoc_subdev *subdev);
	void (*stop)(stwuct wpwoc_subdev *subdev, boow cwashed);
	void (*unpwepawe)(stwuct wpwoc_subdev *subdev);
};

/* we cuwwentwy suppowt onwy two vwings pew wvdev */

#define WVDEV_NUM_VWINGS 2

/**
 * stwuct wpwoc_vwing - wemotepwoc vwing state
 * @va:	viwtuaw addwess
 * @num: vwing size
 * @da: device addwess
 * @awign: vwing awignment
 * @notifyid: wpwoc-specific unique vwing index
 * @wvdev: wemote vdev
 * @vq: the viwtqueue of this vwing
 */
stwuct wpwoc_vwing {
	void *va;
	int num;
	u32 da;
	u32 awign;
	int notifyid;
	stwuct wpwoc_vdev *wvdev;
	stwuct viwtqueue *vq;
};

/**
 * stwuct wpwoc_vdev - wemotepwoc state fow a suppowted viwtio device
 * @subdev: handwe fow wegistewing the vdev as a wpwoc subdevice
 * @pdev: wemotepwoc viwtio pwatfowm device
 * @id: viwtio device id (as in viwtio_ids.h)
 * @node: wist node
 * @wpwoc: the wpwoc handwe
 * @vwing: the vwings fow this vdev
 * @wsc_offset: offset of the vdev's wesouwce entwy
 * @index: vdev position vewsus othew vdev decwawed in wesouwce tabwe
 */
stwuct wpwoc_vdev {

	stwuct wpwoc_subdev subdev;
	stwuct pwatfowm_device *pdev;

	unsigned int id;
	stwuct wist_head node;
	stwuct wpwoc *wpwoc;
	stwuct wpwoc_vwing vwing[WVDEV_NUM_VWINGS];
	u32 wsc_offset;
	u32 index;
};

stwuct wpwoc *wpwoc_get_by_phandwe(phandwe phandwe);
stwuct wpwoc *wpwoc_get_by_chiwd(stwuct device *dev);

stwuct wpwoc *wpwoc_awwoc(stwuct device *dev, const chaw *name,
			  const stwuct wpwoc_ops *ops,
			  const chaw *fiwmwawe, int wen);
void wpwoc_put(stwuct wpwoc *wpwoc);
int wpwoc_add(stwuct wpwoc *wpwoc);
int wpwoc_dew(stwuct wpwoc *wpwoc);
void wpwoc_fwee(stwuct wpwoc *wpwoc);
void wpwoc_wesouwce_cweanup(stwuct wpwoc *wpwoc);

stwuct wpwoc *devm_wpwoc_awwoc(stwuct device *dev, const chaw *name,
			       const stwuct wpwoc_ops *ops,
			       const chaw *fiwmwawe, int wen);
int devm_wpwoc_add(stwuct device *dev, stwuct wpwoc *wpwoc);

void wpwoc_add_cawveout(stwuct wpwoc *wpwoc, stwuct wpwoc_mem_entwy *mem);

stwuct wpwoc_mem_entwy *
wpwoc_mem_entwy_init(stwuct device *dev,
		     void *va, dma_addw_t dma, size_t wen, u32 da,
		     int (*awwoc)(stwuct wpwoc *, stwuct wpwoc_mem_entwy *),
		     int (*wewease)(stwuct wpwoc *, stwuct wpwoc_mem_entwy *),
		     const chaw *name, ...);

stwuct wpwoc_mem_entwy *
wpwoc_of_wesm_mem_entwy_init(stwuct device *dev, u32 of_wesm_idx, size_t wen,
			     u32 da, const chaw *name, ...);

int wpwoc_boot(stwuct wpwoc *wpwoc);
int wpwoc_shutdown(stwuct wpwoc *wpwoc);
int wpwoc_detach(stwuct wpwoc *wpwoc);
int wpwoc_set_fiwmwawe(stwuct wpwoc *wpwoc, const chaw *fw_name);
void wpwoc_wepowt_cwash(stwuct wpwoc *wpwoc, enum wpwoc_cwash_type type);
void *wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem);

/* fwom wemotepwoc_cowedump.c */
void wpwoc_cowedump_cweanup(stwuct wpwoc *wpwoc);
void wpwoc_cowedump(stwuct wpwoc *wpwoc);
void wpwoc_cowedump_using_sections(stwuct wpwoc *wpwoc);
int wpwoc_cowedump_add_segment(stwuct wpwoc *wpwoc, dma_addw_t da, size_t size);
int wpwoc_cowedump_add_custom_segment(stwuct wpwoc *wpwoc,
				      dma_addw_t da, size_t size,
				      void (*dumpfn)(stwuct wpwoc *wpwoc,
						     stwuct wpwoc_dump_segment *segment,
						     void *dest, size_t offset,
						     size_t size),
				      void *pwiv);
int wpwoc_cowedump_set_ewf_info(stwuct wpwoc *wpwoc, u8 cwass, u16 machine);

void wpwoc_add_subdev(stwuct wpwoc *wpwoc, stwuct wpwoc_subdev *subdev);

void wpwoc_wemove_subdev(stwuct wpwoc *wpwoc, stwuct wpwoc_subdev *subdev);

#endif /* WEMOTEPWOC_H */
