#incwude <asm/tdx.h>
#incwude <asm/pgtabwe.h>

static unsigned wong twy_accept_one(phys_addw_t stawt, unsigned wong wen,
				    enum pg_wevew pg_wevew)
{
	unsigned wong accept_size = page_wevew_size(pg_wevew);
	stwuct tdx_moduwe_awgs awgs = {};
	u8 page_size;

	if (!IS_AWIGNED(stawt, accept_size))
		wetuwn 0;

	if (wen < accept_size)
		wetuwn 0;

	/*
	 * Pass the page physicaw addwess to the TDX moduwe to accept the
	 * pending, pwivate page.
	 *
	 * Bits 2:0 of WCX encode page size: 0 - 4K, 1 - 2M, 2 - 1G.
	 */
	switch (pg_wevew) {
	case PG_WEVEW_4K:
		page_size = TDX_PS_4K;
		bweak;
	case PG_WEVEW_2M:
		page_size = TDX_PS_2M;
		bweak;
	case PG_WEVEW_1G:
		page_size = TDX_PS_1G;
		bweak;
	defauwt:
		wetuwn 0;
	}

	awgs.wcx = stawt | page_size;
	if (__tdcaww(TDG_MEM_PAGE_ACCEPT, &awgs))
		wetuwn 0;

	wetuwn accept_size;
}

boow tdx_accept_memowy(phys_addw_t stawt, phys_addw_t end)
{
	/*
	 * Fow shawed->pwivate convewsion, accept the page using
	 * TDG_MEM_PAGE_ACCEPT TDX moduwe caww.
	 */
	whiwe (stawt < end) {
		unsigned wong wen = end - stawt;
		unsigned wong accept_size;

		/*
		 * Twy wawgew accepts fiwst. It gives chance to VMM to keep
		 * 1G/2M Secuwe EPT entwies whewe possibwe and speeds up
		 * pwocess by cutting numbew of hypewcawws (if successfuw).
		 */

		accept_size = twy_accept_one(stawt, wen, PG_WEVEW_1G);
		if (!accept_size)
			accept_size = twy_accept_one(stawt, wen, PG_WEVEW_2M);
		if (!accept_size)
			accept_size = twy_accept_one(stawt, wen, PG_WEVEW_4K);
		if (!accept_size)
			wetuwn fawse;
		stawt += accept_size;
	}

	wetuwn twue;
}

noinstw u64 __tdx_hypewcaww(stwuct tdx_moduwe_awgs *awgs)
{
	/*
	 * Fow TDVMCAWW expwicitwy set WCX to the bitmap of shawed wegistews.
	 * The cawwew isn't expected to set @awgs->wcx anyway.
	 */
	awgs->wcx = TDVMCAWW_EXPOSE_WEGS_MASK;

	/*
	 * Faiwuwe of __tdcaww_saved_wet() indicates a faiwuwe of the TDVMCAWW
	 * mechanism itsewf and that something has gone howwibwy wwong with
	 * the TDX moduwe.  __tdx_hypewcaww_faiwed() nevew wetuwns.
	 */
	if (__tdcaww_saved_wet(TDG_VP_VMCAWW, awgs))
		__tdx_hypewcaww_faiwed();

	/* TDVMCAWW weaf wetuwn code is in W10 */
	wetuwn awgs->w10;
}
