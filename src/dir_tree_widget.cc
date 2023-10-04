#include "dir_tree_widget.h"
#include "./ui_dir_tree_widget.h"

namespace astro {

DirTreeWidget::DirTreeWidget(QWidget *parent)
    : QWidget(parent),
      fsystem_model_(new QFileSystemModel(this)),
      proxy_model_(new TreeFilterProxyModel(this)),
      icon_provider_(new QFileIconProvider),
      ui_(new Ui::DirTreeWidget) {
  ui_->setupUi(this);
  SetupTreeView();
}

DirTreeWidget::~DirTreeWidget() {
  delete ui_;
}

inline void DirTreeWidget::SetHomePath() {
  const QModelIndex root_idx = fsystem_model_->index(QDir::homePath());
  const QModelIndex filter_idx = proxy_model_->mapFromSource(root_idx);
  ui_->tree_view->setRootIndex(filter_idx);
}

void DirTreeWidget::SetupTreeView() {
  fsystem_model_->setIconProvider(icon_provider_.get());

  fsystem_model_->setRootPath(QDir::homePath());
  fsystem_model_->setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
#if (QT_VERSION >= QT_VERSION_CHECK(5,12,0))
  fsystem_model_->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
  fsystem_model_->setOption(QFileSystemModel::DontWatchForChanges);
#endif
  proxy_model_->setSourceModel(fsystem_model_);
  proxy_model_->setFilterKeyColumn(0);
  proxy_model_->setRecursiveFilteringEnabled(true);

  ui_->tree_view->setModel(proxy_model_);

  SetHomePath();

  ui_->tree_view->header()->setStretchLastSection(false);
  ui_->tree_view->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  ui_->tree_view->setAnimated(false);
  ui_->tree_view->setIndentation(20);
  ui_->tree_view->setSortingEnabled(true);

  connect(ui_->line_edit, QOverload<const QString &>::of(&QLineEdit::textChanged), this, &DirTreeWidget::FilterSlot);
}

void DirTreeWidget::FilterSlot() {
#if (QT_VERSION >= QT_VERSION_CHECK(5,12,0))
  proxy_model_->setFilterRegularExpression(ui_->line_edit->text());
#else
  proxy_model_->setFilterRegExp(ui_->line_edit->text());
#endif
  SetHomePath();
}

} // namespace astro
