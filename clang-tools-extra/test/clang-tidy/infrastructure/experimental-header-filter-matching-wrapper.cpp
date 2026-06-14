// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='wrapper_kept_header\.h' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s

#include "wrapper_header.h"

namespace ns {
int lO = 1;
// CHECK: :[[@LINE-1]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
} // namespace ns
