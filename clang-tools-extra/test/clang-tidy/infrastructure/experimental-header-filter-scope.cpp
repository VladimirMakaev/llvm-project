// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='does-not-match' %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-DEFAULT
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='does-not-match' -experimental-header-filter-scope %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-CLI --allow-empty
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='.*' -exclude-header-filter='confusable_header\\.h' %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-EXCLUDE
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='.*' -exclude-header-filter='confusable_header\\.h' -config='{ExperimentalHeaderFilterScope: true}' %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-CONFIG --allow-empty

#include "confusable_header.h"

int lO = 1;
// CHECK-DEFAULT: :[[@LINE-1]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-CLI-NOT: warning:
// CHECK-EXCLUDE: :[[@LINE-3]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-CONFIG-NOT: warning:
