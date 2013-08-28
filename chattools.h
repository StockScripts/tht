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

#ifndef CHATTOOLS_H
#define CHATTOOLS_H

#include <QString>
#include <QRegExp>
#include <QColor>
#include <QList>
#include <QIcon>
#include <QHash>

#include "QXmppPresence.h"

class ChatTools
{
public:
    static void init();

    static QList<QColor> colors();

    static QString cssForLinks();

    static QColor randomColor();

    static QRegExp urlRegExp();

    static QIcon chatIcon();

    static QIcon unreadIcon();

    static QIcon statusIcon(QXmppPresence::AvailableStatusType);

    static QString escapeBrackets(const QString &plain);

private:
    ChatTools();

    static QList<QColor> m_colors;
    static QList<QColor> m_tempColors;
    static QRegExp m_rxLink;
    static QIcon m_chatIcon;
    static QIcon m_unreadIcon;
    static QHash<QXmppPresence::AvailableStatusType, QIcon> m_statusIcons;
};

inline
QList<QColor> ChatTools::colors()
{
    return ChatTools::m_colors;
}

inline
QRegExp ChatTools::urlRegExp()
{
    return ChatTools::m_rxLink;
}

inline
QIcon ChatTools::chatIcon()
{
    return ChatTools::m_chatIcon;
}

inline
QIcon ChatTools::unreadIcon()
{
    return ChatTools::m_unreadIcon;
}

inline
QIcon ChatTools::statusIcon(QXmppPresence::AvailableStatusType type)
{
    return ChatTools::m_statusIcons.value(type);
}

#endif // CHATTOOLS_H
