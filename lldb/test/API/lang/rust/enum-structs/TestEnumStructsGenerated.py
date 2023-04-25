"""Test that lldb recognizes enum structs emitted by Rust compiler """

import lldb
from lldbsuite.test.decorators import *
from lldbsuite.test.lldbtest import *
from lldbsuite.test import lldbutil


class TestEnumStructsGenerated(TestBase):

    def setUp(self):
        TestBase.setUp(self)
        src_dir = self.getSourceDir()
        yaml_path = os.path.join(src_dir, "main.yaml")
        obj_path = self.getBuildArtifact("main.o")
        self.yaml2obj(yaml_path, obj_path)
        self.dbg.CreateTarget(obj_path)

    @no_debug_info_test
    def test_option_i32_emits_variants(self):
        self.expect("type lookup Option<i32>", substrs=[
            "core::option::Option<i32>::core::option::Option<i32>$Inner::None$Variant $variant$0",
            "core::option::Option<i32>::core::option::Option<i32>$Inner::Some$Variant $variant$1",
            "core::option::Option<i32>::core::option::Option<i32>$Inner inner"
        ])

    @no_debug_info_test
    def test_optimized_enum_emits_variants(self):
        self.expect("type lookup Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>", substrs=[
            "core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>::core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>$Inner::None$Variant $variant$0",
            "core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>::core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>$Inner::Some$Variant $variant$;",
            "core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>::core::option::Option<core::ptr::non_null::NonNull<test_simple_enum::MyEnumOptimization>>$Inner inner"
        ])

    @no_debug_info_test
    def test_custom_enum_enum(self):
        self.expect("type lookup MyEnumOptimization", substrs=[
            "test_simple_enum::MyEnumOptimization::test_simple_enum::MyEnumOptimization$Inner::A$Variant $variant$0;",
            "test_simple_enum::MyEnumOptimization::test_simple_enum::MyEnumOptimization$Inner::B$Variant $variant$1;",
            "test_simple_enum::MyEnumOptimization::test_simple_enum::MyEnumOptimization$Inner::C$Variant $variant$2;",
            "test_simple_enum::MyEnumOptimization::test_simple_enum::MyEnumOptimization$Inner::D$Variant $variant$3;",
            "test_simple_enum::MyEnumOptimization::test_simple_enum::MyEnumOptimization$Inner inner"
        ])
