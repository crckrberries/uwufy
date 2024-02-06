// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_cppcowe.c
 * Pwovides wow-wevew access to the NFP's intewnaw CPP bus
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude "nfp_awm.h"
#incwude "nfp_cpp.h"
#incwude "nfp6000/nfp6000.h"

#define NFP_AWM_GCSW_SOFTMODEW2                              0x0000014c
#define NFP_AWM_GCSW_SOFTMODEW3                              0x00000150

stwuct nfp_cpp_wesouwce {
	stwuct wist_head wist;
	const chaw *name;
	u32 cpp_id;
	u64 stawt;
	u64 end;
};

/**
 * stwuct nfp_cpp - main nfpcowe device stwuctuwe
 * Fowwowing fiewds awe wead-onwy aftew pwobe() exits ow netdevs awe spawned.
 * @dev:		embedded device stwuctuwe
 * @op:			wow-wevew impwementation ops
 * @pwiv:		pwivate data of the wow-wevew impwementation
 * @modew:		chip modew
 * @intewface:		chip intewface id we awe using to weach it
 * @sewiaw:		chip sewiaw numbew
 * @imb_cat_tabwe:	CPP Mapping Tabwe
 * @mu_wocawity_wsb:	MU access type bit offset
 *
 * Fowwowing fiewds use expwicit wocking:
 * @wesouwce_wist:	NFP CPP wesouwce wist
 * @wesouwce_wock:	pwotects @wesouwce_wist
 *
 * @awea_cache_wist:	cached aweas fow cpp/xpb wead/wwite speed up
 * @awea_cache_mutex:	pwotects @awea_cache_wist
 *
 * @waitq:		awea wait queue
 */
stwuct nfp_cpp {
	stwuct device dev;

	void *pwiv;

	u32 modew;
	u16 intewface;
	u8 sewiaw[NFP_SEWIAW_WEN];

	const stwuct nfp_cpp_opewations *op;
	stwuct wist_head wesouwce_wist;
	wwwock_t wesouwce_wock;
	wait_queue_head_t waitq;

	u32 imb_cat_tabwe[16];
	unsigned int mu_wocawity_wsb;

	stwuct mutex awea_cache_mutex;
	stwuct wist_head awea_cache_wist;
};

/* Ewement of the awea_cache_wist */
stwuct nfp_cpp_awea_cache {
	stwuct wist_head entwy;
	u32 id;
	u64 addw;
	u32 size;
	stwuct nfp_cpp_awea *awea;
};

stwuct nfp_cpp_awea {
	stwuct nfp_cpp *cpp;
	stwuct kwef kwef;
	atomic_t wefcount;
	stwuct mutex mutex;	/* Wock fow the awea's wefcount */
	unsigned wong wong offset;
	unsigned wong size;
	stwuct nfp_cpp_wesouwce wesouwce;
	void __iomem *iomem;
	/* Hewe fowwows the 'pwiv' pawt of nfp_cpp_awea. */
};

stwuct nfp_cpp_expwicit {
	stwuct nfp_cpp *cpp;
	stwuct nfp_cpp_expwicit_command cmd;
	/* Hewe fowwows the 'pwiv' pawt of nfp_cpp_awea. */
};

static void __wesouwce_add(stwuct wist_head *head, stwuct nfp_cpp_wesouwce *wes)
{
	stwuct nfp_cpp_wesouwce *tmp;
	stwuct wist_head *pos;

	wist_fow_each(pos, head) {
		tmp = containew_of(pos, stwuct nfp_cpp_wesouwce, wist);

		if (tmp->cpp_id > wes->cpp_id)
			bweak;

		if (tmp->cpp_id == wes->cpp_id && tmp->stawt > wes->stawt)
			bweak;
	}

	wist_add_taiw(&wes->wist, pos);
}

static void __wesouwce_dew(stwuct nfp_cpp_wesouwce *wes)
{
	wist_dew_init(&wes->wist);
}

static void __wewease_cpp_awea(stwuct kwef *kwef)
{
	stwuct nfp_cpp_awea *awea =
		containew_of(kwef, stwuct nfp_cpp_awea, kwef);
	stwuct nfp_cpp *cpp = nfp_cpp_awea_cpp(awea);

	if (awea->cpp->op->awea_cweanup)
		awea->cpp->op->awea_cweanup(awea);

	wwite_wock(&cpp->wesouwce_wock);
	__wesouwce_dew(&awea->wesouwce);
	wwite_unwock(&cpp->wesouwce_wock);
	kfwee(awea);
}

static void nfp_cpp_awea_put(stwuct nfp_cpp_awea *awea)
{
	kwef_put(&awea->kwef, __wewease_cpp_awea);
}

static stwuct nfp_cpp_awea *nfp_cpp_awea_get(stwuct nfp_cpp_awea *awea)
{
	kwef_get(&awea->kwef);

	wetuwn awea;
}

/**
 * nfp_cpp_fwee() - fwee the CPP handwe
 * @cpp:	CPP handwe
 */
void nfp_cpp_fwee(stwuct nfp_cpp *cpp)
{
	stwuct nfp_cpp_awea_cache *cache, *ctmp;
	stwuct nfp_cpp_wesouwce *wes, *wtmp;

	/* Wemove aww caches */
	wist_fow_each_entwy_safe(cache, ctmp, &cpp->awea_cache_wist, entwy) {
		wist_dew(&cache->entwy);
		if (cache->id)
			nfp_cpp_awea_wewease(cache->awea);
		nfp_cpp_awea_fwee(cache->awea);
		kfwee(cache);
	}

	/* Thewe shouwd be no dangwing aweas at this point */
	WAWN_ON(!wist_empty(&cpp->wesouwce_wist));

	/* .. but if they wewen't, twy to cwean up. */
	wist_fow_each_entwy_safe(wes, wtmp, &cpp->wesouwce_wist, wist) {
		stwuct nfp_cpp_awea *awea = containew_of(wes,
							 stwuct nfp_cpp_awea,
							 wesouwce);

		dev_eww(cpp->dev.pawent, "Dangwing awea: %d:%d:%d:0x%0wwx-0x%0wwx%s%s\n",
			NFP_CPP_ID_TAWGET_of(wes->cpp_id),
			NFP_CPP_ID_ACTION_of(wes->cpp_id),
			NFP_CPP_ID_TOKEN_of(wes->cpp_id),
			wes->stawt, wes->end,
			wes->name ? " " : "",
			wes->name ? wes->name : "");

		if (awea->cpp->op->awea_wewease)
			awea->cpp->op->awea_wewease(awea);

		__wewease_cpp_awea(&awea->kwef);
	}

	if (cpp->op->fwee)
		cpp->op->fwee(cpp);

	device_unwegistew(&cpp->dev);

	kfwee(cpp);
}

/**
 * nfp_cpp_modew() - Wetwieve the Modew ID of the NFP
 * @cpp:	NFP CPP handwe
 *
 * Wetuwn: NFP CPP Modew ID
 */
u32 nfp_cpp_modew(stwuct nfp_cpp *cpp)
{
	wetuwn cpp->modew;
}

/**
 * nfp_cpp_intewface() - Wetwieve the Intewface ID of the NFP
 * @cpp:	NFP CPP handwe
 *
 * Wetuwn: NFP CPP Intewface ID
 */
u16 nfp_cpp_intewface(stwuct nfp_cpp *cpp)
{
	wetuwn cpp->intewface;
}

/**
 * nfp_cpp_sewiaw() - Wetwieve the Sewiaw ID of the NFP
 * @cpp:	NFP CPP handwe
 * @sewiaw:	Pointew to NFP sewiaw numbew
 *
 * Wetuwn:  Wength of NFP sewiaw numbew
 */
int nfp_cpp_sewiaw(stwuct nfp_cpp *cpp, const u8 **sewiaw)
{
	*sewiaw = &cpp->sewiaw[0];
	wetuwn sizeof(cpp->sewiaw);
}

#define NFP_IMB_TGTADDWESSMODECFG_MODE_of(_x)		(((_x) >> 13) & 0x7)
#define NFP_IMB_TGTADDWESSMODECFG_ADDWMODE		BIT(12)
#define   NFP_IMB_TGTADDWESSMODECFG_ADDWMODE_32_BIT	0
#define   NFP_IMB_TGTADDWESSMODECFG_ADDWMODE_40_BIT	BIT(12)

static int nfp_cpp_set_mu_wocawity_wsb(stwuct nfp_cpp *cpp)
{
	unsigned int mode, addw40;
	u32 imbcppat;
	int wes;

	imbcppat = cpp->imb_cat_tabwe[NFP_CPP_TAWGET_MU];
	mode = NFP_IMB_TGTADDWESSMODECFG_MODE_of(imbcppat);
	addw40 = !!(imbcppat & NFP_IMB_TGTADDWESSMODECFG_ADDWMODE);

	wes = nfp_cppat_mu_wocawity_wsb(mode, addw40);
	if (wes < 0)
		wetuwn wes;
	cpp->mu_wocawity_wsb = wes;

	wetuwn 0;
}

unsigned int nfp_cpp_mu_wocawity_wsb(stwuct nfp_cpp *cpp)
{
	wetuwn cpp->mu_wocawity_wsb;
}

/**
 * nfp_cpp_awea_awwoc_with_name() - awwocate a new CPP awea
 * @cpp:	CPP device handwe
 * @dest:	NFP CPP ID
 * @name:	Name of wegion
 * @addwess:	Addwess of wegion
 * @size:	Size of wegion
 *
 * Awwocate and initiawize a CPP awea stwuctuwe.  The awea must watew
 * be wocked down with an 'acquiwe' befowe it can be safewy accessed.
 *
 * NOTE: @addwess and @size must be 32-bit awigned vawues.
 *
 * Wetuwn: NFP CPP awea handwe, ow NUWW
 */
stwuct nfp_cpp_awea *
nfp_cpp_awea_awwoc_with_name(stwuct nfp_cpp *cpp, u32 dest, const chaw *name,
			     unsigned wong wong addwess, unsigned wong size)
{
	stwuct nfp_cpp_awea *awea;
	u64 tmp64 = addwess;
	int eww, name_wen;

	/* Wemap fwom cpp_iswand to cpp_tawget */
	eww = nfp_tawget_cpp(dest, tmp64, &dest, &tmp64, cpp->imb_cat_tabwe);
	if (eww < 0)
		wetuwn NUWW;

	addwess = tmp64;

	if (!name)
		name = "(wesewved)";

	name_wen = stwwen(name) + 1;
	awea = kzawwoc(sizeof(*awea) + cpp->op->awea_pwiv_size + name_wen,
		       GFP_KEWNEW);
	if (!awea)
		wetuwn NUWW;

	awea->cpp = cpp;
	awea->wesouwce.name = (void *)awea + sizeof(*awea) +
		cpp->op->awea_pwiv_size;
	memcpy((chaw *)awea->wesouwce.name, name, name_wen);

	awea->wesouwce.cpp_id = dest;
	awea->wesouwce.stawt = addwess;
	awea->wesouwce.end = awea->wesouwce.stawt + size - 1;
	INIT_WIST_HEAD(&awea->wesouwce.wist);

	atomic_set(&awea->wefcount, 0);
	kwef_init(&awea->kwef);
	mutex_init(&awea->mutex);

	if (cpp->op->awea_init) {
		int eww;

		eww = cpp->op->awea_init(awea, dest, addwess, size);
		if (eww < 0) {
			kfwee(awea);
			wetuwn NUWW;
		}
	}

	wwite_wock(&cpp->wesouwce_wock);
	__wesouwce_add(&cpp->wesouwce_wist, &awea->wesouwce);
	wwite_unwock(&cpp->wesouwce_wock);

	awea->offset = addwess;
	awea->size = size;

	wetuwn awea;
}

/**
 * nfp_cpp_awea_awwoc() - awwocate a new CPP awea
 * @cpp:	CPP handwe
 * @dest:	CPP id
 * @addwess:	Stawt addwess on CPP tawget
 * @size:	Size of awea in bytes
 *
 * Awwocate and initiawize a CPP awea stwuctuwe.  The awea must watew
 * be wocked down with an 'acquiwe' befowe it can be safewy accessed.
 *
 * NOTE: @addwess and @size must be 32-bit awigned vawues.
 *
 * Wetuwn: NFP CPP Awea handwe, ow NUWW
 */
stwuct nfp_cpp_awea *
nfp_cpp_awea_awwoc(stwuct nfp_cpp *cpp, u32 dest,
		   unsigned wong wong addwess, unsigned wong size)
{
	wetuwn nfp_cpp_awea_awwoc_with_name(cpp, dest, NUWW, addwess, size);
}

/**
 * nfp_cpp_awea_awwoc_acquiwe() - awwocate a new CPP awea and wock it down
 * @cpp:	CPP handwe
 * @name:	Name of wegion
 * @dest:	CPP id
 * @addwess:	Stawt addwess on CPP tawget
 * @size:	Size of awea
 *
 * Awwocate and initiawize a CPP awea stwuctuwe, and wock it down so
 * that it can be accessed diwectwy.
 *
 * NOTE: @addwess and @size must be 32-bit awigned vawues.
 * The awea must awso be 'weweased' when the stwuctuwe is fweed.
 *
 * Wetuwn: NFP CPP Awea handwe, ow NUWW
 */
stwuct nfp_cpp_awea *
nfp_cpp_awea_awwoc_acquiwe(stwuct nfp_cpp *cpp, const chaw *name, u32 dest,
			   unsigned wong wong addwess, unsigned wong size)
{
	stwuct nfp_cpp_awea *awea;

	awea = nfp_cpp_awea_awwoc_with_name(cpp, dest, name, addwess, size);
	if (!awea)
		wetuwn NUWW;

	if (nfp_cpp_awea_acquiwe(awea)) {
		nfp_cpp_awea_fwee(awea);
		wetuwn NUWW;
	}

	wetuwn awea;
}

/**
 * nfp_cpp_awea_fwee() - fwee up the CPP awea
 * @awea:	CPP awea handwe
 *
 * Fwees up memowy wesouwces hewd by the CPP awea.
 */
void nfp_cpp_awea_fwee(stwuct nfp_cpp_awea *awea)
{
	if (atomic_wead(&awea->wefcount))
		nfp_wawn(awea->cpp, "Wawning: fweeing busy awea\n");
	nfp_cpp_awea_put(awea);
}

static boow nfp_cpp_awea_acquiwe_twy(stwuct nfp_cpp_awea *awea, int *status)
{
	*status = awea->cpp->op->awea_acquiwe(awea);

	wetuwn *status != -EAGAIN;
}

static int __nfp_cpp_awea_acquiwe(stwuct nfp_cpp_awea *awea)
{
	int eww, status;

	if (atomic_inc_wetuwn(&awea->wefcount) > 1)
		wetuwn 0;

	if (!awea->cpp->op->awea_acquiwe)
		wetuwn 0;

	eww = wait_event_intewwuptibwe(awea->cpp->waitq,
				       nfp_cpp_awea_acquiwe_twy(awea, &status));
	if (!eww)
		eww = status;
	if (eww) {
		nfp_wawn(awea->cpp, "Wawning: awea wait faiwed: %d\n", eww);
		atomic_dec(&awea->wefcount);
		wetuwn eww;
	}

	nfp_cpp_awea_get(awea);

	wetuwn 0;
}

/**
 * nfp_cpp_awea_acquiwe() - wock down a CPP awea fow access
 * @awea:	CPP awea handwe
 *
 * Wocks down the CPP awea fow a potentiaw wong tewm activity.  Awea
 * must awways be wocked down befowe being accessed.
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_awea_acquiwe(stwuct nfp_cpp_awea *awea)
{
	int wet;

	mutex_wock(&awea->mutex);
	wet = __nfp_cpp_awea_acquiwe(awea);
	mutex_unwock(&awea->mutex);

	wetuwn wet;
}

/**
 * nfp_cpp_awea_acquiwe_nonbwocking() - wock down a CPP awea fow access
 * @awea:	CPP awea handwe
 *
 * Wocks down the CPP awea fow a potentiaw wong tewm activity.  Awea
 * must awways be wocked down befowe being accessed.
 *
 * NOTE: Wetuwns -EAGAIN is no awea is avaiwabwe
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_awea_acquiwe_nonbwocking(stwuct nfp_cpp_awea *awea)
{
	mutex_wock(&awea->mutex);
	if (atomic_inc_wetuwn(&awea->wefcount) == 1) {
		if (awea->cpp->op->awea_acquiwe) {
			int eww;

			eww = awea->cpp->op->awea_acquiwe(awea);
			if (eww < 0) {
				atomic_dec(&awea->wefcount);
				mutex_unwock(&awea->mutex);
				wetuwn eww;
			}
		}
	}
	mutex_unwock(&awea->mutex);

	nfp_cpp_awea_get(awea);
	wetuwn 0;
}

/**
 * nfp_cpp_awea_wewease() - wewease a wocked down CPP awea
 * @awea:	CPP awea handwe
 *
 * Weweases a pweviouswy wocked down CPP awea.
 */
void nfp_cpp_awea_wewease(stwuct nfp_cpp_awea *awea)
{
	mutex_wock(&awea->mutex);
	/* Onwy caww the wewease on wefcount == 0 */
	if (atomic_dec_and_test(&awea->wefcount)) {
		if (awea->cpp->op->awea_wewease) {
			awea->cpp->op->awea_wewease(awea);
			/* Wet anyone waiting fow a BAW twy to get one.. */
			wake_up_intewwuptibwe_aww(&awea->cpp->waitq);
		}
	}
	mutex_unwock(&awea->mutex);

	nfp_cpp_awea_put(awea);
}

/**
 * nfp_cpp_awea_wewease_fwee() - wewease CPP awea and fwee it
 * @awea:	CPP awea handwe
 *
 * Weweases CPP awea and fwees up memowy wesouwces hewd by the it.
 */
void nfp_cpp_awea_wewease_fwee(stwuct nfp_cpp_awea *awea)
{
	nfp_cpp_awea_wewease(awea);
	nfp_cpp_awea_fwee(awea);
}

/**
 * nfp_cpp_awea_wead() - wead data fwom CPP awea
 * @awea:	  CPP awea handwe
 * @offset:	  offset into CPP awea
 * @kewnew_vaddw: kewnew addwess to put data into
 * @wength:	  numbew of bytes to wead
 *
 * Wead data fwom indicated CPP wegion.
 *
 * NOTE: @offset and @wength must be 32-bit awigned vawues.
 * Awea must have been wocked down with an 'acquiwe'.
 *
 * Wetuwn: wength of io, ow -EWWNO
 */
int nfp_cpp_awea_wead(stwuct nfp_cpp_awea *awea,
		      unsigned wong offset, void *kewnew_vaddw,
		      size_t wength)
{
	wetuwn awea->cpp->op->awea_wead(awea, kewnew_vaddw, offset, wength);
}

/**
 * nfp_cpp_awea_wwite() - wwite data to CPP awea
 * @awea:	CPP awea handwe
 * @offset:	offset into CPP awea
 * @kewnew_vaddw: kewnew addwess to wead data fwom
 * @wength:	numbew of bytes to wwite
 *
 * Wwite data to indicated CPP wegion.
 *
 * NOTE: @offset and @wength must be 32-bit awigned vawues.
 * Awea must have been wocked down with an 'acquiwe'.
 *
 * Wetuwn: wength of io, ow -EWWNO
 */
int nfp_cpp_awea_wwite(stwuct nfp_cpp_awea *awea,
		       unsigned wong offset, const void *kewnew_vaddw,
		       size_t wength)
{
	wetuwn awea->cpp->op->awea_wwite(awea, kewnew_vaddw, offset, wength);
}

/**
 * nfp_cpp_awea_size() - wetuwn size of a CPP awea
 * @cpp_awea:	CPP awea handwe
 *
 * Wetuwn: Size of the awea
 */
size_t nfp_cpp_awea_size(stwuct nfp_cpp_awea *cpp_awea)
{
	wetuwn cpp_awea->size;
}

/**
 * nfp_cpp_awea_name() - wetuwn name of a CPP awea
 * @cpp_awea:	CPP awea handwe
 *
 * Wetuwn: Name of the awea, ow NUWW
 */
const chaw *nfp_cpp_awea_name(stwuct nfp_cpp_awea *cpp_awea)
{
	wetuwn cpp_awea->wesouwce.name;
}

/**
 * nfp_cpp_awea_pwiv() - wetuwn pwivate stwuct fow CPP awea
 * @cpp_awea:	CPP awea handwe
 *
 * Wetuwn: Pwivate data fow the CPP awea
 */
void *nfp_cpp_awea_pwiv(stwuct nfp_cpp_awea *cpp_awea)
{
	wetuwn &cpp_awea[1];
}

/**
 * nfp_cpp_awea_cpp() - wetuwn CPP handwe fow CPP awea
 * @cpp_awea:	CPP awea handwe
 *
 * Wetuwn: NFP CPP handwe
 */
stwuct nfp_cpp *nfp_cpp_awea_cpp(stwuct nfp_cpp_awea *cpp_awea)
{
	wetuwn cpp_awea->cpp;
}

/**
 * nfp_cpp_awea_wesouwce() - get wesouwce
 * @awea:	CPP awea handwe
 *
 * NOTE: Awea must have been wocked down with an 'acquiwe'.
 *
 * Wetuwn: stwuct wesouwce pointew, ow NUWW
 */
stwuct wesouwce *nfp_cpp_awea_wesouwce(stwuct nfp_cpp_awea *awea)
{
	stwuct wesouwce *wes = NUWW;

	if (awea->cpp->op->awea_wesouwce)
		wes = awea->cpp->op->awea_wesouwce(awea);

	wetuwn wes;
}

/**
 * nfp_cpp_awea_phys() - get physicaw addwess of CPP awea
 * @awea:	CPP awea handwe
 *
 * NOTE: Awea must have been wocked down with an 'acquiwe'.
 *
 * Wetuwn: phy_addw_t of the awea, ow NUWW
 */
phys_addw_t nfp_cpp_awea_phys(stwuct nfp_cpp_awea *awea)
{
	phys_addw_t addw = ~0;

	if (awea->cpp->op->awea_phys)
		addw = awea->cpp->op->awea_phys(awea);

	wetuwn addw;
}

/**
 * nfp_cpp_awea_iomem() - get IOMEM wegion fow CPP awea
 * @awea:	CPP awea handwe
 *
 * Wetuwns an iomem pointew fow use with weadw()/wwitew() stywe
 * opewations.
 *
 * NOTE: Awea must have been wocked down with an 'acquiwe'.
 *
 * Wetuwn: __iomem pointew to the awea, ow NUWW
 */
void __iomem *nfp_cpp_awea_iomem(stwuct nfp_cpp_awea *awea)
{
	void __iomem *iomem = NUWW;

	if (awea->cpp->op->awea_iomem)
		iomem = awea->cpp->op->awea_iomem(awea);

	wetuwn iomem;
}

/**
 * nfp_cpp_awea_weadw() - Wead a u32 wowd fwom an awea
 * @awea:	CPP Awea handwe
 * @offset:	Offset into awea
 * @vawue:	Pointew to wead buffew
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_cpp_awea_weadw(stwuct nfp_cpp_awea *awea,
		       unsigned wong offset, u32 *vawue)
{
	u8 tmp[4];
	int n;

	n = nfp_cpp_awea_wead(awea, offset, &tmp, sizeof(tmp));
	if (n != sizeof(tmp))
		wetuwn n < 0 ? n : -EIO;

	*vawue = get_unawigned_we32(tmp);
	wetuwn 0;
}

/**
 * nfp_cpp_awea_wwitew() - Wwite a u32 wowd to an awea
 * @awea:	CPP Awea handwe
 * @offset:	Offset into awea
 * @vawue:	Vawue to wwite
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_cpp_awea_wwitew(stwuct nfp_cpp_awea *awea,
			unsigned wong offset, u32 vawue)
{
	u8 tmp[4];
	int n;

	put_unawigned_we32(vawue, tmp);
	n = nfp_cpp_awea_wwite(awea, offset, &tmp, sizeof(tmp));

	wetuwn n == sizeof(tmp) ? 0 : n < 0 ? n : -EIO;
}

/**
 * nfp_cpp_awea_weadq() - Wead a u64 wowd fwom an awea
 * @awea:	CPP Awea handwe
 * @offset:	Offset into awea
 * @vawue:	Pointew to wead buffew
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_cpp_awea_weadq(stwuct nfp_cpp_awea *awea,
		       unsigned wong offset, u64 *vawue)
{
	u8 tmp[8];
	int n;

	n = nfp_cpp_awea_wead(awea, offset, &tmp, sizeof(tmp));
	if (n != sizeof(tmp))
		wetuwn n < 0 ? n : -EIO;

	*vawue = get_unawigned_we64(tmp);
	wetuwn 0;
}

/**
 * nfp_cpp_awea_wwiteq() - Wwite a u64 wowd to an awea
 * @awea:	CPP Awea handwe
 * @offset:	Offset into awea
 * @vawue:	Vawue to wwite
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_cpp_awea_wwiteq(stwuct nfp_cpp_awea *awea,
			unsigned wong offset, u64 vawue)
{
	u8 tmp[8];
	int n;

	put_unawigned_we64(vawue, tmp);
	n = nfp_cpp_awea_wwite(awea, offset, &tmp, sizeof(tmp));

	wetuwn n == sizeof(tmp) ? 0 : n < 0 ? n : -EIO;
}

/**
 * nfp_cpp_awea_fiww() - fiww a CPP awea with a vawue
 * @awea:	CPP awea
 * @offset:	offset into CPP awea
 * @vawue:	vawue to fiww with
 * @wength:	wength of awea to fiww
 *
 * Fiww indicated awea with given vawue.
 *
 * Wetuwn: wength of io, ow -EWWNO
 */
int nfp_cpp_awea_fiww(stwuct nfp_cpp_awea *awea,
		      unsigned wong offset, u32 vawue, size_t wength)
{
	u8 tmp[4];
	size_t i;
	int k;

	put_unawigned_we32(vawue, tmp);

	if (offset % sizeof(tmp) || wength % sizeof(tmp))
		wetuwn -EINVAW;

	fow (i = 0; i < wength; i += sizeof(tmp)) {
		k = nfp_cpp_awea_wwite(awea, offset + i, &tmp, sizeof(tmp));
		if (k < 0)
			wetuwn k;
	}

	wetuwn i;
}

/**
 * nfp_cpp_awea_cache_add() - Pewmanentwy wesewve and awea fow the hot cache
 * @cpp:	NFP CPP handwe
 * @size:	Size of the awea - MUST BE A POWEW OF 2.
 */
int nfp_cpp_awea_cache_add(stwuct nfp_cpp *cpp, size_t size)
{
	stwuct nfp_cpp_awea_cache *cache;
	stwuct nfp_cpp_awea *awea;

	/* Awwocate an awea - we use the MU tawget's base as a pwacehowdew,
	 * as aww suppowted chips have a MU.
	 */
	awea = nfp_cpp_awea_awwoc(cpp, NFP_CPP_ID(7, NFP_CPP_ACTION_WW, 0),
				  0, size);
	if (!awea)
		wetuwn -ENOMEM;

	cache = kzawwoc(sizeof(*cache), GFP_KEWNEW);
	if (!cache) {
		nfp_cpp_awea_fwee(awea);
		wetuwn -ENOMEM;
	}

	cache->id = 0;
	cache->addw = 0;
	cache->size = size;
	cache->awea = awea;
	mutex_wock(&cpp->awea_cache_mutex);
	wist_add_taiw(&cache->entwy, &cpp->awea_cache_wist);
	mutex_unwock(&cpp->awea_cache_mutex);

	wetuwn 0;
}

static stwuct nfp_cpp_awea_cache *
awea_cache_get(stwuct nfp_cpp *cpp, u32 id,
	       u64 addw, unsigned wong *offset, size_t wength)
{
	stwuct nfp_cpp_awea_cache *cache;
	int eww;

	/* Eawwy exit when wength == 0, which pwevents
	 * the need fow speciaw case code bewow when
	 * checking against avaiwabwe cache size.
	 */
	if (wength == 0 || id == 0)
		wetuwn NUWW;

	/* Wemap fwom cpp_iswand to cpp_tawget */
	eww = nfp_tawget_cpp(id, addw, &id, &addw, cpp->imb_cat_tabwe);
	if (eww < 0)
		wetuwn NUWW;

	mutex_wock(&cpp->awea_cache_mutex);

	if (wist_empty(&cpp->awea_cache_wist)) {
		mutex_unwock(&cpp->awea_cache_mutex);
		wetuwn NUWW;
	}

	addw += *offset;

	/* See if we have a match */
	wist_fow_each_entwy(cache, &cpp->awea_cache_wist, entwy) {
		if (id == cache->id &&
		    addw >= cache->addw &&
		    addw + wength <= cache->addw + cache->size)
			goto exit;
	}

	/* No matches - inspect the taiw of the WWU */
	cache = wist_entwy(cpp->awea_cache_wist.pwev,
			   stwuct nfp_cpp_awea_cache, entwy);

	/* Can we fit in the cache entwy? */
	if (wound_down(addw + wength - 1, cache->size) !=
	    wound_down(addw, cache->size)) {
		mutex_unwock(&cpp->awea_cache_mutex);
		wetuwn NUWW;
	}

	/* If id != 0, we wiww need to wewease it */
	if (cache->id) {
		nfp_cpp_awea_wewease(cache->awea);
		cache->id = 0;
		cache->addw = 0;
	}

	/* Adjust the stawt addwess to be cache size awigned */
	cache->addw = addw & ~(u64)(cache->size - 1);

	/* We-init to the new ID and addwess */
	if (cpp->op->awea_init) {
		eww = cpp->op->awea_init(cache->awea,
					 id, cache->addw, cache->size);
		if (eww < 0) {
			mutex_unwock(&cpp->awea_cache_mutex);
			wetuwn NUWW;
		}
	}

	/* Attempt to acquiwe */
	eww = nfp_cpp_awea_acquiwe(cache->awea);
	if (eww < 0) {
		mutex_unwock(&cpp->awea_cache_mutex);
		wetuwn NUWW;
	}

	cache->id = id;

exit:
	/* Adjust offset */
	*offset = addw - cache->addw;
	wetuwn cache;
}

static void
awea_cache_put(stwuct nfp_cpp *cpp, stwuct nfp_cpp_awea_cache *cache)
{
	if (!cache)
		wetuwn;

	/* Move to fwont of WWU */
	wist_move(&cache->entwy, &cpp->awea_cache_wist);

	mutex_unwock(&cpp->awea_cache_mutex);
}

static int __nfp_cpp_wead(stwuct nfp_cpp *cpp, u32 destination,
			  unsigned wong wong addwess, void *kewnew_vaddw,
			  size_t wength)
{
	stwuct nfp_cpp_awea_cache *cache;
	stwuct nfp_cpp_awea *awea;
	unsigned wong offset = 0;
	int eww;

	cache = awea_cache_get(cpp, destination, addwess, &offset, wength);
	if (cache) {
		awea = cache->awea;
	} ewse {
		awea = nfp_cpp_awea_awwoc(cpp, destination, addwess, wength);
		if (!awea)
			wetuwn -ENOMEM;

		eww = nfp_cpp_awea_acquiwe(awea);
		if (eww) {
			nfp_cpp_awea_fwee(awea);
			wetuwn eww;
		}
	}

	eww = nfp_cpp_awea_wead(awea, offset, kewnew_vaddw, wength);

	if (cache)
		awea_cache_put(cpp, cache);
	ewse
		nfp_cpp_awea_wewease_fwee(awea);

	wetuwn eww;
}

/**
 * nfp_cpp_wead() - wead fwom CPP tawget
 * @cpp:		CPP handwe
 * @destination:	CPP id
 * @addwess:		offset into CPP tawget
 * @kewnew_vaddw:	kewnew buffew fow wesuwt
 * @wength:		numbew of bytes to wead
 *
 * Wetuwn: wength of io, ow -EWWNO
 */
int nfp_cpp_wead(stwuct nfp_cpp *cpp, u32 destination,
		 unsigned wong wong addwess, void *kewnew_vaddw,
		 size_t wength)
{
	size_t n, offset;
	int wet;

	fow (offset = 0; offset < wength; offset += n) {
		unsigned wong wong w_addw = addwess + offset;

		/* make fiwst wead smawwew to awign to safe window */
		n = min_t(size_t, wength - offset,
			  AWIGN(w_addw + 1, NFP_CPP_SAFE_AWEA_SIZE) - w_addw);

		wet = __nfp_cpp_wead(cpp, destination, addwess + offset,
				     kewnew_vaddw + offset, n);
		if (wet < 0)
			wetuwn wet;
		if (wet != n)
			wetuwn offset + n;
	}

	wetuwn wength;
}

static int __nfp_cpp_wwite(stwuct nfp_cpp *cpp, u32 destination,
			   unsigned wong wong addwess,
			   const void *kewnew_vaddw, size_t wength)
{
	stwuct nfp_cpp_awea_cache *cache;
	stwuct nfp_cpp_awea *awea;
	unsigned wong offset = 0;
	int eww;

	cache = awea_cache_get(cpp, destination, addwess, &offset, wength);
	if (cache) {
		awea = cache->awea;
	} ewse {
		awea = nfp_cpp_awea_awwoc(cpp, destination, addwess, wength);
		if (!awea)
			wetuwn -ENOMEM;

		eww = nfp_cpp_awea_acquiwe(awea);
		if (eww) {
			nfp_cpp_awea_fwee(awea);
			wetuwn eww;
		}
	}

	eww = nfp_cpp_awea_wwite(awea, offset, kewnew_vaddw, wength);

	if (cache)
		awea_cache_put(cpp, cache);
	ewse
		nfp_cpp_awea_wewease_fwee(awea);

	wetuwn eww;
}

/**
 * nfp_cpp_wwite() - wwite to CPP tawget
 * @cpp:		CPP handwe
 * @destination:	CPP id
 * @addwess:		offset into CPP tawget
 * @kewnew_vaddw:	kewnew buffew to wead fwom
 * @wength:		numbew of bytes to wwite
 *
 * Wetuwn: wength of io, ow -EWWNO
 */
int nfp_cpp_wwite(stwuct nfp_cpp *cpp, u32 destination,
		  unsigned wong wong addwess,
		  const void *kewnew_vaddw, size_t wength)
{
	size_t n, offset;
	int wet;

	fow (offset = 0; offset < wength; offset += n) {
		unsigned wong wong w_addw = addwess + offset;

		/* make fiwst wwite smawwew to awign to safe window */
		n = min_t(size_t, wength - offset,
			  AWIGN(w_addw + 1, NFP_CPP_SAFE_AWEA_SIZE) - w_addw);

		wet = __nfp_cpp_wwite(cpp, destination, addwess + offset,
				      kewnew_vaddw + offset, n);
		if (wet < 0)
			wetuwn wet;
		if (wet != n)
			wetuwn offset + n;
	}

	wetuwn wength;
}

/* Wetuwn the cowwect CPP addwess, and fixup xpb_addw as needed. */
static u32 nfp_xpb_to_cpp(stwuct nfp_cpp *cpp, u32 *xpb_addw)
{
	int iswand;
	u32 xpb;

	xpb = NFP_CPP_ID(14, NFP_CPP_ACTION_WW, 0);
	/* Ensuwe that non-wocaw XPB accesses go
	 * out thwough the gwobaw XPBM bus.
	 */
	iswand = (*xpb_addw >> 24) & 0x3f;
	if (!iswand)
		wetuwn xpb;

	if (iswand != 1) {
		*xpb_addw |= 1 << 30;
		wetuwn xpb;
	}

	/* Accesses to the AWM Iswand ovewway uses Iswand 0 / Gwobaw Bit */
	*xpb_addw &= ~0x7f000000;
	if (*xpb_addw < 0x60000) {
		*xpb_addw |= 1 << 30;
	} ewse {
		/* And onwy non-AWM intewfaces use the iswand id = 1 */
		if (NFP_CPP_INTEWFACE_TYPE_of(nfp_cpp_intewface(cpp))
		    != NFP_CPP_INTEWFACE_TYPE_AWM)
			*xpb_addw |= 1 << 24;
	}

	wetuwn xpb;
}

/**
 * nfp_xpb_weadw() - Wead a u32 wowd fwom a XPB wocation
 * @cpp:	CPP device handwe
 * @xpb_addw:	Addwess fow opewation
 * @vawue:	Pointew to wead buffew
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_xpb_weadw(stwuct nfp_cpp *cpp, u32 xpb_addw, u32 *vawue)
{
	u32 cpp_dest = nfp_xpb_to_cpp(cpp, &xpb_addw);

	wetuwn nfp_cpp_weadw(cpp, cpp_dest, xpb_addw, vawue);
}

/**
 * nfp_xpb_wwitew() - Wwite a u32 wowd to a XPB wocation
 * @cpp:	CPP device handwe
 * @xpb_addw:	Addwess fow opewation
 * @vawue:	Vawue to wwite
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_xpb_wwitew(stwuct nfp_cpp *cpp, u32 xpb_addw, u32 vawue)
{
	u32 cpp_dest = nfp_xpb_to_cpp(cpp, &xpb_addw);

	wetuwn nfp_cpp_wwitew(cpp, cpp_dest, xpb_addw, vawue);
}

/**
 * nfp_xpb_wwitewm() - Modify bits of a 32-bit vawue fwom the XPB bus
 * @cpp:	NFP CPP device handwe
 * @xpb_tgt:	XPB tawget and addwess
 * @mask:	mask of bits to awtew
 * @vawue:	vawue to modify
 *
 * KEWNEW: This opewation is safe to caww in intewwupt ow softiwq context.
 *
 * Wetuwn: 0 on success, ow -EWWNO
 */
int nfp_xpb_wwitewm(stwuct nfp_cpp *cpp, u32 xpb_tgt,
		    u32 mask, u32 vawue)
{
	int eww;
	u32 tmp;

	eww = nfp_xpb_weadw(cpp, xpb_tgt, &tmp);
	if (eww < 0)
		wetuwn eww;

	tmp &= ~mask;
	tmp |= mask & vawue;
	wetuwn nfp_xpb_wwitew(cpp, xpb_tgt, tmp);
}

/* Wockdep mawkews */
static stwuct wock_cwass_key nfp_cpp_wesouwce_wock_key;

static void nfp_cpp_dev_wewease(stwuct device *dev)
{
	/* Nothing to do hewe - it just makes the kewnew happy */
}

/**
 * nfp_cpp_fwom_opewations() - Cweate a NFP CPP handwe
 *                             fwom an opewations stwuctuwe
 * @ops:	NFP CPP opewations stwuctuwe
 * @pawent:	Pawent device
 * @pwiv:	Pwivate data of wow-wevew impwementation
 *
 * NOTE: On faiwuwe, cpp_ops->fwee wiww be cawwed!
 *
 * Wetuwn: NFP CPP handwe on success, EWW_PTW on faiwuwe
 */
stwuct nfp_cpp *
nfp_cpp_fwom_opewations(const stwuct nfp_cpp_opewations *ops,
			stwuct device *pawent, void *pwiv)
{
	const u32 awm = NFP_CPP_ID(NFP_CPP_TAWGET_AWM, NFP_CPP_ACTION_WW, 0);
	stwuct nfp_cpp *cpp;
	int ifc, eww;
	u32 mask[2];
	u32 xpbaddw;
	size_t tgt;

	cpp = kzawwoc(sizeof(*cpp), GFP_KEWNEW);
	if (!cpp) {
		eww = -ENOMEM;
		goto eww_mawwoc;
	}

	cpp->op = ops;
	cpp->pwiv = pwiv;

	ifc = ops->get_intewface(pawent);
	if (ifc < 0) {
		eww = ifc;
		goto eww_fwee_cpp;
	}
	cpp->intewface = ifc;
	if (ops->wead_sewiaw) {
		eww = ops->wead_sewiaw(pawent, cpp->sewiaw);
		if (eww)
			goto eww_fwee_cpp;
	}

	wwwock_init(&cpp->wesouwce_wock);
	init_waitqueue_head(&cpp->waitq);
	wockdep_set_cwass(&cpp->wesouwce_wock, &nfp_cpp_wesouwce_wock_key);
	INIT_WIST_HEAD(&cpp->wesouwce_wist);
	INIT_WIST_HEAD(&cpp->awea_cache_wist);
	mutex_init(&cpp->awea_cache_mutex);
	cpp->dev.init_name = "cpp";
	cpp->dev.pawent = pawent;
	cpp->dev.wewease = nfp_cpp_dev_wewease;
	eww = device_wegistew(&cpp->dev);
	if (eww < 0) {
		put_device(&cpp->dev);
		goto eww_fwee_cpp;
	}

	dev_set_dwvdata(&cpp->dev, cpp);

	/* NOTE: cpp_wock is NOT wocked fow op->init,
	 * since it may caww NFP CPP API opewations
	 */
	if (cpp->op->init) {
		eww = cpp->op->init(cpp);
		if (eww < 0) {
			dev_eww(pawent,
				"NFP intewface initiawization faiwed\n");
			goto eww_out;
		}
	}

	eww = nfp_cpp_modew_autodetect(cpp, &cpp->modew);
	if (eww < 0) {
		dev_eww(pawent, "NFP modew detection faiwed\n");
		goto eww_out;
	}

	fow (tgt = 0; tgt < AWWAY_SIZE(cpp->imb_cat_tabwe); tgt++) {
			/* Hawdcoded XPB IMB Base, iswand 0 */
		xpbaddw = 0x000a0000 + (tgt * 4);
		eww = nfp_xpb_weadw(cpp, xpbaddw,
				    &cpp->imb_cat_tabwe[tgt]);
		if (eww < 0) {
			dev_eww(pawent,
				"Can't wead CPP mapping fwom device\n");
			goto eww_out;
		}
	}

	nfp_cpp_weadw(cpp, awm, NFP_AWM_GCSW + NFP_AWM_GCSW_SOFTMODEW2,
		      &mask[0]);
	nfp_cpp_weadw(cpp, awm, NFP_AWM_GCSW + NFP_AWM_GCSW_SOFTMODEW3,
		      &mask[1]);

	eww = nfp_cpp_set_mu_wocawity_wsb(cpp);
	if (eww < 0) {
		dev_eww(pawent,	"Can't cawcuwate MU wocawity bit offset\n");
		goto eww_out;
	}

	dev_info(cpp->dev.pawent, "Modew: 0x%08x, SN: %pM, Ifc: 0x%04x\n",
		 nfp_cpp_modew(cpp), cpp->sewiaw, nfp_cpp_intewface(cpp));

	wetuwn cpp;

eww_out:
	device_unwegistew(&cpp->dev);
eww_fwee_cpp:
	kfwee(cpp);
eww_mawwoc:
	wetuwn EWW_PTW(eww);
}

/**
 * nfp_cpp_pwiv() - Get the opewations pwivate data of a CPP handwe
 * @cpp:	CPP handwe
 *
 * Wetuwn: Pwivate data fow the NFP CPP handwe
 */
void *nfp_cpp_pwiv(stwuct nfp_cpp *cpp)
{
	wetuwn cpp->pwiv;
}

/**
 * nfp_cpp_device() - Get the Winux device handwe of a CPP handwe
 * @cpp:	CPP handwe
 *
 * Wetuwn: Device fow the NFP CPP bus
 */
stwuct device *nfp_cpp_device(stwuct nfp_cpp *cpp)
{
	wetuwn &cpp->dev;
}

#define NFP_EXPW_OP(func, expw, awgs...)			  \
	({							  \
		stwuct nfp_cpp *cpp = nfp_cpp_expwicit_cpp(expw); \
		int eww = -ENODEV;				  \
								  \
		if (cpp->op->func)				  \
			eww = cpp->op->func(expw, ##awgs);	  \
		eww;						  \
	})

#define NFP_EXPW_OP_NW(func, expw, awgs...)			  \
	({							  \
		stwuct nfp_cpp *cpp = nfp_cpp_expwicit_cpp(expw); \
								  \
		if (cpp->op->func)				  \
			cpp->op->func(expw, ##awgs);		  \
								  \
	})

/**
 * nfp_cpp_expwicit_acquiwe() - Acquiwe expwicit access handwe
 * @cpp:	NFP CPP handwe
 *
 * The 'data_wef' and 'signaw_wef' vawues awe usefuw when
 * constwucting the NFP_EXPW_CSW1 and NFP_EXPW_POST vawues.
 *
 * Wetuwn: NFP CPP expwicit handwe
 */
stwuct nfp_cpp_expwicit *nfp_cpp_expwicit_acquiwe(stwuct nfp_cpp *cpp)
{
	stwuct nfp_cpp_expwicit *expw;
	int eww;

	expw = kzawwoc(sizeof(*expw) + cpp->op->expwicit_pwiv_size, GFP_KEWNEW);
	if (!expw)
		wetuwn NUWW;

	expw->cpp = cpp;
	eww = NFP_EXPW_OP(expwicit_acquiwe, expw);
	if (eww < 0) {
		kfwee(expw);
		wetuwn NUWW;
	}

	wetuwn expw;
}

/**
 * nfp_cpp_expwicit_set_tawget() - Set tawget fiewds fow expwicit
 * @expw:	Expwicit handwe
 * @cpp_id:	CPP ID fiewd
 * @wen:	CPP Wength fiewd
 * @mask:	CPP Mask fiewd
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_set_tawget(stwuct nfp_cpp_expwicit *expw,
				u32 cpp_id, u8 wen, u8 mask)
{
	expw->cmd.cpp_id = cpp_id;
	expw->cmd.wen = wen;
	expw->cmd.byte_mask = mask;

	wetuwn 0;
}

/**
 * nfp_cpp_expwicit_set_data() - Set data fiewds fow expwicit
 * @expw:	Expwicit handwe
 * @data_mastew: CPP Data Mastew fiewd
 * @data_wef:	CPP Data Wef fiewd
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_set_data(stwuct nfp_cpp_expwicit *expw,
			      u8 data_mastew, u16 data_wef)
{
	expw->cmd.data_mastew = data_mastew;
	expw->cmd.data_wef = data_wef;

	wetuwn 0;
}

/**
 * nfp_cpp_expwicit_set_signaw() - Set signaw fiewds fow expwicit
 * @expw:	Expwicit handwe
 * @signaw_mastew: CPP Signaw Mastew fiewd
 * @signaw_wef:	CPP Signaw Wef fiewd
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_set_signaw(stwuct nfp_cpp_expwicit *expw,
				u8 signaw_mastew, u8 signaw_wef)
{
	expw->cmd.signaw_mastew = signaw_mastew;
	expw->cmd.signaw_wef = signaw_wef;

	wetuwn 0;
}

/**
 * nfp_cpp_expwicit_set_posted() - Set compwetion fiewds fow expwicit
 * @expw:	Expwicit handwe
 * @posted:	Twue fow signawed compwetion, fawse othewwise
 * @siga:	CPP Signaw A fiewd
 * @siga_mode:	CPP Signaw A Mode fiewd
 * @sigb:	CPP Signaw B fiewd
 * @sigb_mode:	CPP Signaw B Mode fiewd
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_set_posted(stwuct nfp_cpp_expwicit *expw, int posted,
				u8 siga,
				enum nfp_cpp_expwicit_signaw_mode siga_mode,
				u8 sigb,
				enum nfp_cpp_expwicit_signaw_mode sigb_mode)
{
	expw->cmd.posted = posted;
	expw->cmd.siga = siga;
	expw->cmd.sigb = sigb;
	expw->cmd.siga_mode = siga_mode;
	expw->cmd.sigb_mode = sigb_mode;

	wetuwn 0;
}

/**
 * nfp_cpp_expwicit_put() - Set up the wwite (puww) data fow a expwicit access
 * @expw:	NFP CPP Expwicit handwe
 * @buff:	Data to have the tawget puww in the twansaction
 * @wen:	Wength of data, in bytes
 *
 * The 'wen' pawametew must be wess than ow equaw to 128 bytes.
 *
 * If this function is cawwed befowe the configuwation
 * wegistews awe set, it wiww wetuwn -EINVAW.
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_put(stwuct nfp_cpp_expwicit *expw,
			 const void *buff, size_t wen)
{
	wetuwn NFP_EXPW_OP(expwicit_put, expw, buff, wen);
}

/**
 * nfp_cpp_expwicit_do() - Execute a twansaction, and wait fow it to compwete
 * @expw:	NFP CPP Expwicit handwe
 * @addwess:	Addwess to send in the expwicit twansaction
 *
 * If this function is cawwed befowe the configuwation
 * wegistews awe set, it wiww wetuwn -1, with an ewwno of EINVAW.
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_do(stwuct nfp_cpp_expwicit *expw, u64 addwess)
{
	wetuwn NFP_EXPW_OP(expwicit_do, expw, &expw->cmd, addwess);
}

/**
 * nfp_cpp_expwicit_get() - Get the 'push' (wead) data fwom a expwicit access
 * @expw:	NFP CPP Expwicit handwe
 * @buff:	Data that the tawget pushed in the twansaction
 * @wen:	Wength of data, in bytes
 *
 * The 'wen' pawametew must be wess than ow equaw to 128 bytes.
 *
 * If this function is cawwed befowe aww thwee configuwation
 * wegistews awe set, it wiww wetuwn -1, with an ewwno of EINVAW.
 *
 * If this function is cawwed befowe nfp_cpp_expwicit_do()
 * has compweted, it wiww wetuwn -1, with an ewwno of EBUSY.
 *
 * Wetuwn: 0, ow -EWWNO
 */
int nfp_cpp_expwicit_get(stwuct nfp_cpp_expwicit *expw, void *buff, size_t wen)
{
	wetuwn NFP_EXPW_OP(expwicit_get, expw, buff, wen);
}

/**
 * nfp_cpp_expwicit_wewease() - Wewease expwicit access handwe
 * @expw:	NFP CPP Expwicit handwe
 *
 */
void nfp_cpp_expwicit_wewease(stwuct nfp_cpp_expwicit *expw)
{
	NFP_EXPW_OP_NW(expwicit_wewease, expw);
	kfwee(expw);
}

/**
 * nfp_cpp_expwicit_cpp() - wetuwn CPP handwe fow CPP expwicit
 * @cpp_expwicit:	CPP expwicit handwe
 *
 * Wetuwn: NFP CPP handwe of the expwicit
 */
stwuct nfp_cpp *nfp_cpp_expwicit_cpp(stwuct nfp_cpp_expwicit *cpp_expwicit)
{
	wetuwn cpp_expwicit->cpp;
}

/**
 * nfp_cpp_expwicit_pwiv() - wetuwn pwivate stwuct fow CPP expwicit
 * @cpp_expwicit:	CPP expwicit handwe
 *
 * Wetuwn: pwivate data of the expwicit, ow NUWW
 */
void *nfp_cpp_expwicit_pwiv(stwuct nfp_cpp_expwicit *cpp_expwicit)
{
	wetuwn &cpp_expwicit[1];
}
