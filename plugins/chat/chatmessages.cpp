/*
 * This file is part of THT.
 *
 * THT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * THT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with THT.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QTextDocument>

#include "chatmessages.h"
#include "chattools.h"
#include "ui_chatmessages.h"

ChatMessages::ChatMessages(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessages)
{
    ui->setupUi(this);

    ui->textMessages->document()->setDefaultStyleSheet(ChatTools::cssForLinks());
    ui->textMessages->document()->setMaximumBlockCount(1024);
}

ChatMessages::~ChatMessages()
{
    delete ui;
}

QTextBrowser *ChatMessages::messages() const
{
    return ui->textMessages;
}
