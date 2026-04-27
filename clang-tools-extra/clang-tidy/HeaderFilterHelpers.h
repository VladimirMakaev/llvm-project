//===--- HeaderFilterHelpers.h - clang-tidy header filtering ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_HEADERFILTERHELPERS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_HEADERFILTERHELPERS_H

#include "clang/Basic/SourceManager.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/Regex.h"

namespace clang::tidy {

/// Classifies whether a source location should be processed according to the
/// configured header filters.
class HeaderFilterMatcher {
public:
  HeaderFilterMatcher(llvm::StringRef HeaderFilterRegex,
                      llvm::StringRef ExcludeHeaderFilterRegex)
      : HeaderFilter(HeaderFilterRegex),
        ExcludeHeaderFilter(ExcludeHeaderFilterRegex) {}

  /// Returns true when the location should be processed.
  ///
  /// Main-file locations are always processed. Locations without a FileEntry
  /// (such as command-line buffers) are treated as user code to match the
  /// existing diagnostic filtering behavior.
  bool shouldProcessLocation(SourceLocation Loc, const SourceManager &SM) {
    if (!Loc.isValid())
      return true;

    if (SM.isInMainFile(Loc))
      return true;

    const FileID FID = SM.getDecomposedExpansionLoc(Loc).first;
    if (const auto It = Cache.find(FID); It != Cache.end())
      return It->second;

    bool Result = true;
    if (OptionalFileEntryRef File = SM.getFileEntryRefForID(FID)) {
      const llvm::StringRef FileName = File->getName();
      Result =
          HeaderFilter.match(FileName) && !ExcludeHeaderFilter.match(FileName);
    }

    Cache[FID] = Result;
    return Result;
  }

private:
  llvm::Regex HeaderFilter;
  llvm::Regex ExcludeHeaderFilter;
  llvm::DenseMap<FileID, bool> Cache;
};

} // namespace clang::tidy

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_HEADERFILTERHELPERS_H
