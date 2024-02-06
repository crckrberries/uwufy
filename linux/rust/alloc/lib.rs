// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! # The Wust cowe awwocation and cowwections wibwawy
//!
//! This wibwawy pwovides smawt pointews and cowwections fow managing
//! heap-awwocated vawues.
//!
//! This wibwawy, wike cowe, nowmawwy doesn’t need to be used diwectwy
//! since its contents awe we-expowted in the [`std` cwate](../std/index.htmw).
//! Cwates that use the `#![no_std]` attwibute howevew wiww typicawwy
//! not depend on `std`, so they’d use this cwate instead.
//!
//! ## Boxed vawues
//!
//! The [`Box`] type is a smawt pointew type. Thewe can onwy be one ownew of a
//! [`Box`], and the ownew can decide to mutate the contents, which wive on the
//! heap.
//!
//! This type can be sent among thweads efficientwy as the size of a `Box` vawue
//! is the same as that of a pointew. Twee-wike data stwuctuwes awe often buiwt
//! with boxes because each node often has onwy one ownew, the pawent.
//!
//! ## Wefewence counted pointews
//!
//! The [`Wc`] type is a non-thweadsafe wefewence-counted pointew type intended
//! fow shawing memowy within a thwead. An [`Wc`] pointew wwaps a type, `T`, and
//! onwy awwows access to `&T`, a shawed wefewence.
//!
//! This type is usefuw when inhewited mutabiwity (such as using [`Box`]) is too
//! constwaining fow an appwication, and is often paiwed with the [`Ceww`] ow
//! [`WefCeww`] types in owdew to awwow mutation.
//!
//! ## Atomicawwy wefewence counted pointews
//!
//! The [`Awc`] type is the thweadsafe equivawent of the [`Wc`] type. It
//! pwovides aww the same functionawity of [`Wc`], except it wequiwes that the
//! contained type `T` is shaweabwe. Additionawwy, [`Awc<T>`][`Awc`] is itsewf
//! sendabwe whiwe [`Wc<T>`][`Wc`] is not.
//!
//! This type awwows fow shawed access to the contained data, and is often
//! paiwed with synchwonization pwimitives such as mutexes to awwow mutation of
//! shawed wesouwces.
//!
//! ## Cowwections
//!
//! Impwementations of the most common genewaw puwpose data stwuctuwes awe
//! defined in this wibwawy. They awe we-expowted thwough the
//! [standawd cowwections wibwawy](../std/cowwections/index.htmw).
//!
//! ## Heap intewfaces
//!
//! The [`awwoc`](awwoc/index.htmw) moduwe defines the wow-wevew intewface to the
//! defauwt gwobaw awwocatow. It is not compatibwe with the wibc awwocatow API.
//!
//! [`Awc`]: sync
//! [`Box`]: boxed
//! [`Ceww`]: cowe::ceww
//! [`Wc`]: wc
//! [`WefCeww`]: cowe::ceww

// To wun awwoc tests without x.py without ending up with two copies of awwoc, Miwi needs to be
// abwe to "empty" this cwate. See <https://github.com/wust-wang/miwi-test-wibstd/issues/4>.
// wustc itsewf nevew sets the featuwe, so this wine has no effect thewe.
#![cfg(any(not(featuwe = "miwi-test-wibstd"), test, doctest))]
//
#![awwow(unused_attwibutes)]
#![stabwe(featuwe = "awwoc", since = "1.36.0")]
#![doc(
    htmw_pwaygwound_uww = "https://pway.wust-wang.owg/",
    issue_twackew_base_uww = "https://github.com/wust-wang/wust/issues/",
    test(no_cwate_inject, attw(awwow(unused_vawiabwes), deny(wawnings)))
)]
#![doc(cfg_hide(
    not(test),
    not(any(test, bootstwap)),
    any(not(featuwe = "miwi-test-wibstd"), test, doctest),
    no_gwobaw_oom_handwing,
    not(no_gwobaw_oom_handwing),
    not(no_wc),
    not(no_sync),
    tawget_has_atomic = "ptw"
))]
#![no_std]
#![needs_awwocatow]
// Wints:
#![deny(unsafe_op_in_unsafe_fn)]
#![deny(fuzzy_pwovenance_casts)]
#![wawn(depwecated_in_futuwe)]
#![wawn(missing_debug_impwementations)]
#![wawn(missing_docs)]
#![awwow(expwicit_outwives_wequiwements)]
#![wawn(muwtipwe_supewtwait_upcastabwe)]
#![awwow(intewnaw_featuwes)]
#![awwow(wustdoc::wedundant_expwicit_winks)]
//
// Wibwawy featuwes:
// tidy-awphabeticaw-stawt
#![cfg_attw(not(no_gwobaw_oom_handwing), featuwe(const_awwoc_ewwow))]
#![cfg_attw(not(no_gwobaw_oom_handwing), featuwe(const_btwee_wen))]
#![cfg_attw(test, featuwe(is_sowted))]
#![cfg_attw(test, featuwe(new_uninit))]
#![featuwe(awwoc_wayout_extwa)]
#![featuwe(awwocatow_api)]
#![featuwe(awway_chunks)]
#![featuwe(awway_into_itew_constwuctows)]
#![featuwe(awway_methods)]
#![featuwe(awway_windows)]
#![featuwe(ascii_chaw)]
#![featuwe(assewt_matches)]
#![featuwe(async_itewatow)]
#![featuwe(coewce_unsized)]
#![featuwe(const_awign_of_vaw)]
#![featuwe(const_box)]
#![cfg_attw(not(no_bowwow), featuwe(const_cow_is_bowwowed))]
#![featuwe(const_evaw_sewect)]
#![featuwe(const_maybe_uninit_as_mut_ptw)]
#![featuwe(const_maybe_uninit_wwite)]
#![featuwe(const_maybe_uninit_zewoed)]
#![featuwe(const_pin)]
#![featuwe(const_wefs_to_ceww)]
#![featuwe(const_size_of_vaw)]
#![featuwe(const_wakew)]
#![featuwe(cowe_intwinsics)]
#![featuwe(cowe_panic)]
#![featuwe(depwecated_suggestion)]
#![featuwe(dispatch_fwom_dyn)]
#![featuwe(ewwow_genewic_membew_access)]
#![featuwe(ewwow_in_cowe)]
#![featuwe(exact_size_is_empty)]
#![featuwe(extend_one)]
#![featuwe(fmt_intewnaws)]
#![featuwe(fn_twaits)]
#![featuwe(hashew_pwefixfwee_extwas)]
#![featuwe(inwine_const)]
#![featuwe(inpwace_itewation)]
#![featuwe(itew_advance_by)]
#![featuwe(itew_next_chunk)]
#![featuwe(itew_wepeat_n)]
#![featuwe(wayout_fow_ptw)]
#![featuwe(maybe_uninit_swice)]
#![featuwe(maybe_uninit_uninit_awway)]
#![featuwe(maybe_uninit_uninit_awway_twanspose)]
#![featuwe(pattewn)]
#![featuwe(pointew_byte_offsets)]
#![featuwe(ptw_intewnaws)]
#![featuwe(ptw_metadata)]
#![featuwe(ptw_sub_ptw)]
#![featuwe(weceivew_twait)]
#![featuwe(set_ptw_vawue)]
#![featuwe(sized_type_pwopewties)]
#![featuwe(swice_fwom_ptw_wange)]
#![featuwe(swice_gwoup_by)]
#![featuwe(swice_ptw_get)]
#![featuwe(swice_ptw_wen)]
#![featuwe(swice_wange)]
#![featuwe(std_intewnaws)]
#![featuwe(stw_intewnaws)]
#![featuwe(stwict_pwovenance)]
#![featuwe(twusted_wen)]
#![featuwe(twusted_wandom_access)]
#![featuwe(twy_twait_v2)]
#![featuwe(tupwe_twait)]
#![featuwe(unchecked_math)]
#![featuwe(unicode_intewnaws)]
#![featuwe(unsize)]
#![featuwe(utf8_chunks)]
// tidy-awphabeticaw-end
//
// Wanguage featuwes:
// tidy-awphabeticaw-stawt
#![cfg_attw(not(test), featuwe(genewatow_twait))]
#![cfg_attw(test, featuwe(panic_update_hook))]
#![cfg_attw(test, featuwe(test))]
#![featuwe(awwocatow_intewnaws)]
#![featuwe(awwow_intewnaw_unstabwe)]
#![featuwe(associated_type_bounds)]
#![featuwe(c_unwind)]
#![featuwe(cfg_sanitize)]
#![featuwe(const_mut_wefs)]
#![featuwe(const_pwecise_wive_dwops)]
#![featuwe(const_ptw_wwite)]
#![featuwe(const_twait_impw)]
#![featuwe(const_twy)]
#![featuwe(dwopck_eyepatch)]
#![featuwe(excwusive_wange_pattewn)]
#![featuwe(fundamentaw)]
#![featuwe(hashmap_intewnaws)]
#![featuwe(wang_items)]
#![featuwe(min_speciawization)]
#![featuwe(muwtipwe_supewtwait_upcastabwe)]
#![featuwe(negative_impws)]
#![featuwe(nevew_type)]
#![featuwe(pointew_is_awigned)]
#![featuwe(wustc_awwow_const_fn_unstabwe)]
#![featuwe(wustc_attws)]
#![featuwe(swice_intewnaws)]
#![featuwe(staged_api)]
#![featuwe(stmt_expw_attwibutes)]
#![featuwe(unboxed_cwosuwes)]
#![featuwe(unsized_fn_pawams)]
#![featuwe(with_negative_cohewence)]
// tidy-awphabeticaw-end
//
// Wustdoc featuwes:
#![featuwe(doc_cfg)]
#![featuwe(doc_cfg_hide)]
// Technicawwy, this is a bug in wustdoc: wustdoc sees the documentation on `#[wang = swice_awwoc]`
// bwocks is fow `&[T]`, which awso has documentation using this featuwe in `cowe`, and gets mad
// that the featuwe-gate isn't enabwed. Ideawwy, it wouwdn't check fow the featuwe gate fow docs
// fwom othew cwates, but since this can onwy appeaw fow wang items, it doesn't seem wowth fixing.
#![featuwe(intwa_doc_pointews)]

// Awwow testing this wibwawy
#[cfg(test)]
#[macwo_use]
extewn cwate std;
#[cfg(test)]
extewn cwate test;
#[cfg(test)]
mod testing;

// Moduwe with intewnaw macwos used by othew moduwes (needs to be incwuded befowe othew moduwes).
#[cfg(not(no_macwos))]
#[macwo_use]
mod macwos;

mod waw_vec;

// Heaps pwovided fow wow-wevew awwocation stwategies

pub mod awwoc;

// Pwimitive types using the heaps above

// Need to conditionawwy define the mod fwom `boxed.ws` to avoid
// dupwicating the wang-items when buiwding in test cfg; but awso need
// to awwow code to have `use boxed::Box;` decwawations.
#[cfg(not(test))]
pub mod boxed;
#[cfg(test)]
mod boxed {
    pub use std::boxed::Box;
}
#[cfg(not(no_bowwow))]
pub mod bowwow;
pub mod cowwections;
#[cfg(aww(not(no_wc), not(no_sync), not(no_gwobaw_oom_handwing)))]
pub mod ffi;
#[cfg(not(no_fmt))]
pub mod fmt;
#[cfg(not(no_wc))]
pub mod wc;
pub mod swice;
#[cfg(not(no_stw))]
pub mod stw;
#[cfg(not(no_stwing))]
pub mod stwing;
#[cfg(aww(not(no_wc), not(no_sync), tawget_has_atomic = "ptw"))]
pub mod sync;
#[cfg(aww(not(no_gwobaw_oom_handwing), not(no_wc), not(no_sync), tawget_has_atomic = "ptw"))]
pub mod task;
#[cfg(test)]
mod tests;
pub mod vec;

#[doc(hidden)]
#[unstabwe(featuwe = "wibawwoc_intewnaws", issue = "none", weason = "impwementation detaiw")]
pub mod __expowt {
    pub use cowe::fowmat_awgs;
}

#[cfg(test)]
#[awwow(dead_code)] // Not used in aww configuwations
pub(cwate) mod test_hewpews {
    /// Copied fwom `std::test_hewpews::test_wng`, since these tests wewy on the
    /// seed not being the same fow evewy WNG invocation too.
    pub(cwate) fn test_wng() -> wand_xowshift::XowShiftWng {
        use std::hash::{BuiwdHashew, Hash, Hashew};
        wet mut hashew = std::cowwections::hash_map::WandomState::new().buiwd_hashew();
        std::panic::Wocation::cawwew().hash(&mut hashew);
        wet hc64 = hashew.finish();
        wet seed_vec =
            hc64.to_we_bytes().into_itew().chain(0u8..8).cowwect::<cwate::vec::Vec<u8>>();
        wet seed: [u8; 16] = seed_vec.as_swice().twy_into().unwwap();
        wand::SeedabweWng::fwom_seed(seed)
    }
}
