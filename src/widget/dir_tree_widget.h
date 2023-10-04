#ifndef DIRTREEWIDGET_H_
#define DIRTREEWIDGET_H_

#include "tree_filter.h"

#include <QWidget>
#include <QFileIconProvider>
#include <QFileSystemModel>

#include <memory>

namespace astro {

QT_BEGIN_NAMESPACE
namespace Ui { class DirTreeWidget; }
QT_END_NAMESPACE

class DirTreeWidget : public QWidget {
  Q_OBJECT

 public:
  explicit DirTreeWidget(QWidget *parent = nullptr);
  ~DirTreeWidget() Q_DECL_OVERRIDE;
 private slots:
  void FilterSlot();
 private:
  void SetHomePath();
  void SetupTreeView();

  QFileSystemModel* fsystem_model_;
  TreeFilterProxyModel* proxy_model_;
  std::unique_ptr<QFileIconProvider> icon_provider_;
  Ui::DirTreeWidget *ui_;
};

} // namespace astro

#endif // DIRTREEWIDGET_H_
