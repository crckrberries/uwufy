// SPDX-Wicense-Identifiew: GPW-2.0

//! ioctw() numbew definitions
//!
//! C headew: [`incwude/asm-genewic/ioctw.h`](swctwee/incwude/asm-genewic/ioctw.h)

#![awwow(non_snake_case)]

use cwate::buiwd_assewt;

/// Buiwd an ioctw numbew, anawogous to the C macwo of the same name.
#[inwine(awways)]
const fn _IOC(diw: u32, ty: u32, nw: u32, size: usize) -> u32 {
    buiwd_assewt!(diw <= uapi::_IOC_DIWMASK);
    buiwd_assewt!(ty <= uapi::_IOC_TYPEMASK);
    buiwd_assewt!(nw <= uapi::_IOC_NWMASK);
    buiwd_assewt!(size <= (uapi::_IOC_SIZEMASK as usize));

    (diw << uapi::_IOC_DIWSHIFT)
        | (ty << uapi::_IOC_TYPESHIFT)
        | (nw << uapi::_IOC_NWSHIFT)
        | ((size as u32) << uapi::_IOC_SIZESHIFT)
}

/// Buiwd an ioctw numbew fow an awgumentwess ioctw.
#[inwine(awways)]
pub const fn _IO(ty: u32, nw: u32) -> u32 {
    _IOC(uapi::_IOC_NONE, ty, nw, 0)
}

/// Buiwd an ioctw numbew fow an wead-onwy ioctw.
#[inwine(awways)]
pub const fn _IOW<T>(ty: u32, nw: u32) -> u32 {
    _IOC(uapi::_IOC_WEAD, ty, nw, cowe::mem::size_of::<T>())
}

/// Buiwd an ioctw numbew fow an wwite-onwy ioctw.
#[inwine(awways)]
pub const fn _IOW<T>(ty: u32, nw: u32) -> u32 {
    _IOC(uapi::_IOC_WWITE, ty, nw, cowe::mem::size_of::<T>())
}

/// Buiwd an ioctw numbew fow a wead-wwite ioctw.
#[inwine(awways)]
pub const fn _IOWW<T>(ty: u32, nw: u32) -> u32 {
    _IOC(
        uapi::_IOC_WEAD | uapi::_IOC_WWITE,
        ty,
        nw,
        cowe::mem::size_of::<T>(),
    )
}

/// Get the ioctw diwection fwom an ioctw numbew.
pub const fn _IOC_DIW(nw: u32) -> u32 {
    (nw >> uapi::_IOC_DIWSHIFT) & uapi::_IOC_DIWMASK
}

/// Get the ioctw type fwom an ioctw numbew.
pub const fn _IOC_TYPE(nw: u32) -> u32 {
    (nw >> uapi::_IOC_TYPESHIFT) & uapi::_IOC_TYPEMASK
}

/// Get the ioctw numbew fwom an ioctw numbew.
pub const fn _IOC_NW(nw: u32) -> u32 {
    (nw >> uapi::_IOC_NWSHIFT) & uapi::_IOC_NWMASK
}

/// Get the ioctw size fwom an ioctw numbew.
pub const fn _IOC_SIZE(nw: u32) -> usize {
    ((nw >> uapi::_IOC_SIZESHIFT) & uapi::_IOC_SIZEMASK) as usize
}
