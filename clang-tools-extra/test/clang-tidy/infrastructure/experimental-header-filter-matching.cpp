// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='does-not-match' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-DEFAULT
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='.*' -exclude-header-filter='confusable_header\.h' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-EXCLUDE
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers' -header-filter='does-not-match' -line-filter='[{"name":"experimental-header-filter-matching.cpp","lines":[[1,20]]}]' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-LINE-FILTER
// RUN: clang-tidy -checks='-*,misc-confusable-identifiers,google-explicit-constructor' -header-filter='does-not-match' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-MIXED
//
// Safe checks use the scoped finder automatically with a narrow header filter.
// RUN: clang-tidy -checks='-*,google-explicit-constructor' -header-filter='explicit_constructor_header\.h' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-SAFE-HEADER
//
// Positive control: main-file diagnostics must still fire with scoped matching.
// RUN: clang-tidy -checks='-*,google-explicit-constructor' -header-filter='does-not-match' %s -- -I %S/Inputs/experimental-header-filter-matching 2>&1 | FileCheck %s --check-prefix=CHECK-MAIN-FILE --implicit-check-not='explicit_constructor_header.h'

#include "confusable_header.h"
#include "explicit_constructor_header.h"

int lO = 1;
// CHECK-DEFAULT: :[[@LINE-1]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-EXCLUDE: :[[@LINE-2]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-LINE-FILTER: :[[@LINE-3]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]
// CHECK-MIXED-DAG: :[[@LINE-4]]:5: warning: 'lO' is confusable with 'l0' [misc-confusable-identifiers]

class A { A(int); };
// CHECK-MIXED-DAG: :[[@LINE-1]]:11: warning: single-argument constructors must be marked explicit{{.*}} [google-explicit-constructor]
// CHECK-MAIN-FILE: :[[@LINE-2]]:11: warning: single-argument constructors must be marked explicit{{.*}} [google-explicit-constructor]
// CHECK-SAFE-HEADER: explicit_constructor_header.h:1:20: warning: single-argument constructors must be marked explicit{{.*}} [google-explicit-constructor]
