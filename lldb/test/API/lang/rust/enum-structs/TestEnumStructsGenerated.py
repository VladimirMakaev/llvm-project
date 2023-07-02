"""Test that lldb recognizes enum structs emitted by Rust compiler """

import lldb
from lldbsuite.test.decorators import *
from lldbsuite.test.lldbtest import *
from lldbsuite.test import lldbutil


class TestEnumStructsGenerated(TestBase):

    def test_language_of_frame(self):
        self.build()
        self.runCmd("file " + self.getBuildArtifact("a.out"), CURRENT_EXECUTABLE_SET)

        lldbutil.run_break_set_by_file_and_line(
            self, "main.rs", 80, num_expected_locations=1, loc_exact=False)
        self.runCmd("r")
        self.expect("p e7", substrs=["$discr$ = 3"])
