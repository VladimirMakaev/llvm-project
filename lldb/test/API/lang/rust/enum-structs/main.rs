#![no_std]
#![no_main]

use core::panic::PanicInfo;
use core::ptr::NonNull;

struct VariantStruct {
    field1: usize,
    opt: Option<u32>,
    opt2: Option<InnerStruct>,
}

struct InnerStruct {
    field1: usize,
    value: EnumOpt2,
}

enum IntEnum {
    A = 2,
    C = 10,
}
enum EnumOpt2 {
    A(u8),
    B(bool),
}

#[repr(usize)]
enum MyEnumOptimization {
    A,
    B(i32),
    C(u8, i32),
    D(Option<VariantStruct>),
}

#[repr(u8)] // Use u8 as the discriminant type
enum SmallEnum {
    VariantA = 1,
    VariantB = 2,
    VariantC = 3,
}

#[repr(u32)] // Use u32 as the discriminant type
enum LargeEnum {
    VariantA = 1,
    VariantB = 2,
    VariantC = 3,
}

enum EnumOpt3 {
    A(u32),
    B(usize),
}

#[no_mangle] // ensure that this symbol is called `main` in the output
fn main(_n: i32, _args: *const *const u8) -> i32 {
    // code here
    let t = (123, 56879);
    let mut e1 = Option::Some(1);
    let mut e2 = MyEnumOptimization::B(30);
    let mut e3: usize = (&mut e2 as *mut _) as usize;
    let mut e4 = NonNull::new(&mut e2 as *mut _);
    let mut e5 = Option::<NonNull<MyEnumOptimization>>::None;
    let mut e6 = MyEnumOptimization::C(30, 234674);
    let mut e7 = MyEnumOptimization::D(Some(VariantStruct {
        field1: 1234,
        opt: None,
        opt2: Some(InnerStruct {
            field1: 123457,
            value: EnumOpt2::B(true),
        }),
    }));
    let mut e8 = IntEnum::C; //break1
    let mut e9 = Option::Some(2);
    let mut e10 = SmallEnum::VariantA;
    let mut e11 = LargeEnum::VariantB;
    let mut e12 = EnumOpt2::A(123);
    let mut e13 = EnumOpt2::B(true);
    let mut e14 = EnumOpt2::B(false);
    let mut e15 = EnumOpt3::A(34);
    let mut e16 = EnumOpt3::B(23456);
    match e16 {
        EnumOpt3::B(ref mut x) => *x += 10,
        _ => {}
    };

    // volatile writes to avoid optimizations
    unsafe {
        core::ptr::write_volatile(&mut e1 as *mut _, e1);
        core::ptr::write_volatile(&mut e2 as *mut _, e2);
        core::ptr::write_volatile(&mut e3 as *mut _, e3);
        core::ptr::write_volatile(&mut e4 as *mut _, e4);
        core::ptr::write_volatile(&mut e5 as *mut _, e5);
        core::ptr::write_volatile(&mut e6 as *mut _, e6);
        core::ptr::write_volatile(&mut e7 as *mut _, e7);
        core::ptr::write_volatile(&mut e8 as *mut _, e8);
        core::ptr::write_volatile(&mut e9 as *mut _, e9);
        core::ptr::write_volatile(&mut e10 as *mut _, e10);
        core::ptr::write_volatile(&mut e11 as *mut _, e11);
        core::ptr::write_volatile(&mut e12 as *mut _, e12);
        core::ptr::write_volatile(&mut e13 as *mut _, e13);
        core::ptr::write_volatile(&mut e14 as *mut _, e14);
        core::ptr::write_volatile(&mut e15 as *mut _, e15);
        core::ptr::write_volatile(&mut e16 as *mut _, e16);
    }

    0
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
