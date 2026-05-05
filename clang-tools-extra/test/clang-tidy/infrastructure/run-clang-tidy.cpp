// RUN: %run_clang_tidy --help
// RUN: rm -rf %t
// RUN: mkdir %t
// RUN: echo "[{\"directory\":\".\",\"command\":\"clang++ -c %/t/test.cpp\",\"file\":\"%/t/test.cpp\"}]" | sed -e 's/\\/\\\\/g' > %t/compile_commands.json
// RUN: echo "Checks: '-*,modernize-use-auto'" > %t/.clang-tidy
// RUN: echo "WarningsAsErrors: '*'" >> %t/.clang-tidy
// RUN: echo "CheckOptions:" >> %t/.clang-tidy
// RUN: echo "  modernize-use-auto.MinTypeNameLength: '0'" >> %t/.clang-tidy
// RUN: cp "%s" "%t/test.cpp"
// RUN: cd "%t"
// RUN: not %run_clang_tidy "test.cpp" 2>&1 | FileCheck %s --check-prefix=CHECK-JMAX
// CHECK-JMAX: Running clang-tidy in {{[1-9][0-9]*}} threads for

// RUN: not %run_clang_tidy -j 1 "test.cpp" 2>&1 | FileCheck %s --check-prefix=CHECK-J1
// CHECK-J1: Running clang-tidy in 1 threads for

// RUN: rm -rf %t-scope
// RUN: mkdir -p %t-scope/include
// RUN: echo "[{\"directory\":\".\",\"command\":\"clang++ -c %/t-scope/test.cpp -I%/t-scope/include\",\"file\":\"%/t-scope/test.cpp\"}]" | sed -e 's/\\/\\\\/g' > %t-scope/compile_commands.json
// RUN: echo "Checks: '-*,misc-confusable-identifiers'" > %t-scope/.clang-tidy
// RUN: echo "WarningsAsErrors: '*'" >> %t-scope/.clang-tidy
// RUN: echo "int l0 = 0;" > %t-scope/include/confusable_header.h
// RUN: echo '#include "confusable_header.h"' > %t-scope/test.cpp
// RUN: echo 'int lO = 1;' >> %t-scope/test.cpp
// RUN: cd "%t-scope"
// RUN: not %run_clang_tidy -j 1 -header-filter=does-not-match "test.cpp" 2>&1 | FileCheck %s --check-prefix=CHECK-SCOPE-OFF
// RUN: %run_clang_tidy -j 1 -header-filter=does-not-match -experimental-header-filter-scope=true "test.cpp" 2>&1 | FileCheck %s --check-prefix=CHECK-SCOPE-ON
// CHECK-SCOPE-OFF: 'lO' is confusable with 'l0'
// CHECK-SCOPE-ON: Running clang-tidy in 1 threads for 1 files out of 1 in compilation database
// CHECK-SCOPE-ON-NOT: 'lO' is confusable with 'l0'

int main()
{
  int* x = new int();
  delete x;
}
