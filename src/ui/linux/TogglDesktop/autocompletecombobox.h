#ifndef AUTOCOMPLETECOMBOBOX_H
#define AUTOCOMPLETECOMBOBOX_H

#include <QComboBox>
#include <QLineEdit>
#include <QCompleter>
#include <QSortFilterProxyModel>

#include "autocompleteview.h"

class AutocompleteCompleter;
class AutocompleteProxyModel;
class AutocompleteListView;

class AutocompleteComboBox : public QComboBox {
    Q_OBJECT
public:
    AutocompleteComboBox(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model);

    void showPopup() override;

    bool eventFilter(QObject *o, QEvent *e) override;

    AutocompleteView *currentView();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onDropdownVisibleChanged();
    void onDropdownSelected(AutocompleteView *item);

signals:
    void returnPressed();
    void timeEntrySelected(const QString &name);
    void projectSelected(const QString &name, uint64_t id, const QString &color);
    void taskSelected(const QString &name, uint64_t id);
    void billableChanged(bool billable);
    void tagsChanged(const QString &tags);

private:
    AutocompleteCompleter *completer;
    AutocompleteProxyModel *proxyModel;
    AutocompleteListView *listView;

    QString oldLabel {};
};

class AutocompleteCompleter : public QCompleter {
    Q_OBJECT
    friend class AutocompleteComboBox;
public:
    AutocompleteCompleter(QWidget *parent = nullptr);

    bool eventFilter(QObject *o, QEvent *e) override;
};

class AutocompleteProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    friend class AutocompleteComboBox;
public:
    AutocompleteProxyModel(QObject *parent = nullptr);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // AUTOCOMPLETECOMBOBOX_H
