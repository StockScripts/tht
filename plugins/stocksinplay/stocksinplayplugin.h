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

#ifndef STOCKSINPLAYPLUGIN_H
#define STOCKSINPLAYPLUGIN_H

#include "pluginimportexport.h"

class QMenu;

class StocksInPlayPlugin : public PluginImportExport
{
    Q_OBJECT

public:
    explicit StocksInPlayPlugin();

    virtual bool init();

    virtual Type type() const
    {
        return AddTickersFrom;
    }

    virtual bool embed(int list, QMenu *parentMenu);

    virtual QList<Hotkey> supportedHotkeysInList() const
    {
        return QList<Hotkey>() << Hotkey(Qt::Key_V);
    }

    virtual void listHotkeyActivated(int list, const Hotkey &ke);

private:
    void addFromStocksInPlay(int list, const QString &hash);
    void showStocksInPlaySelector(int list);
    void rebuildMenu(QMenu *menu);

private slots:
    void slotAdd();
    void slotManageUrls();
};

#endif // STOCKSINPLAYPLUGIN_H
