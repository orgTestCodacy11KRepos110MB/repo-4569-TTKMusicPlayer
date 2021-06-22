/* =================================================
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2021 Greedysky Studio

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

#ifndef ADPLUGHELPER_H
#define ADPLUGHELPER_H

#include <QStringList>
#include <adplug/adplug.h>
#include <adplug/emuopl.h>

/**
   @author Ilya Kotov <forkotov02@ya.ru>
*/
class AdplugHelper
{
public:
    struct Frame
    {
      Frame(size_t n, unsigned char *buf)
          : m_n(n),
            m_buf(buf)
      {

      }

      size_t m_n = 0;
      unsigned char *m_buf = nullptr;
    };

    explicit AdplugHelper(const QString &path);
    ~AdplugHelper();

    bool initialize();

    int bitrate() const;
    int rate() const { return 44100; }
    int depth() const { return 16; }
    int channels() const { return 1; }

    unsigned long length() const { return m_player->songlength(); }
    void seek(unsigned long pos) const { m_player->seek(pos); }

    Frame read();

    QString title() const { return QString::fromStdString(m_player->gettitle()); }
    QString format() const { return QString::fromStdString(m_player->gettype()); }
    QString author() const { return QString::fromStdString(m_player->getauthor()); }
    QString description() const { return QString::fromStdString(m_player->getdesc()); }
    unsigned int pattern_count() const { return m_player->getpatterns(); }
    unsigned int instrument_count() const { return m_player->getinstruments(); }

    QStringList instruments() const;

private:
    QString m_filePath;
    Copl *m_opl = nullptr;
    CPlayer *m_player = nullptr;
    short m_buf[16384] = { 0 };
    size_t m_remaining = 0;

};

#endif