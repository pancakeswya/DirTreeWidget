#include "tree_filter.h"

namespace astro {

bool TreeFilterProxyModel::filterAcceptsRow(int row, const QModelIndex& parent) const {
  QModelIndex index = sourceModel()->index(row, filterKeyColumn(), parent);
  if (!index.isValid()) {
    return false;
  }

  bool found_root = QSortFilterProxyModel::filterAcceptsRow(row, parent);

  if (found_root) {
    return true;
  }

  bool found_sub{};

  int row_count = sourceModel()->rowCount(index);

  for (int i = 0;!found_sub && i < row_count; ++i) {
    found_sub = filterAcceptsRow(i, index);
  }

  return found_sub;
}

} // namespace astro
