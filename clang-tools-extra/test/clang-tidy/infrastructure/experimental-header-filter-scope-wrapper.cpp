// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='wrapper_kept_header\.h' %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-DEFAULT
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='wrapper_kept_header\.h' -experimental-header-filter-scope %s -- -I %S/Inputs/experimental-header-filter-scope 2>&1 | FileCheck %s --check-prefix=CHECK-SCOPED

#include "wrapper_header.h"

namespace ns {
int lO = 1;
// CHECK-DEFAULT: :[[@LINE-1]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-SCOPED: :[[@LINE-2]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
} // namespace ns
