/*
 * This file is part of THT-lib.
 *
 * THT-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1
 * as published by the Free Software Foundation.
 *
 * THT-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with THT-lib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QTreeWidgetItem>
#include <QKeySequence>
#include <QStringList>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QShortcut>
#include <QFrame>

#include "datamanagerbase.h"
#include "ui_datamanagerbase.h"

class DataManagerBasePrivate
{
public:
    Ui::DataManagerBase *ui;
    bool changed;
};

/***********************************/

DataManagerBase::DataManagerBase(QWidget *parent) :
    QDialog(parent)
{
    d = new DataManagerBasePrivate;

    d->ui = new Ui::DataManagerBase;

    d->ui->setupUi(this);

    QShortcut *s;

    // some hotkeys
    s = new QShortcut(Qt::Key_Insert, d->ui->tree, 0, 0, Qt::WidgetShortcut);
    connect(s, SIGNAL(activated()), this, SLOT(slotAdd()));

    s = new QShortcut(QKeySequence::Delete, d->ui->tree, 0, 0, Qt::WidgetShortcut);
    connect(s, SIGNAL(activated()), this, SLOT(slotDelete()));

    s = new QShortcut(Qt::CTRL + Qt::Key_Up, d->ui->tree, 0, 0, Qt::WidgetShortcut);
    connect(s, SIGNAL(activated()), this, SLOT(slotUp()));

    s = new QShortcut(Qt::CTRL + Qt::Key_Down, d->ui->tree, 0, 0, Qt::WidgetShortcut);
    connect(s, SIGNAL(activated()), this, SLOT(slotDown()));

    s = new QShortcut(QKeySequence::New, d->ui->tree, 0, 0, Qt::WidgetShortcut);
    connect(s, SIGNAL(activated()), this, SLOT(slotClear()));

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    d->ui->tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
    d->ui->tree->header()->setResizeMode(QHeaderView::ResizeToContents);
#endif

    // layout for extra buttons
    QVBoxLayout *l = new QVBoxLayout(d->ui->widgetButtons);
    l->setContentsMargins(0, 0, 0, 4);
    d->ui->widgetButtons->setLayout(l);
}

DataManagerBase::~DataManagerBase()
{
    delete d->ui;
    delete d;
}

void DataManagerBase::setChanged(bool changed)
{
    d->changed = changed;
}

bool DataManagerBase::changed() const
{
    return d->changed;
}

QTreeWidget *DataManagerBase::tree() const
{
    return d->ui->tree;
}

QPushButton *DataManagerBase::buttonAdd() const
{
    return d->ui->pushAdd;
}

bool DataManagerBase::event(QEvent *e)
{
    return QDialog::event(e);
}

void DataManagerBase::addItem(const QStringList &strings, const QVariant &data, bool edit)
{
    QTreeWidgetItem *i = new QTreeWidgetItem(strings);
    i->setData(0, Qt::UserRole, data);
    i->setFlags(i->flags() | Qt::ItemIsEditable);

    d->ui->tree->addTopLevelItem(i);

    if(edit)
    {
        d->ui->tree->setCurrentItem(i);
        d->ui->tree->editItem(i);
    }
}

void DataManagerBase::addButton(QPushButton *button)
{
    if(!button)
        return;

    // add separator
    if(!d->ui->widgetButtons->layout()->count())
    {
        QFrame *line = new QFrame(d->ui->widgetButtons);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        d->ui->widgetButtons->layout()->addWidget(line);
    }

    // add button
    button->setParent(d->ui->widgetButtons);
    d->ui->widgetButtons->layout()->addWidget(button);

    resetTabOrders();
}

void DataManagerBase::moveItem(int index, int diff)
{
    QTreeWidgetItem *i = d->ui->tree->takeTopLevelItem(index);
    d->ui->tree->insertTopLevelItem(index+diff, i);
    d->ui->tree->setCurrentItem(i, QItemSelectionModel::ClearAndSelect);

    d->changed = true;
}

void DataManagerBase::resetTabOrders()
{
    QWidget *lastWidget = d->ui->pushClear;
    QList<QPushButton *> buttons = d->ui->widgetButtons->findChildren<QPushButton *>();

    foreach(QPushButton *b, buttons)
    {
        QWidget::setTabOrder(lastWidget, b);
        lastWidget = b;
    }

    QWidget::setTabOrder(lastWidget, d->ui->buttonBox);
}

void DataManagerBase::slotDelete()
{
    QTreeWidgetItem *ci = d->ui->tree->currentItem();

    if(!ci)
        return;

    QTreeWidgetItem *i = d->ui->tree->itemBelow(ci);

    if(!i)
        i = d->ui->tree->itemAbove(ci);

    delete ci;

    d->ui->tree->setCurrentItem(i, QItemSelectionModel::ClearAndSelect);

    d->changed = true;
}

void DataManagerBase::slotUp()
{
    QTreeWidgetItem *i = d->ui->tree->currentItem();
    int index = d->ui->tree->indexOfTopLevelItem(i);

    if(!i || index <= 0)
        return;

    moveItem(index, -1);
}

void DataManagerBase::slotDown()
{
    QTreeWidgetItem *i = d->ui->tree->currentItem();
    int index = d->ui->tree->indexOfTopLevelItem(i);

    if(!i || index < 0 || index >= d->ui->tree->topLevelItemCount()-1)
        return;

    moveItem(index, +1);
}

void DataManagerBase::slotClear()
{
    d->ui->tree->clear();
    d->changed = true;
}

void DataManagerBase::slotItemChanged()
{
    d->changed = true;
}
