#ifndef DLNAFINDER_H
#define DLNAFINDER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <QStringList>
#include "musicextrasglobaldefine.h"

class DlnaClient;
class DlnaFinderPrivate;

/*! @brief The class of the dlna finder.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_EXTRAS_EXPORT DlnaFinder : public QObject
{
    Q_OBJECT
public:
    explicit DlnaFinder(QObject *parent = nullptr);

    void find();

    DlnaClient* client(int index) const;
    QList<DlnaClient*> clients() const;
    QStringList clientNames() const;

Q_SIGNALS:
    void finished();

public Q_SLOTS:
    void readResponse();

private:
    TTK_DECLARE_PRIVATE(DlnaFinder)

};

#endif // DLNAFINDER_H
