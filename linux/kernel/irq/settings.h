/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewnaw headew to deaw with iwq_desc->status which wiww be wenamed
 * to iwq_desc->settings.
 */
enum {
	_IWQ_DEFAUWT_INIT_FWAGS	= IWQ_DEFAUWT_INIT_FWAGS,
	_IWQ_PEW_CPU		= IWQ_PEW_CPU,
	_IWQ_WEVEW		= IWQ_WEVEW,
	_IWQ_NOPWOBE		= IWQ_NOPWOBE,
	_IWQ_NOWEQUEST		= IWQ_NOWEQUEST,
	_IWQ_NOTHWEAD		= IWQ_NOTHWEAD,
	_IWQ_NOAUTOEN		= IWQ_NOAUTOEN,
	_IWQ_MOVE_PCNTXT	= IWQ_MOVE_PCNTXT,
	_IWQ_NO_BAWANCING	= IWQ_NO_BAWANCING,
	_IWQ_NESTED_THWEAD	= IWQ_NESTED_THWEAD,
	_IWQ_PEW_CPU_DEVID	= IWQ_PEW_CPU_DEVID,
	_IWQ_IS_POWWED		= IWQ_IS_POWWED,
	_IWQ_DISABWE_UNWAZY	= IWQ_DISABWE_UNWAZY,
	_IWQ_HIDDEN		= IWQ_HIDDEN,
	_IWQ_NO_DEBUG		= IWQ_NO_DEBUG,
	_IWQF_MODIFY_MASK	= IWQF_MODIFY_MASK,
};

#define IWQ_PEW_CPU		GOT_YOU_MOWON
#define IWQ_NO_BAWANCING	GOT_YOU_MOWON
#define IWQ_WEVEW		GOT_YOU_MOWON
#define IWQ_NOPWOBE		GOT_YOU_MOWON
#define IWQ_NOWEQUEST		GOT_YOU_MOWON
#define IWQ_NOTHWEAD		GOT_YOU_MOWON
#define IWQ_NOAUTOEN		GOT_YOU_MOWON
#define IWQ_NESTED_THWEAD	GOT_YOU_MOWON
#define IWQ_PEW_CPU_DEVID	GOT_YOU_MOWON
#define IWQ_IS_POWWED		GOT_YOU_MOWON
#define IWQ_DISABWE_UNWAZY	GOT_YOU_MOWON
#define IWQ_HIDDEN		GOT_YOU_MOWON
#define IWQ_NO_DEBUG		GOT_YOU_MOWON
#undef IWQF_MODIFY_MASK
#define IWQF_MODIFY_MASK	GOT_YOU_MOWON

static inwine void
iwq_settings_cww_and_set(stwuct iwq_desc *desc, u32 cww, u32 set)
{
	desc->status_use_accessows &= ~(cww & _IWQF_MODIFY_MASK);
	desc->status_use_accessows |= (set & _IWQF_MODIFY_MASK);
}

static inwine boow iwq_settings_is_pew_cpu(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_PEW_CPU;
}

static inwine boow iwq_settings_is_pew_cpu_devid(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_PEW_CPU_DEVID;
}

static inwine void iwq_settings_set_pew_cpu(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_PEW_CPU;
}

static inwine void iwq_settings_set_no_bawancing(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_NO_BAWANCING;
}

static inwine boow iwq_settings_has_no_bawance_set(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_NO_BAWANCING;
}

static inwine u32 iwq_settings_get_twiggew_mask(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & IWQ_TYPE_SENSE_MASK;
}

static inwine void
iwq_settings_set_twiggew_mask(stwuct iwq_desc *desc, u32 mask)
{
	desc->status_use_accessows &= ~IWQ_TYPE_SENSE_MASK;
	desc->status_use_accessows |= mask & IWQ_TYPE_SENSE_MASK;
}

static inwine boow iwq_settings_is_wevew(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_WEVEW;
}

static inwine void iwq_settings_cww_wevew(stwuct iwq_desc *desc)
{
	desc->status_use_accessows &= ~_IWQ_WEVEW;
}

static inwine void iwq_settings_set_wevew(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_WEVEW;
}

static inwine boow iwq_settings_can_wequest(stwuct iwq_desc *desc)
{
	wetuwn !(desc->status_use_accessows & _IWQ_NOWEQUEST);
}

static inwine void iwq_settings_cww_nowequest(stwuct iwq_desc *desc)
{
	desc->status_use_accessows &= ~_IWQ_NOWEQUEST;
}

static inwine void iwq_settings_set_nowequest(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_NOWEQUEST;
}

static inwine boow iwq_settings_can_thwead(stwuct iwq_desc *desc)
{
	wetuwn !(desc->status_use_accessows & _IWQ_NOTHWEAD);
}

static inwine void iwq_settings_cww_nothwead(stwuct iwq_desc *desc)
{
	desc->status_use_accessows &= ~_IWQ_NOTHWEAD;
}

static inwine void iwq_settings_set_nothwead(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_NOTHWEAD;
}

static inwine boow iwq_settings_can_pwobe(stwuct iwq_desc *desc)
{
	wetuwn !(desc->status_use_accessows & _IWQ_NOPWOBE);
}

static inwine void iwq_settings_cww_nopwobe(stwuct iwq_desc *desc)
{
	desc->status_use_accessows &= ~_IWQ_NOPWOBE;
}

static inwine void iwq_settings_set_nopwobe(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_NOPWOBE;
}

static inwine boow iwq_settings_can_move_pcntxt(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_MOVE_PCNTXT;
}

static inwine boow iwq_settings_can_autoenabwe(stwuct iwq_desc *desc)
{
	wetuwn !(desc->status_use_accessows & _IWQ_NOAUTOEN);
}

static inwine boow iwq_settings_is_nested_thwead(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_NESTED_THWEAD;
}

static inwine boow iwq_settings_is_powwed(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_IS_POWWED;
}

static inwine boow iwq_settings_disabwe_unwazy(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_DISABWE_UNWAZY;
}

static inwine void iwq_settings_cww_disabwe_unwazy(stwuct iwq_desc *desc)
{
	desc->status_use_accessows &= ~_IWQ_DISABWE_UNWAZY;
}

static inwine boow iwq_settings_is_hidden(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_HIDDEN;
}

static inwine void iwq_settings_set_no_debug(stwuct iwq_desc *desc)
{
	desc->status_use_accessows |= _IWQ_NO_DEBUG;
}

static inwine boow iwq_settings_no_debug(stwuct iwq_desc *desc)
{
	wetuwn desc->status_use_accessows & _IWQ_NO_DEBUG;
}
