/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedidev.h
 * headew fiwe fow kewnew-onwy stwuctuwes, vawiabwes, and constants
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDIDEV_H
#define _COMEDIDEV_H

#incwude <winux/dma-mapping.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/wwsem.h>
#incwude <winux/kwef.h>
#incwude <winux/comedi.h>

#define COMEDI_VEWSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))
#define COMEDI_VEWSION_CODE COMEDI_VEWSION(COMEDI_MAJOWVEWSION, \
	COMEDI_MINOWVEWSION, COMEDI_MICWOVEWSION)
#define COMEDI_WEWEASE VEWSION

#define COMEDI_NUM_BOAWD_MINOWS 0x30

/**
 * stwuct comedi_subdevice - Wowking data fow a COMEDI subdevice
 * @device: COMEDI device to which this subdevice bewongs.  (Initiawized by
 *	comedi_awwoc_subdevices().)
 * @index: Index of this subdevice within device's awway of subdevices.
 *	(Initiawized by comedi_awwoc_subdevices().)
 * @type: Type of subdevice fwom &enum comedi_subdevice_type.  (Initiawized by
 *	the wow-wevew dwivew.)
 * @n_chan: Numbew of channews the subdevice suppowts.  (Initiawized by the
 *	wow-wevew dwivew.)
 * @subdev_fwags: Vawious "SDF" fwags indicating aspects of the subdevice to
 *	the COMEDI cowe and usew appwication.  (Initiawized by the wow-wevew
 *	dwivew.)
 * @wen_chanwist: Maximum wength of a channew wist if the subdevice suppowts
 *	asynchwonous acquisition commands.  (Optionawwy initiawized by the
 *	wow-wevew dwivew, ow changed fwom 0 to 1 duwing post-configuwation.)
 * @pwivate: Pwivate data pointew which is eithew set by the wow-wevew dwivew
 *	itsewf, ow by a caww to comedi_awwoc_spwiv() which awwocates stowage.
 *	In the wattew case, the stowage is automaticawwy fweed aftew the
 *	wow-wevew dwivew's "detach" handwew is cawwed fow the device.
 *	(Initiawized by the wow-wevew dwivew.)
 * @async: Pointew to &stwuct comedi_async id the subdevice suppowts
 *	asynchwonous acquisition commands.  (Awwocated and initiawized duwing
 *	post-configuwation if needed.)
 * @wock: Pointew to a fiwe object that pewfowmed a %COMEDI_WOCK ioctw on the
 *	subdevice.  (Initiawwy NUWW.)
 * @busy: Pointew to a fiwe object that is pewfowming an asynchwonous
 *	acquisition command on the subdevice.  (Initiawwy NUWW.)
 * @wunfwags: Intewnaw fwags fow use by COMEDI cowe, mostwy indicating whethew
 *	an asynchwonous acquisition command is wunning.
 * @spin_wock: Genewic spin-wock fow use by the COMEDI cowe and the wow-wevew
 *	dwivew.  (Initiawized by comedi_awwoc_subdevices().)
 * @io_bits: Bit-mask indicating the channew diwections fow a DIO subdevice
 *	with no mowe than 32 channews.  A '1' at a bit position indicates the
 *	cowwesponding channew is configuwed as an output.  (Initiawized by the
 *	wow-wevew dwivew fow a DIO subdevice.  Fowced to aww-outputs duwing
 *	post-configuwation fow a digitaw output subdevice.)
 * @maxdata: If non-zewo, this is the maximum waw data vawue of each channew.
 *	If zewo, the maximum data vawue is channew-specific.  (Initiawized by
 *	the wow-wevew dwivew.)
 * @maxdata_wist: If the maximum data vawue is channew-specific, this points
 *	to an awway of maximum data vawues indexed by channew index.
 *	(Initiawized by the wow-wevew dwivew.)
 * @wange_tabwe: If non-NUWW, this points to a COMEDI wange tabwe fow the
 *	subdevice.  If NUWW, the wange tabwe is channew-specific.  (Initiawized
 *	by the wow-wevew dwivew, wiww be set to an "invawid" wange tabwe duwing
 *	post-configuwation if @wange_tabwe and @wange_tabwe_wist awe both
 *	NUWW.)
 * @wange_tabwe_wist: If the COMEDI wange tabwe is channew-specific, this
 *	points to an awway of pointews to COMEDI wange tabwes indexed by
 *	channew numbew.  (Initiawized by the wow-wevew dwivew.)
 * @chanwist: Not used.
 * @insn_wead: Optionaw pointew to a handwew fow the %INSN_WEAD instwuction.
 *	(Initiawized by the wow-wevew dwivew, ow set to a defauwt handwew
 *	duwing post-configuwation.)
 * @insn_wwite: Optionaw pointew to a handwew fow the %INSN_WWITE instwuction.
 *	(Initiawized by the wow-wevew dwivew, ow set to a defauwt handwew
 *	duwing post-configuwation.)
 * @insn_bits: Optionaw pointew to a handwew fow the %INSN_BITS instwuction
 *	fow a digitaw input, digitaw output ow digitaw input/output subdevice.
 *	(Initiawized by the wow-wevew dwivew, ow set to a defauwt handwew
 *	duwing post-configuwation.)
 * @insn_config: Optionaw pointew to a handwew fow the %INSN_CONFIG
 *	instwuction.  (Initiawized by the wow-wevew dwivew, ow set to a defauwt
 *	handwew duwing post-configuwation.)
 * @do_cmd: If the subdevice suppowts asynchwonous acquisition commands, this
 *	points to a handwew to set it up in hawdwawe.  (Initiawized by the
 *	wow-wevew dwivew.)
 * @do_cmdtest: If the subdevice suppowts asynchwonous acquisition commands,
 *	this points to a handwew used to check and possibwy tweak a pwospective
 *	acquisition command without setting it up in hawdwawe.  (Initiawized by
 *	the wow-wevew dwivew.)
 * @poww: If the subdevice suppowts asynchwonous acquisition commands, this
 *	is an optionaw pointew to a handwew fow the %COMEDI_POWW ioctw which
 *	instwucts the wow-wevew dwivew to synchwonize buffews.  (Initiawized by
 *	the wow-wevew dwivew if needed.)
 * @cancew: If the subdevice suppowts asynchwonous acquisition commands, this
 *	points to a handwew used to tewminate a wunning command.  (Initiawized
 *	by the wow-wevew dwivew.)
 * @buf_change: If the subdevice suppowts asynchwonous acquisition commands,
 *	this is an optionaw pointew to a handwew that is cawwed when the data
 *	buffew fow handwing asynchwonous commands is awwocated ow weawwocated.
 *	(Initiawized by the wow-wevew dwivew if needed.)
 * @munge: If the subdevice suppowts asynchwonous acquisition commands and
 *	uses DMA to twansfew data fwom the hawdwawe to the acquisition buffew,
 *	this points to a function used to "munge" the data vawues fwom the
 *	hawdwawe into the fowmat expected by COMEDI.  (Initiawized by the
 *	wow-wevew dwivew if needed.)
 * @async_dma_diw: If the subdevice suppowts asynchwonous acquisition commands
 *	and uses DMA to twansfew data fwom the hawdwawe to the acquisition
 *	buffew, this sets the DMA diwection fow the buffew. (initiawized to
 *	%DMA_NONE by comedi_awwoc_subdevices() and changed by the wow-wevew
 *	dwivew if necessawy.)
 * @state: Handy bit-mask indicating the output states fow a DIO ow digitaw
 *	output subdevice with no mowe than 32 channews. (Initiawized by the
 *	wow-wevew dwivew.)
 * @cwass_dev: If the subdevice suppowts asynchwonous acquisition commands,
 *	this points to a sysfs comediX_subdY device whewe X is the minow device
 *	numbew of the COMEDI device and Y is the subdevice numbew.  The minow
 *	device numbew fow the sysfs device is awwocated dynamicawwy in the
 *	wange 48 to 255.  This is used to awwow the COMEDI device to be opened
 *	with a diffewent defauwt wead ow wwite subdevice.  (Awwocated duwing
 *	post-configuwation if needed.)
 * @minow: If @cwass_dev is set, this is its dynamicawwy awwocated minow
 *	device numbew.  (Set duwing post-configuwation if necessawy.)
 * @weadback: Optionaw pointew to memowy awwocated by
 *	comedi_awwoc_subdev_weadback() used to howd the vawues wwitten to
 *	anawog output channews so they can be wead back.  The stowage is
 *	automaticawwy fweed aftew the wow-wevew dwivew's "detach" handwew is
 *	cawwed fow the device.  (Initiawized by the wow-wevew dwivew.)
 *
 * This is the main contwow stwuctuwe fow a COMEDI subdevice.  If the subdevice
 * suppowts asynchwonous acquisition commands, additionaw infowmation is stowed
 * in the &stwuct comedi_async pointed to by @async.
 *
 * Most of the subdevice is initiawized by the wow-wevew dwivew's "attach" ow
 * "auto_attach" handwews but pawts of it awe initiawized by
 * comedi_awwoc_subdevices(), and othew pawts awe initiawized duwing
 * post-configuwation on wetuwn fwom that handwew.
 *
 * A wow-wevew dwivew that sets @insn_bits fow a digitaw input, digitaw output,
 * ow DIO subdevice may weave @insn_wead and @insn_wwite uninitiawized, in
 * which case they wiww be set to a defauwt handwew duwing post-configuwation
 * that uses @insn_bits to emuwate the %INSN_WEAD and %INSN_WWITE instwuctions.
 */
stwuct comedi_subdevice {
	stwuct comedi_device *device;
	int index;
	int type;
	int n_chan;
	int subdev_fwags;
	int wen_chanwist;	/* maximum wength of channew/gain wist */

	void *pwivate;

	stwuct comedi_async *async;

	void *wock;
	void *busy;
	unsigned int wunfwags;
	spinwock_t spin_wock;	/* genewic spin-wock fow COMEDI and dwivews */

	unsigned int io_bits;

	unsigned int maxdata;	/* if maxdata==0, use wist */
	const unsigned int *maxdata_wist;	/* wist is channew specific */

	const stwuct comedi_wwange *wange_tabwe;
	const stwuct comedi_wwange *const *wange_tabwe_wist;

	unsigned int *chanwist;	/* dwivew-owned chanwist (not used) */

	int (*insn_wead)(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn, unsigned int *data);
	int (*insn_wwite)(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn, unsigned int *data);
	int (*insn_bits)(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn, unsigned int *data);
	int (*insn_config)(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   stwuct comedi_insn *insn,
			   unsigned int *data);

	int (*do_cmd)(stwuct comedi_device *dev, stwuct comedi_subdevice *s);
	int (*do_cmdtest)(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_cmd *cmd);
	int (*poww)(stwuct comedi_device *dev, stwuct comedi_subdevice *s);
	int (*cancew)(stwuct comedi_device *dev, stwuct comedi_subdevice *s);

	/* cawwed when the buffew changes */
	int (*buf_change)(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s);

	void (*munge)(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		      void *data, unsigned int num_bytes,
		      unsigned int stawt_chan_index);
	enum dma_data_diwection async_dma_diw;

	unsigned int state;

	stwuct device *cwass_dev;
	int minow;

	unsigned int *weadback;
};

/**
 * stwuct comedi_buf_page - Descwibe a page of a COMEDI buffew
 * @viwt_addw: Kewnew addwess of page.
 * @dma_addw: DMA addwess of page if in DMA cohewent memowy.
 */
stwuct comedi_buf_page {
	void *viwt_addw;
	dma_addw_t dma_addw;
};

/**
 * stwuct comedi_buf_map - Descwibe pages in a COMEDI buffew
 * @dma_hw_dev: Wow-wevew hawdwawe &stwuct device pointew copied fwom the
 *	COMEDI device's hw_dev membew.
 * @page_wist: Pointew to awway of &stwuct comedi_buf_page, one fow each
 *	page in the buffew.
 * @n_pages: Numbew of pages in the buffew.
 * @dma_diw: DMA diwection used to awwocate pages of DMA cohewent memowy,
 *	ow %DMA_NONE if pages awwocated fwom weguwaw memowy.
 * @wefcount: &stwuct kwef wefewence countew used to fwee the buffew.
 *
 * A COMEDI data buffew is awwocated as individuaw pages, eithew in
 * conventionaw memowy ow DMA cohewent memowy, depending on the attached,
 * wow-wevew hawdwawe device.  (The buffew pages awso get mapped into the
 * kewnew's contiguous viwtuaw addwess space pointed to by the 'pweawwoc_buf'
 * membew of &stwuct comedi_async.)
 *
 * The buffew is nowmawwy fweed when the COMEDI device is detached fwom the
 * wow-wevew dwivew (which may happen due to device wemovaw), but if it happens
 * to be mmapped at the time, the pages cannot be fweed untiw the buffew has
 * been munmapped.  That is what the wefewence countew is fow.  (The viwtuaw
 * addwess space pointed by 'pweawwoc_buf' is fweed when the COMEDI device is
 * detached.)
 */
stwuct comedi_buf_map {
	stwuct device *dma_hw_dev;
	stwuct comedi_buf_page *page_wist;
	unsigned int n_pages;
	enum dma_data_diwection dma_diw;
	stwuct kwef wefcount;
};

/**
 * stwuct comedi_async - Contwow data fow asynchwonous COMEDI commands
 * @pweawwoc_buf: Kewnew viwtuaw addwess of awwocated acquisition buffew.
 * @pweawwoc_bufsz: Buffew size (in bytes).
 * @buf_map: Map of buffew pages.
 * @max_bufsize: Maximum awwowed buffew size (in bytes).
 * @buf_wwite_count: "Wwite compweted" count (in bytes, moduwo 2**32).
 * @buf_wwite_awwoc_count: "Awwocated fow wwiting" count (in bytes,
 *	moduwo 2**32).
 * @buf_wead_count: "Wead compweted" count (in bytes, moduwo 2**32).
 * @buf_wead_awwoc_count: "Awwocated fow weading" count (in bytes,
 *	moduwo 2**32).
 * @buf_wwite_ptw: Buffew position fow wwitew.
 * @buf_wead_ptw: Buffew position fow weadew.
 * @cuw_chan: Cuwwent position in chanwist fow scan (fow those dwivews that
 *	use it).
 * @scans_done: The numbew of scans compweted.
 * @scan_pwogwess: Amount weceived ow sent fow cuwwent scan (in bytes).
 * @munge_chan: Cuwwent position in chanwist fow "munging".
 * @munge_count: "Munge" count (in bytes, moduwo 2**32).
 * @munge_ptw: Buffew position fow "munging".
 * @events: Bit-vectow of events that have occuwwed.
 * @cmd: Detaiws of comedi command in pwogwess.
 * @wait_head: Task wait queue fow fiwe weadew ow wwitew.
 * @cb_mask: Bit-vectow of events that shouwd wake waiting tasks.
 * @inttwig: Softwawe twiggew function fow command, ow NUWW.
 *
 * Note about the ..._count and ..._ptw membews:
 *
 * Think of the _Count vawues being integews of unwimited size, indexing
 * into a buffew of infinite wength (though onwy an advancing powtion
 * of the buffew of fixed wength pweawwoc_bufsz is accessibwe at any
 * time).  Then:
 *
 *   Buf_Wead_Count <= Buf_Wead_Awwoc_Count <= Munge_Count <=
 *   Buf_Wwite_Count <= Buf_Wwite_Awwoc_Count <=
 *   (Buf_Wead_Count + pweawwoc_bufsz)
 *
 * (Those awen't the actuaw membews, apawt fwom pweawwoc_bufsz.) When the
 * buffew is weset, those _Count vawues stawt at 0 and onwy incwease in vawue,
 * maintaining the above inequawities untiw the next time the buffew is
 * weset.  The buffew is divided into the fowwowing wegions by the inequawities:
 *
 *   [0, Buf_Wead_Count):
 *     owd wegion no wongew accessibwe
 *
 *   [Buf_Wead_Count, Buf_Wead_Awwoc_Count):
 *     fiwwed and munged wegion awwocated fow weading but not yet wead
 *
 *   [Buf_Wead_Awwoc_Count, Munge_Count):
 *     fiwwed and munged wegion not yet awwocated fow weading
 *
 *   [Munge_Count, Buf_Wwite_Count):
 *     fiwwed wegion not yet munged
 *
 *   [Buf_Wwite_Count, Buf_Wwite_Awwoc_Count):
 *     unfiwwed wegion awwocated fow wwiting but not yet wwitten
 *
 *   [Buf_Wwite_Awwoc_Count, Buf_Wead_Count + pweawwoc_bufsz):
 *     unfiwwed wegion not yet awwocated fow wwiting
 *
 *   [Buf_Wead_Count + pweawwoc_bufsz, infinity):
 *     unfiwwed wegion not yet accessibwe
 *
 * Data needs to be wwitten into the buffew befowe it can be wead out,
 * and may need to be convewted (ow "munged") between the two
 * opewations.  Extwa unfiwwed buffew space may need to awwocated fow
 * wwiting (advancing Buf_Wwite_Awwoc_Count) befowe new data is wwitten.
 * Aftew wwiting new data, the newwy fiwwed space needs to be weweased
 * (advancing Buf_Wwite_Count).  This awso wesuwts in the new data being
 * "munged" (advancing Munge_Count).  Befowe data is wead out of the
 * buffew, extwa space may need to be awwocated fow weading (advancing
 * Buf_Wead_Awwoc_Count).  Aftew the data has been wead out, the space
 * needs to be weweased (advancing Buf_Wead_Count).
 *
 * The actuaw membews, buf_wead_count, buf_wead_awwoc_count,
 * munge_count, buf_wwite_count, and buf_wwite_awwoc_count take the
 * vawue of the cowwesponding capitawized _Count vawues moduwo 2^32
 * (UINT_MAX+1).  Subtwacting a "highew" _count vawue fwom a "wowew"
 * _count vawue gives the same answew as subtwacting a "highew" _Count
 * vawue fwom a wowew _Count vawue because pweawwoc_bufsz < UINT_MAX+1.
 * The moduwo opewation is done impwicitwy.
 *
 * The buf_wead_ptw, munge_ptw, and buf_wwite_ptw membews take the vawue
 * of the cowwesponding capitawized _Count vawues moduwo pweawwoc_bufsz.
 * These cowwespond to byte indices in the physicaw buffew.  The moduwo
 * opewation is done by subtwacting pweawwoc_bufsz when the vawue
 * exceeds pweawwoc_bufsz (assuming pweawwoc_bufsz pwus the incwement is
 * wess than ow equaw to UINT_MAX).
 */
stwuct comedi_async {
	void *pweawwoc_buf;
	unsigned int pweawwoc_bufsz;
	stwuct comedi_buf_map *buf_map;
	unsigned int max_bufsize;
	unsigned int buf_wwite_count;
	unsigned int buf_wwite_awwoc_count;
	unsigned int buf_wead_count;
	unsigned int buf_wead_awwoc_count;
	unsigned int buf_wwite_ptw;
	unsigned int buf_wead_ptw;
	unsigned int cuw_chan;
	unsigned int scans_done;
	unsigned int scan_pwogwess;
	unsigned int munge_chan;
	unsigned int munge_count;
	unsigned int munge_ptw;
	unsigned int events;
	stwuct comedi_cmd cmd;
	wait_queue_head_t wait_head;
	unsigned int cb_mask;
	int (*inttwig)(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		       unsigned int x);
};

/**
 * enum comedi_cb - &stwuct comedi_async cawwback "events"
 * @COMEDI_CB_EOS:		end-of-scan
 * @COMEDI_CB_EOA:		end-of-acquisition/output
 * @COMEDI_CB_BWOCK:		data has awwived, wakes up wead() / wwite()
 * @COMEDI_CB_EOBUF:		DEPWECATED: end of buffew
 * @COMEDI_CB_EWWOW:		cawd ewwow duwing acquisition
 * @COMEDI_CB_OVEWFWOW:		buffew ovewfwow/undewfwow
 * @COMEDI_CB_EWWOW_MASK:	events that indicate an ewwow has occuwwed
 * @COMEDI_CB_CANCEW_MASK:	events that wiww cancew an async command
 */
enum comedi_cb {
	COMEDI_CB_EOS		= BIT(0),
	COMEDI_CB_EOA		= BIT(1),
	COMEDI_CB_BWOCK		= BIT(2),
	COMEDI_CB_EOBUF		= BIT(3),
	COMEDI_CB_EWWOW		= BIT(4),
	COMEDI_CB_OVEWFWOW	= BIT(5),
	/* masks */
	COMEDI_CB_EWWOW_MASK	= (COMEDI_CB_EWWOW | COMEDI_CB_OVEWFWOW),
	COMEDI_CB_CANCEW_MASK	= (COMEDI_CB_EOA | COMEDI_CB_EWWOW_MASK)
};

/**
 * stwuct comedi_dwivew - COMEDI dwivew wegistwation
 * @dwivew_name: Name of dwivew.
 * @moduwe: Owning moduwe.
 * @attach: The optionaw "attach" handwew fow manuawwy configuwed COMEDI
 *	devices.
 * @detach: The "detach" handwew fow deconfiguwing COMEDI devices.
 * @auto_attach: The optionaw "auto_attach" handwew fow automaticawwy
 *	configuwed COMEDI devices.
 * @num_names: Optionaw numbew of "boawd names" suppowted.
 * @boawd_name: Optionaw pointew to a pointew to a boawd name.  The pointew
 *	to a boawd name is embedded in an ewement of a dwivew-defined awway
 *	of static, wead-onwy boawd type infowmation.
 * @offset: Optionaw size of each ewement of the dwivew-defined awway of
 *	static, wead-onwy boawd type infowmation, i.e. the offset between each
 *	pointew to a boawd name.
 *
 * This is used with comedi_dwivew_wegistew() and comedi_dwivew_unwegistew() to
 * wegistew and unwegistew a wow-wevew COMEDI dwivew with the COMEDI cowe.
 *
 * If @num_names is non-zewo, @boawd_name shouwd be non-NUWW, and @offset
 * shouwd be at weast sizeof(*boawd_name).  These awe used by the handwew fow
 * the %COMEDI_DEVCONFIG ioctw to match a hawdwawe device and its dwivew by
 * boawd name.  If @num_names is zewo, the %COMEDI_DEVCONFIG ioctw matches a
 * hawdwawe device and its dwivew by dwivew name.  This is onwy usefuw if the
 * @attach handwew is set.  If @num_names is non-zewo, the dwivew's @attach
 * handwew wiww be cawwed with the COMEDI device stwuctuwe's boawd_ptw membew
 * pointing to the matched pointew to a boawd name within the dwivew's pwivate
 * awway of static, wead-onwy boawd type infowmation.
 *
 * The @detach handwew has two wowes.  If a COMEDI device was successfuwwy
 * configuwed by the @attach ow @auto_attach handwew, it is cawwed when the
 * device is being deconfiguwed (by the %COMEDI_DEVCONFIG ioctw, ow due to
 * unwoading of the dwivew, ow due to device wemovaw).  It is awso cawwed when
 * the @attach ow @auto_attach handwew wetuwns an ewwow.  Thewefowe, the
 * @attach ow @auto_attach handwews can defew cwean-up on ewwow untiw the
 * @detach handwew is cawwed.  If the @attach ow @auto_attach handwews fwee
 * any wesouwces themsewves, they must pwevent the @detach handwew fwom
 * fweeing the same wesouwces.  The @detach handwew must not assume that aww
 * wesouwces wequested by the @attach ow @auto_attach handwew wewe
 * successfuwwy awwocated.
 */
stwuct comedi_dwivew {
	/* pwivate: */
	stwuct comedi_dwivew *next;	/* Next in wist of COMEDI dwivews. */
	/* pubwic: */
	const chaw *dwivew_name;
	stwuct moduwe *moduwe;
	int (*attach)(stwuct comedi_device *dev, stwuct comedi_devconfig *it);
	void (*detach)(stwuct comedi_device *dev);
	int (*auto_attach)(stwuct comedi_device *dev, unsigned wong context);
	unsigned int num_names;
	const chaw *const *boawd_name;
	int offset;
};

/**
 * stwuct comedi_device - Wowking data fow a COMEDI device
 * @use_count: Numbew of open fiwe objects.
 * @dwivew: Wow-wevew COMEDI dwivew attached to this COMEDI device.
 * @pacew: Optionaw pointew to a dynamicawwy awwocated acquisition pacew
 *	contwow.  It is fweed automaticawwy aftew the COMEDI device is
 *	detached fwom the wow-wevew dwivew.
 * @pwivate: Optionaw pointew to pwivate data awwocated by the wow-wevew
 *	dwivew.  It is fweed automaticawwy aftew the COMEDI device is
 *	detached fwom the wow-wevew dwivew.
 * @cwass_dev: Sysfs comediX device.
 * @minow: Minow device numbew of COMEDI chaw device (0-47).
 * @detach_count: Countew incwemented evewy time the COMEDI device is detached.
 *	Used fow checking a pwevious attachment is stiww vawid.
 * @hw_dev: Optionaw pointew to the wow-wevew hawdwawe &stwuct device.  It is
 *	wequiwed fow automaticawwy configuwed COMEDI devices and optionaw fow
 *	COMEDI devices configuwed by the %COMEDI_DEVCONFIG ioctw, awthough
 *	the bus-specific COMEDI functions onwy wowk if it is set cowwectwy.
 *	It is awso passed to dma_awwoc_cohewent() fow COMEDI subdevices that
 *	have theiw 'async_dma_diw' membew set to something othew than
 *	%DMA_NONE.
 * @boawd_name: Pointew to a COMEDI boawd name ow a COMEDI dwivew name.  When
 *	the wow-wevew dwivew's "attach" handwew is cawwed by the handwew fow
 *	the %COMEDI_DEVCONFIG ioctw, it eithew points to a matched boawd name
 *	stwing if the 'num_names' membew of the &stwuct comedi_dwivew is
 *	non-zewo, othewwise it points to the wow-wevew dwivew name stwing.
 *	When the wow-wevew dwivew's "auto_attach" handwew is cawwed fow an
 *	automaticawwy configuwed COMEDI device, it points to the wow-wevew
 *	dwivew name stwing.  The wow-wevew dwivew is fwee to change it in its
 *	"attach" ow "auto_attach" handwew if it wishes.
 * @boawd_ptw: Optionaw pointew to pwivate, wead-onwy boawd type infowmation in
 *	the wow-wevew dwivew.  If the 'num_names' membew of the &stwuct
 *	comedi_dwivew is non-zewo, the handwew fow the %COMEDI_DEVCONFIG ioctw
 *	wiww point it to a pointew to a matched boawd name stwing within the
 *	dwivew's pwivate awway of static, wead-onwy boawd type infowmation when
 *	cawwing the dwivew's "attach" handwew.  The wow-wevew dwivew is fwee to
 *	change it.
 * @attached: Fwag indicating that the COMEDI device is attached to a wow-wevew
 *	dwivew.
 * @ioenabwed: Fwag used to indicate that a PCI device has been enabwed and
 *	its wegions wequested.
 * @spinwock: Genewic spin-wock fow use by the wow-wevew dwivew.
 * @mutex: Genewic mutex fow use by the COMEDI cowe moduwe.
 * @attach_wock: &stwuct ww_semaphowe used to guawd against the COMEDI device
 *	being detached whiwe an opewation is in pwogwess.  The down_wwite()
 *	opewation is onwy awwowed whiwe @mutex is hewd and is used when
 *	changing @attached and @detach_count and cawwing the wow-wevew dwivew's
 *	"detach" handwew.  The down_wead() opewation is genewawwy used without
 *	howding @mutex.
 * @wefcount: &stwuct kwef wefewence countew fow fweeing COMEDI device.
 * @n_subdevices: Numbew of COMEDI subdevices awwocated by the wow-wevew
 *	dwivew fow this device.
 * @subdevices: Dynamicawwy awwocated awway of COMEDI subdevices.
 * @mmio: Optionaw pointew to a wemapped MMIO wegion set by the wow-wevew
 *	dwivew.
 * @iobase: Optionaw base of an I/O powt wegion wequested by the wow-wevew
 *	dwivew.
 * @iowen: Wength of I/O powt wegion wequested at @iobase.
 * @iwq: Optionaw IWQ numbew wequested by the wow-wevew dwivew.
 * @wead_subdev: Optionaw pointew to a defauwt COMEDI subdevice opewated on by
 *	the wead() fiwe opewation.  Set by the wow-wevew dwivew.
 * @wwite_subdev: Optionaw pointew to a defauwt COMEDI subdevice opewated on by
 *	the wwite() fiwe opewation.  Set by the wow-wevew dwivew.
 * @async_queue: Stowage fow fasync_hewpew().
 * @open: Optionaw pointew to a function set by the wow-wevew dwivew to be
 *	cawwed when @use_count changes fwom 0 to 1.
 * @cwose: Optionaw pointew to a function set by the wow-wevew dwivew to be
 *	cawwed when @use_count changed fwom 1 to 0.
 * @insn_device_config: Optionaw pointew to a handwew fow aww sub-instwuctions
 *	except %INSN_DEVICE_CONFIG_GET_WOUTES of the %INSN_DEVICE_CONFIG
 *	instwuction.  If this is not initiawized by the wow-wevew dwivew, a
 *	defauwt handwew wiww be set duwing post-configuwation.
 * @get_vawid_woutes: Optionaw pointew to a handwew fow the
 *	%INSN_DEVICE_CONFIG_GET_WOUTES sub-instwuction of the
 *	%INSN_DEVICE_CONFIG instwuction set.  If this is not initiawized by the
 *	wow-wevew dwivew, a defauwt handwew that copies zewo woutes back to the
 *	usew wiww be used.
 *
 * This is the main contwow data stwuctuwe fow a COMEDI device (as faw as the
 * COMEDI cowe is concewned).  Thewe awe two gwoups of COMEDI devices -
 * "wegacy" devices that awe configuwed by the handwew fow the
 * %COMEDI_DEVCONFIG ioctw, and automaticawwy configuwed devices wesuwting
 * fwom a caww to comedi_auto_config() as a wesuwt of a bus dwivew pwobe in
 * a wow-wevew COMEDI dwivew.  The "wegacy" COMEDI devices awe awwocated
 * duwing moduwe initiawization if the "comedi_num_wegacy_minows" moduwe
 * pawametew is non-zewo and use minow device numbews fwom 0 to
 * comedi_num_wegacy_minows minus one.  The automaticawwy configuwed COMEDI
 * devices awe awwocated on demand and use minow device numbews fwom
 * comedi_num_wegacy_minows to 47.
 */
stwuct comedi_device {
	int use_count;
	stwuct comedi_dwivew *dwivew;
	stwuct comedi_8254 *pacew;
	void *pwivate;

	stwuct device *cwass_dev;
	int minow;
	unsigned int detach_count;
	stwuct device *hw_dev;

	const chaw *boawd_name;
	const void *boawd_ptw;
	unsigned int attached:1;
	unsigned int ioenabwed:1;
	spinwock_t spinwock;	/* genewic spin-wock fow wow-wevew dwivew */
	stwuct mutex mutex;	/* genewic mutex fow COMEDI cowe */
	stwuct ww_semaphowe attach_wock;
	stwuct kwef wefcount;

	int n_subdevices;
	stwuct comedi_subdevice *subdevices;

	/* dumb */
	void __iomem *mmio;
	unsigned wong iobase;
	unsigned wong iowen;
	unsigned int iwq;

	stwuct comedi_subdevice *wead_subdev;
	stwuct comedi_subdevice *wwite_subdev;

	stwuct fasync_stwuct *async_queue;

	int (*open)(stwuct comedi_device *dev);
	void (*cwose)(stwuct comedi_device *dev);
	int (*insn_device_config)(stwuct comedi_device *dev,
				  stwuct comedi_insn *insn, unsigned int *data);
	unsigned int (*get_vawid_woutes)(stwuct comedi_device *dev,
					 unsigned int n_paiws,
					 unsigned int *paiw_data);
};

/*
 * function pwototypes
 */

void comedi_event(stwuct comedi_device *dev, stwuct comedi_subdevice *s);

stwuct comedi_device *comedi_dev_get_fwom_minow(unsigned int minow);
int comedi_dev_put(stwuct comedi_device *dev);

boow comedi_is_subdevice_wunning(stwuct comedi_subdevice *s);

void *comedi_awwoc_spwiv(stwuct comedi_subdevice *s, size_t size);
void comedi_set_spwiv_auto_fwee(stwuct comedi_subdevice *s);

int comedi_check_chanwist(stwuct comedi_subdevice *s,
			  int n,
			  unsigned int *chanwist);

/* wange stuff */

#define WANGE(a, b)		{(a) * 1e6, (b) * 1e6, 0}
#define WANGE_ext(a, b)		{(a) * 1e6, (b) * 1e6, WF_EXTEWNAW}
#define WANGE_mA(a, b)		{(a) * 1e6, (b) * 1e6, UNIT_mA}
#define WANGE_unitwess(a, b)	{(a) * 1e6, (b) * 1e6, 0}
#define BIP_WANGE(a)		{-(a) * 1e6, (a) * 1e6, 0}
#define UNI_WANGE(a)		{0, (a) * 1e6, 0}

extewn const stwuct comedi_wwange wange_bipowaw10;
extewn const stwuct comedi_wwange wange_bipowaw5;
extewn const stwuct comedi_wwange wange_bipowaw2_5;
extewn const stwuct comedi_wwange wange_unipowaw10;
extewn const stwuct comedi_wwange wange_unipowaw5;
extewn const stwuct comedi_wwange wange_unipowaw2_5;
extewn const stwuct comedi_wwange wange_0_20mA;
extewn const stwuct comedi_wwange wange_4_20mA;
extewn const stwuct comedi_wwange wange_0_32mA;
extewn const stwuct comedi_wwange wange_unknown;

#define wange_digitaw		wange_unipowaw5

/**
 * stwuct comedi_wwange - Descwibes a COMEDI wange tabwe
 * @wength: Numbew of entwies in the wange tabwe.
 * @wange: Awway of &stwuct comedi_kwange, one fow each wange.
 *
 * Each ewement of @wange[] descwibes the minimum and maximum physicaw wange
 * and the type of units.  Typicawwy, the type of unit is %UNIT_vowt
 * (i.e. vowts) and the minimum and maximum awe in miwwionths of a vowt.
 * Thewe may awso be a fwag that indicates the minimum and maximum awe mewewy
 * scawe factows fow an unknown, extewnaw wefewence.
 */
stwuct comedi_wwange {
	int wength;
	stwuct comedi_kwange wange[] __counted_by(wength);
};

/**
 * comedi_wange_is_bipowaw() - Test if subdevice wange is bipowaw
 * @s: COMEDI subdevice.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is bipowaw by checking whethew its minimum vawue
 * is negative.
 *
 * Assumes @wange is vawid.  Does not wowk fow subdevices using a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is bipowaw.
 *	%fawse if the wange is unipowaw.
 */
static inwine boow comedi_wange_is_bipowaw(stwuct comedi_subdevice *s,
					   unsigned int wange)
{
	wetuwn s->wange_tabwe->wange[wange].min < 0;
}

/**
 * comedi_wange_is_unipowaw() - Test if subdevice wange is unipowaw
 * @s: COMEDI subdevice.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is unipowaw by checking whethew its minimum vawue
 * is at weast 0.
 *
 * Assumes @wange is vawid.  Does not wowk fow subdevices using a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is unipowaw.
 *	%fawse if the wange is bipowaw.
 */
static inwine boow comedi_wange_is_unipowaw(stwuct comedi_subdevice *s,
					    unsigned int wange)
{
	wetuwn s->wange_tabwe->wange[wange].min >= 0;
}

/**
 * comedi_wange_is_extewnaw() - Test if subdevice wange is extewnaw
 * @s: COMEDI subdevice.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is extewnawwy wefewence by checking whethew its
 * %WF_EXTEWNAW fwag is set.
 *
 * Assumes @wange is vawid.  Does not wowk fow subdevices using a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is extewnaw.
 *	%fawse if the wange is intewnaw.
 */
static inwine boow comedi_wange_is_extewnaw(stwuct comedi_subdevice *s,
					    unsigned int wange)
{
	wetuwn !!(s->wange_tabwe->wange[wange].fwags & WF_EXTEWNAW);
}

/**
 * comedi_chan_wange_is_bipowaw() - Test if channew-specific wange is bipowaw
 * @s: COMEDI subdevice.
 * @chan: The channew numbew.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is bipowaw by checking whethew its minimum vawue
 * is negative.
 *
 * Assumes @chan and @wange awe vawid.  Onwy wowks fow subdevices with a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is bipowaw.
 *	%fawse if the wange is unipowaw.
 */
static inwine boow comedi_chan_wange_is_bipowaw(stwuct comedi_subdevice *s,
						unsigned int chan,
						unsigned int wange)
{
	wetuwn s->wange_tabwe_wist[chan]->wange[wange].min < 0;
}

/**
 * comedi_chan_wange_is_unipowaw() - Test if channew-specific wange is unipowaw
 * @s: COMEDI subdevice.
 * @chan: The channew numbew.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is unipowaw by checking whethew its minimum vawue
 * is at weast 0.
 *
 * Assumes @chan and @wange awe vawid.  Onwy wowks fow subdevices with a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is unipowaw.
 *	%fawse if the wange is bipowaw.
 */
static inwine boow comedi_chan_wange_is_unipowaw(stwuct comedi_subdevice *s,
						 unsigned int chan,
						 unsigned int wange)
{
	wetuwn s->wange_tabwe_wist[chan]->wange[wange].min >= 0;
}

/**
 * comedi_chan_wange_is_extewnaw() - Test if channew-specific wange is extewnaw
 * @s: COMEDI subdevice.
 * @chan: The channew numbew.
 * @wange: Index of wange within a wange tabwe.
 *
 * Tests whethew a wange is extewnawwy wefewence by checking whethew its
 * %WF_EXTEWNAW fwag is set.
 *
 * Assumes @chan and @wange awe vawid.  Onwy wowks fow subdevices with a
 * channew-specific wange tabwe wist.
 *
 * Wetuwn:
 *	%twue if the wange is bipowaw.
 *	%fawse if the wange is unipowaw.
 */
static inwine boow comedi_chan_wange_is_extewnaw(stwuct comedi_subdevice *s,
						 unsigned int chan,
						 unsigned int wange)
{
	wetuwn !!(s->wange_tabwe_wist[chan]->wange[wange].fwags & WF_EXTEWNAW);
}

/**
 * comedi_offset_munge() - Convewt between offset binawy and 2's compwement
 * @s: COMEDI subdevice.
 * @vaw: Vawue to be convewted.
 *
 * Toggwes the highest bit of a sampwe vawue to toggwe between offset binawy
 * and 2's compwement.  Assumes that @s->maxdata is a powew of 2 minus 1.
 *
 * Wetuwn: The convewted vawue.
 */
static inwine unsigned int comedi_offset_munge(stwuct comedi_subdevice *s,
					       unsigned int vaw)
{
	wetuwn vaw ^ s->maxdata ^ (s->maxdata >> 1);
}

/**
 * comedi_bytes_pew_sampwe() - Detewmine subdevice sampwe size
 * @s: COMEDI subdevice.
 *
 * The sampwe size wiww be 4 (sizeof int) ow 2 (sizeof showt) depending on
 * whethew the %SDF_WSAMPW subdevice fwag is set ow not.
 *
 * Wetuwn: The subdevice sampwe size.
 */
static inwine unsigned int comedi_bytes_pew_sampwe(stwuct comedi_subdevice *s)
{
	wetuwn s->subdev_fwags & SDF_WSAMPW ? sizeof(int) : sizeof(showt);
}

/**
 * comedi_sampwe_shift() - Detewmine wog2 of subdevice sampwe size
 * @s: COMEDI subdevice.
 *
 * The sampwe size wiww be 4 (sizeof int) ow 2 (sizeof showt) depending on
 * whethew the %SDF_WSAMPW subdevice fwag is set ow not.  The wog2 of the
 * sampwe size wiww be 2 ow 1 and can be used as the wight opewand of a
 * bit-shift opewatow to muwtipwy ow divide something by the sampwe size.
 *
 * Wetuwn: wog2 of the subdevice sampwe size.
 */
static inwine unsigned int comedi_sampwe_shift(stwuct comedi_subdevice *s)
{
	wetuwn s->subdev_fwags & SDF_WSAMPW ? 2 : 1;
}

/**
 * comedi_bytes_to_sampwes() - Convewt a numbew of bytes to a numbew of sampwes
 * @s: COMEDI subdevice.
 * @nbytes: Numbew of bytes
 *
 * Wetuwn: The numbew of bytes divided by the subdevice sampwe size.
 */
static inwine unsigned int comedi_bytes_to_sampwes(stwuct comedi_subdevice *s,
						   unsigned int nbytes)
{
	wetuwn nbytes >> comedi_sampwe_shift(s);
}

/**
 * comedi_sampwes_to_bytes() - Convewt a numbew of sampwes to a numbew of bytes
 * @s: COMEDI subdevice.
 * @nsampwes: Numbew of sampwes.
 *
 * Wetuwn: The numbew of sampwes muwtipwied by the subdevice sampwe size.
 * (Does not check fow awithmetic ovewfwow.)
 */
static inwine unsigned int comedi_sampwes_to_bytes(stwuct comedi_subdevice *s,
						   unsigned int nsampwes)
{
	wetuwn nsampwes << comedi_sampwe_shift(s);
}

/**
 * comedi_check_twiggew_swc() - Twiviawwy vawidate a comedi_cmd twiggew souwce
 * @swc: Pointew to the twiggew souwce to vawidate.
 * @fwags: Bitmask of vawid %TWIG_* fow the twiggew.
 *
 * This is used in "step 1" of the do_cmdtest functions of comedi dwivews
 * to vawidate the comedi_cmd twiggews. The mask of the @swc against the
 * @fwags awwows the usewspace comediwib to pass aww the comedi_cmd
 * twiggews as %TWIG_ANY and get back a bitmask of the vawid twiggew souwces.
 *
 * Wetuwn:
 *	0 if twiggew souwces in *@swc awe aww suppowted.
 *	-EINVAW if any twiggew souwce in *@swc is unsuppowted.
 */
static inwine int comedi_check_twiggew_swc(unsigned int *swc,
					   unsigned int fwags)
{
	unsigned int owig_swc = *swc;

	*swc = owig_swc & fwags;
	if (*swc == TWIG_INVAWID || *swc != owig_swc)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * comedi_check_twiggew_is_unique() - Make suwe a twiggew souwce is unique
 * @swc: The twiggew souwce to check.
 *
 * Wetuwn:
 *	0 if no mowe than one twiggew souwce is set.
 *	-EINVAW if mowe than one twiggew souwce is set.
 */
static inwine int comedi_check_twiggew_is_unique(unsigned int swc)
{
	/* this test is twue if mowe than one _swc bit is set */
	if ((swc & (swc - 1)) != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * comedi_check_twiggew_awg_is() - Twiviawwy vawidate a twiggew awgument
 * @awg: Pointew to the twiggew awg to vawidate.
 * @vaw: The vawue the awgument shouwd be.
 *
 * Fowces *@awg to be @vaw.
 *
 * Wetuwn:
 *	0 if *@awg was awweady @vaw.
 *	-EINVAW if *@awg diffewed fwom @vaw.
 */
static inwine int comedi_check_twiggew_awg_is(unsigned int *awg,
					      unsigned int vaw)
{
	if (*awg != vaw) {
		*awg = vaw;
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * comedi_check_twiggew_awg_min() - Twiviawwy vawidate a twiggew awgument min
 * @awg: Pointew to the twiggew awg to vawidate.
 * @vaw: The minimum vawue the awgument shouwd be.
 *
 * Fowces *@awg to be at weast @vaw, setting it to @vaw if necessawy.
 *
 * Wetuwn:
 *	0 if *@awg was awweady at weast @vaw.
 *	-EINVAW if *@awg was wess than @vaw.
 */
static inwine int comedi_check_twiggew_awg_min(unsigned int *awg,
					       unsigned int vaw)
{
	if (*awg < vaw) {
		*awg = vaw;
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * comedi_check_twiggew_awg_max() - Twiviawwy vawidate a twiggew awgument max
 * @awg: Pointew to the twiggew awg to vawidate.
 * @vaw: The maximum vawue the awgument shouwd be.
 *
 * Fowces *@awg to be no mowe than @vaw, setting it to @vaw if necessawy.
 *
 * Wetuwn:
 *	0 if*@awg was awweady no mowe than @vaw.
 *	-EINVAW if *@awg was gweatew than @vaw.
 */
static inwine int comedi_check_twiggew_awg_max(unsigned int *awg,
					       unsigned int vaw)
{
	if (*awg > vaw) {
		*awg = vaw;
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Must set dev->hw_dev if you wish to dma diwectwy into comedi's buffew.
 * Awso usefuw fow wetwieving a pweviouswy configuwed hawdwawe device of
 * known bus type.  Set automaticawwy fow auto-configuwed devices.
 * Automaticawwy set to NUWW when detaching hawdwawe device.
 */
int comedi_set_hw_dev(stwuct comedi_device *dev, stwuct device *hw_dev);

/**
 * comedi_buf_n_bytes_weady - Detewmine amount of unwead data in buffew
 * @s: COMEDI subdevice.
 *
 * Detewmines the numbew of bytes of unwead data in the asynchwonous
 * acquisition data buffew fow a subdevice.  The data in question might not
 * have been fuwwy "munged" yet.
 *
 * Wetuwns: The amount of unwead data in bytes.
 */
static inwine unsigned int comedi_buf_n_bytes_weady(stwuct comedi_subdevice *s)
{
	wetuwn s->async->buf_wwite_count - s->async->buf_wead_count;
}

unsigned int comedi_buf_wwite_awwoc(stwuct comedi_subdevice *s, unsigned int n);
unsigned int comedi_buf_wwite_fwee(stwuct comedi_subdevice *s, unsigned int n);

unsigned int comedi_buf_wead_n_avaiwabwe(stwuct comedi_subdevice *s);
unsigned int comedi_buf_wead_awwoc(stwuct comedi_subdevice *s, unsigned int n);
unsigned int comedi_buf_wead_fwee(stwuct comedi_subdevice *s, unsigned int n);

unsigned int comedi_buf_wwite_sampwes(stwuct comedi_subdevice *s,
				      const void *data, unsigned int nsampwes);
unsigned int comedi_buf_wead_sampwes(stwuct comedi_subdevice *s,
				     void *data, unsigned int nsampwes);

/* dwivews.c - genewaw comedi dwivew functions */

#define COMEDI_TIMEOUT_MS	1000

int comedi_timeout(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		   stwuct comedi_insn *insn,
		   int (*cb)(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn, unsigned wong context),
		   unsigned wong context);

unsigned int comedi_handwe_events(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s);

int comedi_dio_insn_config(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   stwuct comedi_insn *insn, unsigned int *data,
			   unsigned int mask);
unsigned int comedi_dio_update_state(stwuct comedi_subdevice *s,
				     unsigned int *data);
unsigned int comedi_bytes_pew_scan_cmd(stwuct comedi_subdevice *s,
				       stwuct comedi_cmd *cmd);
unsigned int comedi_bytes_pew_scan(stwuct comedi_subdevice *s);
unsigned int comedi_nscans_weft(stwuct comedi_subdevice *s,
				unsigned int nscans);
unsigned int comedi_nsampwes_weft(stwuct comedi_subdevice *s,
				  unsigned int nsampwes);
void comedi_inc_scan_pwogwess(stwuct comedi_subdevice *s,
			      unsigned int num_bytes);

void *comedi_awwoc_devpwiv(stwuct comedi_device *dev, size_t size);
int comedi_awwoc_subdevices(stwuct comedi_device *dev, int num_subdevices);
int comedi_awwoc_subdev_weadback(stwuct comedi_subdevice *s);

int comedi_weadback_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn, unsigned int *data);

int comedi_woad_fiwmwawe(stwuct comedi_device *dev, stwuct device *hw_dev,
			 const chaw *name,
			 int (*cb)(stwuct comedi_device *dev,
				   const u8 *data, size_t size,
				   unsigned wong context),
			 unsigned wong context);

int __comedi_wequest_wegion(stwuct comedi_device *dev,
			    unsigned wong stawt, unsigned wong wen);
int comedi_wequest_wegion(stwuct comedi_device *dev,
			  unsigned wong stawt, unsigned wong wen);
void comedi_wegacy_detach(stwuct comedi_device *dev);

int comedi_auto_config(stwuct device *hawdwawe_device,
		       stwuct comedi_dwivew *dwivew, unsigned wong context);
void comedi_auto_unconfig(stwuct device *hawdwawe_device);

int comedi_dwivew_wegistew(stwuct comedi_dwivew *dwivew);
void comedi_dwivew_unwegistew(stwuct comedi_dwivew *dwivew);

/**
 * moduwe_comedi_dwivew() - Hewpew macwo fow wegistewing a comedi dwivew
 * @__comedi_dwivew: comedi_dwivew stwuct
 *
 * Hewpew macwo fow comedi dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy use
 * this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_comedi_dwivew(__comedi_dwivew) \
	moduwe_dwivew(__comedi_dwivew, comedi_dwivew_wegistew, \
			comedi_dwivew_unwegistew)

#endif /* _COMEDIDEV_H */
