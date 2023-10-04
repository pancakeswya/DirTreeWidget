#ifndef TREE_FILTER_H_
#define TREE_FILTER_H_

#include <QSortFilterProxyModel>

namespace astro {

class TreeFilterProxyModel : public QSortFilterProxyModel {
 public:
  using QSortFilterProxyModel::QSortFilterProxyModel;

 protected:
  bool filterAcceptsRow(int row, const QModelIndex& parent) const Q_DECL_OVERRIDE;
};


} // namespace astro

#endif // TREE_FILTER_H_
