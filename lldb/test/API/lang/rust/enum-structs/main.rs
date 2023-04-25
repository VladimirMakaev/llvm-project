#![no_std]
#![no_main]
use core::ptr::NonNull;

struct VariantStruct {
    field1: usize,
    opt: Option<u32>,
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

#[no_mangle]
pub extern "C" fn main(_argc: isize, _argv: *const *const u8) -> isize {
    let t = (123, 56879);
    let x = Option::Some(1);
    let mut y = MyEnumOptimization::B(30);
    let x1: usize = (&mut y as *mut _) as usize;
    let non_null = NonNull::new(&mut y as *mut _);
    let null_ptr = Option::<NonNull<MyEnumOptimization>>::None;
    let y1 = MyEnumOptimization::C(30, 234674);
    let z = IntEnum::C;
    let a = Option::Some(2);
    let small_enum_value = SmallEnum::VariantA;
    let large_enum_value = LargeEnum::VariantB;
    let e1 = EnumOpt2::A(123);
    let e2 = EnumOpt2::B(true);
    let e3 = EnumOpt2::B(false);
    let e4 = EnumOpt3::A(34);
    let mut e5 = EnumOpt3::B(23456); //break
    match e5 {
        EnumOpt3::B(ref mut x) => *x += 10,
        _ => {}
    };

    return 0;
}

#[panic_handler]
fn my_panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}
